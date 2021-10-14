// Copyright (c) 2017 The Khronos Group Inc.
// Copyright (c) 2017 Valve Corporation
// Copyright (c) 2017 LunarG Inc.
// Copyright (c) 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "source/opt/aggressive_dead_code_elim_pass.h"

#include <memory>
#include <stack>

#include "source/cfa.h"
#include "source/latest_version_glsl_std_450_header.h"
#include "source/opt/eliminate_dead_functions_util.h"
#include "source/opt/iterator.h"
#include "source/opt/reflect.h"
#include "source/spirv_constant.h"

namespace spvtools {
namespace opt {

namespace {

const uint32_t kTypePointerStorageClassInIdx = 0;
const uint32_t kEntryPointFunctionIdInIdx = 1;
const uint32_t kSelectionMergeMergeBlockIdInIdx = 0;
const uint32_t kLoopMergeContinueBlockIdInIdx = 1;
const uint32_t kCopyMemoryTargetAddrInIdx = 0;
const uint32_t kCopyMemorySourceAddrInIdx = 1;
const uint32_t kDebugDeclareOperandVariableIndex = 5;
const uint32_t kGlobalVariableVariableIndex = 12;

// Sorting functor to present annotation instructions in an easy-to-process
// order. The functor orders by opcode first and falls back on unique id
// ordering if both instructions have the same opcode.
//
// Desired priority:
// SpvOpGroupDecorate
// SpvOpGroupMemberDecorate
// SpvOpDecorate
// SpvOpMemberDecorate
// SpvOpDecorateId
// SpvOpDecorateStringGOOGLE
// SpvOpDecorationGroup
struct DecorationLess {
  bool operator()(const Instruction* lhs, const Instruction* rhs) const {
    assert(lhs && rhs);
    SpvOp lhsOp = lhs->opcode();
    SpvOp rhsOp = rhs->opcode();
    if (lhsOp != rhsOp) {
#define PRIORITY_CASE(opcode)                          \
  if (lhsOp == opcode && rhsOp != opcode) return true; \
  if (rhsOp == opcode && lhsOp != opcode) return false;
      // OpGroupDecorate and OpGroupMember decorate are highest priority to
      // eliminate dead targets early and simplify subsequent checks.
      PRIORITY_CASE(SpvOpGroupDecorate)
      PRIORITY_CASE(SpvOpGroupMemberDecorate)
      PRIORITY_CASE(SpvOpDecorate)
      PRIORITY_CASE(SpvOpMemberDecorate)
      PRIORITY_CASE(SpvOpDecorateId)
      PRIORITY_CASE(SpvOpDecorateStringGOOGLE)
      // OpDecorationGroup is lowest priority to ensure use/def chains remain
      // usable for instructions that target this group.
      PRIORITY_CASE(SpvOpDecorationGroup)
#undef PRIORITY_CASE
    }

    // Fall back to maintain total ordering (compare unique ids).
    return *lhs < *rhs;
  }
};

}  // namespace

bool AggressiveDCEPass::IsVarOfStorage(uint32_t varId, uint32_t storageClass) {
  if (varId == 0) return false;
  const Instruction* varInst = get_def_use_mgr()->GetDef(varId);
  const SpvOp op = varInst->opcode();
  if (op != SpvOpVariable) return false;
  const uint32_t varTypeId = varInst->type_id();
  const Instruction* varTypeInst = get_def_use_mgr()->GetDef(varTypeId);
  if (varTypeInst->opcode() != SpvOpTypePointer) return false;
  return varTypeInst->GetSingleWordInOperand(kTypePointerStorageClassInIdx) ==
         storageClass;
}

bool AggressiveDCEPass::IsLocalVar(uint32_t varId) {
  if (IsVarOfStorage(varId, SpvStorageClassFunction)) {
    return true;
  }
  if (!private_like_local_) {
    return false;
  }

  return IsVarOfStorage(varId, SpvStorageClassPrivate) ||
         IsVarOfStorage(varId, SpvStorageClassWorkgroup);
}

void AggressiveDCEPass::AddStores(Function* func, uint32_t ptrId) {
  get_def_use_mgr()->ForEachUser(ptrId, [this, ptrId, func](Instruction* user) {
    // If the user is not a part of |func|, skip it.
    BasicBlock* blk = context()->get_instr_block(user);
    if (blk && blk->GetParent() != func) return;

    switch (user->opcode()) {
      case SpvOpAccessChain:
      case SpvOpInBoundsAccessChain:
      case SpvOpCopyObject:
        this->AddStores(func, user->result_id());
        break;
      case SpvOpLoad:
        break;
      case SpvOpCopyMemory:
      case SpvOpCopyMemorySized:
        if (user->GetSingleWordInOperand(kCopyMemoryTargetAddrInIdx) == ptrId) {
          AddToWorklist(user);
        }
        break;
      // If default, assume it stores e.g. frexp, modf, function call
      case SpvOpStore:
      default:
        AddToWorklist(user);
        break;
    }
  });
}

bool AggressiveDCEPass::AllExtensionsSupported() const {
  // If any extension not in allowlist, return false
  for (auto& ei : get_module()->extensions()) {
    const char* extName =
        reinterpret_cast<const char*>(&ei.GetInOperand(0).words[0]);
    if (extensions_allowlist_.find(extName) == extensions_allowlist_.end())
      return false;
  }
  // Only allow NonSemantic.Shader.DebugInfo.100, we cannot safely optimise
  // around unknown extended instruction sets even if they are non-semantic
  for (auto& inst : context()->module()->ext_inst_imports()) {
    assert(inst.opcode() == SpvOpExtInstImport &&
           "Expecting an import of an extension's instruction set.");
    const char* extension_name =
        reinterpret_cast<const char*>(&inst.GetInOperand(0).words[0]);
    if (0 == std::strncmp(extension_name, "NonSemantic.", 12) &&
        0 != std::strncmp(extension_name, "NonSemantic.Shader.DebugInfo.100",
                          32)) {
      return false;
    }
  }
  return true;
}

bool AggressiveDCEPass::IsDead(Instruction* inst) {
  if (IsLive(inst)) return false;
  if ((inst->IsBranch() || inst->opcode() == SpvOpUnreachable) &&
      context()->get_instr_block(inst)->GetMergeInst() == nullptr)
    return false;
  return true;
}

bool AggressiveDCEPass::IsTargetDead(Instruction* inst) {
  const uint32_t tId = inst->GetSingleWordInOperand(0);
  Instruction* tInst = get_def_use_mgr()->GetDef(tId);
  if (IsAnnotationInst(tInst->opcode())) {
    // This must be a decoration group. We go through annotations in a specific
    // order. So if this is not used by any group or group member decorates, it
    // is dead.
    assert(tInst->opcode() == SpvOpDecorationGroup);
    bool dead = true;
    get_def_use_mgr()->ForEachUser(tInst, [&dead](Instruction* user) {
      if (user->opcode() == SpvOpGroupDecorate ||
          user->opcode() == SpvOpGroupMemberDecorate)
        dead = false;
    });
    return dead;
  }
  return IsDead(tInst);
}

void AggressiveDCEPass::ProcessLoad(Function* func, uint32_t varId) {
  // Only process locals
  if (!IsLocalVar(varId)) return;
  // Return if already processed
  if (live_local_vars_.find(varId) != live_local_vars_.end()) return;
  // Mark all stores to varId as live
  AddStores(func, varId);
  // Cache varId as processed
  live_local_vars_.insert(varId);
}

void AggressiveDCEPass::AddBranch(uint32_t labelId, BasicBlock* bp) {
  std::unique_ptr<Instruction> newBranch(
      new Instruction(context(), SpvOpBranch, 0, 0,
                      {{spv_operand_type_t::SPV_OPERAND_TYPE_ID, {labelId}}}));
  context()->AnalyzeDefUse(&*newBranch);
  context()->set_instr_block(&*newBranch, bp);
  bp->AddInstruction(std::move(newBranch));
}

void AggressiveDCEPass::AddBreaksAndContinuesToWorklist(
    Instruction* mergeInst) {
  assert(mergeInst->opcode() == SpvOpSelectionMerge ||
         mergeInst->opcode() == SpvOpLoopMerge);

  BasicBlock* header = context()->get_instr_block(mergeInst);
  const uint32_t mergeId = mergeInst->GetSingleWordInOperand(0);
  get_def_use_mgr()->ForEachUser(mergeId, [header, this](Instruction* user) {
    if (!user->IsBranch()) return;
    BasicBlock* block = context()->get_instr_block(user);
    if (BlockIsInConstruct(header, block)) {
      // This is a break from the loop.
      AddToWorklist(user);
      // Add branch's merge if there is one.
      Instruction* userMerge = GetMergeInstruction(user);
      if (userMerge != nullptr) AddToWorklist(userMerge);
    }
  });

  if (mergeInst->opcode() != SpvOpLoopMerge) {
    return;
  }

  // For loops we need to find the continues as well.
  const uint32_t contId =
      mergeInst->GetSingleWordInOperand(kLoopMergeContinueBlockIdInIdx);
  get_def_use_mgr()->ForEachUser(contId, [&contId, this](Instruction* user) {
    SpvOp op = user->opcode();
    if (op == SpvOpBranchConditional || op == SpvOpSwitch) {
      // A conditional branch or switch can only be a continue if it does not
      // have a merge instruction or its merge block is not the continue block.
      Instruction* hdrMerge = GetMergeInstruction(user);
      if (hdrMerge != nullptr && hdrMerge->opcode() == SpvOpSelectionMerge) {
        uint32_t hdrMergeId =
            hdrMerge->GetSingleWordInOperand(kSelectionMergeMergeBlockIdInIdx);
        if (hdrMergeId == contId) return;
        // Need to mark merge instruction too
        AddToWorklist(hdrMerge);
      }
    } else if (op == SpvOpBranch) {
      // An unconditional branch can only be a continue if it is not
      // branching to its own merge block.
      BasicBlock* blk = context()->get_instr_block(user);
      Instruction* hdrBranch = GetHeaderBranch(blk);
      if (hdrBranch == nullptr) return;
      Instruction* hdrMerge = GetMergeInstruction(hdrBranch);
      if (hdrMerge->opcode() == SpvOpLoopMerge) return;
      uint32_t hdrMergeId =
          hdrMerge->GetSingleWordInOperand(kSelectionMergeMergeBlockIdInIdx);
      if (contId == hdrMergeId) return;
    } else {
      return;
    }
    AddToWorklist(user);
  });
}

bool AggressiveDCEPass::AggressiveDCE(Function* func) {
  // Mark function parameters as live.
  AddToWorklist(&func->DefInst());
  MarkFunctionParameterAsLive(func);

  std::list<BasicBlock*> structuredOrder;
  cfg()->ComputeStructuredOrder(func, &*func->begin(), &structuredOrder);
  bool modified = false;
  live_local_vars_.clear();
  InitializeWorkList(func, structuredOrder);

  // Perform closure on live instruction set.
  while (!worklist_.empty()) {
    Instruction* liveInst = worklist_.front();
    // Add all operand instructions of Debug[No]Lines
    for (auto& lineInst : liveInst->dbg_line_insts()) {
      if (lineInst.IsDebugLineInst()) {
        lineInst.ForEachInId([this](const uint32_t* iid) {
          AddToWorklist(get_def_use_mgr()->GetDef(*iid));
        });
      }
    }
    // Add all operand instructions if not already live
    liveInst->ForEachInId([&liveInst, this](const uint32_t* iid) {
      Instruction* inInst = get_def_use_mgr()->GetDef(*iid);
      // Do not add label if an operand of a branch. This is not needed
      // as part of live code discovery and can create false live code,
      // for example, the branch to a header of a loop.
      if (inInst->opcode() == SpvOpLabel && liveInst->IsBranch()) return;
      AddToWorklist(inInst);
    });
    if (liveInst->type_id() != 0) {
      AddToWorklist(get_def_use_mgr()->GetDef(liveInst->type_id()));
    }
    BasicBlock* basic_block = context()->get_instr_block(liveInst);
    if (basic_block != nullptr) {
      AddToWorklist(basic_block->GetLabelInst());
    }

    // If in a structured if or loop construct, add the controlling
    // conditional branch and its merge.
    BasicBlock* blk = context()->get_instr_block(liveInst);
    Instruction* branchInst = GetHeaderBranch(blk);
    if (branchInst != nullptr) {
      AddToWorklist(branchInst);
      Instruction* mergeInst = GetMergeInstruction(branchInst);
      AddToWorklist(mergeInst);
    }
    // If the block is a header, add the next outermost controlling
    // conditional branch and its merge.
    Instruction* nextBranchInst = GetBranchForNextHeader(blk);
    if (nextBranchInst != nullptr) {
      AddToWorklist(nextBranchInst);
      Instruction* mergeInst = GetMergeInstruction(nextBranchInst);
      AddToWorklist(mergeInst);
    }
    // If local load, add all variable's stores if variable not already live
    if (liveInst->opcode() == SpvOpLoad || liveInst->IsAtomicWithLoad()) {
      uint32_t varId;
      (void)GetPtr(liveInst, &varId);
      if (varId != 0) {
        ProcessLoad(func, varId);
      }
      // Process memory copies like loads
    } else if (liveInst->opcode() == SpvOpCopyMemory ||
               liveInst->opcode() == SpvOpCopyMemorySized) {
      uint32_t varId;
      (void)GetPtr(liveInst->GetSingleWordInOperand(kCopyMemorySourceAddrInIdx),
                   &varId);
      if (varId != 0) {
        ProcessLoad(func, varId);
      }
      // If DebugDeclare, process as load of variable
    } else if (liveInst->GetCommonDebugOpcode() ==
               CommonDebugInfoDebugDeclare) {
      uint32_t varId =
          liveInst->GetSingleWordOperand(kDebugDeclareOperandVariableIndex);
      ProcessLoad(func, varId);
      // If DebugValue with Deref, process as load of variable
    } else if (liveInst->GetCommonDebugOpcode() == CommonDebugInfoDebugValue) {
      uint32_t varId = context()
                           ->get_debug_info_mgr()
                           ->GetVariableIdOfDebugValueUsedForDeclare(liveInst);
      if (varId != 0) ProcessLoad(func, varId);
      // If merge, add other branches that are part of its control structure
    } else if (liveInst->opcode() == SpvOpLoopMerge ||
               liveInst->opcode() == SpvOpSelectionMerge) {
      AddBreaksAndContinuesToWorklist(liveInst);
      // If function call, treat as if it loads from all pointer arguments
    } else if (liveInst->opcode() == SpvOpFunctionCall) {
      liveInst->ForEachInId([this, func](const uint32_t* iid) {
        // Skip non-ptr args
        if (!IsPtr(*iid)) return;
        uint32_t varId;
        (void)GetPtr(*iid, &varId);
        ProcessLoad(func, varId);
      });
      // If function parameter, treat as if it's result id is loaded from
    } else if (liveInst->opcode() == SpvOpFunctionParameter) {
      ProcessLoad(func, liveInst->result_id());
      // We treat an OpImageTexelPointer as a load of the pointer, and
      // that value is manipulated to get the result.
    } else if (liveInst->opcode() == SpvOpImageTexelPointer) {
      uint32_t varId;
      (void)GetPtr(liveInst, &varId);
      if (varId != 0) {
        ProcessLoad(func, varId);
      }
    }

    // Add OpDecorateId instructions that apply to this instruction to the work
    // list.  We use the decoration manager to look through the group
    // decorations to get to the OpDecorate* instructions themselves.
    auto decorations =
        get_decoration_mgr()->GetDecorationsFor(liveInst->result_id(), false);
    for (Instruction* dec : decorations) {
      // We only care about OpDecorateId instructions because the are the only
      // decorations that will reference an id that will have to be kept live
      // because of that use.
      if (dec->opcode() != SpvOpDecorateId) {
        continue;
      }
      if (dec->GetSingleWordInOperand(1) ==
          SpvDecorationHlslCounterBufferGOOGLE) {
        // These decorations should not force the use id to be live.  It will be
        // removed if either the target or the in operand are dead.
        continue;
      }
      AddToWorklist(dec);
    }

    // Add DebugScope and DebugInlinedAt for |liveInst| to the work list.
    if (liveInst->GetDebugScope().GetLexicalScope() != kNoDebugScope) {
      auto* scope = get_def_use_mgr()->GetDef(
          liveInst->GetDebugScope().GetLexicalScope());
      AddToWorklist(scope);
    }
    if (liveInst->GetDebugInlinedAt() != kNoInlinedAt) {
      auto* inlined_at =
          get_def_use_mgr()->GetDef(liveInst->GetDebugInlinedAt());
      AddToWorklist(inlined_at);
    }
    worklist_.pop();
  }

  // Kill dead instructions and remember dead blocks
  for (auto bi = structuredOrder.begin(); bi != structuredOrder.end();) {
    uint32_t mergeBlockId = 0;
    (*bi)->ForEachInst([this, &modified, &mergeBlockId](Instruction* inst) {
      if (!IsDead(inst)) return;
      if (inst->opcode() == SpvOpLabel) return;
      // If dead instruction is selection merge, remember merge block
      // for new branch at end of block
      if (inst->opcode() == SpvOpSelectionMerge ||
          inst->opcode() == SpvOpLoopMerge)
        mergeBlockId = inst->GetSingleWordInOperand(0);
      to_kill_.push_back(inst);
      modified = true;
    });
    // If a structured if or loop was deleted, add a branch to its merge
    // block, and traverse to the merge block and continue processing there.
    // We know the block still exists because the label is not deleted.
    if (mergeBlockId != 0) {
      AddBranch(mergeBlockId, *bi);
      for (++bi; (*bi)->id() != mergeBlockId; ++bi) {
      }

      auto merge_terminator = (*bi)->terminator();
      if (merge_terminator->opcode() == SpvOpUnreachable) {
        // The merge was unreachable. This is undefined behaviour so just
        // return (or return an undef). Then mark the new return as live.
        auto func_ret_type_inst = get_def_use_mgr()->GetDef(func->type_id());
        if (func_ret_type_inst->opcode() == SpvOpTypeVoid) {
          merge_terminator->SetOpcode(SpvOpReturn);
        } else {
          // Find an undef for the return value and make sure it gets kept by
          // the pass.
          auto undef_id = Type2Undef(func->type_id());
          auto undef = get_def_use_mgr()->GetDef(undef_id);
          live_insts_.Set(undef->unique_id());
          merge_terminator->SetOpcode(SpvOpReturnValue);
          merge_terminator->SetInOperands({{SPV_OPERAND_TYPE_ID, {undef_id}}});
          get_def_use_mgr()->AnalyzeInstUse(merge_terminator);
        }
        live_insts_.Set(merge_terminator->unique_id());
      }
    } else {
      ++bi;
    }
  }

  return modified;
}

void AggressiveDCEPass::InitializeWorkList(
    Function* func, std::list<BasicBlock*>& structuredOrder) {
  // Add instructions with external side effects to the worklist. Also add
  // branches that are not attached to a structured construct.
  // TODO(s-perron): The handling of branch seems to be adhoc.  This needs to be
  // cleaned up.
  bool call_in_func = false;
  bool func_is_entry_point = false;

  // TODO(s-perron): We need to check if this is actually needed.  In cases
  // where private variable can be treated as if they are function scope, the
  // private-to-local pass should be able to change them to function scope.
  std::vector<Instruction*> private_stores;

  for (auto bi = structuredOrder.begin(); bi != structuredOrder.end(); ++bi) {
    for (auto ii = (*bi)->begin(); ii != (*bi)->end(); ++ii) {
      SpvOp op = ii->opcode();
      switch (op) {
        case SpvOpStore: {
          uint32_t varId;
          (void)GetPtr(&*ii, &varId);
          // Mark stores as live if their variable is not function scope
          // and is not private scope. Remember private stores for possible
          // later inclusion.  We cannot call IsLocalVar at this point because
          // private_like_local_ has not been set yet.
          if (IsVarOfStorage(varId, SpvStorageClassPrivate) ||
              IsVarOfStorage(varId, SpvStorageClassWorkgroup))
            private_stores.push_back(&*ii);
          else if (!IsVarOfStorage(varId, SpvStorageClassFunction))
            AddToWorklist(&*ii);
        } break;
        case SpvOpCopyMemory:
        case SpvOpCopyMemorySized: {
          uint32_t varId;
          (void)GetPtr(ii->GetSingleWordInOperand(kCopyMemoryTargetAddrInIdx),
                       &varId);
          if (IsVarOfStorage(varId, SpvStorageClassPrivate) ||
              IsVarOfStorage(varId, SpvStorageClassWorkgroup))
            private_stores.push_back(&*ii);
          else if (!IsVarOfStorage(varId, SpvStorageClassFunction))
            AddToWorklist(&*ii);
        } break;
        case SpvOpSwitch:
        case SpvOpBranch:
        case SpvOpBranchConditional:
        case SpvOpUnreachable: {
          bool branchRelatedToConstruct =
              (GetMergeInstruction(&*ii) == nullptr &&
               GetHeaderBlock(context()->get_instr_block(&*ii)) == nullptr);
          if (branchRelatedToConstruct) {
            AddToWorklist(&*ii);
          }
        } break;
        case SpvOpLoopMerge:
        case SpvOpSelectionMerge:
          break;
        default: {
          // Function calls, atomics, function params, function returns, etc.
          if (!ii->IsOpcodeSafeToDelete()) {
            AddToWorklist(&*ii);
          }
          // Remember function calls
          if (op == SpvOpFunctionCall) call_in_func = true;
        } break;
      }
    }
  }
  // See if current function is an entry point
  for (auto& ei : get_module()->entry_points()) {
    if (ei.GetSingleWordInOperand(kEntryPointFunctionIdInIdx) ==
        func->result_id()) {
      func_is_entry_point = true;
      break;
    }
  }
  // If the current function is an entry point and has no function calls,
  // we can optimize private variables as locals
  private_like_local_ = func_is_entry_point && !call_in_func;
  // If privates are not like local, add their stores to worklist
  if (!private_like_local_)
    for (auto& ps : private_stores) AddToWorklist(ps);
}

void AggressiveDCEPass::InitializeModuleScopeLiveInstructions() {
  // Keep all execution modes.
  for (auto& exec : get_module()->execution_modes()) {
    AddToWorklist(&exec);
  }
  // Keep all entry points.
  for (auto& entry : get_module()->entry_points()) {
    if (get_module()->version() >= SPV_SPIRV_VERSION_WORD(1, 4) &&
        !preserve_interface_) {
      // In SPIR-V 1.4 and later, entry points must list all global variables
      // used. DCE can still remove non-input/output variables and update the
      // interface list. Mark the entry point as live and inputs and outputs as
      // live, but defer decisions all other interfaces.
      live_insts_.Set(entry.unique_id());
      // The actual function is live always.
      AddToWorklist(
          get_def_use_mgr()->GetDef(entry.GetSingleWordInOperand(1u)));
      for (uint32_t i = 3; i < entry.NumInOperands(); ++i) {
        auto* var = get_def_use_mgr()->GetDef(entry.GetSingleWordInOperand(i));
        auto storage_class = var->GetSingleWordInOperand(0u);
        if (storage_class == SpvStorageClassInput ||
            storage_class == SpvStorageClassOutput) {
          AddToWorklist(var);
        }
      }
    } else {
      AddToWorklist(&entry);
    }
  }
  for (auto& anno : get_module()->annotations()) {
    if (anno.opcode() == SpvOpDecorate) {
      // Keep workgroup size.
      if (anno.GetSingleWordInOperand(1u) == SpvDecorationBuiltIn &&
          anno.GetSingleWordInOperand(2u) == SpvBuiltInWorkgroupSize) {
        AddToWorklist(&anno);
      }

      if (context()->preserve_bindings()) {
        // Keep all bindings.
        if ((anno.GetSingleWordInOperand(1u) == SpvDecorationDescriptorSet) ||
            (anno.GetSingleWordInOperand(1u) == SpvDecorationBinding)) {
          AddToWorklist(&anno);
        }
      }

      if (context()->preserve_spec_constants()) {
        // Keep all specialization constant instructions
        if (anno.GetSingleWordInOperand(1u) == SpvDecorationSpecId) {
          AddToWorklist(&anno);
        }
      }
    }
  }

  // For each DebugInfo GlobalVariable keep all operands except the Variable.
  // Later, if the variable is dead, we will set the operand to DebugInfoNone.
  for (auto& dbg : get_module()->ext_inst_debuginfo()) {
    if (dbg.GetCommonDebugOpcode() != CommonDebugInfoDebugGlobalVariable)
      continue;
    dbg.ForEachInId([this](const uint32_t* iid) {
      Instruction* inInst = get_def_use_mgr()->GetDef(*iid);
      if (inInst->opcode() == SpvOpVariable) return;
      AddToWorklist(inInst);
    });
  }
}

Pass::Status AggressiveDCEPass::ProcessImpl() {
  // Current functionality assumes shader capability
  // TODO(greg-lunarg): Handle additional capabilities
  if (!context()->get_feature_mgr()->HasCapability(SpvCapabilityShader))
    return Status::SuccessWithoutChange;

  // Current functionality assumes relaxed logical addressing (see
  // instruction.h)
  // TODO(greg-lunarg): Handle non-logical addressing
  if (context()->get_feature_mgr()->HasCapability(SpvCapabilityAddresses))
    return Status::SuccessWithoutChange;

  // The variable pointer extension is no longer needed to use the capability,
  // so we have to look for the capability.
  if (context()->get_feature_mgr()->HasCapability(
          SpvCapabilityVariablePointersStorageBuffer))
    return Status::SuccessWithoutChange;

  // If any extensions in the module are not explicitly supported,
  // return unmodified.
  if (!AllExtensionsSupported()) return Status::SuccessWithoutChange;

  // Eliminate Dead functions.
  bool modified = EliminateDeadFunctions();

  InitializeModuleScopeLiveInstructions();

  // Process all entry point functions.
  ProcessFunction pfn = [this](Function* fp) { return AggressiveDCE(fp); };
  modified |= context()->ProcessReachableCallTree(pfn);

  // If the decoration manager is kept live then the context will try to keep it
  // up to date.  ADCE deals with group decorations by changing the operands in
  // |OpGroupDecorate| instruction directly without informing the decoration
  // manager.  This can put it in an invalid state which will cause an error
  // when the context tries to update it.  To avoid this problem invalidate
  // the decoration manager upfront.
  //
  // We kill it at now because it is used when processing the entry point
  // functions.
  context()->InvalidateAnalyses(IRContext::Analysis::kAnalysisDecorations);

  // Process module-level instructions. Now that all live instructions have
  // been marked, it is safe to remove dead global values.
  modified |= ProcessGlobalValues();

  assert((to_kill_.empty() || modified) &&
         "A dead instruction was identified, but no change recorded.");

  // Kill all dead instructions.
  for (auto inst : to_kill_) {
    context()->KillInst(inst);
  }

  // Cleanup all CFG including all unreachable blocks.
  ProcessFunction cleanup = [this](Function* f) { return CFGCleanup(f); };
  modified |= context()->ProcessReachableCallTree(cleanup);

  return modified ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

bool AggressiveDCEPass::EliminateDeadFunctions() {
  // Identify live functions first. Those that are not live
  // are dead.
  std::unordered_set<const Function*> live_function_set;
  ProcessFunction mark_live = [&live_function_set](Function* fp) {
    live_function_set.insert(fp);
    return false;
  };
  context()->ProcessReachableCallTree(mark_live);

  bool modified = false;
  for (auto funcIter = get_module()->begin();
       funcIter != get_module()->end();) {
    if (live_function_set.count(&*funcIter) == 0) {
      modified = true;
      funcIter =
          eliminatedeadfunctionsutil::EliminateFunction(context(), &funcIter);
    } else {
      ++funcIter;
    }
  }

  return modified;
}

bool AggressiveDCEPass::ProcessGlobalValues() {
  // Remove debug and annotation statements referencing dead instructions.
  // This must be done before killing the instructions, otherwise there are
  // dead objects in the def/use database.
  bool modified = false;
  Instruction* instruction = &*get_module()->debug2_begin();
  while (instruction) {
    if (instruction->opcode() != SpvOpName) {
      instruction = instruction->NextNode();
      continue;
    }

    if (IsTargetDead(instruction)) {
      instruction = context()->KillInst(instruction);
      modified = true;
    } else {
      instruction = instruction->NextNode();
    }
  }

  // This code removes all unnecessary decorations safely (see #1174). It also
  // does so in a more efficient manner than deleting them only as the targets
  // are deleted.
  std::vector<Instruction*> annotations;
  for (auto& inst : get_module()->annotations()) annotations.push_back(&inst);
  std::sort(annotations.begin(), annotations.end(), DecorationLess());
  for (auto annotation : annotations) {
    switch (annotation->opcode()) {
      case SpvOpDecorate:
      case SpvOpMemberDecorate:
      case SpvOpDecorateStringGOOGLE:
      case SpvOpMemberDecorateStringGOOGLE:
        if (IsTargetDead(annotation)) {
          context()->KillInst(annotation);
          modified = true;
        }
        break;
      case SpvOpDecorateId:
        if (IsTargetDead(annotation)) {
          context()->KillInst(annotation);
          modified = true;
        } else {
          if (annotation->GetSingleWordInOperand(1) ==
              SpvDecorationHlslCounterBufferGOOGLE) {
            // HlslCounterBuffer will reference an id other than the target.
            // If that id is dead, then the decoration can be removed as well.
            uint32_t counter_buffer_id = annotation->GetSingleWordInOperand(2);
            Instruction* counter_buffer_inst =
                get_def_use_mgr()->GetDef(counter_buffer_id);
            if (IsDead(counter_buffer_inst)) {
              context()->KillInst(annotation);
              modified = true;
            }
          }
        }
        break;
      case SpvOpGroupDecorate: {
        // Go through the targets of this group decorate. Remove each dead
        // target. If all targets are dead, remove this decoration.
        bool dead = true;
        bool removed_operand = false;
        for (uint32_t i = 1; i < annotation->NumOperands();) {
          Instruction* opInst =
              get_def_use_mgr()->GetDef(annotation->GetSingleWordOperand(i));
          if (IsDead(opInst)) {
            // Don't increment |i|.
            annotation->RemoveOperand(i);
            modified = true;
            removed_operand = true;
          } else {
            i++;
            dead = false;
          }
        }
        if (dead) {
          context()->KillInst(annotation);
          modified = true;
        } else if (removed_operand) {
          context()->UpdateDefUse(annotation);
        }
        break;
      }
      case SpvOpGroupMemberDecorate: {
        // Go through the targets of this group member decorate. Remove each
        // dead target (and member index). If all targets are dead, remove this
        // decoration.
        bool dead = true;
        bool removed_operand = false;
        for (uint32_t i = 1; i < annotation->NumOperands();) {
          Instruction* opInst =
              get_def_use_mgr()->GetDef(annotation->GetSingleWordOperand(i));
          if (IsDead(opInst)) {
            // Don't increment |i|.
            annotation->RemoveOperand(i + 1);
            annotation->RemoveOperand(i);
            modified = true;
            removed_operand = true;
          } else {
            i += 2;
            dead = false;
          }
        }
        if (dead) {
          context()->KillInst(annotation);
          modified = true;
        } else if (removed_operand) {
          context()->UpdateDefUse(annotation);
        }
        break;
      }
      case SpvOpDecorationGroup:
        // By the time we hit decoration groups we've checked everything that
        // can target them. So if they have no uses they must be dead.
        if (get_def_use_mgr()->NumUsers(annotation) == 0) {
          context()->KillInst(annotation);
          modified = true;
        }
        break;
      default:
        assert(false);
        break;
    }
  }

  for (auto& dbg : get_module()->ext_inst_debuginfo()) {
    if (!IsDead(&dbg)) continue;
    // Save GlobalVariable if its variable is live, otherwise null out variable
    // index
    if (dbg.GetCommonDebugOpcode() == CommonDebugInfoDebugGlobalVariable) {
      auto var_id = dbg.GetSingleWordOperand(kGlobalVariableVariableIndex);
      Instruction* var_inst = get_def_use_mgr()->GetDef(var_id);
      if (!IsDead(var_inst)) continue;
      context()->ForgetUses(&dbg);
      dbg.SetOperand(
          kGlobalVariableVariableIndex,
          {context()->get_debug_info_mgr()->GetDebugInfoNone()->result_id()});
      context()->AnalyzeUses(&dbg);
      continue;
    }
    to_kill_.push_back(&dbg);
    modified = true;
  }

  // Since ADCE is disabled for non-shaders, we don't check for export linkage
  // attributes here.
  for (auto& val : get_module()->types_values()) {
    if (IsDead(&val)) {
      // Save forwarded pointer if pointer is live since closure does not mark
      // this live as it does not have a result id. This is a little too
      // conservative since it is not known if the structure type that needed
      // it is still live. TODO(greg-lunarg): Only save if needed.
      if (val.opcode() == SpvOpTypeForwardPointer) {
        uint32_t ptr_ty_id = val.GetSingleWordInOperand(0);
        Instruction* ptr_ty_inst = get_def_use_mgr()->GetDef(ptr_ty_id);
        if (!IsDead(ptr_ty_inst)) continue;
      }
      to_kill_.push_back(&val);
      modified = true;
    }
  }

  if (get_module()->version() >= SPV_SPIRV_VERSION_WORD(1, 4) &&
      !preserve_interface_) {
    // Remove the dead interface variables from the entry point interface list.
    for (auto& entry : get_module()->entry_points()) {
      std::vector<Operand> new_operands;
      for (uint32_t i = 0; i < entry.NumInOperands(); ++i) {
        if (i < 3) {
          // Execution model, function id and name are always valid.
          new_operands.push_back(entry.GetInOperand(i));
        } else {
          auto* var =
              get_def_use_mgr()->GetDef(entry.GetSingleWordInOperand(i));
          if (!IsDead(var)) {
            new_operands.push_back(entry.GetInOperand(i));
          }
        }
      }
      if (new_operands.size() != entry.NumInOperands()) {
        entry.SetInOperands(std::move(new_operands));
        get_def_use_mgr()->UpdateDefUse(&entry);
      }
    }
  }

  return modified;
}

Pass::Status AggressiveDCEPass::Process() {
  // Initialize extensions allowlist
  InitExtensions();
  return ProcessImpl();
}

void AggressiveDCEPass::InitExtensions() {
  extensions_allowlist_.clear();
  extensions_allowlist_.insert({
      "SPV_AMD_shader_explicit_vertex_parameter",
      "SPV_AMD_shader_trinary_minmax",
      "SPV_AMD_gcn_shader",
      "SPV_KHR_shader_ballot",
      "SPV_AMD_shader_ballot",
      "SPV_AMD_gpu_shader_half_float",
      "SPV_KHR_shader_draw_parameters",
      "SPV_KHR_subgroup_vote",
      "SPV_KHR_8bit_storage",
      "SPV_KHR_16bit_storage",
      "SPV_KHR_device_group",
      "SPV_KHR_multiview",
      "SPV_NVX_multiview_per_view_attributes",
      "SPV_NV_viewport_array2",
      "SPV_NV_stereo_view_rendering",
      "SPV_NV_sample_mask_override_coverage",
      "SPV_NV_geometry_shader_passthrough",
      "SPV_AMD_texture_gather_bias_lod",
      "SPV_KHR_storage_buffer_storage_class",
      // SPV_KHR_variable_pointers
      //   Currently do not support extended pointer expressions
      "SPV_AMD_gpu_shader_int16",
      "SPV_KHR_post_depth_coverage",
      "SPV_KHR_shader_atomic_counter_ops",
      "SPV_EXT_shader_stencil_export",
      "SPV_EXT_shader_viewport_index_layer",
      "SPV_AMD_shader_image_load_store_lod",
      "SPV_AMD_shader_fragment_mask",
      "SPV_EXT_fragment_fully_covered",
      "SPV_AMD_gpu_shader_half_float_fetch",
      "SPV_GOOGLE_decorate_string",
      "SPV_GOOGLE_hlsl_functionality1",
      "SPV_GOOGLE_user_type",
      "SPV_NV_shader_subgroup_partitioned",
      "SPV_EXT_demote_to_helper_invocation",
      "SPV_EXT_descriptor_indexing",
      "SPV_NV_fragment_shader_barycentric",
      "SPV_NV_compute_shader_derivatives",
      "SPV_NV_shader_image_footprint",
      "SPV_NV_shading_rate",
      "SPV_NV_mesh_shader",
      "SPV_NV_ray_tracing",
      "SPV_KHR_ray_tracing",
      "SPV_KHR_ray_query",
      "SPV_EXT_fragment_invocation_density",
      "SPV_EXT_physical_storage_buffer",
      "SPV_KHR_terminate_invocation",
      "SPV_KHR_shader_clock",
      "SPV_KHR_vulkan_memory_model",
      "SPV_KHR_subgroup_uniform_control_flow",
      "SPV_KHR_integer_dot_product",
      "SPV_EXT_shader_image_int64",
      "SPV_KHR_non_semantic_info",
  });
}

Instruction* AggressiveDCEPass::GetHeaderBranch(BasicBlock* blk) {
  if (blk == nullptr) {
    return nullptr;
  }
  BasicBlock* header_block = GetHeaderBlock(blk);
  if (header_block == nullptr) {
    return nullptr;
  }
  return header_block->terminator();
}

BasicBlock* AggressiveDCEPass::GetHeaderBlock(BasicBlock* blk) const {
  if (blk == nullptr) {
    return nullptr;
  }

  BasicBlock* header_block = nullptr;
  if (blk->IsLoopHeader()) {
    header_block = blk;
  } else {
    uint32_t header =
        context()->GetStructuredCFGAnalysis()->ContainingConstruct(blk->id());
    header_block = context()->get_instr_block(header);
  }
  return header_block;
}

Instruction* AggressiveDCEPass::GetMergeInstruction(Instruction* inst) {
  BasicBlock* bb = context()->get_instr_block(inst);
  if (bb == nullptr) {
    return nullptr;
  }
  return bb->GetMergeInst();
}

Instruction* AggressiveDCEPass::GetBranchForNextHeader(BasicBlock* blk) {
  if (blk == nullptr) {
    return nullptr;
  }

  if (blk->IsLoopHeader()) {
    uint32_t header =
        context()->GetStructuredCFGAnalysis()->ContainingConstruct(blk->id());
    blk = context()->get_instr_block(header);
  }
  return GetHeaderBranch(blk);
}

void AggressiveDCEPass::MarkFunctionParameterAsLive(const Function* func) {
  func->ForEachParam(
      [this](const Instruction* param) {
        AddToWorklist(const_cast<Instruction*>(param));
      },
      false);
}

bool AggressiveDCEPass::BlockIsInConstruct(BasicBlock* header_block,
                                           BasicBlock* bb) {
  if (bb == nullptr || header_block == nullptr) {
    return false;
  }

  uint32_t current_header = bb->id();
  while (current_header != 0) {
    if (current_header == header_block->id()) return true;
    current_header = context()->GetStructuredCFGAnalysis()->ContainingConstruct(
        current_header);
  }
  return false;
}

}  // namespace opt
}  // namespace spvtools

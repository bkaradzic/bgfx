// Copyright (c) 2020 Google LLC
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

#include "source/opt/debug_info_manager.h"

#include <cassert>

#include "source/opt/ir_context.h"

// Constants for OpenCL.DebugInfo.100 extension instructions.

static const uint32_t kOpLineOperandLineIndex = 1;
static const uint32_t kLineOperandIndexDebugFunction = 7;
static const uint32_t kLineOperandIndexDebugLexicalBlock = 5;
static const uint32_t kDebugFunctionOperandFunctionIndex = 13;
static const uint32_t kDebugFunctionOperandParentIndex = 9;
static const uint32_t kDebugTypeCompositeOperandParentIndex = 9;
static const uint32_t kDebugLexicalBlockOperandParentIndex = 7;
static const uint32_t kDebugInlinedAtOperandInlinedIndex = 6;
static const uint32_t kDebugExpressOperandOperationIndex = 4;
static const uint32_t kDebugDeclareOperandLocalVariableIndex = 4;
static const uint32_t kDebugDeclareOperandVariableIndex = 5;
static const uint32_t kDebugValueOperandLocalVariableIndex = 4;
static const uint32_t kDebugValueOperandExpressionIndex = 6;
static const uint32_t kDebugOperationOperandOperationIndex = 4;
static const uint32_t kOpVariableOperandStorageClassIndex = 2;
static const uint32_t kDebugLocalVariableOperandParentIndex = 9;

namespace spvtools {
namespace opt {
namespace analysis {
namespace {

void SetInlinedOperand(Instruction* dbg_inlined_at, uint32_t inlined_operand) {
  assert(dbg_inlined_at);
  assert(dbg_inlined_at->GetOpenCL100DebugOpcode() ==
         OpenCLDebugInfo100DebugInlinedAt);
  if (dbg_inlined_at->NumOperands() <= kDebugInlinedAtOperandInlinedIndex) {
    dbg_inlined_at->AddOperand(
        {spv_operand_type_t::SPV_OPERAND_TYPE_ID, {inlined_operand}});
  } else {
    dbg_inlined_at->SetOperand(kDebugInlinedAtOperandInlinedIndex,
                               {inlined_operand});
  }
}

uint32_t GetInlinedOperand(Instruction* dbg_inlined_at) {
  assert(dbg_inlined_at);
  assert(dbg_inlined_at->GetOpenCL100DebugOpcode() ==
         OpenCLDebugInfo100DebugInlinedAt);
  if (dbg_inlined_at->NumOperands() <= kDebugInlinedAtOperandInlinedIndex)
    return kNoInlinedAt;
  return dbg_inlined_at->GetSingleWordOperand(
      kDebugInlinedAtOperandInlinedIndex);
}

bool IsEmptyDebugExpression(Instruction* instr) {
  return instr->GetOpenCL100DebugOpcode() ==
             OpenCLDebugInfo100DebugExpression &&
         instr->NumOperands() == kDebugExpressOperandOperationIndex;
}

}  // namespace

DebugInfoManager::DebugInfoManager(IRContext* c) : context_(c) {
  AnalyzeDebugInsts(*c->module());
}

Instruction* DebugInfoManager::GetDbgInst(uint32_t id) {
  auto dbg_inst_it = id_to_dbg_inst_.find(id);
  return dbg_inst_it == id_to_dbg_inst_.end() ? nullptr : dbg_inst_it->second;
}

void DebugInfoManager::RegisterDbgInst(Instruction* inst) {
  assert(
      inst->NumInOperands() != 0 &&
      context()->get_feature_mgr()->GetExtInstImportId_OpenCL100DebugInfo() ==
          inst->GetInOperand(0).words[0] &&
      "Given instruction is not a debug instruction");
  id_to_dbg_inst_[inst->result_id()] = inst;
}

void DebugInfoManager::RegisterDbgFunction(Instruction* inst) {
  assert(inst->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugFunction &&
         "inst is not a DebugFunction");
  auto fn_id = inst->GetSingleWordOperand(kDebugFunctionOperandFunctionIndex);
  assert(
      fn_id_to_dbg_fn_.find(fn_id) == fn_id_to_dbg_fn_.end() &&
      "Register DebugFunction for a function that already has DebugFunction");
  fn_id_to_dbg_fn_[fn_id] = inst;
}

void DebugInfoManager::RegisterDbgDeclare(uint32_t var_id,
                                          Instruction* dbg_declare) {
  assert(dbg_declare->GetOpenCL100DebugOpcode() ==
             OpenCLDebugInfo100DebugDeclare ||
         dbg_declare->GetOpenCL100DebugOpcode() ==
             OpenCLDebugInfo100DebugValue);
  auto dbg_decl_itr = var_id_to_dbg_decl_.find(var_id);
  if (dbg_decl_itr == var_id_to_dbg_decl_.end()) {
    var_id_to_dbg_decl_[var_id] = {dbg_declare};
  } else {
    dbg_decl_itr->second.insert(dbg_declare);
  }
}

uint32_t DebugInfoManager::CreateDebugInlinedAt(const Instruction* line,
                                                const DebugScope& scope) {
  if (context()->get_feature_mgr()->GetExtInstImportId_OpenCL100DebugInfo() ==
      0)
    return kNoInlinedAt;

  uint32_t line_number = 0;
  if (line == nullptr) {
    auto* lexical_scope_inst = GetDbgInst(scope.GetLexicalScope());
    if (lexical_scope_inst == nullptr) return kNoInlinedAt;
    OpenCLDebugInfo100Instructions debug_opcode =
        lexical_scope_inst->GetOpenCL100DebugOpcode();
    switch (debug_opcode) {
      case OpenCLDebugInfo100DebugFunction:
        line_number = lexical_scope_inst->GetSingleWordOperand(
            kLineOperandIndexDebugFunction);
        break;
      case OpenCLDebugInfo100DebugLexicalBlock:
        line_number = lexical_scope_inst->GetSingleWordOperand(
            kLineOperandIndexDebugLexicalBlock);
        break;
      case OpenCLDebugInfo100DebugTypeComposite:
      case OpenCLDebugInfo100DebugCompilationUnit:
        assert(false &&
               "DebugTypeComposite and DebugCompilationUnit are lexical "
               "scopes, but we inline functions into a function or a block "
               "of a function, not into a struct/class or a global scope.");
        break;
      default:
        assert(false &&
               "Unreachable. a debug extension instruction for a "
               "lexical scope must be DebugFunction, DebugTypeComposite, "
               "DebugLexicalBlock, or DebugCompilationUnit.");
        break;
    }
  } else {
    line_number = line->GetSingleWordOperand(kOpLineOperandLineIndex);
  }

  uint32_t result_id = context()->TakeNextId();
  std::unique_ptr<Instruction> inlined_at(new Instruction(
      context(), SpvOpExtInst, context()->get_type_mgr()->GetVoidTypeId(),
      result_id,
      {
          {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
           {context()
                ->get_feature_mgr()
                ->GetExtInstImportId_OpenCL100DebugInfo()}},
          {spv_operand_type_t::SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER,
           {static_cast<uint32_t>(OpenCLDebugInfo100DebugInlinedAt)}},
          {spv_operand_type_t::SPV_OPERAND_TYPE_LITERAL_INTEGER, {line_number}},
          {spv_operand_type_t::SPV_OPERAND_TYPE_ID, {scope.GetLexicalScope()}},
      }));
  // |scope| already has DebugInlinedAt. We put the existing DebugInlinedAt
  // into the Inlined operand of this new DebugInlinedAt.
  if (scope.GetInlinedAt() != kNoInlinedAt) {
    inlined_at->AddOperand(
        {spv_operand_type_t::SPV_OPERAND_TYPE_ID, {scope.GetInlinedAt()}});
  }
  RegisterDbgInst(inlined_at.get());
  if (context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse))
    context()->get_def_use_mgr()->AnalyzeInstDefUse(inlined_at.get());
  context()->module()->AddExtInstDebugInfo(std::move(inlined_at));
  return result_id;
}

DebugScope DebugInfoManager::BuildDebugScope(
    const DebugScope& callee_instr_scope,
    DebugInlinedAtContext* inlined_at_ctx) {
  return DebugScope(callee_instr_scope.GetLexicalScope(),
                    BuildDebugInlinedAtChain(callee_instr_scope.GetInlinedAt(),
                                             inlined_at_ctx));
}

uint32_t DebugInfoManager::BuildDebugInlinedAtChain(
    uint32_t callee_inlined_at, DebugInlinedAtContext* inlined_at_ctx) {
  if (inlined_at_ctx->GetScopeOfCallInstruction().GetLexicalScope() ==
      kNoDebugScope)
    return kNoInlinedAt;

  // Reuse the already generated DebugInlinedAt chain if exists.
  uint32_t already_generated_chain_head_id =
      inlined_at_ctx->GetDebugInlinedAtChain(callee_inlined_at);
  if (already_generated_chain_head_id != kNoInlinedAt) {
    return already_generated_chain_head_id;
  }

  const uint32_t new_dbg_inlined_at_id =
      CreateDebugInlinedAt(inlined_at_ctx->GetLineOfCallInstruction(),
                           inlined_at_ctx->GetScopeOfCallInstruction());
  if (new_dbg_inlined_at_id == kNoInlinedAt) return kNoInlinedAt;

  if (callee_inlined_at == kNoInlinedAt) {
    inlined_at_ctx->SetDebugInlinedAtChain(kNoInlinedAt, new_dbg_inlined_at_id);
    return new_dbg_inlined_at_id;
  }

  uint32_t chain_head_id = kNoInlinedAt;
  uint32_t chain_iter_id = callee_inlined_at;
  Instruction* last_inlined_at_in_chain = nullptr;
  do {
    Instruction* new_inlined_at_in_chain = CloneDebugInlinedAt(
        chain_iter_id, /* insert_before */ last_inlined_at_in_chain);
    assert(new_inlined_at_in_chain != nullptr);

    // Set DebugInlinedAt of the new scope as the head of the chain.
    if (chain_head_id == kNoInlinedAt)
      chain_head_id = new_inlined_at_in_chain->result_id();

    // Previous DebugInlinedAt of the chain must point to the new
    // DebugInlinedAt as its Inlined operand to build a recursive
    // chain.
    if (last_inlined_at_in_chain != nullptr) {
      SetInlinedOperand(last_inlined_at_in_chain,
                        new_inlined_at_in_chain->result_id());
    }
    last_inlined_at_in_chain = new_inlined_at_in_chain;

    chain_iter_id = GetInlinedOperand(new_inlined_at_in_chain);
  } while (chain_iter_id != kNoInlinedAt);

  // Put |new_dbg_inlined_at_id| into the end of the chain.
  SetInlinedOperand(last_inlined_at_in_chain, new_dbg_inlined_at_id);

  // Keep the new chain information that will be reused it.
  inlined_at_ctx->SetDebugInlinedAtChain(callee_inlined_at, chain_head_id);
  return chain_head_id;
}

Instruction* DebugInfoManager::GetDebugInfoNone() {
  if (debug_info_none_inst_ != nullptr) return debug_info_none_inst_;

  uint32_t result_id = context()->TakeNextId();
  std::unique_ptr<Instruction> dbg_info_none_inst(new Instruction(
      context(), SpvOpExtInst, context()->get_type_mgr()->GetVoidTypeId(),
      result_id,
      {
          {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
           {context()
                ->get_feature_mgr()
                ->GetExtInstImportId_OpenCL100DebugInfo()}},
          {spv_operand_type_t::SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER,
           {static_cast<uint32_t>(OpenCLDebugInfo100DebugInfoNone)}},
      }));

  // Add to the front of |ext_inst_debuginfo_|.
  debug_info_none_inst_ =
      context()->module()->ext_inst_debuginfo_begin()->InsertBefore(
          std::move(dbg_info_none_inst));

  RegisterDbgInst(debug_info_none_inst_);
  if (context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse))
    context()->get_def_use_mgr()->AnalyzeInstDefUse(debug_info_none_inst_);
  return debug_info_none_inst_;
}

Instruction* DebugInfoManager::GetEmptyDebugExpression() {
  if (empty_debug_expr_inst_ != nullptr) return empty_debug_expr_inst_;

  uint32_t result_id = context()->TakeNextId();
  std::unique_ptr<Instruction> empty_debug_expr(new Instruction(
      context(), SpvOpExtInst, context()->get_type_mgr()->GetVoidTypeId(),
      result_id,
      {
          {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
           {context()
                ->get_feature_mgr()
                ->GetExtInstImportId_OpenCL100DebugInfo()}},
          {spv_operand_type_t::SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER,
           {static_cast<uint32_t>(OpenCLDebugInfo100DebugExpression)}},
      }));

  // Add to the front of |ext_inst_debuginfo_|.
  empty_debug_expr_inst_ =
      context()->module()->ext_inst_debuginfo_begin()->InsertBefore(
          std::move(empty_debug_expr));

  RegisterDbgInst(empty_debug_expr_inst_);
  if (context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse))
    context()->get_def_use_mgr()->AnalyzeInstDefUse(empty_debug_expr_inst_);
  return empty_debug_expr_inst_;
}

Instruction* DebugInfoManager::GetDebugInlinedAt(uint32_t dbg_inlined_at_id) {
  auto* inlined_at = GetDbgInst(dbg_inlined_at_id);
  if (inlined_at == nullptr) return nullptr;
  if (inlined_at->GetOpenCL100DebugOpcode() !=
      OpenCLDebugInfo100DebugInlinedAt) {
    return nullptr;
  }
  return inlined_at;
}

Instruction* DebugInfoManager::CloneDebugInlinedAt(uint32_t clone_inlined_at_id,
                                                   Instruction* insert_before) {
  auto* inlined_at = GetDebugInlinedAt(clone_inlined_at_id);
  if (inlined_at == nullptr) return nullptr;
  std::unique_ptr<Instruction> new_inlined_at(inlined_at->Clone(context()));
  new_inlined_at->SetResultId(context()->TakeNextId());
  RegisterDbgInst(new_inlined_at.get());
  if (context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse))
    context()->get_def_use_mgr()->AnalyzeInstDefUse(new_inlined_at.get());
  if (insert_before != nullptr)
    return insert_before->InsertBefore(std::move(new_inlined_at));
  return context()->module()->ext_inst_debuginfo_end()->InsertBefore(
      std::move(new_inlined_at));
}

uint32_t DebugInfoManager::GetParentScope(uint32_t child_scope) {
  auto dbg_scope_itr = id_to_dbg_inst_.find(child_scope);
  assert(dbg_scope_itr != id_to_dbg_inst_.end());
  OpenCLDebugInfo100Instructions debug_opcode =
      dbg_scope_itr->second->GetOpenCL100DebugOpcode();
  uint32_t parent_scope = kNoDebugScope;
  switch (debug_opcode) {
    case OpenCLDebugInfo100DebugFunction:
      parent_scope = dbg_scope_itr->second->GetSingleWordOperand(
          kDebugFunctionOperandParentIndex);
      break;
    case OpenCLDebugInfo100DebugLexicalBlock:
      parent_scope = dbg_scope_itr->second->GetSingleWordOperand(
          kDebugLexicalBlockOperandParentIndex);
      break;
    case OpenCLDebugInfo100DebugTypeComposite:
      parent_scope = dbg_scope_itr->second->GetSingleWordOperand(
          kDebugTypeCompositeOperandParentIndex);
      break;
    case OpenCLDebugInfo100DebugCompilationUnit:
      // DebugCompilationUnit does not have a parent scope.
      break;
    default:
      assert(false &&
             "Unreachable. A debug scope instruction must be "
             "DebugFunction, DebugTypeComposite, DebugLexicalBlock, "
             "or DebugCompilationUnit.");
      break;
  }
  return parent_scope;
}

bool DebugInfoManager::IsAncestorOfScope(uint32_t scope, uint32_t ancestor) {
  uint32_t ancestor_scope_itr = scope;
  while (ancestor_scope_itr != kNoDebugScope) {
    if (ancestor == ancestor_scope_itr) return true;
    ancestor_scope_itr = GetParentScope(ancestor_scope_itr);
  }
  return false;
}

bool DebugInfoManager::IsDeclareVisibleToInstr(Instruction* dbg_declare,
                                               uint32_t instr_scope_id) {
  if (instr_scope_id == kNoDebugScope) return false;

  uint32_t dbg_local_var_id =
      dbg_declare->GetSingleWordOperand(kDebugDeclareOperandLocalVariableIndex);
  auto dbg_local_var_itr = id_to_dbg_inst_.find(dbg_local_var_id);
  assert(dbg_local_var_itr != id_to_dbg_inst_.end());
  uint32_t decl_scope_id = dbg_local_var_itr->second->GetSingleWordOperand(
      kDebugLocalVariableOperandParentIndex);

  // If the scope of DebugDeclare is an ancestor scope of the instruction's
  // scope, the local variable is visible to the instruction.
  return IsAncestorOfScope(instr_scope_id, decl_scope_id);
}

void DebugInfoManager::AddDebugValue(Instruction* scope_and_line,
                                     uint32_t variable_id, uint32_t value_id,
                                     Instruction* insert_pos) {
  auto dbg_decl_itr = var_id_to_dbg_decl_.find(variable_id);
  if (dbg_decl_itr == var_id_to_dbg_decl_.end()) return;

  uint32_t instr_scope_id = scope_and_line->GetDebugScope().GetLexicalScope();
  for (auto* dbg_decl_or_val : dbg_decl_itr->second) {
    if (!IsDeclareVisibleToInstr(dbg_decl_or_val, instr_scope_id)) continue;

    uint32_t result_id = context()->TakeNextId();
    std::unique_ptr<Instruction> new_dbg_value(new Instruction(
        context(), SpvOpExtInst, context()->get_type_mgr()->GetVoidTypeId(),
        result_id,
        {
            {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
             {context()
                  ->get_feature_mgr()
                  ->GetExtInstImportId_OpenCL100DebugInfo()}},
            {spv_operand_type_t::SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER,
             {static_cast<uint32_t>(OpenCLDebugInfo100DebugValue)}},
            {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
             {dbg_decl_or_val->GetSingleWordOperand(
                 kDebugValueOperandLocalVariableIndex)}},
            {spv_operand_type_t::SPV_OPERAND_TYPE_ID, {value_id}},
            {spv_operand_type_t::SPV_OPERAND_TYPE_ID,
             {GetEmptyDebugExpression()->result_id()}},
        }));

    if (dbg_decl_or_val->NumOperands() >
        kDebugValueOperandExpressionIndex + 1) {
      assert(dbg_decl_or_val->GetOpenCL100DebugOpcode() ==
             OpenCLDebugInfo100DebugValue);
      for (uint32_t i = kDebugValueOperandExpressionIndex + 1;
           i < dbg_decl_or_val->NumOperands(); ++i) {
        new_dbg_value->AddOperand({spv_operand_type_t::SPV_OPERAND_TYPE_ID,
                                   {dbg_decl_or_val->GetSingleWordOperand(i)}});
      }
    }

    // Avoid inserting the new DebugValue between OpPhi or OpVariable
    // instructions.
    Instruction* insert_before = insert_pos->NextNode();
    while (insert_before->opcode() == SpvOpPhi ||
           insert_before->opcode() == SpvOpVariable) {
      insert_before = insert_before->NextNode();
    }

    Instruction* added_dbg_value =
        insert_before->InsertBefore(std::move(new_dbg_value));
    added_dbg_value->UpdateDebugInfo(scope_and_line);
    AnalyzeDebugInst(added_dbg_value);
    if (context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse))
      context()->get_def_use_mgr()->AnalyzeInstDefUse(added_dbg_value);
  }
}

uint32_t DebugInfoManager::GetVariableIdOfDebugValueUsedForDeclare(
    Instruction* inst) {
  if (inst->GetOpenCL100DebugOpcode() != OpenCLDebugInfo100DebugValue) return 0;

  auto* expr =
      GetDbgInst(inst->GetSingleWordOperand(kDebugValueOperandExpressionIndex));
  if (expr == nullptr) return 0;
  if (expr->NumOperands() != kDebugExpressOperandOperationIndex + 1) return 0;

  auto* operation = GetDbgInst(
      expr->GetSingleWordOperand(kDebugExpressOperandOperationIndex));
  if (operation == nullptr) return 0;
  if (operation->GetSingleWordOperand(kDebugOperationOperandOperationIndex) !=
      OpenCLDebugInfo100Deref) {
    return 0;
  }

  uint32_t var_id =
      inst->GetSingleWordOperand(kDebugDeclareOperandVariableIndex);
  if (!context()->AreAnalysesValid(IRContext::Analysis::kAnalysisDefUse)) {
    assert(false &&
           "Checking a DebugValue can be used for declare needs DefUseManager");
    return 0;
  }

  auto* var = context()->get_def_use_mgr()->GetDef(var_id);
  if (var->opcode() == SpvOpVariable &&
      SpvStorageClass(var->GetSingleWordOperand(
          kOpVariableOperandStorageClassIndex)) == SpvStorageClassFunction) {
    return var_id;
  }
  return 0;
}

void DebugInfoManager::AnalyzeDebugInst(Instruction* dbg_inst) {
  if (dbg_inst->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100InstructionsMax)
    return;

  RegisterDbgInst(dbg_inst);

  if (dbg_inst->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugFunction) {
    assert(GetDebugFunction(dbg_inst->GetSingleWordOperand(
               kDebugFunctionOperandFunctionIndex)) == nullptr &&
           "Two DebugFunction instruction exists for a single OpFunction.");
    RegisterDbgFunction(dbg_inst);
  }

  if (debug_info_none_inst_ == nullptr &&
      dbg_inst->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugInfoNone) {
    debug_info_none_inst_ = dbg_inst;
  }

  if (empty_debug_expr_inst_ == nullptr && IsEmptyDebugExpression(dbg_inst)) {
    empty_debug_expr_inst_ = dbg_inst;
  }

  if (dbg_inst->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugDeclare) {
    uint32_t var_id =
        dbg_inst->GetSingleWordOperand(kDebugDeclareOperandVariableIndex);
    RegisterDbgDeclare(var_id, dbg_inst);
  }

  if (uint32_t var_id = GetVariableIdOfDebugValueUsedForDeclare(dbg_inst)) {
    RegisterDbgDeclare(var_id, dbg_inst);
  }
}

void DebugInfoManager::AnalyzeDebugInsts(Module& module) {
  debug_info_none_inst_ = nullptr;
  empty_debug_expr_inst_ = nullptr;
  module.ForEachInst([this](Instruction* cpi) { AnalyzeDebugInst(cpi); });

  // Move |empty_debug_expr_inst_| to the beginning of the debug instruction
  // list.
  if (empty_debug_expr_inst_ != nullptr &&
      empty_debug_expr_inst_->PreviousNode() != nullptr &&
      empty_debug_expr_inst_->PreviousNode()->GetOpenCL100DebugOpcode() !=
          OpenCLDebugInfo100InstructionsMax) {
    empty_debug_expr_inst_->InsertBefore(
        &*context()->module()->ext_inst_debuginfo_begin());
  }

  // Move |debug_info_none_inst_| to the beginning of the debug instruction
  // list.
  if (debug_info_none_inst_ != nullptr &&
      debug_info_none_inst_->PreviousNode() != nullptr &&
      debug_info_none_inst_->PreviousNode()->GetOpenCL100DebugOpcode() !=
          OpenCLDebugInfo100InstructionsMax) {
    debug_info_none_inst_->InsertBefore(
        &*context()->module()->ext_inst_debuginfo_begin());
  }
}

void DebugInfoManager::ClearDebugInfo(Instruction* instr) {
  if (instr == nullptr ||
      instr->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100InstructionsMax) {
    return;
  }

  id_to_dbg_inst_.erase(instr->result_id());

  if (instr->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugFunction) {
    auto fn_id =
        instr->GetSingleWordOperand(kDebugFunctionOperandFunctionIndex);
    fn_id_to_dbg_fn_.erase(fn_id);
  }

  if (instr->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugDeclare ||
      instr->GetOpenCL100DebugOpcode() == OpenCLDebugInfo100DebugValue) {
    auto var_or_value_id =
        instr->GetSingleWordOperand(kDebugDeclareOperandVariableIndex);
    auto dbg_decl_itr = var_id_to_dbg_decl_.find(var_or_value_id);
    if (dbg_decl_itr != var_id_to_dbg_decl_.end()) {
      dbg_decl_itr->second.erase(instr);
    }
  }

  if (debug_info_none_inst_ == instr) {
    debug_info_none_inst_ = nullptr;
    for (auto dbg_instr_itr = context()->module()->ext_inst_debuginfo_begin();
         dbg_instr_itr != context()->module()->ext_inst_debuginfo_end();
         ++dbg_instr_itr) {
      if (instr != &*dbg_instr_itr &&
          dbg_instr_itr->GetOpenCL100DebugOpcode() ==
              OpenCLDebugInfo100DebugInfoNone) {
        debug_info_none_inst_ = &*dbg_instr_itr;
      }
    }
  }

  if (empty_debug_expr_inst_ == instr) {
    empty_debug_expr_inst_ = nullptr;
    for (auto dbg_instr_itr = context()->module()->ext_inst_debuginfo_begin();
         dbg_instr_itr != context()->module()->ext_inst_debuginfo_end();
         ++dbg_instr_itr) {
      if (instr != &*dbg_instr_itr && IsEmptyDebugExpression(&*dbg_instr_itr)) {
        empty_debug_expr_inst_ = &*dbg_instr_itr;
      }
    }
  }
}

}  // namespace analysis
}  // namespace opt
}  // namespace spvtools

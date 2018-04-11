// Copyright (c) 2017 Google Inc.
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

#include "scalar_replacement_pass.h"

#include "enum_string_mapping.h"
#include "extensions.h"
#include "make_unique.h"
#include "reflect.h"
#include "types.h"

#include <queue>
#include <tuple>

namespace spvtools {
namespace opt {

// Heuristic aggregate element limit.
const uint32_t MAX_NUM_ELEMENTS = 100u;

Pass::Status ScalarReplacementPass::Process(ir::IRContext* c) {
  InitializeProcessing(c);

  Status status = Status::SuccessWithoutChange;
  for (auto& f : *get_module()) {
    Status functionStatus = ProcessFunction(&f);
    if (functionStatus == Status::Failure)
      return functionStatus;
    else if (functionStatus == Status::SuccessWithChange)
      status = functionStatus;
  }

  return status;
}

Pass::Status ScalarReplacementPass::ProcessFunction(ir::Function* function) {
  std::queue<ir::Instruction*> worklist;
  ir::BasicBlock& entry = *function->begin();
  for (auto iter = entry.begin(); iter != entry.end(); ++iter) {
    // Function storage class OpVariables must appear as the first instructions
    // of the entry block.
    if (iter->opcode() != SpvOpVariable) break;

    ir::Instruction* varInst = &*iter;
    if (CanReplaceVariable(varInst)) {
      worklist.push(varInst);
    }
  }

  Status status = Status::SuccessWithoutChange;
  while (!worklist.empty()) {
    ir::Instruction* varInst = worklist.front();
    worklist.pop();

    if (!ReplaceVariable(varInst, &worklist))
      return Status::Failure;
    else
      status = Status::SuccessWithChange;
  }

  return status;
}

bool ScalarReplacementPass::ReplaceVariable(
    ir::Instruction* inst, std::queue<ir::Instruction*>* worklist) {
  std::vector<ir::Instruction*> replacements;
  CreateReplacementVariables(inst, &replacements);

  std::vector<ir::Instruction*> dead;
  dead.push_back(inst);
  if (!get_def_use_mgr()->WhileEachUser(
          inst, [this, &replacements, &dead](ir::Instruction* user) {
            if (!ir::IsAnnotationInst(user->opcode())) {
              switch (user->opcode()) {
                case SpvOpLoad:
                  ReplaceWholeLoad(user, replacements);
                  dead.push_back(user);
                  break;
                case SpvOpStore:
                  ReplaceWholeStore(user, replacements);
                  dead.push_back(user);
                  break;
                case SpvOpAccessChain:
                case SpvOpInBoundsAccessChain:
                  if (!ReplaceAccessChain(user, replacements)) return false;
                  dead.push_back(user);
                  break;
                case SpvOpName:
                case SpvOpMemberName:
                  break;
                default:
                  assert(false && "Unexpected opcode");
                  break;
              }
            }
            return true;
          }))
    return false;

  // Clean up some dead code.
  while (!dead.empty()) {
    ir::Instruction* toKill = dead.back();
    dead.pop_back();

    context()->KillInst(toKill);
  }

  // Attempt to further scalarize.
  for (auto var : replacements) {
    if (get_def_use_mgr()->NumUsers(var) == 0) {
      context()->KillInst(var);
    } else if (CanReplaceVariable(var)) {
      worklist->push(var);
    }
  }

  return true;
}

void ScalarReplacementPass::ReplaceWholeLoad(
    ir::Instruction* load, const std::vector<ir::Instruction*>& replacements) {
  // Replaces the load of the entire composite with a load from each replacement
  // variable followed by a composite construction.
  ir::BasicBlock* block = context()->get_instr_block(load);
  std::vector<ir::Instruction*> loads;
  loads.reserve(replacements.size());
  ir::BasicBlock::iterator where(load);
  for (auto var : replacements) {
    // Create a load of each replacement variable.
    ir::Instruction* type = GetStorageType(var);
    uint32_t loadId = TakeNextId();
    std::unique_ptr<ir::Instruction> newLoad(
        new ir::Instruction(context(), SpvOpLoad, type->result_id(), loadId,
                            std::initializer_list<ir::Operand>{
                                {SPV_OPERAND_TYPE_ID, {var->result_id()}}}));
    // Copy memory access attributes which start at index 1. Index 0 is the
    // pointer to load.
    for (uint32_t i = 1; i < load->NumInOperands(); ++i) {
      ir::Operand copy(load->GetInOperand(i));
      newLoad->AddOperand(std::move(copy));
    }
    where = where.InsertBefore(std::move(newLoad));
    get_def_use_mgr()->AnalyzeInstDefUse(&*where);
    context()->set_instr_block(&*where, block);
    loads.push_back(&*where);
  }

  // Construct a new composite.
  uint32_t compositeId = TakeNextId();
  where = load;
  std::unique_ptr<ir::Instruction> compositeConstruct(new ir::Instruction(
      context(), SpvOpCompositeConstruct, load->type_id(), compositeId, {}));
  for (auto l : loads) {
    ir::Operand op(SPV_OPERAND_TYPE_ID,
                   std::initializer_list<uint32_t>{l->result_id()});
    compositeConstruct->AddOperand(std::move(op));
  }
  where = where.InsertBefore(std::move(compositeConstruct));
  get_def_use_mgr()->AnalyzeInstDefUse(&*where);
  context()->set_instr_block(&*where, block);
  context()->ReplaceAllUsesWith(load->result_id(), compositeId);
}

void ScalarReplacementPass::ReplaceWholeStore(
    ir::Instruction* store, const std::vector<ir::Instruction*>& replacements) {
  // Replaces a store to the whole composite with a series of extract and stores
  // to each element.
  uint32_t storeInput = store->GetSingleWordInOperand(1u);
  ir::BasicBlock* block = context()->get_instr_block(store);
  ir::BasicBlock::iterator where(store);
  uint32_t elementIndex = 0;
  for (auto var : replacements) {
    // Create the extract.
    ir::Instruction* type = GetStorageType(var);
    uint32_t extractId = TakeNextId();
    std::unique_ptr<ir::Instruction> extract(new ir::Instruction(
        context(), SpvOpCompositeExtract, type->result_id(), extractId,
        std::initializer_list<ir::Operand>{
            {SPV_OPERAND_TYPE_ID, {storeInput}},
            {SPV_OPERAND_TYPE_LITERAL_INTEGER, {elementIndex++}}}));
    auto iter = where.InsertBefore(std::move(extract));
    get_def_use_mgr()->AnalyzeInstDefUse(&*iter);
    context()->set_instr_block(&*iter, block);

    // Create the store.
    std::unique_ptr<ir::Instruction> newStore(
        new ir::Instruction(context(), SpvOpStore, 0, 0,
                            std::initializer_list<ir::Operand>{
                                {SPV_OPERAND_TYPE_ID, {var->result_id()}},
                                {SPV_OPERAND_TYPE_ID, {extractId}}}));
    // Copy memory access attributes which start at index 2. Index 0 is the
    // pointer and index 1 is the data.
    for (uint32_t i = 2; i < store->NumInOperands(); ++i) {
      ir::Operand copy(store->GetInOperand(i));
      newStore->AddOperand(std::move(copy));
    }
    iter = where.InsertBefore(std::move(newStore));
    get_def_use_mgr()->AnalyzeInstDefUse(&*iter);
    context()->set_instr_block(&*iter, block);
  }
}

bool ScalarReplacementPass::ReplaceAccessChain(
    ir::Instruction* chain, const std::vector<ir::Instruction*>& replacements) {
  // Replaces the access chain with either another access chain (with one fewer
  // indexes) or a direct use of the replacement variable.
  uint32_t indexId = chain->GetSingleWordInOperand(1u);
  const ir::Instruction* index = get_def_use_mgr()->GetDef(indexId);
  size_t indexValue = GetConstantInteger(index);
  if (indexValue > replacements.size()) {
    // Out of bounds access, this is illegal IR.
    return false;
  } else {
    const ir::Instruction* var = replacements[indexValue];
    if (chain->NumInOperands() > 2) {
      // Replace input access chain with another access chain.
      ir::BasicBlock::iterator chainIter(chain);
      uint32_t replacementId = TakeNextId();
      std::unique_ptr<ir::Instruction> replacementChain(new ir::Instruction(
          context(), chain->opcode(), chain->type_id(), replacementId,
          std::initializer_list<ir::Operand>{
              {SPV_OPERAND_TYPE_ID, {var->result_id()}}}));
      // Add the remaining indexes.
      for (uint32_t i = 2; i < chain->NumInOperands(); ++i) {
        ir::Operand copy(chain->GetInOperand(i));
        replacementChain->AddOperand(std::move(copy));
      }
      auto iter = chainIter.InsertBefore(std::move(replacementChain));
      get_def_use_mgr()->AnalyzeInstDefUse(&*iter);
      context()->set_instr_block(&*iter, context()->get_instr_block(chain));
      context()->ReplaceAllUsesWith(chain->result_id(), replacementId);
    } else {
      // Replace with a use of the variable.
      context()->ReplaceAllUsesWith(chain->result_id(), var->result_id());
    }
  }

  return true;
}

void ScalarReplacementPass::CreateReplacementVariables(
    ir::Instruction* inst, std::vector<ir::Instruction*>* replacements) {
  ir::Instruction* type = GetStorageType(inst);
  uint32_t elem = 0;
  switch (type->opcode()) {
    case SpvOpTypeStruct:
      type->ForEachInOperand([this, inst, &elem, replacements](uint32_t* id) {
        CreateVariable(*id, inst, elem++, replacements);
      });
      break;
    case SpvOpTypeArray:
      for (uint32_t i = 0; i != GetArrayLength(type); ++i) {
        CreateVariable(type->GetSingleWordInOperand(0u), inst, i, replacements);
      }
      break;

    case SpvOpTypeMatrix:
    case SpvOpTypeVector:
      for (uint32_t i = 0; i != GetNumElements(type); ++i) {
        CreateVariable(type->GetSingleWordInOperand(0u), inst, i, replacements);
      }
      break;

    default:
      assert(false && "Unexpected type.");
      break;
  }

  TransferAnnotations(inst, replacements);
}

void ScalarReplacementPass::TransferAnnotations(
    const ir::Instruction* source,
    std::vector<ir::Instruction*>* replacements) {
  // Only transfer invariant and restrict decorations on the variable. There are
  // no type or member decorations that are necessary to transfer.
  for (auto inst :
       get_decoration_mgr()->GetDecorationsFor(source->result_id(), false)) {
    assert(inst->opcode() == SpvOpDecorate);
    uint32_t decoration = inst->GetSingleWordInOperand(1u);
    if (decoration == SpvDecorationInvariant ||
        decoration == SpvDecorationRestrict) {
      for (auto var : *replacements) {
        std::unique_ptr<ir::Instruction> annotation(new ir::Instruction(
            context(), SpvOpDecorate, 0, 0,
            std::initializer_list<ir::Operand>{
                {SPV_OPERAND_TYPE_ID, {var->result_id()}},
                {SPV_OPERAND_TYPE_DECORATION, {decoration}}}));
        for (uint32_t i = 2; i < inst->NumInOperands(); ++i) {
          ir::Operand copy(inst->GetInOperand(i));
          annotation->AddOperand(std::move(copy));
        }
        context()->AddAnnotationInst(std::move(annotation));
        get_def_use_mgr()->AnalyzeInstUse(&*--context()->annotation_end());
      }
    }
  }
}

void ScalarReplacementPass::CreateVariable(
    uint32_t typeId, ir::Instruction* varInst, uint32_t index,
    std::vector<ir::Instruction*>* replacements) {
  uint32_t ptrId = GetOrCreatePointerType(typeId);
  uint32_t id = TakeNextId();
  std::unique_ptr<ir::Instruction> variable(new ir::Instruction(
      context(), SpvOpVariable, ptrId, id,
      std::initializer_list<ir::Operand>{
          {SPV_OPERAND_TYPE_STORAGE_CLASS, {SpvStorageClassFunction}}}));

  ir::BasicBlock* block = context()->get_instr_block(varInst);
  block->begin().InsertBefore(std::move(variable));
  ir::Instruction* inst = &*block->begin();

  // If varInst was initialized, make sure to initialize its replacement.
  GetOrCreateInitialValue(varInst, index, inst);
  get_def_use_mgr()->AnalyzeInstDefUse(inst);
  context()->set_instr_block(inst, block);

  replacements->push_back(inst);
}

uint32_t ScalarReplacementPass::GetOrCreatePointerType(uint32_t id) {
  auto iter = pointee_to_pointer_.find(id);
  if (iter != pointee_to_pointer_.end()) return iter->second;

  analysis::Type* pointeeTy;
  std::unique_ptr<analysis::Pointer> pointerTy;
  std::tie(pointeeTy, pointerTy) =
      context()->get_type_mgr()->GetTypeAndPointerType(id,
                                                       SpvStorageClassFunction);
  uint32_t ptrId = 0;
  if (id == context()->get_type_mgr()->GetId(pointeeTy)) {
    // Non-ambiguous type, just ask the type manager for an id.
    ptrId = context()->get_type_mgr()->GetTypeInstruction(pointerTy.get());
    pointee_to_pointer_[id] = ptrId;
    return ptrId;
  }

  // Ambiguous type. We must perform a linear search to try and find the right
  // type.
  for (auto global : context()->types_values()) {
    if (global.opcode() == SpvOpTypePointer &&
        global.GetSingleWordInOperand(0u) == SpvStorageClassFunction &&
        global.GetSingleWordInOperand(1u) == id) {
      if (!context()->get_feature_mgr()->HasExtension(
              libspirv::Extension::kSPV_KHR_variable_pointers) ||
          get_decoration_mgr()->GetDecorationsFor(id, false).empty()) {
        // If variable pointers is enabled, only reuse a decoration-less
        // pointer of the correct type.
        ptrId = global.result_id();
        break;
      }
    }
  }

  if (ptrId != 0) {
    pointee_to_pointer_[id] = ptrId;
    return ptrId;
  }

  ptrId = TakeNextId();
  context()->AddType(MakeUnique<ir::Instruction>(
      context(), SpvOpTypePointer, 0, ptrId,
      std::initializer_list<ir::Operand>{
          {SPV_OPERAND_TYPE_STORAGE_CLASS, {SpvStorageClassFunction}},
          {SPV_OPERAND_TYPE_ID, {id}}}));
  ir::Instruction* ptr = &*--context()->types_values_end();
  get_def_use_mgr()->AnalyzeInstDefUse(ptr);
  pointee_to_pointer_[id] = ptrId;
  // Register with the type manager if necessary.
  context()->get_type_mgr()->RegisterType(ptrId, *pointerTy);

  return ptrId;
}

void ScalarReplacementPass::GetOrCreateInitialValue(ir::Instruction* source,
                                                    uint32_t index,
                                                    ir::Instruction* newVar) {
  assert(source->opcode() == SpvOpVariable);
  if (source->NumInOperands() < 2) return;

  uint32_t initId = source->GetSingleWordInOperand(1u);
  uint32_t storageId = GetStorageType(newVar)->result_id();
  ir::Instruction* init = get_def_use_mgr()->GetDef(initId);
  uint32_t newInitId = 0;
  // TODO(dnovillo): Refactor this with constant propagation.
  if (init->opcode() == SpvOpConstantNull) {
    // Initialize to appropriate NULL.
    auto iter = type_to_null_.find(storageId);
    if (iter == type_to_null_.end()) {
      newInitId = TakeNextId();
      type_to_null_[storageId] = newInitId;
      context()->AddGlobalValue(MakeUnique<ir::Instruction>(
          context(), SpvOpConstantNull, storageId, newInitId,
          std::initializer_list<ir::Operand>{}));
      ir::Instruction* newNull = &*--context()->types_values_end();
      get_def_use_mgr()->AnalyzeInstDefUse(newNull);
    } else {
      newInitId = iter->second;
    }
  } else if (ir::IsSpecConstantInst(init->opcode())) {
    // Create a new constant extract.
    newInitId = TakeNextId();
    context()->AddGlobalValue(MakeUnique<ir::Instruction>(
        context(), SpvOpSpecConstantOp, storageId, newInitId,
        std::initializer_list<ir::Operand>{
            {SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER, {SpvOpCompositeExtract}},
            {SPV_OPERAND_TYPE_ID, {init->result_id()}},
            {SPV_OPERAND_TYPE_LITERAL_INTEGER, {index}}}));
    ir::Instruction* newSpecConst = &*--context()->types_values_end();
    get_def_use_mgr()->AnalyzeInstDefUse(newSpecConst);
  } else if (init->opcode() == SpvOpConstantComposite) {
    // Get the appropriate index constant.
    newInitId = init->GetSingleWordInOperand(index);
    ir::Instruction* element = get_def_use_mgr()->GetDef(newInitId);
    if (element->opcode() == SpvOpUndef) {
      // Undef is not a valid initializer for a variable.
      newInitId = 0;
    }
  } else {
    assert(false);
  }

  if (newInitId != 0) {
    newVar->AddOperand({SPV_OPERAND_TYPE_ID, {newInitId}});
  }
}

size_t ScalarReplacementPass::GetIntegerLiteral(const ir::Operand& op) const {
  assert(op.words.size() <= 2);
  size_t len = 0;
  for (uint32_t i = 0; i != op.words.size(); ++i) {
    len |= (op.words[i] << (32 * i));
  }
  return len;
}

size_t ScalarReplacementPass::GetConstantInteger(
    const ir::Instruction* constant) const {
  assert(get_def_use_mgr()->GetDef(constant->type_id())->opcode() ==
         SpvOpTypeInt);
  assert(constant->opcode() == SpvOpConstant ||
         constant->opcode() == SpvOpConstantNull);
  if (constant->opcode() == SpvOpConstantNull) {
    return 0;
  }

  const ir::Operand& op = constant->GetInOperand(0u);
  return GetIntegerLiteral(op);
}

size_t ScalarReplacementPass::GetArrayLength(
    const ir::Instruction* arrayType) const {
  assert(arrayType->opcode() == SpvOpTypeArray);
  const ir::Instruction* length =
      get_def_use_mgr()->GetDef(arrayType->GetSingleWordInOperand(1u));
  return GetConstantInteger(length);
}

size_t ScalarReplacementPass::GetNumElements(
    const ir::Instruction* type) const {
  assert(type->opcode() == SpvOpTypeVector ||
         type->opcode() == SpvOpTypeMatrix);
  const ir::Operand& op = type->GetInOperand(1u);
  assert(op.words.size() <= 2);
  size_t len = 0;
  for (uint32_t i = 0; i != op.words.size(); ++i) {
    len |= (op.words[i] << (32 * i));
  }
  return len;
}

ir::Instruction* ScalarReplacementPass::GetStorageType(
    const ir::Instruction* inst) const {
  assert(inst->opcode() == SpvOpVariable);

  uint32_t ptrTypeId = inst->type_id();
  uint32_t typeId =
      get_def_use_mgr()->GetDef(ptrTypeId)->GetSingleWordInOperand(1u);
  return get_def_use_mgr()->GetDef(typeId);
}

bool ScalarReplacementPass::CanReplaceVariable(
    const ir::Instruction* varInst) const {
  assert(varInst->opcode() == SpvOpVariable);

  // Can only replace function scope variables.
  if (varInst->GetSingleWordInOperand(0u) != SpvStorageClassFunction)
    return false;

  if (!CheckTypeAnnotations(get_def_use_mgr()->GetDef(varInst->type_id())))
    return false;

  const ir::Instruction* typeInst = GetStorageType(varInst);
  return CheckType(typeInst) && CheckAnnotations(varInst) && CheckUses(varInst);
}

bool ScalarReplacementPass::CheckType(const ir::Instruction* typeInst) const {
  if (!CheckTypeAnnotations(typeInst)) return false;

  switch (typeInst->opcode()) {
    case SpvOpTypeStruct:
      // Don't bother with empty structs or very large structs.
      if (typeInst->NumInOperands() == 0 ||
          typeInst->NumInOperands() > MAX_NUM_ELEMENTS)
        return false;
      return true;
    case SpvOpTypeArray:
      if (GetArrayLength(typeInst) > MAX_NUM_ELEMENTS) return false;
      return true;
    // TODO(alanbaker): Develop some heuristics for when this should be
    // re-enabled.
    //// Specifically including matrix and vector in an attempt to reduce the
    //// number of vector registers required.
    // case SpvOpTypeMatrix:
    // case SpvOpTypeVector:
    //  if (GetNumElements(typeInst) > MAX_NUM_ELEMENTS) return false;
    //  return true;

    case SpvOpTypeRuntimeArray:
    default:
      return false;
  }
}

bool ScalarReplacementPass::CheckTypeAnnotations(
    const ir::Instruction* typeInst) const {
  for (auto inst :
       get_decoration_mgr()->GetDecorationsFor(typeInst->result_id(), false)) {
    uint32_t decoration;
    if (inst->opcode() == SpvOpDecorate) {
      decoration = inst->GetSingleWordInOperand(1u);
    } else {
      assert(inst->opcode() == SpvOpMemberDecorate);
      decoration = inst->GetSingleWordInOperand(2u);
    }

    switch (decoration) {
      case SpvDecorationRowMajor:
      case SpvDecorationColMajor:
      case SpvDecorationArrayStride:
      case SpvDecorationMatrixStride:
      case SpvDecorationCPacked:
      case SpvDecorationInvariant:
      case SpvDecorationRestrict:
      case SpvDecorationOffset:
      case SpvDecorationAlignment:
      case SpvDecorationAlignmentId:
      case SpvDecorationMaxByteOffset:
        break;
      default:
        return false;
    }
  }

  return true;
}

bool ScalarReplacementPass::CheckAnnotations(
    const ir::Instruction* varInst) const {
  for (auto inst :
       get_decoration_mgr()->GetDecorationsFor(varInst->result_id(), false)) {
    assert(inst->opcode() == SpvOpDecorate);
    uint32_t decoration = inst->GetSingleWordInOperand(1u);
    switch (decoration) {
      case SpvDecorationInvariant:
      case SpvDecorationRestrict:
      case SpvDecorationAlignment:
      case SpvDecorationAlignmentId:
      case SpvDecorationMaxByteOffset:
        break;
      default:
        return false;
    }
  }

  return true;
}

bool ScalarReplacementPass::CheckUses(const ir::Instruction* inst) const {
  VariableStats stats = {0, 0};
  bool ok = CheckUses(inst, &stats);

  // TODO(alanbaker/greg-lunarg): Add some meaningful heuristics about when
  // SRoA is costly, such as when the structure has many (unaccessed?)
  // members.

  return ok;
}

bool ScalarReplacementPass::CheckUses(const ir::Instruction* inst,
                                      VariableStats* stats) const {
  bool ok = true;
  get_def_use_mgr()->ForEachUse(
      inst, [this, stats, &ok](const ir::Instruction* user, uint32_t index) {
        // Annotations are check as a group separately.
        if (!ir::IsAnnotationInst(user->opcode())) {
          switch (user->opcode()) {
            case SpvOpAccessChain:
            case SpvOpInBoundsAccessChain:
              if (index == 2u) {
                uint32_t id = user->GetSingleWordOperand(3u);
                const ir::Instruction* opInst = get_def_use_mgr()->GetDef(id);
                if (!ir::IsCompileTimeConstantInst(opInst->opcode())) {
                  ok = false;
                } else {
                  if (!CheckUsesRelaxed(user)) ok = false;
                }
                stats->num_partial_accesses++;
              } else {
                ok = false;
              }
              break;
            case SpvOpLoad:
              if (!CheckLoad(user, index)) ok = false;
              stats->num_full_accesses++;
              break;
            case SpvOpStore:
              if (!CheckStore(user, index)) ok = false;
              stats->num_full_accesses++;
              break;
            case SpvOpName:
            case SpvOpMemberName:
              break;
            default:
              ok = false;
              break;
          }
        }
      });

  return ok;
}

bool ScalarReplacementPass::CheckUsesRelaxed(
    const ir::Instruction* inst) const {
  bool ok = true;
  get_def_use_mgr()->ForEachUse(
      inst, [this, &ok](const ir::Instruction* user, uint32_t index) {
        switch (user->opcode()) {
          case SpvOpAccessChain:
          case SpvOpInBoundsAccessChain:
            if (index != 2u) {
              ok = false;
            } else {
              if (!CheckUsesRelaxed(user)) ok = false;
            }
            break;
          case SpvOpLoad:
            if (!CheckLoad(user, index)) ok = false;
            break;
          case SpvOpStore:
            if (!CheckStore(user, index)) ok = false;
            break;
          default:
            ok = false;
            break;
        }
      });

  return ok;
}

bool ScalarReplacementPass::CheckLoad(const ir::Instruction* inst,
                                      uint32_t index) const {
  if (index != 2u) return false;
  if (inst->NumInOperands() >= 2 &&
      inst->GetSingleWordInOperand(1u) & SpvMemoryAccessVolatileMask)
    return false;
  return true;
}

bool ScalarReplacementPass::CheckStore(const ir::Instruction* inst,
                                       uint32_t index) const {
  if (index != 0u) return false;
  if (inst->NumInOperands() >= 3 &&
      inst->GetSingleWordInOperand(2u) & SpvMemoryAccessVolatileMask)
    return false;
  return true;
}

}  // namespace opt
}  // namespace spvtools

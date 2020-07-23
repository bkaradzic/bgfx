// Copyright (c) 2019 Google LLC
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

#include "source/fuzz/fuzzer_util.h"

#include <algorithm>
#include <unordered_set>

#include "source/opt/build_module.h"

namespace spvtools {
namespace fuzz {

namespace fuzzerutil {

bool IsFreshId(opt::IRContext* context, uint32_t id) {
  return !context->get_def_use_mgr()->GetDef(id);
}

void UpdateModuleIdBound(opt::IRContext* context, uint32_t id) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2541) consider the
  //  case where the maximum id bound is reached.
  context->module()->SetIdBound(
      std::max(context->module()->id_bound(), id + 1));
}

opt::BasicBlock* MaybeFindBlock(opt::IRContext* context,
                                uint32_t maybe_block_id) {
  auto inst = context->get_def_use_mgr()->GetDef(maybe_block_id);
  if (inst == nullptr) {
    // No instruction defining this id was found.
    return nullptr;
  }
  if (inst->opcode() != SpvOpLabel) {
    // The instruction defining the id is not a label, so it cannot be a block
    // id.
    return nullptr;
  }
  return context->cfg()->block(maybe_block_id);
}

bool PhiIdsOkForNewEdge(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids) {
  if (bb_from->IsSuccessor(bb_to)) {
    // There is already an edge from |from_block| to |to_block|, so there is
    // no need to extend OpPhi instructions.  Do not allow phi ids to be
    // present. This might turn out to be too strict; perhaps it would be OK
    // just to ignore the ids in this case.
    return phi_ids.empty();
  }
  // The edge would add a previously non-existent edge from |from_block| to
  // |to_block|, so we go through the given phi ids and check that they exactly
  // match the OpPhi instructions in |to_block|.
  uint32_t phi_index = 0;
  // An explicit loop, rather than applying a lambda to each OpPhi in |bb_to|,
  // makes sense here because we need to increment |phi_index| for each OpPhi
  // instruction.
  for (auto& inst : *bb_to) {
    if (inst.opcode() != SpvOpPhi) {
      // The OpPhi instructions all occur at the start of the block; if we find
      // a non-OpPhi then we have seen them all.
      break;
    }
    if (phi_index == static_cast<uint32_t>(phi_ids.size())) {
      // Not enough phi ids have been provided to account for the OpPhi
      // instructions.
      return false;
    }
    // Look for an instruction defining the next phi id.
    opt::Instruction* phi_extension =
        context->get_def_use_mgr()->GetDef(phi_ids[phi_index]);
    if (!phi_extension) {
      // The id given to extend this OpPhi does not exist.
      return false;
    }
    if (phi_extension->type_id() != inst.type_id()) {
      // The instruction given to extend this OpPhi either does not have a type
      // or its type does not match that of the OpPhi.
      return false;
    }

    if (context->get_instr_block(phi_extension)) {
      // The instruction defining the phi id has an associated block (i.e., it
      // is not a global value).  Check whether its definition dominates the
      // exit of |from_block|.
      auto dominator_analysis =
          context->GetDominatorAnalysis(bb_from->GetParent());
      if (!dominator_analysis->Dominates(phi_extension,
                                         bb_from->terminator())) {
        // The given id is no good as its definition does not dominate the exit
        // of |from_block|
        return false;
      }
    }
    phi_index++;
  }
  // We allow some of the ids provided for extending OpPhi instructions to be
  // unused.  Their presence does no harm, and requiring a perfect match may
  // make transformations less likely to cleanly apply.
  return true;
}

void AddUnreachableEdgeAndUpdateOpPhis(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    bool condition_value,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids) {
  assert(PhiIdsOkForNewEdge(context, bb_from, bb_to, phi_ids) &&
         "Precondition on phi_ids is not satisfied");
  assert(bb_from->terminator()->opcode() == SpvOpBranch &&
         "Precondition on terminator of bb_from is not satisfied");

  // Get the id of the boolean constant to be used as the condition.
  uint32_t bool_id = MaybeGetBoolConstant(context, condition_value);
  assert(
      bool_id &&
      "Precondition that condition value must be available is not satisfied");

  const bool from_to_edge_already_exists = bb_from->IsSuccessor(bb_to);
  auto successor = bb_from->terminator()->GetSingleWordInOperand(0);

  // Add the dead branch, by turning OpBranch into OpBranchConditional, and
  // ordering the targets depending on whether the given boolean corresponds to
  // true or false.
  bb_from->terminator()->SetOpcode(SpvOpBranchConditional);
  bb_from->terminator()->SetInOperands(
      {{SPV_OPERAND_TYPE_ID, {bool_id}},
       {SPV_OPERAND_TYPE_ID, {condition_value ? successor : bb_to->id()}},
       {SPV_OPERAND_TYPE_ID, {condition_value ? bb_to->id() : successor}}});

  // Update OpPhi instructions in the target block if this branch adds a
  // previously non-existent edge from source to target.
  if (!from_to_edge_already_exists) {
    uint32_t phi_index = 0;
    for (auto& inst : *bb_to) {
      if (inst.opcode() != SpvOpPhi) {
        break;
      }
      assert(phi_index < static_cast<uint32_t>(phi_ids.size()) &&
             "There should be at least one phi id per OpPhi instruction.");
      inst.AddOperand({SPV_OPERAND_TYPE_ID, {phi_ids[phi_index]}});
      inst.AddOperand({SPV_OPERAND_TYPE_ID, {bb_from->id()}});
      phi_index++;
    }
  }
}

bool BlockIsBackEdge(opt::IRContext* context, uint32_t block_id,
                     uint32_t loop_header_id) {
  auto block = context->cfg()->block(block_id);
  auto loop_header = context->cfg()->block(loop_header_id);

  // |block| and |loop_header| must be defined, |loop_header| must be in fact
  // loop header and |block| must branch to it.
  if (!(block && loop_header && loop_header->IsLoopHeader() &&
        block->IsSuccessor(loop_header))) {
    return false;
  }

  // |block_id| must be reachable and be dominated by |loop_header|.
  opt::DominatorAnalysis* dominator_analysis =
      context->GetDominatorAnalysis(loop_header->GetParent());
  return dominator_analysis->IsReachable(block_id) &&
         dominator_analysis->Dominates(loop_header_id, block_id);
}

bool BlockIsInLoopContinueConstruct(opt::IRContext* context, uint32_t block_id,
                                    uint32_t maybe_loop_header_id) {
  // We deem a block to be part of a loop's continue construct if the loop's
  // continue target dominates the block.
  auto containing_construct_block = context->cfg()->block(maybe_loop_header_id);
  if (containing_construct_block->IsLoopHeader()) {
    auto continue_target = containing_construct_block->ContinueBlockId();
    if (context->GetDominatorAnalysis(containing_construct_block->GetParent())
            ->Dominates(continue_target, block_id)) {
      return true;
    }
  }
  return false;
}

opt::BasicBlock::iterator GetIteratorForInstruction(
    opt::BasicBlock* block, const opt::Instruction* inst) {
  for (auto inst_it = block->begin(); inst_it != block->end(); ++inst_it) {
    if (inst == &*inst_it) {
      return inst_it;
    }
  }
  return block->end();
}

bool BlockIsReachableInItsFunction(opt::IRContext* context,
                                   opt::BasicBlock* bb) {
  auto enclosing_function = bb->GetParent();
  return context->GetDominatorAnalysis(enclosing_function)
      ->Dominates(enclosing_function->entry().get(), bb);
}

bool CanInsertOpcodeBeforeInstruction(
    SpvOp opcode, const opt::BasicBlock::iterator& instruction_in_block) {
  if (instruction_in_block->PreviousNode() &&
      (instruction_in_block->PreviousNode()->opcode() == SpvOpLoopMerge ||
       instruction_in_block->PreviousNode()->opcode() == SpvOpSelectionMerge)) {
    // We cannot insert directly after a merge instruction.
    return false;
  }
  if (opcode != SpvOpVariable &&
      instruction_in_block->opcode() == SpvOpVariable) {
    // We cannot insert a non-OpVariable instruction directly before a
    // variable; variables in a function must be contiguous in the entry block.
    return false;
  }
  // We cannot insert a non-OpPhi instruction directly before an OpPhi, because
  // OpPhi instructions need to be contiguous at the start of a block.
  return opcode == SpvOpPhi || instruction_in_block->opcode() != SpvOpPhi;
}

bool CanMakeSynonymOf(opt::IRContext* ir_context, opt::Instruction* inst) {
  if (inst->opcode() == SpvOpSampledImage) {
    // The SPIR-V data rules say that only very specific instructions may
    // may consume the result id of an OpSampledImage, and this excludes the
    // instructions that are used for making synonyms.
    return false;
  }
  if (!inst->HasResultId()) {
    // We can only make a synonym of an instruction that generates an id.
    return false;
  }
  if (!inst->type_id()) {
    // We can only make a synonym of an instruction that has a type.
    return false;
  }
  auto type_inst = ir_context->get_def_use_mgr()->GetDef(inst->type_id());
  if (type_inst->opcode() == SpvOpTypePointer) {
    switch (inst->opcode()) {
      case SpvOpConstantNull:
      case SpvOpUndef:
        // We disallow making synonyms of null or undefined pointers.  This is
        // to provide the property that if the original shader exhibited no bad
        // pointer accesses, the transformed shader will not either.
        return false;
      default:
        break;
    }
  }

  // We do not make synonyms of objects that have decorations: if the synonym is
  // not decorated analogously, using the original object vs. its synonymous
  // form may not be equivalent.
  return ir_context->get_decoration_mgr()
      ->GetDecorationsFor(inst->result_id(), true)
      .empty();
}

bool IsCompositeType(const opt::analysis::Type* type) {
  return type && (type->AsArray() || type->AsMatrix() || type->AsStruct() ||
                  type->AsVector());
}

std::vector<uint32_t> RepeatedFieldToVector(
    const google::protobuf::RepeatedField<uint32_t>& repeated_field) {
  std::vector<uint32_t> result;
  for (auto i : repeated_field) {
    result.push_back(i);
  }
  return result;
}

uint32_t WalkOneCompositeTypeIndex(opt::IRContext* context,
                                   uint32_t base_object_type_id,
                                   uint32_t index) {
  auto should_be_composite_type =
      context->get_def_use_mgr()->GetDef(base_object_type_id);
  assert(should_be_composite_type && "The type should exist.");
  switch (should_be_composite_type->opcode()) {
    case SpvOpTypeArray: {
      auto array_length = GetArraySize(*should_be_composite_type, context);
      if (array_length == 0 || index >= array_length) {
        return 0;
      }
      return should_be_composite_type->GetSingleWordInOperand(0);
    }
    case SpvOpTypeMatrix:
    case SpvOpTypeVector: {
      auto count = should_be_composite_type->GetSingleWordInOperand(1);
      if (index >= count) {
        return 0;
      }
      return should_be_composite_type->GetSingleWordInOperand(0);
    }
    case SpvOpTypeStruct: {
      if (index >= GetNumberOfStructMembers(*should_be_composite_type)) {
        return 0;
      }
      return should_be_composite_type->GetSingleWordInOperand(index);
    }
    default:
      return 0;
  }
}

uint32_t WalkCompositeTypeIndices(
    opt::IRContext* context, uint32_t base_object_type_id,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& indices) {
  uint32_t sub_object_type_id = base_object_type_id;
  for (auto index : indices) {
    sub_object_type_id =
        WalkOneCompositeTypeIndex(context, sub_object_type_id, index);
    if (!sub_object_type_id) {
      return 0;
    }
  }
  return sub_object_type_id;
}

uint32_t GetNumberOfStructMembers(
    const opt::Instruction& struct_type_instruction) {
  assert(struct_type_instruction.opcode() == SpvOpTypeStruct &&
         "An OpTypeStruct instruction is required here.");
  return struct_type_instruction.NumInOperands();
}

uint32_t GetArraySize(const opt::Instruction& array_type_instruction,
                      opt::IRContext* context) {
  auto array_length_constant =
      context->get_constant_mgr()
          ->GetConstantFromInst(context->get_def_use_mgr()->GetDef(
              array_type_instruction.GetSingleWordInOperand(1)))
          ->AsIntConstant();
  if (array_length_constant->words().size() != 1) {
    return 0;
  }
  return array_length_constant->GetU32();
}

bool IsValid(opt::IRContext* context, spv_validator_options validator_options) {
  std::vector<uint32_t> binary;
  context->module()->ToBinary(&binary, false);
  SpirvTools tools(context->grammar().target_env());
  return tools.Validate(binary.data(), binary.size(), validator_options);
}

std::unique_ptr<opt::IRContext> CloneIRContext(opt::IRContext* context) {
  std::vector<uint32_t> binary;
  context->module()->ToBinary(&binary, false);
  return BuildModule(context->grammar().target_env(), nullptr, binary.data(),
                     binary.size());
}

bool IsNonFunctionTypeId(opt::IRContext* ir_context, uint32_t id) {
  auto type = ir_context->get_type_mgr()->GetType(id);
  return type && !type->AsFunction();
}

bool IsMergeOrContinue(opt::IRContext* ir_context, uint32_t block_id) {
  bool result = false;
  ir_context->get_def_use_mgr()->WhileEachUse(
      block_id,
      [&result](const opt::Instruction* use_instruction,
                uint32_t /*unused*/) -> bool {
        switch (use_instruction->opcode()) {
          case SpvOpLoopMerge:
          case SpvOpSelectionMerge:
            result = true;
            return false;
          default:
            return true;
        }
      });
  return result;
}

uint32_t FindFunctionType(opt::IRContext* ir_context,
                          const std::vector<uint32_t>& type_ids) {
  // Look through the existing types for a match.
  for (auto& type_or_value : ir_context->types_values()) {
    if (type_or_value.opcode() != SpvOpTypeFunction) {
      // We are only interested in function types.
      continue;
    }
    if (type_or_value.NumInOperands() != type_ids.size()) {
      // Not a match: different numbers of arguments.
      continue;
    }
    // Check whether the return type and argument types match.
    bool input_operands_match = true;
    for (uint32_t i = 0; i < type_or_value.NumInOperands(); i++) {
      if (type_ids[i] != type_or_value.GetSingleWordInOperand(i)) {
        input_operands_match = false;
        break;
      }
    }
    if (input_operands_match) {
      // Everything matches.
      return type_or_value.result_id();
    }
  }
  // No match was found.
  return 0;
}

opt::Instruction* GetFunctionType(opt::IRContext* context,
                                  const opt::Function* function) {
  uint32_t type_id = function->DefInst().GetSingleWordInOperand(1);
  return context->get_def_use_mgr()->GetDef(type_id);
}

opt::Function* FindFunction(opt::IRContext* ir_context, uint32_t function_id) {
  for (auto& function : *ir_context->module()) {
    if (function.result_id() == function_id) {
      return &function;
    }
  }
  return nullptr;
}

bool FunctionIsEntryPoint(opt::IRContext* context, uint32_t function_id) {
  for (auto& entry_point : context->module()->entry_points()) {
    if (entry_point.GetSingleWordInOperand(1) == function_id) {
      return true;
    }
  }
  return false;
}

bool IdIsAvailableAtUse(opt::IRContext* context,
                        opt::Instruction* use_instruction,
                        uint32_t use_input_operand_index, uint32_t id) {
  auto defining_instruction = context->get_def_use_mgr()->GetDef(id);
  auto enclosing_function =
      context->get_instr_block(use_instruction)->GetParent();
  // If the id a function parameter, it needs to be associated with the
  // function containing the use.
  if (defining_instruction->opcode() == SpvOpFunctionParameter) {
    return InstructionIsFunctionParameter(defining_instruction,
                                          enclosing_function);
  }
  if (!context->get_instr_block(id)) {
    // The id must be at global scope.
    return true;
  }
  if (defining_instruction == use_instruction) {
    // It is not OK for a definition to use itself.
    return false;
  }
  auto dominator_analysis = context->GetDominatorAnalysis(enclosing_function);
  if (use_instruction->opcode() == SpvOpPhi) {
    // In the case where the use is an operand to OpPhi, it is actually the
    // *parent* block associated with the operand that must be dominated by
    // the synonym.
    auto parent_block =
        use_instruction->GetSingleWordInOperand(use_input_operand_index + 1);
    return dominator_analysis->Dominates(
        context->get_instr_block(defining_instruction)->id(), parent_block);
  }
  return dominator_analysis->Dominates(defining_instruction, use_instruction);
}

bool IdIsAvailableBeforeInstruction(opt::IRContext* context,
                                    opt::Instruction* instruction,
                                    uint32_t id) {
  auto defining_instruction = context->get_def_use_mgr()->GetDef(id);
  auto enclosing_function = context->get_instr_block(instruction)->GetParent();
  // If the id a function parameter, it needs to be associated with the
  // function containing the instruction.
  if (defining_instruction->opcode() == SpvOpFunctionParameter) {
    return InstructionIsFunctionParameter(defining_instruction,
                                          enclosing_function);
  }
  if (!context->get_instr_block(id)) {
    // The id is at global scope.
    return true;
  }
  if (defining_instruction == instruction) {
    // The instruction is not available right before its own definition.
    return false;
  }
  return context->GetDominatorAnalysis(enclosing_function)
      ->Dominates(defining_instruction, instruction);
}

bool InstructionIsFunctionParameter(opt::Instruction* instruction,
                                    opt::Function* function) {
  if (instruction->opcode() != SpvOpFunctionParameter) {
    return false;
  }
  bool found_parameter = false;
  function->ForEachParam(
      [instruction, &found_parameter](opt::Instruction* param) {
        if (param == instruction) {
          found_parameter = true;
        }
      });
  return found_parameter;
}

uint32_t GetTypeId(opt::IRContext* context, uint32_t result_id) {
  return context->get_def_use_mgr()->GetDef(result_id)->type_id();
}

uint32_t GetPointeeTypeIdFromPointerType(opt::Instruction* pointer_type_inst) {
  assert(pointer_type_inst && pointer_type_inst->opcode() == SpvOpTypePointer &&
         "Precondition: |pointer_type_inst| must be OpTypePointer.");
  return pointer_type_inst->GetSingleWordInOperand(1);
}

uint32_t GetPointeeTypeIdFromPointerType(opt::IRContext* context,
                                         uint32_t pointer_type_id) {
  return GetPointeeTypeIdFromPointerType(
      context->get_def_use_mgr()->GetDef(pointer_type_id));
}

SpvStorageClass GetStorageClassFromPointerType(
    opt::Instruction* pointer_type_inst) {
  assert(pointer_type_inst && pointer_type_inst->opcode() == SpvOpTypePointer &&
         "Precondition: |pointer_type_inst| must be OpTypePointer.");
  return static_cast<SpvStorageClass>(
      pointer_type_inst->GetSingleWordInOperand(0));
}

SpvStorageClass GetStorageClassFromPointerType(opt::IRContext* context,
                                               uint32_t pointer_type_id) {
  return GetStorageClassFromPointerType(
      context->get_def_use_mgr()->GetDef(pointer_type_id));
}

uint32_t MaybeGetPointerType(opt::IRContext* context, uint32_t pointee_type_id,
                             SpvStorageClass storage_class) {
  for (auto& inst : context->types_values()) {
    switch (inst.opcode()) {
      case SpvOpTypePointer:
        if (inst.GetSingleWordInOperand(0) == storage_class &&
            inst.GetSingleWordInOperand(1) == pointee_type_id) {
          return inst.result_id();
        }
        break;
      default:
        break;
    }
  }
  return 0;
}

uint32_t InOperandIndexFromOperandIndex(const opt::Instruction& inst,
                                        uint32_t absolute_index) {
  // Subtract the number of non-input operands from the index
  return absolute_index - inst.NumOperands() + inst.NumInOperands();
}

bool IsNullConstantSupported(const opt::analysis::Type& type) {
  return type.AsBool() || type.AsInteger() || type.AsFloat() ||
         type.AsMatrix() || type.AsVector() || type.AsArray() ||
         type.AsStruct() || type.AsPointer() || type.AsEvent() ||
         type.AsDeviceEvent() || type.AsReserveId() || type.AsQueue();
}

bool GlobalVariablesMustBeDeclaredInEntryPointInterfaces(
    const opt::IRContext* ir_context) {
  // TODO(afd): We capture the universal environments for which this requirement
  //  holds.  The check should be refined on demand for other target
  //  environments.
  switch (ir_context->grammar().target_env()) {
    case SPV_ENV_UNIVERSAL_1_0:
    case SPV_ENV_UNIVERSAL_1_1:
    case SPV_ENV_UNIVERSAL_1_2:
    case SPV_ENV_UNIVERSAL_1_3:
      return false;
    default:
      return true;
  }
}

void AddVariableIdToEntryPointInterfaces(opt::IRContext* context, uint32_t id) {
  if (GlobalVariablesMustBeDeclaredInEntryPointInterfaces(context)) {
    // Conservatively add this global to the interface of every entry point in
    // the module.  This means that the global is available for other
    // transformations to use.
    //
    // A downside of this is that the global will be in the interface even if it
    // ends up never being used.
    //
    // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3111) revisit
    //  this if a more thorough approach to entry point interfaces is taken.
    for (auto& entry_point : context->module()->entry_points()) {
      entry_point.AddOperand({SPV_OPERAND_TYPE_ID, {id}});
    }
  }
}

void AddGlobalVariable(opt::IRContext* context, uint32_t result_id,
                       uint32_t type_id, SpvStorageClass storage_class,
                       uint32_t initializer_id) {
  // Check various preconditions.
  assert(result_id != 0 && "Result id can't be 0");

  assert((storage_class == SpvStorageClassPrivate ||
          storage_class == SpvStorageClassWorkgroup) &&
         "Variable's storage class must be either Private or Workgroup");

  auto* type_inst = context->get_def_use_mgr()->GetDef(type_id);
  (void)type_inst;  // Variable becomes unused in release mode.
  assert(type_inst && type_inst->opcode() == SpvOpTypePointer &&
         GetStorageClassFromPointerType(type_inst) == storage_class &&
         "Variable's type is invalid");

  if (storage_class == SpvStorageClassWorkgroup) {
    assert(initializer_id == 0);
  }

  if (initializer_id != 0) {
    const auto* constant_inst =
        context->get_def_use_mgr()->GetDef(initializer_id);
    (void)constant_inst;  // Variable becomes unused in release mode.
    assert(constant_inst && spvOpcodeIsConstant(constant_inst->opcode()) &&
           GetPointeeTypeIdFromPointerType(type_inst) ==
               constant_inst->type_id() &&
           "Initializer is invalid");
  }

  opt::Instruction::OperandList operands = {
      {SPV_OPERAND_TYPE_STORAGE_CLASS, {static_cast<uint32_t>(storage_class)}}};

  if (initializer_id) {
    operands.push_back({SPV_OPERAND_TYPE_ID, {initializer_id}});
  }

  context->module()->AddGlobalValue(MakeUnique<opt::Instruction>(
      context, SpvOpVariable, type_id, result_id, std::move(operands)));

  AddVariableIdToEntryPointInterfaces(context, result_id);
  UpdateModuleIdBound(context, result_id);
}

void AddLocalVariable(opt::IRContext* context, uint32_t result_id,
                      uint32_t type_id, uint32_t function_id,
                      uint32_t initializer_id) {
  // Check various preconditions.
  assert(result_id != 0 && "Result id can't be 0");

  auto* type_inst = context->get_def_use_mgr()->GetDef(type_id);
  (void)type_inst;  // Variable becomes unused in release mode.
  assert(type_inst && type_inst->opcode() == SpvOpTypePointer &&
         GetStorageClassFromPointerType(type_inst) == SpvStorageClassFunction &&
         "Variable's type is invalid");

  const auto* constant_inst =
      context->get_def_use_mgr()->GetDef(initializer_id);
  (void)constant_inst;  // Variable becomes unused in release mode.
  assert(constant_inst && spvOpcodeIsConstant(constant_inst->opcode()) &&
         GetPointeeTypeIdFromPointerType(type_inst) ==
             constant_inst->type_id() &&
         "Initializer is invalid");

  auto* function = FindFunction(context, function_id);
  assert(function && "Function id is invalid");

  function->begin()->begin()->InsertBefore(MakeUnique<opt::Instruction>(
      context, SpvOpVariable, type_id, result_id,
      opt::Instruction::OperandList{
          {SPV_OPERAND_TYPE_STORAGE_CLASS, {SpvStorageClassFunction}},
          {SPV_OPERAND_TYPE_ID, {initializer_id}}}));

  UpdateModuleIdBound(context, result_id);
}

bool HasDuplicates(const std::vector<uint32_t>& arr) {
  return std::unordered_set<uint32_t>(arr.begin(), arr.end()).size() !=
         arr.size();
}

bool IsPermutationOfRange(const std::vector<uint32_t>& arr, uint32_t lo,
                          uint32_t hi) {
  if (arr.empty()) {
    return lo > hi;
  }

  if (HasDuplicates(arr)) {
    return false;
  }

  auto min_max = std::minmax_element(arr.begin(), arr.end());
  return arr.size() == hi - lo + 1 && *min_max.first == lo &&
         *min_max.second == hi;
}

std::vector<opt::Instruction*> GetParameters(opt::IRContext* ir_context,
                                             uint32_t function_id) {
  auto* function = FindFunction(ir_context, function_id);
  assert(function && "|function_id| is invalid");

  std::vector<opt::Instruction*> result;
  function->ForEachParam(
      [&result](opt::Instruction* inst) { result.push_back(inst); });

  return result;
}

void AddFunctionType(opt::IRContext* ir_context, uint32_t result_id,
                     const std::vector<uint32_t>& type_ids) {
  assert(result_id != 0 && "Result id can't be 0");
  assert(!type_ids.empty() &&
         "OpTypeFunction always has at least one operand - function's return "
         "type");
  assert(IsNonFunctionTypeId(ir_context, type_ids[0]) &&
         "Return type must not be a function");

  for (size_t i = 1; i < type_ids.size(); ++i) {
    const auto* param_type = ir_context->get_type_mgr()->GetType(type_ids[i]);
    (void)param_type;  // Make compiler happy in release mode.
    assert(param_type && !param_type->AsVoid() && !param_type->AsFunction() &&
           "Function parameter can't have a function or void type");
  }

  opt::Instruction::OperandList operands;
  operands.reserve(type_ids.size());
  for (auto id : type_ids) {
    operands.push_back({SPV_OPERAND_TYPE_ID, {id}});
  }

  ir_context->AddType(MakeUnique<opt::Instruction>(
      ir_context, SpvOpTypeFunction, 0, result_id, std::move(operands)));

  UpdateModuleIdBound(ir_context, result_id);
}

uint32_t FindOrCreateFunctionType(opt::IRContext* ir_context,
                                  uint32_t result_id,
                                  const std::vector<uint32_t>& type_ids) {
  if (auto existing_id = FindFunctionType(ir_context, type_ids)) {
    return existing_id;
  }
  AddFunctionType(ir_context, result_id, type_ids);
  return result_id;
}

uint32_t MaybeGetIntegerType(opt::IRContext* ir_context, uint32_t width,
                             bool is_signed) {
  opt::analysis::Integer type(width, is_signed);
  return ir_context->get_type_mgr()->GetId(&type);
}

uint32_t MaybeGetFloatType(opt::IRContext* ir_context, uint32_t width) {
  opt::analysis::Float type(width);
  return ir_context->get_type_mgr()->GetId(&type);
}

uint32_t MaybeGetVectorType(opt::IRContext* ir_context,
                            uint32_t component_type_id,
                            uint32_t element_count) {
  const auto* component_type =
      ir_context->get_type_mgr()->GetType(component_type_id);
  assert(component_type &&
         (component_type->AsInteger() || component_type->AsFloat() ||
          component_type->AsBool()) &&
         "|component_type_id| is invalid");
  assert(element_count >= 2 && element_count <= 4 &&
         "Precondition: component count must be in range [2, 4].");
  opt::analysis::Vector type(component_type, element_count);
  return ir_context->get_type_mgr()->GetId(&type);
}

uint32_t MaybeGetStructType(opt::IRContext* ir_context,
                            const std::vector<uint32_t>& component_type_ids) {
  std::vector<const opt::analysis::Type*> component_types;
  component_types.reserve(component_type_ids.size());

  for (auto type_id : component_type_ids) {
    const auto* component_type = ir_context->get_type_mgr()->GetType(type_id);
    assert(component_type && !component_type->AsFunction() &&
           "Component type is invalid");
    component_types.push_back(component_type);
  }

  opt::analysis::Struct type(component_types);
  return ir_context->get_type_mgr()->GetId(&type);
}

uint32_t MaybeGetZeroConstant(opt::IRContext* ir_context,
                              uint32_t scalar_or_composite_type_id) {
  const auto* type =
      ir_context->get_type_mgr()->GetType(scalar_or_composite_type_id);
  assert(type && "|scalar_or_composite_type_id| is invalid");

  switch (type->kind()) {
    case opt::analysis::Type::kBool:
      return MaybeGetBoolConstant(ir_context, false);
    case opt::analysis::Type::kFloat:
    case opt::analysis::Type::kInteger: {
      std::vector<uint32_t> words = {0};
      if ((type->AsInteger() && type->AsInteger()->width() > 32) ||
          (type->AsFloat() && type->AsFloat()->width() > 32)) {
        words.push_back(0);
      }

      return MaybeGetScalarConstant(ir_context, words,
                                    scalar_or_composite_type_id);
    }
    case opt::analysis::Type::kStruct: {
      std::vector<uint32_t> component_ids;
      for (const auto* component_type : type->AsStruct()->element_types()) {
        auto component_type_id =
            ir_context->get_type_mgr()->GetId(component_type);
        assert(component_type_id && "Component type is invalid");

        auto component_id = MaybeGetZeroConstant(ir_context, component_type_id);
        if (component_id == 0) {
          return 0;
        }

        component_ids.push_back(component_id);
      }

      return MaybeGetCompositeConstant(ir_context, component_ids,
                                       scalar_or_composite_type_id);
    }
    case opt::analysis::Type::kMatrix:
    case opt::analysis::Type::kVector: {
      const auto* component_type = type->AsVector()
                                       ? type->AsVector()->element_type()
                                       : type->AsMatrix()->element_type();
      auto component_type_id =
          ir_context->get_type_mgr()->GetId(component_type);
      assert(component_type_id && "Component type is invalid");

      if (auto component_id =
              MaybeGetZeroConstant(ir_context, component_type_id)) {
        auto component_count = type->AsVector()
                                   ? type->AsVector()->element_count()
                                   : type->AsMatrix()->element_count();
        return MaybeGetCompositeConstant(
            ir_context, std::vector<uint32_t>(component_count, component_id),
            scalar_or_composite_type_id);
      }

      return 0;
    }
    case opt::analysis::Type::kArray: {
      auto component_type_id =
          ir_context->get_type_mgr()->GetId(type->AsArray()->element_type());
      assert(component_type_id && "Component type is invalid");

      if (auto component_id =
              MaybeGetZeroConstant(ir_context, component_type_id)) {
        auto type_id = ir_context->get_type_mgr()->GetId(type);
        assert(type_id && "|type| is invalid");

        const auto* type_inst = ir_context->get_def_use_mgr()->GetDef(type_id);
        assert(type_inst && "Array's type id is invalid");

        return MaybeGetCompositeConstant(
            ir_context,
            std::vector<uint32_t>(GetArraySize(*type_inst, ir_context),
                                  component_id),
            scalar_or_composite_type_id);
      }

      return 0;
    }
    default:
      assert(false && "Type is not supported");
      return 0;
  }
}

uint32_t MaybeGetScalarConstant(opt::IRContext* ir_context,
                                const std::vector<uint32_t>& words,
                                uint32_t scalar_type_id) {
  const auto* type = ir_context->get_type_mgr()->GetType(scalar_type_id);
  assert(type && "|scalar_type_id| is invalid");

  if (const auto* int_type = type->AsInteger()) {
    return MaybeGetIntegerConstant(ir_context, words, int_type->width(),
                                   int_type->IsSigned());
  } else if (const auto* float_type = type->AsFloat()) {
    return MaybeGetFloatConstant(ir_context, words, float_type->width());
  } else {
    assert(type->AsBool() && words.size() == 1 &&
           "|scalar_type_id| doesn't represent a scalar type");
    return MaybeGetBoolConstant(ir_context, words[0]);
  }
}

uint32_t MaybeGetCompositeConstant(opt::IRContext* ir_context,
                                   const std::vector<uint32_t>& component_ids,
                                   uint32_t composite_type_id) {
  std::vector<const opt::analysis::Constant*> constants;
  for (auto id : component_ids) {
    const auto* component_constant =
        ir_context->get_constant_mgr()->FindDeclaredConstant(id);
    assert(component_constant && "|id| is invalid");

    constants.push_back(component_constant);
  }

  const auto* type = ir_context->get_type_mgr()->GetType(composite_type_id);
  assert(type && "|composite_type_id| is invalid");

  std::unique_ptr<opt::analysis::Constant> composite_constant;
  switch (type->kind()) {
    case opt::analysis::Type::kStruct:
      composite_constant = MakeUnique<opt::analysis::StructConstant>(
          type->AsStruct(), std::move(constants));
      break;
    case opt::analysis::Type::kVector:
      composite_constant = MakeUnique<opt::analysis::VectorConstant>(
          type->AsVector(), std::move(constants));
      break;
    case opt::analysis::Type::kMatrix:
      composite_constant = MakeUnique<opt::analysis::MatrixConstant>(
          type->AsMatrix(), std::move(constants));
      break;
    case opt::analysis::Type::kArray:
      composite_constant = MakeUnique<opt::analysis::ArrayConstant>(
          type->AsArray(), std::move(constants));
      break;
    default:
      assert(false &&
             "|composite_type_id| is not a result id of a composite type");
      return 0;
  }

  return ir_context->get_constant_mgr()->FindDeclaredConstant(
      composite_constant.get(), composite_type_id);
}

uint32_t MaybeGetIntegerConstant(opt::IRContext* ir_context,
                                 const std::vector<uint32_t>& words,
                                 uint32_t width, bool is_signed) {
  auto type_id = MaybeGetIntegerType(ir_context, width, is_signed);
  if (!type_id) {
    return 0;
  }

  const auto* type = ir_context->get_type_mgr()->GetType(type_id);
  assert(type && "|type_id| is invalid");

  opt::analysis::IntConstant constant(type->AsInteger(), words);
  return ir_context->get_constant_mgr()->FindDeclaredConstant(&constant,
                                                              type_id);
}

uint32_t MaybeGetFloatConstant(opt::IRContext* ir_context,
                               const std::vector<uint32_t>& words,
                               uint32_t width) {
  auto type_id = MaybeGetFloatType(ir_context, width);
  if (!type_id) {
    return 0;
  }

  const auto* type = ir_context->get_type_mgr()->GetType(type_id);
  assert(type && "|type_id| is invalid");

  opt::analysis::FloatConstant constant(type->AsFloat(), words);
  return ir_context->get_constant_mgr()->FindDeclaredConstant(&constant,
                                                              type_id);
}

uint32_t MaybeGetBoolConstant(opt::IRContext* context, bool value) {
  opt::analysis::Bool bool_type;
  auto registered_bool_type =
      context->get_type_mgr()->GetRegisteredType(&bool_type);
  if (!registered_bool_type) {
    return 0;
  }
  opt::analysis::BoolConstant bool_constant(registered_bool_type->AsBool(),
                                            value);
  return context->get_constant_mgr()->FindDeclaredConstant(
      &bool_constant, context->get_type_mgr()->GetId(&bool_type));
}

void AddIntegerType(opt::IRContext* ir_context, uint32_t result_id,
                    uint32_t width, bool is_signed) {
  ir_context->module()->AddType(MakeUnique<opt::Instruction>(
      ir_context, SpvOpTypeInt, 0, result_id,
      opt::Instruction::OperandList{
          {SPV_OPERAND_TYPE_LITERAL_INTEGER, {width}},
          {SPV_OPERAND_TYPE_LITERAL_INTEGER, {is_signed ? 1u : 0u}}}));

  UpdateModuleIdBound(ir_context, result_id);
}

void AddFloatType(opt::IRContext* ir_context, uint32_t result_id,
                  uint32_t width) {
  ir_context->module()->AddType(MakeUnique<opt::Instruction>(
      ir_context, SpvOpTypeFloat, 0, result_id,
      opt::Instruction::OperandList{
          {SPV_OPERAND_TYPE_LITERAL_INTEGER, {width}}}));

  UpdateModuleIdBound(ir_context, result_id);
}

void AddVectorType(opt::IRContext* ir_context, uint32_t result_id,
                   uint32_t component_type_id, uint32_t element_count) {
  const auto* component_type =
      ir_context->get_type_mgr()->GetType(component_type_id);
  (void)component_type;  // Make compiler happy in release mode.
  assert(component_type &&
         (component_type->AsInteger() || component_type->AsFloat() ||
          component_type->AsBool()) &&
         "|component_type_id| is invalid");
  assert(element_count >= 2 && element_count <= 4 &&
         "Precondition: component count must be in range [2, 4].");
  ir_context->module()->AddType(MakeUnique<opt::Instruction>(
      ir_context, SpvOpTypeVector, 0, result_id,
      opt::Instruction::OperandList{
          {SPV_OPERAND_TYPE_ID, {component_type_id}},
          {SPV_OPERAND_TYPE_LITERAL_INTEGER, {element_count}}}));

  UpdateModuleIdBound(ir_context, result_id);
}

void AddStructType(opt::IRContext* ir_context, uint32_t result_id,
                   const std::vector<uint32_t>& component_type_ids) {
  opt::Instruction::OperandList operands;
  operands.reserve(component_type_ids.size());

  for (auto type_id : component_type_ids) {
    const auto* type = ir_context->get_type_mgr()->GetType(type_id);
    (void)type;  // Make compiler happy in release mode.
    assert(type && !type->AsFunction() && "Component's type id is invalid");
    operands.push_back({SPV_OPERAND_TYPE_ID, {type_id}});
  }

  ir_context->AddType(MakeUnique<opt::Instruction>(
      ir_context, SpvOpTypeStruct, 0, result_id, std::move(operands)));

  UpdateModuleIdBound(ir_context, result_id);
}

}  // namespace fuzzerutil

}  // namespace fuzz
}  // namespace spvtools

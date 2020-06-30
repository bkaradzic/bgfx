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

#include "source/fuzz/transformation_access_chain.h"

#include <vector>

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationAccessChain::TransformationAccessChain(
    const spvtools::fuzz::protobufs::TransformationAccessChain& message)
    : message_(message) {}

TransformationAccessChain::TransformationAccessChain(
    uint32_t fresh_id, uint32_t pointer_id,
    const std::vector<uint32_t>& index_id,
    const protobufs::InstructionDescriptor& instruction_to_insert_before) {
  message_.set_fresh_id(fresh_id);
  message_.set_pointer_id(pointer_id);
  for (auto id : index_id) {
    message_.add_index_id(id);
  }
  *message_.mutable_instruction_to_insert_before() =
      instruction_to_insert_before;
}

bool TransformationAccessChain::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  // The result id must be fresh
  if (!fuzzerutil::IsFreshId(ir_context, message_.fresh_id())) {
    return false;
  }
  // The pointer id must exist and have a type.
  auto pointer = ir_context->get_def_use_mgr()->GetDef(message_.pointer_id());
  if (!pointer || !pointer->type_id()) {
    return false;
  }
  // The type must indeed be a pointer
  auto pointer_type = ir_context->get_def_use_mgr()->GetDef(pointer->type_id());
  if (pointer_type->opcode() != SpvOpTypePointer) {
    return false;
  }

  // The described instruction to insert before must exist and be a suitable
  // point where an OpAccessChain instruction could be inserted.
  auto instruction_to_insert_before =
      FindInstruction(message_.instruction_to_insert_before(), ir_context);
  if (!instruction_to_insert_before) {
    return false;
  }
  if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(
          SpvOpAccessChain, instruction_to_insert_before)) {
    return false;
  }

  // Do not allow making an access chain from a null or undefined pointer, as
  // we do not want to allow accessing such pointers.  This might be acceptable
  // in dead blocks, but we conservatively avoid it.
  switch (pointer->opcode()) {
    case SpvOpConstantNull:
    case SpvOpUndef:
      // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3185): When
      //  fuzzing for real we would like an 'assert(false)' here.  But we also
      //  want to be able to write negative unit tests.
      return false;
    default:
      break;
  }

  // The pointer on which the access chain is to be based needs to be available
  // (according to dominance rules) at the insertion point.
  if (!fuzzerutil::IdIsAvailableBeforeInstruction(
          ir_context, instruction_to_insert_before, message_.pointer_id())) {
    return false;
  }

  // We now need to use the given indices to walk the type structure of the
  // base type of the pointer, making sure that (a) the indices correspond to
  // integers, and (b) these integer values are in-bounds.

  // Start from the base type of the pointer.
  uint32_t subobject_type_id = pointer_type->GetSingleWordInOperand(1);

  // Consider the given index ids in turn.
  for (auto index_id : message_.index_id()) {
    // Try to get the integer value associated with this index is.  The first
    // component of the result will be false if the id did not correspond to an
    // integer.  Otherwise, the integer with which the id is associated is the
    // second component.
    std::pair<bool, uint32_t> maybe_index_value =
        GetIndexValue(ir_context, index_id);
    if (!maybe_index_value.first) {
      // There was no integer: this index is no good.
      return false;
    }
    // Try to walk down the type using this index.  This will yield 0 if the
    // type is not a composite or the index is out of bounds, and the id of
    // the next type otherwise.
    subobject_type_id = fuzzerutil::WalkOneCompositeTypeIndex(
        ir_context, subobject_type_id, maybe_index_value.second);
    if (!subobject_type_id) {
      // Either the type was not a composite (so that too many indices were
      // provided), or the index was out of bounds.
      return false;
    }
  }
  // At this point, |subobject_type_id| is the type of the value targeted by
  // the new access chain.  The result type of the access chain should be a
  // pointer to this type, with the same storage class as for the original
  // pointer.  Such a pointer type needs to exist in the module.
  //
  // We do not use the type manager to look up this type, due to problems
  // associated with pointers to isomorphic structs being regarded as the same.
  return fuzzerutil::MaybeGetPointerType(
             ir_context, subobject_type_id,
             static_cast<SpvStorageClass>(
                 pointer_type->GetSingleWordInOperand(0))) != 0;
}

void TransformationAccessChain::Apply(
    opt::IRContext* ir_context,
    TransformationContext* transformation_context) const {
  // The operands to the access chain are the pointer followed by the indices.
  // The result type of the access chain is determined by where the indices
  // lead.  We thus push the pointer to a sequence of operands, and then follow
  // the indices, pushing each to the operand list and tracking the type
  // obtained by following it.  Ultimately this yields the type of the
  // component reached by following all the indices, and the result type is
  // a pointer to this component type.
  opt::Instruction::OperandList operands;

  // Add the pointer id itself.
  operands.push_back({SPV_OPERAND_TYPE_ID, {message_.pointer_id()}});

  // Start walking the indices, starting with the pointer's base type.
  auto pointer_type = ir_context->get_def_use_mgr()->GetDef(
      ir_context->get_def_use_mgr()->GetDef(message_.pointer_id())->type_id());
  uint32_t subobject_type_id = pointer_type->GetSingleWordInOperand(1);

  // Go through the index ids in turn.
  for (auto index_id : message_.index_id()) {
    // Add the index id to the operands.
    operands.push_back({SPV_OPERAND_TYPE_ID, {index_id}});
    // Get the integer value associated with the index id.
    uint32_t index_value = GetIndexValue(ir_context, index_id).second;
    // Walk to the next type in the composite object using this index.
    subobject_type_id = fuzzerutil::WalkOneCompositeTypeIndex(
        ir_context, subobject_type_id, index_value);
  }
  // The access chain's result type is a pointer to the composite component that
  // was reached after following all indices.  The storage class is that of the
  // original pointer.
  uint32_t result_type = fuzzerutil::MaybeGetPointerType(
      ir_context, subobject_type_id,
      static_cast<SpvStorageClass>(pointer_type->GetSingleWordInOperand(0)));

  // Add the access chain instruction to the module, and update the module's id
  // bound.
  fuzzerutil::UpdateModuleIdBound(ir_context, message_.fresh_id());
  FindInstruction(message_.instruction_to_insert_before(), ir_context)
      ->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpAccessChain, result_type, message_.fresh_id(),
          operands));

  // Conservatively invalidate all analyses.
  ir_context->InvalidateAnalysesExceptFor(opt::IRContext::kAnalysisNone);

  // If the base pointer's pointee value was irrelevant, the same is true of the
  // pointee value of the result of this access chain.
  if (transformation_context->GetFactManager()->PointeeValueIsIrrelevant(
          message_.pointer_id())) {
    transformation_context->GetFactManager()->AddFactValueOfPointeeIsIrrelevant(
        message_.fresh_id());
  }
}

protobufs::Transformation TransformationAccessChain::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_access_chain() = message_;
  return result;
}

std::pair<bool, uint32_t> TransformationAccessChain::GetIndexValue(
    opt::IRContext* ir_context, uint32_t index_id) const {
  auto index_instruction = ir_context->get_def_use_mgr()->GetDef(index_id);
  if (!index_instruction || !spvOpcodeIsConstant(index_instruction->opcode())) {
    // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3179) We could
    //  allow non-constant indices when looking up non-structs, using clamping
    //  to ensure they are in-bounds.
    return {false, 0};
  }
  auto index_type =
      ir_context->get_def_use_mgr()->GetDef(index_instruction->type_id());
  if (index_type->opcode() != SpvOpTypeInt ||
      index_type->GetSingleWordInOperand(0) != 32) {
    return {false, 0};
  }
  return {true, index_instruction->GetSingleWordInOperand(0)};
}

}  // namespace fuzz
}  // namespace spvtools

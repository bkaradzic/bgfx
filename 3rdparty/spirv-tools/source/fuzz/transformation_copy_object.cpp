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

#include "source/fuzz/transformation_copy_object.h"

#include "source/fuzz/data_descriptor.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"
#include "source/opt/instruction.h"
#include "source/util/make_unique.h"

namespace spvtools {
namespace fuzz {

TransformationCopyObject::TransformationCopyObject(
    const protobufs::TransformationCopyObject& message)
    : message_(message) {}

TransformationCopyObject::TransformationCopyObject(
    uint32_t object,
    const protobufs::InstructionDescriptor& instruction_to_insert_before,
    uint32_t fresh_id) {
  message_.set_object(object);
  *message_.mutable_instruction_to_insert_before() =
      instruction_to_insert_before;
  message_.set_fresh_id(fresh_id);
}

bool TransformationCopyObject::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  if (!fuzzerutil::IsFreshId(ir_context, message_.fresh_id())) {
    // We require the id for the object copy to be unused.
    return false;
  }
  // The id of the object to be copied must exist
  auto object_inst = ir_context->get_def_use_mgr()->GetDef(message_.object());
  if (!object_inst) {
    return false;
  }
  if (!fuzzerutil::CanMakeSynonymOf(ir_context, object_inst)) {
    return false;
  }

  auto insert_before =
      FindInstruction(message_.instruction_to_insert_before(), ir_context);
  if (!insert_before) {
    // The instruction before which the copy should be inserted was not found.
    return false;
  }

  if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpCopyObject,
                                                    insert_before)) {
    return false;
  }

  // |message_object| must be available directly before the point where we want
  // to add the copy.
  return fuzzerutil::IdIsAvailableBeforeInstruction(ir_context, insert_before,
                                                    message_.object());
}

void TransformationCopyObject::Apply(
    opt::IRContext* ir_context,
    TransformationContext* transformation_context) const {
  auto object_inst = ir_context->get_def_use_mgr()->GetDef(message_.object());
  assert(object_inst && "The object to be copied must exist.");
  auto insert_before_inst =
      FindInstruction(message_.instruction_to_insert_before(), ir_context);
  auto destination_block = ir_context->get_instr_block(insert_before_inst);
  assert(destination_block && "The base instruction must be in a block.");
  auto insert_before = fuzzerutil::GetIteratorForInstruction(
      destination_block, insert_before_inst);
  assert(insert_before != destination_block->end() &&
         "There must be an instruction before which the copy can be inserted.");

  opt::Instruction::OperandList operands = {
      {SPV_OPERAND_TYPE_ID, {message_.object()}}};
  insert_before->InsertBefore(MakeUnique<opt::Instruction>(
      ir_context, SpvOp::SpvOpCopyObject, object_inst->type_id(),
      message_.fresh_id(), operands));

  fuzzerutil::UpdateModuleIdBound(ir_context, message_.fresh_id());
  ir_context->InvalidateAnalysesExceptFor(
      opt::IRContext::Analysis::kAnalysisNone);

  transformation_context->GetFactManager()->AddFactDataSynonym(
      MakeDataDescriptor(message_.object(), {}),
      MakeDataDescriptor(message_.fresh_id(), {}), ir_context);

  if (transformation_context->GetFactManager()->PointeeValueIsIrrelevant(
          message_.object())) {
    transformation_context->GetFactManager()->AddFactValueOfPointeeIsIrrelevant(
        message_.fresh_id());
  }
}

protobufs::Transformation TransformationCopyObject::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_copy_object() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

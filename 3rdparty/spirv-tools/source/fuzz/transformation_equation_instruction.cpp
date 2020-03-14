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

#include "source/fuzz/transformation_equation_instruction.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationEquationInstruction::TransformationEquationInstruction(
    const spvtools::fuzz::protobufs::TransformationEquationInstruction& message)
    : message_(message) {}

TransformationEquationInstruction::TransformationEquationInstruction(
    uint32_t fresh_id, SpvOp opcode, const std::vector<uint32_t>& in_operand_id,
    const protobufs::InstructionDescriptor& instruction_to_insert_before) {
  message_.set_fresh_id(fresh_id);
  message_.set_opcode(opcode);
  for (auto id : in_operand_id) {
    message_.add_in_operand_id(id);
  }
  *message_.mutable_instruction_to_insert_before() =
      instruction_to_insert_before;
}

bool TransformationEquationInstruction::IsApplicable(
    opt::IRContext* context,
    const spvtools::fuzz::FactManager& /*unused*/) const {
  // The result id must be fresh.
  if (!fuzzerutil::IsFreshId(context, message_.fresh_id())) {
    return false;
  }
  // The instruction to insert before must exist.
  auto insert_before =
      FindInstruction(message_.instruction_to_insert_before(), context);
  if (!insert_before) {
    return false;
  }
  // The input ids must all exist, not be OpUndef, and be available before this
  // instruction.
  for (auto id : message_.in_operand_id()) {
    auto inst = context->get_def_use_mgr()->GetDef(id);
    if (!inst) {
      return false;
    }
    if (inst->opcode() == SpvOpUndef) {
      return false;
    }
    if (!fuzzerutil::IdIsAvailableBeforeInstruction(context, insert_before,
                                                    id)) {
      return false;
    }
  }

  return MaybeGetResultType(context) != 0;
}

void TransformationEquationInstruction::Apply(
    opt::IRContext* context, spvtools::fuzz::FactManager* fact_manager) const {
  fuzzerutil::UpdateModuleIdBound(context, message_.fresh_id());

  opt::Instruction::OperandList in_operands;
  std::vector<uint32_t> rhs_id;
  for (auto id : message_.in_operand_id()) {
    in_operands.push_back({SPV_OPERAND_TYPE_ID, {id}});
    rhs_id.push_back(id);
  }

  FindInstruction(message_.instruction_to_insert_before(), context)
      ->InsertBefore(MakeUnique<opt::Instruction>(
          context, static_cast<SpvOp>(message_.opcode()),
          MaybeGetResultType(context), message_.fresh_id(), in_operands));

  context->InvalidateAnalysesExceptFor(opt::IRContext::kAnalysisNone);

  fact_manager->AddFactIdEquation(message_.fresh_id(),
                                  static_cast<SpvOp>(message_.opcode()), rhs_id,
                                  context);
}

protobufs::Transformation TransformationEquationInstruction::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_equation_instruction() = message_;
  return result;
}

uint32_t TransformationEquationInstruction::MaybeGetResultType(
    opt::IRContext* context) const {
  switch (static_cast<SpvOp>(message_.opcode())) {
    case SpvOpIAdd:
    case SpvOpISub: {
      if (message_.in_operand_id().size() != 2) {
        return 0;
      }
      uint32_t first_operand_width = 0;
      uint32_t first_operand_type_id = 0;
      for (uint32_t index = 0; index < 2; index++) {
        auto operand_inst =
            context->get_def_use_mgr()->GetDef(message_.in_operand_id(index));
        if (!operand_inst || !operand_inst->type_id()) {
          return 0;
        }
        auto operand_type =
            context->get_type_mgr()->GetType(operand_inst->type_id());
        if (!(operand_type->AsInteger() ||
              (operand_type->AsVector() &&
               operand_type->AsVector()->element_type()->AsInteger()))) {
          return 0;
        }
        uint32_t operand_width =
            operand_type->AsInteger()
                ? 1
                : operand_type->AsVector()->element_count();
        if (index == 0) {
          first_operand_width = operand_width;
          first_operand_type_id = operand_inst->type_id();
        } else {
          assert(first_operand_width != 0 &&
                 "The first operand should have been processed.");
          if (operand_width != first_operand_width) {
            return 0;
          }
        }
      }
      assert(first_operand_type_id != 0 &&
             "A type must have been found for the first operand.");
      return first_operand_type_id;
    }
    case SpvOpLogicalNot: {
      if (message_.in_operand_id().size() != 1) {
        return 0;
      }
      auto operand_inst =
          context->get_def_use_mgr()->GetDef(message_.in_operand_id(0));
      if (!operand_inst || !operand_inst->type_id()) {
        return 0;
      }
      auto operand_type =
          context->get_type_mgr()->GetType(operand_inst->type_id());
      if (!(operand_type->AsBool() ||
            (operand_type->AsVector() &&
             operand_type->AsVector()->element_type()->AsBool()))) {
        return 0;
      }
      return operand_inst->type_id();
    }
    case SpvOpSNegate: {
      if (message_.in_operand_id().size() != 1) {
        return 0;
      }
      auto operand_inst =
          context->get_def_use_mgr()->GetDef(message_.in_operand_id(0));
      if (!operand_inst || !operand_inst->type_id()) {
        return 0;
      }
      auto operand_type =
          context->get_type_mgr()->GetType(operand_inst->type_id());
      if (!(operand_type->AsInteger() ||
            (operand_type->AsVector() &&
             operand_type->AsVector()->element_type()->AsInteger()))) {
        return 0;
      }
      return operand_inst->type_id();
    }

    default:
      assert(false && "Inappropriate opcode for equation instruction.");
      return 0;
  }
}

}  // namespace fuzz
}  // namespace spvtools

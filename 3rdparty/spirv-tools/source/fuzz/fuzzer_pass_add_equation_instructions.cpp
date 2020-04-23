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

#include "source/fuzz/fuzzer_pass_add_equation_instructions.h"

#include <vector>

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/transformation_equation_instruction.h"

namespace spvtools {
namespace fuzz {

FuzzerPassAddEquationInstructions::FuzzerPassAddEquationInstructions(
    opt::IRContext* ir_context, TransformationContext* transformation_context,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, transformation_context, fuzzer_context,
                 transformations) {}

FuzzerPassAddEquationInstructions::~FuzzerPassAddEquationInstructions() =
    default;

void FuzzerPassAddEquationInstructions::Apply() {
  ForEachInstructionWithInstructionDescriptor(
      [this](opt::Function* function, opt::BasicBlock* block,
             opt::BasicBlock::iterator inst_it,
             const protobufs::InstructionDescriptor& instruction_descriptor) {
        if (!GetFuzzerContext()->ChoosePercentage(
                GetFuzzerContext()->GetChanceOfAddingEquationInstruction())) {
          return;
        }

        // Check that it is OK to add an equation instruction before the given
        // instruction in principle - e.g. check that this does not lead to
        // inserting before an OpVariable or OpPhi instruction.  We use OpIAdd
        // as an example opcode for this check, to be representative of *some*
        // opcode that defines an equation, even though we may choose a
        // different opcode below.
        if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpIAdd, inst_it)) {
          return;
        }

        // Get all available instructions with result ids and types that are not
        // OpUndef.
        std::vector<opt::Instruction*> available_instructions =
            FindAvailableInstructions(
                function, block, inst_it,
                [](opt::IRContext*, opt::Instruction* instruction) -> bool {
                  return instruction->result_id() && instruction->type_id() &&
                         instruction->opcode() != SpvOpUndef;
                });

        // Try the opcodes for which we know how to make ids at random until
        // something works.
        std::vector<SpvOp> candidate_opcodes = {SpvOpIAdd, SpvOpISub,
                                                SpvOpLogicalNot, SpvOpSNegate};
        do {
          auto opcode =
              GetFuzzerContext()->RemoveAtRandomIndex(&candidate_opcodes);
          switch (opcode) {
            case SpvOpIAdd:
            case SpvOpISub: {
              // Instructions of integer (scalar or vector) result type are
              // suitable for these opcodes.
              auto integer_instructions =
                  GetIntegerInstructions(available_instructions);
              if (!integer_instructions.empty()) {
                // There is at least one such instruction, so pick one at random
                // for the LHS of an equation.
                auto lhs = integer_instructions.at(
                    GetFuzzerContext()->RandomIndex(integer_instructions));

                // For the RHS, we can use any instruction with an integer
                // scalar/vector result type of the same number of components
                // and the same bit-width for the underlying integer type.

                // Work out the element count and bit-width.
                auto lhs_type =
                    GetIRContext()->get_type_mgr()->GetType(lhs->type_id());
                uint32_t lhs_element_count;
                uint32_t lhs_bit_width;
                if (lhs_type->AsVector()) {
                  lhs_element_count = lhs_type->AsVector()->element_count();
                  lhs_bit_width = lhs_type->AsVector()
                                      ->element_type()
                                      ->AsInteger()
                                      ->width();
                } else {
                  lhs_element_count = 1;
                  lhs_bit_width = lhs_type->AsInteger()->width();
                }

                // Get all the instructions that match on element count and
                // bit-width.
                auto candidate_rhs_instructions = RestrictToElementBitWidth(
                    RestrictToVectorWidth(integer_instructions,
                                          lhs_element_count),
                    lhs_bit_width);

                // Choose a RHS instruction at random; there is guaranteed to
                // be at least one choice as the LHS will be available.
                auto rhs = candidate_rhs_instructions.at(
                    GetFuzzerContext()->RandomIndex(
                        candidate_rhs_instructions));

                // Add the equation instruction.
                ApplyTransformation(TransformationEquationInstruction(
                    GetFuzzerContext()->GetFreshId(), opcode,
                    {lhs->result_id(), rhs->result_id()},
                    instruction_descriptor));
                return;
              }
              break;
            }
            case SpvOpLogicalNot: {
              // Choose any available instruction of boolean scalar/vector
              // result type and equate its negation with a fresh id.
              auto boolean_instructions =
                  GetBooleanInstructions(available_instructions);
              if (!boolean_instructions.empty()) {
                ApplyTransformation(TransformationEquationInstruction(
                    GetFuzzerContext()->GetFreshId(), opcode,
                    {boolean_instructions
                         .at(GetFuzzerContext()->RandomIndex(
                             boolean_instructions))
                         ->result_id()},
                    instruction_descriptor));
                return;
              }
              break;
            }
            case SpvOpSNegate: {
              // Similar to OpLogicalNot, but for signed integer negation.
              auto integer_instructions =
                  GetIntegerInstructions(available_instructions);
              if (!integer_instructions.empty()) {
                ApplyTransformation(TransformationEquationInstruction(
                    GetFuzzerContext()->GetFreshId(), opcode,
                    {integer_instructions
                         .at(GetFuzzerContext()->RandomIndex(
                             integer_instructions))
                         ->result_id()},
                    instruction_descriptor));
                return;
              }
              break;
            }
            default:
              assert(false && "Unexpected opcode.");
              break;
          }
        } while (!candidate_opcodes.empty());
        // Reaching here means that we did not manage to apply any
        // transformation at this point of the module.
      });
}

std::vector<opt::Instruction*>
FuzzerPassAddEquationInstructions::GetIntegerInstructions(
    const std::vector<opt::Instruction*>& instructions) const {
  std::vector<opt::Instruction*> result;
  for (auto& inst : instructions) {
    auto type = GetIRContext()->get_type_mgr()->GetType(inst->type_id());
    if (type->AsInteger() ||
        (type->AsVector() && type->AsVector()->element_type()->AsInteger())) {
      result.push_back(inst);
    }
  }
  return result;
}

std::vector<opt::Instruction*>
FuzzerPassAddEquationInstructions::GetBooleanInstructions(
    const std::vector<opt::Instruction*>& instructions) const {
  std::vector<opt::Instruction*> result;
  for (auto& inst : instructions) {
    auto type = GetIRContext()->get_type_mgr()->GetType(inst->type_id());
    if (type->AsBool() ||
        (type->AsVector() && type->AsVector()->element_type()->AsBool())) {
      result.push_back(inst);
    }
  }
  return result;
}

std::vector<opt::Instruction*>
FuzzerPassAddEquationInstructions::RestrictToVectorWidth(
    const std::vector<opt::Instruction*>& instructions,
    uint32_t vector_width) const {
  std::vector<opt::Instruction*> result;
  for (auto& inst : instructions) {
    auto type = GetIRContext()->get_type_mgr()->GetType(inst->type_id());
    // Get the vector width of |inst|, which is 1 if |inst| is a scalar and is
    // otherwise derived from its vector type.
    uint32_t other_vector_width =
        type->AsVector() ? type->AsVector()->element_count() : 1;
    // Keep |inst| if the vector widths match.
    if (vector_width == other_vector_width) {
      result.push_back(inst);
    }
  }
  return result;
}

std::vector<opt::Instruction*>
FuzzerPassAddEquationInstructions::RestrictToElementBitWidth(
    const std::vector<opt::Instruction*>& instructions,
    uint32_t bit_width) const {
  std::vector<opt::Instruction*> result;
  for (auto& inst : instructions) {
    const opt::analysis::Type* type =
        GetIRContext()->get_type_mgr()->GetType(inst->type_id());
    if (type->AsVector()) {
      type = type->AsVector()->element_type();
    }
    assert(type->AsInteger() &&
           "Precondition: all input instructions must "
           "have integer scalar or vector type.");
    if (type->AsInteger()->width() == bit_width) {
      result.push_back(inst);
    }
  }
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

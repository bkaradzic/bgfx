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

#include "source/fuzz/id_use_descriptor.h"

#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

opt::Instruction* FindInstructionContainingUse(
    const protobufs::IdUseDescriptor& id_use_descriptor,
    opt::IRContext* context) {
  auto result =
      FindInstruction(id_use_descriptor.enclosing_instruction(), context);
  if (!result) {
    return nullptr;
  }
  if (id_use_descriptor.in_operand_index() >= result->NumInOperands()) {
    return nullptr;
  }
  if (result->GetSingleWordInOperand(id_use_descriptor.in_operand_index()) !=
      id_use_descriptor.id_of_interest()) {
    return nullptr;
  }
  return result;
}

protobufs::IdUseDescriptor MakeIdUseDescriptor(
    uint32_t id_of_interest,
    const protobufs::InstructionDescriptor& enclosing_instruction,
    uint32_t in_operand_index) {
  protobufs::IdUseDescriptor result;
  result.set_id_of_interest(id_of_interest);
  *result.mutable_enclosing_instruction() = enclosing_instruction;
  result.set_in_operand_index(in_operand_index);
  return result;
}

protobufs::IdUseDescriptor MakeIdUseDescriptorFromUse(
    opt::IRContext* context, opt::Instruction* inst,
    uint32_t in_operand_index) {
  auto in_operand = inst->GetInOperand(in_operand_index);
  assert(in_operand.type == SPV_OPERAND_TYPE_ID);
  auto id_of_interest = in_operand.words[0];

  auto block = context->get_instr_block(inst);
  uint32_t base_instruction_result_id = block->id();
  uint32_t num_opcodes_to_ignore = 0;
  for (auto& inst_in_block : *block) {
    if (inst_in_block.HasResultId()) {
      base_instruction_result_id = inst_in_block.result_id();
      num_opcodes_to_ignore = 0;
    }
    if (&inst_in_block == inst) {
      return MakeIdUseDescriptor(
          id_of_interest,
          MakeInstructionDescriptor(base_instruction_result_id, inst->opcode(),
                                    num_opcodes_to_ignore),
          in_operand_index);
    }
    if (inst_in_block.opcode() == inst->opcode()) {
      num_opcodes_to_ignore++;
    }
  }
  assert(false && "No matching instruction was found.");
  return protobufs::IdUseDescriptor();
}

}  // namespace fuzz
}  // namespace spvtools

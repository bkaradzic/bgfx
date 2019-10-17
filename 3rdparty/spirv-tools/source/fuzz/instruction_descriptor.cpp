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

#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

opt::Instruction* FindInstruction(
    const protobufs::InstructionDescriptor& instruction_descriptor,
    spvtools::opt::IRContext* context) {
  for (auto& function : *context->module()) {
    for (auto& block : function) {
      bool found_base =
          block.id() == instruction_descriptor.base_instruction_result_id();
      uint32_t num_ignored = 0;
      for (auto& instruction : block) {
        if (instruction.HasResultId() &&
            instruction.result_id() ==
                instruction_descriptor.base_instruction_result_id()) {
          assert(!found_base &&
                 "It should not be possible to find the base instruction "
                 "multiple times.");
          found_base = true;
          assert(num_ignored == 0 &&
                 "The skipped instruction count should only be incremented "
                 "after the instruction base has been found.");
        }
        if (found_base &&
            instruction.opcode() ==
                instruction_descriptor.target_instruction_opcode()) {
          if (num_ignored == instruction_descriptor.num_opcodes_to_ignore()) {
            return &instruction;
          }
          num_ignored++;
        }
      }
      if (found_base) {
        // We found the base instruction, but did not find the target
        // instruction in the same block.
        return nullptr;
      }
    }
  }
  return nullptr;
}

protobufs::InstructionDescriptor MakeInstructionDescriptor(
    uint32_t base_instruction_result_id, SpvOp target_instruction_opcode,
    uint32_t num_opcodes_to_ignore) {
  protobufs::InstructionDescriptor result;
  result.set_base_instruction_result_id(base_instruction_result_id);
  result.set_target_instruction_opcode(target_instruction_opcode);
  result.set_num_opcodes_to_ignore(num_opcodes_to_ignore);
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

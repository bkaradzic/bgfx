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

#include "source/fuzz/fuzzer_pass.h"

#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

FuzzerPass::FuzzerPass(opt::IRContext* ir_context, FactManager* fact_manager,
                       FuzzerContext* fuzzer_context,
                       protobufs::TransformationSequence* transformations)
    : ir_context_(ir_context),
      fact_manager_(fact_manager),
      fuzzer_context_(fuzzer_context),
      transformations_(transformations) {}

FuzzerPass::~FuzzerPass() = default;

std::vector<opt::Instruction*> FuzzerPass::FindAvailableInstructions(
    const opt::Function& function, opt::BasicBlock* block,
    opt::BasicBlock::iterator inst_it,
    std::function<bool(opt::IRContext*, opt::Instruction*)>
        instruction_is_relevant) {
  // TODO(afd) The following is (relatively) simple, but may end up being
  //  prohibitively inefficient, as it walks the whole dominator tree for
  //  every instruction that is considered.

  std::vector<opt::Instruction*> result;
  // Consider all global declarations
  for (auto& global : GetIRContext()->module()->types_values()) {
    if (instruction_is_relevant(GetIRContext(), &global)) {
      result.push_back(&global);
    }
  }

  // Consider all previous instructions in this block
  for (auto prev_inst_it = block->begin(); prev_inst_it != inst_it;
       ++prev_inst_it) {
    if (instruction_is_relevant(GetIRContext(), &*prev_inst_it)) {
      result.push_back(&*prev_inst_it);
    }
  }

  // Walk the dominator tree to consider all instructions from dominating
  // blocks
  auto dominator_analysis = GetIRContext()->GetDominatorAnalysis(&function);
  for (auto next_dominator = dominator_analysis->ImmediateDominator(block);
       next_dominator != nullptr;
       next_dominator =
           dominator_analysis->ImmediateDominator(next_dominator)) {
    for (auto& dominating_inst : *next_dominator) {
      if (instruction_is_relevant(GetIRContext(), &dominating_inst)) {
        result.push_back(&dominating_inst);
      }
    }
  }
  return result;
}

void FuzzerPass::MaybeAddTransformationBeforeEachInstruction(
    std::function<
        void(const opt::Function& function, opt::BasicBlock* block,
             opt::BasicBlock::iterator inst_it,
             const protobufs::InstructionDescriptor& instruction_descriptor)>
        maybe_apply_transformation) {
  // Consider every block in every function.
  for (auto& function : *GetIRContext()->module()) {
    for (auto& block : function) {
      // We now consider every instruction in the block, randomly deciding
      // whether to apply a transformation before it.

      // In order for transformations to insert new instructions, they need to
      // be able to identify the instruction to insert before.  We describe an
      // instruction via its opcode, 'opc', a base instruction 'base' that has a
      // result id, and the number of instructions with opcode 'opc' that we
      // should skip when searching from 'base' for the desired instruction.
      // (An instruction that has a result id is represented by its own opcode,
      // itself as 'base', and a skip-count of 0.)
      std::vector<std::tuple<uint32_t, SpvOp, uint32_t>>
          base_opcode_skip_triples;

      // The initial base instruction is the block label.
      uint32_t base = block.id();

      // Counts the number of times we have seen each opcode since we reset the
      // base instruction.
      std::map<SpvOp, uint32_t> skip_count;

      // Consider every instruction in the block.  The label is excluded: it is
      // only necessary to consider it as a base in case the first instruction
      // in the block does not have a result id.
      for (auto inst_it = block.begin(); inst_it != block.end(); ++inst_it) {
        if (inst_it->HasResultId()) {
          // In the case that the instruction has a result id, we use the
          // instruction as its own base, and clear the skip counts we have
          // collected.
          base = inst_it->result_id();
          skip_count.clear();
        }
        const SpvOp opcode = inst_it->opcode();

        // Invoke the provided function, which might apply a transformation.
        maybe_apply_transformation(
            function, &block, inst_it,
            MakeInstructionDescriptor(
                base, opcode,
                skip_count.count(opcode) ? skip_count.at(opcode) : 0));

        if (!inst_it->HasResultId()) {
          skip_count[opcode] =
              skip_count.count(opcode) ? skip_count.at(opcode) + 1 : 1;
        }
      }
    }
  }
}

}  // namespace fuzz
}  // namespace spvtools

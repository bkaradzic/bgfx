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

#include "source/fuzz/transformation_split_block.h"

#include <utility>

#include "source/fuzz/fuzzer_util.h"
#include "source/util/make_unique.h"

namespace spvtools {
namespace fuzz {

TransformationSplitBlock::TransformationSplitBlock(
    const spvtools::fuzz::protobufs::TransformationSplitBlock& message)
    : message_(message) {}

TransformationSplitBlock::TransformationSplitBlock(uint32_t result_id,
                                                   uint32_t offset,
                                                   uint32_t fresh_id) {
  message_.set_result_id(result_id);
  message_.set_offset(offset);
  message_.set_fresh_id(fresh_id);
}

std::pair<bool, opt::BasicBlock::iterator>
TransformationSplitBlock::FindInstToSplitBefore(opt::BasicBlock* block) const {
  // There are three possibilities:
  // (1) the transformation wants to split at some offset from the block's
  //     label.
  // (2) the transformation wants to split at some offset from a
  //     non-label instruction inside the block.
  // (3) the split assocaiated with this transformation has nothing to do with
  //     this block
  if (message_.result_id() == block->id()) {
    // Case (1).
    if (message_.offset() == 0) {
      // The offset is not allowed to be 0: this would mean splitting before the
      // block's label.
      // By returning (true, block->end()), we indicate that we did find the
      // instruction (so that it is not worth searching further for it), but
      // that splitting will not be possible.
      return {true, block->end()};
    }
    // Conceptually, the first instruction in the block is [label + 1].
    // We thus start from 1 when applying the offset.
    auto inst_it = block->begin();
    for (uint32_t i = 1; i < message_.offset() && inst_it != block->end();
         i++) {
      ++inst_it;
    }
    // This is either the desired instruction, or the end of the block.
    return {true, inst_it};
  }
  for (auto inst_it = block->begin(); inst_it != block->end(); ++inst_it) {
    if (message_.result_id() == inst_it->result_id()) {
      // Case (2): we have found the base instruction; we now apply the offset.
      for (uint32_t i = 0; i < message_.offset() && inst_it != block->end();
           i++) {
        ++inst_it;
      }
      // This is either the desired instruction, or the end of the block.
      return {true, inst_it};
    }
  }
  // Case (3).
  return {false, block->end()};
}

bool TransformationSplitBlock::IsApplicable(
    opt::IRContext* context, const FactManager& /*unused*/) const {
  if (!fuzzerutil::IsFreshId(context, message_.fresh_id())) {
    // We require the id for the new block to be unused.
    return false;
  }
  // Consider every block in every function.
  for (auto& function : *context->module()) {
    for (auto& block : function) {
      auto maybe_split_before = FindInstToSplitBefore(&block);
      if (!maybe_split_before.first) {
        continue;
      }
      if (maybe_split_before.second == block.end()) {
        // The base instruction was found, but the offset was inappropriate.
        return false;
      }
      if (block.IsLoopHeader()) {
        // We cannot split a loop header block: back-edges would become invalid.
        return false;
      }
      auto split_before = maybe_split_before.second;
      if (split_before->PreviousNode() &&
          split_before->PreviousNode()->opcode() == SpvOpSelectionMerge) {
        // We cannot split directly after a selection merge: this would separate
        // the merge from its associated branch or switch operation.
        return false;
      }
      if (split_before->opcode() == SpvOpVariable) {
        // We cannot split directly after a variable; variables in a function
        // must be contiguous in the entry block.
        return false;
      }
      if (split_before->opcode() == SpvOpPhi &&
          split_before->NumInOperands() != 2) {
        // We cannot split before an OpPhi unless the OpPhi has exactly one
        // associated incoming edge.
        return false;
      }
      return true;
    }
  }
  return false;
}

void TransformationSplitBlock::Apply(opt::IRContext* context,
                                     FactManager* /*unused*/) const {
  for (auto& function : *context->module()) {
    for (auto& block : function) {
      auto maybe_split_before = FindInstToSplitBefore(&block);
      if (!maybe_split_before.first) {
        continue;
      }
      assert(maybe_split_before.second != block.end() &&
             "If the transformation is applicable, we should have an "
             "instruction to split on.");
      // We need to make sure the module's id bound is large enough to add the
      // fresh id.
      fuzzerutil::UpdateModuleIdBound(context, message_.fresh_id());
      // Split the block.
      auto new_bb = block.SplitBasicBlock(context, message_.fresh_id(),
                                          maybe_split_before.second);
      // The split does not automatically add a branch between the two parts of
      // the original block, so we add one.
      block.AddInstruction(MakeUnique<opt::Instruction>(
          context, SpvOpBranch, 0, 0,
          std::initializer_list<opt::Operand>{
              opt::Operand(spv_operand_type_t::SPV_OPERAND_TYPE_ID,
                           {message_.fresh_id()})}));
      // If we split before OpPhi instructions, we need to update their
      // predecessor operand so that the block they used to be inside is now the
      // predecessor.
      new_bb->ForEachPhiInst([&block](opt::Instruction* phi_inst) {
        // The following assertion is a sanity check.  It is guaranteed to hold
        // if IsApplicable holds.
        assert(phi_inst->NumInOperands() == 2 &&
               "We can only split a block before an OpPhi if block has exactly "
               "one predecessor.");
        phi_inst->SetInOperand(1, {block.id()});
      });
      // Invalidate all analyses
      context->InvalidateAnalysesExceptFor(
          opt::IRContext::Analysis::kAnalysisNone);
      return;
    }
  }
  assert(0 &&
         "Should be unreachable: it should have been possible to apply this "
         "transformation.");
}

protobufs::Transformation TransformationSplitBlock::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_split_block() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

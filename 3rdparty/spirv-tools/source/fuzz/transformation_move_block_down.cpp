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

#include "source/fuzz/transformation_move_block_down.h"

#include "source/opt/basic_block.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

using opt::BasicBlock;
using opt::IRContext;

bool IsApplicable(const protobufs::TransformationMoveBlockDown& message,
                  IRContext* context, const FactManager& /*unused*/) {
  // Go through every block in every function, looking for a block whose id
  // matches that of the block we want to consider moving down.
  for (auto& function : *context->module()) {
    for (auto block_it = function.begin(); block_it != function.end();
         ++block_it) {
      if (block_it->id() == message.block_id()) {
        // We have found a match.
        if (block_it == function.begin()) {
          // The block is the first one appearing in the function.  We are not
          // allowed to move this block down.
          return false;
        }
        // Record the block we would like to consider moving down.
        BasicBlock* block_matching_id = &*block_it;
        // Now see whether there is some block following that block in program
        // order.
        ++block_it;
        if (block_it == function.end()) {
          // There is no such block; i.e., the block we are considering moving
          // is the last one in the function.  The transformation thus does not
          // apply.
          return false;
        }
        BasicBlock* next_block_in_program_order = &*block_it;
        // We can move the block of interest down if and only if it does not
        // dominate the block that comes next.
        return !context->GetDominatorAnalysis(&function)->Dominates(
            block_matching_id, next_block_in_program_order);
      }
    }
  }

  // We did not find a matching block, so the transformation is not applicable:
  // there is no relevant block to move.
  return false;
}

void Apply(const protobufs::TransformationMoveBlockDown& message,
           IRContext* context, FactManager* /*unused*/) {
  // Go through every block in every function, looking for a block whose id
  // matches that of the block we want to move down.
  for (auto& function : *context->module()) {
    for (auto block_it = function.begin(); block_it != function.end();
         ++block_it) {
      if (block_it->id() == message.block_id()) {
        ++block_it;
        assert(block_it != function.end() &&
               "To be able to move a block down, it needs to have a "
               "program-order successor.");
        function.MoveBasicBlockToAfter(message.block_id(), &*block_it);
        // It is prudent to invalidate analyses after changing block ordering in
        // case any of them depend on it, but the ones that definitely do not
        // depend on ordering can be preserved. These include the following,
        // which can likely be extended.
        context->InvalidateAnalysesExceptFor(
            IRContext::Analysis::kAnalysisDefUse |
            IRContext::Analysis::kAnalysisDominatorAnalysis);

        return;
      }
    }
  }
  assert(false && "No block was found to move down.");
}

protobufs::TransformationMoveBlockDown MakeTransformationMoveBlockDown(
    uint32_t id) {
  protobufs::TransformationMoveBlockDown result;
  result.set_block_id(id);
  return result;
}

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

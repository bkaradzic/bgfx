// Copyright (c) 2018 Google LLC
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

#include "dominator_analysis.h"

#include <unordered_set>

#include "ir_context.h"

namespace spvtools {
namespace opt {

ir::BasicBlock* DominatorAnalysisBase::CommonDominator(
    ir::BasicBlock* b1, ir::BasicBlock* b2) const {
  if (!b1 || !b2) return nullptr;

  std::unordered_set<ir::BasicBlock*> seen;
  ir::BasicBlock* block = b1;
  while (block && seen.insert(block).second) {
    block = ImmediateDominator(block);
  }

  block = b2;
  while (block && !seen.count(block)) {
    block = ImmediateDominator(block);
  }

  return block;
}

bool DominatorAnalysisBase::Dominates(ir::Instruction* a,
                                      ir::Instruction* b) const {
  if (!a || !b) {
    return false;
  }

  if (a == b) {
    return true;
  }

  ir::BasicBlock* bb_a = a->context()->get_instr_block(a);
  ir::BasicBlock* bb_b = b->context()->get_instr_block(b);

  if (bb_a != bb_b) {
    return tree_.Dominates(bb_a, bb_b);
  }

  for (ir::Instruction& inst : *bb_a) {
    if (&inst == a) {
      return true;
    } else if (&inst == b) {
      return false;
    }
  }
  assert(false &&
         "We did not find the load or store in the block they are "
         "supposed to be in.");
  return false;
}

}  // namespace opt
}  // namespace spvtools

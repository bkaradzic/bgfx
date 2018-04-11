// Copyright (c) 2018 Google LLC.
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

#include "opt/licm_pass.h"
#include "opt/module.h"
#include "opt/pass.h"

#include <queue>
#include <utility>

namespace spvtools {
namespace opt {

Pass::Status LICMPass::Process(ir::IRContext* c) {
  InitializeProcessing(c);
  bool modified = false;

  if (c != nullptr) {
    modified = ProcessIRContext();
  }

  return modified ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

bool LICMPass::ProcessIRContext() {
  bool modified = false;
  ir::Module* module = get_module();

  // Process each function in the module
  for (ir::Function& f : *module) {
    modified |= ProcessFunction(&f);
  }
  return modified;
}

bool LICMPass::ProcessFunction(ir::Function* f) {
  bool modified = false;
  ir::LoopDescriptor* loop_descriptor = context()->GetLoopDescriptor(f);

  // Process each loop in the function
  for (ir::Loop& loop : *loop_descriptor) {
    // Ignore nested loops, as we will process them in order in ProcessLoop
    if (loop.IsNested()) {
      continue;
    }
    modified |= ProcessLoop(&loop, f);
  }
  return modified;
}

bool LICMPass::ProcessLoop(ir::Loop* loop, ir::Function* f) {
  bool modified = false;

  // Process all nested loops first
  for (ir::Loop* nested_loop : *loop) {
    modified |= ProcessLoop(nested_loop, f);
  }

  std::vector<ir::BasicBlock*> loop_bbs{};
  modified |= AnalyseAndHoistFromBB(loop, f, loop->GetHeaderBlock(), &loop_bbs);

  for (size_t i = 0; i < loop_bbs.size(); ++i) {
    ir::BasicBlock* bb = loop_bbs[i];
    // do not delete the element
    modified |= AnalyseAndHoistFromBB(loop, f, bb, &loop_bbs);
  }

  return modified;
}

bool LICMPass::AnalyseAndHoistFromBB(ir::Loop* loop, ir::Function* f,
                                     ir::BasicBlock* bb,
                                     std::vector<ir::BasicBlock*>* loop_bbs) {
  bool modified = false;
  std::function<void(ir::Instruction*)> hoist_inst =
      [this, &loop, &modified](ir::Instruction* inst) {
        if (loop->ShouldHoistInstruction(this->context(), inst)) {
          HoistInstruction(loop, inst);
          modified = true;
        }
      };

  if (IsImmediatelyContainedInLoop(loop, f, bb)) {
    bb->ForEachInst(hoist_inst, false);
  }

  opt::DominatorAnalysis* dom_analysis =
      context()->GetDominatorAnalysis(f, *cfg());
  opt::DominatorTree& dom_tree = dom_analysis->GetDomTree();

  for (opt::DominatorTreeNode* child_dom_tree_node :
       *dom_tree.GetTreeNode(bb)) {
    if (loop->IsInsideLoop(child_dom_tree_node->bb_)) {
      loop_bbs->push_back(child_dom_tree_node->bb_);
    }
  }

  return modified;
}

bool LICMPass::IsImmediatelyContainedInLoop(ir::Loop* loop, ir::Function* f,
                                            ir::BasicBlock* bb) {
  ir::LoopDescriptor* loop_descriptor = context()->GetLoopDescriptor(f);
  return loop == (*loop_descriptor)[bb->id()];
}

void LICMPass::HoistInstruction(ir::Loop* loop, ir::Instruction* inst) {
  ir::BasicBlock* pre_header_bb = loop->GetOrCreatePreHeaderBlock();
  inst->InsertBefore(std::move(&(*pre_header_bb->tail())));
  context()->set_instr_block(inst, pre_header_bb);
}

}  // namespace opt
}  // namespace spvtools

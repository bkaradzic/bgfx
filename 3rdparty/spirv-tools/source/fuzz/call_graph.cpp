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

#include "source/fuzz/call_graph.h"

#include <queue>

namespace spvtools {
namespace fuzz {

CallGraph::CallGraph(opt::IRContext* context) {
  // Initialize function in-degree and call graph edges to 0 and empty.
  for (auto& function : *context->module()) {
    function_in_degree_[function.result_id()] = 0;
    call_graph_edges_[function.result_id()] = std::set<uint32_t>();
  }

  // Consider every function.
  for (auto& function : *context->module()) {
    // Avoid considering the same callee of this function multiple times by
    // recording known callees.
    std::set<uint32_t> known_callees;
    // Consider every function call instruction in every block.
    for (auto& block : function) {
      for (auto& instruction : block) {
        if (instruction.opcode() != SpvOpFunctionCall) {
          continue;
        }
        // Get the id of the function being called.
        uint32_t callee = instruction.GetSingleWordInOperand(0);
        if (known_callees.count(callee)) {
          // We have already considered a call to this function - ignore it.
          continue;
        }
        // Increase the callee's in-degree and add an edge to the call graph.
        function_in_degree_[callee]++;
        call_graph_edges_[function.result_id()].insert(callee);
        // Mark the callee as 'known'.
        known_callees.insert(callee);
      }
    }
  }
}

void CallGraph::PushDirectCallees(uint32_t function_id,
                                  std::queue<uint32_t>* queue) const {
  for (auto callee : GetDirectCallees(function_id)) {
    queue->push(callee);
  }
}

std::set<uint32_t> CallGraph::GetIndirectCallees(uint32_t function_id) const {
  std::set<uint32_t> result;
  std::queue<uint32_t> queue;
  PushDirectCallees(function_id, &queue);

  while (!queue.empty()) {
    auto next = queue.front();
    queue.pop();
    if (result.count(next)) {
      continue;
    }
    result.insert(next);
    PushDirectCallees(next, &queue);
  }
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

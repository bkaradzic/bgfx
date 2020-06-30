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

#ifndef SOURCE_FUZZ_CALL_GRAPH_H_
#define SOURCE_FUZZ_CALL_GRAPH_H_

#include <map>
#include <set>

#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

// Represents the acyclic call graph of a SPIR-V module.
class CallGraph {
 public:
  // Creates a call graph corresponding to the given SPIR-V module.
  explicit CallGraph(opt::IRContext* context);

  // Returns a mapping from each function to its number of distinct callers.
  const std::map<uint32_t, uint32_t>& GetFunctionInDegree() const {
    return function_in_degree_;
  }

  // Returns the ids of the functions that |function_id| directly invokes.
  const std::set<uint32_t>& GetDirectCallees(uint32_t function_id) const {
    return call_graph_edges_.at(function_id);
  }

  // Returns the ids of the functions that |function_id| directly or indirectly
  // invokes.
  std::set<uint32_t> GetIndirectCallees(uint32_t function_id) const;

 private:
  // Pushes the direct callees of |function_id| on to |queue|.
  void PushDirectCallees(uint32_t function_id,
                         std::queue<uint32_t>* queue) const;

  // Maps each function id to the ids of its immediate callees.
  std::map<uint32_t, std::set<uint32_t>> call_graph_edges_;

  // For each function id, stores the number of distinct functions that call
  // the function.
  std::map<uint32_t, uint32_t> function_in_degree_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_CALL_GRAPH_H_

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

#ifndef SOURCE_OPT_SCALAR_ANALYSIS_H_
#define SOURCE_OPT_SCALAR_ANALYSIS_H_

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

#include "opt/basic_block.h"
#include "opt/instruction.h"
#include "opt/scalar_analysis_nodes.h"

namespace spvtools {
namespace ir {
class IRContext;
class Loop;
}  // namespace ir

namespace opt {

// Manager for the Scalar Evolution analysis. Creates and maintains a DAG of
// scalar operations generated from analysing the use def graph from incoming
// instructions. Each node is hashed as it is added so like node (for instance,
// two induction variables i=0,i++ and j=0,j++) become the same node. After
// creating a DAG with AnalyzeInstruction it can the be simplified into a more
// usable form with SimplifyExpression.
class ScalarEvolutionAnalysis {
 public:
  explicit ScalarEvolutionAnalysis(ir::IRContext* context);

  // Create a unary negative node on |operand|.
  SENode* CreateNegation(SENode* operand);

  // Creates a subtraction between the two operands by adding |operand_1| to the
  // negation of |operand_2|.
  SENode* CreateSubtraction(SENode* operand_1, SENode* operand_2);

  // Create an addition node between two operands. The |simplify| when set will
  // allow the function to return an SEConstant instead of an addition if the
  // two input operands are also constant.
  SENode* CreateAddNode(SENode* operand_1, SENode* operand_2);

  // Create a multiply node between two operands.
  SENode* CreateMultiplyNode(SENode* operand_1, SENode* operand_2);

  // Create a node representing a constant integer.
  SENode* CreateConstant(int64_t integer);

  // Create a value unknown node, such as a load.
  SENode* CreateValueUnknownNode(const ir::Instruction* inst);

  // Create a CantComputeNode. Used to exit out of analysis.
  SENode* CreateCantComputeNode();

  // Create a new recurrent node with |offset| and |coefficient|, with respect
  // to |loop|.
  SENode* CreateRecurrentExpression(const ir::Loop* loop, SENode* offset,
                                    SENode* coefficient);

  // Construct the DAG by traversing use def chain of |inst|.
  SENode* AnalyzeInstruction(const ir::Instruction* inst);

  // Simplify the |node| by grouping like terms or if contains a recurrent
  // expression, rewrite the graph so the whole DAG (from |node| down) is in
  // terms of that recurrent expression.
  //
  // For example.
  // Induction variable i=0, i++ would produce Rec(0,1) so i+1 could be
  // transformed into Rec(1,1).
  //
  // X+X*2+Y-Y+34-17 would be transformed into 3*X + 17, where X and Y are
  // ValueUnknown nodes (such as a load instruction).
  SENode* SimplifyExpression(SENode* node);

  // Add |prospective_node| into the cache and return a raw pointer to it. If
  // |prospective_node| is already in the cache just return the raw pointer.
  SENode* GetCachedOrAdd(std::unique_ptr<SENode> prospective_node);

  // Checks that the graph starting from |node| is invariant to the |loop|.
  bool IsLoopInvariant(const ir::Loop* loop, const SENode* node) const;

  // Find the recurrent term belonging to |loop| in the graph starting from
  // |node| and return the coefficient of that recurrent term. Constant zero
  // will be returned if no recurrent could be found. |node| should be in
  // simplest form.
  SENode* GetCoefficientFromRecurrentTerm(SENode* node, const ir::Loop* loop);

  // Return a rebuilt graph starting from |node| with the recurrent expression
  // belonging to |loop| being zeroed out. Returned node will be simplified.
  SENode* BuildGraphWithoutRecurrentTerm(SENode* node, const ir::Loop* loop);

  // Return the recurrent term belonging to |loop| if it appears in the graph
  // starting at |node| or null if it doesn't.
  SERecurrentNode* GetRecurrentTerm(SENode* node, const ir::Loop* loop);

  SENode* UpdateChildNode(SENode* parent, SENode* child, SENode* new_child);

 private:
  SENode* AnalyzeConstant(const ir::Instruction* inst);

  // Handles both addition and subtraction. If the |instruction| is OpISub
  // then the resulting node will be op1+(-op2) otherwise if it is OpIAdd then
  // the result will be op1+op2. |instruction| must be OpIAdd or OpISub.
  SENode* AnalyzeAddOp(const ir::Instruction* instruction);

  SENode* AnalyzeMultiplyOp(const ir::Instruction* multiply);

  SENode* AnalyzePhiInstruction(const ir::Instruction* phi);

  ir::IRContext* context_;

  // A map of instructions to SENodes. This is used to track recurrent
  // expressions as they are added when analyzing instructions. Recurrent
  // expressions come from phi nodes which by nature can include recursion so we
  // check if nodes have already been built when analyzing instructions.
  std::map<const ir::Instruction*, SENode*> recurrent_node_map_;

  // On creation we create and cache the CantCompute node so we not need to
  // perform a needless create step.
  SENode* cached_cant_compute_;

  // Helper functor to allow two unique_ptr to nodes to be compare. Only
  // needed
  // for the unordered_set implementation.
  struct NodePointersEquality {
    bool operator()(const std::unique_ptr<SENode>& lhs,
                    const std::unique_ptr<SENode>& rhs) const {
      return *lhs == *rhs;
    }
  };

  // Cache of nodes. All pointers to the nodes are references to the memory
  // managed by they set.
  std::unordered_set<std::unique_ptr<SENode>, SENodeHash, NodePointersEquality>
      node_cache_;
};

}  // namespace opt
}  // namespace spvtools
#endif  // SOURCE_OPT_SCALAR_ANALYSIS_H__

// Copyright (c) 2015-2016 The Khronos Group Inc.
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

#include "cfa.h"
#include "validate.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "spirv_validator_options.h"
#include "val/basic_block.h"
#include "val/construct.h"
#include "val/function.h"
#include "val/validation_state.h"

using std::find;
using std::function;
using std::get;
using std::ignore;
using std::make_pair;
using std::make_tuple;
using std::numeric_limits;
using std::pair;
using std::string;
using std::tie;
using std::transform;
using std::tuple;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using libspirv::BasicBlock;

namespace libspirv {

namespace {

using bb_ptr = BasicBlock*;
using cbb_ptr = const BasicBlock*;
using bb_iter = vector<BasicBlock*>::const_iterator;

}  // namespace

void printDominatorList(const BasicBlock& b) {
  std::cout << b.id() << " is dominated by: ";
  const BasicBlock* bb = &b;
  while (bb->immediate_dominator() != bb) {
    bb = bb->immediate_dominator();
    std::cout << bb->id() << " ";
  }
}

#define CFG_ASSERT(ASSERT_FUNC, TARGET) \
  if (spv_result_t rcode = ASSERT_FUNC(_, TARGET)) return rcode

spv_result_t FirstBlockAssert(ValidationState_t& _, uint32_t target) {
  if (_.current_function().IsFirstBlock(target)) {
    return _.diag(SPV_ERROR_INVALID_CFG)
           << "First block " << _.getIdName(target) << " of function "
           << _.getIdName(_.current_function().id()) << " is targeted by block "
           << _.getIdName(_.current_function().current_block()->id());
  }
  return SPV_SUCCESS;
}

spv_result_t MergeBlockAssert(ValidationState_t& _, uint32_t merge_block) {
  if (_.current_function().IsBlockType(merge_block, kBlockTypeMerge)) {
    return _.diag(SPV_ERROR_INVALID_CFG)
           << "Block " << _.getIdName(merge_block)
           << " is already a merge block for another header";
  }
  return SPV_SUCCESS;
}

/// Update the continue construct's exit blocks once the backedge blocks are
/// identified in the CFG.
void UpdateContinueConstructExitBlocks(
    Function& function, const vector<pair<uint32_t, uint32_t>>& back_edges) {
  auto& constructs = function.constructs();
  // TODO(umar): Think of a faster way to do this
  for (auto& edge : back_edges) {
    uint32_t back_edge_block_id;
    uint32_t loop_header_block_id;
    tie(back_edge_block_id, loop_header_block_id) = edge;
    auto is_this_header = [=](Construct& c) {
      return c.type() == ConstructType::kLoop &&
             c.entry_block()->id() == loop_header_block_id;
    };

    for (auto construct : constructs) {
      if (is_this_header(construct)) {
        Construct* continue_construct =
            construct.corresponding_constructs().back();
        assert(continue_construct->type() == ConstructType::kContinue);

        BasicBlock* back_edge_block;
        tie(back_edge_block, ignore) = function.GetBlock(back_edge_block_id);
        continue_construct->set_exit(back_edge_block);
      }
    }
  }
}

tuple<string, string, string> ConstructNames(ConstructType type) {
  string construct_name, header_name, exit_name;

  switch (type) {
    case ConstructType::kSelection:
      construct_name = "selection";
      header_name = "selection header";
      exit_name = "merge block";
      break;
    case ConstructType::kLoop:
      construct_name = "loop";
      header_name = "loop header";
      exit_name = "merge block";
      break;
    case ConstructType::kContinue:
      construct_name = "continue";
      header_name = "continue target";
      exit_name = "back-edge block";
      break;
    case ConstructType::kCase:
      construct_name = "case";
      header_name = "case entry block";
      exit_name = "case exit block";
      break;
    default:
      assert(1 == 0 && "Not defined type");
  }

  return make_tuple(construct_name, header_name, exit_name);
}

/// Constructs an error message for construct validation errors
string ConstructErrorString(const Construct& construct,
                            const string& header_string,
                            const string& exit_string,
                            const string& dominate_text) {
  string construct_name, header_name, exit_name;
  tie(construct_name, header_name, exit_name) =
      ConstructNames(construct.type());

  // TODO(umar): Add header block for continue constructs to error message
  return "The " + construct_name + " construct with the " + header_name + " " +
         header_string + " " + dominate_text + " the " + exit_name + " " +
         exit_string;
}

spv_result_t StructuredControlFlowChecks(
    const ValidationState_t& _, const Function& function,
    const vector<pair<uint32_t, uint32_t>>& back_edges) {
  /// Check all backedges target only loop headers and have exactly one
  /// back-edge branching to it

  // Map a loop header to blocks with back-edges to the loop header.
  std::map<uint32_t, std::unordered_set<uint32_t>> loop_latch_blocks;
  for (auto back_edge : back_edges) {
    uint32_t back_edge_block;
    uint32_t header_block;
    tie(back_edge_block, header_block) = back_edge;
    if (!function.IsBlockType(header_block, kBlockTypeLoop)) {
      return _.diag(SPV_ERROR_INVALID_CFG)
             << "Back-edges (" << _.getIdName(back_edge_block) << " -> "
             << _.getIdName(header_block)
             << ") can only be formed between a block and a loop header.";
    }
    loop_latch_blocks[header_block].insert(back_edge_block);
  }

  // Check the loop headers have exactly one back-edge branching to it
  for (BasicBlock* loop_header : function.ordered_blocks()) {
    if (!loop_header->reachable()) continue;
    if (!loop_header->is_type(kBlockTypeLoop)) continue;
    auto loop_header_id = loop_header->id();
    auto num_latch_blocks = loop_latch_blocks[loop_header_id].size();
    if (num_latch_blocks != 1) {
      return _.diag(SPV_ERROR_INVALID_CFG)
             << "Loop header " << _.getIdName(loop_header_id)
             << " is targeted by " << num_latch_blocks
             << " back-edge blocks but the standard requires exactly one";
    }
  }

  // Check construct rules
  for (const Construct& construct : function.constructs()) {
    auto header = construct.entry_block();
    auto merge = construct.exit_block();

    if (header->reachable() && !merge) {
      string construct_name, header_name, exit_name;
      tie(construct_name, header_name, exit_name) =
          ConstructNames(construct.type());
      return _.diag(SPV_ERROR_INTERNAL)
             << "Construct " + construct_name + " with " + header_name + " " +
                    _.getIdName(header->id()) + " does not have a " +
                    exit_name + ". This may be a bug in the validator.";
    }

    // If the exit block is reachable then it's dominated by the
    // header.
    if (merge && merge->reachable()) {
      if (!header->dominates(*merge)) {
        return _.diag(SPV_ERROR_INVALID_CFG) << ConstructErrorString(
                   construct, _.getIdName(header->id()),
                   _.getIdName(merge->id()), "does not dominate");
      }
      // If it's really a merge block for a selection or loop, then it must be
      // *strictly* dominated by the header.
      if (construct.ExitBlockIsMergeBlock() && (header == merge)) {
        return _.diag(SPV_ERROR_INVALID_CFG) << ConstructErrorString(
                   construct, _.getIdName(header->id()),
                   _.getIdName(merge->id()), "does not strictly dominate");
      }
    }
    // Check post-dominance for continue constructs.  But dominance and
    // post-dominance only make sense when the construct is reachable.
    if (header->reachable() && construct.type() == ConstructType::kContinue) {
      if (!merge->postdominates(*header)) {
        return _.diag(SPV_ERROR_INVALID_CFG) << ConstructErrorString(
                   construct, _.getIdName(header->id()),
                   _.getIdName(merge->id()), "is not post dominated by");
      }
    }
    // TODO(umar):  an OpSwitch block dominates all its defined case
    // constructs
    // TODO(umar):  each case construct has at most one branch to another
    // case construct
    // TODO(umar):  each case construct is branched to by at most one other
    // case construct
    // TODO(umar):  if Target T1 branches to Target T2, or if Target T1
    // branches to the Default and the Default branches to Target T2, then
    // T1 must immediately precede T2 in the list of the OpSwitch Target
    // operands
  }
  return SPV_SUCCESS;
}

spv_result_t PerformCfgChecks(ValidationState_t& _) {
  for (auto& function : _.functions()) {
    // Check all referenced blocks are defined within a function
    if (function.undefined_block_count() != 0) {
      string undef_blocks("{");
      for (auto undefined_block : function.undefined_blocks()) {
        undef_blocks += _.getIdName(undefined_block) + " ";
      }
      return _.diag(SPV_ERROR_INVALID_CFG)
             << "Block(s) " << undef_blocks << "\b}"
             << " are referenced but not defined in function "
             << _.getIdName(function.id());
    }

    // Set each block's immediate dominator and immediate postdominator,
    // and find all back-edges.
    //
    // We want to analyze all the blocks in the function, even in degenerate
    // control flow cases including unreachable blocks.  So use the augmented
    // CFG to ensure we cover all the blocks.
    vector<const BasicBlock*> postorder;
    vector<const BasicBlock*> postdom_postorder;
    vector<pair<uint32_t, uint32_t>> back_edges;
    auto ignore_block = [](cbb_ptr) {};
    auto ignore_edge = [](cbb_ptr, cbb_ptr) {};
    if (!function.ordered_blocks().empty()) {
      /// calculate dominators
      spvtools::CFA<libspirv::BasicBlock>::DepthFirstTraversal(
          function.first_block(), function.AugmentedCFGSuccessorsFunction(),
          ignore_block, [&](cbb_ptr b) { postorder.push_back(b); },
          ignore_edge);
      auto edges = spvtools::CFA<libspirv::BasicBlock>::CalculateDominators(
          postorder, function.AugmentedCFGPredecessorsFunction());
      for (auto edge : edges) {
        edge.first->SetImmediateDominator(edge.second);
      }

      /// calculate post dominators
      spvtools::CFA<libspirv::BasicBlock>::DepthFirstTraversal(
          function.pseudo_exit_block(),
          function.AugmentedCFGPredecessorsFunction(), ignore_block,
          [&](cbb_ptr b) { postdom_postorder.push_back(b); }, ignore_edge);
      auto postdom_edges =
          spvtools::CFA<libspirv::BasicBlock>::CalculateDominators(
              postdom_postorder, function.AugmentedCFGSuccessorsFunction());
      for (auto edge : postdom_edges) {
        edge.first->SetImmediatePostDominator(edge.second);
      }
      /// calculate back edges.
      spvtools::CFA<libspirv::BasicBlock>::DepthFirstTraversal(
          function.pseudo_entry_block(),
          function
              .AugmentedCFGSuccessorsFunctionIncludingHeaderToContinueEdge(),
          ignore_block, ignore_block, [&](cbb_ptr from, cbb_ptr to) {
            back_edges.emplace_back(from->id(), to->id());
          });
    }
    UpdateContinueConstructExitBlocks(function, back_edges);

    auto& blocks = function.ordered_blocks();
    if (!blocks.empty()) {
      // Check if the order of blocks in the binary appear before the blocks
      // they dominate
      for (auto block = begin(blocks) + 1; block != end(blocks); ++block) {
        if (auto idom = (*block)->immediate_dominator()) {
          if (idom != function.pseudo_entry_block() &&
              block == std::find(begin(blocks), block, idom)) {
            return _.diag(SPV_ERROR_INVALID_CFG)
                   << "Block " << _.getIdName((*block)->id())
                   << " appears in the binary before its dominator "
                   << _.getIdName(idom->id());
          }
        }
      }
      // If we have structed control flow, check that no block has a control
      // flow nesting depth larger than the limit.
      if (_.HasCapability(SpvCapabilityShader)) {
        const int control_flow_nesting_depth_limit =
            _.options()->universal_limits_.max_control_flow_nesting_depth;
        for (auto block = begin(blocks); block != end(blocks); ++block) {
          if (function.GetBlockDepth(*block) >
              control_flow_nesting_depth_limit) {
            return _.diag(SPV_ERROR_INVALID_CFG)
                   << "Maximum Control Flow nesting depth exceeded.";
          }
        }
      }
    }

    /// Structured control flow checks are only required for shader capabilities
    if (_.HasCapability(SpvCapabilityShader)) {
      if (auto error = StructuredControlFlowChecks(_, function, back_edges))
        return error;
    }
  }
  return SPV_SUCCESS;
}

spv_result_t CfgPass(ValidationState_t& _,
                     const spv_parsed_instruction_t* inst) {
  SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  switch (opcode) {
    case SpvOpLabel:
      if (auto error = _.current_function().RegisterBlock(inst->result_id))
        return error;
      break;
    case SpvOpLoopMerge: {
      uint32_t merge_block = inst->words[inst->operands[0].offset];
      uint32_t continue_block = inst->words[inst->operands[1].offset];
      CFG_ASSERT(MergeBlockAssert, merge_block);

      if (auto error = _.current_function().RegisterLoopMerge(merge_block,
                                                              continue_block))
        return error;
    } break;
    case SpvOpSelectionMerge: {
      uint32_t merge_block = inst->words[inst->operands[0].offset];
      CFG_ASSERT(MergeBlockAssert, merge_block);

      if (auto error = _.current_function().RegisterSelectionMerge(merge_block))
        return error;
    } break;
    case SpvOpBranch: {
      uint32_t target = inst->words[inst->operands[0].offset];
      CFG_ASSERT(FirstBlockAssert, target);

      _.current_function().RegisterBlockEnd({target}, opcode);
    } break;
    case SpvOpBranchConditional: {
      uint32_t tlabel = inst->words[inst->operands[1].offset];
      uint32_t flabel = inst->words[inst->operands[2].offset];
      CFG_ASSERT(FirstBlockAssert, tlabel);
      CFG_ASSERT(FirstBlockAssert, flabel);

      _.current_function().RegisterBlockEnd({tlabel, flabel}, opcode);
    } break;

    case SpvOpSwitch: {
      vector<uint32_t> cases;
      for (int i = 1; i < inst->num_operands; i += 2) {
        uint32_t target = inst->words[inst->operands[i].offset];
        CFG_ASSERT(FirstBlockAssert, target);
        cases.push_back(target);
      }
      _.current_function().RegisterBlockEnd({cases}, opcode);
    } break;
    case SpvOpReturn: {
      const uint32_t return_type = _.current_function().GetResultTypeId();
      const Instruction* return_type_inst = _.FindDef(return_type);
      assert(return_type_inst);
      if (return_type_inst->opcode() != SpvOpTypeVoid)
        return _.diag(SPV_ERROR_INVALID_CFG)
               << "OpReturn can only be called from a function with void "
               << "return type.";
    }
    // Fallthrough.
    case SpvOpKill:
    case SpvOpReturnValue:
    case SpvOpUnreachable:
      _.current_function().RegisterBlockEnd(vector<uint32_t>(), opcode);
      if (opcode == SpvOpKill) {
        _.current_function().RegisterExecutionModelLimitation(
            SpvExecutionModelFragment,
            "OpKill requires Fragment execution model");
      }
      break;
    default:
      break;
  }
  return SPV_SUCCESS;
}
}  // namespace libspirv

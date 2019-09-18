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

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {

namespace fuzzerutil {

bool IsFreshId(opt::IRContext* context, uint32_t id) {
  return !context->get_def_use_mgr()->GetDef(id);
}

void UpdateModuleIdBound(opt::IRContext* context, uint32_t id) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2541) consider the
  //  case where the maximum id bound is reached.
  context->module()->SetIdBound(
      std::max(context->module()->id_bound(), id + 1));
}

opt::BasicBlock* MaybeFindBlock(opt::IRContext* context,
                                uint32_t maybe_block_id) {
  auto inst = context->get_def_use_mgr()->GetDef(maybe_block_id);
  if (inst == nullptr) {
    // No instruction defining this id was found.
    return nullptr;
  }
  if (inst->opcode() != SpvOpLabel) {
    // The instruction defining the id is not a label, so it cannot be a block
    // id.
    return nullptr;
  }
  return context->cfg()->block(maybe_block_id);
}

bool PhiIdsOkForNewEdge(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids) {
  if (bb_from->IsSuccessor(bb_to)) {
    // There is already an edge from |from_block| to |to_block|, so there is
    // no need to extend OpPhi instructions.  Do not allow phi ids to be
    // present. This might turn out to be too strict; perhaps it would be OK
    // just to ignore the ids in this case.
    return phi_ids.empty();
  }
  // The edge would add a previously non-existent edge from |from_block| to
  // |to_block|, so we go through the given phi ids and check that they exactly
  // match the OpPhi instructions in |to_block|.
  uint32_t phi_index = 0;
  // An explicit loop, rather than applying a lambda to each OpPhi in |bb_to|,
  // makes sense here because we need to increment |phi_index| for each OpPhi
  // instruction.
  for (auto& inst : *bb_to) {
    if (inst.opcode() != SpvOpPhi) {
      // The OpPhi instructions all occur at the start of the block; if we find
      // a non-OpPhi then we have seen them all.
      break;
    }
    if (phi_index == static_cast<uint32_t>(phi_ids.size())) {
      // Not enough phi ids have been provided to account for the OpPhi
      // instructions.
      return false;
    }
    // Look for an instruction defining the next phi id.
    opt::Instruction* phi_extension =
        context->get_def_use_mgr()->GetDef(phi_ids[phi_index]);
    if (!phi_extension) {
      // The id given to extend this OpPhi does not exist.
      return false;
    }
    if (phi_extension->type_id() != inst.type_id()) {
      // The instruction given to extend this OpPhi either does not have a type
      // or its type does not match that of the OpPhi.
      return false;
    }

    if (context->get_instr_block(phi_extension)) {
      // The instruction defining the phi id has an associated block (i.e., it
      // is not a global value).  Check whether its definition dominates the
      // exit of |from_block|.
      auto dominator_analysis =
          context->GetDominatorAnalysis(bb_from->GetParent());
      if (!dominator_analysis->Dominates(phi_extension,
                                         bb_from->terminator())) {
        // The given id is no good as its definition does not dominate the exit
        // of |from_block|
        return false;
      }
    }
    phi_index++;
  }
  // Return false if not all of the ids for extending OpPhi instructions are
  // needed. This might turn out to be stricter than necessary; perhaps it would
  // be OK just to not use the ids in this case.
  return phi_index == static_cast<uint32_t>(phi_ids.size());
}

void AddUnreachableEdgeAndUpdateOpPhis(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    bool condition_value,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids) {
  assert(PhiIdsOkForNewEdge(context, bb_from, bb_to, phi_ids) &&
         "Precondition on phi_ids is not satisfied");
  assert(bb_from->terminator()->opcode() == SpvOpBranch &&
         "Precondition on terminator of bb_from is not satisfied");

  // Get the id of the boolean constant to be used as the condition.
  opt::analysis::Bool bool_type;
  opt::analysis::BoolConstant bool_constant(
      context->get_type_mgr()->GetRegisteredType(&bool_type)->AsBool(),
      condition_value);
  uint32_t bool_id = context->get_constant_mgr()->FindDeclaredConstant(
      &bool_constant, context->get_type_mgr()->GetId(&bool_type));

  const bool from_to_edge_already_exists = bb_from->IsSuccessor(bb_to);
  auto successor = bb_from->terminator()->GetSingleWordInOperand(0);

  // Add the dead branch, by turning OpBranch into OpBranchConditional, and
  // ordering the targets depending on whether the given boolean corresponds to
  // true or false.
  bb_from->terminator()->SetOpcode(SpvOpBranchConditional);
  bb_from->terminator()->SetInOperands(
      {{SPV_OPERAND_TYPE_ID, {bool_id}},
       {SPV_OPERAND_TYPE_ID, {condition_value ? successor : bb_to->id()}},
       {SPV_OPERAND_TYPE_ID, {condition_value ? bb_to->id() : successor}}});

  // Update OpPhi instructions in the target block if this branch adds a
  // previously non-existent edge from source to target.
  if (!from_to_edge_already_exists) {
    uint32_t phi_index = 0;
    for (auto& inst : *bb_to) {
      if (inst.opcode() != SpvOpPhi) {
        break;
      }
      assert(phi_index < static_cast<uint32_t>(phi_ids.size()) &&
             "There should be exactly one phi id per OpPhi instruction.");
      inst.AddOperand({SPV_OPERAND_TYPE_ID, {phi_ids[phi_index]}});
      inst.AddOperand({SPV_OPERAND_TYPE_ID, {bb_from->id()}});
      phi_index++;
    }
    assert(phi_index == static_cast<uint32_t>(phi_ids.size()) &&
           "There should be exactly one phi id per OpPhi instruction.");
  }
}

bool BlockIsInLoopContinueConstruct(opt::IRContext* context, uint32_t block_id,
                                    uint32_t maybe_loop_header_id) {
  // We deem a block to be part of a loop's continue construct if the loop's
  // continue target dominates the block.
  auto containing_construct_block = context->cfg()->block(maybe_loop_header_id);
  if (containing_construct_block->IsLoopHeader()) {
    auto continue_target = containing_construct_block->ContinueBlockId();
    if (context->GetDominatorAnalysis(containing_construct_block->GetParent())
            ->Dominates(continue_target, block_id)) {
      return true;
    }
  }
  return false;
}

opt::BasicBlock::iterator GetIteratorForBaseInstructionAndOffset(
    opt::BasicBlock* block, const opt::Instruction* base_inst,
    uint32_t offset) {
  // The cases where |base_inst| is the block's label, vs. inside the block,
  // are dealt with separately.
  if (base_inst == block->GetLabelInst()) {
    // |base_inst| is the block's label.
    if (offset == 0) {
      // We cannot return an iterator to the block's label.
      return block->end();
    }
    // Conceptually, the first instruction in the block is [label + 1].
    // We thus start from 1 when applying the offset.
    auto inst_it = block->begin();
    for (uint32_t i = 1; i < offset && inst_it != block->end(); i++) {
      ++inst_it;
    }
    // This is either the desired instruction, or the end of the block.
    return inst_it;
  }
  // |base_inst| is inside the block.
  for (auto inst_it = block->begin(); inst_it != block->end(); ++inst_it) {
    if (base_inst == &*inst_it) {
      // We have found the base instruction; we now apply the offset.
      for (uint32_t i = 0; i < offset && inst_it != block->end(); i++) {
        ++inst_it;
      }
      // This is either the desired instruction, or the end of the block.
      return inst_it;
    }
  }
  assert(false && "The base instruction was not found.");
  return nullptr;
}

std::vector<uint32_t> GetSuccessors(opt::BasicBlock* block) {
  std::vector<uint32_t> result;
  switch (block->terminator()->opcode()) {
    case SpvOpBranch:
      result.push_back(block->terminator()->GetSingleWordInOperand(0));
      break;
    case SpvOpBranchConditional:
      result.push_back(block->terminator()->GetSingleWordInOperand(1));
      result.push_back(block->terminator()->GetSingleWordInOperand(2));
      break;
    case SpvOpSwitch:
      for (uint32_t i = 1; i < block->terminator()->NumInOperands(); i += 2) {
        result.push_back(block->terminator()->GetSingleWordInOperand(i));
      }
      break;
    default:
      break;
  }
  return result;
}

void FindBypassedBlocks(opt::IRContext* context, opt::BasicBlock* bb_from,
                        opt::BasicBlock* bb_to,
                        std::set<opt::BasicBlock*>* bypassed_blocks) {
  // This algorithm finds all blocks different from |bb_from| that:
  // - are in the innermost structured control flow construct containing
  // |bb_from|
  // - can be reached from |bb_from| without traversing a back-edge or going
  // through |bb_to|
  //
  // This is achieved by doing a depth-first search of the function's CFG,
  // exploring merge blocks before successors, and grabbing all blocks that are
  // visited in the sub-search rooted at |bb_from|. (As an optimization, the
  // search terminates as soon as exploration of |bb_from| has completed.)

  // This represents a basic block in a partial state of exploration.  As we
  // wish to visit merge blocks in advance of regular successors, we track them
  // separately.
  struct StackNode {
    opt::BasicBlock* block;
    bool handled_merge;
    std::vector<uint32_t> successors;
    uint32_t next_successor;
  };

  auto enclosing_function = bb_from->GetParent();

  // The set of block ids already visited during search.  We put |bb_to| in
  // there initially so that search automatically backtracks when this block is
  // reached.
  std::set<uint32_t> visited;
  visited.insert(bb_to->id());

  // Tracks when we are in the region of blocks that are to be grabbed; we flip
  // this to 'true' once we reach |bb_from| and have finished searching its
  // merge block (in the case that it happens to be a header.
  bool interested = false;

  std::vector<StackNode> dfs_stack;
  opt::BasicBlock* entry_block = enclosing_function->entry().get();
  dfs_stack.push_back({entry_block, false, GetSuccessors(entry_block), 0});
  while (!dfs_stack.empty()) {
    StackNode* node = &dfs_stack.back();

    // First make sure we search the merge block associated ith this block, if
    // there is one.
    if (!node->handled_merge) {
      node->handled_merge = true;
      if (node->block->MergeBlockIdIfAny()) {
        opt::BasicBlock* merge_block =
            context->cfg()->block(node->block->MergeBlockIdIfAny());
        // A block can only be the merge block for one header, so this block
        // should only be in |visited| if it is |bb_to|, which we put into
        // |visited| in advance.
        assert(visited.count(merge_block->id()) == 0 || merge_block == bb_to);
        if (visited.count(merge_block->id()) == 0) {
          visited.insert(merge_block->id());
          dfs_stack.push_back(
              {merge_block, false, GetSuccessors(merge_block), 0});
        }
      }
      continue;
    }

    // If we find |bb_from|, we are interested in grabbing previously unseen
    // successor blocks (by this point we will have already searched the merge
    // block associated with |bb_from|, if there is one.
    if (node->block == bb_from) {
      interested = true;
    }

    // Consider the next unexplored successor.
    if (node->next_successor < node->successors.size()) {
      uint32_t successor_id = node->successors[node->next_successor];
      if (visited.count(successor_id) == 0) {
        visited.insert(successor_id);
        opt::BasicBlock* successor_block = context->cfg()->block(successor_id);
        if (interested) {
          // If we're in the region of interest, grab this block.
          bypassed_blocks->insert(successor_block);
        }
        dfs_stack.push_back(
            {successor_block, false, GetSuccessors(successor_block), 0});
      }
      node->next_successor++;
    } else {
      // We have finished exploring |node|.  If it is |bb_from|, we can
      // terminate search -- we have grabbed all the relevant blocks.
      if (node->block == bb_from) {
        break;
      }
      dfs_stack.pop_back();
    }
  }
}

bool NewEdgeLeavingConstructBodyRespectsUseDefDominance(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to) {
  // Find those blocks that the edge from |bb_from| to |bb_to| might bypass.
  std::set<opt::BasicBlock*> bypassed_blocks;
  FindBypassedBlocks(context, bb_from, bb_to, &bypassed_blocks);

  // For each bypassed block, check whether it contains a definition that is
  // used by some non-bypassed block - that would be problematic.
  for (auto defining_block : bypassed_blocks) {
    for (auto& inst : *defining_block) {
      if (!context->get_def_use_mgr()->WhileEachUse(
              &inst,
              [context, &bypassed_blocks](opt::Instruction* user,
                                          uint32_t operand_index) -> bool {
                // If this use is in an OpPhi, we need to check that dominance
                // of the relevant *parent* block is not spoiled.  Otherwise we
                // need to check that dominance of the block containing the use
                // is not spoiled.
                opt::BasicBlock* use_block_or_phi_parent =
                    user->opcode() == SpvOpPhi
                        ? context->cfg()->block(
                              user->GetSingleWordOperand(operand_index + 1))
                        : context->get_instr_block(user);

                // There might not be any relevant block, e.g. if the use is in
                // a decoration; in this case the new edge is unproblematic.
                if (use_block_or_phi_parent == nullptr) {
                  return true;
                }

                // If the use-block is not in |bypassed_blocks| then we have
                // found a block in the construct that is reachable from
                // |from_block|, and which defines an id that is used outside of
                // the construct.  Adding an edge from |from_block| to
                // |to_block| would prevent this use being dominated.
                return bypassed_blocks.find(use_block_or_phi_parent) !=
                       bypassed_blocks.end();
              })) {
        return false;
      }
    }
  }
  return true;
}

}  // namespace fuzzerutil

}  // namespace fuzz
}  // namespace spvtools

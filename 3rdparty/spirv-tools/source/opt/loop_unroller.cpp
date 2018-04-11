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

#include "opt/loop_unroller.h"
#include <map>
#include <memory>
#include <utility>
#include "opt/ir_builder.h"
#include "opt/loop_utils.h"

// Implements loop util unrolling functionality for fully and partially
// unrolling loops. Given a factor it will duplicate the loop that many times,
// appending each one to the end of the old loop and removing backedges, to
// create a new unrolled loop.
//
// 1 - User calls LoopUtils::FullyUnroll or LoopUtils::PartiallyUnroll with a
// loop they wish to unroll. LoopUtils::CanPerformUnroll is used to
// validate that a given loop can be unrolled. That method (along with the
// constructor of loop) checks that the IR is in the expected canonicalised
// format.
//
// 2 - The LoopUtils methods create a LoopUnrollerUtilsImpl object to actually
// perform the unrolling. This implements helper methods to copy the loop basic
// blocks and remap the ids of instructions used inside them.
//
// 3 - The core of LoopUnrollerUtilsImpl is the Unroll method, this method
// actually performs the loop duplication. It does this by creating a
// LoopUnrollState object and then copying the loop as given by the factor
// parameter. The LoopUnrollState object retains the state of the unroller
// between the loop body copies as each iteration needs information on the last
// to adjust the phi induction variable, adjust the OpLoopMerge instruction in
// the main loop header, and change the previous continue block to point to the
// new header and the new continue block to the main loop header.
//
// 4 - If the loop is to be fully unrolled then it is simply closed after step
// 3, with the OpLoopMerge being deleted, the backedge removed, and the
// condition blocks folded.
//
// 5 - If it is being partially unrolled: if the unrolling factor leaves the
// loop with an even number of bodies with respect to the number of loop
// iterations then step 3 is all that is needed. If it is uneven then we need to
// duplicate the loop completely and unroll the duplicated loop to cover the
// residual part and adjust the first loop to cover only the "even" part. For
// instance if you request an unroll factor of 3 on a loop with 10 iterations
// then copying the body three times would leave you with three bodies in the
// loop
// where the loop still iterates over each 4 times. So we make two loops one
// iterating once then a second loop of three iterating 3 times.

namespace spvtools {
namespace opt {
namespace {

// Loop control constant value for DontUnroll flag.
static const uint32_t kLoopControlDontUnrollIndex = 2;

// Operand index of the loop control parameter of the OpLoopMerge.
static const uint32_t kLoopControlIndex = 2;

// This utility class encapsulates some of the state we need to maintain between
// loop unrolls. Specifically it maintains key blocks and the induction variable
// in the current loop duplication step and the blocks from the previous one.
// This is because each step of the unroll needs to use data from both the
// preceding step and the original loop.
struct LoopUnrollState {
  LoopUnrollState()
      : previous_phi_(nullptr),
        previous_continue_block_(nullptr),
        previous_condition_block_(nullptr),
        new_phi(nullptr),
        new_continue_block(nullptr),
        new_condition_block(nullptr),
        new_header_block(nullptr) {}

  // Initialize from the loop descriptor class.
  LoopUnrollState(ir::Instruction* induction, ir::BasicBlock* continue_block,
                  ir::BasicBlock* condition,
                  std::vector<ir::Instruction*>&& phis)
      : previous_phi_(induction),
        previous_continue_block_(continue_block),
        previous_condition_block_(condition),
        new_phi(nullptr),
        new_continue_block(nullptr),
        new_condition_block(nullptr),
        new_header_block(nullptr) {
    previous_phis_ = std::move(phis);
  }

  // Swap the state so that the new nodes are now the previous nodes.
  void NextIterationState() {
    previous_phi_ = new_phi;
    previous_continue_block_ = new_continue_block;
    previous_condition_block_ = new_condition_block;
    previous_phis_ = std::move(new_phis_);

    // Clear new nodes.
    new_phi = nullptr;
    new_continue_block = nullptr;
    new_condition_block = nullptr;
    new_header_block = nullptr;

    // Clear new block/instruction maps.
    new_blocks.clear();
    new_inst.clear();
    ids_to_new_inst.clear();
  }

  // The induction variable from the immediately preceding loop body.
  ir::Instruction* previous_phi_;

  // All the phi nodes from the previous loop iteration.
  std::vector<ir::Instruction*> previous_phis_;

  std::vector<ir::Instruction*> new_phis_;
  // The previous continue block. The backedge will be removed from this and
  // added to the new continue block.
  ir::BasicBlock* previous_continue_block_;

  // The previous condition block. This may be folded to flatten the loop.
  ir::BasicBlock* previous_condition_block_;

  // The new induction variable.
  ir::Instruction* new_phi;

  // The new continue block.
  ir::BasicBlock* new_continue_block;

  // The new condition block.
  ir::BasicBlock* new_condition_block;

  // The new header block.
  ir::BasicBlock* new_header_block;

  // A mapping of new block ids to the original blocks which they were copied
  // from.
  std::unordered_map<uint32_t, ir::BasicBlock*> new_blocks;

  // A mapping of the original instruction ids to the instruction ids to their
  // copies.
  std::unordered_map<uint32_t, uint32_t> new_inst;

  std::unordered_map<uint32_t, ir::Instruction*> ids_to_new_inst;
};

// This class implements the actual unrolling. It uses a LoopUnrollState to
// maintain the state of the unrolling inbetween steps.
class LoopUnrollerUtilsImpl {
 public:
  using BasicBlockListTy = std::vector<std::unique_ptr<ir::BasicBlock>>;

  LoopUnrollerUtilsImpl(ir::IRContext* c, ir::Function* function)
      : context_(c),
        function_(*function),
        loop_condition_block_(nullptr),
        loop_induction_variable_(nullptr),
        number_of_loop_iterations_(0),
        loop_step_value_(0),
        loop_init_value_(0) {}

  // Unroll the |loop| by given |factor| by copying the whole body |factor|
  // times. The resulting basicblock structure will remain a loop.
  void PartiallyUnroll(ir::Loop*, size_t factor);

  // If partially unrolling the |loop| would leave the loop with too many bodies
  // for its number of iterations then this method should be used. This method
  // will duplicate the |loop| completely, making the duplicated loop the
  // successor of the original's merge block. The original loop will have its
  // condition changed to loop over the residual part and the duplicate will be
  // partially unrolled. The resulting structure will be two loops.
  void PartiallyUnrollResidualFactor(ir::Loop* loop, size_t factor);

  // Fully unroll the |loop| by copying the full body by the total number of
  // loop iterations, folding all conditions, and removing the backedge from the
  // continue block to the header.
  void FullyUnroll(ir::Loop* loop);

  // Get the ID of the variable in the |phi| paired with |label|.
  uint32_t GetPhiDefID(const ir::Instruction* phi, uint32_t label) const;

  // Close the loop by removing the OpLoopMerge from the |loop| header block and
  // making the backedge point to the merge block.
  void CloseUnrolledLoop(ir::Loop* loop);

  // Remove the OpConditionalBranch instruction inside |conditional_block| used
  // to branch to either exit or continue the loop and replace it with an
  // unconditional OpBranch to block |new_target|.
  void FoldConditionBlock(ir::BasicBlock* condtion_block, uint32_t new_target);

  // Add all blocks_to_add_ to function_ at the |insert_point|.
  void AddBlocksToFunction(const ir::BasicBlock* insert_point);

  // Duplicates the |old_loop|, cloning each body and remaping the ids without
  // removing instructions or changing relative structure. Result will be stored
  // in |new_loop|.
  void DuplicateLoop(ir::Loop* old_loop, ir::Loop* new_loop);

  inline size_t GetLoopIterationCount() const {
    return number_of_loop_iterations_;
  }

  // Extracts the initial state information from the |loop|.
  void Init(ir::Loop* loop);

  // Replace the uses of each induction variable outside the loop with the final
  // value of the induction variable before the loop exit. To reflect the proper
  // state of a fully unrolled loop.
  void ReplaceInductionUseWithFinalValue(ir::Loop* loop);

  // Remove all the instructions in the invalidated_instructions_ vector.
  void RemoveDeadInstructions();

  // Replace any use of induction variables outwith the loop with the final
  // value of the induction variable in the unrolled loop.
  void ReplaceOutsideLoopUseWithFinalValue(ir::Loop* loop);

  // Set the LoopControl operand of the OpLoopMerge instruction to be
  // DontUnroll.
  void MarkLoopControlAsDontUnroll(ir::Loop* loop) const;

 private:
  // Remap all the in |basic_block| to new IDs and keep the mapping of new ids
  // to old
  // ids. |loop| is used to identify special loop blocks (header, continue,
  // ect).
  void AssignNewResultIds(ir::BasicBlock* basic_block);

  // Using the map built by AssignNewResultIds, for each instruction in
  // |basic_block| use
  // that map to substitute the IDs used by instructions (in the operands) with
  // the new ids.
  void RemapOperands(ir::BasicBlock* basic_block);

  // Copy the whole body of the loop, all blocks dominated by the |loop| header
  // and not dominated by the |loop| merge. The copied body will be linked to by
  // the old |loop| continue block and the new body will link to the |loop|
  // header via the new continue block. |eliminate_conditions| is used to decide
  // whether or not to fold all the condition blocks other than the last one.
  void CopyBody(ir::Loop* loop, bool eliminate_conditions);

  // Copy a given |block_to_copy| in the |loop| and record the mapping of the
  // old/new ids. |preserve_instructions| determines whether or not the method
  // will modify (other than result_id) instructions which are copied.
  void CopyBasicBlock(ir::Loop* loop, const ir::BasicBlock* block_to_copy,
                      bool preserve_instructions);

  // The actual implementation of the unroll step. Unrolls |loop| by given
  // |factor| by copying the body by |factor| times. Also propagates the
  // induction variable value throughout the copies.
  void Unroll(ir::Loop* loop, size_t factor);

  // Fills the loop_blocks_inorder_ field with the ordered list of basic blocks
  // as computed by the method ComputeLoopOrderedBlocks.
  void ComputeLoopOrderedBlocks(ir::Loop* loop);

  // Adds the blocks_to_add_ to both the |loop| and to the parent of |loop| if
  // the parent exists.
  void AddBlocksToLoop(ir::Loop* loop) const;

  // After the partially unroll step the phi instructions in the header block
  // will be in an illegal format. This function makes the phis legal by making
  // the edge from the latch block come from the new latch block and the value
  // to be the actual value of the phi at that point.
  void LinkLastPhisToStart(ir::Loop* loop) const;

  // A pointer to the IRContext. Used to add/remove instructions and for usedef
  // chains.
  ir::IRContext* context_;

  // A reference the function the loop is within.
  ir::Function& function_;

  // A list of basic blocks to be added to the loop at the end of an unroll
  // step.
  BasicBlockListTy blocks_to_add_;

  // List of instructions which are now dead and can be removed.
  std::vector<ir::Instruction*> invalidated_instructions_;

  // Maintains the current state of the transform between calls to unroll.
  LoopUnrollState state_;

  // An ordered list containing the loop basic blocks.
  std::vector<ir::BasicBlock*> loop_blocks_inorder_;

  // The block containing the condition check which contains a conditional
  // branch to the merge and continue block.
  ir::BasicBlock* loop_condition_block_;

  // The induction variable of the loop.
  ir::Instruction* loop_induction_variable_;

  // Phis used in the loop need to be remapped to use the actual result values
  // and then be remapped at the end.
  std::vector<ir::Instruction*> loop_phi_instructions_;

  // The number of loop iterations that the loop would preform pre-unroll.
  size_t number_of_loop_iterations_;

  // The amount that the loop steps each iteration.
  int64_t loop_step_value_;

  // The value the loop starts stepping from.
  int64_t loop_init_value_;
};

/*
 * Static helper functions.
 */

// Retrieve the index of the OpPhi instruction |phi| which corresponds to the
// incoming |block| id.
static uint32_t GetPhiIndexFromLabel(const ir::BasicBlock* block,
                                     const ir::Instruction* phi) {
  for (uint32_t i = 1; i < phi->NumInOperands(); i += 2) {
    if (block->id() == phi->GetSingleWordInOperand(i)) {
      return i;
    }
  }
  assert(false && "Could not find operand in instruction.");
  return 0;
}

void LoopUnrollerUtilsImpl::Init(ir::Loop* loop) {
  loop_condition_block_ = loop->FindConditionBlock();

  // When we reinit the second loop during PartiallyUnrollResidualFactor we need
  // to use the cached value from the duplicate step as the dominator tree
  // basded solution, loop->FindConditionBlock, requires all the nodes to be
  // connected up with the correct branches. They won't be at this point.
  if (!loop_condition_block_) {
    loop_condition_block_ = state_.new_condition_block;
  }
  assert(loop_condition_block_);

  loop_induction_variable_ = loop->FindConditionVariable(loop_condition_block_);
  assert(loop_induction_variable_);

  bool found = loop->FindNumberOfIterations(
      loop_induction_variable_, &*loop_condition_block_->ctail(),
      &number_of_loop_iterations_, &loop_step_value_, &loop_init_value_);
  (void)found;  // To silence unused variable warning on release builds.
  assert(found);

  // Blocks are stored in an unordered set of ids in the loop class, we need to
  // create the dominator ordered list.
  ComputeLoopOrderedBlocks(loop);
}

// This function is used to partially unroll the loop when the factor provided
// would normally lead to an illegal optimization. Instead of just unrolling the
// loop it creates two loops and unrolls one and adjusts the condition on the
// other. The end result being that the new loop pair iterates over the correct
// number of bodies.
void LoopUnrollerUtilsImpl::PartiallyUnrollResidualFactor(ir::Loop* loop,
                                                          size_t factor) {
  std::unique_ptr<ir::Instruction> new_label{new ir::Instruction(
      context_, SpvOp::SpvOpLabel, 0, context_->TakeNextId(), {})};
  std::unique_ptr<ir::BasicBlock> new_exit_bb{
      new ir::BasicBlock(std::move(new_label))};

  // Save the id of the block before we move it.
  uint32_t new_merge_id = new_exit_bb->id();

  // Add the block the list of blocks to add, we want this merge block to be
  // right at the start of the new blocks.
  blocks_to_add_.push_back(std::move(new_exit_bb));
  ir::BasicBlock* new_exit_bb_raw = blocks_to_add_[0].get();
  ir::Instruction& original_conditional_branch = *loop_condition_block_->tail();
  // Duplicate the loop, providing access to the blocks of both loops.
  // This is a naked new due to the VS2013 requirement of not having unique
  // pointers in vectors, as it will be inserted into a vector with
  // loop_descriptor.AddLoop.
  ir::Loop* new_loop = new ir::Loop(*loop);

  // Clear the basic blocks of the new loop.
  new_loop->ClearBlocks();

  DuplicateLoop(loop, new_loop);

  // Add the blocks to the function.
  AddBlocksToFunction(loop->GetMergeBlock());
  blocks_to_add_.clear();

  // Create a new merge block for the first loop.
  InstructionBuilder builder{context_, new_exit_bb_raw};
  // Make the first loop branch to the second.
  builder.AddBranch(new_loop->GetHeaderBlock()->id());

  loop_condition_block_ = state_.new_condition_block;
  loop_induction_variable_ = state_.new_phi;
  // Unroll the new loop by the factor with the usual -1 to account for the
  // existing block iteration.
  Unroll(new_loop, factor);

  LinkLastPhisToStart(new_loop);
  AddBlocksToLoop(new_loop);

  // Add the new merge block to the back of the list of blocks to be added. It
  // needs to be the last block added to maintain dominator order in the binary.
  blocks_to_add_.push_back(
      std::unique_ptr<ir::BasicBlock>(new_loop->GetMergeBlock()));

  // Add the blocks to the function.
  AddBlocksToFunction(loop->GetMergeBlock());

  // Reset the usedef analysis.
  context_->InvalidateAnalysesExceptFor(
      ir::IRContext::Analysis::kAnalysisLoopAnalysis);
  opt::analysis::DefUseManager* def_use_manager = context_->get_def_use_mgr();

  // The loop condition.
  ir::Instruction* condition_check = def_use_manager->GetDef(
      original_conditional_branch.GetSingleWordOperand(0));

  // This should have been checked by the LoopUtils::CanPerformUnroll function
  // before entering this.
  assert(loop->IsSupportedCondition(condition_check->opcode()));

  // We need to account for the initial body when calculating the remainder.
  int64_t remainder = ir::Loop::GetResidualConditionValue(
      condition_check->opcode(), loop_init_value_, loop_step_value_,
      number_of_loop_iterations_, factor);

  assert(remainder > std::numeric_limits<int32_t>::min() &&
         remainder < std::numeric_limits<int32_t>::max());

  ir::Instruction* new_constant = nullptr;

  // If the remainder is negative then we add a signed constant, otherwise just
  // add an unsigned constant.
  if (remainder < 0) {
    new_constant =
        builder.Add32BitSignedIntegerConstant(static_cast<int32_t>(remainder));
  } else {
    new_constant = builder.Add32BitUnsignedIntegerConstant(
        static_cast<int32_t>(remainder));
  }

  uint32_t constant_id = new_constant->result_id();

  // Update the condition check.
  condition_check->SetInOperand(1, {constant_id});

  // Update the next phi node. The phi will have a constant value coming in from
  // the preheader block. For the duplicated loop we need to update the constant
  // to be the amount of iterations covered by the first loop and the incoming
  // block to be the first loops new merge block.
  std::vector<ir::Instruction*> new_inductions;
  new_loop->GetInductionVariables(new_inductions);

  std::vector<ir::Instruction*> old_inductions;
  loop->GetInductionVariables(old_inductions);
  for (size_t index = 0; index < new_inductions.size(); ++index) {
    ir::Instruction* new_induction = new_inductions[index];
    ir::Instruction* old_induction = old_inductions[index];
    // Get the index of the loop initalizer, the value coming in from the
    // preheader.
    uint32_t initalizer_index =
        GetPhiIndexFromLabel(new_loop->GetPreHeaderBlock(), old_induction);

    // Replace the second loop initalizer with the phi from the first
    new_induction->SetInOperand(initalizer_index - 1,
                                {old_induction->result_id()});
    new_induction->SetInOperand(initalizer_index, {new_merge_id});

    // If the use of the first loop induction variable is outside of the loop
    // then replace that use with the second loop induction variable.
    uint32_t second_loop_induction = new_induction->result_id();
    auto replace_use_outside_of_loop = [loop, second_loop_induction](
                                           ir::Instruction* user,
                                           uint32_t operand_index) {
      if (!loop->IsInsideLoop(user)) {
        user->SetOperand(operand_index, {second_loop_induction});
      }
    };

    context_->get_def_use_mgr()->ForEachUse(old_induction,
                                            replace_use_outside_of_loop);
  }

  context_->InvalidateAnalysesExceptFor(
      ir::IRContext::Analysis::kAnalysisLoopAnalysis);

  context_->ReplaceAllUsesWith(loop->GetMergeBlock()->id(), new_merge_id);

  ir::LoopDescriptor& loop_descriptor =
      *context_->GetLoopDescriptor(&function_);

  loop_descriptor.AddLoop(new_loop, loop->GetParent());

  RemoveDeadInstructions();
}

// Mark this loop as DontUnroll as it will already be unrolled and it may not
// be safe to unroll a previously partially unrolled loop.
void LoopUnrollerUtilsImpl::MarkLoopControlAsDontUnroll(ir::Loop* loop) const {
  ir::Instruction* loop_merge_inst = loop->GetHeaderBlock()->GetLoopMergeInst();
  assert(loop_merge_inst &&
         "Loop merge instruction could not be found after entering unroller "
         "(should have exited before this)");
  loop_merge_inst->SetInOperand(kLoopControlIndex,
                                {kLoopControlDontUnrollIndex});
}

// Duplicate the |loop| body |factor| - 1 number of times while keeping the loop
// backedge intact. This will leave the loop with |factor| number of bodies
// after accounting for the initial body.
void LoopUnrollerUtilsImpl::Unroll(ir::Loop* loop, size_t factor) {
  // If we unroll a loop partially it will not be safe to unroll it further.
  // This is due to the current method of calculating the number of loop
  // iterations.
  MarkLoopControlAsDontUnroll(loop);

  std::vector<ir::Instruction*> inductions;
  loop->GetInductionVariables(inductions);
  state_ = LoopUnrollState{loop_induction_variable_, loop->GetLatchBlock(),
                           loop_condition_block_, std::move(inductions)};
  for (size_t i = 0; i < factor - 1; ++i) {
    CopyBody(loop, true);
  }
}

void LoopUnrollerUtilsImpl::RemoveDeadInstructions() {
  // Remove the dead instructions.
  for (ir::Instruction* inst : invalidated_instructions_) {
    context_->KillInst(inst);
  }
}

void LoopUnrollerUtilsImpl::ReplaceInductionUseWithFinalValue(ir::Loop* loop) {
  context_->InvalidateAnalysesExceptFor(
      ir::IRContext::Analysis::kAnalysisLoopAnalysis);
  std::vector<ir::Instruction*> inductions;
  loop->GetInductionVariables(inductions);

  for (size_t index = 0; index < inductions.size(); ++index) {
    uint32_t trip_step_id = GetPhiDefID(state_.previous_phis_[index],
                                        state_.previous_continue_block_->id());
    context_->ReplaceAllUsesWith(inductions[index]->result_id(), trip_step_id);
    invalidated_instructions_.push_back(inductions[index]);
  }
}

// Fully unroll the loop by partially unrolling it by the number of loop
// iterations minus one for the body already accounted for.
void LoopUnrollerUtilsImpl::FullyUnroll(ir::Loop* loop) {
  // We unroll the loop by number of iterations in the loop.
  Unroll(loop, number_of_loop_iterations_);

  // The first condition block is preserved until now so it can be copied.
  FoldConditionBlock(loop_condition_block_, 1);

  // Delete the OpLoopMerge and remove the backedge to the header.
  CloseUnrolledLoop(loop);

  // Mark the loop for later deletion. This allows us to preserve the loop
  // iterators but still disregard dead loops.
  loop->MarkLoopForRemoval();

  // If the loop has a parent add the new blocks to the parent.
  if (loop->GetParent()) {
    AddBlocksToLoop(loop->GetParent());
  }

  // Add the blocks to the function.
  AddBlocksToFunction(loop->GetMergeBlock());

  ReplaceInductionUseWithFinalValue(loop);

  RemoveDeadInstructions();
  // Invalidate all analyses.
  context_->InvalidateAnalysesExceptFor(
      ir::IRContext::Analysis::kAnalysisLoopAnalysis);
}

// Copy a given basic block, give it a new result_id, and store the new block
// and the id mapping in the state. |preserve_instructions| is used to determine
// whether or not this function should edit instructions other than the
// |result_id|.
void LoopUnrollerUtilsImpl::CopyBasicBlock(ir::Loop* loop,
                                           const ir::BasicBlock* itr,
                                           bool preserve_instructions) {
  // Clone the block exactly, including the IDs.
  ir::BasicBlock* basic_block = itr->Clone(context_);
  basic_block->SetParent(itr->GetParent());

  // Assign each result a new unique ID and keep a mapping of the old ids to
  // the new ones.
  AssignNewResultIds(basic_block);

  // If this is the continue block we are copying.
  if (itr == loop->GetLatchBlock()) {
    // Make the OpLoopMerge point to this block for the continue.
    if (!preserve_instructions) {
      ir::Instruction* merge_inst = loop->GetHeaderBlock()->GetLoopMergeInst();
      merge_inst->SetInOperand(1, {basic_block->id()});
    }

    state_.new_continue_block = basic_block;
  }

  // If this is the header block we are copying.
  if (itr == loop->GetHeaderBlock()) {
    state_.new_header_block = basic_block;

    if (!preserve_instructions) {
      // Remove the loop merge instruction if it exists.
      ir::Instruction* merge_inst = basic_block->GetLoopMergeInst();
      if (merge_inst) invalidated_instructions_.push_back(merge_inst);
    }
  }

  // If this is the condition block we are copying.
  if (itr == loop_condition_block_) {
    state_.new_condition_block = basic_block;
  }

  // Add this block to the list of blocks to add to the function at the end of
  // the unrolling process.
  blocks_to_add_.push_back(std::unique_ptr<ir::BasicBlock>(basic_block));

  // Keep tracking the old block via a map.
  state_.new_blocks[itr->id()] = basic_block;
}

void LoopUnrollerUtilsImpl::CopyBody(ir::Loop* loop,
                                     bool eliminate_conditions) {
  // Copy each basic block in the loop, give them new ids, and save state
  // information.
  for (const ir::BasicBlock* itr : loop_blocks_inorder_) {
    CopyBasicBlock(loop, itr, false);
  }

  // Set the previous continue block to point to the new header.
  ir::Instruction& continue_branch = *state_.previous_continue_block_->tail();
  continue_branch.SetInOperand(0, {state_.new_header_block->id()});

  // As the algorithm copies the original loop blocks exactly, the tail of the
  // latch block on iterations after the first one will be a branch to the new
  // header and not the actual loop header. The last continue block in the loop
  // should always be a backedge to the global header.
  ir::Instruction& new_continue_branch = *state_.new_continue_block->tail();
  new_continue_branch.SetInOperand(0, {loop->GetHeaderBlock()->id()});

  std::vector<ir::Instruction*> inductions;
  loop->GetInductionVariables(inductions);
  for (size_t index = 0; index < inductions.size(); ++index) {
    ir::Instruction* master_copy = inductions[index];

    assert(master_copy->result_id() != 0);
    ir::Instruction* induction_clone =
        state_.ids_to_new_inst[state_.new_inst[master_copy->result_id()]];

    state_.new_phis_.push_back(induction_clone);
    assert(induction_clone->result_id() != 0);

    if (!state_.previous_phis_.empty()) {
      state_.new_inst[master_copy->result_id()] = GetPhiDefID(
          state_.previous_phis_[index], state_.previous_continue_block_->id());
    } else {
      // Do not replace the first phi block ids.
      state_.new_inst[master_copy->result_id()] = master_copy->result_id();
    }
  }

  if (eliminate_conditions &&
      state_.new_condition_block != loop_condition_block_) {
    FoldConditionBlock(state_.new_condition_block, 1);
  }

  // Only reference to the header block is the backedge in the latch block,
  // don't change this.
  state_.new_inst[loop->GetHeaderBlock()->id()] = loop->GetHeaderBlock()->id();

  for (auto& pair : state_.new_blocks) {
    RemapOperands(pair.second);
  }

  for (ir::Instruction* dead_phi : state_.new_phis_)
    invalidated_instructions_.push_back(dead_phi);

  // Swap the state so the new is now the previous.
  state_.NextIterationState();
}

uint32_t LoopUnrollerUtilsImpl::GetPhiDefID(const ir::Instruction* phi,
                                            uint32_t label) const {
  for (uint32_t operand = 3; operand < phi->NumOperands(); operand += 2) {
    if (phi->GetSingleWordOperand(operand) == label) {
      return phi->GetSingleWordOperand(operand - 1);
    }
  }
  assert(false && "Could not find a phi index matching the provided label");
  return 0;
}

void LoopUnrollerUtilsImpl::FoldConditionBlock(ir::BasicBlock* condition_block,
                                               uint32_t operand_label) {
  // Remove the old conditional branch to the merge and continue blocks.
  ir::Instruction& old_branch = *condition_block->tail();
  uint32_t new_target = old_branch.GetSingleWordOperand(operand_label);

  context_->KillInst(&old_branch);
  // Add the new unconditional branch to the merge block.
  InstructionBuilder builder{context_, condition_block};
  builder.AddBranch(new_target);
}

void LoopUnrollerUtilsImpl::CloseUnrolledLoop(ir::Loop* loop) {
  // Remove the OpLoopMerge instruction from the function.
  ir::Instruction* merge_inst = loop->GetHeaderBlock()->GetLoopMergeInst();
  invalidated_instructions_.push_back(merge_inst);

  // Remove the final backedge to the header and make it point instead to the
  // merge block.
  state_.previous_continue_block_->tail()->SetInOperand(
      0, {loop->GetMergeBlock()->id()});

  // Remove all induction variables as the phis will now be invalid. Replace all
  // uses with the constant initializer value (all uses of phis will be in
  // the first iteration with the subsequent phis already having been removed).
  std::vector<ir::Instruction*> inductions;
  loop->GetInductionVariables(inductions);

  // We can use the state instruction mechanism to replace all internal loop
  // values within the first loop trip (as the subsequent ones will be updated
  // by the copy function) with the value coming in from the preheader and then
  // use context ReplaceAllUsesWith for the uses outside the loop with the final
  // trip phi value.
  state_.new_inst.clear();
  for (ir::Instruction* induction : inductions) {
    uint32_t initalizer_id =
        GetPhiDefID(induction, loop->GetPreHeaderBlock()->id());

    state_.new_inst[induction->result_id()] = initalizer_id;
  }

  for (ir::BasicBlock* block : loop_blocks_inorder_) {
    RemapOperands(block);
  }
}

// Uses the first loop to create a copy of the loop with new IDs.
void LoopUnrollerUtilsImpl::DuplicateLoop(ir::Loop* old_loop,
                                          ir::Loop* new_loop) {
  std::vector<ir::BasicBlock*> new_block_order;

  // Copy every block in the old loop.
  for (const ir::BasicBlock* itr : loop_blocks_inorder_) {
    CopyBasicBlock(old_loop, itr, true);
    new_block_order.push_back(blocks_to_add_.back().get());
  }

  // Clone the merge block, give it a new id and record it in the state.
  ir::BasicBlock* new_merge = old_loop->GetMergeBlock()->Clone(context_);
  new_merge->SetParent(old_loop->GetMergeBlock()->GetParent());
  AssignNewResultIds(new_merge);
  state_.new_blocks[old_loop->GetMergeBlock()->id()] = new_merge;

  // Remap the operands of every instruction in the loop to point to the new
  // copies.
  for (auto& pair : state_.new_blocks) {
    RemapOperands(pair.second);
  }

  loop_blocks_inorder_ = std::move(new_block_order);

  AddBlocksToLoop(new_loop);

  new_loop->SetHeaderBlock(state_.new_header_block);
  new_loop->SetLatchBlock(state_.new_continue_block);
  new_loop->SetMergeBlock(new_merge);
}

// Whenever the utility copies a block it stores it in a tempory buffer, this
// function adds the buffer into the ir::Function. The blocks will be inserted
// after the block |insert_point|.
void LoopUnrollerUtilsImpl::AddBlocksToFunction(
    const ir::BasicBlock* insert_point) {
  for (auto basic_block_iterator = function_.begin();
       basic_block_iterator != function_.end(); ++basic_block_iterator) {
    if (basic_block_iterator->id() == insert_point->id()) {
      basic_block_iterator.InsertBefore(&blocks_to_add_);
      return;
    }
  }

  assert(
      false &&
      "Could not add basic blocks to function as insert point was not found.");
}

// Assign all result_ids in |basic_block| instructions to new IDs and preserve
// the mapping of new ids to old ones.
void LoopUnrollerUtilsImpl::AssignNewResultIds(ir::BasicBlock* basic_block) {
  // Label instructions aren't covered by normal traversal of the
  // instructions.
  uint32_t new_label_id = context_->TakeNextId();

  // Assign a new id to the label.
  state_.new_inst[basic_block->GetLabelInst()->result_id()] = new_label_id;
  basic_block->GetLabelInst()->SetResultId(new_label_id);

  for (ir::Instruction& inst : *basic_block) {
    uint32_t old_id = inst.result_id();

    // Ignore stores etc.
    if (old_id == 0) {
      continue;
    }

    // Give the instruction a new id.
    inst.SetResultId(context_->TakeNextId());

    // Save the mapping of old_id -> new_id.
    state_.new_inst[old_id] = inst.result_id();
    // Check if this instruction is the induction variable.
    if (loop_induction_variable_->result_id() == old_id) {
      // Save a pointer to the new copy of it.
      state_.new_phi = &inst;
    }
    state_.ids_to_new_inst[inst.result_id()] = &inst;
  }
}

// For all instructions in |basic_block| check if the operands used are from a
// copied instruction and if so swap out the operand for the copy of it.
void LoopUnrollerUtilsImpl::RemapOperands(ir::BasicBlock* basic_block) {
  for (ir::Instruction& inst : *basic_block) {
    auto remap_operands_to_new_ids = [this](uint32_t* id) {
      auto itr = state_.new_inst.find(*id);

      if (itr != state_.new_inst.end()) {
        *id = itr->second;
      }
    };

    inst.ForEachInId(remap_operands_to_new_ids);
  }
}

// Generate the ordered list of basic blocks in the |loop| and cache it for
// later use.
void LoopUnrollerUtilsImpl::ComputeLoopOrderedBlocks(ir::Loop* loop) {
  loop_blocks_inorder_.clear();
  loop->ComputeLoopStructuredOrder(&loop_blocks_inorder_);
}

// Adds the blocks_to_add_ to both the loop and to the parent.
void LoopUnrollerUtilsImpl::AddBlocksToLoop(ir::Loop* loop) const {
  // Add the blocks to this loop.
  for (auto& block_itr : blocks_to_add_) {
    loop->AddBasicBlock(block_itr.get());
  }

  // Add the blocks to the parent as well.
  if (loop->GetParent()) AddBlocksToLoop(loop->GetParent());
}

void LoopUnrollerUtilsImpl::LinkLastPhisToStart(ir::Loop* loop) const {
  std::vector<ir::Instruction*> inductions;
  loop->GetInductionVariables(inductions);

  for (size_t i = 0; i < inductions.size(); ++i) {
    ir::Instruction* last_phi_in_block = state_.previous_phis_[i];

    uint32_t phi_index = GetPhiIndexFromLabel(state_.previous_continue_block_,
                                              last_phi_in_block);
    uint32_t phi_variable =
        last_phi_in_block->GetSingleWordInOperand(phi_index - 1);
    uint32_t phi_label = last_phi_in_block->GetSingleWordInOperand(phi_index);

    ir::Instruction* phi = inductions[i];
    phi->SetInOperand(phi_index - 1, {phi_variable});
    phi->SetInOperand(phi_index, {phi_label});
  }
}

// Duplicate the |loop| body |factor| number of times while keeping the loop
// backedge intact.
void LoopUnrollerUtilsImpl::PartiallyUnroll(ir::Loop* loop, size_t factor) {
  Unroll(loop, factor);
  LinkLastPhisToStart(loop);
  AddBlocksToLoop(loop);
  AddBlocksToFunction(loop->GetMergeBlock());
  RemoveDeadInstructions();
}

/*
 * End LoopUtilsImpl.
 */

}  // namespace

/*
 *
 *  Begin Utils.
 *
 * */

bool LoopUtils::CanPerformUnroll() {
  // The loop is expected to be in structured order.
  if (!loop_->GetHeaderBlock()->GetMergeInst()) {
    return false;
  }

  // Find check the loop has a condition we can find and evaluate.
  const ir::BasicBlock* condition = loop_->FindConditionBlock();
  if (!condition) return false;

  // Check that we can find and process the induction variable.
  const ir::Instruction* induction = loop_->FindConditionVariable(condition);
  if (!induction || induction->opcode() != SpvOpPhi) return false;

  // Check that we can find the number of loop iterations.
  if (!loop_->FindNumberOfIterations(induction, &*condition->ctail(), nullptr))
    return false;

  // Make sure the continue block is a unconditional branch to the header
  // block.
  const ir::Instruction& branch = *loop_->GetLatchBlock()->ctail();
  bool branching_assumption =
      branch.opcode() == SpvOpBranch &&
      branch.GetSingleWordInOperand(0) == loop_->GetHeaderBlock()->id();
  if (!branching_assumption) {
    return false;
  }

  std::vector<ir::Instruction*> inductions;
  loop_->GetInductionVariables(inductions);

  // Ban breaks within the loop.
  const std::vector<uint32_t>& merge_block_preds =
      context_->cfg()->preds(loop_->GetMergeBlock()->id());
  if (merge_block_preds.size() != 1) {
    return false;
  }

  // Ban continues within the loop.
  const std::vector<uint32_t>& continue_block_preds =
      context_->cfg()->preds(loop_->GetLatchBlock()->id());
  if (continue_block_preds.size() != 1) {
    return false;
  }

  // Ban returns in the loop.
  // Iterate over all the blocks within the loop and check that none of them
  // exit the loop.
  for (uint32_t label_id : loop_->GetBlocks()) {
    const ir::BasicBlock* block = context_->cfg()->block(label_id);
    if (block->ctail()->opcode() == SpvOp::SpvOpKill ||
        block->ctail()->opcode() == SpvOp::SpvOpReturn ||
        block->ctail()->opcode() == SpvOp::SpvOpReturnValue) {
      return false;
    }
  }
  // Can only unroll inner loops.
  if (!loop_->AreAllChildrenMarkedForRemoval()) {
    return false;
  }

  return true;
}

bool LoopUtils::PartiallyUnroll(size_t factor) {
  if (factor == 1 || !CanPerformUnroll()) return false;

  // Create the unroller utility.
  LoopUnrollerUtilsImpl unroller{context_,
                                 loop_->GetHeaderBlock()->GetParent()};
  unroller.Init(loop_);

  // If the unrolling factor is larger than or the same size as the loop just
  // fully unroll the loop.
  if (factor >= unroller.GetLoopIterationCount()) {
    unroller.FullyUnroll(loop_);
    return true;
  }

  // If the loop unrolling factor is an residual number of iterations we need to
  // let run the loop for the residual part then let it branch into the unrolled
  // remaining part. We add one when calucating the remainder to take into
  // account the one iteration already in the loop.
  if (unroller.GetLoopIterationCount() % factor != 0) {
    unroller.PartiallyUnrollResidualFactor(loop_, factor);
  } else {
    unroller.PartiallyUnroll(loop_, factor);
  }

  return true;
}

bool LoopUtils::FullyUnroll() {
  if (!CanPerformUnroll()) return false;

  std::vector<ir::Instruction*> inductions;
  loop_->GetInductionVariables(inductions);

  LoopUnrollerUtilsImpl unroller{context_,
                                 loop_->GetHeaderBlock()->GetParent()};

  unroller.Init(loop_);
  unroller.FullyUnroll(loop_);

  return true;
}

void LoopUtils::Finalize() {
  // Clean up the loop descriptor to preserve the analysis.

  ir::LoopDescriptor* LD = context_->GetLoopDescriptor(&function_);
  LD->PostModificationCleanup();
}

/*
 *
 * Begin Pass.
 *
 */

Pass::Status LoopUnroller::Process(ir::IRContext* c) {
  context_ = c;
  bool changed = false;
  for (ir::Function& f : *c->module()) {
    ir::LoopDescriptor* LD = context_->GetLoopDescriptor(&f);
    for (ir::Loop& loop : *LD) {
      LoopUtils loop_utils{c, &loop};
      if (!loop.HasUnrollLoopControl() || !loop_utils.CanPerformUnroll()) {
        continue;
      }

      if (fully_unroll_) {
        loop_utils.FullyUnroll();
      } else {
        loop_utils.PartiallyUnroll(unroll_factor_);
      }
      changed = true;
    }
    LD->PostModificationCleanup();
  }

  return changed ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

}  // namespace opt
}  // namespace spvtools

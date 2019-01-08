// Copyright (c) 2018 The Khronos Group Inc.
// Copyright (c) 2018 Valve Corporation
// Copyright (c) 2018 LunarG Inc.
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

#include "inst_bindless_check_pass.h"

namespace {

// Input Operand Indices
static const int kSpvImageSampleImageIdInIdx = 0;
static const int kSpvSampledImageImageIdInIdx = 0;
static const int kSpvSampledImageSamplerIdInIdx = 1;
static const int kSpvImageSampledImageIdInIdx = 0;
static const int kSpvLoadPtrIdInIdx = 0;
static const int kSpvAccessChainBaseIdInIdx = 0;
static const int kSpvAccessChainIndex0IdInIdx = 1;
static const int kSpvTypePointerTypeIdInIdx = 1;
static const int kSpvTypeArrayLengthIdInIdx = 1;
static const int kSpvConstantValueInIdx = 0;

}  // anonymous namespace

namespace spvtools {
namespace opt {

void InstBindlessCheckPass::GenBindlessCheckCode(
    BasicBlock::iterator ref_inst_itr,
    UptrVectorIterator<BasicBlock> ref_block_itr, uint32_t instruction_idx,
    uint32_t stage_idx, std::vector<std::unique_ptr<BasicBlock>>* new_blocks) {
  // Look for reference through bindless descriptor. If not, return.
  std::unique_ptr<BasicBlock> new_blk_ptr;
  uint32_t image_id;
  switch (ref_inst_itr->opcode()) {
    case SpvOp::SpvOpImageSampleImplicitLod:
    case SpvOp::SpvOpImageSampleExplicitLod:
    case SpvOp::SpvOpImageSampleDrefImplicitLod:
    case SpvOp::SpvOpImageSampleDrefExplicitLod:
    case SpvOp::SpvOpImageSampleProjImplicitLod:
    case SpvOp::SpvOpImageSampleProjExplicitLod:
    case SpvOp::SpvOpImageSampleProjDrefImplicitLod:
    case SpvOp::SpvOpImageSampleProjDrefExplicitLod:
    case SpvOp::SpvOpImageGather:
    case SpvOp::SpvOpImageDrefGather:
    case SpvOp::SpvOpImageQueryLod:
    case SpvOp::SpvOpImageSparseSampleImplicitLod:
    case SpvOp::SpvOpImageSparseSampleExplicitLod:
    case SpvOp::SpvOpImageSparseSampleDrefImplicitLod:
    case SpvOp::SpvOpImageSparseSampleDrefExplicitLod:
    case SpvOp::SpvOpImageSparseSampleProjImplicitLod:
    case SpvOp::SpvOpImageSparseSampleProjExplicitLod:
    case SpvOp::SpvOpImageSparseSampleProjDrefImplicitLod:
    case SpvOp::SpvOpImageSparseSampleProjDrefExplicitLod:
    case SpvOp::SpvOpImageSparseGather:
    case SpvOp::SpvOpImageSparseDrefGather:
    case SpvOp::SpvOpImageFetch:
    case SpvOp::SpvOpImageRead:
    case SpvOp::SpvOpImageQueryFormat:
    case SpvOp::SpvOpImageQueryOrder:
    case SpvOp::SpvOpImageQuerySizeLod:
    case SpvOp::SpvOpImageQuerySize:
    case SpvOp::SpvOpImageQueryLevels:
    case SpvOp::SpvOpImageQuerySamples:
    case SpvOp::SpvOpImageSparseFetch:
    case SpvOp::SpvOpImageSparseRead:
    case SpvOp::SpvOpImageWrite:
      image_id =
          ref_inst_itr->GetSingleWordInOperand(kSpvImageSampleImageIdInIdx);
      break;
    default:
      return;
  }
  Instruction* image_inst = get_def_use_mgr()->GetDef(image_id);
  uint32_t load_id;
  Instruction* load_inst;
  if (image_inst->opcode() == SpvOp::SpvOpSampledImage) {
    load_id = image_inst->GetSingleWordInOperand(kSpvSampledImageImageIdInIdx);
    load_inst = get_def_use_mgr()->GetDef(load_id);
  } else if (image_inst->opcode() == SpvOp::SpvOpImage) {
    load_id = image_inst->GetSingleWordInOperand(kSpvImageSampledImageIdInIdx);
    load_inst = get_def_use_mgr()->GetDef(load_id);
  } else {
    load_id = image_id;
    load_inst = image_inst;
    image_id = 0;
  }
  if (load_inst->opcode() != SpvOp::SpvOpLoad) {
    // TODO(greg-lunarg): Handle additional possibilities
    return;
  }
  uint32_t ptr_id = load_inst->GetSingleWordInOperand(kSpvLoadPtrIdInIdx);
  Instruction* ptr_inst = get_def_use_mgr()->GetDef(ptr_id);
  if (ptr_inst->opcode() != SpvOp::SpvOpAccessChain) return;
  if (ptr_inst->NumInOperands() != 2) {
    assert(false && "unexpected bindless index number");
    return;
  }
  uint32_t index_id =
      ptr_inst->GetSingleWordInOperand(kSpvAccessChainIndex0IdInIdx);
  ptr_id = ptr_inst->GetSingleWordInOperand(kSpvAccessChainBaseIdInIdx);
  ptr_inst = get_def_use_mgr()->GetDef(ptr_id);
  if (ptr_inst->opcode() != SpvOpVariable) {
    assert(false && "unexpected bindless base");
    return;
  }
  uint32_t var_type_id = ptr_inst->type_id();
  Instruction* var_type_inst = get_def_use_mgr()->GetDef(var_type_id);
  uint32_t ptr_type_id =
      var_type_inst->GetSingleWordInOperand(kSpvTypePointerTypeIdInIdx);
  Instruction* ptr_type_inst = get_def_use_mgr()->GetDef(ptr_type_id);
  // TODO(greg-lunarg): Handle RuntimeArray. Will need to pull length
  // out of debug input buffer.
  if (ptr_type_inst->opcode() != SpvOpTypeArray) return;
  // If index and bound both compile-time constants and index < bound,
  // return without changing
  uint32_t length_id =
      ptr_type_inst->GetSingleWordInOperand(kSpvTypeArrayLengthIdInIdx);
  Instruction* index_inst = get_def_use_mgr()->GetDef(index_id);
  Instruction* length_inst = get_def_use_mgr()->GetDef(length_id);
  if (index_inst->opcode() == SpvOpConstant &&
      length_inst->opcode() == SpvOpConstant &&
      index_inst->GetSingleWordInOperand(kSpvConstantValueInIdx) <
          length_inst->GetSingleWordInOperand(kSpvConstantValueInIdx))
    return;
  // Generate full runtime bounds test code with true branch
  // being full reference and false branch being debug output and zero
  // for the referenced value.
  MovePreludeCode(ref_inst_itr, ref_block_itr, &new_blk_ptr);
  InstructionBuilder builder(
      context(), &*new_blk_ptr,
      IRContext::kAnalysisDefUse | IRContext::kAnalysisInstrToBlockMapping);
  uint32_t error_id = builder.GetUintConstantId(kInstErrorBindlessBounds);
  Instruction* ult_inst =
      builder.AddBinaryOp(GetBoolId(), SpvOpULessThan, index_id, length_id);
  uint32_t merge_blk_id = TakeNextId();
  uint32_t valid_blk_id = TakeNextId();
  uint32_t invalid_blk_id = TakeNextId();
  std::unique_ptr<Instruction> merge_label(NewLabel(merge_blk_id));
  std::unique_ptr<Instruction> valid_label(NewLabel(valid_blk_id));
  std::unique_ptr<Instruction> invalid_label(NewLabel(invalid_blk_id));
  (void)builder.AddConditionalBranch(ult_inst->result_id(), valid_blk_id,
                                     invalid_blk_id, merge_blk_id,
                                     SpvSelectionControlMaskNone);
  // Close selection block and gen valid reference block
  new_blocks->push_back(std::move(new_blk_ptr));
  new_blk_ptr.reset(new BasicBlock(std::move(valid_label)));
  builder.SetInsertPoint(&*new_blk_ptr);
  // Clone descriptor load
  Instruction* new_load_inst =
      builder.AddLoad(load_inst->type_id(),
                      load_inst->GetSingleWordInOperand(kSpvLoadPtrIdInIdx));
  uint32_t new_load_id = new_load_inst->result_id();
  get_decoration_mgr()->CloneDecorations(load_inst->result_id(), new_load_id);
  uint32_t new_image_id = new_load_id;
  // Clone Image/SampledImage with new load, if needed
  if (image_id != 0) {
    if (image_inst->opcode() == SpvOp::SpvOpSampledImage) {
      Instruction* new_image_inst = builder.AddBinaryOp(
          image_inst->type_id(), SpvOpSampledImage, new_load_id,
          image_inst->GetSingleWordInOperand(kSpvSampledImageSamplerIdInIdx));
      new_image_id = new_image_inst->result_id();
    } else {
      assert(image_inst->opcode() == SpvOp::SpvOpImage && "expecting OpImage");
      Instruction* new_image_inst =
          builder.AddUnaryOp(image_inst->type_id(), SpvOpImage, new_load_id);
      new_image_id = new_image_inst->result_id();
    }
    get_decoration_mgr()->CloneDecorations(image_id, new_image_id);
  }
  // Clone original reference using new image code
  std::unique_ptr<Instruction> new_ref_inst(ref_inst_itr->Clone(context()));
  uint32_t ref_result_id = ref_inst_itr->result_id();
  uint32_t new_ref_id = 0;
  if (ref_result_id != 0) {
    new_ref_id = TakeNextId();
    new_ref_inst->SetResultId(new_ref_id);
  }
  new_ref_inst->SetInOperand(kSpvImageSampleImageIdInIdx, {new_image_id});
  // Register new reference and add to new block
  builder.AddInstruction(std::move(new_ref_inst));
  if (new_ref_id != 0)
    get_decoration_mgr()->CloneDecorations(ref_result_id, new_ref_id);
  // Close valid block and gen invalid block
  (void)builder.AddBranch(merge_blk_id);
  new_blocks->push_back(std::move(new_blk_ptr));
  new_blk_ptr.reset(new BasicBlock(std::move(invalid_label)));
  builder.SetInsertPoint(&*new_blk_ptr);
  uint32_t u_index_id = GenUintCastCode(index_id, &builder);
  GenDebugStreamWrite(instruction_idx, stage_idx,
                      {error_id, u_index_id, length_id}, &builder);
  // Remember last invalid block id
  uint32_t last_invalid_blk_id = new_blk_ptr->GetLabelInst()->result_id();
  // Gen zero for invalid  reference
  uint32_t ref_type_id = ref_inst_itr->type_id();
  // Close invalid block and gen merge block
  (void)builder.AddBranch(merge_blk_id);
  new_blocks->push_back(std::move(new_blk_ptr));
  new_blk_ptr.reset(new BasicBlock(std::move(merge_label)));
  builder.SetInsertPoint(&*new_blk_ptr);
  // Gen phi of new reference and zero, if necessary, and replace the
  // result id of the original reference with that of the Phi. Kill original
  // reference and move in remainder of original block.
  if (new_ref_id != 0) {
    Instruction* phi_inst = builder.AddPhi(
        ref_type_id, {new_ref_id, valid_blk_id, builder.GetNullId(ref_type_id),
                      last_invalid_blk_id});
    context()->ReplaceAllUsesWith(ref_result_id, phi_inst->result_id());
  }
  context()->KillInst(&*ref_inst_itr);
  MovePostludeCode(ref_block_itr, &new_blk_ptr);
  // Add remainder/merge block to new blocks
  new_blocks->push_back(std::move(new_blk_ptr));
}

void InstBindlessCheckPass::InitializeInstBindlessCheck() {
  // Initialize base class
  InitializeInstrument();
  // Look for related extensions
  ext_descriptor_indexing_defined_ = false;
  for (auto& ei : get_module()->extensions()) {
    const char* ext_name =
        reinterpret_cast<const char*>(&ei.GetInOperand(0).words[0]);
    if (strcmp(ext_name, "SPV_EXT_descriptor_indexing") == 0) {
      ext_descriptor_indexing_defined_ = true;
      break;
    }
  }
}

Pass::Status InstBindlessCheckPass::ProcessImpl() {
  // Perform instrumentation on each entry point function in module
  InstProcessFunction pfn =
      [this](BasicBlock::iterator ref_inst_itr,
             UptrVectorIterator<BasicBlock> ref_block_itr,
             uint32_t instruction_idx, uint32_t stage_idx,
             std::vector<std::unique_ptr<BasicBlock>>* new_blocks) {
        return GenBindlessCheckCode(ref_inst_itr, ref_block_itr,
                                    instruction_idx, stage_idx, new_blocks);
      };
  bool modified = InstProcessEntryPointCallTree(pfn);
  // This pass does not update inst->blk info
  context()->InvalidateAnalyses(IRContext::kAnalysisInstrToBlockMapping);
  return modified ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

Pass::Status InstBindlessCheckPass::Process() {
  InitializeInstBindlessCheck();
  return ProcessImpl();
}

}  // namespace opt
}  // namespace spvtools

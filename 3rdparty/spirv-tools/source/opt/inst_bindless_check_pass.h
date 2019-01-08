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

#ifndef LIBSPIRV_OPT_INST_BINDLESS_CHECK_PASS_H_
#define LIBSPIRV_OPT_INST_BINDLESS_CHECK_PASS_H_

#include "instrument_pass.h"

namespace spvtools {
namespace opt {

// This class/pass is designed to support the bindless (descriptor indexing)
// GPU-assisted validation layer of
// https://github.com/KhronosGroup/Vulkan-ValidationLayers. Its internal and
// external design may change as the layer evolves.
class InstBindlessCheckPass : public InstrumentPass {
 public:
  // For test harness only
  InstBindlessCheckPass() : InstrumentPass(7, 23, kInstValidationIdBindless) {}
  // For all other interfaces
  InstBindlessCheckPass(uint32_t desc_set, uint32_t shader_id)
      : InstrumentPass(desc_set, shader_id, kInstValidationIdBindless) {}

  ~InstBindlessCheckPass() override = default;

  // See optimizer.hpp for pass user documentation.
  Status Process() override;

  const char* name() const override { return "inst-bindless-check-pass"; }

 private:
  // Initialize state for instrumenting bindless checking
  void InitializeInstBindlessCheck();

  // This function does bindless checking instrumentation on a single
  // instruction. It is designed to be passed to
  // InstrumentPass::InstProcessEntryPointCallTree(), which applies the
  // function to each instruction in a module and replaces the instruction
  // if warranted.
  //
  // If |ref_inst_itr| is a bindless reference, return in |new_blocks| the
  // result of instrumenting it with validation code within its block at
  // |ref_block_itr|. Specifically, generate code to check that the index
  // into the descriptor array is in-bounds. If the check passes, execute
  // the remainder of the reference, otherwise write a record to the debug
  // output buffer stream including |function_idx, instruction_idx, stage_idx|
  // and replace the reference with the null value of the original type. The
  // block at |ref_block_itr| can just be replaced with the blocks in
  // |new_blocks|, which will contain at least two blocks. The last block will
  // comprise all instructions following |ref_inst_itr|,
  // preceded by a phi instruction.
  //
  // This instrumentation pass utilizes GenDebugStreamWrite() to write its
  // error records. The validation-specific part of the error record will
  // have the format:
  //
  //    Validation Error Code (=kInstErrorBindlessBounds)
  //    Descriptor Index
  //    Descriptor Array Size
  //
  // The Descriptor Index is the index which has been determined to be
  // out-of-bounds.
  //
  // The Descriptor Array Size is the size of the descriptor array which was
  // indexed.
  void GenBindlessCheckCode(
      BasicBlock::iterator ref_inst_itr,
      UptrVectorIterator<BasicBlock> ref_block_itr, uint32_t instruction_idx,
      uint32_t stage_idx, std::vector<std::unique_ptr<BasicBlock>>* new_blocks);

  Pass::Status ProcessImpl();

  // True if VK_EXT_descriptor_indexing is defined
  bool ext_descriptor_indexing_defined_;
};

}  // namespace opt
}  // namespace spvtools

#endif  // LIBSPIRV_OPT_INST_BINDLESS_CHECK_PASS_H_

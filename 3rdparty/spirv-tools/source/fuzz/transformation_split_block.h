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

#ifndef SOURCE_FUZZ_TRANSFORMATION_SPLIT_BLOCK_H_
#define SOURCE_FUZZ_TRANSFORMATION_SPLIT_BLOCK_H_

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

// - |result_id| must be the result id of an instruction 'base' in some
//   block 'blk'.
// - 'blk' must contain an instruction 'inst' located |offset| instructions
//   after 'inst' (if |offset| = 0 then 'inst' = 'base').
// - Splitting 'blk' at 'inst', so that all instructions from 'inst' onwards
//   appear in a new block that 'blk' directly jumps to must be valid.
// - |fresh_id| must not be used by the module.
bool IsApplicable(const protobufs::TransformationSplitBlock& message,
                  opt::IRContext* context, const FactManager& fact_manager);

// - A new block with label |fresh_id| is inserted right after 'blk' in
//   program order.
// - All instructions of 'blk' from 'inst' onwards are moved into the new
//   block.
// - 'blk' is made to jump unconditionally to the new block.
void Apply(const protobufs::TransformationSplitBlock& message,
           opt::IRContext* context, FactManager* fact_manager);

// Creates a protobuf message representing a block-splitting transformation.
protobufs::TransformationSplitBlock MakeTransformationSplitBlock(
    uint32_t result_id, uint32_t offset, uint32_t fresh_id);

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_SPLIT_BLOCK_H_

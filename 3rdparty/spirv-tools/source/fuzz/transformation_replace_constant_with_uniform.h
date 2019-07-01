#include <utility>

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

#ifndef SOURCE_FUZZ_TRANSFORMATION_REPLACE_CONSTANT_WITH_UNIFORM_H_
#define SOURCE_FUZZ_TRANSFORMATION_REPLACE_CONSTANT_WITH_UNIFORM_H_

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/id_use_descriptor.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

// - |fresh_id_for_access_chain| and |fresh_id_for_load| must be distinct fresh
//   ids.
// - |uniform_descriptor| specifies a result id and a list of integer literal
//   indices.
//   As an example, suppose |uniform_descriptor| is (18, [0, 1, 0])
//   It is required that:
//     - the result id (18 in our example) is the id of some uniform variable
//     - the module contains an integer constant instruction corresponding to
//       each of the literal indices; in our example there must thus be
//       OpConstant instructions %A and %B say for each of 0 and 1
//     - it is legitimate to index into the uniform variable using the
//       sequence of indices; in our example this means indexing into %18 using
//       the sequence %A %B %A
//     - the module contains a uniform pointer type corresponding to the type
//       of the uniform data element obtained by following these indices
// - |id_use_descriptor| identifies the use of some id %C.  It is required that:
//     - this use does indeed exist in the module
//     - %C is an OpConstant
//     - According to the fact manager, the uniform data element specified by
//       |uniform_descriptor| holds a value with the same type and value as %C
bool IsApplicable(
    const protobufs::TransformationReplaceConstantWithUniform& message,
    opt::IRContext* context, const FactManager& fact_manager);

// - Introduces two new instructions:
//   - An access chain targeting the uniform data element specified by
//     |uniform_descriptor|, with result id |fresh_id_for_access_chain|
//   - A load from this access chain, with id |fresh_id_for_load|
// - Replaces the id use specified by |id_use_descriptor| with
//   |fresh_id_for_load|
void Apply(const protobufs::TransformationReplaceConstantWithUniform& message,
           opt::IRContext* context, FactManager* fact_manager);

// Helper factory to create a transformation message.
protobufs::TransformationReplaceConstantWithUniform
MakeTransformationReplaceConstantWithUniform(
    protobufs::IdUseDescriptor id_use,
    protobufs::UniformBufferElementDescriptor uniform_descriptor,
    uint32_t fresh_id_for_access_chain, uint32_t fresh_id_for_load);

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_REPLACE_CONSTANT_WITH_UNIFORM_H_

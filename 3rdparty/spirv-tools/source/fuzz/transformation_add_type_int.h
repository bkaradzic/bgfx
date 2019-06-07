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

#ifndef SOURCE_FUZZ_TRANSFORMATION_ADD_TYPE_INT_H_
#define SOURCE_FUZZ_TRANSFORMATION_ADD_TYPE_INT_H_

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

// - |message.fresh_id| must not be used by the module
// - The module must not contain an OpTypeInt instruction with width
//   |message.width| and signedness |message.is_signed|
bool IsApplicable(const protobufs::TransformationAddTypeInt& message,
                  opt::IRContext* context, const FactManager& fact_manager);

// Adds an OpTypeInt instruction to the module with the given width and
// signedness.
void Apply(const protobufs::TransformationAddTypeInt& message,
           opt::IRContext* context, FactManager* fact_manager);

// Helper factory to create a transformation message.
protobufs::TransformationAddTypeInt MakeTransformationAddTypeInt(
    uint32_t fresh_id, uint32_t width, bool is_signed);

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_ADD_TYPE_INT_H_

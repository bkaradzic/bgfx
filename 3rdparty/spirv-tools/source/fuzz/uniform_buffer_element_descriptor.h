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

#ifndef SOURCE_FUZZ_UNIFORM_BUFFER_ELEMENT_DESCRIPTOR_H_
#define SOURCE_FUZZ_UNIFORM_BUFFER_ELEMENT_DESCRIPTOR_H_

#include <algorithm>
#include <vector>

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"

namespace spvtools {
namespace fuzz {

// Factory method to create a uniform buffer element descriptor message from an
// id and list of indices.
protobufs::UniformBufferElementDescriptor MakeUniformBufferElementDescriptor(
    uint32_t uniform_variable_id, std::vector<uint32_t>&& indices);

// Equality function for uniform buffer element descriptors.
struct UniformBufferElementDescriptorEquals {
  bool operator()(
      const protobufs::UniformBufferElementDescriptor* first,
      const protobufs::UniformBufferElementDescriptor* second) const;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // #define SOURCE_FUZZ_UNIFORM_BUFFER_ELEMENT_DESCRIPTOR_H_

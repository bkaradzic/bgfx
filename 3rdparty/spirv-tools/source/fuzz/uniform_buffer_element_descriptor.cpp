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

#include "source/fuzz/uniform_buffer_element_descriptor.h"

namespace spvtools {
namespace fuzz {

protobufs::UniformBufferElementDescriptor MakeUniformBufferElementDescriptor(
    uint32_t uniform_variable_id, std::vector<uint32_t>&& indices) {
  protobufs::UniformBufferElementDescriptor result;
  result.set_uniform_variable_id(uniform_variable_id);
  for (auto index : indices) {
    result.add_index(index);
  }
  return result;
}

bool UniformBufferElementDescriptorEquals::operator()(
    const protobufs::UniformBufferElementDescriptor* first,
    const protobufs::UniformBufferElementDescriptor* second) const {
  return first->uniform_variable_id() == second->uniform_variable_id() &&
         std::equal(first->index().begin(), first->index().end(),
                    second->index().begin());
}

}  // namespace fuzz
}  // namespace spvtools

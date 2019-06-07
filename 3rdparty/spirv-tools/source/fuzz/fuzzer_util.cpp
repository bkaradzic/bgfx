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

}  // namespace fuzzerutil

}  // namespace fuzz
}  // namespace spvtools

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

#include "source/spirv_fuzzer_options.h"

spv_fuzzer_options_t::spv_fuzzer_options_t() = default;

SPIRV_TOOLS_EXPORT spv_fuzzer_options spvFuzzerOptionsCreate() {
  return new spv_fuzzer_options_t();
}

SPIRV_TOOLS_EXPORT void spvFuzzerOptionsDestroy(spv_fuzzer_options options) {
  delete options;
}

SPIRV_TOOLS_EXPORT void spvFuzzerOptionsSetRandomSeed(
    spv_fuzzer_options options, uint32_t seed) {
  options->has_random_seed = true;
  options->random_seed = seed;
}

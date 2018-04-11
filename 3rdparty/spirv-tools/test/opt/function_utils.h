// Copyright (c) 2017 Google Inc.
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

#ifndef LIBSPIRV_TEST_OPT_FUNCTION_UTILS_H_
#define LIBSPIRV_TEST_OPT_FUNCTION_UTILS_H_

#include "opt/function.h"
#include "opt/module.h"

namespace spvtest {

spvtools::ir::Function* GetFunction(spvtools::ir::Module* module, uint32_t id) {
  for (spvtools::ir::Function& f : *module) {
    if (f.result_id() == id) {
      return &f;
    }
  }
  return nullptr;
}

const spvtools::ir::Function* GetFunction(const spvtools::ir::Module* module,
                                          uint32_t id) {
  for (const spvtools::ir::Function& f : *module) {
    if (f.result_id() == id) {
      return &f;
    }
  }
  return nullptr;
}

const spvtools::ir::BasicBlock* GetBasicBlock(const spvtools::ir::Function* fn,
                                              uint32_t id) {
  for (const spvtools::ir::BasicBlock& bb : *fn) {
    if (bb.id() == id) {
      return &bb;
    }
  }
  return nullptr;
}

}  // namespace spvtest

#endif  // LIBSPIRV_TEST_OPT_FUNCTION_UTILS_H_

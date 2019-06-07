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

#include <utility>

#include "source/fuzz/fact_manager.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

FactManager::FactManager() = default;

FactManager::~FactManager() = default;

bool FactManager::AddFacts(const protobufs::FactSequence& initial_facts,
                           opt::IRContext* context) {
  for (auto& fact : initial_facts.fact()) {
    if (!AddFact(fact, context)) {
      // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2621) Provide
      //  information about the fact that could not be added.
      return false;
    }
  }
  return true;
}

bool FactManager::AddFact(const spvtools::fuzz::protobufs::Fact&,
                          spvtools::opt::IRContext*) {
  assert(0 && "No facts are yet supported.");
  return true;
}

}  // namespace fuzz
}  // namespace spvtools

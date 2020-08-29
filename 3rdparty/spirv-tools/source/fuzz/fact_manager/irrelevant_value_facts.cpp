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

#include "source/fuzz/fact_manager/irrelevant_value_facts.h"

#include "source/fuzz/data_descriptor.h"
#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {
namespace fact_manager {

void IrrelevantValueFacts::AddFact(
    const protobufs::FactPointeeValueIsIrrelevant& fact) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3550)
  //  Assert that the id does not participate in DataSynonym facts and is a
  //  pointer.

  pointers_to_irrelevant_pointees_ids_.insert(fact.pointer_id());
}

void IrrelevantValueFacts::AddFact(const protobufs::FactIdIsIrrelevant& fact) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3550)
  //  Assert that the id does not participate in DataSynonym facts and is not a
  //  pointer.

  irrelevant_ids_.insert(fact.result_id());
}

bool IrrelevantValueFacts::PointeeValueIsIrrelevant(uint32_t pointer_id) const {
  return pointers_to_irrelevant_pointees_ids_.count(pointer_id) != 0;
}

bool IrrelevantValueFacts::IdIsIrrelevant(uint32_t pointer_id) const {
  return irrelevant_ids_.count(pointer_id) != 0;
}

}  // namespace fact_manager
}  // namespace fuzz
}  // namespace spvtools

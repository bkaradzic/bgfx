// Copyright (c) 2020 Google LLC
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

#include "source/fuzz/fuzzer_pass_add_global_variables.h"

#include "source/fuzz/transformation_add_global_variable.h"
#include "source/fuzz/transformation_add_type_pointer.h"

namespace spvtools {
namespace fuzz {

FuzzerPassAddGlobalVariables::FuzzerPassAddGlobalVariables(
    opt::IRContext* ir_context, FactManager* fact_manager,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, fact_manager, fuzzer_context, transformations) {}

FuzzerPassAddGlobalVariables::~FuzzerPassAddGlobalVariables() = default;

void FuzzerPassAddGlobalVariables::Apply() {
  auto base_type_ids_and_pointers =
      GetAvailableBaseTypesAndPointers(SpvStorageClassPrivate);

  // These are the base types that are available to this fuzzer pass.
  auto& base_types = base_type_ids_and_pointers.first;

  // These are the pointers to those base types that are *initially* available
  // to the fuzzer pass.  The fuzzer pass might add pointer types in cases where
  // none are available for a given base type.
  auto& base_type_to_pointers = base_type_ids_and_pointers.second;

  // Probabilistically keep adding global variables.
  while (GetFuzzerContext()->ChoosePercentage(
      GetFuzzerContext()->GetChanceOfAddingGlobalVariable())) {
    // Choose a random base type; the new variable's type will be a pointer to
    // this base type.
    uint32_t base_type =
        base_types[GetFuzzerContext()->RandomIndex(base_types)];
    uint32_t pointer_type_id;
    std::vector<uint32_t>& available_pointers_to_base_type =
        base_type_to_pointers.at(base_type);
    // Determine whether there is at least one pointer to this base type.
    if (available_pointers_to_base_type.empty()) {
      // There is not.  Make one, to use here, and add it to the available
      // pointers for the base type so that future variables can potentially
      // use it.
      pointer_type_id = GetFuzzerContext()->GetFreshId();
      available_pointers_to_base_type.push_back(pointer_type_id);
      ApplyTransformation(TransformationAddTypePointer(
          pointer_type_id, SpvStorageClassPrivate, base_type));
    } else {
      // There is - grab one.
      pointer_type_id =
          available_pointers_to_base_type[GetFuzzerContext()->RandomIndex(
              available_pointers_to_base_type)];
    }
    ApplyTransformation(TransformationAddGlobalVariable(
        GetFuzzerContext()->GetFreshId(), pointer_type_id,
        FindOrCreateZeroConstant(base_type), true));
  }
}

}  // namespace fuzz
}  // namespace spvtools

// Copyright (c) 2020 Vasyl Teliman
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

#include "source/fuzz/fuzzer_pass_add_parameters.h"

#include "source/fuzz/fuzzer_context.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"
#include "source/fuzz/transformation_add_parameters.h"

namespace spvtools {
namespace fuzz {

FuzzerPassAddParameters::FuzzerPassAddParameters(
    opt::IRContext* ir_context, TransformationContext* transformation_context,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, transformation_context, fuzzer_context,
                 transformations) {}

FuzzerPassAddParameters::~FuzzerPassAddParameters() = default;

void FuzzerPassAddParameters::Apply() {
  const auto& type_candidates = ComputeTypeCandidates();

  if (type_candidates.empty()) {
    // The module contains no suitable types to use in new parameters.
    return;
  }

  // Iterate over all functions in the module.
  for (const auto& function : *GetIRContext()->module()) {
    // Skip all entry-point functions - we don't want to change those.
    if (fuzzerutil::FunctionIsEntryPoint(GetIRContext(),
                                         function.result_id())) {
      continue;
    }

    if (GetNumberOfParameters(function) >=
        GetFuzzerContext()->GetMaximumNumberOfFunctionParameters()) {
      continue;
    }

    if (!GetFuzzerContext()->ChoosePercentage(
            GetFuzzerContext()->GetChanceOfAddingParameters())) {
      continue;
    }

    const auto* type_inst =
        fuzzerutil::GetFunctionType(GetIRContext(), &function);
    assert(type_inst);

    // -1 because we don't take return type into account.
    auto num_old_parameters = type_inst->NumInOperands() - 1;
    auto num_new_parameters =
        GetFuzzerContext()->GetRandomNumberOfNewParameters(
            GetNumberOfParameters(function));

    std::vector<uint32_t> all_types(num_old_parameters);
    std::vector<uint32_t> new_types(num_new_parameters);
    std::vector<uint32_t> parameter_ids(num_new_parameters);
    std::vector<uint32_t> constant_ids(num_new_parameters);

    // Get type ids for old parameters.
    for (uint32_t i = 0; i < num_old_parameters; ++i) {
      // +1 since we don't take return type into account.
      all_types[i] = type_inst->GetSingleWordInOperand(i + 1);
    }

    for (uint32_t i = 0; i < num_new_parameters; ++i) {
      // Get type ids for new parameters.
      new_types[i] =
          type_candidates[GetFuzzerContext()->RandomIndex(type_candidates)];

      // Create constants to initialize new parameters from.
      constant_ids[i] = FindOrCreateZeroConstant(new_types[i]);
    }

    // Append new parameters to the old ones.
    all_types.insert(all_types.end(), new_types.begin(), new_types.end());

    // Generate result ids for new parameters.
    for (auto& id : parameter_ids) {
      id = GetFuzzerContext()->GetFreshId();
    }

    auto result_type_id = type_inst->GetSingleWordInOperand(0);
    ApplyTransformation(TransformationAddParameters(
        function.result_id(),
        FindOrCreateFunctionType(result_type_id, all_types),
        std::move(new_types), std::move(parameter_ids),
        std::move(constant_ids)));
  }
}

std::vector<uint32_t> FuzzerPassAddParameters::ComputeTypeCandidates() const {
  std::vector<uint32_t> result;

  for (const auto* type_inst : GetIRContext()->module()->GetTypes()) {
    // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3403):
    //  the number of types we support here is limited by the number of types
    //  supported by |FindOrCreateZeroConstant|.
    switch (type_inst->opcode()) {
      case SpvOpTypeBool:
      case SpvOpTypeInt:
      case SpvOpTypeFloat:
      case SpvOpTypeArray:
      case SpvOpTypeMatrix:
      case SpvOpTypeVector:
      case SpvOpTypeStruct: {
        result.push_back(type_inst->result_id());
      } break;
      default:
        // Ignore other types.
        break;
    }
  }

  return result;
}

uint32_t FuzzerPassAddParameters::GetNumberOfParameters(
    const opt::Function& function) const {
  const auto* type = GetIRContext()->get_type_mgr()->GetType(
      function.DefInst().GetSingleWordInOperand(1));
  assert(type && type->AsFunction());

  return static_cast<uint32_t>(type->AsFunction()->param_types().size());
}

}  // namespace fuzz
}  // namespace spvtools

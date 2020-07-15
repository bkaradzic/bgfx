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
#include "source/fuzz/transformation_add_parameter.h"

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

    auto num_new_parameters =
        GetFuzzerContext()->GetRandomNumberOfNewParameters(
            GetNumberOfParameters(function));
    for (uint32_t i = 0; i < num_new_parameters; ++i) {
      ApplyTransformation(TransformationAddParameter(
          function.result_id(), GetFuzzerContext()->GetFreshId(),
          FindOrCreateZeroConstant(
              type_candidates[GetFuzzerContext()->RandomIndex(
                  type_candidates)]),
          GetFuzzerContext()->GetFreshId()));
    }
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

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

#include <unordered_set>
#include <vector>

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/transformation_permute_function_parameters.h"

namespace spvtools {
namespace fuzz {

TransformationPermuteFunctionParameters::
    TransformationPermuteFunctionParameters(
        const spvtools::fuzz::protobufs::
            TransformationPermuteFunctionParameters& message)
    : message_(message) {}

TransformationPermuteFunctionParameters::
    TransformationPermuteFunctionParameters(
        uint32_t function_id, uint32_t new_type_id,
        const std::vector<uint32_t>& permutation) {
  message_.set_function_id(function_id);
  message_.set_new_type_id(new_type_id);

  for (auto index : permutation) {
    message_.add_permutation(index);
  }
}

bool TransformationPermuteFunctionParameters::IsApplicable(
    opt::IRContext* context, const FactManager& /*unused*/) const {
  // Check that function exists
  const auto* function =
      fuzzerutil::FindFunction(context, message_.function_id());
  if (!function || function->DefInst().opcode() != SpvOpFunction ||
      fuzzerutil::FunctionIsEntryPoint(context, function->result_id())) {
    return false;
  }

  // Check that permutation has valid indices
  const auto* function_type = fuzzerutil::GetFunctionType(context, function);
  assert(function_type && "Function type is null");

  const auto& permutation = message_.permutation();

  // Don't take return type into account
  auto arg_size = function_type->NumInOperands() - 1;

  // |permutation| vector should be equal to the number of arguments
  if (static_cast<uint32_t>(permutation.size()) != arg_size) {
    return false;
  }

  // Check that all indices are valid
  // and unique integers from the [0, n-1] set
  std::unordered_set<uint32_t> unique_indices;
  for (auto index : permutation) {
    // We don't compare |index| with 0 since it's an unsigned integer
    if (index >= arg_size) {
      return false;
    }

    unique_indices.insert(index);
  }

  // Check that permutation doesn't have duplicated values
  assert(unique_indices.size() == arg_size && "Permutation has duplicates");

  // Check that new function's type is valid:
  //   - Has the same number of operands
  //   - Has the same result type as the old one
  //   - Order of arguments is permuted
  auto new_type_id = message_.new_type_id();
  const auto* new_type = context->get_def_use_mgr()->GetDef(new_type_id);

  if (!new_type || new_type->opcode() != SpvOpTypeFunction ||
      new_type->NumInOperands() != function_type->NumInOperands()) {
    return false;
  }

  // Check that both instructions have the same result type
  if (new_type->GetSingleWordInOperand(0) !=
      function_type->GetSingleWordInOperand(0)) {
    return false;
  }

  // Check that new function type has its arguments permuted
  for (int i = 0, n = static_cast<int>(permutation.size()); i < n; ++i) {
    // +1 to take return type into account
    if (new_type->GetSingleWordInOperand(i + 1) !=
        function_type->GetSingleWordInOperand(permutation[i] + 1)) {
      return false;
    }
  }

  return true;
}

void TransformationPermuteFunctionParameters::Apply(
    opt::IRContext* context, FactManager* /*unused*/) const {
  // Retrieve all data from the message
  uint32_t function_id = message_.function_id();
  uint32_t new_type_id = message_.new_type_id();
  const auto& permutation = message_.permutation();

  // Find the function that will be transformed
  auto* function = fuzzerutil::FindFunction(context, function_id);
  assert(function && "Can't find the function");

  // Change function's type
  function->DefInst().SetInOperand(1, {new_type_id});

  // Adjust OpFunctionParameter instructions

  // Collect ids and types from OpFunctionParameter instructions
  std::vector<uint32_t> param_id, param_type;
  function->ForEachParam(
      [&param_id, &param_type](const opt::Instruction* param) {
        param_id.push_back(param->result_id());
        param_type.push_back(param->type_id());
      });

  // Permute parameters' ids and types
  std::vector<uint32_t> permuted_param_id, permuted_param_type;
  for (auto index : permutation) {
    permuted_param_id.push_back(param_id[index]);
    permuted_param_type.push_back(param_type[index]);
  }

  // Set OpFunctionParameter instructions to point to new parameters
  size_t i = 0;
  function->ForEachParam(
      [&i, &permuted_param_id, &permuted_param_type](opt::Instruction* param) {
        param->SetResultType(permuted_param_type[i]);
        param->SetResultId(permuted_param_id[i]);
        ++i;
      });

  // Fix all OpFunctionCall instructions
  context->get_def_use_mgr()->ForEachUser(
      &function->DefInst(),
      [function_id, &permutation](opt::Instruction* call) {
        if (call->opcode() != SpvOpFunctionCall ||
            call->GetSingleWordInOperand(0) != function_id) {
          return;
        }

        opt::Instruction::OperandList call_operands = {
            call->GetInOperand(0)  // Function id
        };

        for (auto index : permutation) {
          // Take function id into account
          call_operands.push_back(call->GetInOperand(index + 1));
        }

        call->SetInOperands(std::move(call_operands));
      });

  // Make sure our changes are analyzed
  context->InvalidateAnalysesExceptFor(opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationPermuteFunctionParameters::ToMessage()
    const {
  protobufs::Transformation result;
  *result.mutable_permute_function_parameters() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

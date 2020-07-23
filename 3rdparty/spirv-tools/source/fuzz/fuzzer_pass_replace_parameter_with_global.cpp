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

#include "source/fuzz/fuzzer_pass_replace_parameter_with_global.h"

#include <numeric>
#include <vector>

#include "source/fuzz/fuzzer_context.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/transformation_replace_parameter_with_global.h"

namespace spvtools {
namespace fuzz {

FuzzerPassReplaceParameterWithGlobal::FuzzerPassReplaceParameterWithGlobal(
    opt::IRContext* ir_context, TransformationContext* transformation_context,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, transformation_context, fuzzer_context,
                 transformations) {}

FuzzerPassReplaceParameterWithGlobal::~FuzzerPassReplaceParameterWithGlobal() =
    default;

void FuzzerPassReplaceParameterWithGlobal::Apply() {
  for (const auto& function : *GetIRContext()->module()) {
    if (fuzzerutil::FunctionIsEntryPoint(GetIRContext(),
                                         function.result_id())) {
      continue;
    }

    if (!GetFuzzerContext()->ChoosePercentage(
            GetFuzzerContext()->GetChanceOfReplacingParametersWithGlobals())) {
      continue;
    }

    auto params =
        fuzzerutil::GetParameters(GetIRContext(), function.result_id());

    // Make sure at least one parameter can be replaced. Also checks that the
    // function has at least one parameter.
    if (std::none_of(params.begin(), params.end(),
                     [this](const opt::Instruction* param) {
                       const auto* param_type =
                           GetIRContext()->get_type_mgr()->GetType(
                               param->type_id());
                       assert(param_type && "Parameter has invalid type");
                       return TransformationReplaceParameterWithGlobal::
                           IsParameterTypeSupported(*param_type);
                     })) {
      continue;
    }

    // Select id of a parameter to replace.
    const opt::Instruction* replaced_param = nullptr;
    const opt::analysis::Type* param_type = nullptr;
    do {
      replaced_param = GetFuzzerContext()->RemoveAtRandomIndex(&params);
      param_type =
          GetIRContext()->get_type_mgr()->GetType(replaced_param->type_id());
      assert(param_type && "Parameter has invalid type");
    } while (
        !TransformationReplaceParameterWithGlobal::IsParameterTypeSupported(
            *param_type));

    assert(replaced_param && "Unable to find a parameter to replace");

    // Make sure type id for the global variable exists in the module.
    FindOrCreatePointerType(replaced_param->type_id(), SpvStorageClassPrivate);

    // Make sure initializer for the global variable exists in the module.
    FindOrCreateZeroConstant(replaced_param->type_id());

    ApplyTransformation(TransformationReplaceParameterWithGlobal(
        GetFuzzerContext()->GetFreshId(), replaced_param->result_id(),
        GetFuzzerContext()->GetFreshId()));
  }
}

}  // namespace fuzz
}  // namespace spvtools

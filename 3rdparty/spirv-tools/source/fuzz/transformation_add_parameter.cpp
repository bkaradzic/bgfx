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

#include "source/fuzz/transformation_add_parameter.h"

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {

TransformationAddParameter::TransformationAddParameter(
    const protobufs::TransformationAddParameter& message)
    : message_(message) {}

TransformationAddParameter::TransformationAddParameter(
    uint32_t function_id, uint32_t parameter_fresh_id, uint32_t initializer_id,
    uint32_t function_type_fresh_id) {
  message_.set_function_id(function_id);
  message_.set_parameter_fresh_id(parameter_fresh_id);
  message_.set_initializer_id(initializer_id);
  message_.set_function_type_fresh_id(function_type_fresh_id);
}

bool TransformationAddParameter::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  // Check that function exists
  const auto* function =
      fuzzerutil::FindFunction(ir_context, message_.function_id());
  if (!function ||
      fuzzerutil::FunctionIsEntryPoint(ir_context, function->result_id())) {
    return false;
  }

  // Check that |initializer_id| is valid.
  const auto* initializer_inst =
      ir_context->get_def_use_mgr()->GetDef(message_.initializer_id());

  if (!initializer_inst) {
    return false;
  }

  // Check that initializer's type is valid.
  const auto* initializer_type =
      ir_context->get_type_mgr()->GetType(initializer_inst->type_id());

  if (!initializer_type || !IsParameterTypeSupported(*initializer_type)) {
    return false;
  }

  return fuzzerutil::IsFreshId(ir_context, message_.parameter_fresh_id()) &&
         fuzzerutil::IsFreshId(ir_context, message_.function_type_fresh_id()) &&
         message_.parameter_fresh_id() != message_.function_type_fresh_id();
}

void TransformationAddParameter::Apply(
    opt::IRContext* ir_context,
    TransformationContext* transformation_context) const {
  // Find the function that will be transformed
  auto* function = fuzzerutil::FindFunction(ir_context, message_.function_id());
  assert(function && "Can't find the function");

  const auto new_parameter_type_id =
      fuzzerutil::GetTypeId(ir_context, message_.initializer_id());
  assert(new_parameter_type_id != 0 && "Initializer has invalid type");

  // Add new parameters to the function.
  function->AddParameter(MakeUnique<opt::Instruction>(
      ir_context, SpvOpFunctionParameter, new_parameter_type_id,
      message_.parameter_fresh_id(), opt::Instruction::OperandList()));

  fuzzerutil::UpdateModuleIdBound(ir_context, message_.parameter_fresh_id());

  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3403):
  //  Add an PointeeValueIsIrrelevant fact if the parameter is a pointer.

  // Mark new parameter as irrelevant so that we can replace its use with some
  // other id.
  transformation_context->GetFactManager()->AddFactIdIsIrrelevant(
      message_.parameter_fresh_id());

  // Fix all OpFunctionCall instructions.
  for (auto* inst : fuzzerutil::GetCallers(ir_context, function->result_id())) {
    inst->AddOperand({SPV_OPERAND_TYPE_ID, {message_.initializer_id()}});
  }

  // Update function's type.
  {
    // We use a separate scope here since |old_function_type| might become a
    // dangling pointer after the call to the fuzzerutil::UpdateFunctionType.

    const auto* old_function_type =
        fuzzerutil::GetFunctionType(ir_context, function);
    assert(old_function_type && "Function must have a valid type");

    std::vector<uint32_t> parameter_type_ids;
    for (uint32_t i = 1; i < old_function_type->NumInOperands(); ++i) {
      parameter_type_ids.push_back(
          old_function_type->GetSingleWordInOperand(i));
    }

    parameter_type_ids.push_back(new_parameter_type_id);

    fuzzerutil::UpdateFunctionType(
        ir_context, function->result_id(), message_.function_type_fresh_id(),
        old_function_type->GetSingleWordInOperand(0), parameter_type_ids);
  }

  // Make sure our changes are analyzed.
  ir_context->InvalidateAnalysesExceptFor(
      opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationAddParameter::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_add_parameter() = message_;
  return result;
}

bool TransformationAddParameter::IsParameterTypeSupported(
    const opt::analysis::Type& type) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3403):
  //  Think about other type instructions we can add here.
  switch (type.kind()) {
    case opt::analysis::Type::kBool:
    case opt::analysis::Type::kInteger:
    case opt::analysis::Type::kFloat:
    case opt::analysis::Type::kArray:
    case opt::analysis::Type::kMatrix:
    case opt::analysis::Type::kVector:
      return true;
    case opt::analysis::Type::kStruct:
      return std::all_of(type.AsStruct()->element_types().begin(),
                         type.AsStruct()->element_types().end(),
                         [](const opt::analysis::Type* element_type) {
                           return IsParameterTypeSupported(*element_type);
                         });
    default:
      return false;
  }
}

}  // namespace fuzz
}  // namespace spvtools

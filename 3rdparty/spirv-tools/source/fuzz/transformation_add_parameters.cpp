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

#include "source/fuzz/transformation_add_parameters.h"

#include <source/spirv_constant.h>

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {

TransformationAddParameters::TransformationAddParameters(
    const protobufs::TransformationAddParameters& message)
    : message_(message) {}

TransformationAddParameters::TransformationAddParameters(
    uint32_t function_id, uint32_t new_type_id,
    const std::vector<uint32_t>& new_parameter_type,
    const std::vector<uint32_t>& new_parameter_id,
    const std::vector<uint32_t>& constant_id) {
  message_.set_function_id(function_id);
  message_.set_new_type_id(new_type_id);

  for (auto id : new_parameter_type) {
    message_.add_new_parameter_type(id);
  }

  for (auto id : new_parameter_id) {
    message_.add_new_parameter_id(id);
  }

  for (auto id : constant_id) {
    message_.add_constant_id(id);
  }
}

bool TransformationAddParameters::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  // Check that function exists
  const auto* function =
      fuzzerutil::FindFunction(ir_context, message_.function_id());
  if (!function ||
      fuzzerutil::FunctionIsEntryPoint(ir_context, function->result_id())) {
    return false;
  }

  // Validate new parameters.
  const auto& new_type_ids = message_.new_parameter_type();
  const auto& new_parameter_ids = message_.new_parameter_id();
  const auto& constant_ids = message_.constant_id();

  // All three vectors must have the same size.
  if (new_type_ids.size() != new_parameter_ids.size() ||
      new_type_ids.size() != constant_ids.size()) {
    return false;
  }

  // Vectors must have at least one component.
  if (new_type_ids.empty()) {
    return false;
  }

  // Check that type ids exist in the module and are not OpTypeVoid.
  for (auto id : new_type_ids) {
    const auto* type = ir_context->get_type_mgr()->GetType(id);
    if (!type || type->AsVoid()) {
      return false;
    }
  }

  // Check that all parameter ids are fresh.
  for (auto id : new_parameter_ids) {
    if (!fuzzerutil::IsFreshId(ir_context, id)) {
      return false;
    }
  }

  // Check that constants exist and have valid type.
  for (int i = 0, n = constant_ids.size(); i < n; ++i) {
    const auto* inst = ir_context->get_def_use_mgr()->GetDef(constant_ids[i]);
    if (!inst || inst->type_id() != new_type_ids[i]) {
      return false;
    }
  }

  // Validate new function type.
  const auto* old_type_inst = fuzzerutil::GetFunctionType(ir_context, function);
  const auto* new_type_inst =
      ir_context->get_def_use_mgr()->GetDef(message_.new_type_id());

  // Both types must exist.
  assert(old_type_inst && old_type_inst->opcode() == SpvOpTypeFunction);
  if (!new_type_inst || new_type_inst->opcode() != SpvOpTypeFunction) {
    return false;
  }

  auto num_old_parameters = old_type_inst->NumInOperands();
  auto num_new_parameters = new_type_ids.size();

  // New function type has been added to the module which means that it's valid.
  // Thus, we don't need to check whether the limit on the number of arguments
  // is satisfied.

  // New type = old type + new parameters.
  if (new_type_inst->NumInOperands() !=
      num_old_parameters + num_new_parameters) {
    return false;
  }

  // Check that old parameters and the return type are preserved.
  for (uint32_t i = 0; i < num_old_parameters; ++i) {
    if (new_type_inst->GetSingleWordInOperand(i) !=
        old_type_inst->GetSingleWordInOperand(i)) {
      return false;
    }
  }

  // Check that new parameters have been appended.
  for (int i = 0; i < num_new_parameters; ++i) {
    if (new_type_inst->GetSingleWordInOperand(i + num_old_parameters) !=
        new_type_ids[i]) {
      return false;
    }
  }

  return true;
}

void TransformationAddParameters::Apply(
    opt::IRContext* ir_context, TransformationContext* /*unused*/) const {
  // Retrieve all data from the message
  auto function_id = message_.function_id();
  const auto& new_parameter_type = message_.new_parameter_type();
  const auto& new_parameter_id = message_.new_parameter_id();
  const auto& constant_id = message_.constant_id();

  // Find the function that will be transformed
  auto* function = fuzzerutil::FindFunction(ir_context, function_id);
  assert(function && "Can't find the function");

  // Change function's type
  function->DefInst().SetInOperand(1, {message_.new_type_id()});

  // Add new parameters to the function.
  for (int i = 0, n = new_parameter_id.size(); i < n; ++i) {
    function->AddParameter(MakeUnique<opt::Instruction>(
        ir_context, SpvOpFunctionParameter, new_parameter_type[i],
        new_parameter_id[i], opt::Instruction::OperandList()));

    // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3403):
    //  Add an PointeeValueIsIrrelevant fact if the parameter is a pointer.
  }

  // Fix all OpFunctionCall instructions.
  ir_context->get_def_use_mgr()->ForEachUser(
      &function->DefInst(),
      [function_id, &constant_id](opt::Instruction* call) {
        if (call->opcode() != SpvOpFunctionCall ||
            call->GetSingleWordInOperand(0) != function_id) {
          return;
        }

        for (auto id : constant_id) {
          // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3177):
          //  it would be good to mark this usage of |id| as irrelevant, so that
          //  we can perform some interesting transformations on it later.
          call->AddOperand({SPV_OPERAND_TYPE_ID, {id}});
        }
      });

  // Update module's id bound. We can safely dereference the result of
  // max_element since |new_parameter_id| is guaranteed to have elements.
  fuzzerutil::UpdateModuleIdBound(
      ir_context,
      *std::max_element(new_parameter_id.begin(), new_parameter_id.end()));

  // Make sure our changes are analyzed.
  ir_context->InvalidateAnalysesExceptFor(
      opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationAddParameters::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_add_parameters() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

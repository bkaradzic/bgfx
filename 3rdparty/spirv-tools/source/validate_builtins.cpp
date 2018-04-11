// Copyright (c) 2018 Google LLC.
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

// Validates correctness of built-in variables.

#include "validate.h"

#include <functional>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "diagnostic.h"
#include "opcode.h"
#include "spirv_target_env.h"
#include "util/bitutils.h"
#include "val/instruction.h"
#include "val/validation_state.h"

namespace libspirv {

namespace {

// Returns a short textual description of the id defined by the given
// instruction.
std::string GetIdDesc(const Instruction& inst) {
  std::ostringstream ss;
  ss << "ID <" << inst.id() << "> (Op" << spvOpcodeString(inst.opcode()) << ")";
  return ss.str();
}

// Gets underlying data type which is
// - member type if instruction is OpTypeStruct
//   (member index is taken from decoration).
// - data type if id creates a pointer.
// - type of the constant if instruction is OpConst or OpSpecConst.
//
// Fails in any other case. The function is based on built-ins allowed by
// the Vulkan spec.
// TODO: If non-Vulkan validation rules are added then it might need
// to be refactored.
spv_result_t GetUnderlyingType(const ValidationState_t& _,
                               const Decoration& decoration,
                               const Instruction& inst,
                               uint32_t* underlying_type) {
  if (decoration.struct_member_index() != Decoration::kInvalidMember) {
    assert(inst.opcode() == SpvOpTypeStruct);
    *underlying_type = inst.word(decoration.struct_member_index() + 2);
    return SPV_SUCCESS;
  }

  assert(inst.opcode() != SpvOpTypeStruct);

  if (spvOpcodeIsConstant(inst.opcode())) {
    *underlying_type = inst.type_id();
    return SPV_SUCCESS;
  }

  uint32_t storage_class = 0;
  if (!_.GetPointerTypeInfo(inst.type_id(), underlying_type, &storage_class)) {
    return _.diag(SPV_ERROR_INVALID_DATA)
           << GetIdDesc(inst)
           << " is decorated with BuiltIn. BuiltIn decoration should only be "
              "applied to struct types, variables and constants.";
  }
  return SPV_SUCCESS;
}

// Returns Storage Class used by the instruction if applicable.
// Returns SpvStorageClassMax if not.
SpvStorageClass GetStorageClass(const Instruction& inst) {
  switch (inst.opcode()) {
    case SpvOpTypePointer:
    case SpvOpTypeForwardPointer: {
      return SpvStorageClass(inst.word(2));
    }
    case SpvOpVariable: {
      return SpvStorageClass(inst.word(3));
    }
    case SpvOpGenericCastToPtrExplicit: {
      return SpvStorageClass(inst.word(4));
    }
    default: { break; }
  }
  return SpvStorageClassMax;
}

// Helper class managing validation of built-ins.
// TODO: Generic functionality of this class can be moved into
// ValidationState_t to be made available to other users.
class BuiltInsValidator {
 public:
  BuiltInsValidator(const ValidationState_t& vstate) : _(vstate) {}

  // Run validation.
  spv_result_t Run();

 private:
  // Goes through all decorations in the module, if decoration is BuiltIn
  // calls ValidateSingleBuiltInAtDefinition().
  spv_result_t ValidateBuiltInsAtDefinition();

  // Validates the instruction defining an id with built-in decoration.
  // Can be called multiple times for the same id, if multiple built-ins are
  // specified. Seeds id_to_at_reference_checks_ with decorated ids if needed.
  spv_result_t ValidateSingleBuiltInAtDefinition(const Decoration& decoration,
                                                 const Instruction& inst);

  // The following section contains functions which are called when id defined
  // by |inst| is decorated with BuiltIn |decoration|.
  // Most functions are specific to a single built-in and have naming scheme:
  // ValidateXYZAtDefinition. Some functions are common to multiple kinds of
  // BuiltIn.
  spv_result_t ValidateClipOrCullDistanceAtDefinition(
      const Decoration& decoration, const Instruction& inst);
  spv_result_t ValidateFragCoordAtDefinition(const Decoration& decoration,
                                             const Instruction& inst);
  spv_result_t ValidateFragDepthAtDefinition(const Decoration& decoration,
                                             const Instruction& inst);
  spv_result_t ValidateFrontFacingAtDefinition(const Decoration& decoration,
                                               const Instruction& inst);
  spv_result_t ValidateHelperInvocationAtDefinition(
      const Decoration& decoration, const Instruction& inst);
  spv_result_t ValidateInvocationIdAtDefinition(const Decoration& decoration,
                                                const Instruction& inst);
  spv_result_t ValidateInstanceIndexAtDefinition(const Decoration& decoration,
                                                 const Instruction& inst);
  spv_result_t ValidateLayerOrViewportIndexAtDefinition(
      const Decoration& decoration, const Instruction& inst);
  spv_result_t ValidatePatchVerticesAtDefinition(const Decoration& decoration,
                                                 const Instruction& inst);
  spv_result_t ValidatePointCoordAtDefinition(const Decoration& decoration,
                                              const Instruction& inst);
  spv_result_t ValidatePointSizeAtDefinition(const Decoration& decoration,
                                             const Instruction& inst);
  spv_result_t ValidatePositionAtDefinition(const Decoration& decoration,
                                            const Instruction& inst);
  spv_result_t ValidatePrimitiveIdAtDefinition(const Decoration& decoration,
                                               const Instruction& inst);
  spv_result_t ValidateSampleIdAtDefinition(const Decoration& decoration,
                                            const Instruction& inst);
  spv_result_t ValidateSampleMaskAtDefinition(const Decoration& decoration,
                                              const Instruction& inst);
  spv_result_t ValidateSamplePositionAtDefinition(const Decoration& decoration,
                                                  const Instruction& inst);
  spv_result_t ValidateTessCoordAtDefinition(const Decoration& decoration,
                                             const Instruction& inst);
  spv_result_t ValidateTessLevelOuterAtDefinition(const Decoration& decoration,
                                                  const Instruction& inst);
  spv_result_t ValidateTessLevelInnerAtDefinition(const Decoration& decoration,
                                                  const Instruction& inst);
  spv_result_t ValidateVertexIndexAtDefinition(const Decoration& decoration,
                                               const Instruction& inst);
  spv_result_t ValidateWorkgroupSizeAtDefinition(const Decoration& decoration,
                                                 const Instruction& inst);
  // Used for GlobalInvocationId, LocalInvocationId, NumWorkgroups, WorkgroupId.
  spv_result_t ValidateComputeShaderI32Vec3InputAtDefinition(
      const Decoration& decoration, const Instruction& inst);

  // The following section contains functions which are called when id defined
  // by |referenced_inst| is
  // 1. referenced by |referenced_from_inst|
  // 2. dependent on |built_in_inst| which is decorated with BuiltIn
  // |decoration|. Most functions are specific to a single built-in and have
  // naming scheme: ValidateXYZAtReference. Some functions are common to
  // multiple kinds of BuiltIn.
  spv_result_t ValidateFragCoordAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateFragDepthAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateFrontFacingAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateHelperInvocationAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateInvocationIdAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateInstanceIndexAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidatePatchVerticesAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidatePointCoordAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidatePointSizeAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidatePositionAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidatePrimitiveIdAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateSampleIdAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateSampleMaskAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateSamplePositionAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateTessCoordAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateTessLevelAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateVertexIndexAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateLayerOrViewportIndexAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateWorkgroupSizeAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  spv_result_t ValidateClipOrCullDistanceAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  // Used for GlobalInvocationId, LocalInvocationId, NumWorkgroups, WorkgroupId.
  spv_result_t ValidateComputeShaderI32Vec3InputAtReference(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  // Validates that |built_in_inst| is not (even indirectly) referenced from
  // within a function which can be called with |execution_model|.
  //
  // |comment| - text explaining why the restriction was imposed.
  // |decoration| - BuiltIn decoration which causes the restriction.
  // |referenced_inst| - instruction which is dependent on |built_in_inst| and
  //                     defines the id which was referenced.
  // |referenced_from_inst| - instruction which references id defined by
  //                          |referenced_inst| from within a function.
  spv_result_t ValidateNotCalledWithExecutionModel(
      const char* comment, SpvExecutionModel execution_model,
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst);

  // The following section contains functions which check that the decorated
  // variable has the type specified in the function name. |diag| would be
  // called with a corresponding error message, if validation is not successful.
  spv_result_t ValidateBool(
      const Decoration& decoration, const Instruction& inst,
      const std::function<spv_result_t(const std::string& message)>& diag);
  spv_result_t ValidateI32(
      const Decoration& decoration, const Instruction& inst,
      const std::function<spv_result_t(const std::string& message)>& diag);
  spv_result_t ValidateI32Vec(
      const Decoration& decoration, const Instruction& inst,
      uint32_t num_components,
      const std::function<spv_result_t(const std::string& message)>& diag);
  spv_result_t ValidateI32Arr(
      const Decoration& decoration, const Instruction& inst,
      const std::function<spv_result_t(const std::string& message)>& diag);
  spv_result_t ValidateF32(
      const Decoration& decoration, const Instruction& inst,
      const std::function<spv_result_t(const std::string& message)>& diag);
  spv_result_t ValidateF32Vec(
      const Decoration& decoration, const Instruction& inst,
      uint32_t num_components,
      const std::function<spv_result_t(const std::string& message)>& diag);
  // If |num_components| is zero, the number of components is not checked.
  spv_result_t ValidateF32Arr(
      const Decoration& decoration, const Instruction& inst,
      uint32_t num_components,
      const std::function<spv_result_t(const std::string& message)>& diag);

  // Generates strings like "Member #0 of struct ID <2>".
  std::string GetDefinitionDesc(const Decoration& decoration,
                                const Instruction& inst) const;

  // Generates strings like "ID <51> (OpTypePointer) is referencing ID <2>
  // (OpTypeStruct) which is decorated with BuiltIn Position".
  std::string GetReferenceDesc(
      const Decoration& decoration, const Instruction& built_in_inst,
      const Instruction& referenced_inst,
      const Instruction& referenced_from_inst,
      SpvExecutionModel execution_model = SpvExecutionModelMax) const;

  // Generates strings like "ID <51> (OpTypePointer) uses storage class
  // UniformConstant".
  std::string GetStorageClassDesc(const Instruction& inst) const;

  // Updates inner working of the class. Is called sequentially for every
  // instruction.
  void Update(const Instruction& inst);

  // Traverses call tree and computes function_to_entry_points_.
  void ComputeFunctionToEntryPointMapping();

  const ValidationState_t& _;

  // Mapping id -> list of rules which validate instruction referencing the
  // id. Rules can create new rules and add them to this container.
  // Using std::map, and not std::unordered_map to avoid iterator invalidation
  // during rehashing.
  std::map<uint32_t, std::list<std::function<spv_result_t(const Instruction&)>>>
      id_to_at_reference_checks_;

  // Id of the function we are currently inside. 0 if not inside a function.
  uint32_t function_id_ = 0;

  // Entry points which can (indirectly) call the current function.
  // The pointer either points to a vector inside to function_to_entry_points_
  // or to no_entry_points_. The pointer is guaranteed to never be null.
  const std::vector<uint32_t> no_entry_points;
  const std::vector<uint32_t>* entry_points_ = &no_entry_points;

  // Mapping function -> array of entry points inside this
  // module which can (indirectly) call the function.
  std::unordered_map<uint32_t, std::vector<uint32_t>> function_to_entry_points_;

  // Execution models with which the current function can be called.
  std::set<SpvExecutionModel> execution_models_;
};

void BuiltInsValidator::Update(const Instruction& inst) {
  const SpvOp opcode = inst.opcode();
  if (opcode == SpvOpFunction) {
    // Entering a function.
    assert(function_id_ == 0);
    function_id_ = inst.id();
    execution_models_.clear();
    const auto it = function_to_entry_points_.find(function_id_);
    if (it == function_to_entry_points_.end()) {
      entry_points_ = &no_entry_points;
    } else {
      entry_points_ = &it->second;
      // Collect execution models from all entry points from which the current
      // function can be called.
      for (const uint32_t entry_point : *entry_points_) {
        if (const auto* models = _.GetExecutionModels(entry_point)) {
          execution_models_.insert(models->begin(), models->end());
        }
      }
    }
  }

  if (opcode == SpvOpFunctionEnd) {
    // Exiting a function.
    assert(function_id_ != 0);
    function_id_ = 0;
    entry_points_ = &no_entry_points;
    execution_models_.clear();
  }
}

void BuiltInsValidator::ComputeFunctionToEntryPointMapping() {
  // TODO: Move this into validation_state.cpp.
  for (const uint32_t entry_point : _.entry_points()) {
    std::stack<uint32_t> call_stack;
    std::set<uint32_t> visited;
    call_stack.push(entry_point);
    while (!call_stack.empty()) {
      const uint32_t called_func_id = call_stack.top();
      call_stack.pop();
      if (!visited.insert(called_func_id).second) continue;

      function_to_entry_points_[called_func_id].push_back(entry_point);

      const Function* called_func = _.function(called_func_id);
      assert(called_func);
      for (const uint32_t new_call : called_func->function_call_targets()) {
        call_stack.push(new_call);
      }
    }
  }
}

std::string BuiltInsValidator::GetDefinitionDesc(
    const Decoration& decoration, const Instruction& inst) const {
  std::ostringstream ss;
  if (decoration.struct_member_index() != Decoration::kInvalidMember) {
    assert(inst.opcode() == SpvOpTypeStruct);
    ss << "Member #" << decoration.struct_member_index();
    ss << " of struct ID <" << inst.id() << ">";
  } else {
    ss << GetIdDesc(inst);
  }
  return ss.str();
}

std::string BuiltInsValidator::GetReferenceDesc(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst, const Instruction& referenced_from_inst,
    SpvExecutionModel execution_model) const {
  std::ostringstream ss;
  ss << GetIdDesc(referenced_from_inst) << " is referencing "
     << GetIdDesc(referenced_inst);
  if (built_in_inst.id() != referenced_inst.id()) {
    ss << " which is dependent on " << GetIdDesc(built_in_inst);
  }

  ss << " which is decorated with BuiltIn ";
  ss << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                      decoration.params()[0]);
  if (function_id_) {
    ss << " in function <" << function_id_ << ">";
    if (execution_model != SpvExecutionModelMax) {
      ss << " called with execution model ";
      ss << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_EXECUTION_MODEL,
                                          execution_model);
    }
  }
  ss << ".";
  return ss.str();
}

std::string BuiltInsValidator::GetStorageClassDesc(
    const Instruction& inst) const {
  std::ostringstream ss;
  ss << GetIdDesc(inst) << " uses storage class ";
  ss << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_STORAGE_CLASS,
                                      GetStorageClass(inst));
  ss << ".";
  return ss.str();
}

spv_result_t BuiltInsValidator::ValidateBool(
    const Decoration& decoration, const Instruction& inst,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  if (!_.IsBoolScalarType(underlying_type)) {
    return diag(GetDefinitionDesc(decoration, inst) + " is not a bool scalar.");
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateI32(
    const Decoration& decoration, const Instruction& inst,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  if (!_.IsIntScalarType(underlying_type)) {
    return diag(GetDefinitionDesc(decoration, inst) + " is not an int scalar.");
  }

  const uint32_t bit_width = _.GetBitWidth(underlying_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst) << " has bit width " << bit_width
       << ".";
    return diag(ss.str());
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateF32(
    const Decoration& decoration, const Instruction& inst,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  if (!_.IsFloatScalarType(underlying_type)) {
    return diag(GetDefinitionDesc(decoration, inst) +
                " is not a float scalar.");
  }

  const uint32_t bit_width = _.GetBitWidth(underlying_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst) << " has bit width " << bit_width
       << ".";
    return diag(ss.str());
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateI32Vec(
    const Decoration& decoration, const Instruction& inst,
    uint32_t num_components,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  if (!_.IsIntVectorType(underlying_type)) {
    return diag(GetDefinitionDesc(decoration, inst) + " is not an int vector.");
  }

  const uint32_t actual_num_components = _.GetDimension(underlying_type);
  if (_.GetDimension(underlying_type) != num_components) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst) << " has "
       << actual_num_components << " components.";
    return diag(ss.str());
  }

  const uint32_t bit_width = _.GetBitWidth(underlying_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst)
       << " has components with bit width " << bit_width << ".";
    return diag(ss.str());
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateF32Vec(
    const Decoration& decoration, const Instruction& inst,
    uint32_t num_components,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  if (!_.IsFloatVectorType(underlying_type)) {
    return diag(GetDefinitionDesc(decoration, inst) +
                " is not a float vector.");
  }

  const uint32_t actual_num_components = _.GetDimension(underlying_type);
  if (_.GetDimension(underlying_type) != num_components) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst) << " has "
       << actual_num_components << " components.";
    return diag(ss.str());
  }

  const uint32_t bit_width = _.GetBitWidth(underlying_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst)
       << " has components with bit width " << bit_width << ".";
    return diag(ss.str());
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateI32Arr(
    const Decoration& decoration, const Instruction& inst,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  const Instruction* const type_inst = _.FindDef(underlying_type);
  if (type_inst->opcode() != SpvOpTypeArray) {
    return diag(GetDefinitionDesc(decoration, inst) + " is not an array.");
  }

  const uint32_t component_type = type_inst->word(2);
  if (!_.IsIntScalarType(component_type)) {
    return diag(GetDefinitionDesc(decoration, inst) +
                " components are not int scalar.");
  }

  const uint32_t bit_width = _.GetBitWidth(component_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst)
       << " has components with bit width " << bit_width << ".";
    return diag(ss.str());
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateF32Arr(
    const Decoration& decoration, const Instruction& inst,
    uint32_t num_components,
    const std::function<spv_result_t(const std::string& message)>& diag) {
  uint32_t underlying_type = 0;
  if (spv_result_t error =
          GetUnderlyingType(_, decoration, inst, &underlying_type)) {
    return error;
  }

  const Instruction* const type_inst = _.FindDef(underlying_type);
  if (type_inst->opcode() != SpvOpTypeArray) {
    return diag(GetDefinitionDesc(decoration, inst) + " is not an array.");
  }

  const uint32_t component_type = type_inst->word(2);
  if (!_.IsFloatScalarType(component_type)) {
    return diag(GetDefinitionDesc(decoration, inst) +
                " components are not float scalar.");
  }

  const uint32_t bit_width = _.GetBitWidth(component_type);
  if (bit_width != 32) {
    std::ostringstream ss;
    ss << GetDefinitionDesc(decoration, inst)
       << " has components with bit width " << bit_width << ".";
    return diag(ss.str());
  }

  if (num_components != 0) {
    uint64_t actual_num_components = 0;
    if (!_.GetConstantValUint64(type_inst->word(3), &actual_num_components)) {
      assert(0 && "Array type definition is corrupt");
    }
    if (actual_num_components != num_components) {
      std::ostringstream ss;
      ss << GetDefinitionDesc(decoration, inst) << " has "
         << actual_num_components << " components.";
      return diag(ss.str());
    }
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateNotCalledWithExecutionModel(
    const char* comment, SpvExecutionModel execution_model,
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (function_id_) {
    if (execution_models_.count(execution_model)) {
      const char* execution_model_str = _.grammar().lookupOperandName(
          SPV_OPERAND_TYPE_EXECUTION_MODEL, execution_model);
      const char* built_in_str = _.grammar().lookupOperandName(
          SPV_OPERAND_TYPE_BUILT_IN, decoration.params()[0]);
      return _.diag(SPV_ERROR_INVALID_DATA)
             << comment << " " << GetIdDesc(referenced_inst) << " depends on "
             << GetIdDesc(built_in_inst) << " which is decorated with BuiltIn "
             << built_in_str << "."
             << " Id <" << referenced_inst.id() << "> is later referenced by "
             << GetIdDesc(referenced_from_inst) << " in function <"
             << function_id_ << "> which is called with execution model "
             << execution_model_str << ".";
    }
  } else {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(
        std::bind(&BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
                  comment, execution_model, decoration, built_in_inst,
                  referenced_from_inst, std::placeholders::_1));
  }
  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateClipOrCullDistanceAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Arr(
            decoration, inst, /* Any number of components */ 0,
            [this, &decoration](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn "
                     << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                      decoration.params()[0])
                     << " variable needs to be a 32-bit float array. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateClipOrCullDistanceAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateClipOrCullDistanceAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn "
             << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                              decoration.params()[0])
             << " to be only used for variables with Input or Output storage "
                "class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassInput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn ClipDistance/CullDistance to be "
          "used for variables with Input storage class if execution model is "
          "Vertex.",
          SpvExecutionModelVertex, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    if (storage_class == SpvStorageClassOutput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn ClipDistance/CullDistance to be "
          "used for variables with Output storage class if execution model is "
          "Fragment.",
          SpvExecutionModelFragment, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelFragment:
        case SpvExecutionModelVertex:
        case SpvExecutionModelTessellationControl:
        case SpvExecutionModelTessellationEvaluation:
        case SpvExecutionModelGeometry: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn "
                 << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                  decoration.params()[0])
                 << " to be used only with Fragment, Vertex, "
                    "TessellationControl, TessellationEvaluation or Geometry "
                    "execution models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(
        std::bind(&BuiltInsValidator::ValidateClipOrCullDistanceAtReference,
                  this, decoration, built_in_inst, referenced_from_inst,
                  std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateFragCoordAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Vec(
            decoration, inst, 4,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn FragCoord "
                        "variable needs to be a 4-component 32-bit float "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateFragCoordAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateFragCoordAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn FragCoord to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn FragCoord to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateFragCoordAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateFragDepthAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn FragDepth "
                        "variable needs to be a 32-bit float scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateFragDepthAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateFragDepthAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn FragDepth to be only used for "
                "variables with Output storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn FragDepth to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }

    for (const uint32_t entry_point : *entry_points_) {
      // Every entry point from which this function is called needs to have
      // Execution Mode DepthReplacing.
      const auto* modes = _.GetExecutionModes(entry_point);
      if (!modes || !modes->count(SpvExecutionModeDepthReplacing)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec requires DepthReplacing execution mode to be "
                  "declared when using BuiltIn FragDepth. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateFragDepthAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateFrontFacingAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateBool(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn FrontFacing "
                        "variable needs to be a bool scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateFrontFacingAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateFrontFacingAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn FrontFacing to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn FrontFacing to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateFrontFacingAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateHelperInvocationAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateBool(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn HelperInvocation "
                        "variable needs to be a bool scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateHelperInvocationAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateHelperInvocationAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn HelperInvocation to be only used "
                "for variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn HelperInvocation to be used only "
                  "with Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(
        std::bind(&BuiltInsValidator::ValidateHelperInvocationAtReference, this,
                  decoration, built_in_inst, referenced_from_inst,
                  std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateInvocationIdAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn InvocationId "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateInvocationIdAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateInvocationIdAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn InvocationId to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelTessellationControl &&
          execution_model != SpvExecutionModelGeometry) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn InvocationId to be used only "
                  "with TessellationControl or Geometry execution models. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateInvocationIdAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateInstanceIndexAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn InstanceIndex "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateInstanceIndexAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateInstanceIndexAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn InstanceIndex to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelVertex) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn InstanceIndex to be used only "
                  "with Vertex execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateInstanceIndexAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidatePatchVerticesAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn PatchVertices "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidatePatchVerticesAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidatePatchVerticesAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn PatchVertices to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelTessellationControl &&
          execution_model != SpvExecutionModelTessellationEvaluation) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn PatchVertices to be used only "
                  "with TessellationControl or TessellationEvaluation "
                  "execution models. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidatePatchVerticesAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidatePointCoordAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Vec(
            decoration, inst, 2,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn PointCoord "
                        "variable needs to be a 2-component 32-bit float "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidatePointCoordAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidatePointCoordAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn PointCoord to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn PointCoord to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidatePointCoordAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidatePointSizeAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn PointSize "
                        "variable needs to be a 32-bit float scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidatePointSizeAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidatePointSizeAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn PointSize to be only used for "
                "variables with Input or Output storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassInput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn PointSize to be used for "
          "variables with Input storage class if execution model is Vertex.",
          SpvExecutionModelVertex, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelVertex:
        case SpvExecutionModelTessellationControl:
        case SpvExecutionModelTessellationEvaluation:
        case SpvExecutionModelGeometry: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn PointSize to be used only with "
                    "Vertex, TessellationControl, TessellationEvaluation or "
                    "Geometry execution models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidatePointSizeAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidatePositionAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Vec(
            decoration, inst, 4,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn Position "
                        "variable needs to be a 4-component 32-bit float "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidatePositionAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidatePositionAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn Position to be only used for "
                "variables with Input or Output storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassInput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn Position to be used for variables "
          "with Input storage class if execution model is Vertex.",
          SpvExecutionModelVertex, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelVertex:
        case SpvExecutionModelTessellationControl:
        case SpvExecutionModelTessellationEvaluation:
        case SpvExecutionModelGeometry: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn Position to be used only with "
                    "Vertex, TessellationControl, TessellationEvaluation or "
                    "Geometry execution models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidatePositionAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidatePrimitiveIdAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn PrimitiveId "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidatePrimitiveIdAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidatePrimitiveIdAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn PrimitiveId to be only used for "
                "variables with Input or Output storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassOutput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn PrimitiveId to be used for "
          "variables with Output storage class if execution model is "
          "TessellationControl.",
          SpvExecutionModelTessellationControl, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn PrimitiveId to be used for "
          "variables with Output storage class if execution model is "
          "TessellationEvaluation.",
          SpvExecutionModelTessellationEvaluation, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn PrimitiveId to be used for "
          "variables with Output storage class if execution model is Fragment.",
          SpvExecutionModelFragment, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelFragment:
        case SpvExecutionModelTessellationControl:
        case SpvExecutionModelTessellationEvaluation:
        case SpvExecutionModelGeometry: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn PrimitiveId to be used only "
                    "with Fragment, TessellationControl, "
                    "TessellationEvaluation or Geometry execution models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidatePrimitiveIdAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateSampleIdAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn SampleId "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateSampleIdAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateSampleIdAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn SampleId to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn SampleId to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateSampleIdAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateSampleMaskAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32Arr(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn SampleMask "
                        "variable needs to be a 32-bit int array. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateSampleMaskAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateSampleMaskAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn SampleMask to be only used for "
                "variables with Input or Output storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn SampleMask to be used only with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateSampleMaskAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateSamplePositionAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Vec(
            decoration, inst, 2,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn SamplePosition "
                        "variable needs to be a 2-component 32-bit float "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateSamplePositionAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateSamplePositionAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn SamplePosition to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelFragment) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn SamplePosition to be used only "
                  "with "
                  "Fragment execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateSamplePositionAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateTessCoordAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Vec(
            decoration, inst, 3,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn TessCoord "
                        "variable needs to be a 3-component 32-bit float "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateTessCoordAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateTessCoordAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn TessCoord to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelTessellationEvaluation) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn TessCoord to be used only with "
                  "TessellationEvaluation execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateTessCoordAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateTessLevelOuterAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Arr(
            decoration, inst, 4,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn TessLevelOuter "
                        "variable needs to be a 4-component 32-bit float "
                        "array. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateTessLevelAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateTessLevelInnerAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateF32Arr(
            decoration, inst, 2,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn TessLevelOuter "
                        "variable needs to be a 2-component 32-bit float "
                        "array. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateTessLevelAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateTessLevelAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn "
             << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                              decoration.params()[0])
             << " to be only used for variables with Input or Output storage "
                "class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassInput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow TessLevelOuter/TessLevelInner to be used "
          "for variables with Input storage class if execution model is "
          "TessellationControl.",
          SpvExecutionModelTessellationControl, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    if (storage_class == SpvStorageClassOutput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow TessLevelOuter/TessLevelInner to be used "
          "for variables with Output storage class if execution model is "
          "TessellationEvaluation.",
          SpvExecutionModelTessellationEvaluation, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelTessellationControl:
        case SpvExecutionModelTessellationEvaluation: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn "
                 << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                  decoration.params()[0])
                 << " to be used only with TessellationControl or "
                    "TessellationEvaluation execution models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateTessLevelAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateVertexIndexAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn VertexIndex "
                        "variable needs to be a 32-bit int scalar. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateVertexIndexAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateVertexIndexAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn VertexIndex to be only used for "
                "variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelVertex) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn VertexIndex to be used only with "
                  "Vertex execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateVertexIndexAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateLayerOrViewportIndexAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32(
            decoration, inst,
            [this, &decoration](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn "
                     << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                      decoration.params()[0])
                     << "variable needs to be a 32-bit int scalar. " << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateLayerOrViewportIndexAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateLayerOrViewportIndexAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput &&
        storage_class != SpvStorageClassOutput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn "
             << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                              decoration.params()[0])
             << " to be only used for variables with Input or Output storage "
                "class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    if (storage_class == SpvStorageClassInput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn Layer and ViewportIndex to be "
          "used for variables with Input storage class if execution model is "
          "Geometry.",
          SpvExecutionModelGeometry, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    if (storage_class == SpvStorageClassOutput) {
      assert(function_id_ == 0);
      id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
          &BuiltInsValidator::ValidateNotCalledWithExecutionModel, this,
          "Vulkan spec doesn't allow BuiltIn Layer and ViewportIndex to be "
          "used for variables with Output storage class if execution model is "
          "Fragment.",
          SpvExecutionModelFragment, decoration, built_in_inst,
          referenced_from_inst, std::placeholders::_1));
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      switch (execution_model) {
        case SpvExecutionModelGeometry:
        case SpvExecutionModelFragment: {
          // Ok.
          break;
        }

        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Vulkan spec allows BuiltIn "
                 << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                  decoration.params()[0])
                 << " to be used only with Fragment or Geometry execution "
                    "models. "
                 << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                     referenced_from_inst, execution_model);
        }
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(
        std::bind(&BuiltInsValidator::ValidateLayerOrViewportIndexAtReference,
                  this, decoration, built_in_inst, referenced_from_inst,
                  std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateComputeShaderI32Vec3InputAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (spv_result_t error = ValidateI32Vec(
            decoration, inst, 3,
            [this, &decoration](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn "
                     << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                      decoration.params()[0])
                     << " variable needs to be a 3-component 32-bit int "
                        "vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateComputeShaderI32Vec3InputAtReference(decoration, inst, inst,
                                                      inst);
}

spv_result_t BuiltInsValidator::ValidateComputeShaderI32Vec3InputAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn "
             << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                              decoration.params()[0])
             << " to be only used for variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelGLCompute) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn "
               << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                decoration.params()[0])
               << " to be used only with GLCompute execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateComputeShaderI32Vec3InputAtReference, this,
        decoration, built_in_inst, referenced_from_inst,
        std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateWorkgroupSizeAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    if (!spvOpcodeIsConstant(inst.opcode())) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec requires BuiltIn WorkgroupSize to be a constant. "
             << GetIdDesc(inst) << " is not a constant.";
    }

    if (spv_result_t error = ValidateI32Vec(
            decoration, inst, 3,
            [this](const std::string& message) -> spv_result_t {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << "According to the Vulkan spec BuiltIn WorkgroupSize "
                        "variable "
                        "needs to be a 3-component 32-bit int vector. "
                     << message;
            })) {
      return error;
    }
  }

  // Seed at reference checks with this built-in.
  return ValidateWorkgroupSizeAtReference(decoration, inst, inst, inst);
}

spv_result_t BuiltInsValidator::ValidateWorkgroupSizeAtReference(
    const Decoration& decoration, const Instruction& built_in_inst,
    const Instruction& referenced_inst,
    const Instruction& referenced_from_inst) {
  if (spvIsVulkanEnv(_.context()->target_env)) {
    const SpvStorageClass storage_class = GetStorageClass(referenced_from_inst);
    if (storage_class != SpvStorageClassMax &&
        storage_class != SpvStorageClassInput) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Vulkan spec allows BuiltIn "
             << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                              decoration.params()[0])
             << " to be only used for variables with Input storage class. "
             << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                 referenced_from_inst)
             << " " << GetStorageClassDesc(referenced_from_inst);
    }

    for (const SpvExecutionModel execution_model : execution_models_) {
      if (execution_model != SpvExecutionModelGLCompute) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Vulkan spec allows BuiltIn "
               << _.grammar().lookupOperandName(SPV_OPERAND_TYPE_BUILT_IN,
                                                decoration.params()[0])
               << " to be used only with GLCompute execution model. "
               << GetReferenceDesc(decoration, built_in_inst, referenced_inst,
                                   referenced_from_inst, execution_model);
      }
    }
  }

  if (function_id_ == 0) {
    // Propagate this rule to all dependant ids in the global scope.
    id_to_at_reference_checks_[referenced_from_inst.id()].push_back(std::bind(
        &BuiltInsValidator::ValidateWorkgroupSizeAtReference, this, decoration,
        built_in_inst, referenced_from_inst, std::placeholders::_1));
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateSingleBuiltInAtDefinition(
    const Decoration& decoration, const Instruction& inst) {
  const SpvBuiltIn label = SpvBuiltIn(decoration.params()[0]);
  // If you are adding a new BuiltIn enum, please register it here.
  // If the newly added enum has validation rules associated with it
  // consider leaving a TODO and/or creating an issue.
  switch (label) {
    case SpvBuiltInClipDistance:
    case SpvBuiltInCullDistance: {
      return ValidateClipOrCullDistanceAtDefinition(decoration, inst);
    }
    case SpvBuiltInFragCoord: {
      return ValidateFragCoordAtDefinition(decoration, inst);
    }
    case SpvBuiltInFragDepth: {
      return ValidateFragDepthAtDefinition(decoration, inst);
    }
    case SpvBuiltInFrontFacing: {
      return ValidateFrontFacingAtDefinition(decoration, inst);
    }
    case SpvBuiltInGlobalInvocationId:
    case SpvBuiltInLocalInvocationId:
    case SpvBuiltInNumWorkgroups:
    case SpvBuiltInWorkgroupId: {
      return ValidateComputeShaderI32Vec3InputAtDefinition(decoration, inst);
    }
    case SpvBuiltInHelperInvocation: {
      return ValidateHelperInvocationAtDefinition(decoration, inst);
    }
    case SpvBuiltInInvocationId: {
      return ValidateInvocationIdAtDefinition(decoration, inst);
    }
    case SpvBuiltInInstanceIndex: {
      return ValidateInstanceIndexAtDefinition(decoration, inst);
    }
    case SpvBuiltInLayer:
    case SpvBuiltInViewportIndex: {
      return ValidateLayerOrViewportIndexAtDefinition(decoration, inst);
    }
    case SpvBuiltInPatchVertices: {
      return ValidatePatchVerticesAtDefinition(decoration, inst);
    }
    case SpvBuiltInPointCoord: {
      return ValidatePointCoordAtDefinition(decoration, inst);
    }
    case SpvBuiltInPointSize: {
      return ValidatePointSizeAtDefinition(decoration, inst);
    }
    case SpvBuiltInPosition: {
      return ValidatePositionAtDefinition(decoration, inst);
    }
    case SpvBuiltInPrimitiveId: {
      return ValidatePrimitiveIdAtDefinition(decoration, inst);
    }
    case SpvBuiltInSampleId: {
      return ValidateSampleIdAtDefinition(decoration, inst);
    }
    case SpvBuiltInSampleMask: {
      return ValidateSampleMaskAtDefinition(decoration, inst);
    }
    case SpvBuiltInSamplePosition: {
      return ValidateSamplePositionAtDefinition(decoration, inst);
    }
    case SpvBuiltInTessCoord: {
      return ValidateTessCoordAtDefinition(decoration, inst);
    }
    case SpvBuiltInTessLevelOuter: {
      return ValidateTessLevelOuterAtDefinition(decoration, inst);
    }
    case SpvBuiltInTessLevelInner: {
      return ValidateTessLevelInnerAtDefinition(decoration, inst);
    }
    case SpvBuiltInVertexIndex: {
      return ValidateVertexIndexAtDefinition(decoration, inst);
    }
    case SpvBuiltInWorkgroupSize: {
      return ValidateWorkgroupSizeAtDefinition(decoration, inst);
    }
    case SpvBuiltInVertexId:
    case SpvBuiltInInstanceId:
    case SpvBuiltInLocalInvocationIndex:
    case SpvBuiltInWorkDim:
    case SpvBuiltInGlobalSize:
    case SpvBuiltInEnqueuedWorkgroupSize:
    case SpvBuiltInGlobalOffset:
    case SpvBuiltInGlobalLinearId:
    case SpvBuiltInSubgroupSize:
    case SpvBuiltInSubgroupMaxSize:
    case SpvBuiltInNumSubgroups:
    case SpvBuiltInNumEnqueuedSubgroups:
    case SpvBuiltInSubgroupId:
    case SpvBuiltInSubgroupLocalInvocationId:
    case SpvBuiltInSubgroupEqMaskKHR:
    case SpvBuiltInSubgroupGeMaskKHR:
    case SpvBuiltInSubgroupGtMaskKHR:
    case SpvBuiltInSubgroupLeMaskKHR:
    case SpvBuiltInSubgroupLtMaskKHR:
    case SpvBuiltInBaseVertex:
    case SpvBuiltInBaseInstance:
    case SpvBuiltInDrawIndex:
    case SpvBuiltInDeviceIndex:
    case SpvBuiltInViewIndex:
    case SpvBuiltInBaryCoordNoPerspAMD:
    case SpvBuiltInBaryCoordNoPerspCentroidAMD:
    case SpvBuiltInBaryCoordNoPerspSampleAMD:
    case SpvBuiltInBaryCoordSmoothAMD:
    case SpvBuiltInBaryCoordSmoothCentroidAMD:
    case SpvBuiltInBaryCoordSmoothSampleAMD:
    case SpvBuiltInBaryCoordPullModelAMD:
    case SpvBuiltInFragStencilRefEXT:
    case SpvBuiltInViewportMaskNV:
    case SpvBuiltInSecondaryPositionNV:
    case SpvBuiltInSecondaryViewportMaskNV:
    case SpvBuiltInPositionPerViewNV:
    case SpvBuiltInViewportMaskPerViewNV:
    case SpvBuiltInFullyCoveredEXT:
    case SpvBuiltInMax: {
      // No validation rules (for the moment).
      break;
    }
  }
  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::ValidateBuiltInsAtDefinition() {
  for (const auto& kv : _.id_decorations()) {
    const uint32_t id = kv.first;
    const auto& decorations = kv.second;
    if (decorations.empty()) {
      continue;
    }

    const Instruction* inst = _.FindDef(id);
    assert(inst);

    for (const auto& decoration : kv.second) {
      if (decoration.dec_type() != SpvDecorationBuiltIn) {
        continue;
      }

      if (spv_result_t error =
              ValidateSingleBuiltInAtDefinition(decoration, *inst)) {
        return error;
      }
    }
  }

  return SPV_SUCCESS;
}

spv_result_t BuiltInsValidator::Run() {
  // First pass: validate all built-ins at definition and seed
  // id_to_at_reference_checks_ with built-ins.
  if (auto error = ValidateBuiltInsAtDefinition()) {
    return error;
  }

  if (id_to_at_reference_checks_.empty()) {
    // No validation tasks were seeded. Nothing else to do.
    return SPV_SUCCESS;
  }

  ComputeFunctionToEntryPointMapping();

  // Second pass: validate every id reference in the module using
  // rules in id_to_at_reference_checks_.
  for (const Instruction& inst : _.ordered_instructions()) {
    Update(inst);

    std::set<uint32_t> already_checked;

    for (const auto& operand : inst.operands()) {
      if (!spvIsIdType(operand.type)) {
        // Not id.
        continue;
      }

      const uint32_t id = inst.word(operand.offset);
      if (id == inst.id()) {
        // No need to check result id.
        continue;
      }

      if (!already_checked.insert(id).second) {
        // The instruction has already referenced this id.
        continue;
      }

      // Instruction references the id. Run all checks associated with the id on
      // the instruction. id_to_at_reference_checks_ can be modified in the
      // process, iterators are safe because it's a tree-based map.
      const auto it = id_to_at_reference_checks_.find(id);
      if (it != id_to_at_reference_checks_.end()) {
        for (const auto& check : it->second) {
          if (spv_result_t error = check(inst)) {
            return error;
          }
        }
      }
    }
  }

  return SPV_SUCCESS;
}

}  // anonymous namespace

// Validates correctness of built-in variables.
spv_result_t ValidateBuiltIns(const ValidationState_t& _) {
  if (!spvIsVulkanEnv(_.context()->target_env)) {
    // Early return. All currently implemented rules are based on Vulkan spec.
    //
    // TODO: If you are adding validation rules for environments other than
    // Vulkan (or general rules which are not environment independent), then you
    // need to modify or remove this condition. Consider also adding early
    // returns into BuiltIn-specific rules, so that the system doesn't spawn new
    // rules which don't do anything.
    return SPV_SUCCESS;
  }

  BuiltInsValidator validator(_);
  return validator.Run();
}

}  // namespace libspirv

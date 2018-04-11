// Copyright (c) 2017 Google Inc.
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

#include "validate.h"

#include <algorithm>
#include <string>

#include "diagnostic.h"
#include "opcode.h"
#include "spirv_target_env.h"
#include "val/validation_state.h"

using libspirv::Decoration;
using libspirv::DiagnosticStream;
using libspirv::Instruction;
using libspirv::ValidationState_t;

namespace {

// Returns whether the given variable has a BuiltIn decoration.
bool isBuiltInVar(uint32_t var_id, ValidationState_t& vstate) {
  const auto& decorations = vstate.id_decorations(var_id);
  return std::any_of(
      decorations.begin(), decorations.end(),
      [](const Decoration& d) { return SpvDecorationBuiltIn == d.dec_type(); });
}

// Returns whether the given structure type has any members with BuiltIn
// decoration.
bool isBuiltInStruct(uint32_t struct_id, ValidationState_t& vstate) {
  const auto& decorations = vstate.id_decorations(struct_id);
  return std::any_of(
      decorations.begin(), decorations.end(), [](const Decoration& d) {
        return SpvDecorationBuiltIn == d.dec_type() &&
               Decoration::kInvalidMember != d.struct_member_index();
      });
}

// Returns true if the given ID has the Import LinkageAttributes decoration.
bool hasImportLinkageAttribute(uint32_t id, ValidationState_t& vstate) {
  const auto& decorations = vstate.id_decorations(id);
  return std::any_of(decorations.begin(), decorations.end(),
                     [](const Decoration& d) {
                       return SpvDecorationLinkageAttributes == d.dec_type() &&
                              d.params().size() >= 2u &&
                              d.params().back() == SpvLinkageTypeImport;
                     });
}

spv_result_t CheckLinkageAttrOfFunctions(ValidationState_t& vstate) {
  for (const auto& function : vstate.functions()) {
    if (function.block_count() == 0u) {
      // A function declaration (an OpFunction with no basic blocks), must have
      // a Linkage Attributes Decoration with the Import Linkage Type.
      if (!hasImportLinkageAttribute(function.id(), vstate)) {
        return vstate.diag(SPV_ERROR_INVALID_BINARY)
               << "Function declaration (id " << function.id()
               << ") must have a LinkageAttributes decoration with the Import "
                  "Linkage type.";
      }
    } else {
      if (hasImportLinkageAttribute(function.id(), vstate)) {
        return vstate.diag(SPV_ERROR_INVALID_BINARY)
               << "Function definition (id " << function.id()
               << ") may not be decorated with Import Linkage type.";
      }
    }
  }
  return SPV_SUCCESS;
}

// Checks whether an imported variable is initialized by this module.
spv_result_t CheckImportedVariableInitialization(ValidationState_t& vstate) {
  // According the SPIR-V Spec 2.16.1, it is illegal to initialize an imported
  // variable. This means that a module-scope OpVariable with initialization
  // value cannot be marked with the Import Linkage Type (import type id = 1).
  for (auto global_var_id : vstate.global_vars()) {
    // Initializer <id> is an optional argument for OpVariable. If initializer
    // <id> is present, the instruction will have 5 words.
    auto variable_instr = vstate.FindDef(global_var_id);
    if (variable_instr->words().size() == 5u &&
        hasImportLinkageAttribute(global_var_id, vstate)) {
      return vstate.diag(SPV_ERROR_INVALID_ID)
             << "A module-scope OpVariable with initialization value "
                "cannot be marked with the Import Linkage Type.";
    }
  }
  return SPV_SUCCESS;
}

// Checks whether a builtin variable is valid.
spv_result_t CheckBuiltInVariable(uint32_t var_id, ValidationState_t& vstate) {
  const auto& decorations = vstate.id_decorations(var_id);
  for (const auto& d : decorations) {
    if (spvIsVulkanEnv(vstate.context()->target_env)) {
      if (d.dec_type() == SpvDecorationLocation ||
          d.dec_type() == SpvDecorationComponent) {
        return vstate.diag(SPV_ERROR_INVALID_ID)
               << "A BuiltIn variable (id " << var_id
               << ") cannot have any Location or Component decorations";
      }
    }
  }
  return SPV_SUCCESS;
}

// Checks whether proper decorations have been appied to the entry points.
spv_result_t CheckDecorationsOfEntryPoints(ValidationState_t& vstate) {
  for (uint32_t entry_point : vstate.entry_points()) {
    const auto& interfaces = vstate.entry_point_interfaces(entry_point);
    int num_builtin_inputs = 0;
    int num_builtin_outputs = 0;
    for (auto interface : interfaces) {
      Instruction* var_instr = vstate.FindDef(interface);
      if (SpvOpVariable != var_instr->opcode()) {
        return vstate.diag(SPV_ERROR_INVALID_ID)
               << "Interfaces passed to OpEntryPoint must be of type "
                  "OpTypeVariable. Found Op"
               << spvOpcodeString(static_cast<SpvOp>(var_instr->opcode()))
               << ".";
      }
      const uint32_t ptr_id = var_instr->word(1);
      Instruction* ptr_instr = vstate.FindDef(ptr_id);
      // It is guaranteed (by validator ID checks) that ptr_instr is
      // OpTypePointer. Word 3 of this instruction is the type being pointed to.
      const uint32_t type_id = ptr_instr->word(3);
      Instruction* type_instr = vstate.FindDef(type_id);
      const auto storage_class =
          static_cast<SpvStorageClass>(var_instr->word(3));
      if (storage_class != SpvStorageClassInput &&
          storage_class != SpvStorageClassOutput) {
        return vstate.diag(SPV_ERROR_INVALID_ID)
               << "OpEntryPoint interfaces must be OpVariables with "
                  "Storage Class of Input(1) or Output(3). Found Storage Class "
               << storage_class << " for Entry Point id " << entry_point << ".";
      }
      if (type_instr && SpvOpTypeStruct == type_instr->opcode() &&
          isBuiltInStruct(type_id, vstate)) {
        if (storage_class == SpvStorageClassInput) ++num_builtin_inputs;
        if (storage_class == SpvStorageClassOutput) ++num_builtin_outputs;
        if (num_builtin_inputs > 1 || num_builtin_outputs > 1) break;
        if (auto error = CheckBuiltInVariable(interface, vstate)) return error;
      } else if (isBuiltInVar(interface, vstate)) {
        if (auto error = CheckBuiltInVariable(interface, vstate)) return error;
      }
    }
    if (num_builtin_inputs > 1 || num_builtin_outputs > 1) {
      return vstate.diag(SPV_ERROR_INVALID_BINARY)
             << "There must be at most one object per Storage Class that can "
                "contain a structure type containing members decorated with "
                "BuiltIn, consumed per entry-point. Entry Point id "
             << entry_point << " does not meet this requirement.";
    }
    // The LinkageAttributes Decoration cannot be applied to functions targeted
    // by an OpEntryPoint instruction
    for (auto& decoration : vstate.id_decorations(entry_point)) {
      if (SpvDecorationLinkageAttributes == decoration.dec_type()) {
        const char* linkage_name =
            reinterpret_cast<const char*>(&decoration.params()[0]);
        return vstate.diag(SPV_ERROR_INVALID_BINARY)
               << "The LinkageAttributes Decoration (Linkage name: "
               << linkage_name << ") cannot be applied to function id "
               << entry_point
               << " because it is targeted by an OpEntryPoint instruction.";
      }
    }
  }
  return SPV_SUCCESS;
}

}  // anonymous namespace

namespace libspirv {

// Validates that decorations have been applied properly.
spv_result_t ValidateDecorations(ValidationState_t& vstate) {
  if (auto error = CheckImportedVariableInitialization(vstate)) return error;
  if (auto error = CheckDecorationsOfEntryPoints(vstate)) return error;
  if (auto error = CheckLinkageAttrOfFunctions(vstate)) return error;
  return SPV_SUCCESS;
}

}  // namespace libspirv

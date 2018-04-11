// Copyright (c) 2015-2016 The Khronos Group Inc.
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

// Performs validation on instructions that appear inside of a SPIR-V block.

#include "validate.h"

#include <algorithm>
#include <cassert>

#include <sstream>
#include <string>

#include "binary.h"
#include "diagnostic.h"
#include "enum_set.h"
#include "enum_string_mapping.h"
#include "extensions.h"
#include "opcode.h"
#include "operand.h"
#include "spirv_constant.h"
#include "spirv_definition.h"
#include "spirv_target_env.h"
#include "spirv_validator_options.h"
#include "util/string_utils.h"
#include "val/function.h"
#include "val/validation_state.h"

using libspirv::AssemblyGrammar;
using libspirv::CapabilitySet;
using libspirv::DiagnosticStream;
using libspirv::ExtensionSet;
using libspirv::ValidationState_t;

namespace {

std::string ToString(const CapabilitySet& capabilities,
                     const AssemblyGrammar& grammar) {
  std::stringstream ss;
  capabilities.ForEach([&grammar, &ss](SpvCapability cap) {
    spv_operand_desc desc;
    if (SPV_SUCCESS ==
        grammar.lookupOperand(SPV_OPERAND_TYPE_CAPABILITY, cap, &desc))
      ss << desc->name << " ";
    else
      ss << cap << " ";
  });
  return ss.str();
}

// Reports a missing-capability error to _'s diagnostic stream and returns
// SPV_ERROR_INVALID_CAPABILITY.
spv_result_t CapabilityError(ValidationState_t& _, int which_operand,
                             SpvOp opcode,
                             const std::string& required_capabilities) {
  return _.diag(SPV_ERROR_INVALID_CAPABILITY)
         << "Operand " << which_operand << " of " << spvOpcodeString(opcode)
         << " requires one of these capabilities: " << required_capabilities;
}

// Returns capabilities that enable an opcode.  An empty result is interpreted
// as no prohibition of use of the opcode.  If the result is non-empty, then
// the opcode may only be used if at least one of the capabilities is specified
// by the module.
CapabilitySet EnablingCapabilitiesForOp(const ValidationState_t& state,
                                        SpvOp opcode) {
  // Exceptions for SPV_AMD_shader_ballot
  switch (opcode) {
    // Normally these would require Group capability
    case SpvOpGroupIAddNonUniformAMD:
    case SpvOpGroupFAddNonUniformAMD:
    case SpvOpGroupFMinNonUniformAMD:
    case SpvOpGroupUMinNonUniformAMD:
    case SpvOpGroupSMinNonUniformAMD:
    case SpvOpGroupFMaxNonUniformAMD:
    case SpvOpGroupUMaxNonUniformAMD:
    case SpvOpGroupSMaxNonUniformAMD:
      if (state.HasExtension(libspirv::kSPV_AMD_shader_ballot))
        return CapabilitySet();
      break;
    default:
      break;
  }
  // Look it up in the grammar
  spv_opcode_desc opcode_desc = {};
  if (SPV_SUCCESS == state.grammar().lookupOpcode(opcode, &opcode_desc)) {
    return state.grammar().filterCapsAgainstTargetEnv(
        opcode_desc->capabilities, opcode_desc->numCapabilities);
  }
  return CapabilitySet();
}

// Returns an operand's required capabilities.
CapabilitySet RequiredCapabilities(const ValidationState_t& state,
                                   spv_operand_type_t type, uint32_t operand) {
  // Mere mention of PointSize, ClipDistance, or CullDistance in a Builtin
  // decoration does not require the associated capability.  The use of such
  // a variable value should trigger the capability requirement, but that's
  // not implemented yet.  This rule is independent of target environment.
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/365
  if (type == SPV_OPERAND_TYPE_BUILT_IN) {
    switch (operand) {
      case SpvBuiltInPointSize:
      case SpvBuiltInClipDistance:
      case SpvBuiltInCullDistance:
        return CapabilitySet();
      default:
        break;
    }
  } else if (type == SPV_OPERAND_TYPE_FP_ROUNDING_MODE) {
    // Allow all FP rounding modes if requested
    if (state.features().free_fp_rounding_mode) {
      return CapabilitySet();
    }
  }

  spv_operand_desc operand_desc;
  const auto ret = state.grammar().lookupOperand(type, operand, &operand_desc);
  if (ret == SPV_SUCCESS) {
    // Allow FPRoundingMode decoration if requested.
    if (type == SPV_OPERAND_TYPE_DECORATION &&
        operand_desc->value == SpvDecorationFPRoundingMode) {
      if (state.features().free_fp_rounding_mode) return CapabilitySet();

      // Vulkan API requires more capabilities on rounding mode.
      if (spvIsVulkanEnv(state.context()->target_env)) {
        CapabilitySet cap_set;
        cap_set.Add(SpvCapabilityStorageUniformBufferBlock16);
        cap_set.Add(SpvCapabilityStorageUniform16);
        cap_set.Add(SpvCapabilityStoragePushConstant16);
        cap_set.Add(SpvCapabilityStorageInputOutput16);
        return cap_set;
      }
    }
    // Allow certain group operations if requested.
    if (state.features().group_ops_reduce_and_scans &&
        type == SPV_OPERAND_TYPE_GROUP_OPERATION &&
        (operand <= uint32_t(SpvGroupOperationExclusiveScan))) {
      return CapabilitySet();
    }

    return state.grammar().filterCapsAgainstTargetEnv(
        operand_desc->capabilities, operand_desc->numCapabilities);
  }

  return CapabilitySet();
}

// Returns operand's required extensions.
ExtensionSet RequiredExtensions(const ValidationState_t& state,
                                spv_operand_type_t type, uint32_t operand) {
  spv_operand_desc operand_desc;
  if (state.grammar().lookupOperand(type, operand, &operand_desc) ==
      SPV_SUCCESS) {
    assert(operand_desc);
    // If this operand is incorporated into core SPIR-V before or in the current
    // target environment, we don't require extensions anymore.
    if (spvVersionForTargetEnv(state.grammar().target_env()) >=
        operand_desc->minVersion)
      return {};
    return {operand_desc->numExtensions, operand_desc->extensions};
  }

  return {};
}

}  // namespace

namespace libspirv {

spv_result_t CapabilityCheck(ValidationState_t& _,
                             const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  CapabilitySet opcode_caps = EnablingCapabilitiesForOp(_, opcode);
  if (!_.HasAnyOfCapabilities(opcode_caps)) {
    return _.diag(SPV_ERROR_INVALID_CAPABILITY)
           << "Opcode " << spvOpcodeString(opcode)
           << " requires one of these capabilities: "
           << ToString(opcode_caps, _.grammar());
  }
  for (int i = 0; i < inst->num_operands; ++i) {
    const auto& operand = inst->operands[i];
    const auto word = inst->words[operand.offset];
    if (spvOperandIsConcreteMask(operand.type)) {
      // Check for required capabilities for each bit position of the mask.
      for (uint32_t mask_bit = 0x80000000; mask_bit; mask_bit >>= 1) {
        if (word & mask_bit) {
          const auto caps = RequiredCapabilities(_, operand.type, mask_bit);
          if (!_.HasAnyOfCapabilities(caps)) {
            return CapabilityError(_, i + 1, opcode,
                                   ToString(caps, _.grammar()));
          }
        }
      }
    } else if (spvIsIdType(operand.type)) {
      // TODO(dneto): Check the value referenced by this Id, if we can compute
      // it.  For now, just punt, to fix issue 248:
      // https://github.com/KhronosGroup/SPIRV-Tools/issues/248
    } else {
      // Check the operand word as a whole.
      const auto caps = RequiredCapabilities(_, operand.type, word);
      if (!_.HasAnyOfCapabilities(caps)) {
        return CapabilityError(_, i + 1, opcode, ToString(caps, _.grammar()));
      }
    }
  }
  return SPV_SUCCESS;
}

// Checks that all extensions required by the given instruction's operands were
// declared in the module.
spv_result_t ExtensionCheck(ValidationState_t& _,
                            const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  for (size_t operand_index = 0; operand_index < inst->num_operands;
       ++operand_index) {
    const auto& operand = inst->operands[operand_index];
    const uint32_t word = inst->words[operand.offset];
    const ExtensionSet required_extensions =
        RequiredExtensions(_, operand.type, word);
    if (!_.HasAnyOfExtensions(required_extensions)) {
      return _.diag(SPV_ERROR_MISSING_EXTENSION)
             << spvutils::CardinalToOrdinal(operand_index + 1) << " operand of "
             << spvOpcodeString(opcode) << ": operand " << word
             << " requires one of these extensions: "
             << ExtensionSetToString(required_extensions);
    }
  }
  return SPV_SUCCESS;
}

// Checks that the instruction can be used in this target environment.
spv_result_t VersionCheck(ValidationState_t& _,
                          const spv_parsed_instruction_t* inst) {
  const auto opcode = static_cast<SpvOp>(inst->opcode);
  spv_opcode_desc inst_desc;
  const bool r = _.grammar().lookupOpcode(opcode, &inst_desc);
  assert(r == SPV_SUCCESS);
  (void)r;

  const auto min_version = inst_desc->minVersion;

  ExtensionSet exts(inst_desc->numExtensions, inst_desc->extensions);
  if (exts.IsEmpty()) {
    // If no extensions can enable this instruction, then emit error messages
    // only concerning core SPIR-V versions if errors happen.
    if (min_version == ~0u) {
      return _.diag(SPV_ERROR_WRONG_VERSION)
             << spvOpcodeString(opcode) << " is reserved for future use.";
    }

    if (spvVersionForTargetEnv(_.grammar().target_env()) < min_version) {
      return _.diag(SPV_ERROR_WRONG_VERSION)
             << spvOpcodeString(opcode) << " requires "
             << spvTargetEnvDescription(
                    static_cast<spv_target_env>(min_version))
             << " at minimum.";
    }
  }
  // Otherwise, we only error out when no enabling extensions are registered.
  else if (!_.HasAnyOfExtensions(exts)) {
    if (min_version == ~0u) {
      return _.diag(SPV_ERROR_MISSING_EXTENSION)
             << spvOpcodeString(opcode)
             << " requires one of the following extensions: "
             << ExtensionSetToString(exts);
    }

    if (static_cast<uint32_t>(_.grammar().target_env()) < min_version) {
      return _.diag(SPV_ERROR_WRONG_VERSION)
             << spvOpcodeString(opcode) << " requires "
             << spvTargetEnvDescription(
                    static_cast<spv_target_env>(min_version))
             << " at minimum or one of the following extensions: "
             << ExtensionSetToString(exts);
    }
  }

  return SPV_SUCCESS;
}

// Checks that the Resuld <id> is within the valid bound.
spv_result_t LimitCheckIdBound(ValidationState_t& _,
                               const spv_parsed_instruction_t* inst) {
  if (inst->result_id >= _.getIdBound()) {
    return _.diag(SPV_ERROR_INVALID_BINARY)
           << "Result <id> '" << inst->result_id
           << "' must be less than the ID bound '" << _.getIdBound() << "'.";
  }
  return SPV_SUCCESS;
}

// Checks that the number of OpTypeStruct members is within the limit.
spv_result_t LimitCheckStruct(ValidationState_t& _,
                              const spv_parsed_instruction_t* inst) {
  if (SpvOpTypeStruct != inst->opcode) {
    return SPV_SUCCESS;
  }

  // Number of members is the number of operands of the instruction minus 1.
  // One operand is the result ID.
  const uint16_t limit =
      static_cast<uint16_t>(_.options()->universal_limits_.max_struct_members);
  if (inst->num_operands - 1 > limit) {
    return _.diag(SPV_ERROR_INVALID_BINARY)
           << "Number of OpTypeStruct members (" << inst->num_operands - 1
           << ") has exceeded the limit (" << limit << ").";
  }

  // Section 2.17 of SPIRV Spec specifies that the "Structure Nesting Depth"
  // must be less than or equal to 255.
  // This is interpreted as structures including other structures as members.
  // The code does not follow pointers or look into arrays to see if we reach a
  // structure downstream.
  // The nesting depth of a struct is 1+(largest depth of any member).
  // Scalars are at depth 0.
  uint32_t max_member_depth = 0;
  // Struct members start at word 2 of OpTypeStruct instruction.
  for (size_t word_i = 2; word_i < inst->num_words; ++word_i) {
    auto member = inst->words[word_i];
    auto memberTypeInstr = _.FindDef(member);
    if (memberTypeInstr && SpvOpTypeStruct == memberTypeInstr->opcode()) {
      max_member_depth = std::max(
          max_member_depth, _.struct_nesting_depth(memberTypeInstr->id()));
    }
  }

  const uint32_t depth_limit = _.options()->universal_limits_.max_struct_depth;
  const uint32_t cur_depth = 1 + max_member_depth;
  _.set_struct_nesting_depth(inst->result_id, cur_depth);
  if (cur_depth > depth_limit) {
    return _.diag(SPV_ERROR_INVALID_BINARY)
           << "Structure Nesting Depth may not be larger than " << depth_limit
           << ". Found " << cur_depth << ".";
  }
  return SPV_SUCCESS;
}

// Checks that the number of (literal, label) pairs in OpSwitch is within the
// limit.
spv_result_t LimitCheckSwitch(ValidationState_t& _,
                              const spv_parsed_instruction_t* inst) {
  if (SpvOpSwitch == inst->opcode) {
    // The instruction syntax is as follows:
    // OpSwitch <selector ID> <Default ID> literal label literal label ...
    // literal,label pairs come after the first 2 operands.
    // It is guaranteed at this point that num_operands is an even numner.
    unsigned int num_pairs = (inst->num_operands - 2) / 2;
    const unsigned int num_pairs_limit =
        _.options()->universal_limits_.max_switch_branches;
    if (num_pairs > num_pairs_limit) {
      return _.diag(SPV_ERROR_INVALID_BINARY)
             << "Number of (literal, label) pairs in OpSwitch (" << num_pairs
             << ") exceeds the limit (" << num_pairs_limit << ").";
    }
  }
  return SPV_SUCCESS;
}

// Ensure the number of variables of the given class does not exceed the limit.
spv_result_t LimitCheckNumVars(ValidationState_t& _, const uint32_t var_id,
                               const SpvStorageClass storage_class) {
  if (SpvStorageClassFunction == storage_class) {
    _.registerLocalVariable(var_id);
    const uint32_t num_local_vars_limit =
        _.options()->universal_limits_.max_local_variables;
    if (_.num_local_vars() > num_local_vars_limit) {
      return _.diag(SPV_ERROR_INVALID_BINARY)
             << "Number of local variables ('Function' Storage Class) "
                "exceeded the valid limit ("
             << num_local_vars_limit << ").";
    }
  } else {
    _.registerGlobalVariable(var_id);
    const uint32_t num_global_vars_limit =
        _.options()->universal_limits_.max_global_variables;
    if (_.num_global_vars() > num_global_vars_limit) {
      return _.diag(SPV_ERROR_INVALID_BINARY)
             << "Number of Global Variables (Storage Class other than "
                "'Function') exceeded the valid limit ("
             << num_global_vars_limit << ").";
    }
  }
  return SPV_SUCCESS;
}

// Registers necessary decoration(s) for the appropriate IDs based on the
// instruction.
spv_result_t RegisterDecorations(ValidationState_t& _,
                                 const spv_parsed_instruction_t* inst) {
  switch (inst->opcode) {
    case SpvOpDecorate: {
      const uint32_t target_id = inst->words[1];
      const SpvDecoration dec_type = static_cast<SpvDecoration>(inst->words[2]);
      std::vector<uint32_t> dec_params;
      if (inst->num_words > 3) {
        dec_params.insert(dec_params.end(), inst->words + 3,
                          inst->words + inst->num_words);
      }
      _.RegisterDecorationForId(target_id, Decoration(dec_type, dec_params));
      break;
    }
    case SpvOpMemberDecorate: {
      const uint32_t struct_id = inst->words[1];
      const uint32_t index = inst->words[2];
      const SpvDecoration dec_type = static_cast<SpvDecoration>(inst->words[3]);
      std::vector<uint32_t> dec_params;
      if (inst->num_words > 4) {
        dec_params.insert(dec_params.end(), inst->words + 4,
                          inst->words + inst->num_words);
      }
      _.RegisterDecorationForId(struct_id,
                                Decoration(dec_type, dec_params, index));
      break;
    }
    case SpvOpDecorationGroup: {
      // We don't need to do anything right now. Assigning decorations to groups
      // will be taken care of via OpGroupDecorate.
      break;
    }
    case SpvOpGroupDecorate: {
      // Word 1 is the group <id>. All subsequent words are target <id>s that
      // are going to be decorated with the decorations.
      const uint32_t decoration_group_id = inst->words[1];
      std::vector<Decoration>& group_decorations =
          _.id_decorations(decoration_group_id);
      for (int i = 2; i < inst->num_words; ++i) {
        const uint32_t target_id = inst->words[i];
        _.RegisterDecorationsForId(target_id, group_decorations.begin(),
                                   group_decorations.end());
      }
      break;
    }
    case SpvOpGroupMemberDecorate: {
      // Word 1 is the Decoration Group <id> followed by (struct<id>,literal)
      // pairs. All decorations of the group should be applied to all the struct
      // members that are specified in the instructions.
      const uint32_t decoration_group_id = inst->words[1];
      std::vector<Decoration>& group_decorations =
          _.id_decorations(decoration_group_id);
      // Grammar checks ensures that the number of arguments to this instruction
      // is an odd number: 1 decoration group + (id,literal) pairs.
      for (int i = 2; i + 1 < inst->num_words; i = i + 2) {
        const uint32_t struct_id = inst->words[i];
        const uint32_t index = inst->words[i + 1];
        // ID validation phase ensures this is in fact a struct instruction and
        // that the index is not out of bound.
        _.RegisterDecorationsForStructMember(struct_id, index,
                                             group_decorations.begin(),
                                             group_decorations.end());
      }
      break;
    }
    default:
      break;
  }
  return SPV_SUCCESS;
}

// Parses OpExtension instruction and logs warnings if unsuccessful.
void CheckIfKnownExtension(ValidationState_t& _,
                           const spv_parsed_instruction_t* inst) {
  const std::string extension_str = GetExtensionString(inst);
  Extension extension;
  if (!GetExtensionFromString(extension_str.c_str(), &extension)) {
    _.diag(SPV_SUCCESS) << "Found unrecognized extension " << extension_str;
    return;
  }
}

spv_result_t InstructionPass(ValidationState_t& _,
                             const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  if (opcode == SpvOpExtension) {
    CheckIfKnownExtension(_, inst);
  } else if (opcode == SpvOpCapability) {
    _.RegisterCapability(
        static_cast<SpvCapability>(inst->words[inst->operands[0].offset]));
  } else if (opcode == SpvOpMemoryModel) {
    _.set_addressing_model(
        static_cast<SpvAddressingModel>(inst->words[inst->operands[0].offset]));
    _.set_memory_model(
        static_cast<SpvMemoryModel>(inst->words[inst->operands[1].offset]));
  } else if (opcode == SpvOpExecutionMode) {
    const uint32_t entry_point = inst->words[1];
    _.RegisterExecutionModeForEntryPoint(entry_point,
                                         SpvExecutionMode(inst->words[2]));
  } else if (opcode == SpvOpVariable) {
    const auto storage_class =
        static_cast<SpvStorageClass>(inst->words[inst->operands[2].offset]);
    if (auto error = LimitCheckNumVars(_, inst->result_id, storage_class)) {
      return error;
    }
    if (storage_class == SpvStorageClassGeneric)
      return _.diag(SPV_ERROR_INVALID_BINARY)
             << "OpVariable storage class cannot be Generic";
    if (_.current_layout_section() == kLayoutFunctionDefinitions) {
      if (storage_class != SpvStorageClassFunction) {
        return _.diag(SPV_ERROR_INVALID_LAYOUT)
               << "Variables must have a function[7] storage class inside"
                  " of a function";
      }
      if (_.current_function().IsFirstBlock(
              _.current_function().current_block()->id()) == false) {
        return _.diag(SPV_ERROR_INVALID_CFG) << "Variables can only be defined "
                                                "in the first block of a "
                                                "function";
      }
    } else {
      if (storage_class == SpvStorageClassFunction) {
        return _.diag(SPV_ERROR_INVALID_LAYOUT)
               << "Variables can not have a function[7] storage class "
                  "outside of a function";
      }
    }
  }

  // SPIR-V Spec 2.16.3: Validation Rules for Kernel Capabilities: The
  // Signedness in OpTypeInt must always be 0.
  if (SpvOpTypeInt == inst->opcode && _.HasCapability(SpvCapabilityKernel) &&
      inst->words[inst->operands[2].offset] != 0u) {
    return _.diag(SPV_ERROR_INVALID_BINARY) << "The Signedness in OpTypeInt "
                                               "must always be 0 when Kernel "
                                               "capability is used.";
  }

  // In order to validate decoration rules, we need to know all the decorations
  // that are applied to any given <id>.
  RegisterDecorations(_, inst);

  if (auto error = ExtensionCheck(_, inst)) return error;
  if (auto error = CapabilityCheck(_, inst)) return error;
  if (auto error = LimitCheckIdBound(_, inst)) return error;
  if (auto error = LimitCheckStruct(_, inst)) return error;
  if (auto error = LimitCheckSwitch(_, inst)) return error;
  if (auto error = VersionCheck(_, inst)) return error;

  // All instruction checks have passed.
  return SPV_SUCCESS;
}
}  // namespace libspirv

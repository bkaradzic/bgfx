// Copyright (c) 2023 Google Inc.
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

#include "source/opt/trim_capabilities_pass.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "source/enum_set.h"
#include "source/enum_string_mapping.h"
#include "source/opt/ir_context.h"
#include "source/spirv_target_env.h"
#include "source/util/string_utils.h"

namespace spvtools {
namespace opt {

namespace {
constexpr uint32_t kVariableStorageClassIndex = 0;
constexpr uint32_t kTypeArrayTypeIndex = 0;
constexpr uint32_t kOpTypeScalarBitWidthIndex = 0;
constexpr uint32_t kTypePointerTypeIdInIdx = 1;
}  // namespace

// ============== Begin opcode handler implementations. =======================
//
// Adding support for a new capability should only require adding a new handler,
// and updating the
// kSupportedCapabilities/kUntouchableCapabilities/kFordiddenCapabilities lists.
//
// Handler names follow the following convention:
//  Handler_<Opcode>_<Capability>()

static std::optional<spv::Capability> Handler_OpVariable_StorageInputOutput16(
    const Instruction* instruction) {
  assert(instruction->opcode() == spv::Op::OpVariable &&
         "This handler only support OpVariable opcodes.");

  // This capability is only required if the variable as an Input/Output storage
  // class.
  spv::StorageClass storage_class = spv::StorageClass(
      instruction->GetSingleWordInOperand(kVariableStorageClassIndex));
  if (storage_class != spv::StorageClass::Input &&
      storage_class != spv::StorageClass::Output) {
    return std::nullopt;
  }

  // This capability is only required if the type involves a 16-bit component.
  // Quick check: are 16-bit types allowed?
  const CapabilitySet& capabilities =
      instruction->context()->get_feature_mgr()->GetCapabilities();
  if (!capabilities.contains(spv::Capability::Float16) &&
      !capabilities.contains(spv::Capability::Int16)) {
    return std::nullopt;
  }

  // We need to walk the type definition.
  std::queue<uint32_t> instructions_to_visit;
  instructions_to_visit.push(instruction->type_id());
  const auto* def_use_mgr = instruction->context()->get_def_use_mgr();
  while (!instructions_to_visit.empty()) {
    const Instruction* item =
        def_use_mgr->GetDef(instructions_to_visit.front());
    instructions_to_visit.pop();

    if (item->opcode() == spv::Op::OpTypePointer) {
      instructions_to_visit.push(
          item->GetSingleWordInOperand(kTypePointerTypeIdInIdx));
      continue;
    }

    if (item->opcode() == spv::Op::OpTypeMatrix ||
        item->opcode() == spv::Op::OpTypeVector ||
        item->opcode() == spv::Op::OpTypeArray ||
        item->opcode() == spv::Op::OpTypeRuntimeArray) {
      instructions_to_visit.push(
          item->GetSingleWordInOperand(kTypeArrayTypeIndex));
      continue;
    }

    if (item->opcode() == spv::Op::OpTypeStruct) {
      item->ForEachInOperand([&instructions_to_visit](const uint32_t* op_id) {
        instructions_to_visit.push(*op_id);
      });
      continue;
    }

    if (item->opcode() != spv::Op::OpTypeInt &&
        item->opcode() != spv::Op::OpTypeFloat) {
      continue;
    }

    if (item->GetSingleWordInOperand(kOpTypeScalarBitWidthIndex) == 16) {
      return spv::Capability::StorageInputOutput16;
    }
  }

  return std::nullopt;
}

// Opcode of interest to determine capabilities requirements.
constexpr std::array<std::pair<spv::Op, OpcodeHandler>, 1> kOpcodeHandlers{{
    {spv::Op::OpVariable, Handler_OpVariable_StorageInputOutput16},
}};

// ==============  End opcode handler implementations.  =======================

namespace {
ExtensionSet getExtensionsRelatedTo(const CapabilitySet& capabilities,
                                    const AssemblyGrammar& grammar) {
  ExtensionSet output;
  const spv_operand_desc_t* desc = nullptr;
  for (auto capability : capabilities) {
    if (SPV_SUCCESS != grammar.lookupOperand(SPV_OPERAND_TYPE_CAPABILITY,
                                             static_cast<uint32_t>(capability),
                                             &desc)) {
      continue;
    }

    for (uint32_t i = 0; i < desc->numExtensions; ++i) {
      output.insert(desc->extensions[i]);
    }
  }

  return output;
}
}  // namespace

TrimCapabilitiesPass::TrimCapabilitiesPass()
    : supportedCapabilities_(
          TrimCapabilitiesPass::kSupportedCapabilities.cbegin(),
          TrimCapabilitiesPass::kSupportedCapabilities.cend()),
      forbiddenCapabilities_(
          TrimCapabilitiesPass::kForbiddenCapabilities.cbegin(),
          TrimCapabilitiesPass::kForbiddenCapabilities.cend()),
      untouchableCapabilities_(
          TrimCapabilitiesPass::kUntouchableCapabilities.cbegin(),
          TrimCapabilitiesPass::kUntouchableCapabilities.cend()),
      opcodeHandlers_(kOpcodeHandlers.cbegin(), kOpcodeHandlers.cend()) {}

void TrimCapabilitiesPass::addInstructionRequirements(
    Instruction* instruction, CapabilitySet* capabilities,
    ExtensionSet* extensions) const {
  // Ignoring OpCapability instructions.
  if (instruction->opcode() == spv::Op::OpCapability) {
    return;
  }

  // First case: the opcode is itself gated by a capability.
  {
    const spv_opcode_desc_t* desc = {};
    auto result =
        context()->grammar().lookupOpcode(instruction->opcode(), &desc);
    if (result == SPV_SUCCESS) {
      addSupportedCapabilitiesToSet(desc->numCapabilities, desc->capabilities,
                                    capabilities);
      if (desc->minVersion <=
          spvVersionForTargetEnv(context()->GetTargetEnv())) {
        extensions->insert(desc->extensions,
                           desc->extensions + desc->numExtensions);
      }
    }
  }

  // Second case: one of the opcode operand is gated by a capability.
  const uint32_t operandCount = instruction->NumOperands();
  for (uint32_t i = 0; i < operandCount; i++) {
    const auto& operand = instruction->GetOperand(i);
    // No supported capability relies on a 2+-word operand.
    if (operand.words.size() != 1) {
      continue;
    }

    // No supported capability relies on a literal string operand.
    if (operand.type == SPV_OPERAND_TYPE_LITERAL_STRING) {
      continue;
    }

    const spv_operand_desc_t* desc = {};
    auto result = context()->grammar().lookupOperand(operand.type,
                                                     operand.words[0], &desc);
    if (result != SPV_SUCCESS) {
      continue;
    }

    addSupportedCapabilitiesToSet(desc->numCapabilities, desc->capabilities,
                                  capabilities);
    if (desc->minVersion <= spvVersionForTargetEnv(context()->GetTargetEnv())) {
      extensions->insert(desc->extensions,
                         desc->extensions + desc->numExtensions);
    }
  }

  // Last case: some complex logic needs to be run to determine capabilities.
  auto[begin, end] = opcodeHandlers_.equal_range(instruction->opcode());
  for (auto it = begin; it != end; it++) {
    const OpcodeHandler handler = it->second;
    auto result = handler(instruction);
    if (result.has_value()) {
      capabilities->insert(*result);
    }
  }
}

std::pair<CapabilitySet, ExtensionSet>
TrimCapabilitiesPass::DetermineRequiredCapabilitiesAndExtensions() const {
  CapabilitySet required_capabilities;
  ExtensionSet required_extensions;

  get_module()->ForEachInst([&](Instruction* instruction) {
    addInstructionRequirements(instruction, &required_capabilities,
                               &required_extensions);
  });

#if !defined(NDEBUG)
  // Debug only. We check the outputted required capabilities against the
  // supported capabilities list. The supported capabilities list is useful for
  // API users to quickly determine if they can use the pass or not. But this
  // list has to remain up-to-date with the pass code. If we can detect a
  // capability as required, but it's not listed, it means the list is
  // out-of-sync. This method is not ideal, but should cover most cases.
  {
    for (auto capability : required_capabilities) {
      assert(supportedCapabilities_.contains(capability) &&
             "Module is using a capability that is not listed as supported.");
    }
  }
#endif

  return std::make_pair(std::move(required_capabilities),
                        std::move(required_extensions));
}

Pass::Status TrimCapabilitiesPass::TrimUnrequiredCapabilities(
    const CapabilitySet& required_capabilities) const {
  const FeatureManager* feature_manager = context()->get_feature_mgr();
  CapabilitySet capabilities_to_trim;
  for (auto capability : feature_manager->GetCapabilities()) {
    // Forbidden capability completely prevents trimming. Early exit.
    if (forbiddenCapabilities_.contains(capability)) {
      return Pass::Status::SuccessWithoutChange;
    }

    // Some capabilities cannot be safely removed. Leaving them untouched.
    if (untouchableCapabilities_.contains(capability)) {
      continue;
    }

    // If the capability is unsupported, don't trim it.
    if (!supportedCapabilities_.contains(capability)) {
      continue;
    }

    if (required_capabilities.contains(capability)) {
      continue;
    }

    capabilities_to_trim.insert(capability);
  }

  for (auto capability : capabilities_to_trim) {
    context()->RemoveCapability(capability);
  }

  return capabilities_to_trim.size() == 0 ? Pass::Status::SuccessWithoutChange
                                          : Pass::Status::SuccessWithChange;
}

Pass::Status TrimCapabilitiesPass::TrimUnrequiredExtensions(
    const ExtensionSet& required_extensions) const {
  const auto supported_extensions =
      getExtensionsRelatedTo(supportedCapabilities_, context()->grammar());

  bool modified_module = false;
  for (auto extension : supported_extensions) {
    if (!required_extensions.contains(extension)) {
      modified_module = true;
      context()->RemoveExtension(extension);
    }
  }

  return modified_module ? Pass::Status::SuccessWithChange
                         : Pass::Status::SuccessWithoutChange;
}

Pass::Status TrimCapabilitiesPass::Process() {
  auto[required_capabilities, required_extensions] =
      DetermineRequiredCapabilitiesAndExtensions();

  Pass::Status status = TrimUnrequiredCapabilities(required_capabilities);
  // If no capabilities were removed, we have no extension to trim.
  // Note: this is true because this pass only removes unused extensions caused
  // by unused capabilities.
  //       This is not an extension trimming pass.
  if (status == Pass::Status::SuccessWithoutChange) {
    return status;
  }
  return TrimUnrequiredExtensions(required_extensions);
}

}  // namespace opt
}  // namespace spvtools

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
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "source/enum_set.h"
#include "source/enum_string_mapping.h"
#include "source/opt/ir_context.h"
#include "source/opt/reflect.h"
#include "source/spirv_target_env.h"
#include "source/util/string_utils.h"

namespace spvtools {
namespace opt {

namespace {
constexpr uint32_t kOpTypePointerStorageClassIndex = 0;
constexpr uint32_t kTypeArrayTypeIndex = 0;
constexpr uint32_t kOpTypeScalarBitWidthIndex = 0;
constexpr uint32_t kTypePointerTypeIdInIdx = 1;

// DFS visit of the type defined by `instruction`.
// If `condition` is true, children of the current node are visited.
// If `condition` is false, the children of the current node are ignored.
template <class UnaryPredicate>
static void DFSWhile(const Instruction* instruction, UnaryPredicate condition) {
  std::stack<uint32_t> instructions_to_visit;
  instructions_to_visit.push(instruction->result_id());
  const auto* def_use_mgr = instruction->context()->get_def_use_mgr();

  while (!instructions_to_visit.empty()) {
    const Instruction* item = def_use_mgr->GetDef(instructions_to_visit.top());
    instructions_to_visit.pop();

    if (!condition(item)) {
      continue;
    }

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
  }
}

// Walks the type defined by `instruction` (OpType* only).
// Returns `true` if any call to `predicate` with the type/subtype returns true.
template <class UnaryPredicate>
static bool AnyTypeOf(const Instruction* instruction,
                      UnaryPredicate predicate) {
  assert(IsTypeInst(instruction->opcode()) &&
         "AnyTypeOf called with a non-type instruction.");

  bool found_one = false;
  DFSWhile(instruction, [&found_one, predicate](const Instruction* node) {
    if (found_one || predicate(node)) {
      found_one = true;
      return false;
    }

    return true;
  });
  return found_one;
}

static bool is16bitType(const Instruction* instruction) {
  if (instruction->opcode() != spv::Op::OpTypeInt &&
      instruction->opcode() != spv::Op::OpTypeFloat) {
    return false;
  }

  return instruction->GetSingleWordInOperand(kOpTypeScalarBitWidthIndex) == 16;
}

static bool Has16BitCapability(const FeatureManager* feature_manager) {
  const CapabilitySet& capabilities = feature_manager->GetCapabilities();
  return capabilities.contains(spv::Capability::Float16) ||
         capabilities.contains(spv::Capability::Int16);
}

}  // namespace

// ============== Begin opcode handler implementations. =======================
//
// Adding support for a new capability should only require adding a new handler,
// and updating the
// kSupportedCapabilities/kUntouchableCapabilities/kFordiddenCapabilities lists.
//
// Handler names follow the following convention:
//  Handler_<Opcode>_<Capability>()

static std::optional<spv::Capability>
Handler_OpTypePointer_StorageInputOutput16(const Instruction* instruction) {
  assert(instruction->opcode() == spv::Op::OpTypePointer &&
         "This handler only support OpTypePointer opcodes.");

  // This capability is only required if the variable has an Input/Output
  // storage class.
  spv::StorageClass storage_class = spv::StorageClass(
      instruction->GetSingleWordInOperand(kOpTypePointerStorageClassIndex));
  if (storage_class != spv::StorageClass::Input &&
      storage_class != spv::StorageClass::Output) {
    return std::nullopt;
  }

  if (!Has16BitCapability(instruction->context()->get_feature_mgr())) {
    return std::nullopt;
  }

  return AnyTypeOf(instruction, is16bitType)
             ? std::optional(spv::Capability::StorageInputOutput16)
             : std::nullopt;
}

static std::optional<spv::Capability>
Handler_OpTypePointer_StoragePushConstant16(const Instruction* instruction) {
  assert(instruction->opcode() == spv::Op::OpTypePointer &&
         "This handler only support OpTypePointer opcodes.");

  // This capability is only required if the variable has a PushConstant storage
  // class.
  spv::StorageClass storage_class = spv::StorageClass(
      instruction->GetSingleWordInOperand(kOpTypePointerStorageClassIndex));
  if (storage_class != spv::StorageClass::PushConstant) {
    return std::nullopt;
  }

  if (!Has16BitCapability(instruction->context()->get_feature_mgr())) {
    return std::nullopt;
  }

  return AnyTypeOf(instruction, is16bitType)
             ? std::optional(spv::Capability::StoragePushConstant16)
             : std::nullopt;
}

static std::optional<spv::Capability>
Handler_OpTypePointer_StorageUniformBufferBlock16(
    const Instruction* instruction) {
  assert(instruction->opcode() == spv::Op::OpTypePointer &&
         "This handler only support OpTypePointer opcodes.");

  // This capability is only required if the variable has a Uniform storage
  // class.
  spv::StorageClass storage_class = spv::StorageClass(
      instruction->GetSingleWordInOperand(kOpTypePointerStorageClassIndex));
  if (storage_class != spv::StorageClass::Uniform) {
    return std::nullopt;
  }

  if (!Has16BitCapability(instruction->context()->get_feature_mgr())) {
    return std::nullopt;
  }

  const auto* decoration_mgr = instruction->context()->get_decoration_mgr();
  const bool matchesCondition =
      AnyTypeOf(instruction, [decoration_mgr](const Instruction* item) {
        if (!decoration_mgr->HasDecoration(item->result_id(),
                                           spv::Decoration::BufferBlock)) {
          return false;
        }

        return AnyTypeOf(item, is16bitType);
      });

  return matchesCondition
             ? std::optional(spv::Capability::StorageUniformBufferBlock16)
             : std::nullopt;
}

static std::optional<spv::Capability> Handler_OpTypePointer_StorageUniform16(
    const Instruction* instruction) {
  assert(instruction->opcode() == spv::Op::OpTypePointer &&
         "This handler only support OpTypePointer opcodes.");

  // This capability is only required if the variable has a Uniform storage
  // class.
  spv::StorageClass storage_class = spv::StorageClass(
      instruction->GetSingleWordInOperand(kOpTypePointerStorageClassIndex));
  if (storage_class != spv::StorageClass::Uniform) {
    return std::nullopt;
  }

  const auto* feature_manager = instruction->context()->get_feature_mgr();
  if (!Has16BitCapability(feature_manager)) {
    return std::nullopt;
  }

  const bool hasBufferBlockCapability =
      feature_manager->GetCapabilities().contains(
          spv::Capability::StorageUniformBufferBlock16);
  const auto* decoration_mgr = instruction->context()->get_decoration_mgr();
  bool found16bitType = false;

  DFSWhile(instruction, [decoration_mgr, hasBufferBlockCapability,
                         &found16bitType](const Instruction* item) {
    if (found16bitType) {
      return false;
    }

    if (hasBufferBlockCapability &&
        decoration_mgr->HasDecoration(item->result_id(),
                                      spv::Decoration::BufferBlock)) {
      return false;
    }

    if (is16bitType(item)) {
      found16bitType = true;
      return false;
    }

    return true;
  });

  return found16bitType ? std::optional(spv::Capability::StorageUniform16)
                        : std::nullopt;
}

// Opcode of interest to determine capabilities requirements.
constexpr std::array<std::pair<spv::Op, OpcodeHandler>, 4> kOpcodeHandlers{{
    // clang-format off
    {spv::Op::OpTypePointer, Handler_OpTypePointer_StorageInputOutput16},
    {spv::Op::OpTypePointer, Handler_OpTypePointer_StoragePushConstant16},
    {spv::Op::OpTypePointer, Handler_OpTypePointer_StorageUniformBufferBlock16},
    {spv::Op::OpTypePointer, Handler_OpTypePointer_StorageUniform16}
    // clang-format on
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

void TrimCapabilitiesPass::addInstructionRequirementsForOpcode(
    spv::Op opcode, CapabilitySet* capabilities,
    ExtensionSet* extensions) const {
  // Ignoring OpBeginInvocationInterlockEXT and OpEndInvocationInterlockEXT
  // because they have three possible capabilities, only one of which is needed
  if (opcode == spv::Op::OpBeginInvocationInterlockEXT ||
      opcode == spv::Op::OpEndInvocationInterlockEXT) {
    return;
  }

  const spv_opcode_desc_t* desc = {};
  auto result = context()->grammar().lookupOpcode(opcode, &desc);
  if (result != SPV_SUCCESS) {
    return;
  }

  addSupportedCapabilitiesToSet(desc, capabilities);
  addSupportedExtensionsToSet(desc, extensions);
}

void TrimCapabilitiesPass::addInstructionRequirementsForOperand(
    const Operand& operand, CapabilitySet* capabilities,
    ExtensionSet* extensions) const {
  // No supported capability relies on a 2+-word operand.
  if (operand.words.size() != 1) {
    return;
  }

  // No supported capability relies on a literal string operand or an ID.
  if (operand.type == SPV_OPERAND_TYPE_LITERAL_STRING ||
      operand.type == SPV_OPERAND_TYPE_ID ||
      operand.type == SPV_OPERAND_TYPE_RESULT_ID) {
    return;
  }

  // case 1: Operand is a single value, can directly lookup.
  if (!spvOperandIsConcreteMask(operand.type)) {
    const spv_operand_desc_t* desc = {};
    auto result = context()->grammar().lookupOperand(operand.type,
                                                     operand.words[0], &desc);
    if (result != SPV_SUCCESS) {
      return;
    }
    addSupportedCapabilitiesToSet(desc, capabilities);
    addSupportedExtensionsToSet(desc, extensions);
    return;
  }

  // case 2: operand can be a bitmask, we need to decompose the lookup.
  for (uint32_t i = 0; i < 32; i++) {
    const uint32_t mask = (1 << i) & operand.words[0];
    if (!mask) {
      continue;
    }

    const spv_operand_desc_t* desc = {};
    auto result = context()->grammar().lookupOperand(operand.type, mask, &desc);
    if (result != SPV_SUCCESS) {
      continue;
    }

    addSupportedCapabilitiesToSet(desc, capabilities);
    addSupportedExtensionsToSet(desc, extensions);
  }
}

void TrimCapabilitiesPass::addInstructionRequirements(
    Instruction* instruction, CapabilitySet* capabilities,
    ExtensionSet* extensions) const {
  // Ignoring OpCapability and OpExtension instructions.
  if (instruction->opcode() == spv::Op::OpCapability ||
      instruction->opcode() == spv::Op::OpExtension) {
    return;
  }

  addInstructionRequirementsForOpcode(instruction->opcode(), capabilities,
                                      extensions);

  // Second case: one of the opcode operand is gated by a capability.
  const uint32_t operandCount = instruction->NumOperands();
  for (uint32_t i = 0; i < operandCount; i++) {
    addInstructionRequirementsForOperand(instruction->GetOperand(i),
                                         capabilities, extensions);
  }

  // Last case: some complex logic needs to be run to determine capabilities.
  auto[begin, end] = opcodeHandlers_.equal_range(instruction->opcode());
  for (auto it = begin; it != end; it++) {
    const OpcodeHandler handler = it->second;
    auto result = handler(instruction);
    if (!result.has_value()) {
      continue;
    }

    capabilities->insert(*result);
  }
}

void TrimCapabilitiesPass::AddExtensionsForOperand(
    const spv_operand_type_t type, const uint32_t value,
    ExtensionSet* extensions) const {
  const spv_operand_desc_t* desc = nullptr;
  spv_result_t result = context()->grammar().lookupOperand(type, value, &desc);
  if (result != SPV_SUCCESS) {
    return;
  }
  addSupportedExtensionsToSet(desc, extensions);
}

std::pair<CapabilitySet, ExtensionSet>
TrimCapabilitiesPass::DetermineRequiredCapabilitiesAndExtensions() const {
  CapabilitySet required_capabilities;
  ExtensionSet required_extensions;

  get_module()->ForEachInst([&](Instruction* instruction) {
    addInstructionRequirements(instruction, &required_capabilities,
                               &required_extensions);
  });

  for (auto capability : required_capabilities) {
    AddExtensionsForOperand(SPV_OPERAND_TYPE_CAPABILITY,
                            static_cast<uint32_t>(capability),
                            &required_extensions);
  }

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
    if (required_extensions.contains(extension)) {
      continue;
    }

    if (context()->RemoveExtension(extension)) {
      modified_module = true;
    }
  }

  return modified_module ? Pass::Status::SuccessWithChange
                         : Pass::Status::SuccessWithoutChange;
}

bool TrimCapabilitiesPass::HasForbiddenCapabilities() const {
  // EnumSet.HasAnyOf returns `true` if the given set is empty.
  if (forbiddenCapabilities_.size() == 0) {
    return false;
  }

  const auto& capabilities = context()->get_feature_mgr()->GetCapabilities();
  return capabilities.HasAnyOf(forbiddenCapabilities_);
}

Pass::Status TrimCapabilitiesPass::Process() {
  if (HasForbiddenCapabilities()) {
    return Status::SuccessWithoutChange;
  }

  auto[required_capabilities, required_extensions] =
      DetermineRequiredCapabilitiesAndExtensions();

  Pass::Status capStatus = TrimUnrequiredCapabilities(required_capabilities);
  Pass::Status extStatus = TrimUnrequiredExtensions(required_extensions);

  return capStatus == Pass::Status::SuccessWithChange ||
                 extStatus == Pass::Status::SuccessWithChange
             ? Pass::Status::SuccessWithChange
             : Pass::Status::SuccessWithoutChange;
}

}  // namespace opt
}  // namespace spvtools

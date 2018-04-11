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

#include "validate.h"

#include <cassert>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

#include "diagnostic.h"
#include "instruction.h"
#include "message.h"
#include "opcode.h"
#include "operand.h"
#include "spirv-tools/libspirv.h"
#include "spirv_validator_options.h"
#include "val/function.h"
#include "val/validation_state.h"

using libspirv::Decoration;
using libspirv::Function;
using libspirv::ValidationState_t;
using std::function;
using std::ignore;
using std::make_pair;
using std::pair;
using std::unordered_set;
using std::vector;

namespace {

class idUsage {
 public:
  idUsage(spv_const_context context, const spv_instruction_t* pInsts,
          const uint64_t instCountArg, const SpvMemoryModel memoryModelArg,
          const SpvAddressingModel addressingModelArg,
          const ValidationState_t& module, const vector<uint32_t>& entry_points,
          spv_position positionArg, const spvtools::MessageConsumer& consumer)
      : targetEnv(context->target_env),
        opcodeTable(context->opcode_table),
        operandTable(context->operand_table),
        extInstTable(context->ext_inst_table),
        firstInst(pInsts),
        instCount(instCountArg),
        memoryModel(memoryModelArg),
        addressingModel(addressingModelArg),
        position(positionArg),
        consumer_(consumer),
        module_(module),
        entry_points_(entry_points) {}

  bool isValid(const spv_instruction_t* inst);

  template <SpvOp>
  bool isValid(const spv_instruction_t* inst, const spv_opcode_desc);

 private:
  const spv_target_env targetEnv;
  const spv_opcode_table opcodeTable;
  const spv_operand_table operandTable;
  const spv_ext_inst_table extInstTable;
  const spv_instruction_t* const firstInst;
  const uint64_t instCount;
  const SpvMemoryModel memoryModel;
  const SpvAddressingModel addressingModel;
  spv_position position;
  const spvtools::MessageConsumer& consumer_;
  const ValidationState_t& module_;
  vector<uint32_t> entry_points_;

  // Returns true if the two instructions represent structs that, as far as the
  // validator can tell, have the exact same data layout.
  bool AreLayoutCompatibleStructs(const libspirv::Instruction* type1,
                                  const libspirv::Instruction* type2);

  // Returns true if the operands to the OpTypeStruct instruction defining the
  // types are the same or are layout compatible types. |type1| and |type2| must
  // be OpTypeStruct instructions.
  bool HaveLayoutCompatibleMembers(const libspirv::Instruction* type1,
                                   const libspirv::Instruction* type2);

  // Returns true if all decorations that affect the data layout of the struct
  // (like Offset), are the same for the two types. |type1| and |type2| must be
  // OpTypeStruct instructions.
  bool HaveSameLayoutDecorations(const libspirv::Instruction* type1,
                                 const libspirv::Instruction* type2);
  bool HasConflictingMemberOffsets(
      const vector<Decoration>& type1_decorations,
      const vector<Decoration>& type2_decorations) const;
};

#define DIAG(INDEX)                                                \
  position->index += INDEX;                                        \
  libspirv::DiagnosticStream helper(*position, consumer_,          \
                                    SPV_ERROR_INVALID_DIAGNOSTIC); \
  helper

#if 0
template <>
bool idUsage::isValid<SpvOpUndef>(const spv_instruction_t *inst,
                                  const spv_opcode_desc) {
  assert(0 && "Unimplemented!");
  return false;
}
#endif  // 0

template <>
bool idUsage::isValid<SpvOpMemberName>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  auto typeIndex = 1;
  auto type = module_.FindDef(inst->words[typeIndex]);
  if (!type || SpvOpTypeStruct != type->opcode()) {
    DIAG(typeIndex) << "OpMemberName Type <id> '" << inst->words[typeIndex]
                    << "' is not a struct type.";
    return false;
  }
  auto memberIndex = 2;
  auto member = inst->words[memberIndex];
  auto memberCount = (uint32_t)(type->words().size() - 2);
  if (memberCount <= member) {
    DIAG(memberIndex) << "OpMemberName Member <id> '"
                      << inst->words[memberIndex]
                      << "' index is larger than Type <id> '" << type->id()
                      << "'s member count.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpLine>(const spv_instruction_t* inst,
                                 const spv_opcode_desc) {
  auto fileIndex = 1;
  auto file = module_.FindDef(inst->words[fileIndex]);
  if (!file || SpvOpString != file->opcode()) {
    DIAG(fileIndex) << "OpLine Target <id> '" << inst->words[fileIndex]
                    << "' is not an OpString.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpDecorate>(const spv_instruction_t* inst,
                                     const spv_opcode_desc) {
  auto decorationIndex = 2;
  auto decoration = inst->words[decorationIndex];
  if (decoration == SpvDecorationSpecId) {
    auto targetIndex = 1;
    auto target = module_.FindDef(inst->words[targetIndex]);
    if (!target || !spvOpcodeIsScalarSpecConstant(target->opcode())) {
      DIAG(targetIndex) << "OpDecorate SpectId decoration target <id> '"
                        << inst->words[decorationIndex]
                        << "' is not a scalar specialization constant.";
      return false;
    }
  }
  // TODO: Add validations for all decorations.
  return true;
}

template <>
bool idUsage::isValid<SpvOpMemberDecorate>(const spv_instruction_t* inst,
                                           const spv_opcode_desc) {
  auto structTypeIndex = 1;
  auto structType = module_.FindDef(inst->words[structTypeIndex]);
  if (!structType || SpvOpTypeStruct != structType->opcode()) {
    DIAG(structTypeIndex) << "OpMemberDecorate Structure type <id> '"
                          << inst->words[structTypeIndex]
                          << "' is not a struct type.";
    return false;
  }
  auto memberIndex = 2;
  auto member = inst->words[memberIndex];
  auto memberCount = static_cast<uint32_t>(structType->words().size() - 2);
  if (memberCount < member) {
    DIAG(memberIndex) << "Index " << member
                      << " provided in OpMemberDecorate for struct <id> "
                      << inst->words[structTypeIndex]
                      << " is out of bounds. The structure has " << memberCount
                      << " members. Largest valid index is " << memberCount - 1
                      << ".";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpDecorationGroup>(const spv_instruction_t* inst,
                                            const spv_opcode_desc) {
  auto decorationGroupIndex = 1;
  auto decorationGroup = module_.FindDef(inst->words[decorationGroupIndex]);

  for (auto pair : decorationGroup->uses()) {
    auto use = pair.first;
    if (use->opcode() != SpvOpDecorate && use->opcode() != SpvOpGroupDecorate &&
        use->opcode() != SpvOpGroupMemberDecorate &&
        use->opcode() != SpvOpName) {
      DIAG(decorationGroupIndex) << "Result id of OpDecorationGroup can only "
                                 << "be targeted by OpName, OpGroupDecorate, "
                                 << "OpDecorate, and OpGroupMemberDecorate";
      return false;
    }
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpGroupDecorate>(const spv_instruction_t* inst,
                                          const spv_opcode_desc) {
  auto decorationGroupIndex = 1;
  auto decorationGroup = module_.FindDef(inst->words[decorationGroupIndex]);
  if (!decorationGroup || SpvOpDecorationGroup != decorationGroup->opcode()) {
    DIAG(decorationGroupIndex)
        << "OpGroupDecorate Decoration group <id> '"
        << inst->words[decorationGroupIndex] << "' is not a decoration group.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpGroupMemberDecorate>(const spv_instruction_t* inst,
                                                const spv_opcode_desc) {
  auto decorationGroupIndex = 1;
  auto decorationGroup = module_.FindDef(inst->words[decorationGroupIndex]);
  if (!decorationGroup || SpvOpDecorationGroup != decorationGroup->opcode()) {
    DIAG(decorationGroupIndex)
        << "OpGroupMemberDecorate Decoration group <id> '"
        << inst->words[decorationGroupIndex] << "' is not a decoration group.";
    return false;
  }
  // Grammar checks ensures that the number of arguments to this instruction
  // is an odd number: 1 decoration group + (id,literal) pairs.
  for (size_t i = 2; i + 1 < inst->words.size(); i = i + 2) {
    const uint32_t struct_id = inst->words[i];
    const uint32_t index = inst->words[i + 1];
    auto struct_instr = module_.FindDef(struct_id);
    if (!struct_instr || SpvOpTypeStruct != struct_instr->opcode()) {
      DIAG(i) << "OpGroupMemberDecorate Structure type <id> '" << struct_id
              << "' is not a struct type.";
      return false;
    }
    const uint32_t num_struct_members =
        static_cast<uint32_t>(struct_instr->words().size() - 2);
    if (index >= num_struct_members) {
      DIAG(i) << "Index " << index
              << " provided in OpGroupMemberDecorate for struct <id> "
              << struct_id << " is out of bounds. The structure has "
              << num_struct_members << " members. Largest valid index is "
              << num_struct_members - 1 << ".";
      return false;
    }
  }
  return true;
}

#if 0
template <>
bool idUsage::isValid<SpvOpExtInst>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif  // 0

template <>
bool idUsage::isValid<SpvOpEntryPoint>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  auto entryPointIndex = 2;
  auto entryPoint = module_.FindDef(inst->words[entryPointIndex]);
  if (!entryPoint || SpvOpFunction != entryPoint->opcode()) {
    DIAG(entryPointIndex) << "OpEntryPoint Entry Point <id> '"
                          << inst->words[entryPointIndex]
                          << "' is not a function.";
    return false;
  }
  // don't check kernel function signatures
  const SpvExecutionModel executionModel = SpvExecutionModel(inst->words[1]);
  if (executionModel != SpvExecutionModelKernel) {
    // TODO: Check the entry point signature is void main(void), may be subject
    // to change
    auto entryPointType = module_.FindDef(entryPoint->words()[4]);
    if (!entryPointType || 3 != entryPointType->words().size()) {
      DIAG(entryPointIndex)
          << "OpEntryPoint Entry Point <id> '" << inst->words[entryPointIndex]
          << "'s function parameter count is not zero.";
      return false;
    }
  }

  std::stack<uint32_t> call_stack;
  std::set<uint32_t> visited;
  call_stack.push(entryPoint->id());
  while (!call_stack.empty()) {
    const uint32_t called_func_id = call_stack.top();
    call_stack.pop();
    if (!visited.insert(called_func_id).second) continue;

    const Function* called_func = module_.function(called_func_id);
    assert(called_func);

    std::string reason;
    if (!called_func->IsCompatibleWithExecutionModel(executionModel, &reason)) {
      DIAG(entryPointIndex)
          << "OpEntryPoint Entry Point <id> '" << inst->words[entryPointIndex]
          << "'s callgraph contains function <id> " << called_func_id
          << ", which cannot be used with the current execution model:\n"
          << reason;
      return false;
    }

    for (uint32_t new_call : called_func->function_call_targets()) {
      call_stack.push(new_call);
    }
  }

  auto returnType = module_.FindDef(entryPoint->type_id());
  if (!returnType || SpvOpTypeVoid != returnType->opcode()) {
    DIAG(entryPointIndex) << "OpEntryPoint Entry Point <id> '"
                          << inst->words[entryPointIndex]
                          << "'s function return type is not void.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpExecutionMode>(const spv_instruction_t* inst,
                                          const spv_opcode_desc) {
  auto entryPointIndex = 1;
  auto entryPointID = inst->words[entryPointIndex];
  auto found =
      std::find(entry_points_.cbegin(), entry_points_.cend(), entryPointID);
  if (found == entry_points_.cend()) {
    DIAG(entryPointIndex) << "OpExecutionMode Entry Point <id> '"
                          << inst->words[entryPointIndex]
                          << "' is not the Entry Point "
                             "operand of an OpEntryPoint.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeVector>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  auto componentIndex = 2;
  auto componentType = module_.FindDef(inst->words[componentIndex]);
  if (!componentType || !spvOpcodeIsScalarType(componentType->opcode())) {
    DIAG(componentIndex) << "OpTypeVector Component Type <id> '"
                         << inst->words[componentIndex]
                         << "' is not a scalar type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeMatrix>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  auto columnTypeIndex = 2;
  auto columnType = module_.FindDef(inst->words[columnTypeIndex]);
  if (!columnType || SpvOpTypeVector != columnType->opcode()) {
    DIAG(columnTypeIndex) << "OpTypeMatrix Column Type <id> '"
                          << inst->words[columnTypeIndex]
                          << "' is not a vector.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeSampler>(const spv_instruction_t*,
                                        const spv_opcode_desc) {
  // OpTypeSampler takes no arguments in Rev31 and beyond.
  return true;
}

// True if the integer constant is > 0. constWords are words of the
// constant-defining instruction (either OpConstant or
// OpSpecConstant). typeWords are the words of the constant's-type-defining
// OpTypeInt.
bool aboveZero(const vector<uint32_t>& constWords,
               const vector<uint32_t>& typeWords) {
  const uint32_t width = typeWords[2];
  const bool is_signed = typeWords[3] > 0;
  const uint32_t loWord = constWords[3];
  if (width > 32) {
    // The spec currently doesn't allow integers wider than 64 bits.
    const uint32_t hiWord = constWords[4];  // Must exist, per spec.
    if (is_signed && (hiWord >> 31)) return false;
    return (loWord | hiWord) > 0;
  } else {
    if (is_signed && (loWord >> 31)) return false;
    return loWord > 0;
  }
}

template <>
bool idUsage::isValid<SpvOpTypeArray>(const spv_instruction_t* inst,
                                      const spv_opcode_desc) {
  auto elementTypeIndex = 2;
  auto elementType = module_.FindDef(inst->words[elementTypeIndex]);
  if (!elementType || !spvOpcodeGeneratesType(elementType->opcode())) {
    DIAG(elementTypeIndex) << "OpTypeArray Element Type <id> '"
                           << inst->words[elementTypeIndex]
                           << "' is not a type.";
    return false;
  }
  auto lengthIndex = 3;
  auto length = module_.FindDef(inst->words[lengthIndex]);
  if (!length || !spvOpcodeIsConstant(length->opcode())) {
    DIAG(lengthIndex) << "OpTypeArray Length <id> '" << inst->words[lengthIndex]
                      << "' is not a scalar constant type.";
    return false;
  }

  // NOTE: Check the initialiser value of the constant
  auto constInst = length->words();
  auto constResultTypeIndex = 1;
  auto constResultType = module_.FindDef(constInst[constResultTypeIndex]);
  if (!constResultType || SpvOpTypeInt != constResultType->opcode()) {
    DIAG(lengthIndex) << "OpTypeArray Length <id> '" << inst->words[lengthIndex]
                      << "' is not a constant integer type.";
    return false;
  }

  switch (length->opcode()) {
    case SpvOpSpecConstant:
    case SpvOpConstant:
      if (aboveZero(length->words(), constResultType->words())) break;
    // Else fall through!
    case SpvOpConstantNull: {
      DIAG(lengthIndex) << "OpTypeArray Length <id> '"
                        << inst->words[lengthIndex]
                        << "' default value must be at least 1.";
      return false;
    }
    case SpvOpSpecConstantOp:
      // Assume it's OK, rather than try to evaluate the operation.
      break;
    default:
      assert(0 && "bug in spvOpcodeIsConstant() or result type isn't int");
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeRuntimeArray>(const spv_instruction_t* inst,
                                             const spv_opcode_desc) {
  auto elementTypeIndex = 2;
  auto elementType = module_.FindDef(inst->words[elementTypeIndex]);
  if (!elementType || !spvOpcodeGeneratesType(elementType->opcode())) {
    DIAG(elementTypeIndex) << "OpTypeRuntimeArray Element Type <id> '"
                           << inst->words[elementTypeIndex]
                           << "' is not a type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeStruct>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  ValidationState_t& vstate = const_cast<ValidationState_t&>(module_);
  const uint32_t struct_id = inst->words[1];
  for (size_t memberTypeIndex = 2; memberTypeIndex < inst->words.size();
       ++memberTypeIndex) {
    auto memberTypeId = inst->words[memberTypeIndex];
    auto memberType = module_.FindDef(memberTypeId);
    if (!memberType || !spvOpcodeGeneratesType(memberType->opcode())) {
      DIAG(memberTypeIndex)
          << "OpTypeStruct Member Type <id> '" << inst->words[memberTypeIndex]
          << "' is not a type.";
      return false;
    }
    if (SpvOpTypeStruct == memberType->opcode() &&
        module_.IsStructTypeWithBuiltInMember(memberTypeId)) {
      DIAG(memberTypeIndex)
          << "Structure <id> " << memberTypeId
          << " contains members with BuiltIn decoration. Therefore this "
             "structure may not be contained as a member of another structure "
             "type. Structure <id> "
          << struct_id << " contains structure <id> " << memberTypeId << ".";
      return false;
    }
    if (module_.IsForwardPointer(memberTypeId)) {
      if (memberType->opcode() != SpvOpTypePointer) {
        DIAG(memberTypeIndex) << "Found a forward reference to a non-pointer "
                                 "type in OpTypeStruct instruction.";
        return false;
      }
      // If we're dealing with a forward pointer:
      // Find out the type that the pointer is pointing to (must be struct)
      // word 3 is the <id> of the type being pointed to.
      auto typePointingTo = module_.FindDef(memberType->words()[3]);
      if (typePointingTo && typePointingTo->opcode() != SpvOpTypeStruct) {
        // Forward declared operands of a struct may only point to a struct.
        DIAG(memberTypeIndex)
            << "A forward reference operand in an OpTypeStruct must be an "
               "OpTypePointer that points to an OpTypeStruct. "
               "Found OpTypePointer that points to Op"
            << spvOpcodeString(static_cast<SpvOp>(typePointingTo->opcode()))
            << ".";
        return false;
      }
    }
  }
  std::unordered_set<uint32_t> built_in_members;
  for (auto decoration : vstate.id_decorations(struct_id)) {
    if (decoration.dec_type() == SpvDecorationBuiltIn &&
        decoration.struct_member_index() != Decoration::kInvalidMember) {
      built_in_members.insert(decoration.struct_member_index());
    }
  }
  int num_struct_members = static_cast<int>(inst->words.size() - 2);
  int num_builtin_members = static_cast<int>(built_in_members.size());
  if (num_builtin_members > 0 && num_builtin_members != num_struct_members) {
    DIAG(0)
        << "When BuiltIn decoration is applied to a structure-type member, "
           "all members of that structure type must also be decorated with "
           "BuiltIn (No allowed mixing of built-in variables and "
           "non-built-in variables within a single structure). Structure id "
        << struct_id << " does not meet this requirement.";
    return false;
  }
  if (num_builtin_members > 0) {
    vstate.RegisterStructTypeWithBuiltInMember(struct_id);
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypePointer>(const spv_instruction_t* inst,
                                        const spv_opcode_desc) {
  auto typeIndex = 3;
  auto type = module_.FindDef(inst->words[typeIndex]);
  if (!type || !spvOpcodeGeneratesType(type->opcode())) {
    DIAG(typeIndex) << "OpTypePointer Type <id> '" << inst->words[typeIndex]
                    << "' is not a type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypeFunction>(const spv_instruction_t* inst,
                                         const spv_opcode_desc) {
  auto returnTypeIndex = 2;
  auto returnType = module_.FindDef(inst->words[returnTypeIndex]);
  if (!returnType || !spvOpcodeGeneratesType(returnType->opcode())) {
    DIAG(returnTypeIndex) << "OpTypeFunction Return Type <id> '"
                          << inst->words[returnTypeIndex] << "' is not a type.";
    return false;
  }
  size_t num_args = 0;
  for (size_t paramTypeIndex = 3; paramTypeIndex < inst->words.size();
       ++paramTypeIndex, ++num_args) {
    auto paramType = module_.FindDef(inst->words[paramTypeIndex]);
    if (!paramType || !spvOpcodeGeneratesType(paramType->opcode())) {
      DIAG(paramTypeIndex) << "OpTypeFunction Parameter Type <id> '"
                           << inst->words[paramTypeIndex] << "' is not a type.";
      return false;
    }
  }
  const uint32_t num_function_args_limit =
      module_.options()->universal_limits_.max_function_args;
  if (num_args > num_function_args_limit) {
    DIAG(returnTypeIndex) << "OpTypeFunction may not take more than "
                          << num_function_args_limit
                          << " arguments. OpTypeFunction <id> '"
                          << inst->words[1] << "' has " << num_args
                          << " arguments.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpTypePipe>(const spv_instruction_t*,
                                     const spv_opcode_desc) {
  // OpTypePipe has no ID arguments.
  return true;
}

template <>
bool idUsage::isValid<SpvOpConstantTrue>(const spv_instruction_t* inst,
                                         const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypeBool != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpConstantTrue Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a boolean type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpConstantFalse>(const spv_instruction_t* inst,
                                          const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypeBool != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpConstantFalse Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a boolean type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpConstantComposite>(const spv_instruction_t* inst,
                                              const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || !spvOpcodeIsComposite(resultType->opcode())) {
    DIAG(resultTypeIndex) << "OpConstantComposite Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a composite type.";
    return false;
  }

  auto constituentCount = inst->words.size() - 3;
  switch (resultType->opcode()) {
    case SpvOpTypeVector: {
      auto componentCount = resultType->words()[3];
      if (componentCount != constituentCount) {
        // TODO: Output ID's on diagnostic
        DIAG(inst->words.size() - 1)
            << "OpConstantComposite Constituent <id> count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s vector component count.";
        return false;
      }
      auto componentType = module_.FindDef(resultType->words()[2]);
      assert(componentType);
      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentResultType = module_.FindDef(constituent->type_id());
        if (!constituentResultType ||
            componentType->opcode() != constituentResultType->opcode()) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "'s type does not match Result Type <id> '" << resultType->id()
              << "'s vector element type.";
          return false;
        }
      }
    } break;
    case SpvOpTypeMatrix: {
      auto columnCount = resultType->words()[3];
      if (columnCount != constituentCount) {
        // TODO: Output ID's on diagnostic
        DIAG(inst->words.size() - 1)
            << "OpConstantComposite Constituent <id> count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s matrix column count.";
        return false;
      }

      auto columnType = module_.FindDef(resultType->words()[2]);
      assert(columnType);
      auto componentCount = columnType->words()[3];
      auto componentType = module_.FindDef(columnType->words()[2]);
      assert(componentType);

      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent || !(SpvOpConstantComposite == constituent->opcode() ||
                              SpvOpUndef == constituent->opcode())) {
          // The message says "... or undef" because the spec does not say
          // undef is a constant.
          DIAG(constituentIndex) << "OpConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant composite or undef.";
          return false;
        }
        auto vector = module_.FindDef(constituent->type_id());
        assert(vector);
        if (columnType->opcode() != vector->opcode()) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' type does not match Result Type <id> '" << resultType->id()
              << "'s matrix column type.";
          return false;
        }
        auto vectorComponentType = module_.FindDef(vector->words()[2]);
        assert(vectorComponentType);
        if (componentType->id() != vectorComponentType->id()) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' component type does not match Result Type <id> '"
              << resultType->id() << "'s matrix column component type.";
          return false;
        }
        if (componentCount != vector->words()[3]) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' vector component count does not match Result Type <id> '"
              << resultType->id() << "'s vector component count.";
          return false;
        }
      }
    } break;
    case SpvOpTypeArray: {
      auto elementType = module_.FindDef(resultType->words()[2]);
      assert(elementType);
      auto length = module_.FindDef(resultType->words()[3]);
      assert(length);
      if (length->words()[3] != constituentCount) {
        DIAG(inst->words.size() - 1)
            << "OpConstantComposite Constituent count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s array length.";
        return false;
      }
      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentType = module_.FindDef(constituent->type_id());
        assert(constituentType);
        if (elementType->id() != constituentType->id()) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "'s type does not match Result Type <id> '" << resultType->id()
              << "'s array element type.";
          return false;
        }
      }
    } break;
    case SpvOpTypeStruct: {
      auto memberCount = resultType->words().size() - 2;
      if (memberCount != constituentCount) {
        DIAG(resultTypeIndex) << "OpConstantComposite Constituent <id> '"
                              << inst->words[resultTypeIndex]
                              << "' count does not match Result Type <id> '"
                              << resultType->id() << "'s struct member count.";
        return false;
      }
      for (uint32_t constituentIndex = 3, memberIndex = 2;
           constituentIndex < inst->words.size();
           constituentIndex++, memberIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentType = module_.FindDef(constituent->type_id());
        assert(constituentType);

        auto memberType = module_.FindDef(resultType->words()[memberIndex]);
        assert(memberType);
        if (memberType->id() != constituentType->id()) {
          DIAG(constituentIndex)
              << "OpConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' type does not match the Result Type <id> '"
              << resultType->id() << "'s member type.";
          return false;
        }
      }
    } break;
    default: { assert(0 && "Unreachable!"); } break;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpConstantSampler>(const spv_instruction_t* inst,
                                            const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypeSampler != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpConstantSampler Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a sampler type.";
    return false;
  }
  return true;
}

// True if instruction defines a type that can have a null value, as defined by
// the SPIR-V spec.  Tracks composite-type components through module to check
// nullability transitively.
bool IsTypeNullable(const vector<uint32_t>& instruction,
                    const ValidationState_t& module) {
  uint16_t opcode;
  uint16_t word_count;
  spvOpcodeSplit(instruction[0], &word_count, &opcode);
  switch (static_cast<SpvOp>(opcode)) {
    case SpvOpTypeBool:
    case SpvOpTypeInt:
    case SpvOpTypeFloat:
    case SpvOpTypePointer:
    case SpvOpTypeEvent:
    case SpvOpTypeDeviceEvent:
    case SpvOpTypeReserveId:
    case SpvOpTypeQueue:
      return true;
    case SpvOpTypeArray:
    case SpvOpTypeMatrix:
    case SpvOpTypeVector: {
      auto base_type = module.FindDef(instruction[2]);
      return base_type && IsTypeNullable(base_type->words(), module);
    }
    case SpvOpTypeStruct: {
      for (size_t elementIndex = 2; elementIndex < instruction.size();
           ++elementIndex) {
        auto element = module.FindDef(instruction[elementIndex]);
        if (!element || !IsTypeNullable(element->words(), module)) return false;
      }
      return true;
    }
    default:
      return false;
  }
}

template <>
bool idUsage::isValid<SpvOpConstantNull>(const spv_instruction_t* inst,
                                         const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || !IsTypeNullable(resultType->words(), module_)) {
    DIAG(resultTypeIndex) << "OpConstantNull Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' cannot have a null value.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpSpecConstantTrue>(const spv_instruction_t* inst,
                                             const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypeBool != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpSpecConstantTrue Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a boolean type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpSpecConstantFalse>(const spv_instruction_t* inst,
                                              const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypeBool != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpSpecConstantFalse Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a boolean type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpSampledImage>(const spv_instruction_t* inst,
                                         const spv_opcode_desc) {
  auto resultTypeIndex = 2;
  auto resultID = inst->words[resultTypeIndex];
  auto sampledImageInstr = module_.FindDef(resultID);
  // We need to validate 2 things:
  // * All OpSampledImage instructions must be in the same block in which their
  // Result <id> are consumed.
  // * Result <id> from OpSampledImage instructions must not appear as operands
  // to OpPhi instructions or OpSelect instructions, or any instructions other
  // than the image lookup and query instructions specified to take an operand
  // whose type is OpTypeSampledImage.
  std::vector<uint32_t> consumers = module_.getSampledImageConsumers(resultID);
  if (!consumers.empty()) {
    for (auto consumer_id : consumers) {
      auto consumer_instr = module_.FindDef(consumer_id);
      auto consumer_opcode = consumer_instr->opcode();
      if (consumer_instr->block() != sampledImageInstr->block()) {
        DIAG(resultTypeIndex)
            << "All OpSampledImage instructions must be in the same block in "
               "which their Result <id> are consumed. OpSampledImage Result "
               "Type <id> '"
            << resultID
            << "' has a consumer in a different basic "
               "block. The consumer instruction <id> is '"
            << consumer_id << "'.";
        return false;
      }
      // TODO: The following check is incomplete. We should also check that the
      // Sampled Image is not used by instructions that should not take
      // SampledImage as an argument. We could find the list of valid
      // instructions by scanning for "Sampled Image" in the operand description
      // field in the grammar file.
      if (consumer_opcode == SpvOpPhi || consumer_opcode == SpvOpSelect) {
        DIAG(resultTypeIndex)
            << "Result <id> from OpSampledImage instruction must not appear as "
               "operands of Op"
            << spvOpcodeString(static_cast<SpvOp>(consumer_opcode)) << "."
            << " Found result <id> '" << resultID << "' as an operand of <id> '"
            << consumer_id << "'.";
        return false;
      }
    }
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpSpecConstantComposite>(const spv_instruction_t* inst,
                                                  const spv_opcode_desc) {
  // The result type must be a composite type.
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || !spvOpcodeIsComposite(resultType->opcode())) {
    DIAG(resultTypeIndex) << "OpSpecConstantComposite Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a composite type.";
    return false;
  }
  // Validation checks differ based on the type of composite type.
  auto constituentCount = inst->words.size() - 3;
  switch (resultType->opcode()) {
    // For Vectors, the following must be met:
    // * Number of constituents in the result type and the vector must match.
    // * All the components of the vector must have the same type (or specialize
    // to the same type). OpConstant and OpSpecConstant are allowed.
    // To check that condition, we check each supplied value argument's type
    // against the element type of the result type.
    case SpvOpTypeVector: {
      auto componentCount = resultType->words()[3];
      if (componentCount != constituentCount) {
        DIAG(inst->words.size() - 1)
            << "OpSpecConstantComposite Constituent <id> count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s vector component count.";
        return false;
      }
      auto componentType = module_.FindDef(resultType->words()[2]);
      assert(componentType);
      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpSpecConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentResultType = module_.FindDef(constituent->type_id());
        if (!constituentResultType ||
            componentType->opcode() != constituentResultType->opcode()) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "'s type does not match Result Type <id> '" << resultType->id()
              << "'s vector element type.";
          return false;
        }
      }
      break;
    }
    case SpvOpTypeMatrix: {
      auto columnCount = resultType->words()[3];
      if (columnCount != constituentCount) {
        DIAG(inst->words.size() - 1)
            << "OpSpecConstantComposite Constituent <id> count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s matrix column count.";
        return false;
      }

      auto columnType = module_.FindDef(resultType->words()[2]);
      assert(columnType);
      auto componentCount = columnType->words()[3];
      auto componentType = module_.FindDef(columnType->words()[2]);
      assert(componentType);

      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        auto constituentOpCode = constituent->opcode();
        if (!constituent || !(SpvOpSpecConstantComposite == constituentOpCode ||
                              SpvOpConstantComposite == constituentOpCode ||
                              SpvOpUndef == constituentOpCode)) {
          // The message says "... or undef" because the spec does not say
          // undef is a constant.
          DIAG(constituentIndex) << "OpSpecConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant composite or undef.";
          return false;
        }
        auto vector = module_.FindDef(constituent->type_id());
        assert(vector);
        if (columnType->opcode() != vector->opcode()) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' type does not match Result Type <id> '" << resultType->id()
              << "'s matrix column type.";
          return false;
        }
        auto vectorComponentType = module_.FindDef(vector->words()[2]);
        assert(vectorComponentType);
        if (componentType->id() != vectorComponentType->id()) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' component type does not match Result Type <id> '"
              << resultType->id() << "'s matrix column component type.";
          return false;
        }
        if (componentCount != vector->words()[3]) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' vector component count does not match Result Type <id> '"
              << resultType->id() << "'s vector component count.";
          return false;
        }
      }
      break;
    }
    case SpvOpTypeArray: {
      auto elementType = module_.FindDef(resultType->words()[2]);
      assert(elementType);
      auto length = module_.FindDef(resultType->words()[3]);
      assert(length);
      if (length->words()[3] != constituentCount) {
        DIAG(inst->words.size() - 1)
            << "OpSpecConstantComposite Constituent count does not match "
               "Result Type <id> '"
            << resultType->id() << "'s array length.";
        return false;
      }
      for (size_t constituentIndex = 3; constituentIndex < inst->words.size();
           constituentIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpSpecConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentType = module_.FindDef(constituent->type_id());
        assert(constituentType);
        if (elementType->id() != constituentType->id()) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "'s type does not match Result Type <id> '" << resultType->id()
              << "'s array element type.";
          return false;
        }
      }
      break;
    }
    case SpvOpTypeStruct: {
      auto memberCount = resultType->words().size() - 2;
      if (memberCount != constituentCount) {
        DIAG(resultTypeIndex) << "OpSpecConstantComposite Constituent <id> '"
                              << inst->words[resultTypeIndex]
                              << "' count does not match Result Type <id> '"
                              << resultType->id() << "'s struct member count.";
        return false;
      }
      for (uint32_t constituentIndex = 3, memberIndex = 2;
           constituentIndex < inst->words.size();
           constituentIndex++, memberIndex++) {
        auto constituent = module_.FindDef(inst->words[constituentIndex]);
        if (!constituent ||
            !spvOpcodeIsConstantOrUndef(constituent->opcode())) {
          DIAG(constituentIndex) << "OpSpecConstantComposite Constituent <id> '"
                                 << inst->words[constituentIndex]
                                 << "' is not a constant or undef.";
          return false;
        }
        auto constituentType = module_.FindDef(constituent->type_id());
        assert(constituentType);

        auto memberType = module_.FindDef(resultType->words()[memberIndex]);
        assert(memberType);
        if (memberType->id() != constituentType->id()) {
          DIAG(constituentIndex)
              << "OpSpecConstantComposite Constituent <id> '"
              << inst->words[constituentIndex]
              << "' type does not match the Result Type <id> '"
              << resultType->id() << "'s member type.";
          return false;
        }
      }
      break;
    }
    default: { assert(0 && "Unreachable!"); } break;
  }
  return true;
}

#if 0
template <>
bool idUsage::isValid<SpvOpSpecConstantOp>(const spv_instruction_t *inst) {}
#endif

template <>
bool idUsage::isValid<SpvOpVariable>(const spv_instruction_t* inst,
                                     const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || SpvOpTypePointer != resultType->opcode()) {
    DIAG(resultTypeIndex) << "OpVariable Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' is not a pointer type.";
    return false;
  }
  const auto initialiserIndex = 4;
  if (initialiserIndex < inst->words.size()) {
    const auto initialiser = module_.FindDef(inst->words[initialiserIndex]);
    const auto storageClassIndex = 3;
    const auto is_module_scope_var =
        initialiser && (initialiser->opcode() == SpvOpVariable) &&
        (initialiser->word(storageClassIndex) != SpvStorageClassFunction);
    const auto is_constant =
        initialiser && spvOpcodeIsConstant(initialiser->opcode());
    if (!initialiser || !(is_constant || is_module_scope_var)) {
      DIAG(initialiserIndex)
          << "OpVariable Initializer <id> '" << inst->words[initialiserIndex]
          << "' is not a constant or module-scope variable.";
      return false;
    }
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpLoad>(const spv_instruction_t* inst,
                                 const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType) {
    DIAG(resultTypeIndex) << "OpLoad Result Type <id> '"
                          << inst->words[resultTypeIndex] << "' is not defind.";
    return false;
  }
  const bool uses_variable_pointer =
      module_.features().variable_pointers ||
      module_.features().variable_pointers_storage_buffer;
  auto pointerIndex = 3;
  auto pointer = module_.FindDef(inst->words[pointerIndex]);
  if (!pointer ||
      (addressingModel == SpvAddressingModelLogical &&
       ((!uses_variable_pointer &&
         !spvOpcodeReturnsLogicalPointer(pointer->opcode())) ||
        (uses_variable_pointer &&
         !spvOpcodeReturnsLogicalVariablePointer(pointer->opcode()))))) {
    DIAG(pointerIndex) << "OpLoad Pointer <id> '" << inst->words[pointerIndex]
                       << "' is not a logical pointer.";
    return false;
  }
  auto pointerType = module_.FindDef(pointer->type_id());
  if (!pointerType || pointerType->opcode() != SpvOpTypePointer) {
    DIAG(pointerIndex) << "OpLoad type for pointer <id> '"
                       << inst->words[pointerIndex]
                       << "' is not a pointer type.";
    return false;
  }
  auto pointeeType = module_.FindDef(pointerType->words()[3]);
  if (!pointeeType || resultType->id() != pointeeType->id()) {
    DIAG(resultTypeIndex) << "OpLoad Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' does not match Pointer <id> '" << pointer->id()
                          << "'s type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpStore>(const spv_instruction_t* inst,
                                  const spv_opcode_desc) {
  const bool uses_variable_pointer =
      module_.features().variable_pointers ||
      module_.features().variable_pointers_storage_buffer;
  const auto pointerIndex = 1;
  auto pointer = module_.FindDef(inst->words[pointerIndex]);
  if (!pointer ||
      (addressingModel == SpvAddressingModelLogical &&
       ((!uses_variable_pointer &&
         !spvOpcodeReturnsLogicalPointer(pointer->opcode())) ||
        (uses_variable_pointer &&
         !spvOpcodeReturnsLogicalVariablePointer(pointer->opcode()))))) {
    DIAG(pointerIndex) << "OpStore Pointer <id> '" << inst->words[pointerIndex]
                       << "' is not a logical pointer.";
    return false;
  }
  auto pointerType = module_.FindDef(pointer->type_id());
  if (!pointer || pointerType->opcode() != SpvOpTypePointer) {
    DIAG(pointerIndex) << "OpStore type for pointer <id> '"
                       << inst->words[pointerIndex]
                       << "' is not a pointer type.";
    return false;
  }
  auto type = module_.FindDef(pointerType->words()[3]);
  assert(type);
  if (SpvOpTypeVoid == type->opcode()) {
    DIAG(pointerIndex) << "OpStore Pointer <id> '" << inst->words[pointerIndex]
                       << "'s type is void.";
    return false;
  }

  // validate storage class
  {
    uint32_t dataType;
    uint32_t storageClass;
    if (!module_.GetPointerTypeInfo(pointerType->id(), &dataType,
                                    &storageClass)) {
      DIAG(pointerIndex) << "OpStore Pointer <id> '"
                         << inst->words[pointerIndex]
                         << "' is not pointer type";
      return false;
    }

    if (storageClass == SpvStorageClassUniformConstant ||
        storageClass == SpvStorageClassInput ||
        storageClass == SpvStorageClassPushConstant) {
      DIAG(pointerIndex) << "OpStore Pointer <id> '"
                         << inst->words[pointerIndex]
                         << "' storage class is read-only";
      return false;
    }
  }

  auto objectIndex = 2;
  auto object = module_.FindDef(inst->words[objectIndex]);
  if (!object || !object->type_id()) {
    DIAG(objectIndex) << "OpStore Object <id> '" << inst->words[objectIndex]
                      << "' is not an object.";
    return false;
  }
  auto objectType = module_.FindDef(object->type_id());
  assert(objectType);
  if (SpvOpTypeVoid == objectType->opcode()) {
    DIAG(objectIndex) << "OpStore Object <id> '" << inst->words[objectIndex]
                      << "'s type is void.";
    return false;
  }

  if (type->id() != objectType->id()) {
    if (!module_.options()->relax_struct_store ||
        type->opcode() != SpvOpTypeStruct ||
        objectType->opcode() != SpvOpTypeStruct) {
      DIAG(pointerIndex) << "OpStore Pointer <id> '"
                         << inst->words[pointerIndex]
                         << "'s type does not match Object <id> '"
                         << object->id() << "'s type.";
      return false;
    }

    // TODO: Check for layout compatible matricies and arrays as well.
    if (!AreLayoutCompatibleStructs(type, objectType)) {
      DIAG(pointerIndex) << "OpStore Pointer <id> '"
                         << inst->words[pointerIndex]
                         << "'s layout does not match Object <id> '"
                         << object->id() << "'s layout.";
      return false;
    }
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpCopyMemory>(const spv_instruction_t* inst,
                                       const spv_opcode_desc) {
  auto targetIndex = 1;
  auto target = module_.FindDef(inst->words[targetIndex]);
  if (!target) return false;
  auto sourceIndex = 2;
  auto source = module_.FindDef(inst->words[sourceIndex]);
  if (!source) return false;
  auto targetPointerType = module_.FindDef(target->type_id());
  assert(targetPointerType);
  auto targetType = module_.FindDef(targetPointerType->words()[3]);
  assert(targetType);
  auto sourcePointerType = module_.FindDef(source->type_id());
  assert(sourcePointerType);
  auto sourceType = module_.FindDef(sourcePointerType->words()[3]);
  assert(sourceType);
  if (targetType->id() != sourceType->id()) {
    DIAG(sourceIndex) << "OpCopyMemory Target <id> '"
                      << inst->words[sourceIndex]
                      << "'s type does not match Source <id> '"
                      << sourceType->id() << "'s type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpCopyMemorySized>(const spv_instruction_t* inst,
                                            const spv_opcode_desc) {
  auto targetIndex = 1;
  auto target = module_.FindDef(inst->words[targetIndex]);
  if (!target) return false;
  auto sourceIndex = 2;
  auto source = module_.FindDef(inst->words[sourceIndex]);
  if (!source) return false;
  auto sizeIndex = 3;
  auto size = module_.FindDef(inst->words[sizeIndex]);
  if (!size) return false;
  auto targetPointerType = module_.FindDef(target->type_id());
  if (!targetPointerType || SpvOpTypePointer != targetPointerType->opcode()) {
    DIAG(targetIndex) << "OpCopyMemorySized Target <id> '"
                      << inst->words[targetIndex] << "' is not a pointer.";
    return false;
  }
  auto sourcePointerType = module_.FindDef(source->type_id());
  if (!sourcePointerType || SpvOpTypePointer != sourcePointerType->opcode()) {
    DIAG(sourceIndex) << "OpCopyMemorySized Source <id> '"
                      << inst->words[sourceIndex] << "' is not a pointer.";
    return false;
  }
  switch (size->opcode()) {
    // TODO: The following opcode's are assumed to be valid, refer to the
    // following bug https://cvs.khronos.org/bugzilla/show_bug.cgi?id=13871 for
    // clarification
    case SpvOpConstant:
    case SpvOpSpecConstant: {
      auto sizeType = module_.FindDef(size->type_id());
      assert(sizeType);
      if (SpvOpTypeInt != sizeType->opcode()) {
        DIAG(sizeIndex) << "OpCopyMemorySized Size <id> '"
                        << inst->words[sizeIndex]
                        << "'s type is not an integer type.";
        return false;
      }
    } break;
    case SpvOpVariable: {
      auto pointerType = module_.FindDef(size->type_id());
      assert(pointerType);
      auto sizeType = module_.FindDef(pointerType->type_id());
      if (!sizeType || SpvOpTypeInt != sizeType->opcode()) {
        DIAG(sizeIndex) << "OpCopyMemorySized Size <id> '"
                        << inst->words[sizeIndex]
                        << "'s variable type is not an integer type.";
        return false;
      }
    } break;
    default:
      DIAG(sizeIndex) << "OpCopyMemorySized Size <id> '"
                      << inst->words[sizeIndex]
                      << "' is not a constant or variable.";
      return false;
  }
  // TODO: Check that consant is a least size 1, see the same bug as above for
  // clarification?
  return true;
}

template <>
bool idUsage::isValid<SpvOpAccessChain>(const spv_instruction_t* inst,
                                        const spv_opcode_desc) {
  std::string instr_name =
      "Op" + std::string(spvOpcodeString(static_cast<SpvOp>(inst->opcode)));

  // The result type must be OpTypePointer. Result Type is at word 1.
  auto resultTypeIndex = 1;
  auto resultTypeInstr = module_.FindDef(inst->words[resultTypeIndex]);
  if (SpvOpTypePointer != resultTypeInstr->opcode()) {
    DIAG(resultTypeIndex) << "The Result Type of " << instr_name << " <id> '"
                          << inst->words[2]
                          << "' must be OpTypePointer. Found Op"
                          << spvOpcodeString(
                                 static_cast<SpvOp>(resultTypeInstr->opcode()))
                          << ".";
    return false;
  }

  // Result type is a pointer. Find out what it's pointing to.
  // This will be used to make sure the indexing results in the same type.
  // OpTypePointer word 3 is the type being pointed to.
  auto resultTypePointedTo = module_.FindDef(resultTypeInstr->word(3));

  // Base must be a pointer, pointing to the base of a composite object.
  auto baseIdIndex = 3;
  auto baseInstr = module_.FindDef(inst->words[baseIdIndex]);
  auto baseTypeInstr = module_.FindDef(baseInstr->type_id());
  if (!baseTypeInstr || SpvOpTypePointer != baseTypeInstr->opcode()) {
    DIAG(baseIdIndex) << "The Base <id> '" << inst->words[baseIdIndex]
                      << "' in " << instr_name
                      << " instruction must be a pointer.";
    return false;
  }

  // The result pointer storage class and base pointer storage class must match.
  // Word 2 of OpTypePointer is the Storage Class.
  auto resultTypeStorageClass = resultTypeInstr->word(2);
  auto baseTypeStorageClass = baseTypeInstr->word(2);
  if (resultTypeStorageClass != baseTypeStorageClass) {
    DIAG(resultTypeIndex) << "The result pointer storage class and base "
                             "pointer storage class in "
                          << instr_name << " do not match.";
    return false;
  }

  // The type pointed to by OpTypePointer (word 3) must be a composite type.
  auto typePointedTo = module_.FindDef(baseTypeInstr->word(3));

  // Check Universal Limit (SPIR-V Spec. Section 2.17).
  // The number of indexes passed to OpAccessChain may not exceed 255
  // The instruction includes 4 words + N words (for N indexes)
  const size_t num_indexes = inst->words.size() - 4;
  const size_t num_indexes_limit =
      module_.options()->universal_limits_.max_access_chain_indexes;
  if (num_indexes > num_indexes_limit) {
    DIAG(resultTypeIndex) << "The number of indexes in " << instr_name
                          << " may not exceed " << num_indexes_limit
                          << ". Found " << num_indexes << " indexes.";
    return false;
  }
  // Indexes walk the type hierarchy to the desired depth, potentially down to
  // scalar granularity. The first index in Indexes will select the top-level
  // member/element/component/element of the base composite. All composite
  // constituents use zero-based numbering, as described by their OpType...
  // instruction. The second index will apply similarly to that result, and so
  // on. Once any non-composite type is reached, there must be no remaining
  // (unused) indexes.
  for (size_t i = 4; i < inst->words.size(); ++i) {
    const uint32_t cur_word = inst->words[i];
    // Earlier ID checks ensure that cur_word definition exists.
    auto cur_word_instr = module_.FindDef(cur_word);
    // The index must be a scalar integer type (See OpAccessChain in the Spec.)
    auto indexTypeInstr = module_.FindDef(cur_word_instr->type_id());
    if (!indexTypeInstr || SpvOpTypeInt != indexTypeInstr->opcode()) {
      DIAG(i) << "Indexes passed to " << instr_name
              << " must be of type integer.";
      return false;
    }
    switch (typePointedTo->opcode()) {
      case SpvOpTypeMatrix:
      case SpvOpTypeVector:
      case SpvOpTypeArray:
      case SpvOpTypeRuntimeArray: {
        // In OpTypeMatrix, OpTypeVector, OpTypeArray, and OpTypeRuntimeArray,
        // word 2 is the Element Type.
        typePointedTo = module_.FindDef(typePointedTo->word(2));
        break;
      }
      case SpvOpTypeStruct: {
        // In case of structures, there is an additional constraint on the
        // index: the index must be an OpConstant.
        if (SpvOpConstant != cur_word_instr->opcode()) {
          DIAG(i) << "The <id> passed to " << instr_name
                  << " to index into a "
                     "structure must be an OpConstant.";
          return false;
        }
        // Get the index value from the OpConstant (word 3 of OpConstant).
        // OpConstant could be a signed integer. But it's okay to treat it as
        // unsigned because a negative constant int would never be seen as
        // correct as a struct offset, since structs can't have more than 2
        // billion members.
        const uint32_t cur_index = cur_word_instr->word(3);
        // The index points to the struct member we want, therefore, the index
        // should be less than the number of struct members.
        const uint32_t num_struct_members =
            static_cast<uint32_t>(typePointedTo->words().size() - 2);
        if (cur_index >= num_struct_members) {
          DIAG(i) << "Index is out of bounds: " << instr_name
                  << " can not find index " << cur_index
                  << " into the structure <id> '" << typePointedTo->id()
                  << "'. This structure has " << num_struct_members
                  << " members. Largest valid index is "
                  << num_struct_members - 1 << ".";
          return false;
        }
        // Struct members IDs start at word 2 of OpTypeStruct.
        auto structMemberId = typePointedTo->word(cur_index + 2);
        typePointedTo = module_.FindDef(structMemberId);
        break;
      }
      default: {
        // Give an error. reached non-composite type while indexes still remain.
        DIAG(i) << instr_name
                << " reached non-composite type while indexes "
                   "still remain to be traversed.";
        return false;
      }
    }
  }
  // At this point, we have fully walked down from the base using the indeces.
  // The type being pointed to should be the same as the result type.
  if (typePointedTo->id() != resultTypePointedTo->id()) {
    DIAG(resultTypeIndex)
        << instr_name << " result type (Op"
        << spvOpcodeString(static_cast<SpvOp>(resultTypePointedTo->opcode()))
        << ") does not match the type that results from indexing into the base "
           "<id> (Op"
        << spvOpcodeString(static_cast<SpvOp>(typePointedTo->opcode())) << ").";
    return false;
  }

  return true;
}

template <>
bool idUsage::isValid<SpvOpInBoundsAccessChain>(
    const spv_instruction_t* inst, const spv_opcode_desc opcodeEntry) {
  return isValid<SpvOpAccessChain>(inst, opcodeEntry);
}

template <>
bool idUsage::isValid<SpvOpPtrAccessChain>(const spv_instruction_t* inst,
                                           const spv_opcode_desc opcodeEntry) {
  // OpPtrAccessChain's validation rules are similar to OpAccessChain, with one
  // difference: word 4 must be id of an integer (Element <id>).
  // The grammar guarantees that there are at least 5 words in the instruction
  // (i.e. if there are fewer than 5 words, the SPIR-V code will not compile.)
  int elem_index = 4;
  // We can remove the Element <id> from the instruction words, and simply call
  // the validation code of OpAccessChain.
  spv_instruction_t new_inst = *inst;
  new_inst.words.erase(new_inst.words.begin() + elem_index);
  return isValid<SpvOpAccessChain>(&new_inst, opcodeEntry);
}

template <>
bool idUsage::isValid<SpvOpInBoundsPtrAccessChain>(
    const spv_instruction_t* inst, const spv_opcode_desc opcodeEntry) {
  // Has the same validation rules as OpPtrAccessChain
  return isValid<SpvOpPtrAccessChain>(inst, opcodeEntry);
}

#if 0
template <>
bool idUsage::isValid<SpvOpArrayLength>(const spv_instruction_t *inst,
                                        const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<SpvOpImagePointer>(const spv_instruction_t *inst,
                                         const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<SpvOpGenericPtrMemSemantics>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

template <>
bool idUsage::isValid<SpvOpFunction>(const spv_instruction_t* inst,
                                     const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType) return false;
  auto functionTypeIndex = 4;
  auto functionType = module_.FindDef(inst->words[functionTypeIndex]);
  if (!functionType || SpvOpTypeFunction != functionType->opcode()) {
    DIAG(functionTypeIndex)
        << "OpFunction Function Type <id> '" << inst->words[functionTypeIndex]
        << "' is not a function type.";
    return false;
  }
  auto returnType = module_.FindDef(functionType->words()[2]);
  assert(returnType);
  if (returnType->id() != resultType->id()) {
    DIAG(resultTypeIndex) << "OpFunction Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' does not match the Function Type <id> '"
                          << resultType->id() << "'s return type.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpFunctionParameter>(const spv_instruction_t* inst,
                                              const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType) return false;
  // NOTE: Find OpFunction & ensure OpFunctionParameter is not out of place.
  size_t paramIndex = 0;
  assert(firstInst < inst && "Invalid instruction pointer");
  while (firstInst != --inst) {
    if (SpvOpFunction == inst->opcode) {
      break;
    } else if (SpvOpFunctionParameter == inst->opcode) {
      paramIndex++;
    }
  }
  auto functionType = module_.FindDef(inst->words[4]);
  assert(functionType);
  if (paramIndex >= functionType->words().size() - 3) {
    DIAG(0) << "Too many OpFunctionParameters for " << inst->words[2]
            << ": expected " << functionType->words().size() - 3
            << " based on the function's type";
    return false;
  }
  auto paramType = module_.FindDef(functionType->words()[paramIndex + 3]);
  assert(paramType);
  if (resultType->id() != paramType->id()) {
    DIAG(resultTypeIndex) << "OpFunctionParameter Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "' does not match the OpTypeFunction parameter "
                             "type of the same index.";
    return false;
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpFunctionCall>(const spv_instruction_t* inst,
                                         const spv_opcode_desc) {
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType) return false;
  auto functionIndex = 3;
  auto function = module_.FindDef(inst->words[functionIndex]);
  if (!function || SpvOpFunction != function->opcode()) {
    DIAG(functionIndex) << "OpFunctionCall Function <id> '"
                        << inst->words[functionIndex] << "' is not a function.";
    return false;
  }
  auto returnType = module_.FindDef(function->type_id());
  assert(returnType);
  if (returnType->id() != resultType->id()) {
    DIAG(resultTypeIndex) << "OpFunctionCall Result Type <id> '"
                          << inst->words[resultTypeIndex]
                          << "'s type does not match Function <id> '"
                          << returnType->id() << "'s return type.";
    return false;
  }
  auto functionType = module_.FindDef(function->words()[4]);
  assert(functionType);
  auto functionCallArgCount = inst->words.size() - 4;
  auto functionParamCount = functionType->words().size() - 3;
  if (functionParamCount != functionCallArgCount) {
    DIAG(inst->words.size() - 1)
        << "OpFunctionCall Function <id>'s parameter count does not match "
           "the argument count.";
    return false;
  }
  for (size_t argumentIndex = 4, paramIndex = 3;
       argumentIndex < inst->words.size(); argumentIndex++, paramIndex++) {
    auto argument = module_.FindDef(inst->words[argumentIndex]);
    if (!argument) return false;
    auto argumentType = module_.FindDef(argument->type_id());
    assert(argumentType);
    auto parameterType = module_.FindDef(functionType->words()[paramIndex]);
    assert(parameterType);
    if (argumentType->id() != parameterType->id()) {
      DIAG(argumentIndex) << "OpFunctionCall Argument <id> '"
                          << inst->words[argumentIndex]
                          << "'s type does not match Function <id> '"
                          << parameterType->id() << "'s parameter type.";
      return false;
    }
  }
  return true;
}

template <>
bool idUsage::isValid<SpvOpVectorShuffle>(const spv_instruction_t* inst,
                                          const spv_opcode_desc) {
  auto instr_name = [&inst]() {
    std::string name =
        "Op" + std::string(spvOpcodeString(static_cast<SpvOp>(inst->opcode)));
    return name;
  };

  // Result Type must be an OpTypeVector.
  auto resultTypeIndex = 1;
  auto resultType = module_.FindDef(inst->words[resultTypeIndex]);
  if (!resultType || resultType->opcode() != SpvOpTypeVector) {
    DIAG(resultTypeIndex) << "The Result Type of " << instr_name()
                          << " must be OpTypeVector. Found Op"
                          << spvOpcodeString(
                                 static_cast<SpvOp>(resultType->opcode()))
                          << ".";
    return false;
  }

  // The number of components in Result Type must be the same as the number of
  // Component operands.
  auto componentCount = inst->words.size() - 5;
  auto vectorComponentCountIndex = 3;
  auto resultVectorDimension = resultType->words()[vectorComponentCountIndex];
  if (componentCount != resultVectorDimension) {
    DIAG(inst->words.size() - 1)
        << instr_name()
        << " component literals count does not match "
           "Result Type <id> '"
        << resultType->id() << "'s vector component count.";
    return false;
  }

  // Vector 1 and Vector 2 must both have vector types, with the same Component
  // Type as Result Type.
  auto vector1Index = 3;
  auto vector1Object = module_.FindDef(inst->words[vector1Index]);
  auto vector1Type = module_.FindDef(vector1Object->type_id());
  auto vector2Index = 4;
  auto vector2Object = module_.FindDef(inst->words[vector2Index]);
  auto vector2Type = module_.FindDef(vector2Object->type_id());
  if (!vector1Type || vector1Type->opcode() != SpvOpTypeVector) {
    DIAG(vector1Index) << "The type of Vector 1 must be OpTypeVector.";
    return false;
  }
  if (!vector2Type || vector2Type->opcode() != SpvOpTypeVector) {
    DIAG(vector2Index) << "The type of Vector 2 must be OpTypeVector.";
    return false;
  }
  auto vectorComponentTypeIndex = 2;
  auto resultComponentType = resultType->words()[vectorComponentTypeIndex];
  auto vector1ComponentType = vector1Type->words()[vectorComponentTypeIndex];
  if (vector1ComponentType != resultComponentType) {
    DIAG(vector1Index) << "The Component Type of Vector 1 must be the same "
                          "as ResultType.";
    return false;
  }
  auto vector2ComponentType = vector2Type->words()[vectorComponentTypeIndex];
  if (vector2ComponentType != resultComponentType) {
    DIAG(vector2Index) << "The Component Type of Vector 2 must be the same "
                          "as ResultType.";
    return false;
  }

  // All Component literals must either be FFFFFFFF or in [0, N - 1].
  auto vector1ComponentCount = vector1Type->words()[vectorComponentCountIndex];
  auto vector2ComponentCount = vector2Type->words()[vectorComponentCountIndex];
  auto N = vector1ComponentCount + vector2ComponentCount;
  auto firstLiteralIndex = 5;
  for (size_t i = firstLiteralIndex; i < inst->words.size(); ++i) {
    auto literal = inst->words[i];
    if (literal != 0xFFFFFFFF && literal >= N) {
      DIAG(i) << "Component literal value " << literal << " is greater than "
              << N - 1 << ".";
      return false;
    }
  }

  return true;
}

template <>
bool idUsage::isValid<SpvOpPhi>(const spv_instruction_t* inst,
                                const spv_opcode_desc /*opcodeEntry*/) {
  auto thisInst = module_.FindDef(inst->words[2]);
  SpvOp typeOp = module_.GetIdOpcode(thisInst->type_id());
  if (!spvOpcodeGeneratesType(typeOp)) {
    DIAG(0) << "OpPhi's type <id> " << module_.getIdName(thisInst->type_id())
            << " is not a type instruction.";
    return false;
  }

  auto block = thisInst->block();
  size_t numInOps = inst->words.size() - 3;
  if (numInOps % 2 != 0) {
    DIAG(0) << "OpPhi does not have an equal number of incoming values and "
               "basic blocks.";
    return false;
  }

  // Create a uniqued vector of predecessor ids for comparison against
  // incoming values. OpBranchConditional %cond %label %label produces two
  // predecessors in the CFG.
  std::vector<uint32_t> predIds;
  std::transform(block->predecessors()->begin(), block->predecessors()->end(),
                 std::back_inserter(predIds),
                 [](const libspirv::BasicBlock* b) { return b->id(); });
  std::sort(predIds.begin(), predIds.end());
  predIds.erase(std::unique(predIds.begin(), predIds.end()), predIds.end());

  size_t numEdges = numInOps / 2;
  if (numEdges != predIds.size()) {
    DIAG(0) << "OpPhi's number of incoming blocks (" << numEdges
            << ") does not match block's predecessor count ("
            << block->predecessors()->size() << ").";
    return false;
  }

  for (size_t i = 3; i < inst->words.size(); ++i) {
    auto incId = inst->words[i];
    if (i % 2 == 1) {
      // Incoming value type must match the phi result type.
      auto incTypeId = module_.GetTypeId(incId);
      if (thisInst->type_id() != incTypeId) {
        DIAG(i) << "OpPhi's result type <id> "
                << module_.getIdName(thisInst->type_id())
                << " does not match incoming value <id> "
                << module_.getIdName(incId) << " type <id> "
                << module_.getIdName(incTypeId) << ".";
        return false;
      }
    } else {
      if (module_.GetIdOpcode(incId) != SpvOpLabel) {
        DIAG(i) << "OpPhi's incoming basic block <id> "
                << module_.getIdName(incId) << " is not an OpLabel.";
        return false;
      }

      // Incoming basic block must be an immediate predecessor of the phi's
      // block.
      if (!std::binary_search(predIds.begin(), predIds.end(), incId)) {
        DIAG(i) << "OpPhi's incoming basic block <id> "
                << module_.getIdName(incId) << " is not a predecessor of <id> "
                << module_.getIdName(block->id()) << ".";
        return false;
      }
    }
  }

  return true;
}

#if 0
template <>
bool idUsage::isValid<OpLoopMerge>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpSelectionMerge>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpBranch>(const spv_instruction_t *inst,
                                const spv_opcode_desc opcodeEntry) {}
#endif

template <>
bool idUsage::isValid<SpvOpBranchConditional>(const spv_instruction_t* inst,
                                              const spv_opcode_desc) {
  const size_t numOperands = inst->words.size() - 1;
  const size_t condOperandIndex = 1;
  const size_t targetTrueIndex = 2;
  const size_t targetFalseIndex = 3;

  // num_operands is either 3 or 5 --- if 5, the last two need to be literal
  // integers
  if (numOperands != 3 && numOperands != 5) {
    DIAG(0) << "OpBranchConditional requires either 3 or 5 parameters";
    return false;
  }

  bool ret = true;

  // grab the condition operand and check that it is a bool
  const auto condOp = module_.FindDef(inst->words[condOperandIndex]);
  if (!condOp || !module_.IsBoolScalarType(condOp->type_id())) {
    DIAG(0)
        << "Condition operand for OpBranchConditional must be of boolean type";
    ret = false;
  }

  // target operands must be OpLabel
  // note that we don't need to check that the target labels are in the same
  // function,
  // PerformCfgChecks already checks for that
  const auto targetOpTrue = module_.FindDef(inst->words[targetTrueIndex]);
  if (!targetOpTrue || SpvOpLabel != targetOpTrue->opcode()) {
    DIAG(0) << "The 'True Label' operand for OpBranchConditional must be the "
               "ID of an OpLabel instruction";
    ret = false;
  }

  const auto targetOpFalse = module_.FindDef(inst->words[targetFalseIndex]);
  if (!targetOpFalse || SpvOpLabel != targetOpFalse->opcode()) {
    DIAG(0) << "The 'False Label' operand for OpBranchConditional must be the "
               "ID of an OpLabel instruction";
    ret = false;
  }

  return ret;
}

#if 0
template <>
bool idUsage::isValid<OpSwitch>(const spv_instruction_t *inst,
                                const spv_opcode_desc opcodeEntry) {}
#endif

template <>
bool idUsage::isValid<SpvOpReturnValue>(const spv_instruction_t* inst,
                                        const spv_opcode_desc) {
  auto valueIndex = 1;
  auto value = module_.FindDef(inst->words[valueIndex]);
  if (!value || !value->type_id()) {
    DIAG(valueIndex) << "OpReturnValue Value <id> '" << inst->words[valueIndex]
                     << "' does not represent a value.";
    return false;
  }
  auto valueType = module_.FindDef(value->type_id());
  if (!valueType || SpvOpTypeVoid == valueType->opcode()) {
    DIAG(valueIndex) << "OpReturnValue value's type <id> '" << value->type_id()
                     << "' is missing or void.";
    return false;
  }

  const bool uses_variable_pointer =
      module_.features().variable_pointers ||
      module_.features().variable_pointers_storage_buffer;

  if (addressingModel == SpvAddressingModelLogical &&
      SpvOpTypePointer == valueType->opcode() && !uses_variable_pointer &&
      !module_.options()->relax_logcial_pointer) {
    DIAG(valueIndex)
        << "OpReturnValue value's type <id> '" << value->type_id()
        << "' is a pointer, which is invalid in the Logical addressing model.";
    return false;
  }

  // NOTE: Find OpFunction
  const spv_instruction_t* function = inst - 1;
  while (firstInst != function) {
    if (SpvOpFunction == function->opcode) break;
    function--;
  }
  if (SpvOpFunction != function->opcode) {
    DIAG(valueIndex) << "OpReturnValue is not in a basic block.";
    return false;
  }
  auto returnType = module_.FindDef(function->words[1]);
  if (!returnType || returnType->id() != valueType->id()) {
    DIAG(valueIndex) << "OpReturnValue Value <id> '" << inst->words[valueIndex]
                     << "'s type does not match OpFunction's return type.";
    return false;
  }
  return true;
}

#if 0
template <>
bool idUsage::isValid<OpLifetimeStart>(const spv_instruction_t *inst,
                                       const spv_opcode_desc opcodeEntry) {
}
#endif

#if 0
template <>
bool idUsage::isValid<OpLifetimeStop>(const spv_instruction_t *inst,
                                      const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicInit>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicLoad>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicStore>(const spv_instruction_t *inst,
                                     const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicExchange>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicCompareExchange>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicCompareExchangeWeak>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicIIncrement>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicIDecrement>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicIAdd>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicISub>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicUMin>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicUMax>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicAnd>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicOr>(const spv_instruction_t *inst,
                                  const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicXor>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicIMin>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpAtomicIMax>(const spv_instruction_t *inst,
                                    const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpEmitStreamVertex>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpEndStreamPrimitive>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupAsyncCopy>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupWaitEvents>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupAll>(const spv_instruction_t *inst,
                                  const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupAny>(const spv_instruction_t *inst,
                                  const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupBroadcast>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupIAdd>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupFAdd>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupFMin>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupUMin>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupSMin>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupFMax>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupUMax>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupSMax>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpEnqueueMarker>(const spv_instruction_t *inst,
                                       const spv_opcode_desc opcodeEntry) {
}
#endif

#if 0
template <>
bool idUsage::isValid<OpEnqueueKernel>(const spv_instruction_t *inst,
                                       const spv_opcode_desc opcodeEntry) {
}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetKernelNDrangeSubGroupCount>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetKernelNDrangeMaxSubGroupSize>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetKernelWorkGroupSize>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetKernelPreferredWorkGroupSizeMultiple>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpRetainEvent>(const spv_instruction_t *inst,
                                     const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReleaseEvent>(const spv_instruction_t *inst,
                                      const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpCreateUserEvent>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpIsValidEvent>(const spv_instruction_t *inst,
                                      const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpSetUserEventStatus>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpCaptureEventProfilingInfo>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetDefaultQueue>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpBuildNDRange>(const spv_instruction_t *inst,
                                      const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReadPipe>(const spv_instruction_t *inst,
                                  const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpWritePipe>(const spv_instruction_t *inst,
                                   const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReservedReadPipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReservedWritePipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReserveReadPipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpReserveWritePipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpCommitReadPipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpCommitWritePipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpIsValidReserveId>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetNumPipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGetMaxPipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupReserveReadPipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupReserveWritePipePackets>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupCommitReadPipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#if 0
template <>
bool idUsage::isValid<OpGroupCommitWritePipe>(
    const spv_instruction_t *inst, const spv_opcode_desc opcodeEntry) {}
#endif

#undef DIAG

bool idUsage::isValid(const spv_instruction_t* inst) {
  spv_opcode_desc opcodeEntry = nullptr;
  if (spvOpcodeTableValueLookup(targetEnv, opcodeTable, inst->opcode,
                                &opcodeEntry))
    return false;
#define CASE(OpCode) \
  case Spv##OpCode:  \
    return isValid<Spv##OpCode>(inst, opcodeEntry);
#define TODO(OpCode) \
  case Spv##OpCode:  \
    return true;
  switch (inst->opcode) {
    TODO(OpUndef)
    CASE(OpMemberName)
    CASE(OpLine)
    CASE(OpDecorate)
    CASE(OpMemberDecorate)
    CASE(OpDecorationGroup)
    CASE(OpGroupDecorate)
    CASE(OpGroupMemberDecorate)
    TODO(OpExtInst)
    CASE(OpEntryPoint)
    CASE(OpExecutionMode)
    CASE(OpTypeVector)
    CASE(OpTypeMatrix)
    CASE(OpTypeSampler)
    CASE(OpTypeArray)
    CASE(OpTypeRuntimeArray)
    CASE(OpTypeStruct)
    CASE(OpTypePointer)
    CASE(OpTypeFunction)
    CASE(OpTypePipe)
    CASE(OpConstantTrue)
    CASE(OpConstantFalse)
    CASE(OpConstantComposite)
    CASE(OpConstantSampler)
    CASE(OpConstantNull)
    CASE(OpSpecConstantTrue)
    CASE(OpSpecConstantFalse)
    CASE(OpSpecConstantComposite)
    CASE(OpSampledImage)
    TODO(OpSpecConstantOp)
    CASE(OpVariable)
    CASE(OpLoad)
    CASE(OpStore)
    CASE(OpCopyMemory)
    CASE(OpCopyMemorySized)
    CASE(OpAccessChain)
    CASE(OpInBoundsAccessChain)
    CASE(OpPtrAccessChain)
    CASE(OpInBoundsPtrAccessChain)
    TODO(OpArrayLength)
    TODO(OpGenericPtrMemSemantics)
    CASE(OpFunction)
    CASE(OpFunctionParameter)
    CASE(OpFunctionCall)
    // Conversion opcodes are validated in validate_conversion.cpp.
    CASE(OpVectorShuffle)
    // Other composite opcodes are validated in validate_composites.cpp.
    // Arithmetic opcodes are validated in validate_arithmetics.cpp.
    // Bitwise opcodes are validated in validate_bitwise.cpp.
    // Logical opcodes are validated in validate_logicals.cpp.
    // Derivative opcodes are validated in validate_derivatives.cpp.
    CASE(OpPhi)
    TODO(OpLoopMerge)
    TODO(OpSelectionMerge)
    TODO(OpBranch)
    CASE(OpBranchConditional)
    TODO(OpSwitch)
    CASE(OpReturnValue)
    TODO(OpLifetimeStart)
    TODO(OpLifetimeStop)
    TODO(OpAtomicLoad)
    TODO(OpAtomicStore)
    TODO(OpAtomicExchange)
    TODO(OpAtomicCompareExchange)
    TODO(OpAtomicCompareExchangeWeak)
    TODO(OpAtomicIIncrement)
    TODO(OpAtomicIDecrement)
    TODO(OpAtomicIAdd)
    TODO(OpAtomicISub)
    TODO(OpAtomicUMin)
    TODO(OpAtomicUMax)
    TODO(OpAtomicAnd)
    TODO(OpAtomicOr)
    TODO(OpAtomicSMin)
    TODO(OpAtomicSMax)
    TODO(OpEmitStreamVertex)
    TODO(OpEndStreamPrimitive)
    TODO(OpGroupAsyncCopy)
    TODO(OpGroupWaitEvents)
    TODO(OpGroupAll)
    TODO(OpGroupAny)
    TODO(OpGroupBroadcast)
    TODO(OpGroupIAdd)
    TODO(OpGroupFAdd)
    TODO(OpGroupFMin)
    TODO(OpGroupUMin)
    TODO(OpGroupSMin)
    TODO(OpGroupFMax)
    TODO(OpGroupUMax)
    TODO(OpGroupSMax)
    TODO(OpEnqueueMarker)
    TODO(OpEnqueueKernel)
    TODO(OpGetKernelNDrangeSubGroupCount)
    TODO(OpGetKernelNDrangeMaxSubGroupSize)
    TODO(OpGetKernelWorkGroupSize)
    TODO(OpGetKernelPreferredWorkGroupSizeMultiple)
    TODO(OpRetainEvent)
    TODO(OpReleaseEvent)
    TODO(OpCreateUserEvent)
    TODO(OpIsValidEvent)
    TODO(OpSetUserEventStatus)
    TODO(OpCaptureEventProfilingInfo)
    TODO(OpGetDefaultQueue)
    TODO(OpBuildNDRange)
    TODO(OpReadPipe)
    TODO(OpWritePipe)
    TODO(OpReservedReadPipe)
    TODO(OpReservedWritePipe)
    TODO(OpReserveReadPipePackets)
    TODO(OpReserveWritePipePackets)
    TODO(OpCommitReadPipe)
    TODO(OpCommitWritePipe)
    TODO(OpIsValidReserveId)
    TODO(OpGetNumPipePackets)
    TODO(OpGetMaxPipePackets)
    TODO(OpGroupReserveReadPipePackets)
    TODO(OpGroupReserveWritePipePackets)
    TODO(OpGroupCommitReadPipe)
    TODO(OpGroupCommitWritePipe)
    default:
      return true;
  }
#undef TODO
#undef CASE
}

bool idUsage::AreLayoutCompatibleStructs(const libspirv::Instruction* type1,
                                         const libspirv::Instruction* type2) {
  if (type1->opcode() != SpvOpTypeStruct) {
    return false;
  }
  if (type2->opcode() != SpvOpTypeStruct) {
    return false;
  }

  if (!HaveLayoutCompatibleMembers(type1, type2)) return false;

  return HaveSameLayoutDecorations(type1, type2);
}

bool idUsage::HaveLayoutCompatibleMembers(const libspirv::Instruction* type1,
                                          const libspirv::Instruction* type2) {
  assert(type1->opcode() == SpvOpTypeStruct &&
         "type1 must be and OpTypeStruct instruction.");
  assert(type2->opcode() == SpvOpTypeStruct &&
         "type2 must be and OpTypeStruct instruction.");
  const auto& type1_operands = type1->operands();
  const auto& type2_operands = type2->operands();
  if (type1_operands.size() != type2_operands.size()) {
    return false;
  }

  for (size_t operand = 2; operand < type1_operands.size(); ++operand) {
    if (type1->word(operand) != type2->word(operand)) {
      auto def1 = module_.FindDef(type1->word(operand));
      auto def2 = module_.FindDef(type2->word(operand));
      if (!AreLayoutCompatibleStructs(def1, def2)) {
        return false;
      }
    }
  }
  return true;
}

bool idUsage::HaveSameLayoutDecorations(const libspirv::Instruction* type1,
                                        const libspirv::Instruction* type2) {
  assert(type1->opcode() == SpvOpTypeStruct &&
         "type1 must be and OpTypeStruct instruction.");
  assert(type2->opcode() == SpvOpTypeStruct &&
         "type2 must be and OpTypeStruct instruction.");
  const std::vector<Decoration>& type1_decorations =
      module_.id_decorations(type1->id());
  const std::vector<Decoration>& type2_decorations =
      module_.id_decorations(type2->id());

  // TODO: Will have to add other check for arrays an matricies if we want to
  // handle them.
  if (HasConflictingMemberOffsets(type1_decorations, type2_decorations)) {
    return false;
  }

  return true;
}

bool idUsage::HasConflictingMemberOffsets(
    const vector<Decoration>& type1_decorations,
    const vector<Decoration>& type2_decorations) const {
  {
    // We are interested in conflicting decoration.  If a decoration is in one
    // list but not the other, then we will assume the code is correct.  We are
    // looking for things we know to be wrong.
    //
    // We do not have to traverse type2_decoration because, after traversing
    // type1_decorations, anything new will not be found in
    // type1_decoration.  Therefore, it cannot lead to a conflict.
    for (const Decoration& decoration : type1_decorations) {
      switch (decoration.dec_type()) {
        case SpvDecorationOffset: {
          // Since these affect the layout of the struct, they must be present
          // in both structs.
          auto compare = [&decoration](const Decoration& rhs) {
            if (rhs.dec_type() != SpvDecorationOffset) return false;
            return decoration.struct_member_index() ==
                   rhs.struct_member_index();
          };
          auto i = find_if(type2_decorations.begin(), type2_decorations.end(),
                           compare);
          if (i != type2_decorations.end() &&
              decoration.params().front() != i->params().front()) {
            return true;
          }
        } break;
        default:
          // This decoration does not affect the layout of the structure, so
          // just moving on.
          break;
      }
    }
  }
  return false;
}
}  // anonymous namespace

namespace libspirv {

spv_result_t UpdateIdUse(ValidationState_t& _) {
  for (const auto& inst : _.ordered_instructions()) {
    for (auto& operand : inst.operands()) {
      const spv_operand_type_t& type = operand.type;
      const uint32_t operand_id = inst.word(operand.offset);
      if (spvIsIdType(type) && type != SPV_OPERAND_TYPE_RESULT_ID) {
        if (auto def = _.FindDef(operand_id))
          def->RegisterUse(&inst, operand.offset);
      }
    }
  }
  return SPV_SUCCESS;
}

/// This function checks all ID definitions dominate their use in the CFG.
///
/// This function will iterate over all ID definitions that are defined in the
/// functions of a module and make sure that the definitions appear in a
/// block that dominates their use.
///
/// NOTE: This function does NOT check module scoped functions which are
/// checked during the initial binary parse in the IdPass below
spv_result_t CheckIdDefinitionDominateUse(const ValidationState_t& _) {
  unordered_set<const Instruction*> phi_instructions;
  for (const auto& definition : _.all_definitions()) {
    // Check only those definitions defined in a function
    if (const Function* func = definition.second->function()) {
      if (const BasicBlock* block = definition.second->block()) {
        if (!block->reachable()) continue;
        // If the Id is defined within a block then make sure all references to
        // that Id appear in a blocks that are dominated by the defining block
        for (auto& use_index_pair : definition.second->uses()) {
          const Instruction* use = use_index_pair.first;
          if (const BasicBlock* use_block = use->block()) {
            if (use_block->reachable() == false) continue;
            if (use->opcode() == SpvOpPhi) {
              phi_instructions.insert(use);
            } else if (!block->dominates(*use->block())) {
              return _.diag(SPV_ERROR_INVALID_ID)
                     << "ID " << _.getIdName(definition.first)
                     << " defined in block " << _.getIdName(block->id())
                     << " does not dominate its use in block "
                     << _.getIdName(use_block->id());
            }
          }
        }
      } else {
        // If the Ids defined within a function but not in a block(i.e. function
        // parameters, block ids), then make sure all references to that Id
        // appear within the same function
        for (auto use : definition.second->uses()) {
          const Instruction* inst = use.first;
          if (inst->function() && inst->function() != func) {
            return _.diag(SPV_ERROR_INVALID_ID)
                   << "ID " << _.getIdName(definition.first)
                   << " used in function "
                   << _.getIdName(inst->function()->id())
                   << " is used outside of it's defining function "
                   << _.getIdName(func->id());
          }
        }
      }
    }
    // NOTE: Ids defined outside of functions must appear before they are used
    // This check is being performed in the IdPass function
  }

  // Check all OpPhi parent blocks are dominated by the variable's defining
  // blocks
  for (const Instruction* phi : phi_instructions) {
    if (phi->block()->reachable() == false) continue;
    for (size_t i = 3; i < phi->operands().size(); i += 2) {
      const Instruction* variable = _.FindDef(phi->word(i));
      const BasicBlock* parent =
          phi->function()->GetBlock(phi->word(i + 1)).first;
      if (variable->block() && parent->reachable() &&
          !variable->block()->dominates(*parent)) {
        return _.diag(SPV_ERROR_INVALID_ID)
               << "In OpPhi instruction " << _.getIdName(phi->id()) << ", ID "
               << _.getIdName(variable->id())
               << " definition does not dominate its parent "
               << _.getIdName(parent->id());
      }
    }
  }

  return SPV_SUCCESS;
}

// Performs SSA validation on the IDs of an instruction. The
// can_have_forward_declared_ids  functor should return true if the
// instruction operand's ID can be forward referenced.
spv_result_t IdPass(ValidationState_t& _,
                    const spv_parsed_instruction_t* inst) {
  auto can_have_forward_declared_ids =
      spvOperandCanBeForwardDeclaredFunction(static_cast<SpvOp>(inst->opcode));

  // Keep track of a result id defined by this instruction.  0 means it
  // does not define an id.
  uint32_t result_id = 0;

  for (unsigned i = 0; i < inst->num_operands; i++) {
    const spv_parsed_operand_t& operand = inst->operands[i];
    const spv_operand_type_t& type = operand.type;
    // We only care about Id operands, which are a single word.
    const uint32_t operand_word = inst->words[operand.offset];

    auto ret = SPV_ERROR_INTERNAL;
    switch (type) {
      case SPV_OPERAND_TYPE_RESULT_ID:
        // NOTE: Multiple Id definitions are being checked by the binary parser.
        //
        // Defer undefined-forward-reference removal until after we've analyzed
        // the remaining operands to this instruction.  Deferral only matters
        // for
        // OpPhi since it's the only case where it defines its own forward
        // reference.  Other instructions that can have forward references
        // either don't define a value or the forward reference is to a function
        // Id (and hence defined outside of a function body).
        result_id = operand_word;
        // NOTE: The result Id is added (in RegisterInstruction) *after* all of
        // the other Ids have been checked to avoid premature use in the same
        // instruction.
        ret = SPV_SUCCESS;
        break;
      case SPV_OPERAND_TYPE_ID:
      case SPV_OPERAND_TYPE_TYPE_ID:
      case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID:
      case SPV_OPERAND_TYPE_SCOPE_ID:
        if (_.IsDefinedId(operand_word)) {
          ret = SPV_SUCCESS;
        } else if (can_have_forward_declared_ids(i)) {
          ret = _.ForwardDeclareId(operand_word);
        } else {
          ret = _.diag(SPV_ERROR_INVALID_ID)
                << "ID " << _.getIdName(operand_word)
                << " has not been defined";
        }
        break;
      default:
        ret = SPV_SUCCESS;
        break;
    }
    if (SPV_SUCCESS != ret) {
      return ret;
    }
  }
  if (result_id) {
    _.RemoveIfForwardDeclared(result_id);
  }
  _.RegisterInstruction(*inst);
  return SPV_SUCCESS;
}
}  // namespace libspirv

spv_result_t spvValidateInstructionIDs(const spv_instruction_t* pInsts,
                                       const uint64_t instCount,
                                       const libspirv::ValidationState_t& state,
                                       spv_position position) {
  idUsage idUsage(state.context(), pInsts, instCount, state.memory_model(),
                  state.addressing_model(), state, state.entry_points(),
                  position, state.context()->consumer);
  for (uint64_t instIndex = 0; instIndex < instCount; ++instIndex) {
    if (!idUsage.isValid(&pInsts[instIndex])) return SPV_ERROR_INVALID_ID;
    position->index += pInsts[instIndex].words.size();
  }
  return SPV_SUCCESS;
}

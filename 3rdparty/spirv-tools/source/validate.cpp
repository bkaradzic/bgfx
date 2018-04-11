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
#include <cstdio>

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "binary.h"
#include "diagnostic.h"
#include "enum_string_mapping.h"
#include "extensions.h"
#include "instruction.h"
#include "opcode.h"
#include "operand.h"
#include "spirv-tools/libspirv.h"
#include "spirv_constant.h"
#include "spirv_endian.h"
#include "spirv_target_env.h"
#include "spirv_validator_options.h"
#include "val/construct.h"
#include "val/function.h"
#include "val/validation_state.h"

using std::function;
using std::ostream_iterator;
using std::string;
using std::stringstream;
using std::transform;
using std::vector;
using std::placeholders::_1;

using libspirv::CfgPass;
using libspirv::DataRulesPass;
using libspirv::Extension;
using libspirv::IdPass;
using libspirv::InstructionPass;
using libspirv::LiteralsPass;
using libspirv::ModuleLayoutPass;
using libspirv::ValidationState_t;

spv_result_t spvValidateIDs(const spv_instruction_t* pInsts,
                            const uint64_t count,
                            const ValidationState_t& state,
                            spv_position position) {
  position->index = SPV_INDEX_INSTRUCTION;
  if (auto error = spvValidateInstructionIDs(pInsts, count, state, position))
    return error;
  return SPV_SUCCESS;
}

namespace {

// TODO(umar): Validate header
// TODO(umar): The binary parser validates the magic word, and the length of the
// header, but nothing else.
spv_result_t setHeader(void* user_data, spv_endianness_t endian, uint32_t magic,
                       uint32_t version, uint32_t generator, uint32_t id_bound,
                       uint32_t reserved) {
  // Record the ID bound so that the validator can ensure no ID is out of bound.
  ValidationState_t& _ = *(reinterpret_cast<ValidationState_t*>(user_data));
  _.setIdBound(id_bound);

  (void)endian;
  (void)magic;
  (void)version;
  (void)generator;
  (void)id_bound;
  (void)reserved;
  return SPV_SUCCESS;
}

// Improves diagnostic messages by collecting names of IDs
// NOTE: This function returns void and is not involved in validation
void DebugInstructionPass(ValidationState_t& _,
                          const spv_parsed_instruction_t* inst) {
  switch (inst->opcode) {
    case SpvOpName: {
      const uint32_t target = *(inst->words + inst->operands[0].offset);
      const char* str =
          reinterpret_cast<const char*>(inst->words + inst->operands[1].offset);
      _.AssignNameToId(target, str);
    } break;
    case SpvOpMemberName: {
      const uint32_t target = *(inst->words + inst->operands[0].offset);
      const char* str =
          reinterpret_cast<const char*>(inst->words + inst->operands[2].offset);
      _.AssignNameToId(target, str);
    } break;
    case SpvOpSourceContinued:
    case SpvOpSource:
    case SpvOpSourceExtension:
    case SpvOpString:
    case SpvOpLine:
    case SpvOpNoLine:

    default:
      break;
  }
}

// Parses OpExtension instruction and registers extension.
void RegisterExtension(ValidationState_t& _,
                       const spv_parsed_instruction_t* inst) {
  const std::string extension_str = libspirv::GetExtensionString(inst);
  Extension extension;
  if (!GetExtensionFromString(extension_str.c_str(), &extension)) {
    // The error will be logged in the ProcessInstruction pass.
    return;
  }

  _.RegisterExtension(extension);
}

// Parses the beginning of the module searching for OpExtension instructions.
// Registers extensions if recognized. Returns SPV_REQUESTED_TERMINATION
// once an instruction which is not SpvOpCapability and SpvOpExtension is
// encountered. According to the SPIR-V spec extensions are declared after
// capabilities and before everything else.
spv_result_t ProcessExtensions(void* user_data,
                               const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  if (opcode == SpvOpCapability) return SPV_SUCCESS;

  if (opcode == SpvOpExtension) {
    ValidationState_t& _ = *(reinterpret_cast<ValidationState_t*>(user_data));
    RegisterExtension(_, inst);
    return SPV_SUCCESS;
  }

  // OpExtension block is finished, requesting termination.
  return SPV_REQUESTED_TERMINATION;
}

spv_result_t ProcessInstruction(void* user_data,
                                const spv_parsed_instruction_t* inst) {
  ValidationState_t& _ = *(reinterpret_cast<ValidationState_t*>(user_data));
  _.increment_instruction_count();
  if (static_cast<SpvOp>(inst->opcode) == SpvOpEntryPoint) {
    const auto entry_point = inst->words[2];
    const SpvExecutionModel execution_model = SpvExecutionModel(inst->words[1]);
    _.RegisterEntryPointId(entry_point, execution_model);
    // Operand 3 and later are the <id> of interfaces for the entry point.
    for (int i = 3; i < inst->num_operands; ++i) {
      _.RegisterInterfaceForEntryPoint(entry_point,
                                       inst->words[inst->operands[i].offset]);
    }
  }
  if (static_cast<SpvOp>(inst->opcode) == SpvOpFunctionCall) {
    _.AddFunctionCallTarget(inst->words[3]);
  }

  DebugInstructionPass(_, inst);
  if (auto error = CapabilityPass(_, inst)) return error;
  if (auto error = DataRulesPass(_, inst)) return error;
  if (auto error = IdPass(_, inst)) return error;
  if (auto error = ModuleLayoutPass(_, inst)) return error;
  if (auto error = CfgPass(_, inst)) return error;
  if (auto error = InstructionPass(_, inst)) return error;
  if (auto error = TypeUniquePass(_, inst)) return error;
  if (auto error = ArithmeticsPass(_, inst)) return error;
  if (auto error = CompositesPass(_, inst)) return error;
  if (auto error = ConversionPass(_, inst)) return error;
  if (auto error = DerivativesPass(_, inst)) return error;
  if (auto error = LogicalsPass(_, inst)) return error;
  if (auto error = BitwisePass(_, inst)) return error;
  if (auto error = ExtInstPass(_, inst)) return error;
  if (auto error = ImagePass(_, inst)) return error;
  if (auto error = AtomicsPass(_, inst)) return error;
  if (auto error = BarriersPass(_, inst)) return error;
  if (auto error = PrimitivesPass(_, inst)) return error;
  if (auto error = LiteralsPass(_, inst)) return error;

  return SPV_SUCCESS;
}

void printDot(const ValidationState_t& _, const libspirv::BasicBlock& other) {
  string block_string;
  if (other.successors()->empty()) {
    block_string += "end ";
  } else {
    for (auto block : *other.successors()) {
      block_string += _.getIdOrName(block->id()) + " ";
    }
  }
  printf("%10s -> {%s\b}\n", _.getIdOrName(other.id()).c_str(),
         block_string.c_str());
}

void PrintBlocks(ValidationState_t& _, libspirv::Function func) {
  assert(func.first_block());

  printf("%10s -> %s\n", _.getIdOrName(func.id()).c_str(),
         _.getIdOrName(func.first_block()->id()).c_str());
  for (const auto& block : func.ordered_blocks()) {
    printDot(_, *block);
  }
}

#ifdef __clang__
#define UNUSED(func) [[gnu::unused]] func
#elif defined(__GNUC__)
#define UNUSED(func)            \
  func __attribute__((unused)); \
  func
#elif defined(_MSC_VER)
#define UNUSED(func) func
#endif

UNUSED(void PrintDotGraph(ValidationState_t& _, libspirv::Function func)) {
  if (func.first_block()) {
    string func_name(_.getIdOrName(func.id()));
    printf("digraph %s {\n", func_name.c_str());
    PrintBlocks(_, func);
    printf("}\n");
  }
}

spv_result_t ValidateBinaryUsingContextAndValidationState(
    const spv_context_t& context, const uint32_t* words, const size_t num_words,
    spv_diagnostic* pDiagnostic, ValidationState_t* vstate) {
  auto binary = std::unique_ptr<spv_const_binary_t>(
      new spv_const_binary_t{words, num_words});

  spv_endianness_t endian;
  spv_position_t position = {};
  if (spvBinaryEndianness(binary.get(), &endian)) {
    return libspirv::DiagnosticStream(position, context.consumer,
                                      SPV_ERROR_INVALID_BINARY)
           << "Invalid SPIR-V magic number.";
  }

  spv_header_t header;
  if (spvBinaryHeaderGet(binary.get(), endian, &header)) {
    return libspirv::DiagnosticStream(position, context.consumer,
                                      SPV_ERROR_INVALID_BINARY)
           << "Invalid SPIR-V header.";
  }

  if (header.version > spvVersionForTargetEnv(context.target_env)) {
    return libspirv::DiagnosticStream(position, context.consumer,
                                      SPV_ERROR_WRONG_VERSION)
           << "Invalid SPIR-V binary version "
           << SPV_SPIRV_VERSION_MAJOR_PART(header.version) << "."
           << SPV_SPIRV_VERSION_MINOR_PART(header.version)
           << " for target environment "
           << spvTargetEnvDescription(context.target_env) << ".";
  }

  // Look for OpExtension instructions and register extensions.
  // Diagnostics if any will be produced in the next pass (ProcessInstruction).
  spvBinaryParse(&context, vstate, words, num_words,
                 /* parsed_header = */ nullptr, ProcessExtensions,
                 /* diagnostic = */ nullptr);

  // NOTE: Parse the module and perform inline validation checks. These
  // checks do not require the the knowledge of the whole module.
  if (auto error = spvBinaryParse(&context, vstate, words, num_words, setHeader,
                                  ProcessInstruction, pDiagnostic))
    return error;

  if (vstate->in_function_body())
    return vstate->diag(SPV_ERROR_INVALID_LAYOUT)
           << "Missing OpFunctionEnd at end of module.";

  // TODO(umar): Add validation checks which require the parsing of the entire
  // module. Use the information from the ProcessInstruction pass to make the
  // checks.
  if (vstate->unresolved_forward_id_count() > 0) {
    stringstream ss;
    vector<uint32_t> ids = vstate->UnresolvedForwardIds();

    transform(begin(ids), end(ids), ostream_iterator<string>(ss, " "),
              bind(&ValidationState_t::getIdName, std::ref(*vstate), _1));

    auto id_str = ss.str();
    return vstate->diag(SPV_ERROR_INVALID_ID)
           << "The following forward referenced IDs have not been defined:\n"
           << id_str.substr(0, id_str.size() - 1);
  }

  // Validate the preconditions involving adjacent instructions. e.g. SpvOpPhi
  // must only be preceeded by SpvOpLabel, SpvOpPhi, or SpvOpLine.
  if (auto error = ValidateAdjacency(*vstate)) return error;

  // CFG checks are performed after the binary has been parsed
  // and the CFGPass has collected information about the control flow
  if (auto error = PerformCfgChecks(*vstate)) return error;
  if (auto error = UpdateIdUse(*vstate)) return error;
  if (auto error = CheckIdDefinitionDominateUse(*vstate)) return error;
  if (auto error = ValidateDecorations(*vstate)) return error;

  // Entry point validation. Based on 2.16.1 (Universal Validation Rules) of the
  // SPIRV spec:
  // * There is at least one OpEntryPoint instruction, unless the Linkage
  // capability is being used.
  // * No function can be targeted by both an OpEntryPoint instruction and an
  // OpFunctionCall instruction.
  if (vstate->entry_points().empty() &&
      !vstate->HasCapability(SpvCapabilityLinkage)) {
    return vstate->diag(SPV_ERROR_INVALID_BINARY)
           << "No OpEntryPoint instruction was found. This is only allowed if "
              "the Linkage capability is being used.";
  }
  for (const auto& entry_point : vstate->entry_points()) {
    if (vstate->IsFunctionCallTarget(entry_point)) {
      return vstate->diag(SPV_ERROR_INVALID_BINARY)
             << "A function (" << entry_point
             << ") may not be targeted by both an OpEntryPoint instruction and "
                "an OpFunctionCall instruction.";
    }
  }

  // NOTE: Copy each instruction for easier processing
  std::vector<spv_instruction_t> instructions;
  // Expect average instruction length to be a bit over 2 words.
  instructions.reserve(binary->wordCount / 2);
  uint64_t index = SPV_INDEX_INSTRUCTION;
  while (index < binary->wordCount) {
    uint16_t wordCount;
    uint16_t opcode;
    spvOpcodeSplit(spvFixWord(binary->code[index], endian), &wordCount,
                   &opcode);
    spv_instruction_t inst;
    spvInstructionCopy(&binary->code[index], static_cast<SpvOp>(opcode),
                       wordCount, endian, &inst);
    instructions.emplace_back(std::move(inst));
    index += wordCount;
  }

  position.index = SPV_INDEX_INSTRUCTION;
  if (auto error = spvValidateIDs(instructions.data(), instructions.size(),
                                  *vstate, &position))
    return error;

  if (auto error = ValidateBuiltIns(*vstate)) return error;

  return SPV_SUCCESS;
}
}  // anonymous namespace

spv_result_t spvValidate(const spv_const_context context,
                         const spv_const_binary binary,
                         spv_diagnostic* pDiagnostic) {
  return spvValidateBinary(context, binary->code, binary->wordCount,
                           pDiagnostic);
}

spv_result_t spvValidateBinary(const spv_const_context context,
                               const uint32_t* words, const size_t num_words,
                               spv_diagnostic* pDiagnostic) {
  spv_context_t hijack_context = *context;
  if (pDiagnostic) {
    *pDiagnostic = nullptr;
    libspirv::UseDiagnosticAsMessageConsumer(&hijack_context, pDiagnostic);
  }

  // This interface is used for default command line options.
  spv_validator_options default_options = spvValidatorOptionsCreate();

  // Create the ValidationState using the context and default options.
  ValidationState_t vstate(&hijack_context, default_options);

  spv_result_t result = ValidateBinaryUsingContextAndValidationState(
      hijack_context, words, num_words, pDiagnostic, &vstate);

  spvValidatorOptionsDestroy(default_options);
  return result;
}

spv_result_t spvValidateWithOptions(const spv_const_context context,
                                    spv_const_validator_options options,
                                    const spv_const_binary binary,
                                    spv_diagnostic* pDiagnostic) {
  spv_context_t hijack_context = *context;
  if (pDiagnostic) {
    *pDiagnostic = nullptr;
    libspirv::UseDiagnosticAsMessageConsumer(&hijack_context, pDiagnostic);
  }

  // Create the ValidationState using the context.
  ValidationState_t vstate(&hijack_context, options);

  return ValidateBinaryUsingContextAndValidationState(
      hijack_context, binary->code, binary->wordCount, pDiagnostic, &vstate);
}

namespace spvtools {

spv_result_t ValidateBinaryAndKeepValidationState(
    const spv_const_context context, spv_const_validator_options options,
    const uint32_t* words, const size_t num_words, spv_diagnostic* pDiagnostic,
    std::unique_ptr<ValidationState_t>* vstate) {
  spv_context_t hijack_context = *context;
  if (pDiagnostic) {
    *pDiagnostic = nullptr;
    libspirv::UseDiagnosticAsMessageConsumer(&hijack_context, pDiagnostic);
  }

  vstate->reset(new ValidationState_t(&hijack_context, options));

  return ValidateBinaryUsingContextAndValidationState(
      hijack_context, words, num_words, pDiagnostic, vstate->get());
}

spv_result_t ValidateInstructionAndUpdateValidationState(
    ValidationState_t* vstate, const spv_parsed_instruction_t* inst) {
  return ProcessInstruction(vstate, inst);
}

}  // namespace spvtools

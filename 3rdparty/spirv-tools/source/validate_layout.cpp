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

// Source code for logical layout validation as described in section 2.4

#include "validate.h"

#include <cassert>

#include "diagnostic.h"
#include "opcode.h"
#include "operand.h"
#include "spirv-tools/libspirv.h"
#include "val/function.h"
#include "val/validation_state.h"

using libspirv::FunctionDecl;
using libspirv::kLayoutFunctionDeclarations;
using libspirv::kLayoutFunctionDefinitions;
using libspirv::kLayoutMemoryModel;
using libspirv::ValidationState_t;

namespace {
// Module scoped instructions are processed by determining if the opcode
// is part of the current layout section. If it is not then the next sections is
// checked.
spv_result_t ModuleScopedInstructions(ValidationState_t& _,
                                      const spv_parsed_instruction_t* inst,
                                      SpvOp opcode) {
  while (_.IsOpcodeInCurrentLayoutSection(opcode) == false) {
    _.ProgressToNextLayoutSectionOrder();

    switch (_.current_layout_section()) {
      case kLayoutMemoryModel:
        if (opcode != SpvOpMemoryModel) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << spvOpcodeString(opcode)
                 << " cannot appear before the memory model instruction";
        }
        break;
      case kLayoutFunctionDeclarations:
        // All module sections have been processed. Recursively call
        // ModuleLayoutPass to process the next section of the module
        return libspirv::ModuleLayoutPass(_, inst);
      default:
        break;
    }
  }
  return SPV_SUCCESS;
}

// Function declaration validation is performed by making sure that the
// FunctionParameter and FunctionEnd instructions only appear inside of
// functions. It also ensures that the Function instruction does not appear
// inside of another function. This stage ends when the first label is
// encountered inside of a function.
spv_result_t FunctionScopedInstructions(ValidationState_t& _,
                                        const spv_parsed_instruction_t* inst,
                                        SpvOp opcode) {
  if (_.IsOpcodeInCurrentLayoutSection(opcode)) {
    switch (opcode) {
      case SpvOpFunction: {
        if (_.in_function_body()) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "Cannot declare a function in a function body";
        }
        auto control_mask = static_cast<SpvFunctionControlMask>(
            inst->words[inst->operands[2].offset]);
        if (auto error =
                _.RegisterFunction(inst->result_id, inst->type_id, control_mask,
                                   inst->words[inst->operands[3].offset]))
          return error;
        if (_.current_layout_section() == kLayoutFunctionDefinitions) {
          if (auto error = _.current_function().RegisterSetFunctionDeclType(
                  FunctionDecl::kFunctionDeclDefinition))
            return error;
        }
      } break;

      case SpvOpFunctionParameter:
        if (_.in_function_body() == false) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT) << "Function parameter "
                                                     "instructions must be in "
                                                     "a function body";
        }
        if (_.current_function().block_count() != 0) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "Function parameters must only appear immediately after "
                    "the function definition";
        }
        if (auto error = _.current_function().RegisterFunctionParameter(
                inst->result_id, inst->type_id))
          return error;
        break;

      case SpvOpFunctionEnd:
        if (_.in_function_body() == false) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "Function end instructions must be in a function body";
        }
        if (_.in_block()) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "Function end cannot be called in blocks";
        }
        if (_.current_function().block_count() == 0 &&
            _.current_layout_section() == kLayoutFunctionDefinitions) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT) << "Function declarations "
                                                     "must appear before "
                                                     "function definitions.";
        }
        if (_.current_layout_section() == kLayoutFunctionDeclarations) {
          if (auto error = _.current_function().RegisterSetFunctionDeclType(
                  FunctionDecl::kFunctionDeclDeclaration))
            return error;
        }
        if (auto error = _.RegisterFunctionEnd()) return error;
        break;

      case SpvOpLine:
      case SpvOpNoLine:
        break;
      case SpvOpLabel:
        // If the label is encountered then the current function is a
        // definition so set the function to a declaration and update the
        // module section
        if (_.in_function_body() == false) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "Label instructions must be in a function body";
        }
        if (_.in_block()) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "A block must end with a branch instruction.";
        }
        if (_.current_layout_section() == kLayoutFunctionDeclarations) {
          _.ProgressToNextLayoutSectionOrder();
          if (auto error = _.current_function().RegisterSetFunctionDeclType(
                  FunctionDecl::kFunctionDeclDefinition))
            return error;
        }
        break;

      default:
        if (_.current_layout_section() == kLayoutFunctionDeclarations &&
            _.in_function_body()) {
          return _.diag(SPV_ERROR_INVALID_LAYOUT)
                 << "A function must begin with a label";
        } else {
          if (_.in_block() == false) {
            return _.diag(SPV_ERROR_INVALID_LAYOUT)
                   << spvOpcodeString(opcode) << " must appear in a block";
          }
        }
        break;
    }
  } else {
    return _.diag(SPV_ERROR_INVALID_LAYOUT)
           << spvOpcodeString(opcode)
           << " cannot appear in a function declaration";
  }
  return SPV_SUCCESS;
}
}  // namespace

namespace libspirv {
// TODO(umar): Check linkage capabilities for function declarations
// TODO(umar): Better error messages
// NOTE: This function does not handle CFG related validation
// Performs logical layout validation. See Section 2.4
spv_result_t ModuleLayoutPass(ValidationState_t& _,
                              const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);

  switch (_.current_layout_section()) {
    case kLayoutCapabilities:
    case kLayoutExtensions:
    case kLayoutExtInstImport:
    case kLayoutMemoryModel:
    case kLayoutEntryPoint:
    case kLayoutExecutionMode:
    case kLayoutDebug1:
    case kLayoutDebug2:
    case kLayoutDebug3:
    case kLayoutAnnotations:
    case kLayoutTypes:
      if (auto error = ModuleScopedInstructions(_, inst, opcode)) return error;
      break;
    case kLayoutFunctionDeclarations:
    case kLayoutFunctionDefinitions:
      if (auto error = FunctionScopedInstructions(_, inst, opcode)) {
        return error;
      }
      break;
  }
  return SPV_SUCCESS;
}
}  // namespace libspirv

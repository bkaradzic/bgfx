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

// Ensures type declarations are unique unless allowed by the specification.

#include "validate.h"

#include "diagnostic.h"
#include "opcode.h"
#include "val/instruction.h"
#include "val/validation_state.h"

namespace libspirv {

// Validates that type declarations are unique, unless multiple declarations
// of the same data type are allowed by the specification.
// (see section 2.8 Types and Variables)
// Doesn't do anything if SPV_VAL_ignore_type_decl_unique was declared in the
// module.
spv_result_t TypeUniquePass(ValidationState_t& _,
                            const spv_parsed_instruction_t* inst) {
  if (_.HasExtension(Extension::kSPV_VALIDATOR_ignore_type_decl_unique))
    return SPV_SUCCESS;

  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);

  if (spvOpcodeGeneratesType(opcode)) {
    if (opcode == SpvOpTypeArray || opcode == SpvOpTypeRuntimeArray ||
        opcode == SpvOpTypeStruct) {
      // Duplicate declarations of aggregates are allowed.
      return SPV_SUCCESS;
    }

    if (inst->opcode == SpvOpTypePointer &&
        _.HasExtension(Extension::kSPV_KHR_variable_pointers)) {
      // Duplicate pointer types are allowed with this extension.
      return SPV_SUCCESS;
    }

    if (!_.RegisterUniqueTypeDeclaration(*inst)) {
      return _.diag(SPV_ERROR_INVALID_DATA)
             << "Duplicate non-aggregate type declarations are not allowed."
             << " Opcode: " << spvOpcodeString(SpvOp(inst->opcode))
             << " id: " << inst->result_id;
    }
  }

  return SPV_SUCCESS;
}

}  // namespace libspirv

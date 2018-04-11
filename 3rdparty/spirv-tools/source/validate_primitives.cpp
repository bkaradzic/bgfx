// Copyright (c) 2017 LunarG Inc.
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

// Validates correctness of primitive SPIR-V instructions.

#include "validate.h"

#include <string>

#include "diagnostic.h"
#include "opcode.h"
#include "val/instruction.h"
#include "val/validation_state.h"

namespace libspirv {

// Validates correctness of primitive instructions.
spv_result_t PrimitivesPass(ValidationState_t& _,
                            const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);

  switch (opcode) {
    case SpvOpEmitVertex:
    case SpvOpEndPrimitive:
    case SpvOpEmitStreamVertex:
    case SpvOpEndStreamPrimitive:
      _.current_function().RegisterExecutionModelLimitation(
          SpvExecutionModelGeometry,
          std::string(spvOpcodeString(opcode)) +
              " instructions require Geometry execution model");
      break;
    default:
      break;
  }

  switch (opcode) {
    case SpvOpEmitStreamVertex:
    case SpvOpEndStreamPrimitive: {
      const uint32_t stream_id = inst->words[1];
      const uint32_t stream_type = _.GetTypeId(stream_id);
      if (!_.IsIntScalarType(stream_type)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Stream to be int scalar";
      }

      const SpvOp stream_opcode = _.GetIdOpcode(stream_id);
      if (!spvOpcodeIsConstant(stream_opcode)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Stream to be constant instruction";
      }
    }

    default:
      break;
  }

  return SPV_SUCCESS;
}

}  // namespace libspirv

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

// Validates correctness of bitwise instructions.

#include "validate.h"

#include "diagnostic.h"
#include "opcode.h"
#include "val/instruction.h"
#include "val/validation_state.h"

namespace libspirv {

namespace {

// Returns operand word for given instruction and operand index.
// The operand is expected to only have one word.
inline uint32_t GetOperandWord(const spv_parsed_instruction_t* inst,
                               size_t operand_index) {
  assert(operand_index < inst->num_operands);
  const spv_parsed_operand_t& operand = inst->operands[operand_index];
  assert(operand.num_words == 1);
  return inst->words[operand.offset];
}

// Returns the type id of instruction operand at |operand_index|.
// The operand is expected to be an id.
inline uint32_t GetOperandTypeId(ValidationState_t& _,
                                 const spv_parsed_instruction_t* inst,
                                 size_t operand_index) {
  return _.GetTypeId(GetOperandWord(inst, operand_index));
}
}  // namespace

// Validates correctness of bitwise instructions.
spv_result_t BitwisePass(ValidationState_t& _,
                         const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  const uint32_t result_type = inst->type_id;

  switch (opcode) {
    case SpvOpShiftRightLogical:
    case SpvOpShiftRightArithmetic:
    case SpvOpShiftLeftLogical: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t result_dimension = _.GetDimension(result_type);
      const uint32_t base_type = GetOperandTypeId(_, inst, 2);
      const uint32_t shift_type = GetOperandTypeId(_, inst, 3);

      if (!base_type ||
          (!_.IsIntScalarType(base_type) && !_.IsIntVectorType(base_type)))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base to be int scalar or vector: "
               << spvOpcodeString(opcode);

      if (_.GetDimension(base_type) != result_dimension)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base to have the same dimension "
               << "as Result Type: " << spvOpcodeString(opcode);

      if (_.GetBitWidth(base_type) != _.GetBitWidth(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base to have the same bit width "
               << "as Result Type: " << spvOpcodeString(opcode);

      if (!shift_type ||
          (!_.IsIntScalarType(shift_type) && !_.IsIntVectorType(shift_type)))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Shift to be int scalar or vector: "
               << spvOpcodeString(opcode);

      if (_.GetDimension(shift_type) != result_dimension)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Shift to have the same dimension "
               << "as Result Type: " << spvOpcodeString(opcode);
      break;
    }

    case SpvOpBitwiseOr:
    case SpvOpBitwiseXor:
    case SpvOpBitwiseAnd:
    case SpvOpNot: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t result_dimension = _.GetDimension(result_type);
      const uint32_t result_bit_width = _.GetBitWidth(result_type);

      for (size_t operand_index = 2; operand_index < inst->num_operands;
           ++operand_index) {
        const uint32_t type_id = GetOperandTypeId(_, inst, operand_index);
        if (!type_id ||
            (!_.IsIntScalarType(type_id) && !_.IsIntVectorType(type_id)))
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Expected int scalar or vector as operand: "
                 << spvOpcodeString(opcode) << " operand index "
                 << operand_index;

        if (_.GetDimension(type_id) != result_dimension)
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Expected operands to have the same dimension "
                 << "as Result Type: " << spvOpcodeString(opcode)
                 << " operand index " << operand_index;

        if (_.GetBitWidth(type_id) != result_bit_width)
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Expected operands to have the same bit width "
                 << "as Result Type: " << spvOpcodeString(opcode)
                 << " operand index " << operand_index;
      }
      break;
    }

    case SpvOpBitFieldInsert: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t base_type = GetOperandTypeId(_, inst, 2);
      const uint32_t insert_type = GetOperandTypeId(_, inst, 3);
      const uint32_t offset_type = GetOperandTypeId(_, inst, 4);
      const uint32_t count_type = GetOperandTypeId(_, inst, 5);

      if (base_type != result_type)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base Type to be equal to Result Type: "
               << spvOpcodeString(opcode);

      if (insert_type != result_type)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Insert Type to be equal to Result Type: "
               << spvOpcodeString(opcode);

      if (!offset_type || !_.IsIntScalarType(offset_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Offset Type to be int scalar: "
               << spvOpcodeString(opcode);

      if (!count_type || !_.IsIntScalarType(count_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Count Type to be int scalar: "
               << spvOpcodeString(opcode);
      break;
    }

    case SpvOpBitFieldSExtract:
    case SpvOpBitFieldUExtract: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t base_type = GetOperandTypeId(_, inst, 2);
      const uint32_t offset_type = GetOperandTypeId(_, inst, 3);
      const uint32_t count_type = GetOperandTypeId(_, inst, 4);

      if (base_type != result_type)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base Type to be equal to Result Type: "
               << spvOpcodeString(opcode);

      if (!offset_type || !_.IsIntScalarType(offset_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Offset Type to be int scalar: "
               << spvOpcodeString(opcode);

      if (!count_type || !_.IsIntScalarType(count_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Count Type to be int scalar: "
               << spvOpcodeString(opcode);
      break;
    }

    case SpvOpBitReverse: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t base_type = GetOperandTypeId(_, inst, 2);

      if (base_type != result_type)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base Type to be equal to Result Type: "
               << spvOpcodeString(opcode);
      break;
    }

    case SpvOpBitCount: {
      if (!_.IsIntScalarType(result_type) && !_.IsIntVectorType(result_type))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected int scalar or vector type as Result Type: "
               << spvOpcodeString(opcode);

      const uint32_t base_type = GetOperandTypeId(_, inst, 2);
      if (!base_type ||
          (!_.IsIntScalarType(base_type) && !_.IsIntVectorType(base_type)))
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base Type to be int scalar or vector: "
               << spvOpcodeString(opcode);

      const uint32_t base_dimension = _.GetDimension(base_type);
      const uint32_t result_dimension = _.GetDimension(result_type);

      if (base_dimension != result_dimension)
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Expected Base dimension to be equal to Result Type "
                  "dimension: "
               << spvOpcodeString(opcode);
      break;
    }

    default:
      break;
  }

  return SPV_SUCCESS;
}

}  // namespace libspirv

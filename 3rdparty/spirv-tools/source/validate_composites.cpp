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

// Validates correctness of composite SPIR-V instructions.

#include "validate.h"

#include "diagnostic.h"
#include "opcode.h"
#include "val/instruction.h"
#include "val/validation_state.h"

namespace libspirv {

namespace {

// Returns the type of the value accessed by OpCompositeExtract or
// OpCompositeInsert instruction. The function traverses the hierarchy of
// nested data structures (structs, arrays, vectors, matrices) as directed by
// the sequence of indices in the instruction. May return error if traversal
// fails (encountered non-composite, out of bounds, nesting too deep).
// Returns the type of Composite operand if the instruction has no indices.
spv_result_t GetExtractInsertValueType(ValidationState_t& _,
                                       const spv_parsed_instruction_t& inst,
                                       uint32_t* member_type) {
  const SpvOp opcode = static_cast<SpvOp>(inst.opcode);
  assert(opcode == SpvOpCompositeExtract || opcode == SpvOpCompositeInsert);
  uint32_t word_index = opcode == SpvOpCompositeExtract ? 4 : 5;
  const uint32_t num_words = static_cast<uint32_t>(inst.num_words);
  const uint32_t composite_id_index = word_index - 1;

  const uint32_t num_indices = num_words - word_index;
  const uint32_t kCompositeExtractInsertMaxNumIndices = 255;
  if (num_indices > kCompositeExtractInsertMaxNumIndices) {
    return _.diag(SPV_ERROR_INVALID_DATA)
           << "The number of indexes in Op" << spvOpcodeString(opcode)
           << " may not exceed " << kCompositeExtractInsertMaxNumIndices
           << ". Found " << num_indices << " indexes.";
  }

  *member_type = _.GetTypeId(inst.words[composite_id_index]);
  if (*member_type == 0) {
    return _.diag(SPV_ERROR_INVALID_DATA)
           << spvOpcodeString(opcode)
           << ": expected Composite to be an object of composite type";
  }

  for (; word_index < num_words; ++word_index) {
    const uint32_t component_index = inst.words[word_index];
    const Instruction* const type_inst = _.FindDef(*member_type);
    assert(type_inst);
    switch (type_inst->opcode()) {
      case SpvOpTypeVector: {
        *member_type = type_inst->word(2);
        const uint32_t vector_size = type_inst->word(3);
        if (component_index >= vector_size) {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << spvOpcodeString(opcode)
                 << ": vector access is out of bounds, vector size is "
                 << vector_size << ", but access index is " << component_index;
        }
        break;
      }
      case SpvOpTypeMatrix: {
        *member_type = type_inst->word(2);
        const uint32_t num_cols = type_inst->word(3);
        if (component_index >= num_cols) {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << spvOpcodeString(opcode)
                 << ": matrix access is out of bounds, matrix has " << num_cols
                 << " columns, but access index is " << component_index;
        }
        break;
      }
      case SpvOpTypeArray: {
        uint64_t array_size = 0;
        auto size = _.FindDef(type_inst->word(3));
        *member_type = type_inst->word(2);
        if (spvOpcodeIsSpecConstant(size->opcode())) {
          // Cannot verify against the size of this array.
          break;
        }

        if (!_.GetConstantValUint64(type_inst->word(3), &array_size)) {
          assert(0 && "Array type definition is corrupt");
        }
        if (component_index >= array_size) {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << spvOpcodeString(opcode)
                 << ": array access is out of bounds, array size is "
                 << array_size << ", but access index is " << component_index;
        }
        break;
      }
      case SpvOpTypeRuntimeArray: {
        *member_type = type_inst->word(2);
        // Array size is unknown.
        break;
      }
      case SpvOpTypeStruct: {
        const size_t num_struct_members = type_inst->words().size() - 2;
        if (component_index >= num_struct_members) {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << "Index is out of bounds: Op" << spvOpcodeString(opcode)
                 << " can not find index " << component_index
                 << " into the structure <id> '" << type_inst->id()
                 << "'. This structure has " << num_struct_members
                 << " members. Largest valid index is "
                 << num_struct_members - 1 << ".";
        }
        *member_type = type_inst->word(component_index + 2);
        break;
      }
      default:
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Op" << spvOpcodeString(opcode)
               << " reached non-composite type while indexes still remain to "
                  "be traversed.";
    }
  }

  return SPV_SUCCESS;
}

}  // anonymous namespace

// Validates correctness of composite instructions.
spv_result_t CompositesPass(ValidationState_t& _,
                            const spv_parsed_instruction_t* inst) {
  const SpvOp opcode = static_cast<SpvOp>(inst->opcode);
  const uint32_t result_type = inst->type_id;
  const uint32_t num_operands = static_cast<uint32_t>(inst->num_operands);

  switch (opcode) {
    case SpvOpVectorExtractDynamic: {
      const SpvOp result_opcode = _.GetIdOpcode(result_type);
      if (!spvOpcodeIsScalarType(result_opcode)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Result Type to be a scalar type";
      }

      const uint32_t vector_type = _.GetOperandTypeId(inst, 2);
      const SpvOp vector_opcode = _.GetIdOpcode(vector_type);
      if (vector_opcode != SpvOpTypeVector) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Vector type to be OpTypeVector";
      }

      if (_.GetComponentType(vector_type) != result_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Vector component type to be equal to Result Type";
      }

      const uint32_t index_type = _.GetOperandTypeId(inst, 3);
      if (!_.IsIntScalarType(index_type)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Index to be int scalar";
      }

      break;
    }

    case SpvOpVectorInsertDynamic: {
      const SpvOp result_opcode = _.GetIdOpcode(result_type);
      if (result_opcode != SpvOpTypeVector) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Result Type to be OpTypeVector";
      }

      const uint32_t vector_type = _.GetOperandTypeId(inst, 2);
      if (vector_type != result_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Vector type to be equal to Result Type";
      }

      const uint32_t component_type = _.GetOperandTypeId(inst, 3);
      if (_.GetComponentType(result_type) != component_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Component type to be equal to Result Type "
               << "component type";
      }

      const uint32_t index_type = _.GetOperandTypeId(inst, 4);
      if (!_.IsIntScalarType(index_type)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Index to be int scalar";
      }

      break;
    }

    case SpvOpVectorShuffle: {
      // Handled in validate_id.cpp.
      // TODO(atgoo@github.com) Consider moving it here.
      break;
    }

    case SpvOpCompositeConstruct: {
      const SpvOp result_opcode = _.GetIdOpcode(result_type);
      switch (result_opcode) {
        case SpvOpTypeVector: {
          const uint32_t num_result_components = _.GetDimension(result_type);
          const uint32_t result_component_type =
              _.GetComponentType(result_type);
          uint32_t given_component_count = 0;

          if (num_operands <= 3) {
            return _.diag(SPV_ERROR_INVALID_DATA)
                   << spvOpcodeString(opcode)
                   << ": expected number of constituents to be at least 2";
          }

          for (uint32_t operand_index = 2; operand_index < num_operands;
               ++operand_index) {
            const uint32_t operand_type =
                _.GetOperandTypeId(inst, operand_index);
            if (operand_type == result_component_type) {
              ++given_component_count;
            } else {
              if (_.GetIdOpcode(operand_type) != SpvOpTypeVector ||
                  _.GetComponentType(operand_type) != result_component_type) {
                return _.diag(SPV_ERROR_INVALID_DATA)
                       << spvOpcodeString(opcode)
                       << ": expected Constituents to be scalars or vectors of "
                       << "the same type as Result Type components";
              }

              given_component_count += _.GetDimension(operand_type);
            }
          }

          if (num_result_components != given_component_count) {
            return _.diag(SPV_ERROR_INVALID_DATA)
                   << spvOpcodeString(opcode)
                   << ": expected total number of given components to be equal "
                   << "to the size of Result Type vector";
          }

          break;
        }
        case SpvOpTypeMatrix: {
          uint32_t result_num_rows = 0;
          uint32_t result_num_cols = 0;
          uint32_t result_col_type = 0;
          uint32_t result_component_type = 0;
          if (!_.GetMatrixTypeInfo(result_type, &result_num_rows,
                                   &result_num_cols, &result_col_type,
                                   &result_component_type)) {
            assert(0);
          }

          if (result_num_cols + 2 != num_operands) {
            return _.diag(SPV_ERROR_INVALID_DATA)
                   << spvOpcodeString(opcode)
                   << ": expected total number of Constituents to be equal "
                   << "to the number of columns of Result Type matrix";
          }

          for (uint32_t operand_index = 2; operand_index < num_operands;
               ++operand_index) {
            const uint32_t operand_type =
                _.GetOperandTypeId(inst, operand_index);
            if (operand_type != result_col_type) {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << spvOpcodeString(opcode)
                     << ": expected Constituent type to be equal to the column "
                     << "type Result Type matrix";
            }
          }

          break;
        }
        case SpvOpTypeArray: {
          const Instruction* const array_inst = _.FindDef(result_type);
          assert(array_inst);
          assert(array_inst->opcode() == SpvOpTypeArray);

          auto size = _.FindDef(array_inst->word(3));
          if (spvOpcodeIsSpecConstant(size->opcode())) {
            // Cannot verify against the size of this array.
            break;
          }

          uint64_t array_size = 0;
          if (!_.GetConstantValUint64(array_inst->word(3), &array_size)) {
            assert(0 && "Array type definition is corrupt");
          }

          if (array_size + 2 != num_operands) {
            return _.diag(SPV_ERROR_INVALID_DATA)
                   << spvOpcodeString(opcode)
                   << ": expected total number of Constituents to be equal "
                   << "to the number of elements of Result Type array";
          }

          const uint32_t result_component_type = array_inst->word(2);
          for (uint32_t operand_index = 2; operand_index < num_operands;
               ++operand_index) {
            const uint32_t operand_type =
                _.GetOperandTypeId(inst, operand_index);
            if (operand_type != result_component_type) {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << spvOpcodeString(opcode)
                     << ": expected Constituent type to be equal to the column "
                     << "type Result Type array";
            }
          }

          break;
        }
        case SpvOpTypeStruct: {
          const Instruction* const struct_inst = _.FindDef(result_type);
          assert(struct_inst);
          assert(struct_inst->opcode() == SpvOpTypeStruct);

          if (struct_inst->operands().size() + 1 != num_operands) {
            return _.diag(SPV_ERROR_INVALID_DATA)
                   << spvOpcodeString(opcode)
                   << ": expected total number of Constituents to be equal "
                   << "to the number of members of Result Type struct";
          }

          for (uint32_t operand_index = 2; operand_index < num_operands;
               ++operand_index) {
            const uint32_t operand_type =
                _.GetOperandTypeId(inst, operand_index);
            const uint32_t member_type = struct_inst->word(operand_index);
            if (operand_type != member_type) {
              return _.diag(SPV_ERROR_INVALID_DATA)
                     << spvOpcodeString(opcode)
                     << ": expected Constituent type to be equal to the "
                     << "corresponding member type of Result Type struct";
            }
          }

          break;
        }
        default: {
          return _.diag(SPV_ERROR_INVALID_DATA)
                 << spvOpcodeString(opcode)
                 << ": expected Result Type to be a composite type";
        }
      }

      break;
    }

    case SpvOpCompositeExtract: {
      uint32_t member_type = 0;
      if (spv_result_t error =
              GetExtractInsertValueType(_, *inst, &member_type)) {
        return error;
      }

      if (result_type != member_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "Op" << spvOpcodeString(opcode) << " result type (Op"
               << spvOpcodeString(_.GetIdOpcode(result_type))
               << ") does not match the type that results from indexing into "
                  "the "
                  "composite (Op"
               << spvOpcodeString(_.GetIdOpcode(member_type)) << ").";
      }
      break;
    }

    case SpvOpCompositeInsert: {
      const uint32_t object_type = _.GetOperandTypeId(inst, 2);
      const uint32_t composite_type = _.GetOperandTypeId(inst, 3);

      if (result_type != composite_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "The Result Type must be the same as Composite type in Op"
               << spvOpcodeString(opcode) << " yielding Result Id "
               << result_type << ".";
      }

      uint32_t member_type = 0;
      if (spv_result_t error =
              GetExtractInsertValueType(_, *inst, &member_type)) {
        return error;
      }

      if (object_type != member_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << "The Object type (Op"
               << spvOpcodeString(_.GetIdOpcode(object_type)) << ") in Op"
               << spvOpcodeString(opcode)
               << " does not match the type that results from indexing into "
                  "the Composite (Op"
               << spvOpcodeString(_.GetIdOpcode(member_type)) << ").";
      }
      break;
    }

    case SpvOpCopyObject: {
      if (!spvOpcodeGeneratesType(_.GetIdOpcode(result_type))) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Result Type to be a type";
      }

      const uint32_t operand_type = _.GetOperandTypeId(inst, 2);
      if (operand_type != result_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Result Type and Operand type to be the same";
      }

      break;
    }

    case SpvOpTranspose: {
      uint32_t result_num_rows = 0;
      uint32_t result_num_cols = 0;
      uint32_t result_col_type = 0;
      uint32_t result_component_type = 0;
      if (!_.GetMatrixTypeInfo(result_type, &result_num_rows, &result_num_cols,
                               &result_col_type, &result_component_type)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Result Type to be a matrix type";
      }

      const uint32_t matrix_type = _.GetOperandTypeId(inst, 2);
      uint32_t matrix_num_rows = 0;
      uint32_t matrix_num_cols = 0;
      uint32_t matrix_col_type = 0;
      uint32_t matrix_component_type = 0;
      if (!_.GetMatrixTypeInfo(matrix_type, &matrix_num_rows, &matrix_num_cols,
                               &matrix_col_type, &matrix_component_type)) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected Matrix to be of type OpTypeMatrix";
      }

      if (result_component_type != matrix_component_type) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected component types of Matrix and Result Type to be "
               << "identical";
      }

      if (result_num_rows != matrix_num_cols ||
          result_num_cols != matrix_num_rows) {
        return _.diag(SPV_ERROR_INVALID_DATA)
               << spvOpcodeString(opcode)
               << ": expected number of columns and the column size of Matrix "
               << "to be the reverse of those of Result Type";
      }

      break;
    }

    default:
      break;
  }

  return SPV_SUCCESS;
}

}  // namespace libspirv

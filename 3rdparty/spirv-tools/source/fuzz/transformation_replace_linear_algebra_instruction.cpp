// Copyright (c) 2020 André Perez Maselco
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

#include "source/fuzz/transformation_replace_linear_algebra_instruction.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationReplaceLinearAlgebraInstruction::
    TransformationReplaceLinearAlgebraInstruction(
        const spvtools::fuzz::protobufs::
            TransformationReplaceLinearAlgebraInstruction& message)
    : message_(message) {}

TransformationReplaceLinearAlgebraInstruction::
    TransformationReplaceLinearAlgebraInstruction(
        const std::vector<uint32_t>& fresh_ids,
        const protobufs::InstructionDescriptor& instruction_descriptor) {
  for (auto fresh_id : fresh_ids) {
    message_.add_fresh_ids(fresh_id);
  }
  *message_.mutable_instruction_descriptor() = instruction_descriptor;
}

bool TransformationReplaceLinearAlgebraInstruction::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  auto instruction =
      FindInstruction(message_.instruction_descriptor(), ir_context);

  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3354):
  // Right now we only support certain operations. When this issue is addressed
  // the following conditional can use the function |spvOpcodeIsLinearAlgebra|.
  // It must be a supported linear algebra instruction.
  if (instruction->opcode() != SpvOpVectorTimesScalar &&
      instruction->opcode() != SpvOpMatrixTimesScalar &&
      instruction->opcode() != SpvOpDot) {
    return false;
  }

  // |message_.fresh_ids.size| must be the exact number of fresh ids needed to
  // apply the transformation.
  if (static_cast<uint32_t>(message_.fresh_ids().size()) !=
      GetRequiredFreshIdCount(ir_context, instruction)) {
    return false;
  }

  // All ids in |message_.fresh_ids| must be fresh.
  for (uint32_t i = 0; i < static_cast<uint32_t>(message_.fresh_ids().size());
       i++) {
    if (!fuzzerutil::IsFreshId(ir_context, message_.fresh_ids(i))) {
      return false;
    }
  }

  return true;
}

void TransformationReplaceLinearAlgebraInstruction::Apply(
    opt::IRContext* ir_context, TransformationContext* /*unused*/) const {
  auto linear_algebra_instruction =
      FindInstruction(message_.instruction_descriptor(), ir_context);

  switch (linear_algebra_instruction->opcode()) {
    case SpvOpVectorTimesScalar:
      ReplaceOpVectorTimesScalar(ir_context, linear_algebra_instruction);
      break;
    case SpvOpMatrixTimesScalar:
      ReplaceOpMatrixTimesScalar(ir_context, linear_algebra_instruction);
      break;
    case SpvOpDot:
      ReplaceOpDot(ir_context, linear_algebra_instruction);
      break;
    default:
      assert(false && "Should be unreachable.");
      break;
  }

  ir_context->InvalidateAnalysesExceptFor(opt::IRContext::kAnalysisNone);
}

protobufs::Transformation
TransformationReplaceLinearAlgebraInstruction::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_replace_linear_algebra_instruction() = message_;
  return result;
}

uint32_t TransformationReplaceLinearAlgebraInstruction::GetRequiredFreshIdCount(
    opt::IRContext* ir_context, opt::Instruction* instruction) {
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3354):
  // Right now we only support certain operations.
  switch (instruction->opcode()) {
    case SpvOpVectorTimesScalar:
      // For each vector component, 1 OpCompositeExtract and 1 OpFMul will be
      // inserted.
      return 2 *
             ir_context->get_type_mgr()
                 ->GetType(ir_context->get_def_use_mgr()
                               ->GetDef(instruction->GetSingleWordInOperand(0))
                               ->type_id())
                 ->AsVector()
                 ->element_count();
    case SpvOpMatrixTimesScalar: {
      // For each matrix column, |1 + column.size| OpCompositeExtract,
      // |column.size| OpFMul and 1 OpCompositeConstruct instructions will be
      // inserted.
      auto matrix_instruction = ir_context->get_def_use_mgr()->GetDef(
          instruction->GetSingleWordInOperand(0));
      auto matrix_type =
          ir_context->get_type_mgr()->GetType(matrix_instruction->type_id());
      return 2 * matrix_type->AsMatrix()->element_count() *
             (1 + matrix_type->AsMatrix()
                      ->element_type()
                      ->AsVector()
                      ->element_count());
    }
    case SpvOpDot:
      // For each pair of vector components, 2 OpCompositeExtract and 1 OpFMul
      // will be inserted. The first two OpFMul instructions will result the
      // first OpFAdd instruction to be inserted. For each remaining OpFMul, 1
      // OpFAdd will be inserted. The last OpFAdd instruction is got by changing
      // the OpDot instruction.
      return 4 * ir_context->get_type_mgr()
                     ->GetType(
                         ir_context->get_def_use_mgr()
                             ->GetDef(instruction->GetSingleWordInOperand(0))
                             ->type_id())
                     ->AsVector()
                     ->element_count() -
             2;
    default:
      assert(false && "Unsupported linear algebra instruction.");
      return 0;
  }
}

void TransformationReplaceLinearAlgebraInstruction::ReplaceOpVectorTimesScalar(
    opt::IRContext* ir_context,
    opt::Instruction* linear_algebra_instruction) const {
  // Gets OpVectorTimesScalar in operands.
  auto vector = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(0));
  auto scalar = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(1));

  uint32_t vector_component_count = ir_context->get_type_mgr()
                                        ->GetType(vector->type_id())
                                        ->AsVector()
                                        ->element_count();
  std::vector<uint32_t> float_multiplication_ids(vector_component_count);
  uint32_t fresh_id_index = 0;

  for (uint32_t i = 0; i < vector_component_count; i++) {
    // Extracts |vector| component.
    uint32_t vector_extract_id = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, vector_extract_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpCompositeExtract, scalar->type_id(), vector_extract_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {vector->result_id()}},
             {SPV_OPERAND_TYPE_LITERAL_INTEGER, {i}}})));

    // Multiplies the |vector| component with the |scalar|.
    uint32_t float_multiplication_id = message_.fresh_ids(fresh_id_index++);
    float_multiplication_ids[i] = float_multiplication_id;
    fuzzerutil::UpdateModuleIdBound(ir_context, float_multiplication_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpFMul, scalar->type_id(), float_multiplication_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {vector_extract_id}},
             {SPV_OPERAND_TYPE_ID, {scalar->result_id()}}})));
  }

  // The OpVectorTimesScalar instruction is changed to an OpCompositeConstruct
  // instruction.
  linear_algebra_instruction->SetOpcode(SpvOpCompositeConstruct);
  linear_algebra_instruction->SetInOperand(0, {float_multiplication_ids[0]});
  linear_algebra_instruction->SetInOperand(1, {float_multiplication_ids[1]});
  for (uint32_t i = 2; i < float_multiplication_ids.size(); i++) {
    linear_algebra_instruction->AddOperand(
        {SPV_OPERAND_TYPE_ID, {float_multiplication_ids[i]}});
  }
}

void TransformationReplaceLinearAlgebraInstruction::ReplaceOpMatrixTimesScalar(
    opt::IRContext* ir_context,
    opt::Instruction* linear_algebra_instruction) const {
  // Gets OpMatrixTimesScalar in operands.
  auto matrix_instruction = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(0));
  auto scalar_instruction = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(1));

  // Gets matrix information.
  uint32_t matrix_column_count = ir_context->get_type_mgr()
                                     ->GetType(matrix_instruction->type_id())
                                     ->AsMatrix()
                                     ->element_count();
  auto matrix_column_type = ir_context->get_type_mgr()
                                ->GetType(matrix_instruction->type_id())
                                ->AsMatrix()
                                ->element_type();
  uint32_t matrix_column_size = matrix_column_type->AsVector()->element_count();

  std::vector<uint32_t> composite_construct_ids(matrix_column_count);
  uint32_t fresh_id_index = 0;

  for (uint32_t i = 0; i < matrix_column_count; i++) {
    // Extracts |matrix| column.
    uint32_t matrix_extract_id = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, matrix_extract_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpCompositeExtract,
        ir_context->get_type_mgr()->GetId(matrix_column_type),
        matrix_extract_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {matrix_instruction->result_id()}},
             {SPV_OPERAND_TYPE_LITERAL_INTEGER, {i}}})));

    std::vector<uint32_t> float_multiplication_ids(matrix_column_size);

    for (uint32_t j = 0; j < matrix_column_size; j++) {
      // Extracts |column| component.
      uint32_t column_extract_id = message_.fresh_ids(fresh_id_index++);
      fuzzerutil::UpdateModuleIdBound(ir_context, column_extract_id);
      linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpCompositeExtract, scalar_instruction->type_id(),
          column_extract_id,
          opt::Instruction::OperandList(
              {{SPV_OPERAND_TYPE_ID, {matrix_extract_id}},
               {SPV_OPERAND_TYPE_LITERAL_INTEGER, {j}}})));

      // Multiplies the |column| component with the |scalar|.
      float_multiplication_ids[j] = message_.fresh_ids(fresh_id_index++);
      fuzzerutil::UpdateModuleIdBound(ir_context, float_multiplication_ids[j]);
      linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpFMul, scalar_instruction->type_id(),
          float_multiplication_ids[j],
          opt::Instruction::OperandList(
              {{SPV_OPERAND_TYPE_ID, {column_extract_id}},
               {SPV_OPERAND_TYPE_ID, {scalar_instruction->result_id()}}})));
    }

    // Constructs a new column multiplied by |scalar|.
    opt::Instruction::OperandList composite_construct_in_operands;
    for (uint32_t& float_multiplication_id : float_multiplication_ids) {
      composite_construct_in_operands.push_back(
          {SPV_OPERAND_TYPE_ID, {float_multiplication_id}});
    }
    composite_construct_ids[i] = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, composite_construct_ids[i]);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpCompositeConstruct,
        ir_context->get_type_mgr()->GetId(matrix_column_type),
        composite_construct_ids[i], composite_construct_in_operands));
  }

  // The OpMatrixTimesScalar instruction is changed to an OpCompositeConstruct
  // instruction.
  linear_algebra_instruction->SetOpcode(SpvOpCompositeConstruct);
  linear_algebra_instruction->SetInOperand(0, {composite_construct_ids[0]});
  linear_algebra_instruction->SetInOperand(1, {composite_construct_ids[1]});
  for (uint32_t i = 2; i < composite_construct_ids.size(); i++) {
    linear_algebra_instruction->AddOperand(
        {SPV_OPERAND_TYPE_ID, {composite_construct_ids[i]}});
  }
}

void TransformationReplaceLinearAlgebraInstruction::ReplaceOpDot(
    opt::IRContext* ir_context,
    opt::Instruction* linear_algebra_instruction) const {
  // Gets OpDot in operands.
  auto vector_1 = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(0));
  auto vector_2 = ir_context->get_def_use_mgr()->GetDef(
      linear_algebra_instruction->GetSingleWordInOperand(1));

  uint32_t vectors_component_count = ir_context->get_type_mgr()
                                         ->GetType(vector_1->type_id())
                                         ->AsVector()
                                         ->element_count();
  std::vector<uint32_t> float_multiplication_ids(vectors_component_count);
  uint32_t fresh_id_index = 0;

  for (uint32_t i = 0; i < vectors_component_count; i++) {
    // Extracts |vector_1| component.
    uint32_t vector_1_extract_id = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, vector_1_extract_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpCompositeExtract,
        linear_algebra_instruction->type_id(), vector_1_extract_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {vector_1->result_id()}},
             {SPV_OPERAND_TYPE_LITERAL_INTEGER, {i}}})));

    // Extracts |vector_2| component.
    uint32_t vector_2_extract_id = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, vector_2_extract_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpCompositeExtract,
        linear_algebra_instruction->type_id(), vector_2_extract_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {vector_2->result_id()}},
             {SPV_OPERAND_TYPE_LITERAL_INTEGER, {i}}})));

    // Multiplies the pair of components.
    float_multiplication_ids[i] = message_.fresh_ids(fresh_id_index++);
    fuzzerutil::UpdateModuleIdBound(ir_context, float_multiplication_ids[i]);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpFMul, linear_algebra_instruction->type_id(),
        float_multiplication_ids[i],
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {vector_1_extract_id}},
             {SPV_OPERAND_TYPE_ID, {vector_2_extract_id}}})));
  }

  // If the vector has 2 components, then there will be 2 float multiplication
  // instructions.
  if (vectors_component_count == 2) {
    linear_algebra_instruction->SetOpcode(SpvOpFAdd);
    linear_algebra_instruction->SetInOperand(0, {float_multiplication_ids[0]});
    linear_algebra_instruction->SetInOperand(1, {float_multiplication_ids[1]});
  } else {
    // The first OpFAdd instruction has as operands the first two OpFMul
    // instructions.
    std::vector<uint32_t> float_add_ids;
    uint32_t float_add_id = message_.fresh_ids(fresh_id_index++);
    float_add_ids.push_back(float_add_id);
    fuzzerutil::UpdateModuleIdBound(ir_context, float_add_id);
    linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
        ir_context, SpvOpFAdd, linear_algebra_instruction->type_id(),
        float_add_id,
        opt::Instruction::OperandList(
            {{SPV_OPERAND_TYPE_ID, {float_multiplication_ids[0]}},
             {SPV_OPERAND_TYPE_ID, {float_multiplication_ids[1]}}})));

    // The remaining OpFAdd instructions has as operands an OpFMul and an OpFAdd
    // instruction.
    for (uint32_t i = 2; i < float_multiplication_ids.size() - 1; i++) {
      float_add_id = message_.fresh_ids(fresh_id_index++);
      fuzzerutil::UpdateModuleIdBound(ir_context, float_add_id);
      float_add_ids.push_back(float_add_id);
      linear_algebra_instruction->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpFAdd, linear_algebra_instruction->type_id(),
          float_add_id,
          opt::Instruction::OperandList(
              {{SPV_OPERAND_TYPE_ID, {float_multiplication_ids[i]}},
               {SPV_OPERAND_TYPE_ID, {float_add_ids[i - 2]}}})));
    }

    // The last OpFAdd instruction is got by changing some of the OpDot
    // instruction attributes.
    linear_algebra_instruction->SetOpcode(SpvOpFAdd);
    linear_algebra_instruction->SetInOperand(
        0, {float_multiplication_ids[float_multiplication_ids.size() - 1]});
    linear_algebra_instruction->SetInOperand(
        1, {float_add_ids[float_add_ids.size() - 1]});
  }
}

}  // namespace fuzz
}  // namespace spvtools

// Copyright (c) 2019 Google LLC
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

#include "source/fuzz/fuzzer_pass.h"

#include <set>

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"
#include "source/fuzz/transformation_add_constant_boolean.h"
#include "source/fuzz/transformation_add_constant_composite.h"
#include "source/fuzz/transformation_add_constant_scalar.h"
#include "source/fuzz/transformation_add_global_undef.h"
#include "source/fuzz/transformation_add_type_boolean.h"
#include "source/fuzz/transformation_add_type_float.h"
#include "source/fuzz/transformation_add_type_function.h"
#include "source/fuzz/transformation_add_type_int.h"
#include "source/fuzz/transformation_add_type_matrix.h"
#include "source/fuzz/transformation_add_type_pointer.h"
#include "source/fuzz/transformation_add_type_vector.h"

namespace spvtools {
namespace fuzz {

FuzzerPass::FuzzerPass(opt::IRContext* ir_context,
                       TransformationContext* transformation_context,
                       FuzzerContext* fuzzer_context,
                       protobufs::TransformationSequence* transformations)
    : ir_context_(ir_context),
      transformation_context_(transformation_context),
      fuzzer_context_(fuzzer_context),
      transformations_(transformations) {}

FuzzerPass::~FuzzerPass() = default;

std::vector<opt::Instruction*> FuzzerPass::FindAvailableInstructions(
    opt::Function* function, opt::BasicBlock* block,
    const opt::BasicBlock::iterator& inst_it,
    std::function<bool(opt::IRContext*, opt::Instruction*)>
        instruction_is_relevant) const {
  // TODO(afd) The following is (relatively) simple, but may end up being
  //  prohibitively inefficient, as it walks the whole dominator tree for
  //  every instruction that is considered.

  std::vector<opt::Instruction*> result;
  // Consider all global declarations
  for (auto& global : GetIRContext()->module()->types_values()) {
    if (instruction_is_relevant(GetIRContext(), &global)) {
      result.push_back(&global);
    }
  }

  // Consider all function parameters
  function->ForEachParam(
      [this, &instruction_is_relevant, &result](opt::Instruction* param) {
        if (instruction_is_relevant(GetIRContext(), param)) {
          result.push_back(param);
        }
      });

  // Consider all previous instructions in this block
  for (auto prev_inst_it = block->begin(); prev_inst_it != inst_it;
       ++prev_inst_it) {
    if (instruction_is_relevant(GetIRContext(), &*prev_inst_it)) {
      result.push_back(&*prev_inst_it);
    }
  }

  // Walk the dominator tree to consider all instructions from dominating
  // blocks
  auto dominator_analysis = GetIRContext()->GetDominatorAnalysis(function);
  for (auto next_dominator = dominator_analysis->ImmediateDominator(block);
       next_dominator != nullptr;
       next_dominator =
           dominator_analysis->ImmediateDominator(next_dominator)) {
    for (auto& dominating_inst : *next_dominator) {
      if (instruction_is_relevant(GetIRContext(), &dominating_inst)) {
        result.push_back(&dominating_inst);
      }
    }
  }
  return result;
}

void FuzzerPass::ForEachInstructionWithInstructionDescriptor(
    std::function<
        void(opt::Function* function, opt::BasicBlock* block,
             opt::BasicBlock::iterator inst_it,
             const protobufs::InstructionDescriptor& instruction_descriptor)>
        action) {
  // Consider every block in every function.
  for (auto& function : *GetIRContext()->module()) {
    for (auto& block : function) {
      // We now consider every instruction in the block, randomly deciding
      // whether to apply a transformation before it.

      // In order for transformations to insert new instructions, they need to
      // be able to identify the instruction to insert before.  We describe an
      // instruction via its opcode, 'opc', a base instruction 'base' that has a
      // result id, and the number of instructions with opcode 'opc' that we
      // should skip when searching from 'base' for the desired instruction.
      // (An instruction that has a result id is represented by its own opcode,
      // itself as 'base', and a skip-count of 0.)
      std::vector<std::tuple<uint32_t, SpvOp, uint32_t>>
          base_opcode_skip_triples;

      // The initial base instruction is the block label.
      uint32_t base = block.id();

      // Counts the number of times we have seen each opcode since we reset the
      // base instruction.
      std::map<SpvOp, uint32_t> skip_count;

      // Consider every instruction in the block.  The label is excluded: it is
      // only necessary to consider it as a base in case the first instruction
      // in the block does not have a result id.
      for (auto inst_it = block.begin(); inst_it != block.end(); ++inst_it) {
        if (inst_it->HasResultId()) {
          // In the case that the instruction has a result id, we use the
          // instruction as its own base, and clear the skip counts we have
          // collected.
          base = inst_it->result_id();
          skip_count.clear();
        }
        const SpvOp opcode = inst_it->opcode();

        // Invoke the provided function, which might apply a transformation.
        action(&function, &block, inst_it,
               MakeInstructionDescriptor(
                   base, opcode,
                   skip_count.count(opcode) ? skip_count.at(opcode) : 0));

        if (!inst_it->HasResultId()) {
          skip_count[opcode] =
              skip_count.count(opcode) ? skip_count.at(opcode) + 1 : 1;
        }
      }
    }
  }
}

uint32_t FuzzerPass::FindOrCreateBoolType() {
  opt::analysis::Bool bool_type;
  auto existing_id = GetIRContext()->get_type_mgr()->GetId(&bool_type);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddTypeBoolean(result));
  return result;
}

uint32_t FuzzerPass::FindOrCreate32BitIntegerType(bool is_signed) {
  opt::analysis::Integer int_type(32, is_signed);
  auto existing_id = GetIRContext()->get_type_mgr()->GetId(&int_type);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddTypeInt(result, 32, is_signed));
  return result;
}

uint32_t FuzzerPass::FindOrCreate32BitFloatType() {
  opt::analysis::Float float_type(32);
  auto existing_id = GetIRContext()->get_type_mgr()->GetId(&float_type);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddTypeFloat(result, 32));
  return result;
}

uint32_t FuzzerPass::FindOrCreateFunctionType(
    uint32_t return_type_id, const std::vector<uint32_t>& argument_id) {
  // FindFunctionType has a sigle argument for OpTypeFunction operands
  // so we will have to copy them all in this vector
  std::vector<uint32_t> type_ids(argument_id.size() + 1);
  type_ids[0] = return_type_id;
  std::copy(argument_id.begin(), argument_id.end(), type_ids.begin() + 1);

  // Check if type exists
  auto existing_id = fuzzerutil::FindFunctionType(GetIRContext(), type_ids);
  if (existing_id) {
    return existing_id;
  }

  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddTypeFunction(result, return_type_id, argument_id));
  return result;
}

uint32_t FuzzerPass::FindOrCreateVectorType(uint32_t component_type_id,
                                            uint32_t component_count) {
  assert(component_count >= 2 && component_count <= 4 &&
         "Precondition: component count must be in range [2, 4].");
  opt::analysis::Type* component_type =
      GetIRContext()->get_type_mgr()->GetType(component_type_id);
  assert(component_type && "Precondition: the component type must exist.");
  opt::analysis::Vector vector_type(component_type, component_count);
  auto existing_id = GetIRContext()->get_type_mgr()->GetId(&vector_type);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddTypeVector(result, component_type_id, component_count));
  return result;
}

uint32_t FuzzerPass::FindOrCreateMatrixType(uint32_t column_count,
                                            uint32_t row_count) {
  assert(column_count >= 2 && column_count <= 4 &&
         "Precondition: column count must be in range [2, 4].");
  assert(row_count >= 2 && row_count <= 4 &&
         "Precondition: row count must be in range [2, 4].");
  uint32_t column_type_id =
      FindOrCreateVectorType(FindOrCreate32BitFloatType(), row_count);
  opt::analysis::Type* column_type =
      GetIRContext()->get_type_mgr()->GetType(column_type_id);
  opt::analysis::Matrix matrix_type(column_type, column_count);
  auto existing_id = GetIRContext()->get_type_mgr()->GetId(&matrix_type);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddTypeMatrix(result, column_type_id, column_count));
  return result;
}

uint32_t FuzzerPass::FindOrCreatePointerType(uint32_t base_type_id,
                                             SpvStorageClass storage_class) {
  // We do not use the type manager here, due to problems related to isomorphic
  // but distinct structs not being regarded as different.
  auto existing_id = fuzzerutil::MaybeGetPointerType(
      GetIRContext(), base_type_id, storage_class);
  if (existing_id) {
    return existing_id;
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddTypePointer(result, storage_class, base_type_id));
  return result;
}

uint32_t FuzzerPass::FindOrCreatePointerTo32BitIntegerType(
    bool is_signed, SpvStorageClass storage_class) {
  return FindOrCreatePointerType(FindOrCreate32BitIntegerType(is_signed),
                                 storage_class);
}

uint32_t FuzzerPass::FindOrCreate32BitIntegerConstant(uint32_t word,
                                                      bool is_signed) {
  auto uint32_type_id = FindOrCreate32BitIntegerType(is_signed);
  opt::analysis::IntConstant int_constant(
      GetIRContext()->get_type_mgr()->GetType(uint32_type_id)->AsInteger(),
      {word});
  auto existing_constant =
      GetIRContext()->get_constant_mgr()->FindConstant(&int_constant);
  if (existing_constant) {
    return GetIRContext()
        ->get_constant_mgr()
        ->GetDefiningInstruction(existing_constant)
        ->result_id();
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddConstantScalar(result, uint32_type_id, {word}));
  return result;
}

uint32_t FuzzerPass::FindOrCreate32BitFloatConstant(uint32_t word) {
  auto float_type_id = FindOrCreate32BitFloatType();
  opt::analysis::FloatConstant float_constant(
      GetIRContext()->get_type_mgr()->GetType(float_type_id)->AsFloat(),
      {word});
  auto existing_constant =
      GetIRContext()->get_constant_mgr()->FindConstant(&float_constant);
  if (existing_constant) {
    return GetIRContext()
        ->get_constant_mgr()
        ->GetDefiningInstruction(existing_constant)
        ->result_id();
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(
      TransformationAddConstantScalar(result, float_type_id, {word}));
  return result;
}

uint32_t FuzzerPass::FindOrCreateBoolConstant(bool value) {
  auto bool_type_id = FindOrCreateBoolType();
  opt::analysis::BoolConstant bool_constant(
      GetIRContext()->get_type_mgr()->GetType(bool_type_id)->AsBool(), value);
  auto existing_constant =
      GetIRContext()->get_constant_mgr()->FindConstant(&bool_constant);
  if (existing_constant) {
    return GetIRContext()
        ->get_constant_mgr()
        ->GetDefiningInstruction(existing_constant)
        ->result_id();
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddConstantBoolean(result, value));
  return result;
}

uint32_t FuzzerPass::FindOrCreateGlobalUndef(uint32_t type_id) {
  for (auto& inst : GetIRContext()->types_values()) {
    if (inst.opcode() == SpvOpUndef && inst.type_id() == type_id) {
      return inst.result_id();
    }
  }
  auto result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddGlobalUndef(result, type_id));
  return result;
}

std::pair<std::vector<uint32_t>, std::map<uint32_t, std::vector<uint32_t>>>
FuzzerPass::GetAvailableBasicTypesAndPointers(
    SpvStorageClass storage_class) const {
  // Records all of the basic types available in the module.
  std::set<uint32_t> basic_types;

  // For each basic type, records all the associated pointer types that target
  // the basic type and that have |storage_class| as their storage class.
  std::map<uint32_t, std::vector<uint32_t>> basic_type_to_pointers;

  for (auto& inst : GetIRContext()->types_values()) {
    // For each basic type that we come across, record type, and the fact that
    // we cannot yet have seen any pointers that use the basic type as its
    // pointee type.
    //
    // For pointer types with basic pointee types, associate the pointer type
    // with the basic type.
    switch (inst.opcode()) {
      case SpvOpTypeBool:
      case SpvOpTypeFloat:
      case SpvOpTypeInt:
      case SpvOpTypeMatrix:
      case SpvOpTypeVector:
        // These are all basic types.
        basic_types.insert(inst.result_id());
        basic_type_to_pointers.insert({inst.result_id(), {}});
        break;
      case SpvOpTypeArray:
        // An array type is basic if its base type is basic.
        if (basic_types.count(inst.GetSingleWordInOperand(0))) {
          basic_types.insert(inst.result_id());
          basic_type_to_pointers.insert({inst.result_id(), {}});
        }
        break;
      case SpvOpTypeStruct: {
        // A struct type is basic if all of its members are basic.
        bool all_members_are_basic_types = true;
        for (uint32_t i = 0; i < inst.NumInOperands(); i++) {
          if (!basic_types.count(inst.GetSingleWordInOperand(i))) {
            all_members_are_basic_types = false;
            break;
          }
        }
        if (all_members_are_basic_types) {
          basic_types.insert(inst.result_id());
          basic_type_to_pointers.insert({inst.result_id(), {}});
        }
        break;
      }
      case SpvOpTypePointer: {
        // We are interested in the pointer if its pointee type is basic and it
        // has the right storage class.
        auto pointee_type = inst.GetSingleWordInOperand(1);
        if (inst.GetSingleWordInOperand(0) == storage_class &&
            basic_types.count(pointee_type)) {
          // The pointer has the desired storage class, and its pointee type is
          // a basic type, so we are interested in it.  Associate it with its
          // basic type.
          basic_type_to_pointers.at(pointee_type).push_back(inst.result_id());
        }
        break;
      }
      default:
        break;
    }
  }
  return {{basic_types.begin(), basic_types.end()}, basic_type_to_pointers};
}

uint32_t FuzzerPass::FindOrCreateZeroConstant(
    uint32_t scalar_or_composite_type_id) {
  auto type_instruction =
      GetIRContext()->get_def_use_mgr()->GetDef(scalar_or_composite_type_id);
  assert(type_instruction && "The type instruction must exist.");
  switch (type_instruction->opcode()) {
    case SpvOpTypeBool:
      return FindOrCreateBoolConstant(false);
    case SpvOpTypeFloat:
      return FindOrCreate32BitFloatConstant(0);
    case SpvOpTypeInt:
      return FindOrCreate32BitIntegerConstant(
          0, type_instruction->GetSingleWordInOperand(1) != 0);
    case SpvOpTypeArray: {
      return GetZeroConstantForHomogeneousComposite(
          *type_instruction, type_instruction->GetSingleWordInOperand(0),
          fuzzerutil::GetArraySize(*type_instruction, GetIRContext()));
    }
    case SpvOpTypeMatrix:
    case SpvOpTypeVector: {
      return GetZeroConstantForHomogeneousComposite(
          *type_instruction, type_instruction->GetSingleWordInOperand(0),
          type_instruction->GetSingleWordInOperand(1));
    }
    case SpvOpTypeStruct: {
      std::vector<const opt::analysis::Constant*> field_zero_constants;
      std::vector<uint32_t> field_zero_ids;
      for (uint32_t index = 0; index < type_instruction->NumInOperands();
           index++) {
        uint32_t field_constant_id = FindOrCreateZeroConstant(
            type_instruction->GetSingleWordInOperand(index));
        field_zero_ids.push_back(field_constant_id);
        field_zero_constants.push_back(
            GetIRContext()->get_constant_mgr()->FindDeclaredConstant(
                field_constant_id));
      }
      return FindOrCreateCompositeConstant(
          *type_instruction, field_zero_constants, field_zero_ids);
    }
    default:
      assert(false && "Unknown type.");
      return 0;
  }
}

uint32_t FuzzerPass::FindOrCreateCompositeConstant(
    const opt::Instruction& composite_type_instruction,
    const std::vector<const opt::analysis::Constant*>& constants,
    const std::vector<uint32_t>& constant_ids) {
  assert(constants.size() == constant_ids.size() &&
         "Precondition: |constants| and |constant_ids| must be in "
         "correspondence.");

  opt::analysis::Type* composite_type = GetIRContext()->get_type_mgr()->GetType(
      composite_type_instruction.result_id());
  std::unique_ptr<opt::analysis::Constant> composite_constant;
  if (composite_type->AsArray()) {
    composite_constant = MakeUnique<opt::analysis::ArrayConstant>(
        composite_type->AsArray(), constants);
  } else if (composite_type->AsMatrix()) {
    composite_constant = MakeUnique<opt::analysis::MatrixConstant>(
        composite_type->AsMatrix(), constants);
  } else if (composite_type->AsStruct()) {
    composite_constant = MakeUnique<opt::analysis::StructConstant>(
        composite_type->AsStruct(), constants);
  } else if (composite_type->AsVector()) {
    composite_constant = MakeUnique<opt::analysis::VectorConstant>(
        composite_type->AsVector(), constants);
  } else {
    assert(false &&
           "Precondition: |composite_type| must declare a composite type.");
    return 0;
  }

  uint32_t existing_constant =
      GetIRContext()->get_constant_mgr()->FindDeclaredConstant(
          composite_constant.get(), composite_type_instruction.result_id());
  if (existing_constant) {
    return existing_constant;
  }
  uint32_t result = GetFuzzerContext()->GetFreshId();
  ApplyTransformation(TransformationAddConstantComposite(
      result, composite_type_instruction.result_id(), constant_ids));
  return result;
}

uint32_t FuzzerPass::GetZeroConstantForHomogeneousComposite(
    const opt::Instruction& composite_type_instruction,
    uint32_t component_type_id, uint32_t num_components) {
  std::vector<const opt::analysis::Constant*> zero_constants;
  std::vector<uint32_t> zero_ids;
  uint32_t zero_component = FindOrCreateZeroConstant(component_type_id);
  const opt::analysis::Constant* registered_zero_component =
      GetIRContext()->get_constant_mgr()->FindDeclaredConstant(zero_component);
  for (uint32_t i = 0; i < num_components; i++) {
    zero_constants.push_back(registered_zero_component);
    zero_ids.push_back(zero_component);
  }
  return FindOrCreateCompositeConstant(composite_type_instruction,
                                       zero_constants, zero_ids);
}

}  // namespace fuzz
}  // namespace spvtools

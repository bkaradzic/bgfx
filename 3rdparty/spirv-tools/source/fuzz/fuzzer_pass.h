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

#ifndef SOURCE_FUZZ_FUZZER_PASS_H_
#define SOURCE_FUZZ_FUZZER_PASS_H_

#include <functional>
#include <vector>

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/fuzzer_context.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

// Interface for applying a pass of transformations to a module.
class FuzzerPass {
 public:
  FuzzerPass(opt::IRContext* ir_context, FactManager* fact_manager,
             FuzzerContext* fuzzer_context,
             protobufs::TransformationSequence* transformations);

  virtual ~FuzzerPass();

  // Applies the pass to the module |ir_context_|, assuming and updating
  // facts from |fact_manager_|, and using |fuzzer_context_| to guide the
  // process.  Appends to |transformations_| all transformations that were
  // applied during the pass.
  virtual void Apply() = 0;

 protected:
  opt::IRContext* GetIRContext() const { return ir_context_; }

  FactManager* GetFactManager() const { return fact_manager_; }

  FuzzerContext* GetFuzzerContext() const { return fuzzer_context_; }

  protobufs::TransformationSequence* GetTransformations() const {
    return transformations_;
  }

  // Returns all instructions that are *available* at |inst_it|, which is
  // required to be inside block |block| of function |function| - that is, all
  // instructions at global scope and all instructions that strictly dominate
  // |inst_it|.
  //
  // Filters said instructions to return only those that satisfy the
  // |instruction_is_relevant| predicate.  This, for instance, could ignore all
  // instructions that have a particular decoration.
  std::vector<opt::Instruction*> FindAvailableInstructions(
      opt::Function* function, opt::BasicBlock* block,
      const opt::BasicBlock::iterator& inst_it,
      std::function<bool(opt::IRContext*, opt::Instruction*)>
          instruction_is_relevant) const;

  // A helper method that iterates through each instruction in each block, at
  // all times tracking an instruction descriptor that allows the latest
  // instruction to be located even if it has no result id.
  //
  // The code to manipulate the instruction descriptor is a bit fiddly.  The
  // point of this method is to avoiding having to duplicate it in multiple
  // transformation passes.
  //
  // The function |action| is invoked for each instruction |inst_it| in block
  // |block| of function |function| that is encountered.  The
  // |instruction_descriptor| parameter to the function object allows |inst_it|
  // to be identified.
  //
  // In most intended use cases, the job of |action| is to randomly decide
  // whether to try to apply some transformation, and then - if selected - to
  // attempt to apply it.
  void ForEachInstructionWithInstructionDescriptor(
      std::function<
          void(opt::Function* function, opt::BasicBlock* block,
               opt::BasicBlock::iterator inst_it,
               const protobufs::InstructionDescriptor& instruction_descriptor)>
          action);

  // A generic helper for applying a transformation that should be applicable
  // by construction, and adding it to the sequence of applied transformations.
  template <typename TransformationType>
  void ApplyTransformation(const TransformationType& transformation) {
    assert(transformation.IsApplicable(GetIRContext(), *GetFactManager()) &&
           "Transformation should be applicable by construction.");
    transformation.Apply(GetIRContext(), GetFactManager());
    *GetTransformations()->add_transformation() = transformation.ToMessage();
  }

  // Returns the id of an OpTypeBool instruction.  If such an instruction does
  // not exist, a transformation is applied to add it.
  uint32_t FindOrCreateBoolType();

  // Returns the id of an OpTypeInt instruction, with width 32 and signedness
  // specified by |is_signed|.  If such an instruction does not exist, a
  // transformation is applied to add it.
  uint32_t FindOrCreate32BitIntegerType(bool is_signed);

  // Returns the id of an OpTypeFloat instruction, with width 32.  If such an
  // instruction does not exist, a transformation is applied to add it.
  uint32_t FindOrCreate32BitFloatType();

  // Returns the id of an OpTypeFunction %<return_type_id> %<...argument_id>
  // instruction. If such an instruction doesn't exist, a transformation
  // is applied to create a new one.
  uint32_t FindOrCreateFunctionType(uint32_t return_type_id,
                                    const std::vector<uint32_t>& argument_id);

  // Returns the id of an OpTypeVector instruction, with |component_type_id|
  // (which must already exist) as its base type, and |component_count|
  // elements (which must be in the range [2, 4]).  If such an instruction does
  // not exist, a transformation is applied to add it.
  uint32_t FindOrCreateVectorType(uint32_t component_type_id,
                                  uint32_t component_count);

  // Returns the id of an OpTypeMatrix instruction, with |column_count| columns
  // and |row_count| rows (each of which must be in the range [2, 4]).  If the
  // float and vector types required to build this matrix type or the matrix
  // type itself do not exist, transformations are applied to add them.
  uint32_t FindOrCreateMatrixType(uint32_t column_count, uint32_t row_count);

  // Returns the id of a pointer type with base type |base_type_id| (which must
  // already exist) and storage class |storage_class|.  A transformation is
  // applied to add the pointer if it does not already exist.
  uint32_t FindOrCreatePointerType(uint32_t base_type_id,
                                   SpvStorageClass storage_class);

  // Returns the id of an OpTypePointer instruction, with a 32-bit integer base
  // type of signedness specified by |is_signed|.  If the pointer type or
  // required integer base type do not exist, transformations are applied to add
  // them.
  uint32_t FindOrCreatePointerTo32BitIntegerType(bool is_signed,
                                                 SpvStorageClass storage_class);

  // Returns the id of an OpConstant instruction, with 32-bit integer type of
  // signedness specified by |is_signed|, with |word| as its value.  If either
  // the required integer type or the constant do not exist, transformations are
  // applied to add them.
  uint32_t FindOrCreate32BitIntegerConstant(uint32_t word, bool is_signed);

  // Returns the id of an OpConstant instruction, with 32-bit floating-point
  // type, with |word| as its value.  If either the required floating-point type
  // or the constant do not exist, transformations are applied to add them.
  uint32_t FindOrCreate32BitFloatConstant(uint32_t word);

  // Returns the id of an OpConstantTrue or OpConstantFalse instruction,
  // according to |value|.  If either the required instruction or the bool
  // type do not exist, transformations are applied to add them.
  uint32_t FindOrCreateBoolConstant(bool value);

  // Returns the result id of an instruction of the form:
  //   %id = OpUndef %|type_id|
  // If no such instruction exists, a transformation is applied to add it.
  uint32_t FindOrCreateGlobalUndef(uint32_t type_id);

  // Yields a pair, (base_type_ids, base_type_ids_to_pointers), such that:
  // - base_type_ids captures every scalar or composite type declared in the
  //   module (i.e., all int, bool, float, vector, matrix, struct and array
  //   types
  // - base_type_ids_to_pointers maps every such base type to the sequence
  //   of all pointer types that have storage class |storage_class| and the
  //   given base type as their pointee type.  The sequence may be empty for
  //   some base types if no pointers to those types are defined for the given
  //   storage class, and the sequence will have multiple elements if there are
  //   repeated pointer declarations for the same base type and storage class.
  std::pair<std::vector<uint32_t>, std::map<uint32_t, std::vector<uint32_t>>>
  GetAvailableBaseTypesAndPointers(SpvStorageClass storage_class) const;

  // Given a type id, |scalar_or_composite_type_id|, which must correspond to
  // some scalar or composite type, returns the result id of an instruction
  // defining a constant of the given type that is zero or false at everywhere.
  // If such an instruction does not yet exist, transformations are applied to
  // add it.
  //
  // Examples:
  // --------------+-------------------------------
  //   TYPE        | RESULT is id corresponding to
  // --------------+-------------------------------
  //   bool        | false
  // --------------+-------------------------------
  //   bvec4       | (false, false, false, false)
  // --------------+-------------------------------
  //   float       | 0.0
  // --------------+-------------------------------
  //   vec2        | (0.0, 0.0)
  // --------------+-------------------------------
  //   int[3]      | [0, 0, 0]
  // --------------+-------------------------------
  //   struct S {  |
  //     int i;    | S(0, false, (0u, 0u))
  //     bool b;   |
  //     uint2 u;  |
  //   }           |
  // --------------+-------------------------------
  uint32_t FindOrCreateZeroConstant(uint32_t scalar_or_composite_type_id);

 private:
  // Array, matrix and vector are *homogeneous* composite types in the sense
  // that every component of one of these types has the same type.  Given a
  // homogeneous composite type instruction, |composite_type_instruction|,
  // returns the id of a composite constant instruction for which every element
  // is zero/false.  If such an instruction does not yet exist, transformations
  // are applied to add it.
  uint32_t GetZeroConstantForHomogeneousComposite(
      const opt::Instruction& composite_type_instruction,
      uint32_t component_type_id, uint32_t num_components);

  // Helper to find an existing composite constant instruction of the given
  // composite type with the given constant components, or to apply
  // transformations to create such an instruction if it does not yet exist.
  // Parameter |composite_type_instruction| must be a composite type
  // instruction.  The parameters |constants| and |constant_ids| must have the
  // same size, and it must be the case that for each i, |constant_ids[i]| is
  // the result id of an instruction that defines |constants[i]|.
  uint32_t FindOrCreateCompositeConstant(
      const opt::Instruction& composite_type_instruction,
      const std::vector<const opt::analysis::Constant*>& constants,
      const std::vector<uint32_t>& constant_ids);

  opt::IRContext* ir_context_;
  FactManager* fact_manager_;
  FuzzerContext* fuzzer_context_;
  protobufs::TransformationSequence* transformations_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_FUZZER_PASS_H_

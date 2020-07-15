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

#ifndef SOURCE_FUZZ_FUZZER_UTIL_H_
#define SOURCE_FUZZ_FUZZER_UTIL_H_

#include <vector>

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/basic_block.h"
#include "source/opt/instruction.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

// Provides types and global utility methods for use by the fuzzer
namespace fuzzerutil {

// Function type that produces a SPIR-V module.
using ModuleSupplier = std::function<std::unique_ptr<opt::IRContext>()>;

// Returns true if and only if the module does not define the given id.
bool IsFreshId(opt::IRContext* context, uint32_t id);

// Updates the module's id bound if needed so that it is large enough to
// account for the given id.
void UpdateModuleIdBound(opt::IRContext* context, uint32_t id);

// Return the block with id |maybe_block_id| if it exists, and nullptr
// otherwise.
opt::BasicBlock* MaybeFindBlock(opt::IRContext* context,
                                uint32_t maybe_block_id);

// When adding an edge from |bb_from| to |bb_to| (which are assumed to be blocks
// in the same function), it is important to supply |bb_to| with ids that can be
// used to augment OpPhi instructions in the case that there is not already such
// an edge.  This function returns true if and only if the ids provided in
// |phi_ids| suffice for this purpose,
bool PhiIdsOkForNewEdge(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids);

// Requires that a boolean constant with value |condition_value| is available,
// that PhiIdsOkForNewEdge(context, bb_from, bb_to, phi_ids) holds, and that
// bb_from ends with "OpBranch %some_block".  Turns OpBranch into
// "OpBranchConditional |condition_value| ...", such that control will branch
// to %some_block, with |bb_to| being the unreachable alternative.  Updates
// OpPhi instructions in |bb_to| using |phi_ids| so that the new edge is valid.
void AddUnreachableEdgeAndUpdateOpPhis(
    opt::IRContext* context, opt::BasicBlock* bb_from, opt::BasicBlock* bb_to,
    bool condition_value,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& phi_ids);

// Returns true if and only if |maybe_loop_header_id| is a loop header and
// |block_id| is in the continue construct of the associated loop.
bool BlockIsInLoopContinueConstruct(opt::IRContext* context, uint32_t block_id,
                                    uint32_t maybe_loop_header_id);

// If |block| contains |inst|, an iterator for |inst| is returned.
// Otherwise |block|->end() is returned.
opt::BasicBlock::iterator GetIteratorForInstruction(
    opt::BasicBlock* block, const opt::Instruction* inst);

// Returns true if and only if there is a path to |bb| from the entry block of
// the function that contains |bb|.
bool BlockIsReachableInItsFunction(opt::IRContext* context,
                                   opt::BasicBlock* bb);

// Determines whether it is OK to insert an instruction with opcode |opcode|
// before |instruction_in_block|.
bool CanInsertOpcodeBeforeInstruction(
    SpvOp opcode, const opt::BasicBlock::iterator& instruction_in_block);

// Determines whether it is OK to make a synonym of |inst|.
bool CanMakeSynonymOf(opt::IRContext* ir_context, opt::Instruction* inst);

// Determines whether the given type is a composite; that is: an array, matrix,
// struct or vector.
bool IsCompositeType(const opt::analysis::Type* type);

// Returns a vector containing the same elements as |repeated_field|.
std::vector<uint32_t> RepeatedFieldToVector(
    const google::protobuf::RepeatedField<uint32_t>& repeated_field);

// Given a type id, |base_object_type_id|, returns 0 if the type is not a
// composite type or if |index| is too large to be used as an index into the
// composite.  Otherwise returns the type id of the type associated with the
// composite's index.
//
// Example: if |base_object_type_id| is 10, and we have:
//
// %10 = OpTypeStruct %3 %4 %5
//
// then 3 will be returned if |index| is 0, 5 if |index| is 2, and 0 if index
// is 3 or larger.
uint32_t WalkOneCompositeTypeIndex(opt::IRContext* context,
                                   uint32_t base_object_type_id,
                                   uint32_t index);

// Given a type id, |base_object_type_id|, checks that the given sequence of
// |indices| is suitable for indexing into this type.  Returns the id of the
// type of the final sub-object reached via the indices if they are valid, and
// 0 otherwise.
uint32_t WalkCompositeTypeIndices(
    opt::IRContext* context, uint32_t base_object_type_id,
    const google::protobuf::RepeatedField<google::protobuf::uint32>& indices);

// Returns the number of members associated with |struct_type_instruction|,
// which must be an OpStructType instruction.
uint32_t GetNumberOfStructMembers(
    const opt::Instruction& struct_type_instruction);

// Returns the constant size of the array associated with
// |array_type_instruction|, which must be an OpArrayType instruction. Returns
// 0 if there is not a static size.
uint32_t GetArraySize(const opt::Instruction& array_type_instruction,
                      opt::IRContext* context);

// Returns true if and only if |context| is valid, according to the validator
// instantiated with |validator_options|.
bool IsValid(opt::IRContext* context, spv_validator_options validator_options);

// Returns a clone of |context|, by writing |context| to a binary and then
// parsing it again.
std::unique_ptr<opt::IRContext> CloneIRContext(opt::IRContext* context);

// Returns true if and only if |id| is the id of a type that is not a function
// type.
bool IsNonFunctionTypeId(opt::IRContext* ir_context, uint32_t id);

// Returns true if and only if |block_id| is a merge block or continue target
bool IsMergeOrContinue(opt::IRContext* ir_context, uint32_t block_id);

// Returns the result id of an instruction of the form:
//  %id = OpTypeFunction |type_ids|
// or 0 if no such instruction exists.
uint32_t FindFunctionType(opt::IRContext* ir_context,
                          const std::vector<uint32_t>& type_ids);

// Returns a type instruction (OpTypeFunction) for |function|.
// Returns |nullptr| if type is not found.
opt::Instruction* GetFunctionType(opt::IRContext* context,
                                  const opt::Function* function);

// Returns the function with result id |function_id|, or |nullptr| if no such
// function exists.
opt::Function* FindFunction(opt::IRContext* ir_context, uint32_t function_id);

// Returns |true| if one of entry points has function id |function_id|.
bool FunctionIsEntryPoint(opt::IRContext* context, uint32_t function_id);

// Checks whether |id| is available (according to dominance rules) at the use
// point defined by input operand |use_input_operand_index| of
// |use_instruction|.
bool IdIsAvailableAtUse(opt::IRContext* context,
                        opt::Instruction* use_instruction,
                        uint32_t use_input_operand_index, uint32_t id);

// Checks whether |id| is available (according to dominance rules) at the
// program point directly before |instruction|.
bool IdIsAvailableBeforeInstruction(opt::IRContext* context,
                                    opt::Instruction* instruction, uint32_t id);

// Returns true if and only if |instruction| is an OpFunctionParameter
// associated with |function|.
bool InstructionIsFunctionParameter(opt::Instruction* instruction,
                                    opt::Function* function);

// Returns the type id of the instruction defined by |result_id|, or 0 if there
// is no such result id.
uint32_t GetTypeId(opt::IRContext* context, uint32_t result_id);

// Given |pointer_type_inst|, which must be an OpTypePointer instruction,
// returns the id of the associated pointee type.
uint32_t GetPointeeTypeIdFromPointerType(opt::Instruction* pointer_type_inst);

// Given |pointer_type_id|, which must be the id of a pointer type, returns the
// id of the associated pointee type.
uint32_t GetPointeeTypeIdFromPointerType(opt::IRContext* context,
                                         uint32_t pointer_type_id);

// Given |pointer_type_inst|, which must be an OpTypePointer instruction,
// returns the associated storage class.
SpvStorageClass GetStorageClassFromPointerType(
    opt::Instruction* pointer_type_inst);

// Given |pointer_type_id|, which must be the id of a pointer type, returns the
// associated storage class.
SpvStorageClass GetStorageClassFromPointerType(opt::IRContext* context,
                                               uint32_t pointer_type_id);

// Returns the id of a pointer with pointee type |pointee_type_id| and storage
// class |storage_class|, if it exists, and 0 otherwise.
uint32_t MaybeGetPointerType(opt::IRContext* context, uint32_t pointee_type_id,
                             SpvStorageClass storage_class);

// Returns true if and only if |type| is one of the types for which it is legal
// to have an OpConstantNull value.
bool IsNullConstantSupported(const opt::analysis::Type& type);

// Returns true if and only if the SPIR-V version being used requires that
// global variables accessed in the static call graph of an entry point need
// to be listed in that entry point's interface.
bool GlobalVariablesMustBeDeclaredInEntryPointInterfaces(
    const opt::IRContext* context);

// Adds |id| into the interface of every entry point of the shader.
// Does nothing if SPIR-V doesn't require global variables, that are accessed
// from an entry point function, to be listed in that function's interface.
void AddVariableIdToEntryPointInterfaces(opt::IRContext* context, uint32_t id);

// Adds a global variable with storage class |storage_class| to the module, with
// type |type_id| and either no initializer or |initializer_id| as an
// initializer, depending on whether |initializer_id| is 0. The global variable
// has result id |result_id|. Updates module's id bound to accommodate for
// |result_id|.
//
// - |type_id| must be the id of a pointer type with the same storage class as
//   |storage_class|.
// - |storage_class| must be Private or Workgroup.
// - |initializer_id| must be 0 if |storage_class| is Workgroup, and otherwise
//   may either be 0 or the id of a constant whose type is the pointee type of
//   |type_id|.
void AddGlobalVariable(opt::IRContext* context, uint32_t result_id,
                       uint32_t type_id, SpvStorageClass storage_class,
                       uint32_t initializer_id);

// Adds an instruction to the start of |function_id|, of the form:
//   |result_id| = OpVariable |type_id| Function |initializer_id|.
// Updates module's id bound to accommodate for |result_id|.
//
// - |type_id| must be the id of a pointer type with Function storage class.
// - |initializer_id| must be the id of a constant with the same type as the
//   pointer's pointee type.
// - |function_id| must be the id of a function.
void AddLocalVariable(opt::IRContext* context, uint32_t result_id,
                      uint32_t type_id, uint32_t function_id,
                      uint32_t initializer_id);

// Returns true if the vector |arr| has duplicates.
bool HasDuplicates(const std::vector<uint32_t>& arr);

// Checks that the given vector |arr| contains a permutation of a range
// [lo, hi]. That being said, all elements in the range are present without
// duplicates. If |arr| is empty, returns true iff |lo > hi|.
bool IsPermutationOfRange(const std::vector<uint32_t>& arr, uint32_t lo,
                          uint32_t hi);

// Returns OpFunctionParameter instructions corresponding to the function
// with result id |function_id|.
std::vector<opt::Instruction*> GetParameters(opt::IRContext* ir_context,
                                             uint32_t function_id);

// Creates new OpTypeFunction instruction in the module. |type_ids| may not be
// empty. It may not contain result ids of OpTypeFunction instructions.
// |type_ids[i]| may not be a result id of OpTypeVoid instruction for |i >= 1|.
// |result_id| may not equal to 0. Updates module's id bound to accommodate for
// |result_id|.
void AddFunctionType(opt::IRContext* ir_context, uint32_t result_id,
                     const std::vector<uint32_t>& type_ids);

// Returns a result id of an OpTypeFunction instruction in the module. Creates a
// new instruction if required and returns |result_id|. type_ids| may not be
// empty. It may not contain result ids of OpTypeFunction instructions.
// |type_ids[i]| may not be a result id of OpTypeVoid instruction for |i >= 1|.
// |result_id| must not be equal to 0. Updates module's id bound to accommodate
// for |result_id|.
uint32_t FindOrCreateFunctionType(opt::IRContext* ir_context,
                                  uint32_t result_id,
                                  const std::vector<uint32_t>& type_ids);

// Returns a result id of an OpTypeInt instruction if present. Returns 0
// otherwise.
uint32_t MaybeGetIntegerType(opt::IRContext* ir_context, uint32_t width,
                             bool is_signed);

// Returns a result id of an OpTypeFloat instruction if present. Returns 0
// otherwise.
uint32_t MaybeGetFloatType(opt::IRContext* ir_context, uint32_t width);

// Returns a result id of an OpTypeVector instruction if present. Returns 0
// otherwise. |component_type_id| must be a valid result id of an OpTypeInt,
// OpTypeFloat or OpTypeBool instruction in the module. |element_count| must be
// in the range [2, 4].
uint32_t MaybeGetVectorType(opt::IRContext* ir_context,
                            uint32_t component_type_id, uint32_t element_count);

// Returns a result id of an OpTypeStruct instruction if present. Returns 0
// otherwise. |component_type_ids| may not contain a result id of an
// OpTypeFunction.
uint32_t MaybeGetStructType(opt::IRContext* ir_context,
                            const std::vector<uint32_t>& component_type_ids);

// Recursive definition is the following:
// - if |scalar_or_composite_type_id| is a result id of a scalar type - returns
//   a result id of the following constants (depending on the type): int -> 0,
//   float -> 0.0, bool -> false.
// - otherwise, returns a result id of an OpConstantComposite instruction.
//   Every component of the composite constant is looked up by calling this
//   function with the type id of that component.
// Returns 0 if no such instruction is present in the module.
uint32_t MaybeGetZeroConstant(opt::IRContext* ir_context,
                              uint32_t scalar_or_composite_type_id);

// Returns the result id of an OpConstant instruction. |scalar_type_id| must be
// a result id of a scalar type (i.e. int, float or bool). Returns 0 if no such
// instruction is present in the module.
uint32_t MaybeGetScalarConstant(opt::IRContext* ir_context,
                                const std::vector<uint32_t>& words,
                                uint32_t scalar_type_id);

// Returns the result id of an OpConstantComposite instruction.
// |composite_type_id| must be a result id of a composite type (i.e. vector,
// matrix, struct or array). Returns 0 if no such instruction is present in the
// module.
uint32_t MaybeGetCompositeConstant(opt::IRContext* ir_context,
                                   const std::vector<uint32_t>& component_ids,
                                   uint32_t composite_type_id);

// Returns the result id of an OpConstant instruction of integral type.
// Returns 0 if no such instruction or type is present in the module.
uint32_t MaybeGetIntegerConstant(opt::IRContext* ir_context,
                                 const std::vector<uint32_t>& words,
                                 uint32_t width, bool is_signed);

// Returns the result id of an OpConstant instruction of floating-point type.
// Returns 0 if no such instruction or type is present in the module.
uint32_t MaybeGetFloatConstant(opt::IRContext* ir_context,
                               const std::vector<uint32_t>& words,
                               uint32_t width);

// Returns the id of a boolean constant with value |value| if it exists in the
// module, or 0 otherwise.
uint32_t MaybeGetBoolConstant(opt::IRContext* context, bool value);

// Creates a new OpTypeInt instruction in the module. Updates module's id bound
// to accommodate for |result_id|.
void AddIntegerType(opt::IRContext* ir_context, uint32_t result_id,
                    uint32_t width, bool is_signed);

// Creates a new OpTypeFloat instruction in the module. Updates module's id
// bound to accommodate for |result_id|.
void AddFloatType(opt::IRContext* ir_context, uint32_t result_id,
                  uint32_t width);

// Creates a new OpTypeVector instruction in the module. |component_type_id|
// must be a valid result id of an OpTypeInt, OpTypeFloat or OpTypeBool
// instruction in the module. |element_count| must be in the range [2, 4].
// Updates module's id bound to accommodate for |result_id|.
void AddVectorType(opt::IRContext* ir_context, uint32_t result_id,
                   uint32_t component_type_id, uint32_t element_count);

// Creates a new OpTypeStruct instruction in the module. Updates module's id
// bound to accommodate for |result_id|. |component_type_ids| may not contain
// a result id of an OpTypeFunction.
void AddStructType(opt::IRContext* ir_context, uint32_t result_id,
                   const std::vector<uint32_t>& component_type_ids);

// Returns a result id of an OpTypeInt instruction in the module. Creates a new
// instruction with |result_id|, if no required OpTypeInt is present in the
// module, and returns |result_id|. Updates module's id bound to accommodate for
// |result_id|.
uint32_t FindOrCreateIntegerType(opt::IRContext* ir_context, uint32_t result_id,
                                 uint32_t width, bool is_signed);

// Returns a result id of an OpTypeFloat instruction in the module. Creates a
// new instruction with |result_id|, if no required OpTypeFloat is present in
// the module, and returns |result_id|. Updates module's id bound
// to accommodate for |result_id|.
uint32_t FindOrCreateFloatType(opt::IRContext* ir_context, uint32_t result_id,
                               uint32_t width);

// Returns a result id of an OpTypeVector instruction in the module. Creates a
// new instruction with |result_id|, if no required OpTypeVector is present in
// the module, and returns |result_id|. |component_type_id| must be a valid
// result id of an OpTypeInt, OpTypeFloat or OpTypeBool instruction in the
// module. |element_count| must be in the range [2, 4]. Updates module's id
// bound to accommodate for |result_id|.
uint32_t FindOrCreateVectorType(opt::IRContext* ir_context, uint32_t result_id,
                                uint32_t component_type_id,
                                uint32_t element_count);

// Returns a result id of an OpTypeStruct instruction in the module. Creates a
// new instruction with |result_id|, if no required OpTypeStruct is present in
// the module, and returns |result_id|. Updates module's id bound
// to accommodate for |result_id|. |component_type_ids| may not contain a result
// id of an OpTypeFunction.
uint32_t FindOrCreateStructType(
    opt::IRContext* ir_context, uint32_t result_id,
    const std::vector<uint32_t>& component_type_ids);

}  // namespace fuzzerutil

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_FUZZER_UTIL_H_

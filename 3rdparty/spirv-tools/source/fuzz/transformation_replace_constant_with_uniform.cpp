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

#include "source/fuzz/transformation_replace_constant_with_uniform.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/uniform_buffer_element_descriptor.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

namespace {

std::unique_ptr<opt::Instruction> MakeAccessChainInstruction(
    const protobufs::TransformationReplaceConstantWithUniform& message,
    spvtools::opt::IRContext* context, uint32_t constant_type_id) {
  // The input operands for the access chain.
  opt::Instruction::OperandList operands_for_access_chain;

  opt::Instruction* uniform_variable =
      FindUniformVariable(message.uniform_descriptor(), context, false);

  // The first input operand is the id of the uniform variable.
  operands_for_access_chain.push_back(
      {SPV_OPERAND_TYPE_ID, {uniform_variable->result_id()}});

  // The other input operands are the ids of the constants used to index into
  // the uniform. The uniform buffer descriptor specifies a series of literals;
  // for each we find the id of the instruction that defines it, and add these
  // instruction ids as operands.
  opt::analysis::Integer int_type(32, true);
  auto registered_int_type =
      context->get_type_mgr()->GetRegisteredType(&int_type)->AsInteger();
  auto int_type_id = context->get_type_mgr()->GetId(&int_type);
  for (auto index : message.uniform_descriptor().index()) {
    opt::analysis::IntConstant int_constant(registered_int_type, {index});
    auto constant_id = context->get_constant_mgr()->FindDeclaredConstant(
        &int_constant, int_type_id);
    operands_for_access_chain.push_back({SPV_OPERAND_TYPE_ID, {constant_id}});
  }

  // The type id for the access chain is a uniform pointer with base type
  // matching the given constant id type.
  auto type_and_pointer_type = context->get_type_mgr()->GetTypeAndPointerType(
      constant_type_id, SpvStorageClassUniform);
  assert(type_and_pointer_type.first != nullptr);
  assert(type_and_pointer_type.second != nullptr);
  auto pointer_to_uniform_constant_type_id =
      context->get_type_mgr()->GetId(type_and_pointer_type.second.get());

  return MakeUnique<opt::Instruction>(
      context, SpvOpAccessChain, pointer_to_uniform_constant_type_id,
      message.fresh_id_for_access_chain(), operands_for_access_chain);
}

std::unique_ptr<opt::Instruction> MakeLoadInstruction(
    const protobufs::TransformationReplaceConstantWithUniform& message,
    spvtools::opt::IRContext* context, uint32_t constant_type_id) {
  opt::Instruction::OperandList operands_for_load = {
      {SPV_OPERAND_TYPE_ID, {message.fresh_id_for_access_chain()}}};
  return MakeUnique<opt::Instruction>(context, SpvOpLoad, constant_type_id,
                                      message.fresh_id_for_load(),
                                      operands_for_load);
}

}  // namespace

bool IsApplicable(
    const protobufs::TransformationReplaceConstantWithUniform& message,
    spvtools::opt::IRContext* context,
    const spvtools::fuzz::FactManager& fact_manager) {
  // The following is really an invariant of the transformation rather than
  // merely a requirement of the precondition.  We check it here since we cannot
  // check it in the message constructor.
  assert(message.fresh_id_for_access_chain() != message.fresh_id_for_load() &&
         "Fresh ids for access chain and load result cannot be the same.");

  // The ids for the access chain and load instructions must both be fresh.
  if (!fuzzerutil::IsFreshId(context, message.fresh_id_for_access_chain())) {
    return false;
  }
  if (!fuzzerutil::IsFreshId(context, message.fresh_id_for_load())) {
    return false;
  }

  // The id specified in the id use descriptor must be that of a declared scalar
  // constant.
  auto declared_constant = context->get_constant_mgr()->FindDeclaredConstant(
      message.id_use_descriptor().id_of_interest());
  if (!declared_constant) {
    return false;
  }
  if (!declared_constant->AsScalarConstant()) {
    return false;
  }

  // The fact manager needs to believe that the uniform data element described
  // by the uniform buffer element descriptor will hold a scalar value.
  auto constant_id_associated_with_uniform =
      fact_manager.GetConstantFromUniformDescriptor(
          context, message.uniform_descriptor());
  if (!constant_id_associated_with_uniform) {
    return false;
  }
  auto constant_associated_with_uniform =
      context->get_constant_mgr()->FindDeclaredConstant(
          constant_id_associated_with_uniform);
  assert(constant_associated_with_uniform &&
         "The constant should be present in the module.");
  if (!constant_associated_with_uniform->AsScalarConstant()) {
    return false;
  }

  // The types and values of the scalar value held in the id specified by the id
  // use descriptor and in the uniform data element specified by the uniform
  // buffer element descriptor need to match on both type and value.
  if (!declared_constant->type()->IsSame(
          constant_associated_with_uniform->type())) {
    return false;
  }
  if (declared_constant->AsScalarConstant()->words() !=
      constant_associated_with_uniform->AsScalarConstant()->words()) {
    return false;
  }

  // The id use descriptor must identify some instruction with respect to the
  // module.
  auto instruction_using_constant =
      transformation::FindInstruction(message.id_use_descriptor(), context);
  if (!instruction_using_constant) {
    return false;
  }

  // The module needs to have a uniform pointer type suitable for indexing into
  // the uniform variable, i.e. matching the type of the constant we wish to
  // replace with a uniform.
  opt::analysis::Pointer pointer_to_type_of_constant(declared_constant->type(),
                                                     SpvStorageClassUniform);
  if (!context->get_type_mgr()->GetId(&pointer_to_type_of_constant)) {
    return false;
  }

  // In order to index into the uniform, the module has got to contain the int32
  // type, plus an OpConstant for each of the indices of interest.
  opt::analysis::Integer int_type(32, true);
  if (!context->get_type_mgr()->GetId(&int_type)) {
    return false;
  }
  auto registered_int_type =
      context->get_type_mgr()->GetRegisteredType(&int_type)->AsInteger();
  auto int_type_id = context->get_type_mgr()->GetId(&int_type);
  for (auto index : message.uniform_descriptor().index()) {
    opt::analysis::IntConstant int_constant(registered_int_type, {index});
    if (!context->get_constant_mgr()->FindDeclaredConstant(&int_constant,
                                                           int_type_id)) {
      return false;
    }
  }

  return true;
}

void Apply(const protobufs::TransformationReplaceConstantWithUniform& message,
           spvtools::opt::IRContext* context,
           spvtools::fuzz::FactManager* /*unused*/) {
  // Get the instruction that contains the id use we wish to replace.
  auto instruction_containing_constant_use =
      transformation::FindInstruction(message.id_use_descriptor(), context);
  assert(instruction_containing_constant_use &&
         "Precondition requires that the id use can be found.");
  assert(instruction_containing_constant_use->GetSingleWordInOperand(
             message.id_use_descriptor().in_operand_index()) ==
             message.id_use_descriptor().id_of_interest() &&
         "Does not appear to be a usage of the desired id.");

  // The id of the type for the constant whose use we wish to replace.
  auto constant_type_id =
      context->get_def_use_mgr()
          ->GetDef(message.id_use_descriptor().id_of_interest())
          ->type_id();

  // Add an access chain instruction to target the uniform element.
  instruction_containing_constant_use->InsertBefore(
      MakeAccessChainInstruction(message, context, constant_type_id));

  // Add a load from this access chain.
  instruction_containing_constant_use->InsertBefore(
      MakeLoadInstruction(message, context, constant_type_id));

  // Adjust the instruction containing the usage of the constant so that this
  // usage refers instead to the result of the load.
  instruction_containing_constant_use->SetInOperand(
      message.id_use_descriptor().in_operand_index(),
      {message.fresh_id_for_load()});

  // Update the module id bound to reflect the new instructions.
  fuzzerutil::UpdateModuleIdBound(context, message.fresh_id_for_load());
  fuzzerutil::UpdateModuleIdBound(context, message.fresh_id_for_access_chain());

  context->InvalidateAnalysesExceptFor(opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::TransformationReplaceConstantWithUniform
MakeTransformationReplaceConstantWithUniform(
    protobufs::IdUseDescriptor id_use,
    protobufs::UniformBufferElementDescriptor uniform_descriptor,
    uint32_t fresh_id_for_access_chain, uint32_t fresh_id_for_load) {
  protobufs::TransformationReplaceConstantWithUniform result;
  *result.mutable_id_use_descriptor() = std::move(id_use);
  *result.mutable_uniform_descriptor() = std::move(uniform_descriptor);
  result.set_fresh_id_for_access_chain(fresh_id_for_access_chain);
  result.set_fresh_id_for_load(fresh_id_for_load);
  return result;
}

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

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

#include "source/fuzz/transformation_inline_function.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationInlineFunction::TransformationInlineFunction(
    const spvtools::fuzz::protobufs::TransformationInlineFunction& message)
    : message_(message) {}

TransformationInlineFunction::TransformationInlineFunction(
    uint32_t function_call_id,
    const std::map<uint32_t, uint32_t>& result_id_map) {
  message_.set_function_call_id(function_call_id);
  *message_.mutable_result_id_map() =
      fuzzerutil::MapToRepeatedUInt32Pair(result_id_map);
}

bool TransformationInlineFunction::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  // The values in the |message_.result_id_map| must be all fresh and all
  // distinct.
  const auto result_id_map =
      fuzzerutil::RepeatedUInt32PairToMap(message_.result_id_map());
  std::set<uint32_t> ids_used_by_this_transformation;
  for (auto& pair : result_id_map) {
    if (!CheckIdIsFreshAndNotUsedByThisTransformation(
            pair.second, ir_context, &ids_used_by_this_transformation)) {
      return false;
    }
  }

  // |function_call_instruction| must be suitable for inlining.
  auto* function_call_instruction =
      ir_context->get_def_use_mgr()->GetDef(message_.function_call_id());
  if (!IsSuitableForInlining(ir_context, function_call_instruction)) {
    return false;
  }

  // |function_call_instruction| must be the penultimate instruction in its
  // block and its block termination instruction must be an OpBranch. This
  // avoids the case where the penultimate instruction is an OpLoopMerge, which
  // would make the back-edge block not branch to the loop header.
  auto* function_call_instruction_block =
      ir_context->get_instr_block(function_call_instruction);
  if (function_call_instruction !=
          &*--function_call_instruction_block->tail() ||
      function_call_instruction_block->terminator()->opcode() != SpvOpBranch) {
    return false;
  }

  auto* called_function = fuzzerutil::FindFunction(
      ir_context, function_call_instruction->GetSingleWordInOperand(0));
  for (auto& block : *called_function) {
    // Since the entry block label will not be inlined, only the remaining
    // labels must have a corresponding value in the map.
    if (&block != &*called_function->entry() &&
        !result_id_map.count(block.GetLabel()->result_id())) {
      return false;
    }

    // |result_id_map| must have an entry for every result id in the called
    // function.
    for (auto& instruction : block) {
      // If |instruction| has result id, then it must have a mapped id in
      // |result_id_map|.
      if (instruction.HasResultId() &&
          !result_id_map.count(instruction.result_id())) {
        return false;
      }
    }
  }

  // |result_id_map| must not contain an entry for any parameter of the function
  // that is being inlined.
  bool found_entry_for_parameter = false;
  called_function->ForEachParam(
      [&result_id_map, &found_entry_for_parameter](opt::Instruction* param) {
        if (result_id_map.count(param->result_id())) {
          found_entry_for_parameter = true;
        }
      });
  return !found_entry_for_parameter;
}

void TransformationInlineFunction::Apply(
    opt::IRContext* ir_context, TransformationContext* /*unused*/) const {
  auto* function_call_instruction =
      ir_context->get_def_use_mgr()->GetDef(message_.function_call_id());
  auto* caller_function =
      ir_context->get_instr_block(function_call_instruction)->GetParent();
  auto* called_function = fuzzerutil::FindFunction(
      ir_context, function_call_instruction->GetSingleWordInOperand(0));
  const auto result_id_map =
      fuzzerutil::RepeatedUInt32PairToMap(message_.result_id_map());
  auto* successor_block = ir_context->cfg()->block(
      ir_context->get_instr_block(function_call_instruction)
          ->terminator()
          ->GetSingleWordInOperand(0));

  // Inline the |called_function| entry block.
  for (auto& entry_block_instruction : *called_function->entry()) {
    opt::Instruction* inlined_instruction = nullptr;

    if (entry_block_instruction.opcode() == SpvOpVariable) {
      // All OpVariable instructions in a function must be in the first block
      // in the function.
      inlined_instruction = caller_function->begin()->begin()->InsertBefore(
          MakeUnique<opt::Instruction>(entry_block_instruction));
    } else {
      inlined_instruction = function_call_instruction->InsertBefore(
          MakeUnique<opt::Instruction>(entry_block_instruction));
    }

    AdaptInlinedInstruction(ir_context, inlined_instruction);
  }

  // Inline the |called_function| non-entry blocks.
  for (auto& block : *called_function) {
    if (&block == &*called_function->entry()) {
      continue;
    }

    auto* cloned_block = block.Clone(ir_context);
    cloned_block = caller_function->InsertBasicBlockBefore(
        std::unique_ptr<opt::BasicBlock>(cloned_block), successor_block);
    cloned_block->SetParent(caller_function);
    cloned_block->GetLabel()->SetResultId(
        result_id_map.at(cloned_block->GetLabel()->result_id()));
    fuzzerutil::UpdateModuleIdBound(ir_context,
                                    cloned_block->GetLabel()->result_id());

    for (auto& inlined_instruction : *cloned_block) {
      AdaptInlinedInstruction(ir_context, &inlined_instruction);
    }
  }

  // Removes the function call instruction and its block termination instruction
  // from |caller_function|.
  ir_context->KillInst(
      ir_context->get_instr_block(function_call_instruction)->terminator());
  ir_context->KillInst(function_call_instruction);

  // Since the SPIR-V module has changed, no analyses must be validated.
  ir_context->InvalidateAnalysesExceptFor(
      opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationInlineFunction::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_inline_function() = message_;
  return result;
}

bool TransformationInlineFunction::IsSuitableForInlining(
    opt::IRContext* ir_context, opt::Instruction* function_call_instruction) {
  // |function_call_instruction| must be defined and must be an OpFunctionCall
  // instruction.
  if (!function_call_instruction ||
      function_call_instruction->opcode() != SpvOpFunctionCall) {
    return false;
  }

  // If |function_call_instruction| return type is void, then
  // |function_call_instruction| must not have uses.
  if (ir_context->get_type_mgr()
          ->GetType(function_call_instruction->type_id())
          ->AsVoid() &&
      ir_context->get_def_use_mgr()->NumUses(function_call_instruction) != 0) {
    return false;
  }

  // |called_function| must not have an early return.
  auto called_function = fuzzerutil::FindFunction(
      ir_context, function_call_instruction->GetSingleWordInOperand(0));
  if (called_function->HasEarlyReturn()) {
    return false;
  }

  // |called_function| must not use OpKill or OpUnreachable.
  if (fuzzerutil::FunctionContainsOpKillOrUnreachable(*called_function)) {
    return false;
  }

  return true;
}

void TransformationInlineFunction::AdaptInlinedInstruction(
    opt::IRContext* ir_context,
    opt::Instruction* instruction_to_be_inlined) const {
  auto* function_call_instruction =
      ir_context->get_def_use_mgr()->GetDef(message_.function_call_id());
  auto* called_function = fuzzerutil::FindFunction(
      ir_context, function_call_instruction->GetSingleWordInOperand(0));
  const auto result_id_map =
      fuzzerutil::RepeatedUInt32PairToMap(message_.result_id_map());

  // Replaces the operand ids with their mapped result ids.
  instruction_to_be_inlined->ForEachInId([called_function,
                                          function_call_instruction,
                                          &result_id_map](uint32_t* id) {
    // If |id| is mapped, then set it to its mapped value.
    if (result_id_map.count(*id)) {
      *id = result_id_map.at(*id);
      return;
    }

    uint32_t parameter_index = 0;
    called_function->ForEachParam(
        [id, function_call_instruction,
         &parameter_index](opt::Instruction* parameter_instruction) {
          // If the id is a function parameter, then set it to the
          // parameter value passed in the function call instruction.
          if (*id == parameter_instruction->result_id()) {
            // We do + 1 because the first in-operand for OpFunctionCall is
            // the function id that is being called.
            *id = function_call_instruction->GetSingleWordInOperand(
                parameter_index + 1);
          }
          parameter_index++;
        });
  });

  // If |instruction_to_be_inlined| has result id, then set it to its mapped
  // value.
  if (instruction_to_be_inlined->HasResultId()) {
    assert(result_id_map.count(instruction_to_be_inlined->result_id()) &&
           "Result id must be mapped to a fresh id.");
    instruction_to_be_inlined->SetResultId(
        result_id_map.at(instruction_to_be_inlined->result_id()));
    fuzzerutil::UpdateModuleIdBound(ir_context,
                                    instruction_to_be_inlined->result_id());
  }

  // The return instruction will be changed into an OpBranch to the basic
  // block that follows the block containing the function call.
  if (spvOpcodeIsReturn(instruction_to_be_inlined->opcode())) {
    uint32_t successor_block_id =
        ir_context->get_instr_block(function_call_instruction)
            ->terminator()
            ->GetSingleWordInOperand(0);
    switch (instruction_to_be_inlined->opcode()) {
      case SpvOpReturn:
        instruction_to_be_inlined->AddOperand(
            {SPV_OPERAND_TYPE_ID, {successor_block_id}});
        break;
      case SpvOpReturnValue: {
        instruction_to_be_inlined->InsertBefore(MakeUnique<opt::Instruction>(
            ir_context, SpvOpCopyObject, function_call_instruction->type_id(),
            function_call_instruction->result_id(),
            opt::Instruction::OperandList(
                {{SPV_OPERAND_TYPE_ID,
                  {instruction_to_be_inlined->GetSingleWordOperand(0)}}})));
        instruction_to_be_inlined->SetInOperand(0, {successor_block_id});
        break;
      }
      default:
        break;
    }
    instruction_to_be_inlined->SetOpcode(SpvOpBranch);
  }
}

}  // namespace fuzz
}  // namespace spvtools

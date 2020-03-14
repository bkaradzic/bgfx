// Copyright (c) 2020 Google LLC
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

#include "source/fuzz/fuzzer_pass_add_function_calls.h"

#include "source/fuzz/call_graph.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/transformation_add_global_variable.h"
#include "source/fuzz/transformation_add_local_variable.h"
#include "source/fuzz/transformation_function_call.h"

namespace spvtools {
namespace fuzz {

FuzzerPassAddFunctionCalls::FuzzerPassAddFunctionCalls(
    opt::IRContext* ir_context, FactManager* fact_manager,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, fact_manager, fuzzer_context, transformations) {}

FuzzerPassAddFunctionCalls::~FuzzerPassAddFunctionCalls() = default;

void FuzzerPassAddFunctionCalls::Apply() {
  ForEachInstructionWithInstructionDescriptor(
      [this](opt::Function* function, opt::BasicBlock* block,
             opt::BasicBlock::iterator inst_it,
             const protobufs::InstructionDescriptor& instruction_descriptor)
          -> void {
        // Check whether it is legitimate to insert a function call before the
        // instruction.
        if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpFunctionCall,
                                                          inst_it)) {
          return;
        }

        // Randomly decide whether to try inserting a function call here.
        if (!GetFuzzerContext()->ChoosePercentage(
                GetFuzzerContext()->GetChanceOfCallingFunction())) {
          return;
        }

        // Compute the module's call graph - we don't cache it since it may
        // change each time we apply a transformation.  If this proves to be
        // a bottleneck the call graph data structure could be made updatable.
        CallGraph call_graph(GetIRContext());

        // Gather all the non-entry point functions different from this
        // function.  It is important to ignore entry points as a function
        // cannot be an entry point and the target of an OpFunctionCall
        // instruction.  We ignore this function to avoid direct recursion.
        std::vector<opt::Function*> candidate_functions;
        for (auto& other_function : *GetIRContext()->module()) {
          if (&other_function != function &&
              !fuzzerutil::FunctionIsEntryPoint(GetIRContext(),
                                                other_function.result_id())) {
            candidate_functions.push_back(&other_function);
          }
        }

        // Choose a function to call, at random, by considering candidate
        // functions until a suitable one is found.
        opt::Function* chosen_function = nullptr;
        while (!candidate_functions.empty()) {
          opt::Function* candidate_function =
              GetFuzzerContext()->RemoveAtRandomIndex(&candidate_functions);
          if (!GetFactManager()->BlockIsDead(block->id()) &&
              !GetFactManager()->FunctionIsLivesafe(
                  candidate_function->result_id())) {
            // Unless in a dead block, only livesafe functions can be invoked
            continue;
          }
          if (call_graph.GetIndirectCallees(candidate_function->result_id())
                  .count(function->result_id())) {
            // Calling this function could lead to indirect recursion
            continue;
          }
          chosen_function = candidate_function;
          break;
        }

        if (!chosen_function) {
          // No suitable function was found to call.  (This can happen, for
          // instance, if the current function is the only function in the
          // module.)
          return;
        }

        ApplyTransformation(TransformationFunctionCall(
            GetFuzzerContext()->GetFreshId(), chosen_function->result_id(),
            ChooseFunctionCallArguments(*chosen_function, function, block,
                                        inst_it),
            instruction_descriptor));
      });
}

std::map<uint32_t, std::vector<opt::Instruction*>>
FuzzerPassAddFunctionCalls::GetAvailableInstructionsSuitableForActualParameters(
    opt::Function* function, opt::BasicBlock* block,
    const opt::BasicBlock::iterator& inst_it) {
  // Find all instructions in scope that could potentially be used as actual
  // parameters.  Weed out unsuitable pointer arguments immediately.
  std::vector<opt::Instruction*> potentially_suitable_instructions =
      FindAvailableInstructions(
          function, block, inst_it,
          [this, block](opt::IRContext* context,
                        opt::Instruction* inst) -> bool {
            if (!inst->HasResultId() || !inst->type_id()) {
              // An instruction needs a result id and type in order
              // to be suitable as an actual parameter.
              return false;
            }
            if (context->get_def_use_mgr()->GetDef(inst->type_id())->opcode() ==
                SpvOpTypePointer) {
              switch (inst->opcode()) {
                case SpvOpFunctionParameter:
                case SpvOpVariable:
                  // Function parameters and variables are the only
                  // kinds of pointer that can be used as actual
                  // parameters.
                  break;
                default:
                  return false;
              }
              if (!GetFactManager()->BlockIsDead(block->id()) &&
                  !GetFactManager()->PointeeValueIsIrrelevant(
                      inst->result_id())) {
                // We can only pass a pointer as an actual parameter
                // if the pointee value for the pointer is irrelevant,
                // or if the block from which we would make the
                // function call is dead.
                return false;
              }
            }
            return true;
          });

  // Group all the instructions that are potentially viable as function actual
  // parameters by their result types.
  std::map<uint32_t, std::vector<opt::Instruction*>> result;
  for (auto inst : potentially_suitable_instructions) {
    if (result.count(inst->type_id()) == 0) {
      // This is the first instruction of this type we have seen, so populate
      // the map with an entry.
      result.insert({inst->type_id(), {}});
    }
    // Add the instruction to the sequence of instructions already associated
    // with this type.
    result.at(inst->type_id()).push_back(inst);
  }
  return result;
}

std::vector<uint32_t> FuzzerPassAddFunctionCalls::ChooseFunctionCallArguments(
    const opt::Function& callee, opt::Function* caller_function,
    opt::BasicBlock* caller_block,
    const opt::BasicBlock::iterator& caller_inst_it) {
  auto type_to_available_instructions =
      GetAvailableInstructionsSuitableForActualParameters(
          caller_function, caller_block, caller_inst_it);

  opt::Instruction* function_type = GetIRContext()->get_def_use_mgr()->GetDef(
      callee.DefInst().GetSingleWordInOperand(1));
  assert(function_type->opcode() == SpvOpTypeFunction &&
         "The function type does not have the expected opcode.");
  std::vector<uint32_t> result;
  for (uint32_t arg_index = 1; arg_index < function_type->NumInOperands();
       arg_index++) {
    auto arg_type_id =
        GetIRContext()
            ->get_def_use_mgr()
            ->GetDef(function_type->GetSingleWordInOperand(arg_index))
            ->result_id();
    if (type_to_available_instructions.count(arg_type_id)) {
      std::vector<opt::Instruction*>& candidate_arguments =
          type_to_available_instructions.at(arg_type_id);
      // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3177) The value
      //  selected here is arbitrary.  We should consider adding this
      //  information as a fact so that the passed parameter could be
      //  transformed/changed.
      result.push_back(candidate_arguments[GetFuzzerContext()->RandomIndex(
                                               candidate_arguments)]
                           ->result_id());
    } else {
      // We don't have a suitable id in scope to pass, so we must make
      // something up.
      auto type_instruction =
          GetIRContext()->get_def_use_mgr()->GetDef(arg_type_id);

      if (type_instruction->opcode() == SpvOpTypePointer) {
        // In the case of a pointer, we make a new variable, at function
        // or global scope depending on the storage class of the
        // pointer.

        // Get a fresh id for the new variable.
        uint32_t fresh_variable_id = GetFuzzerContext()->GetFreshId();

        // The id of this variable is what we pass as the parameter to
        // the call.
        result.push_back(fresh_variable_id);

        // Now bring the variable into existence.
        if (type_instruction->GetSingleWordInOperand(0) ==
            SpvStorageClassFunction) {
          // Add a new zero-initialized local variable to the current
          // function, noting that its pointee value is irrelevant.
          ApplyTransformation(TransformationAddLocalVariable(
              fresh_variable_id, arg_type_id, caller_function->result_id(),
              FindOrCreateZeroConstant(
                  type_instruction->GetSingleWordInOperand(1)),
              true));
        } else {
          assert(type_instruction->GetSingleWordInOperand(0) ==
                     SpvStorageClassPrivate &&
                 "Only Function and Private storage classes are "
                 "supported at present.");
          // Add a new zero-initialized global variable to the module,
          // noting that its pointee value is irrelevant.
          ApplyTransformation(TransformationAddGlobalVariable(
              fresh_variable_id, arg_type_id,
              FindOrCreateZeroConstant(
                  type_instruction->GetSingleWordInOperand(1)),
              true));
        }
      } else {
        // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3177): We use
        //  constant zero for the parameter, but could consider adding a fact
        //  to allow further passes to obfuscate it.
        result.push_back(FindOrCreateZeroConstant(arg_type_id));
      }
    }
  }
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

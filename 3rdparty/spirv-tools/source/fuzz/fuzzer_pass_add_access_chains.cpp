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

#include "source/fuzz/fuzzer_pass_add_access_chains.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/transformation_access_chain.h"

namespace spvtools {
namespace fuzz {

FuzzerPassAddAccessChains::FuzzerPassAddAccessChains(
    opt::IRContext* ir_context, FactManager* fact_manager,
    FuzzerContext* fuzzer_context,
    protobufs::TransformationSequence* transformations)
    : FuzzerPass(ir_context, fact_manager, fuzzer_context, transformations) {}

FuzzerPassAddAccessChains::~FuzzerPassAddAccessChains() = default;

void FuzzerPassAddAccessChains::Apply() {
  ForEachInstructionWithInstructionDescriptor(
      [this](opt::Function* function, opt::BasicBlock* block,
             opt::BasicBlock::iterator inst_it,
             const protobufs::InstructionDescriptor& instruction_descriptor)
          -> void {
        assert(inst_it->opcode() ==
                   instruction_descriptor.target_instruction_opcode() &&
               "The opcode of the instruction we might insert before must be "
               "the same as the opcode in the descriptor for the instruction");

        // Check whether it is legitimate to insert an access chain
        // instruction before this instruction.
        if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpAccessChain,
                                                          inst_it)) {
          return;
        }

        // Randomly decide whether to try inserting a load here.
        if (!GetFuzzerContext()->ChoosePercentage(
                GetFuzzerContext()->GetChanceOfAddingAccessChain())) {
          return;
        }

        // Get all of the pointers that are currently in scope, excluding
        // explicitly null and undefined pointers.
        std::vector<opt::Instruction*> relevant_pointer_instructions =
            FindAvailableInstructions(
                function, block, inst_it,
                [](opt::IRContext* context,
                   opt::Instruction* instruction) -> bool {
                  if (!instruction->result_id() || !instruction->type_id()) {
                    // A pointer needs both a result and type id.
                    return false;
                  }
                  switch (instruction->opcode()) {
                    case SpvOpConstantNull:
                    case SpvOpUndef:
                      // Do not allow making an access chain from a null or
                      // undefined pointer.  (We can eliminate these cases
                      // before actually checking that the instruction is a
                      // pointer.)
                      return false;
                    default:
                      break;
                  }
                  // If the instruction has pointer type, we can legitimately
                  // make an access chain from it.
                  return context->get_def_use_mgr()
                             ->GetDef(instruction->type_id())
                             ->opcode() == SpvOpTypePointer;
                });

        // At this point, |relevant_instructions| contains all the pointers
        // we might think of making an access chain from.
        if (relevant_pointer_instructions.empty()) {
          return;
        }

        auto chosen_pointer =
            relevant_pointer_instructions[GetFuzzerContext()->RandomIndex(
                relevant_pointer_instructions)];
        std::vector<uint32_t> index_ids;
        auto pointer_type = GetIRContext()->get_def_use_mgr()->GetDef(
            chosen_pointer->type_id());
        uint32_t subobject_type_id = pointer_type->GetSingleWordInOperand(1);
        while (true) {
          auto subobject_type =
              GetIRContext()->get_def_use_mgr()->GetDef(subobject_type_id);
          if (!spvOpcodeIsComposite(subobject_type->opcode())) {
            break;
          }
          if (!GetFuzzerContext()->ChoosePercentage(
                  GetFuzzerContext()
                      ->GetChanceOfGoingDeeperWhenMakingAccessChain())) {
            break;
          }
          uint32_t bound;
          switch (subobject_type->opcode()) {
            case SpvOpTypeArray:
              bound = fuzzerutil::GetArraySize(*subobject_type, GetIRContext());
              break;
            case SpvOpTypeMatrix:
            case SpvOpTypeVector:
              bound = subobject_type->GetSingleWordInOperand(1);
              break;
            case SpvOpTypeStruct:
              bound = fuzzerutil::GetNumberOfStructMembers(*subobject_type);
              break;
            default:
              assert(false && "Not a composite type opcode.");
              // Set the bound to a value in order to keep release compilers
              // happy.
              bound = 0;
              break;
          }
          if (bound == 0) {
            // It is possible for a composite type to legitimately have zero
            // sub-components, at least in the case of a struct, which
            // can have no fields.
            break;
          }

          // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/3179) We
          //  could allow non-constant indices when looking up non-structs,
          //  using clamping to ensure they are in-bounds.
          uint32_t index_value =
              GetFuzzerContext()->GetRandomIndexForAccessChain(bound);
          index_ids.push_back(FindOrCreate32BitIntegerConstant(
              index_value, GetFuzzerContext()->ChooseEven()));
          switch (subobject_type->opcode()) {
            case SpvOpTypeArray:
            case SpvOpTypeMatrix:
            case SpvOpTypeVector:
              subobject_type_id = subobject_type->GetSingleWordInOperand(0);
              break;
            case SpvOpTypeStruct:
              subobject_type_id =
                  subobject_type->GetSingleWordInOperand(index_value);
              break;
            default:
              assert(false && "Not a composite type opcode.");
          }
        }
        // The transformation we are about to create will only apply if a
        // pointer suitable for the access chain's result type exists, so we
        // create one if it does not.
        FindOrCreatePointerType(subobject_type_id,
                                static_cast<SpvStorageClass>(
                                    pointer_type->GetSingleWordInOperand(0)));
        // Apply the transformation to add an access chain.
        ApplyTransformation(TransformationAccessChain(
            GetFuzzerContext()->GetFreshId(), chosen_pointer->result_id(),
            index_ids, instruction_descriptor));
      });
}

}  // namespace fuzz
}  // namespace spvtools

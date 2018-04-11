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

#include "private_to_local_pass.h"

#include "ir_context.h"

namespace {
const uint32_t kVariableStorageClassInIdx = 0;
const uint32_t kSpvTypePointerTypeIdInIdx = 1;
}  // namespace

namespace spvtools {
namespace opt {

Pass::Status PrivateToLocalPass::Process(ir::IRContext* c) {
  InitializeProcessing(c);
  bool modified = false;

  // Private variables require the shader capability.  If this is not a shader,
  // there is no work to do.
  if (context()->get_feature_mgr()->HasCapability(SpvCapabilityAddresses))
    return Status::SuccessWithoutChange;

  std::vector<std::pair<ir::Instruction*, ir::Function*>> variables_to_move;
  for (auto& inst : context()->types_values()) {
    if (inst.opcode() != SpvOpVariable) {
      continue;
    }

    if (inst.GetSingleWordInOperand(kVariableStorageClassInIdx) !=
        SpvStorageClassPrivate) {
      continue;
    }

    ir::Function* target_function = FindLocalFunction(inst);
    if (target_function != nullptr) {
      variables_to_move.push_back({&inst, target_function});
    }
  }

  modified = !variables_to_move.empty();
  for (auto p : variables_to_move) {
    MoveVariable(p.first, p.second);
  }

  return (modified ? Status::SuccessWithChange : Status::SuccessWithoutChange);
}

ir::Function* PrivateToLocalPass::FindLocalFunction(
    const ir::Instruction& inst) const {
  bool found_first_use = false;
  ir::Function* target_function = nullptr;
  context()->get_def_use_mgr()->ForEachUser(
      inst.result_id(),
      [&target_function, &found_first_use, this](ir::Instruction* use) {
        ir::BasicBlock* current_block = context()->get_instr_block(use);
        if (current_block == nullptr) {
          return;
        }

        if (!IsValidUse(use)) {
          found_first_use = true;
          target_function = nullptr;
          return;
        }
        ir::Function* current_function = current_block->GetParent();
        if (!found_first_use) {
          found_first_use = true;
          target_function = current_function;
        } else if (target_function != current_function) {
          target_function = nullptr;
        }
      });
  return target_function;
}  // namespace opt

void PrivateToLocalPass::MoveVariable(ir::Instruction* variable,
                                      ir::Function* function) {
  // The variable needs to be removed from the global section, and placed in the
  // header of the function.  First step remove from the global list.
  variable->RemoveFromList();
  std::unique_ptr<ir::Instruction> var(variable);  // Take ownership.
  context()->ForgetUses(variable);

  // Update the storage class of the variable.
  variable->SetInOperand(kVariableStorageClassInIdx, {SpvStorageClassFunction});

  // Update the type as well.
  uint32_t new_type_id = GetNewType(variable->type_id());
  variable->SetResultType(new_type_id);

  // Place the variable at the start of the first basic block.
  context()->AnalyzeUses(variable);
  function->begin()->begin()->InsertBefore(move(var));

  // Update uses where the type may have changed.
  UpdateUses(variable->result_id());
}

uint32_t PrivateToLocalPass::GetNewType(uint32_t old_type_id) {
  auto type_mgr = context()->get_type_mgr();
  ir::Instruction* old_type_inst = get_def_use_mgr()->GetDef(old_type_id);
  uint32_t pointee_type_id =
      old_type_inst->GetSingleWordInOperand(kSpvTypePointerTypeIdInIdx);
  uint32_t new_type_id =
      type_mgr->FindPointerToType(pointee_type_id, SpvStorageClassFunction);
  return new_type_id;
}

bool PrivateToLocalPass::IsValidUse(const ir::Instruction* inst) const {
  // The cases in this switch have to match the cases in |UpdateUse|.
  // If we don't know how to update it, it is not valid.
  switch (inst->opcode()) {
    case SpvOpLoad:
    case SpvOpStore:
    case SpvOpImageTexelPointer:  // Treat like a load
      return true;
    case SpvOpAccessChain:
      return context()->get_def_use_mgr()->WhileEachUser(
          inst, [this](const ir::Instruction* user) {
            if (!IsValidUse(user)) return false;
            return true;
          });
    case SpvOpName:
      return true;
    default:
      return spvOpcodeIsDecoration(inst->opcode());
  }
}

void PrivateToLocalPass::UpdateUse(ir::Instruction* inst) {
  // The cases in this switch have to match the cases in |IsValidUse|.  If we
  // don't think it is valid, the optimization will not view the variable as a
  // candidate, and therefore the use will not be updated.
  switch (inst->opcode()) {
    case SpvOpLoad:
    case SpvOpStore:
    case SpvOpImageTexelPointer:  // Treat like a load
      // The type is fine because it is the type pointed to, and that does not
      // change.
      break;
    case SpvOpAccessChain:
      context()->ForgetUses(inst);
      inst->SetResultType(GetNewType(inst->type_id()));
      context()->AnalyzeUses(inst);

      // Update uses where the type may have changed.
      UpdateUses(inst->result_id());
      break;
    case SpvOpName:
      break;
    default:
      assert(spvOpcodeIsDecoration(inst->opcode()) &&
             "Do not know how to update the type for this instruction.");
      break;
  }
}
void PrivateToLocalPass::UpdateUses(uint32_t id) {
  std::vector<ir::Instruction*> uses;
  this->context()->get_def_use_mgr()->ForEachUser(
      id, [&uses](ir::Instruction* use) { uses.push_back(use); });

  for (ir::Instruction* use : uses) {
    UpdateUse(use);
  }
}

}  // namespace opt
}  // namespace spvtools

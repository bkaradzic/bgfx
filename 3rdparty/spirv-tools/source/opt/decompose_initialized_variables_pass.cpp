// Copyright (c) 2019 Google LLC.
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

#include "source/opt/decompose_initialized_variables_pass.h"

#include "source/opt/ir_context.h"

namespace spvtools {
namespace opt {

using inst_iterator = InstructionList::iterator;

namespace {

bool HasInitializer(Instruction* inst) {
  if (inst->opcode() != SpvOpVariable) return false;
  if (inst->NumOperands() < 4) return false;

  return true;
}

}  // namespace

Pass::Status DecomposeInitializedVariablesPass::Process() {
  auto* module = context()->module();
  bool changed = false;

  // TODO(zoddicus): Handle 'Output' variables
  // TODO(zoddicus): Handle 'Private' variables

  // Handle 'Function' variables
  for (auto func = module->begin(); func != module->end(); ++func) {
    auto block = func->entry().get();
    std::vector<Instruction*> new_stores;

    auto last_var = block->begin();
    for (auto iter = block->begin();
         iter != block->end() && iter->opcode() == SpvOpVariable; ++iter) {
      last_var = iter;
      Instruction* inst = &(*iter);
      if (!HasInitializer(inst)) continue;

      changed = true;
      auto var_id = inst->result_id();
      auto val_id = inst->GetOperand(3).words[0];
      Instruction* store_inst = new Instruction(
          context(), SpvOpStore, 0, 0,
          {{SPV_OPERAND_TYPE_ID, {var_id}}, {SPV_OPERAND_TYPE_ID, {val_id}}});
      new_stores.push_back(store_inst);
      iter->RemoveOperand(3);
      get_def_use_mgr()->UpdateDefUse(&*iter);
    }

    for (auto store = new_stores.begin(); store != new_stores.end(); ++store) {
      context()->AnalyzeDefUse(*store);
      context()->set_instr_block(*store, block);
      (*store)->InsertAfter(&*last_var);
      last_var = *store;
    }
  }

  return changed ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

}  // namespace opt
}  // namespace spvtools

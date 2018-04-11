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

#include "constants.h"
#include "ir_context.h"

#include <unordered_map>
#include <vector>

namespace spvtools {
namespace opt {
namespace analysis {

float Constant::GetFloat() const {
  assert(type()->AsFloat() != nullptr && type()->AsFloat()->width() == 32);

  if (const FloatConstant* fc = AsFloatConstant()) {
    return fc->GetFloatValue();
  } else {
    assert(AsNullConstant() && "Must be a floating point constant.");
    return 0.0f;
  }
}

double Constant::GetDouble() const {
  assert(type()->AsFloat() != nullptr && type()->AsFloat()->width() == 64);

  if (const FloatConstant* fc = AsFloatConstant()) {
    return fc->GetDoubleValue();
  } else {
    assert(AsNullConstant() && "Must be a floating point constant.");
    return 0.0;
  }
}

uint32_t Constant::GetU32() const {
  assert(type()->AsInteger() != nullptr);
  assert(type()->AsInteger()->width() == 32);

  if (const IntConstant* ic = AsIntConstant()) {
    return ic->GetU32BitValue();
  } else {
    assert(AsNullConstant() && "Must be an integer constant.");
    return 0u;
  }
}

uint64_t Constant::GetU64() const {
  assert(type()->AsInteger() != nullptr);
  assert(type()->AsInteger()->width() == 64);

  if (const IntConstant* ic = AsIntConstant()) {
    return ic->GetU64BitValue();
  } else {
    assert(AsNullConstant() && "Must be an integer constant.");
    return 0u;
  }
}

int32_t Constant::GetS32() const {
  assert(type()->AsInteger() != nullptr);
  assert(type()->AsInteger()->width() == 32);

  if (const IntConstant* ic = AsIntConstant()) {
    return ic->GetS32BitValue();
  } else {
    assert(AsNullConstant() && "Must be an integer constant.");
    return 0;
  }
}

int64_t Constant::GetS64() const {
  assert(type()->AsInteger() != nullptr);
  assert(type()->AsInteger()->width() == 64);

  if (const IntConstant* ic = AsIntConstant()) {
    return ic->GetS64BitValue();
  } else {
    assert(AsNullConstant() && "Must be an integer constant.");
    return 0;
  }
}

ConstantManager::ConstantManager(ir::IRContext* ctx) : ctx_(ctx) {
  // Populate the constant table with values from constant declarations in the
  // module.  The values of each OpConstant declaration is the identity
  // assignment (i.e., each constant is its own value).
  for (const auto& inst : ctx_->module()->GetConstants()) {
    MapInst(inst);
  }
}

Type* ConstantManager::GetType(const ir::Instruction* inst) const {
  return context()->get_type_mgr()->GetType(inst->type_id());
}

std::vector<const Constant*> ConstantManager::GetOperandConstants(
    ir::Instruction* inst) const {
  std::vector<const Constant*> constants;
  for (uint32_t i = 0; i < inst->NumInOperands(); i++) {
    const ir::Operand* operand = &inst->GetInOperand(i);
    if (operand->type != SPV_OPERAND_TYPE_ID) {
      constants.push_back(nullptr);
    } else {
      uint32_t id = operand->words[0];
      const analysis::Constant* constant = FindDeclaredConstant(id);
      constants.push_back(constant);
    }
  }
  return constants;
}

std::vector<const Constant*> ConstantManager::GetConstantsFromIds(
    const std::vector<uint32_t>& ids) const {
  std::vector<const Constant*> constants;
  for (uint32_t id : ids) {
    if (const Constant* c = FindDeclaredConstant(id)) {
      constants.push_back(c);
    } else {
      return {};
    }
  }
  return constants;
}

ir::Instruction* ConstantManager::BuildInstructionAndAddToModule(
    const Constant* new_const, ir::Module::inst_iterator* pos,
    uint32_t type_id) {
  uint32_t new_id = context()->TakeNextId();
  auto new_inst = CreateInstruction(new_id, new_const, type_id);
  if (!new_inst) {
    return nullptr;
  }
  auto* new_inst_ptr = new_inst.get();
  *pos = pos->InsertBefore(std::move(new_inst));
  ++(*pos);
  context()->get_def_use_mgr()->AnalyzeInstDefUse(new_inst_ptr);
  MapConstantToInst(new_const, new_inst_ptr);
  return new_inst_ptr;
}

ir::Instruction* ConstantManager::GetDefiningInstruction(
    const Constant* c, ir::Module::inst_iterator* pos) {
  uint32_t decl_id = FindDeclaredConstant(c);
  if (decl_id == 0) {
    auto iter = context()->types_values_end();
    if (pos == nullptr) pos = &iter;
    return BuildInstructionAndAddToModule(c, pos);
  } else {
    auto def = context()->get_def_use_mgr()->GetDef(decl_id);
    assert(def != nullptr);
    return def;
  }
}

const Constant* ConstantManager::CreateConstant(
    const Type* type, const std::vector<uint32_t>& literal_words_or_ids) const {
  if (literal_words_or_ids.size() == 0) {
    // Constant declared with OpConstantNull
    return new NullConstant(type);
  } else if (auto* bt = type->AsBool()) {
    assert(literal_words_or_ids.size() == 1 &&
           "Bool constant should be declared with one operand");
    return new BoolConstant(bt, literal_words_or_ids.front());
  } else if (auto* it = type->AsInteger()) {
    return new IntConstant(it, literal_words_or_ids);
  } else if (auto* ft = type->AsFloat()) {
    return new FloatConstant(ft, literal_words_or_ids);
  } else if (auto* vt = type->AsVector()) {
    auto components = GetConstantsFromIds(literal_words_or_ids);
    if (components.empty()) return nullptr;
    // All components of VectorConstant must be of type Bool, Integer or Float.
    if (!std::all_of(components.begin(), components.end(),
                     [](const Constant* c) {
                       if (c->type()->AsBool() || c->type()->AsInteger() ||
                           c->type()->AsFloat()) {
                         return true;
                       } else {
                         return false;
                       }
                     }))
      return nullptr;
    // All components of VectorConstant must be in the same type.
    const auto* component_type = components.front()->type();
    if (!std::all_of(components.begin(), components.end(),
                     [&component_type](const Constant* c) {
                       if (c->type() == component_type) return true;
                       return false;
                     }))
      return nullptr;
    return new VectorConstant(vt, components);
  } else if (auto* mt = type->AsMatrix()) {
    auto components = GetConstantsFromIds(literal_words_or_ids);
    if (components.empty()) return nullptr;
    return new MatrixConstant(mt, components);
  } else if (auto* st = type->AsStruct()) {
    auto components = GetConstantsFromIds(literal_words_or_ids);
    if (components.empty()) return nullptr;
    return new StructConstant(st, components);
  } else if (auto* at = type->AsArray()) {
    auto components = GetConstantsFromIds(literal_words_or_ids);
    if (components.empty()) return nullptr;
    return new ArrayConstant(at, components);
  } else {
    return nullptr;
  }
}

const Constant* ConstantManager::GetConstantFromInst(ir::Instruction* inst) {
  std::vector<uint32_t> literal_words_or_ids;

  // Collect the constant defining literals or component ids.
  for (uint32_t i = 0; i < inst->NumInOperands(); i++) {
    literal_words_or_ids.insert(literal_words_or_ids.end(),
                                inst->GetInOperand(i).words.begin(),
                                inst->GetInOperand(i).words.end());
  }

  switch (inst->opcode()) {
    // OpConstant{True|False} have the value embedded in the opcode. So they
    // are not handled by the for-loop above. Here we add the value explicitly.
    case SpvOp::SpvOpConstantTrue:
      literal_words_or_ids.push_back(true);
      break;
    case SpvOp::SpvOpConstantFalse:
      literal_words_or_ids.push_back(false);
      break;
    case SpvOp::SpvOpConstantNull:
    case SpvOp::SpvOpConstant:
    case SpvOp::SpvOpConstantComposite:
    case SpvOp::SpvOpSpecConstantComposite:
      break;
    default:
      return nullptr;
  }

  return GetConstant(GetType(inst), literal_words_or_ids);
}

std::unique_ptr<ir::Instruction> ConstantManager::CreateInstruction(
    uint32_t id, const Constant* c, uint32_t type_id) const {
  uint32_t type =
      (type_id == 0) ? context()->get_type_mgr()->GetId(c->type()) : type_id;
  if (c->AsNullConstant()) {
    return MakeUnique<ir::Instruction>(context(), SpvOp::SpvOpConstantNull,
                                       type, id,
                                       std::initializer_list<ir::Operand>{});
  } else if (const BoolConstant* bc = c->AsBoolConstant()) {
    return MakeUnique<ir::Instruction>(
        context(),
        bc->value() ? SpvOp::SpvOpConstantTrue : SpvOp::SpvOpConstantFalse,
        type, id, std::initializer_list<ir::Operand>{});
  } else if (const IntConstant* ic = c->AsIntConstant()) {
    return MakeUnique<ir::Instruction>(
        context(), SpvOp::SpvOpConstant, type, id,
        std::initializer_list<ir::Operand>{ir::Operand(
            spv_operand_type_t::SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER,
            ic->words())});
  } else if (const FloatConstant* fc = c->AsFloatConstant()) {
    return MakeUnique<ir::Instruction>(
        context(), SpvOp::SpvOpConstant, type, id,
        std::initializer_list<ir::Operand>{ir::Operand(
            spv_operand_type_t::SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER,
            fc->words())});
  } else if (const CompositeConstant* cc = c->AsCompositeConstant()) {
    return CreateCompositeInstruction(id, cc, type_id);
  } else {
    return nullptr;
  }
}

std::unique_ptr<ir::Instruction> ConstantManager::CreateCompositeInstruction(
    uint32_t result_id, const CompositeConstant* cc, uint32_t type_id) const {
  std::vector<ir::Operand> operands;
  for (const Constant* component_const : cc->GetComponents()) {
    uint32_t id = FindDeclaredConstant(component_const);
    if (id == 0) {
      // Cannot get the id of the component constant, while all components
      // should have been added to the module prior to the composite constant.
      // Cannot create OpConstantComposite instruction in this case.
      return nullptr;
    }
    operands.emplace_back(spv_operand_type_t::SPV_OPERAND_TYPE_ID,
                          std::initializer_list<uint32_t>{id});
  }
  uint32_t type =
      (type_id == 0) ? context()->get_type_mgr()->GetId(cc->type()) : type_id;
  return MakeUnique<ir::Instruction>(context(), SpvOp::SpvOpConstantComposite,
                                     type, result_id, std::move(operands));
}

const Constant* ConstantManager::GetConstant(
    const Type* type, const std::vector<uint32_t>& literal_words_or_ids) {
  auto cst = CreateConstant(type, literal_words_or_ids);
  return cst ? RegisterConstant(cst) : nullptr;
}

}  // namespace analysis
}  // namespace opt
}  // namespace spvtools

// Copyright (c) 2016 Google Inc.
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

#include "instruction.h"

#include <initializer_list>

#include "disassemble.h"
#include "fold.h"
#include "ir_context.h"
#include "reflect.h"

namespace spvtools {
namespace ir {

namespace {
// Indices used to get particular operands out of instructions using InOperand.
const uint32_t kTypeImageDimIndex = 1;
const uint32_t kLoadBaseIndex = 0;
const uint32_t kVariableStorageClassIndex = 0;
const uint32_t kTypeImageSampledIndex = 5;
}  // namespace

Instruction::Instruction(IRContext* c)
    : utils::IntrusiveNodeBase<Instruction>(),
      context_(c),
      opcode_(SpvOpNop),
      type_id_(0),
      result_id_(0),
      unique_id_(c->TakeNextUniqueId()) {}

Instruction::Instruction(IRContext* c, SpvOp op)
    : utils::IntrusiveNodeBase<Instruction>(),
      context_(c),
      opcode_(op),
      type_id_(0),
      result_id_(0),
      unique_id_(c->TakeNextUniqueId()) {}

Instruction::Instruction(IRContext* c, const spv_parsed_instruction_t& inst,
                         std::vector<Instruction>&& dbg_line)
    : context_(c),
      opcode_(static_cast<SpvOp>(inst.opcode)),
      type_id_(inst.type_id),
      result_id_(inst.result_id),
      unique_id_(c->TakeNextUniqueId()),
      dbg_line_insts_(std::move(dbg_line)) {
  assert((!IsDebugLineInst(opcode_) || dbg_line.empty()) &&
         "Op(No)Line attaching to Op(No)Line found");
  for (uint32_t i = 0; i < inst.num_operands; ++i) {
    const auto& current_payload = inst.operands[i];
    std::vector<uint32_t> words(
        inst.words + current_payload.offset,
        inst.words + current_payload.offset + current_payload.num_words);
    operands_.emplace_back(current_payload.type, std::move(words));
  }
}

Instruction::Instruction(IRContext* c, SpvOp op, uint32_t ty_id,
                         uint32_t res_id,
                         const std::vector<Operand>& in_operands)
    : utils::IntrusiveNodeBase<Instruction>(),
      context_(c),
      opcode_(op),
      type_id_(ty_id),
      result_id_(res_id),
      unique_id_(c->TakeNextUniqueId()),
      operands_() {
  if (type_id_ != 0) {
    operands_.emplace_back(spv_operand_type_t::SPV_OPERAND_TYPE_TYPE_ID,
                           std::initializer_list<uint32_t>{type_id_});
  }
  if (result_id_ != 0) {
    operands_.emplace_back(spv_operand_type_t::SPV_OPERAND_TYPE_RESULT_ID,
                           std::initializer_list<uint32_t>{result_id_});
  }
  operands_.insert(operands_.end(), in_operands.begin(), in_operands.end());
}

Instruction::Instruction(Instruction&& that)
    : utils::IntrusiveNodeBase<Instruction>(),
      opcode_(that.opcode_),
      type_id_(that.type_id_),
      result_id_(that.result_id_),
      unique_id_(that.unique_id_),
      operands_(std::move(that.operands_)),
      dbg_line_insts_(std::move(that.dbg_line_insts_)) {}

Instruction& Instruction::operator=(Instruction&& that) {
  opcode_ = that.opcode_;
  type_id_ = that.type_id_;
  result_id_ = that.result_id_;
  unique_id_ = that.unique_id_;
  operands_ = std::move(that.operands_);
  dbg_line_insts_ = std::move(that.dbg_line_insts_);
  return *this;
}

Instruction* Instruction::Clone(IRContext* c) const {
  Instruction* clone = new Instruction(c);
  clone->opcode_ = opcode_;
  clone->type_id_ = type_id_;
  clone->result_id_ = result_id_;
  clone->unique_id_ = c->TakeNextUniqueId();
  clone->operands_ = operands_;
  clone->dbg_line_insts_ = dbg_line_insts_;
  return clone;
}

uint32_t Instruction::GetSingleWordOperand(uint32_t index) const {
  const auto& words = GetOperand(index).words;
  assert(words.size() == 1 && "expected the operand only taking one word");
  return words.front();
}

uint32_t Instruction::NumInOperandWords() const {
  uint32_t size = 0;
  for (uint32_t i = TypeResultIdCount(); i < operands_.size(); ++i)
    size += static_cast<uint32_t>(operands_[i].words.size());
  return size;
}

void Instruction::ToBinaryWithoutAttachedDebugInsts(
    std::vector<uint32_t>* binary) const {
  const uint32_t num_words = 1 + NumOperandWords();
  binary->push_back((num_words << 16) | static_cast<uint16_t>(opcode_));
  for (const auto& operand : operands_)
    binary->insert(binary->end(), operand.words.begin(), operand.words.end());
}

void Instruction::ReplaceOperands(const std::vector<Operand>& new_operands) {
  operands_.clear();
  operands_.insert(operands_.begin(), new_operands.begin(), new_operands.end());
  operands_.shrink_to_fit();
}

bool Instruction::IsReadOnlyLoad() const {
  if (IsLoad()) {
    ir::Instruction* address_def = GetBaseAddress();
    if (!address_def || address_def->opcode() != SpvOpVariable) {
      return false;
    }
    return address_def->IsReadOnlyVariable();
  }
  return false;
}

Instruction* Instruction::GetBaseAddress() const {
  assert((IsLoad() || opcode() == SpvOpStore || opcode() == SpvOpAccessChain ||
          opcode() == SpvOpInBoundsAccessChain || opcode() == SpvOpCopyObject ||
          opcode() == SpvOpImageTexelPointer) &&
         "GetBaseAddress should only be called on instructions that take a "
         "pointer or image.");
  uint32_t base = GetSingleWordInOperand(kLoadBaseIndex);
  ir::Instruction* base_inst = context()->get_def_use_mgr()->GetDef(base);
  bool done = false;
  while (!done) {
    switch (base_inst->opcode()) {
      case SpvOpAccessChain:
      case SpvOpInBoundsAccessChain:
      case SpvOpPtrAccessChain:
      case SpvOpInBoundsPtrAccessChain:
      case SpvOpImageTexelPointer:
      case SpvOpCopyObject:
        // All of these instructions have the base pointer use a base pointer
        // in in-operand 0.
        base = base_inst->GetSingleWordInOperand(0);
        base_inst = context()->get_def_use_mgr()->GetDef(base);
        break;
      default:
        done = true;
        break;
    }
  }

  switch (opcode()) {
    case SpvOpLoad:
    case SpvOpStore:
    case SpvOpAccessChain:
    case SpvOpInBoundsAccessChain:
    case SpvOpCopyObject:
      // A load or store through a pointer.
      assert(base_inst->IsValidBasePointer() &&
             "We cannot have a base pointer come from this load");
      break;
    default:
      // A load or store of an image.
      assert(base_inst->IsValidBaseImage() && "We are expecting an image.");
      break;
  }
  return base_inst;
}

bool Instruction::IsReadOnlyVariable() const {
  if (context()->get_feature_mgr()->HasCapability(SpvCapabilityShader))
    return IsReadOnlyVariableShaders();
  else
    return IsReadOnlyVariableKernel();
}

bool Instruction::IsVulkanStorageImage() const {
  if (opcode() != SpvOpTypePointer) {
    return false;
  }

  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  if (storage_class != SpvStorageClassUniformConstant) {
    return false;
  }

  ir::Instruction* base_type =
      context()->get_def_use_mgr()->GetDef(GetSingleWordInOperand(1));
  if (base_type->opcode() != SpvOpTypeImage) {
    return false;
  }

  if (base_type->GetSingleWordInOperand(kTypeImageDimIndex) == SpvDimBuffer) {
    return false;
  }

  // Check if the image is sampled.  If we do not know for sure that it is,
  // then assume it is a storage image.
  auto s = base_type->GetSingleWordInOperand(kTypeImageSampledIndex);
  return s != 1;
}

bool Instruction::IsVulkanSampledImage() const {
  if (opcode() != SpvOpTypePointer) {
    return false;
  }

  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  if (storage_class != SpvStorageClassUniformConstant) {
    return false;
  }

  ir::Instruction* base_type =
      context()->get_def_use_mgr()->GetDef(GetSingleWordInOperand(1));
  if (base_type->opcode() != SpvOpTypeImage) {
    return false;
  }

  if (base_type->GetSingleWordInOperand(kTypeImageDimIndex) == SpvDimBuffer) {
    return false;
  }

  // Check if the image is sampled.  If we know for sure that it is,
  // then return true.
  auto s = base_type->GetSingleWordInOperand(kTypeImageSampledIndex);
  return s == 1;
}

bool Instruction::IsVulkanStorageTexelBuffer() const {
  if (opcode() != SpvOpTypePointer) {
    return false;
  }

  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  if (storage_class != SpvStorageClassUniformConstant) {
    return false;
  }

  ir::Instruction* base_type =
      context()->get_def_use_mgr()->GetDef(GetSingleWordInOperand(1));
  if (base_type->opcode() != SpvOpTypeImage) {
    return false;
  }

  if (base_type->GetSingleWordInOperand(kTypeImageDimIndex) != SpvDimBuffer) {
    return false;
  }

  // Check if the image is sampled.  If we do not know for sure that it is,
  // then assume it is a storage texel buffer.
  return base_type->GetSingleWordInOperand(kTypeImageSampledIndex) != 1;
}

bool Instruction::IsVulkanStorageBuffer() const {
  // Is there a difference between a "Storage buffer" and a "dynamic storage
  // buffer" in SPIR-V and do we care about the difference?
  if (opcode() != SpvOpTypePointer) {
    return false;
  }

  ir::Instruction* base_type =
      context()->get_def_use_mgr()->GetDef(GetSingleWordInOperand(1));

  if (base_type->opcode() != SpvOpTypeStruct) {
    return false;
  }

  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  if (storage_class == SpvStorageClassUniform) {
    bool is_buffer_block = false;
    context()->get_decoration_mgr()->ForEachDecoration(
        base_type->result_id(), SpvDecorationBufferBlock,
        [&is_buffer_block](const ir::Instruction&) { is_buffer_block = true; });
    return is_buffer_block;
  } else if (storage_class == SpvStorageClassStorageBuffer) {
    bool is_block = false;
    context()->get_decoration_mgr()->ForEachDecoration(
        base_type->result_id(), SpvDecorationBlock,
        [&is_block](const ir::Instruction&) { is_block = true; });
    return is_block;
  }
  return false;
}

bool Instruction::IsVulkanUniformBuffer() const {
  if (opcode() != SpvOpTypePointer) {
    return false;
  }

  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  if (storage_class != SpvStorageClassUniform) {
    return false;
  }

  ir::Instruction* base_type =
      context()->get_def_use_mgr()->GetDef(GetSingleWordInOperand(1));
  if (base_type->opcode() != SpvOpTypeStruct) {
    return false;
  }

  bool is_block = false;
  context()->get_decoration_mgr()->ForEachDecoration(
      base_type->result_id(), SpvDecorationBlock,
      [&is_block](const ir::Instruction&) { is_block = true; });
  return is_block;
}

bool Instruction::IsReadOnlyVariableShaders() const {
  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  Instruction* type_def = context()->get_def_use_mgr()->GetDef(type_id());

  switch (storage_class) {
    case SpvStorageClassUniformConstant:
      if (!type_def->IsVulkanStorageImage() &&
          !type_def->IsVulkanStorageTexelBuffer()) {
        return true;
      }
      break;
    case SpvStorageClassUniform:
      if (!type_def->IsVulkanStorageBuffer()) {
        return true;
      }
      break;
    case SpvStorageClassPushConstant:
    case SpvStorageClassInput:
      return true;
    default:
      break;
  }

  bool is_nonwritable = false;
  context()->get_decoration_mgr()->ForEachDecoration(
      result_id(), SpvDecorationNonWritable,
      [&is_nonwritable](const Instruction&) { is_nonwritable = true; });
  return is_nonwritable;
}

bool Instruction::IsReadOnlyVariableKernel() const {
  uint32_t storage_class = GetSingleWordInOperand(kVariableStorageClassIndex);
  return storage_class == SpvStorageClassUniformConstant;
}

uint32_t Instruction::GetTypeComponent(uint32_t element) const {
  uint32_t subtype = 0;
  switch (opcode()) {
    case SpvOpTypeStruct:
      subtype = GetSingleWordInOperand(element);
      break;
    case SpvOpTypeArray:
    case SpvOpTypeRuntimeArray:
    case SpvOpTypeVector:
    case SpvOpTypeMatrix:
      // These types all have uniform subtypes.
      subtype = GetSingleWordInOperand(0u);
      break;
    default:
      break;
  }

  return subtype;
}

Instruction* Instruction::InsertBefore(
    std::vector<std::unique_ptr<Instruction>>&& list) {
  Instruction* first_node = list.front().get();
  for (auto& i : list) {
    i.release()->InsertBefore(this);
  }
  list.clear();
  return first_node;
}

Instruction* Instruction::InsertBefore(std::unique_ptr<Instruction>&& i) {
  i.get()->InsertBefore(this);
  return i.release();
}

bool Instruction::IsValidBasePointer() const {
  uint32_t tid = type_id();
  if (tid == 0) {
    return false;
  }

  ir::Instruction* type = context()->get_def_use_mgr()->GetDef(tid);
  if (type->opcode() != SpvOpTypePointer) {
    return false;
  }

  if (context()->get_feature_mgr()->HasCapability(SpvCapabilityAddresses)) {
    // TODO: The rules here could be more restrictive.
    return true;
  }

  if (opcode() == SpvOpVariable || opcode() == SpvOpFunctionParameter) {
    return true;
  }

  uint32_t pointee_type_id = type->GetSingleWordInOperand(1);
  ir::Instruction* pointee_type_inst =
      context()->get_def_use_mgr()->GetDef(pointee_type_id);

  if (pointee_type_inst->IsOpaqueType()) {
    return true;
  }
  return false;
}

bool Instruction::IsValidBaseImage() const {
  uint32_t tid = type_id();
  if (tid == 0) {
    return false;
  }

  ir::Instruction* type = context()->get_def_use_mgr()->GetDef(tid);
  return (type->opcode() == SpvOpTypeImage ||
          type->opcode() == SpvOpTypeSampledImage);
}

bool Instruction::IsOpaqueType() const {
  if (opcode() == SpvOpTypeStruct) {
    bool is_opaque = false;
    ForEachInOperand([&is_opaque, this](const uint32_t* op_id) {
      ir::Instruction* type_inst = context()->get_def_use_mgr()->GetDef(*op_id);
      is_opaque |= type_inst->IsOpaqueType();
    });
    return is_opaque;
  } else if (opcode() == SpvOpTypeArray) {
    uint32_t sub_type_id = GetSingleWordInOperand(0);
    ir::Instruction* sub_type_inst =
        context()->get_def_use_mgr()->GetDef(sub_type_id);
    return sub_type_inst->IsOpaqueType();
  } else {
    return opcode() == SpvOpTypeRuntimeArray ||
           spvOpcodeIsBaseOpaqueType(opcode());
  }
}

bool Instruction::IsFoldable() const {
  return IsFoldableByFoldScalar() ||
         opt::GetConstantFoldingRules().HasFoldingRule(opcode());
}

bool Instruction::IsFoldableByFoldScalar() const {
  if (!opt::IsFoldableOpcode(opcode())) {
    return false;
  }
  Instruction* type = context()->get_def_use_mgr()->GetDef(type_id());
  return opt::IsFoldableType(type);
}

bool Instruction::IsFloatingPointFoldingAllowed() const {
  // TODO: Add the rules for kernels.  For now it will be pessimistic.
  if (!context_->get_feature_mgr()->HasCapability(SpvCapabilityShader)) {
    return false;
  }

  bool is_nocontract = false;
  context_->get_decoration_mgr()->WhileEachDecoration(
      opcode_, SpvDecorationNoContraction,
      [&is_nocontract](const ir::Instruction&) {
        is_nocontract = true;
        return false;
      });
  return !is_nocontract;
}

std::string Instruction::PrettyPrint(uint32_t options) const {
  // Convert the module to binary.
  std::vector<uint32_t> module_binary;
  context()->module()->ToBinary(&module_binary, /* skip_nop = */ false);

  // Convert the instruction to binary. This is used to identify the correct
  // stream of words to output from the module.
  std::vector<uint32_t> inst_binary;
  ToBinaryWithoutAttachedDebugInsts(&inst_binary);

  // Do not generate a header.
  return spvInstructionBinaryToText(
      context()->grammar().target_env(), inst_binary.data(), inst_binary.size(),
      module_binary.data(), module_binary.size(),
      options | SPV_BINARY_TO_TEXT_OPTION_NO_HEADER);
}

std::ostream& operator<<(std::ostream& str, const ir::Instruction& inst) {
  str << inst.PrettyPrint();
  return str;
}

bool Instruction::IsOpcodeCodeMotionSafe() const {
  switch (opcode_) {
    case SpvOpVectorExtractDynamic:
    case SpvOpVectorInsertDynamic:
    case SpvOpVectorShuffle:
    case SpvOpConvertFToU:
    case SpvOpConvertFToS:
    case SpvOpConvertSToF:
    case SpvOpConvertUToF:
    case SpvOpUConvert:
    case SpvOpSConvert:
    case SpvOpFConvert:
    case SpvOpQuantizeToF16:
    case SpvOpBitcast:
    case SpvOpSNegate:
    case SpvOpFNegate:
    case SpvOpIAdd:
    case SpvOpFAdd:
    case SpvOpISub:
    case SpvOpFSub:
    case SpvOpIMul:
    case SpvOpFMul:
    case SpvOpUDiv:
    case SpvOpSDiv:
    case SpvOpFDiv:
    case SpvOpUMod:
    case SpvOpSRem:
    case SpvOpSMod:
    case SpvOpFRem:
    case SpvOpFMod:
    case SpvOpVectorTimesScalar:
    case SpvOpMatrixTimesScalar:
    case SpvOpVectorTimesMatrix:
    case SpvOpMatrixTimesVector:
    case SpvOpMatrixTimesMatrix:
    case SpvOpLogicalEqual:
    case SpvOpLogicalNotEqual:
    case SpvOpLogicalOr:
    case SpvOpLogicalAnd:
    case SpvOpLogicalNot:
    case SpvOpIEqual:
    case SpvOpINotEqual:
    case SpvOpUGreaterThan:
    case SpvOpSGreaterThan:
    case SpvOpUGreaterThanEqual:
    case SpvOpSGreaterThanEqual:
    case SpvOpULessThan:
    case SpvOpSLessThan:
    case SpvOpULessThanEqual:
    case SpvOpSLessThanEqual:
    case SpvOpFOrdEqual:
    case SpvOpFUnordEqual:
    case SpvOpFOrdNotEqual:
    case SpvOpFUnordNotEqual:
    case SpvOpFOrdLessThan:
    case SpvOpFUnordLessThan:
    case SpvOpFOrdGreaterThan:
    case SpvOpFUnordGreaterThan:
    case SpvOpFOrdLessThanEqual:
    case SpvOpFUnordLessThanEqual:
    case SpvOpFOrdGreaterThanEqual:
    case SpvOpFUnordGreaterThanEqual:
    case SpvOpShiftRightLogical:
    case SpvOpShiftRightArithmetic:
    case SpvOpShiftLeftLogical:
    case SpvOpBitwiseOr:
    case SpvOpBitwiseXor:
    case SpvOpBitwiseAnd:
    case SpvOpNot:
      return true;
    default:
      return false;
  }
}

}  // namespace ir
}  // namespace spvtools

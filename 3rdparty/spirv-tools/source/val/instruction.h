// Copyright (c) 2015-2016 The Khronos Group Inc.
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

#ifndef LIBSPIRV_VAL_INSTRUCTION_H_
#define LIBSPIRV_VAL_INSTRUCTION_H_

#include <cassert>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

#include "spirv-tools/libspirv.h"
#include "table.h"

namespace libspirv {

class BasicBlock;
class Function;

/// Wraps the spv_parsed_instruction struct along with use and definition of the
/// instruction's result id
class Instruction {
 public:
  explicit Instruction(const spv_parsed_instruction_t* inst,
                       Function* defining_function = nullptr,
                       BasicBlock* defining_block = nullptr);

  /// Registers the use of the Instruction in instruction \p inst at \p index
  void RegisterUse(const Instruction* inst, uint32_t index);

  uint32_t id() const { return inst_.result_id; }
  uint32_t type_id() const { return inst_.type_id; }
  SpvOp opcode() const { return static_cast<SpvOp>(inst_.opcode); }

  /// Returns the Function where the instruction was defined. nullptr if it was
  /// defined outside of a Function
  const Function* function() const { return function_; }

  /// Returns the BasicBlock where the instruction was defined. nullptr if it
  /// was defined outside of a BasicBlock
  const BasicBlock* block() const { return block_; }

  /// Returns a vector of pairs of all references to this instruction's result
  /// id. The first element is the instruction in which this result id was
  /// referenced and the second is the index of the word in that instruction
  /// where this result id appeared
  const std::vector<std::pair<const Instruction*, uint32_t>>& uses() const {
    return uses_;
  }

  /// The word used to define the Instruction
  uint32_t word(size_t index) const { return words_[index]; }

  /// The words used to define the Instruction
  const std::vector<uint32_t>& words() const { return words_; }

  /// The operands of the Instruction
  const std::vector<spv_parsed_operand_t>& operands() const {
    return operands_;
  }

  /// Provides direct access to the stored C instruction object.
  const spv_parsed_instruction_t& c_inst() const { return inst_; }

  // Casts the words belonging to the operand under |index| to |T| and returns.
  template <typename T>
  T GetOperandAs(size_t index) const {
    const spv_parsed_operand_t& operand = operands_.at(index);
    assert(operand.num_words * 4 >= sizeof(T));
    assert(operand.offset + operand.num_words <= inst_.num_words);
    return *reinterpret_cast<const T*>(&words_[operand.offset]);
  }

 private:
  const std::vector<uint32_t> words_;
  const std::vector<spv_parsed_operand_t> operands_;
  spv_parsed_instruction_t inst_;

  /// The function in which this instruction was declared
  Function* function_;

  /// The basic block in which this instruction was declared
  BasicBlock* block_;

  /// This is a vector of pairs of all references to this instruction's result
  /// id. The first element is the instruction in which this result id was
  /// referenced and the second is the index of the word in the referencing
  /// instruction where this instruction appeared
  std::vector<std::pair<const Instruction*, uint32_t>> uses_;
};

#define OPERATOR(OP)                                                \
  bool operator OP(const Instruction& lhs, const Instruction& rhs); \
  bool operator OP(const Instruction& lhs, uint32_t rhs)

OPERATOR(<);
OPERATOR(==);
#undef OPERATOR

}  // namespace libspirv

// custom specialization of std::hash for Instruction
namespace std {
template <>
struct hash<libspirv::Instruction> {
  typedef libspirv::Instruction argument_type;
  typedef std::size_t result_type;
  result_type operator()(const argument_type& inst) const {
    return hash<uint32_t>()(inst.id());
  }
};
}  // namespace std

#endif  // LIBSPIRV_VAL_INSTRUCTION_H_

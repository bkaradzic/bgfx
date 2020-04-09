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

#include "source/fuzz/fact_manager.h"

#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "source/fuzz/equivalence_relation.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/uniform_buffer_element_descriptor.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

namespace {

std::string ToString(const protobufs::FactConstantUniform& fact) {
  std::stringstream stream;
  stream << "(" << fact.uniform_buffer_element_descriptor().descriptor_set()
         << ", " << fact.uniform_buffer_element_descriptor().binding() << ")[";

  bool first = true;
  for (auto index : fact.uniform_buffer_element_descriptor().index()) {
    if (first) {
      first = false;
    } else {
      stream << ", ";
    }
    stream << index;
  }

  stream << "] == [";

  first = true;
  for (auto constant_word : fact.constant_word()) {
    if (first) {
      first = false;
    } else {
      stream << ", ";
    }
    stream << constant_word;
  }

  stream << "]";
  return stream.str();
}

std::string ToString(const protobufs::FactDataSynonym& fact) {
  std::stringstream stream;
  stream << fact.data1() << " = " << fact.data2();
  return stream.str();
}

std::string ToString(const protobufs::FactIdEquation& fact) {
  std::stringstream stream;
  stream << fact.lhs_id();
  stream << " " << static_cast<SpvOp>(fact.opcode());
  for (auto rhs_id : fact.rhs_id()) {
    stream << " " << rhs_id;
  }
  return stream.str();
}

std::string ToString(const protobufs::Fact& fact) {
  switch (fact.fact_case()) {
    case protobufs::Fact::kConstantUniformFact:
      return ToString(fact.constant_uniform_fact());
    case protobufs::Fact::kDataSynonymFact:
      return ToString(fact.data_synonym_fact());
    case protobufs::Fact::kIdEquationFact:
      return ToString(fact.id_equation_fact());
    default:
      assert(false && "Stringification not supported for this fact.");
      return "";
  }
}

}  // namespace

//=======================
// Constant uniform facts

// The purpose of this class is to group the fields and data used to represent
// facts about uniform constants.
class FactManager::ConstantUniformFacts {
 public:
  // See method in FactManager which delegates to this method.
  bool AddFact(const protobufs::FactConstantUniform& fact,
               opt::IRContext* context);

  // See method in FactManager which delegates to this method.
  std::vector<uint32_t> GetConstantsAvailableFromUniformsForType(
      opt::IRContext* ir_context, uint32_t type_id) const;

  // See method in FactManager which delegates to this method.
  const std::vector<protobufs::UniformBufferElementDescriptor>
  GetUniformDescriptorsForConstant(opt::IRContext* ir_context,
                                   uint32_t constant_id) const;

  // See method in FactManager which delegates to this method.
  uint32_t GetConstantFromUniformDescriptor(
      opt::IRContext* context,
      const protobufs::UniformBufferElementDescriptor& uniform_descriptor)
      const;

  // See method in FactManager which delegates to this method.
  std::vector<uint32_t> GetTypesForWhichUniformValuesAreKnown() const;

  // See method in FactManager which delegates to this method.
  const std::vector<std::pair<protobufs::FactConstantUniform, uint32_t>>&
  GetConstantUniformFactsAndTypes() const;

 private:
  // Returns true if and only if the words associated with
  // |constant_instruction| exactly match the words for the constant associated
  // with |constant_uniform_fact|.
  bool DataMatches(
      const opt::Instruction& constant_instruction,
      const protobufs::FactConstantUniform& constant_uniform_fact) const;

  // Yields the constant words associated with |constant_uniform_fact|.
  std::vector<uint32_t> GetConstantWords(
      const protobufs::FactConstantUniform& constant_uniform_fact) const;

  // Yields the id of a constant of type |type_id| whose data matches the
  // constant data in |constant_uniform_fact|, or 0 if no such constant is
  // declared.
  uint32_t GetConstantId(
      opt::IRContext* context,
      const protobufs::FactConstantUniform& constant_uniform_fact,
      uint32_t type_id) const;

  // Checks that the width of a floating-point constant is supported, and that
  // the constant is finite.
  bool FloatingPointValueIsSuitable(const protobufs::FactConstantUniform& fact,
                                    uint32_t width) const;

  std::vector<std::pair<protobufs::FactConstantUniform, uint32_t>>
      facts_and_type_ids_;
};

uint32_t FactManager::ConstantUniformFacts::GetConstantId(
    opt::IRContext* context,
    const protobufs::FactConstantUniform& constant_uniform_fact,
    uint32_t type_id) const {
  auto type = context->get_type_mgr()->GetType(type_id);
  assert(type != nullptr && "Unknown type id.");
  auto constant = context->get_constant_mgr()->GetConstant(
      type, GetConstantWords(constant_uniform_fact));
  return context->get_constant_mgr()->FindDeclaredConstant(constant, type_id);
}

std::vector<uint32_t> FactManager::ConstantUniformFacts::GetConstantWords(
    const protobufs::FactConstantUniform& constant_uniform_fact) const {
  std::vector<uint32_t> result;
  for (auto constant_word : constant_uniform_fact.constant_word()) {
    result.push_back(constant_word);
  }
  return result;
}

bool FactManager::ConstantUniformFacts::DataMatches(
    const opt::Instruction& constant_instruction,
    const protobufs::FactConstantUniform& constant_uniform_fact) const {
  assert(constant_instruction.opcode() == SpvOpConstant);
  std::vector<uint32_t> data_in_constant;
  for (uint32_t i = 0; i < constant_instruction.NumInOperands(); i++) {
    data_in_constant.push_back(constant_instruction.GetSingleWordInOperand(i));
  }
  return data_in_constant == GetConstantWords(constant_uniform_fact);
}

std::vector<uint32_t>
FactManager::ConstantUniformFacts::GetConstantsAvailableFromUniformsForType(
    opt::IRContext* ir_context, uint32_t type_id) const {
  std::vector<uint32_t> result;
  std::set<uint32_t> already_seen;
  for (auto& fact_and_type_id : facts_and_type_ids_) {
    if (fact_and_type_id.second != type_id) {
      continue;
    }
    if (auto constant_id =
            GetConstantId(ir_context, fact_and_type_id.first, type_id)) {
      if (already_seen.find(constant_id) == already_seen.end()) {
        result.push_back(constant_id);
        already_seen.insert(constant_id);
      }
    }
  }
  return result;
}

const std::vector<protobufs::UniformBufferElementDescriptor>
FactManager::ConstantUniformFacts::GetUniformDescriptorsForConstant(
    opt::IRContext* ir_context, uint32_t constant_id) const {
  std::vector<protobufs::UniformBufferElementDescriptor> result;
  auto constant_inst = ir_context->get_def_use_mgr()->GetDef(constant_id);
  assert(constant_inst->opcode() == SpvOpConstant &&
         "The given id must be that of a constant");
  auto type_id = constant_inst->type_id();
  for (auto& fact_and_type_id : facts_and_type_ids_) {
    if (fact_and_type_id.second != type_id) {
      continue;
    }
    if (DataMatches(*constant_inst, fact_and_type_id.first)) {
      result.emplace_back(
          fact_and_type_id.first.uniform_buffer_element_descriptor());
    }
  }
  return result;
}

uint32_t FactManager::ConstantUniformFacts::GetConstantFromUniformDescriptor(
    opt::IRContext* context,
    const protobufs::UniformBufferElementDescriptor& uniform_descriptor) const {
  // Consider each fact.
  for (auto& fact_and_type : facts_and_type_ids_) {
    // Check whether the uniform descriptor associated with the fact matches
    // |uniform_descriptor|.
    if (UniformBufferElementDescriptorEquals()(
            &uniform_descriptor,
            &fact_and_type.first.uniform_buffer_element_descriptor())) {
      return GetConstantId(context, fact_and_type.first, fact_and_type.second);
    }
  }
  // No fact associated with the given uniform descriptor was found.
  return 0;
}

std::vector<uint32_t>
FactManager::ConstantUniformFacts::GetTypesForWhichUniformValuesAreKnown()
    const {
  std::vector<uint32_t> result;
  for (auto& fact_and_type : facts_and_type_ids_) {
    if (std::find(result.begin(), result.end(), fact_and_type.second) ==
        result.end()) {
      result.push_back(fact_and_type.second);
    }
  }
  return result;
}

bool FactManager::ConstantUniformFacts::FloatingPointValueIsSuitable(
    const protobufs::FactConstantUniform& fact, uint32_t width) const {
  const uint32_t kFloatWidth = 32;
  const uint32_t kDoubleWidth = 64;
  if (width != kFloatWidth && width != kDoubleWidth) {
    // Only 32- and 64-bit floating-point types are handled.
    return false;
  }
  std::vector<uint32_t> words = GetConstantWords(fact);
  if (width == 32) {
    float value;
    memcpy(&value, words.data(), sizeof(float));
    if (!std::isfinite(value)) {
      return false;
    }
  } else {
    double value;
    memcpy(&value, words.data(), sizeof(double));
    if (!std::isfinite(value)) {
      return false;
    }
  }
  return true;
}

bool FactManager::ConstantUniformFacts::AddFact(
    const protobufs::FactConstantUniform& fact, opt::IRContext* context) {
  // Try to find a unique instruction that declares a variable such that the
  // variable is decorated with the descriptor set and binding associated with
  // the constant uniform fact.
  opt::Instruction* uniform_variable = FindUniformVariable(
      fact.uniform_buffer_element_descriptor(), context, true);

  if (!uniform_variable) {
    return false;
  }

  assert(SpvOpVariable == uniform_variable->opcode());
  assert(SpvStorageClassUniform == uniform_variable->GetSingleWordInOperand(0));

  auto should_be_uniform_pointer_type =
      context->get_type_mgr()->GetType(uniform_variable->type_id());
  if (!should_be_uniform_pointer_type->AsPointer()) {
    return false;
  }
  if (should_be_uniform_pointer_type->AsPointer()->storage_class() !=
      SpvStorageClassUniform) {
    return false;
  }
  auto should_be_uniform_pointer_instruction =
      context->get_def_use_mgr()->GetDef(uniform_variable->type_id());
  auto composite_type =
      should_be_uniform_pointer_instruction->GetSingleWordInOperand(1);

  auto final_element_type_id = fuzzerutil::WalkCompositeTypeIndices(
      context, composite_type,
      fact.uniform_buffer_element_descriptor().index());
  if (!final_element_type_id) {
    return false;
  }
  auto final_element_type =
      context->get_type_mgr()->GetType(final_element_type_id);
  assert(final_element_type &&
         "There should be a type corresponding to this id.");

  if (!(final_element_type->AsFloat() || final_element_type->AsInteger())) {
    return false;
  }
  auto width = final_element_type->AsFloat()
                   ? final_element_type->AsFloat()->width()
                   : final_element_type->AsInteger()->width();

  if (final_element_type->AsFloat() &&
      !FloatingPointValueIsSuitable(fact, width)) {
    return false;
  }

  auto required_words = (width + 32 - 1) / 32;
  if (static_cast<uint32_t>(fact.constant_word().size()) != required_words) {
    return false;
  }
  facts_and_type_ids_.emplace_back(
      std::pair<protobufs::FactConstantUniform, uint32_t>(
          fact, final_element_type_id));
  return true;
}

const std::vector<std::pair<protobufs::FactConstantUniform, uint32_t>>&
FactManager::ConstantUniformFacts::GetConstantUniformFactsAndTypes() const {
  return facts_and_type_ids_;
}

// End of uniform constant facts
//==============================

//==============================
// Data synonym and id equation facts

// This helper struct represents the right hand side of an equation as an
// operator applied to a number of data descriptor operands.
struct Operation {
  SpvOp opcode;
  std::vector<const protobufs::DataDescriptor*> operands;
};

// Hashing for operations, to allow deterministic unordered sets.
struct OperationHash {
  size_t operator()(const Operation& operation) const {
    std::u32string hash;
    hash.push_back(operation.opcode);
    for (auto operand : operation.operands) {
      hash.push_back(static_cast<uint32_t>(DataDescriptorHash()(operand)));
    }
    return std::hash<std::u32string>()(hash);
  }
};

// Equality for operations, to allow deterministic unordered sets.
struct OperationEquals {
  bool operator()(const Operation& first, const Operation& second) const {
    // Equal operations require...
    //
    // Equal opcodes.
    if (first.opcode != second.opcode) {
      return false;
    }
    // Matching operand counds.
    if (first.operands.size() != second.operands.size()) {
      return false;
    }
    // Equal operands.
    for (uint32_t i = 0; i < first.operands.size(); i++) {
      if (!DataDescriptorEquals()(first.operands[i], second.operands[i])) {
        return false;
      }
    }
    return true;
  }
};

// A helper, for debugging, to represent an operation as a string.
std::string ToString(const Operation& operation) {
  std::stringstream stream;
  stream << operation.opcode;
  for (auto operand : operation.operands) {
    stream << " " << *operand;
  }
  return stream.str();
}

// The purpose of this class is to group the fields and data used to represent
// facts about data synonyms and id equations.
class FactManager::DataSynonymAndIdEquationFacts {
 public:
  // See method in FactManager which delegates to this method.
  void AddFact(const protobufs::FactDataSynonym& fact, opt::IRContext* context);

  // See method in FactManager which delegates to this method.
  void AddFact(const protobufs::FactIdEquation& fact, opt::IRContext* context);

  // See method in FactManager which delegates to this method.
  std::vector<const protobufs::DataDescriptor*> GetSynonymsForDataDescriptor(
      const protobufs::DataDescriptor& data_descriptor,
      opt::IRContext* context) const;

  // See method in FactManager which delegates to this method.
  std::vector<uint32_t> GetIdsForWhichSynonymsAreKnown(
      opt::IRContext* context) const;

  // See method in FactManager which delegates to this method.
  bool IsSynonymous(const protobufs::DataDescriptor& data_descriptor1,
                    const protobufs::DataDescriptor& data_descriptor2,
                    opt::IRContext* context) const;

 private:
  // Adds the synonym |dd1| = |dd2| to the set of managed facts, and recurses
  // into sub-components of the data descriptors, if they are composites, to
  // record that their components are pairwise-synonymous.
  void AddDataSynonymFactRecursive(const protobufs::DataDescriptor& dd1,
                                   const protobufs::DataDescriptor& dd2,
                                   opt::IRContext* context);

  // Inspects all known facts and adds corollary facts; e.g. if we know that
  // a.x == b.x and a.y == b.y, where a and b have vec2 type, we can record
  // that a == b holds.
  //
  // This method is expensive, and is thus called on demand: rather than
  // computing the closure of facts each time a data synonym fact is added, we
  // compute the closure only when a data synonym fact is *queried*.
  void ComputeClosureOfFacts(opt::IRContext* context) const;

  // Records the fact that |dd1| and |dd2| are equivalent, and merges the sets
  // of equations that are known about them.
  //
  // This is a const method, despite the fact that it mutates the (mutable)
  // set of facts about data descriptors because it is invoked in a lazy fashion
  // when querying facts.
  void MakeEquivalent(const protobufs::DataDescriptor& dd1,
                      const protobufs::DataDescriptor& dd2) const;

  // Returns true if and only if |dd1| and |dd2| are valid data descriptors
  // whose associated data have the same type (modulo integer signedness).
  bool DataDescriptorsAreWellFormedAndComparable(
      opt::IRContext* context, const protobufs::DataDescriptor& dd1,
      const protobufs::DataDescriptor& dd2) const;

  // Requires that |lhs_dd| and every element of |rhs_dds| is present in the
  // |synonymous_| equivalence relation, but is not necessarily its own
  // representative.  Records the fact that the equation
  // "|lhs_dd| |opcode| |rhs_dds_non_canonical|" holds, and adds any
  // corollaries, in the form of data synonym or equation facts, that follow
  // from this and other known facts.
  void AddEquationFactRecursive(
      const protobufs::DataDescriptor& lhs_dd, SpvOp opcode,
      const std::vector<const protobufs::DataDescriptor*>& rhs_dds,
      opt::IRContext* context);

  // The data descriptors that are known to be synonymous with one another are
  // captured by this equivalence relation.
  //
  // This member is mutable in order to allow the closure of facts captured by
  // the relation to be computed lazily when a question about data synonym
  // facts is asked.
  mutable EquivalenceRelation<protobufs::DataDescriptor, DataDescriptorHash,
                              DataDescriptorEquals>
      synonymous_;

  // When a new synonym fact is added, it may be possible to deduce further
  // synonym facts by computing a closure of all known facts.  However, there is
  // no point computing this closure until a question regarding synonym facts is
  // actually asked: if several facts are added in succession with no questions
  // asked in between, we can avoid computing fact closures multiple times.
  //
  // This boolean tracks whether a closure computation is required - i.e.,
  // whether a new fact has been added since the last time such a computation
  // was performed.
  //
  // It is mutable to facilitate having const methods, that provide answers to
  // questions about data synonym facts, triggering closure computation on
  // demand.
  mutable bool closure_computation_required_ = false;

  // Represents a set of equations on data descriptors as a map indexed by
  // left-hand-side, mapping a left-hand-side to a set of operations, each of
  // which (together with the left-hand-side) defines an equation.
  //
  // All data descriptors occurring in equations are required to be present in
  // the |synonymous_| equivalence relation, and to be their own representatives
  // in that relation.
  //
  // It is mutable because a closure computation can be triggered from a const
  // method, and when a closure computation detects that two data descriptors
  // are equivalent it is necessary to merge the equation facts for those data
  // descriptors.
  mutable std::unordered_map<
      const protobufs::DataDescriptor*,
      std::unordered_set<Operation, OperationHash, OperationEquals>>
      id_equations_;
};

void FactManager::DataSynonymAndIdEquationFacts::AddFact(
    const protobufs::FactDataSynonym& fact, opt::IRContext* context) {
  // Add the fact, including all facts relating sub-components of the data
  // descriptors that are involved.
  AddDataSynonymFactRecursive(fact.data1(), fact.data2(), context);
}

void FactManager::DataSynonymAndIdEquationFacts::AddFact(
    const protobufs::FactIdEquation& fact, opt::IRContext* context) {
  protobufs::DataDescriptor lhs_dd = MakeDataDescriptor(fact.lhs_id(), {});

  // Register the LHS in the equivalence relation if needed.
  if (!synonymous_.Exists(lhs_dd)) {
    synonymous_.Register(lhs_dd);
  }

  // Get equivalence class representatives for all ids used on the RHS of the
  // equation.
  std::vector<const protobufs::DataDescriptor*> rhs_dd_ptrs;
  for (auto rhs_id : fact.rhs_id()) {
    // Register a data descriptor based on this id in the equivalence relation
    // if needed, and then record the equivalence class representative.
    protobufs::DataDescriptor rhs_dd = MakeDataDescriptor(rhs_id, {});
    if (!synonymous_.Exists(rhs_dd)) {
      synonymous_.Register(rhs_dd);
    }
    rhs_dd_ptrs.push_back(synonymous_.Find(&rhs_dd));
  }

  // Now add the fact.
  AddEquationFactRecursive(lhs_dd, static_cast<SpvOp>(fact.opcode()),
                           rhs_dd_ptrs, context);
}

void FactManager::DataSynonymAndIdEquationFacts::AddEquationFactRecursive(
    const protobufs::DataDescriptor& lhs_dd, SpvOp opcode,
    const std::vector<const protobufs::DataDescriptor*>& rhs_dds,
    opt::IRContext* context) {
  assert(synonymous_.Exists(lhs_dd) &&
         "The LHS must be known to the equivalence relation.");
  for (auto rhs_dd : rhs_dds) {
    // Keep release compilers happy.
    (void)(rhs_dd);
    assert(synonymous_.Exists(*rhs_dd) &&
           "The RHS operands must be known to the equivalence relation.");
  }

  auto lhs_dd_representative = synonymous_.Find(&lhs_dd);

  if (id_equations_.count(lhs_dd_representative) == 0) {
    // We have not seen an equation with this LHS before, so associate the LHS
    // with an initially empty set.
    id_equations_.insert(
        {lhs_dd_representative,
         std::unordered_set<Operation, OperationHash, OperationEquals>()});
  }

  {
    auto existing_equations = id_equations_.find(lhs_dd_representative);
    assert(existing_equations != id_equations_.end() &&
           "A set of operations should be present, even if empty.");

    Operation new_operation = {opcode, rhs_dds};
    if (existing_equations->second.count(new_operation)) {
      // This equation is known, so there is nothing further to be done.
      return;
    }
    // Add the equation to the set of known equations.
    existing_equations->second.insert(new_operation);
  }

  // Now try to work out corollaries implied by the new equation and existing
  // facts.
  switch (opcode) {
    case SpvOpIAdd: {
      // Equation form: "a = b + c"
      {
        auto existing_first_operand_equations = id_equations_.find(rhs_dds[0]);
        if (existing_first_operand_equations != id_equations_.end()) {
          for (auto equation : existing_first_operand_equations->second) {
            if (equation.opcode == SpvOpISub) {
              // Equation form: "a = (d - e) + c"
              if (synonymous_.IsEquivalent(*equation.operands[1],
                                           *rhs_dds[1])) {
                // Equation form: "a = (d - c) + c"
                // We can thus infer "a = d"
                AddDataSynonymFactRecursive(lhs_dd, *equation.operands[0],
                                            context);
              }
              if (synonymous_.IsEquivalent(*equation.operands[0],
                                           *rhs_dds[1])) {
                // Equation form: "a = (c - e) + c"
                // We can thus infer "a = -e"
                AddEquationFactRecursive(lhs_dd, SpvOpSNegate,
                                         {equation.operands[1]}, context);
              }
            }
          }
        }
      }
      {
        auto existing_second_operand_equations = id_equations_.find(rhs_dds[1]);
        if (existing_second_operand_equations != id_equations_.end()) {
          for (auto equation : existing_second_operand_equations->second) {
            if (equation.opcode == SpvOpISub) {
              // Equation form: "a = b + (d - e)"
              if (synonymous_.IsEquivalent(*equation.operands[1],
                                           *rhs_dds[0])) {
                // Equation form: "a = b + (d - b)"
                // We can thus infer "a = d"
                AddDataSynonymFactRecursive(lhs_dd, *equation.operands[0],
                                            context);
              }
            }
          }
        }
      }
      break;
    }
    case SpvOpISub: {
      // Equation form: "a = b - c"
      {
        auto existing_first_operand_equations = id_equations_.find(rhs_dds[0]);
        if (existing_first_operand_equations != id_equations_.end()) {
          for (auto equation : existing_first_operand_equations->second) {
            if (equation.opcode == SpvOpIAdd) {
              // Equation form: "a = (d + e) - c"
              if (synonymous_.IsEquivalent(*equation.operands[0],
                                           *rhs_dds[1])) {
                // Equation form: "a = (c + e) - c"
                // We can thus infer "a = e"
                AddDataSynonymFactRecursive(lhs_dd, *equation.operands[1],
                                            context);
              }
              if (synonymous_.IsEquivalent(*equation.operands[1],
                                           *rhs_dds[1])) {
                // Equation form: "a = (d + c) - c"
                // We can thus infer "a = d"
                AddDataSynonymFactRecursive(lhs_dd, *equation.operands[0],
                                            context);
              }
            }

            if (equation.opcode == SpvOpISub) {
              // Equation form: "a = (d - e) - c"
              if (synonymous_.IsEquivalent(*equation.operands[0],
                                           *rhs_dds[1])) {
                // Equation form: "a = (c - e) - c"
                // We can thus infer "a = -e"
                AddEquationFactRecursive(lhs_dd, SpvOpSNegate,
                                         {equation.operands[1]}, context);
              }
            }
          }
        }
      }

      {
        auto existing_second_operand_equations = id_equations_.find(rhs_dds[1]);
        if (existing_second_operand_equations != id_equations_.end()) {
          for (auto equation : existing_second_operand_equations->second) {
            if (equation.opcode == SpvOpIAdd) {
              // Equation form: "a = b - (d + e)"
              if (synonymous_.IsEquivalent(*equation.operands[0],
                                           *rhs_dds[0])) {
                // Equation form: "a = b - (b + e)"
                // We can thus infer "a = -e"
                AddEquationFactRecursive(lhs_dd, SpvOpSNegate,
                                         {equation.operands[1]}, context);
              }
              if (synonymous_.IsEquivalent(*equation.operands[1],
                                           *rhs_dds[0])) {
                // Equation form: "a = b - (d + b)"
                // We can thus infer "a = -d"
                AddEquationFactRecursive(lhs_dd, SpvOpSNegate,
                                         {equation.operands[0]}, context);
              }
            }
            if (equation.opcode == SpvOpISub) {
              // Equation form: "a = b - (d - e)"
              if (synonymous_.IsEquivalent(*equation.operands[0],
                                           *rhs_dds[0])) {
                // Equation form: "a = b - (b - e)"
                // We can thus infer "a = e"
                AddDataSynonymFactRecursive(lhs_dd, *equation.operands[1],
                                            context);
              }
            }
          }
        }
      }
      break;
    }
    case SpvOpLogicalNot:
    case SpvOpSNegate: {
      // Equation form: "a = !b" or "a = -b"
      auto existing_equations = id_equations_.find(rhs_dds[0]);
      if (existing_equations != id_equations_.end()) {
        for (auto equation : existing_equations->second) {
          if (equation.opcode == opcode) {
            // Equation form: "a = !!b" or "a = -(-b)"
            // We can thus infer "a = b"
            AddDataSynonymFactRecursive(lhs_dd, *equation.operands[0], context);
          }
        }
      }
      break;
    }
    default:
      break;
  }
}

void FactManager::DataSynonymAndIdEquationFacts::AddDataSynonymFactRecursive(
    const protobufs::DataDescriptor& dd1, const protobufs::DataDescriptor& dd2,
    opt::IRContext* context) {
  assert(DataDescriptorsAreWellFormedAndComparable(context, dd1, dd2));

  // Record that the data descriptors provided in the fact are equivalent.
  MakeEquivalent(dd1, dd2);

  // We now check whether this is a synonym about composite objects.  If it is,
  // we can recursively add synonym facts about their associated sub-components.

  // Get the type of the object referred to by the first data descriptor in the
  // synonym fact.
  uint32_t type_id = fuzzerutil::WalkCompositeTypeIndices(
      context, context->get_def_use_mgr()->GetDef(dd1.object())->type_id(),
      dd1.index());
  auto type = context->get_type_mgr()->GetType(type_id);
  auto type_instruction = context->get_def_use_mgr()->GetDef(type_id);
  assert(type != nullptr &&
         "Invalid data synonym fact: one side has an unknown type.");

  // Check whether the type is composite, recording the number of elements
  // associated with the composite if so.
  uint32_t num_composite_elements;
  if (type->AsArray()) {
    num_composite_elements =
        fuzzerutil::GetArraySize(*type_instruction, context);
  } else if (type->AsMatrix()) {
    num_composite_elements = type->AsMatrix()->element_count();
  } else if (type->AsStruct()) {
    num_composite_elements =
        fuzzerutil::GetNumberOfStructMembers(*type_instruction);
  } else if (type->AsVector()) {
    num_composite_elements = type->AsVector()->element_count();
  } else {
    // The type is not a composite, so return.
    return;
  }

  // If the fact has the form:
  //   obj_1[a_1, ..., a_m] == obj_2[b_1, ..., b_n]
  // then for each composite index i, we add a fact of the form:
  //   obj_1[a_1, ..., a_m, i] == obj_2[b_1, ..., b_n, i]
  for (uint32_t i = 0; i < num_composite_elements; i++) {
    std::vector<uint32_t> extended_indices1 =
        fuzzerutil::RepeatedFieldToVector(dd1.index());
    extended_indices1.push_back(i);
    std::vector<uint32_t> extended_indices2 =
        fuzzerutil::RepeatedFieldToVector(dd2.index());
    extended_indices2.push_back(i);
    AddDataSynonymFactRecursive(
        MakeDataDescriptor(dd1.object(), std::move(extended_indices1)),
        MakeDataDescriptor(dd2.object(), std::move(extended_indices2)),
        context);
  }
}

void FactManager::DataSynonymAndIdEquationFacts::ComputeClosureOfFacts(
    opt::IRContext* context) const {
  // Suppose that obj_1[a_1, ..., a_m] and obj_2[b_1, ..., b_n] are distinct
  // data descriptors that describe objects of the same composite type, and that
  // the composite type is comprised of k components.
  //
  // For example, if m is a mat4x4 and v a vec4, we might consider:
  //   m[2]: describes the 2nd column of m, a vec4
  //   v[]: describes all of v, a vec4
  //
  // Suppose that we know, for every 0 <= i < k, that the fact:
  //   obj_1[a_1, ..., a_m, i] == obj_2[b_1, ..., b_n, i]
  // holds - i.e. that the children of the two data descriptors are synonymous.
  //
  // Then we can conclude that:
  //   obj_1[a_1, ..., a_m] == obj_2[b_1, ..., b_n]
  // holds.
  //
  // For instance, if we have the facts:
  //   m[2, 0] == v[0]
  //   m[2, 1] == v[1]
  //   m[2, 2] == v[2]
  //   m[2, 3] == v[3]
  // then we can conclude that:
  //   m[2] == v.
  //
  // This method repeatedly searches the equivalence relation of data
  // descriptors, deducing and adding such facts, until a pass over the
  // relation leads to no further facts being deduced.

  // The method relies on working with pairs of data descriptors, and in
  // particular being able to hash and compare such pairs.

  using DataDescriptorPair =
      std::pair<protobufs::DataDescriptor, protobufs::DataDescriptor>;

  struct DataDescriptorPairHash {
    std::size_t operator()(const DataDescriptorPair& pair) const {
      return DataDescriptorHash()(&pair.first) ^
             DataDescriptorHash()(&pair.second);
    }
  };

  struct DataDescriptorPairEquals {
    bool operator()(const DataDescriptorPair& first,
                    const DataDescriptorPair& second) const {
      return DataDescriptorEquals()(&first.first, &second.first) &&
             DataDescriptorEquals()(&first.second, &second.second);
    }
  };

  // This map records, for a given pair of composite data descriptors of the
  // same type, all the indices at which the data descriptors are known to be
  // synonymous.  A pair is a key to this map only if we have observed that
  // the pair are synonymous at *some* index, but not at *all* indices.
  // Once we find that a pair of data descriptors are equivalent at all indices
  // we record the fact that they are synonymous and remove them from the map.
  //
  // Using the m and v example from above, initially the pair (m[2], v) would
  // not be a key to the map.  If we find that m[2, 2] == v[2] holds, we would
  // add an entry:
  //   (m[2], v) -> [false, false, true, false]
  // to record that they are synonymous at index 2.  If we then find that
  // m[2, 0] == v[0] holds, we would update this entry to:
  //   (m[2], v) -> [true, false, true, false]
  // If we then find that m[2, 3] == v[3] holds, we would update this entry to:
  //   (m[2], v) -> [true, false, true, true]
  // Finally, if we then find that m[2, 1] == v[1] holds, which would make the
  // boolean vector true at every index, we would add the fact:
  //   m[2] == v
  // to the equivalence relation and remove (m[2], v) from the map.
  std::unordered_map<DataDescriptorPair, std::vector<bool>,
                     DataDescriptorPairHash, DataDescriptorPairEquals>
      candidate_composite_synonyms;

  // We keep looking for new facts until we perform a complete pass over the
  // equivalence relation without finding any new facts.
  while (closure_computation_required_) {
    // We have not found any new facts yet during this pass; we set this to
    // 'true' if we do find a new fact.
    closure_computation_required_ = false;

    // Consider each class in the equivalence relation.
    for (auto representative :
         synonymous_.GetEquivalenceClassRepresentatives()) {
      auto equivalence_class = synonymous_.GetEquivalenceClass(*representative);

      // Consider every data descriptor in the equivalence class.
      for (auto dd1_it = equivalence_class.begin();
           dd1_it != equivalence_class.end(); ++dd1_it) {
        // If this data descriptor has no indices then it does not have the form
        // obj_1[a_1, ..., a_m, i], so move on.
        auto dd1 = *dd1_it;
        if (dd1->index_size() == 0) {
          continue;
        }

        // Consider every other data descriptor later in the equivalence class
        // (due to symmetry, there is no need to compare with previous data
        // descriptors).
        auto dd2_it = dd1_it;
        for (++dd2_it; dd2_it != equivalence_class.end(); ++dd2_it) {
          auto dd2 = *dd2_it;
          // If this data descriptor has no indices then it does not have the
          // form obj_2[b_1, ..., b_n, i], so move on.
          if (dd2->index_size() == 0) {
            continue;
          }

          // At this point we know that:
          // - |dd1| has the form obj_1[a_1, ..., a_m, i]
          // - |dd2| has the form obj_2[b_1, ..., b_n, j]
          assert(dd1->index_size() > 0 && dd2->index_size() > 0 &&
                 "Control should not reach here if either data descriptor has "
                 "no indices.");

          // We are only interested if i == j.
          if (dd1->index(dd1->index_size() - 1) !=
              dd2->index(dd2->index_size() - 1)) {
            continue;
          }

          const uint32_t common_final_index = dd1->index(dd1->index_size() - 1);

          // Make data descriptors |dd1_prefix| and |dd2_prefix| for
          //   obj_1[a_1, ..., a_m]
          // and
          //   obj_2[b_1, ..., b_n]
          // These are the two data descriptors we might be getting closer to
          // deducing as being synonymous, due to knowing that they are
          // synonymous when extended by a particular index.
          protobufs::DataDescriptor dd1_prefix;
          dd1_prefix.set_object(dd1->object());
          for (uint32_t i = 0; i < static_cast<uint32_t>(dd1->index_size() - 1);
               i++) {
            dd1_prefix.add_index(dd1->index(i));
          }
          protobufs::DataDescriptor dd2_prefix;
          dd2_prefix.set_object(dd2->object());
          for (uint32_t i = 0; i < static_cast<uint32_t>(dd2->index_size() - 1);
               i++) {
            dd2_prefix.add_index(dd2->index(i));
          }
          assert(!DataDescriptorEquals()(&dd1_prefix, &dd2_prefix) &&
                 "By construction these prefixes should be different.");

          // If we already know that these prefixes are synonymous, move on.
          if (synonymous_.Exists(dd1_prefix) &&
              synonymous_.Exists(dd2_prefix) &&
              synonymous_.IsEquivalent(dd1_prefix, dd2_prefix)) {
            continue;
          }

          // Get the type of obj_1
          auto dd1_root_type_id =
              context->get_def_use_mgr()->GetDef(dd1->object())->type_id();
          // Use this type, together with a_1, ..., a_m, to get the type of
          // obj_1[a_1, ..., a_m].
          auto dd1_prefix_type = fuzzerutil::WalkCompositeTypeIndices(
              context, dd1_root_type_id, dd1_prefix.index());

          // Similarly, get the type of obj_2 and use it to get the type of
          // obj_2[b_1, ..., b_n].
          auto dd2_root_type_id =
              context->get_def_use_mgr()->GetDef(dd2->object())->type_id();
          auto dd2_prefix_type = fuzzerutil::WalkCompositeTypeIndices(
              context, dd2_root_type_id, dd2_prefix.index());

          // If the types of dd1_prefix and dd2_prefix are not the same, they
          // cannot be synonymous.
          if (dd1_prefix_type != dd2_prefix_type) {
            continue;
          }

          // At this point, we know we have synonymous data descriptors of the
          // form:
          //   obj_1[a_1, ..., a_m, i]
          //   obj_2[b_1, ..., b_n, i]
          // with the same last_index i, such that:
          //   obj_1[a_1, ..., a_m]
          // and
          //   obj_2[b_1, ..., b_n]
          // have the same type.

          // Work out how many components there are in the (common) commposite
          // type associated with obj_1[a_1, ..., a_m] and obj_2[b_1, ..., b_n].
          // This depends on whether the composite type is array, matrix, struct
          // or vector.
          uint32_t num_components_in_composite;
          auto composite_type =
              context->get_type_mgr()->GetType(dd1_prefix_type);
          auto composite_type_instruction =
              context->get_def_use_mgr()->GetDef(dd1_prefix_type);
          if (composite_type->AsArray()) {
            num_components_in_composite =
                fuzzerutil::GetArraySize(*composite_type_instruction, context);
            if (num_components_in_composite == 0) {
              // This indicates that the array has an unknown size, in which
              // case we cannot be sure we have matched all of its elements with
              // synonymous elements of another array.
              continue;
            }
          } else if (composite_type->AsMatrix()) {
            num_components_in_composite =
                composite_type->AsMatrix()->element_count();
          } else if (composite_type->AsStruct()) {
            num_components_in_composite = fuzzerutil::GetNumberOfStructMembers(
                *composite_type_instruction);
          } else {
            assert(composite_type->AsVector());
            num_components_in_composite =
                composite_type->AsVector()->element_count();
          }

          // We are one step closer to being able to say that |dd1_prefix| and
          // |dd2_prefix| are synonymous.
          DataDescriptorPair candidate_composite_synonym(dd1_prefix,
                                                         dd2_prefix);

          // We look up what we already know about this pair.
          auto existing_entry =
              candidate_composite_synonyms.find(candidate_composite_synonym);

          if (existing_entry == candidate_composite_synonyms.end()) {
            // If this is the first time we have seen the pair, we make a vector
            // of size |num_components_in_composite| that is 'true' at the
            // common final index associated with |dd1| and |dd2|, and 'false'
            // everywhere else, and register this vector as being associated
            // with the pair.
            std::vector<bool> entry;
            for (uint32_t i = 0; i < num_components_in_composite; i++) {
              entry.push_back(i == common_final_index);
            }
            candidate_composite_synonyms[candidate_composite_synonym] = entry;
            existing_entry =
                candidate_composite_synonyms.find(candidate_composite_synonym);
          } else {
            // We have seen this pair of data descriptors before, and we now
            // know that they are synonymous at one further index, so we
            // update the entry to record that.
            existing_entry->second[common_final_index] = true;
          }
          assert(existing_entry != candidate_composite_synonyms.end());

          // Check whether |dd1_prefix| and |dd2_prefix| are now known to match
          // at every sub-component.
          bool all_components_match = true;
          for (uint32_t i = 0; i < num_components_in_composite; i++) {
            if (!existing_entry->second[i]) {
              all_components_match = false;
              break;
            }
          }
          if (all_components_match) {
            // The two prefixes match on all sub-components, so we know that
            // they are synonymous.  We add this fact *non-recursively*, as we
            // have deduced that |dd1_prefix| and |dd2_prefix| are synonymous
            // by observing that all their sub-components are already
            // synonymous.
            assert(DataDescriptorsAreWellFormedAndComparable(
                context, dd1_prefix, dd2_prefix));
            MakeEquivalent(dd1_prefix, dd2_prefix);
            // Now that we know this pair of data descriptors are synonymous,
            // there is no point recording how close they are to being
            // synonymous.
            candidate_composite_synonyms.erase(candidate_composite_synonym);
          }
        }
      }
    }
  }
}

void FactManager::DataSynonymAndIdEquationFacts::MakeEquivalent(
    const protobufs::DataDescriptor& dd1,
    const protobufs::DataDescriptor& dd2) const {
  // Register the data descriptors if they are not already known to the
  // equivalence relation.
  for (const auto& dd : {dd1, dd2}) {
    if (!synonymous_.Exists(dd)) {
      synonymous_.Register(dd);
    }
  }

  if (synonymous_.IsEquivalent(dd1, dd2)) {
    // The data descriptors are already known to be equivalent, so there is
    // nothing to do.
    return;
  }

  // We must make the data descriptors equivalent, and also make sure any
  // equation facts known about their representatives are merged.

  // Record the original equivalence class representatives of the data
  // descriptors.
  auto dd1_original_representative = synonymous_.Find(&dd1);
  auto dd2_original_representative = synonymous_.Find(&dd2);

  // Make the data descriptors equivalent.
  synonymous_.MakeEquivalent(dd1, dd2);
  // As we have updated the equivalence relation, we might be able to deduce
  // more facts by performing a closure computation, so we record that such a
  // computation is required.
  closure_computation_required_ = true;

  // At this point, exactly one of |dd1_original_representative| and
  // |dd2_original_representative| will be the representative of the combined
  // equivalence class.  We work out which one of them is still the class
  // representative and which one is no longer the class representative.

  auto still_representative = synonymous_.Find(dd1_original_representative) ==
                                      dd1_original_representative
                                  ? dd1_original_representative
                                  : dd2_original_representative;
  auto no_longer_representative =
      still_representative == dd1_original_representative
          ? dd2_original_representative
          : dd1_original_representative;

  assert(no_longer_representative != still_representative &&
         "The current and former representatives cannot be the same.");

  // We now need to add all equations about |no_longer_representative| to the
  // set of equations known about |still_representative|.

  // Get the equations associated with |no_longer_representative|.
  auto no_longer_representative_id_equations =
      id_equations_.find(no_longer_representative);
  if (no_longer_representative_id_equations != id_equations_.end()) {
    // There are some equations to transfer.  There might not yet be any
    // equations about |still_representative|; create an empty set of equations
    // if this is the case.
    if (!id_equations_.count(still_representative)) {
      id_equations_.insert(
          {still_representative,
           std::unordered_set<Operation, OperationHash, OperationEquals>()});
    }
    auto still_representative_id_equations =
        id_equations_.find(still_representative);
    assert(still_representative_id_equations != id_equations_.end() &&
           "At this point there must be a set of equations.");
    // Add all the equations known about |no_longer_representative| to the set
    // of equations known about |still_representative|.
    still_representative_id_equations->second.insert(
        no_longer_representative_id_equations->second.begin(),
        no_longer_representative_id_equations->second.end());
  }
  // Delete the no longer-relevant equations about |no_longer_representative|.
  id_equations_.erase(no_longer_representative);
}

bool FactManager::DataSynonymAndIdEquationFacts::
    DataDescriptorsAreWellFormedAndComparable(
        opt::IRContext* context, const protobufs::DataDescriptor& dd1,
        const protobufs::DataDescriptor& dd2) const {
  auto end_type_id_1 = fuzzerutil::WalkCompositeTypeIndices(
      context, context->get_def_use_mgr()->GetDef(dd1.object())->type_id(),
      dd1.index());
  auto end_type_id_2 = fuzzerutil::WalkCompositeTypeIndices(
      context, context->get_def_use_mgr()->GetDef(dd2.object())->type_id(),
      dd2.index());
  // The end types of the data descriptors must exist.
  if (end_type_id_1 == 0 || end_type_id_2 == 0) {
    return false;
  }
  // If the end types are the same, the data descriptors are comparable.
  if (end_type_id_1 == end_type_id_2) {
    return true;
  }
  // Otherwise they are only comparable if they are integer scalars or integer
  // vectors that differ only in signedness.

  // Get both types.
  const opt::analysis::Type* type_1 =
      context->get_type_mgr()->GetType(end_type_id_1);
  const opt::analysis::Type* type_2 =
      context->get_type_mgr()->GetType(end_type_id_2);

  // If the first type is a vector, check that the second type is a vector of
  // the same width, and drill down to the vector element types.
  if (type_1->AsVector()) {
    if (!type_2->AsVector()) {
      return false;
    }
    if (type_1->AsVector()->element_count() !=
        type_2->AsVector()->element_count()) {
      return false;
    }
    type_1 = type_1->AsVector()->element_type();
    type_2 = type_2->AsVector()->element_type();
  }
  // Check that type_1 and type_2 are both integer types of the same bit-width
  // (but with potentially different signedness).
  auto integer_type_1 = type_1->AsInteger();
  auto integer_type_2 = type_2->AsInteger();
  return integer_type_1 && integer_type_2 &&
         integer_type_1->width() == integer_type_2->width();
}

std::vector<const protobufs::DataDescriptor*>
FactManager::DataSynonymAndIdEquationFacts::GetSynonymsForDataDescriptor(
    const protobufs::DataDescriptor& data_descriptor,
    opt::IRContext* context) const {
  ComputeClosureOfFacts(context);
  if (synonymous_.Exists(data_descriptor)) {
    return synonymous_.GetEquivalenceClass(data_descriptor);
  }
  return std::vector<const protobufs::DataDescriptor*>();
}

std::vector<uint32_t>
FactManager::DataSynonymAndIdEquationFacts ::GetIdsForWhichSynonymsAreKnown(
    opt::IRContext* context) const {
  ComputeClosureOfFacts(context);
  std::vector<uint32_t> result;
  for (auto& data_descriptor : synonymous_.GetAllKnownValues()) {
    if (data_descriptor->index().empty()) {
      result.push_back(data_descriptor->object());
    }
  }
  return result;
}

bool FactManager::DataSynonymAndIdEquationFacts::IsSynonymous(
    const protobufs::DataDescriptor& data_descriptor1,
    const protobufs::DataDescriptor& data_descriptor2,
    opt::IRContext* context) const {
  const_cast<FactManager::DataSynonymAndIdEquationFacts*>(this)
      ->ComputeClosureOfFacts(context);
  return synonymous_.Exists(data_descriptor1) &&
         synonymous_.Exists(data_descriptor2) &&
         synonymous_.IsEquivalent(data_descriptor1, data_descriptor2);
}

// End of data synonym facts
//==============================

//==============================
// Dead block facts

// The purpose of this class is to group the fields and data used to represent
// facts about data blocks.
class FactManager::DeadBlockFacts {
 public:
  // See method in FactManager which delegates to this method.
  void AddFact(const protobufs::FactBlockIsDead& fact);

  // See method in FactManager which delegates to this method.
  bool BlockIsDead(uint32_t block_id) const;

 private:
  std::set<uint32_t> dead_block_ids_;
};

void FactManager::DeadBlockFacts::AddFact(
    const protobufs::FactBlockIsDead& fact) {
  dead_block_ids_.insert(fact.block_id());
}

bool FactManager::DeadBlockFacts::BlockIsDead(uint32_t block_id) const {
  return dead_block_ids_.count(block_id) != 0;
}

// End of dead block facts
//==============================

//==============================
// Livesafe function facts

// The purpose of this class is to group the fields and data used to represent
// facts about livesafe functions.
class FactManager::LivesafeFunctionFacts {
 public:
  // See method in FactManager which delegates to this method.
  void AddFact(const protobufs::FactFunctionIsLivesafe& fact);

  // See method in FactManager which delegates to this method.
  bool FunctionIsLivesafe(uint32_t function_id) const;

 private:
  std::set<uint32_t> livesafe_function_ids_;
};

void FactManager::LivesafeFunctionFacts::AddFact(
    const protobufs::FactFunctionIsLivesafe& fact) {
  livesafe_function_ids_.insert(fact.function_id());
}

bool FactManager::LivesafeFunctionFacts::FunctionIsLivesafe(
    uint32_t function_id) const {
  return livesafe_function_ids_.count(function_id) != 0;
}

// End of livesafe function facts
//==============================

//==============================
// Irrelevant pointee value facts

// The purpose of this class is to group the fields and data used to represent
// facts about pointers whose pointee values are irrelevant.
class FactManager::IrrelevantPointeeValueFacts {
 public:
  // See method in FactManager which delegates to this method.
  void AddFact(const protobufs::FactPointeeValueIsIrrelevant& fact);

  // See method in FactManager which delegates to this method.
  bool PointeeValueIsIrrelevant(uint32_t pointer_id) const;

 private:
  std::set<uint32_t> pointers_to_irrelevant_pointees_ids_;
};

void FactManager::IrrelevantPointeeValueFacts::AddFact(
    const protobufs::FactPointeeValueIsIrrelevant& fact) {
  pointers_to_irrelevant_pointees_ids_.insert(fact.pointer_id());
}

bool FactManager::IrrelevantPointeeValueFacts::PointeeValueIsIrrelevant(
    uint32_t pointer_id) const {
  return pointers_to_irrelevant_pointees_ids_.count(pointer_id) != 0;
}

// End of arbitrarily-valued variable facts
//==============================

FactManager::FactManager()
    : uniform_constant_facts_(MakeUnique<ConstantUniformFacts>()),
      data_synonym_and_id_equation_facts_(
          MakeUnique<DataSynonymAndIdEquationFacts>()),
      dead_block_facts_(MakeUnique<DeadBlockFacts>()),
      livesafe_function_facts_(MakeUnique<LivesafeFunctionFacts>()),
      irrelevant_pointee_value_facts_(
          MakeUnique<IrrelevantPointeeValueFacts>()) {}

FactManager::~FactManager() = default;

void FactManager::AddFacts(const MessageConsumer& message_consumer,
                           const protobufs::FactSequence& initial_facts,
                           opt::IRContext* context) {
  for (auto& fact : initial_facts.fact()) {
    if (!AddFact(fact, context)) {
      message_consumer(
          SPV_MSG_WARNING, nullptr, {},
          ("Invalid fact " + ToString(fact) + " ignored.").c_str());
    }
  }
}

bool FactManager::AddFact(const fuzz::protobufs::Fact& fact,
                          opt::IRContext* context) {
  switch (fact.fact_case()) {
    case protobufs::Fact::kConstantUniformFact:
      return uniform_constant_facts_->AddFact(fact.constant_uniform_fact(),
                                              context);
    case protobufs::Fact::kDataSynonymFact:
      data_synonym_and_id_equation_facts_->AddFact(fact.data_synonym_fact(),
                                                   context);
      return true;
    case protobufs::Fact::kBlockIsDeadFact:
      dead_block_facts_->AddFact(fact.block_is_dead_fact());
      return true;
    case protobufs::Fact::kFunctionIsLivesafeFact:
      livesafe_function_facts_->AddFact(fact.function_is_livesafe_fact());
      return true;
    default:
      assert(false && "Unknown fact type.");
      return false;
  }
}

void FactManager::AddFactDataSynonym(const protobufs::DataDescriptor& data1,
                                     const protobufs::DataDescriptor& data2,
                                     opt::IRContext* context) {
  protobufs::FactDataSynonym fact;
  *fact.mutable_data1() = data1;
  *fact.mutable_data2() = data2;
  data_synonym_and_id_equation_facts_->AddFact(fact, context);
}

std::vector<uint32_t> FactManager::GetConstantsAvailableFromUniformsForType(
    opt::IRContext* ir_context, uint32_t type_id) const {
  return uniform_constant_facts_->GetConstantsAvailableFromUniformsForType(
      ir_context, type_id);
}

const std::vector<protobufs::UniformBufferElementDescriptor>
FactManager::GetUniformDescriptorsForConstant(opt::IRContext* ir_context,
                                              uint32_t constant_id) const {
  return uniform_constant_facts_->GetUniformDescriptorsForConstant(ir_context,
                                                                   constant_id);
}

uint32_t FactManager::GetConstantFromUniformDescriptor(
    opt::IRContext* context,
    const protobufs::UniformBufferElementDescriptor& uniform_descriptor) const {
  return uniform_constant_facts_->GetConstantFromUniformDescriptor(
      context, uniform_descriptor);
}

std::vector<uint32_t> FactManager::GetTypesForWhichUniformValuesAreKnown()
    const {
  return uniform_constant_facts_->GetTypesForWhichUniformValuesAreKnown();
}

const std::vector<std::pair<protobufs::FactConstantUniform, uint32_t>>&
FactManager::GetConstantUniformFactsAndTypes() const {
  return uniform_constant_facts_->GetConstantUniformFactsAndTypes();
}

std::vector<uint32_t> FactManager::GetIdsForWhichSynonymsAreKnown(
    opt::IRContext* context) const {
  return data_synonym_and_id_equation_facts_->GetIdsForWhichSynonymsAreKnown(
      context);
}

std::vector<const protobufs::DataDescriptor*>
FactManager::GetSynonymsForDataDescriptor(
    const protobufs::DataDescriptor& data_descriptor,
    opt::IRContext* context) const {
  return data_synonym_and_id_equation_facts_->GetSynonymsForDataDescriptor(
      data_descriptor, context);
}

std::vector<const protobufs::DataDescriptor*> FactManager::GetSynonymsForId(
    uint32_t id, opt::IRContext* context) const {
  return GetSynonymsForDataDescriptor(MakeDataDescriptor(id, {}), context);
}

bool FactManager::IsSynonymous(
    const protobufs::DataDescriptor& data_descriptor1,
    const protobufs::DataDescriptor& data_descriptor2,
    opt::IRContext* context) const {
  return data_synonym_and_id_equation_facts_->IsSynonymous(
      data_descriptor1, data_descriptor2, context);
}

bool FactManager::BlockIsDead(uint32_t block_id) const {
  return dead_block_facts_->BlockIsDead(block_id);
}

void FactManager::AddFactBlockIsDead(uint32_t block_id) {
  protobufs::FactBlockIsDead fact;
  fact.set_block_id(block_id);
  dead_block_facts_->AddFact(fact);
}

bool FactManager::FunctionIsLivesafe(uint32_t function_id) const {
  return livesafe_function_facts_->FunctionIsLivesafe(function_id);
}

void FactManager::AddFactFunctionIsLivesafe(uint32_t function_id) {
  protobufs::FactFunctionIsLivesafe fact;
  fact.set_function_id(function_id);
  livesafe_function_facts_->AddFact(fact);
}

bool FactManager::PointeeValueIsIrrelevant(uint32_t pointer_id) const {
  return irrelevant_pointee_value_facts_->PointeeValueIsIrrelevant(pointer_id);
}

void FactManager::AddFactValueOfPointeeIsIrrelevant(uint32_t pointer_id) {
  protobufs::FactPointeeValueIsIrrelevant fact;
  fact.set_pointer_id(pointer_id);
  irrelevant_pointee_value_facts_->AddFact(fact);
}

void FactManager::AddFactIdEquation(uint32_t lhs_id, SpvOp opcode,
                                    const std::vector<uint32_t>& rhs_id,
                                    opt::IRContext* context) {
  protobufs::FactIdEquation fact;
  fact.set_lhs_id(lhs_id);
  fact.set_opcode(opcode);
  for (auto an_rhs_id : rhs_id) {
    fact.add_rhs_id(an_rhs_id);
  }
  data_synonym_and_id_equation_facts_->AddFact(fact, context);
}

}  // namespace fuzz
}  // namespace spvtools

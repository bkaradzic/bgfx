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

#include "fact_manager.h"

#include <sstream>
#include <unordered_map>

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

void FactManager::AddFacts(const MessageConsumer& message_consumer,
                           const protobufs::FactSequence& initial_facts,
                           opt::IRContext* context) {
  for (auto& fact : initial_facts.fact()) {
    if (!AddFact(fact, context)) {
      auto message = "Invalid fact " + ToString(fact) + " ignored.";
      message_consumer(SPV_MSG_WARNING, nullptr, {}, message.c_str());
    }
  }
}

bool FactManager::AddFact(const fuzz::protobufs::Fact& fact,
                          opt::IRContext* context) {
  switch (fact.fact_case()) {
    case protobufs::Fact::kConstantUniformFact:
      return constant_uniform_facts_.AddFact(fact.constant_uniform_fact(),
                                             context);
    case protobufs::Fact::kDataSynonymFact:
      data_synonym_and_id_equation_facts_.AddFact(fact.data_synonym_fact(),
                                                  context);
      return true;
    case protobufs::Fact::kBlockIsDeadFact:
      dead_block_facts_.AddFact(fact.block_is_dead_fact());
      return true;
    case protobufs::Fact::kFunctionIsLivesafeFact:
      livesafe_function_facts_.AddFact(fact.function_is_livesafe_fact());
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
  data_synonym_and_id_equation_facts_.AddFact(fact, context);
}

std::vector<uint32_t> FactManager::GetConstantsAvailableFromUniformsForType(
    opt::IRContext* ir_context, uint32_t type_id) const {
  return constant_uniform_facts_.GetConstantsAvailableFromUniformsForType(
      ir_context, type_id);
}

std::vector<protobufs::UniformBufferElementDescriptor>
FactManager::GetUniformDescriptorsForConstant(opt::IRContext* ir_context,
                                              uint32_t constant_id) const {
  return constant_uniform_facts_.GetUniformDescriptorsForConstant(ir_context,
                                                                  constant_id);
}

uint32_t FactManager::GetConstantFromUniformDescriptor(
    opt::IRContext* context,
    const protobufs::UniformBufferElementDescriptor& uniform_descriptor) const {
  return constant_uniform_facts_.GetConstantFromUniformDescriptor(
      context, uniform_descriptor);
}

std::vector<uint32_t> FactManager::GetTypesForWhichUniformValuesAreKnown()
    const {
  return constant_uniform_facts_.GetTypesForWhichUniformValuesAreKnown();
}

const std::vector<std::pair<protobufs::FactConstantUniform, uint32_t>>&
FactManager::GetConstantUniformFactsAndTypes() const {
  return constant_uniform_facts_.GetConstantUniformFactsAndTypes();
}

std::vector<uint32_t> FactManager::GetIdsForWhichSynonymsAreKnown() const {
  return data_synonym_and_id_equation_facts_.GetIdsForWhichSynonymsAreKnown();
}

std::vector<const protobufs::DataDescriptor*>
FactManager::GetSynonymsForDataDescriptor(
    const protobufs::DataDescriptor& data_descriptor) const {
  return data_synonym_and_id_equation_facts_.GetSynonymsForDataDescriptor(
      data_descriptor);
}

std::vector<const protobufs::DataDescriptor*> FactManager::GetSynonymsForId(
    uint32_t id) const {
  return GetSynonymsForDataDescriptor(MakeDataDescriptor(id, {}));
}

bool FactManager::IsSynonymous(
    const protobufs::DataDescriptor& data_descriptor1,
    const protobufs::DataDescriptor& data_descriptor2) const {
  return data_synonym_and_id_equation_facts_.IsSynonymous(data_descriptor1,
                                                          data_descriptor2);
}

bool FactManager::BlockIsDead(uint32_t block_id) const {
  return dead_block_facts_.BlockIsDead(block_id);
}

void FactManager::AddFactBlockIsDead(uint32_t block_id) {
  protobufs::FactBlockIsDead fact;
  fact.set_block_id(block_id);
  dead_block_facts_.AddFact(fact);
}

bool FactManager::FunctionIsLivesafe(uint32_t function_id) const {
  return livesafe_function_facts_.FunctionIsLivesafe(function_id);
}

void FactManager::AddFactFunctionIsLivesafe(uint32_t function_id) {
  protobufs::FactFunctionIsLivesafe fact;
  fact.set_function_id(function_id);
  livesafe_function_facts_.AddFact(fact);
}

bool FactManager::PointeeValueIsIrrelevant(uint32_t pointer_id) const {
  return irrelevant_value_facts_.PointeeValueIsIrrelevant(pointer_id);
}

bool FactManager::IdIsIrrelevant(uint32_t result_id) const {
  return irrelevant_value_facts_.IdIsIrrelevant(result_id);
}

void FactManager::AddFactValueOfPointeeIsIrrelevant(uint32_t pointer_id) {
  protobufs::FactPointeeValueIsIrrelevant fact;
  fact.set_pointer_id(pointer_id);
  irrelevant_value_facts_.AddFact(fact);
}

void FactManager::AddFactIdIsIrrelevant(uint32_t result_id) {
  protobufs::FactIdIsIrrelevant fact;
  fact.set_result_id(result_id);
  irrelevant_value_facts_.AddFact(fact);
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
  data_synonym_and_id_equation_facts_.AddFact(fact, context);
}

void FactManager::ComputeClosureOfFacts(
    opt::IRContext* ir_context, uint32_t maximum_equivalence_class_size) {
  data_synonym_and_id_equation_facts_.ComputeClosureOfFacts(
      ir_context, maximum_equivalence_class_size);
}

}  // namespace fuzz
}  // namespace spvtools

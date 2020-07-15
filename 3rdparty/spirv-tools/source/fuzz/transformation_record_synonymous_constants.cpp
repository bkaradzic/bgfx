// Copyright (c) 2020 Stefano Milizia
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

#include "transformation_record_synonymous_constants.h"

namespace spvtools {
namespace fuzz {

namespace {
bool IsScalarZeroConstant(const opt::analysis::Constant* constant) {
  return constant->AsScalarConstant() && constant->IsZero();
}
}  // namespace

TransformationRecordSynonymousConstants::
    TransformationRecordSynonymousConstants(
        const protobufs::TransformationRecordSynonymousConstants& message)
    : message_(message) {}

TransformationRecordSynonymousConstants::
    TransformationRecordSynonymousConstants(uint32_t constant1_id,
                                            uint32_t constant2_id) {
  message_.set_constant1_id(constant1_id);
  message_.set_constant2_id(constant2_id);
}

bool TransformationRecordSynonymousConstants::IsApplicable(
    opt::IRContext* ir_context,
    const TransformationContext& /* unused */) const {
  // The ids must be different
  if (message_.constant1_id() == message_.constant2_id()) {
    return false;
  }

  auto constant1 = ir_context->get_constant_mgr()->FindDeclaredConstant(
      message_.constant1_id());
  auto constant2 = ir_context->get_constant_mgr()->FindDeclaredConstant(
      message_.constant2_id());

  // The constants must exist
  if (constant1 == nullptr || constant2 == nullptr) {
    return false;
  }

  // If the constants are equal, then they are equivalent
  if (constant1 == constant2) {
    return true;
  }

  // If the constants are two integers (signed or unsigned), they are equal
  // if they have the same width and the same data words.
  if (constant1->AsIntConstant() && constant2->AsIntConstant() &&
      constant1->type()->AsInteger()->width() ==
          constant2->type()->AsInteger()->width() &&
      constant1->AsIntConstant()->words() ==
          constant2->AsIntConstant()->words()) {
    return true;
  }

  // The types must be the same
  if (!constant1->type()->IsSame(constant2->type())) {
    return false;
  }

  // The constants are equivalent if one is null and the other is a static
  // constant with value 0.
  return (constant1->AsNullConstant() && IsScalarZeroConstant(constant2)) ||
         (IsScalarZeroConstant(constant1) && constant2->AsNullConstant());
}

void TransformationRecordSynonymousConstants::Apply(
    opt::IRContext* ir_context,
    TransformationContext* transformation_context) const {
  protobufs::FactDataSynonym fact_data_synonym;
  // Define the two equivalent data descriptors (just containing the ids)
  *fact_data_synonym.mutable_data1() =
      MakeDataDescriptor(message_.constant1_id(), {});
  *fact_data_synonym.mutable_data2() =
      MakeDataDescriptor(message_.constant2_id(), {});
  protobufs::Fact fact;
  *fact.mutable_data_synonym_fact() = fact_data_synonym;

  // Add the fact to the fact manager
  transformation_context->GetFactManager()->AddFact(fact, ir_context);
}

protobufs::Transformation TransformationRecordSynonymousConstants::ToMessage()
    const {
  protobufs::Transformation result;
  *result.mutable_record_synonymous_constants() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools

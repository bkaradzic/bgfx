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

#ifndef SOURCE_FUZZ_TRANSFORMATION_RECORD_SYNONYMOUS_CONSTANTS_H
#define SOURCE_FUZZ_TRANSFORMATION_RECORD_SYNONYMOUS_CONSTANTS_H

#include "source/fuzz/transformation.h"

namespace spvtools {
namespace fuzz {

class TransformationRecordSynonymousConstants : public Transformation {
 public:
  explicit TransformationRecordSynonymousConstants(
      const protobufs::TransformationRecordSynonymousConstants& message);

  TransformationRecordSynonymousConstants(uint32_t constant1_id,
                                          uint32_t constant2_id);

  // - |message_.constant_id| and |message_.synonym_id| are distinct ids
  //   of constants
  // - |message_.constant_id| and |message_.synonym_id| refer to constants
  //   that are equal or equivalent.
  //   Two integers with the same width and value are equal, even if one is
  //   signed and the other is not.
  //   Constants are equivalent if both of them represent zero-like scalar
  //   values of the same type (for example OpConstant of type int and value
  //   0 and OpConstantNull of type int).
  bool IsApplicable(
      opt::IRContext* ir_context,
      const TransformationContext& transformation_context) const override;

  // Adds the fact that |message_.constant_id| and |message_.synonym_id|
  // are synonyms to the fact manager. The module is not changed.
  void Apply(opt::IRContext* ir_context,
             TransformationContext* transformation_context) const override;

  protobufs::Transformation ToMessage() const override;

 private:
  protobufs::TransformationRecordSynonymousConstants message_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_RECORD_SYNONYMOUS_CONSTANTS

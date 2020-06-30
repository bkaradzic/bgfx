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

#ifndef SOURCE_FUZZ_TRANSFORMATION_REPLACE_ID_WITH_SYNONYM_H_
#define SOURCE_FUZZ_TRANSFORMATION_REPLACE_ID_WITH_SYNONYM_H_

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

class TransformationReplaceIdWithSynonym : public Transformation {
 public:
  explicit TransformationReplaceIdWithSynonym(
      const protobufs::TransformationReplaceIdWithSynonym& message);

  TransformationReplaceIdWithSynonym(
      protobufs::IdUseDescriptor id_use_descriptor, uint32_t synonymous_id);

  // - The fact manager must know that the id identified by
  //   |message_.id_use_descriptor| is synonomous with
  //   |message_.synonymous_id|.
  // - Replacing the id in |message_.id_use_descriptor| by
  //   |message_.synonymous_id| must respect SPIR-V's rules about uses being
  //   dominated by their definitions.
  // - The id must not be an index into an access chain whose base object has
  //   struct type, as such indices must be constants.
  // - The id must not be a pointer argument to a function call (because the
  //   synonym might not be a memory object declaration).
  // - |fresh_id_for_temporary| must be 0.
  bool IsApplicable(
      opt::IRContext* ir_context,
      const TransformationContext& transformation_context) const override;

  // Replaces the use identified by |message_.id_use_descriptor| with the
  // synonymous id identified by |message_.synonymous_id|.
  void Apply(opt::IRContext* ir_context,
             TransformationContext* transformation_context) const override;

  protobufs::Transformation ToMessage() const override;

  // Checks whether various conditions hold related to the acceptability of
  // replacing the id use at |use_in_operand_index| of |use_instruction| with
  // a synonym.  In particular, this checks that:
  // - the id use is not an index into a struct field in an OpAccessChain - such
  //   indices must be constants, so it is dangerous to replace them.
  // - the id use is not a pointer function call argument, on which there are
  //   restrictions that make replacement problematic.
  static bool UseCanBeReplacedWithSynonym(opt::IRContext* ir_context,
                                          opt::Instruction* use_instruction,
                                          uint32_t use_in_operand_index);

 private:
  protobufs::TransformationReplaceIdWithSynonym message_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_REPLACE_ID_WITH_SYNONYM_H_

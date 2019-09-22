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

#include "source/fuzz/transformation_replace_id_with_synonym.h"

#include <algorithm>

#include "source/fuzz/data_descriptor.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/id_use_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationReplaceIdWithSynonym::TransformationReplaceIdWithSynonym(
    const spvtools::fuzz::protobufs::TransformationReplaceIdWithSynonym&
        message)
    : message_(message) {}

TransformationReplaceIdWithSynonym::TransformationReplaceIdWithSynonym(
    protobufs::IdUseDescriptor id_use_descriptor,
    protobufs::DataDescriptor data_descriptor,
    uint32_t fresh_id_for_temporary) {
  assert(fresh_id_for_temporary == 0 && data_descriptor.index().size() == 0 &&
         "At present we do not support making an id that is synonymous with an "
         "index into a composite.");
  *message_.mutable_id_use_descriptor() = std::move(id_use_descriptor);
  *message_.mutable_data_descriptor() = std::move(data_descriptor);
  message_.set_fresh_id_for_temporary(fresh_id_for_temporary);
}

bool TransformationReplaceIdWithSynonym::IsApplicable(
    spvtools::opt::IRContext* context,
    const spvtools::fuzz::FactManager& fact_manager) const {
  auto id_of_interest = message_.id_use_descriptor().id_of_interest();

  // Does the fact manager know about the synonym?
  if (fact_manager.GetIdsForWhichSynonymsAreKnown().count(id_of_interest) ==
      0) {
    return false;
  }

  auto available_synonyms = fact_manager.GetSynonymsForId(id_of_interest);
  if (std::find_if(available_synonyms.begin(), available_synonyms.end(),
                   [this](protobufs::DataDescriptor dd) -> bool {
                     return DataDescriptorEquals()(&dd,
                                                   &message_.data_descriptor());
                   }) == available_synonyms.end()) {
    return false;
  }

  auto use_instruction =
      transformation::FindInstruction(message_.id_use_descriptor(), context);
  if (!use_instruction) {
    return false;
  }

  if (!ReplacingUseWithSynonymIsOk(
          context, use_instruction,
          message_.id_use_descriptor().in_operand_index(),
          message_.data_descriptor())) {
    return false;
  }

  assert(message_.fresh_id_for_temporary() == 0);
  assert(message_.data_descriptor().index().empty());

  return true;
}

void TransformationReplaceIdWithSynonym::Apply(
    spvtools::opt::IRContext* context,
    spvtools::fuzz::FactManager* /*unused*/) const {
  assert(message_.data_descriptor().index().empty());
  auto instruction_to_change =
      transformation::FindInstruction(message_.id_use_descriptor(), context);
  instruction_to_change->SetInOperand(
      message_.id_use_descriptor().in_operand_index(),
      {message_.data_descriptor().object()});
  context->InvalidateAnalysesExceptFor(opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationReplaceIdWithSynonym::ToMessage()
    const {
  protobufs::Transformation result;
  *result.mutable_replace_id_with_synonym() = message_;
  return result;
}

bool TransformationReplaceIdWithSynonym::ReplacingUseWithSynonymIsOk(
    opt::IRContext* context, opt::Instruction* use_instruction,
    uint32_t use_in_operand_index, const protobufs::DataDescriptor& synonym) {
  auto defining_instruction =
      context->get_def_use_mgr()->GetDef(synonym.object());

  if (use_instruction == defining_instruction) {
    // If we have an instruction:
    //   %a = OpCopyObject %t %b
    // then we know %a and %b are synonymous, but we do *not* want to turn
    // this into:
    //   %a = OpCopyObject %t %a
    // We require this special case because an instruction dominates itself.
    return false;
  }

  if (use_instruction->opcode() == SpvOpAccessChain &&
      use_in_operand_index > 0) {
    // This is an access chain index.  If the object being accessed has
    // pointer-to-struct type then we cannot replace the use with a synonym, as
    // the use needs to be an OpConstant.
    auto object_being_accessed = context->get_def_use_mgr()->GetDef(
        use_instruction->GetSingleWordInOperand(0));
    auto pointer_type =
        context->get_type_mgr()->GetType(object_being_accessed->type_id());
    assert(pointer_type->AsPointer());
    if (pointer_type->AsPointer()->pointee_type()->AsStruct()) {
      return false;
    }
  }

  // We now need to check that replacing the use with the synonym will respect
  // dominance rules - i.e. the synonym needs to dominate the use.
  auto dominator_analysis = context->GetDominatorAnalysis(
      context->get_instr_block(use_instruction)->GetParent());
  if (use_instruction->opcode() == SpvOpPhi) {
    // In the case where the use is an operand to OpPhi, it is actually the
    // *parent* block associated with the operand that must be dominated by the
    // synonym.
    auto parent_block =
        use_instruction->GetSingleWordInOperand(use_in_operand_index + 1);
    if (!dominator_analysis->Dominates(
            context->get_instr_block(defining_instruction)->id(),
            parent_block)) {
      return false;
    }
  } else if (!dominator_analysis->Dominates(defining_instruction,
                                            use_instruction)) {
    return false;
  }
  return true;
}

}  // namespace fuzz
}  // namespace spvtools

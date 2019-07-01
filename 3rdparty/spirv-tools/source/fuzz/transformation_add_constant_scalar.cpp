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

#include "source/fuzz/transformation_add_constant_scalar.h"

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

using opt::IRContext;

bool IsApplicable(const protobufs::TransformationAddConstantScalar& message,
                  IRContext* context,
                  const spvtools::fuzz::FactManager& /*unused*/) {
  // The id needs to be fresh.
  if (!fuzzerutil::IsFreshId(context, message.fresh_id())) {
    return false;
  }
  // The type id for the scalar must exist and be a type.
  auto type = context->get_type_mgr()->GetType(message.type_id());
  if (!type) {
    return false;
  }
  uint32_t width;
  if (type->AsFloat()) {
    width = type->AsFloat()->width();
  } else if (type->AsInteger()) {
    width = type->AsInteger()->width();
  } else {
    return false;
  }
  // The number of words is the integer floor of the width.
  auto words = (width + 32 - 1) / 32;

  // The number of words provided by the transformation needs to match the
  // width of the type.
  return static_cast<uint32_t>(message.word().size()) == words;
}

void Apply(const protobufs::TransformationAddConstantScalar& message,
           IRContext* context, spvtools::fuzz::FactManager* /*unused*/) {
  opt::Instruction::OperandList operand_list;
  for (auto word : message.word()) {
    operand_list.push_back({SPV_OPERAND_TYPE_LITERAL_INTEGER, {word}});
  }
  context->module()->AddGlobalValue(
      MakeUnique<opt::Instruction>(context, SpvOpConstant, message.type_id(),
                                   message.fresh_id(), operand_list));

  fuzzerutil::UpdateModuleIdBound(context, message.fresh_id());

  // We have added an instruction to the module, so need to be careful about the
  // validity of existing analyses.
  context->InvalidateAnalysesExceptFor(IRContext::Analysis::kAnalysisNone);
}

protobufs::TransformationAddConstantScalar MakeTransformationAddConstantScalar(
    uint32_t fresh_id, uint32_t type_id, std::vector<uint32_t> words) {
  protobufs::TransformationAddConstantScalar result;
  result.set_fresh_id(fresh_id);
  result.set_type_id(type_id);
  for (auto word : words) {
    result.add_word(word);
  }
  return result;
}

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

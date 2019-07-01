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

#include "source/fuzz/transformation_add_type_int.h"

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

using opt::IRContext;

bool IsApplicable(const protobufs::TransformationAddTypeInt& message,
                  IRContext* context,
                  const spvtools::fuzz::FactManager& /*unused*/) {
  // The id must be fresh.
  if (!fuzzerutil::IsFreshId(context, message.fresh_id())) {
    return false;
  }

  // Applicable if there is no int type with this width and signedness already
  // declared in the module.
  opt::analysis::Integer int_type(message.width(), message.is_signed());
  return context->get_type_mgr()->GetId(&int_type) == 0;
}

void Apply(const protobufs::TransformationAddTypeInt& message,
           IRContext* context, spvtools::fuzz::FactManager* /*unused*/) {
  opt::Instruction::OperandList in_operands = {
      {SPV_OPERAND_TYPE_LITERAL_INTEGER, {message.width()}},
      {SPV_OPERAND_TYPE_LITERAL_INTEGER, {message.is_signed() ? 1u : 0u}}};
  context->module()->AddType(MakeUnique<opt::Instruction>(
      context, SpvOpTypeInt, 0, message.fresh_id(), in_operands));
  fuzzerutil::UpdateModuleIdBound(context, message.fresh_id());
  // We have added an instruction to the module, so need to be careful about the
  // validity of existing analyses.
  context->InvalidateAnalysesExceptFor(IRContext::Analysis::kAnalysisNone);
}

protobufs::TransformationAddTypeInt MakeTransformationAddTypeInt(
    uint32_t fresh_id, uint32_t width, bool is_signed) {
  protobufs::TransformationAddTypeInt result;
  result.set_fresh_id(fresh_id);
  result.set_width(width);
  result.set_is_signed(is_signed);
  return result;
}

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

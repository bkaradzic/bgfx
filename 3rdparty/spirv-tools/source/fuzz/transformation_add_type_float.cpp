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

#include "source/fuzz/transformation_add_type_float.h"

#include "source/fuzz/fuzzer_util.h"

namespace spvtools {
namespace fuzz {
namespace transformation {

using opt::IRContext;

bool IsApplicable(const protobufs::TransformationAddTypeFloat& message,
                  IRContext* context,
                  const spvtools::fuzz::FactManager& /*unused*/) {
  // The id must be fresh.
  if (!fuzzerutil::IsFreshId(context, message.fresh_id())) {
    return false;
  }

  // Applicable if there is no float type with this width already declared in
  // the module.
  opt::analysis::Float float_type(message.width());
  return context->get_type_mgr()->GetId(&float_type) == 0;
}

void Apply(const protobufs::TransformationAddTypeFloat& message,
           IRContext* context, spvtools::fuzz::FactManager* /*unused*/) {
  opt::Instruction::OperandList width = {
      {SPV_OPERAND_TYPE_LITERAL_INTEGER, {message.width()}}};
  context->module()->AddType(MakeUnique<opt::Instruction>(
      context, SpvOpTypeFloat, 0, message.fresh_id(), width));
  fuzzerutil::UpdateModuleIdBound(context, message.fresh_id());
  // We have added an instruction to the module, so need to be careful about the
  // validity of existing analyses.
  context->InvalidateAnalysesExceptFor(IRContext::Analysis::kAnalysisNone);
}

protobufs::TransformationAddTypeFloat MakeTransformationAddTypeFloat(
    uint32_t fresh_id, uint32_t width) {
  protobufs::TransformationAddTypeFloat result;
  result.set_fresh_id(fresh_id);
  result.set_width(width);
  return result;
}

}  // namespace transformation
}  // namespace fuzz
}  // namespace spvtools

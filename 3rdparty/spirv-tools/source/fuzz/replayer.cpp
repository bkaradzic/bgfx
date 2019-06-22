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

#include "source/fuzz/replayer.h"

#include <utility>

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation_add_constant_boolean.h"
#include "source/fuzz/transformation_add_constant_scalar.h"
#include "source/fuzz/transformation_add_dead_break.h"
#include "source/fuzz/transformation_add_type_boolean.h"
#include "source/fuzz/transformation_add_type_float.h"
#include "source/fuzz/transformation_add_type_int.h"
#include "source/fuzz/transformation_add_type_pointer.h"
#include "source/fuzz/transformation_move_block_down.h"
#include "source/fuzz/transformation_replace_boolean_constant_with_constant_binary.h"
#include "source/fuzz/transformation_replace_constant_with_uniform.h"
#include "source/fuzz/transformation_split_block.h"
#include "source/opt/build_module.h"
#include "source/util/make_unique.h"

namespace spvtools {
namespace fuzz {

namespace {

// Returns true if and only if the precondition for |transformation| holds, with
// respect to the given |context| and |fact_manager|.
bool IsApplicable(const protobufs::Transformation& transformation,
                  opt::IRContext* context, const FactManager& fact_manager) {
  switch (transformation.transformation_case()) {
    case protobufs::Transformation::TransformationCase::kAddConstantBoolean:
      return transformation::IsApplicable(transformation.add_constant_boolean(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddConstantScalar:
      return transformation::IsApplicable(transformation.add_constant_scalar(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddDeadBreak:
      return transformation::IsApplicable(transformation.add_dead_break(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddTypeBoolean:
      return transformation::IsApplicable(transformation.add_type_boolean(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddTypeFloat:
      return transformation::IsApplicable(transformation.add_type_float(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddTypeInt:
      return transformation::IsApplicable(transformation.add_type_int(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kAddTypePointer:
      return transformation::IsApplicable(transformation.add_type_pointer(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::kMoveBlockDown:
      return transformation::IsApplicable(transformation.move_block_down(),
                                          context, fact_manager);
    case protobufs::Transformation::TransformationCase::
        kReplaceBooleanConstantWithConstantBinary:
      return transformation::IsApplicable(
          transformation.replace_boolean_constant_with_constant_binary(),
          context, fact_manager);
    case protobufs::Transformation::TransformationCase::
        kReplaceConstantWithUniform:
      return transformation::IsApplicable(
          transformation.replace_constant_with_uniform(), context,
          fact_manager);
    case protobufs::Transformation::TransformationCase::kSplitBlock:
      return transformation::IsApplicable(transformation.split_block(), context,
                                          fact_manager);
    default:
      assert(transformation.transformation_case() ==
                 protobufs::Transformation::TRANSFORMATION_NOT_SET &&
             "Unhandled transformation type.");
      assert(false && "An unset transformation was encountered.");
      return false;
  }
}

// Requires that IsApplicable holds.  Applies |transformation| to the given
// |context| and |fact_manager|.
void Apply(const protobufs::Transformation& transformation,
           opt::IRContext* context, FactManager* fact_manager) {
  switch (transformation.transformation_case()) {
    case protobufs::Transformation::TransformationCase::kAddConstantBoolean:
      transformation::Apply(transformation.add_constant_boolean(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddConstantScalar:
      transformation::Apply(transformation.add_constant_scalar(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddDeadBreak:
      transformation::Apply(transformation.add_dead_break(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddTypeBoolean:
      transformation::Apply(transformation.add_type_boolean(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddTypeFloat:
      transformation::Apply(transformation.add_type_float(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddTypeInt:
      transformation::Apply(transformation.add_type_int(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kAddTypePointer:
      transformation::Apply(transformation.add_type_pointer(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kMoveBlockDown:
      transformation::Apply(transformation.move_block_down(), context,
                            fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::
        kReplaceBooleanConstantWithConstantBinary:
      transformation::Apply(
          transformation.replace_boolean_constant_with_constant_binary(),
          context, fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::
        kReplaceConstantWithUniform:
      transformation::Apply(transformation.replace_constant_with_uniform(),
                            context, fact_manager);
      break;
    case protobufs::Transformation::TransformationCase::kSplitBlock:
      transformation::Apply(transformation.split_block(), context,
                            fact_manager);
      break;
    default:
      assert(transformation.transformation_case() ==
                 protobufs::Transformation::TRANSFORMATION_NOT_SET &&
             "Unhandled transformation type.");
      assert(false && "An unset transformation was encountered.");
  }
}

}  // namespace

struct Replayer::Impl {
  explicit Impl(spv_target_env env) : target_env(env) {}

  const spv_target_env target_env;  // Target environment.
  MessageConsumer consumer;         // Message consumer.
};

Replayer::Replayer(spv_target_env env) : impl_(MakeUnique<Impl>(env)) {}

Replayer::~Replayer() = default;

void Replayer::SetMessageConsumer(MessageConsumer c) {
  impl_->consumer = std::move(c);
}

Replayer::ReplayerResultStatus Replayer::Run(
    const std::vector<uint32_t>& binary_in,
    const protobufs::FactSequence& initial_facts,
    const protobufs::TransformationSequence& transformation_sequence_in,
    std::vector<uint32_t>* binary_out,
    protobufs::TransformationSequence* transformation_sequence_out) const {
  // Check compatibility between the library version being linked with and the
  // header files being used.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  spvtools::SpirvTools tools(impl_->target_env);
  if (!tools.IsValid()) {
    impl_->consumer(SPV_MSG_ERROR, nullptr, {},
                    "Failed to create SPIRV-Tools interface; stopping.");
    return Replayer::ReplayerResultStatus::kFailedToCreateSpirvToolsInterface;
  }

  // Initial binary should be valid.
  if (!tools.Validate(&binary_in[0], binary_in.size())) {
    impl_->consumer(SPV_MSG_INFO, nullptr, {},
                    "Initial binary is invalid; stopping.");
    return Replayer::ReplayerResultStatus::kInitialBinaryInvalid;
  }

  // Build the module from the input binary.
  std::unique_ptr<opt::IRContext> ir_context = BuildModule(
      impl_->target_env, impl_->consumer, binary_in.data(), binary_in.size());
  assert(ir_context);

  FactManager fact_manager;
  if (!fact_manager.AddFacts(initial_facts, ir_context.get())) {
    return Replayer::ReplayerResultStatus::kInitialFactsInvalid;
  }

  // Consider the transformation proto messages in turn.
  for (auto& transformation : transformation_sequence_in.transformation()) {
    // Check whether the transformation can be applied.
    if (IsApplicable(transformation, ir_context.get(), fact_manager)) {
      // The transformation is applicable, so apply it, and copy it to the
      // sequence of transformations that were applied.
      Apply(transformation, ir_context.get(), &fact_manager);
      *transformation_sequence_out->add_transformation() = transformation;
    }
  }

  // Write out the module as a binary.
  ir_context->module()->ToBinary(binary_out, false);
  return Replayer::ReplayerResultStatus::kComplete;
}

}  // namespace fuzz
}  // namespace spvtools

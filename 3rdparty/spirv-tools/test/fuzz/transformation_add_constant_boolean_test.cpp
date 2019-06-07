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

#include "source/fuzz/transformation_add_constant_boolean.h"
#include "test/fuzz/fuzz_test_util.h"

namespace spvtools {
namespace fuzz {
namespace {

TEST(TransformationAddConstantBooleanTest, NeitherPresentInitiallyAddBoth) {
  std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
          %2 = OpTypeVoid
          %6 = OpTypeBool
          %3 = OpTypeFunction %2
          %4 = OpFunction %2 None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context = BuildModule(env, consumer, shader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;

  // True and false can both be added as neither is present.
  ASSERT_TRUE(transformation::IsApplicable(
      transformation::MakeTransformationAddConstantBoolean(7, true),
      context.get(), fact_manager));
  ASSERT_TRUE(transformation::IsApplicable(
      transformation::MakeTransformationAddConstantBoolean(7, false),
      context.get(), fact_manager));

  // Id 5 is already taken.
  ASSERT_FALSE(transformation::IsApplicable(
      transformation::MakeTransformationAddConstantBoolean(5, true),
      context.get(), fact_manager));

  auto add_true = transformation::MakeTransformationAddConstantBoolean(7, true);
  auto add_false =
      transformation::MakeTransformationAddConstantBoolean(8, false);

  ASSERT_TRUE(
      transformation::IsApplicable(add_true, context.get(), fact_manager));
  transformation::Apply(add_true, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // Having added true, we cannot add it again with the same id.
  ASSERT_FALSE(
      transformation::IsApplicable(add_true, context.get(), fact_manager));
  // But we can add it with a different id.
  auto add_true_again =
      transformation::MakeTransformationAddConstantBoolean(100, true);
  ASSERT_TRUE(transformation::IsApplicable(add_true_again, context.get(),
                                           fact_manager));
  transformation::Apply(add_true_again, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(
      transformation::IsApplicable(add_false, context.get(), fact_manager));
  transformation::Apply(add_false, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // Having added false, we cannot add it again with the same id.
  ASSERT_FALSE(
      transformation::IsApplicable(add_false, context.get(), fact_manager));
  // But we can add it with a different id.
  auto add_false_again =
      transformation::MakeTransformationAddConstantBoolean(101, false);
  ASSERT_TRUE(transformation::IsApplicable(add_false_again, context.get(),
                                           fact_manager));
  transformation::Apply(add_false_again, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  std::string after_transformation = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
          %2 = OpTypeVoid
          %6 = OpTypeBool
          %3 = OpTypeFunction %2
          %7 = OpConstantTrue %6
        %100 = OpConstantTrue %6
          %8 = OpConstantFalse %6
        %101 = OpConstantFalse %6
          %4 = OpFunction %2 None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  ASSERT_TRUE(IsEqual(env, after_transformation, context.get()));
}

TEST(TransformationAddConstantBooleanTest, NoOpTypeBoolPresent) {
  std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %4 = OpFunction %2 None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context = BuildModule(env, consumer, shader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;

  // Neither true nor false can be added as OpTypeBool is not present.
  ASSERT_FALSE(transformation::IsApplicable(
      transformation::MakeTransformationAddConstantBoolean(6, true),
      context.get(), fact_manager));
  ASSERT_FALSE(transformation::IsApplicable(
      transformation::MakeTransformationAddConstantBoolean(6, false),
      context.get(), fact_manager));
}

}  // namespace
}  // namespace fuzz
}  // namespace spvtools

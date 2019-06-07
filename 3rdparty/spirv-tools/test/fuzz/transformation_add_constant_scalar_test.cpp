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
#include "test/fuzz/fuzz_test_util.h"

namespace spvtools {
namespace fuzz {
namespace {

TEST(TransformationAddConstantScalarTest, BasicTest) {
  std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %8 "x"
               OpName %12 "y"
               OpName %16 "z"
               OpDecorate %8 RelaxedPrecision
               OpDecorate %12 RelaxedPrecision
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %7 = OpTypePointer Function %6
          %9 = OpConstant %6 1
         %10 = OpTypeInt 32 0
         %11 = OpTypePointer Function %10
         %13 = OpConstant %10 2
         %14 = OpTypeFloat 32
         %15 = OpTypePointer Function %14
         %17 = OpConstant %14 3
          %4 = OpFunction %2 None %3
          %5 = OpLabel
          %8 = OpVariable %7 Function
         %12 = OpVariable %11 Function
         %16 = OpVariable %15 Function
               OpStore %8 %9
               OpStore %12 %13
               OpStore %16 %17
               OpReturn
               OpFunctionEnd
  )";

  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context = BuildModule(env, consumer, shader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;

  const float float_values[2] = {3.0, 30.0};
  uint32_t uint_for_float[2];
  memcpy(uint_for_float, float_values, sizeof(float_values));

  auto add_signed_int_1 =
      transformation::MakeTransformationAddConstantScalar(100, 6, {1});
  auto add_signed_int_10 =
      transformation::MakeTransformationAddConstantScalar(101, 6, {10});
  auto add_unsigned_int_2 =
      transformation::MakeTransformationAddConstantScalar(102, 10, {2});
  auto add_unsigned_int_20 =
      transformation::MakeTransformationAddConstantScalar(103, 10, {20});
  auto add_float_3 = transformation::MakeTransformationAddConstantScalar(
      104, 14, {uint_for_float[0]});
  auto add_float_30 = transformation::MakeTransformationAddConstantScalar(
      105, 14, {uint_for_float[1]});
  auto bad_add_float_30_id_already_used =
      transformation::MakeTransformationAddConstantScalar(104, 14,
                                                          {uint_for_float[1]});
  auto bad_id_already_used =
      transformation::MakeTransformationAddConstantScalar(1, 6, {1});
  auto bad_no_data =
      transformation::MakeTransformationAddConstantScalar(100, 6, {});
  auto bad_too_much_data =
      transformation::MakeTransformationAddConstantScalar(100, 6, {1, 2});
  auto bad_type_id_does_not_exist =
      transformation::MakeTransformationAddConstantScalar(108, 2020,
                                                          {uint_for_float[0]});
  auto bad_type_id_is_not_a_type =
      transformation::MakeTransformationAddConstantScalar(109, 9, {0});
  auto bad_type_id_is_void =
      transformation::MakeTransformationAddConstantScalar(110, 2, {0});
  auto bad_type_id_is_pointer =
      transformation::MakeTransformationAddConstantScalar(111, 11, {0});

  // Id is already in use.
  ASSERT_FALSE(transformation::IsApplicable(bad_id_already_used, context.get(),
                                            fact_manager));

  // At least one word of data must be provided.
  ASSERT_FALSE(
      transformation::IsApplicable(bad_no_data, context.get(), fact_manager));

  // Cannot give two data words for a 32-bit type.
  ASSERT_FALSE(transformation::IsApplicable(bad_too_much_data, context.get(),
                                            fact_manager));

  // Type id does not exist
  ASSERT_FALSE(transformation::IsApplicable(bad_type_id_does_not_exist,
                                            context.get(), fact_manager));

  // Type id is not a type
  ASSERT_FALSE(transformation::IsApplicable(bad_type_id_is_not_a_type,
                                            context.get(), fact_manager));

  // Type id is void
  ASSERT_FALSE(transformation::IsApplicable(bad_type_id_is_void, context.get(),
                                            fact_manager));

  // Type id is pointer
  ASSERT_FALSE(transformation::IsApplicable(bad_type_id_is_pointer,
                                            context.get(), fact_manager));

  ASSERT_TRUE(transformation::IsApplicable(add_signed_int_1, context.get(),
                                           fact_manager));
  transformation::Apply(add_signed_int_1, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(transformation::IsApplicable(add_signed_int_10, context.get(),
                                           fact_manager));
  transformation::Apply(add_signed_int_10, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(transformation::IsApplicable(add_unsigned_int_2, context.get(),
                                           fact_manager));
  transformation::Apply(add_unsigned_int_2, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(transformation::IsApplicable(add_unsigned_int_20, context.get(),
                                           fact_manager));
  transformation::Apply(add_unsigned_int_20, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(
      transformation::IsApplicable(add_float_3, context.get(), fact_manager));
  transformation::Apply(add_float_3, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_TRUE(
      transformation::IsApplicable(add_float_30, context.get(), fact_manager));
  transformation::Apply(add_float_30, context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  ASSERT_FALSE(transformation::IsApplicable(bad_add_float_30_id_already_used,
                                            context.get(), fact_manager));

  std::string after_transformation = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %8 "x"
               OpName %12 "y"
               OpName %16 "z"
               OpDecorate %8 RelaxedPrecision
               OpDecorate %12 RelaxedPrecision
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %7 = OpTypePointer Function %6
          %9 = OpConstant %6 1
         %10 = OpTypeInt 32 0
         %11 = OpTypePointer Function %10
         %13 = OpConstant %10 2
         %14 = OpTypeFloat 32
         %15 = OpTypePointer Function %14
         %17 = OpConstant %14 3
        %100 = OpConstant %6 1
        %101 = OpConstant %6 10
        %102 = OpConstant %10 2
        %103 = OpConstant %10 20
        %104 = OpConstant %14 3
        %105 = OpConstant %14 30
          %4 = OpFunction %2 None %3
          %5 = OpLabel
          %8 = OpVariable %7 Function
         %12 = OpVariable %11 Function
         %16 = OpVariable %15 Function
               OpStore %8 %9
               OpStore %12 %13
               OpStore %16 %17
               OpReturn
               OpFunctionEnd
  )";

  ASSERT_TRUE(IsEqual(env, after_transformation, context.get()));
}

}  // namespace
}  // namespace fuzz
}  // namespace spvtools

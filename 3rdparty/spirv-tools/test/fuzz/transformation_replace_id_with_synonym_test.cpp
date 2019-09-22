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
#include "source/fuzz/data_descriptor.h"
#include "source/fuzz/id_use_descriptor.h"
#include "test/fuzz/fuzz_test_util.h"

namespace spvtools {
namespace fuzz {
namespace {

// The following shader was obtained from this GLSL, which was then optimized
// with spirv-opt -O and manually edited to include some uses of OpCopyObject
// (to introduce id synonyms).
//
// #version 310 es
//
// precision highp int;
// precision highp float;
//
// layout(set = 0, binding = 0) uniform buf {
//   int a;
//   int b;
//   int c;
// };
//
// layout(location = 0) out vec4 color;
//
// void main() {
//   int x = a;
//   float f = 0.0;
//   while (x < b) {
//     switch(x % 4) {
//       case 0:
//         color[0] = f;
//         break;
//       case 1:
//         color[1] = f;
//         break;
//       case 2:
//         color[2] = f;
//         break;
//       case 3:
//         color[3] = f;
//         break;
//       default:
//         break;
//     }
//     if (x > c) {
//       x++;
//     } else {
//       x += 2;
//     }
//   }
//   color[0] += color[1] + float(x);
// }
const std::string kComplexShader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main" %42
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %9 "buf"
               OpMemberName %9 0 "a"
               OpMemberName %9 1 "b"
               OpMemberName %9 2 "c"
               OpName %11 ""
               OpName %42 "color"
               OpMemberDecorate %9 0 Offset 0
               OpMemberDecorate %9 1 Offset 4
               OpMemberDecorate %9 2 Offset 8
               OpDecorate %9 Block
               OpDecorate %11 DescriptorSet 0
               OpDecorate %11 Binding 0
               OpDecorate %42 Location 0
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %9 = OpTypeStruct %6 %6 %6
         %10 = OpTypePointer Uniform %9
         %11 = OpVariable %10 Uniform
         %12 = OpConstant %6 0
         %13 = OpTypePointer Uniform %6
         %16 = OpTypeFloat 32
         %19 = OpConstant %16 0
         %26 = OpConstant %6 1
         %29 = OpTypeBool
         %32 = OpConstant %6 4
         %40 = OpTypeVector %16 4
         %41 = OpTypePointer Output %40
         %42 = OpVariable %41 Output
         %44 = OpTypeInt 32 0
         %45 = OpConstant %44 0
         %46 = OpTypePointer Output %16
         %50 = OpConstant %44 1
         %54 = OpConstant %44 2
         %58 = OpConstant %44 3
         %64 = OpConstant %6 2
          %4 = OpFunction %2 None %3
          %5 = OpLabel
        %209 = OpCopyObject %6 %12
         %14 = OpAccessChain %13 %11 %12
         %15 = OpLoad %6 %14
        %200 = OpCopyObject %6 %15
               OpBranch %20
         %20 = OpLabel
         %84 = OpPhi %6 %15 %5 %86 %69
         %27 = OpAccessChain %13 %11 %26
         %28 = OpLoad %6 %27
        %207 = OpCopyObject %6 %84
        %201 = OpCopyObject %6 %15
         %30 = OpSLessThan %29 %84 %28
               OpLoopMerge %22 %69 None
               OpBranchConditional %30 %21 %22
         %21 = OpLabel
         %33 = OpSMod %6 %84 %32
        %208 = OpCopyObject %6 %33
               OpSelectionMerge %39 None
               OpSwitch %33 %38 0 %34 1 %35 2 %36 3 %37
         %38 = OpLabel
        %202 = OpCopyObject %6 %15
               OpBranch %39
         %34 = OpLabel
        %210 = OpCopyObject %16 %19
         %47 = OpAccessChain %46 %42 %45
               OpStore %47 %19
               OpBranch %39
         %35 = OpLabel
         %51 = OpAccessChain %46 %42 %50
               OpStore %51 %19
               OpBranch %39
         %36 = OpLabel
        %204 = OpCopyObject %44 %54
         %55 = OpAccessChain %46 %42 %54
        %203 = OpCopyObject %46 %55
               OpStore %55 %19
               OpBranch %39
         %37 = OpLabel
         %59 = OpAccessChain %46 %42 %58
               OpStore %59 %19
               OpBranch %39
         %39 = OpLabel
        %300 = OpIAdd %6 %15 %15
         %65 = OpAccessChain %13 %11 %64
         %66 = OpLoad %6 %65
         %67 = OpSGreaterThan %29 %84 %66
               OpSelectionMerge %69 None
               OpBranchConditional %67 %68 %72
         %68 = OpLabel
         %71 = OpIAdd %6 %84 %26
               OpBranch %69
         %72 = OpLabel
         %74 = OpIAdd %6 %84 %64
        %205 = OpCopyObject %6 %74
               OpBranch %69
         %69 = OpLabel
         %86 = OpPhi %6 %71 %68 %74 %72
        %301 = OpPhi %6 %71 %68 %15 %72
               OpBranch %20
         %22 = OpLabel
         %75 = OpAccessChain %46 %42 %50
         %76 = OpLoad %16 %75
         %78 = OpConvertSToF %16 %84
         %80 = OpAccessChain %46 %42 %45
        %206 = OpCopyObject %16 %78
         %81 = OpLoad %16 %80
         %79 = OpFAdd %16 %76 %78
         %82 = OpFAdd %16 %81 %79
               OpStore %80 %82
               OpReturn
               OpFunctionEnd
)";

protobufs::Fact MakeFact(uint32_t id, uint32_t copy_id) {
  protobufs::FactIdSynonym id_synonym_fact;
  id_synonym_fact.set_id(id);
  id_synonym_fact.mutable_data_descriptor()->set_object(copy_id);
  protobufs::Fact result;
  *result.mutable_id_synonym_fact() = id_synonym_fact;
  return result;
}

// Equips the fact manager with synonym facts for the above shader.
void SetUpIdSynonyms(FactManager* fact_manager, opt::IRContext* context) {
  fact_manager->AddFact(MakeFact(15, 200), context);
  fact_manager->AddFact(MakeFact(15, 201), context);
  fact_manager->AddFact(MakeFact(15, 202), context);
  fact_manager->AddFact(MakeFact(55, 203), context);
  fact_manager->AddFact(MakeFact(54, 204), context);
  fact_manager->AddFact(MakeFact(74, 205), context);
  fact_manager->AddFact(MakeFact(78, 206), context);
  fact_manager->AddFact(MakeFact(84, 207), context);
  fact_manager->AddFact(MakeFact(33, 208), context);
  fact_manager->AddFact(MakeFact(12, 209), context);
  fact_manager->AddFact(MakeFact(19, 210), context);
}

TEST(TransformationReplaceIdWithSynonymTest, IllegalTransformations) {
  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context =
      BuildModule(env, consumer, kComplexShader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;
  SetUpIdSynonyms(&fact_manager, context.get());

  // %202 cannot replace %15 as in-operand 0 of %300, since %202 does not
  // dominate %300.
  auto synonym_does_not_dominate_use = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(15, SpvOpIAdd, 0, 300, 0),
      MakeDataDescriptor(202, {}), 0);
  ASSERT_FALSE(
      synonym_does_not_dominate_use.IsApplicable(context.get(), fact_manager));

  // %202 cannot replace %15 as in-operand 2 of %301, since this is the OpPhi's
  // incoming value for block %72, and %202 does not dominate %72.
  auto synonym_does_not_dominate_use_op_phi =
      TransformationReplaceIdWithSynonym(
          transformation::MakeIdUseDescriptor(15, SpvOpPhi, 2, 301, 0),
          MakeDataDescriptor(202, {}), 0);
  ASSERT_FALSE(synonym_does_not_dominate_use_op_phi.IsApplicable(context.get(),
                                                                 fact_manager));

  // %200 is not a synonym for %84
  auto id_in_use_is_not_synonymous = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(84, SpvOpSGreaterThan, 0, 67, 0),
      MakeDataDescriptor(200, {}), 0);
  ASSERT_FALSE(
      id_in_use_is_not_synonymous.IsApplicable(context.get(), fact_manager));

  // %86 is not a synonym for anything (and in particular not for %74)
  auto id_has_no_synonyms = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(86, SpvOpPhi, 2, 84, 0),
      MakeDataDescriptor(74, {}), 0);
  ASSERT_FALSE(id_has_no_synonyms.IsApplicable(context.get(), fact_manager));

  // This would lead to %207 = 'OpCopyObject %type %207' if it were allowed
  auto synonym_use_is_in_synonym_definition =
      TransformationReplaceIdWithSynonym(
          transformation::MakeIdUseDescriptor(84, SpvOpCopyObject, 0, 207, 0),
          MakeDataDescriptor(207, {}), 0);
  ASSERT_FALSE(synonym_use_is_in_synonym_definition.IsApplicable(context.get(),
                                                                 fact_manager));

  // The id use descriptor does not lead to a use (%84 is not used in the
  // definition of %207)
  auto bad_id_use_descriptor = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(84, SpvOpCopyObject, 0, 200, 0),
      MakeDataDescriptor(207, {}), 0);
  ASSERT_FALSE(bad_id_use_descriptor.IsApplicable(context.get(), fact_manager));

  // This replacement would lead to an access chain into a struct using a
  // non-constant index.
  auto bad_access_chain = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(12, SpvOpAccessChain, 1, 14, 0),
      MakeDataDescriptor(209, {}), 0);
  ASSERT_FALSE(bad_access_chain.IsApplicable(context.get(), fact_manager));
}

TEST(TransformationReplaceIdWithSynonymTest, LegalTransformations) {
  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context =
      BuildModule(env, consumer, kComplexShader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;
  SetUpIdSynonyms(&fact_manager, context.get());

  auto global_constant_synonym = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(19, SpvOpStore, 1, 47, 0),
      MakeDataDescriptor(210, {}), 0);
  ASSERT_TRUE(
      global_constant_synonym.IsApplicable(context.get(), fact_manager));
  global_constant_synonym.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  auto replace_vector_access_chain_index = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(54, SpvOpAccessChain, 1, 55, 0),
      MakeDataDescriptor(204, {}), 0);
  ASSERT_TRUE(replace_vector_access_chain_index.IsApplicable(context.get(),
                                                             fact_manager));
  replace_vector_access_chain_index.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // This is an interesting case because it replaces something that is being
  // copied with something that is already a synonym.
  auto regular_replacement = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(15, SpvOpCopyObject, 0, 202, 0),
      MakeDataDescriptor(201, {}), 0);
  ASSERT_TRUE(regular_replacement.IsApplicable(context.get(), fact_manager));
  regular_replacement.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  auto regular_replacement2 = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(55, SpvOpStore, 0, 203, 0),
      MakeDataDescriptor(203, {}), 0);
  ASSERT_TRUE(regular_replacement2.IsApplicable(context.get(), fact_manager));
  regular_replacement2.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  auto good_op_phi = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(74, SpvOpPhi, 2, 86, 0),
      MakeDataDescriptor(205, {}), 0);
  ASSERT_TRUE(good_op_phi.IsApplicable(context.get(), fact_manager));
  good_op_phi.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  const std::string after_transformation = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main" %42
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %9 "buf"
               OpMemberName %9 0 "a"
               OpMemberName %9 1 "b"
               OpMemberName %9 2 "c"
               OpName %11 ""
               OpName %42 "color"
               OpMemberDecorate %9 0 Offset 0
               OpMemberDecorate %9 1 Offset 4
               OpMemberDecorate %9 2 Offset 8
               OpDecorate %9 Block
               OpDecorate %11 DescriptorSet 0
               OpDecorate %11 Binding 0
               OpDecorate %42 Location 0
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %9 = OpTypeStruct %6 %6 %6
         %10 = OpTypePointer Uniform %9
         %11 = OpVariable %10 Uniform
         %12 = OpConstant %6 0
         %13 = OpTypePointer Uniform %6
         %16 = OpTypeFloat 32
         %19 = OpConstant %16 0
         %26 = OpConstant %6 1
         %29 = OpTypeBool
         %32 = OpConstant %6 4
         %40 = OpTypeVector %16 4
         %41 = OpTypePointer Output %40
         %42 = OpVariable %41 Output
         %44 = OpTypeInt 32 0
         %45 = OpConstant %44 0
         %46 = OpTypePointer Output %16
         %50 = OpConstant %44 1
         %54 = OpConstant %44 2
         %58 = OpConstant %44 3
         %64 = OpConstant %6 2
          %4 = OpFunction %2 None %3
          %5 = OpLabel
        %209 = OpCopyObject %6 %12
         %14 = OpAccessChain %13 %11 %12
         %15 = OpLoad %6 %14
        %200 = OpCopyObject %6 %15
               OpBranch %20
         %20 = OpLabel
         %84 = OpPhi %6 %15 %5 %86 %69
         %27 = OpAccessChain %13 %11 %26
         %28 = OpLoad %6 %27
        %207 = OpCopyObject %6 %84
        %201 = OpCopyObject %6 %15
         %30 = OpSLessThan %29 %84 %28
               OpLoopMerge %22 %69 None
               OpBranchConditional %30 %21 %22
         %21 = OpLabel
         %33 = OpSMod %6 %84 %32
        %208 = OpCopyObject %6 %33
               OpSelectionMerge %39 None
               OpSwitch %33 %38 0 %34 1 %35 2 %36 3 %37
         %38 = OpLabel
        %202 = OpCopyObject %6 %201
               OpBranch %39
         %34 = OpLabel
        %210 = OpCopyObject %16 %19
         %47 = OpAccessChain %46 %42 %45
               OpStore %47 %210
               OpBranch %39
         %35 = OpLabel
         %51 = OpAccessChain %46 %42 %50
               OpStore %51 %19
               OpBranch %39
         %36 = OpLabel
        %204 = OpCopyObject %44 %54
         %55 = OpAccessChain %46 %42 %204
        %203 = OpCopyObject %46 %55
               OpStore %203 %19
               OpBranch %39
         %37 = OpLabel
         %59 = OpAccessChain %46 %42 %58
               OpStore %59 %19
               OpBranch %39
         %39 = OpLabel
        %300 = OpIAdd %6 %15 %15
         %65 = OpAccessChain %13 %11 %64
         %66 = OpLoad %6 %65
         %67 = OpSGreaterThan %29 %84 %66
               OpSelectionMerge %69 None
               OpBranchConditional %67 %68 %72
         %68 = OpLabel
         %71 = OpIAdd %6 %84 %26
               OpBranch %69
         %72 = OpLabel
         %74 = OpIAdd %6 %84 %64
        %205 = OpCopyObject %6 %74
               OpBranch %69
         %69 = OpLabel
         %86 = OpPhi %6 %71 %68 %205 %72
        %301 = OpPhi %6 %71 %68 %15 %72
               OpBranch %20
         %22 = OpLabel
         %75 = OpAccessChain %46 %42 %50
         %76 = OpLoad %16 %75
         %78 = OpConvertSToF %16 %84
         %80 = OpAccessChain %46 %42 %45
        %206 = OpCopyObject %16 %78
         %81 = OpLoad %16 %80
         %79 = OpFAdd %16 %76 %78
         %82 = OpFAdd %16 %81 %79
               OpStore %80 %82
               OpReturn
               OpFunctionEnd
  )";

  ASSERT_TRUE(IsEqual(env, after_transformation, context.get()));
}

TEST(TransformationReplaceIdWithSynonymTest, SynonymsOfVariables) {
  // The following SPIR-V comes from this GLSL, with object copies added:
  //
  // #version 310 es
  //
  // precision highp int;
  //
  // int g;
  //
  // void main() {
  //   int l;
  //   l = g;
  //   g = l;
  // }
  const std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %8 "l"
               OpName %10 "g"
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %7 = OpTypePointer Function %6
          %9 = OpTypePointer Private %6
         %10 = OpVariable %9 Private
          %4 = OpFunction %2 None %3
          %5 = OpLabel
          %8 = OpVariable %7 Function
        %100 = OpCopyObject %9 %10
        %101 = OpCopyObject %7 %8
         %11 = OpLoad %6 %10
               OpStore %8 %11
         %12 = OpLoad %6 %8
               OpStore %10 %12
               OpReturn
               OpFunctionEnd
  )";

  const auto env = SPV_ENV_UNIVERSAL_1_3;
  const auto consumer = nullptr;
  const auto context = BuildModule(env, consumer, shader, kFuzzAssembleOption);
  ASSERT_TRUE(IsValid(env, context.get()));

  FactManager fact_manager;

  fact_manager.AddFact(MakeFact(10, 100), context.get());
  fact_manager.AddFact(MakeFact(8, 101), context.get());

  // Replace %10 with %100 in:
  // %11 = OpLoad %6 %10
  auto replacement1 = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(10, SpvOpLoad, 0, 11, 0),
      MakeDataDescriptor(100, {}), 0);
  ASSERT_TRUE(replacement1.IsApplicable(context.get(), fact_manager));
  replacement1.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // Replace %8 with %101 in:
  // OpStore %8 %11
  auto replacement2 = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(8, SpvOpStore, 0, 11, 0),
      MakeDataDescriptor(101, {}), 0);
  ASSERT_TRUE(replacement2.IsApplicable(context.get(), fact_manager));
  replacement2.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // Replace %8 with %101 in:
  // %12 = OpLoad %6 %8
  auto replacement3 = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(8, SpvOpLoad, 0, 12, 0),
      MakeDataDescriptor(101, {}), 0);
  ASSERT_TRUE(replacement3.IsApplicable(context.get(), fact_manager));
  replacement3.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  // Replace %10 with %100 in:
  // OpStore %10 %12
  auto replacement4 = TransformationReplaceIdWithSynonym(
      transformation::MakeIdUseDescriptor(10, SpvOpStore, 0, 12, 0),
      MakeDataDescriptor(100, {}), 0);
  ASSERT_TRUE(replacement4.IsApplicable(context.get(), fact_manager));
  replacement4.Apply(context.get(), &fact_manager);
  ASSERT_TRUE(IsValid(env, context.get()));

  const std::string after_transformation = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %8 "l"
               OpName %10 "g"
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeInt 32 1
          %7 = OpTypePointer Function %6
          %9 = OpTypePointer Private %6
         %10 = OpVariable %9 Private
          %4 = OpFunction %2 None %3
          %5 = OpLabel
          %8 = OpVariable %7 Function
        %100 = OpCopyObject %9 %10
        %101 = OpCopyObject %7 %8
         %11 = OpLoad %6 %100
               OpStore %101 %11
         %12 = OpLoad %6 %101
               OpStore %100 %12
               OpReturn
               OpFunctionEnd
  )";

  ASSERT_TRUE(IsEqual(env, after_transformation, context.get()));
}

}  // namespace
}  // namespace fuzz
}  // namespace spvtools

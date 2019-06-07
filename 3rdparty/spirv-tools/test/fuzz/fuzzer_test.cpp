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

#include "source/fuzz/fuzzer.h"
#include "test/fuzz/fuzz_test_util.h"

namespace spvtools {
namespace fuzz {
namespace {

// Assembles the given |shader| text, and then runs the fuzzer |num_runs|
// times, using successive seeds starting from |initial_seed|.  Checks that
// the binary produced after each fuzzer run is valid.
void RunFuzzer(const std::string& shader, uint32_t initial_seed,
               uint32_t num_runs) {
  const auto env = SPV_ENV_UNIVERSAL_1_3;

  std::vector<uint32_t> binary_in;
  SpirvTools t(env);
  ASSERT_TRUE(t.Assemble(shader, &binary_in, kFuzzAssembleOption));
  ASSERT_TRUE(t.Validate(binary_in));

  for (uint32_t seed = initial_seed; seed < initial_seed + num_runs; seed++) {
    protobufs::FactSequence initial_facts;
    std::vector<uint32_t> binary_out;
    protobufs::TransformationSequence transformation_sequence_out;
    spvtools::FuzzerOptions fuzzer_options;
    spvFuzzerOptionsSetRandomSeed(fuzzer_options, seed);

    Fuzzer fuzzer(env);
    fuzzer.Run(binary_in, initial_facts, &binary_out,
               &transformation_sequence_out, fuzzer_options);
    ASSERT_TRUE(t.Validate(binary_out));
  }
}

TEST(FuzzerTest, Miscellaneous1) {
  // The SPIR-V came from this GLSL:
  //
  // #version 310 es
  //
  // void foo() {
  //   int x;
  //   x = 2;
  //   for (int i = 0; i < 100; i++) {
  //     x += i;
  //     x = x * 2;
  //   }
  //   return;
  // }
  //
  // void main() {
  //   foo();
  //   for (int i = 0; i < 10; i++) {
  //     int j = 20;
  //     while(j > 0) {
  //       foo();
  //       j--;
  //     }
  //     do {
  //       i++;
  //     } while(i < 4);
  //   }
  // }

  std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main"
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %6 "foo("
               OpName %10 "x"
               OpName %12 "i"
               OpName %33 "i"
               OpName %42 "j"
               OpDecorate %10 RelaxedPrecision
               OpDecorate %12 RelaxedPrecision
               OpDecorate %19 RelaxedPrecision
               OpDecorate %23 RelaxedPrecision
               OpDecorate %24 RelaxedPrecision
               OpDecorate %25 RelaxedPrecision
               OpDecorate %26 RelaxedPrecision
               OpDecorate %27 RelaxedPrecision
               OpDecorate %28 RelaxedPrecision
               OpDecorate %30 RelaxedPrecision
               OpDecorate %33 RelaxedPrecision
               OpDecorate %39 RelaxedPrecision
               OpDecorate %42 RelaxedPrecision
               OpDecorate %49 RelaxedPrecision
               OpDecorate %52 RelaxedPrecision
               OpDecorate %53 RelaxedPrecision
               OpDecorate %58 RelaxedPrecision
               OpDecorate %59 RelaxedPrecision
               OpDecorate %60 RelaxedPrecision
               OpDecorate %63 RelaxedPrecision
               OpDecorate %64 RelaxedPrecision
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %8 = OpTypeInt 32 1
          %9 = OpTypePointer Function %8
         %11 = OpConstant %8 2
         %13 = OpConstant %8 0
         %20 = OpConstant %8 100
         %21 = OpTypeBool
         %29 = OpConstant %8 1
         %40 = OpConstant %8 10
         %43 = OpConstant %8 20
         %61 = OpConstant %8 4
          %4 = OpFunction %2 None %3
          %5 = OpLabel
         %33 = OpVariable %9 Function
         %42 = OpVariable %9 Function
         %32 = OpFunctionCall %2 %6
               OpStore %33 %13
               OpBranch %34
         %34 = OpLabel
               OpLoopMerge %36 %37 None
               OpBranch %38
         %38 = OpLabel
         %39 = OpLoad %8 %33
         %41 = OpSLessThan %21 %39 %40
               OpBranchConditional %41 %35 %36
         %35 = OpLabel
               OpStore %42 %43
               OpBranch %44
         %44 = OpLabel
               OpLoopMerge %46 %47 None
               OpBranch %48
         %48 = OpLabel
         %49 = OpLoad %8 %42
         %50 = OpSGreaterThan %21 %49 %13
               OpBranchConditional %50 %45 %46
         %45 = OpLabel
         %51 = OpFunctionCall %2 %6
         %52 = OpLoad %8 %42
         %53 = OpISub %8 %52 %29
               OpStore %42 %53
               OpBranch %47
         %47 = OpLabel
               OpBranch %44
         %46 = OpLabel
               OpBranch %54
         %54 = OpLabel
               OpLoopMerge %56 %57 None
               OpBranch %55
         %55 = OpLabel
         %58 = OpLoad %8 %33
         %59 = OpIAdd %8 %58 %29
               OpStore %33 %59
               OpBranch %57
         %57 = OpLabel
         %60 = OpLoad %8 %33
         %62 = OpSLessThan %21 %60 %61
               OpBranchConditional %62 %54 %56
         %56 = OpLabel
               OpBranch %37
         %37 = OpLabel
         %63 = OpLoad %8 %33
         %64 = OpIAdd %8 %63 %29
               OpStore %33 %64
               OpBranch %34
         %36 = OpLabel
               OpReturn
               OpFunctionEnd
          %6 = OpFunction %2 None %3
          %7 = OpLabel
         %10 = OpVariable %9 Function
         %12 = OpVariable %9 Function
               OpStore %10 %11
               OpStore %12 %13
               OpBranch %14
         %14 = OpLabel
               OpLoopMerge %16 %17 None
               OpBranch %18
         %18 = OpLabel
         %19 = OpLoad %8 %12
         %22 = OpSLessThan %21 %19 %20
               OpBranchConditional %22 %15 %16
         %15 = OpLabel
         %23 = OpLoad %8 %12
         %24 = OpLoad %8 %10
         %25 = OpIAdd %8 %24 %23
               OpStore %10 %25
         %26 = OpLoad %8 %10
         %27 = OpIMul %8 %26 %11
               OpStore %10 %27
               OpBranch %17
         %17 = OpLabel
         %28 = OpLoad %8 %12
         %30 = OpIAdd %8 %28 %29
               OpStore %12 %30
               OpBranch %14
         %16 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  // Do 10 fuzzer runs, starting from an initial seed of 0 (seed value chosen
  // arbitrarily).
  RunFuzzer(shader, 0, 10);
}

TEST(FuzzerTest, Miscellaneous2) {
  // The SPIR-V came from this GLSL, which was then optimized using spirv-opt
  // with the -O argument:
  //
  // #version 310 es
  //
  // precision highp float;
  //
  // layout(location = 0) out vec4 _GLF_color;
  //
  // layout(set = 0, binding = 0) uniform buf0 {
  //  vec2 injectionSwitch;
  // };
  // layout(set = 0, binding = 1) uniform buf1 {
  //  vec2 resolution;
  // };
  // bool checkSwap(float a, float b)
  // {
  //  return gl_FragCoord.y < resolution.y / 2.0 ? a > b : a < b;
  // }
  // void main()
  // {
  //  float data[10];
  //  for(int i = 0; i < 10; i++)
  //   {
  //    data[i] = float(10 - i) * injectionSwitch.y;
  //   }
  //  for(int i = 0; i < 9; i++)
  //   {
  //    for(int j = 0; j < 10; j++)
  //     {
  //      if(j < i + 1)
  //       {
  //        continue;
  //       }
  //      bool doSwap = checkSwap(data[i], data[j]);
  //      if(doSwap)
  //       {
  //        float temp = data[i];
  //        data[i] = data[j];
  //        data[j] = temp;
  //       }
  //     }
  //   }
  //  if(gl_FragCoord.x < resolution.x / 2.0)
  //   {
  //    _GLF_color = vec4(data[0] / 10.0, data[5] / 10.0, data[9] / 10.0, 1.0);
  //   }
  //  else
  //   {
  //    _GLF_color = vec4(data[5] / 10.0, data[9] / 10.0, data[0] / 10.0, 1.0);
  //   }
  // }

  std::string shader = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main" %16 %139
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %16 "gl_FragCoord"
               OpName %23 "buf1"
               OpMemberName %23 0 "resolution"
               OpName %25 ""
               OpName %61 "data"
               OpName %66 "buf0"
               OpMemberName %66 0 "injectionSwitch"
               OpName %68 ""
               OpName %139 "_GLF_color"
               OpDecorate %16 BuiltIn FragCoord
               OpMemberDecorate %23 0 Offset 0
               OpDecorate %23 Block
               OpDecorate %25 DescriptorSet 0
               OpDecorate %25 Binding 1
               OpDecorate %64 RelaxedPrecision
               OpMemberDecorate %66 0 Offset 0
               OpDecorate %66 Block
               OpDecorate %68 DescriptorSet 0
               OpDecorate %68 Binding 0
               OpDecorate %75 RelaxedPrecision
               OpDecorate %95 RelaxedPrecision
               OpDecorate %126 RelaxedPrecision
               OpDecorate %128 RelaxedPrecision
               OpDecorate %139 Location 0
               OpDecorate %182 RelaxedPrecision
               OpDecorate %183 RelaxedPrecision
               OpDecorate %184 RelaxedPrecision
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeFloat 32
          %7 = OpTypePointer Function %6
          %8 = OpTypeBool
         %14 = OpTypeVector %6 4
         %15 = OpTypePointer Input %14
         %16 = OpVariable %15 Input
         %17 = OpTypeInt 32 0
         %18 = OpConstant %17 1
         %19 = OpTypePointer Input %6
         %22 = OpTypeVector %6 2
         %23 = OpTypeStruct %22
         %24 = OpTypePointer Uniform %23
         %25 = OpVariable %24 Uniform
         %26 = OpTypeInt 32 1
         %27 = OpConstant %26 0
         %28 = OpTypePointer Uniform %6
         %56 = OpConstant %26 10
         %58 = OpConstant %17 10
         %59 = OpTypeArray %6 %58
         %60 = OpTypePointer Function %59
         %66 = OpTypeStruct %22
         %67 = OpTypePointer Uniform %66
         %68 = OpVariable %67 Uniform
         %74 = OpConstant %26 1
         %83 = OpConstant %26 9
        %129 = OpConstant %17 0
        %138 = OpTypePointer Output %14
        %139 = OpVariable %138 Output
        %144 = OpConstant %26 5
        %151 = OpConstant %6 1
        %194 = OpConstant %6 0.5
        %195 = OpConstant %6 0.100000001
          %4 = OpFunction %2 None %3
          %5 = OpLabel
         %61 = OpVariable %60 Function
               OpBranch %50
         %50 = OpLabel
        %182 = OpPhi %26 %27 %5 %75 %51
         %57 = OpSLessThan %8 %182 %56
               OpLoopMerge %52 %51 None
               OpBranchConditional %57 %51 %52
         %51 = OpLabel
         %64 = OpISub %26 %56 %182
         %65 = OpConvertSToF %6 %64
         %69 = OpAccessChain %28 %68 %27 %18
         %70 = OpLoad %6 %69
         %71 = OpFMul %6 %65 %70
         %72 = OpAccessChain %7 %61 %182
               OpStore %72 %71
         %75 = OpIAdd %26 %182 %74
               OpBranch %50
         %52 = OpLabel
               OpBranch %77
         %77 = OpLabel
        %183 = OpPhi %26 %27 %52 %128 %88
         %84 = OpSLessThan %8 %183 %83
               OpLoopMerge %79 %88 None
               OpBranchConditional %84 %78 %79
         %78 = OpLabel
               OpBranch %86
         %86 = OpLabel
        %184 = OpPhi %26 %27 %78 %126 %89
         %92 = OpSLessThan %8 %184 %56
               OpLoopMerge %88 %89 None
               OpBranchConditional %92 %87 %88
         %87 = OpLabel
         %95 = OpIAdd %26 %183 %74
         %96 = OpSLessThan %8 %184 %95
               OpSelectionMerge %98 None
               OpBranchConditional %96 %97 %98
         %97 = OpLabel
               OpBranch %89
         %98 = OpLabel
        %104 = OpAccessChain %7 %61 %183
        %105 = OpLoad %6 %104
        %107 = OpAccessChain %7 %61 %184
        %108 = OpLoad %6 %107
        %166 = OpAccessChain %19 %16 %18
        %167 = OpLoad %6 %166
        %168 = OpAccessChain %28 %25 %27 %18
        %169 = OpLoad %6 %168
        %170 = OpFMul %6 %169 %194
        %171 = OpFOrdLessThan %8 %167 %170
               OpSelectionMerge %172 None
               OpBranchConditional %171 %173 %174
        %173 = OpLabel
        %177 = OpFOrdGreaterThan %8 %105 %108
               OpBranch %172
        %174 = OpLabel
        %180 = OpFOrdLessThan %8 %105 %108
               OpBranch %172
        %172 = OpLabel
        %186 = OpPhi %8 %177 %173 %180 %174
               OpSelectionMerge %112 None
               OpBranchConditional %186 %111 %112
        %111 = OpLabel
        %116 = OpLoad %6 %104
        %120 = OpLoad %6 %107
               OpStore %104 %120
               OpStore %107 %116
               OpBranch %112
        %112 = OpLabel
               OpBranch %89
         %89 = OpLabel
        %126 = OpIAdd %26 %184 %74
               OpBranch %86
         %88 = OpLabel
        %128 = OpIAdd %26 %183 %74
               OpBranch %77
         %79 = OpLabel
        %130 = OpAccessChain %19 %16 %129
        %131 = OpLoad %6 %130
        %132 = OpAccessChain %28 %25 %27 %129
        %133 = OpLoad %6 %132
        %134 = OpFMul %6 %133 %194
        %135 = OpFOrdLessThan %8 %131 %134
               OpSelectionMerge %137 None
               OpBranchConditional %135 %136 %153
        %136 = OpLabel
        %140 = OpAccessChain %7 %61 %27
        %141 = OpLoad %6 %140
        %143 = OpFMul %6 %141 %195
        %145 = OpAccessChain %7 %61 %144
        %146 = OpLoad %6 %145
        %147 = OpFMul %6 %146 %195
        %148 = OpAccessChain %7 %61 %83
        %149 = OpLoad %6 %148
        %150 = OpFMul %6 %149 %195
        %152 = OpCompositeConstruct %14 %143 %147 %150 %151
               OpStore %139 %152
               OpBranch %137
        %153 = OpLabel
        %154 = OpAccessChain %7 %61 %144
        %155 = OpLoad %6 %154
        %156 = OpFMul %6 %155 %195
        %157 = OpAccessChain %7 %61 %83
        %158 = OpLoad %6 %157
        %159 = OpFMul %6 %158 %195
        %160 = OpAccessChain %7 %61 %27
        %161 = OpLoad %6 %160
        %162 = OpFMul %6 %161 %195
        %163 = OpCompositeConstruct %14 %156 %159 %162 %151
               OpStore %139 %163
               OpBranch %137
        %137 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  // Do 10 fuzzer runs, starting from an initial seed of 10 (seed value chosen
  // arbitrarily).
  RunFuzzer(shader, 10, 10);
}

}  // namespace
}  // namespace fuzz
}  // namespace spvtools

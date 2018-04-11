// Copyright (c) 2018 Google LLC
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

#include "assembly_builder.h"
#include "gmock/gmock.h"
#include "pass_fixture.h"
#include "pass_utils.h"

namespace {

using namespace spvtools;

using IfConversionTest = PassTest<::testing::Test>;

#ifdef SPIRV_EFFCEE
TEST_F(IfConversionTest, TestSimpleIfThenElse) {
  const std::string text = R"(
; CHECK: OpSelectionMerge [[merge:%\w+]]
; CHECK: [[merge]] = OpLabel
; CHECK-NOT: OpPhi
; CHECK: [[sel:%\w+]] = OpSelect %uint %true %uint_0 %uint_1
; CHECK OpStore {{%\w+}} [[sel]]
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%bool = OpTypeBool
%true = OpConstantTrue %bool
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%11 = OpTypeFunction %void
%1 = OpFunction %void None %11
%12 = OpLabel
OpSelectionMerge %14 None
OpBranchConditional %true %15 %16
%15 = OpLabel
OpBranch %14
%16 = OpLabel
OpBranch %14
%14 = OpLabel
%18 = OpPhi %uint %uint_0 %15 %uint_1 %16
OpStore %2 %18
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndMatch<opt::IfConversion>(text, true);
}

TEST_F(IfConversionTest, TestSimpleHalfIfTrue) {
  const std::string text = R"(
; CHECK: OpSelectionMerge [[merge:%\w+]]
; CHECK: [[merge]] = OpLabel
; CHECK-NOT: OpPhi
; CHECK: [[sel:%\w+]] = OpSelect %uint %true %uint_0 %uint_1
; CHECK OpStore {{%\w+}} [[sel]]
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%bool = OpTypeBool
%true = OpConstantTrue %bool
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%11 = OpTypeFunction %void
%1 = OpFunction %void None %11
%12 = OpLabel
OpSelectionMerge %14 None
OpBranchConditional %true %15 %14
%15 = OpLabel
OpBranch %14
%14 = OpLabel
%18 = OpPhi %uint %uint_0 %15 %uint_1 %12
OpStore %2 %18
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndMatch<opt::IfConversion>(text, true);
}

TEST_F(IfConversionTest, TestSimpleHalfIfExtraBlock) {
  const std::string text = R"(
; CHECK: OpSelectionMerge [[merge:%\w+]]
; CHECK: [[merge]] = OpLabel
; CHECK-NOT: OpPhi
; CHECK: [[sel:%\w+]] = OpSelect %uint %true %uint_0 %uint_1
; CHECK OpStore {{%\w+}} [[sel]]
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%bool = OpTypeBool
%true = OpConstantTrue %bool
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%11 = OpTypeFunction %void
%1 = OpFunction %void None %11
%12 = OpLabel
OpSelectionMerge %14 None
OpBranchConditional %true %15 %14
%15 = OpLabel
OpBranch %16
%16 = OpLabel
OpBranch %14
%14 = OpLabel
%18 = OpPhi %uint %uint_0 %15 %uint_1 %12
OpStore %2 %18
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndMatch<opt::IfConversion>(text, true);
}

TEST_F(IfConversionTest, TestSimpleHalfIfFalse) {
  const std::string text = R"(
; CHECK: OpSelectionMerge [[merge:%\w+]]
; CHECK: [[merge]] = OpLabel
; CHECK-NOT: OpPhi
; CHECK: [[sel:%\w+]] = OpSelect %uint %true %uint_0 %uint_1
; CHECK OpStore {{%\w+}} [[sel]]
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%bool = OpTypeBool
%true = OpConstantTrue %bool
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%11 = OpTypeFunction %void
%1 = OpFunction %void None %11
%12 = OpLabel
OpSelectionMerge %14 None
OpBranchConditional %true %14 %15
%15 = OpLabel
OpBranch %14
%14 = OpLabel
%18 = OpPhi %uint %uint_0 %12 %uint_1 %15
OpStore %2 %18
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndMatch<opt::IfConversion>(text, true);
}

TEST_F(IfConversionTest, TestVectorSplat) {
  const std::string text = R"(
; CHECK: [[bool_vec:%\w+]] = OpTypeVector %bool 2
; CHECK: OpSelectionMerge [[merge:%\w+]]
; CHECK: [[merge]] = OpLabel
; CHECK-NOT: OpPhi
; CHECK: [[comp:%\w+]] = OpCompositeConstruct [[bool_vec]] %true %true
; CHECK: [[sel:%\w+]] = OpSelect {{%\w+}} [[comp]]
; CHECK OpStore {{%\w+}} [[sel]]
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%bool = OpTypeBool
%true = OpConstantTrue %bool
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%uint_vec2 = OpTypeVector %uint 2
%vec2_01 = OpConstantComposite %uint_vec2 %uint_0 %uint_1
%vec2_10 = OpConstantComposite %uint_vec2 %uint_1 %uint_0
%_ptr_Output_uint = OpTypePointer Output %uint_vec2
%2 = OpVariable %_ptr_Output_uint Output
%11 = OpTypeFunction %void
%1 = OpFunction %void None %11
%12 = OpLabel
OpSelectionMerge %14 None
OpBranchConditional %true %15 %16
%15 = OpLabel
OpBranch %14
%16 = OpLabel
OpBranch %14
%14 = OpLabel
%18 = OpPhi %uint_vec2 %vec2_01 %15 %vec2_10 %16
OpStore %2 %18
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndMatch<opt::IfConversion>(text, true);
}
#endif  // SPIRV_EFFCEE

TEST_F(IfConversionTest, NoCommonDominator) {
  const std::string text = R"(OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%8 = OpTypeFunction %void
%1 = OpFunction %void None %8
%9 = OpLabel
OpBranch %10
%11 = OpLabel
OpBranch %10
%10 = OpLabel
%12 = OpPhi %uint %uint_0 %9 %uint_1 %11
OpStore %2 %12
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndCheck<opt::IfConversion>(text, text, true, true);
}

TEST_F(IfConversionTest, LoopUntouched) {
  const std::string text = R"(OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%8 = OpTypeFunction %void
%bool = OpTypeBool
%true = OpConstantTrue %bool
%1 = OpFunction %void None %8
%11 = OpLabel
OpBranch %12
%12 = OpLabel
%13 = OpPhi %uint %uint_0 %11 %uint_1 %12
OpLoopMerge %14 %12 None
OpBranchConditional %true %14 %12
%14 = OpLabel
OpStore %2 %13
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndCheck<opt::IfConversion>(text, text, true, true);
}

TEST_F(IfConversionTest, TooManyPredecessors) {
  const std::string text = R"(OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%8 = OpTypeFunction %void
%bool = OpTypeBool
%true = OpConstantTrue %bool
%1 = OpFunction %void None %8
%11 = OpLabel
OpSelectionMerge %12 None
OpBranchConditional %true %13 %12
%13 = OpLabel
OpBranchConditional %true %14 %15
%14 = OpLabel
OpBranch %12
%15 = OpLabel
OpBranch %12
%12 = OpLabel
%16 = OpPhi %uint %uint_0 %11 %uint_0 %14 %uint_1 %15
OpStore %2 %16
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndCheck<opt::IfConversion>(text, text, true, true);
}

TEST_F(IfConversionTest, NoCodeMotion) {
  const std::string text = R"(OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %1 "func" %2
%void = OpTypeVoid
%uint = OpTypeInt 32 0
%uint_0 = OpConstant %uint 0
%uint_1 = OpConstant %uint 1
%_ptr_Output_uint = OpTypePointer Output %uint
%2 = OpVariable %_ptr_Output_uint Output
%8 = OpTypeFunction %void
%bool = OpTypeBool
%true = OpConstantTrue %bool
%1 = OpFunction %void None %8
%11 = OpLabel
OpSelectionMerge %12 None
OpBranchConditional %true %13 %12
%13 = OpLabel
%14 = OpIAdd %uint %uint_0 %uint_1
OpBranch %12
%12 = OpLabel
%15 = OpPhi %uint %uint_0 %11 %14 %13
OpStore %2 %15
OpReturn
OpFunctionEnd
)";

  SinglePassRunAndCheck<opt::IfConversion>(text, text, true, true);
}

}  // anonymous namespace

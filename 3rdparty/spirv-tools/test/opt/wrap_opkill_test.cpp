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

#include "gmock/gmock.h"
#include "test/opt/assembly_builder.h"
#include "test/opt/pass_fixture.h"
#include "test/opt/pass_utils.h"

namespace spvtools {
namespace opt {
namespace {

using WrapOpKillTest = PassTest<::testing::Test>;

TEST_F(WrapOpKillTest, SingleOpKill) {
  const std::string text = R"(
; CHECK: OpEntryPoint Fragment [[main:%\w+]]
; CHECK: [[main]] = OpFunction
; CHECK: OpFunctionCall %void [[orig_kill:%\w+]]
; CHECK: [[orig_kill]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpFunctionCall %void [[new_kill:%\w+]]
; CHECK-NEXT: OpUnreachable
; CHECK: [[new_kill]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpKill
; CHECK-NEXT: OpFunctionEnd
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %main "main"
               OpExecutionMode %main OriginUpperLeft
               OpSource GLSL 330
               OpName %main "main"
       %void = OpTypeVoid
          %5 = OpTypeFunction %void
       %bool = OpTypeBool
       %true = OpConstantTrue %bool
       %main = OpFunction %void None %5
          %8 = OpLabel
               OpBranch %9
          %9 = OpLabel
               OpLoopMerge %10 %11 None
               OpBranch %12
         %12 = OpLabel
               OpBranchConditional %true %13 %10
         %13 = OpLabel
               OpBranch %11
         %11 = OpLabel
         %14 = OpFunctionCall %void %kill_
               OpBranch %9
         %10 = OpLabel
               OpReturn
               OpFunctionEnd
      %kill_ = OpFunction %void None %5
         %15 = OpLabel
               OpKill
               OpFunctionEnd
  )";

  SinglePassRunAndMatch<WrapOpKill>(text, true);
}

TEST_F(WrapOpKillTest, MultipleOpKillInSameFunc) {
  const std::string text = R"(
; CHECK: OpEntryPoint Fragment [[main:%\w+]]
; CHECK: [[main]] = OpFunction
; CHECK: OpFunctionCall %void [[orig_kill:%\w+]]
; CHECK: [[orig_kill]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpSelectionMerge
; CHECK-NEXT: OpBranchConditional
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpFunctionCall %void [[new_kill:%\w+]]
; CHECK-NEXT: OpUnreachable
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpFunctionCall %void [[new_kill]]
; CHECK-NEXT: OpUnreachable
; CHECK: [[new_kill]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpKill
; CHECK-NEXT: OpFunctionEnd
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %main "main"
               OpExecutionMode %main OriginUpperLeft
               OpSource GLSL 330
               OpName %main "main"
       %void = OpTypeVoid
          %5 = OpTypeFunction %void
       %bool = OpTypeBool
       %true = OpConstantTrue %bool
       %main = OpFunction %void None %5
          %8 = OpLabel
               OpBranch %9
          %9 = OpLabel
               OpLoopMerge %10 %11 None
               OpBranch %12
         %12 = OpLabel
               OpBranchConditional %true %13 %10
         %13 = OpLabel
               OpBranch %11
         %11 = OpLabel
         %14 = OpFunctionCall %void %kill_
               OpBranch %9
         %10 = OpLabel
               OpReturn
               OpFunctionEnd
      %kill_ = OpFunction %void None %5
         %15 = OpLabel
               OpSelectionMerge %16 None
               OpBranchConditional %true %17 %18
         %17 = OpLabel
               OpKill
         %18 = OpLabel
               OpKill
         %16 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  SinglePassRunAndMatch<WrapOpKill>(text, true);
}

TEST_F(WrapOpKillTest, MultipleOpKillInDifferentFunc) {
  const std::string text = R"(
; CHECK: OpEntryPoint Fragment [[main:%\w+]]
; CHECK: [[main]] = OpFunction
; CHECK: OpFunctionCall %void [[orig_kill1:%\w+]]
; CHECK-NEXT: OpFunctionCall %void [[orig_kill2:%\w+]]
; CHECK: [[orig_kill1]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpFunctionCall %void [[new_kill:%\w+]]
; CHECK-NEXT: OpUnreachable
; CHECK: [[orig_kill2]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpFunctionCall %void [[new_kill]]
; CHECK-NEXT: OpUnreachable
; CHECK: [[new_kill]] = OpFunction
; CHECK-NEXT: OpLabel
; CHECK-NEXT: OpKill
; CHECK-NEXT: OpFunctionEnd
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %main "main"
               OpExecutionMode %main OriginUpperLeft
               OpSource GLSL 330
               OpName %main "main"
       %void = OpTypeVoid
          %4 = OpTypeFunction %void
       %bool = OpTypeBool
       %true = OpConstantTrue %bool
       %main = OpFunction %void None %4
          %7 = OpLabel
               OpBranch %8
          %8 = OpLabel
               OpLoopMerge %9 %10 None
               OpBranch %11
         %11 = OpLabel
               OpBranchConditional %true %12 %9
         %12 = OpLabel
               OpBranch %10
         %10 = OpLabel
         %13 = OpFunctionCall %void %14
         %15 = OpFunctionCall %void %16
               OpBranch %8
          %9 = OpLabel
               OpReturn
               OpFunctionEnd
         %14 = OpFunction %void None %4
         %17 = OpLabel
               OpKill
               OpFunctionEnd
         %16 = OpFunction %void None %4
         %18 = OpLabel
               OpKill
               OpFunctionEnd
  )";

  SinglePassRunAndMatch<WrapOpKill>(text, true);
}

TEST_F(WrapOpKillTest, IdBoundOverflow1) {
  const std::string text = R"(
OpCapability GeometryStreams
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %4 "main"
OpExecutionMode %4 OriginUpperLeft
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%4 = OpFunction %2 Pure|Const %3
%4194302 = OpLabel
OpKill
OpFunctionEnd
  )";

  SetAssembleOptions(SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);

  std::vector<Message> messages = {
      {SPV_MSG_ERROR, "", 0, 0, "ID overflow. Try running compact-ids."}};
  SetMessageConsumer(GetTestMessageConsumer(messages));
  auto result = SinglePassRunToBinary<WrapOpKill>(text, true);
  EXPECT_EQ(Pass::Status::Failure, std::get<1>(result));
}

TEST_F(WrapOpKillTest, IdBoundOverflow2) {
  const std::string text = R"(
OpCapability GeometryStreams
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %4 "main"
OpExecutionMode %4 OriginUpperLeft
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%4 = OpFunction %2 Pure|Const %3
%4194301 = OpLabel
OpKill
OpFunctionEnd
  )";

  SetAssembleOptions(SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);

  std::vector<Message> messages = {
      {SPV_MSG_ERROR, "", 0, 0, "ID overflow. Try running compact-ids."}};
  SetMessageConsumer(GetTestMessageConsumer(messages));
  auto result = SinglePassRunToBinary<WrapOpKill>(text, true);
  EXPECT_EQ(Pass::Status::Failure, std::get<1>(result));
}

TEST_F(WrapOpKillTest, IdBoundOverflow3) {
  const std::string text = R"(
OpCapability GeometryStreams
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %4 "main"
OpExecutionMode %4 OriginUpperLeft
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%4 = OpFunction %2 Pure|Const %3
%4194300 = OpLabel
OpKill
OpFunctionEnd
  )";

  SetAssembleOptions(SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);

  std::vector<Message> messages = {
      {SPV_MSG_ERROR, "", 0, 0, "ID overflow. Try running compact-ids."}};
  SetMessageConsumer(GetTestMessageConsumer(messages));
  auto result = SinglePassRunToBinary<WrapOpKill>(text, true);
  EXPECT_EQ(Pass::Status::Failure, std::get<1>(result));
}

}  // namespace
}  // namespace opt
}  // namespace spvtools

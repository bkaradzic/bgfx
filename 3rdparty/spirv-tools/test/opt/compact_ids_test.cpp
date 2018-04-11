// Copyright (c) 2017 Google Inc.
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

#include <gmock/gmock.h>

#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"

#include "pass_fixture.h"
#include "pass_utils.h"

namespace {

using namespace spvtools;

using CompactIdsTest = PassTest<::testing::Test>;

TEST_F(CompactIdsTest, PassOff) {
  const std::string before =
      R"(OpCapability Addresses
OpCapability Kernel
OpCapability GenericPointer
OpCapability Linkage
OpMemoryModel Physical32 OpenCL
%99 = OpTypeInt 32 0
%10 = OpTypeVector %99 2
%20 = OpConstant %99 2
%30 = OpTypeArray %99 %20
)";

  const std::string after = before;

  SetAssembleOptions(SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);
  SetDisassembleOptions(SPV_BINARY_TO_TEXT_OPTION_NO_HEADER);
  SinglePassRunAndCheck<opt::NullPass>(before, after, false, false);
}

TEST_F(CompactIdsTest, PassOn) {
  const std::string before =
      R"(OpCapability Addresses
OpCapability Kernel
OpCapability GenericPointer
OpCapability Linkage
OpMemoryModel Physical32 OpenCL
OpEntryPoint Kernel %3 "simple_kernel"
%99 = OpTypeInt 32 0
%10 = OpTypeVector %99 2
%20 = OpConstant %99 2
%30 = OpTypeArray %99 %20
%40 = OpTypeVoid
%50 = OpTypeFunction %40
 %3 = OpFunction %40 None %50
%70 = OpLabel
OpReturn
OpFunctionEnd
)";

  const std::string after =
      R"(OpCapability Addresses
OpCapability Kernel
OpCapability GenericPointer
OpCapability Linkage
OpMemoryModel Physical32 OpenCL
OpEntryPoint Kernel %1 "simple_kernel"
%2 = OpTypeInt 32 0
%3 = OpTypeVector %2 2
%4 = OpConstant %2 2
%5 = OpTypeArray %2 %4
%6 = OpTypeVoid
%7 = OpTypeFunction %6
%1 = OpFunction %6 None %7
%8 = OpLabel
OpReturn
OpFunctionEnd
)";

  SetAssembleOptions(SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);
  SetDisassembleOptions(SPV_BINARY_TO_TEXT_OPTION_NO_HEADER);
  SinglePassRunAndCheck<opt::CompactIdsPass>(before, after, false, false);
}

TEST(CompactIds, InstructionResultIsUpdated) {
  // For https://github.com/KhronosGroup/SPIRV-Tools/issues/827
  // In that bug, the compact Ids pass was directly updating the result Id
  // word for an OpFunction instruction, but not updating the cached
  // result_id_ in that Instruction object.
  //
  // This test is a bit cheesy.  We don't expose internal interfaces enough
  // to see the inconsistency.  So reproduce the original scenario, with
  // compact ids followed by a pass that trips up on the inconsistency.

  const std::string input(R"(OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %100 "main"
%200 = OpTypeVoid
%300 = OpTypeFunction %200
%100 = OpFunction %300 None %200
%400 = OpLabel
OpReturn
OpFunctionEnd
)");

  std::vector<uint32_t> binary;
  const spv_target_env env = SPV_ENV_UNIVERSAL_1_0;
  spvtools::SpirvTools tools(env);
  auto assembled = tools.Assemble(
      input, &binary, SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);
  EXPECT_TRUE(assembled);

  spvtools::Optimizer optimizer(env);
  optimizer.RegisterPass(CreateCompactIdsPass());
  // The exhaustive inliner will use the result_id
  optimizer.RegisterPass(CreateInlineExhaustivePass());

  // This should not crash!
  optimizer.Run(binary.data(), binary.size(), &binary);

  std::string disassembly;
  tools.Disassemble(binary, &disassembly, SPV_BINARY_TO_TEXT_OPTION_NO_HEADER);

  const std::string expected(R"(OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %1 "main"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%1 = OpFunction %3 None %2
%4 = OpLabel
OpReturn
OpFunctionEnd
)");

  EXPECT_THAT(disassembly, ::testing::Eq(expected));
}

TEST(CompactIds, HeaderIsUpdated) {
  const std::string input(R"(OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %100 "main"
%200 = OpTypeVoid
%300 = OpTypeFunction %200
%100 = OpFunction %300 None %200
%400 = OpLabel
OpReturn
OpFunctionEnd
)");

  std::vector<uint32_t> binary;
  const spv_target_env env = SPV_ENV_UNIVERSAL_1_0;
  spvtools::SpirvTools tools(env);
  auto assembled = tools.Assemble(
      input, &binary, SPV_TEXT_TO_BINARY_OPTION_PRESERVE_NUMERIC_IDS);
  EXPECT_TRUE(assembled);

  spvtools::Optimizer optimizer(env);
  optimizer.RegisterPass(CreateCompactIdsPass());
  // The exhaustive inliner will use the result_id
  optimizer.RegisterPass(CreateInlineExhaustivePass());

  // This should not crash!
  optimizer.Run(binary.data(), binary.size(), &binary);

  std::string disassembly;
  tools.Disassemble(binary, &disassembly, SPV_BINARY_TO_TEXT_OPTION_NONE);

  const std::string expected(R"(; SPIR-V
; Version: 1.0
; Generator: Khronos SPIR-V Tools Assembler; 0
; Bound: 5
; Schema: 0
OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %1 "main"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%1 = OpFunction %3 None %2
%4 = OpLabel
OpReturn
OpFunctionEnd
)");

  EXPECT_THAT(disassembly, ::testing::Eq(expected));
}

}  // anonymous namespace

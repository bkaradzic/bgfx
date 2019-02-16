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

#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "spirv-tools/libspirv.hpp"
#include "spirv-tools/optimizer.hpp"
#include "test/opt/pass_fixture.h"

namespace spvtools {
namespace opt {
namespace {

using ::testing::Eq;

// Return a string that contains the minimum instructions needed to form
// a valid module.  Other instructions can be appended to this string.
std::string Header() {
  return R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
)";
}

TEST(Optimizer, CanRunNullPassWithDistinctInputOutputVectors) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  std::vector<uint32_t> binary_in;
  tools.Assemble(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid",
                 &binary_in);

  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  opt.RegisterPass(CreateNullPass());
  std::vector<uint32_t> binary_out;
  opt.Run(binary_in.data(), binary_in.size(), &binary_out);

  std::string disassembly;
  tools.Disassemble(binary_out.data(), binary_out.size(), &disassembly);
  EXPECT_THAT(disassembly,
              Eq(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid\n"));
}

TEST(Optimizer, CanRunTransformingPassWithDistinctInputOutputVectors) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  std::vector<uint32_t> binary_in;
  tools.Assemble(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid",
                 &binary_in);

  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  opt.RegisterPass(CreateStripDebugInfoPass());
  std::vector<uint32_t> binary_out;
  opt.Run(binary_in.data(), binary_in.size(), &binary_out);

  std::string disassembly;
  tools.Disassemble(binary_out.data(), binary_out.size(), &disassembly);
  EXPECT_THAT(disassembly, Eq(Header() + "%void = OpTypeVoid\n"));
}

TEST(Optimizer, CanRunNullPassWithAliasedVectors) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  std::vector<uint32_t> binary;
  tools.Assemble("OpName %foo \"foo\"\n%foo = OpTypeVoid", &binary);

  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  opt.RegisterPass(CreateNullPass());
  opt.Run(binary.data(), binary.size(), &binary);  // This is the key.

  std::string disassembly;
  tools.Disassemble(binary.data(), binary.size(), &disassembly);
  EXPECT_THAT(disassembly, Eq("OpName %foo \"foo\"\n%foo = OpTypeVoid\n"));
}

TEST(Optimizer, CanRunNullPassWithAliasedVectorDataButDifferentSize) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  std::vector<uint32_t> binary;
  tools.Assemble(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid", &binary);

  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  opt.RegisterPass(CreateNullPass());
  auto orig_size = binary.size();
  // Now change the size.  Add a word that will be ignored
  // by the optimizer.
  binary.push_back(42);
  EXPECT_THAT(orig_size + 1, Eq(binary.size()));
  opt.Run(binary.data(), orig_size, &binary);  // This is the key.
  // The binary vector should have been rewritten.
  EXPECT_THAT(binary.size(), Eq(orig_size));

  std::string disassembly;
  tools.Disassemble(binary.data(), binary.size(), &disassembly);
  EXPECT_THAT(disassembly,
              Eq(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid\n"));
}

TEST(Optimizer, CanRunTransformingPassWithAliasedVectors) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  std::vector<uint32_t> binary;
  tools.Assemble(Header() + "OpName %foo \"foo\"\n%foo = OpTypeVoid", &binary);

  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  opt.RegisterPass(CreateStripDebugInfoPass());
  opt.Run(binary.data(), binary.size(), &binary);  // This is the key

  std::string disassembly;
  tools.Disassemble(binary.data(), binary.size(), &disassembly);
  EXPECT_THAT(disassembly, Eq(Header() + "%void = OpTypeVoid\n"));
}

TEST(Optimizer, CanValidateFlags) {
  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);
  EXPECT_FALSE(opt.FlagHasValidForm("bad-flag"));
  EXPECT_TRUE(opt.FlagHasValidForm("-O"));
  EXPECT_TRUE(opt.FlagHasValidForm("-Os"));
  EXPECT_FALSE(opt.FlagHasValidForm("-O2"));
  EXPECT_TRUE(opt.FlagHasValidForm("--this_flag"));
}

TEST(Optimizer, CanRegisterPassesFromFlags) {
  SpirvTools tools(SPV_ENV_UNIVERSAL_1_0);
  Optimizer opt(SPV_ENV_UNIVERSAL_1_0);

  spv_message_level_t msg_level;
  const char* msg_fname;
  spv_position_t msg_position;
  const char* msg;
  auto examine_message = [&msg_level, &msg_fname, &msg_position, &msg](
                             spv_message_level_t ml, const char* f,
                             const spv_position_t& p, const char* m) {
    msg_level = ml;
    msg_fname = f;
    msg_position = p;
    msg = m;
  };
  opt.SetMessageConsumer(examine_message);

  std::vector<std::string> pass_flags = {
      "--strip-debug",
      "--strip-reflect",
      "--set-spec-const-default-value=23:42 21:12",
      "--if-conversion",
      "--freeze-spec-const",
      "--inline-entry-points-exhaustive",
      "--inline-entry-points-opaque",
      "--convert-local-access-chains",
      "--eliminate-dead-code-aggressive",
      "--eliminate-insert-extract",
      "--eliminate-local-single-block",
      "--eliminate-local-single-store",
      "--merge-blocks",
      "--merge-return",
      "--eliminate-dead-branches",
      "--eliminate-dead-functions",
      "--eliminate-local-multi-store",
      "--eliminate-common-uniform",
      "--eliminate-dead-const",
      "--eliminate-dead-inserts",
      "--eliminate-dead-variables",
      "--fold-spec-const-op-composite",
      "--loop-unswitch",
      "--scalar-replacement=300",
      "--scalar-replacement",
      "--strength-reduction",
      "--unify-const",
      "--flatten-decorations",
      "--compact-ids",
      "--cfg-cleanup",
      "--local-redundancy-elimination",
      "--loop-invariant-code-motion",
      "--reduce-load-size",
      "--redundancy-elimination",
      "--private-to-local",
      "--remove-duplicates",
      "--workaround-1209",
      "--replace-invalid-opcode",
      "--simplify-instructions",
      "--ssa-rewrite",
      "--copy-propagate-arrays",
      "--loop-fission=20",
      "--loop-fusion=2",
      "--loop-unroll",
      "--vector-dce",
      "--loop-unroll-partial=3",
      "--loop-peeling",
      "--ccp",
      "-O",
      "-Os",
      "--legalize-hlsl"};
  EXPECT_TRUE(opt.RegisterPassesFromFlags(pass_flags));

  // Test some invalid flags.
  EXPECT_FALSE(opt.RegisterPassFromFlag("-O2"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("-loop-unroll"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("--set-spec-const-default-value"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("--scalar-replacement=s"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("--loop-fission=-4"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("--loop-fusion=xx"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);

  EXPECT_FALSE(opt.RegisterPassFromFlag("--loop-unroll-partial"));
  EXPECT_EQ(msg_level, SPV_MSG_ERROR);
}

TEST(Optimizer, WebGPUModeSetsCorrectPasses) {
  Optimizer opt(SPV_ENV_WEBGPU_0);
  opt.RegisterWebGPUPasses();
  std::vector<const char*> pass_names = opt.GetPassNames();

  std::vector<std::string> registered_passes;
  for (auto name = pass_names.begin(); name != pass_names.end(); ++name)
    registered_passes.push_back(*name);

  std::vector<std::string> expected_passes = {
      "eliminate-dead-branches", "eliminate-dead-code-aggressive",
      "flatten-decorations", "strip-debug"};
  std::sort(registered_passes.begin(), registered_passes.end());
  std::sort(expected_passes.begin(), expected_passes.end());

  ASSERT_EQ(registered_passes.size(), expected_passes.size());
  for (size_t i = 0; i < registered_passes.size(); i++)
    EXPECT_EQ(registered_passes[i], expected_passes[i]);
}

struct WebGPUPassCase {
  // Input SPIR-V
  std::string input;
  // Expected result SPIR-V
  std::string expected;
  // Specific pass under test, used for logging messages.
  std::string pass;
};

using WebGPUPassTest = PassTest<::testing::TestWithParam<WebGPUPassCase>>;

TEST_P(WebGPUPassTest, Ran) {
  SpirvTools tools(SPV_ENV_WEBGPU_0);
  std::vector<uint32_t> binary;
  tools.Assemble(GetParam().input, &binary);

  Optimizer opt(SPV_ENV_WEBGPU_0);
  opt.RegisterWebGPUPasses();

  std::vector<uint32_t> optimized;
  class ValidatorOptions validator_options;
  ASSERT_TRUE(opt.Run(binary.data(), binary.size(), &optimized,
                      validator_options, true));

  std::string disassembly;
  tools.Disassemble(optimized.data(), optimized.size(), &disassembly);

  EXPECT_EQ(GetParam().expected, disassembly)
      << "Was expecting pass '" << GetParam().pass << "' to have been run.\n";
}

INSTANTIATE_TEST_SUITE_P(
    WebGPU, WebGPUPassTest,
    ::testing::ValuesIn(std::vector<WebGPUPassCase>{
        // FlattenDecorations
        {// input
         "OpCapability Shader\n"
         "OpCapability VulkanMemoryModelKHR\n"
         "OpExtension \"SPV_KHR_vulkan_memory_model\"\n"
         "OpMemoryModel Logical VulkanKHR\n"
         "OpEntryPoint Fragment %main \"main\" %hue %saturation %value\n"
         "OpExecutionMode %main OriginUpperLeft\n"
         "OpDecorate %group Flat\n"
         "OpDecorate %group NoPerspective\n"
         "%group = OpDecorationGroup\n"
         "%void = OpTypeVoid\n"
         "%void_fn = OpTypeFunction %void\n"
         "%float = OpTypeFloat 32\n"
         "%_ptr_Input_float = OpTypePointer Input %float\n"
         "%hue = OpVariable %_ptr_Input_float Input\n"
         "%saturation = OpVariable %_ptr_Input_float Input\n"
         "%value = OpVariable %_ptr_Input_float Input\n"
         "%main = OpFunction %void None %void_fn\n"
         "%entry = OpLabel\n"
         "OpReturn\n"
         "OpFunctionEnd\n",
         // expected
         "OpCapability Shader\n"
         "OpCapability VulkanMemoryModelKHR\n"
         "OpExtension \"SPV_KHR_vulkan_memory_model\"\n"
         "OpMemoryModel Logical VulkanKHR\n"
         "OpEntryPoint Fragment %1 \"main\" %2 %3 %4\n"
         "OpExecutionMode %1 OriginUpperLeft\n"
         "%void = OpTypeVoid\n"
         "%7 = OpTypeFunction %void\n"
         "%float = OpTypeFloat 32\n"
         "%_ptr_Input_float = OpTypePointer Input %float\n"
         "%2 = OpVariable %_ptr_Input_float Input\n"
         "%3 = OpVariable %_ptr_Input_float Input\n"
         "%4 = OpVariable %_ptr_Input_float Input\n"
         "%1 = OpFunction %void None %7\n"
         "%10 = OpLabel\n"
         "OpReturn\n"
         "OpFunctionEnd\n",
         // pass
         "flatten-decorations"},
        // Strip Debug
        {// input
         "OpCapability Shader\n"
         "OpCapability VulkanMemoryModelKHR\n"
         "OpExtension \"SPV_KHR_vulkan_memory_model\"\n"
         "OpMemoryModel Logical VulkanKHR\n"
         "OpEntryPoint Vertex %func \"shader\"\n"
         "OpName %main \"main\"\n"
         "OpName %void_fn \"void_fn\"\n"
         "%void = OpTypeVoid\n"
         "%void_f = OpTypeFunction %void\n"
         "%func = OpFunction %void None %void_f\n"
         "%label = OpLabel\n"
         "OpReturn\n"
         "OpFunctionEnd\n",
         // expected
         "OpCapability Shader\n"
         "OpCapability VulkanMemoryModelKHR\n"
         "OpExtension \"SPV_KHR_vulkan_memory_model\"\n"
         "OpMemoryModel Logical VulkanKHR\n"
         "OpEntryPoint Vertex %1 \"shader\"\n"
         "%void = OpTypeVoid\n"
         "%5 = OpTypeFunction %void\n"
         "%1 = OpFunction %void None %5\n"
         "%6 = OpLabel\n"
         "OpReturn\n"
         "OpFunctionEnd\n",
         // pass
         "strip-debug"}}));

}  // namespace
}  // namespace opt
}  // namespace spvtools

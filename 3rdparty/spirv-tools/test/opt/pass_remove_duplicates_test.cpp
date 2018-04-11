// Copyright (c) 2017 Pierre Moreau
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

#include <iostream>

#include <gmock/gmock.h>

#include "source/opt/build_module.h"
#include "source/opt/ir_context.h"
#include "source/opt/pass_manager.h"
#include "source/opt/remove_duplicates_pass.h"
#include "source/spirv_constant.h"
#include "unit_spirv.h"

namespace {

using spvtools::ir::IRContext;
using spvtools::ir::Instruction;
using spvtools::opt::PassManager;
using spvtools::opt::RemoveDuplicatesPass;

class RemoveDuplicatesTest : public ::testing::Test {
 public:
  RemoveDuplicatesTest()
      : tools_(SPV_ENV_UNIVERSAL_1_2),
        context_(),
        consumer_([this](spv_message_level_t level, const char*,
                         const spv_position_t& position, const char* message) {
          if (!error_message_.empty()) error_message_ += "\n";
          switch (level) {
            case SPV_MSG_FATAL:
            case SPV_MSG_INTERNAL_ERROR:
            case SPV_MSG_ERROR:
              error_message_ += "ERROR";
              break;
            case SPV_MSG_WARNING:
              error_message_ += "WARNING";
              break;
            case SPV_MSG_INFO:
              error_message_ += "INFO";
              break;
            case SPV_MSG_DEBUG:
              error_message_ += "DEBUG";
              break;
          }
          error_message_ +=
              ": " + std::to_string(position.index) + ": " + message;
        }),
        disassemble_options_(SPV_BINARY_TO_TEXT_OPTION_NO_HEADER),
        error_message_() {
    tools_.SetMessageConsumer(consumer_);
  }

  virtual void TearDown() override { error_message_.clear(); }

  std::string RunPass(const std::string& text) {
    context_ = spvtools::BuildModule(SPV_ENV_UNIVERSAL_1_2, consumer_, text);
    if (!context_.get()) return std::string();

    PassManager manager;
    manager.SetMessageConsumer(consumer_);
    manager.AddPass<RemoveDuplicatesPass>();

    spvtools::opt::Pass::Status pass_res = manager.Run(context_.get());
    if (pass_res == spvtools::opt::Pass::Status::Failure) return std::string();

    return ModuleToText();
  }

  // Disassembles |binary| and outputs the result in |text|. If |text| is a
  // null pointer, SPV_ERROR_INVALID_POINTER is returned.
  spv_result_t Disassemble(const std::vector<uint32_t>& binary,
                           std::string* text) {
    if (!text) return SPV_ERROR_INVALID_POINTER;
    return tools_.Disassemble(binary, text, disassemble_options_)
               ? SPV_SUCCESS
               : SPV_ERROR_INVALID_BINARY;
  }

  // Returns the accumulated error messages for the test.
  std::string GetErrorMessage() const { return error_message_; }

  std::string ToText(const std::vector<Instruction*>& inst) {
    std::vector<uint32_t> binary = {SpvMagicNumber, 0x10200, 0u, 2u, 0u};
    for (const Instruction* i : inst)
      i->ToBinaryWithoutAttachedDebugInsts(&binary);
    std::string text;
    Disassemble(binary, &text);
    return text;
  }

  std::string ModuleToText() {
    std::vector<uint32_t> binary;
    context_->module()->ToBinary(&binary, false);
    std::string text;
    Disassemble(binary, &text);
    return text;
  }

 private:
  spvtools::SpirvTools
      tools_;  // An instance for calling SPIRV-Tools functionalities.
  std::unique_ptr<IRContext> context_;
  spvtools::MessageConsumer consumer_;
  uint32_t disassemble_options_;
  std::string error_message_;
};

TEST_F(RemoveDuplicatesTest, DuplicateCapabilities) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability Shader
OpMemoryModel Logical GLSL450
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, DuplicateExtInstImports) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
%1 = OpExtInstImport "OpenCL.std"
%2 = OpExtInstImport "OpenCL.std"
%3 = OpExtInstImport "GLSL.std.450"
OpMemoryModel Logical GLSL450
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
%1 = OpExtInstImport "OpenCL.std"
%3 = OpExtInstImport "GLSL.std.450"
OpMemoryModel Logical GLSL450
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, DuplicateTypes) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%1 = OpTypeInt 32 0
%2 = OpTypeInt 32 0
%3 = OpTypeStruct %1 %2
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%1 = OpTypeInt 32 0
%3 = OpTypeStruct %1 %1
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, SameTypeDifferentMemberDecoration) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 GLSLPacked
%2 = OpTypeInt 32 0
%1 = OpTypeStruct %2 %2
%3 = OpTypeStruct %2 %2
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 GLSLPacked
%2 = OpTypeInt 32 0
%1 = OpTypeStruct %2 %2
%3 = OpTypeStruct %2 %2
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, SameTypeAndMemberDecoration) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 GLSLPacked
OpDecorate %2 GLSLPacked
%3 = OpTypeInt 32 0
%1 = OpTypeStruct %3 %3
%2 = OpTypeStruct %3 %3
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 GLSLPacked
%3 = OpTypeInt 32 0
%1 = OpTypeStruct %3 %3
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, SameTypeAndDifferentName) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpName %1 "Type1"
OpName %2 "Type2"
%3 = OpTypeInt 32 0
%1 = OpTypeStruct %3 %3
%2 = OpTypeStruct %3 %3
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpName %1 "Type1"
%3 = OpTypeInt 32 0
%1 = OpTypeStruct %3 %3
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

// Check that #1033 has been fixed.
TEST_F(RemoveDuplicatesTest, DoNotRemoveDifferentOpDecorationGroup) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 Constant
%1 = OpDecorationGroup
OpDecorate %2 Restrict
%2 = OpDecorationGroup
OpGroupDecorate %3 %1 %2
%4 = OpTypeInt 32 0
%3 = OpVariable %4 Uniform
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 Constant
%1 = OpDecorationGroup
OpDecorate %2 Restrict
%2 = OpDecorationGroup
OpGroupDecorate %3 %1 %2
%4 = OpTypeInt 32 0
%3 = OpVariable %4 Uniform
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

TEST_F(RemoveDuplicatesTest, DifferentDecorationGroup) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 Constant
OpDecorate %1 Restrict
%1 = OpDecorationGroup
OpDecorate %2 Constant
%2 = OpDecorationGroup
OpGroupDecorate %1 %3
OpGroupDecorate %2 %4
%5 = OpTypeInt 32 0
%3 = OpVariable %5 Uniform
%4 = OpVariable %5 Uniform
)";
  const std::string after = R"(OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %1 Constant
OpDecorate %1 Restrict
%1 = OpDecorationGroup
OpDecorate %2 Constant
%2 = OpDecorationGroup
OpGroupDecorate %1 %3
OpGroupDecorate %2 %4
%5 = OpTypeInt 32 0
%3 = OpVariable %5 Uniform
%4 = OpVariable %5 Uniform
)";

  EXPECT_THAT(RunPass(spirv), after);
  EXPECT_THAT(GetErrorMessage(), "");
}

}  // namespace

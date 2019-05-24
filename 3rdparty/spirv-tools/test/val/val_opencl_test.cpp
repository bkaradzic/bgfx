// Copyright (c) 2019 The Khronos Group Inc.
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

// Validation tests for OpenCL env specific checks

#include <string>

#include "gmock/gmock.h"
#include "test/val/val_fixtures.h"

namespace spvtools {
namespace val {
namespace {

using testing::HasSubstr;

using ValidateOpenCL = spvtest::ValidateBase<bool>;

TEST_F(ValidateOpenCL, NonPhysicalAddressingModelBad) {
  std::string spirv = R"(
     OpCapability Kernel
     OpMemoryModel Logical OpenCL
)";

  CompileSuccessfully(spirv);

  EXPECT_EQ(SPV_ERROR_INVALID_DATA, ValidateInstructions(SPV_ENV_OPENCL_1_2));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Addressing model must be Physical32 or Physical64 "
                        "in the OpenCL environment.\n  OpMemoryModel Logical "
                        "OpenCL\n"));
}

TEST_F(ValidateOpenCL, NonOpenCLMemoryModelBad) {
  std::string spirv = R"(
     OpCapability Kernel
     OpMemoryModel Physical32 GLSL450
)";

  CompileSuccessfully(spirv);

  EXPECT_EQ(SPV_ERROR_INVALID_DATA, ValidateInstructions(SPV_ENV_OPENCL_1_2));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Memory model must be OpenCL in the OpenCL environment."
                        "\n  OpMemoryModel Physical32 GLSL450\n"));
}

}  // namespace
}  // namespace val
}  // namespace spvtools

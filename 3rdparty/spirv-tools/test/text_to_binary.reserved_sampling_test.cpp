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

// Validation tests for illegal instructions

#include "unit_spirv.h"

#include "gmock/gmock.h"
#include "test_fixture.h"

namespace {

using ::testing::Eq;

using ReservedSamplingInstTest = spvtest::TextToBinaryTest;

TEST_F(ReservedSamplingInstTest, OpImageSparseSampleProjImplicitLod) {
  const std::string input = "OpImageSparseSampleProjImplicitLod %1 %2 %3\n";
  EXPECT_THAT(CompileFailure(input),
              Eq("Invalid Opcode name 'OpImageSparseSampleProjImplicitLod'"));
}

TEST_F(ReservedSamplingInstTest, OpImageSparseSampleProjExplicitLod) {
  const std::string input =
      "OpImageSparseSampleProjExplicitLod %1 %2 %3 Lod %4\n";
  EXPECT_THAT(CompileFailure(input),
              Eq("Invalid Opcode name 'OpImageSparseSampleProjExplicitLod'"));
}

TEST_F(ReservedSamplingInstTest, OpImageSparseSampleProjDrefImplicitLod) {
  const std::string input =
      "OpImageSparseSampleProjDrefImplicitLod %1 %2 %3 %4\n";
  EXPECT_THAT(
      CompileFailure(input),
      Eq("Invalid Opcode name 'OpImageSparseSampleProjDrefImplicitLod'"));
}

TEST_F(ReservedSamplingInstTest, OpImageSparseSampleProjDrefExplicitLod) {
  const std::string input =
      "OpImageSparseSampleProjDrefExplicitLod %1 %2 %3 %4 Lod %5\n";
  EXPECT_THAT(
      CompileFailure(input),
      Eq("Invalid Opcode name 'OpImageSparseSampleProjDrefExplicitLod'"));
}

}  // namespace

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

#include "reduce_test_util.h"

namespace spvtools {
namespace reduce {

void CheckEqual(const spv_target_env env,
                const std::vector<uint32_t>& expected_binary,
                const std::vector<uint32_t>& actual_binary) {
  if (expected_binary != actual_binary) {
    SpirvTools t(env);
    std::string expected_disassembled;
    std::string actual_disassembled;
    ASSERT_TRUE(t.Disassemble(expected_binary, &expected_disassembled,
                              kReduceDisassembleOption));
    ASSERT_TRUE(t.Disassemble(actual_binary, &actual_disassembled,
                              kReduceDisassembleOption));
    ASSERT_EQ(expected_disassembled, actual_disassembled);
  }
}

void CheckEqual(const spv_target_env env, const std::string& expected_text,
                const std::vector<uint32_t>& actual_binary) {
  std::vector<uint32_t> expected_binary;
  SpirvTools t(env);
  ASSERT_TRUE(
      t.Assemble(expected_text, &expected_binary, kReduceAssembleOption));
  CheckEqual(env, expected_binary, actual_binary);
}

void CheckEqual(const spv_target_env env, const std::string& expected_text,
                const opt::IRContext* actual_ir) {
  std::vector<uint32_t> actual_binary;
  actual_ir->module()->ToBinary(&actual_binary, false);
  CheckEqual(env, expected_text, actual_binary);
}

void CheckValid(spv_target_env env, const opt::IRContext* ir) {
  std::vector<uint32_t> binary;
  ir->module()->ToBinary(&binary, false);
  SpirvTools t(env);
  ASSERT_TRUE(t.Validate(binary));
}

std::string ToString(spv_target_env env, const opt::IRContext* ir) {
  std::vector<uint32_t> binary;
  ir->module()->ToBinary(&binary, false);
  SpirvTools t(env);
  std::string result;
  t.Disassemble(binary, &result, kReduceDisassembleOption);
  return result;
}

void NopDiagnostic(spv_message_level_t /*level*/, const char* /*source*/,
                   const spv_position_t& /*position*/,
                   const char* /*message*/) {}

}  // namespace reduce
}  // namespace spvtools

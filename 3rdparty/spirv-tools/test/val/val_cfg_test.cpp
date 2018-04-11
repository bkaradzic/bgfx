// Copyright (c) 2015-2016 The Khronos Group Inc.
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

// Validation tests for Control Flow Graph

#include <array>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "gmock/gmock.h"

#include "source/diagnostic.h"
#include "source/validate.h"
#include "test_fixture.h"
#include "unit_spirv.h"
#include "val_fixtures.h"

using std::array;
using std::make_pair;
using std::pair;
using std::string;
using std::stringstream;
using std::vector;

using ::testing::HasSubstr;
using ::testing::MatchesRegex;

using libspirv::BasicBlock;
using libspirv::ValidationState_t;

using ValidateCFG = spvtest::ValidateBase<SpvCapability>;
using spvtest::ScopedContext;

namespace {

string nameOps() { return ""; }

template <typename... Args>
string nameOps(pair<string, string> head, Args... names) {
  return "OpName %" + head.first + " \"" + head.second + "\"\n" +
         nameOps(names...);
}

template <typename... Args>
string nameOps(string head, Args... names) {
  return "OpName %" + head + " \"" + head + "\"\n" + nameOps(names...);
}

/// This class allows the easy creation of complex control flow without writing
/// SPIR-V. This class is used in the test cases below.
class Block {
  string label_;
  string body_;
  SpvOp type_;
  vector<Block> successors_;

 public:
  /// Creates a Block with a given label
  ///
  /// @param[in]: label the label id of the block
  /// @param[in]: type the branch instruciton that ends the block
  explicit Block(string label, SpvOp type = SpvOpBranch)
      : label_(label), body_(), type_(type), successors_() {}

  /// Sets the instructions which will appear in the body of the block
  Block& SetBody(std::string body) {
    body_ = body;
    return *this;
  }

  Block& AppendBody(std::string body) {
    body_ += body;
    return *this;
  }

  /// Converts the block into a SPIR-V string
  operator string() {
    stringstream out;
    out << std::setw(8) << "%" + label_ + "  = OpLabel \n";
    if (!body_.empty()) {
      out << body_;
    }

    switch (type_) {
      case SpvOpBranchConditional:
        out << "OpBranchConditional %cond ";
        for (Block& b : successors_) {
          out << "%" + b.label_ + " ";
        }
        break;
      case SpvOpSwitch: {
        out << "OpSwitch %one %" + successors_.front().label_;
        stringstream ss;
        for (size_t i = 1; i < successors_.size(); i++) {
          ss << " " << i << " %" << successors_[i].label_;
        }
        out << ss.str();
      } break;
      case SpvOpReturn:
        assert(successors_.size() == 0);
        out << "OpReturn\n";
        break;
      case SpvOpUnreachable:
        assert(successors_.size() == 0);
        out << "OpUnreachable\n";
        break;
      case SpvOpBranch:
        assert(successors_.size() == 1);
        out << "OpBranch %" + successors_.front().label_;
        break;
      default:
        assert(1 == 0 && "Unhandled");
    }
    out << "\n";

    return out.str();
  }
  friend Block& operator>>(Block& curr, vector<Block> successors);
  friend Block& operator>>(Block& lhs, Block& successor);
};

/// Assigns the successors for the Block on the lhs
Block& operator>>(Block& lhs, vector<Block> successors) {
  if (lhs.type_ == SpvOpBranchConditional) {
    assert(successors.size() == 2);
  } else if (lhs.type_ == SpvOpSwitch) {
    assert(successors.size() > 1);
  }
  lhs.successors_ = successors;
  return lhs;
}

/// Assigns the successor for the Block on the lhs
Block& operator>>(Block& lhs, Block& successor) {
  assert(lhs.type_ == SpvOpBranch);
  lhs.successors_.push_back(successor);
  return lhs;
}

const char* header(SpvCapability cap) {
  static const char* shader_header =
      "OpCapability Shader\n"
      "OpCapability Linkage\n"
      "OpMemoryModel Logical GLSL450\n";

  static const char* kernel_header =
      "OpCapability Kernel\n"
      "OpCapability Linkage\n"
      "OpMemoryModel Logical OpenCL\n";

  return (cap == SpvCapabilityShader) ? shader_header : kernel_header;
}

const char* types_consts() {
  static const char* types =
      "%voidt   = OpTypeVoid\n"
      "%boolt   = OpTypeBool\n"
      "%intt    = OpTypeInt 32 0\n"
      "%one     = OpConstant %intt 1\n"
      "%two     = OpConstant %intt 2\n"
      "%ptrt    = OpTypePointer Function %intt\n"
      "%funct   = OpTypeFunction %voidt\n";

  return types;
}

INSTANTIATE_TEST_CASE_P(StructuredControlFlow, ValidateCFG,
                        ::testing::Values(SpvCapabilityShader,
                                          SpvCapabilityKernel));

TEST_P(ValidateCFG, LoopReachableFromEntryButNeverLeadingToReturn) {
  // In this case, the loop is reachable from a node without a predecessor,
  // but never reaches a node with a return.
  //
  // This motivates the need for the pseudo-exit node to have a node
  // from a cycle in its predecessors list.  Otherwise the validator's
  // post-dominance calculation will go into an infinite loop.
  //
  // For more motivation, see
  // https://github.com/KhronosGroup/SPIRV-Tools/issues/279
  string str = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450

           OpName %entry "entry"
           OpName %loop "loop"
           OpName %exit "exit"

%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt

%main    = OpFunction %voidt None %funct
%entry   = OpLabel
           OpBranch %loop
%loop    = OpLabel
           OpLoopMerge %exit %loop None
           OpBranch %loop
%exit    = OpLabel
           OpReturn
           OpFunctionEnd
  )";
  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions()) << str;
}

TEST_P(ValidateCFG, LoopUnreachableFromEntryButLeadingToReturn) {
  // In this case, the loop is not reachable from a node without a
  // predecessor, but eventually reaches a node with a return.
  //
  // This motivates the need for the pseudo-entry node to have a node
  // from a cycle in its successors list.  Otherwise the validator's
  // dominance calculation will go into an infinite loop.
  //
  // For more motivation, see
  // https://github.com/KhronosGroup/SPIRV-Tools/issues/279
  // Before that fix, we'd have an infinite loop when calculating
  // post-dominators.
  string str = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450

           OpName %entry "entry"
           OpName %loop "loop"
           OpName %cont "cont"
           OpName %exit "exit"

%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt
%boolt   = OpTypeBool
%false   = OpConstantFalse %boolt

%main    = OpFunction %voidt None %funct
%entry   = OpLabel
           OpReturn

%loop    = OpLabel
           OpLoopMerge %exit %cont None
           OpBranch %cont

%cont    = OpLabel
           OpBranchConditional %false %loop %exit

%exit    = OpLabel
           OpReturn
           OpFunctionEnd
  )";
  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions())
      << str << getDiagnosticString();
}

TEST_P(ValidateCFG, Simple) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block cont("cont");
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop.SetBody("OpLoopMerge %merge %cont None\n");
  }

  string str =
      header(GetParam()) +
      nameOps("loop", "entry", "cont", "merge", make_pair("func", "Main")) +
      types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({cont, merge});
  str += cont >> loop;
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, Variable) {
  Block entry("entry");
  Block cont("cont");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%var = OpVariable %ptrt Function\n");

  string str = header(GetParam()) + nameOps(make_pair("func", "Main")) +
               types_consts() + " %func    = OpFunction %voidt None %funct\n";
  str += entry >> cont;
  str += cont >> exit;
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, VariableNotInFirstBlockBad) {
  Block entry("entry");
  Block cont("cont");
  Block exit("exit", SpvOpReturn);

  // This operation should only be performed in the entry block
  cont.SetBody("%var = OpVariable %ptrt Function\n");

  string str = header(GetParam()) + nameOps(make_pair("func", "Main")) +
               types_consts() + " %func    = OpFunction %voidt None %funct\n";

  str += entry >> cont;
  str += cont >> exit;
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Variables can only be defined in the first block of a function"));
}

TEST_P(ValidateCFG, BlockSelfLoopIsOk) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody("OpLoopMerge %merge %loop None\n");

  string str = header(GetParam()) +
               nameOps("loop", "merge", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  // loop branches to itself, but does not trigger an error.
  str += loop >> vector<Block>({merge, loop});
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions()) << getDiagnosticString();
}

TEST_P(ValidateCFG, BlockAppearsBeforeDominatorBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block cont("cont");
  Block branch("branch", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) branch.SetBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("cont", "branch", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> branch;
  str += cont >> merge;  // cont appears before its dominator
  str += branch >> vector<Block>({cont, merge});
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              MatchesRegex("Block .\\[cont\\] appears in the binary "
                           "before its dominator .\\[branch\\]"));
}

TEST_P(ValidateCFG, MergeBlockTargetedByMultipleHeaderBlocksBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop");
  Block selection("selection", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody(" OpLoopMerge %merge %loop None\n");

  // cannot share the same merge
  if (is_shader) selection.SetBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("merge", make_pair("func", "Main")) + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> selection;
  str += selection >> vector<Block>({loop, merge});
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("Block .\\[merge\\] is already a merge block "
                             "for another header"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, MergeBlockTargetedByMultipleHeaderBlocksSelectionBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block selection("selection", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) selection.SetBody(" OpSelectionMerge %merge None\n");

  // cannot share the same merge
  if (is_shader) loop.SetBody(" OpLoopMerge %merge %loop None\n");

  string str = header(GetParam()) +
               nameOps("merge", make_pair("func", "Main")) + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> selection;
  str += selection >> vector<Block>({merge, loop});
  str += loop >> vector<Block>({loop, merge});
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("Block .\\[merge\\] is already a merge block "
                             "for another header"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, BranchTargetFirstBlockBad) {
  Block entry("entry");
  Block bad("bad");
  Block end("end", SpvOpReturn);
  string str = header(GetParam()) +
               nameOps("entry", "bad", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> bad;
  str += bad >> entry;  // Cannot target entry block
  str += end;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              MatchesRegex("First block .\\[entry\\] of function .\\[Main\\] "
                           "is targeted by block .\\[bad\\]"));
}

TEST_P(ValidateCFG, BranchConditionalTrueTargetFirstBlockBad) {
  Block entry("entry");
  Block bad("bad", SpvOpBranchConditional);
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  bad.SetBody(" OpLoopMerge %entry %exit None\n");

  string str = header(GetParam()) +
               nameOps("entry", "bad", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> bad;
  str += bad >> vector<Block>({entry, exit});  // cannot target entry block
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              MatchesRegex("First block .\\[entry\\] of function .\\[Main\\] "
                           "is targeted by block .\\[bad\\]"));
}

TEST_P(ValidateCFG, BranchConditionalFalseTargetFirstBlockBad) {
  Block entry("entry");
  Block bad("bad", SpvOpBranchConditional);
  Block t("t");
  Block merge("merge");
  Block end("end", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  bad.SetBody("OpLoopMerge %merge %cont None\n");

  string str = header(GetParam()) +
               nameOps("entry", "bad", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> bad;
  str += bad >> vector<Block>({t, entry});
  str += merge >> end;
  str += end;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              MatchesRegex("First block .\\[entry\\] of function .\\[Main\\] "
                           "is targeted by block .\\[bad\\]"));
}

TEST_P(ValidateCFG, SwitchTargetFirstBlockBad) {
  Block entry("entry");
  Block bad("bad", SpvOpSwitch);
  Block block1("block1");
  Block block2("block2");
  Block block3("block3");
  Block def("def");  // default block
  Block merge("merge");
  Block end("end", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  bad.SetBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("entry", "bad", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> bad;
  str += bad >> vector<Block>({def, block1, block2, block3, entry});
  str += def >> merge;
  str += block1 >> merge;
  str += block2 >> merge;
  str += block3 >> merge;
  str += merge >> end;
  str += end;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              MatchesRegex("First block .\\[entry\\] of function .\\[Main\\] "
                           "is targeted by block .\\[bad\\]"));
}

TEST_P(ValidateCFG, BranchToBlockInOtherFunctionBad) {
  Block entry("entry");
  Block middle("middle", SpvOpBranchConditional);
  Block end("end", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  middle.SetBody("OpSelectionMerge %end None\n");

  Block entry2("entry2");
  Block middle2("middle2");
  Block end2("end2", SpvOpReturn);

  string str = header(GetParam()) +
               nameOps("middle2", make_pair("func", "Main")) + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> middle;
  str += middle >> vector<Block>({end, middle2});
  str += end;
  str += "OpFunctionEnd\n";

  str += "%func2    = OpFunction %voidt None %funct\n";
  str += entry2 >> middle2;
  str += middle2 >> end2;
  str += end2;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      MatchesRegex("Block\\(s\\) \\{.\\[middle2\\] .\\} are referenced but not "
                   "defined in function .\\[Main\\]"));
}

TEST_P(ValidateCFG, HeaderDoesntDominatesMergeBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block head("head", SpvOpBranchConditional);
  Block f("f");
  Block merge("merge", SpvOpReturn);

  head.SetBody("%cond = OpSLessThan %boolt %one %two\n");

  if (is_shader) head.AppendBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("head", "merge", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> merge;
  str += head >> vector<Block>({merge, f});
  str += f >> merge;
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(
        getDiagnosticString(),
        MatchesRegex("The selection construct with the selection header "
                     ".\\[head\\] does not dominate the merge block "
                     ".\\[merge\\]"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, HeaderDoesntStrictlyDominateMergeBad) {
  // If a merge block is reachable, then it must be strictly dominated by
  // its header block.
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block head("head", SpvOpBranchConditional);
  Block exit("exit", SpvOpReturn);

  head.SetBody("%cond = OpSLessThan %boolt %one %two\n");

  if (is_shader) head.AppendBody("OpSelectionMerge %head None\n");

  string str = header(GetParam()) +
               nameOps("head", "exit", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += head >> vector<Block>({exit, exit});
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(
        getDiagnosticString(),
        MatchesRegex("The selection construct with the selection header "
                     ".\\[head\\] does not strictly dominate the merge block "
                     ".\\[head\\]"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions()) << str;
  }
}

TEST_P(ValidateCFG, UnreachableMerge) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block branch("branch", SpvOpBranchConditional);
  Block t("t", SpvOpReturn);
  Block f("f", SpvOpReturn);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) branch.AppendBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("branch", "merge", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> branch;
  str += branch >> vector<Block>({t, f});
  str += t;
  str += f;
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, UnreachableMergeDefinedByOpUnreachable) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block branch("branch", SpvOpBranchConditional);
  Block t("t", SpvOpReturn);
  Block f("f", SpvOpReturn);
  Block merge("merge", SpvOpUnreachable);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) branch.AppendBody("OpSelectionMerge %merge None\n");

  string str = header(GetParam()) +
               nameOps("branch", "merge", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> branch;
  str += branch >> vector<Block>({t, f});
  str += t;
  str += f;
  str += merge;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, UnreachableBlock) {
  Block entry("entry");
  Block unreachable("unreachable");
  Block exit("exit", SpvOpReturn);

  string str = header(GetParam()) +
               nameOps("unreachable", "exit", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> exit;
  str += unreachable >> exit;
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, UnreachableBranch) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block unreachable("unreachable", SpvOpBranchConditional);
  Block unreachablechildt("unreachablechildt");
  Block unreachablechildf("unreachablechildf");
  Block merge("merge");
  Block exit("exit", SpvOpReturn);

  unreachable.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) unreachable.AppendBody("OpSelectionMerge %merge None\n");
  string str = header(GetParam()) +
               nameOps("unreachable", "exit", make_pair("func", "Main")) +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> exit;
  str += unreachable >> vector<Block>({unreachablechildt, unreachablechildf});
  str += unreachablechildt >> merge;
  str += unreachablechildf >> merge;
  str += merge >> exit;
  str += exit;
  str += "OpFunctionEnd\n";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, EmptyFunction) {
  string str = header(GetParam()) + string(types_consts()) +
               R"(%func    = OpFunction %voidt None %funct
                  %l = OpLabel
                  OpReturn
                  OpFunctionEnd)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, SingleBlockLoop) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.AppendBody("OpLoopMerge %exit %loop None\n");

  string str = header(GetParam()) + string(types_consts()) +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({loop, exit});
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, NestedLoops) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop1("loop1");
  Block loop1_cont_break_block("loop1_cont_break_block",
                               SpvOpBranchConditional);
  Block loop2("loop2", SpvOpBranchConditional);
  Block loop2_merge("loop2_merge");
  Block loop1_merge("loop1_merge");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop1.SetBody("OpLoopMerge %loop1_merge %loop2 None\n");
    loop2.SetBody("OpLoopMerge %loop2_merge %loop2 None\n");
  }

  string str = header(GetParam()) + nameOps("loop2", "loop2_merge") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop1;
  str += loop1 >> loop1_cont_break_block;
  str += loop1_cont_break_block >> vector<Block>({loop1_merge, loop2});
  str += loop2 >> vector<Block>({loop2, loop2_merge});
  str += loop2_merge >> loop1;
  str += loop1_merge >> exit;
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, NestedSelection) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  const int N = 256;
  vector<Block> if_blocks;
  vector<Block> merge_blocks;
  Block inner("inner");

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");

  if_blocks.emplace_back("if0", SpvOpBranchConditional);

  if (is_shader) if_blocks[0].SetBody("OpSelectionMerge %if_merge0 None\n");
  merge_blocks.emplace_back("if_merge0", SpvOpReturn);

  for (int i = 1; i < N; i++) {
    stringstream ss;
    ss << i;
    if_blocks.emplace_back("if" + ss.str(), SpvOpBranchConditional);
    if (is_shader)
      if_blocks[i].SetBody("OpSelectionMerge %if_merge" + ss.str() + " None\n");
    merge_blocks.emplace_back("if_merge" + ss.str(), SpvOpBranch);
  }
  string str = header(GetParam()) + string(types_consts()) +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> if_blocks[0];
  for (int i = 0; i < N - 1; i++) {
    str += if_blocks[i] >> vector<Block>({if_blocks[i + 1], merge_blocks[i]});
  }
  str += if_blocks.back() >> vector<Block>({inner, merge_blocks.back()});
  str += inner >> merge_blocks.back();
  for (int i = N - 1; i > 0; i--) {
    str += merge_blocks[i] >> merge_blocks[i - 1];
  }
  str += merge_blocks[0];
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_P(ValidateCFG, BackEdgeBlockDoesntPostDominateContinueTargetBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop1("loop1", SpvOpBranchConditional);
  Block loop2("loop2", SpvOpBranchConditional);
  Block loop2_merge("loop2_merge", SpvOpBranchConditional);
  Block be_block("be_block");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop1.SetBody("OpLoopMerge %exit %loop2_merge None\n");
    loop2.SetBody("OpLoopMerge %loop2_merge %loop2 None\n");
  }

  string str = header(GetParam()) +
               nameOps("loop1", "loop2", "be_block", "loop2_merge") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop1;
  str += loop1 >> vector<Block>({loop2, exit});
  str += loop2 >> vector<Block>({loop2, loop2_merge});
  str += loop2_merge >> vector<Block>({be_block, exit});
  str += be_block >> loop1;
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (GetParam() == SpvCapabilityShader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("The continue construct with the continue target "
                             ".\\[loop2_merge\\] is not post dominated by the "
                             "back-edge block .\\[be_block\\]"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, BranchingToNonLoopHeaderBlockBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block split("split", SpvOpBranchConditional);
  Block t("t");
  Block f("f");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) split.SetBody("OpSelectionMerge %exit None\n");

  string str = header(GetParam()) + nameOps("split", "f") + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> split;
  str += split >> vector<Block>({t, f});
  str += t >> exit;
  str += f >> split;
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(
        getDiagnosticString(),
        MatchesRegex("Back-edges \\(.\\[f\\] -> .\\[split\\]\\) can only "
                     "be formed between a block and a loop header."));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, BranchingToSameNonLoopHeaderBlockBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block split("split", SpvOpBranchConditional);
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) split.SetBody("OpSelectionMerge %exit None\n");

  string str = header(GetParam()) + nameOps("split") + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> split;
  str += split >> vector<Block>({split, exit});
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex(
                    "Back-edges \\(.\\[split\\] -> .\\[split\\]\\) can only be "
                    "formed between a block and a loop header."));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, MultipleBackEdgeBlocksToLoopHeaderBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block back0("back0");
  Block back1("back1");
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody("OpLoopMerge %merge %back0 None\n");

  string str = header(GetParam()) + nameOps("loop", "back0", "back1") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({back0, back1});
  str += back0 >> loop;
  str += back1 >> loop;
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex(
                    "Loop header .\\[loop\\] is targeted by 2 back-edge blocks "
                    "but the standard requires exactly one"))
        << str;
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, ContinueTargetMustBePostDominatedByBackEdge) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block cheader("cheader", SpvOpBranchConditional);
  Block be_block("be_block");
  Block merge("merge", SpvOpReturn);
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody("OpLoopMerge %merge %cheader None\n");

  string str = header(GetParam()) + nameOps("cheader", "be_block") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({cheader, merge});
  str += cheader >> vector<Block>({exit, be_block});
  str += exit;  //  Branches out of a continue construct
  str += be_block >> loop;
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("The continue construct with the continue target "
                             ".\\[cheader\\] is not post dominated by the "
                             "back-edge block .\\[be_block\\]"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, BranchOutOfConstructToMergeBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block cont("cont", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody("OpLoopMerge %merge %loop None\n");

  string str = header(GetParam()) + nameOps("cont", "loop") + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({cont, merge});
  str += cont >> vector<Block>({loop, merge});
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("The continue construct with the continue target "
                             ".\\[loop\\] is not post dominated by the "
                             "back-edge block .\\[cont\\]"))
        << str;
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_P(ValidateCFG, BranchOutOfConstructBad) {
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block cont("cont", SpvOpBranchConditional);
  Block merge("merge");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) loop.SetBody("OpLoopMerge %merge %loop None\n");

  string str = header(GetParam()) + nameOps("cont", "loop") + types_consts() +
               "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({cont, merge});
  str += cont >> vector<Block>({loop, exit});
  str += merge >> exit;
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  if (is_shader) {
    ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
    EXPECT_THAT(getDiagnosticString(),
                MatchesRegex("The continue construct with the continue target "
                             ".\\[loop\\] is not post dominated by the "
                             "back-edge block .\\[cont\\]"));
  } else {
    ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
  }
}

TEST_F(ValidateCFG, OpSwitchToUnreachableBlock) {
  Block entry("entry", SpvOpSwitch);
  Block case0("case0");
  Block case1("case1");
  Block case2("case2");
  Block def("default", SpvOpUnreachable);
  Block phi("phi", SpvOpReturn);

  string str = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main" %id
OpExecutionMode %main LocalSize 1 1 1
OpSource GLSL 430
OpName %main "main"
OpDecorate %id BuiltIn GlobalInvocationId
%void      = OpTypeVoid
%voidf     = OpTypeFunction %void
%u32       = OpTypeInt 32 0
%f32       = OpTypeFloat 32
%uvec3     = OpTypeVector %u32 3
%fvec3     = OpTypeVector %f32 3
%uvec3ptr  = OpTypePointer Input %uvec3
%id        = OpVariable %uvec3ptr Input
%one       = OpConstant %u32 1
%three     = OpConstant %u32 3
%main      = OpFunction %void None %voidf
)";

  entry.SetBody(
      "%idval    = OpLoad %uvec3 %id\n"
      "%x        = OpCompositeExtract %u32 %idval 0\n"
      "%selector = OpUMod %u32 %x %three\n"
      "OpSelectionMerge %phi None\n");
  str += entry >> vector<Block>({def, case0, case1, case2});
  str += case1 >> phi;
  str += def;
  str += phi;
  str += case0 >> phi;
  str += case2 >> phi;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateCFG, LoopWithZeroBackEdgesBad) {
  string str = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpEntryPoint Fragment %main "main"
           OpName %loop "loop"
%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt
%main    = OpFunction %voidt None %funct
%loop    = OpLabel
           OpLoopMerge %exit %exit None
           OpBranch %exit
%exit    = OpLabel
           OpReturn
           OpFunctionEnd
)";
  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      MatchesRegex("Loop header .\\[loop\\] is targeted by "
                   "0 back-edge blocks but the standard requires exactly "
                   "one"));
}

TEST_F(ValidateCFG, LoopWithBackEdgeFromUnreachableContinueConstructGood) {
  string str = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpEntryPoint Fragment %main "main"
           OpName %loop "loop"
%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt
%floatt  = OpTypeFloat 32
%boolt   = OpTypeBool
%one     = OpConstant %floatt 1
%two     = OpConstant %floatt 2
%main    = OpFunction %voidt None %funct
%entry   = OpLabel
           OpBranch %loop
%loop    = OpLabel
           OpLoopMerge %exit %cont None
           OpBranch %16
%16      = OpLabel
%cond    = OpFOrdLessThan %boolt %one %two
           OpBranchConditional %cond %body %exit
%body    = OpLabel
           OpReturn
%cont    = OpLabel   ; Reachable only from OpLoopMerge ContinueTarget parameter
           OpBranch %loop ; Should be considered a back-edge
%exit    = OpLabel
           OpReturn
           OpFunctionEnd
)";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions()) << getDiagnosticString();
}

TEST_P(ValidateCFG,
       NestedConstructWithUnreachableMergeBlockBranchingToOuterMergeBlock) {
  // Test for https://github.com/KhronosGroup/SPIRV-Tools/issues/297
  // The nested construct has an unreachable merge block.  In the
  // augmented CFG that merge block
  // we still determine that the
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry", SpvOpBranchConditional);
  Block inner_head("inner_head", SpvOpBranchConditional);
  Block inner_true("inner_true", SpvOpReturn);
  Block inner_false("inner_false", SpvOpReturn);
  Block inner_merge("inner_merge");
  Block exit("exit", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    entry.AppendBody("OpSelectionMerge %exit None\n");
    inner_head.SetBody("OpSelectionMerge %inner_merge None\n");
  }

  string str = header(GetParam()) + nameOps("entry", "inner_merge", "exit") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> vector<Block>({inner_head, exit});
  str += inner_head >> vector<Block>({inner_true, inner_false});
  str += inner_true;
  str += inner_false;
  str += inner_merge >> exit;
  str += exit;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions()) << getDiagnosticString();
}

TEST_P(ValidateCFG, ContinueTargetCanBeMergeBlockForNestedStructureGood) {
  // This example is valid.  It shows that the validator can't just add
  // an edge from the loop head to the continue target.  If that edge
  // is added, then the "if_merge" block is both the continue target
  // for the loop and also the merge block for the nested selection, but
  // then it wouldn't be dominated by "if_head", the header block for the
  // nested selection.
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop");
  Block if_head("if_head", SpvOpBranchConditional);
  Block if_true("if_true");
  Block if_merge("if_merge", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop.SetBody("OpLoopMerge %merge %if_merge None\n");
    if_head.SetBody("OpSelectionMerge %if_merge None\n");
  }

  string str =
      header(GetParam()) +
      nameOps("entry", "loop", "if_head", "if_true", "if_merge", "merge") +
      types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> if_head;
  str += if_head >> vector<Block>({if_true, if_merge});
  str += if_true >> if_merge;
  str += if_merge >> vector<Block>({loop, merge});
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions()) << getDiagnosticString();
}

TEST_P(ValidateCFG, SingleLatchBlockMultipleBranchesToLoopHeader) {
  // This test case ensures we allow both branches of a loop latch block
  // to go back to the loop header.  It still counts as a single back edge.
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop", SpvOpBranchConditional);
  Block latch("latch", SpvOpBranchConditional);
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop.SetBody("OpLoopMerge %merge %latch None\n");
  }

  string str = header(GetParam()) + nameOps("entry", "loop", "latch", "merge") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> vector<Block>({latch, merge});
  str += latch >> vector<Block>({loop, loop});  // This is the key
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions())
      << str << getDiagnosticString();
}

TEST_P(ValidateCFG, SingleLatchBlockHeaderContinueTargetIsItselfGood) {
  // This test case ensures we don't count a Continue Target from a loop
  // header to itself as a self-loop when computing back edges.
  // Also, it detects that there is an edge from %latch to the pseudo-exit
  // node, rather than from %loop.  In particular, it detects that we
  // have used the *reverse* textual order of blocks when computing
  // predecessor traversal roots.
  bool is_shader = GetParam() == SpvCapabilityShader;
  Block entry("entry");
  Block loop("loop");
  Block latch("latch");
  Block merge("merge", SpvOpReturn);

  entry.SetBody("%cond    = OpSLessThan %boolt %one %two\n");
  if (is_shader) {
    loop.SetBody("OpLoopMerge %merge %loop None\n");
  }

  string str = header(GetParam()) + nameOps("entry", "loop", "latch", "merge") +
               types_consts() + "%func    = OpFunction %voidt None %funct\n";

  str += entry >> loop;
  str += loop >> latch;
  str += latch >> loop;
  str += merge;
  str += "OpFunctionEnd";

  CompileSuccessfully(str);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions())
      << str << getDiagnosticString();
}

// Unit test to check the case where a basic block is the entry block of 2
// different constructs. In this case, the basic block is the entry block of a
// continue construct as well as a selection construct. See issue# 517 for more
// details.
TEST_F(ValidateCFG, BasicBlockIsEntryBlockOfTwoConstructsGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
       %void = OpTypeVoid
       %bool = OpTypeBool
        %int = OpTypeInt 32 1
  %void_func = OpTypeFunction %void
      %int_0 = OpConstant %int 0
    %testfun = OpFunction %void None %void_func
    %label_1 = OpLabel
               OpBranch %start
      %start = OpLabel
       %cond = OpSLessThan %bool %int_0 %int_0
       ;
       ; Note: In this case, the "target" block is both the entry block of
       ;       the continue construct of the loop as well as the entry block of
       ;       the selection construct.
       ;
               OpLoopMerge %loop_merge %target None
               OpBranchConditional %cond %target %loop_merge
 %loop_merge = OpLabel
               OpReturn
     %target = OpLabel
               OpSelectionMerge %selection_merge None
               OpBranchConditional %cond %do_stuff %do_other_stuff
     %do_other_stuff = OpLabel
               OpBranch %selection_merge
     %selection_merge = OpLabel
               OpBranch %start
         %do_stuff = OpLabel
               OpBranch %selection_merge
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateCFG, OpReturnInNonVoidFunc) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
        %int = OpTypeInt 32 1
   %int_func = OpTypeFunction %int
    %testfun = OpFunction %int None %int_func
    %label_1 = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  ASSERT_EQ(SPV_ERROR_INVALID_CFG, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "OpReturn can only be called from a function with void return type"));
}

/// TODO(umar): Switch instructions
/// TODO(umar): Nested CFG constructs
}  // namespace

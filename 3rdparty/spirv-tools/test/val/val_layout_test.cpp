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

// Validation tests for Logical Layout

#include <functional>
#include <sstream>
#include <string>
#include <utility>

#include "gmock/gmock.h"
#include "source/diagnostic.h"
#include "unit_spirv.h"
#include "val_fixtures.h"

using std::function;
using std::ostream;
using std::ostream_iterator;
using std::pair;
using std::string;
using std::stringstream;
using std::tie;
using std::tuple;
using std::vector;

using libspirv::spvResultToString;
using ::testing::Eq;
using ::testing::HasSubstr;
using ::testing::StrEq;

using pred_type = function<spv_result_t(int)>;
using ValidateLayout =
    spvtest::ValidateBase<tuple<int, tuple<string, pred_type, pred_type>>>;

namespace {

// returns true if order is equal to VAL
template <int VAL, spv_result_t RET = SPV_ERROR_INVALID_LAYOUT>
spv_result_t Equals(int order) {
  return order == VAL ? SPV_SUCCESS : RET;
}

// returns true if order is between MIN and MAX(inclusive)
template <int MIN, int MAX, spv_result_t RET = SPV_ERROR_INVALID_LAYOUT>
struct Range {
  explicit Range(bool inverse = false) : inverse_(inverse) {}
  spv_result_t operator()(int order) {
    return (inverse_ ^ (order >= MIN && order <= MAX)) ? SPV_SUCCESS : RET;
  }

 private:
  bool inverse_;
};

template <typename... T>
spv_result_t InvalidSet(int order) {
  for (spv_result_t val : {T(true)(order)...})
    if (val != SPV_SUCCESS) return val;
  return SPV_SUCCESS;
}

// SPIRV source used to test the logical layout
const vector<string>& getInstructions() {
  // clang-format off
  static const vector<string> instructions = {
    "OpCapability Shader",
    "OpExtension \"TestExtension\"",
    "%inst = OpExtInstImport \"GLSL.std.450\"",
    "OpMemoryModel Logical GLSL450",
    "OpEntryPoint GLCompute %func \"\"",
    "OpExecutionMode %func LocalSize 1 1 1",
    "%str = OpString \"Test String\"",
    "%str2 = OpString \"blabla\"",
    "OpSource GLSL 450 %str \"uniform vec3 var = vec3(4.0);\"",
    "OpSourceContinued \"void main(){return;}\"",
    "OpSourceExtension \"Test extension\"",
    "OpName %func \"MyFunction\"",
    "OpMemberName %struct 1 \"my_member\"",
    "OpDecorate %dgrp RowMajor",
    "OpMemberDecorate %struct 1 RowMajor",
    "%dgrp   = OpDecorationGroup",
    "OpGroupDecorate %dgrp %mat33 %mat44",
    "%intt     = OpTypeInt 32 1",
    "%floatt   = OpTypeFloat 32",
    "%voidt    = OpTypeVoid",
    "%boolt    = OpTypeBool",
    "%vec4     = OpTypeVector %floatt 4",
    "%vec3     = OpTypeVector %floatt 3",
    "%mat33    = OpTypeMatrix %vec3 3",
    "%mat44    = OpTypeMatrix %vec4 4",
    "%struct   = OpTypeStruct %intt %mat33",
    "%vfunct   = OpTypeFunction %voidt",
    "%viifunct = OpTypeFunction %voidt %intt %intt",
    "%one      = OpConstant %intt 1",
    // TODO(umar): OpConstant fails because the type is not defined
    // TODO(umar): OpGroupMemberDecorate
    "OpLine %str 3 4",
    "OpNoLine",
    "%func     = OpFunction %voidt None %vfunct",
    "%l = OpLabel",
    "OpReturn ; %func return",
    "OpFunctionEnd ; %func end",
    "%func2    = OpFunction %voidt None %viifunct",
    "%funcp1   = OpFunctionParameter %intt",
    "%funcp2   = OpFunctionParameter %intt",
    "%fLabel   = OpLabel",
    "OpNop",
    "OpReturn ; %func2 return",
    "OpFunctionEnd"
  };
  return instructions;
}

static const int kRangeEnd = 1000;
pred_type All = Range<0, kRangeEnd>();

INSTANTIATE_TEST_CASE_P(InstructionsOrder,
    ValidateLayout,
    ::testing::Combine(::testing::Range((int)0, (int)getInstructions().size()),
    // Note: Because of ID dependencies between instructions, some instructions
    // are not free to be placed anywhere without triggering an non-layout
    // validation error. Therefore, "Lines to compile" for some instructions
    // are not "All" in the below.
    //
    //                                   | Instruction                | Line(s) valid          | Lines to compile
    ::testing::Values( make_tuple(string("OpCapability")              , Equals<0>              , Range<0, 2>())
                     , make_tuple(string("OpExtension")               , Equals<1>              , All)
                     , make_tuple(string("OpExtInstImport")           , Equals<2>              , All)
                     , make_tuple(string("OpMemoryModel")             , Equals<3>              , Range<1, kRangeEnd>())
                     , make_tuple(string("OpEntryPoint")              , Equals<4>              , All)
                     , make_tuple(string("OpExecutionMode")           , Equals<5>              , All)
                     , make_tuple(string("OpSource ")                 , Range<6, 10>()         , Range<7, kRangeEnd>())
                     , make_tuple(string("OpSourceContinued ")        , Range<6, 10>()         , All)
                     , make_tuple(string("OpSourceExtension ")        , Range<6, 10>()         , All)
                     , make_tuple(string("%str2 = OpString ")         , Range<6, 10>()         , All)
                     , make_tuple(string("OpName ")                   , Range<11, 12>()        , All)
                     , make_tuple(string("OpMemberName ")             , Range<11, 12>()        , All)
                     , make_tuple(string("OpDecorate ")               , Range<13, 16>()        , All)
                     , make_tuple(string("OpMemberDecorate ")         , Range<13, 16>()        , All)
                     , make_tuple(string("OpGroupDecorate ")          , Range<13, 16>()        , Range<16, kRangeEnd>())
                     , make_tuple(string("OpDecorationGroup")         , Range<13, 16>()        , Range<0, 15>())
                     , make_tuple(string("OpTypeBool")                , Range<17, 30>()        , All)
                     , make_tuple(string("OpTypeVoid")                , Range<17, 30>()        , Range<0, 25>())
                     , make_tuple(string("OpTypeFloat")               , Range<17, 30>()        , Range<0,20>())
                     , make_tuple(string("OpTypeInt")                 , Range<17, 30>()        , Range<0, 20>())
                     , make_tuple(string("OpTypeVector %floatt 4")    , Range<17, 30>()        , Range<19, 23>())
                     , make_tuple(string("OpTypeMatrix %vec4 4")      , Range<17, 30>()        , Range<22, kRangeEnd>())
                     , make_tuple(string("OpTypeStruct")              , Range<17, 30>()        , Range<24, kRangeEnd>())
                     , make_tuple(string("%vfunct   = OpTypeFunction"), Range<17, 30>()        , Range<20, 30>())
                     , make_tuple(string("OpConstant")                , Range<17, 30>()        , Range<20, kRangeEnd>())
                     , make_tuple(string("OpLine ")                   , Range<17, kRangeEnd>() , Range<7, kRangeEnd>())
                     , make_tuple(string("OpNoLine")                  , Range<17, kRangeEnd>() , All)
                     , make_tuple(string("%fLabel   = OpLabel")       , Equals<38>             , All)
                     , make_tuple(string("OpNop")                     , Equals<39>             , Range<39,kRangeEnd>())
                     , make_tuple(string("OpReturn ; %func2 return")  , Equals<40>             , All)
    )),);
// clang-format on

// Creates a new vector which removes the string if the substr is found in the
// instructions vector and reinserts it in the location specified by order.
// NOTE: This will not work correctly if there are two instances of substr in
// instructions
vector<string> GenerateCode(string substr, int order) {
  vector<string> code(getInstructions().size());
  vector<string> inst(1);
  partition_copy(begin(getInstructions()), end(getInstructions()), begin(code),
                 begin(inst), [=](const string& str) {
                   return string::npos == str.find(substr);
                 });

  code.insert(begin(code) + order, inst.front());
  return code;
}

// This test will check the logical layout of a binary by removing each
// instruction in the pair of the INSTANTIATE_TEST_CASE_P call and moving it in
// the SPIRV source formed by combining the vector "instructions".
TEST_P(ValidateLayout, Layout) {
  int order;
  string instruction;
  pred_type pred;
  pred_type test_pred;  // Predicate to determine if the test should be build
  tuple<string, pred_type, pred_type> testCase;

  tie(order, testCase) = GetParam();
  tie(instruction, pred, test_pred) = testCase;

  // Skip test which break the code generation
  if (test_pred(order)) return;

  vector<string> code = GenerateCode(instruction, order);

  stringstream ss;
  copy(begin(code), end(code), ostream_iterator<string>(ss, "\n"));

  // printf("code: \n%s\n", ss.str().c_str());
  CompileSuccessfully(ss.str());
  spv_result_t result;
  // clang-format off
  ASSERT_EQ(pred(order), result = ValidateInstructions())
    << "Actual: "        << spvResultToString(result)
    << "\nExpected: "    << spvResultToString(pred(order))
    << "\nOrder: "       << order
    << "\nInstruction: " << instruction
    << "\nCode: \n"      << ss.str();
  // clang-format on
}

TEST_F(ValidateLayout, MemoryModelMissing) {
  string str = R"(
    OpCapability Matrix
    OpExtension "TestExtension"
    %inst = OpExtInstImport "GLSL.std.450"
    OpEntryPoint GLCompute %func ""
    OpExecutionMode %func LocalSize 1 1 1
    )";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "EntryPoint cannot appear before the memory model instruction"));
}

TEST_F(ValidateLayout, FunctionDefinitionBeforeDeclarationBad) {
  char str[] = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpDecorate %var Restrict
%intt    = OpTypeInt 32 1
%voidt   = OpTypeVoid
%vfunct  = OpTypeFunction %voidt
%vifunct = OpTypeFunction %voidt %intt
%ptrt    = OpTypePointer Function %intt
%func    = OpFunction %voidt None %vfunct
%funcl   = OpLabel
           OpNop
           OpReturn
           OpFunctionEnd
%func2   = OpFunction %voidt None %vifunct ; must appear before definition
%func2p  = OpFunctionParameter %intt
           OpFunctionEnd
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Function declarations must appear before function definitions."));
}

// TODO(umar): Passes but gives incorrect error message. Should be fixed after
// type checking
TEST_F(ValidateLayout, LabelBeforeFunctionParameterBad) {
  char str[] = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpDecorate %var Restrict
%intt    = OpTypeInt 32 1
%voidt   = OpTypeVoid
%vfunct  = OpTypeFunction %voidt
%vifunct = OpTypeFunction %voidt %intt
%ptrt    = OpTypePointer Function %intt
%func    = OpFunction %voidt None %vifunct
%funcl   = OpLabel                    ; Label appears before function parameter
%func2p  = OpFunctionParameter %intt
           OpNop
           OpReturn
           OpFunctionEnd
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Function parameters must only appear immediately "
                        "after the function definition"));
}

TEST_F(ValidateLayout, FuncParameterNotImmediatlyAfterFuncBad) {
  char str[] = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpDecorate %var Restrict
%intt    = OpTypeInt 32 1
%voidt   = OpTypeVoid
%vfunct  = OpTypeFunction %voidt
%vifunct = OpTypeFunction %voidt %intt
%ptrt    = OpTypePointer Function %intt
%func    = OpFunction %voidt None %vifunct
%funcl   = OpLabel
           OpNop
           OpBranch %next
%func2p  = OpFunctionParameter %intt        ;FunctionParameter appears in a function but not immediately afterwards
%next    = OpLabel
           OpNop
           OpReturn
           OpFunctionEnd
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Function parameters must only appear immediately "
                        "after the function definition"));
}

TEST_F(ValidateLayout, OpUndefCanAppearInTypeDeclarationSection) {
  string str = R"(
         OpCapability Kernel
         OpCapability Linkage
         OpMemoryModel Logical OpenCL
%voidt = OpTypeVoid
%uintt = OpTypeInt 32 0
%funct = OpTypeFunction %voidt
%udef  = OpUndef %uintt
%func  = OpFunction %voidt None %funct
%entry = OpLabel
         OpReturn
         OpFunctionEnd
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateLayout, OpUndefCanAppearInBlock) {
  string str = R"(
         OpCapability Kernel
         OpCapability Linkage
         OpMemoryModel Logical OpenCL
%voidt = OpTypeVoid
%uintt = OpTypeInt 32 0
%funct = OpTypeFunction %voidt
%func  = OpFunction %voidt None %funct
%entry = OpLabel
%udef  = OpUndef %uintt
         OpReturn
         OpFunctionEnd
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateLayout, MissingFunctionEndForFunctionWithBody) {
  const auto s = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%void = OpTypeVoid
%tf = OpTypeFunction %void
%f = OpFunction %void None %tf
%l = OpLabel
OpReturn
)";

  CompileSuccessfully(s);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              StrEq("Missing OpFunctionEnd at end of module."));
}

TEST_F(ValidateLayout, MissingFunctionEndForFunctionPrototype) {
  const auto s = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%void = OpTypeVoid
%tf = OpTypeFunction %void
%f = OpFunction %void None %tf
)";

  CompileSuccessfully(s);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              StrEq("Missing OpFunctionEnd at end of module."));
}

using ValidateOpFunctionParameter = spvtest::ValidateBase<int>;

TEST_F(ValidateOpFunctionParameter, OpLineBetweenParameters) {
  const auto s = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%foo_frag = OpString "foo.frag"
%i32 = OpTypeInt 32 1
%tf = OpTypeFunction %i32 %i32 %i32
%c = OpConstant %i32 123
%f = OpFunction %i32 None %tf
OpLine %foo_frag 1 1
%p1 = OpFunctionParameter %i32
OpNoLine
%p2 = OpFunctionParameter %i32
%l = OpLabel
OpReturnValue %c
OpFunctionEnd
)";
  CompileSuccessfully(s);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateOpFunctionParameter, TooManyParameters) {
  const auto s = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%i32 = OpTypeInt 32 1
%tf = OpTypeFunction %i32 %i32 %i32
%c = OpConstant %i32 123
%f = OpFunction %i32 None %tf
%p1 = OpFunctionParameter %i32
%p2 = OpFunctionParameter %i32
%xp3 = OpFunctionParameter %i32
%xp4 = OpFunctionParameter %i32
%xp5 = OpFunctionParameter %i32
%xp6 = OpFunctionParameter %i32
%xp7 = OpFunctionParameter %i32
%l = OpLabel
OpReturnValue %c
OpFunctionEnd
)";
  CompileSuccessfully(s);
  ASSERT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
}

using ValidateEntryPoint = spvtest::ValidateBase<bool>;

// Tests that not having OpEntryPoint causes an error.
TEST_F(ValidateEntryPoint, NoEntryPointBad) {
  std::string spirv = R"(
      OpCapability Shader
      OpMemoryModel Logical GLSL450)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("No OpEntryPoint instruction was found. This is only "
                        "allowed if the Linkage capability is being used."));
}

// Invalid. A function may not be a target of both OpEntryPoint and
// OpFunctionCall.
TEST_F(ValidateEntryPoint, FunctionIsTargetOfEntryPointAndFunctionCallBad) {
  std::string spirv = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpEntryPoint Fragment %foo "foo"
%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt
%foo     = OpFunction %voidt None %funct
%entry   = OpLabel
%recurse = OpFunctionCall %voidt %foo
           OpReturn
           OpFunctionEnd
      )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("A function (1) may not be targeted by both an OpEntryPoint "
                "instruction and an OpFunctionCall instruction."));
}

// Valid. Module with a function but no entry point is valid when Linkage
// Capability is used.
TEST_F(ValidateEntryPoint, NoEntryPointWithLinkageCapGood) {
  std::string spirv = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450
%voidt   = OpTypeVoid
%funct   = OpTypeFunction %voidt
%foo     = OpFunction %voidt None %funct
%entry   = OpLabel
           OpReturn
           OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateLayout, ModuleProcessedInvalidIn10) {
  char str[] = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450
           OpName %void "void"
           OpModuleProcessed "this is ok in 1.1 and later"
           OpDecorate %void Volatile ; bogus, but makes the example short
%void    = OpTypeVoid
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_ERROR_WRONG_VERSION,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_0));
  // In a 1.0 environment the version check fails.
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Invalid SPIR-V binary version 1.1 for target "
                        "environment SPIR-V 1.0."));
}

TEST_F(ValidateLayout, ModuleProcessedValidIn11) {
  char str[] = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450
           OpName %void "void"
           OpModuleProcessed "this is ok in 1.1 and later"
           OpDecorate %void Volatile ; bogus, but makes the example short
%void    = OpTypeVoid
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_1));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateLayout, ModuleProcessedBeforeLastNameIsTooEarly) {
  char str[] = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450
           OpModuleProcessed "this is too early"
           OpName %void "void"
%void    = OpTypeVoid
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_1));
  // By the mechanics of the validator, we assume ModuleProcessed is in the
  // right spot, but then that OpName is in the wrong spot.
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Name cannot appear in a function declaration"));
}

TEST_F(ValidateLayout, ModuleProcessedInvalidAfterFirstAnnotation) {
  char str[] = R"(
           OpCapability Shader
           OpCapability Linkage
           OpMemoryModel Logical GLSL450
           OpDecorate %void Volatile ; this is bogus, but keeps the example short
           OpModuleProcessed "this is too late"
%void    = OpTypeVoid
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("ModuleProcessed cannot appear in a function declaration"));
}

TEST_F(ValidateLayout, ModuleProcessedInvalidInFunctionBeforeLabel) {
  char str[] = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpEntryPoint GLCompute %main "main"
%void    = OpTypeVoid
%voidfn  = OpTypeFunction %void
%main    = OpFunction %void None %voidfn
           OpModuleProcessed "this is too late, in function before label"
%entry  =  OpLabel
           OpReturn
           OpFunctionEnd
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("ModuleProcessed cannot appear in a function declaration"));
}

TEST_F(ValidateLayout, ModuleProcessedInvalidInBasicBlock) {
  char str[] = R"(
           OpCapability Shader
           OpMemoryModel Logical GLSL450
           OpEntryPoint GLCompute %main "main"
%void    = OpTypeVoid
%voidfn  = OpTypeFunction %void
%main    = OpFunction %void None %voidfn
%entry   = OpLabel
           OpModuleProcessed "this is too late, in basic block"
           OpReturn
           OpFunctionEnd
)";

  CompileSuccessfully(str, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_LAYOUT,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("ModuleProcessed cannot appear in a function declaration"));
}

// TODO(umar): Test optional instructions
}  // namespace

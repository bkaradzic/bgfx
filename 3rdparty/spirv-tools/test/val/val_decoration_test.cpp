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

// Validation tests for decorations

#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "source/val/decoration.h"
#include "test/unit_spirv.h"
#include "test/val/val_fixtures.h"

namespace spvtools {
namespace val {
namespace {

using ::testing::Eq;
using ::testing::HasSubstr;

using ValidateDecorations = spvtest::ValidateBase<bool>;

TEST_F(ValidateDecorations, ValidateOpDecorateRegistration) {
  std::string spirv = R"(
    OpCapability Shader
    OpCapability Linkage
    OpMemoryModel Logical GLSL450
    OpDecorate %1 ArrayStride 4
    OpDecorate %1 RelaxedPrecision
    %2 = OpTypeFloat 32
    %1 = OpTypeRuntimeArray %2
    ; Since %1 is used first in Decoration, it gets id 1.
)";
  const uint32_t id = 1;
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
  // Must have 2 decorations.
  EXPECT_THAT(
      vstate_->id_decorations(id),
      Eq(std::vector<Decoration>{Decoration(SpvDecorationArrayStride, {4}),
                                 Decoration(SpvDecorationRelaxedPrecision)}));
}

TEST_F(ValidateDecorations, ValidateOpMemberDecorateRegistration) {
  std::string spirv = R"(
    OpCapability Shader
    OpCapability Linkage
    OpMemoryModel Logical GLSL450
    OpDecorate %_arr_double_uint_6 ArrayStride 4
    OpMemberDecorate %_struct_115 2 NonReadable
    OpMemberDecorate %_struct_115 2 Offset 2
    OpDecorate %_struct_115 BufferBlock
    %float = OpTypeFloat 32
    %uint = OpTypeInt 32 0
    %uint_6 = OpConstant %uint 6
    %_arr_double_uint_6 = OpTypeArray %float %uint_6
    %_struct_115 = OpTypeStruct %float %float %_arr_double_uint_6
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());

  // The array must have 1 decoration.
  const uint32_t arr_id = 1;
  EXPECT_THAT(
      vstate_->id_decorations(arr_id),
      Eq(std::vector<Decoration>{Decoration(SpvDecorationArrayStride, {4})}));

  // The struct must have 3 decorations.
  const uint32_t struct_id = 2;
  EXPECT_THAT(
      vstate_->id_decorations(struct_id),
      Eq(std::vector<Decoration>{Decoration(SpvDecorationNonReadable, {}, 2),
                                 Decoration(SpvDecorationOffset, {2}, 2),
                                 Decoration(SpvDecorationBufferBlock)}));
}

TEST_F(ValidateDecorations, ValidateOpMemberDecorateOutOfBound) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "Main"
               OpExecutionMode %1 OriginUpperLeft
               OpMemberDecorate %_struct_2 1 RelaxedPrecision
       %void = OpTypeVoid
          %4 = OpTypeFunction %void
      %float = OpTypeFloat 32
  %_struct_2 = OpTypeStruct %float
          %1 = OpFunction %void None %4
          %6 = OpLabel
               OpReturn
               OpFunctionEnd
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Index 1 provided in OpMemberDecorate for struct <id> "
                        "2[%_struct_2] is out of bounds. The structure has 1 "
                        "members. Largest valid index is 0."));
}

TEST_F(ValidateDecorations, ValidateGroupDecorateRegistration) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %1 DescriptorSet 0
               OpDecorate %1 NonWritable
               OpDecorate %1 Restrict
          %1 = OpDecorationGroup
               OpGroupDecorate %1 %2 %3
               OpGroupDecorate %1 %4
  %float = OpTypeFloat 32
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_9 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_9 = OpTypePointer Uniform %_struct_9
         %2 = OpVariable %_ptr_Uniform__struct_9 Uniform
 %_struct_10 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_10 = OpTypePointer Uniform %_struct_10
         %3 = OpVariable %_ptr_Uniform__struct_10 Uniform
 %_struct_11 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_11 = OpTypePointer Uniform %_struct_11
         %4 = OpVariable %_ptr_Uniform__struct_11 Uniform
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());

  // Decoration group has 3 decorations.
  auto expected_decorations = std::vector<Decoration>{
      Decoration(SpvDecorationDescriptorSet, {0}),
      Decoration(SpvDecorationNonWritable), Decoration(SpvDecorationRestrict)};

  // Decoration group is applied to id 1, 2, 3, and 4. Note that id 1 (which is
  // the decoration group id) also has all the decorations.
  EXPECT_THAT(vstate_->id_decorations(1), Eq(expected_decorations));
  EXPECT_THAT(vstate_->id_decorations(2), Eq(expected_decorations));
  EXPECT_THAT(vstate_->id_decorations(3), Eq(expected_decorations));
  EXPECT_THAT(vstate_->id_decorations(4), Eq(expected_decorations));
}

TEST_F(ValidateDecorations, WebGPUOpDecorationGroupBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability VulkanMemoryModelKHR
               OpExtension "SPV_KHR_vulkan_memory_model"
               OpMemoryModel Logical VulkanKHR
               OpDecorate %1 DescriptorSet 0
               OpDecorate %1 NonWritable
               OpDecorate %1 Restrict
          %1 = OpDecorationGroup
               OpGroupDecorate %1 %2 %3
               OpGroupDecorate %1 %4
  %float = OpTypeFloat 32
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_9 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_9 = OpTypePointer Uniform %_struct_9
         %2 = OpVariable %_ptr_Uniform__struct_9 Uniform
 %_struct_10 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_10 = OpTypePointer Uniform %_struct_10
         %3 = OpVariable %_ptr_Uniform__struct_10 Uniform
 %_struct_11 = OpTypeStruct %_runtimearr_float
%_ptr_Uniform__struct_11 = OpTypePointer Uniform %_struct_11
         %4 = OpVariable %_ptr_Uniform__struct_11 Uniform
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateInstructions(SPV_ENV_WEBGPU_0));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("OpDecorationGroup is not allowed in the WebGPU "
                        "execution environment.\n  %1 = OpDecorationGroup\n"));
}

// For WebGPU, OpGroupDecorate does not have a test case, because it requires
// being preceded by OpDecorationGroup, which will cause a validation error.

// For WebGPU, OpGroupMemberDecorate does not have a test case, because it
// requires being preceded by OpDecorationGroup, which will cause a validation
// error.

TEST_F(ValidateDecorations, ValidateGroupMemberDecorateRegistration) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %1 Offset 3
          %1 = OpDecorationGroup
               OpGroupMemberDecorate %1 %_struct_1 3 %_struct_2 3 %_struct_3 3
      %float = OpTypeFloat 32
%_runtimearr = OpTypeRuntimeArray %float
  %_struct_1 = OpTypeStruct %float %float %float %_runtimearr
  %_struct_2 = OpTypeStruct %float %float %float %_runtimearr
  %_struct_3 = OpTypeStruct %float %float %float %_runtimearr
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
  // Decoration group has 1 decoration.
  auto expected_decorations =
      std::vector<Decoration>{Decoration(SpvDecorationOffset, {3}, 3)};

  // Decoration group is applied to id 2, 3, and 4.
  EXPECT_THAT(vstate_->id_decorations(2), Eq(expected_decorations));
  EXPECT_THAT(vstate_->id_decorations(3), Eq(expected_decorations));
  EXPECT_THAT(vstate_->id_decorations(4), Eq(expected_decorations));
}

TEST_F(ValidateDecorations, LinkageImportUsedForInitializedVariableBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %target LinkageAttributes "link_ptr" Import
      %float = OpTypeFloat 32
 %_ptr_float = OpTypePointer Uniform %float
       %zero = OpConstantNull %float
     %target = OpVariable %_ptr_float Uniform %zero
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("A module-scope OpVariable with initialization value "
                        "cannot be marked with the Import Linkage Type."));
}
TEST_F(ValidateDecorations, LinkageExportUsedForInitializedVariableGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %target LinkageAttributes "link_ptr" Export
      %float = OpTypeFloat 32
 %_ptr_float = OpTypePointer Uniform %float
       %zero = OpConstantNull %float
     %target = OpVariable %_ptr_float Uniform %zero
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, StructAllMembersHaveBuiltInDecorationsGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpMemberDecorate %_struct_1 0 BuiltIn Position
               OpMemberDecorate %_struct_1 1 BuiltIn Position
               OpMemberDecorate %_struct_1 2 BuiltIn Position
               OpMemberDecorate %_struct_1 3 BuiltIn Position
      %float = OpTypeFloat 32
%_runtimearr = OpTypeRuntimeArray %float
  %_struct_1 = OpTypeStruct %float %float %float %_runtimearr
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, MixedBuiltInDecorationsBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpMemberDecorate %_struct_1 0 BuiltIn Position
               OpMemberDecorate %_struct_1 1 BuiltIn Position
      %float = OpTypeFloat 32
%_runtimearr = OpTypeRuntimeArray %float
  %_struct_1 = OpTypeStruct %float %float %float %_runtimearr
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("When BuiltIn decoration is applied to a structure-type "
                "member, all members of that structure type must also be "
                "decorated with BuiltIn (No allowed mixing of built-in "
                "variables and non-built-in variables within a single "
                "structure). Structure id 1 does not meet this requirement."));
}

TEST_F(ValidateDecorations, StructContainsBuiltInStructBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpMemberDecorate %_struct_1 0 BuiltIn Position
               OpMemberDecorate %_struct_1 1 BuiltIn Position
               OpMemberDecorate %_struct_1 2 BuiltIn Position
               OpMemberDecorate %_struct_1 3 BuiltIn Position
      %float = OpTypeFloat 32
%_runtimearr = OpTypeRuntimeArray %float
  %_struct_1 = OpTypeStruct %float %float %float %_runtimearr
  %_struct_2 = OpTypeStruct %_struct_1
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Structure <id> 1[%_struct_1] contains members with "
                        "BuiltIn decoration. Therefore this structure may not "
                        "be contained as a member of another structure type. "
                        "Structure <id> 4[%_struct_4] contains structure <id> "
                        "1[%_struct_1]."));
}

TEST_F(ValidateDecorations, StructContainsNonBuiltInStructGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
      %float = OpTypeFloat 32
  %_struct_1 = OpTypeStruct %float
  %_struct_2 = OpTypeStruct %_struct_1
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, MultipleBuiltInObjectsConsumedByOpEntryPointBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Geometry
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main" %in_1 %in_2
               OpExecutionMode %main InputPoints
               OpExecutionMode %main OutputPoints
               OpMemberDecorate %struct_1 0 BuiltIn InvocationId
               OpMemberDecorate %struct_2 0 BuiltIn Position
      %int = OpTypeInt 32 1
     %void = OpTypeVoid
     %func = OpTypeFunction %void
    %float = OpTypeFloat 32
 %struct_1 = OpTypeStruct %int
 %struct_2 = OpTypeStruct %float
%ptr_builtin_1 = OpTypePointer Input %struct_1
%ptr_builtin_2 = OpTypePointer Input %struct_2
%in_1 = OpVariable %ptr_builtin_1 Input
%in_2 = OpVariable %ptr_builtin_2 Input
       %main = OpFunction %void None %func
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("There must be at most one object per Storage Class "
                        "that can contain a structure type containing members "
                        "decorated with BuiltIn, consumed per entry-point."));
}

TEST_F(ValidateDecorations,
       OneBuiltInObjectPerStorageClassConsumedByOpEntryPointGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Geometry
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main" %in_1 %out_1
               OpExecutionMode %main InputPoints
               OpExecutionMode %main OutputPoints
               OpMemberDecorate %struct_1 0 BuiltIn InvocationId
               OpMemberDecorate %struct_2 0 BuiltIn Position
      %int = OpTypeInt 32 1
     %void = OpTypeVoid
     %func = OpTypeFunction %void
    %float = OpTypeFloat 32
 %struct_1 = OpTypeStruct %int
 %struct_2 = OpTypeStruct %float
%ptr_builtin_1 = OpTypePointer Input %struct_1
%ptr_builtin_2 = OpTypePointer Output %struct_2
%in_1 = OpVariable %ptr_builtin_1 Input
%out_1 = OpVariable %ptr_builtin_2 Output
       %main = OpFunction %void None %func
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, NoBuiltInObjectsConsumedByOpEntryPointGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Geometry
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main" %in_1 %out_1
               OpExecutionMode %main InputPoints
               OpExecutionMode %main OutputPoints
      %int = OpTypeInt 32 1
     %void = OpTypeVoid
     %func = OpTypeFunction %void
    %float = OpTypeFloat 32
 %struct_1 = OpTypeStruct %int
 %struct_2 = OpTypeStruct %float
%ptr_builtin_1 = OpTypePointer Input %struct_1
%ptr_builtin_2 = OpTypePointer Output %struct_2
%in_1 = OpVariable %ptr_builtin_1 Input
%out_1 = OpVariable %ptr_builtin_2 Output
       %main = OpFunction %void None %func
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, EntryPointFunctionHasLinkageAttributeBad) {
  std::string spirv = R"(
      OpCapability Shader
      OpCapability Linkage
      OpMemoryModel Logical GLSL450
      OpEntryPoint GLCompute %main "main"
      OpDecorate %main LinkageAttributes "import_main" Import
%1 = OpTypeVoid
%2 = OpTypeFunction %1
%main = OpFunction %1 None %2
%4 = OpLabel
     OpReturn
     OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("The LinkageAttributes Decoration (Linkage name: import_main) "
                "cannot be applied to function id 1 because it is targeted by "
                "an OpEntryPoint instruction."));
}

TEST_F(ValidateDecorations, FunctionDeclarationWithoutImportLinkageBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
     %void = OpTypeVoid
     %func = OpTypeFunction %void
       %main = OpFunction %void None %func
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Function declaration (id 3) must have a LinkageAttributes "
                "decoration with the Import Linkage type."));
}

TEST_F(ValidateDecorations, FunctionDeclarationWithImportLinkageGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %main LinkageAttributes "link_fn" Import
     %void = OpTypeVoid
     %func = OpTypeFunction %void
       %main = OpFunction %void None %func
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FunctionDeclarationWithExportLinkageBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %main LinkageAttributes "link_fn" Export
     %void = OpTypeVoid
     %func = OpTypeFunction %void
       %main = OpFunction %void None %func
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Function declaration (id 1) must have a LinkageAttributes "
                "decoration with the Import Linkage type."));
}

TEST_F(ValidateDecorations, FunctionDefinitionWithImportLinkageBad) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
               OpDecorate %main LinkageAttributes "link_fn" Import
     %void = OpTypeVoid
     %func = OpTypeFunction %void
       %main = OpFunction %void None %func
      %label = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Function definition (id 1) may not be decorated with "
                        "Import Linkage type."));
}

TEST_F(ValidateDecorations, FunctionDefinitionWithoutImportLinkageGood) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Linkage
               OpMemoryModel Logical GLSL450
     %void = OpTypeVoid
     %func = OpTypeFunction %void
       %main = OpFunction %void None %func
      %label = OpLabel
               OpReturn
               OpFunctionEnd
  )";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, BuiltinVariablesGoodVulkan) {
  const spv_target_env env = SPV_ENV_VULKAN_1_0;
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %main "main" %gl_FragCoord %_entryPointOutput
OpExecutionMode %main OriginUpperLeft
OpSource HLSL 500
OpDecorate %gl_FragCoord BuiltIn FragCoord
OpDecorate %_entryPointOutput Location 0
%void = OpTypeVoid
%3 = OpTypeFunction %void
%float = OpTypeFloat 32
%v4float = OpTypeVector %float 4
%float_0 = OpConstant %float 0
%14 = OpConstantComposite %v4float %float_0 %float_0 %float_0 %float_0
%_ptr_Input_v4float = OpTypePointer Input %v4float
%gl_FragCoord = OpVariable %_ptr_Input_v4float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
%_entryPointOutput = OpVariable %_ptr_Output_v4float Output
%main = OpFunction %void None %3
%5 = OpLabel
OpStore %_entryPointOutput %14
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, env);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState(env));
}

TEST_F(ValidateDecorations, BuiltinVariablesWithLocationDecorationVulkan) {
  const spv_target_env env = SPV_ENV_VULKAN_1_0;
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %main "main" %gl_FragCoord %_entryPointOutput
OpExecutionMode %main OriginUpperLeft
OpSource HLSL 500
OpDecorate %gl_FragCoord BuiltIn FragCoord
OpDecorate %gl_FragCoord Location 0
OpDecorate %_entryPointOutput Location 0
%void = OpTypeVoid
%3 = OpTypeFunction %void
%float = OpTypeFloat 32
%v4float = OpTypeVector %float 4
%float_0 = OpConstant %float 0
%14 = OpConstantComposite %v4float %float_0 %float_0 %float_0 %float_0
%_ptr_Input_v4float = OpTypePointer Input %v4float
%gl_FragCoord = OpVariable %_ptr_Input_v4float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
%_entryPointOutput = OpVariable %_ptr_Output_v4float Output
%main = OpFunction %void None %3
%5 = OpLabel
OpStore %_entryPointOutput %14
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, env);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState(env));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("A BuiltIn variable (id 2) cannot have any Location or "
                        "Component decorations"));
}
TEST_F(ValidateDecorations, BuiltinVariablesWithComponentDecorationVulkan) {
  const spv_target_env env = SPV_ENV_VULKAN_1_0;
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %main "main" %gl_FragCoord %_entryPointOutput
OpExecutionMode %main OriginUpperLeft
OpSource HLSL 500
OpDecorate %gl_FragCoord BuiltIn FragCoord
OpDecorate %gl_FragCoord Component 0
OpDecorate %_entryPointOutput Location 0
%void = OpTypeVoid
%3 = OpTypeFunction %void
%float = OpTypeFloat 32
%v4float = OpTypeVector %float 4
%float_0 = OpConstant %float 0
%14 = OpConstantComposite %v4float %float_0 %float_0 %float_0 %float_0
%_ptr_Input_v4float = OpTypePointer Input %v4float
%gl_FragCoord = OpVariable %_ptr_Input_v4float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
%_entryPointOutput = OpVariable %_ptr_Output_v4float Output
%main = OpFunction %void None %3
%5 = OpLabel
OpStore %_entryPointOutput %14
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, env);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState(env));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("A BuiltIn variable (id 2) cannot have any Location or "
                        "Component decorations"));
}

// #version 440
// #extension GL_EXT_nonuniform_qualifier : enable
// layout(binding = 1) uniform sampler2D s2d[];
// layout(location = 0) in nonuniformEXT int i;
// void main()
// {
//     vec4 v = texture(s2d[i], vec2(0.3));
// }
TEST_F(ValidateDecorations, RuntimeArrayOfDescriptorSetsIsAllowed) {
  const spv_target_env env = SPV_ENV_VULKAN_1_0;
  std::string spirv = R"(
               OpCapability Shader
               OpCapability ShaderNonUniformEXT
               OpCapability RuntimeDescriptorArrayEXT
               OpCapability SampledImageArrayNonUniformIndexingEXT
               OpExtension "SPV_EXT_descriptor_indexing"
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main" %i
               OpSource GLSL 440
               OpSourceExtension "GL_EXT_nonuniform_qualifier"
               OpName %main "main"
               OpName %v "v"
               OpName %s2d "s2d"
               OpName %i "i"
               OpDecorate %s2d DescriptorSet 0
               OpDecorate %s2d Binding 1
               OpDecorate %i Location 0
               OpDecorate %i NonUniformEXT
               OpDecorate %18 NonUniformEXT
               OpDecorate %21 NonUniformEXT
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
%_ptr_Function_v4float = OpTypePointer Function %v4float
         %10 = OpTypeImage %float 2D 0 0 0 1 Unknown
         %11 = OpTypeSampledImage %10
%_runtimearr_11 = OpTypeRuntimeArray %11
%_ptr_Uniform__runtimearr_11 = OpTypePointer Uniform %_runtimearr_11
        %s2d = OpVariable %_ptr_Uniform__runtimearr_11 Uniform
        %int = OpTypeInt 32 1
%_ptr_Input_int = OpTypePointer Input %int
          %i = OpVariable %_ptr_Input_int Input
%_ptr_Uniform_11 = OpTypePointer Uniform %11
    %v2float = OpTypeVector %float 2
%float_0_300000012 = OpConstant %float 0.300000012
         %24 = OpConstantComposite %v2float %float_0_300000012 %float_0_300000012
    %float_0 = OpConstant %float 0
       %main = OpFunction %void None %3
          %5 = OpLabel
          %v = OpVariable %_ptr_Function_v4float Function
         %18 = OpLoad %int %i
         %20 = OpAccessChain %_ptr_Uniform_11 %s2d %18
         %21 = OpLoad %11 %20
         %26 = OpImageSampleExplicitLod %v4float %21 %24 Lod %float_0
               OpStore %v %26
               OpReturn
               OpFunctionEnd
)";
  CompileSuccessfully(spirv, env);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, BlockMissingOffsetBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must be explicitly laid out with Offset decorations"));
}

TEST_F(ValidateDecorations, BufferBlockMissingOffsetBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must be explicitly laid out with Offset decorations"));
}

TEST_F(ValidateDecorations, BlockNestedStructMissingOffsetBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %v3float %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must be explicitly laid out with Offset decorations"));
}

TEST_F(ValidateDecorations, BufferBlockNestedStructMissingOffsetBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %v3float %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must be explicitly laid out with Offset decorations"));
}

TEST_F(ValidateDecorations, BlockGLSLSharedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
               OpDecorate %Output GLSLShared
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLShared decoration"));
}

TEST_F(ValidateDecorations, BufferBlockGLSLSharedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
               OpDecorate %Output GLSLShared
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLShared decoration"));
}

TEST_F(ValidateDecorations, BlockNestedStructGLSLSharedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpDecorate %S GLSLShared
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLShared decoration"));
}

TEST_F(ValidateDecorations, BufferBlockNestedStructGLSLSharedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpDecorate %S GLSLShared
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLShared decoration"));
}

TEST_F(ValidateDecorations, BlockGLSLPackedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
               OpDecorate %Output GLSLPacked
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLPacked decoration"));
}

TEST_F(ValidateDecorations, BufferBlockGLSLPackedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
               OpDecorate %Output GLSLPacked
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %Output = OpTypeStruct %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLPacked decoration"));
}

TEST_F(ValidateDecorations, BlockNestedStructGLSLPackedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpDecorate %S GLSLPacked
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLPacked decoration"));
}

TEST_F(ValidateDecorations, BufferBlockNestedStructGLSLPackedBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpDecorate %S GLSLPacked
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
          %S = OpTypeStruct %int
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("must not use GLSLPacked decoration"));
}

TEST_F(ValidateDecorations, BlockMissingArrayStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %float %int_3
     %Output = OpTypeStruct %array
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with ArrayStride decorations"));
}

TEST_F(ValidateDecorations, BufferBlockMissingArrayStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %float %int_3
     %Output = OpTypeStruct %array
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with ArrayStride decorations"));
}

TEST_F(ValidateDecorations, BlockNestedStructMissingArrayStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %float %int_3
          %S = OpTypeStruct %array
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with ArrayStride decorations"));
}

TEST_F(ValidateDecorations, BufferBlockNestedStructMissingArrayStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %float %int_3
          %S = OpTypeStruct %array
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with ArrayStride decorations"));
}

TEST_F(ValidateDecorations, BlockMissingMatrixStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
     %matrix = OpTypeMatrix %v3float 4
     %Output = OpTypeStruct %matrix
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BufferBlockMissingMatrixStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
     %matrix = OpTypeMatrix %v3float 4
     %Output = OpTypeStruct %matrix
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BlockMissingMatrixStrideArrayBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output Block
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
     %matrix = OpTypeMatrix %v3float 4
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %matrix %int_3
     %Output = OpTypeStruct %matrix
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BufferBlockMissingMatrixStrideArrayBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %Output BufferBlock
               OpMemberDecorate %Output 0 Offset 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
     %matrix = OpTypeMatrix %v3float 4
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
      %array = OpTypeArray %matrix %int_3
     %Output = OpTypeStruct %matrix
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BlockNestedStructMissingMatrixStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
    %v4float = OpTypeVector %float 4
     %matrix = OpTypeMatrix %v3float 4
          %S = OpTypeStruct %matrix
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BufferBlockNestedStructMissingMatrixStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 16
               OpMemberDecorate %Output 2 Offset 32
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
    %v4float = OpTypeVector %float 4
     %matrix = OpTypeMatrix %v3float 4
          %S = OpTypeStruct %matrix
     %Output = OpTypeStruct %float %v4float %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("must be explicitly laid out with MatrixStride decorations"));
}

TEST_F(ValidateDecorations, BlockStandardUniformBufferLayout) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %F 0 Offset 0
               OpMemberDecorate %F 1 Offset 8
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %_arr_mat3v3float_uint_2 ArrayStride 48
               OpMemberDecorate %O 0 Offset 0
               OpMemberDecorate %O 1 Offset 16
               OpMemberDecorate %O 2 Offset 32
               OpMemberDecorate %O 3 Offset 64
               OpMemberDecorate %O 4 ColMajor
               OpMemberDecorate %O 4 Offset 80
               OpMemberDecorate %O 4 MatrixStride 16
               OpDecorate %_arr_O_uint_2 ArrayStride 176
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpMemberDecorate %Output 2 Offset 16
               OpMemberDecorate %Output 3 Offset 32
               OpMemberDecorate %Output 4 Offset 48
               OpMemberDecorate %Output 5 Offset 64
               OpMemberDecorate %Output 6 ColMajor
               OpMemberDecorate %Output 6 Offset 96
               OpMemberDecorate %Output 6 MatrixStride 16
               OpMemberDecorate %Output 7 Offset 128
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
          %F = OpTypeStruct %int %v2uint
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%mat2v3float = OpTypeMatrix %v3float 2
     %v3uint = OpTypeVector %uint 3
%mat3v3float = OpTypeMatrix %v3float 3
%_arr_mat3v3float_uint_2 = OpTypeArray %mat3v3float %uint_2
          %O = OpTypeStruct %v3uint %v2float %_arr_float_uint_2 %v2float %_arr_mat3v3float_uint_2
%_arr_O_uint_2 = OpTypeArray %O %uint_2
     %Output = OpTypeStruct %float %v2float %v3float %F %float %_arr_float_uint_2 %mat2v3float %_arr_O_uint_2
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, BlockLayoutPermitsTightVec3ScalarPackingGood) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 12
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %v3float %float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, BlockLayoutForbidsTightScalarVec3PackingBad) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Structure id 2 decorated as Block for variable in Uniform "
                "storage class must follow standard uniform buffer layout "
                "rules: member 1 at offset 4 is not aligned to 16"));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsTightScalarVec3PackingWithRelaxedLayoutGood) {
  // Same as previous test, but with explicit option to relax block layout.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetRelaxBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsTightScalarVec3PackingBadOffsetWithRelaxedLayoutBad) {
  // Same as previous test, but with the vector not aligned to its scalar
  // element. Use offset 5 instead of a multiple of 4.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 5
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetRelaxBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 2 decorated as Block for variable in Uniform storage "
          "class must follow relaxed uniform buffer layout rules: member 1 at "
          "offset 5 is not aligned to scalar element size 4"));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsTightScalarVec3PackingWithVulkan1_1Good) {
  // Same as previous test, but with Vulkan 1.1.  Vulkan 1.1 included
  // VK_KHR_relaxed_block_layout in core.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsTightScalarVec3PackingWithScalarLayoutGood) {
  // Same as previous test, but with scalar block layout.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsScalarAlignedArrayWithScalarLayoutGood) {
  // The array at offset 4 is ok with scalar block layout.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
               OpDecorate %arr_float ArrayStride 4
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %uint_3 = OpConstant %uint 3
      %float = OpTypeFloat 32
  %arr_float = OpTypeArray %float %uint_3
          %S = OpTypeStruct %float %arr_float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsScalarAlignedArrayOfVec3WithScalarLayoutGood) {
  // The array at offset 4 is ok with scalar block layout, even though
  // its elements are vec3.
  // This is the same as the previous case, but the array elements are vec3
  // instead of float.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
               OpDecorate %arr_vec3 ArrayStride 12
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %uint_3 = OpConstant %uint 3
      %float = OpTypeFloat 32
       %vec3 = OpTypeVector %float 3
   %arr_vec3 = OpTypeArray %vec3 %uint_3
          %S = OpTypeStruct %float %arr_vec3
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations,
       BlockLayoutPermitsScalarAlignedStructWithScalarLayoutGood) {
  // Scalar block layout permits the struct at offset 4, even though
  // it contains a vector with base alignment 8 and scalar alignment 4.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpMemberDecorate %st 0 Offset 0
               OpMemberDecorate %st 1 Offset 8
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %vec2 = OpTypeVector %float 2
        %st  = OpTypeStruct %vec2 %float
          %S = OpTypeStruct %float %st
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(
    ValidateDecorations,
    BlockLayoutPermitsFieldsInBaseAlignmentPaddingAtEndOfStructWithScalarLayoutGood) {
  // Scalar block layout permits fields in what would normally be the padding at
  // the end of a struct.
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Float64
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %st 0 Offset 0
               OpMemberDecorate %st 1 Offset 8
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 12
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %double = OpTypeFloat 64
         %st = OpTypeStruct %double %float
          %S = OpTypeStruct %st %float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(
    ValidateDecorations,
    BlockLayoutPermitsStraddlingVectorWithScalarLayoutOverrideRelaxBlockLayoutGood) {
  // Same as previous, but set relaxed block layout first.  Scalar layout always
  // wins.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %vec4 = OpTypeVector %float 4
          %S = OpTypeStruct %float %vec4
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetRelaxBlockLayout(getValidatorOptions(), true);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(
    ValidateDecorations,
    BlockLayoutPermitsStraddlingVectorWithRelaxedLayoutOverridenByScalarBlockLayoutGood) {
  // Same as previous, but set scalar block layout first.  Scalar layout always
  // wins.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %vec4 = OpTypeVector %float 4
          %S = OpTypeStruct %float %vec4
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetScalarBlockLayout(getValidatorOptions(), true);
  spvValidatorOptionsSetRelaxBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations, BufferBlock16bitStandardStorageBufferLayout) {
  std::string spirv = R"(
             OpCapability Shader
             OpCapability StorageUniform16
             OpExtension "SPV_KHR_16bit_storage"
             OpMemoryModel Logical GLSL450
             OpEntryPoint GLCompute %main "main"
             OpExecutionMode %main LocalSize 1 1 1
             OpDecorate %f32arr ArrayStride 4
             OpDecorate %f16arr ArrayStride 2
             OpMemberDecorate %SSBO32 0 Offset 0
             OpMemberDecorate %SSBO16 0 Offset 0
             OpDecorate %SSBO32 BufferBlock
             OpDecorate %SSBO16 BufferBlock
     %void = OpTypeVoid
    %voidf = OpTypeFunction %void
      %u32 = OpTypeInt 32 0
      %i32 = OpTypeInt 32 1
      %f32 = OpTypeFloat 32
    %uvec3 = OpTypeVector %u32 3
 %c_i32_32 = OpConstant %i32 32
%c_i32_128 = OpConstant %i32 128
   %f32arr = OpTypeArray %f32 %c_i32_128
      %f16 = OpTypeFloat 16
   %f16arr = OpTypeArray %f16 %c_i32_128
   %SSBO32 = OpTypeStruct %f32arr
   %SSBO16 = OpTypeStruct %f16arr
%_ptr_Uniform_SSBO32 = OpTypePointer Uniform %SSBO32
 %varSSBO32 = OpVariable %_ptr_Uniform_SSBO32 Uniform
%_ptr_Uniform_SSBO16 = OpTypePointer Uniform %SSBO16
 %varSSBO16 = OpVariable %_ptr_Uniform_SSBO16 Uniform
     %main = OpFunction %void None %voidf
    %label = OpLabel
             OpReturn
             OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, BlockArrayBaseAlignmentGood) {
  // For uniform buffer, Array base alignment is 16, and ArrayStride
  // must be a multiple of 16.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 16
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_PushConstant_S = OpTypePointer PushConstant %S
          %u = OpVariable %_ptr_PushConstant_S PushConstant
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, BlockArrayBadAlignmentBad) {
  // For uniform buffer, Array base alignment is 16.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 8
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %u = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 3 decorated as Block for variable in Uniform "
          "storage class must follow standard uniform buffer layout rules: "
          "member 1 at offset 8 is not aligned to 16"));
}

TEST_F(ValidateDecorations, BlockArrayBadAlignmentWithRelaxedLayoutStillBad) {
  // For uniform buffer, Array base alignment is 16, and ArrayStride
  // must be a multiple of 16.  This case uses relaxed block layout.  Relaxed
  // layout only relaxes rules for vector alignment, not array alignment.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %u DescriptorSet 0
               OpDecorate %u Binding 0
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 8
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %u = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  spvValidatorOptionsSetRelaxBlockLayout(getValidatorOptions(), true);
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 4 decorated as Block for variable in Uniform "
          "storage class must follow standard uniform buffer layout rules: "
          "member 1 at offset 8 is not aligned to 16"));
}

TEST_F(ValidateDecorations, BlockArrayBadAlignmentWithVulkan1_1StillBad) {
  // Same as previous test, but with Vulkan 1.1, which includes
  // VK_KHR_relaxed_block_layout in core.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %u DescriptorSet 0
               OpDecorate %u Binding 0
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 8
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %u = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 4 decorated as Block for variable in Uniform "
          "storage class must follow relaxed uniform buffer layout rules: "
          "member 1 at offset 8 is not aligned to 16"));
}

TEST_F(ValidateDecorations, PushConstantArrayBaseAlignmentGood) {
  // Tests https://github.com/KhronosGroup/SPIRV-Tools/issues/1664
  // From GLSL vertex shader:
  // #version 450
  // layout(push_constant) uniform S { vec2 v; float arr[2]; } u;
  // void main() { }

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 4
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 8
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_PushConstant_S = OpTypePointer PushConstant %S
          %u = OpVariable %_ptr_PushConstant_S PushConstant
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, PushConstantArrayBadAlignmentBad) {
  // Like the previous test, but with offset 7 instead of 8.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 4
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 7
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_PushConstant_S = OpTypePointer PushConstant %S
          %u = OpVariable %_ptr_PushConstant_S PushConstant
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 3 decorated as Block for variable in PushConstant "
          "storage class must follow standard storage buffer layout rules: "
          "member 1 at offset 7 is not aligned to 4"));
}

TEST_F(ValidateDecorations,
       PushConstantLayoutPermitsTightVec3ScalarPackingGood) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 12
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %v3float %float
%_ptr_PushConstant_S = OpTypePointer PushConstant %S
          %B = OpVariable %_ptr_PushConstant_S PushConstant
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations,
       PushConstantLayoutForbidsTightScalarVec3PackingBad) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer PushConstant %S
          %B = OpVariable %_ptr_Uniform_S PushConstant
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 2 decorated as Block for variable in PushConstant "
          "storage class must follow standard storage buffer layout "
          "rules: member 1 at offset 4 is not aligned to 16"));
}

TEST_F(ValidateDecorations, PushConstantMissingBlockGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer PushConstant %struct
      %pc = OpVariable %ptr PushConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, VulkanPushConstantMissingBlockBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer PushConstant %struct
      %pc = OpVariable %ptr PushConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("PushConstant id '2' is missing Block decoration.\n"
                        "From Vulkan spec, section 14.5.1:\n"
                        "Such variables must be identified with a Block "
                        "decoration"));
}

TEST_F(ValidateDecorations, MultiplePushConstantsSingleEntryPointGood) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Fragment %1 "main"
                OpExecutionMode %1 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant

           %1 = OpFunction %void None %voidfn
       %label = OpLabel
           %2 = OpAccessChain %ptr_float %pc1 %int_0
           %3 = OpLoad %float %2
           %4 = OpAccessChain %ptr_float %pc2 %int_0
           %5 = OpLoad %float %4
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations,
       VulkanMultiplePushConstantsDifferentEntryPointGood) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Vertex %1 "func1"
                OpEntryPoint Fragment %2 "func2"
                OpExecutionMode %2 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant

           %1 = OpFunction %void None %voidfn
      %label1 = OpLabel
           %3 = OpAccessChain %ptr_float %pc1 %int_0
           %4 = OpLoad %float %3
                OpReturn
                OpFunctionEnd

           %2 = OpFunction %void None %voidfn
      %label2 = OpLabel
           %5 = OpAccessChain %ptr_float %pc2 %int_0
           %6 = OpLoad %float %5
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1))
      << getDiagnosticString();
}

TEST_F(ValidateDecorations,
       VulkanMultiplePushConstantsUnusedSingleEntryPointGood) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Fragment %1 "main"
                OpExecutionMode %1 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant

           %1 = OpFunction %void None %voidfn
       %label = OpLabel
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1))
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, VulkanMultiplePushConstantsSingleEntryPointBad) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Fragment %1 "main"
                OpExecutionMode %1 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant

           %1 = OpFunction %void None %voidfn
       %label = OpLabel
           %2 = OpAccessChain %ptr_float %pc1 %int_0
           %3 = OpLoad %float %2
           %4 = OpAccessChain %ptr_float %pc2 %int_0
           %5 = OpLoad %float %4
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Entry point id '1' uses more than one PushConstant interface.\n"
          "From Vulkan spec, section 14.5.1:\n"
          "There must be no more than one push constant block "
          "statically used per shader entry point."));
}

TEST_F(ValidateDecorations,
       VulkanMultiplePushConstantsDifferentEntryPointSubFunctionGood) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Vertex %1 "func1"
                OpEntryPoint Fragment %2 "func2"
                OpExecutionMode %2 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant
 
        %sub1 = OpFunction %void None %voidfn
  %label_sub1 = OpLabel
           %3 = OpAccessChain %ptr_float %pc1 %int_0
           %4 = OpLoad %float %3
                OpReturn
                OpFunctionEnd

        %sub2 = OpFunction %void None %voidfn
  %label_sub2 = OpLabel
           %5 = OpAccessChain %ptr_float %pc2 %int_0
           %6 = OpLoad %float %5
                OpReturn
                OpFunctionEnd

           %1 = OpFunction %void None %voidfn
      %label1 = OpLabel
       %call1 = OpFunctionCall %void %sub1
                OpReturn
                OpFunctionEnd

           %2 = OpFunction %void None %voidfn
      %label2 = OpLabel
       %call2 = OpFunctionCall %void %sub2
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1))
      << getDiagnosticString();
}

TEST_F(ValidateDecorations,
       VulkanMultiplePushConstantsSingleEntryPointSubFunctionBad) {
  std::string spirv = R"(
                OpCapability Shader
                OpMemoryModel Logical GLSL450
                OpEntryPoint Fragment %1 "main"
                OpExecutionMode %1 OriginUpperLeft
    
                OpDecorate %struct Block
                OpMemberDecorate %struct 0 Offset 0
    
        %void = OpTypeVoid
      %voidfn = OpTypeFunction %void
       %float = OpTypeFloat 32
         %int = OpTypeInt 32 0
       %int_0 = OpConstant %int 0
      %struct = OpTypeStruct %float
         %ptr = OpTypePointer PushConstant %struct
   %ptr_float = OpTypePointer PushConstant %float 
         %pc1 = OpVariable %ptr PushConstant
         %pc2 = OpVariable %ptr PushConstant

        %sub1 = OpFunction %void None %voidfn
  %label_sub1 = OpLabel
           %3 = OpAccessChain %ptr_float %pc1 %int_0
           %4 = OpLoad %float %3
                OpReturn
                OpFunctionEnd

        %sub2 = OpFunction %void None %voidfn
  %label_sub2 = OpLabel
           %5 = OpAccessChain %ptr_float %pc2 %int_0
           %6 = OpLoad %float %5
                OpReturn
                OpFunctionEnd

           %1 = OpFunction %void None %voidfn
      %label1 = OpLabel
       %call1 = OpFunctionCall %void %sub1
       %call2 = OpFunctionCall %void %sub2
                OpReturn
                OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Entry point id '1' uses more than one PushConstant interface.\n"
          "From Vulkan spec, section 14.5.1:\n"
          "There must be no more than one push constant block "
          "statically used per shader entry point."));
}

TEST_F(ValidateDecorations, VulkanUniformMissingDescriptorSetBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpMemberDecorate %struct 0 Offset 0
            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer Uniform %struct
%ptr_float = OpTypePointer Uniform %float
     %var = OpVariable %ptr Uniform
     %int = OpTypeInt 32 0
   %int_0 = OpConstant %int 0

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpAccessChain %ptr_float %var %int_0
       %3 = OpLoad %float %2
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Uniform id '3' is missing DescriptorSet decoration.\n"
                        "From Vulkan spec, section 14.5.2:\n"
                        "These variables must have DescriptorSet and Binding "
                        "decorations specified"));
}

TEST_F(ValidateDecorations, VulkanUniformMissingBindingBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpMemberDecorate %struct 0 Offset 0
            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer Uniform %struct
%ptr_float = OpTypePointer Uniform %float
     %var = OpVariable %ptr Uniform
     %int = OpTypeInt 32 0
   %int_0 = OpConstant %int 0

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpAccessChain %ptr_float %var %int_0
       %3 = OpLoad %float %2
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Uniform id '3' is missing Binding decoration.\n"
                        "From Vulkan spec, section 14.5.2:\n"
                        "These variables must have DescriptorSet and Binding "
                        "decorations specified"));
}

TEST_F(ValidateDecorations, VulkanUniformConstantMissingDescriptorSetBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
 %sampler = OpTypeSampler
     %ptr = OpTypePointer UniformConstant %sampler
     %var = OpVariable %ptr UniformConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpLoad %sampler %var
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("UniformConstant id '2' is missing DescriptorSet decoration.\n"
                "From Vulkan spec, section 14.5.2:\n"
                "These variables must have DescriptorSet and Binding "
                "decorations specified"));
}

TEST_F(ValidateDecorations, VulkanUniformConstantMissingBindingBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
 %sampler = OpTypeSampler
     %ptr = OpTypePointer UniformConstant %sampler
     %var = OpVariable %ptr UniformConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpLoad %sampler %var
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("UniformConstant id '2' is missing Binding decoration.\n"
                "From Vulkan spec, section 14.5.2:\n"
                "These variables must have DescriptorSet and Binding "
                "decorations specified"));
}

TEST_F(ValidateDecorations, VulkanStorageBufferMissingDescriptorSetBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer
%ptr_float = OpTypePointer StorageBuffer %float
     %int = OpTypeInt 32 0
   %int_0 = OpConstant %int 0

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpAccessChain %ptr_float %var %int_0
       %3 = OpLoad %float %2
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("StorageBuffer id '3' is missing DescriptorSet decoration.\n"
                "From Vulkan spec, section 14.5.2:\n"
                "These variables must have DescriptorSet and Binding "
                "decorations specified"));
}

TEST_F(ValidateDecorations, VulkanStorageBufferMissingBindingBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer
%ptr_float = OpTypePointer StorageBuffer %float
     %int = OpTypeInt 32 0
   %int_0 = OpConstant %int 0

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
       %2 = OpAccessChain %ptr_float %var %int_0
       %3 = OpLoad %float %2
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("StorageBuffer id '3' is missing Binding decoration.\n"
                        "From Vulkan spec, section 14.5.2:\n"
                        "These variables must have DescriptorSet and Binding "
                        "decorations specified"));
}

TEST_F(ValidateDecorations,
       VulkanStorageBufferMissingDescriptorSetSubFunctionBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer
%ptr_float = OpTypePointer StorageBuffer %float
     %int = OpTypeInt 32 0
   %int_0 = OpConstant %int 0

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
    %call = OpFunctionCall %void %2
            OpReturn
            OpFunctionEnd
       %2 = OpFunction %void None %voidfn
  %label2 = OpLabel
       %3 = OpAccessChain %ptr_float %var %int_0
       %4 = OpLoad %float %3
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("StorageBuffer id '3' is missing DescriptorSet decoration.\n"
                "From Vulkan spec, section 14.5.2:\n"
                "These variables must have DescriptorSet and Binding "
                "decorations specified"));
}

TEST_F(ValidateDecorations,
       VulkanStorageBufferMissingDescriptorAndBindingUnusedGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct BufferBlock

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateDecorations, UniformMissingDescriptorSetGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpMemberDecorate %struct 0 Offset 0
            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer Uniform %struct
     %var = OpVariable %ptr Uniform

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, UniformMissingBindingGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpMemberDecorate %struct 0 Offset 0
            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer Uniform %struct
     %var = OpVariable %ptr Uniform

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, UniformConstantMissingDescriptorSetGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
 %sampler = OpTypeSampler
     %ptr = OpTypePointer UniformConstant %sampler
     %var = OpVariable %ptr UniformConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, UniformConstantMissingBindingGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
 %sampler = OpTypeSampler
     %ptr = OpTypePointer UniformConstant %sampler
     %var = OpVariable %ptr UniformConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, StorageBufferMissingDescriptorSetGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct BufferBlock
            OpDecorate %var Binding 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, StorageBufferMissingBindingGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpExtension "SPV_KHR_storage_buffer_storage_class"
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct BufferBlock
            OpDecorate %var DescriptorSet 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer StorageBuffer %struct
     %var = OpVariable %ptr StorageBuffer

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, StorageBufferStorageClassArrayBaseAlignmentGood) {
  // Spot check buffer rules when using StorageBuffer storage class with Block
  // decoration.
  std::string spirv = R"(
               OpCapability Shader
               OpExtension "SPV_KHR_storage_buffer_storage_class"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 4
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 8
               OpDecorate %S Block
               OpDecorate %u DescriptorSet 0
               OpDecorate %u Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_Uniform_S = OpTypePointer StorageBuffer %S
          %u = OpVariable %_ptr_Uniform_S StorageBuffer
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, StorageBufferStorageClassArrayBadAlignmentBad) {
  // Like the previous test, but with offset 7.
  std::string spirv = R"(
               OpCapability Shader
               OpExtension "SPV_KHR_storage_buffer_storage_class"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpDecorate %_arr_float_uint_2 ArrayStride 4
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 7
               OpDecorate %S Block
               OpDecorate %u DescriptorSet 0
               OpDecorate %u Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
          %S = OpTypeStruct %v2float %_arr_float_uint_2
%_ptr_Uniform_S = OpTypePointer StorageBuffer %S
          %u = OpVariable %_ptr_Uniform_S StorageBuffer
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 3 decorated as Block for variable in StorageBuffer "
          "storage class must follow standard storage buffer layout rules: "
          "member 1 at offset 7 is not aligned to 4"));
}

TEST_F(ValidateDecorations, BufferBlockStandardStorageBufferLayout) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %F 0 Offset 0
               OpMemberDecorate %F 1 Offset 8
               OpDecorate %_arr_float_uint_2 ArrayStride 4
               OpDecorate %_arr_mat3v3float_uint_2 ArrayStride 48
               OpMemberDecorate %O 0 Offset 0
               OpMemberDecorate %O 1 Offset 16
               OpMemberDecorate %O 2 Offset 24
               OpMemberDecorate %O 3 Offset 32
               OpMemberDecorate %O 4 ColMajor
               OpMemberDecorate %O 4 Offset 48
               OpMemberDecorate %O 4 MatrixStride 16
               OpDecorate %_arr_O_uint_2 ArrayStride 144
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpMemberDecorate %Output 2 Offset 16
               OpMemberDecorate %Output 3 Offset 32
               OpMemberDecorate %Output 4 Offset 48
               OpMemberDecorate %Output 5 Offset 52
               OpMemberDecorate %Output 6 ColMajor
               OpMemberDecorate %Output 6 Offset 64
               OpMemberDecorate %Output 6 MatrixStride 16
               OpMemberDecorate %Output 7 Offset 96
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
          %F = OpTypeStruct %int %v2uint
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%mat2v3float = OpTypeMatrix %v3float 2
     %v3uint = OpTypeVector %uint 3
%mat3v3float = OpTypeMatrix %v3float 3
%_arr_mat3v3float_uint_2 = OpTypeArray %mat3v3float %uint_2
          %O = OpTypeStruct %v3uint %v2float %_arr_float_uint_2 %v2float %_arr_mat3v3float_uint_2
%_arr_O_uint_2 = OpTypeArray %O %uint_2
     %Output = OpTypeStruct %float %v2float %v3float %F %float %_arr_float_uint_2 %mat2v3float %_arr_O_uint_2
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations,
       StorageBufferLayoutPermitsTightVec3ScalarPackingGood) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpExtension "SPV_KHR_storage_buffer_storage_class"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 12
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %v3float %float
%_ptr_StorageBuffer_S = OpTypePointer StorageBuffer %S
          %B = OpVariable %_ptr_StorageBuffer_S StorageBuffer
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations,
       StorageBufferLayoutForbidsTightScalarVec3PackingBad) {
  // See https://github.com/KhronosGroup/SPIRV-Tools/issues/1666
  std::string spirv = R"(
               OpCapability Shader
               OpExtension "SPV_KHR_storage_buffer_storage_class"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 0
               OpMemberDecorate %S 1 Offset 4
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_StorageBuffer_S = OpTypePointer StorageBuffer %S
          %B = OpVariable %_ptr_StorageBuffer_S StorageBuffer
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 2 decorated as Block for variable in StorageBuffer "
          "storage class must follow standard storage buffer layout "
          "rules: member 1 at offset 4 is not aligned to 16"));
}

TEST_F(ValidateDecorations,
       BlockStandardUniformBufferLayoutIncorrectOffset0Bad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %F 0 Offset 0
               OpMemberDecorate %F 1 Offset 8
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %_arr_mat3v3float_uint_2 ArrayStride 48
               OpMemberDecorate %O 0 Offset 0
               OpMemberDecorate %O 1 Offset 16
               OpMemberDecorate %O 2 Offset 24
               OpMemberDecorate %O 3 Offset 33
               OpMemberDecorate %O 4 ColMajor
               OpMemberDecorate %O 4 Offset 80
               OpMemberDecorate %O 4 MatrixStride 16
               OpDecorate %_arr_O_uint_2 ArrayStride 176
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpMemberDecorate %Output 2 Offset 16
               OpMemberDecorate %Output 3 Offset 32
               OpMemberDecorate %Output 4 Offset 48
               OpMemberDecorate %Output 5 Offset 64
               OpMemberDecorate %Output 6 ColMajor
               OpMemberDecorate %Output 6 Offset 96
               OpMemberDecorate %Output 6 MatrixStride 16
               OpMemberDecorate %Output 7 Offset 128
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
          %F = OpTypeStruct %int %v2uint
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%mat2v3float = OpTypeMatrix %v3float 2
     %v3uint = OpTypeVector %uint 3
%mat3v3float = OpTypeMatrix %v3float 3
%_arr_mat3v3float_uint_2 = OpTypeArray %mat3v3float %uint_2
          %O = OpTypeStruct %v3uint %v2float %_arr_float_uint_2 %v2float %_arr_mat3v3float_uint_2
%_arr_O_uint_2 = OpTypeArray %O %uint_2
     %Output = OpTypeStruct %float %v2float %v3float %F %float %_arr_float_uint_2 %mat2v3float %_arr_O_uint_2
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Structure id 6 decorated as Block for variable in Uniform "
                "storage class must follow standard uniform buffer layout "
                "rules: member 2 at offset 24 is not aligned to 16"));
}

TEST_F(ValidateDecorations,
       BlockStandardUniformBufferLayoutIncorrectOffset1Bad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %F 0 Offset 0
               OpMemberDecorate %F 1 Offset 8
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %_arr_mat3v3float_uint_2 ArrayStride 48
               OpMemberDecorate %O 0 Offset 0
               OpMemberDecorate %O 1 Offset 16
               OpMemberDecorate %O 2 Offset 32
               OpMemberDecorate %O 3 Offset 64
               OpMemberDecorate %O 4 ColMajor
               OpMemberDecorate %O 4 Offset 80
               OpMemberDecorate %O 4 MatrixStride 16
               OpDecorate %_arr_O_uint_2 ArrayStride 176
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpMemberDecorate %Output 2 Offset 16
               OpMemberDecorate %Output 3 Offset 32
               OpMemberDecorate %Output 4 Offset 48
               OpMemberDecorate %Output 5 Offset 71
               OpMemberDecorate %Output 6 ColMajor
               OpMemberDecorate %Output 6 Offset 96
               OpMemberDecorate %Output 6 MatrixStride 16
               OpMemberDecorate %Output 7 Offset 128
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
          %F = OpTypeStruct %int %v2uint
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%mat2v3float = OpTypeMatrix %v3float 2
     %v3uint = OpTypeVector %uint 3
%mat3v3float = OpTypeMatrix %v3float 3
%_arr_mat3v3float_uint_2 = OpTypeArray %mat3v3float %uint_2
          %O = OpTypeStruct %v3uint %v2float %_arr_float_uint_2 %v2float %_arr_mat3v3float_uint_2
%_arr_O_uint_2 = OpTypeArray %O %uint_2
     %Output = OpTypeStruct %float %v2float %v3float %F %float %_arr_float_uint_2 %mat2v3float %_arr_O_uint_2
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Structure id 8 decorated as Block for variable in Uniform "
                "storage class must follow standard uniform buffer layout "
                "rules: member 5 at offset 71 is not aligned to 16"));
}

TEST_F(ValidateDecorations, BlockUniformBufferLayoutIncorrectArrayStrideBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %F 0 Offset 0
               OpMemberDecorate %F 1 Offset 8
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpDecorate %_arr_mat3v3float_uint_2 ArrayStride 49
               OpMemberDecorate %O 0 Offset 0
               OpMemberDecorate %O 1 Offset 16
               OpMemberDecorate %O 2 Offset 32
               OpMemberDecorate %O 3 Offset 64
               OpMemberDecorate %O 4 ColMajor
               OpMemberDecorate %O 4 Offset 80
               OpMemberDecorate %O 4 MatrixStride 16
               OpDecorate %_arr_O_uint_2 ArrayStride 176
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpMemberDecorate %Output 2 Offset 16
               OpMemberDecorate %Output 3 Offset 32
               OpMemberDecorate %Output 4 Offset 48
               OpMemberDecorate %Output 5 Offset 64
               OpMemberDecorate %Output 6 ColMajor
               OpMemberDecorate %Output 6 Offset 96
               OpMemberDecorate %Output 6 MatrixStride 16
               OpMemberDecorate %Output 7 Offset 128
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v2float = OpTypeVector %float 2
    %v3float = OpTypeVector %float 3
        %int = OpTypeInt 32 1
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
          %F = OpTypeStruct %int %v2uint
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%mat2v3float = OpTypeMatrix %v3float 2
     %v3uint = OpTypeVector %uint 3
%mat3v3float = OpTypeMatrix %v3float 3
%_arr_mat3v3float_uint_2 = OpTypeArray %mat3v3float %uint_2
          %O = OpTypeStruct %v3uint %v2float %_arr_float_uint_2 %v2float %_arr_mat3v3float_uint_2
%_arr_O_uint_2 = OpTypeArray %O %uint_2
     %Output = OpTypeStruct %float %v2float %v3float %F %float %_arr_float_uint_2 %mat2v3float %_arr_O_uint_2
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 6 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 4 is "
          "an array with stride 49 not satisfying alignment to 16"));
}

TEST_F(ValidateDecorations,
       BufferBlockStandardStorageBufferLayoutImproperStraddleBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 8
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
     %Output = OpTypeStruct %float %v3float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Structure id 3 decorated as BufferBlock for variable in "
                "Uniform storage class must follow standard storage buffer "
                "layout rules: member 1 at offset 8 is not aligned to 16"));
}

TEST_F(ValidateDecorations,
       BlockUniformBufferLayoutOffsetInsideArrayPaddingBad) {
  // In this case the 2nd member fits entirely within the padding.
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpDecorate %_arr_float_uint_2 ArrayStride 16
               OpMemberDecorate %Output 0 Offset 0
               OpMemberDecorate %Output 1 Offset 20
               OpDecorate %Output Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %uint = OpTypeInt 32 0
     %v2uint = OpTypeVector %uint 2
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
     %Output = OpTypeStruct %_arr_float_uint_2 %float
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 4 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 1 at "
          "offset 20 overlaps previous member ending at offset 31"));
}

TEST_F(ValidateDecorations,
       BlockUniformBufferLayoutOffsetInsideStructPaddingBad) {
  // In this case the 2nd member fits entirely within the padding.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %1 "main"
               OpMemberDecorate %_struct_6 0 Offset 0
               OpMemberDecorate %_struct_2 0 Offset 0
               OpMemberDecorate %_struct_2 1 Offset 4
               OpDecorate %_struct_2 Block
       %void = OpTypeVoid
          %4 = OpTypeFunction %void
      %float = OpTypeFloat 32
  %_struct_6 = OpTypeStruct %float
  %_struct_2 = OpTypeStruct %_struct_6 %float
%_ptr_Uniform__struct_2 = OpTypePointer Uniform %_struct_2
          %8 = OpVariable %_ptr_Uniform__struct_2 Uniform
          %1 = OpFunction %void None %4
          %9 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 3 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 1 at "
          "offset 4 overlaps previous member ending at offset 15"));
}

TEST_F(ValidateDecorations, BlockLayoutOffsetOutOfOrderGoodUniversal1_0) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpMemberDecorate %Outer 0 Offset 4
               OpMemberDecorate %Outer 1 Offset 0
               OpDecorate %Outer Block
               OpDecorate %O DescriptorSet 0
               OpDecorate %O Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
      %Outer = OpTypeStruct %uint %uint
%_ptr_Uniform_Outer = OpTypePointer Uniform %Outer
          %O = OpVariable %_ptr_Uniform_Outer Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_UNIVERSAL_1_0));
}

TEST_F(ValidateDecorations, BlockLayoutOffsetOutOfOrderGoodOpenGL4_5) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpMemberDecorate %Outer 0 Offset 4
               OpMemberDecorate %Outer 1 Offset 0
               OpDecorate %Outer Block
               OpDecorate %O DescriptorSet 0
               OpDecorate %O Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
      %Outer = OpTypeStruct %uint %uint
%_ptr_Uniform_Outer = OpTypePointer Uniform %Outer
          %O = OpVariable %_ptr_Uniform_Outer Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_OPENGL_4_5));
}

TEST_F(ValidateDecorations, BlockLayoutOffsetOutOfOrderGoodVulkan1_1) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpMemberDecorate %Outer 0 Offset 4
               OpMemberDecorate %Outer 1 Offset 0
               OpDecorate %Outer Block
               OpDecorate %O DescriptorSet 0
               OpDecorate %O Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
      %Outer = OpTypeStruct %uint %uint
%_ptr_Uniform_Outer = OpTypePointer Uniform %Outer
          %O = OpVariable %_ptr_Uniform_Outer Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_1))
      << getDiagnosticString();
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations, BlockLayoutOffsetOverlapBad) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpMemberDecorate %Outer 0 Offset 0
               OpMemberDecorate %Outer 1 Offset 16
               OpMemberDecorate %Inner 0 Offset 0
               OpMemberDecorate %Inner 1 Offset 16
               OpDecorate %Outer Block
               OpDecorate %O DescriptorSet 0
               OpDecorate %O Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
      %Inner = OpTypeStruct %uint %uint
      %Outer = OpTypeStruct %Inner %uint
%_ptr_Uniform_Outer = OpTypePointer Uniform %Outer
          %O = OpVariable %_ptr_Uniform_Outer Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 3 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 1 at "
          "offset 16 overlaps previous member ending at offset 31"));
}

TEST_F(ValidateDecorations, BufferBlockEmptyStruct) {
  std::string spirv = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main"
               OpExecutionMode %main LocalSize 1 1 1
               OpSource GLSL 430
               OpMemberDecorate %Output 0 Offset 0
               OpDecorate %Output BufferBlock
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
          %S = OpTypeStruct
     %Output = OpTypeStruct %S
%_ptr_Uniform_Output = OpTypePointer Uniform %Output
 %dataOutput = OpVariable %_ptr_Uniform_Output Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, RowMajorMatrixTightPackingGood) {
  // Row major matrix rule:
  //     A row-major matrix of C columns has a base alignment equal to
  //     the base alignment of a vector of C matrix components.
  // Note: The "matrix component" is the scalar element type.

  // The matrix has 3 columns and 2 rows (C=3, R=2).
  // So the base alignment of b is the same as a vector of 3 floats, which is 16
  // bytes. The matrix consists of two of these, and therefore occupies 2 x 16
  // bytes, or 32 bytes.
  //
  // So the offsets can be:
  // a -> 0
  // b -> 16
  // c -> 48
  // d -> 60 ; d fits at bytes 12-15 after offset of c. Tight (vec3;float)
  // packing

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpSource GLSL 450
               OpMemberDecorate %_struct_2 0 Offset 0
               OpMemberDecorate %_struct_2 1 RowMajor
               OpMemberDecorate %_struct_2 1 Offset 16
               OpMemberDecorate %_struct_2 1 MatrixStride 16
               OpMemberDecorate %_struct_2 2 Offset 48
               OpMemberDecorate %_struct_2 3 Offset 60
               OpDecorate %_struct_2 Block
               OpDecorate %3 DescriptorSet 0
               OpDecorate %3 Binding 0
       %void = OpTypeVoid
          %5 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
    %v2float = OpTypeVector %float 2
%mat3v2float = OpTypeMatrix %v2float 3
    %v3float = OpTypeVector %float 3
  %_struct_2 = OpTypeStruct %v4float %mat3v2float %v3float %float
%_ptr_Uniform__struct_2 = OpTypePointer Uniform %_struct_2
          %3 = OpVariable %_ptr_Uniform__struct_2 Uniform
          %1 = OpFunction %void None %5
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, ArrayArrayRowMajorMatrixTightPackingGood) {
  // Like the previous case, but we have an array of arrays of matrices.
  // The RowMajor decoration goes on the struct member (surprisingly).

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpSource GLSL 450
               OpMemberDecorate %_struct_2 0 Offset 0
               OpMemberDecorate %_struct_2 1 RowMajor
               OpMemberDecorate %_struct_2 1 Offset 16
               OpMemberDecorate %_struct_2 1 MatrixStride 16
               OpMemberDecorate %_struct_2 2 Offset 80
               OpMemberDecorate %_struct_2 3 Offset 92
               OpDecorate %arr_mat ArrayStride 32
               OpDecorate %arr_arr_mat ArrayStride 32
               OpDecorate %_struct_2 Block
               OpDecorate %3 DescriptorSet 0
               OpDecorate %3 Binding 0
       %void = OpTypeVoid
          %5 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
    %v2float = OpTypeVector %float 2
%mat3v2float = OpTypeMatrix %v2float 3
%uint        = OpTypeInt 32 0
%uint_1      = OpConstant %uint 1
%uint_2      = OpConstant %uint 2
    %arr_mat = OpTypeArray %mat3v2float %uint_1
%arr_arr_mat = OpTypeArray %arr_mat %uint_2
    %v3float = OpTypeVector %float 3
  %_struct_2 = OpTypeStruct %v4float %arr_arr_mat %v3float %float
%_ptr_Uniform__struct_2 = OpTypePointer Uniform %_struct_2
          %3 = OpVariable %_ptr_Uniform__struct_2 Uniform
          %1 = OpFunction %void None %5
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState())
      << getDiagnosticString();
}

TEST_F(ValidateDecorations, ArrayArrayRowMajorMatrixNextMemberOverlapsBad) {
  // Like the previous case, but the offset of member 2 overlaps the matrix.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpSource GLSL 450
               OpMemberDecorate %_struct_2 0 Offset 0
               OpMemberDecorate %_struct_2 1 RowMajor
               OpMemberDecorate %_struct_2 1 Offset 16
               OpMemberDecorate %_struct_2 1 MatrixStride 16
               OpMemberDecorate %_struct_2 2 Offset 64
               OpMemberDecorate %_struct_2 3 Offset 92
               OpDecorate %arr_mat ArrayStride 32
               OpDecorate %arr_arr_mat ArrayStride 32
               OpDecorate %_struct_2 Block
               OpDecorate %3 DescriptorSet 0
               OpDecorate %3 Binding 0
       %void = OpTypeVoid
          %5 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
    %v2float = OpTypeVector %float 2
%mat3v2float = OpTypeMatrix %v2float 3
%uint        = OpTypeInt 32 0
%uint_1      = OpConstant %uint 1
%uint_2      = OpConstant %uint 2
    %arr_mat = OpTypeArray %mat3v2float %uint_1
%arr_arr_mat = OpTypeArray %arr_mat %uint_2
    %v3float = OpTypeVector %float 3
  %_struct_2 = OpTypeStruct %v4float %arr_arr_mat %v3float %float
%_ptr_Uniform__struct_2 = OpTypePointer Uniform %_struct_2
          %3 = OpVariable %_ptr_Uniform__struct_2 Uniform
          %1 = OpFunction %void None %5
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 2 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 2 at "
          "offset 64 overlaps previous member ending at offset 79"));
}

TEST_F(ValidateDecorations, StorageBufferArraySizeCalculationPackGood) {
  // Original GLSL

  // #version 450
  // layout (set=0,binding=0) buffer S {
  //   uvec3 arr[2][2]; // first 3 elements are 16 bytes, last is 12
  //   uint i;  // Can have offset 60 = 3x16 + 12
  // } B;
  // void main() {}

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpDecorate %_arr_v3uint_uint_2 ArrayStride 16
               OpDecorate %_arr__arr_v3uint_uint_2_uint_2 ArrayStride 32
               OpMemberDecorate %_struct_4 0 Offset 0
               OpMemberDecorate %_struct_4 1 Offset 60
               OpDecorate %_struct_4 BufferBlock
               OpDecorate %5 DescriptorSet 0
               OpDecorate %5 Binding 0
       %void = OpTypeVoid
          %7 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %v3uint = OpTypeVector %uint 3
     %uint_2 = OpConstant %uint 2
%_arr_v3uint_uint_2 = OpTypeArray %v3uint %uint_2
%_arr__arr_v3uint_uint_2_uint_2 = OpTypeArray %_arr_v3uint_uint_2 %uint_2
  %_struct_4 = OpTypeStruct %_arr__arr_v3uint_uint_2_uint_2 %uint
%_ptr_Uniform__struct_4 = OpTypePointer Uniform %_struct_4
          %5 = OpVariable %_ptr_Uniform__struct_4 Uniform
          %1 = OpFunction %void None %7
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, StorageBufferArraySizeCalculationPackBad) {
  // Like previous but, the offset of the second member is too small.

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpDecorate %_arr_v3uint_uint_2 ArrayStride 16
               OpDecorate %_arr__arr_v3uint_uint_2_uint_2 ArrayStride 32
               OpMemberDecorate %_struct_4 0 Offset 0
               OpMemberDecorate %_struct_4 1 Offset 56
               OpDecorate %_struct_4 BufferBlock
               OpDecorate %5 DescriptorSet 0
               OpDecorate %5 Binding 0
       %void = OpTypeVoid
          %7 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %v3uint = OpTypeVector %uint 3
     %uint_2 = OpConstant %uint 2
%_arr_v3uint_uint_2 = OpTypeArray %v3uint %uint_2
%_arr__arr_v3uint_uint_2_uint_2 = OpTypeArray %_arr_v3uint_uint_2 %uint_2
  %_struct_4 = OpTypeStruct %_arr__arr_v3uint_uint_2_uint_2 %uint
%_ptr_Uniform__struct_4 = OpTypePointer Uniform %_struct_4
          %5 = OpVariable %_ptr_Uniform__struct_4 Uniform
          %1 = OpFunction %void None %7
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Structure id 4 decorated as BufferBlock for variable "
                        "in Uniform storage class must follow standard storage "
                        "buffer layout rules: member 1 at offset 56 overlaps "
                        "previous member ending at offset 59"));
}

TEST_F(ValidateDecorations, UniformBufferArraySizeCalculationPackGood) {
  // Like the corresponding buffer block case, but the array padding must
  // count for the last element as well, and so the offset of the second
  // member must be at least 64.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpDecorate %_arr_v3uint_uint_2 ArrayStride 16
               OpDecorate %_arr__arr_v3uint_uint_2_uint_2 ArrayStride 32
               OpMemberDecorate %_struct_4 0 Offset 0
               OpMemberDecorate %_struct_4 1 Offset 64
               OpDecorate %_struct_4 Block
               OpDecorate %5 DescriptorSet 0
               OpDecorate %5 Binding 0
       %void = OpTypeVoid
          %7 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %v3uint = OpTypeVector %uint 3
     %uint_2 = OpConstant %uint 2
%_arr_v3uint_uint_2 = OpTypeArray %v3uint %uint_2
%_arr__arr_v3uint_uint_2_uint_2 = OpTypeArray %_arr_v3uint_uint_2 %uint_2
  %_struct_4 = OpTypeStruct %_arr__arr_v3uint_uint_2_uint_2 %uint
%_ptr_Uniform__struct_4 = OpTypePointer Uniform %_struct_4
          %5 = OpVariable %_ptr_Uniform__struct_4 Uniform
          %1 = OpFunction %void None %7
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, UniformBufferArraySizeCalculationPackBad) {
  // Like previous but, the offset of the second member is too small.

  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %1 "main"
               OpDecorate %_arr_v3uint_uint_2 ArrayStride 16
               OpDecorate %_arr__arr_v3uint_uint_2_uint_2 ArrayStride 32
               OpMemberDecorate %_struct_4 0 Offset 0
               OpMemberDecorate %_struct_4 1 Offset 60
               OpDecorate %_struct_4 Block
               OpDecorate %5 DescriptorSet 0
               OpDecorate %5 Binding 0
       %void = OpTypeVoid
          %7 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %v3uint = OpTypeVector %uint 3
     %uint_2 = OpConstant %uint 2
%_arr_v3uint_uint_2 = OpTypeArray %v3uint %uint_2
%_arr__arr_v3uint_uint_2_uint_2 = OpTypeArray %_arr_v3uint_uint_2 %uint_2
  %_struct_4 = OpTypeStruct %_arr__arr_v3uint_uint_2_uint_2 %uint
%_ptr_Uniform__struct_4 = OpTypePointer Uniform %_struct_4
          %5 = OpVariable %_ptr_Uniform__struct_4 Uniform
          %1 = OpFunction %void None %7
         %12 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Structure id 4 decorated as Block for variable in Uniform storage "
          "class must follow standard uniform buffer layout rules: member 1 at "
          "offset 60 overlaps previous member ending at offset 63"));
}

TEST_F(ValidateDecorations, LayoutNotCheckedWhenSkipBlockLayout) {
  // Checks that block layout is not verified in skipping block layout mode.
  // Even for obviously wrong layout.
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 450
               OpMemberDecorate %S 0 Offset 3 ; wrong alignment
               OpMemberDecorate %S 1 Offset 3 ; same offset as before!
               OpDecorate %S Block
               OpDecorate %B DescriptorSet 0
               OpDecorate %B Binding 0
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v3float = OpTypeVector %float 3
          %S = OpTypeStruct %float %v3float
%_ptr_Uniform_S = OpTypePointer Uniform %S
          %B = OpVariable %_ptr_Uniform_S Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  spvValidatorOptionsSetSkipBlockLayout(getValidatorOptions(), true);
  EXPECT_EQ(SPV_SUCCESS,
            ValidateAndRetrieveValidationState(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations, EntryPointVariableWrongStorageClass) {
  const std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %1 "func" %var
OpExecutionMode %1 OriginUpperLeft
%void = OpTypeVoid
%int = OpTypeInt 32 0
%ptr_int_Workgroup = OpTypePointer Workgroup %int
%var = OpVariable %ptr_int_Workgroup Workgroup
%func_ty = OpTypeFunction %void
%1 = OpFunction %void None %func_ty
%2 = OpLabel
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("OpEntryPoint interfaces must be OpVariables with "
                        "Storage Class of Input(1) or Output(3). Found Storage "
                        "Class 4 for Entry Point id 1."));
}

TEST_F(ValidateDecorations, VulkanMemoryModelNonCoherent) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpMemoryModel Logical VulkanKHR
OpDecorate %1 Coherent
%2 = OpTypeInt 32 0
%3 = OpTypePointer StorageBuffer %2
%1 = OpVariable %3 StorageBuffer
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Coherent decoration targeting 1[%1] is "
                        "banned when using the Vulkan memory model."));
}

TEST_F(ValidateDecorations, VulkanMemoryModelNoCoherentMember) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpMemberDecorate %1 0 Coherent
%2 = OpTypeInt 32 0
%1 = OpTypeStruct %2 %2
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Coherent decoration targeting 1[%_struct_1] (member index 0) "
                "is banned when using the Vulkan memory model."));
}

TEST_F(ValidateDecorations, VulkanMemoryModelNoVolatile) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpMemoryModel Logical VulkanKHR
OpDecorate %1 Volatile
%2 = OpTypeInt 32 0
%3 = OpTypePointer StorageBuffer %2
%1 = OpVariable %3 StorageBuffer
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Volatile decoration targeting 1[%1] is banned when "
                        "using the Vulkan memory model."));
}

TEST_F(ValidateDecorations, VulkanMemoryModelNoVolatileMember) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpMemberDecorate %1 1 Volatile
%2 = OpTypeInt 32 0
%1 = OpTypeStruct %2 %2
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Volatile decoration targeting 1[%_struct_1] (member "
                        "index 1) is banned when using the Vulkan memory "
                        "model."));
}

TEST_F(ValidateDecorations, FPRoundingModeGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%float_1_25 = OpConstant %float 1.25
%half_ptr = OpTypePointer StorageBuffer %half
%half_ptr_var = OpVariable %half_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %float_1_25
OpStore %half_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FPRoundingModeVectorGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%v2half = OpTypeVector %half 2
%v2float = OpTypeVector %float 2
%float_1_25 = OpConstant %float 1.25
%floats = OpConstantComposite %v2float %float_1_25 %float_1_25
%halfs_ptr = OpTypePointer StorageBuffer %v2half
%halfs_ptr_var = OpVariable %halfs_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %v2half %floats
OpStore %halfs_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FPRoundingModeNotOpFConvert) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%short = OpTypeInt 16 1
%int = OpTypeInt 32 1
%int_17 = OpConstant %int 17
%short_ptr = OpTypePointer StorageBuffer %short
%short_ptr_var = OpVariable %short_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpSConvert %short %int_17
OpStore %short_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("FPRoundingMode decoration can be applied only to a "
                        "width-only conversion instruction for floating-point "
                        "object."));
}

TEST_F(ValidateDecorations, FPRoundingModeNoOpStoreGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%float_1_25 = OpConstant %float 1.25
%half_ptr = OpTypePointer StorageBuffer %half
%half_ptr_var = OpVariable %half_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %float_1_25
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FPRoundingModeFConvert64to16Good) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpCapability Float64
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%double = OpTypeFloat 64
%double_1_25 = OpConstant %double 1.25
%half_ptr = OpTypePointer StorageBuffer %half
%half_ptr_var = OpVariable %half_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %double_1_25
OpStore %half_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FPRoundingModeNotStoreInFloat16) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpCapability Float64
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%float = OpTypeFloat 32
%double = OpTypeFloat 64
%double_1_25 = OpConstant %double 1.25
%float_ptr = OpTypePointer StorageBuffer %float
%float_ptr_var = OpVariable %float_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %float %double_1_25
OpStore %float_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("FPRoundingMode decoration can be applied only to the "
                "Object operand of an OpStore storing through a "
                "pointer to a 16-bit floating-point scalar or vector object."));
}

TEST_F(ValidateDecorations, FPRoundingModeBadStorageClass) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%float_1_25 = OpConstant %float 1.25
%half_ptr = OpTypePointer Private %half
%half_ptr_var = OpVariable %half_ptr Private
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %float_1_25
OpStore %half_ptr_var %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("FPRoundingMode decoration can be applied only to the "
                "Object operand of an OpStore in the StorageBuffer, Uniform, "
                "PushConstant, Input, or Output Storage Classes."));
}

TEST_F(ValidateDecorations, FPRoundingModeMultipleOpStoreGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%float_1_25 = OpConstant %float 1.25
%half_ptr = OpTypePointer StorageBuffer %half
%half_ptr_var_0 = OpVariable %half_ptr StorageBuffer
%half_ptr_var_1 = OpVariable %half_ptr StorageBuffer
%half_ptr_var_2 = OpVariable %half_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %float_1_25
OpStore %half_ptr_var_0 %_
OpStore %half_ptr_var_1 %_
OpStore %half_ptr_var_2 %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateAndRetrieveValidationState());
}

TEST_F(ValidateDecorations, FPRoundingModeMultipleUsesBad) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpCapability StorageBuffer16BitAccess
OpExtension "SPV_KHR_storage_buffer_storage_class"
OpExtension "SPV_KHR_variable_pointers"
OpExtension "SPV_KHR_16bit_storage"
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpDecorate %_ FPRoundingMode RTE
%half = OpTypeFloat 16
%float = OpTypeFloat 32
%float_1_25 = OpConstant %float 1.25
%half_ptr = OpTypePointer StorageBuffer %half
%half_ptr_var_0 = OpVariable %half_ptr StorageBuffer
%half_ptr_var_1 = OpVariable %half_ptr StorageBuffer
%void = OpTypeVoid
%func = OpTypeFunction %void
%main = OpFunction %void None %func
%main_entry = OpLabel
%_ = OpFConvert %half %float_1_25
OpStore %half_ptr_var_0 %_
%result = OpFAdd %half %_ %_
OpStore %half_ptr_var_1 %_
OpReturn
OpFunctionEnd
  )";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("FPRoundingMode decoration can be applied only to the "
                        "Object operand of an OpStore."));
}

TEST_F(ValidateDecorations, GroupDecorateTargetsDecorationGroup) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%1 = OpDecorationGroup
OpGroupDecorate %1 %1
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("OpGroupDecorate may not target OpDecorationGroup <id> "
                        "'1[%1]'"));
}

TEST_F(ValidateDecorations, GroupDecorateTargetsDecorationGroup2) {
  std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%1 = OpDecorationGroup
OpGroupDecorate %1 %2 %1
%2 = OpTypeVoid
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("OpGroupDecorate may not target OpDecorationGroup <id> "
                        "'1[%1]'"));
}

TEST_F(ValidateDecorations, RecurseThroughRuntimeArray) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
OpDecorate %outer Block
OpMemberDecorate %inner 0 Offset 0
OpMemberDecorate %inner 1 Offset 1
OpDecorate %runtime ArrayStride 16
OpMemberDecorate %outer 0 Offset 0
%int = OpTypeInt 32 0
%inner = OpTypeStruct %int %int
%runtime = OpTypeRuntimeArray %inner
%outer = OpTypeStruct %runtime
%outer_ptr = OpTypePointer Uniform %outer
%var = OpVariable %outer_ptr Uniform
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Structure id 2 decorated as Block for variable in Uniform "
                "storage class must follow standard uniform buffer layout "
                "rules: member 1 at offset 1 is not aligned to 4"));
}

TEST_F(ValidateDecorations, EmptyStructAtNonZeroOffsetGood) {
  const std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint GLCompute %main "main"
OpExecutionMode %main LocalSize 1 1 1
OpDecorate %struct Block
OpMemberDecorate %struct 0 Offset 0
OpMemberDecorate %struct 1 Offset 16
OpDecorate %var DescriptorSet 0
OpDecorate %var Binding 0
%void = OpTypeVoid
%float = OpTypeFloat 32
%empty = OpTypeStruct
%struct = OpTypeStruct %float %empty
%ptr_struct_ubo = OpTypePointer Uniform %struct
%var = OpVariable %ptr_struct_ubo Uniform
%voidfn = OpTypeFunction %void
%main = OpFunction %void None %voidfn
%entry = OpLabel
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

// Uniform decoration

TEST_F(ValidateDecorations, UniformDecorationGood) {
  const std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %main "main"
OpExecutionMode %main LocalSize 1 1 1
OpDecorate %int0 Uniform
OpDecorate %var Uniform
OpDecorate %val Uniform
%void = OpTypeVoid
%int = OpTypeInt 32 1
%int0 = OpConstantNull %int
%intptr = OpTypePointer Private %int
%var = OpVariable %intptr Private
%fn = OpTypeFunction %void
%main = OpFunction %void None %fn
%entry = OpLabel
%val = OpLoad %int %var
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(), Eq(""));
}

TEST_F(ValidateDecorations, UniformDecorationTargetsTypeBad) {
  const std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %main "main"
OpExecutionMode %main LocalSize 1 1 1
OpDecorate %fn Uniform
%void = OpTypeVoid
%fn = OpTypeFunction %void
%main = OpFunction %void None %fn
%entry = OpLabel
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Uniform decoration applied to a non-object"));
  EXPECT_THAT(getDiagnosticString(), HasSubstr("%2 = OpTypeFunction %void"));
}

TEST_F(ValidateDecorations, UniformDecorationTargetsVoidValueBad) {
  const std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical Simple
OpEntryPoint GLCompute %main "main"
OpExecutionMode %main LocalSize 1 1 1
OpName %call "call"
OpName %myfunc "myfunc"
OpDecorate %call Uniform
%void = OpTypeVoid
%fnty = OpTypeFunction %void
%myfunc = OpFunction %void None %fnty
%myfuncentry = OpLabel
OpReturn
OpFunctionEnd
%main = OpFunction %void None %fnty
%entry = OpLabel
%call = OpFunctionCall %void %myfunc
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Uniform decoration applied to a value with void type\n"
                        "  %call = OpFunctionCall %void %myfunc"));
}

TEST_F(ValidateDecorations, MultipleOffsetDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 Offset 0

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
  %struct = OpTypeStruct %float

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2', member '0' decorated with Offset multiple "
                        "times is not allowed."));
}

TEST_F(ValidateDecorations, MultipleArrayStrideDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %array ArrayStride 4
            OpDecorate %array ArrayStride 4

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
    %uint = OpTypeInt 32 0
  %uint_4 = OpConstant %uint 4
   %array = OpTypeArray %float %uint_4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2' decorated with ArrayStride multiple "
                        "times is not allowed."));
}

TEST_F(ValidateDecorations, MultipleMatrixStrideDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 ColMajor
            OpMemberDecorate %struct 0 MatrixStride 16
            OpMemberDecorate %struct 0 MatrixStride 16

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
   %fvec4 = OpTypeVector %float 4
   %fmat4 = OpTypeMatrix %fvec4 4
  %struct = OpTypeStruct %fmat4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2', member '0' decorated with MatrixStride "
                        "multiple times is not allowed."));
}

TEST_F(ValidateDecorations, MultipleRowMajorDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 MatrixStride 16
            OpMemberDecorate %struct 0 RowMajor
            OpMemberDecorate %struct 0 RowMajor

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
   %fvec4 = OpTypeVector %float 4
   %fmat4 = OpTypeMatrix %fvec4 4
  %struct = OpTypeStruct %fmat4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2', member '0' decorated with RowMajor multiple "
                        "times is not allowed."));
}

TEST_F(ValidateDecorations, MultipleColMajorDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 MatrixStride 16
            OpMemberDecorate %struct 0 ColMajor
            OpMemberDecorate %struct 0 ColMajor

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
   %fvec4 = OpTypeVector %float 4
   %fmat4 = OpTypeMatrix %fvec4 4
  %struct = OpTypeStruct %fmat4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2', member '0' decorated with ColMajor multiple "
                        "times is not allowed."));
}

TEST_F(ValidateDecorations, RowMajorAndColMajorDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 MatrixStride 16
            OpMemberDecorate %struct 0 ColMajor
            OpMemberDecorate %struct 0 RowMajor

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
   %fvec4 = OpTypeVector %float 4
   %fmat4 = OpTypeMatrix %fvec4 4
  %struct = OpTypeStruct %fmat4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("ID '2', member '0' decorated with both RowMajor and "
                        "ColMajor is not allowed."));
}

TEST_F(ValidateDecorations, BlockAndBufferBlockDecorationsOnSameID) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

            OpDecorate %struct Block
            OpDecorate %struct BufferBlock
            OpMemberDecorate %struct 0 Offset 0
            OpMemberDecorate %struct 0 MatrixStride 16
            OpMemberDecorate %struct 0 RowMajor

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
   %fvec4 = OpTypeVector %float 4
   %fmat4 = OpTypeMatrix %fvec4 4
  %struct = OpTypeStruct %fmat4

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateAndRetrieveValidationState());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "ID '2' decorated with both BufferBlock and Block is not allowed."));
}

}  // namespace
}  // namespace val
}  // namespace spvtools

// Copyright (c) 2018 Google Inc.
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

// Validation tests for memory/storage

#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "test/unit_spirv.h"
#include "test/val/val_fixtures.h"

namespace spvtools {
namespace val {
namespace {

using ::testing::Eq;
using ::testing::HasSubstr;

using ValidateMemory = spvtest::ValidateBase<bool>;

TEST_F(ValidateMemory, VulkanUniformConstantOnNonOpaqueResourceBad) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer UniformConstant %float
%2 = OpVariable %float_ptr UniformConstant
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("From Vulkan spec, section 14.5.2:\n"
                "Variables identified with the UniformConstant storage class "
                "are used only as handles to refer to opaque resources. Such "
                "variables must be typed as OpTypeImage, OpTypeSampler, "
                "OpTypeSampledImage, OpTypeAccelerationStructureNV, or an "
                "array of one of these types."));
}

TEST_F(ValidateMemory, VulkanUniformConstantOnOpaqueResourceGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
OpDecorate %2 DescriptorSet 0
OpDecorate %2 Binding 0
%sampler = OpTypeSampler
%sampler_ptr = OpTypePointer UniformConstant %sampler
%2 = OpVariable %sampler_ptr UniformConstant
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanUniformConstantOnNonOpaqueResourceArrayBad) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%uint = OpTypeInt 32 0
%array_size = OpConstant %uint 5
%array = OpTypeArray %float %array_size
%array_ptr = OpTypePointer UniformConstant %array
%2 = OpVariable %array_ptr UniformConstant
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("From Vulkan spec, section 14.5.2:\n"
                "Variables identified with the UniformConstant storage class "
                "are used only as handles to refer to opaque resources. Such "
                "variables must be typed as OpTypeImage, OpTypeSampler, "
                "OpTypeSampledImage, OpTypeAccelerationStructureNV, or an "
                "array of one of these types."));
}

TEST_F(ValidateMemory, VulkanUniformConstantOnOpaqueResourceArrayGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
OpDecorate %2 DescriptorSet 0
OpDecorate %2 Binding 0
%sampler = OpTypeSampler
%uint = OpTypeInt 32 0
%array_size = OpConstant %uint 5
%array = OpTypeArray %sampler %array_size
%array_ptr = OpTypePointer UniformConstant %array
%2 = OpVariable %array_ptr UniformConstant
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanUniformConstantOnOpaqueResourceRuntimeArrayGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
OpDecorate %2 DescriptorSet 0
OpDecorate %2 Binding 0
%sampler = OpTypeSampler
%uint = OpTypeInt 32 0
%array = OpTypeRuntimeArray %sampler
%array_ptr = OpTypePointer UniformConstant %array
%2 = OpVariable %array_ptr UniformConstant
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanUniformOnIntBad) {
  char src[] = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint GLCompute %kernel "main"
            OpExecutionMode %kernel LocalSize 1 1 1

            OpDecorate %var DescriptorSet 0
            OpDecorate %var Binding 0

  %voidty = OpTypeVoid
%kernelty = OpTypeFunction %voidty
   %intty = OpTypeInt 32 0
   %varty = OpTypePointer Uniform %intty
   %value = OpConstant %intty 42

     %var = OpVariable %varty Uniform

  %kernel = OpFunction %voidty None %kernelty
   %label = OpLabel
            OpStore %var %value
            OpReturn
            OpFunctionEnd
)";
  CompileSuccessfully(src, SPV_ENV_VULKAN_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("From Vulkan spec, section 14.5.2:\n"
                "Variables identified with the Uniform storage class are used "
                "to access transparent buffer backed resources. Such variables "
                "must be typed as OpTypeStruct, or an array of this type"));
}

// #version 440
// #extension GL_EXT_nonuniform_qualifier : enable
// layout(binding = 1) uniform sampler2D s2d[][2];
// layout(location = 0) in nonuniformEXT int i;
// void main()
// {
//     vec4 v = texture(s2d[i][i], vec2(0.3));
// }
TEST_F(ValidateMemory, VulkanUniformOnRuntimeArrayOfArrayBad) {
  char src[] = R"(
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
               OpDecorate %21 NonUniformEXT
               OpDecorate %22 NonUniformEXT
               OpDecorate %25 NonUniformEXT
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
%_ptr_Function_v4float = OpTypePointer Function %v4float
         %10 = OpTypeImage %float 2D 0 0 0 1 Unknown
         %11 = OpTypeSampledImage %10
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_11_uint_2 = OpTypeArray %11 %uint_2
%_runtimearr__arr_11_uint_2 = OpTypeRuntimeArray %_arr_11_uint_2
%_ptr_Uniform__runtimearr__arr_11_uint_2 = OpTypePointer Uniform %_runtimearr__arr_11_uint_2
        %s2d = OpVariable %_ptr_Uniform__runtimearr__arr_11_uint_2 Uniform
        %int = OpTypeInt 32 1
%_ptr_Input_int = OpTypePointer Input %int
          %i = OpVariable %_ptr_Input_int Input
%_ptr_Uniform_11 = OpTypePointer Uniform %11
    %v2float = OpTypeVector %float 2
%float_0_300000012 = OpConstant %float 0.300000012
         %28 = OpConstantComposite %v2float %float_0_300000012 %float_0_300000012
    %float_0 = OpConstant %float 0
       %main = OpFunction %void None %3
          %5 = OpLabel
          %v = OpVariable %_ptr_Function_v4float Function
         %21 = OpLoad %int %i
         %22 = OpLoad %int %i
         %24 = OpAccessChain %_ptr_Uniform_11 %s2d %21 %22
         %25 = OpLoad %11 %24
         %30 = OpImageSampleExplicitLod %v4float %25 %28 Lod %float_0
               OpStore %v %30
               OpReturn
               OpFunctionEnd
)";
  CompileSuccessfully(src, SPV_ENV_VULKAN_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("From Vulkan spec, section 14.5.2:\n"
                "Variables identified with the Uniform storage class are used "
                "to access transparent buffer backed resources. Such variables "
                "must be typed as OpTypeStruct, or an array of this type"));
}

// #version 440
// layout (set=1, binding=1) uniform sampler2D variableName[2][2];
// void main() {
// }
TEST_F(ValidateMemory, VulkanUniformOnArrayOfArrayBad) {
  char src[] = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %main "main"
               OpSource GLSL 440
               OpName %main "main"
               OpName %variableName "variableName"
               OpDecorate %variableName DescriptorSet 1
               OpDecorate %variableName Binding 1
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
          %7 = OpTypeImage %float 2D 0 0 0 1 Unknown
          %8 = OpTypeSampledImage %7
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
%_arr_8_uint_2 = OpTypeArray %8 %uint_2
%_arr__arr_8_uint_2_uint_2 = OpTypeArray %_arr_8_uint_2 %uint_2
%_ptr_Uniform__arr__arr_8_uint_2_uint_2 = OpTypePointer Uniform %_arr__arr_8_uint_2_uint_2
%variableName = OpVariable %_ptr_Uniform__arr__arr_8_uint_2_uint_2 Uniform
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
)";
  CompileSuccessfully(src, SPV_ENV_VULKAN_1_1);
  ASSERT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("From Vulkan spec, section 14.5.2:\n"
                "Variables identified with the Uniform storage class are used "
                "to access transparent buffer backed resources. Such variables "
                "must be typed as OpTypeStruct, or an array of this type"));
}

TEST_F(ValidateMemory, MismatchingStorageClassesBad) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Uniform %float
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
%2 = OpVariable %float_ptr Function
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "From SPIR-V spec, section 3.32.8 on OpVariable:\n"
          "Its Storage Class operand must be the same as the Storage Class "
          "operand of the result type."));
}

TEST_F(ValidateMemory, MatchingStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Function %float
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
%2 = OpVariable %float_ptr Function
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateMemory, WebGPUInitializerWithOutputStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Output %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Output %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_WEBGPU_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_WEBGPU_0));
}

TEST_F(ValidateMemory, WebGPUInitializerWithFunctionStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Function %float
%init_val = OpConstant %float 1.0
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
%2 = OpVariable %float_ptr Function %init_val
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_WEBGPU_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_WEBGPU_0));
}

TEST_F(ValidateMemory, WebGPUInitializerWithPrivateStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Private %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Private %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_WEBGPU_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_WEBGPU_0));
}

TEST_F(ValidateMemory, WebGPUInitializerWithDisallowedStorageClassesBad) {
  std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Uniform %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Uniform %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_WEBGPU_0);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_WEBGPU_0));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "OpVariable, <id> '5[%5]', has a disallowed initializer & storage "
          "class combination.\nFrom WebGPU execution environment spec:\n"
          "Variable declarations that include initializers must have one of "
          "the following storage classes: Output, Private, or Function\n"
          "  %5 = OpVariable %_ptr_Uniform_float Uniform %float_1\n"));
}

TEST_F(ValidateMemory, VulkanInitializerWithOutputStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Output %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Output %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanInitializerWithFunctionStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Function %float
%init_val = OpConstant %float 1.0
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%1 = OpLabel
%2 = OpVariable %float_ptr Function %init_val
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanInitializerWithPrivateStorageClassesGood) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Private %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Private %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanInitializerWithDisallowedStorageClassesBad) {
  std::string spirv = R"(
OpCapability Shader
OpMemoryModel Logical GLSL450
OpEntryPoint Fragment %func "func"
OpExecutionMode %func OriginUpperLeft
%float = OpTypeFloat 32
%float_ptr = OpTypePointer Input %float
%init_val = OpConstant %float 1.0
%1 = OpVariable %float_ptr Input %init_val
%void = OpTypeVoid
%functy = OpTypeFunction %void
%func = OpFunction %void None %functy
%2 = OpLabel
OpReturn
OpFunctionEnd
)";
  CompileSuccessfully(spirv.c_str(), SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "OpVariable, <id> '5[%5]', has a disallowed initializer & storage "
          "class combination.\nFrom Vulkan spec, Appendix A:\n"
          "Variable declarations that include initializers must have one of "
          "the following storage classes: Output, Private, or Function\n  "
          "%5 = OpVariable %_ptr_Input_float Input %float_1\n"));
}

TEST_F(ValidateMemory, ArrayLenCorrectResultType) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %_runtimearr_float
%_ptr_Function__struct_7 = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7 Function
         %11 = OpArrayLength %uint %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateMemory, ArrayLenIndexCorrectWith2Members) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %float %_runtimearr_float
%_ptr_Function__struct_7  = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7  Function
         %11 = OpArrayLength %uint %10 1
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateMemory, ArrayLenResultNotIntType) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_6 = OpTypeStruct %_runtimearr_float
%_ptr_Function__struct_6 = OpTypePointer Function %_struct_6
          %1 = OpFunction %void None %3
          %8 = OpLabel
          %9 = OpVariable %_ptr_Function__struct_6 Function
         %10 = OpArrayLength %float %9 0
               OpReturn
               OpFunctionEnd
)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "The Result Type of OpArrayLength <id> '10[%10]' must be OpTypeInt "
          "with width 32 and signedness 0.\n  %10 = OpArrayLength %float %9 "
          "0\n"));
}

TEST_F(ValidateMemory, ArrayLenResultNot32bits) {
  std::string spirv = R"(
               OpCapability Shader
               OpCapability Int16
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %ushort = OpTypeInt 16 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %_runtimearr_float
%_ptr_Function__struct_7 = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7 Function
         %11 = OpArrayLength %ushort %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "The Result Type of OpArrayLength <id> '11[%11]' must be OpTypeInt "
          "with width 32 and signedness 0.\n  %11 = OpArrayLength %ushort %10 "
          "0\n"));
}

TEST_F(ValidateMemory, ArrayLenResultSigned) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %int = OpTypeInt 32 1
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %_runtimearr_float
%_ptr_Function__struct_7 = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7 Function
         %11 = OpArrayLength %int %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "The Result Type of OpArrayLength <id> '11[%11]' must be OpTypeInt "
          "with width 32 and signedness 0.\n  %11 = OpArrayLength %int %10 "
          "0\n"));
}

TEST_F(ValidateMemory, ArrayLenInputNotStruct) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %_runtimearr_float
%_ptr_Function_float = OpTypePointer Function %float
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function_float Function
         %11 = OpArrayLength %uint %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("The Struture's type in OpArrayLength <id> '11[%11]' "
                        "must be a pointer to an OpTypeStruct."));
}

TEST_F(ValidateMemory, ArrayLenInputLastMemberNoRTA) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %float
%_ptr_Function__struct_7  = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7  Function
         %11 = OpArrayLength %uint %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("The Struture's last member in OpArrayLength <id> '11[%11]' "
                "must be an OpTypeRuntimeArray.\n  %11 = OpArrayLength %uint "
                "%10 0\n"));
}

TEST_F(ValidateMemory, ArrayLenInputLastMemberNoRTA2) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %_runtimearr_float %float
%_ptr_Function__struct_7  = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7  Function
         %11 = OpArrayLength %uint %10 1
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("The Struture's last member in OpArrayLength <id> '11[%11]' "
                "must be an OpTypeRuntimeArray.\n  %11 = OpArrayLength %uint "
                "%10 1\n"));
}

TEST_F(ValidateMemory, ArrayLenIndexNotLastMember) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %float %_runtimearr_float
%_ptr_Function__struct_7  = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7  Function
         %11 = OpArrayLength %uint %10 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "The array member in OpArrayLength <id> '11[%11]' must be an the "
          "last member of the struct.\n  %11 = OpArrayLength %uint %10 0\n"));
}

TEST_F(ValidateMemory, ArrayLenIndexNotPointerToStruct) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
     %uint = OpTypeInt 32 0
%_runtimearr_float = OpTypeRuntimeArray %float
  %_struct_7 = OpTypeStruct %float %_runtimearr_float
%_ptr_Function__struct_7  = OpTypePointer Function %_struct_7
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %10 = OpVariable %_ptr_Function__struct_7  Function
         %11 = OpLoad %_struct_7 %10
         %12 = OpArrayLength %uint %11 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "The Struture's type in OpArrayLength <id> '12[%12]' must be a "
          "pointer to an OpTypeStruct.\n  %12 = OpArrayLength %uint %11 0\n"));
}

TEST_F(ValidateMemory, ArrayLenPointerIsAType) {
  std::string spirv = R"(
               OpCapability Shader
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %1 "main"
               OpExecutionMode %1 OriginUpperLeft
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %uint = OpTypeInt 32 0
          %1 = OpFunction %void None %3
          %9 = OpLabel
         %12 = OpArrayLength %uint %float 0
               OpReturn
               OpFunctionEnd

)";

  CompileSuccessfully(spirv.c_str());
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(), HasSubstr("Operand 4[%float] cannot be a "
                                               "type"));
}

TEST_F(ValidateMemory, PushConstantNotStructGood) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
     %ptr = OpTypePointer PushConstant %float
      %pc = OpVariable %ptr PushConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateMemory, VulkanPushConstantNotStructBad) {
  std::string spirv = R"(
            OpCapability Shader
            OpMemoryModel Logical GLSL450
            OpEntryPoint Fragment %1 "main"
            OpExecutionMode %1 OriginUpperLeft

    %void = OpTypeVoid
  %voidfn = OpTypeFunction %void
   %float = OpTypeFloat 32
     %ptr = OpTypePointer PushConstant %float
      %pc = OpVariable %ptr PushConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";
  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions(SPV_ENV_VULKAN_1_1));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("PushConstant OpVariable <id> '6[%6]' has illegal "
                        "type.\nFrom Vulkan spec, section 14.5.1:\n"
                        "Such variables must be typed as OpTypeStruct, "
                        "or an array of this type"));
}

TEST_F(ValidateMemory, VulkanPushConstant) {
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
  %struct = OpTypeStruct %float
     %ptr = OpTypePointer PushConstant %struct
      %pc = OpVariable %ptr PushConstant

       %1 = OpFunction %void None %voidfn
   %label = OpLabel
            OpReturn
            OpFunctionEnd
)";
  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_1);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_1));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeLoadBad1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
%load = OpLoad %int %var MakePointerVisibleKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeLoadBad2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
%load = OpLoad %int %var Aligned|MakePointerVisibleKHR|NonPrivatePointerKHR 4 %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeLoadGood1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
%load = OpLoad %int %var MakePointerVisibleKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeLoadGood2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
%load = OpLoad %int %var Aligned|MakePointerVisibleKHR|NonPrivatePointerKHR 4 %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeStoreBad1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpStore %var %device MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeStoreBad2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpStore %var %device Aligned|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeStoreGood1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpStore %var %device MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeStoreGood2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpStore %var %device Aligned|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryBad1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryBad2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device %workgroup
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryBad3) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %workgroup %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryGood1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryGood2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 2
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device %workgroup
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemoryGood3) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 2
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemory %var1 %var2 Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %workgroup %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedBad1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedBad2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device %workgroup
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedBad3) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %workgroup %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_ERROR_INVALID_DATA,
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Use of device scope with VulkanKHR memory model requires the "
                "VulkanMemoryModelDeviceScopeKHR capability"));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedGood1) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device MakePointerAvailableKHR|NonPrivatePointerKHR %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedGood2) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 2
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %device %workgroup
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, VulkanMemoryModelDeviceScopeCopyMemorySizedGood3) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability VulkanMemoryModelKHR
OpCapability VulkanMemoryModelDeviceScopeKHR
OpCapability Linkage
OpCapability Addresses
OpExtension "SPV_KHR_vulkan_memory_model"
OpMemoryModel Logical VulkanKHR
%void = OpTypeVoid
%int = OpTypeInt 32 0
%device = OpConstant %int 1
%workgroup = OpConstant %int 2
%int_ptr_ssbo = OpTypePointer StorageBuffer %int
%var1 = OpVariable %int_ptr_ssbo StorageBuffer
%var2 = OpVariable %int_ptr_ssbo StorageBuffer
%voidfn = OpTypeFunction %void
%func = OpFunction %void None %voidfn
%entry = OpLabel
OpCopyMemorySized %var1 %var2 %device Aligned|MakePointerVisibleKHR|MakePointerAvailableKHR|NonPrivatePointerKHR 4 %workgroup %device
OpReturn
OpFunctionEnd
)";

  CompileSuccessfully(spirv, SPV_ENV_UNIVERSAL_1_3);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_UNIVERSAL_1_3));
}

TEST_F(ValidateMemory, ArrayLengthStructIsLabel) {
  const std::string spirv = R"(
OpCapability Tessellation
OpMemoryModel Logical GLSL450
OpName %20 "incorrect"
%void = OpTypeVoid
%3 = OpTypeFunction %void
%float = OpTypeFloat 32
%v4float = OpTypeVector %float 4
%uint = OpTypeInt 32 0
%4 = OpFunction %void None %3
%20 = OpLabel
%24 = OpArrayLength %uint %20 0
%25 = OpLoad %v4float %24
OpReturnValue %25
OpFunctionEnd
)";

  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_ID, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Operand 1[%incorrect] requires a type"));
}

}  // namespace
}  // namespace val
}  // namespace spvtools

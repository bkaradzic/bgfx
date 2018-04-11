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

#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include <gmock/gmock.h>

#include "source/assembly_grammar.h"
#include "test_fixture.h"
#include "unit_spirv.h"
#include "val_fixtures.h"

namespace {

using spvtest::ScopedContext;
using std::get;
using std::make_pair;
using std::ostringstream;
using std::pair;
using std::string;
using std::tuple;
using std::vector;
using testing::Combine;
using testing::HasSubstr;
using testing::Values;
using testing::ValuesIn;

// Parameter for validation test fixtures.  The first string is a capability
// name that will begin the assembly under test, the second the remainder
// assembly, and the vector at the end determines whether the test expects
// success or failure.  See below for details and convenience methods to access
// each one.
//
// The assembly to test is composed from a variable top line and a fixed
// remainder.  The top line will be an OpCapability instruction, while the
// remainder will be some assembly text that succeeds or fails to assemble
// depending on which capability was chosen.  For instance, the following will
// succeed:
//
// OpCapability Pipes ; implies Kernel
// OpLifetimeStop %1 0 ; requires Kernel
//
// and the following will fail:
//
// OpCapability Kernel
// %1 = OpTypeNamedBarrier ; requires NamedBarrier
//
// So how does the test parameter capture which capabilities should cause
// success and which shouldn't?  The answer is in the last element: it's a
// vector of capabilities that make the remainder assembly succeed.  So if the
// first-line capability exists in that vector, success is expected; otherwise,
// failure is expected in the tests.
//
// We will use testing::Combine() to vary the first line: when we combine
// AllCapabilities() with a single remainder assembly, we generate enough test
// cases to try the assembly with every possible capability that could be
// declared. However, Combine() only produces tuples -- it cannot produce, say,
// a struct.  Therefore, this type must be a tuple.
using CapTestParameter = tuple<string, pair<string, vector<string>>>;

const string& Capability(const CapTestParameter& p) { return get<0>(p); }
const string& Remainder(const CapTestParameter& p) { return get<1>(p).first; }
const vector<string>& MustSucceed(const CapTestParameter& p) {
  return get<1>(p).second;
}

// Creates assembly to test from p.
string MakeAssembly(const CapTestParameter& p) {
  ostringstream ss;
  const string& capability = Capability(p);
  if (!capability.empty()) {
    ss << "OpCapability " << capability << "\n";
  }
  ss << Remainder(p);
  return ss.str();
}

// Expected validation result for p.
spv_result_t ExpectedResult(const CapTestParameter& p) {
  const auto& caps = MustSucceed(p);
  auto found = find(begin(caps), end(caps), Capability(p));
  return (found == end(caps)) ? SPV_ERROR_INVALID_CAPABILITY : SPV_SUCCESS;
}

// Assembles using v1.0, unless the parameter's capability requires v1.1.
using ValidateCapability = spvtest::ValidateBase<CapTestParameter>;

// Always assembles using v1.1.
using ValidateCapabilityV11 = spvtest::ValidateBase<CapTestParameter>;

// Always assembles using Vulkan 1.0.
// TODO(dneto): Refactor all these tests to scale better across environments.
using ValidateCapabilityVulkan10 = spvtest::ValidateBase<CapTestParameter>;
// Always assembles using OpenGL 4.0.
using ValidateCapabilityOpenGL40 = spvtest::ValidateBase<CapTestParameter>;

TEST_F(ValidateCapability, Default) {
  const char str[] = R"(
            OpCapability Kernel
            OpCapability Linkage
            OpCapability Matrix
            OpMemoryModel Logical OpenCL
%f32      = OpTypeFloat 32
%vec3     = OpTypeVector %f32 3
%mat33    = OpTypeMatrix %vec3 3
)";

  CompileSuccessfully(str);
  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

// clang-format off
const vector<string>& AllCapabilities() {
  static const auto r = new vector<string>{
    "",
    "Matrix",
    "Shader",
    "Geometry",
    "Tessellation",
    "Addresses",
    "Linkage",
    "Kernel",
    "Vector16",
    "Float16Buffer",
    "Float16",
    "Float64",
    "Int64",
    "Int64Atomics",
    "ImageBasic",
    "ImageReadWrite",
    "ImageMipmap",
    "Pipes",
    "Groups",
    "DeviceEnqueue",
    "LiteralSampler",
    "AtomicStorage",
    "Int16",
    "TessellationPointSize",
    "GeometryPointSize",
    "ImageGatherExtended",
    "StorageImageMultisample",
    "UniformBufferArrayDynamicIndexing",
    "SampledImageArrayDynamicIndexing",
    "StorageBufferArrayDynamicIndexing",
    "StorageImageArrayDynamicIndexing",
    "ClipDistance",
    "CullDistance",
    "ImageCubeArray",
    "SampleRateShading",
    "ImageRect",
    "SampledRect",
    "GenericPointer",
    "Int8",
    "InputAttachment",
    "SparseResidency",
    "MinLod",
    "Sampled1D",
    "Image1D",
    "SampledCubeArray",
    "SampledBuffer",
    "ImageBuffer",
    "ImageMSArray",
    "StorageImageExtendedFormats",
    "ImageQuery",
    "DerivativeControl",
    "InterpolationFunction",
    "TransformFeedback",
    "GeometryStreams",
    "StorageImageReadWithoutFormat",
    "StorageImageWriteWithoutFormat",
    "MultiViewport",
    "SubgroupDispatch",
    "NamedBarrier",
    "PipeStorage"};
  return *r;
}

const vector<string>& AllSpirV10Capabilities() {
  static const auto r = new vector<string>{
    "",
    "Matrix",
    "Shader",
    "Geometry",
    "Tessellation",
    "Addresses",
    "Linkage",
    "Kernel",
    "Vector16",
    "Float16Buffer",
    "Float16",
    "Float64",
    "Int64",
    "Int64Atomics",
    "ImageBasic",
    "ImageReadWrite",
    "ImageMipmap",
    "Pipes",
    "Groups",
    "DeviceEnqueue",
    "LiteralSampler",
    "AtomicStorage",
    "Int16",
    "TessellationPointSize",
    "GeometryPointSize",
    "ImageGatherExtended",
    "StorageImageMultisample",
    "UniformBufferArrayDynamicIndexing",
    "SampledImageArrayDynamicIndexing",
    "StorageBufferArrayDynamicIndexing",
    "StorageImageArrayDynamicIndexing",
    "ClipDistance",
    "CullDistance",
    "ImageCubeArray",
    "SampleRateShading",
    "ImageRect",
    "SampledRect",
    "GenericPointer",
    "Int8",
    "InputAttachment",
    "SparseResidency",
    "MinLod",
    "Sampled1D",
    "Image1D",
    "SampledCubeArray",
    "SampledBuffer",
    "ImageBuffer",
    "ImageMSArray",
    "StorageImageExtendedFormats",
    "ImageQuery",
    "DerivativeControl",
    "InterpolationFunction",
    "TransformFeedback",
    "GeometryStreams",
    "StorageImageReadWithoutFormat",
    "StorageImageWriteWithoutFormat",
    "MultiViewport"};
  return *r;
}

const vector<string>& AllVulkan10Capabilities() {
  static const auto r = new vector<string>{
    "",
    "Matrix",
    "Shader",
    "InputAttachment",
    "Sampled1D",
    "Image1D",
    "SampledBuffer",
    "ImageBuffer",
    "ImageQuery",
    "DerivativeControl",
    "Geometry",
    "Tessellation",
    "Float64",
    "Int64",
    "Int16",
    "TessellationPointSize",
    "GeometryPointSize",
    "ImageGatherExtended",
    "StorageImageMultisample",
    "UniformBufferArrayDynamicIndexing",
    "SampledImageArrayDynamicIndexing",
    "StorageBufferArrayDynamicIndexing",
    "StorageImageArrayDynamicIndexing",
    "ClipDistance",
    "CullDistance",
    "ImageCubeArray",
    "SampleRateShading",
    "SparseResidency",
    "MinLod",
    "SampledCubeArray",
    "ImageMSArray",
    "StorageImageExtendedFormats",
    "InterpolationFunction",
    "StorageImageReadWithoutFormat",
    "StorageImageWriteWithoutFormat",
    "MultiViewport"};
  return *r;
}

const vector<string>& MatrixDependencies() {
  static const auto r = new vector<string>{
  "Matrix",
  "Shader",
  "Geometry",
  "Tessellation",
  "AtomicStorage",
  "TessellationPointSize",
  "GeometryPointSize",
  "ImageGatherExtended",
  "StorageImageMultisample",
  "UniformBufferArrayDynamicIndexing",
  "SampledImageArrayDynamicIndexing",
  "StorageBufferArrayDynamicIndexing",
  "StorageImageArrayDynamicIndexing",
  "ClipDistance",
  "CullDistance",
  "ImageCubeArray",
  "SampleRateShading",
  "ImageRect",
  "SampledRect",
  "InputAttachment",
  "SparseResidency",
  "MinLod",
  "SampledCubeArray",
  "ImageMSArray",
  "StorageImageExtendedFormats",
  "ImageQuery",
  "DerivativeControl",
  "InterpolationFunction",
  "TransformFeedback",
  "GeometryStreams",
  "StorageImageReadWithoutFormat",
  "StorageImageWriteWithoutFormat",
  "MultiViewport"};
  return *r;
}

const vector<string>& ShaderDependencies() {
  static const auto r = new vector<string>{
  "Shader",
  "Geometry",
  "Tessellation",
  "AtomicStorage",
  "TessellationPointSize",
  "GeometryPointSize",
  "ImageGatherExtended",
  "StorageImageMultisample",
  "UniformBufferArrayDynamicIndexing",
  "SampledImageArrayDynamicIndexing",
  "StorageBufferArrayDynamicIndexing",
  "StorageImageArrayDynamicIndexing",
  "ClipDistance",
  "CullDistance",
  "ImageCubeArray",
  "SampleRateShading",
  "ImageRect",
  "SampledRect",
  "InputAttachment",
  "SparseResidency",
  "MinLod",
  "SampledCubeArray",
  "ImageMSArray",
  "StorageImageExtendedFormats",
  "ImageQuery",
  "DerivativeControl",
  "InterpolationFunction",
  "TransformFeedback",
  "GeometryStreams",
  "StorageImageReadWithoutFormat",
  "StorageImageWriteWithoutFormat",
  "MultiViewport"};
  return *r;
}

const vector<string>& TessellationDependencies() {
  static const auto r = new vector<string>{
  "Tessellation",
  "TessellationPointSize"};
  return *r;
}

const vector<string>& GeometryDependencies() {
  static const auto r = new vector<string>{
  "Geometry",
  "GeometryPointSize",
  "GeometryStreams",
  "MultiViewport"};
  return *r;
}

const vector<string>& GeometryTessellationDependencies() {
  static const auto r = new vector<string>{
  "Tessellation",
  "TessellationPointSize",
  "Geometry",
  "GeometryPointSize",
  "GeometryStreams",
  "MultiViewport"};
  return *r;
}

// Returns the names of capabilities that directly depend on Kernel,
// plus itself.
const vector<string>& KernelDependencies() {
  static const auto r = new vector<string>{
  "Kernel",
  "Vector16",
  "Float16Buffer",
  "ImageBasic",
  "ImageReadWrite",
  "ImageMipmap",
  "Pipes",
  "DeviceEnqueue",
  "LiteralSampler",
  "Int8",
  "SubgroupDispatch",
  "NamedBarrier",
  "PipeStorage"};
  return *r;
}

const vector<string>& AddressesDependencies() {
  static const auto r = new vector<string>{
  "Addresses",
  "GenericPointer"};
  return *r;
}

const vector<string>& Sampled1DDependencies() {
  static const auto r = new vector<string>{
  "Sampled1D",
  "Image1D"};
  return *r;
}

const vector<string>& SampledRectDependencies() {
  static const auto r = new vector<string>{
  "SampledRect",
  "ImageRect"};
  return *r;
}

const vector<string>& SampledBufferDependencies() {
  static const auto r = new vector<string>{
  "SampledBuffer",
  "ImageBuffer"};
  return *r;
}

const char kOpenCLMemoryModel[] = \
  " OpCapability Kernel"
  " OpMemoryModel Logical OpenCL ";

const char kGLSL450MemoryModel[] = \
  " OpCapability Shader"
  " OpMemoryModel Logical GLSL450 ";

const char kVoidFVoid[] = \
  " %void   = OpTypeVoid"
  " %void_f = OpTypeFunction %void"
  " %func   = OpFunction %void None %void_f"
  " %label  = OpLabel"
  "           OpReturn"
  "           OpFunctionEnd ";

const char kVoidFVoid2[] = \
  " %void_f = OpTypeFunction %voidt"
  " %func   = OpFunction %voidt None %void_f"
  " %label  = OpLabel"
  "           OpReturn"
  "           OpFunctionEnd ";

INSTANTIATE_TEST_CASE_P(ExecutionModel, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint TessellationControl %func \"shader\"" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint TessellationEvaluation %func \"shader\"" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Geometry %func \"shader\"" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Fragment %func \"shader\"" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint GLCompute %func \"shader\"" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Kernel %func \"shader\"" +
          string(kVoidFVoid), KernelDependencies())
)),);

INSTANTIATE_TEST_CASE_P(AddressingAndMemoryModel, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(" OpCapability Shader"
          " OpMemoryModel Logical Simple"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid),     AllCapabilities()),
make_pair(" OpCapability Shader"
          " OpMemoryModel Logical GLSL450"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid),    AllCapabilities()),
make_pair(" OpCapability Kernel"
          " OpMemoryModel Logical OpenCL"
          " OpEntryPoint Kernel %func \"compute\"" +
          string(kVoidFVoid),     AllCapabilities()),
make_pair(" OpCapability Shader"
          " OpMemoryModel Physical32 Simple"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid),  AddressesDependencies()),
make_pair(" OpCapability Shader"
          " OpMemoryModel Physical32 GLSL450"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid), AddressesDependencies()),
make_pair(" OpCapability Kernel"
          " OpMemoryModel Physical32 OpenCL"
          " OpEntryPoint Kernel %func \"compute\"" +
          string(kVoidFVoid),  AddressesDependencies()),
make_pair(" OpCapability Shader"
          " OpMemoryModel Physical64 Simple"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid),  AddressesDependencies()),
make_pair(" OpCapability Shader"
          " OpMemoryModel Physical64 GLSL450"
          " OpEntryPoint Vertex %func \"shader\"" +
          string(kVoidFVoid), AddressesDependencies()),
make_pair(" OpCapability Kernel"
          " OpMemoryModel Physical64 OpenCL"
          " OpEntryPoint Kernel %func \"compute\"" +
          string(kVoidFVoid),  AddressesDependencies())
)),);

INSTANTIATE_TEST_CASE_P(ExecutionMode, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func Invocations 42" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func SpacingEqual" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func SpacingFractionalEven" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func SpacingFractionalOdd" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func VertexOrderCw" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func VertexOrderCcw" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func PixelCenterInteger" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func OriginUpperLeft" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func OriginLowerLeft" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func EarlyFragmentTests" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func PointMode" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func Xfb" +
          string(kVoidFVoid), vector<string>{"TransformFeedback"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func DepthReplacing" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func DepthGreater" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func DepthLess" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" "
          "OpExecutionMode %func DepthUnchanged" +
          string(kVoidFVoid), ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"shader\" "
          "OpExecutionMode %func LocalSize 42 42 42" +
          string(kVoidFVoid), AllCapabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Kernel %func \"shader\" "
          "OpExecutionMode %func LocalSizeHint 42 42 42" +
          string(kVoidFVoid), KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func InputPoints" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func InputLines" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func InputLinesAdjacency" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func Triangles" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func Triangles" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func InputTrianglesAdjacency" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func Quads" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func Isolines" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func OutputVertices 42" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint TessellationControl %func \"shader\" "
          "OpExecutionMode %func OutputVertices 42" +
          string(kVoidFVoid), TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func OutputPoints" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func OutputLineStrip" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Geometry %func \"shader\" "
          "OpExecutionMode %func OutputTriangleStrip" +
          string(kVoidFVoid), GeometryDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Kernel %func \"shader\" "
          "OpExecutionMode %func VecTypeHint 2" +
          string(kVoidFVoid), KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Kernel %func \"shader\" "
          "OpExecutionMode %func ContractionOff" +
          string(kVoidFVoid), KernelDependencies()))),);

// clang-format on

INSTANTIATE_TEST_CASE_P(
    ExecutionModeV11, ValidateCapabilityV11,
    Combine(ValuesIn(AllCapabilities()),
            Values(make_pair(string(kOpenCLMemoryModel) +
                                 "OpEntryPoint Kernel %func \"shader\" "
                                 "OpExecutionMode %func SubgroupSize 1" +
                                 string(kVoidFVoid),
                             vector<string>{"SubgroupDispatch"}),
                   make_pair(
                       string(kOpenCLMemoryModel) +
                           "OpEntryPoint Kernel %func \"shader\" "
                           "OpExecutionMode %func SubgroupsPerWorkgroup 65535" +
                           string(kVoidFVoid),
                       vector<string>{"SubgroupDispatch"}))), );
// clang-format off

INSTANTIATE_TEST_CASE_P(StorageClass, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer UniformConstant %intt\n"
          " %var = OpVariable %ptrt UniformConstant\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Kernel %func \"compute\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Input %intt"
          " %var = OpVariable %ptrt Input\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Uniform %intt\n"
          " %var = OpVariable %ptrt Uniform\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Output %intt\n"
          " %var = OpVariable %ptrt Output\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Workgroup %intt\n"
          " %var = OpVariable %ptrt Workgroup\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer CrossWorkgroup %intt\n"
          " %var = OpVariable %ptrt CrossWorkgroup\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Kernel %func \"compute\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Private %intt\n"
          " %var = OpVariable %ptrt Private\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          " OpEntryPoint Kernel %func \"compute\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer PushConstant %intt\n"
          " %var = OpVariable %ptrt PushConstant\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer AtomicCounter %intt\n"
          " %var = OpVariable %ptrt AtomicCounter\n" + string(kVoidFVoid),
          vector<string>{"AtomicStorage"}),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\"" +
          " %intt = OpTypeInt 32 0\n"
          " %ptrt = OpTypePointer Image %intt\n"
          " %var = OpVariable %ptrt Image\n" + string(kVoidFVoid),
          AllCapabilities())
)),);

INSTANTIATE_TEST_CASE_P(Dim, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt 1D 0 0 0 0 Unknown" + string(kVoidFVoid2),
          Sampled1DDependencies()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt 2D 0 0 0 0 Unknown" + string(kVoidFVoid2),
          AllCapabilities()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt 3D 0 0 0 0 Unknown" + string(kVoidFVoid2),
          AllCapabilities()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt Cube 0 0 0 0 Unknown" + string(kVoidFVoid2),
          ShaderDependencies()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt Rect 0 0 0 0 Unknown" + string(kVoidFVoid2),
          SampledRectDependencies()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt Buffer 0 0 0 0 Unknown" + string(kVoidFVoid2),
          SampledBufferDependencies()),
make_pair(" OpCapability ImageBasic" +
          string(kOpenCLMemoryModel) +
          string(" OpEntryPoint Kernel %func \"compute\"") +
          " %voidt = OpTypeVoid"
          " %imgt = OpTypeImage %voidt SubpassData 0 0 0 2 Unknown" + string(kVoidFVoid2),
          vector<string>{"InputAttachment"})
)),);

// NOTE: All Sampler Address Modes require kernel capabilities but the
// OpConstantSampler requires LiteralSampler which depends on Kernel
INSTANTIATE_TEST_CASE_P(SamplerAddressingMode, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\""
          " %samplert = OpTypeSampler"
          " %sampler = OpConstantSampler %samplert None 1 Nearest" +
          string(kVoidFVoid),
          vector<string>{"LiteralSampler"}),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\""
          " %samplert = OpTypeSampler"
          " %sampler = OpConstantSampler %samplert ClampToEdge 1 Nearest" +
          string(kVoidFVoid),
          vector<string>{"LiteralSampler"}),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\""
          " %samplert = OpTypeSampler"
          " %sampler = OpConstantSampler %samplert Clamp 1 Nearest" +
          string(kVoidFVoid),
          vector<string>{"LiteralSampler"}),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\""
          " %samplert = OpTypeSampler"
          " %sampler = OpConstantSampler %samplert Repeat 1 Nearest" +
          string(kVoidFVoid),
          vector<string>{"LiteralSampler"}),
make_pair(string(kGLSL450MemoryModel) +
          " OpEntryPoint Vertex %func \"shader\""
          " %samplert = OpTypeSampler"
          " %sampler = OpConstantSampler %samplert RepeatMirrored 1 Nearest" +
          string(kVoidFVoid),
          vector<string>{"LiteralSampler"})
)),);

//TODO(umar): Sampler Filter Mode
//TODO(umar): Image Format
//TODO(umar): Image Channel Order
//TODO(umar): Image Channel Data Type
//TODO(umar): Image Operands
//TODO(umar): FP Fast Math Mode
//TODO(umar): FP Rounding Mode
//TODO(umar): Linkage Type
//TODO(umar): Access Qualifier
//TODO(umar): Function Parameter Attribute

INSTANTIATE_TEST_CASE_P(Decoration, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt RelaxedPrecision\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Block\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt BufferBlock\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt RowMajor\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          MatrixDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt ColMajor\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          MatrixDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt ArrayStride 1\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt MatrixStride 1\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          MatrixDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt GLSLShared\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt GLSLPacked\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt CPacked\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt NoPerspective\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Flat\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Patch\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Centroid\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Sample\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"SampleRateShading"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Invariant\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Restrict\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Aliased\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Volatile\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt Constant\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Coherent\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt NonWritable\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt NonReadable\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Uniform\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt SaturatedConversion\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Stream 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"GeometryStreams"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Location 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Component 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Index 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Binding 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt DescriptorSet 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt Offset 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt XfbBuffer 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"TransformFeedback"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt XfbStride 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"TransformFeedback"}),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt FuncParamAttr Zext\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt FPFastMathMode Fast\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt LinkageAttributes \"other\" Import\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"Linkage"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt NoContraction\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n"
          "OpDecorate %intt InputAttachmentIndex 0\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"InputAttachment"}),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpDecorate %intt Alignment 4\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies())
)),);

// clang-format on
INSTANTIATE_TEST_CASE_P(
    DecorationSpecId, ValidateCapability,
    Combine(ValuesIn(AllSpirV10Capabilities()),
            Values(make_pair(string(kOpenCLMemoryModel) +
                                 "OpEntryPoint Vertex %func \"shader\" \n" +
                                 "OpDecorate %1 SpecId 1\n"
                                 "%intt = OpTypeInt 32 0\n"
                                 "%1 = OpSpecConstant %intt 0\n" +
                                 string(kVoidFVoid),
                             ShaderDependencies()))), );

INSTANTIATE_TEST_CASE_P(
    DecorationV11, ValidateCapabilityV11,
    Combine(ValuesIn(AllCapabilities()),
            Values(make_pair(string(kOpenCLMemoryModel) +
                                 "OpEntryPoint Kernel %func \"compute\" \n"
                                 "OpDecorate %p MaxByteOffset 0 "
                                 "%i32 = OpTypeInt 32 0 "
                                 "%pi32 = OpTypePointer Workgroup %i32 "
                                 "%p = OpVariable %pi32 Workgroup " +
                                 string(kVoidFVoid),
                             AddressesDependencies()),
                   // Trying to test OpDecorate here, but if this fails due to
                   // incorrect OpMemoryModel validation, that must also be
                   // fixed.
                   make_pair(string("OpMemoryModel Logical OpenCL "
                                    "OpEntryPoint Kernel %func \"compute\" \n"
                                    "OpDecorate %1 SpecId 1 "
                                    "%intt = OpTypeInt 32 0 "
                                    "%1 = OpSpecConstant %intt 0") +
                                 string(kVoidFVoid),
                             KernelDependencies()),
                   make_pair(string("OpMemoryModel Logical Simple "
                                    "OpEntryPoint Vertex %func \"shader\" \n"
                                    "OpDecorate %1 SpecId 1 "
                                    "%intt = OpTypeInt 32 0 "
                                    "%1 = OpSpecConstant %intt 0") +
                                 string(kVoidFVoid),
                             ShaderDependencies()))), );
// clang-format off

INSTANTIATE_TEST_CASE_P(BuiltIn, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn Position\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
// Just mentioning PointSize, ClipDistance, or CullDistance as a BuiltIn does
// not trigger the requirement for the associated capability.
// See https://github.com/KhronosGroup/SPIRV-Tools/issues/365
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn PointSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn ClipDistance\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn CullDistance\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn VertexId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn InstanceId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn PrimitiveId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          GeometryTessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn InvocationId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          GeometryTessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn Layer\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          GeometryDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn ViewportIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"MultiViewport"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn TessLevelOuter\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn TessLevelInner\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn TessCoord\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn PatchVertices\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          TessellationDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn FragCoord\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn PointCoord\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn FrontFacing\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn SampleId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"SampleRateShading"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn SamplePosition\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          vector<string>{"SampleRateShading"}),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn SampleMask\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn FragDepth\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn HelperInvocation\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn VertexIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn InstanceIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn NumWorkgroups\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn WorkgroupSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn WorkgroupId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn LocalInvocationId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn GlobalInvocationId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn LocalInvocationIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllCapabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn WorkDim\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn GlobalSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn EnqueuedWorkgroupSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn GlobalOffset\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn GlobalLinearId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn SubgroupSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn SubgroupMaxSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn NumSubgroups\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn NumEnqueuedSubgroups\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn SubgroupId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn SubgroupLocalInvocationId\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          KernelDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn VertexIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies()),
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "OpDecorate %intt BuiltIn InstanceIndex\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          ShaderDependencies())
)),);

// Ensure that mere mention of PointSize, ClipDistance, or CullDistance as
// BuiltIns does not trigger the requirement for the associated
// capability.
// See https://github.com/KhronosGroup/SPIRV-Tools/issues/365
INSTANTIATE_TEST_CASE_P(BuiltIn, ValidateCapabilityVulkan10,
                        Combine(
                            // All capabilities to try.
                            ValuesIn(AllSpirV10Capabilities()),
                            Values(
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpMemberDecorate %block 0 BuiltIn PointSize\n"
          "%f32 = OpTypeFloat 32\n"
          "%block = OpTypeStruct %f32\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          // Capabilities which should succeed.
          AllVulkan10Capabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpMemberDecorate %block 0 BuiltIn ClipDistance\n"
          "%f32 = OpTypeFloat 32\n"
          "%intt = OpTypeInt 32 0\n"
          "%intt_4 = OpConstant %intt 4\n"
          "%f32arr4 = OpTypeArray %f32 %intt_4\n"
          "%block = OpTypeStruct %f32arr4\n" + string(kVoidFVoid),
          AllVulkan10Capabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n"
          "OpMemberDecorate %block 0 BuiltIn CullDistance\n"
          "%f32 = OpTypeFloat 32\n"
          "%intt = OpTypeInt 32 0\n"
          "%intt_4 = OpConstant %intt 4\n"
          "%f32arr4 = OpTypeArray %f32 %intt_4\n"
          "%block = OpTypeStruct %f32arr4\n" + string(kVoidFVoid),
          AllVulkan10Capabilities())
)),);

INSTANTIATE_TEST_CASE_P(BuiltIn, ValidateCapabilityOpenGL40,
                        Combine(
                            // OpenGL 4.0 is based on SPIR-V 1.0
                            ValuesIn(AllSpirV10Capabilities()),
                            Values(
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn PointSize\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllSpirV10Capabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn ClipDistance\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllSpirV10Capabilities()),
make_pair(string(kGLSL450MemoryModel) +
          "OpEntryPoint Vertex %func \"shader\" \n" +
          "OpDecorate %intt BuiltIn CullDistance\n"
          "%intt = OpTypeInt 32 0\n" + string(kVoidFVoid),
          AllSpirV10Capabilities())
)),);

// TODO(umar): Selection Control
// TODO(umar): Loop Control
// TODO(umar): Function Control
// TODO(umar): Memory Semantics
// TODO(umar): Memory Access
// TODO(umar): Scope
// TODO(umar): Group Operation
// TODO(umar): Kernel Enqueue Flags
// TODO(umar): Kernel Profiling Flags

INSTANTIATE_TEST_CASE_P(MatrixOp, ValidateCapability,
                        Combine(
                            ValuesIn(AllCapabilities()),
                            Values(
make_pair(string(kOpenCLMemoryModel) +
          "OpEntryPoint Kernel %func \"compute\" \n" +
          "%f32      = OpTypeFloat 32\n"
          "%vec3     = OpTypeVector %f32 3\n"
          "%mat33    = OpTypeMatrix %vec3 3\n" + string(kVoidFVoid),
          MatrixDependencies()))),);
// clang-format on

#if 0
// TODO(atgoo@github.com) The following test is not valid as it generates
// invalid combinations of images, instructions and image operands.
//
// Creates assembly containing an OpImageFetch instruction using operands for
// the image-operands part.  The assembly defines constants %fzero and %izero
// that can be used for operands where IDs are required.  The assembly is valid,
// apart from not declaring any capabilities required by the operands.
string ImageOperandsTemplate(const string& operands) {
  ostringstream ss;
  // clang-format off
  ss << R"(
OpCapability Kernel
OpCapability Linkage
OpMemoryModel Logical OpenCL

%i32 = OpTypeInt 32 0
%f32 = OpTypeFloat 32
%v4i32 = OpTypeVector %i32 4
%timg = OpTypeImage %i32 2D 0 0 0 0 Unknown
%pimg = OpTypePointer UniformConstant %timg
%tfun = OpTypeFunction %i32

%vimg = OpVariable %pimg UniformConstant
%izero = OpConstant %i32 0
%fzero = OpConstant %f32 0.

%main = OpFunction %i32 None %tfun
%lbl = OpLabel
%img = OpLoad %timg %vimg
%r1 = OpImageFetch %v4i32 %img %izero )" << operands << R"(
OpReturnValue %izero
OpFunctionEnd
)";
  // clang-format on
  return ss.str();
}

INSTANTIATE_TEST_CASE_P(
    TwoImageOperandsMask, ValidateCapability,
    Combine(
        ValuesIn(AllCapabilities()),
        Values(make_pair(ImageOperandsTemplate("Bias|Lod %fzero %fzero"),
                         ShaderDependencies()),
               make_pair(ImageOperandsTemplate("Lod|Offset %fzero %izero"),
                         vector<string>{"ImageGatherExtended"}),
               make_pair(ImageOperandsTemplate("Sample|MinLod %izero %fzero"),
                         vector<string>{"MinLod"}),
               make_pair(ImageOperandsTemplate("Lod|Sample %fzero %izero"),
                         AllCapabilities()))), );
#endif

// TODO(umar): Instruction capability checks

// True if capability exists in env.
bool Exists(const std::string& capability, spv_target_env env) {
  spv_operand_desc dummy;
  return SPV_SUCCESS == libspirv::AssemblyGrammar(ScopedContext(env).context)
                            .lookupOperand(SPV_OPERAND_TYPE_CAPABILITY,
                                           capability.c_str(),
                                           capability.size(), &dummy);
}

TEST_P(ValidateCapability, Capability) {
  const string capability = Capability(GetParam());
  spv_target_env env =
      (capability.empty() || Exists(capability, SPV_ENV_UNIVERSAL_1_0))
          ? SPV_ENV_UNIVERSAL_1_0
          : SPV_ENV_UNIVERSAL_1_1;
  const string test_code = MakeAssembly(GetParam());
  CompileSuccessfully(test_code, env);
  ASSERT_EQ(ExpectedResult(GetParam()), ValidateInstructions(env))
      << "target env: " << spvTargetEnvDescription(env) << "\ntest code:\n"
      << test_code;
}

TEST_P(ValidateCapabilityV11, Capability) {
  const string test_code = MakeAssembly(GetParam());
  CompileSuccessfully(test_code, SPV_ENV_UNIVERSAL_1_1);
  ASSERT_EQ(ExpectedResult(GetParam()),
            ValidateInstructions(SPV_ENV_UNIVERSAL_1_1))
      << test_code;
}

TEST_P(ValidateCapabilityVulkan10, Capability) {
  const string test_code = MakeAssembly(GetParam());
  CompileSuccessfully(test_code, SPV_ENV_VULKAN_1_0);
  ASSERT_EQ(ExpectedResult(GetParam()),
            ValidateInstructions(SPV_ENV_VULKAN_1_0))
      << test_code;
}

TEST_P(ValidateCapabilityOpenGL40, Capability) {
  const string test_code = MakeAssembly(GetParam());
  CompileSuccessfully(test_code, SPV_ENV_OPENGL_4_0);
  ASSERT_EQ(ExpectedResult(GetParam()),
            ValidateInstructions(SPV_ENV_OPENGL_4_0))
      << test_code;
}

TEST_F(ValidateCapability, SemanticsIdIsAnIdNotALiteral) {
  // From https://github.com/KhronosGroup/SPIRV-Tools/issues/248
  // The validator was interpreting the memory semantics ID number
  // as the value to be checked rather than an ID that references
  // another value to be checked.
  // In this case a raw ID of 64 was mistaken to mean a literal
  // semantic value of UniformMemory, which would require the Shader
  // capability.
  const char str[] = R"(
OpCapability Kernel
OpCapability Linkage
OpMemoryModel Logical OpenCL

;  %i32 has ID 1
%i32    = OpTypeInt 32 0
%tf     = OpTypeFunction %i32
%pi32   = OpTypePointer CrossWorkgroup %i32
%var    = OpVariable %pi32 CrossWorkgroup
%c      = OpConstant %i32 100
%scope  = OpConstant %i32 1 ; Device scope

; Fake an instruction with 64 as the result id.
; !64 = OpConstantNull %i32
!0x3002e !1 !64

%f = OpFunction %i32 None %tf
%l = OpLabel
%result = OpAtomicIAdd %i32 %var %scope !64 %c
OpReturnValue %result
OpFunctionEnd
)";

  CompileSuccessfully(str);

  // Since we are forcing usage of <id> 64, the "id bound" in the binary header
  // must be overwritten so that <id> 64 is considered within bound.
  // ID Bound is at index 3 of the binary. Set it to 65.
  OverwriteAssembledBinary(3, 65);

  ASSERT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateCapability, IntSignednessKernelGood) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Linkage
OpMemoryModel Logical OpenCL
%i32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateCapability, IntSignednessKernelBad) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Linkage
OpMemoryModel Logical OpenCL
%i32    = OpTypeInt 32 1
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_ERROR_INVALID_BINARY, ValidateInstructions());
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("The Signedness in OpTypeInt must always be 0 when "
                        "Kernel capability is used."));
}

TEST_F(ValidateCapability, IntSignednessShaderGood) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%u32    = OpTypeInt 32 0
%i32    = OpTypeInt 32 1
)";
  CompileSuccessfully(spirv);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions());
}

TEST_F(ValidateCapability, NonVulkan10Capability) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability Linkage
OpMemoryModel Logical GLSL450
%u32    = OpTypeInt 32 0
%i32    = OpTypeInt 32 1
)";
  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Linkage is not allowed by Vulkan 1.0"));
}

TEST_F(ValidateCapability, Vulkan10EnabledByExtension) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability DrawParameters
OpExtension "SPV_KHR_shader_draw_parameters"
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %func "shader"
OpMemberDecorate %block 0 BuiltIn PointSize
%f32 = OpTypeFloat 32
%block = OpTypeStruct %f32
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_VULKAN_1_0));
}

TEST_F(ValidateCapability, Vulkan10NotEnabledByExtension) {
  const std::string spirv = R"(
OpCapability Shader
OpCapability DrawParameters
OpMemoryModel Logical GLSL450
OpEntryPoint Vertex %func "shader"
OpDecorate %intt BuiltIn PointSize
%intt = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_VULKAN_1_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_VULKAN_1_0));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Capability DrawParameters is not allowed by Vulkan 1.0"));
}

TEST_F(ValidateCapability, NonOpenCL12FullCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Pipes
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_1_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_1_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Capability Pipes is not allowed by OpenCL 1.2 Full Profile"));
}

TEST_F(ValidateCapability, OpenCL12FullEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_1_2);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_1_2));
}

TEST_F(ValidateCapability, OpenCL12FullNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_1_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_1_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Capability Sampled1D is not allowed by OpenCL 1.2 Full Profile"));
}

TEST_F(ValidateCapability, NonOpenCL12EmbeddedCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Int64
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_1_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_1_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Capability Int64 is not allowed by OpenCL 1.2 Embedded Profile"));
}

TEST_F(ValidateCapability, OpenCL12EmbeddedEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_1_2);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_1_2));
}

TEST_F(ValidateCapability, OpenCL12EmbeddedNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_1_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_1_2));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Sampled1D is not allowed by OpenCL 1.2 "
                        "Embedded Profile"));
}

TEST_F(ValidateCapability, OpenCL20FullCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Pipes
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_2_0));
}

TEST_F(ValidateCapability, NonOpenCL20FullCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Matrix
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_2_0));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Capability Matrix is not allowed by OpenCL 2.0/2.1 Full Profile"));
}

TEST_F(ValidateCapability, OpenCL20FullEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_2_0));
}

TEST_F(ValidateCapability, OpenCL20FullNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_2_0));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Sampled1D is not allowed by OpenCL 2.0/2.1 "
                        "Full Profile"));
}

TEST_F(ValidateCapability, NonOpenCL20EmbeddedCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Int64
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_0));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Int64 is not allowed by OpenCL 2.0/2.1 "
                        "Embedded Profile"));
}

TEST_F(ValidateCapability, OpenCL20EmbeddedEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_0);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_0));
}

TEST_F(ValidateCapability, OpenCL20EmbeddedNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_0);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_0));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Sampled1D is not allowed by OpenCL 2.0/2.1 "
                        "Embedded Profile"));
}

TEST_F(ValidateCapability, OpenCL22FullCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability PipeStorage
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_2);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_2_2));
}

TEST_F(ValidateCapability, NonOpenCL22FullCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Matrix
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_2_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr("Capability Matrix is not allowed by OpenCL 2.2 Full Profile"));
}

TEST_F(ValidateCapability, OpenCL22FullEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_2);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_2_2));
}

TEST_F(ValidateCapability, OpenCL22FullNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_2_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_2_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Capability Sampled1D is not allowed by OpenCL 2.2 Full Profile"));
}

TEST_F(ValidateCapability, NonOpenCL22EmbeddedCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Int64
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)";
  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_2));
  EXPECT_THAT(
      getDiagnosticString(),
      HasSubstr(
          "Capability Int64 is not allowed by OpenCL 2.2 Embedded Profile"));
}

TEST_F(ValidateCapability, OpenCL22EmbeddedEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability ImageBasic
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_2);
  EXPECT_EQ(SPV_SUCCESS, ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_2));
}

TEST_F(ValidateCapability, OpenCL22EmbeddedNotEnabledByCapability) {
  const std::string spirv = R"(
OpCapability Kernel
OpCapability Addresses
OpCapability Linkage
OpCapability Sampled1D
OpMemoryModel Physical64 OpenCL
%u32    = OpTypeInt 32 0
)" + string(kVoidFVoid);

  CompileSuccessfully(spirv, SPV_ENV_OPENCL_EMBEDDED_2_2);
  EXPECT_EQ(SPV_ERROR_INVALID_CAPABILITY,
            ValidateInstructions(SPV_ENV_OPENCL_EMBEDDED_2_2));
  EXPECT_THAT(getDiagnosticString(),
              HasSubstr("Capability Sampled1D is not allowed by OpenCL 2.2 "
                        "Embedded Profile"));
}

}  // namespace

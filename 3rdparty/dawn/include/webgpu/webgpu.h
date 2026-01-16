// BSD 3-Clause License
//
// Copyright (c) 2019, "WebGPU native" developers
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifdef __EMSCRIPTEN__
#error "Do not include this header. Emscripten already provides headers needed for WebGPU."
#endif

#ifndef WEBGPU_H_
#define WEBGPU_H_

#if defined(WGPU_SHARED_LIBRARY)
#    if defined(_WIN32)
#        if defined(WGPU_IMPLEMENTATION)
#            define WGPU_EXPORT __declspec(dllexport)
#        else
#            define WGPU_EXPORT __declspec(dllimport)
#        endif
#    else  // defined(_WIN32)
#        if defined(WGPU_IMPLEMENTATION)
#            define WGPU_EXPORT __attribute__((visibility("default")))
#        else
#            define WGPU_EXPORT
#        endif
#    endif  // defined(_WIN32)
#else       // defined(WGPU_SHARED_LIBRARY)
#    define WGPU_EXPORT
#endif  // defined(WGPU_SHARED_LIBRARY)

#if !defined(WGPU_OBJECT_ATTRIBUTE)
#define WGPU_OBJECT_ATTRIBUTE
#endif
#if !defined(WGPU_ENUM_ATTRIBUTE)
#define WGPU_ENUM_ATTRIBUTE
#endif
#if !defined(WGPU_STRUCTURE_ATTRIBUTE)
#define WGPU_STRUCTURE_ATTRIBUTE
#endif
#if !defined(WGPU_FUNCTION_ATTRIBUTE)
#define WGPU_FUNCTION_ATTRIBUTE
#endif
#if !defined(WGPU_NULLABLE)
#define WGPU_NULLABLE
#endif

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#define _wgpu_COMMA ,
#if defined(__cplusplus)
#  define _wgpu_ENUM_ZERO_INIT(type) type(0)
#  define _wgpu_STRUCT_ZERO_INIT {}
#  if __cplusplus >= 201103L
#    define _wgpu_MAKE_INIT_STRUCT(type, value) (type value)
#  else
#    define _wgpu_MAKE_INIT_STRUCT(type, value) value
#  endif
#else
#  define _wgpu_ENUM_ZERO_INIT(type) (type)0
#  define _wgpu_STRUCT_ZERO_INIT {0}
#  if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define _wgpu_MAKE_INIT_STRUCT(type, value) ((type) value)
#  else
#    define _wgpu_MAKE_INIT_STRUCT(type, value) value
#  endif
#endif

#define WGPU_TRUE (UINT32_C(1))
#define WGPU_FALSE (UINT32_C(0))
#define WGPU_ARRAY_LAYER_COUNT_UNDEFINED (UINT32_MAX)
#define WGPU_COPY_STRIDE_UNDEFINED (UINT32_MAX)
#define WGPU_DEPTH_CLEAR_VALUE_UNDEFINED (NAN)
#define WGPU_DEPTH_SLICE_UNDEFINED (UINT32_MAX)
#define WGPU_INVALID_BINDING (UINT32_MAX)
#define WGPU_LIMIT_U32_UNDEFINED (UINT32_MAX)
#define WGPU_LIMIT_U64_UNDEFINED (UINT64_MAX)
#define WGPU_MIP_LEVEL_COUNT_UNDEFINED (UINT32_MAX)
#define WGPU_QUERY_SET_INDEX_UNDEFINED (UINT32_MAX)
#define WGPU_STRLEN (SIZE_MAX)
#define WGPU_WHOLE_MAP_SIZE (SIZE_MAX)
#define WGPU_WHOLE_SIZE (UINT64_MAX)

typedef struct WGPUStringView {
    WGPU_NULLABLE char const * data;
    size_t length;
} WGPUStringView WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STRING_VIEW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStringView, { \
    /*.data=*/NULL _wgpu_COMMA \
    /*.length=*/WGPU_STRLEN _wgpu_COMMA \
})

typedef uint64_t WGPUFlags;
typedef uint32_t WGPUBool;

typedef struct WGPUAdapterImpl* WGPUAdapter WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBindGroupImpl* WGPUBindGroup WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBindGroupLayoutImpl* WGPUBindGroupLayout WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBufferImpl* WGPUBuffer WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUCommandBufferImpl* WGPUCommandBuffer WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUComputePipelineImpl* WGPUComputePipeline WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUDeviceImpl* WGPUDevice WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUExternalTextureImpl* WGPUExternalTexture WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUInstanceImpl* WGPUInstance WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUPipelineLayoutImpl* WGPUPipelineLayout WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUQuerySetImpl* WGPUQuerySet WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUQueueImpl* WGPUQueue WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderBundleImpl* WGPURenderBundle WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderPipelineImpl* WGPURenderPipeline WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUResourceTableImpl* WGPUResourceTable WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSamplerImpl* WGPUSampler WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUShaderModuleImpl* WGPUShaderModule WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSharedBufferMemoryImpl* WGPUSharedBufferMemory WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSharedFenceImpl* WGPUSharedFence WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSharedTextureMemoryImpl* WGPUSharedTextureMemory WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSurfaceImpl* WGPUSurface WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTexelBufferViewImpl* WGPUTexelBufferView WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureImpl* WGPUTexture WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureViewImpl* WGPUTextureView WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUCommandEncoderImpl* WGPUCommandEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUComputePassEncoderImpl* WGPUComputePassEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderBundleEncoderImpl* WGPURenderBundleEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderPassEncoderImpl* WGPURenderPassEncoder WGPU_OBJECT_ATTRIBUTE;

// Structure forward declarations
struct WGPUAdapterPropertiesD3D;
struct WGPUAdapterPropertiesVk;
struct WGPUAdapterPropertiesWGPU;
struct WGPUBindingResource;
struct WGPUBlendComponent;
struct WGPUBufferBindingLayout;
struct WGPUBufferHostMappedPointer;
struct WGPUColor;
struct WGPUColorTargetStateExpandResolveTextureDawn;
struct WGPUCommandBufferDescriptor;
struct WGPUCompatibilityModeLimits;
struct WGPUConstantEntry;
struct WGPUCopyTextureForBrowserOptions;
struct WGPUDawnAdapterPropertiesPowerPreference;
struct WGPUDawnBufferDescriptorErrorInfoFromWireClient;
struct WGPUDawnCacheDeviceDescriptor;
struct WGPUDawnCompilationMessageUtf16;
struct WGPUDawnConsumeAdapterDescriptor;
struct WGPUDawnDeviceAllocatorControl;
struct WGPUDawnDrmFormatProperties;
struct WGPUDawnEncoderInternalUsageDescriptor;
struct WGPUDawnFakeBufferOOMForTesting;
struct WGPUDawnFakeDeviceInitializeErrorForTesting;
struct WGPUDawnHostMappedPointerLimits;
struct WGPUDawnInjectedInvalidSType;
struct WGPUDawnRenderPassColorAttachmentRenderToSingleSampled;
struct WGPUDawnShaderModuleSPIRVOptionsDescriptor;
struct WGPUDawnTexelCopyBufferRowAlignmentLimits;
struct WGPUDawnTextureInternalUsageDescriptor;
struct WGPUDawnTogglesDescriptor;
struct WGPUDawnWGSLBlocklist;
struct WGPUDawnWireWGSLControl;
struct WGPUEmscriptenSurfaceSourceCanvasHTMLSelector;
struct WGPUExtent2D;
struct WGPUExtent3D;
struct WGPUExternalTextureBindingEntry;
struct WGPUExternalTextureBindingLayout;
struct WGPUFuture;
struct WGPUInstanceLimits;
struct WGPUINTERNAL_HAVE_EMDAWNWEBGPU_HEADER;
struct WGPUMemoryHeapInfo;
struct WGPUMultisampleState;
struct WGPUOrigin2D;
struct WGPUOrigin3D;
struct WGPUPassTimestampWrites;
struct WGPUPipelineLayoutResourceTable;
struct WGPUPipelineLayoutStorageAttachment;
struct WGPUPrimitiveState;
struct WGPUQuerySetDescriptor;
struct WGPUQueueDescriptor;
struct WGPURenderBundleDescriptor;
struct WGPURenderBundleEncoderDescriptor;
struct WGPURenderPassDepthStencilAttachment;
struct WGPURenderPassDescriptorExpandResolveRect;
struct WGPURenderPassDescriptorResolveRect;
struct WGPURenderPassMaxDrawCount;
struct WGPURequestAdapterWebGPUBackendOptions;
struct WGPURequestAdapterWebXROptions;
struct WGPUResourceTableDescriptor;
struct WGPUResourceTableLimits;
struct WGPUSamplerBindingLayout;
struct WGPUShaderModuleCompilationOptions;
struct WGPUShaderSourceSPIRV;
struct WGPUShaderSourceWGSL;
struct WGPUSharedBufferMemoryBeginAccessDescriptor;
struct WGPUSharedBufferMemoryDescriptor;
struct WGPUSharedBufferMemoryEndAccessState;
struct WGPUSharedBufferMemoryProperties;
struct WGPUSharedFenceDXGISharedHandleDescriptor;
struct WGPUSharedFenceDXGISharedHandleExportInfo;
struct WGPUSharedFenceEGLSyncDescriptor;
struct WGPUSharedFenceEGLSyncExportInfo;
struct WGPUSharedFenceMTLSharedEventDescriptor;
struct WGPUSharedFenceMTLSharedEventExportInfo;
struct WGPUSharedFenceSyncFDDescriptor;
struct WGPUSharedFenceSyncFDExportInfo;
struct WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor;
struct WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo;
struct WGPUSharedFenceVkSemaphoreZirconHandleDescriptor;
struct WGPUSharedFenceVkSemaphoreZirconHandleExportInfo;
struct WGPUSharedTextureMemoryAHardwareBufferDescriptor;
struct WGPUSharedTextureMemoryD3D11BeginState;
struct WGPUSharedTextureMemoryD3DSwapchainBeginState;
struct WGPUSharedTextureMemoryDmaBufPlane;
struct WGPUSharedTextureMemoryDXGISharedHandleDescriptor;
struct WGPUSharedTextureMemoryEGLImageDescriptor;
struct WGPUSharedTextureMemoryIOSurfaceDescriptor;
struct WGPUSharedTextureMemoryOpaqueFDDescriptor;
struct WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor;
struct WGPUSharedTextureMemoryVkImageLayoutBeginState;
struct WGPUSharedTextureMemoryVkImageLayoutEndState;
struct WGPUSharedTextureMemoryZirconHandleDescriptor;
struct WGPUStaticSamplerBindingLayout;
struct WGPUStencilFaceState;
struct WGPUStorageTextureBindingLayout;
struct WGPUSubgroupMatrixConfig;
struct WGPUSupportedFeatures;
struct WGPUSupportedInstanceFeatures;
struct WGPUSupportedWGSLLanguageFeatures;
struct WGPUSurfaceCapabilities;
struct WGPUSurfaceColorManagement;
struct WGPUSurfaceConfiguration;
struct WGPUSurfaceDescriptorFromWindowsCoreWindow;
struct WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel;
struct WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel;
struct WGPUSurfaceSourceAndroidNativeWindow;
struct WGPUSurfaceSourceMetalLayer;
struct WGPUSurfaceSourceWaylandSurface;
struct WGPUSurfaceSourceWindowsHWND;
struct WGPUSurfaceSourceXCBWindow;
struct WGPUSurfaceSourceXlibWindow;
struct WGPUSurfaceTexture;
struct WGPUTexelBufferBindingEntry;
struct WGPUTexelBufferBindingLayout;
struct WGPUTexelBufferViewDescriptor;
struct WGPUTexelCopyBufferLayout;
struct WGPUTextureBindingLayout;
struct WGPUTextureBindingViewDimensionDescriptor;
struct WGPUTextureComponentSwizzle;
struct WGPUVertexAttribute;
struct WGPUYCbCrVkDescriptor;
struct WGPUAdapterPropertiesMemoryHeaps;
struct WGPUAdapterPropertiesSubgroupMatrixConfigs;
struct WGPUAHardwareBufferProperties;
struct WGPUBindGroupEntry;
struct WGPUBindGroupLayoutEntry;
struct WGPUBlendState;
struct WGPUBufferDescriptor;
struct WGPUCommandEncoderDescriptor;
struct WGPUCompilationMessage;
struct WGPUComputePassDescriptor;
struct WGPUComputeState;
struct WGPUDawnDrmFormatCapabilities;
struct WGPUDepthStencilState;
struct WGPUExternalTextureDescriptor;
struct WGPUFutureWaitInfo;
struct WGPUImageCopyExternalTexture;
struct WGPUInstanceDescriptor;
struct WGPULimits;
struct WGPUPipelineLayoutPixelLocalStorage;
struct WGPURenderPassColorAttachment;
struct WGPURenderPassStorageAttachment;
struct WGPURequestAdapterOptions;
struct WGPUSamplerDescriptor;
struct WGPUShaderModuleDescriptor;
struct WGPUSharedFenceDescriptor;
struct WGPUSharedFenceExportInfo;
struct WGPUSharedTextureMemoryAHardwareBufferProperties;
struct WGPUSharedTextureMemoryBeginAccessDescriptor;
struct WGPUSharedTextureMemoryDmaBufDescriptor;
struct WGPUSharedTextureMemoryMetalEndAccessState;
struct WGPUSurfaceDescriptor;
struct WGPUTexelCopyBufferInfo;
struct WGPUTexelCopyTextureInfo;
struct WGPUTextureComponentSwizzleDescriptor;
struct WGPUTextureDescriptor;
struct WGPUVertexBufferLayout;
struct WGPUAdapterInfo;
struct WGPUBindGroupDescriptor;
struct WGPUBindGroupLayoutDescriptor;
struct WGPUColorTargetState;
struct WGPUCompilationInfo;
struct WGPUComputePipelineDescriptor;
struct WGPUDawnFormatCapabilities;
struct WGPUDeviceDescriptor;
struct WGPUPipelineLayoutDescriptor;
struct WGPURenderPassPixelLocalStorage;
struct WGPUSharedTextureMemoryDescriptor;
struct WGPUSharedTextureMemoryEndAccessState;
struct WGPUSharedTextureMemoryProperties;
struct WGPUTextureViewDescriptor;
struct WGPUVertexState;
struct WGPUFragmentState;
struct WGPURenderPassDescriptor;
struct WGPURenderPipelineDescriptor;

// Callback info structure forward declarations.
struct WGPUBufferMapCallbackInfo;
struct WGPUCompilationInfoCallbackInfo;
struct WGPUCreateComputePipelineAsyncCallbackInfo;
struct WGPUCreateRenderPipelineAsyncCallbackInfo;
struct WGPUDeviceLostCallbackInfo;
struct WGPULoggingCallbackInfo;
struct WGPUPopErrorScopeCallbackInfo;
struct WGPUQueueWorkDoneCallbackInfo;
struct WGPURequestAdapterCallbackInfo;
struct WGPURequestDeviceCallbackInfo;
struct WGPUUncapturedErrorCallbackInfo;

typedef enum WGPUAdapterType {
    WGPUAdapterType_DiscreteGPU = 0x00000001,
    WGPUAdapterType_IntegratedGPU = 0x00000002,
    WGPUAdapterType_CPU = 0x00000003,
    WGPUAdapterType_Unknown = 0x00000004,
    WGPUAdapterType_Force32 = 0x7FFFFFFF
} WGPUAdapterType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUAddressMode {
    WGPUAddressMode_Undefined = 0x00000000,
    WGPUAddressMode_ClampToEdge = 0x00000001,
    WGPUAddressMode_Repeat = 0x00000002,
    WGPUAddressMode_MirrorRepeat = 0x00000003,
    WGPUAddressMode_Force32 = 0x7FFFFFFF
} WGPUAddressMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUAlphaMode {
    WGPUAlphaMode_Opaque = 0x00000001,
    WGPUAlphaMode_Premultiplied = 0x00000002,
    WGPUAlphaMode_Unpremultiplied = 0x00000003,
    WGPUAlphaMode_Force32 = 0x7FFFFFFF
} WGPUAlphaMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBackendType {
    WGPUBackendType_Undefined = 0x00000000,
    WGPUBackendType_Null = 0x00000001,
    WGPUBackendType_WebGPU = 0x00000002,
    WGPUBackendType_D3D11 = 0x00000003,
    WGPUBackendType_D3D12 = 0x00000004,
    WGPUBackendType_Metal = 0x00000005,
    WGPUBackendType_Vulkan = 0x00000006,
    WGPUBackendType_OpenGL = 0x00000007,
    WGPUBackendType_OpenGLES = 0x00000008,
    WGPUBackendType_Force32 = 0x7FFFFFFF
} WGPUBackendType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendFactor {
    WGPUBlendFactor_Undefined = 0x00000000,
    WGPUBlendFactor_Zero = 0x00000001,
    WGPUBlendFactor_One = 0x00000002,
    WGPUBlendFactor_Src = 0x00000003,
    WGPUBlendFactor_OneMinusSrc = 0x00000004,
    WGPUBlendFactor_SrcAlpha = 0x00000005,
    WGPUBlendFactor_OneMinusSrcAlpha = 0x00000006,
    WGPUBlendFactor_Dst = 0x00000007,
    WGPUBlendFactor_OneMinusDst = 0x00000008,
    WGPUBlendFactor_DstAlpha = 0x00000009,
    WGPUBlendFactor_OneMinusDstAlpha = 0x0000000A,
    WGPUBlendFactor_SrcAlphaSaturated = 0x0000000B,
    WGPUBlendFactor_Constant = 0x0000000C,
    WGPUBlendFactor_OneMinusConstant = 0x0000000D,
    WGPUBlendFactor_Src1 = 0x0000000E,
    WGPUBlendFactor_OneMinusSrc1 = 0x0000000F,
    WGPUBlendFactor_Src1Alpha = 0x00000010,
    WGPUBlendFactor_OneMinusSrc1Alpha = 0x00000011,
    WGPUBlendFactor_Force32 = 0x7FFFFFFF
} WGPUBlendFactor WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendOperation {
    WGPUBlendOperation_Undefined = 0x00000000,
    WGPUBlendOperation_Add = 0x00000001,
    WGPUBlendOperation_Subtract = 0x00000002,
    WGPUBlendOperation_ReverseSubtract = 0x00000003,
    WGPUBlendOperation_Min = 0x00000004,
    WGPUBlendOperation_Max = 0x00000005,
    WGPUBlendOperation_Force32 = 0x7FFFFFFF
} WGPUBlendOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferBindingType {
    WGPUBufferBindingType_BindingNotUsed = 0x00000000,
    WGPUBufferBindingType_Undefined = 0x00000001,
    WGPUBufferBindingType_Uniform = 0x00000002,
    WGPUBufferBindingType_Storage = 0x00000003,
    WGPUBufferBindingType_ReadOnlyStorage = 0x00000004,
    WGPUBufferBindingType_Force32 = 0x7FFFFFFF
} WGPUBufferBindingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferMapState {
    WGPUBufferMapState_Unmapped = 0x00000001,
    WGPUBufferMapState_Pending = 0x00000002,
    WGPUBufferMapState_Mapped = 0x00000003,
    WGPUBufferMapState_Force32 = 0x7FFFFFFF
} WGPUBufferMapState WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCallbackMode {
    WGPUCallbackMode_WaitAnyOnly = 0x00000001,
    WGPUCallbackMode_AllowProcessEvents = 0x00000002,
    WGPUCallbackMode_AllowSpontaneous = 0x00000003,
    WGPUCallbackMode_Force32 = 0x7FFFFFFF
} WGPUCallbackMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompareFunction {
    WGPUCompareFunction_Undefined = 0x00000000,
    WGPUCompareFunction_Never = 0x00000001,
    WGPUCompareFunction_Less = 0x00000002,
    WGPUCompareFunction_Equal = 0x00000003,
    WGPUCompareFunction_LessEqual = 0x00000004,
    WGPUCompareFunction_Greater = 0x00000005,
    WGPUCompareFunction_NotEqual = 0x00000006,
    WGPUCompareFunction_GreaterEqual = 0x00000007,
    WGPUCompareFunction_Always = 0x00000008,
    WGPUCompareFunction_Force32 = 0x7FFFFFFF
} WGPUCompareFunction WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationInfoRequestStatus {
    WGPUCompilationInfoRequestStatus_Success = 0x00000001,
    WGPUCompilationInfoRequestStatus_CallbackCancelled = 0x00000002,
    WGPUCompilationInfoRequestStatus_Force32 = 0x7FFFFFFF
} WGPUCompilationInfoRequestStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationMessageType {
    WGPUCompilationMessageType_Error = 0x00000001,
    WGPUCompilationMessageType_Warning = 0x00000002,
    WGPUCompilationMessageType_Info = 0x00000003,
    WGPUCompilationMessageType_Force32 = 0x7FFFFFFF
} WGPUCompilationMessageType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUComponentSwizzle {
    WGPUComponentSwizzle_Undefined = 0x00000000,
    WGPUComponentSwizzle_Zero = 0x00000001,
    WGPUComponentSwizzle_One = 0x00000002,
    WGPUComponentSwizzle_R = 0x00000003,
    WGPUComponentSwizzle_G = 0x00000004,
    WGPUComponentSwizzle_B = 0x00000005,
    WGPUComponentSwizzle_A = 0x00000006,
    WGPUComponentSwizzle_Force32 = 0x7FFFFFFF
} WGPUComponentSwizzle WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompositeAlphaMode {
    WGPUCompositeAlphaMode_Auto = 0x00000000,
    WGPUCompositeAlphaMode_Opaque = 0x00000001,
    WGPUCompositeAlphaMode_Premultiplied = 0x00000002,
    WGPUCompositeAlphaMode_Unpremultiplied = 0x00000003,
    WGPUCompositeAlphaMode_Inherit = 0x00000004,
    WGPUCompositeAlphaMode_Force32 = 0x7FFFFFFF
} WGPUCompositeAlphaMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCreatePipelineAsyncStatus {
    WGPUCreatePipelineAsyncStatus_Success = 0x00000001,
    WGPUCreatePipelineAsyncStatus_CallbackCancelled = 0x00000002,
    WGPUCreatePipelineAsyncStatus_ValidationError = 0x00000003,
    WGPUCreatePipelineAsyncStatus_InternalError = 0x00000004,
    WGPUCreatePipelineAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUCreatePipelineAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCullMode {
    WGPUCullMode_Undefined = 0x00000000,
    WGPUCullMode_None = 0x00000001,
    WGPUCullMode_Front = 0x00000002,
    WGPUCullMode_Back = 0x00000003,
    WGPUCullMode_Force32 = 0x7FFFFFFF
} WGPUCullMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUDeviceLostReason {
    WGPUDeviceLostReason_Unknown = 0x00000001,
    WGPUDeviceLostReason_Destroyed = 0x00000002,
    WGPUDeviceLostReason_CallbackCancelled = 0x00000003,
    WGPUDeviceLostReason_FailedCreation = 0x00000004,
    WGPUDeviceLostReason_Force32 = 0x7FFFFFFF
} WGPUDeviceLostReason WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorFilter {
    WGPUErrorFilter_Validation = 0x00000001,
    WGPUErrorFilter_OutOfMemory = 0x00000002,
    WGPUErrorFilter_Internal = 0x00000003,
    WGPUErrorFilter_Force32 = 0x7FFFFFFF
} WGPUErrorFilter WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorType {
    WGPUErrorType_NoError = 0x00000001,
    WGPUErrorType_Validation = 0x00000002,
    WGPUErrorType_OutOfMemory = 0x00000003,
    WGPUErrorType_Internal = 0x00000004,
    WGPUErrorType_Unknown = 0x00000005,
    WGPUErrorType_Force32 = 0x7FFFFFFF
} WGPUErrorType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUExternalTextureRotation {
    WGPUExternalTextureRotation_Rotate0Degrees = 0x00000001,
    WGPUExternalTextureRotation_Rotate90Degrees = 0x00000002,
    WGPUExternalTextureRotation_Rotate180Degrees = 0x00000003,
    WGPUExternalTextureRotation_Rotate270Degrees = 0x00000004,
    WGPUExternalTextureRotation_Force32 = 0x7FFFFFFF
} WGPUExternalTextureRotation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFeatureLevel {
    WGPUFeatureLevel_Undefined = 0x00000000,
    WGPUFeatureLevel_Compatibility = 0x00000001,
    WGPUFeatureLevel_Core = 0x00000002,
    WGPUFeatureLevel_Force32 = 0x7FFFFFFF
} WGPUFeatureLevel WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFeatureName {
    WGPUFeatureName_CoreFeaturesAndLimits = 0x00000001,
    WGPUFeatureName_DepthClipControl = 0x00000002,
    WGPUFeatureName_Depth32FloatStencil8 = 0x00000003,
    WGPUFeatureName_TextureCompressionBC = 0x00000004,
    WGPUFeatureName_TextureCompressionBCSliced3D = 0x00000005,
    WGPUFeatureName_TextureCompressionETC2 = 0x00000006,
    WGPUFeatureName_TextureCompressionASTC = 0x00000007,
    WGPUFeatureName_TextureCompressionASTCSliced3D = 0x00000008,
    WGPUFeatureName_TimestampQuery = 0x00000009,
    WGPUFeatureName_IndirectFirstInstance = 0x0000000A,
    WGPUFeatureName_ShaderF16 = 0x0000000B,
    WGPUFeatureName_RG11B10UfloatRenderable = 0x0000000C,
    WGPUFeatureName_BGRA8UnormStorage = 0x0000000D,
    WGPUFeatureName_Float32Filterable = 0x0000000E,
    WGPUFeatureName_Float32Blendable = 0x0000000F,
    WGPUFeatureName_ClipDistances = 0x00000010,
    WGPUFeatureName_DualSourceBlending = 0x00000011,
    WGPUFeatureName_Subgroups = 0x00000012,
    WGPUFeatureName_TextureFormatsTier1 = 0x00000013,
    WGPUFeatureName_TextureFormatsTier2 = 0x00000014,
    WGPUFeatureName_PrimitiveIndex = 0x00000015,
    WGPUFeatureName_TextureComponentSwizzle = 0x00000016,
    WGPUFeatureName_DawnInternalUsages = 0x00050000,
    WGPUFeatureName_DawnMultiPlanarFormats = 0x00050001,
    WGPUFeatureName_DawnNative = 0x00050002,
    WGPUFeatureName_ChromiumExperimentalTimestampQueryInsidePasses = 0x00050003,
    WGPUFeatureName_ImplicitDeviceSynchronization = 0x00050004,
    WGPUFeatureName_TransientAttachments = 0x00050006,
    WGPUFeatureName_MSAARenderToSingleSampled = 0x00050007,
    WGPUFeatureName_D3D11MultithreadProtected = 0x00050008,
    WGPUFeatureName_ANGLETextureSharing = 0x00050009,
    WGPUFeatureName_PixelLocalStorageCoherent = 0x0005000A,
    WGPUFeatureName_PixelLocalStorageNonCoherent = 0x0005000B,
    WGPUFeatureName_Unorm16TextureFormats = 0x0005000C,
    WGPUFeatureName_MultiPlanarFormatExtendedUsages = 0x0005000D,
    WGPUFeatureName_MultiPlanarFormatP010 = 0x0005000E,
    WGPUFeatureName_HostMappedPointer = 0x0005000F,
    WGPUFeatureName_MultiPlanarRenderTargets = 0x00050010,
    WGPUFeatureName_MultiPlanarFormatNv12a = 0x00050011,
    WGPUFeatureName_FramebufferFetch = 0x00050012,
    WGPUFeatureName_BufferMapExtendedUsages = 0x00050013,
    WGPUFeatureName_AdapterPropertiesMemoryHeaps = 0x00050014,
    WGPUFeatureName_AdapterPropertiesD3D = 0x00050015,
    WGPUFeatureName_AdapterPropertiesVk = 0x00050016,
    WGPUFeatureName_DawnFormatCapabilities = 0x00050017,
    WGPUFeatureName_DawnDrmFormatCapabilities = 0x00050018,
    WGPUFeatureName_MultiPlanarFormatNv16 = 0x00050019,
    WGPUFeatureName_MultiPlanarFormatNv24 = 0x0005001A,
    WGPUFeatureName_MultiPlanarFormatP210 = 0x0005001B,
    WGPUFeatureName_MultiPlanarFormatP410 = 0x0005001C,
    WGPUFeatureName_SharedTextureMemoryVkDedicatedAllocation = 0x0005001D,
    WGPUFeatureName_SharedTextureMemoryAHardwareBuffer = 0x0005001E,
    WGPUFeatureName_SharedTextureMemoryDmaBuf = 0x0005001F,
    WGPUFeatureName_SharedTextureMemoryOpaqueFD = 0x00050020,
    WGPUFeatureName_SharedTextureMemoryZirconHandle = 0x00050021,
    WGPUFeatureName_SharedTextureMemoryDXGISharedHandle = 0x00050022,
    WGPUFeatureName_SharedTextureMemoryD3D11Texture2D = 0x00050023,
    WGPUFeatureName_SharedTextureMemoryIOSurface = 0x00050024,
    WGPUFeatureName_SharedTextureMemoryEGLImage = 0x00050025,
    WGPUFeatureName_SharedFenceVkSemaphoreOpaqueFD = 0x00050026,
    WGPUFeatureName_SharedFenceSyncFD = 0x00050027,
    WGPUFeatureName_SharedFenceVkSemaphoreZirconHandle = 0x00050028,
    WGPUFeatureName_SharedFenceDXGISharedHandle = 0x00050029,
    WGPUFeatureName_SharedFenceMTLSharedEvent = 0x0005002A,
    WGPUFeatureName_SharedBufferMemoryD3D12Resource = 0x0005002B,
    WGPUFeatureName_StaticSamplers = 0x0005002C,
    WGPUFeatureName_YCbCrVulkanSamplers = 0x0005002D,
    WGPUFeatureName_ShaderModuleCompilationOptions = 0x0005002E,
    WGPUFeatureName_DawnLoadResolveTexture = 0x0005002F,
    WGPUFeatureName_DawnPartialLoadResolveTexture = 0x00050030,
    WGPUFeatureName_MultiDrawIndirect = 0x00050031,
    WGPUFeatureName_DawnTexelCopyBufferRowAlignment = 0x00050032,
    WGPUFeatureName_FlexibleTextureViews = 0x00050033,
    WGPUFeatureName_ChromiumExperimentalSubgroupMatrix = 0x00050034,
    WGPUFeatureName_SharedFenceEGLSync = 0x00050035,
    WGPUFeatureName_DawnDeviceAllocatorControl = 0x00050036,
    WGPUFeatureName_AdapterPropertiesWGPU = 0x00050037,
    WGPUFeatureName_SharedBufferMemoryD3D12SharedMemoryFileMappingHandle = 0x00050038,
    WGPUFeatureName_SharedTextureMemoryD3D12Resource = 0x00050039,
    WGPUFeatureName_ChromiumExperimentalSamplingResourceTable = 0x0005003A,
    WGPUFeatureName_ChromiumExperimentalSubgroupSizeControl = 0x0005003B,
    WGPUFeatureName_Force32 = 0x7FFFFFFF
} WGPUFeatureName WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFilterMode {
    WGPUFilterMode_Undefined = 0x00000000,
    WGPUFilterMode_Nearest = 0x00000001,
    WGPUFilterMode_Linear = 0x00000002,
    WGPUFilterMode_Force32 = 0x7FFFFFFF
} WGPUFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFrontFace {
    WGPUFrontFace_Undefined = 0x00000000,
    WGPUFrontFace_CCW = 0x00000001,
    WGPUFrontFace_CW = 0x00000002,
    WGPUFrontFace_Force32 = 0x7FFFFFFF
} WGPUFrontFace WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUIndexFormat {
    WGPUIndexFormat_Undefined = 0x00000000,
    WGPUIndexFormat_Uint16 = 0x00000001,
    WGPUIndexFormat_Uint32 = 0x00000002,
    WGPUIndexFormat_Force32 = 0x7FFFFFFF
} WGPUIndexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUInstanceFeatureName {
    WGPUInstanceFeatureName_TimedWaitAny = 0x00000001,
    WGPUInstanceFeatureName_ShaderSourceSPIRV = 0x00000002,
    WGPUInstanceFeatureName_MultipleDevicesPerAdapter = 0x00000003,
    WGPUInstanceFeatureName_Force32 = 0x7FFFFFFF
} WGPUInstanceFeatureName WGPU_ENUM_ATTRIBUTE;

typedef enum WGPULoadOp {
    WGPULoadOp_Undefined = 0x00000000,
    WGPULoadOp_Load = 0x00000001,
    WGPULoadOp_Clear = 0x00000002,
    WGPULoadOp_ExpandResolveTexture = 0x00050003,
    WGPULoadOp_Force32 = 0x7FFFFFFF
} WGPULoadOp WGPU_ENUM_ATTRIBUTE;

typedef enum WGPULoggingType {
    WGPULoggingType_Verbose = 0x00000001,
    WGPULoggingType_Info = 0x00000002,
    WGPULoggingType_Warning = 0x00000003,
    WGPULoggingType_Error = 0x00000004,
    WGPULoggingType_Force32 = 0x7FFFFFFF
} WGPULoggingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMapAsyncStatus {
    WGPUMapAsyncStatus_Success = 0x00000001,
    WGPUMapAsyncStatus_CallbackCancelled = 0x00000002,
    WGPUMapAsyncStatus_Error = 0x00000003,
    WGPUMapAsyncStatus_Aborted = 0x00000004,
    WGPUMapAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUMapAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMipmapFilterMode {
    WGPUMipmapFilterMode_Undefined = 0x00000000,
    WGPUMipmapFilterMode_Nearest = 0x00000001,
    WGPUMipmapFilterMode_Linear = 0x00000002,
    WGPUMipmapFilterMode_Force32 = 0x7FFFFFFF
} WGPUMipmapFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUOptionalBool {
    WGPUOptionalBool_False = 0x00000000,
    WGPUOptionalBool_True = 0x00000001,
    WGPUOptionalBool_Undefined = 0x00000002,
    WGPUOptionalBool_Force32 = 0x7FFFFFFF
} WGPUOptionalBool WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPopErrorScopeStatus {
    WGPUPopErrorScopeStatus_Success = 0x00000001,
    WGPUPopErrorScopeStatus_CallbackCancelled = 0x00000002,
    WGPUPopErrorScopeStatus_Error = 0x00000003,
    WGPUPopErrorScopeStatus_Force32 = 0x7FFFFFFF
} WGPUPopErrorScopeStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPowerPreference {
    WGPUPowerPreference_Undefined = 0x00000000,
    WGPUPowerPreference_LowPower = 0x00000001,
    WGPUPowerPreference_HighPerformance = 0x00000002,
    WGPUPowerPreference_Force32 = 0x7FFFFFFF
} WGPUPowerPreference WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPredefinedColorSpace {
    WGPUPredefinedColorSpace_SRGB = 0x00000001,
    WGPUPredefinedColorSpace_DisplayP3 = 0x00000002,
    WGPUPredefinedColorSpace_Force32 = 0x7FFFFFFF
} WGPUPredefinedColorSpace WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPresentMode {
    WGPUPresentMode_Undefined = 0x00000000,
    WGPUPresentMode_Fifo = 0x00000001,
    WGPUPresentMode_FifoRelaxed = 0x00000002,
    WGPUPresentMode_Immediate = 0x00000003,
    WGPUPresentMode_Mailbox = 0x00000004,
    WGPUPresentMode_Force32 = 0x7FFFFFFF
} WGPUPresentMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPrimitiveTopology {
    WGPUPrimitiveTopology_Undefined = 0x00000000,
    WGPUPrimitiveTopology_PointList = 0x00000001,
    WGPUPrimitiveTopology_LineList = 0x00000002,
    WGPUPrimitiveTopology_LineStrip = 0x00000003,
    WGPUPrimitiveTopology_TriangleList = 0x00000004,
    WGPUPrimitiveTopology_TriangleStrip = 0x00000005,
    WGPUPrimitiveTopology_Force32 = 0x7FFFFFFF
} WGPUPrimitiveTopology WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueryType {
    WGPUQueryType_Occlusion = 0x00000001,
    WGPUQueryType_Timestamp = 0x00000002,
    WGPUQueryType_Force32 = 0x7FFFFFFF
} WGPUQueryType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueueWorkDoneStatus {
    WGPUQueueWorkDoneStatus_Success = 0x00000001,
    WGPUQueueWorkDoneStatus_CallbackCancelled = 0x00000002,
    WGPUQueueWorkDoneStatus_Error = 0x00000003,
    WGPUQueueWorkDoneStatus_Force32 = 0x7FFFFFFF
} WGPUQueueWorkDoneStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestAdapterStatus {
    WGPURequestAdapterStatus_Success = 0x00000001,
    WGPURequestAdapterStatus_CallbackCancelled = 0x00000002,
    WGPURequestAdapterStatus_Unavailable = 0x00000003,
    WGPURequestAdapterStatus_Error = 0x00000004,
    WGPURequestAdapterStatus_Force32 = 0x7FFFFFFF
} WGPURequestAdapterStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestDeviceStatus {
    WGPURequestDeviceStatus_Success = 0x00000001,
    WGPURequestDeviceStatus_CallbackCancelled = 0x00000002,
    WGPURequestDeviceStatus_Error = 0x00000003,
    WGPURequestDeviceStatus_Force32 = 0x7FFFFFFF
} WGPURequestDeviceStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSamplerBindingType {
    WGPUSamplerBindingType_BindingNotUsed = 0x00000000,
    WGPUSamplerBindingType_Undefined = 0x00000001,
    WGPUSamplerBindingType_Filtering = 0x00000002,
    WGPUSamplerBindingType_NonFiltering = 0x00000003,
    WGPUSamplerBindingType_Comparison = 0x00000004,
    WGPUSamplerBindingType_Force32 = 0x7FFFFFFF
} WGPUSamplerBindingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSharedFenceType {
    WGPUSharedFenceType_VkSemaphoreOpaqueFD = 0x00000001,
    WGPUSharedFenceType_SyncFD = 0x00000002,
    WGPUSharedFenceType_VkSemaphoreZirconHandle = 0x00000003,
    WGPUSharedFenceType_DXGISharedHandle = 0x00000004,
    WGPUSharedFenceType_MTLSharedEvent = 0x00000005,
    WGPUSharedFenceType_EGLSync = 0x00000006,
    WGPUSharedFenceType_Force32 = 0x7FFFFFFF
} WGPUSharedFenceType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStatus {
    WGPUStatus_Success = 0x00000001,
    WGPUStatus_Error = 0x00000002,
    WGPUStatus_Force32 = 0x7FFFFFFF
} WGPUStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStencilOperation {
    WGPUStencilOperation_Undefined = 0x00000000,
    WGPUStencilOperation_Keep = 0x00000001,
    WGPUStencilOperation_Zero = 0x00000002,
    WGPUStencilOperation_Replace = 0x00000003,
    WGPUStencilOperation_Invert = 0x00000004,
    WGPUStencilOperation_IncrementClamp = 0x00000005,
    WGPUStencilOperation_DecrementClamp = 0x00000006,
    WGPUStencilOperation_IncrementWrap = 0x00000007,
    WGPUStencilOperation_DecrementWrap = 0x00000008,
    WGPUStencilOperation_Force32 = 0x7FFFFFFF
} WGPUStencilOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStorageTextureAccess {
    WGPUStorageTextureAccess_BindingNotUsed = 0x00000000,
    WGPUStorageTextureAccess_Undefined = 0x00000001,
    WGPUStorageTextureAccess_WriteOnly = 0x00000002,
    WGPUStorageTextureAccess_ReadOnly = 0x00000003,
    WGPUStorageTextureAccess_ReadWrite = 0x00000004,
    WGPUStorageTextureAccess_Force32 = 0x7FFFFFFF
} WGPUStorageTextureAccess WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStoreOp {
    WGPUStoreOp_Undefined = 0x00000000,
    WGPUStoreOp_Store = 0x00000001,
    WGPUStoreOp_Discard = 0x00000002,
    WGPUStoreOp_Force32 = 0x7FFFFFFF
} WGPUStoreOp WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSType {
    WGPUSType_ShaderSourceSPIRV = 0x00000001,
    WGPUSType_ShaderSourceWGSL = 0x00000002,
    WGPUSType_RenderPassMaxDrawCount = 0x00000003,
    WGPUSType_SurfaceSourceMetalLayer = 0x00000004,
    WGPUSType_SurfaceSourceWindowsHWND = 0x00000005,
    WGPUSType_SurfaceSourceXlibWindow = 0x00000006,
    WGPUSType_SurfaceSourceWaylandSurface = 0x00000007,
    WGPUSType_SurfaceSourceAndroidNativeWindow = 0x00000008,
    WGPUSType_SurfaceSourceXCBWindow = 0x00000009,
    WGPUSType_SurfaceColorManagement = 0x0000000A,
    WGPUSType_RequestAdapterWebXROptions = 0x0000000B,
    WGPUSType_TextureComponentSwizzleDescriptor = 0x0000000C,
    WGPUSType_CompatibilityModeLimits = 0x00020000,
    WGPUSType_TextureBindingViewDimensionDescriptor = 0x00020001,
    WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector = 0x00040000,
    WGPUSType_SurfaceDescriptorFromWindowsCoreWindow = 0x00050000,
    WGPUSType_ExternalTextureBindingEntry = 0x00050001,
    WGPUSType_ExternalTextureBindingLayout = 0x00050002,
    WGPUSType_SurfaceDescriptorFromWindowsUWPSwapChainPanel = 0x00050003,
    WGPUSType_DawnTextureInternalUsageDescriptor = 0x00050004,
    WGPUSType_DawnEncoderInternalUsageDescriptor = 0x00050005,
    WGPUSType_DawnInstanceDescriptor = 0x00050006,
    WGPUSType_DawnCacheDeviceDescriptor = 0x00050007,
    WGPUSType_DawnAdapterPropertiesPowerPreference = 0x00050008,
    WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient = 0x00050009,
    WGPUSType_DawnTogglesDescriptor = 0x0005000A,
    WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor = 0x0005000B,
    WGPUSType_RequestAdapterOptionsLUID = 0x0005000C,
    WGPUSType_RequestAdapterOptionsGetGLProc = 0x0005000D,
    WGPUSType_RequestAdapterOptionsD3D11Device = 0x0005000E,
    WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled = 0x0005000F,
    WGPUSType_RenderPassPixelLocalStorage = 0x00050010,
    WGPUSType_PipelineLayoutPixelLocalStorage = 0x00050011,
    WGPUSType_BufferHostMappedPointer = 0x00050012,
    WGPUSType_AdapterPropertiesMemoryHeaps = 0x00050013,
    WGPUSType_AdapterPropertiesD3D = 0x00050014,
    WGPUSType_AdapterPropertiesVk = 0x00050015,
    WGPUSType_DawnWireWGSLControl = 0x00050016,
    WGPUSType_DawnWGSLBlocklist = 0x00050017,
    WGPUSType_DawnDrmFormatCapabilities = 0x00050018,
    WGPUSType_ShaderModuleCompilationOptions = 0x00050019,
    WGPUSType_ColorTargetStateExpandResolveTextureDawn = 0x0005001A,
    WGPUSType_RenderPassDescriptorExpandResolveRect = 0x0005001B,
    WGPUSType_SharedTextureMemoryVkDedicatedAllocationDescriptor = 0x0005001C,
    WGPUSType_SharedTextureMemoryAHardwareBufferDescriptor = 0x0005001D,
    WGPUSType_SharedTextureMemoryDmaBufDescriptor = 0x0005001E,
    WGPUSType_SharedTextureMemoryOpaqueFDDescriptor = 0x0005001F,
    WGPUSType_SharedTextureMemoryZirconHandleDescriptor = 0x00050020,
    WGPUSType_SharedTextureMemoryDXGISharedHandleDescriptor = 0x00050021,
    WGPUSType_SharedTextureMemoryD3D11Texture2DDescriptor = 0x00050022,
    WGPUSType_SharedTextureMemoryIOSurfaceDescriptor = 0x00050023,
    WGPUSType_SharedTextureMemoryEGLImageDescriptor = 0x00050024,
    WGPUSType_SharedTextureMemoryInitializedBeginState = 0x00050025,
    WGPUSType_SharedTextureMemoryInitializedEndState = 0x00050026,
    WGPUSType_SharedTextureMemoryVkImageLayoutBeginState = 0x00050027,
    WGPUSType_SharedTextureMemoryVkImageLayoutEndState = 0x00050028,
    WGPUSType_SharedTextureMemoryD3DSwapchainBeginState = 0x00050029,
    WGPUSType_SharedFenceVkSemaphoreOpaqueFDDescriptor = 0x0005002A,
    WGPUSType_SharedFenceVkSemaphoreOpaqueFDExportInfo = 0x0005002B,
    WGPUSType_SharedFenceSyncFDDescriptor = 0x0005002C,
    WGPUSType_SharedFenceSyncFDExportInfo = 0x0005002D,
    WGPUSType_SharedFenceVkSemaphoreZirconHandleDescriptor = 0x0005002E,
    WGPUSType_SharedFenceVkSemaphoreZirconHandleExportInfo = 0x0005002F,
    WGPUSType_SharedFenceDXGISharedHandleDescriptor = 0x00050030,
    WGPUSType_SharedFenceDXGISharedHandleExportInfo = 0x00050031,
    WGPUSType_SharedFenceMTLSharedEventDescriptor = 0x00050032,
    WGPUSType_SharedFenceMTLSharedEventExportInfo = 0x00050033,
    WGPUSType_SharedBufferMemoryD3D12ResourceDescriptor = 0x00050034,
    WGPUSType_StaticSamplerBindingLayout = 0x00050035,
    WGPUSType_YCbCrVkDescriptor = 0x00050036,
    WGPUSType_SharedTextureMemoryAHardwareBufferProperties = 0x00050037,
    WGPUSType_AHardwareBufferProperties = 0x00050038,
    WGPUSType_DawnTexelCopyBufferRowAlignmentLimits = 0x0005003A,
    WGPUSType_AdapterPropertiesSubgroupMatrixConfigs = 0x0005003B,
    WGPUSType_SharedFenceEGLSyncDescriptor = 0x0005003C,
    WGPUSType_SharedFenceEGLSyncExportInfo = 0x0005003D,
    WGPUSType_DawnInjectedInvalidSType = 0x0005003E,
    WGPUSType_DawnCompilationMessageUtf16 = 0x0005003F,
    WGPUSType_DawnFakeBufferOOMForTesting = 0x00050040,
    WGPUSType_SurfaceDescriptorFromWindowsWinUISwapChainPanel = 0x00050041,
    WGPUSType_DawnDeviceAllocatorControl = 0x00050042,
    WGPUSType_DawnHostMappedPointerLimits = 0x00050043,
    WGPUSType_RenderPassDescriptorResolveRect = 0x00050044,
    WGPUSType_RequestAdapterWebGPUBackendOptions = 0x00050045,
    WGPUSType_DawnFakeDeviceInitializeErrorForTesting = 0x00050046,
    WGPUSType_SharedTextureMemoryD3D11BeginState = 0x00050047,
    WGPUSType_DawnConsumeAdapterDescriptor = 0x00050048,
    WGPUSType_TexelBufferBindingEntry = 0x00050049,
    WGPUSType_TexelBufferBindingLayout = 0x0005004A,
    WGPUSType_SharedTextureMemoryMetalEndAccessState = 0x0005004B,
    WGPUSType_AdapterPropertiesWGPU = 0x0005004C,
    WGPUSType_SharedBufferMemoryD3D12SharedMemoryFileMappingHandleDescriptor = 0x0005004D,
    WGPUSType_SharedTextureMemoryD3D12ResourceDescriptor = 0x0005004E,
    WGPUSType_RequestAdapterOptionsAngleVirtualizationGroup = 0x0005004F,
    WGPUSType_ResourceTableLimits = 0x00050050,
    WGPUSType_PipelineLayoutResourceTable = 0x00050051,
    WGPUSType_Force32 = 0x7FFFFFFF
} WGPUSType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSubgroupMatrixComponentType {
    WGPUSubgroupMatrixComponentType_F32 = 0x00000001,
    WGPUSubgroupMatrixComponentType_F16 = 0x00000002,
    WGPUSubgroupMatrixComponentType_U32 = 0x00000003,
    WGPUSubgroupMatrixComponentType_I32 = 0x00000004,
    WGPUSubgroupMatrixComponentType_U8 = 0x00000005,
    WGPUSubgroupMatrixComponentType_I8 = 0x00000006,
    WGPUSubgroupMatrixComponentType_Force32 = 0x7FFFFFFF
} WGPUSubgroupMatrixComponentType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSurfaceGetCurrentTextureStatus {
    WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal = 0x00000001,
    WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal = 0x00000002,
    WGPUSurfaceGetCurrentTextureStatus_Timeout = 0x00000003,
    WGPUSurfaceGetCurrentTextureStatus_Outdated = 0x00000004,
    WGPUSurfaceGetCurrentTextureStatus_Lost = 0x00000005,
    WGPUSurfaceGetCurrentTextureStatus_Error = 0x00000006,
    WGPUSurfaceGetCurrentTextureStatus_Force32 = 0x7FFFFFFF
} WGPUSurfaceGetCurrentTextureStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTexelBufferAccess {
    WGPUTexelBufferAccess_Undefined = 0x00000000,
    WGPUTexelBufferAccess_ReadOnly = 0x00000001,
    WGPUTexelBufferAccess_ReadWrite = 0x00000002,
    WGPUTexelBufferAccess_Force32 = 0x7FFFFFFF
} WGPUTexelBufferAccess WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureAspect {
    WGPUTextureAspect_Undefined = 0x00000000,
    WGPUTextureAspect_All = 0x00000001,
    WGPUTextureAspect_StencilOnly = 0x00000002,
    WGPUTextureAspect_DepthOnly = 0x00000003,
    WGPUTextureAspect_Plane0Only = 0x00050000,
    WGPUTextureAspect_Plane1Only = 0x00050001,
    WGPUTextureAspect_Plane2Only = 0x00050002,
    WGPUTextureAspect_Force32 = 0x7FFFFFFF
} WGPUTextureAspect WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureDimension {
    WGPUTextureDimension_Undefined = 0x00000000,
    WGPUTextureDimension_1D = 0x00000001,
    WGPUTextureDimension_2D = 0x00000002,
    WGPUTextureDimension_3D = 0x00000003,
    WGPUTextureDimension_Force32 = 0x7FFFFFFF
} WGPUTextureDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureFormat {
    WGPUTextureFormat_Undefined = 0x00000000,
    WGPUTextureFormat_R8Unorm = 0x00000001,
    WGPUTextureFormat_R8Snorm = 0x00000002,
    WGPUTextureFormat_R8Uint = 0x00000003,
    WGPUTextureFormat_R8Sint = 0x00000004,
    WGPUTextureFormat_R16Unorm = 0x00000005,
    WGPUTextureFormat_R16Snorm = 0x00000006,
    WGPUTextureFormat_R16Uint = 0x00000007,
    WGPUTextureFormat_R16Sint = 0x00000008,
    WGPUTextureFormat_R16Float = 0x00000009,
    WGPUTextureFormat_RG8Unorm = 0x0000000A,
    WGPUTextureFormat_RG8Snorm = 0x0000000B,
    WGPUTextureFormat_RG8Uint = 0x0000000C,
    WGPUTextureFormat_RG8Sint = 0x0000000D,
    WGPUTextureFormat_R32Float = 0x0000000E,
    WGPUTextureFormat_R32Uint = 0x0000000F,
    WGPUTextureFormat_R32Sint = 0x00000010,
    WGPUTextureFormat_RG16Unorm = 0x00000011,
    WGPUTextureFormat_RG16Snorm = 0x00000012,
    WGPUTextureFormat_RG16Uint = 0x00000013,
    WGPUTextureFormat_RG16Sint = 0x00000014,
    WGPUTextureFormat_RG16Float = 0x00000015,
    WGPUTextureFormat_RGBA8Unorm = 0x00000016,
    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000017,
    WGPUTextureFormat_RGBA8Snorm = 0x00000018,
    WGPUTextureFormat_RGBA8Uint = 0x00000019,
    WGPUTextureFormat_RGBA8Sint = 0x0000001A,
    WGPUTextureFormat_BGRA8Unorm = 0x0000001B,
    WGPUTextureFormat_BGRA8UnormSrgb = 0x0000001C,
    WGPUTextureFormat_RGB10A2Uint = 0x0000001D,
    WGPUTextureFormat_RGB10A2Unorm = 0x0000001E,
    WGPUTextureFormat_RG11B10Ufloat = 0x0000001F,
    WGPUTextureFormat_RGB9E5Ufloat = 0x00000020,
    WGPUTextureFormat_RG32Float = 0x00000021,
    WGPUTextureFormat_RG32Uint = 0x00000022,
    WGPUTextureFormat_RG32Sint = 0x00000023,
    WGPUTextureFormat_RGBA16Unorm = 0x00000024,
    WGPUTextureFormat_RGBA16Snorm = 0x00000025,
    WGPUTextureFormat_RGBA16Uint = 0x00000026,
    WGPUTextureFormat_RGBA16Sint = 0x00000027,
    WGPUTextureFormat_RGBA16Float = 0x00000028,
    WGPUTextureFormat_RGBA32Float = 0x00000029,
    WGPUTextureFormat_RGBA32Uint = 0x0000002A,
    WGPUTextureFormat_RGBA32Sint = 0x0000002B,
    WGPUTextureFormat_Stencil8 = 0x0000002C,
    WGPUTextureFormat_Depth16Unorm = 0x0000002D,
    WGPUTextureFormat_Depth24Plus = 0x0000002E,
    WGPUTextureFormat_Depth24PlusStencil8 = 0x0000002F,
    WGPUTextureFormat_Depth32Float = 0x00000030,
    WGPUTextureFormat_Depth32FloatStencil8 = 0x00000031,
    WGPUTextureFormat_BC1RGBAUnorm = 0x00000032,
    WGPUTextureFormat_BC1RGBAUnormSrgb = 0x00000033,
    WGPUTextureFormat_BC2RGBAUnorm = 0x00000034,
    WGPUTextureFormat_BC2RGBAUnormSrgb = 0x00000035,
    WGPUTextureFormat_BC3RGBAUnorm = 0x00000036,
    WGPUTextureFormat_BC3RGBAUnormSrgb = 0x00000037,
    WGPUTextureFormat_BC4RUnorm = 0x00000038,
    WGPUTextureFormat_BC4RSnorm = 0x00000039,
    WGPUTextureFormat_BC5RGUnorm = 0x0000003A,
    WGPUTextureFormat_BC5RGSnorm = 0x0000003B,
    WGPUTextureFormat_BC6HRGBUfloat = 0x0000003C,
    WGPUTextureFormat_BC6HRGBFloat = 0x0000003D,
    WGPUTextureFormat_BC7RGBAUnorm = 0x0000003E,
    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x0000003F,
    WGPUTextureFormat_ETC2RGB8Unorm = 0x00000040,
    WGPUTextureFormat_ETC2RGB8UnormSrgb = 0x00000041,
    WGPUTextureFormat_ETC2RGB8A1Unorm = 0x00000042,
    WGPUTextureFormat_ETC2RGB8A1UnormSrgb = 0x00000043,
    WGPUTextureFormat_ETC2RGBA8Unorm = 0x00000044,
    WGPUTextureFormat_ETC2RGBA8UnormSrgb = 0x00000045,
    WGPUTextureFormat_EACR11Unorm = 0x00000046,
    WGPUTextureFormat_EACR11Snorm = 0x00000047,
    WGPUTextureFormat_EACRG11Unorm = 0x00000048,
    WGPUTextureFormat_EACRG11Snorm = 0x00000049,
    WGPUTextureFormat_ASTC4x4Unorm = 0x0000004A,
    WGPUTextureFormat_ASTC4x4UnormSrgb = 0x0000004B,
    WGPUTextureFormat_ASTC5x4Unorm = 0x0000004C,
    WGPUTextureFormat_ASTC5x4UnormSrgb = 0x0000004D,
    WGPUTextureFormat_ASTC5x5Unorm = 0x0000004E,
    WGPUTextureFormat_ASTC5x5UnormSrgb = 0x0000004F,
    WGPUTextureFormat_ASTC6x5Unorm = 0x00000050,
    WGPUTextureFormat_ASTC6x5UnormSrgb = 0x00000051,
    WGPUTextureFormat_ASTC6x6Unorm = 0x00000052,
    WGPUTextureFormat_ASTC6x6UnormSrgb = 0x00000053,
    WGPUTextureFormat_ASTC8x5Unorm = 0x00000054,
    WGPUTextureFormat_ASTC8x5UnormSrgb = 0x00000055,
    WGPUTextureFormat_ASTC8x6Unorm = 0x00000056,
    WGPUTextureFormat_ASTC8x6UnormSrgb = 0x00000057,
    WGPUTextureFormat_ASTC8x8Unorm = 0x00000058,
    WGPUTextureFormat_ASTC8x8UnormSrgb = 0x00000059,
    WGPUTextureFormat_ASTC10x5Unorm = 0x0000005A,
    WGPUTextureFormat_ASTC10x5UnormSrgb = 0x0000005B,
    WGPUTextureFormat_ASTC10x6Unorm = 0x0000005C,
    WGPUTextureFormat_ASTC10x6UnormSrgb = 0x0000005D,
    WGPUTextureFormat_ASTC10x8Unorm = 0x0000005E,
    WGPUTextureFormat_ASTC10x8UnormSrgb = 0x0000005F,
    WGPUTextureFormat_ASTC10x10Unorm = 0x00000060,
    WGPUTextureFormat_ASTC10x10UnormSrgb = 0x00000061,
    WGPUTextureFormat_ASTC12x10Unorm = 0x00000062,
    WGPUTextureFormat_ASTC12x10UnormSrgb = 0x00000063,
    WGPUTextureFormat_ASTC12x12Unorm = 0x00000064,
    WGPUTextureFormat_ASTC12x12UnormSrgb = 0x00000065,
    WGPUTextureFormat_R8BG8Biplanar420Unorm = 0x00050006,
    WGPUTextureFormat_R10X6BG10X6Biplanar420Unorm = 0x00050007,
    WGPUTextureFormat_R8BG8A8Triplanar420Unorm = 0x00050008,
    WGPUTextureFormat_R8BG8Biplanar422Unorm = 0x00050009,
    WGPUTextureFormat_R8BG8Biplanar444Unorm = 0x0005000A,
    WGPUTextureFormat_R10X6BG10X6Biplanar422Unorm = 0x0005000B,
    WGPUTextureFormat_R10X6BG10X6Biplanar444Unorm = 0x0005000C,
    WGPUTextureFormat_External = 0x0005000D,
    WGPUTextureFormat_Force32 = 0x7FFFFFFF
} WGPUTextureFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureSampleType {
    WGPUTextureSampleType_BindingNotUsed = 0x00000000,
    WGPUTextureSampleType_Undefined = 0x00000001,
    WGPUTextureSampleType_Float = 0x00000002,
    WGPUTextureSampleType_UnfilterableFloat = 0x00000003,
    WGPUTextureSampleType_Depth = 0x00000004,
    WGPUTextureSampleType_Sint = 0x00000005,
    WGPUTextureSampleType_Uint = 0x00000006,
    WGPUTextureSampleType_Force32 = 0x7FFFFFFF
} WGPUTextureSampleType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureViewDimension {
    WGPUTextureViewDimension_Undefined = 0x00000000,
    WGPUTextureViewDimension_1D = 0x00000001,
    WGPUTextureViewDimension_2D = 0x00000002,
    WGPUTextureViewDimension_2DArray = 0x00000003,
    WGPUTextureViewDimension_Cube = 0x00000004,
    WGPUTextureViewDimension_CubeArray = 0x00000005,
    WGPUTextureViewDimension_3D = 0x00000006,
    WGPUTextureViewDimension_Force32 = 0x7FFFFFFF
} WGPUTextureViewDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUToneMappingMode {
    WGPUToneMappingMode_Standard = 0x00000001,
    WGPUToneMappingMode_Extended = 0x00000002,
    WGPUToneMappingMode_Force32 = 0x7FFFFFFF
} WGPUToneMappingMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexFormat {
    WGPUVertexFormat_Uint8 = 0x00000001,
    WGPUVertexFormat_Uint8x2 = 0x00000002,
    WGPUVertexFormat_Uint8x4 = 0x00000003,
    WGPUVertexFormat_Sint8 = 0x00000004,
    WGPUVertexFormat_Sint8x2 = 0x00000005,
    WGPUVertexFormat_Sint8x4 = 0x00000006,
    WGPUVertexFormat_Unorm8 = 0x00000007,
    WGPUVertexFormat_Unorm8x2 = 0x00000008,
    WGPUVertexFormat_Unorm8x4 = 0x00000009,
    WGPUVertexFormat_Snorm8 = 0x0000000A,
    WGPUVertexFormat_Snorm8x2 = 0x0000000B,
    WGPUVertexFormat_Snorm8x4 = 0x0000000C,
    WGPUVertexFormat_Uint16 = 0x0000000D,
    WGPUVertexFormat_Uint16x2 = 0x0000000E,
    WGPUVertexFormat_Uint16x4 = 0x0000000F,
    WGPUVertexFormat_Sint16 = 0x00000010,
    WGPUVertexFormat_Sint16x2 = 0x00000011,
    WGPUVertexFormat_Sint16x4 = 0x00000012,
    WGPUVertexFormat_Unorm16 = 0x00000013,
    WGPUVertexFormat_Unorm16x2 = 0x00000014,
    WGPUVertexFormat_Unorm16x4 = 0x00000015,
    WGPUVertexFormat_Snorm16 = 0x00000016,
    WGPUVertexFormat_Snorm16x2 = 0x00000017,
    WGPUVertexFormat_Snorm16x4 = 0x00000018,
    WGPUVertexFormat_Float16 = 0x00000019,
    WGPUVertexFormat_Float16x2 = 0x0000001A,
    WGPUVertexFormat_Float16x4 = 0x0000001B,
    WGPUVertexFormat_Float32 = 0x0000001C,
    WGPUVertexFormat_Float32x2 = 0x0000001D,
    WGPUVertexFormat_Float32x3 = 0x0000001E,
    WGPUVertexFormat_Float32x4 = 0x0000001F,
    WGPUVertexFormat_Uint32 = 0x00000020,
    WGPUVertexFormat_Uint32x2 = 0x00000021,
    WGPUVertexFormat_Uint32x3 = 0x00000022,
    WGPUVertexFormat_Uint32x4 = 0x00000023,
    WGPUVertexFormat_Sint32 = 0x00000024,
    WGPUVertexFormat_Sint32x2 = 0x00000025,
    WGPUVertexFormat_Sint32x3 = 0x00000026,
    WGPUVertexFormat_Sint32x4 = 0x00000027,
    WGPUVertexFormat_Unorm10_10_10_2 = 0x00000028,
    WGPUVertexFormat_Unorm8x4BGRA = 0x00000029,
    WGPUVertexFormat_Force32 = 0x7FFFFFFF
} WGPUVertexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexStepMode {
    WGPUVertexStepMode_Undefined = 0x00000000,
    WGPUVertexStepMode_Vertex = 0x00000001,
    WGPUVertexStepMode_Instance = 0x00000002,
    WGPUVertexStepMode_Force32 = 0x7FFFFFFF
} WGPUVertexStepMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUWaitStatus {
    WGPUWaitStatus_Success = 0x00000001,
    WGPUWaitStatus_TimedOut = 0x00000002,
    WGPUWaitStatus_Error = 0x00000003,
    WGPUWaitStatus_Force32 = 0x7FFFFFFF
} WGPUWaitStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUWGSLLanguageFeatureName {
    WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures = 0x00000001,
    WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct = 0x00000002,
    WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters = 0x00000003,
    WGPUWGSLLanguageFeatureName_PointerCompositeAccess = 0x00000004,
    WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout = 0x00000005,
    WGPUWGSLLanguageFeatureName_SubgroupId = 0x00000006,
    WGPUWGSLLanguageFeatureName_SizedBindingArray = 0x00050007,
    WGPUWGSLLanguageFeatureName_TexelBuffers = 0x00050008,
    WGPUWGSLLanguageFeatureName_ChromiumPrint = 0x00050009,
    WGPUWGSLLanguageFeatureName_FragmentDepth = 0x0005000A,
    WGPUWGSLLanguageFeatureName_ImmediateAddressSpace = 0x0005000B,
    WGPUWGSLLanguageFeatureName_SubgroupUniformity = 0x0005000C,
    WGPUWGSLLanguageFeatureName_TextureAndSamplerLet = 0x0005000D,
    WGPUWGSLLanguageFeatureName_BufferView = 0x0005000E,
    WGPUWGSLLanguageFeatureName_ChromiumTestingUnimplemented = 0x00050000,
    WGPUWGSLLanguageFeatureName_ChromiumTestingUnsafeExperimental = 0x00050001,
    WGPUWGSLLanguageFeatureName_ChromiumTestingExperimental = 0x00050002,
    WGPUWGSLLanguageFeatureName_ChromiumTestingShippedWithKillswitch = 0x00050003,
    WGPUWGSLLanguageFeatureName_ChromiumTestingShipped = 0x00050004,
    WGPUWGSLLanguageFeatureName_Force32 = 0x7FFFFFFF
} WGPUWGSLLanguageFeatureName WGPU_ENUM_ATTRIBUTE;

typedef WGPUFlags WGPUBufferUsage;
static const WGPUBufferUsage WGPUBufferUsage_None = 0x0000000000000000;
static const WGPUBufferUsage WGPUBufferUsage_MapRead = 0x0000000000000001;
static const WGPUBufferUsage WGPUBufferUsage_MapWrite = 0x0000000000000002;
static const WGPUBufferUsage WGPUBufferUsage_CopySrc = 0x0000000000000004;
static const WGPUBufferUsage WGPUBufferUsage_CopyDst = 0x0000000000000008;
static const WGPUBufferUsage WGPUBufferUsage_Index = 0x0000000000000010;
static const WGPUBufferUsage WGPUBufferUsage_Vertex = 0x0000000000000020;
static const WGPUBufferUsage WGPUBufferUsage_Uniform = 0x0000000000000040;
static const WGPUBufferUsage WGPUBufferUsage_Storage = 0x0000000000000080;
static const WGPUBufferUsage WGPUBufferUsage_Indirect = 0x0000000000000100;
static const WGPUBufferUsage WGPUBufferUsage_QueryResolve = 0x0000000000000200;
static const WGPUBufferUsage WGPUBufferUsage_TexelBuffer = 0x0000000000000400;

typedef WGPUFlags WGPUColorWriteMask;
static const WGPUColorWriteMask WGPUColorWriteMask_None = 0x0000000000000000;
static const WGPUColorWriteMask WGPUColorWriteMask_Red = 0x0000000000000001;
static const WGPUColorWriteMask WGPUColorWriteMask_Green = 0x0000000000000002;
static const WGPUColorWriteMask WGPUColorWriteMask_Blue = 0x0000000000000004;
static const WGPUColorWriteMask WGPUColorWriteMask_Alpha = 0x0000000000000008;
static const WGPUColorWriteMask WGPUColorWriteMask_All = 0x000000000000000F;

typedef WGPUFlags WGPUHeapProperty;
static const WGPUHeapProperty WGPUHeapProperty_None = 0x0000000000000000;
static const WGPUHeapProperty WGPUHeapProperty_DeviceLocal = 0x0000000000000001;
static const WGPUHeapProperty WGPUHeapProperty_HostVisible = 0x0000000000000002;
static const WGPUHeapProperty WGPUHeapProperty_HostCoherent = 0x0000000000000004;
static const WGPUHeapProperty WGPUHeapProperty_HostUncached = 0x0000000000000008;
static const WGPUHeapProperty WGPUHeapProperty_HostCached = 0x0000000000000010;

typedef WGPUFlags WGPUMapMode;
static const WGPUMapMode WGPUMapMode_None = 0x0000000000000000;
static const WGPUMapMode WGPUMapMode_Read = 0x0000000000000001;
static const WGPUMapMode WGPUMapMode_Write = 0x0000000000000002;

typedef WGPUFlags WGPUShaderStage;
static const WGPUShaderStage WGPUShaderStage_None = 0x0000000000000000;
static const WGPUShaderStage WGPUShaderStage_Vertex = 0x0000000000000001;
static const WGPUShaderStage WGPUShaderStage_Fragment = 0x0000000000000002;
static const WGPUShaderStage WGPUShaderStage_Compute = 0x0000000000000004;

typedef WGPUFlags WGPUTextureUsage;
static const WGPUTextureUsage WGPUTextureUsage_None = 0x0000000000000000;
static const WGPUTextureUsage WGPUTextureUsage_CopySrc = 0x0000000000000001;
static const WGPUTextureUsage WGPUTextureUsage_CopyDst = 0x0000000000000002;
static const WGPUTextureUsage WGPUTextureUsage_TextureBinding = 0x0000000000000004;
static const WGPUTextureUsage WGPUTextureUsage_StorageBinding = 0x0000000000000008;
static const WGPUTextureUsage WGPUTextureUsage_RenderAttachment = 0x0000000000000010;
static const WGPUTextureUsage WGPUTextureUsage_TransientAttachment = 0x0000000000000020;
static const WGPUTextureUsage WGPUTextureUsage_StorageAttachment = 0x0000000000000040;

typedef void (*WGPUCallback)(void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef size_t (*WGPUDawnLoadCacheDataFunction)(void const * key, size_t keySize, void * value, size_t valueSize, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUDawnStoreCacheDataFunction)(void const * key, size_t keySize, void const * value, size_t valueSize, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProc)(void) WGPU_FUNCTION_ATTRIBUTE;

// Callback function pointers
typedef void (*WGPUBufferMapCallback)(WGPUMapAsyncStatus status, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUCompilationInfoCallback)(WGPUCompilationInfoRequestStatus status, struct WGPUCompilationInfo const * compilationInfo, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUCreateComputePipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPUComputePipeline pipeline, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUCreateRenderPipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPURenderPipeline pipeline, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUDeviceLostCallback)(WGPUDevice const * device, WGPUDeviceLostReason reason, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPULoggingCallback)(WGPULoggingType type, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUPopErrorScopeCallback)(WGPUPopErrorScopeStatus status, WGPUErrorType type, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUQueueWorkDoneCallback)(WGPUQueueWorkDoneStatus status, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPURequestAdapterCallback)(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPURequestDeviceCallback)(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUUncapturedErrorCallback)(WGPUDevice const * device, WGPUErrorType type, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

typedef struct WGPUChainedStruct {
    struct WGPUChainedStruct * next;
    WGPUSType sType;
} WGPUChainedStruct WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBufferMapCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUBufferMapCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUBufferMapCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_MAP_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferMapCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCompilationInfoCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUCompilationInfoCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCompilationInfoCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_INFO_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationInfoCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCreateComputePipelineAsyncCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUCreateComputePipelineAsyncCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCreateComputePipelineAsyncCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CREATE_COMPUTE_PIPELINE_ASYNC_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCreateComputePipelineAsyncCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCreateRenderPipelineAsyncCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUCreateRenderPipelineAsyncCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCreateRenderPipelineAsyncCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CREATE_RENDER_PIPELINE_ASYNC_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCreateRenderPipelineAsyncCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUDeviceLostCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUDeviceLostCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUDeviceLostCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEVICE_LOST_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDeviceLostCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPULoggingCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPULoggingCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPULoggingCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_LOGGING_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPULoggingCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUPopErrorScopeCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUPopErrorScopeCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUPopErrorScopeCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_POP_ERROR_SCOPE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPopErrorScopeCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUQueueWorkDoneCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPUQueueWorkDoneCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUQueueWorkDoneCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUEUE_WORK_DONE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQueueWorkDoneCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPURequestAdapterCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPURequestAdapterCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPURequestAdapterCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPURequestDeviceCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUCallbackMode mode;
    WGPURequestDeviceCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPURequestDeviceCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestDeviceCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/_wgpu_ENUM_ZERO_INIT(WGPUCallbackMode) _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUUncapturedErrorCallbackInfo {
    WGPUChainedStruct * nextInChain;
    WGPUUncapturedErrorCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUUncapturedErrorCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUUncapturedErrorCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUAdapterPropertiesD3D {
    WGPUChainedStruct chain;
    uint32_t shaderModel;
} WGPUAdapterPropertiesD3D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_PROPERTIES_D3D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterPropertiesD3D, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_AdapterPropertiesD3D _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.shaderModel=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUAdapterPropertiesVk {
    WGPUChainedStruct chain;
    uint32_t driverVersion;
} WGPUAdapterPropertiesVk WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_PROPERTIES_VK_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterPropertiesVk, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_AdapterPropertiesVk _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.driverVersion=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUAdapterPropertiesWGPU {
    WGPUChainedStruct chain;
    WGPUBackendType backendType;
} WGPUAdapterPropertiesWGPU WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_PROPERTIES_WGPU_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterPropertiesWGPU, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_AdapterPropertiesWGPU _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.backendType=*/WGPUBackendType_Undefined _wgpu_COMMA \
})

typedef struct WGPUBindingResource {
    WGPUChainedStruct * nextInChain;
    WGPU_NULLABLE WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
    WGPU_NULLABLE WGPUSampler sampler;
    WGPU_NULLABLE WGPUTextureView textureView;
} WGPUBindingResource WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BINDING_RESOURCE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindingResource, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.buffer=*/NULL _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.size=*/WGPU_WHOLE_SIZE _wgpu_COMMA \
    /*.sampler=*/NULL _wgpu_COMMA \
    /*.textureView=*/NULL _wgpu_COMMA \
})

typedef struct WGPUBlendComponent {
    WGPUBlendOperation operation;
    WGPUBlendFactor srcFactor;
    WGPUBlendFactor dstFactor;
} WGPUBlendComponent WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BLEND_COMPONENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBlendComponent, { \
    /*.operation=*/WGPUBlendOperation_Undefined _wgpu_COMMA \
    /*.srcFactor=*/WGPUBlendFactor_Undefined _wgpu_COMMA \
    /*.dstFactor=*/WGPUBlendFactor_Undefined _wgpu_COMMA \
})

typedef struct WGPUBufferBindingLayout {
    WGPUChainedStruct * nextInChain;
    WGPUBufferBindingType type;
    WGPUBool hasDynamicOffset;
    uint64_t minBindingSize;
} WGPUBufferBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.type=*/WGPUBufferBindingType_Undefined _wgpu_COMMA \
    /*.hasDynamicOffset=*/WGPU_FALSE _wgpu_COMMA \
    /*.minBindingSize=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUBufferDescriptor
typedef struct WGPUBufferHostMappedPointer {
    WGPUChainedStruct chain;
    void * pointer;
    WGPUCallback disposeCallback;
    void * userdata;
} WGPUBufferHostMappedPointer WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_HOST_MAPPED_POINTER_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferHostMappedPointer, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_BufferHostMappedPointer _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.pointer=*/NULL _wgpu_COMMA \
    /*.disposeCallback=*/NULL _wgpu_COMMA \
    /*.userdata=*/NULL _wgpu_COMMA \
})

typedef struct WGPUColor {
    double r;
    double g;
    double b;
    double a;
} WGPUColor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COLOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUColor, { \
    /*.r=*/0. _wgpu_COMMA \
    /*.g=*/0. _wgpu_COMMA \
    /*.b=*/0. _wgpu_COMMA \
    /*.a=*/0. _wgpu_COMMA \
})

// Can be chained in WGPUColorTargetState
typedef struct WGPUColorTargetStateExpandResolveTextureDawn {
    WGPUChainedStruct chain;
    WGPUBool enabled;
} WGPUColorTargetStateExpandResolveTextureDawn WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COLOR_TARGET_STATE_EXPAND_RESOLVE_TEXTURE_DAWN_INIT _wgpu_MAKE_INIT_STRUCT(WGPUColorTargetStateExpandResolveTextureDawn, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ColorTargetStateExpandResolveTextureDawn _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.enabled=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUCommandBufferDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUCommandBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCommandBufferDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

// Can be chained in WGPULimits
typedef struct WGPUCompatibilityModeLimits {
    WGPUChainedStruct chain;
    uint32_t maxStorageBuffersInVertexStage;
    uint32_t maxStorageTexturesInVertexStage;
    uint32_t maxStorageBuffersInFragmentStage;
    uint32_t maxStorageTexturesInFragmentStage;
} WGPUCompatibilityModeLimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPATIBILITY_MODE_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompatibilityModeLimits, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_CompatibilityModeLimits _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxStorageBuffersInVertexStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageTexturesInVertexStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageBuffersInFragmentStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageTexturesInFragmentStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

typedef struct WGPUConstantEntry {
    WGPUChainedStruct * nextInChain;
    WGPUStringView key;
    double value;
} WGPUConstantEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CONSTANT_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUConstantEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.key=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.value=*/0. _wgpu_COMMA \
})

typedef struct WGPUCopyTextureForBrowserOptions {
    WGPUChainedStruct * nextInChain;
    WGPUBool flipY;
    WGPUBool needsColorSpaceConversion;
    WGPUAlphaMode srcAlphaMode;
    WGPU_NULLABLE float const * srcTransferFunctionParameters;
    WGPU_NULLABLE float const * conversionMatrix;
    WGPU_NULLABLE float const * dstTransferFunctionParameters;
    WGPUAlphaMode dstAlphaMode;
    WGPUBool internalUsage;
} WGPUCopyTextureForBrowserOptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COPY_TEXTURE_FOR_BROWSER_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCopyTextureForBrowserOptions, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.flipY=*/WGPU_FALSE _wgpu_COMMA \
    /*.needsColorSpaceConversion=*/WGPU_FALSE _wgpu_COMMA \
    /*.srcAlphaMode=*/WGPUAlphaMode_Unpremultiplied _wgpu_COMMA \
    /*.srcTransferFunctionParameters=*/NULL _wgpu_COMMA \
    /*.conversionMatrix=*/NULL _wgpu_COMMA \
    /*.dstTransferFunctionParameters=*/NULL _wgpu_COMMA \
    /*.dstAlphaMode=*/WGPUAlphaMode_Unpremultiplied _wgpu_COMMA \
    /*.internalUsage=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUDawnAdapterPropertiesPowerPreference {
    WGPUChainedStruct chain;
    WGPUPowerPreference powerPreference;
} WGPUDawnAdapterPropertiesPowerPreference WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_ADAPTER_PROPERTIES_POWER_PREFERENCE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnAdapterPropertiesPowerPreference, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnAdapterPropertiesPowerPreference _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.powerPreference=*/WGPUPowerPreference_Undefined _wgpu_COMMA \
})

// Can be chained in WGPUBufferDescriptor
typedef struct WGPUDawnBufferDescriptorErrorInfoFromWireClient {
    WGPUChainedStruct chain;
    WGPUBool outOfMemory;
} WGPUDawnBufferDescriptorErrorInfoFromWireClient WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_BUFFER_DESCRIPTOR_ERROR_INFO_FROM_WIRE_CLIENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnBufferDescriptorErrorInfoFromWireClient, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.outOfMemory=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUDeviceDescriptor
typedef struct WGPUDawnCacheDeviceDescriptor {
    WGPUChainedStruct chain;
    WGPUStringView isolationKey;
    WGPUDawnLoadCacheDataFunction loadDataFunction;
    WGPUDawnStoreCacheDataFunction storeDataFunction;
    void * functionUserdata;
} WGPUDawnCacheDeviceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_CACHE_DEVICE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnCacheDeviceDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnCacheDeviceDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.isolationKey=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.loadDataFunction=*/NULL _wgpu_COMMA \
    /*.storeDataFunction=*/NULL _wgpu_COMMA \
    /*.functionUserdata=*/nullptr _wgpu_COMMA \
})

// Can be chained in WGPUCompilationMessage
typedef struct WGPUDawnCompilationMessageUtf16 {
    WGPUChainedStruct chain;
    uint64_t linePos;
    uint64_t offset;
    uint64_t length;
} WGPUDawnCompilationMessageUtf16 WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_COMPILATION_MESSAGE_UTF16_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnCompilationMessageUtf16, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnCompilationMessageUtf16 _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.linePos=*/0 _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.length=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUDeviceDescriptor
typedef struct WGPUDawnConsumeAdapterDescriptor {
    WGPUChainedStruct chain;
    WGPUBool consumeAdapter;
} WGPUDawnConsumeAdapterDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_CONSUME_ADAPTER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnConsumeAdapterDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnConsumeAdapterDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.consumeAdapter=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUDeviceDescriptor
typedef struct WGPUDawnDeviceAllocatorControl {
    WGPUChainedStruct chain;
    size_t allocatorHeapBlockSize;
} WGPUDawnDeviceAllocatorControl WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_DEVICE_ALLOCATOR_CONTROL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnDeviceAllocatorControl, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnDeviceAllocatorControl _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.allocatorHeapBlockSize=*/0 _wgpu_COMMA \
})

typedef struct WGPUDawnDrmFormatProperties {
    uint64_t modifier;
    uint32_t modifierPlaneCount;
} WGPUDawnDrmFormatProperties WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_DRM_FORMAT_PROPERTIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnDrmFormatProperties, { \
    /*.modifier=*/0 _wgpu_COMMA \
    /*.modifierPlaneCount=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUCommandEncoderDescriptor
typedef struct WGPUDawnEncoderInternalUsageDescriptor {
    WGPUChainedStruct chain;
    WGPUBool useInternalUsages;
} WGPUDawnEncoderInternalUsageDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_ENCODER_INTERNAL_USAGE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnEncoderInternalUsageDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnEncoderInternalUsageDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.useInternalUsages=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUBufferDescriptor
typedef struct WGPUDawnFakeBufferOOMForTesting {
    WGPUChainedStruct chain;
    WGPUBool fakeOOMAtWireClientMap;
    WGPUBool fakeOOMAtNativeMap;
    WGPUBool fakeOOMAtDevice;
} WGPUDawnFakeBufferOOMForTesting WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_FAKE_BUFFER_OOM_FOR_TESTING_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnFakeBufferOOMForTesting, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnFakeBufferOOMForTesting _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.fakeOOMAtWireClientMap=*/WGPU_FALSE _wgpu_COMMA \
    /*.fakeOOMAtNativeMap=*/WGPU_FALSE _wgpu_COMMA \
    /*.fakeOOMAtDevice=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUDeviceDescriptor
typedef struct WGPUDawnFakeDeviceInitializeErrorForTesting {
    WGPUChainedStruct chain;
} WGPUDawnFakeDeviceInitializeErrorForTesting WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_FAKE_DEVICE_INITIALIZE_ERROR_FOR_TESTING_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnFakeDeviceInitializeErrorForTesting, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnFakeDeviceInitializeErrorForTesting _wgpu_COMMA \
    }) _wgpu_COMMA \
})

// Can be chained in WGPULimits
typedef struct WGPUDawnHostMappedPointerLimits {
    WGPUChainedStruct chain;
    uint32_t hostMappedPointerAlignment;
} WGPUDawnHostMappedPointerLimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_HOST_MAPPED_POINTER_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnHostMappedPointerLimits, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnHostMappedPointerLimits _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.hostMappedPointerAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

typedef struct WGPUDawnInjectedInvalidSType {
    WGPUChainedStruct chain;
    WGPUSType invalidSType;
} WGPUDawnInjectedInvalidSType WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_INJECTED_INVALID_S_TYPE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnInjectedInvalidSType, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnInjectedInvalidSType _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.invalidSType=*/_wgpu_ENUM_ZERO_INIT(WGPUSType) _wgpu_COMMA \
})

// Can be chained in WGPURenderPassColorAttachment
typedef struct WGPUDawnRenderPassColorAttachmentRenderToSingleSampled {
    WGPUChainedStruct chain;
    uint32_t implicitSampleCount;
} WGPUDawnRenderPassColorAttachmentRenderToSingleSampled WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_RENDER_PASS_COLOR_ATTACHMENT_RENDER_TO_SINGLE_SAMPLED_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnRenderPassColorAttachmentRenderToSingleSampled, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.implicitSampleCount=*/1 _wgpu_COMMA \
})

// Can be chained in WGPUShaderModuleDescriptor
typedef struct WGPUDawnShaderModuleSPIRVOptionsDescriptor {
    WGPUChainedStruct chain;
    WGPUBool allowNonUniformDerivatives;
} WGPUDawnShaderModuleSPIRVOptionsDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_SHADER_MODULE_SPIRV_OPTIONS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnShaderModuleSPIRVOptionsDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.allowNonUniformDerivatives=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPULimits
typedef struct WGPUDawnTexelCopyBufferRowAlignmentLimits {
    WGPUChainedStruct chain;
    uint32_t minTexelCopyBufferRowAlignment;
} WGPUDawnTexelCopyBufferRowAlignmentLimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_TEXEL_COPY_BUFFER_ROW_ALIGNMENT_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnTexelCopyBufferRowAlignmentLimits, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnTexelCopyBufferRowAlignmentLimits _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.minTexelCopyBufferRowAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

// Can be chained in WGPUTextureDescriptor
typedef struct WGPUDawnTextureInternalUsageDescriptor {
    WGPUChainedStruct chain;
    WGPUTextureUsage internalUsage;
} WGPUDawnTextureInternalUsageDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_TEXTURE_INTERNAL_USAGE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnTextureInternalUsageDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnTextureInternalUsageDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.internalUsage=*/WGPUTextureUsage_None _wgpu_COMMA \
})

// Can be chained in WGPUInstanceDescriptor
// Can be chained in WGPURequestAdapterOptions
// Can be chained in WGPUDeviceDescriptor
typedef struct WGPUDawnTogglesDescriptor {
    WGPUChainedStruct chain;
    size_t enabledToggleCount;
    const char* const * enabledToggles;
    size_t disabledToggleCount;
    const char* const * disabledToggles;
} WGPUDawnTogglesDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_TOGGLES_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnTogglesDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnTogglesDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.enabledToggleCount=*/0 _wgpu_COMMA \
    /*.enabledToggles=*/NULL _wgpu_COMMA \
    /*.disabledToggleCount=*/0 _wgpu_COMMA \
    /*.disabledToggles=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUInstanceDescriptor
typedef struct WGPUDawnWGSLBlocklist {
    WGPUChainedStruct chain;
    size_t blocklistedFeatureCount;
    const char* const * blocklistedFeatures;
} WGPUDawnWGSLBlocklist WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_WGSL_BLOCKLIST_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnWGSLBlocklist, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnWGSLBlocklist _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.blocklistedFeatureCount=*/0 _wgpu_COMMA \
    /*.blocklistedFeatures=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUInstanceDescriptor
typedef struct WGPUDawnWireWGSLControl {
    WGPUChainedStruct chain;
    WGPUBool enableExperimental;
    WGPUBool enableUnsafe;
    WGPUBool enableTesting;
} WGPUDawnWireWGSLControl WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_WIRE_WGSL_CONTROL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnWireWGSLControl, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnWireWGSLControl _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.enableExperimental=*/WGPU_FALSE _wgpu_COMMA \
    /*.enableUnsafe=*/WGPU_FALSE _wgpu_COMMA \
    /*.enableTesting=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUEmscriptenSurfaceSourceCanvasHTMLSelector {
    WGPUChainedStruct chain;
    WGPUStringView selector;
} WGPUEmscriptenSurfaceSourceCanvasHTMLSelector WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EMSCRIPTEN_SURFACE_SOURCE_CANVAS_HTML_SELECTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUEmscriptenSurfaceSourceCanvasHTMLSelector, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.selector=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUExtent2D {
    uint32_t width;
    uint32_t height;
} WGPUExtent2D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTENT_2D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExtent2D, { \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/0 _wgpu_COMMA \
})

typedef struct WGPUExtent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depthOrArrayLayers;
} WGPUExtent3D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTENT_3D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExtent3D, { \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/1 _wgpu_COMMA \
    /*.depthOrArrayLayers=*/1 _wgpu_COMMA \
})

// Can be chained in WGPUBindGroupEntry
typedef struct WGPUExternalTextureBindingEntry {
    WGPUChainedStruct chain;
    WGPUExternalTexture externalTexture;
} WGPUExternalTextureBindingEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTERNAL_TEXTURE_BINDING_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExternalTextureBindingEntry, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExternalTextureBindingEntry _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.externalTexture=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUBindGroupLayoutEntry
typedef struct WGPUExternalTextureBindingLayout {
    WGPUChainedStruct chain;
} WGPUExternalTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTERNAL_TEXTURE_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExternalTextureBindingLayout, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExternalTextureBindingLayout _wgpu_COMMA \
    }) _wgpu_COMMA \
})

typedef struct WGPUFuture {
    uint64_t id;
} WGPUFuture WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FUTURE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFuture, { \
    /*.id=*/0 _wgpu_COMMA \
})

typedef struct WGPUInstanceLimits {
    WGPUChainedStruct * nextInChain;
    size_t timedWaitAnyMaxCount;
} WGPUInstanceLimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_INSTANCE_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceLimits, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.timedWaitAnyMaxCount=*/0 _wgpu_COMMA \
})

typedef struct WGPUINTERNAL_HAVE_EMDAWNWEBGPU_HEADER {
    WGPUBool unused;
} WGPUINTERNAL_HAVE_EMDAWNWEBGPU_HEADER WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_INTERNAL_HAVE_EMDAWNWEBGPU_HEADER_INIT _wgpu_MAKE_INIT_STRUCT(WGPUINTERNAL_HAVE_EMDAWNWEBGPU_HEADER, { \
    /*.unused=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUMemoryHeapInfo {
    WGPUHeapProperty properties;
    uint64_t size;
} WGPUMemoryHeapInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_MEMORY_HEAP_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUMemoryHeapInfo, { \
    /*.properties=*/WGPUHeapProperty_None _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
})

typedef struct WGPUMultisampleState {
    WGPUChainedStruct * nextInChain;
    uint32_t count;
    uint32_t mask;
    WGPUBool alphaToCoverageEnabled;
} WGPUMultisampleState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_MULTISAMPLE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUMultisampleState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.count=*/1 _wgpu_COMMA \
    /*.mask=*/0xFFFFFFFF _wgpu_COMMA \
    /*.alphaToCoverageEnabled=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUOrigin2D {
    uint32_t x;
    uint32_t y;
} WGPUOrigin2D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ORIGIN_2D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUOrigin2D, { \
    /*.x=*/0 _wgpu_COMMA \
    /*.y=*/0 _wgpu_COMMA \
})

typedef struct WGPUOrigin3D {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} WGPUOrigin3D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ORIGIN_3D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUOrigin3D, { \
    /*.x=*/0 _wgpu_COMMA \
    /*.y=*/0 _wgpu_COMMA \
    /*.z=*/0 _wgpu_COMMA \
})

typedef struct WGPUPassTimestampWrites {
    WGPUChainedStruct * nextInChain;
    WGPUQuerySet querySet;
    uint32_t beginningOfPassWriteIndex;
    uint32_t endOfPassWriteIndex;
} WGPUPassTimestampWrites WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PASS_TIMESTAMP_WRITES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPassTimestampWrites, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.querySet=*/NULL _wgpu_COMMA \
    /*.beginningOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
    /*.endOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
})

// Can be chained in WGPUPipelineLayoutDescriptor
typedef struct WGPUPipelineLayoutResourceTable {
    WGPUChainedStruct chain;
    WGPUBool usesResourceTable;
} WGPUPipelineLayoutResourceTable WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PIPELINE_LAYOUT_RESOURCE_TABLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutResourceTable, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_PipelineLayoutResourceTable _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.usesResourceTable=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUPipelineLayoutStorageAttachment {
    WGPUChainedStruct * nextInChain;
    uint64_t offset;
    WGPUTextureFormat format;
} WGPUPipelineLayoutStorageAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PIPELINE_LAYOUT_STORAGE_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutStorageAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
})

typedef struct WGPUPrimitiveState {
    WGPUChainedStruct * nextInChain;
    WGPUPrimitiveTopology topology;
    WGPUIndexFormat stripIndexFormat;
    WGPUFrontFace frontFace;
    WGPUCullMode cullMode;
    WGPUBool unclippedDepth;
} WGPUPrimitiveState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PRIMITIVE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPrimitiveState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.topology=*/WGPUPrimitiveTopology_Undefined _wgpu_COMMA \
    /*.stripIndexFormat=*/WGPUIndexFormat_Undefined _wgpu_COMMA \
    /*.frontFace=*/WGPUFrontFace_Undefined _wgpu_COMMA \
    /*.cullMode=*/WGPUCullMode_Undefined _wgpu_COMMA \
    /*.unclippedDepth=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUQuerySetDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUQueryType type;
    uint32_t count;
} WGPUQuerySetDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUERY_SET_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQuerySetDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.type=*/_wgpu_ENUM_ZERO_INIT(WGPUQueryType) _wgpu_COMMA \
    /*.count=*/0 _wgpu_COMMA \
})

typedef struct WGPUQueueDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUQueueDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUEUE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQueueDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPURenderBundleDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPURenderBundleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_BUNDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderBundleDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPURenderBundleEncoderDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    size_t colorFormatCount;
    WGPUTextureFormat const * colorFormats;
    WGPUTextureFormat depthStencilFormat;
    uint32_t sampleCount;
    WGPUBool depthReadOnly;
    WGPUBool stencilReadOnly;
} WGPURenderBundleEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_BUNDLE_ENCODER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderBundleEncoderDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.colorFormatCount=*/0 _wgpu_COMMA \
    /*.colorFormats=*/NULL _wgpu_COMMA \
    /*.depthStencilFormat=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.sampleCount=*/1 _wgpu_COMMA \
    /*.depthReadOnly=*/WGPU_FALSE _wgpu_COMMA \
    /*.stencilReadOnly=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPURenderPassDepthStencilAttachment {
    WGPUChainedStruct * nextInChain;
    WGPUTextureView view;
    WGPULoadOp depthLoadOp;
    WGPUStoreOp depthStoreOp;
    float depthClearValue;
    WGPUBool depthReadOnly;
    WGPULoadOp stencilLoadOp;
    WGPUStoreOp stencilStoreOp;
    uint32_t stencilClearValue;
    WGPUBool stencilReadOnly;
} WGPURenderPassDepthStencilAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDepthStencilAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.view=*/NULL _wgpu_COMMA \
    /*.depthLoadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.depthStoreOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.depthClearValue=*/WGPU_DEPTH_CLEAR_VALUE_UNDEFINED _wgpu_COMMA \
    /*.depthReadOnly=*/WGPU_FALSE _wgpu_COMMA \
    /*.stencilLoadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.stencilStoreOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.stencilClearValue=*/0 _wgpu_COMMA \
    /*.stencilReadOnly=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPURenderPassDescriptor
typedef struct WGPURenderPassDescriptorExpandResolveRect {
    WGPUChainedStruct chain;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
} WGPURenderPassDescriptorExpandResolveRect WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DESCRIPTOR_EXPAND_RESOLVE_RECT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDescriptorExpandResolveRect, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RenderPassDescriptorExpandResolveRect _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.x=*/0 _wgpu_COMMA \
    /*.y=*/0 _wgpu_COMMA \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/0 _wgpu_COMMA \
})

// Can be chained in WGPURenderPassDescriptor
typedef struct WGPURenderPassDescriptorResolveRect {
    WGPUChainedStruct chain;
    uint32_t colorOffsetX;
    uint32_t colorOffsetY;
    uint32_t resolveOffsetX;
    uint32_t resolveOffsetY;
    uint32_t width;
    uint32_t height;
} WGPURenderPassDescriptorResolveRect WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DESCRIPTOR_RESOLVE_RECT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDescriptorResolveRect, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RenderPassDescriptorResolveRect _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.colorOffsetX=*/0 _wgpu_COMMA \
    /*.colorOffsetY=*/0 _wgpu_COMMA \
    /*.resolveOffsetX=*/0 _wgpu_COMMA \
    /*.resolveOffsetY=*/0 _wgpu_COMMA \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/0 _wgpu_COMMA \
})

// Can be chained in WGPURenderPassDescriptor
typedef struct WGPURenderPassMaxDrawCount {
    WGPUChainedStruct chain;
    uint64_t maxDrawCount;
} WGPURenderPassMaxDrawCount WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_MAX_DRAW_COUNT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassMaxDrawCount, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RenderPassMaxDrawCount _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxDrawCount=*/50000000 _wgpu_COMMA \
})

// Can be chained in WGPURequestAdapterOptions
typedef struct WGPURequestAdapterWebGPUBackendOptions {
    WGPUChainedStruct chain;
} WGPURequestAdapterWebGPUBackendOptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_WEBGPU_BACKEND_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterWebGPUBackendOptions, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RequestAdapterWebGPUBackendOptions _wgpu_COMMA \
    }) _wgpu_COMMA \
})

// Can be chained in WGPURequestAdapterOptions
typedef struct WGPURequestAdapterWebXROptions {
    WGPUChainedStruct chain;
    WGPUBool xrCompatible;
} WGPURequestAdapterWebXROptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_WEBXR_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterWebXROptions, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RequestAdapterWebXROptions _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.xrCompatible=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUResourceTableDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    uint32_t size;
} WGPUResourceTableDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RESOURCE_TABLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUResourceTableDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
})

// Can be chained in WGPULimits
typedef struct WGPUResourceTableLimits {
    WGPUChainedStruct chain;
    uint32_t maxResourceTableSize;
} WGPUResourceTableLimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RESOURCE_TABLE_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUResourceTableLimits, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ResourceTableLimits _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxResourceTableSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

typedef struct WGPUSamplerBindingLayout {
    WGPUChainedStruct * nextInChain;
    WGPUSamplerBindingType type;
} WGPUSamplerBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SAMPLER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSamplerBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.type=*/WGPUSamplerBindingType_Undefined _wgpu_COMMA \
})

// Can be chained in WGPUShaderModuleDescriptor
typedef struct WGPUShaderModuleCompilationOptions {
    WGPUChainedStruct chain;
    WGPUBool strictMath;
} WGPUShaderModuleCompilationOptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_MODULE_COMPILATION_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderModuleCompilationOptions, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderModuleCompilationOptions _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.strictMath=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUShaderModuleDescriptor
typedef struct WGPUShaderSourceSPIRV {
    WGPUChainedStruct chain;
    uint32_t codeSize;
    uint32_t const * code;
} WGPUShaderSourceSPIRV WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_SOURCE_SPIRV_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderSourceSPIRV, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderSourceSPIRV _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.codeSize=*/0 _wgpu_COMMA \
    /*.code=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUShaderModuleDescriptor
typedef struct WGPUShaderSourceWGSL {
    WGPUChainedStruct chain;
    WGPUStringView code;
} WGPUShaderSourceWGSL WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_SOURCE_WGSL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderSourceWGSL, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderSourceWGSL _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.code=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedBufferMemoryBeginAccessDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUBool initialized;
    size_t fenceCount;
    WGPUSharedFence const * fences;
    uint64_t const * signaledValues;
} WGPUSharedBufferMemoryBeginAccessDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_BUFFER_MEMORY_BEGIN_ACCESS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedBufferMemoryBeginAccessDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.initialized=*/WGPU_FALSE _wgpu_COMMA \
    /*.fenceCount=*/0 _wgpu_COMMA \
    /*.fences=*/NULL _wgpu_COMMA \
    /*.signaledValues=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSharedBufferMemoryDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUSharedBufferMemoryDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_BUFFER_MEMORY_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedBufferMemoryDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedBufferMemoryEndAccessState {
    WGPUChainedStruct * nextInChain;
    WGPUBool initialized;
    size_t fenceCount;
    WGPUSharedFence const * fences;
    uint64_t const * signaledValues;
} WGPUSharedBufferMemoryEndAccessState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_BUFFER_MEMORY_END_ACCESS_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedBufferMemoryEndAccessState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.initialized=*/WGPU_FALSE _wgpu_COMMA \
    /*.fenceCount=*/0 _wgpu_COMMA \
    /*.fences=*/NULL _wgpu_COMMA \
    /*.signaledValues=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSharedBufferMemoryProperties {
    WGPUChainedStruct * nextInChain;
    WGPUBufferUsage usage;
    uint64_t size;
} WGPUSharedBufferMemoryProperties WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_BUFFER_MEMORY_PROPERTIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedBufferMemoryProperties, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.usage=*/WGPUBufferUsage_None _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceDXGISharedHandleDescriptor {
    WGPUChainedStruct chain;
    void * handle;
} WGPUSharedFenceDXGISharedHandleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_DXGI_SHARED_HANDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceDXGISharedHandleDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceDXGISharedHandleDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceDXGISharedHandleExportInfo {
    WGPUChainedStruct chain;
    void * handle;
} WGPUSharedFenceDXGISharedHandleExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_DXGI_SHARED_HANDLE_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceDXGISharedHandleExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceDXGISharedHandleExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceEGLSyncDescriptor {
    WGPUChainedStruct chain;
    void * sync;
} WGPUSharedFenceEGLSyncDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_EGL_SYNC_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceEGLSyncDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceEGLSyncDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.sync=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceEGLSyncExportInfo {
    WGPUChainedStruct chain;
    void * sync;
} WGPUSharedFenceEGLSyncExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_EGL_SYNC_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceEGLSyncExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceEGLSyncExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.sync=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceMTLSharedEventDescriptor {
    WGPUChainedStruct chain;
    void * sharedEvent;
} WGPUSharedFenceMTLSharedEventDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_MTL_SHARED_EVENT_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceMTLSharedEventDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceMTLSharedEventDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.sharedEvent=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceMTLSharedEventExportInfo {
    WGPUChainedStruct chain;
    void * sharedEvent;
} WGPUSharedFenceMTLSharedEventExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_MTL_SHARED_EVENT_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceMTLSharedEventExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceMTLSharedEventExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.sharedEvent=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceSyncFDDescriptor {
    WGPUChainedStruct chain;
    int handle;
} WGPUSharedFenceSyncFDDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_SYNC_FD_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceSyncFDDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceSyncFDDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceSyncFDExportInfo {
    WGPUChainedStruct chain;
    int handle;
} WGPUSharedFenceSyncFDExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_SYNC_FD_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceSyncFDExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceSyncFDExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor {
    WGPUChainedStruct chain;
    int handle;
} WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_VK_SEMAPHORE_OPAQUE_FD_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceVkSemaphoreOpaqueFDDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo {
    WGPUChainedStruct chain;
    int handle;
} WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_VK_SEMAPHORE_OPAQUE_FD_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceVkSemaphoreOpaqueFDExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceDescriptor
typedef struct WGPUSharedFenceVkSemaphoreZirconHandleDescriptor {
    WGPUChainedStruct chain;
    uint32_t handle;
} WGPUSharedFenceVkSemaphoreZirconHandleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_VK_SEMAPHORE_ZIRCON_HANDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceVkSemaphoreZirconHandleDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedFenceExportInfo
typedef struct WGPUSharedFenceVkSemaphoreZirconHandleExportInfo {
    WGPUChainedStruct chain;
    uint32_t handle;
} WGPUSharedFenceVkSemaphoreZirconHandleExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_VK_SEMAPHORE_ZIRCON_HANDLE_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedFenceVkSemaphoreZirconHandleExportInfo _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryAHardwareBufferDescriptor {
    WGPUChainedStruct chain;
    void * handle;
    WGPUBool useExternalFormat;
} WGPUSharedTextureMemoryAHardwareBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_A_HARDWARE_BUFFER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryAHardwareBufferDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryAHardwareBufferDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/NULL _wgpu_COMMA \
    /*.useExternalFormat=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryBeginAccessDescriptor
typedef struct WGPUSharedTextureMemoryD3D11BeginState {
    WGPUChainedStruct chain;
    WGPUBool requiresEndAccessFence;
} WGPUSharedTextureMemoryD3D11BeginState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_D3D11_BEGIN_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryD3D11BeginState, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryD3D11BeginState _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.requiresEndAccessFence=*/WGPU_TRUE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryBeginAccessDescriptor
typedef struct WGPUSharedTextureMemoryD3DSwapchainBeginState {
    WGPUChainedStruct chain;
    WGPUBool isSwapchain;
} WGPUSharedTextureMemoryD3DSwapchainBeginState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_D3D_SWAPCHAIN_BEGIN_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryD3DSwapchainBeginState, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryD3DSwapchainBeginState _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.isSwapchain=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUSharedTextureMemoryDmaBufPlane {
    int fd;
    uint64_t offset;
    uint32_t stride;
} WGPUSharedTextureMemoryDmaBufPlane WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_DMA_BUF_PLANE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryDmaBufPlane, { \
    /*.fd=*/0 _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.stride=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryDXGISharedHandleDescriptor {
    WGPUChainedStruct chain;
    void * handle;
    WGPUBool useKeyedMutex;
} WGPUSharedTextureMemoryDXGISharedHandleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_DXGI_SHARED_HANDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryDXGISharedHandleDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryDXGISharedHandleDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.handle=*/NULL _wgpu_COMMA \
    /*.useKeyedMutex=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryEGLImageDescriptor {
    WGPUChainedStruct chain;
    void * image;
} WGPUSharedTextureMemoryEGLImageDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_EGL_IMAGE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryEGLImageDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryEGLImageDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.image=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryIOSurfaceDescriptor {
    WGPUChainedStruct chain;
    void * ioSurface;
    WGPUBool allowStorageBinding;
} WGPUSharedTextureMemoryIOSurfaceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_IO_SURFACE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryIOSurfaceDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryIOSurfaceDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.ioSurface=*/NULL _wgpu_COMMA \
    /*.allowStorageBinding=*/WGPU_TRUE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryOpaqueFDDescriptor {
    WGPUChainedStruct chain;
    void const * vkImageCreateInfo;
    int memoryFD;
    uint32_t memoryTypeIndex;
    uint64_t allocationSize;
    WGPUBool dedicatedAllocation;
} WGPUSharedTextureMemoryOpaqueFDDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_OPAQUE_FD_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryOpaqueFDDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryOpaqueFDDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.vkImageCreateInfo=*/NULL _wgpu_COMMA \
    /*.memoryFD=*/0 _wgpu_COMMA \
    /*.memoryTypeIndex=*/0 _wgpu_COMMA \
    /*.allocationSize=*/0 _wgpu_COMMA \
    /*.dedicatedAllocation=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor {
    WGPUChainedStruct chain;
    WGPUBool dedicatedAllocation;
} WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_VK_DEDICATED_ALLOCATION_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryVkDedicatedAllocationDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.dedicatedAllocation=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryBeginAccessDescriptor
typedef struct WGPUSharedTextureMemoryVkImageLayoutBeginState {
    WGPUChainedStruct chain;
    int32_t oldLayout;
    int32_t newLayout;
} WGPUSharedTextureMemoryVkImageLayoutBeginState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_VK_IMAGE_LAYOUT_BEGIN_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryVkImageLayoutBeginState, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryVkImageLayoutBeginState _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.oldLayout=*/0 _wgpu_COMMA \
    /*.newLayout=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryEndAccessState
typedef struct WGPUSharedTextureMemoryVkImageLayoutEndState {
    WGPUChainedStruct chain;
    int32_t oldLayout;
    int32_t newLayout;
} WGPUSharedTextureMemoryVkImageLayoutEndState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_VK_IMAGE_LAYOUT_END_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryVkImageLayoutEndState, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryVkImageLayoutEndState _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.oldLayout=*/0 _wgpu_COMMA \
    /*.newLayout=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryZirconHandleDescriptor {
    WGPUChainedStruct chain;
    uint32_t memoryFD;
    uint64_t allocationSize;
} WGPUSharedTextureMemoryZirconHandleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_ZIRCON_HANDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryZirconHandleDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryZirconHandleDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.memoryFD=*/0 _wgpu_COMMA \
    /*.allocationSize=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUBindGroupLayoutEntry
typedef struct WGPUStaticSamplerBindingLayout {
    WGPUChainedStruct chain;
    WGPUSampler sampler;
    uint32_t sampledTextureBinding;
} WGPUStaticSamplerBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STATIC_SAMPLER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStaticSamplerBindingLayout, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_StaticSamplerBindingLayout _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.sampler=*/NULL _wgpu_COMMA \
    /*.sampledTextureBinding=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

typedef struct WGPUStencilFaceState {
    WGPUCompareFunction compare;
    WGPUStencilOperation failOp;
    WGPUStencilOperation depthFailOp;
    WGPUStencilOperation passOp;
} WGPUStencilFaceState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STENCIL_FACE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStencilFaceState, { \
    /*.compare=*/WGPUCompareFunction_Undefined _wgpu_COMMA \
    /*.failOp=*/WGPUStencilOperation_Undefined _wgpu_COMMA \
    /*.depthFailOp=*/WGPUStencilOperation_Undefined _wgpu_COMMA \
    /*.passOp=*/WGPUStencilOperation_Undefined _wgpu_COMMA \
})

typedef struct WGPUStorageTextureBindingLayout {
    WGPUChainedStruct * nextInChain;
    WGPUStorageTextureAccess access;
    WGPUTextureFormat format;
    WGPUTextureViewDimension viewDimension;
} WGPUStorageTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStorageTextureBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.access=*/WGPUStorageTextureAccess_Undefined _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.viewDimension=*/WGPUTextureViewDimension_Undefined _wgpu_COMMA \
})

typedef struct WGPUSubgroupMatrixConfig {
    WGPUSubgroupMatrixComponentType componentType;
    WGPUSubgroupMatrixComponentType resultComponentType;
    uint32_t M;
    uint32_t N;
    uint32_t K;
} WGPUSubgroupMatrixConfig WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUBGROUP_MATRIX_CONFIG_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSubgroupMatrixConfig, { \
    /*.componentType=*/_wgpu_ENUM_ZERO_INIT(WGPUSubgroupMatrixComponentType) _wgpu_COMMA \
    /*.resultComponentType=*/_wgpu_ENUM_ZERO_INIT(WGPUSubgroupMatrixComponentType) _wgpu_COMMA \
    /*.M=*/0 _wgpu_COMMA \
    /*.N=*/0 _wgpu_COMMA \
    /*.K=*/0 _wgpu_COMMA \
})

typedef struct WGPUSupportedFeatures {
    size_t featureCount;
    WGPUFeatureName const * features;
} WGPUSupportedFeatures WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUPPORTED_FEATURES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedFeatures, { \
    /*.featureCount=*/0 _wgpu_COMMA \
    /*.features=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSupportedInstanceFeatures {
    size_t featureCount;
    WGPUInstanceFeatureName const * features;
} WGPUSupportedInstanceFeatures WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUPPORTED_INSTANCE_FEATURES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedInstanceFeatures, { \
    /*.featureCount=*/0 _wgpu_COMMA \
    /*.features=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSupportedWGSLLanguageFeatures {
    size_t featureCount;
    WGPUWGSLLanguageFeatureName const * features;
} WGPUSupportedWGSLLanguageFeatures WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUPPORTED_WGSL_LANGUAGE_FEATURES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedWGSLLanguageFeatures, { \
    /*.featureCount=*/0 _wgpu_COMMA \
    /*.features=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSurfaceCapabilities {
    WGPUChainedStruct * nextInChain;
    WGPUTextureUsage usages;
    size_t formatCount;
    WGPUTextureFormat const * formats;
    size_t presentModeCount;
    WGPUPresentMode const * presentModes;
    size_t alphaModeCount;
    WGPUCompositeAlphaMode const * alphaModes;
} WGPUSurfaceCapabilities WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_CAPABILITIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceCapabilities, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.usages=*/WGPUTextureUsage_None _wgpu_COMMA \
    /*.formatCount=*/0 _wgpu_COMMA \
    /*.formats=*/NULL _wgpu_COMMA \
    /*.presentModeCount=*/0 _wgpu_COMMA \
    /*.presentModes=*/NULL _wgpu_COMMA \
    /*.alphaModeCount=*/0 _wgpu_COMMA \
    /*.alphaModes=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceColorManagement {
    WGPUChainedStruct chain;
    WGPUPredefinedColorSpace colorSpace;
    WGPUToneMappingMode toneMappingMode;
} WGPUSurfaceColorManagement WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_COLOR_MANAGEMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceColorManagement, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceColorManagement _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.colorSpace=*/_wgpu_ENUM_ZERO_INIT(WGPUPredefinedColorSpace) _wgpu_COMMA \
    /*.toneMappingMode=*/_wgpu_ENUM_ZERO_INIT(WGPUToneMappingMode) _wgpu_COMMA \
})

typedef struct WGPUSurfaceConfiguration {
    WGPUChainedStruct * nextInChain;
    WGPUDevice device;
    WGPUTextureFormat format;
    WGPUTextureUsage usage;
    uint32_t width;
    uint32_t height;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
    WGPUCompositeAlphaMode alphaMode;
    WGPUPresentMode presentMode;
} WGPUSurfaceConfiguration WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_CONFIGURATION_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceConfiguration, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.device=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_RenderAttachment _wgpu_COMMA \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/0 _wgpu_COMMA \
    /*.viewFormatCount=*/0 _wgpu_COMMA \
    /*.viewFormats=*/NULL _wgpu_COMMA \
    /*.alphaMode=*/WGPUCompositeAlphaMode_Auto _wgpu_COMMA \
    /*.presentMode=*/WGPUPresentMode_Undefined _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceDescriptorFromWindowsCoreWindow {
    WGPUChainedStruct chain;
    void * coreWindow;
} WGPUSurfaceDescriptorFromWindowsCoreWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_DESCRIPTOR_FROM_WINDOWS_CORE_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceDescriptorFromWindowsCoreWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceDescriptorFromWindowsCoreWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.coreWindow=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel {
    WGPUChainedStruct chain;
    void * swapChainPanel;
} WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_DESCRIPTOR_FROM_WINDOWS_UWP_SWAP_CHAIN_PANEL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceDescriptorFromWindowsUWPSwapChainPanel _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.swapChainPanel=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel {
    WGPUChainedStruct chain;
    void * swapChainPanel;
} WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_DESCRIPTOR_FROM_WINDOWS_WINUI_SWAP_CHAIN_PANEL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceDescriptorFromWindowsWinUISwapChainPanel _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.swapChainPanel=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceAndroidNativeWindow {
    WGPUChainedStruct chain;
    void * window;
} WGPUSurfaceSourceAndroidNativeWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_ANDROID_NATIVE_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceAndroidNativeWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceAndroidNativeWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.window=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceMetalLayer {
    WGPUChainedStruct chain;
    void * layer;
} WGPUSurfaceSourceMetalLayer WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_METAL_LAYER_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceMetalLayer, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceMetalLayer _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.layer=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceWaylandSurface {
    WGPUChainedStruct chain;
    void * display;
    void * surface;
} WGPUSurfaceSourceWaylandSurface WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_WAYLAND_SURFACE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceWaylandSurface, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceWaylandSurface _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.display=*/NULL _wgpu_COMMA \
    /*.surface=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceWindowsHWND {
    WGPUChainedStruct chain;
    void * hinstance;
    void * hwnd;
} WGPUSurfaceSourceWindowsHWND WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceWindowsHWND, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceWindowsHWND _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.hinstance=*/NULL _wgpu_COMMA \
    /*.hwnd=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceXCBWindow {
    WGPUChainedStruct chain;
    void * connection;
    uint32_t window;
} WGPUSurfaceSourceXCBWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_XCB_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceXCBWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceXCBWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.connection=*/NULL _wgpu_COMMA \
    /*.window=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSurfaceDescriptor
typedef struct WGPUSurfaceSourceXlibWindow {
    WGPUChainedStruct chain;
    void * display;
    uint64_t window;
} WGPUSurfaceSourceXlibWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_XLIB_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceXlibWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceXlibWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.display=*/NULL _wgpu_COMMA \
    /*.window=*/0 _wgpu_COMMA \
})

typedef struct WGPUSurfaceTexture {
    WGPUChainedStruct * nextInChain;
    WGPUTexture texture;
    WGPUSurfaceGetCurrentTextureStatus status;
} WGPUSurfaceTexture WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_TEXTURE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceTexture, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.texture=*/NULL _wgpu_COMMA \
    /*.status=*/_wgpu_ENUM_ZERO_INIT(WGPUSurfaceGetCurrentTextureStatus) _wgpu_COMMA \
})

// Can be chained in WGPUBindGroupEntry
typedef struct WGPUTexelBufferBindingEntry {
    WGPUChainedStruct chain;
    WGPUTexelBufferView texelBufferView;
} WGPUTexelBufferBindingEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_BUFFER_BINDING_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelBufferBindingEntry, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_TexelBufferBindingEntry _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.texelBufferView=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUBindGroupLayoutEntry
typedef struct WGPUTexelBufferBindingLayout {
    WGPUChainedStruct chain;
    WGPUTexelBufferAccess access;
    WGPUTextureFormat format;
} WGPUTexelBufferBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_BUFFER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelBufferBindingLayout, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_TexelBufferBindingLayout _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.access=*/WGPUTexelBufferAccess_Undefined _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
})

typedef struct WGPUTexelBufferViewDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUTextureFormat format;
    uint64_t offset;
    uint64_t size;
} WGPUTexelBufferViewDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_BUFFER_VIEW_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelBufferViewDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.size=*/WGPU_WHOLE_SIZE _wgpu_COMMA \
})

typedef struct WGPUTexelCopyBufferLayout {
    uint64_t offset;
    uint32_t bytesPerRow;
    uint32_t rowsPerImage;
} WGPUTexelCopyBufferLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyBufferLayout, { \
    /*.offset=*/0 _wgpu_COMMA \
    /*.bytesPerRow=*/WGPU_COPY_STRIDE_UNDEFINED _wgpu_COMMA \
    /*.rowsPerImage=*/WGPU_COPY_STRIDE_UNDEFINED _wgpu_COMMA \
})

typedef struct WGPUTextureBindingLayout {
    WGPUChainedStruct * nextInChain;
    WGPUTextureSampleType sampleType;
    WGPUTextureViewDimension viewDimension;
    WGPUBool multisampled;
} WGPUTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.sampleType=*/WGPUTextureSampleType_Undefined _wgpu_COMMA \
    /*.viewDimension=*/WGPUTextureViewDimension_Undefined _wgpu_COMMA \
    /*.multisampled=*/WGPU_FALSE _wgpu_COMMA \
})

// Can be chained in WGPUTextureDescriptor
typedef struct WGPUTextureBindingViewDimensionDescriptor {
    WGPUChainedStruct chain;
    WGPUTextureViewDimension textureBindingViewDimension;
} WGPUTextureBindingViewDimensionDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_BINDING_VIEW_DIMENSION_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureBindingViewDimensionDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_TextureBindingViewDimensionDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.textureBindingViewDimension=*/WGPUTextureViewDimension_Undefined _wgpu_COMMA \
})

typedef struct WGPUTextureComponentSwizzle {
    WGPUComponentSwizzle r;
    WGPUComponentSwizzle g;
    WGPUComponentSwizzle b;
    WGPUComponentSwizzle a;
} WGPUTextureComponentSwizzle WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_COMPONENT_SWIZZLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureComponentSwizzle, { \
    /*.r=*/WGPUComponentSwizzle_Undefined _wgpu_COMMA \
    /*.g=*/WGPUComponentSwizzle_Undefined _wgpu_COMMA \
    /*.b=*/WGPUComponentSwizzle_Undefined _wgpu_COMMA \
    /*.a=*/WGPUComponentSwizzle_Undefined _wgpu_COMMA \
})

typedef struct WGPUVertexAttribute {
    WGPUChainedStruct * nextInChain;
    WGPUVertexFormat format;
    uint64_t offset;
    uint32_t shaderLocation;
} WGPUVertexAttribute WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_ATTRIBUTE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexAttribute, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/_wgpu_ENUM_ZERO_INIT(WGPUVertexFormat) _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.shaderLocation=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUSamplerDescriptor
// Can be chained in WGPUTextureViewDescriptor
typedef struct WGPUYCbCrVkDescriptor {
    WGPUChainedStruct chain;
    uint32_t vkFormat;
    uint32_t vkYCbCrModel;
    uint32_t vkYCbCrRange;
    uint32_t vkComponentSwizzleRed;
    uint32_t vkComponentSwizzleGreen;
    uint32_t vkComponentSwizzleBlue;
    uint32_t vkComponentSwizzleAlpha;
    uint32_t vkXChromaOffset;
    uint32_t vkYChromaOffset;
    WGPUFilterMode vkChromaFilter;
    WGPUBool forceExplicitReconstruction;
    uint64_t externalFormat;
} WGPUYCbCrVkDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_Y_CB_CR_VK_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUYCbCrVkDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_YCbCrVkDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.vkFormat=*/0 _wgpu_COMMA \
    /*.vkYCbCrModel=*/0 _wgpu_COMMA \
    /*.vkYCbCrRange=*/0 _wgpu_COMMA \
    /*.vkComponentSwizzleRed=*/0 _wgpu_COMMA \
    /*.vkComponentSwizzleGreen=*/0 _wgpu_COMMA \
    /*.vkComponentSwizzleBlue=*/0 _wgpu_COMMA \
    /*.vkComponentSwizzleAlpha=*/0 _wgpu_COMMA \
    /*.vkXChromaOffset=*/0 _wgpu_COMMA \
    /*.vkYChromaOffset=*/0 _wgpu_COMMA \
    /*.vkChromaFilter=*/WGPUFilterMode_Undefined _wgpu_COMMA \
    /*.forceExplicitReconstruction=*/WGPU_FALSE _wgpu_COMMA \
    /*.externalFormat=*/0 _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUAdapterPropertiesMemoryHeaps {
    WGPUChainedStruct chain;
    size_t heapCount;
    WGPUMemoryHeapInfo const * heapInfo;
} WGPUAdapterPropertiesMemoryHeaps WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_PROPERTIES_MEMORY_HEAPS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterPropertiesMemoryHeaps, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_AdapterPropertiesMemoryHeaps _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.heapCount=*/0 _wgpu_COMMA \
    /*.heapInfo=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUAdapterInfo
typedef struct WGPUAdapterPropertiesSubgroupMatrixConfigs {
    WGPUChainedStruct chain;
    size_t configCount;
    WGPUSubgroupMatrixConfig const * configs;
} WGPUAdapterPropertiesSubgroupMatrixConfigs WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_PROPERTIES_SUBGROUP_MATRIX_CONFIGS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterPropertiesSubgroupMatrixConfigs, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_AdapterPropertiesSubgroupMatrixConfigs _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.configCount=*/0 _wgpu_COMMA \
    /*.configs=*/NULL _wgpu_COMMA \
})

typedef struct WGPUAHardwareBufferProperties {
    WGPUYCbCrVkDescriptor yCbCrInfo;
} WGPUAHardwareBufferProperties WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_A_HARDWARE_BUFFER_PROPERTIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAHardwareBufferProperties, { \
    /*.yCbCrInfo=*/WGPU_Y_CB_CR_VK_DESCRIPTOR_INIT _wgpu_COMMA \
})

typedef struct WGPUBindGroupEntry {
    WGPUChainedStruct * nextInChain;
    uint32_t binding;
    WGPU_NULLABLE WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
    WGPU_NULLABLE WGPUSampler sampler;
    WGPU_NULLABLE WGPUTextureView textureView;
} WGPUBindGroupEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.binding=*/0 _wgpu_COMMA \
    /*.buffer=*/NULL _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.size=*/WGPU_WHOLE_SIZE _wgpu_COMMA \
    /*.sampler=*/NULL _wgpu_COMMA \
    /*.textureView=*/NULL _wgpu_COMMA \
})

typedef struct WGPUBindGroupLayoutEntry {
    WGPUChainedStruct * nextInChain;
    uint32_t binding;
    WGPUShaderStage visibility;
    uint32_t bindingArraySize;
    WGPUBufferBindingLayout buffer;
    WGPUSamplerBindingLayout sampler;
    WGPUTextureBindingLayout texture;
    WGPUStorageTextureBindingLayout storageTexture;
} WGPUBindGroupLayoutEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupLayoutEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.binding=*/0 _wgpu_COMMA \
    /*.visibility=*/WGPUShaderStage_None _wgpu_COMMA \
    /*.bindingArraySize=*/0 _wgpu_COMMA \
    /*.buffer=*/_wgpu_STRUCT_ZERO_INIT _wgpu_COMMA \
    /*.sampler=*/_wgpu_STRUCT_ZERO_INIT _wgpu_COMMA \
    /*.texture=*/_wgpu_STRUCT_ZERO_INIT _wgpu_COMMA \
    /*.storageTexture=*/_wgpu_STRUCT_ZERO_INIT _wgpu_COMMA \
})

typedef struct WGPUBlendState {
    WGPUBlendComponent color;
    WGPUBlendComponent alpha;
} WGPUBlendState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BLEND_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBlendState, { \
    /*.color=*/WGPU_BLEND_COMPONENT_INIT _wgpu_COMMA \
    /*.alpha=*/WGPU_BLEND_COMPONENT_INIT _wgpu_COMMA \
})

typedef struct WGPUBufferDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUBufferUsage usage;
    uint64_t size;
    WGPUBool mappedAtCreation;
} WGPUBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.usage=*/WGPUBufferUsage_None _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
    /*.mappedAtCreation=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUCommandEncoderDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUCommandEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCommandEncoderDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUCompilationMessage {
    WGPUChainedStruct * nextInChain;
    WGPUStringView message;
    WGPUCompilationMessageType type;
    uint64_t lineNum;
    uint64_t linePos;
    uint64_t offset;
    uint64_t length;
} WGPUCompilationMessage WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_MESSAGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationMessage, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.message=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.type=*/_wgpu_ENUM_ZERO_INIT(WGPUCompilationMessageType) _wgpu_COMMA \
    /*.lineNum=*/0 _wgpu_COMMA \
    /*.linePos=*/0 _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.length=*/0 _wgpu_COMMA \
})

typedef struct WGPUComputePassDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPU_NULLABLE WGPUPassTimestampWrites const * timestampWrites;
} WGPUComputePassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_PASS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputePassDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.timestampWrites=*/NULL _wgpu_COMMA \
})

typedef struct WGPUComputeState {
    WGPUChainedStruct * nextInChain;
    WGPUShaderModule module;
    WGPUStringView entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
} WGPUComputeState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputeState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUDawnFormatCapabilities
typedef struct WGPUDawnDrmFormatCapabilities {
    WGPUChainedStruct chain;
    size_t propertiesCount;
    WGPUDawnDrmFormatProperties const * properties;
} WGPUDawnDrmFormatCapabilities WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_DRM_FORMAT_CAPABILITIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnDrmFormatCapabilities, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DawnDrmFormatCapabilities _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.propertiesCount=*/0 _wgpu_COMMA \
    /*.properties=*/NULL _wgpu_COMMA \
})

typedef struct WGPUDepthStencilState {
    WGPUChainedStruct * nextInChain;
    WGPUTextureFormat format;
    WGPUOptionalBool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilFaceState stencilFront;
    WGPUStencilFaceState stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
} WGPUDepthStencilState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEPTH_STENCIL_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDepthStencilState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.depthWriteEnabled=*/WGPUOptionalBool_Undefined _wgpu_COMMA \
    /*.depthCompare=*/WGPUCompareFunction_Undefined _wgpu_COMMA \
    /*.stencilFront=*/WGPU_STENCIL_FACE_STATE_INIT _wgpu_COMMA \
    /*.stencilBack=*/WGPU_STENCIL_FACE_STATE_INIT _wgpu_COMMA \
    /*.stencilReadMask=*/0xFFFFFFFF _wgpu_COMMA \
    /*.stencilWriteMask=*/0xFFFFFFFF _wgpu_COMMA \
    /*.depthBias=*/0 _wgpu_COMMA \
    /*.depthBiasSlopeScale=*/0.f _wgpu_COMMA \
    /*.depthBiasClamp=*/0.f _wgpu_COMMA \
})

typedef struct WGPUExternalTextureDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUTextureView plane0;
    WGPU_NULLABLE WGPUTextureView plane1;
    WGPUOrigin2D cropOrigin;
    WGPUExtent2D cropSize;
    WGPUExtent2D apparentSize;
    WGPUBool doYuvToRgbConversionOnly;
    WGPU_NULLABLE float const * yuvToRgbConversionMatrix;
    float const * srcTransferFunctionParameters;
    float const * dstTransferFunctionParameters;
    float const * gamutConversionMatrix;
    WGPUBool mirrored;
    WGPUExternalTextureRotation rotation;
} WGPUExternalTextureDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTERNAL_TEXTURE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExternalTextureDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.plane0=*/NULL _wgpu_COMMA \
    /*.plane1=*/NULL _wgpu_COMMA \
    /*.cropOrigin=*/WGPU_ORIGIN_2D_INIT _wgpu_COMMA \
    /*.cropSize=*/WGPU_EXTENT_2D_INIT _wgpu_COMMA \
    /*.apparentSize=*/WGPU_EXTENT_2D_INIT _wgpu_COMMA \
    /*.doYuvToRgbConversionOnly=*/WGPU_FALSE _wgpu_COMMA \
    /*.yuvToRgbConversionMatrix=*/NULL _wgpu_COMMA \
    /*.srcTransferFunctionParameters=*/NULL _wgpu_COMMA \
    /*.dstTransferFunctionParameters=*/NULL _wgpu_COMMA \
    /*.gamutConversionMatrix=*/NULL _wgpu_COMMA \
    /*.mirrored=*/WGPU_FALSE _wgpu_COMMA \
    /*.rotation=*/WGPUExternalTextureRotation_Rotate0Degrees _wgpu_COMMA \
})

typedef struct WGPUFutureWaitInfo {
    WGPUFuture future;
    WGPUBool completed;
} WGPUFutureWaitInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FUTURE_WAIT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFutureWaitInfo, { \
    /*.future=*/WGPU_FUTURE_INIT _wgpu_COMMA \
    /*.completed=*/WGPU_FALSE _wgpu_COMMA \
})

typedef struct WGPUImageCopyExternalTexture {
    WGPUChainedStruct * nextInChain;
    WGPUExternalTexture externalTexture;
    WGPUOrigin3D origin;
    WGPUExtent2D naturalSize;
} WGPUImageCopyExternalTexture WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_IMAGE_COPY_EXTERNAL_TEXTURE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUImageCopyExternalTexture, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.externalTexture=*/NULL _wgpu_COMMA \
    /*.origin=*/WGPU_ORIGIN_3D_INIT _wgpu_COMMA \
    /*.naturalSize=*/WGPU_EXTENT_2D_INIT _wgpu_COMMA \
})

typedef struct WGPUInstanceDescriptor {
    WGPUChainedStruct * nextInChain;
    size_t requiredFeatureCount;
    WGPUInstanceFeatureName const * requiredFeatures;
    WGPU_NULLABLE WGPUInstanceLimits const * requiredLimits;
} WGPUInstanceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_INSTANCE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.requiredFeatureCount=*/0 _wgpu_COMMA \
    /*.requiredFeatures=*/NULL _wgpu_COMMA \
    /*.requiredLimits=*/NULL _wgpu_COMMA \
})

typedef struct WGPULimits {
    WGPUChainedStruct * nextInChain;
    uint32_t maxTextureDimension1D;
    uint32_t maxTextureDimension2D;
    uint32_t maxTextureDimension3D;
    uint32_t maxTextureArrayLayers;
    uint32_t maxBindGroups;
    uint32_t maxBindGroupsPlusVertexBuffers;
    uint32_t maxBindingsPerBindGroup;
    uint32_t maxDynamicUniformBuffersPerPipelineLayout;
    uint32_t maxDynamicStorageBuffersPerPipelineLayout;
    uint32_t maxSampledTexturesPerShaderStage;
    uint32_t maxSamplersPerShaderStage;
    uint32_t maxStorageBuffersPerShaderStage;
    uint32_t maxStorageTexturesPerShaderStage;
    uint32_t maxUniformBuffersPerShaderStage;
    uint64_t maxUniformBufferBindingSize;
    uint64_t maxStorageBufferBindingSize;
    uint32_t minUniformBufferOffsetAlignment;
    uint32_t minStorageBufferOffsetAlignment;
    uint32_t maxVertexBuffers;
    uint64_t maxBufferSize;
    uint32_t maxVertexAttributes;
    uint32_t maxVertexBufferArrayStride;
    uint32_t maxInterStageShaderVariables;
    uint32_t maxColorAttachments;
    uint32_t maxColorAttachmentBytesPerSample;
    uint32_t maxComputeWorkgroupStorageSize;
    uint32_t maxComputeInvocationsPerWorkgroup;
    uint32_t maxComputeWorkgroupSizeX;
    uint32_t maxComputeWorkgroupSizeY;
    uint32_t maxComputeWorkgroupSizeZ;
    uint32_t maxComputeWorkgroupsPerDimension;
    uint32_t maxImmediateSize;
} WGPULimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPULimits, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.maxTextureDimension1D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureDimension2D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureDimension3D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureArrayLayers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindGroups=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindGroupsPlusVertexBuffers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindingsPerBindGroup=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxDynamicUniformBuffersPerPipelineLayout=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxDynamicStorageBuffersPerPipelineLayout=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxSampledTexturesPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxSamplersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageBuffersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageTexturesPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxUniformBuffersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxUniformBufferBindingSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.maxStorageBufferBindingSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.minUniformBufferOffsetAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.minStorageBufferOffsetAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxVertexBuffers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBufferSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.maxVertexAttributes=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxVertexBufferArrayStride=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxInterStageShaderVariables=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxColorAttachments=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxColorAttachmentBytesPerSample=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupStorageSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeInvocationsPerWorkgroup=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeX=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeY=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeZ=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupsPerDimension=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxImmediateSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

// Can be chained in WGPUPipelineLayoutDescriptor
typedef struct WGPUPipelineLayoutPixelLocalStorage {
    WGPUChainedStruct chain;
    uint64_t totalPixelLocalStorageSize;
    size_t storageAttachmentCount;
    WGPUPipelineLayoutStorageAttachment const * storageAttachments;
} WGPUPipelineLayoutPixelLocalStorage WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PIPELINE_LAYOUT_PIXEL_LOCAL_STORAGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutPixelLocalStorage, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_PipelineLayoutPixelLocalStorage _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.totalPixelLocalStorageSize=*/0 _wgpu_COMMA \
    /*.storageAttachmentCount=*/0 _wgpu_COMMA \
    /*.storageAttachments=*/NULL _wgpu_COMMA \
})

typedef struct WGPURenderPassColorAttachment {
    WGPUChainedStruct * nextInChain;
    WGPU_NULLABLE WGPUTextureView view;
    uint32_t depthSlice;
    WGPU_NULLABLE WGPUTextureView resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColor clearValue;
} WGPURenderPassColorAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassColorAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.view=*/NULL _wgpu_COMMA \
    /*.depthSlice=*/WGPU_DEPTH_SLICE_UNDEFINED _wgpu_COMMA \
    /*.resolveTarget=*/NULL _wgpu_COMMA \
    /*.loadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.storeOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.clearValue=*/WGPU_COLOR_INIT _wgpu_COMMA \
})

typedef struct WGPURenderPassStorageAttachment {
    WGPUChainedStruct * nextInChain;
    uint64_t offset;
    WGPUTextureView storage;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColor clearValue;
} WGPURenderPassStorageAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_STORAGE_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassStorageAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.storage=*/NULL _wgpu_COMMA \
    /*.loadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.storeOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.clearValue=*/WGPU_COLOR_INIT _wgpu_COMMA \
})

typedef struct WGPURequestAdapterOptions {
    WGPUChainedStruct * nextInChain;
    WGPUFeatureLevel featureLevel;
    WGPUPowerPreference powerPreference;
    WGPUBool forceFallbackAdapter;
    WGPUBackendType backendType;
    WGPU_NULLABLE WGPUSurface compatibleSurface;
} WGPURequestAdapterOptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterOptions, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.featureLevel=*/WGPUFeatureLevel_Undefined _wgpu_COMMA \
    /*.powerPreference=*/WGPUPowerPreference_Undefined _wgpu_COMMA \
    /*.forceFallbackAdapter=*/WGPU_FALSE _wgpu_COMMA \
    /*.backendType=*/WGPUBackendType_Undefined _wgpu_COMMA \
    /*.compatibleSurface=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSamplerDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUMipmapFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;
    uint16_t maxAnisotropy;
} WGPUSamplerDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SAMPLER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSamplerDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.addressModeU=*/WGPUAddressMode_Undefined _wgpu_COMMA \
    /*.addressModeV=*/WGPUAddressMode_Undefined _wgpu_COMMA \
    /*.addressModeW=*/WGPUAddressMode_Undefined _wgpu_COMMA \
    /*.magFilter=*/WGPUFilterMode_Undefined _wgpu_COMMA \
    /*.minFilter=*/WGPUFilterMode_Undefined _wgpu_COMMA \
    /*.mipmapFilter=*/WGPUMipmapFilterMode_Undefined _wgpu_COMMA \
    /*.lodMinClamp=*/0.f _wgpu_COMMA \
    /*.lodMaxClamp=*/32.f _wgpu_COMMA \
    /*.compare=*/WGPUCompareFunction_Undefined _wgpu_COMMA \
    /*.maxAnisotropy=*/1 _wgpu_COMMA \
})

typedef struct WGPUShaderModuleDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUShaderModuleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_MODULE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderModuleDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedFenceDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUSharedFenceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedFenceExportInfo {
    WGPUChainedStruct * nextInChain;
    WGPUSharedFenceType type;
} WGPUSharedFenceExportInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_FENCE_EXPORT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedFenceExportInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.type=*/_wgpu_ENUM_ZERO_INIT(WGPUSharedFenceType) _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryProperties
typedef struct WGPUSharedTextureMemoryAHardwareBufferProperties {
    WGPUChainedStruct chain;
    WGPUYCbCrVkDescriptor yCbCrInfo;
} WGPUSharedTextureMemoryAHardwareBufferProperties WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_A_HARDWARE_BUFFER_PROPERTIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryAHardwareBufferProperties, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryAHardwareBufferProperties _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.yCbCrInfo=*/WGPU_Y_CB_CR_VK_DESCRIPTOR_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedTextureMemoryBeginAccessDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUBool concurrentRead;
    WGPUBool initialized;
    size_t fenceCount;
    WGPUSharedFence const * fences;
    uint64_t const * signaledValues;
} WGPUSharedTextureMemoryBeginAccessDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_BEGIN_ACCESS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryBeginAccessDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.concurrentRead=*/WGPU_FALSE _wgpu_COMMA \
    /*.initialized=*/WGPU_FALSE _wgpu_COMMA \
    /*.fenceCount=*/0 _wgpu_COMMA \
    /*.fences=*/NULL _wgpu_COMMA \
    /*.signaledValues=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryDescriptor
typedef struct WGPUSharedTextureMemoryDmaBufDescriptor {
    WGPUChainedStruct chain;
    WGPUExtent3D size;
    uint32_t drmFormat;
    uint64_t drmModifier;
    size_t planeCount;
    WGPUSharedTextureMemoryDmaBufPlane const * planes;
} WGPUSharedTextureMemoryDmaBufDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_DMA_BUF_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryDmaBufDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryDmaBufDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.size=*/WGPU_EXTENT_3D_INIT _wgpu_COMMA \
    /*.drmFormat=*/0 _wgpu_COMMA \
    /*.drmModifier=*/0 _wgpu_COMMA \
    /*.planeCount=*/0 _wgpu_COMMA \
    /*.planes=*/NULL _wgpu_COMMA \
})

// Can be chained in WGPUSharedTextureMemoryEndAccessState
typedef struct WGPUSharedTextureMemoryMetalEndAccessState {
    WGPUChainedStruct chain;
    WGPUFuture commandsScheduledFuture;
} WGPUSharedTextureMemoryMetalEndAccessState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_METAL_END_ACCESS_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryMetalEndAccessState, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SharedTextureMemoryMetalEndAccessState _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.commandsScheduledFuture=*/WGPU_FUTURE_INIT _wgpu_COMMA \
})

typedef struct WGPUSurfaceDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUSurfaceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUTexelCopyBufferInfo {
    WGPUTexelCopyBufferLayout layout;
    WGPUBuffer buffer;
} WGPUTexelCopyBufferInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_BUFFER_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyBufferInfo, { \
    /*.layout=*/WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT _wgpu_COMMA \
    /*.buffer=*/NULL _wgpu_COMMA \
})

typedef struct WGPUTexelCopyTextureInfo {
    WGPUTexture texture;
    uint32_t mipLevel;
    WGPUOrigin3D origin;
    WGPUTextureAspect aspect;
} WGPUTexelCopyTextureInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_TEXTURE_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyTextureInfo, { \
    /*.texture=*/NULL _wgpu_COMMA \
    /*.mipLevel=*/0 _wgpu_COMMA \
    /*.origin=*/WGPU_ORIGIN_3D_INIT _wgpu_COMMA \
    /*.aspect=*/WGPUTextureAspect_Undefined _wgpu_COMMA \
})

// Can be chained in WGPUTextureViewDescriptor
typedef struct WGPUTextureComponentSwizzleDescriptor {
    WGPUChainedStruct chain;
    WGPUTextureComponentSwizzle swizzle;
} WGPUTextureComponentSwizzleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_COMPONENT_SWIZZLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureComponentSwizzleDescriptor, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_TextureComponentSwizzleDescriptor _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.swizzle=*/WGPU_TEXTURE_COMPONENT_SWIZZLE_INIT _wgpu_COMMA \
})

typedef struct WGPUTextureDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUTextureUsage usage;
    WGPUTextureDimension dimension;
    WGPUExtent3D size;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
} WGPUTextureDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_None _wgpu_COMMA \
    /*.dimension=*/WGPUTextureDimension_Undefined _wgpu_COMMA \
    /*.size=*/WGPU_EXTENT_3D_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.mipLevelCount=*/1 _wgpu_COMMA \
    /*.sampleCount=*/1 _wgpu_COMMA \
    /*.viewFormatCount=*/0 _wgpu_COMMA \
    /*.viewFormats=*/NULL _wgpu_COMMA \
})

typedef struct WGPUVertexBufferLayout {
    WGPUChainedStruct * nextInChain;
    WGPUVertexStepMode stepMode;
    uint64_t arrayStride;
    size_t attributeCount;
    WGPUVertexAttribute const * attributes;
} WGPUVertexBufferLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_BUFFER_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexBufferLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.stepMode=*/WGPUVertexStepMode_Undefined _wgpu_COMMA \
    /*.arrayStride=*/0 _wgpu_COMMA \
    /*.attributeCount=*/0 _wgpu_COMMA \
    /*.attributes=*/NULL _wgpu_COMMA \
})

typedef struct WGPUAdapterInfo {
    WGPUChainedStruct * nextInChain;
    WGPUStringView vendor;
    WGPUStringView architecture;
    WGPUStringView device;
    WGPUStringView description;
    WGPUBackendType backendType;
    WGPUAdapterType adapterType;
    uint32_t vendorID;
    uint32_t deviceID;
    uint32_t subgroupMinSize;
    uint32_t subgroupMaxSize;
} WGPUAdapterInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.vendor=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.architecture=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.device=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.description=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.backendType=*/WGPUBackendType_Undefined _wgpu_COMMA \
    /*.adapterType=*/_wgpu_ENUM_ZERO_INIT(WGPUAdapterType) _wgpu_COMMA \
    /*.vendorID=*/0 _wgpu_COMMA \
    /*.deviceID=*/0 _wgpu_COMMA \
    /*.subgroupMinSize=*/0 _wgpu_COMMA \
    /*.subgroupMaxSize=*/0 _wgpu_COMMA \
})

typedef struct WGPUBindGroupDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUBindGroupLayout layout;
    size_t entryCount;
    WGPUBindGroupEntry const * entries;
} WGPUBindGroupDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.entryCount=*/0 _wgpu_COMMA \
    /*.entries=*/NULL _wgpu_COMMA \
})

typedef struct WGPUBindGroupLayoutDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    size_t entryCount;
    WGPUBindGroupLayoutEntry const * entries;
} WGPUBindGroupLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupLayoutDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.entryCount=*/0 _wgpu_COMMA \
    /*.entries=*/NULL _wgpu_COMMA \
})

typedef struct WGPUColorTargetState {
    WGPUChainedStruct * nextInChain;
    WGPUTextureFormat format;
    WGPU_NULLABLE WGPUBlendState const * blend;
    WGPUColorWriteMask writeMask;
} WGPUColorTargetState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COLOR_TARGET_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUColorTargetState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.blend=*/NULL _wgpu_COMMA \
    /*.writeMask=*/WGPUColorWriteMask_All _wgpu_COMMA \
})

typedef struct WGPUCompilationInfo {
    WGPUChainedStruct * nextInChain;
    size_t messageCount;
    WGPUCompilationMessage const * messages;
} WGPUCompilationInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.messageCount=*/0 _wgpu_COMMA \
    /*.messages=*/NULL _wgpu_COMMA \
})

typedef struct WGPUComputePipelineDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPU_NULLABLE WGPUPipelineLayout layout;
    WGPUComputeState compute;
} WGPUComputePipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_PIPELINE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputePipelineDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.compute=*/WGPU_COMPUTE_STATE_INIT _wgpu_COMMA \
})

typedef struct WGPUDawnFormatCapabilities {
    WGPUChainedStruct * nextInChain;
} WGPUDawnFormatCapabilities WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DAWN_FORMAT_CAPABILITIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDawnFormatCapabilities, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
})

typedef struct WGPUDeviceDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    size_t requiredFeatureCount;
    WGPUFeatureName const * requiredFeatures;
    WGPU_NULLABLE WGPULimits const * requiredLimits;
    WGPUQueueDescriptor defaultQueue;
    WGPUDeviceLostCallbackInfo deviceLostCallbackInfo;
    WGPUUncapturedErrorCallbackInfo uncapturedErrorCallbackInfo;
} WGPUDeviceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEVICE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDeviceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.requiredFeatureCount=*/0 _wgpu_COMMA \
    /*.requiredFeatures=*/NULL _wgpu_COMMA \
    /*.requiredLimits=*/NULL _wgpu_COMMA \
    /*.defaultQueue=*/WGPU_QUEUE_DESCRIPTOR_INIT _wgpu_COMMA \
    /*.deviceLostCallbackInfo=*/WGPU_DEVICE_LOST_CALLBACK_INFO_INIT _wgpu_COMMA \
    /*.uncapturedErrorCallbackInfo=*/WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT _wgpu_COMMA \
})

typedef struct WGPUPipelineLayoutDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    size_t bindGroupLayoutCount;
    WGPUBindGroupLayout const * bindGroupLayouts;
    uint32_t immediateSize;
} WGPUPipelineLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.bindGroupLayoutCount=*/0 _wgpu_COMMA \
    /*.bindGroupLayouts=*/NULL _wgpu_COMMA \
    /*.immediateSize=*/0 _wgpu_COMMA \
})

// Can be chained in WGPURenderPassDescriptor
typedef struct WGPURenderPassPixelLocalStorage {
    WGPUChainedStruct chain;
    uint64_t totalPixelLocalStorageSize;
    size_t storageAttachmentCount;
    WGPURenderPassStorageAttachment const * storageAttachments;
} WGPURenderPassPixelLocalStorage WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_PIXEL_LOCAL_STORAGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassPixelLocalStorage, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RenderPassPixelLocalStorage _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.totalPixelLocalStorageSize=*/0 _wgpu_COMMA \
    /*.storageAttachmentCount=*/0 _wgpu_COMMA \
    /*.storageAttachments=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSharedTextureMemoryDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
} WGPUSharedTextureMemoryDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

typedef struct WGPUSharedTextureMemoryEndAccessState {
    WGPUChainedStruct * nextInChain;
    WGPUBool initialized;
    size_t fenceCount;
    WGPUSharedFence const * fences;
    uint64_t const * signaledValues;
} WGPUSharedTextureMemoryEndAccessState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_END_ACCESS_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryEndAccessState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.initialized=*/WGPU_FALSE _wgpu_COMMA \
    /*.fenceCount=*/0 _wgpu_COMMA \
    /*.fences=*/NULL _wgpu_COMMA \
    /*.signaledValues=*/NULL _wgpu_COMMA \
})

typedef struct WGPUSharedTextureMemoryProperties {
    WGPUChainedStruct * nextInChain;
    WGPUTextureUsage usage;
    WGPUExtent3D size;
    WGPUTextureFormat format;
} WGPUSharedTextureMemoryProperties WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHARED_TEXTURE_MEMORY_PROPERTIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSharedTextureMemoryProperties, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_None _wgpu_COMMA \
    /*.size=*/WGPU_EXTENT_3D_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
})

typedef struct WGPUTextureViewDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPUTextureFormat format;
    WGPUTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    WGPUTextureAspect aspect;
    WGPUTextureUsage usage;
} WGPUTextureViewDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureViewDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.dimension=*/WGPUTextureViewDimension_Undefined _wgpu_COMMA \
    /*.baseMipLevel=*/0 _wgpu_COMMA \
    /*.mipLevelCount=*/WGPU_MIP_LEVEL_COUNT_UNDEFINED _wgpu_COMMA \
    /*.baseArrayLayer=*/0 _wgpu_COMMA \
    /*.arrayLayerCount=*/WGPU_ARRAY_LAYER_COUNT_UNDEFINED _wgpu_COMMA \
    /*.aspect=*/WGPUTextureAspect_Undefined _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_None _wgpu_COMMA \
})

typedef struct WGPUVertexState {
    WGPUChainedStruct * nextInChain;
    WGPUShaderModule module;
    WGPUStringView entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
    size_t bufferCount;
    WGPUVertexBufferLayout const * buffers;
} WGPUVertexState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
    /*.bufferCount=*/0 _wgpu_COMMA \
    /*.buffers=*/NULL _wgpu_COMMA \
})

typedef struct WGPUFragmentState {
    WGPUChainedStruct * nextInChain;
    WGPUShaderModule module;
    WGPUStringView entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
    size_t targetCount;
    WGPUColorTargetState const * targets;
} WGPUFragmentState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FRAGMENT_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFragmentState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
    /*.targetCount=*/0 _wgpu_COMMA \
    /*.targets=*/NULL _wgpu_COMMA \
})

typedef struct WGPURenderPassDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    size_t colorAttachmentCount;
    WGPURenderPassColorAttachment const * colorAttachments;
    WGPU_NULLABLE WGPURenderPassDepthStencilAttachment const * depthStencilAttachment;
    WGPU_NULLABLE WGPUQuerySet occlusionQuerySet;
    WGPU_NULLABLE WGPUPassTimestampWrites const * timestampWrites;
} WGPURenderPassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.colorAttachmentCount=*/0 _wgpu_COMMA \
    /*.colorAttachments=*/NULL _wgpu_COMMA \
    /*.depthStencilAttachment=*/NULL _wgpu_COMMA \
    /*.occlusionQuerySet=*/NULL _wgpu_COMMA \
    /*.timestampWrites=*/NULL _wgpu_COMMA \
})

typedef struct WGPURenderPipelineDescriptor {
    WGPUChainedStruct * nextInChain;
    WGPUStringView label;
    WGPU_NULLABLE WGPUPipelineLayout layout;
    WGPUVertexState vertex;
    WGPUPrimitiveState primitive;
    WGPU_NULLABLE WGPUDepthStencilState const * depthStencil;
    WGPUMultisampleState multisample;
    WGPU_NULLABLE WGPUFragmentState const * fragment;
} WGPURenderPipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPipelineDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.vertex=*/WGPU_VERTEX_STATE_INIT _wgpu_COMMA \
    /*.primitive=*/WGPU_PRIMITIVE_STATE_INIT _wgpu_COMMA \
    /*.depthStencil=*/NULL _wgpu_COMMA \
    /*.multisample=*/WGPU_MULTISAMPLE_STATE_INIT _wgpu_COMMA \
    /*.fragment=*/NULL _wgpu_COMMA \
})

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WGPU_SKIP_PROCS)
// TODO(374150686): Remove these Emscripten specific declarations from the
// header once they are fully deprecated.
WGPU_EXPORT WGPUDevice emscripten_webgpu_get_device(void);
// Global procs
typedef WGPUInstance (*WGPUProcCreateInstance)(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcGetInstanceFeatures)(WGPUSupportedInstanceFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcGetInstanceLimits)(WGPUInstanceLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcHasInstanceFeature)(WGPUInstanceFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUProc (*WGPUProcGetProcAddress)(WGPUStringView procName) WGPU_FUNCTION_ATTRIBUTE;


// Procs of Adapter
typedef WGPUDevice (*WGPUProcAdapterCreateDevice)(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterGetFeatures)(WGPUAdapter adapter, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcAdapterGetFormatCapabilities)(WGPUAdapter adapter, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcAdapterGetInfo)(WGPUAdapter adapter, WGPUAdapterInfo * info) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUInstance (*WGPUProcAdapterGetInstance)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcAdapterGetLimits)(WGPUAdapter adapter, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcAdapterHasFeature)(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcAdapterRequestDevice)(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterAddRef)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterRelease)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;

// Procs of AdapterInfo
typedef void (*WGPUProcAdapterInfoFreeMembers)(WGPUAdapterInfo adapterInfo) WGPU_FUNCTION_ATTRIBUTE;

// Procs of AdapterPropertiesMemoryHeaps
typedef void (*WGPUProcAdapterPropertiesMemoryHeapsFreeMembers)(WGPUAdapterPropertiesMemoryHeaps adapterPropertiesMemoryHeaps) WGPU_FUNCTION_ATTRIBUTE;

// Procs of AdapterPropertiesSubgroupMatrixConfigs
typedef void (*WGPUProcAdapterPropertiesSubgroupMatrixConfigsFreeMembers)(WGPUAdapterPropertiesSubgroupMatrixConfigs adapterPropertiesSubgroupMatrixConfigs) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroup
typedef void (*WGPUProcBindGroupSetLabel)(WGPUBindGroup bindGroup, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupAddRef)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupRelease)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroupLayout
typedef void (*WGPUProcBindGroupLayoutSetLabel)(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupLayoutAddRef)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupLayoutRelease)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Buffer
typedef WGPUTexelBufferView (*WGPUProcBufferCreateTexelView)(WGPUBuffer buffer, WGPUTexelBufferViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferDestroy)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void const * (*WGPUProcBufferGetConstMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void * (*WGPUProcBufferGetMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBufferMapState (*WGPUProcBufferGetMapState)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef uint64_t (*WGPUProcBufferGetSize)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBufferUsage (*WGPUProcBufferGetUsage)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcBufferMapAsync)(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcBufferReadMappedRange)(WGPUBuffer buffer, size_t offset, void * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferSetLabel)(WGPUBuffer buffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferUnmap)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcBufferWriteMappedRange)(WGPUBuffer buffer, size_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferAddRef)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferRelease)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandBuffer
typedef void (*WGPUProcCommandBufferSetLabel)(WGPUCommandBuffer commandBuffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandBufferAddRef)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandBufferRelease)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandEncoder
typedef WGPUComputePassEncoder (*WGPUProcCommandEncoderBeginComputePass)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderPassEncoder (*WGPUProcCommandEncoderBeginRenderPass)(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderClearBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyBufferToBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyBufferToTexture)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyTextureToBuffer)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyTextureToTexture)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUCommandBuffer (*WGPUProcCommandEncoderFinish)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderInjectValidationError)(WGPUCommandEncoder commandEncoder, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderInsertDebugMarker)(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderPopDebugGroup)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderPushDebugGroup)(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderResolveQuerySet)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderSetLabel)(WGPUCommandEncoder commandEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderSetResourceTable)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUResourceTable table) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderWriteBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderWriteTimestamp)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderAddRef)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderRelease)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePassEncoder
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroups)(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroupsIndirect)(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderEnd)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderInsertDebugMarker)(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderPopDebugGroup)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderPushDebugGroup)(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetBindGroup)(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetImmediates)(WGPUComputePassEncoder computePassEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetLabel)(WGPUComputePassEncoder computePassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetPipeline)(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderWriteTimestamp)(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderAddRef)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderRelease)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePipeline
typedef WGPUBindGroupLayout (*WGPUProcComputePipelineGetBindGroupLayout)(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineSetLabel)(WGPUComputePipeline computePipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineAddRef)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineRelease)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of DawnDrmFormatCapabilities
typedef void (*WGPUProcDawnDrmFormatCapabilitiesFreeMembers)(WGPUDawnDrmFormatCapabilities dawnDrmFormatCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Device
typedef WGPUBindGroup (*WGPUProcDeviceCreateBindGroup)(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBindGroupLayout (*WGPUProcDeviceCreateBindGroupLayout)(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPU_NULLABLE WGPUBuffer (*WGPUProcDeviceCreateBuffer)(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUCommandEncoder (*WGPUProcDeviceCreateCommandEncoder)(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUComputePipeline (*WGPUProcDeviceCreateComputePipeline)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcDeviceCreateComputePipelineAsync)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBuffer (*WGPUProcDeviceCreateErrorBuffer)(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUExternalTexture (*WGPUProcDeviceCreateErrorExternalTexture)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUShaderModule (*WGPUProcDeviceCreateErrorShaderModule)(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTexture (*WGPUProcDeviceCreateErrorTexture)(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUExternalTexture (*WGPUProcDeviceCreateExternalTexture)(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUPipelineLayout (*WGPUProcDeviceCreatePipelineLayout)(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQuerySet (*WGPUProcDeviceCreateQuerySet)(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderBundleEncoder (*WGPUProcDeviceCreateRenderBundleEncoder)(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderPipeline (*WGPUProcDeviceCreateRenderPipeline)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcDeviceCreateRenderPipelineAsync)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUResourceTable (*WGPUProcDeviceCreateResourceTable)(WGPUDevice device, WGPUResourceTableDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUSampler (*WGPUProcDeviceCreateSampler)(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUShaderModule (*WGPUProcDeviceCreateShaderModule)(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTexture (*WGPUProcDeviceCreateTexture)(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceDestroy)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceForceLoss)(WGPUDevice device, WGPUDeviceLostReason type, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUAdapter (*WGPUProcDeviceGetAdapter)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcDeviceGetAdapterInfo)(WGPUDevice device, WGPUAdapterInfo * adapterInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcDeviceGetAHardwareBufferProperties)(WGPUDevice device, void * handle, WGPUAHardwareBufferProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceGetFeatures)(WGPUDevice device, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcDeviceGetLimits)(WGPUDevice device, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcDeviceGetLostFuture)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQueue (*WGPUProcDeviceGetQueue)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcDeviceHasFeature)(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUSharedBufferMemory (*WGPUProcDeviceImportSharedBufferMemory)(WGPUDevice device, WGPUSharedBufferMemoryDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUSharedFence (*WGPUProcDeviceImportSharedFence)(WGPUDevice device, WGPUSharedFenceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUSharedTextureMemory (*WGPUProcDeviceImportSharedTextureMemory)(WGPUDevice device, WGPUSharedTextureMemoryDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceInjectError)(WGPUDevice device, WGPUErrorType type, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcDevicePopErrorScope)(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDevicePushErrorScope)(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceSetLabel)(WGPUDevice device, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceSetLoggingCallback)(WGPUDevice device, WGPULoggingCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceTick)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceValidateTextureDescriptor)(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceAddRef)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceRelease)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ExternalTexture
typedef void (*WGPUProcExternalTextureDestroy)(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcExternalTextureExpire)(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcExternalTextureRefresh)(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcExternalTextureSetLabel)(WGPUExternalTexture externalTexture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcExternalTextureAddRef)(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcExternalTextureRelease)(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Instance
typedef WGPUSurface (*WGPUProcInstanceCreateSurface)(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceGetWGSLLanguageFeatures)(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcInstanceHasWGSLLanguageFeature)(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceProcessEvents)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcInstanceRequestAdapter)(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUWaitStatus (*WGPUProcInstanceWaitAny)(WGPUInstance instance, size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo * futures, uint64_t timeoutNS) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceAddRef)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceRelease)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;

// Procs of PipelineLayout
typedef void (*WGPUProcPipelineLayoutSetLabel)(WGPUPipelineLayout pipelineLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcPipelineLayoutAddRef)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcPipelineLayoutRelease)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of QuerySet
typedef void (*WGPUProcQuerySetDestroy)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcQuerySetGetCount)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQueryType (*WGPUProcQuerySetGetType)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetSetLabel)(WGPUQuerySet querySet, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetAddRef)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetRelease)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Queue
typedef void (*WGPUProcQueueCopyExternalTextureForBrowser)(WGPUQueue queue, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueCopyTextureForBrowser)(WGPUQueue queue, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUFuture (*WGPUProcQueueOnSubmittedWorkDone)(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueSetLabel)(WGPUQueue queue, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueSubmit)(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueWriteBuffer)(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueWriteTexture)(WGPUQueue queue, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueAddRef)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueRelease)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundle
typedef void (*WGPUProcRenderBundleSetLabel)(WGPURenderBundle renderBundle, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleAddRef)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleRelease)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundleEncoder
typedef void (*WGPUProcRenderBundleEncoderDraw)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndexed)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndexedIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderBundle (*WGPUProcRenderBundleEncoderFinish)(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderInsertDebugMarker)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderPopDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderPushDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetBindGroup)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetImmediates)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetIndexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetLabel)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetPipeline)(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetVertexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderAddRef)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderRelease)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPassEncoder
typedef void (*WGPUProcRenderPassEncoderBeginOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDraw)(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndexed)(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndexedIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderEnd)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderEndOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderExecuteBundles)(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderInsertDebugMarker)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndexedIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderPixelLocalStorageBarrier)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderPopDebugGroup)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderPushDebugGroup)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetBindGroup)(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetBlendConstant)(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetImmediates)(WGPURenderPassEncoder renderPassEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetIndexBuffer)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetLabel)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetPipeline)(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetScissorRect)(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetStencilReference)(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetVertexBuffer)(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetViewport)(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderWriteTimestamp)(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderAddRef)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderRelease)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPipeline
typedef WGPUBindGroupLayout (*WGPUProcRenderPipelineGetBindGroupLayout)(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineSetLabel)(WGPURenderPipeline renderPipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineAddRef)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineRelease)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ResourceTable
typedef void (*WGPUProcResourceTableDestroy)(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcResourceTableGetSize)(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcResourceTableInsertBinding)(WGPUResourceTable resourceTable, WGPUBindingResource const * resource) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcResourceTableRemoveBinding)(WGPUResourceTable resourceTable, uint32_t slot) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcResourceTableUpdate)(WGPUResourceTable resourceTable, uint32_t slot, WGPUBindingResource const * resource) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcResourceTableAddRef)(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcResourceTableRelease)(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Sampler
typedef void (*WGPUProcSamplerSetLabel)(WGPUSampler sampler, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSamplerAddRef)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSamplerRelease)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ShaderModule
typedef WGPUFuture (*WGPUProcShaderModuleGetCompilationInfo)(WGPUShaderModule shaderModule, WGPUCompilationInfoCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleSetLabel)(WGPUShaderModule shaderModule, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleAddRef)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleRelease)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SharedBufferMemory
typedef WGPUStatus (*WGPUProcSharedBufferMemoryBeginAccess)(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBuffer (*WGPUProcSharedBufferMemoryCreateBuffer)(WGPUSharedBufferMemory sharedBufferMemory, WGPU_NULLABLE WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSharedBufferMemoryEndAccess)(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSharedBufferMemoryGetProperties)(WGPUSharedBufferMemory sharedBufferMemory, WGPUSharedBufferMemoryProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcSharedBufferMemoryIsDeviceLost)(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedBufferMemorySetLabel)(WGPUSharedBufferMemory sharedBufferMemory, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedBufferMemoryAddRef)(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedBufferMemoryRelease)(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SharedBufferMemoryEndAccessState
typedef void (*WGPUProcSharedBufferMemoryEndAccessStateFreeMembers)(WGPUSharedBufferMemoryEndAccessState sharedBufferMemoryEndAccessState) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SharedFence
typedef void (*WGPUProcSharedFenceExportInfo)(WGPUSharedFence sharedFence, WGPUSharedFenceExportInfo * info) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedFenceAddRef)(WGPUSharedFence sharedFence) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedFenceRelease)(WGPUSharedFence sharedFence) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SharedTextureMemory
typedef WGPUStatus (*WGPUProcSharedTextureMemoryBeginAccess)(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTexture (*WGPUProcSharedTextureMemoryCreateTexture)(WGPUSharedTextureMemory sharedTextureMemory, WGPU_NULLABLE WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSharedTextureMemoryEndAccess)(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSharedTextureMemoryGetProperties)(WGPUSharedTextureMemory sharedTextureMemory, WGPUSharedTextureMemoryProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcSharedTextureMemoryIsDeviceLost)(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedTextureMemorySetLabel)(WGPUSharedTextureMemory sharedTextureMemory, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedTextureMemoryAddRef)(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSharedTextureMemoryRelease)(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SharedTextureMemoryEndAccessState
typedef void (*WGPUProcSharedTextureMemoryEndAccessStateFreeMembers)(WGPUSharedTextureMemoryEndAccessState sharedTextureMemoryEndAccessState) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SupportedFeatures
typedef void (*WGPUProcSupportedFeaturesFreeMembers)(WGPUSupportedFeatures supportedFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SupportedInstanceFeatures
typedef void (*WGPUProcSupportedInstanceFeaturesFreeMembers)(WGPUSupportedInstanceFeatures supportedInstanceFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SupportedWGSLLanguageFeatures
typedef void (*WGPUProcSupportedWGSLLanguageFeaturesFreeMembers)(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Surface
typedef void (*WGPUProcSurfaceConfigure)(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSurfaceGetCapabilities)(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceGetCurrentTexture)(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUStatus (*WGPUProcSurfacePresent)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceSetLabel)(WGPUSurface surface, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceUnconfigure)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceAddRef)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceRelease)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SurfaceCapabilities
typedef void (*WGPUProcSurfaceCapabilitiesFreeMembers)(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Procs of TexelBufferView
typedef void (*WGPUProcTexelBufferViewSetLabel)(WGPUTexelBufferView texelBufferView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTexelBufferViewAddRef)(WGPUTexelBufferView texelBufferView) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTexelBufferViewRelease)(WGPUTexelBufferView texelBufferView) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Texture
typedef WGPUTextureView (*WGPUProcTextureCreateErrorView)(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureView (*WGPUProcTextureCreateView)(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureDestroy)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetDepthOrArrayLayers)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureDimension (*WGPUProcTextureGetDimension)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureFormat (*WGPUProcTextureGetFormat)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetHeight)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetMipLevelCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetSampleCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureViewDimension (*WGPUProcTextureGetTextureBindingViewDimension)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureUsage (*WGPUProcTextureGetUsage)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetWidth)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTexturePin)(WGPUTexture texture, WGPUTextureUsage usage) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureSetLabel)(WGPUTexture texture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureSetOwnershipForMemoryDump)(WGPUTexture texture, uint64_t ownerGuid) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureUnpin)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureAddRef)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureRelease)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;

// Procs of TextureView
typedef void (*WGPUProcTextureViewSetLabel)(WGPUTextureView textureView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureViewAddRef)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureViewRelease)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_PROCS)

#if !defined(WGPU_SKIP_DECLARATIONS)
WGPU_EXPORT WGPUInstance wgpuCreateInstance(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuGetInstanceFeatures(WGPUSupportedInstanceFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuGetInstanceLimits(WGPUInstanceLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuHasInstanceFeature(WGPUInstanceFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUProc wgpuGetProcAddress(WGPUStringView procName) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Adapter
WGPU_EXPORT WGPUDevice wgpuAdapterCreateDevice(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterGetFeatures(WGPUAdapter adapter, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuAdapterGetFormatCapabilities(WGPUAdapter adapter, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuAdapterGetInfo(WGPUAdapter adapter, WGPUAdapterInfo * info) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUInstance wgpuAdapterGetInstance(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuAdapterGetLimits(WGPUAdapter adapter, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterAddRef(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterRelease(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;

// Methods of AdapterInfo
WGPU_EXPORT void wgpuAdapterInfoFreeMembers(WGPUAdapterInfo adapterInfo) WGPU_FUNCTION_ATTRIBUTE;

// Methods of AdapterPropertiesMemoryHeaps
WGPU_EXPORT void wgpuAdapterPropertiesMemoryHeapsFreeMembers(WGPUAdapterPropertiesMemoryHeaps adapterPropertiesMemoryHeaps) WGPU_FUNCTION_ATTRIBUTE;

// Methods of AdapterPropertiesSubgroupMatrixConfigs
WGPU_EXPORT void wgpuAdapterPropertiesSubgroupMatrixConfigsFreeMembers(WGPUAdapterPropertiesSubgroupMatrixConfigs adapterPropertiesSubgroupMatrixConfigs) WGPU_FUNCTION_ATTRIBUTE;

// Methods of BindGroup
WGPU_EXPORT void wgpuBindGroupSetLabel(WGPUBindGroup bindGroup, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupAddRef(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupRelease(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;

// Methods of BindGroupLayout
WGPU_EXPORT void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Buffer
WGPU_EXPORT WGPUTexelBufferView wgpuBufferCreateTexelView(WGPUBuffer buffer, WGPUTexelBufferViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferDestroy(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void const * wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void * wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint64_t wgpuBufferGetSize(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuBufferReadMappedRange(WGPUBuffer buffer, size_t offset, void * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferSetLabel(WGPUBuffer buffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferUnmap(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuBufferWriteMappedRange(WGPUBuffer buffer, size_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferAddRef(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferRelease(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;

// Methods of CommandBuffer
WGPU_EXPORT void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferAddRef(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;

// Methods of CommandEncoder
WGPU_EXPORT WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderInjectValidationError(WGPUCommandEncoder commandEncoder, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderSetResourceTable(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUResourceTable table) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderWriteBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderAddRef(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Methods of ComputePassEncoder
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetImmediates(WGPUComputePassEncoder computePassEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Methods of ComputePipeline
WGPU_EXPORT WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineAddRef(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;

// Methods of DawnDrmFormatCapabilities
WGPU_EXPORT void wgpuDawnDrmFormatCapabilitiesFreeMembers(WGPUDawnDrmFormatCapabilities dawnDrmFormatCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Device
WGPU_EXPORT WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPU_NULLABLE WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBuffer wgpuDeviceCreateErrorBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUExternalTexture wgpuDeviceCreateErrorExternalTexture(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateErrorShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTexture wgpuDeviceCreateErrorTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUExternalTexture wgpuDeviceCreateExternalTexture(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUResourceTable wgpuDeviceCreateResourceTable(WGPUDevice device, WGPUResourceTableDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceDestroy(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceForceLoss(WGPUDevice device, WGPUDeviceLostReason type, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUAdapter wgpuDeviceGetAdapter(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuDeviceGetAdapterInfo(WGPUDevice device, WGPUAdapterInfo * adapterInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuDeviceGetAHardwareBufferProperties(WGPUDevice device, void * handle, WGPUAHardwareBufferProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceGetFeatures(WGPUDevice device, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuDeviceGetLimits(WGPUDevice device, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDeviceGetLostFuture(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueue wgpuDeviceGetQueue(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSharedBufferMemory wgpuDeviceImportSharedBufferMemory(WGPUDevice device, WGPUSharedBufferMemoryDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSharedFence wgpuDeviceImportSharedFence(WGPUDevice device, WGPUSharedFenceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSharedTextureMemory wgpuDeviceImportSharedTextureMemory(WGPUDevice device, WGPUSharedTextureMemoryDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceInjectError(WGPUDevice device, WGPUErrorType type, WGPUStringView message) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDevicePopErrorScope(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceSetLabel(WGPUDevice device, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceSetLoggingCallback(WGPUDevice device, WGPULoggingCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceTick(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceValidateTextureDescriptor(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceAddRef(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceRelease(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;

// Methods of ExternalTexture
WGPU_EXPORT void wgpuExternalTextureDestroy(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExternalTextureExpire(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExternalTextureRefresh(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExternalTextureSetLabel(WGPUExternalTexture externalTexture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExternalTextureAddRef(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExternalTextureRelease(WGPUExternalTexture externalTexture) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Instance
WGPU_EXPORT WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceGetWGSLLanguageFeatures(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceProcessEvents(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuInstanceRequestAdapter(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo * futures, uint64_t timeoutNS) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceAddRef(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceRelease(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;

// Methods of PipelineLayout
WGPU_EXPORT void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutAddRef(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;

// Methods of QuerySet
WGPU_EXPORT void wgpuQuerySetDestroy(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetSetLabel(WGPUQuerySet querySet, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetAddRef(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetRelease(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Queue
WGPU_EXPORT void wgpuQueueCopyExternalTextureForBrowser(WGPUQueue queue, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueCopyTextureForBrowser(WGPUQueue queue, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSetLabel(WGPUQueue queue, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueWriteTexture(WGPUQueue queue, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueAddRef(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueRelease(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;

// Methods of RenderBundle
WGPU_EXPORT void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleAddRef(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleRelease(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;

// Methods of RenderBundleEncoder
WGPU_EXPORT void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetImmediates(WGPURenderBundleEncoder renderBundleEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Methods of RenderPassEncoder
WGPU_EXPORT void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPixelLocalStorageBarrier(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetImmediates(WGPURenderPassEncoder renderPassEncoder, uint32_t offset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Methods of RenderPipeline
WGPU_EXPORT WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineAddRef(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;

// Methods of ResourceTable
WGPU_EXPORT void wgpuResourceTableDestroy(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuResourceTableGetSize(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuResourceTableInsertBinding(WGPUResourceTable resourceTable, WGPUBindingResource const * resource) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuResourceTableRemoveBinding(WGPUResourceTable resourceTable, uint32_t slot) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuResourceTableUpdate(WGPUResourceTable resourceTable, uint32_t slot, WGPUBindingResource const * resource) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuResourceTableAddRef(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuResourceTableRelease(WGPUResourceTable resourceTable) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Sampler
WGPU_EXPORT void wgpuSamplerSetLabel(WGPUSampler sampler, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerAddRef(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerRelease(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;

// Methods of ShaderModule
WGPU_EXPORT WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleAddRef(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleRelease(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SharedBufferMemory
WGPU_EXPORT WGPUStatus wgpuSharedBufferMemoryBeginAccess(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBuffer wgpuSharedBufferMemoryCreateBuffer(WGPUSharedBufferMemory sharedBufferMemory, WGPU_NULLABLE WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSharedBufferMemoryEndAccess(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSharedBufferMemoryGetProperties(WGPUSharedBufferMemory sharedBufferMemory, WGPUSharedBufferMemoryProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuSharedBufferMemoryIsDeviceLost(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedBufferMemorySetLabel(WGPUSharedBufferMemory sharedBufferMemory, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedBufferMemoryAddRef(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedBufferMemoryRelease(WGPUSharedBufferMemory sharedBufferMemory) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SharedBufferMemoryEndAccessState
WGPU_EXPORT void wgpuSharedBufferMemoryEndAccessStateFreeMembers(WGPUSharedBufferMemoryEndAccessState sharedBufferMemoryEndAccessState) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SharedFence
WGPU_EXPORT void wgpuSharedFenceExportInfo(WGPUSharedFence sharedFence, WGPUSharedFenceExportInfo * info) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedFenceAddRef(WGPUSharedFence sharedFence) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedFenceRelease(WGPUSharedFence sharedFence) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SharedTextureMemory
WGPU_EXPORT WGPUStatus wgpuSharedTextureMemoryBeginAccess(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTexture wgpuSharedTextureMemoryCreateTexture(WGPUSharedTextureMemory sharedTextureMemory, WGPU_NULLABLE WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSharedTextureMemoryEndAccess(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSharedTextureMemoryGetProperties(WGPUSharedTextureMemory sharedTextureMemory, WGPUSharedTextureMemoryProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuSharedTextureMemoryIsDeviceLost(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedTextureMemorySetLabel(WGPUSharedTextureMemory sharedTextureMemory, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedTextureMemoryAddRef(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSharedTextureMemoryRelease(WGPUSharedTextureMemory sharedTextureMemory) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SharedTextureMemoryEndAccessState
WGPU_EXPORT void wgpuSharedTextureMemoryEndAccessStateFreeMembers(WGPUSharedTextureMemoryEndAccessState sharedTextureMemoryEndAccessState) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SupportedFeatures
WGPU_EXPORT void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures supportedFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SupportedInstanceFeatures
WGPU_EXPORT void wgpuSupportedInstanceFeaturesFreeMembers(WGPUSupportedInstanceFeatures supportedInstanceFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SupportedWGSLLanguageFeatures
WGPU_EXPORT void wgpuSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Surface
WGPU_EXPORT void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUStatus wgpuSurfacePresent(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceSetLabel(WGPUSurface surface, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceUnconfigure(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceAddRef(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceRelease(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;

// Methods of SurfaceCapabilities
WGPU_EXPORT void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Methods of TexelBufferView
WGPU_EXPORT void wgpuTexelBufferViewSetLabel(WGPUTexelBufferView texelBufferView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTexelBufferViewAddRef(WGPUTexelBufferView texelBufferView) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTexelBufferViewRelease(WGPUTexelBufferView texelBufferView) WGPU_FUNCTION_ATTRIBUTE;

// Methods of Texture
WGPU_EXPORT WGPUTextureView wgpuTextureCreateErrorView(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureDestroy(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetHeight(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetMipLevelCount(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetSampleCount(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureViewDimension wgpuTextureGetTextureBindingViewDimension(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureUsage wgpuTextureGetUsage(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetWidth(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTexturePin(WGPUTexture texture, WGPUTextureUsage usage) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureSetLabel(WGPUTexture texture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureSetOwnershipForMemoryDump(WGPUTexture texture, uint64_t ownerGuid) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureUnpin(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureAddRef(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureRelease(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;

// Methods of TextureView
WGPU_EXPORT void wgpuTextureViewSetLabel(WGPUTextureView textureView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewAddRef(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewRelease(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBGPU_H_

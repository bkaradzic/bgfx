/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
#define BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

#include "renderer.h"

#define USE_WEBGPU_DYNAMIC_LIB (0 \
		|| BX_PLATFORM_LINUX      \
		|| BX_PLATFORM_OSX        \
		|| BX_PLATFORM_WINDOWS    \
		)

#include "debug_renderdoc.h"
#include "shader_spirv.h"

#define _WGPU_CHECK(_call) _call; BX_ASSERT(!wgpuErrorCheck(), "" #_call " failed!")

#if BGFX_CONFIG_DEBUG
#	define WGPU_CHECK(_call) _WGPU_CHECK(_call)
#else
#	define WGPU_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

#define WGPU_SKIP_DECLARATIONS
#include <dawn/include/webgpu/webgpu.h>

#if USE_WEBGPU_DYNAMIC_LIB
#	define WGPU_IMPORT                                                              \
		/* instance */                                                              \
		WGPU_IMPORT_FUNC(false, CreateInstance);                                    \
		WGPU_IGNORE_____(false, GetInstanceFeatures);                               \
		WGPU_IGNORE_____(false, GetInstanceLimits);                                 \
		WGPU_IGNORE_____(false, HasInstanceFeature);                                \
		WGPU_IMPORT_FUNC(false, GetProcAddress);                                    \
		/* adapter */                                                               \
		WGPU_IGNORE_____(false, AdapterCreateDevice);                               \
		WGPU_IMPORT_FUNC(false, AdapterGetFeatures);                                \
		WGPU_IGNORE_____(false, AdapterGetFormatCapabilities);                      \
		WGPU_IMPORT_FUNC(false, AdapterGetInfo);                                    \
		WGPU_IGNORE_____(false, AdapterGetInstance);                                \
		WGPU_IMPORT_FUNC(false, AdapterGetLimits);                                  \
		WGPU_IMPORT_FUNC(false, AdapterHasFeature);                                 \
		WGPU_IMPORT_FUNC(false, AdapterRequestDevice);                              \
		WGPU_IGNORE_____(false, AdapterAddRef);                                     \
		WGPU_IMPORT_FUNC(false, AdapterRelease);                                    \
		WGPU_IMPORT_FUNC(false, AdapterInfoFreeMembers);                            \
		WGPU_IGNORE_____(false, AdapterPropertiesMemoryHeapsFreeMembers);           \
		WGPU_IGNORE_____(false, AdapterPropertiesSubgroupMatrixConfigsFreeMembers); \
		/* bind group */                                                            \
		WGPU_IMPORT_FUNC(false, BindGroupSetLabel);                                 \
		WGPU_IGNORE_____(false, BindGroupAddRef);                                   \
		WGPU_IMPORT_FUNC(false, BindGroupRelease);                                  \
		WGPU_IMPORT_FUNC(false, BindGroupLayoutSetLabel);                           \
		WGPU_IGNORE_____(false, BindGroupLayoutAddRef);                             \
		WGPU_IMPORT_FUNC(false, BindGroupLayoutRelease);                            \
		/* buffer */                                                                \
		WGPU_IGNORE_____(false, BufferCreateTexelView);                             \
		WGPU_IMPORT_FUNC(false, BufferDestroy);                                     \
		WGPU_IMPORT_FUNC(false, BufferGetConstMappedRange);                         \
		WGPU_IGNORE_____(false, BufferGetMappedRange);                              \
		WGPU_IGNORE_____(false, BufferGetMapState);                                 \
		WGPU_IGNORE_____(false, BufferGetSize);                                     \
		WGPU_IGNORE_____(false, BufferGetUsage);                                    \
		WGPU_IMPORT_FUNC(false, BufferMapAsync);                                    \
		WGPU_IGNORE_____(false, BufferReadMappedRange);                             \
		WGPU_IMPORT_FUNC(false, BufferSetLabel);                                    \
		WGPU_IMPORT_FUNC(false, BufferUnmap);                                       \
		WGPU_IGNORE_____(false, BufferWriteMappedRange);                            \
		WGPU_IGNORE_____(false, BufferAddRef);                                      \
		WGPU_IMPORT_FUNC(false, BufferRelease);                                     \
		WGPU_IMPORT_FUNC(false, CommandBufferSetLabel);                             \
		WGPU_IGNORE_____(false, CommandBufferAddRef);                               \
		WGPU_IMPORT_FUNC(false, CommandBufferRelease);                              \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, CommandEncoderBeginComputePass);                    \
		WGPU_IMPORT_FUNC(false, CommandEncoderBeginRenderPass);                     \
		WGPU_IMPORT_FUNC(false, CommandEncoderClearBuffer);                         \
		WGPU_IMPORT_FUNC(false, CommandEncoderCopyBufferToBuffer);                  \
		WGPU_IMPORT_FUNC(false, CommandEncoderCopyBufferToTexture);                 \
		WGPU_IMPORT_FUNC(false, CommandEncoderCopyTextureToBuffer);                 \
		WGPU_IMPORT_FUNC(false, CommandEncoderCopyTextureToTexture);                \
		WGPU_IMPORT_FUNC(false, CommandEncoderFinish);                              \
		WGPU_IGNORE_____(false, CommandEncoderInjectValidationError);               \
		WGPU_IMPORT_FUNC(false, CommandEncoderInsertDebugMarker);                   \
		WGPU_IMPORT_FUNC(false, CommandEncoderPopDebugGroup);                       \
		WGPU_IMPORT_FUNC(false, CommandEncoderPushDebugGroup);                      \
		WGPU_IMPORT_FUNC(false, CommandEncoderResolveQuerySet);                     \
		WGPU_IMPORT_FUNC(false, CommandEncoderSetLabel);                            \
		WGPU_IGNORE_____(false, CommandEncoderWriteBuffer);                         \
		WGPU_IMPORT_FUNC(false, CommandEncoderWriteTimestamp);                      \
		WGPU_IGNORE_____(false, CommandEncoderAddRef);                              \
		WGPU_IMPORT_FUNC(false, CommandEncoderRelease);                             \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderDispatchWorkgroups);              \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderDispatchWorkgroupsIndirect);      \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderEnd);                             \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderInsertDebugMarker);               \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderPopDebugGroup);                   \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderPushDebugGroup);                  \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderSetBindGroup);                    \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderSetLabel);                        \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderSetPipeline);                     \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderWriteTimestamp);                  \
		WGPU_IGNORE_____(false, ComputePassEncoderAddRef);                          \
		WGPU_IMPORT_FUNC(false, ComputePassEncoderRelease);                         \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, ComputePipelineGetBindGroupLayout);                 \
		WGPU_IMPORT_FUNC(false, ComputePipelineSetLabel);                           \
		WGPU_IGNORE_____(false, ComputePipelineAddRef);                             \
		WGPU_IMPORT_FUNC(false, ComputePipelineRelease);                            \
		/* */                                                                       \
		WGPU_IGNORE_____(false, DawnDrmFormatCapabilitiesFreeMembers);              \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, DeviceCreateBindGroup);                             \
		WGPU_IMPORT_FUNC(false, DeviceCreateBindGroupLayout);                       \
		WGPU_IMPORT_FUNC(false, DeviceCreateBuffer);                                \
		WGPU_IMPORT_FUNC(false, DeviceCreateCommandEncoder);                        \
		WGPU_IMPORT_FUNC(false, DeviceCreateComputePipeline);                       \
		WGPU_IMPORT_FUNC(false, DeviceCreateComputePipelineAsync);                  \
		WGPU_IGNORE_____(false, DeviceCreateErrorBuffer);                           \
		WGPU_IGNORE_____(false, DeviceCreateErrorExternalTexture);                  \
		WGPU_IGNORE_____(false, DeviceCreateErrorShaderModule);                     \
		WGPU_IGNORE_____(false, DeviceCreateErrorTexture);                          \
		WGPU_IGNORE_____(false, DeviceCreateExternalTexture);                       \
		WGPU_IMPORT_FUNC(false, DeviceCreatePipelineLayout);                        \
		WGPU_IMPORT_FUNC(false, DeviceCreateQuerySet);                              \
		WGPU_IMPORT_FUNC(false, DeviceCreateRenderBundleEncoder);                   \
		WGPU_IMPORT_FUNC(false, DeviceCreateRenderPipeline);                        \
		WGPU_IMPORT_FUNC(false, DeviceCreateRenderPipelineAsync);                   \
		WGPU_IMPORT_FUNC(false, DeviceCreateSampler);                               \
		WGPU_IMPORT_FUNC(false, DeviceCreateShaderModule);                          \
		WGPU_IMPORT_FUNC(false, DeviceCreateTexture);                               \
		WGPU_IMPORT_FUNC(false, DeviceDestroy);                                     \
		WGPU_IGNORE_____(false, DeviceForceLoss);                                   \
		WGPU_IGNORE_____(false, DeviceGetAdapter);                                  \
		WGPU_IMPORT_FUNC(false, DeviceGetAdapterInfo);                              \
		WGPU_IGNORE_____(false, DeviceGetAHardwareBufferProperties);                \
		WGPU_IMPORT_FUNC(false, DeviceGetFeatures);                                 \
		WGPU_IMPORT_FUNC(false, DeviceGetLimits);                                   \
		WGPU_IMPORT_FUNC(false, DeviceGetLostFuture);                               \
		WGPU_IMPORT_FUNC(false, DeviceGetQueue);                                    \
		WGPU_IMPORT_FUNC(false, DeviceHasFeature);                                  \
		WGPU_IGNORE_____(false, DeviceImportSharedBufferMemory);                    \
		WGPU_IGNORE_____(false, DeviceImportSharedFence);                           \
		WGPU_IGNORE_____(false, DeviceImportSharedTextureMemory);                   \
		WGPU_IGNORE_____(false, DeviceInjectError);                                 \
		WGPU_IMPORT_FUNC(false, DevicePopErrorScope);                               \
		WGPU_IMPORT_FUNC(false, DevicePushErrorScope);                              \
		WGPU_IMPORT_FUNC(false, DeviceSetLabel);                                    \
		WGPU_IGNORE_____(false, DeviceSetLoggingCallback);                          \
		WGPU_IGNORE_____(false, DeviceTick);                                        \
		WGPU_IGNORE_____(false, DeviceValidateTextureDescriptor);                   \
		WGPU_IGNORE_____(false, DeviceAddRef);                                      \
		WGPU_IMPORT_FUNC(false, DeviceRelease);                                     \
		/* */                                                                       \
		WGPU_IGNORE_____(false, ExternalTextureDestroy);                            \
		WGPU_IGNORE_____(false, ExternalTextureExpire);                             \
		WGPU_IGNORE_____(false, ExternalTextureRefresh);                            \
		WGPU_IGNORE_____(false, ExternalTextureSetLabel);                           \
		WGPU_IGNORE_____(false, ExternalTextureAddRef);                             \
		WGPU_IGNORE_____(false, ExternalTextureRelease);                            \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, InstanceCreateSurface);                             \
		WGPU_IMPORT_FUNC(false, InstanceGetWGSLLanguageFeatures);                   \
		WGPU_IMPORT_FUNC(false, InstanceHasWGSLLanguageFeature);                    \
		WGPU_IMPORT_FUNC(false, InstanceProcessEvents);                             \
		WGPU_IMPORT_FUNC(false, InstanceRequestAdapter);                            \
		WGPU_IMPORT_FUNC(false, InstanceWaitAny);                                   \
		WGPU_IGNORE_____(false, InstanceAddRef);                                    \
		WGPU_IMPORT_FUNC(false, InstanceRelease);                                   \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, PipelineLayoutSetLabel);                            \
		WGPU_IGNORE_____(false, PipelineLayoutAddRef);                              \
		WGPU_IMPORT_FUNC(false, PipelineLayoutRelease);                             \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, QuerySetDestroy);                                   \
		WGPU_IMPORT_FUNC(false, QuerySetGetCount);                                  \
		WGPU_IMPORT_FUNC(false, QuerySetGetType);                                   \
		WGPU_IMPORT_FUNC(false, QuerySetSetLabel);                                  \
		WGPU_IGNORE_____(false, QuerySetAddRef);                                    \
		WGPU_IMPORT_FUNC(false, QuerySetRelease);                                   \
		/* */                                                                       \
		WGPU_IGNORE_____(false, QueueCopyExternalTextureForBrowser);                \
		WGPU_IGNORE_____(false, QueueCopyTextureForBrowser);                        \
		WGPU_IMPORT_FUNC(false, QueueOnSubmittedWorkDone);                          \
		WGPU_IMPORT_FUNC(false, QueueSetLabel);                                     \
		WGPU_IMPORT_FUNC(false, QueueSubmit);                                       \
		WGPU_IMPORT_FUNC(false, QueueWriteBuffer);                                  \
		WGPU_IMPORT_FUNC(false, QueueWriteTexture);                                 \
		WGPU_IGNORE_____(false, QueueAddRef);                                       \
		WGPU_IMPORT_FUNC(false, QueueRelease);                                      \
		/* */                                                                       \
		WGPU_IGNORE_____(false, RenderBundleSetLabel);                              \
		WGPU_IGNORE_____(false, RenderBundleAddRef);                                \
		WGPU_IGNORE_____(false, RenderBundleRelease);                               \
		/* */                                                                       \
		WGPU_IGNORE_____(false, RenderBundleEncoderDraw);                           \
		WGPU_IGNORE_____(false, RenderBundleEncoderDrawIndexed);                    \
		WGPU_IGNORE_____(false, RenderBundleEncoderDrawIndexedIndirect);            \
		WGPU_IGNORE_____(false, RenderBundleEncoderDrawIndirect);                   \
		WGPU_IGNORE_____(false, RenderBundleEncoderFinish);                         \
		WGPU_IGNORE_____(false, RenderBundleEncoderInsertDebugMarker);              \
		WGPU_IGNORE_____(false, RenderBundleEncoderPopDebugGroup);                  \
		WGPU_IGNORE_____(false, RenderBundleEncoderPushDebugGroup);                 \
		WGPU_IGNORE_____(false, RenderBundleEncoderSetBindGroup);                   \
		WGPU_IGNORE_____(false, RenderBundleEncoderSetIndexBuffer);                 \
		WGPU_IGNORE_____(false, RenderBundleEncoderSetLabel);                       \
		WGPU_IGNORE_____(false, RenderBundleEncoderSetPipeline);                    \
		WGPU_IGNORE_____(false, RenderBundleEncoderSetVertexBuffer);                \
		WGPU_IGNORE_____(false, RenderBundleEncoderAddRef);                         \
		WGPU_IGNORE_____(false, RenderBundleEncoderRelease);                        \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderBeginOcclusionQuery);              \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderDraw);                             \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderDrawIndexed);                      \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderDrawIndexedIndirect);              \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderDrawIndirect);                     \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderEnd);                              \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderEndOcclusionQuery);                \
		WGPU_IGNORE_____(false, RenderPassEncoderExecuteBundles);                   \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderInsertDebugMarker);                \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderMultiDrawIndexedIndirect);         \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderMultiDrawIndirect);                \
		WGPU_IGNORE_____(false, RenderPassEncoderPixelLocalStorageBarrier);         \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderPopDebugGroup);                    \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderPushDebugGroup);                   \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetBindGroup);                     \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetBlendConstant);                 \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetIndexBuffer);                   \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetLabel);                         \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetPipeline);                      \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetScissorRect);                   \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetStencilReference);              \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetVertexBuffer);                  \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderSetViewport);                      \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderWriteTimestamp);                   \
		WGPU_IGNORE_____(false, RenderPassEncoderAddRef);                           \
		WGPU_IMPORT_FUNC(false, RenderPassEncoderRelease);                          \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, RenderPipelineGetBindGroupLayout);                  \
		WGPU_IMPORT_FUNC(false, RenderPipelineSetLabel);                            \
		WGPU_IMPORT_FUNC(false, RenderPipelineAddRef);                              \
		WGPU_IMPORT_FUNC(false, RenderPipelineRelease);                             \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, SamplerSetLabel);                                   \
		WGPU_IGNORE_____(false, SamplerAddRef);                                     \
		WGPU_IMPORT_FUNC(false, SamplerRelease);                                    \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, ShaderModuleGetCompilationInfo);                    \
		WGPU_IMPORT_FUNC(false, ShaderModuleSetLabel);                              \
		WGPU_IGNORE_____(false, ShaderModuleAddRef);                                \
		WGPU_IMPORT_FUNC(false, ShaderModuleRelease);                               \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SharedBufferMemoryBeginAccess);                     \
		WGPU_IGNORE_____(false, SharedBufferMemoryCreateBuffer);                    \
		WGPU_IGNORE_____(false, SharedBufferMemoryEndAccess);                       \
		WGPU_IGNORE_____(false, SharedBufferMemoryGetProperties);                   \
		WGPU_IGNORE_____(false, SharedBufferMemoryIsDeviceLost);                    \
		WGPU_IGNORE_____(false, SharedBufferMemorySetLabel);                        \
		WGPU_IGNORE_____(false, SharedBufferMemoryAddRef);                          \
		WGPU_IGNORE_____(false, SharedBufferMemoryRelease);                         \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SharedBufferMemoryEndAccessStateFreeMembers);       \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SharedFenceExportInfo);                             \
		WGPU_IGNORE_____(false, SharedFenceAddRef);                                 \
		WGPU_IGNORE_____(false, SharedFenceRelease);                                \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SharedTextureMemoryBeginAccess);                    \
		WGPU_IGNORE_____(false, SharedTextureMemoryCreateTexture);                  \
		WGPU_IGNORE_____(false, SharedTextureMemoryEndAccess);                      \
		WGPU_IGNORE_____(false, SharedTextureMemoryGetProperties);                  \
		WGPU_IGNORE_____(false, SharedTextureMemoryIsDeviceLost);                   \
		WGPU_IGNORE_____(false, SharedTextureMemorySetLabel);                       \
		WGPU_IGNORE_____(false, SharedTextureMemoryAddRef);                         \
		WGPU_IGNORE_____(false, SharedTextureMemoryRelease);                        \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SharedTextureMemoryEndAccessStateFreeMembers);      \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, SupportedFeaturesFreeMembers);                      \
		/* */                                                                       \
		WGPU_IGNORE_____(false, SupportedInstanceFeaturesFreeMembers);              \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, SupportedWGSLLanguageFeaturesFreeMembers);          \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, SurfaceConfigure);                                  \
		WGPU_IMPORT_FUNC(false, SurfaceGetCapabilities);                            \
		WGPU_IMPORT_FUNC(false, SurfaceGetCurrentTexture);                          \
		WGPU_IMPORT_FUNC(false, SurfacePresent);                                    \
		WGPU_IMPORT_FUNC(false, SurfaceSetLabel);                                   \
		WGPU_IMPORT_FUNC(false, SurfaceUnconfigure);                                \
		WGPU_IGNORE_____(false, SurfaceAddRef);                                     \
		WGPU_IMPORT_FUNC(false, SurfaceRelease);                                    \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, SurfaceCapabilitiesFreeMembers);                    \
		/* */                                                                       \
		WGPU_IGNORE_____(false, TexelBufferViewSetLabel);                           \
		WGPU_IGNORE_____(false, TexelBufferViewAddRef);                             \
		WGPU_IGNORE_____(false, TexelBufferViewRelease);                            \
		/* */                                                                       \
		WGPU_IGNORE_____(false, TextureCreateErrorView);                            \
		WGPU_IMPORT_FUNC(false, TextureCreateView);                                 \
		WGPU_IMPORT_FUNC(false, TextureDestroy);                                    \
		WGPU_IGNORE_____(false, TextureGetDepthOrArrayLayers);                      \
		WGPU_IGNORE_____(false, TextureGetDimension);                               \
		WGPU_IGNORE_____(false, TextureGetFormat);                                  \
		WGPU_IGNORE_____(false, TextureGetHeight);                                  \
		WGPU_IGNORE_____(false, TextureGetMipLevelCount);                           \
		WGPU_IGNORE_____(false, TextureGetSampleCount);                             \
		WGPU_IGNORE_____(false, TextureGetUsage);                                   \
		WGPU_IGNORE_____(false, TextureGetWidth);                                   \
		WGPU_IGNORE_____(false, TexturePin);                                        \
		WGPU_IMPORT_FUNC(false, TextureSetLabel);                                   \
		WGPU_IGNORE_____(false, TextureUnpin);                                      \
		WGPU_IGNORE_____(false, TextureAddRef);                                     \
		WGPU_IMPORT_FUNC(false, TextureRelease);                                    \
		/* */                                                                       \
		WGPU_IMPORT_FUNC(false, TextureViewSetLabel);                               \
		WGPU_IGNORE_____(false, TextureViewAddRef);                                 \
		WGPU_IMPORT_FUNC(false, TextureViewRelease);                                \
		/* end */

#endif // USE_WEBGPU_DYNAMIC_LIB

#define WGPU_RELEASE                            \
	WGPU_RELEASE_FUNC(Adapter);                 \
	WGPU_RELEASE_FUNC(Device);                  \
	WGPU_RELEASE_FUNC(Instance);                \
	WGPU_RELEASE_FUNC(Surface);                 \
	WGPU_RELEASE_FUNC(Queue);                   \
	WGPU_RELEASE_FUNC(Texture);                 \
	WGPU_RELEASE_FUNC(TextureView);             \
	WGPU_RELEASE_FUNC(CommandEncoder);          \
	WGPU_RELEASE_FUNC(ComputePassEncoder);      \
	WGPU_RELEASE_FUNC(RenderPassEncoder);       \
	WGPU_RELEASE_FUNC(CommandBuffer);           \
	WGPU_RELEASE_FUNC(BindGroup);               \
	WGPU_RELEASE_FUNC(BindGroupLayout);         \
	WGPU_RELEASE_FUNC(Buffer);                  \
	WGPU_RELEASE_FUNC(ComputePipeline);         \
	/*WGPU_RELEASE_FUNC(ExternalTexture);*/     \
	WGPU_RELEASE_FUNC(PipelineLayout);          \
	WGPU_RELEASE_FUNC(QuerySet);                \
	/*WGPU_RELEASE_FUNC(RenderBundle);*/        \
	/*WGPU_RELEASE_FUNC(RenderBundleEncoder);*/ \
	WGPU_RELEASE_FUNC(RenderPipeline);          \
	/*WGPU_RELEASE_FUNC(ResourceTable);*/       \
	WGPU_RELEASE_FUNC(Sampler);                 \
	WGPU_RELEASE_FUNC(ShaderModule);            \
	/*WGPU_RELEASE_FUNC(SharedBufferMemory);*/  \
	/*WGPU_RELEASE_FUNC(SharedFence);*/         \
	/*WGPU_RELEASE_FUNC(SharedTextureMemory);*/ \
	/*WGPU_RELEASE_FUNC(TexelBufferView);*/     \
	/* end */

#define WGPU_DESTROY                      \
	WGPU_DESTROY_FUNC(Buffer)             \
	WGPU_DESTROY_FUNC(Device)             \
	WGPU_DESTROY_FUNC(Texture)            \
	WGPU_DESTROY_FUNC(QuerySet)           \
	/*WGPU_DESTROY_FUNC(ResourceTable);*/ \
	/* end */

#define BGFX_WGPU_PROFILER_BEGIN(_view, _abgr)        \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_WGPU_PROFILER_BEGIN_LITERAL(_name, _abgr) \
	BX_MACRO_BLOCK_BEGIN                               \
		BGFX_PROFILER_BEGIN_LITERAL("" _name, _abgr);  \
	BX_MACRO_BLOCK_END

#define BGFX_WGPU_PROFILER_END() \
	BX_MACRO_BLOCK_BEGIN         \
		BGFX_PROFILER_END();     \
	BX_MACRO_BLOCK_END

namespace bgfx { namespace wgpu
{
#define WGPU_RELEASE_FUNC(_name) void wgpuRelease(WGPU##_name& _obj)

	WGPU_RELEASE

#undef WGPU_RELEASE_FUNC

	template<typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _key, Ty _value)
		{
			invalidate(_key);
			m_hashMap.insert(stl::make_pair(_key, _value) );
		}

		Ty find(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return 0;
		}

		void invalidate(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				wgpuRelease(it->second);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				wgpuRelease(it->second);
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty> HashMap;
		HashMap m_hashMap;
	};

	inline constexpr WGPUStringView toWGPUStringView(const bx::StringView& _str)
	{
		return { .data = _str.getPtr(), .length = size_t(_str.getLength() ) };
	}

	struct ChunkedScratchBufferOffset
	{
		WGPUBuffer buffer;
		uint32_t offsets[2];
	};

	struct ChunkedScratchBufferAlloc
	{
		uint32_t offset;
		uint32_t chunkIdx;
	};

	struct ChunkedScratchBufferWGPU
	{
		ChunkedScratchBufferWGPU()
			: m_chunkControl(0)
		{
		}

		void create(uint32_t _chunkSize, uint32_t _numChunks, WGPUBufferUsage _usage, uint32_t _align);
		void createUniform(uint32_t _chunkSize, uint32_t _numChunks);
		void destroy();

		void addChunk(uint32_t _at = UINT32_MAX);
		ChunkedScratchBufferAlloc alloc(uint32_t _size);

		void write(ChunkedScratchBufferOffset& _outSbo, const void* _vsData, uint32_t _vsSize, const void* _fsData = NULL, uint32_t _fsSize = 0);

		void begin();
		void end();
		void flush();

		struct Chunk
		{
			WGPUBuffer buffer;
			uint8_t* data;
		};

		using ScratchBufferChunksArray = stl::vector<Chunk>;

		ScratchBufferChunksArray m_chunks;
		bx::RingBufferControl m_chunkControl;

		uint32_t m_chunkPos;
		uint32_t m_chunkSize;
		uint32_t m_align;
		WGPUBufferUsage m_usage;

		uint32_t m_consume[BGFX_CONFIG_MAX_FRAME_LATENCY];
		uint32_t m_totalUsed;
	};

	struct BufferWGPU
	{
		BufferWGPU()
			: m_buffer(NULL)
			, m_size(0)
			, m_flags(BGFX_BUFFER_NONE)
		{
		}

		void create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride = 0);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false) const;
		void destroy();

		WGPUBuffer m_buffer;
		uint32_t m_size;
		uint16_t m_flags;
	};

	using IndexBufferWGPU = BufferWGPU;

	struct VertexBufferWGPU : public BufferWGPU
	{
		void create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags);

		VertexLayoutHandle m_layoutHandle;
	};

	struct ShaderBinding
	{
		struct Type
		{
			enum Enum
			{
				Buffer,
				Image,
				Sampler,

				Count
			};
		};

		UniformHandle uniformHandle = BGFX_INVALID_HANDLE;
		Type::Enum type;
		uint32_t binding;
		uint32_t samplerBinding;
		uint32_t index;
		WGPUBufferBindingType bufferBindingType;
		WGPUTextureSampleType sampleType;
		WGPUTextureViewDimension viewDimension;
		WGPUShaderStage shaderStage;

		void clear()
		{
			uniformHandle     = BGFX_INVALID_HANDLE;
			type              = ShaderBinding::Type::Count;
			binding           = 0;
			samplerBinding    = 0;
			index             = UINT32_MAX;
			bufferBindingType = WGPUBufferBindingType_Undefined;
			sampleType        = WGPUTextureSampleType_Undefined;
			viewDimension     = WGPUTextureViewDimension_Undefined;
		}
	};

	struct ShaderWGPU
	{
		ShaderWGPU()
			: m_code(NULL)
			, m_module(NULL)
			, m_constantBuffer(NULL)
			, m_hash(0)
			, m_numUniforms(0)
			, m_numPredefined(0)
		{
		}

		void create(const Memory* _mem);
		void destroy();

		const Memory* m_code;
		WGPUShaderModule m_module;
		UniformBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];
		uint8_t m_attrRemap[Attrib::Count];

		uint32_t m_hash;
		uint16_t m_numUniforms;
		uint16_t m_size;
		uint16_t m_blockSize;
		uint8_t  m_numPredefined;
		uint8_t  m_numAttrs;

		ShaderBinding m_shaderBinding[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		uint8_t m_numTextures;
	};

	struct BindGroup
	{
		void invalidate()
		{
			wgpuRelease(bindGroup);
		}

		WGPUBindGroup bindGroup;
		uint32_t      numOffsets;
	};

	inline void release(BindGroup& _bindGroup)
	{
		_bindGroup.invalidate();
	}

	struct ComputePipeline
	{
		void invalidate()
		{
			wgpuRelease(bindGroupLayout);
			wgpuRelease(pipeline);
		}

		WGPUBindGroupLayout bindGroupLayout;
		WGPUComputePipeline pipeline;
	};

	inline void release(ComputePipeline& _computePipeline)
	{
		_computePipeline.invalidate();
	}

	struct RenderPipeline
	{
		void invalidate()
		{
			wgpuRelease(bindGroupLayout);
			wgpuRelease(pipeline);
		}

		WGPUBindGroupLayout bindGroupLayout;
		WGPURenderPipeline  pipeline;
	};

	inline void release(RenderPipeline& _renderPipeline)
	{
		_renderPipeline.invalidate();
	}

	struct ProgramWGPU
	{
		ProgramWGPU()
			: m_vsh(NULL)
			, m_fsh(NULL)
		{
		}

		void create(const ShaderWGPU* _vsh, const ShaderWGPU* _fsh);
		void destroy();

		const ShaderWGPU* m_vsh;
		const ShaderWGPU* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;

		ShaderBinding m_shaderBinding[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		uint32_t m_numBindings;
	};

	struct TextureWGPU
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureWGPU()
			: m_texture(NULL)
			, m_textureResolve(NULL)
			, m_type(Texture2D)
		{
		}

		void create(const Memory* _mem, uint64_t _flags, uint8_t _skip);
		void destroy();
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);

		WGPUSampler getSamplerState(uint32_t _samplerFlags) const;
		WGPUTextureView getTextureView(uint8_t _baseMipLevel, uint8_t _mipLevelCount, bool _storage) const;

		WGPUTexture m_texture;
		WGPUTexture m_textureResolve;
		WGPUTextureViewDimension m_viewDimension;

		uint64_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint32_t m_numLayers;
		uint32_t m_numSides;
		uint8_t  m_type;
		uint8_t  m_requestedFormat;
		uint8_t  m_textureFormat;
		uint8_t  m_numMips;
	};

	struct SwapChainWGPU
	{
		SwapChainWGPU()
			: m_nwh(NULL)
			, m_surface(NULL)
			, m_textureView(NULL)
			, m_msaaTextureView(NULL)
			, m_depthStencilView(NULL)
		{
		}

		bool create(void* _nwh, const Resolution& _resolution);
		void destroy();
		void update(void* _nwh, const Resolution& _resolution);

		bool createSurface(void* _nwh);

		bool configure(const Resolution& _resolution);
		void present();

		void* m_nwh;
		Resolution m_resolution;
		WGPUSurfaceConfiguration m_surfaceConfig;

		WGPUSurface m_surface;
		WGPUTextureView m_textureView;
		WGPUTextureView m_msaaTextureView;
		WGPUTextureView m_depthStencilView;

		uint8_t m_formatDepthStencil;
	};

	struct FrameBufferWGPU
	{
		FrameBufferWGPU()
			: m_depth({ kInvalidHandle })
			, m_depthStencilView(NULL)
			, m_denseIdx(kInvalidHandle)
			, m_numColorAttachments(0)
			, m_numAttachments(0)
			, m_needPresent(false)
		{
		}

		void create(uint8_t _num, const Attachment* _attachment);
		bool create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _colorFormat, TextureFormat::Enum _depthFormat = TextureFormat::Count);
		uint16_t destroy();

		void preReset();
		void postReset();

		void update(const Resolution& _resolution);

		void present();

		bool isSwapChain() const
		{
			return m_swapChain.m_nwh;
		}

		TextureHandle m_texture[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		TextureHandle m_depth;

		Attachment      m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		WGPUTextureView m_textureView[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		WGPUTextureView m_depthStencilView;
		uint8_t m_formatDepthStencil;

		uint16_t m_denseIdx;
		uint8_t m_numColorAttachments;
		uint8_t m_numAttachments;

		uint32_t m_width;
		uint32_t m_height;

		SwapChainWGPU m_swapChain;
		bool m_needPresent;
		bool m_needResolve;
	};

	struct CommandQueueWGPU
	{
		CommandQueueWGPU()
			: m_queue(NULL)
			, m_commandEncoder(NULL)
			, m_counter(0)
		{
		}

		void init(WGPUDevice _device);
		void shutdown();

		WGPUCommandEncoder alloc();
		void kick();
		void wait();
		void frame();

		void writeBuffer(WGPUBuffer _buffer, uint64_t _bufferOffset, const void* _data, size_t _size) const;
		void writeTexture(const WGPUTexelCopyTextureInfo& _destination, const void* _data, size_t _size, const WGPUTexelCopyBufferLayout& _source, const WGPUExtent3D& _writeSize) const;

		void copyBufferToBuffer(WGPUBuffer _source, uint64_t _sourceOffset, WGPUBuffer _destination, uint64_t _destinationOffset, uint64_t _size);
		void copyBufferToTexture(const WGPUTexelCopyBufferInfo& _source, const WGPUTexelCopyTextureInfo& _destination, const WGPUExtent3D& _copySize);
		void copyTextureToBuffer(const WGPUTexelCopyTextureInfo& source, const WGPUTexelCopyBufferInfo& destination, const WGPUExtent3D& copySize);
		void copyTextureToTexture(const WGPUTexelCopyTextureInfo& _source, const WGPUTexelCopyTextureInfo& _destination, const WGPUExtent3D& _copySize);

		WGPUQueue m_queue;
		WGPUCommandEncoder m_commandEncoder;
		uint32_t m_currentFrameInFlight;
		uint32_t m_counter;
	};

	struct TimerQueryWGPU
	{
		TimerQueryWGPU()
			: m_control(BX_COUNTOF(m_result) )
		{
		}

		void init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx, uint32_t _frameNum);
		void end(uint32_t _idx);

		struct Query
		{
			uint32_t m_resultIdx;
			uint32_t m_frameNum;
			uint64_t m_fence;
			bool     m_ready;
		};

		struct Result
		{
			void reset()
			{
				m_begin    = 0;
				m_end      = 0;
				m_pending  = 0;
				m_frameNum = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
			uint32_t m_frameNum;
		};

		uint64_t m_frequency;

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];
		Query m_query[BGFX_CONFIG_MAX_VIEWS*4];

		WGPUQuerySet m_querySet;
		WGPUBuffer m_resolve;
		WGPUBuffer m_readback;

		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryWGPU
	{
		OcclusionQueryWGPU()
			: m_querySet(NULL)
			, m_resolve(NULL)
			, m_readback(NULL)
			, m_control(BX_COUNTOF(m_handle) )
		{
		}

		void init();
		void shutdown();
		void begin(WGPURenderPassEncoder _renderPassEncoder, OcclusionQueryHandle _handle);
		void end(WGPURenderPassEncoder _renderPassEncoder);
		void resolve();
		void readResultsAsync(Frame* _frame);
		void consumeResults(Frame* _frame);
		void invalidate(OcclusionQueryHandle _handle);

		WGPUQuerySet m_querySet;
		WGPUBuffer m_resolve;
		WGPUBuffer m_readback;

		OcclusionQueryHandle m_handle[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /* namespace bgfx */ } // namespace wgpu

#endif // BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_CONFIG_H_HEADER_GUARD
#define BGFX_CONFIG_H_HEADER_GUARD

#include <bx/bx.h> // bx::isPowerOf2

// # Configuration options for bgfx.
//
// Any of `BGFX_CONFIG_*` options that's inside `#ifndef` block can be configured externally
// via compiler options.
//
// When selecting rendering backends select all backends you want to include in the build.

#ifndef BX_CONFIG_DEBUG
#	error "BX_CONFIG_DEBUG must be defined in build script!"
#endif // BX_CONFIG_DEBUG

#if !defined(BGFX_CONFIG_RENDERER_AGC)        \
 && !defined(BGFX_CONFIG_RENDERER_DIRECT3D11) \
 && !defined(BGFX_CONFIG_RENDERER_DIRECT3D12) \
 && !defined(BGFX_CONFIG_RENDERER_GNM)        \
 && !defined(BGFX_CONFIG_RENDERER_METAL)      \
 && !defined(BGFX_CONFIG_RENDERER_NVN)        \
 && !defined(BGFX_CONFIG_RENDERER_OPENGL)     \
 && !defined(BGFX_CONFIG_RENDERER_OPENGLES)   \
 && !defined(BGFX_CONFIG_RENDERER_VULKAN)     \
 && !defined(BGFX_CONFIG_RENDERER_WEBGPU)

#	ifndef BGFX_CONFIG_RENDERER_AGC
#		define BGFX_CONFIG_RENDERER_AGC (0 \
					|| BX_PLATFORM_PS5     \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_AGC

#	ifndef BGFX_CONFIG_RENDERER_DIRECT3D11
#		define BGFX_CONFIG_RENDERER_DIRECT3D11 (0 \
					|| BX_PLATFORM_LINUX          \
					|| BX_PLATFORM_WINDOWS        \
					|| BX_PLATFORM_WINRT          \
					|| BX_PLATFORM_XBOXONE        \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#	ifndef BGFX_CONFIG_RENDERER_DIRECT3D12
#		define BGFX_CONFIG_RENDERER_DIRECT3D12 (0 \
					|| BX_PLATFORM_LINUX          \
					|| BX_PLATFORM_WINDOWS        \
					|| BX_PLATFORM_WINRT          \
					|| BX_PLATFORM_XBOXONE        \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D12

#	ifndef BGFX_CONFIG_RENDERER_GNM
#		define BGFX_CONFIG_RENDERER_GNM (0 \
					|| BX_PLATFORM_PS4     \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_GNM

#	ifndef BGFX_CONFIG_RENDERER_METAL
#		define BGFX_CONFIG_RENDERER_METAL (0 \
					|| BX_PLATFORM_IOS       \
					|| BX_PLATFORM_OSX       \
					|| BX_PLATFORM_VISIONOS \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_METAL

#	ifndef BGFX_CONFIG_RENDERER_NVN
#		define BGFX_CONFIG_RENDERER_NVN (0 \
					|| BX_PLATFORM_NX      \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_NVN

#	ifndef BGFX_CONFIG_RENDERER_OPENGL_MIN_VERSION
#		define BGFX_CONFIG_RENDERER_OPENGL_MIN_VERSION 1
#	endif // BGFX_CONFIG_RENDERER_OPENGL_MIN_VERSION

#	ifndef BGFX_CONFIG_RENDERER_OPENGL
#		define BGFX_CONFIG_RENDERER_OPENGL (0 \
					|| BX_PLATFORM_LINUX      \
					|| BX_PLATFORM_WINDOWS    \
					? BGFX_CONFIG_RENDERER_OPENGL_MIN_VERSION : 0)
#	endif // BGFX_CONFIG_RENDERER_OPENGL

#	ifndef BGFX_CONFIG_RENDERER_OPENGLES_MIN_VERSION
#		define BGFX_CONFIG_RENDERER_OPENGLES_MIN_VERSION (0 \
					|| BX_PLATFORM_ANDROID                  \
					? 30 : 1)
#	endif // BGFX_CONFIG_RENDERER_OPENGLES_MIN_VERSION

#	ifndef BGFX_CONFIG_RENDERER_OPENGLES
#		define BGFX_CONFIG_RENDERER_OPENGLES (0 \
					|| BX_PLATFORM_ANDROID      \
					|| BX_PLATFORM_EMSCRIPTEN   \
					|| BX_PLATFORM_NX           \
					|| BX_PLATFORM_RPI          \
					? BGFX_CONFIG_RENDERER_OPENGLES_MIN_VERSION : 0)
#	endif // BGFX_CONFIG_RENDERER_OPENGLES

#	ifndef BGFX_CONFIG_RENDERER_VULKAN
#		define BGFX_CONFIG_RENDERER_VULKAN (0 \
					|| BX_PLATFORM_ANDROID    \
					|| BX_PLATFORM_LINUX      \
					|| BX_PLATFORM_NX         \
					|| BX_PLATFORM_OSX        \
					|| BX_PLATFORM_WINDOWS    \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_VULKAN

#	ifndef BGFX_CONFIG_RENDERER_WEBGPU
#		define BGFX_CONFIG_RENDERER_WEBGPU (0     \
					/*|| BX_PLATFORM_EMSCRIPTEN*/ \
					|| BX_PLATFORM_LINUX          \
					|| BX_PLATFORM_OSX            \
					|| BX_PLATFORM_WINDOWS        \
					? 1 : 0)
#	endif // BGFX_CONFIG_RENDERER_WEBGPU

#else
#	ifndef BGFX_CONFIG_RENDERER_AGC
#		define BGFX_CONFIG_RENDERER_AGC 0
#	endif // BGFX_CONFIG_RENDERER_AGC

#	ifndef BGFX_CONFIG_RENDERER_DIRECT3D11
#		define BGFX_CONFIG_RENDERER_DIRECT3D11 0
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#	ifndef BGFX_CONFIG_RENDERER_DIRECT3D12
#		define BGFX_CONFIG_RENDERER_DIRECT3D12 0
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D12

#	ifndef BGFX_CONFIG_RENDERER_GNM
#		define BGFX_CONFIG_RENDERER_GNM 0
#	endif // BGFX_CONFIG_RENDERER_GNM

#	ifndef BGFX_CONFIG_RENDERER_METAL
#		define BGFX_CONFIG_RENDERER_METAL 0
#	endif // BGFX_CONFIG_RENDERER_METAL

#	ifndef BGFX_CONFIG_RENDERER_NVN
#		define BGFX_CONFIG_RENDERER_NVN 0
#	endif // BGFX_CONFIG_RENDERER_NVN

#	ifndef BGFX_CONFIG_RENDERER_OPENGL
#		define BGFX_CONFIG_RENDERER_OPENGL 0
#	endif // BGFX_CONFIG_RENDERER_OPENGL

#	ifndef BGFX_CONFIG_RENDERER_OPENGLES
#		define BGFX_CONFIG_RENDERER_OPENGLES 0
#	endif // BGFX_CONFIG_RENDERER_OPENGLES

#	ifndef BGFX_CONFIG_RENDERER_VULKAN
#		define BGFX_CONFIG_RENDERER_VULKAN 0
#	endif // BGFX_CONFIG_RENDERER_VULKAN

#	ifndef BGFX_CONFIG_RENDERER_WEBGPU
#		define BGFX_CONFIG_RENDERER_WEBGPU 0
#	endif // BGFX_CONFIG_RENDERER_WEBGPU
#endif // !defined...

#if BGFX_CONFIG_RENDERER_OPENGL && BGFX_CONFIG_RENDERER_OPENGL < 21
#	undef BGFX_CONFIG_RENDERER_OPENGL
#	define BGFX_CONFIG_RENDERER_OPENGL 21
#endif // BGFX_CONFIG_RENDERER_OPENGL && BGFX_CONFIG_RENDERER_OPENGL < 21

#if BGFX_CONFIG_RENDERER_OPENGLES && BGFX_CONFIG_RENDERER_OPENGLES < 20
#	undef BGFX_CONFIG_RENDERER_OPENGLES
#	define BGFX_CONFIG_RENDERER_OPENGLES 20
#endif // BGFX_CONFIG_RENDERER_OPENGLES && BGFX_CONFIG_RENDERER_OPENGLES < 20

#if BGFX_CONFIG_RENDERER_OPENGL && BGFX_CONFIG_RENDERER_OPENGLES
#	error "Can't define both BGFX_CONFIG_RENDERER_OPENGL and BGFX_CONFIG_RENDERER_OPENGLES"
#endif // BGFX_CONFIG_RENDERER_OPENGL && BGFX_CONFIG_RENDERER_OPENGLES

/// Enable use of renderer-specific API extensions (e.g. OpenGL extensions,
/// Vulkan extensions). Default is 1 (enabled).
#ifndef BGFX_CONFIG_RENDERER_USE_EXTENSIONS
#	define BGFX_CONFIG_RENDERER_USE_EXTENSIONS 1
#endif // BGFX_CONFIG_RENDERER_USE_EXTENSIONS

/// Enable use of staging buffers in the Direct3D 11 renderer for texture and
/// buffer updates. Default is 0 (disabled). When enabled, updates go through
/// a staging buffer instead of using Map/Unmap directly.
#ifndef BGFX_CONFIG_RENDERER_DIRECT3D11_USE_STAGING_BUFFER
#	define BGFX_CONFIG_RENDERER_DIRECT3D11_USE_STAGING_BUFFER 0
#endif // BGFX_CONFIG_RENDERER_DIRECT3D11_USE_STAGING_BUFFER

/// Maximum number of Vulkan descriptor sets allocated per frame. Default is
/// 1024. Each draw/compute call may consume one descriptor set.
#ifndef BGFX_CONFIG_RENDERER_VULKAN_MAX_DESCRIPTOR_SETS_PER_FRAME
#	define BGFX_CONFIG_RENDERER_VULKAN_MAX_DESCRIPTOR_SETS_PER_FRAME 1024
#endif // BGFX_CONFIG_RENDERER_VULKAN_MAX_DESCRIPTOR_SETS_PER_FRAME

/// Enable use of tinystl instead of std containers for internal data
/// structures. Default is 1 (enabled). Reduces binary size and avoids
/// std library dependency.
#ifndef BGFX_CONFIG_USE_TINYSTL
#	define BGFX_CONFIG_USE_TINYSTL 1
#endif // BGFX_CONFIG_USE_TINYSTL

/// Debug text maximum scale factor.
#ifndef BGFX_CONFIG_DEBUG_TEXT_MAX_SCALE
#	define BGFX_CONFIG_DEBUG_TEXT_MAX_SCALE 4
#endif // BGFX_CONFIG_DEBUG_TEXT_MAX_SCALE

/// Enable nVidia PerfHUD integration.
#ifndef BGFX_CONFIG_DEBUG_PERFHUD
#	define BGFX_CONFIG_DEBUG_PERFHUD 0
#endif // BGFX_CONFIG_DEBUG_NVPERFHUD

/// Enable annotation for graphics debuggers.
#ifndef BGFX_CONFIG_DEBUG_ANNOTATION
#	define BGFX_CONFIG_DEBUG_ANNOTATION BGFX_CONFIG_DEBUG
#endif // BGFX_CONFIG_DEBUG_ANNOTATION

/// Enable DX11 object names.
#ifndef BGFX_CONFIG_DEBUG_OBJECT_NAME
#	define BGFX_CONFIG_DEBUG_OBJECT_NAME BGFX_CONFIG_DEBUG_ANNOTATION
#endif // BGFX_CONFIG_DEBUG_OBJECT_NAME

/// Enable uniform debug checks.
#ifndef BGFX_CONFIG_DEBUG_UNIFORM
#	define BGFX_CONFIG_DEBUG_UNIFORM BGFX_CONFIG_DEBUG
#endif // BGFX_CONFIG_DEBUG_UNIFORM

/// Enable occlusion debug checks.
#ifndef BGFX_CONFIG_DEBUG_OCCLUSION
#	define BGFX_CONFIG_DEBUG_OCCLUSION BGFX_CONFIG_DEBUG
#endif // BGFX_CONFIG_DEBUG_OCCLUSION

/// Enable/disable multithreaded rendering. When enabled, bgfx can use a
/// separate render thread for GPU submission. Default is 1 on all platforms
/// that support threading (0 on Emscripten).
#ifndef BGFX_CONFIG_MULTITHREADED
#	define BGFX_CONFIG_MULTITHREADED ( (0 == BX_PLATFORM_EMSCRIPTEN) ? 1 : 0)
#endif // BGFX_CONFIG_MULTITHREADED

/// Maximum number of draw/compute calls per frame. Default is 65535 (64K - 1).
#ifndef BGFX_CONFIG_MAX_DRAW_CALLS
#	define BGFX_CONFIG_MAX_DRAW_CALLS ( (64<<10)-1)
#endif // BGFX_CONFIG_MAX_DRAW_CALLS

/// Maximum number of blit items per frame. Default is 1024.
#ifndef BGFX_CONFIG_MAX_BLIT_ITEMS
#	define BGFX_CONFIG_MAX_BLIT_ITEMS (1<<10)
#endif // BGFX_CONFIG_MAX_BLIT_ITEMS

/// Maximum number of cached transform matrices. Default is BGFX_CONFIG_MAX_DRAW_CALLS + 1.
/// Each draw call may reference a transform matrix; this cache stores them for the frame.
#ifndef BGFX_CONFIG_MAX_MATRIX_CACHE
#	define BGFX_CONFIG_MAX_MATRIX_CACHE (BGFX_CONFIG_MAX_DRAW_CALLS+1)
#endif // BGFX_CONFIG_MAX_MATRIX_CACHE

/// Maximum number of cached scissor rectangles per frame. Default is 4096.
#ifndef BGFX_CONFIG_MAX_RECT_CACHE
#	define BGFX_CONFIG_MAX_RECT_CACHE (4<<10)
#endif //  BGFX_CONFIG_MAX_RECT_CACHE

/// Number of bits used for depth in the sort key. Default is 32.
/// Reducing this allows more bits for other sort key fields.
#ifndef BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH
#	define BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH 32
#endif // BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH

/// Number of bits used for sequence number in the sort key. Default is 20.
/// Determines maximum draw calls per view in sequential mode (2^20 = ~1M).
#ifndef BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ
#	define BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ 20
#endif // BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ

/// Number of bits used for program index in the sort key. Default is 9.
/// Determines BGFX_CONFIG_MAX_PROGRAMS (2^9 = 512).
#ifndef BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM
#	define BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM 9
#endif // BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM

// Cannot be configured via compiler options.
#define BGFX_CONFIG_MAX_PROGRAMS (1<<BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM)
static_assert(bx::isPowerOf2(BGFX_CONFIG_MAX_PROGRAMS), "BGFX_CONFIG_MAX_PROGRAMS must be power of 2.");

/// Maximum number of views. Default is 256. Must be a power of 2.
/// Views are referenced by ViewId (uint16_t).
#ifndef BGFX_CONFIG_MAX_VIEWS
#	define BGFX_CONFIG_MAX_VIEWS 256
#endif // BGFX_CONFIG_MAX_VIEWS
static_assert(bx::isPowerOf2(BGFX_CONFIG_MAX_VIEWS), "BGFX_CONFIG_MAX_VIEWS must be power of 2.");

#define BGFX_CONFIG_MAX_VIEW_NAME_RESERVED 6

/// Maximum length of a view name string. Default is 256.
#ifndef BGFX_CONFIG_MAX_VIEW_NAME
#	define BGFX_CONFIG_MAX_VIEW_NAME 256
#endif // BGFX_CONFIG_MAX_VIEW_NAME

/// Maximum number of vertex layout declarations. Default is 64.
#ifndef BGFX_CONFIG_MAX_VERTEX_LAYOUTS
#	define BGFX_CONFIG_MAX_VERTEX_LAYOUTS 64
#endif // BGFX_CONFIG_MAX_VERTEX_LAYOUTS

/// Maximum number of static index buffer handles. Default is 4096.
#ifndef BGFX_CONFIG_MAX_INDEX_BUFFERS
#	define BGFX_CONFIG_MAX_INDEX_BUFFERS (4<<10)
#endif // BGFX_CONFIG_MAX_INDEX_BUFFERS

/// Maximum number of static vertex buffer handles. Default is 4096.
#ifndef BGFX_CONFIG_MAX_VERTEX_BUFFERS
#	define BGFX_CONFIG_MAX_VERTEX_BUFFERS (4<<10)
#endif // BGFX_CONFIG_MAX_VERTEX_BUFFERS

/// Maximum number of vertex streams per draw call. Default is 4.
#ifndef BGFX_CONFIG_MAX_VERTEX_STREAMS
#	define BGFX_CONFIG_MAX_VERTEX_STREAMS 4
#endif // BGFX_CONFIG_MAX_VERTEX_STREAMS

/// Maximum number of dynamic index buffer handles. Default is 4096.
#ifndef BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS
#	define BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS (4<<10)
#endif // BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS

/// Maximum number of dynamic vertex buffer handles. Default is 4096.
#ifndef BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS
#	define BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS (4<<10)
#endif // BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS

/// Initial size in bytes of the dynamic index buffer backing store. Default is 1 MB.
/// The backing store grows as needed via sub-allocation.
#ifndef BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE
#	define BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE (1<<20)
#endif // BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE

/// Initial size in bytes of the dynamic vertex buffer backing store. Default is 3 MB.
/// The backing store grows as needed via sub-allocation.
#ifndef BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE
#	define BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE (3<<20)
#endif // BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE

/// Maximum number of shader handles (vertex + fragment + compute). Default is 512.
#ifndef BGFX_CONFIG_MAX_SHADERS
#	define BGFX_CONFIG_MAX_SHADERS 512
#endif // BGFX_CONFIG_MAX_FRAGMENT_SHADERS

/// Maximum number of texture handles. Default is 4096.
#ifndef BGFX_CONFIG_MAX_TEXTURES
#	define BGFX_CONFIG_MAX_TEXTURES (4<<10)
#endif // BGFX_CONFIG_MAX_TEXTURES

/// Maximum number of texture samplers per draw call. Default is 16.
#ifndef BGFX_CONFIG_MAX_TEXTURE_SAMPLERS
#	define BGFX_CONFIG_MAX_TEXTURE_SAMPLERS 16
#endif // BGFX_CONFIG_MAX_TEXTURE_SAMPLERS

/// Maximum number of frame buffer handles. Default is 128.
#ifndef BGFX_CONFIG_MAX_FRAME_BUFFERS
#	define BGFX_CONFIG_MAX_FRAME_BUFFERS 128
#endif // BGFX_CONFIG_MAX_FRAME_BUFFERS

/// Maximum number of attachments (color + depth/stencil) per frame buffer.
/// Default is 8.
#ifndef BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
#	define BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS 8
#endif // BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS

/// Maximum number of uniform handles. Default is 512.
#ifndef BGFX_CONFIG_MAX_UNIFORMS
#	define BGFX_CONFIG_MAX_UNIFORMS 512
#endif // BGFX_CONFIG_MAX_UNIFORMS

/// Maximum number of occlusion query handles. Default is 256.
#ifndef BGFX_CONFIG_MAX_OCCLUSION_QUERIES
#	define BGFX_CONFIG_MAX_OCCLUSION_QUERIES 256
#endif // BGFX_CONFIG_MAX_OCCLUSION_QUERIES

/// Minimum initial size in bytes of the resource command buffer (pre/post
/// render commands for resource creation and updates). Default is 64 KB.
/// The buffer grows as needed.
#ifndef BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE
#	define BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE (64<<10)
#endif // BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE

#ifndef BGFX_CONFIG_MAX_TRANSIENT_VERTEX_BUFFER_SIZE
/// Maximum transient vertex buffer size. There is no growth, and all transient
/// vertices must fit into this buffer.
#	define BGFX_CONFIG_MAX_TRANSIENT_VERTEX_BUFFER_SIZE (6<<20)
#endif // BGFX_CONFIG_MAX_TRANSIENT_VERTEX_BUFFER_SIZE

#ifndef BGFX_CONFIG_MAX_TRANSIENT_INDEX_BUFFER_SIZE
/// Maximum transient index buffer size. There is no growth, and all transient
/// indices must fit into this buffer.
#	define BGFX_CONFIG_MAX_TRANSIENT_INDEX_BUFFER_SIZE (2<<20)
#endif // BGFX_CONFIG_MAX_TRANSIENT_INDEX_BUFFER_SIZE

#ifndef BGFX_CONFIG_MIN_UNIFORM_BUFFER_SIZE
/// Mimumum uniform buffer size. This buffer will resize on demand.
#	define BGFX_CONFIG_MIN_UNIFORM_BUFFER_SIZE (1<<20)
#endif // BGFX_CONFIG_MIN_UNIFORM_BUFFER_SIZE

#ifndef BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_THRESHOLD_SIZE
/// Max amount of unused uniform buffer space before uniform buffer resize.
#	define BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_THRESHOLD_SIZE (64<<10)
#endif // BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_THRESHOLD_SIZE

#ifndef BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_INCREMENT_SIZE
/// Increment of uniform buffer resize.
#	define BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_INCREMENT_SIZE (1<<20)
#endif // BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_INCREMENT_SIZE

#ifndef BGFX_CONFIG_CACHED_DEVICE_MEMORY_ALLOCATIONS_SIZE
/// Amount of allowed memory allocations left on device to use for recycling during
/// later allocations. This can be beneficial in case the driver is slow allocating memory
/// on the device.
/// Note: Currently only used by the Vulkan backend.
#	define BGFX_CONFIG_CACHED_DEVICE_MEMORY_ALLOCATIONS_SIZE (128 << 20)
#endif // BGFX_CONFIG_CACHED_DEVICE_MEMORY_ALLOCATIONS_SIZE

#ifndef BGFX_CONFIG_MAX_STAGING_SCRATCH_BUFFER_SIZE
/// The threshold of data size above which the staging scratch buffer will
/// not be used, but instead a separate device memory allocation will take
/// place to stage the data for copying to device.
#   define BGFX_CONFIG_MAX_STAGING_SCRATCH_BUFFER_SIZE (16 << 20)
#endif // BGFX_CONFIG_MAX_STAGING_SCRATCH_BUFFER_SIZE

#ifndef BGFX_CONFIG_MAX_SCRATCH_STAGING_BUFFER_PER_FRAME_SIZE
/// Amount of scratch buffer size (per in-flight frame) that will be reserved
/// for staging data for copying to the device (such as vertex buffer data,
/// texture data, etc). This buffer will be used instead of allocating memory
/// on device separately for every data copy.
/// Note: Currently only used by the Vulkan backend.
#   define BGFX_CONFIG_MAX_SCRATCH_STAGING_BUFFER_PER_FRAME_SIZE (32<<20)
#endif // BGFX_CONFIG_MAX_SCRATCH_STAGING_BUFFER_PER_FRAME_SIZE

/// Maximum number of instance data vec4 attributes per draw call. Default is 5.
/// Each instance data element is a vec4 (16 bytes). Total instance stride is
/// BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT * 16 bytes.
#ifndef BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT
#	define BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT 5
#endif // BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT

/// Maximum number of color palette entries. Default is 16.
/// Color palettes are used with clear color indexing.
#ifndef BGFX_CONFIG_MAX_COLOR_PALETTE
#	define BGFX_CONFIG_MAX_COLOR_PALETTE 16
#endif // BGFX_CONFIG_MAX_COLOR_PALETTE

/// Stride in bytes of each draw indirect command. Fixed at 32 bytes.
#define BGFX_CONFIG_DRAW_INDIRECT_STRIDE 32

/// Enable internal profiler instrumentation. When enabled, bgfx will emit
/// profiler scopes for frame, submit, resource, and view operations.
/// Default is 0 (disabled).
#ifndef BGFX_CONFIG_PROFILER
#	define BGFX_CONFIG_PROFILER 0
#endif // BGFX_CONFIG_PROFILER

/// File path for RenderDoc capture log output. Default is "temp/bgfx".
#ifndef BGFX_CONFIG_RENDERDOC_LOG_FILEPATH
#	define BGFX_CONFIG_RENDERDOC_LOG_FILEPATH "temp/bgfx"
#endif // BGFX_CONFIG_RENDERDOC_LOG_FILEPATH

/// Key(s) to trigger a RenderDoc capture. Default is F11.
#ifndef BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS
#	define BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS { eRENDERDOC_Key_F11 }
#endif // BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS

/// Timeout in milliseconds for the API/render thread semaphore wait.
/// Default is 5000 ms. If the wait times out, it typically indicates a
/// deadlock or the other thread has stalled.
#ifndef BGFX_CONFIG_API_SEMAPHORE_TIMEOUT
#	define BGFX_CONFIG_API_SEMAPHORE_TIMEOUT (5000)
#endif // BGFX_CONFIG_API_SEMAPHORE_TIMEOUT

/// Global MIP level-of-detail bias applied to all texture sampling.
/// Default is 0 (no bias). Positive values select coarser MIP levels,
/// negative values select finer MIP levels.
#ifndef BGFX_CONFIG_MIP_LOD_BIAS
#	define BGFX_CONFIG_MIP_LOD_BIAS 0
#endif // BGFX_CONFIG_MIP_LOD_BIAS

/// Default maximum number of simultaneous encoders for multithreaded
/// draw call submission. Default is 8 when multithreaded, 1 otherwise.
/// Can be overridden at runtime via Limits.maxEncoders in bgfx::Init.
#ifndef BGFX_CONFIG_DEFAULT_MAX_ENCODERS
#	define BGFX_CONFIG_DEFAULT_MAX_ENCODERS ( (0 != BGFX_CONFIG_MULTITHREADED) ? 8 : 1)
#endif // BGFX_CONFIG_DEFAULT_MAX_ENCODERS

/// Maximum number of back buffers for swap chain. Default is 4.
/// The actual number used is specified via bgfx::Resolution::numBackBuffers.
#ifndef BGFX_CONFIG_MAX_BACK_BUFFERS
#	define BGFX_CONFIG_MAX_BACK_BUFFERS 4
#endif // BGFX_CONFIG_MAX_BACK_BUFFERS

/// Maximum frame latency (number of frames that can be queued ahead).
/// Default is 3. The actual value is specified via
/// bgfx::Resolution::maxFrameLatency.
#ifndef BGFX_CONFIG_MAX_FRAME_LATENCY
#	define BGFX_CONFIG_MAX_FRAME_LATENCY 3
#endif // BGFX_CONFIG_MAX_FRAME_LATENCY

/// On laptops with integrated and discrete GPU, prefer selection of the
/// discrete GPU. Applies to nVidia and AMD on Windows only.
/// Default is 1 on Windows, 0 elsewhere.
#ifndef BGFX_CONFIG_PREFER_DISCRETE_GPU
#	define BGFX_CONFIG_PREFER_DISCRETE_GPU BX_PLATFORM_WINDOWS
#endif // BGFX_CONFIG_PREFER_DISCRETE_GPU

/// Maximum number of screenshot requests that can be queued per frame.
/// Default is 4.
#ifndef BGFX_CONFIG_MAX_SCREENSHOTS
#	define BGFX_CONFIG_MAX_SCREENSHOTS 4
#endif // BGFX_CONFIG_MAX_SCREENSHOTS

/// When set to 1, disable the legacy non-encoder API (bgfx::setState,
/// bgfx::submit, etc.) and require all submissions to go through the
/// Encoder API (bgfx::begin / bgfx::end). Default is 0.
#ifndef BGFX_CONFIG_ENCODER_API_ONLY
#	define BGFX_CONFIG_ENCODER_API_ONLY 0
#endif // BGFX_CONFIG_ENCODER_API_ONLY

#endif // BGFX_CONFIG_H_HEADER_GUARD

/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_H_HEADER_GUARD
#define BGFX_H_HEADER_GUARD

#include <stdarg.h> // va_list
#include <stdint.h> // uint32_t
#include <stdlib.h> // NULL

#include "defines.h"

///
#define BGFX_HANDLE(_name)                                                           \
	struct _name { uint16_t idx; };                                                  \
	inline bool isValid(_name _handle) { return bgfx::kInvalidHandle != _handle.idx; }

#define BGFX_INVALID_HANDLE { bgfx::kInvalidHandle }

namespace bx { struct AllocatorI; }

/// BGFX
namespace bgfx
{
	/// Fatal error enum.
	///
	/// @attention C99 equivalent is `bgfx_fatal_t`.
	///
	struct Fatal
	{
		enum Enum
		{
			DebugCheck,
			InvalidShader,
			UnableToInitialize,
			UnableToCreateTexture,
			DeviceLost,

			Count
		};
	};

	/// Renderer backend type enum.
	///
	/// @attention C99 equivalent is `bgfx_renderer_type_t`.
	///
	struct RendererType
	{
		/// Renderer types:
		enum Enum
		{
			Noop,         //!< No rendering.
			Direct3D9,    //!< Direct3D 9.0
			Direct3D11,   //!< Direct3D 11.0
			Direct3D12,   //!< Direct3D 12.0
			Gnm,          //!< GNM
			Metal,        //!< Metal
			Nvn,          //!< NVN
			OpenGLES,     //!< OpenGL ES 2.0+
			OpenGL,       //!< OpenGL 2.1+
			Vulkan,       //!< Vulkan
			WebGPU,       //!< WebGPU

			Count
		};
	};

	/// Access mode enum.
	///
	/// @attention C99 equivalent is `bgfx_access_t`.
	///
	struct Access
	{
		/// Access:
		enum Enum
		{
			Read,      //!< Read
			Write,     //!< Write
			ReadWrite, //!< Read and write

			Count
		};
	};

	/// Vertex attribute enum.
	///
	/// @attention C99 equivalent is `bgfx_attrib_t`.
	///
	struct Attrib
	{
		/// Corresponds to vertex shader attribute.
		enum Enum
		{
			Position,  //!< a_position
			Normal,    //!< a_normal
			Tangent,   //!< a_tangent
			Bitangent, //!< a_bitangent
			Color0,    //!< a_color0
			Color1,    //!< a_color1
			Color2,    //!< a_color2
			Color3,    //!< a_color3
			Indices,   //!< a_indices
			Weight,    //!< a_weight
			TexCoord0, //!< a_texcoord0
			TexCoord1, //!< a_texcoord1
			TexCoord2, //!< a_texcoord2
			TexCoord3, //!< a_texcoord3
			TexCoord4, //!< a_texcoord4
			TexCoord5, //!< a_texcoord5
			TexCoord6, //!< a_texcoord6
			TexCoord7, //!< a_texcoord7

			Count
		};
	};

	/// Vertex attribute type enum.
	///
	/// @attention C99 equivalent is `bgfx_attrib_type_t`.
	///
	struct AttribType
	{
		/// Attribute types:
		enum Enum
		{
			Uint8,  //!< Uint8
			Uint10, //!< Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
			Int16,  //!< Int16
			Half,   //!< Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
			Float,  //!< Float

			Count
		};
	};

	/// Texture format enum.
	///
	/// Notation:
	///
	///       RGBA16S
	///       ^   ^ ^
	///       |   | +-- [ ]Unorm
	///       |   |     [F]loat
	///       |   |     [S]norm
	///       |   |     [I]nt
	///       |   |     [U]int
	///       |   +---- Number of bits per component
	///       +-------- Components
	///
	/// @attention Availability depends on Caps (see: formats).
	///
	/// @attention C99 equivalent is `bgfx_texture_format_t`.
	///
	struct TextureFormat
	{
		/// Texture formats:
		enum Enum
		{
			BC1,          //!< DXT1 R5G6B5A1
			BC2,          //!< DXT3 R5G6B5A4
			BC3,          //!< DXT5 R5G6B5A8
			BC4,          //!< LATC1/ATI1 R8
			BC5,          //!< LATC2/ATI2 RG8
			BC6H,         //!< BC6H RGB16F
			BC7,          //!< BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
			ETC1,         //!< ETC1 RGB8
			ETC2,         //!< ETC2 RGB8
			ETC2A,        //!< ETC2 RGBA8
			ETC2A1,       //!< ETC2 RGB8A1
			PTC12,        //!< PVRTC1 RGB 2BPP
			PTC14,        //!< PVRTC1 RGB 4BPP
			PTC12A,       //!< PVRTC1 RGBA 2BPP
			PTC14A,       //!< PVRTC1 RGBA 4BPP
			PTC22,        //!< PVRTC2 RGBA 2BPP
			PTC24,        //!< PVRTC2 RGBA 4BPP
			ATC,          //!< ATC RGB 4BPP
			ATCE,         //!< ATCE RGBA 8 BPP explicit alpha
			ATCI,         //!< ATCI RGBA 8 BPP interpolated alpha
			ASTC4x4,      //!< ASTC 4x4 8.0 BPP
			ASTC5x5,      //!< ASTC 5x5 5.12 BPP
			ASTC6x6,      //!< ASTC 6x6 3.56 BPP
			ASTC8x5,      //!< ASTC 8x5 3.20 BPP
			ASTC8x6,      //!< ASTC 8x6 2.67 BPP
			ASTC10x5,     //!< ASTC 10x5 2.56 BPP

			Unknown,      // Compressed formats above.

			R1,
			A8,
			R8,
			R8I,
			R8U,
			R8S,
			R16,
			R16I,
			R16U,
			R16F,
			R16S,
			R32I,
			R32U,
			R32F,
			RG8,
			RG8I,
			RG8U,
			RG8S,
			RG16,
			RG16I,
			RG16U,
			RG16F,
			RG16S,
			RG32I,
			RG32U,
			RG32F,
			RGB8,
			RGB8I,
			RGB8U,
			RGB8S,
			RGB9E5F,
			BGRA8,
			RGBA8,
			RGBA8I,
			RGBA8U,
			RGBA8S,
			RGBA16,
			RGBA16I,
			RGBA16U,
			RGBA16F,
			RGBA16S,
			RGBA32I,
			RGBA32U,
			RGBA32F,
			R5G6B5,
			RGBA4,
			RGB5A1,
			RGB10A2,
			RG11B10F,

			UnknownDepth, // Depth formats below.

			D16,
			D24,
			D24S8,
			D32,
			D16F,
			D24F,
			D32F,
			D0S8,

			Count
		};
	};

	/// Uniform type enum.
	///
	/// @attention C99 equivalent is `bgfx_uniform_type_t`.
	///
	struct UniformType
	{
		/// Uniform types:
		enum Enum
		{
			Sampler, //!< Sampler.
			End,     //!< Reserved, do not use.

			Vec4,    //!< 4 floats vector.
			Mat3,    //!< 3x3 matrix.
			Mat4,    //!< 4x4 matrix.

			Count
		};
	};

	/// Backbuffer ratio enum.
	///
	/// @attention C99 equivalent is `bgfx_backbuffer_ratio_t`.
	///
	struct BackbufferRatio
	{
		/// Backbuffer ratios:
		enum Enum
		{
			Equal,     //!< Equal to backbuffer.
			Half,      //!< One half size of backbuffer.
			Quarter,   //!< One quarter size of backbuffer.
			Eighth,    //!< One eighth size of backbuffer.
			Sixteenth, //!< One sixteenth size of backbuffer.
			Double,    //!< Double size of backbuffer.

			Count
		};
	};

	/// Occlusion query result.
	///
	/// @attention C99 equivalent is `bgfx_occlusion_query_result_t`.
	///
	struct OcclusionQueryResult
	{
		/// Occlusion query results:
		enum Enum
		{
			Invisible, //!< Query failed test.
			Visible,   //!< Query passed test.
			NoResult,  //!< Query result is not available yet.

			Count
		};
	};

	/// Primitive topology.
	///
	/// @attention C99 equivalent is `bgfx_topology_t`.
	///
	struct Topology
	{
		/// Primitive topology:
		enum Enum
		{
			TriList,   //!< Triangle list.
			TriStrip,  //!< Triangle strip.
			LineList,  //!< Line list.
			LineStrip, //!< Line strip.
			PointList, //!< Point list.

			Count
		};
	};

	/// Topology conversion function.
	///
	/// @attention C99 equivalent is `bgfx_topology_convert_t`.
	///
	struct TopologyConvert
	{
		/// Topology conversion functions:
		enum Enum
		{
			TriListFlipWinding,  //!< Flip winding order of triangle list.
			TriStripFlipWinding, //!< Flip winding order of trinagle strip.
			TriListToLineList,   //!< Convert triangle list to line list.
			TriStripToTriList,   //!< Convert triangle strip to triangle list.
			LineStripToLineList, //!< Convert line strip to line list.

			Count
		};
	};

	/// Topology sort order.
	///
	/// @attention C99 equivalent is `bgfx_topology_sort_t`.
	///
	struct TopologySort
	{
		/// Topology sort order:
		enum Enum
		{
			DirectionFrontToBackMin, //!<
			DirectionFrontToBackAvg, //!<
			DirectionFrontToBackMax, //!<
			DirectionBackToFrontMin, //!<
			DirectionBackToFrontAvg, //!<
			DirectionBackToFrontMax, //!<
			DistanceFrontToBackMin,  //!<
			DistanceFrontToBackAvg,  //!<
			DistanceFrontToBackMax,  //!<
			DistanceBackToFrontMin,  //!<
			DistanceBackToFrontAvg,  //!<
			DistanceBackToFrontMax,  //!<

			Count
		};
	};

	/// View mode sets draw call sort order.
	///
	/// @attention C99 equivalent is `bgfx_view_mode_t`.
	///
	struct ViewMode
	{
		/// View modes:
		enum Enum
		{
			Default,         //!< Default sort order.
			Sequential,      //!< Sort in the same order in which submit calls were called.
			DepthAscending,  //!< Sort draw call depth in ascending order.
			DepthDescending, //!< Sort draw call depth in descending order.

			Count
		};
	};

	static const uint16_t kInvalidHandle = UINT16_MAX;

	BGFX_HANDLE(DynamicIndexBufferHandle)
	BGFX_HANDLE(DynamicVertexBufferHandle)
	BGFX_HANDLE(FrameBufferHandle)
	BGFX_HANDLE(IndexBufferHandle)
	BGFX_HANDLE(IndirectBufferHandle)
	BGFX_HANDLE(OcclusionQueryHandle)
	BGFX_HANDLE(ProgramHandle)
	BGFX_HANDLE(ShaderHandle)
	BGFX_HANDLE(TextureHandle)
	BGFX_HANDLE(UniformHandle)
	BGFX_HANDLE(VertexBufferHandle)
	BGFX_HANDLE(VertexLayoutHandle)

	/// Callback interface to implement application specific behavior.
	/// Cached items are currently used for OpenGL and Direct3D 12 binary
	/// shaders.
	///
	/// @remarks
	///   'fatal' and 'trace' callbacks can be called from any thread. Other
	///   callbacks are called from the render thread.
	///
	/// @attention C99 equivalent is `bgfx_callback_interface_t`.
	///
	struct CallbackI
	{
		virtual ~CallbackI() = 0;

		/// This callback is called on unrecoverable errors.
		/// It's not safe to continue (Exluding _code `Fatal::DebugCheck`),
		/// inform the user and terminate the application.
		///
		/// @param[in] _filePath File path where fatal message was generated.
		/// @param[in] _line Line where fatal message was generated.
		/// @param[in] _code Fatal error code.
		/// @param[in] _str More information about error.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.fatal`.
		///
		virtual void fatal(
			  const char* _filePath
			, uint16_t _line
			, Fatal::Enum _code
			, const char* _str
			) = 0;

		/// Print debug message.
		///
		/// @param[in] _filePath File path where debug message was generated.
		/// @param[in] _line Line where debug message was generated.
		/// @param[in] _format `printf` style format.
		/// @param[in] _argList Variable arguments list initialized with
		///   `va_start`.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.trace_vargs`.
		///
		virtual void traceVargs(
			  const char* _filePath
			, uint16_t _line
			, const char* _format
			, va_list _argList
			) = 0;

		/// Profiler region begin.
		///
		/// @param[in] _name Region name, contains dynamic string.
		/// @param[in] _abgr Color of profiler region.
		/// @param[in] _filePath File path where `profilerBegin` was called.
		/// @param[in] _line Line where `profilerBegin` was called.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_begin`.
		///
		virtual void profilerBegin(
			  const char* _name
			, uint32_t _abgr
			, const char* _filePath
			, uint16_t _line
			) = 0;

		/// Profiler region begin with string literal name.
		///
		/// @param[in] _name Region name, contains string literal.
		/// @param[in] _abgr Color of profiler region.
		/// @param[in] _filePath File path where `profilerBeginLiteral` was called.
		/// @param[in] _line Line where `profilerBeginLiteral` was called.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_begin_literal`.
		///
		virtual void profilerBeginLiteral(
			  const char* _name
			, uint32_t _abgr
			, const char* _filePath
			, uint16_t _line
			) = 0;

		/// Profiler region end.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_end`.
		///
		virtual void profilerEnd() = 0;

		/// Returns the size of a cached item. Returns 0 if no cached item was
		/// found.
		///
		/// @param[in] _id Cache id.
		/// @returns Number of bytes to read.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.cache_read_size`.
		///
		virtual uint32_t cacheReadSize(uint64_t _id) = 0;

		/// Read cached item.
		///
		/// @param[in] _id Cache id.
		/// @param[in] _data Buffer where to read data.
		/// @param[in] _size Size of data to read.
		///
		/// @returns True if data is read.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.cache_read`.
		///
		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) = 0;

		/// Write cached item.
		///
		/// @param[in] _id Cache id.
		/// @param[in] _data Data to write.
		/// @param[in] _size Size of data to write.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.cache_write`.
		///
		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) = 0;

		/// Screenshot captured. Screenshot format is always 4-byte BGRA.
		///
		/// @param[in] _filePath File path.
		/// @param[in] _width Image width.
		/// @param[in] _height Image height.
		/// @param[in] _pitch Number of bytes to skip between the start of
		///   each horizontal line of the image.
		/// @param[in] _data Image data.
		/// @param[in] _size Image size.
		/// @param[in] _yflip If true, image origin is bottom left.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.screen_shot`.
		///
		virtual void screenShot(
			  const char* _filePath
			, uint32_t _width
			, uint32_t _height
			, uint32_t _pitch
			, const void* _data
			, uint32_t _size
			, bool _yflip
			) = 0;

		/// Called when a video capture begins.
		///
		/// @param[in] _width Image width.
		/// @param[in] _height Image height.
		/// @param[in] _pitch Number of bytes to skip between the start of
		///   each horizontal line of the image.
		/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
		/// @param[in] _yflip If true, image origin is bottom left.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.capture_begin`.
		///
		virtual void captureBegin(
			  uint32_t _width
			, uint32_t _height
			, uint32_t _pitch
			, TextureFormat::Enum _format
			, bool _yflip
			) = 0;

		/// Called when a video capture ends.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.capture_end`.
		///
		virtual void captureEnd() = 0;

		/// Captured frame.
		///
		/// @param[in] _data Image data.
		/// @param[in] _size Image size.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.capture_frame`.
		///
		virtual void captureFrame(const void* _data, uint32_t _size) = 0;
	};

	inline CallbackI::~CallbackI()
	{
	}

	/// Platform data.
	///
	/// @attention C99 equivalent is `bgfx_platform_data_t`.
	///
	struct PlatformData
	{
		PlatformData();

		void* ndt;          //!< Native display type (*nix specific).
		void* nwh;          //!< Native window handle. If `NULL` bgfx will create headless
		                    ///  context/device if renderer API supports it.
		void* context;      //!< GL context, or D3D device. If `NULL`, bgfx will create context/device.
		void* backBuffer;   //!< GL back-buffer, or D3D render target view. If `NULL` bgfx will
		                    ///  create back-buffer color surface.
		void* backBufferDS; //!< Backbuffer depth/stencil. If `NULL` bgfx will create back-buffer
		                    ///  depth/stencil surface.
	};

	/// Backbuffer resolution and reset parameters.
	///
	/// @attention C99 equivalent is `bgfx_resolution_t`.
	///
	struct Resolution
	{
		Resolution();

		TextureFormat::Enum format; //!< Backbuffer format.
		uint32_t width;             //!< Backbuffer width.
		uint32_t height;            //!< Backbuffer height.
		uint32_t reset;	            //!< Reset parameters.
		uint8_t  numBackBuffers;    //!< Number of back buffers.
		uint8_t  maxFrameLatency;   //!< Maximum frame latency.
	};

	/// Initialization parameters used by `bgfx::init`.
	///
	/// @attention C99 equivalent is `bgfx_init_t`.
	///
	struct Init
	{
		Init();

		/// Select rendering backend. When set to RendererType::Count
		/// a default rendering backend will be selected appropriate to the platform.
		/// See: `bgfx::RendererType`
		RendererType::Enum type;

		/// Vendor PCI id. If set to `BGFX_PCI_ID_NONE` it will select the first
		/// device.
		///   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
		///   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
		///   - `BGFX_PCI_ID_AMD` - AMD adapter.
		///   - `BGFX_PCI_ID_INTEL` - Intel adapter.
		///   - `BGFX_PCI_ID_NVIDIA` - nVidia adapter.
		uint16_t vendorId;

		/// Device id. If set to 0 it will select first device, or device with
		/// matching id.
		uint16_t deviceId;

		bool debug;   //!< Enable device for debuging.
		bool profile; //!< Enable device for profiling.

		/// Platform data.
		PlatformData platformData;

		/// Backbuffer resolution and reset parameters. See: `bgfx::Resolution`.
		Resolution resolution;

		/// Configurable runtime limits parameters.
		///
		/// @attention C99 equivalent is `bgfx_init_limits_t`.
		///
		struct Limits
		{
			Limits();

			uint16_t maxEncoders;       //!< Maximum number of encoder threads.
			uint32_t minResourceCbSize; //!< Minimum resource command buffer size.
			uint32_t transientVbSize;   //!< Maximum transient vertex buffer size.
			uint32_t transientIbSize;   //!< Maximum transient index buffer size.
		};

		Limits limits; // Configurable runtime limits.

		/// Provide application specific callback interface.
		/// See: `bgfx::CallbackI`
		CallbackI* callback;

		/// Custom allocator. When a custom allocator is not
		/// specified, bgfx uses the CRT allocator. Bgfx assumes
		/// custom allocator is thread safe.
		bx::AllocatorI* allocator;
	};

	/// Memory release callback.
	///
	/// param[in] _ptr Pointer to allocated data.
	/// param[in] _userData User defined data if needed.
	///
	/// @attention C99 equivalent is `bgfx_release_fn_t`.
	///
	typedef void (*ReleaseFn)(void* _ptr, void* _userData);

	/// Memory must be obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
	///
	/// @attention It is illegal to create this structure on stack and pass it to any bgfx API.
	///
	/// @attention C99 equivalent is `bgfx_memory_t`.
	///
	struct Memory
	{
		Memory() = delete;

		uint8_t* data; //!< Pointer to data.
		uint32_t size; //!< Data size.
	};

	/// Renderer capabilities.
	///
	/// @attention C99 equivalent is `bgfx_caps_t`.
	///
	struct Caps
	{
		/// Renderer backend type. See: `bgfx::RendererType`
		RendererType::Enum rendererType;

		/// Supported functionality.
		///
		/// @attention See BGFX_CAPS_* flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
		///
		uint64_t supported;

		uint16_t vendorId;         //!< Selected GPU vendor PCI id.
		uint16_t deviceId;         //!< Selected GPU device id.
		bool     homogeneousDepth; //!< True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
		bool     originBottomLeft; //!< True when NDC origin is at bottom left.
		uint8_t  numGPUs;          //!< Number of enumerated GPUs.

		/// GPU info.
		///
		/// @attention C99 equivalent is `bgfx_caps_gpu_t`.
		///
		struct GPU
		{
			uint16_t vendorId; //!< Vendor PCI id. See `BGFX_PCI_ID_*`.
			uint16_t deviceId; //!< Device id.
		};

		GPU gpu[4]; //!< Enumerated GPUs.

		/// Renderer runtime limits.
		///
		/// @attention C99 equivalent is `bgfx_caps_limits_t`.
		///
		struct Limits
		{
			uint32_t maxDrawCalls;            //!< Maximum number of draw calls.
			uint32_t maxBlits;                //!< Maximum number of blit calls.
			uint32_t maxTextureSize;          //!< Maximum texture size.
			uint32_t maxTextureLayers;        //!< Maximum texture layers.
			uint32_t maxViews;                //!< Maximum number of views.
			uint32_t maxFrameBuffers;         //!< Maximum number of frame buffer handles.
			uint32_t maxFBAttachments;        //!< Maximum number of frame buffer attachments.
			uint32_t maxPrograms;             //!< Maximum number of program handles.
			uint32_t maxShaders;              //!< Maximum number of shader handles.
			uint32_t maxTextures;             //!< Maximum number of texture handles.
			uint32_t maxTextureSamplers;      //!< Maximum number of texture samplers.
			uint32_t maxComputeBindings;      //!< Maximum number of compute bindings.
			uint32_t maxVertexLayouts;        //!< Maximum number of vertex format layouts.
			uint32_t maxVertexStreams;        //!< Maximum number of vertex streams.
			uint32_t maxIndexBuffers;         //!< Maximum number of index buffer handles.
			uint32_t maxVertexBuffers;        //!< Maximum number of vertex buffer handles.
			uint32_t maxDynamicIndexBuffers;  //!< Maximum number of dynamic index buffer handles.
			uint32_t maxDynamicVertexBuffers; //!< Maximum number of dynamic vertex buffer handles.
			uint32_t maxUniforms;             //!< Maximum number of uniform handles.
			uint32_t maxOcclusionQueries;     //!< Maximum number of occlusion query handles.
			uint32_t maxEncoders;             //!< Maximum number of encoder threads.
			uint32_t minResourceCbSize;       //!< Minimum resource command buffer size.
			uint32_t transientVbSize;         //!< Maximum transient vertex buffer size.
			uint32_t transientIbSize;         //!< Maximum transient index buffer size.
		};

		Limits limits; //!< Renderer runtime limits.

		/// Supported texture format capabilities flags:
		///   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ` - Texture format can be used as image
		///     and read from.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE` - Texture format can be used as image
		///     and written to.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
		///     buffer.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
		///     frame buffer.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
		///     mips.
		uint16_t formats[TextureFormat::Count];
	};

	/// Transient index buffer.
	///
	/// @attention C99 equivalent is `bgfx_transient_index_buffer_t`.
	///
	struct TransientIndexBuffer
	{
		uint8_t* data;            //!< Pointer to data.
		uint32_t size;            //!< Data size.
		uint32_t startIndex;      //!< First index.
		IndexBufferHandle handle; //!< Index buffer handle.
		bool isIndex16;           //!< Index buffer format is 16-bits if true, otherwise it is 32-bit.
	};

	/// Transient vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_transient_vertex_buffer_t`.
	///
	struct TransientVertexBuffer
	{
		uint8_t* data;                      //!< Pointer to data.
		uint32_t size;                      //!< Data size.
		uint32_t startVertex;               //!< First vertex.
		uint16_t stride;                    //!< Vertex stride.
		VertexBufferHandle handle;          //!< Vertex buffer handle.
		VertexLayoutHandle layoutHandle;    //!< Vertex layout handle.
	};

	/// Instance data buffer info.
	///
	/// @attention C99 equivalent is `bgfx_instance_data_buffer_t`.
	///
	struct InstanceDataBuffer
	{
		uint8_t* data;             //!< Pointer to data.
		uint32_t size;             //!< Data size.
		uint32_t offset;           //!< Offset in vertex buffer.
		uint32_t num;              //!< Number of instances.
		uint16_t stride;           //!< Vertex buffer stride.
		VertexBufferHandle handle; //!< Vertex buffer object handle.
	};

	/// Texture info.
	///
	/// @attention C99 equivalent is `bgfx_texture_info_t`.
	///
	struct TextureInfo
	{
		TextureFormat::Enum format; //!< Texture format.
		uint32_t storageSize;       //!< Total amount of bytes required to store texture.
		uint16_t width;             //!< Texture width.
		uint16_t height;            //!< Texture height.
		uint16_t depth;             //!< Texture depth.
		uint16_t numLayers;         //!< Number of layers in texture array.
		uint8_t numMips;            //!< Number of MIP maps.
		uint8_t bitsPerPixel;       //!< Format bits per pixel.
		bool    cubeMap;            //!< Texture is cubemap.
	};

	/// Uniform info.
	///
	/// @attention C99 equivalent is `bgfx_uniform_info_t`.
	///
	struct UniformInfo
	{
		char name[256];         //!< Uniform name.
		UniformType::Enum type; //!< Uniform type.
		uint16_t num;           //!< Number of elements in array.
	};

	/// Frame buffer texture attachment info.
	///
	/// @attention C99 equivalent is `bgfx_attachment_t`.
	///
	struct Attachment
	{
		/// Init attachment.
		///
		/// @param[in] _handle Render target texture handle.
		/// @param[in] _access Access. See `Access::Enum`.
		/// @param[in] _layer Cubemap side or depth layer/slice to use.
		/// @param[in] _numLayers Number of texture layer/slice(s) in array to use.
		/// @param[in] _mip Mip level.
		/// @param[in] _resolve Resolve flags. See: `BGFX_RESOLVE_*`
		///
		void init(
			  TextureHandle _handle
			, Access::Enum _access = Access::Write
			, uint16_t _layer = 0
			, uint16_t _numLayers = 1
			, uint16_t _mip = 0
			, uint8_t _resolve = BGFX_RESOLVE_AUTO_GEN_MIPS
			);

		Access::Enum  access; //!< Attachement access. See `Access::Enum`.
		TextureHandle handle; //!< Render target texture handle.
		uint16_t mip;         //!< Mip level.
		uint16_t layer;       //!< Cubemap side or depth layer/slice to use.
		uint16_t numLayers;   //!< Number of texture layer/slice(s) in array to use.
		uint8_t  resolve;     //!< Resolve flags. See: `BGFX_RESOLVE_*`
	};

	/// Transform data.
	///
	/// @attention C99 equivalent is `bgfx_transform_t`.
	///
	struct Transform
	{
		float* data;  //!< Pointer to first 4x4 matrix.
		uint16_t num; //!< Number of matrices.
	};

	///
	typedef uint16_t ViewId;

	/// View stats.
	///
	/// @attention C99 equivalent is `bgfx_view_stats_t`.
	///
	struct ViewStats
	{
		char    name[256];      //!< View name.
		ViewId  view;           //!< View id.
		int64_t cpuTimeBegin;   //!< CPU (submit) begin time.
		int64_t cpuTimeEnd;     //!< CPU (submit) end time.
		int64_t gpuTimeBegin;   //!< GPU begin time.
		int64_t gpuTimeEnd;     //!< GPU end time.
	};

	/// Encoder stats.
	///
	/// @attention C99 equivalent is `bgfx_encoder_stats_t`.
	///
	struct EncoderStats
	{
		int64_t cpuTimeBegin; //!< Encoder thread CPU submit begin time.
		int64_t cpuTimeEnd;   //!< Encoder thread CPU submit end time.
	};

	/// Renderer statistics data.
	///
	/// @attention C99 equivalent is `bgfx_stats_t`.
	///
	/// @remarks All time values are high-resolution timestamps, while
	///   time frequencies define timestamps-per-second for that hardware.
	struct Stats
	{
		int64_t cpuTimeFrame;               //!< CPU time between two `bgfx::frame` calls.
		int64_t cpuTimeBegin;               //!< Render thread CPU submit begin time.
		int64_t cpuTimeEnd;                 //!< Render thread CPU submit end time.
		int64_t cpuTimerFreq;               //!< CPU timer frequency. Timestamps-per-second

		int64_t gpuTimeBegin;               //!< GPU frame begin time.
		int64_t gpuTimeEnd;                 //!< GPU frame end time.
		int64_t gpuTimerFreq;               //!< GPU timer frequency.

		int64_t waitRender;                 //!< Time spent waiting for render backend thread to finish issuing
		                                    //!  draw commands to underlying graphics API.
		int64_t waitSubmit;                 //!< Time spent waiting for submit thread to advance to next frame.

		uint32_t numDraw;                   //!< Number of draw calls submitted.
		uint32_t numCompute;                //!< Number of compute calls submitted.
		uint32_t numBlit;                   //!< Number of blit calls submitted.
		uint32_t maxGpuLatency;             //!< GPU driver latency.

		uint16_t numDynamicIndexBuffers;    //!< Number of used dynamic index buffers.
		uint16_t numDynamicVertexBuffers;   //!< Number of used dynamic vertex buffers.
		uint16_t numFrameBuffers;           //!< Number of used frame buffers.
		uint16_t numIndexBuffers;           //!< Number of used index buffers.
		uint16_t numOcclusionQueries;       //!< Number of used occlusion queries.
		uint16_t numPrograms;               //!< Number of used programs.
		uint16_t numShaders;                //!< Number of used shaders.
		uint16_t numTextures;               //!< Number of used textures.
		uint16_t numUniforms;               //!< Number of used uniforms.
		uint16_t numVertexBuffers;          //!< Number of used vertex buffers.
		uint16_t numVertexLayouts;          //!< Number of used vertex layouts.

		int64_t textureMemoryUsed;          //!< Estimate of texture memory used.
		int64_t rtMemoryUsed;               //!< Estimate of render target memory used.
		int32_t transientVbUsed;            //!< Amount of transient vertex buffer used.
		int32_t transientIbUsed;            //!< Amount of transient index buffer used.

		uint32_t numPrims[Topology::Count]; //!< Number of primitives rendered.

		int64_t gpuMemoryMax;               //!< Maximum available GPU memory for application.
		int64_t gpuMemoryUsed;              //!< Amount of GPU memory used by the application.

		uint16_t width;                     //!< Backbuffer width in pixels.
		uint16_t height;                    //!< Backbuffer height in pixels.
		uint16_t textWidth;                 //!< Debug text width in characters.
		uint16_t textHeight;                //!< Debug text height in characters.

		uint16_t   numViews;                //!< Number of view stats.
		ViewStats* viewStats;               //!< Array of View stats.

		uint8_t       numEncoders;          //!< Number of encoders used during frame.
		EncoderStats* encoderStats;         //!< Array of encoder stats.
	};

	/// Encoders are used for submitting draw calls from multiple threads. Only one encoder
	/// per thread should be used. Use `bgfx::begin()` to obtain an encoder for a thread.
	///
	/// @attention C99 equivalent is `bgfx_encoder`.
	///
	struct Encoder
	{
		/// Sets a debug marker. This allows you to group
		/// graphics calls together for easy browsing in
		/// graphics debugging tools.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_marker`.
		///
		void setMarker(const char* _marker);

		/// Set render states for draw primitive.
		///
		/// @param[in] _state State flags. Default state for primitive type is
		///   triangles. See: `BGFX_STATE_DEFAULT`.
		///   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
		///   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
		///   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
		///   - `BGFX_STATE_CULL_*` - Backface culling mode.
		///   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
		///   - `BGFX_STATE_MSAA` - Enable hardware multisample antialiasing.
		///   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
		///
		/// @param[in] _rgba Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
		///   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
		///
		/// @remarks
		///   1. To setup more complex states use:
		///      `BGFX_STATE_ALPHA_REF(_ref)`,
		///      `BGFX_STATE_POINT_SIZE(_size)`,
		///      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
		///      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`,
		///      `BGFX_STATE_BLEND_EQUATION(_equation)`,
		///      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
		///   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
		///      equation is specified.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_state`.
		///
		void setState(
			  uint64_t _state
			, uint32_t _rgba = 0
			);

		/// Set condition for rendering.
		///
		/// @param[in] _handle Occlusion query handle.
		/// @param[in] _visible Render if occlusion query is visible.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_condition`.
		///
		void setCondition(
			  OcclusionQueryHandle _handle
			, bool _visible
			);

		/// Set stencil test state.
		///
		/// @param[in] _fstencil Front stencil state.
		/// @param[in] _bstencil Back stencil state. If back is set to `BGFX_STENCIL_NONE`
		///   _fstencil is applied to both front and back facing primitives.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_stencil`.
		///
		void setStencil(
			  uint32_t _fstencil
			, uint32_t _bstencil = BGFX_STENCIL_NONE
			);

		/// Set scissor for draw primitive. To scissor for all primitives in
		/// view see `bgfx::setViewScissor`.
		///
		/// @param[in] _x Position x from the left side of the window.
		/// @param[in] _y Position y from the top of the window.
		/// @param[in] _width Width of scissor region.
		/// @param[in] _height Height of scissor region.
		/// @returns Scissor cache index.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_scissor`.
		///
		uint16_t setScissor(
			  uint16_t _x
			, uint16_t _y
			, uint16_t _width
			, uint16_t _height
			);

		/// Set scissor from cache for draw primitive.
		///
		/// @param[in] _cache Index in scissor cache.
		///   Pass UINT16_MAX to have primitive use view scissor instead.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_scissor_cached`.
		///
		void setScissor(uint16_t _cache = UINT16_MAX);

		/// Set model matrix for draw primitive. If it is not called, model will
		/// be rendered with identity model matrix.
		///
		/// @param[in] _mtx Pointer to first matrix in array.
		/// @param[in] _num Number of matrices in array.
		/// @returns Index into matrix cache in case the same model matrix has
		///   to be used for other draw primitive call.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transform`.
		///
		uint32_t setTransform(
			  const void* _mtx
			, uint16_t _num = 1
			);

		/// Reserve `_num` matrices in internal matrix cache.
		///
		/// @param[in] _transform Pointer to `Transform` structure.
		/// @param[in] _num Number of matrices.
		/// @returns Index into matrix cache.
		///
		/// @attention Pointer returned can be modifed until `bgfx::frame` is called.
		/// @attention C99 equivalent is `bgfx_encoder_alloc_transform`.
		///
		uint32_t allocTransform(
			  Transform* _transform
			, uint16_t _num
			);

		/// Set model matrix from matrix cache for draw primitive.
		///
		/// @param[in] _cache Index in matrix cache.
		/// @param[in] _num Number of matrices from cache.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transform_cached`.
		///
		void setTransform(
			  uint32_t _cache
			, uint16_t _num = 1
			);

		/// Set shader uniform parameter for draw primitive.
		///
		/// @param[in] _handle Uniform.
		/// @param[in] _value Pointer to uniform data.
		/// @param[in] _num Number of elements. Passing `UINT16_MAX` will
		///   use the _num passed on uniform creation.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_uniform`.
		///
		void setUniform(
			  UniformHandle _handle
			, const void* _value
			, uint16_t _num = 1
			);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _handle Index buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_index_buffer`.
		///
		void setIndexBuffer(IndexBufferHandle _handle);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _handle Index buffer.
		/// @param[in] _firstIndex First index to render.
		/// @param[in] _numIndices Number of indices to render.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_index_buffer`.
		///
		void setIndexBuffer(
			  IndexBufferHandle _handle
			, uint32_t _firstIndex
			, uint32_t _numIndices
			);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _handle Dynamic index buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_dynamic_index_buffer`.
		///
		void setIndexBuffer(DynamicIndexBufferHandle _handle);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _handle Dynamic index buffer.
		/// @param[in] _firstIndex First index to render.
		/// @param[in] _numIndices Number of indices to render.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_dynamic_index_buffer`.
		///
		void setIndexBuffer(
			  DynamicIndexBufferHandle _handle
			, uint32_t _firstIndex
			, uint32_t _numIndices
			);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _tib Transient index buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transient_index_buffer`.
		///
		void setIndexBuffer(const TransientIndexBuffer* _tib);

		/// Set index buffer for draw primitive.
		///
		/// @param[in] _tib Transient index buffer.
		/// @param[in] _firstIndex First index to render.
		/// @param[in] _numIndices Number of indices to render.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transient_index_buffer`.
		///
		void setIndexBuffer(
			  const TransientIndexBuffer* _tib
			, uint32_t _firstIndex
			, uint32_t _numIndices
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _handle Vertex buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, VertexBufferHandle _handle
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _handle Vertex buffer.
		/// @param[in] _startVertex First vertex to render.
		/// @param[in] _numVertices Number of vertices to render.
		/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
		///   used, vertex layout used for creation of vertex buffer will be used.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, VertexBufferHandle _handle
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _handle Dynamic vertex buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_dynamic_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, DynamicVertexBufferHandle _handle
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _handle Dynamic vertex buffer.
		/// @param[in] _startVertex First vertex to render.
		/// @param[in] _numVertices Number of vertices to render.
		/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
		///   used, vertex layout used for creation of vertex buffer will be used.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_dynamic_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, DynamicVertexBufferHandle _handle
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _tvb Transient vertex buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transient_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, const TransientVertexBuffer* _tvb
			);

		/// Set vertex buffer for draw primitive.
		///
		/// @param[in] _stream Vertex stream.
		/// @param[in] _tvb Transient vertex buffer.
		/// @param[in] _startVertex First vertex to render.
		/// @param[in] _numVertices Number of vertices to render.
		/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
		///   used, vertex layout used for creation of vertex buffer will be used.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_transient_vertex_buffer`.
		///
		void setVertexBuffer(
			  uint8_t _stream
			, const TransientVertexBuffer* _tvb
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
			);

		/// Set number of vertices for auto generated vertices use in conjuction
		/// with gl_VertexID.
		///
		/// @param[in] _numVertices Number of vertices.
		///
		/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		/// @attention C99 equivalent is `bgfx_encoder_set_vertex_count`.
		///
		void setVertexCount(uint32_t _numVertices);

		/// Set instance data buffer for draw primitive.
		///
		/// @param[in] _idb Transient instance data buffer.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_instance_data_buffer`.
		///
		void setInstanceDataBuffer(const InstanceDataBuffer* _idb);

		/// Set instance data buffer for draw primitive.
		///
		/// @param[in] _idb Transient instance data buffer.
		/// @param[in] _start First instance data.
		/// @param[in] _num Number of data instances.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_instance_data_buffer`.
		///
		void setInstanceDataBuffer(
			  const InstanceDataBuffer* _idb
			, uint32_t _start
			, uint32_t _num
			);

		/// Set instance data buffer for draw primitive.
		///
		/// @param[in] _handle Vertex buffer.
		/// @param[in] _start First instance data.
		/// @param[in] _num Number of data instances.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_instance_data_from_vertex_buffer`.
		///
		void setInstanceDataBuffer(
			  VertexBufferHandle _handle
			, uint32_t _start
			, uint32_t _num
			);

		/// Set instance data buffer for draw primitive.
		///
		/// @param[in] _handle Vertex buffer.
		/// @param[in] _start First instance data.
		/// @param[in] _num Number of data instances.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer`.
		///
		void setInstanceDataBuffer(
			  DynamicVertexBufferHandle _handle
			, uint32_t _start
			, uint32_t _num
			);

		/// Set number of instances for auto generated instances use in conjuction
		/// with gl_InstanceID.
		///
		/// @param[in] _numInstances Number of instances.
		///
		/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
		/// @attention C99 equivalent is `bgfx_encoder_set_instance_count`.
		///
		void setInstanceCount(uint32_t _numInstances);

		/// Set texture stage for draw primitive.
		///
		/// @param[in] _stage Texture unit.
		/// @param[in] _sampler Program sampler.
		/// @param[in] _handle Texture handle.
		/// @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
		///   texture sampling settings from the texture.
		///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
		///     mode.
		///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
		///     sampling.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_texture`.
		///
		void setTexture(
			  uint8_t _stage
			, UniformHandle _sampler
			, TextureHandle _handle
			, uint32_t _flags = UINT32_MAX
			);

		/// Submit an empty primitive for rendering. Uniforms and draw state
		/// will be applied but no geometry will be submitted. Useful in cases
		/// when no other draw/compute primitive is submitted to view, but it's
		/// desired to execute clear view.
		///
		/// These empty draw calls will sort before ordinary draw calls.
		///
		/// @param[in] _id View id.
		///
		/// @attention C99 equivalent is `bgfx_encoder_touch`.
		///
		void touch(ViewId _id);

		/// Submit primitive for rendering.
		///
		/// @param[in] _id View id.
		/// @param[in] _program Program.
		/// @param[in] _depth Depth for sorting.
		/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_submit`.
		///
		void submit(
			  ViewId _id
			, ProgramHandle _program
			, uint32_t _depth = 0
			, uint8_t _flags  = BGFX_DISCARD_ALL
			);

		/// Submit primitive with occlusion query for rendering.
		///
		/// @param[in] _id View id.
		/// @param[in] _program Program.
		/// @param[in] _occlusionQuery Occlusion query.
		/// @param[in] _depth Depth for sorting.
		/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_submit_occlusion_query`.
		///
		void submit(
			  ViewId _id
			, ProgramHandle _program
			, OcclusionQueryHandle _occlusionQuery
			, uint32_t _depth = 0
			, uint8_t _flags  = BGFX_DISCARD_ALL
			);

		/// Submit primitive for rendering with index and instance data info from
		/// indirect buffer.
		///
		/// @param[in] _id View id.
		/// @param[in] _program Program.
		/// @param[in] _indirectHandle Indirect buffer.
		/// @param[in] _start First element in indirect buffer.
		/// @param[in] _num Number of dispatches.
		/// @param[in] _depth Depth for sorting.
		/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_submit_indirect`.
		///
		void submit(
			  ViewId _id
			, ProgramHandle _program
			, IndirectBufferHandle _indirectHandle
			, uint16_t _start = 0
			, uint16_t _num = 1
			, uint32_t _depth = 0
			, uint8_t _flags = BGFX_DISCARD_ALL
			);

		/// Set compute index buffer.
		///
		/// @param[in] _stage Compute stage.
		/// @param[in] _handle Index buffer handle.
		/// @param[in] _access Buffer access. See `Access::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_compute_index_buffer`.
		///
		void setBuffer(
			  uint8_t _stage
			, IndexBufferHandle _handle
			, Access::Enum _access
			);

		/// Set compute vertex buffer.
		///
		/// @param[in] _stage Compute stage.
		/// @param[in] _handle Vertex buffer handle.
		/// @param[in] _access Buffer access. See `Access::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_compute_vertex_buffer`.
		///
		void setBuffer(
			  uint8_t _stage
			, VertexBufferHandle _handle
			, Access::Enum _access
			);

		/// Set compute dynamic index buffer.
		///
		/// @param[in] _stage Compute stage.
		/// @param[in] _handle Dynamic index buffer handle.
		/// @param[in] _access Buffer access. See `Access::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_compute_dynamic_index_buffer`.
		///
		void setBuffer(
			  uint8_t _stage
			, DynamicIndexBufferHandle _handle
			, Access::Enum _access
			);

		/// Set compute dynamic vertex buffer.
		///
		/// @param[in] _stage Compute stage.
		/// @param[in] _handle Dynamic vertex buffer handle.
		/// @param[in] _access Buffer access. See `Access::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_compute_dynamic_vertex_buffer`.
		///
		void setBuffer(
			  uint8_t _stage
			, DynamicVertexBufferHandle _handle
			, Access::Enum _access
			);

		/// Set compute indirect buffer.
		///
		/// @param[in] _stage Compute stage.
		/// @param[in] _handle Indirect buffer handle.
		/// @param[in] _access Buffer access. See `Access::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_compute_indirect_buffer`.
		///
		void setBuffer(
			  uint8_t _stage
			, IndirectBufferHandle _handle
			, Access::Enum _access
			);

		/// Set compute image from texture.
		///
		/// @param[in] _stage Texture unit.
		/// @param[in] _handle Texture handle.
		/// @param[in] _mip Mip level.
		/// @param[in] _access Texture access. See `Access::Enum`.
		/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_set_image`.
		///
		void setImage(
			  uint8_t _stage
			, TextureHandle _handle
			, uint8_t _mip
			, Access::Enum _access
			, TextureFormat::Enum _format = TextureFormat::Count
			);

		/// Dispatch compute.
		///
		/// @param[in] _id View id.
		/// @param[in] _handle Compute program.
		/// @param[in] _numX Number of groups X.
		/// @param[in] _numY Number of groups Y.
		/// @param[in] _numZ Number of groups Z.
		/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_dispatch`.
		///
		void dispatch(
			  ViewId _id
			, ProgramHandle _handle
			, uint32_t _numX = 1
			, uint32_t _numY = 1
			, uint32_t _numZ = 1
			, uint8_t _flags = BGFX_DISCARD_ALL
			);

		/// Dispatch compute indirect.
		///
		/// @param[in] _id View id.
		/// @param[in] _handle Compute program.
		/// @param[in] _indirectHandle Indirect buffer.
		/// @param[in] _start First element in indirect buffer.
		/// @param[in] _num Number of dispatches.
		/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
		///
		/// @attention C99 equivalent is `bgfx_encoder_dispatch_indirect`.
		///
		void dispatch(
			  ViewId _id
			, ProgramHandle _handle
			, IndirectBufferHandle _indirectHandle
			, uint16_t _start = 0
			, uint16_t _num   = 1
			, uint8_t _flags  = BGFX_DISCARD_ALL
			);

		/// Discard all previously set state for draw or compute call.
		///
		/// @param[in] _flags Draw/compute states to discard.
		///
		/// @attention C99 equivalent is `bgfx_encoder_discard`.
		///
		void discard(uint8_t _flags = BGFX_DISCARD_ALL);

		/// Blit texture 2D region between two 2D textures.
		///
		/// @param[in] _id View id.
		/// @param[in] _dst Destination texture handle.
		/// @param[in] _dstX Destination texture X position.
		/// @param[in] _dstY Destination texture Y position.
		/// @param[in] _src Source texture handle.
		/// @param[in] _srcX Source texture X position.
		/// @param[in] _srcY Source texture Y position.
		/// @param[in] _width Width of region.
		/// @param[in] _height Height of region.
		///
		/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		/// @attention C99 equivalent is `bgfx_encoder_blit`.
		///
		void blit(
			  ViewId _id
			, TextureHandle _dst
			, uint16_t _dstX
			, uint16_t _dstY
			, TextureHandle _src
			, uint16_t _srcX = 0
			, uint16_t _srcY = 0
			, uint16_t _width = UINT16_MAX
			, uint16_t _height = UINT16_MAX
			);

		/// Blit texture region between two textures.
		///
		/// @param[in] _id View id.
		/// @param[in] _dst Destination texture handle.
		/// @param[in] _dstMip Destination texture mip level.
		/// @param[in] _dstX Destination texture X position.
		/// @param[in] _dstY Destination texture Y position.
		/// @param[in] _dstZ If texture is 2D this argument should be 0. If destination texture is cube
		///   this argument represents destination texture cube face. For 3D texture this argument
		///   represents destination texture Z position.
		/// @param[in] _src Source texture handle.
		/// @param[in] _srcMip Source texture mip level.
		/// @param[in] _srcX Source texture X position.
		/// @param[in] _srcY Source texture Y position.
		/// @param[in] _srcZ If texture is 2D this argument should be 0. If source texture is cube
		///   this argument represents source texture cube face. For 3D texture this argument
		///   represents source texture Z position.
		/// @param[in] _width Width of region.
		/// @param[in] _height Height of region.
		/// @param[in] _depth If texture is 3D this argument represents depth of region, otherwise it's
		///   unused.
		///
		/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
		/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
		/// @attention C99 equivalent is `bgfx_encoder_blit`.
		///
		void blit(
			  ViewId _id
			, TextureHandle _dst
			, uint8_t _dstMip
			, uint16_t _dstX
			, uint16_t _dstY
			, uint16_t _dstZ
			, TextureHandle _src
			, uint8_t _srcMip = 0
			, uint16_t _srcX = 0
			, uint16_t _srcY = 0
			, uint16_t _srcZ = 0
			, uint16_t _width = UINT16_MAX
			, uint16_t _height = UINT16_MAX
			, uint16_t _depth = UINT16_MAX
			);
	};

	/// Vertex layout.
	///
	/// @attention C99 equivalent is `bgfx_vertex_layout_t`.
	///
	struct VertexLayout
	{
		VertexLayout();

		/// Start VertexLayout.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_begin`.
		///
		VertexLayout& begin(RendererType::Enum _renderer = RendererType::Noop);

		/// End VertexLayout.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_end`.
		///
		void end();

		/// Add attribute to VertexLayout.
		///
		/// @param[in] _attrib Attribute semantics. See: `bgfx::Attrib`
		/// @param[in] _num Number of elements 1, 2, 3 or 4.
		/// @param[in] _type Element type.
		/// @param[in] _normalized When using fixed point AttribType (f.e. Uint8)
		///   value will be normalized for vertex shader usage. When normalized
		///   is set to true, AttribType::Uint8 value in range 0-255 will be
		///   in range 0.0-1.0 in vertex shader.
		/// @param[in] _asInt Packaging rule for vertexPack, vertexUnpack, and
		///   vertexConvert for AttribType::Uint8 and AttribType::Int16.
		///   Unpacking code must be implemented inside vertex shader.
		///
		/// @remarks
		///   Must be called between begin/end.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_add`.
		///
		VertexLayout& add(
			  Attrib::Enum _attrib
			, uint8_t _num
			, AttribType::Enum _type
			, bool _normalized = false
			, bool _asInt = false
			);

		/// Skip _num bytes in vertex stream.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_skip`.
		///
		VertexLayout& skip(uint8_t _num);

		/// Decode attribute.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_decode`.
		///
		void decode(
			  Attrib::Enum _attrib
			, uint8_t& _num
			, AttribType::Enum& _type
			, bool& _normalized
			, bool& _asInt
			) const;

		/// Returns true if VertexLayout contains attribute.
		///
		/// @attention C99 equivalent is `bgfx_vertex_layout_has`.
		///
		bool has(Attrib::Enum _attrib) const { return UINT16_MAX != m_attributes[_attrib]; }

		/// Returns relative attribute offset from the vertex.
		uint16_t getOffset(Attrib::Enum _attrib) const { return m_offset[_attrib]; }

		/// Returns vertex stride.
		uint16_t getStride() const { return m_stride; }

		/// Returns size of vertex buffer for number of vertices.
		uint32_t getSize(uint32_t _num) const { return _num*m_stride; }

		uint32_t m_hash;
		uint16_t m_stride;
		uint16_t m_offset[Attrib::Count];
		uint16_t m_attributes[Attrib::Count];
	};

	/// Pack vertex attribute into vertex stream format.
	///
	/// @param[in] _input Value to be packed into vertex stream.
	/// @param[in] _inputNormalized True if input value is already normalized.
	/// @param[in] _attr Attribute to pack.
	/// @param[in] _layout Vertex stream layout.
	/// @param[in] _data Destination vertex stream where data will be packed.
	/// @param[in] _index Vertex index that will be modified.
	///
	/// @attention C99 equivalent is `bgfx_vertex_pack`.
	///
	void vertexPack(
		  const float _input[4]
		, bool _inputNormalized
		, Attrib::Enum _attr
		, const VertexLayout& _layout
		, void* _data
		, uint32_t _index = 0
		);

	/// Unpack vertex attribute from vertex stream format.
	///
	/// @param[out] _output Result of unpacking.
	/// @param[in]  _attr Attribute to unpack.
	/// @param[in]  _layout Vertex stream layout.
	/// @param[in]  _data Source vertex stream from where data will be unpacked.
	/// @param[in]  _index Vertex index that will be unpacked.
	///
	/// @attention C99 equivalent is `bgfx_vertex_unpack`.
	///
	void vertexUnpack(
		  float _output[4]
		, Attrib::Enum _attr
		, const VertexLayout& _layout
		, const void* _data
		, uint32_t _index = 0
		);

	/// Converts vertex stream data from one vertex stream format to another.
	///
	/// @param[in] _destLayout Destination vertex stream layout.
	/// @param[in] _destData Destination vertex stream.
	/// @param[in] _srcLayout Source vertex stream layout.
	/// @param[in] _srcData Source vertex stream data.
	/// @param[in] _num Number of vertices to convert from source to destination.
	///
	/// @attention C99 equivalent is `bgfx_vertex_convert`.
	///
	void vertexConvert(
		  const VertexLayout& _destLayout
		, void* _destData
		, const VertexLayout& _srcLayout
		, const void* _srcData
		, uint32_t _num = 1
		);

	/// Weld vertices.
	///
	/// @param[in] _output Welded vertices remapping table. The size of buffer
	///   must be the same as number of vertices.
	/// @param[in] _layout Vertex stream layout.
	/// @param[in] _data Vertex stream.
	/// @param[in] _num Number of vertices in vertex stream.
	/// @param[in] _index32 Set to `true` if input indices are 32-bit.
	/// @param[in] _epsilon Error tolerance for vertex position comparison.
	/// @returns Number of unique vertices after vertex welding.
	///
	/// @attention C99 equivalent is `bgfx_weld_vertices`.
	///
	uint32_t weldVertices(
		  void* _output
		, const VertexLayout& _layout
		, const void* _data
		, uint32_t _num
		, bool _index32
		, float _epsilon = 0.001f
		);

	/// Convert index buffer for use with different primitive topologies.
	///
	/// @param[in] _conversion Conversion type, see `TopologyConvert::Enum`.
	/// @param[in] _dst Destination index buffer. If this argument is NULL
	///    function will return number of indices after conversion.
	/// @param[in] _dstSize Destination index buffer in bytes. It must be
	///    large enough to contain output indices. If destination size is
	///    insufficient index buffer will be truncated.
	/// @param[in] _indices Source indices.
	/// @param[in] _numIndices Number of input indices.
	/// @param[in] _index32 Set to `true` if input indices are 32-bit.
	///
	/// @returns Number of output indices after conversion.
	///
	/// @attention C99 equivalent is `bgfx_topology_convert`.
	///
	uint32_t topologyConvert(
		  TopologyConvert::Enum _conversion
		, void* _dst
		, uint32_t _dstSize
		, const void* _indices
		, uint32_t _numIndices
		, bool _index32
		);

	/// Sort indices.
	///
	/// @param[in] _sort Sort order, see `TopologySort::Enum`.
	/// @param[in] _dst Destination index buffer.
	/// @param[in] _dstSize Destination index buffer in bytes. It must be
	///    large enough to contain output indices. If destination size is
	///    insufficient index buffer will be truncated.
	/// @param[in] _dir Direction (vector must be normalized).
	/// @param[in] _pos Position.
	/// @param[in] _vertices Pointer to first vertex represented as
	///    float x, y, z. Must contain at least number of vertices
	///    referencende by index buffer.
	/// @param[in] _stride Vertex stride.
	/// @param[in] _indices Source indices.
	/// @param[in] _numIndices Number of input indices.
	/// @param[in] _index32 Set to `true` if input indices are 32-bit.
	///
	/// @attention C99 equivalent is `bgfx_topology_sort_tri_list`.
	///
	void topologySortTriList(
		  TopologySort::Enum _sort
		, void* _dst
		, uint32_t _dstSize
		, const float _dir[3]
		, const float _pos[3]
		, const void* _vertices
		, uint32_t _stride
		, const void* _indices
		, uint32_t _numIndices
		, bool _index32
		);

	/// Returns supported backend API renderers.
	///
	/// @param[in] _max Maximum number of elements in _enum array.
	/// @param[inout] _enum Array where supported renderers will be written.
	///
	/// @returns Number of supported renderers.
	///
	/// @attention C99 equivalent is `bgfx_get_supported_renderers`.
	///
	uint8_t getSupportedRenderers(
		  uint8_t _max = 0
		, RendererType::Enum* _enum = NULL
		);

	/// Returns name of renderer.
	///
	/// @attention C99 equivalent is `bgfx_get_renderer_name`.
	///
	const char* getRendererName(RendererType::Enum _type);

	/// Initialize bgfx library.
	///
	/// @param[in] _init Initialization parameters. See: `bgfx::Init` for more info.
	///
	/// @returns `true` if initialization was successful.
	///
	/// @attention C99 equivalent is `bgfx_init`.
	///
	bool init(const Init& _init = {});

	/// Shutdown bgfx library.
	///
	/// @attention C99 equivalent is `bgfx_shutdown`.
	///
	void shutdown();

	/// Reset graphic settings and back-buffer size.
	///
	/// @param[in] _width Back-buffer width.
	/// @param[in] _height Back-buffer height.
	/// @param[in] _flags See: `BGFX_RESET_*` for more info.
	///   - `BGFX_RESET_NONE` - No reset flags.
	///   - `BGFX_RESET_FULLSCREEN` - Not supported yet.
	///   - `BGFX_RESET_MSAA_X[2/4/8/16]` - Enable 2, 4, 8 or 16 x MSAA.
	///   - `BGFX_RESET_VSYNC` - Enable V-Sync.
	///   - `BGFX_RESET_MAXANISOTROPY` - Turn on/off max anisotropy.
	///   - `BGFX_RESET_CAPTURE` - Begin screen capture.
	///   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
	///   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
	///     occurs. Default behavior is that flip occurs before rendering new
	///     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	///   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB backbuffer.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	///
	/// @attention This call doesn't actually change window size, it just
	///   resizes back-buffer. Windowing code has to change window size.
	///
	/// @attention C99 equivalent is `bgfx_reset`.
	///
	void reset(
		  uint32_t _width
		, uint32_t _height
		, uint32_t _flags = BGFX_RESET_NONE
		, TextureFormat::Enum _format = TextureFormat::Count
		);

	/// Begin submitting draw calls from thread.
	///
	/// @param[in] _forThread Explicitly request an encoder for a worker thread.
	///
	Encoder* begin(bool _forThread = false);

	/// End submitting draw calls from thread.
	///
	void end(Encoder* _encoder);

	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	///
	/// @param[in] _capture Capture frame with graphics debugger.
	///
	/// @returns Current frame number. This might be used in conjunction with
	///   double/multi buffering data outside the library and passing it to
	///   library via `bgfx::makeRef` calls.
	///
	/// @attention C99 equivalent is `bgfx_frame`.
	///
	uint32_t frame(bool _capture = false);

	/// Returns current renderer backend API type.
	///
	/// @remarks
	///   Library must be initialized.
	///
	/// @attention C99 equivalent is `bgfx_get_renderer_type`.
	///
	RendererType::Enum getRendererType();

	/// Returns renderer capabilities.
	///
	/// @returns Pointer to static `bgfx::Caps` structure.
	///
	/// @remarks
	///   Library must be initialized.
	///
	/// @attention C99 equivalent is `bgfx_get_caps`.
	///
	const Caps* getCaps();

	/// Returns performance counters.
	///
	/// @attention Pointer returned is valid until `bgfx::frame` is called.
	/// @attention C99 equivalent is `bgfx_get_stats`.
	///
	const Stats* getStats();

	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	///
	/// @param[in] _size Size to allocate.
	///
	/// @attention C99 equivalent is `bgfx_alloc`.
	///
	const Memory* alloc(uint32_t _size);

	/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
	///
	/// @param[in] _data Pointer to data to be copied.
	/// @param[in] _size Size of data to be copied.
	///
	/// @attention C99 equivalent is `bgfx_copy`.
	///
	const Memory* copy(
		  const void* _data
		, uint32_t _size
		);

	/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc`, this call
	/// doesn't allocate memory for data. It just copies the _data pointer. You
	/// can pass `ReleaseFn` function pointer to release this memory after it's
	/// consumed, otherwise you must make sure _data is available for at least 2
	/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	/// from any thread.
	///
	/// @param[in] _data Pointer to data.
	/// @param[in] _size Size of data.
	/// @param[in] _releaseFn Callback function to release memory after use.
	/// @param[in] _userData User data to be passed to callback function.
	///
	/// @attention Data passed must be available for at least 2 `bgfx::frame` calls.
	/// @attention C99 equivalent are `bgfx_make_ref`, `bgfx_make_ref_release`.
	///
	const Memory* makeRef(
		  const void* _data
		, uint32_t _size
		, ReleaseFn _releaseFn = NULL
		, void* _userData = NULL
		);

	/// Set debug flags.
	///
	/// @param[in] _debug Available flags:
	///   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
	///     all rendering calls will be skipped. This is useful when profiling
	///     to quickly assess potential bottlenecks between CPU and GPU.
	///   - `BGFX_DEBUG_PROFILER` - Enable profiler.
	///   - `BGFX_DEBUG_STATS` - Display internal statistics.
	///   - `BGFX_DEBUG_TEXT` - Display debug text.
	///   - `BGFX_DEBUG_WIREFRAME` - Wireframe rendering. All rendering
	///     primitives will be rendered as lines.
	///
	/// @attention C99 equivalent is `bgfx_set_debug`.
	///
	void setDebug(uint32_t _debug);

	/// Clear internal debug text buffer.
	///
	/// @param[in] _attr Background color.
	/// @param[in] _small Default 8x16 or 8x8 font.
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_clear`.
	///
	void dbgTextClear(
		  uint8_t _attr = 0
		, bool _small = false
		);

	/// Print into internal debug text character-buffer (VGA-compatible text mode).
	///
	/// @param[in] _x, _y 2D position from top-left.
	/// @param[in] _attr Color palette. Where top 4-bits represent index of background, and bottom
	///   4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	/// @param[in] _format `printf` style format.
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_printf`.
	///
	void dbgTextPrintf(
		  uint16_t _x
		, uint16_t _y
		, uint8_t _attr
		, const char* _format
		, ...
		);

	/// Print into internal debug text character-buffer (VGA-compatible text mode).
	///
	/// @param[in] _x, _y 2D position from top-left.
	/// @param[in] _attr Color palette. Where top 4-bits represent index of background, and bottom
	///   4-bits represent foreground color from standard VGA text palette (ANSI escape codes).
	/// @param[in] _format `printf` style format.
	/// @param[in] _argList additional arguments for format string
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_vprintf`.
	///
	void dbgTextPrintfVargs(
		  uint16_t _x
		, uint16_t _y
		, uint8_t _attr
		, const char* _format
		, va_list _argList
		);

	/// Draw image into internal debug text buffer.
	///
	/// @param[in] _x, _y 2D position from top-left.
	/// @param[in] _width, _height  Image width and height.
	/// @param[in] _data  Raw image data (character/attribute raw encoding).
	/// @param[in] _pitch Image pitch in bytes.
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_image`.
	///
	void dbgTextImage(
		  uint16_t _x
		, uint16_t _y
		, uint16_t _width
		, uint16_t _height
		, const void* _data
		, uint16_t _pitch
		);

	/// Create static index buffer.
	///
	/// @param[in] _mem Index buffer data.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_index_buffer`.
	///
	IndexBufferHandle createIndexBuffer(
		  const Memory* _mem
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Set static index buffer debug name.
	///
	/// @param[in] _handle Static index buffer handle.
	/// @param[in] _name Static index buffer name.
	/// @param[in] _len Static index buffer name length (if length is INT32_MAX, it's expected
	///   that _name is zero terminated string.
	///
	/// @attention C99 equivalent is `bgfx_set_index_buffer_name`.
	///
	void setName(
		  IndexBufferHandle _handle
		, const char* _name
		, int32_t _len = INT32_MAX
		);

	/// Destroy static index buffer.
	///
	/// @param[in] _handle Static index buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_index_buffer`.
	///
	void destroy(IndexBufferHandle _handle);

	/// Create vertex layout.
	///
	/// @attention C99 equivalent is `bgfx_create_vertex_layout`.
	///
	VertexLayoutHandle createVertexLayout(const VertexLayout& _layout);

	/// Destroy vertex layout.
	///
	/// @attention C99 equivalent is `bgfx_destroy_vertex_layout`.
	///
	void destroy(VertexLayoutHandle _handle);

	/// Create static vertex buffer.
	///
	/// @param[in] _mem Vertex buffer data.
	/// @param[in] _layout Vertex layout.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Static vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_vertex_buffer`.
	///
	VertexBufferHandle createVertexBuffer(
		  const Memory* _mem
		, const VertexLayout& _layout
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Set static vertex buffer debug name.
	///
	/// @param[in] _handle Static vertex buffer handle.
	/// @param[in] _name Static vertex buffer name.
	/// @param[in] _len Static vertex buffer name length (if length is INT32_MAX, it's expected
	///   that _name is zero terminated string.
	///
	/// @attention C99 equivalent is `bgfx_set_vertex_buffer_name`.
	///
	void setName(
		  VertexBufferHandle _handle
		, const char* _name
		, int32_t _len = INT32_MAX
		);

	/// Destroy static vertex buffer.
	///
	/// @param[in] _handle Static vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_vertex_buffer`.
	///
	void destroy(VertexBufferHandle _handle);

	/// Create empty dynamic index buffer.
	///
	/// @param[in] _num Number of indices.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Dynamic index buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_index_buffer`.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(
		  uint32_t _num
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Create dynamic index buffer and initialized it.
	///
	/// @param[in] _mem Index buffer data.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Dynamic index buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_index_buffer_mem`.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(
		  const Memory* _mem
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Update dynamic index buffer.
	///
	/// @param[in] _handle Dynamic index buffer handle.
	/// @param[in] _startIndex Start index.
	/// @param[in] _mem Index buffer data.
	///
	/// @attention C99 equivalent is `bgfx_update_dynamic_index_buffer`.
	///
	void update(
		  DynamicIndexBufferHandle _handle
		, uint32_t _startIndex
		, const Memory* _mem
		);

	/// Destroy dynamic index buffer.
	///
	/// @param[in] _handle Dynamic index buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_dynamic_index_buffer`.
	///
	void destroy(DynamicIndexBufferHandle _handle);

	/// Create empty dynamic vertex buffer.
	///
	/// @param[in] _num Number of vertices.
	/// @param[in] _layout Vertex layout.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Dynamic vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_vertex_buffer`.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(
		  uint32_t _num
		, const VertexLayout& _layout
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Create dynamic vertex buffer and initialize it.
	///
	/// @param[in] _mem Vertex buffer data.
	/// @param[in] _layout Vertex layout.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if a different amount of
	///       data is passed. If this flag is not specified, and more data is passed on update, the buffer
	///       will be trimmed to fit the existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Dynamic vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_vertex_buffer_mem`.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(
		  const Memory* _mem
		, const VertexLayout& _layout
		, uint16_t _flags = BGFX_BUFFER_NONE
		);

	/// Update dynamic vertex buffer.
	///
	/// @param[in] _handle Dynamic vertex buffer handle.
	/// @param[in] _startVertex Start vertex.
	/// @param[in] _mem Vertex buffer data.
	///
	/// @attention C99 equivalent is `bgfx_update_dynamic_vertex_buffer`.
	///
	void update(
		  DynamicVertexBufferHandle _handle
		, uint32_t _startVertex
		, const Memory* _mem
		);

	/// Destroy dynamic vertex buffer.
	///
	/// @param[in] _handle Dynamic vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_dynamic_vertex_buffer`.
	///
	void destroy(DynamicVertexBufferHandle _handle);

	/// Returns number of requested or maximum available indices.
	///
	/// @param[in] _num Number of required indices.
	///
	/// @attention C99 equivalent is `bgfx_get_avail_transient_index_buffer`.
	///
	uint32_t getAvailTransientIndexBuffer(uint32_t _num);

	/// Returns number of requested or maximum available vertices.
	///
	/// @param[in] _num Number of required vertices.
	/// @param[in] _layout Vertex layout.
	///
	/// @attention C99 equivalent is `bgfx_get_avail_transient_vertex_buffer`.
	///
	uint32_t getAvailTransientVertexBuffer(
		  uint32_t _num
		, const VertexLayout& _layout
		);

	/// Returns number of requested or maximum available instance buffer slots.
	///
	/// @param[in] _num Number of required instances.
	/// @param[in] _stride Stride per instance.
	///
	/// @attention C99 equivalent is `bgfx_get_avail_instance_data_buffer`.
	///
	uint32_t getAvailInstanceDataBuffer(
		  uint32_t _num
		, uint16_t _stride
		);

	/// Allocate transient index buffer.
	///
	/// @param[out] _tib TransientIndexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param[in] _num Number of indices to allocate.
	/// @param[in] _index32 Set to `true` if input indices will be 32-bit.
	///
	/// @remarks
	///   Only 16-bit index buffer is supported.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_index_buffer`.
	///
	void allocTransientIndexBuffer(
		  TransientIndexBuffer* _tib
		, uint32_t _num
		, bool _index32 = false
		);

	/// Allocate transient vertex buffer.
	///
	/// @param[out] _tvb TransientVertexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param[in] _num Number of vertices to allocate.
	/// @param[in] _layout Vertex layout.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_vertex_buffer`.
	///
	void allocTransientVertexBuffer(
		  TransientVertexBuffer* _tvb
		, uint32_t _num
		, const VertexLayout& _layout
		);

	/// Check for required space and allocate transient vertex and index
	/// buffers. If both space requirements are satisfied function returns
	/// true.
	///
	/// @remarks
	///   Only 16-bit index buffer is supported.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_buffers`.
	///
	bool allocTransientBuffers(
		  TransientVertexBuffer* _tvb
		, const VertexLayout& _layout
		, uint32_t _numVertices
		, TransientIndexBuffer* _tib
		, uint32_t _numIndices
		);

	/// Allocate instance data buffer.
	///
	/// @param[out] _idb InstanceDataBuffer structure is filled and is valid
	///   for duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param[in] _num Number of instances.
	/// @param[in] _stride Instance stride. Must be multiple of 16.
	///
	/// @attention C99 equivalent is `bgfx_alloc_instance_data_buffer`.
	///
	void allocInstanceDataBuffer(
		  InstanceDataBuffer* _idb
		, uint32_t _num
		, uint16_t _stride
		);

	/// Create draw indirect buffer.
	///
	/// @param[in] _num Number of indirect calls.
	/// @returns Indirect buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_indirect_buffer`.
	///
	IndirectBufferHandle createIndirectBuffer(uint32_t _num);

	/// Destroy draw indirect buffer.
	///
	/// @param[in] _handle Indirect buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_indirect_buffer`.
	///
	void destroy(IndirectBufferHandle _handle);

	/// Create shader from memory buffer.
	///
	/// @attention C99 equivalent is `bgfx_create_shader`.
	///
	ShaderHandle createShader(const Memory* _mem);

	/// Returns the number of uniforms and uniform handles used inside a shader.
	///
	/// @param[in] _handle Shader handle.
	/// @param[in] _uniforms UniformHandle array where data will be stored.
	/// @param[in] _max Maximum capacity of array.
	/// @returns Number of uniforms used by shader.
	///
	/// @remarks
	///   Only non-predefined uniforms are returned.
	///
	/// @attention C99 equivalent is `bgfx_get_shader_uniforms`.
	///
	uint16_t getShaderUniforms(
		  ShaderHandle _handle
		, UniformHandle* _uniforms = NULL
		, uint16_t _max = 0
		);

	/// Set shader debug name.
	///
	/// @param[in] _handle Shader handle.
	/// @param[in] _name Shader name.
	/// @param[in] _len Shader name length (if length is INT32_MAX, it's expected
	///   that _name is zero terminated string.
	///
	/// @attention C99 equivalent is `bgfx_set_shader_name`.
	///
	void setName(
		  ShaderHandle _handle
		, const char* _name
		, int32_t _len = INT32_MAX
		);

	/// Destroy shader. Once a shader program is created with _handle,
	/// it is safe to destroy that shader.
	///
	/// @param[in] _handle Shader handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_shader`.
	///
	void destroy(ShaderHandle _handle);

	/// Create program with vertex and fragment shaders.
	///
	/// @param[in] _vsh Vertex shader.
	/// @param[in] _fsh Fragment shader.
	/// @param[in] _destroyShaders If true, shaders will be destroyed when
	///   program is destroyed.
	/// @returns Program handle if vertex shader output and fragment shader
	///   input are matching, otherwise returns invalid program handle.
	///
	/// @attention C99 equivalent is `bgfx_create_program`.
	///
	ProgramHandle createProgram(
		  ShaderHandle _vsh
		, ShaderHandle _fsh
		, bool _destroyShaders = false
		);

	/// Create program with compute shader.
	///
	/// @param[in] _csh Compute shader.
	/// @param[in] _destroyShader If true, shader will be destroyed when
	///   program is destroyed.
	/// @returns Program handle.
	///
	/// @attention C99 equivalent is `bgfx_create_compute_program`.
	///
	ProgramHandle createProgram(
		  ShaderHandle _csh
		, bool _destroyShader = false
		);

	/// Destroy program.
	///
	/// @param[in] _handle Program handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_program`.
	///
	void destroy(ProgramHandle _handle);

	/// Validate texture parameters.
	///
	/// @param[in] _depth Depth dimension of volume texture.
	/// @param[in] _cubeMap Indicates that texture contains cubemap.
	/// @param[in] _numLayers Number of layers in texture array.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Texture flags. See `BGFX_TEXTURE_*`.
	/// @returns True if texture can be successfully created.
	///
	/// @attention C99 equivalent is `bgfx_is_texture_valid`.
	///
	bool isTextureValid(
		  uint16_t _depth
		, bool _cubeMap
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		, uint64_t _flags
		);

	/// Calculate amount of memory required for texture.
	///
	/// @param[out] _info Resulting texture info structure. See: `TextureInfo`.
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _depth Depth dimension of volume texture.
	/// @param[in] _cubeMap Indicates that texture contains cubemap.
	/// @param[in] _hasMips Indicates that texture contains full mip-map chain.
	/// @param[in] _numLayers Number of layers in texture array.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_calc_texture_size`.
	///
	void calcTextureSize(
		  TextureInfo& _info
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, bool _cubeMap
		, bool _hasMips
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		);

	/// Create texture from memory buffer.
	///
	/// @param[in] _mem DDS, KTX or PVR texture data.
	/// @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	///   flags. Default texture sampling mode is linear, and wrap mode is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _skip Skip top level mips when parsing texture.
	/// @param[out] _info When non-`NULL` is specified it returns parsed texture information.
	/// @returns Texture handle.
	///
	/// @attention C99 equivalent is `bgfx_create_texture`.
	///
	TextureHandle createTexture(
		  const Memory* _mem
		, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE
		, uint8_t _skip = 0
		, TextureInfo* _info = NULL
		);

	/// Create 2D texture.
	///
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _hasMips Indicates that texture contains full mip-map chain.
	/// @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
	///   `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	///   flags. Default texture sampling mode is linear, and wrap mode is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	///   `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
	///   1, expected memory layout is texture and all mips together for each array element.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_2d`.
	///
	TextureHandle createTexture2D(
		  uint16_t _width
		, uint16_t _height
		, bool     _hasMips
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE
		, const Memory* _mem = NULL
		);

	/// Create texture with size based on backbuffer ratio. Texture will maintain ratio
	/// if back buffer resolution changes.
	///
	/// @param[in] _ratio Frame buffer size in respect to back-buffer size. See:
	///   `BackbufferRatio::Enum`.
	/// @param[in] _hasMips Indicates that texture contains full mip-map chain.
	/// @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
	///   `BGFX_CAPS_TEXTURE_2D_ARRAY` flag is not set.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	///   flags. Default texture sampling mode is linear, and wrap mode is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_2d_scaled`.
	///
	TextureHandle createTexture2D(
		  BackbufferRatio::Enum _ratio
		, bool _hasMips
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE
		);

	/// Create 3D texture.
	///
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _depth Depth.
	/// @param[in] _hasMips Indicates that texture contains full mip-map chain.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	///   flags. Default texture sampling mode is linear, and wrap mode is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	///   `_mem` is NULL content of the texture is uninitialized.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_3d`.
	///
	TextureHandle createTexture3D(
		  uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, bool _hasMips
		, TextureFormat::Enum _format
		, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE
		, const Memory* _mem = NULL
		);

	/// Create Cube texture.
	///
	/// @param[in] _size Cube side size.
	/// @param[in] _hasMips Indicates that texture contains full mip-map chain.
	/// @param[in] _numLayers Number of layers in texture array. Must be 1 if caps
	///   `BGFX_CAPS_TEXTURE_CUBE_ARRAY` flag is not set.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Texture creation (see `BGFX_TEXTURE_*`.), and sampler (see `BGFX_SAMPLER_*`)
	///   flags. Default texture sampling mode is linear, and wrap mode is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable. If
	///   `_mem` is NULL content of the texture is uninitialized. When `_numLayers` is more than
	///   1, expected memory layout is texture and all mips together for each array element.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_cube`.
	///
	TextureHandle createTextureCube(
		  uint16_t _size
		, bool _hasMips
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE
		, const Memory* _mem = NULL
		);

	/// Update 2D texture.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _layer Layers in texture array.
	/// @param[in] _mip Mip level.
	/// @param[in] _x X offset in texture.
	/// @param[in] _y Y offset in texture.
	/// @param[in] _width Width of texture block.
	/// @param[in] _height Height of texture block.
	/// @param[in] _mem Texture update data.
	/// @param[in] _pitch Pitch of input image (bytes). When _pitch is set to
	///   UINT16_MAX, it will be calculated internally based on _width.
	///
	/// @attention It's valid to update only mutable texture. See `bgfx::createTexture2D` for more info.
	///
	/// @attention C99 equivalent is `bgfx_update_texture_2d`.
	///
	void updateTexture2D(
		  TextureHandle _handle
		, uint16_t _layer
		, uint8_t _mip
		, uint16_t _x
		, uint16_t _y
		, uint16_t _width
		, uint16_t _height
		, const Memory* _mem
		, uint16_t _pitch = UINT16_MAX
		);

	/// Update 3D texture.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _mip Mip level.
	/// @param[in] _x X offset in texture.
	/// @param[in] _y Y offset in texture.
	/// @param[in] _z Z offset in texture.
	/// @param[in] _width Width of texture block.
	/// @param[in] _height Height of texture block.
	/// @param[in] _depth Depth of texture block.
	/// @param[in] _mem Texture update data.
	///
	/// @attention It's valid to update only mutable texture. See `bgfx::createTexture3D` for more info.
	///
	/// @attention C99 equivalent is `bgfx_update_texture_3d`.
	///
	void updateTexture3D(
		  TextureHandle _handle
		, uint8_t _mip
		, uint16_t _x
		, uint16_t _y
		, uint16_t _z
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, const Memory* _mem
		);

	/// Update Cube texture.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _layer Layers in texture array.
	/// @param[in] _side Cubemap side `BGFX_CUBE_MAP_<POSITIVE or NEGATIVE>_<X, Y or Z>`,
	///   where 0 is +X, 1 is -X, 2 is +Y, 3 is -Y, 4 is +Z, and 5 is -Z.
	///
	///                  +----------+
	///                  |-z       2|
	///                  | ^  +y    |
	///                  | |        |    Unfolded cube:
	///                  | +---->+x |
	///       +----------+----------+----------+----------+
	///       |+y       1|+y       4|+y       0|+y       5|
	///       | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
	///       | |        | |        | |        | |        |
	///       | +---->+z | +---->+x | +---->-z | +---->-x |
	///       +----------+----------+----------+----------+
	///                  |+z       3|
	///                  | ^  -y    |
	///                  | |        |
	///                  | +---->+x |
	///                  +----------+
	///
	/// @param[in] _mip Mip level.
	/// @param[in] _x X offset in texture.
	/// @param[in] _y Y offset in texture.
	/// @param[in] _width Width of texture block.
	/// @param[in] _height Height of texture block.
	/// @param[in] _mem Texture update data.
	/// @param[in] _pitch Pitch of input image (bytes). When _pitch is set to
	///   UINT16_MAX, it will be calculated internally based on _width.
	///
	/// @attention It's valid to update only mutable texture. See `bgfx::createTextureCube` for more info.
	///
	/// @attention C99 equivalent is `bgfx_update_texture_cube`.
	///
	void updateTextureCube(
		  TextureHandle _handle
		, uint16_t _layer
		, uint8_t _side
		, uint8_t _mip
		, uint16_t _x
		, uint16_t _y
		, uint16_t _width
		, uint16_t _height
		, const Memory* _mem
		, uint16_t _pitch = UINT16_MAX
		);

	/// Read back texture content.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _data Destination buffer.
	/// @param[in] _mip Mip level.
	///
	/// @returns Frame number when the result will be available. See: `bgfx::frame`.
	///
	/// @attention Texture must be created with `BGFX_TEXTURE_READ_BACK` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_READ_BACK`.
	/// @attention C99 equivalent is `bgfx_read_texture`.
	///
	uint32_t readTexture(
		  TextureHandle _handle
		, void* _data
		, uint8_t _mip = 0
		);

	/// Set texture debug name.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _name Texture name.
	/// @param[in] _len Texture name length (if length is INT32_MAX, it's expected
	///   that _name is zero terminated string.
	///
	/// @attention C99 equivalent is `bgfx_set_texture_name`.
	///
	void setName(
		  TextureHandle _handle
		, const char* _name
		, int32_t _len = INT32_MAX
		);

	/// Returns texture direct access pointer.
	///
	/// @param[in] _handle Texture handle.
	///
	/// @returns Pointer to texture memory. If returned pointer is `NULL` direct access
	///   is not available for this texture. If pointer is `UINTPTR_MAX` sentinel value
	///   it means texture is pending creation. Pointer returned can be cached and it
	///   will be valid until texture is destroyed.
	///
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_DIRECT_ACCESS`. This feature
	///   is available on GPUs that have unified memory architecture (UMA) support.
	///
	/// @attention C99 equivalent is `bgfx_get_direct_access_ptr`.
	///
	void* getDirectAccessPtr(TextureHandle _handle);

	/// Destroy texture.
	///
	/// @param[in] _handle Texture handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_texture`.
	///
	void destroy(TextureHandle _handle);

	/// Create frame buffer (simple).
	///
	/// @param[in] _width Texture width.
	/// @param[in] _height Texture height.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _textureFlags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer`.
	///
	FrameBufferHandle createFrameBuffer(
		  uint16_t _width
		, uint16_t _height
		, TextureFormat::Enum _format
		, uint64_t _textureFlags = BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP
		);

	/// Create frame buffer with size based on backbuffer ratio. Frame buffer will maintain ratio
	/// if back buffer resolution changes.
	///
	/// @param[in] _ratio Frame buffer size in respect to back-buffer size. See:
	///   `BackbufferRatio::Enum`.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _textureFlags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_scaled`.
	///
	FrameBufferHandle createFrameBuffer(
		  BackbufferRatio::Enum _ratio
		, TextureFormat::Enum _format
		, uint64_t _textureFlags = BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP
		);

	/// Create MRT frame buffer from texture handles (simple).
	///
	/// @param[in] _num Number of texture attachments.
	/// @param[in] _handles Texture attachments.
	/// @param[in] _destroyTextures If true, textures will be destroyed when
	///   frame buffer is destroyed.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_from_handles`.
	///
	FrameBufferHandle createFrameBuffer(
		  uint8_t _num
		, const TextureHandle* _handles
		, bool _destroyTextures = false
		);

	/// Create MRT frame buffer from texture handles with specific layer and
	/// mip level.
	///
	/// @param[in] _num Number of texture attachments.
	/// @param[in] _attachment Attachment texture info. See: `bgfx::Attachment`.
	/// @param[in] _destroyTextures If true, textures will be destroyed when
	///   frame buffer is destroyed.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_from_attachment`.
	///
	FrameBufferHandle createFrameBuffer(
		  uint8_t _num
		, const Attachment* _attachment
		, bool _destroyTextures = false
		);

	/// Create frame buffer for multiple window rendering.
	///
	/// @param[in] _nwh OS' target native window handle.
	/// @param[in] _width Window back buffer width.
	/// @param[in] _height Window back buffer height.
	/// @param[in] _format Window back buffer color format.
	/// @param[in] _depthFormat Window back buffer depth format.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @remarks
	///   Frame buffer cannot be used for sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_from_nwh`.
	///
	FrameBufferHandle createFrameBuffer(
		  void* _nwh
		, uint16_t _width
		, uint16_t _height
		, TextureFormat::Enum _format      = TextureFormat::Count
		, TextureFormat::Enum _depthFormat = TextureFormat::Count
		);

	/// Set frame buffer debug name.
	///
	/// @param[in] _handle frame buffer handle.
	/// @param[in] _name frame buffer name.
	/// @param[in] _len frame buffer name length (if length is INT32_MAX, it's expected
	///   that _name is zero terminated string.
	///
	/// @attention C99 equivalent is `bgfx_set_frame_buffer_name`.
	///
	void setName(
		  FrameBufferHandle _handle
		, const char* _name
		, int32_t _len = INT32_MAX
		);

	/// Obtain texture handle of frame buffer attachment.
	///
	/// @param[in] _handle Frame buffer handle.
	/// @param[in] _attachment Frame buffer attachment index.
	///
	/// @returns Returns invalid texture handle if attachment index is not
	///   correct, or frame buffer is created with native window handle.
	///
	/// @attention C99 equivalent is `bgfx_get_texture`.
	///
	TextureHandle getTexture(
		  FrameBufferHandle _handle
		, uint8_t _attachment = 0
		);

	/// Destroy frame buffer.
	///
	/// @param[in] _handle Frame buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_frame_buffer`.
	///
	void destroy(FrameBufferHandle _handle);

	/// Create shader uniform parameter.
	///
	/// @param[in] _name Uniform name in shader.
	/// @param[in] _type Type of uniform (See: `bgfx::UniformType`).
	/// @param[in] _num Number of elements in array.
	///
	/// @returns Handle to uniform object.
	///
	/// @remarks
	///   1. Uniform names are unique. It's valid to call `bgfx::createUniform`
	///      multiple times with the same uniform name. The library will always
	///      return the same handle, but the handle reference count will be
	///      incremented. This means that the same number of `bgfx::destroyUniform`
	///      must be called to properly destroy the uniform.
	///
	///   2. Predefined uniforms (declared in `bgfx_shader.sh`):
	///      - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
	///        view, in pixels.
	///      - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
	///        width and height
	///      - `u_view mat4` - view matrix
	///      - `u_invView mat4` - inverted view matrix
	///      - `u_proj mat4` - projection matrix
	///      - `u_invProj mat4` - inverted projection matrix
	///      - `u_viewProj mat4` - concatenated view projection matrix
	///      - `u_invViewProj mat4` - concatenated inverted view projection matrix
	///      - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
	///      - `u_modelView mat4` - concatenated model view matrix, only first
	///        model matrix from array is used.
	///      - `u_modelViewProj mat4` - concatenated model view projection matrix.
	///      - `u_alphaRef float` - alpha reference value for alpha test.
	///
	/// @attention C99 equivalent is `bgfx_create_uniform`.
	///
	UniformHandle createUniform(
		  const char* _name
		, UniformType::Enum _type
		, uint16_t _num = 1
		);

	/// Retrieve uniform info.
	///
	/// @param[in] _handle Handle to uniform object.
	/// @param[out] _info Uniform info.
	///
	/// @attention C99 equivalent is `bgfx_get_uniform_info`.
	///
	void getUniformInfo(
		  UniformHandle _handle
		, UniformInfo& _info
		);

	/// Destroy shader uniform parameter.
	///
	/// @param[in] _handle Handle to uniform object.
	///
	/// @attention C99 equivalent is `bgfx_destroy_uniform`.
	///
	void destroy(UniformHandle _handle);

	/// Create occlusion query.
	///
	/// @returns Handle to occlusion query object.
	///
	/// @attention C99 equivalent is `bgfx_create_occlusion_query`.
	///
	OcclusionQueryHandle createOcclusionQuery();

	/// Retrieve occlusion query result from previous frame.
	///
	/// @param[in] _handle Handle to occlusion query object.
	/// @param[out] _result Number of pixels that passed test. This argument
	///   can be `NULL` if result of occlusion query is not needed.
	/// @returns Occlusion query result.
	///
	/// @attention C99 equivalent is `bgfx_get_result`.
	///
	OcclusionQueryResult::Enum getResult(
		  OcclusionQueryHandle _handle
		, int32_t* _result = NULL
		);

	/// Destroy occlusion query.
	///
	/// @param[in] _handle Handle to occlusion query object.
	///
	/// @attention C99 equivalent is `bgfx_destroy_occlusion_query`.
	///
	void destroy(OcclusionQueryHandle _handle);

	/// Set palette color value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _rgba Packed 32-bit RGBA value.
	///
	/// @attention C99 equivalent is `bgfx_set_palette_color`.
	///
	void setPaletteColor(
		  uint8_t _index
		, uint32_t _rgba
		);

	/// Set palette color value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _r, _g, _b, _a RGBA floating point values.
	///
	/// @attention C99 equivalent is `bgfx_set_palette_color`.
	///
	void setPaletteColor(
		  uint8_t _index
		, float _r
		, float _g
		, float _b
		, float _a
		);

	/// Set palette color value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _rgba RGBA floating point value.
	///
	/// @attention C99 equivalent is `bgfx_set_palette_color`.
	///
	void setPaletteColor(
		  uint8_t _index
		, const float _rgba[4]
		);

	/// Set view name.
	///
	/// @param[in] _id View id.
	/// @param[in] _name View name.
	///
	/// @remarks
	///   This is debug only feature.
	///
	///   In graphics debugger view name will appear as:
	///
	///       "nnnce <view name>"
	///        ^  ^^ ^
	///        |  |+-- eye (L/R)
	///        |  +--- compute (C)
	///        +------ view id
	///
	/// @attention C99 equivalent is `bgfx_set_view_name`.
	///
	void setViewName(
		  ViewId _id
		, const char* _name
		);

	/// Set view rectangle. Draw primitive outside view will be clipped.
	///
	/// @param[in] _id View id.
	/// @param[in] _x Position x from the left corner of the window.
	/// @param[in] _y Position y from the top corner of the window.
	/// @param[in] _width Width of view port region.
	/// @param[in] _height Height of view port region.
	///
	/// @attention C99 equivalent is `bgfx_set_view_rect`.
	///
	void setViewRect(
		  ViewId _id
		, uint16_t _x
		, uint16_t _y
		, uint16_t _width
		, uint16_t _height
		);

	/// Set view rectangle. Draw primitive outside view will be clipped.
	///
	/// @param[in] _id View id.
	/// @param[in] _x Position x from the left corner of the window.
	/// @param[in] _y Position y from the top corner of the window.
	/// @param[in] _ratio Width and height will be set in respect to back-buffer size. See:
	///   `BackbufferRatio::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_view_rect_ratio`.
	///
	void setViewRect(
		  ViewId _id
		, uint16_t _x
		, uint16_t _y
		, BackbufferRatio::Enum _ratio
		);

	/// Set view scissor. Draw primitive outside view will be clipped. When
	/// _x, _y, _width and _height are set to 0, scissor will be disabled.
	///
	/// @param[in] _id View id.
	/// @param[in] _x Position x from the left corner of the window.
	/// @param[in] _y Position y from the top corner of the window.
	/// @param[in] _width Width of scissor region.
	/// @param[in] _height Height of scissor region.
	///
	/// @attention C99 equivalent is `bgfx_set_view_scissor`.
	///
	void setViewScissor(
		  ViewId _id
		, uint16_t _x = 0
		, uint16_t _y = 0
		, uint16_t _width = 0
		, uint16_t _height = 0
		);

	/// Set view clear flags.
	///
	/// @param[in] _id View id.
	/// @param[in] _flags Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
	///   operation. See: `BGFX_CLEAR_*`.
	/// @param[in] _rgba Color clear value.
	/// @param[in] _depth Depth clear value.
	/// @param[in] _stencil Stencil clear value.
	///
	/// @attention C99 equivalent is `bgfx_set_view_clear`.
	///
	void setViewClear(
		  ViewId _id
		, uint16_t _flags
		, uint32_t _rgba = 0x000000ff
		, float _depth = 1.0f
		, uint8_t _stencil = 0
		);

	/// Set view clear flags with different clear color for each
	/// frame buffer texture. Must use `bgfx::setPaletteColor` to setup clear color
	/// palette.
	///
	/// @param[in] _id View id.
	/// @param[in] _flags Clear flags. Use `BGFX_CLEAR_NONE` to remove any clear
	///   operation. See: `BGFX_CLEAR_*`.
	/// @param[in] _depth Depth clear value.
	/// @param[in] _stencil Stencil clear value.
	/// @param[in] _0 Palette index for frame buffer attachment 0.
	/// @param[in] _1 Palette index for frame buffer attachment 1.
	/// @param[in] _2 Palette index for frame buffer attachment 2.
	/// @param[in] _3 Palette index for frame buffer attachment 3.
	/// @param[in] _4 Palette index for frame buffer attachment 4.
	/// @param[in] _5 Palette index for frame buffer attachment 5.
	/// @param[in] _6 Palette index for frame buffer attachment 6.
	/// @param[in] _7 Palette index for frame buffer attachment 7.
	///
	/// @attention C99 equivalent is `bgfx_set_view_clear_mrt`.
	///
	void setViewClear(
		  ViewId _id
		, uint16_t _flags
		, float _depth
		, uint8_t _stencil
		, uint8_t _0 = UINT8_MAX
		, uint8_t _1 = UINT8_MAX
		, uint8_t _2 = UINT8_MAX
		, uint8_t _3 = UINT8_MAX
		, uint8_t _4 = UINT8_MAX
		, uint8_t _5 = UINT8_MAX
		, uint8_t _6 = UINT8_MAX
		, uint8_t _7 = UINT8_MAX
		);

	/// Set view sorting mode.
	///
	/// @param[in] _id View id.
	/// @param[in] _mode View sort mode. See `ViewMode::Enum`.
	///
	/// @remarks
	///   View mode must be set prior calling `bgfx::submit` for the view.
	///
	/// @attention C99 equivalent is `bgfx_set_view_mode`.
	///
	void setViewMode(
		  ViewId _id
		, ViewMode::Enum _mode = ViewMode::Default
		);

	/// Set view frame buffer.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Frame buffer handle. Passing `BGFX_INVALID_HANDLE` as
	///   frame buffer handle will draw primitives from this view into
	///   default back buffer.
	///
	/// @remarks
	///   Not persistent after `bgfx::reset` call.
	///
	/// @attention C99 equivalent is `bgfx_set_view_frame_buffer`.
	///
	void setViewFrameBuffer(
		  ViewId _id
		, FrameBufferHandle _handle
		);

	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	///
	/// @param[in] _id View id.
	/// @param[in] _view View matrix.
	/// @param[in] _proj Projection matrix.
	///
	/// @attention C99 equivalent is `bgfx_set_view_transform`.
	///
	void setViewTransform(
		  ViewId _id
		, const void* _view
		, const void* _proj
		);

	/// Post submit view reordering.
	///
	/// @param[in] _id First view id.
	/// @param[in] _num Number of views to remap.
	/// @param[in] _remap View remap id table. Passing `NULL` will reset view ids
	///   to default state.
	///
	/// @attention C99 equivalent is `bgfx_set_view_order`.
	///
	void setViewOrder(
		  ViewId _id = 0
		, uint16_t _num = UINT16_MAX
		, const ViewId* _remap = NULL
		);

	/// Reset all view settings to default.
	///
	/// @param[in] _id View id.
	///
	/// @attention C99 equivalent is `bgfx_reset_view`.
	///
	void resetView(ViewId _id);

	/// Sets debug marker.
	///
	/// @attention C99 equivalent is `bgfx_set_marker`.
	///
	void setMarker(const char* _marker);

	/// Set render states for draw primitive.
	///
	/// @param[in] _state State flags. Default state for primitive type is
	///   triangles. See: `BGFX_STATE_DEFAULT`.
	///   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
	///   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
	///   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
	///   - `BGFX_STATE_CULL_*` - Backface culling mode.
	///   - `BGFX_STATE_WRITE_*` - Enable R, G, B, A or Z write.
	///   - `BGFX_STATE_MSAA` - Enable MSAA.
	///   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
	///
	/// @param[in] _rgba Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
	///   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
	///
	/// @remarks
	///   1. To setup more complex states use:
	///      `BGFX_STATE_ALPHA_REF(_ref)`,
	///      `BGFX_STATE_POINT_SIZE(_size)`,
	///      `BGFX_STATE_BLEND_FUNC(_src, _dst)`,
	///      `BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)`
	///      `BGFX_STATE_BLEND_EQUATION(_equation)`
	///      `BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)`
	///   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	///      equation is specified.
	///
	/// @attention C99 equivalent is `bgfx_set_state`.
	///
	void setState(
		  uint64_t _state
		, uint32_t _rgba = 0
		);

	/// Set condition for rendering.
	///
	/// @param[in] _handle Occlusion query handle.
	/// @param[in] _visible Render if occlusion query is visible.
	///
	/// @attention C99 equivalent is `bgfx_set_condition`.
	///
	void setCondition(
		  OcclusionQueryHandle _handle
		, bool _visible
		);

	/// Set stencil test state.
	///
	/// @param[in] _fstencil Front stencil state.
	/// @param[in] _bstencil Back stencil state. If back is set to `BGFX_STENCIL_NONE`
	///   _fstencil is applied to both front and back facing primitives.
	///
	/// @attention C99 equivalent is `bgfx_set_stencil`.
	///
	void setStencil(
		  uint32_t _fstencil
		, uint32_t _bstencil = BGFX_STENCIL_NONE
		);

	/// Set scissor for draw primitive. For scissor for all primitives in
	/// view see `bgfx::setViewScissor`.
	///
	/// @param[in] _x Position x from the left corner of the window.
	/// @param[in] _y Position y from the top corner of the window.
	/// @param[in] _width Width of scissor region.
	/// @param[in] _height Height of scissor region.
	/// @returns Scissor cache index.
	///
	/// @attention C99 equivalent is `bgfx_set_scissor`.
	///
	uint16_t setScissor(
		  uint16_t _x
		, uint16_t _y
		, uint16_t _width
		, uint16_t _height
		);

	/// Set scissor from cache for draw primitive.
	///
	/// @param[in] _cache Index in scissor cache. Passing UINT16_MAX unset primitive
	///   scissor and primitive will use view scissor instead.
	///
	/// @attention C99 equivalent is `bgfx_set_scissor_cached`.
	///
	void setScissor(uint16_t _cache = UINT16_MAX);

	/// Set model matrix for draw primitive. If it is not called,
	/// the model will be rendered with an identity model matrix.
	///
	/// @param[in] _mtx Pointer to first matrix in array.
	/// @param[in] _num Number of matrices in array.
	/// @returns index into matrix cache in case the same model matrix has
	///   to be used for other draw primitive call.
	///
	/// @attention C99 equivalent is `bgfx_set_transform`.
	///
	uint32_t setTransform(
		  const void* _mtx
		, uint16_t _num = 1
		);

	/// Reserve `_num` matrices in internal matrix cache.
	///
	/// @param[in] _transform Pointer to `Transform` structure.
	/// @param[in] _num Number of matrices.
	/// @returns index into matrix cache.
	///
	/// @attention Pointer returned can be modifed until `bgfx::frame` is called.
	/// @attention C99 equivalent is `bgfx_alloc_transform`.
	///
	uint32_t allocTransform(
		  Transform* _transform
		, uint16_t _num
		);

	/// Set model matrix from matrix cache for draw primitive.
	///
	/// @param[in] _cache Index in matrix cache.
	/// @param[in] _num Number of matrices from cache.
	///
	/// @attention C99 equivalent is `bgfx_set_transform_cached`.
	///
	void setTransform(
		  uint32_t _cache
		, uint16_t _num = 1
		);

	/// Set shader uniform parameter for draw primitive.
	///
	/// @param[in] _handle Uniform.
	/// @param[in] _value Pointer to uniform data.
	/// @param[in] _num Number of elements. Passing `UINT16_MAX` will
	///   use the _num passed on uniform creation.
	///
	/// @attention C99 equivalent is `bgfx_set_uniform`.
	///
	void setUniform(
		  UniformHandle _handle
		, const void* _value
		, uint16_t _num = 1
		);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Index buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_index_buffer`.
	///
	void setIndexBuffer(IndexBufferHandle _handle);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Index buffer.
	/// @param[in] _firstIndex First index to render.
	/// @param[in] _numIndices Number of indices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_index_buffer`.
	///
	void setIndexBuffer(
		  IndexBufferHandle _handle
		, uint32_t _firstIndex
		, uint32_t _numIndices
		);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Dynamic index buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_index_buffer`.
	///
	void setIndexBuffer(DynamicIndexBufferHandle _handle);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Dynamic index buffer.
	/// @param[in] _firstIndex First index to render.
	/// @param[in] _numIndices Number of indices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_index_buffer`.
	///
	void setIndexBuffer(
		  DynamicIndexBufferHandle _handle
		, uint32_t _firstIndex
		, uint32_t _numIndices
		);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _tib Transient index buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_index_buffer`.
	///
	void setIndexBuffer(const TransientIndexBuffer* _tib);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _tib Transient index buffer.
	/// @param[in] _firstIndex First index to render.
	/// @param[in] _numIndices Number of indices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_index_buffer`.
	///
	void setIndexBuffer(
		  const TransientIndexBuffer* _tib
		, uint32_t _firstIndex
		, uint32_t _numIndices
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _handle Vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, VertexBufferHandle _handle
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _handle Vertex buffer.
	/// @param[in] _startVertex First vertex to render.
	/// @param[in] _numVertices Number of vertices to render.
	/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
	///   used, vertex layout used for creation of vertex buffer will be used.
	///
	/// @attention C99 equivalent is `bgfx_set_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, VertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _handle Dynamic vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, DynamicVertexBufferHandle _handle
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _handle Dynamic vertex buffer.
	/// @param[in] _startVertex First vertex to render.
	/// @param[in] _numVertices Number of vertices to render.
	/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
	///   used, vertex layout used for creation of vertex buffer will be used.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, DynamicVertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _tvb Transient vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, const TransientVertexBuffer* _tvb
		);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _stream Vertex stream.
	/// @param[in] _tvb Transient vertex buffer.
	/// @param[in] _startVertex First vertex to render.
	/// @param[in] _numVertices Number of vertices to render.
	/// @param[in] _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is
	///   used, vertex layout used for creation of vertex buffer will be used.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_vertex_buffer`.
	///
	void setVertexBuffer(
		  uint8_t _stream
		, const TransientVertexBuffer* _tvb
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE
		);

	/// Set number of vertices for auto generated vertices use in conjuction
	/// with gl_VertexID.
	///
	/// @param[in] _numVertices Number of vertices.
	///
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// @attention C99 equivalent is `bgfx_set_vertex_count`.
	///
	void setVertexCount(uint32_t _numVertices);

	/// Set instance data buffer for draw primitive.
	///
	/// @param[in] _idb Transient instance data buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_buffer`.
	///
	void setInstanceDataBuffer(const InstanceDataBuffer* _idb);

	/// Set instance data buffer for draw primitive.
	///
	/// @param[in] _idb Transient instance data buffer.
	/// @param[in] _start First instance data.
	/// @param[in] _num Number of data instances.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_buffer`.
	///
	void setInstanceDataBuffer(
		  const InstanceDataBuffer* _idb
		, uint32_t _start
		, uint32_t _num
		);

	/// Set instance data buffer for draw primitive.
	///
	/// @param[in] _handle Vertex buffer.
	/// @param[in] _start First instance data.
	/// @param[in] _num Number of data instances.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_from_vertex_buffer`.
	///
	void setInstanceDataBuffer(
		  VertexBufferHandle _handle
		, uint32_t _start
		, uint32_t _num
		);

	/// Set instance data buffer for draw primitive.
	///
	/// @param[in] _handle Vertex buffer.
	/// @param[in] _start First instance data.
	/// @param[in] _num Number of data instances.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_from_dynamic_vertex_buffer`.
	///
	void setInstanceDataBuffer(
		  DynamicVertexBufferHandle _handle
		, uint32_t _start
		, uint32_t _num
		);

	/// Set number of instances for auto generated instances use in conjuction
	/// with gl_InstanceID.
	///
	/// @param[in] _numInstances Number of instances.
	///
	/// @attention Availability depends on: `BGFX_CAPS_VERTEX_ID`.
	/// @attention C99 equivalent is `bgfx_set_instance_count`.
	///
	void setInstanceCount(uint32_t _numInstances);

	/// Set texture stage for draw primitive.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _sampler Program sampler.
	/// @param[in] _handle Texture handle.
	/// @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///   - `BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_set_texture`.
	///
	void setTexture(
		  uint8_t _stage
		, UniformHandle _sampler
		, TextureHandle _handle
		, uint32_t _flags = UINT32_MAX
		);

	/// Submit an empty primitive for rendering. Uniforms and draw state
	/// will be applied but no geometry will be submitted.
	///
	/// These empty draw calls will sort before ordinary draw calls.
	///
	/// @param[in] _id View id.
	///
	/// @attention C99 equivalent is `bgfx_touch`.
	///
	void touch(ViewId _id);

	/// Submit primitive for rendering.
	///
	/// @param[in] _id View id.
	/// @param[in] _program Program.
	/// @param[in] _depth Depth for sorting.
	/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
	///
	/// @attention C99 equivalent is `bgfx_submit`.
	///
	void submit(
		  ViewId _id
		, ProgramHandle _program
		, uint32_t _depth = 0
		, uint8_t _flags  = BGFX_DISCARD_ALL
		);

	/// Submit primitive with occlusion query for rendering.
	///
	/// @param[in] _id View id.
	/// @param[in] _program Program.
	/// @param[in] _occlusionQuery Occlusion query.
	/// @param[in] _depth Depth for sorting.
	/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
	///
	/// @attention C99 equivalent is `bgfx_submit_occlusion_query`.
	///
	void submit(
		  ViewId _id
		, ProgramHandle _program
		, OcclusionQueryHandle _occlusionQuery
		, uint32_t _depth = 0
		, uint8_t _flags  = BGFX_DISCARD_ALL
		);

	/// Submit primitive for rendering with index and instance data info from
	/// indirect buffer.
	///
	/// @param[in] _id View id.
	/// @param[in] _program Program.
	/// @param[in] _indirectHandle Indirect buffer.
	/// @param[in] _start First element in indirect buffer.
	/// @param[in] _num Number of dispatches.
	/// @param[in] _depth Depth for sorting.
	/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
	///
	/// @attention C99 equivalent is `bgfx_submit_indirect`.
	///
	void submit(
		  ViewId _id
		, ProgramHandle _program
		, IndirectBufferHandle _indirectHandle
		, uint16_t _start = 0
		, uint16_t _num   = 1
		, uint32_t _depth = 0
		, uint8_t _flags  = BGFX_DISCARD_ALL
		);

	/// Set compute index buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Index buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_index_buffer`.
	///
	void setBuffer(
		  uint8_t _stage
		, IndexBufferHandle _handle
		, Access::Enum _access
		);

	/// Set compute vertex buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Vertex buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_vertex_buffer`.
	///
	void setBuffer(
		  uint8_t _stage
		, VertexBufferHandle _handle
		, Access::Enum _access
		);

	/// Set compute dynamic index buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Dynamic index buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_dynamic_index_buffer`.
	///
	void setBuffer(
		  uint8_t _stage
		, DynamicIndexBufferHandle _handle
		, Access::Enum _access
		);

	/// Set compute dynamic vertex buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Dynamic vertex buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_dynamic_vertex_buffer`.
	///
	void setBuffer(
		  uint8_t _stage
		, DynamicVertexBufferHandle _handle
		, Access::Enum _access
		);

	/// Set compute indirect buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Indirect buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_indirect_buffer`.
	///
	void setBuffer(
		  uint8_t _stage
		, IndirectBufferHandle _handle
		, Access::Enum _access
		);

	/// Set compute image from texture.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _handle Texture handle.
	/// @param[in] _mip Mip level.
	/// @param[in] _access Texture access. See `Access::Enum`.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_image`.
	///
	void setImage(
		  uint8_t _stage
		, TextureHandle _handle
		, uint8_t _mip
		, Access::Enum _access
		, TextureFormat::Enum _format = TextureFormat::Count
		);

	/// Dispatch compute.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Compute program.
	/// @param[in] _numX Number of groups X.
	/// @param[in] _numY Number of groups Y.
	/// @param[in] _numZ Number of groups Z.
	/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
	///
	/// @attention C99 equivalent is `bgfx_dispatch`.
	///
	void dispatch(
		  ViewId _id
		, ProgramHandle _handle
		, uint32_t _numX = 1
		, uint32_t _numY = 1
		, uint32_t _numZ = 1
		, uint8_t _flags = BGFX_DISCARD_ALL
		);

	/// Dispatch compute indirect.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Compute program.
	/// @param[in] _indirectHandle Indirect buffer.
	/// @param[in] _start First element in indirect buffer.
	/// @param[in] _num Number of dispatches.
	/// @param[in] _flags Discard or preserve states. See `BGFX_DISCARD_*`.
	///
	/// @attention C99 equivalent is `bgfx_dispatch_indirect`.
	///
	void dispatch(
		  ViewId _id
		, ProgramHandle _handle
		, IndirectBufferHandle _indirectHandle
		, uint16_t _start = 0
		, uint16_t _num   = 1
		, uint8_t _flags  = BGFX_DISCARD_ALL
		);

	/// Discard all previously set state for draw or compute call.
	///
	/// @param[in] _flags Draw/compute states to discard.
	///
	/// @attention C99 equivalent is `bgfx_discard`.
	///
	void discard(uint8_t _flags = BGFX_DISCARD_ALL);

	/// Blit 2D texture region between two 2D textures.
	///
	/// @param[in] _id View id.
	/// @param[in] _dst Destination texture handle.
	/// @param[in] _dstX Destination texture X position.
	/// @param[in] _dstY Destination texture Y position.
	/// @param[in] _src Source texture handle.
	/// @param[in] _srcX Source texture X position.
	/// @param[in] _srcY Source texture Y position.
	/// @param[in] _width Width of region.
	/// @param[in] _height Height of region.
	///
	/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	/// @attention C99 equivalent is `bgfx_blit`.
	///
	void blit(
		  ViewId _id
		, TextureHandle _dst
		, uint16_t _dstX
		, uint16_t _dstY
		, TextureHandle _src
		, uint16_t _srcX = 0
		, uint16_t _srcY = 0
		, uint16_t _width = UINT16_MAX
		, uint16_t _height = UINT16_MAX
		);

	/// Blit texture region between two textures.
	///
	/// @param[in] _id View id.
	/// @param[in] _dst Destination texture handle.
	/// @param[in] _dstMip Destination texture mip level.
	/// @param[in] _dstX Destination texture X position.
	/// @param[in] _dstY Destination texture Y position.
	/// @param[in] _dstZ If texture is 2D this argument should be 0. If destination texture is cube
	///   this argument represents destination texture cube face. For 3D texture this argument
	///   represents destination texture Z position.
	/// @param[in] _src Source texture handle.
	/// @param[in] _srcMip Source texture mip level.
	/// @param[in] _srcX Source texture X position.
	/// @param[in] _srcY Source texture Y position.
	/// @param[in] _srcZ If texture is 2D this argument should be 0. If source texture is cube
	///   this argument represents source texture cube face. For 3D texture this argument
	///   represents source texture Z position.
	/// @param[in] _width Width of region.
	/// @param[in] _height Height of region.
	/// @param[in] _depth If texture is 3D this argument represents depth of region, otherwise it's
	///   unused.
	///
	/// @attention Destination texture must be created with `BGFX_TEXTURE_BLIT_DST` flag.
	/// @attention Availability depends on: `BGFX_CAPS_TEXTURE_BLIT`.
	/// @attention C99 equivalent is `bgfx_blit`.
	///
	void blit(
		  ViewId _id
		, TextureHandle _dst
		, uint8_t _dstMip
		, uint16_t _dstX
		, uint16_t _dstY
		, uint16_t _dstZ
		, TextureHandle _src
		, uint8_t _srcMip = 0
		, uint16_t _srcX = 0
		, uint16_t _srcY = 0
		, uint16_t _srcZ = 0
		, uint16_t _width = UINT16_MAX
		, uint16_t _height = UINT16_MAX
		, uint16_t _depth = UINT16_MAX
		);

	/// Request screen shot of window back buffer.
	///
	/// @param[in] _handle Frame buffer handle. If handle is `BGFX_INVALID_HANDLE` request will be
	///   made for main window back buffer.
	/// @param[in] _filePath Will be passed to `bgfx::CallbackI::screenShot` callback.
	///
	/// @remarks
	///   `bgfx::CallbackI::screenShot` must be implemented.
	///
	/// @attention Frame buffer handle must be created with OS' target native window handle.
	/// @attention C99 equivalent is `bgfx_request_screen_shot`.
	///
	void requestScreenShot(
		  FrameBufferHandle _handle
		, const char* _filePath
		);

} // namespace bgfx

#endif // BGFX_H_HEADER_GUARD

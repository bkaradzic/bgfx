/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_H_HEADER_GUARD
#define BGFX_H_HEADER_GUARD

#include <stdarg.h> // va_list
#include <stdint.h> // uint32_t
#include <stdlib.h> // size_t

#include "bgfxdefines.h"

///
#define BGFX_HANDLE(_name) \
			struct _name { uint16_t idx; }; \
			inline bool isValid(_name _handle) { return bgfx::invalidHandle != _handle.idx; }

#define BGFX_INVALID_HANDLE { bgfx::invalidHandle }

namespace bx { struct ReallocatorI; }

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
			MinimumRequiredSpecs,
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
			Null,         //!< No rendering.
			Direct3D9,    //!< Direct3D 9.0
			Direct3D11,   //!< Direct3D 11.0
			Direct3D12,   //!< Direct3D 12.0
			Metal,        //!< Metal
			OpenGLES,     //!< OpenGL ES 2.0+
			OpenGL,       //!< OpenGL 2.1+
			Vulkan,       //!< Vulkan

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
			Read,
			Write,
			ReadWrite,

			Count
		};
	};

	/// Vertex attribute enum.
	///
	/// @attention C99 equivalent is `bgfx_attrib_t`.
	///
	struct Attrib
	{
		/// Corresponds to vertex shader attribute. Attributes:
		enum Enum
		{
			Position,  //!< a_position
			Normal,    //!< a_normal
			Tangent,   //!< a_tangent
			Bitangent, //!< a_bitangent
			Color0,    //!< a_color0
			Color1,    //!< a_color1
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
			BC1,          //!< DXT1
			BC2,          //!< DXT3
			BC3,          //!< DXT5
			BC4,          //!< LATC1/ATI1
			BC5,          //!< LATC2/ATI2
			BC6H,         //!< BC6H
			BC7,          //!< BC7
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
			R11G11B10F,

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
			Int1,
			End,

			Vec4,
			Mat3,
			Mat4,

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
			Equal,
			Half,
			Quarter,
			Eighth,
			Sixteenth,
			Double,

			Count
		};
	};

	static const uint16_t invalidHandle = UINT16_MAX;

	BGFX_HANDLE(DynamicIndexBufferHandle);
	BGFX_HANDLE(DynamicVertexBufferHandle);
	BGFX_HANDLE(FrameBufferHandle);
	BGFX_HANDLE(IndexBufferHandle);
	BGFX_HANDLE(IndirectBufferHandle);
	BGFX_HANDLE(ProgramHandle);
	BGFX_HANDLE(ShaderHandle);
	BGFX_HANDLE(TextureHandle);
	BGFX_HANDLE(UniformHandle);
	BGFX_HANDLE(VertexBufferHandle);
	BGFX_HANDLE(VertexDeclHandle);

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

		/// If fatal code code is not Fatal::DebugCheck this callback is
		/// called on unrecoverable error. It's not safe to continue, inform
		/// user and terminate application from this call.
		///
		/// @param[in] _code Fatal error code.
		/// @param[in] _str More information about error.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.fatal`.
		///
		virtual void fatal(Fatal::Enum _code, const char* _str) = 0;

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
		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) = 0;

		/// Return size of for cached item. Return 0 if no cached item was
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
		/// @param[in] _pitch Number of bytes to skip to next line.
		/// @param[in] _data Image data.
		/// @param[in] _size Image size.
		/// @param[in] _yflip If true image origin is bottom left.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.screen_shot`.
		///
		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) = 0;

		/// Called when capture begins.
		///
		/// @attention C99 equivalent is `bgfx_callback_vtbl.capture_begin`.
		///
		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format, bool _yflip) = 0;

		/// Called when capture ends.
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

	/// Memory release callback.
	///
	/// @attention C99 equivalent is `bgfx_release_fn_t`.
	///
	typedef void (*ReleaseFn)(void* _ptr, void* _userData);

	/// Memory obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
	///
	/// @attention C99 equivalent is `bgfx_memory_t`.
	///
	struct Memory
	{
		uint8_t* data;
		uint32_t size;
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
		/// - `BGFX_CAPS_TEXTURE_COMPARE_LEQUAL` - Less equal texture
		///      compare mode.
		/// - `BGFX_CAPS_TEXTURE_COMPARE_ALL` - All texture compare modes.
		/// - `BGFX_CAPS_TEXTURE_3D` - 3D textures.
		/// - `BGFX_CAPS_VERTEX_ATTRIB_HALF` - AttribType::Half.
		/// - `BGFX_CAPS_INSTANCING` - Vertex instancing.
		/// - `BGFX_CAPS_RENDERER_MULTITHREADED` - Renderer on separate
		///      thread.
		/// - `BGFX_CAPS_FRAGMENT_DEPTH` - Fragment shader can modify depth
		///      buffer value (gl_FragDepth).
		/// - `BGFX_CAPS_BLEND_INDEPENDENT` - Multiple render targets can
		///      have different blend mode set individually.
		/// - `BGFX_CAPS_COMPUTE` - Renderer has compute shaders.
		/// - `BGFX_CAPS_FRAGMENT_ORDERING` - Intel's pixel sync.
		/// - `BGFX_CAPS_SWAP_CHAIN` - Multiple windows.
		///
		uint64_t supported;

		uint32_t maxDrawCalls;     //!< Maximum draw calls.
		uint16_t maxTextureSize;   //!< Maximum texture size.
		uint16_t maxViews;         //!< Maximum views.
		uint8_t  maxFBAttachments; //!< Maximum frame buffer attachments.
		uint8_t  numGPUs;          //!< Number of enumerated GPUs.
		uint16_t vendorId;         //!< Selected GPU vendor id.
		uint16_t deviceId;         //!< Selected GPU device id.

		/// GPU info.
		///
		/// @attention C99 equivalent is `bgfx_caps_gpu_t`.
		///
		struct GPU
		{
			uint16_t vendorId;
			uint16_t deviceId;
		};

		GPU gpu[4]; //!< Enumerated GPUs.

		/// Supported texture formats.
		///   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - not supported
		///   - `BGFX_CAPS_FORMAT_TEXTURE_COLOR` - supported
		///   - `BGFX_CAPS_FORMAT_TEXTURE_EMULATED` - emulated
		///   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - supported vertex texture
		uint8_t formats[TextureFormat::Count];
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
	};

	/// Transient vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_transient_vertex_buffer_t`.
	///
	struct TransientVertexBuffer
	{
		uint8_t* data;             //!< Pointer to data.
		uint32_t size;             //!< Data size.
		uint32_t startVertex;      //!< First vertex.
		uint16_t stride;           //!< Vertex stride.
		VertexBufferHandle handle; //!< Vertex buffer handle.
		VertexDeclHandle decl;     //!< Vertex declaration handle.
	};

	/// Instance data buffer info.
	///
	/// @attention C99 equivalent is `bgfx_texture_info_t`.
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
		uint8_t numMips;            //!< Number of MIP maps.
		uint8_t bitsPerPixel;       //!< Format bits per pixel.
		bool    cubeMap;            //!< Texture is cubemap.
	};

	/// Transform data.
	///
	/// @attention C99 equivalent is `bgfx_transform_t`.
	///
	struct Transform
	{
		float* data;  //!< Pointer to first matrix.
		uint16_t num; //!< Number of matrices.
	};

	/// HMD info.
	///
	/// @attention C99 equivalent is `bgfx_hmd_t`.
	///
	struct HMD
	{
		/// Eye
		///
		/// @attention C99 equivalent is `bgfx_hmd_eye_t`.
		///
		struct Eye
		{
			float rotation[4];          //!< Eye rotation represented as quaternion.
			float translation[3];       //!< Eye translation.
			float fov[4];               //!< Field of view (up, down, left, right).
			float viewOffset[3];        //!< Eye view matrix translation adjustment.
			float pixelsPerTanAngle[2]; //!<
		};

		Eye eye[2];
		uint16_t width;        //!< Framebuffer width.
		uint16_t height;       //!< Framebuffer width.
		uint32_t deviceWidth;  //!< Device resolution width
		uint32_t deviceHeight; //!< Device resolution height
		uint8_t flags;         //!< Status flags
	};

	/// Renderer statistics data.
	///
	/// @attention C99 equivalent is `bgfx_stats_t`.
	///
	struct Stats
	{
		uint64_t cpuTime;      //!< CPU frame time.
		uint64_t cpuTimerFreq; //!< CPU timer frequency.

		uint64_t gpuTime;      //!< GPU frame time.
		uint64_t gpuTimerFreq; //!< GPU timer frequency.
	};

	/// Vertex declaration.
	///
	/// @attention C99 equivalent is `bgfx_vertex_decl_t`.
	///
	struct VertexDecl
	{
		VertexDecl();

		/// Start VertexDecl.
		///
		/// @attention C99 equivalent is `bgfx_vertex_decl_begin`.
		///
		VertexDecl& begin(RendererType::Enum _renderer = RendererType::Null);

		/// End VertexDecl.
		///
		/// @attention C99 equivalent is `bgfx_vertex_decl_begin`.
		///
		void end();

		/// Add attribute to VertexDecl.
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
		/// @attention C99 equivalent is `bgfx_vertex_decl_add`.
		///
		VertexDecl& add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized = false, bool _asInt = false);

		/// Skip _num bytes in vertex stream.
		///
		/// @attention C99 equivalent is `bgfx_vertex_decl_skip`.
		///
		VertexDecl& skip(uint8_t _num);

		/// Decode attribute.
		///
		/// @attention C99 equivalent is ``.
		///
		void decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized, bool& _asInt) const;

		/// Returns true if VertexDecl contains attribute.
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

	/// Pack vec4 into vertex stream format.
	///
	/// @attention C99 equivalent is `bgfx_vertex_pack`.
	///
	void vertexPack(const float _input[4], bool _inputNormalized, Attrib::Enum _attr, const VertexDecl& _decl, void* _data, uint32_t _index = 0);

	/// Unpack vec4 from vertex stream format.
	///
	/// @attention C99 equivalent is `bgfx_vertex_unpack`.
	///
	void vertexUnpack(float _output[4], Attrib::Enum _attr, const VertexDecl& _decl, const void* _data, uint32_t _index = 0);

	/// Converts vertex stream data from one vertex stream format to another.
	///
	/// @param[in] _destDecl Destination vertex stream declaration.
	/// @param[in] _destData Destination vertex stream.
	/// @param[in] _srcDecl Source vertex stream declaration.
	/// @param[in] _srcData Source vertex stream data.
	/// @param[in] _num Number of vertices to convert from source to destination.
	///
	/// @attention C99 equivalent is `bgfx_vertex_convert`.
	///
	void vertexConvert(const VertexDecl& _destDecl, void* _destData, const VertexDecl& _srcDecl, const void* _srcData, uint32_t _num = 1);

	/// Weld vertices.
	///
	/// @param[in] _output Welded vertices remapping table. The size of buffer
	///   must be the same as number of vertices.
	/// @param[in] _decl Vertex stream declaration.
	/// @param[in] _data Vertex stream.
	/// @param[in] _num Number of vertices in vertex stream.
	/// @param[in] _epsilon Error tolerance for vertex position comparison.
	/// @returns Number of unique vertices after vertex welding.
	///
	/// @attention C99 equivalent is `bgfx_weld_vertices`.
	///
	uint16_t weldVertices(uint16_t* _output, const VertexDecl& _decl, const void* _data, uint16_t _num, float _epsilon = 0.001f);

	/// Swizzle RGBA8 image to BGRA8.
	///
	/// @param[in] _width Width of input image (pixels).
	/// @param[in] _height Height of input image (pixels).
	/// @param[in] _pitch Pitch of input image (bytes).
	/// @param[in] _src Source image.
	/// @param[in] _dst Destination image. Must be the same size as input image.
	///   _dst might be pointer to the same memory as _src.
	///
	/// @attention C99 equivalent is `bgfx_image_swizzle_bgra8`.
	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	/// Downsample RGBA8 image with 2x2 pixel average filter.
	///
	/// @param[in] _width Width of input image (pixels).
	/// @param[in] _height Height of input image (pixels).
	/// @param[in] _pitch Pitch of input image (bytes).
	/// @param[in] _src Source image.
	/// @param[in] _dst Destination image. Must be at least quarter size of
	///   input image. _dst might be pointer to the same memory as _src.
	///
	/// @attention C99 equivalent is `bgfx_image_rgba8_downsample_2x2`.
	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	/// Returns supported backend API renderers.
	///
	/// @attention C99 equivalent is `bgfx_get_supported_renderers`.
	///
	uint8_t getSupportedRenderers(RendererType::Enum _enum[RendererType::Count]);

	/// Returns name of renderer.
	///
	/// @attention C99 equivalent is `bgfx_get_renderer_name`.
	///
	const char* getRendererName(RendererType::Enum _type);

	/// Initialize bgfx library.
	///
	/// @param[in] _type Select rendering backend. When set to RendererType::Count
	///   default rendering backend will be selected.
	///   See: `bgfx::RendererType`
	///
	/// @param[in] _vendorId Vendor PCI id. If set to `BGFX_PCI_ID_NONE` it will select the first
	///   device.
	///   - `BGFX_PCI_ID_NONE` - autoselect.
	///   - `BGFX_PCI_ID_AMD` - AMD.
	///   - `BGFX_PCI_ID_INTEL` - Intel.
	///   - `BGFX_PCI_ID_NVIDIA` - nVidia.
	///
	/// @param[in] _deviceId Device id. If set to 0 it will select first device, or device with
	///   matching id.
	///
	/// @param[in] _callback Provide application specific callback interface.
	///   See: `bgfx::CallbackI`
	///
	/// @param[in] _reallocator Custom allocator. When custom allocator is not
	///   specified, library uses default CRT allocator. The library assumes
	///   icustom allocator is thread safe.
	///
	/// @returns `true` if initialization is sucessful.
	///
	/// @attention C99 equivalent is `bgfx_init`.
	///
	bool init(RendererType::Enum _type = RendererType::Count, uint16_t _vendorId = BGFX_PCI_ID_NONE, uint16_t _deviceId = 0, CallbackI* _callback = NULL, bx::ReallocatorI* _reallocator = NULL);

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
	///   - `BGFX_RESET_HMD` - HMD stereo rendering.
	///   - `BGFX_RESET_HMD_DEBUG` - HMD stereo rendering debug mode.
	///   - `BGFX_RESET_HMD_RECENTER` - HMD calibration.
	///   - `BGFX_RESET_FLUSH_AFTER_RENDER` - Flush rendering after submitting to GPU.
	///   - `BGFX_RESET_FLIP_AFTER_RENDER` - This flag  specifies where flip
	///     occurs. Default behavior is that flip occurs before rendering new
	///     frame. This flag only has effect when `BGFX_CONFIG_MULTITHREADED=0`.
	///   - `BGFX_RESET_SRGB_BACKBUFFER` - Enable sRGB backbuffer.
	///
	/// @attention This call doesn't actually change window size, it just
	///   resizes back-buffer. Windowing code has to change window size.
	///
	/// @attention C99 equivalent is `bgfx_reset`.
	///
	void reset(uint32_t _width, uint32_t _height, uint32_t _flags = BGFX_RESET_NONE);

	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	///
	/// @returns Current frame number. This might be used in conjunction with
	///   double/multi buffering data outside the library and passing it to
	///   library via `bgfx::makeRef` calls.
	///
	/// @attention C99 equivalent is `bgfx_frame`.
	///
	uint32_t frame();

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

	/// Returns HMD info.
	///
	/// @attention C99 equivalent is `bgfx_get_hmd`.
	///
	const HMD* getHMD();

	/// Returns performance counters.
	///
	const Stats* getStats();

	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	///
	/// @attention C99 equivalent is `bgfx_alloc`.
	///
	const Memory* alloc(uint32_t _size);

	/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
	///
	/// @attention C99 equivalent is `bgfx_copy`.
	///
	const Memory* copy(const void* _data, uint32_t _size);

	/// Make reference to data to pass to bgfx. Unlike `bgfx::alloc` this call
	/// doesn't allocate memory for data. It just copies pointer to data. You
	/// can pass `ReleaseFn` function pointer to release this memory after it's
	/// consumed, or you must make sure data is available for at least 2
	/// `bgfx::frame` calls. `ReleaseFn` function must be able to be called
	/// called from any thread.
	///
	/// @attention C99 equivalent are `bgfx_make_ref`, `bgfx_make_ref_release`.
	///
	const Memory* makeRef(const void* _data, uint32_t _size, ReleaseFn _releaseFn = NULL, void* _userData = NULL);

	/// Set debug flags.
	///
	/// @param[in] _debug Available flags:
	///   - `BGFX_DEBUG_IFH` - Infinitely fast hardware. When this flag is set
	///     all rendering calls will be skipped. It's useful when profiling
	///     to quickly assess bottleneck between CPU and GPU.
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
	/// @attention C99 equivalent is `bgfx_dbg_text_clear`.
	///
	void dbgTextClear(uint8_t _attr = 0, bool _small = false);

	/// Print into internal debug text buffer.
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_printf`.
	///
	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);

	/// Draw image into internal debug text buffer.
	///
	/// @param[in] _x      X position from top-left.
	/// @param[in] _y      Y position from top-left.
	/// @param[in] _width  Image width.
	/// @param[in] _height Image height.
	/// @param[in] _data   Raw image data (character/attribute raw encoding).
	/// @param[in] _pitch  Image pitch in bytes.
	///
	/// @attention C99 equivalent is `bgfx_dbg_text_image`.
	///
	void dbgTextImage(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch);

	/// Create static index buffer.
	///
	/// @param[in] _mem Index buffer data.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_index_buffer`.
	///
	IndexBufferHandle createIndexBuffer(const Memory* _mem, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Destroy static index buffer.
	///
	/// @attention C99 equivalent is `bgfx_destroy_index_buffer`.
	///
	void destroyIndexBuffer(IndexBufferHandle _handle);

	/// Create static vertex buffer.
	///
	/// @param[in] _mem Vertex buffer data.
	/// @param[in] _decl Vertex declaration.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	/// @returns Static vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_create_vertex_buffer`.
	///
	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Destroy static vertex buffer.
	///
	/// @param[in] _handle Static vertex buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_vertex_buffer`.
	///
	void destroyVertexBuffer(VertexBufferHandle _handle);

	/// Create empty dynamic index buffer.
	///
	/// @param[in] _num Number of indices.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_index_buffer`.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Create dynamic index buffer and initialized it.
	///
	/// @param[in] _mem Index buffer data.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_index_buffer_mem`.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Update dynamic index buffer.
	///
	/// @param[in] _handle Dynamic index buffer handle.
	/// @param[in] _startIndex Start index.
	/// @param[in] _mem Index buffer data.
	///
	/// @attention C99 equivalent is `bgfx_update_dynamic_index_buffer`.
	///
	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem);

	/// Destroy dynamic index buffer.
	///
	/// @param[in] _handle Dynamic index buffer handle.
	///
	/// @attention C99 equivalent is `bgfx_destroy_dynamic_index_buffer`.
	///
	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle);

	/// Create empty dynamic vertex buffer.
	///
	/// @param[in] _num Number of vertices.
	/// @param[in] _decl Vertex declaration.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_vertex_buffer`.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexDecl& _decl, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Create dynamic vertex buffer and initialize it.
	///
	/// @param[in] _mem Vertex buffer data.
	/// @param[in] _decl Vertex declaration.
	/// @param[in] _flags Buffer creation flags.
	///   - `BGFX_BUFFER_NONE` - No flags.
	///   - `BGFX_BUFFER_COMPUTE_READ` - Buffer will be read from by compute shader.
	///   - `BGFX_BUFFER_COMPUTE_WRITE` - Buffer will be written into by compute shader. When buffer
	///       is created with `BGFX_BUFFER_COMPUTE_WRITE` flag it cannot be updated from CPU.
	///   - `BGFX_BUFFER_COMPUTE_READ_WRITE` - Buffer will be used for read/write by compute shader.
	///   - `BGFX_BUFFER_ALLOW_RESIZE` - Buffer will resize on buffer update if different amount of
	///       data is passed. If this flag is not specified if more data is passed on update buffer
	///       will be trimmed to fit existing buffer size. This flag has effect only on dynamic
	///       buffers.
	///   - `BGFX_BUFFER_INDEX32` - Buffer is using 32-bit indices. This flag has effect only on
	///       index buffers.
	///
	/// @attention C99 equivalent is `bgfx_create_dynamic_vertex_buffer_mem`.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags = BGFX_BUFFER_NONE);

	/// Update dynamic vertex buffer.
	///
	/// @param[in] _handle Dynamic vertex buffer handle.
	/// @param[in] _startVertex Start vertex.
	/// @param[in] _mem Vertex buffer data.
	///
	/// @attention C99 equivalent is `bgfx_update_dynamic_vertex_buffer`.
	///
	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem);

	/// Destroy dynamic vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_destroy_dynamic_vertex_buffer`.
	///
	void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle);

	/// Returns true if internal transient index buffer has enough space.
	///
	/// @param[in] _num Number of indices.
	///
	/// @attention C99 equivalent is `bgfx_check_avail_transient_index_buffer`.
	///
	bool checkAvailTransientIndexBuffer(uint32_t _num);

	/// Returns true if internal transient vertex buffer has enough space.
	///
	/// @param[in] _num Number of vertices.
	/// @param[in] _decl Vertex declaration.
	///
	/// @attention C99 equivalent is `bgfx_check_avail_transient_vertex_buffer`.
	///
	bool checkAvailTransientVertexBuffer(uint32_t _num, const VertexDecl& _decl);

	/// Returns true if internal instance data buffer has enough space.
	///
	/// @param[in] _num Number of instances.
	/// @param[in] _stride Stride per instance.
	///
	/// @attention C99 equivalent is `bgfx_check_avail_instance_data_buffer`.
	///
	bool checkAvailInstanceDataBuffer(uint32_t _num, uint16_t _stride);

	/// Returns true if both internal transient index and vertex buffer have
	/// enough space.
	///
	/// @param[in] _numVertices Number of vertices.
	/// @param[in] _decl Vertex declaration.
	/// @param[in] _numIndices Number of indices.
	///
	/// @attention C99 equivalent is `bgfx_check_avail_transient_buffers`.
	///
	bool checkAvailTransientBuffers(uint32_t _numVertices, const VertexDecl& _decl, uint32_t _numIndices);

	/// Allocate transient index buffer.
	///
	/// @param[out] _tib TransientIndexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param[in] _num Number of indices to allocate.
	///
	/// @remarks
	///   1. You must call setIndexBuffer after alloc in order to avoid memory
	///      leak.
	///   2. Only 16-bit index buffer is supported.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_index_buffer`.
	///
	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num);

	/// Allocate transient vertex buffer.
	///
	/// @param[out] _tvb TransientVertexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param[in] _num Number of vertices to allocate.
	/// @param[in] _decl Vertex declaration.
	///
	/// @remarks
	///   You must call setVertexBuffer after alloc in order to avoid memory
	///   leak.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_vertex_buffer`.
	///
	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexDecl& _decl);

	/// Check for required space and allocate transient vertex and index
	/// buffers. If both space requirements are satisfied function returns
	/// true.
	///
	/// @remarks
	///   Only 16-bit index buffer is supported.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transient_buffers`.
	///
	bool allocTransientBuffers(TransientVertexBuffer* _tvb, const VertexDecl& _decl, uint32_t _numVertices, TransientIndexBuffer* _tib, uint32_t _numIndices);

	/// Allocate instance data buffer.
	///
	/// @remarks
	///   You must call setInstanceDataBuffer after alloc in order to avoid
	///   memory leak.
	///
	/// @attention C99 equivalent is `bgfx_alloc_instance_data_buffer`.
	///
	const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride);

	/// Create draw indirect buffer.
	///
	/// @attention C99 equivalent is `bgfx_create_indirect_buffer`.
	///
	IndirectBufferHandle createIndirectBuffer(uint32_t _num);

	/// Destroy draw indirect buffer.
	///
	/// @attention C99 equivalent is `bgfx_destroy_indirect_buffer`.
	///
	void destroyIndirectBuffer(IndirectBufferHandle _handle);

	/// Create shader from memory buffer.
	///
	/// @attention C99 equivalent is `bgfx_create_shader`.
	///
	ShaderHandle createShader(const Memory* _mem);

	/// Returns num of uniforms, and uniform handles used inside shader.
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
	uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms = NULL, uint16_t _max = 0);

	/// Destroy shader. Once program is created with shader it is safe to
	/// destroy shader.
	///
	/// @attention C99 equivalent is `bgfx_destroy_shader`.
	///
	void destroyShader(ShaderHandle _handle);

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
	ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders = false);

	/// Create program with compute shader.
	///
	/// @param[in] _csh Compute shader.
	/// @param[in] _destroyShader If true, shader will be destroyed when
	///   program is destroyed.
	/// @returns Program handle.
	///
	/// @attention C99 equivalent is `bgfx_create_compute_program`.
	///
	ProgramHandle createProgram(ShaderHandle _csh, bool _destroyShader = false);

	/// Destroy program.
	///
	/// @attention C99 equivalent is `bgfx_destroy_program`.
	///
	void destroyProgram(ProgramHandle _handle);

	/// Calculate amount of memory required for texture.
	///
	/// @attention C99 equivalent is `bgfx_calc_texture_size`.
	///
	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint8_t _numMips, TextureFormat::Enum _format);

	/// Create texture from memory buffer.
	///
	/// @param[in] _mem DDS, KTX or PVR texture data.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _skip Skip top level mips when parsing texture.
	/// @param[out] _info When non-`NULL` is specified it returns parsed texture information.
	/// @returns Texture handle.
	///
	/// @attention C99 equivalent is `bgfx_create_texture`.
	///
	TextureHandle createTexture(const Memory* _mem, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, TextureInfo* _info = NULL);

	/// Create 2D texture.
	///
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _numMips Number of mip-maps.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_2d`.
	///
	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create frame buffer with size based on backbuffer ratio. Frame buffer will maintain ratio
	/// if back buffer resolution changes.
	///
	/// @param[in] _ratio Frame buffer size in respect to back-buffer size. See:
	///   `BackbufferRatio::Enum`.
	/// @param[in] _numMips Number of mip-maps.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_2d_scaled`.
	///
	TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE);

	/// Create 3D texture.
	///
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _depth Depth.
	/// @param[in] _numMips Number of mip-maps.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_3d`.
	///
	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create Cube texture.
	///
	/// @param[in] _size Cube side size.
	/// @param[in] _numMips Number of mip-maps.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _mem Texture data. If `_mem` is non-NULL, created texture will be immutable.
	///
	/// @attention C99 equivalent is `bgfx_create_texture_cube`.
	///
	TextureHandle createTextureCube(uint16_t _size, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Update 2D texture.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _mip Mip level.
	/// @param[in] _x X offset in texture.
	/// @param[in] _y Y offset in texture.
	/// @param[in] _width Width of texture block.
	/// @param[in] _height Height of texture block.
	/// @param[in] _mem Texture update data.
	/// @param[in] _pitch Pitch of input image (bytes). When _pitch is set to
	///   UINT16_MAX, it will be calculated internally based on _width.
	///
	/// @attention C99 equivalent is `bgfx_update_texture_2d`.
	///
	void updateTexture2D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch = UINT16_MAX);

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
	/// @attention C99 equivalent is `bgfx_update_texture_3d`.
	///
	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem);

	/// Update Cube texture.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _side Cubemap side, where 0 is +X, 1 is -X, 2 is +Y, 3 is
	///   -Y, 4 is +Z, and 5 is -Z.
	///
	///                  +----------+
	///                  |-z       2|
	///                  | ^  +y    |
	///                  | |        |
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
	/// @attention C99 equivalent is `bgfx_update_texture_cube`.
	///
	void updateTextureCube(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch = UINT16_MAX);

	/// Destroy texture.
	///
	/// @attention C99 equivalent is `bgfx_destroy_texture`.
	///
	void destroyTexture(TextureHandle _handle);

	/// Create frame buffer (simple).
	///
	/// @param[in] _width Texture width.
	/// @param[in] _height Texture height.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _textureFlags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer`.
	///
	FrameBufferHandle createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	/// Create frame buffer with size based on backbuffer ratio. Frame buffer will maintain ratio
	/// if back buffer resolution changes.
	///
	/// @param[in] _ratio Frame buffer size in respect to back-buffer size. See:
	///   `BackbufferRatio::Enum`.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _textureFlags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_scaled`.
	///
	FrameBufferHandle createFrameBuffer(BackbufferRatio::Enum _ratio, TextureFormat::Enum _format, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	/// Create frame buffer.
	///
	/// @param[in] _num Number of texture attachments.
	/// @param[in] _handles Texture attachments.
	/// @param[in] _destroyTextures If true, textures will be destroyed when
	///   frame buffer is destroyed.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_from_handles`.
	///
	FrameBufferHandle createFrameBuffer(uint8_t _num, TextureHandle* _handles, bool _destroyTextures = false);

	/// Create frame buffer for multiple window rendering.
	///
	/// @param[in] _nwh OS' target native window handle.
	/// @param[in] _width Window back buffer width.
	/// @param[in] _height Window back buffer height.
	/// @param[in] _depthFormat Window back buffer depth format.
	///
	/// @returns Handle to frame buffer object.
	///
	/// @remarks
	///   Frame buffer cannnot be used for sampling.
	///
	/// @attention C99 equivalent is `bgfx_create_frame_buffer_from_nwh`.
	///
	FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _depthFormat = TextureFormat::UnknownDepth);

	/// Destroy frame buffer.
	///
	/// @attention C99 equivalent is `bgfx_destroy_frame_buffer`.
	///
	void destroyFrameBuffer(FrameBufferHandle _handle);

	/// Create shader uniform parameter.
	///
	/// @param[in] _name Uniform name in shader.
	/// @param[in] _type Type of uniform (See: `bgfx::UniformType`).
	/// @param[in] _num Number of elements in array.
	///
	/// @returns Handle to uniform object.
	///
	/// @remarks
	/// Predefined uniforms (declared in `bgfx_shader.sh`):
	///   - `u_viewRect vec4(x, y, width, height)` - view rectangle for current
	///     view.
	///   - `u_viewTexel vec4(1.0/width, 1.0/height, undef, undef)` - inverse
	///     width and height
	///   - `u_view mat4` - view matrix
	///   - `u_invView mat4` - inverted view matrix
	///   - `u_proj mat4` - projection matrix
	///   - `u_invProj mat4` - inverted projection matrix
	///   - `u_viewProj mat4` - concatenated view projection matrix
	///   - `u_invViewProj mat4` - concatenated inverted view projection matrix
	///   - `u_model mat4[BGFX_CONFIG_MAX_BONES]` - array of model matrices.
	///   - `u_modelView mat4` - concatenated model view matrix, only first
	///     model matrix from array is used.
	///   - `u_modelViewProj mat4` - concatenated model view projection matrix.
	///   - `u_alphaRef float` - alpha reference value for alpha test.
	///
	/// @attention C99 equivalent is `bgfx_create_uniform`.
	///
	UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num = 1);

	/// Destroy shader uniform parameter.
	///
	/// @param[in] _handle Handle to uniform object.
	///
	/// @attention C99 equivalent is `bgfx_destroy_uniform`.
	///
	void destroyUniform(UniformHandle _handle);

	/// Set clear color palette value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _rgba Packed 32-bit RGBA value.
	///
	/// @attention C99 equivalent is `bgfx_set_clear_color`.
	///
	void setClearColor(uint8_t _index, uint32_t _rgba);

	/// Set clear color palette value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _r, _g, _b, _a RGBA floating point values.
	///
	/// @attention C99 equivalent is `bgfx_set_clear_color`.
	///
	void setClearColor(uint8_t _index, float _r, float _g, float _b, float _a);

	/// Set clear color palette value.
	///
	/// @param[in] _index Index into palette.
	/// @param[in] _rgba RGBA floating point value.
	///
	/// @attention C99 equivalent is `bgfx_set_clear_color`.
	///
	void setClearColor(uint8_t _index, const float _rgba[4]);

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
	///     "nnnce <view name>"
	///      ^  ^^ ^
	///      |  |+-- eye (L/R)
	///      |  +-- compute (C)
	///      +-- view id
	///
	/// @attention C99 equivalent is `bgfx_set_view_name`.
	///
	void setViewName(uint8_t _id, const char* _name);

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
	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

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
	void setViewScissor(uint8_t _id, uint16_t _x = 0, uint16_t _y = 0, uint16_t _width = 0, uint16_t _height = 0);

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
	void setViewClear(uint8_t _id, uint16_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	/// Set view clear flags with different clear color for each
	/// frame buffer texture. Must use setClearColor to setup clear color
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
	void setViewClear(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0 = UINT8_MAX, uint8_t _1 = UINT8_MAX, uint8_t _2 = UINT8_MAX, uint8_t _3 = UINT8_MAX, uint8_t _4 = UINT8_MAX, uint8_t _5 = UINT8_MAX, uint8_t _6 = UINT8_MAX, uint8_t _7 = UINT8_MAX);

	/// Set view into sequential mode. Draw calls will be sorted in the same
	/// order in which submit calls were called.
	///
	/// @attention C99 equivalent is `bgfx_set_view_seq`.
	///
	void setViewSeq(uint8_t _id, bool _enabled);

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
	void setViewFrameBuffer(uint8_t _id, FrameBufferHandle _handle);

	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	///
	/// @param[in] _id View id.
	/// @param[in] _view View matrix.
	/// @param[in] _projL Projection matrix. When using stereo rendering this projection matrix
	///   represent projection matrix for left eye.
	/// @param[in] _flags View flags. Use
	///   - `BGFX_VIEW_NONE` - View will be rendered only once if stereo mode is enabled.
	///   - `BGFX_VIEW_STEREO` - View will be rendered for both eyes if stereo mode is enabled. When
	///     stereo mode is disabled this flag doesn't have effect.
	/// @param[in] _projR Projection matrix for right eye in stereo mode.
	///
	/// @attention C99 equivalent are `bgfx_set_view_transform`, `bgfx_set_view_transform_stereo`.
	///
	void setViewTransform(uint8_t _id, const void* _view, const void* _projL, uint8_t _flags = BGFX_VIEW_STEREO, const void* _projR = NULL);

	/// Post submit view reordering.
	///
	/// @param[in] _id First view id.
	/// @param[in] _num Number of views to remap.
	/// @param[in] _remap View remap id table. Passing `NULL` will reset view ids
	///   to default state.
	///
	/// @attention C99 equivalent is `bgfx_set_view_remap`.
	///
	void setViewRemap(uint8_t _id = 0, uint8_t _num = UINT8_MAX, const void* _remap = NULL);

	/// Sets debug marker.
	///
	/// @attention C99 equivalent is `bgfx_set_marker`.
	///
	void setMarker(const char* _marker);

	/// Set render states for draw primitive.
	///
	/// @param[in] _state State flags. Default state for primitive type is
	///   triangles. See: `BGFX_STATE_DEFAULT`.
	///   - `BGFX_STATE_ALPHA_WRITE` - Enable alpha write.
	///   - `BGFX_STATE_DEPTH_WRITE` - Enable depth write.
	///   - `BGFX_STATE_DEPTH_TEST_*` - Depth test function.
	///   - `BGFX_STATE_BLEND_*` - See remark 1 about BGFX_STATE_BLEND_FUNC.
	///   - `BGFX_STATE_BLEND_EQUATION_*` - See remark 2.
	///   - `BGFX_STATE_CULL_*` - Backface culling mode.
	///   - `BGFX_STATE_RGB_WRITE` - Enable RGB write.
	///   - `BGFX_STATE_MSAA` - Enable MSAA.
	///   - `BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]` - Primitive type.
	///
	/// @param[in] _rgba Sets blend factor used by `BGFX_STATE_BLEND_FACTOR` and
	///   `BGFX_STATE_BLEND_INV_FACTOR` blend modes.
	///
	/// @remarks
	///   1. Use `BGFX_STATE_ALPHA_REF`, `BGFX_STATE_POINT_SIZE` and
	///      `BGFX_STATE_BLEND_FUNC` macros to setup more complex states.
	///   2. `BGFX_STATE_BLEND_EQUATION_ADD` is set when no other blend
	///      equation is specified.
	///
	/// @attention C99 equivalent is `bgfx_set_state`.
	///
	void setState(uint64_t _state, uint32_t _rgba = 0);

	/// Set stencil test state.
	///
	/// @param[in] _fstencil Front stencil state.
	/// @param[in] _bstencil Back stencil state. If back is set to `BGFX_STENCIL_NONE`
	///   _fstencil is applied to both front and back facing primitives.
	///
	/// @attention C99 equivalent is `bgfx_set_stencil`.
	///
	void setStencil(uint32_t _fstencil, uint32_t _bstencil = BGFX_STENCIL_NONE);

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
	uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set scissor from cache for draw primitive.
	///
	/// @param[in] _cache Index in scissor cache. Passing UINT16_MAX unset primitive
	///   scissor and primitive will use view scissor instead.
	///
	/// @attention C99 equivalent is `bgfx_set_scissor_cached`.
	///
	void setScissor(uint16_t _cache = UINT16_MAX);

	/// Set model matrix for draw primitive. If it is not called model will
	/// be rendered with identity model matrix.
	///
	/// @param[in] _mtx Pointer to first matrix in array.
	/// @param[in] _num Number of matrices in array.
	/// @returns index into matrix cache in case the same model matrix has
	///   to be used for other draw primitive call.
	///
	/// @attention C99 equivalent is `bgfx_set_transform`.
	///
	uint32_t setTransform(const void* _mtx, uint16_t _num = 1);

	/// Reserve `_num` matrices in internal matrix cache. Pointer returned
	/// can be modifed until `bgfx::frame` is called.
	///
	/// @param[in] _transform Pointer to `Transform` structure.
	/// @param[in] _num Number of matrices.
	/// @returns index into matrix cache.
	///
	/// @attention C99 equivalent is `bgfx_alloc_transform`.
	///
	uint32_t allocTransform(Transform* _transform, uint16_t _num);

	/// Set model matrix from matrix cache for draw primitive.
	///
	/// @param[in] _cache Index in matrix cache.
	/// @param[in] _num Number of matrices from cache.
	///
	/// @attention C99 equivalent is `bgfx_set_transform_cached`.
	///
	void setTransform(uint32_t _cache, uint16_t _num = 1);

	/// Set shader uniform parameter for draw primitive.
	///
	/// @param[in] _handle Uniform.
	/// @param[in] _value Pointer to uniform data.
	/// @param[in] _num Number of elements.
	///
	/// @attention C99 equivalent is `bgfx_set_uniform`.
	///
	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num = 1);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Index buffer.
	/// @param[in] _firstIndex First index to render.
	/// @param[in] _numIndices Number of indices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_index_buffer`.
	///
	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex = 0, uint32_t _numIndices = UINT32_MAX);

	/// Set index buffer for draw primitive.
	///
	/// @param[in] _handle Dynamic index buffer.
	/// @param[in] _firstIndex First index to render.
	/// @param[in] _numIndices Number of indices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_index_buffer`.
	///
	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex = 0, uint32_t _numIndices = UINT32_MAX);

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
	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _handle Vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_vertex_buffer`.
	///
	void setVertexBuffer(VertexBufferHandle _handle);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _handle Vertex buffer.
	/// @param[in] _startVertex First vertex to render.
	/// @param[in] _numVertices Number of vertices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_vertex_buffer`.
	///
	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _handle Dynamic vertex buffer.
	/// @param[in] _numVertices Number of vertices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_dynamic_vertex_buffer`.
	///
	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _tvb Transient vertex buffer.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_vertex_buffer`.
	///
	void setVertexBuffer(const TransientVertexBuffer* _tvb);

	/// Set vertex buffer for draw primitive.
	///
	/// @param[in] _tvb Transient vertex buffer.
	/// @param[in] _startVertex First vertex to render.
	/// @param[in] _numVertices Number of vertices to render.
	///
	/// @attention C99 equivalent is `bgfx_set_transient_vertex_buffer`.
	///
	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices);

	/// Set instance data buffer for draw primitive.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_buffer`.
	///
	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num = UINT32_MAX);

	/// Set instance data buffer for draw primitive.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_from_vertex_buffer`.
	///
	void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num);

	/// Set instance data buffer for draw primitive.
	///
	/// @attention C99 equivalent is `bgfx_set_instance_data_from_dynamic_vertex_buffer`.
	///
	void setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num);

	/// Set texture stage for draw primitive.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _sampler Program sampler.
	/// @param[in] _handle Texture handle.
	/// @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @param[in] _flags Texture sampler filtering flags. UINT32_MAX use the
	///   sampler filtering mode set by texture.
	///
	/// @attention C99 equivalent is `bgfx_set_texture`.
	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags = UINT32_MAX);

	/// Set texture stage for draw primitive.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _sampler Program sampler.
	/// @param[in] _handle Frame buffer handle.
	/// @param[in] _attachment Attachment index.
	/// @param[in] _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @attention C99 equivalent is `bgfx_set_texture_from_frame_buffer`.
	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment = 0, uint32_t _flags = UINT32_MAX);

	/// Touch view.
	uint32_t touch(uint8_t _id);

	/// Submit primitive for rendering.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Program.
	/// @param[in] _depth Depth for sorting.
	/// @returns Number of draw calls.
	///
	/// @attention C99 equivalent is `bgfx_submit`.
	///
	uint32_t submit(uint8_t _id, ProgramHandle _handle, int32_t _depth = 0);

	/// Submit primitive for rendering with index and instance data info from
	/// indirect buffer.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Program.
	/// @param[in] _indirectHandle Indirect buffer.
	/// @param[in] _start First element in indirect buffer.
	/// @param[in] _num Number of dispatches.
	/// @param[in] _depth Depth for sorting.
	///
	/// @attention C99 equivalent is `bgfx_submit_indirect`.
	///
	uint32_t submit(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1, int32_t _depth = 0);

	/// Set compute index buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Index buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_index_buffer`.
	///
	void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access);

	/// Set compute vertex buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Vertex buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_vertex_buffer`.
	///
	void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access);

	/// Set compute dynamic index buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Dynamic index buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_dynamic_index_buffer`.
	///
	void setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access);

	/// Set compute dynamic vertex buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Dynamic vertex buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_dynamic_vertex_buffer`.
	///
	void setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access);

	/// Set compute indirect buffer.
	///
	/// @param[in] _stage Compute stage.
	/// @param[in] _handle Indirect buffer handle.
	/// @param[in] _access Buffer access. See `Access::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_compute_indirect_buffer`.
	///
	void setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access);

	/// Set compute image from texture.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _sampler Program sampler.
	/// @param[in] _handle Texture handle.
	/// @param[in] _mip Mip level.
	/// @param[in] _access Texture access. See `Access::Enum`.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_image`.
	///
	void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format = TextureFormat::Count);

	/// Set compute image from frame buffer texture.
	///
	/// @param[in] _stage Texture unit.
	/// @param[in] _sampler Program sampler.
	/// @param[in] _handle Frame buffer handle.
	/// @param[in] _attachment Attachment index.
	/// @param[in] _access Texture access. See `Access::Enum`.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	///
	/// @attention C99 equivalent is `bgfx_set_image_from_frame_buffer`.
	///
	void setImage(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, Access::Enum _access, TextureFormat::Enum _format = TextureFormat::Count);

	/// Dispatch compute.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Compute program.
	/// @param[in] _numX Number of groups X.
	/// @param[in] _numY Number of groups Y.
	/// @param[in] _numZ Number of groups Z.
	/// @param[in] _flags View flags. Use
	///   - `BGFX_VIEW_NONE` - View will be rendered only once if stereo mode is enabled.
	///   - `BGFX_VIEW_STEREO` - View will be rendered for both eyes if stereo mode is enabled. When
	///     stereo mode is disabled this flag doesn't have effect.
	///
	/// @attention C99 equivalent is `bgfx_dispatch`.
	///
	uint32_t dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _numX = 1, uint16_t _numY = 1, uint16_t _numZ = 1, uint8_t _flags = BGFX_SUBMIT_EYE_FIRST);

	/// Dispatch compute indirect.
	///
	/// @param[in] _id View id.
	/// @param[in] _handle Compute program.
	/// @param[in] _indirectHandle Indirect buffer.
	/// @param[in] _start First element in indirect buffer.
	/// @param[in] _num Number of dispatches.
	/// @param[in] _flags View flags. Use
	///   - `BGFX_VIEW_NONE` - View will be rendered only once if stereo mode is enabled.
	///   - `BGFX_VIEW_STEREO` - View will be rendered for both eyes if stereo mode is enabled. When
	///     stereo mode is disabled this flag doesn't have effect.
	///
	/// @attention C99 equivalent is `bgfx_dispatch_indirect`.
	///
	uint32_t dispatch(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1, uint8_t _flags = BGFX_SUBMIT_EYE_FIRST);

	/// Discard all previously set state for draw or compute call.
	///
	/// @attention C99 equivalent is `bgfx_discard`.
	///
	void discard();

	/// Request screen shot.
	///
	/// @param[in] _filePath Will be passed to `bgfx::CallbackI::screenShot` callback.
	///
	/// @remarks
	///   `bgfx::CallbackI::screenShot` must be implemented.
	///
	/// @attention C99 equivalent is `bgfx_save_screen_shot`.
	///
	void saveScreenShot(const char* _filePath);

} // namespace bgfx

#endif // BGFX_H_HEADER_GUARD

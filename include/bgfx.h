/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_H_HEADER_GUARD
#define BGFX_H_HEADER_GUARD

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
	struct Fatal
	{
		enum Enum
		{
			DebugCheck,
			MinimumRequiredSpecs,
			InvalidShader,
			UnableToInitialize,
			UnableToCreateTexture,
		};
	};

	struct RendererType
	{
		enum Enum
		{
			Null,
			Direct3D9,
			Direct3D11,
			OpenGLES,
			OpenGL,

			Count
		};
	};

	struct Access
	{
		enum Enum
		{
			Read,
			Write,
			ReadWrite,

			Count
		};
	};

	struct Attrib
	{
		enum Enum // corresponds to vertex shader attribute:
		{
			Position,  // a_position
			Normal,    // a_normal
			Tangent,   // a_tangent
			Color0,    // a_color0
			Color1,    // a_color1
			Indices,   // a_indices
			Weight,    // a_weight
			TexCoord0, // a_texcoord0
			TexCoord1, // a_texcoord1
			TexCoord2, // a_texcoord2
			TexCoord3, // a_texcoord3
			TexCoord4, // a_texcoord4
			TexCoord5, // a_texcoord5
			TexCoord6, // a_texcoord6
			TexCoord7, // a_texcoord7

			Count
		};
	};

	struct AttribType
	{
		enum Enum
		{
			Uint8,
			Int16,
			Half, // Availability depends on: BGFX_CAPS_VERTEX_ATTRIB_HALF.
			Float,

			Count
		};
	};

	struct TextureFormat
	{
		// Availability depends on Caps (see: formats).
		enum Enum
		{
			BC1,    // DXT1
			BC2,    // DXT3
			BC3,    // DXT5
			BC4,    // LATC1/ATI1
			BC5,    // LATC2/ATI2
			BC6H,   // BC6H
			BC7,    // BC7
			ETC1,   // ETC1 RGB8
			ETC2,   // ETC2 RGB8
			ETC2A,  // ETC2 RGBA8
			ETC2A1, // ETC2 RGB8A1
			PTC12,  // PVRTC1 RGB 2BPP
			PTC14,  // PVRTC1 RGB 4BPP
			PTC12A, // PVRTC1 RGBA 2BPP
			PTC14A, // PVRTC1 RGBA 4BPP
			PTC22,  // PVRTC2 RGBA 2BPP
			PTC24,  // PVRTC2 RGBA 4BPP

			Unknown, // compressed formats above

			R8,
			R16,
			R16F,
			R32,
			R32F,
			RG8,
			RG16,
			RG16F,
			RG32,
			RG32F,
			BGRA8,
			RGBA16,
			RGBA16F,
			RGBA32,
			RGBA32F,
			R5G6B5,
			RGBA4,
			RGB5A1,
			RGB10A2,

			UnknownDepth, // depth formats below

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

	struct UniformType
	{
		enum Enum
		{
			Uniform1i,
			Uniform1f,
			End,

			Uniform1iv,
			Uniform1fv,
			Uniform2fv,
			Uniform3fv,
			Uniform4fv,
			Uniform3x3fv,
			Uniform4x4fv,

			Count
		};
	};

	static const uint16_t invalidHandle = UINT16_MAX;

	BGFX_HANDLE(DynamicIndexBufferHandle);
	BGFX_HANDLE(DynamicVertexBufferHandle);
	BGFX_HANDLE(FrameBufferHandle);
	BGFX_HANDLE(IndexBufferHandle);
	BGFX_HANDLE(ProgramHandle);
	BGFX_HANDLE(ShaderHandle);
	BGFX_HANDLE(TextureHandle);
	BGFX_HANDLE(UniformHandle);
	BGFX_HANDLE(VertexBufferHandle);
	BGFX_HANDLE(VertexDeclHandle);

	/// Callback interface to implement application specific behavior.
	/// Cached items are currently used only for OpenGL binary shaders.
	///
	/// NOTE:
	///   'fatal' callback can be called from any thread. Other callbacks
	///   are called from the render thread.
	///
	struct CallbackI
	{
		virtual ~CallbackI() = 0;

		/// If fatal code code is not Fatal::DebugCheck this callback is
		/// called on unrecoverable error. It's not safe to continue, inform
		/// user and terminate application from this call.
		virtual void fatal(Fatal::Enum _code, const char* _str) = 0;

		/// Return size of for cached item. Return 0 if no cached item was
		/// found.
		virtual uint32_t cacheReadSize(uint64_t _id) = 0;

		/// Read cached item.
		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) = 0;

		/// Write cached item.
		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) = 0;

		/// Screenshot captured. Screenshot format is always 4-byte BGRA.
		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) = 0;

		/// Called when capture begins.
		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format, bool _yflip) = 0;

		/// Called when capture ends.
		virtual void captureEnd() = 0;

		/// Captured frame.
		virtual void captureFrame(const void* _data, uint32_t _size) = 0;
	};

	inline CallbackI::~CallbackI()
	{
	}

	struct Memory
	{
		uint8_t* data;
		uint32_t size;
	};

	/// Renderer capabilities.
	struct Caps
	{
		/// Renderer backend type.
		RendererType::Enum rendererType;

		/// Supported functionality, it includes emulated functionality.
		/// Checking supported and not emulated will give functionality
		/// natively supported by renderer.
		uint64_t supported;

		/// Emulated functionality. For example some texture compression
		/// modes are not natively supported by all renderers. The library
		/// internally decompresses texture into supported format.
		uint64_t emulated;

		uint16_t maxTextureSize;   ///< Maximum texture size.
		uint16_t maxDrawCalls;     ///< Maximum draw calls.
		uint8_t  maxFBAttachments; ///< Maximum frame buffer attachments.

		/// Supported texture formats.
		///   0 - not supported
		///   1 - supported
		///   2 - emulated
		uint8_t formats[TextureFormat::Count];
	};

	struct TransientIndexBuffer
	{
		uint8_t* data;
		uint32_t size;
		IndexBufferHandle handle;
		uint32_t startIndex;
	};

	struct TransientVertexBuffer
	{
		uint8_t* data;
		uint32_t size;
		uint32_t startVertex;
		uint16_t stride;
		VertexBufferHandle handle;
		VertexDeclHandle decl;
	};

	struct InstanceDataBuffer
	{
		uint8_t* data;
		uint32_t size;
		uint32_t offset;
		uint16_t stride;
		uint16_t num;
		VertexBufferHandle handle;
	};

	struct TextureInfo
	{
		TextureFormat::Enum format;
		uint32_t storageSize;
		uint16_t width;
		uint16_t height;
		uint16_t depth;
		uint8_t numMips;
		uint8_t bitsPerPixel;
	};

	/// Vertex declaration.
	struct VertexDecl
	{
		/// Start VertexDecl.
		VertexDecl& begin(RendererType::Enum _renderer = RendererType::Null);

		/// End VertexDecl.
		void end();

		/// Add attribute to VertexDecl.
		///
		/// @param _attrib Attribute semantics.
		/// @param _num Number of elements 1, 2, 3 or 4.
		/// @param _type Element type.
		/// @param _normalized When using fixed point AttribType (f.e. Uint8)
		///   value will be normalized for vertex shader usage. When normalized
		///   is set to true, AttribType::Uint8 value in range 0-255 will be
		///   in range 0.0-1.0 in vertex shader.
		/// @param _asInt Packaging rule for vertexPack, vertexUnpack, and
		///   vertexConvert for AttribType::Uint8 and AttribType::Int16.
		///   Unpacking code must be implemented inside vertex shader.
		///
		/// NOTE:
		///   Must be called between begin/end.
		///
		VertexDecl& add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized = false, bool _asInt = false);

		/// Skip _num bytes in vertex stream.
		VertexDecl& skip(uint8_t _num);

		/// Decode attribute.
		void decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized, bool& _asInt) const;

		/// Returns true if VertexDecl contains attribute.
		bool has(Attrib::Enum _attrib) const { return 0xff != m_attributes[_attrib]; }

		/// Returns relative attribute offset from the vertex.
		uint16_t getOffset(Attrib::Enum _attrib) const { return m_offset[_attrib]; }

		/// Returns vertex stride.
		uint16_t getStride() const { return m_stride; }

		/// Returns size of vertex buffer for number of vertices.
		uint32_t getSize(uint32_t _num) const { return _num*m_stride; }

		uint32_t m_hash;
		uint16_t m_stride;
		uint16_t m_offset[Attrib::Count];
		uint8_t m_attributes[Attrib::Count];
	};

	/// Pack vec4 into vertex stream format.
	void vertexPack(const float _input[4], bool _inputNormalized, Attrib::Enum _attr, const VertexDecl& _decl, void* _data, uint32_t _index = 0);

	/// Unpack vec4 from vertex stream format.
	void vertexUnpack(float _output[4], Attrib::Enum _attr, const VertexDecl& _decl, const void* _data, uint32_t _index = 0);

	/// Converts vertex stream data from one vertex stream format to another.
	///
	/// @param _destDecl Destination vertex stream declaration.
	/// @param _destData Destination vertex stream.
	/// @param _srcDecl Source vertex stream declaration.
	/// @param _srcData Source vertex stream data.
	/// @param _num Number of vertices to convert from source to destination.
	///
	void vertexConvert(const VertexDecl& _destDecl, void* _destData, const VertexDecl& _srcDecl, const void* _srcData, uint32_t _num = 1);

	/// Weld vertices.
	///
	/// @param _output Welded vertices remapping table. The size of buffer
	///   must be the same as number of vertices.
	/// @param _decl Vertex stream declaration.
	/// @param _data Vertex stream.
	/// @param _num Number of vertices in vertex stream.
	/// @param _epsilon Error tolerance for vertex position comparison.
	/// @returns Number of unique vertices after vertex welding.
	///
	uint16_t weldVertices(uint16_t* _output, const VertexDecl& _decl, const void* _data, uint16_t _num, float _epsilon = 0.001f);

	/// Swizzle RGBA8 image to BGRA8.
	///
	/// @param _width Width of input image (pixels).
	/// @param _height Height of input image (pixels).
	/// @param _pitch Pitch of input image (bytes).
	/// @param _src Source image.
	/// @param _dst Destination image. Must be the same size as input image.
	///   _dst might be pointer to the same memory as _src.
	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	/// Downsample RGBA8 image with 2x2 pixel average filter.
	///
	/// @param _width Width of input image (pixels).
	/// @param _height Height of input image (pixels).
	/// @param _pitch Pitch of input image (bytes).
	/// @param _src Source image.
	/// @param _dst Destination image. Must be at least quarter size of
	///   input image. _dst might be pointer to the same memory as _src.
	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	/// Returns supported backend API renderers.
	uint8_t getSupportedRenderers(RendererType::Enum _enum[RendererType::Count]);

	/// Returns name of renderer.
	const char* getRendererName(RendererType::Enum _type);

	/// Initialize bgfx library.
	///
	/// @param _type Select rendering backend. When set to RendererType::Count
	///   default rendering backend will be selected.
	///
	/// @param _callback Provide application specific callback interface.
	///   See: CallbackI
	///
	/// @param _reallocator Custom allocator. When custom allocator is not
	///   specified, library uses default CRT allocator. The library assumes
	///   custom allocator is thread safe.
	///
	void init(RendererType::Enum _type = RendererType::Count, CallbackI* _callback = NULL, bx::ReallocatorI* _reallocator = NULL);

	/// Shutdown bgfx library.
	void shutdown();

	/// Reset graphic settings.
	void reset(uint32_t _width, uint32_t _height, uint32_t _flags = BGFX_RESET_NONE);

	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	///
	/// @returns Current frame number. This might be used in conjunction with
	///   double/multi buffering data outside the library and passing it to
	///   library via makeRef calls.
	///
	uint32_t frame();

	/// Returns current renderer backend API type.
	///
	/// NOTE:
	///   Library must be initialized.
	///
	RendererType::Enum getRendererType();

	/// Returns renderer capabilities.
	///
	/// NOTE:
	///   Library must be initialized.
	///
	const Caps* getCaps();

	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	const Memory* alloc(uint32_t _size);

	/// Allocate buffer and copy data into it. Data will be freed inside bgfx.
	const Memory* copy(const void* _data, uint32_t _size);

	/// Make reference to data to pass to bgfx. Unlike bgfx::alloc this call
	/// doesn't allocate memory for data. It just copies pointer to data.
	/// You must make sure data is available for at least 2 bgfx::frame calls.
	const Memory* makeRef(const void* _data, uint32_t _size);

	/// Set debug flags.
	///
	/// @param _debug Available flags:
	///
	///   BGFX_DEBUG_IFH - Infinitely fast hardware. When this flag is set
	///     all rendering calls will be skipped. It's useful when profiling
	///     to quickly assess bottleneck between CPU and GPU.
	///
	///   BGFX_DEBUG_STATS - Display internal statistics.
	///
	///   BGFX_DEBUG_TEXT - Display debug text.
	///
	///   BGFX_DEBUG_WIREFRAME - Wireframe rendering. All rendering
	///     primitives will be rendered as lines.
	///
	void setDebug(uint32_t _debug);

	/// Clear internal debug text buffer.
	void dbgTextClear(uint8_t _attr = 0, bool _small = false);

	/// Print into internal debug text buffer.
	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...);

	/// Create static index buffer.
	///
	/// NOTE:
	///   Only 16-bit index buffer is supported.
	///
	IndexBufferHandle createIndexBuffer(const Memory* _mem);

	/// Destroy static index buffer.
	void destroyIndexBuffer(IndexBufferHandle _handle);

	/// Create static vertex buffer.
	///
	/// @param _mem Vertex buffer data.
	/// @param _decl Vertex declaration.
	/// @returns Static vertex buffer handle.
	///
	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl);

	/// Destroy static vertex buffer.
	///
	/// @param _handle Static vertex buffer handle.
	///
	void destroyVertexBuffer(VertexBufferHandle _handle);

	/// Create empty dynamic index buffer.
	///
	/// @param _num Number of indices.
	///
	/// NOTE:
	///   Only 16-bit index buffer is supported.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num);

	/// Create dynamic index buffer and initialized it.
	///
	/// @param _mem Index buffer data.
	///
	/// NOTE:
	///   Only 16-bit index buffer is supported.
	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem);

	/// Update dynamic index buffer.
	///
	/// @param _handle Dynamic index buffer handle.
	/// @param _mem Index buffer data.
	///
	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem);

	/// Destroy dynamic index buffer.
	///
	/// @param _handle Dynamic index buffer handle.
	///
	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle);

	/// Create empty dynamic vertex buffer.
	///
	/// @param _num Number of vertices.
	/// @param _decl Vertex declaration.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	/// Create dynamic vertex buffer and initialize it.
	///
	/// @param _mem Vertex buffer data.
	/// @param _decl Vertex declaration.
	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl);

	/// Update dynamic vertex buffer.
	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, const Memory* _mem);

	/// Destroy dynamic vertex buffer.
	void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle);

	/// Returns true if internal transient index buffer has enough space.
	///
	/// @param _num Number of indices.
	///
	bool checkAvailTransientIndexBuffer(uint32_t _num);

	/// Returns true if internal transient vertex buffer has enough space.
	///
	/// @param _num Number of vertices.
	/// @param _decl Vertex declaration.
	///
	bool checkAvailTransientVertexBuffer(uint32_t _num, const VertexDecl& _decl);

	/// Returns true if internal instance data buffer has enough space.
	///
	/// @param _num Number of instances.
	/// @param _stride Stride per instance.
	///
	bool checkAvailInstanceDataBuffer(uint32_t _num, uint16_t _stride);

	/// Returns true if both internal transient index and vertex buffer have
	/// enough space.
	///
	/// @param _numVertices Number of vertices.
	/// @param _decl Vertex declaration.
	/// @param _numIndices Number of indices.
	///
	bool checkAvailTransientBuffers(uint32_t _numVertices, const VertexDecl& _decl, uint32_t _numIndices);

	/// Allocate transient index buffer.
	///
	/// @param[out] _tib TransientIndexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param _num Number of indices to allocate.
	///
	/// NOTE:
	///   1. You must call setIndexBuffer after alloc in order to avoid memory
	///      leak.
	///   2. Only 16-bit index buffer is supported.
	///
	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num);

	/// Allocate transient vertex buffer.
	///
	/// @param[out] _tvb TransientVertexBuffer structure is filled and is valid
	///   for the duration of frame, and it can be reused for multiple draw
	///   calls.
	/// @param _num Number of vertices to allocate.
	/// @param _decl Vertex declaration.
	///
	/// NOTE:
	///   You must call setVertexBuffer after alloc in order to avoid memory
	///   leak.
	///
	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexDecl& _decl);

	/// Check for required space and allocate transient vertex and index
	/// buffers. If both space requirements are satisfied function returns
	/// true.
	///
	/// NOTE:
	///   Only 16-bit index buffer is supported.
	///
	bool allocTransientBuffers(TransientVertexBuffer* _tvb, const VertexDecl& _decl, uint16_t _numVertices, TransientIndexBuffer* _tib, uint16_t _numIndices);

	/// Allocate instance data buffer.
	///
	/// NOTE:
	///   You must call setInstanceDataBuffer after alloc in order to avoid
	///   memory leak.
	///
	const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride);

	/// Create shader from memory buffer.
	ShaderHandle createShader(const Memory* _mem);

	/// Returns num of uniforms, and uniform handles used inside shader.
	///
	/// @param _handle Shader handle.
	/// @param _uniforms UniformHandle array where data will be stored.
	/// @param _max Maximum capacity of array.
	/// @returns Number of uniforms used by shader.
	///
	/// NOTE:
	///   Only non-predefined uniforms are returned.
	///
	uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms = NULL, uint16_t _max = 0);

	/// Destroy shader. Once program is created with shader it is safe to
	/// destroy shader.
	void destroyShader(ShaderHandle _handle);

	/// Create program with vertex and fragment shaders.
	///
	/// @param _vsh Vertex shader.
	/// @param _fsh Fragment shader.
	/// @param _destroyShaders If true, shaders will be destroyed when
	///   program is destroyed.
	/// @returns Program handle if vertex shader output and fragment shader
	///   input are matching, otherwise returns invalid program handle.
	///
	ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders = false);

	/// Destroy program.
	void destroyProgram(ProgramHandle _handle);

	/// Calculate amount of memory required for texture.
	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format);

	/// Create texture from memory buffer.
	///
	/// @param _mem DDS, KTX or PVR texture data.
	/// @param _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///
	///   BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
	///     mode.
	///
	///   BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
	///     sampling.
	///
	/// @param _skip Skip top level mips when parsing texture.
	/// @param _info Returns parsed texture information.
	/// @returns Texture handle.
	///
	TextureHandle createTexture(const Memory* _mem, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, TextureInfo* _info = NULL);

	/// Create 2D texture.
	///
	/// @param _width
	/// @param _height
	/// @param _numMips
	/// @param _format
	/// @param _flags
	/// @param _mem
	///
	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create 3D texture.
	///
	/// @param _width
	/// @param _height
	/// @param _depth
	/// @param _numMips
	/// @param _format
	/// @param _flags
	/// @param _mem
	///
	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create Cube texture.
	///
	/// @param _size
	/// @param _numMips
	/// @param _format
	/// @param _flags
	/// @param _mem
	///
	TextureHandle createTextureCube(uint16_t _size, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Update 2D texture.
	///
	/// @param _handle
	/// @param _mip
	/// @param _x
	/// @param _y
	/// @param _width
	/// @param _height
	/// @param _mem
	/// @param _pitch Pitch of input image (bytes). When _pitch is set to
	///   UINT16_MAX, it will be calculated internally based on _width.
	///
	void updateTexture2D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch = UINT16_MAX);

	/// Update 3D texture.
	///
	/// @param _handle
	/// @param _mip
	/// @param _x
	/// @param _y
	/// @param _z
	/// @param _width
	/// @param _height
	/// @param _depth
	/// @param _mem
	///
	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem);

	/// Update Cube texture.
	///
	/// @param _handle
	/// @param _side Cubemap side, where 0 is +X, 1 is -X, 2 is +Y, 3 is
	///   -Y, 4 is +Z, and 5 is -Z.
	///
	///              +----------+
	///              |-z       2|
	///              | ^  +y    |
	///              | |        |
	///              | +---->+x |
	///   +----------+----------+----------+----------+
	///   |+y       1|+y       4|+y       0|+y       5|
	///   | ^  -x    | ^  +z    | ^  +x    | ^  -z    |
	///   | |        | |        | |        | |        |
	///   | +---->+z | +---->+x | +---->-z | +---->-x |
	///   +----------+----------+----------+----------+
	///              |+z       3|
	///              | ^  -y    |
	///              | |        |
	///              | +---->+x |
	///              +----------+
	///
	/// @param _mip
	/// @param _x
	/// @param _y
	/// @param _width
	/// @param _height
	/// @param _mem
	/// @param _pitch Pitch of input image (bytes). When _pitch is set to
	///   UINT16_MAX, it will be calculated internally based on _width.
	///
	void updateTextureCube(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch = UINT16_MAX);

	/// Destroy texture.
	void destroyTexture(TextureHandle _handle);

	/// Create frame buffer (simple).
	///
	/// @param _width Texture width.
	/// @param _height Texture height.
	/// @param _format Texture format.
	/// @param _textureFlags Texture flags.
	///
	FrameBufferHandle createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	/// Create frame buffer.
	///
	/// @param _num Number of texture attachments.
	/// @param _handles Texture attachments.
	/// @param _destroyTextures If true, textures will be destroyed when 
	///   frame buffer is destroyed.
	///
	FrameBufferHandle createFrameBuffer(uint8_t _num, TextureHandle* _handles, bool _destroyTextures = false);

	/// Destroy frame buffer.
	void destroyFrameBuffer(FrameBufferHandle _handle);

	/// Create shader uniform parameter.
	///
	/// @param _name Uniform name in shader.
	/// @param _type Type of uniform (See: UniformType).
	/// @param _num Number of elements in array.
	///
	/// Predefined uniforms:
	///
	///   u_viewRect vec4(x, y, width, height) - view rectangle for current
	///     view.
	///
	///   u_viewTexel vec4(1.0/width, 1.0/height, undef, undef) - inverse
	///     width and height
	///
	///   u_view mat4 - view matrix
	///
	///   u_invView mat4 - inverted view matrix
	///
	///   u_proj mat4 - projection matrix
	///
	///   u_invProj mat4 - inverted projection matrix
	///
	///   u_viewProj mat4 - concatenated view projection matrix
	///
	///   u_invViewProj mat4 - concatenated inverted view projection matrix
	///
	///   u_model mat4[BGFX_CONFIG_MAX_BONES] - array of model matrices.
	///
	///   u_modelView mat4 - concatenated model view matrix, only first
	///     model matrix from array is used.
	///
	///   u_modelViewProj mat4 - concatenated model view projection matrix.
	///
	///   u_alphaRef float - alpha reference value for alpha test.
	///
	UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num = 1);

	/// Destroy shader uniform parameter.
	void destroyUniform(UniformHandle _handle);

	/// Set view name.
	///
	/// @param _id View id.
	/// @param _name View name.
	///
	/// NOTE:
	///   This is debug only feature.
	///
	void setViewName(uint8_t _id, const char* _name);

	/// Set view rectangle. Draw primitive outside view will be clipped.
	///
	/// @param _id View id.
	/// @param _x Position x from the left corner of the window.
	/// @param _y Position y from the top corner of the window.
	/// @param _width Width of view port region.
	/// @param _height Height of view port region.
	///
	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set view rectangle for multiple views.
	///
	/// @param _viewMask Bit mask representing affected views.
	/// @param _x Position x from the left corner of the window.
	/// @param _y Position y from the top corner of the window.
	/// @param _width Width of view port region.
	/// @param _height Height of view port region.
	///
	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set view scissor. Draw primitive outside view will be clipped. When
	/// _x, _y, _width and _height are set to 0, scissor will be disabled.
	///
	/// @param _x Position x from the left corner of the window.
	/// @param _y Position y from the top corner of the window.
	/// @param _width Width of scissor region.
	/// @param _height Height of scissor region.
	///
	void setViewScissor(uint8_t _id, uint16_t _x = 0, uint16_t _y = 0, uint16_t _width = 0, uint16_t _height = 0);

	/// Set view scissor for multiple views. When _x, _y, _width and _height
	/// are set to 0, scissor will be disabled.
	///
	/// @param _id View id.
	/// @param _viewMask Bit mask representing affected views.
	/// @param _x Position x from the left corner of the window.
	/// @param _y Position y from the top corner of the window.
	/// @param _width Width of scissor region.
	/// @param _height Height of scissor region.
	///
	void setViewScissorMask(uint32_t _viewMask, uint16_t _x = 0, uint16_t _y = 0, uint16_t _width = 0, uint16_t _height = 0);

	/// Set view clear flags.
	///
	/// @param _id View id.
	/// @param _flags Clear flags. Use BGFX_CLEAR_NONE to remove any clear
	///   operation. See: BGFX_CLEAR_*.
	/// @param _rgba Color clear value.
	/// @param _depth Depth clear value.
	/// @param _stencil Stencil clear value.
	///
	void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	/// Set view clear flags for multiple views.
	void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	/// Set view into sequential mode. Draw calls will be sorted in the same
	/// order in which submit calls were called.
	void setViewSeq(uint8_t _id, bool _enabled);

	/// Set multiple views into sequential mode.
	void setViewSeqMask(uint32_t _viewMask, bool _enabled);

	/// Set view frame buffer.
	///
	/// @param _id View id.
	/// @param _handle Frame buffer handle. Passing BGFX_INVALID_HANDLE as
	///   frame buffer handle will draw primitives from this view into
	///   default back buffer.
	///
	void setViewFrameBuffer(uint8_t _id, FrameBufferHandle _handle);

	/// Set view frame buffer for multiple views.
	///
	/// @param _viewMask View mask.
	/// @param _handle Frame buffer handle. Passing BGFX_INVALID_HANDLE as
	///   frame buffer handle will draw primitives from this view into
	///   default back buffer.
	///
	void setViewFrameBufferMask(uint32_t _viewMask, FrameBufferHandle _handle);

	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	void setViewTransform(uint8_t _id, const void* _view, const void* _proj);

	/// Set view view and projection matrices for multiple views.
	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj);

	/// Sets debug marker.
	void setMarker(const char* _marker);

	/// Set render states for draw primitive.
	///
	/// @param _state State flags. Default state for primitive type is
	///   triangles. See: BGFX_STATE_DEFAULT.
	///
	///   BGFX_STATE_ALPHA_WRITE - Enable alpha write.
	///   BGFX_STATE_DEPTH_WRITE - Enable depth write.
	///   BGFX_STATE_DEPTH_TEST_* - Depth test function.
	///   BGFX_STATE_BLEND_* - See NOTE 1: BGFX_STATE_BLEND_FUNC.
	///   BGFX_STATE_BLEND_EQUATION_* - See NOTE 2.
	///   BGFX_STATE_CULL_* - Backface culling mode.
	///   BGFX_STATE_RGB_WRITE - Enable RGB write.
	///   BGFX_STATE_MSAA - Enable MSAA.
	///   BGFX_STATE_PT_[LINES/POINTS] - Primitive type.
	///
	/// @param _rgba Sets blend factor used by BGFX_STATE_BLEND_FACTOR and
	///   BGFX_STATE_BLEND_INV_FACTOR blend modes.
	///
	/// NOTE:
	///   1. Use BGFX_STATE_ALPHA_REF, BGFX_STATE_POINT_SIZE and
	///      BGFX_STATE_BLEND_FUNC macros to setup more complex states.
	///   2. BGFX_STATE_BLEND_EQUATION_ADD is set when no other blend
	///      equation is specified.
	///
	void setState(uint64_t _state, uint32_t _rgba = 0);

	/// Set stencil test state.
	///
	/// @param _fstencil Front stencil state.
	/// @param _bstencil Back stencil state. If back is set to BGFX_STENCIL_NONE
	///   _fstencil is applied to both front and back facing primitives.
	///
	void setStencil(uint32_t _fstencil, uint32_t _bstencil = BGFX_STENCIL_NONE);

	/// Set scissor for draw primitive. For scissor for all primitives in
	/// view see setViewScissor.
	///
	/// @param _x Position x from the left corner of the window.
	/// @param _y Position y from the top corner of the window.
	/// @param _width Width of scissor region.
	/// @param _height Height of scissor region.
	/// @returns Scissor cache index.
	///
	uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set scissor from cache for draw primitive.
	///
	/// @param _cache Index in scissor cache. Passing UINT16_MAX unset primitive
	///   scissor and primitive will use view scissor instead.
	///
	void setScissor(uint16_t _cache = UINT16_MAX);

	/// Set model matrix for draw primitive. If it is not called model will
	/// be rendered with identity model matrix.
	///
	/// @param _mtx Pointer to first matrix in array.
	/// @param _num Number of matrices in array.
	/// @returns index into matrix cache in case the same model matrix has
	///   to be used for other draw primitive call.
	///
	uint32_t setTransform(const void* _mtx, uint16_t _num = 1);

	/// Set model matrix from matrix cache for draw primitive.
	///
	/// @param _cache Index in matrix cache.
	/// @param _num Number of matrices from cache.
	///
	void setTransform(uint32_t _cache, uint16_t _num = 1);

	/// Set shader uniform parameter for draw primitive.
	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num = 1);

	/// Set index buffer for draw primitive.
	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex = 0, uint32_t _numIndices = UINT32_MAX);

	/// Set index buffer for draw primitive.
	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex = 0, uint32_t _numIndices = UINT32_MAX);

	/// Set index buffer for draw primitive.
	void setIndexBuffer(const TransientIndexBuffer* _tib);

	/// Set index buffer for draw primitive.
	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(VertexBufferHandle _handle);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(const TransientVertexBuffer* _tvb);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices);

	/// Set instance data buffer for draw primitive.
	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint16_t _num = UINT16_MAX);

	/// Set program for draw primitive.
	void setProgram(ProgramHandle _handle);

	/// Set texture stage for draw primitive.
	///
	/// @param _stage Texture unit.
	/// @param _sampler Program sampler.
	/// @param _handle Texture handle.
	/// @param _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///
	///   BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
	///     mode.
	///
	///   BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
	///     sampling.
	///
	/// @param _flags Texture sampler filtering flags. UINT32_MAX use the
	///   sampler filtering mode set by texture.
	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags = UINT32_MAX);

	/// Set texture stage for draw primitive.
	///
	/// @param _stage Texture unit.
	/// @param _sampler Program sampler.
	/// @param _handle Frame buffer handle.
	/// @param _attachment Attachment index.
	/// @param _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///
	///   BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
	///     mode.
	///
	///   BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
	///     sampling.
	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment = 0, uint32_t _flags = UINT32_MAX);

	/// Submit primitive for rendering into single view.
	///
	/// @param _id View id.
	/// @param _depth Depth for sorting.
	/// @returns Number of draw calls.
	///
	uint32_t submit(uint8_t _id, int32_t _depth = 0);

	/// Submit primitive for rendering into multiple views.
	///
	/// @param _viewMask Mask to which views to submit draw primitive calls.
	/// @param _depth Depth for sorting.
	/// @returns Number of draw calls.
	///
	uint32_t submitMask(uint32_t _viewMask, int32_t _depth = 0);

	///
	void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, TextureFormat::Enum _format, Access::Enum _access);

	///
	void setImage(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, TextureFormat::Enum _format, Access::Enum _access);

	/// Dispatch compute.
	void dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _numX = 1, uint16_t _numY = 1, uint16_t _numZ = 1);

	/// Discard all previously set state for draw or compute call.
	void discard();

	/// Request screen shot.
	///
	/// @param _filePath Will be passed to CallbackI::screenShot callback.
	///
	/// NOTE:
	///   CallbackI::screenShot must be implemented.
	///
	void saveScreenShot(const char* _filePath);

} // namespace bgfx

#endif // BGFX_H_HEADER_GUARD

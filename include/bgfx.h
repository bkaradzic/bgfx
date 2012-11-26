/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFX_H__
#define __BGFX_H__

#include <stdint.h> // uint32_t
#include <stdlib.h> // size_t

///
#define BGFX_STATE_DEPTH_WRITE          UINT64_C(0x0000000000000001)

#define BGFX_STATE_ALPHA_TEST           UINT64_C(0x0000000000000004)
#define BGFX_STATE_ALPHA_WRITE          UINT64_C(0x0000000000000008)
#define BGFX_STATE_ALPHA_MASK           UINT64_C(0x000000000000000c)

#define BGFX_STATE_DEPTH_TEST_LESS      UINT64_C(0x0000000000000010)
#define BGFX_STATE_DEPTH_TEST_LEQUAL    UINT64_C(0x0000000000000020)
#define BGFX_STATE_DEPTH_TEST_EQUAL     UINT64_C(0x0000000000000030)
#define BGFX_STATE_DEPTH_TEST_GEQUAL    UINT64_C(0x0000000000000040)
#define BGFX_STATE_DEPTH_TEST_GREATER   UINT64_C(0x0000000000000050)
#define BGFX_STATE_DEPTH_TEST_NOTEQUAL  UINT64_C(0x0000000000000060)
#define BGFX_STATE_DEPTH_TEST_NEVER     UINT64_C(0x0000000000000070)
#define BGFX_STATE_DEPTH_TEST_ALWAYS    UINT64_C(0x0000000000000080)
#define BGFX_STATE_DEPTH_TEST_SHIFT     4
#define BGFX_STATE_DEPTH_TEST_MASK      UINT64_C(0x00000000000000f0)

#define BGFX_STATE_ALPHA_TEST_LESS      UINT64_C(0x0000000000000100)
#define BGFX_STATE_ALPHA_TEST_LEQUAL    UINT64_C(0x0000000000000200)
#define BGFX_STATE_ALPHA_TEST_EQUAL     UINT64_C(0x0000000000000300)
#define BGFX_STATE_ALPHA_TEST_GEQUAL    UINT64_C(0x0000000000000400)
#define BGFX_STATE_ALPHA_TEST_GREATER   UINT64_C(0x0000000000000500)
#define BGFX_STATE_ALPHA_TEST_NOTEQUAL  UINT64_C(0x0000000000000600)
#define BGFX_STATE_ALPHA_TEST_NEVER     UINT64_C(0x0000000000000700)
#define BGFX_STATE_ALPHA_TEST_ALWAYS    UINT64_C(0x0000000000000800)
#define BGFX_STATE_ALPHA_TEST_SHIFT     8
#define BGFX_STATE_ALPHA_TEST_MASK      UINT64_C(0x0000000000000f00)

#define BGFX_STATE_BLEND_ZERO           UINT64_C(0x0000000000001000)
#define BGFX_STATE_BLEND_ONE            UINT64_C(0x0000000000002000)
#define BGFX_STATE_BLEND_SRC_COLOR      UINT64_C(0x0000000000003000)
#define BGFX_STATE_BLEND_INV_SRC_COLOR  UINT64_C(0x0000000000004000)
#define BGFX_STATE_BLEND_SRC_ALPHA      UINT64_C(0x0000000000005000)
#define BGFX_STATE_BLEND_INV_SRC_ALPHA  UINT64_C(0x0000000000006000)
#define BGFX_STATE_BLEND_DST_ALPHA      UINT64_C(0x0000000000007000)
#define BGFX_STATE_BLEND_INV_DST_ALPHA  UINT64_C(0x0000000000008000)
#define BGFX_STATE_BLEND_DST_COLOR      UINT64_C(0x0000000000009000)
#define BGFX_STATE_BLEND_INV_DST_COLOR  UINT64_C(0x000000000000a000)
#define BGFX_STATE_BLEND_SRC_ALPHA_SAT  UINT64_C(0x000000000000b000)
#define BGFX_STATE_BLEND_SHIFT          12
#define BGFX_STATE_BLEND_MASK           UINT64_C(0x000000000ffff000)

#define BGFX_STATE_CULL_CW              UINT64_C(0x0000000010000000)
#define BGFX_STATE_CULL_CCW             UINT64_C(0x0000000020000000)
#define BGFX_STATE_CULL_SHIFT           28
#define BGFX_STATE_CULL_MASK            UINT64_C(0x0000000030000000)

#define BGFX_STATE_RGB_WRITE            UINT64_C(0x0000000040000000)

#define BGFX_STATE_ALPHA_REF_SHIFT      32
#define BGFX_STATE_ALPHA_REF_MASK       UINT64_C(0x000000ff00000000)

#define BGFX_STATE_PT_LINES             UINT64_C(0x0000010000000000)
#define BGFX_STATE_PT_POINTS            UINT64_C(0x0000020000000000)
#define BGFX_STATE_PT_SHIFT             40
#define BGFX_STATE_PT_MASK              UINT64_C(0x0000030000000000)

#define BGFX_STATE_POINT_SIZE_SHIFT     44
#define BGFX_STATE_POINT_SIZE_MASK      UINT64_C(0x000ff00000000000)

#define BGFX_STATE_SRGBWRITE            UINT64_C(0x0010000000000000)
#define BGFX_STATE_MSAA                 UINT64_C(0x0020000000000000)

#define BGFX_STATE_RESERVED             UINT64_C(0xff00000000000000)

#define BGFX_STATE_NONE                 UINT64_C(0x0000000000000000)
#define BGFX_STATE_MASK                 UINT64_C(0xffffffffffffffff)
#define BGFX_STATE_DEFAULT (0 \
					| BGFX_STATE_RGB_WRITE \
					| BGFX_STATE_ALPHA_WRITE \
					| BGFX_STATE_DEPTH_TEST_LESS \
					| BGFX_STATE_DEPTH_WRITE \
					| BGFX_STATE_CULL_CW \
					| BGFX_STATE_MSAA \
					)

#define BGFX_STATE_ALPHA_REF(_ref) ( (uint64_t(_ref)<<BGFX_STATE_ALPHA_REF_SHIFT)&BGFX_STATE_ALPHA_REF_MASK)
#define BGFX_STATE_POINT_SIZE(_size) ( (uint64_t(_size)<<BGFX_STATE_POINT_SIZE_SHIFT)&BGFX_STATE_POINT_SIZE_MASK)

///
#define BGFX_STENCIL_FUNC_REF_SHIFT     0
#define BGFX_STENCIL_FUNC_REF_MASK      UINT32_C(0x000000ff)
#define BGFX_STENCIL_FUNC_RMASK_SHIFT   8
#define BGFX_STENCIL_FUNC_RMASK_MASK    UINT32_C(0x0000ff00)

#define BGFX_STENCIL_TEST_LESS          UINT32_C(0x00010000)
#define BGFX_STENCIL_TEST_LEQUAL        UINT32_C(0x00020000)
#define BGFX_STENCIL_TEST_EQUAL         UINT32_C(0x00030000)
#define BGFX_STENCIL_TEST_GEQUAL        UINT32_C(0x00040000)
#define BGFX_STENCIL_TEST_GREATER       UINT32_C(0x00050000)
#define BGFX_STENCIL_TEST_NOTEQUAL      UINT32_C(0x00060000)
#define BGFX_STENCIL_TEST_NEVER         UINT32_C(0x00070000)
#define BGFX_STENCIL_TEST_ALWAYS        UINT32_C(0x00080000)
#define BGFX_STENCIL_TEST_SHIFT         16
#define BGFX_STENCIL_TEST_MASK          UINT32_C(0x000f0000)

#define BGFX_STENCIL_OP_FAIL_S_ZERO     UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_S_KEEP     UINT32_C(0x00100000)
#define BGFX_STENCIL_OP_FAIL_S_REPLACE  UINT32_C(0x00200000)
#define BGFX_STENCIL_OP_FAIL_S_INCR     UINT32_C(0x00300000)
#define BGFX_STENCIL_OP_FAIL_S_INCRSAT  UINT32_C(0x00400000)
#define BGFX_STENCIL_OP_FAIL_S_DECR     UINT32_C(0x00500000)
#define BGFX_STENCIL_OP_FAIL_S_DECRSAT  UINT32_C(0x00600000)
#define BGFX_STENCIL_OP_FAIL_S_INVERT   UINT32_C(0x00700000)
#define BGFX_STENCIL_OP_FAIL_S_SHIFT    20
#define BGFX_STENCIL_OP_FAIL_S_MASK     UINT32_C(0x00f00000)

#define BGFX_STENCIL_OP_FAIL_Z_ZERO     UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_Z_KEEP     UINT32_C(0x01000000)
#define BGFX_STENCIL_OP_FAIL_Z_REPLACE  UINT32_C(0x02000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCR     UINT32_C(0x03000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCRSAT  UINT32_C(0x04000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECR     UINT32_C(0x05000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECRSAT  UINT32_C(0x06000000)
#define BGFX_STENCIL_OP_FAIL_Z_INVERT   UINT32_C(0x07000000)
#define BGFX_STENCIL_OP_FAIL_Z_SHIFT    24
#define BGFX_STENCIL_OP_FAIL_Z_MASK     UINT32_C(0x0f000000)

#define BGFX_STENCIL_OP_PASS_Z_ZERO     UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_PASS_Z_KEEP     UINT32_C(0x10000000)
#define BGFX_STENCIL_OP_PASS_Z_REPLACE  UINT32_C(0x20000000)
#define BGFX_STENCIL_OP_PASS_Z_INCR     UINT32_C(0x30000000)
#define BGFX_STENCIL_OP_PASS_Z_INCRSAT  UINT32_C(0x40000000)
#define BGFX_STENCIL_OP_PASS_Z_DECR     UINT32_C(0x50000000)
#define BGFX_STENCIL_OP_PASS_Z_DECRSAT  UINT32_C(0x60000000)
#define BGFX_STENCIL_OP_PASS_Z_INVERT   UINT32_C(0x70000000)
#define BGFX_STENCIL_OP_PASS_Z_SHIFT    28
#define BGFX_STENCIL_OP_PASS_Z_MASK     UINT32_C(0xf0000000)

#define BGFX_STENCIL_NONE               UINT32_C(0x00000000)
#define BGFX_STENCIL_MASK               UINT32_C(0xffffffff)
#define BGFX_STENCIL_DEFAULT            UINT32_C(0x00000000)

#define BGFX_STENCIL_FUNC_REF(_ref) ( (uint32_t(_ref)<<BGFX_STENCIL_FUNC_REF_SHIFT)&BGFX_STENCIL_FUNC_REF_MASK)
#define BGFX_STENCIL_FUNC_RMASK(_mask) ( (uint32_t(_mask)<<BGFX_STENCIL_FUNC_RMASK_SHIFT)&BGFX_STENCIL_FUNC_RMASK_MASK)

///
#define BGFX_CLEAR_NONE                 UINT8_C(0x00)
#define BGFX_CLEAR_COLOR_BIT            UINT8_C(0x01)
#define BGFX_CLEAR_DEPTH_BIT            UINT8_C(0x02)
#define BGFX_CLEAR_STENCIL_BIT          UINT8_C(0x04)

///
#define BGFX_DEBUG_NONE                 UINT32_C(0x00000000)
#define BGFX_DEBUG_WIREFRAME            UINT32_C(0x00000001)
#define BGFX_DEBUG_IFH                  UINT32_C(0x00000002)
#define BGFX_DEBUG_STATS                UINT32_C(0x00000004)
#define BGFX_DEBUG_TEXT                 UINT32_C(0x00000008)

///
#define BGFX_TEXTURE_NONE               UINT32_C(0x00000000)
#define BGFX_TEXTURE_U_REPEAT           UINT32_C(0x00000000)
#define BGFX_TEXTURE_U_MIRROR           UINT32_C(0x00000001)
#define BGFX_TEXTURE_U_CLAMP            UINT32_C(0x00000002)
#define BGFX_TEXTURE_U_SHIFT            0
#define BGFX_TEXTURE_U_MASK             UINT32_C(0x00000003)
#define BGFX_TEXTURE_V_REPEAT           UINT32_C(0x00000000)
#define BGFX_TEXTURE_V_MIRROR           UINT32_C(0x00000010)
#define BGFX_TEXTURE_V_CLAMP            UINT32_C(0x00000020)
#define BGFX_TEXTURE_V_SHIFT            4
#define BGFX_TEXTURE_V_MASK             UINT32_C(0x00000030)
#define BGFX_TEXTURE_W_REPEAT           UINT32_C(0x00000000)
#define BGFX_TEXTURE_W_MIRROR           UINT32_C(0x00000100)
#define BGFX_TEXTURE_W_CLAMP            UINT32_C(0x00000200)
#define BGFX_TEXTURE_W_SHIFT            8
#define BGFX_TEXTURE_W_MASK             UINT32_C(0x00000300)
#define BGFX_TEXTURE_MIN_POINT          UINT32_C(0x00001000)
#define BGFX_TEXTURE_MIN_SHIFT          12
#define BGFX_TEXTURE_MIN_MASK           UINT32_C(0x00001000)
#define BGFX_TEXTURE_MAG_POINT          UINT32_C(0x00010000)
#define BGFX_TEXTURE_MAG_SHIFT          16
#define BGFX_TEXTURE_MAG_MASK           UINT32_C(0x00010000)
#define BGFX_TEXTURE_MIP_POINT          UINT32_C(0x00100000)
#define BGFX_TEXTURE_MIP_SHIFT          20
#define BGFX_TEXTURE_MIP_MASK           UINT32_C(0x00100000)
#define BGFX_TEXTURE_SRGB               UINT32_C(0x00200000)

///
#define BGFX_RENDER_TARGET_NONE         UINT32_C(0x00000000)
#define BGFX_RENDER_TARGET_COLOR_RGBA   UINT32_C(0x00000001)
#define BGFX_RENDER_TARGET_COLOR_R32F   UINT32_C(0x00000002)
#define BGFX_RENDER_TARGET_COLOR_SHIFT  0
#define BGFX_RENDER_TARGET_COLOR_MASK   UINT32_C(0x000000ff)
#define BGFX_RENDER_TARGET_DEPTH        UINT32_C(0x00000100)
#define BGFX_RENDER_TARGET_DEPTH_SHIFT  8
#define BGFX_RENDER_TARGET_DEPTH_MASK   UINT32_C(0x0000ff00)
#define BGFX_RENDER_TARGET_MSAA_X2      UINT32_C(0x00010000)
#define BGFX_RENDER_TARGET_MSAA_X4      UINT32_C(0x00020000)
#define BGFX_RENDER_TARGET_MSAA_X8      UINT32_C(0x00030000)
#define BGFX_RENDER_TARGET_MSAA_X16     UINT32_C(0x00040000)
#define BGFX_RENDER_TARGET_MSAA_SHIFT   16
#define BGFX_RENDER_TARGET_MSAA_MASK    UINT32_C(0x00070000)
#define BGFX_RENDER_TARGET_SRGBWRITE    UINT32_C(0x00080000)

///
#define BGFX_RESET_NONE                 UINT32_C(0x00000000)
#define BGFX_RESET_FULLSCREEN           UINT32_C(0x00000001)
#define BGFX_RESET_FULLSCREEN_FAKE      UINT32_C(0x00000002)
#define BGFX_RESET_FULLSCREEN_SHIFT     0
#define BGFX_RESET_FULLSCREEN_MASK      UINT32_C(0x00000003)
#define BGFX_RESET_MSAA_X2              UINT32_C(0x00000010)
#define BGFX_RESET_MSAA_X4              UINT32_C(0x00000020)
#define BGFX_RESET_MSAA_X8              UINT32_C(0x00000030)
#define BGFX_RESET_MSAA_X16             UINT32_C(0x00000040)
#define BGFX_RESET_MSAA_SHIFT           4
#define BGFX_RESET_MSAA_MASK            UINT32_C(0x00000070)
#define BGFX_RESET_VSYNC                UINT32_C(0x00000080)

///
#define BGFX_HANDLE(_name) struct _name { uint16_t idx; }
#define BGFX_INVALID_HANDLE { bgfx::invalidHandle }

/// BGFX
namespace bgfx
{
	struct Fatal
	{
		enum Enum
		{
			MinimumRequiredSpecs = 1,
			InvalidShader,
			D3D9_UnableToCreateInterface,
			D3D9_UnableToCreateDevice,
			D3D9_UnableToCreateRenderTarget,
			D3D9_UnableToCreateTexture,
			D3D11_UnableToInitialize,
			OPENGL_UnableToCreateContext,
		};
	};

	struct RendererType
	{
		enum Enum
		{
			Null,
			Direct3D9,
			Direct3D11,
			OpenGLES2,
			OpenGLES3,
			OpenGL,

			Count
		};
	};

	struct Attrib
	{
		enum Enum
		{
			Position,
			Normal,
			Tangent,
			Color0,
			Color1,
			Indices,
			Weight,
			TexCoord0,
			TexCoord1,
			TexCoord2,
			TexCoord3,
			TexCoord4,
			TexCoord5,
			TexCoord6,
			TexCoord7,

			Count
		};
	};

	struct AttribType
	{
		enum Enum
		{
			Uint8,
			Uint16,
			Half,
			Float,

			Count
		};
	};

	struct TextureFormat
	{
		enum Enum
		{
			Dxt1,
			Dxt3,
			Dxt5,
			Unknown,
			L8,
			XRGB8,
			ARGB8,
			ABGR16,
			R5G6B5,
			RGBA4,
			RGB5A1,
			RGB10A2,
			
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
	BGFX_HANDLE(FragmentShaderHandle);
	BGFX_HANDLE(IndexBufferHandle);
	BGFX_HANDLE(ProgramHandle);
	BGFX_HANDLE(RenderTargetHandle);
	BGFX_HANDLE(TextureHandle);
	BGFX_HANDLE(UniformHandle);
	BGFX_HANDLE(VertexBufferHandle);
	BGFX_HANDLE(VertexDeclHandle);
	BGFX_HANDLE(VertexShaderHandle);

	typedef void (*FatalFn)(Fatal::Enum _code, const char* _str);
	typedef void* (*ReallocFn)(void* _ptr, size_t _size);
	typedef void (*FreeFn)(void* _ptr);
	typedef void (*CacheFn)(uint64_t _id, bool _store, void* _data, uint32_t& _length);

	struct Memory
	{
		uint8_t* data;
		uint32_t size;
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
		uint16_t width;
		uint16_t height;
		uint16_t depth;
	};

	struct VertexDecl
	{
		/// Start VertexDecl.
		void begin(RendererType::Enum _renderer = RendererType::Null);

		/// End VertexDecl.
		void end();

		/// Add attribute to VertexDecl. Note: Must be called between begin/end.
		void add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized = false);

		/// Decode attribute.
		void decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized) const;

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

	/// Returns renderer backend API type.
	RendererType::Enum getRendererType();

	///
	void init(FatalFn _fatal = NULL, ReallocFn _realloc = NULL, FreeFn _free = NULL, CacheFn _cache = NULL);

	///
	void shutdown();

	///
	void reset(uint32_t _width, uint32_t _height, uint32_t _flags = BGFX_RESET_NONE);

	/// Advance to next frame. When using multithreaded renderer, this call
	/// just swaps internal buffers, kicks render thread, and returns. In
	/// singlethreaded renderer this call does frame rendering.
	void frame();

	/// Allocate buffer to pass to bgfx calls. Data will be freed inside bgfx.
	const Memory* alloc(uint32_t _size);

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

	///
	IndexBufferHandle createIndexBuffer(const Memory* _mem);

	///
	void destroyIndexBuffer(IndexBufferHandle _handle);

	///
	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl);

	///
	void destroyVertexBuffer(VertexBufferHandle _handle);

	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(uint16_t _num);

	///
	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem);

	///
	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem);

	///
	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle);

	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	///
	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl);

	///
	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, const Memory* _mem);

	///
	void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle);

	/// Returns true if internal transient index buffer has enough space.
	bool checkAvailTransientIndexBuffer(uint16_t _num);

	/// Allocate transient index buffer.
	///
	/// @param[out] _tib is valid for the duration of frame, and it can be reused for
	/// multiple draw calls.
	/// @param _num number of indices to allocate.
	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint16_t _num);

	/// Returns true if internal transient vertex buffer has enough space.
	bool checkAvailTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	/// Allocate transient vertex buffer.
	///
	/// @param[out] _tvb is valid for the duration of frame, and it can be reused for
	/// multiple draw calls.
	/// @param _num number of vertices to allocate.
	/// @param _decl vertex declaration.
	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint16_t _num, const VertexDecl& _decl);

	///
	const InstanceDataBuffer* allocInstanceDataBuffer(uint16_t _num, uint16_t _stride);

	/// Create vertex shader from memory buffer.
	VertexShaderHandle createVertexShader(const Memory* _mem);

	/// Destroy vertex shader. Once program is created with vertex shader
	/// it is safe to destroy vertex shader.
	void destroyVertexShader(VertexShaderHandle _handle);

	/// Create fragment shader from memory buffer.
	FragmentShaderHandle createFragmentShader(const Memory* _mem);

	/// Destroy fragment shader. Once program is created with fragment shader
	/// it is safe to destroy fragment shader.
	void destroyFragmentShader(FragmentShaderHandle _handle);

	/// Create program with vertex and fragment shaders.
	///
	/// @param _vsh vertex shader.
	/// @param _fsh fragment shader.
	/// @returns Program handle if vertex shader output and fragment shader
	/// input are matching, otherwise returns invalid program handle.
	ProgramHandle createProgram(VertexShaderHandle _vsh, FragmentShaderHandle _fsh);

	/// Destroy program.
	void destroyProgram(ProgramHandle _handle);

	/// Create texture from memory buffer.
	TextureHandle createTexture(const Memory* _mem, uint32_t _flags = BGFX_TEXTURE_NONE, TextureInfo* _info = NULL);

	///
	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	///
	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	///
	TextureHandle createTextureCube(uint16_t _sides, uint16_t _width, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	///
	void updateTexture2D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem);

	///
	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem);

	///
	void updateTextureCube(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem);

	///
	void destroyTexture(TextureHandle _handle);

	///
	RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags = BGFX_RENDER_TARGET_COLOR_RGBA, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	///
	void destroyRenderTarget(RenderTargetHandle _handle);

	///
	UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num = 1);

	///
	void destroyUniform(UniformHandle _handle);

	/// Set view rectangle. Draw primitive outside view will be clipped.
	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	///
	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set view clear flags.
	///
	/// @param _id view id.
	/// @param _flags clear flags.
	///     See: BGFX_CLEAR_*
	///
	/// @param _rgba color clear value.
	/// @param _depth depth clear value.
	/// @param _stencil stencil clear value.
	void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	///
	void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	/// Set view into sequential mode. Draw calls will be sorted in the same
	/// order in which submit calls were called.
	void setViewSeq(uint8_t _id, bool _enabled);

	///
	void setViewSeqMask(uint32_t _viewMask, bool _enabled);

	/// Set view render target. View without render target draws primitives
	/// into default backbuffer.
	void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle);

	///
	void setViewRenderTargetMask(uint32_t _viewMask, RenderTargetHandle _handle);

	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other = 0xff);

	///
	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other = 0xff);

	/// Set render states for draw primitive.
	///   BGFX_STATE_*
	void setState(uint64_t _state);

	/// Set stencil test state.
	///
	/// @param _fstencil Front stencil state.
	/// @param _bstencil Back stencil state. If back is set to BGFX_STENCIL_NONE
	///     _fstencil is applied to both front and back facing primitives.
	void setStencil(uint32_t _fstencil, uint32_t _bstencil = BGFX_STENCIL_NONE);

	/// Set model matrix for draw primitive. If it is not called model will
	/// be rendered with identity model matrix.
	///
	/// @param _mtx pointer to first matrix in array.
	/// @param _num number of matrices in array.
	/// @returns index into matrix cache in case the same model matrix has to
	/// be used for other draw primitive call.
	uint32_t setTransform(const void* _mtx, uint16_t _num = 1);

	/// Set model matrix from matrix cache for draw primitive.
	///
	/// @param _cache index in matrix cache.
	/// @param _num number of matrices from cache.
	void setTransform(uint32_t _cache, uint16_t _num = 1);

	///
	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num = 1);

	///
	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices);

	///
	void setIndexBuffer(IndexBufferHandle _handle);

	///
	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices);

	///
	void setIndexBuffer(DynamicIndexBufferHandle _handle);

	///
	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _numIndices = UINT32_MAX);

	///
	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	///
	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	///
	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _numVertices = UINT32_MAX);

	///
	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint16_t _num = UINT16_MAX);

	///
	void setProgram(ProgramHandle _handle);

	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle);

	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth = false);

	/// Submit primitive for rendering into single view.
	///
	/// @param _id View id.
	/// @param _depth depth for sorting.
	void submit(uint8_t _id, int32_t _depth = 0);

	/// Submit primitive for rendering into multiple views.
	///
	/// @param _viewMask mask to which views to submit draw primitive calls.
	/// @param _depth depth for sorting.
	void submitMask(uint32_t _viewMask, int32_t _depth = 0);

	///
	void saveScreenShot(const char* _filePath);

} // namespace bgfx

#endif // __BGFX_H__

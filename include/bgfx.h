/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFX_H__
#define __BGFX_H__

#include <stdint.h> // uint32_t
#include <stdlib.h> // size_t

///
#define BGFX_STATE_DEPTH_WRITE           UINT64_C(0x0000000000000001)

#define BGFX_STATE_ALPHA_WRITE           UINT64_C(0x0000000000000008)
#define BGFX_STATE_ALPHA_MASK            UINT64_C(0x000000000000000c)

#define BGFX_STATE_DEPTH_TEST_LESS       UINT64_C(0x0000000000000010)
#define BGFX_STATE_DEPTH_TEST_LEQUAL     UINT64_C(0x0000000000000020)
#define BGFX_STATE_DEPTH_TEST_EQUAL      UINT64_C(0x0000000000000030)
#define BGFX_STATE_DEPTH_TEST_GEQUAL     UINT64_C(0x0000000000000040)
#define BGFX_STATE_DEPTH_TEST_GREATER    UINT64_C(0x0000000000000050)
#define BGFX_STATE_DEPTH_TEST_NOTEQUAL   UINT64_C(0x0000000000000060)
#define BGFX_STATE_DEPTH_TEST_NEVER      UINT64_C(0x0000000000000070)
#define BGFX_STATE_DEPTH_TEST_ALWAYS     UINT64_C(0x0000000000000080)
#define BGFX_STATE_DEPTH_TEST_SHIFT      4
#define BGFX_STATE_DEPTH_TEST_MASK       UINT64_C(0x00000000000000f0)

#define BGFX_STATE_BLEND_ZERO            UINT64_C(0x0000000000001000)
#define BGFX_STATE_BLEND_ONE             UINT64_C(0x0000000000002000)
#define BGFX_STATE_BLEND_SRC_COLOR       UINT64_C(0x0000000000003000)
#define BGFX_STATE_BLEND_INV_SRC_COLOR   UINT64_C(0x0000000000004000)
#define BGFX_STATE_BLEND_SRC_ALPHA       UINT64_C(0x0000000000005000)
#define BGFX_STATE_BLEND_INV_SRC_ALPHA   UINT64_C(0x0000000000006000)
#define BGFX_STATE_BLEND_DST_ALPHA       UINT64_C(0x0000000000007000)
#define BGFX_STATE_BLEND_INV_DST_ALPHA   UINT64_C(0x0000000000008000)
#define BGFX_STATE_BLEND_DST_COLOR       UINT64_C(0x0000000000009000)
#define BGFX_STATE_BLEND_INV_DST_COLOR   UINT64_C(0x000000000000a000)
#define BGFX_STATE_BLEND_SRC_ALPHA_SAT   UINT64_C(0x000000000000b000)
#define BGFX_STATE_BLEND_FACTOR          UINT64_C(0x000000000000c000)
#define BGFX_STATE_BLEND_INV_FACTOR      UINT64_C(0x000000000000d000)
#define BGFX_STATE_BLEND_SHIFT           12
#define BGFX_STATE_BLEND_MASK            UINT64_C(0x00000000000ff000)

#define BGFX_STATE_BLEND_EQUATION_SUB    UINT64_C(0x0000000000100000)
#define BGFX_STATE_BLEND_EQUATION_REVSUB UINT64_C(0x0000000000200000)
#define BGFX_STATE_BLEND_EQUATION_MIN    UINT64_C(0x0000000000300000)
#define BGFX_STATE_BLEND_EQUATION_MAX    UINT64_C(0x0000000000400000)
#define BGFX_STATE_BLEND_EQUATION_SHIFT  20
#define BGFX_STATE_BLEND_EQUATION_MASK   UINT64_C(0x0000000000700000)

#define BGFX_STATE_CULL_CW               UINT64_C(0x0000000010000000)
#define BGFX_STATE_CULL_CCW              UINT64_C(0x0000000020000000)
#define BGFX_STATE_CULL_SHIFT            28
#define BGFX_STATE_CULL_MASK             UINT64_C(0x0000000030000000)

#define BGFX_STATE_RGB_WRITE             UINT64_C(0x0000000040000000)

#define BGFX_STATE_ALPHA_REF_SHIFT       32
#define BGFX_STATE_ALPHA_REF_MASK        UINT64_C(0x000000ff00000000)

#define BGFX_STATE_PT_LINES              UINT64_C(0x0000010000000000)
#define BGFX_STATE_PT_POINTS             UINT64_C(0x0000020000000000)
#define BGFX_STATE_PT_SHIFT              40
#define BGFX_STATE_PT_MASK               UINT64_C(0x0000030000000000)

#define BGFX_STATE_POINT_SIZE_SHIFT      44
#define BGFX_STATE_POINT_SIZE_MASK       UINT64_C(0x000ff00000000000)

#define BGFX_STATE_MSAA                  UINT64_C(0x0020000000000000)

#define BGFX_STATE_RESERVED_MASK         UINT64_C(0xff00000000000000)

#define BGFX_STATE_NONE                  UINT64_C(0x0000000000000000)
#define BGFX_STATE_MASK                  UINT64_C(0xffffffffffffffff)
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
#define BGFX_STATE_BLEND_FUNC(_src, _dst) ( uint64_t(_src)|( uint64_t(_dst)<<4) )

#define BGFX_STATE_BLEND_ADD         (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) )
#define BGFX_STATE_BLEND_ALPHA       (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_COLOR) )
#define BGFX_STATE_BLEND_DARKEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION_MIN)
#define BGFX_STATE_BLEND_LIGHTEN     (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_ONE          ) | BGFX_STATE_BLEND_EQUATION_MAX)
#define BGFX_STATE_BLEND_MULTIPLY    (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_ZERO         ) )
#define BGFX_STATE_BLEND_NORMAL      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_ALPHA) )
#define BGFX_STATE_BLEND_SCREEN      (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_COLOR) )
#define BGFX_STATE_BLEND_LINEAR_BURN (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_INV_DST_COLOR) | BGFX_STATE_BLEND_EQUATION_SUB)

///
#define BGFX_STENCIL_FUNC_REF_SHIFT      0
#define BGFX_STENCIL_FUNC_REF_MASK       UINT32_C(0x000000ff)
#define BGFX_STENCIL_FUNC_RMASK_SHIFT    8
#define BGFX_STENCIL_FUNC_RMASK_MASK     UINT32_C(0x0000ff00)

#define BGFX_STENCIL_TEST_LESS           UINT32_C(0x00010000)
#define BGFX_STENCIL_TEST_LEQUAL         UINT32_C(0x00020000)
#define BGFX_STENCIL_TEST_EQUAL          UINT32_C(0x00030000)
#define BGFX_STENCIL_TEST_GEQUAL         UINT32_C(0x00040000)
#define BGFX_STENCIL_TEST_GREATER        UINT32_C(0x00050000)
#define BGFX_STENCIL_TEST_NOTEQUAL       UINT32_C(0x00060000)
#define BGFX_STENCIL_TEST_NEVER          UINT32_C(0x00070000)
#define BGFX_STENCIL_TEST_ALWAYS         UINT32_C(0x00080000)
#define BGFX_STENCIL_TEST_SHIFT          16
#define BGFX_STENCIL_TEST_MASK           UINT32_C(0x000f0000)

#define BGFX_STENCIL_OP_FAIL_S_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_S_KEEP      UINT32_C(0x00100000)
#define BGFX_STENCIL_OP_FAIL_S_REPLACE   UINT32_C(0x00200000)
#define BGFX_STENCIL_OP_FAIL_S_INCR      UINT32_C(0x00300000)
#define BGFX_STENCIL_OP_FAIL_S_INCRSAT   UINT32_C(0x00400000)
#define BGFX_STENCIL_OP_FAIL_S_DECR      UINT32_C(0x00500000)
#define BGFX_STENCIL_OP_FAIL_S_DECRSAT   UINT32_C(0x00600000)
#define BGFX_STENCIL_OP_FAIL_S_INVERT    UINT32_C(0x00700000)
#define BGFX_STENCIL_OP_FAIL_S_SHIFT     20
#define BGFX_STENCIL_OP_FAIL_S_MASK      UINT32_C(0x00f00000)

#define BGFX_STENCIL_OP_FAIL_Z_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_FAIL_Z_KEEP      UINT32_C(0x01000000)
#define BGFX_STENCIL_OP_FAIL_Z_REPLACE   UINT32_C(0x02000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCR      UINT32_C(0x03000000)
#define BGFX_STENCIL_OP_FAIL_Z_INCRSAT   UINT32_C(0x04000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECR      UINT32_C(0x05000000)
#define BGFX_STENCIL_OP_FAIL_Z_DECRSAT   UINT32_C(0x06000000)
#define BGFX_STENCIL_OP_FAIL_Z_INVERT    UINT32_C(0x07000000)
#define BGFX_STENCIL_OP_FAIL_Z_SHIFT     24
#define BGFX_STENCIL_OP_FAIL_Z_MASK      UINT32_C(0x0f000000)

#define BGFX_STENCIL_OP_PASS_Z_ZERO      UINT32_C(0x00000000)
#define BGFX_STENCIL_OP_PASS_Z_KEEP      UINT32_C(0x10000000)
#define BGFX_STENCIL_OP_PASS_Z_REPLACE   UINT32_C(0x20000000)
#define BGFX_STENCIL_OP_PASS_Z_INCR      UINT32_C(0x30000000)
#define BGFX_STENCIL_OP_PASS_Z_INCRSAT   UINT32_C(0x40000000)
#define BGFX_STENCIL_OP_PASS_Z_DECR      UINT32_C(0x50000000)
#define BGFX_STENCIL_OP_PASS_Z_DECRSAT   UINT32_C(0x60000000)
#define BGFX_STENCIL_OP_PASS_Z_INVERT    UINT32_C(0x70000000)
#define BGFX_STENCIL_OP_PASS_Z_SHIFT     28
#define BGFX_STENCIL_OP_PASS_Z_MASK      UINT32_C(0xf0000000)

#define BGFX_STENCIL_NONE                UINT32_C(0x00000000)
#define BGFX_STENCIL_MASK                UINT32_C(0xffffffff)
#define BGFX_STENCIL_DEFAULT             UINT32_C(0x00000000)

#define BGFX_STENCIL_FUNC_REF(_ref) ( (uint32_t(_ref)<<BGFX_STENCIL_FUNC_REF_SHIFT)&BGFX_STENCIL_FUNC_REF_MASK)
#define BGFX_STENCIL_FUNC_RMASK(_mask) ( (uint32_t(_mask)<<BGFX_STENCIL_FUNC_RMASK_SHIFT)&BGFX_STENCIL_FUNC_RMASK_MASK)

///
#define BGFX_CLEAR_NONE                  UINT8_C(0x00)
#define BGFX_CLEAR_COLOR_BIT             UINT8_C(0x01)
#define BGFX_CLEAR_DEPTH_BIT             UINT8_C(0x02)
#define BGFX_CLEAR_STENCIL_BIT           UINT8_C(0x04)

///
#define BGFX_DEBUG_NONE                  UINT32_C(0x00000000)
#define BGFX_DEBUG_WIREFRAME             UINT32_C(0x00000001)
#define BGFX_DEBUG_IFH                   UINT32_C(0x00000002)
#define BGFX_DEBUG_STATS                 UINT32_C(0x00000004)
#define BGFX_DEBUG_TEXT                  UINT32_C(0x00000008)

///
#define BGFX_TEXTURE_NONE                UINT32_C(0x00000000)
#define BGFX_TEXTURE_U_MIRROR            UINT32_C(0x00000001)
#define BGFX_TEXTURE_U_CLAMP             UINT32_C(0x00000002)
#define BGFX_TEXTURE_U_SHIFT             0
#define BGFX_TEXTURE_U_MASK              UINT32_C(0x00000003)
#define BGFX_TEXTURE_V_MIRROR            UINT32_C(0x00000010)
#define BGFX_TEXTURE_V_CLAMP             UINT32_C(0x00000020)
#define BGFX_TEXTURE_V_SHIFT             4
#define BGFX_TEXTURE_V_MASK              UINT32_C(0x00000030)
#define BGFX_TEXTURE_W_MIRROR            UINT32_C(0x00000100)
#define BGFX_TEXTURE_W_CLAMP             UINT32_C(0x00000200)
#define BGFX_TEXTURE_W_SHIFT             8
#define BGFX_TEXTURE_W_MASK              UINT32_C(0x00000300)
#define BGFX_TEXTURE_MIN_POINT           UINT32_C(0x00001000)
#define BGFX_TEXTURE_MIN_ANISOTROPIC     UINT32_C(0x00002000)
#define BGFX_TEXTURE_MIN_SHIFT           12
#define BGFX_TEXTURE_MIN_MASK            UINT32_C(0x00003000)
#define BGFX_TEXTURE_MAG_POINT           UINT32_C(0x00010000)
#define BGFX_TEXTURE_MAG_ANISOTROPIC     UINT32_C(0x00020000)
#define BGFX_TEXTURE_MAG_SHIFT           16
#define BGFX_TEXTURE_MAG_MASK            UINT32_C(0x00030000)
#define BGFX_TEXTURE_MIP_POINT           UINT32_C(0x00100000)
#define BGFX_TEXTURE_MIP_SHIFT           20
#define BGFX_TEXTURE_MIP_MASK            UINT32_C(0x00100000)
#define BGFX_TEXTURE_RESERVED_MASK       UINT32_C(0xf0000000)

///
#define BGFX_RENDER_TARGET_NONE          UINT32_C(0x00000000)
#define BGFX_RENDER_TARGET_COLOR_RGBA8   UINT32_C(0x00000001)
#define BGFX_RENDER_TARGET_COLOR_RGB10A2 UINT32_C(0x00000002)
#define BGFX_RENDER_TARGET_COLOR_RGBA16  UINT32_C(0x00000003)
#define BGFX_RENDER_TARGET_COLOR_RGBA16F UINT32_C(0x00000004)
#define BGFX_RENDER_TARGET_COLOR_R16F    UINT32_C(0x00000005)
#define BGFX_RENDER_TARGET_COLOR_R32F    UINT32_C(0x00000006)
#define BGFX_RENDER_TARGET_COLOR_SHIFT   0
#define BGFX_RENDER_TARGET_COLOR_MASK    UINT32_C(0x000000ff)
#define BGFX_RENDER_TARGET_DEPTH         UINT32_C(0x00000100)
#define BGFX_RENDER_TARGET_DEPTH_SHIFT   8
#define BGFX_RENDER_TARGET_DEPTH_MASK    UINT32_C(0x0000ff00)
#define BGFX_RENDER_TARGET_MSAA_X2       UINT32_C(0x00010000)
#define BGFX_RENDER_TARGET_MSAA_X4       UINT32_C(0x00020000)
#define BGFX_RENDER_TARGET_MSAA_X8       UINT32_C(0x00030000)
#define BGFX_RENDER_TARGET_MSAA_X16      UINT32_C(0x00040000)
#define BGFX_RENDER_TARGET_MSAA_SHIFT    16
#define BGFX_RENDER_TARGET_MSAA_MASK     UINT32_C(0x00070000)

///
#define BGFX_RESET_NONE                  UINT32_C(0x00000000)
#define BGFX_RESET_FULLSCREEN            UINT32_C(0x00000001)
#define BGFX_RESET_FULLSCREEN_SHIFT      0
#define BGFX_RESET_FULLSCREEN_MASK       UINT32_C(0x00000001)
#define BGFX_RESET_MSAA_X2               UINT32_C(0x00000010)
#define BGFX_RESET_MSAA_X4               UINT32_C(0x00000020)
#define BGFX_RESET_MSAA_X8               UINT32_C(0x00000030)
#define BGFX_RESET_MSAA_X16              UINT32_C(0x00000040)
#define BGFX_RESET_MSAA_SHIFT            4
#define BGFX_RESET_MSAA_MASK             UINT32_C(0x00000070)
#define BGFX_RESET_VSYNC                 UINT32_C(0x00000080)
#define BGFX_RESET_CAPTURE               UINT32_C(0x00000100)

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
			DebugCheck,
			MinimumRequiredSpecs,
			InvalidShader,
			UnableToInitialize,
			UnableToCreateRenderTarget,
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
			OpenGLES2,
			OpenGLES3,
			OpenGL,

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
			Half,
			Float,

			Count
		};
	};

	struct TextureFormat
	{
		enum Enum
		{
			BC1, // DXT1
			BC2, // DXT3
			BC3, // DXT5
			BC4, // LATC1/ATI1
			BC5, // LATC2/ATI2
			Unknown,
			L8,
			BGRX8,
			BGRA8,
			RGBA16,
			RGBA16F,
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

	typedef void* (*ReallocFn)(void* _ptr, size_t _size);
	typedef void (*FreeFn)(void* _ptr);

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
		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip) = 0;

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
		void begin(RendererType::Enum _renderer = RendererType::Null);

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
		void add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized = false, bool _asInt = false);

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

	/// Swizzle RGBA8 image to BGRA8.
	void imageSwizzleBGRA8(uint8_t* _rgbaData, uint32_t _width, uint32_t _height);

	/// Returns renderer backend API type.
	RendererType::Enum getRendererType();

	/// Initialize bgfx library.
	///
	/// @param _callback Provide application specific callback interface.
	///   See: CallbackI
	///
	/// @param _realloc Custom realloc function.
	/// @param _free Custom free function.
	///
	/// NOTE: In order to properly set custom allocator realloc and free,
	///   both functions must be provided. When custom allocator is not
	///   specified, library uses default CRT allocator. The library assumes
	///   custom allocator is thread safe.
	///
	void init(CallbackI* _callback = NULL, ReallocFn _realloc = NULL, FreeFn _free = NULL);

	/// Shutdown bgfx library.
	void shutdown();

	/// Reset graphic settings.
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

	/// Create static index buffer.
	IndexBufferHandle createIndexBuffer(const Memory* _mem);

	/// Destroy static index buffer.
	void destroyIndexBuffer(IndexBufferHandle _handle);

	/// Create static vertex buffer.
	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl);

	/// Destroy static vertex buffer.
	void destroyVertexBuffer(VertexBufferHandle _handle);

	/// Create empty dynamic index buffer.
	DynamicIndexBufferHandle createDynamicIndexBuffer(uint16_t _num);

	/// Create dynamic index buffer and initialized it.
	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem);

	/// Update dynamic index buffer.
	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem);

	/// Destroy dynamic index buffer.
	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle);

	/// Create empty dynamic vertex buffer.
	DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	/// Create dynamic vertex buffer and initialize it.
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
	///   You must call setIndexBuffer after alloc in order to avoid memory
	///   leak.
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

	/// Allocate instance data buffer.
	///
	/// NOTE:
	///   You must call setInstanceDataBuffer after alloc in order to avoid
	///   memory leak.
	///
	const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride);

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
	/// @param _vsh Vertex shader.
	/// @param _fsh Fragment shader.
	/// @returns Program handle if vertex shader output and fragment shader
	///   input are matching, otherwise returns invalid program handle.
	///
	ProgramHandle createProgram(VertexShaderHandle _vsh, FragmentShaderHandle _fsh);

	/// Destroy program.
	void destroyProgram(ProgramHandle _handle);

	/// Calculate amount of memory required for texture.
	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format);

	/// Create texture from memory buffer.
	///
	/// @param _mem DDS texture data.
	/// @param _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///
	///   BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
	///     mode.
	///
	///   BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
	///     sampling.
	///
	/// @param _info Returns parsed DDS texture information.
	/// @returns Texture handle.
	///
	TextureHandle createTexture(const Memory* _mem, uint32_t _flags = BGFX_TEXTURE_NONE, TextureInfo* _info = NULL);

	/// Create 2D texture.
	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create 3D texture.
	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Create Cube texture.
	TextureHandle createTextureCube(uint16_t _sides, uint16_t _width, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE, const Memory* _mem = NULL);

	/// Update 2D texture.
	void updateTexture2D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem);

	/// Update 3D texture.
	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem);

	/// Update Cube texture.
	///
	/// @param _side Cubemap side, where 0 is +X, 1 is -X, 2 is +Y, 3 is
	///   -Y, 4 is +Z, and 5 is -Z.
	///
	void updateTextureCube(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem);

	/// Destroy texture.
	void destroyTexture(TextureHandle _handle);

	/// Create render target.
	RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags = BGFX_RENDER_TARGET_COLOR_RGBA8, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	/// Destroy render target.
	void destroyRenderTarget(RenderTargetHandle _handle);

	/// Create shader uniform parameter.
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
	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set view rectangle for multiple views.
	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	/// Set view scissor. Draw primitive outside view will be clipped. When
	/// _x, _y, _width and _height are set to 0, scissor will be disabled.
	void setViewScissor(uint8_t _id, uint16_t _x = 0, uint16_t _y = 0, uint16_t _width = 0, uint16_t _height = 0);

	/// Set view scissor for multiple views. When _x, _y, _width and _height
	/// are set to 0, scissor will be disabled.
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

	/// Set mulitple views into sequential mode.
	void setViewSeqMask(uint32_t _viewMask, bool _enabled);

	/// Set view render target.
	///
	/// @param _id View id.
	/// @param _handle Render target handle. Passing BGFX_INVALID_HANDLE as
	///   render target handle will draw primitives from this view into
	///   default backbuffer.
	///
	void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle);

	/// Set view render target for multiple views.
	///
	/// @param _viewMask View mask.
	/// @param _handle Render target handle. Passing BGFX_INVALID_HANDLE as
	///   render target handle will draw primitives from this view into
	///   default backbuffer.
	///
	void setViewRenderTargetMask(uint32_t _viewMask, RenderTargetHandle _handle);

	/// Set view view and projection matrices, all draw primitives in this
	/// view will use these matrices.
	void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other = 0xff);

	/// Set view view and projection matrices for multiple views.
	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other = 0xff);

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
	void setState(uint64_t _state, uint32_t _rgba = UINT32_MAX);

	/// Set stencil test state.
	///
	/// @param _fstencil Front stencil state.
	/// @param _bstencil Back stencil state. If back is set to BGFX_STENCIL_NONE
	///   _fstencil is applied to both front and back facing primitives.
	///
	void setStencil(uint32_t _fstencil, uint32_t _bstencil = BGFX_STENCIL_NONE);

	/// Set scissor for draw primitive.
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
	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _numIndices = UINT32_MAX);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices = UINT32_MAX);

	/// Set vertex buffer for draw primitive.
	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _numVertices = UINT32_MAX);

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
	/// @param _handle Render target handle.
	/// @param _flags Texture sampling mode. Default value UINT32_MAX uses
	///   texture sampling settings from the texture.
	///
	///   BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP] - Mirror or clamp to edge wrap
	///     mode.
	///
	///   BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC] - Point or anisotropic
	///     sampling.
	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth = false, uint32_t _flags = UINT32_MAX);

	/// Submit primitive for rendering into single view.
	///
	/// @param _id View id.
	/// @param _depth Depth for sorting.
	///
	void submit(uint8_t _id, int32_t _depth = 0);

	/// Submit primitive for rendering into multiple views.
	///
	/// @param _viewMask Mask to which views to submit draw primitive calls.
	/// @param _depth Depth for sorting.
	///
	void submitMask(uint32_t _viewMask, int32_t _depth = 0);

	/// Discard all previously set state for draw call.
	void discard();

	/// Request screen shot.
	void saveScreenShot(const char* _filePath);

} // namespace bgfx

#endif // __BGFX_H__

/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFX_H__
#define __BGFX_H__

#include <stdint.h> // uint32_t
#include <stdlib.h> // size_t

namespace bgfx
{
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

#define BGFX_CLEAR_NONE                 UINT8_C(0x00)
#define BGFX_CLEAR_COLOR_BIT            UINT8_C(0x01)
#define BGFX_CLEAR_DEPTH_BIT            UINT8_C(0x02)
#define BGFX_CLEAR_STENCIL_BIT          UINT8_C(0x04)

#define BGFX_DEBUG_NONE                 UINT32_C(0x00000000)
#define BGFX_DEBUG_WIREFRAME            UINT32_C(0x00000001)
#define BGFX_DEBUG_IFH                  UINT32_C(0x00000002)
#define BGFX_DEBUG_STATS                UINT32_C(0x00000004)
#define BGFX_DEBUG_TEXT                 UINT32_C(0x00000008)

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

#define BGFX_INVALID_HANDLE { bgfx::invalidHandle }

	struct Fatal
	{
		enum Enum
		{
			MinimumRequiredSpecs = 1,
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
			Null = 0,
			Direct3D9,
			Direct3D11,
			OpenGLES2,
			OpenGL,
		};
	};

	struct Attrib
	{
		enum Enum
		{
			Position = 0,
			Normal,
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

			Count,
		};
	};

	struct AttribType
	{
		enum Enum
		{
			Uint8,
			Uint16,
			Float,

			Count,
		};
	};

	static const uint16_t invalidHandle = 0xffff;

	typedef struct { uint16_t idx; } DynamicIndexBufferHandle;
	typedef struct { uint16_t idx; } DynamicVertexBufferHandle;
	typedef struct { uint16_t idx; } FragmentShaderHandle;
	typedef struct { uint16_t idx; } IndexBufferHandle;
	typedef struct { uint16_t idx; } MaterialHandle;
	typedef struct { uint16_t idx; } RenderTargetHandle;
	typedef struct { uint16_t idx; } TextureHandle;
	typedef struct { uint16_t idx; } UniformHandle;
	typedef struct { uint16_t idx; } VertexBufferHandle;
	typedef struct { uint16_t idx; } VertexDeclHandle;
	typedef struct { uint16_t idx; } VertexShaderHandle;

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

	struct ConstantType
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

	typedef void (*FatalFn)(Fatal::Enum _code, const char* _str);
	typedef void* (*ReallocFn)(void* _ptr, size_t _size);
	typedef void (*FreeFn)(void* _ptr);
	typedef void (*CacheFn)(uint64_t _id, bool _store, void* _data, uint32_t& _length);

	struct VertexDecl
	{
		void begin();
		void end();
		void add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized = false);
		void decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized) const;

		uint32_t m_hash;
		uint16_t m_stride;
		uint16_t m_offset[Attrib::Count];
		uint8_t m_attributes[Attrib::Count];
	};

	///
	RendererType::Enum getRendererType();

	///
	void init(bool _createRenderThread = true, FatalFn _fatal = NULL, ReallocFn _realloc = NULL, FreeFn _free = NULL, CacheFn _cache = NULL);

	///
	void shutdown();

	///
	void reset(uint32_t _width, uint32_t _height, uint32_t _flags = BGFX_RESET_NONE);

	///
	void frame();

	///
	const Memory* alloc(uint32_t _size);

	///
	const Memory* makeRef(void* _data, uint32_t _size);

	///
	void setDebug(uint32_t _debug);

	///
	void dbgTextClear(uint8_t _attr = 0, bool _small = false);

	///
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

	///
	bool checkAvailTransientIndexBuffer(uint16_t _num);

	///
	const TransientIndexBuffer* allocTransientIndexBuffer(uint16_t _num);

	///
	bool checkAvailTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	///
	const TransientVertexBuffer* allocTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl);

	///
	const InstanceDataBuffer* allocInstanceDataBuffer(uint16_t _num, uint16_t _stride);

	///
	VertexShaderHandle createVertexShader(const Memory* _mem);

	///
	void destroyVertexShader(VertexShaderHandle _handle);

	///
	FragmentShaderHandle createFragmentShader(const Memory* _mem);

	///
	void destroyFragmentShader(FragmentShaderHandle _handle);

	///
	MaterialHandle createMaterial(VertexShaderHandle _vsh, FragmentShaderHandle _fsh);

	///
	void destroyMaterial(MaterialHandle _handle);

	///
	TextureHandle createTexture(const Memory* _mem, uint32_t _flags = BGFX_TEXTURE_NONE, uint16_t* _width = NULL, uint16_t* _height = NULL);

	///
	void destroyTexture(TextureHandle _handle);

	///
	RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags = BGFX_RENDER_TARGET_COLOR_RGBA, uint32_t _textureFlags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);

	///
	void destroyRenderTarget(RenderTargetHandle _handle);

	///
	UniformHandle createUniform(const char* _name, ConstantType::Enum _type, uint16_t _num = 1);

	///
	void destroyUniform(UniformHandle _handle);

	///
	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	///
	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height);

	///
	void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	///
	void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0);

	///
	void setViewSeq(uint8_t _id, bool _enabled);

	///
	void setViewSeqMask(uint32_t _viewMask, bool _enabled);

	///
	void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle);

	///
	void setViewRenderTargetMask(uint32_t _viewMask, RenderTargetHandle _handle);

	///
	void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other = 0xff);

	///
	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other = 0xff);

	///
	void setState(uint64_t _state);

	///
	uint32_t setTransform(const void* _mtx, uint16_t _num = 1);

	///
	void setTransform(uint32_t _cache = 0, uint16_t _num = 1);

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
	void setIndexBuffer(const TransientIndexBuffer* _ib, uint32_t _numIndices = 0xffffffff);

	///
	void setVertexBuffer(VertexBufferHandle _handle);

	///
	void setVertexBuffer(DynamicVertexBufferHandle _handle);

	///
	void setVertexBuffer(const TransientVertexBuffer* _vb);

	///
	void setInstanceDataBuffer(const InstanceDataBuffer* _idb);

	///
	void setMaterial(MaterialHandle _handle);

	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle);

	///
	void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth = false);

	///
	void submit(uint8_t _id);

	///
	void submitMask(uint32_t _viewMask);

	///
	void saveScreenShot(const char* _filePath);

} // namespace bgfx

#endif // __BGFX_H__

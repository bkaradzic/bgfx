/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NULL

namespace bgfx { namespace noop
{
	struct RendererContextNULL : public RendererContextI
	{
		RendererContextNULL()
		{
		}

		~RendererContextNULL()
		{
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Null;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			return BGFX_RENDERER_NULL_NAME;
		}

		void flip(HMD& /*_hmd*/) BX_OVERRIDE
		{
		}

		void createIndexBuffer(IndexBufferHandle /*_handle*/, Memory* /*_mem*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
		}

		void destroyIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createVertexDecl(VertexDeclHandle /*_handle*/, const VertexDecl& /*_decl*/) BX_OVERRIDE
		{
		}

		void destroyVertexDecl(VertexDeclHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createVertexBuffer(VertexBufferHandle /*_handle*/, Memory* /*_mem*/, VertexDeclHandle /*_declHandle*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
		}

		void destroyVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
		}

		void updateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
		{
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
		}

		void updateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
		{
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createShader(ShaderHandle /*_handle*/, Memory* /*_mem*/) BX_OVERRIDE
		{
		}

		void destroyShader(ShaderHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createProgram(ProgramHandle /*_handle*/, ShaderHandle /*_vsh*/, ShaderHandle /*_fsh*/) BX_OVERRIDE
		{
		}

		void destroyProgram(ProgramHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createTexture(TextureHandle /*_handle*/, Memory* /*_mem*/, uint32_t /*_flags*/, uint8_t /*_skip*/) BX_OVERRIDE
		{
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) BX_OVERRIDE
		{
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, uint16_t /*_pitch*/, const Memory* /*_mem*/) BX_OVERRIDE
		{
		}

		void updateTextureEnd() BX_OVERRIDE
		{
		}

		void readTexture(TextureHandle /*_handle*/, void* /*_data*/) BX_OVERRIDE
		{
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/) BX_OVERRIDE
		{
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) BX_OVERRIDE
		{
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) BX_OVERRIDE
		{
			return 0;
		}

		void destroyTexture(TextureHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, uint8_t /*_num*/, const Attachment* /*_attachment*/) BX_OVERRIDE
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_depthFormat*/) BX_OVERRIDE
		{
		}

		void destroyFrameBuffer(FrameBufferHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createUniform(UniformHandle /*_handle*/, UniformType::Enum /*_type*/, uint16_t /*_num*/, const char* /*_name*/) BX_OVERRIDE
		{
		}

		void destroyUniform(UniformHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void saveScreenShot(const char* /*_filePath*/) BX_OVERRIDE
		{
		}

		void updateViewName(uint8_t /*_id*/, const char* /*_name*/) BX_OVERRIDE
		{
		}

		void updateUniform(uint16_t /*_loc*/, const void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
		{
		}

		void setMarker(const char* /*_marker*/, uint32_t /*_size*/) BX_OVERRIDE
		{
		}

		void submit(Frame* /*_render*/, ClearQuad& /*_clearQuad*/, TextVideoMemBlitter& /*_textVideoMemBlitter*/) BX_OVERRIDE
		{
		}

		void blitSetup(TextVideoMemBlitter& /*_blitter*/) BX_OVERRIDE
		{
		}

		void blitRender(TextVideoMemBlitter& /*_blitter*/, uint32_t /*_numIndices*/) BX_OVERRIDE
		{
		}
	};

	static RendererContextNULL* s_renderNULL;

	RendererContextI* rendererCreate()
	{
		s_renderNULL = BX_NEW(g_allocator, RendererContextNULL);
		return s_renderNULL;
	}

	void rendererDestroy()
	{
		BX_DELETE(g_allocator, s_renderNULL);
		s_renderNULL = NULL;
	}
} /* namespace noop */ } // namespace bgfx

#else

namespace bgfx { namespace noop
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace noop */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_NULL

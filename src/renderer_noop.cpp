/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NOOP

namespace bgfx { namespace noop
{
	struct RendererContextNOOP : public RendererContextI
	{
		RendererContextNOOP()
		{
			// Pretend all features that are not returning results to CPU
			// are available.
			g_caps.supported = 0
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_FRAGMENT_ORDERING
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_DRAW_INDIRECT
				| BGFX_CAPS_HIDPI
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_CONSERVATIVE_RASTER
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_CUBE_ARRAY
				;
		}

		~RendererContextNOOP()
		{
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Noop;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			return BGFX_RENDERER_NOOP_NAME;
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

		void readTexture(TextureHandle /*_handle*/, void* /*_data*/, uint8_t /*_mip*/) BX_OVERRIDE
		{
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/) BX_OVERRIDE
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

		void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) BX_OVERRIDE
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

		void invalidateOcclusionQuery(OcclusionQueryHandle /*_handle*/) BX_OVERRIDE
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

	static RendererContextNOOP* s_renderNOOP;

	RendererContextI* rendererCreate()
	{
		s_renderNOOP = BX_NEW(g_allocator, RendererContextNOOP);
		return s_renderNOOP;
	}

	void rendererDestroy()
	{
		BX_DELETE(g_allocator, s_renderNOOP);
		s_renderNOOP = NULL;
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

#endif // BGFX_CONFIG_RENDERER_NOOP

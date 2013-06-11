/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NULL

namespace bgfx
{
	void ConstantBuffer::commit()
	{
	}

	void TextVideoMemBlitter::setup()
	{
	}

	void TextVideoMemBlitter::render(uint32_t /*_numIndices*/)
	{
	}

	void Context::flip()
	{
	}

	void Context::rendererInit()
	{
	}

	void Context::rendererShutdown()
	{
	}

	void Context::rendererCreateIndexBuffer(IndexBufferHandle /*_handle*/, Memory* /*_mem*/)
	{
	}

	void Context::rendererDestroyIndexBuffer(IndexBufferHandle /*_handle*/)
	{
	}

	void Context::rendererCreateVertexDecl(VertexDeclHandle /*_handle*/, const VertexDecl& /*_decl*/)
	{
	}

	void Context::rendererDestroyVertexDecl(VertexDeclHandle /*_handle*/)
	{
	}

	void Context::rendererCreateVertexBuffer(VertexBufferHandle /*_handle*/, Memory* /*_mem*/, VertexDeclHandle /*_declHandle*/)
	{
	}

	void Context::rendererDestroyVertexBuffer(VertexBufferHandle /*_handle*/)
	{
	}

	void Context::rendererCreateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_size*/)
	{
	}

	void Context::rendererUpdateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/)
	{
	}

	void Context::rendererDestroyDynamicIndexBuffer(IndexBufferHandle /*_handle*/)
	{
	}

	void Context::rendererCreateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_size*/)
	{
	}

	void Context::rendererUpdateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/)
	{
	}

	void Context::rendererDestroyDynamicVertexBuffer(VertexBufferHandle /*_handle*/)
	{
	}

	void Context::rendererCreateVertexShader(VertexShaderHandle /*_handle*/, Memory* /*_mem*/)
	{
	}

	void Context::rendererDestroyVertexShader(VertexShaderHandle /*_handle*/)
	{
	}

	void Context::rendererCreateFragmentShader(FragmentShaderHandle /*_handle*/, Memory* /*_mem*/)
	{
	}

	void Context::rendererDestroyFragmentShader(FragmentShaderHandle /*_handle*/)
	{
	}

	void Context::rendererCreateProgram(ProgramHandle /*_handle*/, VertexShaderHandle /*_vsh*/, FragmentShaderHandle /*_fsh*/)
	{
	}

	void Context::rendererDestroyProgram(FragmentShaderHandle /*_handle*/)
	{
	}

	void Context::rendererCreateTexture(TextureHandle /*_handle*/, Memory* _mem, uint32_t /*_flags*/)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		if (BGFX_CHUNK_MAGIC_TEX == magic)
		{
			TextureCreate tc;
			bx::read(&reader, tc);

			if (NULL != tc.m_mem)
			{
				release(tc.m_mem);
			}
		}
	}

	void Context::rendererUpdateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/)
	{
	}

	void Context::rendererUpdateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, const Memory* /*_mem*/)
	{
	}

	void Context::rendererUpdateTextureEnd()
	{
	}

	void Context::rendererDestroyTexture(TextureHandle /*_handle*/)
	{
	}

	void Context::rendererCreateRenderTarget(RenderTargetHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint32_t /*_flags*/, uint32_t /*_textureFlags*/)
	{
	}

	void Context::rendererDestroyRenderTarget(RenderTargetHandle /*_handle*/)
	{
	}

	void Context::rendererCreateUniform(UniformHandle /*_handle*/, UniformType::Enum /*_type*/, uint16_t /*_num*/, const char* /*_name*/)
	{
	}

	void Context::rendererDestroyUniform(UniformHandle /*_handle*/)
	{
	}

	void Context::rendererSaveScreenShot(const char* /*_filePath*/)
	{
	}

	void Context::rendererUpdateViewName(uint8_t /*_id*/, const char* /*_name*/)
	{
	}

	void Context::rendererUpdateUniform(uint16_t /*_loc*/, const void* /*_data*/, uint32_t /*_size*/)
	{
	}

	void Context::rendererSetMarker(const char* /*_marker*/, uint32_t /*_size*/)
	{
	}

	void Context::rendererSubmit()
	{
	}
}

#endif // BGFX_CONFIG_RENDERER_NULL

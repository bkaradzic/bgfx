/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_D3D11_H_HEADER_GUARD
#define BGFX_RENDERER_D3D11_H_HEADER_GUARD

#define USE_D3D11_DYNAMIC_LIB !BX_PLATFORM_WINRT

#if !USE_D3D11_DYNAMIC_LIB
#	undef  BGFX_CONFIG_DEBUG_PIX
#	define BGFX_CONFIG_DEBUG_PIX 0
#endif // !USE_D3D11_DYNAMIC_LIB

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas" );
BX_PRAGMA_DIAGNOSTIC_IGNORED_GCC("-Wpragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4005) // warning C4005: '' : macro redefinition
#define D3D11_NO_HELPERS
#include <d3d11.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#include "renderer_d3d.h"

#define D3DCOLOR_ARGB(_a, _r, _g, _b) ( (DWORD)( ( ( (_a)&0xff)<<24)|( ( (_r)&0xff)<<16)|( ( (_g)&0xff)<<8)|( (_b)&0xff) ) )
#define D3DCOLOR_RGBA(_r, _g, _b, _a) D3DCOLOR_ARGB(_a, _r, _g, _b)

namespace bgfx
{
	struct IndexBufferD3D11
	{
		IndexBufferD3D11()
			: m_ptr(NULL)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data);
		void update(uint32_t _offset, uint32_t _size, void* _data);

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}
		}

		ID3D11Buffer* m_ptr;
		uint32_t m_size;
		bool m_dynamic;
	};

	struct VertexBufferD3D11
	{
		VertexBufferD3D11()
			: m_ptr(NULL)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}
		}

		ID3D11Buffer* m_ptr;
		uint32_t m_size;
		VertexDeclHandle m_decl;
		bool m_dynamic;
	};

	struct ShaderD3D11
	{
		ShaderD3D11()
			: m_ptr(NULL)
			, m_code(NULL)
			, m_buffer(NULL)
			, m_constantBuffer(NULL)
			, m_hash(0)
			, m_numUniforms(0)
			, m_numPredefined(0)
		{
		}

		void create(const Memory* _mem);
		DWORD* getShaderCode(uint8_t _fragmentBit, const Memory* _mem);

		void destroy()
		{
			if (NULL != m_constantBuffer)
			{
				ConstantBuffer::destroy(m_constantBuffer);
				m_constantBuffer = NULL;
			}

			m_numPredefined = 0;

			if (NULL != m_buffer)
			{
				DX_RELEASE(m_buffer, 0);
			}

			DX_RELEASE(m_ptr, 0);

			if (NULL != m_code)
			{
				release(m_code);
				m_code = NULL;
				m_hash = 0;
			}
		}

		union
		{
			ID3D11ComputeShader* m_computeShader;
			ID3D11PixelShader*   m_pixelShader;
			ID3D11VertexShader*  m_vertexShader;
			IUnknown*            m_ptr;
		};
		const Memory* m_code;
		ID3D11Buffer* m_buffer;
		ConstantBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_attrMask[Attrib::Count];

		uint32_t m_hash;

		uint16_t m_numUniforms;
		uint8_t m_numPredefined;
	};

	struct ProgramD3D11
	{
		ProgramD3D11()
			: m_vsh(NULL)
			, m_fsh(NULL)
		{
		}

		void create(const ShaderD3D11* _vsh, const ShaderD3D11* _fsh)
		{
			BX_CHECK(NULL != _vsh->m_ptr, "Vertex shader doesn't exist.");
			m_vsh = _vsh;
			memcpy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform) );
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				BX_CHECK(NULL != _fsh->m_ptr, "Fragment shader doesn't exist.");
				m_fsh = _fsh;
				memcpy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform) );
				m_numPredefined += _fsh->m_numPredefined;
			}
		}

		void destroy()
		{
			m_numPredefined = 0;
			m_vsh = NULL;
			m_fsh = NULL;
		}

		const ShaderD3D11* m_vsh;
		const ShaderD3D11* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count*2];
		uint8_t m_numPredefined;
	};

	struct TextureD3D11
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureD3D11()
			: m_ptr(NULL)
			, m_srv(NULL)
			, m_uav(NULL)
			, m_sampler(NULL)
			, m_numMips(0)
		{
		}

		void create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
		void destroy();
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void commit(uint8_t _stage, uint32_t _flags = BGFX_SAMPLER_DEFAULT_FLAGS);
		void resolve();

		union
		{
			ID3D11Resource* m_ptr;
			ID3D11Texture2D* m_texture2d;
			ID3D11Texture3D* m_texture3d;
		};

		ID3D11ShaderResourceView* m_srv;
		ID3D11UnorderedAccessView* m_uav;
		ID3D11SamplerState* m_sampler;
		uint32_t m_flags;
		uint8_t m_type;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
		uint8_t m_numMips;
	};

	struct FrameBufferD3D11
	{
		FrameBufferD3D11()
			: m_denseIdx(UINT16_MAX)
			, m_num(0)
		{
		}

		void create(uint8_t _num, const TextureHandle* _handles);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		void resolve();
		void clear(const Clear& _clear, const float _palette[][4]);

		ID3D11RenderTargetView* m_rtv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11ShaderResourceView* m_srv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11DepthStencilView* m_dsv;
		IDXGISwapChain* m_swapChain;
		uint16_t m_denseIdx;
		uint8_t m_num;
	};

} // namespace bgfx

#endif // BGFX_RENDERER_D3D11_H_HEADER_GUARD

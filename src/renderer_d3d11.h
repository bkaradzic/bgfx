/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
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
#if BX_PLATFORM_WINRT
#include <d3d11_2.h>
#else
#include <d3d11.h>
#endif
BX_PRAGMA_DIAGNOSTIC_POP()

#include "renderer.h"
#include "renderer_d3d.h"
#include "ovr.h"
#include "renderdoc.h"

#ifndef D3DCOLOR_ARGB
#	define D3DCOLOR_ARGB(_a, _r, _g, _b) ( (DWORD)( ( ( (_a)&0xff)<<24)|( ( (_r)&0xff)<<16)|( ( (_g)&0xff)<<8)|( (_b)&0xff) ) )
#endif // D3DCOLOR_ARGB

#ifndef D3DCOLOR_RGBA
#	define D3DCOLOR_RGBA(_r, _g, _b, _a) D3DCOLOR_ARGB(_a, _r, _g, _b)
#endif // D3DCOLOR_RGBA

#ifndef DXGI_FORMAT_B4G4R4A4_UNORM
// Win8 only BS
// https://blogs.msdn.com/b/chuckw/archive/2012/11/14/directx-11-1-and-windows-7.aspx?Redirected=true
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb173059%28v=vs.85%29.aspx
#	define DXGI_FORMAT_B4G4R4A4_UNORM DXGI_FORMAT(115)
#endif // DXGI_FORMAT_B4G4R4A4_UNORM

#ifndef D3D_FEATURE_LEVEL_11_1
#	define D3D_FEATURE_LEVEL_11_1 D3D_FEATURE_LEVEL(0xb100)
#endif // D3D_FEATURE_LEVEL_11_1

#if defined(__MINGW32__)
// MinGW Linux/Wine missing defines...
#	ifndef D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT
#		define D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT 8
#	endif // D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT

#	ifndef D3D11_PS_CS_UAV_REGISTER_COUNT
#		define D3D11_PS_CS_UAV_REGISTER_COUNT 8
#	endif // D3D11_PS_CS_UAV_REGISTER_COUNT

#	ifndef D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT
#		define D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 8
#	endif

#	ifndef D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
#		define D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT 8
#	endif // D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT

#	ifndef D3D11_APPEND_ALIGNED_ELEMENT
#		define D3D11_APPEND_ALIGNED_ELEMENT UINT32_MAX
#	endif // D3D11_APPEND_ALIGNED_ELEMENT

#	ifndef D3D11_REQ_MAXANISOTROPY
#		define	D3D11_REQ_MAXANISOTROPY	16
#	endif // D3D11_REQ_MAXANISOTROPY

#	ifndef D3D11_FEATURE_DATA_FORMAT_SUPPORT
typedef struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
{
	DXGI_FORMAT InFormat;
	UINT OutFormatSupport;
} D3D11_FEATURE_DATA_FORMAT_SUPPORT;
#	endif // D3D11_FEATURE_DATA_FORMAT_SUPPORT

#	ifndef D3D11_FEATURE_DATA_FORMAT_SUPPORT2
typedef struct D3D11_FEATURE_DATA_FORMAT_SUPPORT2
{
	DXGI_FORMAT InFormat;
	UINT OutFormatSupport2;
} D3D11_FEATURE_DATA_FORMAT_SUPPORT2;
#	endif // D3D11_FEATURE_DATA_FORMAT_SUPPORT2
#endif // __MINGW32__

namespace bgfx { namespace d3d11
{
	struct BufferD3D11
	{
		BufferD3D11()
			: m_ptr(NULL)
			, m_srv(NULL)
			, m_uav(NULL)
			, m_flags(BGFX_BUFFER_NONE)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data, uint8_t _flags, uint16_t _stride = 0, bool _vertex = false);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}

			DX_RELEASE(m_srv, 0);
			DX_RELEASE(m_uav, 0);
		}

		ID3D11Buffer* m_ptr;
		ID3D11ShaderResourceView*  m_srv;
		ID3D11UnorderedAccessView* m_uav;
		uint32_t m_size;
		uint8_t m_flags;
		bool m_dynamic;
	};

	typedef BufferD3D11 IndexBufferD3D11;

	struct VertexBufferD3D11 : public BufferD3D11
	{
		VertexBufferD3D11()
			: BufferD3D11()
		{
		}

		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint8_t _flags);

		VertexDeclHandle m_decl;
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
			, m_numTh(0)
			, m_dsv(NULL)
		{
		}

		void create(uint8_t _num, const TextureHandle* _handles);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		void preReset();
		void postReset();
		void resolve();
		void clear(const Clear& _clear, const float _palette[][4]);

		ID3D11RenderTargetView* m_rtv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11ShaderResourceView* m_srv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11DepthStencilView* m_dsv;
		IDXGISwapChain* m_swapChain;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		TextureHandle m_th[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

} /*  namespace d3d11 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D11_H_HEADER_GUARD

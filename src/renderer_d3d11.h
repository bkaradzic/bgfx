/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_D3D11_H_HEADER_GUARD
#define BGFX_RENDERER_D3D11_H_HEADER_GUARD

#define USE_D3D11_DYNAMIC_LIB BX_PLATFORM_WINDOWS

#if !USE_D3D11_DYNAMIC_LIB
#	undef  BGFX_CONFIG_DEBUG_PIX
#	define BGFX_CONFIG_DEBUG_PIX 0
#endif // !USE_D3D11_DYNAMIC_LIB

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas" );
BX_PRAGMA_DIAGNOSTIC_IGNORED_GCC("-Wpragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4005) // warning C4005: '' : macro redefinition
#include <sal.h>
#define D3D11_NO_HELPERS
#if BX_PLATFORM_WINDOWS
#	include <d3d11_3.h>
#	include <dxgi1_3.h>
#elif BX_PLATFORM_WINRT
#	include <d3d11_3.h>
#else
#	include <d3d11_x.h>
#endif // BX_PLATFORM_*
BX_PRAGMA_DIAGNOSTIC_POP()

#include "renderer.h"
#include "renderer_d3d.h"
#include "shader_dxbc.h"
#include "hmd.h"
#include "hmd_openvr.h"
#include "debug_renderdoc.h"

#ifndef D3DCOLOR_ARGB
#	define D3DCOLOR_ARGB(_a, _r, _g, _b) ( (DWORD)( ( ( (_a)&0xff)<<24)|( ( (_r)&0xff)<<16)|( ( (_g)&0xff)<<8)|( (_b)&0xff) ) )
#endif // D3DCOLOR_ARGB

#ifndef D3DCOLOR_RGBA
#	define D3DCOLOR_RGBA(_r, _g, _b, _a) D3DCOLOR_ARGB(_a, _r, _g, _b)
#endif // D3DCOLOR_RGBA

#define BGFX_D3D11_BLEND_STATE_MASK (0 \
			| BGFX_STATE_BLEND_MASK \
			| BGFX_STATE_BLEND_EQUATION_MASK \
			| BGFX_STATE_BLEND_INDEPENDENT \
			| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE \
			| BGFX_STATE_ALPHA_WRITE \
			| BGFX_STATE_RGB_WRITE \
			)

#define BGFX_D3D11_DEPTH_STENCIL_MASK (0 \
			| BGFX_STATE_DEPTH_WRITE \
			| BGFX_STATE_DEPTH_TEST_MASK \
			)

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

		void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
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
		uint16_t m_flags;
		bool m_dynamic;
	};

	typedef BufferD3D11 IndexBufferD3D11;

	struct VertexBufferD3D11 : public BufferD3D11
	{
		VertexBufferD3D11()
			: BufferD3D11()
		{
		}

		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags);

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
			, m_hasDepthOp(false)
		{
		}

		void create(const Memory* _mem);

		void destroy()
		{
			if (NULL != m_constantBuffer)
			{
				UniformBuffer::destroy(m_constantBuffer);
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
		UniformBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];

		uint32_t m_hash;

		uint16_t m_numUniforms;
		uint8_t m_numPredefined;
		bool m_hasDepthOp;
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
			bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform) );
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				BX_CHECK(NULL != _fsh->m_ptr, "Fragment shader doesn't exist.");
				m_fsh = _fsh;
				bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform) );
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
			, m_rt(NULL)
			, m_srv(NULL)
			, m_uav(NULL)
			, m_numMips(0)
		{
		}

		void create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
		void destroy();
		void overrideInternal(uintptr_t _ptr);
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void commit(uint8_t _stage, uint32_t _flags, const float _palette[][4]);
		void resolve() const;
		TextureHandle getHandle() const;

		union
		{
			ID3D11Resource*  m_ptr;
			ID3D11Texture2D* m_texture2d;
			ID3D11Texture3D* m_texture3d;
		};

		union
		{
			ID3D11Resource* m_rt;
			ID3D11Texture2D* m_rt2d;
		};

		ID3D11ShaderResourceView*  m_srv;
		ID3D11UnorderedAccessView* m_uav;
		uint32_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t  m_type;
		uint8_t  m_requestedFormat;
		uint8_t  m_textureFormat;
		uint8_t  m_numMips;
	};

	struct FrameBufferD3D11
	{
		FrameBufferD3D11()
			: m_dsv(NULL)
			, m_swapChain(NULL)
			, m_width(0)
			, m_height(0)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
			, m_numTh(0)
			, m_needPresent(false)
		{
		}

		void create(uint8_t _num, const Attachment* _attachment);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		void preReset(bool _force = false);
		void postReset();
		void resolve();
		void clear(const Clear& _clear, const float _palette[][4]);
		void set();
		HRESULT present(uint32_t _syncInterval);

		ID3D11RenderTargetView* m_rtv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11ShaderResourceView* m_srv[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		ID3D11DepthStencilView* m_dsv;
		IDXGISwapChain* m_swapChain;
		uint32_t m_width;
		uint32_t m_height;

		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		bool m_needPresent;
	};

	struct TimerQueryD3D11
	{
		TimerQueryD3D11()
			: m_control(BX_COUNTOF(m_frame) )
		{
		}

		void postReset();
		void preReset();
		void begin();
		void end();
		bool get();

		struct Frame
		{
			ID3D11Query* m_disjoint;
			ID3D11Query* m_begin;
			ID3D11Query* m_end;
		};

		uint64_t m_begin;
		uint64_t m_end;
		uint64_t m_elapsed;
		uint64_t m_frequency;

		Frame m_frame[4];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryD3D11
	{
		OcclusionQueryD3D11()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		void postReset();
		void preReset();
		void begin(Frame* _render, OcclusionQueryHandle _handle);
		void end();
		void resolve(Frame* _render, bool _wait = false);
		void invalidate(OcclusionQueryHandle _handle);

		struct Query
		{
			ID3D11Query* m_ptr;
			OcclusionQueryHandle m_handle;
		};

		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /*  namespace d3d11 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D11_H_HEADER_GUARD

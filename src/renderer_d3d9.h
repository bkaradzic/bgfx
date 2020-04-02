/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_D3D9_H_HEADER_GUARD
#define BGFX_RENDERER_D3D9_H_HEADER_GUARD

#define BGFX_CONFIG_RENDERER_DIRECT3D9EX BX_PLATFORM_WINDOWS

#if BX_PLATFORM_WINDOWS
#	include <sal.h>
#	include <d3d9.h>
#endif // BX_PLATFORM_

#ifndef D3DSTREAMSOURCE_INDEXEDDATA
#	define D3DSTREAMSOURCE_INDEXEDDATA  (1<<30)
#endif// D3DSTREAMSOURCE_INDEXEDDATA

#ifndef D3DSTREAMSOURCE_INSTANCEDATA
#	define D3DSTREAMSOURCE_INSTANCEDATA (2<<30)
#endif // D3DSTREAMSOURCE_INSTANCEDATA

#include "renderer.h"
#include "renderer_d3d.h"
#include "nvapi.h"

#define BGFX_D3D9_PROFILER_BEGIN(_view, _abgr)         \
	BX_MACRO_BLOCK_BEGIN                               \
		PIX_BEGINEVENT(_abgr, s_viewNameW[_view]);     \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr);  \
	BX_MACRO_BLOCK_END

#define BGFX_D3D9_PROFILER_BEGIN_LITERAL(_name, _abgr) \
	BX_MACRO_BLOCK_BEGIN                               \
		PIX_BEGINEVENT(_abgr, L"" _name);              \
		BGFX_PROFILER_BEGIN_LITERAL("" _name, _abgr);  \
	BX_MACRO_BLOCK_END

#define BGFX_D3D9_PROFILER_END()                       \
	BX_MACRO_BLOCK_BEGIN                               \
		BGFX_PROFILER_END();                           \
		PIX_ENDEVENT();                                \
	BX_MACRO_BLOCK_END

namespace bgfx { namespace d3d9
{
#	if defined(D3D_DISABLE_9EX)
#		define D3DFMT_S8_LOCKABLE D3DFORMAT( 85)
#		define D3DFMT_A1          D3DFORMAT(118)
#	endif // defined(D3D_DISABLE_9EX)

#	ifndef D3DFMT_ATI1
#		define D3DFMT_ATI1 ( (D3DFORMAT)BX_MAKEFOURCC('A', 'T', 'I', '1') )
#	endif // D3DFMT_ATI1

#	ifndef D3DFMT_ATI2
#		define D3DFMT_ATI2 ( (D3DFORMAT)BX_MAKEFOURCC('A', 'T', 'I', '2') )
#	endif // D3DFMT_ATI2

#	ifndef D3DFMT_ATOC
#		define D3DFMT_ATOC ( (D3DFORMAT)BX_MAKEFOURCC('A', 'T', 'O', 'C') )
#	endif // D3DFMT_ATOC

#	ifndef D3DFMT_DF16
#		define D3DFMT_DF16 ( (D3DFORMAT)BX_MAKEFOURCC('D', 'F', '1', '6') )
#	endif // D3DFMT_DF16

#	ifndef D3DFMT_DF24
#		define D3DFMT_DF24 ( (D3DFORMAT)BX_MAKEFOURCC('D', 'F', '2', '4') )
#	endif // D3DFMT_DF24

#	ifndef D3DFMT_INST
#		define D3DFMT_INST ( (D3DFORMAT)BX_MAKEFOURCC('I', 'N', 'S', 'T') )
#	endif // D3DFMT_INST

#	ifndef D3DFMT_INTZ
#		define D3DFMT_INTZ ( (D3DFORMAT)BX_MAKEFOURCC('I', 'N', 'T', 'Z') )
#	endif // D3DFMT_INTZ

#	ifndef D3DFMT_NULL
#		define D3DFMT_NULL ( (D3DFORMAT)BX_MAKEFOURCC('N', 'U', 'L', 'L') )
#	endif // D3DFMT_NULL

#	ifndef D3DFMT_RESZ
#		define D3DFMT_RESZ ( (D3DFORMAT)BX_MAKEFOURCC('R', 'E', 'S', 'Z') )
#	endif // D3DFMT_RESZ

#	ifndef D3DFMT_RAWZ
#		define D3DFMT_RAWZ ( (D3DFORMAT)BX_MAKEFOURCC('R', 'A', 'W', 'Z') )
#	endif // D3DFMT_RAWZ

#	ifndef D3DFMT_S8_LOCKABLE
#		define D3DFMT_S8_LOCKABLE ( (D3DFORMAT)85)
#	endif // D3DFMT_S8_LOCKABLE

#	ifndef D3DFMT_A1
#		define D3DFMT_A1 ( (D3DFORMAT)118)
#	endif // D3DFMT_A1

	struct ExtendedFormat
	{
		enum Enum
		{
			Ati1,
			Ati2,
			Df16,
			Df24,
			Inst,
			Intz,
			Null,
			Resz,
			Rawz,
			Atoc,

			Count,
		};

		D3DFORMAT m_fmt;
		DWORD m_usage;
		D3DRESOURCETYPE m_type;
		bool m_supported;
	};

	struct Msaa
	{
		D3DMULTISAMPLE_TYPE m_type;
		DWORD m_quality;
	};

	struct IndexBufferD3D9
	{
		IndexBufferD3D9()
			: m_ptr(NULL)
			, m_dynamic(NULL)
			, m_size(0)
			, m_flags(BGFX_BUFFER_NONE)
		{
		}

		void create(uint32_t _size, void* _data, uint16_t _flags);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			if (NULL  != m_dynamic
			&&  _data != m_dynamic)
			{
				bx::memCopy(&m_dynamic[_offset], _data, _size);
			}

			void* buffer;
			DX_CHECK(m_ptr->Lock(_offset
				, _size
				, &buffer
				, _discard || (m_dynamic && 0 == _offset && m_size == _size) ? D3DLOCK_DISCARD : 0
				) );

			bx::memCopy(buffer, _data, _size);

			DX_CHECK(m_ptr->Unlock() );
		}

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);

				if (NULL != m_dynamic)
				{
					BX_FREE(g_allocator, m_dynamic);
					m_dynamic = NULL;
				}
			}
		}

		void preReset();
		void postReset();

		IDirect3DIndexBuffer9* m_ptr;
		uint8_t* m_dynamic;
		uint32_t m_size;
		uint16_t m_flags;
	};

	struct VertexBufferD3D9
	{
		VertexBufferD3D9()
			: m_ptr(NULL)
			, m_dynamic(NULL)
			, m_size(0)
		{
		}

		void create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			if (NULL  != m_dynamic
			&&  _data != m_dynamic)
			{
				bx::memCopy(&m_dynamic[_offset], _data, _size);
			}

			void* buffer;
			DX_CHECK(m_ptr->Lock(_offset
				, _size
				, &buffer
				, _discard || (m_dynamic && 0 == _offset && m_size == _size) ? D3DLOCK_DISCARD : 0
				) );

			bx::memCopy(buffer, _data, _size);

			DX_CHECK(m_ptr->Unlock() );
		}

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);

				if (NULL != m_dynamic)
				{
					BX_FREE(g_allocator, m_dynamic);
					m_dynamic = NULL;
				}
			}
		}

		void preReset();
		void postReset();

		IDirect3DVertexBuffer9* m_ptr;
		uint8_t* m_dynamic;
		uint32_t m_size;
		VertexLayoutHandle m_layoutHandle;
	};

	struct ShaderD3D9
	{
		ShaderD3D9()
			: m_vertexShader(NULL)
			, m_constantBuffer(NULL)
			, m_numPredefined(0)
			, m_type(0)
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

			switch (m_type)
			{
			case 0:  DX_RELEASE(m_vertexShader, 0); BX_FALLTHROUGH;
			default: DX_RELEASE(m_pixelShader,  0);
			}
		}

		union
		{
			// X360 doesn't have interface inheritance (can't use IUnknown*).
			IDirect3DVertexShader9* m_vertexShader;
			IDirect3DPixelShader9*  m_pixelShader;
		};
		UniformBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
		uint8_t m_type;
	};

	struct ProgramD3D9
	{
		void create(const ShaderD3D9* _vsh, const ShaderD3D9* _fsh)
		{
			m_vsh = _vsh;
			m_fsh = _fsh;

			bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform) );
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				bx::memCopy(&m_predefined[_vsh->m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform) );
				m_numPredefined += _fsh->m_numPredefined;
			}
		}

		void destroy()
		{
			m_numPredefined = 0;
			m_vsh = NULL;
			m_fsh = NULL;
		}

		const ShaderD3D9* m_vsh;
		const ShaderD3D9* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count*2];
		uint8_t m_numPredefined;
	};

	struct TextureD3D9
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureD3D9()
			: m_ptr(NULL)
			, m_surface(NULL)
			, m_staging(NULL)
			, m_textureFormat(TextureFormat::Unknown)
		{
		}

		void createTexture(uint32_t _width, uint32_t _height, uint8_t _numMips);
		void createVolumeTexture(uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips);
		void createCubeTexture(uint32_t _width, uint8_t _numMips);

		uint8_t* lock(uint8_t _side, uint8_t _lod, uint32_t& _pitch, uint32_t& _slicePitch, const Rect* _rect = NULL);
		void unlock(uint8_t _side, uint8_t _lod);
		void dirty(uint8_t _side, const Rect& _rect, uint16_t _z, uint16_t _depth);
		IDirect3DSurface9* getSurface(uint8_t _side = 0, uint8_t _mip = 0) const;

		void create(const Memory* _mem, uint64_t _flags, uint8_t _skip);

		void destroy(bool _resize = false)
		{
			if (0 == (m_flags & BGFX_SAMPLER_INTERNAL_SHARED) )
			{
				if (_resize)
				{
					// BK - at the time of resize there might be one reference held by frame buffer
					//      surface. This frame buffer will be recreated later, and release reference
					//      to existing surface. That's why here we don't care about ref count.
					m_ptr->Release();
				}
				else
				{
					DX_RELEASE(m_ptr, 0);
				}
			}
			DX_RELEASE(m_surface, 0);
			DX_RELEASE(m_staging, 0);
			m_textureFormat = TextureFormat::Unknown;
		}

		void overrideInternal(uintptr_t _ptr)
		{
			destroy();
			m_flags |= BGFX_SAMPLER_INTERNAL_SHARED;
			m_ptr = (IDirect3DBaseTexture9*)_ptr;
		}

		void updateBegin(uint8_t _side, uint8_t _mip);
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void updateEnd();
		void commit(uint8_t _stage, uint32_t _flags, const float _palette[][4]);
		void resolve(uint8_t _resolve) const;

		void preReset();
		void postReset();

		union
		{
			IDirect3DBaseTexture9*   m_ptr;
			IDirect3DTexture9*       m_texture2d;
			IDirect3DVolumeTexture9* m_texture3d;
			IDirect3DCubeTexture9*   m_textureCube;
		};

		IDirect3DSurface9* m_surface;

		union
		{
			IDirect3DBaseTexture9*   m_staging;
			IDirect3DTexture9*       m_staging2d;
			IDirect3DVolumeTexture9* m_staging3d;
			IDirect3DCubeTexture9*   m_stagingCube;
		};

		uint64_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_numMips;
		uint8_t m_type;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
	};

	struct FrameBufferD3D9
	{
		FrameBufferD3D9()
			: m_hwnd(NULL)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
			, m_numTh(0)
			, m_dsIdx(UINT8_MAX)
			, m_needResolve(false)
			, m_needPresent(false)
		{
		}

		void create(uint8_t _num, const Attachment* _attachment);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		HRESULT present();
		void resolve() const;
		void preReset();
		void postReset();
		void createNullColorRT();
		void set();

		IDirect3DSurface9* m_surface[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS-1];
		IDirect3DSwapChain9* m_swapChain;
		HWND m_hwnd;
		uint32_t m_width;
		uint32_t m_height;

		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		uint8_t m_dsIdx;
		bool m_needResolve;
		bool m_needPresent;
	};

	struct TimerQueryD3D9
	{
		TimerQueryD3D9()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		void postReset();
		void preReset();
		uint32_t begin(uint32_t _resultIdx);
		void end(uint32_t _idx);
		bool update();

		struct Query
		{
			IDirect3DQuery9* m_disjoint;
			IDirect3DQuery9* m_begin;
			IDirect3DQuery9* m_end;
			IDirect3DQuery9* m_freq;
			uint32_t         m_resultIdx;
			bool             m_ready;
		};

		struct Result
		{
			void reset()
			{
				m_begin     = 0;
				m_end       = 0;
				m_frequency = 1;
				m_pending   = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint64_t m_frequency;
			uint32_t m_pending;
		};

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];

		Query m_query[BGFX_CONFIG_MAX_VIEWS*4];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryD3D9
	{
		OcclusionQueryD3D9()
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
			IDirect3DQuery9* m_ptr;
			OcclusionQueryHandle m_handle;
		};

		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /* namespace d3d9 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D9_H_HEADER_GUARD

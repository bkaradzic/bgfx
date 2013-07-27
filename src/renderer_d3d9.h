/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __RENDERER_D3D9_H__
#define __RENDERER_D3D9_H__

#define BGFX_CONFIG_RENDERER_DIRECT3D9EX (BX_PLATFORM_WINDOWS && 0)

#if BX_PLATFORM_WINDOWS
#	if !BGFX_CONFIG_RENDERER_DIRECT3D9EX
#		define D3D_DISABLE_9EX
#	endif // !BGFX_CONFIG_RENDERER_DIRECT3D9EX
#	include <d3d9.h>

#	if BGFX_CONFIG_RENDERER_DIRECT3D9EX
typedef HRESULT (WINAPI *Direct3DCreate9ExFn)(UINT SDKVersion, IDirect3D9Ex**);
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D9EX
typedef IDirect3D9* (WINAPI *Direct3DCreate9Fn)(UINT SDKVersion);

#elif BX_PLATFORM_XBOX360
#	include <xgraphics.h>
#	define D3DUSAGE_DYNAMIC 0 // not supported on X360
#	define D3DLOCK_DISCARD 0 // not supported on X360
#	define D3DERR_DEVICEHUNG D3DERR_DEVICELOST // not supported on X360
#	define D3DERR_DEVICEREMOVED D3DERR_DEVICELOST // not supported on X360
#	define D3DMULTISAMPLE_8_SAMPLES D3DMULTISAMPLE_4_SAMPLES
#	define D3DMULTISAMPLE_16_SAMPLES D3DMULTISAMPLE_4_SAMPLES

#	define D3DFMT_DF24 D3DFMT_D24FS8

#	define _PIX_SETMARKER(_col, _name) do {} while(0)
#	define _PIX_BEGINEVENT(_col, _name) do {} while(0)
#	define _PIX_ENDEVENT() do {} while(0)
#endif // BX_PLATFORM_

#ifndef D3DSTREAMSOURCE_INDEXEDDATA
#	define D3DSTREAMSOURCE_INDEXEDDATA  (1<<30)
#endif// D3DSTREAMSOURCE_INDEXEDDATA

#ifndef D3DSTREAMSOURCE_INSTANCEDATA
#	define D3DSTREAMSOURCE_INSTANCEDATA (2<<30)
#endif // D3DSTREAMSOURCE_INSTANCEDATA

#include "renderer_d3d.h"

namespace bgfx
{
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

	struct IndexBuffer
	{
		IndexBuffer()
			: m_ptr(NULL)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			void* buffer;
			DX_CHECK(m_ptr->Lock(_offset
				, _size
				, &buffer
				, _discard || (m_dynamic && 0 == _offset && m_size == _size) ? D3DLOCK_DISCARD : 0
				) );

			memcpy(buffer, _data, _size);

			m_ptr->Unlock();
		}

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}
		}

		void preReset();
		void postReset();

		IDirect3DIndexBuffer9* m_ptr;
		uint32_t m_size;
		bool m_dynamic;
	};

	struct VertexBuffer
	{
		VertexBuffer()
			: m_ptr(NULL)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false)
		{
			void* buffer;
			DX_CHECK(m_ptr->Lock(_offset
				, _size
				, &buffer
				, _discard || (m_dynamic && 0 == _offset && m_size == _size) ? D3DLOCK_DISCARD : 0
				) );

			memcpy(buffer, _data, _size);

			m_ptr->Unlock();
		}

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}
		}

		void preReset();
		void postReset();

		IDirect3DVertexBuffer9* m_ptr;
		uint32_t m_size;
		VertexDeclHandle m_decl;
		bool m_dynamic;
	};

	struct VertexDeclaration
	{
		void create(const VertexDecl& _decl);

		void destroy()
		{
			DX_RELEASE(m_ptr, 0);
		}

		IDirect3DVertexDeclaration9* m_ptr;
		VertexDecl m_decl;
	};

	struct Shader
	{
		Shader()
			: m_ptr(NULL)
		{
		}

		void create(bool _fragment, const Memory* _mem);
		DWORD* getShaderCode(uint8_t _fragmentBit, const Memory* _mem);

		void destroy()
		{
			ConstantBuffer::destroy(m_constantBuffer);
			m_constantBuffer = NULL;
			m_numPredefined = 0;

			DX_RELEASE(m_ptr, 0);
		}

		IUnknown* m_ptr;
		ConstantBuffer* m_constantBuffer;
		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint8_t m_numPredefined;
	};

	struct Program
	{
		void create(const Shader& _vsh, const Shader& _fsh)
		{
			BX_CHECK(NULL != _vsh.m_ptr, "Vertex shader doesn't exist.");
			m_vsh = &_vsh;

			BX_CHECK(NULL != _fsh.m_ptr, "Fragment shader doesn't exist.");
			m_fsh = &_fsh;

			memcpy(&m_predefined[0], _vsh.m_predefined, _vsh.m_numPredefined*sizeof(PredefinedUniform) );
			memcpy(&m_predefined[_vsh.m_numPredefined], _fsh.m_predefined, _fsh.m_numPredefined*sizeof(PredefinedUniform) );
			m_numPredefined = _vsh.m_numPredefined + _fsh.m_numPredefined;
		}

		void destroy()
		{
			m_numPredefined = 0;
			m_vsh = NULL;
			m_fsh = NULL;
		}

		void commit()
		{
			if (NULL != m_vsh->m_constantBuffer)
			{
				m_vsh->m_constantBuffer->commit();
			}

			if (NULL != m_fsh->m_constantBuffer)
			{
				m_fsh->m_constantBuffer->commit();
			}
		}

		const Shader* m_vsh;
		const Shader* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count*2];
		uint8_t m_numPredefined;
	};

	struct Texture
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		Texture()
			: m_ptr(NULL)
		{
		}

		void createTexture(uint32_t _width, uint32_t _height, uint8_t _numMips, D3DFORMAT _fmt);
		void createVolumeTexture(uint32_t _width, uint32_t _height, uint32_t _depth, uint32_t _numMips, D3DFORMAT _fmt);
		void createCubeTexture(uint32_t _edge, uint32_t _numMips, D3DFORMAT _fmt);

		uint8_t* lock(uint8_t _side, uint8_t _lod, uint32_t& _pitch, uint32_t& _slicePitch, const Rect* _rect = NULL);
		void unlock(uint8_t _side, uint8_t _lod);
		void dirty(uint8_t _side, const Rect& _rect, uint16_t _z, uint16_t _depth);

		void create(const Memory* _mem, uint32_t _flags);

		void destroy()
		{
			DX_RELEASE(m_ptr, 0);
		}

		void updateBegin(uint8_t _side, uint8_t _mip);
		void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem);
		void updateEnd();
		void commit(uint8_t _stage, uint32_t _flags = BGFX_SAMPLER_DEFAULT_FLAGS);
	
		union
		{
			IDirect3DBaseTexture9* m_ptr;
			IDirect3DTexture9* m_texture2d;
			IDirect3DVolumeTexture9* m_texture3d;
			IDirect3DCubeTexture9* m_textureCube;
		};

		uint32_t m_flags;
		TextureFormat::Enum m_format;
		Enum m_type;
	};

	struct RenderTarget
	{
		RenderTarget()
			: m_rt(NULL)
			, m_colorTexture(NULL)
			, m_color(NULL)
			, m_depthTexture(NULL)
			, m_depth(NULL)
			, m_width(0)
			, m_height(0)
			, m_flags(0)
			, m_depthOnly(false)
		{
		}

		void create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags);
		void createTextures();
		void destroyTextures();

		void destroy()
		{
			destroyTextures();
			m_flags = 0;
		}

		void preReset()
		{
			destroyTextures();
		}

		void postReset()
		{
			createTextures();
		}

		void commit(uint8_t _stage, uint32_t _textureFlags = BGFX_SAMPLER_DEFAULT_FLAGS);
		void resolve();

		Msaa m_msaa;
		IDirect3DSurface9* m_rt;
		IDirect3DTexture9* m_colorTexture;
		IDirect3DSurface9* m_color;
		IDirect3DTexture9* m_depthTexture;
		IDirect3DSurface9* m_depth;
		uint16_t m_width;
		uint16_t m_height;
		uint32_t m_flags;
		uint32_t m_textureFlags;
		bool m_depthOnly;
	};

} // namespace bgfx

#endif // __RENDERER_D3D9_H__

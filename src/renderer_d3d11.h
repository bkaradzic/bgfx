/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __RENDERER_D3D11_H__
#define __RENDERER_D3D11_H__

#include <d3d11.h>
#include "renderer_d3d.h"

namespace bgfx
{
	template <typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _id, Ty* _item)
		{
			invalidate(_id);
			m_hashMap.insert(stl::make_pair(_id, _item) );
		}

		Ty* find(uint64_t _id)
		{
			HashMap::iterator it = m_hashMap.find(_id);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return NULL;
		}

		void invalidate(uint64_t _id)
		{
			HashMap::iterator it = m_hashMap.find(_id);
			if (it != m_hashMap.end() )
			{
				DX_RELEASE(it->second, 0);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				DX_RELEASE(it->second, 0);
			}
			m_hashMap.clear();
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty*> HashMap;
		HashMap m_hashMap;
	};

	struct IndexBuffer
	{
		IndexBuffer()
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

	struct VertexBuffer
	{
		VertexBuffer()
			: m_ptr(NULL)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle);
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
		VertexDeclHandle m_decl;
		bool m_dynamic;
	};

	struct Uniform
	{
		Uniform()
			: m_ptr(NULL)
			, m_data(NULL)
		{
		}

		void create(ConstantType::Enum _type, uint16_t _num, bool _alloc = true);
		void destroy();

		ID3D11Buffer* m_ptr;
		void* m_data;
	};

	struct Shader
	{
		Shader()
			: m_ptr(NULL)
			, m_code(NULL)
			, m_buffer(NULL)
			, m_hash(0)
		{
		}

		void create(bool _fragment, const Memory* _mem);
		DWORD* getShaderCode(uint8_t _fragmentBit, const Memory* _mem);

		void destroy()
		{
			ConstantBuffer::destroy(m_constantBuffer);
			m_constantBuffer = NULL;
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

		IUnknown* m_ptr;
		const Memory* m_code;
		ID3D11Buffer* m_buffer;
		ConstantBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];

		uint32_t m_hash;

		uint16_t m_numUniforms;
		uint8_t m_numPredefined;
	};

	struct Material
	{
		Material()
			: m_vsh(NULL)
			, m_fsh(NULL)
		{
		}

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
			: m_srv(NULL)
		{
		}

// 		void createTexture(uint32_t _width, uint32_t _height, uint8_t _numMips, D3DFORMAT _fmt);
// 		void createVolumeTexture(uint32_t _width, uint32_t _height, uint32_t _depth, uint32_t _numMips, D3DFORMAT _fmt);
// 		void createCubeTexture(uint32_t _edge, uint32_t _numMips, D3DFORMAT _fmt);

		void create(const Memory* _mem, uint32_t _flags);

		void destroy()
		{
			DX_RELEASE(m_srv, 0);
			DX_RELEASE(m_ptr, 1);
		}

		void commit(uint8_t _stage);
		void update(uint8_t _mip, const Rect& _rect, const Memory* _mem);

		ID3D11Texture2D* m_ptr;
		ID3D11ShaderResourceView* m_srv;
		ID3D11SamplerState* m_sampler;
		Enum m_type;
		bool m_srgb;
	};

	struct RenderTarget
	{
		RenderTarget()
			: 
//		m_rt(NULL)
// 			, m_colorTexture(NULL)
// 			, m_color(NULL)
// 			, m_depthTexture(NULL)
// 			, m_depth(NULL)
// 			, m_minFilter(D3DTEXF_LINEAR)
// 			, m_magFilter(D3DTEXF_LINEAR)
			 m_width(0)
			, m_height(0)
			, m_flags(0)
			, m_depthOnly(false)
		{
		}

		void create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags);
		void destroy();

 		void commit(uint8_t _stage);
// 		void resolve();

//		Msaa m_msaa;
// 		IDirect3DSurface9* m_rt;
// 		IDirect3DTexture9* m_colorTexture;
// 		IDirect3DSurface9* m_color;
// 		IDirect3DTexture9* m_depthTexture;
// 		IDirect3DSurface9* m_depth;
// 		D3DTEXTUREFILTERTYPE m_minFilter;
// 		D3DTEXTUREFILTERTYPE m_magFilter;

		ID3D11Texture2D* m_colorTexture;
		ID3D11RenderTargetView* m_rtv;
		ID3D11ShaderResourceView* m_srv;
		ID3D11SamplerState* m_sampler;
		uint16_t m_width;
		uint16_t m_height;
		uint32_t m_flags;
		bool m_depthOnly;
	};

} // namespace bgfx

#endif // __RENDERER_D3D11_H__

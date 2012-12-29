/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <string.h>
#include <bx/hash.h>

#include "vertexdecl.h"

namespace bgfx
{
	static const uint8_t s_attribTypeSizeDx9[AttribType::Count][4] =
	{
		{  4,  4,  4,  4 },
		{  4,  4,  8,  8 },
		{  4,  4,  8,  8 },
		{  4,  8, 12, 16 },
	};

	static const uint8_t s_attribTypeSizeDx11[AttribType::Count][4] =
	{
		{  1,  2,  4,  4 },
		{  2,  4,  8,  8 },
		{  2,  4,  8,  8 },
		{  4,  8, 12, 16 },
	};

	static const uint8_t s_attribTypeSizeGl[AttribType::Count][4] =
	{
		{  1,  2,  4,  4 },
		{  2,  4,  6,  8 },
		{  2,  4,  6,  8 },
		{  4,  8, 12, 16 },
	};

	static const uint8_t (*s_attribTypeSize[RendererType::Count])[AttribType::Count][4] =
	{
#if BGFX_CONFIG_RENDERER_DIRECT3D9
		&s_attribTypeSizeDx9,
#elif BGFX_CONFIG_RENDERER_DIRECT3D11
		&s_attribTypeSizeDx11,
#elif BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3
		&s_attribTypeSizeGl,
#else
		&s_attribTypeSizeDx9,
#endif // BGFX_CONFIG_RENDERER_
		&s_attribTypeSizeDx9,
		&s_attribTypeSizeDx11,
		&s_attribTypeSizeGl,
		&s_attribTypeSizeGl,
		&s_attribTypeSizeGl,
	};

	void VertexDecl::begin(RendererType::Enum _renderer)
	{
		m_hash = _renderer; // use hash to store renderer type while building VertexDecl.
		m_stride = 0;
		memset(m_attributes, 0xff, sizeof(m_attributes) );
		memset(m_offset, 0, sizeof(m_offset) );
	}

	void VertexDecl::end()
	{
		m_hash = bx::hashMurmur2A(m_attributes, sizeof(m_attributes) );
	}

	void VertexDecl::add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized)
	{
		const uint8_t encoded_norm = (_normalized&1)<<6;
		const uint8_t encoded_type = (_type&3)<<3;
		const uint8_t encoded_num = (_num-1)&3;

		m_attributes[_attrib] = encoded_norm|encoded_type|encoded_num;
		m_offset[_attrib] = m_stride;
		m_stride += (*s_attribTypeSize[m_hash])[_type][_num-1];
	}

	void VertexDecl::decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized) const
	{
		uint8_t val = m_attributes[_attrib];
		_num = (val&3)+1;
		_type = AttribType::Enum((val>>3)&3);
		_normalized = !!(val&(1<<6) );
	}

	const char* getAttribName(Attrib::Enum _attr)
	{
		static const char* attrName[Attrib::Count] = 
		{
			"Attrib::Position",
			"Attrib::Normal",
			"Attrib::Color0",
			"Attrib::Color1",
			"Attrib::Indices",
			"Attrib::Weights",
			"Attrib::TexCoord0",
			"Attrib::TexCoord1",
			"Attrib::TexCoord2",
			"Attrib::TexCoord3",
			"Attrib::TexCoord4",
			"Attrib::TexCoord5",
			"Attrib::TexCoord6",
			"Attrib::TexCoord7",
		};

		return attrName[_attr];
	}

	void dump(const VertexDecl& _decl)
	{
#if BGFX_CONFIG_DEBUG
		BX_TRACE("vertexdecl %08x (%08x), stride %d"
			, _decl.m_hash
			, hashMurmur2A(_decl.m_attributes, sizeof(_decl.m_attributes) )
			, _decl.m_stride
			);

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (0xff != _decl.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				_decl.decode(Attrib::Enum(attr), num, type, normalized);

				BX_TRACE("\tattr %d - %s, num %d, type %d, norm %d, offset %d"
					, attr
					, getAttribName(Attrib::Enum(attr) )
					, num
					, type
					, normalized
					, _decl.m_offset[attr]
				);
			}
		}
#else
		BX_UNUSED(_decl);
#endif // BGFX_CONFIG_DEBUG
	}

} // namespace bgfx

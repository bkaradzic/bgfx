/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/debug.h>
#include <bx/hash.h>
#include <bx/readerwriter.h>
#include <bx/sort.h>
#include <bx/string.h>
#include <bx/uint32_t.h>

#include "vertexlayout.h"

namespace bgfx
{
	static const uint8_t s_attribTypeSizeD3D9[AttribType::Count][4] =
	{
		{  4,  4,  4,  4 }, // Uint8
		{  4,  4,  4,  4 }, // Uint10
		{  4,  4,  8,  8 }, // Int16
		{  4,  4,  8,  8 }, // Half
		{  4,  8, 12, 16 }, // Float
	};

	static const uint8_t s_attribTypeSizeD3D1x[AttribType::Count][4] =
	{
		{  1,  2,  4,  4 }, // Uint8
		{  4,  4,  4,  4 }, // Uint10
		{  2,  4,  8,  8 }, // Int16
		{  2,  4,  8,  8 }, // Half
		{  4,  8, 12, 16 }, // Float
	};

	static const uint8_t s_attribTypeSizeGl[AttribType::Count][4] =
	{
		{  1,  2,  4,  4 }, // Uint8
		{  4,  4,  4,  4 }, // Uint10
		{  2,  4,  6,  8 }, // Int16
		{  2,  4,  6,  8 }, // Half
		{  4,  8, 12, 16 }, // Float
	};

	static const uint8_t (*s_attribTypeSize[])[AttribType::Count][4] =
	{
		&s_attribTypeSizeD3D9,  // Noop
		&s_attribTypeSizeD3D9,  // Direct3D9
		&s_attribTypeSizeD3D1x, // Direct3D11
		&s_attribTypeSizeD3D1x, // Direct3D12
		&s_attribTypeSizeD3D1x, // Gnm
		&s_attribTypeSizeGl,    // Metal
		&s_attribTypeSizeGl,    // Nvn
		&s_attribTypeSizeGl,    // OpenGLES
		&s_attribTypeSizeGl,    // OpenGL
		&s_attribTypeSizeD3D1x, // Vulkan
		&s_attribTypeSizeD3D1x, // WebGPU
		&s_attribTypeSizeD3D9,  // Count
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_attribTypeSize) == RendererType::Count+1);

	void initAttribTypeSizeTable(RendererType::Enum _type)
	{
		s_attribTypeSize[0]                   = s_attribTypeSize[_type];
		s_attribTypeSize[RendererType::Count] = s_attribTypeSize[_type];
	}

	VertexLayout::VertexLayout()
		: m_stride(0)
	{
		// BK - struct need to have ctor to qualify as non-POD data.
		// Need this to catch programming errors when serializing struct.
	}

	VertexLayout& VertexLayout::begin(RendererType::Enum _renderer)
	{
		m_hash = _renderer; // use hash to store renderer type while building VertexLayout.
		m_stride = 0;
		bx::memSet(m_attributes, 0xff, sizeof(m_attributes) );
		bx::memSet(m_offset, 0, sizeof(m_offset) );

		return *this;
	}

	void VertexLayout::end()
	{
		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_attributes, sizeof(m_attributes) );
		murmur.add(m_offset, sizeof(m_offset) );
		murmur.add(m_stride);
		m_hash = murmur.end();
	}

	VertexLayout& VertexLayout::add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized, bool _asInt)
	{
		const uint16_t encodedNorm = (_normalized&1)<<7;
		const uint16_t encodedType = (_type&7)<<3;
		const uint16_t encodedNum  = (_num-1)&3;
		const uint16_t encodeAsInt = (_asInt&(!!"\x1\x1\x1\x0\x0"[_type]) )<<8;
		m_attributes[_attrib] = encodedNorm|encodedType|encodedNum|encodeAsInt;

		m_offset[_attrib] = m_stride;
		m_stride += (*s_attribTypeSize[m_hash])[_type][_num-1];

		return *this;
	}

	VertexLayout& VertexLayout::skip(uint8_t _num)
	{
		m_stride += _num;

		return *this;
	}

	void VertexLayout::decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized, bool& _asInt) const
	{
		uint16_t val = m_attributes[_attrib];
		_num        = (val&3)+1;
		_type       = AttribType::Enum( (val>>3)&7);
		_normalized = !!(val&(1<<7) );
		_asInt      = !!(val&(1<<8) );
	}

	static const char* s_attrName[] =
	{
		"P",  "Attrib::Position",
		"N",  "Attrib::Normal",
		"T",  "Attrib::Tangent",
		"B",  "Attrib::Bitangent",
		"C0", "Attrib::Color0",
		"C1", "Attrib::Color1",
		"C2", "Attrib::Color2",
		"C3", "Attrib::Color3",
		"I",  "Attrib::Indices",
		"W",  "Attrib::Weights",
		"T0", "Attrib::TexCoord0",
		"T1", "Attrib::TexCoord1",
		"T2", "Attrib::TexCoord2",
		"T3", "Attrib::TexCoord3",
		"T4", "Attrib::TexCoord4",
		"T5", "Attrib::TexCoord5",
		"T6", "Attrib::TexCoord6",
		"T7", "Attrib::TexCoord7",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_attrName) == Attrib::Count*2);

	const char* getAttribNameShort(Attrib::Enum _attr)
	{
		return s_attrName[_attr*2+0];
	}

	const char* getAttribName(Attrib::Enum _attr)
	{
		return s_attrName[_attr*2+1];
	}

	struct AttribToId
	{
		Attrib::Enum attr;
		uint16_t id;
	};

	static AttribToId s_attribToId[] =
	{
		// NOTICE:
		// Attrib must be in order how it appears in Attrib::Enum! id is
		// unique and should not be changed if new Attribs are added.
		{ Attrib::Position,  0x0001 },
		{ Attrib::Normal,    0x0002 },
		{ Attrib::Tangent,   0x0003 },
		{ Attrib::Bitangent, 0x0004 },
		{ Attrib::Color0,    0x0005 },
		{ Attrib::Color1,    0x0006 },
		{ Attrib::Color2,    0x0018 },
		{ Attrib::Color3,    0x0019 },
		{ Attrib::Indices,   0x000e },
		{ Attrib::Weight,    0x000f },
		{ Attrib::TexCoord0, 0x0010 },
		{ Attrib::TexCoord1, 0x0011 },
		{ Attrib::TexCoord2, 0x0012 },
		{ Attrib::TexCoord3, 0x0013 },
		{ Attrib::TexCoord4, 0x0014 },
		{ Attrib::TexCoord5, 0x0015 },
		{ Attrib::TexCoord6, 0x0016 },
		{ Attrib::TexCoord7, 0x0017 },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_attribToId) == Attrib::Count);

	Attrib::Enum idToAttrib(uint16_t id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_attribToId); ++ii)
		{
			if (s_attribToId[ii].id == id)
			{
				return s_attribToId[ii].attr;
			}
		}

		return Attrib::Count;
	}

	uint16_t attribToId(Attrib::Enum _attr)
	{
		return s_attribToId[_attr].id;
	}

	struct AttribTypeToId
	{
		AttribType::Enum type;
		uint16_t id;
	};

	static AttribTypeToId s_attribTypeToId[] =
	{
		// NOTICE:
		// AttribType must be in order how it appears in AttribType::Enum!
		// id is unique and should not be changed if new AttribTypes are
		// added.
		{ AttribType::Uint8,  0x0001 },
		{ AttribType::Uint10, 0x0005 },
		{ AttribType::Int16,  0x0002 },
		{ AttribType::Half,   0x0003 },
		{ AttribType::Float,  0x0004 },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_attribTypeToId) == AttribType::Count);

	AttribType::Enum idToAttribType(uint16_t id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_attribTypeToId); ++ii)
		{
			if (s_attribTypeToId[ii].id == id)
			{
				return s_attribTypeToId[ii].type;
			}
		}

		return AttribType::Count;
	}

	uint16_t attribTypeToId(AttribType::Enum _attr)
	{
		return s_attribTypeToId[_attr].id;
	}

	int32_t write(bx::WriterI* _writer, const VertexLayout& _layout, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		int32_t total = 0;
		uint8_t numAttrs = 0;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			numAttrs += UINT16_MAX == _layout.m_attributes[attr] ? 0 : 1;
		}

		total += bx::write(_writer, numAttrs, _err);
		total += bx::write(_writer, _layout.m_stride, _err);

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _layout.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				bool asInt;
				_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);
				total += bx::write(_writer, _layout.m_offset[attr], _err);
				total += bx::write(_writer, s_attribToId[attr].id, _err);
				total += bx::write(_writer, num, _err);
				total += bx::write(_writer, s_attribTypeToId[type].id, _err);
				total += bx::write(_writer, normalized, _err);
				total += bx::write(_writer, asInt, _err);
			}
		}

		return total;
	}

	int32_t read(bx::ReaderI* _reader, VertexLayout& _layout, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		int32_t total = 0;

		uint8_t numAttrs;
		total += bx::read(_reader, numAttrs, _err);

		uint16_t stride;
		total += bx::read(_reader, stride, _err);

		if (!_err->isOk() )
		{
			return total;
		}

		_layout.begin();

		for (uint32_t ii = 0; ii < numAttrs; ++ii)
		{
			uint16_t offset;
			total += bx::read(_reader, offset, _err);

			uint16_t attribId = 0;
			total += bx::read(_reader, attribId, _err);

			uint8_t num;
			total += bx::read(_reader, num, _err);

			uint16_t attribTypeId;
			total += bx::read(_reader, attribTypeId, _err);

			bool normalized;
			total += bx::read(_reader, normalized, _err);

			bool asInt;
			total += bx::read(_reader, asInt, _err);

			if (!_err->isOk() )
			{
				return total;
			}

			Attrib::Enum     attr = idToAttrib(attribId);
			AttribType::Enum type = idToAttribType(attribTypeId);
			if (Attrib::Count     != attr
			&&  AttribType::Count != type)
			{
				_layout.add(attr, num, type, normalized, asInt);
				_layout.m_offset[attr] = offset;
			}
		}

		_layout.end();
		_layout.m_stride = stride;

		return total;
	}

	void vertexPack(const float _input[4], bool _inputNormalized, Attrib::Enum _attr, const VertexLayout& _layout, void* _data, uint32_t _index)
	{
		if (!_layout.has(_attr) )
		{
			return;
		}

		uint32_t stride = _layout.getStride();
		uint8_t* data = (uint8_t*)_data + _index*stride + _layout.getOffset(_attr);

		uint8_t num;
		AttribType::Enum type;
		bool normalized;
		bool asInt;
		_layout.decode(_attr, num, type, normalized, asInt);

		switch (type)
		{
		default:
		case AttribType::Uint8:
			{
				uint8_t* packed = (uint8_t*)data;
				if (_inputNormalized)
				{
					if (asInt)
					{
						switch (num)
						{
						default: *packed++ = uint8_t(*_input++ * 127.0f + 128.0f); BX_FALLTHROUGH;
						case 3:  *packed++ = uint8_t(*_input++ * 127.0f + 128.0f); BX_FALLTHROUGH;
						case 2:  *packed++ = uint8_t(*_input++ * 127.0f + 128.0f); BX_FALLTHROUGH;
						case 1:  *packed++ = uint8_t(*_input++ * 127.0f + 128.0f);
						}
					}
					else
					{
						switch (num)
						{
						default: *packed++ = uint8_t(*_input++ * 255.0f); BX_FALLTHROUGH;
						case 3:  *packed++ = uint8_t(*_input++ * 255.0f); BX_FALLTHROUGH;
						case 2:  *packed++ = uint8_t(*_input++ * 255.0f); BX_FALLTHROUGH;
						case 1:  *packed++ = uint8_t(*_input++ * 255.0f);
						}
					}
				}
				else
				{
					switch (num)
					{
					default: *packed++ = uint8_t(*_input++); BX_FALLTHROUGH;
					case 3:  *packed++ = uint8_t(*_input++); BX_FALLTHROUGH;
					case 2:  *packed++ = uint8_t(*_input++); BX_FALLTHROUGH;
					case 1:  *packed++ = uint8_t(*_input++);
					}
				}
			}
			break;

		case AttribType::Uint10:
			{
				uint32_t packed = 0;
				if (_inputNormalized)
				{
					if (asInt)
					{
						switch (num)
						{
						default: BX_FALLTHROUGH;
						case 3:                packed |= uint32_t(*_input++ * 511.0f + 512.0f); BX_FALLTHROUGH;
						case 2: packed <<= 10; packed |= uint32_t(*_input++ * 511.0f + 512.0f); BX_FALLTHROUGH;
						case 1: packed <<= 10; packed |= uint32_t(*_input++ * 511.0f + 512.0f);
						}
					}
					else
					{
						switch (num)
						{
						default: BX_FALLTHROUGH;
						case 3:                packed |= uint32_t(*_input++ * 1023.0f); BX_FALLTHROUGH;
						case 2: packed <<= 10; packed |= uint32_t(*_input++ * 1023.0f); BX_FALLTHROUGH;
						case 1: packed <<= 10; packed |= uint32_t(*_input++ * 1023.0f);
						}
					}
				}
				else
				{
					switch (num)
					{
					default: BX_FALLTHROUGH;
					case 3:                packed |= uint32_t(*_input++); BX_FALLTHROUGH;
					case 2: packed <<= 10; packed |= uint32_t(*_input++); BX_FALLTHROUGH;
					case 1: packed <<= 10; packed |= uint32_t(*_input++);
					}
				}
				*(uint32_t*)data = packed;
			}
			break;

		case AttribType::Int16:
			{
				int16_t* packed = (int16_t*)data;
				if (_inputNormalized)
				{
					if (asInt)
					{
						switch (num)
						{
						default: *packed++ = int16_t(*_input++ * 32767.0f); BX_FALLTHROUGH;
						case 3:  *packed++ = int16_t(*_input++ * 32767.0f); BX_FALLTHROUGH;
						case 2:  *packed++ = int16_t(*_input++ * 32767.0f); BX_FALLTHROUGH;
						case 1:  *packed++ = int16_t(*_input++ * 32767.0f);
						}
					}
					else
					{
						switch (num)
						{
						default: *packed++ = int16_t(*_input++ * 65535.0f - 32768.0f); BX_FALLTHROUGH;
						case 3:  *packed++ = int16_t(*_input++ * 65535.0f - 32768.0f); BX_FALLTHROUGH;
						case 2:  *packed++ = int16_t(*_input++ * 65535.0f - 32768.0f); BX_FALLTHROUGH;
						case 1:  *packed++ = int16_t(*_input++ * 65535.0f - 32768.0f);
						}
					}
				}
				else
				{
					switch (num)
					{
					default: *packed++ = int16_t(*_input++); BX_FALLTHROUGH;
					case 3:  *packed++ = int16_t(*_input++); BX_FALLTHROUGH;
					case 2:  *packed++ = int16_t(*_input++); BX_FALLTHROUGH;
					case 1:  *packed++ = int16_t(*_input++);
					}
				}
			}
			break;

		case AttribType::Half:
			{
				uint16_t* packed = (uint16_t*)data;
				switch (num)
				{
				default: *packed++ = bx::halfFromFloat(*_input++); BX_FALLTHROUGH;
				case 3:  *packed++ = bx::halfFromFloat(*_input++); BX_FALLTHROUGH;
				case 2:  *packed++ = bx::halfFromFloat(*_input++); BX_FALLTHROUGH;
				case 1:  *packed++ = bx::halfFromFloat(*_input++);
				}
			}
			break;

		case AttribType::Float:
			bx::memCopy(data, _input, num*sizeof(float) );
			break;
		}
	}

	void vertexUnpack(float _output[4], Attrib::Enum _attr, const VertexLayout& _layout, const void* _data, uint32_t _index)
	{
		if (!_layout.has(_attr) )
		{
			bx::memSet(_output, 0, 4*sizeof(float) );
			return;
		}

		uint32_t stride = _layout.getStride();
		uint8_t* data = (uint8_t*)_data + _index*stride + _layout.getOffset(_attr);

		uint8_t num;
		AttribType::Enum type;
		bool normalized;
		bool asInt;
		_layout.decode(_attr, num, type, normalized, asInt);

		switch (type)
		{
		default:
		case AttribType::Uint8:
			{
				uint8_t* packed = (uint8_t*)data;
				if (asInt)
				{
					switch (num)
					{
					default: *_output++ = (float(*packed++) - 128.0f)*1.0f/127.0f; BX_FALLTHROUGH;
					case 3:  *_output++ = (float(*packed++) - 128.0f)*1.0f/127.0f; BX_FALLTHROUGH;
					case 2:  *_output++ = (float(*packed++) - 128.0f)*1.0f/127.0f; BX_FALLTHROUGH;
					case 1:  *_output++ = (float(*packed++) - 128.0f)*1.0f/127.0f;
					}
				}
				else
				{
					switch (num)
					{
					default: *_output++ = float(*packed++)*1.0f/255.0f; BX_FALLTHROUGH;
					case 3:  *_output++ = float(*packed++)*1.0f/255.0f; BX_FALLTHROUGH;
					case 2:  *_output++ = float(*packed++)*1.0f/255.0f; BX_FALLTHROUGH;
					case 1:  *_output++ = float(*packed++)*1.0f/255.0f;
					}
				}
			}
			break;

		case AttribType::Uint10:
			{
				uint32_t packed = *(uint32_t*)data;
				if (asInt)
				{
					switch (num)
					{
					default: BX_FALLTHROUGH;
					case 3: *_output++ = (float(packed & 0x3ff) - 512.0f)*1.0f/511.0f; packed >>= 10; BX_FALLTHROUGH;
					case 2: *_output++ = (float(packed & 0x3ff) - 512.0f)*1.0f/511.0f; packed >>= 10; BX_FALLTHROUGH;
					case 1: *_output++ = (float(packed & 0x3ff) - 512.0f)*1.0f/511.0f;
					}
				}
				else
				{
					switch (num)
					{
					default: BX_FALLTHROUGH;
					case 3: *_output++ = float(packed & 0x3ff)*1.0f/1023.0f; packed >>= 10; BX_FALLTHROUGH;
					case 2: *_output++ = float(packed & 0x3ff)*1.0f/1023.0f; packed >>= 10; BX_FALLTHROUGH;
					case 1: *_output++ = float(packed & 0x3ff)*1.0f/1023.0f;
					}
				}
			}
			break;

		case AttribType::Int16:
			{
				int16_t* packed = (int16_t*)data;
				if (asInt)
				{
					switch (num)
					{
					default: *_output++ = float(*packed++)*1.0f/32767.0f; BX_FALLTHROUGH;
					case 3:  *_output++ = float(*packed++)*1.0f/32767.0f; BX_FALLTHROUGH;
					case 2:  *_output++ = float(*packed++)*1.0f/32767.0f; BX_FALLTHROUGH;
					case 1:  *_output++ = float(*packed++)*1.0f/32767.0f;
					}
				}
				else
				{
					switch (num)
					{
					default: *_output++ = (float(*packed++) + 32768.0f)*1.0f/65535.0f; BX_FALLTHROUGH;
					case 3:  *_output++ = (float(*packed++) + 32768.0f)*1.0f/65535.0f; BX_FALLTHROUGH;
					case 2:  *_output++ = (float(*packed++) + 32768.0f)*1.0f/65535.0f; BX_FALLTHROUGH;
					case 1:  *_output++ = (float(*packed++) + 32768.0f)*1.0f/65535.0f;
					}
				}
			}
			break;

		case AttribType::Half:
			{
				uint16_t* packed = (uint16_t*)data;
				switch (num)
				{
				default: *_output++ = bx::halfToFloat(*packed++); BX_FALLTHROUGH;
				case 3:  *_output++ = bx::halfToFloat(*packed++); BX_FALLTHROUGH;
				case 2:  *_output++ = bx::halfToFloat(*packed++); BX_FALLTHROUGH;
				case 1:  *_output++ = bx::halfToFloat(*packed++);
				}
			}
			break;

		case AttribType::Float:
			bx::memCopy(_output, data, num*sizeof(float) );
			_output += num;
			break;
		}

		switch (num)
		{
		case 1: *_output++ = 0.0f; BX_FALLTHROUGH;
		case 2: *_output++ = 0.0f; BX_FALLTHROUGH;
		case 3: *_output++ = 0.0f; BX_FALLTHROUGH;
		default: break;
		}
	}

	void vertexConvert(const VertexLayout& _destLayout, void* _destData, const VertexLayout& _srcLayout, const void* _srcData, uint32_t _num)
	{
		if (_destLayout.m_hash == _srcLayout.m_hash)
		{
			bx::memCopy(_destData, _srcData, _srcLayout.getSize(_num) );
			return;
		}

		struct ConvertOp
		{
			enum Enum
			{
				Set,
				Copy,
				Convert,
			};

			Attrib::Enum attr;
			Enum op;
			uint32_t src;
			uint32_t dest;
			uint32_t size;
		};

		ConvertOp convertOp[Attrib::Count];
		uint32_t numOps = 0;

		for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
		{
			Attrib::Enum attr = (Attrib::Enum)ii;

			if (_destLayout.has(attr) )
			{
				ConvertOp& cop = convertOp[numOps];
				cop.attr = attr;
				cop.dest = _destLayout.getOffset(attr);

				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				bool asInt;
				_destLayout.decode(attr, num, type, normalized, asInt);
				cop.size = (*s_attribTypeSize[0])[type][num-1];

				if (_srcLayout.has(attr) )
				{
					cop.src = _srcLayout.getOffset(attr);
					cop.op = _destLayout.m_attributes[attr] == _srcLayout.m_attributes[attr] ? ConvertOp::Copy : ConvertOp::Convert;
				}
				else
				{
					cop.op = ConvertOp::Set;
				}

				++numOps;
			}
		}

		if (0 < numOps)
		{
			const uint8_t* src = (const uint8_t*)_srcData;
			uint32_t srcStride = _srcLayout.getStride();

			uint8_t* dest = (uint8_t*)_destData;
			uint32_t destStride = _destLayout.getStride();

			float unpacked[4];

			for (uint32_t ii = 0; ii < _num; ++ii)
			{
				for (uint32_t jj = 0; jj < numOps; ++jj)
				{
					const ConvertOp& cop = convertOp[jj];

					switch (cop.op)
					{
					case ConvertOp::Set:
						bx::memSet(dest + cop.dest, 0, cop.size);
						break;

					case ConvertOp::Copy:
						bx::memCopy(dest + cop.dest, src + cop.src, cop.size);
						break;

					case ConvertOp::Convert:
						vertexUnpack(unpacked, cop.attr, _srcLayout, src);
						vertexPack(unpacked, true, cop.attr, _destLayout, dest);
						break;
					}
				}

				src += srcStride;
				dest += destStride;
			}
		}
	}

	inline float sqLength(const float _a[3], const float _b[3])
	{
		const float xx = _a[0] - _b[0];
		const float yy = _a[1] - _b[1];
		const float zz = _a[2] - _b[2];
		return xx*xx + yy*yy + zz*zz;
	}

	template<typename IndexT>
	static IndexT weldVerticesRef(IndexT* _output, const VertexLayout& _layout, const void* _data, uint32_t _num, float _epsilon)
	{
		// Brute force slow vertex welding...
		const float epsilonSq = _epsilon*_epsilon;

		uint32_t numVertices = 0;
		bx::memSet(_output, 0xff, _num*sizeof(IndexT) );

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			if (IndexT(-1) != _output[ii])
			{
				continue;
			}

			_output[ii] = (IndexT)ii;
			++numVertices;

			float pos[4];
			vertexUnpack(pos, Attrib::Position, _layout, _data, ii);

			for (uint32_t jj = 0; jj < _num; ++jj)
			{
				if (IndexT(-1) != _output[jj])
				{
					continue;
				}

				float test[4];
				vertexUnpack(test, Attrib::Position, _layout, _data, jj);

				if (sqLength(test, pos) < epsilonSq)
				{
					_output[jj] = IndexT(ii);
				}
			}
		}

		return IndexT(numVertices);
	}

	template<typename IndexT>
	static IndexT weldVertices(IndexT* _output, const VertexLayout& _layout, const void* _data, uint32_t _num, float _epsilon, bx::AllocatorI* _allocator)
	{
		const uint32_t hashSize = bx::uint32_nextpow2(_num);
		const uint32_t hashMask = hashSize-1;
		const float epsilonSq = _epsilon*_epsilon;

		uint32_t numVertices = 0;

		const uint32_t size = sizeof(IndexT)*(hashSize + _num);
		IndexT* hashTable = (IndexT*)BX_ALLOC(_allocator, size);
		bx::memSet(hashTable, 0xff, size);

		IndexT* next = hashTable + hashSize;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			float pos[4];
			vertexUnpack(pos, Attrib::Position, _layout, _data, ii);
			uint32_t hashValue = bx::hash<bx::HashMurmur2A>(pos, 3*sizeof(float) ) & hashMask;

			IndexT offset = hashTable[hashValue];
			for (; IndexT(-1) != offset; offset = next[offset])
			{
				float test[4];
				vertexUnpack(test, Attrib::Position, _layout, _data, _output[offset]);

				if (sqLength(test, pos) < epsilonSq)
				{
					_output[ii] = _output[offset];
					break;
				}
			}

			if (IndexT(-1) == offset)
			{
				_output[ii] = IndexT(ii);
				next[ii] = hashTable[hashValue];
				hashTable[hashValue] = IndexT(ii);
				numVertices++;
			}
		}

		BX_FREE(_allocator, hashTable);

		return IndexT(numVertices);
	}

	uint32_t weldVertices(void* _output, const VertexLayout& _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon, bx::AllocatorI* _allocator)
	{
		if (_index32)
		{
			return weldVertices( (uint32_t*)_output, _layout, _data, _num, _epsilon, _allocator);
		}

		return weldVertices( (uint16_t*)_output, _layout, _data, _num, _epsilon, _allocator);
	}

} // namespace bgfx

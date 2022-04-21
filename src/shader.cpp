/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"
#include "shader_dxbc.h"
#include "shader_dx9bc.h"
#include "shader_spirv.h"

namespace bgfx
{
	struct DescriptorTypeToId
	{
		DescriptorType::Enum type;
		uint16_t id;
	};

	static DescriptorTypeToId s_descriptorTypeToId[] =
	{
		// NOTICE:
		// DescriptorType must be in order how it appears in DescriptorType::Enum! id is
		// unique and should not be changed if new DescriptorTypes are added.
		{ DescriptorType::StorageBuffer, 0x0007 },
		{ DescriptorType::StorageImage,  0x0003 },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_descriptorTypeToId) == DescriptorType::Count);

	DescriptorType::Enum idToDescriptorType(uint16_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_descriptorTypeToId); ++ii)
		{
			if (s_descriptorTypeToId[ii].id == _id)
			{
				return s_descriptorTypeToId[ii].type;
			}
		}

		return DescriptorType::Count;
	}

	uint16_t descriptorTypeToId(DescriptorType::Enum _type)
	{
		return s_descriptorTypeToId[_type].id;
	}

	struct TextureComponentTypeToId
	{
		TextureComponentType::Enum type;
		uint8_t id;
	};

	static TextureComponentTypeToId s_textureComponentTypeToId[] =
	{
		// see comment in s_descriptorTypeToId
		{ TextureComponentType::Float,             0x00 },
		{ TextureComponentType::Int,               0x01 },
		{ TextureComponentType::Uint,              0x02 },
		{ TextureComponentType::Depth,             0x03 },
		{ TextureComponentType::UnfilterableFloat, 0x04 },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_textureComponentTypeToId) == TextureComponentType::Count);

	TextureComponentType::Enum idToTextureComponentType(uint8_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_textureComponentTypeToId); ++ii)
		{
			if (s_textureComponentTypeToId[ii].id == _id)
			{
				return s_textureComponentTypeToId[ii].type;
			}
		}

		return TextureComponentType::Count;
	}

	uint8_t textureComponentTypeToId(TextureComponentType::Enum _type)
	{
		return s_textureComponentTypeToId[_type].id;
	}

	struct TextureDimensionToId
	{
		TextureDimension::Enum dimension;
		uint8_t id;
	};

	static TextureDimensionToId s_textureDimensionToId[] =
	{
		// see comment in s_descriptorTypeToId
		{ TextureDimension::Dimension1D,        0x01 },
		{ TextureDimension::Dimension2D,        0x02 },
		{ TextureDimension::Dimension2DArray,   0x03 },
		{ TextureDimension::DimensionCube,      0x04 },
		{ TextureDimension::DimensionCubeArray, 0x05 },
		{ TextureDimension::Dimension3D,        0x06 },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_textureDimensionToId) == TextureDimension::Count);

	TextureDimension::Enum idToTextureDimension(uint8_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_textureDimensionToId); ++ii)
		{
			if (s_textureDimensionToId[ii].id == _id)
			{
				return s_textureDimensionToId[ii].dimension;
			}
		}

		return TextureDimension::Count;
	}

	uint8_t textureDimensionToId(TextureDimension::Enum _dim)
	{
		return s_textureDimensionToId[_dim].id;
	}

	static bool printAsm(uint32_t _offset, const DxbcInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);

		bx::Error err;
		bx::write(writer, temp, (int32_t)bx::strLen(temp), &err);
		bx::write(writer, '\n', &err);
		return true;
	}

	static bool printAsm(uint32_t _offset, const Dx9bcInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);

		bx::Error err;
		bx::write(writer, temp, (int32_t)bx::strLen(temp), &err);
		bx::write(writer, '\n', &err);
		return true;
	}

	static bool printAsm(uint32_t _offset, const SpvInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);

		bx::Error err;
		bx::write(writer, temp, (int32_t)bx::strLen(temp), &err);
		bx::write(writer, '\n', &err);
		return true;
	}

	void disassembleByteCode(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err)
	{
		uint32_t magic;
		bx::peek(_reader, magic, _err);

		if (magic == SPV_CHUNK_HEADER)
		{
			SpirV spirv;
			read(_reader, spirv, _err);
			parse(spirv.shader, printAsm, _writer, _err);
		}
		else if (magic == DXBC_CHUNK_HEADER)
		{
			DxbcContext dxbc;
			read(_reader, dxbc, _err);
			parse(dxbc.shader, printAsm, _writer, _err);
		}
		else
		{
			Dx9bc dx9bc;
			read(_reader, dx9bc, _err);
			parse(dx9bc.shader, printAsm, _writer, _err);
		}
	}

	void disassemble(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		uint32_t magic;
		bx::peek(_reader, magic, _err);

		if (isShaderBin(magic) )
		{
			bx::read(_reader, magic, _err);

			uint32_t hashIn;
			bx::read(_reader, hashIn, _err);

			uint32_t hashOut;

			if (isShaderVerLess(magic, 6) )
			{
				hashOut = hashIn;
			}
			else
			{
				bx::read(_reader, hashOut, _err);
			}

			uint16_t count;
			bx::read(_reader, count, _err);

			if (!_err->isOk() ) { return; }

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(_reader, nameSize, _err);

				if (!_err->isOk() ) { return; }

				char name[256];
				bx::read(_reader, &name, nameSize, _err);
				name[nameSize] = '\0';

				uint8_t type;
				bx::read(_reader, type, _err);

				uint8_t num;
				bx::read(_reader, num, _err);

				uint16_t regIndex;
				bx::read(_reader, regIndex, _err);

				uint16_t regCount;
				bx::read(_reader, regCount, _err);

				if (!isShaderVerLess(magic, 8) )
				{
					uint16_t texInfo;
					bx::read(_reader, texInfo, _err);
				}

				if (!isShaderVerLess(magic, 10) )
				{
					uint16_t texFormat = 0;
					bx::read(_reader, texFormat, _err);
				}
			}

			uint32_t shaderSize;
			bx::read(_reader, shaderSize, _err);

			if (!_err->isOk() ) { return; }

			uint8_t* shaderCode = (uint8_t*)BX_ALLOC(g_allocator, shaderSize);
			bx::read(_reader, shaderCode, shaderSize, _err);

			bx::MemoryReader reader(shaderCode, shaderSize);
			disassembleByteCode(_writer, &reader, _err);

			bx::write(_writer, '\0', _err);

			BX_FREE(g_allocator, shaderCode);
		}
		else
		{
			disassembleByteCode(_writer, _reader, _err);
		}
	}

	void disassemble(bx::WriterI* _writer, const void* _data, uint32_t _size, bx::Error* _err)
	{
		bx::MemoryReader reader(_data, _size);
		disassemble(_writer, &reader, _err);
	}

} // namespace bgfx

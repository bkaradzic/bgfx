/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "shader_dxbc.h"
#include "shader_dx9bc.h"
#include "shader_spirv.h"

namespace bgfx
{
	static bool printAsm(uint32_t _offset, const DxbcInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);
		bx::write(writer, temp, (int32_t)bx::strLen(temp) );
		bx::write(writer, '\n');
		return true;
	}

	static bool printAsm(uint32_t _offset, const Dx9bcInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);
		bx::write(writer, temp, (int32_t)bx::strLen(temp) );
		bx::write(writer, '\n');
		return true;
	}

	static bool printAsm(uint32_t _offset, const SpvInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		bx::WriterI* writer = reinterpret_cast<bx::WriterI*>(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);
		bx::write(writer, temp, (int32_t)bx::strLen(temp) );
		bx::write(writer, '\n');
		return true;
	}

	void disassembleByteCode(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err)
	{
		uint32_t magic;
		bx::peek(_reader, magic);

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
		bx::peek(_reader, magic);

		if (isShaderBin(magic) )
		{
			bx::read(_reader, magic);

			uint32_t hashIn;
			bx::read(_reader, hashIn);

			uint32_t hashOut;

			if (isShaderVerLess(magic, 6) )
			{
				hashOut = hashIn;
			}
			else
			{
				bx::read(_reader, hashOut);
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

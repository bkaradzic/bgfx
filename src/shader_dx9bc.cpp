/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "shader_dx9bc.h"

BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-parameter");
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunneeded-internal-declaration");

namespace bgfx
{
	struct Dx9bcOpcodeInfo
	{
		uint8_t numOperands;
		uint8_t numValues;
	};

	static const Dx9bcOpcodeInfo s_dx9bcOpcodeInfo[] =
	{
		{ 0, 0 }, // NOP
		{ 2, 0 }, // MOV
		{ 3, 0 }, // ADD
		{ 1, 0 }, // SUB
		{ 4, 0 }, // MAD
		{ 3, 0 }, // MUL
		{ 2, 0 }, // RCP
		{ 2, 0 }, // RSQ
		{ 3, 0 }, // DP3
		{ 3, 0 }, // DP4
		{ 3, 0 }, // MIN
		{ 3, 0 }, // MAX
		{ 3, 0 }, // SLT
		{ 3, 0 }, // SGE
		{ 2, 0 }, // EXP
		{ 2, 0 }, // LOG
		{ 1, 0 }, // LIT
		{ 1, 0 }, // DST
		{ 4, 0 }, // LRP
		{ 2, 0 }, // FRC
		{ 1, 0 }, // M4X4
		{ 1, 0 }, // M4X3
		{ 1, 0 }, // M3X4
		{ 1, 0 }, // M3X3
		{ 1, 0 }, // M3X2
		{ 0, 0 }, // CALL
		{ 0, 0 }, // CALLNZ
		{ 0, 0 }, // LOOP
		{ 0, 0 }, // RET
		{ 0, 0 }, // ENDLOOP
		{ 0, 0 }, // LABEL
		{ 1, 1 }, // DCL
		{ 3, 0 }, // POW
		{ 1, 0 }, // CRS
		{ 1, 0 }, // SGN
		{ 1, 0 }, // ABS
		{ 2, 0 }, // NRM
		{ 4, 0 }, // SINCOS
		{ 1, 0 }, // REP
		{ 0, 0 }, // ENDREP
		{ 1, 0 }, // IF
		{ 2, 0 }, // IFC
		{ 0, 0 }, // ELSE
		{ 0, 0 }, // ENDIF
		{ 0, 0 }, // BREAK
		{ 2, 0 }, // BREAKC
		{ 2, 0 }, // MOVA
		{ 1, 4 }, // DEFB
		{ 1, 4 }, // DEFI
		{ 0, 0 }, // 0
		{ 0, 0 }, // 1
		{ 0, 0 }, // 2
		{ 0, 0 }, // 3
		{ 0, 0 }, // 4
		{ 0, 0 }, // 5
		{ 0, 0 }, // 6
		{ 0, 0 }, // 7
		{ 0, 0 }, // 8
		{ 0, 0 }, // 9
		{ 0, 0 }, // 10
		{ 0, 0 }, // 11
		{ 0, 0 }, // 12
		{ 0, 0 }, // 13
		{ 0, 0 }, // 14
		{ 1, 0 }, // TEXCOORD
		{ 1, 0 }, // TEXKILL
		{ 3, 0 }, // TEX
		{ 1, 0 }, // TEXBEM
		{ 1, 0 }, // TEXBEM1
		{ 1, 0 }, // TEXREG2AR
		{ 1, 0 }, // TEXREG2GB
		{ 1, 0 }, // TEXM3X2PAD
		{ 1, 0 }, // TEXM3X2TEX
		{ 1, 0 }, // TEXM3X3PAD
		{ 1, 0 }, // TEXM3X3TEX
		{ 1, 0 }, // TEXM3X3DIFF
		{ 1, 0 }, // TEXM3X3SPEC
		{ 1, 0 }, // TEXM3X3VSPEC
		{ 2, 0 }, // EXPP
		{ 2, 0 }, // LOGP
		{ 4, 0 }, // CND
		{ 1, 4 }, // DEF
		{ 1, 0 }, // TEXREG2RGB
		{ 1, 0 }, // TEXDP3TEX
		{ 1, 0 }, // TEXM3X2DEPTH
		{ 1, 0 }, // TEXDP3
		{ 1, 0 }, // TEXM3X3
		{ 1, 0 }, // TEXDEPTH
		{ 4, 0 }, // CMP
		{ 1, 0 }, // BEM
		{ 4, 0 }, // DP2ADD
		{ 2, 0 }, // DSX
		{ 2, 0 }, // DSY
		{ 5, 0 }, // TEXLDD
		{ 1, 0 }, // SETP
		{ 3, 0 }, // TEXLDL
		{ 0, 0 }, // BREAKP
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dx9bcOpcodeInfo) == Dx9bcOpcode::Count);

	static const char* s_dx9bcOpcode[] =
	{
		"nop",
		"mov",
		"add",
		"sub",
		"mad",
		"mul",
		"rcp",
		"rsq",
		"dp3",
		"dp4",
		"min",
		"max",
		"slt",
		"sge",
		"exp",
		"log",
		"lit",
		"dst",
		"lrp",
		"frc",
		"m4x4",
		"m4x3",
		"m3x4",
		"m3x3",
		"m3x2",
		"call",
		"callnz",
		"loop",
		"ret",
		"endloop",
		"label",
		"dcl",
		"pow",
		"crs",
		"sgn",
		"abs",
		"nrm",
		"sincos",
		"rep",
		"endrep",
		"if",
		"ifc",
		"else",
		"endif",
		"break",
		"breakc",
		"mova",
		"defb",
		"defi",

		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,

		"texcoord",
		"texkill",
		"tex",
		"texbem",
		"texbem1",
		"texreg2ar",
		"texreg2gb",
		"texm3x2pad",
		"texm3x2tex",
		"texm3x3pad",
		"texm3x3tex",
		"texm3x3diff",
		"texm3x3spec",
		"texm3x3vspec",
		"expp",
		"logp",
		"cnd",
		"def",
		"texreg2rgb",
		"texdp3tex",
		"texm3x2depth",
		"texdp3",
		"texm3x3",
		"texdepth",
		"cmp",
		"bem",
		"dp2add",
		"dsx",
		"dsy",
		"texldd",
		"setp",
		"texldl",
		"breakp",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dx9bcOpcode) == Dx9bcOpcode::Count);

	const char* getName(Dx9bcOpcode::Enum _opcode)
	{
		BX_CHECK(_opcode < Dx9bcOpcode::Count, "Unknown opcode id %d (%x).", _opcode, _opcode);
		return s_dx9bcOpcode[_opcode];
	}

	static const char* s_dx9bcOperandType[] =
	{
		"r",           // Temporary Register File
		"v",           // Input Register File
		"c",           // Constant Register File
		"t",           // Texture Register File (PS)
		"oPos",        // Rasterizer Register File
		"oD",          // Attribute Output Register File
		"oT",          // Texture Coordinate Output Register File
		"output",      // Output register file for VS3.0+
		"i",           // Constant Integer Vector Register File
		"oColor",      // Color Output Register File
		"oDepth",      // Depth Output Register File
		"s",           // Sampler State Register File
		"c",           // Constant Register File  2048 - 4095
		"c",           // Constant Register File  4096 - 6143
		"c",           // Constant Register File  6144 - 8191
		"b",           // Constant Boolean register file
		"aL",          // Loop counter register file
		"tempfloat16", // 16-bit float temp register file
		"misctype",    // Miscellaneous (single) registers.
		"label",       // Label
		"p",           // Predicate register
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dx9bcOperandType) == Dx9bcOperandType::Count);

	static const char* s_dx9bcDeclUsage[] =
	{
		"position",
		"blendweight",
		"blendindices",
		"normal",
		"psize",
		"texcoord",
		"tangent",
		"binormal",
		"tessfactor",
		"positiont",
		"color",
		"fog",
		"depth",
		"sample",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dx9bcDeclUsage) == Dx9bcDeclUsage::Count);

	int32_t read(bx::ReaderI* _reader, Dx9bcSubOperand& _subOperand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token, _err);

		_subOperand.type        =   Dx9bcOperandType::Enum( ( (token & UINT32_C(0x70000000) ) >> 28)
		                                                  | ( (token & UINT32_C(0x00001800) ) >>  8) );
		_subOperand.regIndex    =                             (token & UINT32_C(0x000007ff) );
		_subOperand.swizzleBits =                    uint8_t( (token & UINT32_C(0x00ff0000) ) >> 16);

		return size;
	}

	int32_t write(bx::WriterI* _writer, const Dx9bcSubOperand& _subOperand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token = 0;
		token |= (_subOperand.type        << 28) & UINT32_C(0x70000000);
		token |= (_subOperand.type        <<  8) & UINT32_C(0x00001800);
		token |=  _subOperand.regIndex           & UINT32_C(0x000007ff);
		token |= (_subOperand.swizzleBits << 16) & UINT32_C(0x00ff0000);
		size += bx::write(_writer, token, _err);

		return size;
	}

	int32_t read(bx::ReaderI* _reader, Dx9bcOperand& _operand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token, _err);

		_operand.type     =   Dx9bcOperandType::Enum( ( (token & UINT32_C(0x70000000) ) >> 28)
													| ( (token & UINT32_C(0x00001800) ) >>  8) );
		_operand.regIndex =                             (token & UINT32_C(0x000007ff) );
		_operand.addrMode = Dx9bcOperandAddrMode::Enum( (token & UINT32_C(0x00002000) ) >> 13);

		if (_operand.destination)
		{
			// Destination Parameter Token
			// https://msdn.microsoft.com/en-us/library/ff552738.aspx

			_operand.writeMask        = uint8_t( (token & UINT32_C(0x000f0000) ) >> 16);
			_operand.saturate         =     0 != (token & UINT32_C(0x00100000) );
			_operand.partialPrecision =     0 != (token & UINT32_C(0x00200000) );
			_operand.centroid         =     0 != (token & UINT32_C(0x00400000) );
		}
		else
		{
			// Source Parameter Token
			// https://msdn.microsoft.com/en-us/library/ff569716%28v=vs.85%29.aspx

			_operand.writeMask        = 0;
			_operand.saturate         = false;
			_operand.partialPrecision = false;
			_operand.centroid         = false;
			_operand.swizzleBits      = uint8_t( (token & UINT32_C(0x00ff0000) ) >> 16);
		}

		if (Dx9bcOperandAddrMode::Relative == _operand.addrMode)
		{
			size += read(_reader, _operand.subOperand, _err);
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const Dx9bcOperand& _operand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token = 0;
		token |= (_operand.type     << 28) & UINT32_C(0x70000000);
		token |= (_operand.type     <<  8) & UINT32_C(0x00001800);
		token |=  _operand.regIndex        & UINT32_C(0x000007ff);
		token |= (_operand.addrMode << 13) & UINT32_C(0x00002000);
		size += bx::write(_writer, token, _err);

		if (Dx9bcOperandAddrMode::Relative == _operand.addrMode)
		{
			size += write(_writer, _operand.subOperand, _err);
		}

		return size;
	}

	int32_t read(bx::ReaderI* _reader, Dx9bcInstruction& _instruction, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token, _err);

		_instruction.opcode = Dx9bcOpcode::Enum( (token & UINT32_C(0x0000ffff) ) );

		if (Dx9bcOpcode::Comment == _instruction.opcode)
		{
			_instruction.specific   = 0;
			_instruction.length     = uint16_t( (token & UINT32_C(0x7fff0000) ) >> 16) + 1;
			_instruction.predicated = false;
			_instruction.coissue    = false;
		}
		else
		{
			_instruction.specific   = uint8_t( (token & UINT32_C(0x00ff0000) ) >> 16);
			_instruction.length     = uint8_t( (token & UINT32_C(0x0f000000) ) >> 24) + 1;
			_instruction.predicated =     0 != (token & UINT32_C(0x10000000) );
			_instruction.coissue    =     0 != (token & UINT32_C(0x40000000) );
		}

		if (Dx9bcOpcode::Count <= _instruction.opcode)
		{
			if (Dx9bcOpcode::Comment == _instruction.opcode)
			{
				for (int32_t ii = 0, num = _instruction.length-1; ii < num; ++ii)
				{
					uint32_t tmp;
					size += bx::read(_reader, tmp, _err);
				}
			}

			return size;
		}

		uint32_t currOp = 0;

		const Dx9bcOpcodeInfo& info = s_dx9bcOpcodeInfo[bx::uint32_min(_instruction.opcode, Dx9bcOpcode::Count)];
		_instruction.numOperands = info.numOperands;
		_instruction.numValues   = info.numValues;

		switch (_instruction.opcode)
		{
		case Dx9bcOpcode::SINCOS:
			if (5 > _instruction.length)
			{
				_instruction.numOperands = 2;
			}
			break;

		default:
			break;
		};

//BX_TRACE("%d (%d), %d, %d, 0x%08x"
//		, _instruction.opcode
//		, bx::uint32_min(_instruction.opcode, Dx9bcOpcode::Count)
//		, _instruction.length
//		, _instruction.numOperands
//		, token
//		);

		const bool valuesBeforeOpcode = false
				|| Dx9bcOpcode::DCL == _instruction.opcode
				;

		if (valuesBeforeOpcode
		&&  0 < info.numValues)
		{
			size += read(_reader, _instruction.value, info.numValues*sizeof(uint32_t), _err);
		}

		_instruction.operand[0].destination = true;

		switch (_instruction.numOperands)
		{
		case 6: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 5: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 4: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 3: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 2: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 1: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 0:
			if (!valuesBeforeOpcode
			&&  0 < info.numValues)
			{
				size += read(_reader, _instruction.value, info.numValues*sizeof(uint32_t), _err);
			}
			break;

		default:
			BX_CHECK(false, "Instruction %s with invalid number of operands %d (numValues %d)."
					, getName(_instruction.opcode)
					, _instruction.numOperands
					, info.numValues
					);
			break;
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const Dx9bcInstruction& _instruction, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token = 0;
		token |=    _instruction.opcode             & UINT32_C(0x0000ffff);
		token |=   (_instruction.specific    << 16) & UINT32_C(0x00ff0000);
		token |= ( (_instruction.length - 1) << 24) & UINT32_C(0x0f000000);
		size += bx::write(_writer, token, _err);

		uint32_t currOp = 0;
		switch (_instruction.numOperands)
		{
		case 6: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 5: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 4: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 3: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 2: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 1: size += write(_writer, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 0:
			break;
		}

		return 0;
	}

	int32_t toString(char* _out, int32_t _size, const Dx9bcInstruction& _instruction)
	{
		int32_t size = 0;

		if (Dx9bcOpcode::Comment == _instruction.opcode
		||  Dx9bcOpcode::Phase   == _instruction.opcode)
		{
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "// %x"
						, _instruction.opcode
						);
			return size;
		}

		size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%2d %s"
							, _instruction.opcode
							, getName(_instruction.opcode)
							);

		switch (_instruction.opcode)
		{
		case Dx9bcOpcode::DCL:
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
					, "_%s%d (%d, %d, %d, %d)"
					, s_dx9bcDeclUsage[_instruction.value[0] & UINT32_C(0x0000000f)]
					, (_instruction.value[0] & UINT32_C(0x000f0000) )>>16
					, (_instruction.value[0] & UINT32_C(0x08000000) )>>27 // ?
					, (_instruction.value[0] & UINT32_C(0x10000000) )>>28 // texture2d
					, (_instruction.value[0] & UINT32_C(0x20000000) )>>29 // textureCube
					, (_instruction.value[0] & UINT32_C(0x40000000) )>>30 // texture3d
					);
			break;

		default:
			break;
		}

		for (uint32_t ii = 0; ii < _instruction.numOperands; ++ii)
		{
			const Dx9bcOperand& operand = _instruction.operand[ii];
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
								, "%s%s%d"
								, 0 == ii ? " " : ", "
								, s_dx9bcOperandType[operand.type]
								, operand.regIndex
								);

			if (operand.destination)
			{
				if (0xf > operand.writeMask
				&&  0   < operand.writeMask)
				{
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
										, ".%s%s%s%s"
										, 0 == (operand.writeMask & 1) ? "" : "x"
										, 0 == (operand.writeMask & 2) ? "" : "y"
										, 0 == (operand.writeMask & 4) ? "" : "z"
										, 0 == (operand.writeMask & 8) ? "" : "w"
										);
				}
			}
			else
			{
				if (Dx9bcOperandAddrMode::Relative == operand.addrMode)
				{
					const bool array = true;

					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
										, "["
										);

					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
										, "%s%d"
										, s_dx9bcOperandType[operand.subOperand.type]
										, operand.subOperand.regIndex
										);

					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
										, "%s"
										, array ? "]" : ""
										);
				}

				if (0xe4 != operand.swizzleBits)
				{
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
										, ".%c%c%c%c"
										, "xyzw"[(operand.swizzleBits   )&0x3]
										, "xyzw"[(operand.swizzleBits>>2)&0x3]
										, "xyzw"[(operand.swizzleBits>>4)&0x3]
										, "xyzw"[(operand.swizzleBits>>6)&0x3]
										);
				}
			}
		}

		switch (_instruction.opcode)
		{
		case Dx9bcOpcode::DEF:
			for (uint32_t jj = 0; jj < _instruction.numValues; ++jj)
			{
				union { int32_t i; float f; } cast = { _instruction.value[jj] };
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s%f%s"
						, 0 == jj ? " (" : ", "
						, cast.f
						, uint32_t(_instruction.numValues-1) == jj ? ")" : ""
						);
			}
			break;

		case Dx9bcOpcode::DEFI:
			for (uint32_t jj = 0; jj < _instruction.numValues; ++jj)
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s%d%s"
						, 0 == jj ? " (" : ", "
						, _instruction.value[jj]
						, uint32_t(_instruction.numValues-1) == jj ? ")" : ""
						);
			}
			break;

		default:
			break;
		}

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, Dx9bcShader& _shader, bx::Error* _err)
	{
		int32_t size = 0;
		int64_t offset = bx::seek(_reader);

		for (;;)
		{
			Dx9bcInstruction instruction;
			int32_t length = read(_reader, instruction, _err);
			size += length;

			if (Dx9bcOpcode::Count > instruction.opcode)
			{
				char temp[512];
				toString(temp, 512, instruction);

				BX_CHECK(length/4 == instruction.length
						, "%s\nread %d, expected %d"
						, temp
						, length/4
						, instruction.length
						);
			}
			else
			{
				if (Dx9bcOpcode::End == instruction.opcode)
				{
					size -= length;
					break;
				}
			}
		}

		bx::seek(_reader, offset, bx::Whence::Begin);

		_shader.byteCode.resize(size);
		bx::read(_reader, _shader.byteCode.data(), size, _err);

		return size;
	}

	int32_t write(bx::WriterI* _writer, const Dx9bcShader& _shader, bx::Error* _err)
	{
		BX_UNUSED(_writer, _shader, _err);
		return 0;
	}

	int32_t read(bx::ReaderSeekerI* _reader, Dx9bc& _bc, bx::Error* _err)
	{
		int32_t size = 0;

		size += bx::read(_reader, _bc.version, _err);

		bool pixelShader = (0xffff0000 == (_bc.version & 0xffff0000) );
		uint32_t versionMajor = (_bc.version>>8)&0xff;
		uint32_t versionMinor = _bc.version&0xff;
		BX_UNUSED(pixelShader, versionMajor, versionMinor);
		BX_TRACE("%s shader %d.%d"
			, pixelShader ? "pixel" : "vertex"
			, versionMajor
			, versionMinor
			);

		size += read(_reader, _bc.shader, _err);

		return size;
	}

	int32_t write(bx::WriterSeekerI* _writer, const Dx9bc& _dxbc, bx::Error* _err)
	{
		BX_UNUSED(_writer, _dxbc, _err);
		return 0;
	}

	void parse(const Dx9bcShader& _src, Dx9bcParseFn _fn, void* _userData, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		bx::Error err;

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			Dx9bcInstruction instruction;
			uint32_t size = read(&reader, instruction, _err);
			BX_CHECK(size/4 == instruction.length, "read %d, expected %d", size/4, instruction.length); BX_UNUSED(size);

			bool cont = _fn(token * sizeof(uint32_t), instruction, _userData);
			if (!cont)
			{
				return;
			}

			token += instruction.length;
		}
	}

	void filter(Dx9bcShader& _dst, const Dx9bcShader& _src, Dx9bcFilterFn _fn, void* _userData, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		bx::MemoryBlock mb(g_allocator);
		bx::MemoryWriter writer(&mb);

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			Dx9bcInstruction instruction;
			uint32_t size = read(&reader, instruction, _err);
			BX_CHECK(size/4 == instruction.length, "read %d, expected %d", size/4, instruction.length); BX_UNUSED(size);

			_fn(instruction, _userData);

			write(&writer, instruction, _err);

			token += instruction.length;
		}

		uint8_t* data = (uint8_t*)mb.more();
		uint32_t size = uint32_t(bx::getSize(&writer) );
		_dst.byteCode.reserve(size);
		bx::memCopy(_dst.byteCode.data(), data, size);
	}

} // namespace bgfx

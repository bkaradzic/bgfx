/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_DX9BC_H
#define BGFX_SHADER_DX9BC_H

#include <bx/readerwriter.h>

namespace bgfx
{
	struct Dx9bcOpcode
	{
		enum Enum
		{
			NOP,
			MOV,
			ADD,
			SUB,
			MAD,
			MUL,
			RCP,
			RSQ,
			DP3,
			DP4,
			MIN,
			MAX,
			SLT,
			SGE,
			EXP,
			LOG,
			LIT,
			DST,
			LRP,
			FRC,
			M4X4,
			M4X3,
			M3X4,
			M3X3,
			M3X2,
			CALL,
			CALLNZ,
			LOOP,
			RET,
			ENDLOOP,
			LABEL,
			DCL,
			POW,
			CRS,
			SGN,
			ABS,
			NRM,
			SINCOS,
			REP,
			ENDREP,
			IF,
			IFC,
			ELSE,
			ENDIF,
			BREAK,
			BREAKC,
			MOVA,
			DEFB,
			DEFI,

			Unknown = 63,
			TEXCOORD,
			TEXKILL,
			TEX,
			TEXBEM,
			TEXBEM1,
			TEXREG2AR,
			TEXREG2GB,
			TEXM3X2PAD,
			TEXM3X2TEX,
			TEXM3X3PAD,
			TEXM3X3TEX,
			TEXM3X3DIFF,
			TEXM3X3SPEC,
			TEXM3X3VSPEC,
			EXPP,
			LOGP,
			CND,
			DEF,
			TEXREG2RGB,
			TEXDP3TEX,
			TEXM3X2DEPTH,
			TEXDP3,
			TEXM3X3,
			TEXDEPTH,
			CMP,
			BEM,
			DP2ADD,
			DSX,
			DSY,
			TEXLDD,
			SETP,
			TEXLDL,
			BREAKP,

			Count,

			Phase   = 0xfffd,
			Comment = 0xfffe,
			End     = 0xffff
		};
	};

	const char* getName(Dx9bcOpcode::Enum _opcode);

	struct Dx9bcResourceDim
	{
		enum Enum
		{
			Unknown,
			Texture1D,
			Texture2D,
			TextureCube,
			Texture3D,
		};
	};

	struct Dx9bcOperandType
	{
		enum Enum
		{
			Temp,
			Input,
			Const,
			Texture,
			RastOut,
			AttrOut,
			TexCrdOut,
			Output,
			ConstInt,
			ColorOut,
			DepthOut,
			Sampler,
			Const2,
			Const3,
			Const4,
			ConstBool,
			Loop,
			TempFloat16,
			MiscType,
			Label,
			Predicate,

			Count
		};
	};

	struct Dx9bcDeclUsage
	{
		enum Enum
		{
			Position,
			BlendWeight,
			BlendIndices,
			Normal,
			Psize,
			Texcoord,
			Tangent,
			Binormal,
			TessFactor,
			PositionT,
			Color,
			Fog,
			Depth,
			Sample,

			Count
  		};
	};

	struct Dx9bcOperandAddrMode
	{
		enum Enum
		{
			Absolute,
			Relative,

			Count
		};
	};

	struct Dx9bcSubOperand
	{
		Dx9bcSubOperand() { /* not pod */ }

		Dx9bcOperandType::Enum type;
		uint32_t regIndex;
		uint8_t swizzleBits;
	};

	struct Dx9bcOperand
	{
		Dx9bcOperand() { /* not pod */ }

		Dx9bcOperandType::Enum type;
		uint32_t regIndex;

		bool destination;

		// Destination
		uint8_t writeMask;
		bool saturate;
		bool partialPrecision;
		bool centroid;

		// Source
		uint8_t swizzleBits;

		Dx9bcOperandAddrMode::Enum addrMode;
		Dx9bcSubOperand subOperand;
	};

	struct Dx9bcInstruction
	{
		Dx9bcInstruction() { /* not pod */ }

		Dx9bcOpcode::Enum opcode;
		uint16_t length;
		uint8_t numOperands;
		uint8_t numValues;
		uint8_t specific;
		bool predicated;
		bool coissue;

		Dx9bcOperand operand[6];
		int32_t value[4];
	};

	int32_t read(bx::ReaderI* _reader, Dx9bcInstruction& _instruction, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const Dx9bcInstruction& _instruction, bx::Error* _err);
	int32_t toString(char* _out, int32_t _size, const Dx9bcInstruction& _instruction);

	struct Dx9bcShader
	{
		Dx9bcShader() { /* not pod */ }

		stl::vector<uint8_t> byteCode;
	};

	int32_t read(bx::ReaderSeekerI* _reader, Dx9bcShader& _shader, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const Dx9bcShader& _shader, bx::Error* _err);

	struct Dx9bc
	{
		Dx9bc() { /* not pod */ }

		uint32_t version;
		Dx9bcShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, Dx9bc& _dx9bc, bx::Error* _err);
	int32_t write(bx::WriterSeekerI* _writer, const Dx9bc& _dx9bc, bx::Error* _err);

	typedef bool (*Dx9bcParseFn)(uint32_t _offset, const Dx9bcInstruction& _instruction, void* _userData);
	void parse(const Dx9bcShader& _src, Dx9bcParseFn _fn, void* _userData, bx::Error* _err = NULL);

	typedef void (*Dx9bcFilterFn)(Dx9bcInstruction& _instruction, void* _userData);
	void filter(Dx9bcShader& _dst, const Dx9bcShader& _src, Dx9bcFilterFn _fn, void* _userData, bx::Error* _err = NULL);

} // namespace bgfx

#endif // BGFX_SHADER_DX9BC_H

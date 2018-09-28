/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "shader_dxbc.h"

namespace bgfx
{
	struct DxbcOpcodeInfo
	{
		uint8_t numOperands;
		uint8_t numValues;
	};

	static const DxbcOpcodeInfo s_dxbcOpcodeInfo[] =
	{
		{ 3, 0 }, // ADD
		{ 3, 0 }, // AND
		{ 0, 0 }, // BREAK
		{ 1, 0 }, // BREAKC
		{ 0, 0 }, // CALL
		{ 0, 0 }, // CALLC
		{ 1, 0 }, // CASE
		{ 0, 0 }, // CONTINUE
		{ 1, 0 }, // CONTINUEC
		{ 0, 0 }, // CUT
		{ 0, 0 }, // DEFAULT
		{ 2, 0 }, // DERIV_RTX
		{ 2, 0 }, // DERIV_RTY
		{ 1, 0 }, // DISCARD
		{ 3, 0 }, // DIV
		{ 3, 0 }, // DP2
		{ 3, 0 }, // DP3
		{ 3, 0 }, // DP4
		{ 0, 0 }, // ELSE
		{ 0, 0 }, // EMIT
		{ 0, 0 }, // EMITTHENCUT
		{ 0, 0 }, // ENDIF
		{ 0, 0 }, // ENDLOOP
		{ 0, 0 }, // ENDSWITCH
		{ 3, 0 }, // EQ
		{ 2, 0 }, // EXP
		{ 2, 0 }, // FRC
		{ 2, 0 }, // FTOI
		{ 2, 0 }, // FTOU
		{ 3, 0 }, // GE
		{ 3, 0 }, // IADD
		{ 1, 0 }, // IF
		{ 3, 0 }, // IEQ
		{ 3, 0 }, // IGE
		{ 3, 0 }, // ILT
		{ 4, 0 }, // IMAD
		{ 3, 0 }, // IMAX
		{ 3, 0 }, // IMIN
		{ 4, 0 }, // IMUL
		{ 3, 0 }, // INE
		{ 2, 0 }, // INEG
		{ 3, 0 }, // ISHL
		{ 3, 0 }, // ISHR
		{ 2, 0 }, // ITOF
		{ 0, 0 }, // LABEL
		{ 3, 0 }, // LD
		{ 4, 0 }, // LD_MS
		{ 2, 0 }, // LOG
		{ 0, 0 }, // LOOP
		{ 3, 0 }, // LT
		{ 4, 0 }, // MAD
		{ 3, 0 }, // MIN
		{ 3, 0 }, // MAX
		{ 0, 1 }, // CUSTOMDATA
		{ 2, 0 }, // MOV
		{ 4, 0 }, // MOVC
		{ 3, 0 }, // MUL
		{ 3, 0 }, // NE
		{ 0, 0 }, // NOP
		{ 2, 0 }, // NOT
		{ 3, 0 }, // OR
		{ 3, 0 }, // RESINFO
		{ 0, 0 }, // RET
		{ 1, 0 }, // RETC
		{ 2, 0 }, // ROUND_NE
		{ 2, 0 }, // ROUND_NI
		{ 2, 0 }, // ROUND_PI
		{ 2, 0 }, // ROUND_Z
		{ 2, 0 }, // RSQ
		{ 4, 0 }, // SAMPLE
		{ 5, 0 }, // SAMPLE_C
		{ 5, 0 }, // SAMPLE_C_LZ
		{ 5, 0 }, // SAMPLE_L
		{ 6, 0 }, // SAMPLE_D
		{ 5, 0 }, // SAMPLE_B
		{ 2, 0 }, // SQRT
		{ 1, 0 }, // SWITCH
		{ 3, 0 }, // SINCOS
		{ 4, 0 }, // UDIV
		{ 3, 0 }, // ULT
		{ 3, 0 }, // UGE
		{ 4, 0 }, // UMUL
		{ 4, 0 }, // UMAD
		{ 3, 0 }, // UMAX
		{ 3, 0 }, // UMIN
		{ 3, 0 }, // USHR
		{ 2, 0 }, // UTOF
		{ 3, 0 }, // XOR
		{ 1, 1 }, // DCL_RESOURCE
		{ 1, 0 }, // DCL_CONSTANT_BUFFER
		{ 1, 0 }, // DCL_SAMPLER
		{ 1, 1 }, // DCL_INDEX_RANGE
		{ 1, 0 }, // DCL_GS_OUTPUT_PRIMITIVE_TOPOLOGY
		{ 1, 0 }, // DCL_GS_INPUT_PRIMITIVE
		{ 0, 1 }, // DCL_MAX_OUTPUT_VERTEX_COUNT
		{ 1, 0 }, // DCL_INPUT
		{ 1, 1 }, // DCL_INPUT_SGV
		{ 1, 0 }, // DCL_INPUT_SIV
		{ 1, 0 }, // DCL_INPUT_PS
		{ 1, 1 }, // DCL_INPUT_PS_SGV
		{ 1, 1 }, // DCL_INPUT_PS_SIV
		{ 1, 0 }, // DCL_OUTPUT
		{ 1, 0 }, // DCL_OUTPUT_SGV
		{ 1, 1 }, // DCL_OUTPUT_SIV
		{ 0, 1 }, // DCL_TEMPS
		{ 0, 3 }, // DCL_INDEXABLE_TEMP
		{ 0, 0 }, // DCL_GLOBAL_FLAGS

		{ 0, 0 }, // InstrD3D10
		{ 4, 0 }, // LOD
		{ 4, 0 }, // GATHER4
		{ 0, 0 }, // SAMPLE_POS
		{ 0, 0 }, // SAMPLE_INFO

		{ 0, 0 }, // InstrD3D10_1
		{ 0, 0 }, // HS_DECLS
		{ 0, 0 }, // HS_CONTROL_POINT_PHASE
		{ 0, 0 }, // HS_FORK_PHASE
		{ 0, 0 }, // HS_JOIN_PHASE
		{ 0, 0 }, // EMIT_STREAM
		{ 0, 0 }, // CUT_STREAM
		{ 1, 0 }, // EMITTHENCUT_STREAM
		{ 1, 0 }, // INTERFACE_CALL
		{ 0, 0 }, // BUFINFO
		{ 2, 0 }, // DERIV_RTX_COARSE
		{ 2, 0 }, // DERIV_RTX_FINE
		{ 2, 0 }, // DERIV_RTY_COARSE
		{ 2, 0 }, // DERIV_RTY_FINE
		{ 5, 0 }, // GATHER4_C
		{ 5, 0 }, // GATHER4_PO
		{ 0, 0 }, // GATHER4_PO_C
		{ 2, 0 }, // RCP
		{ 0, 0 }, // F32TOF16
		{ 0, 0 }, // F16TOF32
		{ 0, 0 }, // UADDC
		{ 0, 0 }, // USUBB
		{ 0, 0 }, // COUNTBITS
		{ 0, 0 }, // FIRSTBIT_HI
		{ 0, 0 }, // FIRSTBIT_LO
		{ 0, 0 }, // FIRSTBIT_SHI
		{ 4, 0 }, // UBFE
		{ 4, 0 }, // IBFE
		{ 5, 0 }, // BFI
		{ 0, 0 }, // BFREV
		{ 5, 0 }, // SWAPC
		{ 0, 0 }, // DCL_STREAM
		{ 1, 0 }, // DCL_FUNCTION_BODY
		{ 0, 0 }, // DCL_FUNCTION_TABLE
		{ 0, 0 }, // DCL_INTERFACE
		{ 0, 0 }, // DCL_INPUT_CONTROL_POINT_COUNT
		{ 0, 0 }, // DCL_OUTPUT_CONTROL_POINT_COUNT
		{ 0, 0 }, // DCL_TESS_DOMAIN
		{ 0, 0 }, // DCL_TESS_PARTITIONING
		{ 0, 0 }, // DCL_TESS_OUTPUT_PRIMITIVE
		{ 0, 0 }, // DCL_HS_MAX_TESSFACTOR
		{ 0, 0 }, // DCL_HS_FORK_PHASE_INSTANCE_COUNT
		{ 0, 0 }, // DCL_HS_JOIN_PHASE_INSTANCE_COUNT
		{ 0, 3 }, // DCL_THREAD_GROUP
		{ 1, 1 }, // DCL_UNORDERED_ACCESS_VIEW_TYPED
		{ 1, 0 }, // DCL_UNORDERED_ACCESS_VIEW_RAW
		{ 1, 1 }, // DCL_UNORDERED_ACCESS_VIEW_STRUCTURED
		{ 1, 1 }, // DCL_THREAD_GROUP_SHARED_MEMORY_RAW
		{ 1, 2 }, // DCL_THREAD_GROUP_SHARED_MEMORY_STRUCTURED
		{ 1, 0 }, // DCL_RESOURCE_RAW
		{ 1, 1 }, // DCL_RESOURCE_STRUCTURED
		{ 3, 0 }, // LD_UAV_TYPED
		{ 3, 0 }, // STORE_UAV_TYPED
		{ 3, 0 }, // LD_RAW
		{ 3, 0 }, // STORE_RAW
		{ 4, 0 }, // LD_STRUCTURED
		{ 4, 0 }, // STORE_STRUCTURED
		{ 3, 0 }, // ATOMIC_AND
		{ 3, 0 }, // ATOMIC_OR
		{ 3, 0 }, // ATOMIC_XOR
		{ 3, 0 }, // ATOMIC_CMP_STORE
		{ 3, 0 }, // ATOMIC_IADD
		{ 3, 0 }, // ATOMIC_IMAX
		{ 3, 0 }, // ATOMIC_IMIN
		{ 3, 0 }, // ATOMIC_UMAX
		{ 3, 0 }, // ATOMIC_UMIN
		{ 2, 0 }, // IMM_ATOMIC_ALLOC
		{ 2, 0 }, // IMM_ATOMIC_CONSUME
		{ 0, 0 }, // IMM_ATOMIC_IADD
		{ 0, 0 }, // IMM_ATOMIC_AND
		{ 0, 0 }, // IMM_ATOMIC_OR
		{ 0, 0 }, // IMM_ATOMIC_XOR
		{ 0, 0 }, // IMM_ATOMIC_EXCH
		{ 0, 0 }, // IMM_ATOMIC_CMP_EXCH
		{ 0, 0 }, // IMM_ATOMIC_IMAX
		{ 0, 0 }, // IMM_ATOMIC_IMIN
		{ 0, 0 }, // IMM_ATOMIC_UMAX
		{ 0, 0 }, // IMM_ATOMIC_UMIN
		{ 0, 0 }, // SYNC
		{ 3, 0 }, // DADD
		{ 3, 0 }, // DMAX
		{ 3, 0 }, // DMIN
		{ 3, 0 }, // DMUL
		{ 3, 0 }, // DEQ
		{ 3, 0 }, // DGE
		{ 3, 0 }, // DLT
		{ 3, 0 }, // DNE
		{ 2, 0 }, // DMOV
		{ 4, 0 }, // DMOVC
		{ 0, 0 }, // DTOF
		{ 0, 0 }, // FTOD
		{ 3, 0 }, // EVAL_SNAPPED
		{ 3, 0 }, // EVAL_SAMPLE_INDEX
		{ 2, 0 }, // EVAL_CENTROID
		{ 0, 1 }, // DCL_GS_INSTANCE_COUNT
		{ 0, 0 }, // ABORT
		{ 0, 0 }, // DEBUG_BREAK

		{ 0, 0 }, // InstrD3D11
		{ 0, 0 }, // DDIV
		{ 0, 0 }, // DFMA
		{ 0, 0 }, // DRCP
		{ 0, 0 }, // MSAD
		{ 0, 0 }, // DTOI
		{ 0, 0 }, // DTOU
		{ 0, 0 }, // ITOD
		{ 0, 0 }, // UTOD
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcOpcodeInfo) == DxbcOpcode::Count);

	static const char* s_dxbcOpcode[] =
	{
		"add",
		"and",
		"break",
		"breakc",
		"call",
		"callc",
		"case",
		"continue",
		"continuec",
		"cut",
		"default",
		"deriv_rtx",
		"deriv_rty",
		"discard",
		"div",
		"dp2",
		"dp3",
		"dp4",
		"else",
		"emit",
		"emitthencut",
		"endif",
		"endloop",
		"endswitch",
		"eq",
		"exp",
		"frc",
		"ftoi",
		"ftou",
		"ge",
		"iadd",
		"if",
		"ieq",
		"ige",
		"ilt",
		"imad",
		"imax",
		"imin",
		"imul",
		"ine",
		"ineg",
		"ishl",
		"ishr",
		"itof",
		"label",
		"ld",
		"ld_ms",
		"log",
		"loop",
		"lt",
		"mad",
		"min",
		"max",
		"customdata",
		"mov",
		"movc",
		"mul",
		"ne",
		"nop",
		"not",
		"or",
		"resinfo",
		"ret",
		"retc",
		"round_ne",
		"round_ni",
		"round_pi",
		"round_z",
		"rsq",
		"sample",
		"sample_c",
		"sample_c_lz",
		"sample_l",
		"sample_d",
		"sample_b",
		"sqrt",
		"switch",
		"sincos",
		"udiv",
		"ult",
		"uge",
		"umul",
		"umad",
		"umax",
		"umin",
		"ushr",
		"utof",
		"xor",
		"dcl_resource",
		"dcl_constantbuffer",
		"dcl_sampler",
		"dcl_index_range",
		"dcl_gs_output_primitive_topology",
		"dcl_gs_input_primitive",
		"dcl_max_output_vertex_count",
		"dcl_input",
		"dcl_input_sgv",
		"dcl_input_siv",
		"dcl_input_ps",
		"dcl_input_ps_sgv",
		"dcl_input_ps_siv",
		"dcl_output",
		"dcl_output_sgv",
		"dcl_output_siv",
		"dcl_temps",
		"dcl_indexable_temp",
		"dcl_global_flags",

		NULL,
		"lod",
		"gather4",
		"sample_pos",
		"sample_info",

		NULL,
		"hs_decls",
		"hs_control_point_phase",
		"hs_fork_phase",
		"hs_join_phase",
		"emit_stream",
		"cut_stream",
		"emitthencut_stream",
		"interface_call",
		"bufinfo",
		"deriv_rtx_coarse",
		"deriv_rtx_fine",
		"deriv_rty_coarse",
		"deriv_rty_fine",
		"gather4_c",
		"gather4_po",
		"gather4_po_c",
		"rcp",
		"f32tof16",
		"f16tof32",
		"uaddc",
		"usubb",
		"countbits",
		"firstbit_hi",
		"firstbit_lo",
		"firstbit_shi",
		"ubfe",
		"ibfe",
		"bfi",
		"bfrev",
		"swapc",
		"dcl_stream",
		"dcl_function_body",
		"dcl_function_table",
		"dcl_interface",
		"dcl_input_control_point_count",
		"dcl_output_control_point_count",
		"dcl_tess_domain",
		"dcl_tess_partitioning",
		"dcl_tess_output_primitive",
		"dcl_hs_max_tessfactor",
		"dcl_hs_fork_phase_instance_count",
		"dcl_hs_join_phase_instance_count",
		"dcl_thread_group",
		"dcl_unordered_access_view_typed",
		"dcl_unordered_access_view_raw",
		"dcl_unordered_access_view_structured",
		"dcl_thread_group_shared_memory_raw",
		"dcl_thread_group_shared_memory_structured",
		"dcl_resource_raw",
		"dcl_resource_structured",
		"ld_uav_typed",
		"store_uav_typed",
		"ld_raw",
		"store_raw",
		"ld_structured",
		"store_structured",
		"atomic_and",
		"atomic_or",
		"atomic_xor",
		"atomic_cmp_store",
		"atomic_iadd",
		"atomic_imax",
		"atomic_imin",
		"atomic_umax",
		"atomic_umin",
		"imm_atomic_alloc",
		"imm_atomic_consume",
		"imm_atomic_iadd",
		"imm_atomic_and",
		"imm_atomic_or",
		"imm_atomic_xor",
		"imm_atomic_exch",
		"imm_atomic_cmp_exch",
		"imm_atomic_imax",
		"imm_atomic_imin",
		"imm_atomic_umax",
		"imm_atomic_umin",
		"sync",
		"dadd",
		"dmax",
		"dmin",
		"dmul",
		"deq",
		"dge",
		"dlt",
		"dne",
		"dmov",
		"dmovc",
		"dtof",
		"ftod",
		"eval_snapped",
		"eval_sample_index",
		"eval_centroid",
		"dcl_gs_instance_count",
		"abort",
		"debug_break",

		NULL,
		"ddiv",
		"dfma",
		"drcp",
		"msad",
		"dtoi",
		"dtou",
		"itod",
		"utod",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcOpcode) == DxbcOpcode::Count);

	const char* getName(DxbcOpcode::Enum _opcode)
	{
		BX_CHECK(_opcode < DxbcOpcode::Count, "Unknown opcode id %d.", _opcode);
		return s_dxbcOpcode[_opcode];
	}

	static const char* s_dxbcSrvType[] =
	{
		"",                 // Unknown
		"Buffer",           // Buffer
		"Texture1D",        // Texture1D
		"Texture2D",        // Texture2D
		"Texture2DMS",      // Texture2DMS
		"Texture3D",        // Texture3D
		"TextureCube",      // TextureCube
		"Texture1DArray",   // Texture1DArray
		"Texture2DArray",   // Texture2DArray
		"Texture2DMSArray", // Texture2DMSArray
		"TextureCubearray", // TextureCubearray
		"RawBuffer",        // RawBuffer
		"StructuredBuffer", // StructuredBuffer
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcSrvType) == DxbcResourceDim::Count);

	const char* s_dxbcInterpolationName[] =
	{
		"",
		"constant",
		"linear",
		"linear centroid",
		"linear noperspective",
		"linear noperspective centroid",
		"linear sample",
		"linear noperspective sample",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcInterpolationName) == DxbcInterpolation::Count);

	// mesa/src/gallium/state_trackers/d3d1x/d3d1xshader/defs/shortfiles.txt
	static const char* s_dxbcOperandType[] =
	{
		"r",                         // Temp
		"v",                         // Input
		"o",                         // Output
		"x",                         // TempArray
		"l",                         // Imm32
		"d",                         // Imm64
		"s",                         // Sampler
		"t",                         // Resource
		"cb",                        // ConstantBuffer
		"icb",                       // ImmConstantBuffer
		"label",                     // Label
		"vPrim",                     // PrimitiveID
		"oDepth",                    // OutputDepth
		"null",                      // Null
		"rasterizer",                // Rasterizer
		"oMask",                     // CoverageMask
		"stream",                    // Stream
		"function_body",             // FunctionBody
		"function_table",            // FunctionTable
		"interface",                 // Interface
		"function_input",            // FunctionInput
		"function_output",           // FunctionOutput
		"vOutputControlPointID",     // OutputControlPointId
		"vForkInstanceID",           // InputForkInstanceId
		"vJoinInstanceID",           // InputJoinInstanceId
		"vicp",                      // InputControlPoint
		"vocp",                      // OutputControlPoint
		"vpc",                       // InputPatchConstant
		"vDomain",                   // InputDomainPoint
		"this",                      // ThisPointer
		"u",                         // UnorderedAccessView
		"g",                         // ThreadGroupSharedMemory
		"vThreadID",                 // InputThreadId
		"vThreadGrouID",             // InputThreadGroupId
		"vThreadIDInGroup",          // InputThreadIdInGroup
		"vCoverage",                 // InputCoverageMask
		"vThreadIDInGroupFlattened", // InputThreadIdInGroupFlattened
		"vGSInstanceID",             // InputGsInstanceId
		"oDepthGE",                  // OutputDepthGreaterEqual
		"oDepthLE",                  // OutputDepthLessEqual
		"vCycleCounter",             // CycleCounter
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcOperandType) == DxbcOperandType::Count);

	static const char* s_dxbcCustomDataClass[] =
	{
		"Comment",
		"DebugInfo",
		"Opaque",
		"dcl_immediateConstantBuffer",
		"ShaderMessage",
		"ClipPlaneConstantMappingsForDx9",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_dxbcCustomDataClass) == DxbcCustomDataClass::Count);

#define DXBC_MAX_NAME_STRING 512

	int32_t readString(bx::ReaderSeekerI* _reader, int64_t _offset, char* _out, uint32_t _max, bx::Error* _err)
	{
		int64_t oldOffset = bx::seek(_reader);
		bx::seek(_reader, _offset, bx::Whence::Begin);

		int32_t size = 0;

		for (uint32_t ii = 0; ii < _max-1; ++ii)
		{
			char ch;
			size += bx::read(_reader, ch, _err);
			*_out++ = ch;

			if ('\0' == ch)
			{
				break;
			}
		}
		*_out = '\0';

		bx::seek(_reader, oldOffset, bx::Whence::Begin);

		return size;
	}

	inline uint32_t dxbcMixF(uint32_t _b, uint32_t _c, uint32_t _d)
	{
		const uint32_t tmp0   = bx::uint32_xor(_c, _d);
		const uint32_t tmp1   = bx::uint32_and(_b, tmp0);
		const uint32_t result = bx::uint32_xor(_d, tmp1);

		return result;
	}

	inline uint32_t dxbcMixG(uint32_t _b, uint32_t _c, uint32_t _d)
	{
		return dxbcMixF(_d, _b, _c);
	}

	inline uint32_t dxbcMixH(uint32_t _b, uint32_t _c, uint32_t _d)
	{
		const uint32_t tmp0   = bx::uint32_xor(_b, _c);
		const uint32_t result = bx::uint32_xor(_d, tmp0);

		return result;
	}

	inline uint32_t dxbcMixI(uint32_t _b, uint32_t _c, uint32_t _d)
	{
		const uint32_t tmp0   = bx::uint32_orc(_b, _d);
		const uint32_t result = bx::uint32_xor(_c, tmp0);

		return result;
	}

	void dxbcHashBlock(const uint32_t* data, uint32_t* hash)
	{
		const uint32_t d0  = data[ 0];
		const uint32_t d1  = data[ 1];
		const uint32_t d2  = data[ 2];
		const uint32_t d3  = data[ 3];
		const uint32_t d4  = data[ 4];
		const uint32_t d5  = data[ 5];
		const uint32_t d6  = data[ 6];
		const uint32_t d7  = data[ 7];
		const uint32_t d8  = data[ 8];
		const uint32_t d9  = data[ 9];
		const uint32_t d10 = data[10];
		const uint32_t d11 = data[11];
		const uint32_t d12 = data[12];
		const uint32_t d13 = data[13];
		const uint32_t d14 = data[14];
		const uint32_t d15 = data[15];

		uint32_t aa = hash[0];
		uint32_t bb = hash[1];
		uint32_t cc = hash[2];
		uint32_t dd = hash[3];

		aa = bb + bx::uint32_rol(aa + dxbcMixF(bb, cc, dd) + d0  + 0xd76aa478,  7);
		dd = aa + bx::uint32_rol(dd + dxbcMixF(aa, bb, cc) + d1  + 0xe8c7b756, 12);
		cc = dd + bx::uint32_ror(cc + dxbcMixF(dd, aa, bb) + d2  + 0x242070db, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixF(cc, dd, aa) + d3  + 0xc1bdceee, 10);
		aa = bb + bx::uint32_rol(aa + dxbcMixF(bb, cc, dd) + d4  + 0xf57c0faf,  7);
		dd = aa + bx::uint32_rol(dd + dxbcMixF(aa, bb, cc) + d5  + 0x4787c62a, 12);
		cc = dd + bx::uint32_ror(cc + dxbcMixF(dd, aa, bb) + d6  + 0xa8304613, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixF(cc, dd, aa) + d7  + 0xfd469501, 10);
		aa = bb + bx::uint32_rol(aa + dxbcMixF(bb, cc, dd) + d8  + 0x698098d8,  7);
		dd = aa + bx::uint32_rol(dd + dxbcMixF(aa, bb, cc) + d9  + 0x8b44f7af, 12);
		cc = dd + bx::uint32_ror(cc + dxbcMixF(dd, aa, bb) + d10 + 0xffff5bb1, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixF(cc, dd, aa) + d11 + 0x895cd7be, 10);
		aa = bb + bx::uint32_rol(aa + dxbcMixF(bb, cc, dd) + d12 + 0x6b901122,  7);
		dd = aa + bx::uint32_rol(dd + dxbcMixF(aa, bb, cc) + d13 + 0xfd987193, 12);
		cc = dd + bx::uint32_ror(cc + dxbcMixF(dd, aa, bb) + d14 + 0xa679438e, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixF(cc, dd, aa) + d15 + 0x49b40821, 10);

		aa = bb + bx::uint32_rol(aa + dxbcMixG(bb, cc, dd) + d1  + 0xf61e2562,  5);
		dd = aa + bx::uint32_rol(dd + dxbcMixG(aa, bb, cc) + d6  + 0xc040b340,  9);
		cc = dd + bx::uint32_rol(cc + dxbcMixG(dd, aa, bb) + d11 + 0x265e5a51, 14);
		bb = cc + bx::uint32_ror(bb + dxbcMixG(cc, dd, aa) + d0  + 0xe9b6c7aa, 12);
		aa = bb + bx::uint32_rol(aa + dxbcMixG(bb, cc, dd) + d5  + 0xd62f105d,  5);
		dd = aa + bx::uint32_rol(dd + dxbcMixG(aa, bb, cc) + d10 + 0x02441453,  9);
		cc = dd + bx::uint32_rol(cc + dxbcMixG(dd, aa, bb) + d15 + 0xd8a1e681, 14);
		bb = cc + bx::uint32_ror(bb + dxbcMixG(cc, dd, aa) + d4  + 0xe7d3fbc8, 12);
		aa = bb + bx::uint32_rol(aa + dxbcMixG(bb, cc, dd) + d9  + 0x21e1cde6,  5);
		dd = aa + bx::uint32_rol(dd + dxbcMixG(aa, bb, cc) + d14 + 0xc33707d6,  9);
		cc = dd + bx::uint32_rol(cc + dxbcMixG(dd, aa, bb) + d3  + 0xf4d50d87, 14);
		bb = cc + bx::uint32_ror(bb + dxbcMixG(cc, dd, aa) + d8  + 0x455a14ed, 12);
		aa = bb + bx::uint32_rol(aa + dxbcMixG(bb, cc, dd) + d13 + 0xa9e3e905,  5);
		dd = aa + bx::uint32_rol(dd + dxbcMixG(aa, bb, cc) + d2  + 0xfcefa3f8,  9);
		cc = dd + bx::uint32_rol(cc + dxbcMixG(dd, aa, bb) + d7  + 0x676f02d9, 14);
		bb = cc + bx::uint32_ror(bb + dxbcMixG(cc, dd, aa) + d12 + 0x8d2a4c8a, 12);

		aa = bb + bx::uint32_rol(aa + dxbcMixH(bb, cc, dd) + d5  + 0xfffa3942,  4);
		dd = aa + bx::uint32_rol(dd + dxbcMixH(aa, bb, cc) + d8  + 0x8771f681, 11);
		cc = dd + bx::uint32_rol(cc + dxbcMixH(dd, aa, bb) + d11 + 0x6d9d6122, 16);
		bb = cc + bx::uint32_ror(bb + dxbcMixH(cc, dd, aa) + d14 + 0xfde5380c,  9);
		aa = bb + bx::uint32_rol(aa + dxbcMixH(bb, cc, dd) + d1  + 0xa4beea44,  4);
		dd = aa + bx::uint32_rol(dd + dxbcMixH(aa, bb, cc) + d4  + 0x4bdecfa9, 11);
		cc = dd + bx::uint32_rol(cc + dxbcMixH(dd, aa, bb) + d7  + 0xf6bb4b60, 16);
		bb = cc + bx::uint32_ror(bb + dxbcMixH(cc, dd, aa) + d10 + 0xbebfbc70,  9);
		aa = bb + bx::uint32_rol(aa + dxbcMixH(bb, cc, dd) + d13 + 0x289b7ec6,  4);
		dd = aa + bx::uint32_rol(dd + dxbcMixH(aa, bb, cc) + d0  + 0xeaa127fa, 11);
		cc = dd + bx::uint32_rol(cc + dxbcMixH(dd, aa, bb) + d3  + 0xd4ef3085, 16);
		bb = cc + bx::uint32_ror(bb + dxbcMixH(cc, dd, aa) + d6  + 0x04881d05,  9);
		aa = bb + bx::uint32_rol(aa + dxbcMixH(bb, cc, dd) + d9  + 0xd9d4d039,  4);
		dd = aa + bx::uint32_rol(dd + dxbcMixH(aa, bb, cc) + d12 + 0xe6db99e5, 11);
		cc = dd + bx::uint32_rol(cc + dxbcMixH(dd, aa, bb) + d15 + 0x1fa27cf8, 16);
		bb = cc + bx::uint32_ror(bb + dxbcMixH(cc, dd, aa) + d2  + 0xc4ac5665,  9);

		aa = bb + bx::uint32_rol(aa + dxbcMixI(bb, cc, dd) + d0  + 0xf4292244,  6);
		dd = aa + bx::uint32_rol(dd + dxbcMixI(aa, bb, cc) + d7  + 0x432aff97, 10);
		cc = dd + bx::uint32_rol(cc + dxbcMixI(dd, aa, bb) + d14 + 0xab9423a7, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixI(cc, dd, aa) + d5  + 0xfc93a039, 11);
		aa = bb + bx::uint32_rol(aa + dxbcMixI(bb, cc, dd) + d12 + 0x655b59c3,  6);
		dd = aa + bx::uint32_rol(dd + dxbcMixI(aa, bb, cc) + d3  + 0x8f0ccc92, 10);
		cc = dd + bx::uint32_rol(cc + dxbcMixI(dd, aa, bb) + d10 + 0xffeff47d, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixI(cc, dd, aa) + d1  + 0x85845dd1, 11);
		aa = bb + bx::uint32_rol(aa + dxbcMixI(bb, cc, dd) + d8  + 0x6fa87e4f,  6);
		dd = aa + bx::uint32_rol(dd + dxbcMixI(aa, bb, cc) + d15 + 0xfe2ce6e0, 10);
		cc = dd + bx::uint32_rol(cc + dxbcMixI(dd, aa, bb) + d6  + 0xa3014314, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixI(cc, dd, aa) + d13 + 0x4e0811a1, 11);
		aa = bb + bx::uint32_rol(aa + dxbcMixI(bb, cc, dd) + d4  + 0xf7537e82,  6);
		dd = aa + bx::uint32_rol(dd + dxbcMixI(aa, bb, cc) + d11 + 0xbd3af235, 10);
		cc = dd + bx::uint32_rol(cc + dxbcMixI(dd, aa, bb) + d2  + 0x2ad7d2bb, 15);
		bb = cc + bx::uint32_ror(bb + dxbcMixI(cc, dd, aa) + d9  + 0xeb86d391, 11);

		hash[0] += aa;
		hash[1] += bb;
		hash[2] += cc;
		hash[3] += dd;
	}

	// dxbc hash function is slightly modified version of MD5 hash.
	// https://tools.ietf.org/html/rfc1321
	// http://www.efgh.com/software/md5.txt
	//
	// Assumption is that data pointer, size are both 4-byte aligned,
	// and little endian.
	//
	void dxbcHash(const void* _data, uint32_t _size, void* _digest)
	{
		uint32_t hash[4] =
		{
			0x67452301,
			0xefcdab89,
			0x98badcfe,
			0x10325476,
		};

		const uint32_t* data = (const uint32_t*)_data;
		for (uint32_t ii = 0, num = _size/64; ii < num; ++ii)
		{
			dxbcHashBlock(data, hash);
			data += 16;
		}

		uint32_t last[16];
		bx::memSet(last, 0, sizeof(last) );

		const uint32_t remaining = _size & 0x3f;

		if (remaining >= 56)
		{
			bx::memCopy(&last[0], data, remaining);
			last[remaining/4] = 0x80;
			dxbcHashBlock(last, hash);

			bx::memSet(&last[1], 0, 56);
		}
		else
		{
			bx::memCopy(&last[1], data, remaining);
			last[1 + remaining/4] = 0x80;
		}

		last[ 0] = _size * 8;
		last[15] = _size * 2 + 1;
		dxbcHashBlock(last, hash);

		bx::memCopy(_digest, hash, 16);
	}

	int32_t read(bx::ReaderI* _reader, DxbcSubOperand& _subOperand, bx::Error* _err)
	{
		uint32_t token;
		int32_t size = 0;

		// 0       1       2       3
		// 76543210765432107654321076543210
		// e222111000nnttttttttssssssssmmoo
		// ^^  ^  ^  ^ ^       ^       ^ ^-- number of operands
		// ||  |  |  | |       |       +---- operand mode
		// ||  |  |  | |       +------------ operand mode bits
		// ||  |  |  | +-------------------- type
		// ||  |  |  +---------------------- number of addressing modes
		// ||  |  +------------------------- addressing mode 0
		// ||  +---------------------------- addressing mode 1
		// |+------------------------------- addressing mode 2
		// +-------------------------------- extended

		size += bx::read(_reader, token, _err);
		_subOperand.type         = DxbcOperandType::Enum( (token & UINT32_C(0x000ff000) ) >> 12);
		_subOperand.numAddrModes =               uint8_t( (token & UINT32_C(0x00300000) ) >> 20);
		_subOperand.addrMode     =               uint8_t( (token & UINT32_C(0x01c00000) ) >> 22);
		_subOperand.mode         = DxbcOperandMode::Enum( (token & UINT32_C(0x0000000c) ) >>  2);
		_subOperand.modeBits     =               uint8_t( (token & UINT32_C(0x00000ff0) ) >>  4) & "\x0f\xff\x03\x00"[_subOperand.mode];
		_subOperand.num          =               uint8_t( (token & UINT32_C(0x00000003) )      );

		switch (_subOperand.addrMode)
		{
		case DxbcOperandAddrMode::Imm32:
			size += bx::read(_reader, _subOperand.regIndex, _err);
			break;

		case DxbcOperandAddrMode::Reg:
			{
				DxbcSubOperand subOperand;
				size += read(_reader, subOperand, _err);
			}
			break;

		case DxbcOperandAddrMode::RegImm32:
			{
				size += bx::read(_reader, _subOperand.regIndex, _err);

				DxbcSubOperand subOperand;
				size += read(_reader, subOperand, _err);
			}
			break;

		case DxbcOperandAddrMode::RegImm64:
			{
				size += bx::read(_reader, _subOperand.regIndex, _err);
				size += bx::read(_reader, _subOperand.regIndex, _err);

				DxbcSubOperand subOperand;
				size += read(_reader, subOperand, _err);
			}
			break;

		default:
			BX_CHECK(false, "sub operand addressing mode %d", _subOperand.addrMode);
			break;
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const DxbcSubOperand& _subOperand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token = 0;
		token |= (_subOperand.type         << 12) & UINT32_C(0x000ff000);
		token |= (_subOperand.numAddrModes << 20) & UINT32_C(0x00300000);
		token |= (_subOperand.addrMode     << 22) & UINT32_C(0x01c00000);
		token |= (_subOperand.mode         <<  2) & UINT32_C(0x0000000c);
		token |= (_subOperand.modeBits     <<  4) & UINT32_C(0x00000ff0);
		token |=  _subOperand.num                 & UINT32_C(0x00000003);
		size += bx::write(_writer, token, _err);

		switch (_subOperand.addrMode)
		{
		case DxbcOperandAddrMode::Imm32:
			size += bx::write(_writer, _subOperand.regIndex, _err);
			break;

		case DxbcOperandAddrMode::Reg:
			{
				DxbcSubOperand subOperand;
				size += write(_writer, subOperand, _err);
			}
			break;

		case DxbcOperandAddrMode::RegImm32:
			{
				size += bx::write(_writer, _subOperand.regIndex, _err);

				DxbcSubOperand subOperand;
				size += write(_writer, subOperand, _err);
			}
			break;

		case DxbcOperandAddrMode::RegImm64:
			{
				size += bx::write(_writer, _subOperand.regIndex, _err);
				size += bx::write(_writer, _subOperand.regIndex, _err);

				DxbcSubOperand subOperand;
				size += write(_writer, subOperand, _err);
			}
			break;

		default:
			BX_CHECK(false, "sub operand addressing mode %d", _subOperand.addrMode);
			break;
		}

		return size;
	}

	int32_t read(bx::ReaderI* _reader, DxbcOperand& _operand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token, _err);

		// 0       1       2       3
		// 76543210765432107654321076543210
		// e222111000nnttttttttssssssssmmoo
		// ^^  ^  ^  ^ ^       ^       ^ ^-- number of operands
		// ||  |  |  | |       |       +---- operand mode
		// ||  |  |  | |       +------------ operand mode bits
		// ||  |  |  | +-------------------- type
		// ||  |  |  +---------------------- number of addressing modes
		// ||  |  +------------------------- addressing mode 0
		// ||  +---------------------------- addressing mode 1
		// |+------------------------------- addressing mode 2
		// +-------------------------------- extended

		_operand.numAddrModes =               uint8_t( (token & UINT32_C(0x00300000) ) >> 20);
		_operand.addrMode[0]  =               uint8_t( (token & UINT32_C(0x01c00000) ) >> 22);
		_operand.addrMode[1]  =               uint8_t( (token & UINT32_C(0x0e000000) ) >> 25);
		_operand.addrMode[2]  =               uint8_t( (token & UINT32_C(0x70000000) ) >> 28);
		_operand.type         = DxbcOperandType::Enum( (token & UINT32_C(0x000ff000) ) >> 12);
		_operand.mode         = DxbcOperandMode::Enum( (token & UINT32_C(0x0000000c) ) >>  2);
		_operand.modeBits     =               uint8_t( (token & UINT32_C(0x00000ff0) ) >>  4) & "\x0f\xff\x03\x00"[_operand.mode];
		_operand.num          =               uint8_t( (token & UINT32_C(0x00000003) )      );

		const bool extended = 0 != (token & UINT32_C(0x80000000) );
		if (extended)
		{
			uint32_t extBits = 0;
			size += bx::read(_reader, extBits, _err);

			_operand.modifier = DxbcOperandModifier::Enum( (extBits & UINT32_C(0x00003fc0) ) >> 6);
		}
		else
		{
			_operand.modifier = DxbcOperandModifier::None;
		}

		switch (_operand.type)
		{
		case DxbcOperandType::Imm32:
			_operand.num = 2 == _operand.num ? 4 : _operand.num;
			for (uint32_t ii = 0; ii < _operand.num; ++ii)
			{
				size += bx::read(_reader, _operand.un.imm32[ii], _err);
			}
			break;

		case DxbcOperandType::Imm64:
			_operand.num = 2 == _operand.num ? 4 : _operand.num;
			for (uint32_t ii = 0; ii < _operand.num; ++ii)
			{
				size += bx::read(_reader, _operand.un.imm64[ii], _err);
			}
			break;

		default:
			break;
		}

		for (uint32_t ii = 0; ii < _operand.numAddrModes; ++ii)
		{
			switch (_operand.addrMode[ii])
			{
			case DxbcOperandAddrMode::Imm32:
				size += bx::read(_reader, _operand.regIndex[ii], _err);
				break;

			case DxbcOperandAddrMode::Reg:
				size += read(_reader, _operand.subOperand[ii], _err);
				break;

			case DxbcOperandAddrMode::RegImm32:
				size += bx::read(_reader, _operand.regIndex[ii], _err);
				size += read(_reader, _operand.subOperand[ii], _err);
				break;

			default:
				BX_CHECK(false, "operand %d addressing mode %d", ii, _operand.addrMode[ii]);
				break;
			}
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const DxbcOperand& _operand, bx::Error* _err)
	{
		int32_t size = 0;

		const bool extended = _operand.modifier != DxbcOperandModifier::None;

		uint32_t token = 0;
		token |=  extended                     ? UINT32_C(0x80000000) : 0;
		token |= (_operand.numAddrModes << 20) & UINT32_C(0x00300000);
		token |= (_operand.addrMode[0]  << 22) & UINT32_C(0x01c00000);
		token |= (_operand.addrMode[1]  << 25) & UINT32_C(0x0e000000);
		token |= (_operand.addrMode[2]  << 28) & UINT32_C(0x70000000);
		token |= (_operand.type         << 12) & UINT32_C(0x000ff000);
		token |= (_operand.mode         <<  2) & UINT32_C(0x0000000c);

		token |= (4 == _operand.num ? 2 : _operand.num) & UINT32_C(0x00000003);
		token |= ( (_operand.modeBits & "\x0f\xff\x03\x00"[_operand.mode]) << 4) & UINT32_C(0x00000ff0);

		size += bx::write(_writer, token, _err);

		if (extended)
		{
			uint32_t extBits = 0
				| ( (_operand.modifier << 6) & UINT32_C(0x00003fc0) )
				| 1 /* 1 == has extended operand modifier */
				;
			size += bx::write(_writer, extBits, _err);
		}

		switch (_operand.type)
		{
		case DxbcOperandType::Imm32:
			for (uint32_t ii = 0; ii < _operand.num; ++ii)
			{
				size += bx::write(_writer, _operand.un.imm32[ii], _err);
			}
			break;

		case DxbcOperandType::Imm64:
			for (uint32_t ii = 0; ii < _operand.num; ++ii)
			{
				size += bx::write(_writer, _operand.un.imm64[ii], _err);
			}
			break;

		default:
			break;
		}

		for (uint32_t ii = 0, num = bx::uint32_min(_operand.numAddrModes, BX_COUNTOF(_operand.addrMode) ); ii < num; ++ii)
		{
			switch (_operand.addrMode[ii])
			{
			case DxbcOperandAddrMode::Imm32:
				size += bx::write(_writer, _operand.regIndex[ii], _err);
				break;

			case DxbcOperandAddrMode::Reg:
				size += write(_writer, _operand.subOperand[ii], _err);
				break;

			case DxbcOperandAddrMode::RegImm32:
				size += bx::write(_writer, _operand.regIndex[ii], _err);
				size += write(_writer, _operand.subOperand[ii], _err);
				break;

			default:
				BX_CHECK(false, "operand %d addressing mode %d", ii, _operand.addrMode[ii]);
				break;
			}
		}

		return size;
	}

	int32_t read(bx::ReaderI* _reader, DxbcInstruction& _instruction, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token, _err);

		// 0       1       2       3
		// 76543210765432107654321076543210
		// elllllll.............ooooooooooo
		// ^^                   ^----------- opcode
		// |+------------------------------- length
		// +-------------------------------- extended

		_instruction.opcode = DxbcOpcode::Enum( (token & UINT32_C(0x000007ff) )      );
		_instruction.length =          uint8_t( (token & UINT32_C(0x7f000000) ) >> 24);
		bool extended       =              0 != (token & UINT32_C(0x80000000) );

		_instruction.srv     = DxbcResourceDim::Unknown;
		_instruction.samples = 0;

		_instruction.shadow = false;
		_instruction.mono   = false;

		_instruction.allowRefactoring = false;
		_instruction.fp64             = false;
		_instruction.earlyDepth       = false;
		_instruction.enableBuffers    = false;
		_instruction.skipOptimization = false;
		_instruction.enableMinPrecision     = false;
		_instruction.enableDoubleExtensions = false;
		_instruction.enableShaderExtensions = false;

		_instruction.threadsInGroup = false;
		_instruction.sharedMemory   = false;
		_instruction.uavGroup       = false;
		_instruction.uavGlobal      = false;

		_instruction.saturate = false;
		_instruction.testNZ   = false;
		_instruction.retType  = DxbcResourceReturnType::Unused;

		_instruction.customDataClass = DxbcCustomDataClass::Comment;
		_instruction.customData.clear();

		switch (_instruction.opcode)
		{
			case DxbcOpcode::CUSTOMDATA:
				{
					_instruction.customDataClass = DxbcCustomDataClass::Enum( (token & UINT32_C(0xfffff800) ) >> 11);

					_instruction.numOperands = 0;
					size += bx::read(_reader, _instruction.length, _err);
					for (uint32_t ii = 0, num = (_instruction.length-2); ii < num && _err->isOk(); ++ii)
					{
						uint32_t temp;
						size += bx::read(_reader, temp, _err);
						if (_err->isOk() )
						{
							_instruction.customData.push_back(temp);
						}
					}
				}
				return size;

			case DxbcOpcode::DCL_CONSTANT_BUFFER:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........            a...........
				//                     ^------------ Allow refactoring

				_instruction.allowRefactoring = 0 != (token & UINT32_C(0x00000800) );
				break;

			case DxbcOpcode::DCL_GLOBAL_FLAGS:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........     sxmoudfa...........
				//              ^^^^^^^^------------ Allow refactoring
				//              ||||||+------------- FP64
				//              |||||+-------------- Force early depth/stencil
				//              ||||+--------------- Enable raw and structured buffers
				//              |||+---------------- Skip optimizations
				//              ||+----------------- Enable minimum precision
				//              |+------------------ Enable double extension
				//              +------------------- Enable shader extension

				_instruction.allowRefactoring       = 0 != (token & UINT32_C(0x00000800) );
				_instruction.fp64                   = 0 != (token & UINT32_C(0x00001000) );
				_instruction.earlyDepth             = 0 != (token & UINT32_C(0x00002000) );
				_instruction.enableBuffers          = 0 != (token & UINT32_C(0x00004000) );
				_instruction.skipOptimization       = 0 != (token & UINT32_C(0x00008000) );
				_instruction.enableMinPrecision     = 0 != (token & UINT32_C(0x00010000) );
				_instruction.enableDoubleExtensions = 0 != (token & UINT32_C(0x00020000) );
				_instruction.enableShaderExtensions = 0 != (token & UINT32_C(0x00040000) );
				break;

			case DxbcOpcode::DCL_INPUT_PS:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........        iiiii...........
				//                 ^---------------- Interploation

				_instruction.interpolation = DxbcInterpolation::Enum( (token & UINT32_C(0x0000f800) ) >> 11);
				break;

			case DxbcOpcode::DCL_RESOURCE:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........ sssssssrrrrr...........
				//          ^      ^---------------- SRV
				//          +----------------------- MSAA samples

				_instruction.srv     = DxbcResourceDim::Enum( (token & UINT32_C(0x0000f800) ) >> 11);
				_instruction.samples =               uint8_t( (token & UINT32_C(0x007f0000) ) >> 16);
				break;

			case DxbcOpcode::DCL_SAMPLER:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........           ms...........
				//                    ^^------------ Shadow sampler
				//                    +------------- Mono

				_instruction.shadow = 0 != (token & UINT32_C(0x00000800) );
				_instruction.mono   = 0 != (token & UINT32_C(0x00001000) );
				break;

			case DxbcOpcode::SYNC:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........         gust...........
				//                  ^^^^------------ Threads in group
				//                  ||+------------- Shared memory
				//                  |+-------------- UAV group
				//                  +--------------- UAV global

				_instruction.threadsInGroup = 0 != (token & UINT32_C(0x00000800) );
				_instruction.sharedMemory   = 0 != (token & UINT32_C(0x00001000) );
				_instruction.uavGroup       = 0 != (token & UINT32_C(0x00002000) );
				_instruction.uavGlobal      = 0 != (token & UINT32_C(0x00004000) );
				break;

			default:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// ........ ppppn    stt...........
				//          ^   ^    ^^------------- Resource info return type
				//          |   |    +-------------- Saturate
				//          |   +------------------- Test not zero
				//          +----------------------- Precise mask

				_instruction.retType  = DxbcResourceReturnType::Enum( (token & UINT32_C(0x00001800) ) >> 11);
				_instruction.saturate =                          0 != (token & UINT32_C(0x00002000) );
				_instruction.testNZ   =                          0 != (token & UINT32_C(0x00040000) );
//				_instruction.precise  =              uint8_t( (token & UINT32_C(0x00780000) ) >> 19);
				break;
		}

		_instruction.extended[0] = DxbcInstruction::ExtendedType::Count;
		for (uint32_t ii = 0; extended; ++ii)
		{
			// 0       1       2       3
			// 76543210765432107654321076543210
			// e..........................ttttt
			// ^                          ^
			// |                          +----- type
			// +-------------------------------- extended

			uint32_t extBits;
			size += bx::read(_reader, extBits, _err);
			extended = 0 != (extBits & UINT32_C(0x80000000) );
			_instruction.extended[ii  ] = DxbcInstruction::ExtendedType::Enum(extBits & UINT32_C(0x0000001f) );
			_instruction.extended[ii+1] = DxbcInstruction::ExtendedType::Count;

			switch (_instruction.extended[ii])
			{
			case DxbcInstruction::ExtendedType::SampleControls:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .          zzzzyyyyxxxx    .....
				//            ^   ^   ^
				//            |   |   +------------- x
				//            |   +----------------- y
				//            +--------------------- z

				_instruction.sampleOffsets[0] = uint8_t( (extBits & UINT32_C(0x00001e00) ) >>  9);
				_instruction.sampleOffsets[1] = uint8_t( (extBits & UINT32_C(0x0001e000) ) >> 13);
				_instruction.sampleOffsets[2] = uint8_t( (extBits & UINT32_C(0x001e0000) ) >> 17);
				break;

			case DxbcInstruction::ExtendedType::ResourceDim:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .                          .....
				//

				_instruction.resourceTarget = uint8_t( (extBits & UINT32_C(0x000003e0) ) >>  6);
				_instruction.resourceStride = uint8_t( (extBits & UINT32_C(0x0000f800) ) >> 11);
				break;

			case DxbcInstruction::ExtendedType::ResourceReturnType:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .          3333222211110000.....
				//            ^   ^   ^
				//            |   |   +------------- x
				//            |   +----------------- y
				//            +--------------------- z

				_instruction.resourceReturnTypes[0] = DxbcResourceReturnType::Enum( (extBits & UINT32_C(0x000001e0) ) >>   6);
				_instruction.resourceReturnTypes[1] = DxbcResourceReturnType::Enum( (extBits & UINT32_C(0x00001e00) ) >>   9);
				_instruction.resourceReturnTypes[2] = DxbcResourceReturnType::Enum( (extBits & UINT32_C(0x0001e000) ) >>  13);
				_instruction.resourceReturnTypes[3] = DxbcResourceReturnType::Enum( (extBits & UINT32_C(0x001e0000) ) >>  17);
				break;

			default:
				break;
			}
		}

		switch (_instruction.opcode)
		{
			case DxbcOpcode::DCL_FUNCTION_TABLE:
				{
					uint32_t tableId;
					size += read(_reader, tableId, _err);

					uint32_t num;
					size += read(_reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						uint32_t bodyId;
						size += read(_reader, bodyId, _err);
					}
				}
				break;

			case DxbcOpcode::DCL_INTERFACE:
				{
					uint32_t interfaceId;
					size += read(_reader, interfaceId, _err);

					uint32_t num;
					size += read(_reader, num, _err);

					BX_CHECK(false, "not implemented.");
				}
				break;

			default:
				break;
		};

		uint32_t currOp = 0;

		const DxbcOpcodeInfo& info = s_dxbcOpcodeInfo[_instruction.opcode];
		_instruction.numOperands = info.numOperands;
		switch (info.numOperands)
		{
		case 6: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 5: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 4: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 3: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 2: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 1: size += read(_reader, _instruction.operand[currOp++], _err); BX_FALLTHROUGH;
		case 0:
			if (0 < info.numValues)
			{
				size += read(_reader, _instruction.value, info.numValues*sizeof(uint32_t), _err);
			}
			break;

		default:
			BX_CHECK(false, "Instruction %s with invalid number of operands %d (numValues %d)."
					, getName(_instruction.opcode)
					, info.numOperands
					, info.numValues
					);
			break;
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const DxbcInstruction& _instruction, bx::Error* _err)
	{
		uint32_t token = 0;
		token |= (_instruction.opcode        ) & UINT32_C(0x000007ff);
		token |= (_instruction.length   << 24) & UINT32_C(0x7f000000);

		token |=  DxbcInstruction::ExtendedType::Count != _instruction.extended[0]
			? UINT32_C(0x80000000)
			: 0
			;

		int32_t size =0;

		switch (_instruction.opcode)
		{
			case DxbcOpcode::CUSTOMDATA:
				{
					token &= UINT32_C(0x000007ff);
					token |= _instruction.customDataClass << 11;

					size += bx::write(_writer, token);

					uint32_t len = uint32_t(_instruction.customData.size()*sizeof(uint32_t) );
					size += bx::write(_writer, len/4+2, _err);
					size += bx::write(_writer, _instruction.customData.data(), len, _err);
				}
				return size;

			case DxbcOpcode::DCL_CONSTANT_BUFFER:
				token |= _instruction.allowRefactoring ? UINT32_C(0x00000800) : 0;
				break;

			case DxbcOpcode::DCL_GLOBAL_FLAGS:
				token |= _instruction.allowRefactoring       ? UINT32_C(0x00000800) : 0;
				token |= _instruction.fp64                   ? UINT32_C(0x00001000) : 0;
				token |= _instruction.earlyDepth             ? UINT32_C(0x00002000) : 0;
				token |= _instruction.enableBuffers          ? UINT32_C(0x00004000) : 0;
				token |= _instruction.skipOptimization       ? UINT32_C(0x00008000) : 0;
				token |= _instruction.enableMinPrecision     ? UINT32_C(0x00010000) : 0;
				token |= _instruction.enableDoubleExtensions ? UINT32_C(0x00020000) : 0;
				token |= _instruction.enableShaderExtensions ? UINT32_C(0x00040000) : 0;
				break;

			case DxbcOpcode::DCL_INPUT_PS:
				token |= (_instruction.interpolation << 11) & UINT32_C(0x0000f800);
				break;

			case DxbcOpcode::DCL_RESOURCE:
				token |= (_instruction.srv     << 11) & UINT32_C(0x0000f800);
				token |= (_instruction.samples << 16) & UINT32_C(0x007f0000);
				break;

			case DxbcOpcode::DCL_SAMPLER:
				token |= _instruction.shadow ? (0x00000800) : 0;
				token |= _instruction.mono   ? (0x00001000) : 0;
				break;

			case DxbcOpcode::SYNC:
				token |= _instruction.threadsInGroup ? UINT32_C(0x00000800) : 0;
				token |= _instruction.sharedMemory   ? UINT32_C(0x00001000) : 0;
				token |= _instruction.uavGroup       ? UINT32_C(0x00002000) : 0;
				token |= _instruction.uavGlobal      ? UINT32_C(0x00004000) : 0;
				break;

			default:
				token |= (_instruction.retType << 11) & UINT32_C(0x00001800);
				token |=  _instruction.saturate ? UINT32_C(0x00002000) : 0;
				token |=  _instruction.testNZ   ? UINT32_C(0x00040000) : 0;
//				_instruction.precise  =              uint8_t( (token & UINT32_C(0x00780000) ) >> 19);
				break;
		}

		size += bx::write(_writer, token);

		for (uint32_t ii = 0; _instruction.extended[ii] != DxbcInstruction::ExtendedType::Count; ++ii)
		{
			// 0       1       2       3
			// 76543210765432107654321076543210
			// e..........................ttttt
			// ^                          ^
			// |                          +----- type
			// +-------------------------------- extended

			token = _instruction.extended[ii+1] == DxbcInstruction::ExtendedType::Count
				? 0
				: UINT32_C(0x80000000)
				;
			token |= uint8_t(_instruction.extended[ii]);

			switch (_instruction.extended[ii])
			{
			case DxbcInstruction::ExtendedType::SampleControls:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .          zzzzyyyyxxxx    .....
				//            ^   ^   ^
				//            |   |   +------------- x
				//            |   +----------------- y
				//            +--------------------- z

				token |= (uint32_t(_instruction.sampleOffsets[0]) <<  9) & UINT32_C(0x00001e00);
				token |= (uint32_t(_instruction.sampleOffsets[1]) << 13) & UINT32_C(0x0001e000);
				token |= (uint32_t(_instruction.sampleOffsets[2]) << 17) & UINT32_C(0x001e0000);
				break;

			case DxbcInstruction::ExtendedType::ResourceDim:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .                          .....
				//

				token |= (uint32_t(_instruction.resourceTarget <<  6) & UINT32_C(0x000003e0) );
				token |= (uint32_t(_instruction.resourceStride << 11) & UINT32_C(0x0000f800) );
				break;

			case DxbcInstruction::ExtendedType::ResourceReturnType:
				// 0       1       2       3
				// 76543210765432107654321076543210
				// .          3333222211110000.....
				//            ^   ^   ^
				//            |   |   +------------- x
				//            |   +----------------- y
				//            +--------------------- z

				token |= (uint32_t(_instruction.resourceReturnTypes[0]) <<  6) & UINT32_C(0x000001e0);
				token |= (uint32_t(_instruction.resourceReturnTypes[1]) <<  9) & UINT32_C(0x00001e00);
				token |= (uint32_t(_instruction.resourceReturnTypes[2]) << 13) & UINT32_C(0x0001e000);
				token |= (uint32_t(_instruction.resourceReturnTypes[3]) << 17) & UINT32_C(0x001e0000);
				break;

			default:
				break;
			}

			size += bx::write(_writer, token, _err);
		}

		for (uint32_t ii = 0; ii < _instruction.numOperands; ++ii)
		{
			size += write(_writer, _instruction.operand[ii], _err);
		}

		const DxbcOpcodeInfo& info = s_dxbcOpcodeInfo[_instruction.opcode];
		if (0 < info.numValues)
		{
			size += bx::write(_writer, _instruction.value, info.numValues*sizeof(uint32_t), _err);
		}

		return size;
	}

	int32_t toString(char* _out, int32_t _size, DxbcOperandMode::Enum _mode, uint8_t _modeBits)
	{
		int32_t size = 0;

		switch (_mode)
		{
		case DxbcOperandMode::Mask:
			if (0xf > _modeBits
			&&  0   < _modeBits)
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, ".%s%s%s%s"
							, 0 == (_modeBits & 1) ? "" : "x"
							, 0 == (_modeBits & 2) ? "" : "y"
							, 0 == (_modeBits & 4) ? "" : "z"
							, 0 == (_modeBits & 8) ? "" : "w"
							);
			}
			break;

		case DxbcOperandMode::Swizzle:
			if (0xe4 != _modeBits)
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, ".%c%c%c%c"
							, "xyzw"[(_modeBits   )&0x3]
							, "xyzw"[(_modeBits>>2)&0x3]
							, "xyzw"[(_modeBits>>4)&0x3]
							, "xyzw"[(_modeBits>>6)&0x3]
							);
			}
			break;

		case DxbcOperandMode::Scalar:
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, ".%c"
						, "xyzw"[_modeBits]
						);
			break;

		default:
			break;
		}

		return size;
	}

	int32_t toString(char* _out, int32_t _size, const DxbcInstruction& _instruction)
	{
		int32_t size = 0;

		switch (_instruction.opcode)
		{
		case DxbcOpcode::CUSTOMDATA:
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s"
						, s_dxbcCustomDataClass[_instruction.customDataClass]
						);
			break;

		case DxbcOpcode::IF:
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s%s"
						, getName(_instruction.opcode)
						, _instruction.testNZ ? "_nz"  : "_z"
						);
			break;

		default:
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s%s%s"
						, getName(_instruction.opcode)
						, _instruction.saturate ? "_sat" : ""
						, _instruction.testNZ   ? "_nz"  : ""
						);
			break;
		}

		if (DxbcResourceDim::Unknown != _instruction.srv)
		{
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, " %s<%x>"
						, s_dxbcSrvType[_instruction.srv]
						, _instruction.value[0]
						);
		}
		else if (0 < s_dxbcOpcodeInfo[_instruction.opcode].numValues)
		{
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, " %d"
						, _instruction.value[0]
						);
		}

		for (uint32_t ii = 0; ii < _instruction.numOperands; ++ii)
		{
			const DxbcOperand& operand = _instruction.operand[ii];

			const bool array = false
				|| 1 < operand.numAddrModes
				|| DxbcOperandAddrMode::Imm32 != operand.addrMode[0]
				;

			const char* preOperand  = "";
			const char* postOperand = "";

			switch (operand.modifier)
			{
			case DxbcOperandModifier::Neg:    preOperand =     "-"; postOperand =  ""; break;
			case DxbcOperandModifier::Abs:    preOperand =  "abs("; postOperand = ")"; break;
			case DxbcOperandModifier::AbsNeg: preOperand = "-abs("; postOperand = ")"; break;
			default: break;
			}

			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s%s%s"
						, 0 == ii ? " " : ", "
						, preOperand
						, s_dxbcOperandType[operand.type]
						);

			switch (operand.type)
			{
			case DxbcOperandType::Imm32:
			case DxbcOperandType::Imm64:
				for (uint32_t jj = 0; jj < operand.num; ++jj)
				{
					union { uint32_t i; float f; } cast = { operand.un.imm32[jj] };
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
								, "%s%f"
								, 0 == jj ? "(" : ", "
								, cast.f
								);
				}

				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, ")"
							);
				break;

			default:
				break;
			}

			const uint32_t first = false
				|| DxbcOperandType::ImmConstantBuffer == operand.type
				|| DxbcOperandAddrMode::RegImm32      == operand.addrMode[0]
				? 0 : 1
				;
			if (0 == first)
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "["
							);
			}
			else
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%d%s"
							, operand.regIndex[0]
							, array ? "[" : ""
							);
			}

			for (uint32_t jj = first, num = bx::uint32_min(operand.numAddrModes, BX_COUNTOF(operand.addrMode) ); jj < num; ++jj)
			{
				switch (operand.addrMode[jj])
				{
				case DxbcOperandAddrMode::Imm32:
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
								, "%d"
								, operand.regIndex[jj]
								);
					break;

				case DxbcOperandAddrMode::Reg:
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
								, "%s%d"
								, s_dxbcOperandType[operand.subOperand[jj].type]
								, operand.subOperand[jj].regIndex
								);
					size += toString(&_out[size], bx::uint32_imax(0, _size-size)
								, DxbcOperandMode::Enum(operand.subOperand[jj].mode)
								, operand.subOperand[jj].modeBits
								);
					break;

				case DxbcOperandAddrMode::RegImm32:
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
								, "%d + %s%d"
								, operand.regIndex[jj]
								, s_dxbcOperandType[operand.subOperand[jj].type]
								, operand.subOperand[jj].regIndex
								);
					size += toString(&_out[size], bx::uint32_imax(0, _size-size)
								, DxbcOperandMode::Enum(operand.subOperand[jj].mode)
								, operand.subOperand[jj].modeBits
								);
					break;

				default:
					size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size), "???");
					break;
				}
			}

			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s"
						, array ? "]" : ""
						);

			size += toString(&_out[size], bx::uint32_imax(0, _size-size), operand.mode, operand.modeBits);

			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, "%s"
						, postOperand
						);
		}

		if (_instruction.opcode == DxbcOpcode::DCL_CONSTANT_BUFFER
		&&  _instruction.allowRefactoring)
		{
			size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
						, ", dynamicIndexed"
						);
		}

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, DxbcSignature& _signature, bx::Error* _err)
	{
		int32_t size = 0;

		int64_t offset = bx::seek(_reader);

		uint32_t num;
		size += bx::read(_reader, num, _err);
		size += bx::read(_reader, _signature.key, _err);

		for (uint32_t ii = 0; ii < num; ++ii)
		{
			DxbcSignature::Element element;

			uint32_t nameOffset;
			size += bx::read(_reader, nameOffset);

			char name[DXBC_MAX_NAME_STRING];
			readString(_reader, offset + nameOffset, name, DXBC_MAX_NAME_STRING, _err);
			element.name = name;

			size += bx::read(_reader, element.semanticIndex, _err);
			size += bx::read(_reader, element.valueType, _err);
			size += bx::read(_reader, element.componentType, _err);
			size += bx::read(_reader, element.registerIndex, _err);
			size += bx::read(_reader, element.mask, _err);
			size += bx::read(_reader, element.readWriteMask, _err);
			size += bx::read(_reader, element.stream, _err);

			// padding
			uint8_t padding;
			size += bx::read(_reader, padding, _err);

			_signature.elements.push_back(element);
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const DxbcSignature& _signature, bx::Error* _err)
	{
		int32_t size = 0;

		const uint32_t num = uint32_t(_signature.elements.size() );
		size += bx::write(_writer, num, _err);
		size += bx::write(_writer, _signature.key, _err);

		typedef stl::unordered_map<stl::string, uint32_t> NameOffsetMap;
		NameOffsetMap nom;

		const uint8_t pad = 0;
		uint32_t nameOffset = num * 24 + 8;
		for (uint32_t ii = 0; ii < num; ++ii)
		{
			const DxbcSignature::Element& element = _signature.elements[ii];

			NameOffsetMap::iterator it = nom.find(element.name);
			if (it == nom.end() )
			{
				nom.insert(stl::make_pair(element.name, nameOffset) );
				size += bx::write(_writer, nameOffset, _err);
				nameOffset += uint32_t(element.name.size() + 1);
			}
			else
			{
				size += bx::write(_writer, it->second);
			}

			size += bx::write(_writer, element.semanticIndex, _err);
			size += bx::write(_writer, element.valueType, _err);
			size += bx::write(_writer, element.componentType, _err);
			size += bx::write(_writer, element.registerIndex, _err);
			size += bx::write(_writer, element.mask, _err);
			size += bx::write(_writer, element.readWriteMask, _err);
			size += bx::write(_writer, element.stream, _err);
			size += bx::write(_writer, pad, _err);
		}

		uint32_t len = 0;
		for (uint32_t ii = 0; ii < num; ++ii)
		{
			const DxbcSignature::Element& element = _signature.elements[ii];
			NameOffsetMap::iterator it = nom.find(element.name);
			if (it != nom.end() )
			{
				nom.erase(it);
				size += bx::write(_writer, element.name.c_str(), uint32_t(element.name.size() + 1), _err);
				len  += uint32_t(element.name.size() + 1);
			}
		}

		// align 4 bytes
		size += bx::writeRep(_writer, 0xab, (len+3)/4*4 - len, _err);

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, DxbcShader& _shader, bx::Error* _err)
	{
		int32_t size = 0;

		size += bx::read(_reader, _shader.version, _err);

		uint32_t bcLength;
		size += bx::read(_reader, bcLength, _err);

		uint32_t len = (bcLength-2)*sizeof(uint32_t);
		_shader.byteCode.resize(len);
		size += bx::read(_reader, _shader.byteCode.data(), len, _err);

		return size;
	}

	int32_t write(bx::WriterI* _writer, const DxbcShader& _shader, bx::Error* _err)
	{
		const uint32_t len = uint32_t(_shader.byteCode.size() );
		const uint32_t bcLength = len / sizeof(uint32_t) + 2;

		int32_t size = 0;
		size += bx::write(_writer, _shader.version, _err);
		size += bx::write(_writer, bcLength, _err);
		size += bx::write(_writer, _shader.byteCode.data(), len, _err);

		return size;
	}

#define DXBC_CHUNK_SHADER           BX_MAKEFOURCC('S', 'H', 'D', 'R')
#define DXBC_CHUNK_SHADER_EX        BX_MAKEFOURCC('S', 'H', 'E', 'X')

#define DXBC_CHUNK_INPUT_SIGNATURE  BX_MAKEFOURCC('I', 'S', 'G', 'N')
#define DXBC_CHUNK_OUTPUT_SIGNATURE BX_MAKEFOURCC('O', 'S', 'G', 'N')

	int32_t read(bx::ReaderSeekerI* _reader, DxbcContext& _dxbc, bx::Error* _err)
	{
		int32_t size = 0;
		size += bx::read(_reader, _dxbc.header, _err);
		_dxbc.shader.shex = false;
		_dxbc.shader.aon9 = false;

		for (uint32_t ii = 0; ii < _dxbc.header.numChunks; ++ii)
		{
			bx::seek(_reader, sizeof(DxbcContext::Header) + ii*sizeof(uint32_t), bx::Whence::Begin);

			uint32_t chunkOffset;
			size += bx::read(_reader, chunkOffset, _err);

			bx::seek(_reader, chunkOffset, bx::Whence::Begin);

			uint32_t fourcc;
			size += bx::read(_reader, fourcc, _err);

			uint32_t chunkSize;
			size += bx::read(_reader, chunkSize, _err);

			switch (fourcc)
			{
			case DXBC_CHUNK_SHADER_EX:
				_dxbc.shader.shex = true;
				BX_FALLTHROUGH;

			case DXBC_CHUNK_SHADER:
				size += read(_reader, _dxbc.shader, _err);
				break;

			case BX_MAKEFOURCC('I', 'S', 'G', '1'):
			case DXBC_CHUNK_INPUT_SIGNATURE:
				size += read(_reader, _dxbc.inputSignature, _err);
				break;

			case BX_MAKEFOURCC('O', 'S', 'G', '1'):
			case BX_MAKEFOURCC('O', 'S', 'G', '5'):
			case DXBC_CHUNK_OUTPUT_SIGNATURE:
				size += read(_reader, _dxbc.outputSignature, _err);
				break;

			case BX_MAKEFOURCC('A', 'o', 'n', '9'): // Contains DX9BC for feature level 9.x (*s_4_0_level_9_*) shaders.
				_dxbc.shader.aon9 = true;
				break;

			case BX_MAKEFOURCC('I', 'F', 'C', 'E'): // Interface.
			case BX_MAKEFOURCC('R', 'D', 'E', 'F'): // Resource definition.
			case BX_MAKEFOURCC('S', 'D', 'G', 'B'): // Shader debugging info (old).
			case BX_MAKEFOURCC('S', 'P', 'D', 'B'): // Shader debugging info (new).
			case BX_MAKEFOURCC('S', 'F', 'I', '0'): // ?
			case BX_MAKEFOURCC('S', 'T', 'A', 'T'): // Statistics.
			case BX_MAKEFOURCC('P', 'C', 'S', 'G'): // Patch constant signature.
			case BX_MAKEFOURCC('P', 'S', 'O', '1'): // Pipeline State Object 1
			case BX_MAKEFOURCC('P', 'S', 'O', '2'): // Pipeline State Object 2
			case BX_MAKEFOURCC('X', 'N', 'A', 'P'): // ?
			case BX_MAKEFOURCC('X', 'N', 'A', 'S'): // ?
				size += chunkSize;
				break;

			default:
				size += chunkSize;
				BX_CHECK(false, "UNKNOWN FOURCC %c%c%c%c %d"
					, ( (char*)&fourcc)[0]
					, ( (char*)&fourcc)[1]
					, ( (char*)&fourcc)[2]
					, ( (char*)&fourcc)[3]
					, size
					);
				break;
			}
		}

		return size;
	}

	int32_t write(bx::WriterSeekerI* _writer, const DxbcContext& _dxbc, bx::Error* _err)
	{
		int32_t size = 0;

		int64_t dxbcOffset = bx::seek(_writer);
		size += bx::write(_writer, DXBC_CHUNK_HEADER);

		size += bx::writeRep(_writer, 0, 16, _err);

		size += bx::write(_writer, UINT32_C(1), _err);

		int64_t sizeOffset = bx::seek(_writer);
		size += bx::writeRep(_writer, 0, 4, _err);

		uint32_t numChunks = 3;
		size += bx::write(_writer, numChunks, _err);

		int64_t chunksOffsets = bx::seek(_writer);
		size += bx::writeRep(_writer, 0, numChunks*sizeof(uint32_t), _err);

		uint32_t chunkOffset[3];
		uint32_t chunkSize[3];

		chunkOffset[0] = uint32_t(bx::seek(_writer) - dxbcOffset);
		size += write(_writer, DXBC_CHUNK_INPUT_SIGNATURE, _err);
		size += write(_writer, UINT32_C(0), _err);
		chunkSize[0] = write(_writer, _dxbc.inputSignature, _err);

		chunkOffset[1] = uint32_t(bx::seek(_writer) - dxbcOffset);
		size += write(_writer, DXBC_CHUNK_OUTPUT_SIGNATURE, _err);
		size += write(_writer, UINT32_C(0), _err);
		chunkSize[1] = write(_writer, _dxbc.outputSignature, _err);

		chunkOffset[2] = uint32_t(bx::seek(_writer) - dxbcOffset);
		size += write(_writer, _dxbc.shader.shex ? DXBC_CHUNK_SHADER_EX : DXBC_CHUNK_SHADER, _err);
		size += write(_writer, UINT32_C(0), _err);
		chunkSize[2] = write(_writer, _dxbc.shader, _err);

		size += 0
			+ chunkSize[0]
			+ chunkSize[1]
			+ chunkSize[2]
			;

		int64_t eof = bx::seek(_writer);

		bx::seek(_writer, sizeOffset, bx::Whence::Begin);
		bx::write(_writer, size, _err);

		bx::seek(_writer, chunksOffsets, bx::Whence::Begin);
		bx::write(_writer, chunkOffset, sizeof(chunkOffset), _err);

		for (uint32_t ii = 0; ii < BX_COUNTOF(chunkOffset); ++ii)
		{
			bx::seek(_writer, chunkOffset[ii]+4, bx::Whence::Begin);
			bx::write(_writer, chunkSize[ii], _err);
		}

		bx::seek(_writer, eof, bx::Whence::Begin);

		return size;
	}

	void parse(const DxbcShader& _src, DxbcParseFn _fn, void* _userData, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			DxbcInstruction instruction;
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

	void filter(DxbcShader& _dst, const DxbcShader& _src, DxbcFilterFn _fn, void* _userData, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		bx::MemoryBlock mb(g_allocator);
		bx::MemoryWriter writer(&mb);

		int32_t total = 0;

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			DxbcInstruction instruction;
			uint32_t size = read(&reader, instruction, _err);
			BX_CHECK(size/4 == instruction.length, "read %d, expected %d", size/4, instruction.length); BX_UNUSED(size);

			_fn(instruction, _userData);

			bx::SizerWriter sw;
			uint32_t length = instruction.length;
			instruction.length = uint32_t(write(&sw, instruction, _err)/4);

			total += write(&writer, instruction, _err);
			token += length;
		}

		uint8_t* data = (uint8_t*)mb.more();
		_dst.byteCode.resize(total);
		bx::memCopy(_dst.byteCode.data(), data, total);
	}

} // namespace bgfx

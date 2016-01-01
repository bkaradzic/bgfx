/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_DXBC_H
#define BGFX_SHADER_DXBC_H

#include <bx/readerwriter.h>

namespace bgfx
{
	struct DxbcOpcode
	{
		enum Enum
		{
			ADD,
			AND,
			BREAK,
			BREAKC,
			CALL,
			CALLC,
			CASE,
			CONTINUE,
			CONTINUEC,
			CUT,
			DEFAULT,
			DERIV_RTX,
			DERIV_RTY,
			DISCARD,
			DIV,
			DP2,
			DP3,
			DP4,
			ELSE,
			EMIT,
			EMITTHENCUT,
			ENDIF,
			ENDLOOP,
			ENDSWITCH,
			EQ,
			EXP,
			FRC,
			FTOI,
			FTOU,
			GE,
			IADD,
			IF,
			IEQ,
			IGE,
			ILT,
			IMAD,
			IMAX,
			IMIN,
			IMUL,
			INE,
			INEG,
			ISHL,
			ISHR,
			ITOF,
			LABEL,
			LD,
			LD_MS,
			LOG,
			LOOP,
			LT,
			MAD,
			MIN,
			MAX,
			CUSTOMDATA,
			MOV,
			MOVC,
			MUL,
			NE,
			NOP,
			NOT,
			OR,
			RESINFO,
			RET,
			RETC,
			ROUND_NE,
			ROUND_NI,
			ROUND_PI,
			ROUND_Z,
			RSQ,
			SAMPLE,
			SAMPLE_C,
			SAMPLE_C_LZ,
			SAMPLE_L,
			SAMPLE_D,
			SAMPLE_B,
			SQRT,
			SWITCH,
			SINCOS,
			UDIV,
			ULT,
			UGE,
			UMUL,
			UMAD,
			UMAX,
			UMIN,
			USHR,
			UTOF,
			XOR,
			DCL_RESOURCE,
			DCL_CONSTANT_BUFFER,
			DCL_SAMPLER,
			DCL_INDEX_RANGE,
			DCL_GS_OUTPUT_PRIMITIVE_TOPOLOGY,
			DCL_GS_INPUT_PRIMITIVE,
			DCL_MAX_OUTPUT_VERTEX_COUNT,
			DCL_INPUT,
			DCL_INPUT_SGV,
			DCL_INPUT_SIV,
			DCL_INPUT_PS,
			DCL_INPUT_PS_SGV,
			DCL_INPUT_PS_SIV,
			DCL_OUTPUT,
			DCL_OUTPUT_SGV,
			DCL_OUTPUT_SIV,
			DCL_TEMPS,
			DCL_INDEXABLE_TEMP,
			DCL_GLOBAL_FLAGS,

			UnknownD3D10,
			LOD,
			GATHER4,
			SAMPLE_POS,
			SAMPLE_INFO,

			UnknownD3D10_1,
			HS_DECLS,
			HS_CONTROL_POINT_PHASE,
			HS_FORK_PHASE,
			HS_JOIN_PHASE,
			EMIT_STREAM,
			CUT_STREAM,
			EMITTHENCUT_STREAM,
			INTERFACE_CALL,
			BUFINFO,
			DERIV_RTX_COARSE,
			DERIV_RTX_FINE,
			DERIV_RTY_COARSE,
			DERIV_RTY_FINE,
			GATHER4_C,
			GATHER4_PO,
			GATHER4_PO_C,
			RCP,
			F32TOF16,
			F16TOF32,
			UADDC,
			USUBB,
			COUNTBITS,
			FIRSTBIT_HI,
			FIRSTBIT_LO,
			FIRSTBIT_SHI,
			UBFE,
			IBFE,
			BFI,
			BFREV,
			SWAPC,
			DCL_STREAM,
			DCL_FUNCTION_BODY,
			DCL_FUNCTION_TABLE,
			DCL_INTERFACE,
			DCL_INPUT_CONTROL_POINT_COUNT,
			DCL_OUTPUT_CONTROL_POINT_COUNT,
			DCL_TESS_DOMAIN,
			DCL_TESS_PARTITIONING,
			DCL_TESS_OUTPUT_PRIMITIVE,
			DCL_HS_MAX_TESSFACTOR,
			DCL_HS_FORK_PHASE_INSTANCE_COUNT,
			DCL_HS_JOIN_PHASE_INSTANCE_COUNT,
			DCL_THREAD_GROUP,
			DCL_UNORDERED_ACCESS_VIEW_TYPED,
			DCL_UNORDERED_ACCESS_VIEW_RAW,
			DCL_UNORDERED_ACCESS_VIEW_STRUCTURED,
			DCL_THREAD_GROUP_SHARED_MEMORY_RAW,
			DCL_THREAD_GROUP_SHARED_MEMORY_STRUCTURED,
			DCL_RESOURCE_RAW,
			DCL_RESOURCE_STRUCTURED,
			LD_UAV_TYPED,
			STORE_UAV_TYPED,
			LD_RAW,
			STORE_RAW,
			LD_STRUCTURED,
			STORE_STRUCTURED,
			ATOMIC_AND,
			ATOMIC_OR,
			ATOMIC_XOR,
			ATOMIC_CMP_STORE,
			ATOMIC_IADD,
			ATOMIC_IMAX,
			ATOMIC_IMIN,
			ATOMIC_UMAX,
			ATOMIC_UMIN,
			IMM_ATOMIC_ALLOC,
			IMM_ATOMIC_CONSUME,
			IMM_ATOMIC_IADD,
			IMM_ATOMIC_AND,
			IMM_ATOMIC_OR,
			IMM_ATOMIC_XOR,
			IMM_ATOMIC_EXCH,
			IMM_ATOMIC_CMP_EXCH,
			IMM_ATOMIC_IMAX,
			IMM_ATOMIC_IMIN,
			IMM_ATOMIC_UMAX,
			IMM_ATOMIC_UMIN,
			SYNC,
			DADD,
			DMAX,
			DMIN,
			DMUL,
			DEQ,
			DGE,
			DLT,
			DNE,
			DMOV,
			DMOVC,
			DTOF,
			FTOD,
			EVAL_SNAPPED,
			EVAL_SAMPLE_INDEX,
			EVAL_CENTROID,
			DCL_GS_INSTANCE_COUNT,
			ABORT,
			DEBUG_BREAK,

			UnknownD3D11,
			DDIV,
			DFMA,
			DRCP,
			MSAD,
			DTOI,
			DTOU,
			ITOD,
			UTOD,

			Count
		};
	};

	const char* getName(DxbcOpcode::Enum _opcode);

	struct DxbcBuiltin
	{
		// D3D_NAME
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ff728724%28v=vs.85%29.aspx
		// mesa/src/gallium/state_trackers/d3d1x/d3d1xshader/defs/svs.txt
		enum Enum
		{
			Undefined,
			Position,
			ClipDistance,
			CullDistance,
			RenderTargetArrayIndex,
			ViewportArrayIndex,
			VertexId,
			PrimitiveId,
			InstanceId,
			IsFrontFace,
			SampleIndex,
			FinalQuadUEq0EdgeTessFactor,
			FinalQuadVEq0EdgeTessFactor,
			FinalQuadUEq1EdgeTessFactor,
			FinalQuadVEq1EdgeTessFactor,
			FinalQuadUInsideTessFactor,
			FinalQuadVInsideTessFactor,
			FinalTriUEq0EdgeTessFactor,
			FinalTriVEq0EdgeTessFactor,
			FinalTriWEq0EdgeTessFactor,
			FinalTriInsideTessFactor,
			FinalLineDetailTessFactor,
			FinalLineDensityTessFactor,
			Target = 64,
			Depth,
			Coverage,
			DepthGreaterEqual,
			DepthLessEqual,
			StencilRef,
			InnerCoverage,
		};
	};

	struct DxbcResourceDim
	{
		// D3D_SRV_DIMENSION
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ff728736%28v=vs.85%29.aspx
		// mesa/src/gallium/state_trackers/d3d1x/d3d1xshader/defs/targets.txt
		enum Enum
		{
			Unknown,
			Buffer,
			Texture1D,
			Texture2D,
			Texture2DMS,
			Texture3D,
			TextureCube,
			Texture1DArray,
			Texture2DArray,
			Texture2DMSArray,
			TextureCubearray,
			RawBuffer,
			StructuredBuffer,

			Count
		};
	};

	struct DxbcInterpolation
	{
		enum Enum
		{
			Unknown,
			Constant,
			Linear,
			LinearCentroid,
			LinearNoPerspective,
			LinearNoPerspectiveCentroid,
			LinearSample,
			LinearNoPerspectiveSample,

			Count
		};
	};

	struct DxbcResourceReturnType
	{
		enum Enum
		{
			Unorm,
			Snorm,
			Sint,
			Uint,
			Float,
			Mixed,
			Double,
			Continued,
			Unused,

			Count
		};
	};

	struct DxbcComponentType
	{
		enum Enum
		{
			Unknown,
			Uint32,
			Int32,
			Float,

			Count
		};
	};

	struct DxbcPrecision
	{
		enum Enum
		{
			Default,
			Half,
			Float2_8,
			Reserved,
			Int16,
			Uint16,
			Any16 = 0xf0,
			Any10 = 0xf1,
		};
	};

	struct DxbcOperandType
	{
		enum Enum
		{
			Temp,
			Input,
			Output,
			TempArray,
			Imm32,
			Imm64,
			Sampler,
			Resource,
			ConstantBuffer,
			ImmConstantBuffer,
			Label,
			PrimitiveID,
			OutputDepth,
			Null,
			Rasterizer,
			CoverageMask,
			Stream,
			FunctionBody,
			FunctionTable,
			Interface,
			FunctionInput,
			FunctionOutput,
			OutputControlPointId,
			InputForkInstanceId,
			InputJoinInstanceId,
			InputControlPoint,
			OutputControlPoint,
			InputPatchConstant,
			InputDomainPoint,
			ThisPointer,
			UnorderedAccessView,
			ThreadGroupSharedMemory,
			InputThreadId,
			InputThreadGroupId,
			InputThreadIdInGroup,
			InputCoverageMask,
			InputThreadIdInGroupFlattened,
			InputGsInstanceId,
			OutputDepthGreaterEqual,
			OutputDepthLessEqual,
			CycleCounter,

			Count
		};
	};

	struct DxbcOperandAddrMode
	{
		enum Enum
		{
			Imm32,
			Imm64,
			Reg,
			RegImm32,
			RegImm64,

			Count
		};
	};

	struct DxbcOperandMode
	{
		enum Enum
		{
			Mask,
			Swizzle,
			Scalar,

			Count
		};
	};

	struct DxbcSubOperand
	{
		DxbcOperandType::Enum type;
		uint8_t mode;
		uint8_t modeBits;
		uint8_t num;
		uint8_t numAddrModes;
		uint8_t addrMode;
		uint32_t regIndex;
	};

	struct DxbcOperand
	{
		DxbcOperandType::Enum type;
		DxbcOperandMode::Enum mode;
		uint8_t modeBits;
		uint8_t num;
		bool extended;
		uint32_t extBits;

		uint8_t numAddrModes;
		uint8_t addrMode[3];
		uint32_t regIndex[3];
		DxbcSubOperand subOperand[3];

		union
		{
			uint32_t imm32[4];
			uint64_t imm64[4];
		} un;
	};

	struct DxbcInstruction
	{
		struct ExtendedType
		{
			enum Enum
			{
				Empty,
				SampleControls,
				ResourceDim,
				ResourceReturnType,

				Count
			};
		};

		DxbcOpcode::Enum opcode;
		uint32_t value[3];
		uint32_t length;
		uint8_t numOperands;
		ExtendedType::Enum extended[3];

		//
		DxbcResourceDim::Enum srv;
		uint8_t samples;

		//
		DxbcInterpolation::Enum interpolation;

		//
		bool shadow;
		bool mono;

		//
		bool allowRefactoring;
		bool fp64;
		bool earlyDepth;
		bool enableBuffers;
		bool skipOptimization;
		bool enableMinPrecision;
		bool enableDoubleExtensions;
		bool enableShaderExtensions;

		//
		bool threadsInGroup;
		bool sharedMemory;
		bool uavGroup;
		bool uavGlobal;

		//
		DxbcResourceReturnType::Enum retType;
		bool saturate;
		uint8_t testNZ;

		//
		uint8_t sampleOffsets[3];
		uint8_t resourceTarget;
		uint8_t resourceStride;
		DxbcResourceReturnType::Enum resourceReturnTypes[4];

		DxbcOperand operand[6];
	};

	int32_t read(bx::ReaderI* _reader, DxbcInstruction& _instruction);
	int32_t write(bx::WriterI* _writer, const DxbcInstruction& _instruction);
	int32_t toString(char* _out, int32_t _size, const DxbcInstruction& _instruction);

	struct DxbcSignature
	{
		struct Element
		{
			stl::string name;
			uint32_t semanticIndex;
			DxbcBuiltin::Enum valueType;
			DxbcComponentType::Enum componentType;
			uint32_t registerIndex;
			uint8_t mask;
			uint8_t readWriteMask;
			uint8_t stream;
		};

		uint32_t key;
		stl::vector<Element> elements;
	};

	int32_t read(bx::ReaderSeekerI* _reader, DxbcSignature& _signature);
	int32_t write(bx::WriterI* _writer, const DxbcSignature& _signature);

	struct DxbcShader
	{
		uint32_t version;
		stl::vector<uint8_t> byteCode;
		bool shex;
	};

	int32_t read(bx::ReaderSeekerI* _reader, DxbcShader& _shader);
	int32_t write(bx::WriterI* _writer, const DxbcShader& _shader);

	typedef bool (*DxbcParseFn)(uint32_t _offset, const DxbcInstruction& _instruction, void* _userData);
	void parse(const DxbcShader& _src, DxbcParseFn _fn, void* _userData);

	typedef void (*DxbcFilterFn)(DxbcInstruction& _instruction, void* _userData);
	void filter(DxbcShader& _dst, const DxbcShader& _src, DxbcFilterFn _fn, void* _userData);

	struct DxbcContext
	{
		struct Header
		{
			uint32_t magic;
			uint8_t  hash[16];
			uint32_t version;
			uint32_t size;
			uint32_t numChunks;
		};

		Header header;
		DxbcSignature inputSignature;
		DxbcSignature outputSignature;
		DxbcShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, DxbcContext& _dxbc);
	int32_t write(bx::WriterSeekerI* _writer, const DxbcContext& _dxbc);

	/// Calculate DXBC hash from data.
	void dxbcHash(const void* _data, uint32_t _size, void* _digest);

} // namespace bgfx

#endif // BGFX_SHADER_DXBC_H

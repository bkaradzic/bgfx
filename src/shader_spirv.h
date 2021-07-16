/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_SPIRV_H
#define BGFX_SHADER_SPIRV_H

#include <bx/readerwriter.h>

BX_ERROR_RESULT(BGFX_SHADER_SPIRV_INVALID_HEADER,      BX_MAKEFOURCC('S', 'H', 0, 1) );
BX_ERROR_RESULT(BGFX_SHADER_SPIRV_INVALID_INSTRUCTION, BX_MAKEFOURCC('S', 'H', 0, 2) );

#define SPV_CHUNK_HEADER BX_MAKEFOURCC(0x03, 0x02, 0x23, 0x07)

namespace bgfx
{
	constexpr uint8_t kSpirvVertexBinding   = 0;
	constexpr uint8_t kSpirvFragmentBinding = 1;
	constexpr uint8_t kSpirvBindShift       = 2;
	constexpr uint8_t kSpirvSamplerShift    = 16;

	constexpr uint8_t kSpirvOldVertexBinding    = 0;
	constexpr uint8_t kSpirvOldFragmentBinding  = 48;
	constexpr uint8_t kSpirvOldFragmentShift    = 48;
	constexpr uint8_t kSpirvOldBufferShift      = 16;
	constexpr uint8_t kSpirvOldImageShift       = 32;
	constexpr uint8_t kSpirvOldTextureShift     = 16;

	// Reference(s):
	// - https://web.archive.org/web/20181126035927/https://www.khronos.org/registry/spir-v/specs/1.0/SPIRV.html
	//
	struct SpvOpcode
	{
		enum Enum
		{
			Nop,
			Undef,
			SourceContinued,
			Source,
			SourceExtension,
			Name,
			MemberName,
			String,
			Line,
			Invalid9,
			Extension,
			ExtInstImport,
			ExtInst,
			Invalid13,
			MemoryModel,
			EntryPoint,
			ExecutionMode,
			Capability,
			Invalid18,
			TypeVoid,
			TypeBool,
			TypeInt,
			TypeFloat,
			TypeVector,
			TypeMatrix,
			TypeImage,
			TypeSampler,
			TypeSampledImage,
			TypeArray,
			TypeRuntimeArray,
			TypeStruct,
			TypeOpaque,
			TypePointer,
			TypeFunction,
			TypeEvent,
			TypeDeviceEvent,
			TypeReserveId,
			TypeQueue,
			TypePipe,
			TypeForwardPointer,
			Invalid40,
			ConstantTrue,
			ConstantFalse,
			Constant,
			ConstantComposite,
			ConstantSampler,
			ConstantNull,
			Invalid47,
			SpecConstantTrue,
			SpecConstantFalse,
			SpecConstant,
			SpecConstantComposite,
			SpecConstantOp,
			Invalid53,
			Function,
			FunctionParameter,
			FunctionEnd,
			FunctionCall,
			Invalid58,
			Variable,
			ImageTexelPointer,
			Load,
			Store,
			CopyMemory,
			CopyMemorySized,
			AccessChain,
			InBoundsAccessChain,
			PtrAccessChain,
			ArrayLength,
			GenericPtrMemSemantics,
			InBoundsPtrAccessChain,
			Decorate,
			MemberDecorate,
			DecorationGroup,
			GroupDecorate,
			GroupMemberDecorate,
			Invalid76,
			VectorExtractDynamic,
			VectorInsertDynamic,
			VectorShuffle,
			CompositeConstruct,
			CompositeExtract,
			CompositeInsert,
			CopyObject,
			Transpose,
			Invalid85,
			SampledImage,
			ImageSampleImplicitLod,
			ImageSampleExplicitLod,
			ImageSampleDrefImplicitLod,
			ImageSampleDrefExplicitLod,
			ImageSampleProjImplicitLod,
			ImageSampleProjExplicitLod,
			ImageSampleProjDrefImplicitLod,
			ImageSampleProjDrefExplicitLod,
			ImageFetch,
			ImageGather,
			ImageDrefGather,
			ImageRead,
			ImageWrite,
			Image,
			ImageQueryFormat,
			ImageQueryOrder,
			ImageQuerySizeLod,
			ImageQuerySize,
			ImageQueryLod,
			ImageQueryLevels,
			ImageQuerySamples,
			Invalid108,
			ConvertFToU,
			ConvertFToS,
			ConvertSToF,
			ConvertUToF,
			UConvert,
			SConvert,
			FConvert,
			QuantizeToF16,
			ConvertPtrToU,
			SatConvertSToU,
			SatConvertUToS,
			ConvertUToPtr,
			PtrCastToGeneric,
			GenericCastToPtr,
			GenericCastToPtrExplicit,
			Bitcast,
			Invalid125,
			SNegate,
			FNegate,
			IAdd,
			FAdd,
			ISub,
			FSub,
			IMul,
			FMul,
			UDiv,
			SDiv,
			FDiv,
			UMod,
			SRem,
			SMod,
			FRem,
			FMod,
			VectorTimesScalar,
			MatrixTimesScalar,
			VectorTimesMatrix,
			MatrixTimesVector,
			MatrixTimesMatrix,
			OuterProduct,
			Dot,
			IAddCarry,
			ISubBorrow,
			UMulExtended,
			SMulExtended,
			Invalid153,
			Any,
			All,
			IsNan,
			IsInf,
			IsFinite,
			IsNormal,
			SignBitSet,
			LessOrGreater,
			Ordered,
			Unordered,
			LogicalEqual,
			LogicalNotEqual,
			LogicalOr,
			LogicalAnd,
			LogicalNot,
			Select,
			IEqual,
			INotEqual,
			UGreaterThan,
			SGreaterThan,
			UGreaterThanEqual,
			SGreaterThanEqual,
			ULessThan,
			SLessThan,
			ULessThanEqual,
			SLessThanEqual,
			FOrdEqual,
			FUnordEqual,
			FOrdNotEqual,
			FUnordNotEqual,
			FOrdLessThan,
			FUnordLessThan,
			FOrdGreaterThan,
			FUnordGreaterThan,
			FOrdLessThanEqual,
			FUnordLessThanEqual,
			FOrdGreaterThanEqual,
			FUnordGreaterThanEqual,
			Invalid192,
			Invalid193,
			ShiftRightLogical,
			ShiftRightArithmetic,
			ShiftLeftLogical,
			BitwiseOr,
			BitwiseXor,
			BitwiseAnd,
			Not,
			BitFieldInsert,
			BitFieldSExtract,
			BitFieldUExtract,
			BitReverse,
			BitCount,
			Invalid206,
			DPdx,
			DPdy,
			Fwidth,
			DPdxFine,
			DPdyFine,
			FwidthFine,
			DPdxCoarse,
			DPdyCoarse,
			FwidthCoarse,
			Invalid216,
			Invalid217,
			EmitVertex,
			EndPrimitive,
			EmitStreamVertex,
			EndStreamPrimitive,
			Invalid222,
			Invalid223,
			ControlBarrier,
			MemoryBarrier,
			Invalid226,
			AtomicLoad,
			AtomicStore,
			AtomicExchange,
			AtomicCompareExchange,
			AtomicCompareExchangeWeak,
			AtomicIIncrement,
			AtomicIDecrement,
			AtomicIAdd,
			AtomicISub,
			AtomicSMin,
			AtomicUMin,
			AtomicSMax,
			AtomicUMax,
			AtomicAnd,
			AtomicOr,
			AtomicXor,
			Invalid243,
			Invalid244,
			Phi,
			LoopMerge,
			SelectionMerge,
			Label,
			Branch,
			BranchConditional,
			Switch,
			Kill,
			Return,
			ReturnValue,
			Unreachable,
			LifetimeStart,
			LifetimeStop,
			Invalid258,
			GroupAsyncCopy,
			GroupWaitEvents,
			GroupAll,
			GroupAny,
			GroupBroadcast,
			GroupIAdd,
			GroupFAdd,
			GroupFMin,
			GroupUMin,
			GroupSMin,
			GroupFMax,
			GroupUMax,
			GroupSMax,
			Invalid272,
			Invalid273,
			ReadPipe,
			WritePipe,
			ReservedReadPipe,
			ReservedWritePipe,
			ReserveReadPipePackets,
			ReserveWritePipePackets,
			CommitReadPipe,
			CommitWritePipe,
			IsValidReserveId,
			GetNumPipePackets,
			GetMaxPipePackets,
			GroupReserveReadPipePackets,
			GroupReserveWritePipePackets,
			GroupCommitReadPipe,
			GroupCommitWritePipe,
			Invalid289,
			Invalid290,
			EnqueueMarker,
			EnqueueKernel,
			GetKernelNDrangeSubGroupCount,
			GetKernelNDrangeMaxSubGroupSize,
			GetKernelWorkGroupSize,
			GetKernelPreferredWorkGroupSizeMultiple,
			RetainEvent,
			ReleaseEvent,
			CreateUserEvent,
			IsValidEvent,
			SetUserEventStatus,
			CaptureEventProfilingInfo,
			GetDefaultQueue,
			BuildNDRange,
			ImageSparseSampleImplicitLod,
			ImageSparseSampleExplicitLod,
			ImageSparseSampleDrefImplicitLod,
			ImageSparseSampleDrefExplicitLod,
			ImageSparseSampleProjImplicitLod,
			ImageSparseSampleProjExplicitLod,
			ImageSparseSampleProjDrefImplicitLod,
			ImageSparseSampleProjDrefExplicitLod,
			ImageSparseFetch,
			ImageSparseGather,
			ImageSparseDrefGather,
			ImageSparseTexelsResident,
			NoLine,
			AtomicFlagTestAndSet,
			AtomicFlagClear,
			ImageSparseRead,

			Count
		};
	};

	const char* getName(SpvOpcode::Enum _opcode);

	struct SpvBuiltin
	{
		enum Enum
		{
			Position,
			PointSize,
			ClipDistance,
			CullDistance,
			VertexId,
			InstanceId,
			PrimitiveId,
			InvocationId,
			Layer,
			ViewportIndex,
			TessLevelOuter,
			TessLevelInner,
			TessCoord,
			PatchVertices,
			FragCoord,
			PointCoord,
			FrontFacing,
			SampleId,
			SamplePosition,
			SampleMask,
			FragDepth,
			HelperInvocation,
			NumWorkgroups,
			WorkgroupSize,
			WorkgroupId,
			LocalInvocationId,
			GlobalInvocationId,
			LocalInvocationIndex,
			WorkDim,
			GlobalSize,
			EnqueuedWorkgroupSize,
			GlobalOffset,
			GlobalLinearId,
			SubgroupSize,
			SubgroupMaxSize,
			NumSubgroups,
			NumEnqueuedSubgroups,
			SubgroupId,
			SubgroupLocalInvocationId,
			VertexIndex,
			InstanceIndex,

			Count
		};
	};

	const char* getName(SpvBuiltin::Enum _enum);

	struct SpvExecutionModel
	{
		enum Enum
		{
			Vertex,
			TessellationControl,
			TessellationEvaluation,
			Geometry,
			Fragment,
			GLCompute,
			Kernel,

			Count
		};
	};

	struct SpvAddressingModel
	{
		enum Enum
		{
			Logical,
			Physical32,
			Physical64,

			Count
		};
	};

	struct SpvMemoryModel
	{
		enum Enum
		{
			Simple,
			GLSL450,
			OpenCL,

			Count
		};
	};

	struct SpvStorageClass
	{
		enum Enum
		{
			UniformConstant,
			Input,
			Uniform,
			Output,
			Workgroup,
			CrossWorkgroup,
			Private,
			Function,
			Generic,
			PushConstant,
			AtomicCounter,
			Image,

			Count
		};
	};

	const char* getName(SpvStorageClass::Enum _enum);

	struct SpvResourceDim
	{
		enum Enum
		{
			Texture1D,
			Texture2D,
			Texture3D,
			TextureCube,
			TextureRect,
			Buffer,
			SubpassData,
		};
	};

	struct SpvDecoration
	{
		enum Enum
		{
			RelaxedPrecision,
			SpecId,
			Block,
			BufferBlock,
			RowMajor,
			ColMajor,
			ArrayStride,
			MatrixStride,
			GLSLShared,
			GLSLPacked,
			CPacked,
			BuiltIn,
			Unknown12,
			NoPerspective,
			Flat,
			Patch,
			Centroid,
			Sample,
			Invariant,
			Restrict,
			Aliased,
			Volatile,
			Constant,
			Coherent,
			NonWritable,
			NonReadable,
			Uniform,
			Unknown27,
			SaturatedConversion,
			Stream,
			Location,
			Component,
			Index,
			Binding,
			DescriptorSet,
			Offset,
			XfbBuffer,
			XfbStride,
			FuncParamAttr,
			FPRoundingMode,
			FPFastMathMode,
			LinkageAttributes,
			NoContraction,
			InputAttachmentIndex,
			Alignment,

			Count
		};
	};

	const char* getName(SpvDecoration::Enum _enum);

	struct SpvOperand
	{
		SpvOperand() { /* not pod */ }

		enum Enum
		{
			AccessQualifier,
			AddressingModel,
			Base,
			Capability,
			Component,
			ComponentType,
			Composite,
			Condition,
			Coordinate,
			Decoration,
			Dim,
			Dref,
			ElementType,
			ExecutionModel,
			Function,
			FunctionControl,
			Id,
			IdRep,
			ImageFormat,
			ImageOperands,
			LinkageType,
			LiteralNumber,
			LiteralRep,
			LiteralString,
			Matrix,
			MemoryAccess,
			MemoryModel,
			Object,
			Pointer,
			SampledType,
			SampledImage,
			SamplerAddressingMode,
			SamplerFilterMode,
			Scalar,
			SourceLanguage,
			StorageClass,
			StructureType,
			Vector,

			Count
		};

		Enum type;
		uint32_t data;

		stl::string literalString;
	};

	struct SpvInstruction
	{
		SpvInstruction() { /* not pod */ }

		SpvOpcode::Enum opcode;
		uint16_t length;
		uint16_t numOperands;

		uint32_t type;
		uint32_t result;
		bool hasType;
		bool hasResult;

		SpvOperand operand[32];
	};

	int32_t read(bx::ReaderI* _reader, SpvInstruction& _instruction, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const SpvInstruction& _instruction, bx::Error* _err);
	int32_t toString(char* _out, int32_t _size, const SpvInstruction& _instruction);

	struct SpvShader
	{
		SpvShader() { /* not pod */ }

		stl::vector<uint8_t> byteCode;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpvShader& _shader, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const SpvShader& _shader, bx::Error* _err);

	typedef bool (*SpvParseFn)(uint32_t _offset, const SpvInstruction& _instruction, void* _userData);
	void parse(const SpvShader& _src, SpvParseFn _fn, void* _userData, bx::Error* _err = NULL);

	typedef void (*SpvFilterFn)(SpvInstruction& _instruction, void* _userData);
	void filter(SpvShader& _dst, const SpvShader& _src, SpvFilterFn _fn, void* _userData, bx::Error* _err = NULL);

	struct SpirV
	{
		SpirV() { /* not pod */ }

		struct Header
		{
			uint32_t magic;
			uint32_t version;
			uint32_t generator;
			uint32_t bound;
			uint32_t schema;
		};

		Header header;
		SpvShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpirV& _spirv, bx::Error* _err);
	int32_t write(bx::WriterSeekerI* _writer, const SpirV& _spirv, bx::Error* _err);

} // namespace bgfx

#endif // BGFX_SHADER_SPIRV_H

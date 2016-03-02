/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_SPIRV_H
#define BGFX_SHADER_SPIRV_H

#include <bx/readerwriter.h>

namespace bgfx
{
	// Reference: https://www.khronos.org/registry/spir-v/specs/1.0/SPIRV.html

	struct SpirvOpcode
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
			Extension,
			ExtInstImport,
			ExtInst,
			MemoryModel,
			EntryPoint,
			ExecutionMode,
			Capability,
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
			ConstantTrue,
			ConstantFalse,
			Constant,
			ConstantComposite,
			ConstantSampler,
			ConstantNull,
			SpecConstantTrue,
			SpecConstantFalse,
			SpecConstant,
			SpecConstantComposite,
			SpecConstantOp,
			Function,
			FunctionParameter,
			FunctionEnd,
			FunctionCall,
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
			VectorExtractDynamic,
			VectorInsertDynamic,
			VectorShuffle,
			CompositeConstruct,
			CompositeExtract,
			CompositeInsert,
			CopyObject,
			Transpose,
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
			DPdx,
			DPdy,
			Fwidth,
			DPdxFine,
			DPdyFine,
			FwidthFine,
			DPdxCoarse,
			DPdyCoarse,
			FwidthCoarse,
			EmitVertex,
			EndPrimitive,
			EmitStreamVertex,
			EndStreamPrimitive,
			ControlBarrier,
			MemoryBarrier,
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

	struct SpirvBuiltin
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
		};
	};

	struct SpirvExecutionModel
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

	struct SpirvMemoryModel
	{
		enum Enum
		{
			Simple,
			GLSL450,
			OpenCL,

			Count
		};
	};

	struct SpirvStorageClass
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
		};
	};

	struct SpirvResourceDim
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

	struct SpirvDecoration
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

	struct SpirvOperand
	{
	};

	struct SpirvInstruction
	{
		SpirvOpcode::Enum opcode;
		uint16_t length;

		uint8_t numOperands;
		SpirvOperand operand[6];

		union
		{
			struct ResultTypeId
			{
				uint32_t resultType;
				uint32_t id;
			};

			ResultTypeId constant;
			ResultTypeId constantComposite;

			uint32_t value[8];
		} un;
	};

	int32_t read(bx::ReaderI* _reader, SpirvInstruction& _instruction);
	int32_t write(bx::WriterI* _writer, const SpirvInstruction& _instruction);
	int32_t toString(char* _out, int32_t _size, const SpirvInstruction& _instruction);

	struct SpirvShader
	{
		stl::vector<uint8_t> byteCode;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpirvShader& _shader);
	int32_t write(bx::WriterI* _writer, const SpirvShader& _shader);

	typedef bool (*SpirvParseFn)(uint32_t _offset, const SpirvInstruction& _instruction, void* _userData);
	void parse(const SpirvShader& _src, SpirvParseFn _fn, void* _userData);

	typedef void (*SpirvFilterFn)(SpirvInstruction& _instruction, void* _userData);
	void filter(SpirvShader& _dst, const SpirvShader& _src, SpirvFilterFn _fn, void* _userData);

	struct Spirv
	{
		struct Header
		{
			uint32_t magic;
			uint32_t version;
			uint32_t generator;
			uint32_t bound;
			uint32_t schema;
		};

		Header header;
		SpirvShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, Spirv& _spirv);
	int32_t write(bx::WriterSeekerI* _writer, const Spirv& _spirv);

} // namespace bgfx

#endif // BGFX_SHADER_SPIRV_H

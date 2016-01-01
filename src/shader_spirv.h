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
			Source,
			SourceExtension,
			Extension,
			ExtInstImport,
			MemoryModel,
			EntryPoint,
			ExecutionMode,
			TypeVoid,
			TypeBool,
			TypeInt,
			TypeFloat,
			TypeVector,
			TypeMatrix,
			TypeSampler,
			TypeFilter,
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
			ConstantTrue,
			ConstantFalse,
			Constant,
			ConstantComposite,
			ConstantSampler,
			ConstantNullPointer,
			ConstantNullObject,
			SpecConstantTrue,
			SpecConstantFalse,
			SpecConstant,
			SpecConstantComposite,
			Variable,
			VariableArray,
			Function,
			FunctionParameter,
			FunctionEnd,
			FunctionCall,
			ExtInst,
			Undef,
			Load,
			Store,
			Phi,
			DecorationGroup,
			Decorate,
			MemberDecorate,
			GroupDecorate,
			GroupMemberDecorate,
			Name,
			MemberName,
			String,
			Line,
			VectorExtractDynamic,
			VectorInsertDynamic,
			VectorShuffle,
			CompositeConstruct,
			CompositeExtract,
			CompositeInsert,
			CopyObject,
			CopyMemory,
			CopyMemorySized,
			Sampler,
			TextureSample,
			TextureSampleDref,
			TextureSampleLod,
			TextureSampleProj,
			TextureSampleGrad,
			TextureSampleOffset,
			TextureSampleProjLod,
			TextureSampleProjGrad,
			TextureSampleLodOffset,
			TextureSampleProjOffset,
			TextureSampleGradOffset,
			TextureSampleProjLodOffset,
			TextureSampleProjGradOffset,
			TextureFetchTexelLod,
			TextureFetchTexelOffset,
			TextureFetchSample,
			TextureFetchTexel,
			TextureGather,
			TextureGatherOffset,
			TextureGatherOffsets,
			TextureQuerySizeLod,
			TextureQuerySize,
			TextureQueryLod,
			TextureQueryLevels,
			TextureQuerySamples,
			AccessChain,
			InBoundsAccessChain,
			SNegate,
			FNegate,
			Not,
			Any,
			All,
			ConvertFToU,
			ConvertFToS,
			ConvertSToF,
			ConvertUToF,
			UConvert,
			SConvert,
			FConvert,
			ConvertPtrToU,
			ConvertUToPtr,
			PtrCastToGeneric,
			GenericCastToPtr,
			Bitcast,
			Transpose,
			IsNan,
			IsInf,
			IsFinite,
			IsNormal,
			SignBitSet,
			LessOrGreater,
			Ordered,
			Unordered,
			ArrayLength,
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
			ShiftRightLogical,
			ShiftRightArithmetic,
			ShiftLeftLogical,
			LogicalOr,
			LogicalXor,
			LogicalAnd,
			BitwiseOr,
			BitwiseXor,
			BitwiseAnd,
			Select,
			IEqual,
			FOrdEqual,
			FUnordEqual,
			INotEqual,
			FOrdNotEqual,
			FUnordNotEqual,
			ULessThan,
			SLessThan,
			FOrdLessThan,
			FUnordLessThan,
			UGreaterThan,
			SGreaterThan,
			FOrdGreaterThan,
			FUnordGreaterThan,
			ULessThanEqual,
			SLessThanEqual,
			FOrdLessThanEqual,
			FUnordLessThanEqual,
			UGreaterThanEqual,
			SGreaterThanEqual,
			FOrdGreaterThanEqual,
			FUnordGreaterThanEqual,
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
			ImagePointer,
			AtomicInit,
			AtomicLoad,
			AtomicStore,
			AtomicExchange,
			AtomicCompareExchange,
			AtomicCompareExchangeWeak,
			AtomicIIncrement,
			AtomicIDecrement,
			AtomicIAdd,
			AtomicISub,
			AtomicUMin,
			AtomicUMax,
			AtomicAnd,
			AtomicOr,
			AtomicXor,
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
			CompileFlag,
			AsyncGroupCopy,
			WaitGroupEvents,
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
			GenericCastToPtrExplicit,
			GenericPtrMemSemantics,
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
			SatConvertSToU,
			SatConvertUToS,
			AtomicIMin,
			AtomicIMax,

			Count
		};
	};

	struct SpirvBuiltin
	{
		enum Enum
		{
			Position,
			PointSize,
			ClipVertex,
			ClipDistance,
			CullDistance,
			VertexId,
			InstanceId,
			BuiltInPrimitiveId,
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
			FragColor,
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
			WorkgroupLinearId,
			SubgroupSize,
			SubgroupMaxSize,
			NumSubgroups,
			NumEnqueuedSubgroups,
			SubgroupId,
			SubgroupLocalInvocationId,
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
			OpenCL12,
			OpenCL20,
			OpenCL21,

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
			WorkgroupLocal,
			WorkgroupGlobal,
			PrivateGlobal,
			Function,
			Generic,
			Private,
			AtomicCounter,
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
		};
	};

	struct SpirvDecoration
	{
		enum Enum
		{
			PrecisionLow,
			PrecisionMedium,
			PrecisionHigh,
			Block,
			BufferBlock,
			RowMajor,
			ColMajor,
			GLSLShared,
			GLSLStd140,
			GLSLStd430,
			GLSLPacked,
			Smooth,
			Noperspective,
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
			Nonwritable,
			Nonreadable,
			Uniform,
			NoStaticUse,
			CPacked,
			SaturatedConversion,
			Stream,
			Location,
			Component,
			Index,
			Binding,
			DescriptorSet,
			Offset,
			Alignment,
			XfbBuffer,
			Stride,
			BuiltIn,
			FuncParamAttr,
			FPRoundingMode,
			FPFastMathMode,
			LinkageAttributes,
			SpecId,

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

	typedef void (*SpirvParseFn)(uint32_t _offset, const SpirvInstruction& _instruction, void* _userData);
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

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include "shader_spirv.h"

namespace bgfx
{
	struct SpirvOpcodeInfo
	{
		uint8_t numOperands;
		uint8_t numValues;
		bool    hasVariable;
	};

	static const SpirvOpcodeInfo s_sprivOpcodeInfo[] =
	{
		{ 0, 0, false }, // Nop,
		{ 0, 0, true  }, // Source
		{ 0, 0, true  }, // SourceExtension
		{ 0, 0, false }, // Extension
		{ 0, 1, true  }, // ExtInstImport
		{ 0, 2, false }, // MemoryModel
		{ 0, 2, false }, // EntryPoint
		{ 0, 0, false }, // ExecutionMode
		{ 0, 1, false }, // TypeVoid
		{ 0, 1, false }, // TypeBool
		{ 0, 3, false }, // TypeInt
		{ 0, 2, false }, // TypeFloat
		{ 0, 3, false }, // TypeVector
		{ 0, 3, false }, // TypeMatrix
		{ 1, 7, false }, // TypeSampler
		{ 0, 0, false }, // TypeFilter
		{ 0, 0, false }, // TypeArray
		{ 0, 0, false }, // TypeRuntimeArray
		{ 0, 0, false }, // TypeStruct
		{ 0, 0, false }, // TypeOpaque
		{ 0, 3, false }, // TypePointer
		{ 0, 2, true  }, // TypeFunction
		{ 0, 0, false }, // TypeEvent
		{ 0, 0, false }, // TypeDeviceEvent
		{ 0, 0, false }, // TypeReserveId
		{ 0, 0, false }, // TypeQueue
		{ 0, 0, false }, // TypePipe
		{ 0, 0, false }, // ConstantTrue
		{ 0, 0, false }, // ConstantFalse
		{ 0, 2, true  }, // Constant
		{ 0, 2, true  }, // ConstantComposite
		{ 0, 0, false }, // ConstantSampler
		{ 0, 0, false }, // ConstantNullPointer
		{ 0, 0, false }, // ConstantNullObject
		{ 0, 0, false }, // SpecConstantTrue
		{ 0, 0, false }, // SpecConstantFalse
		{ 0, 0, false }, // SpecConstant
		{ 0, 0, false }, // SpecConstantComposite
		{ 0, 3, true  }, // Variable
		{ 0, 0, false }, // VariableArray
		{ 0, 4, false }, // Function
		{ 0, 0, false }, // FunctionParameter
		{ 0, 0, false }, // FunctionEnd
		{ 0, 0, false }, // FunctionCall
		{ 0, 0, false }, // ExtInst
		{ 0, 0, false }, // Undef
		{ 0, 0, false }, // Load
		{ 0, 2, true  }, // Store
		{ 0, 0, false }, // Phi
		{ 0, 0, false }, // DecorationGroup
		{ 0, 2, true  }, // Decorate
		{ 0, 0, false }, // MemberDecorate
		{ 0, 0, false }, // GroupDecorate
		{ 0, 0, false }, // GroupMemberDecorate
		{ 0, 1, true  }, // Name
		{ 0, 1, true  }, // MemberName
		{ 0, 0, false }, // String
		{ 0, 0, false }, // Line
		{ 0, 0, false }, // VectorExtractDynamic
		{ 0, 0, false }, // VectorInsertDynamic
		{ 0, 0, false }, // VectorShuffle
		{ 0, 0, false }, // CompositeConstruct
		{ 0, 0, false }, // CompositeExtract
		{ 0, 0, false }, // CompositeInsert
		{ 0, 0, false }, // CopyObject
		{ 0, 0, false }, // CopyMemory
		{ 0, 0, false }, // CopyMemorySized
		{ 0, 0, false }, // Sampler
		{ 0, 0, false }, // TextureSample
		{ 0, 0, false }, // TextureSampleDref
		{ 0, 0, false }, // TextureSampleLod
		{ 0, 0, false }, // TextureSampleProj
		{ 0, 0, false }, // TextureSampleGrad
		{ 0, 0, false }, // TextureSampleOffset
		{ 0, 0, false }, // TextureSampleProjLod
		{ 0, 0, false }, // TextureSampleProjGrad
		{ 0, 0, false }, // TextureSampleLodOffset
		{ 0, 0, false }, // TextureSampleProjOffset
		{ 0, 0, false }, // TextureSampleGradOffset
		{ 0, 0, false }, // TextureSampleProjLodOffset
		{ 0, 0, false }, // TextureSampleProjGradOffset
		{ 0, 0, false }, // TextureFetchTexelLod
		{ 0, 0, false }, // TextureFetchTexelOffset
		{ 0, 0, false }, // TextureFetchSample
		{ 0, 0, false }, // TextureFetchTexel
		{ 0, 0, false }, // TextureGather
		{ 0, 0, false }, // TextureGatherOffset
		{ 0, 0, false }, // TextureGatherOffsets
		{ 0, 0, false }, // TextureQuerySizeLod
		{ 0, 0, false }, // TextureQuerySize
		{ 0, 0, false }, // TextureQueryLod
		{ 0, 0, false }, // TextureQueryLevels
		{ 0, 0, false }, // TextureQuerySamples
		{ 0, 0, false }, // AccessChain
		{ 0, 0, false }, // InBoundsAccessChain
		{ 0, 0, false }, // SNegate
		{ 0, 0, false }, // FNegate
		{ 0, 0, false }, // Not
		{ 0, 0, false }, // Any
		{ 0, 0, false }, // All
		{ 0, 0, false }, // ConvertFToU
		{ 0, 0, false }, // ConvertFToS
		{ 0, 0, false }, // ConvertSToF
		{ 0, 0, false }, // ConvertUToF
		{ 0, 0, false }, // UConvert
		{ 0, 0, false }, // SConvert
		{ 0, 0, false }, // FConvert
		{ 0, 0, false }, // ConvertPtrToU
		{ 0, 0, false }, // ConvertUToPtr
		{ 0, 0, false }, // PtrCastToGeneric
		{ 0, 0, false }, // GenericCastToPtr
		{ 0, 0, false }, // Bitcast
		{ 0, 0, false }, // Transpose
		{ 0, 0, false }, // IsNan
		{ 0, 0, false }, // IsInf
		{ 0, 0, false }, // IsFinite
		{ 0, 0, false }, // IsNormal
		{ 0, 0, false }, // SignBitSet
		{ 0, 0, false }, // LessOrGreater
		{ 0, 0, false }, // Ordered
		{ 0, 0, false }, // Unordered
		{ 0, 0, false }, // ArrayLength
		{ 0, 0, false }, // IAdd
		{ 0, 0, false }, // FAdd
		{ 0, 0, false }, // ISub
		{ 0, 0, false }, // FSub
		{ 0, 0, false }, // IMul
		{ 0, 0, false }, // FMul
		{ 0, 0, false }, // UDiv
		{ 0, 0, false }, // SDiv
		{ 0, 0, false }, // FDiv
		{ 0, 0, false }, // UMod
		{ 0, 0, false }, // SRem
		{ 0, 0, false }, // SMod
		{ 0, 0, false }, // FRem
		{ 0, 0, false }, // FMod
		{ 0, 0, false }, // VectorTimesScalar
		{ 0, 0, false }, // MatrixTimesScalar
		{ 0, 0, false }, // VectorTimesMatrix
		{ 0, 0, false }, // MatrixTimesVector
		{ 0, 0, false }, // MatrixTimesMatrix
		{ 0, 0, false }, // OuterProduct
		{ 0, 0, false }, // Dot
		{ 0, 0, false }, // ShiftRightLogical
		{ 0, 0, false }, // ShiftRightArithmetic
		{ 0, 0, false }, // ShiftLeftLogical
		{ 0, 0, false }, // LogicalOr
		{ 0, 0, false }, // LogicalXor
		{ 0, 0, false }, // LogicalAnd
		{ 0, 0, false }, // BitwiseOr
		{ 0, 0, false }, // BitwiseXor
		{ 0, 0, false }, // BitwiseAnd
		{ 0, 0, false }, // Select
		{ 0, 0, false }, // IEqual
		{ 0, 0, false }, // FOrdEqual
		{ 0, 0, false }, // FUnordEqual
		{ 0, 0, false }, // INotEqual
		{ 0, 0, false }, // FOrdNotEqual
		{ 0, 0, false }, // FUnordNotEqual
		{ 0, 0, false }, // ULessThan
		{ 0, 0, false }, // SLessThan
		{ 0, 0, false }, // FOrdLessThan
		{ 0, 0, false }, // FUnordLessThan
		{ 0, 0, false }, // UGreaterThan
		{ 0, 0, false }, // SGreaterThan
		{ 0, 0, false }, // FOrdGreaterThan
		{ 0, 0, false }, // FUnordGreaterThan
		{ 0, 0, false }, // ULessThanEqual
		{ 0, 0, false }, // SLessThanEqual
		{ 0, 0, false }, // FOrdLessThanEqual
		{ 0, 0, false }, // FUnordLessThanEqual
		{ 0, 0, false }, // UGreaterThanEqual
		{ 0, 0, false }, // SGreaterThanEqual
		{ 0, 0, false }, // FOrdGreaterThanEqual
		{ 0, 0, false }, // FUnordGreaterThanEqual
		{ 0, 0, false }, // DPdx
		{ 0, 0, false }, // DPdy
		{ 0, 0, false }, // Fwidth
		{ 0, 0, false }, // DPdxFine
		{ 0, 0, false }, // DPdyFine
		{ 0, 0, false }, // FwidthFine
		{ 0, 0, false }, // DPdxCoarse
		{ 0, 0, false }, // DPdyCoarse
		{ 0, 0, false }, // FwidthCoarse
		{ 0, 0, false }, // EmitVertex
		{ 0, 0, false }, // EndPrimitive
		{ 0, 0, false }, // EmitStreamVertex
		{ 0, 0, false }, // EndStreamPrimitive
		{ 0, 0, false }, // ControlBarrier
		{ 0, 0, false }, // MemoryBarrier
		{ 0, 0, false }, // ImagePointer
		{ 0, 0, false }, // AtomicInit
		{ 0, 0, false }, // AtomicLoad
		{ 0, 0, false }, // AtomicStore
		{ 0, 0, false }, // AtomicExchange
		{ 0, 0, false }, // AtomicCompareExchange
		{ 0, 0, false }, // AtomicCompareExchangeWeak
		{ 0, 0, false }, // AtomicIIncrement
		{ 0, 0, false }, // AtomicIDecrement
		{ 0, 0, false }, // AtomicIAdd
		{ 0, 0, false }, // AtomicISub
		{ 0, 0, false }, // AtomicUMin
		{ 0, 0, false }, // AtomicUMax
		{ 0, 0, false }, // AtomicAnd
		{ 0, 0, false }, // AtomicOr
		{ 0, 0, false }, // AtomicXor
		{ 0, 0, false }, // LoopMerge
		{ 0, 0, false }, // SelectionMerge
		{ 0, 1, false }, // Label
		{ 0, 1, false }, // Branch
		{ 0, 0, false }, // BranchConditional
		{ 0, 0, false }, // Switch
		{ 0, 0, false }, // Kill
		{ 0, 0, false }, // Return
		{ 0, 0, false }, // ReturnValue
		{ 0, 0, false }, // Unreachable
		{ 0, 0, false }, // LifetimeStart
		{ 0, 0, false }, // LifetimeStop
		{ 0, 0, false }, // CompileFlag
		{ 0, 0, false }, // AsyncGroupCopy
		{ 0, 0, false }, // WaitGroupEvents
		{ 0, 0, false }, // GroupAll
		{ 0, 0, false }, // GroupAny
		{ 0, 0, false }, // GroupBroadcast
		{ 0, 0, false }, // GroupIAdd
		{ 0, 0, false }, // GroupFAdd
		{ 0, 0, false }, // GroupFMin
		{ 0, 0, false }, // GroupUMin
		{ 0, 0, false }, // GroupSMin
		{ 0, 0, false }, // GroupFMax
		{ 0, 0, false }, // GroupUMax
		{ 0, 0, false }, // GroupSMax
		{ 0, 0, false }, // GenericCastToPtrExplicit
		{ 0, 0, false }, // GenericPtrMemSemantics
		{ 0, 0, false }, // ReadPipe
		{ 0, 0, false }, // WritePipe
		{ 0, 0, false }, // ReservedReadPipe
		{ 0, 0, false }, // ReservedWritePipe
		{ 0, 0, false }, // ReserveReadPipePackets
		{ 0, 0, false }, // ReserveWritePipePackets
		{ 0, 0, false }, // CommitReadPipe
		{ 0, 0, false }, // CommitWritePipe
		{ 0, 0, false }, // IsValidReserveId
		{ 0, 0, false }, // GetNumPipePackets
		{ 0, 0, false }, // GetMaxPipePackets
		{ 0, 0, false }, // GroupReserveReadPipePackets
		{ 0, 0, false }, // GroupReserveWritePipePackets
		{ 0, 0, false }, // GroupCommitReadPipe
		{ 0, 0, false }, // GroupCommitWritePipe
		{ 0, 0, false }, // EnqueueMarker
		{ 0, 0, false }, // EnqueueKernel
		{ 0, 0, false }, // GetKernelNDrangeSubGroupCount
		{ 0, 0, false }, // GetKernelNDrangeMaxSubGroupSize
		{ 0, 0, false }, // GetKernelWorkGroupSize
		{ 0, 0, false }, // GetKernelPreferredWorkGroupSizeMultiple
		{ 0, 0, false }, // RetainEvent
		{ 0, 0, false }, // ReleaseEvent
		{ 0, 0, false }, // CreateUserEvent
		{ 0, 0, false }, // IsValidEvent
		{ 0, 0, false }, // SetUserEventStatus
		{ 0, 0, false }, // CaptureEventProfilingInfo
		{ 0, 0, false }, // GetDefaultQueue
		{ 0, 0, false }, // BuildNDRange
		{ 0, 0, false }, // SatConvertSToU
		{ 0, 0, false }, // SatConvertUToS
		{ 0, 0, false }, // AtomicIMin
		{ 0, 0, false }, // AtomicIMax
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_sprivOpcodeInfo) == SpirvOpcode::Count);

	const char* s_spirvOpcode[] =
	{
		"Nop",
		"Source",
		"SourceExtension",
		"Extension",
		"ExtInstImport",
		"MemoryModel",
		"EntryPoint",
		"ExecutionMode",
		"TypeVoid",
		"TypeBool",
		"TypeInt",
		"TypeFloat",
		"TypeVector",
		"TypeMatrix",
		"TypeSampler",
		"TypeFilter",
		"TypeArray",
		"TypeRuntimeArray",
		"TypeStruct",
		"TypeOpaque",
		"TypePointer",
		"TypeFunction",
		"TypeEvent",
		"TypeDeviceEvent",
		"TypeReserveId",
		"TypeQueue",
		"TypePipe",
		"ConstantTrue",
		"ConstantFalse",
		"Constant",
		"ConstantComposite",
		"ConstantSampler",
		"ConstantNullPointer",
		"ConstantNullObject",
		"SpecConstantTrue",
		"SpecConstantFalse",
		"SpecConstant",
		"SpecConstantComposite",
		"Variable",
		"VariableArray",
		"Function",
		"FunctionParameter",
		"FunctionEnd",
		"FunctionCall",
		"ExtInst",
		"Undef",
		"Load",
		"Store",
		"Phi",
		"DecorationGroup",
		"Decorate",
		"MemberDecorate",
		"GroupDecorate",
		"GroupMemberDecorate",
		"Name",
		"MemberName",
		"String",
		"Line",
		"VectorExtractDynamic",
		"VectorInsertDynamic",
		"VectorShuffle",
		"CompositeConstruct",
		"CompositeExtract",
		"CompositeInsert",
		"CopyObject",
		"CopyMemory",
		"CopyMemorySized",
		"Sampler",
		"TextureSample",
		"TextureSampleDref",
		"TextureSampleLod",
		"TextureSampleProj",
		"TextureSampleGrad",
		"TextureSampleOffset",
		"TextureSampleProjLod",
		"TextureSampleProjGrad",
		"TextureSampleLodOffset",
		"TextureSampleProjOffset",
		"TextureSampleGradOffset",
		"TextureSampleProjLodOffset",
		"TextureSampleProjGradOffset",
		"TextureFetchTexelLod",
		"TextureFetchTexelOffset",
		"TextureFetchSample",
		"TextureFetchTexel",
		"TextureGather",
		"TextureGatherOffset",
		"TextureGatherOffsets",
		"TextureQuerySizeLod",
		"TextureQuerySize",
		"TextureQueryLod",
		"TextureQueryLevels",
		"TextureQuerySamples",
		"AccessChain",
		"InBoundsAccessChain",
		"SNegate",
		"FNegate",
		"Not",
		"Any",
		"All",
		"ConvertFToU",
		"ConvertFToS",
		"ConvertSToF",
		"ConvertUToF",
		"UConvert",
		"SConvert",
		"FConvert",
		"ConvertPtrToU",
		"ConvertUToPtr",
		"PtrCastToGeneric",
		"GenericCastToPtr",
		"Bitcast",
		"Transpose",
		"IsNan",
		"IsInf",
		"IsFinite",
		"IsNormal",
		"SignBitSet",
		"LessOrGreater",
		"Ordered",
		"Unordered",
		"ArrayLength",
		"IAdd",
		"FAdd",
		"ISub",
		"FSub",
		"IMul",
		"FMul",
		"UDiv",
		"SDiv",
		"FDiv",
		"UMod",
		"SRem",
		"SMod",
		"FRem",
		"FMod",
		"VectorTimesScalar",
		"MatrixTimesScalar",
		"VectorTimesMatrix",
		"MatrixTimesVector",
		"MatrixTimesMatrix",
		"OuterProduct",
		"Dot",
		"ShiftRightLogical",
		"ShiftRightArithmetic",
		"ShiftLeftLogical",
		"LogicalOr",
		"LogicalXor",
		"LogicalAnd",
		"BitwiseOr",
		"BitwiseXor",
		"BitwiseAnd",
		"Select",
		"IEqual",
		"FOrdEqual",
		"FUnordEqual",
		"INotEqual",
		"FOrdNotEqual",
		"FUnordNotEqual",
		"ULessThan",
		"SLessThan",
		"FOrdLessThan",
		"FUnordLessThan",
		"UGreaterThan",
		"SGreaterThan",
		"FOrdGreaterThan",
		"FUnordGreaterThan",
		"ULessThanEqual",
		"SLessThanEqual",
		"FOrdLessThanEqual",
		"FUnordLessThanEqual",
		"UGreaterThanEqual",
		"SGreaterThanEqual",
		"FOrdGreaterThanEqual",
		"FUnordGreaterThanEqual",
		"DPdx",
		"DPdy",
		"Fwidth",
		"DPdxFine",
		"DPdyFine",
		"FwidthFine",
		"DPdxCoarse",
		"DPdyCoarse",
		"FwidthCoarse",
		"EmitVertex",
		"EndPrimitive",
		"EmitStreamVertex",
		"EndStreamPrimitive",
		"ControlBarrier",
		"MemoryBarrier",
		"ImagePointer",
		"AtomicInit",
		"AtomicLoad",
		"AtomicStore",
		"AtomicExchange",
		"AtomicCompareExchange",
		"AtomicCompareExchangeWeak",
		"AtomicIIncrement",
		"AtomicIDecrement",
		"AtomicIAdd",
		"AtomicISub",
		"AtomicUMin",
		"AtomicUMax",
		"AtomicAnd",
		"AtomicOr",
		"AtomicXor",
		"LoopMerge",
		"SelectionMerge",
		"Label",
		"Branch",
		"BranchConditional",
		"Switch",
		"Kill",
		"Return",
		"ReturnValue",
		"Unreachable",
		"LifetimeStart",
		"LifetimeStop",
		"CompileFlag",
		"AsyncGroupCopy",
		"WaitGroupEvents",
		"GroupAll",
		"GroupAny",
		"GroupBroadcast",
		"GroupIAdd",
		"GroupFAdd",
		"GroupFMin",
		"GroupUMin",
		"GroupSMin",
		"GroupFMax",
		"GroupUMax",
		"GroupSMax",
		"GenericCastToPtrExplicit",
		"GenericPtrMemSemantics",
		"ReadPipe",
		"WritePipe",
		"ReservedReadPipe",
		"ReservedWritePipe",
		"ReserveReadPipePackets",
		"ReserveWritePipePackets",
		"CommitReadPipe",
		"CommitWritePipe",
		"IsValidReserveId",
		"GetNumPipePackets",
		"GetMaxPipePackets",
		"GroupReserveReadPipePackets",
		"GroupReserveWritePipePackets",
		"GroupCommitReadPipe",
		"GroupCommitWritePipe",
		"EnqueueMarker",
		"EnqueueKernel",
		"GetKernelNDrangeSubGroupCount",
		"GetKernelNDrangeMaxSubGroupSize",
		"GetKernelWorkGroupSize",
		"GetKernelPreferredWorkGroupSizeMultiple",
		"RetainEvent",
		"ReleaseEvent",
		"CreateUserEvent",
		"IsValidEvent",
		"SetUserEventStatus",
		"CaptureEventProfilingInfo",
		"GetDefaultQueue",
		"BuildNDRange",
		"SatConvertSToU",
		"SatConvertUToS",
		"AtomicIMin",
		"AtomicIMax",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spirvOpcode) == SpirvOpcode::Count);

	const char* getName(SpirvOpcode::Enum _opcode)
	{
		BX_CHECK(_opcode < SpirvOpcode::Count, "Unknown opcode id %d.", _opcode);
		return s_spirvOpcode[_opcode];
	}

	int32_t read(bx::ReaderI* _reader, SpirvOperand& _operand)
	{
		int32_t size = 0;

		BX_UNUSED(_operand);
		uint32_t token;
		size += bx::read(_reader, token);

		return size;
	}

	int32_t read(bx::ReaderI* _reader, SpirvInstruction& _instruction)
	{
		int32_t size = 0;

		uint32_t token;
		size += bx::read(_reader, token);

		_instruction.opcode = SpirvOpcode::Enum( (token & UINT32_C(0x0000ffff) )      );
		_instruction.length =          uint16_t( (token & UINT32_C(0xffff0000) ) >> 16);

		uint32_t currOp = 0;

		const SpirvOpcodeInfo& info = s_sprivOpcodeInfo[_instruction.opcode];

		if (0 < info.numValues)
		{
			size += read(_reader, _instruction.un.value, info.numValues*sizeof(uint32_t) );
		}

		if (info.hasVariable)
		{
			while (size/4 != _instruction.length)
			{
				uint32_t tmp;
				size += bx::read(_reader, tmp);
			}
		}
		else
		{
			_instruction.numOperands = info.numOperands;
			switch (info.numOperands)
			{
			case 6: size += read(_reader, _instruction.operand[currOp++]);
			case 5: size += read(_reader, _instruction.operand[currOp++]);
			case 4: size += read(_reader, _instruction.operand[currOp++]);
			case 3: size += read(_reader, _instruction.operand[currOp++]);
			case 2: size += read(_reader, _instruction.operand[currOp++]);
			case 1: size += read(_reader, _instruction.operand[currOp++]);
			case 0:
				break;

			default:
				BX_WARN(false, "Instruction %s with invalid number of operands %d (numValues %d)."
						, getName(_instruction.opcode)
						, info.numOperands
						, info.numValues
						);
				break;
			}

			BX_WARN(size/4 == _instruction.length, "read %d, expected %d, %s"
					, size/4
					, _instruction.length
					, getName(_instruction.opcode)
					);
			while (size/4 != _instruction.length)
			{
				uint32_t tmp;
				size += bx::read(_reader, tmp);
			}
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const SpirvInstruction& _instruction)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _instruction);
		return size;
	}

	int32_t toString(char* _out, int32_t _size, const SpirvInstruction& _instruction)
	{
		int32_t size = 0;
		size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
					, "%s %d (%d, %d)"
					, getName(_instruction.opcode)
					, _instruction.numOperands
					, _instruction.un.value[0]
					, _instruction.un.value[1]
					);

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, SpirvShader& _shader)
	{
		int32_t size = 0;

		uint32_t len = uint32_t(bx::getSize(_reader) - bx::seek(_reader) );
		_shader.byteCode.resize(len);
		size += bx::read(_reader, _shader.byteCode.data(), len);

		return size;
	}

	int32_t write(bx::WriterI* _writer, const SpirvShader& _shader)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _shader);
		return size;
	}

#define SPIRV_MAGIC 0x07230203

	int32_t read(bx::ReaderSeekerI* _reader, Spirv& _spirv)
	{
		int32_t size = 0;

		size += bx::read(_reader, _spirv.header);

		if (size != sizeof(Spirv::Header)
		||  _spirv.header.magic != SPIRV_MAGIC
		   )
		{
			// error
			return -size;
		}

		size += read(_reader, _spirv.shader);

		return size;
	}

	int32_t write(bx::WriterSeekerI* _writer, const Spirv& _spirv)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _spirv);
		return size;
	}

	void parse(const SpirvShader& _src, SpirvParseFn _fn, void* _userData)
	{
		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			SpirvInstruction instruction;
			uint32_t size = read(&reader, instruction);
			BX_CHECK(size/4 == instruction.length, "read %d, expected %d, %s"
					, size/4
					, instruction.length
					, getName(instruction.opcode)
					);
			BX_UNUSED(size);

			_fn(token * sizeof(uint32_t), instruction, _userData);

			token += instruction.length;
		}
	}

} // namespace bgfx

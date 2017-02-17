/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: 'inclusionDepth' : unreferenced formal parameter
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4265) // error C4265: 'spv::spirvbin_t': class has virtual functions, but destructor is not virtual
#include <ShaderLang.h>
#include <ResourceLimits.h>
#include <SPIRV/SPVRemapper.h>
//#include <spirv-tools/libspirv.hpp>
//#include <spirv-tools/optimizer.hpp>
BX_PRAGMA_DIAGNOSTIC_POP()

namespace bgfx
{
	static bx::CrtAllocator s_allocator;
	bx::AllocatorI* g_allocator = &s_allocator;

	struct TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};

	void* TinyStlAllocator::static_allocate(size_t _bytes)
	{
		return BX_ALLOC(g_allocator, _bytes);
	}

	void TinyStlAllocator::static_deallocate(void* _ptr, size_t /*_bytes*/)
	{
		if (NULL != _ptr)
		{
			BX_FREE(g_allocator, _ptr);
		}
	}
} // namespace bgfx

#define TINYSTL_ALLOCATOR bgfx::TinyStlAllocator
#include <tinystl/allocator.h>
#include <tinystl/string.h>
#include <tinystl/unordered_map.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

#include "../../src/shader_spirv.h"

namespace glslang
{
	void GlslangToSpv(const glslang::TIntermediate& _intermediate, std::vector<uint32_t>& _spirv);

} // namespace glslang

namespace bgfx { namespace spirv
{
	const TBuiltInResource resourceLimits =
	{
		32,    // MaxLights
		6,     // MaxClipPlanes
		32,    // MaxTextureUnits
		32,    // MaxTextureCoords
		64,    // MaxVertexAttribs
		4096,  // MaxVertexUniformComponents
		64,    // MaxVaryingFloats
		32,    // MaxVertexTextureImageUnits
		80,    // MaxCombinedTextureImageUnits
		32,    // MaxTextureImageUnits
		4096,  // MaxFragmentUniformComponents
		32,    // MaxDrawBuffers
		128,   // MaxVertexUniformVectors
		8,     // MaxVaryingVectors
		16,    // MaxFragmentUniformVectors
		16,    // MaxVertexOutputVectors
		15,    // MaxFragmentInputVectors
		-8,    // MinProgramTexelOffset
		7,     // MaxProgramTexelOffset
		8,     // MaxClipDistances
		65535, // MaxComputeWorkGroupCountX
		65535, // MaxComputeWorkGroupCountY
		65535, // MaxComputeWorkGroupCountZ
		1024,  // MaxComputeWorkGroupSizeX
		1024,  // MaxComputeWorkGroupSizeY
		64,    // MaxComputeWorkGroupSizeZ
		1024,  // MaxComputeUniformComponents
		16,    // MaxComputeTextureImageUnits
		8,     // MaxComputeImageUniforms
		8,     // MaxComputeAtomicCounters
		1,     // MaxComputeAtomicCounterBuffers
		60,    // MaxVaryingComponents
		64,    // MaxVertexOutputComponents
		64,    // MaxGeometryInputComponents
		128,   // MaxGeometryOutputComponents
		128,   // MaxFragmentInputComponents
		8,     // MaxImageUnits
		8,     // MaxCombinedImageUnitsAndFragmentOutputs
		8,     // MaxCombinedShaderOutputResources
		0,     // MaxImageSamples
		0,     // MaxVertexImageUniforms
		0,     // MaxTessControlImageUniforms
		0,     // MaxTessEvaluationImageUniforms
		0,     // MaxGeometryImageUniforms
		8,     // MaxFragmentImageUniforms
		8,     // MaxCombinedImageUniforms
		16,    // MaxGeometryTextureImageUnits
		256,   // MaxGeometryOutputVertices
		1024,  // MaxGeometryTotalOutputComponents
		1024,  // MaxGeometryUniformComponents
		64,    // MaxGeometryVaryingComponents
		128,   // MaxTessControlInputComponents
		128,   // MaxTessControlOutputComponents
		16,    // MaxTessControlTextureImageUnits
		1024,  // MaxTessControlUniformComponents
		4096,  // MaxTessControlTotalOutputComponents
		128,   // MaxTessEvaluationInputComponents
		128,   // MaxTessEvaluationOutputComponents
		16,    // MaxTessEvaluationTextureImageUnits
		1024,  // MaxTessEvaluationUniformComponents
		120,   // MaxTessPatchComponents
		32,    // MaxPatchVertices
		64,    // MaxTessGenLevel
		16,    // MaxViewports
		0,     // MaxVertexAtomicCounters
		0,     // MaxTessControlAtomicCounters
		0,     // MaxTessEvaluationAtomicCounters
		0,     // MaxGeometryAtomicCounters
		8,     // MaxFragmentAtomicCounters
		8,     // MaxCombinedAtomicCounters
		1,     // MaxAtomicCounterBindings
		0,     // MaxVertexAtomicCounterBuffers
		0,     // MaxTessControlAtomicCounterBuffers
		0,     // MaxTessEvaluationAtomicCounterBuffers
		0,     // MaxGeometryAtomicCounterBuffers
		1,     // MaxFragmentAtomicCounterBuffers
		1,     // MaxCombinedAtomicCounterBuffers
		16384, // MaxAtomicCounterBufferSize
		4,     // MaxTransformFeedbackBuffers
		64,    // MaxTransformFeedbackInterleavedComponents
		8,     // MaxCullDistances
		8,     // MaxCombinedClipAndCullDistances
		4,     // MaxSamples
		{      // limits
			1, // nonInductiveForLoops
			1, // whileLoops
			1, // doWhileLoops
			1, // generalUniformIndexing
			1, // generalAttributeMatrixVectorIndexing
			1, // generalVaryingIndexing
			1, // generalSamplerIndexing
			1, // generalVariableIndexing
			1, // generalConstantMatrixVectorIndexing
		},
	};

	bool printAsm(uint32_t _offset, const SpvInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_userData);
		char temp[512];
		toString(temp, sizeof(temp), _instruction);
		BX_TRACE("%5d: %s", _offset, temp);
		return true;
	}

	struct SpvReflection
	{
		struct TypeId
		{
			enum Enum
			{
				Void,
				Bool,
				Int32,
				Int64,
				Uint32,
				Uint64,
				Float,
				Double,

				Vector,
				Matrix,

				Count
			};

			TypeId()
				: baseType(Enum::Count)
				, type(Enum::Count)
				, numComponents(0)
			{
			}

			Enum baseType;
			Enum type;
			uint32_t numComponents;

			stl::string toString()
			{
				stl::string result;

				switch (type)
				{
				case Float:
					result.append("float");
					break;

				case Vector:
					bx::stringPrintf(result, "vec%d"
						, numComponents
						);
					break;

				case Matrix:
					bx::stringPrintf(result, "mat%d"
						, numComponents
						);

				default:
					break;
				}

				return result;
			}
		};

		struct Id
		{
			struct Variable
			{
				Variable()
					: decoration(SpvDecoration::Count)
					, builtin(SpvBuiltin::Count)
					, storageClass(SpvStorageClass::Count)
					, location(UINT32_MAX)
					, offset(UINT32_MAX)
					, type(UINT32_MAX)
				{
				}

				stl::string name;
				SpvDecoration::Enum decoration;
				SpvBuiltin::Enum builtin;
				SpvStorageClass::Enum storageClass;
				uint32_t location;
				uint32_t offset;
				uint32_t type;
			};

			typedef stl::vector<Variable> MemberArray;

			Variable var;
			MemberArray members;
		};

		typedef stl::unordered_map<uint32_t, TypeId> TypeIdMap;
		typedef stl::unordered_map<uint32_t, Id> IdMap;

		TypeIdMap typeIdMap;
		IdMap idMap;

		stl::string getTypeName(uint32_t _typeId)
		{
			return getTypeId(_typeId).toString();
		}

		Id& getId(uint32_t _id)
		{
			IdMap::iterator it = idMap.find(_id);
			if (it == idMap.end() )
			{
				Id id;
				stl::pair<IdMap::iterator, bool> result = idMap.insert(stl::make_pair(_id, id) );
				it = result.first;
			}

			return it->second;
		}

		Id::Variable& get(uint32_t _id, uint32_t _idx)
		{
			Id& id = getId(_id);
			id.members.resize(bx::uint32_max(_idx+1, uint32_t(id.members.size() ) ) );
			return id.members[_idx];
		}

		TypeId& getTypeId(uint32_t _id)
		{
			TypeIdMap::iterator it = typeIdMap.find(_id);
			if (it == typeIdMap.end() )
			{
				TypeId id;
				stl::pair<TypeIdMap::iterator, bool> result = typeIdMap.insert(stl::make_pair(_id, id) );
				it = result.first;
			}

			return it->second;
		}

		void update(uint32_t _id, const stl::string& _name)
		{
			getId(_id).var.name = _name;
		}

		BX_NO_INLINE void update(Id::Variable& _variable, SpvDecoration::Enum _decoration, uint32_t _literal)
		{
			_variable.decoration = _decoration;
			switch (_decoration)
			{
			case SpvDecoration::Location:
				_variable.location = _literal;
				break;

			case SpvDecoration::Offset:
				_variable.offset = _literal;
				break;

			case SpvDecoration::BuiltIn:
				_variable.builtin = SpvBuiltin::Enum(_literal);
				break;

			default:
				break;
			}
		}

		BX_NO_INLINE void update(Id::Variable& _variable, uint32_t _type, SpvStorageClass::Enum _storageClass)
		{
			_variable.type         = _type;
			_variable.storageClass = _storageClass;
		}

		void update(uint32_t _id, SpvDecoration::Enum _decoration, uint32_t _literal)
		{
			update(getId(_id).var, _decoration, _literal);
		}

		void update(uint32_t _id, uint32_t _type, SpvStorageClass::Enum _storageClass)
		{
			update(getId(_id).var, _type, _storageClass);
		}

		void update(uint32_t _id, uint32_t _idx, const stl::string& _name)
		{
			Id::Variable& var = get(_id, _idx);
			var.name = _name;
		}

		BX_NO_INLINE void update(uint32_t _id, uint32_t _idx, SpvDecoration::Enum _decoration, uint32_t _literal)
		{
			update(get(_id, _idx), _decoration, _literal);
		}

		void update(uint32_t _id, TypeId::Enum _type)
		{
			TypeId& type = getTypeId(_id);
			type.type = _type;
		}

		void update(uint32_t _id, TypeId::Enum _type, uint32_t _baseTypeId, uint32_t _numComonents)
		{
			TypeId& type = getTypeId(_id);
			type.type = _type;

			type.baseType = getTypeId(_baseTypeId).type;
			type.numComponents = _numComonents;
		}
	};

	bool spvParse(uint32_t _offset, const SpvInstruction& _instruction, void* _userData)
	{
		BX_UNUSED(_offset);
		SpvReflection* spv = (SpvReflection*)_userData;

		switch (_instruction.opcode)
		{
		case SpvOpcode::Name:
			spv->update(_instruction.result
				, _instruction.operand[0].literalString
				);
			break;

		case SpvOpcode::Decorate:
			spv->update(_instruction.operand[0].data
				, SpvDecoration::Enum(_instruction.operand[1].data)
				, _instruction.operand[2].data
				);
			break;

		case SpvOpcode::MemberName:
			spv->update(_instruction.result
				, _instruction.operand[0].data
				, _instruction.operand[1].literalString
				);
			break;

		case SpvOpcode::MemberDecorate:
			spv->update(_instruction.operand[0].data
				, _instruction.operand[1].data
				, SpvDecoration::Enum(_instruction.operand[2].data)
				, _instruction.operand[3].data
				);
			break;

		case SpvOpcode::Variable:
			spv->update(_instruction.result
				, _instruction.type
				, SpvStorageClass::Enum(_instruction.operand[0].data)
				);
			break;

		case SpvOpcode::TypeVoid:
			spv->update(_instruction.result, SpvReflection::TypeId::Void);
			break;

		case SpvOpcode::TypeBool:
			spv->update(_instruction.result, SpvReflection::TypeId::Bool);
			break;

		case SpvOpcode::TypeInt:
			spv->update(_instruction.result
				, 32 == _instruction.operand[0].data
				?	0 == _instruction.operand[1].data
					? SpvReflection::TypeId::Uint32
					: SpvReflection::TypeId::Int32
				:	0 == _instruction.operand[1].data
					? SpvReflection::TypeId::Uint64
					: SpvReflection::TypeId::Int64
				);
			break;

		case SpvOpcode::TypeFloat:
			spv->update(_instruction.result
				, 32 == _instruction.operand[0].data
				? SpvReflection::TypeId::Float
				: SpvReflection::TypeId::Double
				);
			break;

		case SpvOpcode::TypeVector:
			spv->update(_instruction.result
				, SpvReflection::TypeId::Vector
				, _instruction.operand[0].data
				, _instruction.operand[1].data
				);
			break;

		case SpvOpcode::TypeMatrix:
			spv->update(_instruction.result
				, SpvReflection::TypeId::Matrix
				, _instruction.operand[0].data
				, _instruction.operand[1].data
				);
			break;

		case SpvOpcode::TypeImage:
		case SpvOpcode::TypeSampler:
		case SpvOpcode::TypeSampledImage:
			break;

		case SpvOpcode::TypeStruct:
			for (uint32_t ii = 0, num = _instruction.numOperands; ii < num; ++ii)
			{
				SpvReflection::Id::Variable& var = spv->get(_instruction.result, ii);
				var.type = _instruction.operand[ii].data;
			}
			break;

		default:
			break;
		}

		return true;
	}

	void disassemble(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err)
	{
		BX_UNUSED(_writer);

		uint32_t magic;
		bx::peek(_reader, magic);

		SpvReflection spvx;

		if (magic == SPV_CHUNK_HEADER)
		{
			SpirV spirv;
			read(_reader, spirv, _err);
			parse(spirv.shader, spvParse, &spvx, _err);

			for (SpvReflection::IdMap::const_iterator it = spvx.idMap.begin(), itEnd = spvx.idMap.end(); it != itEnd; ++it)
			{
				const SpvReflection::Id& id = it->second;
				uint32_t num = uint32_t(id.members.size() );
				if (0 < num
				&&  0 != strcmp(id.var.name.c_str(), "gl_PerVertex") )
				{
					printf("%3d: %s %d %s\n"
						, it->first
						, id.var.name.c_str()
						, id.var.location
						, getName(id.var.storageClass)
						);
					printf("{\n");
					for (uint32_t ii = 0; ii < num; ++ii)
					{
						const SpvReflection::Id::Variable& var = id.members[ii];
						printf("\t\t%s %s %d %s\n"
							, spvx.getTypeName(var.type).c_str()
							, var.name.c_str()
							, var.offset
							, getName(var.storageClass)
							);
					}
					printf("}\n");
				}
			}

		}
	}

	struct DebugOutputWriter : public bx::WriterI
	{
		virtual int32_t write(const void* _data, int32_t _size, bx::Error*) BX_OVERRIDE
		{
			char* out = (char*)alloca(_size + 1);
			memcpy(out, _data, _size);
			out[_size] = '\0';
			printf("%s", out);
			return _size;
		}
	};

	static EShLanguage getLang(char _p)
	{
		switch (_p)
		{
		case 'c': return EShLangCompute;
		case 'f': return EShLangFragment;
		default:  break;
		}

		return EShLangVertex;
	}

//	static void printError(spv_message_level_t, const char*, const spv_position_t&, const char* _message)
//	{
//		fprintf(stderr, "%s\n", _message);
//	}

	static bool compile(bx::CommandLine& _cmdLine, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		BX_UNUSED(_cmdLine, _version, _code, _writer);

		const char* profile = _cmdLine.findOption('p', "profile");
		if (NULL == profile)
		{
			fprintf(stderr, "Error: Shader profile must be specified.\n");
			return false;
		}

		glslang::InitializeProcess();

		glslang::TProgram* program = new glslang::TProgram;

		EShLanguage stage = getLang(profile[0]);
		glslang::TShader* shader = new glslang::TShader(stage);

		EShMessages messages = EShMessages(0
			| EShMsgDefault
			| EShMsgReadHlsl
			| EShMsgVulkanRules
			| EShMsgSpvRules
			);

		const char* shaderStrings[] = { _code.c_str() };
		const char* shaderNames[]   = { "" };

		shader->setStringsWithLengthsAndNames(
			  shaderStrings
			, NULL
			, shaderNames
			, BX_COUNTOF(shaderNames)
			);
		bool compiled = shader->parse(&resourceLimits
			, 110
			, false
			, messages
			);
		bool linked = false;
		bool validated = true;
		bool optimized = true;

		if (!compiled)
		{
			const char* log = shader->getInfoLog();
			if (NULL != log)
			{
				int32_t source  = 0;
				int32_t line    = 0;
				int32_t column  = 0;
				int32_t start   = 0;
				int32_t end     = INT32_MAX;

				const char* err = strstr(log, "ERROR:");

				bool found = false;

				if (NULL != err)
				{
					found = 2 == sscanf(err, "ERROR: %u:%u: '", &source, &line);
					if (found)
					{
						++line;
					}
				}

				if (found)
				{
					start = bx::uint32_imax(1, line-10);
					end   = start + 20;
				}

				printCode(_code.c_str(), line, start, end, column);

				fprintf(stderr, "%s\n", log);
			}
		}
		else
		{
			program->addShader(shader);
			linked = true
				&& program->link(messages)
				&& program->mapIO()
				;

			if (!linked)
			{
				const char* log = program->getInfoLog();
				if (NULL != log)
				{
					fprintf(stderr, "%s\n", log);
				}
			}
			else
			{
				program->buildReflection();
				{
					uint16_t count = (uint16_t)program->getNumLiveUniformVariables();
					bx::write(_writer, count);

					uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
					for (uint16_t ii = 0; ii < count; ++ii)
					{
						Uniform un;
						un.name = program->getUniformName(ii);
						switch (program->getUniformType(ii))
						{
						case 0x1404: // GL_INT:
							un.type = UniformType::Int1;
							break;
						case 0x8B52: // GL_FLOAT_VEC4:
							un.type = UniformType::Vec4;
							break;
						case 0x8B5B: // GL_FLOAT_MAT3:
							un.type = UniformType::Mat3;
							break;
						case 0x8B5C: // GL_FLOAT_MAT4:
							un.type = UniformType::Mat4;
							break;
						default:
							un.type = UniformType::End;
							break;
						}
						un.num = program->getUniformArraySize(ii);
						un.regIndex = 0;
						un.regCount = un.num;

						uint8_t nameSize = (uint8_t)un.name.size();
						bx::write(_writer, nameSize);
						bx::write(_writer, un.name.c_str(), nameSize);
						uint8_t type = un.type | fragmentBit;
						bx::write(_writer, type);
						bx::write(_writer, un.num);
						bx::write(_writer, un.regIndex);
						bx::write(_writer, un.regCount);

						BX_TRACE("%s, %s, %d, %d, %d"
							, un.name.c_str()
							, getUniformTypeName(un.type)
							, un.num
							, un.regIndex
							, un.regCount
						);
					}
				}
				program->dumpReflection();

				BX_UNUSED(spv::MemorySemanticsAllMemory);

				glslang::TIntermediate* intermediate = program->getIntermediate(stage);
				std::vector<uint32_t> spirv;
				glslang::GlslangToSpv(*intermediate, spirv);
				spv::spirvbin_t spvBin;
				spvBin.remap(
					  spirv
					, 0
					| spv::spirvbin_t::DCE_ALL
					| spv::spirvbin_t::OPT_ALL
					| spv::spirvbin_t::MAP_ALL
//					| spv::spirvbin_t::STRIP
					);

				bx::Error err;
				DebugOutputWriter writer;
				bx::MemoryReader reader(spirv.data(), uint32_t(spirv.size()*4) );
				disassemble(&writer, &reader, &err);

#if 0
				spvtools::SpirvTools tools(SPV_ENV_VULKAN_1_0);
				tools.SetMessageConsumer(printError);
				validated = tools.Validate(spirv);

				if (!validated)
				{
					std::string out;
					tools.Disassemble(spirv, &out);
					printf("%s\n", out.c_str());
				}

				if (validated)
				{
					spvtools::Optimizer optm(SPV_ENV_VULKAN_1_0);
					optm.SetMessageConsumer(printError);
					optm
						.RegisterPass(spvtools::CreateStripDebugInfoPass() )
//						.RegisterPass(spvtools::CreateSetSpecConstantDefaultValuePass({ {1, "42" } }) )
						.RegisterPass(spvtools::CreateFreezeSpecConstantValuePass() )
						.RegisterPass(spvtools::CreateFoldSpecConstantOpAndCompositePass() )
						.RegisterPass(spvtools::CreateEliminateDeadConstantPass() )
						.RegisterPass(spvtools::CreateUnifyConstantPass() )
						;
					optimized = optm.Run(spirv.data(), spirv.size(), &spirv);
				}
#endif // 0

				if (optimized)
				{
					uint16_t shaderSize = (uint16_t)spirv.size()*sizeof(uint32_t);
					bx::write(_writer, shaderSize);
					bx::write(_writer, spirv.data(), shaderSize);
					uint8_t nul = 0;
					bx::write(_writer, nul);
				}
			}
		}

		delete program;
		delete shader;

		glslang::FinalizeProcess();

		return compiled && linked && validated && optimized;
	}

} // namespace spirv

	bool compileSPIRVShader(bx::CommandLine& _cmdLine, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		return spirv::compile(_cmdLine, _version, _code, _writer);
	}

} // namespace bgfx

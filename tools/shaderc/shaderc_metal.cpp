/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: 'inclusionDepth' : unreferenced formal parameter
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4265) // error C4265: 'spv::spirvbin_t': class has virtual functions, but destructor is not virtual
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow") // warning: declaration of 'userData' shadows a member of 'glslang::TShader::Includer::IncludeResult'
#define ENABLE_OPT 1
#include <ShaderLang.h>
#include <ResourceLimits.h>
#include <SPIRV/SPVRemapper.h>
#include <SPIRV/GlslangToSpv.h>
#define SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS
#include <spirv_msl.hpp>
#include <spirv_reflect.hpp>
#include <spirv-tools/optimizer.hpp>
BX_PRAGMA_DIAGNOSTIC_POP()

namespace bgfx
{
	struct TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};

} // namespace bgfx

#define TINYSTL_ALLOCATOR bgfx::TinyStlAllocator
#include <tinystl/allocator.h>
#include <tinystl/string.h>
#include <tinystl/unordered_map.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

#include "../../src/shader_spirv.h"

namespace bgfx { namespace metal
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
		0,     // maxMeshOutputVerticesNV;
		0,     // maxMeshOutputPrimitivesNV;
		0,     // maxMeshWorkGroupSizeX_NV;
		0,     // maxMeshWorkGroupSizeY_NV;
		0,     // maxMeshWorkGroupSizeZ_NV;
		0,     // maxTaskWorkGroupSizeX_NV;
		0,     // maxTaskWorkGroupSizeY_NV;
		0,     // maxTaskWorkGroupSizeZ_NV;
		0,     // maxMeshViewCountNV

		{ // limits
			true, // nonInductiveForLoops
			true, // whileLoops
			true, // doWhileLoops
			true, // generalUniformIndexing
			true, // generalAttributeMatrixVectorIndexing
			true, // generalVaryingIndexing
			true, // generalSamplerIndexing
			true, // generalVariableIndexing
			true, // generalConstantMatrixVectorIndexing
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

#define DBG(...) // bx::debugPrintf(__VA_ARGS__)

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
				&&  0 != bx::strCmp(id.var.name.c_str(), "gl_PerVertex") )
				{
					DBG("%3d: %s %d %s\n"
						, it->first
						, id.var.name.c_str()
						, id.var.location
						, getName(id.var.storageClass)
						);
					DBG("{\n");
					for (uint32_t ii = 0; ii < num; ++ii)
					{
						const SpvReflection::Id::Variable& var = id.members[ii];
						DBG("\t\t%s %s %d %s\n"
							, spvx.getTypeName(var.type).c_str()
							, var.name.c_str()
							, var.offset
							, getName(var.storageClass)
							);
						BX_UNUSED(var);
					}
					DBG("}\n");
				}
			}

		}
	}

	static EShLanguage getLang(char _p)
	{
		switch (_p)
		{
		case 'c': return EShLangCompute;
		case 'f': return EShLangFragment;
		case 'v': return EShLangVertex;
		default:  return EShLangCount;
		}
	}

	static const char* s_attribName[] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_bitangent",
		"a_color0",
		"a_color1",
		"a_color2",
		"a_color3",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};
	BX_STATIC_ASSERT(bgfx::Attrib::Count == BX_COUNTOF(s_attribName) );

	bgfx::Attrib::Enum toAttribEnum(const bx::StringView& _name)
	{
		for (uint8_t ii = 0; ii < Attrib::Count; ++ii)
		{
			if (0 == bx::strCmp(s_attribName[ii], _name) )
			{
				return bgfx::Attrib::Enum(ii);
			}
		}

		return bgfx::Attrib::Count;
	}

	static const char* s_samplerTypes[] =
	{
		"BgfxSampler2D",
		"BgfxISampler2D",
		"BgfxUSampler2D",
		"BgfxSampler2DArray",
		"BgfxSampler2DShadow",
		"BgfxSampler2DArrayShadow",
		"BgfxSampler3D",
		"BgfxISampler3D",
		"BgfxUSampler3D",
		"BgfxSamplerCube",
		"BgfxSamplerCubeShadow",
		"BgfxSampler2DMS",
	};

	static uint16_t writeUniformArray(bx::WriterI* _writer, const UniformArray& uniforms, bool isFragmentShader)
	{
		uint16_t size = 0;

		uint16_t count = static_cast<uint16_t>(uniforms.size());
		bx::write(_writer, count);

		uint32_t fragmentBit = isFragmentShader ? BGFX_UNIFORM_FRAGMENTBIT : 0;
		for (uint16_t ii = 0; ii < count; ++ii)
		{
			const Uniform& un = uniforms[ii];

			size += un.regCount*16;

			uint8_t nameSize = (uint8_t)un.name.size();
			bx::write(_writer, nameSize);
			bx::write(_writer, un.name.c_str(), nameSize);
			bx::write(_writer, uint8_t(un.type | fragmentBit));
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
		return size;
	}

	static bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
	{
		BX_UNUSED(_version);

		glslang::InitializeProcess();

		glslang::TProgram* program = new glslang::TProgram;

		EShLanguage stage = getLang(_options.shaderType);
		if (EShLangCount == stage)
		{
			bx::printf("Error: Unknown shader type '%c'.\n", _options.shaderType);
			return false;
		}
		glslang::TShader* shader = new glslang::TShader(stage);

		EShMessages messages = EShMessages(0
			| EShMsgDefault
			| EShMsgReadHlsl
			| EShMsgVulkanRules
			| EShMsgSpvRules
			);

		shader->setEntryPoint("main");
		shader->setAutoMapBindings(true);
		const int textureBindingOffset = 16;
		shader->setShiftBinding(glslang::EResTexture, textureBindingOffset);
		shader->setShiftBinding(glslang::EResSampler, textureBindingOffset);
		shader->setShiftBinding(glslang::EResImage, textureBindingOffset);

		const char* shaderStrings[] = { _code.c_str() };
		shader->setStrings(
			  shaderStrings
			, BX_COUNTOF(shaderStrings)
			);
		bool compiled = shader->parse(&resourceLimits
			, 110
			, false
			, messages
			);
		bool linked = false;
		bool validated = true;

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

				bx::StringView err = bx::strFind(log, "ERROR:");

				bool found = false;

				if (!err.isEmpty() )
				{
					found = 2 == sscanf(err.getPtr(), "ERROR: %u:%u: '", &source, &line);
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

				bx::printf("%s\n", log);
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
					bx::printf("%s\n", log);
				}
			}
			else
			{
				program->buildReflection();

				if (_firstPass)
				{
					// first time through, we just find unused uniforms and get rid of them
					std::string output;
					bx::Error err;
					LineReader reader(_code.c_str() );
					while (err.isOk() )
					{
						char str[4096];
						int32_t len = bx::read(&reader, str, BX_COUNTOF(str), &err);
						if (err.isOk() )
						{
							std::string strLine(str, len);

							size_t index = strLine.find("uniform ");
							if (index != std::string::npos)
							{
								bool found = false;

								for (uint32_t ii = 0; ii < BX_COUNTOF(s_samplerTypes); ++ii)
								{
									if (!bx::findIdentifierMatch(strLine.c_str(), s_samplerTypes[ii]).isEmpty())
									{
										found = true;
										break;
									}
								}

								if (!found)
								{
									for (int32_t ii = 0, num = program->getNumLiveUniformVariables(); ii < num; ++ii)
									{
										// matching lines like:  uniform u_name;
										// we want to replace "uniform" with "static" so that it's no longer
										// included in the uniform blob that the application must upload
										// we can't just remove them, because unused functions might still reference
										// them and cause a compile error when they're gone
										if (!bx::findIdentifierMatch(strLine.c_str(), program->getUniformName(ii)).isEmpty())
										{
											found = true;
											break;
										}
									}
								}

								if (!found)
								{
									strLine = strLine.replace(index, 7 /* uniform */, "static");
								}
							}

							output += strLine;
						}
					}

					// recompile with the unused uniforms converted to statics
					return compile(_options, _version, output.c_str(), _writer, false);
				}

				UniformArray uniforms;

				{
					uint16_t count = (uint16_t)program->getNumLiveUniformVariables();

					for (uint16_t ii = 0; ii < count; ++ii)
					{
						Uniform un;
						un.name = program->getUniformName(ii);

						un.num = uint8_t(program->getUniformArraySize(ii) );
						const uint32_t offset = program->getUniformBufferOffset(ii);
						un.regIndex = uint16_t(offset);
						un.regCount = un.num;

						switch (program->getUniformType(ii))
						{
						case 0x1404: // GL_INT:
							un.type = UniformType::Sampler;
							break;
						case 0x8B52: // GL_FLOAT_VEC4:
							un.type = UniformType::Vec4;
							break;
						case 0x8B5B: // GL_FLOAT_MAT3:
							un.type = UniformType::Mat3;
							un.regCount *= 3;
							break;
						case 0x8B5C: // GL_FLOAT_MAT4:
							un.type = UniformType::Mat4;
							un.regCount *= 4;
							break;
						default:
							un.type = UniformType::End;
							break;
						}

						uniforms.push_back(un);
					}
				}
				if (g_verbose)
				{
					program->dumpReflection();
				}

				BX_UNUSED(spv::MemorySemanticsAllMemory);

				glslang::TIntermediate* intermediate = program->getIntermediate(stage);
				std::vector<uint32_t> spirv;

				glslang::SpvOptions options;
				options.disableOptimizer = false;

				glslang::GlslangToSpv(*intermediate, spirv, &options);

				spvtools::Optimizer opt(SPV_ENV_VULKAN_1_0);

				auto print_msg_to_stderr = [](
					  spv_message_level_t
					, const char*
					, const spv_position_t&
					, const char* m
					)
				{
					bx::printf("Error: %s\n", m);
				};

				opt.SetMessageConsumer(print_msg_to_stderr);

				opt.RegisterLegalizationPasses();

				spvtools::ValidatorOptions validatorOptions;
				validatorOptions.SetBeforeHlslLegalization(true);

				if (!opt.Run(
					  spirv.data()
					, spirv.size()
					, &spirv
					, validatorOptions
					, false
					) )
				{
					compiled = false;
				}
				else
				{
					bx::Error err;
					bx::WriterI* writer = bx::getDebugOut();
					bx::MemoryReader reader(spirv.data(), uint32_t(spirv.size()*4) );
					disassemble(writer, &reader, &err);

					spirv_cross::CompilerReflection refl(spirv);
					spirv_cross::ShaderResources resourcesrefl = refl.get_shader_resources();

					// Loop through the separate_images, and extract the uniform names:
					for (auto &resource : resourcesrefl.separate_images)
					{
						std::string name = refl.get_name(resource.id);
						if (name.size() > 7 && 0 == bx::strCmp(name.c_str() + name.length() - 7, "Texture") )
						{
							auto uniform_name = name.substr(0, name.length() - 7);

							Uniform un;
							un.name = uniform_name;
							un.type = UniformType::Sampler;

							un.num = 0;			// needed?
							un.regIndex = 0;	// needed?
							un.regCount = 0;	// needed?

							uniforms.push_back(un);
						}
					}
					uint16_t size = writeUniformArray( _writer, uniforms, _options.shaderType == 'f');

					if (_version == BX_MAKEFOURCC('M', 'T', 'L', 0))
					{
						if (g_verbose)
						{
							glslang::SpirvToolsDisassemble(std::cout, spirv);
						}

						spirv_cross::CompilerMSL msl(std::move(spirv));

						auto executionModel = msl.get_execution_model();
						spirv_cross::MSLResourceBinding newBinding;
						newBinding.stage = executionModel;

						spirv_cross::ShaderResources resources = msl.get_shader_resources();

						spirv_cross::SmallVector<spirv_cross::EntryPoint> entryPoints = msl.get_entry_points_and_stages();
						if (!entryPoints.empty())
							msl.rename_entry_point(entryPoints[0].name, "xlatMtlMain", entryPoints[0].execution_model);

						for (auto &resource : resources.uniform_buffers)
						{
							unsigned set = msl.get_decoration( resource.id, spv::DecorationDescriptorSet );
							unsigned binding = msl.get_decoration( resource.id, spv::DecorationBinding );
							newBinding.desc_set = set;
							newBinding.binding = binding;
							newBinding.msl_buffer = 0;
							msl.add_msl_resource_binding( newBinding );

							msl.set_name(resource.id, "_mtl_u");
						}

						for (auto &resource : resources.storage_buffers)
						{
							unsigned set = msl.get_decoration( resource.id, spv::DecorationDescriptorSet );
							unsigned binding = msl.get_decoration( resource.id, spv::DecorationBinding );
							newBinding.desc_set = set;
							newBinding.binding = binding;
							newBinding.msl_buffer = binding + 1;
							msl.add_msl_resource_binding( newBinding );
						}

						for (auto &resource : resources.separate_samplers)
						{
							unsigned set = msl.get_decoration( resource.id, spv::DecorationDescriptorSet );
							unsigned binding = msl.get_decoration( resource.id, spv::DecorationBinding );
							newBinding.desc_set = set;
							newBinding.binding = binding;
							newBinding.msl_texture = binding - textureBindingOffset;
							newBinding.msl_sampler = binding - textureBindingOffset;
							msl.add_msl_resource_binding( newBinding );
						}

						for (auto &resource : resources.separate_images)
						{
							std::string name = msl.get_name(resource.id);
							if (name.size() > 7 && 0 == bx::strCmp(name.c_str() + name.length() - 7, "Texture") )
								msl.set_name(resource.id, name.substr(0, name.length() - 7));

							unsigned set = msl.get_decoration( resource.id, spv::DecorationDescriptorSet );
							unsigned binding = msl.get_decoration( resource.id, spv::DecorationBinding );
							newBinding.desc_set = set;
							newBinding.binding = binding;
							newBinding.msl_texture = binding - textureBindingOffset;
							newBinding.msl_sampler = binding - textureBindingOffset;
							msl.add_msl_resource_binding( newBinding );
						}

						for (auto &resource : resources.storage_images)
						{
							std::string name = msl.get_name(resource.id);
							if (name.size() > 7 && 0 == bx::strCmp(name.c_str() + name.length() - 7, "Texture") )
								msl.set_name(resource.id, name.substr(0, name.length() - 7));

							unsigned set = msl.get_decoration( resource.id, spv::DecorationDescriptorSet );
							unsigned binding = msl.get_decoration( resource.id, spv::DecorationBinding );
							newBinding.desc_set = set;
							newBinding.binding = binding;
							newBinding.msl_texture = binding - textureBindingOffset;
							newBinding.msl_sampler = binding - textureBindingOffset;
							msl.add_msl_resource_binding( newBinding );
						}

						std::string source = msl.compile();

						if ('c' == _options.shaderType)
						{
							for (int i = 0; i < 3; ++i)
							{
								uint16_t dim = (uint16_t)msl.get_execution_mode_argument(spv::ExecutionMode::ExecutionModeLocalSize, i);
								bx::write(_writer, dim);
							}
						}

						uint32_t shaderSize = (uint32_t)source.size();
						bx::write(_writer, shaderSize);
						bx::write(_writer, source.c_str(), shaderSize);
						uint8_t nul = 0;
						bx::write(_writer, nul);
					}
					else
					{
						uint32_t shaderSize = (uint32_t)spirv.size() * sizeof(uint32_t);
						bx::write(_writer, shaderSize);
						bx::write(_writer, spirv.data(), shaderSize);
						uint8_t nul = 0;
						bx::write(_writer, nul);
					}
					//
					const uint8_t numAttr = (uint8_t)program->getNumLiveAttributes();
					bx::write(_writer, numAttr);

					for (uint8_t ii = 0; ii < numAttr; ++ii)
					{
						bgfx::Attrib::Enum attr = toAttribEnum(program->getAttributeName(ii) );
						if (bgfx::Attrib::Count != attr)
						{
							bx::write(_writer, bgfx::attribToId(attr) );
						}
						else
						{
							bx::write(_writer, uint16_t(UINT16_MAX) );
						}
					}

					bx::write(_writer, size);
				}
			}
		}

		delete program;
		delete shader;

		glslang::FinalizeProcess();

		return compiled && linked && validated;
	}

} // namespace metal

	bool compileMetalShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		return metal::compile(_options, _version, _code, _writer, true);
	}

} // namespace bgfx

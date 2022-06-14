/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "shaderc.h"

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: 'inclusionDepth' : unreferenced formal parameter
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4265) // error C4265: 'spv::spirvbin_t': class has virtual functions, but destructor is not virtual
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wattributes") // warning: attribute ignored
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wdeprecated-declarations") // warning: ‘MSLVertexAttr’ is deprecated
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits") // warning: comparison of unsigned expression in ‘< 0’ is always false
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow") // warning: declaration of 'userData' shadows a member of 'glslang::TShader::Includer::IncludeResult'
#define ENABLE_OPT 1
#include <ShaderLang.h>
#include <ResourceLimits.h>
#include <SPIRV/SPVRemapper.h>
#include <SPIRV/GlslangToSpv.h>
#include <webgpu/webgpu_cpp.h>
#define SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS
#include <spirv_msl.hpp>
#include <spirv_reflect.hpp>
#include <spirv-tools/optimizer.hpp>
BX_PRAGMA_DIAGNOSTIC_POP()

namespace bgfx
{
	static bx::DefaultAllocator s_allocator;
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

#include "../../src/shader.h"
#include "../../src/shader_spirv.h"
#include "../../3rdparty/khronos/vulkan-local/vulkan.h"

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
		0,     // maxMeshOutputVerticesNV
		0,     // maxMeshOutputPrimitivesNV
		0,     // maxMeshWorkGroupSizeX_NV
		0,     // maxMeshWorkGroupSizeY_NV
		0,     // maxMeshWorkGroupSizeZ_NV
		0,     // maxTaskWorkGroupSizeX_NV
		0,     // maxTaskWorkGroupSizeY_NV
		0,     // maxTaskWorkGroupSizeZ_NV
		0,     // maxMeshViewCountNV
		0,     // maxDualSourceDrawBuffersEXT

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

	bgfx::TextureComponentType::Enum SpirvCrossBaseTypeToFormatType(spirv_cross::SPIRType::BaseType spirvBaseType, bool depth)
	{
		if (depth)
			return bgfx::TextureComponentType::Depth;

		switch (spirvBaseType)
		{
		case spirv_cross::SPIRType::Float:
			return bgfx::TextureComponentType::Float;
		case spirv_cross::SPIRType::Int:
			return bgfx::TextureComponentType::Int;
		case spirv_cross::SPIRType::UInt:
			return bgfx::TextureComponentType::Uint;
		default:
		    return bgfx::TextureComponentType::Float;
		}
	}

	bgfx::TextureDimension::Enum SpirvDimToTextureViewDimension(spv::Dim _dim, bool _arrayed)
	{
		switch (_dim)
		{
		case spv::Dim::Dim1D:
			return bgfx::TextureDimension::Dimension1D;
		case spv::Dim::Dim2D:
			return _arrayed
				? bgfx::TextureDimension::Dimension2DArray
				: bgfx::TextureDimension::Dimension2D
				;
		case spv::Dim::Dim3D:
			return bgfx::TextureDimension::Dimension3D;
		case spv::Dim::DimCube:
			return _arrayed
				? bgfx::TextureDimension::DimensionCubeArray
				: bgfx::TextureDimension::DimensionCube
				;
		default:
			BX_ASSERT(false, "Unknown texture dimension %d", _dim);
			return bgfx::TextureDimension::Dimension2D;
		}
	}

	static bgfx::TextureFormat::Enum s_textureFormats[] =
	{
		bgfx::TextureFormat::Unknown,   // spv::ImageFormatUnknown = 0
		bgfx::TextureFormat::RGBA32F,   // spv::ImageFormatRgba32f = 1
		bgfx::TextureFormat::RGBA16F,   // spv::ImageFormatRgba16f = 2
		bgfx::TextureFormat::R32F,      // spv::ImageFormatR32f = 3
		bgfx::TextureFormat::RGBA8,     // spv::ImageFormatRgba8 = 4
		bgfx::TextureFormat::RGBA8S,    // spv::ImageFormatRgba8Snorm = 5
		bgfx::TextureFormat::RG32F,     // spv::ImageFormatRg32f = 6
		bgfx::TextureFormat::RG16F,     // spv::ImageFormatRg16f = 7
		bgfx::TextureFormat::RG11B10F,  // spv::ImageFormatR11fG11fB10f = 8
		bgfx::TextureFormat::R16F,      // spv::ImageFormatR16f = 9
		bgfx::TextureFormat::RGBA16,    // spv::ImageFormatRgba16 = 10
		bgfx::TextureFormat::RGB10A2,   // spv::ImageFormatRgb10A2 = 11
		bgfx::TextureFormat::RG16,      // spv::ImageFormatRg16 = 12
		bgfx::TextureFormat::RG8,       // spv::ImageFormatRg8 = 13
		bgfx::TextureFormat::R16,       // spv::ImageFormatR16 = 14
		bgfx::TextureFormat::R8,        // spv::ImageFormatR8 = 15
		bgfx::TextureFormat::RGBA16S,   // spv::ImageFormatRgba16Snorm = 16
		bgfx::TextureFormat::RG16S,     // spv::ImageFormatRg16Snorm = 17
		bgfx::TextureFormat::RG8S,      // spv::ImageFormatRg8Snorm = 18
		bgfx::TextureFormat::R16S,      // spv::ImageFormatR16Snorm = 19
		bgfx::TextureFormat::R8S,       // spv::ImageFormatR8Snorm = 20
		bgfx::TextureFormat::RGBA32I,   // spv::ImageFormatRgba32i = 21
		bgfx::TextureFormat::RGBA16I,   // spv::ImageFormatRgba16i = 22
		bgfx::TextureFormat::RGBA8I,    // spv::ImageFormatRgba8i = 23
		bgfx::TextureFormat::R32I,      // spv::ImageFormatR32i = 24
		bgfx::TextureFormat::RG32I,     // spv::ImageFormatRg32i = 25
		bgfx::TextureFormat::RG16I,     // spv::ImageFormatRg16i = 26
		bgfx::TextureFormat::RG8I,      // spv::ImageFormatRg8i = 27
		bgfx::TextureFormat::R16I,      // spv::ImageFormatR16i = 28
		bgfx::TextureFormat::R8I,       // spv::ImageFormatR8i = 29
		bgfx::TextureFormat::RGBA32U,   // spv::ImageFormatRgba32ui = 30
		bgfx::TextureFormat::RGBA16U,   // spv::ImageFormatRgba16ui = 31
		bgfx::TextureFormat::RGBA8U,    // spv::ImageFormatRgba8ui = 32
		bgfx::TextureFormat::R32U,      // spv::ImageFormatR32ui = 33
		bgfx::TextureFormat::Unknown,   // spv::ImageFormatRgb10a2ui = 34
		bgfx::TextureFormat::RG32U,     // spv::ImageFormatRg32ui = 35
		bgfx::TextureFormat::RG16U,     // spv::ImageFormatRg16ui = 36
		bgfx::TextureFormat::RG8U,      // spv::ImageFormatRg8ui = 37
		bgfx::TextureFormat::R16U,      // spv::ImageFormatR16ui = 38
		bgfx::TextureFormat::R8U,       // spv::ImageFormatR8ui = 39
		bgfx::TextureFormat::Unknown,   // spv::ImageFormatR64ui = 40
		bgfx::TextureFormat::Unknown,   // spv::ImageFormatR64i = 41
	};

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

		bx::ErrorAssert err;

		uint16_t count = uint16_t(uniforms.size());
		bx::write(_writer, count, &err);

		uint32_t fragmentBit = isFragmentShader ? kUniformFragmentBit : 0;

		for (uint16_t ii = 0; ii < count; ++ii)
		{
			const Uniform& un = uniforms[ii];

			if ( (un.type & ~kUniformMask) > UniformType::End)
			{
				size = bx::max(size, (uint16_t)(un.regIndex + un.regCount*16) );
			}

			uint8_t nameSize = (uint8_t)un.name.size();
			bx::write(_writer, nameSize, &err);
			bx::write(_writer, un.name.c_str(), nameSize, &err);
			bx::write(_writer, uint8_t(un.type | fragmentBit), &err);
			bx::write(_writer, un.num, &err);
			bx::write(_writer, un.regIndex, &err);
			bx::write(_writer, un.regCount, &err);
			bx::write(_writer, un.texComponent, &err);
			bx::write(_writer, un.texDimension, &err);
			bx::write(_writer, un.texFormat, &err);

			BX_TRACE("%s, %s, %d, %d, %d"
				, un.name.c_str()
				, getUniformTypeName(UniformType::Enum(un.type & ~kUniformMask))
				, un.num
				, un.regIndex
				, un.regCount
				);
		}
		return size;
	}

	static spv_target_env getSpirvTargetVersion(uint32_t version)
	{
		switch (version)
		{
			case 1010:
				return SPV_ENV_VULKAN_1_0;
			case 1311:
				return SPV_ENV_VULKAN_1_1;
			case 1411:
				return SPV_ENV_VULKAN_1_1_SPIRV_1_4;
			case 1512:
				return SPV_ENV_VULKAN_1_2;
			default:
				BX_ASSERT(0, "Unknown SPIR-V version requested. Returning SPV_ENV_VULKAN_1_0 as default.");
				return SPV_ENV_VULKAN_1_0;
		}
	}

	static glslang::EShTargetClientVersion getGlslangTargetVulkanVersion(uint32_t version)
	{
		switch (version)
		{
			case 1010:
				return glslang::EShTargetVulkan_1_0;
			case 1311:
			case 1411:
				return glslang::EShTargetVulkan_1_1;
			case 1512:
				return glslang::EShTargetVulkan_1_2;
			default:
				BX_ASSERT(0, "Unknown SPIR-V version requested. Returning EShTargetVulkan_1_0 as default.");
				return glslang::EShTargetVulkan_1_0;
		}
	}

	static glslang::EShTargetLanguageVersion getGlslangTargetSpirvVersion(uint32_t version)
	{
		switch (version)
		{
			case 1010:
				return glslang::EShTargetSpv_1_0;
			case 1311:
				return glslang::EShTargetSpv_1_3;
			case 1411:
				return glslang::EShTargetSpv_1_4;
			case 1512:
				return glslang::EShTargetSpv_1_5;
			default:
				BX_ASSERT(0, "Unknown SPIR-V version requested. Returning EShTargetSpv_1_0 as default.");
				return glslang::EShTargetSpv_1_0;
		}
	}

	/// This is the value used to fill out GLSLANG's SpvVersion object.
	/// The required value is that which is defined by GL_KHR_vulkan_glsl, which is defined here:
	/// https://github.com/KhronosGroup/GLSL/blob/master/extensions/khr/GL_KHR_vulkan_glsl.txt
	/// The value is 100.
	constexpr int s_GLSL_VULKAN_CLIENT_VERSION = 100;

	static bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
	{
		BX_UNUSED(_version);

		glslang::InitializeProcess();

		EShLanguage stage = getLang(_options.shaderType);
		if (EShLangCount == stage)
		{
			bx::printf("Error: Unknown shader type '%c'.\n", _options.shaderType);
			return false;
		}

		glslang::TProgram* program = new glslang::TProgram;
		glslang::TShader* shader   = new glslang::TShader(stage);

		EShMessages messages = EShMessages(0
			| EShMsgDefault
			| EShMsgReadHlsl
			| EShMsgVulkanRules
			| EShMsgSpvRules
			);

		shader->setEntryPoint("main");
		shader->setAutoMapBindings(true);
		shader->setEnvInput(glslang::EShSourceHlsl, stage, glslang::EShClientVulkan, s_GLSL_VULKAN_CLIENT_VERSION);
		shader->setEnvClient(glslang::EShClientVulkan, getGlslangTargetVulkanVersion(_version));
		shader->setEnvTarget(glslang::EShTargetSpv, getGlslangTargetSpirvVersion(_version));

		// Reserve two spots for the stage UBOs
		shader->setShiftBinding(glslang::EResUbo, (stage == EShLanguage::EShLangFragment ? kSpirvFragmentBinding : kSpirvVertexBinding));
		shader->setShiftBinding(glslang::EResTexture, kSpirvBindShift);
		shader->setShiftBinding(glslang::EResSampler, kSpirvBindShift + kSpirvSamplerShift);
		shader->setShiftBinding(glslang::EResSsbo, kSpirvBindShift);
		shader->setShiftBinding(glslang::EResImage, kSpirvBindShift);

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

					struct Uniform
					{
						std::string name;
						std::string decl;
					};
					std::vector<Uniform> uniforms;

					bx::LineReader reader(_code.c_str() );
					while (!reader.isDone() )
					{
						bx::StringView strLine = reader.next();

						bool moved = false;

						bx::StringView str = strFind(strLine, "uniform ");
						if (!str.isEmpty() )
						{
							bool found = false;
							bool sampler = false;
							std::string name = "";

							// add to samplers

							for (uint32_t ii = 0; ii < BX_COUNTOF(s_samplerTypes); ++ii)
							{
								if (!bx::findIdentifierMatch(strLine, s_samplerTypes[ii]).isEmpty() )
								{
									found = true;
									sampler = true;
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
									if (!bx::findIdentifierMatch(strLine, program->getUniformName(ii) ).isEmpty() )
									{
										found = true;
										name = program->getUniformName(ii);
										break;
									}
								}
							}

							if (!found)
							{
								output.append(strLine.getPtr(), str.getPtr() );
								output += "static ";
								output.append(str.getTerm(), strLine.getTerm() );
								output += "\n";
								moved = true;
							}
							else if (!sampler)
							{
								Uniform uniform;
								uniform.name = name;
								uniform.decl = std::string(strLine.getPtr(), strLine.getTerm() );
								uniforms.push_back(uniform);
								moved = true;
							}
						}

						if (!moved)
						{
							output.append(strLine.getPtr(), strLine.getTerm() );
							output += "\n";
						}
					}

					std::string uniformBlock;
					uniformBlock += "cbuffer UniformBlock\n";
					uniformBlock += "{\n";

					for (const Uniform& uniform : uniforms)
					{
						uniformBlock += uniform.decl.substr(7 /* uniform */);
						uniformBlock += "\n";
					}

					uniformBlock += "};\n";

					output = uniformBlock + output;

					// recompile with the unused uniforms converted to statics
					delete program;
					delete shader;
					return compile(_options, _version, output.c_str(), _writer, false);
				}

				UniformArray uniforms;

				{
					uint16_t count = (uint16_t)program->getNumLiveUniformVariables();

					for (uint16_t ii = 0; ii < count; ++ii)
					{
						Uniform un;
						un.name = program->getUniformName(ii);

						if (bx::hasSuffix(un.name.c_str(), ".@data") )
						{
							continue;
						}

						un.num = 0;
						const uint32_t offset = program->getUniformBufferOffset(ii);
						un.regIndex = uint16_t(offset);
						un.regCount = uint16_t(program->getUniformArraySize(ii));

						switch (program->getUniformType(ii) )
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
							continue;
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

				spvtools::Optimizer opt(getSpirvTargetVersion(_version));

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
					if (g_verbose)
					{
						glslang::SpirvToolsDisassemble(std::cout, spirv, getSpirvTargetVersion(_version));
					}

					spirv_cross::CompilerReflection refl(spirv);
					spirv_cross::ShaderResources resourcesrefl = refl.get_shader_resources();

					// Loop through the separate_images, and extract the uniform names:
					for (auto &resource : resourcesrefl.separate_images)
					{
						std::string name = refl.get_name(resource.id);

						if (name.size() > 7
						&&  0 == bx::strCmp(name.c_str() + name.length() - 7, "Texture") )
						{
							name = name.substr(0, name.length() - 7);
						}

						uint32_t binding_index = refl.get_decoration(resource.id, spv::Decoration::DecorationBinding);

						auto imageType = refl.get_type(resource.base_type_id).image;
						auto componentType = refl.get_type(imageType.type).basetype;

						bool isCompareSampler = false;
						for (auto& sampler : resourcesrefl.separate_samplers)
						{
							if (binding_index + 16 == refl.get_decoration(sampler.id, spv::Decoration::DecorationBinding) )
							{
								std::string samplerName = refl.get_name(sampler.id);
								isCompareSampler = refl.variable_is_depth_or_compare(sampler.id) || samplerName.find("Comparison") != std::string::npos;
								break;
							}
						}

						Uniform un;
						un.name = name;
						un.type = UniformType::Enum(UniformType::Sampler
								| kUniformSamplerBit
								| (isCompareSampler ? kUniformCompareBit : 0)
								);

						un.texComponent = textureComponentTypeToId(SpirvCrossBaseTypeToFormatType(componentType, imageType.depth) );
						un.texDimension = textureDimensionToId(SpirvDimToTextureViewDimension(imageType.dim, imageType.arrayed) );
						un.texFormat = uint16_t(s_textureFormats[imageType.format]);

						un.regIndex = uint16_t(binding_index);
						un.regCount = 0; // unused

						uniforms.push_back(un);
					}

					// Loop through the storage_images, and extract the uniform names:
					for (auto &resource : resourcesrefl.storage_images)
					{
						std::string name = refl.get_name(resource.id);

						uint32_t binding_index = refl.get_decoration(resource.id, spv::Decoration::DecorationBinding);

						auto imageType = refl.get_type(resource.base_type_id).image;
						auto componentType = refl.get_type(imageType.type).basetype;

						spirv_cross::Bitset flags = refl.get_decoration_bitset(resource.id);
						UniformType::Enum type = flags.get(spv::DecorationNonWritable)
							? UniformType::Enum(kUniformReadOnlyBit | UniformType::End)
							: UniformType::End;

						Uniform un;
						un.name = name;
						un.type = type;

						un.texComponent = textureComponentTypeToId(SpirvCrossBaseTypeToFormatType(componentType, imageType.depth) );
						un.texDimension = textureDimensionToId(SpirvDimToTextureViewDimension(imageType.dim, imageType.arrayed) );
						un.texFormat = uint16_t(s_textureFormats[imageType.format]);

						un.regIndex = uint16_t(binding_index);
						un.regCount = descriptorTypeToId(DescriptorType::StorageImage);

						uniforms.push_back(un);
					}

					bx::Error err;

					// Loop through the storage buffer, and extract the uniform names:
					for (auto& resource : resourcesrefl.storage_buffers)
					{
						std::string name = refl.get_name(resource.id);

						uint32_t binding_index = refl.get_decoration(resource.id, spv::Decoration::DecorationBinding);

						spirv_cross::Bitset flags = refl.get_buffer_block_flags(resource.id);
						UniformType::Enum type = flags.get(spv::DecorationNonWritable)
							? UniformType::Enum(kUniformReadOnlyBit | UniformType::End)
							: UniformType::End;

						Uniform un;
						un.name = name;
						un.type = type;
						un.num = 0;
						un.regIndex = uint16_t(binding_index);
						un.regCount = descriptorTypeToId(DescriptorType::StorageBuffer);

						uniforms.push_back(un);
					}

					uint16_t size = writeUniformArray( _writer, uniforms, _options.shaderType == 'f');

					uint32_t shaderSize = (uint32_t)spirv.size() * sizeof(uint32_t);
					bx::write(_writer, shaderSize, &err);
					bx::write(_writer, spirv.data(), shaderSize, &err);
					uint8_t nul = 0;
					bx::write(_writer, nul, &err);

					const uint8_t numAttr = (uint8_t)program->getNumLiveAttributes();
					bx::write(_writer, numAttr, &err);

					for (uint8_t ii = 0; ii < numAttr; ++ii)
					{
						bgfx::Attrib::Enum attr = toAttribEnum(program->getAttributeName(ii) );
						if (bgfx::Attrib::Count != attr)
						{
							bx::write(_writer, bgfx::attribToId(attr), &err);
						}
						else
						{
							bx::write(_writer, uint16_t(UINT16_MAX), &err);
						}
					}

					bx::write(_writer, size, &err);
				}
			}
		}

		delete program;
		delete shader;

		glslang::FinalizeProcess();

		return compiled && linked && validated;
	}

} // namespace spirv

	bool compileSPIRVShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		return spirv::compile(_options, _version, _code, _writer, true);
	}

} // namespace bgfx

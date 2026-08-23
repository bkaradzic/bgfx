/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "shaderc.h"

#if SHADERC_CONFIG_HAS_GLSLANG

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: 'inclusionDepth' : unreferenced formal parameter
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4265) // error C4265: 'spv::spirvbin_t': class has virtual functions, but destructor is not virtual
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wattributes") // warning: attribute ignored
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wdeprecated-declarations")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow")
#define SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS
#include <spirv_common.hpp>
#include <spirv_glsl.hpp>

#define ENABLE_OPT 1
#include <ShaderLang.h>
#include <ResourceLimits.h>
#include <SPIRV/GlslangToSpv.h>
#include <spirv-tools/optimizer.hpp>
BX_PRAGMA_DIAGNOSTIC_POP()

namespace bgfx { namespace glsl
{
	static EShLanguage getLang(char _p)
	{
		switch (_p)
		{
		case 'c': return EShLangCompute;
		case 'f': return EShLangFragment;
		case 'v': return EShLangVertex;
		default:  break;
		}

		return EShLangCount;
	}

	static UniformType::Enum getUniformType(const spirv_cross::SPIRType& _type)
	{
		if (spirv_cross::SPIRType::Float != _type.basetype)
		{
			return UniformType::Count;
		}

		if (4 == _type.columns
		&&  4 == _type.vecsize)
		{
			return UniformType::Mat4;
		}

		if (3 == _type.columns
		&&  3 == _type.vecsize)
		{
			return UniformType::Mat3;
		}

		if (1 == _type.columns
		&&  4 == _type.vecsize)
		{
			return UniformType::Vec4;
		}

		return UniformType::Count;
	}

	static bool isDesktopOnlyFormat(spv::ImageFormat _format)
	{
		switch (_format)
		{
		case spv::ImageFormatR11fG11fB10f:
		case spv::ImageFormatR16f:
		case spv::ImageFormatRgb10A2:
		case spv::ImageFormatR8:
		case spv::ImageFormatRg8:
		case spv::ImageFormatR16:
		case spv::ImageFormatRg16:
		case spv::ImageFormatRgba16:
		case spv::ImageFormatR16Snorm:
		case spv::ImageFormatRg16Snorm:
		case spv::ImageFormatRgba16Snorm:
		case spv::ImageFormatR8Snorm:
		case spv::ImageFormatRg8Snorm:
		case spv::ImageFormatR8ui:
		case spv::ImageFormatRg8ui:
		case spv::ImageFormatR16ui:
		case spv::ImageFormatRgb10a2ui:
		case spv::ImageFormatR8i:
		case spv::ImageFormatRg8i:
		case spv::ImageFormatR16i:
			return true;

		default:
			break;
		}

		return false;
	}

	static bool compileSpirvCross(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _shaderWriter, bx::WriterI* _messageWriter)
	{
		bx::ErrorAssert messageErr;

		const bool     es      = 0 != (_version & 0x80000000);
		const uint32_t version = _version & ~0x80000000;

		const EShLanguage stage = getLang(_options.shaderType);

		if (EShLangCount == stage)
		{
			bx::write(_messageWriter, &messageErr, "Error: Unknown shader type '%c'.\n", _options.shaderType);
			return false;
		}

		glslang::InitializeProcess();

		glslang::TProgram* program = new glslang::TProgram;
		glslang::TShader*  shader  = new glslang::TShader(stage);

		const EShMessages messages = EShMessages(0
			| EShMsgDefault
			| EShMsgSpvRules
			);

		shader->setEntryPoint("main");
		shader->setAutoMapBindings(true);
		shader->setAutoMapLocations(true);
		shader->setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientOpenGL, 100);
		shader->setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
		shader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);

		const char* shaderStrings[] = { _code.c_str() };
		shader->setStrings(
			  shaderStrings
			, BX_COUNTOF(shaderStrings)
			);

		bool compiled = shader->parse(GetDefaultResources()
			, 110
			, false
			, messages
			);
		bool linked = false;
		bool result = false;

		if (!compiled)
		{
			const char* log = shader->getInfoLog();

			if (NULL != log)
			{
				int32_t source = 0;
				int32_t line   = 0;
				int32_t start  = 0;
				int32_t end    = INT32_MAX;

				const bx::StringView err = bx::strFind(log, "ERROR:");

				if (!err.isEmpty()
				&&  2 == sscanf(err.getPtr(), "ERROR: %u:%u: '", &source, &line) )
				{
					start = bx::max<int32_t>(1, line-10);
					end   = start + 20;
				}

				printCode(_code.c_str(), line, start, end, -1);

				bx::write(_messageWriter, &messageErr, "%s\n", log);
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
					bx::write(_messageWriter, &messageErr, "%s\n", log);
				}
			}
		}

		if (linked)
		{
			std::vector<uint32_t> spirv;

			glslang::SpvOptions spvOptions;
			spvOptions.disableOptimizer = true;

			glslang::GlslangToSpv(*program->getIntermediate(stage), spirv, &spvOptions);

			spvtools::Optimizer opt(SPV_ENV_OPENGL_4_5);

			opt.SetMessageConsumer(
				[_messageWriter, &messageErr](spv_message_level_t, const char*, const spv_position_t&, const char* _message)
				{
					bx::write(_messageWriter, &messageErr, "%s\n", _message);
				});

			opt.RegisterPerformancePasses();

			std::vector<uint32_t> optimized;

			if (opt.Run(spirv.data(), spirv.size(), &optimized) )
			{
				spirv = std::move(optimized);
			}

			spirv_cross::CompilerGLSL compiler(std::move(spirv) );

			spirv_cross::CompilerGLSL::Options compilerOptions = compiler.get_common_options();
			compilerOptions.version                            = version;
			compilerOptions.es                                 = es;
			compilerOptions.vulkan_semantics                   = false;
			compilerOptions.enable_420pack_extension           = false;
			compilerOptions.emit_uniform_buffer_as_plain_uniforms = true;
			compiler.set_common_options(compilerOptions);

			spirv_cross::ShaderResources resources = compiler.get_shader_resources();

			for (const spirv_cross::Resource& resource : resources.gl_plain_uniforms)
			{
				compiler.unset_decoration(resource.id, spv::DecorationLocation);
			}

			for (const spirv_cross::Resource& resource : resources.sampled_images)
			{
				compiler.unset_decoration(resource.id, spv::DecorationLocation);
				compiler.unset_decoration(resource.id, spv::DecorationBinding);
			}

			if ('v' == _options.shaderType)
			{
				for (const spirv_cross::Resource& resource : resources.stage_outputs)
				{
					compiler.unset_decoration(resource.id, spv::DecorationLocation);
				}
			}
			else if ('f' == _options.shaderType)
			{
				for (const spirv_cross::Resource& resource : resources.stage_inputs)
				{
					compiler.unset_decoration(resource.id, spv::DecorationLocation);
				}
			}

			if (es)
			{
				bool unsupported = false;

				for (const spirv_cross::Resource& resource : resources.storage_images)
				{
					const spirv_cross::SPIRType& type = compiler.get_type(resource.type_id);

					if (isDesktopOnlyFormat(type.image.format) )
					{
						bx::write(_messageWriter, &messageErr
							, "Error: Image '%s' uses a format that's not supported by ESSL.\n"
							, resource.name.c_str()
							);
						unsupported = true;
					}
				}

				if (unsupported)
				{
					delete program;
					delete shader;
					glslang::FinalizeProcess();
					return false;
				}
			}

			std::string source = compiler.compile();

			if (0 == source.compare(0, 8, "#version") )
			{
				const size_t eol = source.find('\n');
				source.erase(0, std::string::npos == eol ? source.size() : eol+1);
			}

			UniformArray uniforms;

			for (const spirv_cross::Resource& resource : resources.gl_plain_uniforms)
			{
				const spirv_cross::SPIRType& type = compiler.get_type(resource.type_id);

				Uniform un;
				un.name = compiler.get_name(resource.id);
				un.type = getUniformType(type);

				if (0 == bx::strCmp(un.name.c_str(), "bgfx_ndc") )
				{
					continue;
				}

				if (UniformType::Count == un.type)
				{
					continue;
				}

				un.num      = uint8_t(type.array.empty() ? 1 : type.array[0]);
				un.regIndex = 0;
				un.regCount = un.num;

				switch (un.type)
				{
				case UniformType::Mat3:
					un.regCount *= 3;
					break;

				case UniformType::Mat4:
					un.regCount *= 4;
					break;

				default:
					break;
				}

				BX_TRACE("name: %s (type %d, num %d)", un.name.c_str(), un.type, un.num);

				uniforms.push_back(un);
			}

			for (const spirv_cross::Resource& resource : resources.sampled_images)
			{
				const spirv_cross::SPIRType& type = compiler.get_type(resource.type_id);

				Uniform un;
				un.name         = compiler.get_name(resource.id);
				un.type         = UniformType::Sampler;
				un.num          = 1;
				un.regIndex     = 0;
				un.regCount     = 1;
				un.texDimension = spirvDimToTextureDimensionId(uint32_t(type.image.dim), type.image.arrayed);

				uniforms.push_back(un);
			}

			bx::ErrorAssert err;

			RawBindings().write(_shaderWriter, &err);

			uint16_t count = uint16_t(uniforms.size() );
			bx::write(_shaderWriter, count, &err);

			for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
			{
				const Uniform& un = *it;
				uint8_t nameSize = (uint8_t)un.name.size();
				bx::write(_shaderWriter, nameSize, &err);
				bx::write(_shaderWriter, un.name.c_str(), nameSize, &err);
				uint8_t uniformType = uint8_t(un.type);
				bx::write(_shaderWriter, uniformType, &err);
				bx::write(_shaderWriter, un.num, &err);
				bx::write(_shaderWriter, un.regIndex, &err);
				bx::write(_shaderWriter, un.regCount, &err);
				bx::write(_shaderWriter, un.texComponent, &err);
				bx::write(_shaderWriter, un.texDimension, &err);
				bx::write(_shaderWriter, un.texFormat, &err);
			}

			uint32_t shaderSize = uint32_t(source.size() );
			bx::write(_shaderWriter, shaderSize, &err);
			bx::write(_shaderWriter, source.c_str(), shaderSize, &err);
			uint8_t nul = 0;
			bx::write(_shaderWriter, nul, &err);

			if (_options.disasm)
			{
				std::string disasmfp = _options.outputFilePath + ".disasm";
				writeFile(disasmfp.c_str(), source.c_str(), shaderSize);
			}

			result = true;
		}

		delete program;
		delete shader;

		glslang::FinalizeProcess();

		return result;
	}

} // namespace glsl
} // namespace bgfx

#endif // SHADERC_CONFIG_HAS_GLSLANG

namespace bgfx
{
	bool compileGLSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _shaderWriter, bx::WriterI* _messageWriter)
	{
#if SHADERC_CONFIG_HAS_GLSLANG
		return glsl::compileSpirvCross(_options, _version, _code, _shaderWriter, _messageWriter);
#else
		BX_UNUSED(_options, _version, _code, _shaderWriter);
		bx::ErrorAssert messageErr;
		bx::write(_messageWriter, &messageErr, "GLSL compiler is not compiled in.\n");
		return false;
#endif // SHADERC_CONFIG_HAS_GLSLANG
	}

} // namespace bgfx

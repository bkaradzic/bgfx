/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"
#include "glsl_optimizer.h"

namespace bgfx { namespace glsl
{
	static bool compile(bx::CommandLine& _cmdLine, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		char ch = char(tolower(_cmdLine.findOption('\0', "type")[0]) );
		const glslopt_shader_type type = ch == 'f'
			? kGlslOptShaderFragment
			: (ch == 'c' ? kGlslOptShaderCompute : kGlslOptShaderVertex);

		glslopt_target target = kGlslTargetOpenGL;
		switch (_version)
		{
		case BX_MAKEFOURCC('M', 'T', 'L', 0):
			target = kGlslTargetMetal;
			break;

		case 2:
			target = kGlslTargetOpenGLES20;
			break;

		case 3:
			target = kGlslTargetOpenGLES30;
			break;

		default:
			target = kGlslTargetOpenGL;
			break;
		}

		glslopt_ctx* ctx = glslopt_initialize(target);

		glslopt_shader* shader = glslopt_optimize(ctx, type, _code.c_str(), 0);

		if (!glslopt_get_status(shader) )
		{
			const char* log = glslopt_get_log(shader);
			int32_t source  = 0;
			int32_t line    = 0;
			int32_t column  = 0;
			int32_t start   = 0;
			int32_t end     = INT32_MAX;

			bool found = false
				|| 3 == sscanf(log, "%u:%u(%u):", &source, &line, &column)
				;

			if (found
			&&  0 != line)
			{
				start = bx::uint32_imax(1, line-10);
				end   = start + 20;
			}

			printCode(_code.c_str(), line, start, end, column);
			fprintf(stderr, "Error: %s\n", log);
			glslopt_cleanup(ctx);
			return false;
		}

		const char* optimizedShader = glslopt_get_output(shader);

		// Trim all directives.
		while ('#' == *optimizedShader)
		{
			optimizedShader = bx::strnl(optimizedShader);
		}

		{
			char* code = const_cast<char*>(optimizedShader);
			strReplace(code, "gl_FragDepthEXT", "gl_FragDepth");

			strReplace(code, "texture2DLodARB", "texture2DLod");
			strReplace(code, "texture2DLodEXT", "texture2DLod");
			strReplace(code, "texture2DGradARB", "texture2DGrad");
			strReplace(code, "texture2DGradEXT", "texture2DGrad");

			strReplace(code, "textureCubeLodARB", "textureCubeLod");
			strReplace(code, "textureCubeLodEXT", "textureCubeLod");
			strReplace(code, "textureCubeGradARB", "textureCubeGrad");
			strReplace(code, "textureCubeGradEXT", "textureCubeGrad");

			strReplace(code, "texture2DProjLodARB", "texture2DProjLod");
			strReplace(code, "texture2DProjLodEXT", "texture2DProjLod");
			strReplace(code, "texture2DProjGradARB", "texture2DProjGrad");
			strReplace(code, "texture2DProjGradEXT", "texture2DProjGrad");

			strReplace(code, "shadow2DARB", "shadow2D");
			strReplace(code, "shadow2DEXT", "shadow2D");
			strReplace(code, "shadow2DProjARB", "shadow2DProj");
			strReplace(code, "shadow2DProjEXT", "shadow2DProj");
		}

		UniformArray uniforms;

		if (target != kGlslTargetMetal)
		{
			const char* parse = optimizedShader;

			while (NULL != parse
				&&  *parse != '\0')
			{
				parse = bx::strws(parse);
				const char* eol = strchr(parse, ';');
				if (NULL != eol)
				{
					const char* qualifier = parse;
					parse = bx::strws(bx::strword(parse) );

					if (0 == strncmp(qualifier, "attribute", 9)
					||  0 == strncmp(qualifier, "varying", 7) )
					{
						// skip attributes and varyings.
						parse = eol + 1;
						continue;
					}

					if (0 != strncmp(qualifier, "uniform", 7) )
					{
						// end if there is no uniform keyword.
						parse = NULL;
						continue;
					}

					const char* precision = NULL;
					const char* typen = parse;

					if (0 == strncmp(typen, "lowp", 4)
					||  0 == strncmp(typen, "mediump", 7)
					||  0 == strncmp(typen, "highp", 5) )
					{
						precision = typen;
						typen = parse = bx::strws(bx::strword(parse) );
					}

					BX_UNUSED(precision);

					char uniformType[256];
					parse = bx::strword(parse);

					if (0 == strncmp(typen, "sampler", 7) )
					{
						strcpy(uniformType, "int");
					}
					else
					{
						bx::strlcpy(uniformType, typen, parse-typen+1);
					}

					const char* name = parse = bx::strws(parse);

					char uniformName[256];
					uint8_t num = 1;
					const char* array = bx::strnstr(name, "[", eol-parse);
					if (NULL != array)
					{
						bx::strlcpy(uniformName, name, array-name+1);

						char arraySize[32];
						const char* end = bx::strnstr(array, "]", eol-array);
						bx::strlcpy(arraySize, array+1, end-array);
						num = uint8_t(atoi(arraySize) );
					}
					else
					{
						bx::strlcpy(uniformName, name, eol-name+1);
					}

					Uniform un;
					un.type = nameToUniformTypeEnum(uniformType);

					if (UniformType::Count != un.type)
					{
						BX_TRACE("name: %s (type %d, num %d)", uniformName, un.type, num);

						un.name = uniformName;
						un.num = num;
						un.regIndex = 0;
						un.regCount = num;
						uniforms.push_back(un);
					}

					parse = eol + 1;
				}
			}
		}
		else
		{
			const char* parse = strstr(optimizedShader, "struct xlatMtlShaderUniform {");
			const char* end   = parse;
			if (NULL != parse)
			{
				parse += strlen("struct xlatMtlShaderUniform {");
				end   = strstr(parse, "};");
			}

			while ( parse < end
			&&     *parse != '\0')
			{
				parse = bx::strws(parse);
				const char* eol = strchr(parse, ';');
				if (NULL != eol)
				{
					const char* typen = parse;

					char uniformType[256];
					parse = bx::strword(parse);
					bx::strlcpy(uniformType, typen, parse-typen+1);
					const char* name = parse = bx::strws(parse);

					char uniformName[256];
					uint8_t num = 1;
					const char* array = bx::strnstr(name, "[", eol-parse);
					if (NULL != array)
					{
						bx::strlcpy(uniformName, name, array-name+1);

						char arraySize[32];
						const char* arrayEnd = bx::strnstr(array, "]", eol-array);
						bx::strlcpy(arraySize, array+1, arrayEnd-array);
						num = uint8_t(atoi(arraySize) );
					}
					else
					{
						bx::strlcpy(uniformName, name, eol-name+1);
					}

					Uniform un;
					un.type = nameToUniformTypeEnum(uniformType);

					if (UniformType::Count != un.type)
					{
						BX_TRACE("name: %s (type %d, num %d)", uniformName, un.type, num);

						un.name = uniformName;
						un.num = num;
						un.regIndex = 0;
						un.regCount = num;
						uniforms.push_back(un);
					}

					parse = eol + 1;
				}
			}
		}

		uint16_t count = (uint16_t)uniforms.size();
		bx::write(_writer, count);

		for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
		{
			const Uniform& un = *it;
			uint8_t nameSize = (uint8_t)un.name.size();
			bx::write(_writer, nameSize);
			bx::write(_writer, un.name.c_str(), nameSize);
			uint8_t uniformType = uint8_t(un.type);
			bx::write(_writer, uniformType);
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

		uint32_t shaderSize = (uint32_t)strlen(optimizedShader);
		bx::write(_writer, shaderSize);
		bx::write(_writer, optimizedShader, shaderSize);
		uint8_t nul = 0;
		bx::write(_writer, nul);

		if (_cmdLine.hasArg('\0', "disasm") )
		{
			std::string disasmfp = _cmdLine.findOption('o');
			disasmfp += ".disasm";
			writeFile(disasmfp.c_str(), optimizedShader, shaderSize);
		}

		glslopt_cleanup(ctx);

		return true;
	}

} // namespace glsl

	bool compileGLSLShader(bx::CommandLine& _cmdLine, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		return glsl::compile(_cmdLine, _version, _code, _writer);
	}

} // namespace bgfx

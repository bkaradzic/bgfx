/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#define _BX_TRACE(_format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					if (g_verbose) \
					{ \
						fprintf(stderr, BX_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__); \
					} \
				BX_MACRO_BLOCK_END

#define _BX_WARN(_condition, _format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					if (!(_condition) ) \
					{ \
						BX_TRACE("WARN " _format, ##__VA_ARGS__); \
					} \
				BX_MACRO_BLOCK_END

#define _BX_CHECK(_condition, _format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					if (!(_condition) ) \
					{ \
						BX_TRACE("CHECK " _format, ##__VA_ARGS__); \
						bx::debugBreak(); \
					} \
				BX_MACRO_BLOCK_END

#define BX_TRACE _BX_TRACE
#define BX_WARN  _BX_WARN
#define BX_CHECK _BX_CHECK

bool g_verbose = false;

#include <bx/bx.h>
#include <bx/debug.h>

#define NOMINMAX
#include <alloca.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#define MAX_TAGS 256
extern "C"
{
#include <fpp.h>
} // extern "C"

#define BGFX_CHUNK_MAGIC_CSH BX_MAKEFOURCC('C', 'S', 'H', 0x0)
#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x2)
#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x2)

#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/uint32_t.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include <bx/hash.h>

#include "glsl_optimizer.h"

#if BX_PLATFORM_WINDOWS
#	include <sal.h>
#	define __D3DX9MATH_INL__ // not used and MinGW complains about type-punning
#	include <d3dx9.h>
#	include <d3dcompiler.h>
#endif // BX_PLATFORM_WINDOWS

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

struct Attrib
{
	enum Enum
	{
		Position = 0,
		Normal,
		Tangent,
		Color0,
		Color1,
		Indices,
		Weight,
		TexCoord0,
		TexCoord1,
		TexCoord2,
		TexCoord3,
		TexCoord4,
		TexCoord5,
		TexCoord6,
		TexCoord7,

		Count,
	};
};

static const char* s_ARB_shader_texture_lod[] =
{
	"texture2DLod",
	"texture2DProjLod",
	"texture3DLod",
	"texture3DProjLod",
	"textureCubeLod",
	"shadow2DLod",
	"shadow2DProjLod",
	NULL
	// "texture1DLod",
	// "texture1DProjLod",
	// "shadow1DLod",
	// "shadow1DProjLod",
};

static const char* s_EXT_shadow_samplers[] =
{
	"shadow2D",
	"shadow2DProj",
	"sampler2DShadow",
	NULL
};

static const char* s_OES_standard_derivatives[] =
{
	"dFdx",
	"dFdy",
	"fwidth",
	NULL
};

static const char* s_OES_texture_3D[] =
{
	"texture3D",
	"texture3DProj",
	"texture3DLod",
	"texture3DProjLod",
	NULL
};

struct RemapInputSemantic
{
	Attrib::Enum m_attr;
	const char* m_name;
	uint8_t m_index;
};

static const RemapInputSemantic s_remapInputSemantic[Attrib::Count+1] =
{
	{ Attrib::Position,  "POSITION",     0 },
	{ Attrib::Normal,    "NORMAL",       0 },
	{ Attrib::Tangent,   "TANGENT",      0 },
	{ Attrib::Color0,    "COLOR",        0 },
	{ Attrib::Color1,    "COLOR",        1 },
	{ Attrib::Indices,   "BLENDINDICES", 0 },
	{ Attrib::Weight,    "BLENDWEIGHT",  0 },
	{ Attrib::TexCoord0, "TEXCOORD",     0 },
	{ Attrib::TexCoord1, "TEXCOORD",     1 },
	{ Attrib::TexCoord2, "TEXCOORD",     2 },
	{ Attrib::TexCoord3, "TEXCOORD",     3 },
	{ Attrib::TexCoord4, "TEXCOORD",     4 },
	{ Attrib::TexCoord5, "TEXCOORD",     5 },
	{ Attrib::TexCoord6, "TEXCOORD",     6 },
	{ Attrib::TexCoord7, "TEXCOORD",     7 },
	{ Attrib::Count,     "",             0 },
};

const RemapInputSemantic& findInputSemantic(const char* _name, uint8_t _index)
{
	for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
	{
		const RemapInputSemantic& ris = s_remapInputSemantic[ii];
		if (0 == strcmp(ris.m_name, _name)
		&&  ris.m_index == _index)
		{
			return ris;
		}
	}

	return s_remapInputSemantic[Attrib::Count];
}

struct UniformType
{
	enum Enum
	{
		Uniform1i,
		Uniform1f,
		End,

		Uniform1iv,
		Uniform1fv,
		Uniform2fv,
		Uniform3fv,
		Uniform4fv,
		Uniform3x3fv,
		Uniform4x4fv,

		Count
	};
};

#define BGFX_UNIFORM_FRAGMENTBIT UINT8_C(0x10)

const char* s_uniformTypeName[UniformType::Count] =
{
	"int",
	"float",
	NULL,
	"int",
	"float",
	"vec2",
	"vec3",
	"vec4",
	"mat3",
	"mat4",
};

UniformType::Enum nameToUniformTypeEnum(const char* _name)
{
	for (uint32_t ii = 0; ii < UniformType::Count; ++ii)
	{
		if (NULL != s_uniformTypeName[ii]
		&&  0 == strcmp(_name, s_uniformTypeName[ii]) )
		{
			return UniformType::Enum(ii);
		}
	}

	return UniformType::Count;
}

struct Uniform
{
	std::string name;
	UniformType::Enum type;
	uint8_t num;
	uint16_t regIndex;
	uint16_t regCount;
};
typedef std::vector<Uniform> UniformArray;

const char* interpolationDx11(const char* _glsl)
{
	if (0 == strcmp(_glsl, "smooth") )
	{
		return "linear";
	}
	else if (0 == strcmp(_glsl, "flat") )
	{
		return "nointerpolation";
	}

	return _glsl; // noperspective
}

#if BX_PLATFORM_WINDOWS
struct UniformRemapDx9
{
	UniformType::Enum id;
	D3DXPARAMETER_CLASS paramClass;
	D3DXPARAMETER_TYPE paramType;
	uint8_t columns;
	uint8_t rows;
};

static const UniformRemapDx9 s_constRemapDx9[7] =
{
	{ UniformType::Uniform1iv,   D3DXPC_SCALAR,         D3DXPT_INT,   0, 0 },
	{ UniformType::Uniform1fv,   D3DXPC_SCALAR,         D3DXPT_FLOAT, 0, 0 },
	{ UniformType::Uniform2fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT, 0, 0 },
	{ UniformType::Uniform3fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT, 0, 0 },
	{ UniformType::Uniform4fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT, 0, 0 },
	{ UniformType::Uniform3x3fv, D3DXPC_MATRIX_COLUMNS, D3DXPT_FLOAT, 3, 3 },
	{ UniformType::Uniform4x4fv, D3DXPC_MATRIX_COLUMNS, D3DXPT_FLOAT, 4, 4 },
};

UniformType::Enum findUniformTypeDx9(const D3DXCONSTANT_DESC& constDesc)
{
	for (uint32_t ii = 0; ii < BX_COUNTOF(s_constRemapDx9); ++ii)
	{
		const UniformRemapDx9& remap = s_constRemapDx9[ii];

		if (remap.paramClass == constDesc.Class
		&&  remap.paramType  == constDesc.Type)
		{
			if (D3DXPC_MATRIX_COLUMNS != constDesc.Class)
			{
				return remap.id;
			}

			if (remap.columns == constDesc.Columns
			&&  remap.rows    == constDesc.Rows)
			{
				return remap.id;
			}
		}
	}

	return UniformType::Count;
}

static uint32_t s_optimizationLevelDx9[4] =
{
	D3DXSHADER_OPTIMIZATION_LEVEL0,
	D3DXSHADER_OPTIMIZATION_LEVEL1,
	D3DXSHADER_OPTIMIZATION_LEVEL2,
	D3DXSHADER_OPTIMIZATION_LEVEL3,
};

struct UniformRemapDx11
{
	UniformType::Enum id;
	D3D_SHADER_VARIABLE_CLASS paramClass;
	D3D_SHADER_VARIABLE_TYPE paramType;
	uint8_t columns;
	uint8_t rows;
};

static const UniformRemapDx11 s_constRemapDx11[7] =
{
	{ UniformType::Uniform1iv,   D3D_SVC_SCALAR,         D3D_SVT_INT,   0, 0 },
	{ UniformType::Uniform1fv,   D3D_SVC_SCALAR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform2fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform3fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform4fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform3x3fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 3, 3 },
	{ UniformType::Uniform4x4fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 4, 4 },
};

UniformType::Enum findUniformTypeDx11(const D3D11_SHADER_TYPE_DESC& constDesc)
{
	for (uint32_t ii = 0; ii < BX_COUNTOF(s_constRemapDx11); ++ii)
	{
		const UniformRemapDx11& remap = s_constRemapDx11[ii];

		if (remap.paramClass == constDesc.Class
		&&  remap.paramType == constDesc.Type)
		{
			if (D3D_SVC_MATRIX_COLUMNS != constDesc.Class)
			{
				return remap.id;
			}

			if (remap.columns == constDesc.Columns
			&&  remap.rows    == constDesc.Rows)
			{
				return remap.id;
			}
		}
	}

	return UniformType::Count;
}

static uint32_t s_optimizationLevelDx11[4] =
{
	D3DCOMPILE_OPTIMIZATION_LEVEL0,
	D3DCOMPILE_OPTIMIZATION_LEVEL1,
	D3DCOMPILE_OPTIMIZATION_LEVEL2,
	D3DCOMPILE_OPTIMIZATION_LEVEL3,
};
#endif // BX_PLATFORM_WINDOWS

int32_t writef(bx::WriterI* _writer, const char* _format, ...)
{
	va_list argList;
	va_start(argList, _format);

	char temp[2048];

	char* out = temp;
	int32_t max = sizeof(temp);
	int32_t len = bx::vsnprintf(out, max, _format, argList);
	if (len > max)
	{
		out = (char*)alloca(len);
		len = bx::vsnprintf(out, len, _format, argList);
	}

	len = bx::write(_writer, out, len);

	va_end(argList);

	return len;
}

class Bin2cWriter : public bx::CrtFileWriter
{
public:
	Bin2cWriter(const char* _name)
		: m_name(_name)
	{
	}

	virtual ~Bin2cWriter()
	{
	}

	virtual int32_t close() BX_OVERRIDE
	{
		generate();
		return bx::CrtFileWriter::close();
	}

	virtual int32_t write(const void* _data, int32_t _size) BX_OVERRIDE
	{
		const char* data = (const char*)_data;
		m_buffer.insert(m_buffer.end(), data, data+_size);
		return _size;
	}

private:
	void generate()
	{
#define HEX_DUMP_WIDTH 16
#define HEX_DUMP_SPACE_WIDTH 96
#define HEX_DUMP_FORMAT "%-" BX_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "." BX_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "s"
		const uint8_t* data = &m_buffer[0];
		uint32_t size = (uint32_t)m_buffer.size();

		outf("static const uint8_t %s[%d] =\n{\n", m_name.c_str(), size);

		if (NULL != data)
		{
			char hex[HEX_DUMP_SPACE_WIDTH+1];
			char ascii[HEX_DUMP_WIDTH+1];
			uint32_t hexPos = 0;
			uint32_t asciiPos = 0;
			for (uint32_t ii = 0; ii < size; ++ii)
			{
				bx::snprintf(&hex[hexPos], sizeof(hex)-hexPos, "0x%02x, ", data[asciiPos]);
				hexPos += 6;

				ascii[asciiPos] = isprint(data[asciiPos]) && data[asciiPos] != '\\' ? data[asciiPos] : '.';
				asciiPos++;

				if (HEX_DUMP_WIDTH == asciiPos)
				{
					ascii[asciiPos] = '\0';
					outf("\t" HEX_DUMP_FORMAT "// %s\n", hex, ascii);
					data += asciiPos;
					hexPos = 0;
					asciiPos = 0;
				}
			}

			if (0 != asciiPos)
			{
				ascii[asciiPos] = '\0';
				outf("\t" HEX_DUMP_FORMAT "// %s\n", hex, ascii);
			}
		}

		outf("};\n");
#undef HEX_DUMP_WIDTH
#undef HEX_DUMP_SPACE_WIDTH
#undef HEX_DUMP_FORMAT
	}

	int32_t outf(const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		char temp[2048];
		char* out = temp;
		int32_t max = sizeof(temp);
		int32_t len = bx::vsnprintf(out, max, _format, argList);
		if (len > max)
		{
			out = (char*)alloca(len);
			len = bx::vsnprintf(out, len, _format, argList);
		}

		int32_t size = bx::CrtFileWriter::write(out, len);

		va_end(argList);

		return size;
	}

	std::string m_filePath;
	std::string m_name;
	typedef std::vector<uint8_t> Buffer;
	Buffer m_buffer;
};

struct Varying
{
	std::string m_precision;
	std::string m_interpolation;
	std::string m_name;
	std::string m_type;
	std::string m_init;
	std::string m_semantics;
};

typedef std::unordered_map<std::string, Varying> VaryingMap;

class File 
{
public:
	File(const char* _filePath)
		: m_data(NULL)
	{
		FILE* file = fopen(_filePath, "r");
		if (NULL != file)
		{
			m_size = fsize(file);
			m_data = new char[m_size+1];
			m_size = (uint32_t)fread(m_data, 1, m_size, file);
			m_data[m_size] = '\0';
			fclose(file);
		}
	}

	~File()
	{
		delete [] m_data;
	}

	const char* getData() const
	{
		return m_data;
	}

	uint32_t getSize() const
	{
		return m_size;
	}

private:
	char* m_data;
	uint32_t m_size;
};

void strins(char* _str, const char* _insert)
{
	size_t len = strlen(_insert);
	memmove(&_str[len], _str, strlen(_str) );
	memcpy(_str, _insert, len);
}

void strreplace(char* _str, const char* _find, const char* _replace)
{
	const size_t len = strlen(_find);

	char* replace = (char*)alloca(len+1);
	bx::strlcpy(replace, _replace, len+1);
	for (size_t ii = strlen(replace); ii < len; ++ii)
	{
		replace[ii] = ' ';
	}
	replace[len] = '\0';

	BX_CHECK(len >= strlen(_replace), "");
	for (char* ptr = strstr(_str, _find); NULL != ptr; ptr = strstr(ptr + len, _find) )
	{
		memcpy(ptr, replace, len);
	}
}

class LineReader
{
public:
	LineReader(const char* _str)
		: m_str(_str)
		, m_pos(0)
		, m_size( (uint32_t)strlen(_str) )
	{
	}

	std::string getLine()
	{
		const char* str = &m_str[m_pos];
		skipLine();

		const char* eol = &m_str[m_pos];

		std::string tmp;
		tmp.assign(str, eol-str);
		return tmp;
	}

	bool isEof() const
	{
		return m_str[m_pos] == '\0';
	}

	void skipLine()
	{
		const char* str = &m_str[m_pos];
		const char* nl = bx::strnl(str);
		m_pos += (uint32_t)(nl - str);
	}

	const char* m_str;
	uint32_t m_pos;
	uint32_t m_size;
};

void printCode(const char* _code, int32_t _line = 0, int32_t _start = 0, int32_t _end = INT32_MAX)
{
	fprintf(stderr, "Code:\n---\n");

	LineReader lr(_code);
	for (int32_t line = 1; !lr.isEof() && line < _end; ++line)
	{
		if (line >= _start)
		{
			fprintf(stderr, "%s%3d: %s", _line == line ? ">>> " : "    ", line, lr.getLine().c_str() );
		}
		else
		{
			lr.skipLine();
		}
	}

	fprintf(stderr, "---\n");
}

void writeFile(const char* _filePath, const void* _data, int32_t _size)
{
	bx::CrtFileWriter out;
	if (0 == out.open(_filePath) )
	{
		out.write(_data, _size);
		out.close();
	}
}

bool compileGLSLShader(bx::CommandLine& _cmdLine, uint32_t _gles, const std::string& _code, bx::WriterI* _writer)
{
	char ch = tolower(_cmdLine.findOption('\0', "type")[0]);
	const glslopt_shader_type type = ch == 'f'
		? kGlslOptShaderFragment 
		: (ch == 'c' ? kGlslOptShaderCompute : kGlslOptShaderVertex);

	glslopt_target target = kGlslTargetOpenGL;
	switch (_gles)
	{
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
		int32_t source = 0;
		int32_t line = 0;
		int32_t column = 0;
		int32_t start = 0;
		int32_t end = INT32_MAX;

		if (3 == sscanf(log, "%u:%u(%u):", &source, &line, &column)
		&&  0 != line)
		{
			start = bx::uint32_imax(1, line-10);
			end = start + 20;
		}

		printCode(_code.c_str(), line, start, end);
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

	if (0 != _gles)
	{
		char* shader = const_cast<char*>(optimizedShader);
		strreplace(shader, "gl_FragDepthEXT", "gl_FragDepth");

		strreplace(shader, "texture2DLodEXT", "texture2DLod");
		strreplace(shader, "texture2DProjLodEXT", "texture2DProjLod");
		strreplace(shader, "textureCubeLodEXT", "textureCubeLod");
		strreplace(shader, "texture2DGradEXT", "texture2DGrad");
		strreplace(shader, "texture2DProjGradEXT", "texture2DProjGrad");
		strreplace(shader, "textureCubeGradEXT", "textureCubeGrad");
 
		strreplace(shader, "shadow2DEXT", "shadow2D");
		strreplace(shader, "shadow2DProjEXT", "shadow2DProj");
	}

	UniformArray uniforms;

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
				const char* type = parse;

				if (0 == strncmp(type, "lowp", 4)
				||  0 == strncmp(type, "mediump", 7)
				||  0 == strncmp(type, "highp", 5) )
				{
					precision = type;
					type = parse = bx::strws(bx::strword(parse) );
				}

				BX_UNUSED(precision);

				char uniformType[256];
				parse = bx::strword(parse);

				if (0 == strncmp(type, "sampler", 7) )
				{
					strcpy(uniformType, "int");
				}
				else
				{
					bx::strlcpy(uniformType, type, parse-type+1);
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
					num = atoi(arraySize);
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
		uint8_t type = un.type;
		bx::write(_writer, type);
		bx::write(_writer, un.num);
		bx::write(_writer, un.regIndex);
		bx::write(_writer, un.regCount);

		BX_TRACE("%s, %s, %d, %d, %d"
			, un.name.c_str()
			, s_uniformTypeName[un.type]
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

	glslopt_cleanup(ctx);

	return true;
}

bool compileHLSLShaderDx9(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
#if BX_PLATFORM_WINDOWS
	BX_TRACE("DX9");

	const char* profile = _cmdLine.findOption('p', "profile");
	if (NULL == profile)
	{
		fprintf(stderr, "Shader profile must be specified.\n");
		return false;
	}

	bool debug = _cmdLine.hasArg('\0', "debug");

	uint32_t flags = 0;
	flags |= debug ? D3DXSHADER_DEBUG : 0;
	flags |= _cmdLine.hasArg('\0', "avoid-flow-control") ? D3DXSHADER_AVOID_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "no-preshader") ? D3DXSHADER_NO_PRESHADER : 0;
	flags |= _cmdLine.hasArg('\0', "partial-precision") ? D3DXSHADER_PARTIALPRECISION : 0;
	flags |= _cmdLine.hasArg('\0', "prefer-flow-control") ? D3DXSHADER_PREFER_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "backwards-compatibility") ? D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY : 0;

	bool werror = _cmdLine.hasArg('\0', "Werror");

	uint32_t optimization = 3;
	if (_cmdLine.hasArg(optimization, 'O') )
	{
		optimization = bx::uint32_min(optimization, BX_COUNTOF(s_optimizationLevelDx9)-1);
		flags |= s_optimizationLevelDx9[optimization];
	}
	else
	{
		flags |= D3DXSHADER_SKIPOPTIMIZATION;
	}

	BX_TRACE("Profile: %s", profile);
	BX_TRACE("Flags: 0x%08x", flags);

	LPD3DXBUFFER code;
	LPD3DXBUFFER errorMsg;
	LPD3DXCONSTANTTABLE constantTable;

	HRESULT hr;

	// Output preprocessed shader so that HLSL can be debugged via GPA
	// or PIX. Compiling through memory won't embed preprocessed shader
	// file path.
	if (debug)
	{
		std::string hlslfp = _cmdLine.findOption('o');
		hlslfp += ".hlsl";
		writeFile(hlslfp.c_str(), _code.c_str(), (int32_t)_code.size() );

		hr = D3DXCompileShaderFromFileA(hlslfp.c_str()
				, NULL
				, NULL
				, "main"
				, profile
				, flags
				, &code
				, &errorMsg
				, &constantTable
				);
	}
	else
	{
		hr = D3DXCompileShader(_code.c_str()
				, (uint32_t)_code.size()
				, NULL
				, NULL
				, "main"
				, profile
				, flags
				, &code
				, &errorMsg
				, &constantTable
				);
	}

	if (FAILED(hr)
	|| (werror && NULL != errorMsg) )
	{
		const char* log = (const char*)errorMsg->GetBufferPointer();

		char source[1024];
		int32_t line = 0;
		int32_t column = 0;
		int32_t start = 0;
		int32_t end = INT32_MAX;

		if (3 == sscanf(log, "%[^(](%u,%u):", source, &line, &column)
		&&  0 != line)
		{
			start = bx::uint32_imax(1, line-10);
			end = start + 20;
		}

		printCode(_code.c_str(), line, start, end);
		fprintf(stderr, "Error: 0x%08x %s\n", (uint32_t)hr, log);
		errorMsg->Release();
		return false;
	}

	D3DXCONSTANTTABLE_DESC desc;
	hr = constantTable->GetDesc(&desc);
	if (FAILED(hr) )
	{
		fprintf(stderr, "Error 0x%08x\n", (uint32_t)hr);
		return false;
	}

	BX_TRACE("Creator: %s 0x%08x", desc.Creator, (uint32_t /*mingw warning*/)desc.Version);
	BX_TRACE("Num constants: %d", desc.Constants);
	BX_TRACE("#   cl ty RxC   S  By Name");

	UniformArray uniforms;

	for (uint32_t ii = 0; ii < desc.Constants; ++ii)
	{
		D3DXHANDLE handle = constantTable->GetConstant(NULL, ii);
		D3DXCONSTANT_DESC constDesc;
		uint32_t count;
		constantTable->GetConstantDesc(handle, &constDesc, &count);
		BX_TRACE("%3d %2d %2d [%dx%d] %d %3d %s[%d] c%d (%d)"
			, ii
			, constDesc.Class
			, constDesc.Type
			, constDesc.Rows
			, constDesc.Columns
			, constDesc.StructMembers
			, constDesc.Bytes
			, constDesc.Name
			, constDesc.Elements
			, constDesc.RegisterIndex
			, constDesc.RegisterCount
			);

		UniformType::Enum type = findUniformTypeDx9(constDesc);
		if (UniformType::Count != type)
		{
			Uniform un;
			un.name = '$' == constDesc.Name[0] ? constDesc.Name+1 : constDesc.Name;
			un.type = type;
			un.num = constDesc.Elements;
			un.regIndex = constDesc.RegisterIndex;
			un.regCount = constDesc.RegisterCount;
			uniforms.push_back(un);
		}
	}

	uint16_t count = (uint16_t)uniforms.size();
	bx::write(_writer, count);

	uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
	for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
	{
		const Uniform& un = *it;
		uint8_t nameSize = (uint8_t)un.name.size();
		bx::write(_writer, nameSize);
		bx::write(_writer, un.name.c_str(), nameSize);
		uint8_t type = un.type|fragmentBit;
		bx::write(_writer, type);
		bx::write(_writer, un.num);
		bx::write(_writer, un.regIndex);
		bx::write(_writer, un.regCount);

		BX_TRACE("%s, %s, %d, %d, %d"
			, un.name.c_str()
			, s_uniformTypeName[un.type]
			, un.num
			, un.regIndex
			, un.regCount
			);
	}

	uint16_t shaderSize = (uint16_t)code->GetBufferSize();
	bx::write(_writer, shaderSize);
	bx::write(_writer, code->GetBufferPointer(), shaderSize);
	uint8_t nul = 0;
	bx::write(_writer, nul);

	if (_cmdLine.hasArg('\0', "disasm") )
	{
		LPD3DXBUFFER disasm;
		D3DXDisassembleShader( (const DWORD*)code->GetBufferPointer()
			, false
			, NULL
			, &disasm
			);

		if (NULL != disasm)
		{
			std::string disasmfp = _cmdLine.findOption('o');
			disasmfp += ".disasm";

			writeFile(disasmfp.c_str(), disasm->GetBufferPointer(), disasm->GetBufferSize() );
			disasm->Release();
		}
	}

	if (NULL != code)
	{
		code->Release();
	}

	if (NULL != errorMsg)
	{
		errorMsg->Release();
	}

	if (NULL != constantTable)
	{
		constantTable->Release();
	}

	return true;
#else
	BX_UNUSED(_cmdLine, _code, _writer);
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
#endif // BX_PLATFORM_WINDOWS
}

bool compileHLSLShaderDx11(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
#if BX_PLATFORM_WINDOWS
	BX_TRACE("DX11");

	const char* profile = _cmdLine.findOption('p', "profile");
	if (NULL == profile)
	{
		fprintf(stderr, "Shader profile must be specified.\n");
		return false;
	}

	bool debug = _cmdLine.hasArg('\0', "debug");

	uint32_t flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
	flags |= debug ? D3DCOMPILE_DEBUG : 0;
	flags |= _cmdLine.hasArg('\0', "avoid-flow-control") ? D3DCOMPILE_AVOID_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "no-preshader") ? D3DCOMPILE_NO_PRESHADER : 0;
	flags |= _cmdLine.hasArg('\0', "partial-precision") ? D3DCOMPILE_PARTIAL_PRECISION : 0;
	flags |= _cmdLine.hasArg('\0', "prefer-flow-control") ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "backwards-compatibility") ? D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY : 0;

	bool werror = _cmdLine.hasArg('\0', "Werror");

	if (werror)
	{
		flags |= D3DCOMPILE_WARNINGS_ARE_ERRORS;
	}

	uint32_t optimization = 3;
	if (_cmdLine.hasArg(optimization, 'O') )
	{
		optimization = bx::uint32_min(optimization, BX_COUNTOF(s_optimizationLevelDx11)-1);
		flags |= s_optimizationLevelDx11[optimization];
	}
	else
	{
		flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
	}

	BX_TRACE("Profile: %s", profile);
	BX_TRACE("Flags: 0x%08x", flags);

	ID3DBlob* code;
	ID3DBlob* errorMsg;

	// Output preprocessed shader so that HLSL can be debugged via GPA
	// or PIX. Compiling through memory won't embed preprocessed shader
	// file path.
	std::string hlslfp;

	if (debug)
	{
		hlslfp = _cmdLine.findOption('o');
		hlslfp += ".hlsl";
		writeFile(hlslfp.c_str(), _code.c_str(), (int32_t)_code.size() );
	}

	HRESULT hr = D3DCompile(_code.c_str()
					, _code.size()
					, hlslfp.c_str()
					, NULL
					, NULL
					, "main"
					, profile
					, flags
					, 0
					, &code
					, &errorMsg
					);
	if (FAILED(hr)
	|| (werror && NULL != errorMsg) )
	{
		const char* log = (char*)errorMsg->GetBufferPointer();

		int32_t line = 0;
		int32_t column = 0;
		int32_t start = 0;
		int32_t end = INT32_MAX;

		if (2 == sscanf(log, "(%u,%u):", &line, &column)
		&&  0 != line)
		{
			start = bx::uint32_imax(1, line-10);
			end = start + 20;
		}

		printCode(_code.c_str(), line, start, end);
		fprintf(stderr, "Error: 0x%08x %s\n", (uint32_t)hr, log);
		errorMsg->Release();
		return false;
	}

	UniformArray uniforms;

	ID3D11ShaderReflection* reflect = NULL;
	hr = D3DReflect(code->GetBufferPointer()
		, code->GetBufferSize()
		, IID_ID3D11ShaderReflection
		, (void**)&reflect
		);
	if (FAILED(hr) )
	{
		fprintf(stderr, "Error: 0x%08x\n", (uint32_t)hr);
		return false;
	}

	D3D11_SHADER_DESC desc;
	hr = reflect->GetDesc(&desc);
	if (FAILED(hr) )
	{
		fprintf(stderr, BX_FILE_LINE_LITERAL "Error: 0x%08x\n", (uint32_t)hr);
		return false;
	}

	BX_TRACE("Creator: %s 0x%08x", desc.Creator, desc.Version);
	BX_TRACE("Num constant buffers: %d", desc.ConstantBuffers);

	BX_TRACE("Input:");
	uint8_t attrMask[Attrib::Count];
	memset(attrMask, 0, sizeof(attrMask) );

	for (uint32_t ii = 0; ii < desc.InputParameters; ++ii)
	{
		D3D11_SIGNATURE_PARAMETER_DESC spd;
		reflect->GetInputParameterDesc(ii, &spd);
		BX_TRACE("\t%2d: %s%d, vt %d, ct %d, mask %x, reg %d"
			, ii
			, spd.SemanticName
			, spd.SemanticIndex
			, spd.SystemValueType
			, spd.ComponentType
			, spd.Mask
			, spd.Register
			);

		const RemapInputSemantic& ris = findInputSemantic(spd.SemanticName, spd.SemanticIndex);
		if (ris.m_attr != Attrib::Count)
		{
			attrMask[ris.m_attr] = 0xff;
		}
	}

	BX_TRACE("Output:");
	for (uint32_t ii = 0; ii < desc.OutputParameters; ++ii)
	{
		D3D11_SIGNATURE_PARAMETER_DESC spd;
		reflect->GetOutputParameterDesc(ii, &spd);
		BX_TRACE("\t%2d: %s%d, %d, %d", ii, spd.SemanticName, spd.SemanticIndex, spd.SystemValueType, spd.ComponentType);
	}

	uint16_t size = 0;

	for (uint32_t ii = 0; ii < bx::uint32_min(1, desc.ConstantBuffers); ++ii)
	{
		ID3D11ShaderReflectionConstantBuffer* cbuffer = reflect->GetConstantBufferByIndex(ii);
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		hr = cbuffer->GetDesc(&bufferDesc);

		size = (uint16_t)bufferDesc.Size;

		if (SUCCEEDED(hr) )
		{
			BX_TRACE("%s, %d, vars %d, size %d"
				, bufferDesc.Name
				, bufferDesc.Type
				, bufferDesc.Variables
				, bufferDesc.Size
				);

			for (uint32_t jj = 0; jj < bufferDesc.Variables; ++jj)
			{
				ID3D11ShaderReflectionVariable* var = cbuffer->GetVariableByIndex(jj);
				ID3D11ShaderReflectionType* type = var->GetType();
				D3D11_SHADER_VARIABLE_DESC varDesc;
				hr = var->GetDesc(&varDesc);
				if (SUCCEEDED(hr) )
				{
					D3D11_SHADER_TYPE_DESC constDesc;
					hr = type->GetDesc(&constDesc);
					if (SUCCEEDED(hr) )
					{
						UniformType::Enum type = findUniformTypeDx11(constDesc);

						if (UniformType::Count != type
						&&  0 != (varDesc.uFlags & D3D_SVF_USED) )
						{
							Uniform un;
							un.name = varDesc.Name;
							un.type = type;
							un.num = constDesc.Elements;
							un.regIndex = varDesc.StartOffset;
							un.regCount = BX_ALIGN_16(varDesc.Size)/16;
							uniforms.push_back(un);

							BX_TRACE("\t%s, %d, size %d, flags 0x%08x, %d"
								, varDesc.Name
								, varDesc.StartOffset
								, varDesc.Size
								, varDesc.uFlags
								, type
								);
						}
						else
						{
							BX_TRACE("\t%s, unknown type", varDesc.Name);
						}
					}
				}
			}
		}
	}

	BX_TRACE("Bound:");
	for (uint32_t ii = 0; ii < desc.BoundResources; ++ii)
	{
		D3D11_SHADER_INPUT_BIND_DESC bindDesc;

		hr = reflect->GetResourceBindingDesc(ii, &bindDesc);
		if (SUCCEEDED(hr) )
		{
//			if (bindDesc.Type == D3D_SIT_SAMPLER)
			{
				BX_TRACE("\t%s, %d, %d, %d"
					, bindDesc.Name
					, bindDesc.Type
					, bindDesc.BindPoint
					, bindDesc.BindCount
					);
			}
		}
	}

	uint16_t count = (uint16_t)uniforms.size();
	bx::write(_writer, count);

	uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
	for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
	{
		const Uniform& un = *it;
		uint8_t nameSize = (uint8_t)un.name.size();
		bx::write(_writer, nameSize);
		bx::write(_writer, un.name.c_str(), nameSize);
		uint8_t type = un.type|fragmentBit;
		bx::write(_writer, type);
		bx::write(_writer, un.num);
		bx::write(_writer, un.regIndex);
		bx::write(_writer, un.regCount);

		BX_TRACE("%s, %s, %d, %d, %d"
			, un.name.c_str()
			, s_uniformTypeName[un.type]
			, un.num
			, un.regIndex
			, un.regCount
			);
	}

	uint16_t shaderSize = (uint16_t)code->GetBufferSize();
	bx::write(_writer, shaderSize);
	bx::write(_writer, code->GetBufferPointer(), shaderSize);
	uint8_t nul = 0;
	bx::write(_writer, nul);

	bx::write(_writer, attrMask, sizeof(attrMask) );
	bx::write(_writer, size);

	if (_cmdLine.hasArg('\0', "disasm") )
	{
		ID3DBlob* disasm;
		D3DDisassemble(code->GetBufferPointer()
			, code->GetBufferSize()
			, 0
			, NULL
			, &disasm
			);

		if (NULL != disasm)
		{
			std::string disasmfp = _cmdLine.findOption('o');
			disasmfp += ".disasm";

			writeFile(disasmfp.c_str(), disasm->GetBufferPointer(), (uint32_t)disasm->GetBufferSize() );
			disasm->Release();
		}
	}

	if (NULL != reflect)
	{
		reflect->Release();
	}

	if (NULL != errorMsg)
	{
		errorMsg->Release();
	}

	code->Release();

	return true;
#else
	BX_UNUSED(_cmdLine, _code, _writer);
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
#endif // BX_PLATFORM_WINDOWS
}

struct Preprocessor
{
	Preprocessor(const char* _filePath, bool _gles, const char* _includeDir = NULL)
		: m_tagptr(m_tags)
		, m_scratchPos(0)
		, m_fgetsPos(0)
	{
		m_tagptr->tag = FPPTAG_USERDATA;
		m_tagptr->data = this;
		m_tagptr++;

		m_tagptr->tag = FPPTAG_DEPENDS;
		m_tagptr->data = (void*)fppDepends;
		m_tagptr++; 

		m_tagptr->tag = FPPTAG_INPUT;
		m_tagptr->data = (void*)fppInput;
		m_tagptr++; 

		m_tagptr->tag = FPPTAG_OUTPUT;
		m_tagptr->data = (void*)fppOutput;
		m_tagptr++;

		m_tagptr->tag = FPPTAG_ERROR;
		m_tagptr->data = (void*)fppError;
		m_tagptr++;

		m_tagptr->tag = FPPTAG_IGNOREVERSION;
		m_tagptr->data = (void*)0;
		m_tagptr++;

		m_tagptr->tag = FPPTAG_LINE;
		m_tagptr->data = (void*)0;
		m_tagptr++;

		m_tagptr->tag = FPPTAG_INPUT_NAME;
		m_tagptr->data = scratch(_filePath);
		m_tagptr++;

		if (NULL != _includeDir)
		{
			addInclude(_includeDir);
		}

		if (!_gles)
		{
			m_default = "#define lowp\n#define mediump\n#define highp\n";
		}
	}

	void setDefine(const char* _define)
	{
		m_tagptr->tag = FPPTAG_DEFINE;
		m_tagptr->data = scratch(_define);
		m_tagptr++;
	}

	void setDefaultDefine(const char* _name)
	{
		char temp[1024];
		bx::snprintf(temp, BX_COUNTOF(temp)
			, "#ifndef %s\n"
			  "#	define %s 0\n"
			  "#endif // %s\n"
			  "\n"
			, _name
			, _name
			, _name
			);

		m_default += temp;
	}

	void writef(const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);
		bx::stringPrintfVargs(m_default, _format, argList);
		va_end(argList);
	}

	void addInclude(const char* _includeDir)
	{
		char* start = scratch(_includeDir);

		for (char* split = strchr(start, ';'); NULL != split; split = strchr(start, ';'))
		{
			*split = '\0';
			m_tagptr->tag = FPPTAG_INCLUDE_DIR;
			m_tagptr->data = start;
			m_tagptr++;
			start = split + 1;
		}

		m_tagptr->tag = FPPTAG_INCLUDE_DIR;
		m_tagptr->data = start;
		m_tagptr++;
	}

	void addDependency(const char* _fileName)
	{
		m_depends += " \\\n ";
		m_depends += _fileName;
	}

	bool run(const char* _input)
	{
		m_fgetsPos = 0;

		m_preprocessed.clear();
		m_input = m_default;
		m_input += "\n\n";

		size_t len = strlen(_input)+1;
		char* temp = new char[len];
		bx::eolLF(temp, len, _input);
		m_input += temp;
		delete [] temp;

		fppTag* tagptr = m_tagptr;

		tagptr->tag = FPPTAG_END;
		tagptr->data = 0;
		tagptr++;

		int result = fppPreProcess(m_tags);

		return 0 == result;
	}

	char* fgets(char* _buffer, int _size)
	{
		int ii = 0;
		for (char ch = m_input[m_fgetsPos]; m_fgetsPos < m_input.size() && ii < _size-1; ch = m_input[++m_fgetsPos])
		{
			_buffer[ii++] = ch;

			if (ch == '\n' || ii == _size)
			{
				_buffer[ii] = '\0';
				m_fgetsPos++;
				return _buffer;
			}
		}

		return NULL;
	}

	static void fppDepends(char* _fileName, void* _userData)
	{
		Preprocessor* thisClass = (Preprocessor*)_userData;
		thisClass->addDependency(_fileName);
	}

	static char* fppInput(char* _buffer, int _size, void* _userData)
	{
		Preprocessor* thisClass = (Preprocessor*)_userData;
		return thisClass->fgets(_buffer, _size);
	}

	static void fppOutput(int _ch, void* _userData)
	{
		Preprocessor* thisClass = (Preprocessor*)_userData;
		thisClass->m_preprocessed += _ch;
	}

	static void fppError(void* /*_userData*/, char* _format, va_list _vargs)
	{
		vfprintf(stderr, _format, _vargs);
	}

	char* scratch(const char* _str)
	{
		char* result = &m_scratch[m_scratchPos];
		strcpy(result, _str);
		m_scratchPos += (uint32_t)strlen(_str)+1;

		return result;
	}

	fppTag m_tags[MAX_TAGS];
	fppTag* m_tagptr;

	std::string m_depends;
	std::string m_default;
	std::string m_input;
	std::string m_preprocessed;
	char m_scratch[16<<10];
	uint32_t m_scratchPos;
	uint32_t m_fgetsPos;
};

const char* baseName(const char* _filePath)
{
	const char* bs = strrchr(_filePath, '\\');
	const char* fs = strrchr(_filePath, '/');
	const char* column = strrchr(_filePath, ':');
	const char* basename = std::max(std::max(bs, fs), column);
	if (NULL != basename)
	{
		return basename+1;
	}

	return _filePath;
}

typedef std::vector<std::string> InOut;

uint32_t parseInOut(InOut& _inout, const char* _str, const char* _eol)
{
	uint32_t hash = 0;
	_str = bx::strws(_str);

	if (_str < _eol)
	{
		const char* delim;
		do
		{
			delim = strpbrk(_str, " ,");
			if (NULL != delim)
			{
				delim = delim > _eol ? _eol : delim;
				std::string token;
				token.assign(_str, delim-_str);
				_inout.push_back(token);
				_str = bx::strws(delim + 1);
			}
		}
		while (delim < _eol && _str < _eol && NULL != delim);

		std::sort(_inout.begin(), _inout.end() );

		bx::HashMurmur2A murmur;
		murmur.begin();
		for (InOut::const_iterator it = _inout.begin(), itEnd = _inout.end(); it != itEnd; ++it)
		{
			murmur.add(it->c_str(), (uint32_t)it->size() );
		}
		hash = murmur.end();
	}

	return hash;
}

void addFragData(Preprocessor& _preprocessor, char* _data, uint32_t _idx, bool _comma)
{
	char find[32];
	bx::snprintf(find, sizeof(find), "gl_FragData[%d]", _idx);

	char replace[32];
	bx::snprintf(replace, sizeof(replace), "gl_FragData_%d_", _idx);

	strreplace(_data, find, replace);

	_preprocessor.writef(
		" \\\n\t%sout vec4 gl_FragData_%d_ : SV_TARGET%d"
		, _comma ? ", " : "  "
		, _idx
		, _idx
		);

}

// c - compute
// d - domain
// f - fragment
// g - geometry
// h - hull
// v - vertex
//
// OpenGL #version Features Direct3D Features Shader Model
// 2.1    120      vf       9.0      vf       2.0
// 3.0    130
// 3.1    140
// 3.2    150      vgf
// 3.3    330               10.0     vgf      4.0
// 4.0    400      vhdgf
// 4.1    410
// 4.2    420               11.0     vhdgf+c  5.0
// 4.3    430      vhdgf+c
// 4.4    440

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "shaderc, bgfx shader compiler tool\n"
		  "Copyright 2011-2014 Branimir Karadzic. All rights reserved.\n"
		  "License: http://www.opensource.org/licenses/BSD-2-Clause\n\n"
		);

	fprintf(stderr
		, "Usage: shaderc -f <in> -o <out> --type <v/f> --platform <platform>\n"

		  "\n"
		  "Options:\n"
		  "  -f <file path>                Input file path.\n"
		  "  -i <include path>             Include path (for multiple paths use semicolon).\n"
		  "  -o <file path>                Output file path.\n"
		  "      --bin2c <file path>       Generate C header file.\n"
		  "      --depends <file path>     Generate makefile style depends file.\n"
		  "      --platform <platform>     Target platform.\n"
		  "           android\n"
		  "           asm.js\n"
		  "           ios\n"
		  "           linux\n"
		  "           nacl\n"
		  "           osx\n"
		  "           windows\n"
		  "      --preprocess              Preprocess only.\n"
		  "      --raw                     Do not process shader. No preprocessor, and no glsl-optimizer (GLSL only).\n"
		  "      --type <type>             Shader type (vertex, fragment)\n"
		  "      --varyingdef <file path>  Path to varying.def.sc file.\n"
		  "      --verbose                 Verbose.\n"

		  "\n"
		  "Options (DX9 and DX11 only):\n"

		  "\n"
		  "      --debug                   Debug information.\n"
		  "      --disasm                  Disassemble compiled shader.\n"
		  "  -p, --profile <profile>       Shader model (f.e. ps_3_0).\n"
		  "  -O <level>                    Optimization level (0, 1, 2, 3).\n"
		  "      --Werror                  Treat warnings as errors.\n"

		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return EXIT_FAILURE;
	}

	g_verbose = cmdLine.hasArg("verbose");

	const char* filePath = cmdLine.findOption('f');
	if (NULL == filePath)
	{
		help("Shader file name must be specified.");
		return EXIT_FAILURE;
	}

	const char* outFilePath = cmdLine.findOption('o');
	if (NULL == outFilePath)
	{
		help("Output file name must be specified.");
		return EXIT_FAILURE;
	}

	const char* type = cmdLine.findOption('\0', "type");
	if (NULL == type)
	{
		help("Must specify shader type.");
		return EXIT_FAILURE;
	}

	const char* platform = cmdLine.findOption('\0', "platform");
	if (NULL == platform)
	{
		help("Must specify platform.");
		return EXIT_FAILURE;
	}

	bool raw = cmdLine.hasArg('\0', "raw");

	uint32_t gles = 0;
	uint32_t hlsl = 2;
	const char* profile = cmdLine.findOption('p', "profile");
	if (NULL != profile)
	{
		if (0 == strncmp(&profile[1], "s_3", 3) )
		{
			hlsl = 3;
		}
		else if (0 == strncmp(&profile[1], "s_4", 3) )
		{
			hlsl = 4;
		}
		else if (0 == strncmp(&profile[1], "s_5", 3) )
		{
			hlsl = 5;
		}
	}
	else
	{
		gles = 2;
	}

	const char* bin2c = NULL;
	if (cmdLine.hasArg("bin2c") )
	{
		bin2c = cmdLine.findOption("bin2c");
		if (NULL == bin2c)
		{
			bin2c = baseName(outFilePath);
			uint32_t len = (uint32_t)strlen(bin2c);
			char* temp = (char*)alloca(len+1);
			for (char *out = temp; *bin2c != '\0';)
			{
				char ch = *bin2c++;
				if (isalnum(ch) )
				{
					*out++ = ch;
				}
				else
				{
					*out++ = '_';
				}
			}
			temp[len] = '\0';

			bin2c = temp;
		}
	}

	bool depends = cmdLine.hasArg("depends");
	bool preprocessOnly = cmdLine.hasArg("preprocess");
	const char* includeDir = cmdLine.findOption('i');

	Preprocessor preprocessor(filePath, 0 != gles, includeDir);

	std::string dir;
	{
		const char* base = baseName(filePath);

		if (base != filePath)
		{
			dir.assign(filePath, base-filePath);
			preprocessor.addInclude(dir.c_str() );
		}
	}

	preprocessor.setDefaultDefine("BX_PLATFORM_ANDROID");
	preprocessor.setDefaultDefine("BX_PLATFORM_EMSCRIPTEN");
	preprocessor.setDefaultDefine("BX_PLATFORM_IOS");
	preprocessor.setDefaultDefine("BX_PLATFORM_LINUX");
	preprocessor.setDefaultDefine("BX_PLATFORM_NACL");
	preprocessor.setDefaultDefine("BX_PLATFORM_OSX");
	preprocessor.setDefaultDefine("BX_PLATFORM_WINDOWS");
	preprocessor.setDefaultDefine("BX_PLATFORM_XBOX360");
//	preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_ESSL");
	preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_GLSL");
	preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_HLSL");
	preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_COMPUTE");
	preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_FRAGMENT");
	preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_VERTEX");

	bool glsl = false;

	if (0 == bx::stricmp(platform, "android") )
	{
		preprocessor.setDefine("BX_PLATFORM_ANDROID=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "asm.js") )
	{
		preprocessor.setDefine("BX_PLATFORM_EMSCRIPTEN=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "ios") )
	{
		preprocessor.setDefine("BX_PLATFORM_IOS=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "linux") )
	{
		preprocessor.setDefine("BX_PLATFORM_LINUX=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "nacl") )
	{
		preprocessor.setDefine("BX_PLATFORM_NACL=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "osx") )
	{
		preprocessor.setDefine("BX_PLATFORM_OSX=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		glsl = true;
	}
	else if (0 == bx::stricmp(platform, "windows") )
	{
		preprocessor.setDefine("BX_PLATFORM_WINDOWS=1");
		char temp[256];
		bx::snprintf(temp, sizeof(temp), "BGFX_SHADER_LANGUAGE_HLSL=%d", hlsl);
		preprocessor.setDefine(temp);
	}
	else if (0 == bx::stricmp(platform, "xbox360") )
	{
		preprocessor.setDefine("BX_PLATFORM_XBOX360=1");
		preprocessor.setDefine("BGFX_SHADER_LANGUAGE_HLSL=3");
	}
	else
	{
		fprintf(stderr, "Unknown platform %s?!", platform);
		return EXIT_FAILURE;
	}

	preprocessor.setDefine("M_PI=3.1415926535897932384626433832795");

	char shaderType = tolower(type[0]);
	switch (shaderType)
	{
	case 'c':
		preprocessor.setDefine("BGFX_SHADER_TYPE_COMPUTE=1");
		break;

	case 'f':
		preprocessor.setDefine("BGFX_SHADER_TYPE_FRAGMENT=1");
		break;

	case 'v':
		preprocessor.setDefine("BGFX_SHADER_TYPE_VERTEX=1");
		break;

	default:
		fprintf(stderr, "Unknown type: %s?!", type);
		return EXIT_FAILURE;
	}

	bool compiled = false;

	FILE* file = fopen(filePath, "r");
	if (NULL != file)
	{
		VaryingMap varyingMap;

		std::string defaultVarying = dir + "varying.def.sc";
		const char* varyingdef = cmdLine.findOption("varyingdef", defaultVarying.c_str() );
		File attribdef(varyingdef);
		const char* parse = attribdef.getData();
		if (NULL != parse
		&&  *parse != '\0')
		{
			preprocessor.addDependency(varyingdef);
		}

		while (NULL != parse
		   &&  *parse != '\0')
		{
			parse = bx::strws(parse);
			const char* eol = strchr(parse, ';');
			if (NULL == eol)
			{
				eol = bx::streol(parse);
			}

			if (NULL != eol)
			{
				const char* precision = NULL;
				const char* interpolation = NULL;
				const char* type = parse;

				if (0 == strncmp(type, "lowp", 4)
				||  0 == strncmp(type, "mediump", 7)
				||  0 == strncmp(type, "highp", 5) )
				{
					precision = type;
					type = parse = bx::strws(bx::strword(parse) );
				}

				if (0 == strncmp(type, "flat", 4)
				||  0 == strncmp(type, "smooth", 6)
				||  0 == strncmp(type, "noperspective", 13) )
				{
					interpolation = type;
					type = parse = bx::strws(bx::strword(parse) );
				}

				const char* name      = parse = bx::strws(bx::strword(parse) );
				const char* column    = parse = bx::strws(bx::strword(parse) );
				const char* semantics = parse = bx::strws(bx::strnws (parse) );
				const char* assign    = parse = bx::strws(bx::strword(parse) );
				const char* init      = parse = bx::strws(bx::strnws (parse) );

				if (type < eol
				&&  name < eol
				&&  column < eol
				&&  ':' == *column
				&&  semantics < eol)
				{
					Varying var;
					if (NULL != precision)
					{
						var.m_precision.assign(precision, bx::strword(precision)-precision);
					}

					if (NULL != interpolation)
					{
						var.m_interpolation.assign(interpolation, bx::strword(interpolation)-interpolation);
					}

					var.m_type.assign(type, bx::strword(type)-type);
					var.m_name.assign(name, bx::strword(name)-name);
					var.m_semantics.assign(semantics, bx::strword(semantics)-semantics);

					if (assign < eol
					&&  '=' == *assign
					&&  init < eol)
					{
						var.m_init.assign(init, eol-init);
					}

					varyingMap.insert(std::make_pair(var.m_name, var) );
				}

				parse = bx::strnl(eol);
			}
		}

		InOut shaderInputs;
		InOut shaderOutputs;
		uint32_t inputHash = 0;
		uint32_t outputHash = 0;

		char* data;
		char* input;
		{
			const size_t padding = 16;
			uint32_t size = (uint32_t)fsize(file);
			data = new char[size+padding+1];
			size = (uint32_t)fread(data, 1, size, file);
			// Compiler generates "error X3000: syntax error: unexpected end of file"
			// if input doesn't have empty line at EOF.
			data[size] = '\n';
			memset(&data[size+1], 0, padding);
			fclose(file);

			input = data;
			while (input[0] == '$')
			{
				const char* str = input+1;
				const char* eol = bx::streol(str);
				const char* nl = bx::strnl(eol);
				input = const_cast<char*>(nl);

				if (0 == strncmp(str, "input", 5) )
				{
					str += 5;
					const char* comment = strstr(str, "//");
					eol = NULL != comment && comment < eol ? comment : eol;
					inputHash = parseInOut(shaderInputs, str, eol);
				}
				else if (0 == strncmp(str, "output", 6) )
				{
					str += 6;
					const char* comment = strstr(str, "//");
					eol = NULL != comment && comment < eol ? comment : eol;
					outputHash = parseInOut(shaderOutputs, str, eol);
				}
				else if (0 == strncmp(str, "raw", 3) )
				{
					raw = true;
					str += 3;
				}
			}

			if (!raw)
			{
				// To avoid commented code being recognized as used feature,
				// first preprocess pass is used to strip all comments before
				// substituting code.
				preprocessor.run(input);
				delete [] data;

				size = (uint32_t)preprocessor.m_preprocessed.size();
				data = new char[size+padding+1];
				memcpy(data, preprocessor.m_preprocessed.c_str(), size);
				memset(&data[size], 0, padding+1);
				input = data;
			}
		}

		if (raw)
		{
			bx::CrtFileWriter* writer = NULL;

			if (NULL != bin2c)
			{
				writer = new Bin2cWriter(bin2c);
			}
			else
			{
				writer = new bx::CrtFileWriter;
			}

			if (0 != writer->open(outFilePath) )
			{
				fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
				return EXIT_FAILURE;
			}

			uint32_t inputHash = 0;
			uint32_t outputHash = 0;

			if ('f' == shaderType)
			{
				bx::write(writer, BGFX_CHUNK_MAGIC_FSH);
				bx::write(writer, inputHash);
			}
			else if ('v' == shaderType)
			{
				bx::write(writer, BGFX_CHUNK_MAGIC_VSH);
				bx::write(writer, outputHash);
			}
			else
			{
				bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
				bx::write(writer, outputHash);
			}

			if (glsl)
			{
				bx::write(writer, uint16_t(0) );

				uint32_t shaderSize = (uint32_t)strlen(input);
				bx::write(writer, shaderSize);
				bx::write(writer, input, shaderSize);
				bx::write(writer, uint8_t(0) );

				compiled = true;
			}
			else
			{
				if (hlsl > 3)
				{
					compiled = compileHLSLShaderDx11(cmdLine, input, writer);
				}
				else
				{
					compiled = compileHLSLShaderDx9(cmdLine, input, writer);
				}
			}

			writer->close();
			delete writer;
		}
		else if ('c' == shaderType) // Compute
		{
			char* entry = strstr(input, "void main()");
			if (NULL == entry)
			{
				fprintf(stderr, "Shader entry point 'void main()' is not found.\n");
			}
			else
			{
				if (glsl)
				{
				}
				else
				{
					preprocessor.writef(
						"#define lowp\n"
						"#define mediump\n"
						"#define highp\n"
						"#define ivec2 int2\n"
						"#define ivec3 int3\n"
						"#define ivec4 int4\n"
						"#define uvec2 uint2\n"
						"#define uvec3 uint3\n"
						"#define uvec4 uint4\n"
						"#define vec2 float2\n"
						"#define vec3 float3\n"
						"#define vec4 float4\n"
						"#define mat2 float2x2\n"
						"#define mat3 float3x3\n"
						"#define mat4 float4x4\n"
						);

					entry[4] = '_';

					preprocessor.writef("#define void_main()");
					preprocessor.writef(" \\\n\tvoid main(");

					uint32_t arg = 0;

					const bool hasLocalInvocationID    = NULL != strstr(input, "gl_LocalInvocationID");
					const bool hasLocalInvocationIndex = NULL != strstr(input, "gl_LocalInvocationIndex");
					const bool hasGlobalInvocationID   = NULL != strstr(input, "gl_GlobalInvocationID");
					const bool hasWorkGroupID          = NULL != strstr(input, "gl_WorkGroupID");

					if (hasLocalInvocationID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_LocalInvocationID : SV_GroupThreadID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasLocalInvocationIndex)
					{
						preprocessor.writef(
							" \\\n\t%sint gl_LocalInvocationIndex : SV_GroupIndex"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasGlobalInvocationID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_GlobalInvocationID : SV_DispatchThreadID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasWorkGroupID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_WorkGroupID : SV_GroupID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					preprocessor.writef(
						" \\\n\t)\n"
						);
				}

				if (preprocessor.run(input) )
				{
					BX_TRACE("Input file: %s", filePath);
					BX_TRACE("Output file: %s", outFilePath);

					if (preprocessOnly)
					{
						bx::CrtFileWriter writer;

						if (0 != writer.open(outFilePath) )
						{
							fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
							return EXIT_FAILURE;
						}

						writer.write(preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );
						writer.close();

						return EXIT_SUCCESS;
					}

					{
						bx::CrtFileWriter* writer = NULL;

						if (NULL != bin2c)
						{
							writer = new Bin2cWriter(bin2c);
						}
						else
						{
							writer = new bx::CrtFileWriter;
						}

						if (0 != writer->open(outFilePath) )
						{
							fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
							return EXIT_FAILURE;
						}

						bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
						bx::write(writer, outputHash);

						if (glsl)
						{
							std::string code;

							if (gles)
							{
								bx::stringPrintf(code, "#version 310 es\n");
							}
							else
							{
								int32_t version = atoi(profile);
								bx::stringPrintf(code, "#version %d\n", version == 0 ? 430 : version);
							}

							code += preprocessor.m_preprocessed;
#if 1
							bx::write(writer, uint16_t(0) );

							uint32_t shaderSize = (uint32_t)code.size();
							bx::write(writer, shaderSize);
							bx::write(writer, code.c_str(), shaderSize);
							bx::write(writer, uint8_t(0) );

							compiled = true;
#else
							compiled = compileGLSLShader(cmdLine, gles, code, writer);
#endif // 0
						}
						else
						{
							if (hlsl > 3)
							{
								compiled = compileHLSLShaderDx11(cmdLine, preprocessor.m_preprocessed, writer);
							}
							else
							{
								compiled = compileHLSLShaderDx9(cmdLine, preprocessor.m_preprocessed, writer);
							}
						}

						writer->close();
						delete writer;
					}

					if (compiled)
					{
						if (depends)
						{
							std::string ofp = outFilePath;
							ofp += ".d";
							bx::CrtFileWriter writer;
							if (0 == writer.open(ofp.c_str() ) )
							{
								writef(&writer, "%s : %s\n", outFilePath, preprocessor.m_depends.c_str() );
								writer.close();
							}
						}
					}
				}
			}
		}
		else // Vertex/Fragment
		{
			char* entry = strstr(input, "void main()");
			if (NULL == entry)
			{
				fprintf(stderr, "Shader entry point 'void main()' is not found.\n");
			}
			else
			{
				if (glsl)
				{
					preprocessor.writef(
						"#define ivec2 vec2\n"
						"#define ivec3 vec3\n"
						"#define ivec4 vec4\n"
						);

					if (0 == gles)
					{
						// bgfx shadow2D/Proj behave like EXT_shadow_samplers
						// not as GLSL language 1.2 specs shadow2D/Proj.
						preprocessor.writef(
							"#define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord).x\n"
							"#define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord).x\n"
							);
					}

					for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
					{
						VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
						if (varyingIt != varyingMap.end() )
						{
							const Varying& var = varyingIt->second;
							const char* name = var.m_name.c_str();

							if (0 == strncmp(name, "a_", 2)
							||  0 == strncmp(name, "i_", 2) )
							{
								preprocessor.writef("attribute %s %s %s %s;\n"
										, var.m_precision.c_str()
										, var.m_interpolation.c_str()
										, var.m_type.c_str()
										, name
										);
							}
							else
							{
								preprocessor.writef("%s varying %s %s %s;\n"
										, var.m_interpolation.c_str()
										, var.m_precision.c_str()
										, var.m_type.c_str()
										, name
										);
							}
						}
					}

					for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
					{
						VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
						if (varyingIt != varyingMap.end() )
						{
							const Varying& var = varyingIt->second;
							preprocessor.writef("%s varying %s %s;\n"
								, var.m_interpolation.c_str()
								, var.m_type.c_str()
								, var.m_name.c_str()
								);
						}
					}
				}
				else
				{
					preprocessor.writef(
						"#define lowp\n"
						"#define mediump\n"
						"#define highp\n"
						"#define ivec2 int2\n"
						"#define ivec3 int3\n"
						"#define ivec4 int4\n"
						"#define uvec2 uint2\n"
						"#define uvec3 uint3\n"
						"#define uvec4 uint4\n"
						"#define vec2 float2\n"
						"#define vec3 float3\n"
						"#define vec4 float4\n"
						"#define mat2 float2x2\n"
						"#define mat3 float3x3\n"
						"#define mat4 float4x4\n"
						);

					if (hlsl < 4)
					{
						preprocessor.writef(
							"#define flat\n"
							"#define smooth\n"
							"#define noperspective\n"
							);
					}

					entry[4] = '_';

					if ('f' == shaderType)
					{
						const bool hasFragCoord   = NULL != strstr(input, "gl_FragCoord") || hlsl > 3;
						const bool hasFragDepth   = NULL != strstr(input, "gl_FragDepth");
						const bool hasFrontFacing = NULL != strstr(input, "gl_FrontFacing");
						const bool hasFragData0   = NULL != strstr(input, "gl_FragData[0]");
						const bool hasFragData1   = NULL != strstr(input, "gl_FragData[1]");
						const bool hasFragData2   = NULL != strstr(input, "gl_FragData[2]");
						const bool hasFragData3   = NULL != strstr(input, "gl_FragData[3]");

						if (!hasFragData0
						&&  !hasFragData1
						&&  !hasFragData2
						&&  !hasFragData3)
						{
							// GL errors when both gl_FragColor and gl_FragData is used.
							// This will trigger the same error with HLSL compiler too.
							preprocessor.writef("#define gl_FragColor gl_FragData_0_\n");
						}

						preprocessor.writef("#define void_main()");
						preprocessor.writef(" \\\n\tvoid main(");

						uint32_t arg = 0;

						if (hasFragCoord)
						{
							preprocessor.writef(" \\\n\tvec4 gl_FragCoord : SV_POSITION");
							++arg;
						}

						for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(" \\\n\t%s%s %s %s : %s"
									, arg++ > 0 ? ", " : "  "
									, interpolationDx11(var.m_interpolation.c_str() )
									, var.m_type.c_str()
									, var.m_name.c_str()
									, var.m_semantics.c_str()
									);
							}
						}

						addFragData(preprocessor, input, 0, arg++ > 0);

						if (hasFragData1)
						{
							addFragData(preprocessor, input, 1, arg++ > 0);
						}

						if (hasFragData2)
						{
							addFragData(preprocessor, input, 2, arg++ > 0);
						}

						if (hasFragData3)
						{
							addFragData(preprocessor, input, 3, arg++ > 0);
						}

						if (hasFragDepth)
						{
							preprocessor.writef(
								" \\\n\t%sout float gl_FragDepth : SV_DEPTH"
								, arg++ > 0 ? ", " : "  "
								);
						}

						if (hasFrontFacing)
						{
							preprocessor.writef(
								" \\\n\t%sfloat __vface : VFACE"
								, arg++ > 0 ? ", " : "  "
								);
						}

						preprocessor.writef(
							" \\\n\t)\n"
							);

						if (hasFrontFacing)
						{
							preprocessor.writef(
								"#define gl_FrontFacing (__vface <= 0.0)\n"
								);
						}
					}
					else if ('v' == shaderType)
					{
						const char* brace = strstr(entry, "{");
						if (NULL != brace)
						{
							const char* end = bx::strmb(brace, '{', '}');
							if (NULL != end)
							{
								strins(const_cast<char*>(end), "__RETURN__;\n");
							}
						}

						preprocessor.writef(
							"struct Output\n"
							"{\n"
							"\tvec4 gl_Position : SV_POSITION;\n"
							"#define gl_Position _varying_.gl_Position\n"
							);
						for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef("\t%s %s : %s;\n", var.m_type.c_str(), var.m_name.c_str(), var.m_semantics.c_str() );
								preprocessor.writef("#define %s _varying_.%s\n", var.m_name.c_str(), var.m_name.c_str() );
							}
						}
						preprocessor.writef(
							"};\n"
							);

						preprocessor.writef("#define void_main() \\\n");
						preprocessor.writef("Output main(");
						bool first = true;
						for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef("%s%s %s : %s\\\n", first ? "" : "\t, ", var.m_type.c_str(), var.m_name.c_str(), var.m_semantics.c_str() );
								first = false;
							}
						}
						preprocessor.writef(
							") \\\n"
							"{ \\\n"
							"\tOutput _varying_;"
							);

						for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(" \\\n\t%s = %s;", var.m_name.c_str(), var.m_init.c_str() );
							}
						}

						preprocessor.writef(
							"\n#define __RETURN__ \\\n"
							"\t} \\\n"
							"\treturn _varying_"
							);
					}
				}

				if (preprocessor.run(input) )
				{
					BX_TRACE("Input file: %s", filePath);
					BX_TRACE("Output file: %s", outFilePath);

					if (preprocessOnly)
					{
						bx::CrtFileWriter writer;

						if (0 != writer.open(outFilePath) )
						{
							fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
							return EXIT_FAILURE;
						}

						if (glsl)
						{
							const char* profile = cmdLine.findOption('p', "profile");
							if (NULL == profile)
							{
								writef(&writer
									, "#ifdef GL_ES\n"
									  "precision highp float;\n"
									  "#endif // GL_ES\n\n"
									);
							}
						}
						writer.write(preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );
						writer.close();

						return EXIT_SUCCESS;
					}

					{
						bx::CrtFileWriter* writer = NULL;

						if (NULL != bin2c)
						{
							writer = new Bin2cWriter(bin2c);
						}
						else
						{
							writer = new bx::CrtFileWriter;
						}

						if (0 != writer->open(outFilePath) )
						{
							fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
							return EXIT_FAILURE;
						}

						if ('f' == shaderType)
						{
							bx::write(writer, BGFX_CHUNK_MAGIC_FSH);
							bx::write(writer, inputHash);
						}
						else if ('v' == shaderType)
						{
							bx::write(writer, BGFX_CHUNK_MAGIC_VSH);
							bx::write(writer, outputHash);
						}
						else
						{
							bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
							bx::write(writer, outputHash);
						}

						if (glsl)
						{
							std::string code;

							bool hasTextureLod = NULL != bx::findIdentifierMatch(input, s_ARB_shader_texture_lod /*EXT_shader_texture_lod*/);

							if (0 == gles)
							{
								bx::stringPrintf(code, "#version %s\n", profile);
								int32_t version = atoi(profile);

								bx::stringPrintf(code
									, "#define bgfxShadow2D shadow2D\n"
									  "#define bgfxShadow2DProj shadow2DProj\n"
									);

								if (hasTextureLod
								&&  130 > version)
								{
									bx::stringPrintf(code
										, "#extension GL_ARB_shader_texture_lod : enable\n"
										);
								}
							}
							else
							{
								// Pretend that all extensions are available.
								// This will be stripped later.
								if (hasTextureLod)
								{
									bx::stringPrintf(code
										, "#extension GL_EXT_shader_texture_lod : enable\n"
										  "#define texture2DLod texture2DLodEXT\n"
										  "#define texture2DProjLod texture2DProjLodEXT\n"
										  "#define textureCubeLod textureCubeLodEXT\n"
//										  "#define texture2DGrad texture2DGradEXT\n"
//										  "#define texture2DProjGrad texture2DProjGradEXT\n"
//										  "#define textureCubeGrad textureCubeGradEXT\n"
										);
								}

								if (NULL != bx::findIdentifierMatch(input, s_OES_standard_derivatives) )
								{
									bx::stringPrintf(code, "#extension GL_OES_standard_derivatives : enable\n");
								}

								if (NULL != bx::findIdentifierMatch(input, s_OES_texture_3D) )
								{
									bx::stringPrintf(code, "#extension GL_OES_texture_3D : enable\n");
								}

								if (NULL != bx::findIdentifierMatch(input, s_EXT_shadow_samplers) )
								{
									bx::stringPrintf(code
										, "#extension GL_EXT_shadow_samplers : enable\n"
										  "#define shadow2D shadow2DEXT\n"
										  "#define shadow2DProj shadow2DProjEXT\n"
										);
								}

								if (NULL != bx::findIdentifierMatch(input, "gl_FragDepth") )
								{
									bx::stringPrintf(code
										, "#extension GL_EXT_frag_depth : enable\n"
										  "#define gl_FragDepth gl_FragDepthEXT\n"
										);
								}
							}

							code += preprocessor.m_preprocessed;
							compiled = compileGLSLShader(cmdLine, gles, code, writer);
						}
						else
						{
							if (hlsl > 3)
							{
								compiled = compileHLSLShaderDx11(cmdLine, preprocessor.m_preprocessed, writer);
							}
							else
							{
								compiled = compileHLSLShaderDx9(cmdLine, preprocessor.m_preprocessed, writer);
							}
						}

						writer->close();
						delete writer;
					}

					if (compiled)
					{
						if (depends)
						{
							std::string ofp = outFilePath;
							ofp += ".d";
							bx::CrtFileWriter writer;
							if (0 == writer.open(ofp.c_str() ) )
							{
								writef(&writer, "%s : %s\n", outFilePath, preprocessor.m_depends.c_str() );
								writer.close();
							}
						}
					}
				}
			}
		}

		delete [] data;
	}

	if (compiled)
	{
		return EXIT_SUCCESS;
	}

	remove(outFilePath);

	fprintf(stderr, "Failed to build shader.\n");
	return EXIT_FAILURE;
}

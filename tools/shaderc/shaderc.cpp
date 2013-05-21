/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef SHADERC_DEBUG
#	define SHADERC_DEBUG 0
#endif // SHADERC_DEBUG

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

namespace std { namespace tr1 {} using namespace tr1; } // namespace std

#define MAX_TAGS 256
extern "C"
{
#include <fpp.h>
} // extern "C"

#if SHADERC_DEBUG
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x1)
#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x1)

#include <bx/bx.h>

#include <bx/commandline.h>
#include <bx/countof.h>
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

struct ConstantType
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

		Count,
	};
};

#define BGFX_UNIFORM_FRAGMENTBIT UINT8_C(0x10)

const char* s_constantTypeName[ConstantType::Count] =
{
	"int",
	"float",
	NULL,
	"int",
	"float",
	"float2",
	"float3",
	"float4",
	"float3x3",
	"float4x4",
};

struct Uniform
{
	std::string name;
	ConstantType::Enum type;
	uint8_t num;
	uint16_t regIndex;
	uint16_t regCount;
};
typedef std::vector<Uniform> UniformArray;

#if BX_PLATFORM_WINDOWS
struct ConstRemapDx9
{
	ConstantType::Enum id;
	D3DXPARAMETER_CLASS paramClass;
	D3DXPARAMETER_TYPE paramType;
	uint32_t paramBytes;
};

static const ConstRemapDx9 s_constRemapDx9[7] =
{
	{ ConstantType::Uniform1iv,   D3DXPC_SCALAR,         D3DXPT_INT,    4 },
	{ ConstantType::Uniform1fv,   D3DXPC_SCALAR,         D3DXPT_FLOAT,  4 },
	{ ConstantType::Uniform2fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT,  8 },
	{ ConstantType::Uniform3fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT, 12 },
	{ ConstantType::Uniform4fv,   D3DXPC_VECTOR,         D3DXPT_FLOAT, 16 },
	{ ConstantType::Uniform3x3fv, D3DXPC_MATRIX_COLUMNS, D3DXPT_FLOAT, 36 },
	{ ConstantType::Uniform4x4fv, D3DXPC_MATRIX_COLUMNS, D3DXPT_FLOAT, 64 },
};

ConstantType::Enum findConstantTypeDx9(const D3DXCONSTANT_DESC& constDesc)
{
	uint32_t count = sizeof(s_constRemapDx9)/sizeof(ConstRemapDx9);
	for (uint32_t ii = 0; ii < count; ++ii)
	{
		const ConstRemapDx9& remap = s_constRemapDx9[ii];

		if (remap.paramClass == constDesc.Class
		&&  remap.paramType == constDesc.Type
		&&  (constDesc.Bytes%remap.paramBytes) == 0)
		{
			return remap.id;
		}
	}

	return ConstantType::Count;
}

static uint32_t s_optimizationLevelDx9[4] =
{
	D3DXSHADER_OPTIMIZATION_LEVEL0,
	D3DXSHADER_OPTIMIZATION_LEVEL1,
	D3DXSHADER_OPTIMIZATION_LEVEL2,
	D3DXSHADER_OPTIMIZATION_LEVEL3,
};

struct ConstRemapDx11
{
	ConstantType::Enum id;
	D3D_SHADER_VARIABLE_CLASS paramClass;
	D3D_SHADER_VARIABLE_TYPE paramType;
	uint32_t paramBytes;
};

static const ConstRemapDx11 s_constRemapDx11[7] =
{
	{ ConstantType::Uniform1iv,   D3D_SVC_SCALAR,         D3D_SVT_INT,    4 },
	{ ConstantType::Uniform1fv,   D3D_SVC_SCALAR,         D3D_SVT_FLOAT,  4 },
	{ ConstantType::Uniform2fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT,  8 },
	{ ConstantType::Uniform3fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 12 },
	{ ConstantType::Uniform4fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 16 },
	{ ConstantType::Uniform3x3fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 36 },
	{ ConstantType::Uniform4x4fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 64 },
};

ConstantType::Enum findConstantTypeDx11(const D3D11_SHADER_TYPE_DESC& constDesc, uint32_t _size)
{
	uint32_t count = sizeof(s_constRemapDx11)/sizeof(ConstRemapDx9);
	for (uint32_t ii = 0; ii < count; ++ii)
	{
		const ConstRemapDx11& remap = s_constRemapDx11[ii];

		if (remap.paramClass == constDesc.Class
		&&  remap.paramType == constDesc.Type
		&&  (_size%remap.paramBytes) == 0)
		{
			return remap.id;
		}
	}

	return ConstantType::Count;
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

	len = _writer->write(out, len);

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

private:
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

void printCode(const char* _code)
{
	fprintf(stderr, "Code:\n---\n");

	LineReader lr(_code);
	for (uint32_t line =  1; !lr.isEof(); ++line)
	{
		fprintf(stderr, "%3d: %s", line, lr.getLine().c_str() );
	}

	fprintf(stderr, "---\n");
}

void writeFile(const char* _filePath, void* _data, uint32_t _size)
{
	FILE* file = fopen(_filePath, "wb");
	if (NULL != file)
	{
		fwrite(_data, 1, _size, file);
		fclose(file);
	}
}

bool compileGLSLShader(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
	const glslopt_shader_type type = tolower(_cmdLine.findOption('\0', "type")[0]) == 'f' ? kGlslOptShaderFragment : kGlslOptShaderVertex;

	glslopt_ctx* ctx = glslopt_initialize(false);

	glslopt_shader* shader = glslopt_optimize(ctx, type, _code.c_str(), 0); 

	if( !glslopt_get_status(shader) )
	{
		printCode(_code.c_str() );
		fprintf(stderr, "Error: %s\n", glslopt_get_log(shader) );
		glslopt_cleanup(ctx);
		return false;
	}

	const char* optimizedShader = glslopt_get_output(shader);

	const char* profile = _cmdLine.findOption('p', "profile");
	if (NULL == profile)
	{
		writef(_writer, "#ifdef GL_ES\n");
		writef(_writer, "precision highp float;\n");
		writef(_writer, "#endif // GL_ES\n\n");
	}
	else
	{
		writef(_writer, "#version %s\n\n", profile);
	}

	_writer->write(optimizedShader, (int32_t)strlen(optimizedShader) );
	uint8_t nul = 0;
	bx::write(_writer, nul);

	glslopt_cleanup(ctx);

	return true;
}

bool compileHLSLShaderDx9(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
#if BX_PLATFORM_WINDOWS
	const char* profile = _cmdLine.findOption('p', "profile");
	if (NULL == profile)
	{
		fprintf(stderr, "Shader profile must be specified.\n");
		return false;
	}

	uint32_t flags = 0;
	flags |= _cmdLine.hasArg('\0', "debug") ? D3DXSHADER_DEBUG : 0;
	flags |= _cmdLine.hasArg('\0', "avoid-flow-control") ? D3DXSHADER_AVOID_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "no-preshader") ? D3DXSHADER_NO_PRESHADER : 0;
	flags |= _cmdLine.hasArg('\0', "partial-precision") ? D3DXSHADER_PARTIALPRECISION : 0;
	flags |= _cmdLine.hasArg('\0', "prefer-flow-control") ? D3DXSHADER_PREFER_FLOW_CONTROL : 0;
	flags |= _cmdLine.hasArg('\0', "backwards-compatibility") ? D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY : 0;
	
	bool werror = _cmdLine.hasArg('\0', "Werror");

	uint32_t optimization = 3;
	if (_cmdLine.hasArg(optimization, 'O') )
	{
		optimization = bx::uint32_min(optimization, countof(s_optimizationLevelDx9)-1);
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

	HRESULT hr = D3DXCompileShader(_code.c_str()
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
	if (FAILED(hr)
	|| (werror && NULL != errorMsg) )
	{
		printCode(_code.c_str() );
		fprintf(stderr, "Error: 0x%08x %s\n", (uint32_t)hr, (const char*)errorMsg->GetBufferPointer() );
		return false;
	}

	D3DXCONSTANTTABLE_DESC desc;
	hr = constantTable->GetDesc(&desc);
	if (FAILED(hr) )
	{
		fprintf(stderr, "Error 0x%08x\n", (uint32_t)hr);
		return false;
	}

	BX_TRACE("Creator: %s 0x%08x", desc.Creator, desc.Version);
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

		ConstantType::Enum type = findConstantTypeDx9(constDesc);
		if (ConstantType::Count != type)
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
		_writer->write(un.name.c_str(), nameSize);
		uint8_t type = un.type|fragmentBit;
		bx::write(_writer, type);
		bx::write(_writer, un.num);
		bx::write(_writer, un.regIndex);
		bx::write(_writer, un.regCount);

		BX_TRACE("%s, %s, %d, %d, %d"
			, un.name.c_str()
			, s_constantTypeName[un.type]
			, un.num
			, un.regIndex
			, un.regCount
			);
	}

	uint16_t shaderSize = (uint16_t)code->GetBufferSize();
	bx::write(_writer, shaderSize);
	_writer->write(code->GetBufferPointer(), shaderSize);
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
			std::string ofp = _cmdLine.findOption('o');
			ofp += ".disasm";

			writeFile(ofp.c_str(), disasm->GetBufferPointer(), disasm->GetBufferSize() );
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
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
#endif // BX_PLATFORM_WINDOWS
}

bool compileHLSLShaderDx11(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
#if BX_PLATFORM_WINDOWS
	const char* profile = _cmdLine.findOption('p', "profile");
	if (NULL == profile)
	{
		fprintf(stderr, "Shader profile must be specified.\n");
		return false;
	}

	uint32_t flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
	flags |= _cmdLine.hasArg('\0', "debug") ? D3DCOMPILE_DEBUG : 0;
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
		optimization = bx::uint32_min(optimization, countof(s_optimizationLevelDx11)-1);
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

	HRESULT hr = D3DCompile(_code.c_str()
		, _code.size()
		, NULL
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
		printCode(_code.c_str() );
		fprintf(stderr, BX_FILE_LINE_LITERAL "Error: 0x%08x %s\n", (uint32_t)hr, (char*)errorMsg->GetBufferPointer() );
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
		fprintf(stderr, BX_FILE_LINE_LITERAL "Error: 0x%08x\n", (uint32_t)hr);
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

	_writer->write(attrMask, sizeof(attrMask) );

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
						ConstantType::Enum type = findConstantTypeDx11(constDesc, varDesc.Size);

						if (ConstantType::Count != type
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

	bx::write(_writer, size);

	uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
	for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
	{
		const Uniform& un = *it;
		uint8_t nameSize = (uint8_t)un.name.size();
		bx::write(_writer, nameSize);
		_writer->write(un.name.c_str(), nameSize);
		uint8_t type = un.type|fragmentBit;
		bx::write(_writer, type);
		bx::write(_writer, un.num);
		bx::write(_writer, un.regIndex);
		bx::write(_writer, un.regCount);

		BX_TRACE("%s, %s, %d, %d, %d"
			, un.name.c_str()
			, s_constantTypeName[un.type]
			, un.num
			, un.regIndex
			, un.regCount
			);
	}

	uint16_t shaderSize = (uint16_t)code->GetBufferSize();
	bx::write(_writer, shaderSize);
	_writer->write(code->GetBufferPointer(), shaderSize);
	uint8_t nul = 0;
	bx::write(_writer, nul);

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
			std::string ofp = _cmdLine.findOption('o');
			ofp += ".disasm";

			writeFile(ofp.c_str(), disasm->GetBufferPointer(), (uint32_t)disasm->GetBufferSize() );
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
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
#endif // BX_PLATFORM_WINDOWS
}

struct Preprocessor
{
	Preprocessor(const char* _filePath, const char* _includeDir = NULL)
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

		m_default = "#define lowp\n#define mediump\n#define highp\n";
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
		bx::snprintf(temp, countof(temp)
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

// OpenGL #version Features Direct3D Features Shader Model
// 2.1    120      vf       9.0      vf       2.0
// 3.0    130
// 3.1    140
// 3.2    150      vgf
// 3.3    330               10.0     vgf      4.0
// 4.0    400      vhdgf
// 4.1    410
// 4.2    420               11.0     vhdgf    5.0

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "shaderc, bgfx shader compiler tool\n"
		  "Copyright 2011-2013 Branimir Karadzic. All rights reserved.\n"
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
		  "           ios\n"
		  "           linux\n"
		  "           nacl\n"
		  "           osx\n"
		  "           windows\n"
		  "      --type <type>             Shader type (vertex, fragment)\n"
		  "      --varyingdef <file path>  Path to varying.def.sc file.\n"

		  "\n"
		  "Options (DX9 and DX11 only):\n"

		  "\n"
		  "      --disasm      Disassemble compiled shader.\n"
		  "  -p, --profile     Shader model (f.e. ps_3_0).\n"

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

	Preprocessor preprocessor(filePath, includeDir);

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
	preprocessor.setDefaultDefine("BX_PLATFORM_IOS");
	preprocessor.setDefaultDefine("BX_PLATFORM_LINUX");
	preprocessor.setDefaultDefine("BX_PLATFORM_NACL");
	preprocessor.setDefaultDefine("BX_PLATFORM_OSX");
	preprocessor.setDefaultDefine("BX_PLATFORM_WINDOWS");
	preprocessor.setDefaultDefine("BX_PLATFORM_XBOX360");
	preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_GLSL");
	preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_HLSL");
	preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_FRAGMENT");
	preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_VERTEX");

	bool glsl = false;

	if (0 == bx::stricmp(platform, "android") )
	{
		preprocessor.setDefine("BX_PLATFORM_ANDROID=1");
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

	bool fragment = false;
	switch (tolower(type[0]) )
	{
	case 'f':
		preprocessor.setDefine("BGFX_SHADER_TYPE_FRAGMENT=1");
		fragment = true;
		break;

	case 'v':
		preprocessor.setDefine("BGFX_SHADER_TYPE_VERTEX=1");
		break;

	default:
		fprintf(stderr, "Unknown type: %s?!", type);
		return EXIT_FAILURE;
	}

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
			if (NULL != eol)
			{
				const char* type = parse;
				const char* name = parse = bx::strws(bx::strword(parse) );
				const char* column = parse = bx::strws(bx::strword(parse) );
				const char* semantics = parse = bx::strws(bx::strnws(parse) );
				const char* assign = parse = bx::strws(bx::strword(parse) );
				const char* init = parse = bx::strws(bx::strnws(parse) );

				if (type < eol
				&&  name < eol
				&&  column < eol
				&&  ':' == *column
				&&  semantics < eol)
				{
					Varying var;
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

		const size_t padding = 16;
		uint32_t size = (uint32_t)fsize(file);
		char* data = new char[size+padding+1];
		size = (uint32_t)fread(data, 1, size, file);
		// Compiler generates "error X3000: syntax error: unexpected end of file"
		// if input doesn't have empty line at EOF.
		data[size] = '\n';
		memset(&data[size+1], 0, padding);
		fclose(file);

		char* entry = strstr(data, "void main()");
		if (NULL == entry)
		{
			fprintf(stderr, "Shader entry point 'void main()' is not found.\n");
		}
		else
		{
			InOut shaderInputs;
			InOut shaderOutputs;
			uint32_t inputHash = 0;
			uint32_t outputHash = 0;

			const char* input = data;
			while (input[0] == '$')
			{
				const char* str = input+1;
				const char* eol = bx::streol(str);
				const char* nl = bx::strnl(eol);
				input = nl;

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
			}

			if (glsl)
			{
				preprocessor.writef(
					"#define ivec2 vec2\n"
					"#define ivec3 vec3\n"
					"#define ivec4 vec4\n"
					);


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
							preprocessor.writef("attribute %s %s;\n", var.m_type.c_str(), name);
						}
						else
						{
							preprocessor.writef("varying %s %s;\n", var.m_type.c_str(), name);
						}
					}
				}

				for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
				{
					VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
					if (varyingIt != varyingMap.end() )
					{
						const Varying& var = varyingIt->second;
						preprocessor.writef("varying %s %s;\n", var.m_type.c_str(), var.m_name.c_str() );
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
					"#define vec2 float2\n"
					"#define vec3 float3\n"
					"#define vec4 float4\n"
					"#define mat2 float2x2\n"
					"#define mat3 float3x3\n"
					"#define mat4 float4x4\n"
					);

				entry[4] = '_';

				if (fragment)
				{
					preprocessor.writef("#define void_main() \\\n");
					preprocessor.writef("\tvoid main(vec4 gl_FragCoord : SV_POSITION \\\n");
					for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
					{
						VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
						if (varyingIt != varyingMap.end() )
						{
							const Varying& var = varyingIt->second;
							preprocessor.writef("\t, %s %s : %s \\\n", var.m_type.c_str(), var.m_name.c_str(), var.m_semantics.c_str() );
						}
					}

					preprocessor.writef(
						", out vec4 gl_FragColor : SV_TARGET \\\n"
						);

					if (NULL != strstr(data, "gl_FragDepth") )
					{
						preprocessor.writef(
							", out float gl_FragDepth : SV_DEPTH \\\n"
							);
					}

					preprocessor.writef(
						")\n"
						);
				}
				else
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
						return false;
					}

					if (glsl)
					{
						const char* profile = cmdLine.findOption('p', "profile");
						if (NULL == profile)
						{
							writef(&writer, "#ifdef GL_ES\n");
							writef(&writer, "precision highp float;\n");
							writef(&writer, "#endif // GL_ES\n\n");
						}
						else
						{
							writef(&writer, "#version %s\n\n", profile);
						}
					}
					writer.write(preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );
					writer.close();

					return EXIT_SUCCESS;
				}

				bool compiled = false;

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
						return false;
					}

					if (fragment)
					{
						bx::write(writer, BGFX_CHUNK_MAGIC_FSH);
						bx::write(writer, inputHash);
					}
					else
					{
						bx::write(writer, BGFX_CHUNK_MAGIC_VSH);
						bx::write(writer, outputHash);
					}

					if (glsl)
					{
						compiled = compileGLSLShader(cmdLine, preprocessor.m_preprocessed, writer);
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

					return EXIT_SUCCESS;
				}
			}
		}

		delete [] data;
	}

	remove(outFilePath);

	fprintf(stderr, "Failed to build shader.\n");
	return EXIT_FAILURE;
}

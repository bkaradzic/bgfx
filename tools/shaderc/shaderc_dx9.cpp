/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "shaderc.h"

#if SHADERC_CONFIG_DIRECT3D9

#include <sal.h>
#define __D3DX9MATH_INL__ // not used and MinGW complains about type-punning
BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wundef");
#include <d3dx9.h>
BX_PRAGMA_DIAGNOSTIC_POP();

#if defined(__MINGW32__)
#	ifndef D3DXDisassembleShader
extern "C" HRESULT WINAPI D3DXDisassembleShader(CONST DWORD* pShader, BOOL EnableColorCode, LPCSTR pComments, LPD3DXBUFFER* ppDisassembly);
#	endif // D3DXDisassembleShader
#endif // !defined(__MINGW32__)

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

bool compileHLSLShaderDx9(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
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

	UniformArray uniforms;

	if (NULL != constantTable)
	{
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
			, getUniformTypeName(un.type)
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
}

#else

bool compileHLSLShaderDx9(bx::CommandLine& _cmdLine, const std::string& _code, bx::WriterI* _writer)
{
	BX_UNUSED(_cmdLine, _code, _writer);
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
}

#endif // SHADERC_CONFIG_DIRECT3D9

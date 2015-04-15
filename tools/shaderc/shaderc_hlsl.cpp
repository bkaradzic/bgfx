/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "shaderc.h"

#if SHADERC_CONFIG_HLSL

#include <d3dcompiler.h>
#include <d3d11shader.h>

#ifndef D3D_SVF_USED
#	define D3D_SVF_USED 2
#endif // D3D_SVF_USED

#ifndef IID_ID3D11ShaderReflection
// In case MinGW is missing IID...
static const GUID GUID_ID3D11ShaderReflection = { 0x0a233719, 0x3960, 0x4578, { 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1 } };
#	define IID_ID3D11ShaderReflection GUID_ID3D11ShaderReflection
#endif // IID_ID3D11ShaderReflection

struct CTHeader
{
	uint32_t Size;
	uint32_t Creator;
	uint32_t Version;
	uint32_t Constants;
	uint32_t ConstantInfo;
	uint32_t Flags;
	uint32_t Target;
};

struct CTInfo
{
	uint32_t Name;
	uint16_t RegisterSet;
	uint16_t RegisterIndex;
	uint16_t RegisterCount;
	uint16_t Reserved;
	uint32_t TypeInfo;
	uint32_t DefaultValue;
};

struct CTType
{
	uint16_t Class;
	uint16_t Type;
	uint16_t Rows;
	uint16_t Columns;
	uint16_t Elements;
	uint16_t StructMembers;
	uint32_t StructMemberInfo;
};

struct RemapInputSemantic
{
	bgfx::Attrib::Enum m_attr;
	const char* m_name;
	uint8_t m_index;
};

static const RemapInputSemantic s_remapInputSemantic[bgfx::Attrib::Count+1] =
{
	{ bgfx::Attrib::Position,  "POSITION",     0 },
	{ bgfx::Attrib::Normal,    "NORMAL",       0 },
	{ bgfx::Attrib::Tangent,   "TANGENT",      0 },
	{ bgfx::Attrib::Bitangent, "BITANGENT",    0 },
	{ bgfx::Attrib::Color0,    "COLOR",        0 },
	{ bgfx::Attrib::Color1,    "COLOR",        1 },
	{ bgfx::Attrib::Indices,   "BLENDINDICES", 0 },
	{ bgfx::Attrib::Weight,    "BLENDWEIGHT",  0 },
	{ bgfx::Attrib::TexCoord0, "TEXCOORD",     0 },
	{ bgfx::Attrib::TexCoord1, "TEXCOORD",     1 },
	{ bgfx::Attrib::TexCoord2, "TEXCOORD",     2 },
	{ bgfx::Attrib::TexCoord3, "TEXCOORD",     3 },
	{ bgfx::Attrib::TexCoord4, "TEXCOORD",     4 },
	{ bgfx::Attrib::TexCoord5, "TEXCOORD",     5 },
	{ bgfx::Attrib::TexCoord6, "TEXCOORD",     6 },
	{ bgfx::Attrib::TexCoord7, "TEXCOORD",     7 },
	{ bgfx::Attrib::Count,     "",             0 },
};

const RemapInputSemantic& findInputSemantic(const char* _name, uint8_t _index)
{
	for (uint32_t ii = 0; ii < bgfx::Attrib::Count; ++ii)
	{
		const RemapInputSemantic& ris = s_remapInputSemantic[ii];
		if (0 == strcmp(ris.m_name, _name)
		&&  ris.m_index == _index)
		{
			return ris;
		}
	}

	return s_remapInputSemantic[bgfx::Attrib::Count];
}

struct UniformRemap
{
	UniformType::Enum id;
	D3D_SHADER_VARIABLE_CLASS paramClass;
	D3D_SHADER_VARIABLE_TYPE paramType;
	uint8_t columns;
	uint8_t rows;
};

static const UniformRemap s_uniformRemap[7] =
{
	{ UniformType::Uniform1iv,   D3D_SVC_SCALAR,         D3D_SVT_INT,   0, 0 },
	{ UniformType::Uniform1fv,   D3D_SVC_SCALAR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform4fv,   D3D_SVC_VECTOR,         D3D_SVT_FLOAT, 0, 0 },
	{ UniformType::Uniform3x3fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 3, 3 },
	{ UniformType::Uniform4x4fv, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT, 4, 4 },
};

UniformType::Enum findUniformType(const D3D11_SHADER_TYPE_DESC& constDesc)
{
	for (uint32_t ii = 0; ii < BX_COUNTOF(s_uniformRemap); ++ii)
	{
		const UniformRemap& remap = s_uniformRemap[ii];

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

typedef std::vector<std::string> UniformNameList;

bool getReflectionDataDx9(ID3DBlob* _code, UniformArray& _uniforms)
{
	// see reference for magic values: https://msdn.microsoft.com/en-us/library/ff552891(VS.85).aspx
	const uint32_t D3DSIO_COMMENT = 0x0000FFFE;
	const uint32_t D3DSIO_END = 0x0000FFFF;
	const uint32_t D3DSI_OPCODE_MASK = 0x0000FFFF;
	const uint32_t D3DSI_COMMENTSIZE_MASK = 0x7FFF0000;
	const uint32_t CTAB_CONSTANT = MAKEFOURCC('C','T','A','B');

	// parse the shader blob for the constant table
	const size_t codeSize = _code->GetBufferSize();
	const uint32_t* ptr = (const uint32_t*)_code->GetBufferPointer();
	const uint32_t* end = (const uint32_t*)( (const uint8_t*)ptr + codeSize);
	const CTHeader* header = NULL;

	ptr++;	// first byte is shader type / version; skip it since we already know

	while (ptr < end && *ptr != D3DSIO_END)
	{
		uint32_t cur = *ptr++;
		if ( (cur & D3DSI_OPCODE_MASK) != D3DSIO_COMMENT)
		{
			continue;
		}

		// try to find CTAB comment block
		uint32_t commentSize = (cur & D3DSI_COMMENTSIZE_MASK) >> 16;
		uint32_t fourcc = *ptr;
		if (fourcc == CTAB_CONSTANT)
		{
			// found the constant table data
			header = (const CTHeader*)(ptr + 1);
			uint32_t tableSize = (commentSize - 1) * 4;
			if (tableSize < sizeof(CTHeader) || header->Size != sizeof(CTHeader) )
			{
				fprintf(stderr, "Error: Invalid constant table data\n");
				return false;
			}
			break;
		}

		// this is a different kind of comment section, so skip over it
		ptr += commentSize - 1;
	}

	if (!header)
	{
		fprintf(stderr, "Error: Could not find constant table data\n");
		return false;
	}

	const uint8_t* headerBytePtr = (const uint8_t*)header;
	const char* creator = (const char*)(headerBytePtr + header->Creator);

	BX_TRACE("Creator: %s 0x%08x", creator, header->Version);
	BX_TRACE("Num constants: %d", header->Constants);
	BX_TRACE("#   cl ty RxC   S  By Name");

	const CTInfo* ctInfoArray = (const CTInfo*)(headerBytePtr + header->ConstantInfo);
	for (uint32_t ii = 0; ii < header->Constants; ++ii)
	{
		const CTInfo& ctInfo = ctInfoArray[ii];
		const CTType& ctType = *(const CTType*)(headerBytePtr + ctInfo.TypeInfo);
		const char* name = (const char*)(headerBytePtr + ctInfo.Name);

		BX_TRACE("%3d %2d %2d [%dx%d] %d %s[%d] c%d (%d)"
			, ii
			, ctType.Class
			, ctType.Type
			, ctType.Rows
			, ctType.Columns
			, ctType.StructMembers
			, name
			, ctType.Elements
			, ctInfo.RegisterIndex
			, ctInfo.RegisterCount
			);

		D3D11_SHADER_TYPE_DESC desc;
		desc.Class = (D3D_SHADER_VARIABLE_CLASS)ctType.Class;
		desc.Type = (D3D_SHADER_VARIABLE_TYPE)ctType.Type;
		desc.Rows = ctType.Rows;
		desc.Columns = ctType.Columns;

		UniformType::Enum type = findUniformType(desc);
		if (UniformType::Count != type)
		{
			Uniform un;
			un.name = '$' == name[0] ? name + 1 : name;
			un.type = type;
			un.num = (uint8_t)ctType.Elements;
			un.regIndex = ctInfo.RegisterIndex;
			un.regCount = ctInfo.RegisterCount;
			_uniforms.push_back(un);
		}
	}

	return true;
}

bool getReflectionDataDx11(ID3DBlob* _code, bool _vshader, UniformArray& _uniforms, uint8_t& _numAttrs, uint16_t* _attrs, uint16_t& _size, UniformNameList& unusedUniforms)
{
	ID3D11ShaderReflection* reflect = NULL;
	HRESULT hr = D3DReflect(_code->GetBufferPointer()
		, _code->GetBufferSize()
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

	if (_vshader) // Only care about input semantic on vertex shaders
	{
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
			if (ris.m_attr != bgfx::Attrib::Count)
			{
				_attrs[_numAttrs] = bgfx::attribToId(ris.m_attr);
				++_numAttrs;
			}
		}
	}

	BX_TRACE("Output:");
	for (uint32_t ii = 0; ii < desc.OutputParameters; ++ii)
	{
		D3D11_SIGNATURE_PARAMETER_DESC spd;
		reflect->GetOutputParameterDesc(ii, &spd);
		BX_TRACE("\t%2d: %s%d, %d, %d", ii, spd.SemanticName, spd.SemanticIndex, spd.SystemValueType, spd.ComponentType);
	}

	for (uint32_t ii = 0, num = bx::uint32_min(1, desc.ConstantBuffers); ii < num; ++ii)
	{
		ID3D11ShaderReflectionConstantBuffer* cbuffer = reflect->GetConstantBufferByIndex(ii);
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		hr = cbuffer->GetDesc(&bufferDesc);

		_size = (uint16_t)bufferDesc.Size;

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
						UniformType::Enum uniformType = findUniformType(constDesc);

						if (UniformType::Count != uniformType
						&&  0 != (varDesc.uFlags & D3D_SVF_USED) )
						{
							Uniform un;
							un.name = varDesc.Name;
							un.type = uniformType;
							un.num = constDesc.Elements;
							un.regIndex = varDesc.StartOffset;
							un.regCount = BX_ALIGN_16(varDesc.Size) / 16;
							_uniforms.push_back(un);

							BX_TRACE("\t%s, %d, size %d, flags 0x%08x, %d (used)"
								, varDesc.Name
								, varDesc.StartOffset
								, varDesc.Size
								, varDesc.uFlags
								, uniformType
								);
						}
						else
						{
							if (0 == (varDesc.uFlags & D3D_SVF_USED) )
							{
								unusedUniforms.push_back(varDesc.Name);
							}

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

	if (NULL != reflect)
	{
		reflect->Release();
	}

	return true;
}

bool compileHLSLShader(bx::CommandLine& _cmdLine, uint32_t _d3d, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
{
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
	uint8_t numAttrs = 0;
	uint16_t attrs[bgfx::Attrib::Count];
	uint16_t size = 0;

	if (_d3d == 9)
	{
		if (!getReflectionDataDx9(code, uniforms) )
		{
			return false;
		}
	}
	else
	{
		UniformNameList unusedUniforms;
		if (!getReflectionDataDx11(code, profile[0] == 'v', uniforms, numAttrs, attrs, size, unusedUniforms) )
		{
			return false;
		}

		if (_firstPass
		&&  unusedUniforms.size() > 0)
		{
			const size_t strLength = strlen("uniform");

			// first time through, we just find unused uniforms and get rid of them
			std::string output;
			LineReader reader(_code.c_str() );
			while (!reader.isEof() )
			{
				std::string line = reader.getLine();
				for (UniformNameList::const_iterator it = unusedUniforms.begin(), itEnd = unusedUniforms.end(); it != itEnd; ++it)
				{
					size_t index = line.find("uniform ");
					if (index == std::string::npos)
					{
						continue;
					}

					// matching lines like:  uniform u_name;
					// we want to replace "uniform" with "static" so that it's no longer
					// included in the uniform blob that the application must upload
					// we can't just remove them, because unused functions might still reference
					// them and cause a compile error when they're gone
					if (!!bx::findIdentifierMatch(line.c_str(), it->c_str() ) )
					{
						line = line.replace(index, strLength, "static");
						unusedUniforms.erase(it);
						break;
					}
				}

				output += line;
			}

			// recompile with the unused uniforms converted to statics
			return compileHLSLShader(_cmdLine, _d3d, output.c_str(), _writer, false);
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

	{
		ID3DBlob* stripped;
		hr = D3DStripShader(code->GetBufferPointer()
			, code->GetBufferSize()
			, D3DCOMPILER_STRIP_REFLECTION_DATA
			| D3DCOMPILER_STRIP_TEST_BLOBS
			, &stripped
			);

		if (SUCCEEDED(hr) )
		{
			code->Release();
			code = stripped;
		}
	}

	uint16_t shaderSize = (uint16_t)code->GetBufferSize();
	bx::write(_writer, shaderSize);
	bx::write(_writer, code->GetBufferPointer(), shaderSize);
	uint8_t nul = 0;
	bx::write(_writer, nul);

	if (_d3d > 9)
	{
		bx::write(_writer, numAttrs);
		bx::write(_writer, attrs, numAttrs*sizeof(uint16_t) );

		bx::write(_writer, size);
	}

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

	if (NULL != errorMsg)
	{
		errorMsg->Release();
	}

	code->Release();

	return true;
}

#else

bool compileHLSLShader(bx::CommandLine& _cmdLine, uint32_t _d3d, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
{
	BX_UNUSED(_cmdLine, _d3d, _code, _writer, _firstPass);
	fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
	return false;
}

#endif // SHADERC_CONFIG_HLSL

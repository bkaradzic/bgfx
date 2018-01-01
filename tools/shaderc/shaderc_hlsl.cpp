/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"

#if SHADERC_CONFIG_HLSL

#if defined(__MINGW32__)
#	define __REQUIRED_RPCNDR_H_VERSION__ 475
#	define __in
#	define __out
#endif // defined(__MINGW32__)

#define COM_NO_WINDOWS_H
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <bx/os.h>

#ifndef D3D_SVF_USED
#	define D3D_SVF_USED 2
#endif // D3D_SVF_USED

namespace bgfx { namespace hlsl
{
	typedef HRESULT(WINAPI* PFN_D3D_COMPILE)(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData
		, _In_ SIZE_T SrcDataSize
		, _In_opt_ LPCSTR pSourceName
		, _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL) ) CONST D3D_SHADER_MACRO* pDefines
		, _In_opt_ ID3DInclude* pInclude
		, _In_opt_ LPCSTR pEntrypoint
		, _In_ LPCSTR pTarget
		, _In_ UINT Flags1
		, _In_ UINT Flags2
		, _Out_ ID3DBlob** ppCode
		, _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs
		);

	typedef HRESULT(WINAPI* PFN_D3D_DISASSEMBLE)(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData
		, _In_ SIZE_T SrcDataSize
		, _In_ UINT Flags
		, _In_opt_ LPCSTR szComments
		, _Out_ ID3DBlob** ppDisassembly
		);

	typedef HRESULT(WINAPI* PFN_D3D_REFLECT)(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData
		, _In_ SIZE_T SrcDataSize
		, _In_ REFIID pInterface
		, _Out_ void** ppReflector
		);

	typedef HRESULT(WINAPI* PFN_D3D_STRIP_SHADER)(_In_reads_bytes_(BytecodeLength) LPCVOID pShaderBytecode
		, _In_ SIZE_T BytecodeLength
		, _In_ UINT uStripFlags
		, _Out_ ID3DBlob** ppStrippedBlob
		);

	PFN_D3D_COMPILE      D3DCompile;
	PFN_D3D_DISASSEMBLE  D3DDisassemble;
	PFN_D3D_REFLECT      D3DReflect;
	PFN_D3D_STRIP_SHADER D3DStripShader;

	struct D3DCompiler
	{
		const char* fileName;
		const GUID  IID_ID3D11ShaderReflection;
	};

	static const D3DCompiler s_d3dcompiler[] =
	{ // BK - the only different method in interface is GetRequiresFlags at the end
	  //      of IID_ID3D11ShaderReflection47 (which is not used anyway).
		{ "D3DCompiler_47.dll", { 0x8d536ca1, 0x0cca, 0x4956, { 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84 } } },
		{ "D3DCompiler_46.dll", { 0x0a233719, 0x3960, 0x4578, { 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1 } } },
		{ "D3DCompiler_45.dll", { 0x0a233719, 0x3960, 0x4578, { 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1 } } },
		{ "D3DCompiler_44.dll", { 0x0a233719, 0x3960, 0x4578, { 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1 } } },
		{ "D3DCompiler_43.dll", { 0x0a233719, 0x3960, 0x4578, { 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1 } } },
	};

	static const D3DCompiler* s_compiler;
	static void* s_d3dcompilerdll;

	const D3DCompiler* load()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_d3dcompiler); ++ii)
		{
			const D3DCompiler* compiler = &s_d3dcompiler[ii];
			s_d3dcompilerdll = bx::dlopen(compiler->fileName);
			if (NULL == s_d3dcompilerdll)
			{
				continue;
			}

			D3DCompile     = (PFN_D3D_COMPILE     )bx::dlsym(s_d3dcompilerdll, "D3DCompile");
			D3DDisassemble = (PFN_D3D_DISASSEMBLE )bx::dlsym(s_d3dcompilerdll, "D3DDisassemble");
			D3DReflect     = (PFN_D3D_REFLECT     )bx::dlsym(s_d3dcompilerdll, "D3DReflect");
			D3DStripShader = (PFN_D3D_STRIP_SHADER)bx::dlsym(s_d3dcompilerdll, "D3DStripShader");

			if (NULL == D3DCompile
			||  NULL == D3DDisassemble
			||  NULL == D3DReflect
			||  NULL == D3DStripShader)
			{
				bx::dlclose(s_d3dcompilerdll);
				continue;
			}

			if (g_verbose)
			{
				char filePath[MAX_PATH];
				GetModuleFileNameA( (HMODULE)s_d3dcompilerdll, filePath, sizeof(filePath) );
				BX_TRACE("Loaded %s compiler (%s).", compiler->fileName, filePath);
			}

			return compiler;
		}

		fprintf(stderr, "Error: Unable to open D3DCompiler_*.dll shader compiler.\n");
		return NULL;
	}

	void unload()
	{
		bx::dlclose(s_d3dcompilerdll);
	}

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

	static const RemapInputSemantic s_remapInputSemantic[bgfx::Attrib::Count + 1] =
	{
		{ bgfx::Attrib::Position,  "POSITION",     0 },
		{ bgfx::Attrib::Normal,    "NORMAL",       0 },
		{ bgfx::Attrib::Tangent,   "TANGENT",      0 },
		{ bgfx::Attrib::Bitangent, "BITANGENT",    0 },
		{ bgfx::Attrib::Color0,    "COLOR",        0 },
		{ bgfx::Attrib::Color1,    "COLOR",        1 },
		{ bgfx::Attrib::Color2,    "COLOR",        2 },
		{ bgfx::Attrib::Color3,    "COLOR",        3 },
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
			if (0 == bx::strCmp(ris.m_name, _name)
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

	static const UniformRemap s_uniformRemap[] =
	{
		{ UniformType::Int1, D3D_SVC_SCALAR,         D3D_SVT_INT,         0, 0 },
		{ UniformType::Vec4, D3D_SVC_VECTOR,         D3D_SVT_FLOAT,       0, 0 },
		{ UniformType::Mat3, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT,       3, 3 },
		{ UniformType::Mat4, D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT,       4, 4 },
		{ UniformType::Int1, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER,     0, 0 },
		{ UniformType::Int1, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER2D,   0, 0 },
		{ UniformType::Int1, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER3D,   0, 0 },
		{ UniformType::Int1, D3D_SVC_OBJECT,         D3D_SVT_SAMPLERCUBE, 0, 0 },
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
				&&  remap.rows == constDesc.Rows)
				{
					return remap.id;
				}
			}
		}

		return UniformType::Count;
	}

	static uint32_t s_optimizationLevelD3D11[4] =
	{
		D3DCOMPILE_OPTIMIZATION_LEVEL0,
		D3DCOMPILE_OPTIMIZATION_LEVEL1,
		D3DCOMPILE_OPTIMIZATION_LEVEL2,
		D3DCOMPILE_OPTIMIZATION_LEVEL3,
	};

	typedef std::vector<std::string> UniformNameList;

	static bool isSampler(D3D_SHADER_VARIABLE_TYPE _svt)
	{
		switch (_svt)
		{
		case D3D_SVT_SAMPLER:
		case D3D_SVT_SAMPLER1D:
		case D3D_SVT_SAMPLER2D:
		case D3D_SVT_SAMPLER3D:
		case D3D_SVT_SAMPLERCUBE:
			return true;

		default:
			break;
		}

		return false;
	}

	bool getReflectionDataD3D9(ID3DBlob* _code, UniformArray& _uniforms)
	{
		// see reference for magic values: https://msdn.microsoft.com/en-us/library/ff552891(VS.85).aspx
		const uint32_t D3DSIO_COMMENT = 0x0000FFFE;
		const uint32_t D3DSIO_END = 0x0000FFFF;
		const uint32_t D3DSI_OPCODE_MASK = 0x0000FFFF;
		const uint32_t D3DSI_COMMENTSIZE_MASK = 0x7FFF0000;
		const uint32_t CTAB_CONSTANT = MAKEFOURCC('C', 'T', 'A', 'B');

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
				un.type = isSampler(desc.Type)
					? UniformType::Enum(BGFX_UNIFORM_SAMPLERBIT | type)
					: type
					;
				un.num = (uint8_t)ctType.Elements;
				un.regIndex = ctInfo.RegisterIndex;
				un.regCount = ctInfo.RegisterCount;

				_uniforms.push_back(un);
			}
		}

		return true;
	}

	bool getReflectionDataD3D11(ID3DBlob* _code, bool _vshader, UniformArray& _uniforms, uint8_t& _numAttrs, uint16_t* _attrs, uint16_t& _size, UniformNameList& unusedUniforms)
	{
		ID3D11ShaderReflection* reflect = NULL;
		HRESULT hr = D3DReflect(_code->GetBufferPointer()
			, _code->GetBufferSize()
			, s_compiler->IID_ID3D11ShaderReflection
			, (void**)&reflect
			);
		if (FAILED(hr) )
		{
			fprintf(stderr, "Error: D3DReflect failed 0x%08x\n", (uint32_t)hr);
			return false;
		}

		D3D11_SHADER_DESC desc;
		hr = reflect->GetDesc(&desc);
		if (FAILED(hr) )
		{
			fprintf(stderr, "Error: ID3D11ShaderReflection::GetDesc failed 0x%08x\n", (uint32_t)hr);
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

				const RemapInputSemantic& ris = findInputSemantic(spd.SemanticName, uint8_t(spd.SemanticIndex) );
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
								un.num = uint8_t(constDesc.Elements);
								un.regIndex = uint16_t(varDesc.StartOffset);
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
				if (D3D_SIT_SAMPLER == bindDesc.Type)
				{
					BX_TRACE("\t%s, %d, %d, %d"
						, bindDesc.Name
						, bindDesc.Type
						, bindDesc.BindPoint
						, bindDesc.BindCount
						);

					const char * end = bx::strFind(bindDesc.Name, "Sampler");
					if (NULL != end)
					{
						Uniform un;
						un.name.assign(bindDesc.Name, (end - bindDesc.Name) );
						un.type = UniformType::Enum(BGFX_UNIFORM_SAMPLERBIT | UniformType::Int1);
						un.num = 1;
						un.regIndex = uint16_t(bindDesc.BindPoint);
						un.regCount = uint16_t(bindDesc.BindCount);
						_uniforms.push_back(un);
					}
				}
			}
		}

		if (NULL != reflect)
		{
			reflect->Release();
		}

		return true;
	}

	static bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
	{
		const char* profile = _options.profile.c_str();

		if (profile[0] == '\0')
		{
			fprintf(stderr, "Error: Shader profile must be specified.\n");
			return false;
		}

		s_compiler = load();

		bool result = false;
		bool debug = _options.debugInformation;

		uint32_t flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
		flags |= debug ? D3DCOMPILE_DEBUG : 0;
		flags |= _options.avoidFlowControl ? D3DCOMPILE_AVOID_FLOW_CONTROL : 0;
		flags |= _options.noPreshader ? D3DCOMPILE_NO_PRESHADER : 0;
		flags |= _options.partialPrecision ? D3DCOMPILE_PARTIAL_PRECISION : 0;
		flags |= _options.preferFlowControl ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0;
		flags |= _options.backwardsCompatibility ? D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY : 0;

		bool werror = _options.warningsAreErrors;

		if (werror)
		{
			flags |= D3DCOMPILE_WARNINGS_ARE_ERRORS;
		}

		if (_options.optimize )
		{
			uint32_t optimization = bx::uint32_min(_options.optimizationLevel, BX_COUNTOF(s_optimizationLevelD3D11) - 1);
			flags |= s_optimizationLevelD3D11[optimization];
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
			hlslfp = _options.outputFilePath + ".hlsl";
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

			int32_t line   = 0;
			int32_t column = 0;
			int32_t start  = 0;
			int32_t end    = INT32_MAX;

			bool found = false
				|| 2 == sscanf(log, "(%u,%u):",  &line, &column)
				|| 2 == sscanf(log, " :%u:%u: ", &line, &column)
				;

			if (found
			&&  0 != line)
			{
				start = bx::uint32_imax(1, line - 10);
				end   = start + 20;
			}

			printCode(_code.c_str(), line, start, end, column);
			fprintf(stderr, "Error: D3DCompile failed 0x%08x %s\n", (uint32_t)hr, log);
			errorMsg->Release();
			return false;
		}

		UniformArray uniforms;
		uint8_t numAttrs = 0;
		uint16_t attrs[bgfx::Attrib::Count];
		uint16_t size = 0;

		if (_version == 9)
		{
			if (!getReflectionDataD3D9(code, uniforms) )
			{
				fprintf(stderr, "Error: Unable to get D3D9 reflection data.\n");
				goto error;
			}
		}
		else
		{
			UniformNameList unusedUniforms;
			if (!getReflectionDataD3D11(code, profile[0] == 'v', uniforms, numAttrs, attrs, size, unusedUniforms) )
			{
				fprintf(stderr, "Error: Unable to get D3D11 reflection data.\n");
				goto error;
			}

			if (_firstPass
			&&  unusedUniforms.size() > 0)
			{
				const size_t strLength = bx::strLen("uniform");

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

						for (UniformNameList::iterator it = unusedUniforms.begin(), itEnd = unusedUniforms.end(); it != itEnd; ++it)
						{
							size_t index = strLine.find("uniform ");
							if (index == std::string::npos)
							{
								continue;
							}

							// matching lines like:  uniform u_name;
							// we want to replace "uniform" with "static" so that it's no longer
							// included in the uniform blob that the application must upload
							// we can't just remove them, because unused functions might still reference
							// them and cause a compile error when they're gone
							if (!!bx::findIdentifierMatch(strLine.c_str(), it->c_str() ) )
							{
								strLine = strLine.replace(index, strLength, "static");
								unusedUniforms.erase(it);
								break;
							}
						}

						output += strLine;
					}
				}

				// recompile with the unused uniforms converted to statics
				return compile(_options, _version, output.c_str(), _writer, false);
			}
		}

		{
			uint16_t count = (uint16_t)uniforms.size();
			bx::write(_writer, count);

			uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
			for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
			{
				const Uniform& un = *it;
				uint8_t nameSize = (uint8_t)un.name.size();
				bx::write(_writer, nameSize);
				bx::write(_writer, un.name.c_str(), nameSize);
				uint8_t type = uint8_t(un.type | fragmentBit);
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

		{
			uint32_t shaderSize = uint32_t(code->GetBufferSize() );
			bx::write(_writer, shaderSize);
			bx::write(_writer, code->GetBufferPointer(), shaderSize);
			uint8_t nul = 0;
			bx::write(_writer, nul);
		}

		if (_version > 9)
		{
			bx::write(_writer, numAttrs);
			bx::write(_writer, attrs, numAttrs*sizeof(uint16_t) );

			bx::write(_writer, size);
		}

		if (_options.disasm )
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
				std::string disasmfp = _options.outputFilePath + ".disasm";

				writeFile(disasmfp.c_str(), disasm->GetBufferPointer(), (uint32_t)disasm->GetBufferSize() );
				disasm->Release();
			}
		}

		if (NULL != errorMsg)
		{
			errorMsg->Release();
		}

		result = true;

	error:
		code->Release();
		unload();
		return result;
	}

} // namespace hlsl

	bool compileHLSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		return hlsl::compile(_options, _version, _code, _writer, true);
	}

} // namespace bgfx

#else

namespace bgfx
{
	bool compileHLSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
		BX_UNUSED(_options, _version, _code, _writer);
		fprintf(stderr, "HLSL compiler is not supported on this platform.\n");
		return false;
	}

} // namespace bgfx

#endif // SHADERC_CONFIG_HLSL

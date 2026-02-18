/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "shaderc.h"
#include <bx/os.h>

#if SHADERC_CONFIG_HAS_DXC

#if BX_PLATFORM_WINDOWS
#	include <windows.h>
#endif // BX_PLATFORM_WINDOWS

#ifndef _Maybenull_
#	define _Maybenull_
#endif // _Maybenull_

#ifndef _In_bytecount_
#	define _In_bytecount_(size)
#endif // _In_bytecount_

#include <unknwnbase.h>
#include <dxcapi.h>
#include <winapifamily.h>
#include <d3d12shader.h>

namespace bgfx { namespace dxil
{
	static const GUID IID_ID3D12ShaderReflection               = { 0x5a58797d, 0xa72c, 0x478d, { 0x8b, 0xa2, 0xef, 0xc6, 0xb0, 0xef, 0xe8, 0x8e } };
	static const GUID IID_ID3D12ShaderReflectionConstantBuffer = { 0xc59598b4, 0x48b3, 0x4869, { 0xb9, 0xb1, 0xb1, 0x61, 0x8b, 0x14, 0xa8, 0xb7 } };
	static const GUID IID_IDxcBlob                             = { 0x8ba5fb08, 0x5195, 0x40e2, { 0xac, 0x58, 0x0d, 0x98, 0x9c, 0x3a, 0x01, 0x02 } };
	static const GUID IID_IDxcBlobEncoding                     = { 0x7241d424, 0x2646, 0x4191, { 0x97, 0xc0, 0x98, 0xe9, 0x6e, 0x42, 0xfc, 0x68 } };
	static const GUID IID_IDxcBlobUtf8                         = { 0x3da636c9, 0xba71, 0x4024, { 0xa3, 0x01, 0x30, 0xcb, 0xf1, 0x25, 0x30, 0x5b } };
	static const GUID IID_IDxcCompiler3                        = { 0x228b4687, 0x5a6a, 0x4730, { 0x90, 0x0c, 0x97, 0x02, 0xb2, 0x20, 0x3f, 0x54 } };
	static const GUID IID_IDxcResult                           = { 0x58346cda, 0xdde7, 0x4497, { 0x94, 0x61, 0x6f, 0x87, 0xaf, 0x5e, 0x06, 0x59 } };
	static const GUID IID_IDxcUtils                            = { 0x4605c4cb, 0x2019, 0x492a, { 0xad, 0xa4, 0x65, 0xf2, 0x0b, 0xb7, 0xd6, 0x7f } };

	template<typename Ty>
	void dxcRelease(Ty*& _ptr)
	{
		if (NULL != _ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
	}

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
		{ UniformType::Sampler, D3D_SVC_SCALAR,         D3D_SVT_INT,         0, 0 },
		{ UniformType::Vec4,    D3D_SVC_VECTOR,         D3D_SVT_FLOAT,       0, 0 },
		{ UniformType::Mat3,    D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT,       3, 3 },
		{ UniformType::Mat4,    D3D_SVC_MATRIX_COLUMNS, D3D_SVT_FLOAT,       4, 4 },
		{ UniformType::Sampler, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER,     0, 0 },
		{ UniformType::Sampler, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER2D,   0, 0 },
		{ UniformType::Sampler, D3D_SVC_OBJECT,         D3D_SVT_SAMPLER3D,   0, 0 },
		{ UniformType::Sampler, D3D_SVC_OBJECT,         D3D_SVT_SAMPLERCUBE, 0, 0 },
	};

	UniformType::Enum findUniformType(const D3D12_SHADER_TYPE_DESC& constDesc)
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

	static const wchar_t* s_optimizationLevel[] =
	{
		DXC_ARG_OPTIMIZATION_LEVEL0,
		DXC_ARG_OPTIMIZATION_LEVEL1,
		DXC_ARG_OPTIMIZATION_LEVEL2,
		DXC_ARG_OPTIMIZATION_LEVEL3,
	};

	typedef std::vector<std::string> UniformNameList;

	struct Dxc
	{
		IDxcCompiler3* compiler3 = NULL;
		IDxcUtils*     utils     = NULL;
		void*          dll       = NULL;
	};

	void unload(Dxc& _dxc)
	{
		dxcRelease(_dxc.utils);
		dxcRelease(_dxc.compiler3);

		bx::dlclose(_dxc.dll);
		_dxc.dll = NULL;
	}

	Dxc load()
	{
		const char* dxcCompilerDllName =
#if BX_PLATFORM_WINDOWS
			"dxcompiler.dll"
#elif BX_PLATFORM_LINUX
			"libdxcompiler.so"
#else
			"dxcompiler???"
#endif // BX_PLATFORM_
			;

		HRESULT hr = E_FAIL;

		bx::FilePath dxcCompilerDll = bx::FilePath(bx::Dir::Executable).getPath();
		dxcCompilerDll.join(dxcCompilerDllName);

		Dxc dxc;
		dxc.dll = bx::dlopen(dxcCompilerDll.getCPtr() );

		if (NULL == dxc.dll)
		{
			BX_TRACE("Error: Unable to open %s shader compiler.\n", dxcCompilerDll.getCPtr() );
			return Dxc{};
		}

		DxcCreateInstanceProc DxcCreateInstance = bx::dlsym<DxcCreateInstanceProc>(dxc.dll, "DxcCreateInstance");
		if (NULL == DxcCreateInstance)
		{
			BX_TRACE("Error: Symbol 'DxcCreateInstance' not found.\n");

			unload(dxc);
			return Dxc{};
		}

		hr = DxcCreateInstance(CLSID_DxcCompiler, IID_IDxcCompiler3, (void**)&dxc.compiler3);
		if (FAILED(hr) )
		{
			BX_TRACE("Error: DxcCreateInstance IID_IDxcCompiler3 failed 0x%08x\n", (uint32_t)hr);

			unload(dxc);
			return Dxc{};
		}

		hr = DxcCreateInstance(CLSID_DxcUtils, IID_IDxcUtils, (void**)&dxc.utils);
		if (FAILED(hr) )
		{
			BX_TRACE("Error: DxcCreateInstance IID_IDxcUtils failed 0x%08x\n", (uint32_t)hr);

			unload(dxc);
			return Dxc{};
		}

		return dxc;
	}

	bool getReflectionData(ID3D12ShaderReflection* _shaderReflection, bool _vshader, UniformArray& _uniforms, uint8_t& _numAttrs, uint16_t* _attrs, uint16_t& _size, UniformNameList& unusedUniforms, bx::WriterI* _messageWriter)
	{
		bx::Error messageErr;
		HRESULT hr = E_FAIL;

		D3D12_SHADER_DESC desc;
		hr = _shaderReflection->GetDesc(&desc);

		if (FAILED(hr) )
		{
			bx::write(_messageWriter, &messageErr, "Error: ID3D12ShaderReflection::GetDesc failed 0x%08x\n", (uint32_t)hr);
			return false;
		}

		BX_TRACE("Creator: %s 0x%08x", desc.Creator, desc.Version);
		BX_TRACE("Num constant buffers: %d", desc.ConstantBuffers);

		BX_TRACE("Input:");

		if (_vshader) // Only care about input semantic on vertex shaders
		{
			for (uint32_t ii = 0; ii < desc.InputParameters; ++ii)
			{
				D3D12_SIGNATURE_PARAMETER_DESC spd;
				_shaderReflection->GetInputParameterDesc(ii, &spd);
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
			D3D12_SIGNATURE_PARAMETER_DESC spd;
			_shaderReflection->GetOutputParameterDesc(ii, &spd);
			BX_TRACE("\t%2d: %s%d, %d, %d", ii, spd.SemanticName, spd.SemanticIndex, spd.SystemValueType, spd.ComponentType);
		}

		for (uint32_t ii = 0, num = bx::uint32_min(1, desc.ConstantBuffers); ii < num; ++ii)
		{
			ID3D12ShaderReflectionConstantBuffer* cbuffer = _shaderReflection->GetConstantBufferByIndex(ii);
			D3D12_SHADER_BUFFER_DESC bufferDesc;
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
					ID3D12ShaderReflectionVariable* var = cbuffer->GetVariableByIndex(jj);
					ID3D12ShaderReflectionType* type = var->GetType();

					D3D12_SHADER_VARIABLE_DESC varDesc;
					hr = var->GetDesc(&varDesc);

					if (SUCCEEDED(hr) )
					{
						D3D12_SHADER_TYPE_DESC constDesc;
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
								un.regCount = uint16_t(bx::alignUp(varDesc.Size, 16) / 16);
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
			D3D12_SHADER_INPUT_BIND_DESC bindDesc;

			hr = _shaderReflection->GetResourceBindingDesc(ii, &bindDesc);
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

					bx::StringView end = bx::strFind(bindDesc.Name, "Sampler");

					if (!end.isEmpty() )
					{
						Uniform un;
						un.name.assign(bindDesc.Name, (end.getPtr() - bindDesc.Name) );
						un.type = UniformType::Enum(kUniformSamplerBit | UniformType::Sampler);
						un.num = 1;
						un.regIndex = uint16_t(bindDesc.BindPoint);
						un.regCount = uint16_t(bindDesc.BindCount);
						_uniforms.push_back(un);
					}
				}
			}
		}

		return true;
	}

	static bool compile(Dxc& _dxc, const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _shaderWriter, bx::WriterI* _messageWriter, bool _firstPass)
	{
		bx::Error messageErr;
		bx::ErrorAssert err;

		HRESULT hr = E_FAIL;

		{
			const DxcBuffer source =
			{
				.Ptr      = _code.c_str(),
				.Size     = _code.size(),
				.Encoding = DXC_CP_UTF8,
			};

			const wchar_t* args[32];
			uint32_t numArgs = 0;

			args[numArgs++] = L"-E";
			args[numArgs++] = L"main";

			args[numArgs++] = L"-T";
			if ('c' == _options.shaderType)
			{
				args[numArgs++] = L"cs_6_0";
			}
			else if ('f' == _options.shaderType)
			{
				args[numArgs++] = L"ps_6_0";
			}
			else if ('v' == _options.shaderType)
			{
				args[numArgs++] = L"vs_6_0";
			}

			if (_options.warningsAreErrors)
			{
				args[numArgs++] = DXC_ARG_WARNINGS_ARE_ERRORS;
			}

			if (_options.optimize)
			{
				const uint32_t optimization = bx::uint32_min(_options.optimizationLevel, BX_COUNTOF(s_optimizationLevel) - 1);
				args[numArgs++] = s_optimizationLevel[optimization];
			}
			else
			{
				args[numArgs++] = DXC_ARG_SKIP_OPTIMIZATIONS;
			}

			if (_options.debugInformation)
			{
				args[numArgs++] = DXC_ARG_DEBUG;
			}

			if (_options.preferFlowControl)
			{
				args[numArgs++] = DXC_ARG_PREFER_FLOW_CONTROL;
			}

			if (!_firstPass)
			{
				args[numArgs++] = L"-Zs";
				args[numArgs++] = L"-Qstrip_debug";
				args[numArgs++] = L"-Qstrip_priv";
				args[numArgs++] = L"-Qstrip_reflect";
				args[numArgs++] = L"-Qstrip_rootsignature";
			}

			BX_ASSERT(numArgs < BX_COUNTOF(args), "");

			IDxcResult* dxcResult = NULL;
			hr = _dxc.compiler3->Compile(
					&source
					, args
					, numArgs
					, NULL
					, IID_IDxcResult
					, (void**)&dxcResult
					);

			if (FAILED(hr) )
			{
				BX_TRACE("Compile failed %x", hr);
				return false;
			}

			dxcResult->GetStatus(&hr);

			if (FAILED(hr) )
			{
				bx::write(_messageWriter, &messageErr, "Status: %x\n", hr);

				BX_TRACE("%s\n", _code.c_str() );

				IDxcBlobUtf8* dxcErrors = NULL;
				dxcResult->GetOutput(DXC_OUT_ERRORS, IID_IDxcBlobUtf8, (void**)&dxcErrors, NULL);
				if (NULL != dxcErrors)
				{
					bx::write(_messageWriter, &messageErr, "Error: %s\n", dxcErrors->GetStringPointer() );

					dxcRelease(dxcErrors);
				}

				return false;
			}

			IDxcBlob* dxcReflectionBlob = NULL;
			hr = dxcResult->GetOutput(DXC_OUT_REFLECTION, IID_IDxcBlob, (void**)&dxcReflectionBlob, NULL);
			if (FAILED(hr) )
			{
				bx::write(_messageWriter, &messageErr, "Error: GetOutput DXC_OUT_REFLECTION 0x%08x\n", (uint32_t)hr);
				return false;
			}

			const DxcBuffer reflection =
			{
				.Ptr      = dxcReflectionBlob->GetBufferPointer(),
				.Size     = dxcReflectionBlob->GetBufferSize(),
				.Encoding = DXC_CP_ACP,
			};

			ID3D12ShaderReflection* shaderReflection;
			hr = _dxc.utils->CreateReflection(&reflection, IID_ID3D12ShaderReflection, (void**)&shaderReflection);

			if (FAILED(hr) )
			{
				bx::write(_messageWriter, &messageErr, "Error: CreateReflection failed 0x%08x\n", (uint32_t)hr);
				return false;
			}

			UniformArray uniforms;
			uint8_t numAttrs = 0;
			uint16_t attrs[bgfx::Attrib::Count];
			uint16_t size = 0;

			UniformNameList unusedUniforms;
			if (!getReflectionData(shaderReflection, _options.shaderType == 'v', uniforms, numAttrs, attrs, size, unusedUniforms, _messageWriter) )
			{
				bx::write(_messageWriter, &messageErr, "Error: Unable to get DXC reflection data.\n");
				return false;
			}

			dxcRelease(shaderReflection);
			dxcRelease(dxcReflectionBlob);

			if (_firstPass
			&&  unusedUniforms.size() > 0)
			{
				// first time through, we just find unused uniforms and get rid of them
				std::string output;
				bx::LineReader reader(_code.c_str() );
				while (!reader.isDone() )
				{
					bx::StringView strLine = reader.next();
					bool found = false;

					for (UniformNameList::iterator it = unusedUniforms.begin(), itEnd = unusedUniforms.end(); it != itEnd; ++it)
					{
						bx::StringView str = strFind(strLine, "uniform ");
						if (str.isEmpty() )
						{
							continue;
						}

						// matching lines like:  uniform u_name;
						// we want to replace "uniform" with "static" so that it's no longer
						// included in the uniform blob that the application must upload
						// we can't just remove them, because unused functions might still reference
						// them and cause a compile error when they're gone
						if (!bx::findIdentifierMatch(strLine, it->c_str() ).isEmpty() )
						{
							output.append(strLine.getPtr(), str.getPtr() );
							output += "static ";
							output.append(str.getTerm(), strLine.getTerm() );
							output += "\n";
							found = true;

							unusedUniforms.erase(it);
							break;
						}
					}

					if (!found)
					{
						output.append(strLine.getPtr(), strLine.getTerm() );
						output += "\n";
					}
				}

				// recompile with the unused uniforms converted to statics
				return compile(_dxc, _options, _version, output.c_str(), _shaderWriter, _messageWriter, false);
			}

			IDxcBlob* dxcShaderBlob = NULL;
			hr = dxcResult->GetOutput(DXC_OUT_OBJECT, IID_IDxcBlob, (void**)&dxcShaderBlob, NULL);
			if (NULL == dxcShaderBlob)
			{
				bx::write(_messageWriter, &messageErr, "Error: Unable to obtain shader object 0x%08x\n", (uint32_t)hr);
				return false;
			}

			{
				uint16_t count = (uint16_t)uniforms.size();
				bx::write(_shaderWriter, count, &err);

				uint32_t fragmentBit = _options.shaderType == 'f' ? kUniformFragmentBit : 0;
				for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
				{
					const Uniform& un = *it;

					const uint8_t nameSize = (uint8_t)un.name.size();
					bx::write(_shaderWriter, nameSize, &err);
					bx::write(_shaderWriter, un.name.c_str(), nameSize, &err);

					const uint8_t type = uint8_t(un.type | fragmentBit);
					bx::write(_shaderWriter, type, &err);
					bx::write(_shaderWriter, un.num, &err);
					bx::write(_shaderWriter, un.regIndex, &err);
					bx::write(_shaderWriter, un.regCount, &err);
					bx::write(_shaderWriter, un.texComponent, &err);
					bx::write(_shaderWriter, un.texDimension, &err);
					bx::write(_shaderWriter, un.texFormat, &err);

					BX_TRACE("%s, %s, %d, %d, %d"
						, un.name.c_str()
						, getUniformTypeName(UniformType::Enum(un.type & ~kUniformMask))
						, un.num
						, un.regIndex
						, un.regCount
						);
				}

				const uint32_t shaderSize = uint32_t(dxcShaderBlob->GetBufferSize() );
				bx::write(_shaderWriter, shaderSize, &err);
				bx::write(_shaderWriter, dxcShaderBlob->GetBufferPointer(), shaderSize, &err);
				bx::write(_shaderWriter, uint8_t(0), &err);

				bx::write(_shaderWriter, numAttrs, &err);
				bx::write(_shaderWriter, attrs, numAttrs*sizeof(uint16_t), &err);

				bx::write(_shaderWriter, size, &err);
			}

			if (_options.disasm)
			{
				const DxcBuffer shader =
				{
					.Ptr      = dxcShaderBlob->GetBufferPointer(),
					.Size     = dxcShaderBlob->GetBufferSize(),
					.Encoding = DXC_CP_ACP,
				};

				IDxcResult* dxcDisassembleResult = NULL;
				hr = _dxc.compiler3->Disassemble(&shader, IID_IDxcResult, (void**)&dxcDisassembleResult);
				if (NULL == dxcDisassembleResult)
				{
					bx::write(_messageWriter, &messageErr, "Error: Unable to disassemble shader 0x%08x\n", (uint32_t)hr);
					return false;
				}

				IDxcBlobUtf8* dxcShaderDisassembleBlob = NULL;
				hr = dxcDisassembleResult->GetOutput(DXC_OUT_DISASSEMBLY, IID_IDxcBlobUtf8, (void**)&dxcShaderDisassembleBlob, NULL);
				if (NULL == dxcShaderDisassembleBlob)
				{
					bx::write(_messageWriter, &messageErr, "Error: GetOutput DXC_OUT_DISASSEMBLY 0x%08x\n", (uint32_t)hr);
					return false;
				}

				std::string disasmfp = _options.outputFilePath + ".disasm";

				writeFile(disasmfp.c_str(), dxcShaderDisassembleBlob->GetBufferPointer(), (uint32_t)dxcShaderDisassembleBlob->GetBufferSize() );

				dxcRelease(dxcShaderDisassembleBlob);
				dxcRelease(dxcDisassembleResult);
			}

			dxcRelease(dxcShaderBlob);
			dxcRelease(dxcResult);
		}

		return SUCCEEDED(hr);
	}

} // namespace hlsl

	bool compileDxilShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _shaderWriter, bx::WriterI* _messageWriter)
	{
		using namespace dxil;

		Dxc dxc = load();

		if (NULL == dxc.dll)
		{
			bx::write(_messageWriter, bx::ErrorIgnore{}, "Error: Unable to load DXC compiler.\n");
			return false;
		}

		const bool result = dxil::compile(dxc, _options, _version, _code, _shaderWriter, _messageWriter, true);

		unload(dxc);

		return result;
	}

} // namespace bgfx

#else // SHADERC_CONFIG_HAS_DXC

namespace bgfx
{
	bool compileDxilShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _shaderWriter, bx::WriterI* _messageWriter)
	{
		BX_UNUSED(_options, _version, _code, _shaderWriter);
		bx::Error messageErr;
		bx::write(_messageWriter, &messageErr, "DXIL compiler is not compiled in or not supported on this platform.\n");
		return false;
	}

} // namespace bgfx

#endif // SHADERC_CONFIG_HAS_DXC

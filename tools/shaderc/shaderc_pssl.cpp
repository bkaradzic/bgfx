/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../../../bgfx/tools/shaderc/shaderc.h"

#if defined(BGFX_GNM)
#include <bx/os.h>
#include <bx/string.h>
#include <bx/process.h>
#include <bx/sort.h>

#define SCE_SHADER_BINARY_INTERNAL_STATIC_EXPORT
#include <shader/binary.h>
#include <shader/wave_psslc.h>

#include <unordered_set>
#include <map>
#include <atomic>
#endif



/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "shaderc.h"

#if defined(BGFX_GNM)
#include <gnm/constants.h>
#include <gnm/shader.h>
#include <shader/wave_psslc.h>
#include <shader/binary.h>
#include <gnmx/shaderbinary.h>
#include <gnmx/shader_parser.h>
#include <shader/pssl_types.h>
#endif

namespace bgfx {
	namespace pssl
	{

#if defined(BGFX_GNM)

		static const char* s_preamble = ""
			"#define bool                             uint\n"
			"#define SV_TARGET                        S_TARGET_OUTPUT\n"
			"#define SV_TARGET0                       S_TARGET_OUTPUT0\n"
			"#define SV_TARGET1                       S_TARGET_OUTPUT1\n"
			"#define SV_TARGET2                       S_TARGET_OUTPUT2\n"
			"#define SV_TARGET3                       S_TARGET_OUTPUT3\n"
			"#define SV_TARGET4                       S_TARGET_OUTPUT4\n"
			"#define SV_TARGET5                       S_TARGET_OUTPUT5\n"
			"#define SV_TARGET6                       S_TARGET_OUTPUT6\n"
			"#define SV_TARGET7                       S_TARGET_OUTPUT7\n"
			"#define POSITION                         S_POSITION\n"
			"#define SV_POSITION                      S_POSITION\n"
			"#define SV_DEPTH                         S_DEPTH_OUTPUT\n"
			"#define SV_DEPTHGREATEREQUAL             S_DEPTH_GE_OUTPUT\n"
			"#define SV_DEPTHLESSEQUAL                S_DEPTH_LE_OUTPUT\n"
			"#define SV_VertexID                      S_VERTEX_ID\n"
			"#define SV_VERTEXID                      S_VERTEX_ID\n"
			"#define SV_INSTANCEID                    S_INSTANCE_ID\n"
			"#define SV_PRIMITIVEID                   S_PRIMITIVE_ID\n"
			"#define SV_SAMPLEINDEX                   S_SAMPLE_INDEX\n"
			"#define shared\n"
			"#define groupshared                      thread_group_memory\n"
			"#define nointerpolation                  nointerp\n"
			"#define noperspective                    nopersp\n"
			"#define SV_TessFactor                    S_EDGE_TESS_FACTOR\n"
			"#define SV_InsideTessFactor              S_INSIDE_TESS_FACTOR\n"
			"#define SV_OutputControlPointID          S_OUTPUT_CONTROL_POINT_ID\n"
			"#define SV_DomainLocation                S_DOMAIN_LOCATION\n"
			"#define SV_IsFrontFace                   S_FRONT_FACE\n"
			"#define SV_Coverage                      S_COVERAGE\n"
			"#define SV_ClipDistance                  S_CLIP_DISTANCE\n"
			"#define SV_CullDistance                  S_CULL_DISTANCE\n"
			"#define SV_RenderTargetArrayIndex        S_RENDER_TARGET_INDEX\n"
			"#define SV_ViewportArrayIndex            S_VIEWPORT_INDEX\n"
			"#define SV_DispatchThreadID              S_DISPATCH_THREAD_ID\n"
			"#define SV_GroupID                       S_GROUP_ID\n"
			"#define SV_GroupIndex                    S_GROUP_INDEX\n"
			"#define SV_GroupThreadID                 S_GROUP_THREAD_ID\n"
			"#define Buffer                           DataBuffer\n"
			"#define RWBuffer                         RW_DataBuffer\n"
			"#define ByteAddressBuffer                ByteBuffer\n"
			"#define RWByteAddressBuffer              RW_ByteBuffer\n"
			"#define StructuredBuffer                 RegularBuffer\n"
			"#define RWStructuredBuffer               RW_RegularBuffer\n"
			"#define AppendStructuredBuffer           AppendRegularBuffer\n"
			"#define ConsumeStructuredBuffer          ConsumeRegularBuffer\n"
			"#define RWTexture1D                      RW_Texture1D\n"
			"#define RWTexture1DArray                 RW_Texture1D_Array\n"
			"#define RWTexture2D                      RW_Texture2D\n"
			"#define RWTexture2DArray                 RW_Texture2D_Array\n"
			"#define RWTexture3D                      RW_Texture3D\n"
			"#define RWTextureCube                    RW_TextureCube\n"
			"#define RWTextureCubeArray               RW_TextureCube_Array\n"
			"#define Texture1DArray                   Texture1D_Array\n"
			"#define Texture2DArray                   Texture2D_Array\n"
			"#define TextureCubeArray                 TextureCube_Array\n"
			"#define Texture2DMS                      MS_Texture2D\n"
			"#define Texture2DMSArray                 MS_Texture2D_Array\n"
			"#define mips                             MipMaps\n"
			"#define IncrementCounter                 IncrementCount\n"
			"#define DecrementCounter                 DecrementCount\n"
			"#define SampleCmpLevelZero               SampleCmpLOD0\n"
			"#define SampleLevel                      SampleLOD\n"
			"#define SampleGrad                       SampleGradient\n"
			"#define CalculateLevelOfDetail           GetLOD\n"
			"#define CalculateLevelOfDetailUnclamped  GetLODUnclamped\n"
			"#define GetSamplePosition                GetSamplePoint\n"
			"#define cbuffer                          ConstantBuffer\n"
			"#define tbuffer                          TextureBuffer\n"
			"#define domain                           DOMAIN_PATCH_TYPE\n"
			"#define maxtessfactor                    MAX_TESS_FACTOR\n"
			"#define outputcontrolpoints              OUTPUT_CONTROL_POINTS\n"
			"#define outputtopology                   OUTPUT_TOPOLOGY_TYPE\n"
			"#define partitioning                     PARTITIONING_TYPE\n"
			"#define patchconstantfunc                PATCH_CONSTANT_FUNC\n"
			"#define instance                         INSTANCE\n"
			"#define numthreads                       NUM_THREADS\n"
			"#define patchsize                        PATCH_SIZE\n"
			"#define maxvertexcount                   MAX_VERTEX_COUNT\n"
			"#define earlydepthstencil                FORCE_EARLY_DEPTH_STENCIL\n"
			"#define GroupMemoryBarrier               ThreadGroupMemoryBarrier\n"
			"#define GroupMemoryBarrierWithGroupSync  ThreadGroupMemoryBarrierSync\n"
			"#define DeviceMemoryBarrier              SharedMemoryBarrier\n"
			"#define DeviceMemoryBarrierWithGroupSync SharedMemoryBarrierSync\n"
			"#define AllMemoryBarrier                 MemoryBarrier\n"
			"#define AllMemoryBarrierWithGroupSync    MemoryBarrierSync\n"
			"#define InterlockedAdd                   AtomicAdd\n"
			"#define InterlockedAnd                   AtomicAnd\n"
			"#define InterlockedCompareExchange       AtomicCmpExchange\n"
			"#define InterlockedCompareStore          AtomicCmpStore\n"
			"#define InterlockedExchange              AtomicExchange\n"
			"#define InterlockedMax                   AtomicMax\n"
			"#define InterlockedMin                   AtomicMin\n"
			"#define InterlockedOr                    AtomicOr\n"
			"#define InterlockedXor                   AtomicXor\n"
			"#define firstbithigh                     FirstSetBit_Hi\n"
			"#define firstbitlow                      FirstSetBit_Lo\n"
			"#define reversebits                      ReverseBits\n"
			"#define countbits                        CountSetBits\n"
			"#define EvaluateAttributeAtCentroid      EvaluateAttributeCentroid\n"
			"#define GetRenderTargetSampleCount       sampleCount\n"
			"#define GetRenderTargetSamplePosition    samplePosition\n"
			;


		// BBI-TODO (dgalloway 3) make this path something reasonable like in the user documents folder and maybe with an override
		static const std::string sGnmGpuDebuggerPath = "D:\\temp\\GnmGPUDebuggerPath\\";

		static void printShaderDiagnostics(const Options& _options, const sce::Shader::Wave::Psslc::DiagnosticMessage* diags, int diagCount)
		{
			const sce::Shader::Wave::Psslc::SourceLocation* srcLoc = nullptr;

			const char* srcFile = "n/a";
			uint32_t srcLine = 0;
			uint32_t srcColumn = 0;

			for (int ii = 0; ii < diagCount; ++ii)
			{
				srcLoc = diags[ii].location;

				if (srcLoc != nullptr)
				{
					srcFile = srcLoc->file->fileName;
					srcLine = srcLoc->lineNumber;
					srcColumn = srcLoc->columnNumber;
				}

				std::string diagnostic =
					"\n================ [Shader Diagnostic] ================"
					"\nCode: " + std::to_string(diags[ii].code) +
					"\nLevel: " + std::to_string(diags[ii].level) +
					"\nMessage: " + diags[ii].message +
					"\nLocation: " + srcFile + " @ Ln " + std::to_string(srcLine) + ", Col " + std::to_string(srcColumn);

				fprintf(stderr, diagnostic.c_str());
			}
		}

		static bool writeUniforms(const Options& _options, bx::WriterI* _writer, const sce::Shader::Binary::Program& program, uint16_t& constantBufferSize)
		{

			bool isFragment = (_options.shaderType == 'f');
			uint32_t fragmentBit = isFragment ? kUniformFragmentBit : 0;

			struct UniformMapping
			{
				bgfx::UniformType::Enum mType;
				uint16_t mSize;
				uint16_t mRegCount;
			};

			static const std::map<sce::Shader::Binary::PsslType, UniformMapping> psslUniformToBgfx =
			{
				{sce::Shader::Binary::PsslType::kTypeFloat4,   {bgfx::UniformType::Enum::Vec4, sizeof(float) * 4, 1}},
				{sce::Shader::Binary::PsslType::kTypeFloat3x3, {bgfx::UniformType::Enum::Mat3, sizeof(float) * 4 * 3, 3}},
				{sce::Shader::Binary::PsslType::kTypeFloat4x4, {bgfx::UniformType::Enum::Mat4, sizeof(float) * 4 * 4, 4}},
			};

			uint16_t numUniforms = 0;
			uint32_t globalBufIdx = UINT32_MAX;

			// find the global constant buffer
			if ((program.m_elements != nullptr) && (program.m_numElements > 0) && program.m_numBuffers > 0)
			{
				uint32_t idx;

				for (idx = 0; idx < program.m_numBuffers; ++idx)
				{
					const sce::Shader::Binary::Buffer& buffer = program.m_buffers[idx];
					const char* bufferName = program.m_buffers[idx].getName();
					if (0 == bx::strCmp("__GLOBAL_CB__", bufferName))
					{
						globalBufIdx = idx;
						break;
					}
				}
			}

			uint32_t startPosition = 0;
			uint32_t numConstantBufferUniforms = 0;
			if (globalBufIdx != UINT32_MAX)
			{
				startPosition = program.m_buffers[globalBufIdx].m_elementOffset;
				numConstantBufferUniforms = program.m_buffers[globalBufIdx].m_numElements;
			}

			numUniforms = numConstantBufferUniforms + program.m_numSamplerStates;

			BX_TRACE("-----------------------------------------------------------------------");
			BX_TRACE("Writing uniforms");

			bx::write(_writer, numUniforms);
			BX_TRACE("count: %d", numUniforms);

			if (numUniforms == 0)
			{
				return true;
			}

			// check if we have any constant buffer values to output
			if (0 < numConstantBufferUniforms)
			{
				for (uint32_t ii = startPosition; ii < (startPosition + numConstantBufferUniforms); ++ii)
				{
					const sce::Shader::Binary::Element& elem = program.m_elements[ii];
					if (elem.m_isUsed)
					{
						Uniform un = {};
						un.name.assign(elem.getName());
						un.regIndex = elem.m_byteOffset;

						uint16_t entrySize = 0;
						bool valid = false;

						{
							auto mapping = psslUniformToBgfx.find(static_cast<sce::Shader::Binary::PsslType>(elem.m_type));
							if (!(mapping == psslUniformToBgfx.end()))
							{
								un.type = mapping->second.mType;
								un.num = elem.m_arraySize > 0 ? elem.m_arraySize : 1;
								un.regCount = mapping->second.mRegCount * un.num;  // regCount should be multiplied by number - corresponding change in renderer_gnm.cpp
								entrySize += mapping->second.mSize * un.num;
								valid = true;
							}
							else
							{
								// BBI TODO
								// printError has a side effect of exiting the compilation!!
								fprintf (stderr, ("Unknown uniform type for " + un.name + ". Type is " + std::to_string(un.type)).c_str());
							}
						}

						if (valid)
						{
							constantBufferSize = std::max(constantBufferSize, static_cast<uint16_t>(elem.m_byteOffset + entrySize));

							const uint8_t nameSize = static_cast<uint8_t>(un.name.size());
							bx::write(_writer, nameSize);
							BX_TRACE("nameSize: %d", nameSize);
							bx::write(_writer, un.name.c_str(), nameSize);
							BX_TRACE("name: %s", un.name.c_str());
							uint8_t type = uint8_t(un.type | kUniformFragmentBit);
							bx::write(_writer, type);
							BX_TRACE("type: %d", type);
							bx::write(_writer, un.num);
							BX_TRACE("num: %d", un.num);
							bx::write(_writer, un.regIndex);
							BX_TRACE("regIndex: %d", un.regIndex);
							bx::write(_writer, un.regCount);
							BX_TRACE("regCount: %d", un.regCount);
						}
					}
					else
					{
						continue;
					}
				}
			}


			// loop over buffers to emit the texture uniforms
			for (uint32_t idx = 0; idx < program.m_numSamplerStates; ++idx)
			{
				const sce::Shader::Binary::SamplerState& samplerState = program.m_samplerStates[idx];

				Uniform un = {};
				uint16_t entrySize = 0;
				bool valid = false;

				// Remove 'sampler' suffix to adhere to same convention as DX
				// Not sure this is truly necessary
				std::string bufferName(samplerState.getName());
				std::string s = "Sampler";
				std::string::size_type i = bufferName.rfind(s);
				if (i != std::string::npos)
					bufferName.erase(i, s.length());

				un.name.assign(bufferName);
				un.regIndex = samplerState.m_resourceIndex;
				un.type = UniformType::Enum(fragmentBit | kUniformSamplerBit | bgfx::UniformType::Sampler);
				un.num = 1;
				un.regCount = 1; // uint16_t(bindDesc.BindCount);
				entrySize = 16; // still uses full register of 4 floats
				valid = true;

				if (valid)
				{
					constantBufferSize = std::max(constantBufferSize, static_cast<uint16_t>(entrySize));
					const uint8_t nameSize = static_cast<uint8_t>(un.name.size());
					bx::write(_writer, nameSize);
					BX_TRACE("nameSize: %d", nameSize);
					bx::write(_writer, un.name.c_str(), nameSize);
					BX_TRACE("name: %s", un.name.c_str());
					uint8_t type = uint8_t(un.type | fragmentBit);
					bx::write(_writer, type);
					BX_TRACE("type: %d", type);
					bx::write(_writer, un.num);
					BX_TRACE("num: %d", un.num);
					bx::write(_writer, un.regIndex);
					BX_TRACE("regIndex: %d", un.regIndex);
					bx::write(_writer, un.regCount);
					BX_TRACE("regCount: %d", un.regCount);
				}

			}

			return true;
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

		static const RemapInputSemantic& findInputSemantic(const char* _name, uint8_t _index)
		{
			for (uint32_t ii = 0; ii < bgfx::Attrib::Count; ++ii)
			{
				const RemapInputSemantic& ris = s_remapInputSemantic[ii];
				if (0 == bx::strCmp(ris.m_name, _name)
					&& ris.m_index == _index)
				{
					return ris;
				}
			}

			return s_remapInputSemantic[bgfx::Attrib::Count];
		}

		static bool writeAttributes(const Options& _options, bx::WriterI* _writer, const sce::Shader::Binary::Program& program)
		{
			const uint32_t numInputAttribs = program.m_numInputAttributes;
			uint8_t attributesCount = 0;  // This HAS to be uint_8_t since it's being written below in bx::write and the reader expects a 8 bit value

			// Only need to write out attributes for vertex shader
			if (_options.shaderType == 'v')
			{
				for (uint32_t ii = 0; ii < numInputAttribs; ++ii)
				{
					const sce::Shader::Binary::Attribute* attrib = program.m_inputAttributes + ii;
					const char* semanticName = attrib->getSemanticName();
					if ( bx::strFind(semanticName, "S_").getPtr() == semanticName)
					{
						continue;
					}
					attributesCount++;
				}
			}

			BX_TRACE("-----------------------------------------------------------------------");
			BX_TRACE("Writing attributes");

			bx::write(_writer, attributesCount);
			BX_TRACE("numAttrs: %d", attributesCount);

			if (attributesCount > 0)
			{
				for (uint32_t ii = 0; ii < numInputAttribs; ++ii)
				{
					const sce::Shader::Binary::Attribute* attrib = program.m_inputAttributes + ii;
					const char* semanticName = attrib->getSemanticName();

					if (bx::strFind(semanticName, "S_").getPtr() == semanticName)
					{
						continue;
					}
					const RemapInputSemantic ris = findInputSemantic(attrib->getSemanticName(), attrib->m_semanticIndex);

					uint8_t slotPlusInstanceFlag = attrib->m_resourceIndex;
					constexpr uint8_t IS_INSTANCE_FLAG = 128;
					const char* attribName = attrib->getName();

					// if semantic names start with i_ this indicates instancing on PS4
					if ((attribName[0] == 'i') && (attribName[1] == '_')) {
						slotPlusInstanceFlag |= IS_INSTANCE_FLAG;
					}

					bx::write(_writer, slotPlusInstanceFlag);

					if (ris.m_attr != bgfx::Attrib::Count)
					{
						const uint16_t attribId = bgfx::attribToId(ris.m_attr);
						bx::write(_writer, attribId);
						BX_TRACE("attr: %d : %d : %s", attribId, slotPlusInstanceFlag, attribName);
					}
					else
					{
						constexpr uint16_t attribId = UINT16_MAX;
						bx::write(_writer, attribId);
						BX_TRACE("attr: %d", attribId);
						fprintf(stderr, "Error: Unknown vertex input attribute.\n");
						return false;
					}
				}
			}

			BX_TRACE("-----------------------------------------------------------------------");

			return true;
		}

		sce::Shader::Wave::Psslc::SourceFile* loadShaderSource(const char* fileName, const sce::Shader::Wave::Psslc::SourceLocation* includedFrom, const sce::Shader::Wave::Psslc::OptionsBase* compileOptions, void* userData, const char** errorString)
		{
			BX_UNUSED(fileName, includedFrom, compileOptions, errorString);
			return static_cast<sce::Shader::Wave::Psslc::SourceFile*>(userData);
		}

		static bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
		{
			std::string variant = "";

			bool debug = _options.debugInformation;

			if (_options.emitShaderSource)
			{
				const char* profile = _options.profile.c_str();
				std::string file;

				for (auto& item : _options.defines)
				{
					std::string temp = item;
					const std::string flag = "FLAG_";
					if (temp.rfind("FLAG_", 0) == 0)
					{
						temp.erase(0, flag.length());
						std::string s = "=1";
						std::string::size_type fl = temp.rfind(s);
						if (fl != std::string::npos)
							temp.erase(fl, s.length());

						s = "_";
						fl = temp.rfind(s);
						if (fl != std::string::npos)
							temp.erase(fl, s.length());

						variant += temp + "__";
					}
				}

				variant = _options.inputFilePath + "__" + variant;

				//file = ".\\pssl\\" + file + variant + ".pssl";
				file = file + variant + ".pssl";

				writeFile(file.c_str(), _code.c_str(), (int32_t)_code.size());
			}

			sce::Shader::Wave::Psslc::Options compileOptions;
			sce::Shader::Wave::Psslc::initializeOptions(&compileOptions, SCE_WAVE_API_VERSION);

			switch (_options.shaderType)
			{
			case 'v': compileOptions.targetProfile = sce::Shader::Wave::Psslc::TargetProfile::kTargetProfileVsVs;
				break;
			case 'f': compileOptions.targetProfile = sce::Shader::Wave::Psslc::TargetProfile::kTargetProfilePs;
				break;
			case 'c': compileOptions.targetProfile = sce::Shader::Wave::Psslc::TargetProfile::kTargetProfileCs;
				break;
			default:
				fprintf(stderr, "Error: Unsupported shader type.\n");
				return false;
			}

			BX_TRACE("***********************************************************************");
			BX_TRACE("Saving shader: %s PSSL", variant.c_str());

			// Format shader macros as C-string array
			std::vector<const char*> macroDefinitions{};
			macroDefinitions.reserve(_options.defines.size());

			for (const auto& define : _options.defines)
			{
				macroDefinitions.push_back(define.c_str());
			}

			compileOptions.macroDefinitions = macroDefinitions.data();
			compileOptions.macroDefinitionCount = static_cast<uint32_t>(macroDefinitions.size());

			compileOptions.mainSourceFile = _options.inputFilePath.c_str();
			compileOptions.entryFunctionName = "main";
			if (debug) {
				compileOptions.sdbCache = 1;
			}

			static const uint32_t suppressedWarnings[] =
			{
				6923,  // implicit type narrowing
				20087, // unreferenced formal parameter
				20088  // unreferenced local variable
			};

			compileOptions.suppressedWarnings = suppressedWarnings;
			compileOptions.suppressedWarningsCount = sizeof(suppressedWarnings);

			// Set all callbacks to trivial placeholders, except for CallbackOpenFile
			sce::Shader::Wave::Psslc::CallbackList callbackList;
			sce::Shader::Wave::Psslc::initializeCallbackList(&callbackList, sce::Shader::Wave::Psslc::kCallbackDefaultsTrivial);
			callbackList.openFile = &loadShaderSource;

			// The above openFile callback will return this dummy file
			sce::Shader::Wave::Psslc::SourceFile srcFile;
			srcFile.fileName = _options.inputFilePath.c_str();
			srcFile.text = _code.data();
			srcFile.size = static_cast<uint32_t>(_code.size());

			if (debug)
			{
				compileOptions.optimizeForDebug = 1;
				compileOptions.optimizationLevel = 0;
				compileOptions.useFastmath = 0;
			}
			else
			{
				if (_options.optimize) {
					compileOptions.optimizationLevel = 4;
				}
			}

			// Now tell the compiler to load our dummy file when it runs
			compileOptions.userData = static_cast<void*>(&srcFile);

			const sce::Shader::Wave::Psslc::Output* compileOutput = sce::Shader::Wave::Psslc::run(&compileOptions, &callbackList);

			if (compileOutput)
			{
				if (compileOutput->programData != nullptr && compileOutput->programSize != 0)
				{
					sce::Shader::Binary::Program program = {};
					sce::Shader::Binary::PsslStatus result = program.loadFromMemory(compileOutput->programData, compileOutput->programSize);

					if (result != sce::Shader::Binary::PsslStatus::kStatusOk)
					{
						fprintf( stderr, "Failed to load shader binary program from source blob!");
						return false;
					}

					uint16_t constantBufferSize = 0;
					if (!writeUniforms(_options, _writer, program, constantBufferSize))
					{
						fprintf(stderr, "Failed to write uniforms for shader binary program!");
						return false;
					}

					bx::write(_writer, compileOutput->programSize);
					BX_TRACE("size: %d", compileOutput->programSize);
					bx::write(_writer, compileOutput->programData, compileOutput->programSize);
					BX_TRACE("code:");
					uint8_t nul = 0;
					bx::write(_writer, nul);
					BX_TRACE("nul:");

					if (!writeAttributes(_options, _writer, program))
					{
						fprintf(stderr, "Failed to write attributes for shader binary program!");
						return false;
					}

					bx::write(_writer, constantBufferSize);
					BX_TRACE("constant buffer size: %d", constantBufferSize);
					BX_TRACE("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");


					// Write SDB files for GPU Debugger (BBI-TODO)
					//if (compileOutput->sdbDataSize > 0 && debug) {

					//	static std::atomic<int> sFileUniqueCounter = 0;

					//	std::string outputSDBFile = sGnmGpuDebuggerPath + std::string(_options.inputFilePath.c_str()) + std::string("_") + std::to_string(sFileUniqueCounter++) + std::string("_") + _options.shaderType + std::string(compileOutput->sdbExt);

					//	FILE* glslcOutputFileHandle = nullptr;

					//	if (fopen_s(&glslcOutputFileHandle, outputSDBFile.c_str(), "wb") != 0)
					//	{
					//		BX_ASSERT(false, "Failed to open file %s", outputSDBFile.c_str());
					//	}
					//	if (!glslcOutputFileHandle)
					//	{
					//		BX_ASSERT(false, "Can't write file %s", outputSDBFile.c_str());
					//	}

					//	fwrite(compileOutput->sdbData, compileOutput->sdbDataSize, 1, glslcOutputFileHandle);
					//	fclose(glslcOutputFileHandle);
					//}

					sce::Shader::Wave::Psslc::destroyOutput(compileOutput);
				}
				else
				{
					BX_TRACE("Compile failed");
					if (compileOutput->diagnosticCount > 0)
					{
						printShaderDiagnostics(_options, compileOutput->diagnostics, compileOutput->diagnosticCount);
					}
					fprintf(stderr, "Error: Failed to compile shader.\n");
					return false;
				}
			}
			else
			{
				fprintf(stderr, "Error: Internal psslc error. Failed to compile shader.\n");
				return false;
			}

			return true;
		}
#endif // BGFX_GNM
	} // namespace pssl

	bool compilePSSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
#if defined(BGFX_GNM)
		return pssl::compile(_options, _version, _code, _writer);
#else
		BX_UNUSED(_options, _version, _code, _writer);
		_options.printError("PSSL not supported for this platform");
		return CompileResult{ false };
#endif
	}

	const char* getPsslPreamble()
	{
#if defined(BGFX_GNM)

		return pssl::s_preamble;
#else
		return "";
#endif

	}

} // namespace bgfx

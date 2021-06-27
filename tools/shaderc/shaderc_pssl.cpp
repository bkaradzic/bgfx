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

		// "??0Program@Binary@Shader@sce@@QEAA@XZ"
		// "??1Program@Binary@Shader@sce@@QEAA@XZ"
		// "?calculateSize@Program@Binary@Shader@sce@@QEAAIXZ"
		// "?calculateSize@Program@Binary@Shader@sce@@QEBAIXZ"
		// "?getBufferResourceByName@Program@Binary@Shader@sce@@QEBAPEAVBuffer@234@PEBD@Z"
		// "?getConstantByName@Program@Binary@Shader@sce@@QEBAPEAVConstant@234@PEBD@Z"
		// "?getInputAttributeById@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@E@Z"
		// "?getInputAttributeBySemantic@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@W4PsslSemantic@234@@Z"
		// "?getInputAttributeBySemanticNameAndIndex@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@PEBDE@Z"
		// "?getOutputAttributeById@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@E@Z"
		// "?getOutputAttributeBySemantic@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@W4PsslSemantic@234@@Z"
		// "?getOutputAttributeBySemanticNameAndIndex@Program@Binary@Shader@sce@@QEBAPEAVAttribute@234@PEBDE@Z"
		// "?getSamplerStateByName@Program@Binary@Shader@sce@@QEBAPEAVSamplerState@234@PEBD@Z"
		// "?loadFromMemory@Program@Binary@Shader@sce@@QEAA?AW4PsslStatus@234@PEBXI@Z"
		// "?parseGsShader@Binary@Shader@sce@@YAXPEAVShaderInfo@123@0PEBX@Z"
		// "?parseShader@Binary@Shader@sce@@YAXPEAVShaderInfo@123@PEBXW4ShaderType@Gnmx@3@@Z"
		// "?saveToMemory@Program@Binary@Shader@sce@@QEAA?AW4PsslStatus@234@PEAXI@Z"
		// "?saveToMemory@Program@Binary@Shader@sce@@QEBA?AW4PsslStatus@234@PEAXI@Z"

		typedef sce::Shader::Binary::PsslStatus(*LoadFromMemoryFn)(sce::Shader::Binary::Program* _this, const void* shaderBinary, uint32_t shaderBinarySize);

		struct RemapInputSemantic
		{
			bgfx::Attrib::Enum m_attr;
			const char* m_name;
			uint8_t m_index;
		};

		static const RemapInputSemantic s_remapInputSemantic[] =
		{
			{ bgfx::Attrib::Position,  "S_POSITION",   0 },
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
		BX_STATIC_ASSERT(BX_COUNTOF(s_remapInputSemantic) == bgfx::Attrib::Count + 1);

		const RemapInputSemantic& findInputSemantic(const char* _name, uint8_t _index)
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

		struct UniformRemap
		{
			UniformType::Enum id;
			sce::Shader::Binary::PsslType type;
		};

		static const UniformRemap s_uniformRemap[] =
		{
			{ UniformType::Sampler, sce::Shader::Binary::PsslType::kTypeInt1     },
			{ UniformType::Vec4, sce::Shader::Binary::PsslType::kTypeFloat4   },
			{ UniformType::Mat3, sce::Shader::Binary::PsslType::kTypeFloat3x3 },
			{ UniformType::Mat4, sce::Shader::Binary::PsslType::kTypeFloat4x4 },
			{ UniformType::Sampler, sce::Shader::Binary::PsslType::kTypeInt1     },
			{ UniformType::Sampler, sce::Shader::Binary::PsslType::kTypeInt1     },
			{ UniformType::Sampler, sce::Shader::Binary::PsslType::kTypeInt1     },
			{ UniformType::Sampler, sce::Shader::Binary::PsslType::kTypeInt1     },
		};

		UniformType::Enum findUniformType(sce::Shader::Binary::PsslType _type)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_uniformRemap); ++ii)
			{
				const UniformRemap& remap = s_uniformRemap[ii];

				if (remap.type == _type)
				{
					return remap.id;
				}
			}

			return UniformType::Count;
		}

		static const char* toString(sce::Shader::Binary::PsslType _psslType)
		{
			switch (_psslType)
			{
			case sce::Shader::Binary::kTypeInt1:   return "int1";
			case sce::Shader::Binary::kTypeInt2:   return "int2";
			case sce::Shader::Binary::kTypeInt3:   return "int3";
			case sce::Shader::Binary::kTypeInt4:   return "int4";
			case sce::Shader::Binary::kTypeUint1:  return "uint1";
			case sce::Shader::Binary::kTypeUint2:  return "uint2";
			case sce::Shader::Binary::kTypeUint3:  return "uint3";
			case sce::Shader::Binary::kTypeUint4:  return "uint4";
			case sce::Shader::Binary::kTypeFloat1: return "float1";
			case sce::Shader::Binary::kTypeFloat2: return "float2";
			case sce::Shader::Binary::kTypeFloat3: return "float3";
			case sce::Shader::Binary::kTypeFloat4:
			default: break;
			};

			return "float4";
		}

		struct Srt
		{
			std::string name;
			uint32_t idx;
		};

		typedef std::vector<Srt> SrtArray;

		typedef std::vector<bx::StringView> StringViewArray;

		StringViewArray split(const bx::StringView& _str, char _seperator)
		{
			StringViewArray result;

			const char* prev = _str.getPtr();
			bx::StringView curr(_str);

			for (curr = bx::strFind(bx::StringView(curr.getPtr(), _str.getTerm()), _seperator)
				; !curr.isEmpty()
				; prev = curr.getPtr() + 1, curr = bx::strFind(bx::StringView(prev, _str.getTerm()), _seperator)
				)
			{
				bx::StringView sv(prev, curr.getPtr());
				result.push_back(sv);
			}

			bx::StringView sv(prev, _str.getTerm());

			if (!sv.isEmpty())
			{
				result.push_back(sv);
			}

			return result;
		}

		bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass, const SrtArray& _srts)
		{
			char sceOrbisSdkDir[bx::kMaxFilePath];
			char tempDir[bx::kMaxFilePath];
			{
				uint32_t len = sizeof(sceOrbisSdkDir);
				if (!bx::getEnv(sceOrbisSdkDir, &len, "SCE_ORBIS_SDK_DIR"))
				{
					fprintf(stderr, "Error: SCE_ORBIS_SDK_DIR environment variable not set.");
					return false;
				}

				bx::FilePath temp(bx::Dir::Temp);
				bx::strCopy(tempDir, BX_COUNTOF(tempDir), temp);
			}

			std::string dll(sceOrbisSdkDir);
			dll += "\\host_tools\\bin\\libSceShaderBinary.dll";
			void* sceShaderBinaryDll = bx::dlopen(dll.c_str());
			if (NULL == sceShaderBinaryDll)
			{
				fprintf(stderr, "Error: PSSL compiler is not supported.\n");
				return false;
			}

			LoadFromMemoryFn loadFromMemory = (LoadFromMemoryFn)bx::dlsym(sceShaderBinaryDll
				, "?loadFromMemory@Program@Binary@Shader@sce@@QEAA?AW4PsslStatus@234@PEBXI@Z"
			);

			std::string shader;
			//		shader += s_preamble;
			shader += _code;

			uint32_t hash = bx::hash<bx::HashMurmur2A>(shader.c_str(), uint32_t(shader.length()));
			char psslFilePath[bx::kMaxFilePath];
			bx::snprintf(psslFilePath, BX_COUNTOF(psslFilePath), "%s/tmp-%08x.pssl", tempDir, hash);

			char sbFilePath[bx::kMaxFilePath];
			bx::snprintf(sbFilePath, BX_COUNTOF(sbFilePath), "%s/tmp-%08x.sb", tempDir, hash);

			bx::FileWriter writer;
			bx::Error err;
			if (bx::open(&writer, psslFilePath, false, &err))
			{
				bx::write(&writer, shader.c_str(), uint32_t(shader.length()), &err);
				bx::close(&writer);
			}

			if (!err.isOk())
			{
				fprintf(stderr, "Error: failed to save temp file.\n");
				goto error;
			}

			{
				bx::ProcessReader pr;

				bx::FilePath exec(sceOrbisSdkDir);
				exec.join("host_tools/bin/orbis-wave-psslc.exe");

				// warning D20087: unreferenced formal parameter ''
				// warning D20088: unreferenced local variable ''
				std::string cmd = "-Wsuppress=20087,20088 ";

				{
					cmd += " -profile sce_";

					switch (_options.shaderType)
					{
					case 'c': cmd += "c";    break;
					case 'f': cmd += "p";    break;
					case 'v': cmd += "vs_v"; break;
					}

					cmd += "s_orbis";
				}

				cmd += " -o ";
				cmd += sbFilePath;
				cmd += " ";
				cmd += psslFilePath;

				if (bx::open(&pr, exec, cmd.c_str(), &err))
				{
					char out[1024];

					for (;;)
					{
						int32_t len = bx::read(&pr, out, sizeof(out) - 1, &err);
						if (!err.isOk())
						{
							break;
						}

						out[len] = '\0';
						fputs(out, stderr);
					}

					bx::close(&pr);

					if (!_options.keepIntermediate)
					{
						bx::remove(psslFilePath);
					}

					if (!err.isOk()
						&& err != bx::kErrorReaderWriterEof)
					{
						fprintf(stderr, "Error: PSSL process failed.\n");
						goto error;
					}

					if (0 != pr.getExitCode())
					{
						fprintf(stderr, "Error: PSSL exit 0x%08x.\n", pr.getExitCode());

						if (0xc0000005 == uint32_t(pr.getExitCode()))
						{
							fprintf(stderr
								, "\n"
								"If you're running inside ConEmu/Cmder, disable hooks temporary with:\n"
								"\n"
								"    set ConEmuHooks=OFF\n"
								"\n"
								"Reference(s):\n"
								" - https://conemu.github.io/en/ConEmuEnvironment.html#Disabling_hooks_temporarily\n"
								"\n"
							);
						}

						goto error;
					}
				}
				else
				{
					fprintf(stderr, "Error: PSSL process failed to open.\n");
					goto error;
				}

				{
					bx::FileReader reader;
					if (bx::open(&reader, sbFilePath))
					{
						uint32_t shaderSize = (uint32_t)bx::getSize(&reader);
						char* shaderData = new char[shaderSize];
						shaderSize = (uint32_t)bx::read(&reader, shaderData, shaderSize);
						bx::close(&reader);

						if (!_options.keepIntermediate)
						{
							bx::remove(sbFilePath);
						}

						sce::Shader::Binary::Program* sbp = (sce::Shader::Binary::Program*)alloca(sizeof(sce::Shader::Binary::Program));
						sce::Shader::Binary::PsslStatus status = loadFromMemory(sbp, shaderData, shaderSize);
						if (sce::Shader::Binary::PsslStatus::kStatusOk == status)
						{
							if (_firstPass)
							{
								for (uint32_t ii = 0, num = sbp->m_numElements; ii < num; ++ii)
								{
									const sce::Shader::Binary::Element& element = sbp->m_elements[ii];
									BX_TRACE("element %d: %s", ii, element.getName());
								}

								std::string samplersInit;
								std::unordered_set<std::string> samplers;

								// Sort resources by binding index.
								struct Remap
								{
									uint32_t idx;
									uint32_t resourceIndex;
								};

								Remap remap[128];

								for (uint32_t ii = 0, num = sbp->m_numSamplerStates; ii < num; ++ii)
								{
									const sce::Shader::Binary::SamplerState& ss = sbp->m_samplerStates[ii];
									remap[ii].idx = ii;
									remap[ii].resourceIndex = ss.m_resourceIndex;
								}

								bx::quickSort(remap, sbp->m_numSamplerStates, sizeof(Remap), [](const void* _lhs, const void* _rhs) {
									const Remap* lhs = (const Remap*)_lhs;
									const Remap* rhs = (const Remap*)_rhs;
									return int32_t(lhs->resourceIndex) - int32_t(rhs->resourceIndex);
								});

								for (uint32_t ii = 0, num = sbp->m_numSamplerStates, resourceIndex = 0; ii < num; ++ii)
								{
									const sce::Shader::Binary::SamplerState& ss = sbp->m_samplerStates[remap[ii].idx];

									for (; resourceIndex != ss.m_resourceIndex; ++resourceIndex)
									{
										std::string str;
										bx::stringPrintf(str, "unused%d", resourceIndex);

										samplersInit += "\tSamplerState " + str + ";\n";
									}

									const char* name = ss.getName();
									uint32_t len = (uint32_t)bx::strLen(name);
									if (0 == bx::strCmp(&name[len - 7], "Sampler"))
									{
										char str[1024];
										bx::strCopy(str, sizeof(str), name, len - 7);
										BX_TRACE("%2d: %s", ii, str);

										samplersInit += "\tSamplerState ";
										samplersInit += str;
										samplersInit += ";\n";

										samplers.insert(str);
									}
									else if (0 == bx::strCmp(&name[len - 10], "Comparison"))
									{
										char str[1024];
										bx::strCopy(str, sizeof(str), name, len - 17);
										BX_TRACE("%2d: %s", ii, str);

										samplersInit += "\tSamplerComparisonState ";
										samplersInit += str;
										samplersInit += ";\n";

										samplers.insert(str);
									}
									else
									{
										BX_TRACE("Unknown: %s", name);
									}

									++resourceIndex;
								}

								std::string input;

								if ('v' == _options.shaderType) // Only care about input semantic on vertex shaders
								{
									// Keep "unused" arguments - let the actual PSSL compiler strip them and the dead code that's
									// using them, instead of trying to define them as statics or strip dead code ourselves.
									//    Output main(float4 a_color0 : COLOR0 , float4 a_normal : NORMAL , float3 a_position : POSITION , float2 a_texcoord0 : TEXCOORD0) {
									// input:         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

									const char mainArgsStart[] = "Output main(";
									size_t pos = _code.find(mainArgsStart) + sizeof(mainArgsStart) - 1;
									size_t end = _code.find(')', pos);
									input = _code.substr(pos, end - pos);
								}

								std::string init;
								std::string textures;

								// Sort resources by binding index.
								for (uint32_t ii = 0, num = sbp->m_numBuffers; ii < num; ++ii)
								{
									const sce::Shader::Binary::Buffer& sbb = sbp->m_buffers[ii];
									remap[ii].idx = ii;
									remap[ii].resourceIndex = sbb.m_resourceIndex;
								}

								bx::quickSort(remap, sbp->m_numBuffers, sizeof(Remap), [](const void* _lhs, const void* _rhs) {
									const Remap* lhs = (const Remap*)_lhs;
									const Remap* rhs = (const Remap*)_rhs;
									return int32_t(lhs->resourceIndex) - int32_t(rhs->resourceIndex);
								});

								SrtArray srts;
								for (uint32_t ii = 0, num = sbp->m_numBuffers, resourceIndex = 0; ii < num; ++ii)
								{
									const sce::Shader::Binary::Buffer& sbb = sbp->m_buffers[remap[ii].idx];
									const char* name = sbb.getName();

									if (sce::Shader::Binary::PsslBufferType::kBufferTypeDataBuffer == sbb.m_langType
										|| sce::Shader::Binary::PsslBufferType::kBufferTypeRwDataBuffer == sbb.m_langType)
									{
										for (; resourceIndex != sbb.m_resourceIndex; ++resourceIndex)
										{
											std::string str;
											bx::stringPrintf(str, "unused%d", resourceIndex);

											textures += "\tTexture2D<float4> " + str + ";\n";
										}

										textures += "\t";

										sce::Shader::Binary::PsslType psslType = sce::Shader::Binary::PsslType(sbb.m_type);
										switch (sbb.m_langType)
										{
										default:
										case sce::Shader::Binary::PsslBufferType::kBufferTypeDataBuffer:   textures += "DataBuffer<";   break;
										case sce::Shader::Binary::PsslBufferType::kBufferTypeRwDataBuffer: textures += "RW_DataBuffer<"; break;
										}

										textures += toString(psslType);
										textures += "> ";

										Srt srt;
										srt.name = name;
										srt.idx = sbb.m_resourceIndex;

										srts.push_back(srt);

										textures += name;
										textures += ";\n";

										textures += "\tDataBuffer<float4> ";
										bx::stringPrintf(textures, "pad%d", resourceIndex);
										textures += ";\n";

										init += "\t";
										init += name;
										init += " = bgfxSrtData.textures->";
										init += name;
										init += ";\n";

										++resourceIndex;
									}
									else
									{
										uint32_t len = (uint32_t)bx::strLen(name);
										if (0 != bx::strCmp(name, "__GLOBAL_CB__")
											&& len > 7)
										{
											if (0 == bx::strCmp(&name[len - 7], "Texture"))
											{
												for (; resourceIndex != sbb.m_resourceIndex; ++resourceIndex)
												{
													std::string str;
													bx::stringPrintf(str, "unused%d", resourceIndex);

													textures += "\tTexture2D<float4> " + str + ";\n";
												}

												char str[1024];
												bx::strCopy(str, sizeof(str), name, len - 7);
												BX_TRACE("%2d: %s", ii, str);

												textures += "\t";

												sce::Shader::Binary::PsslType psslType = sce::Shader::Binary::PsslType(sbb.m_type);
												switch (sbb.m_langType)
												{
												default:
												case sce::Shader::Binary::PsslBufferType::kBufferTypeTexture2d:          textures += "Texture2D<";             break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeTexture2dArray:     textures += "Texture2D_Array<";       break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeMsTexture2d:        textures += "MS_Texture2D<";          break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeMsTexture2dArray:   textures += "MS_Texture2D_Array<";    break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwTexture2d:        textures += "RW_Texture2D<";          break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwTexture2dArray:   textures += "RW_Texture2D_Array<";    break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwMsTexture2d:      textures += "RW_MS_Texture2D<";       break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwMsTexture2dArray: textures += "RW_MS_Texture2D_Array<"; break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeTexture3d:          textures += "Texture3D<";             break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwTexture3d:        textures += "RW_Texture3D<";          break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeTextureCube:        textures += "TextureCube<";           break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeTextureCubeArray:   textures += "TextureCube_Array<";     break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwTextureCube:      textures += "RW_TextureCube<";        break;
												case sce::Shader::Binary::PsslBufferType::kBufferTypeRwTextureCubeArray: textures += "RW_TextureCube_Array<";  break;
												};

												textures += toString(psslType);
												textures += "> ";

												Srt srt;
												srt.name = str;
												srt.idx = sbb.m_resourceIndex;

												srts.push_back(srt);

												textures += str;
												textures += ";\n";

												if (samplers.end() != samplers.find(str))
												{
													init += "\t";
													init += str;
													init += ".m_sampler = bgfxSrtData.samplers->";
													init += str;
													init += ";\n";
												}

												init += "\t";
												init += str;
												init += ".m_texture = bgfxSrtData.textures->";
												init += str;
												init += ";\n";

												++resourceIndex;
											}
										}
									}
								}

								if (!textures.empty()
									|| !input.empty())
								{
									delete shaderData;

									size_t end = std::string::npos;
									size_t pos = _code.find("[NUM_THREADS(");
									if (std::string::npos != pos)
									{
										end = _code.find(')', pos);
										end = _code.find(')', end + 1);
									}
									else
									{
										pos = std::string::npos == pos ? _code.find("void main(") : pos;
										pos = std::string::npos == pos ? _code.find("Output main(") : pos;
										end = _code.find(')', pos);
									}

									std::string code(_code, 0, pos);
									code += "\n";

									if (!textures.empty())
									{
										code += "struct BgfxSrtTextures\n{\n";
										code += textures;
										code += "};\n\n";

										code += "struct BgfxSrtSamplers\n{\n";
										code += samplersInit;
										code += "};\n\n";

										code +=
											"struct BgfxSrt\n"
											"{\n"
											"\tBgfxSrtSamplers* samplers;\n"
											"\tBgfxSrtTextures* textures;\n"
											"};\n"
											"\n"
											;

										size_t func = _code.find("main(", pos) + 5;
										code += _code.substr(pos, func - pos);
										std::string args = _code.substr(func, end - func);
										code += input.empty() ? args : input;
										code += 1 >= args.size() ? " " : ", ";
										code += "BgfxSrt bgfxSrtData : S_SRT_DATA)\n{\n";
										code += init;
									}
									else
									{
										size_t func = _code.find('(', pos) + 1;
										code += _code.substr(pos, func - pos);
										code += input;
										code += ")\n{\n";
									}

									end = _code.find('{', end) + 1;

									code += _code.substr(end);

									//								fputs(code.c_str(), stderr);

									return compile(_options, _version, code, _writer, false, srts);
								}
							}

							UniformArray uniforms;
							uint8_t numAttrs = 0;
							uint16_t attrs[bgfx::Attrib::Count];

							if ('v' == _options.shaderType) // Only care about input semantic on vertex shaders
							{
								size_t pos = _code.find("Output main(");
								size_t end = _code.find(')', pos);
								size_t func = _code.find("main(", pos) + 5;
								std::string args = _code.substr(func, end - func);
								StringViewArray sa = split(args.c_str(), ',');

								bool hasSrt = false;

								if (0 != sa.size())
								{
									const bx::StringView srtArg = sa[sa.size() - 1];
									hasSrt = !bx::strFind(srtArg, "BgfxSrt").isEmpty();

									if (hasSrt)
									{
										sa.pop_back();
									}

									if (sbp->m_numInputAttributes != sa.size())
									{
										std::string code(_code, 0, pos);
										code += "Output main(";

										bool first = true;

										for (uint32_t ii = 0, num = sbp->m_numInputAttributes; ii < num; ++ii)
										{
											const sce::Shader::Binary::Attribute& sbs = sbp->m_inputAttributes[ii];

											std::string semantic = sbs.getSemanticName();
											if (0 == bx::strCmp(sbs.getSemanticName(), "TEXCOORD")
												|| 0 == bx::strCmp(sbs.getSemanticName(), "COLOR"))
											{
												bx::stringPrintf(semantic, "%d", sbs.m_semanticIndex);
											}

											for (StringViewArray::const_iterator it = sa.begin(), itEnd = sa.end(); it != itEnd; ++it)
											{
												if (!bx::strFind(*it, semantic.c_str()).isEmpty())
												{
													code += !first ? "," : "";
													first = false;
													code.append(it->getPtr(), it->getTerm());

													sa.erase(it);
													break;
												}
											}
										}

										if (hasSrt)
										{
											code += !first ? "," : "";
											code.append(srtArg.getPtr(), srtArg.getTerm());
										}

										code += ")\n{\n";

										if (0 != sa.size())
										{
											code += "\t// Removed input attributes:\n";
											for (StringViewArray::const_iterator it = sa.begin(), itEnd = sa.end(); it != itEnd; ++it)
											{
												code += "\t";
												code.append(it->getPtr(), bx::strFind(*it, ':').getPtr());
												code += ";\n";
											}
										}

										end = _code.find('{', end);
										code += _code.substr(end + 1);

										return compile(_options, _version, code, _writer, false, _srts);
									}
								}

								for (uint32_t ii = 0, num = sbp->m_numInputAttributes; ii < num; ++ii)
								{
									const sce::Shader::Binary::Attribute& sbs = sbp->m_inputAttributes[ii];

									const RemapInputSemantic& ris = findInputSemantic(
										sbs.getSemanticName()
										, sbs.m_semanticIndex
									);
									if (ris.m_attr != bgfx::Attrib::Count)
									{
										BX_TRACE("Attribute: %s", sbs.getName());
										attrs[numAttrs] = bgfx::attribToId(ris.m_attr);
										++numAttrs;
									}
								}
							}

							uint16_t uniformBufferSize = 0;
							for (uint32_t ii = 0, num = sbp->m_numElements; ii < num; ++ii)
							{
								const sce::Shader::Binary::Element& sbs = sbp->m_elements[ii];

								Uniform un;
								un.name = sbs.getName();
								un.type = findUniformType(sce::Shader::Binary::PsslType(sbs.m_type));
								if (bgfx::UniformType::Count == un.type)
								{
									continue;
								}

								un.num = uint8_t(sbs.m_numElements);
								un.regIndex = uint16_t(sbs.m_byteOffset / 16);
								un.regCount = uint16_t(sbs.m_size / 16);
								uniforms.push_back(un);

								uniformBufferSize = bx::max(
									uniformBufferSize
									, uint16_t(sbs.m_byteOffset + sbs.m_size)
								);

								BX_TRACE("%s", sbs.getName());
							}

							uint8_t numSrtData = 0;
							for (uint32_t ii = 0, num = uint32_t(_srts.size()); ii < num; ++ii)
							{
								Uniform un;
								un.name = _srts[ii].name.c_str();
								un.type = UniformType::Enum(bgfx::UniformType::Sampler | kUniformSamplerBit);
								un.num = 1;
								un.regIndex = uint16_t(_srts[ii].idx);
								un.regCount = 0;
								uniforms.push_back(un);

								numSrtData = bx::max(numSrtData, uint8_t(un.regIndex + 1));
							}

							uint16_t count = (uint16_t)uniforms.size();
							bx::write(_writer, count);

							uint32_t fragmentBit = 'f' == _options.shaderType ? kUniformFragmentBit : 0;
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

							//						bx::align(_writer, 4);
							bx::write(_writer, shaderSize);
							bx::write(_writer, shaderData, shaderSize);
							uint8_t nul = 0;
							bx::write(_writer, nul);

							bx::write(_writer, numAttrs);
							bx::write(_writer, attrs, numAttrs * sizeof(uint16_t));

							bx::write(_writer, uniformBufferSize);
							bx::write(_writer, numSrtData);
						}

						delete shaderData;
					}
				}
			}

			bx::dlclose(sceShaderBinaryDll);
			return true;

		error:
			bx::dlclose(sceShaderBinaryDll);
			return false;
		}
#endif // BGFX_GNM
	} // namespace pssl

	bool compilePSSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
#if defined(BGFX_GNM)
		pssl::SrtArray srts;
		return pssl::compile(_options, _version, _code, _writer, true, srts);
#else
		BX_UNUSED(_options, _version, _code, _writer);
		bx::printf("PSSL not supported for this platform");
		return false;
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

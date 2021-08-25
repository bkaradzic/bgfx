#include "../../../bgfx/tools/shaderc/shaderc.h"

#if defined(BGFX_PROSPERO)
#include <bx/os.h>
#include <bx/string.h>
#include <bx/process.h>
#include <bx/sort.h>

#include <shader\shader_reflection.h>
#include <prospero_wave_psslc.h>
#include <agc\shaderbinary.h>
#include <unordered_set>
#include <map>

#include <string>
#include <iostream>
#include <sstream>

#endif



namespace bgfx {
	namespace pssl2
	{

#if defined(BGFX_PROSPERO)

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

		// --------------------------------------------------------------------------/
		// iterate over all structs
		template <typename Fn>
		static void ForEachStruct(
			SceShaderMetadataSectionHandle md,
			SceShaderTypeHandle type,
			Fn fn)
		{
			if (nullptr != type)
			{
				SceShaderTypeClass const klass = sceShaderGetTypeClass(md, type);
				switch (klass)
				{
				case SceShaderArrayType:
					return ForEachStruct(md, sceShaderGetArrayElement(md, type), fn);
				case SceShaderStructType:
					fn(type);
					for (SceShaderMemberHandle m = sceShaderGetFirstMember(md, type);
						nullptr != m;
						m = sceShaderGetNextMember(md, m))
						ForEachStruct(md, sceShaderGetMemberType(md, m), fn);
					return;
				case SceShaderPointerType:
					return ForEachStruct(md, sceShaderGetPointerElement(md, type), fn);
				case SceShaderTextureType:
				case SceShaderBufferType:
					return ForEachStruct(md, sceShaderGetBufferElementType(md, type), fn);
				default:
					return;
				};
			}
		}

		// --------------------------------------------------------------------------/
		// gather all user-defined structures used by any resource in the shader
		static void GetUserDefinedTypes(
			SceShaderMetadataSectionHandle md,
			SceShaderResourceListHandle reflection,
			std::vector<SceShaderTypeHandle>& structures,
			std::map<SceShaderTypeHandle, std::string>& names)
		{
			// traverse the type hierarchy and collect structures we want to print out
			for (SceShaderResourceHandle r = sceShaderGetFirstResource(md, reflection);
				nullptr != r;
				r = sceShaderGetNextResource(md, r))
			{
				ForEachStruct(md, sceShaderGetResourceType(md, r), [&](auto handle) {
					if (nullptr == sceShaderGetTypeName(md, handle))
						return;
					auto const it = std::find(structures.begin(), structures.end(), handle);
					if (it == structures.end())
						structures.push_back(handle);
				});
			}
			if (structures.empty())
				return;

			// now we want to give versioned name to each struct
			std::map<std::string, int> rnames;
			for (auto const s : structures)
			{
				std::string name(sceShaderGetTypeName(md, s));
				auto it = rnames.find(name);
				if (it == rnames.end()) {
					names[s] = name;
					rnames[name] = 1;
				}
				else {
					char tmp[1024];
					snprintf(tmp, sizeof(tmp), "%s@%d", name.c_str(), it->second);
					names[s] = tmp;
					rnames[name]++;
				}
			}
		}

		static char const* Indent(std::ostream& os, int32_t howMuch)
		{
			for (auto i = 0; i < howMuch; ++i) os << " ";
			return "";
		}

		// --------------------------------------------------------------------------/
		// Dump a type from the reflection data. this is recursive since type contains
		// other types. A structure contains a list of typed member. An array has a
		// valid type for its elements and so on.
		static void PrintReflectionType(
			SceShaderMetadataSectionHandle md,
			SceShaderTypeHandle type,
			std::map<SceShaderTypeHandle, std::string> const& names,
			std::ostream& os,
			bool expandStructs,
			int32_t indent = 0
		)
		{
			auto const ind = [&]() { return Indent(os, indent); };

			// early out
			if (nullptr == type)
			{
				os << ind() << "nullptr";
				return;
			}

			// Shader type class enumerates all types supported and exposed by the API
			SceShaderTypeClass const klass = sceShaderGetTypeClass(md, type);

			// handy lambda to print structs/constant buffers
			auto const printAggregate = [&]()
			{
				std::string name;
				auto const nameIt = names.find(type);
				if (nameIt == names.end())
					name = sceShaderGetTypeName(md, type);
				else
					name = nameIt->second.c_str();

				if (expandStructs)
				{
					if (SceShaderStructType == klass)
						os << ind() << "struct ";
					else
						os << ind() << "ConstantBuffer ";

					// build a vector of string pair, so we can nicely align them lazily
					std::vector<std::pair<std::string, std::string>> lines;

					// one line per member
					int32_t memberColSize = 0;

					// sceShaderGetFirstMember and sceShaderGetNextMember iterate over
					// the list of a structure members
					for (SceShaderMemberHandle m = sceShaderGetFirstMember(md, type);
						nullptr != m;
						m = sceShaderGetNextMember(md, m))
					{
						// print the member itself
						std::stringstream mos;
						PrintReflectionType(
							md,
							sceShaderGetMemberType(md, m),
							names,
							mos,
							false,
							indent);
						mos << " " << sceShaderGetMemberName(md, m) << ";";

						// print the extra information related to it
						std::stringstream ios;
						ios << "  // offset: " << sceShaderGetMemberOffset(md, m);

						if (!sceShaderIsMemberUsed(md, m))
						{
							ios << ",unused";
						}
						std::string const moString = mos.str();
						std::string const ioString = ios.str();
						memberColSize = std::max(memberColSize, int(moString.size()));
						lines.push_back({ moString, ioString });
					}

					// Now print the structure out
					char tmp[2048];
					os << " { // size=" << sceShaderGetStructSize(md, type) << "\n";
					indent++;
					int32_t memberIndex = 0;
					for (SceShaderMemberHandle m = sceShaderGetFirstMember(md, type);
						nullptr != m;
						m = sceShaderGetNextMember(md, m), ++memberIndex)
					{
						os << ind();
						snprintf(tmp, sizeof(tmp), "%-*s%s",
							memberColSize,
							lines[memberIndex].first.c_str(),
							lines[memberIndex].second.c_str());
						os << tmp << "\n";
						if (void const* const defaultValue = sceShaderGetDefaultValue(md, m))
						{
							uint64_t const defaultValuesize = sceShaderGetDefaultValueSize(md, m);
							indent += 4;
							os << ind() << "default-value: ";
							indent++;
							int32_t const lineWidth = 8;
							for (int32_t r = 0; r < int32_t(defaultValuesize); ++r)
							{
								char buf[3];
								snprintf(
									buf,
									sizeof(buf),
									"%02x",
									reinterpret_cast<uint8_t const*>(defaultValue)[r]);
								if (0 == r % lineWidth)
									os << "\n" << ind();
								os << buf << " ";
							}
							indent -= 5;
							os << "\n";
						}
					}
					indent--;
					os << ind() << "};\n";
				}
				else
					os << name.c_str();	// otherwise just print the name
			};

			switch (klass)
			{
			case SceShaderVectorType:
			case SceShaderMatrixType:
			{
				bool const ismatrix = SceShaderMatrixType == klass;
				SceShaderNumericClass const numklass = sceShaderGetNumericClass(md, type);
				int32_t const cols = sceShaderGetColumns(md, type);
				int32_t const rows = sceShaderGetRows(md, type);
				bool const rm = sceShaderIsRowMajor(md, type);
				if (ismatrix && rm)
					os << "row_major ";
				os << sceShaderGetNumericClassName(numklass);
				if ((!ismatrix && cols > 1) || ismatrix)
					os << cols;
				if (ismatrix)
					os << "x" << rows;
			}
			break;

			case SceShaderArrayType:
			{
				SceShaderTypeHandle elemTy = sceShaderGetArrayElement(md, type);
				while (SceShaderArrayType == sceShaderGetTypeClass(md, elemTy))
					elemTy = sceShaderGetArrayElement(md, elemTy);
				PrintReflectionType(md, elemTy, names, os, false, indent);
				elemTy = type;
				while (SceShaderArrayType == sceShaderGetTypeClass(md, elemTy))
				{
					os << "[" << sceShaderGetArraySize(md, elemTy) << "]";
					elemTy = sceShaderGetArrayElement(md, elemTy);
				}
			}
			break;

			case SceShaderStructType:
				printAggregate();
				break;

			case SceShaderPointerType:
				PrintReflectionType(
					md,
					sceShaderGetPointerElement(md, type),
					names,
					os,
					false,
					indent);
				os << "*";
				break;

			case SceShaderSamplerStateType:
				os << "SamplerState";
				break;

			case SceShaderTextureType:
			case SceShaderBufferType:
			{
				if (sceShaderIsRwBuffer(md, type))
					os << "RW_";
				SceShaderBufferClass const bufferClass = sceShaderGetBufferClass(md, type);
				os << sceShaderGetBufferClassName(bufferClass);
				if (SceShaderByteBuffer != bufferClass)
				{
					os << "<";
					SceShaderTypeHandle const bufferElemType = sceShaderGetBufferElementType(md, type);
					PrintReflectionType(md, bufferElemType, names, os, false, indent);
					os << ">";
				}
			}
			break;
			default:
				os << "unknown";
				break;
			};
		}


		static bool printReflectionDataPSSL2(const SceShaderBinaryHandle& sl)
		{
			// --------------------------------------------------------------------------/
			// dump reflection
			{
				// For now, just dump everything to stdout
				std::ostream& os = std::cout;

				int32_t level = 0;
				auto const ind = [&]() { return Indent(os, level); };

				SceShaderMetadataSectionHandle const md = sceShaderGetMetadataSection(sl);
				if (nullptr == md)
					return false;

				// this gives a list of all resources used by the shader
				SceShaderResourceListHandle const reflection = sceShaderGetResourceList(md);
				if (nullptr == reflection)
					return false;

				// start by gathering all user defined structures
				std::vector<SceShaderTypeHandle> structures;
				std::map<SceShaderTypeHandle, std::string> names;
				GetUserDefinedTypes(md, reflection, structures, names);

				// scan resources to compute a decent justification value for columns
				int32_t nameColWidth = 0, numResources = 0;
				for (SceShaderResourceHandle r = sceShaderGetFirstResource(md, reflection);
					nullptr != r;
					r = sceShaderGetNextResource(md, r))
				{
					if (char const* const name = sceShaderGetResourceName(md, r))
						nameColWidth = std::max(int(strlen(name)), nameColWidth);
					numResources++;
				}
				if (0 == numResources)
					return false;
				nameColWidth = std::min(nameColWidth, 40);
				auto const resourceIndexWidth = int32_t(std::to_string(numResources).size());

				// open a multi-line comment section
				os << ind() << "\n";
				os << ind() << "/*\n";

				// print out resources
				os << ind() << "=== resources:\n";

				uint32_t index = 0;
				for (SceShaderResourceHandle r = sceShaderGetFirstResource(md, reflection);
					nullptr != r;
					r = sceShaderGetNextResource(md, r), ++index)
				{
					SceShaderResourceClass const klass = sceShaderGetResourceClass(md, r);
					char const* const name = sceShaderGetResourceName(md, r);
					int32_t const apiSlot = sceShaderGetResourceApiSlot(md, r);
					SceShaderTypeHandle const type = sceShaderGetResourceType(md, r);
					char temp[256];
					snprintf(temp, sizeof(temp), "%*d) class: %-10s slot: %-3d name:%-*s",
						resourceIndexWidth,
						index,
						sceShaderGetResourceClassName(klass),
						apiSlot,
						nameColWidth,
						name ? name : "anonymous");
					os << ind() << temp;
					if (SceShaderInputAttribute == klass || SceShaderOutputAttribute == klass)
					{
						char const* const semaName = sceShaderGetSemanticName(md, r);
						int32_t const semaIndex = sceShaderGetSemanticIndex(md, r);
						os << " semantic: " << semaName << " index: " << semaIndex;
					}
					if (nullptr != type)
					{
						os << " type: ";
						PrintReflectionType(md, type, names, os, false, level);
					}
					os << "\n";
				}

				if (!structures.empty())
				{
					os << "\n";
					os << ind() << "=== user-types:\n";
					for (auto const s : structures)
					{
						PrintReflectionType(md, s, names, os, true, level);
						os << "\n";
					}
				}

				// close the comment section
				os << ind() << "*/\n";
			}

			return true;
		}

		// --------------------------------------------------------------------------/
		// Get a type from the reflection data. Non recursive
		static void GetReflectionTypeInfo(
			SceShaderMetadataSectionHandle md,
			SceShaderTypeHandle type,
			Uniform& uniform,
			std::map<SceShaderTypeHandle, std::string> const& names
		)
		{
			UniformType::Enum ut = UniformType::Count;

			// early out
			if (nullptr == type)
			{
				BX_TRACE("nullptr");
				return;
			}

			// Shader type class enumerates all types supported and exposed by the API
			SceShaderTypeClass const klass = sceShaderGetTypeClass(md, type);

			int regCount = 0;

			switch (klass)
			{
			case SceShaderVectorType:
			{
				int32_t const cols = sceShaderGetColumns(md, type);
				if (cols == 4)
				{
					regCount = 1;
					ut = UniformType::Vec4;
				}
				else
					BX_TRACE("Unsupported Vector type float%d", cols);
			}
			break;

			case SceShaderMatrixType:
			{
				bool const ismatrix = SceShaderMatrixType == klass;
				SceShaderNumericClass const numklass = sceShaderGetNumericClass(md, type);
				int32_t const cols = sceShaderGetColumns(md, type);
				int32_t const rows = sceShaderGetRows(md, type);
				bool const rm = sceShaderIsRowMajor(md, type);

				if (rows == cols)
				{
					if (rows == 3)
					{
						ut = UniformType::Mat3;
						regCount = 3;
					}
					else if (rows == 4)
					{
						ut = UniformType::Mat4;
						regCount = 4;
					}
					else
					{
						BX_TRACE("unsupported matrix");
					}

				}
				else
				{
					BX_TRACE("unsupported matrix");
				}
			}
			break;

			case SceShaderArrayType:
			{
				BX_TRACE("Don't support nested arrays"); // BBI-NOTE (dgalloway) This might include 2D arrays. IE [4][4]
			}
			break;

			case SceShaderStructType:
				BX_TRACE("Don't support nested structures"); // BBI-NOTE (dgalloway) we don't support nested structures
				break;

			case SceShaderPointerType:
				BX_TRACE("Don't support pointer types"); // BBI-NOTE (dgalloway) we don't support nested structures
				break;

			case SceShaderSamplerStateType:
				// "SamplerState";
				BX_TRACE("SamplerState");
				break;

			case SceShaderTextureType:
			case SceShaderBufferType:
			{
				if (sceShaderIsRwBuffer(md, type))
				{
					BX_TRACE("RW_Buffer");
				}

				SceShaderBufferClass const bufferClass = sceShaderGetBufferClass(md, type);
				BX_TRACE("%s", sceShaderGetBufferClassName(bufferClass));

				if (SceShaderByteBuffer != bufferClass)
				{
					BX_TRACE("Not a byte buffer");
					//SceShaderTypeHandle const bufferElemType = sceShaderGetBufferElementType(md, type);
					//GetReflectionType(md, bufferElemType, names, false, _uniforms, indent);
				}
			}
			break;
			default:
				BX_TRACE("unknown");
				break;
			};

			uniform.type = ut;
			uniform.regCount = regCount;

			return;
		}

		// --------------------------------------------------------------------------/
		// Dump a type from the reflection data. this is recursive since type contains
		// other types. A structure contains a list of typed member. An array has a
		// valid type for its elements and so on.
		static void GetReflectionType(
			SceShaderMetadataSectionHandle md,
			SceShaderTypeHandle type,
			std::map<SceShaderTypeHandle, std::string> const& names,
			bool expandStructs,
			UniformArray& _uniforms,
			int32_t indent = 0
		)
		{
			// early out
			if (nullptr == type)
			{
				BX_TRACE("nullptr");
				return;
			}

			// Shader type class enumerates all types supported and exposed by the API
			SceShaderTypeClass const klass = sceShaderGetTypeClass(md, type);

			// lambda to handle structs/constant buffers
			auto const getAggregate = [&]()
			{
				std::string name;
				auto const nameIt = names.find(type);
				if (nameIt == names.end())
					name = sceShaderGetTypeName(md, type);
				else
					name = nameIt->second.c_str();

				if (expandStructs)
				{
					Uniform un;

					// When SceShaderStructType == klass then "struct " else "ConstantBuffer"
					// sceShaderGetFirstMember and sceShaderGetNextMember iterate over
					// the list of a structure members

					for (SceShaderMemberHandle m = sceShaderGetFirstMember(md, type);
						nullptr != m;
						m = sceShaderGetNextMember(md, m))
					{

						auto name = sceShaderGetMemberName(md, m);

						BX_TRACE(" s: %s", name);

						un.name.assign(name);
						if (name == "__GLOBAL_CB__")
							return;

						// BBI-NOTE (dgalloway) we don't support nested aggregates

						SceShaderTypeHandle const memberType = sceShaderGetMemberType(md, m);
						SceShaderTypeClass const memberKlass = sceShaderGetTypeClass(md, memberType);

						if (memberKlass == SceShaderArrayType)
						{  //BBI-NOTE only support single dimensional arrays currently :|

							SceShaderTypeHandle elemTy = sceShaderGetArrayElement(md, memberType);

							while (SceShaderArrayType == sceShaderGetTypeClass(md, elemTy))
								elemTy = sceShaderGetArrayElement(md, elemTy);

							// Get the uniform data on a member
							GetReflectionTypeInfo(
								md,
								elemTy,
								un,
								names);

							auto arraySize = sceShaderGetArraySize(md, memberType);


							un.name.assign(name);
							un.num = arraySize;
							un.regCount = un.regCount * arraySize;
							un.regIndex = sceShaderGetMemberOffset(md, m);

						}
						else
						{
							GetReflectionTypeInfo(
								md,
								memberType,
								un,
								names);

							un.name.assign(name);
							un.num = 1;
							un.regIndex = sceShaderGetMemberOffset(md, m);
						}

						if (!sceShaderIsMemberUsed(md, m))
						{
							BX_TRACE("unused member");
							//BBI-TODO (dgalloway 3) how to handle this (does this need a two pass or just ignore)
						}
						else
						{
							_uniforms.push_back(un);
						}
					}
				}
			};

			if (klass == SceShaderStructType)
			{
				getAggregate();
			}
			else
			{

				std::string name;
				auto const nameIt = names.find(type);
				if (nameIt == names.end())
				{
					if (nullptr == sceShaderGetTypeName(md, type))
						return;
					name = sceShaderGetTypeName(md, type);
					if (name == "__GLOBAL_CB__")
						return;
				}
				else
					name = nameIt->second.c_str();

				Uniform un;

				GetReflectionTypeInfo(
					md,
					type,
					un,
					names);

				un.name.assign(name);

				_uniforms.push_back(un);
			}
		}

		static bool getReflectionDataPSSL2(const SceShaderBinaryHandle& sl, UniformArray& _uniforms, uint16_t& size, uint16_t* _attrs, uint8_t& _numAttrs)
		{
			// --------------------------------------------------------------------------/
			// dump reflection
			{

				SceShaderMetadataSectionHandle const md = sceShaderGetMetadataSection(sl);
				if (nullptr == md)
					return false;

				// this gives a list of all resources used by the shader
				SceShaderResourceListHandle const reflection = sceShaderGetResourceList(md);
				if (nullptr == reflection)
					return false;

				// start by gathering all user defined structures
				std::vector<SceShaderTypeHandle> structures;
				std::map<SceShaderTypeHandle, std::string> names;
				GetUserDefinedTypes(md, reflection, structures, names);

				// scan resources and count
				int32_t numResources = 0;
				for (SceShaderResourceHandle r = sceShaderGetFirstResource(md, reflection);
					nullptr != r;
					r = sceShaderGetNextResource(md, r))
				{
					numResources++;
				}

				if (0 == numResources)
					return false;

				uint32_t index = 0;
				for (SceShaderResourceHandle r = sceShaderGetFirstResource(md, reflection);
					nullptr != r;
					r = sceShaderGetNextResource(md, r), ++index)
				{
					SceShaderResourceClass const klass = sceShaderGetResourceClass(md, r);
					char const* const name = sceShaderGetResourceName(md, r);
					int32_t const apiSlot = sceShaderGetResourceApiSlot(md, r);
					SceShaderTypeHandle const type = sceShaderGetResourceType(md, r);
					char const* const resourceName = sceShaderGetResourceClassName(klass);

					BX_TRACE("- %s, %d, %s", name, apiSlot, resourceName);

					if (klass == SceShaderInputAttribute)
					{
						BX_TRACE("Input semantic");

						char const* const semaName = sceShaderGetSemanticName(md, r);
						int32_t const semaIndex = sceShaderGetSemanticIndex(md, r);

						const RemapInputSemantic& ris = findInputSemantic(semaName, uint8_t(semaIndex));
						if (ris.m_attr != bgfx::Attrib::Count)
						{
							_attrs[_numAttrs] = bgfx::attribToId(ris.m_attr);
							++_numAttrs;
						}
					}

					if (klass == SceShaderSamplerState)
					{
						Uniform un;

						// Remove 'sampler' suffix to adhere to same convention as DX
						// Not sure this is truly necessary
						std::string bufferName = name;
						std::string s = "Sampler";
						std::string::size_type i = bufferName.rfind(s);
						if (i != std::string::npos)
							bufferName.erase(i, s.length());

						un.name = bufferName;
						un.type = UniformType::Enum(kUniformSamplerBit | UniformType::Sampler);
						un.num = 1;
						un.regIndex = apiSlot;
						un.regCount = 0;

						_uniforms.push_back(un);
					}

					if (SceShaderInputAttribute == klass || SceShaderOutputAttribute == klass)
					{
						char const* const semaName = sceShaderGetSemanticName(md, r);
						int32_t const semaIndex = sceShaderGetSemanticIndex(md, r);
						//os << " semantic: " << semaName << " index: " << semaIndex;
					}
					if (nullptr != type)
					{
						GetReflectionType(md, type, names, false, _uniforms);
					}
				}

				if (!structures.empty())
				{
					// BBI-TODO (dgalloway 3) assert that there is one and only one CB / structure
					// otherwise we will have to handle it differently
					for (auto const s : structures)
					{
						//SceShaderTypeHandle const type = sceShaderGetResourceType(md, s);
						size = (int16_t)sceShaderGetStructSize(md, s);
						GetReflectionType(md, s, names, true, _uniforms);
					}
				}
			}

			return true;
		}


		static bool writeUniforms(const Options& _options, bx::WriterI* _writer, UniformArray& uniforms)
		{

			struct UniformMapping
			{
				bgfx::UniformType::Enum mType;
				uint16_t mSize;
				uint16_t mRegCount;
			};

			BX_TRACE("\n\n--------------------------------------------------\n")

			{
				uint16_t count = (uint16_t)uniforms.size();
				bx::write(_writer, count);
				BX_TRACE("uniforms count:%d", count);

				bool isFragment = (_options.shaderType == 'f');
				uint32_t fragmentBit = isFragment ? kUniformFragmentBit : 0;

				for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
				{
					const Uniform& un = *it;

					uint8_t nameSize = (uint8_t)un.name.size();
					bx::write(_writer, nameSize);
					bx::write(_writer, un.name.c_str(), nameSize);
					BX_TRACE("%d: %s", nameSize, un.name.c_str());
					uint8_t type = uint8_t(un.type | fragmentBit);
					bx::write(_writer, type);
					BX_TRACE("type:%d, fragmentBit: %d", un.type, fragmentBit);
					bx::write(_writer, un.num);
					BX_TRACE("num:%d", un.num);
					bx::write(_writer, un.regIndex);
					BX_TRACE("regIndex:%d", un.regIndex);
					bx::write(_writer, un.regCount);
					BX_TRACE("regCount:%d", un.regCount);
					bx::write(_writer, un.texComponent);
					BX_TRACE("texComponent:%d", un.texComponent);
					bx::write(_writer, un.texDimension);
					BX_TRACE("texDimension:%d", un.texDimension);
					bx::write(_writer, un.texFormat); // BBI-NOTE: (manderson) new in version 10
					BX_TRACE("texFormat:%d", un.texFormat);
				}
			}

			return true;
		}

		struct UniformRemap
		{
			UniformType::Enum id;
			int type;
			//sce::Prospero::Binary::PsslType type;
		};

		static const UniformRemap s_uniformRemap[] =
		{
			{ UniformType::Sampler, 0     },
			{ UniformType::Vec4, 1   }

			//{ UniformType::Sampler, sce::Prospero::Binary::PsslType::kTypeInt1     },
			//{ UniformType::Vec4, sce::Prospero::Binary::PsslType::kTypeFloat4   },
			//{ UniformType::Mat3, sce::Prospero::Binary::PsslType::kTypeFloat3x3 },
			//{ UniformType::Mat4, sce::Prospero::Binary::PsslType::kTypeFloat4x4 },
			//{ UniformType::Sampler, sce::Prospero::Binary::PsslType::kTypeInt1     },
			//{ UniformType::Sampler, sce::Prospero::Binary::PsslType::kTypeInt1     },
			//{ UniformType::Sampler, sce::Prospero::Binary::PsslType::kTypeInt1     },
			//{ UniformType::Sampler, sce::Prospero::Binary::PsslType::kTypeInt1     },
		};

		UniformType::Enum findUniformType(int _type) // BBI-TODO (dgalloway 3) use correct type
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

		static const char* toString(int _psslType)
		{
			switch (_psslType)
			{
			case 0:   return "int1";
			case 1:   return "int2";
			case 2:   return "int3";
			case 3:   return "int4";
			case 4:  return "uint1";
			case 5:  return "uint2";
			case 6:  return "uint3";
			case 7:  return "uint4";
			case 8: return "float1";
			case 9: return "float2";
			case 10: return "float3";
			case 11: // float4 BBI-TODO
			default: break;
			};

			return "float4";
		}

		struct Srt
		{
			std::string name;
			uint32_t idx;
		};

		// --------------------------------------------------------------------------/
		static sce::Prospero::Wave::Psslc::SourceFile* loadShaderSource(
			const char* fileName,
			const sce::Prospero::Wave::Psslc::SourceLocation* includedFrom,
			const sce::Prospero::Wave::Psslc::OptionsBase* compileOptions,
			void* userData,
			const char** errorString)
		{
			// there is only one file to open
			(void)fileName;
			(void)includedFrom;
			(void)compileOptions;
			(void)userData;
			(void)errorString;
			return (sce::Prospero::Wave::Psslc::SourceFile*)userData;
		}

		// --------------------------------------------------------------------------/
		static void releaseShaderSource(
			const sce::Prospero::Wave::Psslc::SourceFile* file,
			const sce::Prospero::Wave::Psslc::OptionsBase* compileOptions,
			void* userData)
		{
			(void)file;
			(void)compileOptions;
			(void)userData;
		}

		bool compile(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
		{
			char sceProsperoSdkDir[bx::kMaxFilePath];
			char tempDir[bx::kMaxFilePath];
			{
				uint32_t len = sizeof(sceProsperoSdkDir);
				if (!bx::getEnv(sceProsperoSdkDir, &len, "SCE_PROSPERO_SDK_DIR"))
				{
					fprintf(stderr, "Error: SCE_PROSPERO_SDK_DIR environment variable not set.");
					return false;
				}

				bx::FilePath temp(bx::Dir::Temp);
				bx::strCopy(tempDir, BX_COUNTOF(tempDir), temp);
			} // BBI-NOTE (dgalloway) if we want to load the DLL from the environment path instead of having the dll's copied to the shaderc.exe location

			std::string variant = "test";

			bool debug = _options.debugInformation;

			// BBI-TODO (dgalloway 2) finish implementing dumping pssl2 shader source
			if (0) //_options.emitShaderSource)
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
				//variant = _options.inputFilePath + "__" + variant;

				file = "c:\\test\\pssl2\\" + file + variant + ".pssl2";

				writeFile(file.c_str(), _code.c_str(), (int32_t)_code.size());
			}

			sce::Prospero::Wave::Psslc::OptionsWithCommandLine compileOptions;
			sce::Prospero::Wave::Psslc::initializeOptions(&compileOptions, SCE_PROSPERO_WAVE_API_VERSION);

			std::string shaderType = "sce_";

			{
				switch (_options.shaderType)
				{
				case 'c': shaderType += "cs";    break;
				case 'f': shaderType += "ps";    break;
				case 'v': shaderType += "vs_vs"; break;
				}

				shaderType += "_prospero";
			}


			std::vector<std::string> cmdLineOptions;

			cmdLineOptions.push_back("-profile");
			cmdLineOptions.push_back(shaderType);
			cmdLineOptions.push_back(_options.inputFilePath.c_str());
			cmdLineOptions.push_back("-Wsuppress=6923,20087,20088");  // 6923 implicit type narrowing, 20087 unreferenced formal parameter, 20088 unreferenced local variable

			if (debug)
			{
				cmdLineOptions.push_back("-Od");						// Optimize for debug
				cmdLineOptions.push_back("-O0");						// OptimizationLevel = 0;
				cmdLineOptions.push_back("-nofastmath");				// disable aggressive floating point optimization
				cmdLineOptions.push_back("-debug-info");				// specify the creation agsd files
				cmdLineOptions.push_back("-debug-info-path");
				cmdLineOptions.push_back(_options.debugDatabaseDir);	// where to store the agsd files
			}
			else
			{
				if (_options.optimize) {
					cmdLineOptions.push_back("-fastmath");
					cmdLineOptions.push_back("-O3");
				}
			}


			{
				// BBI-TODO (dgalloway 3) handle _options.defines and pass into compile options?
				//_options.defines

				sce::Prospero::Wave::Psslc::CallbackList callbackList;
				sce::Prospero::Wave::Psslc::initializeCallbackList(&callbackList, sce::Prospero::Wave::Psslc::kCallbackDefaultsTrivial);
				callbackList.openFile = &loadShaderSource;
				callbackList.releaseFile = &releaseShaderSource;

				// The above openFile callback will return this dummy file
				sce::Prospero::Wave::Psslc::SourceFile srcFile;
				srcFile.fileName = _options.inputFilePath.c_str();
				srcFile.text = _code.data();
				srcFile.size = static_cast<uint32_t>(_code.size());

				const char** opts = new const char* [cmdLineOptions.size()];

				for (int i = 0; i < cmdLineOptions.size(); i++)
				{
					opts[i] = cmdLineOptions[i].c_str();
				}

				compileOptions.userData = &srcFile;
				compileOptions.argc = (uint32_t)cmdLineOptions.size();
				compileOptions.argv = opts;

				const sce::Prospero::Wave::Psslc::Output* compileOutput = sce::Prospero::Wave::Psslc::run(&compileOptions, &callbackList);

				if (compileOutput)
				{

					if (compileOutput->programData != nullptr && compileOutput->programSize != 0)
					{

						SceShaderBinaryHandle const sl = sceShaderGetBinaryHandle(compileOutput->programData);

						if (nullptr == sl)
						{
							std::cerr << "File '" << _options.inputFilePath << "' did not generate program data\n";
							return false;
						}

						UniformArray uniforms;
						uint8_t numAttrs = 0;
						uint16_t attrs[bgfx::Attrib::Count];
						uint16_t constantBufferSize = 0;

						//printReflectionDataPSSL2(sl);
						getReflectionDataPSSL2(sl, uniforms, constantBufferSize, attrs, numAttrs);

						if (!writeUniforms(_options, _writer, uniforms))
						{
							std::cout << "Failed to write uniforms for shader binary program!\n";
							return false;
						}

						// Write binary program
						bx::write(_writer, compileOutput->programSize);
						BX_TRACE("size: %d", compileOutput->programSize);
						bx::write(_writer, compileOutput->programData, compileOutput->programSize);
						BX_TRACE("code:");
						uint8_t nul = 0;
						bx::write(_writer, nul);
						BX_TRACE("nul:");


						// Write attributes
						bx::write(_writer, numAttrs);
						BX_TRACE("numAttrs:%d", numAttrs);
						bx::write(_writer, attrs, numAttrs * sizeof(uint16_t));
						for (int i = 0; i < numAttrs; i++)
						{
							BX_TRACE("attr %d : %d", i, attrs[i]);
						}

						// Write constant buffer size
						bx::write(_writer, constantBufferSize);
						BX_TRACE("constant buffer size: %d", constantBufferSize);

						// End
						BX_TRACE("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");

						if (debug && compileOutput->agsdFileCount != 0 && compileOutput->agsdFiles[0].dataSize > 0)
						{
							static const std::string sGnmGpuDebuggerPath = _options.debugDatabaseDir;

							bx::FilePath filePath(_options.debugDatabaseDir.c_str());

							filePath.join(compileOutput->agsdFiles[0].debugExt);

							if (!(bx::makeAll(filePath.getPath())))
							{
								fprintf(stderr, "Error: Could not make path for debug AGSD files.");
								return false;
							}

							std::string outputAGSDFile(filePath.getCPtr());

							FILE* glslcOutputFileHandle = nullptr;

							if (fopen_s(&glslcOutputFileHandle, outputAGSDFile.c_str(), "wb") != 0)
							{
								fprintf(stderr, "Error: Could not open file %s.", outputAGSDFile.c_str());
								return false;

							}
							if (!glslcOutputFileHandle)
							{
								fprintf(stderr, "Error: Could not write file %s.", outputAGSDFile.c_str());
								return false;
							}

							fwrite(compileOutput->agsdFiles[0].data, compileOutput->agsdFiles[0].dataSize, 1, glslcOutputFileHandle);
							fclose(glslcOutputFileHandle);
						}
					}
					else
					{
						for (int i = 0; i < compileOutput->diagnosticCount; ++i)
						{												// BBI-TODO (dgalloway 4) maybe indicate file and type of diagnostic?
							fprintf(stderr, "Line: %d Column: %d  %s\n", /*compileOutput->diagnostics[i].level, info/warning/error */ compileOutput->diagnostics[i].location->lineNumber, compileOutput->diagnostics[i].location->columnNumber, compileOutput->diagnostics[i].message);
						}
					}
				}
				else
				{
					fprintf(stderr, "Error: No compile output for %s", _options.inputFilePath.c_str());
					return false;
				}

				delete[] opts;
			}
			return true;
		}

#endif // BGFX_PROSPERO
	} // namespace pssl2

	bool compilePSSL2Shader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
#if defined(BGFX_PROSPERO)
		return pssl2::compile(_options, _version, _code, _writer, true);
#else
		BX_UNUSED(_options, _version, _code, _writer);
		bx::printf("PSSL2 not supported for this platform");
		return false;
#endif
	}

	const char* getPssl2Preamble()
	{
#if defined(BGFX_PROSPERO)

		return pssl2::s_preamble;
#else
		return "";
#endif

	}

} // namespace bgfx

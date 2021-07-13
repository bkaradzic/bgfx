/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "../../../bgfx/tools/shaderc/shaderc.h"
#include <atomic>
#include <map>

#if defined(BGFX_NVN)
#include <nvnTool/nvnTool_GlslcInterface.h>
#endif

namespace bgfx {
	namespace nvn
	{
		// BBI-NOTE: (dgalloway) (this would need some code in bx to print to stderr via getStdErr())
		void printError(const std::string& message) {
			bx::printf(message.c_str());
		}


#if defined(BGFX_NVN)
		static const std::string sGlslcNvidiaGpuDebuggerPath = ""; // E:\\Mojang\\mehnvn\\";

		struct UniformData
		{
			std::string      m_Name;
			GLSLCpiqTypeEnum m_Type;
			int32_t          m_BlockNdx;
			int32_t          m_BlockOffset;
			int32_t          m_Bindings[6];
			uint8_t          m_IsArray;
			uint32_t         m_SizeOfArray;
			uint32_t         m_ArrayStride;
			int32_t          m_MatrixStride;
			uint32_t         m_IsRowMajor;
			uint8_t          m_StagesReferencedIn;
		};

		struct UniformBlockData
		{
			std::string m_Name;
			int32_t     m_Bindings[6];
			uint32_t    m_Size;
			uint32_t    m_NumActiveVariables;
			uint8_t     m_StagesReferencedIn;

			std::vector<UniformData> m_Uniforms;
		};

		struct VertexAttributeData
		{
			std::string      m_Name;
			GLSLCpiqTypeEnum m_Type;
			uint8_t          m_IsArray;
			uint32_t         m_SizeOfArray;
			int32_t          m_Location;
			uint8_t          m_IsPerPatch;
			uint8_t          m_StagesReferencedIn;
		};

		struct ShaderReflectionInfo
		{
			std::vector<UniformData> m_GlobalUniforms;
			std::vector<UniformBlockData> m_UniformBlocks;
			std::vector<VertexAttributeData> m_VertexAttributes;
		};

		constexpr bool getLang(char _p, NVNshaderStage& stage)
		{
			switch (_p)
			{
			case 'c': stage = NVNshaderStage::NVN_SHADER_STAGE_COMPUTE; return true;
			case 'f': stage = NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT; return true;
			case 'v': stage = NVNshaderStage::NVN_SHADER_STAGE_VERTEX; return true;
			default:  return false;
			}
		}

		constexpr bool isSampler(GLSLCpiqTypeEnum type)
		{
			switch (type)
			{
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_1D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_3D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_CUBE:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_1D_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_1D_SHADOW:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_SHADOW:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_1D_ARRAY_SHADOW:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_ARRAY_SHADOW:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_MULTISAMPLE:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_MULTISAMPLE_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_CUBE_SHADOW:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_BUFFER:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_RECT:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_SAMPLER_2D_RECT_SHADOW:
				return true;
			default:
				return false;
			}
		}

		constexpr bool isImage(GLSLCpiqTypeEnum type)
		{
			switch (type)
			{
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_1D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_2D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_3D:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_2D_RECT:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_CUBE:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_BUFFER:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_1D_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_2D_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_CUBE_MAP_ARRAY:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_2D_MULTISAMPLE:
			case GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_IMAGE_2D_MULTISAMPLE_ARRAY:
				return true;
			default:
				return false;
			}
		}

		bool fillUniformData(Uniform& target, const Options& _options, const UniformData& uniformData)
		{
			target.name = uniformData.m_Name;
			target.regIndex = uniformData.m_BlockOffset;

			struct UniformMapping
			{
				bgfx::UniformType::Enum mType;
				size_t mSize;
			};

			static const std::map<GLSLCpiqTypeEnum, UniformMapping> glUniformToBgfx = {
				{GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_FLOAT_VEC4, {bgfx::UniformType::Enum::Vec4, sizeof(float) * 4}},
				{GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_MAT3, {bgfx::UniformType::Enum::Mat3, sizeof(float) * 4 * 3}},
				{GLSLCpiqTypeEnum::GLSLC_PIQ_TYPE_MAT4, {bgfx::UniformType::Enum::Mat4, sizeof(float) * 4 * 4}},
			};

			if (isSampler(uniformData.m_Type) || isImage(uniformData.m_Type))
			{
				target.type = UniformType::Enum(bgfx::UniformType::Sampler | kUniformSamplerBit);
				target.num = 1;
				target.regCount = 1;
			}
			else {
				auto mapping = glUniformToBgfx.find(uniformData.m_Type);
				if (mapping == glUniformToBgfx.end())
				{
					printError("Unknown uniform type for " + uniformData.m_Name + ". Type is " + std::to_string(uniformData.m_Type));
					return false;
				}
				else
				{
					target.type = mapping->second.mType;
					target.num = uniformData.m_SizeOfArray;
					target.regCount = bx::alignUp((uint16_t)(mapping->second.mSize), 16);
				}
			}

			return true;
		}

		static const char* s_attribName[] =
		{
			"a_position",
			"a_normal",
			"a_tangent",
			"a_bitangent",
			"a_color0",
			"a_color1",
			"a_color2",
			"a_color3",
			"a_indices",
			"a_weight",
			"a_texcoord0",
			"a_texcoord1",
			"a_texcoord2",
			"a_texcoord3",
			"a_texcoord4",
			"a_texcoord5",
			"a_texcoord6",
			"a_texcoord7",
		};
		BX_STATIC_ASSERT(bgfx::Attrib::Count == BX_COUNTOF(s_attribName));

		bgfx::Attrib::Enum toAttribEnum(const bx::StringView& _name)
		{
			for (uint8_t ii = 0; ii < Attrib::Count; ++ii)
			{
				if (0 == bx::strCmp(s_attribName[ii], _name))
				{
					return bgfx::Attrib::Enum(ii);
				}
			}

			return bgfx::Attrib::Count;
		}

		bool writeUniforms(const Options& _options, bx::WriterI* _writer, std::vector<std::reference_wrapper<const std::vector<UniformData>>> _uniforms)
		{
			uint16_t totalCount = 0;
			for (const auto& uniformBlock : _uniforms)
			{
				totalCount += static_cast<uint16_t>(uniformBlock.get().size());
			}

			bx::write(_writer, totalCount);

			for (const auto& uniformBlock : _uniforms)
			{
				for (const UniformData& uniformData : uniformBlock.get())
				{
					Uniform un = {};
					if (!fillUniformData(un, _options, uniformData))
					{
						return false;
					}
					else
					{
						uint8_t nameSize = static_cast<uint8_t>(un.name.size());
						bx::write(_writer, nameSize);
						bx::write(_writer, un.name.c_str(), nameSize);
						bx::write(_writer, static_cast<uint8_t>(un.type));
						bx::write(_writer, un.num);
						bx::write(_writer, un.regIndex);
						bx::write(_writer, un.regCount);
						bx::write(_writer, un.texComponent); // BBI-NOTE: (tstump) this isn't added in the version of bgfx the game is based off
						bx::write(_writer, un.texDimension);
					}
				}
			}

			return true;
		}

		static bool compile(GLSLCcompileObject& compiler, const Options& _options, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
		{
			compiler.input.count = 1;

			const char* const paths[] = { _options.inputFilePath.c_str() };
			compiler.options.includeInfo.numPaths = 1;
			compiler.options.includeInfo.paths = paths;

			const char* const sources[] = { _code.c_str() };
			NVNshaderStage shaderStages[1];
			if (!getLang(_options.shaderType, shaderStages[0]))
			{
				printError(std::string{ "Error: Unknown shader type: " } + _options.shaderType);
				return false;
			}
			compiler.input.sources = sources;
			compiler.input.stages = shaderStages;

			NVNshaderStage currentShaderStage = shaderStages[0];
			NVNshaderStageBits currentShaderStageBits;

			switch (currentShaderStage)
			{
			case NVNshaderStage::NVN_SHADER_STAGE_VERTEX: {currentShaderStageBits = NVNshaderStageBits::NVN_SHADER_STAGE_VERTEX_BIT; break; }
			case NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT: {currentShaderStageBits = NVNshaderStageBits::NVN_SHADER_STAGE_FRAGMENT_BIT; break; }
			case NVNshaderStage::NVN_SHADER_STAGE_COMPUTE: {currentShaderStageBits = NVNshaderStageBits::NVN_SHADER_STAGE_COMPUTE_BIT; break; }
			default:
			{
				printError(std::string{ "Error: Unknown shader stage: " } + std::to_string(currentShaderStage));
				return false;
			}
			}

			GLSLCoptionFlags& optionFlags = compiler.options.optionFlags;
			optionFlags.outputThinGpuBinaries = 0;
			optionFlags.outputAssembly = true;
			optionFlags.outputGpuBinaries = true;
			optionFlags.glslSeparable = true;
			optionFlags.outputPerfStats = true;
			optionFlags.outputShaderReflection = true;
			optionFlags.language = GLSLClanguageTypeEnum::GLSLC_LANGUAGE_GLSL;

			if (_options.debugInformation)
			{
				optionFlags.outputDebugInfo = GLSLC_DEBUG_LEVEL_G2;
				optionFlags.optLevel = GLSLCoptLevelEnum::GLSLC_OPTLEVEL_NONE;
			}
			else if (_options.optimize)
			{
				optionFlags.outputDebugInfo = GLSLC_DEBUG_LEVEL_NONE;
				optionFlags.optLevel = GLSLCoptLevelEnum::GLSLC_OPTLEVEL_DEFAULT;
			}
			else
			{
				optionFlags.outputDebugInfo = GLSLC_DEBUG_LEVEL_G0;
			}

			if (!glslcCompile(&compiler)) {
				printError(compiler.lastCompiledResults->compilationStatus->infoLog);
				return false;
			}

			const GLSLCoutput* compileOutput = compiler.lastCompiledResults->glslcOutput;

			if (sGlslcNvidiaGpuDebuggerPath.size() > 0)
			{
				static std::atomic<int> sFileUniqueCounter = 0;

				FILE* glslcOutputFileHandle = NULL;

				std::string glslcOutputFileName(sGlslcNvidiaGpuDebuggerPath + _options.inputFilePath + std::to_string(sFileUniqueCounter++) + _options.shaderType + ".glslc");
				if (fopen_s(&glslcOutputFileHandle, glslcOutputFileName.c_str(), "wb") != 0)
				{
					BX_ASSERT(false, "Can't write file");
				}
				if (!glslcOutputFileHandle)
				{
					BX_ASSERT(false, "Can't write file");
				}

				fwrite(reinterpret_cast<const char*>(compileOutput), compileOutput->size, 1, glslcOutputFileHandle);
				fclose(glslcOutputFileHandle);
			}

			ShaderReflectionInfo reflectionInfo;

			for (uint32_t i = 0; i < compileOutput->numSections; ++i)
			{
				GLSLCsectionTypeEnum type = compileOutput->headers[i].genericHeader.common.type;

				if (type == GLSLC_SECTION_TYPE_REFLECTION)
				{
					void* data = ((char*)compileOutput) + (compileOutput->headers[i].genericHeader.common.dataOffset);

					const GLSLCprogramReflectionHeader* reflectionHeader = &(compileOutput->headers[i].programReflectionHeader);
					const char* stringPool = (const char*)data + reflectionHeader->stringPoolOffset;

					const GLSLCuniformBlockInfo* uniformBlock = (GLSLCuniformBlockInfo*)((char*)data + reflectionHeader->uniformBlockOffset);
					for (uint32_t j = 0; j < reflectionHeader->numUniformBlocks; ++j)
					{
						UniformBlockData uniformBlockData;

						for (uint32_t k = 0; k < 6; ++k)
							uniformBlockData.m_Bindings[k] = uniformBlock->bindings[k];

						uniformBlockData.m_Name = stringPool + uniformBlock->nameInfo.nameOffset;
						uniformBlockData.m_Size = uniformBlock->size;
						uniformBlockData.m_NumActiveVariables = uniformBlock->numActiveVariables;
						uniformBlockData.m_StagesReferencedIn = static_cast<uint8_t>(uniformBlock->stagesReferencedIn);

						reflectionInfo.m_UniformBlocks.push_back(uniformBlockData);

						++uniformBlock;
					}

					GLSLCuniformInfo* uniform = (GLSLCuniformInfo*)((char*)data + reflectionHeader->uniformOffset);
					for (uint32_t j = 0; j < reflectionHeader->numUniforms; ++j)
					{
						UniformData uniformData;

						uniformData.m_Name = stringPool + uniform->nameInfo.nameOffset;
						uniformData.m_Type = uniform->type;
						uniformData.m_BlockNdx = uniform->blockNdx;
						uniformData.m_BlockOffset = uniform->blockOffset;

						for (uint32_t k = 0; k < 6; ++k)
						{
							uniformData.m_Bindings[k] = uniform->bindings[k];
						}

						uniformData.m_IsArray = uniform->isArray;
						uniformData.m_SizeOfArray = uniform->sizeOfArray;
						uniformData.m_ArrayStride = uniform->arrayStride;
						uniformData.m_MatrixStride = uniform->matrixStride;
						uniformData.m_IsRowMajor = uniform->isRowMajor;
						uniformData.m_StagesReferencedIn = static_cast<uint8_t>(uniform->stagesReferencedIn);

						if (uniformData.m_BlockNdx != -1)
						{
							if (isSampler(uniform->type) || isImage(uniform->type))
							{
								printError("Samplers are expected to be declared as a global uniform, but this one is in a uniform block: " + uniformData.m_Name + "\n");
							}
							else
							{
								reflectionInfo.m_UniformBlocks[uniformData.m_BlockNdx].m_Uniforms.push_back(uniformData);
							}
						}
						else
						{
							if (isSampler(uniform->type) || isImage(uniform->type)) {
								reflectionInfo.m_GlobalUniforms.push_back(uniformData);
							}
							else {
								printError("All uniforms should've been in a uniform block, or should've been a global sampler, but this one isn't: " + uniformData.m_Name + "\n");
								return false;
							}
						}

						++uniform;
					}

					GLSLCprogramInputInfo* programInput = (GLSLCprogramInputInfo*)((char*)data + reflectionHeader->programInputsOffset);
					for (uint32_t j = 0; j < reflectionHeader->numProgramInputs; ++j)
					{
						VertexAttributeData vertexAttributeData;
						vertexAttributeData.m_Name = stringPool + programInput->nameInfo.nameOffset;
						vertexAttributeData.m_Type = programInput->type;
						vertexAttributeData.m_IsArray = programInput->isArray;
						vertexAttributeData.m_SizeOfArray = programInput->sizeOfArray;
						vertexAttributeData.m_Location = programInput->location;
						vertexAttributeData.m_IsPerPatch = programInput->isPerPatch;
						vertexAttributeData.m_StagesReferencedIn = static_cast<uint8_t>(programInput->stagesReferencedIn);

						if (vertexAttributeData.m_StagesReferencedIn & currentShaderStageBits) {
							reflectionInfo.m_VertexAttributes.push_back(vertexAttributeData);
						}

						++programInput;
					}
				}
			}

			if (reflectionInfo.m_UniformBlocks.size() > std::numeric_limits<uint8_t>::max())
			{
				printError("Didn't expect more than " + std::to_string(std::numeric_limits<uint8_t>::max()) + " uniform blocks, but found " + std::to_string(reflectionInfo.m_UniformBlocks.size()));
				return false;
			}

			std::vector<const UniformBlockData*> usedUniformBlocks;

			for (const UniformBlockData& uniformBlock : reflectionInfo.m_UniformBlocks)
			{
				uint32_t useBit = 0;
				useBit |= (uniformBlock.m_Bindings[NVNshaderStage::NVN_SHADER_STAGE_COMPUTE] != -1) ? NVNshaderStageBits::NVN_SHADER_STAGE_COMPUTE_BIT : 0;
				useBit |= (uniformBlock.m_Bindings[NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT] != -1) ? NVNshaderStageBits::NVN_SHADER_STAGE_FRAGMENT_BIT : 0;
				useBit |= (uniformBlock.m_Bindings[NVNshaderStage::NVN_SHADER_STAGE_VERTEX] != -1) ? NVNshaderStageBits::NVN_SHADER_STAGE_VERTEX_BIT : 0;

				bool isUsed = (currentShaderStageBits & useBit) > 0;
				if (!isUsed) {
					continue;
				}
				else
				{
					usedUniformBlocks.push_back(&uniformBlock);
				}
			}

			// ------- COMMON BGFX SECTION - has to contain all of the uniforms declared

			std::vector<std::reference_wrapper<const std::vector<UniformData>>> allUniforms;
			allUniforms.push_back(reflectionInfo.m_GlobalUniforms);
			for (const auto& block : usedUniformBlocks)
			{
				allUniforms.push_back(block->m_Uniforms);
			}

			writeUniforms(_options, _writer, allUniforms);

			// ------- PLATFORM SPECIFIC SECTION

			// Global Uniforms (aka, samplers)
			writeUniforms(_options, _writer, { reflectionInfo.m_GlobalUniforms });

			// UniformBuffer count
			bx::write(_writer, static_cast<uint8_t>(usedUniformBlocks.size()));

			for (const UniformBlockData* uniformBlockPtr : usedUniformBlocks)
			{
				const UniformBlockData& uniformBlock = *uniformBlockPtr;

				{
					uint8_t nameSize = (uint8_t)uniformBlock.m_Name.size();
					bx::write(_writer, nameSize);
					bx::write(_writer, uniformBlock.m_Name.c_str(), nameSize);
				}

				bx::write(_writer, (uint32_t)uniformBlock.m_Size);

				writeUniforms(_options, _writer, { uniformBlock.m_Uniforms });
			}

			// Stage Input
			bx::write(_writer, static_cast<uint32_t>(reflectionInfo.m_VertexAttributes.size()));

			for (const VertexAttributeData& attribute : reflectionInfo.m_VertexAttributes)
			{
				const bgfx::Attrib::Enum attType = toAttribEnum(attribute.m_Name.c_str());
				bx::write(_writer, static_cast<uint8_t>(attType));

				uint8_t nameSize = (uint8_t)attribute.m_Name.size();
				bx::write(_writer, nameSize);
				bx::write(_writer, attribute.m_Name.c_str(), nameSize);

				bx::write(_writer, (int32_t)attribute.m_Location);
			}

			// Actual shader code
			{
				bool alreadyHadCode = false;

				for (uint32_t i = 0; i < compileOutput->numSections; ++i)
				{
					GLSLCsectionTypeEnum type = compileOutput->headers[i].genericHeader.common.type;

					if (type == GLSLC_SECTION_TYPE_GPU_CODE)
					{
						if (alreadyHadCode)
						{
							printError("More than one gpu code section encountered. This wasn't expected");
							return false;
						}
						else
						{
							alreadyHadCode = true;
						}

						const GLSLCgpuCodeHeader* gpuHeader = &(compileOutput->headers[i].gpuCodeHeader);

						/*
						 * Grab a pointer to the data section of the header. The control offset and
						 * data offset from the gpu code header are offsets from this pointer.
						 */
						void* data = ((char*)compileOutput) + gpuHeader->common.dataOffset;

						if (gpuHeader->stage != currentShaderStage)
						{
							printError("Got a gpu shader code for stage " + std::to_string(gpuHeader->stage) + " but was expecting stage " + std::to_string(currentShaderStage));
							return false;
						}


						bx::write(_writer, uint32_t{ gpuHeader->controlSize });
						bx::write(_writer, uint32_t{ gpuHeader->dataSize });

						bx::write(_writer, ((char*)data + gpuHeader->controlOffset), gpuHeader->controlSize);
						bx::write(_writer, ((char*)data + gpuHeader->dataOffset), gpuHeader->dataSize);
					}
				}
			}

			return true;
		}
#endif

	} // namespace nvn

	bool compileNVNShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer)
	{
#if !defined(BGFX_NVN)
		BX_UNUSED(_options, _version, _code, _writer);
		bx::printf("NVN support disabled");
		return false;
#else
		GLSLCcompileObject compiler;
		if (!glslcInitialize(&compiler)) {
			bx::printf("failed to initialize glslcCompileObject");
			return false;
		}

		bool compiled = nvn::compile(compiler, _options, _code, _writer, true);

		glslcFinalize(&compiler);
		return compiled;
#endif

	}

} // namespace bgfx

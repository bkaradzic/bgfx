/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_GNM_H_HEADER_GUARD
#define BGFX_RENDERER_GNM_H_HEADER_GUARD

#ifdef __ORBIS__


#include <gnm/constants.h>
#include <gnm/dataformats.h>
#include <gnmx.h>
#include <gnmx/shader_parser.h>
#include "allocator_gnm.h"
#include <array>
#include <vector>
#include <memory>
#include <map>

namespace sce {
	namespace TextureTool {
		class Image;
		class MippedImage;
	}
}

namespace bgfx {
	namespace gnm {

		enum class EmbeddedShaderType {
			VertexShader,
			PixelShader,
			ComputeShader
		};

		sce::Gnm::ResourceHandle registerResource(const char* _name, sce::Gnm::ResourceType _resourceType, const void* _data, uint32_t _size);
		void unregisterResource(sce::Gnm::ResourceHandle _handle);

		// These embedded pixel shaders are only meant for clearing operations. Should never be used outside of this class.
		// Templatize to reduce duplicated code. xxShader can either be PsShader or CsShader
		template <class xxShader, EmbeddedShaderType embeddedShaderType>
		struct EmbeddedShaderWithSource {
			const uint32_t* m_source = nullptr;
			xxShader* m_xxShader = nullptr;
			sce::Gnmx::InputOffsetsCache m_offsetsTable;
			void* m_shaderBinaryAllocated = nullptr;
			void* m_shaderHeaderAllocated = nullptr;
			void* m_fetchShader = nullptr;
			uint32_t m_fetchShaderSize = 0;
			uint32_t m_fetchShaderModifier = 0;

			void initialize(GnmAllocator& garlicAllocator, GnmAllocator& onionAllocator, const char* debugName) {
				sce::Gnmx::ShaderInfo shaderInfo;
				sce::Gnmx::parseShader(&shaderInfo, m_source);

				m_shaderBinaryAllocated = garlicAllocator.allocate(shaderInfo.m_gpuShaderCodeSize, sce::Gnm::kAlignmentOfShaderInBytes, sce::Gnm::kResourceTypeFetchShaderBaseAddress, debugName);
				memcpy(m_shaderBinaryAllocated, shaderInfo.m_gpuShaderCode, shaderInfo.m_gpuShaderCodeSize);

				sce::Gnm::ShaderStage shaderStage;
				switch (embeddedShaderType) {
				case EmbeddedShaderType::VertexShader:
					shaderStage = sce::Gnm::kShaderStageVs;
					m_shaderHeaderAllocated = onionAllocator.allocate(shaderInfo.m_vsShader->computeSize(), sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeFetchShaderBaseAddress, debugName);
					memcpy(m_shaderHeaderAllocated, shaderInfo.m_vsShader, shaderInfo.m_vsShader->computeSize());
					m_fetchShaderSize = computeVsFetchShaderSize(shaderInfo.m_vsShader);
					break;

				case EmbeddedShaderType::PixelShader:
					shaderStage = sce::Gnm::kShaderStagePs;
					m_shaderHeaderAllocated = onionAllocator.allocate(shaderInfo.m_psShader->computeSize(), sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeFetchShaderBaseAddress, debugName);
					memcpy(m_shaderHeaderAllocated, shaderInfo.m_psShader, shaderInfo.m_psShader->computeSize());
					break;

				case EmbeddedShaderType::ComputeShader:
					shaderStage = sce::Gnm::kShaderStageCs;
					m_shaderHeaderAllocated = onionAllocator.allocate(shaderInfo.m_csShader->computeSize(), sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeFetchShaderBaseAddress, debugName);
					memcpy(m_shaderHeaderAllocated, shaderInfo.m_csShader, shaderInfo.m_csShader->computeSize());
					break;

				default:
					BX_ASSERT(false, "embeddedShaderType is unknown please handle it");
					break;
				}

				m_xxShader = static_cast<xxShader*>(m_shaderHeaderAllocated);
				m_xxShader->patchShaderGpuAddress(m_shaderBinaryAllocated);

				sce::Gnmx::generateInputOffsetsCache(&m_offsetsTable, shaderStage, m_xxShader);
			}

			void initializeFetchShader(GnmAllocator& garlicAllocator, const sce::Gnm::FetchShaderInstancingMode* fetchInstancingData = nullptr, int numElementsFetchInstancingData = 0) {
				if (embeddedShaderType == EmbeddedShaderType::VertexShader) {
					// Extra stuff for fetch shader - just for vertex shader. It's a special PS4 shader that fetches the vertex attributes.
					BX_ASSERT(m_fetchShaderSize > 0, "Please call initialize() before initializeFetchShader() m_fetchShaderSize should have been set by now.");
					m_fetchShader = garlicAllocator.allocate(m_fetchShaderSize, sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeFetchShaderBaseAddress, "vs shader fetch");
					BX_ASSERT(m_fetchShader != nullptr, "Failed to allocate memory for fetch shader for Vertex Shader");
					sce::Gnmx::generateVsFetchShader(m_fetchShader, &m_fetchShaderModifier, m_xxShader, fetchInstancingData, numElementsFetchInstancingData);
					m_xxShader->applyFetchShaderModifier(m_fetchShaderModifier);
				}
			}

			void shutdown(GnmAllocator& garlicAllocator, GnmAllocator& onionAllocator) {
				if (m_fetchShader) {
					garlicAllocator.release(m_fetchShader);
					m_fetchShader = nullptr;
				}

				if (m_shaderBinaryAllocated) {
					garlicAllocator.release(m_shaderBinaryAllocated);
					m_shaderBinaryAllocated = nullptr;
				}

				if (m_shaderHeaderAllocated) {
					onionAllocator.release(m_shaderHeaderAllocated);
					m_shaderHeaderAllocated = nullptr;
				}
			}
		};

		using EmbeddedPixelShaderWithSource = EmbeddedShaderWithSource<sce::Gnmx::PsShader, EmbeddedShaderType::PixelShader>;
		using EmbeddedVertexShaderWithSource = EmbeddedShaderWithSource<sce::Gnmx::VsShader, EmbeddedShaderType::VertexShader>;
		using EmbeddedComputeShaderWithSource = EmbeddedShaderWithSource<sce::Gnmx::CsShader, EmbeddedShaderType::ComputeShader>;

		struct ShaderGNM {
			ShaderGNM() = default;

			void create(const Memory* _mem);
			void destroy();

			uint16_t m_numUniforms = 0;
			uint8_t m_numPredefined = 0;
			uint8_t m_numAttributes = 0;

			PredefinedUniform m_predefined[PredefinedUniform::Count];

			UniformBuffer* m_constantBuffer = nullptr;

			size_t m_constantBufferSize = 0;

			uint16_t m_attrMask[Attrib::Count];

			std::array<int8_t, Attrib::Count> m_attributesSlot;

			EmbeddedPixelShaderWithSource* m_pixelShader = nullptr;
			EmbeddedVertexShaderWithSource* m_vertexShader = nullptr;

			std::string m_name;

		};

		struct ProgramGNM {
			ProgramGNM() = default;

			void create(const ShaderGNM* _vsh, const ShaderGNM* _fsh);

			void destroy();

			const ShaderGNM* m_vsh = nullptr;
			const ShaderGNM* m_fsh = nullptr;

			std::array<PredefinedUniform, PredefinedUniform::Count * 2> m_predefined;
			uint8_t m_numPredefined = 0;

			uint8_t m_numAttributes = 0;
			std::array<int8_t, Attrib::Count> m_attributesSlot;
		};

		struct TextureGNM {
			TextureGNM()
				: m_numMips(0)
				, m_created(false)
				, m_gpuMemory(nullptr)
				, m_gpuStencilMemory(nullptr)
				, m_BoundFrameBuffer(nullptr)
				, m_isExternal(false)
			{
				;
			}

			void* create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
			void* createAsTexture2D(const bimg::ImageContainer& _imageContainer, const sce::Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod);
			void* createAsCubeMap(const bimg::ImageContainer& _imageContainer, const sce::Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod);
			void* createAsTextureVolume(const bimg::ImageContainer& _imageContainer, const sce::Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod);
			void allocateTexture(const sce::Gnm::SizeAlign& sizeAlign);
			void destroy();
			void overrideInternal(uintptr_t _ptr, uint32_t _flags);
			void update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
			void commit(struct TextureStageGNM& ts, uint32_t _stage, uint32_t _flags, const float _palette[][4]);
			void resolve() const;
			void wrapExternal(sce::Gnm::Texture const& externalTexture, TextureRef& ref);
			sce::Gnm::TextureSpec textureSpecFromImageContainer(const bimg::ImageContainer& imageContainer, const uint8_t _skip, const uint8_t startLod, const bool isMsaaEnabled);
			void registerResource(const char* _name, sce::Gnm::ResourceType _resourceType);

			sce::Gnm::Texture m_internalTexture;
			GnmAllocator::Unique<uint8_t> m_gpuMemory;
			GnmAllocator::Unique<uint8_t> m_gpuStencilMemory;
			std::map<uint8_t, std::unique_ptr<sce::TextureTool::Image>> m_Mips;

			uint32_t m_flags;
			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_depth;
			uint8_t  m_type;
			uint8_t  m_requestedFormat;
			uint8_t  m_textureFormat;
			uint8_t  m_numMips;
			uint32_t m_size;
			sce::Gnm::ResourceHandle m_handle;
			std::string m_name = "";
			struct FrameBufferGNM* m_BoundFrameBuffer;
			bool m_created;
			bool m_isExternal;
		};


		struct GPUmem {
			void update(uint32_t _offset, uint32_t _size, void* _data);
			void destroy();

			GnmAllocator::Unique<uint8_t> m_gpuMemory;

			uint32_t m_size = 0;
			uint16_t m_flags = 0;

			void _create(uint32_t _size, uint32_t _align, const sce::Gnm::ResourceType _resourceType, const char* _name, void* _data, uint16_t _flags);
		};

		struct VertexBufferGNM : public GPUmem {
			VertexBufferGNM() = default;

			void create(uint32_t _size, void* _data, VertexLayoutHandle _declHandle, uint16_t _flags) {
				m_decl = _declHandle;

				_create(_size, sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeVertexBufferBaseAddress, "VertexBufferGNM", _data, _flags);
			}

			VertexLayoutHandle m_decl;
		};

		struct IndexBufferGNM : public GPUmem {
			IndexBufferGNM() = default;

			void create(uint32_t _size, void* _data, uint16_t _flags) {
				_create(_size, sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeIndexBufferBaseAddress, "IndexBufferGNM", _data, _flags);
			}
		};

		struct RenderTargetWithSliceInfo {
			sce::Gnm::RenderTarget m_renderTarget;
			uint32_t m_numSlices = 0;
		};


		struct RenderTargetGNM : public GPUmem {
			RenderTargetGNM() = default;

			RenderTargetWithSliceInfo m_rtsi;
			void create(const uint32_t _size, const uint32_t _align) {
				_create(_size, _align, sce::Gnm::kResourceTypeRenderTargetBaseAddress, "RenderTargetGNM", nullptr, 0);
			}
		};

		struct DepthRenderTargetGNM : public GPUmem {
			DepthRenderTargetGNM() = default;
			struct InternalBuffer : public GPUmem {
				void create(const uint32_t _size, const uint32_t _align, const sce::Gnm::ResourceType _type, const char* _name) {
					_create(_size, _align, _type, _name, nullptr, 0);
				}
			};

			sce::Gnm::DepthRenderTarget m_depthRenderTarget;
			InternalBuffer m_hTileBuffer;
			InternalBuffer m_stencilBuffer;

			void create(const uint32_t _size, const uint32_t _align, const bool _hTileEnabled, const sce::Gnm::StencilFormat _stencilFormat) {
				_create(_size, _align, sce::Gnm::kResourceTypeDepthRenderTargetBaseAddress, "DepthRenderTargetGNM", nullptr, 0);

				if (_hTileEnabled) {
					const auto sizeAlign = m_depthRenderTarget.getHtileSizeAlign();
					m_hTileBuffer.create(sizeAlign.m_size, sizeAlign.m_align, sce::Gnm::kResourceTypeDepthRenderTargetHTileAddress, "DepthRenderTarget HTile");
					m_depthRenderTarget.setHtileAddress(m_hTileBuffer.m_gpuMemory.get());
					m_depthRenderTarget.setHtileAccelerationEnable(true);
				}

				if (_stencilFormat != sce::Gnm::kStencilInvalid) {
					const auto sizeAlign = m_depthRenderTarget.getStencilSizeAlign();
					m_stencilBuffer.create(sizeAlign.m_size, sizeAlign.m_align, sce::Gnm::kResourceTypeDepthRenderTargetStencilAddress, "DepthRenderTarget Stencil");
				}
				m_depthRenderTarget.setAddresses(m_gpuMemory.get(), m_stencilBuffer.m_gpuMemory.get());
			}
		};


		struct BufferGNM {
			BufferGNM()
				: m_size(0)
				, m_flags(BGFX_BUFFER_NONE)
				, m_stride(0)
				, m_numElements(0)
				, m_gpuBufferIndex(0)
			{
			}

			void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
			void update(uint32_t _offset, uint32_t _size, void* _data);
			void destroy();

			GPUmem m_ptr[2];
			sce::Gnm::Buffer m_buffer[2];

			uint32_t m_gpuBufferIndex;
			uint32_t m_size;
			uint32_t m_stride;
			uint32_t m_numElements;
			uint16_t m_flags;
		};

		struct ShaderBufferGNM : public BufferGNM {
			ShaderBufferGNM() = default;
		};

		struct DisplayBuffer
		{
			RenderTargetWithSliceInfo m_rtsi;
			int m_displayIndex = 0;
			GnmAllocator::Unique<uint8_t> m_gpuBuffer;
			GnmAllocator::Unique<uint8_t> m_cmaskBuffer;
			GnmAllocator::Unique<uint8_t> m_fmaskBuffer;

			void destroy() {
				m_rtsi.m_renderTarget.setAddresses(nullptr, nullptr, nullptr);
				m_cmaskBuffer = nullptr;
				m_fmaskBuffer = nullptr;
				m_gpuBuffer = nullptr;
			}
		};

		struct FrameBufferGNM {
			FrameBufferGNM()
				: m_width(0)
				, m_height(0)
				, m_num(0)
				, m_numTh(0)
				, m_numSlicesDepth(0)
				, m_needPresent(false)
				, m_haveDepthAttachment(false)
				, m_frameBufferMSAA(false)
			{
			}

			enum class ResourceTransition {
				TargetToTexture,
				TextureToTarget
			};

			void create(uint8_t _num, const Attachment* _attachment);
			void destroy();
			void preReset(bool _force = false);
			void postReset();
			void resolve();
			void clear(const Clear& _clear, const Rect* _prect, const float _palette[][4]);
			void transitionTo(ResourceTransition transition);
			void set();
			void updateTextureBindings();
			void _initMsaaRenderTargetFromTexture(const sce::Gnm::DataFormat& colorFormat, DisplayBuffer& msaaRenderTarget, const gnm::TextureGNM& texture, uint32_t slot);
			void _drawTexture(sce::Gnm::RenderTarget& renderTarget, const sce::Gnm::Texture& texture, uint32_t slot);

			uint32_t m_width;
			uint32_t m_height;
			uint8_t  m_num;
			uint8_t  m_numTh;
			bool	 m_haveDepthAttachment;
			bool     m_needPresent;
			bool	 m_frameBufferMSAA;
			uint32_t m_mask;

			RenderTargetGNM m_renderTargets[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			DisplayBuffer m_intermediateRenderTargets[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			sce::Gnmx::ResourceBarrier m_resourceBarriers[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			sce::Gnm::DepthRenderTarget m_depthRenderTarget; // there can be only one ...
			uint32_t m_numSlicesDepth;
			Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		};

		template<typename Ty>
		class StateCacheT {
		public:

			Ty* add(uint64_t _key, Ty&& _value) {
				invalidate(_key);
				auto iter = m_hashMap.insert(stl::make_pair(_key, std::move(_value)));
				return &(*iter.first).second;
			}
			Ty* add(uint64_t _key, const Ty& _value) {
				invalidate(_key);
				auto iter = m_hashMap.insert(stl::make_pair(_key, _value));
				return &(*iter.first).second;
			}


			Ty find(uint64_t _key) {
				typename HashMap::iterator it = m_hashMap.find(_key);
				if (it != m_hashMap.end()) {
					return it->second;
				}

				return 0;
			}

			void invalidate(uint64_t _key) {
				typename HashMap::iterator it = m_hashMap.find(_key);
				if (it != m_hashMap.end()) {
					vkDestroy(it->second);
					m_hashMap.erase(it);
				}
			}

			void invalidate() {
				for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it) {
					vkDestroy(it->second);
				}

				m_hashMap.clear();
			}

			uint32_t getCount() const {
				return uint32_t(m_hashMap.size());
			}

		private:
			typedef stl::unordered_map<uint64_t, Ty> HashMap;
			HashMap m_hashMap;
		};

		template<>
		class StateCacheT<sce::Gnm::Sampler> {
		public:

			sce::Gnm::Sampler* add(uint64_t _key, sce::Gnm::Sampler&& _value) {
				invalidate(_key);
				auto iter = m_hashMap.insert(stl::make_pair(_key, std::move(_value)));
				return &(*iter.first).second;
			}
			sce::Gnm::Sampler* add(uint64_t _key, const sce::Gnm::Sampler& _value) {
				invalidate(_key);
				auto iter = m_hashMap.insert(stl::make_pair(_key, _value));
				return &(*iter.first).second;
			}

			sce::Gnm::Sampler* find(uint64_t _key) {
				typename HashMap::iterator it = m_hashMap.find(_key);
				if (it != m_hashMap.end()) {
					return &it->second;
				}

				return nullptr;
			}

			void invalidate(uint64_t _key) {
				typename HashMap::iterator it = m_hashMap.find(_key);
				if (it != m_hashMap.end()) {
					m_hashMap.erase(it);
				}
			}

			void invalidate() {
				m_hashMap.clear();
			}

			uint32_t getCount() const {
				return uint32_t(m_hashMap.size());
			}

		private:
			typedef stl::unordered_map<uint64_t, sce::Gnm::Sampler> HashMap;
			HashMap m_hashMap;
		};

		struct BorderColorTableGNM {
			void init();
			void shutdown();
			float* getFloat4FromIndex(uint32_t index);
			uint32_t getIndexFromColor(const float* color);
			// Max Table size based on Specification
			static constexpr uint32_t mMaxTableSize = 4096;
			static constexpr uint32_t kTableAlignment = 256;
			static constexpr uint32_t kFloatPerColor = 4;
			stl::unordered_map<uint32_t, uint32_t> mColorToIndexMap;
			float* mColorTable = nullptr;
			uint32_t mCurrentIndex = 0;
		};

	}
} //namespace gnm //namespace bgfx

#endif // __ORBIS__

#endif // !BGFX_RENDERER_GNM_H_HEADER_GUARD

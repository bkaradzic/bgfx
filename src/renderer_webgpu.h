/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_WEBGPU_H_HEADER_GUARD
#define BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_WEBGPU

#if !BX_PLATFORM_EMSCRIPTEN
#	include <dawn/webgpu_cpp.h>
#	include <dawn/dawn_wsi.h>
#else
#	include <webgpu/webgpu_cpp.h>
#endif // !BX_PLATFORM_EMSCRIPTEN

#define BGFX_WEBGPU_PROFILER_BEGIN(_view, _abgr)      \
	BX_MACRO_BLOCK_BEGIN                              \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr); \
	BX_MACRO_BLOCK_END

#define BGFX_WEBGPU_PROFILER_BEGIN_LITERAL(_name, _abgr) \
	BX_MACRO_BLOCK_BEGIN                                 \
		BGFX_PROFILER_BEGIN_LITERAL("" # _name, _abgr);  \
	BX_MACRO_BLOCK_END

#define BGFX_WEBGPU_PROFILER_END() \
	BX_MACRO_BLOCK_BEGIN           \
		BGFX_PROFILER_END();       \
	BX_MACRO_BLOCK_END

#define WEBGPU_NUM_UNIFORM_BUFFERS  8

namespace bgfx { namespace webgpu
{
	template <typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _id, Ty _item)
		{
			invalidate(_id);
			m_hashMap.insert(stl::make_pair(_id, _item));
		}

		Ty find(uint64_t _id)
		{
			typename HashMap::iterator it = m_hashMap.find(_id);
			if(it != m_hashMap.end())
			{
				return it->second;
			}

			return NULL;
		}

		void invalidate(uint64_t _id)
		{
			typename HashMap::iterator it = m_hashMap.find(_id);
			if(it != m_hashMap.end())
			{
				release(it->second);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for(typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				release(it->second);
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size());
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty> HashMap;
		HashMap m_hashMap;
	};

	struct BufferWgpu
	{
		void create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride = 0, bool _vertex = false);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			m_ptr.Destroy();

			if(NULL != m_dynamic)
			{
				BX_DELETE(g_allocator, m_dynamic);
				m_dynamic = NULL;
			}
		}

		uint32_t m_size;
		uint16_t m_flags = BGFX_BUFFER_NONE;
		bool     m_vertex;

		String       m_label;
		wgpu::Buffer m_ptr;
		uint8_t*     m_dynamic = NULL;
	};

	struct IndexBufferWgpu : public BufferWgpu
	{
		void create(uint32_t _size, void* _data, uint16_t _flags);

		wgpu::IndexFormat m_format;
	};

	struct VertexBufferWgpu : public BufferWgpu
	{
		void create(uint32_t _size, void* _data, VertexLayoutHandle _declHandle, uint16_t _flags);

		VertexLayoutHandle m_layoutHandle;
	};

	struct BindInfo
	{
		uint32_t      m_index = UINT32_MAX;
		uint32_t      m_binding = UINT32_MAX;
		UniformHandle m_uniform = BGFX_INVALID_HANDLE;
	};

	struct ShaderWgpu
	{
		void create(ShaderHandle _handle, const Memory* _mem);
		void destroy()
		{
			if (NULL != m_constantBuffer)
			{
				UniformBuffer::destroy(m_constantBuffer);
				m_constantBuffer = NULL;
			}

			m_module = NULL;
		}

		const char* name() const { return getName(m_handle); }

		ShaderHandle m_handle;
		String m_label;

		wgpu::ShaderStage m_stage;
		wgpu::ShaderModule m_module;

		uint32_t* m_code = NULL;
		size_t m_codeSize = 0;

		UniformBuffer* m_constantBuffer = NULL;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];
		uint8_t  m_attrRemap[Attrib::Count];

		uint32_t m_hash = 0;
		uint16_t m_numUniforms = 0;
		uint16_t m_size = 0;
		uint16_t m_gpuSize = 0;
		uint8_t  m_numPredefined = 0;
		uint8_t  m_numAttrs = 0;

		BindInfo                   m_bindInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		wgpu::BindGroupLayoutEntry m_samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		wgpu::BindGroupLayoutEntry m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint8_t                    m_numSamplers = 0;
		wgpu::BindGroupLayoutEntry m_buffers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint32_t                   m_numBuffers = 0;
	};

	struct PipelineStateWgpu;

	struct ProgramWgpu
	{
		void create(const ShaderWgpu* _vsh, const ShaderWgpu* _fsh);
		void destroy();

		const ShaderWgpu* m_vsh = NULL;
		const ShaderWgpu* m_fsh = NULL;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;

		PipelineStateWgpu* m_computePS = NULL;

		wgpu::BindGroupLayout m_bindGroupLayout;
		uint16_t              m_gpuSize = 0;
		uint32_t              m_numUniforms;
		uint32_t              m_bindGroupLayoutHash;

		BindInfo                   m_bindInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		wgpu::BindGroupLayoutEntry m_samplers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		wgpu::BindGroupLayoutEntry m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint32_t                   m_numSamplers = 0;
		wgpu::BindGroupLayoutEntry m_buffers[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint32_t                   m_numBuffers = 0;
	};

	constexpr size_t kMaxVertexInputs = 16;
	constexpr size_t kMaxVertexAttributes = 16;
	constexpr size_t kMaxColorAttachments = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;

	constexpr uint32_t kMinBufferOffsetAlignment = 256;

	struct RenderPassDescriptor
	{
		RenderPassDescriptor();

		wgpu::RenderPassDescriptor desc;

		wgpu::RenderPassColorAttachment colorAttachments[kMaxColorAttachments];
		wgpu::RenderPassDepthStencilAttachment depthStencilAttachment;
	};

	struct VertexStateDescriptor
	{
		VertexStateDescriptor();

		wgpu::VertexState desc;

		wgpu::VertexBufferLayoutDescriptor buffers[kMaxVertexInputs];
		wgpu::VertexAttributeDescriptor attributes[kMaxVertexAttributes];
	};

	struct RenderPipelineDescriptor
	{
		RenderPipelineDescriptor();

		wgpu::RenderPipelineDescriptor2 desc;

		wgpu::FragmentState fragment;
		wgpu::DepthStencilState depthStencil;

		wgpu::ColorTargetState targets[kMaxColorAttachments];
		wgpu::BlendState blends[kMaxColorAttachments];
	};

	struct BindingsWgpu
	{
		uint32_t numEntries = 0;
		wgpu::BindGroupEntry m_entries[2 + BGFX_CONFIG_MAX_TEXTURE_SAMPLERS*3];
	};

	struct BindStateWgpu
	{
		void clear();

		uint32_t numOffset;

		wgpu::BindGroup m_bindGroup;
	};

	struct RenderPassStateWgpu
	{
		RenderPassDescriptor m_rpd;
	};

	struct PipelineStateWgpu
	{
		RenderPipelineDescriptor m_rpd;

		wgpu::PipelineLayout m_layout;

		wgpu::RenderPipeline m_rps;
		wgpu::ComputePipeline m_cps;
	};

	void release(RenderPassStateWgpu* _ptr)
	{
		BX_DELETE(g_allocator, _ptr);
	}

	void release(PipelineStateWgpu* _ptr)
	{
		BX_DELETE(g_allocator, _ptr);
	}

	class StagingBufferWgpu
	{
	public:
		void create(uint32_t _size, bool mapped);
		void map();
		void unmap();
		void destroy();

		void mapped(void* _data);

		wgpu::Buffer m_buffer;
		void* m_data = NULL;
		uint64_t m_size = 0;
	};

	class ScratchBufferWgpu
	{
	public:
		void create(uint32_t _size); // , uint32_t _maxBindGroups);
		void destroy();
		void begin();
		uint32_t write(void* data, uint64_t _size, uint64_t _offset);
		uint32_t write(void* data, uint64_t _size);
		void submit();
		void release();

		StagingBufferWgpu* m_staging = NULL;
		wgpu::Buffer m_buffer;
		uint32_t m_offset;
		uint32_t m_size;
		uint8_t m_stagingIndex = 0;
	};

	class BindStateCacheWgpu
	{
	public:
		void create(); // , uint32_t _maxBindGroups);
		void destroy();
		void reset();

		BindStateWgpu m_bindStates[1024] = {};
		uint32_t m_currentBindState;
		//uint32_t m_maxBindStates;
	};

	struct ReadbackWgpu
	{
		void create(TextureHandle _texture) { m_texture = _texture; }

		void destroy()
		{
			m_buffer.Destroy();
		}

		void readback(void const* data)
		{
			bx::memCopy(m_data, data, m_size);
			m_buffer.Unmap();
			m_mapped = false;
		}

		TextureHandle m_texture;
		wgpu::Buffer m_buffer;
		uint32_t m_mip = 0;
		bool m_mapped = false;
		void* m_data = NULL;
		size_t m_size = 0;
	};

	struct TextureWgpu
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		void create(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip);

		void destroy()
		{
			m_ptr.Destroy();
		}

		void update(
			uint8_t _side
			, uint8_t _mip
			, const Rect& _rect
			, uint16_t _z
			, uint16_t _depth
			, uint16_t _pitch
			, const Memory* _mem
		);

		TextureHandle m_handle;
		String m_label;

		wgpu::TextureView m_view;
		wgpu::TextureView getTextureMipLevel(int _mip);

		wgpu::Texture m_ptr;
		wgpu::Texture m_ptrMsaa;
		wgpu::TextureView m_ptrMips[14] = {};
		wgpu::Sampler m_sampler;
		uint64_t m_flags = 0;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t m_depth = 0;
		uint8_t m_type;
		TextureFormat::Enum m_requestedFormat;
		TextureFormat::Enum m_textureFormat;
		uint8_t m_numMips = 0;
		uint8_t m_numLayers;
		uint32_t m_numSides;
		uint8_t m_sampleCount;

		ReadbackWgpu m_readback;
	};

	struct SamplerStateWgpu
	{
		wgpu::Sampler m_sampler;
	};

	void release(SamplerStateWgpu* _ptr)
	{
		BX_DELETE(g_allocator, _ptr);
	}

	struct FrameBufferWgpu;

	struct SwapChainWgpu
	{
		void init(wgpu::Device _device, void* _nwh, uint32_t _width, uint32_t _height);
		void resize(FrameBufferWgpu& _frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags);

		void flip();

		wgpu::TextureView current();

#if !BX_PLATFORM_EMSCRIPTEN
		DawnSwapChainImplementation m_impl;
#endif

		wgpu::SwapChain m_swapChain;

		wgpu::TextureView m_drawable;

		wgpu::Texture m_backBufferColorMsaa;
		wgpu::Texture m_backBufferDepth;

		wgpu::TextureFormat m_colorFormat;
		wgpu::TextureFormat m_depthFormat;

		uint32_t m_maxAnisotropy = 0;
		uint8_t m_sampleCount;
	};

	struct FrameBufferWgpu
	{
		void create(uint8_t _num, const Attachment* _attachment);
		bool create(
				uint16_t _denseIdx
			, void* _nwh
			, uint32_t _width
			, uint32_t _height
			, TextureFormat::Enum _format
			, TextureFormat::Enum _depthFormat
			);
		void postReset();
		uint16_t destroy();

		SwapChainWgpu* m_swapChain = NULL;
		void* m_nwh = NULL;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx = UINT16_MAX;

		uint32_t m_pixelFormatHash = 0;

		TextureHandle m_colorHandle[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS - 1];
		TextureHandle m_depthHandle = { kInvalidHandle };
		Attachment m_colorAttachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS - 1];
		Attachment m_depthAttachment;
		uint8_t m_num = 0; // number of color handles
	};

	struct CommandQueueWgpu
	{
		void init(wgpu::Queue _queue);
		void shutdown();
		void beginRender();
		void beginStaging();
		void kick(bool _endFrame, bool _waitForFinish = false);
		void finish(bool _finishAll = false);
		void release(wgpu::Buffer _buffer);
		void consume();

#if BGFX_CONFIG_MULTITHREADED
		//bx::Semaphore 		 m_framesSemaphore;
#endif

		wgpu::Queue		     m_queue;
		wgpu::CommandEncoder m_stagingEncoder;
		wgpu::CommandEncoder m_renderEncoder;

		int m_releaseWriteIndex = 0;
		int m_releaseReadIndex = 0;

		typedef stl::vector<wgpu::Buffer> ResourceArray;
		ResourceArray m_release[BGFX_CONFIG_MAX_FRAME_LATENCY];
	};

	struct TimerQueryWgpu
	{
		TimerQueryWgpu()
			: m_control(4)
		{
		}

		void init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx);
		void end(uint32_t _idx);
		void addHandlers(wgpu::CommandBuffer& _commandBuffer);
		bool get();

		struct Result
		{
			void reset()
			{
				m_begin = 0;
				m_end = 0;
				m_pending = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
		};

		uint64_t m_begin;
		uint64_t m_end;
		uint64_t m_elapsed;
		uint64_t m_frequency;

		Result m_result[4 * 2];
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryWgpu
	{
		OcclusionQueryWgpu()
			: m_control(BX_COUNTOF(m_query))
		{
		}

		void postReset();
		void preReset();
		void begin(wgpu::RenderPassEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle);
		void end(wgpu::RenderPassEncoder& _rce);
		void resolve(Frame* _render, bool _wait = false);
		void invalidate(OcclusionQueryHandle _handle);

		struct Query
		{
			OcclusionQueryHandle m_handle;
		};

		wgpu::Buffer m_buffer;
		Query m_query[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		bx::RingBufferControl m_control;
	};

} /* namespace webgpu */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU

#endif // BGFX_RENDERER_WEBGPU_H_HEADER_GUARD

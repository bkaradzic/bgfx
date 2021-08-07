/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_NVN_RESOURCES_H_HEADER_GUARD
#define BGFX_NVN_RESOURCES_H_HEADER_GUARD

#include "memory.h"

#define BGFX_NVN_UNIFORMLOCATION_REGISTERMASK 0xFFFF
#define BGFX_NVN_UNIFORMLOCATION_INDEX_MASK 0xFFFF0000
#define BGFX_NVN_UNIFORMLOCATION_INDEX_SHIFT (16)

namespace bgfx { namespace nvn
{
	struct CopyOperation
	{
		struct Data
		{
			uint32_t m_size;
			void* m_mem;
			NVNmemoryPool m_pool;
			NVNbuffer m_buffer;
		};

		struct Op
		{
			uint32_t m_offset;
			uint32_t m_memSize;
			NVNtextureView m_dstView;
			NVNcopyRegion m_dstRegion;
			NVNtexture* m_dstData;
		};

		void createBuffer(size_t _size, CopyOperation::Data* _data);

		Data* m_data;
		std::vector<Op> m_ops;
	};

	template<typename T>
	class DoubleBufferedResource
	{
	public:
		DoubleBufferedResource() = default;
		~DoubleBufferedResource() = default;

		template<typename... TArgs>
		void init(TArgs&&... args)
		{
			for (auto& resource : m_Resources)
			{
				resource.init(std::forward<TArgs>(args)...);
			}
		}

		void shutdown()
		{
			for (auto& resource : m_Resources)
			{
				resource.shutdown();
			}
		}

		void swap()
		{
			m_Current = 1 - m_Current;
			get().reset();
		}

		T& get()
		{
			return m_Resources[m_Current];
		}
	private:
		std::array<T, 2> m_Resources;
		uint8_t m_Current = 0;
	};

	struct TextureNVN
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureNVN()
			: m_numMips(0)
			, m_created(false)
		{
		}

		void create(NVNdevice* _device, const Memory* _mem, uint32_t _flags, uint8_t _skip, CopyOperation& _copyOp);
		void create(NVNdevice* _device, NVNtextureBuilder& _builder);
		void destroy();
		void update(NVNcommandBuffer* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);

		bool m_created;

		int m_handle = -1;

		NVNtexture m_ptr;
		uint32_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_type;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
		uint8_t m_numMips;
		MemoryPool m_pool;
	};

	struct SamplerNVN
	{
		void create(int index, const NVNsamplerBuilder& _desc);
		void destroy();

		NVNsamplerBuilder m_desc;

		bool m_created = false;
		NVNsampler m_sampler;
		int m_index = -1;
	};

	struct BackBuffer
	{
		TextureNVN* m_Color = nullptr;
		TextureNVN* m_Depth = nullptr;
	};

	struct SwapChainNVN
	{
		static constexpr uint8_t TextureCount = 2;

		void create(NVNnativeWindow _nativeWindow, NVNdevice* _device, const bgfx::Resolution& _size, const bgfx::TextureFormat::Enum _colorFormat, const bgfx::TextureFormat::Enum _depthFormat);
		void destroy();
		void present(NVNqueue* _queue);

		BackBuffer acquireNext();
		BackBuffer get();

		std::array<TextureNVN, TextureCount> m_ColorTextures;
		std::array<TextureNVN, TextureCount> m_DepthTextures;

		NVNwindow m_Window;
		bool m_Created = false;
		NVNsync m_WindowSync;
		int m_Current = 0;
	};

	struct CommandListNVN
	{
	public:
		std::array<NVNtexture*, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> m_CurrentColor = {};
		NVNtexture* m_CurrentDepth = nullptr;
		NVNdrawPrimitive m_PrimitiveTopology = NVNdrawPrimitive::NVN_DRAW_PRIMITIVE_TRIANGLES;
		//ProgramNVN* m_CurrentProgram = nullptr;

		//const IndexBufferNVN* m_CurrentIndexBuffer = nullptr;
		NVNbufferAddress m_CurrentIndexBufferAddress = 0;
		NVNindexType m_CurrentIndexBufferIndexType = NVNindexType::NVN_INDEX_TYPE_UNSIGNED_SHORT;

		//std::array<PipelineVboBindPoint, PipelineVboBindPoint::MaxBindPoints> m_VboBindings;
		//std::array<UniformScratchMemory, BGFX_NVN_MAXUNIFORMBUFFER> m_UniformScratch;

		void init(NVNdevice* _device);
		void shutdown();

		void begin(const char* name);
		void submit(NVNqueue* queue, NVNsync* fence);

		NVNcommandBuffer* get();

	private:
		NVNcommandBuffer m_cmd;

		NVNcommandHandle _end();
		void _resetState();
	};

	struct CommandQueueNVN
	{
		CommandQueueNVN();

		void init(NVNdevice* _device, SwapChainNVN* _swapChain);
		void shutdown();
		CommandListNVN* alloc(CommandMemoryPool& commandMemoryPool, const char* name);
		NVNsync* kick();
		bool waitIsFenceSignaled(NVNsync* _waitFence, const uint64_t _ms = NVN_WAIT_TIMEOUT_MAXIMUM);
		void finish(NVNsync* _waitFence = nullptr, bool _finishAll = false);
		void waitForIdle();
		void flush();
		bool consume(const uint64_t _ms = NVN_WAIT_TIMEOUT_MAXIMUM);

		/*struct CommandList
		{
			ID3D12GraphicsCommandList* m_commandList;
			ID3D12CommandAllocator* m_commandAllocator;
			HANDLE m_event;
		};*/

		static constexpr size_t CommandListCount = 256;

		NVNdevice* m_Device = nullptr;
		SwapChainNVN* m_SwapChain = nullptr;

		NVNqueue m_GfxQueue;

		std::array<CommandListNVN, CommandListCount> m_commandList;
		std::array<NVNsync, CommandListCount> m_fences;
		bx::RingBufferControl m_control;

		NVNsync m_idleSync;
		/*uint64_t m_currentFence;
		uint64_t m_completedFence;
		ID3D12Fence* m_fence;
		typedef stl::vector<ID3D12Resource*> ResourceArray;
		ResourceArray m_release[256];
		*/
	};

	struct ShaderUniformBuffer
	{
		struct UniformReference
		{
			uint8_t m_predefined = PredefinedUniform::Enum::Count;
			UniformHandle m_handle = { kInvalidHandle };
			void* m_data = nullptr;
			uint16_t m_index = 0;
			uint16_t m_count = 0;
		};

		static uint32_t computeHash(const std::vector<UniformReference>& _uniforms);

		void create(uint32_t _size, std::vector<UniformReference>&& _uniforms);
		void destroy();

		void update(NVNcommandBuffer* _cmdBuf);

		uint32_t m_size = 0;
		uint8_t* m_data; // cpu side interim data
		BufferNVN* m_buffer; // actual gpu buffer
		NVNbufferAddress m_gpuAddress;
		std::vector<UniformReference> m_uniforms;
	};

	struct UniformBufferRegistry
	{
		struct Entry
		{
			uint32_t m_hash;
			ShaderUniformBuffer m_buffer;
		};

		static constexpr uint32_t InvalidEntry = ~0;

		void destroy();

		uint32_t find(const uint32_t _hash) const;
		uint32_t add(const uint32_t _hash, ShaderUniformBuffer&& _buf);
		ShaderUniformBuffer& get(const uint32_t _index);

		std::vector<Entry> m_buffers;
	};

	struct ShaderNVN
	{
		ShaderNVN()
			: m_code(NULL)
			, m_hash(0)
			, m_numUniforms(0)
			, m_numPredefined(0)
			, m_stage(NVNshaderStage::NVN_SHADER_STAGE_LARGE)
		{
		}

		void create(NVNdevice* _device, const Memory* _mem, UniformRegistry& _uniformRegistry, UniformBufferRegistry& _uniformBuffers);

		void destroy()
		{
			m_constantBuffers.clear();

			m_numPredefined = 0;
			m_control.clear();

			//m_shader.Finalize( &g_Device );

			if (NULL != m_code)
			{
				release(m_code);
				m_code = NULL;
				m_hash = 0;
			}

			m_codeMemoryPool.Shutdown();
		}

		NVNshaderData m_shader;
		NVNshaderStage m_stage;
		NVNbuffer m_codeBuffer;

		uint8_t* m_code = nullptr;
		std::vector<uint8_t> m_control;

		size_t m_codeSize = 0;
		MemoryPool m_codeMemoryPool;

		std::vector<uint32_t> m_constantBuffers;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];
		uint8_t m_attrRemap[Attrib::Count];

		uint32_t m_hash = 0;

		uint16_t m_numUniforms = 0;
		uint8_t m_numPredefined = 0;
		uint8_t m_numAttrs = 0;

		uint16_t m_size = 0;
	};

	struct ProgramNVN
	{
		ProgramNVN()
		{
		}

		void create(NVNdevice* _device, const ShaderNVN* _vsh, const ShaderNVN* _fsh);

		void destroy()
		{
			nvnProgramFinalize(&m_program);
		}

		const ShaderNVN* m_vsh;
		const ShaderNVN* m_fsh;

		int m_Stages = 0;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;

		NVNprogram m_program;
	};

	struct VertexLayoutNVN
	{
		void create(const VertexLayout& _vertexLayout);

		std::vector<NVNvertexAttribState> m_attribStates;
	};

	struct VertexBufferNVN : public BufferNVN
	{
		VertexBufferNVN()
			: BufferNVN()
		{
		}

		void create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags);

		VertexLayoutHandle m_layoutHandle;
	};
} }

#endif // BGFX_NVN_RESOURCES_H_HEADER_GUARD

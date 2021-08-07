/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "renderer_nvn.h"
#include "renderer_nvn/resources.h"

#include <nn/nn_Log.h>

#if BX_PLATFORM_NX
extern "C"
{
	PFNNVNGENERICFUNCPTRPROC NVNAPIENTRY nvnBootstrapLoader(const char* name);
}
#endif

namespace bgfx { namespace nvn
{
	//
	//
	//

	NVNdevice* g_nvnDevice = NULL;

	struct ContextResources
	{
		TextureNVN m_textures[BGFX_CONFIG_MAX_TEXTURES];
		BufferNVN m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferNVN m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		ShaderNVN m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramNVN m_program[BGFX_CONFIG_MAX_PROGRAMS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		uint8_t m_uniformsPredefinedVS[64 << 10];
		uint8_t m_uniformsPredefinedFS[64 << 10];
		UniformRegistry m_uniformReg;
		UniformBufferRegistry m_uniformBuffers;

		ContextResources()
		{
			memset(m_uniforms, 0, sizeof(m_uniforms));
		}
	};

	struct Commands
	{
		struct CurrentState
		{
			uint16_t view = UINT16_MAX;
			uint16_t programIndex = kInvalidHandle;
			bool isCompute = false;
			bool wasCompute = false;
			uint16_t frameBuffer = kInvalidHandle;
			ViewState viewState;
			Rect scissor;
			float depthNear = 0.f;
			float depthFar = 0.f;

			CurrentState(Frame* _render)
				: viewState(_render)
			{
			}
		};

		CommandListNVN& m_cmdList;
		ContextResources& m_resources;
		CurrentState m_state;

		Commands(CommandListNVN& cmd, Frame* _render, ContextResources& resources)
			: m_cmdList(cmd)
			, m_state(_render)
			, m_resources(resources)
		{
		}

		void setFrameBuffer(uint16_t _count, NVNtexture** _colors, NVNtexture* _depth)
		{
			for (uint16_t i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++i)
			{
				m_cmdList.m_CurrentColor[i] = (i < _count) ? _colors[i] : nullptr;
			}

			m_cmdList.m_CurrentDepth = _depth;

			nvnCommandBufferSetRenderTargets(m_cmdList.get(), BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, m_cmdList.m_CurrentColor.data(), NULL, m_cmdList.m_CurrentDepth, NULL);
		}

		bool setView(Frame* _render, uint16_t _view, bool _force, BackBuffer& _backBuffer)
		{
			bool changed = false;

			if (m_state.view != _view || _force)
			{
				FrameBufferHandle fbh = _render->m_view[_view].m_fbh;

				if (fbh.idx != m_state.frameBuffer)
				{
					m_state.frameBuffer = fbh.idx;

					//if (!isValid(fbh))
					{
						std::array<NVNtexture*, 1> target = { &_backBuffer.m_Color->m_ptr };
						setFrameBuffer(1, target.data(), &_backBuffer.m_Depth->m_ptr);
					}
					//else
					//{
					//}
				}

				m_state.view = _view;

				changed = true;
			}

			return changed;
		}

		void setViewport(const Rect& _vp, const Rect& _scissor, float _near, float _far)
		{
			if (memcmp(&m_state.viewState.m_rect, &_vp, sizeof(Rect)) != 0)
			{
				m_state.viewState.m_rect = _vp;
				nvnCommandBufferSetViewport(m_cmdList.get(), _vp.m_x, _vp.m_y, _vp.m_width, _vp.m_height);
			}

			Rect scissor = _scissor.isZeroArea() ? _vp : _scissor;
			if (memcmp(&m_state.scissor, &scissor, sizeof(Rect)) != 0)
			{
				m_state.scissor = scissor;
				nvnCommandBufferSetScissor(m_cmdList.get(), scissor.m_x, scissor.m_y, scissor.m_width, scissor.m_height);
			}

			if (m_state.depthNear != _near || m_state.depthFar != _far)
			{
				m_state.depthNear = _near;
				m_state.depthFar = _far;
				nvnCommandBufferSetDepthRange(m_cmdList.get(), _near, _far);
			}
		}

		void clearViewport(const Clear& _clear, const float _palette[][4])
		{
			if (BGFX_CLEAR_NONE != (_clear.m_flags & BGFX_CLEAR_MASK))
			{
				if (_clear.m_flags & BGFX_CLEAR_COLOR)
				{
					float rgba[4] =
					{
						_clear.m_index[0] * 1.0f / 255.0f,
						_clear.m_index[1] * 1.0f / 255.0f,
						_clear.m_index[2] * 1.0f / 255.0f,
						_clear.m_index[3] * 1.0f / 255.0f
					};

					for (int i = 0; i < m_cmdList.m_CurrentColor.size(); i++)
					{
						if (m_cmdList.m_CurrentColor[i] != nullptr)
						{
							if (_clear.m_flags & BGFX_CLEAR_COLOR_USE_PALETTE)
							{
								int index = _clear.m_index[i];
								rgba[0] = _palette[index][0];
								rgba[1] = _palette[index][1];
								rgba[2] = _palette[index][2];
								rgba[3] = _palette[index][3];
							}

							nvnCommandBufferClearColor(m_cmdList.get(), i, rgba, NVN_CLEAR_COLOR_MASK_RGBA);
						}
					}
				}

				if (_clear.m_flags & (BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL))
				{
					if (m_cmdList.m_CurrentDepth != nullptr)
					{
						nvnCommandBufferClearDepthStencil(m_cmdList.get(), _clear.m_depth, _clear.m_flags & BGFX_CLEAR_DEPTH, _clear.m_stencil, _clear.m_flags & BGFX_CLEAR_STENCIL);
					}
				}
			}
		}

		void bindProgram(const ProgramHandle& handle)
		{
			if (handle.idx != m_state.programIndex)
			{
				m_state.programIndex = handle.idx;

				if (m_state.programIndex != kInvalidHandle)
				{
					ProgramNVN& program = m_resources.m_program[m_state.programIndex];
					nvnCommandBufferBindProgram(m_cmdList.get(), &program.m_program, program.m_Stages);
				}
				else
				{
					nvnCommandBufferBindProgram(m_cmdList.get(), nullptr, NVNshaderStageBits::NVN_SHADER_STAGE_ALL_GRAPHICS_BITS);
					nvnCommandBufferBindProgram(m_cmdList.get(), nullptr, NVNshaderStageBits::NVN_SHADER_STAGE_COMPUTE_BIT);
				}
			}
		}

		void updateUniformBuffers(ProgramNVN& _program)
		{
			const ShaderNVN* shaders[2] =
			{
				_program.m_vsh,
				_program.m_fsh
			};

			NVNshaderStage stages[2] =
			{
				m_state.isCompute ? NVN_SHADER_STAGE_COMPUTE : NVN_SHADER_STAGE_VERTEX,
				NVN_SHADER_STAGE_FRAGMENT
			};

			for (int i = 0; i < 2; ++i)
			{
				if (shaders[i] == nullptr)
				{
					continue;
				}

				for (uint32_t index : shaders[i]->m_constantBuffers)
				{
					if (index == UniformBufferRegistry::InvalidEntry)
					{
						continue;
					}

					ShaderUniformBuffer& ub = m_resources.m_uniformBuffers.get(index);
					ub.update(m_cmdList.get());
					nvnCommandBufferBindUniformBuffer(m_cmdList.get(), stages[i], (int)index, ub.m_gpuAddress, ub.m_size);
				}
			}
		}
	};

	//
	// RendererContextNVN
	//

	struct RendererContextNVN : public RendererContextI
	{
		struct DeleteOperation
		{
			uint8_t m_count = 3;
			CopyOperation::Data* m_data;
		};

		NVNnativeWindow m_Hwnd = nullptr;

		PFNNVNBOOTSTRAPLOADERPROC m_nvnLoader = nullptr;

		NVNdevice m_Device;
		nn::vi::Display* m_pDisplay = nullptr;
		nn::vi::Layer* m_pLayer = nullptr;

		int m_CommandBufferCommandAlignment = 0;
		int m_CommandBufferControlAlignment = 0;
		int m_maxAnisotropy = 1;
		int m_UniformBufferAlignment = 0;

		TexturesSamplersPool m_TextureSamplersPool;
		DoubleBufferedResource<CommandMemoryPool> m_CommandMemoryPools;
		std::unique_ptr<UniformRingBuffer> m_frameUniformBuffer;

		ContextResources m_resources;

		SwapChainNVN m_SwapChain;
		CommandQueueNVN m_Queue;

		NVNsync* m_PreviousFrameSync = nullptr; // BBI-TODO: (tstump 1) change this from previous frame to array to we can do triple buffering
		uint64_t m_SubmitCounter = 0;

		std::vector<CopyOperation> m_copyOperations;
		std::vector<DeleteOperation> m_deleteOperations;

		RendererContextNVN()
		{
			// Pretend all features are available.
			g_caps.supported = 0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_CONSERVATIVE_RASTER
				| BGFX_CAPS_DRAW_INDIRECT
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_FRAGMENT_ORDERING
				| BGFX_CAPS_GRAPHICS_DEBUGGER
				| BGFX_CAPS_HIDPI
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_RENDERER_MULTITHREADED
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_CUBE_ARRAY
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				;

			// Pretend all features are available for all texture formats.
			for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
			{
				g_caps.formats[formatIdx] = 0
					| BGFX_CAPS_FORMAT_TEXTURE_NONE
					| BGFX_CAPS_FORMAT_TEXTURE_2D
					| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
					| BGFX_CAPS_FORMAT_TEXTURE_3D
					| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ
					| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE
					| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
					| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
					| BGFX_CAPS_FORMAT_TEXTURE_MSAA
					| BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
					;
			}

			// Pretend we have no limits
			g_caps.limits.maxTextureSize     = 16384;
			g_caps.limits.maxTextureLayers   = 2048;
			g_caps.limits.maxComputeBindings = g_caps.limits.maxTextureSamplers;
			g_caps.limits.maxFBAttachments   = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;
			g_caps.limits.maxVertexStreams   = BGFX_CONFIG_MAX_VERTEX_STREAMS;
		}

		~RendererContextNVN()
		{
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Nvn;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_NVN_NAME;
		}

		// NVN on NX
		bool nvnInit()
		{
			BX_ASSERT(m_Hwnd != nullptr, "No native window passed at initialization");

			pfnc_nvnDeviceGetProcAddress = (PFNNVNDEVICEGETPROCADDRESSPROC)(*nvnBootstrapLoader)("nvnDeviceGetProcAddress");
			nvnLoadCProcs(NULL, pfnc_nvnDeviceGetProcAddress);

			return true;
		}

		void nvnShutdown()
		{

		}

		static void debugLayerCallback(
			NVNdebugCallbackSource source,
			NVNdebugCallbackType type,
			int id,
			NVNdebugCallbackSeverity severity,
			const char* message,
			void* pUser
		)
		{
			BX_TRACE("NVN Debug Layer Callback:\n");
			BX_TRACE("  source:       0x%08x\n", source);
			BX_TRACE("  type:         0x%08x\n", type);
			BX_TRACE("  id:           0x%08x\n", id);
			BX_TRACE("  severity:     0x%08x\n", severity);
			BX_TRACE("  message:      %s\n", message);

			BX_ASSERT(false, "NVN Debug layer callback hit");
		}

		bool nvnInitDevice(const Init& _init)
		{
			int deviceFlags = 0;

			if (_init.debug) {
				deviceFlags = NVN_DEVICE_FLAG_DEBUG_ENABLE_BIT | NVN_DEVICE_FLAG_DEBUG_ENABLE_LEVEL_4_BIT;
			}

			NVNdeviceBuilder deviceBuilder;
			nvnDeviceBuilderSetDefaults(&deviceBuilder);
			nvnDeviceBuilderSetFlags(&deviceBuilder, deviceFlags);

			if (!nvnDeviceInitialize(&m_Device, &deviceBuilder))
			{
				BX_ASSERT(false, "nvnDeviceInitialize");
				return false;
			}

			nvnLoadCProcs(&m_Device, pfnc_nvnDeviceGetProcAddress);

			/*
				* Debug Layer Callback
				* --------------------
				* Install the debug layer callback if the debug layer was enabled during
				* device initialization. It is possible to pass a pointer to the NVN API
				* to remember and pass back through the debug callback.
				*/
			if (deviceFlags & NVN_DEVICE_FLAG_DEBUG_ENABLE_LEVEL_4_BIT)
			{
				nvnDeviceInstallDebugCallback(
					&m_Device,
					reinterpret_cast<PFNNVNDEBUGCALLBACKPROC>(&debugLayerCallback),
					NULL, // For testing purposes; any pointer is OK here.
					NVN_TRUE // NVN_TRUE = Enable the callback.
				);
			}

			int apiMajor, apiMinor;
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_API_MAJOR_VERSION, &apiMajor);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_API_MINOR_VERSION, &apiMinor);

			// do quick API version check? is that even necessary?

			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_COMMAND_ALIGNMENT, &m_CommandBufferCommandAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_CONTROL_ALIGNMENT, &m_CommandBufferControlAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_UNIFORM_BUFFER_ALIGNMENT, &m_UniformBufferAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_MAX_TEXTURE_ANISOTROPY, &m_maxAnisotropy);

			return true;
		}

		void initializeMemoryPool()
		{
			const size_t initialRingSize = BGFX_CONFIG_MAX_DRAW_CALLS * 64;

			m_TextureSamplersPool.init(&m_Device);
			m_CommandMemoryPools.init(&m_Device);
			m_frameUniformBuffer = std::make_unique<UniformRingBuffer>(initialRingSize);
		}

		void initializeSwapChain(const Init& _init)
		{
			m_SwapChain.create(m_Hwnd, &m_Device, _init.resolution, bgfx::TextureFormat::Enum::RGBA8, bgfx::TextureFormat::Enum::D24S8);
			m_Queue.init(&m_Device, &m_SwapChain);
		}

		void initializeWindow(const Init& _init)
		{
#if 0
			for (int ii = 0; ii < SwapChainBufferCount; ii++)
			{
				nvnSyncInitialize(&m_DisplayFence[ii], &m_Device);
			}

			if (nn::oe::GetOperationMode() == nn::oe::OperationMode_Console) {
				g_caps.displayWidth = 1920;
				g_caps.displayHeight = 1080;
			}
			else {
				g_caps.displayWidth = 1280;
				g_caps.displayHeight = 720;
			}
#endif
		}

		bool init(const Init& _init)
		{
			m_Hwnd = (NVNnativeWindow)g_platformData.nwh;

			if (!m_Hwnd)
			{
				BX_ASSERT(false, "No hwnd provided");
				return false;
			}

			if (!nvnInit())
			{
				return false;
			}

			if (!nvnInitDevice(_init))
			{
				return false;
			}

			g_nvnDevice = &m_Device;

			initializeMemoryPool();
			initializeSwapChain(_init);
			initializeWindow(_init);

			return true;
		}

		void shutdown()
		{
			//for (int ii = 0; ii < SwapChainBufferCount; ii++)
			//{
			//	nvnSyncFinalize(&m_DisplayFence[ii]);
			//}

			//m_activeSamplersCount = 0;
			//m_samplers.invalidate();
			//m_Queue.shutdown();

			m_SwapChain.destroy();

			m_frameUniformBuffer.reset();
			m_CommandMemoryPools.shutdown();
			m_TextureSamplersPool.shutdown();

			g_nvnDevice = NULL;
			nvnDeviceFinalize(&m_Device);
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_resources.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags, 0, BufferNVN::Usage::IndexBuffer);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_resources.m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) override
		{
			VertexLayout& layout = m_resources.m_vertexLayouts[_handle.idx];
			::memcpy(&layout, &_layout, sizeof(VertexLayout));
			dump(layout);
		}

		void destroyVertexLayout(VertexLayoutHandle _handle) override
		{
			VertexLayout& layout = m_resources.m_vertexLayouts[_handle.idx];
			memset(&layout, 0, sizeof(VertexLayout));
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) override
		{
			m_resources.m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _layoutHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_resources.m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) override
		{
		}

		void updateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, const Memory* /*_mem*/) override
		{
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle /*_handle*/) override
		{
		}

		void createDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) override
		{
		}

		void updateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, const Memory* /*_mem*/) override
		{
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle /*_handle*/) override
		{
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			ShaderNVN& shader = m_resources.m_shaders[_handle.idx];

			shader.create(&m_Device, _mem, m_resources.m_uniformReg, m_resources.m_uniformBuffers);

			// resolve uniform references in uniform buffers
			for (uint32_t index : shader.m_constantBuffers)
			{
				ShaderUniformBuffer& cb = m_resources.m_uniformBuffers.get(index);
				for (ShaderUniformBuffer::UniformReference& uniformRef : cb.m_uniforms)
				{
					if (uniformRef.m_data == nullptr)
					{
						if (uniformRef.m_predefined != PredefinedUniform::Enum::Count)
						{
							int predefined = 0;
							for (predefined = 0; predefined < shader.m_numPredefined; ++predefined)
							{
								if (shader.m_predefined[predefined].m_type == uniformRef.m_predefined)
								{
									break;
								}
							}

							BX_ASSERT(predefined != shader.m_numPredefined, "Unknown predefined uniform.");

							uint32_t loc = shader.m_predefined[predefined].m_loc;

							if (uniformRef.m_predefined & kUniformFragmentBit)
							{
								uniformRef.m_data = &m_resources.m_uniformsPredefinedFS[loc];
							}
							else
							{
								uniformRef.m_data = &m_resources.m_uniformsPredefinedVS[loc];
							}
						}
						else
						{
							uniformRef.m_data = m_resources.m_uniforms[uniformRef.m_handle.idx];
						}
					}
				}
			}
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_resources.m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override
		{
			m_resources.m_program[_handle.idx].create(&m_Device, &m_resources.m_shaders[_vsh.idx], &m_resources.m_shaders[_fsh.idx]);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_resources.m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			CopyOperation copyOp;
			m_resources.m_textures[_handle.idx].create(&m_Device, _mem, _flags, _skip, copyOp);
			m_TextureSamplersPool.set(_handle.idx, &m_resources.m_textures[_handle.idx].m_ptr);
			if (!copyOp.m_ops.empty())
			{
				m_copyOperations.push_back(copyOp);
			}
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, uint16_t /*_pitch*/, const Memory* /*_mem*/) override
		{
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle /*_handle*/, void* /*_data*/, uint8_t /*_mip*/) override
		{
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/, uint16_t /*_numLayers*/) override
		{
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) override
		{
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) override
		{
			return 0;
		}

		void destroyTexture(TextureHandle /*_handle*/) override
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, uint8_t /*_num*/, const Attachment* /*_attachment*/) override
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_format*/, TextureFormat::Enum /*_depthFormat*/) override
		{
		}

		void destroyFrameBuffer(FrameBufferHandle /*_handle*/) override
		{
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_resources.m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_resources.m_uniforms[_handle.idx]);
			}

			uint32_t size = nn::util::align_up(g_uniformTypeSize[_type] * _num, 16);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_resources.m_uniforms[_handle.idx] = data;
			m_resources.m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_resources.m_uniforms[_handle.idx]);
			m_resources.m_uniforms[_handle.idx] = NULL;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags & kUniformFragmentBit)
			{
				memcpy(&m_resources.m_uniformsPredefinedFS[_regIndex], _val, _numRegs * 16);
			}
			else
			{
				memcpy(&m_resources.m_uniformsPredefinedVS[_regIndex], _val, _numRegs * 16);
			}
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
		}

		void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) override
		{
		}

		void updateViewName(ViewId /*_id*/, const char* /*_name*/) override
		{
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			memcpy(m_resources.m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle /*_handle*/) override
		{
		}

		void setMarker(const char* /*_marker*/, uint16_t /*_len*/) override
		{
		}

		virtual void setName(Handle /*_handle*/, const char* /*_name*/, uint16_t /*_len*/) override
		{
		}

		void _processCopyOperations(CommandListNVN& cmd)
		{
			// process pending transient deletions first
			{
				auto it = m_deleteOperations.begin();
				while (it != m_deleteOperations.end())
				{
					DeleteOperation& op = *it;
					op.m_count--;
					if (op.m_count == 0)
					{
						nvnBufferFinalize(&op.m_data->m_buffer);
						nvnMemoryPoolFinalize(&op.m_data->m_pool);
						BX_ALIGNED_FREE(g_allocator, op.m_data->m_mem, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
						it = m_deleteOperations.erase(it);
					}
					else
					{
						++it;
					}
				}
			}

			// then process pending copy operations
			{
				NVNcommandBuffer* cmdBuf = cmd.get();

				for (CopyOperation& copyOp : m_copyOperations)
				{
					CopyOperation::Data* data = copyOp.m_data;

					NVNbufferAddress gpuAddr = nvnBufferGetAddress(&data->m_buffer);
					for (CopyOperation::Op& op : copyOp.m_ops)
					{
						nvnCommandBufferCopyBufferToTexture(cmdBuf, gpuAddr + op.m_offset, op.m_dstData, &op.m_dstView, &op.m_dstRegion, NVN_COPY_FLAGS_MIRROR_Y_BIT);
					}

					DeleteOperation delOp;
					delOp.m_data = data;
					m_deleteOperations.push_back(delOp);
				}

				m_copyOperations.clear();
			}
		}

		void _processItemCompute(Commands& _cmds, Frame* _render, const RenderCompute& _compute)
		{
			ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

			_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _compute);
			rendererUpdateUniforms(this, _render->m_uniformBuffer[_compute.m_uniformIdx], _compute.m_uniformBegin, _compute.m_uniformEnd);
			_cmds.updateUniformBuffers(program);
		}

		void _processItemDraw(Commands& _cmds, Frame* _render, const RenderDraw& _draw)
		{
			ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

			_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _draw);
			rendererUpdateUniforms(this, _render->m_uniformBuffer[_draw.m_uniformIdx], _draw.m_uniformBegin, _draw.m_uniformEnd);
			_cmds.updateUniformBuffers(program);

			// bind resources
			// dispatch?
		}

		void _processViewItems(CommandListNVN& cmd, Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
		{
			BGFX_PROFILER_SCOPE("gfx::_processViewItems", 0xff2040ff);

			Commands cmds(cmd, _render, m_resources);

			BX_UNUSED(_clearQuad);
			BX_UNUSED(_textVideoMemBlitter);

			SortKey key;

			BackBuffer backBuffer = m_SwapChain.get();

			std::array<NVNtexture*, 1> defaultTarget = { &backBuffer.m_Color->m_ptr };
			cmds.setFrameBuffer(1, defaultTarget.data(), &backBuffer.m_Depth->m_ptr);

			int32_t numItems = _render->m_numRenderItems;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];

				cmds.m_state.isCompute = key.decode(encodedKey, _render->m_viewRemap);

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];

				BX_UNUSED(renderBind);

				const View& view = _render->m_view[key.m_view];

				if (cmds.setView(_render, key.m_view, item == numItems, backBuffer))
				{
					cmds.setViewport(view.m_rect, view.m_scissor, 0.f, 1.f);
					cmds.clearViewport(view.m_clear, _render->m_colorPalette);
				}

				cmds.bindProgram(key.m_program);

				if (cmds.m_state.isCompute)
				{
					_processItemCompute(cmds, _render, renderItem.compute);
				}
				else
				{
					_processItemDraw(cmds, _render, renderItem.draw);
				}

				cmds.m_state.wasCompute = cmds.m_state.isCompute;

				++item;
			}
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override
		{
			BGFX_PROFILER_SCOPE("gfx::submit", 0xff2040ff);

			_render->sort();

			if (0 == (_render->m_debug & BGFX_DEBUG_IFH))
			{
				{
					BGFX_PROFILER_SCOPE("gfx::acquireNextScanBuffer", 0xff2040ff);

					m_SwapChain.acquireNext();

					// TODO REMOVE
					m_Queue.waitForIdle();

					m_CommandMemoryPools.swap();
				}

				{
					BGFX_PROFILER_SCOPE("gfx::waitForPreviousFrame", 0xff2040ff);

					if (m_PreviousFrameSync != nullptr)
					{
						m_Queue.finish(m_PreviousFrameSync);
						m_PreviousFrameSync = nullptr;
					}

					if (m_SubmitCounter > 0)
					{
						m_frameUniformBuffer->setCompletedFence(m_SubmitCounter);
					}

					m_SubmitCounter++;
					m_frameUniformBuffer->setCurrentFence(m_SubmitCounter);
				}

				CommandListNVN& cmd = *m_Queue.alloc(m_CommandMemoryPools.get(), "submit");

				_processCopyOperations(cmd);

				m_TextureSamplersPool.bind(cmd.get());

				_processViewItems(cmd, _render, _clearQuad, _textVideoMemBlitter);

				m_PreviousFrameSync = m_Queue.kick();
				m_SwapChain.present(&m_Queue.m_GfxQueue);
			}
#if 0
			const int64_t timerFreq = bx::getHPFrequency();
			const int64_t timeBegin = bx::getHPCounter();

			Stats& perfStats = _render->m_perfStats;
			perfStats.cpuTimeBegin  = timeBegin;
			perfStats.cpuTimeEnd    = timeBegin;
			perfStats.cpuTimerFreq  = timerFreq;

			perfStats.gpuTimeBegin  = 0;
			perfStats.gpuTimeEnd    = 0;
			perfStats.gpuTimerFreq  = 1000000000;

			bx::memSet(perfStats.numPrims, 0, sizeof(perfStats.numPrims) );

			perfStats.gpuMemoryMax  = -INT64_MAX;
			perfStats.gpuMemoryUsed = -INT64_MAX;
#endif
		}

		void blitSetup(TextVideoMemBlitter& /*_blitter*/) override
		{
		}

		void blitRender(TextVideoMemBlitter& /*_blitter*/, uint32_t /*_numIndices*/) override
		{
		}
	};

	static RendererContextNVN* s_renderNVN = NULL;

	void OutOfCommandBufferMemoryEventCallback(NVNcommandBuffer* cmdBuf,
		NVNcommandBufferMemoryEvent event,
		size_t minSize,
		void* callbackData)
	{
		const size_t size = std::max(size_t{ 512 }, minSize);

		CommandMemoryPool& pools = s_renderNVN->m_CommandMemoryPools.get();

		MemoryPool& poolCommands = pools[MemoryPoolType::CommandBufferCommands];
		MemoryPool& poolControls = pools[MemoryPoolType::CommandBufferControls];

		switch (event)
		{
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY:
			nvnCommandBufferAddCommandMemory(cmdBuf, poolCommands.GetMemoryPool(), poolCommands.GetNewMemoryChunkOffset(size, s_renderNVN->m_CommandBufferCommandAlignment), size);
			break;
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY:
			nvnCommandBufferAddControlMemory(cmdBuf, static_cast<uint8_t*>(poolControls.GetMemory()) + poolControls.GetNewMemoryChunkOffset(size, s_renderNVN->m_CommandBufferControlAlignment), size);
			break;
		default:
			BX_ASSERT(false, "Unknown event");
			break;
		}
	}

	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		s_renderNVN = BX_NEW(g_allocator, RendererContextNVN);
		if (!s_renderNVN->init(_init))
		{
			BX_DELETE(g_allocator, s_renderNVN);
			s_renderNVN = NULL;
		}

		return s_renderNVN;
	}

	void rendererDestroy()
	{
		s_renderNVN->shutdown();
		BX_DELETE(g_allocator, s_renderNVN);
		s_renderNVN = NULL;
	}
} /* namespace nvn */ } // namespace bgfx

#else

namespace bgfx { namespace nvn
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace nvn */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_NVN

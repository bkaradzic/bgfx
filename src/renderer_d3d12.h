/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_D3D12_H_HEADER_GUARD
#define BGFX_RENDERER_D3D12_H_HEADER_GUARD

#define USE_D3D12_DYNAMIC_LIB 1

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_4.h>

#include "renderer.h"
#include "renderer_d3d.h"
#include "shader_dxbc.h"

namespace bgfx { namespace d3d12
{
	struct Rdt
	{
		enum Enum
		{
			Sampler,
			SRV,
			CBV,
			UAV,

			Count
		};
	};

	class ScratchBufferD3D12
	{
	public:
		ScratchBufferD3D12()
		{
		}

		~ScratchBufferD3D12()
		{
		}

		void create(uint32_t _size, uint32_t _maxDescriptors);
		void destroy();
		void reset(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle);
		void* alloc(D3D12_GPU_VIRTUAL_ADDRESS& gpuAddress, uint32_t _size);
		void  alloc(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct TextureD3D12& _texture);
		void  allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct TextureD3D12& _texture, uint8_t _mip);

		void  alloc(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct BufferD3D12& _buffer);
		void  allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct BufferD3D12& _buffer);

		ID3D12DescriptorHeap* getHeap()
		{
			return m_heap;
		}

	private:
		ID3D12DescriptorHeap* m_heap;
		ID3D12Resource* m_upload;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVA;
		D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;
		uint32_t m_incrementSize;
		uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_pos;
	};

	class DescriptorAllocator
	{
	public:
		DescriptorAllocator()
			: m_numDescriptorsPerBlock(1)
		{
		}

		~DescriptorAllocator()
		{
		}

		void create(D3D12_DESCRIPTOR_HEAP_TYPE _type, uint32_t _maxDescriptors, uint16_t _numDescriptorsPerBlock = 1);
		void destroy();

		uint16_t alloc(ID3D12Resource* _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC* _desc);
		uint16_t alloc(const uint32_t* _flags, uint32_t _num = BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		void free(uint16_t _handle);
		void reset();

		D3D12_GPU_DESCRIPTOR_HANDLE get(uint16_t _handle);

		ID3D12DescriptorHeap* getHeap()
		{
			return m_heap;
		}

	private:
		ID3D12DescriptorHeap* m_heap;
		bx::HandleAlloc* m_handleAlloc;
		D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;
		uint32_t m_incrementSize;
		uint16_t m_numDescriptorsPerBlock;
	};

	struct BufferD3D12
	{
		BufferD3D12()
			: m_ptr(NULL)
			, m_state(D3D12_RESOURCE_STATE_COMMON)
			, m_size(0)
			, m_flags(BGFX_BUFFER_NONE)
			, m_dynamic(false)
		{
		}

		void create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride = 0);
		void update(ID3D12GraphicsCommandList* _commandList, uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			if (NULL != m_ptr)
			{
				DX_RELEASE(m_ptr, 0);
				m_dynamic = false;
			}
		}

		D3D12_RESOURCE_STATES setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state);

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource* m_ptr;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVA;
		D3D12_RESOURCE_STATES m_state;
		uint32_t m_size;
		uint16_t m_flags;
		bool m_dynamic;
	};

	struct VertexBufferD3D12 : public BufferD3D12
	{
		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags);

		VertexDeclHandle m_decl;
	};

	struct ShaderD3D12
	{
		ShaderD3D12()
			: m_code(NULL)
			, m_constantBuffer(NULL)
			, m_hash(0)
			, m_numUniforms(0)
			, m_numPredefined(0)
		{
		}

		void create(const Memory* _mem);
		DWORD* getShaderCode(uint8_t _fragmentBit, const Memory* _mem);

		void destroy()
		{
			if (NULL != m_constantBuffer)
			{
				ConstantBuffer::destroy(m_constantBuffer);
				m_constantBuffer = NULL;
			}

			m_numPredefined = 0;

			if (NULL != m_code)
			{
				release(m_code);
				m_code = NULL;
				m_hash = 0;
			}
		}

		const Memory* m_code;
		ConstantBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];

		uint32_t m_hash;
		uint16_t m_numUniforms;
		uint16_t m_size;
		uint8_t m_numPredefined;
	};

	struct ProgramD3D12
	{
		ProgramD3D12()
			: m_vsh(NULL)
			, m_fsh(NULL)
		{
		}

		void create(const ShaderD3D12* _vsh, const ShaderD3D12* _fsh)
		{
			BX_CHECK(NULL != _vsh->m_code, "Vertex shader doesn't exist.");
			m_vsh = _vsh;
			memcpy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform));
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				BX_CHECK(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
				m_fsh = _fsh;
				memcpy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform));
				m_numPredefined += _fsh->m_numPredefined;
			}
		}

		void destroy()
		{
			m_numPredefined = 0;
			m_vsh = NULL;
			m_fsh = NULL;
		}

		const ShaderD3D12* m_vsh;
		const ShaderD3D12* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;
	};

	struct TextureD3D12
	{
		enum Enum
		{
			Texture2D,
			Texture3D,
			TextureCube,
		};

		TextureD3D12()
			: m_ptr(NULL)
			, m_state(D3D12_RESOURCE_STATE_COMMON)
			, m_numMips(0)
		{
		}

		void create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
		void destroy();
		void update(ID3D12GraphicsCommandList* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void commit(uint8_t _stage, uint32_t _flags = BGFX_SAMPLER_DEFAULT_FLAGS);
		void resolve();
		D3D12_RESOURCE_STATES setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state);

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource* m_ptr;
		D3D12_RESOURCE_STATES m_state;
		uint32_t m_flags;
		uint16_t m_samplerIdx;
		uint8_t m_type;
		uint8_t m_requestedFormat;
		uint8_t m_textureFormat;
		uint8_t m_numMips;
	};

	struct FrameBufferD3D12
	{
		FrameBufferD3D12()
			: m_swapChain(NULL)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
			, m_numTh(0)
		{
			m_depth.idx = bgfx::invalidHandle;
		}

		void create(uint8_t _num, const TextureHandle* _handles);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		void preReset();
		void postReset();
		void resolve();
		void clear(ID3D12GraphicsCommandList* _commandList, const Clear& _clear, const float _palette[][4], const D3D12_RECT* _rect = NULL, uint32_t _num = 0);

		TextureHandle m_texture[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		TextureHandle m_depth;
		IDXGISwapChain* m_swapChain;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		TextureHandle m_th[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

	struct CommandQueue
	{
		CommandQueue()
			: m_control(BX_COUNTOF(m_commandList) )
		{
		}

		void init(ID3D12Device* _device)
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc;
			queueDesc.Type     = D3D12_COMMAND_LIST_TYPE_DIRECT;
			queueDesc.Priority = 0;
			queueDesc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.NodeMask = 1;
			DX_CHECK(_device->CreateCommandQueue(&queueDesc
					, __uuidof(ID3D12CommandQueue)
					, (void**)&m_commandQueue
					) );

			m_currentFence = 0;
			DX_CHECK(_device->CreateFence(0
					, D3D12_FENCE_FLAG_NONE
					, __uuidof(ID3D12Fence)
					, (void**)&m_fence
					) );

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_commandList); ++ii)
			{
				DX_CHECK(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
						, __uuidof(ID3D12CommandAllocator)
						, (void**)&m_commandList[ii].m_commandAllocator
						) );

				DX_CHECK(_device->CreateCommandList(0
						, D3D12_COMMAND_LIST_TYPE_DIRECT
						, m_commandList[ii].m_commandAllocator
						, NULL
						, __uuidof(ID3D12GraphicsCommandList)
						, (void**)&m_commandList[ii].m_commandList
						) );

				DX_CHECK(m_commandList[ii].m_commandList->Close() );
			}
		}

		void shutdown()
		{
			finish(UINT64_MAX, true);

			DX_RELEASE(m_fence, 0);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_commandList); ++ii)
			{
				DX_RELEASE(m_commandList[ii].m_commandAllocator, 0);
				DX_RELEASE(m_commandList[ii].m_commandList, 0);
			}

			DX_RELEASE(m_commandQueue, 0);
		}

		ID3D12GraphicsCommandList* alloc()
		{
			while (0 == m_control.reserve(1) )
			{
				consume();
			}

			CommandList& commandList = m_commandList[m_control.m_current];
			DX_CHECK(commandList.m_commandAllocator->Reset() );
			DX_CHECK(commandList.m_commandList->Reset(commandList.m_commandAllocator, NULL) );
			return commandList.m_commandList;
		}

		uint64_t kick()
		{
			CommandList& commandList = m_commandList[m_control.m_current];
			DX_CHECK(commandList.m_commandList->Close() );

			ID3D12CommandList* commandLists[] = { commandList.m_commandList };
			m_commandQueue->ExecuteCommandLists(BX_COUNTOF(commandLists), commandLists);

			commandList.m_event = CreateEventExA(NULL, NULL, 0, EVENT_ALL_ACCESS);
			const uint64_t fence = m_currentFence++;
			m_commandQueue->Signal(m_fence, fence);
			m_fence->SetEventOnCompletion(fence, commandList.m_event);

			m_control.commit(1);

			return fence;
		}

		void finish(uint64_t _waitFence = UINT64_MAX, bool _finishAll = false)
		{
			while (0 < m_control.available() )
			{
				consume();

				if (!_finishAll
				&&  _waitFence <= m_completedFence)
				{
					return;
				}
			}

			BX_CHECK(0 == m_control.available(), "");
		}

		bool tryFinish(uint64_t _waitFence)
		{
			if (0 < m_control.available() )
			{
				if (consume(0)
				&& _waitFence <= m_completedFence)
				{
					return true;
				}
			}

			return false;
		}

		void release(ID3D12Resource* _ptr)
		{
			m_release[m_control.m_current].push_back(_ptr);
		}

		bool consume(uint32_t _ms = INFINITE)
		{
			CommandList& commandList = m_commandList[m_control.m_read];
			if (WAIT_OBJECT_0 == WaitForSingleObject(commandList.m_event, _ms) )
			{
				CloseHandle(commandList.m_event);
				commandList.m_event = NULL;
				m_completedFence = m_fence->GetCompletedValue();
				m_commandQueue->Wait(m_fence, m_completedFence);

				ResourceArray& ra = m_release[m_control.m_read];
				for (ResourceArray::iterator it = ra.begin(), itEnd = ra.end(); it != itEnd; ++it)
				{
					DX_RELEASE(*it, 0);
				}
				ra.clear();

				m_control.consume(1);

				return true;
			}

			return false;
		}

		struct CommandList
		{
			ID3D12GraphicsCommandList* m_commandList;
			ID3D12CommandAllocator* m_commandAllocator;
			HANDLE m_event;
		};

		ID3D12CommandQueue* m_commandQueue;
		uint64_t m_currentFence;
		uint64_t m_completedFence;
		ID3D12Fence* m_fence;
		CommandList m_commandList[4];
		typedef stl::vector<ID3D12Resource*> ResourceArray;
		ResourceArray m_release[4];
		bx::RingBufferControl m_control;
	};

} /* namespace d3d12 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D12_H_HEADER_GUARD

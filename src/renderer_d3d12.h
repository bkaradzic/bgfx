/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_D3D12_H_HEADER_GUARD
#define BGFX_RENDERER_D3D12_H_HEADER_GUARD

#define USE_D3D12_DYNAMIC_LIB 1

#include <sal.h>
#include <d3d12.h>

#if defined(__MINGW32__) // BK - temp workaround for MinGW until I nuke d3dx12 usage.
extern "C++" {
	__extension__ template<typename Ty>
	const GUID& __mingw_uuidof();

	template<>
	const GUID& __mingw_uuidof<ID3D12Device>()
	{
		static const GUID IID_ID3D12Device0 = { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
		return IID_ID3D12Device0;
	}
}
#endif // defined(__MINGW32__)

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wmissing-field-initializers");
#include <d3dx12.h>
BX_PRAGMA_DIAGNOSTIC_POP();

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

		void* allocCbv(D3D12_GPU_VIRTUAL_ADDRESS& gpuAddress, uint32_t _size);

		void  allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct TextureD3D12& _texture, uint8_t _mip = 0);
		void  allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct BufferD3D12& _buffer);

		void  allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle, struct TextureD3D12& _texture, uint8_t _mip = 0);
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

	class DescriptorAllocatorD3D12
	{
	public:
		DescriptorAllocatorD3D12()
			: m_numDescriptorsPerBlock(1)
		{
		}

		~DescriptorAllocatorD3D12()
		{
		}

		void create(D3D12_DESCRIPTOR_HEAP_TYPE _type, uint16_t _maxDescriptors, uint16_t _numDescriptorsPerBlock = 1);
		void destroy();

		uint16_t alloc(ID3D12Resource* _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC* _desc);
		uint16_t alloc(const uint32_t* _flags, uint32_t _num, const float _palette[][4]);
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
		void destroy();

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
				UniformBuffer::destroy(m_constantBuffer);
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
		UniformBuffer* m_constantBuffer;

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
			memset(&m_srvd, 0, sizeof(m_srvd) );
			memset(&m_uavd, 0, sizeof(m_uavd) );
		}

		void create(const Memory* _mem, uint32_t _flags, uint8_t _skip);
		void destroy();
		void update(ID3D12GraphicsCommandList* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void resolve();
		D3D12_RESOURCE_STATES setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state);

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource* m_ptr;
		D3D12_RESOURCE_STATES m_state;
		uint32_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
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
			, m_width(0)
			, m_height(0)
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
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		TextureHandle m_th[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

	struct CommandQueueD3D12
	{
		CommandQueueD3D12()
			: m_currentFence(0)
			, m_completedFence(0)
			, m_control(BX_COUNTOF(m_commandList) )
		{
			BX_STATIC_ASSERT(BX_COUNTOF(m_commandList) == BX_COUNTOF(m_release) );
		}

		void init(ID3D12Device* _device);
		void shutdown();
		ID3D12GraphicsCommandList* alloc();
		uint64_t kick();
		void finish(uint64_t _waitFence = UINT64_MAX, bool _finishAll = false);
		bool tryFinish(uint64_t _waitFence);
		void release(ID3D12Resource* _ptr);
		bool consume(uint32_t _ms = INFINITE);

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
		CommandList m_commandList[256];
		typedef stl::vector<ID3D12Resource*> ResourceArray;
		ResourceArray m_release[256];
		bx::RingBufferControl m_control;
	};

	struct BatchD3D12
	{
		enum Enum
		{
			Draw,
			DrawIndexed,

			Count
		};

		BatchD3D12()
			: m_currIndirect(0)
			, m_maxDrawPerBatch(0)
			, m_minIndirect(0)
			, m_flushPerBatch(0)
		{
			memset(m_num, 0, sizeof(m_num) );
		}

		~BatchD3D12()
		{
		}

		void create(uint32_t _maxDrawPerBatch);
		void destroy();

		template<typename Ty>
		Ty& getCmd(Enum _type);

		uint32_t draw(ID3D12GraphicsCommandList* _commandList, D3D12_GPU_VIRTUAL_ADDRESS _cbv, const RenderDraw& _draw);

		void flush(ID3D12GraphicsCommandList* _commandList, Enum _type);
		void flush(ID3D12GraphicsCommandList* _commandList, bool _clean = false);

		void begin();
		void end(ID3D12GraphicsCommandList* _commandList);

		void setSeqMode(bool _enabled)
		{
			m_flushPerBatch = _enabled ? 1 : m_maxDrawPerBatch;
		}

		void setIndirectMode(bool _enabled)
		{
			m_minIndirect = _enabled ? 64 : UINT32_MAX;
		}

		ID3D12CommandSignature* m_commandSignature[Count];
		uint32_t m_num[Count];
		void* m_cmds[Count];

		struct DrawIndirectCommand
		{
			D3D12_GPU_VIRTUAL_ADDRESS cbv;
			D3D12_VERTEX_BUFFER_VIEW vbv[2];
			D3D12_DRAW_ARGUMENTS draw;
		};

		struct DrawIndexedIndirectCommand
		{
			D3D12_GPU_VIRTUAL_ADDRESS cbv;
			D3D12_VERTEX_BUFFER_VIEW vbv[2];
			D3D12_INDEX_BUFFER_VIEW ibv;
			D3D12_DRAW_INDEXED_ARGUMENTS drawIndexed;
		};

		struct Stats
		{
			uint32_t m_numImmediate[Count];
			uint32_t m_numIndirect[Count];
		};

		BufferD3D12 m_indirect[32];
		uint32_t m_currIndirect;
		DrawIndexedIndirectCommand m_current;

		Stats m_stats;
		uint32_t m_maxDrawPerBatch;
		uint32_t m_minIndirect;
		uint32_t m_flushPerBatch;
	};

} /* namespace d3d12 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D12_H_HEADER_GUARD

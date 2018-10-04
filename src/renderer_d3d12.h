/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_D3D12_H_HEADER_GUARD
#define BGFX_RENDERER_D3D12_H_HEADER_GUARD

#define USE_D3D12_DYNAMIC_LIB BX_PLATFORM_WINDOWS

#include <sal.h>
#if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
#   include <d3d12.h>
#else
#   if !BGFX_CONFIG_DEBUG
#      define D3DCOMPILE_NO_DEBUG 1
#   endif // !BGFX_CONFIG_DEBUG
#   include <d3d12_x.h>
#endif // BX_PLATFORM_XBOXONE

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
#if BX_PLATFORM_XBOXONE
#	include <d3dx12_x.h>
#else
#	include <d3dx12.h>
#endif // BX_PLATFORM_XBOXONE
BX_PRAGMA_DIAGNOSTIC_POP();

#ifndef D3D12_TEXTURE_DATA_PITCH_ALIGNMENT
#	define D3D12_TEXTURE_DATA_PITCH_ALIGNMENT 1024
#endif // D3D12_TEXTURE_DATA_PITCH_ALIGNMENT

#include "renderer.h"
#include "renderer_d3d.h"
#include "shader_dxbc.h"
#include "debug_renderdoc.h"
#include "nvapi.h"
#include "dxgi.h"

#if BGFX_CONFIG_DEBUG_PIX
#	if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
typedef struct PIXEventsThreadInfo* (WINAPI* PFN_PIX_GET_THREAD_INFO)();
typedef uint64_t                    (WINAPI* PFN_PIX_EVENTS_REPLACE_BLOCK)(bool _getEarliestTime);

extern PFN_PIX_GET_THREAD_INFO      bgfx_PIXGetThreadInfo;
extern PFN_PIX_EVENTS_REPLACE_BLOCK bgfx_PIXEventsReplaceBlock;

#		define PIXGetThreadInfo      bgfx_PIXGetThreadInfo
#		define PIXEventsReplaceBlock bgfx_PIXEventsReplaceBlock
#	else
extern "C" struct PIXEventsThreadInfo* WINAPI bgfx_PIXGetThreadInfo();
extern "C" uint64_t                    WINAPI bgfx_PIXEventsReplaceBlock(bool _getEarliestTime);
#	endif // BX_PLATFORM_WINDOWS

#	include <pix3.h>

#	define _PIX3_BEGINEVENT(_commandList, _color, _name) PIXBeginEvent(_commandList, _color, _name)
#	define _PIX3_SETMARKER(_commandList, _color, _name)  PIXSetMarker(_commandList, _color, _name)
#	define _PIX3_ENDEVENT(_commandList)                  PIXEndEvent(_commandList)

#	define PIX3_BEGINEVENT(_commandList, _color, _name) _PIX3_BEGINEVENT(_commandList, _color, _name)
#	define PIX3_SETMARKER(_commandList, _color, _name)  _PIX3_SETMARKER(_commandList, _color, _name)
#	define PIX3_ENDEVENT(_commandList)                  _PIX3_ENDEVENT(_commandList)
#else
#	define PIX3_BEGINEVENT(_commandList, _color, _name) BX_UNUSED(_commandList, _color, _name)
#	define PIX3_SETMARKER(_commandList, _color, _name)  BX_UNUSED(_commandList, _color, _name)
#	define PIX3_ENDEVENT(_commandList)                  BX_UNUSED(_commandList)
#endif // BGFX_CONFIG_DEBUG_PIX

namespace bgfx { namespace d3d12
{
	typedef HRESULT (WINAPI* PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES)(uint32_t _numFeatures, const IID* _iids, void* _configurationStructs, uint32_t* _configurationStructSizes);

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
		void reset(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle);

		void  allocEmpty(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle);

		void* allocCbv(D3D12_GPU_VIRTUAL_ADDRESS& _gpuAddress, uint32_t _size);

		void  allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, struct TextureD3D12& _texture, uint8_t _mip = 0);
		void  allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, struct BufferD3D12& _buffer);

		void  allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, struct TextureD3D12& _texture, uint8_t _mip = 0);
		void  allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, struct BufferD3D12& _buffer);

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
			bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform));
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				BX_CHECK(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
				m_fsh = _fsh;
				bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform));
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
			, m_directAccessPtr(NULL)
			, m_state(D3D12_RESOURCE_STATE_COMMON)
			, m_numMips(0)
		{
			bx::memSet(&m_srvd, 0, sizeof(m_srvd) );
			bx::memSet(&m_uavd, 0, sizeof(m_uavd) );
		}

		void* create(const Memory* _mem, uint64_t _flags, uint8_t _skip);
		void destroy();
		void update(ID3D12GraphicsCommandList* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void resolve(uint8_t _resolve) const;
		D3D12_RESOURCE_STATES setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state);

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource* m_ptr;
		void* m_directAccessPtr;
		D3D12_RESOURCE_STATES m_state;
		uint64_t m_flags;
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
			, m_nwh(NULL)
			, m_width(0)
			, m_height(0)
			, m_denseIdx(UINT16_MAX)
			, m_num(0)
			, m_numTh(0)
			, m_state(D3D12_RESOURCE_STATE_PRESENT)
			, m_needPresent(false)
		{
			m_depth.idx = bgfx::kInvalidHandle;
		}

		void create(uint8_t _num, const Attachment* _attachment);
		void create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat);
		uint16_t destroy();
		HRESULT present(uint32_t _syncInterval, uint32_t _flags);
		void preReset();
		void postReset();
		void resolve();
		void clear(ID3D12GraphicsCommandList* _commandList, const Clear& _clear, const float _palette[][4], const D3D12_RECT* _rect = NULL, uint32_t _num = 0);
		D3D12_RESOURCE_STATES setState(ID3D12GraphicsCommandList* _commandList, uint8_t _idx, D3D12_RESOURCE_STATES _state);

		TextureHandle m_texture[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		TextureHandle m_depth;
		Dxgi::SwapChainI* m_swapChain;
		void* m_nwh;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		D3D12_RESOURCE_STATES m_state;
		bool m_needPresent;
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
			bx::memSet(m_num, 0, sizeof(m_num) );
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
			D3D12_VERTEX_BUFFER_VIEW vbv[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1 /* instanced buffer */];
			D3D12_GPU_VIRTUAL_ADDRESS cbv;
			D3D12_DRAW_ARGUMENTS args;
		};

		struct DrawIndexedIndirectCommand
		{
			D3D12_VERTEX_BUFFER_VIEW vbv[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1 /* instanced buffer */];
			D3D12_INDEX_BUFFER_VIEW ibv;
			D3D12_GPU_VIRTUAL_ADDRESS cbv;
			D3D12_DRAW_INDEXED_ARGUMENTS args;
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

	struct TimerQueryD3D12
	{
		TimerQueryD3D12()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		void init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx);
		void end(uint32_t _idx);
		bool update();

		struct Query
		{
			uint32_t m_resultIdx;
			bool     m_ready;
			uint64_t m_fence;
		};

		struct Result
		{
			void reset()
			{
				m_begin     = 0;
				m_end       = 0;
				m_pending   = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
		};

		uint64_t m_frequency;

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];
		Query m_query[BGFX_CONFIG_MAX_VIEWS*4];

		ID3D12Resource*  m_readback;
		ID3D12QueryHeap* m_queryHeap;
		uint64_t* m_queryResult;
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryD3D12
	{
		OcclusionQueryD3D12()
			: m_control(BX_COUNTOF(m_handle) )
		{
		}

		void init();
		void shutdown();
		void begin(ID3D12GraphicsCommandList* _commandList, Frame* _render, OcclusionQueryHandle _handle);
		void end(ID3D12GraphicsCommandList* _commandList);
		void invalidate(OcclusionQueryHandle _handle);

		ID3D12Resource*  m_readback;
		ID3D12QueryHeap* m_queryHeap;
		OcclusionQueryHandle m_handle[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];
		uint64_t* m_result;
		bx::RingBufferControl m_control;
	};

} /* namespace d3d12 */ } // namespace bgfx

#endif // BGFX_RENDERER_D3D12_H_HEADER_GUARD

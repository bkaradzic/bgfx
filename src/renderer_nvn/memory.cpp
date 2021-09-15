/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "../bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "memory.h"
#include <nvn/nvn.h>

namespace bgfx { namespace nvn
{
	extern NVNdevice* g_nvnDevice;

	//
	//
	//

	AllocatorNVN g_allocatorNVN;

	void AllocatorNVN::init(size_t _poolSize)
	{
		m_mem = BX_ALLOC(g_allocator, _poolSize);
		m_size = _poolSize;
		m_allocator.Initialize(m_mem, m_size);

		m_totalFree = m_allocator.GetTotalFreeSize();
		m_largestFree = m_allocator.GetAllocatableSize();
		m_highwater = 0;
	}

	void AllocatorNVN::release()
	{
		// BBI-TODO: (tstump 3) check for leftover allocations? doesn't really matter since we release the entire heap below anyway.
		m_allocator.Finalize();
		BX_FREE(g_allocator, m_mem);
		m_mem = nullptr;
	}

	void* AllocatorNVN::realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line)
	{
		if (_ptr)
		{
			_ptr = m_allocator.Reallocate(_ptr, _size);
		}
		else
		{
			_ptr = _size ? m_allocator.Allocate(_size, _align ? _align : 1) : nullptr;
		}

		if (_size)
		{
			BX_ASSERT(_ptr != nullptr, "Allocation failed for size %d (free: %d largest: %d)", _size, m_totalFree, m_largestFree);
		}

		m_totalFree = m_allocator.GetTotalFreeSize();
		m_largestFree = m_allocator.GetAllocatableSize();
		m_highwater = bx::max(m_highwater, m_size - m_totalFree);

		return _ptr;
	}

	//
	//
	//

	void BufferNVN::create(uint32_t _size, void* _data, uint16_t _flags, uint32_t _stride, Usage _usage)
	{
		if (m_created)
		{
			BX_ASSERT(false, "Trying to create before destroy");
			destroy();
		}

		m_size = _size;
		m_flags = _flags;

		if (_stride > 0)
		{
			BX_ASSERT(_size % _stride == 0, "size was expected to be the full size in bytes, thus stride should evenly divide size");
		}

		int nvnFlags = 0;

		switch (_usage)
		{
		case Usage::IndexBuffer:
		case Usage::VertexBuffer:
		case Usage::GenericGpu:
			nvnFlags = NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT;
			break;
		case Usage::Upload:
			nvnFlags = NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_UNCACHED_BIT;
			break;
		case Usage::UniformBuffer:
			nvnFlags = NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT;
			break;
		default:
			BX_ASSERT(false, "Unknown usage"); break;
		}

		m_pool.Init(nullptr, _size, nvnFlags, g_nvnDevice);

		NVNbufferBuilder builder;
		nvnBufferBuilderSetDefaults(&builder);
		nvnBufferBuilderSetDevice(&builder, g_nvnDevice);
		nvnBufferBuilderSetStorage(&builder, m_pool.GetMemoryPool(), 0, _size);

		if (!nvnBufferInitialize(&m_buffer, &builder))
		{
			BX_ASSERT(false, "Failed to build the buffer");
		}

		m_gpuAddress = nvnBufferGetAddress(&m_buffer);

		if (_data)
		{
			update(0, _size, _data);
		}

		m_created = true;
	}

	void BufferNVN::update(uint32_t _offset, uint32_t _size, void* _data, bool /*_discard*/)
	{
		if (_data)
		{
			uint8_t* ptrAddr = static_cast<uint8_t*>(nvnBufferMap(&m_buffer));
			::memcpy(ptrAddr + _offset, _data, _size);
			nvnBufferFlushMappedRange(&m_buffer, _offset, _size);
		}
	}

} }

#endif // BGFX_CONFIG_RENDERER_NVN

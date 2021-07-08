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

	void BufferNVN::create(uint32_t _size, void* _data, uint16_t _flags, uint32_t _stride, Usage _usage)
	{
		BX_UNUSED(_stride);

		if (m_created)
		{
			BX_ASSERT(false, "Trying to create before destroy");
			destroy();
		}

		m_size = _size;
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
			const auto ptrAddr = static_cast<uint8_t*>(nvnBufferMap(&m_buffer));
			::memcpy(ptrAddr + _offset, _data, _size);
			nvnBufferFlushMappedRange(&m_buffer, _offset, _size);
		}
	}
} }

#endif // BGFX_CONFIG_RENDERER_NVN

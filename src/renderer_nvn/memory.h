/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_NVN_MEMORY_H_HEADER_GUARD
#define BGFX_NVN_MEMORY_H_HEADER_GUARD

#if BGFX_CONFIG_RENDERER_NVN

#include <array>
#include <atomic>
#include <nn/mem.h>
#include <nn/perf/perf_Profile.h>
#include <nn/util/util_BytePtr.h>
#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <vector>

namespace bgfx { namespace nvn
{
	struct AllocatorNVN : bx::AllocatorI
	{
		void init(size_t _poolSize);
		void release();

		void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) override;

		size_t m_size = 0;
		size_t m_totalFree = 0;
		size_t m_largestFree = 0;
		size_t m_highwater = 0;

		void* m_mem = nullptr;
		nn::mem::StandardAllocator m_allocator;
	};

	extern AllocatorNVN g_allocatorNVN;

	template<typename TPtr>
	TPtr atomicAlignedAllocOffset(std::atomic<TPtr>& _offset, const size_t _size, const size_t _alignment)
	{
		bool tryAgain = true;

		while (tryAgain)
		{
			TPtr prevValue = _offset;
			size_t alignedStart = nn::util::align_up(prevValue, _alignment);

			const bool succeeded = _offset.compare_exchange_weak(prevValue, alignedStart + _size);
			tryAgain = !succeeded;

			if (!tryAgain) {
				return static_cast<TPtr>(alignedStart);
			}
			else {
				// Atomic operation failed, try again
			}
		}

		BX_ASSERT(false, "Failed to allocate memory");
		return TPtr{};
	}

	struct CpuMeasureScope
	{
		CpuMeasureScope(const char* name)
		{
			NN_PERF_BEGIN_MEASURE_NAME(name);
		}

		CpuMeasureScope(CpuMeasureScope&&) = delete;
		CpuMeasureScope(const CpuMeasureScope&) = delete;

		~CpuMeasureScope()
		{
			NN_PERF_END_MEASURE();
		}
	};

	class MemoryPool {
	public:
		static const size_t g_MinimumPoolSize = NVN_MEMORY_POOL_STORAGE_GRANULARITY;

	private:
		ptrdiff_t m_CurrentWriteOffset = 0;
		NVNmemoryPool m_MemoryPool;
		void* m_OwnedMemory = nullptr;
		void* m_CpuMemory = nullptr;
		size_t m_Size = 0;
		int m_Flags = 0;
		bool m_SelfAllocatedMemory = false;

	public:
		MemoryPool()
			: m_CurrentWriteOffset(0),
			m_Size(0)
		{
		}

		~MemoryPool()
		{
			Shutdown();
		}

		void Init(void* pMemory, size_t size, int flags, NVNdevice* pDevice)
		{
			m_OwnedMemory = pMemory;
			m_SelfAllocatedMemory = false;

			if (size < g_MinimumPoolSize)
			{
				/* Set memory pool to minimum allowed size */
				size = g_MinimumPoolSize;
			}


			/* Align the pool size to the proper granularity */
			m_Size = nn::util::align_up(size, NVN_MEMORY_POOL_STORAGE_GRANULARITY);

			/*
			 * If a valid pointer is provided to a memory pool, then the pointer
			 * will be used instead of a new buffer, though with some differences
			 * between Windows and NX.
			 *
			 * On Windows, the buffer itself is not used, but its contents are
			 * copied into the memory that the driver itself allocates for the
			 * memory pool.
			 *
			 * On NX, the buffer is used as is as the backing memory for the pool
			 * and must be properly aligned with the proper granularity.
			 */
			if (m_OwnedMemory == NULL)
			{
				/* Allocate memory of the aligned size at the correct address alignment. */
				m_OwnedMemory = BX_ALIGNED_ALLOC(&g_allocatorNVN, m_Size, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
				m_SelfAllocatedMemory = true;
			}

			NVNmemoryPoolBuilder poolBuilder;
			nvnMemoryPoolBuilderSetDefaults(&poolBuilder);
			nvnMemoryPoolBuilderSetDevice(&poolBuilder, pDevice);
			nvnMemoryPoolBuilderSetFlags(&poolBuilder, flags);
			nvnMemoryPoolBuilderSetStorage(&poolBuilder, m_OwnedMemory, m_Size);

			if (nvnMemoryPoolInitialize(&m_MemoryPool, &poolBuilder) == NVN_FALSE)
			{
				BX_ASSERT(false, "Failed to initialize buffer memory pool");
			}

			if (!(flags & NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT))
			{
				m_CpuMemory = nvnMemoryPoolMap(&m_MemoryPool);
			}
			else
			{
				m_CpuMemory = nullptr;
			}

			m_Flags = flags;
		}

		void Reset()
		{
			m_CurrentWriteOffset = 0;
		}

		void Shutdown()
		{
			if (m_OwnedMemory != NULL)
			{
				m_Size = 0;
				m_CurrentWriteOffset = 0;

				nvnMemoryPoolFinalize(&m_MemoryPool);

				if (m_SelfAllocatedMemory)
				{
					BX_ALIGNED_FREE(&g_allocatorNVN, m_OwnedMemory, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
				}

				m_OwnedMemory = NULL;
			}
		}

		ptrdiff_t GetNewMemoryChunkOffset(size_t size, size_t alignment)
		{
			const ptrdiff_t resultOffset = m_CurrentWriteOffset;
			m_CurrentWriteOffset += nn::util::align_up(size, alignment);

			if ((static_cast<size_t>(resultOffset) + size) > m_Size)
			{
				BX_ASSERT(false, "Memory pool out of memory.");
			}

			return resultOffset;
		}

		NVNmemoryPool* GetMemoryPool()
		{
			return &m_MemoryPool;
		}

		void* GetMemory()
		{
			return m_CpuMemory;
		}

		size_t GetSize() const
		{
			return m_Size;
		}
	};

	struct BufferNVN
	{
		enum class Usage
		{
			UniformBuffer,
			Upload,
			GenericGpu,
			VertexBuffer,
			IndexBuffer
		};

		BufferNVN() = default;

		void create(uint32_t _size, void* _data, uint16_t _flags, uint32_t _stride, Usage _usage);
		void update(uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);

		void destroy()
		{
			if (m_created)
			{
				m_created = false;

				nvnBufferFinalize(&m_buffer);
				m_pool.Shutdown();

				m_size = 0;
			}
		}

		bool m_created = false;

		uint32_t m_size = 0;
		uint16_t m_flags = 0;

		MemoryPool m_pool;
		NVNbuffer m_buffer;
		NVNbufferAddress m_gpuAddress = 0;

		uint32_t getSize() const
		{
			return m_size;
		}

		void getData(NVNbufferAddress& _gpuAddress, void*& _cpuAddress, uint32_t _offset)
		{
			_cpuAddress = static_cast<uint8_t*>(m_pool.GetMemory()) + _offset;

			_gpuAddress = m_gpuAddress + _offset;
		}
	};

} }

#endif // BGFX_CONFIG_RENDERER_NVN

#endif // BGFX_NVN_MEMORY_H_HEADER_GUARD

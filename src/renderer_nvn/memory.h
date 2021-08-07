/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_NVN_MEMORY_H_HEADER_GUARD
#define BGFX_NVN_MEMORY_H_HEADER_GUARD

#include <array>
#include <atomic>
#include <nn/perf/perf_Profile.h>
#include <nn/util/util_BytePtr.h>
#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <vector>

#include "../ringbuffer.h"

namespace bgfx { namespace nvn
{
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
				m_OwnedMemory = BX_ALIGNED_ALLOC(g_allocator, m_Size, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
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
					BX_ALIGNED_FREE(g_allocator, m_OwnedMemory, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
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

		uint32_t getSize() const
		{
			return m_size;
		}

		void getData(NVNbufferAddress& _gpuAddress, void*& _cpuAddress, uint32_t _offset)
		{
			_cpuAddress = static_cast<uint8_t*>(m_pool.GetMemory()) + _offset;

			_gpuAddress = nvnBufferGetAddress(&m_buffer) + _offset;
		}
	};

	template<int TFlags, BufferNVN::Usage TUsage>
	struct RingBufferNVNAllocator {
		using Ptr = BufferNVN*;

		static Ptr allocate(const uint64_t _size) {
			auto nvnBuffer = BX_NEW(g_allocator, BufferNVN);
			nvnBuffer->create(static_cast<uint32_t>(_size), nullptr, TFlags, 1, TUsage);
			return nvnBuffer;
		}

		static void release(Ptr _buffer) {
			_buffer->destroy();
			BX_DELETE(g_allocator, _buffer);
		}
	};

	using UniformRingBuffer = bgfx::RingBuffer<BufferNVN*, NVNbufferAddress, void*, RingBufferNVNAllocator<0, BufferNVN::Usage::UniformBuffer>>;

	enum class MemoryPoolType
	{
		CommandBufferCommands,
		CommandBufferControls,
		Count
	};

	struct MemoryPoolSetup
	{
		size_t mSize = 0;
		int mFlags = 0;
	};

	static const std::array<MemoryPoolSetup, static_cast<size_t>(MemoryPoolType::Count)> MemoryPoolFlags =
	{
		MemoryPoolSetup{512, NVNmemoryPoolFlags::NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVNmemoryPoolFlags::NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT},
		MemoryPoolSetup{512, NVNmemoryPoolFlags::NVN_MEMORY_POOL_FLAGS_CPU_CACHED_BIT | NVNmemoryPoolFlags::NVN_MEMORY_POOL_FLAGS_GPU_NO_ACCESS_BIT}
	};

	class CommandMemoryPool
	{
	public:
		static constexpr size_t CommandListCount = 256;

		MemoryPool& operator[](const MemoryPoolType type)
		{
			BX_ASSERT(static_cast<int>(type) >= 0 && static_cast<int>(type) < static_cast<int>(MemoryPoolType::Count), "Invalid type");

			return m_Pools[static_cast<size_t>(type)];
		}

		void init(NVNdevice* _device)
		{
			for (int i = 0; i < MemoryPoolFlags.size(); i++)
			{
				const MemoryPoolSetup& poolSetup = MemoryPoolFlags[i];

				m_Pools[i].Init(nullptr, poolSetup.mSize * CommandListCount, poolSetup.mFlags, _device);
			}
		}

		void shutdown()
		{
			for (int i = 0; i < MemoryPoolFlags.size(); i++)
			{
				m_Pools[i].Shutdown();
			}
		}

		void reset()
		{
			for (int i = 0; i < MemoryPoolFlags.size(); i++)
			{
				m_Pools[i].Reset();
			}
		}

	private:
		std::array<MemoryPool, static_cast<size_t>(MemoryPoolType::Count)> m_Pools;
	};
} }

#endif // BGFX_NVN_MEMORY_H_HEADER_GUARD

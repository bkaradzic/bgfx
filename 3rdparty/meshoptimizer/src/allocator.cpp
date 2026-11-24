// This file is part of meshoptimizer library; see meshoptimizer.h for version/license details
#include "meshoptimizer.h"

#include <assert.h>
#include <stdint.h>

// allocator cache requires std::atomic and thread_local for thread safety; if these are not available, meshopt_setAllocatorCache is not supported
#if !defined(MESHOPTIMIZER_ALLOC_NOCACHE) && __cplusplus < 201103L && !(defined(_MSC_VER) && _MSC_VER >= 1900)
#define MESHOPTIMIZER_ALLOC_NOCACHE
#endif

#ifndef MESHOPTIMIZER_ALLOC_NOCACHE
#include <atomic>
#endif

#ifndef MESHOPTIMIZER_ALLOC_NOCACHE
namespace meshopt
{

struct GlobalCache
{
	std::atomic<uint64_t> blocks;
	char padding[120]; // avoid false sharing between threads

	void* data;
	size_t data_size;
	size_t block_size;
	uint64_t all_blocks;
	meshopt_Allocator::Storage fallback;
};

struct LocalCache
{
	void* block;
	size_t offset;
	uint64_t block_mask;
};

alignas(128) static GlobalCache gCache = {};
thread_local static LocalCache gCacheLocal;

static int cacheIndex(uint64_t mask)
{
	int index = -1;
	while (mask)
		mask >>= 1, index++;
	return index;
}

static void* MESHOPTIMIZER_ALLOC_CALLCONV cacheAllocate(size_t size)
{
	GlobalCache& global = gCache;
	LocalCache& local = gCacheLocal;

	// try to grab an available local block
	if (local.block == NULL && size < global.block_size && global.blocks.load(std::memory_order_relaxed) != 0)
	{
		uint64_t blocks = global.blocks.load(std::memory_order_relaxed);
		uint64_t mask = 0;

		do
		{
			// prefer last index for coherency, but settle for lowest bit otherwise
			mask = (blocks & local.block_mask) ? local.block_mask : blocks & (0 - blocks);
			// no available block, unlikely to get one soon
			if (blocks == 0)
				break;
			// reloads blocks on failure
		} while (!global.blocks.compare_exchange_weak(blocks, blocks & ~mask, std::memory_order_acquire, std::memory_order_relaxed));

		if (mask)
		{
			// extract block index from mask (must only have one bit set)
			int index = cacheIndex(mask);
			assert(mask == (1ull << index));

			local.block = static_cast<char*>(global.data) + index * global.block_size;
			local.block_mask = mask;
		}
	}

	// allocate from local block if any
	if (local.block && size < global.block_size && local.offset < global.block_size - size)
	{
		void* ptr = static_cast<char*>(local.block) + local.offset;
		local.offset += size ? size : 1;
		local.offset = (local.offset + 15) & ~size_t(15); // align future allocations to 16b
		return ptr;
	}

	return global.fallback.allocate(size);
}

static void MESHOPTIMIZER_ALLOC_CALLCONV cacheDeallocate(void* ptr)
{
	GlobalCache& global = gCache;
	LocalCache& local = gCacheLocal;

	// has our allocation come from the cache?
	if (global.data && ptr >= global.data && ptr < static_cast<char*>(global.data) + global.data_size)
	{
		// meshopt allocations are guaranteed to be stack ordered and thread local
		assert(local.block && ptr >= local.block && ptr < static_cast<char*>(local.block) + local.offset);
		local.offset = static_cast<char*>(ptr) - static_cast<char*>(local.block);

		// return local block to the pool
		if (local.offset == 0)
		{
			assert(local.block_mask);
			global.blocks.fetch_or(local.block_mask, std::memory_order_release);
			local.block = NULL;
			// keep block_mask as an affinity hint for the next allocation
		}
	}
	else
		global.fallback.deallocate(ptr);
}

} // namespace meshopt
#endif

#ifdef MESHOPTIMIZER_ALLOC_EXPORT
meshopt_Allocator::Storage& meshopt_Allocator::storage()
{
	static Storage s = {::operator new, ::operator delete };
	return s;
}
#endif

void meshopt_setAllocator(void* (MESHOPTIMIZER_ALLOC_CALLCONV* allocate)(size_t), void (MESHOPTIMIZER_ALLOC_CALLCONV* deallocate)(void*))
{
	assert(allocate && deallocate);

#ifndef MESHOPTIMIZER_ALLOC_NOCACHE
	assert(!meshopt::gCache.data); // changing allocation callbacks is prohibited if the cache is already set up
#endif

	meshopt_Allocator::Storage& s = meshopt_Allocator::storage();
	s.allocate = allocate;
	s.deallocate = deallocate;
}

#ifndef MESHOPTIMIZER_ALLOC_NOCACHE
void meshopt_setAllocatorCache(size_t block_count, size_t block_size)
{
	using namespace meshopt;

	assert(block_count <= 64);
	assert(block_count == 0 || block_size >= 16);

	meshopt_Allocator::Storage& allocator = meshopt_Allocator::storage();

	// reset prior global state
	// note: all previously allocated blocks must have been returned at this point; this is guaranteed by the absence of concurrent execution with meshopt_ functions
	if (gCache.data)
	{
		assert(gCache.blocks.load() == gCache.all_blocks);
		gCache.fallback.deallocate(gCache.data);
		gCache.data = NULL;
		gCache.data_size = 0;
		gCache.block_size = 0;
		gCache.all_blocks = 0;
		gCache.blocks.store(0);

		// reset global allocator
		allocator = gCache.fallback;
	}

	// individual allocations are aligned to 16 bytes, so we only use a 16-byte-aligned subset
	block_size &= ~size_t(15);

	// setup the cache if requested
	if (block_count && block_size)
	{
		size_t data_size = block_count > size_t(-1) / block_size ? size_t(-1) : block_count * block_size;

		// allocate a block for each thread and mark each block as available
		gCache.data = allocator.allocate(data_size);
		if (!gCache.data)
			return;

		gCache.data_size = data_size;
		gCache.block_size = block_size;
		gCache.all_blocks = (block_count >= 64) ? ~0ull : (1ull << block_count) - 1;
		gCache.blocks.store(gCache.all_blocks);
		gCache.fallback = allocator;

		allocator.allocate = cacheAllocate;
		allocator.deallocate = cacheDeallocate;
	}
}
#endif

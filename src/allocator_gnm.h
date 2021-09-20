#pragma once

#ifdef __ORBIS__

#include "bgfx_p.h"
#include <sys/dmem.h>
#include <gnm/gpumem.h>
#include <gnm/resourceregistration.h>
#include <utility>
#include <memory>
#include <functional>

// Set TRACK_RESOURCES to 1 if you want resource names to show up in the GPU Debugger. If you do this make sure to set Debug Settings/Graphics/PA Debug to Yes on your PS4 or it will crash
#define TRACK_RESOURCES		0

#if TRACK_RESOURCES
#include <vector>

struct MemAllocObj {
	uint32_t size;
	sce::Gnm::ResourceHandle resourceHandle;
	sce::Gnm::ResourceType resourceType;
};
#endif

class GnmAllocator
{
public:
	template<typename T>
	using Unique = std::unique_ptr<T, std::function<void(void*)>>;

	GnmAllocator();
	~GnmAllocator();

	void initialize(SceKernelMemoryType type,uint64_t size,bool bDeferRelease);
	void* allocate(uint32_t size, uint32_t alignment, sce::Gnm::ResourceType resourceType, const char *name);
	void release(void* pointer);
	void releaseAllMarked();

	template<typename T>
	Unique<T> allocateUnique(uint32_t size, uint32_t alignment, sce::Gnm::ResourceType resourceType, const char *name) {
		T* ptr = reinterpret_cast<T*>(allocate(size, alignment, resourceType, name));
		return Unique<T>(ptr, [this](void* ptr) {
			release(ptr);
		});
	}

	uint32_t getTotalActualSizeAllocated() const
	{
		return mTotalActualSizeAllocated; 
	}

	uint32_t getTotalActualSizeFree() const {
		return mMaxMemory - mTotalActualSizeAllocated;
	}
private:

	uint32_t mNumAllocs = 0;
	//uint32_t mTotalSizeAllocated;
	uint64_t mTotalActualSizeAllocated = 0;
	uint64_t mMaxMemory = 0;
	SceKernelMemoryType mType = SCE_KERNEL_MEMORY_TYPE_END;
	sce::Gnm::OwnerHandle mOwner = sce::Gnm::kInvalidOwnerHandle;
	bool mIsInitialized = false;
	bool mDeferRelease = true;

	tinystl::vector<std::pair<int,void*>> mDeferredReleasePointers;
#if TRACK_RESOURCES
	std::vector<MemAllocObj> mMemoryAllocations;
	tinystl::unordered_map<void*, sce::Gnm::ResourceHandle> mResourceHandlesToFree;
#endif
};

#endif

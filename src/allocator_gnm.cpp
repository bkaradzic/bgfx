
#ifdef __ORBIS__

#include "allocator_gnm.h"
#include <gnm/error.h>
#include <stdio.h>
#if TRACK_RESOURCES
#include <algorithm>
#endif

#define EXTRA_MEM_CHECKING 1
#define EXTRA_PRINTING 0

// Enables tracking of GNM Memory using MemPro by uncommenting this line:
//#define MCPE_MEMPRO_ENABLED_GNM
#ifdef MCPE_MEMPRO_ENABLED_GNM
#define MEMPRO_WAIT_FOR_CONNECT false
#define MEMPRO
#define PS4
#ifndef MCPE_MEMPRO_ENABLED
	// if Mempro is only desired for GNM allocations
#include "MemPro/MemPro.cpp"
#else
	// if Mempro is enabled globally with VMem
#include "MemPro/MemPro.h"
#endif
#endif

namespace
{
	const uint32_t GnmAllocatorAlignment = 1024 * 16;
	const uint32_t GnmAllocatorMask = GnmAllocatorAlignment - 1;

	bool isPowerOfTwo(uint32_t x) {
		return !(x & (x - 1)); // For example: Note 16 is 10000 and 16-1 == 15 which is 01111
	}

	int NUM_FRAMES_DEFER_RELEASE = 1; // Do not make const easier to tune real-time
}

GnmAllocator::GnmAllocator()
{
}

GnmAllocator::~GnmAllocator()
{
	releaseAllMarked();

#if BGFX_CONFIG_DEBUG
	if (mNumAllocs > 0) {

		bx::debugPrintf("Detected %d allocs not freed in ~GnmAllocator MemType %d\n", mNumAllocs, mType);

		for (int i = 0; i < mDeferredReleasePointers.size(); ++i) {

			void* pointer = mDeferredReleasePointers[i].second;
			bx::debugPrintf("Frames %d Adr %lx\n", mDeferredReleasePointers[i].first, uint64_t(pointer));

			SceKernelVirtualQueryInfo memInfo;
			int32_t retSys = sceKernelVirtualQuery(pointer, 0, &memInfo, sizeof(memInfo));
			BX_ASSERT(retSys == 0, "sceKernelVirtualQuery returned retSys error of %d", retSys);

			off_t offset = memInfo.offset;
			size_t len = size_t(memInfo.end) - size_t(memInfo.start);

			bx::debugPrintf("\tOffset %lx Size %d Name %s\n", offset, len, memInfo.name);

#if TRACK_RESOURCES
			auto iter = mResourceHandlesToFree.find(pointer);
			sce::Gnm::ResourceHandle resourceHandle = iter->second;

			char resourceName[200] = { 0 };
			retSys = sce::Gnm::getResourceName(resourceHandle, resourceName, sizeof(resourceName));
			BX_ASSERT(retSys == 0, "getResourceName returned retSys error of %d", retSys);

			sce::Gnm::ResourceType resourceType = sce::Gnm::kResourceTypeInvalid;
			retSys = sce::Gnm::getResourceType(resourceHandle, &resourceType);
			BX_ASSERT(retSys == 0, "getResourceType returned retSys error of %d", retSys);

			bx::debugPrintf("\tResourceType: %d ResourceName: %s\n", resourceType, resourceName);
#endif
		}
	}
#endif

	BX_ASSERT(mNumAllocs == 0, "Freeing GnmAllocator but still have allocations that memory will be corrupt Num = %d", mNumAllocs);
}

void GnmAllocator::initialize(SceKernelMemoryType type, uint64_t size, bool bDeferRelease)
{
	BX_ASSERT(false == mIsInitialized, "Do not call GnmAllocator::initialize twice");
	mNumAllocs = 0;
	//mTotalSizeAllocated = 0;
	mTotalActualSizeAllocated = 0;
	mMaxMemory = size;
	mType = type;
	sce::Gnm::registerOwner(&mOwner, "BGFX GNM");
	mIsInitialized = true;
	mDeferRelease = bDeferRelease;
	if (bDeferRelease)
		mDeferredReleasePointers.reserve(10);
}

void* GnmAllocator::allocate(uint32_t size, uint32_t alignment, sce::Gnm::ResourceType resourceType, const char* name)
{
	if (alignment > GnmAllocatorAlignment)
	{
		// Make sure this big alignment is a multiple of GnmAllocatorAlignment
		BX_ASSERT((alignment & GnmAllocatorMask) == 0, "Alignment must be multiple of GnmAllocatorMask");
		BX_ASSERT(isPowerOfTwo(alignment), "alignment must be power of 2");
	}
	else
	{
		alignment = GnmAllocatorAlignment;
	}

	off_t offset = 0;
	void* base = nullptr;

	// Ask for amount of memory that fits given our alignment restrictions (0 or 16k multiple/power of 2)
	uint32_t actualAllocationSize = (size + GnmAllocatorMask) & ~GnmAllocatorMask;
	BX_ASSERT((actualAllocationSize & GnmAllocatorMask) == 0, "actualAllocationSize must be multiple of GnmAllocatorMask");

	int32_t retSys = sceKernelAllocateDirectMemory(0,
		SCE_KERNEL_MAIN_DMEM_SIZE,
		actualAllocationSize,
		alignment, // alignment
		mType,
		&offset);
	BGFX_FATAL(retSys == 0, bgfx::Fatal::UnableToInitialize, "sceKernelAllocateDirectMemory failed retSys = %x size = %u mTotalActualSizeAllocated = %lu mMaxMemory = %lu",
		retSys, actualAllocationSize, mTotalActualSizeAllocated, mMaxMemory);
	//Map to virtual memory

#if EXTRA_MEM_CHECKING
	char szSizeName[32];
	snprintf_s(szSizeName, "%x %lx", actualAllocationSize, offset);
#else
	const char* szSizeName = "KERNELALLOC";
#endif
	retSys = sceKernelMapNamedDirectMemory(&base,
		actualAllocationSize,
		SCE_KERNEL_PROT_CPU_READ | SCE_KERNEL_PROT_CPU_WRITE | SCE_KERNEL_PROT_GPU_ALL,
		SCE_KERNEL_MAP_NO_COALESCE,						//flags
		offset,
		alignment,
		szSizeName);
	BGFX_FATAL(retSys == 0, bgfx::Fatal::UnableToInitialize, "sceKernelMapNamedDirectMemory failed retSys = %x", retSys);

#if TRACK_RESOURCES
	sce::Gnm::ResourceHandle resourceHandle = sce::Gnm::kInvalidResourceHandle;
	int32_t retSysRegisterResource = sce::Gnm::registerResource(&resourceHandle, mOwner, base, size, name, resourceType, 0);
	BX_ASSERT(retSysRegisterResource == 0, "Gnm::registerResource failed returned %d", retSysRegisterResource);
	BX_ASSERT(resourceHandle != sce::Gnm::kInvalidResourceHandle, "Gnm::registerResource made invalid resource handle");
	mResourceHandlesToFree[base] = resourceHandle;

	//Add the new memory allocation object data and sort by its size
	MemAllocObj memAlloc = { actualAllocationSize, resourceHandle, resourceType };
	auto it = std::lower_bound(mMemoryAllocations.begin(), mMemoryAllocations.end(), memAlloc, [](const MemAllocObj lhs, const MemAllocObj rhs) { return lhs.size > rhs.size; });
	mMemoryAllocations.insert(it, memAlloc);
#endif
	//mTotalSizeAllocated += size;
	mTotalActualSizeAllocated += actualAllocationSize;
	mNumAllocs++;

	BX_ASSERT(mTotalActualSizeAllocated <= mMaxMemory, "You have overflowed mMaxMemory of %lu MB but you could increase size by passing in different number to GnmAllocator::initialize", mMaxMemory / 1024 / 1024);

#if EXTRA_PRINTING
#if TRACK_RESOURCES
	bx::debugPrintf("GnmAllocator%d Alloc %x %x at %lx resourceType %d Handle %x\n", mType, size, actualAllocationSize, (uint64_t)base, resourceType, resourceHandle);
#else
	bx::debugPrintf("GnmAllocator%d Alloc %x %x at %lx resourceType %d\n", mType, size, actualAllocationSize, (uint64_t)base, resourceType);
#endif
#endif
#ifdef MCPE_MEMPRO_ENABLED_GNM
	MEMPRO_TRACK_ALLOC(base, actualAllocationSize);
#endif
	return base;
}

void GnmAllocator::release(void* pointer)
{
	BX_ASSERT(true == mIsInitialized, "Trying to call GnmAllocator::release but you didn't initialize GnmAllocator!");

	if (pointer == nullptr)
		return;

	// Defer N frames. This prevents crashes if GPU tries to consume memory that was freed.
	if (mDeferRelease)
	{
		mDeferredReleasePointers.push_back(std::make_pair(NUM_FRAMES_DEFER_RELEASE, pointer));
		return;
	}

#ifdef MCPE_MEMPRO_ENABLED_GNM
	MEMPRO_TRACK_FREE(pointer);
#endif

	SceKernelVirtualQueryInfo memInfo;
	int32_t retSys = sceKernelVirtualQuery(pointer, 0, &memInfo, sizeof(memInfo));
	BGFX_FATAL(retSys == 0, bgfx::Fatal::UnableToInitialize, "sceKernelVirtualQuery returned retSys error of %x", retSys);

	off_t offset = memInfo.offset;
	size_t len = (size_t)memInfo.end - (size_t)memInfo.start;

#if EXTRA_MEM_CHECKING
	uint32_t checkSizeIsMultipleOfAlignment = 0;
	off_t checkOffset = 0;
	sscanf_s(memInfo.name, "%x %lx", &checkSizeIsMultipleOfAlignment, &checkOffset);
	BX_ASSERT(checkSizeIsMultipleOfAlignment == len, "Failed sanity check: checkSizeIsMultipleOfAlignment == len");
	BX_ASSERT(checkOffset == offset, "Failed sanity check: checkOffset == offset");
#endif
	retSys = sceKernelReleaseDirectMemory(offset, len);
	BGFX_FATAL(retSys == 0, bgfx::Fatal::UnableToInitialize, "sceKernelReleaseDirectMemory failed returned %x", retSys);

#if TRACK_RESOURCES
	auto iter = mResourceHandlesToFree.find(pointer);
	sce::Gnm::ResourceHandle resourceHandle = iter->second;
	uint32_t retSysUnregisterResource = sce::Gnm::unregisterResource(resourceHandle);
	BX_ASSERT(retSysUnregisterResource == 0, "sce::Gnm::unregisterResource failed returned %d", retSysUnregisterResource);

	//Remove the memory allocation object data by its resource handle
	auto it = std::remove_if(mMemoryAllocations.begin(), mMemoryAllocations.end(), [resourceHandle](const MemAllocObj& memAlloc) { return memAlloc.resourceHandle == resourceHandle; });
	mMemoryAllocations.erase(it, mMemoryAllocations.end());

	mResourceHandlesToFree.erase(iter);

#if EXTRA_PRINTING
	bx::debugPrintf("GnmAllocator%d FREE %lx at %lx Handle %x\n", mType, len, (uint64_t)pointer, resourceHandle);
#endif
#else
#if EXTRA_PRINTING
	bx::debugPrintf("GnmAllocator%d FREE %lx at %lx\n", mType, len, (uint64_t)pointer);
#endif
#endif

	//mTotalSizeAllocated -= len;		// TODO - if put it back in, add extra field to memInfo.name
	mTotalActualSizeAllocated -= len;
	mNumAllocs--;
}

void GnmAllocator::releaseAllMarked()
{
	if (mDeferRelease)
	{
		for (int i = 0; i < mDeferredReleasePointers.size(); ) {
			if (mDeferredReleasePointers[i].first-- <= 0) {
				// This pointer's time is up for release.

				mDeferRelease = false;
				release(mDeferredReleasePointers[i].second);
				mDeferRelease = true;

				// Need to delete as we go. Order does not matter so do old "Swap with last element trick".
				int lastElement = mDeferredReleasePointers.size() - 1;
				BX_ASSERT(lastElement >= 0 && lastElement < mDeferredReleasePointers.size(), "lastElement out of vector bounds");
				mDeferredReleasePointers[i] = mDeferredReleasePointers[lastElement];
				mDeferredReleasePointers.pop_back();
				// Deliberately do not increment i
			}
			else {
				++i;
			}
		}
	}
}

#endif

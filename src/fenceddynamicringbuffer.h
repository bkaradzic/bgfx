/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#pragma once

#ifndef BGFX_FENCEDDYNAMICRINGBUFFER_H_HEADER_GUARD
#define BGFX_FENCEDDYNAMICRINGBUFFER_H_HEADER_GUARD

#include "fencedringbuffer.h"

#include <map>
#include <mutex>
#include <shared_mutex>

namespace bgfx {

	template<typename TBufferImpl, size_t sizeIncrementMultiplier = 2, bool enableDebugIntegrityChecks = false>
	class FencedDynamicRingBuffer {
		static_assert(sizeIncrementMultiplier > 1, "The increment multiplier should be greater than 1");
	public:
		using Ring = FencedRingBuffer<TBufferImpl, enableDebugIntegrityChecks>;
		using RingPtr = std::shared_ptr<Ring>;
		using RingRawPtr = Ring * ;
		using Allocation = typename Ring::ScopedAllocation;
		using BufferSize = typename Ring::BufferSize;
		using BufferOffset = typename Ring::BufferOffset;
		using Fence = typename Ring::Fence;
		using SharedMutex = std::shared_timed_mutex;

		FencedDynamicRingBuffer(typename TBufferImpl::Ptr bufferImpl, const BufferSize initialSize, const uint16_t ringLifetimeWithNoAllocation = 0)
			: m_initialSize(initialSize)
			, m_usedSize(0)
			, m_allocationSize(0)
			, m_ringLifetimeWithNoAllocation(ringLifetimeWithNoAllocation)
			, m_currentFence(0)
			, m_bufferImpl(bufferImpl) {
			BX_ASSERT(initialSize > 0, "Initial size should be greater than 0");

			_allocateNewRing(initialSize);
		}

		~FencedDynamicRingBuffer() {
			_releaseAllRings(); // To force TBufferImpl::release to be called
		}

		void setCurrentFenceValue(const Fence fenceValue) {
			std::lock_guard<SharedMutex> uniqueLock(m_accessLock);

			BX_ASSERT(m_allocationScopeCheck == 0, "setCurrentFenceValue is being executed with an allocation in progress in allocate. This will result in corruption");

			m_lastPageAllocatedFrom = nullptr;
			m_currentFence = fenceValue;

			for (auto&& existingRing : m_rings) {
				existingRing.second->setCurrentFenceValue(fenceValue);
			}
		}

		void setLastCompletedFenceValue(const Fence completedFenceValue) {
			std::lock_guard<SharedMutex> uniqueLock(m_accessLock);

			BX_ASSERT(m_allocationScopeCheck == 0, "setLastCompletedFenceValue is being executed with an allocation in progress in allocate. This will result in corruption");

			m_lastPageAllocatedFrom = nullptr;

			// Need to recompute the total size of allocation
			m_usedSize = 0;
			m_lastCompletedFenceValue = completedFenceValue;

			for (auto existingRing = m_rings.begin(); existingRing != m_rings.end();) {
				bool shouldRemove;

				existingRing->second->setLastCompletedFenceValue(completedFenceValue);

				auto ringUsedSize = existingRing->second->getAllocatedSpace();

				if (ringUsedSize == 0 && existingRing->first != m_initialSize) {
					// Remove the empty rings that aren't the first one if their lifetime is expired
					Fence lastAllocationForRing = existingRing->second->getLastAllocateFenceValue();
					if (m_ringLifetimeWithNoAllocation == 0 || (lastAllocationForRing == Ring::kInvalidFence) || (completedFenceValue - lastAllocationForRing) > m_ringLifetimeWithNoAllocation) {
						_releaseRingNoErase(existingRing->second);
						shouldRemove = true; // marked for removal
					}
					else {
						shouldRemove = false; // the ring should stay alive for now
					}
				}
				else {
					m_usedSize += ringUsedSize;
					shouldRemove = false; // the ring will stay allocated
				}

				if (shouldRemove) {
					existingRing = m_rings.erase(existingRing);
				}
				else {
					++existingRing;
				}
			}
		}

		BufferSize getSize() const { return m_allocationSize; }
		BufferSize getAllocatedSpace() const { return m_usedSize; }
		BufferSize getFreeSpace() const { return getSize() - getAllocatedSpace(); }
		uint16_t getRingLifetimeWithNoAllocation() const { return m_ringLifetimeWithNoAllocation; }
		Fence getCurrentFenceValue() const { return m_currentFence; }
		Fence getLastCompletedFenceValue() const { return m_lastCompletedFenceValue; }

		void setRingLifetimeWithNoAllocation(uint16_t lifetime) {
			std::lock_guard<SharedMutex> uniqueLock(m_accessLock);

			BX_ASSERT(m_allocationScopeCheck == 0, "setRingLifetimeWithNoAllocation is being executed with an allocation in progress in allocate. This will result in corruption");

			m_lastPageAllocatedFrom = nullptr;

			m_ringLifetimeWithNoAllocation = lifetime;

			// Make sure that we respect the contract by reevaluating the lifetime conditions
			if (m_lastCompletedFenceValue != Ring::kInvalidFence) {
				setLastCompletedFenceValue(m_lastCompletedFenceValue);
			}
		}

		Allocation allocate(const BufferSize size, const BufferOffset alignment) {
			struct ScopeCheck {
				ScopeCheck(std::atomic<size_t>& allocCount) : m_allocCount(allocCount) {
					m_allocCount++;
				}

				~ScopeCheck() {
					m_allocCount--;
				}
			private:
				std::atomic<size_t>& m_allocCount;
			};

			ScopeCheck scopeAlloc(m_allocationScopeCheck);

			BX_ASSERT(size > 0, "Trying to allocate an empty buffer");
			BX_ASSERT(alignment > 0, "Alignment of 0 isn't valid, should be at least 1");

			// Try a lock-less allocation from the previous page that had empty space
			RingRawPtr lastPageWithAllocation = m_lastPageAllocatedFrom;
			if (lastPageWithAllocation != nullptr) {
				auto allocation = lastPageWithAllocation->tryAllocate(size, alignment);
				if (allocation.has_value()) {
					m_usedSize += allocation.getTotalAllocationSize();
					return allocation;
				}
			}

			// Try first to locate a ring that wants to allocate that request.
			// Should work most of the time
			{
				std::shared_lock<SharedMutex> sharedLock(m_accessLock);

				const auto allocationFromExisting = _tryAllocateFromExistingRing(size, alignment);
				if (allocationFromExisting.has_value()) {
					return allocationFromExisting;
				}
			}

			// Couldn't find a spot. Expensive lookup for what's the next ring to add
			// We only keep at least one ring, so we can start at the next ring.
			{
				std::lock_guard<SharedMutex> uniqueLock(m_accessLock);

				// By the time we get the lock, another thread might have added a ring already, so need to look again
				const auto allocationFromExisting = _tryAllocateFromExistingRing(size, alignment);
				if (allocationFromExisting.has_value()) {
					return allocationFromExisting;
				}

				// Nope, still nothing
				BufferSize newRingSize = m_initialSize * sizeIncrementMultiplier;
				do {
					// We can always align starting at 0, so the only constraint is that the ring is big enough for the
					// allocation
					if (newRingSize >= size && m_rings.find(newRingSize) == m_rings.end()) {
						RingPtr newRing = _allocateNewRing(newRingSize);
						m_lastPageAllocatedFrom = newRing.get();
						auto allocation = newRing->tryAllocate(size, alignment);

						BX_ASSERT(allocation.has_value(), "The allocation into a newly created ring should have succeeded");
						m_usedSize += allocation.getTotalAllocationSize();

						return allocation;
					}

					newRingSize *= sizeIncrementMultiplier;
				} while (true);
			}
		}
	private:
		using RingMap = typename std::map<BufferSize, RingPtr>;

		std::atomic<RingRawPtr> m_lastPageAllocatedFrom = { nullptr };
		std::atomic<size_t> m_allocationScopeCheck = { 0 };

		const BufferSize m_initialSize;
		std::atomic<BufferSize> m_usedSize = 0;
		std::atomic<BufferSize> m_allocationSize = 0;
		RingMap m_rings; // Sorted by the size of the ring
		uint16_t m_ringLifetimeWithNoAllocation;
		Fence m_currentFence;
		Fence m_lastCompletedFenceValue;
		typename TBufferImpl::Ptr m_bufferImpl;

		SharedMutex m_accessLock;

		// Basically saying that if TBufferImpl::Ptr
		// - is a shared_ptr<T>, we want to do *T to get a T&
		// - is a T*, we want to do *T to get a T&
		// - is none of that, we just pass T by reference
		// -------------
		template <typename T> struct is_shared_ptr : std::false_type {};
		template <typename T> struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

		template<typename T, typename = typename std::enable_if<is_shared_ptr<T>::value, typename std::shared_ptr<T>::element_type>>
		typename T::element_type& getInternalBuffer(std::shared_ptr<typename T::element_type>& t) { return *t; }

		template<typename T, typename = typename std::enable_if<std::is_pointer<T>::value>>
		T& getInternalBuffer(T* t) { return *t; }

		template<typename T, typename = std::enable_if<!is_shared_ptr<T>::value, T>>
		T& getInternalBuffer(T& t) { return t; }

		auto& getInternalBuffer() {
			return getInternalBuffer<typename TBufferImpl::Ptr>(m_bufferImpl);
		}

		// -------------

		typename Ring::ScopedAllocation _tryAllocateFromExistingRing(const BufferSize size, const BufferOffset alignment) {
			// Try first to locate a ring that wants to allocate that request.
			// Should work most of the time
			for (auto&& existingRing : m_rings) {
				if (existingRing.second->getFreeSpace() < size) {
					continue;
				}

				auto allocation = existingRing.second->tryAllocate(size, alignment);
				if (allocation.has_value()) {
					m_usedSize += allocation.getTotalAllocationSize();

					m_lastPageAllocatedFrom = existingRing.second.get();

					return allocation;
				}
			}

			return Ring::ScopedAllocation();
		}

		RingPtr _allocateNewRing(const BufferSize size) {
			auto ring = std::make_shared<Ring>(getInternalBuffer().allocate(size));
			m_rings.insert(std::make_pair(size, ring));

			m_allocationSize += size;
			ring->setCurrentFenceValue(m_currentFence);

			return ring;
		}

		void _releaseRingNoErase(RingPtr& ring) {
			auto size = ring->getSize();
			getInternalBuffer().release(ring->getBuffer(), ring->getCurrentFenceValue());

			m_allocationSize -= size;
		}

		void _releaseAllRings() {
			for (auto&& existingRing : m_rings) {
				getInternalBuffer().release(existingRing.second->getBuffer(), existingRing.second->getCurrentFenceValue());
			}

			m_rings.clear();
		}
	};

}


#endif // BGFX_FENCEDDYNAMICRINGBUFFER_H_HEADER_GUARD

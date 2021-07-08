/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#pragma once

#ifndef BGFX_FENCEDRINGBUFFER_H_HEADER_GUARD
#define BGFX_FENCEDRINGBUFFER_H_HEADER_GUARD

#include <queue>
#include <atomic>

namespace bgfx {

	template<typename TBufferImpl, bool enableDebugIntegrityChecks = false>
	class FencedRingBuffer {
	public:
		using Fence = uint64_t;
		using BufferSize = uint64_t;
		using BufferOffset = uint64_t;

		static const Fence kInvalidFence = ~0;

		class ScopedAllocation {
			friend FencedRingBuffer<TBufferImpl, enableDebugIntegrityChecks>;
		private:
			ScopedAllocation(typename TBufferImpl::BufferPtr& buffer, const BufferOffset offset, const BufferSize size, const BufferSize alignmentPrefixSize, const Fence fenceValue)
				: m_valid(true), m_buffer(buffer), m_offset(offset), m_size(size), m_alignmentPrefixSize(alignmentPrefixSize), m_fenceValue(fenceValue) { }

		public:
			ScopedAllocation() : m_valid(false) { }

			typename TBufferImpl::BufferEntry getAllocation() const { return m_buffer->getAllocation(m_offset, m_size); }
			void resetAllocation() { m_buffer->resetAllocation(m_offset, m_size); }

			BufferSize getSize() const { return m_size; }
			BufferOffset getOffset() const { return m_offset; }
			BufferSize getTotalAllocationSize() const { return m_size + m_alignmentPrefixSize; }

			Fence getFenceValue() const { return m_fenceValue; }

			bool has_value() const { return m_valid; }

		private:

			typename TBufferImpl::BufferPtr m_buffer;
			const bool m_valid;
			const BufferOffset m_offset;
			const BufferSize m_size; // Used size that starts from m_offset in the buffer and is m_size long
			const BufferSize m_alignmentPrefixSize; // Because of alignment, size of the allocation before m_offset that was added for padding
			const Fence m_fenceValue;
		};

		FencedRingBuffer(typename TBufferImpl::BufferPtr buffer)
			: m_buffer(buffer)
			, m_size(buffer->getSize())
			, m_usedSize(0)
			, m_currentFence(0)
			, m_headRange(0, m_size)
			, m_tailRange(m_size, 0)
			, m_currentAllocationScopeSize(0)
			, m_currentAllocationId(0) {
		}

		typename TBufferImpl::BufferPtr getBuffer() const { return m_buffer; }
		typename TBufferImpl::BufferPtr getBuffer() { return m_buffer; }

		BufferSize getSize() const { return m_size; }
		BufferSize getFreeSpace() const { return _getSpaceLeft(); }
		BufferSize getAllocatedSpace() const { return m_usedSize; }
		Fence getCurrentFenceValue() const { return m_currentFence; }
		Fence getLastAllocateFenceValue() const { return mLastFenceWithAllocation; }

		// /!\ tryAllocate is thread safe if called concurrently with other tryAllocate on the same object
		// /!\ it is NOT thread safe when calling other operations like setCurrentFenceValue and setLastCompletedFenceValue
		ScopedAllocation tryAllocate(const BufferSize size, const BufferOffset alignment) {
			BX_ASSERT(size > 0, "Cannot allocate a buffer of size 0");

			if (size > _getSpaceLeft()) {
				return ScopedAllocation();
			}

			m_currentAllocationId++;

			auto tentativeAllocation = m_headRange.tryAllocate(size, alignment);
			if (!tentativeAllocation.has_value()) {
				tentativeAllocation = m_tailRange.tryAllocate(size, alignment);
			}

			if (!tentativeAllocation.has_value()) {
				return ScopedAllocation();
			}

			const BufferOffset startOffset = tentativeAllocation->m_dataOffset;
			const BufferSize alignmentPrefix = tentativeAllocation->m_offsetPrefix;

			const BufferSize totalAllocationSize = size + alignmentPrefix;

			m_usedSize += totalAllocationSize;
			m_currentAllocationScopeSize += totalAllocationSize;

			// Not atomic, but it'll possibly just set the same value from multiple threads at the same time
			mLastFenceWithAllocation = m_currentFence;

			return ScopedAllocation(m_buffer, startOffset, size, alignmentPrefix, m_currentFence);
		}

		void setCurrentFenceValue(const Fence fenceValue) {
			BX_ASSERT(fenceValue >= m_currentFence, "The new fence value should be greater than the old one");
			const uint16_t oldAllocId = m_currentAllocationId;

			_checkIntegrity();

			_finalizeScope();
			m_currentFence = fenceValue;

			BX_ASSERT(oldAllocId == m_currentAllocationId, "Another allocation (via tryAllocate) happened during setCurrentFenceValue. This isn't allowed as this class is lockless for performance reasons");
			BX_UNUSED(oldAllocId);
		}

		void setLastCompletedFenceValue(const Fence completedFenceValue) {
			BX_ASSERT(completedFenceValue <= m_currentFence, "The completed fence value %d should be <= than the current fence value %d", completedFenceValue, m_currentFence);
			const uint16_t oldAllocId = m_currentAllocationId;

			_checkIntegrity();

			_finalizeScope();
			_releaseObsoleteAllocations(completedFenceValue);

			BX_ASSERT(oldAllocId == m_currentAllocationId, "Another allocation (via tryAllocate) happened within a call to setLastCompletedFenceValue. This isn't allowed as this class is lockless for performance reasons");
			BX_UNUSED(oldAllocId);
		}

	private:
		struct LinearAllocation {
			bool m_valid = false;
			BufferSize m_offsetPrefix = 0;
			BufferOffset m_dataOffset = 0;
		};

		struct LinearRange {
			BufferOffset m_offset;
			BufferSize m_size;

			std::atomic<BufferOffset> m_currentOffset;

			LinearRange(const BufferOffset offset, const BufferSize size)
				: m_offset(offset)
				, m_size(size)
				, m_currentOffset(offset) {
			}

			void reset(const BufferOffset newOffset, const BufferSize newSize) {
				m_offset = newOffset;
				m_currentOffset = newOffset;

				m_size = newSize;
			}

			LinearAllocation tryAllocate(const BufferSize size, const BufferSize alignment) {
				// early out
				if (size > getApproxFree()) {
					return { false, 0, 0 };
				}

				while (true) {
					// The value might change while computing the alignment, so just keep trying
					// it'll eventually end when no space is left if that specific thread keep losing

					BufferOffset currentAllocatedStartOffset = m_currentOffset;
					const BufferOffset alignedStartOffset = (currentAllocatedStartOffset + (alignment - 1)) & ~(alignment - 1);
					const BufferOffset alignmentPrefix = alignedStartOffset - currentAllocatedStartOffset;

					const BufferOffset finalOffsetAfterAllocation = currentAllocatedStartOffset + alignmentPrefix + size;
					if (finalOffsetAfterAllocation > m_offset + m_size) {
						// Not enough space left
						return { false, 0, 0 };
					}
					else if (m_currentOffset.compare_exchange_weak(currentAllocatedStartOffset, finalOffsetAfterAllocation)) {
						return LinearAllocation{ true, alignmentPrefix, alignedStartOffset };
					}
				}
			}

			BufferSize getApproxUsed() const {
				return m_currentOffset - m_offset;
			}

			BufferSize getApproxFree() const {
				return m_size - getApproxUsed();
			}
		};

		void _finalizeScope() {
			if (m_currentAllocationScopeSize > 0) {
				if (m_headRange.m_offset == 0) {
					// H H H H . . . .
					BX_ASSERT(m_tailRange.m_offset == m_headRange.m_size, "Ring corruption: head is at the beginning but tail isn't directly following");
					BX_ASSERT(m_tailRange.m_size == 0, "Ring corruption: when not wrapping around, tail should be empty");
					BX_ASSERT(m_currentAllocationScopeSize == m_headRange.getApproxUsed(), "Ring corruption: the allocated size in this scenario should be only coming from head");

					const BufferOffset newHeadOffset = m_currentAllocationScopeSize;

					m_allocations.push(ScopedAllocation(m_buffer, m_headRange.m_offset, m_currentAllocationScopeSize, 0, m_currentFence));

					m_headRange.reset(newHeadOffset, (m_tailRange.m_offset + m_tailRange.m_size) - newHeadOffset);
					m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
				}
				else if (m_headRange.m_offset <= m_tailRange.m_offset) {
					// . . H H H T T .
					BX_ASSERT(m_headRange.getApproxUsed() + m_tailRange.getApproxUsed() == m_currentAllocationScopeSize, "Ring corruption: the allocated size of head+tail doesn't match the scope");
					if (m_tailRange.getApproxUsed() > 0) {
						// Skip over head
						m_allocations.push(ScopedAllocation(m_buffer, m_headRange.m_offset, m_headRange.m_size, 0, m_currentFence));
						m_allocations.push(ScopedAllocation(m_buffer, m_tailRange.m_offset, m_tailRange.getApproxUsed(), 0, m_currentFence));

						const BufferOffset newHeadOffset = m_tailRange.m_offset + m_tailRange.getApproxUsed();

						m_headRange.reset(newHeadOffset, m_tailRange.m_size - m_tailRange.getApproxUsed());
						m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
					}
					else if (m_headRange.getApproxUsed() > 0) {
						// Tail hasn't been touched, so just consider the head
						m_allocations.push(ScopedAllocation(m_buffer, m_headRange.m_offset, m_headRange.getApproxUsed(), 0, m_currentFence));

						const BufferOffset newHeadOffset = m_headRange.m_offset + m_headRange.getApproxUsed();

						m_headRange.reset(newHeadOffset, m_tailRange.m_offset + m_tailRange.m_size - newHeadOffset);
						m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
					}
					else {
						BX_ASSERT(false, "Something was supposed to be allocated via m_currentAllocationScopeSize but nothing was found in head or tail");
					}
				}
				else if (m_tailRange.m_offset <= m_headRange.m_offset) {
					// T T . . H H H H
					BX_ASSERT(m_headRange.m_offset + m_headRange.m_size == m_size, "Ring corruption: the ring wraps around but head isn't to the end");
					BX_ASSERT(m_currentAllocationScopeSize == m_headRange.getApproxUsed() + m_tailRange.getApproxUsed(), "Ring corruption: the allocated size doesn't match Head + Tail");

					if (m_tailRange.getApproxUsed() == 0 && m_headRange.getApproxFree() > 0) {
						// We didn't consume all of the space in head, tail is unchanged
						m_allocations.push(ScopedAllocation(m_buffer, m_headRange.m_offset, m_currentAllocationScopeSize, 0, m_currentFence));

						m_headRange.reset(m_headRange.m_offset + m_currentAllocationScopeSize, m_headRange.m_size - m_currentAllocationScopeSize);
					}
					else {
						// Something was allocated in tail or head is full, force the full wrap around
						if (m_headRange.m_size > 0) {
							const BufferSize spaceSkipped = m_headRange.m_size - m_headRange.getApproxUsed();
							m_usedSize += spaceSkipped;

							m_allocations.push(ScopedAllocation(m_buffer, m_headRange.m_offset, m_headRange.m_size, 0, m_currentFence));
						}

						if (m_tailRange.getApproxUsed() > 0) {
							m_allocations.push(ScopedAllocation(m_buffer, 0, m_tailRange.getApproxUsed(), 0, m_currentFence));
						}

						if (m_tailRange.m_offset == 0) {
							// Head at the end, Tail at the beginning, so we need to go through tail
							m_headRange.reset(m_tailRange.getApproxUsed(), m_tailRange.m_size - m_tailRange.getApproxUsed());
							m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
						}
						else {
							// Head at the end, tail at the end, no more space left
							m_headRange.reset(m_tailRange.m_offset + m_tailRange.m_size - m_tailRange.getApproxFree(), m_tailRange.getApproxFree());
							m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
						}
					}
				}
				else {
					BX_ASSERT(false, "Ring corruption: the alignment of Head & Tail didn't match an expected configuration");
				}

				m_currentAllocationScopeSize = 0;

				_checkIntegrity();
			}
		}

		BufferSize _getSpaceLeft() const { return m_headRange.getApproxFree() + m_tailRange.getApproxFree(); }

		void _releaseObsoleteAllocations(const Fence completedFenceValue) {
			_checkIntegrity();

			while (m_allocations.size() > 0) {
				ScopedAllocation& head = m_allocations.front();
				if (head.getFenceValue() <= completedFenceValue) {
					m_allocations.pop();

					head.resetAllocation();

					BufferSize allocationSize = head.getTotalAllocationSize();
					m_usedSize -= allocationSize;

					if (m_tailRange.m_offset == m_size) {
						BX_ASSERT(m_tailRange.m_size == 0, "Ring corruption: The tail is at the end of the ring but has a non zero size");
						BX_ASSERT(head.getOffset() == 0, "Ring corruption: expected an allocation at the head of the ring");
						BX_ASSERT(m_tailRange.getApproxUsed() == 0, "Ring corruption: expected the tail range to be empty");

						m_tailRange.reset(head.getOffset(), head.getSize());
					}
					else {
						if (m_tailRange.m_offset == m_headRange.m_offset + m_headRange.m_size) {
							BX_ASSERT((m_headRange.m_offset + m_headRange.m_size) == head.getOffset(), "Ring corruption: expected an allocation contiguous to current head+size");
							BX_ASSERT(allocationSize <= m_size - (m_headRange.m_offset + m_headRange.m_size), "Ring corruption: trying to release more than the size left");
							BX_ASSERT(m_tailRange.getApproxUsed() == 0, "Ring corruption: the tail should have been empty");

							m_headRange.m_size += allocationSize;
							m_tailRange.reset(m_headRange.m_offset + m_headRange.m_size, 0);
						}
						else {
							BX_ASSERT(m_tailRange.m_offset + m_tailRange.m_size == head.getOffset(), "Ring corruption: the allocation doesn't match the expected offset");
							m_tailRange.m_size += allocationSize;
						}
					}
				}
				else {
					// Reached the end of the allocation until that fence
					break;
				}

				_checkIntegrity();
			}

			if (m_allocations.size() == 0) {
				BX_ASSERT(m_usedSize == 0, "Used size should have been 0");

				// Nothing allocated, reset the indices to have a better allocation
				m_headRange.reset(0, m_size);
				m_tailRange.reset(m_size, 0);
			}

			_checkIntegrity();
		}

		void _checkIntegrity() {
			if (enableDebugIntegrityChecks) {
				std::queue<ScopedAllocation> copy = m_allocations;

				BufferSize expectedUsedSize = 0;

				bool isFirst = true;

				while (!copy.empty()) {
					auto allocation = copy.front();

					if (isFirst) {
						isFirst = false;

						BX_ASSERT(
							(allocation.getOffset() == 0 && (m_tailRange.m_offset == m_size || m_tailRange.m_offset == 0)) ||
							(allocation.getOffset() == (m_tailRange.m_offset + m_tailRange.m_size)),
							"The first freeable allocation is supposed to be next to tail");
					}

					BX_ASSERT(allocation.getTotalAllocationSize() > 0, "Scope with empty allocation isn't valid");

					expectedUsedSize += allocation.getTotalAllocationSize();
					copy.pop();
				}

				expectedUsedSize += m_headRange.getApproxUsed() + m_tailRange.getApproxUsed();

				BX_ASSERT(expectedUsedSize == m_usedSize, "Allocations size mismatch");
			}
		}

		typename TBufferImpl::BufferPtr m_buffer;
		const BufferSize m_size;
		std::queue<ScopedAllocation> m_allocations;
		std::atomic<BufferSize> m_currentAllocationScopeSize;

		LinearRange m_headRange;
		LinearRange m_tailRange;
		std::atomic<BufferSize> m_usedSize;

		// Will wrap around, it's fine
		std::atomic<uint16_t> m_currentAllocationId;

		Fence m_currentFence;
		Fence mLastFenceWithAllocation = kInvalidFence;
	};
}

#endif // BGFX_FENCEDRINGBUFFER_H_HEADER_GUARD

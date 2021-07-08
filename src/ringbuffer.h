/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_RINGBUFFER_H_HEADER_GUARD
#define BGFX_RINGBUFFER_H_HEADER_GUARD

#include "fenceddynamicringbuffer.h"

namespace bgfx
{
	template<typename TBuffer>
	struct RingBufferAllocator
	{
		using Ptr = TBuffer * ;

		static Ptr allocate(const uint64_t _size)
		{
			return TBuffer::allocate(_size);
		}

		static void release(Ptr _buffer)
		{
			TBuffer::release(_buffer);
		}
	};

	template<typename TBuffer, typename TGPUAddress, typename TCPUAddress, typename TAllocator = RingBufferAllocator<TBuffer>>
	class RingBuffer
	{
	public:
		struct Location {
			uint32_t m_offset = 0;
			uint32_t m_size = 0;
			TBuffer m_buffer = {};

			TGPUAddress m_gpuAddr = {};
			TCPUAddress m_cpuAddr = {};
		};

	private:
		class RingBufferResourceAllocator;
		class RingBufferResourceAllocator
		{
		public:
			using Ptr = RingBufferResourceAllocator&;
			using BufferEntry = Location;

			class Buffer {
			public:
				Buffer(TBuffer buffer)
					: m_buffer(buffer)
				{

				}

				TBuffer getBuffer()
				{
					return m_buffer;
				}

				uint32_t getSize() const
				{
					if constexpr (std::is_pointer<TBuffer>::value)
					{
						return m_buffer->getSize();
					}
					else
					{
						return m_buffer.getSize();
					}
				}

				void resetAllocation(const uint64_t offset, const uint64_t size)
				{
					BX_UNUSED(offset, size);
				}

				Location getAllocation(const uint64_t _offset, const uint64_t _size)
				{
					Location result = {};
					result.m_offset = (uint32_t)_offset;
					result.m_size = (uint32_t)_size;
					result.m_buffer = m_buffer;

					if (std::is_pointer<TBuffer>::value)
					{
						m_buffer->getData(result.m_gpuAddr, result.m_cpuAddr, result.m_offset);
					}
					else
					{
						m_buffer.getData(result.m_gpuAddr, result.m_cpuAddr, result.m_offset);
					}

					return result;
				}
			private:
				TBuffer m_buffer;
			};

			using BufferPtr = typename std::shared_ptr<Buffer>;

			RingBufferResourceAllocator() = default;

			BufferPtr allocate(const uint64_t _size)
			{
				return std::make_shared<Buffer>(TAllocator::allocate(_size));
			}

			void release(BufferPtr _buffer, const uint64_t _lastUsedFence)
			{
				TAllocator::release(_buffer->getBuffer());
			}
		};

		using RingBufferImpl = bgfx::FencedDynamicRingBuffer<RingBufferResourceAllocator>;

	public:
		RingBuffer(const size_t _initialSize)
			: m_ringsAllocator()
			, m_rings(m_ringsAllocator, _initialSize, 64/*ring lifetime with no alloc*/)
		{

		}

		Location allocate(uint16_t _alignment, uint32_t _size) {
			return m_rings.allocate(_size, _alignment).getAllocation();
		}
		
		Location upload(uint16_t _alignment, uint32_t _offset, uint32_t _size, void* _data) {
			auto allocationTarget = allocate(_alignment, _size);
			if (_data != nullptr) memcpy(allocationTarget.m_cpuAddr, ((uint8_t*)_data) + _offset, _size);

			return allocationTarget;
		}

		void setCurrentFence(uint64_t fence) {
			m_rings.setCurrentFenceValue(fence);
		}

		void setCompletedFence(uint64_t fence) {
			m_rings.setLastCompletedFenceValue(fence);
		}

	private:
		RingBufferResourceAllocator m_ringsAllocator;
		RingBufferImpl m_rings;
	};

} // namespace bgfx

#endif // BGFX_RINGBUFFER_H_HEADER_GUARD

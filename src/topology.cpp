/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/debug.h>
#include <bx/allocator.h>
#include <bx/radixsort.h>

#include "config.h"
#include "topology.h"

namespace bgfx
{
	template<typename IndexT>
	static uint32_t topologyConvertTriListFlipWinding(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices)
	{
		if (NULL == _dst)
		{
			return _numIndices;
		}

		IndexT* dst = (IndexT*)_dst;
		IndexT* end = &dst[_dstSize/sizeof(IndexT)];
		for (uint32_t ii = 0; ii < _numIndices && dst < end; ii += 3, dst += 3)
		{
			const IndexT* tri = &_indices[ii];
			IndexT i0 = tri[0], i1 = tri[1], i2 = tri[2];

			dst[0] = i0;
			dst[1] = i2;
			dst[2] = i1;
		}

		return _numIndices;
	}

	template<typename IndexT, typename SortT>
	static uint32_t topologyConvertTriListToLineList(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices, IndexT* _temp, SortT* _tempSort)
	{
		// Create all line pairs and sort indices.
		IndexT* dst = _temp;
		for (uint32_t ii = 0; ii < _numIndices; ii += 3)
		{
			const IndexT* tri = &_indices[ii];
			IndexT i0 = tri[0], i1 = tri[1], i2 = tri[2];

			if (i0 > i1) { bx::xchg(i0, i1); }
			if (i1 > i2) { bx::xchg(i1, i2); }
			if (i0 > i1) { bx::xchg(i0, i1); }
			BX_CHECK(i0 < i1 && i1 < i2, "");

			dst[0] = i0; dst[1] = i1;
			dst[2] = i1; dst[3] = i2;
			dst[4] = i0; dst[5] = i2;
			dst += 6;
		}

		// Sort all line pairs.
		SortT* sorted = (SortT*)_temp;
		bx::radixSort(sorted, _tempSort, _numIndices);

		uint32_t num = 0;

		// Remove all line pair duplicates.
		if (NULL == _dst)
		{
			SortT last = sorted[0];
			for (uint32_t ii = 1; ii < _numIndices; ++ii)
			{
				if (last != sorted[ii])
				{
					num += 2;
					last = sorted[ii];
				}
			}
			num += 2;
		}
		else
		{
			dst = (IndexT*)_dst;
			IndexT* end = &dst[_dstSize/sizeof(IndexT)];
			SortT  last = sorted[0];
			for (uint32_t ii = 1; ii < _numIndices && dst < end; ++ii)
			{
				if (last != sorted[ii])
				{
					union Un { SortT key; struct { IndexT i0; IndexT i1; } u16; } un = { last };
					dst[0] = un.u16.i0;
					dst[1] = un.u16.i1;
					dst += 2;
					last = sorted[ii];
				}
			}

			if (dst < end)
			{
				union Un { SortT key; struct { IndexT i0; IndexT i1; } u16; } un = { last };
				dst[0] = un.u16.i0;
				dst[1] = un.u16.i1;
				dst += 2;
			}

			num = uint32_t(dst - (IndexT*)_dst);
		}

		return num;
	}

	template<typename IndexT, typename SortT>
	static uint32_t topologyConvertTriListToLineList(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices, bx::AllocatorI* _allocator)
	{
		IndexT* temp     = (IndexT*)BX_ALLOC(_allocator, _numIndices*2*sizeof(IndexT)*2);
		SortT*  tempSort = (SortT*)&temp[_numIndices*2];
		uint32_t num = topologyConvertTriListToLineList(_dst, _dstSize, _indices, _numIndices, temp, tempSort);
		BX_FREE(_allocator, temp);
		return num;
	}

	template<typename IndexT>
	static uint32_t topologyConvertTriStripToTriList(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices)
	{
		IndexT* dst = (IndexT*)_dst;
		IndexT* end = &dst[_dstSize/sizeof(IndexT)];

		for (uint32_t ii = 0, num = _numIndices-2; ii < num && dst < end; ++ii)
		{
			IndexT i0 = _indices[ii+0];
			IndexT i1 = _indices[ii+1];
			IndexT i2 = _indices[ii+2];
			if (i0 != i1
			&&  i1 != i2)
			{
				dst[0] = i0;
				dst[1] = i1;
				dst[2] = i2;
				dst += 3;
			}
		}

		return uint32_t(dst - (IndexT*)_dst);
	}

	template<typename IndexT>
	static uint32_t topologyConvertLineStripToLineList(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices)
	{
		IndexT* dst = (IndexT*)_dst;
		IndexT* end = &dst[_dstSize/sizeof(IndexT)];

		IndexT i0 = _indices[0];

		for (uint32_t ii = 1; ii < _numIndices && dst < end; ++ii)
		{
			IndexT i1 = _indices[ii];
			if (i0 != i1)
			{
				dst[0] = i0;
				dst[1] = i1;
				dst += 2;

				i0 = i1;
			}
		}

		return uint32_t(dst - (IndexT*)_dst);
	}

	uint32_t topologyConvert(TopologyConvert::Enum _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32, bx::AllocatorI* _allocator)
	{
		switch (_conversion)
		{
		case TopologyConvert::TriStripToTriList:
			if (_index32)
			{
				return topologyConvertTriStripToTriList(_dst, _dstSize, (const uint32_t*)_indices, _numIndices);
			}

			return topologyConvertTriStripToTriList(_dst, _dstSize, (const uint16_t*)_indices, _numIndices);

		case TopologyConvert::TriListFlipWinding:
			if (_index32)
			{
				return topologyConvertTriListFlipWinding(_dst, _dstSize, (const uint32_t*)_indices, _numIndices);
			}

			return topologyConvertTriListFlipWinding(_dst, _dstSize, (const uint16_t*)_indices, _numIndices);

		case TopologyConvert::TriListToLineList:
			if (NULL == _allocator)
			{
				return 0;
			}

			if (_index32)
			{
				return topologyConvertTriListToLineList<uint32_t, uint64_t>(_dst, _dstSize, (const uint32_t*)_indices, _numIndices, _allocator);
			}

			return topologyConvertTriListToLineList<uint16_t, uint32_t>(_dst, _dstSize, (const uint16_t*)_indices, _numIndices, _allocator);

		case TopologyConvert::LineStripToLineList:
			if (_index32)
			{
				return topologyConvertLineStripToLineList(_dst, _dstSize, (const uint32_t*)_indices, _numIndices);
			}

			return topologyConvertLineStripToLineList(_dst, _dstSize, (const uint16_t*)_indices, _numIndices);

		default:
			break;
		}

		return 0;
	}

} //namespace bgfx

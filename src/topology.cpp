/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/allocator.h>
#include <bx/debug.h>
#include <bx/math.h>
#include <bx/sort.h>
#include <bx/uint32_t.h>

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

	inline bool isEven(uint32_t _num)
	{
		return 0 == (_num & 1);
	}

	template<typename IndexT>
	static uint32_t topologyConvertTriStripFlipWinding(void* _dst, uint32_t _dstSize, const IndexT* _indices, uint32_t _numIndices)
	{
		const uint32_t numIndices = isEven(_numIndices) ? _numIndices + 1 : _numIndices;

		if (NULL != _dst)
		{
			return numIndices;
		}

		IndexT* dst = (IndexT*)_dst;
		IndexT* end = &dst[_dstSize/sizeof(IndexT)];

		if (isEven(_numIndices) )
		{
			*dst++ = _indices[_numIndices-1];
		}

		for (uint32_t ii = 1; ii <= _numIndices && dst < end; ++ii)
		{
			*dst++ = _indices[_numIndices - ii];
		}

		return numIndices;
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

			dst[1] = i0; dst[0] = i1;
			dst[3] = i1; dst[2] = i2;
			dst[5] = i0; dst[4] = i2;
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

			{
				union Un { SortT key; struct { IndexT i0; IndexT i1; } u16; } un = { sorted[0] };
				dst[0] = un.u16.i0;
				dst[1] = un.u16.i1;
				dst += 2;
			}

			for (uint32_t ii = 1; ii < _numIndices && dst < end; ++ii)
			{
				if (last != sorted[ii])
				{
					union Un { SortT key; struct { IndexT i0; IndexT i1; } u16; } un = { sorted[ii] };
					dst[0] = un.u16.i0;
					dst[1] = un.u16.i1;
					dst += 2;
					last = sorted[ii];
				}
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

	uint32_t topologyConvert(
		  TopologyConvert::Enum _conversion
		, void* _dst
		, uint32_t _dstSize
		, const void* _indices
		, uint32_t _numIndices
		, bool _index32
		, bx::AllocatorI* _allocator
		)
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

		case TopologyConvert::TriStripFlipWinding:
			if (_index32)
			{
				return topologyConvertTriStripFlipWinding(_dst, _dstSize, (const uint32_t*)_indices, _numIndices);
			}

			return topologyConvertTriStripFlipWinding(_dst, _dstSize, (const uint16_t*)_indices, _numIndices);

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

	inline float fmin3(float _a, float _b, float _c)
	{
		return bx::min(_a, _b, _c);
	}

	inline float fmax3(float _a, float _b, float _c)
	{
		return bx::max(_a, _b, _c);
	}

	inline float favg3(float _a, float _b, float _c)
	{
		return (_a + _b + _c) * 1.0f/3.0f;
	}

	const float* vertexPos(const void* _vertices, uint32_t _stride, uint32_t _index)
	{
		const uint8_t* vertices = (const uint8_t*)_vertices;
		return (const float*)&vertices[_index*_stride];
	}

	inline float distanceDir(const float* __restrict _dir, const void* __restrict _vertices, uint32_t _stride, uint32_t _index)
	{
		return bx::vec3Dot(vertexPos(_vertices, _stride, _index), _dir);
	}

	inline float distancePos(const float* __restrict _pos, const void* __restrict _vertices, uint32_t _stride, uint32_t _index)
	{
		float tmp[3];
		bx::vec3Sub(tmp, _pos, vertexPos(_vertices, _stride, _index) );
		return bx::sqrt(bx::vec3Dot(tmp, tmp) );
	}

	typedef float (*KeyFn)(float, float, float);
	typedef float (*DistanceFn)(const float*, const void*, uint32_t, uint32_t);

	template<typename IndexT, DistanceFn dfn, KeyFn kfn, uint32_t xorBits>
	inline void calcSortKeys(
		  uint32_t* __restrict _keys
		, uint32_t* __restrict _values
		, const float _dirOrPos[3]
		, const void* __restrict _vertices
		, uint32_t _stride
		, const IndexT* _indices
		, uint32_t _num
		)
	{
		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const uint32_t idx0 = _indices[0];
			const uint32_t idx1 = _indices[1];
			const uint32_t idx2 = _indices[2];
			_indices += 3;

			float distance0 = dfn(_dirOrPos, _vertices, _stride, idx0);
			float distance1 = dfn(_dirOrPos, _vertices, _stride, idx1);
			float distance2 = dfn(_dirOrPos, _vertices, _stride, idx2);

			uint32_t ui = bx::floatToBits(kfn(distance0, distance1, distance2) );
			_keys[ii]   = bx::floatFlip(ui) ^ xorBits;
			_values[ii] = ii;
		}
	}

	template<typename IndexT>
	void topologySortTriList(
		  TopologySort::Enum  _sort
		, IndexT* _dst
		, uint32_t* _keys
		, uint32_t* _values
		, uint32_t* _tempKeys
		, uint32_t* _tempValues
		, uint32_t  _num
		, const float _dir[3]
		, const float _pos[3]
		, const void* _vertices
		, uint32_t    _stride
		, const IndexT* _indices
		)
	{
		using namespace bx;

		switch (_sort)
		{
		default:
		case TopologySort::DirectionFrontToBackMin: calcSortKeys<IndexT, distanceDir, fmin3, 0         >(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DirectionFrontToBackAvg: calcSortKeys<IndexT, distanceDir, favg3, 0         >(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DirectionFrontToBackMax: calcSortKeys<IndexT, distanceDir, fmax3, 0         >(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DirectionBackToFrontMin: calcSortKeys<IndexT, distanceDir, fmin3, UINT32_MAX>(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DirectionBackToFrontAvg: calcSortKeys<IndexT, distanceDir, favg3, UINT32_MAX>(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DirectionBackToFrontMax: calcSortKeys<IndexT, distanceDir, fmax3, UINT32_MAX>(_keys, _values, _dir, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceFrontToBackMin:  calcSortKeys<IndexT, distancePos, fmin3, 0         >(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceFrontToBackAvg:  calcSortKeys<IndexT, distancePos, favg3, 0         >(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceFrontToBackMax:  calcSortKeys<IndexT, distancePos, fmax3, 0         >(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceBackToFrontMin:  calcSortKeys<IndexT, distancePos, fmin3, UINT32_MAX>(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceBackToFrontAvg:  calcSortKeys<IndexT, distancePos, favg3, UINT32_MAX>(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		case TopologySort::DistanceBackToFrontMax:  calcSortKeys<IndexT, distancePos, fmax3, UINT32_MAX>(_keys, _values, _pos, _vertices, _stride, _indices, _num); break;
		}

		radixSort(_keys, _tempKeys, _values, _tempValues, _num);

		IndexT* sorted = _dst;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			uint32_t face = _values[ii]*3;
			const IndexT idx0 = _indices[face+0];
			const IndexT idx1 = _indices[face+1];
			const IndexT idx2 = _indices[face+2];

			sorted[0] = idx0;
			sorted[1] = idx1;
			sorted[2] = idx2;
			sorted += 3;
		}
	}

	void topologySortTriList(
		  TopologySort::Enum  _sort
		, void*       _dst
		, uint32_t    _dstSize
		, const float _dir[3]
		, const float _pos[3]
		, const void* _vertices
		, uint32_t    _stride
		, const void* _indices
		, uint32_t    _numIndices
		, bool        _index32
		, bx::AllocatorI* _allocator
		)
	{
		uint32_t indexSize = _index32
			? sizeof(uint32_t)
			: sizeof(uint16_t)
			;
		uint32_t  num  = bx::uint32_min(_numIndices*indexSize, _dstSize)/(indexSize*3);
		uint32_t* temp = (uint32_t*)BX_ALLOC(_allocator, sizeof(uint32_t)*num*4);

		uint32_t* keys       = &temp[num*0];
		uint32_t* values     = &temp[num*1];
		uint32_t* tempKeys   = &temp[num*2];
		uint32_t* tempValues = &temp[num*3];

		if (_index32)
		{
			topologySortTriList(
					  _sort
					, (uint32_t*)_dst
					, keys
					, values
					, tempKeys
					, tempValues
					, num
					, _dir
					, _pos
					, _vertices
					, _stride
					, (const uint32_t*)_indices
					);
		}
		else
		{
			topologySortTriList(
					  _sort
					, (uint16_t*)_dst
					, keys
					, values
					, tempKeys
					, tempValues
					, num
					, _dir
					, _pos
					, _vertices
					, _stride
					, (const uint16_t*)_indices
					);
		}

		BX_FREE(_allocator, temp);
	}

} //namespace bgfx

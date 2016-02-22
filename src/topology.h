/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_TOPOLOGY_H_HEADER_GUARD
#define BGFX_TOPOLOGY_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <bx/allocator.h>

namespace bgfx
{
	///
	struct TopologyConvert
	{
		enum Enum
		{
			TriListFlipWinding,
			TriListToLineList,
			TriStripToTriList,
			LineStripToLineList,

			Count
		};
	};

	/// Converts topology from triangle list to line list.
	///
	/// @param[in] _conversion
	/// @param[in] _dst
	/// @param[in] _dstSize
	/// @param[in] _indices
	/// @param[in] _numIndices
	/// @param[in] _index32
	///
	/// @returns
	///
	uint32_t toplogyConvert(TopologyConvert::Enum _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32, bx::AllocatorI* _allocator);

} // namespace bgfx

#endif // BGFX_TOPOLOGY_H_HEADER_GUARD

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_TOPOLOGY_H_HEADER_GUARD
#define BGFX_TOPOLOGY_H_HEADER_GUARD

#include <bgfx/bgfx.h>

namespace bgfx
{
	/// Convert index buffer for use with different primitive topologies.
	///
	/// @param[in] _conversion Conversion type, see `TopologyConvert::Enum`.
	/// @param[in] _dst Destination index buffer. If this argument it NULL
	///    function will return number of indices after conversion.
	/// @param[in] _dstSize Destination index buffer in bytes. It must be
	///    large enough to contain output indices. If destination size is
	///    insufficient index buffer will be truncated.
	/// @param[in] _indices Source indices.
	/// @param[in] _numIndices Number of input indices.
	/// @param[in] _index32 Set to `true` if input indices are 32-bit.
	///
	/// @returns Number of output indices after conversion.
	///
	/// @attention C99 equivalent is `bgfx_topology_convert`.
	///
	uint32_t topologyConvert(
		  TopologyConvert::Enum _conversion
		, void* _dst
		, uint32_t _dstSize
		, const void* _indices
		, uint32_t _numIndices
		, bool _index32
		, bx::AllocatorI* _allocator
		);

	///
	void topologySortTriList(
		  TopologySort::Enum _sort
		, void* _dst
		, uint32_t _dstSize
		, const float _dir[3]
		, const float _pos[3]
		, const void* _vertices
		, uint32_t _stride
		, const void* _indices
		, uint32_t _numIndices
		, bool _index32
		, bx::AllocatorI* _allocator
		);

} // namespace bgfx

#endif // BGFX_TOPOLOGY_H_HEADER_GUARD

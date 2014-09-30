/*
Copyright (c) 2014, Conor Stokes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef INDEX_COMPRESSION_CONSTANTS_H__
#define INDEX_COMPRESSION_CONSTANTS_H__
#pragma once

// Constant fifo and code sizes.
const int VERTEX_FIFO_SIZE   = 32;
const int VERTEX_FIFO_MASK   = VERTEX_FIFO_SIZE - 1;
const int EDGE_FIFO_SIZE     = 32;
const int EDGE_FIFO_MASK     = EDGE_FIFO_SIZE - 1;
const int CACHED_EDGE_BITS   = 5;
const int CACHED_VERTEX_BITS = 5;
const int IB_CODE_BITS       = 2;

// Edge in the edge fifo.
struct Edge
{
	uint32_t first;
	uint32_t second;
};

// Codes 
enum IndexBufferCodes
{
	// Represents a yet un-seen vertex.
	IB_NEW_VERTEX    = 0,

	// Represents 2 vertices on an edge in the edge fifo, which will be used as the first 2 vertices of the
	// triangle.
	IB_CACHED_EDGE   = 1,
	
	// Represents a vertex that has been seen recently and is still in the vertex fifo.
	IB_CACHED_VERTEX = 2,

	// Represents a vertex that has been seen 
	IB_FREE_VERTEX   = 3
};

#endif 
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
#include "IndexBufferCompression.h"
#include "WriteBitstream.h"
#include "IndexCompressionConstants.h"
#include <assert.h>

#ifdef _MSC_VER
#define IBC_INLINE __forceinline
#else
#define IBC_INLINE __attribute__((always_inline))
#endif 

const uint32_t VERTEX_NOT_MAPPED = 0xFFFFFFFF;

// Output the compression information for a single vertex, remapping any new vertices and updating the vertex fifo where needed.
static IBC_INLINE void OutputVertex( uint32_t vertex,
							         uint32_t* vertexRemap,
							         uint32_t& newVertexCount,
							         uint32_t* vertexFifo,
							         uint32_t& verticesRead,
							         WriteBitstream& output )
{
	// Check if a vertex hasn't been remapped, 
	if ( vertexRemap[ vertex ] == VERTEX_NOT_MAPPED )
	{
		// no remap, so remap to the current high watermark and output a new vertex code.
		vertexRemap[ vertex ] = newVertexCount;

		output.Write( IB_NEW_VERTEX, IB_CODE_BITS );

		++newVertexCount;

		// new vertices go into the vertex FIFO
		vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = vertex;

		++verticesRead;
	}
	else
	{
		int32_t lowestVertexCursor = verticesRead >= VERTEX_FIFO_SIZE ? verticesRead - VERTEX_FIFO_SIZE : 0;

		// Probe backwards in the vertex FIFO for a cached vertex
		for ( int32_t vertexCursor = verticesRead - 1; vertexCursor >= lowestVertexCursor; --vertexCursor )
		{
			if ( vertexFifo[ vertexCursor & VERTEX_FIFO_MASK ] == vertex )
			{
				// found a cached vertex, so write out the code for a cached vertex, as the relative index into the fifo.
				output.Write( IB_CACHED_VERTEX, IB_CODE_BITS );
				output.Write( ( verticesRead - 1 ) - vertexCursor, CACHED_VERTEX_BITS );

				return;
			}
		}

		// no cached vertex found, so write out a free vertex 
		output.Write( IB_FREE_VERTEX, IB_CODE_BITS );

		// free vertices are relative to the latest new vertex.
		uint32_t vertexOutput = ( newVertexCount - 1 ) - vertexRemap[ vertex ];

		// v-int encode the free vertex index.
		do
		{
			uint32_t lower7 = vertexOutput & 0x7F;

			vertexOutput >>= 7;

			output.Write( lower7 | ( vertexOutput > 0 ? 0x80 : 0 ), 8 );

		} while ( vertexOutput > 0 );


		// free vertices go back into the vertex cache.
		vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = vertex;
			
		++verticesRead;
	}

}

template <typename Ty>
void CompressIndexBuffer( const Ty* triangles, 
						  uint32_t triangleCount, 
						  uint32_t* vertexRemap, 
						  uint32_t vertexCount, 
						  WriteBitstream& output )
{
	Edge      edgeFifo[ EDGE_FIFO_SIZE ];
	uint32_t  vertexFifo[ VERTEX_FIFO_SIZE ];

	uint32_t  edgesRead      = 0;
	uint32_t  verticesRead   = 0;
	uint32_t  newVertices    = 0;
	const Ty* triangleEnd    = triangles + ( triangleCount * 3 );

	assert( vertexCount < 0xFFFFFFFF );

	uint32_t* vertexRemapEnd = vertexRemap + vertexCount;

	// clear the vertex remapping to "not found" value of 0xFFFFFFFF - dirty, but low overhead.
	for (uint32_t* remappedVertex = vertexRemap; remappedVertex < vertexRemapEnd; ++remappedVertex )
	{
		*remappedVertex = VERTEX_NOT_MAPPED;
	}

	// iterate through the triangles
	for (const Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
	{
		int32_t lowestEdgeCursor = edgesRead >= EDGE_FIFO_SIZE ? edgesRead - EDGE_FIFO_SIZE : 0;
		int32_t edgeCursor = edgesRead - 1;
		bool     foundEdge = false;

		int32_t freeVertex;

		// Probe back through the edge fifo to see if one of the triangle edges is in the FIFO
		for ( ; edgeCursor >= lowestEdgeCursor; --edgeCursor )
		{
			const Edge& edge = edgeFifo[ edgeCursor & VERTEX_FIFO_MASK ];

			// check all the edges in order and save the free vertex.
			if ( edge.second == triangle[ 0 ] && edge.first == triangle[ 1 ] )
			{
				foundEdge  = true;
				freeVertex = 2;
				break;
			}
			else if ( edge.second == triangle[ 1 ] && edge.first == triangle[ 2 ] )
			{
				foundEdge  = true;
				freeVertex = 0;
				break;
			}
			else if ( edge.second == triangle[ 2 ] && edge.first == triangle[ 0 ] )
			{
				foundEdge  = true;
				freeVertex = 1;
				break;
			}
		}

		// we found an edge so write it out, then output the vertex
		if ( foundEdge )
		{
			output.Write( IB_CACHED_EDGE, IB_CODE_BITS );
			output.Write( ( edgesRead - 1 ) - edgeCursor, CACHED_EDGE_BITS );

			const Edge& edge = edgeFifo[ edgeCursor & EDGE_FIFO_MASK ];

			OutputVertex( triangle[ freeVertex ], vertexRemap, newVertices, vertexFifo, verticesRead, output );

			// edge is in reverse order to last triangle it occured on (and it will only be a match if this is the case).
			// so put the vertices into the fifo in that order.
			vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = edge.second;

			++verticesRead;

			vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = edge.first;

			++verticesRead;

			// Populate the edge fifo with the the remaining edges
			// Note - the winding order is important as we'll need to re-produce this on decompression.
			// The edges are put in as if the found edge is the first edge in the triangle (which it will be when we
			// reconstruct).
			switch ( freeVertex )
			{
			case 0:

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 2 ], triangle[ 0 ]);

				++edgesRead;

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 0 ], triangle[ 1 ]);

				++edgesRead;
				break;

			case 1:

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 0 ], triangle[ 1 ]);

				++edgesRead;

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 1 ], triangle[ 2 ]);

				++edgesRead;
				break;

			case 2:

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 1 ], triangle[ 2 ]);

				++edgesRead;

				edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 2 ], triangle[ 0 ]);

				++edgesRead;
				break;
			}
		}
		else
		{
			// no edge, so we need to output all the vertices.
			OutputVertex( triangle[ 0 ], vertexRemap, newVertices, vertexFifo, verticesRead, output );
			OutputVertex( triangle[ 1 ], vertexRemap, newVertices, vertexFifo, verticesRead, output );
			OutputVertex( triangle[ 2 ], vertexRemap, newVertices, vertexFifo, verticesRead, output );

			// populate the edge fifo with the 3 most recent edges
			edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 0 ], triangle[ 1 ]);

			++edgesRead;

			edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 1 ], triangle[ 2 ]);

			++edgesRead;

			edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set(triangle[ 2 ], triangle[ 0 ]);

			++edgesRead;
		}
	}
}

void CompressIndexBuffer ( const uint16_t* triangles,
						 uint32_t triangleCount, 
						 uint32_t* vertexRemap, 
						 uint32_t vertexCount, 
						 WriteBitstream& output )
{
	CompressIndexBuffer<uint16_t>(triangles, triangleCount, vertexRemap, vertexCount, output);
}

void CompressIndexBuffer ( const uint32_t* triangles,
						  uint32_t triangleCount, 
						  uint32_t* vertexRemap, 
						  uint32_t vertexCount, 
						  WriteBitstream& output )
{
	CompressIndexBuffer<uint32_t>(triangles, triangleCount, vertexRemap, vertexCount, output);
}
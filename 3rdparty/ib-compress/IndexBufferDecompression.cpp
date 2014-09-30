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
#include "IndexBufferDecompression.h"
#include "ReadBitstream.h"
#include "IndexCompressionConstants.h"
#include <assert.h>

void DecompressIndexBuffer( uint32_t* triangles, uint32_t triangleCount, ReadBitstream& input )
{
	Edge            edgeFifo[ EDGE_FIFO_SIZE ];
	uint32_t        vertexFifo[ VERTEX_FIFO_SIZE ];

	uint32_t        edgesRead    = 0;
	uint32_t        verticesRead = 0;
	uint32_t        newVertices  = 0;
	const uint32_t* triangleEnd  = triangles + ( triangleCount * 3 );

	// iterate through the triangles
	for ( uint32_t* triangle = triangles; triangle < triangleEnd; triangle += 3 )
	{
		int  readVertex = 0;
		bool skipFirstEdge = false;

		while ( readVertex < 3 )
		{
			IndexBufferCodes code = static_cast< IndexBufferCodes >( input.Read( IB_CODE_BITS ) );

			switch ( code )
			{
			case IB_NEW_VERTEX:

				triangle[ readVertex ] =
					vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = newVertices;

				++readVertex;
				++verticesRead;
				++newVertices;

				break;

			case IB_CACHED_EDGE:

			{
				assert( readVertex == 0 );

				uint32_t    fifoIndex = input.Read( CACHED_EDGE_BITS );
				const Edge& edge      = edgeFifo[ ( ( edgesRead - 1 ) - fifoIndex ) & EDGE_FIFO_MASK ];

				triangle[ 0 ] = edge.second;
				triangle[ 1 ] = edge.first;

				readVertex    += 2;
				skipFirstEdge  = true;

				break;
			}

			case IB_CACHED_VERTEX:

			{
				uint32_t fifoIndex  = input.Read( CACHED_VERTEX_BITS );
				
				triangle[ readVertex ] = vertexFifo[ ( ( verticesRead - 1 ) - fifoIndex ) & VERTEX_FIFO_MASK ];

				++readVertex;

				break;
			}

			case IB_FREE_VERTEX:

			{
				uint32_t readByte       = 0;
				uint32_t bitsToShift    = 0;
				uint32_t relativeVertex = 0;

				// V-int decoding, done inline.
				do
				{
					readByte = input.Read( 8 );

					relativeVertex |= ( readByte & 0x7F ) << bitsToShift;
					bitsToShift += 7;

				} while ( readByte & 0x80 );

				uint32_t vertex = ( newVertices - 1 ) - relativeVertex;

				triangle[ readVertex ] =
					vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = vertex;

				++verticesRead;
				++readVertex;
				break;
			}
			}
		}

		if ( !skipFirstEdge )
		{
			edgeFifo[ edgesRead & EDGE_FIFO_MASK ] = { triangle[ 0 ], triangle[ 1 ] };

			++edgesRead;
		}
		else // first 2 verts were an edge case, so insert them into the vertex fifo. 
		{
			vertexFifo[ verticesRead & EDGE_FIFO_MASK ] = triangle[ 0 ];

			++verticesRead;

			vertexFifo[ verticesRead & EDGE_FIFO_MASK ] = triangle[ 1 ];

			++verticesRead;
		}

		edgeFifo[ edgesRead & EDGE_FIFO_MASK ] = { triangle[ 1 ], triangle[ 2 ] };

		++edgesRead;

		edgeFifo[ edgesRead & EDGE_FIFO_MASK ] = { triangle[ 2 ], triangle[ 0 ] };

		++edgesRead;
	}
}
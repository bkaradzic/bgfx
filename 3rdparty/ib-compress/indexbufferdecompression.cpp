/*
Copyright (c) 2014-2015, Conor Stokes
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
#include "indexbufferdecompression.h"
#include "readbitstream.h"
#include "indexcompressionconstants.h"
#include "indexbuffercompressionformat.h"
#include <assert.h>

template <typename Ty>
void DecompressTriangleCodes1( Ty* triangles, uint32_t triangleCount, ReadBitstream& input )
{
    Edge      edgeFifo[ EDGE_FIFO_SIZE ];
    uint32_t  vertexFifo[ VERTEX_FIFO_SIZE ];

    uint32_t  edgesRead = 0;
    uint32_t  verticesRead = 0;
    uint32_t  newVertices = 0;
    const Ty* triangleEnd = triangles + ( triangleCount * 3 );

    // iterate through the triangles
    for ( Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
    {
        IndexBufferTriangleCodes code      = static_cast< IndexBufferTriangleCodes >( input.Read( IB_TRIANGLE_CODE_BITS ) );

        switch ( code )
        {
        case IB_EDGE_NEW:
        {
            uint32_t    edgeFifoIndex = input.Read( CACHED_EDGE_BITS );

            const Edge& edge          = edgeFifo[ ( ( edgesRead - 1 ) - edgeFifoIndex ) & EDGE_FIFO_MASK ];

            triangle[ 0 ] = static_cast< Ty >( edge.second );
            triangle[ 1 ] = static_cast< Ty >( edge.first );

            vertexFifo[ verticesRead & EDGE_FIFO_MASK ] =
            triangle[ 2 ]                               = static_cast< Ty >( newVertices );

            ++newVertices;
            ++verticesRead;

            break;
        }

        case IB_EDGE_CACHED:
        {
            uint32_t    edgeFifoIndex   = input.Read( CACHED_EDGE_BITS );
            uint32_t    vertexFifoIndex = input.Read( CACHED_VERTEX_BITS );

            const Edge& edge            = edgeFifo[ ( ( edgesRead - 1 ) - edgeFifoIndex ) & EDGE_FIFO_MASK ];

            triangle[ 0 ] = static_cast< Ty >( edge.second );
            triangle[ 1 ] = static_cast< Ty >( edge.first );
            triangle[ 2 ] = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertexFifoIndex ) & VERTEX_FIFO_MASK ] );
            
            break;
        }
        case IB_EDGE_FREE:
        {
            uint32_t    edgeFifoIndex   = input.Read( CACHED_EDGE_BITS );
            uint32_t    relativeVertex  = input.ReadVInt();

            const Edge& edge            = edgeFifo[ ( ( edgesRead - 1 ) - edgeFifoIndex ) & EDGE_FIFO_MASK ];

            triangle[ 0 ] = static_cast< Ty >( edge.second );
            triangle[ 1 ] = static_cast< Ty >( edge.first );
            
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                 = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex );
            ++verticesRead;
            
            break;
        }
        case IB_NEW_NEW_NEW:
        {
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( newVertices + 1 );
            vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( newVertices + 2 );

            newVertices  += 3;
            verticesRead += 3;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_NEW_CACHED:
        {
            uint32_t vertexFifoIndex = input.Read( CACHED_VERTEX_BITS );

            triangle[ 2 ]                                         = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertexFifoIndex ) & VERTEX_FIFO_MASK ] );
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( newVertices + 1 );

            verticesRead += 2;
            newVertices  += 2;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_NEW_FREE:
        {
            uint32_t relativeVertex = input.ReadVInt();

            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( newVertices + 1 );
            vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex );

            newVertices  += 2;
            verticesRead += 3;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_CACHED_CACHED:
        {
            uint32_t vertex1FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t vertex2FifoIndex = input.Read( CACHED_VERTEX_BITS );

            triangle[ 1 ]                                 = static_cast< Ty >(  vertexFifo[ ( ( verticesRead - 1 ) - vertex1FifoIndex ) & VERTEX_FIFO_MASK ] );
            triangle[ 2 ]                                 = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex2FifoIndex ) & VERTEX_FIFO_MASK ] );
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] =
            triangle[ 0 ]                                 = static_cast< Ty >( newVertices );

            ++verticesRead;
            ++newVertices;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_CACHED_FREE:
        {
            uint32_t vertexFifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t relativeVertex  = input.ReadVInt();

            triangle[ 1 ]                                         = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertexFifoIndex ) & VERTEX_FIFO_MASK ] );
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex );

            verticesRead += 2;
            ++newVertices;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_FREE_CACHED:
        {
            uint32_t relativeVertex  = input.ReadVInt();
            uint32_t vertexFifoIndex = input.Read( CACHED_VERTEX_BITS );

            triangle[ 2 ]                                         = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertexFifoIndex ) & VERTEX_FIFO_MASK ] ); 
            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex );

            verticesRead += 2;
            ++newVertices;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_NEW_FREE_FREE:
        {
            uint32_t relativeVertex1  = input.ReadVInt();
            uint32_t relativeVertex2  = input.ReadVInt();

            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( newVertices );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex1 );
            vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex2 );

            verticesRead += 3;
            ++newVertices;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;

            break;
        }
        case IB_CACHED_CACHED_CACHED:
        {
            uint32_t vertex0FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t vertex1FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t vertex2FifoIndex = input.Read( CACHED_VERTEX_BITS );

            triangle[ 0 ] = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex0FifoIndex ) & VERTEX_FIFO_MASK ] );
            triangle[ 1 ] = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex1FifoIndex ) & VERTEX_FIFO_MASK ] );
            triangle[ 2 ] = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex2FifoIndex ) & VERTEX_FIFO_MASK ] );

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
            break;
        }
        case IB_CACHED_CACHED_FREE:
        {
            uint32_t vertex0FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t vertex1FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t relativeVertex2  = input.ReadVInt();

            triangle[ 0 ]                                 = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex0FifoIndex ) & VERTEX_FIFO_MASK ] );
            triangle[ 1 ]                                 = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex1FifoIndex ) & VERTEX_FIFO_MASK ] );

            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                 = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex2 );

            ++verticesRead;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;

            break;
        }
        case IB_CACHED_FREE_FREE:
        {
            uint32_t vertex0FifoIndex = input.Read( CACHED_VERTEX_BITS );
            uint32_t relativeVertex1  = input.ReadVInt();
            uint32_t relativeVertex2  = input.ReadVInt();

            triangle[ 0 ]                                         = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - vertex0FifoIndex ) & VERTEX_FIFO_MASK ] );

            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 1 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex1 );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex2 );

            verticesRead += 2;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;

            break;
        }
        case IB_FREE_FREE_FREE:
        {
            uint32_t relativeVertex0 = input.ReadVInt();
            uint32_t relativeVertex1 = input.ReadVInt();
            uint32_t relativeVertex2 = input.ReadVInt();

            vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         =
            triangle[ 0 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex0 );
            vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] =
            triangle[ 1 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex1 );
            vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] =
            triangle[ 2 ]                                         = static_cast< Ty >( ( newVertices - 1 ) - relativeVertex2 );

            verticesRead += 3;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;

            break;
        }
        case IB_EDGE_0_NEW:
        {
            const Edge& edge = edgeFifo[ ( edgesRead - 1 ) & EDGE_FIFO_MASK ];

            triangle[ 0 ]                               = static_cast< Ty >( edge.second );
            triangle[ 1 ]                               = static_cast< Ty >( edge.first );

            vertexFifo[ verticesRead & EDGE_FIFO_MASK ] =
            triangle[ 2 ]                               = static_cast< Ty >( newVertices );

            ++newVertices;
            ++verticesRead;
            break;
        }
        case IB_EDGE_1_NEW:
        {
            const Edge& edge = edgeFifo[ ( ( edgesRead - 1 ) - 1 ) & EDGE_FIFO_MASK ];

            triangle[ 0 ]                               = static_cast< Ty >( edge.second );
            triangle[ 1 ]                               = static_cast< Ty >( edge.first );

            vertexFifo[ verticesRead & EDGE_FIFO_MASK ] =
            triangle[ 2 ]                               = static_cast< Ty >( newVertices );

            ++newVertices;
            ++verticesRead;
            break;
        }
        }

        edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

        ++edgesRead;

        edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

        ++edgesRead;
    }
}

template <typename Ty>
void DecompressIndiceCodes1( Ty* triangles, uint32_t triangleCount, ReadBitstream& input )
{
    Edge      edgeFifo[ EDGE_FIFO_SIZE ];
    uint32_t  vertexFifo[ VERTEX_FIFO_SIZE ];

    uint32_t  edgesRead    = 0;
    uint32_t  verticesRead = 0;
    uint32_t  newVertices  = 0;
    const Ty* triangleEnd = triangles + ( triangleCount * 3 );

    // iterate through the triangles
    for ( Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
    {
        int  readVertex = 0;
        bool skipFirstEdge = false;

        while ( readVertex < 3 )
        {
            IndexBufferCodes code = static_cast< IndexBufferCodes >( input.Read( IB_VERTEX_CODE_BITS ) );

            switch ( code )
            {
            case IB_NEW_VERTEX:

                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] =
                triangle[ readVertex ]                        = static_cast< Ty >(  newVertices );

                ++readVertex;
                ++verticesRead;
                ++newVertices;

                break;

            case IB_CACHED_EDGE:

            {
                assert( readVertex == 0 );

                uint32_t    fifoIndex = input.Read( CACHED_EDGE_BITS );
                const Edge& edge      = edgeFifo[ ( ( edgesRead - 1 ) - fifoIndex ) & EDGE_FIFO_MASK ];

                triangle[ 0 ] = static_cast< Ty >( edge.second );
                triangle[ 1 ] = static_cast< Ty >( edge.first );

                readVertex    += 2;
                skipFirstEdge  = true;

                break;
            }

            case IB_CACHED_VERTEX:

            {
                uint32_t fifoIndex     = input.Read( CACHED_VERTEX_BITS );
                
                triangle[ readVertex ] = static_cast< Ty >( vertexFifo[ ( ( verticesRead - 1 ) - fifoIndex ) & VERTEX_FIFO_MASK ] );

                ++readVertex;

                break;
            }

            case IB_FREE_VERTEX:

            {
                uint32_t relativeVertex = input.ReadVInt();

                uint32_t vertex = ( newVertices - 1 ) - relativeVertex;

                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] =
                triangle[ readVertex ]                        = static_cast< Ty >( vertex );

                ++verticesRead;
                ++readVertex;
                break;
            }
            }
        }

        if ( !skipFirstEdge )
        {
            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;
        }
        else // first 2 verts were an edge case, so insert them into the vertex fifo. 
        {
            vertexFifo[ verticesRead & EDGE_FIFO_MASK ] = triangle[ 0 ];

            ++verticesRead;

            vertexFifo[ verticesRead & EDGE_FIFO_MASK ] = triangle[ 1 ];

            ++verticesRead;
        }

        edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

        ++edgesRead;

        edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

        ++edgesRead;
    }
}

template < typename Ty >
void DecompressIndexBuffer( Ty* triangles, uint32_t triangleCount, ReadBitstream& input )
{
    IndexBufferCompressionFormat format = static_cast< IndexBufferCompressionFormat >( input.ReadVInt() );

    switch ( format )
    {
    case IBCF_PER_INDICE_1:

        DecompressIndiceCodes1<Ty>( triangles, triangleCount, input );
        break;

    case IBCF_PER_TRIANGLE_1:

        DecompressTriangleCodes1<Ty>( triangles, triangleCount, input );
        break;

    default: // IBCF_AUTO:
        break;
    }
}

void DecompressIndexBuffer( uint32_t* triangles, uint32_t triangleCount, ReadBitstream& input )
{
    DecompressIndexBuffer<uint32_t>( triangles, triangleCount, input );
}

void DecompressIndexBuffer( uint16_t* triangles, uint32_t triangleCount, ReadBitstream& input )
{
    DecompressIndexBuffer<uint16_t>( triangles, triangleCount, input );
}

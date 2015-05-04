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
#include "indexbuffercompression.h"
#include "writebitstream.h"
#include "indexcompressionconstants.h"
#include <assert.h>

#ifdef _MSC_VER
#define IBC_INLINE __forceinline
#else
#define IBC_INLINE inline
#endif 

// Individual vertex type classifications.
enum VertexClassification
{
    NEW_VERTEX = 0,
    CACHED_VERTEX = 1,
    FREE_VERTEX = 2
};

// Individual case for handling a combination of vertice classifications.
struct VertexCompressionCase
{
    IndexBufferTriangleCodes code;
    uint32_t vertexOrder[ 3 ];
};

// This is a table for looking up the appropriate code and rotation for a set of vertex classifications.
const VertexCompressionCase CompressionCase[3][3][3] =
{
    { // new 
        { // new new
            { // new new new 
                IB_NEW_NEW_NEW, { 0, 1, 2 }
            },
            { // new new cached
                IB_NEW_NEW_CACHED, { 0, 1, 2 }
            },
            { // new new free
                IB_NEW_NEW_FREE, { 0, 1, 2 }
            }
        },
        { // new cached
            { // new cached new
                IB_NEW_NEW_CACHED, { 2, 0, 1 }
            },
            {  // new cached cached
                IB_NEW_CACHED_CACHED, { 0, 1, 2 }
            },
            { // new cached free
                IB_NEW_CACHED_FREE, { 0, 1, 2 }
            }
        },
        { // new free
            { // new free new
                IB_NEW_NEW_FREE, { 2, 0, 1 }
            },
            { // new free cached
                IB_NEW_FREE_CACHED, { 0, 1, 2 }
            },
            { // new free free
                IB_NEW_FREE_FREE, { 0, 1, 2 }
            }
        }
    },
    { // cached
        { // cached new 
            { // cached new new
                IB_NEW_NEW_CACHED, { 1, 2, 0 }
            },
            { // cached new cached
                IB_NEW_CACHED_CACHED, { 1, 2, 0 }
            },
            { // cached new free
                IB_NEW_FREE_CACHED, { 1, 2, 0 }
            }
        },
        { // cached cached
            { // cached cached new
                IB_NEW_CACHED_CACHED, { 2, 0, 1 }
            },
            { // cached cached cached
                IB_CACHED_CACHED_CACHED, { 0, 1, 2 }
            },
            { // cached cached free
                IB_CACHED_CACHED_FREE, { 0, 1, 2 }
            }
        },
        { // cached free
            { // cached free new
                IB_NEW_CACHED_FREE, { 2, 0, 1 }
            },
            { // cached free cached
                IB_CACHED_CACHED_FREE, { 2, 0, 1 }
            },
            { // cached free free 
                IB_CACHED_FREE_FREE, { 0, 1, 2 }
            }
        }
    },
    { // free
        { // free new
            { // free new new
                IB_NEW_NEW_FREE, { 1, 2, 0 }
            },
            { // free new cached
                IB_NEW_CACHED_FREE, { 1, 2, 0 }
            },
            { // free new free
                IB_NEW_FREE_FREE, { 1, 2, 0 }
            }
        },
        { // free cached
            { // free cached new
                IB_NEW_FREE_CACHED, { 2, 0, 1 }
            },
            { // free cached cached
                IB_CACHED_CACHED_FREE, { 1, 2, 0 }
            },
            { // free cached free
                IB_CACHED_FREE_FREE, { 1, 2, 0 }
            }
        },
        { // free free
            { // free free new
                IB_NEW_FREE_FREE, { 2, 0, 1 }
            },
            { // free free cached
                IB_CACHED_FREE_FREE, { 2, 0, 1 }
            },
            { // free free free
                IB_FREE_FREE_FREE, { 0, 1, 2 }
            }
        }
    }
};

const uint32_t VERTEX_NOT_MAPPED = 0xFFFFFFFF;

// Classify a vertex as new, cached or free, outputting the relative position in the vertex indice cache FIFO.
static IBC_INLINE VertexClassification ClassifyVertex( uint32_t vertex, const uint32_t* vertexRemap, const uint32_t* vertexFifo, uint32_t verticesRead, uint32_t& cachedVertexIndex )
{
    if ( vertexRemap[ vertex ] == VERTEX_NOT_MAPPED )
    {
        return NEW_VERTEX;
    }
    else
    {
        int32_t lowestVertexCursor = verticesRead >= VERTEX_FIFO_SIZE ? verticesRead - VERTEX_FIFO_SIZE : 0;

        // Probe backwards in the vertex FIFO for a cached vertex
        for ( int32_t vertexCursor = verticesRead - 1; vertexCursor >= lowestVertexCursor; --vertexCursor )
        {
            if ( vertexFifo[ vertexCursor & VERTEX_FIFO_MASK ] == vertex )
            {
                cachedVertexIndex = ( verticesRead - 1 ) - vertexCursor;

                return CACHED_VERTEX;
            }
        }

        return FREE_VERTEX;
    }
}

template <typename Ty>
void CompressTriangleCodes1( const Ty* triangles,
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
    const Ty* triangleEnd = triangles + ( triangleCount * 3 );

    assert( vertexCount < 0xFFFFFFFF );

    uint32_t* vertexRemapEnd = vertexRemap + vertexCount;

    // clear the vertex remapping to "not found" value of 0xFFFFFFFF - dirty, but low overhead.
    for ( uint32_t* remappedVertex = vertexRemap; remappedVertex < vertexRemapEnd; ++remappedVertex )
    {
        *remappedVertex = VERTEX_NOT_MAPPED;
    }

    // iterate through the triangles
    for ( const Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
    {
        int32_t lowestEdgeCursor = edgesRead >= EDGE_FIFO_SIZE ? edgesRead - EDGE_FIFO_SIZE : 0;
        int32_t edgeCursor       = edgesRead - 1;
        bool    foundEdge        = false;

        int32_t spareVertex = 0;

        // check to make sure that there are no degenerate triangles.
        assert( triangle[ 0 ] != triangle[ 1 ] && triangle[ 1 ] != triangle[ 2 ] && triangle[ 2 ] != triangle[ 0 ] );

        // Probe back through the edge fifo to see if one of the triangle edges is in the FIFO
        for ( ; edgeCursor >= lowestEdgeCursor; --edgeCursor )
        {
            const Edge& edge = edgeFifo[ edgeCursor & EDGE_FIFO_MASK ];

            // check all the edges in order and save the free vertex.
            if ( edge.second == triangle[ 0 ] && edge.first == triangle[ 1 ] )
            {
                foundEdge   = true;
                spareVertex = 2;
                break;
            }
            else if ( edge.second == triangle[ 1 ] && edge.first == triangle[ 2 ] )
            {
                foundEdge   = true;
                spareVertex = 0;
                break;
            }
            else if ( edge.second == triangle[ 2 ] && edge.first == triangle[ 0 ] )
            {
                foundEdge   = true;
                spareVertex = 1;
                break;
            }
        }

        // we found an edge so write it out, so classify a vertex and then write out the correct code.
        if ( foundEdge )
        {
            uint32_t cachedVertex;
            
            uint32_t             spareVertexIndice = triangle[ spareVertex ];
            VertexClassification freeVertexClass   = ClassifyVertex( spareVertexIndice, vertexRemap, vertexFifo, verticesRead, cachedVertex );
            uint32_t             relativeEdge      = ( edgesRead - 1 ) - edgeCursor;

            switch ( freeVertexClass )
            {
            case NEW_VERTEX:
                
                switch ( relativeEdge )
                {
                case 0:

                    output.Write( IB_EDGE_0_NEW, IB_TRIANGLE_CODE_BITS );
                    break;

                case 1:

                    output.Write( IB_EDGE_1_NEW, IB_TRIANGLE_CODE_BITS );
                    break;

                default:

                    output.Write( IB_EDGE_NEW, IB_TRIANGLE_CODE_BITS );
                    output.Write( relativeEdge, CACHED_EDGE_BITS );
                    break;

                }

                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = spareVertexIndice;
                vertexRemap[ spareVertexIndice ]              = newVertices;

                ++verticesRead;
                ++newVertices;
                break;

            case CACHED_VERTEX:

                output.Write( IB_EDGE_CACHED, IB_TRIANGLE_CODE_BITS );
                output.Write( relativeEdge, CACHED_EDGE_BITS );
                output.Write( cachedVertex, CACHED_VERTEX_BITS );
                break;

            case FREE_VERTEX:

                output.Write( IB_EDGE_FREE, IB_TRIANGLE_CODE_BITS );
                output.Write( relativeEdge, CACHED_EDGE_BITS );

                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = spareVertexIndice;

                ++verticesRead;
                
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ spareVertexIndice ] );
                break;

            }

            // Populate the edge fifo with the the remaining edges
            // Note - the winding order is important as we'll need to re-produce this on decompression.
            // The edges are put in as if the found edge is the first edge in the triangle (which it will be when we
            // reconstruct).
            switch ( spareVertex )
            {
            case 0:

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

                ++edgesRead;
                break;

            case 1:

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

                ++edgesRead;
                break;

            case 2:

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

                ++edgesRead;
                break;
            }
        }
        else
        {
            VertexClassification classifications[ 3 ];
            uint32_t             cachedVertexIndices[ 3 ];

            // classify each vertex as new, cached or free, potentially extracting a cached indice.
            classifications[ 0 ] = ClassifyVertex( triangle[ 0 ], vertexRemap, vertexFifo, verticesRead, cachedVertexIndices[ 0 ] );
            classifications[ 1 ] = ClassifyVertex( triangle[ 1 ], vertexRemap, vertexFifo, verticesRead, cachedVertexIndices[ 1 ] );
            classifications[ 2 ] = ClassifyVertex( triangle[ 2 ], vertexRemap, vertexFifo, verticesRead, cachedVertexIndices[ 2 ] );

            // use the classifications to lookup the matching compression code and potentially rotate the order of the vertices.
            const VertexCompressionCase& compressionCase = CompressionCase[ classifications[ 0 ] ][ classifications[ 1 ] ][ classifications[ 2 ] ];
            
            // rotate the order of the vertices based on the compression classification.
            uint32_t reorderedTriangle[ 3 ];
            
            reorderedTriangle[ 0 ] = triangle[ compressionCase.vertexOrder[ 0 ] ];
            reorderedTriangle[ 1 ] = triangle[ compressionCase.vertexOrder[ 1 ] ];
            reorderedTriangle[ 2 ] = triangle[ compressionCase.vertexOrder[ 2 ] ];

            output.Write( compressionCase.code, IB_TRIANGLE_CODE_BITS );

            switch ( compressionCase.code )
            {
            case IB_NEW_NEW_NEW:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = triangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = triangle[ 1 ];
                vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] = triangle[ 2 ];

                vertexRemap[ triangle[ 0 ] ] = newVertices;
                vertexRemap[ triangle[ 1 ] ] = newVertices + 1;
                vertexRemap[ triangle[ 2 ] ] = newVertices + 2;

                verticesRead += 3;
                newVertices  += 3;

                break;
            }
            case IB_NEW_NEW_CACHED:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 1 ];

                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 2 ] ], CACHED_VERTEX_BITS );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;
                vertexRemap[ reorderedTriangle[ 1 ] ] = newVertices + 1;

                verticesRead += 2;
                newVertices  += 2;

                break;
            }
            case IB_NEW_NEW_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 1 ];
                vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;
                vertexRemap[ reorderedTriangle[ 1 ] ] = newVertices + 1;

                verticesRead += 3;
                newVertices  += 2;

                break;
            }
            case IB_NEW_CACHED_CACHED:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = reorderedTriangle[ 0 ];

                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 1 ] ], CACHED_VERTEX_BITS );
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 2 ] ], CACHED_VERTEX_BITS );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;
                verticesRead += 1;
                newVertices  += 1;

                break;
            }
            case IB_NEW_CACHED_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 1 ] ], CACHED_VERTEX_BITS );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;

                verticesRead += 2;
                newVertices  += 1;

                break;
            }
            case IB_NEW_FREE_CACHED:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 1 ];

                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 1 ] ] );
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 2 ] ], CACHED_VERTEX_BITS );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;

                verticesRead += 2;
                newVertices  += 1;

                break;
            }
            case IB_NEW_FREE_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 1 ];
                vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 1 ] ] );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                vertexRemap[ reorderedTriangle[ 0 ] ] = newVertices;

                verticesRead += 3;
                newVertices  += 1;

                break;
            }
            case IB_CACHED_CACHED_CACHED:
            {
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 0 ] ], CACHED_VERTEX_BITS );
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 1 ] ], CACHED_VERTEX_BITS );
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 2 ] ], CACHED_VERTEX_BITS );
                break;
            }
            case IB_CACHED_CACHED_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 0 ] ], CACHED_VERTEX_BITS );
                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 1 ] ], CACHED_VERTEX_BITS );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                verticesRead += 1;

                break;
            }
            case IB_CACHED_FREE_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 1 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.Write( cachedVertexIndices[ compressionCase.vertexOrder[ 0 ] ], CACHED_VERTEX_BITS );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 1 ] ] );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                verticesRead += 2;

                break;
            }
            case IB_FREE_FREE_FREE:
            {
                vertexFifo[ verticesRead & VERTEX_FIFO_MASK ]         = reorderedTriangle[ 0 ];
                vertexFifo[ ( verticesRead + 1 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 1 ];
                vertexFifo[ ( verticesRead + 2 ) & VERTEX_FIFO_MASK ] = reorderedTriangle[ 2 ];

                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 0 ] ] );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 1 ] ] );
                output.WriteVInt( ( newVertices - 1 ) - vertexRemap[ reorderedTriangle[ 2 ] ] );

                verticesRead += 3;
                break;
            }

            default: // IB_EDGE_NEW, IB_EDGE_CACHED, IB_EDGE_0_NEW, IB_EDGE_1_NEW
                break;
            }

            // populate the edge fifo with the 3 most recent edges
            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( reorderedTriangle[ 0 ], reorderedTriangle[ 1 ] );

            ++edgesRead;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( reorderedTriangle[ 1 ], reorderedTriangle[ 2 ] );

            ++edgesRead;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( reorderedTriangle[ 2 ], reorderedTriangle[ 0 ] );

            ++edgesRead;
        }
    }
}



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

        output.Write( IB_NEW_VERTEX, IB_VERTEX_CODE_BITS );

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
                output.Write( IB_CACHED_VERTEX, IB_VERTEX_CODE_BITS );
                output.Write( ( verticesRead - 1 ) - vertexCursor, CACHED_VERTEX_BITS );

                return;
            }
        }

        // no cached vertex found, so write out a free vertex 
        output.Write( IB_FREE_VERTEX, IB_VERTEX_CODE_BITS );

        // free vertices are relative to the latest new vertex.
        uint32_t vertexOutput = ( newVertexCount - 1 ) - vertexRemap[ vertex ];

        // v-int encode the free vertex index.
        output.WriteVInt( vertexOutput );

        // free vertices go back into the vertex cache.
        vertexFifo[ verticesRead & VERTEX_FIFO_MASK ] = vertex;
            
        ++verticesRead;
    }

}

template <typename Ty>
void CompressIndiceCodes1( const Ty* triangles, 
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
    for ( uint32_t* remappedVertex = vertexRemap; remappedVertex < vertexRemapEnd; ++remappedVertex )
    {
        *remappedVertex = VERTEX_NOT_MAPPED;
    }

    // iterate through the triangles
    for ( const Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
    {
        int32_t lowestEdgeCursor = edgesRead >= EDGE_FIFO_SIZE ? edgesRead - EDGE_FIFO_SIZE : 0;
        int32_t edgeCursor = edgesRead - 1;
        bool     foundEdge = false;

        int32_t freeVertex = -1; // should not be negative 1 if found, this is not used as a signal, but for debugging.

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
            output.Write( IB_CACHED_EDGE, IB_VERTEX_CODE_BITS );
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

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

                ++edgesRead;
                break;

            case 1:

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

                ++edgesRead;
                break;

            case 2:

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

                ++edgesRead;

                edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

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
            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 0 ], triangle[ 1 ] );

            ++edgesRead;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 1 ], triangle[ 2 ] );

            ++edgesRead;

            edgeFifo[ edgesRead & EDGE_FIFO_MASK ].set( triangle[ 2 ], triangle[ 0 ] );

            ++edgesRead;
        }
    }
}

// Detects if there are any degenerate triangles in a set of triangles, where there is 1 or more duplicate vertices.
template <typename Ty>
bool ContainsDegenerates( const Ty* triangles, uint32_t triangleCount )
{
    const Ty* triangleEnd = triangles + ( triangleCount * 3 );
    bool      result      = false;

    for ( const Ty* triangle = triangles; triangle < triangleEnd; triangle += 3 )
    {
        if ( triangle[ 0 ] == triangle[ 1 ] || triangle[ 0 ] == triangle[ 2 ] || triangle[ 1 ] == triangle[ 2 ] )
        {
            result = true;
            break;
        }
    }

    return result;
}

template <typename Ty>
void CompressIndexBuffer( const Ty* triangles,
                          uint32_t triangleCount,
                          uint32_t* vertexRemap,
                          uint32_t vertexCount,
                          IndexBufferCompressionFormat format,
                          WriteBitstream& output )
{
    switch ( format )
    {
    case IBCF_PER_INDICE_1:

        output.WriteVInt( IBCF_PER_INDICE_1 );
        CompressIndiceCodes1<Ty>( triangles, triangleCount, vertexRemap, vertexCount, output );
        break;

    case IBCF_PER_TRIANGLE_1:

        output.WriteVInt( IBCF_PER_TRIANGLE_1 );
        CompressTriangleCodes1<Ty>( triangles, triangleCount, vertexRemap, vertexCount, output );
        break;

    case IBCF_AUTO:

        if ( ContainsDegenerates( triangles, triangleCount ) )
        {
            output.WriteVInt( IBCF_PER_INDICE_1 );
            CompressIndiceCodes1<Ty>( triangles, triangleCount, vertexRemap, vertexCount, output );
        }
        else
        {
            output.WriteVInt( IBCF_PER_TRIANGLE_1 );
            CompressTriangleCodes1<Ty>( triangles, triangleCount, vertexRemap, vertexCount, output );
        }

        break;
    }
}

void CompressIndexBuffer( const uint16_t* triangles,
                          uint32_t triangleCount,
                          uint32_t* vertexRemap,
                          uint32_t vertexCount, 
                          IndexBufferCompressionFormat format,
                          WriteBitstream& output )
{

    CompressIndexBuffer<uint16_t>( triangles, triangleCount, vertexRemap, vertexCount, format, output );
}

void CompressIndexBuffer( const uint32_t* triangles,
                          uint32_t triangleCount,
                          uint32_t* vertexRemap,
                          uint32_t vertexCount,
                          IndexBufferCompressionFormat format,
                          WriteBitstream& output )
{
    CompressIndexBuffer<uint32_t>( triangles, triangleCount, vertexRemap, vertexCount, format, output );
}


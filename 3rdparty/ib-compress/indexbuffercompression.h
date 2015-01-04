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
#ifndef INDEX_BUFFER_COMPRESSION_H__
#define INDEX_BUFFER_COMPRESSION_H__
#pragma once

#include <stdint.h>
#include "writebitstream.h"
#include "indexbuffercompressionformat.h"

// Compress an index buffer, writing the results out to a bitstream and providing a vertex remapping (which will be in pre-transform cache optimised
// order).
//
// It works by outputting a code (along with any required index symbols) per vertex.
//
// Parameters: 
//     [in]  triangles      - A typical triangle list index buffer (3 indices to vertices per triangle). 16 bit indices.
//     [in]  triangle count - The number of triangles to process.
//     [out] vertexRemap    - This will be populated with re-mappings that map old vertices to new vertex locations (a new ordering),
//                            where indexing with the old vertex index will get you the new one. Vertices that are unused will 
//                            be mapped to 0xFFFFFFFF.
//                            You should re-order the vertices and removed unused ones based on the vertex remap, instead of storing
//                            the remap. 
//                            It should be allocated as a with at least vertexCount entries.
//     [in] vertexCount     - The number of vertices in the mesh. This should be less than 0xFFFFFFFF/2^32 - 1.
//     [in] format          - The compression format to use for encoding - note the format will be encoded with the compressed data so the decompressor can select the correct algorithm.            
//     [in] output          - The stream that the compressed data will be written to. Note that we will not flush/finish the stream
//                            in case something else is going to be written after, so WriteBitstream::Finish will need to be called after this.
void CompressIndexBuffer( const uint16_t* triangles, uint32_t triangleCount, uint32_t* vertexRemap, uint32_t vertexCount, IndexBufferCompressionFormat format, WriteBitstream& output );

// Same as above but 32bit indices.
void CompressIndexBuffer( const uint32_t* triangles, uint32_t triangleCount, uint32_t* vertexRemap, uint32_t vertexCount, IndexBufferCompressionFormat format, WriteBitstream& output );

#endif // -- INDEX_BUFFER_COMPRESSION_H__
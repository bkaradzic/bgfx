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
#ifndef INDEX_BUFFER_DECOMPRESSION_H__
#define INDEX_BUFFER_DECOMPRESSION_H__
#pragma once

#include <stdint.h>
#include "readbitstream.h"

// Compress an index buffer, writing the results out to a bitstream and providing a vertex remapping (which will be in pre-transform cache optimised
// order.
// Parameters: 
//     [out] triangles      - Triangle list index buffer (3 indices to vertices per triangle), output from the decompression - 16bit indices
//     [in]  triangle count - The number of triangles to decompress.
//     [in]  input          - The bit stream that the compressed data will be read from.
void DecompressIndexBuffer( uint16_t* triangles, uint32_t triangleCount, ReadBitstream& input );

// Same as above but 32 bit indices.
void DecompressIndexBuffer( uint32_t* triangles, uint32_t triangleCount, ReadBitstream& input );

#endif // -- INDEX_BUFFER_DECOMPRESSION_H__
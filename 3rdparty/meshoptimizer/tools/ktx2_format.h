/*
 * Copyright (c) 2010-2018 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
 * Author: Mark Callow from original code by Georg Kolling
 */

/*
 * Converted from ktxint.h + basis_sgd.h by extracting meaningful structures for gltfpack
 */

#pragma once

#include <stdint.h>

#define KTX2_IDENTIFIER_REF  { 0xAB, 0x4B, 0x54, 0x58, 0x20, 0x32, 0x30, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A }
#define KTX2_HEADER_SIZE     (80)

typedef enum ktxSupercmpScheme {
    KTX_SUPERCOMPRESSION_NONE = 0,  /*!< No supercompression. */
    KTX_SUPERCOMPRESSION_BASIS = 1, /*!< Basis Universal supercompression. */
    KTX_SUPERCOMPRESSION_LZMA = 2,  /*!< LZMA supercompression. */
    KTX_SUPERCOMPRESSION_ZLIB = 3,  /*!< Zlib supercompression. */
    KTX_SUPERCOMPRESSION_ZSTD = 4,  /*!< ZStd supercompression. */
    KTX_SUPERCOMPRESSION_BEGIN_RANGE = KTX_SUPERCOMPRESSION_NONE,
    KTX_SUPERCOMPRESSION_END_RANGE = KTX_SUPERCOMPRESSION_ZSTD,
    KTX_SUPERCOMPRESSION_BEGIN_VENDOR_RANGE = 0x10000,
    KTX_SUPERCOMPRESSION_END_VENDOR_RANGE = 0x1ffff,
    KTX_SUPERCOMPRESSION_BEGIN_RESERVED = 0x20000,
} ktxSupercmpScheme;

/**
 * @internal
 * @~English
 * @brief 32-bit KTX 2 index entry.
 */
typedef struct ktxIndexEntry32 {
    uint32_t byteOffset; /*!< Offset of item from start of file. */
    uint32_t byteLength; /*!< Number of bytes of data in the item. */
} ktxIndexEntry32;
/**
 * @internal
 * @~English
 * @brief 64-bit KTX 2 index entry.
 */
typedef struct ktxIndexEntry64 {
    uint64_t byteOffset; /*!< Offset of item from start of file. */
    uint64_t byteLength; /*!< Number of bytes of data in the item. */
} ktxIndexEntry64;

/**
 * @internal
 * @~English
 * @brief KTX 2 file header.
 *
 * See the KTX 2 specification for descriptions.
 */
typedef struct KTX_header2 {
    uint8_t  identifier[12];
    uint32_t vkFormat;
    uint32_t typeSize;
    uint32_t pixelWidth;
    uint32_t pixelHeight;
    uint32_t pixelDepth;
    uint32_t layerCount;
    uint32_t faceCount;
    uint32_t levelCount;
    uint32_t supercompressionScheme;
    ktxIndexEntry32 dataFormatDescriptor;
    ktxIndexEntry32 keyValueData;
    ktxIndexEntry64 supercompressionGlobalData;
} KTX_header2;

/* This will cause compilation to fail if the struct size doesn't match */
typedef int KTX_header2_SIZE_ASSERT [sizeof(KTX_header2) == KTX2_HEADER_SIZE];

/**
 * @internal
 * @~English
 * @brief KTX 2 level index entry.
 */
typedef struct ktxLevelIndexEntry {
    uint64_t byteOffset; /*!< Offset of level from start of file. */
    uint64_t byteLength;
                /*!< Number of bytes of compressed image data in the level. */
    uint64_t uncompressedByteLength;
                /*!< Number of bytes of uncompressed image data in the level. */
} ktxLevelIndexEntry;

typedef struct ktxBasisGlobalHeader {
    uint32_t globalFlags;
    uint16_t endpointCount;
    uint16_t selectorCount;
    uint32_t endpointsByteLength;
    uint32_t selectorsByteLength;
    uint32_t tablesByteLength;
    uint32_t extendedByteLength;
} ktxBasisGlobalHeader;

// This header is followed by imageCount "slice" descriptions.

// 1, or 2 slices per image (i.e. layer, face & slice).
// These offsets are relative to start of a mip level as given by the
// main levelIndex.
typedef struct ktxBasisSliceDesc {
    uint32_t sliceFlags;
    uint32_t sliceByteOffset;
    uint32_t sliceByteLength;
    uint32_t alphaSliceByteOffset;
    uint32_t alphaSliceByteLength;
} ktxBasisSliceDesc;
/*****************************************************************************
 * wma.c
 *****************************************************************************
 * Copyright (C) 2014-2017 L-SMASH project
 *
 * Authors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *****************************************************************************/

/* This file is available under an ISC license. */

#include "common/internal.h" /* must be placed first */

#include <inttypes.h>

#include "core/box.h"

#define WFEX_BOX_MIN_LENGTH 26

#define WAVE_FORMAT_TAG_ID_WMA_V2 0x0161
#define WAVE_FORMAT_TAG_ID_WMA_V3 0x0162

int wma_print_codec_specific( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: General Extended Waveform Format Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    if( box->size < WFEX_BOX_MIN_LENGTH )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *data = box->binary;
    isom_skip_box_common( &data );
    uint16_t wFormatTag = LSMASH_GET_LE16( &data[0] );
    static const char *codec_name[] =
    {
        "Windows Media Audio V2",
        "Windows Media Audio V3"
    };
    if( wFormatTag == WAVE_FORMAT_TAG_ID_WMA_V2
     || wFormatTag == WAVE_FORMAT_TAG_ID_WMA_V3 )
        lsmash_ifprintf( fp, indent, "wFormatTag = 0x%04"PRIx16" (%s)\n", wFormatTag, codec_name[wFormatTag - WAVE_FORMAT_TAG_ID_WMA_V2] );
    else
        lsmash_ifprintf( fp, indent, "wFormatTag = 0x%04"PRIx16"\n", wFormatTag );
    lsmash_ifprintf( fp, indent, "nChannels = %"PRIu16"\n",       LSMASH_GET_LE16( &data[ 2] ) );
    lsmash_ifprintf( fp, indent, "nSamplesPerSec = %"PRIu32"\n",  LSMASH_GET_LE32( &data[ 4] ) );
    lsmash_ifprintf( fp, indent, "nAvgBytesPerSec = %"PRIu32"\n", LSMASH_GET_LE32( &data[ 8] ) );
    lsmash_ifprintf( fp, indent, "nBlockAlign = %"PRIu16"\n",     LSMASH_GET_LE16( &data[12] ) );
    lsmash_ifprintf( fp, indent, "wBitsPerSample = %"PRIu16"\n",  LSMASH_GET_LE16( &data[14] ) );
    uint16_t cbSize = LSMASH_GET_BYTE( &data[16] );
    lsmash_ifprintf( fp, indent, "cbSize = %"PRIu16"\n",           cbSize );
    switch( wFormatTag )
    {
        case WAVE_FORMAT_TAG_ID_WMA_V2 :
            if( cbSize < 10 )
                return LSMASH_ERR_INVALID_DATA;
            lsmash_ifprintf( fp, indent, "dwSamplesPerBlock = %"PRIu32"\n",  LSMASH_GET_LE32( &data[18] ) );
            lsmash_ifprintf( fp, indent, "wEncodeOptions = 0x%04"PRIu16"\n", LSMASH_GET_LE16( &data[22] ) );
            lsmash_ifprintf( fp, indent, "dwSuperBlockAlign = %"PRIu32"\n",  LSMASH_GET_LE32( &data[24] ) );
            break;
        case WAVE_FORMAT_TAG_ID_WMA_V3 :
            if( cbSize < 18 )
                return LSMASH_ERR_INVALID_DATA;
            lsmash_ifprintf( fp, indent, "wValidBitsPerSample = %"PRIu16"\n", LSMASH_GET_LE16( &data[18] ) );
            lsmash_ifprintf( fp, indent, "dwChannelMask = 0x%08"PRIu32"\n",   LSMASH_GET_LE32( &data[20] ) );
            lsmash_ifprintf( fp, indent, "dwReserved1 = 0x%08"PRIu32"\n",     LSMASH_GET_LE32( &data[24] ) );
            lsmash_ifprintf( fp, indent, "dwReserved2 = 0x%08"PRIu32"\n",     LSMASH_GET_LE32( &data[28] ) );
            lsmash_ifprintf( fp, indent, "wEncodeOptions = 0x%04"PRIu16"\n",  LSMASH_GET_LE16( &data[32] ) );
            lsmash_ifprintf( fp, indent, "wReserved3 = 0x%04"PRIu16"\n",      LSMASH_GET_LE16( &data[34] ) );
            break;
        default :
            break;
    }
    return 0;
}

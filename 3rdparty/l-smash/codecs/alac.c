/*****************************************************************************
 * alac.c
 *****************************************************************************
 * Copyright (C) 2012-2017 L-SMASH project
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

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "core/box.h"

#define ALAC_SPECIFIC_BOX_LENGTH 36

uint8_t *lsmash_create_alac_specific_info( lsmash_alac_specific_parameters_t *param, uint32_t *data_length )
{
    uint8_t buffer[ALAC_SPECIFIC_BOX_LENGTH];
    lsmash_bs_t bs = { 0 };
    bs.buffer.data  = buffer;
    bs.buffer.alloc = ALAC_SPECIFIC_BOX_LENGTH;
    lsmash_bs_put_be32( &bs, ALAC_SPECIFIC_BOX_LENGTH );    /* box size */
    lsmash_bs_put_be32( &bs, ISOM_BOX_TYPE_ALAC.fourcc );   /* box type: 'alac' */
    lsmash_bs_put_be32( &bs, 0 );                           /* version + flags */
    lsmash_bs_put_be32( &bs, param->frameLength );
    lsmash_bs_put_byte( &bs, 0 );                           /* compatibleVersion */
    lsmash_bs_put_byte( &bs, param->bitDepth );
    lsmash_bs_put_byte( &bs, 40 );                          /* pb */
    lsmash_bs_put_byte( &bs, 14 );                          /* mb */
    lsmash_bs_put_byte( &bs, 10 );                          /* kb */
    lsmash_bs_put_byte( &bs, param->numChannels );
    lsmash_bs_put_be16( &bs, 255 );                         /* maxRun */
    lsmash_bs_put_be32( &bs, param->maxFrameBytes );
    lsmash_bs_put_be32( &bs, param->avgBitrate );
    lsmash_bs_put_be32( &bs, param->sampleRate );
    return lsmash_bs_export_data( &bs, data_length );
}

int alac_construct_specific_parameters( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < ALAC_SPECIFIC_BOX_LENGTH )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_alac_specific_parameters_t *param = (lsmash_alac_specific_parameters_t *)dst->data.structured;
    uint8_t *data = src->data.unstructured;
    uint64_t size = LSMASH_GET_BE32( data );
    data += ISOM_BASEBOX_COMMON_SIZE;
    if( size == 1 )
    {
        size = LSMASH_GET_BE64( data );
        data += 8;
    }
    if( size != src->size )
        return LSMASH_ERR_INVALID_DATA;
    data += 4;  /* Skip version and flags. */
    param->frameLength   = LSMASH_GET_BE32( &data[0] );
    param->bitDepth      = LSMASH_GET_BYTE( &data[5] );
    param->numChannels   = LSMASH_GET_BYTE( &data[9] );
    param->maxFrameBytes = LSMASH_GET_BE32( &data[12] );
    param->avgBitrate    = LSMASH_GET_BE32( &data[16] );
    param->sampleRate    = LSMASH_GET_BE32( &data[20] );
    return 0;
}

int alac_print_codec_specific( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: ALAC Specific Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    if( box->size < ALAC_SPECIFIC_BOX_LENGTH )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *data = box->binary;
    isom_skip_box_common( &data );
    lsmash_ifprintf( fp, indent, "version = %"PRIu8"\n",           LSMASH_GET_BYTE( &data[0] ) );
    lsmash_ifprintf( fp, indent, "flags = 0x%06"PRIx32"\n",        LSMASH_GET_BE24( &data[1] ) );
    data += 4;
    lsmash_ifprintf( fp, indent, "frameLength = %"PRIu32"\n",      LSMASH_GET_BE32( &data[0] ) );
    lsmash_ifprintf( fp, indent, "compatibleVersion = %"PRIu8"\n", LSMASH_GET_BYTE( &data[4] ) );
    lsmash_ifprintf( fp, indent, "bitDepth = %"PRIu8"\n",          LSMASH_GET_BYTE( &data[5] ) );
    lsmash_ifprintf( fp, indent, "pb = %"PRIu8"\n",                LSMASH_GET_BYTE( &data[6] ) );
    lsmash_ifprintf( fp, indent, "mb = %"PRIu8"\n",                LSMASH_GET_BYTE( &data[7] ) );
    lsmash_ifprintf( fp, indent, "kb = %"PRIu8"\n",                LSMASH_GET_BYTE( &data[8] ) );
    lsmash_ifprintf( fp, indent, "numChannels = %"PRIu8"\n",       LSMASH_GET_BYTE( &data[9] ) );
    lsmash_ifprintf( fp, indent, "maxRun = %"PRIu16"\n",           LSMASH_GET_BE16( &data[10] ) );
    lsmash_ifprintf( fp, indent, "maxFrameBytes = %"PRIu32"\n",    LSMASH_GET_BE32( &data[12] ) );
    lsmash_ifprintf( fp, indent, "avgBitrate = %"PRIu32"\n",       LSMASH_GET_BE32( &data[16] ) );
    lsmash_ifprintf( fp, indent, "sampleRate = %"PRIu32"\n",       LSMASH_GET_BE32( &data[20] ) );
    return 0;
}

int alac_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_audio_entry_t *alac = (isom_audio_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( alac ) )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *exdata      = NULL;
    uint32_t exdata_size = 0;
    isom_box_t *alac_ext = isom_get_extension_box( &alac->extensions, QT_BOX_TYPE_WAVE );
    if( LSMASH_IS_EXISTING_BOX( alac_ext ) )
    {
        /* Apple Lossless Audio inside QuickTime file format
         * Though average bitrate field we found is always set to 0 apparently,
         * we set up maxFrameBytes and avgBitRate fields. */
        if( alac_ext->manager & LSMASH_BINARY_CODED_BOX )
            exdata = isom_get_child_box_position( alac_ext->binary, alac_ext->size, QT_BOX_TYPE_ALAC, &exdata_size );
        else
        {
            isom_wave_t *wave     = (isom_wave_t *)alac_ext;
            isom_box_t  *wave_ext = isom_get_extension_box( &wave->extensions, QT_BOX_TYPE_ALAC );
            if( !(wave_ext->manager & LSMASH_BINARY_CODED_BOX) )
                return LSMASH_ERR_INVALID_DATA;
            exdata      = wave_ext->binary;
            exdata_size = wave_ext->size;
        }
    }
    else
    {
        /* Apple Lossless Audio inside ISO Base Media file format */
        isom_box_t *ext = isom_get_extension_box( &alac->extensions, ISOM_BOX_TYPE_ALAC );
        if( !(ext->manager & LSMASH_BINARY_CODED_BOX) )
            return LSMASH_ERR_INVALID_DATA;
        exdata      = ext->binary;
        exdata_size = ext->size;
    }
    if( !exdata || exdata_size < 36 )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    if( err < 0 )
        return err;
    exdata += 24;
    /* maxFrameBytes */
    LSMASH_SET_BE32( &exdata[0], bufferSizeDB );
    /* avgBitRate */
    LSMASH_SET_BE32( &exdata[4], avgBitrate );
    return 0;
}

#undef ALAC_SPECIFIC_BOX_LENGTH

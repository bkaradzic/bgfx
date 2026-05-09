/*****************************************************************************
 * qt_wfex.c
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

#include "core/box.h"

/*********************************************************************************
    QuickTime Waveform Audio
**********************************************************************************/

int waveform_audio_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_sample_entry_t *sample_entry = (isom_sample_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_box_t *ext = isom_get_extension_box( &sample_entry->extensions, QT_BOX_TYPE_WAVE );
    if( LSMASH_IS_NON_EXISTING_BOX( ext ) )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *exdata      = NULL;
    uint32_t exdata_size = 0;
    if( ext->manager & LSMASH_BINARY_CODED_BOX )
        exdata = isom_get_child_box_position( ext->binary, ext->size, sample_entry->type, &exdata_size );
    else
    {
        isom_wave_t *wave     = (isom_wave_t *)ext;
        isom_box_t  *wave_ext = isom_get_extension_box( &wave->extensions, sample_entry->type );
        if( !(wave_ext->manager & LSMASH_BINARY_CODED_BOX) )
            return LSMASH_ERR_INVALID_DATA;
        exdata      = wave_ext->binary;
        exdata_size = wave_ext->size;
    }
    /* Check whether exdata is valid or not. */
    if( !exdata || exdata_size < ISOM_BASEBOX_COMMON_SIZE + 18 )
        return LSMASH_ERR_INVALID_DATA;
    exdata += ISOM_BASEBOX_COMMON_SIZE;
    uint16_t cbSize = LSMASH_GET_LE16( &exdata[16] );
    if( exdata_size < ISOM_BASEBOX_COMMON_SIZE + 18 + cbSize )
        return LSMASH_ERR_INVALID_DATA;
    /* WAVEFORMATEX.nAvgBytesPerSec */
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    if( err < 0 )
        return err;
    uint32_t nAvgBytesPerSec = avgBitrate / 8;
    LSMASH_SET_LE32( &exdata[8], nAvgBytesPerSec );
    if( lsmash_check_codec_type_identical( sample_entry->type, QT_CODEC_TYPE_FULLMP3_AUDIO )
     || lsmash_check_codec_type_identical( sample_entry->type, QT_CODEC_TYPE_MP3_AUDIO ) )
    {
        /* MPEGLAYER3WAVEFORMAT.nBlockSize */
        uint32_t nSamplesPerSec  = LSMASH_GET_LE32( &exdata[ 4] );
        uint16_t nFramesPerBlock = LSMASH_GET_LE16( &exdata[26] );
        uint16_t padding         = 0;   /* FIXME? */
        uint16_t nBlockSize      = (144 * (avgBitrate / nSamplesPerSec) + padding) * nFramesPerBlock;
        LSMASH_SET_LE16( &exdata[24], nBlockSize );
    }
    return 0;
}

/*****************************************************************************
 * nalu.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
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

#include <string.h>

#include "core/box.h"

#include "nalu.h"

isom_dcr_ps_entry_t *isom_create_ps_entry
(
    uint8_t *ps,
    uint32_t ps_size
)
{
    isom_dcr_ps_entry_t *entry = lsmash_malloc( sizeof(isom_dcr_ps_entry_t) );
    if( !entry )
        return NULL;
    entry->nalUnit = lsmash_memdup( ps, ps_size );
    if( !entry->nalUnit )
    {
        lsmash_free( entry );
        return NULL;
    }
    entry->nalUnitLength = ps_size;
    entry->unused        = 0;
    return entry;
}

void isom_remove_dcr_ps
(
    isom_dcr_ps_entry_t *ps
)
{
    if( !ps )
        return;
    lsmash_free( ps->nalUnit );
    lsmash_free( ps );
}

/* Convert EBSP (Encapsulated Byte Sequence Packets) to RBSP (Raw Byte Sequence Packets). */
static uint8_t *nalu_remove_emulation_prevention
(
    uint8_t *src,
    uint64_t src_length,
    uint8_t *dst
)
{
    uint8_t *src_end = src + src_length;
    while( src < src_end )
        if( ((src + 2) < src_end) && !src[0] && !src[1] && (src[2] == 0x03) )
        {
            /* 0x000003 -> 0x0000 */
            *dst++ = *src++;
            *dst++ = *src++;
            src++;  /* Skip emulation_prevention_three_byte (0x03). */
        }
        else
            *dst++ = *src++;
    return dst;
}

int nalu_import_rbsp_from_ebsp
(
    lsmash_bits_t *bits,
    uint8_t       *rbsp_buffer,
    uint64_t      *rbsp_size,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint8_t *rbsp_start = rbsp_buffer;
    uint8_t *rbsp_end   = nalu_remove_emulation_prevention( ebsp, ebsp_size, rbsp_buffer );
    *rbsp_size = (uint64_t)(rbsp_end - rbsp_start);
    if( *rbsp_size > ebsp_size )
        return LSMASH_ERR_INVALID_DATA;
    return lsmash_bits_import_data( bits, rbsp_start, *rbsp_size );
}

int nalu_check_more_rbsp_data
(
    lsmash_bits_t *bits
)
{
    lsmash_bs_t *bs = bits->bs;
    lsmash_buffer_t *buffer = &bs->buffer;
    if( buffer->pos < buffer->store && !(bits->store == 0 && (buffer->store == buffer->pos + 1)) )
        return 1;       /* rbsp_trailing_bits will be placed at the next or later byte.
                         * Note: bs->pos points at the next byte if bits->store isn't empty. */
    if( bits->store == 0 )
    {
        if( buffer->store == buffer->pos + 1 )
            return buffer->data[ buffer->pos ] != 0x80;
        /* No rbsp_trailing_bits is present in RBSP data. */
        bs->error = 1;
        return 0;
    }
    /* Check whether remainder of bits is identical to rbsp_trailing_bits. */
    uint8_t remainder_bits = bits->cache & ~(~0U << bits->store);
    uint8_t rbsp_trailing_bits = 1U << (bits->store - 1);
    return remainder_bits != rbsp_trailing_bits;
}

int nalu_get_max_ps_length
(
    lsmash_entry_list_t *ps_list,
    uint32_t            *max_ps_length
)
{
    *max_ps_length = 0;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return LSMASH_ERR_NAMELESS;
        if( ps->unused )
            continue;
        *max_ps_length = LSMASH_MAX( *max_ps_length, ps->nalUnitLength );
    }
    return 0;
}

int nalu_get_ps_count
(
    lsmash_entry_list_t *ps_list,
    uint32_t            *ps_count
)
{
    *ps_count = 0;
    for( lsmash_entry_t *entry = ps_list ? ps_list->head : NULL; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return LSMASH_ERR_NAMELESS;
        if( ps->unused )
            continue;
        ++(*ps_count);
    }
    return 0;
}

int nalu_check_same_ps_existence
(
    lsmash_entry_list_t *ps_list,
    void                *ps_data,
    uint32_t             ps_length
)
{
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return LSMASH_ERR_NAMELESS;
        if( ps->unused )
            continue;
        if( ps->nalUnitLength == ps_length && !memcmp( ps->nalUnit, ps_data, ps_length ) )
            return 1;   /* The same parameter set already exists. */
    }
    return 0;
}

int nalu_get_dcr_ps
(
    lsmash_bs_t         *bs,
    lsmash_entry_list_t *list,
    uint8_t              entry_count
)
{
    for( uint8_t i = 0; i < entry_count; i++ )
    {
        isom_dcr_ps_entry_t *data = lsmash_malloc( sizeof(isom_dcr_ps_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->nalUnitLength = lsmash_bs_get_be16( bs );
        data->nalUnit       = lsmash_bs_get_bytes( bs, data->nalUnitLength );
        if( !data->nalUnit )
        {
            lsmash_list_remove_entries( list );
            return LSMASH_ERR_NAMELESS;
        }
    }
    return 0;
}

/* Return the offset from the beginning of stream if a start code is found.
 * Return NALU_NO_START_CODE_FOUND otherwise. */
uint64_t nalu_find_first_start_code
(
    lsmash_bs_t *bs
)
{
    uint64_t first_sc_head_pos = 0;
    while( 1 )
    {
        if( lsmash_bs_is_error( bs ) )
            return NALU_IO_ERROR;
        if( lsmash_bs_is_end( bs, first_sc_head_pos + NALU_LONG_START_CODE_LENGTH ) )
            return NALU_NO_START_CODE_FOUND;
        /* Invalid if encountered any value of non-zero before the first start code. */
        if( lsmash_bs_show_byte( bs, first_sc_head_pos ) )
            return NALU_NO_START_CODE_FOUND;
        /* The first NALU of an AU in decoding order shall have long start code (0x00000001). */
        if( 0x00000001 == lsmash_bs_show_be32( bs, first_sc_head_pos ) )
            break;
        ++first_sc_head_pos;
    }
    return first_sc_head_pos;
}

uint64_t nalu_get_codeNum
(
    lsmash_bits_t *bits
)
{
    uint32_t leadingZeroBits = 0;
    for( int b = 0; !b; leadingZeroBits++ )
        b = lsmash_bits_get( bits, 1 );
    --leadingZeroBits;
    return ((uint64_t)1 << leadingZeroBits) - 1 + lsmash_bits_get( bits, leadingZeroBits );
}

int nalu_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_visual_entry_t *sample_entry = (isom_visual_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_btrt_t *btrt = (isom_btrt_t *)isom_get_extension_box_format( &sample_entry->extensions, ISOM_BOX_TYPE_BTRT );
    if( LSMASH_IS_EXISTING_BOX( btrt ) )
    {
        uint32_t bufferSizeDB;
        uint32_t maxBitrate;
        uint32_t avgBitrate;
        int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
        if( err < 0 )
            return err;
        btrt->bufferSizeDB = bufferSizeDB;
        btrt->maxBitrate   = maxBitrate;
        btrt->avgBitrate   = avgBitrate;
    }
    return 0;
}

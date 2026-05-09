/*****************************************************************************
 * vc1.c
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

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "core/box.h"

/***************************************************************************
    SMPTE 421M-2006
    SMPTE RP 2025-2007
***************************************************************************/
#include "vc1.h"

struct lsmash_vc1_header_tag
{
    uint8_t *ebdu;
    uint32_t ebdu_size;
};

typedef enum
{
    VC1_ADVANCED_PICTURE_TYPE_P       = 0x0,        /* 0b0 */
    VC1_ADVANCED_PICTURE_TYPE_B       = 0x2,        /* 0b10 */
    VC1_ADVANCED_PICTURE_TYPE_I       = 0x6,        /* 0b110 */
    VC1_ADVANCED_PICTURE_TYPE_BI      = 0xE,        /* 0b1110 */
    VC1_ADVANCED_PICTURE_TYPE_SKIPPED = 0xF,        /* 0b1111 */
} vc1_picture_type;

typedef enum
{
    VC1_ADVANCED_FIELD_PICTURE_TYPE_II   = 0x0,     /* 0b000 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_IP   = 0x1,     /* 0b001 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_PI   = 0x2,     /* 0b010 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_PP   = 0x3,     /* 0b011 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_BB   = 0x4,     /* 0b100 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_BBI  = 0x5,     /* 0b101 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_BIB  = 0x6,     /* 0b110 */
    VC1_ADVANCED_FIELD_PICTURE_TYPE_BIBI = 0x7,     /* 0b111 */
} vc1_field_picture_type;

typedef enum
{
    VC1_FRAME_CODING_MODE_PROGRESSIVE     = 0x0,    /* 0b0 */
    VC1_FRAME_CODING_MODE_FRAME_INTERLACE = 0x2,    /* 0b10 */
    VC1_FRAME_CODING_MODE_FIELD_INTERLACE = 0x3,    /* 0b11 */
} vc1_frame_coding_mode;

static void vc1_destroy_header( lsmash_vc1_header_t *hdr )
{
    if( !hdr )
        return;
    lsmash_free( hdr->ebdu );
    lsmash_free( hdr );
}

void lsmash_destroy_vc1_headers( lsmash_vc1_specific_parameters_t *param )
{
    if( !param )
        return;
    vc1_destroy_header( param->seqhdr );
    vc1_destroy_header( param->ephdr );
    param->seqhdr = NULL;
    param->ephdr  = NULL;
}

void vc1_destruct_specific_data( void *data )
{
    if( !data )
        return;
    lsmash_destroy_vc1_headers( data );
    lsmash_free( data );
}

void vc1_cleanup_parser( vc1_info_t *info )
{
    if( !info )
        return;
    lsmash_destroy_vc1_headers( &info->dvc1_param );
    lsmash_destroy_multiple_buffers( info->buffer.bank );
    lsmash_bits_adhoc_cleanup( info->bits );
    info->bits = NULL;
}

int vc1_setup_parser
(
    vc1_info_t *info,
    int         parse_only
)
{
    assert( info );
    memset( info, 0, sizeof(vc1_info_t) );
    vc1_stream_buffer_t *sb = &info->buffer;
    sb->bank = lsmash_create_multiple_buffers( parse_only ? 1 : 3, VC1_DEFAULT_BUFFER_SIZE );
    if( !sb->bank )
        return LSMASH_ERR_MEMORY_ALLOC;
    sb->rbdu = lsmash_withdraw_buffer( sb->bank, 1 );
    if( !parse_only )
    {
        info->access_unit.data            = lsmash_withdraw_buffer( sb->bank, 2 );
        info->access_unit.incomplete_data = lsmash_withdraw_buffer( sb->bank, 3 );
    }
    info->bits = lsmash_bits_adhoc_create();
    if( !info->bits )
    {
        lsmash_destroy_multiple_buffers( sb->bank );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    info->prev_bdu_type = 0xFF; /* 0xFF is a forbidden value. */
    return 0;
}

uint64_t vc1_find_next_start_code_prefix
(
    lsmash_bs_t *bs,
    uint8_t     *bdu_type,
    uint64_t    *trailing_zero_bytes
)
{
    uint64_t length = 0;    /* the length of the latest EBDU */
    uint64_t count  = 0;    /* the number of the trailing zero bytes after the latest EBDU */
    if( !lsmash_bs_is_end( bs, VC1_START_CODE_LENGTH - 1 )
     && 0x000001 == lsmash_bs_show_be24( bs, 0 ) )
    {
        *bdu_type = lsmash_bs_show_byte( bs, VC1_START_CODE_PREFIX_LENGTH );
        length = VC1_START_CODE_LENGTH;
        /* Find the start code of the next EBDU and get the length of the latest EBDU. */
        int no_more = lsmash_bs_is_end( bs, length + VC1_START_CODE_LENGTH - 1 );
        if( !no_more )
        {
            uint32_t sync_bytes = lsmash_bs_show_be24( bs, length );
            while( 0x000001 != sync_bytes )
            {
                no_more = lsmash_bs_is_end( bs, ++length + VC1_START_CODE_LENGTH - 1 );
                if( no_more )
                    break;
                sync_bytes <<= 8;
                sync_bytes  |= lsmash_bs_show_byte( bs, length + VC1_START_CODE_PREFIX_LENGTH - 1 );
                sync_bytes  &= 0xFFFFFF;
            }
        }
        if( no_more )
            length = lsmash_bs_get_remaining_buffer_size( bs );
        /* Any EBDU has no consecutive zero bytes at the end. */
        while( 0x00 == lsmash_bs_show_byte( bs, length - 1 ) )
        {
            --length;
            ++count;
        }
    }
    else
        *bdu_type = 0xFF;   /* 0xFF is a forbidden value. */
    *trailing_zero_bytes = count;
    return length;
}

int vc1_check_next_start_code_suffix
(
    lsmash_bs_t *bs,
    uint8_t     *p_bdu_type
)
{
    uint8_t bdu_type = *((uint8_t *)lsmash_bs_get_buffer_data( bs ) + VC1_START_CODE_PREFIX_LENGTH);
    if( (bdu_type >= 0x00 && bdu_type <= 0x09)
     || (bdu_type >= 0x20 && bdu_type <= 0x7F) )
        return LSMASH_ERR_NAMELESS;     /* SMPTE reserved */
    if( bdu_type >= 0x80 && bdu_type <= 0xFF )
        return LSMASH_ERR_INVALID_DATA; /* Forbidden */
    *p_bdu_type = bdu_type;
    return 0;
}

static inline uint8_t vc1_get_vlc( lsmash_bits_t *bits, int length )
{
    uint8_t value = 0;
    for( int i = 0; i < length; i++ )
        if( lsmash_bits_get( bits, 1 ) )
            value = (value << 1) | 1;
        else
        {
            value = value << 1;
            break;
        }
    return value;
}

/* Convert EBDU (Encapsulated Byte Data Unit) to RBDU (Raw Byte Data Unit). */
static uint8_t *vc1_remove_emulation_prevention( uint8_t *src, uint64_t src_length, uint8_t *dst )
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

static int vc1_import_rbdu_from_ebdu( lsmash_bits_t *bits, uint8_t *rbdu_buffer, uint8_t *ebdu, uint64_t ebdu_size )
{
    uint8_t *rbdu_start  = rbdu_buffer;
    uint8_t *rbdu_end    = vc1_remove_emulation_prevention( ebdu, ebdu_size, rbdu_buffer );
    uint64_t rbdu_length = rbdu_end - rbdu_start;
    return lsmash_bits_import_data( bits, rbdu_start, rbdu_length );
}

static void vc1_parse_hrd_param( lsmash_bits_t *bits, vc1_hrd_param_t *hrd_param )
{
    hrd_param->hrd_num_leaky_buckets = lsmash_bits_get( bits, 5 );
    lsmash_bits_get( bits, 4 );     /* bitrate_exponent */
    lsmash_bits_get( bits, 4 );     /* buffer_size_exponent */
    for( uint8_t i = 0; i < hrd_param->hrd_num_leaky_buckets; i++ )
    {
        lsmash_bits_get( bits, 16 );    /* hrd_rate */
        lsmash_bits_get( bits, 16 );    /* hrd_buffer */
    }
}

int vc1_parse_sequence_header( vc1_info_t *info, uint8_t *ebdu, uint64_t ebdu_size, int try_append )
{
    lsmash_bits_t *bits = info->bits;
    vc1_sequence_header_t *sequence = &info->sequence;
    int err = vc1_import_rbdu_from_ebdu( bits, info->buffer.rbdu, ebdu + VC1_START_CODE_LENGTH, ebdu_size );
    if( err < 0 )
        return err;
    memset( sequence, 0, sizeof(vc1_sequence_header_t) );
    sequence->profile          = lsmash_bits_get( bits, 2 );
    if( sequence->profile != 3 )
        return LSMASH_ERR_NAMELESS; /* SMPTE Reserved */
    sequence->level            = lsmash_bits_get( bits, 3 );
    if( sequence->level > 4 )
        return LSMASH_ERR_NAMELESS; /* SMPTE Reserved */
    sequence->colordiff_format = lsmash_bits_get( bits, 2 );
    if( sequence->colordiff_format != 1 )
        return LSMASH_ERR_NAMELESS; /* SMPTE Reserved */
    lsmash_bits_get( bits, 9 );     /* frmrtq_postproc (3)
                                     * bitrtq_postproc (5)
                                     * postproc_flag   (1) */
    sequence->max_coded_width  = lsmash_bits_get( bits, 12 );
    sequence->max_coded_height = lsmash_bits_get( bits, 12 );
    lsmash_bits_get( bits, 1 );     /* pulldown */
    sequence->interlace        = lsmash_bits_get( bits, 1 );
    lsmash_bits_get( bits, 4 );     /* tfcntrflag  (1)
                                     * finterpflag (1)
                                     * reserved    (1)
                                     * psf         (1) */
    if( lsmash_bits_get( bits, 1 ) )    /* display_ext */
    {
        sequence->disp_horiz_size = lsmash_bits_get( bits, 14 ) + 1;
        sequence->disp_vert_size  = lsmash_bits_get( bits, 14 ) + 1;
        if( lsmash_bits_get( bits, 1 ) )    /* aspect_ratio_flag */
        {
            uint8_t aspect_ratio = lsmash_bits_get( bits, 4 );
            if( aspect_ratio == 15 )
            {
                sequence->aspect_width  = lsmash_bits_get( bits, 8 ) + 1;   /* aspect_horiz_size */
                sequence->aspect_height = lsmash_bits_get( bits, 8 ) + 1;   /* aspect_vert_size */
            }
            else
            {
                static const struct
                {
                    uint32_t aspect_width;
                    uint32_t aspect_height;
                } vc1_aspect_ratio[15] =
                    {
                        {  0,  0 }, {  1,  1 }, { 12, 11 }, { 10, 11 }, { 16, 11 }, { 40, 33 }, {  24, 11 },
                        { 20, 11 }, { 32, 11 }, { 80, 33 }, { 18, 11 }, { 15, 11 }, { 64, 33 }, { 160, 99 },
                        {  0,  0 }  /* SMPTE Reserved */
                    };
                sequence->aspect_width  = vc1_aspect_ratio[ aspect_ratio ].aspect_width;
                sequence->aspect_height = vc1_aspect_ratio[ aspect_ratio ].aspect_height;
            }
        }
        sequence->framerate_flag = lsmash_bits_get( bits, 1 );
        if( sequence->framerate_flag )
        {
            if( lsmash_bits_get( bits, 1 ) )    /* framerateind */
            {
                sequence->framerate_numerator   = lsmash_bits_get( bits, 16 ) + 1;
                sequence->framerate_denominator = 32;
            }
            else
            {
                static const uint32_t vc1_frameratenr_table[8] = { 0, 24, 25, 30, 50, 60, 48, 72 };
                uint8_t frameratenr = lsmash_bits_get( bits, 8 );
                if( frameratenr == 0 )
                    return LSMASH_ERR_INVALID_DATA; /* Forbidden */
                if( frameratenr > 7 )
                    return LSMASH_ERR_NAMELESS; /* SMPTE Reserved */
                uint8_t frameratedr = lsmash_bits_get( bits, 4 );
                if( frameratedr != 1 && frameratedr != 2 )
                    /* 0: Forbidden, 3-15: SMPTE Reserved */
                    return frameratedr == 0
                         ? LSMASH_ERR_INVALID_DATA
                         : LSMASH_ERR_NAMELESS;
                if( frameratedr == 1 )
                {
                    sequence->framerate_numerator = vc1_frameratenr_table[ frameratenr ];
                    sequence->framerate_denominator = 1;
                }
                else
                {
                    sequence->framerate_numerator = vc1_frameratenr_table[ frameratenr ] * 1000;
                    sequence->framerate_denominator = 1001;
                }
            }
        }
        if( lsmash_bits_get( bits, 1 ) )    /* color_format_flag */
        {
            sequence->color_prim    = lsmash_bits_get( bits, 8 );
            sequence->transfer_char = lsmash_bits_get( bits, 8 );
            sequence->matrix_coef   = lsmash_bits_get( bits, 8 );
        }
        sequence->hrd_param_flag = lsmash_bits_get( bits, 1 );
        if( sequence->hrd_param_flag )
            vc1_parse_hrd_param( bits, &sequence->hrd_param );
    }
    /* '1' and stuffing bits ('0's) */
    if( !lsmash_bits_get( bits, 1 ) )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bits_empty( bits );
    /* Preparation for creating VC1SpecificBox */
    if( try_append )
    {
        /* Update some specific parameters. */
        lsmash_vc1_specific_parameters_t *param = &info->dvc1_param;
        lsmash_vc1_header_t *seqhdr = param->seqhdr;
        if( !seqhdr )
        {
            seqhdr = lsmash_malloc( sizeof(lsmash_vc1_header_t) );
            if( !seqhdr )
                return LSMASH_ERR_MEMORY_ALLOC;
            seqhdr->ebdu = lsmash_memdup( ebdu, ebdu_size );
            if( !seqhdr->ebdu )
            {
                lsmash_free( seqhdr );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            seqhdr->ebdu_size = ebdu_size;
            param->seqhdr = seqhdr;
        }
        else if( seqhdr && seqhdr->ebdu && (seqhdr->ebdu_size == ebdu_size) )
            param->multiple_sequence |= !!memcmp( ebdu, seqhdr->ebdu, seqhdr->ebdu_size );
        param->profile     = sequence->profile << 2;
        param->level       = LSMASH_MAX( param->level, sequence->level );
        param->interlaced |= sequence->interlace;
        uint32_t framerate = sequence->framerate_flag
                           ? ((double)sequence->framerate_numerator / sequence->framerate_denominator) + 0.5
                           : 0xffffffff;    /* 0xffffffff means framerate is unknown or unspecified. */
        if( param->framerate == 0 )
            param->framerate = framerate;
        else if( param->framerate != framerate )
            param->framerate = 0xffffffff;
    }
    info->sequence.present = 1;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int vc1_parse_entry_point_header( vc1_info_t *info, uint8_t *ebdu, uint64_t ebdu_size, int try_append )
{
    lsmash_bits_t *bits = info->bits;
    vc1_sequence_header_t *sequence = &info->sequence;
    vc1_entry_point_t *entry_point = &info->entry_point;
    int err = vc1_import_rbdu_from_ebdu( bits, info->buffer.rbdu, ebdu + VC1_START_CODE_LENGTH, ebdu_size );
    if( err < 0 )
        return err;
    memset( entry_point, 0, sizeof(vc1_entry_point_t) );
    uint8_t broken_link_flag = lsmash_bits_get( bits, 1 );          /* 0: no concatenation between the current and the previous entry points
                                                                     * 1: concatenated and needed to discard B-pictures */
    entry_point->closed_entry_point = lsmash_bits_get( bits, 1 );   /* 0: Open RAP, 1: Closed RAP */
    if( broken_link_flag && entry_point->closed_entry_point )
        return LSMASH_ERR_INVALID_DATA; /* invalid combination */
    lsmash_bits_get( bits, 4 );         /* panscan_flag (1)
                                         * refdist_flag (1)
                                         * loopfilter   (1)
                                         * fastuvmc     (1) */
    uint8_t extended_mv = lsmash_bits_get( bits, 1 );
    lsmash_bits_get( bits, 6 );         /* dquant       (2)
                                         * vstransform  (1)
                                         * overlap      (1)
                                         * quantizer    (2) */
    if( sequence->hrd_param_flag )
        for( uint8_t i = 0; i < sequence->hrd_param.hrd_num_leaky_buckets; i++ )
            lsmash_bits_get( bits, 8 ); /* hrd_full */
    /* Decide coded size here.
     * The correct formula is defined in Amendment 2:2011 to SMPTE ST 421M:2006.
     * Don't use the formula specified in SMPTE 421M-2006. */
    uint16_t coded_width;
    uint16_t coded_height;
    if( lsmash_bits_get( bits, 1 ) )    /* coded_size_flag */
    {
        coded_width  = lsmash_bits_get( bits, 12 );
        coded_height = lsmash_bits_get( bits, 12 );
    }
    else
    {
        coded_width  = sequence->max_coded_width;
        coded_height = sequence->max_coded_height;
    }
    coded_width  = 2 * (coded_width  + 1);  /* corrected */
    coded_height = 2 * (coded_height + 1);  /* corrected */
    if( sequence->disp_horiz_size == 0 || sequence->disp_vert_size == 0 )
    {
        sequence->disp_horiz_size = coded_width;
        sequence->disp_vert_size  = coded_height;
    }
    /* */
    if( extended_mv )
        lsmash_bits_get( bits, 1 );     /* extended_dmv */
    if( lsmash_bits_get( bits, 1 ) )    /* range_mapy_flag */
        lsmash_bits_get( bits, 3 );     /* range_mapy */
    if( lsmash_bits_get( bits, 1 ) )    /* range_mapuv_flag */
        lsmash_bits_get( bits, 3 );     /* range_mapuv */
    /* '1' and stuffing bits ('0's) */
    if( !lsmash_bits_get( bits, 1 ) )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bits_empty( bits );
    /* Preparation for creating VC1SpecificBox */
    if( try_append )
    {
        lsmash_vc1_specific_parameters_t *param = &info->dvc1_param;
        lsmash_vc1_header_t *ephdr = param->ephdr;
        if( !ephdr )
        {
            ephdr = lsmash_malloc( sizeof(lsmash_vc1_header_t) );
            if( !ephdr )
                return LSMASH_ERR_MEMORY_ALLOC;
            ephdr->ebdu = lsmash_memdup( ebdu, ebdu_size );
            if( !ephdr->ebdu )
            {
                lsmash_free( ephdr );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            ephdr->ebdu_size = ebdu_size;
            param->ephdr = ephdr;
        }
        else if( ephdr && ephdr->ebdu && (ephdr->ebdu_size == ebdu_size) )
            param->multiple_entry |= !!memcmp( ebdu, ephdr->ebdu, ephdr->ebdu_size );
    }
    info->entry_point.present = 1;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int vc1_parse_advanced_picture( lsmash_bits_t *bits,
                                vc1_sequence_header_t *sequence, vc1_picture_info_t *picture,
                                uint8_t *rbdu_buffer, uint8_t *ebdu, uint64_t ebdu_size )
{
    int err = vc1_import_rbdu_from_ebdu( bits, rbdu_buffer, ebdu + VC1_START_CODE_LENGTH, ebdu_size );
    if( err < 0 )
        return err;
    if( sequence->interlace )
        picture->frame_coding_mode = vc1_get_vlc( bits, 2 );
    else
        picture->frame_coding_mode = 0;
    if( picture->frame_coding_mode != 0x3 )
        picture->type = vc1_get_vlc( bits, 4 );         /* ptype (variable length) */
    else
        picture->type = lsmash_bits_get( bits, 3 );     /* fptype (3) */
    picture->present = 1;
    lsmash_bits_empty( bits );
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

void vc1_update_au_property( vc1_access_unit_t *access_unit, vc1_picture_info_t *picture )
{
    access_unit->random_accessible = picture->random_accessible;
    access_unit->closed_gop        = picture->closed_gop;
    /* I-picture
     *      Be coded using information only from itself. (independent)
     *      All the macroblocks in an I-picture are intra-coded.
     * P-picture
     *      Be coded using motion compensated prediction from past reference fields or frame.
     *      Can contain macroblocks that are inter-coded (i.e. coded using prediction) and macroblocks that are intra-coded.
     * B-picture
     *      Be coded using motion compensated prediction from past and/or future reference fields or frames. (bi-predictive)
     *      Cannot be used for predicting any other picture. (disposable)
     * BI-picture
     *      All the macroblocks in BI-picture are intra-coded. (independent)
     *      Cannot be used for predicting any other picture. (disposable) */
    if( picture->frame_coding_mode == 0x3 )
    {
        /* field interlace */
        access_unit->independent      = picture->type == VC1_ADVANCED_FIELD_PICTURE_TYPE_II || picture->type == VC1_ADVANCED_FIELD_PICTURE_TYPE_BIBI;
        access_unit->non_bipredictive = picture->type <  VC1_ADVANCED_FIELD_PICTURE_TYPE_BB || picture->type == VC1_ADVANCED_FIELD_PICTURE_TYPE_BIBI;
        access_unit->disposable       = picture->type >= VC1_ADVANCED_FIELD_PICTURE_TYPE_BB;
    }
    else
    {
        /* frame progressive/interlace */
        access_unit->independent      = picture->type == VC1_ADVANCED_PICTURE_TYPE_I || picture->type == VC1_ADVANCED_PICTURE_TYPE_BI;
        access_unit->non_bipredictive = picture->type != VC1_ADVANCED_PICTURE_TYPE_B;
        access_unit->disposable       = picture->type == VC1_ADVANCED_PICTURE_TYPE_B || picture->type == VC1_ADVANCED_PICTURE_TYPE_BI;
    }
    picture->present           = 0;
    picture->type              = 0;
    picture->closed_gop        = 0;
    picture->start_of_sequence = 0;
    picture->random_accessible = 0;
}

int vc1_find_au_delimit_by_bdu_type( uint8_t bdu_type, uint8_t prev_bdu_type )
{
    /* In any access unit, EBDU with smaller least significant 8-bits of BDU type doesn't precede EBDU with larger one.
     * Therefore, the condition: (bdu_type 0xF) > (prev_bdu_type & 0xF) is more precisely.
     * No two or more frame start codes shall be in the same access unit. */
    return bdu_type > prev_bdu_type || (bdu_type == 0x0D && prev_bdu_type == 0x0D);
}

int vc1_supplement_buffer( vc1_stream_buffer_t *sb, vc1_access_unit_t *access_unit, uint32_t size )
{
    lsmash_multiple_buffers_t *bank = lsmash_resize_multiple_buffers( sb->bank, size );
    if( !bank )
        return LSMASH_ERR_MEMORY_ALLOC;
    sb->bank = bank;
    sb->rbdu = lsmash_withdraw_buffer( bank, 1 );
    if( access_unit && bank->number_of_buffers == 3 )
    {
        access_unit->data            = lsmash_withdraw_buffer( bank, 2 );
        access_unit->incomplete_data = lsmash_withdraw_buffer( bank, 3 );
    }
    return 0;
}

uint8_t *lsmash_create_vc1_specific_info( lsmash_vc1_specific_parameters_t *param, uint32_t *data_length )
{
    if( !param || !data_length )
        return NULL;
    if( !param->seqhdr || !param->ephdr )
        return NULL;
    /* Calculate enough buffer size. */
    lsmash_vc1_header_t *seqhdr = param->seqhdr;
    lsmash_vc1_header_t *ephdr  = param->ephdr;
    /* Create a VC1SpecificBox */
    lsmash_bits_t *bits = lsmash_bits_adhoc_create();
    if( !bits )
        return NULL;
    lsmash_bits_put( bits, 32, 0 );                         /* box size */
    lsmash_bits_put( bits, 32, ISOM_BOX_TYPE_DVC1.fourcc ); /* box type: 'dvc1' */
    lsmash_bits_put( bits, 4, param->profile );             /* profile */
    lsmash_bits_put( bits, 3, param->level );               /* level */
    lsmash_bits_put( bits, 1, 0 );                          /* reserved */
    /* VC1AdvDecSpecStruc (for Advanced Profile) */
    lsmash_bits_put( bits, 3, param->level );               /* level (identical to the previous level field) */
    lsmash_bits_put( bits, 1, param->cbr );                 /* cbr */
    lsmash_bits_put( bits, 6, 0 );                          /* reserved */
    lsmash_bits_put( bits, 1, !param->interlaced );         /* no_interlace */
    lsmash_bits_put( bits, 1, !param->multiple_sequence );  /* no_multiple_seq */
    lsmash_bits_put( bits, 1, !param->multiple_entry );     /* no_multiple_entry */
    lsmash_bits_put( bits, 1, !param->slice_present );      /* no_slice_code */
    lsmash_bits_put( bits, 1, !param->bframe_present );     /* no_bframe */
    lsmash_bits_put( bits, 1, 0 );                          /* reserved */
    lsmash_bits_put( bits, 32, param->framerate );          /* framerate */
    /* seqhdr_ephdr[] */
    for( uint32_t i = 0; i < seqhdr->ebdu_size; i++ )
        lsmash_bits_put( bits, 8, *(seqhdr->ebdu + i) );
    for( uint32_t i = 0; i < ephdr->ebdu_size; i++ )
        lsmash_bits_put( bits, 8, *(ephdr->ebdu + i) );
    /* */
    uint8_t *data = lsmash_bits_export_data( bits, data_length );
    lsmash_bits_adhoc_cleanup( bits );
    /* Update box size. */
    LSMASH_SET_BE32( data, *data_length );
    return data;
}

static int vc1_try_to_put_header( lsmash_vc1_header_t **p_hdr, uint8_t *multiple_hdr, void *hdr_data, uint32_t hdr_length )
{
    lsmash_vc1_header_t *hdr = *p_hdr;
    if( !hdr )
    {
        hdr = lsmash_malloc_zero( sizeof(lsmash_vc1_header_t) );
        if( !hdr )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    else if( hdr->ebdu )
    {
        *multiple_hdr |= hdr->ebdu_size == hdr_length ? !!memcmp( hdr_data, hdr->ebdu, hdr->ebdu_size ) : 1;
        return 0;
    }
    hdr->ebdu = lsmash_memdup( hdr_data, hdr_length );
    hdr->ebdu_size = hdr->ebdu ? hdr_length : 0;
    *p_hdr = hdr;
    return hdr->ebdu ? 0 : LSMASH_ERR_MEMORY_ALLOC;
}

int lsmash_put_vc1_header( lsmash_vc1_specific_parameters_t *param, void *hdr_data, uint32_t hdr_length )
{
    if( !param || !hdr_data || hdr_length < 5 )
        return LSMASH_ERR_FUNCTION_PARAM;
    /* Check start code prefix (0x000001). */
    uint8_t *data = (uint8_t *)hdr_data;
    if( data[0] != 0x00 || data[1] != 0x00 || data[2] != 0x01 )
        return LSMASH_ERR_INVALID_DATA;
    if( data[3] == 0x0F )       /* sequence header */
        return vc1_try_to_put_header( &param->seqhdr, &param->multiple_sequence, hdr_data, hdr_length );
    else if( data[3] == 0x0E )  /* entry point header */
        return vc1_try_to_put_header( &param->ephdr, &param->multiple_entry, hdr_data, hdr_length );
    return LSMASH_ERR_INVALID_DATA;
}

static int vc1_parse_succeeded
(
    vc1_info_t                       *info,
    lsmash_vc1_specific_parameters_t *param
)
{
    int ret;
    if( info->sequence.present && info->entry_point.present )
    {
        *param = info->dvc1_param;
        /* Avoid freeing headers. */
        info->dvc1_param.seqhdr = NULL;
        info->dvc1_param.ephdr  = NULL;
        ret = 0;
    }
    else
        ret = LSMASH_ERR_INVALID_DATA;
    vc1_cleanup_parser( info );
    return ret;
}

static inline int vc1_parse_failed
(
    vc1_info_t *info,
    int         ret
)
{
    vc1_cleanup_parser( info );
    return ret;
}

int lsmash_setup_vc1_specific_parameters_from_access_unit( lsmash_vc1_specific_parameters_t *param, uint8_t *data, uint32_t data_length )
{
    if( !param || !data || data_length == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    vc1_info_t  *info = &(vc1_info_t){ { 0 } };
    lsmash_bs_t *bs   = &(lsmash_bs_t){ 0 };
    int err = lsmash_bs_set_empty_stream( bs, data, data_length );
    if( err < 0 )
        return err;
    if( (err = vc1_setup_parser( info, 1 )) < 0 )
        return vc1_parse_failed( info, err );
    info->dvc1_param = *param;
    vc1_stream_buffer_t *sb = &info->buffer;
    while( 1 )
    {
        uint8_t  bdu_type;
        uint64_t trailing_zero_bytes;
        uint64_t ebdu_length = vc1_find_next_start_code_prefix( bs, &bdu_type, &trailing_zero_bytes );
        if( ebdu_length <= VC1_START_CODE_LENGTH && lsmash_bs_is_end( bs, ebdu_length ) )
            /* For the last EBDU. This EBDU already has been parsed. */
            return vc1_parse_succeeded( info, param );
        else if( bdu_type == 0xFF )
            return vc1_parse_failed( info, LSMASH_ERR_INVALID_DATA );
        uint64_t next_ebdu_head_pos = info->ebdu_head_pos
                                    + ebdu_length
                                    + trailing_zero_bytes;
        if( bdu_type >= 0x0A && bdu_type <= 0x0F )
        {
            /* Complete the current access unit if encountered delimiter of current access unit. */
            if( vc1_find_au_delimit_by_bdu_type( bdu_type, info->prev_bdu_type ) )
                /* The last video coded EBDU belongs to the access unit you want at this time. */
                return vc1_parse_succeeded( info, param );
            /* Increase the buffer if needed. */
            if( sb->bank->buffer_size < ebdu_length
             && (err = vc1_supplement_buffer( sb, NULL, 2 * ebdu_length )) < 0 )
                return vc1_parse_failed( info, err );
            /* Process EBDU by its BDU type. */
            uint8_t *ebdu = lsmash_bs_get_buffer_data( bs );
            switch( bdu_type )
            {
                /* FRM_SC: Frame start code
                 * FLD_SC: Field start code
                 * SLC_SC: Slice start code
                 * SEQ_SC: Sequence header start code
                 * EP_SC:  Entry-point start code
                 * PIC_L:  Picture layer
                 * SLC_L:  Slice layer
                 * SEQ_L:  Sequence layer
                 * EP_L:   Entry-point layer */
                case 0x0D : /* Frame
                             * For the Progressive or Frame Interlace mode, shall signal the beginning of a new video frame.
                             * For the Field Interlace mode, shall signal the beginning of a sequence of two independently coded video fields.
                             * [FRM_SC][PIC_L][[FLD_SC][PIC_L] (optional)][[SLC_SC][SLC_L] (optional)] ...  */
                {
                    vc1_picture_info_t *picture = &info->picture;
                    if( (err = vc1_parse_advanced_picture( info->bits, &info->sequence, picture, info->buffer.rbdu, ebdu, ebdu_length )) < 0 )
                        return vc1_parse_failed( info, err );
                    info->dvc1_param.bframe_present |= picture->frame_coding_mode == 0x3
                                                     ? picture->type >= VC1_ADVANCED_FIELD_PICTURE_TYPE_BB
                                                     : picture->type == VC1_ADVANCED_PICTURE_TYPE_B || picture->type == VC1_ADVANCED_PICTURE_TYPE_BI;
                }
                case 0x0C : /* Field
                             * Shall only be used for Field Interlaced frames
                             * and shall only be used to signal the beginning of the second field of the frame.
                             * [FRM_SC][PIC_L][FLD_SC][PIC_L][[SLC_SC][SLC_L] (optional)] ...
                             * Field start code is followed by INTERLACE_FIELD_PICTURE_FIELD2() which doesn't have info of its field picture type.*/
                    break;
                case 0x0B : /* Slice
                             * Shall not be used for start code of the first slice of a frame.
                             * Shall not be used for start code of the first slice of an interlace field coded picture.
                             * [FRM_SC][PIC_L][[FLD_SC][PIC_L] (optional)][SLC_SC][SLC_L][[SLC_SC][SLC_L] (optional)] ...
                             * Slice layer may repeat frame header. We just ignore it. */
                    info->dvc1_param.slice_present = 1;
                    break;
                case 0x0E : /* Entry-point header
                             * Entry-point indicates the direct followed frame is a start of group of frames.
                             * Entry-point doesn't indicates the frame is a random access point when multiple sequence headers are present,
                             * since it is necessary to decode sequence header which subsequent frames belong to for decoding them.
                             * Entry point shall be followed by
                             *   1. I-picture - progressive or frame interlace
                             *   2. I/I-picture, I/P-picture, or P/I-picture - field interlace
                             * [[SEQ_SC][SEQ_L] (optional)][EP_SC][EP_L][FRM_SC][PIC_L] ... */
                    if( (err = vc1_parse_entry_point_header( info, ebdu, ebdu_length, 1 )) < 0 )
                        return vc1_parse_failed( info, err );
                    break;
                case 0x0F : /* Sequence header
                             * [SEQ_SC][SEQ_L][EP_SC][EP_L][FRM_SC][PIC_L] ... */
                    if( (err = vc1_parse_sequence_header( info, ebdu, ebdu_length, 1 )) < 0 )
                        return vc1_parse_failed( info, err );
                    break;
                default :   /* End-of-sequence (0x0A) */
                    break;
            }
        }
        /* Move to the first byte of the next EBDU. */
        info->prev_bdu_type = bdu_type;
        if( lsmash_bs_read_seek( bs, next_ebdu_head_pos, SEEK_SET ) != next_ebdu_head_pos )
            return vc1_parse_failed( info, LSMASH_ERR_NAMELESS );
        /* Check if no more data to read from the stream. */
        if( !lsmash_bs_is_end( bs, VC1_START_CODE_PREFIX_LENGTH ) )
            info->ebdu_head_pos = next_ebdu_head_pos;
        else
            return vc1_parse_succeeded( info, param );
    }
}

static inline int vc1_check_next_start_code_prefix( uint8_t *buf_pos, uint8_t *buf_end )
{
    return ((buf_pos + 2) < buf_end) && !buf_pos[0] && !buf_pos[1] && (buf_pos[2] == 0x01);
}

int vc1_construct_specific_parameters( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < ISOM_BASEBOX_COMMON_SIZE + 7 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_vc1_specific_parameters_t *param = (lsmash_vc1_specific_parameters_t *)dst->data.structured;
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
    param->profile = (data[0] >> 4) & 0x0F;
    if( param->profile != 12 )
        return LSMASH_ERR_PATCH_WELCOME;    /* We don't support profile other than 12 (Advanced profile). */
    param->level             = (data[0] >> 1) & 0x07;
    param->cbr               = (data[1] >> 4) & 0x01;
    param->interlaced        = !((data[2] >> 5) & 0x01);
    param->multiple_sequence = !((data[2] >> 4) & 0x01);
    param->multiple_entry    = !((data[2] >> 3) & 0x01);
    param->slice_present     = !((data[2] >> 2) & 0x01);
    param->bframe_present    = !((data[2] >> 1) & 0x01);
    param->framerate         = LSMASH_GET_BE32( &data[3] );
    /* Try to get seqhdr_ephdr[]. */
    if( !param->seqhdr )
    {
        param->seqhdr = lsmash_malloc_zero( sizeof(lsmash_vc1_header_t) );
        if( !param->seqhdr )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    if( !param->ephdr )
    {
        param->ephdr = lsmash_malloc_zero( sizeof(lsmash_vc1_header_t) );
        if( !param->ephdr )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    lsmash_vc1_header_t *seqhdr = param->seqhdr;
    lsmash_vc1_header_t *ephdr  = param->ephdr;
    data += 7;
    uint8_t *pos = data;
    uint8_t *end = src->data.unstructured + src->size;
    /* Find the start point of Sequence header EBDU. */
    while( pos < end )
    {
        if( vc1_check_next_start_code_prefix( pos, end ) && (pos + 3 < end) && *(pos + 3) == 0x0F )
        {
            seqhdr->ebdu_size = 4;
            pos += 4;
            break;
        }
        ++pos;
    }
    /* Find the end point of Sequence header EBDU. */
    while( pos < end )
    {
        if( vc1_check_next_start_code_prefix( pos, end ) )
            break;
        ++ seqhdr->ebdu_size;
    }
    /* Find the start point of Entry-point header EBDU. */
    while( pos < end )
    {
        if( vc1_check_next_start_code_prefix( pos, end ) && (pos + 3 < end) && *(pos + 3) == 0x0E )
        {
            ephdr->ebdu_size = 4;
            pos += 4;
            break;
        }
        ++pos;
    }
    /* Find the end point of Entry-point header EBDU. */
    while( pos < end )
    {
        if( vc1_check_next_start_code_prefix( pos, end ) )
            break;
        ++ ephdr->ebdu_size;
    }
    /* Append the Sequence header EBDU and Entry-point header EBDU if present. */
    if( seqhdr->ebdu_size )
    {
        lsmash_free( seqhdr->ebdu );
        seqhdr->ebdu = lsmash_memdup( data, seqhdr->ebdu_size );
        if( !seqhdr->ebdu )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    if( ephdr->ebdu_size )
    {
        lsmash_free( ephdr->ebdu );
        ephdr->ebdu = lsmash_memdup( data, ephdr->ebdu_size );
        if( !ephdr->ebdu )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

int vc1_copy_codec_specific( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( src && src->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && src->data.structured );
    assert( dst && dst->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && dst->data.structured );
    lsmash_vc1_specific_parameters_t *src_data = (lsmash_vc1_specific_parameters_t *)src->data.structured;
    lsmash_vc1_specific_parameters_t *dst_data = (lsmash_vc1_specific_parameters_t *)dst->data.structured;
    lsmash_destroy_vc1_headers( dst_data );
    *dst_data = *src_data;
    if( !src_data->seqhdr && !src_data->ephdr )
        return 0;
    if( src_data->seqhdr )
    {
        dst_data->seqhdr = lsmash_malloc_zero( sizeof(lsmash_vc1_header_t) );
        if( !dst_data->seqhdr )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( src_data->seqhdr->ebdu_size )
        {
            dst_data->seqhdr->ebdu = lsmash_memdup( src_data->seqhdr->ebdu, src_data->seqhdr->ebdu_size );
            if( !dst_data->seqhdr->ebdu )
            {
                lsmash_destroy_vc1_headers( dst_data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
        dst_data->seqhdr->ebdu_size = src_data->seqhdr->ebdu_size;
    }
    if( src_data->ephdr )
    {
        dst_data->ephdr = lsmash_malloc_zero( sizeof(lsmash_vc1_header_t) );
        if( !dst_data->ephdr )
        {
            lsmash_destroy_vc1_headers( dst_data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        if( src_data->ephdr->ebdu_size )
        {
            dst_data->ephdr->ebdu = lsmash_memdup( src_data->ephdr->ebdu, src_data->ephdr->ebdu_size );
            if( !dst_data->ephdr->ebdu )
            {
                lsmash_destroy_vc1_headers( dst_data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
        dst_data->ephdr->ebdu_size = src_data->ephdr->ebdu_size;
    }
    return 0;
}

int vc1_print_codec_specific( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: VC1 Specific Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    if( box->size < ISOM_BASEBOX_COMMON_SIZE + 7 )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *data = box->binary;
    isom_skip_box_common( &data );
    uint8_t profile = (data[0] >> 4) & 0x0F;
    if( profile != 12 )
        return 0;   /* We don't support profile other than 12 (Advanced profile). */
    lsmash_ifprintf( fp, indent, "profile = %"PRIu8"\n", profile );
    lsmash_ifprintf( fp, indent, "level = %"PRIu8"\n", (data[0] >> 1) & 0x07 );
    lsmash_ifprintf( fp, indent, "reserved = %"PRIu8"\n", data[0] & 0x01 );
    lsmash_ifprintf( fp, indent, "level = %"PRIu8"\n", (data[1] >> 5) & 0x07 );
    lsmash_ifprintf( fp, indent, "cbr = %"PRIu8"\n", (data[1] >> 4) & 0x01 );
    lsmash_ifprintf( fp, indent, "reserved1 = 0x%02"PRIx8"\n", (data[1] & 0x0F) | ((data[2] >> 6) & 0x03) );
    lsmash_ifprintf( fp, indent, "no_interlace = %"PRIu8"\n", (data[2] >> 5) & 0x01 );
    lsmash_ifprintf( fp, indent, "no_multiple_seq = %"PRIu8"\n", (data[2] >> 4) & 0x01 );
    lsmash_ifprintf( fp, indent, "no_multiple_entry = %"PRIu8"\n", (data[2] >> 3) & 0x01 );
    lsmash_ifprintf( fp, indent, "no_slice_code = %"PRIu8"\n", (data[2] >> 2) & 0x01 );
    lsmash_ifprintf( fp, indent, "no_bframe = %"PRIu8"\n", (data[2] >> 1) & 0x01 );
    lsmash_ifprintf( fp, indent, "reserved2 = %"PRIu8"\n", data[2] & 0x01 );
    uint32_t framerate = LSMASH_GET_BE32( &data[3] );
    lsmash_ifprintf( fp, indent, "framerate = %"PRIu32"\n", framerate );
    uint32_t seqhdr_ephdr_size = box->size - (data - box->binary + 7);
    if( seqhdr_ephdr_size )
    {
        lsmash_ifprintf( fp, indent, "seqhdr_ephdr[]\n" );
        data += 7;
        for( uint32_t i = 0; i < seqhdr_ephdr_size; i += 8 )
        {
            lsmash_ifprintf( fp, indent + 1, "" );
            for( uint32_t j = 0; ; j++ )
                if( j == 7 || (i + j == seqhdr_ephdr_size - 1) )
                {
                    fprintf( fp, "0x%02"PRIx8"\n", data[i + j] );
                    break;
                }
                else
                    fprintf( fp, "0x%02"PRIx8" ", data[i + j] );
        }
    }
    return 0;
}

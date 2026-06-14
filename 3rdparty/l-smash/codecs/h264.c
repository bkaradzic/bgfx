/*****************************************************************************
 * h264.c
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
    ITU-T Recommendation H.264 (04/13)
    ISO/IEC 14496-15:2010
***************************************************************************/
#include "h264.h"
#include "nalu.h"

#define IF_EXCEED_INT32( x ) if( (x) < INT32_MIN || (x) > INT32_MAX )
#define H264_REQUIRES_AVCC_EXTENSION( x ) ((x) == 100 || (x) == 110 || (x) == 122 || (x) == 144)
#define H264_POC_DEBUG_PRINT 0

typedef enum
{
    H264_SLICE_TYPE_P    = 0,
    H264_SLICE_TYPE_B    = 1,
    H264_SLICE_TYPE_I    = 2,
    H264_SLICE_TYPE_SP   = 3,
    H264_SLICE_TYPE_SI   = 4
} h264_slice_type;

static lsmash_h264_parameter_sets_t *h264_allocate_parameter_sets( void )
{
    lsmash_h264_parameter_sets_t *parameter_sets = lsmash_malloc_zero( sizeof(lsmash_h264_parameter_sets_t) );
    if( !parameter_sets )
        return NULL;
    lsmash_list_init( parameter_sets->sps_list,    isom_remove_dcr_ps );
    lsmash_list_init( parameter_sets->pps_list,    isom_remove_dcr_ps );
    lsmash_list_init( parameter_sets->spsext_list, isom_remove_dcr_ps );
    return parameter_sets;
}

static void h264_deallocate_parameter_sets
(
    lsmash_h264_specific_parameters_t *param
)
{
    if( !param || !param->parameter_sets )
        return;
    lsmash_list_remove_entries( param->parameter_sets->sps_list );
    lsmash_list_remove_entries( param->parameter_sets->pps_list );
    lsmash_list_remove_entries( param->parameter_sets->spsext_list );
    lsmash_freep( &param->parameter_sets );
}

void lsmash_destroy_h264_parameter_sets
(
    lsmash_h264_specific_parameters_t *param
)
{
    h264_deallocate_parameter_sets( param );
}

void h264_destruct_specific_data
(
    void *data
)
{
    if( !data )
        return;
    h264_deallocate_parameter_sets( data );
    lsmash_free( data );
}

void h264_cleanup_parser
(
    h264_info_t *info
)
{
    if( !info )
        return;
    lsmash_list_remove_entries( info->sps_list );
    lsmash_list_remove_entries( info->pps_list );
    lsmash_list_remove_entries( info->slice_list );
    h264_deallocate_parameter_sets( &info->avcC_param );
    h264_deallocate_parameter_sets( &info->avcC_param_next );
    lsmash_destroy_multiple_buffers( info->buffer.bank );
    lsmash_bits_adhoc_cleanup( info->bits );
    info->bits = NULL;
}

int h264_setup_parser
(
    h264_info_t *info,
    int          parse_only
)
{
    assert( info );
    memset( info, 0, sizeof(h264_info_t) );
    info->avcC_param     .lengthSizeMinusOne = NALU_DEFAULT_NALU_LENGTH_SIZE - 1;
    info->avcC_param_next.lengthSizeMinusOne = NALU_DEFAULT_NALU_LENGTH_SIZE - 1;
    h264_stream_buffer_t *sb = &info->buffer;
    sb->bank = lsmash_create_multiple_buffers( parse_only ? 1 : 3, NALU_DEFAULT_BUFFER_SIZE );
    if( !sb->bank )
        return LSMASH_ERR_MEMORY_ALLOC;
    sb->rbsp = lsmash_withdraw_buffer( sb->bank, 1 );
    if( !parse_only )
    {
        info->au.data            = lsmash_withdraw_buffer( sb->bank, 2 );
        info->au.incomplete_data = lsmash_withdraw_buffer( sb->bank, 3 );
    }
    info->bits = lsmash_bits_adhoc_create();
    if( !info->bits )
    {
        lsmash_destroy_multiple_buffers( sb->bank );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    lsmash_list_init_simple( info->sps_list );
    lsmash_list_init_simple( info->pps_list );
    lsmash_list_init_simple( info->slice_list );
    return 0;
}

static int h264_check_nalu_header
(
    lsmash_bs_t             *bs,
    h264_nalu_header_t      *nuh,
    int                      use_long_start_code
)
{
    uint8_t temp8 = lsmash_bs_show_byte( bs, use_long_start_code ? NALU_LONG_START_CODE_LENGTH : NALU_SHORT_START_CODE_LENGTH );
    nuh->forbidden_zero_bit = (temp8 >> 7) & 0x01;
    nuh->nal_ref_idc        = (temp8 >> 5) & 0x03;
    nuh->nal_unit_type      =  temp8       & 0x1f;
    nuh->length             = 1;
    if( nuh->nal_unit_type == H264_NALU_TYPE_PREFIX
     || nuh->nal_unit_type == H264_NALU_TYPE_SLICE_EXT
     || nuh->nal_unit_type == H264_NALU_TYPE_SLICE_EXT_DVC )
    {
        /* We don't support these types of NALU. */
        //nuh->length += 3;
        return LSMASH_ERR_PATCH_WELCOME;
    }
    if( nuh->forbidden_zero_bit )
        return LSMASH_ERR_INVALID_DATA;
    /* SPS and PPS require long start code (0x00000001).
     * Also AU delimiter requires it too because this type of NALU shall be the first NALU of any AU if present. */
    if( !use_long_start_code
     && (nuh->nal_unit_type == H264_NALU_TYPE_SPS
      || nuh->nal_unit_type == H264_NALU_TYPE_PPS
      || nuh->nal_unit_type == H264_NALU_TYPE_AUD) )
        return LSMASH_ERR_INVALID_DATA;
    if( nuh->nal_ref_idc )
    {
        /* nal_ref_idc shall be equal to 0 for all NALUs having nal_unit_type equal to 6, 9, 10, 11, or 12. */
        if( nuh->nal_unit_type == H264_NALU_TYPE_SEI
         || nuh->nal_unit_type == H264_NALU_TYPE_AUD
         || nuh->nal_unit_type == H264_NALU_TYPE_EOS
         || nuh->nal_unit_type == H264_NALU_TYPE_EOB
         || nuh->nal_unit_type == H264_NALU_TYPE_FD )
            return LSMASH_ERR_INVALID_DATA;
    }
    else
        /* nal_ref_idc shall not be equal to 0 for NALUs with nal_unit_type equal to 5. */
        if( nuh->nal_unit_type == H264_NALU_TYPE_SLICE_IDR )
            return LSMASH_ERR_INVALID_DATA;
    return 0;
}

uint64_t h264_find_next_start_code
(
    lsmash_bs_t        *bs,
    h264_nalu_header_t *nuh,
    uint64_t           *start_code_length,
    uint64_t           *trailing_zero_bytes
)
{
    uint64_t length = 0;    /* the length of the latest NALU */
    uint64_t count  = 0;    /* the number of the trailing zero bytes after the latest NALU */
    /* Check the type of the current start code. */
    int long_start_code
        = (!lsmash_bs_is_end( bs, NALU_LONG_START_CODE_LENGTH )  && 0x00000001 == lsmash_bs_show_be32( bs, 0 )) ? 1
        : (!lsmash_bs_is_end( bs, NALU_SHORT_START_CODE_LENGTH ) && 0x000001   == lsmash_bs_show_be24( bs, 0 )) ? 0
        :                                                                                                        -1;
    if( long_start_code >= 0 && h264_check_nalu_header( bs, nuh, long_start_code ) == 0 )
    {
        *start_code_length = long_start_code ? NALU_LONG_START_CODE_LENGTH : NALU_SHORT_START_CODE_LENGTH;
        uint64_t distance = *start_code_length + nuh->length;
        /* Find the start code of the next NALU and get the distance from the start code of the latest NALU. */
        if( !lsmash_bs_is_end( bs, distance + NALU_SHORT_START_CODE_LENGTH ) )
        {
            uint32_t sync_bytes = lsmash_bs_show_be24( bs, distance );
            while( 0x000001 != sync_bytes )
            {
                if( lsmash_bs_is_end( bs, ++distance + NALU_SHORT_START_CODE_LENGTH ) )
                {
                    distance = lsmash_bs_get_remaining_buffer_size( bs );
                    break;
                }
                sync_bytes <<= 8;
                sync_bytes  |= lsmash_bs_show_byte( bs, distance + NALU_SHORT_START_CODE_LENGTH - 1 );
                sync_bytes  &= 0xFFFFFF;
            }
        }
        else
            distance = lsmash_bs_get_remaining_buffer_size( bs );
        /* Any NALU has no consecutive zero bytes at the end. */
        while( 0x00 == lsmash_bs_show_byte( bs, distance - 1 ) )
        {
            --distance;
            ++count;
        }
        /* Remove the length of the start code. */
        length = distance - *start_code_length;
        /* If there are one or more trailing zero bytes, we treat the last one byte as a part of the next start code.
         * This makes the next start code a long start code. */
        if( count )
            --count;
    }
    else
    {
        /* No start code. */
        nuh->forbidden_zero_bit = 1;    /* shall be 0, so invalid */
        nuh->nal_ref_idc        = 0;    /* arbitrary */
        nuh->nal_unit_type      = H264_NALU_TYPE_UNSPECIFIED0;
        nuh->length             = 0;
        *start_code_length = 0;
        length = NALU_NO_START_CODE_FOUND;
    }
    *trailing_zero_bytes = count;
    return length;
}

static h264_sps_t *h264_get_sps
(
    lsmash_entry_list_t *sps_list,
    uint8_t              sps_id
)
{
    if( !sps_list || sps_id > 31 )
        return NULL;
    for( lsmash_entry_t *entry = sps_list->head; entry; entry = entry->next )
    {
        h264_sps_t *sps = (h264_sps_t *)entry->data;
        if( !sps )
            return NULL;
        if( sps->seq_parameter_set_id == sps_id )
            return sps;
    }
    h264_sps_t *sps = lsmash_malloc_zero( sizeof(h264_sps_t) );
    if( !sps )
        return NULL;
    sps->seq_parameter_set_id = sps_id;
    if( lsmash_list_add_entry( sps_list, sps ) < 0 )
    {
        lsmash_free( sps );
        return NULL;
    }
    return sps;
}

static h264_pps_t *h264_get_pps
(
    lsmash_entry_list_t *pps_list,
    uint8_t              pps_id
)
{
    if( !pps_list )
        return NULL;
    for( lsmash_entry_t *entry = pps_list->head; entry; entry = entry->next )
    {
        h264_pps_t *pps = (h264_pps_t *)entry->data;
        if( !pps )
            return NULL;
        if( pps->pic_parameter_set_id == pps_id )
            return pps;
    }
    h264_pps_t *pps = lsmash_malloc_zero( sizeof(h264_pps_t) );
    if( !pps )
        return NULL;
    pps->pic_parameter_set_id = pps_id;
    if( lsmash_list_add_entry( pps_list, pps ) < 0 )
    {
        lsmash_free( pps );
        return NULL;
    }
    return pps;
}

static h264_slice_info_t *h264_get_slice_info
(
    lsmash_entry_list_t *slice_list,
    uint8_t              slice_id
)
{
    if( !slice_list )
        return NULL;
    for( lsmash_entry_t *entry = slice_list->head; entry; entry = entry->next )
    {
        h264_slice_info_t *slice = (h264_slice_info_t *)entry->data;
        if( !slice )
            return NULL;
        if( slice->slice_id == slice_id )
            return slice;
    }
    h264_slice_info_t *slice = lsmash_malloc_zero( sizeof(h264_slice_info_t) );
    if( !slice )
        return NULL;
    slice->slice_id = slice_id;
    if( lsmash_list_add_entry( slice_list, slice ) < 0 )
    {
        lsmash_free( slice );
        return NULL;
    }
    return slice;
}

int h264_calculate_poc
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_picture_info_t *prev_picture
)
{
#if H264_POC_DEBUG_PRINT
    fprintf( stderr, "PictureOrderCount\n" );
#endif
    h264_pps_t *pps = h264_get_pps( info->pps_list, picture->pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    h264_sps_t *sps = h264_get_sps( info->sps_list, pps->seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    int64_t TopFieldOrderCnt    = 0;
    int64_t BottomFieldOrderCnt = 0;
    if( sps->pic_order_cnt_type == 0 )
    {
        int32_t prevPicOrderCntMsb;
        int32_t prevPicOrderCntLsb;
        if( picture->idr )
        {
            prevPicOrderCntMsb = 0;
            prevPicOrderCntLsb = 0;
        }
        else if( prev_picture->ref_pic_has_mmco5 )
        {
            prevPicOrderCntMsb = 0;
            prevPicOrderCntLsb = prev_picture->ref_pic_bottom_field_flag ? 0 : prev_picture->ref_pic_TopFieldOrderCnt;
        }
        else
        {
            prevPicOrderCntMsb = prev_picture->ref_pic_PicOrderCntMsb;
            prevPicOrderCntLsb = prev_picture->ref_pic_PicOrderCntLsb;
        }
        int64_t PicOrderCntMsb;
        int32_t pic_order_cnt_lsb = picture->pic_order_cnt_lsb;
        uint64_t MaxPicOrderCntLsb = sps->MaxPicOrderCntLsb;
        if( (pic_order_cnt_lsb < prevPicOrderCntLsb)
         && ((prevPicOrderCntLsb - pic_order_cnt_lsb) >= (MaxPicOrderCntLsb / 2)) )
            PicOrderCntMsb = prevPicOrderCntMsb + MaxPicOrderCntLsb;
        else if( (pic_order_cnt_lsb > prevPicOrderCntLsb)
         && ((pic_order_cnt_lsb - prevPicOrderCntLsb) > (MaxPicOrderCntLsb / 2)) )
            PicOrderCntMsb = prevPicOrderCntMsb - MaxPicOrderCntLsb;
        else
            PicOrderCntMsb = prevPicOrderCntMsb;
        IF_EXCEED_INT32( PicOrderCntMsb )
            return LSMASH_ERR_INVALID_DATA;
        BottomFieldOrderCnt = TopFieldOrderCnt = PicOrderCntMsb + pic_order_cnt_lsb;
        if( !picture->field_pic_flag )
            BottomFieldOrderCnt += picture->delta_pic_order_cnt_bottom;
        IF_EXCEED_INT32( TopFieldOrderCnt )
            return LSMASH_ERR_INVALID_DATA;
        IF_EXCEED_INT32( BottomFieldOrderCnt )
            return LSMASH_ERR_INVALID_DATA;
        if( !picture->disposable )
        {
            picture->ref_pic_has_mmco5         = picture->has_mmco5;
            picture->ref_pic_bottom_field_flag = picture->bottom_field_flag;
            picture->ref_pic_TopFieldOrderCnt  = TopFieldOrderCnt;
            picture->ref_pic_PicOrderCntMsb    = PicOrderCntMsb;
            picture->ref_pic_PicOrderCntLsb    = pic_order_cnt_lsb;
        }
#if H264_POC_DEBUG_PRINT
        fprintf( stderr, "    prevPicOrderCntMsb: %"PRId32"\n", prevPicOrderCntMsb );
        fprintf( stderr, "    prevPicOrderCntLsb: %"PRId32"\n", prevPicOrderCntLsb );
        fprintf( stderr, "    PicOrderCntMsb: %"PRId64"\n", PicOrderCntMsb );
        fprintf( stderr, "    pic_order_cnt_lsb: %"PRId32"\n", pic_order_cnt_lsb );
        fprintf( stderr, "    MaxPicOrderCntLsb: %"PRIu64"\n", MaxPicOrderCntLsb );
#endif
    }
    else if( sps->pic_order_cnt_type == 1 )
    {
        uint32_t frame_num          = picture->frame_num;
        uint32_t prevFrameNum       = prev_picture->has_mmco5 ? 0 : prev_picture->frame_num;
        uint32_t prevFrameNumOffset = prev_picture->has_mmco5 ? 0 : prev_picture->FrameNumOffset;
        uint64_t FrameNumOffset     = picture->idr ? 0 : prevFrameNumOffset + (prevFrameNum > frame_num ? sps->MaxFrameNum : 0);
        if( FrameNumOffset > INT32_MAX )
            return LSMASH_ERR_INVALID_DATA;
        int64_t expectedPicOrderCnt;
        if( sps->num_ref_frames_in_pic_order_cnt_cycle )
        {
            uint64_t absFrameNum = FrameNumOffset + frame_num;
            absFrameNum -= picture->disposable && absFrameNum > 0;
            if( absFrameNum )
            {
                uint64_t picOrderCntCycleCnt       = (absFrameNum - 1) / sps->num_ref_frames_in_pic_order_cnt_cycle;
                uint8_t frameNumInPicOrderCntCycle = (absFrameNum - 1) % sps->num_ref_frames_in_pic_order_cnt_cycle;
                expectedPicOrderCnt = picOrderCntCycleCnt * sps->ExpectedDeltaPerPicOrderCntCycle;
                for( uint8_t i = 0; i <= frameNumInPicOrderCntCycle; i++ )
                    expectedPicOrderCnt += sps->offset_for_ref_frame[i];
            }
            else
                expectedPicOrderCnt = 0;
        }
        else
            expectedPicOrderCnt = 0;
        if( picture->disposable )
            expectedPicOrderCnt += sps->offset_for_non_ref_pic;
        TopFieldOrderCnt    = expectedPicOrderCnt + picture->delta_pic_order_cnt[0];
        BottomFieldOrderCnt = TopFieldOrderCnt + sps->offset_for_top_to_bottom_field;
        if( !picture->field_pic_flag )
            BottomFieldOrderCnt += picture->delta_pic_order_cnt[1];
        IF_EXCEED_INT32( TopFieldOrderCnt )
            return LSMASH_ERR_INVALID_DATA;
        IF_EXCEED_INT32( BottomFieldOrderCnt )
            return LSMASH_ERR_INVALID_DATA;
        picture->FrameNumOffset = FrameNumOffset;
    }
    else if( sps->pic_order_cnt_type == 2 )
    {
        uint32_t frame_num          = picture->frame_num;
        uint32_t prevFrameNum       = prev_picture->has_mmco5 ? 0 : prev_picture->frame_num;
        int32_t  prevFrameNumOffset = prev_picture->has_mmco5 ? 0 : prev_picture->FrameNumOffset;
        int64_t  FrameNumOffset;
        int64_t  tempPicOrderCnt;
        if( picture->idr )
        {
            FrameNumOffset  = 0;
            tempPicOrderCnt = 0;
        }
        else
        {
            FrameNumOffset  = prevFrameNumOffset + (prevFrameNum > frame_num ? sps->MaxFrameNum : 0);
            tempPicOrderCnt = 2 * (FrameNumOffset + frame_num) - picture->disposable;
            IF_EXCEED_INT32( FrameNumOffset )
                return LSMASH_ERR_INVALID_DATA;
            IF_EXCEED_INT32( tempPicOrderCnt )
                return LSMASH_ERR_INVALID_DATA;
        }
        TopFieldOrderCnt    = tempPicOrderCnt;
        BottomFieldOrderCnt = tempPicOrderCnt;
        picture->FrameNumOffset = FrameNumOffset;
    }
    if( !picture->field_pic_flag )
        picture->PicOrderCnt = LSMASH_MIN( TopFieldOrderCnt, BottomFieldOrderCnt );
    else
        picture->PicOrderCnt = picture->bottom_field_flag ? BottomFieldOrderCnt : TopFieldOrderCnt;
#if H264_POC_DEBUG_PRINT
    if( picture->field_pic_flag )
    {
        if( !picture->bottom_field_flag )
            fprintf( stderr, "    TopFieldOrderCnt: %"PRId64"\n", TopFieldOrderCnt );
        else
            fprintf( stderr, "    BottomFieldOrderCnt: %"PRId64"\n", BottomFieldOrderCnt );
    }
    fprintf( stderr, "    POC: %"PRId32"\n", picture->PicOrderCnt );
#endif
    return 0;
}

static int h264_parse_scaling_list
(
    lsmash_bits_t *bits,
    int            sizeOfScalingList
)
{
    /* scaling_list( scalingList, sizeOfScalingList, useDefaultScalingMatrixFlag ) */
    int nextScale = 8;
    for( int i = 0; i < sizeOfScalingList; i++ )
    {
        int64_t delta_scale = nalu_get_exp_golomb_se( bits );
        if( delta_scale < -128 || delta_scale > 127 )
            return LSMASH_ERR_INVALID_DATA;
        nextScale = (nextScale + delta_scale + 256) % 256;
        if( nextScale == 0 )
            break;
    }
    return 0;
}

static int h264_parse_hrd_parameters
(
    lsmash_bits_t *bits,
    h264_hrd_t    *hrd
)
{
    /* hrd_parameters() */
    uint64_t cpb_cnt_minus1 = nalu_get_exp_golomb_ue( bits );
    if( cpb_cnt_minus1 > 31 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bits_get( bits, 4 );     /* bit_rate_scale */
    lsmash_bits_get( bits, 4 );     /* cpb_size_scale */
    for( uint64_t SchedSelIdx = 0; SchedSelIdx <= cpb_cnt_minus1; SchedSelIdx++ )
    {
        nalu_get_exp_golomb_ue( bits );     /* bit_rate_value_minus1[ SchedSelIdx ] */
        nalu_get_exp_golomb_ue( bits );     /* cpb_size_value_minus1[ SchedSelIdx ] */
        lsmash_bits_get( bits, 1 );         /* cbr_flag             [ SchedSelIdx ] */
    }
    lsmash_bits_get( bits, 5 );     /* initial_cpb_removal_delay_length_minus1 */
    hrd->cpb_removal_delay_length = lsmash_bits_get( bits, 5 ) + 1;
    hrd->dpb_output_delay_length  = lsmash_bits_get( bits, 5 ) + 1;
    lsmash_bits_get( bits, 5 );     /* time_offset_length */
    return 0;
}

static int h264_parse_sps_minimally
(
    lsmash_bits_t *bits,
    h264_sps_t    *sps,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    memset( sps, 0, sizeof(h264_sps_t) );
    sps->profile_idc          = lsmash_bits_get( bits, 8 );
    sps->constraint_set_flags = lsmash_bits_get( bits, 8 );
    sps->level_idc            = lsmash_bits_get( bits, 8 );
    uint64_t seq_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    if( seq_parameter_set_id > 31 )
        return LSMASH_ERR_INVALID_DATA;
    sps->seq_parameter_set_id = seq_parameter_set_id;
    if( sps->profile_idc == 100 || sps->profile_idc == 110 || sps->profile_idc == 122
     || sps->profile_idc == 244 || sps->profile_idc == 44  || sps->profile_idc == 83
     || sps->profile_idc == 86  || sps->profile_idc == 118 || sps->profile_idc == 128
     || sps->profile_idc == 138 )
    {
        sps->chroma_format_idc = nalu_get_exp_golomb_ue( bits );
        if( sps->chroma_format_idc == 3 )
            sps->separate_colour_plane_flag = lsmash_bits_get( bits, 1 );
        uint64_t bit_depth_luma_minus8 = nalu_get_exp_golomb_ue( bits );
        if( bit_depth_luma_minus8 > 6 )
            return LSMASH_ERR_INVALID_DATA;
        uint64_t bit_depth_chroma_minus8 = nalu_get_exp_golomb_ue( bits );
        if( bit_depth_chroma_minus8 > 6 )
            return LSMASH_ERR_INVALID_DATA;
        sps->bit_depth_luma_minus8   = bit_depth_luma_minus8;
        sps->bit_depth_chroma_minus8 = bit_depth_chroma_minus8;
        lsmash_bits_get( bits, 1 );         /* qpprime_y_zero_transform_bypass_flag */
        if( lsmash_bits_get( bits, 1 ) )    /* seq_scaling_matrix_present_flag */
        {
            int num_loops = sps->chroma_format_idc != 3 ? 8 : 12;
            for( int i = 0; i < num_loops; i++ )
                if( lsmash_bits_get( bits, 1 )          /* seq_scaling_list_present_flag[i] */
                 && (err = h264_parse_scaling_list( bits, i < 6 ? 16 : 64 )) < 0 )
                        return err;
        }
    }
    else
    {
        sps->chroma_format_idc          = 1;
        sps->separate_colour_plane_flag = 0;
        sps->bit_depth_luma_minus8      = 0;
        sps->bit_depth_chroma_minus8    = 0;
    }
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int h264_parse_sps
(
    h264_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    /* seq_parameter_set_data() */
    h264_sps_t temp_sps;
    int err = h264_parse_sps_minimally( bits, &temp_sps, rbsp_buffer, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    h264_sps_t *sps = h264_get_sps( info->sps_list, temp_sps.seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    memset( sps, 0, sizeof(h264_sps_t) );
    sps->profile_idc                = temp_sps.profile_idc;
    sps->constraint_set_flags       = temp_sps.constraint_set_flags;
    sps->level_idc                  = temp_sps.level_idc;
    sps->seq_parameter_set_id       = temp_sps.seq_parameter_set_id;
    sps->chroma_format_idc          = temp_sps.chroma_format_idc;
    sps->separate_colour_plane_flag = temp_sps.separate_colour_plane_flag;
    sps->bit_depth_luma_minus8      = temp_sps.bit_depth_luma_minus8;
    sps->bit_depth_chroma_minus8    = temp_sps.bit_depth_chroma_minus8;
    sps->ChromaArrayType = sps->separate_colour_plane_flag ? 0 : sps->chroma_format_idc;
    uint64_t log2_max_frame_num_minus4 = nalu_get_exp_golomb_ue( bits );
    if( log2_max_frame_num_minus4 > 12 )
        return LSMASH_ERR_INVALID_DATA;
    sps->log2_max_frame_num = log2_max_frame_num_minus4 + 4;
    sps->MaxFrameNum = 1 << sps->log2_max_frame_num;
    uint64_t pic_order_cnt_type = nalu_get_exp_golomb_ue( bits );
    if( pic_order_cnt_type > 2 )
        return LSMASH_ERR_INVALID_DATA;
    sps->pic_order_cnt_type = pic_order_cnt_type;
    if( sps->pic_order_cnt_type == 0 )
    {
        uint64_t log2_max_pic_order_cnt_lsb_minus4 = nalu_get_exp_golomb_ue( bits );
        if( log2_max_pic_order_cnt_lsb_minus4 > 12 )
            return LSMASH_ERR_INVALID_DATA;
        sps->log2_max_pic_order_cnt_lsb = log2_max_pic_order_cnt_lsb_minus4 + 4;
        sps->MaxPicOrderCntLsb = 1 << sps->log2_max_pic_order_cnt_lsb;
    }
    else if( sps->pic_order_cnt_type == 1 )
    {
        sps->delta_pic_order_always_zero_flag = lsmash_bits_get( bits, 1 );
        static const int64_t max_value =  (signed)(((uint64_t)1 << 31) - 1);
        static const int64_t min_value = -(signed)(((uint64_t)1 << 31) - 1);
        int64_t offset_for_non_ref_pic = nalu_get_exp_golomb_se( bits );
        if( offset_for_non_ref_pic < min_value || offset_for_non_ref_pic > max_value )
            return LSMASH_ERR_INVALID_DATA;
        sps->offset_for_non_ref_pic = offset_for_non_ref_pic;
        int64_t offset_for_top_to_bottom_field = nalu_get_exp_golomb_se( bits );
        if( offset_for_top_to_bottom_field < min_value || offset_for_top_to_bottom_field > max_value )
            return LSMASH_ERR_INVALID_DATA;
        sps->offset_for_top_to_bottom_field = offset_for_top_to_bottom_field;
        uint64_t num_ref_frames_in_pic_order_cnt_cycle = nalu_get_exp_golomb_ue( bits );
        if( num_ref_frames_in_pic_order_cnt_cycle > 255 )
            return LSMASH_ERR_INVALID_DATA;
        sps->num_ref_frames_in_pic_order_cnt_cycle = num_ref_frames_in_pic_order_cnt_cycle;
        sps->ExpectedDeltaPerPicOrderCntCycle = 0;
        for( int i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++ )
        {
            int64_t offset_for_ref_frame = nalu_get_exp_golomb_se( bits );
            if( offset_for_ref_frame < min_value || offset_for_ref_frame > max_value )
                return LSMASH_ERR_INVALID_DATA;
            sps->offset_for_ref_frame[i] = offset_for_ref_frame;
            sps->ExpectedDeltaPerPicOrderCntCycle += offset_for_ref_frame;
        }
    }
    sps->max_num_ref_frames = nalu_get_exp_golomb_ue( bits );
    lsmash_bits_get( bits, 1 );         /* gaps_in_frame_num_value_allowed_flag */
    uint64_t pic_width_in_mbs_minus1        = nalu_get_exp_golomb_ue( bits );
    uint64_t pic_height_in_map_units_minus1 = nalu_get_exp_golomb_ue( bits );
    sps->frame_mbs_only_flag = lsmash_bits_get( bits, 1 );
    if( !sps->frame_mbs_only_flag )
        lsmash_bits_get( bits, 1 );     /* mb_adaptive_frame_field_flag */
    lsmash_bits_get( bits, 1 );         /* direct_8x8_inference_flag */
    uint64_t PicWidthInMbs       = pic_width_in_mbs_minus1        + 1;
    uint64_t PicHeightInMapUnits = pic_height_in_map_units_minus1 + 1;
    sps->PicSizeInMapUnits = PicWidthInMbs * PicHeightInMapUnits;
    sps->cropped_width  = PicWidthInMbs * 16;
    sps->cropped_height = (2 - sps->frame_mbs_only_flag) * PicHeightInMapUnits * 16;
    if( lsmash_bits_get( bits, 1 ) )    /* frame_cropping_flag */
    {
        uint8_t CropUnitX;
        uint8_t CropUnitY;
        if( sps->ChromaArrayType == 0 )
        {
            CropUnitX = 1;
            CropUnitY = 2 - sps->frame_mbs_only_flag;
        }
        else
        {
            static const int SubWidthC [] = { 0, 2, 2, 1 };
            static const int SubHeightC[] = { 0, 2, 1, 1 };
            CropUnitX = SubWidthC [ sps->chroma_format_idc ];
            CropUnitY = SubHeightC[ sps->chroma_format_idc ] * (2 - sps->frame_mbs_only_flag);
        }
        uint64_t frame_crop_left_offset   = nalu_get_exp_golomb_ue( bits );
        uint64_t frame_crop_right_offset  = nalu_get_exp_golomb_ue( bits );
        uint64_t frame_crop_top_offset    = nalu_get_exp_golomb_ue( bits );
        uint64_t frame_crop_bottom_offset = nalu_get_exp_golomb_ue( bits );
        sps->cropped_width  -= (frame_crop_left_offset + frame_crop_right_offset)  * CropUnitX;
        sps->cropped_height -= (frame_crop_top_offset  + frame_crop_bottom_offset) * CropUnitY;
    }
    if( lsmash_bits_get( bits, 1 ) )    /* vui_parameters_present_flag */
    {
        /* vui_parameters() */
        if( lsmash_bits_get( bits, 1 ) )        /* aspect_ratio_info_present_flag */
        {
            uint8_t aspect_ratio_idc = lsmash_bits_get( bits, 8 );
            if( aspect_ratio_idc == 255 )
            {
                /* Extended_SAR */
                sps->vui.sar_width  = lsmash_bits_get( bits, 16 );
                sps->vui.sar_height = lsmash_bits_get( bits, 16 );
            }
            else
            {
                static const struct
                {
                    uint16_t sar_width;
                    uint16_t sar_height;
                } pre_defined_sar[]
                    = {
                        {  0,  0 }, {  1,  1 }, { 12, 11 }, {  10, 11 }, { 16, 11 },
                        { 40, 33 }, { 24, 11 }, { 20, 11 }, {  32, 11 }, { 80, 33 },
                        { 18, 11 }, { 15, 11 }, { 64, 33 }, { 160, 99 }, {  4,  3 },
                        {  3,  2 }, {  2,  1 }
                      };
                if( aspect_ratio_idc < (sizeof(pre_defined_sar) / sizeof(pre_defined_sar[0])) )
                {
                    sps->vui.sar_width  = pre_defined_sar[ aspect_ratio_idc ].sar_width;
                    sps->vui.sar_height = pre_defined_sar[ aspect_ratio_idc ].sar_height;
                }
                else
                {
                    /* Behavior when unknown aspect_ratio_idc is detected is not specified in the specification. */
                    sps->vui.sar_width  = 0;
                    sps->vui.sar_height = 0;
                }
            }
        }
        if( lsmash_bits_get( bits, 1 ) )        /* overscan_info_present_flag */
            lsmash_bits_get( bits, 1 );         /* overscan_appropriate_flag */
        if( lsmash_bits_get( bits, 1 ) )        /* video_signal_type_present_flag */
        {
            lsmash_bits_get( bits, 3 );         /* video_format */
            sps->vui.video_full_range_flag = lsmash_bits_get( bits, 1 );
            if( lsmash_bits_get( bits, 1 ) )    /* colour_description_present_flag */
            {
                sps->vui.colour_primaries         = lsmash_bits_get( bits, 8 );
                sps->vui.transfer_characteristics = lsmash_bits_get( bits, 8 );
                sps->vui.matrix_coefficients      = lsmash_bits_get( bits, 8 );
            }
        }
        if( lsmash_bits_get( bits, 1 ) )        /* chroma_loc_info_present_flag */
        {
            nalu_get_exp_golomb_ue( bits );     /* chroma_sample_loc_type_top_field */
            nalu_get_exp_golomb_ue( bits );     /* chroma_sample_loc_type_bottom_field */
        }
        if( lsmash_bits_get( bits, 1 ) )        /* timing_info_present_flag */
        {
            sps->vui.num_units_in_tick     = lsmash_bits_get( bits, 32 );
            sps->vui.time_scale            = lsmash_bits_get( bits, 32 );
            sps->vui.fixed_frame_rate_flag = lsmash_bits_get( bits, 1 );
        }
        else
        {
            sps->vui.num_units_in_tick     = 1;     /* arbitrary */
            sps->vui.time_scale            = 50;    /* arbitrary */
            sps->vui.fixed_frame_rate_flag = 0;
        }
        int nal_hrd_parameters_present_flag = lsmash_bits_get( bits, 1 );
        if( nal_hrd_parameters_present_flag
         && (err = h264_parse_hrd_parameters( bits, &sps->vui.hrd )) < 0 )
            return err;
        int vcl_hrd_parameters_present_flag = lsmash_bits_get( bits, 1 );
        if( vcl_hrd_parameters_present_flag
         && (err = h264_parse_hrd_parameters( bits, &sps->vui.hrd )) < 0 )
            return err;
        if( nal_hrd_parameters_present_flag || vcl_hrd_parameters_present_flag )
        {
            sps->vui.hrd.present                 = 1;
            sps->vui.hrd.CpbDpbDelaysPresentFlag = 1;
            lsmash_bits_get( bits, 1 );         /* low_delay_hrd_flag */
        }
        sps->vui.pic_struct_present_flag = lsmash_bits_get( bits, 1 );
        if( lsmash_bits_get( bits, 1 ) )        /* bitstream_restriction_flag */
        {
            lsmash_bits_get( bits, 1 );         /* motion_vectors_over_pic_boundaries_flag */
            nalu_get_exp_golomb_ue( bits );     /* max_bytes_per_pic_denom */
            nalu_get_exp_golomb_ue( bits );     /* max_bits_per_mb_denom */
            nalu_get_exp_golomb_ue( bits );     /* log2_max_mv_length_horizontal */
            nalu_get_exp_golomb_ue( bits );     /* log2_max_mv_length_vertical */
            nalu_get_exp_golomb_ue( bits );     /* max_num_reorder_frames */
            nalu_get_exp_golomb_ue( bits );     /* max_dec_frame_buffering */
        }
    }
    else
    {
        sps->vui.video_full_range_flag = 0;
        sps->vui.num_units_in_tick     = 1;     /* arbitrary */
        sps->vui.time_scale            = 50;    /* arbitrary */
        sps->vui.fixed_frame_rate_flag = 0;
    }
    /* rbsp_trailing_bits() */
    if( !lsmash_bits_get( bits, 1 ) )   /* rbsp_stop_one_bit */
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    sps->present = 1;
    info->sps = *sps;
    return 0;
}

static int h264_parse_pps_minimally
(
    lsmash_bits_t *bits,
    h264_pps_t    *pps,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    memset( pps, 0, sizeof(h264_pps_t) );
    uint64_t pic_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    if( pic_parameter_set_id > 255 )
        return LSMASH_ERR_INVALID_DATA;
    pps->pic_parameter_set_id = pic_parameter_set_id;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int h264_parse_pps
(
    h264_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    /* pic_parameter_set_rbsp */
    h264_pps_t temp_pps;
    int err = h264_parse_pps_minimally( bits, &temp_pps, rbsp_buffer, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    h264_pps_t *pps = h264_get_pps( info->pps_list, temp_pps.pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    memset( pps, 0, sizeof(h264_pps_t) );
    pps->pic_parameter_set_id = temp_pps.pic_parameter_set_id;
    uint64_t seq_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    if( seq_parameter_set_id > 31 )
        return LSMASH_ERR_INVALID_DATA;
    h264_sps_t *sps = h264_get_sps( info->sps_list, seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    pps->seq_parameter_set_id = seq_parameter_set_id;
    pps->entropy_coding_mode_flag = lsmash_bits_get( bits, 1 );
    pps->bottom_field_pic_order_in_frame_present_flag = lsmash_bits_get( bits, 1 );
    uint64_t num_slice_groups_minus1 = nalu_get_exp_golomb_ue( bits );
    if( num_slice_groups_minus1 > 7 )
        return LSMASH_ERR_INVALID_DATA;
    pps->num_slice_groups_minus1 = num_slice_groups_minus1;
    if( num_slice_groups_minus1 )        /* num_slice_groups_minus1 */
    {
        uint64_t slice_group_map_type = nalu_get_exp_golomb_ue( bits );
        if( slice_group_map_type > 6 )
            return LSMASH_ERR_INVALID_DATA;
        pps->slice_group_map_type = slice_group_map_type;
        if( slice_group_map_type == 0 )
            for( uint64_t iGroup = 0; iGroup <= num_slice_groups_minus1; iGroup++ )
                nalu_get_exp_golomb_ue( bits );     /* run_length_minus1[ iGroup ] */
        else if( slice_group_map_type == 2 )
            for( uint64_t iGroup = 0; iGroup < num_slice_groups_minus1; iGroup++ )
            {
                nalu_get_exp_golomb_ue( bits );     /* top_left    [ iGroup ] */
                nalu_get_exp_golomb_ue( bits );     /* bottom_right[ iGroup ] */
            }
        else if( slice_group_map_type == 3
              || slice_group_map_type == 4
              || slice_group_map_type == 5 )
        {
            lsmash_bits_get( bits, 1 );         /* slice_group_change_direction_flag */
            uint64_t slice_group_change_rate_minus1 = nalu_get_exp_golomb_ue( bits );
            if( slice_group_change_rate_minus1 > (sps->PicSizeInMapUnits - 1) )
                return LSMASH_ERR_INVALID_DATA;
            pps->SliceGroupChangeRate = slice_group_change_rate_minus1 + 1;
        }
        else if( slice_group_map_type == 6 )
        {
            uint64_t pic_size_in_map_units_minus1 = nalu_get_exp_golomb_ue( bits );
            int length = lsmash_ceil_log2( num_slice_groups_minus1 + 1 );
            for( uint64_t i = 0; i <= pic_size_in_map_units_minus1; i++ )
                /* slice_group_id */
                if( lsmash_bits_get( bits, length ) > num_slice_groups_minus1 )
                    return LSMASH_ERR_INVALID_DATA;
        }
    }
    pps->num_ref_idx_l0_default_active_minus1 = nalu_get_exp_golomb_ue( bits );
    pps->num_ref_idx_l1_default_active_minus1 = nalu_get_exp_golomb_ue( bits );
    pps->weighted_pred_flag                   = lsmash_bits_get( bits, 1 );
    pps->weighted_bipred_idc                  = lsmash_bits_get( bits, 2 );
    nalu_get_exp_golomb_se( bits );     /* pic_init_qp_minus26 */
    nalu_get_exp_golomb_se( bits );     /* pic_init_qs_minus26 */
    nalu_get_exp_golomb_se( bits );     /* chroma_qp_index_offset */
    pps->deblocking_filter_control_present_flag = lsmash_bits_get( bits, 1 );
    lsmash_bits_get( bits, 1 );         /* constrained_intra_pred_flag */
    pps->redundant_pic_cnt_present_flag = lsmash_bits_get( bits, 1 );
    if( nalu_check_more_rbsp_data( bits ) )
    {
        int transform_8x8_mode_flag = lsmash_bits_get( bits, 1 );
        if( lsmash_bits_get( bits, 1 ) )        /* pic_scaling_matrix_present_flag */
        {
            int num_loops = 6 + (sps->chroma_format_idc != 3 ? 2 : 6) * transform_8x8_mode_flag;
            for( int i = 0; i < num_loops; i++ )
                if( lsmash_bits_get( bits, 1 )          /* pic_scaling_list_present_flag[i] */
                 && (err = h264_parse_scaling_list( bits, i < 6 ? 16 : 64 )) < 0 )
                        return err;
        }
        nalu_get_exp_golomb_se( bits );         /* second_chroma_qp_index_offset */
    }
    /* rbsp_trailing_bits() */
    if( !lsmash_bits_get( bits, 1 ) )   /* rbsp_stop_one_bit */
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    pps->present = 1;
    info->sps = *sps;
    info->pps = *pps;
    return 0;
}

int h264_parse_sei
(
    lsmash_bits_t *bits,
    h264_sps_t    *sps,
    h264_sei_t    *sei,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    uint8_t *rbsp_start = rbsp_buffer;
    uint64_t rbsp_pos = 0;
    do
    {
        /* sei_message() */
        uint32_t payloadType = 0;
        for( uint8_t temp = lsmash_bits_get( bits, 8 ); ; temp = lsmash_bits_get( bits, 8 ) )
        {
            /* 0xff     : ff_byte
             * otherwise: last_payload_type_byte */
            payloadType += temp;
            ++rbsp_pos;
            if( temp != 0xff )
                break;
        }
        uint32_t payloadSize = 0;
        for( uint8_t temp = lsmash_bits_get( bits, 8 ); ; temp = lsmash_bits_get( bits, 8 ) )
        {
            /* 0xff     : ff_byte
             * otherwise: last_payload_size_byte */
            payloadSize += temp;
            ++rbsp_pos;
            if( temp != 0xff )
                break;
        }
        if( payloadType == 1 )
        {
            /* pic_timing */
            h264_hrd_t *hrd = sps ? &sps->vui.hrd : NULL;
            if( !hrd )
                goto skip_sei_message;  /* Any active SPS is not found. */
            sei->pic_timing.present = 1;
            if( hrd->CpbDpbDelaysPresentFlag )
            {
                lsmash_bits_get( bits, hrd->cpb_removal_delay_length );     /* cpb_removal_delay */
                lsmash_bits_get( bits, hrd->dpb_output_delay_length );      /* dpb_output_delay */
            }
            if( sps->vui.pic_struct_present_flag )
            {
                sei->pic_timing.pic_struct = lsmash_bits_get( bits, 4 );
                /* Skip the remaining bits. */
                uint32_t remaining_bits = payloadSize * 8 - 4;
                if( hrd->CpbDpbDelaysPresentFlag )
                    remaining_bits -= hrd->cpb_removal_delay_length
                                    + hrd->dpb_output_delay_length;
                lsmash_bits_get( bits, remaining_bits );
            }
        }
        else if( payloadType == 3 )
        {
            /* filler_payload
             * 'avc1' and 'avc2' samples are forbidden to contain this. */
            return LSMASH_ERR_PATCH_WELCOME;
        }
        else if( payloadType == 6 )
        {
            /* recovery_point */
            sei->recovery_point.present            = 1;
            sei->recovery_point.random_accessible  = 1;
            sei->recovery_point.recovery_frame_cnt = nalu_get_exp_golomb_ue( bits );
            lsmash_bits_get( bits, 1 );     /* exact_match_flag */
            sei->recovery_point.broken_link_flag   = lsmash_bits_get( bits, 1 );
            lsmash_bits_get( bits, 2 );     /* changing_slice_group_idc */
        }
        else
        {
skip_sei_message:
            lsmash_bits_get( bits, payloadSize * 8 );
        }
        lsmash_bits_get_align( bits );
        rbsp_pos += payloadSize;
        if( rbsp_pos > rbsp_size )
        {
            rbsp_pos = rbsp_size;
            if( *(rbsp_start + rbsp_pos) != 0x80 )
            {
                lsmash_log( NULL, LSMASH_LOG_ERROR, "Invalid payloadSize is there within H.264/AVC sei_message().\n" );
                return LSMASH_ERR_INVALID_DATA;
            }
            else
            {
                /* The last payloadSize is invalid but it probably can do recovery, so just log warning and break loop here. */
                lsmash_log( NULL, LSMASH_LOG_WARNING, "Invalid payloadSize is there within H.264/AVC sei_message().\n" );
                break;  /* redundant but for readability */
            }
        }
    } while( *(rbsp_start + rbsp_pos) != 0x80 );        /* All SEI messages are byte aligned at their end.
                                                         * Therefore, 0x80 shall be rbsp_trailing_bits(). */
    lsmash_bits_empty( bits );
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int h264_parse_slice_header
(
    h264_info_t        *info,
    h264_nalu_header_t *nuh
)
{
    h264_slice_info_t *slice = &info->slice;
    memset( slice, 0, sizeof(h264_slice_info_t) );
    /* slice_header() */
    lsmash_bits_t *bits = info->bits;
    nalu_get_exp_golomb_ue( bits );     /* first_mb_in_slice */
    uint8_t slice_type = slice->type = nalu_get_exp_golomb_ue( bits );
    if( (uint64_t)slice->type > 9 )
        return LSMASH_ERR_INVALID_DATA;
    if( slice_type > 4 )
        slice_type = slice->type -= 5;
    uint64_t pic_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    if( pic_parameter_set_id > 255 )
        return LSMASH_ERR_INVALID_DATA;
    slice->pic_parameter_set_id = pic_parameter_set_id;
    h264_pps_t *pps = h264_get_pps( info->pps_list, pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    h264_sps_t *sps = h264_get_sps( info->sps_list, pps->seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    slice->seq_parameter_set_id = pps->seq_parameter_set_id;
    slice->nal_ref_idc          = nuh->nal_ref_idc;
    slice->IdrPicFlag           = (nuh->nal_unit_type == H264_NALU_TYPE_SLICE_IDR);
    slice->pic_order_cnt_type   = sps->pic_order_cnt_type;
    if( (slice->IdrPicFlag || sps->max_num_ref_frames == 0) && slice_type != 2 && slice_type != 4 )
        return LSMASH_ERR_INVALID_DATA;
    if( sps->separate_colour_plane_flag )
        lsmash_bits_get( bits, 2 );     /* colour_plane_id */
    uint64_t frame_num = lsmash_bits_get( bits, sps->log2_max_frame_num );
    if( frame_num >= (1ULL << sps->log2_max_frame_num) || (slice->IdrPicFlag && frame_num) )
        return LSMASH_ERR_INVALID_DATA;
    slice->frame_num = frame_num;
    if( !sps->frame_mbs_only_flag )
    {
        slice->field_pic_flag = lsmash_bits_get( bits, 1 );
        if( slice->field_pic_flag )
            slice->bottom_field_flag = lsmash_bits_get( bits, 1 );
    }
    if( slice->IdrPicFlag )
    {
        uint64_t idr_pic_id = nalu_get_exp_golomb_ue( bits );
        if( idr_pic_id > 65535 )
            return LSMASH_ERR_INVALID_DATA;
        slice->idr_pic_id = idr_pic_id;
    }
    if( sps->pic_order_cnt_type == 0 )
    {
        uint64_t pic_order_cnt_lsb = lsmash_bits_get( bits, sps->log2_max_pic_order_cnt_lsb );
        if( pic_order_cnt_lsb >= sps->MaxPicOrderCntLsb )
            return LSMASH_ERR_INVALID_DATA;
        slice->pic_order_cnt_lsb = pic_order_cnt_lsb;
        if( pps->bottom_field_pic_order_in_frame_present_flag && !slice->field_pic_flag )
            slice->delta_pic_order_cnt_bottom = nalu_get_exp_golomb_se( bits );
    }
    else if( sps->pic_order_cnt_type == 1 && !sps->delta_pic_order_always_zero_flag )
    {
        slice->delta_pic_order_cnt[0] = nalu_get_exp_golomb_se( bits );
        if( pps->bottom_field_pic_order_in_frame_present_flag && !slice->field_pic_flag )
            slice->delta_pic_order_cnt[1] = nalu_get_exp_golomb_se( bits );
    }
    if( pps->redundant_pic_cnt_present_flag )
    {
        uint64_t redundant_pic_cnt = nalu_get_exp_golomb_ue( bits );
        if( redundant_pic_cnt > 127 )
            return LSMASH_ERR_INVALID_DATA;
        slice->has_redundancy = !!redundant_pic_cnt;
    }
    if( slice_type == H264_SLICE_TYPE_B )
        lsmash_bits_get( bits, 1 );
    uint64_t num_ref_idx_l0_active_minus1 = pps->num_ref_idx_l0_default_active_minus1;
    uint64_t num_ref_idx_l1_active_minus1 = pps->num_ref_idx_l1_default_active_minus1;
    if( slice_type == H264_SLICE_TYPE_P || slice_type == H264_SLICE_TYPE_SP || slice_type == H264_SLICE_TYPE_B )
    {
        if( lsmash_bits_get( bits, 1 ) )            /* num_ref_idx_active_override_flag */
        {
            num_ref_idx_l0_active_minus1 = nalu_get_exp_golomb_ue( bits );
            if( num_ref_idx_l0_active_minus1 > 31 )
                return LSMASH_ERR_INVALID_DATA;
            if( slice_type == H264_SLICE_TYPE_B )
            {
                num_ref_idx_l1_active_minus1 = nalu_get_exp_golomb_ue( bits );
                if( num_ref_idx_l1_active_minus1 > 31 )
                    return LSMASH_ERR_INVALID_DATA;
            }
        }
    }
    if( nuh->nal_unit_type == H264_NALU_TYPE_SLICE_EXT
     || nuh->nal_unit_type == H264_NALU_TYPE_SLICE_EXT_DVC )
    {
        return LSMASH_ERR_PATCH_WELCOME;    /* No support of MVC yet */
#if 0
        /* ref_pic_list_mvc_modification() */
        if( slice_type == H264_SLICE_TYPE_P || slice_type == H264_SLICE_TYPE_B || slice_type == H264_SLICE_TYPE_SP )
        {
            for( int i = 0; i < 1 + (slice_type == H264_SLICE_TYPE_B); i++ )
            {
                if( lsmash_bits_get( bits, 1 ) )        /* (S)P and B: ref_pic_list_modification_flag_l0
                                                         *          B: ref_pic_list_modification_flag_l1 */
                {
                    uint64_t modification_of_pic_nums_idc;
                    do
                    {
                        modification_of_pic_nums_idc = nalu_get_exp_golomb_ue( bits );
#if 0
                        if( modification_of_pic_nums_idc == 0 || modification_of_pic_nums_idc == 1 )
                            nalu_get_exp_golomb_ue( bits );     /* abs_diff_pic_num_minus1 */
                        else if( modification_of_pic_nums_idc == 2 )
                            nalu_get_exp_golomb_ue( bits );     /* long_term_pic_num */
                        else if( modification_of_pic_nums_idc == 4 || modification_of_pic_nums_idc == 5 )
                            nalu_get_exp_golomb_ue( bits );     /* abs_diff_view_idx_minus1 */
#else
                        if( modification_of_pic_nums_idc != 3 )
                            nalu_get_exp_golomb_ue( bits );     /* abs_diff_pic_num_minus1, long_term_pic_num or abs_diff_view_idx_minus1 */
#endif
                    } while( modification_of_pic_nums_idc != 3 );
                }
            }
        }
#endif
    }
    else
    {
        /* ref_pic_list_modification() */
        if( slice_type == H264_SLICE_TYPE_P || slice_type == H264_SLICE_TYPE_B || slice_type == H264_SLICE_TYPE_SP )
        {
            for( int i = 0; i < 1 + (slice_type == H264_SLICE_TYPE_B); i++ )
            {
                if( lsmash_bits_get( bits, 1 ) )        /* (S)P and B: ref_pic_list_modification_flag_l0
                                                         *          B: ref_pic_list_modification_flag_l1 */
                {
                    uint64_t modification_of_pic_nums_idc;
                    do
                    {
                        modification_of_pic_nums_idc = nalu_get_exp_golomb_ue( bits );
#if 0
                        if( modification_of_pic_nums_idc == 0 || modification_of_pic_nums_idc == 1 )
                            nalu_get_exp_golomb_ue( bits );     /* abs_diff_pic_num_minus1 */
                        else if( modification_of_pic_nums_idc == 2 )
                            nalu_get_exp_golomb_ue( bits );     /* long_term_pic_num */
#else
                        if( modification_of_pic_nums_idc != 3 )
                            nalu_get_exp_golomb_ue( bits );     /* abs_diff_pic_num_minus1 or long_term_pic_num */
#endif
                    } while( modification_of_pic_nums_idc != 3 );
                }
            }
        }
    }
    if( (pps->weighted_pred_flag && (slice_type == H264_SLICE_TYPE_P || slice_type == H264_SLICE_TYPE_SP))
     || (pps->weighted_bipred_idc == 1 && slice_type == H264_SLICE_TYPE_B) )
    {
        /* pred_weight_table() */
        nalu_get_exp_golomb_ue( bits );         /* luma_log2_weight_denom */
        if( sps->ChromaArrayType )
            nalu_get_exp_golomb_ue( bits );     /* chroma_log2_weight_denom */
        for( uint8_t i = 0; i <= num_ref_idx_l0_active_minus1; i++ )
        {
            if( lsmash_bits_get( bits, 1 ) )    /* luma_weight_l0_flag */
            {
                nalu_get_exp_golomb_se( bits );     /* luma_weight_l0[i] */
                nalu_get_exp_golomb_se( bits );     /* luma_offset_l0[i] */
            }
            if( sps->ChromaArrayType
             && lsmash_bits_get( bits, 1 )      /* chroma_weight_l0_flag */ )
                for( int j = 0; j < 2; j++ )
                {
                    nalu_get_exp_golomb_se( bits );     /* chroma_weight_l0[i][j]*/
                    nalu_get_exp_golomb_se( bits );     /* chroma_offset_l0[i][j] */
                }
        }
        if( slice_type == H264_SLICE_TYPE_B )
            for( uint8_t i = 0; i <= num_ref_idx_l1_active_minus1; i++ )
            {
                if( lsmash_bits_get( bits, 1 ) )    /* luma_weight_l1_flag */
                {
                    nalu_get_exp_golomb_se( bits );     /* luma_weight_l1[i] */
                    nalu_get_exp_golomb_se( bits );     /* luma_offset_l1[i] */
                }
                if( sps->ChromaArrayType
                 && lsmash_bits_get( bits, 1 )      /* chroma_weight_l1_flag */ )
                    for( int j = 0; j < 2; j++ )
                    {
                        nalu_get_exp_golomb_se( bits );     /* chroma_weight_l1[i][j]*/
                        nalu_get_exp_golomb_se( bits );     /* chroma_offset_l1[i][j] */
                    }
            }
    }
    if( nuh->nal_ref_idc )
    {
        /* dec_ref_pic_marking() */
        if( slice->IdrPicFlag )
        {
            lsmash_bits_get( bits, 1 );     /* no_output_of_prior_pics_flag */
            lsmash_bits_get( bits, 1 );     /* long_term_reference_flag */
        }
        else if( lsmash_bits_get( bits, 1 ) )       /* adaptive_ref_pic_marking_mode_flag */
        {
            uint64_t memory_management_control_operation;
            do
            {
                memory_management_control_operation = nalu_get_exp_golomb_ue( bits );
                if( memory_management_control_operation )
                {
                    if( memory_management_control_operation == 5 )
                        slice->has_mmco5 = 1;
                    else
                    {
                        nalu_get_exp_golomb_ue( bits );
                        if( memory_management_control_operation == 3 )
                            nalu_get_exp_golomb_ue( bits );
                    }
                }
            } while( memory_management_control_operation );
        }
    }
    /* We needn't read more if not slice data partition A.
     * Skip slice_data() and rbsp_slice_trailing_bits(). */
    if( nuh->nal_unit_type == H264_NALU_TYPE_SLICE_DP_A )
    {
        if( pps->entropy_coding_mode_flag && slice_type != H264_SLICE_TYPE_I && slice_type != H264_SLICE_TYPE_SI )
            nalu_get_exp_golomb_ue( bits );     /* cabac_init_idc */
        nalu_get_exp_golomb_se( bits );         /* slice_qp_delta */
        if( slice_type == H264_SLICE_TYPE_SP || slice_type == H264_SLICE_TYPE_SI )
        {
            if( slice_type == H264_SLICE_TYPE_SP )
                lsmash_bits_get( bits, 1 );     /* sp_for_switch_flag */
            nalu_get_exp_golomb_se( bits );     /* slice_qs_delta */
        }
        if( pps->deblocking_filter_control_present_flag
         && nalu_get_exp_golomb_ue( bits ) != 1 /* disable_deblocking_filter_idc */ )
        {
            int64_t slice_alpha_c0_offset_div2 = nalu_get_exp_golomb_se( bits );
            if( slice_alpha_c0_offset_div2 < -6 || slice_alpha_c0_offset_div2 > 6 )
                return LSMASH_ERR_INVALID_DATA;
            int64_t slice_beta_offset_div2     = nalu_get_exp_golomb_se( bits );
            if( slice_beta_offset_div2     < -6 || slice_beta_offset_div2     > 6 )
                return LSMASH_ERR_INVALID_DATA;
        }
        if( pps->num_slice_groups_minus1
         && (pps->slice_group_map_type == 3 || pps->slice_group_map_type == 4 || pps->slice_group_map_type == 5) )
        {
            uint64_t temp = ((uint64_t)sps->PicSizeInMapUnits - 1) / pps->SliceGroupChangeRate + 1;
            uint64_t slice_group_change_cycle = lsmash_bits_get( bits, lsmash_ceil_log2( temp + 1 ) );
            if( slice_group_change_cycle > temp )
                return LSMASH_ERR_INVALID_DATA;
        }
        /* end of slice_header() */
        slice->slice_id = nalu_get_exp_golomb_ue( bits );
        h264_slice_info_t *slice_part = h264_get_slice_info( info->slice_list, slice->slice_id );
        if( !slice_part )
            return LSMASH_ERR_NAMELESS;
        *slice_part = *slice;
    }
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    info->sps = *sps;
    info->pps = *pps;
    return 0;
}

int h264_parse_slice
(
    h264_info_t        *info,
    h264_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    uint64_t size = nuh->nal_unit_type == H264_NALU_TYPE_SLICE_IDR || nuh->nal_ref_idc == 0
                  ? LSMASH_MIN( ebsp_size, 100 )
                  : LSMASH_MIN( ebsp_size, 1000 );
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, size );
    if( err < 0 )
        return err;
    if( nuh->nal_unit_type != H264_NALU_TYPE_SLICE_DP_B
     && nuh->nal_unit_type != H264_NALU_TYPE_SLICE_DP_C )
        return h264_parse_slice_header( info, nuh );
    /* slice_data_partition_b_layer_rbsp() or slice_data_partition_c_layer_rbsp() */
    uint64_t slice_id = nalu_get_exp_golomb_ue( bits );
    h264_slice_info_t *slice = h264_get_slice_info( info->slice_list, slice_id );
    if( !slice )
        return LSMASH_ERR_NAMELESS;
    h264_pps_t *pps = h264_get_pps( info->pps_list, slice->pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    h264_sps_t *sps = h264_get_sps( info->sps_list, pps->seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    slice->seq_parameter_set_id = pps->seq_parameter_set_id;
    if( sps->separate_colour_plane_flag )
        lsmash_bits_get( bits, 2 );     /* colour_plane_id */
    if( pps->redundant_pic_cnt_present_flag )
    {
        uint64_t redundant_pic_cnt = nalu_get_exp_golomb_ue( bits );
        if( redundant_pic_cnt > 127 )
            return LSMASH_ERR_INVALID_DATA;
        slice->has_redundancy = !!redundant_pic_cnt;
    }
    /* Skip slice_data() and rbsp_slice_trailing_bits(). */
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    info->sps = *sps;
    info->pps = *pps;
    return 0;
}

static int h264_get_sps_id
(
    uint8_t *ps_ebsp,
    uint32_t ps_ebsp_length,
    uint8_t *ps_id
)
{
    /* max number of bits of sps_id = 11: 0b000001XXXXX
     * (24 + 11 - 1) / 8 + 1 = 5 bytes
     * Why +1? Because there might be an emulation_prevention_three_byte. */
    lsmash_bits_t bits = { 0 };
    lsmash_bs_t   bs   = { 0 };
    uint8_t rbsp_buffer[6];
    uint8_t buffer     [6];
    bs.buffer.data  = buffer;
    bs.buffer.alloc = 6;
    lsmash_bits_init( &bits, &bs );
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( &bits, rbsp_buffer, &rbsp_size, ps_ebsp, LSMASH_MIN( ps_ebsp_length, 6 ) );
    if( err < 0 )
        return err;
    lsmash_bits_get( &bits, 24 );   /* profile_idc, constraint_set_flags and level_idc */
    uint64_t sec_parameter_set_id = nalu_get_exp_golomb_ue( &bits );
    if( sec_parameter_set_id > 31 )
        return LSMASH_ERR_INVALID_DATA;
    *ps_id = sec_parameter_set_id;
    return bs.error ? LSMASH_ERR_NAMELESS : 0;
}

static int h264_get_pps_id
(
    uint8_t *ps_ebsp,
    uint32_t ps_ebsp_length,
    uint8_t *ps_id
)
{
    /* max number of bits of pps_id = 17: 0b000000001XXXXXXXX
     * (17 - 1) / 8 + 1 = 3 bytes
     * Why +1? Because there might be an emulation_prevention_three_byte. */
    lsmash_bits_t bits = { 0 };
    lsmash_bs_t   bs   = { 0 };
    uint8_t rbsp_buffer[4];
    uint8_t buffer     [4];
    bs.buffer.data  = buffer;
    bs.buffer.alloc = 4;
    lsmash_bits_init( &bits, &bs );
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( &bits, rbsp_buffer, &rbsp_size, ps_ebsp, LSMASH_MIN( ps_ebsp_length, 4 ) );
    if( err < 0 )
        return err;
    uint64_t pic_parameter_set_id = nalu_get_exp_golomb_ue( &bits );
    if( pic_parameter_set_id > 255 )
        return LSMASH_ERR_INVALID_DATA;
    *ps_id = pic_parameter_set_id;
    return bs.error ? LSMASH_ERR_NAMELESS : 0;
}

static inline int h264_get_ps_id
(
    uint8_t                       *ps_ebsp,
    uint32_t                       ps_ebsp_length,
    uint8_t                       *ps_id,
    lsmash_h264_parameter_set_type ps_type
)
{
    int (*get_ps_id)( uint8_t *ps_ebsp, uint32_t ps_ebsp_length, uint8_t *ps_id )
        = ps_type == H264_PARAMETER_SET_TYPE_SPS ? h264_get_sps_id
        : ps_type == H264_PARAMETER_SET_TYPE_PPS ? h264_get_pps_id
        :                                          NULL;
    return get_ps_id ? get_ps_id( ps_ebsp, ps_ebsp_length, ps_id ) : LSMASH_ERR_INVALID_DATA;
}

static inline lsmash_entry_list_t *h264_get_parameter_set_list
(
    lsmash_h264_specific_parameters_t *param,
    lsmash_h264_parameter_set_type     ps_type
)
{
    if( !param->parameter_sets )
        return NULL;
    return ps_type == H264_PARAMETER_SET_TYPE_SPS    ? param->parameter_sets->sps_list
         : ps_type == H264_PARAMETER_SET_TYPE_PPS    ? param->parameter_sets->pps_list
         : ps_type == H264_PARAMETER_SET_TYPE_SPSEXT ? param->parameter_sets->spsext_list
         : NULL;
}

static lsmash_entry_t *h264_get_ps_entry_from_param
(
    lsmash_h264_specific_parameters_t *param,
    lsmash_h264_parameter_set_type     ps_type,
    uint8_t                            ps_id
)
{
    int (*get_ps_id)( uint8_t *ps_ebsp, uint32_t ps_ebsp_length, uint8_t *ps_id )
        = ps_type == H264_PARAMETER_SET_TYPE_SPS ? h264_get_sps_id
        : ps_type == H264_PARAMETER_SET_TYPE_PPS ? h264_get_pps_id
        :                                          NULL;
    if( !get_ps_id )
        return NULL;
    lsmash_entry_list_t *ps_list = h264_get_parameter_set_list( param, ps_type );
    if( !ps_list )
        return NULL;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return NULL;
        uint8_t param_ps_id;
        if( get_ps_id( ps->nalUnit + 1, ps->nalUnitLength - 1, &param_ps_id ) < 0 )
            return NULL;
        if( ps_id == param_ps_id )
            return entry;
    }
    return NULL;
}

static inline void  h264_update_picture_type
(
    h264_picture_info_t *picture,
    h264_slice_info_t   *slice
)
{
    if( picture->type == H264_PICTURE_TYPE_I_P )
    {
        if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_P_B;
        else if( slice->type == H264_SLICE_TYPE_SI || slice->type == H264_SLICE_TYPE_SP )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP;
    }
    else if( picture->type == H264_PICTURE_TYPE_I_P_B )
    {
        if( slice->type != H264_SLICE_TYPE_P && slice->type != H264_SLICE_TYPE_B && slice->type != H264_SLICE_TYPE_I )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP_B;
    }
    else if( picture->type == H264_PICTURE_TYPE_I )
    {
        if( slice->type == H264_SLICE_TYPE_P )
            picture->type = H264_PICTURE_TYPE_I_P;
        else if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_P_B;
        else if( slice->type == H264_SLICE_TYPE_SI )
            picture->type = H264_PICTURE_TYPE_I_SI;
        else if( slice->type == H264_SLICE_TYPE_SP )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP;
    }
    else if( picture->type == H264_PICTURE_TYPE_SI_SP )
    {
        if( slice->type == H264_SLICE_TYPE_P || slice->type == H264_SLICE_TYPE_I )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP;
        else if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP_B;
    }
    else if( picture->type == H264_PICTURE_TYPE_SI )
    {
        if( slice->type == H264_SLICE_TYPE_P )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP;
        else if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP_B;
        else if( slice->type != H264_SLICE_TYPE_I )
            picture->type = H264_PICTURE_TYPE_I_SI;
        else if( slice->type == H264_SLICE_TYPE_SP )
            picture->type = H264_PICTURE_TYPE_SI_SP;
    }
    else if( picture->type == H264_PICTURE_TYPE_I_SI )
    {
        if( slice->type == H264_SLICE_TYPE_P || slice->type == H264_SLICE_TYPE_SP )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP;
        else if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP_B;
    }
    else if( picture->type == H264_PICTURE_TYPE_I_SI_P_SP )
    {
        if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_SI_P_SP_B;
    }
    else if( picture->type == H264_PICTURE_TYPE_NONE )
    {
        if( slice->type == H264_SLICE_TYPE_P )
            picture->type = H264_PICTURE_TYPE_I_P;
        else if( slice->type == H264_SLICE_TYPE_B )
            picture->type = H264_PICTURE_TYPE_I_P_B;
        else if( slice->type == H264_SLICE_TYPE_I )
            picture->type = H264_PICTURE_TYPE_I;
        else if( slice->type == H264_SLICE_TYPE_SI )
            picture->type = H264_PICTURE_TYPE_SI;
        else if( slice->type == H264_SLICE_TYPE_SP )
            picture->type = H264_PICTURE_TYPE_SI_SP;
    }
#if 0
    fprintf( stderr, "Picture type = %s\n", picture->type == H264_PICTURE_TYPE_I_P   ? "P"
                                          : picture->type == H264_PICTURE_TYPE_I_P_B ? "B"
                                          : picture->type == H264_PICTURE_TYPE_I     ? "I"
                                          : picture->type == H264_PICTURE_TYPE_SI    ? "SI"
                                          : picture->type == H264_PICTURE_TYPE_I_SI  ? "SI"
                                          :                                            "SP" );
#endif
}

/* Shall be called at least once per picture. */
void h264_update_picture_info_for_slice
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_slice_info_t   *slice
)
{
    assert( info );
    picture->has_mmco5      |= slice->has_mmco5;
    picture->has_redundancy |= slice->has_redundancy;
    picture->has_primary    |= !slice->has_redundancy;
    h264_update_picture_type( picture, slice );
    /* Mark 'used' on active parameter sets. */
    uint8_t ps_id[2] = { slice->seq_parameter_set_id, slice->pic_parameter_set_id };
    for( int i = 0; i < 2; i++ )
    {
        lsmash_h264_parameter_set_type ps_type = (lsmash_h264_parameter_set_type)i;
        lsmash_entry_t *entry = h264_get_ps_entry_from_param( &info->avcC_param, ps_type, ps_id[i] );
        if( entry && entry->data )
        {
            isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
            if( ps->unused )
                lsmash_append_h264_parameter_set( &info->avcC_param, ps_type, ps->nalUnit, ps->nalUnitLength );
        }
    }
    /* Discard this slice info. */
    slice->present = 0;
}

/* Shall be called exactly once per picture. */
void h264_update_picture_info
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_slice_info_t   *slice,
    h264_sei_t          *sei
)
{
    picture->frame_num                  = slice->frame_num;
    picture->pic_order_cnt_lsb          = slice->pic_order_cnt_lsb;
    picture->delta_pic_order_cnt_bottom = slice->delta_pic_order_cnt_bottom;
    picture->delta_pic_order_cnt[0]     = slice->delta_pic_order_cnt[0];
    picture->delta_pic_order_cnt[1]     = slice->delta_pic_order_cnt[1];
    picture->field_pic_flag             = slice->field_pic_flag;
    picture->bottom_field_flag          = slice->bottom_field_flag;
    picture->idr                        = slice->IdrPicFlag;
    picture->pic_parameter_set_id       = slice->pic_parameter_set_id;
    picture->disposable                 = (slice->nal_ref_idc == 0);
    picture->random_accessible          = slice->IdrPicFlag;
    h264_update_picture_info_for_slice( info, picture, slice );
    picture->independent = picture->type == H264_PICTURE_TYPE_I || picture->type == H264_PICTURE_TYPE_I_SI;
    if( sei->pic_timing.present )
    {
        if( sei->pic_timing.pic_struct < 9 )
        {
            static const uint8_t DeltaTfiDivisor[9] = { 2, 1, 1, 2, 2, 3, 3, 4, 6 };
            picture->delta = DeltaTfiDivisor[ sei->pic_timing.pic_struct ];
        }
        else
            /* Reserved values in the spec we refer to. */
            picture->delta = picture->field_pic_flag ? 1 : 2;
        sei->pic_timing.present = 0;
    }
    else
        picture->delta = picture->field_pic_flag ? 1 : 2;
    if( sei->recovery_point.present )
    {
        picture->random_accessible |= sei->recovery_point.random_accessible;
        picture->broken_link_flag  |= sei->recovery_point.broken_link_flag;
        picture->recovery_frame_cnt = sei->recovery_point.recovery_frame_cnt;
        sei->recovery_point.present = 0;
    }
}

int h264_find_au_delimit_by_slice_info
(
    h264_slice_info_t *slice,
    h264_slice_info_t *prev_slice
)
{
    if( slice->frame_num                    != prev_slice->frame_num
     || ((slice->pic_order_cnt_type == 0    && prev_slice->pic_order_cnt_type == 0)
      && (slice->pic_order_cnt_lsb          != prev_slice->pic_order_cnt_lsb
      ||  slice->delta_pic_order_cnt_bottom != prev_slice->delta_pic_order_cnt_bottom))
     || ((slice->pic_order_cnt_type == 1    && prev_slice->pic_order_cnt_type == 1)
      && (slice->delta_pic_order_cnt[0]     != prev_slice->delta_pic_order_cnt[0]
      ||  slice->delta_pic_order_cnt[1]     != prev_slice->delta_pic_order_cnt[1]))
     || slice->field_pic_flag               != prev_slice->field_pic_flag
     || slice->bottom_field_flag            != prev_slice->bottom_field_flag
     || slice->IdrPicFlag                   != prev_slice->IdrPicFlag
     || slice->pic_parameter_set_id         != prev_slice->pic_parameter_set_id
     || ((slice->nal_ref_idc == 0           || prev_slice->nal_ref_idc == 0)
      && (slice->nal_ref_idc                != prev_slice->nal_ref_idc))
     || (slice->IdrPicFlag == 1             && prev_slice->IdrPicFlag == 1
      && slice->idr_pic_id                  != prev_slice->idr_pic_id) )
        return 1;
    return 0;
}

int h264_find_au_delimit_by_nalu_type
(
    uint8_t nalu_type,
    uint8_t prev_nalu_type
)
{
    return ((nalu_type >= H264_NALU_TYPE_SEI    && nalu_type <= H264_NALU_TYPE_AUD)
         || (nalu_type >= H264_NALU_TYPE_PREFIX && nalu_type <= H264_NALU_TYPE_RSV_NVCL18))
        && ((prev_nalu_type >= H264_NALU_TYPE_SLICE_N_IDR && prev_nalu_type <= H264_NALU_TYPE_SLICE_IDR)
         || prev_nalu_type == H264_NALU_TYPE_FD || prev_nalu_type == H264_NALU_TYPE_SLICE_AUX);
}

int h264_supplement_buffer
(
    h264_stream_buffer_t *sb,
    h264_access_unit_t   *au,
    uint32_t              size
)
{
    lsmash_multiple_buffers_t *bank = lsmash_resize_multiple_buffers( sb->bank, size );
    if( !bank )
        return LSMASH_ERR_MEMORY_ALLOC;
    sb->bank = bank;
    sb->rbsp = lsmash_withdraw_buffer( bank, 1 );
    if( au && bank->number_of_buffers == 3 )
    {
        au->data            = lsmash_withdraw_buffer( bank, 2 );
        au->incomplete_data = lsmash_withdraw_buffer( bank, 3 );
    }
    return 0;
}

static void h264_bs_put_parameter_sets
(
    lsmash_bs_t         *bs,
    lsmash_entry_list_t *ps_list,
    uint32_t             max_ps_count
)
{
    uint32_t ps_count = 0;
    for( lsmash_entry_t *entry = ps_list->head; entry && ps_count < max_ps_count; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( ps && !ps->unused )
        {
            lsmash_bs_put_be16( bs, ps->nalUnitLength );
            lsmash_bs_put_bytes( bs, ps->nalUnitLength, ps->nalUnit );
        }
        else
            continue;
        ++ps_count;
    }
}

uint8_t *lsmash_create_h264_specific_info
(
    lsmash_h264_specific_parameters_t *param,
    uint32_t                          *data_length
)
{
    if( !param || !param->parameter_sets || !data_length )
        return NULL;
    if( param->lengthSizeMinusOne != 0 && param->lengthSizeMinusOne != 1 && param->lengthSizeMinusOne != 3 )
        return NULL;
    static const uint32_t max_ps_count[3] = { 31, 255, 255 };
    lsmash_entry_list_t *ps_list[3] =
        {
            param->parameter_sets->sps_list,        /* SPS */
            param->parameter_sets->pps_list,        /* PPS */
            param->parameter_sets->spsext_list      /* SPSExt */
        };
    uint32_t ps_count[3] = { 0, 0, 0 };
    /* SPS and PPS are mandatory. */
    if( !ps_list[0] || !ps_list[0]->head || ps_list[0]->entry_count == 0
     || !ps_list[1] || !ps_list[1]->head || ps_list[1]->entry_count == 0 )
        return NULL;
    for( int i = 0; i < 3; i++ )
        if( ps_list[i] )
            for( lsmash_entry_t *entry = ps_list[i]->head; entry && ps_count[i] < max_ps_count[i]; entry = entry->next )
            {
                isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
                if( !ps )
                    return NULL;
                if( ps->unused )
                    continue;
                ++ps_count[i];
            }
    /* Create an AVCConfigurationBox */
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return NULL;
    lsmash_bs_put_be32( bs, 0 );                                            /* box size */
    lsmash_bs_put_be32( bs, ISOM_BOX_TYPE_AVCC.fourcc );                    /* box type: 'avcC' */
    lsmash_bs_put_byte( bs, 1 );                                            /* configurationVersion */
    lsmash_bs_put_byte( bs, param->AVCProfileIndication );                  /* AVCProfileIndication */
    lsmash_bs_put_byte( bs, param->profile_compatibility );                 /* profile_compatibility */
    lsmash_bs_put_byte( bs, param->AVCLevelIndication );                    /* AVCLevelIndication */
    lsmash_bs_put_byte( bs, param->lengthSizeMinusOne | 0xfc );             /* lengthSizeMinusOne */
    lsmash_bs_put_byte( bs, ps_count[0] | 0xe0 );                           /* numOfSequenceParameterSets */
    h264_bs_put_parameter_sets( bs, ps_list[0], ps_count[0] );              /* sequenceParameterSetLength
                                                                             * sequenceParameterSetNALUnit */
    lsmash_bs_put_byte( bs, ps_count[1] );                                  /* numOfPictureParameterSets */
    h264_bs_put_parameter_sets( bs, ps_list[1], ps_count[1] );              /* pictureParameterSetLength
                                                                             * pictureParameterSetNALUnit */
    if( H264_REQUIRES_AVCC_EXTENSION( param->AVCProfileIndication ) )
    {
        lsmash_bs_put_byte( bs, param->chroma_format           | 0xfc );    /* chroma_format */
        lsmash_bs_put_byte( bs, param->bit_depth_luma_minus8   | 0xf8 );    /* bit_depth_luma_minus8 */
        lsmash_bs_put_byte( bs, param->bit_depth_chroma_minus8 | 0xf8 );    /* bit_depth_chroma_minus8 */
        if( ps_list[2] )
        {
            lsmash_bs_put_byte( bs, ps_count[2] );                          /* numOfSequenceParameterSetExt */
            h264_bs_put_parameter_sets( bs, ps_list[2], ps_count[2] );      /* sequenceParameterSetExtLength
                                                                             * sequenceParameterSetExtNALUnit */
        }
        else    /* no sequence parameter set extensions */
            lsmash_bs_put_byte( bs, 0 );                                    /* numOfSequenceParameterSetExt */
    }
    uint8_t *data = lsmash_bs_export_data( bs, data_length );
    lsmash_bs_cleanup( bs );
    /* Update box size. */
    LSMASH_SET_BE32( data, *data_length );
    return data;
}

static inline int h264_validate_ps_type
(
    lsmash_h264_parameter_set_type ps_type,
    void                          *ps_data,
    uint32_t                       ps_length
)
{
    if( !ps_data || ps_length < 2 )
        return LSMASH_ERR_INVALID_DATA;
    if( ps_type != H264_PARAMETER_SET_TYPE_SPS
     && ps_type != H264_PARAMETER_SET_TYPE_PPS
     && ps_type != H264_PARAMETER_SET_TYPE_SPSEXT )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t nalu_type = *((uint8_t *)ps_data) & 0x1f;
    if( nalu_type != H264_NALU_TYPE_SPS
     && nalu_type != H264_NALU_TYPE_PPS
     && nalu_type != H264_NALU_TYPE_SPS_EXT )
        return LSMASH_ERR_INVALID_DATA;
    if( (ps_type == H264_PARAMETER_SET_TYPE_SPS    && nalu_type != H264_NALU_TYPE_SPS)
     || (ps_type == H264_PARAMETER_SET_TYPE_PPS    && nalu_type != H264_NALU_TYPE_PPS)
     || (ps_type == H264_PARAMETER_SET_TYPE_SPSEXT && nalu_type != H264_NALU_TYPE_SPS_EXT) )
        return LSMASH_ERR_INVALID_DATA;
    return 0;
}

static lsmash_dcr_nalu_appendable h264_check_sps_appendable
(
    lsmash_bits_t                     *bits,
    uint8_t                           *rbsp_buffer,
    lsmash_h264_specific_parameters_t *param,
    uint8_t                           *ps_data,
    uint32_t                           ps_length,
    lsmash_entry_list_t               *ps_list
)
{
    h264_sps_t sps;
    if( h264_parse_sps_minimally( bits, &sps, rbsp_buffer, ps_data + 1, ps_length - 1 ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    lsmash_bits_empty( bits );
    /* FIXME; If the sequence parameter sets are marked with different profiles,
     * and the relevant profile compatibility flags are all zero,
     * then the stream may need examination to determine which profile, if any, the stream conforms to.
     * If the stream is not examined, or the examination reveals that there is no profile to which the stream conforms,
     * then the stream must be split into two or more sub-streams with separate configuration records in which these rules can be met. */
#if 0
    if( sps.profile_idc != param->AVCProfileIndication && (sps->constraint_set_flags & param->profile_compatibility) )
#else
    if( sps.profile_idc != param->AVCProfileIndication )
#endif
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    /* The values of chroma_format_idc, bit_depth_luma_minus8 and bit_depth_chroma_minus8
     * must be identical in all SPSs in a single AVC configuration record. */
    if( H264_REQUIRES_AVCC_EXTENSION( param->AVCProfileIndication )
     && (sps.chroma_format_idc       != param->chroma_format
     ||  sps.bit_depth_luma_minus8   != param->bit_depth_luma_minus8
     ||  sps.bit_depth_chroma_minus8 != param->bit_depth_chroma_minus8) )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    /* Forbidden to duplicate SPS that has the same seq_parameter_set_id with different form within the same configuration record. */
    uint8_t sps_id = sps.seq_parameter_set_id;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return DCR_NALU_APPEND_ERROR;
        if( ps->unused )
            continue;
        uint8_t param_sps_id;
        if( h264_get_sps_id( ps->nalUnit + 1, ps->nalUnitLength - 1, &param_sps_id ) < 0 )
            return DCR_NALU_APPEND_ERROR;
        if( sps_id == param_sps_id )
            /* SPS that has the same seq_parameter_set_id already exists with different form. */
            return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
        if( entry == ps_list->head )
        {
            /* Check if the visual presentation sizes are different. */
            h264_sps_t first_sps;
            if( h264_parse_sps_minimally( bits, &first_sps, rbsp_buffer,
                                          ps->nalUnit       + 1,
                                          ps->nalUnitLength - 1 ) < 0 )
                return DCR_NALU_APPEND_ERROR;
            if( sps.cropped_width  != first_sps.cropped_width
             || sps.cropped_height != first_sps.cropped_height )
                return DCR_NALU_APPEND_NEW_SAMPLE_ENTRY_REQUIRED;
        }
    }
    return DCR_NALU_APPEND_POSSIBLE;
}

static lsmash_dcr_nalu_appendable h264_check_pps_appendable
(
    uint8_t             *ps_data,
    uint32_t             ps_length,
    lsmash_entry_list_t *ps_list
)
{
    uint8_t pps_id;
    if( h264_get_pps_id( ps_data + 1, ps_length - 1, &pps_id ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return DCR_NALU_APPEND_ERROR;
        if( ps->unused )
            continue;
        uint8_t param_pps_id;
        if( h264_get_pps_id( ps->nalUnit + 1, ps->nalUnitLength - 1, &param_pps_id ) < 0 )
            return DCR_NALU_APPEND_ERROR;
        if( pps_id == param_pps_id )
            /* PPS that has the same pic_parameter_set_id already exists with different form. */
            return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    }
    return DCR_NALU_APPEND_POSSIBLE;
}

lsmash_dcr_nalu_appendable lsmash_check_h264_parameter_set_appendable
(
    lsmash_h264_specific_parameters_t *param,
    lsmash_h264_parameter_set_type     ps_type,
    void                              *_ps_data,
    uint32_t                           ps_length
)
{
    uint8_t *ps_data = _ps_data;
    if( !param )
        return DCR_NALU_APPEND_ERROR;
    if( h264_validate_ps_type( ps_type, ps_data, ps_length ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    if( ps_type == H264_PARAMETER_SET_TYPE_SPSEXT
     && !H264_REQUIRES_AVCC_EXTENSION( param->AVCProfileIndication ) )
        return DCR_NALU_APPEND_ERROR;
    /* Check whether the same parameter set already exsits or not. */
    lsmash_entry_list_t *ps_list = h264_get_parameter_set_list( param, ps_type );
    if( !ps_list || !ps_list->head )
        return DCR_NALU_APPEND_POSSIBLE;    /* No parameter set */
    switch( nalu_check_same_ps_existence( ps_list, ps_data, ps_length ) )
    {
        case 0  : break;
        case 1  : return DCR_NALU_APPEND_DUPLICATED;    /* The same parameter set already exists. */
        default : return DCR_NALU_APPEND_ERROR;         /* An error occured. */
    }
    uint32_t ps_count;
    if( nalu_get_ps_count( ps_list, &ps_count ) )
        return DCR_NALU_APPEND_ERROR;
    if( (ps_type == H264_PARAMETER_SET_TYPE_SPS    && ps_count >= 31)
     || (ps_type == H264_PARAMETER_SET_TYPE_PPS    && ps_count >= 255)
     || (ps_type == H264_PARAMETER_SET_TYPE_SPSEXT && ps_count >= 255) )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;    /* No more appendable parameter sets. */
    if( ps_type == H264_PARAMETER_SET_TYPE_SPSEXT )
        return DCR_NALU_APPEND_POSSIBLE;
    /* Check whether a new specific info is needed or not. */
    if( ps_type == H264_PARAMETER_SET_TYPE_PPS )
        /* PPS */
        return h264_check_pps_appendable( ps_data, ps_length, ps_list );
    else
    {
        /* SPS
         * Set up bitstream handler for parse parameter sets. */
        lsmash_bits_t *bits = lsmash_bits_adhoc_create();
        if( !bits )
            return DCR_NALU_APPEND_ERROR;
        uint32_t max_ps_length;
        uint8_t *rbsp_buffer;
        if( nalu_get_max_ps_length( ps_list, &max_ps_length ) < 0
         || (rbsp_buffer = lsmash_malloc( LSMASH_MAX( max_ps_length, ps_length ) )) == NULL )
        {
            lsmash_bits_adhoc_cleanup( bits );
            return DCR_NALU_APPEND_ERROR;
        }
        lsmash_dcr_nalu_appendable appendable = h264_check_sps_appendable( bits, rbsp_buffer, param, ps_data, ps_length, ps_list );
        lsmash_bits_adhoc_cleanup( bits );
        lsmash_free( rbsp_buffer );
        return appendable;
    }
}

static inline void h264_reorder_parameter_set_ascending_id
(
    lsmash_h264_specific_parameters_t *param,
    lsmash_h264_parameter_set_type     ps_type,
    lsmash_entry_list_t               *ps_list,
    uint8_t                            ps_id
)
{
    lsmash_entry_t *entry = NULL;
    if( ps_id )
        for( int i = ps_id - 1; i; i-- )
        {
            entry = h264_get_ps_entry_from_param( param, ps_type, i );
            if( entry )
                break;
        }
    int append_head = 0;
    if( !entry )
    {
        /* Couldn't find any parameter set with lower identifier.
         * Next, find parameter set with upper identifier. */
        int max_ps_id = ps_type == H264_PARAMETER_SET_TYPE_SPS ? 31 : 255;
        for( int i = ps_id + 1; i <= max_ps_id; i++ )
        {
            entry = h264_get_ps_entry_from_param( param, ps_type, i );
            if( entry )
                break;
        }
        if( entry )
            append_head = 1;
    }
    if( !entry )
        return;     /* The new entry was appended to the tail. */
    lsmash_entry_t *new_entry = ps_list->tail;
    if( append_head )
    {
        /* before: entry[i > ps_id] ... -> prev_entry -> new_entry[ps_id]
         * after:  new_entry[ps_id] -> entry[i > ps_id] -> ... -> prev_entry */
        if( new_entry->prev )
            new_entry->prev->next = NULL;
        new_entry->prev = NULL;
        entry->prev = new_entry;
        new_entry->next = entry;
        return;
    }
    /* before: entry[i < ps_id] -> next_entry -> ... -> prev_entry -> new_entry[ps_id]
     * after:  entry[i < ps_id] -> new_entry[ps_id] -> next_entry -> ... -> prev_entry */
    if( new_entry->prev )
        new_entry->prev->next = NULL;
    new_entry->prev = entry;
    new_entry->next = entry->next;
    if( entry->next )
        entry->next->prev = new_entry;
    entry->next = new_entry;
}

int lsmash_append_h264_parameter_set
(
    lsmash_h264_specific_parameters_t *param,
    lsmash_h264_parameter_set_type     ps_type,
    void                              *_ps_data,
    uint32_t                           ps_length
)
{
    uint8_t *ps_data = _ps_data;
    if( !param || !ps_data || ps_length < 2 )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( ps_type != H264_PARAMETER_SET_TYPE_SPS
     && ps_type != H264_PARAMETER_SET_TYPE_PPS
     && ps_type != H264_PARAMETER_SET_TYPE_SPSEXT )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !param->parameter_sets )
    {
        param->parameter_sets = h264_allocate_parameter_sets();
        if( !param->parameter_sets )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    lsmash_entry_list_t *ps_list = h264_get_parameter_set_list( param, ps_type );
    if( !ps_list )
        return LSMASH_ERR_NAMELESS;
    if( ps_type == H264_PARAMETER_SET_TYPE_SPSEXT )
    {
        if( !H264_REQUIRES_AVCC_EXTENSION( param->AVCProfileIndication ) )
            return 0;
        isom_dcr_ps_entry_t *ps = isom_create_ps_entry( ps_data, ps_length );
        if( !ps )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( ps_list, ps ) < 0 )
        {
            isom_remove_dcr_ps( ps );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        return 0;
    }
    /* Check if the same parameter set identifier already exists. */
    uint8_t ps_id;
    int err = h264_get_ps_id( ps_data + 1, ps_length - 1, &ps_id, ps_type );
    if( err < 0 )
        return err;
    lsmash_entry_t *entry = h264_get_ps_entry_from_param( param, ps_type, ps_id );
    isom_dcr_ps_entry_t *ps = entry ? (isom_dcr_ps_entry_t *)entry->data : NULL;
    if( ps && !ps->unused )
        /* The same parameter set identifier already exists. */
        return LSMASH_ERR_FUNCTION_PARAM;
    int invoke_reorder;
    if( ps )
    {
        /* Reuse an already existed parameter set in the list. */
        ps->unused = 0;
        if( ps->nalUnit != ps_data )
        {
            /* The same address could be given when called by h264_update_picture_info_for_slice(). */
            lsmash_free( ps->nalUnit );
            ps->nalUnit = ps_data;
        }
        ps->nalUnitLength = ps_length;
        invoke_reorder = 0;
    }
    else
    {
        /* Create a new parameter set and append it into the list. */
        ps = isom_create_ps_entry( ps_data, ps_length );
        if( !ps )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( ps_list, ps ) < 0 )
        {
            isom_remove_dcr_ps( ps );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        invoke_reorder = 1;
    }
    if( ps_type == H264_PARAMETER_SET_TYPE_SPS )
    {
        /* Update specific info with SPS. */
        lsmash_bits_t *bits = lsmash_bits_adhoc_create();
        if( !bits )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint8_t *rbsp_buffer = lsmash_malloc( ps_length );
        if( !rbsp_buffer )
        {
            lsmash_bits_adhoc_cleanup( bits );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        h264_sps_t sps;
        err = h264_parse_sps_minimally( bits, &sps, rbsp_buffer, ps_data + 1, ps_length - 1 );
        lsmash_bits_adhoc_cleanup( bits );
        lsmash_free( rbsp_buffer );
        if( err < 0 )
        {
            lsmash_list_remove_entry_tail( ps_list );
            return err;
        }
        if( ps_list->entry_count == 1 )
            param->profile_compatibility = 0xff;
        param->AVCProfileIndication    = sps.profile_idc;
        param->profile_compatibility  &= sps.constraint_set_flags;
        param->AVCLevelIndication      = LSMASH_MAX( param->AVCLevelIndication, sps.level_idc );
        param->chroma_format           = sps.chroma_format_idc;
        param->bit_depth_luma_minus8   = sps.bit_depth_luma_minus8;
        param->bit_depth_chroma_minus8 = sps.bit_depth_chroma_minus8;
    }
    if( invoke_reorder )
        /* Add a new parameter set in order of ascending parameter set identifier. */
        h264_reorder_parameter_set_ascending_id( param, ps_type, ps_list, ps_id );
    return 0;
}

int h264_try_to_append_parameter_set
(
    h264_info_t                   *info,
    lsmash_h264_parameter_set_type ps_type,
    void                          *_ps_data,
    uint32_t                       ps_length
)
{
    uint8_t *ps_data = _ps_data;
    lsmash_dcr_nalu_appendable ret = lsmash_check_h264_parameter_set_appendable( &info->avcC_param, ps_type, ps_data, ps_length );
    lsmash_h264_specific_parameters_t *param;
    switch( ret )
    {
        case DCR_NALU_APPEND_ERROR                     :    /* Error */
            return LSMASH_ERR_NAMELESS;
        case DCR_NALU_APPEND_NEW_DCR_REQUIRED          :    /* Mulitiple sample description is needed. */
        case DCR_NALU_APPEND_NEW_SAMPLE_ENTRY_REQUIRED :    /* Mulitiple sample description is needed. */
            param = &info->avcC_param_next;
            info->avcC_pending = 1;
            break;
        case DCR_NALU_APPEND_POSSIBLE :                     /* Appendable */
            param = info->avcC_pending ? &info->avcC_param_next : &info->avcC_param;
            break;
        default :   /* No need to append */
            return 0;
    }
    int err;
    switch( ps_type )
    {
        case H264_PARAMETER_SET_TYPE_SPS :
            if( (err = h264_parse_sps( info, info->buffer.rbsp, ps_data + 1, ps_length - 1 )) < 0 )
                return err;
            break;
        case H264_PARAMETER_SET_TYPE_PPS :
            if( (err = h264_parse_pps( info, info->buffer.rbsp, ps_data + 1, ps_length - 1 )) < 0 )
                return err;
            break;
        default :
            break;
    }
    return lsmash_append_h264_parameter_set( param, ps_type, ps_data, ps_length );
}

static inline int h264_move_dcr_nalu_entry
(
    lsmash_h264_specific_parameters_t *dst_data,
    lsmash_h264_specific_parameters_t *src_data,
    lsmash_h264_parameter_set_type     ps_type
)
{
    lsmash_entry_list_t *src_ps_list = h264_get_parameter_set_list( src_data, ps_type );
    lsmash_entry_list_t *dst_ps_list = h264_get_parameter_set_list( dst_data, ps_type );
    assert( src_ps_list && dst_ps_list );
    for( lsmash_entry_t *src_entry = src_ps_list->head; src_entry; src_entry = src_entry->next )
    {
        isom_dcr_ps_entry_t *src_ps = (isom_dcr_ps_entry_t *)src_entry->data;
        if( !src_ps )
            continue;
        int err;
        uint8_t src_ps_id;
        if( (err = h264_get_ps_id( src_ps->nalUnit + 1, src_ps->nalUnitLength - 1, &src_ps_id, ps_type )) < 0 )
            return err;
        lsmash_entry_t *dst_entry;
        for( dst_entry = dst_ps_list->head; dst_entry; dst_entry = dst_entry->next )
        {
            isom_dcr_ps_entry_t *dst_ps = (isom_dcr_ps_entry_t *)dst_entry->data;
            if( !dst_ps )
                continue;
            uint8_t dst_ps_id;
            if( (err = h264_get_ps_id( dst_ps->nalUnit + 1, dst_ps->nalUnitLength - 1, &dst_ps_id, ps_type )) < 0 )
                return err;
            if( dst_ps_id == src_ps_id )
            {
                /* Replace the old parameter set with the new one. */
                assert( dst_entry->data != src_entry->data );
                isom_remove_dcr_ps( dst_ps );
                dst_entry->data = src_entry->data;
                src_entry->data = NULL;
                break;
            }
        }
        if( !dst_entry )
        {
            /* Move the parameter set. */
            if( lsmash_list_add_entry( dst_ps_list, src_ps ) < 0 )
                return LSMASH_ERR_MEMORY_ALLOC;
            src_entry->data = NULL;
        }
    }
    return 0;
}

int h264_move_pending_avcC_param
(
    h264_info_t *info
)
{
    assert( info );
    if( !info->avcC_pending )
        return 0;
    /* Mark 'unused' on parameter sets within the decoder configuration record. */
    for( int i = 0; i < H264_PARAMETER_SET_TYPE_NUM; i++ )
    {
        lsmash_entry_list_t *ps_list = h264_get_parameter_set_list( &info->avcC_param, i );
        assert( ps_list );
        for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
        {
            isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
            if( !ps )
                continue;
            ps->unused = 1;
        }
    }
    /* Move the new parameter sets. */
    int err;
    if( (err = h264_move_dcr_nalu_entry( &info->avcC_param, &info->avcC_param_next, H264_PARAMETER_SET_TYPE_SPS )) < 0
     || (err = h264_move_dcr_nalu_entry( &info->avcC_param, &info->avcC_param_next, H264_PARAMETER_SET_TYPE_PPS )) < 0 )
        return err;
    /* Move to the pending. */
    lsmash_h264_parameter_sets_t *parameter_sets = info->avcC_param.parameter_sets; /* Back up parameter sets. */
    info->avcC_param                = info->avcC_param_next;
    info->avcC_param.parameter_sets = parameter_sets;
    /* No pending avcC. */
    h264_deallocate_parameter_sets( &info->avcC_param_next );
    uint8_t lengthSizeMinusOne = info->avcC_param_next.lengthSizeMinusOne;
    memset( &info->avcC_param_next, 0, sizeof(lsmash_h264_specific_parameters_t) );
    info->avcC_param_next.lengthSizeMinusOne = lengthSizeMinusOne;
    info->avcC_pending = 0;
    return 0;
}

static int h264_parse_succeeded
(
    h264_info_t                       *info,
    lsmash_h264_specific_parameters_t *param
)
{
    int ret;
    if( info->sps.present && info->pps.present )
    {
        *param = info->avcC_param;
        /* Avoid freeing parameter sets. */
        info->avcC_param.parameter_sets = NULL;
        ret = 0;
    }
    else
        ret = LSMASH_ERR_INVALID_DATA;
    h264_cleanup_parser( info );
    return ret;
}

static inline int h264_parse_failed
(
    h264_info_t *info,
    int          ret
)
{
    h264_cleanup_parser( info );
    return ret;
}

int lsmash_setup_h264_specific_parameters_from_access_unit
(
    lsmash_h264_specific_parameters_t *param,
    uint8_t                           *data,
    uint32_t                           data_length
)
{
    if( !param || !data || data_length == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    h264_info_t *info = &(h264_info_t){ { 0 } };
    lsmash_bs_t *bs   = &(lsmash_bs_t){ 0 };
    int err = lsmash_bs_set_empty_stream( bs, data, data_length );
    if( err < 0 )
        return err;
    uint64_t sc_head_pos = nalu_find_first_start_code( bs );
    if( sc_head_pos == NALU_NO_START_CODE_FOUND )
        return LSMASH_ERR_INVALID_DATA;
    else if( sc_head_pos == NALU_IO_ERROR )
        return LSMASH_ERR_IO;
    if( (err = h264_setup_parser( info, 1 )) < 0 )
        return h264_parse_failed( info, err );
    h264_stream_buffer_t *sb    = &info->buffer;
    h264_slice_info_t    *slice = &info->slice;
    while( 1 )
    {
        h264_nalu_header_t nuh;
        uint64_t start_code_length;
        uint64_t trailing_zero_bytes;
        uint64_t nalu_length = h264_find_next_start_code( bs, &nuh, &start_code_length, &trailing_zero_bytes );
        if( nalu_length == NALU_NO_START_CODE_FOUND )
            /* For the last NALU. This NALU already has been parsed. */
            return h264_parse_succeeded( info, param );
        uint8_t  nalu_type        = nuh.nal_unit_type;
        uint64_t next_sc_head_pos = sc_head_pos
                                  + start_code_length
                                  + nalu_length
                                  + trailing_zero_bytes;
        if( nalu_type == H264_NALU_TYPE_FD )
        {
            /* We don't support streams with both filler and HRD yet.
             * Otherwise, just skip filler because elemental streams defined in 14496-15 are forbidden to use filler. */
            if( info->sps.vui.hrd.present )
                return h264_parse_failed( info, LSMASH_ERR_PATCH_WELCOME );
        }
        else if( (nalu_type >= H264_NALU_TYPE_SLICE_N_IDR && nalu_type <= H264_NALU_TYPE_SPS_EXT)
              || nalu_type == H264_NALU_TYPE_SLICE_AUX )
        {
            /* Increase the buffer if needed. */
            uint64_t possible_au_length = NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
            if( sb->bank->buffer_size < possible_au_length
             && (err = h264_supplement_buffer( sb, NULL, 2 * possible_au_length )) < 0 )
                return h264_parse_failed( info, err );
            /* Get the EBSP of the current NALU here.
             * AVC elemental stream defined in 14496-15 can recognize from 0 to 13, and 19 of nal_unit_type.
             * We don't support SVC and MVC elemental stream defined in 14496-15 yet. */
            uint8_t *nalu = lsmash_bs_get_buffer_data( bs ) + start_code_length;
            if( nalu_type >= H264_NALU_TYPE_SLICE_N_IDR && nalu_type <= H264_NALU_TYPE_SLICE_IDR )
            {
                /* VCL NALU (slice) */
                h264_slice_info_t prev_slice = *slice;
                if( (err = h264_parse_slice( info, &nuh, sb->rbsp, nalu + nuh.length, nalu_length - nuh.length )) < 0 )
                    return h264_parse_failed( info, err );
                if( prev_slice.present )
                {
                    /* Check whether the AU that contains the previous VCL NALU completed or not. */
                    if( h264_find_au_delimit_by_slice_info( slice, &prev_slice ) )
                        /* The current NALU is the first VCL NALU of the primary coded picture of an new AU.
                         * Therefore, the previous slice belongs to that new AU. */
                        return h264_parse_succeeded( info, param );
                }
                slice->present = 1;
            }
            else
            {
                if( h264_find_au_delimit_by_nalu_type( nalu_type, info->prev_nalu_type ) )
                    /* The last slice belongs to the AU you want at this time. */
                    return h264_parse_succeeded( info, param );
                switch( nalu_type )
                {
                    case H264_NALU_TYPE_SPS :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_SPS, nalu, nalu_length )) < 0 )
                            return h264_parse_failed( info, err );
                        break;
                    case H264_NALU_TYPE_PPS :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_PPS, nalu, nalu_length )) < 0 )
                            return h264_parse_failed( info, err );
                        break;
                    case H264_NALU_TYPE_SPS_EXT :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_SPSEXT, nalu, nalu_length )) < 0 )
                            return h264_parse_failed( info, err );
                        break;
                    default :
                        break;
                }
            }
        }
        /* Move to the first byte of the next start code. */
        info->prev_nalu_type = nalu_type;
        if( lsmash_bs_read_seek( bs, next_sc_head_pos, SEEK_SET ) != next_sc_head_pos )
            return h264_parse_failed( info, LSMASH_ERR_NAMELESS );
        /* Check if no more data to read from the stream. */
        if( !lsmash_bs_is_end( bs, NALU_SHORT_START_CODE_LENGTH ) )
            sc_head_pos = next_sc_head_pos;
        else
            return h264_parse_succeeded( info, param );
    }
}

int h264_construct_specific_parameters
(
    lsmash_codec_specific_t *dst,
    lsmash_codec_specific_t *src
)
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < ISOM_BASEBOX_COMMON_SIZE + 7 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_h264_specific_parameters_t *param = (lsmash_h264_specific_parameters_t *)dst->data.structured;
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
    if( !param->parameter_sets )
    {
        param->parameter_sets = h264_allocate_parameter_sets();
        if( !param->parameter_sets )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = lsmash_bs_import_data( bs, data, src->size - (data - src->data.unstructured) );
    if( err < 0 )
        goto fail;
    if( lsmash_bs_get_byte( bs ) != 1 )
    {
        /* We don't support configurationVersion other than 1. */
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    param->AVCProfileIndication  = lsmash_bs_get_byte( bs );
    param->profile_compatibility = lsmash_bs_get_byte( bs );
    param->AVCLevelIndication    = lsmash_bs_get_byte( bs );
    param->lengthSizeMinusOne    = lsmash_bs_get_byte( bs ) & 0x03;
    uint8_t numOfSequenceParameterSets = lsmash_bs_get_byte( bs ) & 0x1F;
    if( numOfSequenceParameterSets
     && (err = nalu_get_dcr_ps( bs, param->parameter_sets->sps_list, numOfSequenceParameterSets )) < 0 )
        goto fail;
    uint8_t numOfPictureParameterSets = lsmash_bs_get_byte( bs );
    if( numOfPictureParameterSets
     && (err = nalu_get_dcr_ps( bs, param->parameter_sets->pps_list, numOfPictureParameterSets )) < 0 )
        goto fail;
    if( H264_REQUIRES_AVCC_EXTENSION( param->AVCProfileIndication ) )
    {
        param->chroma_format           = lsmash_bs_get_byte( bs ) & 0x03;
        param->bit_depth_luma_minus8   = lsmash_bs_get_byte( bs ) & 0x07;
        param->bit_depth_chroma_minus8 = lsmash_bs_get_byte( bs ) & 0x07;
        uint8_t numOfSequenceParameterSetExt = lsmash_bs_get_byte( bs );
        if( numOfSequenceParameterSetExt
         && (err = nalu_get_dcr_ps( bs, param->parameter_sets->spsext_list, numOfSequenceParameterSetExt )) < 0 )
            goto fail;
    }
    lsmash_bs_cleanup( bs );
    return 0;
fail:
    lsmash_bs_cleanup( bs );
    return err;
}

int h264_print_codec_specific
(
    FILE          *fp,
    lsmash_file_t *file,
    isom_box_t    *box,
    int            level
)
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: AVC Configuration Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    uint8_t     *data   = box->binary;
    uint32_t     offset = isom_skip_box_common( &data );
    lsmash_bs_t *bs     = lsmash_bs_create();
    if( !bs )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = lsmash_bs_import_data( bs, data, box->size - offset );
    if( err < 0 )
    {
        lsmash_bs_cleanup( bs );
        return err;
    }
    lsmash_ifprintf( fp, indent, "configurationVersion = %"PRIu8"\n", lsmash_bs_get_byte( bs ) );
    uint8_t AVCProfileIndication = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "AVCProfileIndication = %"PRIu8"\n", AVCProfileIndication );
    lsmash_ifprintf( fp, indent, "profile_compatibility = 0x%02"PRIx8"\n", lsmash_bs_get_byte( bs ) );
    lsmash_ifprintf( fp, indent, "AVCLevelIndication = %"PRIu8"\n", lsmash_bs_get_byte( bs ) );
    uint8_t temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", (temp8 >> 2) & 0x3F );
    lsmash_ifprintf( fp, indent, "lengthSizeMinusOne = %"PRIu8"\n", temp8 & 0x03 );
    temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", (temp8 >> 5) & 0x07 );
    uint8_t numOfSequenceParameterSets = temp8 & 0x1f;
    lsmash_ifprintf( fp, indent, "numOfSequenceParameterSets = %"PRIu8"\n", numOfSequenceParameterSets );
    for( uint8_t i = 0; i < numOfSequenceParameterSets; i++ )
    {
        uint16_t nalUnitLength = lsmash_bs_get_be16( bs );
        lsmash_bs_skip_bytes( bs, nalUnitLength );
    }
    uint8_t numOfPictureParameterSets = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "numOfPictureParameterSets = %"PRIu8"\n", numOfPictureParameterSets );
    for( uint8_t i = 0; i < numOfPictureParameterSets; i++ )
    {
        uint16_t nalUnitLength = lsmash_bs_get_be16( bs );
        lsmash_bs_skip_bytes( bs, nalUnitLength );
    }
    /* Note: there are too many files, in the world, that don't contain the following fields. */
    if( H264_REQUIRES_AVCC_EXTENSION( AVCProfileIndication )
     && (lsmash_bs_get_pos( bs ) < (box->size - offset)) )
    {
        temp8 = lsmash_bs_get_byte( bs );
        lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", (temp8 >> 2) & 0x3F );
        lsmash_ifprintf( fp, indent, "chroma_format = %"PRIu8"\n", temp8 & 0x03 );
        temp8 = lsmash_bs_get_byte( bs );
        lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", (temp8 >> 3) & 0x1F );
        lsmash_ifprintf( fp, indent, "bit_depth_luma_minus8 = %"PRIu8"\n", temp8 & 0x7 );
        temp8 = lsmash_bs_get_byte( bs );
        lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", (temp8 >> 3) & 0x1F );
        lsmash_ifprintf( fp, indent, "bit_depth_chroma_minus8 = %"PRIu8"\n", temp8 & 0x7 );
        lsmash_ifprintf( fp, indent, "numOfSequenceParameterSetExt = %"PRIu8"\n", lsmash_bs_get_byte( bs ) );
    }
    lsmash_bs_cleanup( bs );
    return 0;
}

int h264_copy_codec_specific
(
    lsmash_codec_specific_t *dst,
    lsmash_codec_specific_t *src
)
{
    assert( src && src->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && src->data.structured );
    assert( dst && dst->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && dst->data.structured );
    lsmash_h264_specific_parameters_t *src_data = (lsmash_h264_specific_parameters_t *)src->data.structured;
    lsmash_h264_specific_parameters_t *dst_data = (lsmash_h264_specific_parameters_t *)dst->data.structured;
    h264_deallocate_parameter_sets( dst_data );
    *dst_data = *src_data;
    if( !src_data->parameter_sets )
        return 0;
    dst_data->parameter_sets = h264_allocate_parameter_sets();
    if( !dst_data->parameter_sets )
        return LSMASH_ERR_MEMORY_ALLOC;
    for( int i = 0; i < 3; i++ )
    {
        lsmash_entry_list_t *src_ps_list = h264_get_parameter_set_list( src_data, i );
        lsmash_entry_list_t *dst_ps_list = h264_get_parameter_set_list( dst_data, i );
        assert( src_ps_list && dst_ps_list );
        for( lsmash_entry_t *entry = src_ps_list->head; entry; entry = entry->next )
        {
            isom_dcr_ps_entry_t *src_ps = (isom_dcr_ps_entry_t *)entry->data;
            if( !src_ps || src_ps->unused )
                continue;
            isom_dcr_ps_entry_t *dst_ps = isom_create_ps_entry( src_ps->nalUnit, src_ps->nalUnitLength );
            if( !dst_ps )
            {
                h264_deallocate_parameter_sets( dst_data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            if( lsmash_list_add_entry( dst_ps_list, dst_ps ) < 0 )
            {
                h264_deallocate_parameter_sets( dst_data );
                isom_remove_dcr_ps( dst_ps );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
    }
    return 0;
}

int h264_print_bitrate
(
    FILE          *fp,
    lsmash_file_t *file,
    isom_box_t    *box,
    int            level
)
{
    assert( fp && LSMASH_IS_EXISTING_BOX( file ) && LSMASH_IS_EXISTING_BOX( box ) );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: MPEG-4 Bit Rate Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    isom_btrt_t *btrt = (isom_btrt_t *)box;
    lsmash_ifprintf( fp, indent, "bufferSizeDB = %"PRIu32"\n", btrt->bufferSizeDB );
    lsmash_ifprintf( fp, indent, "maxBitrate = %"PRIu32"\n", btrt->maxBitrate );
    lsmash_ifprintf( fp, indent, "avgBitrate = %"PRIu32"\n", btrt->avgBitrate );
    return 0;
}

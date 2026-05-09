/*****************************************************************************
 * hevc.c
 *****************************************************************************
 * Copyright (C) 2013-2017 L-SMASH project
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
    ITU-T Recommendation H.265 (04/13)
    ISO/IEC 14496-15:2014
***************************************************************************/
#include "hevc.h"
#include "nalu.h"

#define IF_EXCEED_INT32( x ) if( (x) < INT32_MIN || (x) > INT32_MAX )
#define HEVC_POC_DEBUG_PRINT 0

#define HEVC_MIN_NALU_HEADER_LENGTH 2
#define HEVC_MAX_VPS_ID             15
#define HEVC_MAX_SPS_ID             15
#define HEVC_MAX_PPS_ID             63
#define HEVC_MAX_DPB_SIZE           16
#define HVCC_CONFIGURATION_VERSION  1

typedef enum
{
    HEVC_SLICE_TYPE_B = 0,
    HEVC_SLICE_TYPE_P = 1,
    HEVC_SLICE_TYPE_I = 2,
} hevc_slice_type;

static lsmash_hevc_parameter_arrays_t *hevc_alloc_parameter_arrays( void )
{
    lsmash_hevc_parameter_arrays_t *parameter_arrays = lsmash_malloc_zero( sizeof(lsmash_hevc_parameter_arrays_t) );
    if( !parameter_arrays )
        return NULL;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_VPS       ].array_completeness = 1;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_VPS       ].NAL_unit_type      = HEVC_NALU_TYPE_VPS;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SPS       ].array_completeness = 1;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SPS       ].NAL_unit_type      = HEVC_NALU_TYPE_SPS;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PPS       ].array_completeness = 1;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PPS       ].NAL_unit_type      = HEVC_NALU_TYPE_PPS;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PREFIX_SEI].array_completeness = 0;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PREFIX_SEI].NAL_unit_type      = HEVC_NALU_TYPE_PREFIX_SEI;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SUFFIX_SEI].array_completeness = 0;
    parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SUFFIX_SEI].NAL_unit_type      = HEVC_NALU_TYPE_SUFFIX_SEI;
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
        lsmash_list_init( parameter_arrays->ps_array[i].list, isom_remove_dcr_ps );
    return parameter_arrays;
}

static int hevc_alloc_parameter_arrays_if_needed
(
    lsmash_hevc_specific_parameters_t *param
)
{
    assert( param );
    if( param->parameter_arrays )
        return 0;
    lsmash_hevc_parameter_arrays_t *parameter_arrays = hevc_alloc_parameter_arrays();
    if( !parameter_arrays )
        return LSMASH_ERR_MEMORY_ALLOC;
    param->parameter_arrays = parameter_arrays;
    return 0;
}

static void hevc_deallocate_parameter_arrays
(
    lsmash_hevc_specific_parameters_t *param
)
{
    if( !param || !param->parameter_arrays )
        return;
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
        lsmash_list_remove_entries( param->parameter_arrays->ps_array[i].list );
    lsmash_freep( &param->parameter_arrays );
}

void lsmash_destroy_hevc_parameter_arrays
(
    lsmash_hevc_specific_parameters_t *param
)
{
    hevc_deallocate_parameter_arrays( param );
}

void hevc_destruct_specific_data
(
    void *data
)
{
    if( !data )
        return;
    hevc_deallocate_parameter_arrays( data );
    lsmash_free( data );
}

static void hevc_remove_pps
(
    hevc_pps_t *pps
)
{
    if( !pps )
        return;
    lsmash_free( pps->colWidth );
    lsmash_free( pps->rowHeight );
    lsmash_free( pps );
}

void hevc_cleanup_parser
(
    hevc_info_t *info
)
{
    if( !info )
        return;
    lsmash_list_remove_entries( info->vps_list );
    lsmash_list_remove_entries( info->sps_list );
    lsmash_list_remove_entries( info->pps_list );
    hevc_deallocate_parameter_arrays( &info->hvcC_param );
    hevc_deallocate_parameter_arrays( &info->hvcC_param_next );
    lsmash_destroy_multiple_buffers( info->buffer.bank );
    lsmash_bits_adhoc_cleanup( info->bits );
    info->bits = NULL;
}

int hevc_setup_parser
(
    hevc_info_t *info,
    int          parse_only
)
{
    assert( info );
    memset( info, 0, sizeof(hevc_info_t) );
    info->hvcC_param     .lengthSizeMinusOne = NALU_DEFAULT_NALU_LENGTH_SIZE - 1;
    info->hvcC_param_next.lengthSizeMinusOne = NALU_DEFAULT_NALU_LENGTH_SIZE - 1;
    hevc_stream_buffer_t *sb = &info->buffer;
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
    lsmash_list_init_simple( info->vps_list );
    lsmash_list_init_simple( info->sps_list );
    lsmash_list_init( info->pps_list, hevc_remove_pps );
    info->prev_nalu_type = HEVC_NALU_TYPE_UNKNOWN;
    return 0;
}

static int hevc_check_nalu_header
(
    lsmash_bs_t        *bs,
    hevc_nalu_header_t *nuh,
    int                 use_long_start_code
)
{
    /* Check if the enough length of NALU header on the buffer. */
    int start_code_length = use_long_start_code ? NALU_LONG_START_CODE_LENGTH : NALU_SHORT_START_CODE_LENGTH;
    if( lsmash_bs_is_end( bs, start_code_length + 1 ) )
        return LSMASH_ERR_NAMELESS;
    /* Read NALU header. */
    uint16_t temp16 = lsmash_bs_show_be16( bs, start_code_length );
    nuh->forbidden_zero_bit       = (temp16 >> 15) & 0x01;
    nuh->nal_unit_type            = (temp16 >>  9) & 0x3f;
    nuh->nuh_layer_id             = (temp16 >>  3) & 0x3f;
    uint8_t nuh_temporal_id_plus1 =  temp16        & 0x07;
    if( nuh->forbidden_zero_bit || nuh_temporal_id_plus1 == 0 )
        return LSMASH_ERR_INVALID_DATA;
    nuh->TemporalId = nuh_temporal_id_plus1 - 1;
    nuh->length     = HEVC_MIN_NALU_HEADER_LENGTH;
    /* nuh_layer_id shall be 0 in the specification we refer to. */
    if( nuh->nuh_layer_id )
        return LSMASH_ERR_NAMELESS;
    if( nuh->TemporalId == 0 )
    {
        /* For TSA_N, TSA_R, STSA_N and STSA_R, TemporalId shall not be equal to 0. */
        if( nuh->nal_unit_type >= HEVC_NALU_TYPE_TSA_N
         && nuh->nal_unit_type <= HEVC_NALU_TYPE_STSA_R )
            return LSMASH_ERR_INVALID_DATA;
    }
    else
    {
        /* For BLA_W_LP to RSV_IRAP_VCL23, TemporalId shall be equal to 0. */
        if( nuh->nal_unit_type >= HEVC_NALU_TYPE_BLA_W_LP
         && nuh->nal_unit_type <= HEVC_NALU_TYPE_RSV_IRAP_VCL23 )
            return LSMASH_ERR_INVALID_DATA;
        /* For VPS, SPS, EOS and EOB, TemporalId shall be equal to 0. */
        if( nuh->nal_unit_type >= HEVC_NALU_TYPE_VPS
         && nuh->nal_unit_type <= HEVC_NALU_TYPE_EOB
         && nuh->nal_unit_type != HEVC_NALU_TYPE_PPS
         && nuh->nal_unit_type != HEVC_NALU_TYPE_AUD )
            return LSMASH_ERR_INVALID_DATA;
    }
    /* VPS, SPS and PPS require long start code (0x00000001).
     * Also AU delimiter requires it too because this type of NALU shall be the first NALU of any AU if present. */
    if( !use_long_start_code
     && nuh->nal_unit_type >= HEVC_NALU_TYPE_VPS
     && nuh->nal_unit_type <= HEVC_NALU_TYPE_AUD )
        return LSMASH_ERR_INVALID_DATA;
    return 0;
}

uint64_t hevc_find_next_start_code
(
    lsmash_bs_t        *bs,
    hevc_nalu_header_t *nuh,
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
    if( long_start_code >= 0 && hevc_check_nalu_header( bs, nuh, long_start_code ) == 0 )
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
        nuh->nal_unit_type      = HEVC_NALU_TYPE_UNKNOWN;
        nuh->nuh_layer_id       = 0;    /* arbitrary */
        nuh->TemporalId         = 0;    /* arbitrary */
        nuh->length             = 0;
        *start_code_length = 0;
        length = NALU_NO_START_CODE_FOUND;
    }
    *trailing_zero_bytes = count;
    return length;
}

static hevc_vps_t *hevc_get_vps
(
    lsmash_entry_list_t *vps_list,
    uint8_t              vps_id
)
{
    if( !vps_list || vps_id > HEVC_MAX_VPS_ID )
        return NULL;
    for( lsmash_entry_t *entry = vps_list->head; entry; entry = entry->next )
    {
        hevc_vps_t *vps = (hevc_vps_t *)entry->data;
        if( !vps )
            return NULL;
        if( vps->video_parameter_set_id == vps_id )
            return vps;
    }
    hevc_vps_t *vps = lsmash_malloc_zero( sizeof(hevc_vps_t) );
    if( !vps )
        return NULL;
    vps->video_parameter_set_id = vps_id;
    if( lsmash_list_add_entry( vps_list, vps ) < 0 )
    {
        lsmash_free( vps );
        return NULL;
    }
    return vps;
}

static hevc_sps_t *hevc_get_sps
(
    lsmash_entry_list_t *sps_list,
    uint8_t              sps_id
)
{
    if( !sps_list || sps_id > HEVC_MAX_SPS_ID )
        return NULL;
    for( lsmash_entry_t *entry = sps_list->head; entry; entry = entry->next )
    {
        hevc_sps_t *sps = (hevc_sps_t *)entry->data;
        if( !sps )
            return NULL;
        if( sps->seq_parameter_set_id == sps_id )
            return sps;
    }
    hevc_sps_t *sps = lsmash_malloc_zero( sizeof(hevc_sps_t) );
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

static hevc_pps_t *hevc_get_pps
(
    lsmash_entry_list_t *pps_list,
    uint8_t              pps_id
)
{
    if( !pps_list || pps_id > HEVC_MAX_PPS_ID )
        return NULL;
    for( lsmash_entry_t *entry = pps_list->head; entry; entry = entry->next )
    {
        hevc_pps_t *pps = (hevc_pps_t *)entry->data;
        if( !pps )
            return NULL;
        if( pps->pic_parameter_set_id == pps_id )
            return pps;
    }
    hevc_pps_t *pps = lsmash_malloc_zero( sizeof(hevc_pps_t) );
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

int hevc_calculate_poc
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_picture_info_t *prev_picture
)
{
#if HEVC_POC_DEBUG_PRINT
    fprintf( stderr, "PictureOrderCount\n" );
#endif
    hevc_pps_t *pps = hevc_get_pps( info->pps_list, picture->pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    hevc_sps_t *sps = hevc_get_sps( info->sps_list, pps->seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    /* 8.3.1 Decoding process for picture order count
     * This process needs to be invoked only for the first slice segment of a picture. */
    int NoRaslOutputFlag;
    if( picture->irap )
    {
        /* 8.1 General decoding process
         * If the current picture is an IDR picture, a BLA picture, the first picture in the
         * bitstream in decoding order, or the first picture that follows an end of sequence
         * NAL unit in decoding order, the variable NoRaslOutputFlag is set equal to 1.
         *
         * Note that not only the end of sequence NAL unit but the end of bistream NAL unit as
         * well specify that the current access unit is the last access unit in the coded video
         * sequence in decoding order. */
        NoRaslOutputFlag = picture->idr || picture->broken_link || info->eos;
        if( info->eos )
            info->eos = 0;
    }
    else
        NoRaslOutputFlag = 0;
    int64_t poc_msb;
    int32_t poc_lsb = picture->poc_lsb;
    if( picture->irap && NoRaslOutputFlag )
        poc_msb = 0;
    else
    {
        int32_t prev_poc_msb = picture->idr ? 0 : prev_picture->tid0_poc_msb;
        int32_t prev_poc_lsb = picture->idr ? 0 : prev_picture->tid0_poc_lsb;
        int32_t max_poc_lsb  = 1 << sps->log2_max_pic_order_cnt_lsb;
        if( (poc_lsb < prev_poc_lsb)
         && ((prev_poc_lsb - poc_lsb) >= (max_poc_lsb / 2)) )
            poc_msb = prev_poc_msb + max_poc_lsb;
        else if( (poc_lsb > prev_poc_lsb)
         && ((poc_lsb - prev_poc_lsb) > (max_poc_lsb / 2)) )
            poc_msb = prev_poc_msb - max_poc_lsb;
        else
            poc_msb = prev_poc_msb;
    }
    picture->poc = poc_msb + poc_lsb;
    if( picture->TemporalId == 0 && (!picture->radl || !picture->rasl || !picture->sublayer_nonref) )
    {
        picture->tid0_poc_msb = poc_msb;
        picture->tid0_poc_lsb = poc_lsb;
    }
#if HEVC_POC_DEBUG_PRINT
    fprintf( stderr, "    prevPicOrderCntMsb: %"PRId32"\n", prev_poc_msb );
    fprintf( stderr, "    prevPicOrderCntLsb: %"PRId32"\n", prev_poc_lsb );
    fprintf( stderr, "    PicOrderCntMsb: %"PRId64"\n",     poc_msb );
    fprintf( stderr, "    pic_order_cnt_lsb: %"PRId32"\n",  poc_lsb );
    fprintf( stderr, "    MaxPicOrderCntLsb: %"PRIu64"\n",  max_poc_lsb );
    fprintf( stderr, "    POC: %"PRId32"\n", picture->poc );
#endif
    return 0;
}

static inline int hevc_activate_vps
(
    hevc_info_t *info,
    uint8_t      video_parameter_set_id
)
{
    hevc_vps_t *vps = hevc_get_vps( info->vps_list, video_parameter_set_id );
    if( !vps )
        return LSMASH_ERR_NAMELESS;
    info->vps = *vps;
    return 0;
}

static inline int hevc_activate_sps
(
    hevc_info_t *info,
    uint8_t      seq_parameter_set_id
)
{
    hevc_sps_t *sps = hevc_get_sps( info->sps_list, seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    info->sps = *sps;
    return 0;
}

static void hevc_parse_scaling_list_data
(
    lsmash_bits_t *bits
)
{
    for( int sizeId = 0; sizeId < 4; sizeId++ )
        for( int matrixId = 0; matrixId < (sizeId == 3 ? 2 : 6); matrixId++ )
        {
            if( !lsmash_bits_get( bits, 1 ) )       /* scaling_list_pred_mode_flag[sizeId][matrixId] */
                nalu_get_exp_golomb_ue( bits );     /* scaling_list_pred_matrix_id_delta[sizeId][matrixId] */
            else
            {
                int coefNum = LSMASH_MIN( 64, 1 << (4 + (sizeId << 1)) );
                if( sizeId > 1 )
                    nalu_get_exp_golomb_se( bits ); /* scaling_list_dc_coef_minus8[sizeId - 2][matrixId] */
                for( int i = 0; i < coefNum; i++ )
                    nalu_get_exp_golomb_se( bits ); /* scaling_list_delta_coef */
            }
        }
}

static int hevc_short_term_ref_pic_set
(
    lsmash_bits_t *bits,
    hevc_sps_t    *sps,
    int            stRpsIdx
)
{
    int inter_ref_pic_set_prediction_flag = stRpsIdx != 0 ? lsmash_bits_get( bits, 1 ) : 0;
    if( inter_ref_pic_set_prediction_flag )
    {
        /* delta_idx_minus1 is always 0 in SPS since stRpsIdx must not be equal to num_short_term_ref_pic_sets. */
        uint64_t delta_idx_minus1     = stRpsIdx == sps->num_short_term_ref_pic_sets ? nalu_get_exp_golomb_ue( bits ) : 0;
        int      delta_rps_sign       = lsmash_bits_get( bits, 1 );
        uint64_t abs_delta_rps_minus1 = nalu_get_exp_golomb_ue( bits );
        int RefRpsIdx = stRpsIdx - (delta_idx_minus1 + 1);
        int deltaRps  = (delta_rps_sign ? -1 : 1) * (abs_delta_rps_minus1 + 1);
        hevc_st_rps_t *st_rps  = &sps->st_rps[stRpsIdx];
        hevc_st_rps_t *ref_rps = &sps->st_rps[RefRpsIdx];
        uint8_t used_by_curr_pic_flag[32];
        uint8_t use_delta_flag       [32];
        for( int j = 0; j <= ref_rps->NumDeltaPocs; j++ )
        {
            used_by_curr_pic_flag[j] = lsmash_bits_get( bits, 1 );
            use_delta_flag       [j] = !used_by_curr_pic_flag[j] ? lsmash_bits_get( bits, 1 ) : 1;
        }
        /* NumNegativePics */
        int i = 0;
        for( int j = ref_rps->NumPositivePics - 1; j >= 0; j-- )
        {
            int dPoc = ref_rps->DeltaPocS1[j] + deltaRps;
            if( dPoc < 0 && use_delta_flag[ ref_rps->NumNegativePics + j ] )
            {
                st_rps->DeltaPocS0     [i  ] = dPoc;
                st_rps->UsedByCurrPicS0[i++] = used_by_curr_pic_flag[ ref_rps->NumNegativePics + j ];
            }
        }
        if( deltaRps < 0 && use_delta_flag[ ref_rps->NumDeltaPocs ] )
        {
            st_rps->DeltaPocS0     [i  ] = deltaRps;
            st_rps->UsedByCurrPicS0[i++] = used_by_curr_pic_flag[ ref_rps->NumDeltaPocs ];
        }
        for( int j = 0; j < ref_rps->NumNegativePics; j++ )
        {
            int dPoc = ref_rps->DeltaPocS0[j] + deltaRps;
            if( dPoc < 0 && use_delta_flag[j] )
            {
                st_rps->DeltaPocS0     [i  ] = dPoc;
                st_rps->UsedByCurrPicS0[i++] = used_by_curr_pic_flag[j];
            }
        }
        st_rps->NumNegativePics = i;
        /* NumPositivePics */
        i = 0;
        for( int j = ref_rps->NumNegativePics - 1; j >= 0; j-- )
        {
            int dPoc = ref_rps->DeltaPocS0[j] + deltaRps;
            if( dPoc > 0 && use_delta_flag[j] )
            {
                st_rps->DeltaPocS1     [i  ] = dPoc;
                st_rps->UsedByCurrPicS1[i++] = used_by_curr_pic_flag[j];
            }
        }
        if( deltaRps > 0 && use_delta_flag[ ref_rps->NumDeltaPocs ] )
        {
            st_rps->DeltaPocS1     [i  ] = deltaRps;
            st_rps->UsedByCurrPicS1[i++] = used_by_curr_pic_flag[ ref_rps->NumDeltaPocs ];
        }
        for( int j = 0; j < ref_rps->NumPositivePics; j++ )
        {
            int dPoc = ref_rps->DeltaPocS1[j] + deltaRps;
            if( dPoc > 0 && use_delta_flag[ ref_rps->NumNegativePics + j ] )
            {
                st_rps->DeltaPocS1     [i  ] = dPoc;
                st_rps->UsedByCurrPicS1[i++] = used_by_curr_pic_flag[ ref_rps->NumNegativePics + j ];
            }
        }
        st_rps->NumPositivePics = i;
        /* NumDeltaPocs */
        st_rps->NumDeltaPocs = st_rps->NumNegativePics + st_rps->NumPositivePics;
    }
    else
    {
        uint64_t num_negative_pics = nalu_get_exp_golomb_ue( bits );
        uint64_t num_positive_pics = nalu_get_exp_golomb_ue( bits );
        if( num_negative_pics >= HEVC_MAX_DPB_SIZE || num_positive_pics >= HEVC_MAX_DPB_SIZE )
            return LSMASH_ERR_INVALID_DATA;
        hevc_st_rps_t *st_rps = &sps->st_rps[stRpsIdx];
        st_rps->NumNegativePics = num_negative_pics;
        st_rps->NumPositivePics = num_positive_pics;
        st_rps->NumDeltaPocs    = st_rps->NumNegativePics + st_rps->NumPositivePics;
        for( int i = 0; i < num_negative_pics; i++ )
        {
            uint64_t delta_poc_s0_minus1 = nalu_get_exp_golomb_ue( bits );
            if( i == 0 )
                st_rps->DeltaPocS0[i] = -(signed)(delta_poc_s0_minus1 + 1);
            else
                st_rps->DeltaPocS0[i] = st_rps->DeltaPocS0[i - 1] - (delta_poc_s0_minus1 + 1);
            st_rps->UsedByCurrPicS0[i] = lsmash_bits_get( bits, 1 );    /* used_by_curr_pic_s0_flag */
        }
        for( int i = 0; i < num_positive_pics; i++ )
        {
            uint64_t delta_poc_s1_minus1 = nalu_get_exp_golomb_ue( bits );
            if( i == 0 )
                st_rps->DeltaPocS1[i] = +(delta_poc_s1_minus1 + 1);
            else
                st_rps->DeltaPocS1[i] = st_rps->DeltaPocS1[i - 1] + (delta_poc_s1_minus1 + 1);
            st_rps->UsedByCurrPicS0[i] = lsmash_bits_get( bits, 1 );    /* used_by_curr_pic_s1_flag */
        }
    }
    return 0;
}

static inline void hevc_parse_sub_layer_hrd_parameters
(
    lsmash_bits_t *bits,
    int            CpbCnt,
    int            sub_pic_hrd_params_present_flag
)
{
    for( int i = 0; i <= CpbCnt; i++ )
    {
        nalu_get_exp_golomb_ue( bits );         /* bit_rate_value_minus1[i] */
        nalu_get_exp_golomb_ue( bits );         /* cpb_size_value_minus1[i] */
        if( sub_pic_hrd_params_present_flag )
        {
            nalu_get_exp_golomb_ue( bits );     /* cpb_size_du_value_minus1[i] */
            nalu_get_exp_golomb_ue( bits );     /* bit_rate_du_value_minus1[i] */
        }
        lsmash_bits_get( bits, 1 );             /* cbr_flag[i] */
    }
}

static void hevc_parse_hrd_parameters
(
    lsmash_bits_t *bits,
    hevc_hrd_t    *hrd,
    int            commonInfPresentFlag,
    int            maxNumSubLayersMinus1
)
{
    /* The specification we refer to doesn't define the implicit value of some fields.
     * According to JCTVC-HM reference software,
     *   the implicit value of nal_hrd_parameters_present_flag is to be equal to 0,
     *   the implicit value of vcl_hrd_parameters_present_flag is to be equal to 0. */
    int nal_hrd_parameters_present_flag = 0;
    int vcl_hrd_parameters_present_flag = 0;
    memset( hrd, 0, sizeof(hevc_hrd_t) );
    if( commonInfPresentFlag )
    {
        nal_hrd_parameters_present_flag = lsmash_bits_get( bits, 1 );
        vcl_hrd_parameters_present_flag = lsmash_bits_get( bits, 1 );
        if( nal_hrd_parameters_present_flag
         || vcl_hrd_parameters_present_flag )
        {
            hrd->CpbDpbDelaysPresentFlag         = 1;
            hrd->sub_pic_hrd_params_present_flag = lsmash_bits_get( bits, 1 );
            if( hrd->sub_pic_hrd_params_present_flag )
            {
                lsmash_bits_get( bits, 8 );     /* tick_divisor_minus2 */
                hrd->du_cpb_removal_delay_increment_length     = lsmash_bits_get( bits, 5 ) + 1;
                hrd->sub_pic_cpb_params_in_pic_timing_sei_flag = lsmash_bits_get( bits, 1 );
                hrd->dpb_output_delay_du_length                = lsmash_bits_get( bits, 5 ) + 1;
            }
            lsmash_bits_get( bits, 4 );         /* bit_rate_scale */
            lsmash_bits_get( bits, 4 );         /* cpb_size_scale */
            if( hrd->sub_pic_hrd_params_present_flag )
                lsmash_bits_get( bits, 4 );     /* cpb_size_du_scale */
            lsmash_bits_get( bits, 5 );         /* initial_cpb_removal_delay_length_minus1 */
            hrd->au_cpb_removal_delay_length = lsmash_bits_get( bits, 5 ) + 1;
            hrd->dpb_output_delay_length     = lsmash_bits_get( bits, 5 ) + 1;
        }
    }
    for( int i = 0; i <= maxNumSubLayersMinus1; i++ )
    {
        hrd->fixed_pic_rate_general_flag[i]     =                                        lsmash_bits_get( bits, 1 );
        uint8_t  fixed_pic_rate_within_cvs_flag = !hrd->fixed_pic_rate_general_flag[i] ? lsmash_bits_get( bits, 1 )         : 1;
        uint8_t  low_delay_hrd_flag             = !fixed_pic_rate_within_cvs_flag      ? lsmash_bits_get( bits, 1 )         : 0;
        hrd->elemental_duration_in_tc[i]        =  fixed_pic_rate_within_cvs_flag      ? nalu_get_exp_golomb_ue( bits ) + 1 : 0;
        uint8_t  cpb_cnt_minus1                 = !low_delay_hrd_flag                  ? nalu_get_exp_golomb_ue( bits )     : 0;
        if( nal_hrd_parameters_present_flag )
            hevc_parse_sub_layer_hrd_parameters( bits, cpb_cnt_minus1, hrd->sub_pic_hrd_params_present_flag );
        if( vcl_hrd_parameters_present_flag )
            hevc_parse_sub_layer_hrd_parameters( bits, cpb_cnt_minus1, hrd->sub_pic_hrd_params_present_flag );
    }
}

static inline void hevc_parse_profile_tier_level_common
(
    lsmash_bits_t     *bits,
    hevc_ptl_common_t *ptlc,
    int                profile_present,
    int                level_present
)
{
    if( profile_present )
    {
        ptlc->profile_space               = lsmash_bits_get( bits,  2 );
        ptlc->tier_flag                   = lsmash_bits_get( bits,  1 );
        ptlc->profile_idc                 = lsmash_bits_get( bits,  5 );
        ptlc->profile_compatibility_flags = lsmash_bits_get( bits, 32 );
        ptlc->progressive_source_flag     = lsmash_bits_get( bits,  1 );
        ptlc->interlaced_source_flag      = lsmash_bits_get( bits,  1 );
        ptlc->non_packed_constraint_flag  = lsmash_bits_get( bits,  1 );
        ptlc->frame_only_constraint_flag  = lsmash_bits_get( bits,  1 );
        ptlc->reserved_zero_44bits        = lsmash_bits_get( bits, 44 );
    }
    if( level_present )
        ptlc->level_idc                   = lsmash_bits_get( bits,  8 );
}

static void hevc_parse_profile_tier_level
(
    lsmash_bits_t *bits,
    hevc_ptl_t    *ptl,
    int            maxNumSubLayersMinus1
)
{
    hevc_parse_profile_tier_level_common( bits, &ptl->general, 1, 1 );
    if( maxNumSubLayersMinus1 == 0 )
        return;
    assert( maxNumSubLayersMinus1 <= 6 );
    int sub_layer_profile_present_flag[6] = { 0 };
    int sub_layer_level_present_flag  [6] = { 0 };
    for( int i = 0; i < maxNumSubLayersMinus1; i++ )
    {
        sub_layer_profile_present_flag[i] = lsmash_bits_get( bits, 1 );
        sub_layer_level_present_flag  [i] = lsmash_bits_get( bits, 1 );
    }
    for( int i = maxNumSubLayersMinus1; i < 8; i++ )
        lsmash_bits_get( bits, 2 );     /* reserved_zero_2bits[i] */
    for( int i = 0; i < maxNumSubLayersMinus1; i++ )
        hevc_parse_profile_tier_level_common( bits, &ptl->sub_layer[i], sub_layer_profile_present_flag[i], sub_layer_level_present_flag[i] );
}

static int hevc_parse_vps_minimally
(
    lsmash_bits_t *bits,
    hevc_vps_t    *vps,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    memset( vps, 0, sizeof(hevc_vps_t) );
    vps->video_parameter_set_id = lsmash_bits_get( bits, 4 );
    /* vps_reserved_three_2bits shall be 3 in the specification we refer to. */
    if( lsmash_bits_get( bits, 2 ) != 3 )
        return LSMASH_ERR_NAMELESS;
    /* vps_max_layers_minus1 shall be 0 in the specification we refer to. */
    if( lsmash_bits_get( bits, 6 ) != 0 )
        return LSMASH_ERR_NAMELESS;
    vps->max_sub_layers_minus1    = lsmash_bits_get( bits, 3 );
    vps->temporal_id_nesting_flag = lsmash_bits_get( bits, 1 );
    /* When vps_max_sub_layers_minus1 is equal to 0, vps_temporal_id_nesting_flag shall be equal to 1. */
    if( (vps->max_sub_layers_minus1 | vps->temporal_id_nesting_flag) == 0 )
        return LSMASH_ERR_INVALID_DATA;
    /* vps_reserved_0xffff_16bits shall be 0xFFFF in the specification we refer to. */
    if( lsmash_bits_get( bits, 16 ) != 0xFFFF )
        return LSMASH_ERR_NAMELESS;
    hevc_parse_profile_tier_level( bits, &vps->ptl, vps->max_sub_layers_minus1 );
    vps->frame_field_info_present_flag = vps->ptl.general.progressive_source_flag
                                      && vps->ptl.general.interlaced_source_flag;
    int sub_layer_ordering_info_present_flag = lsmash_bits_get( bits, 1 );
    for( int i = sub_layer_ordering_info_present_flag ? 0 : vps->max_sub_layers_minus1; i <= vps->max_sub_layers_minus1; i++ )
    {
        nalu_get_exp_golomb_ue( bits );  /* max_dec_pic_buffering_minus1[i] */
        nalu_get_exp_golomb_ue( bits );  /* max_num_reorder_pics        [i] */
        nalu_get_exp_golomb_ue( bits );  /* max_latency_increase_plus1  [i] */
    }
    uint8_t  max_layer_id          = lsmash_bits_get( bits, 6 );
    uint16_t num_layer_sets_minus1 = nalu_get_exp_golomb_ue( bits );
    for( int i = 1; i <= num_layer_sets_minus1; i++ )
        for( int j = 0; j <= max_layer_id; j++ )
            lsmash_bits_get( bits, 1 );     /* layer_id_included_flag[i][j] */
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int hevc_parse_vps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    hevc_vps_t *vps;
    {
        /* Parse VPS minimally for configuration records. */
        hevc_vps_t min_vps;
        int err = hevc_parse_vps_minimally( bits, &min_vps, rbsp_buffer, ebsp, ebsp_size );
        if( err < 0 )
            return err;
        vps = hevc_get_vps( info->vps_list, min_vps.video_parameter_set_id );
        if( !vps )
            return LSMASH_ERR_NAMELESS;
        *vps = min_vps;
    }
    vps->timing_info_present_flag = lsmash_bits_get( bits, 1 );
    if( vps->timing_info_present_flag )
    {
        lsmash_bits_get( bits, 32 );        /* num_units_in_tick */
        lsmash_bits_get( bits, 32 );        /* time_scale */
        if( lsmash_bits_get( bits,  1 ) )   /* poc_proportional_to_timing_flag */
            nalu_get_exp_golomb_ue( bits ); /* num_ticks_poc_diff_one_minus1 */
        vps->num_hrd_parameters = nalu_get_exp_golomb_ue( bits );
        for( int i = 0; i < vps->num_hrd_parameters; i++ )
        {
            nalu_get_exp_golomb_ue( bits );     /* hrd_layer_set_idx[i] */
            int cprms_present_flag = i > 0 ? lsmash_bits_get( bits, 1 ) : 1;
            /* Although the value of vps_num_hrd_parameters is required to be less than or equal to 1 in the spec
             * we refer to, decoders shall allow other values of vps_num_hrd_parameters in the range of 0 to 1024,
             * inclusive, to appear in the syntax. */
            if( i <= 1 )
                hevc_parse_hrd_parameters( bits, &vps->hrd[i], cprms_present_flag, vps->max_sub_layers_minus1 );
            else
            {
                hevc_hrd_t dummy_hrd;
                hevc_parse_hrd_parameters( bits, &dummy_hrd,   cprms_present_flag, vps->max_sub_layers_minus1 );
            }
        }
    }
    /* Skip VPS extension. */
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    vps->present = 1;
    info->vps = *vps;
    return 0;
}

static int hevc_parse_sps_minimally
(
    lsmash_bits_t *bits,
    hevc_sps_t    *sps,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    memset( sps, 0, sizeof(hevc_sps_t) );
    sps->video_parameter_set_id   = lsmash_bits_get( bits, 4 );
    sps->max_sub_layers_minus1    = lsmash_bits_get( bits, 3 );
    sps->temporal_id_nesting_flag = lsmash_bits_get( bits, 1 );
    hevc_parse_profile_tier_level( bits, &sps->ptl, sps->max_sub_layers_minus1 );
    sps->seq_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    sps->chroma_format_idc    = nalu_get_exp_golomb_ue( bits );
    if( sps->chroma_format_idc == 3 )
        sps->separate_colour_plane_flag = lsmash_bits_get( bits, 1 );
    static const int SubWidthC [] = { 1, 2, 2, 1 };
    static const int SubHeightC[] = { 1, 2, 1, 1 };
    uint64_t pic_width_in_luma_samples  = nalu_get_exp_golomb_ue( bits );
    uint64_t pic_height_in_luma_samples = nalu_get_exp_golomb_ue( bits );
    sps->cropped_width  = pic_width_in_luma_samples;
    sps->cropped_height = pic_height_in_luma_samples;
    if( lsmash_bits_get( bits, 1 ) )    /* conformance_window_flag */
    {
        uint64_t conf_win_left_offset   = nalu_get_exp_golomb_ue( bits );
        uint64_t conf_win_right_offset  = nalu_get_exp_golomb_ue( bits );
        uint64_t conf_win_top_offset    = nalu_get_exp_golomb_ue( bits );
        uint64_t conf_win_bottom_offset = nalu_get_exp_golomb_ue( bits );
        sps->cropped_width  -= (conf_win_left_offset + conf_win_right_offset)  * SubWidthC [ sps->chroma_format_idc ];
        sps->cropped_height -= (conf_win_top_offset  + conf_win_bottom_offset) * SubHeightC[ sps->chroma_format_idc ];
    }
    sps->bit_depth_luma_minus8               = nalu_get_exp_golomb_ue( bits );
    sps->bit_depth_chroma_minus8             = nalu_get_exp_golomb_ue( bits );
    sps->log2_max_pic_order_cnt_lsb          = nalu_get_exp_golomb_ue( bits ) + 4;
    int sub_layer_ordering_info_present_flag = lsmash_bits_get( bits, 1 );
    for( int i = sub_layer_ordering_info_present_flag ? 0 : sps->max_sub_layers_minus1; i <= sps->max_sub_layers_minus1; i++ )
    {
        nalu_get_exp_golomb_ue( bits );  /* max_dec_pic_buffering_minus1[i] */
        nalu_get_exp_golomb_ue( bits );  /* max_num_reorder_pics        [i] */
        nalu_get_exp_golomb_ue( bits );  /* max_latency_increase_plus1  [i] */
    }
    uint64_t log2_min_luma_coding_block_size_minus3   = nalu_get_exp_golomb_ue( bits );
    uint64_t log2_diff_max_min_luma_coding_block_size = nalu_get_exp_golomb_ue( bits );
    nalu_get_exp_golomb_ue( bits );         /* log2_min_transform_block_size_minus2 */
    nalu_get_exp_golomb_ue( bits );         /* log2_diff_max_min_transform_block_size */
    nalu_get_exp_golomb_ue( bits );         /* max_transform_hierarchy_depth_inter */
    nalu_get_exp_golomb_ue( bits );         /* max_transform_hierarchy_depth_intra */
    {
        int MinCbLog2SizeY = log2_min_luma_coding_block_size_minus3 + 3;
        int MinCbSizeY     = 1 << MinCbLog2SizeY;
        if( pic_width_in_luma_samples  == 0 || pic_width_in_luma_samples  % MinCbSizeY
         || pic_height_in_luma_samples == 0 || pic_height_in_luma_samples % MinCbSizeY )
            return LSMASH_ERR_INVALID_DATA; /* Both shall be an integer multiple of MinCbSizeY. */
        int CtbLog2SizeY = MinCbLog2SizeY + log2_diff_max_min_luma_coding_block_size;
        int CtbSizeY     = 1 << CtbLog2SizeY;
        sps->PicWidthInCtbsY  = (pic_width_in_luma_samples  - 1) / CtbSizeY + 1;
        sps->PicHeightInCtbsY = (pic_height_in_luma_samples - 1) / CtbSizeY + 1;
        sps->PicSizeInCtbsY   = sps->PicWidthInCtbsY * sps->PicHeightInCtbsY;
    }
    if( lsmash_bits_get( bits, 1 )          /* scaling_list_enabled_flag */
     && lsmash_bits_get( bits, 1 ) )        /* sps_scaling_list_data_present_flag */
        hevc_parse_scaling_list_data( bits );
    lsmash_bits_get( bits, 1 );             /* amp_enabled_flag */
    lsmash_bits_get( bits, 1 );             /* sample_adaptive_offset_enabled_flag */
    if( lsmash_bits_get( bits, 1 ) )        /* pcm_enabled_flag */
    {
        lsmash_bits_get( bits, 4 );         /* pcm_sample_bit_depth_luma_minus1 */
        lsmash_bits_get( bits, 4 );         /* pcm_sample_bit_depth_chroma_minus1 */
        nalu_get_exp_golomb_ue( bits );     /* log2_min_pcm_luma_coding_block_size_minus3 */
        nalu_get_exp_golomb_ue( bits );     /* log2_diff_max_min_pcm_luma_coding_block_size */
        lsmash_bits_get( bits, 1 );         /* pcm_loop_filter_disabled_flag */
    }
    sps->num_short_term_ref_pic_sets = nalu_get_exp_golomb_ue( bits );
    for( int i = 0; i < sps->num_short_term_ref_pic_sets; i++ )
        if( (err = hevc_short_term_ref_pic_set( bits, sps, i )) < 0 )
            return err;
    sps->long_term_ref_pics_present_flag = lsmash_bits_get( bits, 1 );
    if( sps->long_term_ref_pics_present_flag )
    {
        sps->num_long_term_ref_pics_sps = nalu_get_exp_golomb_ue( bits );
        for( int i = 0; i < sps->num_long_term_ref_pics_sps; i++ )
        {
            lsmash_bits_get( bits, sps->log2_max_pic_order_cnt_lsb );   /* lt_ref_pic_poc_lsb_sps      [i] */
            lsmash_bits_get( bits, 1 );                                 /* used_by_curr_pic_lt_sps_flag[i] */
        }
    }
    sps->temporal_mvp_enabled_flag = lsmash_bits_get( bits, 1 );
    lsmash_bits_get( bits, 1 );                     /* strong_intra_smoothing_enabled_flag */
    sps->vui.present = lsmash_bits_get( bits, 1 );  /* vui_parameters_present_flag */
    if( sps->vui.present )
    {
        /* vui_parameters() */
        if( lsmash_bits_get( bits, 1 ) )    /* aspect_ratio_info_present_flag */
        {
            uint8_t aspect_ratio_idc = lsmash_bits_get( bits, 8 );
            if( aspect_ratio_idc == 255 )
            {
                /* EXTENDED_SAR */
                sps->vui.sar_width  = lsmash_bits_get( bits, 16 );
                sps->vui.sar_height = lsmash_bits_get( bits, 16 );
            }
            else
            {
                static const struct
                {
                    uint16_t sar_width;
                    uint16_t sar_height;
                } pre_defined_sar[] =
                    {
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
        else
        {
            sps->vui.sar_width  = 0;
            sps->vui.sar_height = 0;
        }
        if( lsmash_bits_get( bits, 1 ) )    /* overscan_info_present_flag */
            lsmash_bits_get( bits, 1 );     /* overscan_appropriate_flag */
        if( lsmash_bits_get( bits, 1 ) )    /* video_signal_type_present_flag */
        {
            lsmash_bits_get( bits, 3 );     /* video_format */
            sps->vui.video_full_range_flag           = lsmash_bits_get( bits, 1 );
            sps->vui.colour_description_present_flag = lsmash_bits_get( bits, 1 );
            if( sps->vui.colour_description_present_flag )
            {
                sps->vui.colour_primaries         = lsmash_bits_get( bits, 8 );
                sps->vui.transfer_characteristics = lsmash_bits_get( bits, 8 );
                sps->vui.matrix_coeffs            = lsmash_bits_get( bits, 8 );
            }
            else
            {
                sps->vui.colour_primaries         = 2;
                sps->vui.transfer_characteristics = 2;
                sps->vui.matrix_coeffs            = 2;
            }
        }
        if( lsmash_bits_get( bits, 1 ) )    /* chroma_loc_info_present_flag */
        {
            nalu_get_exp_golomb_ue( bits ); /* chroma_sample_loc_type_top_field */
            nalu_get_exp_golomb_ue( bits ); /* chroma_sample_loc_type_bottom_field */
        }
        lsmash_bits_get( bits, 1 );         /* neutral_chroma_indication_flag */
        sps->vui.field_seq_flag                = lsmash_bits_get( bits, 1 );
        sps->vui.frame_field_info_present_flag = lsmash_bits_get( bits, 1 );
        if( sps->vui.field_seq_flag )
            /* cropped_height indicates in a frame. */
            sps->cropped_height *= 2;
        if( lsmash_bits_get( bits, 1 ) )    /* default_display_window_flag */
        {
            /* default display window
             *   A rectangular region for display specified by these values is not considered
             *   as cropped visual presentation size which decoder delivers.
             *   Maybe, these values shall be indicated by the clean aperture on container level. */
            sps->vui.def_disp_win_offset.left   = (lsmash_rational_u32_t){ nalu_get_exp_golomb_ue( bits ) * SubWidthC [ sps->chroma_format_idc ], 1 };
            sps->vui.def_disp_win_offset.right  = (lsmash_rational_u32_t){ nalu_get_exp_golomb_ue( bits ) * SubWidthC [ sps->chroma_format_idc ], 1 };
            sps->vui.def_disp_win_offset.top    = (lsmash_rational_u32_t){ nalu_get_exp_golomb_ue( bits ) * SubHeightC[ sps->chroma_format_idc ], 1 };
            sps->vui.def_disp_win_offset.bottom = (lsmash_rational_u32_t){ nalu_get_exp_golomb_ue( bits ) * SubHeightC[ sps->chroma_format_idc ], 1 };
        }
        if( lsmash_bits_get( bits, 1 ) )    /* vui_timing_info_present_flag */
        {
            sps->vui.num_units_in_tick = lsmash_bits_get( bits, 32 );
            sps->vui.time_scale        = lsmash_bits_get( bits, 32 );
            if( lsmash_bits_get( bits, 1 ) )    /* vui_poc_proportional_to_timing_flag */
                nalu_get_exp_golomb_ue( bits ); /* vui_num_ticks_poc_diff_one_minus1 */
            if( lsmash_bits_get( bits, 1 ) )    /* vui_hrd_parameters_present_flag */
                hevc_parse_hrd_parameters( bits, &sps->vui.hrd, 1, sps->max_sub_layers_minus1 );
        }
        else
        {
            sps->vui.num_units_in_tick = 1;     /* arbitrary */
            sps->vui.time_scale        = 25;    /* arbitrary */
        }
        if( lsmash_bits_get( bits, 1 ) )    /* bitstream_restriction_flag */
        {
            lsmash_bits_get( bits, 1 );     /* tiles_fixed_structure_flag */
            lsmash_bits_get( bits, 1 );     /* motion_vectors_over_pic_boundaries_flag */
            lsmash_bits_get( bits, 1 );     /* restricted_ref_pic_lists_flag */
            sps->vui.min_spatial_segmentation_idc = nalu_get_exp_golomb_ue( bits );
            nalu_get_exp_golomb_ue( bits ); /* max_bytes_per_pic_denom */
            nalu_get_exp_golomb_ue( bits ); /* max_bits_per_min_cu_denom */
            nalu_get_exp_golomb_ue( bits ); /* log2_max_mv_length_horizontal */
            nalu_get_exp_golomb_ue( bits ); /* log2_max_mv_length_vertical */
        }
        else
            sps->vui.min_spatial_segmentation_idc = 0;
    }
    else
    {
        sps->vui.sar_width                     = 0;
        sps->vui.sar_height                    = 0;
        sps->vui.colour_primaries              = 2;
        sps->vui.transfer_characteristics      = 2;
        sps->vui.matrix_coeffs                 = 2;
        sps->vui.field_seq_flag                = 0;
        sps->vui.frame_field_info_present_flag = sps->ptl.general.progressive_source_flag
                                              && sps->ptl.general.interlaced_source_flag;
        sps->vui.num_units_in_tick             = 1;     /* arbitrary */
        sps->vui.time_scale                    = 25;    /* arbitrary */
        sps->vui.min_spatial_segmentation_idc  = 0;
    }
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int hevc_parse_sps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    hevc_sps_t *sps;
    {
        /* Parse SPS minimally for configuration records. */
        hevc_sps_t min_sps;
        int err = hevc_parse_sps_minimally( bits, &min_sps, rbsp_buffer, ebsp, ebsp_size );
        if( err < 0 )
            return err;
        sps = hevc_get_sps( info->sps_list, min_sps.seq_parameter_set_id );
        if( !sps )
            return LSMASH_ERR_NAMELESS;
        *sps = min_sps;
    }
    /* Skip SPS extension. */
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    sps->present = 1;
    info->sps = *sps;
    hevc_activate_vps( info, info->sps.video_parameter_set_id );
    return 0;
}

static int hevc_allocate_tile_sizes
(
    hevc_pps_t *pps,
    uint32_t    num_tile_columns,
    uint32_t    num_tile_rows
)
{
    /* Allocate columns and rows of tiles. */
    size_t col_alloc_size = 2 * num_tile_columns * sizeof(uint32_t);
    if( col_alloc_size > pps->col_alloc_size )
    {
        void *temp = lsmash_realloc( pps->colWidth, col_alloc_size );
        if( !temp )
            return LSMASH_ERR_MEMORY_ALLOC;
        pps->col_alloc_size = col_alloc_size;
        pps->colWidth       = temp;
    }
    size_t row_alloc_size = 2 * num_tile_rows * sizeof(uint32_t);
    if( row_alloc_size > pps->row_alloc_size )
    {
        void *temp = lsmash_realloc( pps->rowHeight, row_alloc_size );
        if( !temp )
            return LSMASH_ERR_MEMORY_ALLOC;
        pps->row_alloc_size = row_alloc_size;
        pps->rowHeight      = temp;
    }
    pps->colBd = pps->colWidth  + num_tile_columns;
    pps->rowBd = pps->rowHeight + num_tile_rows;
    return 0;
}

static int hevc_parse_pps_minimally
(
    lsmash_bits_t *bits,
    hevc_pps_t    *pps,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
)
{
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, ebsp_size );
    if( err < 0 )
        return err;
    memset( pps, 0, SIZEOF_PPS_EXCLUDING_HEAP );
    pps->pic_parameter_set_id                  = nalu_get_exp_golomb_ue( bits );
    pps->seq_parameter_set_id                  = nalu_get_exp_golomb_ue( bits );
    pps->dependent_slice_segments_enabled_flag = lsmash_bits_get( bits, 1 );
    pps->output_flag_present_flag              = lsmash_bits_get( bits, 1 );
    pps->num_extra_slice_header_bits           = lsmash_bits_get( bits, 3 );
    lsmash_bits_get( bits, 1 );         /* sign_data_hiding_enabled_flag */
    lsmash_bits_get( bits, 1 );         /* cabac_init_present_flag */
    nalu_get_exp_golomb_ue( bits );     /* num_ref_idx_l0_default_active_minus1 */
    nalu_get_exp_golomb_ue( bits );     /* num_ref_idx_l1_default_active_minus1 */
    nalu_get_exp_golomb_se( bits );     /* init_qp_minus26 */
    lsmash_bits_get( bits, 1 );         /* constrained_intra_pred_flag */
    lsmash_bits_get( bits, 1 );         /* transform_skip_enabled_flag */
    if( lsmash_bits_get( bits, 1 ) )    /* cu_qp_delta_enabled_flag */
        nalu_get_exp_golomb_ue( bits ); /* diff_cu_qp_delta_depth */
    nalu_get_exp_golomb_se( bits );     /* cb_qp_offset */
    nalu_get_exp_golomb_se( bits );     /* cr_qp_offset */
    lsmash_bits_get( bits, 1 );         /* slice_chroma_qp_offsets_present_flag */
    lsmash_bits_get( bits, 1 );         /* weighted_pred_flag */
    lsmash_bits_get( bits, 1 );         /* weighted_bipred_flag */
    lsmash_bits_get( bits, 1 )          /* transquant_bypass_enabled_flag */;
    pps->tiles_enabled_flag               = lsmash_bits_get( bits, 1 );
    pps->entropy_coding_sync_enabled_flag = lsmash_bits_get( bits, 1 );
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int hevc_parse_pps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
)
{
    int err;
    lsmash_bits_t *bits = info->bits;
    hevc_pps_t *pps;
    {
        /* Parse PPS minimally for configuration records. */
        hevc_pps_t min_pps;
        if( (err = hevc_parse_pps_minimally( bits, &min_pps, rbsp_buffer, ebsp, ebsp_size )) < 0 )
            return err;
        pps = hevc_get_pps( info->pps_list, min_pps.pic_parameter_set_id );
        if( !pps )
            return LSMASH_ERR_NAMELESS;
        memcpy( pps, &min_pps, SIZEOF_PPS_EXCLUDING_HEAP );
    }
    hevc_sps_t temp_sps = info->sps;
    if( (err = hevc_activate_sps( info, pps->seq_parameter_set_id )) < 0 )
        return err;
    hevc_sps_t *sps = &info->sps;
    if( pps->tiles_enabled_flag )
    {
        pps->num_tile_columns_minus1 = nalu_get_exp_golomb_ue( bits );
        pps->num_tile_rows_minus1    = nalu_get_exp_golomb_ue( bits );
        if( pps->num_tile_columns_minus1 >= sps->PicWidthInCtbsY
         || pps->num_tile_rows_minus1    >= sps->PicHeightInCtbsY )
        {
            err = LSMASH_ERR_INVALID_DATA;
            goto fail;
        }
        if( (err = hevc_allocate_tile_sizes( pps, pps->num_tile_columns_minus1 + 1, pps->num_tile_rows_minus1 + 1 )) < 0 )
            goto fail;
        if( lsmash_bits_get( bits, 1 ) )        /* uniform_spacing_flag */
        {
            for( int i = 0; i <= pps->num_tile_columns_minus1; i++ )
                pps->colWidth[i] = ((i + 1) * sps->PicWidthInCtbsY) / (pps->num_tile_columns_minus1 + 1)
                                 - ( i      * sps->PicWidthInCtbsY) / (pps->num_tile_columns_minus1 + 1);
            for( int j = 0; j <= pps->num_tile_rows_minus1; j++ )
                pps->rowHeight[j] = ((j + 1) * sps->PicHeightInCtbsY) / (pps->num_tile_rows_minus1 + 1)
                                  - ( j      * sps->PicHeightInCtbsY) / (pps->num_tile_rows_minus1 + 1);
        }
        else
        {
            pps->colWidth[ pps->num_tile_columns_minus1 ] = sps->PicWidthInCtbsY;
            for( uint64_t i = 0; i < pps->num_tile_columns_minus1; i++ )
            {
                pps->colWidth[i] = nalu_get_exp_golomb_ue( bits ) + 1;      /* column_width_minus1[i] */
                pps->colWidth[ pps->num_tile_columns_minus1 ] -= pps->colWidth[i];
            }
            pps->rowHeight[ pps->num_tile_rows_minus1 ] = sps->PicHeightInCtbsY;
            for( uint64_t j = 0; j < pps->num_tile_rows_minus1; j++ )
            {
                pps->rowHeight[j] = nalu_get_exp_golomb_ue( bits ) + 1;     /* row_height_minus1  [j] */
                pps->rowHeight[ pps->num_tile_rows_minus1 ] -= pps->rowHeight[j];
            }
        }
        pps->colBd[0] = 0;
        for( uint64_t i = 0; i < pps->num_tile_columns_minus1; i++ )
            pps->colBd[i + 1] = pps->colBd[i] + pps->colWidth[i];
        pps->rowBd[0] = 0;
        for( uint64_t j = 0; j < pps->num_tile_rows_minus1; j++ )
            pps->rowBd[j + 1] = pps->rowBd[j] + pps->rowHeight[j];
        lsmash_bits_get( bits, 1 );             /* loop_filter_across_tiles_enabled_flag */
    }
    else
    {
        pps->num_tile_columns_minus1 = 0;
        pps->num_tile_rows_minus1    = 0;
        if( (err = hevc_allocate_tile_sizes( pps, 1, 1 )) < 0 )
            goto fail;
        pps->colWidth [0] = sps->PicWidthInCtbsY;
        pps->rowHeight[0] = sps->PicHeightInCtbsY;
        pps->colBd    [0] = 0;
        pps->rowBd    [0] = 0;
    }
    /* */
    /* Skip PPS extension. */
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        goto fail;
    pps->present = 1;
    info->pps = *pps;
    hevc_activate_vps( info, info->sps.video_parameter_set_id );
    return 0;
fail:
    /* Revert SPS. */
    info->sps = temp_sps;
    return err;
}

int hevc_parse_sei
(
    lsmash_bits_t      *bits,
    hevc_vps_t         *vps,
    hevc_sps_t         *sps,
    hevc_sei_t         *sei,
    hevc_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
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
        if( nuh->nal_unit_type == HEVC_NALU_TYPE_PREFIX_SEI )
        {
            if( payloadType == 1 )
            {
                /* pic_timing */
                hevc_hrd_t *hrd = sps ? &sps->vui.hrd : vps ? &vps->hrd[0] : NULL;
                if( !hrd )
                    goto skip_sei_message;  /* Any active VPS or SPS is not found. */
                sei->pic_timing.present = 1;
                if( (sps && sps->vui.frame_field_info_present_flag) || vps->frame_field_info_present_flag )
                {
                    sei->pic_timing.pic_struct = lsmash_bits_get( bits, 4 );
                    lsmash_bits_get( bits, 2 );     /* source_scan_type */
                    lsmash_bits_get( bits, 1 );     /* duplicate_flag */
                }
                if( hrd->CpbDpbDelaysPresentFlag )
                {
                    lsmash_bits_get( bits, hrd->au_cpb_removal_delay_length );      /* au_cpb_removal_delay_minus1 */
                    lsmash_bits_get( bits, hrd->dpb_output_delay_length );          /* pic_dpb_output_delay */
                    if( hrd->sub_pic_hrd_params_present_flag )
                    {
                        lsmash_bits_get( bits, hrd->dpb_output_delay_du_length );   /* pic_dpb_output_du_delay */
                        if( hrd->sub_pic_cpb_params_in_pic_timing_sei_flag )
                        {
                            uint64_t num_decoding_units_minus1 = nalu_get_exp_golomb_ue( bits );
                            int du_common_cpb_removal_delay_flag = lsmash_bits_get( bits, 1 );
                            if( du_common_cpb_removal_delay_flag )
                                /* du_common_cpb_removal_delay_increment_minus1 */
                                lsmash_bits_get( bits, hrd->du_cpb_removal_delay_increment_length );
                            for( uint64_t i = 0; i <= num_decoding_units_minus1; i++ )
                            {
                                nalu_get_exp_golomb_ue( bits );         /* num_nalus_in_du_minus1 */
                                if( !du_common_cpb_removal_delay_flag && i < num_decoding_units_minus1 )
                                    nalu_get_exp_golomb_ue( bits );     /* du_cpb_removal_delay_increment_minus1 */
                            }
                        }
                    }
                }
            }
            else if( payloadType == 3 )
            {
                /* filler_payload
                 * FIXME: remove if array_completeness equal to 1. */
                return LSMASH_ERR_PATCH_WELCOME;
            }
            else if( payloadType == 6 )
            {
                /* recovery_point */
                sei->recovery_point.present          = 1;
                sei->recovery_point.recovery_poc_cnt = nalu_get_exp_golomb_se( bits );
                lsmash_bits_get( bits, 1 );     /* exact_match_flag */
                sei->recovery_point.broken_link_flag = lsmash_bits_get( bits, 1 );
            }
            else
                goto skip_sei_message;
        }
        else if( nuh->nal_unit_type == HEVC_NALU_TYPE_SUFFIX_SEI )
        {
            if( payloadType == 3 )
            {
                /* filler_payload
                 * FIXME: remove if array_completeness equal to 1. */
                return LSMASH_ERR_PATCH_WELCOME;
            }
            else
                goto skip_sei_message;
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
                lsmash_log( NULL, LSMASH_LOG_ERROR, "Invalid payloadSize is there within H.265/HEVC sei_message().\n" );
                return LSMASH_ERR_INVALID_DATA;
            }
            else
            {
                /* The last payloadSize is invalid but it probably can do recovery, so just log warning and break loop here. */
                lsmash_log( NULL, LSMASH_LOG_WARNING, "Invalid payloadSize is there within H.265/HEVC sei_message().\n" );
                break;  /* redundant but for readability */
            }
        }
    } while( *(rbsp_start + rbsp_pos) != 0x80 );        /* All SEI messages are byte aligned at their end.
                                                         * Therefore, 0x80 shall be rbsp_trailing_bits(). */
    lsmash_bits_empty( bits );
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int hevc_parse_slice_segment_header
(
    hevc_info_t        *info,
    hevc_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
)
{
    lsmash_bits_t *bits = info->bits;
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( bits, rbsp_buffer, &rbsp_size, ebsp, LSMASH_MIN( ebsp_size, 50 ) );
    if( err < 0 )
        return err;
    hevc_slice_info_t *slice = &info->slice;
    memset( slice, 0, sizeof(hevc_slice_info_t) );
    slice->nalu_type  = nuh->nal_unit_type;
    slice->TemporalId = nuh->TemporalId;
    slice->first_slice_segment_in_pic_flag = lsmash_bits_get( bits, 1 );
    if( nuh->nal_unit_type >= HEVC_NALU_TYPE_BLA_W_LP
     && nuh->nal_unit_type <= HEVC_NALU_TYPE_RSV_IRAP_VCL23 )
        lsmash_bits_get( bits, 1 );     /* no_output_of_prior_pics_flag */
    slice->pic_parameter_set_id = nalu_get_exp_golomb_ue( bits );
    /* Get PPS by slice_pic_parameter_set_id. */
    hevc_pps_t *pps = hevc_get_pps( info->pps_list, slice->pic_parameter_set_id );
    if( !pps )
        return LSMASH_ERR_NAMELESS;
    /* Get SPS by pps_seq_parameter_set_id. */
    hevc_sps_t *sps = hevc_get_sps( info->sps_list, pps->seq_parameter_set_id );
    if( !sps )
        return LSMASH_ERR_NAMELESS;
    slice->video_parameter_set_id = sps->video_parameter_set_id;
    slice->seq_parameter_set_id   = pps->seq_parameter_set_id;
    if( !slice->first_slice_segment_in_pic_flag )
    {
        slice->dependent_slice_segment_flag = pps->dependent_slice_segments_enabled_flag ? lsmash_bits_get( bits, 1 ) : 0;
        slice->segment_address              = lsmash_bits_get( bits, lsmash_ceil_log2( sps->PicSizeInCtbsY ) );
    }
    else
    {
        slice->dependent_slice_segment_flag = 0;
        slice->segment_address              = 0;
    }
    if( !slice->dependent_slice_segment_flag )
    {
        /* independent slice segment
         * The values of the slice segment header of dependent slice segment are inferred from the values
         * for the preceding independent slice segment in decoding order, if some of the values are not present. */
        for( int i = 0; i < pps->num_extra_slice_header_bits; i++ )
            lsmash_bits_get( bits, 1 );         /* slice_reserved_flag[i] */
        slice->type = nalu_get_exp_golomb_ue( bits );
        if( pps->output_flag_present_flag )
            lsmash_bits_get( bits, 1 );         /* pic_output_flag */
        if( sps->separate_colour_plane_flag )
            lsmash_bits_get( bits, 1 );         /* colour_plane_id */
        if( nuh->nal_unit_type != HEVC_NALU_TYPE_IDR_W_RADL
         && nuh->nal_unit_type != HEVC_NALU_TYPE_IDR_N_LP )
        {
            slice->pic_order_cnt_lsb = lsmash_bits_get( bits, sps->log2_max_pic_order_cnt_lsb );
            if( !lsmash_bits_get( bits, 1 ) )   /* short_term_ref_pic_set_sps_flag */
            {
                if( (err = hevc_short_term_ref_pic_set( bits, sps, sps->num_short_term_ref_pic_sets )) < 0 )
                    return err;
            }
            else
            {
                int length = lsmash_ceil_log2( sps->num_short_term_ref_pic_sets );
                if( length > 0 )
                    lsmash_bits_get( bits, length );                                /* short_term_ref_pic_set_idx */
            }
            if( sps->long_term_ref_pics_present_flag )
            {
                uint64_t num_long_term_sps  = sps->num_long_term_ref_pics_sps > 0 ? nalu_get_exp_golomb_ue( bits ) : 0;
                uint64_t num_long_term_pics = nalu_get_exp_golomb_ue( bits );
                for( uint64_t i = 0; i < num_long_term_sps + num_long_term_pics; i++ )
                {
                    if( i < num_long_term_sps )
                    {
                        int length = lsmash_ceil_log2( sps->num_long_term_ref_pics_sps );
                        if( length > 0 )
                            lsmash_bits_get( bits, length );                        /* lt_idx_sps[i] */
                    }
                    else
                    {
                        lsmash_bits_get( bits, sps->log2_max_pic_order_cnt_lsb );   /* poc_lsb_lt              [i] */
                        lsmash_bits_get( bits, 1 );                                 /* used_by_curr_pic_lt_flag[i] */
                    }
                    if( lsmash_bits_get( bits, 1 ) )                                /* delta_poc_msb_present_flag[i] */
                        nalu_get_exp_golomb_ue( bits );                             /* delta_poc_msb_cycle_lt    [i] */
                }
            }
            if( sps->temporal_mvp_enabled_flag )
                lsmash_bits_get( bits, 1 );                                         /* slice_temporal_mvp_enabled_flag */
        }
        else
            /* For IDR-pictures, slice_pic_order_cnt_lsb is inferred to be 0. */
            slice->pic_order_cnt_lsb = 0;
    }
    lsmash_bits_empty( bits );
    if( bits->bs->error )
        return LSMASH_ERR_NAMELESS;
    info->sps = *sps;
    info->pps = *pps;
    return 0;
}

static int hevc_get_vps_id
(
    uint8_t *ps_ebsp,
    uint32_t ps_ebsp_length,
    uint8_t *ps_id
)
{
    /* the number of bits of vps_id = 4
     * (4 - 1) / 8 + 1 = 1 bytes */
    *ps_id = (*ps_ebsp >> 4) & 0x0F;    /* vps_video_parameter_set_id */
    return 0;
}

static int hevc_get_sps_id
(
    uint8_t *ps_ebsp,
    uint32_t ps_ebsp_length,
    uint8_t *ps_id
)
{
    /* the maximum number of bits of sps_id = 9: 0b00001XXXX
     * (8 + 688 + 9 - 1) / 8 + 1 = 89 bytes
     * Here more additional bytes because there might be emulation_prevention_three_byte(s). */
    lsmash_bits_t bits = { 0 };
    lsmash_bs_t   bs   = { 0 };
    uint8_t rbsp_buffer[128];
    uint8_t buffer     [128];
    bs.buffer.data  = buffer;
    bs.buffer.alloc = 128;
    lsmash_bits_init( &bits, &bs );
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( &bits, rbsp_buffer, &rbsp_size, ps_ebsp, LSMASH_MIN( ps_ebsp_length, 128 ) );
    if( err < 0 )
        return err;
    /* Skip sps_video_parameter_set_id and sps_temporal_id_nesting_flag. */
    uint8_t sps_max_sub_layers_minus1 = (lsmash_bits_get( &bits, 8 ) >> 1) & 0x07;
    /* profile_tier_level() costs at most 688 bits. */
    hevc_ptl_t sps_ptl;
    hevc_parse_profile_tier_level( &bits, &sps_ptl, sps_max_sub_layers_minus1 );
    uint64_t sps_seq_parameter_set_id = nalu_get_exp_golomb_ue( &bits );
    if( sps_seq_parameter_set_id > HEVC_MAX_SPS_ID )
        return LSMASH_ERR_INVALID_DATA;
    *ps_id = sps_seq_parameter_set_id;
    return bs.error ? LSMASH_ERR_NAMELESS : 0;
}

static int hevc_get_pps_id
(
    uint8_t *ps_ebsp,
    uint32_t ps_ebsp_length,
    uint8_t *ps_id
)
{
    /* the maximum number of bits of pps_id = 13: 0b0000001XXXXXX
     * (13 - 1) / 8 + 1 = 2 bytes
     * Why +1? Because there might be an emulation_prevention_three_byte. */
    lsmash_bits_t bits = { 0 };
    lsmash_bs_t   bs   = { 0 };
    uint8_t rbsp_buffer[3];
    uint8_t buffer     [3];
    bs.buffer.data  = buffer;
    bs.buffer.alloc = 3;
    lsmash_bits_init( &bits, &bs );
    uint64_t rbsp_size;
    int err = nalu_import_rbsp_from_ebsp( &bits, rbsp_buffer, &rbsp_size, ps_ebsp, LSMASH_MIN( ps_ebsp_length, 3 ) );
    if( err < 0 )
        return err;
    uint64_t pic_parameter_set_id = nalu_get_exp_golomb_ue( &bits );
    if( pic_parameter_set_id > HEVC_MAX_PPS_ID )
        return LSMASH_ERR_INVALID_DATA;
    *ps_id = pic_parameter_set_id;
    return bs.error ? LSMASH_ERR_NAMELESS : 0;
}

static inline int hevc_get_ps_id
(
    uint8_t                  *ps_ebsp,
    uint32_t                  ps_ebsp_length,
    uint8_t                  *ps_id,
    lsmash_hevc_dcr_nalu_type ps_type
)
{
    int (*get_ps_id)( uint8_t *ps_ebsp, uint32_t ps_ebsp_length, uint8_t *ps_id )
        = ps_type == HEVC_DCR_NALU_TYPE_VPS ? hevc_get_vps_id
        : ps_type == HEVC_DCR_NALU_TYPE_SPS ? hevc_get_sps_id
        : ps_type == HEVC_DCR_NALU_TYPE_PPS ? hevc_get_pps_id
        :                                     NULL;
    return get_ps_id ? get_ps_id( ps_ebsp, ps_ebsp_length, ps_id ) : LSMASH_ERR_INVALID_DATA;
}

static inline hevc_parameter_array_t *hevc_get_parameter_set_array
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type
)
{
    if( !param->parameter_arrays )
        return NULL;
    if( ps_type >= HEVC_DCR_NALU_TYPE_NUM )
        return NULL;
    return &param->parameter_arrays->ps_array[ps_type];
}

static inline lsmash_entry_list_t *hevc_get_parameter_set_list
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type
)
{
    if( !param->parameter_arrays )
        return NULL;
    if( ps_type >= HEVC_DCR_NALU_TYPE_NUM )
        return NULL;
    return param->parameter_arrays->ps_array[ps_type].list;
}

static lsmash_entry_t *hevc_get_ps_entry_from_param
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    uint8_t                            ps_id
)
{
    int (*get_ps_id)( uint8_t *ps_ebsp, uint32_t ps_ebsp_length, uint8_t *ps_id )
        = ps_type == HEVC_DCR_NALU_TYPE_VPS ? hevc_get_vps_id
        : ps_type == HEVC_DCR_NALU_TYPE_SPS ? hevc_get_sps_id
        : ps_type == HEVC_DCR_NALU_TYPE_PPS ? hevc_get_pps_id
        :                                     NULL;
    if( !get_ps_id )
        return NULL;
    lsmash_entry_list_t *list = hevc_get_parameter_set_list( param, ps_type );
    if( !list )
        return NULL;
    for( lsmash_entry_t *entry = list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return NULL;
        uint8_t param_ps_id;
        if( get_ps_id( ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                       ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH, &param_ps_id ) < 0 )
            return NULL;
        if( ps_id == param_ps_id )
            return entry;
    }
    return NULL;
}

static inline void  hevc_update_picture_type
(
    hevc_picture_info_t *picture,
    hevc_slice_info_t   *slice
)
{
    if( picture->type == HEVC_PICTURE_TYPE_I_P )
    {
        if( slice->type == HEVC_SLICE_TYPE_B )
            picture->type = HEVC_PICTURE_TYPE_I_P_B;
    }
    else if( picture->type == HEVC_PICTURE_TYPE_I )
    {
        if( slice->type == HEVC_SLICE_TYPE_P )
            picture->type = HEVC_PICTURE_TYPE_I_P;
        else if( slice->type == HEVC_SLICE_TYPE_B )
            picture->type = HEVC_PICTURE_TYPE_I_P_B;
    }
    else if( picture->type == HEVC_PICTURE_TYPE_NONE )
    {
        if( slice->type == HEVC_SLICE_TYPE_P )
            picture->type = HEVC_PICTURE_TYPE_I_P;
        else if( slice->type == HEVC_SLICE_TYPE_B )
            picture->type = HEVC_PICTURE_TYPE_I_P_B;
        else if( slice->type == HEVC_SLICE_TYPE_I )
            picture->type = HEVC_PICTURE_TYPE_I;
    }
#if 0
    fprintf( stderr, "Picture type = %s\n", picture->type == HEVC_PICTURE_TYPE_I_P   ? "P"
                                          : picture->type == HEVC_PICTURE_TYPE_I_P_B ? "B"
                                          : picture->type == HEVC_PICTURE_TYPE_I     ? "I" );
#endif
}

/* Shall be called at least once per picture. */
void hevc_update_picture_info_for_slice
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_slice_info_t   *slice
)
{
    assert( info );
    picture->has_primary |= !slice->dependent_slice_segment_flag;
    hevc_update_picture_type( picture, slice );
    /* Mark 'used' on active parameter sets. */
    uint8_t ps_id[3] = { slice->video_parameter_set_id, slice->seq_parameter_set_id, slice->pic_parameter_set_id };
    for( int i = 0; i < 3; i++ )
    {
        lsmash_hevc_dcr_nalu_type ps_type = (lsmash_hevc_dcr_nalu_type)i;
        lsmash_entry_t *entry = hevc_get_ps_entry_from_param( &info->hvcC_param, ps_type, ps_id[i] );
        if( entry && entry->data )
        {
            isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
            if( ps->unused )
                lsmash_append_hevc_dcr_nalu( &info->hvcC_param, ps_type, ps->nalUnit, ps->nalUnitLength );
        }
    }
    /* Discard this slice info. */
    slice->present = 0;
}

/* Shall be called exactly once per picture. */
void hevc_update_picture_info
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_slice_info_t   *slice,
    hevc_sps_t          *sps,
    hevc_sei_t          *sei
)
{
    picture->irap                 = slice->nalu_type >= HEVC_NALU_TYPE_BLA_W_LP    && slice->nalu_type <= HEVC_NALU_TYPE_CRA;
    picture->idr                  = slice->nalu_type == HEVC_NALU_TYPE_IDR_W_RADL  || slice->nalu_type == HEVC_NALU_TYPE_IDR_N_LP;
    picture->broken_link          = slice->nalu_type >= HEVC_NALU_TYPE_BLA_W_LP    && slice->nalu_type <= HEVC_NALU_TYPE_BLA_N_LP;
    picture->radl                 = slice->nalu_type == HEVC_NALU_TYPE_RADL_N      || slice->nalu_type == HEVC_NALU_TYPE_RADL_R;
    picture->rasl                 = slice->nalu_type == HEVC_NALU_TYPE_RASL_N      || slice->nalu_type == HEVC_NALU_TYPE_RASL_R;
    picture->sublayer_nonref      = slice->nalu_type <= HEVC_NALU_TYPE_RSV_VCL_R15 && ((slice->nalu_type & 0x01) == 0);
    picture->closed_rap           = slice->nalu_type >= HEVC_NALU_TYPE_BLA_W_RADL  && slice->nalu_type <= HEVC_NALU_TYPE_IDR_N_LP;
    picture->random_accessible    = picture->irap;
    picture->TemporalId           = slice->TemporalId;
    picture->pic_parameter_set_id = slice->pic_parameter_set_id;
    picture->poc_lsb              = slice->pic_order_cnt_lsb;
    hevc_update_picture_info_for_slice( info, picture, slice );
    picture->independent = (picture->type == HEVC_PICTURE_TYPE_I);
    picture->field_coded = sps->vui.field_seq_flag;
    if( sei->pic_timing.present )
    {
        if( sei->pic_timing.pic_struct < 13 )
        {
            static const uint8_t delta[13] = { 2, 1, 1, 2, 2, 3, 3, 4, 6, 1, 1, 1, 1 };
            picture->delta = delta[ sei->pic_timing.pic_struct ];
        }
        else
            /* Reserved values in the spec we refer to. */
            picture->delta = picture->field_coded ? 1 : 2;
        sei->pic_timing.present = 0;
    }
    else
        picture->delta = picture->field_coded ? 1 : 2;
    if( sei->recovery_point.present )
    {
        picture->random_accessible |= sei->recovery_point.present;
        picture->recovery_poc_cnt   = sei->recovery_point.recovery_poc_cnt;
        picture->broken_link       |= sei->recovery_point.broken_link_flag;
        sei->recovery_point.present = 0;
    }
    else
        picture->recovery_poc_cnt = 0;
}

static uint64_t hevc_get_ctb_address_in_tile_scan
(
    hevc_sps_t *sps,
    hevc_pps_t *pps,
    uint64_t    segment_address,
    uint64_t   *TileId
)
{
    uint64_t tbX = segment_address % sps->PicWidthInCtbsY;
    uint64_t tbY = segment_address / sps->PicWidthInCtbsY;
    uint32_t tileX = pps->num_tile_columns_minus1;
    for( uint32_t i = 0; i <= pps->num_tile_columns_minus1; i++ )
        if( tbX >= pps->colBd[i] )
            tileX = i;
    uint32_t tileY = pps->num_tile_rows_minus1;
    for( uint32_t j = 0; j <= pps->num_tile_rows_minus1; j++ )
        if( tbY >= pps->rowBd[j] )
            tileY = j;
    uint64_t CtbAddrInTs = 0;
    for( uint32_t i = 0; i < tileX; i++ )
        CtbAddrInTs += pps->rowHeight[tileY] * pps->colWidth[i];
    for( uint32_t j = 0; j < tileY; j++ )
        CtbAddrInTs += sps->PicWidthInCtbsY * pps->rowHeight[j];
    CtbAddrInTs += (tbY - pps->rowBd[tileY]) * pps->colWidth[tileX] + tbX - pps->colBd[tileX];
    *TileId = (uint64_t)tileY * (pps->num_tile_columns_minus1 + 1) + tileX;
    return CtbAddrInTs;
}

int hevc_find_au_delimit_by_slice_info
(
    hevc_info_t       *info,
    hevc_slice_info_t *slice,
    hevc_slice_info_t *prev_slice
)
{
    /* 7.4.2.4.5 Order of VCL NAL units and association to coded pictures
     *  - The first VCL NAL unit of the coded picture shall have first_slice_segment_in_pic_flag equal to 1. */
    if( slice->first_slice_segment_in_pic_flag )
        return 1;
    /* The value of TemporalId shall be the same for all VCL NAL units of an access unit. */
    if( slice->TemporalId != prev_slice->TemporalId )
        return 1;
    /* 7.4.2.4.5 Order of VCL NAL units and association to coded pictures
     * When either of the following conditions is true, both the current and the previous coded slice segment NAL units
     * shall belong to the same coded picture.
     *  - TileId[ CtbAddrRsToTs[ prev_slice->segment_address ] ] <  TileId[ CtbAddrRsToTs[ slice->segment_address ] ]
     *  - TileId[ CtbAddrRsToTs[ prev_slice->segment_address ] ] == TileId[ CtbAddrRsToTs[ slice->segment_address ] ]
     *   &&       CtbAddrRsToTs[ prev_slice->segment_address ]   <          CtbAddrRsToTs[ slice->segment_address ]
     */
    hevc_pps_t *prev_pps = hevc_get_pps( info->pps_list, prev_slice->pic_parameter_set_id );
    if( !prev_pps )
        return 0;
    hevc_sps_t *prev_sps = hevc_get_sps( info->sps_list, prev_pps->seq_parameter_set_id );
    if( !prev_sps )
        return 0;
    uint64_t currTileId;
    uint64_t prevTileId;
    uint64_t currCtbAddrInTs = hevc_get_ctb_address_in_tile_scan( &info->sps, &info->pps,      slice->segment_address, &currTileId );
    uint64_t prevCtbAddrInTs = hevc_get_ctb_address_in_tile_scan(   prev_sps,   prev_pps, prev_slice->segment_address, &prevTileId );
    if( prevTileId < currTileId )
        return 0;
    if( prevTileId == currTileId && prevCtbAddrInTs < currCtbAddrInTs )
        return 0;
    return 1;
}

int hevc_find_au_delimit_by_nalu_type
(
    uint8_t nalu_type,
    uint8_t prev_nalu_type
)
{
    /* 7.4.2.4.4 Order of NAL units and coded pictures and their association to access units */
    if( prev_nalu_type <= HEVC_NALU_TYPE_RSV_VCL31 )
        /* The first of any of the following NAL units after the last VCL NAL unit of a coded picture
         * specifies the start of a new access unit:
         *   - access unit delimiter NAL unit (when present)
         *   - VPS NAL unit (when present)
         *   - SPS NAL unit (when present)
         *   - PPS NAL unit (when present)
         *   - Prefix SEI NAL unit (when present)
         *   - NAL units with nal_unit_type in the range of RSV_NVCL41..RSV_NVCL44 (when present)
         *   - NAL units with nal_unit_type in the range of UNSPEC48..UNSPEC55 (when present)
         *   - first VCL NAL unit of a coded picture (always present) */
        return (nalu_type >= HEVC_NALU_TYPE_VPS        && nalu_type <= HEVC_NALU_TYPE_AUD)
            || (nalu_type == HEVC_NALU_TYPE_PREFIX_SEI)
            || (nalu_type >= HEVC_NALU_TYPE_RSV_NVCL41 && nalu_type <= HEVC_NALU_TYPE_RSV_NVCL44)
            || (nalu_type >= HEVC_NALU_TYPE_UNSPEC48   && nalu_type <= HEVC_NALU_TYPE_UNSPEC55);
    else if( prev_nalu_type == HEVC_NALU_TYPE_EOS )
        /* An end of sequence NAL unit shall be the last NAL unit in the access unit unless the next
         * NAL unit is an end of bitstream NAL unit. */
        return (nalu_type != HEVC_NALU_TYPE_EOB);
    else
        /* An end of bitstream NAL unit shall be the last NAL unit in the access unit.
         * Thus, the next NAL unit shall be the first NAL unit in the next access unit. */
        return (prev_nalu_type == HEVC_NALU_TYPE_EOB);
}

int hevc_supplement_buffer
(
    hevc_stream_buffer_t *sb,
    hevc_access_unit_t   *au,
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

static void hevc_bs_put_parameter_sets
(
    lsmash_bs_t         *bs,
    lsmash_entry_list_t *dcr_ps_list,
    uint32_t             max_dcr_ps_count
)
{
    uint32_t dcr_ps_count = 0;
    for( lsmash_entry_t *entry = dcr_ps_list->head; entry && dcr_ps_count < max_dcr_ps_count; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( ps && !ps->unused )
        {
            lsmash_bs_put_be16( bs, ps->nalUnitLength );
            lsmash_bs_put_bytes( bs, ps->nalUnitLength, ps->nalUnit );
        }
        else
            continue;
        ++dcr_ps_count;
    }
}

uint8_t *lsmash_create_hevc_specific_info
(
    lsmash_hevc_specific_parameters_t *param,
    uint32_t                          *data_length
)
{
    if( !param || !param->parameter_arrays || !data_length )
        return NULL;
    if( param->lengthSizeMinusOne != 0
     && param->lengthSizeMinusOne != 1
     && param->lengthSizeMinusOne != 3 )
        return NULL;
    hevc_parameter_array_t *param_arrays[HEVC_DCR_NALU_TYPE_NUM];
    lsmash_entry_list_t    *dcr_ps_list [HEVC_DCR_NALU_TYPE_NUM];
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
    {
        param_arrays[i] = &param->parameter_arrays->ps_array[i];
        dcr_ps_list [i] = param_arrays[i]->list;
    }
    /* VPS, SPS and PPS are mandatory. */
    if( !dcr_ps_list[0] || !dcr_ps_list[0]->head || dcr_ps_list[0]->entry_count == 0
     || !dcr_ps_list[1] || !dcr_ps_list[1]->head || dcr_ps_list[1]->entry_count == 0
     || !dcr_ps_list[2] || !dcr_ps_list[2]->head || dcr_ps_list[2]->entry_count == 0 )
        return NULL;
    /* Calculate enough buffer size. */
    static const uint32_t max_dcr_ps_count[HEVC_DCR_NALU_TYPE_NUM] =
        {
            HEVC_MAX_VPS_ID + 1,
            HEVC_MAX_SPS_ID + 1,
            HEVC_MAX_PPS_ID + 1,
            UINT16_MAX,
            UINT16_MAX
        };
    uint32_t ps_count[HEVC_DCR_NALU_TYPE_NUM] = { 0 };
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
        if( dcr_ps_list[i] )
            for( lsmash_entry_t *entry = dcr_ps_list[i]->head; entry && ps_count[i] < max_dcr_ps_count[i]; entry = entry->next )
            {
                isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
                if( !ps )
                    return NULL;
                if( ps->unused )
                    continue;
                ++ps_count[i];
            }
    /* Create an HEVCConfigurationBox */
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return NULL;
    lsmash_bs_put_be32( bs, 0 );                           /* box size */
    lsmash_bs_put_be32( bs, ISOM_BOX_TYPE_HVCC.fourcc );   /* box type: 'hvcC' */
    lsmash_bs_put_byte( bs, HVCC_CONFIGURATION_VERSION );  /* configurationVersion */
    uint8_t temp8 = (param->general_profile_space << 6)
                  | (param->general_tier_flag     << 5)
                  |  param->general_profile_idc;
    lsmash_bs_put_byte( bs, temp8 );
    lsmash_bs_put_be32( bs, param->general_profile_compatibility_flags );
    lsmash_bs_put_be32( bs, param->general_constraint_indicator_flags >> 16 );
    lsmash_bs_put_be16( bs, param->general_constraint_indicator_flags );
    lsmash_bs_put_byte( bs, param->general_level_idc );
    lsmash_bs_put_be16( bs, param->min_spatial_segmentation_idc | 0xF000 );
    lsmash_bs_put_byte( bs, param->parallelismType              | 0xFC );
    lsmash_bs_put_byte( bs, param->chromaFormat                 | 0xFC );
    lsmash_bs_put_byte( bs, param->bitDepthLumaMinus8           | 0xF8 );
    lsmash_bs_put_byte( bs, param->bitDepthChromaMinus8         | 0xF8 );
    lsmash_bs_put_be16( bs, param->avgFrameRate );
    temp8 = (param->constantFrameRate << 6)
          | (param->numTemporalLayers << 3)
          | (param->temporalIdNested  << 2)
          |  param->lengthSizeMinusOne;
    lsmash_bs_put_byte( bs, temp8 );
    uint8_t numOfArrays = !!ps_count[0]
                        + !!ps_count[1]
                        + !!ps_count[2]
                        + !!ps_count[3]
                        + !!ps_count[4];
    lsmash_bs_put_byte( bs, numOfArrays );
    for( uint8_t i = 0; i < numOfArrays; i++ )
    {
        temp8 = (param_arrays[i]->array_completeness << 7) | param_arrays[i]->NAL_unit_type;
        lsmash_bs_put_byte( bs, temp8 );
        lsmash_bs_put_be16( bs, ps_count[i] );
        hevc_bs_put_parameter_sets( bs, dcr_ps_list[i], ps_count[i] );
    }
    uint8_t *data = lsmash_bs_export_data( bs, data_length );
    lsmash_bs_cleanup( bs );
    /* Update box size. */
    LSMASH_SET_BE32( data, *data_length );
    return data;
}

static inline int hevc_validate_dcr_nalu_type
(
    lsmash_hevc_dcr_nalu_type ps_type,
    void                     *ps_data,
    uint32_t                  ps_length
)
{
    if( !ps_data || ps_length < 3 )
        return LSMASH_ERR_INVALID_DATA;
    if( ps_type != HEVC_DCR_NALU_TYPE_VPS
     && ps_type != HEVC_DCR_NALU_TYPE_SPS
     && ps_type != HEVC_DCR_NALU_TYPE_PPS
     && ps_type != HEVC_DCR_NALU_TYPE_PREFIX_SEI
     && ps_type != HEVC_DCR_NALU_TYPE_SUFFIX_SEI )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t nalu_type = (*((uint8_t *)ps_data) >> 1) & 0x3f;
    if( nalu_type != HEVC_NALU_TYPE_VPS
     && nalu_type != HEVC_NALU_TYPE_SPS
     && nalu_type != HEVC_NALU_TYPE_PPS
     && nalu_type != HEVC_NALU_TYPE_PREFIX_SEI
     && nalu_type != HEVC_NALU_TYPE_SUFFIX_SEI )
        return LSMASH_ERR_INVALID_DATA;
    if( (ps_type == HEVC_DCR_NALU_TYPE_VPS        && nalu_type != HEVC_NALU_TYPE_VPS)
     || (ps_type == HEVC_DCR_NALU_TYPE_SPS        && nalu_type != HEVC_NALU_TYPE_SPS)
     || (ps_type == HEVC_DCR_NALU_TYPE_PPS        && nalu_type != HEVC_NALU_TYPE_PPS)
     || (ps_type == HEVC_DCR_NALU_TYPE_PREFIX_SEI && nalu_type != HEVC_NALU_TYPE_PREFIX_SEI)
     || (ps_type == HEVC_DCR_NALU_TYPE_SUFFIX_SEI && nalu_type != HEVC_NALU_TYPE_SUFFIX_SEI) )
        return LSMASH_ERR_INVALID_DATA;
    return 0;
}

static lsmash_dcr_nalu_appendable hevc_check_vps_appendable
(
    lsmash_bits_t                     *bits,
    uint8_t                           *rbsp_buffer,
    lsmash_hevc_specific_parameters_t *param,
    uint8_t                           *ps_data,
    uint32_t                           ps_length,
    lsmash_entry_list_t               *ps_list
)
{
    hevc_vps_t vps;
    if( hevc_parse_vps_minimally( bits, &vps, rbsp_buffer,
                                  ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                  ps_length - HEVC_MIN_NALU_HEADER_LENGTH ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    /* The value of profile_space must be identical in all the parameter sets in a single HEVC Decoder Configuration Record. */
    if( vps.ptl.general.profile_space != param->general_profile_space )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    /* FIXME */
    if( vps.ptl.general.profile_idc != param->general_profile_idc )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return DCR_NALU_APPEND_ERROR;
        if( ps->unused )
            continue;
        uint8_t param_vps_id;
        if( hevc_get_vps_id( ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                             ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH, &param_vps_id ) < 0 )
            return DCR_NALU_APPEND_ERROR;
        if( param_vps_id == vps.video_parameter_set_id )
            /* VPS that has the same video_parameter_set_id already exists with different form. */
            return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    }
    return DCR_NALU_APPEND_POSSIBLE;
}

static lsmash_dcr_nalu_appendable hevc_check_sps_appendable
(
    lsmash_bits_t                     *bits,
    uint8_t                           *rbsp_buffer,
    lsmash_hevc_specific_parameters_t *param,
    uint8_t                           *ps_data,
    uint32_t                           ps_length,
    lsmash_entry_list_t               *ps_list
)
{
    hevc_sps_t sps;
    if( hevc_parse_sps_minimally( bits, &sps, rbsp_buffer,
                                  ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                  ps_length - HEVC_MIN_NALU_HEADER_LENGTH ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    lsmash_bits_empty( bits );
    /* The values of profile_space, chromaFormat, bitDepthLumaMinus8 and bitDepthChromaMinus8
     * must be identical in all the parameter sets in a single HEVC Decoder Configuration Record. */
    if( sps.ptl.general.profile_space != param->general_profile_space
     || sps.chroma_format_idc         != param->chromaFormat
     || sps.bit_depth_luma_minus8     != param->bitDepthLumaMinus8
     || sps.bit_depth_chroma_minus8   != param->bitDepthChromaMinus8 )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    /* FIXME; If the sequence parameter sets are marked with different profiles,
     * and the relevant profile compatibility flags are all zero,
     * then the stream may need examination to determine which profile, if any, the stream conforms to.
     * If the stream is not examined, or the examination reveals that there is no profile to which the stream conforms,
     * then the stream must be split into two or more sub-streams with separate configuration records in which these rules can be met. */
#if 0
    if( sps.ptl.general.profile_idc != param->general_profile_idc
     && (sps.ptl.general.profile_compatibility_flags & param->general_profile_compatibility_flags) )
#else
    if( sps.ptl.general.profile_idc != param->general_profile_idc )
#endif
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    /* Forbidden to duplicate SPS that has the same seq_parameter_set_id with different form within the same configuration record. */
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return DCR_NALU_APPEND_ERROR;
        if( ps->unused )
            continue;
        uint8_t param_sps_id;
        if( hevc_get_sps_id( ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                             ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH, &param_sps_id ) < 0 )
            return DCR_NALU_APPEND_ERROR;
        if( param_sps_id == sps.seq_parameter_set_id )
            /* SPS that has the same seq_parameter_set_id already exists with different form. */
            return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
        if( entry == ps_list->head )
        {
            /* Check if the cropped visual presentation sizes, the sample aspect ratios, the colour descriptions and
             * the default display windows are different. */
            hevc_sps_t first_sps;
            if( hevc_parse_sps_minimally( bits, &first_sps, rbsp_buffer,
                                          ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                                          ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH ) < 0 )
                return DCR_NALU_APPEND_ERROR;
            if( sps.cropped_width                    != first_sps.cropped_width
             || sps.cropped_height                   != first_sps.cropped_height
             || sps.vui.sar_width                    != first_sps.vui.sar_width
             || sps.vui.sar_height                   != first_sps.vui.sar_height
             || sps.vui.colour_primaries             != first_sps.vui.colour_primaries
             || sps.vui.transfer_characteristics     != first_sps.vui.transfer_characteristics
             || sps.vui.matrix_coeffs                != first_sps.vui.matrix_coeffs
             || sps.vui.video_full_range_flag        != first_sps.vui.video_full_range_flag
             || sps.vui.def_disp_win_offset.left  .n != first_sps.vui.def_disp_win_offset.left  .n
             || sps.vui.def_disp_win_offset.right .n != first_sps.vui.def_disp_win_offset.right .n
             || sps.vui.def_disp_win_offset.top   .n != first_sps.vui.def_disp_win_offset.top   .n
             || sps.vui.def_disp_win_offset.bottom.n != first_sps.vui.def_disp_win_offset.bottom.n )
                return DCR_NALU_APPEND_NEW_SAMPLE_ENTRY_REQUIRED;
        }
    }
    return DCR_NALU_APPEND_POSSIBLE;
}

static lsmash_dcr_nalu_appendable hevc_check_pps_appendable
(
    uint8_t             *ps_data,
    uint32_t             ps_length,
    lsmash_entry_list_t *ps_list
)
{
    uint8_t pps_id;
    if( hevc_get_pps_id( ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                         ps_length - HEVC_MIN_NALU_HEADER_LENGTH, &pps_id ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    for( lsmash_entry_t *entry = ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !ps )
            return DCR_NALU_APPEND_ERROR;
        if( ps->unused )
            continue;
        uint8_t param_pps_id;
        if( hevc_get_pps_id( ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                             ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH, &param_pps_id ) < 0 )
            return DCR_NALU_APPEND_ERROR;
        if( pps_id == param_pps_id )
            /* PPS that has the same pic_parameter_set_id already exists with different form. */
            return DCR_NALU_APPEND_NEW_DCR_REQUIRED;
    }
    return DCR_NALU_APPEND_POSSIBLE;
}

lsmash_dcr_nalu_appendable lsmash_check_hevc_dcr_nalu_appendable
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    void                              *_ps_data,
    uint32_t                           ps_length
)
{
    uint8_t *ps_data = _ps_data;
    if( !param )
        return DCR_NALU_APPEND_ERROR;
    if( hevc_validate_dcr_nalu_type( ps_type, ps_data, ps_length ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    /* Check whether the same parameter set already exsits or not. */
    lsmash_entry_list_t *ps_list = hevc_get_parameter_set_list( param, ps_type );
    if( !ps_list || !ps_list->head )
        return DCR_NALU_APPEND_POSSIBLE;    /* No parameter set */
    switch( nalu_check_same_ps_existence( ps_list, ps_data, ps_length ) )
    {
        case 0  : break;
        case 1  : return DCR_NALU_APPEND_DUPLICATED;    /* The same parameter set already exists. */
        default : return DCR_NALU_APPEND_ERROR;         /* An error occured. */
    }
    /* Check the number of parameter sets in HEVC Decoder Configuration Record. */
    uint32_t ps_count;
    if( nalu_get_ps_count( ps_list, &ps_count ) < 0 )
        return DCR_NALU_APPEND_ERROR;
    if( (ps_type == HEVC_DCR_NALU_TYPE_VPS        && ps_count >= HEVC_MAX_VPS_ID)
     || (ps_type == HEVC_DCR_NALU_TYPE_SPS        && ps_count >= HEVC_MAX_SPS_ID)
     || (ps_type == HEVC_DCR_NALU_TYPE_PPS        && ps_count >= HEVC_MAX_PPS_ID)
     || (ps_type == HEVC_DCR_NALU_TYPE_PREFIX_SEI && ps_count >= UINT16_MAX)
     || (ps_type == HEVC_DCR_NALU_TYPE_SUFFIX_SEI && ps_count >= UINT16_MAX) )
        return DCR_NALU_APPEND_NEW_DCR_REQUIRED;    /* No more appendable parameter sets. */
    if( ps_type == HEVC_DCR_NALU_TYPE_PREFIX_SEI
     || ps_type == HEVC_DCR_NALU_TYPE_SUFFIX_SEI )
        return DCR_NALU_APPEND_POSSIBLE;
    /* Check whether a new specific info is needed or not. */
    if( ps_type == HEVC_DCR_NALU_TYPE_PPS )
        /* PPS */
        return hevc_check_pps_appendable( ps_data, ps_length, ps_list );
    else
    {
        /* VPS or SPS
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
        lsmash_dcr_nalu_appendable appendable;
        if( ps_type == HEVC_DCR_NALU_TYPE_VPS )
            appendable = hevc_check_vps_appendable( bits, rbsp_buffer, param, ps_data, ps_length, ps_list );
        else
            appendable = hevc_check_sps_appendable( bits, rbsp_buffer, param, ps_data, ps_length, ps_list );
        lsmash_bits_adhoc_cleanup( bits );
        lsmash_free( rbsp_buffer );
        return appendable;
    }
}

static inline void hevc_specific_parameters_ready
(
    lsmash_hevc_specific_parameters_t *param
)
{
    param->general_profile_compatibility_flags = ~UINT32_C(0);
    param->general_constraint_indicator_flags  = 0x0000FFFFFFFFFFFF;
    param->min_spatial_segmentation_idc        = 0x0FFF;
    param->avgFrameRate                        = 0;     /* unspecified average frame rate */
    param->constantFrameRate                   = 2;
    param->numTemporalLayers                   = 0;
    param->temporalIdNested                    = 1;
}

static inline void hevc_specific_parameters_update_ptl
(
    lsmash_hevc_specific_parameters_t *param,
    hevc_ptl_t                        *ptl
)
{
    param->general_profile_space                = ptl->general.profile_space;
    param->general_tier_flag                    = LSMASH_MAX( param->general_tier_flag, ptl->general.tier_flag );
    param->general_profile_idc                  = ptl->general.profile_idc;
    param->general_profile_compatibility_flags &= ptl->general.profile_compatibility_flags;
    param->general_constraint_indicator_flags  &= ((uint64_t)ptl->general.progressive_source_flag    << 47)
                                                | ((uint64_t)ptl->general.interlaced_source_flag     << 46)
                                                | ((uint64_t)ptl->general.non_packed_constraint_flag << 45)
                                                | ((uint64_t)ptl->general.frame_only_constraint_flag << 44)
                                                |            ptl->general.reserved_zero_44bits;
    param->general_level_idc                    = LSMASH_MAX( param->general_level_idc, ptl->general.level_idc );
}

static inline void hevc_reorder_parameter_set_ascending_id
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    lsmash_entry_list_t               *ps_list,
    uint8_t                            ps_id
)
{
    lsmash_entry_t *entry = NULL;
    if( ps_id )
        for( int i = ps_id - 1; i; i-- )
        {
            entry = hevc_get_ps_entry_from_param( param, ps_type, i );
            if( entry )
                break;
        }
    int append_head = 0;
    if( !entry )
    {
        /* Couldn't find any parameter set with lower identifier.
         * Next, find parameter set with upper identifier. */
        int max_ps_id = ps_type == HEVC_DCR_NALU_TYPE_VPS ? HEVC_MAX_VPS_ID
                      : ps_type == HEVC_DCR_NALU_TYPE_SPS ? HEVC_MAX_SPS_ID
                      :                                     HEVC_MAX_PPS_ID;
        for( int i = ps_id + 1; i <= max_ps_id; i++ )
        {
            entry = hevc_get_ps_entry_from_param( param, ps_type, i );
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

int lsmash_append_hevc_dcr_nalu
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    void                              *_ps_data,
    uint32_t                           ps_length
)
{
    uint8_t *ps_data = _ps_data;
    if( !param || !ps_data || ps_length < 2 )
        return LSMASH_ERR_FUNCTION_PARAM;
    int err = hevc_alloc_parameter_arrays_if_needed( param );
    if( err < 0 )
        return err;
    hevc_parameter_array_t *ps_array = hevc_get_parameter_set_array( param, ps_type );
    if( !ps_array )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_entry_list_t *ps_list = ps_array->list;
    if( ps_type == HEVC_DCR_NALU_TYPE_PREFIX_SEI
     || ps_type == HEVC_DCR_NALU_TYPE_SUFFIX_SEI )
    {
        /* Append a SEI anyway. */
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
    if( ps_type != HEVC_DCR_NALU_TYPE_VPS
     && ps_type != HEVC_DCR_NALU_TYPE_SPS
     && ps_type != HEVC_DCR_NALU_TYPE_PPS )
        return LSMASH_ERR_FUNCTION_PARAM;
    /* Check if the same parameter set identifier already exists. */
    uint8_t ps_id;
    if( (err = hevc_get_ps_id( ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                               ps_length - HEVC_MIN_NALU_HEADER_LENGTH, &ps_id, ps_type )) < 0 )
        return err;
    lsmash_entry_t *entry = hevc_get_ps_entry_from_param( param, ps_type, ps_id );
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
            /* The same address could be given when called by hevc_update_picture_info_for_slice(). */
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
    lsmash_bits_t *bits        = NULL;
    uint8_t       *rbsp_buffer = NULL;
    uint32_t       ps_count;
    if( (err = nalu_get_ps_count( ps_list, &ps_count )) < 0 )
        goto fail;
    if( (bits = lsmash_bits_adhoc_create()) == NULL
     || (rbsp_buffer = lsmash_malloc( ps_length )) == NULL )
    {
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    /* Update specific info with VPS, SPS or PPS. */
    {
        if( ps_type == HEVC_DCR_NALU_TYPE_VPS )
        {
            hevc_vps_t vps;
            if( (err = hevc_parse_vps_minimally( bits, &vps, rbsp_buffer,
                                                 ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                                 ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                goto fail;
            if( ps_count == 1 )
            {
                /* Initialize if not initialized yet. */
                lsmash_entry_list_t *sps_list = hevc_get_parameter_set_list( param, HEVC_DCR_NALU_TYPE_SPS );
                uint32_t sps_count;
                if( (err = nalu_get_ps_count( sps_list, &sps_count )) < 0 )
                    goto fail;
                if( sps_count == 0 )
                    hevc_specific_parameters_ready( param );
            }
            hevc_specific_parameters_update_ptl( param, &vps.ptl );
            param->numTemporalLayers  = LSMASH_MAX( param->numTemporalLayers, vps.max_sub_layers_minus1 + 1 );
            //param->temporalIdNested  &= vps.temporal_id_nesting_flag;
        }
        else if( ps_type == HEVC_DCR_NALU_TYPE_SPS )
        {
            hevc_sps_t sps;
            if( (err = hevc_parse_sps_minimally( bits, &sps, rbsp_buffer,
                                                 ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                                 ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                goto fail;
            if( ps_count == 1 )
            {
                /* Initialize if not initialized yet. */
                lsmash_entry_list_t *vps_list = hevc_get_parameter_set_list( param, HEVC_DCR_NALU_TYPE_VPS );
                uint32_t vps_count;
                if( (err = nalu_get_ps_count( vps_list, &vps_count )) < 0 )
                    goto fail;
                if( vps_count == 0 )
                    hevc_specific_parameters_ready( param );
            }
            hevc_specific_parameters_update_ptl( param, &sps.ptl );
            param->min_spatial_segmentation_idc = LSMASH_MIN( param->min_spatial_segmentation_idc, sps.vui.min_spatial_segmentation_idc );
            param->chromaFormat                 = sps.chroma_format_idc;
            param->bitDepthLumaMinus8           = sps.bit_depth_luma_minus8;
            param->bitDepthChromaMinus8         = sps.bit_depth_chroma_minus8;
            param->numTemporalLayers            = LSMASH_MAX( param->numTemporalLayers, sps.max_sub_layers_minus1 + 1 );
            param->temporalIdNested            &= sps.temporal_id_nesting_flag;
            /* Check type of constant frame rate. */
            if( param->constantFrameRate )
            {
                int cfr;
                if( param->constantFrameRate == 2 )
                {
                    cfr = 1;
                    for( uint8_t i = 0; i <= sps.max_sub_layers_minus1; i++ )
                        cfr &= sps.vui.hrd.fixed_pic_rate_general_flag[i];
                }
                else
                    cfr = 0;
                if( cfr )
                    param->constantFrameRate = 2;
                else
                {
                    for( uint8_t i = 0; i <= sps.max_sub_layers_minus1; i++ )
                        cfr |= sps.vui.hrd.fixed_pic_rate_general_flag[i];
                    param->constantFrameRate = cfr;
                }
            }
#if 0
            /* FIXME: probably, we can get average frame rate according to C.3.3 Picture output. */
            if( param->constantFrameRate )
            {
                uint64_t interval = 0;
                for( uint8_t i = 0; i <= sps.max_sub_layers_minus1; i++ )
                    interval += sps.vui.num_units_in_tick * sps.vui.hrd.elemental_duration_in_tc_minus1[i];
                uint64_t frame_rate;
                if( interval )
                    frame_rate = ((256 * (2 - sps.vui.field_seq_flag) * (uint64_t)sps.vui.time_scale)
                               *  (sps.max_sub_layers_minus1 + 1)) / interval;
                else
                    frame_rate = 0;
                if( frame_rate != param->avgFrameRate && param->avgFrameRate )
                    param->constantFrameRate = 0;
                param->avgFrameRate = frame_rate;
            }
#endif
        }
        else
        {
            hevc_pps_t pps;
            if( (err = hevc_parse_pps_minimally( bits, &pps, rbsp_buffer,
                                                 ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                                 ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                goto fail;
            uint8_t parallelismType = 0;
#if 1   /* Replace 1 with 0 if parallelismType shall be set to 0 when min_spatial_segmentation_idc equal to 0. */

            if( pps.entropy_coding_sync_enabled_flag )
                parallelismType = pps.tiles_enabled_flag ? 0 : 3;
            else if( pps.tiles_enabled_flag )
                parallelismType = 2;
            else
                parallelismType = 1;
#else
            /* Parse SPS and check the value of min_spatial_segmentation_idc is equal to zero or not.
             * If the value is not equal to zero, update parallelismType appropriately.
             * If corresponding SPS is not found, set 0 to parallelismType. */
            entry = hevc_get_ps_entry_from_param( param, HEVC_DCR_NALU_TYPE_SPS, pps.seq_parameter_set_id );
            if( entry && entry->data )
            {
                ps = (isom_dcr_ps_entry_t *)entry->data;
                lsmash_bits_t *sps_bits = lsmash_bits_adhoc_create();
                if( !sps_bits )
                {
                    err = LSMASH_ERR_MEMORY_ALLOC;
                    goto fail;
                }
                uint8_t *sps_rbsp_buffer = lsmash_malloc( ps->nalUnitLength );
                if( !sps_rbsp_buffer )
                {
                    lsmash_bits_adhoc_cleanup( sps_bits );
                    err = LSMASH_ERR_MEMORY_ALLOC;
                    goto fail;
                }
                hevc_sps_t sps;
                if( hevc_parse_sps_minimally( sps_bits, &sps, sps_rbsp_buffer,
                                              ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                                              ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH ) == 0 )
                {
                    if( sps.vui.min_spatial_segmentation_idc )
                    {
                        if( pps.entropy_coding_sync_enabled_flag )
                            parallelismType = pps.tiles_enabled_flag ? 0 : 3;
                        else if( pps.tiles_enabled_flag )
                            parallelismType = 2;
                        else
                            parallelismType = 1;
                    }
                    else
                        parallelismType = 0;
                }
                lsmash_bits_adhoc_cleanup( sps_bits );
                lsmash_free( sps_rbsp_buffer );
            }
#endif
            if( ps_count == 1 )
                param->parallelismType = parallelismType;
            else if( param->parallelismType != parallelismType )
                param->parallelismType = 0;
        }
    }
    if( invoke_reorder )
        /* Add a new parameter set in order of ascending parameter set identifier. */
        hevc_reorder_parameter_set_ascending_id( param, ps_type, ps_list, ps_id );
    err = 0;
    goto clean;
fail:
    ps = (isom_dcr_ps_entry_t *)lsmash_list_get_entry_data( ps_list, ps_list->entry_count );
    if( ps )
        ps->unused = 1;
clean:
    lsmash_bits_adhoc_cleanup( bits );
    lsmash_free( rbsp_buffer );
    return err;
}

int hevc_try_to_append_dcr_nalu
(
    hevc_info_t              *info,
    lsmash_hevc_dcr_nalu_type ps_type,
    void                     *_ps_data,
    uint32_t                  ps_length
)
{
    uint8_t *ps_data = _ps_data;
    lsmash_dcr_nalu_appendable ret = lsmash_check_hevc_dcr_nalu_appendable( &info->hvcC_param, ps_type, ps_data, ps_length );
    lsmash_hevc_specific_parameters_t *param;
    switch( ret )
    {
        case DCR_NALU_APPEND_ERROR                     :    /* Error */
            return LSMASH_ERR_NAMELESS;
        case DCR_NALU_APPEND_NEW_DCR_REQUIRED          :    /* Mulitiple sample description is needed. */
        case DCR_NALU_APPEND_NEW_SAMPLE_ENTRY_REQUIRED :    /* Mulitiple sample description is needed. */
            param = &info->hvcC_param_next;
            info->hvcC_pending = 1;
            break;
        case DCR_NALU_APPEND_POSSIBLE :                     /* Appendable */
            param = info->hvcC_pending ? &info->hvcC_param_next : &info->hvcC_param;
            break;
        default :   /* No need to append */
            return DCR_NALU_APPEND_DUPLICATED;
    }
    int err;
    switch( ps_type )
    {
        case HEVC_DCR_NALU_TYPE_VPS :
            if( (err = hevc_parse_vps( info, info->buffer.rbsp,
                                       ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                       ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                return err;
            break;
        case HEVC_DCR_NALU_TYPE_SPS :
            if( (err = hevc_parse_sps( info, info->buffer.rbsp,
                                       ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                       ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                return err;
            break;
        case HEVC_DCR_NALU_TYPE_PPS :
            if( (err = hevc_parse_pps( info, info->buffer.rbsp,
                                       ps_data   + HEVC_MIN_NALU_HEADER_LENGTH,
                                       ps_length - HEVC_MIN_NALU_HEADER_LENGTH )) < 0 )
                return err;
            break;
        default :
            break;
    }
    return lsmash_append_hevc_dcr_nalu( param, ps_type, ps_data, ps_length );
}

static int hevc_move_dcr_nalu_entry
(
    lsmash_hevc_specific_parameters_t *dst_data,
    lsmash_hevc_specific_parameters_t *src_data,
    lsmash_hevc_dcr_nalu_type          ps_type
)
{
    lsmash_entry_list_t *src_ps_list = hevc_get_parameter_set_list( src_data, ps_type );
    lsmash_entry_list_t *dst_ps_list = hevc_get_parameter_set_list( dst_data, ps_type );
    assert( src_ps_list && dst_ps_list );
    for( lsmash_entry_t *src_entry = src_ps_list->head; src_entry; src_entry = src_entry->next )
    {
        isom_dcr_ps_entry_t *src_ps = (isom_dcr_ps_entry_t *)src_entry->data;
        if( !src_ps )
            continue;
        uint8_t src_ps_id;
        int err;
        if( (err = hevc_get_ps_id( src_ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                                   src_ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH,
                                   &src_ps_id, ps_type )) < 0 )
            return err;
        lsmash_entry_t *dst_entry;
        for( dst_entry = dst_ps_list->head; dst_entry; dst_entry = dst_entry->next )
        {
            isom_dcr_ps_entry_t *dst_ps = (isom_dcr_ps_entry_t *)dst_entry->data;
            if( !dst_ps )
                continue;
            uint8_t dst_ps_id;
            if( (err = hevc_get_ps_id( dst_ps->nalUnit       + HEVC_MIN_NALU_HEADER_LENGTH,
                                       dst_ps->nalUnitLength - HEVC_MIN_NALU_HEADER_LENGTH,
                                       &dst_ps_id, ps_type )) < 0 )
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

int hevc_move_pending_hvcC_param
(
    hevc_info_t *info
)
{
    assert( info );
    if( !info->hvcC_pending )
        return 0;
    /* Mark 'unused' on parameter sets within the decoder configuration record. */
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
    {
        lsmash_entry_list_t *ps_list = hevc_get_parameter_set_list( &info->hvcC_param, i );
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
    if( (err = hevc_move_dcr_nalu_entry( &info->hvcC_param, &info->hvcC_param_next, HEVC_DCR_NALU_TYPE_VPS        )) < 0
     || (err = hevc_move_dcr_nalu_entry( &info->hvcC_param, &info->hvcC_param_next, HEVC_DCR_NALU_TYPE_SPS        )) < 0
     || (err = hevc_move_dcr_nalu_entry( &info->hvcC_param, &info->hvcC_param_next, HEVC_DCR_NALU_TYPE_PPS        )) < 0
     || (err = hevc_move_dcr_nalu_entry( &info->hvcC_param, &info->hvcC_param_next, HEVC_DCR_NALU_TYPE_PREFIX_SEI )) < 0
     || (err = hevc_move_dcr_nalu_entry( &info->hvcC_param, &info->hvcC_param_next, HEVC_DCR_NALU_TYPE_SUFFIX_SEI )) < 0 )
        return err;
    /* Move to the pending. */
    lsmash_hevc_parameter_arrays_t *parameter_arrays = info->hvcC_param.parameter_arrays; /* Back up parameter arrays. */
    info->hvcC_param                  = info->hvcC_param_next;
    info->hvcC_param.parameter_arrays = parameter_arrays;
    /* No pending hvcC. */
    hevc_deallocate_parameter_arrays( &info->hvcC_param_next );
    uint8_t lengthSizeMinusOne = info->hvcC_param_next.lengthSizeMinusOne;
    memset( &info->hvcC_param_next, 0, sizeof(lsmash_hevc_specific_parameters_t) );
    info->hvcC_param_next.lengthSizeMinusOne = lengthSizeMinusOne;
    info->hvcC_pending = 0;
    return 0;
}

int lsmash_set_hevc_array_completeness
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    int                                array_completeness
)
{
    if( hevc_alloc_parameter_arrays_if_needed( param ) < 0 )
        return LSMASH_ERR_MEMORY_ALLOC;
    hevc_parameter_array_t *ps_array = hevc_get_parameter_set_array( param, ps_type );
    if( !ps_array )
        return LSMASH_ERR_FUNCTION_PARAM;
    ps_array->array_completeness = array_completeness;
    return 0;
}

int lsmash_get_hevc_array_completeness
(
    lsmash_hevc_specific_parameters_t *param,
    lsmash_hevc_dcr_nalu_type          ps_type,
    int                               *array_completeness
)
{
    if( hevc_alloc_parameter_arrays_if_needed( param ) < 0 )
        return LSMASH_ERR_MEMORY_ALLOC;
    hevc_parameter_array_t *ps_array = hevc_get_parameter_set_array( param, ps_type );
    if( !ps_array )
        return LSMASH_ERR_FUNCTION_PARAM;
    *array_completeness = ps_array->array_completeness;
    return 0;
}

static int hevc_parse_succeeded
(
    hevc_info_t                       *info,
    lsmash_hevc_specific_parameters_t *param
)
{
    int ret;
    if( info->vps.present
     && info->sps.present
     && info->pps.present )
    {
        *param = info->hvcC_param;
        /* Avoid freeing parameter sets. */
        info->hvcC_param.parameter_arrays = NULL;
        ret = 0;
    }
    else
        ret = LSMASH_ERR_INVALID_DATA;
    hevc_cleanup_parser( info );
    return ret;
}

static inline int hevc_parse_failed
(
    hevc_info_t *info,
    int          ret
)
{
    hevc_cleanup_parser( info );
    return ret;
}

int lsmash_setup_hevc_specific_parameters_from_access_unit
(
    lsmash_hevc_specific_parameters_t *param,
    uint8_t                           *data,
    uint32_t                           data_length
)
{
    if( !param || !data || data_length == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    hevc_info_t *info = &(hevc_info_t){ { 0 } };
    lsmash_bs_t *bs   = &(lsmash_bs_t){ 0 };
    int err = lsmash_bs_set_empty_stream( bs, data, data_length );
    if( err < 0 )
        return err;
    uint64_t sc_head_pos = nalu_find_first_start_code( bs );
    if( sc_head_pos == NALU_NO_START_CODE_FOUND )
        return LSMASH_ERR_INVALID_DATA;
    else if( sc_head_pos == NALU_IO_ERROR )
        return LSMASH_ERR_IO;
    if( (err = hevc_setup_parser( info, 1 )) < 0 )
        return hevc_parse_failed( info, err );
    hevc_stream_buffer_t *sb    = &info->buffer;
    hevc_slice_info_t    *slice = &info->slice;
    while( 1 )
    {
        hevc_nalu_header_t nuh;
        uint64_t start_code_length;
        uint64_t trailing_zero_bytes;
        uint64_t nalu_length = hevc_find_next_start_code( bs, &nuh, &start_code_length, &trailing_zero_bytes );
        if( nalu_length == NALU_NO_START_CODE_FOUND )
            /* For the last NALU. This NALU already has been parsed. */
            return hevc_parse_succeeded( info, param );
        uint8_t  nalu_type        = nuh.nal_unit_type;
        uint64_t next_sc_head_pos = sc_head_pos
                                  + start_code_length
                                  + nalu_length
                                  + trailing_zero_bytes;
        if( nalu_type == HEVC_NALU_TYPE_FD )
        {
            /* We don't support streams with both filler and HRD yet. Otherwise, just skip filler. */
            if( info->sps.vui.hrd.present )
                return hevc_parse_failed( info, LSMASH_ERR_PATCH_WELCOME );
        }
        else if( nalu_type <= HEVC_NALU_TYPE_RASL_R
             || (nalu_type >= HEVC_NALU_TYPE_BLA_W_LP && nalu_type <= HEVC_NALU_TYPE_CRA)
             || (nalu_type >= HEVC_NALU_TYPE_VPS      && nalu_type <= HEVC_NALU_TYPE_SUFFIX_SEI) )
        {
            /* Increase the buffer if needed. */
            uint64_t possible_au_length = NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
            if( sb->bank->buffer_size < possible_au_length
             && (err = hevc_supplement_buffer( sb, NULL, 2 * possible_au_length )) < 0 )
                return hevc_parse_failed( info, err );
            /* Get the EBSP of the current NALU here. */
            uint8_t *nalu = lsmash_bs_get_buffer_data( bs ) + start_code_length;
            if( nalu_type <= HEVC_NALU_TYPE_RSV_VCL31 )
            {
                /* VCL NALU (slice) */
                hevc_slice_info_t prev_slice = *slice;
                if( (err = hevc_parse_slice_segment_header( info, &nuh, sb->rbsp, nalu + nuh.length, nalu_length - nuh.length )) < 0 )
                    return hevc_parse_failed( info, err );
                if( prev_slice.present )
                {
                    /* Check whether the AU that contains the previous VCL NALU completed or not. */
                    if( hevc_find_au_delimit_by_slice_info( info, slice, &prev_slice ) )
                        /* The current NALU is the first VCL NALU of the primary coded picture of a new AU.
                         * Therefore, the previous slice belongs to that new AU. */
                        return hevc_parse_succeeded( info, param );
                }
                slice->present = 1;
            }
            else
            {
                if( hevc_find_au_delimit_by_nalu_type( nalu_type, info->prev_nalu_type ) )
                    /* The last slice belongs to the AU you want at this time. */
                    return hevc_parse_succeeded( info, param );
                switch( nalu_type )
                {
                    case HEVC_NALU_TYPE_VPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_VPS, nalu, nalu_length )) < 0 )
                            return hevc_parse_failed( info, err );
                        break;
                    case HEVC_NALU_TYPE_SPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_SPS, nalu, nalu_length )) < 0 )
                            return hevc_parse_failed( info, err );
                        break;
                    case HEVC_NALU_TYPE_PPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_PPS, nalu, nalu_length )) < 0 )
                            return hevc_parse_failed( info, err );
                        break;
                    default :
                        break;
                }
            }
        }
        /* Move to the first byte of the next start code. */
        info->prev_nalu_type = nalu_type;
        if( lsmash_bs_read_seek( bs, next_sc_head_pos, SEEK_SET ) != next_sc_head_pos )
            return hevc_parse_failed( info, LSMASH_ERR_NAMELESS );
        /* Check if no more data to read from the stream. */
        if( !lsmash_bs_is_end( bs, NALU_SHORT_START_CODE_LENGTH ) )
            sc_head_pos = next_sc_head_pos;
        else
            return hevc_parse_succeeded( info, param );
    }
}

int hevc_construct_specific_parameters
(
    lsmash_codec_specific_t *dst,
    lsmash_codec_specific_t *src
)
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < ISOM_BASEBOX_COMMON_SIZE + 7 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_hevc_specific_parameters_t *param = (lsmash_hevc_specific_parameters_t *)dst->data.structured;
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
    if( hevc_alloc_parameter_arrays_if_needed( param ) < 0 )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = lsmash_bs_import_data( bs, data, src->size - (data - src->data.unstructured) );
    if( err < 0 )
        goto fail;
    if( lsmash_bs_get_byte( bs ) != HVCC_CONFIGURATION_VERSION )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;  /* We don't support configurationVersion other than HVCC_CONFIGURATION_VERSION. */
    }
    uint8_t temp8 = lsmash_bs_get_byte( bs );
    param->general_profile_space               = (temp8 >> 6) & 0x03;
    param->general_tier_flag                   = (temp8 >> 5) & 0x01;
    param->general_profile_idc                 =  temp8       & 0x1F;
    param->general_profile_compatibility_flags = lsmash_bs_get_be32( bs );
    uint32_t temp32 = lsmash_bs_get_be32( bs );
    uint16_t temp16 = lsmash_bs_get_be16( bs );
    param->general_constraint_indicator_flags  = ((uint64_t)temp32 << 16) | temp16;
    param->general_level_idc                   = lsmash_bs_get_byte( bs );
    param->min_spatial_segmentation_idc        = lsmash_bs_get_be16( bs ) & 0x0FFF;
    param->parallelismType                     = lsmash_bs_get_byte( bs ) & 0x03;
    param->chromaFormat                        = lsmash_bs_get_byte( bs ) & 0x03;
    param->bitDepthLumaMinus8                  = lsmash_bs_get_byte( bs ) & 0x07;
    param->bitDepthChromaMinus8                = lsmash_bs_get_byte( bs ) & 0x07;
    param->avgFrameRate                        = lsmash_bs_get_be16( bs );
    temp8 = lsmash_bs_get_byte( bs );
    param->constantFrameRate                   = (temp8 >> 6) & 0x03;
    param->numTemporalLayers                   = (temp8 >> 3) & 0x07;
    param->temporalIdNested                    = (temp8 >> 2) & 0x01;
    param->lengthSizeMinusOne                  =  temp8       & 0x03;
    uint8_t numOfArrays                        = lsmash_bs_get_byte( bs );
    for( uint8_t i = 0; i < numOfArrays; i++ )
    {
        hevc_parameter_array_t param_array;
        memset( &param_array, 0, sizeof(hevc_parameter_array_t) );
        temp8 = lsmash_bs_get_byte( bs );
        param_array.array_completeness = (temp8 >> 7) & 0x01;
        param_array.NAL_unit_type      =  temp8       & 0x3F;
        param_array.list->entry_count  = lsmash_bs_get_be16( bs );
        if( param_array.NAL_unit_type == HEVC_NALU_TYPE_VPS
         || param_array.NAL_unit_type == HEVC_NALU_TYPE_SPS
         || param_array.NAL_unit_type == HEVC_NALU_TYPE_PPS
         || param_array.NAL_unit_type == HEVC_NALU_TYPE_PREFIX_SEI
         || param_array.NAL_unit_type == HEVC_NALU_TYPE_SUFFIX_SEI )
        {
            if( (err = nalu_get_dcr_ps( bs, param_array.list, param_array.list->entry_count )) < 0 )
                goto fail;
        }
        else
            for( uint16_t j = 0; j < param_array.list->entry_count; j++ )
            {
                uint16_t nalUnitLength = lsmash_bs_get_be16( bs );
                lsmash_bs_skip_bytes( bs, nalUnitLength );  /* nalUnit */
            }
        switch( param_array.NAL_unit_type )
        {
            case HEVC_NALU_TYPE_VPS :
                param->parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_VPS] = param_array;
                break;
            case HEVC_NALU_TYPE_SPS :
                param->parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SPS] = param_array;
                break;
            case HEVC_NALU_TYPE_PPS :
                param->parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PPS] = param_array;
                break;
            case HEVC_NALU_TYPE_PREFIX_SEI :
                param->parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_PREFIX_SEI] = param_array;
                break;
            case HEVC_NALU_TYPE_SUFFIX_SEI :
                param->parameter_arrays->ps_array[HEVC_DCR_NALU_TYPE_SUFFIX_SEI] = param_array;
                break;
            default :
                /* Discard unknown NALUs. */
                break;
        }
    }
    lsmash_bs_cleanup( bs );
    return 0;
fail:
    lsmash_bs_cleanup( bs );
    return err;
}

int hevc_print_codec_specific
(
    FILE          *fp,
    lsmash_file_t *file,
    isom_box_t    *box,
    int            level
)
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: HEVC Configuration Box]\n", isom_4cc2str( box->type.fourcc ) );
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
    uint8_t configurationVersion = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "configurationVersion = %"PRIu8"\n",                     configurationVersion );
    if( configurationVersion != HVCC_CONFIGURATION_VERSION )
    {
        lsmash_bs_cleanup( bs );
        return 0;
    }
    uint8_t temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "general_profile_space = %"PRIu8"\n",                    (temp8 >> 6) & 0x03 );
    lsmash_ifprintf( fp, indent, "general_tier_flag = %"PRIu8"\n",                        (temp8 >> 5) & 0x01 );
    lsmash_ifprintf( fp, indent, "general_profile_idc = %"PRIu8"\n",                       temp8       & 0x1F );
    lsmash_ifprintf( fp, indent, "general_profile_compatibility_flags = 0x%08"PRIx32"\n", lsmash_bs_get_be32( bs ) );
    uint32_t temp32 = lsmash_bs_get_be32( bs );
    uint16_t temp16 = lsmash_bs_get_be16( bs );
    lsmash_ifprintf( fp, indent, "general_constraint_indicator_flags = 0x%012"PRIx64"\n", ((uint64_t)temp32 << 16) | temp16 );
    uint8_t general_level_idc = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "general_level_idc = %"PRIu8" (Level %g)\n",             general_level_idc, general_level_idc / 30.0 );
    temp16 = lsmash_bs_get_be16( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n",                             (temp16 >> 12) & 0x0F );
    lsmash_ifprintf( fp, indent, "min_spatial_segmentation_idc = %"PRIu16"\n",             temp16        & 0x0FFF );
    temp8 = lsmash_bs_get_byte( bs );
    uint8_t parallelismType = temp8 & 0x03;
    static const char *parallelism_table[4] =
        {
            "Mixed types or Unknown",
            "Slice based",
            "Tile based",
            "Entropy coding synchronization based / WPP: Wavefront Parallel Processing"
        };
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n",                             (temp8 >> 2) & 0x3F );
    lsmash_ifprintf( fp, indent, "parallelismType = %"PRIu8" (%s)\n",                     parallelismType,
                                                                                          parallelism_table[parallelismType] );
    temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n",                             (temp8 >> 2) & 0x3F );
    lsmash_ifprintf( fp, indent, "chromaFormat = %"PRIu8"\n",                              temp8       & 0x03 );
    temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n",                             (temp8 >> 3) & 0x1F );
    lsmash_ifprintf( fp, indent, "bitDepthLumaMinus8 = %"PRIu8"\n",                        temp8       & 0x07 );
    temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n",                             (temp8 >> 3) & 0x1F );
    lsmash_ifprintf( fp, indent, "bitDepthChromaMinus8 = %"PRIu8"\n",                      temp8       & 0x07 );
    lsmash_ifprintf( fp, indent, "avgFrameRate = %"PRIu16"\n",                            lsmash_bs_get_be16( bs ) );
    temp8 = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "constantFrameRate = %"PRIu8"\n",                        (temp8 >> 6) & 0x03 );
    lsmash_ifprintf( fp, indent, "numTemporalLayers = %"PRIu8"\n",                        (temp8 >> 3) & 0x07 );
    lsmash_ifprintf( fp, indent, "temporalIdNested = %"PRIu8"\n",                         (temp8 >> 2) & 0x01 );
    lsmash_ifprintf( fp, indent, "lengthSizeMinusOne = %"PRIu8"\n",                        temp8       & 0x03 );
    uint8_t numOfArrays = lsmash_bs_get_byte( bs );
    lsmash_ifprintf( fp, indent, "numOfArrays = %"PRIu8"\n", numOfArrays );
    for( uint8_t i = 0; i < numOfArrays; i++ )
    {
        int array_indent = indent + 1;
        lsmash_ifprintf( fp, array_indent++, "array[%"PRIu8"]\n", i );
        temp8 = lsmash_bs_get_byte( bs );
        lsmash_ifprintf( fp, array_indent, "array_completeness = %"PRIu8"\n", (temp8 >> 7) & 0x01 );
        lsmash_ifprintf( fp, array_indent, "reserved = %"PRIu8"\n",           (temp8 >> 6) & 0x01 );
        lsmash_ifprintf( fp, array_indent, "NAL_unit_type = %"PRIu8"\n",       temp8       & 0x3F );
        uint16_t numNalus = lsmash_bs_get_be16( bs );
        lsmash_ifprintf( fp, array_indent, "numNalus = %"PRIu16"\n", numNalus );
        for( uint16_t j = 0; j < numNalus; j++ )
        {
            uint16_t nalUnitLength = lsmash_bs_get_be16( bs );
            lsmash_bs_skip_bytes( bs, nalUnitLength );
            lsmash_ifprintf( fp, array_indent, "nalUnit[%"PRIu16"]\n", j );
            lsmash_ifprintf( fp, array_indent + 1, "nalUnitLength = %"PRIu16"\n", nalUnitLength );
        }
    }
    lsmash_bs_cleanup( bs );
    return 0;
}

static inline int hevc_copy_dcr_nalu_array
(
    lsmash_hevc_specific_parameters_t *dst_data,
    lsmash_hevc_specific_parameters_t *src_data,
    lsmash_hevc_dcr_nalu_type          ps_type
)
{
    hevc_parameter_array_t *src_ps_array = hevc_get_parameter_set_array( src_data, ps_type );
    hevc_parameter_array_t *dst_ps_array = hevc_get_parameter_set_array( dst_data, ps_type );
    assert( src_ps_array && dst_ps_array );
    dst_ps_array->array_completeness = src_ps_array->array_completeness;
    dst_ps_array->NAL_unit_type      = src_ps_array->NAL_unit_type;
    lsmash_entry_list_t *src_ps_list = src_ps_array->list;
    lsmash_entry_list_t *dst_ps_list = dst_ps_array->list;
    for( lsmash_entry_t *entry = src_ps_list->head; entry; entry = entry->next )
    {
        isom_dcr_ps_entry_t *src_ps = (isom_dcr_ps_entry_t *)entry->data;
        if( !src_ps || src_ps->unused )
            continue;
        isom_dcr_ps_entry_t *dst_ps = isom_create_ps_entry( src_ps->nalUnit, src_ps->nalUnitLength );
        if( !dst_ps )
        {
            hevc_deallocate_parameter_arrays( dst_data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        if( lsmash_list_add_entry( dst_ps_list, dst_ps ) < 0 )
        {
            hevc_deallocate_parameter_arrays( dst_data );
            isom_remove_dcr_ps( dst_ps );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
    }
    return 0;
}

int hevc_copy_codec_specific
(
    lsmash_codec_specific_t *dst,
    lsmash_codec_specific_t *src
)
{
    assert( src && src->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && src->data.structured );
    assert( dst && dst->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && dst->data.structured );
    lsmash_hevc_specific_parameters_t *src_data = (lsmash_hevc_specific_parameters_t *)src->data.structured;
    lsmash_hevc_specific_parameters_t *dst_data = (lsmash_hevc_specific_parameters_t *)dst->data.structured;
    hevc_deallocate_parameter_arrays( dst_data );
    *dst_data = *src_data;
    if( !src_data->parameter_arrays )
        return 0;
    dst_data->parameter_arrays = hevc_alloc_parameter_arrays();
    if( !dst_data->parameter_arrays )
        return LSMASH_ERR_MEMORY_ALLOC;
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
    {
        int err = hevc_copy_dcr_nalu_array( dst_data, src_data, (lsmash_hevc_dcr_nalu_type)i );
        if( err < 0 )
            return err;
    }
    return 0;
}

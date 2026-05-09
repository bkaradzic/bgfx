/*****************************************************************************
 * nalu_imp.c
 *****************************************************************************
 * Copyright (C) 2011-2017 L-SMASH project
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

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/***************************************************************************
    H.264 importer
    ITU-T Recommendation H.264 (04/13)
    ISO/IEC 14496-15:2010
***************************************************************************/
#include "codecs/h264.h"
#include "codecs/nalu.h"

typedef struct
{
    h264_info_t            info;
    lsmash_entry_list_t    avcC_list[1];    /* stored as lsmash_codec_specific_t */
    lsmash_media_ts_list_t ts_list;
    uint32_t max_au_length;
    uint32_t num_undecodable;
    uint32_t avcC_number;
    uint32_t last_delta;
    uint64_t last_intra_cts;
    uint64_t last_sync_cts;
    uint64_t sc_head_pos;
    uint8_t  composition_reordering_present;
    uint8_t  field_pic_present;
} h264_importer_t;

typedef struct
{
    int64_t  poc;
    uint32_t delta;
    uint16_t poc_delta;
    uint16_t reset;
} nal_pic_timing_t;

static void remove_h264_importer( h264_importer_t *h264_imp )
{
    if( !h264_imp )
        return;
    lsmash_list_remove_entries( h264_imp->avcC_list );
    h264_cleanup_parser( &h264_imp->info );
    lsmash_free( h264_imp->ts_list.timestamp );
    lsmash_free( h264_imp );
}

static void h264_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_h264_importer( importer->info );
}

static h264_importer_t *create_h264_importer( importer_t *importer )
{
    h264_importer_t *h264_imp = lsmash_malloc_zero( sizeof(h264_importer_t) );
    if( !h264_imp )
        return NULL;
    if( h264_setup_parser( &h264_imp->info, 0 ) < 0 )
    {
        remove_h264_importer( h264_imp );
        return NULL;
    }
    lsmash_list_init( h264_imp->avcC_list, lsmash_destroy_codec_specific_data );
    return h264_imp;
}

static inline int h264_complete_au( h264_access_unit_t *au, int probe )
{
    if( !au->picture.has_primary || au->incomplete_length == 0 )
        return 0;
    if( !probe )
        memcpy( au->data, au->incomplete_data, au->incomplete_length );
    au->length              = au->incomplete_length;
    au->incomplete_length   = 0;
    au->picture.has_primary = 0;
    return 1;
}

static void h264_append_nalu_to_au( h264_access_unit_t *au, uint8_t *src_nalu, uint32_t nalu_length, int probe )
{
    if( !probe )
    {
        uint8_t *dst_nalu = au->incomplete_data + au->incomplete_length + NALU_DEFAULT_NALU_LENGTH_SIZE;
        for( int i = NALU_DEFAULT_NALU_LENGTH_SIZE; i; i-- )
            *(dst_nalu - i) = (nalu_length >> ((i - 1) * 8)) & 0xff;
        memcpy( dst_nalu, src_nalu, nalu_length );
    }
    /* Note: au->incomplete_length shall be 0 immediately after AU has completed.
     * Therefore, possible_au_length in h264_get_access_unit_internal() can't be used here
     * to avoid increasing AU length monotonously through the entire stream. */
    au->incomplete_length += NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
}

static int h264_get_au_internal_succeeded( h264_importer_t *h264_imp, h264_access_unit_t *au )
{
    au->number += 1;
    return 0;
}

static int h264_get_au_internal_failed( h264_importer_t *h264_imp, h264_access_unit_t *au, int complete_au, int ret )
{
    if( complete_au )
        au->number += 1;
    return ret;
}

static lsmash_video_summary_t *h264_create_summary
(
    lsmash_h264_specific_parameters_t *param,
    h264_sps_t                        *sps,
    uint32_t                           max_au_length
)
{
    lsmash_video_summary_t *summary = (lsmash_video_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_VIDEO );
    if( !summary )
        return NULL;
    /* Update summary here.
     * max_au_length is set at the last of mp4sys_h264_probe function. */
    lsmash_codec_specific_t *cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264,
                                                                     LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !cs )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    cs->data.unstructured = lsmash_create_h264_specific_info( param, &cs->size );
    if( !cs->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, cs ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    summary->sample_type            = ISOM_CODEC_TYPE_AVC1_VIDEO;
    summary->max_au_length          = max_au_length;
    summary->timescale              = sps->vui.time_scale;
    summary->timebase               = sps->vui.num_units_in_tick;
    summary->vfr                    = !sps->vui.fixed_frame_rate_flag;
    summary->sample_per_field       = 0;
    summary->width                  = sps->cropped_width;
    summary->height                 = sps->cropped_height;
    summary->par_h                  = sps->vui.sar_width;
    summary->par_v                  = sps->vui.sar_height;
    summary->color.primaries_index  = sps->vui.colour_primaries;
    summary->color.transfer_index   = sps->vui.transfer_characteristics;
    summary->color.matrix_index     = sps->vui.matrix_coefficients;
    summary->color.full_range       = sps->vui.video_full_range_flag;
    return summary;
}

static int h264_store_codec_specific
(
    h264_importer_t                   *h264_imp,
    lsmash_h264_specific_parameters_t *avcC_param
)
{
    lsmash_codec_specific_t *src_cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264,
                                                                         LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !src_cs )
        return LSMASH_ERR_NAMELESS;
    lsmash_h264_specific_parameters_t *src_param = (lsmash_h264_specific_parameters_t *)src_cs->data.structured;
    *src_param = *avcC_param;
    lsmash_codec_specific_t *dst_cs = lsmash_convert_codec_specific_format( src_cs, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    src_param->parameter_sets = NULL;   /* Avoid freeing parameter sets within avcC_param. */
    lsmash_destroy_codec_specific_data( src_cs );
    if( !dst_cs )
    {
        lsmash_destroy_codec_specific_data( dst_cs );
        return LSMASH_ERR_NAMELESS;
    }
    if( lsmash_list_add_entry( h264_imp->avcC_list, dst_cs ) < 0 )
    {
        lsmash_destroy_codec_specific_data( dst_cs );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static inline void h264_new_access_unit
(
    h264_access_unit_t *au
)
{
    au->length                     = 0;
    au->picture.type               = H264_PICTURE_TYPE_NONE;
    au->picture.random_accessible  = 0;
    au->picture.recovery_frame_cnt = 0;
    au->picture.has_mmco5          = 0;
    au->picture.has_redundancy     = 0;
    au->picture.broken_link_flag   = 0;
}

/* If probe equals 0, don't get the actual data (EBPS) of an access unit and only parse NALU.
 * Currently, you can get AU of AVC video elemental stream only, not AVC parameter set elemental stream defined in 14496-15. */
static int h264_get_access_unit_internal
(
    importer_t *importer,
    int         probe
)
{
    h264_importer_t      *h264_imp = (h264_importer_t *)importer->info;
    h264_info_t          *info     = &h264_imp->info;
    h264_slice_info_t    *slice    = &info->slice;
    h264_access_unit_t   *au       = &info->au;
    h264_picture_info_t  *picture  = &au->picture;
    h264_stream_buffer_t *sb       = &info->buffer;
    lsmash_bs_t          *bs       = importer->bs;
    int complete_au = 0;
    h264_new_access_unit( au );
    while( 1 )
    {
        h264_nalu_header_t nuh;
        uint64_t start_code_length;
        uint64_t trailing_zero_bytes;
        uint64_t nalu_length = h264_find_next_start_code( bs, &nuh, &start_code_length, &trailing_zero_bytes );
        if( nalu_length == NALU_NO_START_CODE_FOUND )
        {
            /* For the last NALU.
             * This NALU already has been appended into the latest access unit and parsed. */
            h264_update_picture_info( info, picture, slice, &info->sei );
            complete_au = h264_complete_au( au, probe );
            if( complete_au )
                return h264_get_au_internal_succeeded( h264_imp, au );
            else
                return h264_get_au_internal_failed( h264_imp, au, complete_au, LSMASH_ERR_INVALID_DATA );
        }
        uint8_t  nalu_type        = nuh.nal_unit_type;
        uint64_t next_sc_head_pos = h264_imp->sc_head_pos
                                  + start_code_length
                                  + nalu_length
                                  + trailing_zero_bytes;
#if 0
        if( probe )
        {
            fprintf( stderr, "NALU type: %"PRIu8"                    \n", nalu_type );
            fprintf( stderr, "    NALU header position: %"PRIx64"    \n", h264_imp->sc_head_pos + start_code_length );
            fprintf( stderr, "    EBSP position: %"PRIx64"           \n", h264_imp->sc_head_pos + start_code_length + nuh.length );
            fprintf( stderr, "    EBSP length: %"PRIx64" (%"PRIu64") \n", nalu_length - nuh.length, nalu_length - nuh.length );
            fprintf( stderr, "    trailing_zero_bytes: %"PRIx64"     \n", trailing_zero_bytes );
            fprintf( stderr, "    Next start code position: %"PRIx64"\n", next_sc_head_pos );
        }
#endif
        if( nalu_type == H264_NALU_TYPE_FD )
        {
            /* We don't support streams with both filler and HRD yet.
             * Otherwise, just skip filler because 'avc1' and 'avc2' samples are forbidden to use filler. */
            if( info->sps.vui.hrd.present )
                return h264_get_au_internal_failed( h264_imp, au, complete_au, LSMASH_ERR_PATCH_WELCOME );
        }
        else if( (nalu_type >= H264_NALU_TYPE_SLICE_N_IDR && nalu_type <= H264_NALU_TYPE_SPS_EXT)
              || nalu_type == H264_NALU_TYPE_SLICE_AUX )
        {
            int err;
            /* Increase the buffer if needed. */
            uint64_t possible_au_length = au->incomplete_length + NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
            if( sb->bank->buffer_size < possible_au_length
             && (err = h264_supplement_buffer( sb, au, 2 * possible_au_length )) < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to increase the buffer size.\n" );
                return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
            }
            /* Get the EBSP of the current NALU here.
             * AVC elemental stream defined in 14496-15 can recognizes from 0 to 13, and 19 of nal_unit_type.
             * We don't support SVC and MVC elemental stream defined in 14496-15 yet. */
            uint8_t *nalu = lsmash_bs_get_buffer_data( bs ) + start_code_length;
            if( nalu_type >= H264_NALU_TYPE_SLICE_N_IDR && nalu_type <= H264_NALU_TYPE_SLICE_IDR )
            {
                /* VCL NALU (slice) */
                h264_slice_info_t prev_slice = *slice;
                if( (err = h264_parse_slice( info, &nuh, sb->rbsp, nalu + nuh.length, nalu_length - nuh.length )) < 0 )
                    return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
                if( probe && info->avcC_pending )
                {
                    /* Copy and append a Codec Specific info. */
                    if( (err = h264_store_codec_specific( h264_imp, &info->avcC_param )) < 0 )
                        return err;
                }
                if( (err = h264_move_pending_avcC_param( info )) < 0 )
                    return err;
                if( prev_slice.present )
                {
                    /* Check whether the AU that contains the previous VCL NALU completed or not. */
                    if( h264_find_au_delimit_by_slice_info( slice, &prev_slice ) )
                    {
                        /* The current NALU is the first VCL NALU of the primary coded picture of an new AU.
                         * Therefore, the previous slice belongs to the AU you want at this time. */
                        h264_update_picture_info( info, picture, &prev_slice, &info->sei );
                        complete_au = h264_complete_au( au, probe );
                    }
                    else
                        h264_update_picture_info_for_slice( info, picture, &prev_slice );
                }
                h264_append_nalu_to_au( au, nalu, nalu_length, probe );
                slice->present = 1;
            }
            else
            {
                if( h264_find_au_delimit_by_nalu_type( nalu_type, info->prev_nalu_type ) )
                {
                    /* The last slice belongs to the AU you want at this time. */
                    h264_update_picture_info( info, picture, slice, &info->sei );
                    complete_au = h264_complete_au( au, probe );
                }
                switch( nalu_type )
                {
                    case H264_NALU_TYPE_SEI :
                    {
                        if( (err = h264_parse_sei( info->bits, &info->sps, &info->sei, sb->rbsp,
                                                   nalu        + nuh.length,
                                                   nalu_length - nuh.length )) < 0 )
                            return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
                        h264_append_nalu_to_au( au, nalu, nalu_length, probe );
                        break;
                    }
                    case H264_NALU_TYPE_SPS :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_SPS, nalu, nalu_length )) < 0 )
                            return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
                        break;
                    case H264_NALU_TYPE_PPS :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_PPS, nalu, nalu_length )) < 0 )
                            return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
                        break;
                    case H264_NALU_TYPE_AUD :   /* We drop access unit delimiters. */
                        break;
                    case H264_NALU_TYPE_SPS_EXT :
                        if( (err = h264_try_to_append_parameter_set( info, H264_PARAMETER_SET_TYPE_SPSEXT, nalu, nalu_length )) < 0 )
                            return h264_get_au_internal_failed( h264_imp, au, complete_au, err );
                        break;
                    default :
                        h264_append_nalu_to_au( au, nalu, nalu_length, probe );
                        break;
                }
                if( info->avcC_pending )
                    importer->status = IMPORTER_CHANGE;
            }
        }
        /* Move to the first byte of the next start code. */
        info->prev_nalu_type = nalu_type;
        if( lsmash_bs_read_seek( bs, next_sc_head_pos, SEEK_SET ) != next_sc_head_pos )
        {
            lsmash_log( importer, LSMASH_LOG_ERROR, "failed to seek the next start code.\n" );
            return h264_get_au_internal_failed( h264_imp, au, complete_au, LSMASH_ERR_NAMELESS );
        }
        /* Check if no more data to read from the stream. */
        if( !lsmash_bs_is_end( bs, NALU_SHORT_START_CODE_LENGTH ) )
            h264_imp->sc_head_pos = next_sc_head_pos;
        /* If there is no more data in the stream, and flushed chunk of NALUs, flush it as complete AU here. */
        else if( au->incomplete_length && au->length == 0 )
        {
            h264_update_picture_info( info, picture, slice, &info->sei );
            h264_complete_au( au, probe );
            return h264_get_au_internal_succeeded( h264_imp, au );
        }
        if( complete_au )
            return h264_get_au_internal_succeeded( h264_imp, au );
    }
}

static inline void h264_importer_check_eof( importer_t *importer, h264_access_unit_t *au )
{
    /* AVC byte stream NALU consists of at least 4 bytes (start-code + NALU-header). */
    if( lsmash_bs_is_end( importer->bs, NALU_SHORT_START_CODE_LENGTH ) && au->incomplete_length == 0 )
        importer->status = IMPORTER_EOF;
    else if( importer->status != IMPORTER_CHANGE )
        importer->status = IMPORTER_OK;
}

static int h264_importer_get_accessunit
(
    importer_t       *importer,
    uint32_t          track_number,
    lsmash_sample_t **p_sample
)
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    h264_importer_t *h264_imp = (h264_importer_t *)importer->info;
    h264_info_t     *info     = &h264_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    int err = h264_get_access_unit_internal( importer, 0 );
    if( err < 0 )
    {
        importer->status = IMPORTER_ERROR;
        return err;
    }
    h264_importer_check_eof( importer, &info->au );
    if( importer->status == IMPORTER_CHANGE && !info->avcC_pending )
        current_status = IMPORTER_CHANGE;
    if( current_status == IMPORTER_CHANGE )
    {
        /* Update the active summary. */
        lsmash_codec_specific_t *cs = (lsmash_codec_specific_t *)lsmash_list_get_entry_data( h264_imp->avcC_list, ++ h264_imp->avcC_number );
        if( !cs )
            return LSMASH_ERR_NAMELESS;
        lsmash_h264_specific_parameters_t *avcC_param = (lsmash_h264_specific_parameters_t *)cs->data.structured;
        lsmash_video_summary_t *summary = h264_create_summary( avcC_param, &info->sps, h264_imp->max_au_length );
        if( !summary )
            return LSMASH_ERR_NAMELESS;
        lsmash_list_remove_entry( importer->summaries, track_number );
        if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
        {
            lsmash_cleanup_summary( (lsmash_summary_t *)summary );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        importer->status = IMPORTER_OK;
    }
    lsmash_sample_t *sample = lsmash_create_sample( h264_imp->max_au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    h264_access_unit_t  *au      = &info->au;
    h264_picture_info_t *picture = &au->picture;
    sample->dts = h264_imp->ts_list.timestamp[ au->number - 1 ].dts;
    sample->cts = h264_imp->ts_list.timestamp[ au->number - 1 ].cts;
    if( au->number < h264_imp->num_undecodable )
        sample->prop.leading = ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
    else
        sample->prop.leading =
              picture->independent                    ? ISOM_SAMPLE_IS_NOT_LEADING
            : sample->cts >= h264_imp->last_intra_cts ? ISOM_SAMPLE_IS_NOT_LEADING
            : sample->cts <  h264_imp->last_sync_cts  ? ISOM_SAMPLE_IS_DECODABLE_LEADING
            :                                           ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
    if( h264_imp->composition_reordering_present && !picture->disposable && !picture->idr )
        sample->prop.allow_earlier = QT_SAMPLE_EARLIER_PTS_ALLOWED;
    sample->prop.independent = picture->independent    ? ISOM_SAMPLE_IS_INDEPENDENT : ISOM_SAMPLE_IS_NOT_INDEPENDENT;
    sample->prop.disposable  = picture->disposable     ? ISOM_SAMPLE_IS_DISPOSABLE  : ISOM_SAMPLE_IS_NOT_DISPOSABLE;
    sample->prop.redundant   = picture->has_redundancy ? ISOM_SAMPLE_HAS_REDUNDANCY : ISOM_SAMPLE_HAS_NO_REDUNDANCY;
    sample->prop.post_roll.identifier = picture->frame_num;
    if( picture->random_accessible )
    {
        if( picture->idr )
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
        else if( picture->recovery_frame_cnt )
        {
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_POST_ROLL_START;
            sample->prop.post_roll.complete = (picture->frame_num + picture->recovery_frame_cnt) % info->sps.MaxFrameNum;
        }
        else
        {
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP;
            if( !picture->broken_link_flag )
                sample->prop.ra_flags |= QT_SAMPLE_RANDOM_ACCESS_FLAG_PARTIAL_SYNC;
        }
    }
    if( picture->independent )
        h264_imp->last_intra_cts = sample->cts;
    if( picture->idr )
        h264_imp->last_sync_cts  = sample->cts;
    sample->length = au->length;
    memcpy( sample->data, au->data, au->length );
    return current_status;
}

static void nalu_deduplicate_poc
(
    nal_pic_timing_t *npt,
    uint32_t         *max_composition_delay,
    uint32_t          num_access_units,
    uint32_t          max_num_reorder_pics
)
{
    /* Deduplicate POCs. */
    int64_t  poc_offset            = 0;
    int64_t  poc_min               = 0;
    int64_t  invalid_poc_min       = 0;
    uint32_t last_poc_reset        = UINT32_MAX;
    uint32_t invalid_poc_start     = 0;
    int      invalid_poc_present   = 0;
    for( uint32_t i = 0; ; i++ )
    {
        if( i < num_access_units && npt[i].poc != 0 && !npt[i].reset )
        {
            /* poc_offset is not added to each POC here.
             * It is done when we encounter the next coded video sequence. */
            if( npt[i].poc < 0 )
            {
                /* Pictures with negative POC shall precede IDR-picture in composition order.
                 * The minimum POC is added to poc_offset when we encounter the next coded video sequence. */
                if( last_poc_reset == UINT32_MAX || i > last_poc_reset + max_num_reorder_pics )
                {
                    if( !invalid_poc_present )
                    {
                        invalid_poc_present = 1;
                        invalid_poc_start   = i;
                    }
                    if( invalid_poc_min > npt[i].poc )
                        invalid_poc_min = npt[i].poc;
                }
                else if( poc_min > npt[i].poc )
                {
                    poc_min = npt[i].poc;
                    *max_composition_delay = LSMASH_MAX( *max_composition_delay, i - last_poc_reset );
                }
            }
            continue;
        }
        /* Encountered a new coded video sequence or no more POCs.
         * Add poc_offset to each POC of the previous coded video sequence. */
        poc_offset -= poc_min;
        int64_t poc_max = 0;
        for( uint32_t j = last_poc_reset; j < i + !!npt[i].reset; j++ )
            if( npt[j].poc >= 0 || (j <= last_poc_reset + max_num_reorder_pics) )
            {
                npt[j].poc += poc_offset;
                if( poc_max < npt[j].poc )
                    poc_max = npt[j].poc;
            }
        poc_offset = poc_max + 1;
        if( invalid_poc_present )
        {
            /* Pictures with invalid negative POC is probably supposed to be composited
             * both before the next coded video sequence and after the current one. */
            poc_offset -= invalid_poc_min;
            for( uint32_t j = invalid_poc_start; j < i + !!npt[i].reset; j++ )
                if( npt[j].poc < 0 )
                {
                    npt[j].poc += poc_offset;
                    if( poc_max < npt[j].poc )
                        poc_max = npt[j].poc;
                }
            invalid_poc_present = 0;
            invalid_poc_start   = 0;
            invalid_poc_min     = 0;
            poc_offset = poc_max + 1;
        }
        if( i < num_access_units )
        {
            if( npt[i].reset )
                npt[i].poc = 0;
            poc_min        = 0;
            last_poc_reset = i;
        }
        else
            break;      /* no more POCs */
    }
}

static void nalu_generate_timestamps_from_poc
(
    importer_t        *importer,
    lsmash_media_ts_t *timestamp,
    nal_pic_timing_t  *npt,
    uint8_t           *composition_reordering_present,
    uint32_t          *last_delta,
    uint32_t           max_composition_delay,
    uint32_t           num_access_units
)
{
    /* Check if composition delay derived from reordering is present. */
    if( max_composition_delay == 0 )
    {
        *composition_reordering_present = 0;
        for( uint32_t i = 1; i < num_access_units; i++ )
            if( npt[i].poc < npt[i - 1].poc )
            {
                *composition_reordering_present = 1;
                break;
            }
    }
    else
        *composition_reordering_present = 1;
    if( *composition_reordering_present )
    {
        /* Generate timestamps.
         * Here, DTSs and CTSs are temporary values for sort. */
        for( uint32_t i = 0; i < num_access_units; i++ )
        {
            timestamp[i].cts = (uint64_t)npt[i].poc;
            timestamp[i].dts = (uint64_t)i;
        }
        qsort( timestamp, num_access_units, sizeof(lsmash_media_ts_t), (int(*)( const void *, const void * ))lsmash_compare_cts );
        /* Check POC gap in output order. */
        lsmash_class_t *logger = &(lsmash_class_t){ .name = importer->class->name };
        for( uint32_t i = 1; i < num_access_units; i++ )
            if( timestamp[i].cts > timestamp[i - 1].cts + npt[i - 1].poc_delta )
                lsmash_log( &logger, LSMASH_LOG_WARNING,
                            "POC gap is detected at picture %"PRIu64". Maybe some pictures are lost.\n", timestamp[i].dts );
        /* Get the maximum composition delay derived from reordering. */
        for( uint32_t i = 0; i < num_access_units; i++ )
            if( i < timestamp[i].dts )
            {
                uint32_t composition_delay = timestamp[i].dts - i;
                max_composition_delay = LSMASH_MAX( max_composition_delay, composition_delay );
            }
    }
    /* Generate timestamps. */
    if( max_composition_delay )
    {
        uint64_t *ts_buffer = (uint64_t *)lsmash_malloc( (num_access_units + max_composition_delay) * sizeof(uint64_t) );
        if( !ts_buffer )
        {
            /* It seems that there is no enough memory to generate more appropriate timestamps.
             * Anyway, generate CTSs and DTSs. */
            for( uint32_t i = 0; i < num_access_units; i++ )
                timestamp[i].cts = i + max_composition_delay;
            qsort( timestamp, num_access_units, sizeof(lsmash_media_ts_t), (int(*)( const void *, const void * ))lsmash_compare_dts );
            *last_delta = 1;
            return;
        }
        uint64_t *reorder_cts      = ts_buffer;
        uint64_t *prev_reorder_cts = ts_buffer + num_access_units;
        *last_delta = npt[num_access_units - 1].delta;
        /* Generate CTSs. */
        timestamp[0].cts = 0;
        for( uint32_t i = 1; i < num_access_units; i++ )
            timestamp[i].cts = timestamp[i - 1].cts + npt[i - 1].delta;
        int64_t composition_delay_time = timestamp[max_composition_delay].cts;
        for( uint32_t i = 0; i < num_access_units; i++ )
        {
            timestamp[i].cts += composition_delay_time;
            reorder_cts[i] = timestamp[i].cts;
        }
        /* Generate DTSs. */
        qsort( timestamp, num_access_units, sizeof(lsmash_media_ts_t), (int(*)( const void *, const void * ))lsmash_compare_dts );
        for( uint32_t i = 0; i < num_access_units; i++ )
        {
            timestamp[i].dts = i <= max_composition_delay
                             ? reorder_cts[i] - composition_delay_time
                             : prev_reorder_cts[(i - max_composition_delay) % max_composition_delay];
            prev_reorder_cts[i % max_composition_delay] = reorder_cts[i];
        }
        lsmash_free( ts_buffer );
#if 0
        fprintf( stderr, "max_composition_delay=%"PRIu32", composition_delay_time=%"PRIu64"\n",
                          max_composition_delay, composition_delay_time );
#endif
    }
    else
    {
        timestamp[0].dts = 0;
        timestamp[0].cts = 0;
        for( uint32_t i = 1; i < num_access_units; i++ )
        {
            timestamp[i].dts = timestamp[i - 1].dts + npt[i - 1].delta;
            timestamp[i].cts = timestamp[i - 1].cts + npt[i - 1].delta;
        }
        *last_delta = npt[num_access_units - 1].delta;
    }
}

static void nalu_reduce_timescale
(
    lsmash_media_ts_t *timestamp,
    nal_pic_timing_t  *npt,
    uint32_t          *last_delta,
    uint32_t          *timescale,
    uint32_t           num_access_units
)
{
    uint64_t gcd_delta = *timescale;
    for( uint32_t i = 0; i < num_access_units && gcd_delta > 1; i++ )
        gcd_delta = lsmash_get_gcd( gcd_delta, npt[i].delta );
    if( gcd_delta > 1 )
    {
        for( uint32_t i = 0; i < num_access_units; i++ )
        {
            timestamp[i].dts /= gcd_delta;
            timestamp[i].cts /= gcd_delta;
        }
        *last_delta /= gcd_delta;
        *timescale  /= gcd_delta;
    }
#if 0
    for( uint32_t i = 0; i < num_access_units; i++ )
        fprintf( stderr, "Timestamp[%"PRIu32"]: POC=%"PRId64", DTS=%"PRIu64", CTS=%"PRIu64"\n",
                 i, npt[i].poc, timestamp[i].dts, timestamp[i].cts );
#endif
}

static lsmash_video_summary_t *h264_setup_first_summary
(
    importer_t *importer
)
{
    h264_importer_t *h264_imp = (h264_importer_t *)importer->info;
    lsmash_codec_specific_t *cs = (lsmash_codec_specific_t *)lsmash_list_get_entry_data( h264_imp->avcC_list, ++ h264_imp->avcC_number );
    if( !cs || !cs->data.structured )
    {
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    lsmash_video_summary_t *summary = h264_create_summary( (lsmash_h264_specific_parameters_t *)cs->data.structured,
                                                           &h264_imp->info.sps, h264_imp->max_au_length );
    if( !summary )
    {
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    summary->sample_per_field = h264_imp->field_pic_present;
    return summary;
}

static int h264_analyze_whole_stream
(
    importer_t *importer
)
{
    /* Parse all NALU in the stream for preparation of calculating timestamps. */
    uint32_t npt_alloc = (1 << 12) * sizeof(nal_pic_timing_t);
    nal_pic_timing_t *npt = lsmash_malloc( npt_alloc );
    if( !npt )
        return LSMASH_ERR_MEMORY_ALLOC;
    uint32_t picture_stats[H264_PICTURE_TYPE_NONE + 1] = { 0 };
    uint32_t num_access_units = 0;
    lsmash_class_t *logger = &(lsmash_class_t){ "H.264" };
    lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as H.264\r" );
    h264_importer_t *h264_imp = (h264_importer_t *)importer->info;
    h264_info_t     *info     = &h264_imp->info;
    importer->status = IMPORTER_OK;
    int err = LSMASH_ERR_MEMORY_ALLOC;
    while( importer->status != IMPORTER_EOF )
    {
#if 0
        lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as H.264: %"PRIu32"\n", num_access_units + 1 );
#endif
        h264_picture_info_t     *picture = &info->au.picture;
        h264_picture_info_t prev_picture = *picture;
        if( (err = h264_get_access_unit_internal( importer, 1 ))       < 0
         || (err = h264_calculate_poc( info, picture, &prev_picture )) < 0 )
            goto fail;
        h264_importer_check_eof( importer, &info->au );
        if( npt_alloc <= num_access_units * sizeof(nal_pic_timing_t) )
        {
            uint32_t alloc = 2 * num_access_units * sizeof(nal_pic_timing_t);
            nal_pic_timing_t *temp = (nal_pic_timing_t *)lsmash_realloc( npt, alloc );
            if( !temp )
                goto fail;
            npt       = temp;
            npt_alloc = alloc;
        }
        h264_imp->field_pic_present |= picture->field_pic_flag;
        npt[num_access_units].poc       = picture->PicOrderCnt;
        npt[num_access_units].delta     = picture->delta;
        npt[num_access_units].poc_delta = picture->field_pic_flag ? 1 : 2;
        npt[num_access_units].reset     = picture->has_mmco5;
        ++num_access_units;
        h264_imp->max_au_length = LSMASH_MAX( info->au.length, h264_imp->max_au_length );
        if( picture->idr )
            ++picture_stats[H264_PICTURE_TYPE_IDR];
        else if( picture->type >= H264_PICTURE_TYPE_NONE )
            ++picture_stats[H264_PICTURE_TYPE_NONE];
        else
            ++picture_stats[ picture->type ];
    }
    lsmash_log_refresh_line( &logger );
    lsmash_log( &logger, LSMASH_LOG_INFO,
                "IDR: %"PRIu32", I: %"PRIu32", P: %"PRIu32", B: %"PRIu32", "
                "SI: %"PRIu32", SP: %"PRIu32", Unknown: %"PRIu32"\n",
                picture_stats[H264_PICTURE_TYPE_IDR        ],
                picture_stats[H264_PICTURE_TYPE_I          ],
                picture_stats[H264_PICTURE_TYPE_I_P        ],
                picture_stats[H264_PICTURE_TYPE_I_P_B      ],
                picture_stats[H264_PICTURE_TYPE_SI         ]
              + picture_stats[H264_PICTURE_TYPE_I_SI       ],
                picture_stats[H264_PICTURE_TYPE_SI_SP      ]
              + picture_stats[H264_PICTURE_TYPE_I_SI_P_SP  ]
              + picture_stats[H264_PICTURE_TYPE_I_SI_P_SP_B],
                picture_stats[H264_PICTURE_TYPE_NONE       ] );
    /* Copy and append the last Codec Specific info. */
    if( (err = h264_store_codec_specific( h264_imp, &info->avcC_param )) < 0 )
        goto fail;
    /* Set up the first summary. */
    lsmash_video_summary_t *summary = h264_setup_first_summary( importer );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    /* Allocate timestamps. */
    lsmash_media_ts_t *timestamp = lsmash_malloc( num_access_units * sizeof(lsmash_media_ts_t) );
    if( !timestamp )
        goto fail;
    /* Count leading samples that are undecodable. */
    for( uint32_t i = 0; i < num_access_units; i++ )
    {
        if( npt[i].poc == 0 )
            break;
        ++ h264_imp->num_undecodable;
    }
    /* Deduplicate POCs. */
    uint32_t max_composition_delay = 0;
    nalu_deduplicate_poc( npt, &max_composition_delay, num_access_units, 32 );
    /* Generate timestamps. */
    nalu_generate_timestamps_from_poc( importer, timestamp, npt,
                                       &h264_imp->composition_reordering_present,
                                       &h264_imp->last_delta,
                                       max_composition_delay, num_access_units );
    nalu_reduce_timescale( timestamp, npt, &h264_imp->last_delta, &summary->timescale, num_access_units );
    lsmash_free( npt );
    h264_imp->ts_list.sample_count = num_access_units;
    h264_imp->ts_list.timestamp    = timestamp;
    return 0;
fail:
    lsmash_log_refresh_line( &logger );
    lsmash_free( npt );
    return err;
}

static int h264_importer_probe( importer_t *importer )
{
    /* Find the first start code. */
    h264_importer_t *h264_imp = create_h264_importer( importer );
    if( !h264_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = importer->bs;
    uint64_t first_sc_head_pos = nalu_find_first_start_code( bs );
    int err;
    if( first_sc_head_pos == NALU_NO_START_CODE_FOUND )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    else if( first_sc_head_pos == NALU_IO_ERROR )
    {
        err = LSMASH_ERR_IO;
        goto fail;
    }
    /* OK. It seems the stream has a long start code of H.264. */
    importer->info = h264_imp;
    h264_info_t *info = &h264_imp->info;
    lsmash_bs_read_seek( bs, first_sc_head_pos, SEEK_SET );
    h264_imp->sc_head_pos = first_sc_head_pos;
    if( (err = h264_analyze_whole_stream( importer )) < 0 )
        goto fail;
    /* Go back to the start code of the first NALU. */
    importer->status = IMPORTER_OK;
    lsmash_bs_read_seek( bs, first_sc_head_pos, SEEK_SET );
    h264_imp->sc_head_pos       = first_sc_head_pos;
    info->prev_nalu_type        = H264_NALU_TYPE_UNSPECIFIED0;
    uint8_t *temp_au            = info->au.data;
    uint8_t *temp_incomplete_au = info->au.incomplete_data;
    memset( &info->au, 0, sizeof(h264_access_unit_t) );
    info->au.data               = temp_au;
    info->au.incomplete_data    = temp_incomplete_au;
    memset( &info->slice, 0, sizeof(h264_slice_info_t) );
    memset( &info->sps, 0, sizeof(h264_sps_t) );
    memset( &info->pps, 0, sizeof(h264_pps_t) );
    lsmash_list_remove_entries( info->avcC_param.parameter_sets->sps_list );
    lsmash_list_remove_entries( info->avcC_param.parameter_sets->pps_list );
    lsmash_list_remove_entries( info->avcC_param.parameter_sets->spsext_list );
    lsmash_destroy_h264_parameter_sets( &info->avcC_param_next );
    return 0;
fail:
    remove_h264_importer( h264_imp );
    importer->info = NULL;
    lsmash_list_remove_entries( importer->summaries );
    return err;
}

static uint32_t h264_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    h264_importer_t *h264_imp = (h264_importer_t *)importer->info;
    if( !h264_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    return h264_imp->ts_list.sample_count
         ? h264_imp->last_delta
         : UINT32_MAX;    /* arbitrary */
}

const importer_functions h264_importer =
{
    { "H.264", offsetof( importer_t, log_level ) },
    1,
    h264_importer_probe,
    h264_importer_get_accessunit,
    h264_importer_get_last_delta,
    h264_importer_cleanup
};

/***************************************************************************
    HEVC importer
    ITU-T Recommendation H.265 (04/13)
    ISO/IEC 14496-15:2014
***************************************************************************/
#include "codecs/hevc.h"

typedef struct
{
    hevc_info_t            info;
    lsmash_entry_list_t    hvcC_list[1];    /* stored as lsmash_codec_specific_t */
    lsmash_media_ts_list_t ts_list;
    uint32_t max_au_length;
    uint32_t num_undecodable;
    uint32_t hvcC_number;
    uint32_t last_delta;
    uint64_t last_intra_cts;
    uint64_t sc_head_pos;
    uint8_t  composition_reordering_present;
    uint8_t  field_pic_present;
    uint8_t  max_TemporalId;
} hevc_importer_t;

static void remove_hevc_importer( hevc_importer_t *hevc_imp )
{
    if( !hevc_imp )
        return;
    lsmash_list_remove_entries( hevc_imp->hvcC_list );
    hevc_cleanup_parser( &hevc_imp->info );
    lsmash_free( hevc_imp->ts_list.timestamp );
    lsmash_free( hevc_imp );
}

static void hevc_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_hevc_importer( importer->info );
}

static hevc_importer_t *create_hevc_importer( importer_t *importer )
{
    hevc_importer_t *hevc_imp = lsmash_malloc_zero( sizeof(hevc_importer_t) );
    if( !hevc_imp )
        return NULL;
    if( hevc_setup_parser( &hevc_imp->info, 0 ) < 0 )
    {
        remove_hevc_importer( hevc_imp );
        return NULL;
    }
    lsmash_list_init( hevc_imp->hvcC_list, lsmash_destroy_codec_specific_data );
    hevc_imp->info.eos = 1;
    return hevc_imp;
}

static inline int hevc_complete_au( hevc_access_unit_t *au, int probe )
{
    if( !au->picture.has_primary || au->incomplete_length == 0 )
        return 0;
    if( !probe )
        memcpy( au->data, au->incomplete_data, au->incomplete_length );
    au->TemporalId          = au->picture.TemporalId;
    au->length              = au->incomplete_length;
    au->incomplete_length   = 0;
    au->picture.has_primary = 0;
    return 1;
}

static void hevc_append_nalu_to_au( hevc_access_unit_t *au, uint8_t *src_nalu, uint32_t nalu_length, int probe )
{
    if( !probe )
    {
        uint8_t *dst_nalu = au->incomplete_data + au->incomplete_length + NALU_DEFAULT_NALU_LENGTH_SIZE;
        for( int i = NALU_DEFAULT_NALU_LENGTH_SIZE; i; i-- )
            *(dst_nalu - i) = (nalu_length >> ((i - 1) * 8)) & 0xff;
        memcpy( dst_nalu, src_nalu, nalu_length );
    }
    /* Note: picture->incomplete_au_length shall be 0 immediately after AU has completed.
     * Therefore, possible_au_length in hevc_get_access_unit_internal() can't be used here
     * to avoid increasing AU length monotonously through the entire stream. */
    au->incomplete_length += NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
}

static int hevc_get_au_internal_succeeded( hevc_importer_t *hevc_imp, hevc_access_unit_t *au )
{
    au->number += 1;
    return 0;
}

static int hevc_get_au_internal_failed( hevc_importer_t *hevc_imp, hevc_access_unit_t *au, int complete_au, int ret )
{
    if( complete_au )
        au->number += 1;
    return ret;
}

static lsmash_video_summary_t *hevc_create_summary
(
    lsmash_hevc_specific_parameters_t *param,
    hevc_sps_t                        *sps,
    uint32_t                           max_au_length
)
{
    lsmash_video_summary_t *summary = (lsmash_video_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_VIDEO );
    if( !summary )
        return NULL;
    /* Update summary here.
     * max_au_length is set at the last of hevc_importer_probe function. */
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC,
                                                                           LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !specific )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    specific->data.unstructured = lsmash_create_hevc_specific_info( param, &specific->size );
    if( !specific->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( specific );
        return NULL;
    }
    summary->sample_type            = ISOM_CODEC_TYPE_HVC1_VIDEO;
    summary->max_au_length          = max_au_length;
    summary->timescale              = sps->vui.time_scale;
    summary->timebase               = sps->vui.num_units_in_tick;
    summary->vfr                    = (param->constantFrameRate == 0);
    summary->sample_per_field       = 0;
    summary->width                  = sps->cropped_width;
    summary->height                 = sps->cropped_height;
    summary->par_h                  = sps->vui.sar_width;
    summary->par_v                  = sps->vui.sar_height;
    summary->color.primaries_index  = sps->vui.colour_primaries         != 2 ? sps->vui.colour_primaries         : 0;
    summary->color.transfer_index   = sps->vui.transfer_characteristics != 2 ? sps->vui.transfer_characteristics : 0;
    summary->color.matrix_index     = sps->vui.matrix_coeffs            != 2 ? sps->vui.matrix_coeffs            : 0;
    summary->color.full_range       = sps->vui.video_full_range_flag;
    lsmash_convert_crop_into_clap( sps->vui.def_disp_win_offset, summary->width, summary->height, &summary->clap );
    return summary;
}

static int hevc_store_codec_specific
(
    hevc_importer_t                   *hevc_imp,
    lsmash_hevc_specific_parameters_t *hvcC_param
)
{
    lsmash_codec_specific_t *src_cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC,
                                                                         LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !src_cs )
        return LSMASH_ERR_NAMELESS;
    lsmash_hevc_specific_parameters_t *src_param = (lsmash_hevc_specific_parameters_t *)src_cs->data.structured;
    *src_param = *hvcC_param;
    lsmash_codec_specific_t *dst_cs = lsmash_convert_codec_specific_format( src_cs, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    src_param->parameter_arrays = NULL;     /* Avoid freeing parameter arrays within hvcC_param. */
    lsmash_destroy_codec_specific_data( src_cs );
    if( !dst_cs )
    {
        lsmash_destroy_codec_specific_data( dst_cs );
        return LSMASH_ERR_NAMELESS;
    }
    if( lsmash_list_add_entry( hevc_imp->hvcC_list, dst_cs ) < 0 )
    {
        lsmash_destroy_codec_specific_data( dst_cs );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static inline void hevc_new_access_unit( hevc_access_unit_t *au )
{
    au->length                    = 0;
    au->picture.type              = HEVC_PICTURE_TYPE_NONE;
    au->picture.random_accessible = 0;
    au->picture.recovery_poc_cnt  = 0;
}

/* If probe equals 0, don't get the actual data (EBPS) of an access unit and only parse NALU. */
static int hevc_get_access_unit_internal
(
    importer_t *importer,
    int         probe
)
{
    hevc_importer_t      *hevc_imp = (hevc_importer_t *)importer->info;
    hevc_info_t          *info     = &hevc_imp->info;
    hevc_slice_info_t    *slice    = &info->slice;
    hevc_access_unit_t   *au       = &info->au;
    hevc_picture_info_t  *picture  = &au->picture;
    hevc_stream_buffer_t *sb       = &info->buffer;
    lsmash_bs_t          *bs       = importer->bs;
    int complete_au = 0;
    hevc_new_access_unit( au );
    while( 1 )
    {
        hevc_nalu_header_t nuh;
        uint64_t start_code_length;
        uint64_t trailing_zero_bytes;
        uint64_t nalu_length = hevc_find_next_start_code( bs, &nuh, &start_code_length, &trailing_zero_bytes );
        if( nalu_length == NALU_NO_START_CODE_FOUND )
        {
            /* For the last NALU.
             * This NALU already has been appended into the latest access unit and parsed. */
            hevc_update_picture_info( info, picture, slice, &info->sps, &info->sei );
            complete_au = hevc_complete_au( au, probe );
            if( complete_au )
                return hevc_get_au_internal_succeeded( hevc_imp, au );
            else
                return hevc_get_au_internal_failed( hevc_imp, au, complete_au, LSMASH_ERR_INVALID_DATA );
        }
        uint8_t  nalu_type        = nuh.nal_unit_type;
        uint64_t next_sc_head_pos = hevc_imp->sc_head_pos
                                  + start_code_length
                                  + nalu_length
                                  + trailing_zero_bytes;
#if 0
        if( probe )
        {
            fprintf( stderr, "NALU type: %"PRIu8"                    \n", nalu_type );
            fprintf( stderr, "    NALU header position: %"PRIx64"    \n", hevc_imp->sc_head_pos + start_code_length );
            fprintf( stderr, "    EBSP position: %"PRIx64"           \n", hevc_imp->sc_head_pos + start_code_length + nuh.length );
            fprintf( stderr, "    EBSP length: %"PRIx64" (%"PRIu64") \n", nalu_length - nuh.length, nalu_length - nuh.length );
            fprintf( stderr, "    trailing_zero_bytes: %"PRIx64"     \n", trailing_zero_bytes );
            fprintf( stderr, "    Next start code position: %"PRIx64"\n", next_sc_head_pos );
        }
#endif
        /* Check if the end of sequence. Used for POC calculation. */
        info->eos |= info->prev_nalu_type == HEVC_NALU_TYPE_EOS
                  || info->prev_nalu_type == HEVC_NALU_TYPE_EOB;
        /* Process the current NALU by its type. */
        if( nalu_type == HEVC_NALU_TYPE_FD )
        {
            /* We don't support streams with both filler and HRD yet. Otherwise, just skip filler. */
            if( info->sps.vui.hrd.present )
                return hevc_get_au_internal_failed( hevc_imp, au, complete_au, LSMASH_ERR_PATCH_WELCOME );
        }
        else if( nalu_type <= HEVC_NALU_TYPE_RASL_R
             || (nalu_type >= HEVC_NALU_TYPE_BLA_W_LP && nalu_type <= HEVC_NALU_TYPE_CRA)
             || (nalu_type >= HEVC_NALU_TYPE_VPS      && nalu_type <= HEVC_NALU_TYPE_SUFFIX_SEI)  )
        {
            int err;
            /* Increase the buffer if needed. */
            uint64_t possible_au_length = au->incomplete_length + NALU_DEFAULT_NALU_LENGTH_SIZE + nalu_length;
            if( sb->bank->buffer_size < possible_au_length
             && (err = hevc_supplement_buffer( sb, au, 2 * possible_au_length )) < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to increase the buffer size.\n" );
                return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
            }
            /* Get the EBSP of the current NALU here. */
            uint8_t *nalu = lsmash_bs_get_buffer_data( bs ) + start_code_length;
            if( nalu_type <= HEVC_NALU_TYPE_RSV_VCL31 )
            {
                /* VCL NALU (slice) */
                hevc_slice_info_t prev_slice = *slice;
                if( (err = hevc_parse_slice_segment_header( info, &nuh, sb->rbsp,
                                                            nalu        + nuh.length,
                                                            nalu_length - nuh.length )) < 0 )
                    return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
                if( probe && info->hvcC_pending )
                {
                    /* Copy and append a Codec Specific info. */
                    if( (err = hevc_store_codec_specific( hevc_imp, &info->hvcC_param )) < 0 )
                        return err;
                }
                if( (err = hevc_move_pending_hvcC_param( info )) < 0 )
                    return err;
                if( prev_slice.present )
                {
                    /* Check whether the AU that contains the previous VCL NALU completed or not. */
                    if( hevc_find_au_delimit_by_slice_info( info, slice, &prev_slice ) )
                    {
                        /* The current NALU is the first VCL NALU of the primary coded picture of a new AU.
                         * Therefore, the previous slice belongs to the AU you want at this time. */
                        hevc_update_picture_info( info, picture, &prev_slice, &info->sps, &info->sei );
                        complete_au = hevc_complete_au( au, probe );
                    }
                    else
                        hevc_update_picture_info_for_slice( info, picture, &prev_slice );
                }
                hevc_append_nalu_to_au( au, nalu, nalu_length, probe );
                slice->present = 1;
            }
            else
            {
                if( hevc_find_au_delimit_by_nalu_type( nalu_type, info->prev_nalu_type ) )
                {
                    /* The last slice belongs to the AU you want at this time. */
                    hevc_update_picture_info( info, picture, slice, &info->sps, &info->sei );
                    complete_au = hevc_complete_au( au, probe );
                }
                switch( nalu_type )
                {
                    case HEVC_NALU_TYPE_PREFIX_SEI :
                    case HEVC_NALU_TYPE_SUFFIX_SEI :
                    {
                        if( (err = hevc_parse_sei( info->bits, &info->vps, &info->sps, &info->sei, &nuh,
                                                   sb->rbsp, nalu + nuh.length, nalu_length - nuh.length )) < 0 )
                            return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
                        hevc_append_nalu_to_au( au, nalu, nalu_length, probe );
                        break;
                    }
                    case HEVC_NALU_TYPE_VPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_VPS, nalu, nalu_length )) < 0 )
                            return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
                        break;
                    case HEVC_NALU_TYPE_SPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_SPS, nalu, nalu_length )) < 0 )
                            return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
                        break;
                    case HEVC_NALU_TYPE_PPS :
                        if( (err = hevc_try_to_append_dcr_nalu( info, HEVC_DCR_NALU_TYPE_PPS, nalu, nalu_length )) < 0 )
                            return hevc_get_au_internal_failed( hevc_imp, au, complete_au, err );
                        break;
                    case HEVC_NALU_TYPE_AUD :   /* We drop access unit delimiters. */
                        break;
                    default :
                        hevc_append_nalu_to_au( au, nalu, nalu_length, probe );
                        break;
                }
                if( info->hvcC_pending )
                    importer->status = IMPORTER_CHANGE;
            }
        }
        /* Move to the first byte of the next start code. */
        info->prev_nalu_type = nalu_type;
        if( lsmash_bs_read_seek( bs, next_sc_head_pos, SEEK_SET ) != next_sc_head_pos )
        {
            lsmash_log( importer, LSMASH_LOG_ERROR, "failed to seek the next start code.\n" );
            return hevc_get_au_internal_failed( hevc_imp, au, complete_au, LSMASH_ERR_NAMELESS );
        }
        if( !lsmash_bs_is_end( bs, NALU_SHORT_START_CODE_LENGTH ) )
            hevc_imp->sc_head_pos = next_sc_head_pos;
        /* If there is no more data in the stream, and flushed chunk of NALUs, flush it as complete AU here. */
        else if( au->incomplete_length && au->length == 0 )
        {
            hevc_update_picture_info( info, picture, slice, &info->sps, &info->sei );
            hevc_complete_au( au, probe );
            return hevc_get_au_internal_succeeded( hevc_imp, au );
        }
        if( complete_au )
            return hevc_get_au_internal_succeeded( hevc_imp, au );
    }
}

static inline void hevc_importer_check_eof( importer_t *importer, hevc_access_unit_t *au )
{
    /* HEVC byte stream NALU consists of at least 5 bytes (start-code + NALU-header). */
    if( lsmash_bs_is_end( importer->bs, NALU_SHORT_START_CODE_LENGTH + 1 ) && au->incomplete_length == 0 )
        importer->status = IMPORTER_EOF;
    else if( importer->status != IMPORTER_CHANGE )
        importer->status = IMPORTER_OK;
}

static int hevc_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    hevc_importer_t *hevc_imp = (hevc_importer_t *)importer->info;
    hevc_info_t     *info     = &hevc_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    int err = hevc_get_access_unit_internal( importer, 0 );
    if( err < 0 )
    {
        importer->status = IMPORTER_ERROR;
        return err;
    }
    hevc_importer_check_eof( importer, &info->au );
    if( importer->status == IMPORTER_CHANGE && !info->hvcC_pending )
        current_status = IMPORTER_CHANGE;
    if( current_status == IMPORTER_CHANGE )
    {
        /* Update the active summary. */
        lsmash_codec_specific_t *cs = (lsmash_codec_specific_t *)lsmash_list_get_entry_data( hevc_imp->hvcC_list, ++ hevc_imp->hvcC_number );
        if( !cs )
            return LSMASH_ERR_NAMELESS;
        lsmash_hevc_specific_parameters_t *hvcC_param = (lsmash_hevc_specific_parameters_t *)cs->data.structured;
        lsmash_video_summary_t *summary = hevc_create_summary( hvcC_param, &info->sps, hevc_imp->max_au_length );
        if( !summary )
            return LSMASH_ERR_NAMELESS;
        lsmash_list_remove_entry( importer->summaries, track_number );
        if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
        {
            lsmash_cleanup_summary( (lsmash_summary_t *)summary );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        importer->status = IMPORTER_OK;
    }
    lsmash_sample_t *sample = lsmash_create_sample( hevc_imp->max_au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    hevc_access_unit_t  *au      = &info->au;
    hevc_picture_info_t *picture = &au->picture;
    sample->dts = hevc_imp->ts_list.timestamp[ au->number - 1 ].dts;
    sample->cts = hevc_imp->ts_list.timestamp[ au->number - 1 ].cts;
    /* Set property of disposability. */
    if( picture->sublayer_nonref && au->TemporalId == hevc_imp->max_TemporalId )
        /* Sub-layer non-reference pictures are not referenced by subsequent pictures of
         * the same sub-layer in decoding order. */
        sample->prop.disposable = ISOM_SAMPLE_IS_DISPOSABLE;
    else
        sample->prop.disposable = ISOM_SAMPLE_IS_NOT_DISPOSABLE;
    /* Set property of leading. */
    if( picture->radl || picture->rasl )
        sample->prop.leading = picture->radl ? ISOM_SAMPLE_IS_DECODABLE_LEADING : ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
    else
    {
        if( au->number < hevc_imp->num_undecodable )
            sample->prop.leading = ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
        else
        {
            if( picture->independent || sample->cts >= hevc_imp->last_intra_cts )
                sample->prop.leading = ISOM_SAMPLE_IS_NOT_LEADING;
            else
                sample->prop.leading = ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
        }
    }
    if( picture->independent )
        hevc_imp->last_intra_cts = sample->cts;
    /* Set property of independence. */
    sample->prop.independent = picture->independent ? ISOM_SAMPLE_IS_INDEPENDENT : ISOM_SAMPLE_IS_NOT_INDEPENDENT;
    sample->prop.redundant   = ISOM_SAMPLE_HAS_NO_REDUNDANCY;
    sample->prop.post_roll.identifier = picture->poc;
    if( picture->random_accessible )
    {
        if( picture->irap )
        {
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
            if( picture->closed_rap )
                sample->prop.ra_flags |= ISOM_SAMPLE_RANDOM_ACCESS_FLAG_CLOSED_RAP;
            else
                sample->prop.ra_flags |= ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP;
        }
        else if( picture->recovery_poc_cnt )
        {
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_POST_ROLL_START;
            sample->prop.post_roll.complete = picture->poc + picture->recovery_poc_cnt;
        }
        else
            sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP;
    }
    sample->length = au->length;
    memcpy( sample->data, au->data, au->length );
    return current_status;
}

static lsmash_video_summary_t *hevc_setup_first_summary
(
    importer_t *importer
)
{
    hevc_importer_t *hevc_imp = (hevc_importer_t *)importer->info;
    lsmash_codec_specific_t *cs = (lsmash_codec_specific_t *)lsmash_list_get_entry_data( hevc_imp->hvcC_list, ++ hevc_imp->hvcC_number );
    if( !cs || !cs->data.structured )
    {
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    lsmash_video_summary_t *summary = hevc_create_summary( (lsmash_hevc_specific_parameters_t *)cs->data.structured,
                                                           &hevc_imp->info.sps, hevc_imp->max_au_length );
    if( !summary )
    {
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    summary->sample_per_field = hevc_imp->field_pic_present;
    return summary;
}

static int hevc_analyze_whole_stream
(
    importer_t *importer
)
{
    /* Parse all NALU in the stream for preparation of calculating timestamps. */
    uint32_t npt_alloc = (1 << 12) * sizeof(nal_pic_timing_t);
    nal_pic_timing_t *npt = (nal_pic_timing_t *)lsmash_malloc( npt_alloc );
    if( !npt )
        return LSMASH_ERR_MEMORY_ALLOC;
    uint32_t picture_stats[HEVC_PICTURE_TYPE_NONE + 1] = { 0 };
    uint32_t num_access_units = 0;
    lsmash_class_t *logger = &(lsmash_class_t){ "HEVC" };
    lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as HEVC\r" );
    hevc_importer_t *hevc_imp = (hevc_importer_t *)importer->info;
    hevc_info_t     *info     = &hevc_imp->info;
    importer->status = IMPORTER_OK;
    int err = LSMASH_ERR_MEMORY_ALLOC;
    while( importer->status != IMPORTER_EOF )
    {
#if 0
        lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as HEVC: %"PRIu32"\n", num_access_units + 1 );
#endif
        hevc_picture_info_t     *picture = &info->au.picture;
        hevc_picture_info_t prev_picture = *picture;
        if( (err = hevc_get_access_unit_internal( importer, 1 ))                 < 0
         || (err = hevc_calculate_poc( info, &info->au.picture, &prev_picture )) < 0 )
            goto fail;
        hevc_importer_check_eof( importer, &info->au );
        if( npt_alloc <= num_access_units * sizeof(nal_pic_timing_t) )
        {
            uint32_t alloc = 2 * num_access_units * sizeof(nal_pic_timing_t);
            nal_pic_timing_t *temp = (nal_pic_timing_t *)lsmash_realloc( npt, alloc );
            if( !temp )
                goto fail;
            npt = temp;
            npt_alloc = alloc;
        }
        hevc_imp->field_pic_present |= picture->field_coded;
        npt[num_access_units].poc       = picture->poc;
        npt[num_access_units].delta     = picture->delta;
        npt[num_access_units].poc_delta = 1;
        npt[num_access_units].reset     = 0;
        ++num_access_units;
        hevc_imp->max_au_length  = LSMASH_MAX( hevc_imp->max_au_length,  info->au.length );
        hevc_imp->max_TemporalId = LSMASH_MAX( hevc_imp->max_TemporalId, info->au.TemporalId );
        if( picture->idr )
            ++picture_stats[HEVC_PICTURE_TYPE_IDR];
        else if( picture->irap )
            ++picture_stats[ picture->broken_link ? HEVC_PICTURE_TYPE_BLA : HEVC_PICTURE_TYPE_CRA ];
        else if( picture->type >= HEVC_PICTURE_TYPE_NONE )
            ++picture_stats[HEVC_PICTURE_TYPE_NONE];
        else
            ++picture_stats[ picture->type ];
    }
    lsmash_log_refresh_line( &logger );
    lsmash_log( &logger, LSMASH_LOG_INFO,
                "IDR: %"PRIu32", CRA: %"PRIu32", BLA: %"PRIu32", I: %"PRIu32", P: %"PRIu32", B: %"PRIu32", Unknown: %"PRIu32"\n",
                picture_stats[HEVC_PICTURE_TYPE_IDR], picture_stats[HEVC_PICTURE_TYPE_CRA],
                picture_stats[HEVC_PICTURE_TYPE_BLA], picture_stats[HEVC_PICTURE_TYPE_I],
                picture_stats[HEVC_PICTURE_TYPE_I_P], picture_stats[HEVC_PICTURE_TYPE_I_P_B],
                picture_stats[HEVC_PICTURE_TYPE_NONE]);
    /* Copy and append the last Codec Specific info. */
    if( (err = hevc_store_codec_specific( hevc_imp, &info->hvcC_param )) < 0 )
        goto fail;
    /* Set up the first summary. */
    lsmash_video_summary_t *summary = hevc_setup_first_summary( importer );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    /* */
    lsmash_media_ts_t *timestamp = lsmash_malloc( num_access_units * sizeof(lsmash_media_ts_t) );
    if( !timestamp )
        goto fail;
    /* Count leading samples that are undecodable. */
    for( uint32_t i = 0; i < num_access_units; i++ )
    {
        if( npt[i].poc == 0 )
            break;
        ++ hevc_imp->num_undecodable;
    }
    /* Deduplicate POCs. */
    uint32_t max_composition_delay = 0;
    nalu_deduplicate_poc( npt, &max_composition_delay, num_access_units, 15 );
    /* Generate timestamps. */
    nalu_generate_timestamps_from_poc( importer, timestamp, npt,
                                       &hevc_imp->composition_reordering_present,
                                       &hevc_imp->last_delta,
                                       max_composition_delay, num_access_units );
    summary->timescale *= 2;    /* We assume that picture timing is in field level.
                                 * For HEVC, it seems time_scale is set in frame level basically.
                                 * So multiply by 2 for reducing timebase and timescale. */
    nalu_reduce_timescale( timestamp, npt, &hevc_imp->last_delta, &summary->timescale, num_access_units );
    lsmash_free( npt );
    hevc_imp->ts_list.sample_count = num_access_units;
    hevc_imp->ts_list.timestamp    = timestamp;
    return 0;
fail:
    lsmash_log_refresh_line( &logger );
    lsmash_free( npt );
    return err;
}

static int hevc_importer_probe( importer_t *importer )
{
    /* Find the first start code. */
    hevc_importer_t *hevc_imp = create_hevc_importer( importer );
    if( !hevc_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = importer->bs;
    uint64_t first_sc_head_pos = nalu_find_first_start_code( bs );
    int err;
    if( first_sc_head_pos == NALU_NO_START_CODE_FOUND )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    else if( first_sc_head_pos == NALU_IO_ERROR )
    {
        err = LSMASH_ERR_IO;
        goto fail;
    }
    /* OK. It seems the stream has a long start code of HEVC. */
    importer->info = hevc_imp;
    hevc_info_t *info = &hevc_imp->info;
    lsmash_bs_read_seek( bs, first_sc_head_pos, SEEK_SET );
    hevc_imp->sc_head_pos = first_sc_head_pos;
    if( (err = hevc_analyze_whole_stream( importer )) < 0 )
        goto fail;
    /* Go back to the start code of the first NALU. */
    importer->status = IMPORTER_OK;
    lsmash_bs_read_seek( bs, first_sc_head_pos, SEEK_SET );
    hevc_imp->sc_head_pos       = first_sc_head_pos;
    info->prev_nalu_type        = HEVC_NALU_TYPE_UNKNOWN;
    uint8_t *temp_au            = info->au.data;
    uint8_t *temp_incomplete_au = info->au.incomplete_data;
    memset( &info->au, 0, sizeof(hevc_access_unit_t) );
    info->au.data            = temp_au;
    info->au.incomplete_data = temp_incomplete_au;
    memset( &info->slice, 0, sizeof(hevc_slice_info_t) );
    memset( &info->vps,   0, sizeof(hevc_vps_t) );
    memset( &info->sps,   0, sizeof(hevc_sps_t) );
    memset( &info->pps,   0, SIZEOF_PPS_EXCLUDING_HEAP );
    for( int i = 0; i < HEVC_DCR_NALU_TYPE_NUM; i++ )
        lsmash_list_remove_entries( info->hvcC_param.parameter_arrays->ps_array[i].list );
    lsmash_destroy_hevc_parameter_arrays( &info->hvcC_param_next );
    return 0;
fail:
    remove_hevc_importer( hevc_imp );
    importer->info = NULL;
    lsmash_list_remove_entries( importer->summaries );
    return err;
}

static uint32_t hevc_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    hevc_importer_t *hevc_imp = (hevc_importer_t *)importer->info;
    if( !hevc_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    return hevc_imp->ts_list.sample_count
         ? hevc_imp->last_delta
         : UINT32_MAX;    /* arbitrary */
}

const importer_functions hevc_importer =
{
    { "HEVC", offsetof( importer_t, log_level ) },
    1,
    hevc_importer_probe,
    hevc_importer_get_accessunit,
    hevc_importer_get_last_delta,
    hevc_importer_cleanup
};

/*****************************************************************************
 * vc1_imp.c
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

#include <string.h>
#include <inttypes.h>

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/***************************************************************************
    SMPTE VC-1 importer (only for Advanced Profile)
    SMPTE 421M-2006
    SMPTE RP 2025-2007
***************************************************************************/
#include "codecs/vc1.h"

typedef struct
{
    vc1_info_t             info;
    vc1_sequence_header_t  first_sequence;
    lsmash_media_ts_list_t ts_list;
    uint8_t  composition_reordering_present;
    uint32_t max_au_length;
    uint32_t num_undecodable;
    uint64_t last_ref_intra_cts;
} vc1_importer_t;

static void remove_vc1_importer( vc1_importer_t *vc1_imp )
{
    if( !vc1_imp )
        return;
    vc1_cleanup_parser( &vc1_imp->info );
    lsmash_free( vc1_imp->ts_list.timestamp );
    lsmash_free( vc1_imp );
}

static void vc1_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_vc1_importer( importer->info );
}

static vc1_importer_t *create_vc1_importer( importer_t *importer )
{
    vc1_importer_t *vc1_imp = lsmash_malloc_zero( sizeof(vc1_importer_t) );
    if( !vc1_imp )
        return NULL;
    if( vc1_setup_parser( &vc1_imp->info, 0 ) < 0 )
    {
        remove_vc1_importer( vc1_imp );
        return NULL;
    }
    return vc1_imp;
}

static inline int vc1_complete_au( vc1_access_unit_t *access_unit, vc1_picture_info_t *picture, int probe )
{
    if( !picture->present )
        return 0;
    if( !probe )
        memcpy( access_unit->data, access_unit->incomplete_data, access_unit->incomplete_data_length );
    access_unit->data_length = access_unit->incomplete_data_length;
    access_unit->incomplete_data_length = 0;
    vc1_update_au_property( access_unit, picture );
    return 1;
}

static inline void vc1_append_ebdu_to_au( vc1_access_unit_t *access_unit, uint8_t *ebdu, uint32_t ebdu_length, int probe )
{
    if( !probe )
        memcpy( access_unit->incomplete_data + access_unit->incomplete_data_length, ebdu, ebdu_length );
    /* Note: access_unit->incomplete_data_length shall be 0 immediately after AU has completed.
     * Therefore, possible_au_length in vc1_get_access_unit_internal() can't be used here
     * to avoid increasing AU length monotonously through the entire stream. */
    access_unit->incomplete_data_length += ebdu_length;
}

static int vc1_get_au_internal_succeeded( vc1_importer_t *vc1_imp )
{
    vc1_access_unit_t *access_unit = &vc1_imp->info.access_unit;
    access_unit->number += 1;
    return 0;
}

static int vc1_get_au_internal_failed( vc1_importer_t *vc1_imp, int complete_au, int ret )
{
    vc1_access_unit_t *access_unit = &vc1_imp->info.access_unit;
    if( complete_au )
        access_unit->number += 1;
    return ret;
}

static int vc1_importer_get_access_unit_internal( importer_t *importer, int probe )
{
    vc1_importer_t      *vc1_imp     = (vc1_importer_t *)importer->info;
    vc1_info_t          *info        = &vc1_imp->info;
    vc1_stream_buffer_t *sb          = &info->buffer;
    vc1_access_unit_t   *access_unit = &info->access_unit;
    lsmash_bs_t         *bs          = importer->bs;
    int                  complete_au = 0;
    access_unit->data_length = 0;
    while( 1 )
    {
        int      err;
        uint8_t  bdu_type;
        uint64_t trailing_zero_bytes;
        uint64_t ebdu_length = vc1_find_next_start_code_prefix( bs, &bdu_type, &trailing_zero_bytes );
        if( ebdu_length <= VC1_START_CODE_LENGTH && lsmash_bs_is_end( bs, ebdu_length ) )
        {
            /* For the last EBDU.
             * This EBDU already has been appended into the latest access unit and parsed. */
            vc1_complete_au( access_unit, &info->picture, probe );
            return vc1_get_au_internal_succeeded( vc1_imp );
        }
        else if( bdu_type == 0xFF )
        {
            lsmash_log( importer, LSMASH_LOG_ERROR, "a forbidden BDU type is detected.\n" );
            return vc1_get_au_internal_failed( vc1_imp, complete_au, LSMASH_ERR_INVALID_DATA );
        }
        uint64_t next_ebdu_head_pos = info->ebdu_head_pos
                                    + ebdu_length
                                    + trailing_zero_bytes;
#if 0
        if( probe )
        {
            fprintf( stderr, "BDU type: %"PRIu8"                    \n", bdu_type );
            fprintf( stderr, "    EBDU position: %"PRIx64"          \n", info->ebdu_head_pos );
            fprintf( stderr, "    EBDU length: %"PRIx64" (%"PRIu64")\n", ebdu_length, ebdu_length );
            fprintf( stderr, "    trailing_zero_bytes: %"PRIx64"    \n", trailing_zero_bytes );
            fprintf( stderr, "    Next EBDU position: %"PRIx64"     \n", next_ebdu_head_pos );
        }
#endif
        if( bdu_type >= 0x0A && bdu_type <= 0x0F )
        {
            /* Complete the current access unit if encountered delimiter of current access unit. */
            if( vc1_find_au_delimit_by_bdu_type( bdu_type, info->prev_bdu_type ) )
                /* The last video coded EBDU belongs to the access unit you want at this time. */
                complete_au = vc1_complete_au( access_unit, &info->picture, probe );
            /* Increase the buffer if needed. */
            uint64_t possible_au_length = access_unit->incomplete_data_length + ebdu_length;
            if( sb->bank->buffer_size < possible_au_length
             && (err = vc1_supplement_buffer( sb, access_unit, 2 * possible_au_length )) < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to increase the buffer size.\n" );
                return vc1_get_au_internal_failed( vc1_imp, complete_au, err );
            }
            /* Process EBDU by its BDU type and append it to access unit. */
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
                    if( (err = vc1_parse_advanced_picture( info->bits, &info->sequence, &info->picture, sb->rbdu, ebdu, ebdu_length )) < 0 )
                    {
                        lsmash_log( importer, LSMASH_LOG_ERROR, "failed to parse a frame.\n" );
                        return vc1_get_au_internal_failed( vc1_imp, complete_au, err );
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
                    if( (err = vc1_parse_entry_point_header( info, ebdu, ebdu_length, probe )) < 0 )
                    {
                        lsmash_log( importer, LSMASH_LOG_ERROR, "failed to parse an entry point.\n" );
                        return vc1_get_au_internal_failed( vc1_imp, complete_au, err );
                    }
                    /* Signal random access type of the frame that follows this entry-point header. */
                    info->picture.closed_gop        = info->entry_point.closed_entry_point;
                    info->picture.random_accessible = info->dvc1_param.multiple_sequence ? info->picture.start_of_sequence : 1;
                    break;
                case 0x0F : /* Sequence header
                             * [SEQ_SC][SEQ_L][EP_SC][EP_L][FRM_SC][PIC_L] ... */
                    if( (err = vc1_parse_sequence_header( info, ebdu, ebdu_length, probe )) < 0 )
                    {
                        lsmash_log( importer, LSMASH_LOG_ERROR, "failed to parse a sequence header.\n" );
                        return vc1_get_au_internal_failed( vc1_imp, complete_au, err );
                    }
                    /* The frame that is the first frame after this sequence header shall be a random accessible point. */
                    info->picture.start_of_sequence = 1;
                    if( probe && !vc1_imp->first_sequence.present )
                        vc1_imp->first_sequence = info->sequence;
                    break;
                default :   /* End-of-sequence (0x0A) */
                    break;
            }
            /* Append the current EBDU into the end of an incomplete access unit. */
            vc1_append_ebdu_to_au( access_unit, ebdu, ebdu_length, probe );
        }
        else    /* We don't support other BDU types such as user data yet. */
            return vc1_get_au_internal_failed( vc1_imp, complete_au, LSMASH_ERR_PATCH_WELCOME );
        /* Move to the first byte of the next EBDU. */
        info->prev_bdu_type = bdu_type;
        if( lsmash_bs_read_seek( bs, next_ebdu_head_pos, SEEK_SET ) != next_ebdu_head_pos )
        {
            lsmash_log( importer, LSMASH_LOG_ERROR, "failed to seek the next start code suffix.\n" );
            return vc1_get_au_internal_failed( vc1_imp, complete_au, LSMASH_ERR_NAMELESS );
        }
        /* Check if no more data to read from the stream. */
        if( !lsmash_bs_is_end( bs, VC1_START_CODE_PREFIX_LENGTH ) )
            info->ebdu_head_pos = next_ebdu_head_pos;
        /* If there is no more data in the stream, and flushed chunk of EBDUs, flush it as complete AU here. */
        else if( access_unit->incomplete_data_length && access_unit->data_length == 0 )
        {
            vc1_complete_au( access_unit, &info->picture, probe );
            return vc1_get_au_internal_succeeded( vc1_imp );
        }
        if( complete_au )
            return vc1_get_au_internal_succeeded( vc1_imp );
    }
}

static inline void vc1_importer_check_eof( importer_t *importer, vc1_access_unit_t *access_unit )
{
    if( lsmash_bs_is_end( importer->bs, 0 ) && access_unit->incomplete_data_length == 0 )
        importer->status = IMPORTER_EOF;
    else
        importer->status = IMPORTER_OK;
}

static int vc1_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    vc1_importer_t *vc1_imp = (vc1_importer_t *)importer->info;
    vc1_info_t     *info    = &vc1_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    int err = vc1_importer_get_access_unit_internal( importer, 0 );
    if( err < 0 )
    {
        importer->status = IMPORTER_ERROR;
        return err;
    }
    lsmash_sample_t *sample = lsmash_create_sample( vc1_imp->max_au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    vc1_access_unit_t *access_unit = &info->access_unit;
    vc1_importer_check_eof( importer, access_unit );
    sample->dts = vc1_imp->ts_list.timestamp[ access_unit->number - 1 ].dts;
    sample->cts = vc1_imp->ts_list.timestamp[ access_unit->number - 1 ].cts;
    sample->prop.leading = access_unit->independent
                                 || access_unit->non_bipredictive
                                 || sample->cts >= vc1_imp->last_ref_intra_cts
                                  ? ISOM_SAMPLE_IS_NOT_LEADING : ISOM_SAMPLE_IS_UNDECODABLE_LEADING;
    if( access_unit->independent && !access_unit->disposable )
        vc1_imp->last_ref_intra_cts = sample->cts;
    if( vc1_imp->composition_reordering_present && !access_unit->disposable && !access_unit->closed_gop )
        sample->prop.allow_earlier = QT_SAMPLE_EARLIER_PTS_ALLOWED;
    sample->prop.independent = access_unit->independent ? ISOM_SAMPLE_IS_INDEPENDENT : ISOM_SAMPLE_IS_NOT_INDEPENDENT;
    sample->prop.disposable  = access_unit->disposable  ? ISOM_SAMPLE_IS_DISPOSABLE  : ISOM_SAMPLE_IS_NOT_DISPOSABLE;
    sample->prop.redundant   = ISOM_SAMPLE_HAS_NO_REDUNDANCY;
    if( access_unit->random_accessible )
        /* All random access point is a sync sample even if it's an open RAP. */
        sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    sample->length = access_unit->data_length;
    memcpy( sample->data, access_unit->data, access_unit->data_length );
    return current_status;
}

static lsmash_video_summary_t *vc1_create_summary( vc1_info_t *info, vc1_sequence_header_t *sequence, uint32_t max_au_length )
{
    if( !info->sequence.present || !info->entry_point.present )
        return NULL;
    lsmash_video_summary_t *summary = (lsmash_video_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_VIDEO );
    if( !summary )
        return NULL;
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1,
                                                                           LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !specific )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    specific->data.unstructured = lsmash_create_vc1_specific_info( &info->dvc1_param, &specific->size );
    if( !specific->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( specific );
        return NULL;
    }
    summary->sample_type           = ISOM_CODEC_TYPE_VC_1_VIDEO;
    summary->max_au_length         = max_au_length;
    summary->timescale             = sequence->framerate_numerator;
    summary->timebase              = sequence->framerate_denominator;
    summary->vfr                   = !sequence->framerate_flag;
    summary->sample_per_field      = 0;
    summary->width                 = sequence->disp_horiz_size;
    summary->height                = sequence->disp_vert_size;
    summary->par_h                 = sequence->aspect_width;
    summary->par_v                 = sequence->aspect_height;
    summary->color.primaries_index = sequence->color_prim;
    summary->color.transfer_index  = sequence->transfer_char;
    summary->color.matrix_index    = sequence->matrix_coef;
    return summary;
}

static int vc1_analyze_whole_stream
(
    importer_t *importer
)
{
    /* Parse all EBDU in the stream for preparation of calculating timestamps. */
    uint32_t cts_alloc = (1 << 12) * sizeof(uint64_t);
    uint64_t *cts = lsmash_malloc( cts_alloc );
    if( !cts )
        return LSMASH_ERR_MEMORY_ALLOC; /* Failed to allocate CTS list */
    uint32_t num_access_units  = 0;
    uint32_t num_consecutive_b = 0;
    lsmash_class_t *logger = &(lsmash_class_t){ "VC-1" };
    lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as VC-1\r" );
    vc1_importer_t *vc1_imp = (vc1_importer_t *)importer->info;
    vc1_info_t     *info    = &vc1_imp->info;
    importer->status = IMPORTER_OK;
    int err;
    while( importer->status != IMPORTER_EOF )
    {
#if 0
        lsmash_log( &logger, LSMASH_LOG_INFO, "Analyzing stream as VC-1: %"PRIu32"\n", num_access_units + 1 );
#endif
        if( (err = vc1_importer_get_access_unit_internal( importer, 1 )) < 0 )
            goto fail;
        vc1_importer_check_eof( importer, &info->access_unit );
        /* In the case where B-pictures exist
         * Decode order
         *      I[0]P[1]P[2]B[3]B[4]P[5]...
         * DTS
         *        0   1   2   3   4   5 ...
         * Composition order
         *      I[0]P[1]B[3]B[4]P[2]P[5]...
         * CTS
         *        1   2   3   4   5   6 ...
         * We assumes B or BI-pictures always be present in the stream here. */
        if( !info->access_unit.disposable )
        {
            /* Apply CTS of the last B-picture plus 1 to the last non-B-picture. */
            if( num_access_units > num_consecutive_b )
                cts[ num_access_units - num_consecutive_b - 1 ] = num_access_units;
            num_consecutive_b = 0;
        }
        else    /* B or BI-picture */
        {
            /* B and BI-pictures shall be output or displayed in the same order as they are encoded. */
            cts[ num_access_units ] = num_access_units;
            ++num_consecutive_b;
            info->dvc1_param.bframe_present = 1;
        }
        if( cts_alloc <= num_access_units * sizeof(uint64_t) )
        {
            uint32_t alloc = 2 * num_access_units * sizeof(uint64_t);
            uint64_t *temp = lsmash_realloc( cts, alloc );
            if( !temp )
            {
                err = LSMASH_ERR_MEMORY_ALLOC;
                goto fail;  /* Failed to re-allocate CTS list */
            }
            cts = temp;
            cts_alloc = alloc;
        }
        vc1_imp->max_au_length = LSMASH_MAX( info->access_unit.data_length, vc1_imp->max_au_length );
        ++num_access_units;
    }
    if( num_access_units > num_consecutive_b )
        cts[ num_access_units - num_consecutive_b - 1 ] = num_access_units;
    else
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    /* Construct timestamps. */
    lsmash_media_ts_t *timestamp = lsmash_malloc( num_access_units * sizeof(lsmash_media_ts_t) );
    if( !timestamp )
    {
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;  /* Failed to allocate timestamp list */
    }
    for( uint32_t i = 1; i < num_access_units; i++ )
        if( cts[i] < cts[i - 1] )
        {
            vc1_imp->composition_reordering_present = 1;
            break;
        }
    if( vc1_imp->composition_reordering_present )
        for( uint32_t i = 0; i < num_access_units; i++ )
        {
            timestamp[i].cts = cts[i];
            timestamp[i].dts = i;
        }
    else
        for( uint32_t i = 0; i < num_access_units; i++ )
            timestamp[i].cts = timestamp[i].dts = i;
    lsmash_free( cts );
    lsmash_log_refresh_line( &logger );
#if 0
    for( uint32_t i = 0; i < num_access_units; i++ )
        fprintf( stderr, "Timestamp[%"PRIu32"]: DTS=%"PRIu64", CTS=%"PRIu64"\n", i, timestamp[i].dts, timestamp[i].cts );
#endif
    vc1_imp->ts_list.sample_count = num_access_units;
    vc1_imp->ts_list.timestamp    = timestamp;
    return 0;
fail:
    lsmash_log_refresh_line( &logger );
    lsmash_free( cts );
    return err;
}

static int vc1_importer_probe( importer_t *importer )
{
    /* Find the first start code. */
    vc1_importer_t *vc1_imp = create_vc1_importer( importer );
    if( !vc1_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = importer->bs;
    uint64_t first_ebdu_head_pos = 0;
    int err;
    while( 1 )
    {
        if( lsmash_bs_is_error( bs ) )
        {
            err = LSMASH_ERR_IO;
            goto fail;
        }
        /* The first EBDU in decoding order of the stream shall have start code (0x000001). */
        if( 0x000001 == lsmash_bs_show_be24( bs, first_ebdu_head_pos ) )
            break;
        /* Invalid if encountered any value of non-zero before the first start code. */
        if( lsmash_bs_show_byte( bs, first_ebdu_head_pos ) )
        {
            err = LSMASH_ERR_INVALID_DATA;
            goto fail;
        }
        ++first_ebdu_head_pos;
    }
    /* OK. It seems the stream has a sequence header of VC-1. */
    importer->info = vc1_imp;
    vc1_info_t *info = &vc1_imp->info;
    lsmash_bs_read_seek( bs, first_ebdu_head_pos, SEEK_SET );
    info->ebdu_head_pos = first_ebdu_head_pos;
    if( (err = vc1_analyze_whole_stream( importer )) < 0 )
        goto fail;
    lsmash_video_summary_t *summary = vc1_create_summary( info, &vc1_imp->first_sequence, vc1_imp->max_au_length );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    /* Go back to layer of the first EBDU. */
    importer->status = IMPORTER_OK;
    lsmash_bs_read_seek( bs, first_ebdu_head_pos, SEEK_SET );
    info->prev_bdu_type                  = 0xFF;    /* 0xFF is a forbidden value. */
    info->ebdu_head_pos                  = first_ebdu_head_pos;
    uint8_t *temp_access_unit            = info->access_unit.data;
    uint8_t *temp_incomplete_access_unit = info->access_unit.incomplete_data;
    memset( &info->access_unit, 0, sizeof(vc1_access_unit_t) );
    info->access_unit.data               = temp_access_unit;
    info->access_unit.incomplete_data    = temp_incomplete_access_unit;
    memset( &info->picture, 0, sizeof(vc1_picture_info_t) );
    return 0;
fail:
    remove_vc1_importer( vc1_imp );
    importer->info = NULL;
    lsmash_list_remove_entries( importer->summaries );
    return err;
}

static uint32_t vc1_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    vc1_importer_t *vc1_imp = (vc1_importer_t *)importer->info;
    if( !vc1_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    return vc1_imp->ts_list.sample_count
         ? 1
         : UINT32_MAX;    /* arbitrary */
}

const importer_functions vc1_importer =
{
    { "VC-1", offsetof( importer_t, log_level ) },
    1,
    vc1_importer_probe,
    vc1_importer_get_accessunit,
    vc1_importer_get_last_delta,
    vc1_importer_cleanup
};

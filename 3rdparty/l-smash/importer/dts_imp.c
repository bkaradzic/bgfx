/*****************************************************************************
 * dts_imp.c
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

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/***************************************************************************
    DTS importer
    ETSI TS 102 114 V1.2.1 (2002-12)
    ETSI TS 102 114 V1.3.1 (2011-08)
    ETSI TS 102 114 V1.4.1 (2012-09)
***************************************************************************/
#include "codecs/dts.h"

typedef struct
{
    dts_info_t info;
    uint64_t next_frame_pos;
    uint8_t  buffer[DTS_MAX_EXSS_SIZE];
    lsmash_multiple_buffers_t *au_buffers;
    uint8_t *au;
    uint32_t au_length;
    uint8_t *incomplete_au;
    uint32_t incomplete_au_length;
    uint32_t au_number;
} dts_importer_t;

static void remove_dts_importer( dts_importer_t *dts_imp )
{
    if( !dts_imp )
        return;
    lsmash_destroy_multiple_buffers( dts_imp->au_buffers );
    lsmash_bits_cleanup( dts_imp->info.bits );
    lsmash_free( dts_imp );
}

static dts_importer_t *create_dts_importer( importer_t *importer )
{
    dts_importer_t *dts_imp = (dts_importer_t *)lsmash_malloc_zero( sizeof(dts_importer_t) );
    if( !dts_imp )
        return NULL;
    dts_info_t *dts_info = &dts_imp->info;
    dts_info->bits = lsmash_bits_create( importer->bs );
    if( !dts_info->bits )
    {
        lsmash_free( dts_imp );
        return NULL;
    }
    dts_imp->au_buffers = lsmash_create_multiple_buffers( 2, DTS_MAX_EXSS_SIZE );
    if( !dts_imp->au_buffers )
    {
        lsmash_bits_cleanup( dts_info->bits );
        lsmash_free( dts_imp );
        return NULL;
    }
    dts_imp->au            = lsmash_withdraw_buffer( dts_imp->au_buffers, 1 );
    dts_imp->incomplete_au = lsmash_withdraw_buffer( dts_imp->au_buffers, 2 );
    dts_setup_parser( dts_info );
    return dts_imp;
}

static void dts_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_dts_importer( importer->info );
}

static int dts_importer_get_next_accessunit_internal( importer_t *importer )
{
    int au_completed = 0;
    dts_importer_t *dts_imp = (dts_importer_t *)importer->info;
    dts_info_t     *info    = &dts_imp->info;
    lsmash_bs_t    *bs      = info->bits->bs;
    while( !au_completed )
    {
        /* Read data from the stream if needed. */
        dts_imp->next_frame_pos += info->frame_size;
        lsmash_bs_read_seek( bs, dts_imp->next_frame_pos, SEEK_SET );
        uint64_t remain_size = lsmash_bs_get_remaining_buffer_size( bs );
        if( remain_size < DTS_MAX_EXSS_SIZE )
        {
            if( bs->buffer.pos > DTS_MAX_EXSS_SIZE * 100 )
                lsmash_bs_dispose_past_data( bs );
            int err = lsmash_bs_read( bs, bs->buffer.max_size );
            if( err < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to read data from the stream.\n" );
                return err;
            }
            remain_size = lsmash_bs_get_remaining_buffer_size( bs );
        }
        memcpy( dts_imp->buffer, lsmash_bs_get_buffer_data( bs ), LSMASH_MIN( remain_size, DTS_MAX_EXSS_SIZE ) );
        /* Check the remainder length of the buffer.
         * If there is enough length, then parse the frame in it.
         * The length 10 is the required byte length to get frame size. */
        if( bs->eob || (bs->eof && remain_size < 10) )
        {
            /* Reached the end of stream. */
            importer->status = IMPORTER_EOF;
            au_completed = !!dts_imp->incomplete_au_length;
            if( !au_completed )
            {
                /* No more access units in the stream. */
                if( lsmash_bs_get_remaining_buffer_size( bs ) )
                {
                    lsmash_log( importer, LSMASH_LOG_WARNING, "the stream is truncated at the end.\n" );
                    return LSMASH_ERR_INVALID_DATA;
                }
                return 0;
            }
            if( !info->ddts_param_initialized )
                dts_update_specific_param( info );
        }
        else
        {
            /* Parse substream frame. */
            dts_substream_type prev_substream_type = info->substream_type;
            info->substream_type = dts_get_substream_type( info );
            int err;
            int (*dts_parse_frame)( dts_info_t * ) = NULL;
            switch( info->substream_type )
            {
                /* Decide substream frame parser and check if this frame and the previous frame belong to the same AU. */
                case DTS_SUBSTREAM_TYPE_CORE :
                    if( prev_substream_type != DTS_SUBSTREAM_TYPE_NONE )
                        au_completed = 1;
                    dts_parse_frame = dts_parse_core_substream;
                    break;
                case DTS_SUBSTREAM_TYPE_EXTENSION :
                {
                    uint8_t prev_exss_index = info->exss_index;
                    if( (err = dts_get_exss_index( info, &info->exss_index )) < 0 )
                    {
                        lsmash_log( importer, LSMASH_LOG_ERROR, "failed to get the index of an extension substream.\n" );
                        return err;
                    }
                    if( prev_substream_type == DTS_SUBSTREAM_TYPE_EXTENSION
                     && info->exss_index <= prev_exss_index )
                        au_completed = 1;
                    dts_parse_frame = dts_parse_extension_substream;
                    break;
                }
                default :
                    lsmash_log( importer, LSMASH_LOG_ERROR, "unknown substream type is detected.\n" );
                    return LSMASH_ERR_NAMELESS;
            }
            if( !info->ddts_param_initialized && au_completed )
                dts_update_specific_param( info );
            info->frame_size = 0;
            if( (err = dts_parse_frame( info )) < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to parse a frame.\n" );
                return err;
            }
        }
        if( au_completed )
        {
            memcpy( dts_imp->au, dts_imp->incomplete_au, dts_imp->incomplete_au_length );
            dts_imp->au_length            = dts_imp->incomplete_au_length;
            dts_imp->incomplete_au_length = 0;
            info->exss_count = (info->substream_type == DTS_SUBSTREAM_TYPE_EXTENSION);
            if( importer->status == IMPORTER_EOF )
                break;
        }
        /* Increase buffer size to store AU if short. */
        if( dts_imp->incomplete_au_length + info->frame_size > dts_imp->au_buffers->buffer_size )
        {
            lsmash_multiple_buffers_t *temp = lsmash_resize_multiple_buffers( dts_imp->au_buffers,
                                                                              dts_imp->au_buffers->buffer_size + DTS_MAX_EXSS_SIZE );
            if( !temp )
                return LSMASH_ERR_MEMORY_ALLOC;
            dts_imp->au_buffers    = temp;
            dts_imp->au            = lsmash_withdraw_buffer( dts_imp->au_buffers, 1 );
            dts_imp->incomplete_au = lsmash_withdraw_buffer( dts_imp->au_buffers, 2 );
        }
        /* Append frame data. */
        memcpy( dts_imp->incomplete_au + dts_imp->incomplete_au_length, dts_imp->buffer, info->frame_size );
        dts_imp->incomplete_au_length += info->frame_size;
    }
    return bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    dts_importer_t *dts_imp = (dts_importer_t *)importer->info;
    dts_info_t     *info    = &dts_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF && dts_imp->au_length == 0 )
        return IMPORTER_EOF;
    if( current_status == IMPORTER_CHANGE )
        summary->max_au_length = 0;
    lsmash_sample_t *sample = lsmash_create_sample( dts_imp->au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    memcpy( sample->data, dts_imp->au, dts_imp->au_length );
    sample->length                 = dts_imp->au_length;
    sample->dts                    = dts_imp->au_number++ * summary->samples_in_frame;
    sample->cts                    = sample->dts;
    sample->prop.ra_flags          = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    sample->prop.pre_roll.distance = !!(info->flags & DTS_EXT_SUBSTREAM_LBR_FLAG);  /* MDCT */
    if( importer->status == IMPORTER_EOF )
    {
        dts_imp->au_length = 0;
        return 0;
    }
    if( dts_importer_get_next_accessunit_internal( importer ) < 0 )
        importer->status = IMPORTER_ERROR;
    return current_status;
}

static lsmash_audio_summary_t *dts_create_summary( dts_info_t *info )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    lsmash_dts_specific_parameters_t *param = &info->ddts_param;
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS,
                                                                           LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !specific )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    specific->data.unstructured = lsmash_create_dts_specific_info( param, &specific->size );
    if( !specific->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( specific );
        return NULL;
    }
    /* The CODEC identifiers probably should not be the combination of 'mp4a' and
     * the objectTypeIndications for DTS audio since there is no public specification
     * which defines the encapsulation of the stream as the MPEG-4 Audio context yet.
     * In the world, there are muxers which is using such doubtful implementation.
     * The objectTypeIndications are registered at MP4RA, but this does not always
     * mean we can mux by using those objectTypeIndications.
     * If available, there shall be the specification which defines the existence of
     * DecoderSpecificInfo and its semantics, and what access unit consists of. */
    summary->sample_type = lsmash_dts_get_codingname( param );
    summary->aot         = MP4A_AUDIO_OBJECT_TYPE_NULL;     /* make no sense */
    summary->sbr_mode    = MP4A_AAC_SBR_NOT_SPECIFIED;      /* make no sense */
    switch( param->DTSSamplingFrequency )
    {
        case 12000 :    /* Invalid? (No reference in the spec) */
        case 24000 :
        case 48000 :
        case 96000 :
        case 192000 :
        case 384000 :   /* Invalid? (No reference in the spec) */
            summary->frequency = 48000;
            break;
        case 22050 :
        case 44100 :
        case 88200 :
        case 176400 :
        case 352800 :   /* Invalid? (No reference in the spec) */
            summary->frequency = 44100;
            break;
        case 8000 :     /* Invalid? (No reference in the spec) */
        case 16000 :
        case 32000 :
        case 64000 :
        case 128000 :
            summary->frequency = 32000;
            break;
        default :
            summary->frequency = 0;
            break;
    }
    summary->samples_in_frame = (summary->frequency * info->frame_duration) / param->DTSSamplingFrequency;
    summary->max_au_length    = DTS_MAX_CORE_SIZE + DTS_MAX_NUM_EXSS * DTS_MAX_EXSS_SIZE;
    summary->sample_size      = param->pcmSampleDepth;
    summary->channels         = dts_get_max_channel_count( info );
    return summary;
}

static int dts_importer_probe( importer_t *importer )
{
    dts_importer_t *dts_imp = create_dts_importer( importer );
    if( !dts_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bits_t *bits = dts_imp->info.bits;
    lsmash_bs_t   *bs   = bits->bs;
    bs->buffer.max_size = DTS_MAX_EXSS_SIZE;
    importer->info = dts_imp;
    int err = dts_importer_get_next_accessunit_internal( importer );
    if( err < 0 )
        goto fail;
    lsmash_audio_summary_t *summary = dts_create_summary( &dts_imp->info );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    if( importer->status != IMPORTER_EOF )
        importer->status = IMPORTER_OK;
    dts_imp->au_number = 0;
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    return 0;
fail:
    remove_dts_importer( dts_imp );
    importer->info = NULL;
    return err;
}

static uint32_t dts_importer_get_last_delta( importer_t* importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    dts_importer_t *dts_imp = (dts_importer_t *)importer->info;
    if( !dts_imp || track_number != 1 || importer->status != IMPORTER_EOF || dts_imp->au_length )
        return 0;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return 0;
    return (summary->frequency * dts_imp->info.frame_duration) / dts_imp->info.ddts_param.DTSSamplingFrequency;
}

const importer_functions dts_importer =
{
    { "DTS Coherent Acoustics", offsetof( importer_t, log_level ) },
    1,
    dts_importer_probe,
    dts_importer_get_accessunit,
    dts_importer_get_last_delta,
    dts_importer_cleanup
};

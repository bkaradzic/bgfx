/*****************************************************************************
 * a52_imp.c
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

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/***************************************************************************
    AC-3 importer
    ETSI TS 102 366 V1.2.1 (2008-08)
***************************************************************************/
#include "codecs/a52.h"

#define AC3_SAMPLE_DURATION 1536    /* 256 (samples per audio block) * 6 (audio blocks) */

typedef struct
{
    ac3_info_t info;
    uint64_t   next_frame_pos;
    uint8_t   *next_dac3;
    uint8_t    buffer[AC3_MAX_SYNCFRAME_LENGTH];
    uint32_t   au_number;
} ac3_importer_t;

static void remove_ac3_importer( ac3_importer_t *ac3_imp )
{
    if( !ac3_imp )
        return;
    lsmash_bits_cleanup( ac3_imp->info.bits );
    lsmash_free( ac3_imp );
}

static ac3_importer_t *create_ac3_importer( importer_t *importer )
{
    ac3_importer_t *ac3_imp = (ac3_importer_t *)lsmash_malloc_zero( sizeof(ac3_importer_t) );
    if( !ac3_imp )
        return NULL;
    ac3_imp->info.bits = lsmash_bits_create( importer->bs );
    if( !ac3_imp->info.bits )
    {
        lsmash_free( ac3_imp );
        return NULL;
    }
    return ac3_imp;
}

static void ac3_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_ac3_importer( importer->info );
}

static const uint32_t ac3_frame_size_table[19][3] =
{
    /*  48,  44.1,    32 */
    {  128,   138,   192 },
    {  160,   174,   240 },
    {  192,   208,   288 },
    {  224,   242,   336 },
    {  256,   278,   384 },
    {  320,   348,   480 },
    {  384,   416,   576 },
    {  448,   486,   672 },
    {  512,   556,   768 },
    {  640,   696,   960 },
    {  768,   834,  1152 },
    {  896,   974,  1344 },
    { 1024,  1114,  1536 },
    { 1280,  1392,  1920 },
    { 1536,  1670,  2304 },
    { 1792,  1950,  2688 },
    { 2048,  2228,  3072 },
    { 2304,  2506,  3456 },
    { 2560,  2786,  3840 }
};

static lsmash_audio_summary_t *ac3_create_summary( ac3_info_t *info )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    lsmash_ac3_specific_parameters_t *param = &info->dac3_param;
    lsmash_codec_specific_t *cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3,
                                                                     LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !cs )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    cs->data.unstructured = lsmash_create_ac3_specific_info( &info->dac3_param, &cs->size );
    if( !cs->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, cs ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    summary->sample_type      = ISOM_CODEC_TYPE_AC_3_AUDIO;
    summary->max_au_length    = AC3_MAX_SYNCFRAME_LENGTH;
    summary->aot              = MP4A_AUDIO_OBJECT_TYPE_NULL;    /* no effect */
    summary->frequency        = ac3_get_sample_rate( param );
    summary->channels         = ac3_get_channel_count( param );
    summary->sample_size      = 16;                             /* no effect */
    summary->samples_in_frame = AC3_SAMPLE_DURATION;
    summary->sbr_mode         = MP4A_AAC_SBR_NOT_SPECIFIED;     /* no effect */
    return summary;
}

static int ac3_compare_specific_param( lsmash_ac3_specific_parameters_t *a, lsmash_ac3_specific_parameters_t *b )
{
    return (a->fscod             != b->fscod)
        || (a->bsid              != b->bsid)
        || (a->bsmod             != b->bsmod)
        || (a->acmod             != b->acmod)
        || (a->lfeon             != b->lfeon)
        || ((a->frmsizecod >> 1) != (b->frmsizecod >> 1));
}

static int ac3_buffer_frame( uint8_t *buffer, lsmash_bs_t *bs )
{
    uint64_t remain_size = lsmash_bs_get_remaining_buffer_size( bs );
    if( remain_size < AC3_MAX_SYNCFRAME_LENGTH )
    {
        if( bs->buffer.pos > AC3_MAX_SYNCFRAME_LENGTH * 1000 )
            lsmash_bs_dispose_past_data( bs );
        int err = lsmash_bs_read( bs, bs->buffer.max_size );
        if( err < 0 )
            return err;
        remain_size = lsmash_bs_get_remaining_buffer_size( bs );
    }
    uint64_t copy_size = LSMASH_MIN( remain_size, AC3_MAX_SYNCFRAME_LENGTH );
    memcpy( buffer, lsmash_bs_get_buffer_data( bs ), copy_size );
    return 0;
}

static int ac3_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    ac3_importer_t *ac3_imp = (ac3_importer_t *)importer->info;
    ac3_info_t     *info    = &ac3_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    lsmash_ac3_specific_parameters_t *param = &info->dac3_param;
    uint32_t frame_size = ac3_frame_size_table[ param->frmsizecod >> 1 ][ param->fscod ];
    if( param->fscod == 0x1 && param->frmsizecod & 0x1 )
        frame_size += 2;
    if( current_status == IMPORTER_CHANGE )
    {
        lsmash_codec_specific_t *cs = isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 );
        if( cs )
        {
            cs->destruct( cs->data.unstructured );
            cs->data.unstructured = ac3_imp->next_dac3;
        }
        summary->frequency  = ac3_get_sample_rate( param );
        summary->channels   = ac3_get_channel_count( param );
        //summary->layout_tag = ac3_channel_layout_table[ param->acmod ][ param->lfeon ];
    }
    lsmash_sample_t *sample = lsmash_create_sample( frame_size );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    memcpy( sample->data, ac3_imp->buffer, frame_size );
    sample->length                 = frame_size;
    sample->dts                    = ac3_imp->au_number++ * summary->samples_in_frame;
    sample->cts                    = sample->dts;
    sample->prop.ra_flags          = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    sample->prop.pre_roll.distance = 1; /* MDCT */
    lsmash_bs_t *bs = info->bits->bs;
    ac3_imp->next_frame_pos += frame_size;
    lsmash_bs_read_seek( bs, ac3_imp->next_frame_pos, SEEK_SET );
    uint8_t syncword[2] =
    {
        lsmash_bs_show_byte( bs, 0 ),
        lsmash_bs_show_byte( bs, 1 )
    };
    if( bs->eob || (bs->eof && 0 == lsmash_bs_get_remaining_buffer_size( bs )) )
        importer->status = IMPORTER_EOF;
    else
    {
        /* Parse the next syncframe header. */
        if( syncword[0] != 0x0b
         || syncword[1] != 0x77
         || ac3_buffer_frame( ac3_imp->buffer, bs ) < 0 )
        {
            importer->status = IMPORTER_ERROR;
            return current_status;
        }
        lsmash_ac3_specific_parameters_t current_param = info->dac3_param;
        ac3_parse_syncframe_header( info );
        if( ac3_compare_specific_param( &current_param, &info->dac3_param ) )
        {
            uint32_t dummy;
            uint8_t *dac3 = lsmash_create_ac3_specific_info( &info->dac3_param, &dummy );
            if( !dac3 )
            {
                importer->status = IMPORTER_ERROR;
                return current_status;
            }
            ac3_imp->next_dac3 = dac3;
            importer->status = IMPORTER_CHANGE;
        }
        else
            importer->status = IMPORTER_OK;
    }
    return current_status;
}

static int ac3_importer_probe( importer_t *importer )
{
    ac3_importer_t *ac3_imp = create_ac3_importer( importer );
    if( !ac3_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bits_t *bits = ac3_imp->info.bits;
    lsmash_bs_t   *bs   = bits->bs;
    bs->buffer.max_size = AC3_MAX_SYNCFRAME_LENGTH;
    /* Check the syncword and parse the syncframe header */
    int err;
    if( lsmash_bs_show_byte( bs, 0 ) != 0x0b
     || lsmash_bs_show_byte( bs, 1 ) != 0x77 )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    if( (err = ac3_buffer_frame( ac3_imp->buffer, bs ))      < 0
     || (err = ac3_parse_syncframe_header( &ac3_imp->info )) < 0 )
        goto fail;
    lsmash_audio_summary_t *summary = ac3_create_summary( &ac3_imp->info );
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
    ac3_imp->au_number = 0;
    importer->info   = ac3_imp;
    importer->status = IMPORTER_OK;
    return 0;
fail:
    remove_ac3_importer( ac3_imp );
    return err;
}

static uint32_t ac3_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    ac3_importer_t *ac3_imp = (ac3_importer_t *)importer->info;
    if( !ac3_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    return AC3_SAMPLE_DURATION;
}

const importer_functions ac3_importer =
{
    { "AC-3" },
    1,
    ac3_importer_probe,
    ac3_importer_get_accessunit,
    ac3_importer_get_last_delta,
    ac3_importer_cleanup
};

/***************************************************************************
    Enhanced AC-3 importer
    ETSI TS 102 366 V1.2.1 (2008-08)
***************************************************************************/
#define EAC3_MIN_SAMPLE_DURATION 256

typedef struct
{
    eac3_info_t info;
    uint64_t next_frame_pos;
    uint32_t next_dec3_length;
    uint8_t *next_dec3;
    uint8_t  current_fscod2;
    uint8_t  buffer[EAC3_MAX_SYNCFRAME_LENGTH];
    lsmash_multiple_buffers_t *au_buffers;
    uint8_t *au;
    uint8_t *incomplete_au;
    uint32_t au_length;
    uint32_t incomplete_au_length;
    uint32_t au_number;
    uint32_t syncframe_count_in_au;
} eac3_importer_t;

static void remove_eac3_importer( eac3_importer_t *eac3_imp )
{
    if( !eac3_imp )
        return;
    lsmash_destroy_multiple_buffers( eac3_imp->au_buffers );
    lsmash_bits_cleanup( eac3_imp->info.bits );
    lsmash_free( eac3_imp );
}

static eac3_importer_t *create_eac3_importer( importer_t *importer )
{
    eac3_importer_t *eac3_imp = (eac3_importer_t *)lsmash_malloc_zero( sizeof(eac3_importer_t) );
    if( !eac3_imp )
        return NULL;
    eac3_info_t *info = &eac3_imp->info;
    info->bits = lsmash_bits_create( importer->bs );
    if( !info->bits )
    {
        lsmash_free( eac3_imp );
        return NULL;
    }
    eac3_imp->au_buffers = lsmash_create_multiple_buffers( 2, EAC3_MAX_SYNCFRAME_LENGTH );
    if( !eac3_imp->au_buffers )
    {
        lsmash_bits_cleanup( info->bits );
        lsmash_free( eac3_imp );
        return NULL;
    }
    eac3_imp->au            = lsmash_withdraw_buffer( eac3_imp->au_buffers, 1 );
    eac3_imp->incomplete_au = lsmash_withdraw_buffer( eac3_imp->au_buffers, 2 );
    return eac3_imp;
}

static void eac3_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_eac3_importer( importer->info );
}

static int eac3_importer_get_next_accessunit_internal( importer_t *importer )
{
    int au_completed = 0;
    eac3_importer_t *eac3_imp = (eac3_importer_t *)importer->info;
    eac3_info_t     *info     = &eac3_imp->info;
    lsmash_bs_t     *bs       = info->bits->bs;
    while( !au_completed )
    {
        /* Read data from the stream if needed. */
        eac3_imp->next_frame_pos += info->frame_size;
        lsmash_bs_read_seek( bs, eac3_imp->next_frame_pos, SEEK_SET );
        uint64_t remain_size = lsmash_bs_get_remaining_buffer_size( bs );
        if( remain_size < EAC3_MAX_SYNCFRAME_LENGTH )
        {
            if( bs->buffer.pos > EAC3_MAX_SYNCFRAME_LENGTH * 1000 )
                lsmash_bs_dispose_past_data( bs );
            int err = lsmash_bs_read( bs, bs->buffer.max_size );
            if( err < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to read data from the stream.\n" );
                return err;
            }
            remain_size = lsmash_bs_get_remaining_buffer_size( bs );
        }
        uint64_t copy_size = LSMASH_MIN( remain_size, EAC3_MAX_SYNCFRAME_LENGTH );
        memcpy( eac3_imp->buffer, lsmash_bs_get_buffer_data( bs ), copy_size );
        /* Check the remainder length of the buffer.
         * If there is enough length, then parse the syncframe in it.
         * The length 5 is the required byte length to get frame size. */
        if( bs->eob || (bs->eof && remain_size < 5) )
        {
            /* Reached the end of stream.
             * According to ETSI TS 102 366 V1.2.1 (2008-08),
             * one access unit consists of 6 audio blocks and begins with independent substream 0.
             * The specification doesn't mention the case where a enhanced AC-3 stream ends at non-mod6 audio blocks.
             * At the end of the stream, therefore, we might make an access unit which has less than 6 audio blocks anyway. */
            importer->status = IMPORTER_EOF;
            au_completed = !!eac3_imp->incomplete_au_length;
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
            if( !info->dec3_param_initialized )
                eac3_update_specific_param( info );
        }
        else
        {
            /* Check the syncword. */
            if( lsmash_bs_show_byte( bs, 0 ) != 0x0b
             || lsmash_bs_show_byte( bs, 1 ) != 0x77 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "a syncword is not found.\n" );
                return LSMASH_ERR_INVALID_DATA;
            }
            /* Parse syncframe. */
            info->frame_size = 0;
            int err = eac3_parse_syncframe( info );
            if( err < 0 )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "failed to parse syncframe.\n" );
                return err;
            }
            if( remain_size < info->frame_size )
            {
                lsmash_log( importer, LSMASH_LOG_ERROR, "a frame is truncated.\n" );
                return LSMASH_ERR_INVALID_DATA;
            }
            int independent = info->strmtyp != 0x1;
            if( independent && info->substreamid == 0x0 )
            {
                if( info->number_of_audio_blocks == 6 )
                {
                    /* Encountered the first syncframe of the next access unit. */
                    info->number_of_audio_blocks = 0;
                    au_completed = 1;
                }
                else if( info->number_of_audio_blocks > 6 )
                {
                    lsmash_log( importer, LSMASH_LOG_ERROR, "greater than 6 consecutive independent substreams.\n" );
                    return LSMASH_ERR_INVALID_DATA;
                }
                info->number_of_audio_blocks += eac3_audio_block_table[ info->numblkscod ];
                info->number_of_independent_substreams = 0;
                eac3_imp->current_fscod2 = info->fscod2;
            }
            else if( info->syncframe_count == 0 )
            {
                /* The first syncframe in an AU must be independent and assigned substream ID 0. */
                lsmash_log( importer, LSMASH_LOG_ERROR, "the first syncframe is NOT an independent substream.\n" );
                return LSMASH_ERR_INVALID_DATA;
            }
            if( independent )
                info->independent_info[info->number_of_independent_substreams ++].num_dep_sub = 0;
            else
                ++ info->independent_info[info->number_of_independent_substreams - 1].num_dep_sub;
        }
        if( au_completed )
        {
            memcpy( eac3_imp->au, eac3_imp->incomplete_au, eac3_imp->incomplete_au_length );
            eac3_imp->au_length             = eac3_imp->incomplete_au_length;
            eac3_imp->incomplete_au_length  = 0;
            eac3_imp->syncframe_count_in_au = info->syncframe_count;
            info->syncframe_count = 0;
            if( importer->status == IMPORTER_EOF )
                break;
        }
        /* Increase buffer size to store AU if short. */
        if( eac3_imp->incomplete_au_length + info->frame_size > eac3_imp->au_buffers->buffer_size )
        {
            lsmash_multiple_buffers_t *temp = lsmash_resize_multiple_buffers( eac3_imp->au_buffers,
                                                                              eac3_imp->au_buffers->buffer_size + EAC3_MAX_SYNCFRAME_LENGTH );
            if( !temp )
                return LSMASH_ERR_MEMORY_ALLOC;
            eac3_imp->au_buffers    = temp;
            eac3_imp->au            = lsmash_withdraw_buffer( eac3_imp->au_buffers, 1 );
            eac3_imp->incomplete_au = lsmash_withdraw_buffer( eac3_imp->au_buffers, 2 );
        }
        /* Append syncframe data. */
        memcpy( eac3_imp->incomplete_au + eac3_imp->incomplete_au_length, eac3_imp->buffer, info->frame_size );
        eac3_imp->incomplete_au_length += info->frame_size;
        ++ info->syncframe_count;
    }
    return bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int eac3_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    eac3_importer_t *eac3_imp = (eac3_importer_t *)importer->info;
    eac3_info_t     *info     = &eac3_imp->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF && eac3_imp->au_length == 0 )
        return IMPORTER_EOF;
    if( current_status == IMPORTER_CHANGE )
    {
        lsmash_codec_specific_t *cs = isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 );
        if( cs )
        {
            cs->destruct( cs->data.unstructured );
            cs->data.unstructured = eac3_imp->next_dec3;
            cs->size              = eac3_imp->next_dec3_length;
        }
        summary->max_au_length = eac3_imp->syncframe_count_in_au * EAC3_MAX_SYNCFRAME_LENGTH;
        eac3_update_sample_rate( &summary->frequency, &info->dec3_param, &eac3_imp->current_fscod2 );
        eac3_update_channel_count( &summary->channels, &info->dec3_param );
    }
    lsmash_sample_t *sample = lsmash_create_sample( eac3_imp->au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    memcpy( sample->data, eac3_imp->au, eac3_imp->au_length );
    sample->length                 = eac3_imp->au_length;
    sample->dts                    = eac3_imp->au_number++ * summary->samples_in_frame;
    sample->cts                    = sample->dts;
    sample->prop.ra_flags          = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    sample->prop.pre_roll.distance = 1; /* MDCT */
    if( importer->status == IMPORTER_EOF )
    {
        eac3_imp->au_length = 0;
        return 0;
    }
    uint32_t old_syncframe_count_in_au = eac3_imp->syncframe_count_in_au;
    if( eac3_importer_get_next_accessunit_internal( importer ) < 0 )
    {
        importer->status = IMPORTER_ERROR;
        return current_status;
    }
    if( eac3_imp->syncframe_count_in_au )
    {
        /* Check sample description change. */
        uint32_t new_length;
        uint8_t *dec3 = lsmash_create_eac3_specific_info( &info->dec3_param, &new_length );
        if( !dec3 )
        {
            importer->status = IMPORTER_ERROR;
            return current_status;
        }
        lsmash_codec_specific_t *cs = isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 );
        if( (eac3_imp->syncframe_count_in_au > old_syncframe_count_in_au)
         || (cs && (new_length != cs->size || memcmp( dec3, cs->data.unstructured, cs->size ))) )
        {
            importer->status = IMPORTER_CHANGE;
            eac3_imp->next_dec3        = dec3;
            eac3_imp->next_dec3_length = new_length;
        }
        else
        {
            if( importer->status != IMPORTER_EOF )
                importer->status = IMPORTER_OK;
            lsmash_free( dec3 );
        }
    }
    return current_status;
}

static lsmash_audio_summary_t *eac3_create_summary( eac3_importer_t *eac3_imp )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    eac3_info_t *info = &eac3_imp->info;
    lsmash_codec_specific_t *cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3,
                                                                     LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !cs )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    cs->data.unstructured = lsmash_create_eac3_specific_info( &info->dec3_param, &cs->size );
    if( !cs->data.unstructured
     || lsmash_list_add_entry( &summary->opaque->list, cs ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( cs );
        return NULL;
    }
    summary->sample_type      = ISOM_CODEC_TYPE_EC_3_AUDIO;
    summary->max_au_length    = eac3_imp->syncframe_count_in_au * EAC3_MAX_SYNCFRAME_LENGTH;
    summary->aot              = MP4A_AUDIO_OBJECT_TYPE_NULL;    /* no effect */
    summary->sample_size      = 16;                             /* no effect */
    summary->samples_in_frame = EAC3_MIN_SAMPLE_DURATION * 6;   /* 256 (samples per audio block) * 6 (audio blocks) */
    summary->sbr_mode         = MP4A_AAC_SBR_NOT_SPECIFIED;     /* no effect */
    eac3_update_sample_rate( &summary->frequency, &info->dec3_param, &eac3_imp->current_fscod2 );
    eac3_update_channel_count( &summary->channels, &info->dec3_param );
    return summary;
}

static int eac3_importer_probe( importer_t *importer )
{
    eac3_importer_t *eac3_imp = create_eac3_importer( importer );
    if( !eac3_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bits_t *bits = eac3_imp->info.bits;
    lsmash_bs_t   *bs   = bits->bs;
    bs->buffer.max_size = EAC3_MAX_SYNCFRAME_LENGTH;
    importer->info = eac3_imp;
    int err = eac3_importer_get_next_accessunit_internal( importer );
    if( err < 0 )
        goto fail;
    lsmash_audio_summary_t *summary = eac3_create_summary( eac3_imp );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    if( importer->status != IMPORTER_EOF )
        importer->status = IMPORTER_OK;
    eac3_imp->au_number = 0;
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    return 0;
fail:
    remove_eac3_importer( eac3_imp );
    importer->info      = NULL;
    return err;
}

static uint32_t eac3_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    eac3_importer_t *eac3_imp = (eac3_importer_t *)importer->info;
    if( !eac3_imp || track_number != 1 || importer->status != IMPORTER_EOF || eac3_imp->au_length )
        return 0;
    return EAC3_MIN_SAMPLE_DURATION * eac3_imp->info.number_of_audio_blocks;
}

const importer_functions eac3_importer =
{
    { "Enhanced AC-3", offsetof( importer_t, log_level ) },
    1,
    eac3_importer_probe,
    eac3_importer_get_accessunit,
    eac3_importer_get_last_delta,
    eac3_importer_cleanup
};

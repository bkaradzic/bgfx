/*****************************************************************************
 * wave_imp.c
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

#include <string.h>

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/*********************************************************************************
    Waveform Audio File Format (WAVE) importer

    References
        Multimedia Programming Interface and Data Specifications 1.0
        New Multimedia Data Types and Data Techniques April 15, 1994 Revision: 3.0
        Multiple channel audio data and WAVE files March 7, 2007
        Microsoft Windows SDK MMReg.h
**********************************************************************************/
#include "core/timeline.h"

#define WAVE_MIN_FILESIZE 45

#define WAVE_FORMAT_TYPE_ID_PCM        0x0001   /* WAVE_FORMAT_PCM */
#define WAVE_FORMAT_TYPE_ID_EXTENSIBLE 0xFFFE   /* WAVE_FORMAT_EXTENSIBLE */

#define PASS_GUID( _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15 ) \
                 { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15 }
#define DEFINE_WAVEFORMAT_EXTENSIBLE_SUBTYPE_GUID( name, value ) \
        static const uint8_t name[16] = value

/* KSDATAFORMAT_SUBTYPE_PCM := 00000001-0000-0010-8000-00aa00389b71 */
DEFINE_WAVEFORMAT_EXTENSIBLE_SUBTYPE_GUID
(
    WAVEFORMAT_EXTENSIBLE_SUBTYPE_GUID_PCM,
    PASS_GUID( 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
               0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71 )
);

typedef struct
{
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
} waveformat_extended_t;

typedef struct
{
    waveformat_extended_t wfx;
    union
    {
        uint16_t wValidBitsPerSample;
        uint16_t wSamplesPerBlock;
        uint16_t wReserved;
    } Samples;
    uint32_t dwChannelMask;
    uint8_t guid[16];
} waveformat_extensible_t;

typedef struct
{
    uint32_t number_of_samples;
    uint32_t au_length;
    uint32_t au_number;
    waveformat_extensible_t fmt;
    isom_portable_chunk_t   chunk;
} wave_importer_t;

static void remove_wave_importer( wave_importer_t *wave_imp )
{
    if( !wave_imp )
        return;
    lsmash_free( wave_imp );
}

static wave_importer_t *create_wave_importer( importer_t *importer )
{
    return (wave_importer_t *)lsmash_malloc_zero( sizeof(wave_importer_t) );
}

static void wave_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_wave_importer( importer->info );
}

static int wave_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    wave_importer_t *wave_imp = (wave_importer_t *)importer->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    if( wave_imp->number_of_samples / summary->samples_in_frame > wave_imp->au_number )
        wave_imp->au_length = summary->bytes_per_frame;
    else
    {
        wave_imp->au_length = wave_imp->fmt.wfx.nBlockAlign * (wave_imp->number_of_samples % summary->samples_in_frame);
        importer->status = IMPORTER_EOF;
        if( wave_imp->au_length == 0 )
            return IMPORTER_EOF;
    }
    lsmash_sample_t *sample = lsmash_create_sample( wave_imp->au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    if( lsmash_bs_get_bytes_ex( importer->bs, wave_imp->au_length, sample->data ) != wave_imp->au_length )
    {
        importer->status = IMPORTER_ERROR;
        return LSMASH_ERR_INVALID_DATA;
    }
    sample->length        = wave_imp->au_length;
    sample->dts           = wave_imp->au_number ++ * summary->samples_in_frame;
    sample->cts           = sample->dts;
    sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    return current_status;
}

static inline int wave_fmt_subtype_cmp( const waveformat_extensible_t *fmt, const uint8_t guid[16] )
{
    return memcmp( fmt->guid, guid, 16 );
}

static int wave_parse_fmt_chunk( wave_importer_t *wave_imp, lsmash_bs_t *bs )
{
    waveformat_extensible_t *fmt = &wave_imp->fmt;
    waveformat_extended_t   *wfx = &fmt->wfx;
    wfx->wFormatTag      = lsmash_bs_get_le16( bs );
    wfx->nChannels       = lsmash_bs_get_le16( bs );
    wfx->nSamplesPerSec  = lsmash_bs_get_le32( bs );
    wfx->nAvgBytesPerSec = lsmash_bs_get_le32( bs );
    wfx->nBlockAlign     = lsmash_bs_get_le16( bs );
    wfx->wBitsPerSample  = lsmash_bs_get_le16( bs );
    switch( wfx->wFormatTag )
    {
        case WAVE_FORMAT_TYPE_ID_PCM :
            return 0;
        case WAVE_FORMAT_TYPE_ID_EXTENSIBLE :
            wfx->cbSize = lsmash_bs_get_le16( bs );
            if( wfx->cbSize < 22 )
                return LSMASH_ERR_INVALID_DATA;
            fmt->Samples.wValidBitsPerSample = lsmash_bs_get_le16( bs );
            fmt->dwChannelMask               = lsmash_bs_get_le32( bs );
            if( lsmash_bs_get_bytes_ex( bs, 16, fmt->guid ) != 16 )
                return LSMASH_ERR_NAMELESS;
            /* We support only PCM audio currently. */
            if( wave_fmt_subtype_cmp( fmt, WAVEFORMAT_EXTENSIBLE_SUBTYPE_GUID_PCM ) )
                return LSMASH_ERR_INVALID_DATA;
            return 0;
        default :
            return LSMASH_ERR_NAMELESS;
    }
}

static lsmash_audio_summary_t *wave_create_summary( waveformat_extensible_t *fmt )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    waveformat_extended_t *wfx = &fmt->wfx;
    summary->sample_type      = QT_CODEC_TYPE_LPCM_AUDIO;
    summary->aot              = MP4A_AUDIO_OBJECT_TYPE_NULL;
    summary->frequency        = wfx->nSamplesPerSec;
    summary->channels         = wfx->nChannels;
    summary->sample_size      = wfx->wFormatTag == WAVE_FORMAT_TYPE_ID_EXTENSIBLE
                              ? fmt->Samples.wValidBitsPerSample
                              : wfx->wBitsPerSample;
    summary->samples_in_frame = 1000;   /* arbitrary */
    summary->sbr_mode         = MP4A_AAC_SBR_NOT_SPECIFIED;
    summary->bytes_per_frame  = wfx->nBlockAlign * summary->samples_in_frame;
    summary->max_au_length    = summary->bytes_per_frame;
    lsmash_codec_specific_t *cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS,
                                                                     LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !cs )
        goto fail;
    lsmash_qt_audio_format_specific_flags_t *lpcm = (lsmash_qt_audio_format_specific_flags_t *)cs->data.structured;
    if( (summary->sample_size & 7) == 0 )
        lpcm->format_flags |= QT_AUDIO_FORMAT_FLAG_PACKED;
    else
        lpcm->format_flags |= QT_AUDIO_FORMAT_FLAG_ALIGNED_HIGH;
    if( summary->sample_size > 8 )
        lpcm->format_flags |= QT_AUDIO_FORMAT_FLAG_SIGNED_INTEGER;
    if( lsmash_list_add_entry( &summary->opaque->list, cs ) < 0 )
    {
        lsmash_destroy_codec_specific_data( cs );
        goto fail;
    }
    if( wfx->wFormatTag == WAVE_FORMAT_TYPE_ID_EXTENSIBLE || wfx->nChannels > 2 )
    {
        cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT,
                                                LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
        if( !cs )
            goto fail;
        lsmash_qt_audio_channel_layout_t *layout = (lsmash_qt_audio_channel_layout_t *)cs->data.structured;
        if( wfx->wFormatTag == WAVE_FORMAT_TYPE_ID_EXTENSIBLE )
        {
            layout->channelLayoutTag = QT_CHANNEL_LAYOUT_USE_CHANNEL_BITMAP;
            layout->channelBitmap    = fmt->dwChannelMask;
        }
        else
        {
            layout->channelLayoutTag = QT_CHANNEL_LAYOUT_UNKNOWN | wfx->nChannels;
            layout->channelBitmap    = 0;
        }
        if( lsmash_list_add_entry( &summary->opaque->list, cs ) < 0 )
        {
            lsmash_destroy_codec_specific_data( cs );
            goto fail;
        }
    }
    return summary;
fail:
    lsmash_cleanup_summary( (lsmash_summary_t *)summary );
    return NULL;
}

static int wave_importer_probe( importer_t *importer )
{
    wave_importer_t *wave_imp = create_wave_importer( importer );
    if( !wave_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = 0;
    uint32_t filesize;
    lsmash_bs_t *bs = importer->bs;
    if( lsmash_bs_get_be32( bs ) != LSMASH_4CC( 'R', 'I', 'F', 'F' )
     || ((filesize = lsmash_bs_get_le32( bs ) + 8) < WAVE_MIN_FILESIZE && filesize > 8)
     || lsmash_bs_get_be32( bs ) != LSMASH_4CC( 'W', 'A', 'V', 'E' ) )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    int fmt_chunk_present  = 0;
    int data_chunk_present = 0;
    while( !bs->eob && !(fmt_chunk_present && data_chunk_present) )
    {
        uint32_t ckID   = lsmash_bs_get_be32( bs );
        uint32_t ckSize = lsmash_bs_get_le32( bs );
        lsmash_bs_reset_counter( bs );
        switch( ckID )
        {
            case LSMASH_4CC( 'f', 'm', 't', ' ' ) :
                if( ckSize < 16 )
                {
                    err = LSMASH_ERR_INVALID_DATA;
                    goto fail;
                }
                if( (err = wave_parse_fmt_chunk( wave_imp, bs )) < 0 )
                    goto fail;
                fmt_chunk_present = 1;
                break;
            case LSMASH_4CC( 'd', 'a', 't', 'a' ) :
                if( !fmt_chunk_present )
                {
                    /* The 'fmt ' chunk must be present before the 'data' chunk. */
                    err = LSMASH_ERR_INVALID_DATA;
                    goto fail;
                }
                wave_imp->chunk.data_offset = lsmash_bs_get_stream_pos( bs );
                wave_imp->chunk.length      = ckSize;
                wave_imp->chunk.number      = 1;
                wave_imp->chunk.file        = importer->file;
                wave_imp->number_of_samples = ckSize / wave_imp->fmt.wfx.nBlockAlign;
                data_chunk_present = 1;
                break;
            default :
                break;
        }
        if( !data_chunk_present )
        {
            /* Skip the rest of this chunk.
             * Note that ckData is word-aligned even if ckSize is an odd number. */
            uint32_t skip_size = ckSize;
            if( skip_size & 1 )
                skip_size++;
            if( skip_size > lsmash_bs_count( bs ) )
            {
                skip_size -= lsmash_bs_count( bs );
                lsmash_bs_read_seek( bs, skip_size, SEEK_CUR );
            }
        }
    }
    if( !(fmt_chunk_present && data_chunk_present) )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    /* Make fake movie.
     * Treat WAVE file format as if it's QuickTime file format. */
    uint32_t track_ID;
    lsmash_movie_parameters_t movie_param = { 0 };
    lsmash_track_parameters_t track_param = { 0 };
    lsmash_media_parameters_t media_param = { 0 };
    importer->file->qt_compatible = 1;
    if( (err = lsmash_importer_make_fake_movie( importer )) < 0
     || (err = lsmash_importer_make_fake_track( importer, ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK, &track_ID )) < 0
     || (err = lsmash_get_movie_parameters( importer->root, &movie_param )) < 0
     || (err = lsmash_get_track_parameters( importer->root, track_ID, &track_param )) < 0
     || (err = lsmash_get_media_parameters( importer->root, track_ID, &media_param )) < 0 )
        goto fail;
    movie_param.timescale = wave_imp->fmt.wfx.nSamplesPerSec;
    media_param.timescale = wave_imp->fmt.wfx.nSamplesPerSec;
    if( (err = lsmash_set_movie_parameters( importer->root, &movie_param )) < 0
     || (err = lsmash_set_track_parameters( importer->root, track_ID, &track_param )) < 0
     || (err = lsmash_set_media_parameters( importer->root, track_ID, &media_param )) < 0 )
        goto fail;
    lsmash_audio_summary_t *summary = wave_create_summary( &wave_imp->fmt );
    if( !summary || lsmash_add_sample_entry( importer->root, track_ID, summary ) != 1 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    if( (err = lsmash_list_add_entry( importer->summaries, summary )) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        goto fail;
    }
    importer->info   = wave_imp;
    importer->status = IMPORTER_OK;
    return 0;
fail:
    lsmash_importer_break_fake_movie( importer );
    remove_wave_importer( wave_imp );
    importer->file->qt_compatible = 0;
    importer->info = NULL;
    return err;
}

static uint32_t wave_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    wave_importer_t *wave_imp = (wave_importer_t *)importer->info;
    if( !wave_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return 0;
    return wave_imp->number_of_samples / summary->samples_in_frame >= wave_imp->au_number
         ? summary->samples_in_frame
         : (wave_imp->number_of_samples % summary->samples_in_frame);
}

static int wave_importer_construct_timeline( importer_t *importer, uint32_t track_number )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    isom_timeline_t *timeline = isom_timeline_create();
    if( !timeline )
        return LSMASH_ERR_NAMELESS;
    int err;
    lsmash_file_t *file = importer->file;
    if( !file->timeline )
    {
        /* TODO: this is not a proper place. It should be enclosed in isom_timeline_create(). */
        file->timeline = lsmash_list_create( isom_timeline_destroy );
        if( !file->timeline )
        {
            err = LSMASH_ERR_MEMORY_ALLOC;
            goto fail;
        }
    }
    wave_importer_t *wave_imp = (wave_importer_t *)importer->info;
    if( (err = isom_timeline_set_track_ID( timeline, 1 )) < 0
     || (err = isom_timeline_set_movie_timescale( timeline, wave_imp->fmt.wfx.nSamplesPerSec )) < 0
     || (err = isom_timeline_set_media_timescale( timeline, wave_imp->fmt.wfx.nSamplesPerSec )) < 0
     || (err = isom_timeline_set_sample_count( timeline, wave_imp->number_of_samples )) < 0
     || (err = isom_timeline_set_max_sample_size( timeline, summary->max_au_length )) < 0
     || (err = isom_timeline_set_media_duration( timeline, wave_imp->number_of_samples )) < 0
     || (err = isom_timeline_set_track_duration( timeline, wave_imp->number_of_samples )) < 0 )
        goto fail;
    isom_timeline_set_lpcm_sample_getter_funcs( timeline );
    uint64_t data_offset = wave_imp->chunk.data_offset;
    for( uint32_t samples = 0; samples < wave_imp->number_of_samples; samples += summary->samples_in_frame )
    {
        uint32_t duration;
        if( wave_imp->number_of_samples - samples >= summary->samples_in_frame )
            duration = summary->samples_in_frame;
        else
            duration = wave_imp->number_of_samples - samples;
        isom_lpcm_bunch_t bunch =
        {
            .pos          = data_offset,
            .duration     = 1,
            .offset       = 0,
            .length       = wave_imp->fmt.wfx.nBlockAlign,
            .index        = 1, /* no changes */
            .chunk        = &wave_imp->chunk,
            .prop         = (lsmash_sample_property_t){ .ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC },
            .sample_count = duration
        };
        data_offset += duration * wave_imp->fmt.wfx.nBlockAlign;
        if( (err = isom_add_lpcm_bunch_entry( timeline, &bunch )) < 0 )
            goto fail;
    }
    if( (err = lsmash_list_add_entry( file->timeline, timeline )) < 0 )
        goto fail;
    return 0;
fail:
    isom_timeline_destroy( timeline );
    isom_remove_timelines( file );
    return err;
}

const importer_functions wave_importer =
{
    { "WAVE", offsetof( importer_t, log_level ) },
    1,
    wave_importer_probe,
    wave_importer_get_accessunit,
    wave_importer_get_last_delta,
    wave_importer_cleanup,
    wave_importer_construct_timeline
};

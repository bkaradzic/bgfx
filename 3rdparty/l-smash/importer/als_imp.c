/*****************************************************************************
 * als_imp.c
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
    MPEG-4 ALS importer
    ISO/IEC 14496-3 2009 Fourth edition
***************************************************************************/
#include "codecs/mp4a.h"

#define ALSSC_TWELVE_LENGTH 22

typedef struct
{
    uint32_t  size;
    uint32_t  samp_freq;
    uint32_t  samples;
    uint32_t  channels;
    uint16_t  frame_length;
    uint8_t   resolution;
    uint8_t   random_access;
    uint8_t   ra_flag;
    uint32_t  access_unit_size;
    uint32_t  number_of_ra_units;
    uint32_t *ra_unit_size;
    uint8_t  *sc_data;
    size_t    alloc;
} als_specific_config_t;

typedef struct
{
    als_specific_config_t  alssc;
    uint32_t               samples_in_frame;
    uint32_t               au_number;
} mp4a_als_importer_t;

static void remove_mp4a_als_importer( mp4a_als_importer_t *als_imp )
{
    lsmash_free( als_imp->alssc.ra_unit_size );
    lsmash_free( als_imp->alssc.sc_data );
    lsmash_free( als_imp );
}

static void mp4a_als_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_mp4a_als_importer( importer->info );
}

static mp4a_als_importer_t *create_mp4a_als_importer( importer_t *importer )
{
    return (mp4a_als_importer_t *)lsmash_malloc_zero( sizeof(mp4a_als_importer_t) );
}

static void als_copy_from_buffer( als_specific_config_t *alssc, lsmash_bs_t *bs, uint64_t size )
{
    if( alssc->alloc < size )
    {
        size_t alloc = alssc->alloc ? (alssc->alloc << 1) : (1 << 10);
        uint8_t *temp = lsmash_realloc( alssc->sc_data, alloc );
        if( !temp )
            return;
        alssc->sc_data = temp;
        alssc->alloc   = alloc;
    }
    memcpy( alssc->sc_data + alssc->size, lsmash_bs_get_buffer_data( bs ), size );
    alssc->size += size;
    lsmash_bs_read_seek( bs, size, SEEK_CUR );
}

static int als_parse_specific_config( lsmash_bs_t *bs, mp4a_als_importer_t *als_imp )
{
    /* Check ALS identifier( = 0x414C5300). */
    if( 0x414C5300 != lsmash_bs_show_be32( bs, 0 ) )
        return LSMASH_ERR_INVALID_DATA;
    als_specific_config_t *alssc = &als_imp->alssc;
    alssc->samp_freq     = lsmash_bs_show_be32( bs, 4 );
    alssc->samples       = lsmash_bs_show_be32( bs, 8 );
    if( alssc->samples == 0xffffffff )
        return LSMASH_ERR_PATCH_WELCOME;    /* We don't support this case. */
    alssc->channels      = lsmash_bs_show_be16( bs, 12 );
    alssc->resolution    = (lsmash_bs_show_byte( bs, 14 ) & 0x1c) >> 2;
    if( alssc->resolution > 3 )
        return LSMASH_ERR_NAMELESS; /* reserved */
    alssc->frame_length  = lsmash_bs_show_be16( bs, 15 );
    alssc->random_access = lsmash_bs_show_byte( bs, 17 );
    alssc->ra_flag       = (lsmash_bs_show_byte( bs, 18 ) & 0xc0) >> 6;
    if( alssc->ra_flag == 0 )
        return LSMASH_ERR_PATCH_WELCOME;    /* We don't support this case. */
#if 0
    if( alssc->samples == 0xffffffff && alssc->ra_flag == 2 )
        return LSMASH_ERR_NAMELESS;
#endif
    uint8_t temp8 = lsmash_bs_show_byte( bs, 20 );
    int chan_sort = !!(temp8 & 0x1);
    if( alssc->channels == 0 )
    {
        if( temp8 & 0x8 )
            return LSMASH_ERR_INVALID_DATA; /* If channels = 0 (mono), joint_stereo = 0. */
        else if( temp8 & 0x4 )
            return LSMASH_ERR_INVALID_DATA; /* If channels = 0 (mono), mc_coding = 0. */
        else if( chan_sort )
            return LSMASH_ERR_INVALID_DATA; /* If channels = 0 (mono), chan_sort = 0. */
    }
    int chan_config      = !!(temp8 & 0x2);
    temp8 = lsmash_bs_show_byte( bs, 21 );
    int crc_enabled      = !!(temp8 & 0x80);
    int aux_data_enabled = !!(temp8 & 0x1);
    als_copy_from_buffer( alssc, bs, ALSSC_TWELVE_LENGTH );
    if( chan_config )
    {
        /* chan_config_info */
        lsmash_bs_read( bs, 2 );
        als_copy_from_buffer( alssc, bs, 2 );
    }
    if( chan_sort )
    {
        uint32_t ChBits = lsmash_ceil_log2( alssc->channels + 1 );
        uint32_t chan_pos_length = (alssc->channels + 1) * ChBits;
        chan_pos_length = ((uint64_t)chan_pos_length + 7) / 8;    /* byte_align */
        lsmash_bs_read( bs, chan_pos_length );
        als_copy_from_buffer( alssc, bs, chan_pos_length );
    }
    /* orig_header, orig_trailer and crc. */
    {
        uint32_t header_size  = lsmash_bs_show_be32( bs, 0 );
        uint32_t trailer_size = lsmash_bs_show_be32( bs, 4 );
        als_copy_from_buffer( alssc, bs, 8 );
        if( header_size != 0xffffffff )
        {
            lsmash_bs_read( bs, header_size );
            als_copy_from_buffer( alssc, bs, header_size );
        }
        if( trailer_size != 0xffffffff )
        {
            lsmash_bs_read( bs, trailer_size );
            als_copy_from_buffer( alssc, bs, trailer_size );
        }
        if( crc_enabled )
        {
            lsmash_bs_read( bs, 4 );
            als_copy_from_buffer( alssc, bs, 4 );
        }
    }
    /* Random access units */
    {
        uint32_t number_of_frames = ((alssc->samples + alssc->frame_length) / (alssc->frame_length + 1));
        if( alssc->random_access != 0 )
            alssc->number_of_ra_units = ((uint64_t)number_of_frames + alssc->random_access - 1) / alssc->random_access;
        else
            alssc->number_of_ra_units = 0;
        if( alssc->ra_flag == 2 && alssc->random_access != 0 )
        {
            /* We don't copy all ra_unit_size into alssc->sc_data. */
            int64_t read_size  = (int64_t)alssc->number_of_ra_units * 4;
            int64_t end_offset = lsmash_bs_get_stream_pos( bs ) + read_size;
            alssc->ra_unit_size = lsmash_malloc( read_size );
            if( !alssc->ra_unit_size )
                return LSMASH_ERR_MEMORY_ALLOC;
            uint32_t max_ra_unit_size = 0;
            for( uint32_t i = 0; i < alssc->number_of_ra_units; i++ )
            {
                alssc->ra_unit_size[i] = lsmash_bs_get_be32( bs );
                max_ra_unit_size = LSMASH_MAX( max_ra_unit_size, alssc->ra_unit_size[i] );
            }
            lsmash_bs_read_seek( bs, end_offset, SEEK_SET );
        }
        else
            alssc->ra_unit_size = NULL;
    }
    /* auxiliary data */
    if( aux_data_enabled )
    {
        uint32_t aux_size = lsmash_bs_show_be32( bs, 0 );
        als_copy_from_buffer( alssc, bs, 4 );
        if( aux_size && aux_size != 0xffffffff )
        {
            lsmash_bs_read( bs, aux_size );
            als_copy_from_buffer( alssc, bs, aux_size );
        }
    }
    /* Set 0 to ra_flag. We will remove ra_unit_size in each access unit. */
    alssc->sc_data[18] &= 0x3f;
    return 0;
}

static int mp4a_als_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_list_get_entry_data( importer->summaries, track_number );
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    mp4a_als_importer_t *als_imp = (mp4a_als_importer_t *)importer->info;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    lsmash_bs_t *bs = importer->bs;
    als_specific_config_t *alssc = &als_imp->alssc;
    if( alssc->number_of_ra_units == 0 )
    {
        lsmash_sample_t *sample = lsmash_create_sample( alssc->access_unit_size );
        if( !sample )
            return LSMASH_ERR_MEMORY_ALLOC;
        *p_sample = sample;
        memcpy( sample->data, lsmash_bs_get_buffer_data( bs ), alssc->access_unit_size );
        sample->length        = alssc->access_unit_size;
        sample->cts           = 0;
        sample->dts           = 0;
        sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
        importer->status = IMPORTER_EOF;
        return 0;
    }
    uint32_t au_length;
    if( alssc->ra_flag == 2 )
        au_length = alssc->ra_unit_size[ als_imp->au_number ];
    else /* if( alssc->ra_flag == 1 ) */
        /* We don't export ra_unit_size into a sample. */
        au_length = lsmash_bs_get_be32( bs );
    lsmash_sample_t *sample = lsmash_create_sample( au_length );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    if( lsmash_bs_get_bytes_ex( bs, au_length, sample->data ) != au_length )
    {
        lsmash_log( importer, LSMASH_LOG_WARNING, "failed to read an access unit.\n" );
        importer->status = IMPORTER_ERROR;
        return LSMASH_ERR_INVALID_DATA;
    }
    sample->length        = au_length;
    sample->dts           = als_imp->au_number ++ * als_imp->samples_in_frame;
    sample->cts           = sample->dts;
    sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    if( als_imp->au_number == alssc->number_of_ra_units )
        importer->status = IMPORTER_EOF;
    return 0;
}

#undef CHECK_UPDATE

static lsmash_audio_summary_t *als_create_summary( lsmash_bs_t *bs, als_specific_config_t *alssc )
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    summary->sample_type = ISOM_CODEC_TYPE_MP4A_AUDIO;
    summary->aot         = MP4A_AUDIO_OBJECT_TYPE_ALS;
    summary->frequency   = alssc->samp_freq;
    summary->channels    = alssc->channels + 1;
    summary->sample_size = (alssc->resolution + 1) * 8;
    summary->sbr_mode    = MP4A_AAC_SBR_NOT_SPECIFIED; /* no effect */
    if( alssc->random_access != 0 )
    {
        summary->samples_in_frame = (alssc->frame_length + 1) * alssc->random_access;
        summary->max_au_length    = summary->channels * (summary->sample_size / 8) * summary->samples_in_frame;
    }
    else
    {
        /* Read the remainder of overall stream as an access unit. */
        alssc->access_unit_size = lsmash_bs_get_remaining_buffer_size( bs );
        while( !bs->eof )
        {
            if( lsmash_bs_read( bs, bs->buffer.max_size ) < 0 )
                goto fail;
            alssc->access_unit_size = lsmash_bs_get_remaining_buffer_size( bs );
        }
        summary->max_au_length    = alssc->access_unit_size;
        summary->samples_in_frame = 0;      /* hack for mp4sys_als_importer_get_last_delta() */
    }
    uint32_t data_length;
    uint8_t *data = mp4a_export_AudioSpecificConfig( MP4A_AUDIO_OBJECT_TYPE_ALS,
                                                     summary->frequency, summary->channels, summary->sbr_mode,
                                                     alssc->sc_data, alssc->size, &data_length );
    if( !data )
        goto fail;
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG,
                                                                           LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !specific )
    {
        lsmash_free( data );
        goto fail;
    }
    lsmash_mp4sys_decoder_parameters_t *param = (lsmash_mp4sys_decoder_parameters_t *)specific->data.structured;
    param->objectTypeIndication = MP4SYS_OBJECT_TYPE_Audio_ISO_14496_3;
    param->streamType           = MP4SYS_STREAM_TYPE_AudioStream;
    if( lsmash_set_mp4sys_decoder_specific_info( param, data, data_length ) < 0 )
    {
        lsmash_destroy_codec_specific_data( specific );
        lsmash_free( data );
        goto fail;
    }
    lsmash_free( data );
    if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
    {
        lsmash_destroy_codec_specific_data( specific );
        goto fail;
    }
    return summary;
fail:
    lsmash_cleanup_summary( (lsmash_summary_t *)summary );
    return NULL;
}

static int mp4a_als_importer_probe( importer_t *importer )
{
    mp4a_als_importer_t *als_imp = create_mp4a_als_importer( importer );
    if( !als_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    /* Parse ALS specific configuration. */
    int err = als_parse_specific_config( importer->bs, als_imp );
    if( err < 0 )
        goto fail;
    lsmash_audio_summary_t *summary = als_create_summary( importer->bs, &als_imp->alssc );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    /* importer status */
    als_imp->samples_in_frame = summary->samples_in_frame;
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    importer->info   = als_imp;
    importer->status = IMPORTER_OK;
    return 0;
fail:
    remove_mp4a_als_importer( als_imp );
    return err;
}

static uint32_t mp4a_als_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    mp4a_als_importer_t *als_imp = (mp4a_als_importer_t *)importer->info;
    if( !als_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    als_specific_config_t *alssc = &als_imp->alssc;
    /* If alssc->number_of_ra_units == 0, then the last sample duration is just alssc->samples
     * since als_create_summary sets 0 to summary->samples_in_frame i.e. als_imp->samples_in_frame. */
    return alssc->samples - (alssc->number_of_ra_units - 1) * als_imp->samples_in_frame;
}

const importer_functions mp4a_als_importer =
{
    { "MPEG-4 ALS", offsetof( importer_t, log_level ) },
    1,
    mp4a_als_importer_probe,
    mp4a_als_importer_get_accessunit,
    mp4a_als_importer_get_last_delta,
    mp4a_als_importer_cleanup
};

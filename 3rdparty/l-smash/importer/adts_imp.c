/*****************************************************************************
 * adts_imp.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Takashi Hirata <silverfilain@gmail.com>
 * Contributors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
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

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/***************************************************************************
    ADTS importer
***************************************************************************/
#include "codecs/mp4a.h"

#define MP4SYS_ADTS_FIXED_HEADER_LENGTH 4 /* this is partly a lie. actually 28 bits. */
#define MP4SYS_ADTS_BASIC_HEADER_LENGTH 7
#define MP4SYS_ADTS_MAX_FRAME_LENGTH (( 1 << 13 ) - 1)
#define MP4SYS_ADTS_MAX_RAW_DATA_BLOCKS 4

typedef struct
{
    uint16_t syncword;                           /* 12; */
    uint8_t  ID;                                 /*  1; */
    uint8_t  layer;                              /*  2; */
    uint8_t  protection_absent;                  /*  1; */
    uint8_t  profile_ObjectType;                 /*  2; */
    uint8_t  sampling_frequency_index;           /*  4; */
//  uint8_t  private_bit;                        /*  1; we don't care. */
    uint8_t  channel_configuration;              /*  3; */
//  uint8_t  original_copy;                      /*  1; we don't care. */
//  uint8_t  home;                               /*  1; we don't care. */

} mp4sys_adts_fixed_header_t;

typedef struct
{
//  uint8_t  copyright_identification_bit;       /*  1; we don't care. */
//  uint8_t  copyright_identification_start;     /*  1; we don't care. */
    uint16_t frame_length;                       /* 13; */
//  uint16_t adts_buffer_fullness;               /* 11; we don't care. */
    uint8_t  number_of_raw_data_blocks_in_frame; /*  2; */
//  uint16_t adts_error_check;                                           /* we don't support */
//  uint16_t raw_data_block_position[MP4SYS_ADTS_MAX_RAW_DATA_BLOCKS-1]; /* we don't use this directly, and... */
    uint16_t raw_data_block_size[MP4SYS_ADTS_MAX_RAW_DATA_BLOCKS];       /* use this instead of above. */
//  uint16_t adts_header_error_check;                                    /* we don't support, actually crc_check within this */
//  uint16_t adts_raw_data_block_error_check[MP4SYS_ADTS_MAX_RAW_DATA_BLOCKS]; /* we don't support */
} mp4sys_adts_variable_header_t;

typedef struct
{
    unsigned int                  raw_data_block_idx;
    mp4sys_adts_fixed_header_t    header;
    mp4sys_adts_variable_header_t variable_header;
    uint32_t                      samples_in_frame;
    uint32_t                      au_number;
} mp4sys_adts_importer_t;

static void remove_mp4sys_adts_importer
(
    mp4sys_adts_importer_t *adts_imp
)
{
    lsmash_free( adts_imp );
}

static mp4sys_adts_importer_t *create_mp4sys_adts_importer
(
    importer_t *importer
)
{
    return (mp4sys_adts_importer_t *)lsmash_malloc_zero( sizeof(mp4sys_adts_importer_t) );
}

static void mp4sys_adts_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_mp4sys_adts_importer( importer->info );
}

static void mp4sys_adts_parse_fixed_header
(
    uint8_t                    *buf,
    mp4sys_adts_fixed_header_t *header
)
{
    /* FIXME: should we rewrite these code using bitstream reader? */
    header->syncword                 = (buf[0] << 4) | (buf[1] >> 4);
    header->ID                       = (buf[1] >> 3) & 0x1;
    header->layer                    = (buf[1] >> 1) & 0x3;
    header->protection_absent        = buf[1] & 0x1;
    header->profile_ObjectType       = buf[2] >> 6;
    header->sampling_frequency_index = (buf[2] >> 2) & 0xF;
//  header->private_bit              = (buf[2] >> 1) & 0x1; /* we don't care currently. */
    header->channel_configuration    = ((buf[2] << 2) | (buf[3] >> 6)) & 0x07;
//  header->original_copy            = (buf[3] >> 5) & 0x1; /* we don't care currently. */
//  header->home                     = (buf[3] >> 4) & 0x1; /* we don't care currently. */
}

static int mp4sys_adts_check_fixed_header
(
    mp4sys_adts_fixed_header_t *header
)
{
    if( header->syncword != 0xFFF )              return LSMASH_ERR_INVALID_DATA;
//  if( header->ID != 0x0 )                      return LSMASH_ERR_NAMELESS;        /* we don't care. */
    if( header->layer != 0x0 )                   return LSMASH_ERR_INVALID_DATA;    /* must be 0b00 for any type of AAC */
//  if( header->protection_absent != 0x1 )       return LSMASH_ERR_NAMELESS;        /* we don't care. */
    if( header->profile_ObjectType != 0x1 )      return LSMASH_ERR_PATCH_WELCOME;   /* FIXME: 0b00=Main, 0b01=LC, 0b10=SSR, 0b11=LTP. */
    if( header->sampling_frequency_index > 0xB ) return LSMASH_ERR_INVALID_DATA;    /* must not be > 0xB. */
    if( header->channel_configuration == 0x0 )   return LSMASH_ERR_PATCH_WELCOME;   /* FIXME: we do not support 0b000 currently. */
    if( header->profile_ObjectType == 0x3 && header->ID != 0x0 ) return LSMASH_ERR_INVALID_DATA; /* LTP is valid only if ID==0. */
    return 0;
}

static int mp4sys_adts_parse_variable_header
(
    lsmash_bs_t                   *bs,
    uint8_t                       *buf,
    unsigned int                   protection_absent,
    mp4sys_adts_variable_header_t *header
)
{
    /* FIXME: should we rewrite these code using bitstream reader? */
//  header->copyright_identification_bit       = (buf[3] >> 3) & 0x1; /* we don't care. */
//  header->copyright_identification_start     = (buf[3] >> 2) & 0x1; /* we don't care. */
    header->frame_length                       = ((buf[3] << 11) | (buf[4] << 3) | (buf[5] >> 5)) & 0x1FFF ;
//  header->adts_buffer_fullness               = ((buf[5] << 6) | (buf[6] >> 2)) 0x7FF ;  /* we don't care. */
    header->number_of_raw_data_blocks_in_frame = buf[6] & 0x3;

    if( header->frame_length <= MP4SYS_ADTS_BASIC_HEADER_LENGTH + 2 * (protection_absent == 0) )
        return LSMASH_ERR_INVALID_DATA; /* easy error check */

    /* protection_absent and number_of_raw_data_blocks_in_frame relatives */

    uint8_t buf2[2];
    unsigned int number_of_blocks = header->number_of_raw_data_blocks_in_frame;
    if( number_of_blocks == 0 )
    {
        header->raw_data_block_size[0] = header->frame_length - MP4SYS_ADTS_BASIC_HEADER_LENGTH;
        /* skip adts_error_check() and subtract that from block_size */
        if( protection_absent == 0 )
        {
            header->raw_data_block_size[0] -= 2;
            if( lsmash_bs_get_bytes_ex( bs, 2, buf2 ) != 2 )
                return LSMASH_ERR_INVALID_DATA;
        }
        return 0;
    }

    /* now we have multiple raw_data_block()s, so evaluate adts_header_error_check() */

    uint16_t raw_data_block_position[MP4SYS_ADTS_MAX_RAW_DATA_BLOCKS];
    uint16_t first_offset = MP4SYS_ADTS_BASIC_HEADER_LENGTH;
    if( protection_absent == 0 )
    {
        /* process adts_header_error_check() */
        for( int i = 0 ; i < number_of_blocks ; i++ ) /* 1-based in the spec, but we use 0-based */
        {
            if( lsmash_bs_get_bytes_ex( bs, 2, buf2 ) != 2 )
                return LSMASH_ERR_INVALID_DATA;
            raw_data_block_position[i] = LSMASH_GET_BE16( buf2 );
        }
        /* skip crc_check in adts_header_error_check().
           Or might be sizeof( adts_error_check() ) if we share with the case number_of_raw_data_blocks_in_frame == 0 */
        if( lsmash_bs_get_bytes_ex( bs, 2, buf2 ) != 2 )
            return LSMASH_ERR_INVALID_DATA;
        first_offset += ( 2 * number_of_blocks ) + 2; /* according to above */
    }
    else
    {
        /*
         * NOTE: We never support the case where number_of_raw_data_blocks_in_frame != 0 && protection_absent != 0,
         * because we have to parse the raw AAC bitstream itself to find boundaries of raw_data_block()s in this case.
         * Which is to say, that braindamaged spec requires us (mp4 muxer) to decode AAC once to split frames.
         * L-SMASH is NOT AAC DECODER, so that we've just given up for this case.
         * This is ISO/IEC 13818-7's sin which defines ADTS format originally.
         */
        return LSMASH_ERR_NAMELESS;
    }

    /* convert raw_data_block_position --> raw_data_block_size */

    /* do conversion for first */
    header->raw_data_block_size[0] = raw_data_block_position[0] - first_offset;
    /* set dummy offset to tail for loop, do coversion for rest. */
    raw_data_block_position[number_of_blocks] = header->frame_length;
    for( int i = 1 ; i <= number_of_blocks ; i++ )
        header->raw_data_block_size[i] = raw_data_block_position[i] - raw_data_block_position[i-1];

    /* adjustment for adts_raw_data_block_error_check() */
    if( protection_absent == 0 && number_of_blocks != 0 )
        for( int i = 0 ; i <= number_of_blocks ; i++ )
            header->raw_data_block_size[i] -= 2;

    return 0;
}

static int mp4sys_adts_parse_headers
(
    lsmash_bs_t                   *bs,
    uint8_t                       *buf,
    mp4sys_adts_fixed_header_t    *header,
    mp4sys_adts_variable_header_t *variable_header
)
{
    mp4sys_adts_parse_fixed_header( buf, header );
    int err = mp4sys_adts_check_fixed_header( header );
    if( err < 0 )
        return err;
    /* get payload length & skip extra(crc) header */
    return mp4sys_adts_parse_variable_header( bs, buf, header->protection_absent, variable_header );
}

static lsmash_audio_summary_t *mp4sys_adts_create_summary
(
    mp4sys_adts_fixed_header_t *header
)
{
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    summary->sample_type            = ISOM_CODEC_TYPE_MP4A_AUDIO;
    summary->max_au_length          = MP4SYS_ADTS_MAX_FRAME_LENGTH;
    summary->frequency              = mp4a_sampling_frequency_table[header->sampling_frequency_index][1];
    summary->channels               = header->channel_configuration + ( header->channel_configuration == 0x07 ); /* 0x07 means 7.1ch */
    summary->sample_size            = 16;
    summary->samples_in_frame       = 1024;
    summary->aot                    = header->profile_ObjectType + MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN;
    summary->sbr_mode               = MP4A_AAC_SBR_NOT_SPECIFIED;
#if 0 /* FIXME: This is very unstable. Many players crash with this. */
    if( header->ID != 0 )
    {
        /*
         * NOTE: This ADTS seems of ISO/IEC 13818-7 (MPEG-2 AAC).
         * It has special object_type_indications, depending on it's profile (Legacy Interface).
         * If ADIF header is not available, it should not have decoder specific information, so AudioObjectType neither.
         * see ISO/IEC 14496-1, DecoderSpecificInfo and 14496-3 Subpart 9: MPEG-1/2 Audio in MPEG-4.
         */
        summary->object_type_indication = header->profile_ObjectType + MP4SYS_OBJECT_TYPE_Audio_ISO_13818_7_Main_Profile;
        summary->aot                    = MP4A_AUDIO_OBJECT_TYPE_NULL;
        summary->asc                    = NULL;
        summary->asc_length             = 0;
        // summary->sbr_mode            = MP4A_AAC_SBR_NONE; /* MPEG-2 AAC should not be HE-AAC, but we forgive them. */
        return summary;
    }
#endif
    uint32_t data_length;
    uint8_t *data = mp4a_export_AudioSpecificConfig( header->profile_ObjectType + MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN,
                                                     summary->frequency, summary->channels, summary->sbr_mode,
                                                     NULL, 0, &data_length );
    if( !data )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        return NULL;
    }
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG,
                                                                           LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !specific )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_free( data );
        return NULL;
    }
    lsmash_mp4sys_decoder_parameters_t *param = (lsmash_mp4sys_decoder_parameters_t *)specific->data.structured;
    param->objectTypeIndication = MP4SYS_OBJECT_TYPE_Audio_ISO_14496_3;
    param->streamType           = MP4SYS_STREAM_TYPE_AudioStream;
    if( lsmash_set_mp4sys_decoder_specific_info( param, data, data_length ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( specific );
        lsmash_free( data );
        return NULL;
    }
    lsmash_free( data );
    if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        lsmash_destroy_codec_specific_data( specific );
        return NULL;
    }
    return summary;
}

static int mp4sys_adts_get_accessunit
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
    mp4sys_adts_importer_t *adts_imp = (mp4sys_adts_importer_t *)importer->info;
    importer_status current_status = importer->status;
    uint16_t raw_data_block_size = adts_imp->variable_header.raw_data_block_size[ adts_imp->raw_data_block_idx ];
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    if( current_status == IMPORTER_CHANGE )
    {
        lsmash_entry_t *entry = lsmash_list_get_entry( importer->summaries, track_number );
        if( !entry || !entry->data )
            return LSMASH_ERR_NAMELESS;
        lsmash_audio_summary_t *summary = mp4sys_adts_create_summary( &adts_imp->header );
        if( !summary )
            return LSMASH_ERR_NAMELESS;
        lsmash_cleanup_summary( entry->data );
        entry->data = summary;
        adts_imp->samples_in_frame = summary->samples_in_frame;
    }
    lsmash_bs_t *bs = importer->bs;
    /* read a raw_data_block(), typically == payload of a ADTS frame */
    lsmash_sample_t *sample = lsmash_create_sample( raw_data_block_size );
    if( !sample )
        return LSMASH_ERR_MEMORY_ALLOC;
    *p_sample = sample;
    if( lsmash_bs_get_bytes_ex( bs, raw_data_block_size, sample->data ) != raw_data_block_size )
    {
        importer->status = IMPORTER_ERROR;
        return LSMASH_ERR_INVALID_DATA;
    }
    sample->length                 = raw_data_block_size;
    sample->dts                    = adts_imp->au_number ++ * adts_imp->samples_in_frame;
    sample->cts                    = sample->dts;
    sample->prop.ra_flags          = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
    sample->prop.pre_roll.distance = 1; /* MDCT */

    /* now we succeeded to read current frame, so "return" takes 0 always below. */

    /* skip adts_raw_data_block_error_check() */
    if( adts_imp->header.protection_absent == 0
     && adts_imp->variable_header.number_of_raw_data_blocks_in_frame != 0
     && lsmash_bs_get_bytes_ex( bs, 2, sample->data ) != 2 )
    {
        importer->status = IMPORTER_ERROR;
        return 0;
    }
    /* current adts_frame() has any more raw_data_block()? */
    if( adts_imp->raw_data_block_idx < adts_imp->variable_header.number_of_raw_data_blocks_in_frame )
    {
        adts_imp->raw_data_block_idx++;
        importer->status = IMPORTER_OK;
        return 0;
    }
    adts_imp->raw_data_block_idx = 0;

    /* preparation for next frame */

    uint8_t buf[MP4SYS_ADTS_MAX_FRAME_LENGTH];
    int64_t ret = lsmash_bs_get_bytes_ex( bs, MP4SYS_ADTS_BASIC_HEADER_LENGTH, buf );
    if( ret == 0 )
    {
        importer->status = IMPORTER_EOF;
        return 0;
    }
    if( ret != MP4SYS_ADTS_BASIC_HEADER_LENGTH )
    {
        importer->status = IMPORTER_ERROR;
        return 0;
    }
    /*
     * NOTE: About the spec of ADTS headers.
     * By the spec definition, ADTS's fixed header cannot change in the middle of stream.
     * But spec of MP4 allows that a stream(track) changes its properties in the middle of it.
     */
    /*
     * NOTE: About detailed check for ADTS headers.
     * We do not ommit detailed check for fixed header by simply testing bits' identification,
     * because there're some flags which does not matter to audio_summary (so AudioSpecificConfig neither)
     * so that we can take them as no change and never make new ObjectDescriptor.
     * I know that can be done with/by bitmask also and that should be fast, but L-SMASH project prefers
     * even foolishly straightforward way.
     */
    /*
     * NOTE: About our reading algorithm for ADTS.
     * It's rather simple if we retrieve payload of ADTS (i.e. raw AAC frame) at the same time to
     * retrieve headers.
     * But then we have to cache and memcpy every frame so that it requires more clocks and memory.
     * To avoid them, I adopted this separate retrieving method.
     */
    mp4sys_adts_fixed_header_t header = { 0 };
    mp4sys_adts_variable_header_t variable_header = { 0 };
    if( mp4sys_adts_parse_headers( bs, buf, &header, &variable_header ) < 0 )
    {
        importer->status = IMPORTER_ERROR;
        return 0;
    }
    adts_imp->variable_header = variable_header;
    /*
     * NOTE: About our support for change(s) of properties within an ADTS stream.
     * We have to modify these conditions depending on the features we support.
     * For example, if we support copyright_identification_* in any way within any feature
     * defined by/in any specs, such as ISO/IEC 14496-1 (MPEG-4 Systems), like...
     * "8.3 Intellectual Property Management and Protection (IPMP)", or something similar,
     * we have to check copyright_identification_* and treat them in audio_summary.
     * "Change(s)" may result in MP4SYS_IMPORTER_ERROR or MP4SYS_IMPORTER_CHANGE
     * depending on the features we support, and what the spec allows.
     * Sometimes the "change(s)" can be allowed, while sometimes they're forbidden.
     */
    /* currently UNsupported "change(s)". */
    if( adts_imp->header.profile_ObjectType != header.profile_ObjectType /* currently unsupported. */
     || adts_imp->header.ID != header.ID /* In strict, this means change of object_type_indication. */
     || adts_imp->header.sampling_frequency_index != header.sampling_frequency_index ) /* This may change timebase. */
    {
        importer->status = IMPORTER_ERROR;
        return 0;
    }
    /* currently supported "change(s)". */
    if( adts_imp->header.channel_configuration != header.channel_configuration )
    {
        /*
         * FIXME: About conditions of VALID "change(s)".
         * we have to check whether any "change(s)" affect to audioProfileLevelIndication
         * in InitialObjectDescriptor (MP4_IOD) or not.
         * If another type or upper level is required by the change(s), that is forbidden.
         * Because ObjectDescriptor does not have audioProfileLevelIndication,
         * so that it seems impossible to change audioProfileLevelIndication in the middle of the stream.
         * Note also any other properties, such as AudioObjectType, object_type_indication.
         */
        /*
         * NOTE: updating summary must be done on next call,
         * because user may retrieve summary right after this function call of this time,
         * and that should be of current, before change, one.
         */
        adts_imp->header = header;
        importer->status = IMPORTER_CHANGE;
        return 0;
    }
    /* no change which matters to mp4 muxing was found */
    importer->status = IMPORTER_OK;
    return 0;
}

/* returns 0 if it seems adts. */
static int mp4sys_adts_probe
(
    importer_t *importer
)
{
    mp4sys_adts_importer_t *adts_imp = create_mp4sys_adts_importer( importer );
    if( !adts_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err;
    uint8_t buf[MP4SYS_ADTS_MAX_FRAME_LENGTH];
    if( lsmash_bs_get_bytes_ex( importer->bs, MP4SYS_ADTS_BASIC_HEADER_LENGTH, buf ) != MP4SYS_ADTS_BASIC_HEADER_LENGTH )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    mp4sys_adts_fixed_header_t    header          = { 0 };
    mp4sys_adts_variable_header_t variable_header = { 0 };
    if( (err = mp4sys_adts_parse_headers( importer->bs, buf, &header, &variable_header )) < 0 )
        goto fail;
    /* now the stream seems valid ADTS */
    lsmash_audio_summary_t *summary = mp4sys_adts_create_summary( &header );
    if( !summary )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    /* importer status */
    if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
    {
        lsmash_cleanup_summary( (lsmash_summary_t *)summary );
        err = LSMASH_ERR_MEMORY_ALLOC;
        goto fail;
    }
    adts_imp->raw_data_block_idx = 0;
    adts_imp->header             = header;
    adts_imp->variable_header    = variable_header;
    adts_imp->samples_in_frame   = summary->samples_in_frame;
    importer->info   = adts_imp;
    importer->status = IMPORTER_OK;
    return 0;
fail:
    remove_mp4sys_adts_importer( adts_imp );
    return err;
}

static uint32_t mp4sys_adts_get_last_delta
(
    importer_t *importer,
    uint32_t    track_number
)
{
    debug_if( !importer || !importer->info )
        return 0;
    mp4sys_adts_importer_t *adts_imp = (mp4sys_adts_importer_t *)importer->info;
    if( !adts_imp || track_number != 1 || importer->status != IMPORTER_EOF )
        return 0;
    return adts_imp->samples_in_frame;
}

const importer_functions mp4sys_adts_importer =
{
    { "adts" },
    1,
    mp4sys_adts_probe,
    mp4sys_adts_get_accessunit,
    mp4sys_adts_get_last_delta,
    mp4sys_adts_cleanup
};

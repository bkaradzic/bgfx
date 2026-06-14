/*****************************************************************************
 * mp4a.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Takashi Hirata <silverfilain@gmail.com>
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

#define MP4A_INTERNAL
#include "core/box.h"

#include "mp4a.h"
#include "mp4sys.h"
#include "description.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/***************************************************************************
    implementation of part of ISO/IEC 14496-3 (ISO/IEC 14496-1 relevant)
***************************************************************************/

/* ISO/IEC 14496-3 samplingFrequencyIndex */
/* ISO/IEC 14496-3 Sampling frequency mapping */
const uint32_t mp4a_sampling_frequency_table[13][5] = {
    /* threshold, exact, idx_for_ga, idx_for_sbr, idx */
    {      92017, 96000,        0x0,         0xF, 0x0 }, /* SBR is not allowed */
    {      75132, 88200,        0x1,         0xF, 0x1 }, /* SBR is not allowed */
    {      55426, 64000,        0x2,         0xF, 0x2 }, /* SBR is not allowed */
    {      46009, 48000,        0x3,         0x0, 0x3 },
    {      37566, 44100,        0x4,         0x1, 0x4 },
    {      27713, 32000,        0x5,         0x2, 0x5 },
    {      23004, 24000,        0x6,         0x3, 0x6 },
    {      18783, 22050,        0x7,         0x4, 0x7 },
    {      13856, 16000,        0x8,         0x5, 0x8 },
    {      11502, 12000,        0x9,         0x6, 0x9 },
    {       9391, 11025,        0xA,         0x7, 0xA },
    {       8000,  8000,        0xB,         0x8, 0xB },
    {          0,  7350,        0xB,         0xF, 0xC } /* samplingFrequencyIndex for GASpecificConfig is 0xB (same as 8000Hz). */
};

/* ISO/IEC 14496-3 Interface to ISO/IEC 14496-1 (MPEG-4 Systems), Syntax of AudioSpecificConfig(). */
/* This structure is represent of regularized AudioSpecificConfig. */
/* for actual definition, see Syntax of GetAudioObjectType() for audioObjectType and extensionAudioObjectType. */
typedef struct
{
    lsmash_mp4a_aac_sbr_mode sbr_mode; /* L-SMASH's original, including sbrPresent flag. */
    lsmash_mp4a_AudioObjectType audioObjectType;
    unsigned samplingFrequencyIndex : 4;
    unsigned samplingFrequency      : 24;
    unsigned channelConfiguration   : 4;
    lsmash_mp4a_AudioObjectType extensionAudioObjectType;
    unsigned extensionSamplingFrequencyIndex : 4;
    unsigned extensionSamplingFrequency      : 24;
    unsigned extensionChannelConfiguration   : 4;
    /* if( audioObjectType in
        #[ 1, 2, 3, 4, 6, 7, *17, *19, *20, *21, *22, *23 ] // GASpecificConfig, AAC relatives and TwinVQ, BSAC
        [ 8 ]              // CelpSpecificConfig, not supported
        [ 9 ]              // HvxcSpecificConfig, not supported
        [ 12 ]             // TTSSpecificConfig, not supported
        [ 13, 14, 15, 16 ] // StructuredAudioSpecificConfig, notsupported
        [ 24 ]             // ErrorResilientCelpSpecificConfig, notsupported
        [ 25 ]             // ErrorResilientHvxcSpecificConfig, notsupported
        [ 26, 27 ]         // ParametricSpecificConfig, notsupported
        [ 28 ]             // SSCSpecificConfig, notsupported
        #[ 32, 33, 34 ]     // MPEG_1_2_SpecificConfig
        [ 35 ]             // DSTSpecificConfig, notsupported
    ){ */
        void *deepAudioSpecificConfig; // L-SMASH's original name, reperesents such as GASpecificConfig. */
    /* } */
    /*
    // error resilient stuff, not supported
    if( audioObjectType in [17, 19, 20, 21, 22, 23, 24, 25, 26, 27] ){
        uint8_t epConfig // 2bit
        if( epConfig == 2 || epConfig == 3 ){
            ErrorProtectionSpecificConfig();
        }
        if( epConfig == 3 ){
            uint8_t directMapping;  // 1bit, currently always 1.
            if( !directMapping ){
                // tbd
            }
        }
    }
    */
} mp4a_AudioSpecificConfig_t;

/* ISO/IEC 14496-3 Decoder configuration (GASpecificConfig), Syntax of GASpecificConfig() */
/* ISO/IEC 14496-3 GASpecificConfig(), Sampling frequency mapping */
typedef struct
{
    unsigned frameLengthFlag    : 1; /* FIXME: AAC_SSR: shall be 0, Others: depends, but noramally 0. */
    unsigned dependsOnCoreCoder : 1; /* FIXME: used if scalable AAC. */
    unsigned coreCoderDelay     : 14;
    unsigned extensionFlag      : 1; /* 1bit, 1 if ErrorResilience */
    /* if( !channelConfiguration ){ */
        void* program_config_element;  /* currently not supported. */
    /* } */
    /*
    // we do not support AAC_scalable
    if( (audioObjectType == MP4A_AUDIO_OBJECT_TYPE_AAC_scalable) || (audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable) ){
        uint8_t layerNr; // 3bits
    }
    */
    /*
    // we do not support special AACs
    if( extensionFlag ){
        if( audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_BSAC ){
            uint8_t numOfSubFrame; // 5bits
            uint8_t layer_length;  // 11bits
        }
        if( audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC || audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP
            || audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable || audioObjectType == MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD
        ){
            uint8_t aacSectionDataResilienceFlag; // 1bit
            uint8_t aacScalefactorDataResilienceFlag; // 1bit
            uint8_t aacSpectralDataResilienceFlag; // 1bit
        }
        uint8_t extensionFlag3; // 1bit
        if( extensionFlag3 ){
            // tbd in version 3
        }
    }
    */
} mp4a_GASpecificConfig_t;

/* ISO/IEC 14496-3 MPEG_1_2_SpecificConfig */
typedef struct
{
    uint8_t extension; /* shall be 0. */
} mp4a_MPEG_1_2_SpecificConfig_t;

/* ISO/IEC 14496-3 ALSSpecificConfig */
typedef struct
{
    uint32_t size;
    uint8_t *data;
    uint32_t als_id;
    uint32_t samp_freq;
    uint32_t samples;
    uint16_t channels;
    unsigned file_type            : 3;
    unsigned resolution           : 3;
    unsigned floating             : 1;
    unsigned msb_first            : 1;
    uint16_t frame_length;
    uint8_t  random_access;
    unsigned ra_flag              : 2;
    unsigned adapt_order          : 1;
    unsigned coef_table           : 2;
    unsigned long_term_prediction : 1;
    unsigned max_order            : 10;
    unsigned block_switching      : 2;
    unsigned bgmc_mode            : 1;
    unsigned sb_part              : 1;
    unsigned joint_stereo         : 1;
    unsigned mc_coding            : 1;
    unsigned chan_config          : 1;
    unsigned chan_sort            : 1;
    unsigned crc_enabled          : 1;
    unsigned RLSLMS               : 1;
    unsigned reserved             : 5;
    unsigned aux_data_enabled     : 1;
} mp4a_ALSSpecificConfig_t;

static inline void mp4a_remove_GASpecificConfig( mp4a_GASpecificConfig_t* gasc )
{
    debug_if( !gasc )
        return;
    lsmash_free( gasc->program_config_element );
    lsmash_free( gasc );
}

static inline void mp4a_remove_MPEG_1_2_SpecificConfig( mp4a_MPEG_1_2_SpecificConfig_t* mpeg_1_2_sc )
{
    lsmash_free( mpeg_1_2_sc );
}

void mp4a_remove_AudioSpecificConfig( mp4a_AudioSpecificConfig_t* asc )
{
    if( !asc )
        return;
    switch( asc->audioObjectType ){
    case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_SBR:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_TwinVQ:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ:
    case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD:
        mp4a_remove_GASpecificConfig( (mp4a_GASpecificConfig_t*)asc->deepAudioSpecificConfig );
        break;
    case MP4A_AUDIO_OBJECT_TYPE_Layer_1:
    case MP4A_AUDIO_OBJECT_TYPE_Layer_2:
    case MP4A_AUDIO_OBJECT_TYPE_Layer_3:
        mp4a_remove_MPEG_1_2_SpecificConfig( (mp4a_MPEG_1_2_SpecificConfig_t*)asc->deepAudioSpecificConfig );
        break;
    default:
        lsmash_free( asc->deepAudioSpecificConfig );
        break;
    }
    lsmash_free( asc );
}

/* ADIF/PCE(program config element) style GASpecificConfig is not not supported. */
/* channelConfig/samplingFrequencyIndex will be used when we support ADIF/PCE style GASpecificConfig. */
static mp4a_GASpecificConfig_t* mp4a_create_GASpecificConfig( uint8_t samplingFrequencyIndex, uint8_t channelConfig, lsmash_mp4a_AudioObjectType aot )
{
    debug_if( aot != MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_LC
        && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_SSR && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_LTP
        && aot != MP4A_AUDIO_OBJECT_TYPE_TwinVQ )
        return NULL;
    if( samplingFrequencyIndex > 0xB || channelConfig == 0 || channelConfig == 7 )
        return NULL;
    mp4a_GASpecificConfig_t *gasc = (mp4a_GASpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_GASpecificConfig_t) );
    if( !gasc )
        return NULL;
    gasc->frameLengthFlag = 0; /* FIXME: AAC_SSR: shall be 0, Others: depends, but noramally 0. */
    gasc->dependsOnCoreCoder = 0; /* FIXME: used if scalable AAC. */
    switch( aot ){
    case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_TwinVQ:
        gasc->extensionFlag = 0;
        break;
#if 0 /* intentional dead code */
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ:
    case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD:
        gasc->extensionFlag = 1;
        break;
#endif
    default:
        gasc->extensionFlag = 0;
        break;
    }
    return gasc;
}

static mp4a_MPEG_1_2_SpecificConfig_t* mp4a_create_MPEG_1_2_SpecificConfig()
{
    mp4a_MPEG_1_2_SpecificConfig_t *mpeg_1_2_sc = (mp4a_MPEG_1_2_SpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_MPEG_1_2_SpecificConfig_t) );
    if( !mpeg_1_2_sc )
        return NULL;
    mpeg_1_2_sc->extension = 0; /* shall be 0. */
    return mpeg_1_2_sc;
}

static mp4a_ALSSpecificConfig_t *mp4a_create_ALSSpecificConfig( uint8_t *exdata, uint32_t exdata_length )
{
    mp4a_ALSSpecificConfig_t *alssc = (mp4a_ALSSpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_ALSSpecificConfig_t) );
    if( !alssc )
        return NULL;
    alssc->data = lsmash_memdup( exdata, exdata_length );
    if( !alssc->data )
    {
        lsmash_free( alssc );
        return NULL;
    }
    alssc->size = exdata_length;
    return alssc;
}

/* Currently, only normal AAC, MPEG_1_2 are supported.
   For AAC, other than normal AAC, such as AAC_scalable, ER_AAC_xxx, are not supported.
   ADIF/PCE(program config element) style AudioSpecificConfig is not supported.
   aot shall not be MP4A_AUDIO_OBJECT_TYPE_SBR even if you wish to signal SBR explicitly, use sbr_mode instead.
   Frequency/channels shall be base AAC's one, even if SBR/PS.
   If other than AAC with SBR, sbr_mode shall be MP4A_AAC_SBR_NOT_SPECIFIED. */
mp4a_AudioSpecificConfig_t *mp4a_create_AudioSpecificConfig(
    lsmash_mp4a_AudioObjectType aot,
    uint32_t frequency,
    uint32_t channels,
    lsmash_mp4a_aac_sbr_mode sbr_mode,
    uint8_t *exdata,
    uint32_t exdata_length
)
{
    if( aot != MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_LC
     && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_SSR && aot != MP4A_AUDIO_OBJECT_TYPE_AAC_LTP
     && aot != MP4A_AUDIO_OBJECT_TYPE_TwinVQ && aot != MP4A_AUDIO_OBJECT_TYPE_Layer_1
     && aot != MP4A_AUDIO_OBJECT_TYPE_Layer_2 && aot != MP4A_AUDIO_OBJECT_TYPE_Layer_3
     && aot != MP4A_AUDIO_OBJECT_TYPE_ALS )
        return NULL;
    if( frequency == 0 )
        return NULL;

    uint8_t channelConfig;
    switch( channels ){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            channelConfig = channels;
            break;
        case 8:
            channelConfig = 7;
            break;
        default:
            return NULL;
    }

    mp4a_AudioSpecificConfig_t *asc = (mp4a_AudioSpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_AudioSpecificConfig_t) );
    if( !asc )
        return NULL;

    asc->sbr_mode = sbr_mode;
    asc->audioObjectType = aot;
    asc->channelConfiguration = channelConfig;

    uint8_t samplingFrequencyIndex = 0xF;
    uint8_t i = 0x0;
    if( sbr_mode != MP4A_AAC_SBR_NOT_SPECIFIED
     || aot == MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN
     || aot == MP4A_AUDIO_OBJECT_TYPE_AAC_LC
     || aot == MP4A_AUDIO_OBJECT_TYPE_AAC_SSR
     || aot == MP4A_AUDIO_OBJECT_TYPE_AAC_LTP
     || aot == MP4A_AUDIO_OBJECT_TYPE_SBR )
    {
        while( frequency < mp4a_sampling_frequency_table[i][0] )
            i++;
        asc->samplingFrequencyIndex = frequency == mp4a_sampling_frequency_table[i][1] ? i : 0xF;
        asc->samplingFrequency = frequency;
        samplingFrequencyIndex = mp4a_sampling_frequency_table[i][2];
        /* SBR settings */
        if( sbr_mode != MP4A_AAC_SBR_NOT_SPECIFIED )
        {
            /* SBR limitation */
            /* see ISO/IEC 14496-3 Levels within the profiles / Levels for the High Efficiency AAC Profile */
            if( i < 0x3 )
            {
                lsmash_free( asc );
                return NULL;
            }
            asc->extensionAudioObjectType = MP4A_AUDIO_OBJECT_TYPE_SBR;
        }
        else
            asc->extensionAudioObjectType = MP4A_AUDIO_OBJECT_TYPE_NULL;

        if( sbr_mode == MP4A_AAC_SBR_BACKWARD_COMPATIBLE || sbr_mode == MP4A_AAC_SBR_HIERARCHICAL )
        {
            asc->extensionSamplingFrequency = frequency * 2;
            asc->extensionSamplingFrequencyIndex = i == 0xC ? 0xF : mp4a_sampling_frequency_table[i][3];
        }
        else
        {
            asc->extensionSamplingFrequencyIndex = asc->samplingFrequencyIndex;
            asc->extensionSamplingFrequency = asc->samplingFrequency;
        }
    }
    else
    {
        while( i < 0xD && frequency != mp4a_sampling_frequency_table[i][1] )
            i++;
        asc->samplingFrequencyIndex          = i != 0xD ? i : 0xF;
        asc->samplingFrequency               = frequency;
        asc->extensionAudioObjectType        = MP4A_AUDIO_OBJECT_TYPE_NULL;
        asc->extensionSamplingFrequencyIndex = asc->samplingFrequencyIndex;
        asc->extensionSamplingFrequency      = asc->samplingFrequency;
    }

    switch( aot )
    {
        case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN:
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LC:
        case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR:
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP:
        case MP4A_AUDIO_OBJECT_TYPE_SBR:
#if 0 /* FIXME: here, stop currently unsupported codecs. */
        case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable:
        case MP4A_AUDIO_OBJECT_TYPE_TwinVQ: /* NOTE: I think we already have a support for TwinVQ, but how to test this? */
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC:
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP:
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable:
        case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ:
        case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC:
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD:
#endif
            asc->deepAudioSpecificConfig = mp4a_create_GASpecificConfig( samplingFrequencyIndex, channelConfig, aot );
            break;
        case MP4A_AUDIO_OBJECT_TYPE_Layer_1:
        case MP4A_AUDIO_OBJECT_TYPE_Layer_2:
        case MP4A_AUDIO_OBJECT_TYPE_Layer_3:
            asc->deepAudioSpecificConfig = mp4a_create_MPEG_1_2_SpecificConfig();
            break;
        case MP4A_AUDIO_OBJECT_TYPE_ALS:
            asc->deepAudioSpecificConfig = mp4a_create_ALSSpecificConfig( exdata, exdata_length );
            break;
        default:
            break; /* this case is trapped below. */
    }
    if( !asc->deepAudioSpecificConfig )
    {
        lsmash_free( asc );
        return NULL;
    }
    return asc;
}

/* ADIF/PCE(program config element) style GASpecificConfig is not supported. */
static void mp4a_put_GASpecificConfig( lsmash_bits_t* bits, mp4a_GASpecificConfig_t* gasc )
{
    debug_if( !bits || !gasc )
        return;
    lsmash_bits_put( bits, 1, gasc->frameLengthFlag );
    lsmash_bits_put( bits, 1, gasc->dependsOnCoreCoder );
    lsmash_bits_put( bits, 1, gasc->extensionFlag );
}

static void mp4a_put_MPEG_1_2_SpecificConfig( lsmash_bits_t* bits, mp4a_MPEG_1_2_SpecificConfig_t* mpeg_1_2_sc )
{
    debug_if( !bits || !mpeg_1_2_sc )
        return;
    lsmash_bits_put( bits, 1, mpeg_1_2_sc->extension ); /* shall be 0 */
}

static void mp4a_put_ALSSpecificConfig( lsmash_bits_t *bits, mp4a_ALSSpecificConfig_t *alssc )
{
    debug_if( !bits || !alssc )
        return;
    lsmash_bits_import_data( bits, alssc->data, alssc->size );
}

static inline void mp4a_put_AudioObjectType( lsmash_bits_t* bits, lsmash_mp4a_AudioObjectType aot )
{
    if( aot > MP4A_AUDIO_OBJECT_TYPE_ESCAPE )
    {
        lsmash_bits_put( bits, 5, MP4A_AUDIO_OBJECT_TYPE_ESCAPE );
        lsmash_bits_put( bits, 6, aot - MP4A_AUDIO_OBJECT_TYPE_ESCAPE - 1 );
    }
    else
        lsmash_bits_put( bits, 5, aot );
}

static inline void mp4a_put_SamplingFrequencyIndex( lsmash_bits_t* bits, uint8_t samplingFrequencyIndex, uint32_t samplingFrequency )
{
    lsmash_bits_put( bits, 4, samplingFrequencyIndex );
    if( samplingFrequencyIndex == 0xF )
        lsmash_bits_put( bits, 24, samplingFrequency );
}

/* Currently, only normal AAC, MPEG_1_2 are supported.
   For AAC, other than normal AAC, such as AAC_scalable, ER_AAC_xxx, are not supported.
   ADIF/PCE(program config element) style AudioSpecificConfig is not supported either. */
void mp4a_put_AudioSpecificConfig( lsmash_bs_t* bs, mp4a_AudioSpecificConfig_t* asc )
{
    debug_if( !bs || !asc )
        return;
    lsmash_bits_t bits;
    lsmash_bits_init( &bits, bs );

    if( asc->sbr_mode == MP4A_AAC_SBR_HIERARCHICAL )
        mp4a_put_AudioObjectType( &bits, asc->extensionAudioObjectType ); /* puts MP4A_AUDIO_OBJECT_TYPE_SBR */
    else
        mp4a_put_AudioObjectType( &bits, asc->audioObjectType );
    mp4a_put_SamplingFrequencyIndex( &bits, asc->samplingFrequencyIndex, asc->samplingFrequency );
    lsmash_bits_put( &bits, 4, asc->channelConfiguration );
    if( asc->sbr_mode == MP4A_AAC_SBR_HIERARCHICAL )
    {
        mp4a_put_SamplingFrequencyIndex( &bits, asc->extensionSamplingFrequencyIndex, asc->extensionSamplingFrequency );
        mp4a_put_AudioObjectType( &bits, asc->audioObjectType );
    }
    switch( asc->audioObjectType ){
    case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR:
    case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_SBR:
#if 0 /* FIXME: here, stop currently unsupported codecs */
    case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_TwinVQ: /* NOTE: I think we already have a support for TwinVQ, but how to test this? */
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable:
    case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ:
    case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC:
    case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD:
#endif
        mp4a_put_GASpecificConfig( &bits, (mp4a_GASpecificConfig_t*)asc->deepAudioSpecificConfig );
        break;
    case MP4A_AUDIO_OBJECT_TYPE_Layer_1:
    case MP4A_AUDIO_OBJECT_TYPE_Layer_2:
    case MP4A_AUDIO_OBJECT_TYPE_Layer_3:
        mp4a_put_MPEG_1_2_SpecificConfig( &bits, (mp4a_MPEG_1_2_SpecificConfig_t*)asc->deepAudioSpecificConfig );
        break;
    case MP4A_AUDIO_OBJECT_TYPE_ALS:
        lsmash_bits_put( &bits, 5, 0 );     /* fillBits for byte alignment */
        mp4a_put_ALSSpecificConfig( &bits, (mp4a_ALSSpecificConfig_t *)asc->deepAudioSpecificConfig );
        break;
    default:
        break; /* FIXME: do we have to return error? */
    }

    /* FIXME: Error Resiliant stuff omitted here. */

    if( asc->sbr_mode == MP4A_AAC_SBR_BACKWARD_COMPATIBLE || asc->sbr_mode == MP4A_AAC_SBR_NONE )
    {
        lsmash_bits_put( &bits, 11, 0x2b7 );
        mp4a_put_AudioObjectType( &bits, asc->extensionAudioObjectType ); /* puts MP4A_AUDIO_OBJECT_TYPE_SBR */
        if( asc->extensionAudioObjectType == MP4A_AUDIO_OBJECT_TYPE_SBR ) /* this is always true, due to current spec */
        {
            /* sbrPresentFlag */
            if( asc->sbr_mode == MP4A_AAC_SBR_NONE )
                lsmash_bits_put( &bits, 1, 0x0 );
            else
            {
                lsmash_bits_put( &bits, 1, 0x1 );
                mp4a_put_SamplingFrequencyIndex( &bits, asc->extensionSamplingFrequencyIndex, asc->extensionSamplingFrequency );
            }
        }
    }
    lsmash_bits_put_align( &bits );
}

static int mp4a_get_GASpecificConfig( lsmash_bits_t *bits, mp4a_AudioSpecificConfig_t *asc )
{
    mp4a_GASpecificConfig_t *gasc = (mp4a_GASpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_GASpecificConfig_t) );
    if( !gasc )
        return LSMASH_ERR_MEMORY_ALLOC;
    asc->deepAudioSpecificConfig = gasc;
    gasc->frameLengthFlag    = lsmash_bits_get( bits, 1 );
    gasc->dependsOnCoreCoder = lsmash_bits_get( bits, 1 );
    if( gasc->dependsOnCoreCoder )
        gasc->coreCoderDelay = lsmash_bits_get( bits, 14 );
    gasc->extensionFlag = lsmash_bits_get( bits, 1 );
    return 0;
}

static int mp4a_get_MPEG_1_2_SpecificConfig( lsmash_bits_t *bits, mp4a_AudioSpecificConfig_t *asc )
{
    mp4a_MPEG_1_2_SpecificConfig_t *mpeg_1_2_sc = (mp4a_MPEG_1_2_SpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_MPEG_1_2_SpecificConfig_t) );
    if( !mpeg_1_2_sc )
        return LSMASH_ERR_MEMORY_ALLOC;
    asc->deepAudioSpecificConfig = mpeg_1_2_sc;
    mpeg_1_2_sc->extension = lsmash_bits_get( bits, 1 );
    return 0;
}

static int mp4a_get_ALSSpecificConfig( lsmash_bits_t *bits, mp4a_AudioSpecificConfig_t *asc )
{
    mp4a_ALSSpecificConfig_t *alssc = (mp4a_ALSSpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_ALSSpecificConfig_t) );
    if( !alssc )
        return LSMASH_ERR_MEMORY_ALLOC;
    asc->deepAudioSpecificConfig = alssc;
    alssc->als_id               = lsmash_bits_get( bits, 32 );
    alssc->samp_freq            = lsmash_bits_get( bits, 32 );
    alssc->samples              = lsmash_bits_get( bits, 32 );
    alssc->channels             = lsmash_bits_get( bits, 16 );
    alssc->file_type            = lsmash_bits_get( bits,  3 );
    alssc->resolution           = lsmash_bits_get( bits,  3 );
    alssc->floating             = lsmash_bits_get( bits,  1 );
    alssc->msb_first            = lsmash_bits_get( bits,  1 );
    alssc->frame_length         = lsmash_bits_get( bits, 16 );
    alssc->random_access        = lsmash_bits_get( bits,  8 );
    alssc->ra_flag              = lsmash_bits_get( bits,  2 );
    alssc->adapt_order          = lsmash_bits_get( bits,  1 );
    alssc->coef_table           = lsmash_bits_get( bits,  2 );
    alssc->long_term_prediction = lsmash_bits_get( bits,  1 );
    alssc->max_order            = lsmash_bits_get( bits, 10 );
    alssc->block_switching      = lsmash_bits_get( bits,  2 );
    alssc->bgmc_mode            = lsmash_bits_get( bits,  1 );
    alssc->sb_part              = lsmash_bits_get( bits,  1 );
    alssc->joint_stereo         = lsmash_bits_get( bits,  1 );
    alssc->mc_coding            = lsmash_bits_get( bits,  1 );
    alssc->chan_config          = lsmash_bits_get( bits,  1 );
    alssc->chan_sort            = lsmash_bits_get( bits,  1 );
    alssc->crc_enabled          = lsmash_bits_get( bits,  1 );
    alssc->RLSLMS               = lsmash_bits_get( bits,  1 );
    alssc->reserved             = lsmash_bits_get( bits,  5 );
    alssc->aux_data_enabled     = lsmash_bits_get( bits,  1 );
    return 0;
}

static mp4a_AudioSpecificConfig_t *mp4a_get_AudioSpecificConfig( uint8_t *dsi_payload, uint32_t dsi_payload_length )
{
    lsmash_bits_t *bits = lsmash_bits_adhoc_create();
    if( !bits )
        return NULL;
    if( lsmash_bits_import_data( bits, dsi_payload, dsi_payload_length ) < 0 )
    {
        lsmash_bits_adhoc_cleanup( bits );
        return NULL;
    }
    mp4a_AudioSpecificConfig_t *asc = (mp4a_AudioSpecificConfig_t *)lsmash_malloc_zero( sizeof(mp4a_AudioSpecificConfig_t) );
    if( !asc )
        goto fail;
    asc->audioObjectType = lsmash_bits_get( bits, 5 );
    if( asc->audioObjectType == 31 )
        asc->extensionAudioObjectType = asc->audioObjectType += 1 + lsmash_bits_get( bits, 6 );
    asc->samplingFrequencyIndex = lsmash_bits_get( bits, 4 );
    if( asc->samplingFrequencyIndex == 0xf )
        asc->samplingFrequency = lsmash_bits_get( bits, 24 );
    asc->channelConfiguration = lsmash_bits_get( bits, 4 );
    int ret = 0;
    switch( asc->audioObjectType )
    {
        case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LC :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable :
        case MP4A_AUDIO_OBJECT_TYPE_TwinVQ :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable :
        case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ :
        case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD :
            ret = mp4a_get_GASpecificConfig( bits, asc );
            break;
        case MP4A_AUDIO_OBJECT_TYPE_Layer_1 :
        case MP4A_AUDIO_OBJECT_TYPE_Layer_2 :
        case MP4A_AUDIO_OBJECT_TYPE_Layer_3 :
            ret = mp4a_get_MPEG_1_2_SpecificConfig( bits, asc );
            break;
        case MP4A_AUDIO_OBJECT_TYPE_ALS :
            lsmash_bits_get( bits, 5 );
            ret = mp4a_get_ALSSpecificConfig( bits, asc );
            break;
        default :
            break;
    }
    if( ret < 0 )
        goto fail;
    lsmash_bits_adhoc_cleanup( bits );
    return asc;
fail:
    lsmash_bits_adhoc_cleanup( bits );
    lsmash_free( asc );
    return NULL;
}

int mp4a_setup_summary_from_AudioSpecificConfig( lsmash_audio_summary_t *summary, uint8_t *dsi_payload, uint32_t dsi_payload_length )
{
    mp4a_AudioSpecificConfig_t *asc = mp4a_get_AudioSpecificConfig( dsi_payload, dsi_payload_length );
    if( !asc )
        return LSMASH_ERR_NAMELESS;
    summary->summary_type = LSMASH_SUMMARY_TYPE_AUDIO;
    summary->sample_type  = ISOM_CODEC_TYPE_MP4A_AUDIO;
    summary->aot          = asc->audioObjectType;
    switch( asc->audioObjectType )
    {
        case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LC :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP :
        case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable :
        case MP4A_AUDIO_OBJECT_TYPE_TwinVQ :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable :
        case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ :
        case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC :
        case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD :
        case MP4A_AUDIO_OBJECT_TYPE_Layer_1 :
        case MP4A_AUDIO_OBJECT_TYPE_Layer_2 :
        case MP4A_AUDIO_OBJECT_TYPE_Layer_3 :
            if( asc->samplingFrequencyIndex == 0xf )
                summary->frequency = asc->samplingFrequency;
            else
            {
                uint8_t i = 0x0;
                while( i != 0xc )
                {
                    if( mp4a_sampling_frequency_table[i][2] == asc->samplingFrequencyIndex )
                    {
                        summary->frequency = mp4a_sampling_frequency_table[i][1];
                        break;
                    }
                    ++i;
                }
                if( i == 0xc )
                {
                    mp4a_remove_AudioSpecificConfig( asc );
                    return LSMASH_ERR_INVALID_DATA;
                }
            }
            if( asc->channelConfiguration < 8 )
                summary->channels = asc->channelConfiguration != 7 ? asc->channelConfiguration : 8;
            else
                summary->channels = 0;      /* reserved */
            summary->sample_size = 16;
            switch( asc->audioObjectType )
            {
                case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR :
                    summary->samples_in_frame = 1024;
                    break;
                case MP4A_AUDIO_OBJECT_TYPE_Layer_1 :
                    summary->samples_in_frame = 384;
                    break;
                case MP4A_AUDIO_OBJECT_TYPE_Layer_2 :
                case MP4A_AUDIO_OBJECT_TYPE_Layer_3 :
                    summary->samples_in_frame = 1152;
                    break;
                default :
                    summary->samples_in_frame = !((mp4a_GASpecificConfig_t *)asc->deepAudioSpecificConfig)->frameLengthFlag ? 1024 : 960;
                    break;
            }
            break;
        case MP4A_AUDIO_OBJECT_TYPE_ALS :
        {
            mp4a_ALSSpecificConfig_t *alssc = (mp4a_ALSSpecificConfig_t *)asc->deepAudioSpecificConfig;
            summary->frequency        = alssc->samp_freq;
            summary->channels         = alssc->channels + 1;
            summary->sample_size      = (alssc->resolution + 1) * 8;
            summary->samples_in_frame = alssc->frame_length + 1;
            break;
        }
        default :
            break;
    }
    mp4a_remove_AudioSpecificConfig( asc );
    return 0;
}

/* This function is very ad-hoc. */
uint8_t *mp4a_export_AudioSpecificConfig( lsmash_mp4a_AudioObjectType aot,
                                          uint32_t frequency,
                                          uint32_t channels,
                                          lsmash_mp4a_aac_sbr_mode sbr_mode,
                                          uint8_t *exdata,
                                          uint32_t exdata_length,
                                          uint32_t *data_length )
{
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return NULL;
    mp4a_AudioSpecificConfig_t *asc = mp4a_create_AudioSpecificConfig( aot, frequency, channels, sbr_mode, exdata, exdata_length );
    if( !asc )
    {
        lsmash_bs_cleanup( bs );
        return NULL;
    }
    mp4a_put_AudioSpecificConfig( bs, asc );
    uint8_t *data = lsmash_bs_export_data( bs, data_length );
    mp4a_remove_AudioSpecificConfig( asc );
    lsmash_bs_cleanup( bs );
    if( !data )
        return NULL;
    return data;
}

static void mp4a_print_GASpecificConfig( FILE *fp, mp4a_AudioSpecificConfig_t *asc, int indent )
{
    mp4a_GASpecificConfig_t *gasc = (mp4a_GASpecificConfig_t *)asc->deepAudioSpecificConfig;
    lsmash_ifprintf( fp, indent++, "[GASpecificConfig]\n" );
    lsmash_ifprintf( fp, indent, "frameLengthFlag = %"PRIu8"\n", gasc->frameLengthFlag );
    lsmash_ifprintf( fp, indent, "dependsOnCoreCoder = %"PRIu8"\n", gasc->dependsOnCoreCoder );
    if( gasc->dependsOnCoreCoder )
        lsmash_ifprintf( fp, indent, "coreCoderDelay = %"PRIu16"\n", gasc->coreCoderDelay );
    lsmash_ifprintf( fp, indent, "extensionFlag = %"PRIu8"\n", gasc->extensionFlag );
    if( !asc->channelConfiguration )
        lsmash_ifprintf( fp, indent, "program_config_element()\n" );
}

static void mp4a_print_MPEG_1_2_SpecificConfig( FILE *fp, mp4a_AudioSpecificConfig_t *asc, int indent )
{
    mp4a_MPEG_1_2_SpecificConfig_t *mpeg_1_2_sc = (mp4a_MPEG_1_2_SpecificConfig_t *)asc->deepAudioSpecificConfig;
    lsmash_ifprintf( fp, indent++, "[MPEG_1_2_SpecificConfig]\n" );
    lsmash_ifprintf( fp, indent, "extension = %"PRIu8"\n", mpeg_1_2_sc->extension );
}

static void mp4a_print_ALSSpecificConfig( FILE *fp, mp4a_AudioSpecificConfig_t *asc, int indent )
{
    mp4a_ALSSpecificConfig_t *alssc = (mp4a_ALSSpecificConfig_t *)asc->deepAudioSpecificConfig;
    const char *file_type [4] = { "raw", "wave", "aiff", "bwf" };
    const char *floating  [2] = { "integer", "IEEE 32-bit floating-point" };
    const char *endian    [2] = { "little", "big" };
    const char *ra_flag   [4] = { "not stored", "stored at the beginning of frame_data()", "stored at the end of ALSSpecificConfig", "?" };
    lsmash_ifprintf( fp, indent++, "[ALSSpecificConfig]\n" );
    lsmash_ifprintf( fp, indent, "als_id = 0x%"PRIx32"\n", alssc->als_id );
    lsmash_ifprintf( fp, indent, "samp_freq = %"PRIu32" Hz\n", alssc->samp_freq );
    lsmash_ifprintf( fp, indent, "samples = %"PRIu32"\n", alssc->samples );
    lsmash_ifprintf( fp, indent, "channels = %"PRIu16"\n", alssc->channels );
    if( alssc->file_type <= 3 )
        lsmash_ifprintf( fp, indent, "file_type = %"PRIu8" (%s file)\n", alssc->file_type, file_type[ alssc->file_type ] );
    else
        lsmash_ifprintf( fp, indent, "file_type = %"PRIu8"\n", alssc->file_type );
    if( alssc->resolution <= 3 )
        lsmash_ifprintf( fp, indent, "resolution = %"PRIu8" (%d-bit)\n", alssc->resolution, 8 * (1 + alssc->resolution) );
    else
        lsmash_ifprintf( fp, indent, "resolution = %"PRIu8"\n", alssc->resolution );
    lsmash_ifprintf( fp, indent, "floating = %"PRIu8" (%s)\n", alssc->floating, floating[ alssc->floating ] );
    if( alssc->resolution )
        lsmash_ifprintf( fp, indent, "msb_first = %"PRIu8" (%s-endian)\n", alssc->msb_first, endian[ alssc->msb_first ] );
    else
        lsmash_ifprintf( fp, indent, "msb_first = %"PRIu8" (%ssigned data)\n", alssc->msb_first, ((const char *[2]){ "un", "" })[ alssc->msb_first ] );
    lsmash_ifprintf( fp, indent, "frame_length = %"PRIu16"\n", alssc->frame_length );
    lsmash_ifprintf( fp, indent, "random_access = %"PRIu8"\n", alssc->random_access );
    lsmash_ifprintf( fp, indent, "ra_flag = %"PRIu8" (ra_unit_size is %s)\n", alssc->ra_flag, ra_flag[ alssc->ra_flag ] );
    lsmash_ifprintf( fp, indent, "adapt_order = %"PRIu8"\n", alssc->adapt_order );
    lsmash_ifprintf( fp, indent, "coef_table = %"PRIu8"\n", alssc->coef_table );
    lsmash_ifprintf( fp, indent, "long_term_prediction = %"PRIu8"\n", alssc->long_term_prediction );
    lsmash_ifprintf( fp, indent, "max_order = %"PRIu8"\n", alssc->max_order );
    lsmash_ifprintf( fp, indent, "block_switching = %"PRIu8"\n", alssc->block_switching );
    lsmash_ifprintf( fp, indent, "bgmc_mode = %"PRIu8"\n", alssc->bgmc_mode );
    lsmash_ifprintf( fp, indent, "sb_part = %"PRIu8"\n", alssc->sb_part );
    lsmash_ifprintf( fp, indent, "joint_stereo = %"PRIu8"\n", alssc->joint_stereo );
    lsmash_ifprintf( fp, indent, "mc_coding = %"PRIu8"\n", alssc->mc_coding );
    lsmash_ifprintf( fp, indent, "chan_config = %"PRIu8"\n", alssc->chan_config );
    lsmash_ifprintf( fp, indent, "chan_sort = %"PRIu8"\n", alssc->chan_sort );
    lsmash_ifprintf( fp, indent, "crc_enabled = %"PRIu8"\n", alssc->crc_enabled );
    lsmash_ifprintf( fp, indent, "RLSLMS = %"PRIu8"\n", alssc->RLSLMS );
    lsmash_ifprintf( fp, indent, "reserved = %"PRIu8"\n", alssc->reserved );
    lsmash_ifprintf( fp, indent, "aux_data_enabled = %"PRIu8"\n", alssc->aux_data_enabled );
}

void mp4a_print_AudioSpecificConfig( FILE *fp, uint8_t *dsi_payload, uint32_t dsi_payload_length, int indent )
{
    assert( fp && dsi_payload && dsi_payload_length );
    mp4a_AudioSpecificConfig_t *asc = mp4a_get_AudioSpecificConfig( dsi_payload, dsi_payload_length );
    if( !asc )
        return;
    const char *audio_object_type[] =
        {
            "NULL",
            "AAC MAIN",
            "AAC LC (Low Complexity)",
            "AAC SSR (Scalable Sample Rate)",
            "AAC LTP (Long Term Prediction)",
            "SBR (Spectral Band Replication)",
            "AAC scalable",
            "TwinVQ",
            "CELP (Code Excited Linear Prediction)",
            "HVXC (Harmonic Vector Excitation Coding)",
            "reserved",
            "reserved",
            "TTSI (Text-To-Speech Interface)",
            "Main synthetic",
            "Wavetable synthesis",
            "General MIDI",
            "Algorithmic Synthesis and Audio FX",
            "ER AAC LC",
            "reserved",
            "ER AAC LTP",
            "ER AAC scalable",
            "ER Twin VQ",
            "ER BSAC (Bit-Sliced Arithmetic Coding)",
            "ER AAC LD",
            "ER CELP",
            "ER HVXC",
            "ER HILN (Harmonic and Individual Lines plus Noise)",
            "ER Parametric",
            "SSC (SinuSoidal Coding)",
            "PS (Parametric Stereo)",
            "MPEG Surround",
            "escape",
            "Layer-1",
            "Layer-2",
            "Layer-3",
            "DST (Direct Stream Transfer)",
            "ALS (Audio Lossless Coding)",
            "SLS (Scalable Lossless Coding)",
            "SLS non-core",
            "ER AAC ELD",
            "SMR Simple",
            "SMR Main",
            "USAC (Unified Speech and Audio Coding)",
            "SAOC",
            "LD MPEG Surround",
            "SAOC-DE"
        };
    lsmash_ifprintf( fp, indent++, "[AudioSpecificConfig]\n" );
    if( asc->audioObjectType < sizeof(audio_object_type) / sizeof(audio_object_type[0]) )
        lsmash_ifprintf( fp, indent, "audioObjectType = %d (%s)\n", asc->audioObjectType, audio_object_type[ asc->audioObjectType ] );
    else
        lsmash_ifprintf( fp, indent, "audioObjectType = %d\n", asc->audioObjectType );
    lsmash_ifprintf( fp, indent, "samplingFrequencyIndex = %"PRIu8"\n", asc->samplingFrequencyIndex );
    if( asc->samplingFrequencyIndex == 0xf )
        lsmash_ifprintf( fp, indent, "samplingFrequency = %"PRIu32"\n", asc->samplingFrequency );
    lsmash_ifprintf( fp, indent, "channelConfiguration = %"PRIu8"\n", asc->channelConfiguration );
    if( asc->extensionAudioObjectType == 5 )
    {
        lsmash_ifprintf( fp, indent, "extensionSamplingFrequencyIndex = %"PRIu8"\n", asc->extensionSamplingFrequencyIndex );
        if( asc->extensionSamplingFrequencyIndex == 0xf )
            lsmash_ifprintf( fp, indent, "extensionSamplingFrequency = %"PRIu32"\n", asc->extensionSamplingFrequency );
        if( asc->audioObjectType == 22 )
            lsmash_ifprintf( fp, indent, "extensionChannelConfiguration = %"PRIu8"\n", asc->extensionChannelConfiguration );
    }
    if( asc->deepAudioSpecificConfig )
        switch( asc->audioObjectType )
        {
            case MP4A_AUDIO_OBJECT_TYPE_AAC_MAIN :
            case MP4A_AUDIO_OBJECT_TYPE_AAC_LC :
            case MP4A_AUDIO_OBJECT_TYPE_AAC_SSR :
            case MP4A_AUDIO_OBJECT_TYPE_AAC_LTP :
            case MP4A_AUDIO_OBJECT_TYPE_AAC_scalable :
            case MP4A_AUDIO_OBJECT_TYPE_TwinVQ :
            case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LC :
            case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LTP :
            case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_scalable :
            case MP4A_AUDIO_OBJECT_TYPE_ER_Twin_VQ :
            case MP4A_AUDIO_OBJECT_TYPE_ER_BSAC :
            case MP4A_AUDIO_OBJECT_TYPE_ER_AAC_LD :
                mp4a_print_GASpecificConfig( fp, asc, indent );
                break;
            case MP4A_AUDIO_OBJECT_TYPE_Layer_1 :
            case MP4A_AUDIO_OBJECT_TYPE_Layer_2 :
            case MP4A_AUDIO_OBJECT_TYPE_Layer_3 :
                mp4a_print_MPEG_1_2_SpecificConfig( fp, asc, indent );
                break;
            case MP4A_AUDIO_OBJECT_TYPE_ALS :
                mp4a_print_ALSSpecificConfig( fp, asc, indent );
                break;
            default :
                break;
        }
    mp4a_remove_AudioSpecificConfig( asc );
}

int mp4a_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_audio_entry_t *mp4a = (isom_audio_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( mp4a ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_esds_t *esds;
    if( mp4a->version )
    {
        /* MPEG-4 Audio in QTFF */
        isom_wave_t *wave = (isom_wave_t *)isom_get_extension_box_format( &mp4a->extensions, QT_BOX_TYPE_WAVE );
        if( LSMASH_IS_NON_EXISTING_BOX( wave ) )
            return LSMASH_ERR_INVALID_DATA;
        esds = (isom_esds_t *)isom_get_extension_box_format( &wave->extensions, QT_BOX_TYPE_ESDS );
    }
    else
        esds = (isom_esds_t *)isom_get_extension_box_format( &mp4a->extensions, ISOM_BOX_TYPE_ESDS );
    if( LSMASH_IS_NON_EXISTING_BOX( esds ) || !esds->ES )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    if( err < 0 )
        return err;
    /* FIXME: avgBitrate is 0 only if VBR in proper. */
    return mp4sys_update_DecoderConfigDescriptor( esds->ES, bufferSizeDB, maxBitrate, 0 );
}

/***************************************************************************
    audioProfileLevelIndication
***************************************************************************/
/* NOTE: This function is not strictly preferable, but accurate.
   The spec of audioProfileLevelIndication is too much complicated. */
mp4a_audioProfileLevelIndication mp4a_get_audioProfileLevelIndication( lsmash_audio_summary_t *summary )
{
    if( !summary || summary->summary_type != LSMASH_SUMMARY_TYPE_AUDIO )
        return MP4A_AUDIO_PLI_NONE_REQUIRED;    /* means error. */
    if( lsmash_mp4sys_get_object_type_indication( (lsmash_summary_t *)summary ) != MP4SYS_OBJECT_TYPE_Audio_ISO_14496_3 )
        return MP4A_AUDIO_PLI_NOT_SPECIFIED;    /* This is of audio stream, but not described in ISO/IEC 14496-3. */
    if( summary->channels == 0 || summary->frequency == 0 )
        return MP4A_AUDIO_PLI_NONE_REQUIRED;    /* means error. */
    mp4a_audioProfileLevelIndication pli = MP4A_AUDIO_PLI_NOT_SPECIFIED;
    switch( summary->aot )
    {
        case MP4A_AUDIO_OBJECT_TYPE_AAC_LC:
            if( summary->sbr_mode == MP4A_AAC_SBR_HIERARCHICAL )
            {
                /* NOTE: This is not strictly preferable, but accurate; just possibly over-estimated.
                   We do not expect to use MP4A_AAC_SBR_HIERARCHICAL mode without SBR, nor downsampled mode with SBR. */
                if( summary->channels <= 2 && summary->frequency <= 24000 )
                    pli = MP4A_AUDIO_PLI_HE_AAC_L2;
                else if( summary->channels <= 5 && summary->frequency <= 48000 )
                    pli = MP4A_AUDIO_PLI_HE_AAC_L5;
                else
                    pli = MP4A_AUDIO_PLI_NOT_SPECIFIED;
                break;
            }
            /* pretending plain AAC-LC, if actually HE-AAC. */
            static const uint32_t mp4sys_aac_pli_table[5][3] = {
                /* channels, frequency,    audioProfileLevelIndication */
                {         6,     96000,        MP4A_AUDIO_PLI_AAC_L5 }, /* FIXME: 6ch is not strictly correct, but works in many case. */
                {         6,     48000,        MP4A_AUDIO_PLI_AAC_L4 }, /* FIXME: 6ch is not strictly correct, but works in many case. */
                {         2,     48000,        MP4A_AUDIO_PLI_AAC_L2 },
                {         2,     24000,        MP4A_AUDIO_PLI_AAC_L1 },
                {         0,         0, MP4A_AUDIO_PLI_NOT_SPECIFIED }
            };
            for( int i = 0; summary->channels <= mp4sys_aac_pli_table[i][0] && summary->frequency <= mp4sys_aac_pli_table[i][1] ; i++ )
                pli = mp4sys_aac_pli_table[i][2];
            break;
        case MP4A_AUDIO_OBJECT_TYPE_ALS:
            /* FIXME: this is not stricly. Summary shall carry max_order, block_switching, bgmc_mode and RLSLMS. */
            if( summary->channels <= 2 && summary->frequency <= 48000 && summary->sample_size <= 16 && summary->samples_in_frame <= 4096 )
                pli = MP4A_AUDIO_PLI_ALS_Simple_L1;
            else
                pli = MP4A_AUDIO_PLI_NOT_SPECIFIED;
            break;
        case MP4A_AUDIO_OBJECT_TYPE_Layer_1:
        case MP4A_AUDIO_OBJECT_TYPE_Layer_2:
        case MP4A_AUDIO_OBJECT_TYPE_Layer_3:
            pli = MP4A_AUDIO_PLI_NOT_SPECIFIED; /* 14496-3, Audio profiles and levels, does not allow any pli. */
            break;
        default:
            pli = MP4A_AUDIO_PLI_NOT_SPECIFIED; /* something we don't know/support, or what the spec never covers. */
            break;
    }
    return pli;
}

static int mp4sys_is_same_profile( mp4a_audioProfileLevelIndication a, mp4a_audioProfileLevelIndication b )
{
    switch( a )
    {
    case MP4A_AUDIO_PLI_Main_L1:
    case MP4A_AUDIO_PLI_Main_L2:
    case MP4A_AUDIO_PLI_Main_L3:
    case MP4A_AUDIO_PLI_Main_L4:
        if( MP4A_AUDIO_PLI_Main_L1 <= b && b <= MP4A_AUDIO_PLI_Main_L4 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_Scalable_L1:
    case MP4A_AUDIO_PLI_Scalable_L2:
    case MP4A_AUDIO_PLI_Scalable_L3:
    case MP4A_AUDIO_PLI_Scalable_L4:
        if( MP4A_AUDIO_PLI_Scalable_L1 <= b && b <= MP4A_AUDIO_PLI_Scalable_L4 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_Speech_L1:
    case MP4A_AUDIO_PLI_Speech_L2:
        if( MP4A_AUDIO_PLI_Speech_L1 <= b && b <= MP4A_AUDIO_PLI_Speech_L2 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_Synthetic_L1:
    case MP4A_AUDIO_PLI_Synthetic_L2:
    case MP4A_AUDIO_PLI_Synthetic_L3:
        if( MP4A_AUDIO_PLI_Synthetic_L1 <= b && b <= MP4A_AUDIO_PLI_Synthetic_L3 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_HighQuality_L1:
    case MP4A_AUDIO_PLI_HighQuality_L2:
    case MP4A_AUDIO_PLI_HighQuality_L3:
    case MP4A_AUDIO_PLI_HighQuality_L4:
    case MP4A_AUDIO_PLI_HighQuality_L5:
    case MP4A_AUDIO_PLI_HighQuality_L6:
    case MP4A_AUDIO_PLI_HighQuality_L7:
    case MP4A_AUDIO_PLI_HighQuality_L8:
        if( MP4A_AUDIO_PLI_HighQuality_L1 <= b && b <= MP4A_AUDIO_PLI_HighQuality_L8 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_LowDelay_L1:
    case MP4A_AUDIO_PLI_LowDelay_L2:
    case MP4A_AUDIO_PLI_LowDelay_L3:
    case MP4A_AUDIO_PLI_LowDelay_L4:
    case MP4A_AUDIO_PLI_LowDelay_L5:
    case MP4A_AUDIO_PLI_LowDelay_L6:
    case MP4A_AUDIO_PLI_LowDelay_L7:
    case MP4A_AUDIO_PLI_LowDelay_L8:
        if( MP4A_AUDIO_PLI_LowDelay_L1 <= b && b <= MP4A_AUDIO_PLI_LowDelay_L8 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_Natural_L1:
    case MP4A_AUDIO_PLI_Natural_L2:
    case MP4A_AUDIO_PLI_Natural_L3:
    case MP4A_AUDIO_PLI_Natural_L4:
        if( MP4A_AUDIO_PLI_Natural_L1 <= b && b <= MP4A_AUDIO_PLI_Natural_L4 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_MobileInternetworking_L1:
    case MP4A_AUDIO_PLI_MobileInternetworking_L2:
    case MP4A_AUDIO_PLI_MobileInternetworking_L3:
    case MP4A_AUDIO_PLI_MobileInternetworking_L4:
    case MP4A_AUDIO_PLI_MobileInternetworking_L5:
    case MP4A_AUDIO_PLI_MobileInternetworking_L6:
        if( MP4A_AUDIO_PLI_MobileInternetworking_L1 <= b && b <= MP4A_AUDIO_PLI_MobileInternetworking_L6 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_AAC_L1:
    case MP4A_AUDIO_PLI_AAC_L2:
    case MP4A_AUDIO_PLI_AAC_L4:
    case MP4A_AUDIO_PLI_AAC_L5:
        if( MP4A_AUDIO_PLI_AAC_L1 <= b && b <= MP4A_AUDIO_PLI_AAC_L5 )
            return 1;
        return 0;
        break;
    case MP4A_AUDIO_PLI_HE_AAC_L2:
    case MP4A_AUDIO_PLI_HE_AAC_L3:
    case MP4A_AUDIO_PLI_HE_AAC_L4:
    case MP4A_AUDIO_PLI_HE_AAC_L5:
        if( MP4A_AUDIO_PLI_HE_AAC_L2 <= b && b <= MP4A_AUDIO_PLI_HE_AAC_L5 )
            return 1;
        return 0;
        break;
    default:
        break;
    }
    return 0;
}

/* NOTE: This function is not strictly preferable, but accurate.
   The spec of audioProfileLevelIndication is too much complicated. */
mp4a_audioProfileLevelIndication mp4a_max_audioProfileLevelIndication( mp4a_audioProfileLevelIndication a, mp4a_audioProfileLevelIndication b )
{
    /* NONE_REQUIRED is minimal priotity, and NOT_SPECIFIED is max priority. */
    if( a == MP4A_AUDIO_PLI_NOT_SPECIFIED || b == MP4A_AUDIO_PLI_NONE_REQUIRED )
        return a;
    if( a == MP4A_AUDIO_PLI_NONE_REQUIRED || b == MP4A_AUDIO_PLI_NOT_SPECIFIED )
        return b;
    mp4a_audioProfileLevelIndication c, d;
    if( a < b )
    {
        c = a;
        d = b;
    }
    else
    {
        c = b;
        d = a;
    }
    /* AAC-LC and SBR specific; If mixtured there, use correspond HE_AAC profile. */
    if( MP4A_AUDIO_PLI_AAC_L1    <= c && c <= MP4A_AUDIO_PLI_AAC_L5
     && MP4A_AUDIO_PLI_HE_AAC_L2 <= d && d <= MP4A_AUDIO_PLI_HE_AAC_L5 )
    {
        if( c <= MP4A_AUDIO_PLI_AAC_L2 )
            return d;
        c += 4; /* upgrade to HE-AAC */
        return c > d ? c : d;
    }
    /* General */
    if( mp4sys_is_same_profile( c, d ) )
        return d;
    return MP4A_AUDIO_PLI_NOT_SPECIFIED;
}

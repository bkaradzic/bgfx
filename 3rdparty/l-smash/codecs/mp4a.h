/*****************************************************************************
 * mp4a.h
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

#ifndef MP4A_H
#define MP4A_H

/***************************************************************************
    MPEG-4 Systems for MPEG-4 Audio
***************************************************************************/

/* 14496-3 audioProfileLevelIndication */
typedef enum {
    MP4A_AUDIO_PLI_Reserved                 = 0x00, /* Reserved for ISO use */
    MP4A_AUDIO_PLI_Main_L1                  = 0x01, /* Main Audio Profile L1 */
    MP4A_AUDIO_PLI_Main_L2                  = 0x02, /* Main Audio Profile L2 */
    MP4A_AUDIO_PLI_Main_L3                  = 0x03, /* Main Audio Profile L3 */
    MP4A_AUDIO_PLI_Main_L4                  = 0x04, /* Main Audio Profile L4 */
    MP4A_AUDIO_PLI_Scalable_L1              = 0x05, /* Scalable Audio Profile L1 */
    MP4A_AUDIO_PLI_Scalable_L2              = 0x06, /* Scalable Audio Profile L2 */
    MP4A_AUDIO_PLI_Scalable_L3              = 0x07, /* Scalable Audio Profile L3 */
    MP4A_AUDIO_PLI_Scalable_L4              = 0x08, /* Scalable Audio Profile L4 */
    MP4A_AUDIO_PLI_Speech_L1                = 0x09, /* Speech Audio Profile L1 */
    MP4A_AUDIO_PLI_Speech_L2                = 0x0A, /* Speech Audio Profile L2 */
    MP4A_AUDIO_PLI_Synthetic_L1             = 0x0B, /* Synthetic Audio Profile L1 */
    MP4A_AUDIO_PLI_Synthetic_L2             = 0x0C, /* Synthetic Audio Profile L2 */
    MP4A_AUDIO_PLI_Synthetic_L3             = 0x0D, /* Synthetic Audio Profile L3 */
    MP4A_AUDIO_PLI_HighQuality_L1           = 0x0E, /* High Quality Audio Profile L1 */
    MP4A_AUDIO_PLI_HighQuality_L2           = 0x0F, /* High Quality Audio Profile L2 */
    MP4A_AUDIO_PLI_HighQuality_L3           = 0x10, /* High Quality Audio Profile L3 */
    MP4A_AUDIO_PLI_HighQuality_L4           = 0x11, /* High Quality Audio Profile L4 */
    MP4A_AUDIO_PLI_HighQuality_L5           = 0x12, /* High Quality Audio Profile L5 */
    MP4A_AUDIO_PLI_HighQuality_L6           = 0x13, /* High Quality Audio Profile L6 */
    MP4A_AUDIO_PLI_HighQuality_L7           = 0x14, /* High Quality Audio Profile L7 */
    MP4A_AUDIO_PLI_HighQuality_L8           = 0x15, /* High Quality Audio Profile L8 */
    MP4A_AUDIO_PLI_LowDelay_L1              = 0x16, /* Low Delay Audio Profile L1 */
    MP4A_AUDIO_PLI_LowDelay_L2              = 0x17, /* Low Delay Audio Profile L2 */
    MP4A_AUDIO_PLI_LowDelay_L3              = 0x18, /* Low Delay Audio Profile L3 */
    MP4A_AUDIO_PLI_LowDelay_L4              = 0x19, /* Low Delay Audio Profile L4 */
    MP4A_AUDIO_PLI_LowDelay_L5              = 0x1A, /* Low Delay Audio Profile L5 */
    MP4A_AUDIO_PLI_LowDelay_L6              = 0x1B, /* Low Delay Audio Profile L6 */
    MP4A_AUDIO_PLI_LowDelay_L7              = 0x1C, /* Low Delay Audio Profile L7 */
    MP4A_AUDIO_PLI_LowDelay_L8              = 0x1D, /* Low Delay Audio Profile L8 */
    MP4A_AUDIO_PLI_Natural_L1               = 0x1E, /* Natural Audio Profile L1 */
    MP4A_AUDIO_PLI_Natural_L2               = 0x1F, /* Natural Audio Profile L2 */
    MP4A_AUDIO_PLI_Natural_L3               = 0x20, /* Natural Audio Profile L3 */
    MP4A_AUDIO_PLI_Natural_L4               = 0x21, /* Natural Audio Profile L4 */
    MP4A_AUDIO_PLI_MobileInternetworking_L1 = 0x22, /* Mobile Audio Internetworking Profile L1 */
    MP4A_AUDIO_PLI_MobileInternetworking_L2 = 0x23, /* Mobile Audio Internetworking Profile L2 */
    MP4A_AUDIO_PLI_MobileInternetworking_L3 = 0x24, /* Mobile Audio Internetworking Profile L3 */
    MP4A_AUDIO_PLI_MobileInternetworking_L4 = 0x25, /* Mobile Audio Internetworking Profile L4 */
    MP4A_AUDIO_PLI_MobileInternetworking_L5 = 0x26, /* Mobile Audio Internetworking Profile L5 */
    MP4A_AUDIO_PLI_MobileInternetworking_L6 = 0x27, /* Mobile Audio Internetworking Profile L6 */
    MP4A_AUDIO_PLI_AAC_L1                   = 0x28, /* AAC Profile L1 */
    MP4A_AUDIO_PLI_AAC_L2                   = 0x29, /* AAC Profile L2 */
    MP4A_AUDIO_PLI_AAC_L4                   = 0x2A, /* AAC Profile L4 */
    MP4A_AUDIO_PLI_AAC_L5                   = 0x2B, /* AAC Profile L5 */
    MP4A_AUDIO_PLI_HE_AAC_L2                = 0x2C, /* High Efficiency AAC Profile L2 */
    MP4A_AUDIO_PLI_HE_AAC_L3                = 0x2D, /* High Efficiency AAC Profile L3 */
    MP4A_AUDIO_PLI_HE_AAC_L4                = 0x2E, /* High Efficiency AAC Profile L4 */
    MP4A_AUDIO_PLI_HE_AAC_L5                = 0x2F, /* High Efficiency AAC Profile L5 */
    MP4A_AUDIO_PLI_HE_AAC_v2_L2             = 0x30, /* High Efficiency AAC v2 Profile L2 */
    MP4A_AUDIO_PLI_HE_AAC_v2_L3             = 0x31, /* High Efficiency AAC v2 Profile L3 */
    MP4A_AUDIO_PLI_HE_AAC_v2_L4             = 0x32, /* High Efficiency AAC v2 Profile L4 */
    MP4A_AUDIO_PLI_HE_AAC_v2_L5             = 0x33, /* High Efficiency AAC v2 Profile L5 */
    MP4A_AUDIO_PLI_LowDelay_AAC_L1          = 0x34, /* Low Delay AAC Profile L1 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L1= 0x35, /* Baseline MPEG Surround Profile L1 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L2= 0x36, /* Baseline MPEG Surround Profile L2 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L3= 0x37, /* Baseline MPEG Surround Profile L3 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L4= 0x38, /* Baseline MPEG Surround Profile L4 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L5= 0x39, /* Baseline MPEG Surround Profile L5 */
    MP4A_AUDIO_PLI_Baseline_MPEG_Surround_L6= 0x3A, /* Baseline MPEG Surround Profile L6 */
    MP4A_AUDIO_PLI_HD_AAC_L1                = 0x3B, /* High Definition AAC Profile L1 */
    MP4A_AUDIO_PLI_ALS_Simple_L1            = 0x3C, /* ALS Simple Profile L1 */
    MP4A_AUDIO_PLI_NOT_SPECIFIED            = 0xFE, /* no audio profile specified */
    MP4A_AUDIO_PLI_NONE_REQUIRED            = 0xFF, /* no audio capability required */
} mp4a_audioProfileLevelIndication;

#ifndef MP4A_INTERNAL

typedef void mp4a_AudioSpecificConfig_t;

/* export for mp4sys / importer */
mp4a_AudioSpecificConfig_t *mp4a_create_AudioSpecificConfig(
    lsmash_mp4a_AudioObjectType aot,
    uint32_t frequency,
    uint32_t channels,
    lsmash_mp4a_aac_sbr_mode sbr_mode,
    uint8_t *exdata,
    uint32_t exdata_length
);
void mp4a_put_AudioSpecificConfig( lsmash_bs_t* bs, mp4a_AudioSpecificConfig_t* asc );
void mp4a_remove_AudioSpecificConfig( mp4a_AudioSpecificConfig_t* asc );

uint8_t *mp4a_export_AudioSpecificConfig( lsmash_mp4a_AudioObjectType aot,
                                          uint32_t frequency,
                                          uint32_t channels,
                                          lsmash_mp4a_aac_sbr_mode sbr_mode,
                                          uint8_t *exdata,
                                          uint32_t exdata_length,
                                          uint32_t *data_length );

/* export for importer */
extern const uint32_t mp4a_sampling_frequency_table[13][5];

/* setup for summary */
int mp4a_setup_summary_from_AudioSpecificConfig( lsmash_audio_summary_t *summary, uint8_t *dsi_payload, uint32_t dsi_payload_length );

/* profileLevelIndication relative functions. */
mp4a_audioProfileLevelIndication mp4a_get_audioProfileLevelIndication( lsmash_audio_summary_t *summary );
mp4a_audioProfileLevelIndication mp4a_max_audioProfileLevelIndication(
    mp4a_audioProfileLevelIndication a,
    mp4a_audioProfileLevelIndication b
);

#endif

#endif

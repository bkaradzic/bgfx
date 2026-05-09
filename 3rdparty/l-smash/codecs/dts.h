/*****************************************************************************
 * dts.h
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

#define DTS_MAX_CORE_SIZE 16384
#define DTS_MAX_EXSS_SIZE 32768
#define DTS_MAX_NUM_EXSS      4 /* the maximum number of extension substreams */

typedef enum
{
    DTS_SUBSTREAM_TYPE_NONE      = 0,
    DTS_SUBSTREAM_TYPE_CORE      = 1,
    DTS_SUBSTREAM_TYPE_EXTENSION = 2,
} dts_substream_type;

typedef struct
{
    uint16_t size;
    uint16_t channel_layout;
    uint8_t  lower_planes;      /* CL, LL and RL */
} dts_xxch_info_t;

typedef struct
{
    uint32_t sampling_frequency;
    uint32_t frame_duration;
    uint16_t frame_size;
    uint16_t channel_layout;
    uint8_t  channel_arrangement;
    uint8_t  extension_audio_descriptor;
    uint8_t  pcm_resolution;
    dts_xxch_info_t xxch;
} dts_core_info_t;

typedef struct
{
    uint16_t size;
    uint16_t channel_layout;
    uint32_t sampling_frequency;
    uint32_t frame_duration;
    uint8_t  pcm_resolution;
    uint8_t  stereo_downmix;
    uint8_t  lower_planes;      /* CL, LL and RL */
    uint8_t  dtsx_extension_present;
} dts_xll_info_t;

typedef struct
{
    uint16_t size;
    uint16_t channel_layout;
    uint32_t sampling_frequency;
    uint32_t frame_duration;
    uint8_t  stereo_downmix;
    uint8_t  lfe_present;
    uint8_t  duration_modifier;
    uint8_t  sample_size;
} dts_lbr_info_t;

typedef struct
{
    uint32_t                     size;
    uint16_t                     channel_layout;
    uint8_t                      bOne2OneMapChannels2Speakers;
    uint8_t                      nuRepresentationType;
    uint8_t                      nuCodingMode;
    lsmash_dts_construction_flag nuCoreExtensionMask;
    dts_core_info_t              core;
    dts_xll_info_t               xll;
    dts_lbr_info_t               lbr;
    uint16_t                     xbr_size;
    uint16_t                     x96_size;
    uint16_t                     aux_size;
} dts_audio_asset_t;

typedef struct
{
    uint32_t sampling_frequency;
    uint32_t frame_duration;
    uint8_t  nuBits4ExSSFsize;
    uint8_t  bStaticFieldsPresent;
    uint8_t  bMixMetadataEnbl;
    uint8_t  nuNumMixOutConfigs;
    uint8_t  nNumMixOutCh[4];
    uint8_t  nuNumAudioPresnt;
    uint8_t  nuNumAssets;
    uint8_t  nuActiveExSSMask[8];
    uint8_t  nuActiveAssetMask[8][4];
    uint8_t  bBcCorePresent[8];
    uint8_t  nuBcCoreExtSSIndex[8];
    uint8_t  nuBcCoreAssetIndex[8];
    uint8_t  stereo_downmix;
    uint8_t  bit_resolution;
    dts_audio_asset_t asset[8];
} dts_extension_info_t;

typedef struct
{
    dts_substream_type               substream_type;
    lsmash_dts_construction_flag     flags;
    lsmash_dts_specific_parameters_t ddts_param;
    dts_core_info_t                  core;      /* core component and its extensions in core substream */
    dts_extension_info_t             exss[4];   /* extension substreams */
    uint8_t  ddts_param_initialized;
    uint8_t  exss_index;
    uint8_t  exss_count;
    uint32_t frame_duration;
    uint32_t frame_size;        /* size of substream */
    lsmash_bits_t *bits;
} dts_info_t;

void dts_setup_parser( dts_info_t *info );
int dts_parse_core_substream( dts_info_t *info );
int dts_parse_extension_substream( dts_info_t *info );
int dts_get_max_channel_count( dts_info_t *info );
dts_substream_type dts_get_substream_type( dts_info_t *info );
int dts_get_exss_index( dts_info_t *info, uint8_t *exss_index );
void dts_update_specific_param( dts_info_t *info );

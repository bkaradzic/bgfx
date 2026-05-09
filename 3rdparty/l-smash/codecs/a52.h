/*****************************************************************************
 * a52.h
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

#define AC3_MIN_SYNCFRAME_LENGTH  128
#define AC3_MAX_SYNCFRAME_LENGTH  3840
#define EAC3_MAX_SYNCFRAME_LENGTH 4096

typedef struct
{
    lsmash_ac3_specific_parameters_t dac3_param;
    lsmash_bits_t *bits;
} ac3_info_t;

typedef struct
{
    lsmash_eac3_specific_parameters_t dec3_param;
    lsmash_eac3_substream_info_t independent_info[8];
    lsmash_eac3_substream_info_t dependent_info;
    uint8_t  dec3_param_initialized;
    uint8_t  strmtyp;
    uint8_t  substreamid;
    uint8_t  current_independent_substream_id;
    uint8_t  fscod2;
    uint8_t  numblkscod;
    uint8_t  number_of_audio_blocks;
    uint8_t  number_of_independent_substreams;
    uint32_t syncframe_count;
    uint32_t frame_size;
    lsmash_bits_t *bits;
} eac3_info_t;

extern const uint32_t ac3_sample_rate_table  [4];
extern const uint32_t ac3_channel_count_table[8];
extern const uint8_t eac3_audio_block_table  [4];

static inline uint32_t ac3_get_channel_count
(
    lsmash_ac3_specific_parameters_t *dac3_param
)
{
    return ac3_channel_count_table[ dac3_param->acmod ] + dac3_param->lfeon;
}

uint32_t ac3_get_sample_rate
(
    lsmash_ac3_specific_parameters_t *dac3_param
);

int ac3_parse_syncframe_header
(
    ac3_info_t *info
);

int eac3_parse_syncframe
(
    eac3_info_t *info
);

void eac3_update_specific_param
(
    eac3_info_t *info
);

void eac3_update_sample_rate
(
    uint32_t                          *frequency,
    lsmash_eac3_specific_parameters_t *dec3_param,
    uint8_t                           *fscod2
);

void eac3_update_channel_count
(
    uint32_t                          *channels,
    lsmash_eac3_specific_parameters_t *dec3_param
);

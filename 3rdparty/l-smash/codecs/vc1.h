/*****************************************************************************
 * vc1.h
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

#define VC1_DEFAULT_BUFFER_SIZE      (1<<16)
#define VC1_START_CODE_PREFIX_LENGTH 3      /* 0x000001 */
#define VC1_START_CODE_SUFFIX_LENGTH 1      /* BDU type */
#define VC1_START_CODE_LENGTH (VC1_START_CODE_PREFIX_LENGTH + VC1_START_CODE_SUFFIX_LENGTH)     /* = 4 */

typedef struct
{
    uint8_t hrd_num_leaky_buckets;
} vc1_hrd_param_t;

typedef struct
{
    uint8_t  present;
    uint8_t  profile;
    uint8_t  level;
    uint8_t  colordiff_format;      /* currently 4:2:0 only */
    uint8_t  interlace;
    uint8_t  color_prim;
    uint8_t  transfer_char;
    uint8_t  matrix_coef;
    uint8_t  hrd_param_flag;
    uint8_t  aspect_width;
    uint8_t  aspect_height;
    uint8_t  framerate_flag;
    uint32_t framerate_numerator;
    uint32_t framerate_denominator;
    uint16_t max_coded_width;
    uint16_t max_coded_height;
    uint16_t disp_horiz_size;
    uint16_t disp_vert_size;
    vc1_hrd_param_t hrd_param;
} vc1_sequence_header_t;

typedef struct
{
    uint8_t present;
    uint8_t closed_entry_point;
} vc1_entry_point_t;

typedef struct
{
    uint8_t present;
    uint8_t frame_coding_mode;
    uint8_t type;
    uint8_t closed_gop;
    uint8_t start_of_sequence;
    uint8_t random_accessible;
} vc1_picture_info_t;

typedef struct
{
    uint8_t  random_accessible;
    uint8_t  closed_gop;
    uint8_t  independent;
    uint8_t  non_bipredictive;
    uint8_t  disposable;
    uint8_t *data;
    uint32_t data_length;
    uint8_t *incomplete_data;
    uint32_t incomplete_data_length;
    uint32_t number;
} vc1_access_unit_t;

typedef struct vc1_info_tag vc1_info_t;

typedef struct
{
    lsmash_multiple_buffers_t *bank;
    uint8_t                   *rbdu;
} vc1_stream_buffer_t;

struct vc1_info_tag
{
    lsmash_vc1_specific_parameters_t dvc1_param;
    vc1_sequence_header_t sequence;
    vc1_entry_point_t     entry_point;
    vc1_picture_info_t    picture;
    vc1_access_unit_t     access_unit;
    uint8_t               prev_bdu_type;
    uint64_t              ebdu_head_pos;
    lsmash_bits_t        *bits;
    vc1_stream_buffer_t   buffer;
};

int vc1_setup_parser
(
    vc1_info_t *info,
    int         parse_only
);

uint64_t vc1_find_next_start_code_prefix
(
    lsmash_bs_t *bs,
    uint8_t     *bdu_type,
    uint64_t    *trailing_zero_bytes
);

int vc1_check_next_start_code_suffix
(
    lsmash_bs_t *bs,
    uint8_t     *p_bdu_type
);

void vc1_cleanup_parser( vc1_info_t *info );
int vc1_parse_sequence_header( vc1_info_t *info, uint8_t *ebdu, uint64_t ebdu_size, int probe );
int vc1_parse_entry_point_header( vc1_info_t *info, uint8_t *ebdu, uint64_t ebdu_size, int probe );
int vc1_parse_advanced_picture( lsmash_bits_t *bits,
                                vc1_sequence_header_t *sequence, vc1_picture_info_t *picture,
                                uint8_t *rbdu_buffer, uint8_t *ebdu, uint64_t ebdu_size );
void vc1_update_au_property( vc1_access_unit_t *access_unit, vc1_picture_info_t *picture );
int vc1_find_au_delimit_by_bdu_type( uint8_t bdu_type, uint8_t prev_bdu_type );
int vc1_supplement_buffer( vc1_stream_buffer_t *buffer, vc1_access_unit_t *access_unit, uint32_t size );

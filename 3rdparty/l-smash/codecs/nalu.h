/*****************************************************************************
 * nalu.h
 *****************************************************************************
 * Copyright (C) 2013-2017 L-SMASH project
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

#define NALU_DEFAULT_BUFFER_SIZE      (1<<16)
#define NALU_DEFAULT_NALU_LENGTH_SIZE 4     /* We always use 4 bytes length. */
#define NALU_SHORT_START_CODE_LENGTH  3
#define NALU_LONG_START_CODE_LENGTH   4
#define NALU_IO_ERROR                 UINT64_MAX - 1
#define NALU_NO_START_CODE_FOUND      UINT64_MAX

/* Parameter Set Entry within AVC/HEVC Decoder Configuration Record */
typedef struct
{
    uint16_t nalUnitLength;
    uint8_t *nalUnit;
    /* */
    int      unused;
} isom_dcr_ps_entry_t;

isom_dcr_ps_entry_t *isom_create_ps_entry
(
    uint8_t *ps,
    uint32_t ps_size
);

void isom_remove_dcr_ps
(
    isom_dcr_ps_entry_t *ps
);

int nalu_import_rbsp_from_ebsp
(
    lsmash_bits_t *bits,
    uint8_t       *rbsp_buffer,
    uint64_t      *rbsp_size,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
);

int nalu_check_more_rbsp_data
(
    lsmash_bits_t *bits
);

int nalu_get_max_ps_length
(
    lsmash_entry_list_t *ps_list,
    uint32_t            *max_ps_length
);

int nalu_get_ps_count
(
    lsmash_entry_list_t *ps_list,
    uint32_t            *ps_count
);

int nalu_check_same_ps_existence
(
    lsmash_entry_list_t *ps_list,
    void                *ps_data,
    uint32_t             ps_length
);

int nalu_get_dcr_ps
(
    lsmash_bs_t         *bs,
    lsmash_entry_list_t *list,
    uint8_t              entry_count
);

/* Return the offset from the beginning of stream if a start code is found.
 * Return NALU_NO_START_CODE_FOUND otherwise. */
uint64_t nalu_find_first_start_code
(
    lsmash_bs_t *bs
);

uint64_t nalu_get_codeNum
(
    lsmash_bits_t *bits
);

static inline uint64_t nalu_decode_exp_golomb_ue
(
    uint64_t codeNum
)
{
    return codeNum;
}

static inline int64_t nalu_decode_exp_golomb_se
(
    uint64_t codeNum
)
{
    if( codeNum & 1 )
        return (int64_t)((codeNum >> 1) + 1);
    return -1 * (int64_t)(codeNum >> 1);
}

static inline uint64_t nalu_get_exp_golomb_ue
(
    lsmash_bits_t *bits
)
{
    uint64_t codeNum = nalu_get_codeNum( bits );
    return nalu_decode_exp_golomb_ue( codeNum );
}

static inline uint64_t nalu_get_exp_golomb_se
(
    lsmash_bits_t *bits
)
{
    uint64_t codeNum = nalu_get_codeNum( bits );
    return nalu_decode_exp_golomb_se( codeNum );
}

static inline int nalu_check_next_short_start_code
(
    uint8_t *buf_pos,
    uint8_t *buf_end
)
{
    return ((buf_pos + 2) < buf_end) && !buf_pos[0] && !buf_pos[1] && (buf_pos[2] == 0x01);
}

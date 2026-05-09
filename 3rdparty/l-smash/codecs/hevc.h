/*****************************************************************************
 * hevc.h
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

enum
{
    HEVC_NALU_TYPE_TRAIL_N        = 0,
    HEVC_NALU_TYPE_TRAIL_R        = 1,
    HEVC_NALU_TYPE_TSA_N          = 2,
    HEVC_NALU_TYPE_TSA_R          = 3,
    HEVC_NALU_TYPE_STSA_N         = 4,
    HEVC_NALU_TYPE_STSA_R         = 5,
    HEVC_NALU_TYPE_RADL_N         = 6,
    HEVC_NALU_TYPE_RADL_R         = 7,
    HEVC_NALU_TYPE_RASL_N         = 8,
    HEVC_NALU_TYPE_RASL_R         = 9,
    HEVC_NALU_TYPE_RSV_VCL_R15    = 15,
    HEVC_NALU_TYPE_BLA_W_LP       = 16,
    HEVC_NALU_TYPE_BLA_W_RADL     = 17,
    HEVC_NALU_TYPE_BLA_N_LP       = 18,
    HEVC_NALU_TYPE_IDR_W_RADL     = 19,
    HEVC_NALU_TYPE_IDR_N_LP       = 20,
    HEVC_NALU_TYPE_CRA            = 21,
    HEVC_NALU_TYPE_RSV_IRAP_VCL22 = 22,
    HEVC_NALU_TYPE_RSV_IRAP_VCL23 = 23,
    HEVC_NALU_TYPE_RSV_VCL31      = 31,
    HEVC_NALU_TYPE_VPS            = 32,
    HEVC_NALU_TYPE_SPS            = 33,
    HEVC_NALU_TYPE_PPS            = 34,
    HEVC_NALU_TYPE_AUD            = 35,
    HEVC_NALU_TYPE_EOS            = 36,
    HEVC_NALU_TYPE_EOB            = 37,
    HEVC_NALU_TYPE_FD             = 38,
    HEVC_NALU_TYPE_PREFIX_SEI     = 39,
    HEVC_NALU_TYPE_SUFFIX_SEI     = 40,
    HEVC_NALU_TYPE_RSV_NVCL41     = 41,
    HEVC_NALU_TYPE_RSV_NVCL44     = 44,
    HEVC_NALU_TYPE_RSV_NVCL47     = 47,
    HEVC_NALU_TYPE_UNSPEC48       = 48,
    HEVC_NALU_TYPE_UNSPEC55       = 55,
    HEVC_NALU_TYPE_UNSPEC63       = 63,
    HEVC_NALU_TYPE_UNKNOWN        = 64
};

typedef struct
{
    uint8_t             array_completeness;
    uint8_t             NAL_unit_type;
    lsmash_entry_list_t list[1];
} hevc_parameter_array_t;

struct lsmash_hevc_parameter_arrays_tag
{
    hevc_parameter_array_t ps_array[HEVC_DCR_NALU_TYPE_NUM];
};

typedef struct
{
    unsigned forbidden_zero_bit : 1;
    unsigned nal_unit_type      : 7;   /* +1 bit for HEVC_NALU_TYPE_UNKNOWN */
    unsigned nuh_layer_id       : 6;
    unsigned TemporalId         : 3;
    unsigned length             : 15;
} hevc_nalu_header_t;

/* Profile, Tier and Level */
typedef struct
{
    uint8_t  profile_space;
    uint8_t  tier_flag;
    uint8_t  profile_idc;
    uint32_t profile_compatibility_flags;
    uint8_t  progressive_source_flag;
    uint8_t  interlaced_source_flag;
    uint8_t  non_packed_constraint_flag;
    uint8_t  frame_only_constraint_flag;
    uint64_t reserved_zero_44bits;
    uint8_t  level_idc;
} hevc_ptl_common_t;

typedef struct
{
    hevc_ptl_common_t general;
    hevc_ptl_common_t sub_layer[6];
} hevc_ptl_t;

/* HRD (Hypothetical Reference Decoder) */
typedef struct
{
    uint8_t  present;
    uint8_t  CpbDpbDelaysPresentFlag;
    uint8_t  sub_pic_hrd_params_present_flag;
    uint8_t  du_cpb_removal_delay_increment_length;
    uint8_t  sub_pic_cpb_params_in_pic_timing_sei_flag;
    uint8_t  dpb_output_delay_du_length;
    uint8_t  au_cpb_removal_delay_length;
    uint8_t  dpb_output_delay_length;
    uint8_t  fixed_pic_rate_general_flag[7];
    uint16_t elemental_duration_in_tc   [7];
} hevc_hrd_t;

/* VPS (Video Parameter Set) */
typedef struct
{
    uint8_t    present;
    uint8_t    video_parameter_set_id;
    uint8_t    max_sub_layers_minus1;
    uint8_t    temporal_id_nesting_flag;
    uint8_t    timing_info_present_flag;
    uint8_t    frame_field_info_present_flag;
    uint16_t   num_hrd_parameters;
    hevc_ptl_t ptl;
    hevc_hrd_t hrd[2];
} hevc_vps_t;

typedef struct
{
    uint8_t       present;
    uint16_t      sar_width;
    uint16_t      sar_height;
    uint8_t       video_full_range_flag;
    uint8_t       colour_description_present_flag;
    uint8_t       colour_primaries;
    uint8_t       transfer_characteristics;
    uint8_t       matrix_coeffs;
    uint8_t       field_seq_flag;
    uint8_t       frame_field_info_present_flag;
    uint32_t      num_units_in_tick;
    uint32_t      time_scale;
    uint16_t      min_spatial_segmentation_idc;
    lsmash_crop_t def_disp_win_offset;
    hevc_hrd_t    hrd;
} hevc_vui_t;

/* Short term reference picture sets */
typedef struct
{
    uint8_t NumNegativePics;
    uint8_t NumPositivePics;
    uint8_t NumDeltaPocs;
    uint8_t UsedByCurrPicS0[16];
    uint8_t UsedByCurrPicS1[16];
    int32_t DeltaPocS0[16];
    int32_t DeltaPocS1[16];
} hevc_st_rps_t;

/* SPS (Sequence Parameter Set) */
typedef struct
{
    uint8_t       present;
    uint8_t       video_parameter_set_id;
    uint8_t       max_sub_layers_minus1;
    uint8_t       temporal_id_nesting_flag;
    hevc_ptl_t    ptl;
    uint8_t       seq_parameter_set_id;
    uint8_t       chroma_format_idc;
    uint8_t       separate_colour_plane_flag;
    uint8_t       bit_depth_luma_minus8;
    uint8_t       bit_depth_chroma_minus8;
    uint8_t       log2_max_pic_order_cnt_lsb;
    uint8_t       num_short_term_ref_pic_sets;
    uint8_t       long_term_ref_pics_present_flag;
    uint8_t       num_long_term_ref_pics_sps;
    uint8_t       temporal_mvp_enabled_flag;
    uint32_t      cropped_width;
    uint32_t      cropped_height;
    uint32_t      PicWidthInCtbsY;
    uint32_t      PicHeightInCtbsY;
    uint64_t      PicSizeInCtbsY;
    hevc_st_rps_t st_rps[65];
    hevc_vui_t    vui;
} hevc_sps_t;

/* PPS (Picture Parameter Set) */
typedef struct
{
    uint8_t   present;
    uint8_t   pic_parameter_set_id;
    uint8_t   seq_parameter_set_id;
    uint8_t   dependent_slice_segments_enabled_flag;
    uint8_t   output_flag_present_flag;
    uint8_t   num_extra_slice_header_bits;
    uint8_t   tiles_enabled_flag;
    uint8_t   entropy_coding_sync_enabled_flag;
    uint32_t  num_tile_columns_minus1;
    uint32_t  num_tile_rows_minus1;
#define SIZEOF_PPS_EXCLUDING_HEAP (sizeof(hevc_pps_t) - offsetof( hevc_pps_t, col_alloc_size ))
    size_t    col_alloc_size;
    size_t    row_alloc_size;
    uint32_t *colWidth;
    uint32_t *colBd;
    uint32_t *rowHeight;
    uint32_t *rowBd;
} hevc_pps_t;

/* SEI (Supplemental Enhancement Information) */
typedef struct
{
    uint8_t present;
    uint8_t pic_struct;
} hevc_pic_timing_t;

typedef struct
{
    uint8_t present;
    uint8_t broken_link_flag;
    int32_t recovery_poc_cnt;
} hevc_recovery_point_t;

typedef struct
{
    hevc_pic_timing_t     pic_timing;
    hevc_recovery_point_t recovery_point;
} hevc_sei_t;

/* Slice segment */
typedef struct
{
    uint8_t  present;
    uint8_t  nalu_type;
    uint8_t  TemporalId;
    uint8_t  type;
    uint8_t  video_parameter_set_id;
    uint8_t  seq_parameter_set_id;
    uint8_t  pic_parameter_set_id;
    uint8_t  first_slice_segment_in_pic_flag;
    uint8_t  dependent_slice_segment_flag;
    uint64_t segment_address;
    int32_t  pic_order_cnt_lsb;
} hevc_slice_info_t;

/* Picture */
typedef enum
{
    HEVC_PICTURE_TYPE_I     = 0,
    HEVC_PICTURE_TYPE_I_P   = 1,
    HEVC_PICTURE_TYPE_I_P_B = 2,
    HEVC_PICTURE_TYPE_IDR   = 3,
    HEVC_PICTURE_TYPE_CRA   = 4,
    HEVC_PICTURE_TYPE_BLA   = 5,
    HEVC_PICTURE_TYPE_NONE  = 6,
} hevc_picture_type;

typedef struct
{
    hevc_picture_type type;
    uint8_t           irap;             /* 1: IDR, CRA or BLA picture */
    uint8_t           idr;              /* 1: IDR picture */
    uint8_t           broken_link;      /* 1: BLA picture or picture with broken link flag */
    uint8_t           radl;             /* 1: RADL picture */
    uint8_t           rasl;             /* 1: RASL picture */
    uint8_t           sublayer_nonref;  /* 1: sub-layer non-reference picture */
    uint8_t           closed_rap;       /* 1: no undecodable leading picture in CVS */
    uint8_t           random_accessible;/* 1: RAP or starting point of GDR */
    uint8_t           TemporalId;
    uint8_t           independent;      /* 1: intra coded picture */
    uint8_t           field_coded;      /* 1: field coded picture */
    uint8_t           pic_parameter_set_id;
    uint8_t           has_primary;      /* 1: an independent slice segment is present. */
    uint8_t           delta;
    /* POC */
    uint16_t          poc_lsb;
    int32_t           poc;
    int32_t           tid0_poc_msb;
    int32_t           tid0_poc_lsb;
    /* */
    int32_t           recovery_poc_cnt;
} hevc_picture_info_t;

/* Access unit */
typedef struct
{
    uint8_t            *data;
    uint8_t            *incomplete_data;
    uint32_t            length;
    uint32_t            incomplete_length;
    uint32_t            number;
    uint8_t             TemporalId;
    hevc_picture_info_t picture;
} hevc_access_unit_t;

typedef struct hevc_info_tag hevc_info_t;

typedef struct
{
    lsmash_multiple_buffers_t *bank;
    uint8_t                   *rbsp;
} hevc_stream_buffer_t;

struct hevc_info_tag
{
    lsmash_hevc_specific_parameters_t hvcC_param;
    lsmash_hevc_specific_parameters_t hvcC_param_next;
    hevc_nalu_header_t   nuh;
    lsmash_entry_list_t  vps_list[1];
    lsmash_entry_list_t  sps_list[1];
    lsmash_entry_list_t  pps_list[1];
    hevc_vps_t           vps;           /* active VPS */
    hevc_sps_t           sps;           /* active SPS */
    hevc_pps_t           pps;           /* active PPS */
    hevc_sei_t           sei;           /* active SEI */
    hevc_slice_info_t    slice;         /* active slice */
    hevc_access_unit_t   au;
    uint8_t              prev_nalu_type;
    uint8_t              hvcC_pending;
    uint8_t              eos;           /* end of sequence */
    uint64_t             ebsp_head_pos;
    lsmash_bits_t       *bits;
    hevc_stream_buffer_t buffer;
};

int hevc_setup_parser
(
    hevc_info_t *info,
    int          parse_only
);

void hevc_cleanup_parser
(
    hevc_info_t *info
);

uint64_t hevc_find_next_start_code
(
    lsmash_bs_t        *bs,
    hevc_nalu_header_t *nuh,
    uint64_t           *start_code_length,
    uint64_t           *trailing_zero_bytes
);

int hevc_calculate_poc
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_picture_info_t *prev_picture
);

void hevc_update_picture_info_for_slice
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_slice_info_t   *slice
);

void hevc_update_picture_info
(
    hevc_info_t         *info,
    hevc_picture_info_t *picture,
    hevc_slice_info_t   *slice,
    hevc_sps_t          *sps,
    hevc_sei_t          *sei
);

int hevc_find_au_delimit_by_slice_info
(
    hevc_info_t       *info,
    hevc_slice_info_t *slice,
    hevc_slice_info_t *prev_slice
);

int hevc_find_au_delimit_by_nalu_type
(
    uint8_t nalu_type,
    uint8_t prev_nalu_type
);

int hevc_supplement_buffer
(
    hevc_stream_buffer_t *hb,
    hevc_access_unit_t   *au,
    uint32_t              size
);

int hevc_parse_vps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
);

int hevc_parse_sps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
);

int hevc_parse_pps
(
    hevc_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
);

int hevc_parse_sei
(
    lsmash_bits_t      *bits,
    hevc_vps_t         *vps,
    hevc_sps_t         *sps,
    hevc_sei_t         *sei,
    hevc_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
);
int hevc_parse_slice_segment_header
(
    hevc_info_t        *info,
    hevc_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
);

int hevc_try_to_append_dcr_nalu
(
    hevc_info_t              *info,
    lsmash_hevc_dcr_nalu_type ps_type,
    void                     *ps_data,
    uint32_t                  ps_length
);

int hevc_move_pending_hvcC_param
(
    hevc_info_t *info
);

/*****************************************************************************
 * h264.h
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

enum
{
    H264_NALU_TYPE_UNSPECIFIED0  = 0,   /* Unspecified */
    H264_NALU_TYPE_SLICE_N_IDR   = 1,   /* Coded slice of a non-IDR picture */
    H264_NALU_TYPE_SLICE_DP_A    = 2,   /* Coded slice data partition A */
    H264_NALU_TYPE_SLICE_DP_B    = 3,   /* Coded slice data partition B */
    H264_NALU_TYPE_SLICE_DP_C    = 4,   /* Coded slice data partition C */
    H264_NALU_TYPE_SLICE_IDR     = 5,   /* Coded slice of an IDR picture */
    H264_NALU_TYPE_SEI           = 6,   /* Supplemental Enhancement Information */
    H264_NALU_TYPE_SPS           = 7,   /* Sequence Parameter Set */
    H264_NALU_TYPE_PPS           = 8,   /* Picture Parameter Set */
    H264_NALU_TYPE_AUD           = 9,   /* Access Unit Delimiter */
    H264_NALU_TYPE_EOS           = 10,  /* End of Sequence */
    H264_NALU_TYPE_EOB           = 11,  /* End of Bitstream */
    H264_NALU_TYPE_FD            = 12,  /* Filler Data */
    H264_NALU_TYPE_SPS_EXT       = 13,  /* Sequence Parameter Set Extension */
    H264_NALU_TYPE_PREFIX        = 14,  /* Prefix NAL unit */
    H264_NALU_TYPE_SUBSET_SPS    = 15,  /* Subset Sequence Parameter Set */
    H264_NALU_TYPE_RSV_NVCL16    = 16,  /* Reserved */
    H264_NALU_TYPE_RSV_NVCL17    = 17,  /* Reserved */
    H264_NALU_TYPE_RSV_NVCL18    = 18,  /* Reserved */
    H264_NALU_TYPE_SLICE_AUX     = 19,  /* Coded slice of an auxiliary coded picture without partitioning */
    H264_NALU_TYPE_SLICE_EXT     = 20,  /* Coded slice extension */
    H264_NALU_TYPE_SLICE_EXT_DVC = 21,  /* Coded slice extension for depth view components */
    H264_NALU_TYPE_RSV22         = 22,  /* Reserved */
    H264_NALU_TYPE_RSV23         = 23,  /* Reserved */
    H264_NALU_TYPE_UNSPECIFIED24 = 24,  /* Unspecified */
    H264_NALU_TYPE_UNSPECIFIED31 = 31,  /* Unspecified */
};

struct lsmash_h264_parameter_sets_tag
{
    /* Each list contains entries as isom_dcr_ps_entry_t. */
    lsmash_entry_list_t sps_list   [1];
    lsmash_entry_list_t pps_list   [1];
    lsmash_entry_list_t spsext_list[1];
};

typedef struct
{
    unsigned forbidden_zero_bit : 1;
    unsigned nal_ref_idc        : 2;
    unsigned nal_unit_type      : 5;
    uint8_t  length;
} h264_nalu_header_t;

typedef struct
{
    uint8_t present;
    uint8_t CpbDpbDelaysPresentFlag;
    uint8_t cpb_removal_delay_length;
    uint8_t dpb_output_delay_length;
} h264_hrd_t;

typedef struct
{
    uint16_t sar_width;
    uint16_t sar_height;
    uint8_t  video_full_range_flag;
    uint8_t  colour_primaries;
    uint8_t  transfer_characteristics;
    uint8_t  matrix_coefficients;
    uint32_t num_units_in_tick;
    uint32_t time_scale;
    uint8_t  fixed_frame_rate_flag;
    uint8_t  pic_struct_present_flag;
    h264_hrd_t hrd;
} h264_vui_t;

typedef struct
{
    uint8_t  present;
    uint8_t  profile_idc;
    uint8_t  constraint_set_flags;
    uint8_t  level_idc;
    uint8_t  seq_parameter_set_id;
    uint8_t  chroma_format_idc;
    uint8_t  separate_colour_plane_flag;
    uint8_t  ChromaArrayType;
    uint8_t  bit_depth_luma_minus8;
    uint8_t  bit_depth_chroma_minus8;
    uint8_t  log2_max_frame_num;
    uint8_t  pic_order_cnt_type;
    uint8_t  delta_pic_order_always_zero_flag;
    uint8_t  num_ref_frames_in_pic_order_cnt_cycle;
    uint8_t  frame_mbs_only_flag;
    int32_t  offset_for_non_ref_pic;
    int32_t  offset_for_top_to_bottom_field;
    int32_t  offset_for_ref_frame[255];
    int64_t  ExpectedDeltaPerPicOrderCntCycle;
    uint32_t max_num_ref_frames;
    uint32_t MaxFrameNum;
    uint32_t log2_max_pic_order_cnt_lsb;
    uint32_t MaxPicOrderCntLsb;
    uint32_t PicSizeInMapUnits;
    uint32_t cropped_width;
    uint32_t cropped_height;
    h264_vui_t vui;
} h264_sps_t;

typedef struct
{
    uint8_t  present;
    uint8_t  pic_parameter_set_id;
    uint8_t  seq_parameter_set_id;
    uint8_t  entropy_coding_mode_flag;
    uint8_t  bottom_field_pic_order_in_frame_present_flag;
    uint8_t  num_slice_groups_minus1;
    uint8_t  slice_group_map_type;
    uint8_t  num_ref_idx_l0_default_active_minus1;
    uint8_t  num_ref_idx_l1_default_active_minus1;
    uint8_t  weighted_pred_flag;
    uint8_t  weighted_bipred_idc;
    uint8_t  deblocking_filter_control_present_flag;
    uint8_t  redundant_pic_cnt_present_flag;
    uint32_t SliceGroupChangeRate;
} h264_pps_t;

typedef struct
{
    uint8_t present;
    uint8_t pic_struct;
} h264_pic_timing_t;

typedef struct
{
    uint8_t  present;
    uint8_t  random_accessible;
    uint8_t  broken_link_flag;
    uint32_t recovery_frame_cnt;
} h264_recovery_point_t;

typedef struct
{
    h264_pic_timing_t     pic_timing;
    h264_recovery_point_t recovery_point;
} h264_sei_t;

typedef struct
{
    uint8_t  present;
    uint8_t  slice_id;  /* only for slice data partition */
    uint8_t  type;
    uint8_t  pic_order_cnt_type;
    uint8_t  nal_ref_idc;
    uint8_t  IdrPicFlag;
    uint8_t  seq_parameter_set_id;
    uint8_t  pic_parameter_set_id;
    uint8_t  field_pic_flag;
    uint8_t  bottom_field_flag;
    uint8_t  has_mmco5;
    uint8_t  has_redundancy;
    uint16_t idr_pic_id;
    uint32_t frame_num;
    int32_t  pic_order_cnt_lsb;
    int32_t  delta_pic_order_cnt_bottom;
    int32_t  delta_pic_order_cnt[2];
} h264_slice_info_t;

typedef enum
{
    H264_PICTURE_TYPE_IDR         = 0,
    H264_PICTURE_TYPE_I           = 1,
    H264_PICTURE_TYPE_I_P         = 2,
    H264_PICTURE_TYPE_I_P_B       = 3,
    H264_PICTURE_TYPE_SI          = 4,
    H264_PICTURE_TYPE_SI_SP       = 5,
    H264_PICTURE_TYPE_I_SI        = 6,
    H264_PICTURE_TYPE_I_SI_P_SP   = 7,
    H264_PICTURE_TYPE_I_SI_P_SP_B = 8,
    H264_PICTURE_TYPE_NONE        = 9,
} h264_picture_type;

typedef struct
{
    h264_picture_type type;
    uint8_t           idr;
    uint8_t           random_accessible;
    uint8_t           independent;
    uint8_t           disposable;   /* 1: nal_ref_idc == 0, 0: otherwise */
    uint8_t           has_redundancy;
    uint8_t           has_primary;
    uint8_t           pic_parameter_set_id;
    uint8_t           field_pic_flag;
    uint8_t           bottom_field_flag;
    uint8_t           delta;
    uint8_t           broken_link_flag;
    /* POC */
    uint8_t           has_mmco5;
    uint8_t           ref_pic_has_mmco5;
    uint8_t           ref_pic_bottom_field_flag;
    int32_t           ref_pic_TopFieldOrderCnt;
    int32_t           ref_pic_PicOrderCntMsb;
    int32_t           ref_pic_PicOrderCntLsb;
    int32_t           pic_order_cnt_lsb;
    int32_t           delta_pic_order_cnt_bottom;
    int32_t           delta_pic_order_cnt[2];
    int32_t           PicOrderCnt;
    uint32_t          FrameNumOffset;
    /* */
    uint32_t          recovery_frame_cnt;
    uint32_t          frame_num;
} h264_picture_info_t;

typedef struct
{
    uint8_t            *data;
    uint8_t            *incomplete_data;
    uint32_t            length;
    uint32_t            incomplete_length;
    uint32_t            number;
    h264_picture_info_t picture;
} h264_access_unit_t;

typedef struct h264_info_tag h264_info_t;

typedef struct
{
    lsmash_multiple_buffers_t *bank;
    uint8_t                   *rbsp;
} h264_stream_buffer_t;

struct h264_info_tag
{
    lsmash_h264_specific_parameters_t avcC_param;
    lsmash_h264_specific_parameters_t avcC_param_next;
    lsmash_entry_list_t  sps_list  [1]; /* contains entries as h264_sps_t */
    lsmash_entry_list_t  pps_list  [1]; /* contains entries as h264_pps_t */
    lsmash_entry_list_t  slice_list[1]; /* for slice data partition */
    h264_sps_t           sps;           /* active SPS */
    h264_pps_t           pps;           /* active PPS */
    h264_sei_t           sei;           /* active SEI */
    h264_slice_info_t    slice;         /* active slice */
    h264_access_unit_t   au;
    uint8_t              prev_nalu_type;
    uint8_t              avcC_pending;
    lsmash_bits_t       *bits;
    h264_stream_buffer_t buffer;
};

int h264_setup_parser
(
    h264_info_t *info,
    int          parse_only
);

void h264_cleanup_parser
(
    h264_info_t *info
);

uint64_t h264_find_next_start_code
(
    lsmash_bs_t        *bs,
    h264_nalu_header_t *nuh,
    uint64_t           *start_code_length,
    uint64_t           *trailing_zero_bytes
);

int h264_calculate_poc
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_picture_info_t *prev_picture
);

void h264_update_picture_info_for_slice
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_slice_info_t   *slice
);

void h264_update_picture_info
(
    h264_info_t         *info,
    h264_picture_info_t *picture,
    h264_slice_info_t   *slice,
    h264_sei_t          *sei
);

int h264_find_au_delimit_by_slice_info
(
    h264_slice_info_t *slice,
    h264_slice_info_t *prev_slice
);

int h264_find_au_delimit_by_nalu_type
(
    uint8_t nalu_type,
    uint8_t prev_nalu_type
);

int h264_supplement_buffer
(
    h264_stream_buffer_t *buffer,
    h264_access_unit_t   *au,
    uint32_t              size
);

int h264_parse_sps
(
    h264_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
);

int h264_parse_pps
(
    h264_info_t *info,
    uint8_t     *rbsp_buffer,
    uint8_t     *ebsp,
    uint64_t     ebsp_size
);

int h264_parse_sei
(
    lsmash_bits_t *bits,
    h264_sps_t    *sps,
    h264_sei_t    *sei,
    uint8_t       *rbsp_buffer,
    uint8_t       *ebsp,
    uint64_t       ebsp_size
);

int h264_parse_slice
(
    h264_info_t        *info,
    h264_nalu_header_t *nuh,
    uint8_t            *rbsp_buffer,
    uint8_t            *ebsp,
    uint64_t            ebsp_size
);

int h264_try_to_append_parameter_set
(
    h264_info_t                   *info,
    lsmash_h264_parameter_set_type ps_type,
    void                          *ps_data,
    uint32_t                       ps_length
);

int h264_move_pending_avcC_param
(
    h264_info_t *info
);

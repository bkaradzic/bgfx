/*****************************************************************************
 * description.c
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

#include "common/internal.h" /* must be placed first */

#include <stdlib.h>
#include <string.h>

#include "core/box.h"

#include "a52.h"
#include "mp4a.h"
#include "mp4sys.h"
#include "description.h"

typedef isom_wave_t lsmash_qt_decoder_parameters_t;

static void global_destruct_specific_data( void *data )
{
    if( !data )
        return;
    lsmash_codec_global_header_t *global = (lsmash_codec_global_header_t *)data;
    lsmash_free( global->header_data );
    lsmash_free( global );
}

static int isom_is_qt_video( lsmash_codec_type_t type )
{
    return lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_2VUY_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_APCH_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_APCN_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_APCS_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_APCO_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_AP4H_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_AP4X_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_CFHD_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_CIVD_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVC_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVCP_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVPP_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DV5N_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DV5P_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVH2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVH3_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVH5_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVH6_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVHP_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVHQ_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DV10_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVOO_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVOR_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVTV_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_DVVT_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_FLIC_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_GIF_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_H261_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_H263_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_HD10_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_JPEG_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_M105_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_MJPA_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_MJPB_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_PNG_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_PNTG_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_RAW_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_RLE_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_RPZA_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SHR0_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SHR1_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SHR2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SHR3_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SHR4_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SVQ1_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_SVQ3_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_TGA_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_TIFF_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULRA_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULRG_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULY2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULY0_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULH2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_ULH0_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_UQY2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_V210_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_V216_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_V308_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_V408_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_V410_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_YUV2_VIDEO )
        || lsmash_check_codec_type_identical( type, QT_CODEC_TYPE_WRLE_VIDEO );
}

static int isom_is_nalff( lsmash_codec_type_t type )
{
    return lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_AVC1_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_AVC2_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_AVC3_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_AVC4_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_AVCP_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_HVC1_VIDEO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_HEV1_VIDEO );
}

static int isom_is_dts_audio( lsmash_codec_type_t type )
{
    return lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSC_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSE_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSH_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSL_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSX_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSEL_AUDIO )
        || lsmash_check_codec_type_identical( type, ISOM_CODEC_TYPE_DTSDL_AUDIO );
}

int lsmash_convert_crop_into_clap( lsmash_crop_t crop, uint32_t width, uint32_t height, lsmash_clap_t *clap )
{
    if( !clap || crop.top.d == 0 || crop.bottom.d == 0 || crop.left.d == 0 ||  crop.right.d == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    uint64_t vertical_crop_lcm   = lsmash_get_lcm( crop.top.d,  crop.bottom.d );
    uint64_t horizontal_crop_lcm = lsmash_get_lcm( crop.left.d, crop.right.d  );
    lsmash_rational_u64_t clap_height;
    lsmash_rational_u64_t clap_width;
    lsmash_rational_s64_t clap_horizontal_offset;
    lsmash_rational_s64_t clap_vertical_offset;
    clap_height.d            = vertical_crop_lcm;
    clap_width.d             = horizontal_crop_lcm;
    clap_horizontal_offset.d = 2 * vertical_crop_lcm;
    clap_vertical_offset.d   = 2 * horizontal_crop_lcm;
    clap_height.n = height * vertical_crop_lcm
                  - (crop.top.n * (vertical_crop_lcm / crop.top.d) + crop.bottom.n * (vertical_crop_lcm / crop.bottom.d));
    clap_width.n  = width * horizontal_crop_lcm
                  - (crop.left.n * (horizontal_crop_lcm / crop.left.d) + crop.right.n * (horizontal_crop_lcm / crop.right.d));
    clap_horizontal_offset.n = (int64_t)(crop.left.n * (horizontal_crop_lcm / crop.left.d))
                             - crop.right.n * (horizontal_crop_lcm / crop.right.d);
    clap_vertical_offset.n   = (int64_t)(crop.top.n * (vertical_crop_lcm / crop.top.d))
                             - crop.bottom.n * (vertical_crop_lcm / crop.bottom.d);
    lsmash_reduce_fraction( &clap_height.n, &clap_height.d );
    lsmash_reduce_fraction( &clap_width.n,  &clap_width.d  );
    lsmash_reduce_fraction_su( &clap_vertical_offset.n,   &clap_vertical_offset.d   );
    lsmash_reduce_fraction_su( &clap_horizontal_offset.n, &clap_horizontal_offset.d );
    clap->height            = (lsmash_rational_u32_t){ clap_height.n,            clap_height.d            };
    clap->width             = (lsmash_rational_u32_t){ clap_width.n,             clap_width.d             };
    clap->vertical_offset   = (lsmash_rational_s32_t){ clap_vertical_offset.n,   clap_vertical_offset.d   };
    clap->horizontal_offset = (lsmash_rational_s32_t){ clap_horizontal_offset.n, clap_horizontal_offset.d };
    return 0;
}

int lsmash_convert_clap_into_crop( lsmash_clap_t clap, uint32_t width, uint32_t height, lsmash_crop_t *crop )
{
    if( !crop || clap.height.d == 0 || clap.vertical_offset.d == 0 || clap.width.d == 0 || clap.horizontal_offset.d == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    uint64_t clap_vertical_lcm   = lsmash_get_lcm( clap.height.d, clap.vertical_offset.d   );
    uint64_t clap_horizontal_lcm = lsmash_get_lcm( clap.width.d,  clap.horizontal_offset.d );
    lsmash_rational_u64_t crop_top;
    lsmash_rational_u64_t crop_bottom;
    lsmash_rational_u64_t crop_left;
    lsmash_rational_u64_t crop_right;
    crop_top.d    = 2 * clap_vertical_lcm;
    crop_bottom.d = 2 * clap_vertical_lcm;
    crop_left.d   = 2 * clap_horizontal_lcm;
    crop_right.d  = 2 * clap_horizontal_lcm;
    crop_top.n    = (height * crop_top.d - clap.height.n * (crop_top.d / clap.height.d)) / 2
                  + clap.vertical_offset.n * (crop_top.d / clap.vertical_offset.d);
    crop_bottom.n = (height * crop_bottom.d - clap.height.n * (crop_bottom.d / clap.height.d)) / 2
                  - clap.vertical_offset.n * (crop_bottom.d / clap.vertical_offset.d);
    crop_left.n   = (width * crop_left.d - clap.width.n * (crop_left.d / clap.width.d)) / 2
                  + clap.horizontal_offset.n * (crop_left.d / clap.horizontal_offset.d);
    crop_right.n  = (width * crop_right.d - clap.width.n * (crop_right.d / clap.width.d)) / 2
                  - clap.horizontal_offset.n * (crop_right.d / clap.horizontal_offset.d);
    lsmash_reduce_fraction( &crop_top.n,    &crop_top.d    );
    lsmash_reduce_fraction( &crop_bottom.n, &crop_bottom.d );
    lsmash_reduce_fraction( &crop_left.n,   &crop_left.d   );
    lsmash_reduce_fraction( &crop_right.n,  &crop_right.d  );
    crop->top    = (lsmash_rational_u32_t){ crop_top.n,    crop_top.d    };
    crop->bottom = (lsmash_rational_u32_t){ crop_bottom.n, crop_bottom.d };
    crop->left   = (lsmash_rational_u32_t){ crop_left.n,   crop_left.d   };
    crop->right  = (lsmash_rational_u32_t){ crop_right.n,  crop_right.d  };
    return 0;
}

static void isom_destruct_nothing( void *data )
{
    /* Do nothing. */;
}

static int isom_initialize_structured_codec_specific_data( lsmash_codec_specific_t *specific )
{
    extern void mp4sys_destruct_decoder_config( void * );
    extern void h264_destruct_specific_data( void * );
    extern void hevc_destruct_specific_data( void * );
    extern void vc1_destruct_specific_data( void * );
    extern void dts_destruct_specific_data( void * );
    switch( specific->type )
    {
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG :
            specific->size     = sizeof(lsmash_mp4sys_decoder_parameters_t);
            specific->destruct = mp4sys_destruct_decoder_config;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264 :
            specific->size     = sizeof(lsmash_h264_specific_parameters_t);
            specific->destruct = h264_destruct_specific_data;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC :
            specific->size     = sizeof(lsmash_hevc_specific_parameters_t);
            specific->destruct = hevc_destruct_specific_data;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1 :
            specific->size     = sizeof(lsmash_vc1_specific_parameters_t);
            specific->destruct = vc1_destruct_specific_data;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 :
            specific->size     = sizeof(lsmash_ac3_specific_parameters_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 :
            specific->size     = sizeof(lsmash_eac3_specific_parameters_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS :
            specific->size     = sizeof(lsmash_dts_specific_parameters_t);
            specific->destruct = dts_destruct_specific_data;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC :
            specific->size     = sizeof(lsmash_alac_specific_parameters_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_SAMPLE_SCALE :
            specific->size     = sizeof(lsmash_isom_sample_scale_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264_BITRATE :
            specific->size     = sizeof(lsmash_h264_bitrate_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON :
            specific->size     = sizeof(lsmash_qt_video_common_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON :
            specific->size     = sizeof(lsmash_qt_audio_common_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS :
            specific->size     = sizeof(lsmash_qt_audio_format_specific_flags_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
            specific->size     = sizeof(lsmash_codec_global_header_t);
            specific->destruct = global_destruct_specific_data;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO :
            specific->size     = sizeof(lsmash_qt_field_info_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_PIXEL_FORMAT :
            specific->size     = sizeof(lsmash_qt_pixel_format_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS :
            specific->size     = sizeof(lsmash_qt_significant_bits_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT :
            specific->size     = sizeof(lsmash_qt_audio_channel_layout_t);
            specific->destruct = lsmash_free;
            break;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_RTP_HINT_COMMON:
            specific->size     = sizeof(lsmash_isom_rtp_reception_hint_t);
            specific->destruct = lsmash_free;
            break;
        default :
            specific->size     = 0;
            specific->destruct = isom_destruct_nothing;
            return 0;
    }
    specific->data.structured = lsmash_malloc_zero( specific->size );
    if( !specific->data.structured )
    {
        specific->size     = 0;
        specific->destruct = NULL;
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static inline int isom_initialize_codec_specific_data( lsmash_codec_specific_t *specific,
                                                       lsmash_codec_specific_data_type type,
                                                       lsmash_codec_specific_format format )
{
    specific->type   = type;
    specific->format = format;
    if( format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
    {
        int err = isom_initialize_structured_codec_specific_data( specific );
        if( err < 0 )
            return err;
    }
    else
    {
        specific->data.unstructured = NULL;
        specific->size              = 0;
        specific->destruct          = (lsmash_codec_specific_destructor_t)lsmash_free;
    }
    return 0;
}

void lsmash_destroy_codec_specific_data( lsmash_codec_specific_t *specific )
{
    if( !specific )
        return;
    if( specific->destruct )
    {
        if( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
        {
            if( specific->data.structured )
                specific->destruct( specific->data.structured );
        }
        else
        {
            if( specific->data.unstructured )
                specific->destruct( specific->data.unstructured );
        }
    }
    lsmash_free( specific );
}

lsmash_codec_specific_t *lsmash_create_codec_specific_data( lsmash_codec_specific_data_type type, lsmash_codec_specific_format format )
{
    lsmash_codec_specific_t *specific = lsmash_malloc( sizeof(lsmash_codec_specific_t) );
    if( !specific )
        return NULL;
    if( isom_initialize_codec_specific_data( specific, type, format ) < 0 )
    {
        lsmash_destroy_codec_specific_data( specific );
        return NULL;
    }
    return specific;
}

static int isom_duplicate_structured_specific_data( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    extern int mp4sys_copy_decoder_config( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
    extern int h264_copy_codec_specific( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
    extern int hevc_copy_codec_specific( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
    extern int vc1_copy_codec_specific( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
    extern int dts_copy_codec_specific( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
    void *src_data = src->data.structured;
    void *dst_data = dst->data.structured;
    switch( src->type )
    {
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG :
            return mp4sys_copy_decoder_config( dst, src );
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264 :
            return h264_copy_codec_specific( dst, src );
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC :
            return hevc_copy_codec_specific( dst, src );
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1 :
            return vc1_copy_codec_specific( dst, src );
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 :
            *(lsmash_ac3_specific_parameters_t *)dst_data = *(lsmash_ac3_specific_parameters_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 :
            *(lsmash_eac3_specific_parameters_t *)dst_data = *(lsmash_eac3_specific_parameters_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS :
            return dts_copy_codec_specific( dst, src );
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC :
            *(lsmash_alac_specific_parameters_t *)dst_data = *(lsmash_alac_specific_parameters_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_SAMPLE_SCALE :
            *(lsmash_isom_sample_scale_t *)dst_data = *(lsmash_isom_sample_scale_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264_BITRATE :
            *(lsmash_h264_bitrate_t *)dst_data = *(lsmash_h264_bitrate_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON :
            *(lsmash_qt_video_common_t *)dst_data = *(lsmash_qt_video_common_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON :
            *(lsmash_qt_audio_common_t *)dst_data = *(lsmash_qt_audio_common_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS :
            *(lsmash_qt_audio_format_specific_flags_t *)dst_data = *(lsmash_qt_audio_format_specific_flags_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
        {
            lsmash_codec_global_header_t *src_global = (lsmash_codec_global_header_t *)src_data;
            if( src_global->header_data && src_global->header_size )
            {
                lsmash_codec_global_header_t *dst_global = (lsmash_codec_global_header_t *)dst_data;
                dst_global->header_data = lsmash_memdup( src_global->header_data, src_global->header_size );
                if( !dst_global->header_data )
                    return LSMASH_ERR_MEMORY_ALLOC;
                dst_global->header_size = src_global->header_size;
            }
            return 0;
        }
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO :
            *(lsmash_qt_field_info_t *)dst_data = *(lsmash_qt_field_info_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_PIXEL_FORMAT :
            *(lsmash_qt_pixel_format_t *)dst_data = *(lsmash_qt_pixel_format_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS :
            *(lsmash_qt_significant_bits_t *)dst_data = *(lsmash_qt_significant_bits_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_GAMMA_LEVEL :
            *(lsmash_qt_gamma_t *)dst_data = *(lsmash_qt_gamma_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_CONTENT_LIGHT_LEVEL_INFO :
            *(lsmash_qt_content_light_level_info_t *)dst_data = *(lsmash_qt_content_light_level_info_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_MASTERING_DISPLAY_COLOR_VOLUME :
            *(lsmash_qt_mastering_display_color_volume_t *)dst_data = *(lsmash_qt_mastering_display_color_volume_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT :
            *(lsmash_qt_audio_channel_layout_t *)dst_data = *(lsmash_qt_audio_channel_layout_t *)src_data;
            return 0;
        case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_RTP_HINT_COMMON:
            *(lsmash_isom_rtp_reception_hint_t *)dst_data = *(lsmash_isom_rtp_reception_hint_t *)src_data;
            return 0;
        default :
            return LSMASH_ERR_NAMELESS;
    }
}

lsmash_codec_specific_t *isom_duplicate_codec_specific_data( lsmash_codec_specific_t *specific )
{
    if( !specific )
        return NULL;
    lsmash_codec_specific_t *dup = lsmash_create_codec_specific_data( specific->type, specific->format );
    if( !dup )
        return NULL;
    if( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
    {
        if( isom_duplicate_structured_specific_data( dup, specific ) < 0 )
        {
            lsmash_destroy_codec_specific_data( dup );
            return NULL;
        }
    }
    else
    {
        dup->data.unstructured = lsmash_memdup( specific->data.unstructured, specific->size );
        if( !dup->data.unstructured )
        {
            lsmash_destroy_codec_specific_data( dup );
            return NULL;
        }
    }
    dup->size = specific->size;
    return dup;
}

static int isom_construct_global_specific_header( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    if( src->size < ISOM_BASEBOX_COMMON_SIZE )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_codec_global_header_t *global = (lsmash_codec_global_header_t *)dst->data.structured;
    uint8_t *data = src->data.unstructured;
    uint64_t size = LSMASH_GET_BE32( data );
    data += ISOM_BASEBOX_COMMON_SIZE;
    if( size == 1 )
    {
        size = LSMASH_GET_BE64( data );
        data += 8;
    }
    if( size != src->size )
        return LSMASH_ERR_INVALID_DATA;
    global->header_size = size - ISOM_BASEBOX_COMMON_SIZE;
    if( data != src->data.unstructured + ISOM_BASEBOX_COMMON_SIZE )
        global->header_size -= 8;   /* largesize */
    if( global->header_size )
    {
        global->header_data = lsmash_memdup( data, global->header_size );
        if( !global->header_data )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_construct_audio_channel_layout( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    if( src->size < ISOM_FULLBOX_COMMON_SIZE + 12 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_qt_audio_channel_layout_t *layout = (lsmash_qt_audio_channel_layout_t *)dst->data.structured;
    uint8_t *data = src->data.unstructured;
    uint64_t size = LSMASH_GET_BE32( data );
    data += ISOM_FULLBOX_COMMON_SIZE;
    if( size == 1 )
    {
        size = LSMASH_GET_BE64( data );
        data += 8;
    }
    if( size != src->size )
        return LSMASH_ERR_INVALID_DATA;
    layout->channelLayoutTag = LSMASH_GET_BE32( &data[0] );
    layout->channelBitmap    = LSMASH_GET_BE32( &data[4] );
    return 0;
}

#if 0
static int codec_construct_qt_audio_decompression_info( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    if( src->size < ISOM_BASEBOX_COMMON_SIZE )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *data = src->data.unstructured;
    uint64_t size;
    uint32_t type;
    uint32_t offset = isom_read_box_size_and_type_from_binary_string( &data, &size, &type );
    if( size != src->size )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *end = src->data.unstructured + src->size;
    isom_wave_t *wave = isom_add_wave( isom_non_existing_audio_entry() );
    if( LSMASH_IS_NON_EXISTING_BOX( wave ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    wave->type = QT_BOX_TYPE_WAVE;
    for( uint8_t *pos = data; pos + ISOM_BASEBOX_COMMON_SIZE <= end; )
    {
        offset = isom_read_box_size_and_type_from_binary_string( &pos, &size, &type );
        switch( type )
        {
            case QT_BOX_TYPE_FRMA :
            {
                if( pos + 4 > end )
                    return LSMASH_ERR_INVALID_DATA;
                isom_frma_t *frma = isom_add_frma( wave );
                if( LSMASH_IS_NON_EXISTING_BOX( frma ) )
                    return LSMASH_ERR_NAMELESS;
                frma->data_format = LSMASH_GET_BE32( pos );
                pos += 4;
                break;
            }
            case QT_BOX_TYPE_ENDA :
            {
                if( pos + 2 > end )
                    return LSMASH_ERR_INVALID_DATA;
                isom_enda_t *enda = isom_add_enda( wave );
                if( LSMASH_IS_NON_EXISTING_BOX( enda ) )
                    return LSMASH_ERR_NAMELESS;
                enda->littleEndian = LSMASH_GET_BE16( pos );
                break;
            }
            case QT_BOX_TYPE_MP4A :
            {
                if( pos + 4 > end )
                    return LSMASH_ERR_INVALID_DATA;
                isom_mp4a_t *mp4a = isom_add_mp4a( wave );
                if( LSMASH_IS_NON_EXISTING_BOX( mp4a ) )
                    return LSMASH_ERR_NAMELESS;
                mp4a->unknown = LSMASH_GET_BE32( pos );
                pos += 4;
                break;
            }
            case QT_BOX_TYPE_TERMINATOR :
            {
                if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_terminator( wave ) ) )
                    return LSMASH_ERR_NAMELESS;
                break;
            }
            default :
            {
                isom_unknown_box_t *box = lsmash_malloc_zero( sizeof(isom_unknown_box_t) );
                if( LSMASH_IS_NON_EXISTING_BOX( box ) )
                    return LSMASH_ERR_MEMORY_ALLOC;
                isom_init_box_common( box, wave, type, isom_remove_unknown_box );
                box->unknown_size  = size - offset;
                box->unknown_field = lsmash_memdup( pos, box->unknown_size );
                if( !box->unknown_field )
                {
                    isom_remove_box_by_itself( box );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                if( lsmash_list_add_entry( &wave->extensions, box ) < 0 )
                {
                    isom_remove_unknown_box( box );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                pos += box->unknown_size;
                break;
            }
        }
    }
    return 0;
}
#endif

/* structured <-> unstructured conversion might be irreversible by CODEC
 * since structured formats we defined don't always have all contents included in unstructured data. */
lsmash_codec_specific_t *lsmash_convert_codec_specific_format( lsmash_codec_specific_t *specific, lsmash_codec_specific_format format )
{
    if( !specific || format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSPECIFIED )
        return NULL;
    if( format == specific->format )
        return isom_duplicate_codec_specific_data( specific );
    lsmash_codec_specific_t *dst = lsmash_create_codec_specific_data( specific->type, format );
    if( !dst )
        return NULL;
    if( format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED )
        /* structured -> unstructured */
        switch( specific->type )
        {
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG :
                dst->data.unstructured = lsmash_create_mp4sys_decoder_config( (lsmash_mp4sys_decoder_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264 :
                dst->data.unstructured = lsmash_create_h264_specific_info( (lsmash_h264_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC :
                dst->data.unstructured = lsmash_create_hevc_specific_info( (lsmash_hevc_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1 :
                dst->data.unstructured = lsmash_create_vc1_specific_info( (lsmash_vc1_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 :
                dst->data.unstructured = lsmash_create_ac3_specific_info( (lsmash_ac3_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 :
                dst->data.unstructured = lsmash_create_eac3_specific_info( (lsmash_eac3_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS :
                dst->data.unstructured = lsmash_create_dts_specific_info( (lsmash_dts_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC :
                dst->data.unstructured = lsmash_create_alac_specific_info( (lsmash_alac_specific_parameters_t *)specific->data.structured, &dst->size );
                if( !dst->data.unstructured )
                    goto fail;
                return dst;
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
            {
                lsmash_bs_t *bs = lsmash_bs_create();
                if( !bs )
                    goto fail;
                lsmash_codec_global_header_t *global = specific->data.structured;
                lsmash_bs_put_be32( bs, ISOM_BASEBOX_COMMON_SIZE + global->header_size );
                lsmash_bs_put_be32( bs, QT_BOX_TYPE_GLBL.fourcc );
                lsmash_bs_put_bytes( bs, global->header_size, global->header_data );
                dst->data.unstructured = lsmash_bs_export_data( bs, &dst->size );
                lsmash_bs_cleanup( bs );
                if( !dst->data.unstructured || dst->size != (ISOM_BASEBOX_COMMON_SIZE + global->header_size) )
                    goto fail;
                return dst;
            }
            default :
                break;
        }
    else if( format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
    {
        /* unstructured -> structured */
        extern int mp4sys_construct_decoder_config( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int h264_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int hevc_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int vc1_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int ac3_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int eac3_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int dts_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        extern int alac_construct_specific_parameters( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        static const struct
        {
            lsmash_codec_specific_data_type data_type;
            int (*constructor)( lsmash_codec_specific_t *, lsmash_codec_specific_t * );
        } codec_specific_format_constructor_table[] =
            {
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG,   mp4sys_construct_decoder_config },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264,         h264_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC,         hevc_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1,         vc1_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3,         ac3_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3,         eac3_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS,          dts_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC,         alac_construct_specific_parameters },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER,     isom_construct_global_specific_header },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT, isom_construct_audio_channel_layout },
                { LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN,               NULL }
            };
        int (*constructor)( lsmash_codec_specific_t *, lsmash_codec_specific_t * ) = NULL;
        for( int i = 0; codec_specific_format_constructor_table[i].constructor; i++ )
            if( specific->type == codec_specific_format_constructor_table[i].data_type )
            {
                constructor = codec_specific_format_constructor_table[i].constructor;
                break;
            }
        if( constructor && !constructor( dst, specific ) )
            return dst;
    }
fail:
    lsmash_destroy_codec_specific_data( dst );
    return NULL;
}

static inline void isom_set_default_compressorname( char *compressorname, lsmash_codec_type_t sample_type )
{
    static struct compressorname_table_tag
    {
        lsmash_codec_type_t type;
        char                name[33];
    } compressorname_table[33] = { { LSMASH_CODEC_TYPE_INITIALIZER, { '\0' } } };
    if( compressorname_table[0].name[0] == '\0' )
    {
        int i = 0;
#define ADD_COMPRESSORNAME_TABLE( type, name ) compressorname_table[i++] = (struct compressorname_table_tag){ type, name }
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_AVC1_VIDEO, "\012AVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_AVC2_VIDEO, "\012AVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_AVC3_VIDEO, "\012AVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_AVC4_VIDEO, "\012AVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_AVCP_VIDEO, "\016AVC Parameters" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_HVC1_VIDEO, "\013HEVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_HEV1_VIDEO, "\013HEVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_SVC1_VIDEO, "\012SVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_MVC1_VIDEO, "\012MVC Coding" );
        ADD_COMPRESSORNAME_TABLE( ISOM_CODEC_TYPE_MVC2_VIDEO, "\012MVC Coding" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_APCH_VIDEO,   "\023Apple ProRes 422 (HQ)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_APCN_VIDEO,   "\023Apple ProRes 422 (SD)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_APCS_VIDEO,   "\023Apple ProRes 422 (LT)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_APCO_VIDEO,   "\026Apple ProRes 422 (Proxy)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_AP4H_VIDEO,   "\019Apple ProRes 4444" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_AP4X_VIDEO,   "\022Apple ProRes 4444 XQ" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVPP_VIDEO,   "\014DVCPRO - PAL" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DV5N_VIDEO,   "\017DVCPRO50 - NTSC" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DV5P_VIDEO,   "\016DVCPRO50 - PAL" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVH2_VIDEO,   "\019DVCPRO HD 1080p25" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVH3_VIDEO,   "\019DVCPRO HD 1080p30" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVH5_VIDEO,   "\019DVCPRO HD 1080i50" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVH6_VIDEO,   "\019DVCPRO HD 1080i60" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVHP_VIDEO,   "\018DVCPRO HD 720p60" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_DVHQ_VIDEO,   "\018DVCPRO HD 720p50" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULRA_VIDEO,   "\017Ut Video (ULRA)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULRG_VIDEO,   "\017Ut Video (ULRG)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULY0_VIDEO,   "\017Ut Video (ULY0)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULY2_VIDEO,   "\017Ut Video (ULY2)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULH0_VIDEO,   "\017Ut Video (ULH0)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_ULH2_VIDEO,   "\017Ut Video (ULH2)" );
        ADD_COMPRESSORNAME_TABLE( QT_CODEC_TYPE_UQY2_VIDEO,   "\021Ut Video Pro (UQY2)" );
        ADD_COMPRESSORNAME_TABLE( LSMASH_CODEC_TYPE_UNSPECIFIED, { '\0' } );
#undef ADD_COMPRESSORNAME_TABLE
    }
    for( int i = 0; compressorname_table[i].name[0] != '\0'; i++ )
        if( lsmash_check_codec_type_identical( sample_type, compressorname_table[i].type ) )
        {
            strcpy( compressorname, compressorname_table[i].name );
            return;
        }
}

lsmash_codec_specific_t *isom_get_codec_specific( lsmash_codec_specific_list_t *opaque, lsmash_codec_specific_data_type type )
{
    for( lsmash_entry_t *entry = opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific || specific->type != type )
            continue;
        return specific;
    }
    return NULL;
}

static int isom_check_valid_summary( lsmash_summary_t *summary )
{
    if( !summary )
        return LSMASH_ERR_NAMELESS;
    isom_box_t temp_box;
    temp_box.type    = summary->sample_type;
    temp_box.manager = summary->summary_type == LSMASH_SUMMARY_TYPE_AUDIO ? LSMASH_AUDIO_DESCRIPTION: 0;
    if( isom_is_lpcm_audio( &temp_box ) )
    {
        if( isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS ) )
            return 0;
        return LSMASH_ERR_INVALID_DATA;
    }
    if( isom_is_uncompressed_ycbcr( summary->sample_type ) )
    {
        if( isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO ) )
        {
            if( !lsmash_check_codec_type_identical( summary->sample_type, QT_CODEC_TYPE_V216_VIDEO ) )
                return 0;
        }
        else
            return LSMASH_ERR_INVALID_DATA;
    }
    lsmash_codec_type_t             sample_type        = summary->sample_type;
    lsmash_codec_specific_data_type required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNSPECIFIED;
    if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC1_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC2_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC3_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC4_VIDEO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_HVC1_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_HEV1_VIDEO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_VC_1_VIDEO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1 ;
    else if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULRA_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULRG_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULY0_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULY2_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULH0_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_ULH2_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_UQY2_VIDEO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER;
    else if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_V216_VIDEO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4V_VIDEO )
          || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4A_AUDIO )
          || lsmash_check_codec_type_identical( sample_type,   QT_CODEC_TYPE_MP4A_AUDIO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AC_3_AUDIO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_EC_3_AUDIO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3;
    else if( isom_is_dts_audio( sample_type ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_ALAC_AUDIO )
          || lsmash_check_codec_type_identical( sample_type,   QT_CODEC_TYPE_ALAC_AUDIO ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC;
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_RRTP_HINT ) )
        required_data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_RTP_HINT_COMMON;
    if( required_data_type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNSPECIFIED )
        return 0;
    return isom_get_codec_specific( summary->opaque, required_data_type ) ? 0 : LSMASH_ERR_INVALID_DATA;
}

static lsmash_box_type_t isom_guess_video_codec_specific_box_type( lsmash_codec_type_t active_codec_type, lsmash_compact_box_type_t fourcc )
{
    lsmash_box_type_t box_type = LSMASH_BOX_TYPE_INITIALIZER;
    box_type.fourcc = fourcc;
#define GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( codec_type, predefined_box_type )    \
    else if( (codec_type.user.fourcc == 0                                         \
           || lsmash_check_codec_type_identical( active_codec_type, codec_type )) \
          && box_type.fourcc == predefined_box_type.fourcc )                      \
        box_type = predefined_box_type
    if( 0 );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AVC1_VIDEO,    ISOM_BOX_TYPE_AVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AVC2_VIDEO,    ISOM_BOX_TYPE_AVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AVC3_VIDEO,    ISOM_BOX_TYPE_AVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AVC4_VIDEO,    ISOM_BOX_TYPE_AVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AVCP_VIDEO,    ISOM_BOX_TYPE_AVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_HVC1_VIDEO,    ISOM_BOX_TYPE_HVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_HEV1_VIDEO,    ISOM_BOX_TYPE_HVCC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_VC_1_VIDEO,    ISOM_BOX_TYPE_DVC1 );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_MP4V_VIDEO,    ISOM_BOX_TYPE_ESDS );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED, ISOM_BOX_TYPE_BTRT );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED,   QT_BOX_TYPE_FIEL );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED,   QT_BOX_TYPE_CSPC );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED,   QT_BOX_TYPE_SGBT );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED,   QT_BOX_TYPE_GAMA );
    GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED,   QT_BOX_TYPE_GLBL );
#undef GUESS_VIDEO_CODEC_SPECIFIC_BOX_TYPE
    return box_type;
}

static int isom_setup_visual_description( isom_stsd_t *stsd, lsmash_video_summary_t *summary )
{
    if( !summary || LSMASH_IS_NON_EXISTING_BOX( stsd->parent->parent->parent->parent ) )
        return LSMASH_ERR_NAMELESS;
    int err = isom_check_valid_summary( (lsmash_summary_t *)summary );
    if( err < 0 )
        return err;
    isom_visual_entry_t *visual = isom_add_visual_description( stsd, summary->sample_type );
    if( LSMASH_IS_NON_EXISTING_BOX( visual ) )
        return LSMASH_ERR_NAMELESS;
    visual->data_reference_index = summary->data_ref_index;
    visual->version              = 0;
    visual->revision_level       = 0;
    visual->vendor               = 0;
    visual->temporalQuality      = 0;
    visual->spatialQuality       = 0;
    visual->width                = (uint16_t)summary->width;
    visual->height               = (uint16_t)summary->height;
    visual->horizresolution      = 0x00480000;
    visual->vertresolution       = 0x00480000;
    visual->dataSize             = 0;
    visual->frame_count          = 1;
    visual->depth                = isom_is_qt_video( visual->type ) || isom_is_nalff( visual->type )
                                 ? summary->depth : 0x0018;
    visual->color_table_ID       = -1;
    if( summary->compressorname[0] == '\0' )
        isom_set_default_compressorname( visual->compressorname, visual->type );
    else
    {
        memcpy( visual->compressorname, summary->compressorname, 32 );
        visual->compressorname[32] = '\0';
    }
    err = LSMASH_ERR_NAMELESS;
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific )
            goto fail;
        if( specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN
         && specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
            continue;   /* LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN + LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED is not supported. */
        switch( specific->type )
        {
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON :
            {
                if( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED )
                    continue;
                lsmash_qt_video_common_t *data = (lsmash_qt_video_common_t *)specific->data.structured;
                visual->revision_level  = data->revision_level;
                visual->vendor          = data->vendor;
                visual->temporalQuality = data->temporalQuality;
                visual->spatialQuality  = data->spatialQuality;
                visual->horizresolution = data->horizontal_resolution;
                visual->vertresolution  = data->vertical_resolution;
                visual->dataSize        = data->dataSize;
                visual->frame_count     = data->frame_count;
                visual->color_table_ID  = data->color_table_ID;
                if( data->color_table_ID == 0 )
                {
                    lsmash_qt_color_table_t *src_ct = &data->color_table;
                    uint16_t element_count = LSMASH_MIN( src_ct->size + 1, 256 );
                    isom_qt_color_array_t *dst_array = lsmash_malloc_zero( element_count * sizeof(isom_qt_color_array_t) );
                    if( !dst_array )
                    {
                        err = LSMASH_ERR_MEMORY_ALLOC;
                        goto fail;
                    }
                    isom_qt_color_table_t *dst_ct = &visual->color_table;
                    dst_ct->array = dst_array;
                    dst_ct->seed  = src_ct->seed;
                    dst_ct->flags = src_ct->flags;
                    dst_ct->size  = src_ct->size;
                    for( uint16_t i = 0; i < element_count; i++ )
                    {
                        dst_array[i].value = src_ct->array[i].unused;
                        dst_array[i].r     = src_ct->array[i].r;
                        dst_array[i].g     = src_ct->array[i].g;
                        dst_array[i].b     = src_ct->array[i].b;
                    }
                }
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_SAMPLE_SCALE :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_isom_sample_scale_t *data = (lsmash_isom_sample_scale_t *)cs->data.structured;
                isom_stsl_t *stsl = isom_add_stsl( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( stsl ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                stsl->constraint_flag  = data->constraint_flag;
                stsl->scale_method     = data->scale_method;
                stsl->display_center_x = data->display_center_x;
                stsl->display_center_y = data->display_center_y;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264_BITRATE :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_h264_bitrate_t *data = (lsmash_h264_bitrate_t *)cs->data.structured;
                isom_btrt_t *btrt = isom_add_btrt( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( btrt ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                btrt->bufferSizeDB = data->bufferSizeDB;
                btrt->maxBitrate   = data->maxBitrate;
                btrt->avgBitrate   = data->avgBitrate;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_field_info_t *data = (lsmash_qt_field_info_t *)cs->data.structured;
                isom_fiel_t *fiel = isom_add_fiel( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( fiel ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                fiel->fields = data->fields;
                fiel->detail = data->detail;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_PIXEL_FORMAT :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_pixel_format_t *data = (lsmash_qt_pixel_format_t *)cs->data.structured;
                isom_cspc_t *cspc = isom_add_cspc( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( cspc ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                cspc->pixel_format = data->pixel_format;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_significant_bits_t *data = (lsmash_qt_significant_bits_t *)cs->data.structured;
                isom_sgbt_t *sgbt = isom_add_sgbt( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( sgbt ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                sgbt->significantBits = data->significantBits;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_GAMMA_LEVEL :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_gamma_t *data = (lsmash_qt_gamma_t *)cs->data.structured;
                isom_gama_t *gama = isom_add_gama( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( gama ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                gama->level = data->level;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_CONTENT_LIGHT_LEVEL_INFO :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_content_light_level_info_t *data = (lsmash_qt_content_light_level_info_t *)cs->data.structured;
                isom_clli_t *clli = isom_add_clli( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( clli ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                clli->max_content_light_level     = data->max_content_light_level;
                clli->max_pic_average_light_level = data->max_pic_average_light_level;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_MASTERING_DISPLAY_COLOR_VOLUME :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_qt_mastering_display_color_volume_t *data = (lsmash_qt_mastering_display_color_volume_t *)cs->data.structured;
                isom_mdcv_t *mdcv = isom_add_mdcv( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( mdcv ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                mdcv->display_primaries_g_x           = data->display_primaries_g_x;
                mdcv->display_primaries_g_y           = data->display_primaries_g_y;
                mdcv->display_primaries_b_x           = data->display_primaries_b_x;
                mdcv->display_primaries_b_y           = data->display_primaries_b_y;
                mdcv->display_primaries_r_x           = data->display_primaries_r_x;
                mdcv->display_primaries_r_y           = data->display_primaries_r_y;
                mdcv->white_point_x                   = data->white_point_x;
                mdcv->white_point_y                   = data->white_point_y;
                mdcv->max_display_mastering_luminance = data->max_display_mastering_luminance;
                mdcv->min_display_mastering_luminance = data->min_display_mastering_luminance;
                lsmash_destroy_codec_specific_data( cs );
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_codec_global_header_t *data = (lsmash_codec_global_header_t *)cs->data.structured;
                isom_glbl_t *glbl = isom_add_glbl( visual );
                if( LSMASH_IS_NON_EXISTING_BOX( glbl ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                glbl->header_size = data->header_size;
                glbl->header_data = lsmash_memdup( data->header_data, data->header_size );
                lsmash_destroy_codec_specific_data( cs );
                if( !glbl->header_data )
                {
                    isom_remove_box_by_itself( glbl );
                    err = LSMASH_ERR_MEMORY_ALLOC;
                    goto fail;
                }
                break;
            }
            default :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                if( !cs )
                    goto fail;
                if( cs->size < ISOM_BASEBOX_COMMON_SIZE )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    err = LSMASH_ERR_INVALID_DATA;
                    goto fail;
                }
                uint8_t *data = cs->data.unstructured;
                lsmash_compact_box_type_t fourcc   = LSMASH_4CC( data[4], data[5], data[6], data[7] );
                lsmash_box_type_t         box_type = isom_guess_video_codec_specific_box_type( visual->type, fourcc );
                /* Append the extension. */
                err = isom_add_extension_binary( visual, box_type, LSMASH_BOX_PRECEDENCE_HM, cs->data.unstructured, cs->size );
                cs->data.unstructured = NULL;   /* Avoid freeing the binary data of the extension. */
                lsmash_destroy_codec_specific_data( cs );
                if( err < 0 )
                    goto fail;
                break;
            }
        }
    }
    isom_trak_t *trak = (isom_trak_t *)visual->parent->parent->parent->parent->parent;
    int qt_compatible = trak->file->qt_compatible;
    isom_tapt_t *tapt = trak->tapt;
    isom_stsl_t *stsl = (isom_stsl_t *)isom_get_extension_box_format( &visual->extensions, ISOM_BOX_TYPE_STSL );
    int set_aperture_modes = qt_compatible                                  /* Track Aperture Modes is only available under QuickTime file format. */
        && (LSMASH_IS_NON_EXISTING_BOX( stsl ) || stsl->scale_method == 0)  /* Sample scaling method might conflict with this feature. */
        && LSMASH_IS_EXISTING_BOX( tapt->clef )
        && LSMASH_IS_EXISTING_BOX( tapt->prof )
        && LSMASH_IS_EXISTING_BOX( tapt->enof )                             /* Check if required boxes exist. */
        && ((isom_stsd_t *)visual->parent)->list.entry_count == 1;          /* Multiple sample description might conflict with this, so in that case, disable this feature. */
    if( !set_aperture_modes )
        isom_remove_box_by_itself( trak->tapt );
    int uncompressed_ycbcr = qt_compatible && isom_is_uncompressed_ycbcr( visual->type );
    /* Set up Clean Aperture. */
    if( set_aperture_modes || uncompressed_ycbcr
     || (summary->clap.width.d && summary->clap.height.d && summary->clap.horizontal_offset.d && summary->clap.vertical_offset.d) )
    {
        isom_clap_t *clap = isom_add_clap( visual );
        if( LSMASH_IS_NON_EXISTING_BOX( clap ) )
            goto fail;
        if( summary->clap.width.d && summary->clap.height.d && summary->clap.horizontal_offset.d && summary->clap.vertical_offset.d )
        {
            clap->cleanApertureWidthN  = summary->clap.width.n;
            clap->cleanApertureWidthD  = summary->clap.width.d;
            clap->cleanApertureHeightN = summary->clap.height.n;
            clap->cleanApertureHeightD = summary->clap.height.d;
            clap->horizOffN            = summary->clap.horizontal_offset.n;
            clap->horizOffD            = summary->clap.horizontal_offset.d;
            clap->vertOffN             = summary->clap.vertical_offset.n;
            clap->vertOffD             = summary->clap.vertical_offset.d;
        }
        else
        {
            clap->cleanApertureWidthN  = summary->width;
            clap->cleanApertureWidthD  = 1;
            clap->cleanApertureHeightN = summary->height;
            clap->cleanApertureHeightD = 1;
            clap->horizOffN            = 0;
            clap->horizOffD            = 1;
            clap->vertOffN             = 0;
            clap->vertOffD             = 1;
        }
    }
    /* Set up Pixel Aspect Ratio. */
    if( set_aperture_modes || (summary->par_h && summary->par_v) )
    {
        isom_pasp_t *pasp = isom_add_pasp( visual );
        if( LSMASH_IS_NON_EXISTING_BOX( pasp ) )
            goto fail;
        pasp->hSpacing = LSMASH_MAX( summary->par_h, 1 );
        pasp->vSpacing = LSMASH_MAX( summary->par_v, 1 );
    }
    /* Set up Color Parameter. */
    if( uncompressed_ycbcr
     || summary->color.primaries_index
     || summary->color.transfer_index
     || summary->color.matrix_index
     || (trak->file->isom_compatible && summary->color.full_range) )
    {
        isom_colr_t *colr = isom_add_colr( visual );
        if( LSMASH_IS_NON_EXISTING_BOX( colr ) )
            goto fail;
        /* Set 'nclc' to parameter type, we don't support 'prof'. */
        uint16_t primaries = summary->color.primaries_index;
        uint16_t transfer  = summary->color.transfer_index;
        uint16_t matrix    = summary->color.matrix_index;
        if( qt_compatible && !trak->file->isom_compatible )
        {
            colr->manager                |= LSMASH_QTFF_BASE;
            colr->type                    = QT_BOX_TYPE_COLR;
            colr->color_parameter_type    = QT_COLOR_PARAMETER_TYPE_NCLC;
            colr->primaries_index         = (primaries == 1 || primaries == 5 || primaries == 6)
                                          ? primaries : QT_PRIMARIES_INDEX_UNSPECIFIED;
            colr->transfer_function_index = (transfer == 1 || transfer == 7)
                                          ? transfer : QT_TRANSFER_INDEX_UNSPECIFIED;
            colr->matrix_index            = (matrix == 1 || matrix == 6 || matrix == 7)
                                          ? matrix : QT_MATRIX_INDEX_UNSPECIFIED;
        }
        else
        {
            colr->type                    = ISOM_BOX_TYPE_COLR;
            colr->color_parameter_type    = ISOM_COLOR_PARAMETER_TYPE_NCLX;
            colr->primaries_index         = (primaries == 1 || (primaries >= 4 && primaries <= 7))
                                          ? primaries : ISOM_PRIMARIES_INDEX_UNSPECIFIED;
            colr->transfer_function_index = (transfer == 1 || (transfer >= 4 && transfer <= 8) || (transfer >= 11 && transfer <= 13))
                                          ? transfer : ISOM_TRANSFER_INDEX_UNSPECIFIED;
            colr->matrix_index            = (matrix == 1 || (matrix >= 4 && matrix <= 8))
                                          ? matrix : ISOM_MATRIX_INDEX_UNSPECIFIED;
            colr->full_range_flag         = summary->color.full_range;
        }
    }
    /* Set up Track Apeture Modes. */
    if( set_aperture_modes )
    {
        uint32_t width  = visual->width  << 16;
        uint32_t height = visual->height << 16;
        isom_clap_t *clap = (isom_clap_t *)isom_get_extension_box_format( &visual->extensions, ISOM_BOX_TYPE_CLAP );
        isom_pasp_t *pasp = (isom_pasp_t *)isom_get_extension_box_format( &visual->extensions, ISOM_BOX_TYPE_PASP );
        double clap_width  = ((double)clap->cleanApertureWidthN  / clap->cleanApertureWidthD)  * (1<<16);
        double clap_height = ((double)clap->cleanApertureHeightN / clap->cleanApertureHeightD) * (1<<16);
        double par = (double)pasp->hSpacing / pasp->vSpacing;
        if( par >= 1.0 )
        {
            tapt->clef->width  = clap_width * par;
            tapt->clef->height = clap_height;
            tapt->prof->width  = width * par;
            tapt->prof->height = height;
        }
        else
        {
            tapt->clef->width  = clap_width;
            tapt->clef->height = clap_height / par;
            tapt->prof->width  = width;
            tapt->prof->height = height / par;
        }
        tapt->enof->width  = width;
        tapt->enof->height = height;
    }
    return 0;
fail:
    isom_remove_box_by_itself( visual );
    return err;
}

static int isom_append_audio_es_descriptor_extension( isom_box_t *box, lsmash_audio_summary_t *summary )
{
    uint32_t esds_size = 0;
    uint8_t *esds_data = NULL;
    lsmash_codec_specific_t *specific = isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG );
    if( !specific )
        return LSMASH_ERR_NAMELESS;
    if( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED )
    {
        esds_size = specific->size;
        esds_data = lsmash_memdup( specific->data.unstructured, specific->size );
        if( !esds_data )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    else
    {
        esds_data = lsmash_create_mp4sys_decoder_config( (lsmash_mp4sys_decoder_parameters_t *)specific->data.structured, &esds_size );
        if( !esds_data )
            return LSMASH_ERR_NAMELESS;
    }
    isom_esds_t *esds = isom_add_esds( box );
    if( LSMASH_IS_NON_EXISTING_BOX( esds ) )
    {
        lsmash_free( esds_data );
        return LSMASH_ERR_NAMELESS;
    }
    lsmash_bs_t bs = { 0 };
    bs.buffer.data  = esds_data + ISOM_FULLBOX_COMMON_SIZE;
    bs.buffer.alloc = esds_size - ISOM_FULLBOX_COMMON_SIZE;
    bs.buffer.store = bs.buffer.alloc;
    esds->ES = mp4sys_get_descriptor( &bs, NULL );
    lsmash_free( esds_data );
    if( !esds->ES )
    {
        isom_remove_box_by_itself( esds );
        return LSMASH_ERR_NAMELESS;
    }
    return 0;
}

static int isom_append_channel_layout_extension( lsmash_codec_specific_t *specific, void *parent, uint32_t channels )
{
    assert( LSMASH_IS_EXISTING_BOX( (isom_box_t *)parent ) );
    if( isom_get_extension_box( &((isom_box_t *)parent)->extensions, QT_BOX_TYPE_CHAN ) )
        return 0;   /* Audio Channel Layout Box is already present. */
    lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    if( !cs )
        return LSMASH_ERR_NAMELESS;
    lsmash_qt_audio_channel_layout_t *data = (lsmash_qt_audio_channel_layout_t *)cs->data.structured;
    lsmash_channel_layout_tag channelLayoutTag = data->channelLayoutTag;
    lsmash_channel_bitmap     channelBitmap    = data->channelBitmap;
    if( channelLayoutTag == QT_CHANNEL_LAYOUT_USE_CHANNEL_DESCRIPTIONS    /* We don't support the feature of Channel Descriptions. */
     || (channelLayoutTag == QT_CHANNEL_LAYOUT_USE_CHANNEL_BITMAP && (!channelBitmap || channelBitmap > QT_CHANNEL_BIT_FULL)) )
    {
        channelLayoutTag = QT_CHANNEL_LAYOUT_UNKNOWN | channels;
        channelBitmap    = 0;
    }
    lsmash_destroy_codec_specific_data( cs );
    /* Don't create Audio Channel Layout Box if the channel layout is unknown. */
    if( (channelLayoutTag ^ QT_CHANNEL_LAYOUT_UNKNOWN) >> 16 )
    {
        isom_chan_t *chan = isom_add_chan( parent );
        if( LSMASH_IS_NON_EXISTING_BOX( chan ) )
            return LSMASH_ERR_NAMELESS;
        chan->channelLayoutTag          = channelLayoutTag;
        chan->channelBitmap             = channelBitmap;
        chan->numberChannelDescriptions = 0;
        chan->channelDescriptions       = NULL;
    }
    return 0;
}

static int isom_set_qtff_mp4a_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    isom_wave_t       *wave;
    isom_frma_t       *frma;
    isom_mp4a_t       *mp4a;
    isom_terminator_t *terminator;
    if( (wave       = isom_add_wave( audio ),      LSMASH_IS_NON_EXISTING_BOX( wave ))
     || (frma       = isom_add_frma( wave ),       LSMASH_IS_NON_EXISTING_BOX( frma ))
     || (mp4a       = isom_add_mp4a( wave ),       LSMASH_IS_NON_EXISTING_BOX( mp4a ))
     || (terminator = isom_add_terminator( wave ), LSMASH_IS_NON_EXISTING_BOX( terminator )) )
    {
        lsmash_list_remove_entry_tail( &audio->extensions );
        return LSMASH_ERR_NAMELESS;
    }
    frma->data_format = audio->type.fourcc;
    /* Add ES Descriptor Box. */
    int err = isom_append_audio_es_descriptor_extension( (isom_box_t *)wave, summary );
    if( err < 0 )
        return err;
    /* */
    audio->type                 = QT_CODEC_TYPE_MP4A_AUDIO;
    audio->version              = (summary->channels > 2 || summary->frequency > UINT16_MAX) ? 2 : 1;
    audio->channelcount         = audio->version == 2 ? 3 : LSMASH_MIN( summary->channels, 2 );
    audio->samplesize           = 16;
    audio->compression_ID       = QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION;
    audio->packet_size          = 0;
    if( audio->version == 1 )
    {
        audio->samplerate       = summary->frequency << 16;
        audio->samplesPerPacket = summary->samples_in_frame;
        audio->bytesPerPacket   = 1;    /* Apparently, this field is set to 1. */
        audio->bytesPerFrame    = audio->bytesPerPacket * summary->channels;
        audio->bytesPerSample   = 2;
    }
    else    /* audio->version == 2 */
    {
        audio->samplerate                    = 0x00010000;
        audio->sizeOfStructOnly              = 72;
        audio->audioSampleRate               = (union {double d; uint64_t i;}){summary->frequency}.i;
        audio->numAudioChannels              = summary->channels;
        audio->always7F000000                = 0x7F000000;
        audio->constBitsPerChannel           = 0;   /* compressed audio */
        audio->formatSpecificFlags           = 0;
        audio->constBytesPerAudioPacket      = 0;   /* variable */
        audio->constLPCMFramesPerAudioPacket = summary->samples_in_frame;
    }
    return 0;
}

static int isom_set_isom_mp4a_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    if( summary->summary_type != LSMASH_SUMMARY_TYPE_AUDIO )
        return LSMASH_ERR_NAMELESS;
    /* Check objectTypeIndication. */
    lsmash_mp4sys_object_type_indication objectTypeIndication = lsmash_mp4sys_get_object_type_indication( (lsmash_summary_t *)summary );
    switch( objectTypeIndication )
    {
        case MP4SYS_OBJECT_TYPE_Audio_ISO_14496_3:
        case MP4SYS_OBJECT_TYPE_Audio_ISO_13818_7_Main_Profile:
        case MP4SYS_OBJECT_TYPE_Audio_ISO_13818_7_LC_Profile:
        case MP4SYS_OBJECT_TYPE_Audio_ISO_13818_7_SSR_Profile:
        case MP4SYS_OBJECT_TYPE_Audio_ISO_13818_3:      /* Legacy Interface */
        case MP4SYS_OBJECT_TYPE_Audio_ISO_11172_3:      /* Legacy Interface */
            break;
        default:
            return LSMASH_ERR_NAMELESS;
    }
    /* Add ES Descriptor Box. */
    int err = isom_append_audio_es_descriptor_extension( (isom_box_t *)audio, summary );
    if( err < 0 )
        return err;
    /* In pure mp4 file, these "template" fields shall be default values according to the spec.
       But not pure - hybrid with other spec - mp4 file can take other values.
       Which is to say, these template values shall be ignored in terms of mp4, except some object_type_indications.
       see 14496-14, "Template fields used". */
    audio->type           = ISOM_CODEC_TYPE_MP4A_AUDIO;
    audio->version        = 0;
    audio->revision_level = 0;
    audio->vendor         = 0;
    audio->channelcount   = 2;
    audio->samplesize     = 16;
    audio->compression_ID = 0;
    audio->packet_size    = 0;
    /* WARNING: This field cannot retain frequency above 65535Hz.
       This is not "FIXME", I just honestly implemented what the spec says.
       BTW, who ever expects sampling frequency takes fixed-point decimal??? */
    audio->samplerate     = summary->frequency <= UINT16_MAX ? summary->frequency << 16 : 0;
    return 0;
}

static int isom_set_qtff_lpcm_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    lsmash_qt_audio_format_specific_flags_t *lpcm = NULL;
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific )
            continue;
        if( specific->type   == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS
         && specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
        {
            lpcm = (lsmash_qt_audio_format_specific_flags_t *)specific->data.structured;
            break;
        }
    }
    if( !lpcm )
        return LSMASH_ERR_NAMELESS;
    audio->manager |= LSMASH_QTFF_BASE;
    lsmash_codec_type_t sample_type = audio->type;
    /* Convert the sample type into 'lpcm' if the description doesn't match the format or version = 2 fields are needed. */
    if( (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_RAW_AUDIO )
     && (summary->sample_size != 8 || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_FL32_AUDIO )
     && (summary->sample_size != 32 || !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_FL64_AUDIO )
     && (summary->sample_size != 64 || !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_IN24_AUDIO )
     && (summary->sample_size != 24 || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_IN32_AUDIO )
     && (summary->sample_size != 32 || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_23NI_AUDIO )
     && (summary->sample_size != 32 || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT) || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_SOWT_AUDIO )
     && (summary->sample_size != 16 || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT) || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TWOS_AUDIO )
     && ((summary->sample_size != 16 && summary->sample_size != 8) || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT) || !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_NONE_AUDIO )
     && ((summary->sample_size != 16 && summary->sample_size != 8) || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT) || !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN)))
     || (lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_NOT_SPECIFIED )
     && ((summary->sample_size != 16 && summary->sample_size != 8) || (lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT) || !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN)))
     || (summary->channels > 2 || summary->frequency > UINT16_MAX || summary->sample_size % 8) )
    {
        audio->type    = QT_CODEC_TYPE_LPCM_AUDIO;
        audio->version = 2;
    }
    else if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_LPCM_AUDIO ) )
        audio->version = 2;
    else if( summary->sample_size > 16
     || (!lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_RAW_AUDIO )
      && !lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TWOS_AUDIO )
      && !lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_NONE_AUDIO )
      && !lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_NOT_SPECIFIED )) )
        audio->version = 1;
    /* Set up constBytesPerAudioPacket field.
     * We use constBytesPerAudioPacket as the actual size of LPCM audio frame even when version is not 2. */
    audio->constBytesPerAudioPacket = (summary->sample_size * summary->channels) / 8;
    /* Set up other fields in this description by its version. */
    if( audio->version == 2 )
    {
        audio->channelcount                  = 3;
        audio->samplesize                    = 16;
        audio->compression_ID                = -2;
        audio->samplerate                    = 0x00010000;
        audio->sizeOfStructOnly              = 72;
        audio->audioSampleRate               = (union {double d; uint64_t i;}){summary->frequency}.i;
        audio->numAudioChannels              = summary->channels;
        audio->always7F000000                = 0x7F000000;
        audio->constBitsPerChannel           = summary->sample_size;
        audio->constLPCMFramesPerAudioPacket = 1;
        audio->formatSpecificFlags           = lpcm->format_flags;
        if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TWOS_AUDIO ) && summary->sample_size != 8 )
            audio->formatSpecificFlags |= QT_LPCM_FORMAT_FLAG_BIG_ENDIAN;
        if( lpcm->format_flags & QT_LPCM_FORMAT_FLAG_FLOAT )
            audio->formatSpecificFlags &= ~QT_LPCM_FORMAT_FLAG_SIGNED_INTEGER;
        if( lpcm->format_flags & QT_LPCM_FORMAT_FLAG_PACKED )
            audio->formatSpecificFlags &= ~QT_LPCM_FORMAT_FLAG_ALIGNED_HIGH;
    }
    else if( audio->version == 1 )
    {
        audio->channelcount = summary->channels;
        audio->samplesize   = 16;
        /* Audio formats other than 'raw ' and 'twos' are treated as compressed audio. */
        if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_RAW_AUDIO )
         || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TWOS_AUDIO ) )
            audio->compression_ID = QT_AUDIO_COMPRESSION_ID_NOT_COMPRESSED;
        else
            audio->compression_ID = QT_AUDIO_COMPRESSION_ID_FIXED_COMPRESSION;
        audio->samplerate       = summary->frequency << 16;
        audio->samplesPerPacket = 1;
        audio->bytesPerPacket   = summary->sample_size / 8;
        audio->bytesPerFrame    = audio->bytesPerPacket * summary->channels;    /* sample_size field in stsz box is NOT used. */
        audio->bytesPerSample   = 1 + (summary->sample_size != 8);
        if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_FL32_AUDIO )
         || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_FL64_AUDIO )
         || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_IN24_AUDIO )
         || lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_IN32_AUDIO ) )
        {
            isom_wave_t       *wave;
            isom_frma_t       *frma;
            isom_enda_t       *enda;
            isom_terminator_t *terminator;
            if( (wave       = isom_add_wave( audio ),      LSMASH_IS_NON_EXISTING_BOX( wave ))
             || (frma       = isom_add_frma( wave ),       LSMASH_IS_NON_EXISTING_BOX( frma ))
             || (enda       = isom_add_enda( wave ),       LSMASH_IS_NON_EXISTING_BOX( enda ))
             || (terminator = isom_add_terminator( wave ), LSMASH_IS_NON_EXISTING_BOX( terminator )) )
            {
                lsmash_list_remove_entry_tail( &audio->extensions );
                return LSMASH_ERR_NAMELESS;
            }
            frma->data_format  = sample_type.fourcc;
            enda->littleEndian = !(lpcm->format_flags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN);
        }
    }
    else    /* audio->version == 0 */
    {
        audio->channelcount   = summary->channels;
        audio->samplesize     = summary->sample_size;
        audio->compression_ID = QT_AUDIO_COMPRESSION_ID_NOT_COMPRESSED;
        audio->samplerate     = summary->frequency << 16;
    }
    return 0;
}

static int isom_set_isom_dts_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    audio->version        = 0;
    audio->revision_level = 0;
    audio->vendor         = 0;
    audio->channelcount   = summary->channels;
    audio->samplesize     = 16;
    audio->compression_ID = 0;
    audio->packet_size    = 0;
    switch( summary->frequency )
    {
        case 12000 :    /* Invalid? (No reference in the spec) */
        case 24000 :
        case 48000 :
        case 96000 :
        case 192000 :
        case 384000 :   /* Invalid? (No reference in the spec) */
            audio->samplerate = 48000 << 16;
            break;
        case 22050 :
        case 44100 :
        case 88200 :
        case 176400 :
        case 352800 :   /* Invalid? (No reference in the spec) */
            audio->samplerate = 44100 << 16;
            break;
        case 8000 :     /* Invalid? (No reference in the spec) */
        case 16000 :
        case 32000 :
        case 64000 :
        case 128000 :
            audio->samplerate = 32000 << 16;
            break;
        default :
            audio->samplerate = 0;
            break;
    }
    return 0;
}

static int isom_set_hint_summary( isom_hint_entry_t *hint, lsmash_hint_summary_t *summary )
{
    hint->hinttrackversion         = summary->version;
    hint->highestcompatibleversion = summary->highestcompatibleversion;
    hint->maxpacketsize            = summary->maxpacketsize;
    return 0;
}

static lsmash_box_type_t isom_guess_audio_codec_specific_box_type( lsmash_codec_type_t active_codec_type, lsmash_compact_box_type_t fourcc )
{
    lsmash_box_type_t box_type = LSMASH_BOX_TYPE_INITIALIZER;
    box_type.fourcc = fourcc;
#define GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( codec_type, predefined_box_type )    \
    else if( (codec_type.user.fourcc == 0                                         \
           || lsmash_check_codec_type_identical( active_codec_type, codec_type )) \
          && box_type.fourcc == predefined_box_type.fourcc )                      \
        box_type = predefined_box_type
    if( 0 );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_AC_3_AUDIO,  ISOM_BOX_TYPE_DAC3 );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_EC_3_AUDIO,  ISOM_BOX_TYPE_DEC3 );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSC_AUDIO,  ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSE_AUDIO,  ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSH_AUDIO,  ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSL_AUDIO,  ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSX_AUDIO,  ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSEL_AUDIO, ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_DTSDL_AUDIO, ISOM_BOX_TYPE_DDTS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_ALAC_AUDIO,  ISOM_BOX_TYPE_ALAC );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( ISOM_CODEC_TYPE_MP4A_AUDIO,  ISOM_BOX_TYPE_ESDS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_ALAC_AUDIO,    QT_BOX_TYPE_ALAC );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_MP4A_AUDIO,    QT_BOX_TYPE_ESDS );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_FULLMP3_AUDIO, QT_CODEC_TYPE_MP3_AUDIO );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_ADPCM2_AUDIO,  QT_CODEC_TYPE_ADPCM2_AUDIO );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_ADPCM17_AUDIO, QT_CODEC_TYPE_ADPCM17_AUDIO );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE(   QT_CODEC_TYPE_GSM49_AUDIO,   QT_CODEC_TYPE_GSM49_AUDIO );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED, QT_BOX_TYPE_CHAN );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED, QT_BOX_TYPE_GLBL );
    GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE( LSMASH_CODEC_TYPE_UNSPECIFIED, QT_BOX_TYPE_WAVE );
#undef GUESS_AUDIO_CODEC_SPECIFIC_BOX_TYPE
    return box_type;
}

typedef struct
{
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
} wave_format_ex_t;

static lsmash_bs_t *isom_create_waveform_audio_info
(
    wave_format_ex_t *wfx,
    lsmash_box_type_t type
)
{
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return NULL;
    lsmash_bs_put_be32( bs, ISOM_BASEBOX_COMMON_SIZE + 18 + wfx->cbSize );
    lsmash_bs_put_be32( bs, type.fourcc );
    lsmash_bs_put_le16( bs, wfx->wFormatTag );
    lsmash_bs_put_le16( bs, wfx->nChannels );
    lsmash_bs_put_le32( bs, wfx->nSamplesPerSec );
    lsmash_bs_put_le32( bs, wfx->nAvgBytesPerSec );
    lsmash_bs_put_le16( bs, wfx->nBlockAlign );
    lsmash_bs_put_le16( bs, wfx->wBitsPerSample );
    lsmash_bs_put_le16( bs, wfx->cbSize );
    return bs;
}

static int isom_setup_waveform_audio_info
(
    isom_wave_t            *wave,
    isom_audio_entry_t     *audio,
    lsmash_audio_summary_t *summary,
    uint32_t                samples_per_packet,
    uint32_t                bytes_per_frame,
    uint32_t                sample_size
)
{
    wave_format_ex_t wfx;
    wfx.wFormatTag      = 0x0000;   /* WAVE_FORMAT_UNKNOWN */
    wfx.nChannels       = summary->channels;
    wfx.nSamplesPerSec  = summary->frequency;
    wfx.nAvgBytesPerSec = 0;
    wfx.nBlockAlign     = bytes_per_frame;
    wfx.wBitsPerSample  = sample_size;
    wfx.cbSize          = 0;
    lsmash_bs_t *bs = NULL;
    if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ADPCM2_AUDIO ) )
    {
        /* ADPCMWAVEFORMAT */
        wfx.wFormatTag = 0x0002;    /* WAVE_FORMAT_ADPCM */
        wfx.cbSize     = 32;
        bs = isom_create_waveform_audio_info( &wfx, audio->type );
        if( !bs )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint16_t wSamplesPerBlock = samples_per_packet; /* nBlockAlign * 2 / nChannels - 12 */
        uint16_t wNumCoef         = 7;                  /* Microsoft ADPCM uses just 7 coefficients. */
        static const struct
        {
            int16_t iCoef1;
            int16_t iCoef2;
        } aCoef[7] = { { 256, 0 }, { 512, -256 }, { 0,0 }, { 192,64 }, { 240,0 }, { 460, -208 }, { 392,-232 } };
        lsmash_bs_put_le16( bs, wSamplesPerBlock );
        lsmash_bs_put_le16( bs, wNumCoef );
        for( int i = 0; i < 7; i++ )
        {
            lsmash_bs_put_le16( bs, aCoef[i].iCoef1 );
            lsmash_bs_put_le16( bs, aCoef[i].iCoef2 );
        }
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ADPCM17_AUDIO ) )
    {
        /* IMAADPCMWAVEFORMAT */
        wfx.wFormatTag = 0x0011;    /* WAVE_FORMAT_DVI_ADPCM / WAVE_FORMAT_IMA_ADPCM */
        wfx.cbSize     = 2;
        bs = isom_create_waveform_audio_info( &wfx, audio->type );
        if( !bs )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint16_t wSamplesPerBlock = samples_per_packet;
        lsmash_bs_put_le16( bs, wSamplesPerBlock );
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_GSM49_AUDIO ) )
    {
        /* GSM610WAVEFORMAT */
        wfx.wFormatTag = 0x0031;    /* WAVE_FORMAT_GSM610 */
        wfx.cbSize     = 2;
        bs = isom_create_waveform_audio_info( &wfx, audio->type );
        if( !bs )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint16_t wSamplesPerBlock = samples_per_packet;
        lsmash_bs_put_le16( bs, wSamplesPerBlock );
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_FULLMP3_AUDIO )
          || lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_MP3_AUDIO ) )
    {
        /* MPEGLAYER3WAVEFORMAT */
        wfx.wFormatTag     = 0x0055;    /* WAVE_FORMAT_MPEGLAYER3 */
        wfx.nBlockAlign    = 1;         /* ? */
        wfx.wBitsPerSample = 0;         /* undefined */
        wfx.cbSize         = 12;
        bs = isom_create_waveform_audio_info( &wfx, audio->type );
        if( !bs )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint16_t wID             = 1;   /* MPEGLAYER3_ID_MPEG */
        uint32_t fdwFlags        = 0;   /* We don't know whether the stream is padded or not here. */
        uint16_t nBlockSize      = 0;   /* (144 * (bitrate / nSamplesPerSec) + padding) * nFramesPerBlock */
        uint16_t nFramesPerBlock = 1;   /* the number of audio frames per block */
        uint16_t nCodecDelay     = 0;   /* Encoder delay in samples is unknown. */
        lsmash_bs_put_le16( bs, wID );
        lsmash_bs_put_le32( bs, fdwFlags );
        lsmash_bs_put_le16( bs, nBlockSize );
        lsmash_bs_put_le16( bs, nFramesPerBlock );
        lsmash_bs_put_le16( bs, nCodecDelay );
    }
    if( !bs )
    {
        assert( 0 );
        return LSMASH_ERR_NAMELESS;
    }
    uint32_t wfx_size;
    uint8_t *wfx_data = lsmash_bs_export_data( bs, &wfx_size );
    lsmash_bs_cleanup( bs );
    if( !wfx_data )
        return LSMASH_ERR_NAMELESS;
    if( wfx_size != ISOM_BASEBOX_COMMON_SIZE + 18 + wfx.cbSize )
    {
        lsmash_free( wfx_data );
        return LSMASH_ERR_NAMELESS;
    }
    int err = isom_add_extension_binary( wave, audio->type, LSMASH_BOX_PRECEDENCE_HM, wfx_data, wfx_size );
    if( err < 0 )
    {
        lsmash_free( wfx_data );
        return err;
    }
    return 0;
}

static int isom_set_qtff_sound_decompression_parameters
(
    isom_audio_entry_t                   *audio,
    lsmash_audio_summary_t               *summary,
    lsmash_qt_audio_format_specific_flag *format_flags,
    uint32_t                              samples_per_packet,
    uint32_t                              bytes_per_frame,
    uint32_t                              sample_size
)
{
    /* A 'wave' extension itself shall be absent in the opaque CODEC specific info list.
     * So, create a 'wave' extension here and append it as an extension to the audio sample description. */
    isom_wave_t *wave = isom_add_wave( audio );
    if( LSMASH_IS_NON_EXISTING_BOX( wave ) )
        return LSMASH_ERR_NAMELESS;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_frma      ( wave ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_terminator( wave ) ) )
    {
        lsmash_list_remove_entry_tail( &audio->extensions );
        return LSMASH_ERR_NAMELESS;
    }
    wave->frma->data_format = audio->type.fourcc;
    /* Append extensions from the opaque CODEC specific info list to 'wave' extension. */
    int err;
    int waveform_audio_info_present  = 0;
    int requires_waveform_audio_info = isom_is_waveform_audio( audio->type );
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific )
            return LSMASH_ERR_NAMELESS;
        if( specific->type   == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN
         && specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
            continue;   /* LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN + LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED is not supported. */
        switch( specific->type )
        {
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON :
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS :
                continue;   /* These cannot be an extension for 'wave' extension. */
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT :
                /* (Legacy?) ALAC might have an Audio Channel Layout Box inside 'wave' extension. */
#if 1
                continue;
#else
                if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ALAC_AUDIO ) )
                    continue;
                if( (err = isom_append_channel_layout_extension( specific, wave, summary->channels )) < 0 )
                    return err;
                break;
#endif
            default :
            {
                assert( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED
                     || specific->type   == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_DECOMPRESSION_PARAMETERS );
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                if( !cs )
                    return LSMASH_ERR_NAMELESS;
                if( cs->size < ISOM_BASEBOX_COMMON_SIZE )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    continue;
                }
                uint8_t *box_data = cs->data.unstructured;
                uint64_t box_size = cs->size;
                lsmash_compact_box_type_t fourcc = LSMASH_4CC( box_data[4], box_data[5], box_data[6], box_data[7] );
                if( audio->version == 2 && fourcc == QT_BOX_TYPE_ENDA.fourcc )
                {
                    /* Don't append a 'enda' extension if version == 2.
                     * Endianness is indicated in QuickTime audio format specific flags. */
                    if( box_size >= ISOM_BASEBOX_COMMON_SIZE + 2 )
                    {
                        /* Override endianness indicated in format specific flags. */
                        if( box_data[9] == 1 )
                            *format_flags &= ~QT_AUDIO_FORMAT_FLAG_BIG_ENDIAN;
                        else
                            *format_flags |=  QT_AUDIO_FORMAT_FLAG_BIG_ENDIAN;
                    }
                    lsmash_destroy_codec_specific_data( cs );
                    continue;
                }
                lsmash_box_type_t box_type = isom_guess_audio_codec_specific_box_type( audio->type, fourcc );
                if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_WAVE ) )
                {
                    /* It is insane to appened a 'wave' extension to a 'wave' extension. */
                    lsmash_destroy_codec_specific_data( cs );
                    continue;
                }
                box_type = lsmash_form_qtff_box_type( box_type.fourcc );
                /* Determine 'precedence'. */
                uint64_t precedence;
                if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_FRMA ) )
                    precedence = LSMASH_BOX_PRECEDENCE_QTFF_FRMA;
                else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_ESDS ) )
                    precedence = LSMASH_BOX_PRECEDENCE_QTFF_ESDS;
                else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_ENDA ) )
                    precedence = LSMASH_BOX_PRECEDENCE_QTFF_ENDA;
                else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_MP4A ) )
                    precedence = LSMASH_BOX_PRECEDENCE_QTFF_MP4A;
                else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_TERMINATOR ) )
                    precedence = LSMASH_BOX_PRECEDENCE_QTFF_TERMINATOR;
                else
                    precedence = LSMASH_BOX_PRECEDENCE_HM;
                /* Append the extension. */
                err = isom_add_extension_binary( wave, box_type, precedence, cs->data.unstructured, cs->size );
                cs->data.unstructured = NULL;   /* Avoid freeing the binary data of the extension. */
                lsmash_destroy_codec_specific_data( cs );
                if( err < 0 )
                    return err;
                if( isom_is_waveform_audio( box_type ) )
                    waveform_audio_info_present = 1;
                break;
            }
        }
    }
    if( requires_waveform_audio_info && !waveform_audio_info_present
     && (err = isom_setup_waveform_audio_info( wave, audio, summary, samples_per_packet, bytes_per_frame, sample_size )) < 0 )
        return err;
    return 0;
}

static int isom_set_qtff_template_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    audio->manager |= LSMASH_QTFF_BASE;
    audio->type     = lsmash_form_qtff_box_type( audio->type.fourcc );
    audio->version  = (summary->channels > 2 || summary->frequency > UINT16_MAX) ? 2 : 1;
    /* Try to get QuickTime audio format specific flags. */
    lsmash_qt_audio_format_specific_flag format_flags = QT_AUDIO_FORMAT_FLAG_BIG_ENDIAN;
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific
         || !specific->data.structured )
            continue;
        if( specific->type   == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS
         && specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
        {
            /* A format specific flags is found.
             * Force audio sample description version == 2. */
            format_flags   = ((lsmash_qt_audio_format_specific_flags_t *)specific->data.structured)->format_flags;
            audio->version = 2;
            break;
        }
    }
    uint32_t samples_per_packet;
    uint32_t bytes_per_frame;
    uint32_t sample_size;
    if( !((summary->samples_in_frame == 0 || summary->bytes_per_frame == 0 || summary->sample_size == 0)
     && isom_get_implicit_qt_fixed_comp_audio_sample_quants( audio, &samples_per_packet, &bytes_per_frame, &sample_size )) )
    {
        samples_per_packet = summary->samples_in_frame;
        bytes_per_frame    = summary->bytes_per_frame;
        sample_size        = summary->sample_size;
    }
    if( !lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_MAC3_AUDIO )
     && !lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_MAC6_AUDIO )
     && !lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_AGSM_AUDIO )
     && !lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ALAW_AUDIO )
     && !lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ULAW_AUDIO ) )
    {
        int err = isom_set_qtff_sound_decompression_parameters( audio, summary, &format_flags,
                                                                samples_per_packet, bytes_per_frame, sample_size );
        if( err < 0 )
            return err;
    }
    /* Set up common audio description fields. */
    audio->samplesize  = 16;
    audio->packet_size = 0;
    if( audio->version == 2 )
    {
        audio->channelcount                  = 3;
        audio->compression_ID                = QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION;
        audio->samplerate                    = 0x00010000;
        audio->sizeOfStructOnly              = 72;
        audio->audioSampleRate               = (union {double d; uint64_t i;}){summary->frequency}.i;
        audio->numAudioChannels              = summary->channels;
        audio->always7F000000                = 0x7F000000;
        audio->constBitsPerChannel           = 0;
        audio->constBytesPerAudioPacket      = bytes_per_frame;
        audio->constLPCMFramesPerAudioPacket = samples_per_packet;
        if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ALAC_AUDIO ) )
        {
            switch( sample_size )
            {
                case 16 :
                    audio->formatSpecificFlags = QT_ALAC_FORMAT_FLAG_16BIT_SOURCE_DATA;
                    break;
                case 20 :
                    audio->formatSpecificFlags = QT_ALAC_FORMAT_FLAG_20BIT_SOURCE_DATA;
                    break;
                case 24 :
                    audio->formatSpecificFlags = QT_ALAC_FORMAT_FLAG_24BIT_SOURCE_DATA;
                    break;
                case 32 :
                    audio->formatSpecificFlags = QT_ALAC_FORMAT_FLAG_32BIT_SOURCE_DATA;
                    break;
                default :
                    break;
            }
        }
        else
        {
            if( format_flags & QT_AUDIO_FORMAT_FLAG_FLOAT )
                format_flags &= ~QT_AUDIO_FORMAT_FLAG_SIGNED_INTEGER;
            if( format_flags & QT_AUDIO_FORMAT_FLAG_PACKED )
                format_flags &= ~QT_AUDIO_FORMAT_FLAG_ALIGNED_HIGH;
            audio->formatSpecificFlags = format_flags;
        }
    }
    else    /* if( audio->version == 1 ) */
    {
        audio->channelcount     = LSMASH_MIN( summary->channels, 2 );
        audio->compression_ID   = QT_AUDIO_COMPRESSION_ID_FIXED_COMPRESSION;
        audio->samplerate       = summary->frequency << 16;
        audio->samplesPerPacket = samples_per_packet;
        audio->bytesPerPacket   = bytes_per_frame / summary->channels;
        audio->bytesPerFrame    = bytes_per_frame;  /* sample_size field in stsz box is NOT used. */
        audio->bytesPerSample   = 1 + (sample_size != 8);
    }
    return 0;
}

static void isom_set_samplerate_division_of_media_timescale( isom_audio_entry_t *audio, int strict )
{
    isom_mdia_t *mdia = (isom_mdia_t *)audio->parent->parent->parent->parent;   /* audio_entry->stsd->stbl->minf->mdia */
    if( lsmash_check_box_type_identical( mdia->type, ISOM_BOX_TYPE_MDIA )
     && LSMASH_IS_EXISTING_BOX( mdia->mdhd ) )
    {
        /* Make an effort to match the timescale with samplerate, or be an integer multiple of it. */
        uint32_t orig_timescale = ((isom_mdia_t *)audio->parent->parent->parent->parent)->mdhd->timescale;
        uint32_t timescale      = orig_timescale;
        uint32_t i              = 2;
        while( timescale > UINT16_MAX && timescale > 1 )
        {
            if( timescale % i == 0 )
                timescale /= i;
            else
                i += i > 2 ? 2 : 1;
        }
        if( timescale != orig_timescale && strict )
            lsmash_log( NULL, LSMASH_LOG_WARNING, "samplerate does not match the media timescale.\n" );
        if( timescale <= UINT16_MAX && timescale > 1 )
        {
            audio->samplerate = timescale << 16;
            return;
        }
    }
    audio->samplerate = 0;
}

static int isom_set_isom_template_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    audio->version        = 0;  /* reserved */
    audio->revision_level = 0;  /* reserved */
    audio->vendor         = 0;  /* reserved */
    audio->channelcount   = 2;  /* template */
    audio->samplesize     = 16; /* template */
    audio->compression_ID = 0;  /* pre_defined */
    audio->packet_size    = 0;  /* reserved */
    /* template : default output audio sampling rate at playback */
    if( summary->frequency <= UINT16_MAX )
        audio->samplerate = summary->frequency << 16;
    else
        isom_set_samplerate_division_of_media_timescale( audio, 0 );
    return 0;
}

static int isom_set_isom_amr_audio_description( isom_audio_entry_t *audio, int wb )
{
    /* For AMR-NB and AMR-WB stream, these fields are not meaningful. */
    audio->version        = 0;  /* always 0 */
    audio->revision_level = 0;  /* always 0 */
    audio->vendor         = 0;  /* always 0 */
    audio->channelcount   = 2;  /* always 2 although the actual number of channels is always 1 */
    audio->samplesize     = 16; /* always 16 */
    audio->compression_ID = 0;  /* always 0 */
    audio->packet_size    = 0;  /* always 0 */
    /* Set samplerate by trying to copy from Media Header Box of this media though the
     * actual samplerate is 8000 Hz for AMR-NB and 16000 Hz for AMR-WB.
     * 3GPP and 3GPP2 has no restriction for media timescale. Therefore, users should
     * set suitable media timescale by themselves within the bounds of common sense. */
    isom_set_samplerate_division_of_media_timescale( audio, 1 );
    if( audio->samplerate == 0 )
        /* Set hard-coded but correct samplerate in the CODEC level. */
        audio->samplerate = wb ? 8000 : 16000;
    return 0;
}

static int isom_set_isom_alac_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    return isom_set_isom_template_audio_description( audio, summary );
}

static int isom_set_qtff_alac_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    return isom_set_qtff_template_audio_description( audio, summary );
}

static int isom_set_isom_eac3_audio_description( isom_audio_entry_t *audio, lsmash_audio_summary_t *summary )
{
    return isom_set_isom_template_audio_description( audio, summary );
}

static int isom_setup_audio_description( isom_stsd_t *stsd, lsmash_audio_summary_t *summary )
{
    if( LSMASH_IS_NON_EXISTING_BOX( stsd->file ) || !summary )
        return LSMASH_ERR_NAMELESS;
    int err = isom_check_valid_summary( (lsmash_summary_t *)summary );
    if( err < 0 )
        return err;
    isom_audio_entry_t *audio = isom_add_audio_description( stsd, summary->sample_type );
    if( LSMASH_IS_NON_EXISTING_BOX( audio ) )
        return LSMASH_ERR_NAMELESS;
    audio->data_reference_index = summary->data_ref_index;
    lsmash_file_t *file = stsd->file;
    lsmash_codec_type_t audio_type = audio->type;
    if( lsmash_check_codec_type_identical( audio_type, ISOM_CODEC_TYPE_MP4A_AUDIO )
     || lsmash_check_codec_type_identical( audio_type,   QT_CODEC_TYPE_MP4A_AUDIO ) )
    {
        if( (LSMASH_IS_EXISTING_BOX( file->ftyp ) && file->ftyp->major_brand == ISOM_BRAND_TYPE_QT)
         || (LSMASH_IS_NON_EXISTING_BOX( file->ftyp )
          && (file->qt_compatible || (LSMASH_IS_EXISTING_BOX( file->moov ) && LSMASH_IS_NON_EXISTING_BOX( file->moov->iods )))) )
            err = isom_set_qtff_mp4a_description( audio, summary );
        else
            err = isom_set_isom_mp4a_description( audio, summary );
    }
    else if( isom_is_lpcm_audio( audio ) )
        err = isom_set_qtff_lpcm_description( audio, summary );
    else if( file->isom_compatible && lsmash_check_codec_type_identical( audio_type, ISOM_CODEC_TYPE_ALAC_AUDIO ) )
        err = isom_set_isom_alac_audio_description( audio, summary );
    else if( file->qt_compatible   && lsmash_check_codec_type_identical( audio_type,   QT_CODEC_TYPE_ALAC_AUDIO ) )
        err = isom_set_qtff_alac_audio_description( audio, summary );
    else if( audio->type.fourcc == ISOM_CODEC_TYPE_ALAC_AUDIO.fourcc )
    {
        if( file->qt_compatible )
            err = isom_set_qtff_alac_audio_description( audio, summary );
        else
            err = isom_set_isom_alac_audio_description( audio, summary );
    }
    else if( isom_is_dts_audio( audio_type ) )
        err = isom_set_isom_dts_audio_description( audio, summary );
    else if( lsmash_check_codec_type_identical( audio_type, ISOM_CODEC_TYPE_EC_3_AUDIO ) )
        err = isom_set_isom_eac3_audio_description( audio, summary );
    else if( file->qt_compatible )
        err = isom_set_qtff_template_audio_description( audio, summary );
    else if( lsmash_check_codec_type_identical( audio_type, ISOM_CODEC_TYPE_SAMR_AUDIO ) )
        err = isom_set_isom_amr_audio_description( audio, 0 );
    else if( lsmash_check_codec_type_identical( audio_type, ISOM_CODEC_TYPE_SAWB_AUDIO ) )
        err = isom_set_isom_amr_audio_description( audio, 1 );
    else
        err = isom_set_isom_template_audio_description( audio, summary );
    if( err < 0 )
        goto fail;
    err = LSMASH_ERR_NAMELESS;
    /* Don't use audio_type since audio->type might have changed. */
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
    {
        lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
        if( !specific )
            goto fail;
        if( specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN
         && specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
            continue;   /* LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN + LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED is not supported. */
        switch( specific->type )
        {
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON :
            {
                if( specific->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED )
                    continue;   /* Ignore since not fatal. */
                lsmash_qt_audio_common_t *data = (lsmash_qt_audio_common_t *)specific->data.structured;
                audio->revision_level = data->revision_level;
                audio->vendor         = data->vendor;
                if( audio->version == 1
                 && !isom_is_lpcm_audio( audio )
                 && data->compression_ID != QT_AUDIO_COMPRESSION_ID_NOT_COMPRESSED )
                {
                    /* Compressed audio must not be set to QT_AUDIO_COMPRESSION_ID_NOT_COMPRESSED. */
                    audio->compression_ID = data->compression_ID;
                    if( audio->compression_ID == QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION )
                    {
                        /* For variable compression, bytesPerPacket and bytesPerFrame are reserved and should be set to 0. */
                        audio->bytesPerPacket = 0;
                        audio->bytesPerFrame  = 0;
                    }
                }
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT :
            {
                if( !file->qt_compatible
                 && !lsmash_check_codec_type_identical( audio->type, ISOM_CODEC_TYPE_ALAC_AUDIO )
                 && !lsmash_check_codec_type_identical( audio->type,   QT_CODEC_TYPE_ALAC_AUDIO ) )
                    continue;
                if( (err = isom_append_channel_layout_extension( specific, audio, summary->channels )) < 0 )
                    goto fail;
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !cs )
                    goto fail;
                lsmash_codec_global_header_t *data = (lsmash_codec_global_header_t *)cs->data.structured;
                isom_glbl_t *glbl = isom_add_glbl( audio );
                if( LSMASH_IS_NON_EXISTING_BOX( glbl ) )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    goto fail;
                }
                glbl->header_size = data->header_size;
                glbl->header_data = lsmash_memdup( data->header_data, data->header_size );
                lsmash_destroy_codec_specific_data( cs );
                if( !glbl->header_data )
                {
                    isom_remove_box_by_itself( glbl );
                    err = LSMASH_ERR_MEMORY_ALLOC;
                    goto fail;
                }
                break;
            }
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS :
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_DECOMPRESSION_PARAMETERS :
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG :
                break;  /* shall be set up already */
            case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC :
                if( file->qt_compatible )
                    continue;  /* shall be set up already */
            default :
            {
                lsmash_codec_specific_t *cs = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                if( !cs )
                    goto fail;
                if( cs->size < ISOM_BASEBOX_COMMON_SIZE )
                {
                    lsmash_destroy_codec_specific_data( cs );
                    continue;
                }
                uint8_t *box_data = cs->data.unstructured;
                lsmash_compact_box_type_t fourcc   = LSMASH_4CC( box_data[4], box_data[5], box_data[6], box_data[7] );
                lsmash_box_type_t         box_type = isom_guess_audio_codec_specific_box_type( audio->type, fourcc );
                if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_WAVE ) )
                {
                    /* CODEC specific info shall be already inside 'wave' extension. */
                    lsmash_destroy_codec_specific_data( cs );
                    continue;
                }
                /* Append the extension. */
                err = isom_add_extension_binary( audio, box_type, LSMASH_BOX_PRECEDENCE_HM, cs->data.unstructured, cs->size );
                cs->data.unstructured = NULL;   /* Avoid freeing the binary data of the extension. */
                lsmash_destroy_codec_specific_data( cs );
                if( err < 0 )
                    goto fail;
                break;
            }
        }
    }
    if( audio->version == 0 )
        audio->compression_ID = QT_AUDIO_COMPRESSION_ID_NOT_COMPRESSED;
    else if( audio->version == 2 )
        audio->compression_ID = QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION;
    return 0;
fail:
    isom_remove_box_by_itself( audio );
    return err;
}

static int isom_setup_tx3g_description( isom_stsd_t *stsd, lsmash_summary_t *summary )
{
    isom_tx3g_entry_t *tx3g = isom_add_tx3g_description( stsd );
    if( LSMASH_IS_NON_EXISTING_BOX( tx3g ) )
        return LSMASH_ERR_NAMELESS;
    /* We create a dummy font record to make valid font_ID in the sample description.
     * The specification (3GPP TS 26.245) does not forbid the value 0 for the identifier,
     * but we set 1 to it as track_ID begins from 1. */
    tx3g->data_reference_index = summary->data_ref_index;
    tx3g->font_ID              = 1; /* ID of the default font record */
    int err = LSMASH_ERR_MEMORY_ALLOC;
    isom_ftab_t *ftab = isom_add_ftab( tx3g );
    if( LSMASH_IS_NON_EXISTING_BOX( ftab ) )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    isom_font_record_t *font = lsmash_malloc( sizeof(isom_font_record_t) );
    if( !font )
        goto fail;
    if( lsmash_list_add_entry( ftab->list, font ) < 0 )
    {
        lsmash_free( font );
        goto fail;
    }
    const char font_names[] = "Serif,Sans-serif,Monospace";
    font->font_ID          = 1;
    font->font_name_length = sizeof(font_names);
    font->font_name        = lsmash_memdup( font_names, sizeof(font_names) );
    if( !font->font_name )
        goto fail;
    return 0;
fail:
    isom_remove_box_by_itself( tx3g );
    return err;
}

static int isom_setup_qt_text_description( isom_stsd_t *stsd, lsmash_summary_t *summary )
{
    isom_qt_text_entry_t *text = isom_add_qt_text_description( stsd );
    if( LSMASH_IS_NON_EXISTING_BOX( text ) )
        return LSMASH_ERR_NAMELESS;
    text->data_reference_index = summary->data_ref_index;
    return 0;
}

static int isom_setup_text_description( isom_stsd_t *stsd, lsmash_summary_t *summary )
{
    lsmash_codec_type_t sample_type = summary->sample_type;
    if( lsmash_check_box_type_identical( sample_type, ISOM_CODEC_TYPE_TX3G_TEXT ) )
        return isom_setup_tx3g_description( stsd, summary );
    else if( lsmash_check_box_type_identical( sample_type, QT_CODEC_TYPE_TEXT_TEXT ) )
        return isom_setup_qt_text_description( stsd, summary );
    else
        return LSMASH_ERR_NAMELESS;
}

int isom_setup_hint_description( isom_stsd_t *stsd, lsmash_hint_summary_t *summary )
{
    lsmash_codec_type_t sample_type = summary->sample_type;
    if( LSMASH_IS_NON_EXISTING_BOX( stsd->file ) || !summary )
        return LSMASH_ERR_NAMELESS;
    int err = isom_check_valid_summary( (lsmash_summary_t *)summary );
    if( err < 0 )
        goto fail;
    isom_hint_entry_t *hint = isom_add_hint_description( stsd, sample_type );
    if( LSMASH_IS_NON_EXISTING_BOX( hint ) )
        return LSMASH_ERR_NAMELESS;
    hint->data_reference_index = summary->data_ref_index;
    /* configure the sample description */
    lsmash_codec_type_t hint_type = hint->type;
    if( lsmash_check_codec_type_identical(hint_type, ISOM_CODEC_TYPE_RRTP_HINT ) )
    {
        /* go through list of codec specific datas associated with this summary */
        for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
        {
            lsmash_codec_specific_t *specific = (lsmash_codec_specific_t *)entry->data;
            if( !specific )
            {
                err = LSMASH_ERR_NAMELESS;
                goto fail;
            }
            if( specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_RTP_HINT_COMMON )
            {
                lsmash_isom_rtp_reception_hint_t* rtp_param;
                rtp_param = (lsmash_isom_rtp_reception_hint_t *)specific->data.structured;
                if( rtp_param->timescale == 0 )
                    return LSMASH_ERR_INVALID_DATA;
                err = isom_set_hint_summary( hint, summary );
                if( err < 0 )
                    goto fail;
                isom_tims_t *tims = isom_add_tims( hint );
                isom_tsro_t *tsro = isom_add_tsro( hint );
                isom_tssy_t *tssy = isom_add_tssy( hint );
                if( LSMASH_IS_NON_EXISTING_BOX( tims )
                 || LSMASH_IS_NON_EXISTING_BOX( tsro )
                 || LSMASH_IS_NON_EXISTING_BOX( tssy ) )
                    return LSMASH_ERR_NAMELESS;
                tims->timescale      = rtp_param->timescale;
                tsro->offset         = rtp_param->time_offset;
                tssy->reserved       = rtp_param->reserved_timestamp_sync >> 2;
                tssy->timestamp_sync = rtp_param->reserved_timestamp_sync & 0x03;
            }
        }
    }
    else
        return LSMASH_ERR_PATCH_WELCOME;
    return 0;
fail:
    return err;
}

int isom_setup_sample_description( isom_stsd_t *stsd, lsmash_media_type media_type, lsmash_summary_t *summary )
{
    if( media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK )
        return isom_setup_visual_description( stsd, (lsmash_video_summary_t *)summary );
    else if( media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK )
        return isom_setup_audio_description( stsd, (lsmash_audio_summary_t *)summary );
    else if( media_type == ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK )
        return isom_setup_text_description( stsd, (lsmash_summary_t *)summary );
    else if( media_type == ISOM_MEDIA_HANDLER_TYPE_HINT_TRACK )
        return isom_setup_hint_description( stsd, (lsmash_hint_summary_t *)summary );
    else
        return LSMASH_ERR_NAMELESS;
}

static lsmash_codec_specific_data_type isom_get_codec_specific_data_type( lsmash_compact_box_type_t extension_fourcc )
{
    static struct codec_specific_data_type_table_tag
    {
        lsmash_compact_box_type_t       extension_fourcc;
        lsmash_codec_specific_data_type data_type;
    } codec_specific_data_type_table[32] = { { 0, LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN } };
    if( codec_specific_data_type_table[0].data_type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN )
    {
        int i = 0;
#define ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( extension_type, data_type ) \
    codec_specific_data_type_table[i++] = (struct codec_specific_data_type_table_tag){ extension_type.fourcc, data_type }
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_AVCC, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264 );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_HVCC, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_DVC1, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_VC_1 );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_DAC3, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_DEC3, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_DDTS, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_ALAC, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_ESDS, LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_STSL, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_SAMPLE_SCALE );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( ISOM_BOX_TYPE_BTRT, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264_BITRATE );
        //ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_ALAC, LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_ALAC );
        //ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_ESDS, LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_FIEL, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_CSPC, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_PIXEL_FORMAT );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_SGBT, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_GAMA, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_GAMMA_LEVEL );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_CLLI, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_CONTENT_LIGHT_LEVEL_INFO );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_MDCV, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_MASTERING_DISPLAY_COLOR_VOLUME );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_CHAN, LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT(   QT_BOX_TYPE_GLBL, LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER );
        ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT( LSMASH_BOX_TYPE_UNSPECIFIED, LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN );
#undef ADD_CODEC_SPECIFIC_DATA_TYPE_TABLE_ELEMENT
    }
    lsmash_codec_specific_data_type data_type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN;
    for( int i = 0; codec_specific_data_type_table[i].data_type != LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN; i++ )
        if( extension_fourcc == codec_specific_data_type_table[i].extension_fourcc )
        {
            data_type = codec_specific_data_type_table[i].data_type;
            break;
        }
    return data_type;
}

lsmash_summary_t *isom_create_video_summary_from_description( isom_sample_entry_t *sample_entry )
{
    if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
        return NULL;
    isom_visual_entry_t *visual = (isom_visual_entry_t *)sample_entry;
    lsmash_video_summary_t *summary = (lsmash_video_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_VIDEO );
    if( !summary )
        return NULL;
    summary->sample_type    = visual->type;
    summary->data_ref_index = visual->data_reference_index;
    summary->width          = visual->width;
    summary->height         = visual->height;
    summary->depth          = visual->depth;
    memcpy( summary->compressorname, visual->compressorname, 32 );
    summary->compressorname[32] = '\0';
    if( isom_is_qt_video( summary->sample_type ) )
    {
        lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON,
                                                                               LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
        if( !specific )
            goto fail;
        lsmash_qt_video_common_t *data = (lsmash_qt_video_common_t *)specific->data.structured;
        data->revision_level        = visual->revision_level;
        data->vendor                = visual->vendor;
        data->temporalQuality       = visual->temporalQuality;
        data->spatialQuality        = visual->spatialQuality;
        data->horizontal_resolution = visual->horizresolution;
        data->vertical_resolution   = visual->vertresolution;
        data->dataSize              = visual->dataSize;
        data->frame_count           = visual->frame_count;
        data->color_table_ID        = visual->color_table_ID;
        if( visual->color_table_ID == 0 )
        {
            isom_qt_color_table_t *src_ct = &visual->color_table;
            if( !src_ct->array )
            {
                lsmash_destroy_codec_specific_data( specific );
                goto fail;
            }
            uint16_t element_count = LSMASH_MIN( src_ct->size + 1, 256 );
            lsmash_qt_color_table_t *dst_ct = &data->color_table;
            dst_ct->seed  = src_ct->seed;
            dst_ct->flags = src_ct->flags;
            dst_ct->size  = src_ct->size;
            for( uint16_t i = 0; i < element_count; i++ )
            {
                dst_ct->array[i].unused = src_ct->array[i].value;
                dst_ct->array[i].r      = src_ct->array[i].r;
                dst_ct->array[i].g      = src_ct->array[i].g;
                dst_ct->array[i].b      = src_ct->array[i].b;
            }
        }
        if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
        {
            lsmash_destroy_codec_specific_data( specific );
            goto fail;
        }
    }
    for( lsmash_entry_t *entry = visual->extensions.head; entry; entry = entry->next )
    {
        isom_box_t *box = (isom_box_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( box ) )
            continue;
        if( !(box->manager & LSMASH_BINARY_CODED_BOX) )
        {
            lsmash_codec_specific_t *specific = NULL;
            if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_CLAP ) )
            {
                isom_clap_t *clap = (isom_clap_t *)box;
                summary->clap.width.n             = clap->cleanApertureWidthN;
                summary->clap.width.d             = clap->cleanApertureWidthD;
                summary->clap.height.n            = clap->cleanApertureHeightN;
                summary->clap.height.d            = clap->cleanApertureHeightD;
                summary->clap.horizontal_offset.n = clap->horizOffN;
                summary->clap.horizontal_offset.d = clap->horizOffD;
                summary->clap.vertical_offset.n   = clap->vertOffN;
                summary->clap.vertical_offset.d   = clap->vertOffD;
                continue;
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_PASP ) )
            {
                isom_pasp_t *pasp = (isom_pasp_t *)box;
                summary->par_h = pasp->hSpacing;
                summary->par_v = pasp->vSpacing;
                continue;
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_COLR )
                  || lsmash_check_box_type_identical( box->type,   QT_BOX_TYPE_COLR ) )
            {
                isom_colr_t *colr = (isom_colr_t *)box;
                summary->color.primaries_index = colr->primaries_index;
                summary->color.transfer_index  = colr->transfer_function_index;
                summary->color.matrix_index    = colr->matrix_index;
                summary->color.full_range      = colr->full_range_flag;
                continue;
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_STSL ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_SAMPLE_SCALE,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_stsl_t *stsl = (isom_stsl_t *)box;
                lsmash_isom_sample_scale_t *data = (lsmash_isom_sample_scale_t *)specific->data.structured;
                data->constraint_flag  = stsl->constraint_flag;
                data->scale_method     = stsl->scale_method;
                data->display_center_x = stsl->display_center_x;
                data->display_center_y = stsl->display_center_y;
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_BTRT ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264_BITRATE,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_btrt_t *btrt = (isom_btrt_t *)box;
                lsmash_h264_bitrate_t *data = (lsmash_h264_bitrate_t *)specific->data.structured;
                data->bufferSizeDB = btrt->bufferSizeDB;
                data->maxBitrate   = btrt->maxBitrate;
                data->avgBitrate   = btrt->avgBitrate;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_FIEL ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_FIELD_INFO,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_fiel_t *fiel = (isom_fiel_t *)box;
                lsmash_qt_field_info_t *data = (lsmash_qt_field_info_t *)specific->data.structured;
                data->fields = fiel->fields;
                data->detail = fiel->detail;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_CSPC ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_PIXEL_FORMAT,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_cspc_t *cspc = (isom_cspc_t *)box;
                lsmash_qt_pixel_format_t *data = (lsmash_qt_pixel_format_t *)specific->data.structured;
                data->pixel_format = cspc->pixel_format;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_SGBT ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_SIGNIFICANT_BITS,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_sgbt_t *sgbt = (isom_sgbt_t *)box;
                lsmash_qt_significant_bits_t *data = (lsmash_qt_significant_bits_t *)specific->data.structured;
                data->significantBits = sgbt->significantBits;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_GLBL ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_CODEC_GLOBAL_HEADER,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_glbl_t *glbl = (isom_glbl_t *)box;
                lsmash_codec_global_header_t *data = (lsmash_codec_global_header_t *)specific->data.structured;
                data->header_size = glbl->header_size;
                data->header_data = lsmash_memdup( glbl->header_data, glbl->header_size );
                if( !data->header_data )
                {
                    lsmash_destroy_codec_specific_data( specific );
                    goto fail;
                }
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_CLLI ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_CONTENT_LIGHT_LEVEL_INFO,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_clli_t *clli = (isom_clli_t *)box;
                lsmash_qt_content_light_level_info_t *data = (lsmash_qt_content_light_level_info_t *)specific->data.structured;
                data->max_content_light_level     = clli->max_content_light_level;
                data->max_pic_average_light_level = clli->max_pic_average_light_level;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_MDCV ) )
            {
                specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_MASTERING_DISPLAY_COLOR_VOLUME,
                                                              LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_mdcv_t *mdcv = (isom_mdcv_t *)box;
                lsmash_qt_mastering_display_color_volume_t *data = (lsmash_qt_mastering_display_color_volume_t *)specific->data.structured;
                data->display_primaries_g_x           = mdcv->display_primaries_g_x;
                data->display_primaries_g_y           = mdcv->display_primaries_g_y;
                data->display_primaries_b_x           = mdcv->display_primaries_b_x;
                data->display_primaries_b_y           = mdcv->display_primaries_b_y;
                data->display_primaries_r_x           = mdcv->display_primaries_r_x;
                data->display_primaries_r_y           = mdcv->display_primaries_r_y;
                data->white_point_x                   = mdcv->white_point_x;
                data->white_point_y                   = mdcv->white_point_y;
                data->max_display_mastering_luminance = mdcv->max_display_mastering_luminance;
                data->min_display_mastering_luminance = mdcv->min_display_mastering_luminance;
            }
            else
                continue;
            if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
            {
                lsmash_destroy_codec_specific_data( specific );
                goto fail;
            }
        }
        else
        {
            if( box->size < ISOM_BASEBOX_COMMON_SIZE )
                continue;
            uint8_t *data = box->binary;
            lsmash_compact_box_type_t fourcc = LSMASH_4CC( data[4], data[5], data[6], data[7] );
            lsmash_codec_specific_data_type type = isom_get_codec_specific_data_type( fourcc );
            lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( type, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
            if( !specific )
                goto fail;
            specific->size              = box->size;
            specific->data.unstructured = lsmash_memdup( box->binary, box->size );
            if( !specific->data.unstructured
             || lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
            {
                lsmash_destroy_codec_specific_data( specific );
                goto fail;
            }
        }
    }
    return (lsmash_summary_t *)summary;
fail:
    lsmash_cleanup_summary( (lsmash_summary_t *)summary );
    return NULL;
}

static int isom_append_structured_mp4sys_decoder_config( lsmash_codec_specific_list_t *opaque, isom_esds_t *esds )
{
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return LSMASH_ERR_MEMORY_ALLOC;
    /* Put box size, type, version and flags fields. */
    lsmash_bs_put_be32( bs, 0 );
    lsmash_bs_put_be32( bs, ISOM_BOX_TYPE_ESDS.fourcc );
    lsmash_bs_put_be32( bs, 0 );
    /* Put ES Descriptor. */
    mp4sys_update_descriptor_size( esds->ES );
    mp4sys_write_descriptor( bs, esds->ES );
    /* Export ES Descriptor Box as binary string. */
    uint32_t esds_size;
    uint8_t *esds_data = lsmash_bs_export_data( bs, &esds_size );
    lsmash_bs_cleanup( bs );
    if( !esds_data )
        return LSMASH_ERR_NAMELESS;
    /* Update box size. */
    LSMASH_SET_BE32( esds_data, esds_size );
    lsmash_codec_specific_data_type type = isom_get_codec_specific_data_type( ISOM_BOX_TYPE_ESDS.fourcc );
    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( type, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
    if( !specific )
    {
        lsmash_free( esds_data );
        return LSMASH_ERR_NAMELESS;
    }
    specific->data.unstructured = esds_data;
    specific->size              = esds_size;
    /* Convert unstructured CODEC specific data format into structured, and append it to the opaque list. */
    lsmash_codec_specific_t *conv = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
    lsmash_destroy_codec_specific_data( specific );
    if( !conv )
        return LSMASH_ERR_NAMELESS;
    if( lsmash_list_add_entry( &opaque->list, conv ) < 0 )
    {
        lsmash_destroy_codec_specific_data( conv );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

lsmash_summary_t *isom_create_audio_summary_from_description( isom_sample_entry_t *sample_entry )
{
    if( LSMASH_IS_NON_EXISTING_BOX( sample_entry->file )
     || LSMASH_IS_NON_EXISTING_BOX( sample_entry->parent ) )
        return NULL;
    isom_audio_entry_t *audio = (isom_audio_entry_t *)sample_entry;
    lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
    if( !summary )
        return NULL;
    summary->sample_type    = audio->type;
    summary->data_ref_index = audio->data_reference_index;
    summary->sample_size    = audio->samplesize;
    summary->channels       = audio->channelcount;
    summary->frequency      = audio->samplerate >> 16;
    if( ((isom_stsd_t *)audio->parent)->version == 0
     && audio->file->qt_compatible
     && isom_is_qt_audio( audio->type ) )
    {
        if( audio->version == 0 )
            isom_get_implicit_qt_fixed_comp_audio_sample_quants( audio, &summary->samples_in_frame, &summary->bytes_per_frame, &summary->sample_size );
        else if( audio->version == 1 )
        {
            summary->channels         = audio->bytesPerPacket ? audio->bytesPerFrame / audio->bytesPerPacket : audio->channelcount;
            summary->sample_size      = audio->bytesPerPacket * 8;
            summary->samples_in_frame = audio->samplesPerPacket;
            summary->bytes_per_frame  = audio->bytesPerFrame;
        }
        else if( audio->version == 2 )
        {
            summary->frequency        = (union {uint64_t i; double d;}){audio->audioSampleRate}.d;
            summary->channels         = audio->numAudioChannels;
            summary->sample_size      = audio->constBitsPerChannel;
            summary->samples_in_frame = audio->constLPCMFramesPerAudioPacket;
            summary->bytes_per_frame  = audio->constBytesPerAudioPacket;
        }
        lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON,
                                                                               LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
        if( !specific )
            goto fail;
        lsmash_qt_audio_common_t *common = (lsmash_qt_audio_common_t *)specific->data.structured;
        common->revision_level = audio->revision_level;
        common->vendor         = audio->vendor;
        common->compression_ID = audio->compression_ID;
        if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
        {
            lsmash_destroy_codec_specific_data( specific );
            goto fail;
        }
        if( isom_is_lpcm_audio( audio ) )
        {
            specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS,
                                                          LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
            if( !specific )
                goto fail;
            lsmash_qt_audio_format_specific_flags_t *data = (lsmash_qt_audio_format_specific_flags_t *)specific->data.structured;
            if( audio->version == 2 )
                data->format_flags = audio->formatSpecificFlags;
            else
            {
                data->format_flags = QT_LPCM_FORMAT_FLAG_BIG_ENDIAN | QT_LPCM_FORMAT_FLAG_SIGNED_INTEGER;
                /* Here, don't override samplesize.
                 * We should trust samplesize field in the description for misused CODEC indentifier. */
                lsmash_codec_type_t audio_type = audio->type;
                if( lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_TWOS_AUDIO )
                 || lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_NONE_AUDIO )
                 || lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_NOT_SPECIFIED ) )
                {
                    if( summary->sample_size <= 8 )
                        data->format_flags &= ~(QT_LPCM_FORMAT_FLAG_BIG_ENDIAN | QT_LPCM_FORMAT_FLAG_SIGNED_INTEGER);
                }
                else
                {
                    if( lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_FL32_AUDIO )
                     || lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_FL64_AUDIO ) )
                    {
                        data->format_flags &= ~QT_LPCM_FORMAT_FLAG_SIGNED_INTEGER;
                        data->format_flags |=  QT_LPCM_FORMAT_FLAG_FLOAT;
                    }
                    else if( lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_23NI_AUDIO )
                          || lsmash_check_codec_type_identical( audio_type, QT_CODEC_TYPE_SOWT_AUDIO ) )
                        data->format_flags &= ~QT_LPCM_FORMAT_FLAG_BIG_ENDIAN;
                }
            }
            isom_wave_t *wave = (isom_wave_t *)isom_get_extension_box_format( &audio->extensions, QT_BOX_TYPE_WAVE );
            if( LSMASH_IS_EXISTING_BOX( wave->enda ) )
            {
                if( wave->enda->littleEndian )
                    data->format_flags &= ~QT_LPCM_FORMAT_FLAG_BIG_ENDIAN;
                else
                    data->format_flags |=  QT_LPCM_FORMAT_FLAG_BIG_ENDIAN;
            }
            if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
            {
                lsmash_destroy_codec_specific_data( specific );
                goto fail;
            }
        }
        else if( audio->version == 2
              && (lsmash_check_codec_type_identical( audio->type, ISOM_CODEC_TYPE_ALAC_AUDIO )
               || lsmash_check_codec_type_identical( audio->type,   QT_CODEC_TYPE_ALAC_AUDIO )) )
            switch( audio->formatSpecificFlags )
            {
                case QT_ALAC_FORMAT_FLAG_16BIT_SOURCE_DATA :
                    summary->sample_size = 16;
                    break;
                case QT_ALAC_FORMAT_FLAG_20BIT_SOURCE_DATA :
                    summary->sample_size = 20;
                    break;
                case QT_ALAC_FORMAT_FLAG_24BIT_SOURCE_DATA :
                    summary->sample_size = 24;
                    break;
                case QT_ALAC_FORMAT_FLAG_32BIT_SOURCE_DATA :
                    summary->sample_size = 32;
                    break;
                default :
                    break;
            }
    }
    else if( lsmash_check_codec_type_identical( audio->type, ISOM_CODEC_TYPE_SAMR_AUDIO ) )
    {
        summary->channels  = 1;
        summary->frequency = 8000;
    }
    else if( lsmash_check_codec_type_identical( audio->type, ISOM_CODEC_TYPE_SAWB_AUDIO ) )
    {
        summary->channels  = 1;
        summary->frequency = 16000;
    }
    uint32_t actual_sampling_rate = 0;
    for( lsmash_entry_t *entry = audio->extensions.head; entry; entry = entry->next )
    {
        isom_box_t *box = (isom_box_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( box ) )
            continue;
        if( !(box->manager & LSMASH_BINARY_CODED_BOX) )
        {
            if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_CHAN ) )
            {
                lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_CHANNEL_LAYOUT,
                                                                                       LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                isom_chan_t *chan = (isom_chan_t *)box;
                lsmash_qt_audio_channel_layout_t *data = (lsmash_qt_audio_channel_layout_t *)specific->data.structured;
                data->channelLayoutTag = chan->channelLayoutTag;
                data->channelBitmap    = chan->channelBitmap;
                if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
                {
                    lsmash_destroy_codec_specific_data( specific );
                    goto fail;
                }
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_ESDS )
                  || lsmash_check_box_type_identical( box->type,   QT_BOX_TYPE_ESDS ) )
            {
                isom_esds_t *esds = (isom_esds_t *)box;
                if( mp4sys_setup_summary_from_DecoderSpecificInfo( summary, esds->ES ) < 0
                 || isom_append_structured_mp4sys_decoder_config( summary->opaque, esds ) < 0 )
                    goto fail;
            }
            else if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_SRAT ) )
            {
                isom_srat_t *srat = (isom_srat_t *)box;
                actual_sampling_rate = srat->sampling_rate;
            }
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_WAVE ) )
            {
                /* Don't append 'wave' extension itself to the opaque CODEC specific info list. */
                isom_wave_t *wave = (isom_wave_t *)box;
                lsmash_bs_t *bs = lsmash_bs_create();
                if( !bs )
                    goto fail;
                for( lsmash_entry_t *wave_entry = wave->extensions.head; wave_entry; wave_entry = wave_entry->next )
                {
                    isom_box_t *wave_ext = (isom_box_t *)wave_entry->data;
                    if( LSMASH_IS_NON_EXISTING_BOX( wave_ext ) )
                        continue;
                    lsmash_box_type_t box_type = LSMASH_BOX_TYPE_INITIALIZER;
                    if( !(wave_ext->manager & LSMASH_BINARY_CODED_BOX) )
                    {
                        box_type = wave_ext->type;
                        if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_ENDA ) )
                        {
                            isom_enda_t *enda = (isom_enda_t *)wave_ext;
                            isom_bs_put_box_common( bs, enda );
                            lsmash_bs_put_be16( bs, enda->littleEndian );
                        }
                        else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_MP4A ) )
                        {
                            isom_mp4a_t *mp4a = (isom_mp4a_t *)wave_ext;
                            isom_bs_put_box_common( bs, mp4a );
                            lsmash_bs_put_be32( bs, mp4a->unknown );
                        }
                        else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_CHAN ) )
                        {
                            isom_chan_t *chan = (isom_chan_t *)wave_ext;
                            isom_bs_put_box_common( bs, chan );
                            lsmash_bs_put_be32( bs, chan->channelLayoutTag );
                            lsmash_bs_put_be32( bs, chan->channelBitmap );
                            lsmash_bs_put_be32( bs, chan->numberChannelDescriptions );
                            if( chan->channelDescriptions )
                                for( uint32_t i = 0; i < chan->numberChannelDescriptions; i++ )
                                {
                                    isom_channel_description_t *channelDescriptions = (isom_channel_description_t *)(&chan->channelDescriptions[i]);
                                    lsmash_bs_put_be32( bs, channelDescriptions->channelLabel );
                                    lsmash_bs_put_be32( bs, channelDescriptions->channelFlags );
                                    lsmash_bs_put_be32( bs, channelDescriptions->coordinates[0] );
                                    lsmash_bs_put_be32( bs, channelDescriptions->coordinates[1] );
                                    lsmash_bs_put_be32( bs, channelDescriptions->coordinates[2] );
                                }
                        }
                        else if( lsmash_check_box_type_identical( box_type, QT_BOX_TYPE_ESDS ) )
                        {
                            isom_esds_t *esds = (isom_esds_t *)wave_ext;
                            if( LSMASH_IS_NON_EXISTING_BOX( esds )
                             || mp4sys_setup_summary_from_DecoderSpecificInfo( summary, esds->ES ) < 0
                             || isom_append_structured_mp4sys_decoder_config( summary->opaque, esds ) < 0 )
                            {
                                lsmash_bs_cleanup( bs );
                                goto fail;
                            }
                            continue;
                        }
                        else
                            /* Skip Format Box and Terminator Box since they are mandatory and fixed structure. */
                            continue;
                    }
                    else
                    {
                        if( wave_ext->size < ISOM_BASEBOX_COMMON_SIZE )
                            continue;
                        uint8_t *data = wave_ext->binary;
                        box_type.fourcc = LSMASH_4CC( data[4], data[5], data[6], data[7] );
                        lsmash_bs_put_bytes( bs, wave_ext->size, wave_ext->binary );
                    }
                    /* Export as binary string. */
                    uint32_t box_size;
                    uint8_t *box_data = lsmash_bs_export_data( bs, &box_size );
                    lsmash_bs_empty( bs );
                    if( !box_data )
                    {
                        lsmash_bs_cleanup( bs );
                        goto fail;
                    }
                    /* Append as an unstructured CODEC specific info. */
                    lsmash_codec_specific_data_type type;
                    if( box_type.fourcc == QT_BOX_TYPE_CHAN.fourcc )
                        /* Complete audio channel layout is stored as binary string.
                         * We distinguish it from one of the outside of 'wave' extension here. */
                        type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_DECOMPRESSION_PARAMETERS;
                    else
                    {
                        type = isom_get_codec_specific_data_type( box_type.fourcc );
                        if( type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN )
                            type = LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_DECOMPRESSION_PARAMETERS;
                    }
                    lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( type, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                    if( !specific )
                    {
                        lsmash_free( box_data );
                        lsmash_bs_cleanup( bs );
                        goto fail;
                    }
                    specific->data.unstructured = box_data;
                    specific->size              = box_size;
                    if( lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
                    {
                        lsmash_destroy_codec_specific_data( specific );
                        lsmash_bs_cleanup( bs );
                        goto fail;
                    }
                }
                lsmash_bs_cleanup( bs );
            }
        }
        else
        {
            if( box->size < ISOM_BASEBOX_COMMON_SIZE )
                continue;
            uint8_t *data = box->binary;
            lsmash_compact_box_type_t fourcc = LSMASH_4CC( data[4], data[5], data[6], data[7] );
            lsmash_codec_specific_data_type type = isom_get_codec_specific_data_type( fourcc );
            lsmash_codec_specific_t *specific = lsmash_create_codec_specific_data( type, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
            if( !specific )
                goto fail;
            specific->size              = box->size;
            specific->data.unstructured = lsmash_memdup( box->binary, box->size );
            if( !specific->data.unstructured
             || lsmash_list_add_entry( &summary->opaque->list, specific ) < 0 )
            {
                lsmash_destroy_codec_specific_data( specific );
                goto fail;
            }
            if( specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS
             || specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3
             || specific->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 )
            {
                specific = lsmash_convert_codec_specific_format( specific, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
                if( !specific )
                    goto fail;
                switch( specific->type )
                {
                    case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_DTS :
                    {
                        lsmash_dts_specific_parameters_t *param = (lsmash_dts_specific_parameters_t *)specific->data.structured;
                        summary->sample_size      = param->pcmSampleDepth;
                        summary->samples_in_frame = (summary->frequency * (512 << param->FrameDuration)) / param->DTSSamplingFrequency;
                        break;
                    }
                    case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_AC_3 :
                    {
                        lsmash_ac3_specific_parameters_t *param = (lsmash_ac3_specific_parameters_t *)specific->data.structured;
                        summary->frequency        = ac3_get_sample_rate( param );
                        summary->channels         = ac3_get_channel_count( param );
                        summary->samples_in_frame = 1536;
                        break;
                    }
                    case LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_AUDIO_EC_3 :
                    {
                        lsmash_eac3_specific_parameters_t *param = (lsmash_eac3_specific_parameters_t *)specific->data.structured;
                        eac3_update_sample_rate( &summary->frequency, param, NULL );
                        eac3_update_channel_count( &summary->channels, param );
                        summary->samples_in_frame = 1536;
                        break;
                    }
                    default :
                        break;
                }
                lsmash_destroy_codec_specific_data( specific );
            }
        }
    }
    /* Set the actual sampling rate. */
    if( actual_sampling_rate )
        summary->frequency = actual_sampling_rate;
    return (lsmash_summary_t *)summary;
fail:
    lsmash_cleanup_summary( (lsmash_summary_t *)summary );
    return NULL;
}

lsmash_codec_specific_t *lsmash_get_codec_specific_data( lsmash_summary_t *summary, uint32_t extension_number )
{
    if( !summary || !summary->opaque )
        return NULL;
    uint32_t i = 0;
    for( lsmash_entry_t *entry = summary->opaque->list.head; entry; entry = entry->next )
        if( ++i == extension_number )
            return (lsmash_codec_specific_t *)entry->data;
    return NULL;
}

uint32_t lsmash_count_codec_specific_data( lsmash_summary_t *summary )
{
    if( !summary || !summary->opaque )
        return 0;
    return summary->opaque->list.entry_count;
}

int isom_compare_opaque_extensions( lsmash_summary_t *a, lsmash_summary_t *b )
{
    assert( a && b );
    uint32_t in_number_of_extensions  = lsmash_count_codec_specific_data( a );
    uint32_t out_number_of_extensions = lsmash_count_codec_specific_data( b );
    if( out_number_of_extensions != in_number_of_extensions )
        return 1;
    uint32_t active_number_of_extensions = in_number_of_extensions;
    uint32_t identical_count = 0;
    for( uint32_t j = 1; j <= in_number_of_extensions; j++ )
    {
        lsmash_codec_specific_t *in_cs_orig = lsmash_get_codec_specific_data( a, j );
        lsmash_codec_specific_t *in_cs;
        lsmash_codec_specific_format compare_format = LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED;
        if( in_cs_orig->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
        {
            if( in_cs_orig->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON
             || in_cs_orig->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON
             || in_cs_orig->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_FORMAT_SPECIFIC_FLAGS )
            {
                compare_format = LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED;
                in_cs = in_cs_orig;
            }
            else
            {
                in_cs = lsmash_convert_codec_specific_format( in_cs_orig, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                if( !in_cs )
                {
                    /* We don't support the format converter of this data type. */
                    --active_number_of_extensions;
                    continue;
                }
            }
        }
        else
            in_cs = in_cs_orig;
        for( uint32_t k = 1; k <= out_number_of_extensions; k++ )
        {
            lsmash_codec_specific_t *out_cs_orig = lsmash_get_codec_specific_data( b, k );
            if( out_cs_orig->type != in_cs_orig->type )
                continue;
            lsmash_codec_specific_t *out_cs;
            if( out_cs_orig->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
            {
                if( compare_format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
                    out_cs = out_cs_orig;
                else
                {
                    out_cs = lsmash_convert_codec_specific_format( out_cs_orig, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED );
                    if( !out_cs )
                        continue;
                }
            }
            else
                out_cs = out_cs_orig;
            int identical;
            if( compare_format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED )
                identical = out_cs->size == in_cs->size && !memcmp( out_cs->data.unstructured, in_cs->data.unstructured, in_cs->size );
            else
            {
                if( in_cs->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_VIDEO_COMMON )
                {
                    lsmash_qt_video_common_t *in_data  = (lsmash_qt_video_common_t *)in_cs->data.structured;
                    lsmash_qt_video_common_t *out_data = (lsmash_qt_video_common_t *)out_cs->data.structured;
                    identical = in_data->revision_level        == out_data->revision_level
                             && in_data->vendor                == out_data->vendor
                             && in_data->temporalQuality       == out_data->temporalQuality
                             && in_data->spatialQuality        == out_data->spatialQuality
                             && in_data->horizontal_resolution == out_data->horizontal_resolution
                             && in_data->vertical_resolution   == out_data->vertical_resolution
                             && in_data->dataSize              == out_data->dataSize
                             && in_data->frame_count           == out_data->frame_count
                             && in_data->color_table_ID        == out_data->color_table_ID;
                }
                else if( in_cs->type == LSMASH_CODEC_SPECIFIC_DATA_TYPE_QT_AUDIO_COMMON )
                {
                    lsmash_qt_audio_common_t *in_data  = (lsmash_qt_audio_common_t *)in_cs->data.structured;
                    lsmash_qt_audio_common_t *out_data = (lsmash_qt_audio_common_t *)out_cs->data.structured;
                    identical = in_data->revision_level == out_data->revision_level
                             && in_data->vendor         == out_data->vendor
                             && in_data->compression_ID == out_data->compression_ID;
                }
                else
                {
                    lsmash_qt_audio_format_specific_flags_t *in_data  = (lsmash_qt_audio_format_specific_flags_t *)in_cs->data.structured;
                    lsmash_qt_audio_format_specific_flags_t *out_data = (lsmash_qt_audio_format_specific_flags_t *)out_cs->data.structured;
                    identical = (in_data->format_flags == out_data->format_flags);
                }
            }
            if( out_cs != out_cs_orig )
                lsmash_destroy_codec_specific_data( out_cs );
            if( identical )
            {
                ++identical_count;
                break;
            }
        }
        if( in_cs != in_cs_orig )
            lsmash_destroy_codec_specific_data( in_cs );
    }
    return (identical_count != active_number_of_extensions);
}

int isom_get_implicit_qt_fixed_comp_audio_sample_quants
(
    isom_audio_entry_t *audio,
    uint32_t           *samples_per_packet,
    uint32_t           *constant_bytes_per_frame,
    uint32_t           *sample_size
)
{
    if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_MAC3_AUDIO ) )
    {
        *samples_per_packet       = 6;
        *constant_bytes_per_frame = 2 * audio->channelcount;
        *sample_size              = 8;
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_MAC6_AUDIO ) )
    {
        *samples_per_packet       = 6;
        *constant_bytes_per_frame = audio->channelcount;
        *sample_size              = 8;
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ADPCM17_AUDIO ) )
    {
        *samples_per_packet       = 64;
        *constant_bytes_per_frame = 34 * audio->channelcount;
        *sample_size              = 16;
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_AGSM_AUDIO ) )
    {
        *samples_per_packet       = 160;
        *constant_bytes_per_frame = 33;
        *sample_size              = 16;
    }
    else if( lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ALAW_AUDIO )
          || lsmash_check_codec_type_identical( audio->type, QT_CODEC_TYPE_ULAW_AUDIO ) )
    {
        *samples_per_packet       = 1;
        *constant_bytes_per_frame = audio->channelcount;
        *sample_size              = 16;
    }
    else
        return 0;
    return 1;
}

int hint_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    uint32_t bufferSizeDB;
    uint32_t maxBitrate = 0;
    uint32_t avgBitrate = 0;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    isom_hmhd_t *hmhd = ((isom_mdia_t*)(mdhd->parent))->minf->hmhd;
    hmhd->maxbitrate = maxBitrate;
    hmhd->avgbitrate = avgBitrate;
    hmhd->avgPDUsize = hmhd->PDUcount > 0 ? (hmhd->combinedPDUsize / hmhd->PDUcount) : 0;
    return err;
}

isom_bitrate_updater_t isom_get_bitrate_updater
(
    isom_sample_entry_t *sample_entry
)
{
#define RETURN_BITRATE_UPDATER( func_name )                                                      \
    {                                                                                            \
        extern int func_name( isom_stbl_t *, isom_mdhd_t *, uint32_t sample_description_index ); \
        return func_name;                                                                        \
    }
    lsmash_codec_type_t sample_type = sample_entry->type;
    if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC1_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC2_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC3_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC4_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_HVC1_VIDEO )
     || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_HEV1_VIDEO ) )
        RETURN_BITRATE_UPDATER( nalu_update_bitrate )
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4V_VIDEO ) )
        RETURN_BITRATE_UPDATER( mp4v_update_bitrate )
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4A_AUDIO )
          || lsmash_check_codec_type_identical( sample_type,   QT_CODEC_TYPE_MP4A_AUDIO ) )
        RETURN_BITRATE_UPDATER( mp4a_update_bitrate )
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_ALAC_AUDIO )
          || lsmash_check_codec_type_identical( sample_type,   QT_CODEC_TYPE_ALAC_AUDIO ) )
        RETURN_BITRATE_UPDATER( alac_update_bitrate )
    else if( isom_is_dts_audio( sample_type ) )
        RETURN_BITRATE_UPDATER( dts_update_bitrate )
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_EC_3_AUDIO ) )
        RETURN_BITRATE_UPDATER( eac3_update_bitrate )
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_RRTP_HINT ) )
        RETURN_BITRATE_UPDATER( hint_update_bitrate )
    else if( isom_is_waveform_audio( sample_type ) )
        RETURN_BITRATE_UPDATER( waveform_audio_update_bitrate )
    else
        return NULL;
#undef RETURN_BITRATE_UPDATER
}

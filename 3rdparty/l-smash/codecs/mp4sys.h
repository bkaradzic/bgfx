/*****************************************************************************
 * mp4sys.h
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Takashi Hirata <silverfilain@gmail.com>
 *          Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
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

#ifndef MP4SYS_H
#define MP4SYS_H

/***************************************************************************
    MPEG-4 Systems
***************************************************************************/

/* ODProfileLevelIndication */
typedef enum
{
    MP4SYS_OD_PLI_Forbidden     = 0x00, /* Forbidden */
    MP4SYS_OD_PLI_NOT_SPECIFIED = 0xFE, /* no OD profile specified */
    MP4SYS_OD_PLI_NONE_REQUIRED = 0xFF, /* no OD capability required */
} mp4sys_ODProfileLevelIndication;

/* sceneProfileLevelIndication */
typedef enum
{
    MP4SYS_SCENE_PLI_RESERVED      = 0x00, /* Reserved for ISO use */
    MP4SYS_SCENE_PLI_Simple2D_L1   = 0x01, /* Simple 2D L1 */
    MP4SYS_SCENE_PLI_Simple2D_L2   = 0x02, /* Simple 2D L2 */
    MP4SYS_SCENE_PLI_Audio_L1      = 0x03, /* Audio L1 */
    MP4SYS_SCENE_PLI_Audio_L2      = 0x04, /* Audio L2 */
    MP4SYS_SCENE_PLI_Audio_L3      = 0x05, /* Audio L3 */
    MP4SYS_SCENE_PLI_Audio_L4      = 0x06, /* Audio L4 */
    MP4SYS_SCENE_PLI_3D_Audio_L1   = 0x07, /* 3D Audio L1 */
    MP4SYS_SCENE_PLI_3D_Audio_L2   = 0x08, /* 3D Audio L2 */
    MP4SYS_SCENE_PLI_3D_Audio_L3   = 0x09, /* 3D Audio L3 */
    MP4SYS_SCENE_PLI_3D_Audio_L4   = 0x0A, /* 3D Audio L4 */
    MP4SYS_SCENE_PLI_Basic2D_L1    = 0x0B, /* Basic 2D L1 */
    MP4SYS_SCENE_PLI_Core2D_L1     = 0x0C, /* Core 2D L1 */
    MP4SYS_SCENE_PLI_Core2D_L2     = 0x0D, /* Core 2D L2 */
    MP4SYS_SCENE_PLI_Advanced2D_L1 = 0x0E, /* Advanced 2D L1 */
    MP4SYS_SCENE_PLI_Advanced2D_L2 = 0x0F, /* Advanced 2D L2 */
    MP4SYS_SCENE_PLI_Advanced2D_L3 = 0x10, /* Advanced 2D L3 */
    MP4SYS_SCENE_PLI_Main2D_L1     = 0x11, /* Main 2D L1 */
    MP4SYS_SCENE_PLI_Main2D_L2     = 0x12, /* Main 2D L2 */
    MP4SYS_SCENE_PLI_Main2D_L3     = 0x13, /* Main 2D L3 */
    MP4SYS_SCENE_PLI_NOT_SPECIFIED = 0xFE, /* no scene profile specified */
    MP4SYS_SCENE_PLI_NONE_REQUIRED = 0xFF, /* no scene capability required */
} mp4sys_sceneProfileLevelIndication;

/* 14496-2 Profile and level indication and restrictions */
typedef enum
{
    MP4SYS_VISUAL_PLI_Reserved                       = 0x00, /* 0b00000000, Reserved */
    MP4SYS_VISUAL_PLI_Simple_PL1                     = 0x01, /* 0b00000001, Simple Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Simple_PL2                     = 0x02, /* 0b00000010, Simple Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Simple_PL3                     = 0x03, /* 0b00000011, Simple Profile/Level 3 */
    MP4SYS_VISUAL_PLI_Simple_Scalable_PL1            = 0x11, /* 0b00010001, Simple Scalable Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Simple_Scalable_PL2            = 0x12, /* 0b00010010, Simple Scalable Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Core_PL1                       = 0x21, /* 0b00100001, Core Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Core_PL2                       = 0x22, /* 0b00100010, Core Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Main_PL2                       = 0x32, /* 0b00110010, Main Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Main_PL3                       = 0x33, /* 0b00110011, Main Profile/Level 3 */
    MP4SYS_VISUAL_PLI_Main_PL4                       = 0x34, /* 0b00110100, Main Profile/Level 4 */
    MP4SYS_VISUAL_PLI_N_bit_PL2                      = 0x42, /* 0b01000010, N-bit Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Scalable_Texture_PL1           = 0x51, /* 0b01010001, Scalable Texture Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Simple_Face_Animation_PL1      = 0x61, /* 0b01100001, Simple Face Animation Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Simple_Face_Animation_PL2      = 0x62, /* 0b01100010, Simple Face Animation Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Simple_FBA_PL1                 = 0x63, /* 0b01100011, Simple FBA Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Simple_FBA_PL2                 = 0x64, /* 0b01100100, Simple FBA Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Basic_Animated_Texture_PL1     = 0x71, /* 0b01110001, Basic Animated Texture Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Basic_Animated_Texture_PL2     = 0x72, /* 0b01110010, Basic Animated Texture Profile/Level 2 */
    MP4SYS_VISUAL_PLI_H264_AVC                       = 0x7F, /* ISO/IEC 14496-10 Advanced Video Codec / H.264, defined in ISO/IEC 14496-1:2010 */
                                                             /* NOTE: Some other implementations seem to use 0x15(0b00010101) for AVC, but I think that's wrong. */
    MP4SYS_VISUAL_PLI_Hybrid_PL1                     = 0x81, /* 0b10000001, Hybrid Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Hybrid_PL2                     = 0x82, /* 0b10000010, Hybrid Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Advanced_Real_Time_Simple_PL1  = 0x91, /* 0b10010001, Advanced Real Time Simple Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Advanced_Real_Time_Simple_PL2  = 0x92, /* 0b10010010, Advanced Real Time Simple Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Advanced_Real_Time_Simple_PL3  = 0x93, /* 0b10010011, Advanced Real Time Simple Profile/Level 3 */
    MP4SYS_VISUAL_PLI_Advanced_Real_Time_Simple_PL4  = 0x94, /* 0b10010100, Advanced Real Time Simple Profile/Level 4 */
    MP4SYS_VISUAL_PLI_Core_Scalable_PL1              = 0xA1, /* 0b10100001, Core Scalable Profile/Level1 */
    MP4SYS_VISUAL_PLI_Core_Scalable_PL2              = 0xA2, /* 0b10100010, Core Scalable Profile/Level2 */
    MP4SYS_VISUAL_PLI_Core_Scalable_PL3              = 0xA3, /* 0b10100011, Core Scalable Profile/Level3 */
    MP4SYS_VISUAL_PLI_Advanced_Coding_Efficiency_PL1 = 0xB1, /* 0b10110001, Advanced Coding Efficiency Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Advanced_Coding_Efficiency_PL2 = 0xB2, /* 0b10110010, Advanced Coding Efficiency Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Advanced_Coding_Efficiency_PL3 = 0xB3, /* 0b10110011, Advanced Coding Efficiency Profile/Level 3 */
    MP4SYS_VISUAL_PLI_Advanced_Coding_Efficiency_PL4 = 0xB4, /* 0b10110100, Advanced Coding Efficiency Profile/Level 4 */
    MP4SYS_VISUAL_PLI_Advanced_Core_PL1              = 0xC1, /* 0b11000001, Advanced Core Profile/Level 1 */
    MP4SYS_VISUAL_PLI_Advanced_Core_PL2              = 0xC2, /* 0b11000010, Advanced Core Profile/Level 2 */
    MP4SYS_VISUAL_PLI_Advanced_Scalable_Texture_L1   = 0xD1, /* 0b11010001, Advanced Scalable Texture/Level1 */
    MP4SYS_VISUAL_PLI_Advanced_Scalable_Texture_L2   = 0xD2, /* 0b11010010, Advanced Scalable Texture/Level2 */
    MP4SYS_VISUAL_PLI_Advanced_Scalable_Texture_L3   = 0xD3, /* 0b11010011, Advanced Scalable Texture/Level3 */
    MP4SYS_VISUAL_PLI_NOT_SPECIFIED                  = 0xFE, /* no visual profile specified */
    MP4SYS_VISUAL_PLI_NONE_REQUIRED                  = 0xFF, /* no visual capability required */
} mp4sys_visualProfileLevelIndication;

/* graphicsProfileLevelIndication */
typedef enum
{
    MP4SYS_GRAPHICS_PLI_RESERVED         = 0x00, /* Reserved for ISO use */
    MP4SYS_GRAPHICS_PLI_Simple2D_L1      = 0x01, /* Simple2D profile L1 */
    MP4SYS_GRAPHICS_PLI_Simple2D_Text_L1 = 0x02, /* Simple 2D + Text profile L1 */
    MP4SYS_GRAPHICS_PLI_Simple2D_Text_L2 = 0x03, /* Simple 2D + Text profile L2 */
    MP4SYS_GRAPHICS_PLI_Core2D_L1        = 0x04, /* Core 2D profile L1 */
    MP4SYS_GRAPHICS_PLI_Core2D_L2        = 0x05, /* Core 2D profile L2 */
    MP4SYS_GRAPHICS_PLI_Advanced2D_L1    = 0x06, /* Advanced 2D profile L1 */
    MP4SYS_GRAPHICS_PLI_Advanced2D_L2    = 0x07, /* Advanced 2D profile L2 */
    MP4SYS_GRAPHICS_PLI_NOT_SPECIFIED    = 0xFE, /* no graphics profile specified */
    MP4SYS_GRAPHICS_PLI_NONE_REQUIRED    = 0xFF, /* no graphics capability required */
} mp4sys_graphicsProfileLevelIndication;

/* Just for mp4sys_setup_ES_Descriptor, to facilitate to make ES_Descriptor */
typedef struct
{
    uint16_t ES_ID;                 /* Maybe 0 in stsd(esds), or alternatively, lower 16 bits of the TrackID */
    lsmash_mp4sys_object_type_indication objectTypeIndication;
    lsmash_mp4sys_stream_type            streamType;
    uint32_t bufferSizeDB;          /* byte unit, NOT bit unit. */
    uint32_t maxBitrate;
    uint32_t avgBitrate;            /* 0 if VBR */
    void    *dsi_payload;           /* AudioSpecificConfig or so */
    uint32_t dsi_payload_length ;   /* size of dsi_payload */
} mp4sys_ES_Descriptor_params_t;

struct lsmash_mp4sys_decoder_specific_info_tag
{
    uint8_t *payload;
    uint32_t payload_length;
};

#ifndef MP4SYS_INTERNAL

typedef void mp4sys_descriptor_t;
typedef void mp4sys_ES_Descriptor_t;
typedef void mp4sys_ObjectDescriptor_t;

void mp4sys_remove_descriptor( mp4sys_descriptor_t *descriptor );

/* ES_ID of the ES Descriptor is stored as 0 when the ES Descriptor is built into sample descriptions in MP4 file format
 * since the lower 16 bits of the track_ID is used, instead of ES_ID, for the identifier of the elemental stream within the track. */
mp4sys_ES_Descriptor_t *mp4sys_create_ES_Descriptor( uint16_t ES_ID );
mp4sys_ObjectDescriptor_t *mp4sys_create_ObjectDescriptor( uint16_t ObjectDescriptorID );
int mp4sys_create_ES_ID_Inc( mp4sys_ObjectDescriptor_t *od, uint32_t Track_ID );

int mp4sys_to_InitialObjectDescriptor
(
    mp4sys_ObjectDescriptor_t            *od,
    uint8_t                               include_inline_pli,
    mp4sys_ODProfileLevelIndication       od_pli,
    mp4sys_sceneProfileLevelIndication    scene_pli,
    mp4a_audioProfileLevelIndication      audio_pli,
    mp4sys_visualProfileLevelIndication   visual_pli,
    mp4sys_graphicsProfileLevelIndication graph_pli
);

int mp4sys_update_DecoderConfigDescriptor
(
    mp4sys_ES_Descriptor_t *esd,
    uint32_t                bufferSizeDB,
    uint32_t                maxBitrate,
    uint32_t                avgBitrate
);

uint32_t mp4sys_update_descriptor_size( mp4sys_descriptor_t *descriptor );
int mp4sys_write_descriptor( lsmash_bs_t *bs, mp4sys_descriptor_t *descriptor );
void mp4sys_print_descriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent );
mp4sys_descriptor_t *mp4sys_get_descriptor( lsmash_bs_t *bs, mp4sys_descriptor_t *parent );

int mp4sys_setup_summary_from_DecoderSpecificInfo( lsmash_audio_summary_t *summary, mp4sys_ES_Descriptor_t *esd );

/* to facilitate to make ES_Descriptor */
mp4sys_ES_Descriptor_t *mp4sys_setup_ES_Descriptor( mp4sys_ES_Descriptor_params_t *params );

#endif /* #ifndef MP4SYS_INTERNAL */

#endif /* #ifndef MP4SYS_H */

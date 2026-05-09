/*****************************************************************************
 * dts.c
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
#include <inttypes.h>

#include "core/box.h"

/*****************************************************************************
    ETSI TS 102 114 V1.2.1 (2002-12)
    ETSI TS 102 114 V1.3.1 (2011-08)
    ETSI TS 102 114 V1.4.1 (2012-09)

    IMPLEMENTATION OF DTS AUDIO IN MEDIA FILES BASED ON ISO/IEC 14496
        Document No.: 9302J81100
        Revision: F
        Version: 1.3

    Common File Format & Media Formats Specification Version 2.2 31 July 2015
*****************************************************************************/
#include "dts.h"

#define DTS_MIN_CORE_SIZE           96
#define DTS_MAX_STREAM_CONSTRUCTION 21
#define DTS_SPECIFIC_BOX_MIN_LENGTH 28

typedef enum
{
    DTS_SYNCWORD_CORE           = 0x7FFE8001,
    DTS_SYNCWORD_XCH            = 0x5A5A5A5A,
    DTS_SYNCWORD_XXCH           = 0x47004A03,
    DTS_SYNCWORD_X96K           = 0x1D95F262,
    DTS_SYNCWORD_XBR            = 0x655E315E,
    DTS_SYNCWORD_LBR            = 0x0A801921,
    DTS_SYNCWORD_XLL            = 0x41A29547,
    DTS_SYNCWORD_SUBSTREAM      = 0x64582025,
    DTS_SYNCWORD_SUBSTREAM_CORE = 0x02b09261,
    DTS_SYNCWORD_X              = 0x02000850,
} dts_syncword;

/* Loudspeaker Masks (up to 32-bit) for
 *   - nuCoreSpkrActivityMask
 *   - nuXXChSpkrLayoutMask
 *   - DownMixChMapMask
 *   - nChMask
 *   - nSpkrMask */
typedef enum
{
    DTS_LOUDSPEAKER_MASK32_C    = 0x00000001,    /* Centre in front of listener */
    DTS_LOUDSPEAKER_MASK32_L    = 0x00000002,    /* Left in front */
    DTS_LOUDSPEAKER_MASK32_R    = 0x00000004,    /* Right in front */
    DTS_LOUDSPEAKER_MASK32_LS   = 0x00000008,    /* Left surround on side in rear */
    DTS_LOUDSPEAKER_MASK32_RS   = 0x00000010,    /* Right surround on side in rear */
    DTS_LOUDSPEAKER_MASK32_LFE1 = 0x00000020,    /* Low frequency effects subwoofer */
    DTS_LOUDSPEAKER_MASK32_CS   = 0x00000040,    /* Centre surround in rear */
    DTS_LOUDSPEAKER_MASK32_LSR  = 0x00000080,    /* Left surround in rear */
    DTS_LOUDSPEAKER_MASK32_RSR  = 0x00000100,    /* Right surround in rear */
    DTS_LOUDSPEAKER_MASK32_LSS  = 0x00000200,    /* Left surround on side */
    DTS_LOUDSPEAKER_MASK32_RSS  = 0x00000400,    /* Right surround on side */
    DTS_LOUDSPEAKER_MASK32_LC   = 0x00000800,    /* Between left and centre in front */
    DTS_LOUDSPEAKER_MASK32_RC   = 0x00001000,    /* Between right and centre in front */
    DTS_LOUDSPEAKER_MASK32_LH   = 0x00002000,    /* Left height in front */
    DTS_LOUDSPEAKER_MASK32_CH   = 0x00004000,    /* Centre Height in front */
    DTS_LOUDSPEAKER_MASK32_RH   = 0x00008000,    /* Right Height in front */
    DTS_LOUDSPEAKER_MASK32_LFE2 = 0x00010000,    /* Second low frequency effects subwoofer */
    DTS_LOUDSPEAKER_MASK32_LW   = 0x00020000,    /* Left on side in front */
    DTS_LOUDSPEAKER_MASK32_RW   = 0x00040000,    /* Right on side in front */
    DTS_LOUDSPEAKER_MASK32_OH   = 0x00080000,    /* Over the listener's head */
    DTS_LOUDSPEAKER_MASK32_LHS  = 0x00100000,    /* Left height on side */
    DTS_LOUDSPEAKER_MASK32_RHS  = 0x00200000,    /* Right height on side */
    DTS_LOUDSPEAKER_MASK32_CHR  = 0x00400000,    /* Centre height in rear */
    DTS_LOUDSPEAKER_MASK32_LHR  = 0x00800000,    /* Left height in rear */
    DTS_LOUDSPEAKER_MASK32_RHR  = 0x01000000,    /* Right height in rear */
    DTS_LOUDSPEAKER_MASK32_CL   = 0x02000000,    /* Centre in the plane lower than listener's ears */
    DTS_LOUDSPEAKER_MASK32_LL   = 0x04000000,    /* Left in the plane lower than listener's ears */
    DTS_LOUDSPEAKER_MASK32_RL   = 0x08000000,    /* Right in the plane lower than listener's ears */
} dts_loudspeaker_mask;

/* Loudspeaker Masks (up to 16-bit) for
 *  - nuSpkrActivityMask
 *  - nuStndrSpkrLayoutMask
 *  - nuMixOutChMask
 *  - ChannelLayout of DTSSpecificBox */
typedef enum
{
    DTS_CHANNEL_LAYOUT_C       = 0x0001,    /* Centre in front of listener */
    DTS_CHANNEL_LAYOUT_L_R     = 0x0002,    /* Left/Right in front */
    DTS_CHANNEL_LAYOUT_LS_RS   = 0x0004,    /* Left/Right surround on side in rear */
    DTS_CHANNEL_LAYOUT_LFE1    = 0x0008,    /* Low frequency effects subwoofer */
    DTS_CHANNEL_LAYOUT_CS      = 0x0010,    /* Centre surround in rear */
    DTS_CHANNEL_LAYOUT_LH_RH   = 0x0020,    /* Left/Right height in front */
    DTS_CHANNEL_LAYOUT_LSR_RSR = 0x0040,    /* Left/Right surround in rear */
    DTS_CHANNEL_LAYOUT_CH      = 0x0080,    /* Centre height in front */
    DTS_CHANNEL_LAYOUT_OH      = 0x0100,    /* Over the listener's head */
    DTS_CHANNEL_LAYOUT_LC_RC   = 0x0200,    /* Between left/right and centre in front */
    DTS_CHANNEL_LAYOUT_LW_RW   = 0x0400,    /* Left/Right on side in front */
    DTS_CHANNEL_LAYOUT_LSS_RSS = 0x0800,    /* Left/Right surround on side */
    DTS_CHANNEL_LAYOUT_LFE2    = 0x1000,    /* Second low frequency effects subwoofer */
    DTS_CHANNEL_LAYOUT_LHS_RHS = 0x2000,    /* Left/Right height on side */
    DTS_CHANNEL_LAYOUT_CHR     = 0x4000,    /* Centre height in rear */
    DTS_CHANNEL_LAYOUT_LHR_RHR = 0x8000,    /* Left/Right height in rear */
} dts_channel_layout;

static const lsmash_dts_construction_flag construction_info[DTS_MAX_STREAM_CONSTRUCTION + 1] =
    {
        0,
        DTS_CORE_SUBSTREAM_CORE_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XCH_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XXCH_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_X96_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XXCH_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XBR_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XCH_FLAG  | DTS_EXT_SUBSTREAM_XBR_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XXCH_FLAG | DTS_EXT_SUBSTREAM_XBR_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XXCH_FLAG  | DTS_EXT_SUBSTREAM_XBR_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_X96_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XCH_FLAG  | DTS_EXT_SUBSTREAM_X96_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XXCH_FLAG | DTS_EXT_SUBSTREAM_X96_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XXCH_FLAG  | DTS_EXT_SUBSTREAM_X96_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XLL_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XCH_FLAG  | DTS_EXT_SUBSTREAM_XLL_FLAG,
        DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_X96_FLAG  | DTS_EXT_SUBSTREAM_XLL_FLAG,
        DTS_EXT_SUBSTREAM_XLL_FLAG,
        DTS_EXT_SUBSTREAM_LBR_FLAG,
        DTS_EXT_SUBSTREAM_CORE_FLAG,
        DTS_EXT_SUBSTREAM_CORE_FLAG  | DTS_EXT_SUBSTREAM_XXCH_FLAG,
        DTS_EXT_SUBSTREAM_CORE_FLAG  | DTS_EXT_SUBSTREAM_XLL_FLAG ,
    };

void dts_setup_parser( dts_info_t *info )
{
    dts_extension_info_t *exss = &info->exss[0];
    /* By default the core substream data, if present, has the nuBcCoreExtSSIndex = 0 and the nuBcCoreAssetIndex = 0.
     * Therefore, we can treat as if one extension substream is there even if no extension substreams. */
    exss->nuNumAudioPresnt      = 1;
    exss->nuNumAssets           = 1;
    exss->bBcCorePresent    [0] = 0;
    exss->nuBcCoreExtSSIndex[0] = 0;
    exss->nuBcCoreAssetIndex[0] = 0;
}

struct lsmash_dts_reserved_box_tag
{
    uint32_t size;
    uint8_t *data;
};

int lsmash_append_dts_reserved_box( lsmash_dts_specific_parameters_t *param, const uint8_t *box_data, uint32_t box_size )
{
    if( !param || !box_data || box_size == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !param->box )
    {
        param->box = lsmash_malloc_zero( sizeof(lsmash_dts_reserved_box_t) );
        if( !param->box )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    /* New a DTSExpansionBox. */
    uint32_t size = param->box->size + box_size;
    uint8_t *data = lsmash_realloc( param->box->data, size );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( data + param->box->size, box_data, box_size );
    param->box->data = data;
    param->box->size = size;
    return 0;
}

void lsmash_remove_dts_reserved_box( lsmash_dts_specific_parameters_t *param )
{
    if( !param->box )
        return;
    lsmash_free( param->box->data );
    lsmash_freep( &param->box );
}

void dts_destruct_specific_data( void *data )
{
    if( !data )
        return;
    lsmash_remove_dts_reserved_box( data );
    lsmash_free( data );
}

uint8_t lsmash_dts_get_stream_construction( lsmash_dts_construction_flag flags )
{
    uint8_t StreamConstruction;
    for( StreamConstruction = 1; StreamConstruction <= DTS_MAX_STREAM_CONSTRUCTION; StreamConstruction++ )
        if( flags == construction_info[StreamConstruction] )
            break;
    /* For any stream type not listed in the above table,
     * StreamConstruction shall be set to 0 and the codingname shall default to 'dtsh'. */
    return StreamConstruction <= DTS_MAX_STREAM_CONSTRUCTION ? StreamConstruction : 0;
}

lsmash_dts_construction_flag lsmash_dts_get_construction_flags( uint8_t stream_construction )
{
    if( stream_construction <= DTS_MAX_STREAM_CONSTRUCTION )
        return construction_info[stream_construction];
    return 0;
}

lsmash_codec_type_t lsmash_dts_get_codingname( lsmash_dts_specific_parameters_t *param )
{
    assert( param->StreamConstruction <= DTS_MAX_STREAM_CONSTRUCTION );
    if( param->MultiAssetFlag )
        return ISOM_CODEC_TYPE_DTSH_AUDIO;  /* Multiple asset streams shall use the 'dtsh' coding_name. */
    static lsmash_codec_type_t codingname_table[DTS_MAX_STREAM_CONSTRUCTION + 1] = { LSMASH_CODEC_TYPE_INITIALIZER };
    if( lsmash_check_codec_type_identical( codingname_table[0], LSMASH_CODEC_TYPE_UNSPECIFIED ) )
    {
        int i = 0;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO; /* Undefined stream types shall be set to 0 and the codingname shall default to 'dtsh'. */
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSC_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSC_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSC_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSL_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSE_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
        codingname_table[i++] = ISOM_CODEC_TYPE_DTSH_AUDIO;
    }
    lsmash_codec_type_t codingname = codingname_table[ param->StreamConstruction ];
    /* Check the presence of DTSXParameters Box. */
    if( !lsmash_check_codec_type_identical( codingname, ISOM_CODEC_TYPE_DTSC_AUDIO )
     && !lsmash_check_codec_type_identical( codingname, ISOM_CODEC_TYPE_DTSE_AUDIO )
     && param->box
     && param->box->data
     && param->box->size >= ISOM_FULLBOX_COMMON_SIZE )
    {
        uint8_t *data = param->box->data;
        uint32_t pos  = 0;
        while( pos + ISOM_FULLBOX_COMMON_SIZE <= param->box->size )
        {
            uint32_t size = LSMASH_GET_BE32( &data[0] );
            uint32_t type = LSMASH_GET_BE32( &data[4] );
            if( type == LSMASH_4CC( 'd', 'x', 'p', 'b' ) )
                return ISOM_CODEC_TYPE_DTSX_AUDIO;
            pos += size;
        }
    }
    return codingname;
}

uint8_t *lsmash_create_dts_specific_info( lsmash_dts_specific_parameters_t *param, uint32_t *data_length )
{
    int reserved_box_present = (param->box && param->box->data && param->box->size);
    lsmash_bits_t *bits = lsmash_bits_adhoc_create();
    if( !bits )
        return NULL;
    /* Create a DTSSpecificBox. */
    lsmash_bits_put( bits, 32, 0 );                             /* box size */
    lsmash_bits_put( bits, 32, ISOM_BOX_TYPE_DDTS.fourcc );     /* box type: 'ddts' */
    lsmash_bits_put( bits, 32, param->DTSSamplingFrequency );
    lsmash_bits_put( bits, 32, param->maxBitrate );             /* maxBitrate; setup by isom_update_bitrate_description */
    lsmash_bits_put( bits, 32, param->avgBitrate );             /* avgBitrate; setup by isom_update_bitrate_description */
    lsmash_bits_put( bits, 8, param->pcmSampleDepth );
    lsmash_bits_put( bits, 2, param->FrameDuration );
    lsmash_bits_put( bits, 5, param->StreamConstruction );
    lsmash_bits_put( bits, 1, param->CoreLFEPresent );
    lsmash_bits_put( bits, 6, param->CoreLayout );
    lsmash_bits_put( bits, 14, param->CoreSize );
    lsmash_bits_put( bits, 1, param->StereoDownmix );
    lsmash_bits_put( bits, 3, param->RepresentationType );
    lsmash_bits_put( bits, 16, param->ChannelLayout );
    lsmash_bits_put( bits, 1, param->MultiAssetFlag );
    lsmash_bits_put( bits, 1, param->LBRDurationMod );
    lsmash_bits_put( bits, 1, reserved_box_present );
    lsmash_bits_put( bits, 5, 0 );                              /* Reserved */
    /* ReservedBox */
    if( reserved_box_present )
        for( uint32_t i = 0; i < param->box->size; i++ )
            lsmash_bits_put( bits, 8, param->box->data[i] );
    /* */
    uint8_t *data = lsmash_bits_export_data( bits, data_length );
    lsmash_bits_adhoc_cleanup( bits );
    /* Update box size. */
    LSMASH_SET_BE32( data, *data_length );
    return data;
}

int lsmash_setup_dts_specific_parameters_from_frame( lsmash_dts_specific_parameters_t *param, uint8_t *data, uint32_t data_length )
{
    lsmash_bits_t bits    = { 0 };
    lsmash_bs_t   bs      = { 0 };
    uint8_t buffer[DTS_MAX_EXSS_SIZE] = { 0 };
    bs.buffer.data  = buffer;
    bs.buffer.store = data_length;
    bs.buffer.alloc = DTS_MAX_EXSS_SIZE;
    dts_info_t *info = &(dts_info_t){ .bits = &bits };
    info->bits = &bits;
    lsmash_bits_init( &bits, &bs );
    memcpy( buffer, data, LSMASH_MIN( data_length, DTS_MAX_EXSS_SIZE ) );
    dts_setup_parser( info );
    uint64_t next_frame_pos = 0;
    while( 1 )
    {
        int err;
        /* Seek to the head of the next syncframe. */
        bs.buffer.pos = LSMASH_MIN( data_length, next_frame_pos );
        /* Check the remainder length of the buffer.
         * If there is enough length, then continue to parse the frame in it.
         * The length 10 is the required byte length to get frame size. */
        uint64_t remain_size = lsmash_bs_get_remaining_buffer_size( &bs );
        if( bs.eob || (bs.eof && remain_size < 10) )
            goto setup_param;   /* No more valid data. */
        /* Parse substream frame. */
        dts_substream_type prev_substream_type = info->substream_type;
        info->substream_type = dts_get_substream_type( info );
        int (*dts_parse_frame)( dts_info_t * ) = NULL;
        switch( info->substream_type )
        {
            /* Decide substream frame parser and check if this frame and the previous frame belong to the same AU. */
            case DTS_SUBSTREAM_TYPE_CORE :
                if( prev_substream_type != DTS_SUBSTREAM_TYPE_NONE )
                    goto setup_param;
                dts_parse_frame = dts_parse_core_substream;
                break;
            case DTS_SUBSTREAM_TYPE_EXTENSION :
            {
                uint8_t prev_exss_index = info->exss_index;
                if( (err = dts_get_exss_index( info, &info->exss_index )) < 0 )
                    return err;
                if( prev_substream_type == DTS_SUBSTREAM_TYPE_EXTENSION && info->exss_index <= prev_exss_index )
                    goto setup_param;
                dts_parse_frame = dts_parse_extension_substream;
                break;
            }
            default :
                /* An unknown stream type is detected. */
                return LSMASH_ERR_NAMELESS;
        }
        info->frame_size = 0;
        if( (err = dts_parse_frame( info )) < 0 )
            return err; /* Failed to parse. */
        next_frame_pos += info->frame_size;
    }
setup_param:
    dts_update_specific_param( info );
    *param = info->ddts_param;
    return 0;
}

static inline uint64_t dts_bits_get( lsmash_bits_t *bits, uint32_t width, uint64_t *bits_pos )
{
    *bits_pos += width;
    return lsmash_bits_get( bits, width );
}

static inline void dts_bits_align( lsmash_bits_t *bits, uint64_t *bits_pos )
{
    uint8_t remainder = 8 - (*bits_pos & 0x7);
    (void)dts_bits_get( bits, remainder, bits_pos );
}

static inline void dts_bits_align4( lsmash_bits_t *bits, uint64_t *bits_pos )
{
    uint8_t remainder = 32 - (*bits_pos & 0x1f);
    (void)dts_bits_get( bits, remainder, bits_pos );
}

static int dts_get_channel_count_from_channel_layout( uint16_t channel_layout )
{
#define DTS_CHANNEL_PAIR_MASK      \
       (DTS_CHANNEL_LAYOUT_L_R     \
      | DTS_CHANNEL_LAYOUT_LS_RS   \
      | DTS_CHANNEL_LAYOUT_LH_RH   \
      | DTS_CHANNEL_LAYOUT_LSR_RSR \
      | DTS_CHANNEL_LAYOUT_LC_RC   \
      | DTS_CHANNEL_LAYOUT_LW_RW   \
      | DTS_CHANNEL_LAYOUT_LSS_RSS \
      | DTS_CHANNEL_LAYOUT_LHS_RHS \
      | DTS_CHANNEL_LAYOUT_LHR_RHR)
    return lsmash_count_bits( channel_layout )
         + lsmash_count_bits( channel_layout & DTS_CHANNEL_PAIR_MASK );
#undef DTS_CHANNEL_PAIR_MASK
}

static uint32_t dts_get_channel_layout_from_ls_mask32( uint32_t mask )
{
    uint32_t layout = 0;
    if( mask & DTS_LOUDSPEAKER_MASK32_C )
        layout |= DTS_CHANNEL_LAYOUT_C;
    if( mask & (DTS_LOUDSPEAKER_MASK32_L | DTS_LOUDSPEAKER_MASK32_R) )
        layout |= DTS_CHANNEL_LAYOUT_L_R;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LS | DTS_LOUDSPEAKER_MASK32_RS) )
        layout |= DTS_CHANNEL_LAYOUT_LS_RS;
    if( mask & DTS_LOUDSPEAKER_MASK32_LFE1 )
        layout |= DTS_CHANNEL_LAYOUT_LFE1;
    if( mask & DTS_LOUDSPEAKER_MASK32_CS )
        layout |= DTS_CHANNEL_LAYOUT_CS;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LH | DTS_LOUDSPEAKER_MASK32_RH) )
        layout |= DTS_CHANNEL_LAYOUT_LH_RH;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LSR | DTS_LOUDSPEAKER_MASK32_RSR) )
        layout |= DTS_CHANNEL_LAYOUT_LSR_RSR;
    if( mask & DTS_LOUDSPEAKER_MASK32_CH )
        layout |= DTS_CHANNEL_LAYOUT_CH;
    if( mask & DTS_LOUDSPEAKER_MASK32_OH )
        layout |= DTS_CHANNEL_LAYOUT_OH;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LC | DTS_LOUDSPEAKER_MASK32_RC) )
        layout |= DTS_CHANNEL_LAYOUT_LC_RC;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LW | DTS_LOUDSPEAKER_MASK32_RW) )
        layout |= DTS_CHANNEL_LAYOUT_LW_RW;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LSS | DTS_LOUDSPEAKER_MASK32_RSS) )
        layout |= DTS_CHANNEL_LAYOUT_LSS_RSS;
    if( mask & DTS_LOUDSPEAKER_MASK32_LFE2 )
        layout |= DTS_CHANNEL_LAYOUT_LFE2;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LHS | DTS_LOUDSPEAKER_MASK32_RHS) )
        layout |= DTS_CHANNEL_LAYOUT_LHS_RHS;
    if( mask & DTS_LOUDSPEAKER_MASK32_CHR )
        layout |= DTS_CHANNEL_LAYOUT_CHR;
    if( mask & (DTS_LOUDSPEAKER_MASK32_LHR | DTS_LOUDSPEAKER_MASK32_RHR) )
        layout |= DTS_CHANNEL_LAYOUT_LHR_RHR;
    return layout;
}

/* for channels which cannot be expressed by ChannelLayout; CL, LL and RL */
static inline uint8_t dts_get_lower_channels_from_ls_mask32( uint32_t mask )
{
    return (mask >> 25) & 0x7;
}

static void dts_parse_xll_navigation( lsmash_bits_t *bits, dts_xll_info_t *xll, int nuBits4ExSSFsize, uint64_t *bits_pos )
{
    xll->size = dts_bits_get( bits, nuBits4ExSSFsize, bits_pos ) + 1;                   /* nuExSSXLLFsize        (nuBits4ExSSFsize) */
    if( dts_bits_get( bits, 1, bits_pos ) )                                             /* bExSSXLLSyncPresent   (1) */
    {
        dts_bits_get( bits, 4, bits_pos );                                              /* nuPeakBRCntrlBuffSzkB (4) */
        int nuBitsInitDecDly = dts_bits_get( bits, 5, bits_pos ) + 1;                   /* nuBitsInitDecDly      (5) */
        dts_bits_get( bits, nuBitsInitDecDly, bits_pos );                               /* nuInitLLDecDlyFrames  (nuBitsInitDecDly) */
        dts_bits_get( bits, nuBits4ExSSFsize, bits_pos );                               /* nuExSSXLLSyncOffset   (nuBits4ExSSFsize) */
    }
}

static void dts_parse_lbr_navigation( lsmash_bits_t *bits, dts_lbr_info_t *lbr, uint64_t *bits_pos )
{
    lbr->size = dts_bits_get( bits, 14, bits_pos );   /* nuExSSLBRFsize            (14) */
    if( dts_bits_get( bits, 1, bits_pos ) )           /* bExSSLBRSyncPresent       (1) */
        dts_bits_get( bits, 2, bits_pos );            /* nuExSSLBRSyncDistInFrames (2) */
}

static int dts_parse_asset_descriptor( dts_info_t *info, uint64_t *bits_pos )
{
    lsmash_bits_t        *bits = info->bits;
    dts_extension_info_t *exss = &info->exss[ info->exss_index ];
    /* Audio asset descriptor */
    uint64_t asset_descriptor_pos = *bits_pos;
    int nuAssetDescriptFsize = dts_bits_get( bits, 9, bits_pos ) + 1;                               /* nuAssetDescriptFsize          (9) */
    dts_audio_asset_t *asset = &exss->asset[ dts_bits_get( bits, 3, bits_pos ) ];                   /* nuAssetIndex                  (3) */
    /* Static metadata */
    int bEmbeddedStereoFlag = 0;
    int bEmbeddedSixChFlag  = 0;
    int nuTotalNumChs       = 0;
    if( exss->bStaticFieldsPresent )
    {
        if( dts_bits_get( bits, 1, bits_pos ) )                                                     /* bAssetTypeDescrPresent        (1)*/
            dts_bits_get( bits, 4, bits_pos );                                                      /* nuAssetTypeDescriptor         (4) */
        if( dts_bits_get( bits, 1, bits_pos ) )                                                     /* bLanguageDescrPresent         (1) */
            dts_bits_get( bits, 24, bits_pos );                                                     /* LanguageDescriptor            (24) */
        if( dts_bits_get( bits, 1, bits_pos ) )
        {
            int nuInfoTextByteSize = dts_bits_get( bits, 10, bits_pos ) + 1;                        /* nuInfoTextByteSize            (10) */
            dts_bits_get( bits, nuInfoTextByteSize * 8, bits_pos );                                 /* InfoTextString                (nuInfoTextByteSize) */
        }
        int nuBitResolution = dts_bits_get( bits, 5, bits_pos ) + 1;                                /* nuBitResolution               (5) */
        exss->bit_resolution = LSMASH_MAX( exss->bit_resolution, nuBitResolution );
        int nuMaxSampleRate = dts_bits_get( bits, 4, bits_pos );                                    /* nuMaxSampleRate               (4) */
        static const uint32_t source_sample_rate_table[16] =
            {
                 8000, 16000, 32000, 64000, 128000,
                       22050, 44100, 88200, 176400, 352800,
                12000, 24000, 48000, 96000, 192000, 384000
            };
        exss->sampling_frequency = LSMASH_MAX( exss->sampling_frequency, source_sample_rate_table[nuMaxSampleRate] );
        nuTotalNumChs = dts_bits_get( bits, 8, bits_pos ) + 1;                                      /* nuTotalNumChs                 (8) */
        asset->bOne2OneMapChannels2Speakers = dts_bits_get( bits, 1, bits_pos );                    /* bOne2OneMapChannels2Speakers  (1) */
        if( asset->bOne2OneMapChannels2Speakers )
        {
            if( nuTotalNumChs > 2 )
            {
                bEmbeddedStereoFlag = dts_bits_get( bits, 1, bits_pos );                            /* bEmbeddedStereoFlag           (1) */
                exss->stereo_downmix |= bEmbeddedStereoFlag;
            }
            if( nuTotalNumChs > 6 )
                bEmbeddedSixChFlag = dts_bits_get( bits, 1, bits_pos );                             /* bEmbeddedSixChFlag            (1) */
            int nuNumBits4SAMask;
            if( dts_bits_get( bits, 1, bits_pos ) )                                                 /* bSpkrMaskEnabled              (1) */
            {
                nuNumBits4SAMask = (dts_bits_get( bits, 2, bits_pos ) + 1) << 2;                    /* nuNumBits4SAMask              (2) */
                asset->channel_layout |= dts_bits_get( bits, nuNumBits4SAMask, bits_pos );          /* nuSpkrActivityMask            (nuNumBits4SAMask) */
            }
            else
                /* The specification doesn't mention the value of nuNumBits4SAMask if bSpkrMaskEnabled is set to 0. */
                nuNumBits4SAMask = 16;
            int nuNumSpkrRemapSets = dts_bits_get( bits, 3, bits_pos );
            int nuStndrSpkrLayoutMask[8] = { 0 };
            for( int ns = 0; ns < nuNumSpkrRemapSets; ns++ )
                nuStndrSpkrLayoutMask[ns] = dts_bits_get( bits, nuNumBits4SAMask, bits_pos );
            for( int ns = 0; ns < nuNumSpkrRemapSets; ns++ )
            {
                int nuNumSpeakers    = dts_get_channel_count_from_channel_layout( nuStndrSpkrLayoutMask[ns] );
                int nuNumDecCh4Remap = dts_bits_get( bits, 5, bits_pos ) + 1;                       /* nuNumDecCh4Remap[ns]          (5) */
                for( int nCh = 0; nCh < nuNumSpeakers; nCh++ )
                {
                    uint32_t nuRemapDecChMask = dts_bits_get( bits, nuNumDecCh4Remap, bits_pos );
                    int nCoef = lsmash_count_bits( nuRemapDecChMask );
                    for( int nc = 0; nc < nCoef; nc++ )
                        dts_bits_get( bits, 5, bits_pos );                                          /* nuSpkrRemapCodes[ns][nCh][nc] (5) */
                }
            }
        }
        else
        {
            asset->nuRepresentationType = dts_bits_get( bits, 3, bits_pos );                        /* nuRepresentationType          (3) */
            if( asset->nuRepresentationType == 2
             || asset->nuRepresentationType == 3 )
                nuTotalNumChs = 2;
        }
    }
    /* Dynamic metadata */
    int bDRCCoefPresent = dts_bits_get( bits, 1, bits_pos );                                        /* bDRCCoefPresent               (1) */
    if( bDRCCoefPresent )
        dts_bits_get( bits, 8, bits_pos );                                                          /* nuDRCCode                     (8) */
    if( dts_bits_get( bits, 1, bits_pos ) )                                                         /* bDialNormPresent              (1) */
        dts_bits_get( bits, 5, bits_pos );                                                          /* nuDialNormCode                (5) */
    if( bDRCCoefPresent && bEmbeddedStereoFlag )
        dts_bits_get( bits, 8, bits_pos );                                                          /* nuDRC2ChDmixCode              (8) */
    int bMixMetadataPresent;
    if( exss->bMixMetadataEnbl )
        bMixMetadataPresent = dts_bits_get( bits, 1, bits_pos );                                    /* bMixMetadataPresent           (1) */
    else
        bMixMetadataPresent = 0;
    if( bMixMetadataPresent )
    {
        dts_bits_get( bits, 7, bits_pos );                                                          /* bExternalMixFlag              (1)
                                                                                                     * nuPostMixGainAdjCode          (7) */
        if( dts_bits_get( bits, 2, bits_pos ) < 3 )                                                 /* nuControlMixerDRC             (2) */
            dts_bits_get( bits, 3, bits_pos );                                                      /* nuLimit4EmbeddedDRC           (3) */
        else
            dts_bits_get( bits, 8, bits_pos );                                                      /* nuCustomDRCCode               (8) */
        int bEnblPerChMainAudioScale = dts_bits_get( bits, 1, bits_pos );                           /* bEnblPerChMainAudioScale      (1) */
        for( uint8_t ns = 0; ns < exss->nuNumMixOutConfigs; ns++ )
            if( bEnblPerChMainAudioScale )
                for( uint8_t nCh = 0; nCh < exss->nNumMixOutCh[ns]; nCh++ )
                    dts_bits_get( bits, 6, bits_pos );                                              /* nuMainAudioScaleCode[ns][nCh] (6) */
            else
                dts_bits_get( bits, 6, bits_pos );                                                  /* nuMainAudioScaleCode[ns][0]   (6) */
        int nEmDM = 1;
        int nDecCh[3] = { nuTotalNumChs, 0, 0 };
        if( bEmbeddedSixChFlag )
        {
            nDecCh[nEmDM] = 6;
            ++nEmDM;
        }
        if( bEmbeddedStereoFlag )
        {
            nDecCh[nEmDM] = 2;
            ++nEmDM;
        }
        for( uint8_t ns = 0; ns < exss->nuNumMixOutConfigs; ns++ )
            for( int nE = 0; nE < nEmDM; nE++ )
                for( int nCh = 0; nCh < nDecCh[nE]; nCh++ )
                {
                    int nuMixMapMask = dts_bits_get( bits, exss->nNumMixOutCh[ns], bits_pos );      /* nuMixMapMask                  (nNumMixOutCh[ns]) */
                    int nuNumMixCoefs = lsmash_count_bits( nuMixMapMask );
                    for( int nC = 0; nC < nuNumMixCoefs; nC++ )
                        dts_bits_get( bits, 6, bits_pos );                                          /* nuMixCoeffs[ns][nE][nCh][nC]  (6) */
                }
    }
    /* Decoder navigation data */
    asset->nuCodingMode = dts_bits_get( bits, 2, bits_pos );                                        /* nuCodingMode                  (2) */
    switch( asset->nuCodingMode )
    {
        case 0 : /* DTS-HD Coding Mode that may contain multiple coding components */
        {
            int nuCoreExtensionMask = dts_bits_get( bits, 12, bits_pos );                           /* nuCoreExtensionMask           (12) */
            asset->nuCoreExtensionMask = nuCoreExtensionMask;
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_CORE_FLAG )
            {
                asset->core.frame_size = dts_bits_get( bits, 14, bits_pos ) + 1;                    /* nuExSSCoreFsize               (14) */
                if( dts_bits_get( bits, 1, bits_pos ) )                                             /* bExSSCoreSyncPresent          (1) */
                    dts_bits_get( bits, 2, bits_pos );                                              /* nuExSSCoreSyncDistInFrames    (2) */
            }
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XBR_FLAG )
                asset->xbr_size = dts_bits_get( bits, 14, bits_pos ) + 1;
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XXCH_FLAG )
                asset->core.xxch.size = dts_bits_get( bits, 14, bits_pos ) + 1;
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_X96_FLAG )
                asset->x96_size = dts_bits_get( bits, 12, bits_pos ) + 1;
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_LBR_FLAG )
                dts_parse_lbr_navigation( bits, &asset->lbr, bits_pos );
            if( nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XLL_FLAG )
                dts_parse_xll_navigation( bits, &asset->xll, exss->nuBits4ExSSFsize, bits_pos );
            break;
        }
        case 1 : /* DTS-HD Loss-less coding mode without CBR component */
            dts_parse_xll_navigation( bits, &asset->xll, exss->nuBits4ExSSFsize, bits_pos );
            break;
        case 2 : /* DTS-HD Low bit-rate mode */
            dts_parse_lbr_navigation( bits, &asset->lbr, bits_pos );
            break;
        case 3 : /* Auxiliary coding mode */
            asset->aux_size = dts_bits_get( bits, 14, bits_pos ) + 1;                               /* nuExSSAuxFsize                (14) */
            break;
        default :
            assert( 0 );
            break;
    }
    dts_bits_get( bits, nuAssetDescriptFsize * 8 - (*bits_pos - asset_descriptor_pos), bits_pos );  /* Skip remaining part of Audio asset descriptor. */
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_xxch( dts_info_t *info, uint64_t *bits_pos, dts_xxch_info_t *xxch )
{
    lsmash_bits_t *bits = info->bits;
    /* XXCH Frame Header */
    uint64_t xxch_pos = *bits_pos - 32;                                                 /* SYNCXXCh                       (32) */
    uint64_t nuHeaderSizeXXCh       = dts_bits_get( bits, 6, bits_pos ) + 1;            /* nuHeaderSizeXXCh               (6) */
    dts_bits_get( bits, 1, bits_pos );                                                  /* bCRCPresent4ChSetHeaderXXCh    (1) */
    int nuBits4SpkrMaskXXCh         = dts_bits_get( bits, 5, bits_pos ) + 1;            /* nuBits4SpkrMaskXXCh            (5) */
    int nuNumChSetsInXXCh           = dts_bits_get( bits, 2, bits_pos ) + 1;            /* nuNumChSetsInXXCh              (2) */
    for( int nChSet = 0; nChSet < nuNumChSetsInXXCh; nChSet++ )
        dts_bits_get( bits, 14, bits_pos );                                             /* pnuChSetFsizeXXCh[nChSet] - 1  (14) */
    /* A 5.1 decoder uses this AMODE to configure its decoded outputs to C, L, R, Ls and Rs layout.
     * On the other hand a 7.1 decoder ignores the AMODE information from the core stream and uses
     * instead the nuCoreSpkrActivityMask (C, L, R, LFE1, Lss and Rss) and the nuXXChSpkrLayoutMask
     * (Lsr and Rsr) from the XXCh stream to get the original 7.1 speaker layout (C, L, R, LFE1, Lss,
     * Rsr, Lsr and Rsr) and configures its outputs accordingly. */
    uint32_t xxch_mask = dts_bits_get( bits, nuBits4SpkrMaskXXCh, bits_pos );           /* nuCoreSpkrActivityMask         (nuBits4SpkrMaskXXCh) */
    xxch->channel_layout |= dts_get_channel_layout_from_ls_mask32( xxch_mask );
    xxch->lower_planes    = dts_get_lower_channels_from_ls_mask32( xxch_mask );
    dts_bits_get( bits, nuHeaderSizeXXCh * 8 - (*bits_pos - xxch_pos), bits_pos );      /* Skip remaining part of XXCH Frame Header. */
    for( int nChSet = 0; nChSet < nuNumChSetsInXXCh; nChSet++ )
    {
        /* XXCH Channel Set Header */
        xxch_pos = *bits_pos;
        uint64_t nuXXChChSetHeaderSize = dts_bits_get( bits, 7, bits_pos ) + 1;         /* nuXXChChSetHeaderSize          (7)*/
        dts_bits_get( bits, 3, bits_pos );                                              /* nuChInChSetXXCh                (3) */
        if( nuBits4SpkrMaskXXCh > 6 )
        {
            xxch_mask = dts_bits_get( bits, nuBits4SpkrMaskXXCh - 6, bits_pos ) << 6;   /* nuXXChSpkrLayoutMask           (nuBits4SpkrMaskXXCh - 6) */
            xxch->channel_layout |= dts_get_channel_layout_from_ls_mask32( xxch_mask );
            xxch->lower_planes   |= dts_get_lower_channels_from_ls_mask32( xxch_mask );
        }
#if 0   /* FIXME: Can we detect stereo downmixing from only XXCH data within the core substream? */
        if( dts_bits_get( bits, 1, bits_pos ) )                                         /* bDownMixCoeffCodeEmbedded      (1) */
        {
            int bDownMixEmbedded = dts_bits_get( bits, 1, bits_pos );                   /* bDownMixEmbedded               (1) */
            dts_bits_get( bits, 6, bits_pos );                                          /* nDmixScaleFactor               (6) */
            uint32_t DownMixChMapMask[8];
            for( int nCh = 0; nCh < nuChInChSetXXCh; nCh++ )
                DownMixChMapMask[nCh] = dts_bits_get( bits, nuBits4SpkrMaskXXCh, bits_pos );
        }
#endif
        dts_bits_get( bits, nuXXChChSetHeaderSize * 8 - (*bits_pos - xxch_pos), bits_pos );     /* Skip remaining part of XXCH Channel Set Header. */
    }
    return 0;
}

static int dts_parse_core_xxch( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    if( core->extension_audio_descriptor == 0
     || core->extension_audio_descriptor == 3 )
        return LSMASH_ERR_INVALID_DATA;
    int err = dts_parse_xxch( info, bits_pos, &core->xxch );
    if( err < 0 )
        return err;
    info->flags |= DTS_CORE_SUBSTREAM_XXCH_FLAG;
    return info->bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_xxch( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    lsmash_bits_t *bits = info->bits;
    if( DTS_SYNCWORD_XXCH != dts_bits_get( bits, 32, bits_pos ) )
        return LSMASH_ERR_INVALID_DATA;
    int err = dts_parse_xxch( info, bits_pos, &core->xxch );
    if( err < 0 )
        return err;
    info->flags |= DTS_EXT_SUBSTREAM_XXCH_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_core_x96( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    if( core->extension_audio_descriptor != 2
     && core->extension_audio_descriptor != 3 )
        return 0;   /* Probably this is not an X96 extension. We skip this anyway. */
    lsmash_bits_t *bits = info->bits;
    /* DTS_BCCORE_X96 Frame Header */
                                            /* SYNCX96 (32) */
    /* To reduce the probability of false synchronization caused by the presence of pseudo sync words, it is
     * imperative to check the distance between the detected sync word and the end of current frame. This
     * distance in bytes shall match the value of FSIZE96. */
    uint64_t FSIZE96 = ((lsmash_bs_show_byte( bits->bs, 0 ) << 4)
                     | ((lsmash_bs_show_byte( bits->bs, 1 ) >> 4) & 0x0F)) + 1;
    if( core->frame_size * 8 != (*bits_pos - 32 + FSIZE96 * 8) )
        return 0;       /* Encountered four emulation bytes (pseudo sync word). */
    dts_bits_get( bits, 16, bits_pos );     /* FSIZE96 (12)
                                             * REVNO   (4) */
    core->sampling_frequency *= 2;
    core->frame_duration     *= 2;
    info->flags |= DTS_CORE_SUBSTREAM_X96_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_core_xch( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    if( core->extension_audio_descriptor != 0
     && core->extension_audio_descriptor != 3 )
        return 0;   /* Probably this is not an XCh extension. We skip this anyway. */
    lsmash_bits_t *bits = info->bits;
    /* XCH Frame Header */
                                                                                /* XChSYNC  (32) */
    /* For compatibility reasons with legacy bitstreams the estimated distance in bytes is checked against
     * the XChFSIZE+1 as well as the XChFSIZE. The XCh synchronization is pronounced if the distance matches
     * either of these two values. */
    uint64_t XChFSIZE = (lsmash_bs_show_byte( bits->bs, 0 ) << 2)
                      | ((lsmash_bs_show_byte( bits->bs, 1 ) >> 6) & 0x03);
    if( core->frame_size * 8 != (*bits_pos - 32 + (XChFSIZE + 1) * 8)
     && core->frame_size * 8 != (*bits_pos - 32 +  XChFSIZE      * 8) )
        return 0;       /* Encountered four emulation bytes (pseudo sync word). */
    if( ((lsmash_bs_show_byte( bits->bs, 1 ) >> 2) & 0xF) != 1 )
        return 0;       /* A known value of AMODE is only 1. Otherwise just skip. */
    dts_bits_get( bits, 16, bits_pos );                                         /* XChFSIZE   (10)
                                                                                 * AMODE      (4)
                                                                                 * byte align (2) */
    core->channel_layout |= DTS_CHANNEL_LAYOUT_CS;
    info->flags |= DTS_CORE_SUBSTREAM_XCH_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_xbr( dts_info_t *info, uint64_t *bits_pos )
{
    lsmash_bits_t *bits = info->bits;
    /* XBR Frame Header */
    uint64_t xbr_pos = *bits_pos;
    if( DTS_SYNCWORD_XBR != dts_bits_get( bits, 32, bits_pos ) )            /* SYNCXBR        (32) */
        return LSMASH_ERR_INVALID_DATA;
    uint64_t nHeaderSizeXBR = dts_bits_get( bits, 6, bits_pos ) + 1;        /* nHeaderSizeXBR (6) */
    dts_bits_get( bits, nHeaderSizeXBR * 8 - (*bits_pos - xbr_pos), bits_pos );     /* Skip the remaining bits in XBR Frame Header. */
    info->flags |= DTS_EXT_SUBSTREAM_XBR_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_x96( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    lsmash_bits_t *bits = info->bits;
    /* DTS_EXSUB_STREAM_X96 Frame Header */
    uint64_t x96_pos = *bits_pos;
    if( DTS_SYNCWORD_X96K != dts_bits_get( bits, 32, bits_pos ) )           /* SYNCX96        (32) */
        return LSMASH_ERR_INVALID_DATA;
    uint64_t nHeaderSizeX96 = dts_bits_get( bits, 6, bits_pos ) + 1;        /* nHeaderSizeXBR (6) */
    dts_bits_get( bits, nHeaderSizeX96 * 8 - (*bits_pos - x96_pos), bits_pos );     /* Skip the remaining bits in DTS_EXSUB_STREAM_X96 Frame Header. */
    /* What the fuck! The specification drops 'if' sentence.
     * We assume the same behaviour for core substream. */
    core->sampling_frequency *= 2;
    core->frame_duration     *= 2;
    info->flags |= DTS_EXT_SUBSTREAM_X96_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_lbr( dts_info_t *info, uint64_t *bits_pos, dts_audio_asset_t *asset )
{
    lsmash_bits_t  *bits = info->bits;
    dts_lbr_info_t *lbr  = &asset->lbr;
    if( DTS_SYNCWORD_LBR != dts_bits_get( bits, 32, bits_pos ) )        /* SYNCEXTLBR              (32) */
        return LSMASH_ERR_INVALID_DATA;
    int ucFmtInfoCode = dts_bits_get( bits, 8, bits_pos );
    if( ucFmtInfoCode == 2 )
    {
        /* LBR decoder initialization data */
        int nLBRSampleRateCode  = dts_bits_get( bits, 8, bits_pos );    /* nLBRSampleRateCode      (8) */
        int usLBRSpkrMask       = dts_bits_get( bits, 16, bits_pos );   /* usLBRSpkrMask           (16) */
        dts_bits_get( bits, 16, bits_pos );                             /* nLBRversion             (16) */
        int nLBRCompressedFlags = dts_bits_get( bits, 8, bits_pos );    /* nLBRCompressedFlags     (8) */
        dts_bits_get( bits, 40, bits_pos );                             /* nLBRBitRateMSnybbles    (8)
                                                                         * nLBROriginalBitRate_LSW (16)
                                                                         * nLBRScaledBitRate_LSW   (16) */
        static const uint32_t source_sample_rate_table[16] =
            {
                 8000, 16000, 32000, 0, 0,
                11025, 22050, 44100, 0, 0,
                12000, 24000, 48000, 0, 0, 0
            };
        enum LBRFlags
        {
            LBR_FLAG_24_BIT_SAMPLES       = 0x01,   /* 0b00000001 */
            LBR_FLAG_USE_LFE              = 0x02,   /* 0b00000010 */
            LBR_FLAG_BANDLMT_MASK         = 0x1C,   /* 0b00011100 */
            LBR_FLAG_STEREO_DOWNMIX       = 0x20,   /* 0b00100000 */
            LBR_FLAG_MULTICHANNEL_DOWNMIX = 0x40,   /* 0b01000000 */
        };
        lbr->sampling_frequency = source_sample_rate_table[nLBRSampleRateCode];
        lbr->frame_duration     = lbr->sampling_frequency < 16000 ? 1024
                                : lbr->sampling_frequency < 32000 ? 2048
                                :                                   4096;
        lbr->channel_layout     = ((usLBRSpkrMask >> 8) & 0xff) | ((usLBRSpkrMask << 8) & 0xff00);  /* usLBRSpkrMask is little-endian. */
        lbr->stereo_downmix    |= !!(nLBRCompressedFlags & LBR_FLAG_STEREO_DOWNMIX);
        lbr->lfe_present       |= !!(nLBRCompressedFlags & LBR_FLAG_USE_LFE);
        lbr->duration_modifier |= ((nLBRCompressedFlags & LBR_FLAG_BANDLMT_MASK) == 0x04)
                               || ((nLBRCompressedFlags & LBR_FLAG_BANDLMT_MASK) == 0x0C);
        lbr->sample_size        = (nLBRCompressedFlags & LBR_FLAG_24_BIT_SAMPLES) ? 24 : 16;
    }
    else if( ucFmtInfoCode != 1 )
        return LSMASH_ERR_NAMELESS; /* unknown */
    info->flags |= DTS_EXT_SUBSTREAM_LBR_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_xll( dts_info_t *info, uint64_t *bits_pos, dts_audio_asset_t *asset )
{
    lsmash_bits_t  *bits = info->bits;
    dts_xll_info_t *xll  = &asset->xll;
    /* Common Header */
    uint64_t xll_pos = *bits_pos;
    if( DTS_SYNCWORD_XLL != dts_bits_get( bits, 32, bits_pos ) )                                /* SYNCXLL                        (32) */
        return LSMASH_ERR_INVALID_DATA;
    dts_bits_get( bits, 4, bits_pos );                                                          /* nVersion                       (4) */
    uint64_t nHeaderSize       = dts_bits_get( bits, 8, bits_pos ) + 1;                         /* nHeaderSize                    (8) */
    int      nBits4FrameFsize  = dts_bits_get( bits, 5, bits_pos ) + 1;                         /* nBits4FrameFsize               (5) */
    dts_bits_get( bits, nBits4FrameFsize, bits_pos );                                           /* nLLFrameSize                   (nBits4FrameFsize) */
    int      nNumChSetsInFrame = dts_bits_get( bits, 4, bits_pos ) + 1;                         /* nNumChSetsInFrame              (4) */
    uint16_t nSegmentsInFrame  = 1 << dts_bits_get( bits, 4, bits_pos );                        /* nSegmentsInFrame               (4) */
    uint16_t nSmplInSeg        = 1 << dts_bits_get( bits, 4, bits_pos );                        /* nSmplInSeg                     (4) */
    int      nBits4SSize       = dts_bits_get( bits, 5, bits_pos ) + 1;                         /* nBits4SSize                    (5) */
    dts_bits_get( bits, 3, bits_pos );                                                          /* nBandDataCRCEn                 (2)
                                                                                                 * bScalableLSBs                  (1) */
    int nBits4ChMask = dts_bits_get( bits, 5, bits_pos ) + 1;                                   /* nBits4ChMask                   (5) */
    dts_bits_get( bits, nHeaderSize * 8 - (*bits_pos - xll_pos), bits_pos );    /* Skip the remaining bits in Common Header. */
    int      sum_nChSetLLChannel       = 0;
    uint32_t nFs1                      = 0;
    int      number_of_frequency_bands = 0; /* the number of frequency bands is determined simply by the underlying maximum sampling
                                             * frequency among all of the channel sets.
                                             * For sampling frequency Fs,
                                             *   Number of frequency bands is 1 for Fs <= Base_Fs
                                             *   Number of frequency bands is 2 for Base_Fs < Fs <= 2 * Base_Fs
                                             *   Number of frequency bands is 2 for 2 * Base_Fs < Fs <= 4 * Base_Fs
                                             * where Base_Fs denotes the base sampling frequency i.e. 64 kHz, 88.2 kHz, or 96 kHz. */
    int      nNumFreqBands1            = 0;
    int      nNumFreqBands[16]         = { 0 };
    xll->channel_layout = 0;
    for( int nChSet = 0; nChSet < nNumChSetsInFrame; nChSet++ )
    {
        /* Channel Set Sub-Header */
        xll_pos = *bits_pos;
        uint64_t nChSetHeaderSize = dts_bits_get( bits, 10, bits_pos ) + 1;                     /* nChSetHeaderSize               (10) */
        int nChSetLLChannel = dts_bits_get( bits, 4, bits_pos ) + 1;                            /* nChSetLLChannel                (4) */
        dts_bits_get( bits, nChSetLLChannel, bits_pos );                                        /* nResidualChEncode              (nChSetLLChannel) */
        uint8_t nBitResolution = dts_bits_get( bits, 5, bits_pos ) + 1;                         /* nBitResolution                 (5) */
        dts_bits_get( bits, 5, bits_pos );                                                      /* nBitWidth                      (5) */
        xll->pcm_resolution = LSMASH_MAX( xll->pcm_resolution, nBitResolution );
        static const uint32_t source_sample_rate_table[16] =
            {
                 8000, 16000, 32000, 64000, 128000,
                       22050, 44100, 88200, 176400, 352800,
                12000, 24000, 48000, 96000, 192000, 384000
            };
        int sFreqIndex = dts_bits_get( bits, 4, bits_pos );                                     /* sFreqIndex                     (4) */
        uint32_t nFs = source_sample_rate_table[sFreqIndex];
        dts_bits_get( bits, 2, bits_pos );                                                      /* nFsInterpolate                 (2) */
        int nReplacementSet = dts_bits_get( bits, 2, bits_pos );                                /* nReplacementSet                (2) */
        if( nReplacementSet > 0 )
            dts_bits_get( bits, 1, bits_pos );                                                  /* bActiveReplaceSet              (1) */
        if( asset->bOne2OneMapChannels2Speakers )
        {
            /* Downmix is allowed only when the encoded channel represents a signal feed to a corresponding loudspeaker. */
            int bPrimaryChSet = dts_bits_get( bits, 1, bits_pos );                              /* bPrimaryChSet                  (1) */
            int bDownmixCoeffCodeEmbedded = dts_bits_get( bits, 1, bits_pos );                  /* bDownmixCoeffCodeEmbedded      (1) */
            int nLLDownmixType = 0x7;   /* 0b111: Unused */
            if( bDownmixCoeffCodeEmbedded )
            {
                dts_bits_get( bits, 1, bits_pos );                                              /* bDownmixEmbedded               (1) */
                if( bPrimaryChSet )
                    nLLDownmixType = dts_bits_get( bits, 3, bits_pos );                         /* nLLDownmixType                 (3) */
            }
            int bHierChSet = dts_bits_get( bits, 1, bits_pos );                                 /* bHierChSet                     (1) */
            if( bDownmixCoeffCodeEmbedded )
            {
                /* N: the number of channels in the current channel set
                 *    for non-primary channel set, adding +1 for the down scaling coefficients that prevent overflow
                 * M: the number of channels that the current channel set is mixed into
                 * Downmix coefficients are transmitted using 9-bit codes. */
                static const int downmix_channel_count_table[8] = { 1, 2, 2, 3, 3, 4, 4, 0 };
                int N = nChSetLLChannel + (bPrimaryChSet ? 0 : 1);
                int M = bPrimaryChSet ? downmix_channel_count_table[nLLDownmixType] : sum_nChSetLLChannel;
                int nDownmixCoeffs = N * M;
                dts_bits_get( bits, nDownmixCoeffs * 9, bits_pos );                             /* DownmixCoeffs                  (nDownmixCoeffs * 9) */
                if( bPrimaryChSet && downmix_channel_count_table[nLLDownmixType] == 2 )
                    xll->stereo_downmix |= 1;
            }
            if( bHierChSet )
                sum_nChSetLLChannel += nChSetLLChannel;
            if( dts_bits_get( bits, 1, bits_pos ) )                                             /* bChMaskEnabled                 (1) */
            {
                uint32_t nChMask = dts_bits_get( bits, nBits4ChMask, bits_pos );                /* nChMask                        (nBits4ChMask) */
                xll->channel_layout |= dts_get_channel_layout_from_ls_mask32( nChMask );
                xll->lower_planes   |= dts_get_lower_channels_from_ls_mask32( nChMask );
            }
            else
                dts_bits_get( bits, 25 * nChSetLLChannel, bits_pos );                           /* RadiusDelta[ch]                (9)
                                                                                                 * Theta[ch]                      (9)
                                                                                                 * Phi[ch]                        (7)
                                                                                                 *   per channel */
        }
        else
        {
            /* No downmixing is allowed and each channel set is the primary channel set. */
            if( dts_bits_get( bits, 1, bits_pos ) )                                             /* bMappingCoeffsPresent          (1) */
            {
                int nBitsCh2SpkrCoef = 6 + 2 * dts_bits_get( bits, 3, bits_pos );               /* nBitsCh2SpkrCoef               (3) */
                int nNumSpeakerConfigs = dts_bits_get( bits, 2, bits_pos ) + 1;                 /* nNumSpeakerConfigs             (2) */
                for( int nSpkrConf = 0; nSpkrConf < nNumSpeakerConfigs; nSpkrConf++ )
                {
                    int pnActiveChannelMask = dts_bits_get( bits, nChSetLLChannel, bits_pos );  /* pnActiveChannelMask[nSpkrConf] (nChSetLLChannel) */
                    int pnNumSpeakers = dts_bits_get( bits, 6, bits_pos ) + 1;                  /* pnNumSpeakers[nSpkrConf]       (6) */
                    int bSpkrMaskEnabled = dts_bits_get( bits, 1, bits_pos );                   /* bSpkrMaskEnabled               (1) */
                    if( bSpkrMaskEnabled )
                    {
                        uint32_t nSpkrMask = dts_bits_get( bits, nBits4ChMask, bits_pos );      /* nSpkrMask[nSpkrConf]           (nBits4ChMask) */
                        xll->channel_layout |= dts_get_channel_layout_from_ls_mask32( nSpkrMask );
                        xll->lower_planes   |= dts_get_lower_channels_from_ls_mask32( nSpkrMask );
                    }
                    for( int nSpkr = 0; nSpkr < pnNumSpeakers; nSpkr++ )
                    {
                        if( !bSpkrMaskEnabled )
                            dts_bits_get( bits, 25, bits_pos );                                 /* ChSetSpeakerConfiguration      (25) */
                        for( int nCh = 0; nCh < nChSetLLChannel; nCh++ )
                            if( pnActiveChannelMask & (1 << nCh) )
                                dts_bits_get( bits, nBitsCh2SpkrCoef, bits_pos );               /* pnCh2SpkrMapCoeff              (nBitsCh2SpkrCoef) */
                    }
                }
            }
        }
        int full_bandwidth;
        if( nFs > 96000 )
        {
            /* When bXtraFreqBands is equal to 0, only one-half of the original bandwidth is preserved and, thus, the number
             * of frequency bands is also one-half of the number in the case where full bandwidth is preserved. Apparently,
             * nSmplInSeg is the number of samples in a segment per one frequency band when full bandwidth is preserved.
             * Because of this, to get the correct number of samples per frame, multiply the result by 2 when bXtraFreqBands
             * is equal to 0. */
            full_bandwidth        = dts_bits_get( bits, 1, bits_pos );                          /* bXtraFreqBands                 (1) */
            nNumFreqBands[nChSet] = (1 + full_bandwidth) << (nFs > 192000);
        }
        else
        {
            full_bandwidth        = 1;
            nNumFreqBands[nChSet] = 1;
        }
        uint32_t nSmplInSeg_nChSet;
        if( nChSet == 0 )
        {
            nFs1              = nFs;
            nNumFreqBands1    = nNumFreqBands[nChSet];
            nSmplInSeg_nChSet = nSmplInSeg;
        }
        else
            nSmplInSeg_nChSet = (nSmplInSeg * (nFs * nNumFreqBands1)) / (nFs1 * nNumFreqBands[nChSet]);
        if( xll->sampling_frequency < nFs )
        {
            xll->sampling_frequency = nFs;
            uint32_t samples_per_band_in_frame = nSegmentsInFrame * nSmplInSeg_nChSet;
            xll->frame_duration = samples_per_band_in_frame * nNumFreqBands[nChSet] * (2 - full_bandwidth);
        }
        if( number_of_frequency_bands < nNumFreqBands[nChSet] )
            number_of_frequency_bands = nNumFreqBands[nChSet];
        dts_bits_get( bits, nChSetHeaderSize * 8 - (*bits_pos - xll_pos), bits_pos );   /* Skip the remaining bits in Channel Set Sub-Header. */
    }
    /* NAVI */
    uint64_t FreqBandDataSize = 0;
    for( int Band = 0; Band < number_of_frequency_bands; Band++ )
        for( int Seg = 0; Seg < nSegmentsInFrame; Seg++ )
        {
            /* The spec pseudocode extracts bits and initialize SegmentSize[Band][Seg] here. This may be one of lies in the spec.
             * According to 8.3.2 Stream Navigation in ETSI TS 102 114 V1.4.1, sum of all band data for all channel set in a segments is
             * the size of that segment. In addition there are no headers associated with segment and channel set of abstraction layer.
             * Obviously, the extraction is meaningless and the navigation should works without it. */
            // SegmentSize[Band][Seg] = dts_bits_get( bits, nBits4SSize, bits_pos );
            for( int nChSet = 0; nChSet < nNumChSetsInFrame; nChSet++ )
                if( nNumFreqBands[nChSet] > Band )
                    FreqBandDataSize += dts_bits_get( bits, nBits4SSize, bits_pos ) + 1;        /* BandChSetSize[Band][Seg][nChSet] (nBits4SSize) */
        }
    dts_bits_align( bits, bits_pos );
    dts_bits_get( bits, 16, bits_pos );                                                         /* Checksum                         (16) */
    /* Skip band data. */
    dts_bits_get( bits, FreqBandDataSize * 8, bits_pos );
    dts_bits_align4( bits, bits_pos );
    if( lsmash_bs_show_be32( bits->bs, 0 ) == DTS_SYNCWORD_X )
        xll->dtsx_extension_present = 1;
    info->flags |= DTS_EXT_SUBSTREAM_XLL_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static uint16_t dts_generate_channel_layout_from_core( int channel_arrangement )
{
    static const uint16_t channel_layout_map_table[] =
        {
            DTS_CHANNEL_LAYOUT_C,
            DTS_CHANNEL_LAYOUT_L_R,     /* dual mono */
            DTS_CHANNEL_LAYOUT_L_R,     /* stereo */
            DTS_CHANNEL_LAYOUT_L_R,     /* sum-difference */
            DTS_CHANNEL_LAYOUT_L_R,     /* Lt/Rt */
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_L_R,
            DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_CS,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_CS,
            DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LS_RS,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LS_RS,
            DTS_CHANNEL_LAYOUT_LC_RC | DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LS_RS,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LSR_RSR | DTS_CHANNEL_LAYOUT_OH,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_CS    | DTS_CHANNEL_LAYOUT_L_R     | DTS_CHANNEL_LAYOUT_LSR_RSR,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LC_RC   | DTS_CHANNEL_LAYOUT_LS_RS,
            DTS_CHANNEL_LAYOUT_L_R   | DTS_CHANNEL_LAYOUT_LC_RC | DTS_CHANNEL_LAYOUT_LS_RS   | DTS_CHANNEL_LAYOUT_LSR_RSR,
            DTS_CHANNEL_LAYOUT_C     | DTS_CHANNEL_LAYOUT_CS    | DTS_CHANNEL_LAYOUT_L_R     | DTS_CHANNEL_LAYOUT_LC_RC | DTS_CHANNEL_LAYOUT_LS_RS
        };
    return channel_arrangement < 16 ? channel_layout_map_table[channel_arrangement] : 0;
}

static int dts_parse_core( dts_info_t *info, uint64_t *bits_pos, dts_core_info_t *core )
{
    lsmash_bits_t *bits = info->bits;
    memset( core, 0, sizeof(dts_core_info_t) );
                                                                                /* SYNC            (32) */
    int frame_type = dts_bits_get( bits, 1, bits_pos );                         /* FTYPE           (1) */
    int deficit_sample_count = dts_bits_get( bits, 5, bits_pos );               /* SHORT           (5) */
    if( frame_type == 1 && deficit_sample_count != 31 )
        return LSMASH_ERR_INVALID_DATA; /* Any normal frame (FTYPE == 1) must have SHORT == 31. */
    int crc_present_flag = dts_bits_get( bits, 1, bits_pos );                   /* CPF             (1) */
    int num_of_pcm_sample_blocks = dts_bits_get( bits, 7, bits_pos ) + 1;       /* NBLKS           (7) */
    if( num_of_pcm_sample_blocks <= 5 )
        return LSMASH_ERR_INVALID_DATA;
    core->frame_duration = 32 * num_of_pcm_sample_blocks;
    if( frame_type == 1
     && core->frame_duration != 256
     && core->frame_duration != 512  && core->frame_duration != 1024
     && core->frame_duration != 2048 && core->frame_duration != 4096 )
        return LSMASH_ERR_INVALID_DATA; /* For any normal frame, the actual number of PCM core samples per channel must be
                                         * either 4096, 2048, 1024, 512, or 256 samples per channel. */
    core->frame_size = dts_bits_get( bits, 14, bits_pos ) + 1;                  /* FSIZE           (14) */
    if( core->frame_size < DTS_MIN_CORE_SIZE )
        return LSMASH_ERR_INVALID_DATA;
    core->channel_arrangement = dts_bits_get( bits, 6, bits_pos );              /* AMODE           (6) */
    core->channel_layout = dts_generate_channel_layout_from_core( core->channel_arrangement );
    int core_audio_sampling_frequency = dts_bits_get( bits, 4, bits_pos );      /* SFREQ           (4) */
    static const uint32_t sampling_frequency_table[16] =
        {
                0,
             8000, 16000, 32000, 0, 0,
            11025, 22050, 44100, 0, 0,
            12000, 24000, 48000, 0, 0
        };
    core->sampling_frequency = sampling_frequency_table[core_audio_sampling_frequency];
    if( core->sampling_frequency == 0 )
        return LSMASH_ERR_INVALID_DATA; /* invalid */
    dts_bits_get( bits, 10, bits_pos );                                         /* Skip remainder 10 bits.
                                                                                 * RATE            (5)
                                                                                 * MIX             (1)
                                                                                 * DYNF            (1)
                                                                                 * TIMEF           (1)
                                                                                 * AUXF            (1)
                                                                                 * HDCD            (1) */
    core->extension_audio_descriptor = dts_bits_get( bits, 3,  bits_pos );      /* EXT_AUDIO_ID    (3)
                                                                                 * Note: EXT_AUDIO_ID == 3 is defined in V1.2.1.
                                                                                 * However, its definition disappears and is reserved in V1.3.1. */
    int extended_coding_flag = dts_bits_get( bits, 1, bits_pos );               /* EXT_AUDIO       (1) */
    dts_bits_get( bits, 1, bits_pos );                                          /* ASPF            (1) */
    int low_frequency_effects_flag = dts_bits_get( bits, 2, bits_pos );         /* LFF             (2) */
    if( low_frequency_effects_flag == 0x3 )
        return LSMASH_ERR_INVALID_DATA; /* invalid */
    if( low_frequency_effects_flag )
        core->channel_layout |= DTS_CHANNEL_LAYOUT_LFE1;
    dts_bits_get( bits, 8 + crc_present_flag * 16, bits_pos );                  /* HFLAG           (1)
                                                                                 * HCRC            (16)
                                                                                 * FILTS           (1)
                                                                                 * VERNUM          (4)
                                                                                 * CHIST           (2) */
    int PCMR = dts_bits_get( bits, 3, bits_pos );                               /* PCMR            (3) */
    static const uint8_t source_resolution_table[8] = { 16, 16, 20, 20, 0, 24, 24, 0 };
    core->pcm_resolution = source_resolution_table[PCMR];
    if( core->pcm_resolution == 0 )
        return LSMASH_ERR_INVALID_DATA; /* invalid */
    dts_bits_get( bits, 6, bits_pos );                                          /* SUMF            (1)
                                                                                 * SUMS            (1)
                                                                                 * DIALNORM/UNSPEC (4) */
    if( extended_coding_flag )
    {
        uint32_t syncword = dts_bits_get( bits, 24, bits_pos );
        uint64_t frame_size_bits = core->frame_size * 8;
        while( (*bits_pos + 24) < frame_size_bits )
        {
            int err;
            syncword = ((syncword << 8) & 0xffffff00) | dts_bits_get( bits, 8, bits_pos );
            switch( syncword )
            {
                case DTS_SYNCWORD_XXCH :
                    if( (err = dts_parse_core_xxch( info, bits_pos, core )) < 0 )
                        return err;
                    syncword = dts_bits_get( bits, 24, bits_pos );
                    break;
                case DTS_SYNCWORD_X96K :
                    if( (err = dts_parse_core_x96( info, bits_pos, core )) < 0 )
                        return err;
                    syncword = dts_bits_get( bits, 24, bits_pos );
                    break;
                case DTS_SYNCWORD_XCH :
                    if( (err = dts_parse_core_xch( info, bits_pos, core )) < 0 )
                        return err;
                    break;
                default :
                    continue;
            }
        }
    }
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

static int dts_parse_exss_core( dts_info_t *info, uint64_t *bits_pos, dts_audio_asset_t *asset )
{
    lsmash_bits_t *bits = info->bits;
    if( DTS_SYNCWORD_SUBSTREAM_CORE != dts_bits_get( bits, 32, bits_pos ) )
        return LSMASH_ERR_INVALID_DATA;
    int err = dts_parse_core( info, bits_pos, &asset->core );
    if( err < 0 )
        return err;
    info->flags |= DTS_EXT_SUBSTREAM_CORE_FLAG;
    return bits->bs->error ? LSMASH_ERR_NAMELESS : 0;
}

int dts_parse_core_substream( dts_info_t *info )
{
    lsmash_bits_t *bits = info->bits;
    uint64_t bits_pos = 0;
    int err;
    if( DTS_SYNCWORD_CORE != dts_bits_get( bits, 32, &bits_pos ) )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto parse_fail;
    }
    /* By default the core substream data, if present, has the nuBcCoreExtSSIndex = 0 and the nuBcCoreAssetIndex = 0. */
    dts_extension_info_t *exss = &info->exss[0];
    if( (err = dts_parse_core( info, &bits_pos, &exss->asset[0].core )) < 0 )
        goto parse_fail;
    exss->bBcCorePresent    [0] = 1;
    exss->nuBcCoreExtSSIndex[0] = 0;
    exss->nuBcCoreAssetIndex[0] = 0;
    info->flags |= DTS_CORE_SUBSTREAM_CORE_FLAG;
    info->exss_count      = 0;
    info->core            = exss->asset[0].core;
    info->frame_size      = exss->asset[0].core.frame_size;
    lsmash_bits_get_align( bits );
    return 0;
parse_fail:
    lsmash_bits_get_align( bits );
    return err;
}

int dts_parse_extension_substream( dts_info_t *info )
{
    lsmash_bits_t *bits = info->bits;
    uint64_t bits_pos = 0;
    dts_bits_get( bits, 40, &bits_pos );                                                    /* SYNCEXTSSH                    (32)
                                                                                             * UserDefinedBits               (8) */
    int nExtSSIndex = dts_bits_get( bits, 2, &bits_pos );                                   /* nExtSSIndex                   (2) */
    info->exss_index = nExtSSIndex;
    dts_extension_info_t *exss = &info->exss[nExtSSIndex];
    memset( exss, 0, sizeof(dts_extension_info_t) );
    int bHeaderSizeType = dts_bits_get( bits, 1, &bits_pos );                               /* bHeaderSizeType               (1) */
    int nuBits4Header    =  8 + bHeaderSizeType * 4;
    int nuBits4ExSSFsize = 16 + bHeaderSizeType * 4;
    exss->nuBits4ExSSFsize = nuBits4ExSSFsize;
    uint32_t nuExtSSHeaderSize = dts_bits_get( bits, nuBits4Header, &bits_pos ) + 1;        /* nuExtSSHeaderSize             (8 or 12) */
    info->frame_size = dts_bits_get( bits, nuBits4ExSSFsize, &bits_pos ) + 1;               /* nuExtSSFsize                  (16 or 20) */
    if( info->frame_size < 10 )
        return LSMASH_ERR_INVALID_DATA;
    exss->bStaticFieldsPresent = dts_bits_get( bits, 1, &bits_pos );                        /* bStaticFieldsPresent          (1) */
    if( exss->bStaticFieldsPresent )
    {
        dts_bits_get( bits, 2, &bits_pos );                                                 /* nuRefClockCode                (2) */
        exss->frame_duration = 512 * (dts_bits_get( bits, 3, &bits_pos ) + 1);              /* nuExSSFrameDurationCode       (3) */
        if( dts_bits_get( bits, 1, &bits_pos ) )                                            /* bTimeStampFlag                (1) */
            dts_bits_get( bits, 36, &bits_pos );                                            /* nuTimeStamp                   (32)
                                                                                             * nLSB                          (4) */
        exss->nuNumAudioPresnt = dts_bits_get( bits, 3, &bits_pos ) + 1;                    /* nuNumAudioPresnt              (3) */
        exss->nuNumAssets      = dts_bits_get( bits, 3, &bits_pos ) + 1;                    /* nuNumAssets                   (3) */
        /* The extension substreams with indexes lower than or equal to the index of the current extension substream can
         * be activated in the audio presentations indicated within the current extension substream. */
        for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
            exss->nuActiveExSSMask[nAuPr]
                = dts_bits_get( bits, nExtSSIndex + 1, &bits_pos );                         /* nuActiveExSSMask[nAuPr]       (nExtSSIndex + 1) */
        for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
            for( uint8_t nSS = 0; nSS <= nExtSSIndex; nSS++ )
                exss->nuActiveAssetMask[nAuPr][nSS]
                    = ((exss->nuActiveExSSMask[nAuPr] >> nSS) & 0x1)
                    ? dts_bits_get( bits, 8, &bits_pos )                                    /* nuActiveAssetMask[nAuPr][nSS] (8) */
                    : 0;
        exss->bMixMetadataEnbl = dts_bits_get( bits, 1, &bits_pos );                        /* bMixMetadataEnbl              (1) */
        if( exss->bMixMetadataEnbl )
        {
            dts_bits_get( bits, 2, &bits_pos );                                             /* nuMixMetadataAdjLevel         (2) */
            int nuBits4MixOutMask = (dts_bits_get( bits, 2, &bits_pos ) + 1) << 2;          /* nuBits4MixOutMask             (2) */
            exss->nuNumMixOutConfigs = dts_bits_get( bits, 2, &bits_pos ) + 1;              /* nuNumMixOutConfigs            (2) */
            for( int ns = 0; ns < exss->nuNumMixOutConfigs; ns++ )
            {
                int nuMixOutChMask = dts_bits_get( bits, nuBits4MixOutMask, &bits_pos );    /* nuMixOutChMask[ns]            (nuBits4MixOutMask) */
                exss->nNumMixOutCh[ns] = dts_get_channel_count_from_channel_layout( nuMixOutChMask );
            }
        }
    }
    else
    {
        exss->nuNumAudioPresnt   = 1;
        exss->nuNumAssets        = 1;
        exss->bMixMetadataEnbl   = 0;
        exss->nuNumMixOutConfigs = 0;
    }
    for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        exss->asset[nAst].size = dts_bits_get( bits, nuBits4ExSSFsize, &bits_pos ) + 1;     /* nuAssetFsize[nAst] - 1        (nuBits4ExSSFsize) */
    int err;
    for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        if( (err = dts_parse_asset_descriptor( info, &bits_pos )) < 0 )
            goto parse_fail;
    for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
        exss->bBcCorePresent[nAuPr] = dts_bits_get( bits, 1, &bits_pos );
    for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
        if( exss->bBcCorePresent[nAuPr] )
        {
            exss->nuBcCoreExtSSIndex[nAuPr] = dts_bits_get( bits, 2, &bits_pos );
            exss->nuBcCoreAssetIndex[nAuPr] = dts_bits_get( bits, 3, &bits_pos );
        }
    dts_bits_get( bits, nuExtSSHeaderSize * 8 - bits_pos, &bits_pos );
    for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
    {
        /* Asset Data */
        dts_audio_asset_t *asset = &exss->asset[nAst];
        uint32_t asset_pos = bits_pos;
        switch( asset->nuCodingMode )
        {
            case 0 : /* DTS-HD Coding Mode that may contain multiple coding components */
            {
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_CORE_FLAG )
                {
                    /* Core component */
                    uint64_t core_pos = bits_pos;
                    if( (err = dts_parse_exss_core( info, &bits_pos, asset )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->core.frame_size * 8 - (bits_pos - core_pos), &bits_pos );
                }
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XBR_FLAG )
                {
                    /* XBR extension */
                    uint64_t xbr_pos = bits_pos;
                    if( (err = dts_parse_exss_xbr( info, &bits_pos )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->xbr_size * 8 - (bits_pos - xbr_pos), &bits_pos );
                }
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XXCH_FLAG )
                {
                    /* XXCH extension */
                    uint64_t xxch_pos = bits_pos;
                    if( (err = dts_parse_exss_xxch( info, &bits_pos, &asset->core )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->core.xxch.size * 8 - (bits_pos - xxch_pos), &bits_pos );
                }
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_X96_FLAG )
                {
                    /* X96 extension */
                    uint64_t x96_pos = bits_pos;
                    if( (err = dts_parse_exss_x96( info, &bits_pos, &asset->core )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->x96_size * 8 - (bits_pos - x96_pos), &bits_pos );
                }
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_LBR_FLAG )
                {
                    /* LBR component */
                    uint64_t lbr_pos = bits_pos;
                    if( (err = dts_parse_exss_lbr( info, &bits_pos, asset )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->lbr.size * 8 - (bits_pos - lbr_pos), &bits_pos );
                }
                if( asset->nuCoreExtensionMask & DTS_EXT_SUBSTREAM_XLL_FLAG )
                {
                    /* Lossless extension */
                    uint64_t xll_pos = bits_pos;
                    if( (err = dts_parse_exss_xll( info, &bits_pos, asset )) < 0 )
                        goto parse_fail;
                    dts_bits_get( bits, asset->xll.size * 8 - (bits_pos - xll_pos), &bits_pos );
                }
                break;
            }
            case 1 : /* DTS-HD Loss-less coding mode without CBR component */
                if( (err = dts_parse_exss_xll( info, &bits_pos, asset )) < 0 )
                    goto parse_fail;
                break;
            case 2 : /* DTS-HD Low bit-rate mode */
                if( (err = dts_parse_exss_lbr( info, &bits_pos, asset )) < 0 )
                    goto parse_fail;
                break;
            case 3 : /* Auxiliary coding mode */
                dts_bits_get( bits, asset->aux_size * 8, &bits_pos );
                break;
        }
        dts_bits_get( bits, asset->size * 8 - (bits_pos - asset_pos), &bits_pos );
    }
    dts_bits_get( bits, info->frame_size * 8 - bits_pos, &bits_pos );
    lsmash_bits_get_align( bits );
    if( info->exss_count < DTS_MAX_NUM_EXSS )
        info->exss_count += 1;
    return 0;
parse_fail:
    lsmash_bits_get_align( bits );
    return err;
}

dts_substream_type dts_get_substream_type( dts_info_t *info )
{
    if( lsmash_bs_get_remaining_buffer_size( info->bits->bs ) < 4 )
        return DTS_SUBSTREAM_TYPE_NONE;
    uint8_t *buffer = lsmash_bs_get_buffer_data( info->bits->bs );
    uint32_t syncword = LSMASH_4CC( buffer[0], buffer[1], buffer[2], buffer[3] );
    switch( syncword )
    {
        case DTS_SYNCWORD_CORE :
            return DTS_SUBSTREAM_TYPE_CORE;
        case DTS_SYNCWORD_SUBSTREAM :
            return DTS_SUBSTREAM_TYPE_EXTENSION;
        default :
            return DTS_SUBSTREAM_TYPE_NONE;
    }
}

int dts_get_exss_index( dts_info_t *info, uint8_t *exss_index )
{
    if( lsmash_bs_get_remaining_buffer_size( info->bits->bs ) < 6 )
        return LSMASH_ERR_INVALID_DATA;
    *exss_index = lsmash_bs_show_byte( info->bits->bs, 5 ) >> 6;
    return 0;
}

int dts_get_max_channel_count( dts_info_t *info )
{
    int max_channel_count = 0;
    for( int nExtSSIndex = 0; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
        {
            /* Get the channel layout of an audio presentation from a core component. */
            uint16_t channel_layout = 0;
            int      channel_count  = 0;
            if( exss->bBcCorePresent    [nAuPr]
             && exss->nuBcCoreAssetIndex[nAuPr] < exss->nuNumAssets )
            {
                dts_core_info_t *core = &info->exss[ exss->nuBcCoreExtSSIndex[nAuPr] ].asset[ exss->nuBcCoreAssetIndex[nAuPr] ].core;
                if( core->xxch.channel_layout | core->xxch.lower_planes )
                {
                    channel_layout = core->xxch.channel_layout;
                    channel_count  = lsmash_count_bits( core->xxch.lower_planes );  /* FIXME: Should we count these channels? */
                }
                else
                    channel_layout = core->channel_layout;
            }
            channel_count += dts_get_channel_count_from_channel_layout( channel_layout );
            max_channel_count = LSMASH_MAX( max_channel_count, channel_count );
            /* Get the channel layouts of an audio presentation from extension substreams. */
            uint16_t ext_channel_layout = 0;
            uint16_t lbr_channel_layout = 0;
            uint16_t xll_channel_layout = 0;
            uint8_t  xll_lower_channels = 0;
            for( int nSS = 0; nSS <= nExtSSIndex; nSS++ )
                if( (exss->nuActiveExSSMask[nAuPr] >> nSS) & 0x1 )
                    for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
                        if( (exss->nuActiveAssetMask[nAuPr][nSS] >> nAst) & 0x1 )
                        {
                            dts_audio_asset_t *asset = &exss->asset[nAst];
                            ext_channel_layout |= asset->channel_layout;
                            lbr_channel_layout |= asset->lbr.channel_layout;
                            xll_channel_layout |= asset->xll.channel_layout;
                            xll_lower_channels |= asset->xll.lower_planes;
                        }
            /* Audio asset descriptors */
            channel_count = dts_get_channel_count_from_channel_layout( ext_channel_layout );
            max_channel_count = LSMASH_MAX( max_channel_count, channel_count );
            /* LBR components */
            channel_count = dts_get_channel_count_from_channel_layout( lbr_channel_layout );
            max_channel_count = LSMASH_MAX( max_channel_count, channel_count );
            /* Lossless extensions */
            channel_count = dts_get_channel_count_from_channel_layout( xll_channel_layout )
                          + lsmash_count_bits( xll_lower_channels );
            max_channel_count = LSMASH_MAX( max_channel_count, channel_count );
        }
    }
    return max_channel_count;
}

void dts_update_specific_param( dts_info_t *info )
{
    lsmash_dts_specific_parameters_t *param = &info->ddts_param;
    /* Find the first valid substream.
     * Both nuNumAudioPresnt and nuNumAssets of any substream must not be 0. Therefore, at least one of these are 0,
     * then the substream is invalid or absent. */
    int exss_index_start = 0;
    for( int nExtSSIndex = 0; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        if( exss->nuNumAudioPresnt && exss->nuNumAssets )
        {
            exss_index_start = nExtSSIndex;
            break;
        }
    }
    /* DTSSamplingFrequency and FrameDuration */
    for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        if( exss->nuNumAudioPresnt == 0 || exss->nuNumAssets == 0 )
            continue;
        if( param->DTSSamplingFrequency <= exss->sampling_frequency )
        {
            param->DTSSamplingFrequency = exss->sampling_frequency;
            info->frame_duration        = exss->frame_duration;
        }
        for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        {
            dts_audio_asset_t *asset = &exss->asset[nAst];
            if( param->DTSSamplingFrequency <= asset->core.sampling_frequency )
            {
                param->DTSSamplingFrequency = asset->core.sampling_frequency;
                info->frame_duration        = asset->core.frame_duration;
            }
            if( param->DTSSamplingFrequency <= asset->lbr.sampling_frequency )
            {
                param->DTSSamplingFrequency = asset->lbr.sampling_frequency;
                info->frame_duration        = asset->lbr.frame_duration;
            }
            if( param->DTSSamplingFrequency <= asset->xll.sampling_frequency )
            {
                param->DTSSamplingFrequency = asset->xll.sampling_frequency;
                info->frame_duration        = asset->xll.frame_duration;
            }
        }
    }
    param->FrameDuration = 0;
    for( uint32_t frame_duration = info->frame_duration >> 10; frame_duration; frame_duration >>= 1 )
        ++ param->FrameDuration;
    /* pcmSampleDepth */
    param->pcmSampleDepth = 0;
    for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        if( exss->nuNumAudioPresnt == 0 || exss->nuNumAssets == 0 )
            continue;
        param->pcmSampleDepth = LSMASH_MAX( param->pcmSampleDepth, exss->bit_resolution );
        for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        {
            dts_audio_asset_t *asset = &exss->asset[nAst];
            param->pcmSampleDepth = LSMASH_MAX( param->pcmSampleDepth, asset->core.pcm_resolution );
            param->pcmSampleDepth = LSMASH_MAX( param->pcmSampleDepth, asset->lbr.sample_size );
            param->pcmSampleDepth = LSMASH_MAX( param->pcmSampleDepth, asset->xll.pcm_resolution );
        }
    }
    param->pcmSampleDepth = param->pcmSampleDepth > 16 ? 24 : 16;
    /* StreamConstruction */
    param->StreamConstruction = lsmash_dts_get_stream_construction( info->flags );
    /* CoreLFEPresent */
    param->CoreLFEPresent = !!(info->core.channel_layout & DTS_CHANNEL_LAYOUT_LFE1);
    /* CoreLayout */
    if( param->StreamConstruction == 0  /* Unknown */
     || param->StreamConstruction >= 17 /* No core substream */ )
        /* Use ChannelLayout. */
        param->CoreLayout = 31;
    else
    {
        if( info->core.channel_arrangement != 1
         && info->core.channel_arrangement != 3
         && info->core.channel_arrangement <= 9 )
            param->CoreLayout = info->core.channel_arrangement;
        else
            /* Use ChannelLayout. */
            param->CoreLayout = 31;
    }
    /* CoreSize
     * The specification says this field is the size of a core substream AU in bytes.
     * If we don't assume CoreSize is the copy of FSIZE, when FSIZE equals 0x3FFF, this field overflows and becomes 0. */
    param->CoreSize = info->core.frame_size ? LSMASH_MIN( info->core.frame_size - 1, 0x3FFF ) : 0;
    /* StereoDownmix */
    param->StereoDownmix = 0;
    for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        param->StereoDownmix |= exss->stereo_downmix;
        for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        {
            param->StereoDownmix |= exss->asset[nAst].lbr.stereo_downmix;
            param->StereoDownmix |= exss->asset[nAst].xll.stereo_downmix;
        }
    }
    /* RepresentationType
     * Available only when core substream is absent and ChannelLayout is set to 0. */
    for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        if( exss->nuNumAudioPresnt == 0 || exss->nuNumAssets == 0 )
            continue;
        for( uint8_t nAuPr = 0; nAuPr < exss->nuNumAudioPresnt; nAuPr++ )
        {
            int asset_count = 0;
            for( int nSS = 0; nSS <= nExtSSIndex; nSS++ )
                if( (exss->nuActiveExSSMask[nAuPr] >> nSS) & 0x1 )
                    asset_count += lsmash_count_bits( exss->nuActiveAssetMask[nAuPr][nSS] );
            if( asset_count > 1 )
            {
                /* An audio presentation has mulple audio assets.
                 * Audio asset designated for mixing with another audio asset. */
                param->RepresentationType = 0;
                nExtSSIndex = DTS_MAX_NUM_EXSS;
                break;
            }
            for( int nSS = 0; nSS <= nExtSSIndex; nSS++ )
                if( (exss->nuActiveExSSMask[nAuPr] >> nSS) & 0x1 )
                    for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
                        if( (exss->nuActiveAssetMask[nAuPr][nSS] >> nAst) & 0x1 )
                        {
                            dts_audio_asset_t *asset = &exss->asset[nAst];
                            if( asset->nuRepresentationType == info->exss[exss_index_start].asset[0].nuRepresentationType )
                                param->RepresentationType = asset->nuRepresentationType;
                            else
                            {
                                /* Detected different representation types. Use ChannelLayout. */
                                param->RepresentationType = 0;
                                nAuPr       = exss->nuNumAudioPresnt;
                                nExtSSIndex = DTS_MAX_NUM_EXSS;
                                break;
                            }
                        }
        }
    }
    /* ChannelLayout
     * complete information on channels coded in the audio stream including core and extensions */
    param->ChannelLayout = 0;
    if( param->RepresentationType == 0 )
        for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
        {
            dts_extension_info_t *exss = &info->exss[nExtSSIndex];
            if( exss->nuNumAudioPresnt == 0 || exss->nuNumAssets == 0 )
                continue;
            for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
            {
                dts_audio_asset_t *asset = &exss->asset[nAst];
                param->ChannelLayout |= asset->channel_layout;
                param->ChannelLayout |= asset->core.channel_layout;
                param->ChannelLayout |= asset->core.xxch.channel_layout;
                param->ChannelLayout |= asset->lbr.channel_layout;
                param->ChannelLayout |= asset->xll.channel_layout;
            }
        }
    /* MultiAssetFlag
     * When multiple assets exist, the remaining parameters in the DTSSpecificBox only reflect the coding parameters of the first asset. */
    param->MultiAssetFlag = ((info->exss[0].nuNumAssets
                            + info->exss[1].nuNumAssets
                            + info->exss[2].nuNumAssets
                            + info->exss[3].nuNumAssets) > 1);
    /* LBRDurationMod */
    param->LBRDurationMod = info->exss[exss_index_start].asset[0].lbr.duration_modifier;
    /* DTSExpansionBox[] */
    for( int nExtSSIndex = exss_index_start; nExtSSIndex < DTS_MAX_NUM_EXSS; nExtSSIndex++ )
    {
        dts_extension_info_t *exss = &info->exss[nExtSSIndex];
        for( uint8_t nAst = 0; nAst < exss->nuNumAssets; nAst++ )
        {
            dts_audio_asset_t *asset = &exss->asset[nAst];
            if( asset->xll.dtsx_extension_present )
            {
                /* Add DTSXParameters Box so that its presence indicates DTS:X extensions are present in the bitstream.
                 * Here, treat as unknown whether dialog level control for dialog objects in the bitstream is present or not. */
                static const uint8_t dxpb[] =
                {
                    0x00, 0x00, 0x00, 0x0c, /* size = 12 */
                    0x64, 0x78, 0x70, 0x62, /* type = 'dxpb' */
                    0x00, 0x00, 0x00, 0x00  /* version = 0, flags = 0x000000 (no dialog_control_info_present flag) */
                };
                lsmash_remove_dts_reserved_box( param );
                lsmash_append_dts_reserved_box( param, dxpb, sizeof(dxpb) );
                /* No error checks and just return. */
                goto param_initialized;
            }
        }
    }
param_initialized:
    info->ddts_param_initialized = 1;
}

int dts_construct_specific_parameters( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < DTS_SPECIFIC_BOX_MIN_LENGTH )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_dts_specific_parameters_t *param = (lsmash_dts_specific_parameters_t *)dst->data.structured;
    uint8_t *data = src->data.unstructured;
    uint64_t size = LSMASH_GET_BE32( data );
    int dts_specific_box_min_length = DTS_SPECIFIC_BOX_MIN_LENGTH;
    data += ISOM_BASEBOX_COMMON_SIZE;
    if( size == 1 )
    {
        size = LSMASH_GET_BE64( data );
        dts_specific_box_min_length += 8;
        data += 8;
    }
    if( size != src->size )
        return LSMASH_ERR_INVALID_DATA;
    param->DTSSamplingFrequency = LSMASH_GET_BE32( &data[0] );
    param->maxBitrate           = LSMASH_GET_BE32( &data[4] );
    param->avgBitrate           = LSMASH_GET_BE32( &data[8] );
    param->pcmSampleDepth       = LSMASH_GET_BYTE( &data[12] );
    param->FrameDuration        = (data[13] >> 6) & 0x03;
    param->StreamConstruction   = (data[13] >> 1) & 0x1F;
    param->CoreLFEPresent       = data[13] & 0x01;
    param->CoreLayout           = (data[14] >> 2) & 0x3F;
    param->CoreSize             = ((data[14] & 0x03) << 12) | (data[15] << 4) | ((data[16] >> 4) & 0x0F);
    param->StereoDownmix        = (data[16] >> 3) & 0x01;
    param->RepresentationType   = data[16] & 0x07;
    param->ChannelLayout        = (data[17] << 8) | data[18];
    param->MultiAssetFlag       = (data[19] >> 7) & 0x01;
    param->LBRDurationMod       = (data[19] >> 6) & 0x01;
    int reserved_box_present    = ((data[19] >> 5) & 0x01) && (size > dts_specific_box_min_length);
    if( reserved_box_present )
        lsmash_append_dts_reserved_box( param, data + 20, size - dts_specific_box_min_length );
    return 0;
}

int dts_copy_codec_specific( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( src && src->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && src->data.structured );
    assert( dst && dst->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && dst->data.structured );
    lsmash_dts_specific_parameters_t *src_data = (lsmash_dts_specific_parameters_t *)src->data.structured;
    lsmash_dts_specific_parameters_t *dst_data = (lsmash_dts_specific_parameters_t *)dst->data.structured;
    lsmash_remove_dts_reserved_box( dst_data );
    *dst_data = *src_data;
    if( !src_data->box || !src_data->box->data || src_data->box->size == 0 )
    {
        lsmash_remove_dts_reserved_box( dst_data );
        return 0;
    }
    return lsmash_append_dts_reserved_box( dst_data, src_data->box->data, src_data->box->size );
}

int dts_print_codec_specific( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    assert( box->manager & LSMASH_BINARY_CODED_BOX );
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: DTS Specific Box]\n", isom_4cc2str( box->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    if( box->size < DTS_SPECIFIC_BOX_MIN_LENGTH )
        return LSMASH_ERR_INVALID_DATA;
    uint8_t *data = box->binary;
    isom_skip_box_common( &data );
    uint32_t DTSSamplingFrequency = LSMASH_GET_BE32( &data[0] );
    uint32_t maxBitrate           = LSMASH_GET_BE32( &data[4] );
    uint32_t avgBitrate           = LSMASH_GET_BE32( &data[8] );
    uint8_t  pcmSampleDepth       = LSMASH_GET_BYTE( &data[12] );
    uint8_t  FrameDuration        = (data[13] >> 6) & 0x03;
    uint8_t  StreamConstruction   = (data[13] >> 1) & 0x1F;
    uint8_t  CoreLFEPresent       = data[13] & 0x01;
    uint8_t  CoreLayout           = (data[14] >> 2) & 0x3F;
    uint16_t CoreSize             = ((data[14] & 0x03) << 12) | (data[15] << 4) | ((data[16] >> 4) & 0x0F);
    uint8_t  StereoDownmix        = (data[16] >> 3) & 0x01;
    uint8_t  RepresentationType   = data[16] & 0x07;
    uint16_t ChannelLayout        = (data[17] << 8) | data[18];
    uint8_t  MultiAssetFlag       = (data[19] >> 7) & 0x01;
    uint8_t  LBRDurationMod       = (data[19] >> 6) & 0x01;
    uint8_t  ReservedBoxPresent   = (data[19] >> 5) & 0x01;
    uint8_t  Reserved             = data[19] & 0x1F;
    uint32_t frame_duration       = 512 << FrameDuration;
    int      construction_flags   = StreamConstruction <= DTS_MAX_STREAM_CONSTRUCTION ? construction_info[StreamConstruction] : 0;
    static const char *core_layout_description[64] =
        {
            "Mono (1/0)",
            "Undefined",
            "Stereo (2/0)",
            "Undefined",
            "LT,RT (2/0)",
            "L, C, R (3/0)",
            "L, R, S (2/1)",
            "L, C, R, S (3/1)",
            "L, R, LS, RS (2/2)",
            "L, C, R, LS, RS (3/2)",
            [31] = "use ChannelLayout"
        };
    static const char *representation_type_description[8] =
        {
            "Audio asset designated for mixing with another audio asset",
            "Reserved",
            "Lt/Rt Encoded for matrix surround decoding",
            "Audio processed for headphone playback",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved"
        };
    static const char *channel_layout_description[16] =
        {
            "Center in front of listener",
            "Left/Right in front",
            "Left/Right surround on side in rear",
            "Low frequency effects subwoofer",
            "Center surround in rear",
            "Left/Right height in front",
            "Left/Right surround in rear",
            "Center Height in front",
            "Over the listener's head",
            "Between left/right and center in front",
            "Left/Right on side in front",
            "Left/Right surround on side",
            "Second low frequency effects subwoofer",
            "Left/Right height on side",
            "Center height in rear",
            "Left/Right height in rear"
        };
    lsmash_ifprintf( fp, indent, "DTSSamplingFrequency = %"PRIu32" Hz\n", DTSSamplingFrequency );
    lsmash_ifprintf( fp, indent, "maxBitrate = %"PRIu32" bit/s\n", maxBitrate );
    lsmash_ifprintf( fp, indent, "avgBitrate = %"PRIu32" bit/s\n", avgBitrate );
    lsmash_ifprintf( fp, indent, "pcmSampleDepth = %"PRIu8" bits\n", pcmSampleDepth );
    lsmash_ifprintf( fp, indent, "FrameDuration = %"PRIu8" (%"PRIu32" samples)\n", FrameDuration, frame_duration );
    lsmash_ifprintf( fp, indent, "StreamConstruction = 0x%02"PRIx8"\n", StreamConstruction );
    if( construction_flags & (DTS_CORE_SUBSTREAM_CORE_FLAG | DTS_CORE_SUBSTREAM_XCH_FLAG | DTS_CORE_SUBSTREAM_X96_FLAG | DTS_CORE_SUBSTREAM_XXCH_FLAG) )
    {
        lsmash_ifprintf( fp, indent + 1, "Core substream\n" );
        if( construction_flags & DTS_CORE_SUBSTREAM_CORE_FLAG )
            lsmash_ifprintf( fp, indent + 2, "Core\n" );
        if( construction_flags & DTS_CORE_SUBSTREAM_XCH_FLAG )
            lsmash_ifprintf( fp, indent + 2, "XCH\n" );
        if( construction_flags & DTS_CORE_SUBSTREAM_X96_FLAG )
            lsmash_ifprintf( fp, indent + 2, "X96\n" );
        if( construction_flags & DTS_CORE_SUBSTREAM_XXCH_FLAG )
            lsmash_ifprintf( fp, indent + 2, "XXCH\n" );
    }
    if( construction_flags & (DTS_EXT_SUBSTREAM_CORE_FLAG | DTS_EXT_SUBSTREAM_XXCH_FLAG | DTS_EXT_SUBSTREAM_X96_FLAG
                            | DTS_EXT_SUBSTREAM_XBR_FLAG | DTS_EXT_SUBSTREAM_XLL_FLAG | DTS_EXT_SUBSTREAM_LBR_FLAG) )
    {
        lsmash_ifprintf( fp, indent + 1, "Extension substream\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_CORE_FLAG )
            lsmash_ifprintf( fp, indent + 2, "Core\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_XXCH_FLAG )
            lsmash_ifprintf( fp, indent + 2, "XXCH\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_X96_FLAG )
            lsmash_ifprintf( fp, indent + 2, "X96\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_XBR_FLAG )
            lsmash_ifprintf( fp, indent + 2, "XBR\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_XLL_FLAG )
            lsmash_ifprintf( fp, indent + 2, "XLL\n" );
        if( construction_flags & DTS_EXT_SUBSTREAM_LBR_FLAG )
            lsmash_ifprintf( fp, indent + 2, "LBR\n" );
    }
    lsmash_ifprintf( fp, indent, "CoreLFEPresent = %s\n", CoreLFEPresent ? "1 (LFE exists)" : "0 (no LFE)" );
    if( core_layout_description[CoreLayout] )
        lsmash_ifprintf( fp, indent, "CoreLayout = %"PRIu8" (%s)\n", CoreLayout, core_layout_description[CoreLayout] );
    else
        lsmash_ifprintf( fp, indent, "CoreLayout = %"PRIu8" (Undefined)\n", CoreLayout );
    if( CoreSize )
        lsmash_ifprintf( fp, indent, "CoreSize = %"PRIu16"\n", CoreSize );
    else
        lsmash_ifprintf( fp, indent, "CoreSize = 0 (no core substream exists)\n" );
    lsmash_ifprintf( fp, indent, "StereoDownmix = %s\n", StereoDownmix ? "1 (embedded downmix present)" : "0 (no embedded downmix)" );
    lsmash_ifprintf( fp, indent, "RepresentationType = %"PRIu8" (%s)\n", RepresentationType, representation_type_description[RepresentationType] );
    lsmash_ifprintf( fp, indent, "ChannelLayout = 0x%04"PRIx16"\n", ChannelLayout );
    if( ChannelLayout )
        for( int i = 0; i < 16; i++ )
            if( (ChannelLayout >> i) & 0x01 )
                lsmash_ifprintf( fp, indent + 1, "%s\n", channel_layout_description[i] );
    lsmash_ifprintf( fp, indent, "MultiAssetFlag = %s\n", MultiAssetFlag ? "1 (multiple asset)" : "0 (single asset)" );
    if( LBRDurationMod )
        lsmash_ifprintf( fp, indent, "LBRDurationMod = 1 (%"PRIu32" -> %"PRIu32" samples)\n", frame_duration, (frame_duration * 3) / 2 );
    else
        lsmash_ifprintf( fp, indent, "LBRDurationMod = 0 (no LBR duration modifier)\n" );
    lsmash_ifprintf( fp, indent, "ReservedBoxPresent = %s\n", ReservedBoxPresent ? "1 (ReservedBox present)" : "0 (no ReservedBox)" );
    lsmash_ifprintf( fp, indent, "Reserved = 0x%02"PRIx8"\n", Reserved );
    return 0;
}

int dts_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_audio_entry_t *dts_audio = (isom_audio_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( dts_audio ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_box_t *ext = isom_get_extension_box( &dts_audio->extensions, ISOM_BOX_TYPE_DDTS );
    if( !((ext->manager & LSMASH_BINARY_CODED_BOX) && ext->binary && ext->size >= 28) )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    if( err < 0 )
        return err;
    if( !isom_is_variable_size( stbl ) )
        maxBitrate = avgBitrate;
    uint8_t *exdata = ext->binary + 12;
    LSMASH_SET_BE32( &exdata[0], maxBitrate );
    LSMASH_SET_BE32( &exdata[4], avgBitrate );
    return 0;
}

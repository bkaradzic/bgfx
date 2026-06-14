/*****************************************************************************
 * print.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
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
#include <stdarg.h> /* for isom_iprintf */

#include "box.h"


typedef int (*isom_print_box_t)( FILE *, lsmash_file_t *, isom_box_t *, int );

typedef struct
{
    int              level;
    isom_box_t      *box;
    isom_print_box_t func;
} isom_print_entry_t;

static void isom_ifprintf_duration( FILE *fp, int indent, char *field_name, uint64_t duration, uint32_t timescale )
{
    if( !timescale )
    {
        lsmash_ifprintf( fp, indent, "duration = %"PRIu64"\n", duration );
        return;
    }
    int dur = duration / timescale;
    int hour =  dur / 3600;
    int min  = (dur /   60) % 60;
    int sec  =  dur         % 60;
    int ms   = ((double)duration / timescale - (hour * 3600 + min * 60 + sec)) * 1e3 + 0.5;
    static char str[32];
    sprintf( str, "%02d:%02d:%02d.%03d", hour, min, sec, ms );
    lsmash_ifprintf( fp, indent, "%s = %"PRIu64" (%s)\n", field_name, duration, str );
}

static char *isom_mp4time2utc( uint64_t mp4time )
{
    int year_offset = mp4time / 31536000;
    int leap_years = year_offset / 4 + ((mp4time / 86400) > 366);   /* 1904 itself is leap year */
    int day = (mp4time / 86400) - (year_offset * 365) - leap_years + 1;
    while( day < 1 )
    {
        --year_offset;
        leap_years = year_offset / 4 + ((mp4time / 86400) > 366);
        day = (mp4time / 86400) - (year_offset * 365) - leap_years + 1;
    }
    int year = 1904 + year_offset;
    int is_leap = (!(year % 4) && (year % 100)) || !(year % 400);
    static const int month_days[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int month;
    for( month = 1; month <= 12; month++ )
    {
        int i = (month == 2 && is_leap) ? 0 : month;
        if( day <= month_days[i] )
            break;
        day -= month_days[i];
    }
    int hour = (mp4time / 3600) % 24;
    int min  = (mp4time /   60) % 60;
    int sec  =  mp4time         % 60;
    static char utc[64];
    sprintf( utc, "UTC %d/%02d/%02d, %02d:%02d:%02d\n", year, month, day, hour, min, sec );
    return utc;
}

static void isom_ifprintf_matrix( FILE *fp, int indent, int32_t *matrix )
{
    lsmash_ifprintf( fp, indent, "| a, b, u |   | %f, %f, %f |\n", lsmash_fixed2double( matrix[0], 16 ),
                                                            lsmash_fixed2double( matrix[1], 16 ),
                                                            lsmash_fixed2double( matrix[2], 30 ) );
    lsmash_ifprintf( fp, indent, "| c, d, v | = | %f, %f, %f |\n", lsmash_fixed2double( matrix[3], 16 ),
                                                            lsmash_fixed2double( matrix[4], 16 ),
                                                            lsmash_fixed2double( matrix[5], 30 ) );
    lsmash_ifprintf( fp, indent, "| x, y, w |   | %f, %f, %f |\n", lsmash_fixed2double( matrix[6], 16 ),
                                                            lsmash_fixed2double( matrix[7], 16 ),
                                                            lsmash_fixed2double( matrix[8], 30 ) );
}

static void isom_ifprintf_rgb_color( FILE *fp, int indent, uint16_t *color )
{
    lsmash_ifprintf( fp, indent, "{ R, G, B } = { %"PRIu16", %"PRIu16", %"PRIu16" }\n", color[0], color[1], color[2] );
}

static void isom_ifprintf_rgba_color( FILE *fp, int indent, uint8_t *color )
{
    lsmash_ifprintf( fp, indent, "{ R, G, B, A } = { %"PRIu8", %"PRIu8", %"PRIu8", %"PRIu8" }\n", color[0], color[1], color[2], color[3] );
}

static char *isom_unpack_iso_language( uint16_t language )
{
    static char unpacked[4];
    unpacked[0] = ((language >> 10) & 0x1f) + 0x60;
    unpacked[1] = ((language >>  5) & 0x1f) + 0x60;
    unpacked[2] = ( language        & 0x1f) + 0x60;
    unpacked[3] = 0;
    return unpacked;
}

static void isom_ifprintf_sample_description_common_reserved( FILE *fp, int indent, uint8_t *reserved )
{
    uint64_t temp = ((uint64_t)reserved[0] << 40)
                  | ((uint64_t)reserved[1] << 32)
                  | ((uint64_t)reserved[2] << 24)
                  | ((uint64_t)reserved[3] << 16)
                  | ((uint64_t)reserved[4] <<  8)
                  |  (uint64_t)reserved[5];
    lsmash_ifprintf( fp, indent, "reserved = 0x%012"PRIx64"\n", temp );
}

static void isom_ifprintf_sample_flags( FILE *fp, int indent, char *field_name, isom_sample_flags_t *flags )
{
    uint32_t temp = (flags->reserved                  << 28)
                  | (flags->is_leading                << 26)
                  | (flags->sample_depends_on         << 24)
                  | (flags->sample_is_depended_on     << 22)
                  | (flags->sample_has_redundancy     << 20)
                  | (flags->sample_padding_value      << 17)
                  | (flags->sample_is_non_sync_sample << 16)
                  |  flags->sample_degradation_priority;
    lsmash_ifprintf( fp, indent++, "%s = 0x%08"PRIx32"\n", field_name, temp );
    if     ( flags->is_leading == ISOM_SAMPLE_IS_UNDECODABLE_LEADING       ) lsmash_ifprintf( fp, indent, "undecodable leading\n" );
    else if( flags->is_leading == ISOM_SAMPLE_IS_NOT_LEADING               ) lsmash_ifprintf( fp, indent, "non-leading\n" );
    else if( flags->is_leading == ISOM_SAMPLE_IS_DECODABLE_LEADING         ) lsmash_ifprintf( fp, indent, "decodable leading\n" );
    if     ( flags->sample_depends_on == ISOM_SAMPLE_IS_INDEPENDENT        ) lsmash_ifprintf( fp, indent, "independent\n" );
    else if( flags->sample_depends_on == ISOM_SAMPLE_IS_NOT_INDEPENDENT    ) lsmash_ifprintf( fp, indent, "dependent\n" );
    if     ( flags->sample_is_depended_on == ISOM_SAMPLE_IS_NOT_DISPOSABLE ) lsmash_ifprintf( fp, indent, "non-disposable\n" );
    else if( flags->sample_is_depended_on == ISOM_SAMPLE_IS_DISPOSABLE     ) lsmash_ifprintf( fp, indent, "disposable\n" );
    if     ( flags->sample_has_redundancy == ISOM_SAMPLE_HAS_REDUNDANCY    ) lsmash_ifprintf( fp, indent, "redundant\n" );
    else if( flags->sample_has_redundancy == ISOM_SAMPLE_HAS_NO_REDUNDANCY ) lsmash_ifprintf( fp, indent, "non-redundant\n" );
    if( flags->sample_padding_value )
        lsmash_ifprintf( fp, indent, "padding_bits = %"PRIu8"\n", flags->sample_padding_value );
    lsmash_ifprintf( fp, indent, flags->sample_is_non_sync_sample ? "non-sync sample\n" : "sync sample\n" );
    lsmash_ifprintf( fp, indent, "degradation_priority = %"PRIu16"\n", flags->sample_degradation_priority );
}

static inline int isom_print_simple( FILE *fp, isom_box_t *box, int level, char *name )
{
    int indent = level;
    if( box->type.fourcc != ISOM_BOX_TYPE_UUID.fourcc )
    {
        lsmash_ifprintf( fp, indent++, "[%s: %s]\n", isom_4cc2str( box->type.fourcc ), name );
        lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
        lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    }
    else
    {
        lsmash_ifprintf( fp, indent++, "[uuid: UUID Box]\n" );
        lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
        lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
        lsmash_ifprintf( fp, indent++, "usertype\n" );
        if( isom_is_printable_4cc( box->type.user.fourcc ) )
            lsmash_ifprintf( fp, indent, "type = %s\n", isom_4cc2str( box->type.user.fourcc ) );
        lsmash_ifprintf( fp, indent, "name = %s\n", name );
        lsmash_ifprintf( fp, indent, "uuid = 0x%08"PRIx32"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"0x%08"PRIx32"\n",
                         box->type.user.fourcc,
                         (box->type.user.id[0] << 8) | box->type.user.id[1], (box->type.user.id[2] << 8) | box->type.user.id[3],
                         (box->type.user.id[4] << 8) | box->type.user.id[5], (box->type.user.id[6] << 8) | box->type.user.id[7],
                         (box->type.user.id[8] << 24) | (box->type.user.id[9] << 16) | (box->type.user.id[10] << 8) | box->type.user.id[11] );
    }
    return 0;
}

static void isom_print_basebox_common( FILE *fp, int indent, isom_box_t *box, char *name )
{
    isom_print_simple( fp, box, indent, name );
}

static void isom_print_fullbox_common( FILE *fp, int indent, isom_box_t *box, char *name )
{
    isom_print_simple( fp, box, indent++, name );
    lsmash_ifprintf( fp, indent, "version = %"PRIu8"\n", box->version );
    lsmash_ifprintf( fp, indent, "flags = 0x%06"PRIx32"\n", box->flags & 0x00ffffff );
}

static void isom_print_box_common( FILE *fp, int indent, isom_box_t *box, char *name )
{
    isom_box_t *parent = box->parent;
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
    {
        isom_print_basebox_common( fp, indent, box, name );
        return;
    }
    if( isom_is_fullbox( box ) )
        isom_print_fullbox_common( fp, indent, box, name );
    else
        isom_print_basebox_common( fp, indent, box, name );
}

static int isom_print_unknown( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    int indent = level;
    if( box->type.fourcc != ISOM_BOX_TYPE_UUID.fourcc )
    {
        lsmash_ifprintf( fp, indent++, "[%s]\n", isom_4cc2str( box->type.fourcc ) );
        lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
        lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
    }
    else
    {
        lsmash_ifprintf( fp, indent++, "[uuid: UUID Box]\n" );
        lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
        lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
        lsmash_ifprintf( fp, indent++, "usertype\n" );
        if( isom_is_printable_4cc( box->type.user.fourcc ) )
            lsmash_ifprintf( fp, indent, "type = %s\n", isom_4cc2str( box->type.user.fourcc ) );
        lsmash_ifprintf( fp, indent, "uuid = 0x%08"PRIx32"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"%08"PRIx32"\n",
                         box->type.user.fourcc,
                         (box->type.user.id[0] << 8) | box->type.user.id[1], (box->type.user.id[2] << 8) | box->type.user.id[3],
                         (box->type.user.id[4] << 8) | box->type.user.id[5], (box->type.user.id[6] << 8) | box->type.user.id[7],
                         (box->type.user.id[8] << 24) | (box->type.user.id[9] << 16) | (box->type.user.id[10] << 8) | box->type.user.id[11] );
    }
    return 0;
}

static void isom_print_brand_description( FILE *fp, lsmash_brand_type brand )
{
    if( brand == 0 )
        return;
    static const struct
    {
        lsmash_brand_type brand;
        char             *description;
    } brand_description_table[] =
        {
            { ISOM_BRAND_TYPE_3G2A, "3GPP2" },
            { ISOM_BRAND_TYPE_3GE6, "3GPP Release 6 Extended Presentation Profile" },
            { ISOM_BRAND_TYPE_3GE9, "3GPP Release 9 Extended Presentation Profile" },
            { ISOM_BRAND_TYPE_3GF9, "3GPP Release 9 File-delivery Server Profile" },
            { ISOM_BRAND_TYPE_3GG6, "3GPP Release 6 General Profile" },
            { ISOM_BRAND_TYPE_3GG9, "3GPP Release 9 General Profile" },
            { ISOM_BRAND_TYPE_3GH9, "3GPP Release 9 Adaptive Streaming Profile" },
            { ISOM_BRAND_TYPE_3GM9, "3GPP Release 9 Media Segment Profile" },
            { ISOM_BRAND_TYPE_3GP4, "3GPP Release 4" },
            { ISOM_BRAND_TYPE_3GP5, "3GPP Release 5" },
            { ISOM_BRAND_TYPE_3GP6, "3GPP Release 6 Basic Profile" },
            { ISOM_BRAND_TYPE_3GP7, "3GPP Release 7" },
            { ISOM_BRAND_TYPE_3GP8, "3GPP Release 8" },
            { ISOM_BRAND_TYPE_3GP9, "3GPP Release 9 Basic Profile" },
            { ISOM_BRAND_TYPE_3GR6, "3GPP Release 6 Progressive Download Profile" },
            { ISOM_BRAND_TYPE_3GR9, "3GPP Release 9 Progressive Download Profile" },
            { ISOM_BRAND_TYPE_3GS6, "3GPP Release 6 Streaming Server Profile" },
            { ISOM_BRAND_TYPE_3GS9, "3GPP Release 9 Streaming Server Profile" },
            { ISOM_BRAND_TYPE_3GT9, "3GPP Release 9 Media Stream Recording Profile" },
            { ISOM_BRAND_TYPE_ARRI, "ARRI Digital Camera" },
            { ISOM_BRAND_TYPE_CAEP, "Canon Digital Camera" },
            { ISOM_BRAND_TYPE_CDES, "Convergent Designs" },
            { ISOM_BRAND_TYPE_LCAG, "Leica digital camera" },
            { ISOM_BRAND_TYPE_M4A , "iTunes MPEG-4 audio protected or not" },
            { ISOM_BRAND_TYPE_M4B , "iTunes AudioBook protected or not" },
            { ISOM_BRAND_TYPE_M4P , "MPEG-4 protected audio" },
            { ISOM_BRAND_TYPE_M4V , "MPEG-4 protected audio+video" },
            { ISOM_BRAND_TYPE_MFSM, "Media File for Samsung video Metadata" },
            { ISOM_BRAND_TYPE_MPPI, "Photo Player Multimedia Application Format" },
            { ISOM_BRAND_TYPE_ROSS, "Ross Video" },
            { ISOM_BRAND_TYPE_AVC1, "Advanced Video Coding extensions" },
            { ISOM_BRAND_TYPE_BBXM, "Blinkbox Master File" },
            { ISOM_BRAND_TYPE_CAQV, "Casio Digital Camera" },
            { ISOM_BRAND_TYPE_CCFF, "Common container file format" },
            { ISOM_BRAND_TYPE_DA0A, "DMB AF" },
            { ISOM_BRAND_TYPE_DA0B, "DMB AF" },
            { ISOM_BRAND_TYPE_DA1A, "DMB AF" },
            { ISOM_BRAND_TYPE_DA1B, "DMB AF" },
            { ISOM_BRAND_TYPE_DA2A, "DMB AF" },
            { ISOM_BRAND_TYPE_DA2B, "DMB AF" },
            { ISOM_BRAND_TYPE_DA3A, "DMB AF" },
            { ISOM_BRAND_TYPE_DA3B, "DMB AF" },
            { ISOM_BRAND_TYPE_DASH, "Indexed self-initializing Media Segment" },
            { ISOM_BRAND_TYPE_DBY1, "MP4 files with Dolby content" },
            { ISOM_BRAND_TYPE_DMB1, "DMB AF" },
            { ISOM_BRAND_TYPE_DSMS, "Self-initializing Media Segment" },
            { ISOM_BRAND_TYPE_DV1A, "DMB AF" },
            { ISOM_BRAND_TYPE_DV1B, "DMB AF" },
            { ISOM_BRAND_TYPE_DV2A, "DMB AF" },
            { ISOM_BRAND_TYPE_DV2B, "DMB AF" },
            { ISOM_BRAND_TYPE_DV3A, "DMB AF" },
            { ISOM_BRAND_TYPE_DV3B, "DMB AF" },
            { ISOM_BRAND_TYPE_DVR1, "DVB RTP" },
            { ISOM_BRAND_TYPE_DVT1, "DVB Transport Stream" },
            { ISOM_BRAND_TYPE_IFRM, "Apple iFrame" },
            { ISOM_BRAND_TYPE_ISC2, "Files encrypted according to ISMACryp 2.0" },
            { ISOM_BRAND_TYPE_ISO2, "ISO Base Media file format version 2" },
            { ISOM_BRAND_TYPE_ISO3, "ISO Base Media file format version 3" },
            { ISOM_BRAND_TYPE_ISO4, "ISO Base Media file format version 4" },
            { ISOM_BRAND_TYPE_ISO5, "ISO Base Media file format version 5" },
            { ISOM_BRAND_TYPE_ISO6, "ISO Base Media file format version 6" },
            { ISOM_BRAND_TYPE_ISO7, "ISO Base Media file format version 7" },
            { ISOM_BRAND_TYPE_ISOM, "ISO Base Media file format version 1" },
            { ISOM_BRAND_TYPE_JPSI, "The JPSearch data interchange format" },
            { ISOM_BRAND_TYPE_LMSG, "last Media Segment indicator" },
            { ISOM_BRAND_TYPE_MJ2S, "Motion JPEG 2000 simple profile" },
            { ISOM_BRAND_TYPE_MJP2, "Motion JPEG 2000, general profile" },
            { ISOM_BRAND_TYPE_MP21, "MPEG-21" },
            { ISOM_BRAND_TYPE_MP41, "MP4 version 1" },
            { ISOM_BRAND_TYPE_MP42, "MP4 version 2" },
            { ISOM_BRAND_TYPE_MP71, "MPEG-7 file-level metadata" },
            { ISOM_BRAND_TYPE_MSDH, "Media Segment" },
            { ISOM_BRAND_TYPE_MSIX, "Indexed Media Segment" },
            { ISOM_BRAND_TYPE_NIKO, "Nikon Digital Camera" },
            { ISOM_BRAND_TYPE_ODCF, "OMA DCF" },
            { ISOM_BRAND_TYPE_OPF2, "OMA PDCF" },
            { ISOM_BRAND_TYPE_OPX2, "OMA Adapted PDCF" },
            { ISOM_BRAND_TYPE_PANA, "Panasonic Digital Camera" },
            { ISOM_BRAND_TYPE_PIFF, "Protected Interoperable File Format" },
            { ISOM_BRAND_TYPE_PNVI, "Panasonic Video Intercom" },
            { ISOM_BRAND_TYPE_QT  , "QuickTime file format" },
            { ISOM_BRAND_TYPE_RISX, "Representation Index Segment" },
            { ISOM_BRAND_TYPE_SDV , "SD Video" },
            { ISOM_BRAND_TYPE_SIMS, "Sub-Indexed Media Segment" },
            { ISOM_BRAND_TYPE_SISX, "Single Index Segment" },
            { ISOM_BRAND_TYPE_SSSS, "Subsegment Index Segment" },
            { 0,                    NULL }
        };
    for( int i = 0; brand_description_table[i].description; i++ )
        if( brand == brand_description_table[i].brand )
        {
            fprintf( fp, " : %s\n", brand_description_table[i].description );
            return;
        }
    fprintf( fp, "\n" );
}

static void isom_print_file_type
(
    FILE     *fp,
    int       indent,
    uint32_t  major_brand,
    uint32_t  minor_version,
    uint32_t  brand_count,
    uint32_t *compatible_brands
)
{
    lsmash_ifprintf( fp, indent, "major_brand = %s", isom_4cc2str( major_brand ) );
    isom_print_brand_description( fp, major_brand );
    lsmash_ifprintf( fp, indent, "minor_version = %"PRIu32"\n", minor_version );
    lsmash_ifprintf( fp, indent++, "compatible_brands\n" );
    for( uint32_t i = 0; i < brand_count; i++ )
    {
        if( compatible_brands[i] )
        {
            lsmash_ifprintf( fp, indent, "brand[%"PRIu32"] = %s", i, isom_4cc2str( compatible_brands[i] ) );
            isom_print_brand_description( fp, compatible_brands[i] );
        }
        else
            lsmash_ifprintf( fp, indent, "brand[%"PRIu32"] = (void)\n", i );
    }
}

static int isom_print_ftyp( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_ftyp_t *ftyp = (isom_ftyp_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "File Type Box" );
    isom_print_file_type( fp, indent, ftyp->major_brand, ftyp->minor_version, ftyp->brand_count, ftyp->compatible_brands );
    return 0;
}

static int isom_print_styp( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    /* Print 'valid' if this box is the first box in a file. */
    int valid;
    if( file->print
     && file->print->head
     && file->print->head->data )
        valid = (box == ((isom_print_entry_t *)file->print->head->data)->box);
    else
        valid = 0;
    char *name = valid ? "Segment Type Box (valid)" : "Segment Type Box";
    isom_styp_t *styp = (isom_styp_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, name );
    isom_print_file_type( fp, indent, styp->major_brand, styp->minor_version, styp->brand_count, styp->compatible_brands );
    return 0;
}

static int isom_print_sidx( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_sidx_t *)box)->list )
        return -1;
    isom_sidx_t *sidx = (isom_sidx_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Segment Index Box" );
    lsmash_ifprintf( fp, indent, "reference_ID = %"PRIu32"\n", sidx->reference_ID );
    lsmash_ifprintf( fp, indent, "timescale = %"PRIu32"\n", sidx->timescale );
    lsmash_ifprintf( fp, indent, "earliest_presentation_time = %"PRIu64"\n", sidx->earliest_presentation_time );
    lsmash_ifprintf( fp, indent, "first_offset = %"PRIu64"\n", sidx->first_offset );
    lsmash_ifprintf( fp, indent, "reserved = %"PRIu16"\n", sidx->reserved );
    lsmash_ifprintf( fp, indent, "reference_count = %"PRIu16"\n", sidx->reference_count );
    uint32_t i = 0;
    for( lsmash_entry_t *entry = sidx->list->head; entry; entry = entry->next )
    {
        isom_sidx_referenced_item_t *data = (isom_sidx_referenced_item_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "reference_type = %"PRIu8" (%s)\n", data->reference_type, data->reference_type ? "index" : "media" );
        lsmash_ifprintf( fp, indent, "reference_size = %"PRIu32"\n", data->reference_size );
        lsmash_ifprintf( fp, indent, "subsegment_duration = %"PRIu32"\n", data->subsegment_duration );
        lsmash_ifprintf( fp, indent, "starts_with_SAP = %"PRIu8"%s\n", data->starts_with_SAP, data->starts_with_SAP ? " (yes)" : "" );
        lsmash_ifprintf( fp, indent, "SAP_type = %"PRIu8"%s\n", data->SAP_type, data->SAP_type == 0 ? " (unknown)" : "" );
        lsmash_ifprintf( fp, indent--, "SAP_delta_time = %"PRIu32"\n", data->SAP_delta_time );
    }
    return 0;
}

static int isom_print_moov( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Movie Box" );
}

static int isom_print_mvhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mvhd_t *mvhd = (isom_mvhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Movie Header Box" );
    lsmash_ifprintf( fp, indent, "creation_time = %s", isom_mp4time2utc( mvhd->creation_time ) );
    lsmash_ifprintf( fp, indent, "modification_time = %s", isom_mp4time2utc( mvhd->modification_time ) );
    lsmash_ifprintf( fp, indent, "timescale = %"PRIu32"\n", mvhd->timescale );
    isom_ifprintf_duration( fp, indent, "duration", mvhd->duration, mvhd->timescale );
    lsmash_ifprintf( fp, indent, "rate = %f\n", lsmash_fixed2double( mvhd->rate, 16 ) );
    lsmash_ifprintf( fp, indent, "volume = %f\n", lsmash_fixed2double( mvhd->volume, 8 ) );
    lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", mvhd->reserved );
    if( file->qt_compatible )
    {
        lsmash_ifprintf( fp, indent, "preferredLong1 = 0x%08"PRIx32"\n", mvhd->preferredLong[0] );
        lsmash_ifprintf( fp, indent, "preferredLong2 = 0x%08"PRIx32"\n", mvhd->preferredLong[1] );
        lsmash_ifprintf( fp, indent, "transformation matrix\n" );
        isom_ifprintf_matrix( fp, indent + 1, mvhd->matrix );
        lsmash_ifprintf( fp, indent, "previewTime = %"PRId32"\n", mvhd->previewTime );
        lsmash_ifprintf( fp, indent, "previewDuration = %"PRId32"\n", mvhd->previewDuration );
        lsmash_ifprintf( fp, indent, "posterTime = %"PRId32"\n", mvhd->posterTime );
        lsmash_ifprintf( fp, indent, "selectionTime = %"PRId32"\n", mvhd->selectionTime );
        lsmash_ifprintf( fp, indent, "selectionDuration = %"PRId32"\n", mvhd->selectionDuration );
        lsmash_ifprintf( fp, indent, "currentTime = %"PRId32"\n", mvhd->currentTime );
    }
    else
    {
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", mvhd->preferredLong[0] );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", mvhd->preferredLong[1] );
        lsmash_ifprintf( fp, indent, "transformation matrix\n" );
        isom_ifprintf_matrix( fp, indent + 1, mvhd->matrix );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->previewTime );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->previewDuration );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->posterTime );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->selectionTime );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->selectionDuration );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", mvhd->currentTime );
    }
    lsmash_ifprintf( fp, indent, "next_track_ID = %"PRIu32"\n", mvhd->next_track_ID );
    return 0;
}

static void isom_pring_qt_color_table( FILE *fp, int indent, isom_qt_color_table_t *color_table )
{
    isom_qt_color_array_t *array = color_table->array;
    if( !array )
        return;
    lsmash_ifprintf( fp, indent, "ctSeed = %"PRIu32"\n", color_table->seed );
    lsmash_ifprintf( fp, indent, "ctFlags = 0x%04"PRIx16"\n", color_table->flags );
    lsmash_ifprintf( fp, indent, "ctSize = %"PRIu16"\n", color_table->size );
    lsmash_ifprintf( fp, indent++, "ctTable\n" );
    for( uint16_t i = 0; i <= color_table->size; i++ )
        lsmash_ifprintf( fp, indent,
                         "color[%"PRIu16"] = { 0x%04"PRIx16", 0x%04"PRIx16", 0x%04"PRIx16", 0x%04"PRIx16" }\n",
                         i, array[i].value, array[i].r, array[i].g, array[i].b );
}

static int isom_print_ctab( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_ctab_t *ctab = (isom_ctab_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent, box, "Color Table Box" );
    isom_pring_qt_color_table( fp, indent + 1, &ctab->color_table );
    return 0;
}

static int isom_print_iods( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    extern void mp4sys_print_descriptor( FILE *, void *, int );
    isom_iods_t *iods = (isom_iods_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent, box, "Object Descriptor Box" );
    mp4sys_print_descriptor( fp, iods->OD, indent + 1 );
    return 0;
}

static int isom_print_trak( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Track Box" );
}

static int isom_print_tkhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tkhd_t *tkhd = (isom_tkhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Header Box" );
    ++indent;
    if( tkhd->flags & ISOM_TRACK_ENABLED )
        lsmash_ifprintf( fp, indent, "Track enabled\n" );
    else
        lsmash_ifprintf( fp, indent, "Track disabled\n" );
    if( tkhd->flags & ISOM_TRACK_IN_MOVIE )
        lsmash_ifprintf( fp, indent, "Track in movie\n" );
    if( tkhd->flags & ISOM_TRACK_IN_PREVIEW )
        lsmash_ifprintf( fp, indent, "Track in preview\n" );
    if( file->qt_compatible && (tkhd->flags & QT_TRACK_IN_POSTER) )
        lsmash_ifprintf( fp, indent, "Track in poster\n" );
    lsmash_ifprintf( fp, --indent, "creation_time = %s", isom_mp4time2utc( tkhd->creation_time ) );
    lsmash_ifprintf( fp, indent, "modification_time = %s", isom_mp4time2utc( tkhd->modification_time ) );
    lsmash_ifprintf( fp, indent, "track_ID = %"PRIu32"\n", tkhd->track_ID );
    lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", tkhd->reserved1 );
    if( file->moov && file->moov->mvhd )
        isom_ifprintf_duration( fp, indent, "duration", tkhd->duration, file->moov->mvhd->timescale );
    else
        isom_ifprintf_duration( fp, indent, "duration", tkhd->duration, 0 );
    lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", tkhd->reserved2[0] );
    lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", tkhd->reserved2[1] );
    lsmash_ifprintf( fp, indent, "layer = %"PRId16"\n", tkhd->layer );
    lsmash_ifprintf( fp, indent, "alternate_group = %"PRId16"\n", tkhd->alternate_group );
    lsmash_ifprintf( fp, indent, "volume = %f\n", lsmash_fixed2double( tkhd->volume, 8 ) );
    lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", tkhd->reserved3 );
    lsmash_ifprintf( fp, indent, "transformation matrix\n" );
    isom_ifprintf_matrix( fp, indent + 1, tkhd->matrix );
    lsmash_ifprintf( fp, indent, "width = %f\n", lsmash_fixed2double( tkhd->width, 16 ) );
    lsmash_ifprintf( fp, indent, "height = %f\n", lsmash_fixed2double( tkhd->height, 16 ) );
    return 0;
}

static int isom_print_tapt( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Track Aperture Mode Dimensions Box" );
}

static int isom_print_clef( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_clef_t *clef = (isom_clef_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Clean Aperture Dimensions Box" );
    lsmash_ifprintf( fp, indent, "width = %f\n", lsmash_fixed2double( clef->width, 16 ) );
    lsmash_ifprintf( fp, indent, "height = %f\n", lsmash_fixed2double( clef->height, 16 ) );
    return 0;
}

static int isom_print_prof( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_prof_t *prof = (isom_prof_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Production Aperture Dimensions Box" );
    lsmash_ifprintf( fp, indent, "width = %f\n", lsmash_fixed2double( prof->width, 16 ) );
    lsmash_ifprintf( fp, indent, "height = %f\n", lsmash_fixed2double( prof->height, 16 ) );
    return 0;
}

static int isom_print_enof( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_enof_t *enof = (isom_enof_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Encoded Pixels Dimensions Box" );
    lsmash_ifprintf( fp, indent, "width = %f\n", lsmash_fixed2double( enof->width, 16 ) );
    lsmash_ifprintf( fp, indent, "height = %f\n", lsmash_fixed2double( enof->height, 16 ) );
    return 0;
}

static int isom_print_edts( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Edit Box" );
}

static int isom_print_elst( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_elst_t *elst = (isom_elst_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Edit List Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", elst->list->entry_count );
    for( lsmash_entry_t *entry = elst->list->head; entry; entry = entry->next )
    {
        isom_elst_entry_t *data = (isom_elst_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "segment_duration = %"PRIu64"\n", data->segment_duration );
        lsmash_ifprintf( fp, indent, "media_time = %"PRId64"\n", data->media_time );
        lsmash_ifprintf( fp, indent--, "media_rate = %f\n", lsmash_fixed2double( data->media_rate, 16 ) );
    }
    return 0;
}

static int isom_print_tref( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Track Reference Box" );
}

static int isom_print_track_reference_type( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tref_type_t *ref = (isom_tref_type_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Reference Type Box" );
    for( uint32_t i = 0; i < ref->ref_count; i++ )
        lsmash_ifprintf( fp, indent, "track_ID[%"PRIu32"] = %"PRIu32"\n", i, ref->track_ID[i] );
    return 0;
}

static int isom_print_mdia( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Media Box" );
}

static int isom_print_mdhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mdhd_t *mdhd = (isom_mdhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Media Header Box" );
    lsmash_ifprintf( fp, indent, "creation_time = %s", isom_mp4time2utc( mdhd->creation_time ) );
    lsmash_ifprintf( fp, indent, "modification_time = %s", isom_mp4time2utc( mdhd->modification_time ) );
    lsmash_ifprintf( fp, indent, "timescale = %"PRIu32"\n", mdhd->timescale );
    isom_ifprintf_duration( fp, indent, "duration", mdhd->duration, mdhd->timescale );
    if( mdhd->language >= 0x800 )
        lsmash_ifprintf( fp, indent, "language = %s\n", isom_unpack_iso_language( mdhd->language ) );
    else
        lsmash_ifprintf( fp, indent, "language = %"PRIu16"\n", mdhd->language );
    if( file->qt_compatible )
        lsmash_ifprintf( fp, indent, "quality = %"PRId16"\n", mdhd->quality );
    else
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%04"PRIx16"\n", mdhd->quality );
    return 0;
}

static int isom_print_hdlr( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_hdlr_t *hdlr = (isom_hdlr_t *)box;
    int indent = level;
    char *str = lsmash_malloc( hdlr->componentName_length + 1 );
    if( !str )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( str, hdlr->componentName, hdlr->componentName_length );
    str[hdlr->componentName_length] = 0;
    isom_print_box_common( fp, indent++, box, "Handler Reference Box" );
    if( file->qt_compatible )
    {
        lsmash_ifprintf( fp, indent, "componentType = %s\n", isom_4cc2str( hdlr->componentType ) );
        lsmash_ifprintf( fp, indent, "componentSubtype = %s\n", isom_4cc2str( hdlr->componentSubtype ) );
        lsmash_ifprintf( fp, indent, "componentManufacturer = %s\n", isom_4cc2str( hdlr->componentManufacturer ) );
        lsmash_ifprintf( fp, indent, "componentFlags = 0x%08"PRIx32"\n", hdlr->componentFlags );
        lsmash_ifprintf( fp, indent, "componentFlagsMask = 0x%08"PRIx32"\n", hdlr->componentFlagsMask );
        if( hdlr->componentName_length )
            lsmash_ifprintf( fp, indent, "componentName = %s\n", &str[1] );
        else
            lsmash_ifprintf( fp, indent, "componentName = \n" );
    }
    else
    {
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", hdlr->componentType );
        lsmash_ifprintf( fp, indent, "handler_type = %s\n", isom_4cc2str( hdlr->componentSubtype ) );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", hdlr->componentManufacturer );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", hdlr->componentFlags );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", hdlr->componentFlagsMask );
        lsmash_ifprintf( fp, indent, "name = %s\n", str );
    }
    lsmash_free( str );
    return 0;
}

static int isom_print_minf( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Media Information Box" );
}

static int isom_print_vmhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_vmhd_t *vmhd = (isom_vmhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Video Media Header Box" );
    lsmash_ifprintf( fp, indent, "graphicsmode = %"PRIu16"\n", vmhd->graphicsmode );
    lsmash_ifprintf( fp, indent, "opcolor\n" );
    isom_ifprintf_rgb_color( fp, indent + 1, vmhd->opcolor );
    return 0;
}

static int isom_print_smhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_smhd_t *smhd = (isom_smhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Sound Media Header Box" );
    lsmash_ifprintf( fp, indent, "balance = %f\n", lsmash_fixed2double( smhd->balance, 8 ) );
    lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", smhd->reserved );
    return 0;
}

static int isom_print_hmhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_hmhd_t *hmhd = (isom_hmhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Hint Media Header Box" );
    lsmash_ifprintf( fp, indent, "maxPDUsize = %"PRIu16"\n", hmhd->maxPDUsize );
    lsmash_ifprintf( fp, indent, "avgPDUsize = %"PRIu16"\n", hmhd->avgPDUsize );
    lsmash_ifprintf( fp, indent, "maxbitrate = %"PRIu32"\n", hmhd->maxbitrate );
    lsmash_ifprintf( fp, indent, "avgbitrate = %"PRIu32"\n", hmhd->avgbitrate );
    lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", hmhd->reserved );
    return 0;
}

static int isom_print_nmhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_print_box_common( fp, level, box, "Null Media Header Box" );
    return 0;
}

static int isom_print_gmhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Generic Media Information Header Box" );
}

static int isom_print_gmin( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_gmin_t *gmin = (isom_gmin_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Generic Media Information Box" );
    lsmash_ifprintf( fp, indent, "graphicsmode = %"PRIu16"\n", gmin->graphicsmode );
    lsmash_ifprintf( fp, indent, "opcolor\n" );
    isom_ifprintf_rgb_color( fp, indent + 1, gmin->opcolor );
    lsmash_ifprintf( fp, indent, "balance = %f\n", lsmash_fixed2double( gmin->balance, 8 ) );
    lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", gmin->reserved );
    return 0;
}

static int isom_print_text( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_text_t *text = (isom_text_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Text Media Information Box" );
    lsmash_ifprintf( fp, indent, "Unknown matrix\n" );
    isom_ifprintf_matrix( fp, indent + 1, text->matrix );
    return 0;
}

static int isom_print_dinf( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Data Information Box" );
}

static int isom_print_dref( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_dref_t *dref = (isom_dref_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Data Reference Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu16"\n", dref->list.entry_count );
    return 0;
}

static int isom_print_url( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_dref_entry_t *url = (isom_dref_entry_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Data Entry Url Box" );
    if( url->flags & 0x000001 )
        lsmash_ifprintf( fp, indent, "location = in the same file\n" );
    else
        lsmash_ifprintf( fp, indent, "location = %s\n", url->location );
    return 0;
}

static int isom_print_stbl( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Sample Table Box" );
}

static int isom_print_stsd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_stsd_t *stsd = (isom_stsd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Sample Description Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stsd->entry_count );
    return 0;
}

static int isom_print_visual_description( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_visual_entry_t *visual = (isom_visual_entry_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: Visual Description]\n", isom_4cc2str( visual->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", visual->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", visual->size );
    isom_ifprintf_sample_description_common_reserved( fp, indent, visual->reserved );
    lsmash_ifprintf( fp, indent, "data_reference_index = %"PRIu16"\n", visual->data_reference_index );
    if( file->qt_compatible )
    {
        lsmash_ifprintf( fp, indent, "version = %"PRId16"\n", visual->version );
        lsmash_ifprintf( fp, indent, "revision_level = %"PRId16"\n", visual->revision_level );
        lsmash_ifprintf( fp, indent, "vendor = %s\n", isom_4cc2str( visual->vendor ) );
        lsmash_ifprintf( fp, indent, "temporalQuality = %"PRIu32"\n", visual->temporalQuality );
        lsmash_ifprintf( fp, indent, "spatialQuality = %"PRIu32"\n", visual->spatialQuality );
        lsmash_ifprintf( fp, indent, "width = %"PRIu16"\n", visual->width );
        lsmash_ifprintf( fp, indent, "height = %"PRIu16"\n", visual->height );
        lsmash_ifprintf( fp, indent, "horizresolution = %f\n", lsmash_fixed2double( visual->horizresolution, 16 ) );
        lsmash_ifprintf( fp, indent, "vertresolution = %f\n", lsmash_fixed2double( visual->vertresolution, 16 ) );
        lsmash_ifprintf( fp, indent, "dataSize = %"PRIu32"\n", visual->dataSize );
        lsmash_ifprintf( fp, indent, "frame_count = %"PRIu16"\n", visual->frame_count );
        lsmash_ifprintf( fp, indent, "compressorname_length = %"PRIu8"\n", visual->compressorname[0] );
        lsmash_ifprintf( fp, indent, "compressorname = %s\n", visual->compressorname + 1 );
        lsmash_ifprintf( fp, indent, "depth = 0x%04"PRIx16, visual->depth );
        if( visual->depth == 32 )
            fprintf( fp, " (colour with alpha)\n" );
        else if( visual->depth >= 33 && visual->depth <= 40 )
            fprintf( fp, " (grayscale with no alpha)\n" );
        else
            fprintf( fp, "\n" );
        lsmash_ifprintf( fp, indent, "color_table_ID = %"PRId16"\n", visual->color_table_ID );
        if( visual->color_table_ID == 0 )
            isom_pring_qt_color_table( fp, indent, &visual->color_table );
    }
    else
    {
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%04"PRIx16"\n", visual->version );
        lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", visual->revision_level );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", visual->vendor );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", visual->temporalQuality );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%08"PRIx32"\n", visual->spatialQuality );
        lsmash_ifprintf( fp, indent, "width = %"PRIu16"\n", visual->width );
        lsmash_ifprintf( fp, indent, "height = %"PRIu16"\n", visual->height );
        lsmash_ifprintf( fp, indent, "horizresolution = %f\n", lsmash_fixed2double( visual->horizresolution, 16 ) );
        lsmash_ifprintf( fp, indent, "vertresolution = %f\n", lsmash_fixed2double( visual->vertresolution, 16 ) );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", visual->dataSize );
        lsmash_ifprintf( fp, indent, "frame_count = %"PRIu16"\n", visual->frame_count );
        lsmash_ifprintf( fp, indent, "compressorname_length = %"PRIu8"\n", visual->compressorname[0] );
        lsmash_ifprintf( fp, indent, "compressorname = %s\n", visual->compressorname + 1 );
        lsmash_ifprintf( fp, indent, "depth = 0x%04"PRIx16, visual->depth );
        if( visual->depth == 0x0018 )
            fprintf( fp, " (colour with no alpha)\n" );
        else if( visual->depth == 0x0028 )
            fprintf( fp, " (grayscale with no alpha)\n" );
        else if( visual->depth == 0x0020 )
            fprintf( fp, " (gray or colour with alpha)\n" );
        else
            fprintf( fp, "\n" );
        lsmash_ifprintf( fp, indent, "pre_defined = 0x%04"PRIx16"\n", visual->color_table_ID );
    }
    return 0;
}

static int isom_print_glbl( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_glbl_t *glbl = (isom_glbl_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Global Header Box" );
    if( glbl->header_data )
    {
        lsmash_ifprintf( fp, indent, "global_header[]\n" );
        for( uint32_t i = 0; i < glbl->header_size; i += 8 )
        {
            lsmash_ifprintf( fp, indent + 1, "" );
            for( uint32_t j = 0; ; j++ )
                if( j == 7 || (i + j == glbl->header_size - 1) )
                {
                    fprintf( fp, "0x%02"PRIx8"\n", glbl->header_data[i + j] );
                    break;
                }
                else
                    fprintf( fp, "0x%02"PRIx8" ", glbl->header_data[i + j] );
        }
    }
    return 0;
}

static int isom_print_clap( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_clap_t *clap = (isom_clap_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Clean Aperture Box" );
    lsmash_ifprintf( fp, indent, "cleanApertureWidthN = %"PRIu32"\n", clap->cleanApertureWidthN );
    lsmash_ifprintf( fp, indent, "cleanApertureWidthD = %"PRIu32"\n", clap->cleanApertureWidthD );
    lsmash_ifprintf( fp, indent, "cleanApertureHeightN = %"PRIu32"\n", clap->cleanApertureHeightN );
    lsmash_ifprintf( fp, indent, "cleanApertureHeightD = %"PRIu32"\n", clap->cleanApertureHeightD );
    lsmash_ifprintf( fp, indent, "horizOffN = %"PRId32"\n", clap->horizOffN );
    lsmash_ifprintf( fp, indent, "horizOffD = %"PRIu32"\n", clap->horizOffD );
    lsmash_ifprintf( fp, indent, "vertOffN = %"PRId32"\n", clap->vertOffN );
    lsmash_ifprintf( fp, indent, "vertOffD = %"PRIu32"\n", clap->vertOffD );
    return 0;
}

static int isom_print_pasp( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_pasp_t *pasp = (isom_pasp_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Pixel Aspect Ratio Box" );
    lsmash_ifprintf( fp, indent, "hSpacing = %"PRIu32"\n", pasp->hSpacing );
    lsmash_ifprintf( fp, indent, "vSpacing = %"PRIu32"\n", pasp->vSpacing );
    return 0;
}

static int isom_print_colr( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_colr_t *colr = (isom_colr_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, colr->manager & LSMASH_QTFF_BASE ? "Color Parameter Box" : "Colour Information Box" );
    lsmash_ifprintf( fp, indent, "color_parameter_type = %s\n", isom_4cc2str( colr->color_parameter_type ) );
    if( colr->color_parameter_type == QT_COLOR_PARAMETER_TYPE_NCLC
     || colr->color_parameter_type == ISOM_COLOR_PARAMETER_TYPE_NCLX )
    {
        lsmash_ifprintf( fp, indent, "primaries_index = %"PRIu16"\n", colr->primaries_index );
        lsmash_ifprintf( fp, indent, "transfer_function_index = %"PRIu16"\n", colr->transfer_function_index );
        lsmash_ifprintf( fp, indent, "matrix_index = %"PRIu16"\n", colr->matrix_index );
        if( colr->color_parameter_type == ISOM_COLOR_PARAMETER_TYPE_NCLX )
        {
            if( colr->manager & LSMASH_INCOMPLETE_BOX )
            {
                lsmash_ifprintf( fp, indent, "full_range_flag = N/A\n" );
                lsmash_ifprintf( fp, indent, "reserved = N/A\n" );
            }
            else
            {
                lsmash_ifprintf( fp, indent, "full_range_flag = %"PRIu8"\n", colr->full_range_flag );
                lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx8"\n", colr->reserved );
            }
        }
    }
    return 0;
}

static int isom_print_gama( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_gama_t *gama = (isom_gama_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Gamma Level Box" );
    if( gama->level == 0x00023333 )
        lsmash_ifprintf( fp, indent, "level = 2.2 (standard television video gamma)\n" );
    else
    {
        lsmash_ifprintf( fp, indent, "level = %f", lsmash_fixed2double( gama->level, 16 ) );
        if( gama->level == 0 )
            fprintf( fp, " (platform's standard gamma)" );
        else if( gama->level == 0xffffffff )
            fprintf( fp, " (no gamma-correction)" );
        fprintf( fp, "\n" );
    }
    return 0;
}

static int isom_print_fiel( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_fiel_t *fiel = (isom_fiel_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Field/Frame Information Box" );
    lsmash_ifprintf( fp, indent, "fields = %"PRIu8" (%s)\n", fiel->fields, fiel->fields > 1 ? "interlaced" : "progressive scan" );
    lsmash_ifprintf( fp, indent, "detail = %"PRIu8, fiel->detail );
    if( fiel->fields > 1 )
    {
        static const char *field_orderings[5] =
            { "unknown", "temporal top first", "temporal bottom first", "spatial first line early", "spatial first line late" };
        int ordering = 0;
        if( fiel->fields == 2 )
        {
            if( fiel->detail == QT_FIELD_ORDERINGS_TEMPORAL_TOP_FIRST )
                ordering = 1;
            else if( fiel->detail == QT_FIELD_ORDERINGS_TEMPORAL_BOTTOM_FIRST )
                ordering = 2;
            else if( fiel->detail == QT_FIELD_ORDERINGS_SPATIAL_FIRST_LINE_EARLY )
                ordering = 3;
            else if( fiel->detail == QT_FIELD_ORDERINGS_SPATIAL_FIRST_LINE_LATE )
                ordering = 4;
        }
        fprintf( fp, " (%s)\n", field_orderings[ordering] );
    }
    else
        fprintf( fp, "\n" );
    return 0;
}

static int isom_print_clli( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level ) {
    isom_clli_t *clli = (isom_clli_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Content Light Level Box" );
    lsmash_ifprintf( fp, indent, "max_content_light_level = %"PRIu16"\n", clli->max_content_light_level );
    lsmash_ifprintf( fp, indent, "max_pic_average_light_level = %"PRIu16"\n", clli->max_pic_average_light_level );
    return 0;
}

static int isom_print_mdcv( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level ) {
    isom_mdcv_t *mdcv = (isom_mdcv_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Mastering Display Color Volume Box" );
    lsmash_ifprintf( fp, indent, "display_primaries_g_x = %"PRIu16"\n", mdcv->display_primaries_g_x );
    lsmash_ifprintf( fp, indent, "display_primaries_g_y = %"PRIu16"\n", mdcv->display_primaries_g_y );
    lsmash_ifprintf( fp, indent, "display_primaries_b_x = %"PRIu16"\n", mdcv->display_primaries_b_x );
    lsmash_ifprintf( fp, indent, "display_primaries_b_y = %"PRIu16"\n", mdcv->display_primaries_b_y );
    lsmash_ifprintf( fp, indent, "display_primaries_r_x = %"PRIu16"\n", mdcv->display_primaries_r_x );
    lsmash_ifprintf( fp, indent, "display_primaries_r_y = %"PRIu16"\n", mdcv->display_primaries_r_y );
    lsmash_ifprintf( fp, indent, "white_point_x = %"PRIu16"\n", mdcv->white_point_x );
    lsmash_ifprintf( fp, indent, "white_point_y = %"PRIu16"\n", mdcv->white_point_y );
    lsmash_ifprintf( fp, indent, "max_display_mastering_luminance = %"PRIu32"\n", mdcv->max_display_mastering_luminance );
    lsmash_ifprintf( fp, indent, "min_display_mastering_luminance = %"PRIu32"\n", mdcv->min_display_mastering_luminance );
    return 0;
}

static int isom_print_cspc( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_cspc_t *cspc = (isom_cspc_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Colorspace Box" );
    static const struct
    {
        lsmash_qt_pixel_format pixel_format;
        char *description;
    } unprintable_pixel_format_table[] =
        {
            { QT_PIXEL_FORMAT_TYPE_1_MONOCHROME,                 "1 bit indexed"                     },
            { QT_PIXEL_FORMAT_TYPE_2_INDEXED,                    "2 bit indexed"                     },
            { QT_PIXEL_FORMAT_TYPE_4_INDEXED,                    "4 bit indexed"                     },
            { QT_PIXEL_FORMAT_TYPE_8_INDEXED,                    "8 bit indexed"                     },
            { QT_PIXEL_FORMAT_TYPE_1_INDEXED_GRAY_WHITE_IS_ZERO, "1 bit indexed gray, white is zero" },
            { QT_PIXEL_FORMAT_TYPE_2_INDEXED_GRAY_WHITE_IS_ZERO, "2 bit indexed gray, white is zero" },
            { QT_PIXEL_FORMAT_TYPE_4_INDEXED_GRAY_WHITE_IS_ZERO, "4 bit indexed gray, white is zero" },
            { QT_PIXEL_FORMAT_TYPE_8_INDEXED_GRAY_WHITE_IS_ZERO, "8 bit indexed gray, white is zero" },
            { QT_PIXEL_FORMAT_TYPE_16BE555,                      "16 bit BE RGB 555"                 },
            { QT_PIXEL_FORMAT_TYPE_24RGB,                        "24 bit RGB"                        },
            { QT_PIXEL_FORMAT_TYPE_32ARGB,                       "32 bit ARGB"                       },
            { 0, NULL }
        };
    for( int i = 0; unprintable_pixel_format_table[i].pixel_format; i++ )
        if( cspc->pixel_format == unprintable_pixel_format_table[i].pixel_format )
        {
            lsmash_ifprintf( fp, indent, "pixel_format = 0x%08"PRIx32" (%s)\n", cspc->pixel_format, unprintable_pixel_format_table[i].description );
            return 0;
        }
    lsmash_ifprintf( fp, indent, "pixel_format = %s\n", isom_4cc2str( cspc->pixel_format ) );
    return 0;
}

static int isom_print_sgbt( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_sgbt_t *sgbt = (isom_sgbt_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Significant Bits Box" );
    lsmash_ifprintf( fp, indent, "significantBits = %"PRIu8"\n", sgbt->significantBits );
    return 0;
}

static int isom_print_stsl( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_stsl_t *stsl = (isom_stsl_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Sample Scale Box" );
    lsmash_ifprintf( fp, indent, "constraint_flag = %s\n", (stsl->constraint_flag & 0x01) ? "on" : "off" );
    lsmash_ifprintf( fp, indent, "scale_method = " );
    if( stsl->scale_method == ISOM_SCALE_METHOD_FILL )
        fprintf( fp, "'fill'\n" );
    else if( stsl->scale_method == ISOM_SCALE_METHOD_HIDDEN )
        fprintf( fp, "'hidden'\n" );
    else if( stsl->scale_method == ISOM_SCALE_METHOD_MEET )
        fprintf( fp, "'meet'\n" );
    else if( stsl->scale_method == ISOM_SCALE_METHOD_SLICE_X )
        fprintf( fp, "'slice' in the x-coodinate\n" );
    else if( stsl->scale_method == ISOM_SCALE_METHOD_SLICE_Y )
        fprintf( fp, "'slice' in the y-coodinate\n" );
    lsmash_ifprintf( fp, indent, "display_center_x = %"PRIu16"\n", stsl->display_center_x );
    lsmash_ifprintf( fp, indent, "display_center_y = %"PRIu16"\n", stsl->display_center_y );
    return 0;
}

static int isom_print_audio_description( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_audio_entry_t *audio = (isom_audio_entry_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: Audio Description]\n", isom_4cc2str( audio->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", audio->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", audio->size );
    isom_ifprintf_sample_description_common_reserved( fp, indent, audio->reserved );
    lsmash_ifprintf( fp, indent, "data_reference_index = %"PRIu16"\n", audio->data_reference_index );
    if( file->qt_compatible )
    {
        lsmash_ifprintf( fp, indent, "version = %"PRId16"\n", audio->version );
        lsmash_ifprintf( fp, indent, "revision_level = %"PRId16"\n", audio->revision_level );
        lsmash_ifprintf( fp, indent, "vendor = %s\n", isom_4cc2str( audio->vendor ) );
        lsmash_ifprintf( fp, indent, "channelcount = %"PRIu16"\n", audio->channelcount );
        lsmash_ifprintf( fp, indent, "samplesize = %"PRIu16"\n", audio->samplesize );
        lsmash_ifprintf( fp, indent, "compression_ID = %"PRId16"\n", audio->compression_ID );
        lsmash_ifprintf( fp, indent, "packet_size = %"PRIu16"\n", audio->packet_size );
    }
    else
    {
        lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", audio->version );
        lsmash_ifprintf( fp, indent, "reserved = 0x%04"PRIx16"\n", audio->revision_level );
        lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", audio->vendor );
        lsmash_ifprintf( fp, indent, "channelcount = %"PRIu16"\n", audio->channelcount );
        lsmash_ifprintf( fp, indent, "samplesize = %"PRIu16"\n", audio->samplesize );
        lsmash_ifprintf( fp, indent, "pre_defined = %"PRId16"\n", audio->compression_ID );
        lsmash_ifprintf( fp, indent, "reserved = %"PRIu16"\n", audio->packet_size );
    }
    lsmash_ifprintf( fp, indent, "samplerate = %f\n", lsmash_fixed2double( audio->samplerate, 16 ) );
    if( audio->version == 1 && (audio->manager & LSMASH_QTFF_BASE) )
    {
        lsmash_ifprintf( fp, indent, "samplesPerPacket = %"PRIu32"\n", audio->samplesPerPacket );
        lsmash_ifprintf( fp, indent, "bytesPerPacket = %"PRIu32"\n", audio->bytesPerPacket );
        lsmash_ifprintf( fp, indent, "bytesPerFrame = %"PRIu32"\n", audio->bytesPerFrame );
        lsmash_ifprintf( fp, indent, "bytesPerSample = %"PRIu32"\n", audio->bytesPerSample );
    }
    else if( audio->version == 2 )
    {
        lsmash_ifprintf( fp, indent, "sizeOfStructOnly = %"PRIu32"\n", audio->sizeOfStructOnly );
        lsmash_ifprintf( fp, indent, "audioSampleRate = %lf\n", lsmash_int2float64( audio->audioSampleRate ) );
        lsmash_ifprintf( fp, indent, "numAudioChannels = %"PRIu32"\n", audio->numAudioChannels );
        lsmash_ifprintf( fp, indent, "always7F000000 = 0x%08"PRIx32"\n", audio->always7F000000 );
        lsmash_ifprintf( fp, indent, "constBitsPerChannel = %"PRIu32"\n", audio->constBitsPerChannel );
        lsmash_ifprintf( fp, indent++, "formatSpecificFlags = 0x%08"PRIx32"\n", audio->formatSpecificFlags );
        if( isom_is_lpcm_audio( audio ) )
        {
            lsmash_ifprintf( fp, indent, "sample format: " );
            if( audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_FLOAT )
                fprintf( fp, "floating point\n" );
            else
            {
                fprintf( fp, "integer\n" );
                lsmash_ifprintf( fp, indent, "signedness: " );
                fprintf( fp, audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_SIGNED_INTEGER ? "signed\n" : "unsigned\n" );
            }
            if( audio->constBytesPerAudioPacket != 1 )
            {
                lsmash_ifprintf( fp, indent, "endianness: " );
                fprintf( fp, audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_BIG_ENDIAN ? "big\n" : "little\n" );
            }
            lsmash_ifprintf( fp, indent, "packed: " );
            if( audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_PACKED )
                fprintf( fp, "yes\n" );
            else
            {
                fprintf( fp, "no\n" );
                lsmash_ifprintf( fp, indent, "alignment: " );
                fprintf( fp, audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_ALIGNED_HIGH ? "high\n" : "low\n" );
            }
            if( audio->numAudioChannels > 1 )
            {
                lsmash_ifprintf( fp, indent, "interleved: " );
                fprintf( fp, audio->formatSpecificFlags & QT_LPCM_FORMAT_FLAG_NON_INTERLEAVED ? "no\n" : "yes\n" );
            }
        }
        lsmash_ifprintf( fp, --indent, "constBytesPerAudioPacket = %"PRIu32"\n", audio->constBytesPerAudioPacket );
        lsmash_ifprintf( fp, indent, "constLPCMFramesPerAudioPacket = %"PRIu32"\n", audio->constLPCMFramesPerAudioPacket );
    }
    return 0;
}

static int isom_print_wave( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Sound Information Decompression Parameters Box" );
}

static int isom_print_frma( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_frma_t *frma = (isom_frma_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Format Box" );
    lsmash_ifprintf( fp, indent, "data_format = %s\n", isom_4cc2str( frma->data_format ) );
    return 0;
}

static int isom_print_enda( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_enda_t *enda = (isom_enda_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Audio Endian Box" );
    lsmash_ifprintf( fp, indent, "littleEndian = %s\n", enda->littleEndian ? "yes" : "no" );
    return 0;
}

static int isom_print_terminator( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_terminator_t *terminator = (isom_terminator_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[0x00000000: Terminator Box]\n" );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", terminator->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", terminator->size );
    return 0;
}

static int isom_print_chan( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_chan_t *chan = (isom_chan_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Audio Channel Layout Box" );
    lsmash_ifprintf( fp, indent, "channelLayoutTag = 0x%08"PRIx32"\n", chan->channelLayoutTag );
    lsmash_ifprintf( fp, indent, "channelBitmap = 0x%08"PRIx32"\n", chan->channelBitmap );
    lsmash_ifprintf( fp, indent, "numberChannelDescriptions = %"PRIu32"\n", chan->numberChannelDescriptions );
    if( chan->numberChannelDescriptions )
    {
        isom_channel_description_t *desc = chan->channelDescriptions;
        for( uint32_t i = 0; i < chan->numberChannelDescriptions; i++ )
        {
            lsmash_ifprintf( fp, indent++, "ChannelDescriptions[%"PRIu32"]\n", i );
            lsmash_ifprintf( fp, indent, "channelLabel = 0x%08"PRIx32"\n", desc->channelLabel );
            lsmash_ifprintf( fp, indent, "channelFlags = 0x%08"PRIx32"\n", desc->channelFlags );
            for( int j = 0; j < 3; j++ )
                lsmash_ifprintf( fp, indent, "coordinates[%d] = %f\n", j, lsmash_int2float32( desc->coordinates[j] ) );
            --indent;
        }
    }
    return 0;
}

static int isom_print_srat( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_srat_t *srat = (isom_srat_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Sampling Rate Box" );
    lsmash_ifprintf( fp, indent, "sampling_rate = %"PRIu32"\n", srat->sampling_rate );
    return 0;
}

static int isom_print_text_description( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_qt_text_entry_t *text = (isom_qt_text_entry_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[text: QuickTime Text Description]\n" );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", text->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", text->size );
    isom_ifprintf_sample_description_common_reserved( fp, indent, text->reserved );
    lsmash_ifprintf( fp, indent, "data_reference_index = %"PRIu16"\n", text->data_reference_index );
    lsmash_ifprintf( fp, indent, "displayFlags = 0x%08"PRId32"\n", text->displayFlags );
    lsmash_ifprintf( fp, indent, "textJustification = %"PRId32"\n", text->textJustification );
    lsmash_ifprintf( fp, indent, "bgColor\n" );
    isom_ifprintf_rgb_color( fp, indent + 1, text->bgColor );
    lsmash_ifprintf( fp, indent, "top = %"PRId16"\n", text->top );
    lsmash_ifprintf( fp, indent, "left = %"PRId16"\n", text->left );
    lsmash_ifprintf( fp, indent, "bottom = %"PRId16"\n", text->bottom );
    lsmash_ifprintf( fp, indent, "right = %"PRId16"\n", text->right );
    lsmash_ifprintf( fp, indent, "scrpStartChar = %"PRId32"\n", text->scrpStartChar );
    lsmash_ifprintf( fp, indent, "scrpHeight = %"PRId16"\n", text->scrpHeight );
    lsmash_ifprintf( fp, indent, "scrpAscent = %"PRId16"\n", text->scrpAscent );
    lsmash_ifprintf( fp, indent, "scrpFont = %"PRId16"\n", text->scrpFont );
    lsmash_ifprintf( fp, indent, "scrpFace = %"PRIu16"\n", text->scrpFace );
    lsmash_ifprintf( fp, indent, "scrpSize = %"PRId16"\n", text->scrpSize );
    lsmash_ifprintf( fp, indent, "scrpColor\n" );
    isom_ifprintf_rgb_color( fp, indent + 1, text->scrpColor );
    if( text->font_name_length )
        lsmash_ifprintf( fp, indent, "font_name = %s\n", text->font_name );
    return 0;
}

static int isom_print_tx3g_description( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tx3g_entry_t *tx3g = (isom_tx3g_entry_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[tx3g: Timed Text Description]\n" );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", tx3g->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", tx3g->size );
    isom_ifprintf_sample_description_common_reserved( fp, indent, tx3g->reserved );
    lsmash_ifprintf( fp, indent, "data_reference_index = %"PRIu16"\n", tx3g->data_reference_index );
    lsmash_ifprintf( fp, indent, "displayFlags = 0x%08"PRId32"\n", tx3g->displayFlags );
    lsmash_ifprintf( fp, indent, "horizontal_justification = %"PRId8"\n", tx3g->horizontal_justification );
    lsmash_ifprintf( fp, indent, "vertical_justification = %"PRId8"\n", tx3g->vertical_justification );
    lsmash_ifprintf( fp, indent, "background_color_rgba\n" );
    isom_ifprintf_rgba_color( fp, indent + 1, tx3g->background_color_rgba );
    lsmash_ifprintf( fp, indent, "top = %"PRId16"\n", tx3g->top );
    lsmash_ifprintf( fp, indent, "left = %"PRId16"\n", tx3g->left );
    lsmash_ifprintf( fp, indent, "bottom = %"PRId16"\n", tx3g->bottom );
    lsmash_ifprintf( fp, indent, "right = %"PRId16"\n", tx3g->right );
    lsmash_ifprintf( fp, indent, "startChar = %"PRIu16"\n", tx3g->startChar );
    lsmash_ifprintf( fp, indent, "endChar = %"PRIu16"\n", tx3g->endChar );
    lsmash_ifprintf( fp, indent, "font_ID = %"PRIu16"\n", tx3g->font_ID );
    lsmash_ifprintf( fp, indent, "face_style_flags = %"PRIu8"\n", tx3g->face_style_flags );
    lsmash_ifprintf( fp, indent, "font_size = %"PRIu8"\n", tx3g->font_size );
    lsmash_ifprintf( fp, indent, "text_color_rgba\n" );
    isom_ifprintf_rgba_color( fp, indent + 1, tx3g->text_color_rgba );
    return 0;
}

static int isom_print_ftab( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_ftab_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_ftab_t *ftab = (isom_ftab_t *)box;
    int indent = level;
    uint16_t i = 0;
    isom_print_box_common( fp, indent++, box, "Font Table Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu16"\n", ftab->list->entry_count );
    for( lsmash_entry_t *entry = ftab->list->head; entry; entry = entry->next )
    {
        isom_font_record_t *data = (isom_font_record_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu16"]\n", i++ );
        lsmash_ifprintf( fp, indent, "font_ID = %"PRIu16"\n", data->font_ID );
        if( data->font_name_length )
            lsmash_ifprintf( fp, indent, "font_name = %s\n", data->font_name );
        --indent;
    }
    return 0;
}

static int isom_print_mp4s_description( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mp4s_entry_t *mp4s = (isom_mp4s_entry_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: MPEG-4 Systems Description]\n", isom_4cc2str( mp4s->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", mp4s->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", mp4s->size );
    isom_ifprintf_sample_description_common_reserved( fp, indent, mp4s->reserved );
    lsmash_ifprintf( fp, indent, "data_reference_index = %"PRIu16"\n", mp4s->data_reference_index );
    return 0;
}

static int isom_print_sample_description_extesion( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    extern int mp4sys_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int h264_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int hevc_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int h264_print_bitrate( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int vc1_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int ac3_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int eac3_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int dts_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int alac_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    extern int wma_print_codec_specific( FILE *, lsmash_file_t *, isom_box_t *, int );
    static struct print_description_extension_table_tag
    {
        lsmash_box_type_t type;
        int (*print_func)( FILE *, lsmash_file_t *, isom_box_t *, int );
    } print_description_extension_table[32] = { { LSMASH_BOX_TYPE_INITIALIZER, NULL } };
    if( !print_description_extension_table[0].print_func )
    {
        /* Initialize the table. */
        int i = 0;
#define ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( type, func ) \
    print_description_extension_table[i++] = (struct print_description_extension_table_tag){ type, func }
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_CLAP, isom_print_clap );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_PASP, isom_print_pasp );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_STSL, isom_print_stsl );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_COLR, isom_print_colr );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_COLR, isom_print_colr );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_GAMA, isom_print_gama );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_FIEL, isom_print_fiel );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_CLLI, isom_print_clli );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_MDCV, isom_print_mdcv );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_CSPC, isom_print_cspc );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_SGBT, isom_print_sgbt );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_CTAB, isom_print_ctab );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_GLBL, isom_print_glbl );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_WAVE, isom_print_wave );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_CHAN, isom_print_chan );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_ESDS, mp4sys_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_AVCC, h264_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_BTRT, h264_print_bitrate );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_HVCC, hevc_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_DVC1, vc1_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_DAC3, ac3_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_DEC3, eac3_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_DDTS, dts_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_ALAC, alac_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_WFEX, wma_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( ISOM_BOX_TYPE_FTAB, isom_print_ftab );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_ESDS, mp4sys_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT(   QT_BOX_TYPE_ALAC, alac_print_codec_specific );
        ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT( LSMASH_BOX_TYPE_UNSPECIFIED, NULL );
#undef ADD_PRINT_DESCRIPTION_EXTENSION_TABLE_ELEMENT
    }
    for( int i = 0; print_description_extension_table[i].print_func; i++ )
        if( lsmash_check_box_type_identical( box->type, print_description_extension_table[i].type ) )
            return print_description_extension_table[i].print_func( fp, file, box, level );
    return isom_print_unknown( fp, file, box, level );
}

static int isom_print_stts( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_stts_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_stts_t *stts = (isom_stts_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Decoding Time to Sample Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stts->list->entry_count );
    for( lsmash_entry_t *entry = stts->list->head; entry; entry = entry->next )
    {
        isom_stts_entry_t *data = (isom_stts_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", data->sample_count );
        lsmash_ifprintf( fp, indent--, "sample_delta = %"PRIu32"\n", data->sample_delta );
    }
    return 0;
}

static int isom_print_ctts( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_ctts_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_ctts_t *ctts = (isom_ctts_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Composition Time to Sample Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", ctts->list->entry_count );
    if( file->qt_compatible || ctts->version == 1 )
        for( lsmash_entry_t *entry = ctts->list->head; entry; entry = entry->next )
        {
            isom_ctts_entry_t *data = (isom_ctts_entry_t *)entry->data;
            lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
            lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", data->sample_count );
            if( data->sample_offset != ISOM_NON_OUTPUT_SAMPLE_OFFSET )
                lsmash_ifprintf( fp, indent--, "sample_offset = %"PRId32"\n", (union {uint32_t ui; int32_t si;}){ data->sample_offset }.si );
            else
                lsmash_ifprintf( fp, indent--, "sample_offset = -2^31 (non-output sample)\n" );
        }
    else
        for( lsmash_entry_t *entry = ctts->list->head; entry; entry = entry->next )
        {
            isom_ctts_entry_t *data = (isom_ctts_entry_t *)entry->data;
            lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
            lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", data->sample_count );
            lsmash_ifprintf( fp, indent--, "sample_offset = %"PRIu32"\n", data->sample_offset );
        }
    return 0;
}

static int isom_print_cslg( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_cslg_t *cslg = (isom_cslg_t *)box;
    int indent = level;
    if( file->qt_compatible )
    {
        isom_print_box_common( fp, indent++, box, "Composition Shift Least Greatest Box" );
        lsmash_ifprintf( fp, indent, "compositionOffsetToDTDDeltaShift = %"PRId32"\n", cslg->compositionToDTSShift );
        lsmash_ifprintf( fp, indent, "leastDecodeToDisplayDelta = %"PRId32"\n", cslg->leastDecodeToDisplayDelta );
        lsmash_ifprintf( fp, indent, "greatestDecodeToDisplayDelta = %"PRId32"\n", cslg->greatestDecodeToDisplayDelta );
        lsmash_ifprintf( fp, indent, "displayStartTime = %"PRId32"\n", cslg->compositionStartTime );
        lsmash_ifprintf( fp, indent, "displayEndTime = %"PRId32"\n", cslg->compositionEndTime );
    }
    else
    {
        isom_print_box_common( fp, indent++, box, "Composition to Decode Box" );
        lsmash_ifprintf( fp, indent, "compositionToDTSShift = %"PRId32"\n", cslg->compositionToDTSShift );
        lsmash_ifprintf( fp, indent, "leastDecodeToDisplayDelta = %"PRId32"\n", cslg->leastDecodeToDisplayDelta );
        lsmash_ifprintf( fp, indent, "greatestDecodeToDisplayDelta = %"PRId32"\n", cslg->greatestDecodeToDisplayDelta );
        lsmash_ifprintf( fp, indent, "compositionStartTime = %"PRId32"\n", cslg->compositionStartTime );
        lsmash_ifprintf( fp, indent, "compositionEndTime = %"PRId32"\n", cslg->compositionEndTime );
    }
    return 0;
}

static int isom_print_stss( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_stss_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_stss_t *stss = (isom_stss_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Sync Sample Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stss->list->entry_count );
    for( lsmash_entry_t *entry = stss->list->head; entry; entry = entry->next )
        lsmash_ifprintf( fp, indent, "sample_number[%"PRIu32"] = %"PRIu32"\n", i++, ((isom_stss_entry_t *)entry->data)->sample_number );
    return 0;
}

static int isom_print_stps( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_stps_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_stps_t *stps = (isom_stps_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Partial Sync Sample Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stps->list->entry_count );
    for( lsmash_entry_t *entry = stps->list->head; entry; entry = entry->next )
        lsmash_ifprintf( fp, indent, "sample_number[%"PRIu32"] = %"PRIu32"\n", i++, ((isom_stps_entry_t *)entry->data)->sample_number );
    return 0;
}

static int isom_print_sdtp( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_sdtp_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_sdtp_t *sdtp = (isom_sdtp_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Independent and Disposable Samples Box" );
    for( lsmash_entry_t *entry = sdtp->list->head; entry; entry = entry->next )
    {
        isom_sdtp_entry_t *data = (isom_sdtp_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        if( data->is_leading || data->sample_depends_on || data->sample_is_depended_on || data->sample_has_redundancy )
        {
            if( file->avc_extensions )
            {
                if( data->is_leading == ISOM_SAMPLE_IS_UNDECODABLE_LEADING )
                    lsmash_ifprintf( fp, indent, "undecodable leading\n" );
                else if( data->is_leading == ISOM_SAMPLE_IS_NOT_LEADING )
                    lsmash_ifprintf( fp, indent, "non-leading\n" );
                else if( data->is_leading == ISOM_SAMPLE_IS_DECODABLE_LEADING )
                    lsmash_ifprintf( fp, indent, "decodable leading\n" );
            }
            else if( data->is_leading == QT_SAMPLE_EARLIER_PTS_ALLOWED )
                lsmash_ifprintf( fp, indent, "early display times allowed\n" );
            if( data->sample_depends_on == ISOM_SAMPLE_IS_INDEPENDENT )
                lsmash_ifprintf( fp, indent, "independent\n" );
            else if( data->sample_depends_on == ISOM_SAMPLE_IS_NOT_INDEPENDENT )
                lsmash_ifprintf( fp, indent, "dependent\n" );
            if( data->sample_is_depended_on == ISOM_SAMPLE_IS_NOT_DISPOSABLE )
                lsmash_ifprintf( fp, indent, "non-disposable\n" );
            else if( data->sample_is_depended_on == ISOM_SAMPLE_IS_DISPOSABLE )
                lsmash_ifprintf( fp, indent, "disposable\n" );
            if( data->sample_has_redundancy == ISOM_SAMPLE_HAS_REDUNDANCY )
                lsmash_ifprintf( fp, indent, "redundant\n" );
            else if( data->sample_has_redundancy == ISOM_SAMPLE_HAS_NO_REDUNDANCY )
                lsmash_ifprintf( fp, indent, "non-redundant\n" );
        }
        else
            lsmash_ifprintf( fp, indent, "no description\n" );
        --indent;
    }
    return 0;
}

static int isom_print_stsc( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_stsc_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_stsc_t *stsc = (isom_stsc_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Sample To Chunk Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stsc->list->entry_count );
    for( lsmash_entry_t *entry = stsc->list->head; entry; entry = entry->next )
    {
        isom_stsc_entry_t *data = (isom_stsc_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "first_chunk = %"PRIu32"\n", data->first_chunk );
        lsmash_ifprintf( fp, indent, "samples_per_chunk = %"PRIu32"\n", data->samples_per_chunk );
        lsmash_ifprintf( fp, indent--, "sample_description_index = %"PRIu32"\n", data->sample_description_index );
    }
    return 0;
}

static int isom_print_stsz( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_stsz_t *stsz = (isom_stsz_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Sample Size Box" );
    if( !stsz->sample_size )
        lsmash_ifprintf( fp, indent, "sample_size = 0 (variable)\n" );
    else
        lsmash_ifprintf( fp, indent, "sample_size = %"PRIu32" (constant)\n", stsz->sample_size );
    lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", stsz->sample_count );
    if( !stsz->sample_size && stsz->list )
        for( lsmash_entry_t *entry = stsz->list->head; entry; entry = entry->next )
        {
            isom_stsz_entry_t *data = (isom_stsz_entry_t *)entry->data;
            lsmash_ifprintf( fp, indent, "entry_size[%"PRIu32"] = %"PRIu32"\n", i++, data->entry_size );
        }
    return 0;
}

static int isom_print_stz2( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_stz2_t *stz2 = (isom_stz2_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Compact Sample Size Box" );
    lsmash_ifprintf( fp, indent, "reserved = 0x%06"PRIx32"\n", stz2->reserved );
    lsmash_ifprintf( fp, indent, "field_size = %"PRIu8"\n", stz2->field_size );
    lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", stz2->sample_count );
    for( lsmash_entry_t *entry = stz2->list->head; entry; entry = entry->next )
    {
        isom_stsz_entry_t *data = (isom_stsz_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent, "entry_size[%"PRIu32"] = %"PRIu32"\n", i++, data->entry_size );
    }
    return 0;
}

static int isom_print_stco( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_stco_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_stco_t *stco = (isom_stco_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Chunk Offset Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", stco->list->entry_count );
    if( lsmash_check_box_type_identical( stco->type, ISOM_BOX_TYPE_STCO ) )
    {
        for( lsmash_entry_t *entry = stco->list->head; entry; entry = entry->next )
            lsmash_ifprintf( fp, indent, "chunk_offset[%"PRIu32"] = %"PRIu32"\n", i++, ((isom_stco_entry_t *)entry->data)->chunk_offset );
    }
    else
    {
        for( lsmash_entry_t *entry = stco->list->head; entry; entry = entry->next )
            lsmash_ifprintf( fp, indent, "chunk_offset[%"PRIu32"] = %"PRIu64"\n", i++, ((isom_co64_entry_t *)entry->data)->chunk_offset );
    }
    return 0;
}

static int isom_print_sgpd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_sgpd_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_sgpd_t *sgpd = (isom_sgpd_t *)box;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Sample Group Description Box" );
    lsmash_ifprintf( fp, indent, "grouping_type = %s\n", isom_4cc2str( sgpd->grouping_type ) );
    if( sgpd->version == 1 )
    {
        lsmash_ifprintf( fp, indent, "default_length = %"PRIu32, sgpd->default_length );
        fprintf( fp, " %s\n", sgpd->default_length ? "(constant)" : "(variable)" );
    }
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", sgpd->list->entry_count );
    switch( sgpd->grouping_type )
    {
        case ISOM_GROUP_TYPE_RAP :
            for( lsmash_entry_t *entry = sgpd->list->head; entry; entry = entry->next )
            {
                if( sgpd->version == 1 && !sgpd->default_length )
                    lsmash_ifprintf( fp, indent, "description_length[%"PRIu32"] = %"PRIu32"\n", i++, ((isom_rap_entry_t *)entry->data)->description_length );
                else
                {
                    isom_rap_entry_t *rap = (isom_rap_entry_t *)entry->data;
                    lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
                    lsmash_ifprintf( fp, indent, "num_leading_samples_known = %"PRIu8"\n", rap->num_leading_samples_known );
                    lsmash_ifprintf( fp, indent--, "num_leading_samples = %"PRIu8"\n", rap->num_leading_samples );
                }
            }
            break;
        case ISOM_GROUP_TYPE_ROLL :
        case ISOM_GROUP_TYPE_PROL :
            for( lsmash_entry_t *entry = sgpd->list->head; entry; entry = entry->next )
            {
                if( sgpd->version == 1 && !sgpd->default_length )
                    lsmash_ifprintf( fp, indent, "description_length[%"PRIu32"] = %"PRIu32"\n", i++, ((isom_roll_entry_t *)entry->data)->description_length );
                else
                    lsmash_ifprintf( fp, indent, "roll_distance[%"PRIu32"] = %"PRId16"\n", i++, ((isom_roll_entry_t *)entry->data)->roll_distance );
            }
            break;
        default :
            break;
    }
    return 0;
}

static int isom_print_sbgp( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_sbgp_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_sbgp_t *sbgp = (isom_sbgp_t *)box;
    int indent = level;
    int is_fragment = lsmash_check_box_type_identical( sbgp->parent->type, ISOM_BOX_TYPE_TRAF );
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Sample to Group Box" );
    lsmash_ifprintf( fp, indent, "grouping_type = %s\n", isom_4cc2str( sbgp->grouping_type ) );
    if( sbgp->version == 1 )
        lsmash_ifprintf( fp, indent, "grouping_type_parameter = %s\n", isom_4cc2str( sbgp->grouping_type_parameter ) );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", sbgp->list->entry_count );
    for( lsmash_entry_t *entry = sbgp->list->head; entry; entry = entry->next )
    {
        isom_group_assignment_entry_t *data = (isom_group_assignment_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "sample_count = %"PRIu32"\n", data->sample_count );
        lsmash_ifprintf( fp, indent--, "group_description_index = %"PRIu32, data->group_description_index );
        if( is_fragment && data->group_description_index >= 0x10000 )
            fprintf( fp, " (i.e. %"PRIu32" for this fragment-local group)", data->group_description_index - 0x10000 );
        if( !data->group_description_index )
            fprintf( fp, " (not in this grouping type)\n" );
        else
            fprintf( fp, "\n" );
    }
    return 0;
}

static int isom_print_udta( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "User Data Box" );
}

static int isom_print_chpl( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_chpl_t *chpl = (isom_chpl_t *)box;
    uint32_t timescale;
    if( !chpl->version )
    {
        if( !file->moov || !file->moov->mvhd )
            return LSMASH_ERR_INVALID_DATA;
        timescale = file->moov->mvhd->timescale;
    }
    else
        timescale = 10000000;
    int indent = level;
    uint32_t i = 0;
    isom_print_box_common( fp, indent++, box, "Chapter List Box" );
    if( chpl->version == 1 )
    {
        lsmash_ifprintf( fp, indent, "unknown = 0x%02"PRIx8"\n", chpl->unknown );
        lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", chpl->list->entry_count );
    }
    else
        lsmash_ifprintf( fp, indent, "entry_count = %"PRIu8"\n", (uint8_t)chpl->list->entry_count );
    for( lsmash_entry_t *entry = chpl->list->head; entry; entry = entry->next )
    {
        isom_chpl_entry_t *data = (isom_chpl_entry_t *)entry->data;
        int64_t start_time = data->start_time / timescale;
        int hh =  start_time / 3600;
        int mm = (start_time /   60) % 60;
        int ss =  start_time         % 60;
        int ms = ((data->start_time / (double)timescale) - hh * 3600 - mm * 60 - ss) * 1e3 + 0.5;
        int with_bom = 0;
        if( !memcmp( data->chapter_name, "\xEF\xBB\xBF", 3 ) )    /* detect BOM */
        {
            data->chapter_name += 3;
            with_bom = 1;
        }
        lsmash_ifprintf( fp, indent++, "chapter[%"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "start_time = %02d:%02d:%02d.%03d\n", hh, mm, ss, ms );
        lsmash_ifprintf( fp, indent--, with_bom ? "chapter_name = %s ( it has BOM in it )\n" : "chapter_name = %s\n", data->chapter_name );
    }
    return 0;
}

static int isom_print_meta( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    int indent = level;
    if( !(box->manager & LSMASH_QTFF_BASE) )
    {
        isom_print_basebox_common( fp, indent++, box, "Meta Box" );
        lsmash_ifprintf( fp, indent, "version = %"PRIu8"\n", box->version );
        lsmash_ifprintf( fp, indent, "flags = 0x%06"PRIx32"\n", box->flags & 0x00ffffff );
    }
    else
        isom_print_basebox_common( fp, indent, box, "Metadata Box" );
    return 0;
}

static int isom_print_keys( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    if( !((isom_keys_t *)box)->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_keys_t *keys = (isom_keys_t *)box;
    int indent = level;
    uint32_t i = 1;
    isom_print_box_common( fp, indent++, box, "Metadata Item Keys Box" );
    lsmash_ifprintf( fp, indent, "entry_count = %"PRIu32"\n", keys->list->entry_count );
    for( lsmash_entry_t *entry = keys->list->head; entry; entry = entry->next )
    {
        isom_keys_entry_t *data = (isom_keys_entry_t *)entry->data;
        lsmash_ifprintf( fp, indent++, "[key %"PRIu32"]\n", i++ );
        lsmash_ifprintf( fp, indent, "key_size = %"PRIu32"\n", data->key_size );
        lsmash_ifprintf( fp, indent, "key_namespace = %s\n", isom_4cc2str( data->key_namespace ) );
        uint32_t value_length = data->key_size - 8;
        char *str = lsmash_malloc( value_length + 1 );
        if( !str )
            return LSMASH_ERR_MEMORY_ALLOC;
        memcpy( str, data->key_value, value_length );
        str[value_length] = 0;
        lsmash_ifprintf( fp, indent--, "key_value = %s\n", str );
        lsmash_free( str );
    }
    return 0;
}

static int isom_print_ilst( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Metadata Item List Box" );
}

static int isom_print_metaitem( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_metaitem_t *metaitem = (isom_metaitem_t *)box;
    if( box->parent->parent->manager & LSMASH_QTFF_BASE )
    {
        int indent = level;
        lsmash_ifprintf( fp, indent++, "[key_index %"PRIu32": Metadata Item Box]\n", box->type.fourcc );
        lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", box->pos );
        lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", box->size );
        return 0;
    }
    static const struct
    {
        lsmash_itunes_metadata_item item;
        char                       *name;
    } metaitem_table[] =
        {
            { ITUNES_METADATA_ITEM_ALBUM_NAME,                 "Album Name" },
            { ITUNES_METADATA_ITEM_ARTIST,                     "Artist" },
            { ITUNES_METADATA_ITEM_USER_COMMENT,               "User Comment" },
            { ITUNES_METADATA_ITEM_RELEASE_DATE,               "Release Date" },
            { ITUNES_METADATA_ITEM_ENCODED_BY,                 "Encoded By" },
            { ITUNES_METADATA_ITEM_USER_GENRE,                 "User Genre" },
            { ITUNES_METADATA_ITEM_GROUPING,                   "Grouping" },
            { ITUNES_METADATA_ITEM_LYRICS,                     "Lyrics" },
            { ITUNES_METADATA_ITEM_TITLE,                      "Title" },
            { ITUNES_METADATA_ITEM_ENCODING_TOOL,              "Encoding Tool" },
            { ITUNES_METADATA_ITEM_COMPOSER,                   "Composer" },
            { ITUNES_METADATA_ITEM_ALBUM_ARTIST,               "Album Artist" },
            { ITUNES_METADATA_ITEM_PODCAST_CATEGORY,           "Podcast Category" },
            { ITUNES_METADATA_ITEM_COVER_ART,                  "Cover Art" },
            { ITUNES_METADATA_ITEM_DISC_COMPILATION,           "Disc Compilation" },
            { ITUNES_METADATA_ITEM_COPYRIGHT,                  "Copyright" },
            { ITUNES_METADATA_ITEM_DESCRIPTION,                "Description" },
            { ITUNES_METADATA_ITEM_DISC_NUMBER,                "Disc Number" },
            { ITUNES_METADATA_ITEM_EPISODE_GLOBAL_ID,          "Episode Global Unique ID" },
            { ITUNES_METADATA_ITEM_PREDEFINED_GENRE,           "Pre-defined Genre" },
            { ITUNES_METADATA_ITEM_GROUPING_DRAFT,             "Grouping (Overall work like TIT1 in ID3)" },
            { ITUNES_METADATA_ITEM_HIGH_DEFINITION_VIDEO,      "High Definition Video" },
            { ITUNES_METADATA_ITEM_PODCAST_KEYWORD,            "Podcast Keyword" },
            { ITUNES_METADATA_ITEM_LONG_DESCRIPTION,           "Long Description" },
            { ITUNES_METADATA_ITEM_PODCAST,                    "Podcast" },
            { ITUNES_METADATA_ITEM_GAPLESS_PLAYBACK,           "Gapless Playback" },
            { ITUNES_METADATA_ITEM_PURCHASE_DATE,              "Purchase Date" },
            { ITUNES_METADATA_ITEM_PODCAST_URL,                "Podcast URL" },
            { ITUNES_METADATA_ITEM_CONTENT_RATING,             "Content Rating" },
            { ITUNES_METADATA_ITEM_MEDIA_TYPE,                 "Media Type" },
            { ITUNES_METADATA_ITEM_BEATS_PER_MINUTE,           "Beats Per Minute" },
            { ITUNES_METADATA_ITEM_TRACK_NUMBER,               "Track Number" },
            { ITUNES_METADATA_ITEM_TV_EPISODE_ID,              "TV Episode ID" },
            { ITUNES_METADATA_ITEM_TV_EPISODE,                 "TV Episode" },
            { ITUNES_METADATA_ITEM_TV_NETWORK,                 "TV Network" },
            { ITUNES_METADATA_ITEM_TV_SHOW_NAME,               "TV Show Name" },
            { ITUNES_METADATA_ITEM_TV_SEASON,                  "TV Season" },
            { ITUNES_METADATA_ITEM_ITUNES_PURCHASE_ACCOUNT_ID, "iTunes Account Used for Purchase" },
            { ITUNES_METADATA_ITEM_ITUNES_ACCOUNT_TYPE,        "iTunes Account Type" },
            { ITUNES_METADATA_ITEM_ITUNES_ARTIST_ID,           "iTunes Artist ID" },
            { ITUNES_METADATA_ITEM_ITUNES_COMPOSER_ID,         "iTunes Composer ID" },
            { ITUNES_METADATA_ITEM_ITUNES_CATALOG_ID,          "iTunes Catalog ID" },
            { ITUNES_METADATA_ITEM_ITUNES_TV_GENRE_ID,         "iTunes TV Genre ID" },
            { ITUNES_METADATA_ITEM_ITUNES_PLAYLIST_ID,         "iTunes Playlist ID" },
            { ITUNES_METADATA_ITEM_ITUNES_COUNTRY_CODE,        "iTunes Country Code" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM,          "Sort Album" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ARTIST,         "Sort Artist" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM_ARTIST,   "Sort Album Artist" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_COMPOSER,       "Sort Composer" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_NAME,           "Sort Name" },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_SHOW,           "Sort Show" },
            { ITUNES_METADATA_ITEM_CUSTOM,                     "Custom Metadata Item" },
            { 0,                                               NULL }
        };
    char *name = NULL;
    int i;
    for( i = 0; metaitem_table[i].name; i++ )
        if( metaitem->type.fourcc == metaitem_table[i].item )
        {
            name = metaitem_table[i].name;
            break;
        }
    if( !name )
        name = "Unknown";
    uint32_t name_length = strlen( name );
    uint32_t display_name_length = name_length + 20;
    char *display_name = lsmash_malloc( display_name_length + 1 );
    if( !display_name )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( display_name, "Metadata Item Box (", 19 );
    memcpy( display_name + 19, name, name_length );
    display_name[display_name_length - 1] = ')';
    display_name[display_name_length] = 0;
    int ret = isom_print_simple( fp, box, level, display_name );
    lsmash_free( display_name );
    return ret;
}

static int isom_print_name( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_name_t *name = (isom_name_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Name Box" );
    char *str = lsmash_malloc( name->name_length + 1 );
    if( !str )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( str, name->name, name->name_length );
    str[name->name_length] = 0;
    lsmash_ifprintf( fp, indent, "name = %s\n", str );
    lsmash_free( str );
    return 0;
}

static int isom_print_mean( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mean_t *mean = (isom_mean_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Mean Box" );
    char *str = lsmash_malloc( mean->meaning_string_length + 1 );
    if( !str )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( str, mean->meaning_string, mean->meaning_string_length );
    str[mean->meaning_string_length] = 0;
    lsmash_ifprintf( fp, indent, "meaning_string = %s\n", str );
    lsmash_free( str );
    return 0;
}

static int isom_print_data( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_data_t *data = (isom_data_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Data Box" );
    if( box->parent->parent->parent->manager & LSMASH_QTFF_BASE )
    {
        uint32_t type_set_indicator = data->reserved >> 8;
        uint32_t well_known_type = ((data->reserved << 16) | (data->type_set_identifier << 8) | data->type_code) & 0xffffff;
        char *well_known_type_name = "Unknown";
        static const struct
        {
            uint32_t type;
            char    *name;
        } well_known_type_table[] =
            {
                { 0,   "reserved" },
                { 1,   "UTF-8" },
                { 2,   "UTF-16 BE" },
                { 3,   "S/JIS" },
                { 4,   "UTF-8 sort" },
                { 5,   "UTF-16 sort" },
                { 13,  "JPEG in a JFIF wrapper" },
                { 14,  "PNG in a PNG wrapper" },
                { 21,  "BE Signed Integer" },
                { 22,  "BE Unsigned Integer" },
                { 23,  "BE Float32" },
                { 24,  "BE Float64" },
                { 27,  "BMP (Windows bitmap format graphics)" },
                { 28,  "QuickTime Metadata box" },
                { UINT32_MAX }
            };
        int table_index;
        for( table_index = 0; well_known_type_table[table_index].type != UINT32_MAX; table_index++ )
            if( well_known_type == well_known_type_table[table_index].type )
            {
                well_known_type_name = well_known_type_table[table_index].name;
                break;
            }
        lsmash_ifprintf( fp, indent, "type_set_indicator = %"PRIu8"\n", type_set_indicator );
        lsmash_ifprintf( fp, indent, "well_known_type = %"PRIu32" (%s)\n", well_known_type, well_known_type_name );
        lsmash_ifprintf( fp, indent, "locale_indicator = %"PRIu32"\n", data->the_locale );
        if( data->value_length == 0 )
        {
            lsmash_ifprintf( fp, indent, "value = (null)\n" );
            return 0;
        }
        if( well_known_type == 1 )
        {
            /* UTF-8 without any count or null terminator */
            char *str = lsmash_malloc( data->value_length + 1 );
            if( !str )
                return LSMASH_ERR_MEMORY_ALLOC;
            memcpy( str, data->value, data->value_length );
            str[data->value_length] = 0;
            lsmash_ifprintf( fp, indent, "value = %s\n", str );
            lsmash_free( str );
        }
        else if( well_known_type == 13 || well_known_type == 14 || well_known_type == 27 )
            lsmash_ifprintf( fp, indent, "value = (binary data)\n" );
        else if( well_known_type == 21 && data->value_length <= 4 )
            /* a big-endian signed integer in 1,2,3 or 4 bytes */
            goto show_in_signed_integer;
        else if( well_known_type == 22 && data->value_length <= 4 )
        {
            /* a big-endian unsigned integer in 1,2,3 or 4 bytes */
            uint32_t integer = data->value[0];
            for( uint32_t i = 1; i < data->value_length; i++ )
                integer = (integer << 8) | data->value[i];
            lsmash_ifprintf( fp, indent, "value = %"PRIu32"\n", integer );
        }
        else if( well_known_type == 23 && data->value_length == 4 )
        {
            /* a big-endian 32-bit floating point value (IEEE754) */
            uint32_t float32 = LSMASH_GET_BE32( data->value );
            lsmash_ifprintf( fp, indent, "value = %f\n", lsmash_int2float32( float32 ) );
        }
        else if( well_known_type == 24 && data->value_length == 8 )
        {
            /* a big-endian 64-bit floating point value (IEEE754) */
            uint64_t float64 = LSMASH_GET_BE64( data->value );
            lsmash_ifprintf( fp, indent, "value = %lf\n", lsmash_int2float64( float64 ) );
        }
        else
            goto show_in_binary;
    }
    else
    {
        char *basic_data_type_name = "Unknown";
        static const struct
        {
            uint32_t type;
            char    *name;
        } basic_data_type_table[] =
            {
                { 0,   "Implicit" },
                { 1,   "UTF-8" },
                { 2,   "UTF-16 BE" },
                { 3,   "S/JIS" },
                { 6,   "HTML" },
                { 7,   "XML" },
                { 8,   "UUID" },
                { 9,   "ISRC" },
                { 10,  "MI3P" },
                { 12,  "GIF" },
                { 13,  "JPEG in a JFIF wrapper" },
                { 14,  "PNG in a PNG wrapper" },
                { 15,  "URL" },
                { 16,  "duration" },
                { 17,  "date/time" },
                { 18,  "Genres" },
                { 21,  "BE Signed Integer" },
                { 24,  "RIAA-PA (RIAA Parental advisory)" },
                { 25,  "UPC (Universal Product Code)" },
                { 27,  "BMP (Windows bitmap format graphics)" },
                { UINT32_MAX }
            };
        int table_index;
        for( table_index = 0; basic_data_type_table[table_index].type != UINT32_MAX; table_index++ )
            if( data->type_code == basic_data_type_table[table_index].type )
            {
                basic_data_type_name = basic_data_type_table[table_index].name;
                break;
            }
        lsmash_ifprintf( fp, indent, "reserved = %"PRIu16"\n", data->reserved );
        lsmash_ifprintf( fp, indent, "type_set_identifier = %"PRIu8"%s\n",
                         data->type_set_identifier,
                         data->type_set_identifier ? "" : " (basic type set)" );
        lsmash_ifprintf( fp, indent, "type_code = %"PRIu8" (%s)\n", data->type_code, basic_data_type_name );
        lsmash_ifprintf( fp, indent, "the_locale = %"PRIu32"\n", data->the_locale );
        if( data->value_length == 0 )
        {
            lsmash_ifprintf( fp, indent, "value = (null)\n" );
            return 0;
        }
        if( data->type_code == 6  || data->type_code == 7
         || data->type_code == 12 || data->type_code == 13
         || data->type_code == 14 || data->type_code == 27 )
            lsmash_ifprintf( fp, indent, "value = (binary data)\n" );
        else if( data->type_code == 8 && data->value_length == 16 )
            /* UUID */
            lsmash_ifprintf( fp, indent, "value = 0x%08"PRIx32"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"-%04"PRIx16"0x%08"PRIx32"\n",
                             LSMASH_GET_BE32( &data->value[ 0] ),
                             LSMASH_GET_BE16( &data->value[ 4] ),
                             LSMASH_GET_BE16( &data->value[ 6] ),
                             LSMASH_GET_BE16( &data->value[ 8] ),
                             LSMASH_GET_BE16( &data->value[10] ),
                             LSMASH_GET_BE32( &data->value[12] ) );
        else if( data->type_code == 16 && data->value_length == 4 )
        {
            /* duration in milliseconds */
            uint32_t duration = LSMASH_GET_BE32( data->value );
            lsmash_ifprintf( fp, indent, "value = %"PRIu32" milliseconds\n", duration );
        }
        else if( data->type_code == 17 && (data->value_length == 4 || data->value_length == 8) )
        {
            /* UTC, counting seconds since midnight on 1 January, 1904 */
            uint64_t mp4time = data->value_length == 8
                             ? LSMASH_GET_BE64( data->value )
                             : LSMASH_GET_BE32( data->value );
            isom_mp4time2utc( mp4time );
        }
        else if( data->type_code == 21 && data->value_length <= 8 )
            /* a big-endian signed integer in 1,2,3,4 or 8 bytes */
            goto show_in_signed_integer;
        else if( data->type_code == 24 )
        {
            /* RIAA-PA (RIAA Parental advisory) 8-bit integer */
            lsmash_ifprintf( fp, indent, "value = %"PRIu8, data->value[0] );
            if( data->value[0] == (uint8_t)-1 )
                fprintf( fp, " (no)" );
            else if( data->value[0] == 1 )
                fprintf( fp, " (yes)" );
            else if( data->value[0] == 0 )
                fprintf( fp, " (unspecified)" );
            fprintf( fp, "\n" );
        }
        else if( data->type_code == 1  || data->type_code == 2  || data->type_code == 3
              || data->type_code == 9  || data->type_code == 10 || data->type_code == 15
              || data->type_code == 25 )
        {
            /* String */
            char *str = lsmash_malloc( data->value_length + 1 );
            if( !str )
                return LSMASH_ERR_MEMORY_ALLOC;
            memcpy( str, data->value, data->value_length );
            str[data->value_length] = 0;
            lsmash_ifprintf( fp, indent, "value = %s\n", str );
            lsmash_free( str );
        }
        else
            goto show_in_binary;
    }
    return 0;
show_in_signed_integer:;
    uint64_t integer   = data->value[0];
    uint64_t max_value = 0xff;
    for( uint32_t i = 1; i < data->value_length; i++ )
    {
        integer   = (integer   << 8) | data->value[i];
        max_value = (max_value << 8) | 0xff;
    }
    lsmash_ifprintf( fp, indent, "value = %"PRId64"\n", (int64_t)(integer | (integer > (max_value >> 1) ? ~max_value : 0)) );
    return 0;
show_in_binary:
    lsmash_ifprintf( fp, indent, "value = " );
    if( data->value_length )
    {
        fprintf( fp, "0x" );
        for( uint32_t i = 0; i < data->value_length; i++ )
            fprintf( fp, "%02"PRIx8, data->value[i] );
    }
    fprintf( fp, "\n" );
    return 0;
}

static int isom_print_WLOC( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_WLOC_t *WLOC = (isom_WLOC_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Window Location Box" );
    lsmash_ifprintf( fp, indent, "x = %"PRIu16"\n", WLOC->x );
    lsmash_ifprintf( fp, indent, "y = %"PRIu16"\n", WLOC->y );
    return 0;
}

static int isom_print_LOOP( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_LOOP_t *LOOP = (isom_LOOP_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Looping Box" );
    lsmash_ifprintf( fp, indent, "looping_mode = %"PRIu32, LOOP->looping_mode );
    switch( LOOP->looping_mode )
    {
        case 0 :
            fprintf( fp, " (none)\n" );
            break;
        case 1 :
            fprintf( fp, " (looping)\n" );
            break;
        case 2 :
            fprintf( fp, " (palindromic looping)\n" );
            break;
        default :
            fprintf( fp, "\n" );
            break;
    }
    return 0;
}

static int isom_print_SelO( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_SelO_t *SelO = (isom_SelO_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Play Selection Only Box" );
    lsmash_ifprintf( fp, indent, "selection_only = %"PRIu8"\n", SelO->selection_only );
    return 0;
}

static int isom_print_AllF( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_AllF_t *AllF = (isom_AllF_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Play All Frames Box" );
    lsmash_ifprintf( fp, indent, "play_all_frames = %"PRIu8"\n", AllF->play_all_frames );
    return 0;
}

static int isom_print_cprt( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_cprt_t *cprt = (isom_cprt_t *)box;
    int indent = level;
    char *str = lsmash_malloc( cprt->notice_length + 1 );
    if( !str )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( str, cprt->notice, cprt->notice_length );
    str[cprt->notice_length] = 0;
    isom_print_box_common( fp, indent++, box, "Copyright Box" );
    lsmash_ifprintf( fp, indent, "language = %s\n", isom_unpack_iso_language( cprt->language ) );
    lsmash_ifprintf( fp, indent, "notice = %s\n", str );
    lsmash_free( str );
    return 0;
}

static int isom_print_mvex( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Movie Extends Box" );
}

static int isom_print_mehd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mehd_t *mehd = (isom_mehd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Movie Extends Header Box" );
    if( file->moov && file->moov->mvhd )
        isom_ifprintf_duration( fp, indent, "fragment_duration", mehd->fragment_duration, file->moov->mvhd->timescale );
    else
        isom_ifprintf_duration( fp, indent, "fragment_duration", mehd->fragment_duration, 0 );
    return 0;
}

static int isom_print_trex( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_trex_t *trex = (isom_trex_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Extends Box" );
    lsmash_ifprintf( fp, indent, "track_ID = %"PRIu32"\n", trex->track_ID );
    lsmash_ifprintf( fp, indent, "default_sample_description_index = %"PRIu32"\n", trex->default_sample_description_index );
    lsmash_ifprintf( fp, indent, "default_sample_duration = %"PRIu32"\n", trex->default_sample_duration );
    lsmash_ifprintf( fp, indent, "default_sample_size = %"PRIu32"\n", trex->default_sample_size );
    isom_ifprintf_sample_flags( fp, indent, "default_sample_flags", &trex->default_sample_flags );
    return 0;
}

static int isom_print_moof( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Movie Fragment Box" );
}

static int isom_print_mfhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mfhd_t *mfhd = (isom_mfhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Movie Fragment Header Box" );
    lsmash_ifprintf( fp, indent, "sequence_number = %"PRIu32"\n", mfhd->sequence_number );
    return 0;
}

static int isom_print_traf( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Track Fragment Box" );
}

static int isom_print_tfhd( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tfhd_t *tfhd = (isom_tfhd_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Fragment Header Box" );
    ++indent;
    if( tfhd->flags & ISOM_TF_FLAGS_BASE_DATA_OFFSET_PRESENT         ) lsmash_ifprintf( fp, indent, "base-data-offset-present\n" );
    if( tfhd->flags & ISOM_TF_FLAGS_SAMPLE_DESCRIPTION_INDEX_PRESENT ) lsmash_ifprintf( fp, indent, "sample-description-index-present\n" );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT  ) lsmash_ifprintf( fp, indent, "default-sample-duration-present\n" );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_SIZE_PRESENT      ) lsmash_ifprintf( fp, indent, "default-sample-size-present\n" );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT     ) lsmash_ifprintf( fp, indent, "default-sample-flags-present\n" );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_BASE_IS_MOOF             ) lsmash_ifprintf( fp, indent, "default-base-is-moof\n" );
    lsmash_ifprintf( fp, --indent, "track_ID = %"PRIu32"\n", tfhd->track_ID );
    if( tfhd->flags & ISOM_TF_FLAGS_BASE_DATA_OFFSET_PRESENT )
        lsmash_ifprintf( fp, indent, "base_data_offset = %"PRIu64"\n", tfhd->base_data_offset );
    if( tfhd->flags & ISOM_TF_FLAGS_SAMPLE_DESCRIPTION_INDEX_PRESENT )
        lsmash_ifprintf( fp, indent, "sample_description_index = %"PRIu32"\n", tfhd->sample_description_index );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT )
        lsmash_ifprintf( fp, indent, "default_sample_duration = %"PRIu32"\n", tfhd->default_sample_duration );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_SIZE_PRESENT )
        lsmash_ifprintf( fp, indent, "default_sample_size = %"PRIu32"\n", tfhd->default_sample_size );
    if( tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT )
        isom_ifprintf_sample_flags( fp, indent, "default_sample_flags", &tfhd->default_sample_flags );
    return 0;
}

static int isom_print_tfdt( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tfdt_t *tfdt = (isom_tfdt_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Fragment Base Media Decode Time Box" );
    lsmash_ifprintf( fp, indent, "baseMediaDecodeTime = %"PRIu64"\n", tfdt->baseMediaDecodeTime );
    return 0;
}

static int isom_print_trun( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_trun_t *trun = (isom_trun_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Fragment Run Box" );
    ++indent;
    if( trun->flags & ISOM_TR_FLAGS_DATA_OFFSET_PRESENT                    ) lsmash_ifprintf( fp, indent, "data-offset-present\n" );
    if( trun->flags & ISOM_TR_FLAGS_FIRST_SAMPLE_FLAGS_PRESENT             ) lsmash_ifprintf( fp, indent, "first-sample-flags-present\n" );
    if( trun->flags & ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT                ) lsmash_ifprintf( fp, indent, "sample-duration-present\n" );
    if( trun->flags & ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT                    ) lsmash_ifprintf( fp, indent, "sample-size-present\n" );
    if( trun->flags & ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT                   ) lsmash_ifprintf( fp, indent, "sample-flags-present\n" );
    if( trun->flags & ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT ) lsmash_ifprintf( fp, indent, "sample-composition-time-offsets-present\n" );
    lsmash_ifprintf( fp, --indent, "sample_count = %"PRIu32"\n", trun->sample_count );
    if( trun->flags & ISOM_TR_FLAGS_DATA_OFFSET_PRESENT )
        lsmash_ifprintf( fp, indent, "data_offset = %"PRId32"\n", trun->data_offset );
    if( trun->flags & ISOM_TR_FLAGS_FIRST_SAMPLE_FLAGS_PRESENT )
        isom_ifprintf_sample_flags( fp, indent, "first_sample_flags", &trun->first_sample_flags );
    if( trun->optional )
    {
        uint32_t i = 0;
        for( lsmash_entry_t *entry = trun->optional->head; entry; entry = entry->next )
        {
            isom_trun_optional_row_t *row = (isom_trun_optional_row_t *)entry->data;
            lsmash_ifprintf( fp, indent++, "sample[%"PRIu32"]\n", i++ );
            if( trun->flags & ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT )
                lsmash_ifprintf( fp, indent, "sample_duration = %"PRIu32"\n", row->sample_duration );
            if( trun->flags & ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT )
                lsmash_ifprintf( fp, indent, "sample_size = %"PRIu32"\n", row->sample_size );
            if( trun->flags & ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT )
                isom_ifprintf_sample_flags( fp, indent, "sample_flags", &row->sample_flags );
            if( trun->flags & ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT )
            {
                if( trun->version == 0 )
                    lsmash_ifprintf( fp, indent, "sample_composition_time_offset = %"PRIu32"\n",
                                     row->sample_composition_time_offset );
                else
                    lsmash_ifprintf( fp, indent, "sample_composition_time_offset = %"PRId32"\n",
                                     (union {uint32_t ui; int32_t si;}){ row->sample_composition_time_offset }.si );
            }
            --indent;
        }
    }
    return 0;
}

static int isom_print_free( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Free Space Box" );
}

static int isom_print_mdat( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Media Data Box" );
}

static int isom_print_mfra( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    return isom_print_simple( fp, box, level, "Movie Fragment Random Access Box" );
}

static int isom_print_tfra( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_tfra_t *tfra = (isom_tfra_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Track Fragment Random Access Box" );
    lsmash_ifprintf( fp, indent, "track_ID = %"PRIu32"\n", tfra->track_ID );
    lsmash_ifprintf( fp, indent, "reserved = 0x%08"PRIx32"\n", tfra->reserved );
    lsmash_ifprintf( fp, indent, "length_size_of_traf_num = %"PRIu8"\n", tfra->length_size_of_traf_num );
    lsmash_ifprintf( fp, indent, "length_size_of_trun_num = %"PRIu8"\n", tfra->length_size_of_trun_num );
    lsmash_ifprintf( fp, indent, "length_size_of_sample_num = %"PRIu8"\n", tfra->length_size_of_sample_num );
    lsmash_ifprintf( fp, indent, "number_of_entry = %"PRIu32"\n", tfra->number_of_entry );
    if( tfra->list )
    {
        uint32_t i = 0;
        for( lsmash_entry_t *entry = tfra->list->head; entry; entry = entry->next )
        {
            isom_tfra_location_time_entry_t *data = (isom_tfra_location_time_entry_t *)entry->data;
            lsmash_ifprintf( fp, indent++, "entry[%"PRIu32"]\n", i++ );
            lsmash_ifprintf( fp, indent, "time = %"PRIu64"\n", data->time );
            lsmash_ifprintf( fp, indent, "moof_offset = %"PRIu64"\n", data->moof_offset );
            lsmash_ifprintf( fp, indent, "traf_number = %"PRIu32"\n", data->traf_number );
            lsmash_ifprintf( fp, indent, "trun_number = %"PRIu32"\n", data->trun_number );
            lsmash_ifprintf( fp, indent, "sample_number = %"PRIu32"\n", data->sample_number );
            --indent;
        }
    }
    return 0;
}

static int isom_print_mfro( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    isom_mfro_t *mfro = (isom_mfro_t *)box;
    int indent = level;
    isom_print_box_common( fp, indent++, box, "Movie Fragment Random Access Offset Box" );
    lsmash_ifprintf( fp, indent, "size = %"PRIu32"\n", mfro->length );
    return 0;
}

int lsmash_print_movie( lsmash_root_t *root, const char *filename )
{
    if( LSMASH_IS_NON_EXISTING_BOX( root ) )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( !file->print || !(file->flags & LSMASH_FILE_MODE_DUMP) )
        return LSMASH_ERR_FUNCTION_PARAM;
    FILE *destination;
    if( !strcmp( filename, "-" ) )
        destination = stdout;
    else
    {
        destination = lsmash_fopen( filename, "wb" );
        if( !destination )
            return LSMASH_ERR_NAMELESS;
    }
    fprintf( destination, "[File]\n" );
    fprintf( destination, "    size = %"PRIu64"\n", file->size );
    for( lsmash_entry_t *entry = file->print->head; entry; entry = entry->next )
    {
        isom_print_entry_t *data = (isom_print_entry_t *)entry->data;
        if( !data || !data->box )
        {
            fclose( destination );
            return LSMASH_ERR_NAMELESS;
        }
        int ret = data->func( destination, file, data->box, data->level );
        if( ret < 0 )
        {
            fclose( destination );
            return ret;
        }
    }
    fclose( destination );
    return 0;
}

static isom_print_box_t isom_select_print_func( isom_box_t *box )
{
    if( box->manager & LSMASH_UNKNOWN_BOX )
        return isom_print_unknown;
    if( LSMASH_IS_EXISTING_BOX( box->parent ) )
    {
        isom_box_t *parent = box->parent;
        if( !lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_FREE )
         && !lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_SKIP )
         && lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        {
            /* OK, this box is a sample entry.
             * Here, determine the suitable sample entry printer by media type if possible. */
            if( isom_check_media_hdlr_from_stsd( (isom_stsd_t *)parent ) )
            {
                lsmash_media_type media_type = isom_get_media_type_from_stsd( (isom_stsd_t *)parent );
                if( media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK )
                    return isom_print_visual_description;
                else if( media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK )
                    return isom_print_audio_description;
                else if( media_type == ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK )
                {
                    if( lsmash_check_box_type_identical( box->type, QT_CODEC_TYPE_TEXT_TEXT ) )
                        return isom_print_text_description;
                    else if( lsmash_check_box_type_identical( box->type, ISOM_CODEC_TYPE_TX3G_TEXT ) )
                        return isom_print_tx3g_description;
                }
                else if( lsmash_check_box_type_identical( box->type, ISOM_CODEC_TYPE_MP4S_SYSTEM ) )
                    return isom_print_mp4s_description;
            }
            return isom_print_unknown;
        }
        if( lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE ) )
        {
            if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_FRMA ) )
                return isom_print_frma;
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_ENDA ) )
                return isom_print_enda;
            else if( lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_TERMINATOR ) )
                return isom_print_terminator;
            else
                return isom_print_sample_description_extesion;
        }
        if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TREF ) )
            return isom_print_track_reference_type;
        if( LSMASH_IS_EXISTING_BOX( parent->parent ) )
        {
            if( lsmash_check_box_type_identical( parent->parent->type, ISOM_BOX_TYPE_STSD ) )
                return isom_print_sample_description_extesion;
            else if( lsmash_check_box_type_identical( parent->parent->type, ISOM_BOX_TYPE_ILST )
                  || lsmash_check_box_type_identical( parent->parent->type,   QT_BOX_TYPE_ILST ) )
            {
                if( parent->type.fourcc == LSMASH_4CC( '-', '-', '-', '-' ) )
                {
                    if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_MEAN ) )
                        return isom_print_mean;
                    if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_NAME ) )
                        return isom_print_name;
                }
                if( lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_DATA ) )
                    return isom_print_data;
            }
        }
        if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_ILST )
         || lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_ILST ) )
            return isom_print_metaitem;
    }
    static struct print_box_table_tag
    {
        lsmash_box_type_t type;
        isom_print_box_t  func;
    } print_box_table[128] = { { LSMASH_BOX_TYPE_INITIALIZER, NULL } };
    if( !print_box_table[0].func )
    {
        /* Initialize the table. */
        int i = 0;
#define ADD_PRINT_BOX_TABLE_ELEMENT( type, func ) print_box_table[i++] = (struct print_box_table_tag){ type, func }
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_FTYP, isom_print_ftyp );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STYP, isom_print_styp );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SIDX, isom_print_sidx );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MOOV, isom_print_moov );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MVHD, isom_print_mvhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_IODS, isom_print_iods );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_CTAB, isom_print_ctab );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TRAK, isom_print_trak );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TKHD, isom_print_tkhd );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_TAPT, isom_print_tapt );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_CLEF, isom_print_clef );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_PROF, isom_print_prof );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_ENOF, isom_print_enof );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_EDTS, isom_print_edts );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_ELST, isom_print_elst );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TREF, isom_print_tref );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MDIA, isom_print_mdia );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MDHD, isom_print_mdhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_HDLR, isom_print_hdlr );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MINF, isom_print_minf );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_VMHD, isom_print_vmhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SMHD, isom_print_smhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_HMHD, isom_print_hmhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_NMHD, isom_print_nmhd );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_GMHD, isom_print_gmhd );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_GMIN, isom_print_gmin );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_TEXT, isom_print_text );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_DINF, isom_print_dinf );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_DREF, isom_print_dref );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_URL,  isom_print_url );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STBL, isom_print_stbl );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STSD, isom_print_stsd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CLAP, isom_print_clap );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_PASP, isom_print_pasp );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_COLR, isom_print_colr );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_COLR, isom_print_colr );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_GLBL, isom_print_glbl );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_GAMA, isom_print_gama );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_FIEL, isom_print_fiel );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_CLLI, isom_print_clli );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_MDCV, isom_print_mdcv );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_CSPC, isom_print_cspc );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_SGBT, isom_print_sgbt );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STSL, isom_print_stsl );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_WAVE, isom_print_wave );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_CHAN, isom_print_chan );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SRAT, isom_print_srat );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_FTAB, isom_print_ftab );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STTS, isom_print_stts );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CTTS, isom_print_ctts );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CSLG, isom_print_cslg );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STSS, isom_print_stss );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_STPS, isom_print_stps );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SDTP, isom_print_sdtp );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STSC, isom_print_stsc );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STSZ, isom_print_stsz );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STZ2, isom_print_stz2 );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_STCO, isom_print_stco );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CO64, isom_print_stco );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SGPD, isom_print_sgpd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SBGP, isom_print_sbgp );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_UDTA, isom_print_udta );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CHPL, isom_print_chpl );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_WLOC, isom_print_WLOC );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_LOOP, isom_print_LOOP );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_SELO, isom_print_SelO );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_ALLF, isom_print_AllF );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_CPRT, isom_print_cprt );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MVEX, isom_print_mvex );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MEHD, isom_print_mehd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TREX, isom_print_trex );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MOOF, isom_print_moof );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MFHD, isom_print_mfhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TRAF, isom_print_traf );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TFHD, isom_print_tfhd );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TFDT, isom_print_tfdt );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TRUN, isom_print_trun );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_FREE, isom_print_free );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_SKIP, isom_print_free );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MDAT, isom_print_mdat );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_KEYS, isom_print_keys );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_META, isom_print_meta );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_ILST, isom_print_ilst );
        ADD_PRINT_BOX_TABLE_ELEMENT(   QT_BOX_TYPE_ILST, isom_print_ilst );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MFRA, isom_print_mfra );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_TFRA, isom_print_tfra );
        ADD_PRINT_BOX_TABLE_ELEMENT( ISOM_BOX_TYPE_MFRO, isom_print_mfro );
        ADD_PRINT_BOX_TABLE_ELEMENT( LSMASH_BOX_TYPE_UNSPECIFIED, NULL );
#undef ADD_PRINT_BOX_TABLE_ELEMENT
    }
    for( int i = 0; print_box_table[i].func; i++ )
        if( lsmash_check_box_type_identical( box->type, print_box_table[i].type ) )
            return print_box_table[i].func;
    return isom_print_unknown;
}

static inline void isom_print_remove_plastic_box( isom_box_t *box )
{
    if( box->manager & LSMASH_ABSENT_IN_FILE )
        /* free flagged box */
        isom_remove_box_by_itself( box );
}

int isom_add_print_func( lsmash_file_t *file, void *box, int level )
{
    if( !(file->flags & LSMASH_FILE_MODE_DUMP) )
    {
        isom_print_remove_plastic_box( box );
        return 0;
    }
    isom_print_entry_t *data = lsmash_malloc( sizeof(isom_print_entry_t) );
    if( !data )
    {
        isom_print_remove_plastic_box( box );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    data->level = level;
    data->box   = (isom_box_t *)box;
    data->func  = isom_select_print_func( (isom_box_t *)box );
    assert( data->func );
    if( lsmash_list_add_entry( file->print, data ) < 0 )
    {
        isom_print_remove_plastic_box( data->box );
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static void isom_remove_print_func( isom_print_entry_t *data )
{
    if( !data || !data->box )
        return;
    isom_print_remove_plastic_box( data->box );
    lsmash_free( data );
}

void isom_printer_destory_list( lsmash_file_t *file )
{
    lsmash_list_destroy( file->print );
    file->print = NULL;
}

lsmash_entry_list_t *isom_printer_create_list( void )
{
    return lsmash_list_create( isom_remove_print_func );
}

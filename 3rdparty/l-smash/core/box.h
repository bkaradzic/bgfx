/*****************************************************************************
 * box.h
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

#ifndef LSMASH_BOX_H
#define LSMASH_BOX_H

/* For generating creation_time and modification_time.
 * According to ISO/IEC-14496-5-2001, the difference between Unix time and Mac OS time is 2082758400.
 * However this is wrong and 2082844800 is correct. */
#include <time.h>
#define ISOM_MAC_EPOCH_OFFSET 2082844800

#include "box_type.h"

/* aliases internally used only for convenience */
typedef struct lsmash_file_tag isom_file_abstract_t;
typedef struct lsmash_root_tag isom_root_abstract_t;
typedef struct isom_unknown_box_tag isom_unknown_t;
typedef struct lsmash_box_tag isom_dummy_t; /* for dummy usage */

typedef struct lsmash_box_tag isom_box_t;
typedef struct isom_unknown_box_tag isom_unknown_box_t;
typedef struct isom_mdhd_tag isom_mdhd_t;
typedef struct isom_stbl_tag isom_stbl_t;

typedef void (*isom_extension_destructor_t)( void *extension_data );
typedef int (*isom_extension_writer_t)( lsmash_bs_t *bs, isom_box_t *box );

typedef int (*isom_bitrate_updater_t)( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index );

/* If size is 1, then largesize is actual size.
 * If size is 0, then this box is the last one in the file. */
#define ISOM_BASEBOX_COMMON                                                                             \
        const lsmash_class_t       *class;                                                              \
        lsmash_root_t              *root;               /* pointer to root */                           \
        lsmash_file_t              *file;               /* pointer to file */                           \
        isom_box_t                 *parent;             /* pointer to the parent box of this box */     \
        void                       *nonexist_ptr;       /* pointer to non-existing box constant */      \
        uint8_t                    *binary;             /* used only when LSMASH_BINARY_CODED_BOX */    \
        isom_extension_destructor_t destruct;           /* box specific destructor */                   \
        isom_extension_writer_t     write;              /* box specific writer */                       \
        size_t                      offset_in_parent;   /* offset of this box in parent box struct */   \
        uint32_t                    manager;            /* flags for L-SMASH */                         \
        uint64_t                    precedence;         /* precedence of the box position */            \
        uint64_t                    pos;                /* starting position of this box in the file */ \
        lsmash_entry_list_t         extensions;         /* extension boxes */                           \
    uint64_t          size;                             /* the number of bytes in this box */           \
    lsmash_box_type_t type

#define ISOM_FULLBOX_COMMON                                         \
    ISOM_BASEBOX_COMMON;                                            \
    uint8_t  version;   /* Basically, version is either 0 or 1 */   \
    uint32_t flags      /* In the actual structure of box, flags is 24 bits. */

#define ISOM_BASEBOX_COMMON_SIZE       8
#define ISOM_FULLBOX_COMMON_SIZE      12
#define ISOM_LIST_FULLBOX_COMMON_SIZE 16

/* flags for L-SMASH */
#define LSMASH_UNKNOWN_BOX       0x001
#define LSMASH_ABSENT_IN_FILE    0x002
#define LSMASH_QTFF_BASE         0x004
#define LSMASH_VIDEO_DESCRIPTION 0x008
#define LSMASH_AUDIO_DESCRIPTION 0x010
#define LSMASH_FULLBOX           0x020
#define LSMASH_LAST_BOX          0x040
#define LSMASH_INCOMPLETE_BOX    0x080
#define LSMASH_BINARY_CODED_BOX  0x100
#define LSMASH_PLACEHOLDER       0x200
#define LSMASH_WRITTEN_BOX       0x400
#define LSMASH_NON_EXISTING_BOX  0x800  /* This flag indicates a read only non-existing box constant.
                                         * Don't use for wild boxes other than non-existing box constants
                                         * because this flags prevents attempting to freeing its box. */

/* Use these macros for checking existences of boxes.
 * If the result of LSMASH_IS_EXISTING_BOX is 0, the evaluated box is read only.
 * If the result of LSMASH_IS_NON_EXISTING_BOX is 1, the evaluated box is read only. */
#define LSMASH_IS_EXISTING_BOX( box_ptr ) \
    ((box_ptr) && !((box_ptr)->manager & LSMASH_NON_EXISTING_BOX))
#define LSMASH_IS_NON_EXISTING_BOX( box_ptr ) \
    (!(box_ptr) || ((box_ptr)->manager & LSMASH_NON_EXISTING_BOX))

#define LSMASH_IS_BOX_ADDITION_SUCCESS( box_ptr ) \
    (!((box_ptr)->manager & LSMASH_NON_EXISTING_BOX))
#define LSMASH_IS_BOX_ADDITION_FAILURE( box_ptr ) \
    (!!((box_ptr)->manager & LSMASH_NON_EXISTING_BOX))

/* Use this macro for disabling a predefined child box in struct.
 * Predefined childs must not be NULL for safety. */
#define LSMASH_MAKE_BOX_NON_EXISTING( box_ptr ) \
    (box_ptr) = (void *)(box_ptr)->nonexist_ptr

/* 12-byte ISO reserved value:
 * 0xXXXXXXXX-0011-0010-8000-00AA00389B71 */
static const uint8_t static_lsmash_iso_12_bytes[12]
    = { 0x00, 0x11, 0x00, 0x10, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
#define LSMASH_ISO_12_BYTES static_lsmash_iso_12_bytes

/* L-SMASH original 12-byte QuickTime file format value for CODEC discrimination mainly:
 * 0xXXXXXXXX-0F11-4DA5-BF4E-F2C48C6AA11E */
static const uint8_t static_lsmash_qtff_12_bytes[12]
    = { 0x0F, 0x11, 0x4D, 0xA5, 0xBF, 0x4E, 0xF2, 0xC4, 0x8C, 0x6A, 0xA1, 0x1E };
#define LSMASH_QTFF_12_BYTES static_lsmash_qtff_12_bytes

struct lsmash_box_tag
{
    ISOM_FULLBOX_COMMON;
};

/* Unknown Box
 * This structure is for boxes we don't know or define yet.
 * This box must be always appended as an extension box. */
struct isom_unknown_box_tag
{
    ISOM_BASEBOX_COMMON;
    uint32_t unknown_size;
    uint8_t *unknown_field;
};

/* File Type Box
 * This box identifies the specifications to which this file complies.
 * This box shall occur before any variable-length box.
 * In the absence of this box, the file is QuickTime file format or MP4 version 1 file format.
 * In MP4 version 1 file format, Object Descriptor Box is mandatory.
 * In QuickTime file format, Object Descriptor Box isn't defined.
 * Therefore, if this box and an Object Descriptor Box are absent in the file, the file shall be QuickTime file format. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t major_brand;           /* brand identifier */
    uint32_t minor_version;         /* the minor version of the major brand */
    uint32_t *compatible_brands;    /* a list, to the end of the box, of brands */

        uint32_t brand_count;       /* the number of factors in compatible_brands array */
} isom_ftyp_t;

/* Color Table Box
 * This box defines a list of preferred colors for displaying the movie on devices that support only 256 colors.
 * The list may contain up to 256 colors. This box contains a Macintosh color table data structure.
 * This box is defined in QuickTime File Format Specification.
 * The color table structure is also defined in struct ColorTable defined in Quickdraw.h. */
typedef struct
{
    /* An array of colors.
     * Each color is made of four unsigned 16-bit integers. */
    uint16_t value;     /* index or other value
                         * Must be set to 0. */
    /* true color */
    uint16_t r;         /* magnitude of red component */
    uint16_t g;         /* magnitude of green component */
    uint16_t b;         /* magnitude of blue component */
} isom_qt_color_array_t;

typedef struct
{
    uint32_t seed;          /* unique identifier for table
                             * Must be set to 0. */
    uint16_t flags;         /* high bit: 0 = PixMap; 1 = device
                             * Must be set to 0x8000. */
    uint16_t size;          /* the number of colors in the following color array
                             * This is a zero-relative value;
                             * setting this field to 0 means that there is one color in the array. */
    isom_qt_color_array_t *array;
} isom_qt_color_table_t;

typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_qt_color_table_t color_table;
} isom_ctab_t;

/* Track Header Box
 * This box specifies the characteristics of a single track. */
typedef struct
{
    /* version is either 0 or 1
     * flags
     *      0x000001: Indicates that the track is enabled.
     *                A disabled track is treated as if it were not present.
     *      0x000002: Indicates that the track is used in the presentation.
     *      0x000004: Indicates that the track is used when previewing the presentation.
     *      0x000008: Indicates that the track is used in the movie's poster. (only defined in QuickTime file format)
     * ISOM: If in a presentation all tracks have neither track_in_movie nor track_in_preview set,
     *       then all tracks shall be treated as if both flags were set on all tracks. */
    ISOM_FULLBOX_COMMON;
    /* version == 0: uint64_t -> uint32_t */
    uint64_t creation_time;         /* the creation time of this track (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint64_t modification_time;     /* the most recent time the track was modified (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint32_t track_ID;              /* an integer that uniquely identifies the track
                                     * Track IDs are never re-used and cannot be zero. */
    uint32_t reserved1;
    uint64_t duration;              /* the duration of this track expressed in the movie timescale units */
    /* The following fields are treated as
     * ISOM: template fields.
     * MP41: reserved fields.
     * MP42: ignored fileds since compositions are done using BIFS system.
     * 3GPP: ignored fields except for alternate_group.
     * QTFF: usable fields. */
    uint32_t reserved2[2];
    int16_t  layer;                 /* the front-to-back ordering of video tracks; tracks with lower numbers are closer to the viewer. */
    int16_t  alternate_group;       /* an integer that specifies a group or collection of tracks
                                     * If this field is not 0, it should be the same for tracks that contain alternate data for one another
                                     * and different for tracks belonging to different such groups.
                                     * Only one track within an alternate group should be played or streamed at any one time. */
    int16_t  volume;                /* fixed point 8.8 number. 0x0100 is full volume. */
    uint16_t reserved3;
    int32_t  matrix[9];             /* transformation matrix for the video */
    /* track's visual presentation size
     * All images in the sequence are scaled to this size, before any overall transformation of the track represented by the matrix.
     * Note: these fields are treated as reserved in MP4 version 1. */
    uint32_t width;                 /* fixed point 16.16 number */
    uint32_t height;                /* fixed point 16.16 number */
    /* */
} isom_tkhd_t;

/* Track Clean Aperture Dimensions Box
 * A presentation mode where clap and pasp are reflected. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t width;     /* fixed point 16.16 number */
    uint32_t height;    /* fixed point 16.16 number */
} isom_clef_t;

/* Track Production Aperture Dimensions Box
 * A presentation mode where pasp is reflected. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t width;     /* fixed point 16.16 number */
    uint32_t height;    /* fixed point 16.16 number */
} isom_prof_t;

/* Track Encoded Pixels Dimensions Box
 * A presentation mode where clap and pasp are not reflected. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t width;     /* fixed point 16.16 number */
    uint32_t height;    /* fixed point 16.16 number */
} isom_enof_t;

/* Track Aperture Mode Dimensions Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_clef_t *clef;      /* Track Clean Aperture Dimensions Box */
    isom_prof_t *prof;      /* Track Production Aperture Dimensions Box */
    isom_enof_t *enof;      /* Track Encoded Pixels Dimensions Box */
} isom_tapt_t;

/* Edit List Box
 * This box contains an explicit timeline map.
 * Each entry defines part of the track timeline: by mapping part of the media timeline, or by indicating 'empty' time,
 * or by defining a 'dwell', where a single time-point in the media is held for a period.
 * The last edit in a track shall never be an empty edit.
 * Any difference between the duration in the Movie Header Box, and the track's duration is expressed as an implicit empty edit at the end.
 * It is recommended that any edits, explicit or implied, not select any portion of the composition timeline that doesn't map to a sample.
 * Therefore, if the first sample in the track has non-zero CTS, then this track should have at least one edit and the start time in it should
 * correspond to the value of the CTS the first sample has or more not to exceed the largest CTS in this track. */
typedef struct
{
    /* This entry is called Timeline Mapping Edit (TME) entry in UltraViolet Common File Format.
     * version == 0: 64bits -> 32bits */
    uint64_t segment_duration;  /* the duration of this edit expressed in the movie timescale units */
    int64_t  media_time;        /* the starting composition time within the media of this edit segment
                                 * If this field is set to -1, it is an empty edit. */
    int32_t  media_rate;        /* the relative rate at which to play the media corresponding to this edit segment
                                 * If this value is 0, then the edit is specifying a 'dwell':
                                 * the media at media_time is presented for the segment_duration.
                                 * This field is expressed as 16.16 fixed-point number. */
} isom_elst_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;        /* version is either 0 or 1 */
    lsmash_entry_list_t *list;
} isom_elst_t;

/* Edit Box
 * This optional box maps the presentation time-line to the media time-line as it is stored in the file.
 * In the absence of this box, there is an implicit one-to-one mapping of these time-lines,
 * and the presentation of a track starts at the beginning of the presentation. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_elst_t *elst;     /* Edit List Box */
} isom_edts_t;

/* Track Reference Box
 * The Track Reference Box contains Track Reference Type Boxes.
 * Track Reference Type Boxes define relationships between tracks.
 * They allow one track to specify how it is related to other tracks. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t *track_ID;         /* track_IDs of reference tracks / Zero value must not be used */

        uint32_t ref_count;     /* number of reference tracks */
} isom_tref_type_t;

typedef struct
{
    ISOM_BASEBOX_COMMON;
    lsmash_entry_list_t ref_list;   /* Track Reference Type Boxes */
} isom_tref_t;

/* Media Header Box
 * This box declares overall information that is media-independent, and relevant to characteristics of the media in a track.*/
struct isom_mdhd_tag
{
    ISOM_FULLBOX_COMMON;            /* version is either 0 or 1 */
    /* version == 0: uint64_t -> uint32_t */
    uint64_t creation_time;         /* the creation time of the media in this track (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint64_t modification_time;     /* the most recent time the media in this track was modified (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint32_t timescale;             /* media timescale: timescale for this media */
    uint64_t duration;              /* the duration of this media expressed in the timescale indicated in this box */
    /* */
    uint16_t language;              /* ISOM: ISO-639-2/T language codes. Most significant 1-bit is 0.
                                     *       Each character is packed as the difference between its ASCII value and 0x60.
                                     * QTFF: Macintosh language codes is usually used.
                                     *       Mac's value is less than 0x800 while ISO's value is 0x800 or greater. */
    int16_t quality;                /* ISOM: pre_defined / QTFF: the media's playback quality */
};

/* Handler Reference Box
 * In Media Box, this box is mandatory and (ISOM: should/QTFF: must) come before Media Information Box.
 * ISOM: this box might be also in Meta Box.
 * QTFF: this box might be also in Media Information Box. If this box is present there, it must come before Data Information Box. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t componentType;             /* ISOM: pre_difined = 0
                                         * QTFF: 'mhlr' for Media Handler Reference Box and 'dhlr' for Data Handler Reference Box  */
    uint32_t componentSubtype;          /* Both ISOM and QT: when present in Media Handler Reference Box, this field defines the type of media data.
                                         * ISOM: when present in Metadata Handler Reference Box, this field defines the format of the meta box contents.
                                         * QTFF: when present in Data Handler Reference Box, this field defines the data reference type. */
    /* The following fields are defined in QTFF however these fields aren't mentioned in QuickTime SDK and are reserved in the specification.
     * In ISOM, these fields are still defined as reserved. */
    uint32_t componentManufacturer;     /* vendor indentification / A value of 0 matches any manufacturer. */
    uint32_t componentFlags;            /* flags describing required component capabilities
                                         * The high-order 8 bits should be set to 0.
                                         * The low-order 24 bits are specific to each component type. */
    uint32_t componentFlagsMask;        /* This field indicates which flags in the componentFlags field are relevant to this operation. */
    /* */
    uint8_t *componentName;             /* ISOM: a null-terminated string in UTF-8 characters
                                         * QTFF: Pascal string */

        uint32_t componentName_length;
} isom_hdlr_t;


/** Media Information Header Boxes
 ** There is a different media information header for each track type
 ** (corresponding to the media handler-type); the matching header shall be present. **/
/* Video Media Header Box
 * This box contains general presentation information, independent of the coding, for video media. */
typedef struct
{
    ISOM_FULLBOX_COMMON;        /* flags is 1 */
    uint16_t graphicsmode;      /* template: graphicsmode = 0 */
    uint16_t opcolor[3];        /* template: opcolor = { 0, 0, 0 } */
} isom_vmhd_t;

/* Sound Media Header Box
 * This box contains general presentation information, independent of the coding, for audio media. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    int16_t balance;        /* a fixed-point 8.8 number that places mono audio tracks in a stereo space. template: balance = 0 */
    uint16_t reserved;
} isom_smhd_t;

/* Hint Media Header Box
 * This box contains general information, independent of the protocol, for hint tracks. (A PDU is a Protocol Data Unit.) */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint16_t maxPDUsize;        /* the size in bytes of the largest PDU in this (hint) stream */
    uint16_t avgPDUsize;        /* the average size of a PDU over the entire presentation */
    uint32_t maxbitrate;        /* the maximum rate in bits/second over any window of one second */
    uint32_t avgbitrate;        /* the average rate in bits/second over the entire presentation */
    uint32_t reserved;
    /* run time variables for calculating avgPDUsize, should not be written to file */
    uint64_t combinedPDUsize;
    uint64_t PDUcount;
} isom_hmhd_t;

/* Null Media Header Box
 * This box may be used for streams other than visual and audio (e.g., timed metadata streams). */
typedef struct
{
    /* Streams other than visual and audio may use a Null Media Header Box */
    ISOM_FULLBOX_COMMON;    /* flags is currently all zero */
} isom_nmhd_t;

/* Generic Media Information Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint16_t graphicsmode;
    uint16_t opcolor[3];
    int16_t balance;        /* This field is nomally set to 0. */
    uint16_t reserved;      /* Reserved for use by Apple. Set this field to 0. */
} isom_gmin_t;

/* Text Media Information Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    int32_t matrix[9];      /* Unkown fields. Default values are probably:
                             * { 0x00010000, 0, 0, 0, 0x00010000, 0, 0, 0, 0x40000000 } */
} isom_text_t;

/* Generic Media Information Header Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_gmin_t *gmin;      /* Generic Media Information Box */
    isom_text_t *text;      /* Text Media Information Box */
} isom_gmhd_t;
/** **/

/* Data Reference Box
 * name and location fields are expressed in null-terminated string using UTF-8 characters. */
typedef struct
{
    /* This box is DataEntryUrlBox or DataEntryUrnBox */
    ISOM_FULLBOX_COMMON;    /* flags == 0x000001 means that the media data is in the same file
                             * as the Movie Box containing this data reference. */
    char *name;             /* only for DataEntryUrnBox */
    char *location;         /* a location to find the resource with the given name */

        uint32_t       name_length;
        uint32_t       location_length;
        lsmash_file_t *ref_file;    /* pointer to the handle of the referenced file */
} isom_dref_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t list;
} isom_dref_t;

/* Data Information Box */
typedef struct
{
    /* This box is in Media Information Box or Meta Box */
    ISOM_BASEBOX_COMMON;
    isom_dref_t *dref;      /* Data Reference Box */
} isom_dinf_t;

/** Sample Description **/
/* ES Descriptor Box */
struct mp4sys_ES_Descriptor_t; /* FIXME: I think these structs using mp4sys should be placed in isom.c */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    struct mp4sys_ES_Descriptor_t *ES;
} isom_esds_t;

/* MPEG-4 Bit Rate Box
 * This box signals the bit rate information of the AVC video stream. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t bufferSizeDB;  /* the size of the decoding buffer for the elementary stream in bytes */
    uint32_t maxBitrate;    /* the maximum rate in bits/second over any window of one second */
    uint32_t avgBitrate;    /* the average rate in bits/second over the entire presentation */
} isom_btrt_t;

typedef struct
{
    /* This box is in RTP and RTP reception hint track sample descriptions */
    ISOM_BASEBOX_COMMON;
    uint32_t timescale;
} isom_tims_t;

typedef struct
{
    /* This box is in RTP and RTP reception hint track sample descriptions */
    ISOM_BASEBOX_COMMON;
    int32_t offset;
} isom_tsro_t;

typedef struct
{
    /* This box is in RTP reception hint track sample description */
    ISOM_BASEBOX_COMMON;
    unsigned int reserved       : 6;
    unsigned int timestamp_sync : 2;
} isom_tssy_t;


/* Global Header Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t header_size;
    uint8_t *header_data;
} isom_glbl_t;

/* Clean Aperture Box
 * There are notionally four values in this box and these parameters are represented as a fraction N/D.
 * Here, we refer to the pair of parameters fooN and fooD as foo.
 * Considering the pixel dimensions as defined by the VisualSampleEntry width and height.
 * If picture centre of the image is at pcX and pcY, then horizOff and vertOff are defined as follows:
 *  pcX = horizOff + (width - 1)/2;
 *  pcY = vertOff + (height - 1)/2;
 * The leftmost/rightmost pixel and the topmost/bottommost line of the clean aperture fall at:
 *  pcX +/- (cleanApertureWidth - 1)/2;
 *  pcY +/- (cleanApertureHeight - 1)/2;
 * QTFF: this box is a mandatory extension for all uncompressed Y'CbCr data formats. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t cleanApertureWidthN;
    uint32_t cleanApertureWidthD;
    uint32_t cleanApertureHeightN;
    uint32_t cleanApertureHeightD;
    int32_t  horizOffN;
    uint32_t horizOffD;
    int32_t  vertOffN;
    uint32_t vertOffD;
} isom_clap_t;

/* Pixel Aspect Ratio Box
 * This box specifies the aspect ratio of a pixel, in arbitrary units.
 * If a pixel appears H wide and V tall, then hSpacing/vSpacing is equal to H/V.
 * When adjusting pixel aspect ratio, normally, the horizontal dimension of the video is scaled, if needed. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t hSpacing;      /* horizontal spacing */
    uint32_t vSpacing;      /* vertical spacing */
} isom_pasp_t;

/* ISOM: Colour Information Box / QTFF: Color Parameter Box
 * This box is used to map the numerical values of pixels in the file to a common representation of color
 * in which images can be correctly compared, combined, and displayed.
 * If colour information is supplied in both this box, and also in the video bitstream,
 * this box takes precedence, and over-rides the information in the bitstream.
 * For QuickTime file format:
 *   This box ('colr') supersedes the Gamma Level Box ('gama').
 *   Writers of QTFF should never write both into an Image Description, and readers of QTFF should ignore 'gama' if 'colr' is present.
 *   Note: this box is a mandatory extension for all uncompressed Y'CbCr data formats.
 * For ISO Base Media file format:
 *   Colour information may be supplied in one or more Colour Information Boxes placed in a VisualSampleEntry.
 *   These should be placed in order in the sample entry starting with the most accurate (and potentially the most difficult to process), in progression to the least.
 *   These are advisory and concern rendering and colour conversion, and there is no normative behaviour associated with them; a reader may choose to use the most suitable. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t color_parameter_type;          /* QTFF: 'nclc' or 'prof'
                                             * ISOM: 'nclx', 'rICC' or 'prof' */
    /* for 'nclc' and 'nclx' */
    uint16_t primaries_index;               /* CIE 1931 xy chromaticity coordinates */
    uint16_t transfer_function_index;       /* nonlinear transfer function from RGB to ErEgEb */
    uint16_t matrix_index;                  /* matrix from ErEgEb to EyEcbEcr */
    /* for 'nclx' */
    unsigned full_range_flag : 1;
    unsigned reserved        : 7;
} isom_colr_t;

/* Gamma Level Box
 * This box is used to indicate that the decompressor corrects gamma level at display time.
 * This box is defined in QuickTime File Format Specification and ImageCompression.h. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t level;     /* A fixed-point 16.16 number indicating the gamma level at which the image was captured.
                         * Zero value indicates platform's standard gamma. */
} isom_gama_t;

/* Field/Frame Information Box
 * This box is used by applications to modify decompressed image data or by decompressor components to determine field display order.
 * This box is defined in QuickTime File Format Specification, dispatch019 and ImageCodec.h.
 * Note: this box is a mandatory extension for all uncompressed Y'CbCr data formats. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint8_t fields;     /* the number of fields per frame
                         * 1: progressive scan
                         * 2: 2:1 interlaced */
    uint8_t detail;     /* field ordering */
} isom_fiel_t;

/* Content Light Level Info Box
 * This Box is used to identify the upper bounds for the nominal target brightness light level of the pictures of the video.
 * Note:  The format of this box is identical to h.265 (HEVC) SEI Payload Type 144 (ISO-23008-2 D.2.35) */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint16_t max_content_light_level;
    uint16_t max_pic_average_light_level;
} isom_clli_t;

/* Master Display Color Volume Box
 * This box is used to identify the color volume of a display that is considered to be the mastering display for the video content
 * Note:  The format of this box is identical to the h.265 (HEVC) SEI Payload Type 137 (ISO-23008-2 D.2.28) */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint16_t display_primaries_g_x;
    uint16_t display_primaries_g_y;
    uint16_t display_primaries_b_x;
    uint16_t display_primaries_b_y;
    uint16_t display_primaries_r_x;
    uint16_t display_primaries_r_y;
    uint16_t white_point_x;
    uint16_t white_point_y;
    uint32_t max_display_mastering_luminance;
    uint32_t min_display_mastering_luminance;
} isom_mdcv_t;

/* Colorspace Box
 * This box is defined in ImageCompression.h. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t pixel_format;      /* the native pixel format of an image */
} isom_cspc_t;

/* Significant Bits Box
 * This box is defined in Letters from the Ice Floe dispatch019.
 * Note: this box is a mandatory extension for 'v216' (Uncompressed Y'CbCr, 10, 12, 14, or 16-bit-per-component 4:2:2). */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint8_t significantBits;    /* the number of significant bits per component */
} isom_sgbt_t;

/* Sample Scale Box
 * If this box is present and can be interpreted by the decoder,
 * all samples shall be displayed according to the scaling behaviour that is specified in this box.
 * Otherwise, all samples are scaled to the size that is indicated by the width and height field in the Track Header Box.
 * This box is defined in ISO Base Media file format. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint8_t constraint_flag;    /* Upper 7-bits are reserved.
                                 * If this flag is set, all samples described by this sample entry shall be scaled
                                 * according to the method specified by the field 'scale_method'. */
    uint8_t scale_method;       /* The semantics of the values for scale_method are as specified for the 'fit' attribute of regions in SMIL 1.0. */
    int16_t display_center_x;
    int16_t display_center_y;
} isom_stsl_t;

/* Sample Entry */
#define ISOM_SAMPLE_ENTRY           \
    ISOM_BASEBOX_COMMON;            \
    uint8_t reserved[6];            \
    uint16_t data_reference_index

typedef struct
{
    ISOM_SAMPLE_ENTRY;
} isom_sample_entry_t;

/* Mpeg Sample Entry */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
} isom_mp4s_entry_t;

/* ISOM: Visual Sample Entry / QTFF: Image Description
 * For maximum compatibility, the following extension boxes should follow, not precede,
 * any extension boxes defined in or required by derived specifications.
 *   Clean Aperture Box
 *   Pixel Aspect Ratio Box */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
    int16_t  version;           /* ISOM: pre_defined / QTFF: sample description version */
    int16_t  revision_level;    /* ISOM: reserved / QTFF: version of the CODEC */
    int32_t  vendor;            /* ISOM: pre_defined / QTFF: whose CODEC */
    uint32_t temporalQuality;   /* ISOM: pre_defined / QTFF: the temporal quality factor */
    uint32_t spatialQuality;    /* ISOM: pre_defined / QTFF: the spatial quality factor */
    /* The width and height are the maximum pixel counts that the codec will deliver.
     * Since these are counts they do not take into account pixel aspect ratio. */
    uint16_t width;
    uint16_t height;
    /* */
    uint32_t horizresolution;   /* 16.16 fixed-point / template: horizresolution = 0x00480000 / 72 dpi */
    uint32_t vertresolution;    /* 16.16 fixed-point / template: vertresolution = 0x00480000 / 72 dpi */
    uint32_t dataSize;          /* ISOM: reserved / QTFF: if known, the size of data for this descriptor */
    uint16_t frame_count;       /* frame per sample / template: frame_count = 1 */
    char compressorname[33];    /* a fixed 32-byte field, with the first byte set to the number of bytes to be displayed */
    uint16_t depth;             /* ISOM: template: depth = 0x0018
                                 * AVC : 0x0018: colour with no alpha
                                 *       0x0028: grayscale with no alpha
                                 *       0x0020: gray or colour with alpha
                                 * QTFF: depth of this data (1-32) or (33-40 grayscale) */
    int16_t color_table_ID;     /* ISOM: template: pre_defined = -1
                                 * QTFF: color table ID
                                 *       If this field is set to -1, the default color table should be used for the specified depth
                                 *       If the color table ID is set to 0, a color table is contained within the sample description itself.
                                 *       The color table immediately follows the color table ID field. */
    /* Color table follows color_table_ID only when color_table_ID is set to 0. */
    isom_qt_color_table_t color_table;  /* a list of preferred colors for displaying the movie on devices that support only 256 colors */
} isom_visual_entry_t;

/* Format Box
 * This box shows the data format of the stored sound media.
 * ISO base media file format also defines the same four-character-code for the type field,
 * however, that is used to indicate original sample description of the media when a protected sample entry is used. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t data_format;       /* copy of sample description type */
} isom_frma_t;

/* Audio Endian Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    int16_t littleEndian;
} isom_enda_t;

/* MPEG-4 Audio Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t unknown;           /* always 0? */
} isom_mp4a_t;

/* Terminator Box
 * This box is present to indicate the end of the sound description. It contains no data. */
typedef struct
{
    ISOM_BASEBOX_COMMON;    /* size = 8, type = 0x00000000 */
} isom_terminator_t;

/* Sound Information Decompression Parameters Box
 * This box is defined in QuickTime file format.
 * This box provides the ability to store data specific to a given audio decompressor in the sound description.
 * The contents of this box are dependent on the audio decompressor. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_frma_t       *frma;            /* Format Box */
    isom_enda_t       *enda;            /* Audio Endian Box */
    isom_mp4a_t       *mp4a;            /* MPEG-4 Audio Box */
    isom_terminator_t *terminator;      /* Terminator Box */
} isom_wave_t;

/* Audio Channel Layout Box
 * This box is defined in QuickTime file format or Apple Lossless Audio inside ISO Base Media. */
typedef struct
{
    uint32_t channelLabel;          /* the channelLabel that describes the channel */
    uint32_t channelFlags;          /* flags that control the interpretation of coordinates */
    uint32_t coordinates[3];        /* an ordered triple that specifies a precise speaker location / 32-bit floating point */
} isom_channel_description_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t channelLayoutTag;              /* the channelLayoutTag indicates the layout */
    uint32_t channelBitmap;                 /* If channelLayoutTag is set to 0x00010000, this field is the channel usage bitmap. */
    uint32_t numberChannelDescriptions;     /* the number of items in the Channel Descriptions array */
    /* Channel Descriptions array */
    isom_channel_description_t *channelDescriptions;
} isom_chan_t;

/* Sampling Rate Box
 * This box may be present only in an AudioSampleEntryV1, and when present,
 * it overrides the samplerate field and documents the actual sampling rate.
 * When this box is present, the media timescale should be the same as the
 * sampling rate, or an integer division or multiple of it. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t sampling_rate;     /* the actual sampling rate of the audio media, expressed as a 32-bit integer
                                 * The value of this field overrides the samplerate field in the AudioSampleEntryV1
                                 * and documents the actual sampling rate. */
} isom_srat_t;

/* ISOM: Audio Sample Entry / QTFF: Sound Description */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
    int16_t  version;           /* ISOM: version = 0 is used to support non-high samplerate audio format.
                                 *       version = 1, called AudioSampleEntryV1, is used to support high samplerate audio format.
                                 *       An AudioSampleEntryV1 requires that the enclosing Sample Description Box also takes the version 1.
                                 *       For maximum compatibility, an AudioSampleEntryV1 should only be used when needed.
                                 * QTFF: version = 0 supports only 'raw ' or 'twos' audio format.
                                 *       version = 1 is used to support out-of-band configuration settings for decompression.
                                 *       version = 2 is used to support high samplerate, or 3 or more multichannel audio format. */
    int16_t  revision_level;    /* ISOM: reserved / QTFF: version of the CODEC */
    int32_t  vendor;            /* ISOM: reserved / QTFF: whose CODEC */
    uint16_t channelcount;      /* ISOM: template: channelcount = 2
                                 *       channelcount is a value greater than zero that indicates the maximum number of channels that the
                                 *       audio could deliver.
                                 *       A channelcount of 1 indicates mono audio, and 2 indicates stereo (left/right).
                                 *       When values greater than 2 are used, the codec configuration should identify the channel assignment.
                                 * QTFF: the number of audio channels
                                 *       Allowable values are 1 (mono) or 2 (stereo).
                                 *       For more than 2, set this field to 3 and use numAudioChannels instead of this field. */
    uint16_t samplesize;        /* ISOM: template: samplesize = 16
                                 * QTFF: the number of bits in each uncompressed sample for a single channel
                                 *       Allowable values are 8 or 16.
                                 *       For non-mod8, set this field to 16 and use constBitsPerChannel instead of this field.
                                 *       For more than 16, set this field to 16 and use bytesPerPacket instead of this field. */
    int16_t  compression_ID;    /* ISOM: pre_defined
                                 * QTFF: version = 0 -> must be set to 0.
                                 *       version = 2 -> must be set to -2. */
    uint16_t packet_size;       /* ISOM: reserved / QTFF: must be set to 0. */
    uint32_t samplerate;        /* the sampling rate expressed as a 16.16 fixed-point number
                                 * ISOM: template: samplerate = {default samplerate of media}<<16
                                 *       When it is desired to indicate an audio sampling rate greater than the value that can be represented in
                                 *       this field, this field should contain a value left-shifted 16 bits that matches the media timescale,
                                 *       or be an integer division or multiple of it.
                                 * QTFF: the integer portion should match the media's timescale.
                                 *       If this field is invalid because of higher samplerate,
                                 *       then set this field to 0x00010000 and use audioSampleRate instead of this field. */
    /* QTFF-based version 1 fields
     * These fields are for description of the compression ratio of fixed ratio audio compression algorithms.
     * If these fields are not used, they are set to 0. */
    uint32_t samplesPerPacket;      /* For compressed audio, be set to the number of uncompressed frames generated by a compressed frame.
                                     * For uncompressed audio, shall be set to 1. */
    uint32_t bytesPerPacket;        /* the number of bytes in a sample for a single channel */
    uint32_t bytesPerFrame;         /* the number of bytes in a frame */
    uint32_t bytesPerSample;        /* 8-bit audio: 1, other audio: 2 */
    /* QTFF-based version 2 fields
     * LPCMFrame: one sample from each channel.
     * AudioPacket: For uncompressed audio, an AudioPacket is simply one LPCMFrame.
     *              For compressed audio, an AudioPacket is the natural compressed access unit of that format. */
    uint32_t sizeOfStructOnly;                  /* offset to extensions */
    uint64_t audioSampleRate;                   /* 64-bit floating point */
    uint32_t numAudioChannels;                  /* any channel assignment info will be in Audio Channel Layout Box. */
    int32_t  always7F000000;                    /* always 0x7F000000 */
    uint32_t constBitsPerChannel;               /* only set if constant (and only for uncompressed audio) */
    uint32_t formatSpecificFlags;
    uint32_t constBytesPerAudioPacket;          /* only set if constant */
    uint32_t constLPCMFramesPerAudioPacket;     /* only set if constant */
} isom_audio_entry_t;

/* Hint Sample Entry data field for
 * rtp hint track, 
 * srtp hint track,
 * rtp reception hint track and 
 * srtp reception hint track
 * rtcp reception hint track
 * srtcp reception hint track
 */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
    uint16_t hinttrackversion;         /* = 1 */
    uint16_t highestcompatibleversion; /* = 1 */
    uint32_t maxpacketsize;
} isom_hint_entry_t;

/* Metadata Sample Entry */
#define ISOM_METADATA_SAMPLE_ENTRY \
    ISOM_SAMPLE_ENTRY

typedef struct
{
    ISOM_METADATA_SAMPLE_ENTRY;
} isom_metadata_entry_t;

/* QuickTime Text Sample Description */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
    int32_t displayFlags;
    int32_t textJustification;
    uint16_t bgColor[3];            /* background RGB color */
    /* defaultTextBox */
    int16_t top;
    int16_t left;
    int16_t bottom;
    int16_t right;
    /* defaultStyle */
    int32_t scrpStartChar;          /* starting character position */
    int16_t scrpHeight;
    int16_t scrpAscent;
    int16_t scrpFont;
    uint16_t scrpFace;              /* only first 8-bits are used */
    int16_t scrpSize;
    uint16_t scrpColor[3];          /* foreground RGB color */
    /* defaultFontName is Pascal string */
    uint8_t font_name_length;
    char *font_name;
} isom_qt_text_entry_t;

/* FontRecord */
typedef struct
{
    uint16_t font_ID;
    /* Pascal string */
    uint8_t font_name_length;
    char   *font_name;
} isom_font_record_t;

/* Font Table Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    /* FontRecord
     * entry_count is uint16_t. */
    lsmash_entry_list_t *list;
} isom_ftab_t;

/* 3GPP Timed Text Sample Entry */
typedef struct
{
    ISOM_SAMPLE_ENTRY;
    uint32_t displayFlags;
    int8_t horizontal_justification;
    int8_t vertical_justification;
    uint8_t background_color_rgba[4];
    /* BoxRecord default_text_box */
    int16_t top;
    int16_t left;
    int16_t bottom;
    int16_t right;
    /* StyleRecord default_style */
    uint16_t startChar;     /* always 0 */
    uint16_t endChar;       /* always 0 */
    uint16_t font_ID;
    uint8_t face_style_flags;
    uint8_t font_size;
    uint8_t text_color_rgba[4];
    /* Font Table Box font_table */
    isom_ftab_t *ftab;
} isom_tx3g_entry_t;

/* Sample Description Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t entry_count;   /* print only */
    lsmash_entry_list_t list;
} isom_stsd_t;
/** **/

/* Decoding Time to Sample Box
 * This box contains a compact version of a table that allows indexing from decoding time to sample number.
 * Each entry in the table gives the number of consecutive samples with the same time delta, and the delta of those samples.
 * By adding the deltas a complete time-to-sample map may be built.
 * All samples must have non-zero durations except for the last one.
 * The sum of all deltas gives the media duration in the track (not mapped to the movie timescale, and not considering any edit list).
 * DTS is an abbreviation of 'decoding time stamp'. */
typedef struct
{
    uint32_t sample_count;      /* number of consecutive samples that have the given sample_delta */
    uint32_t sample_delta;      /* DTS[0] = 0; DTS[n+1] = DTS[n] + sample_delta[n]; */
} isom_stts_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_stts_t;

/* Composition Time to Sample Box
 * This box provides the offset between decoding time and composition time.
 * CTS is an abbreviation of 'composition time stamp'.
 * This box is optional and must only be present if DTS and CTS differ for any samples. */
typedef struct
{
#define ISOM_NON_OUTPUT_SAMPLE_OFFSET 0x80000000
    uint32_t sample_count;      /* number of consecutive samples that have the given sample_offset */
    uint32_t sample_offset;     /* CTS[n] = DTS[n] + sample_offset[n];
                                 * ISOM: if version is set to 1, sample_offset is signed 32-bit integer.
                                 * QTFF: sample_offset is always signed 32-bit integer. */
} isom_ctts_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_ctts_t;

/* Composition to Decode Box (Composition Shift Least Greatest Box)
 * This box may be used to relate the composition and decoding timelines,
 * and deal with some of the ambiguities that signed composition offsets introduce. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    int32_t compositionToDTSShift;          /* If this value is added to the composition times (as calculated by the CTS offsets from the DTS),
                                             * then for all samples, their CTS is guaranteed to be greater than or equal to their DTS,
                                             * and the buffer model implied by the indicated profile/level will be honoured;
                                             * if leastDecodeToDisplayDelta is positive or zero, this field can be 0;
                                             * otherwise it should be at least (- leastDecodeToDisplayDelta). */
    int32_t leastDecodeToDisplayDelta;      /* the smallest sample_offset in this track */
    int32_t greatestDecodeToDisplayDelta;   /* the largest sample_offset in this track */
    int32_t compositionStartTime;           /* the smallest CTS for any sample */
    int32_t compositionEndTime;             /* the CTS plus the composition duration, of the sample with the largest CTS in this track */
} isom_cslg_t;

/* Sample Size Box / Compact Sample Size Box
 * This box contains the sample count and a table giving the size in bytes of each sample.
 * The total number of samples in the media within the initial movie is always indicated in the sample_count.
 * Note: a sample size of zero is not prohibited in general, but it must be valid and defined for the coding system,
 *       as defined by the sample entry, that the sample belongs to. */
typedef struct
{
    uint32_t entry_size;        /* the size of a sample */
} isom_stsz_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t sample_size;           /* the default sample size
                                     * If this field is set to 0, then the samples have different sizes. */
    uint32_t sample_count;          /* the number of samples in the media within the initial movie */
    lsmash_entry_list_t *list;      /* available if sample_size == 0 */
} isom_stsz_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    unsigned int reserved   : 24;   /* 0 */
    unsigned int field_size : 8;    /* the size in bits of the entries in the following table
                                     * It shall take the value 4, 8 or 16. If the value 4 is used, then each byte contains two values
                                     * entry[i]<<4 + entry[i+1]; if the sizes do not fill an integral number of bytes, the last byte is
                                     * padded with zero. */
    uint32_t     sample_count;      /* the number of entries in the following table */
    lsmash_entry_list_t *list;      /* L-SMASH uses isom_stsz_entry_t for its internal processes. */
} isom_stz2_t;

/* Sync Sample Box
 * If this box is not present, every sample is a random access point.
 * In AVC streams, this box cannot point non-IDR samples.
 * The table is arranged in strictly increasing order of sample number. */
typedef struct
{
    uint32_t sample_number;     /* the numbers of the samples that are random access points in the stream. */
} isom_stss_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_stss_t;

/* Partial Sync Sample Box
 * Tip from QT engineering - Open-GOP intra frames need to be marked as "partial sync samples".
 * Partial sync frames perform a partial reset of inter-frame dependencies;
 * decoding two partial sync frames and the non-droppable difference frames between them is
 * sufficient to prepare a decompressor for correctly decoding the difference frames that follow. */
typedef struct
{
    uint32_t sample_number;     /* the numbers of the samples that are partial sync samples in the stream. */
} isom_stps_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_stps_t;

/* Independent and Disposable Samples Box */
typedef struct
{
    unsigned is_leading            : 2;     /* ISOM: leading / QTFF: samples later in decode order may have earlier display times */
    unsigned sample_depends_on     : 2;     /* independency */
    unsigned sample_is_depended_on : 2;     /* disposable */
    unsigned sample_has_redundancy : 2;     /* redundancy */
} isom_sdtp_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    /* According to the specification, the size of the table, sample_count, doesn't exist in this box.
     * Instead of this, it is taken from the sample_count in the stsz or the stz2 box. */
    lsmash_entry_list_t *list;
} isom_sdtp_t;

/* Sample To Chunk Box
 * This box can be used to find the chunk that contains a sample, its position, and the associated sample description.
 * The table is compactly coded. Each entry gives the index of the first chunk of a run of chunks with the same characteristics.
 * By subtracting one entry here from the previous one, you can compute how many chunks are in this run.
 * You can convert this to a sample count by multiplying by the appropriate samples_per_chunk. */
typedef struct
{
    uint32_t first_chunk;                   /* the index of the first chunk in this run of chunks that share the same samples_per_chunk and sample_description_index */
    uint32_t samples_per_chunk;             /* the number of samples in each of these chunks */
    uint32_t sample_description_index;      /* the index of the sample entry that describes the samples in this chunk */
} isom_stsc_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_stsc_t;

/* Chunk Offset Box
 * chunk_offset is the offset of the start of a chunk into its containing media file.
 * Offsets are file offsets, not the offset into any box within the file. */
typedef struct
{
    uint32_t chunk_offset;
} isom_stco_entry_t;

typedef struct
{
    /* for large presentations */
    uint64_t chunk_offset;
} isom_co64_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;        /* type = 'stco': 32-bit chunk offsets / type = 'co64': 64-bit chunk offsets */
    lsmash_entry_list_t *list;

        uint8_t large_presentation;     /* Set 1 to this if 64-bit chunk-offset are needed. */
} isom_stco_t;      /* share with co64 box */

/* Sample Group Description Box
 * This box gives information about the characteristics of sample groups. */
typedef struct
{
    ISOM_FULLBOX_COMMON;            /* Use of version 0 entries is deprecated. */
    uint32_t grouping_type;         /* an integer that identifies the sbgp that is associated with this sample group description */
    uint32_t default_length;        /* the length of every group entry (if the length is constant), or zero (if it is variable)
                                     * This field is available only if version == 1. */
    lsmash_entry_list_t *list;
} isom_sgpd_t;

/* Random Access Entry
 * Samples marked by this group must be random access points, and may also be sync points. */
typedef struct
{
    /* grouping_type is 'rap ' */
    uint32_t description_length;                /* This field is available only if version == 1 and default_length == 0. */
    unsigned num_leading_samples_known : 1;     /* the value of one indicates that the number of leading samples is known for each sample in this group,
                                                 * and the number is specified by num_leading_samples. */
    unsigned num_leading_samples       : 7;     /* the number of leading samples for each sample in this group
                                                 * Note: when num_leading_samples_known is equal to 0, this field should be ignored. */
} isom_rap_entry_t;

/* Roll Recovery Entry
 * This grouping type is defined as that group of samples having the same roll distance. */
typedef struct
{
    /* grouping_type is 'roll' */
    uint32_t description_length;        /* This field is available only if version == 1 and default_length == 0. */
    int16_t  roll_distance;             /* the number of samples that must be decoded in order for a sample to be decoded correctly
                                         * A positive value indicates post-roll, and a negative value indicates pre-roll.
                                         * The value zero must not be used. */
} isom_roll_entry_t;

/* Sample to Group Box
 * This box is used to find the group that a sample belongs to and the associated description of that sample group. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t grouping_type;             /* Links it to its sample group description table with the same value for grouping type. */
    uint32_t grouping_type_parameter;   /* an indication of the sub-type of the grouping
                                         * This field is available only if version == 1. */
    lsmash_entry_list_t *list;
} isom_sbgp_t;

typedef struct
{
    uint32_t sample_count;                  /* the number of consecutive samples with the same sample group descriptor */
    uint32_t group_description_index;       /* the index of the sample group entry which describes the samples in this group
                                             * The index ranges from 1 to the number of sample group entries in the Sample Group Description Box,
                                             * or takes the value 0 to indicate that this sample is a member of no group of this type.
                                             * Within the Sample to Group Box in movie fragment, the group description indexes for groups defined
                                             * within the same fragment start at 0x10001, i.e. the index value 1, with the value 1 in the top 16 bits. */
} isom_group_assignment_entry_t;

/* Sample Table Box */
struct isom_stbl_tag
{
    ISOM_BASEBOX_COMMON;
    isom_stsd_t *stsd;      /* Sample Description Box */
    isom_stts_t *stts;      /* Decoding Time to Sample Box */
    isom_ctts_t *ctts;      /* Composition Time to Sample Box */
    isom_cslg_t *cslg;      /* ISOM: Composition to Decode Box / QTFF: Composition Shift Least Greatest Box */
    isom_stss_t *stss;      /* Sync Sample Box */
    isom_stps_t *stps;      /* ISOM: null / QTFF: Partial Sync Sample Box */
    isom_sdtp_t *sdtp;      /* Independent and Disposable Samples Box */
    isom_stsc_t *stsc;      /* Sample To Chunk Box */
    isom_stsz_t *stsz;      /* Sample Size Box */
    isom_stz2_t *stz2;      /* Compact Sample Size Box */
    isom_stco_t *stco;      /* Chunk Offset Box */
    lsmash_entry_list_t sgpd_list;  /* Sample Group Description Boxes */
    lsmash_entry_list_t sbgp_list;  /* Sample To Group Boxes */

        /* Use 'stz2' instead of 'stsz' if possible. (write mode only) */
        int (*compress_sample_size_table)( isom_stbl_t *stbl );
        /* Add independent and disposable info for each sample if possible. (write mode only) */
        int (*add_dependency_type)( isom_stbl_t *stbl, lsmash_file_t *file, lsmash_sample_property_t *prop );
};

/* Media Information Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    /* Media Information Header Boxes */
    isom_vmhd_t *vmhd;      /* Video Media Header Box */
    isom_smhd_t *smhd;      /* Sound Media Header Box */
    isom_hmhd_t *hmhd;      /* ISOM: Hint Media Header Box / QTFF: null */
    isom_nmhd_t *nmhd;      /* ISOM: Null Media Header Box / QTFF: null */
    isom_gmhd_t *gmhd;      /* ISOM: null / QTFF: Generic Media Information Header Box */
    /* */
    isom_hdlr_t *hdlr;      /* ISOM: null / QTFF: Data Handler Reference Box
                             * Note: this box must come before Data Information Box. */
    isom_dinf_t *dinf;      /* Data Information Box */
    isom_stbl_t *stbl;      /* Sample Table Box */
} isom_minf_t;

/* Media Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_mdhd_t *mdhd;      /* Media Header Box */
    isom_hdlr_t *hdlr;      /* ISOM: Handler Reference Box / QTFF: Media Handler Reference Box
                             * Note: this box must come before Media Information Box. */
    isom_minf_t *minf;      /* Media Information Box */
} isom_mdia_t;

/* Movie Header Box
 * This box defines overall information which is media-independent, and relevant to the entire presentation considered as a whole. */
typedef struct
{
    ISOM_FULLBOX_COMMON;            /* version is either 0 or 1 */
    /* version == 0: uint64_t -> uint32_t */
    uint64_t creation_time;         /* the creation time of the presentation (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint64_t modification_time;     /* the most recent time the presentation was modified (in seconds since midnight, Jan. 1, 1904, in UTC time) */
    uint32_t timescale;             /* movie timescale: timescale for the entire presentation */
    uint64_t duration;              /* the duration, expressed in movie timescale, of the longest track */
    /* The following fields are treated as
     * ISOM: template fields.
     * MP41: reserved fields.
     * MP42: ignored fileds since compositions are done using BIFS system.
     * 3GPP: ignored fields.
     * QTFF: usable fields. */
    int32_t  rate;                  /* fixed point 16.16 number. 0x00010000 is normal forward playback. */
    int16_t  volume;                /* fixed point 8.8 number. 0x0100 is full volume. */
    int16_t  reserved;
    int32_t  preferredLong[2];      /* ISOM: reserved / QTFF: unknown */
    int32_t  matrix[9];             /* transformation matrix for the video */
    /* The following fields are defined in QuickTime file format.
     * In ISO Base Media file format, these fields are treated as pre_defined. */
    int32_t  previewTime;           /* the time value in the movie at which the preview begins */
    int32_t  previewDuration;       /* the duration of the movie preview in movie timescale units */
    int32_t  posterTime;            /* the time value of the time of the movie poster */
    int32_t  selectionTime;         /* the time value for the start time of the current selection */
    int32_t  selectionDuration;     /* the duration of the current selection in movie timescale units */
    int32_t  currentTime;           /* the time value for current time position within the movie */
    /* */
    uint32_t next_track_ID;         /* larger than the largest track-ID in use */
} isom_mvhd_t;

/* Object Descriptor Box
 * Note that this box is mandatory under 14496-1:2001 (mp41) while not mandatory under 14496-14:2003 (mp42). */
struct mp4sys_ObjectDescriptor_t; /* FIXME: I think these structs using mp4sys should be placed in isom.c */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    struct mp4sys_ObjectDescriptor_t *OD;
} isom_iods_t;

/* Media Data Box
 * This box contains the media data.
 * A presentation may contain zero or more Media Data Boxes.*/
typedef struct
{
    ISOM_BASEBOX_COMMON;    /* If size is 0, then this box is the last box. */

        uint64_t media_size;    /* the total media size already written in this box */
        uint64_t reserved_size; /* the reserved total media size in this box
                                 * If 'media_size' > 'reserved_size' occurs when finishing a non-fragmented movie,
                                 * rewrite the size of this box. */
} isom_mdat_t;

/* Free Space Box
 * The contents of a free-space box are irrelevant and may be ignored without affecting the presentation. */
typedef struct
{
    ISOM_BASEBOX_COMMON;    /* type is 'free' or 'skip' */
    uint32_t length;
    uint8_t *data;
} isom_free_t;

typedef isom_free_t isom_skip_t;

/* Chapter List Box
 * This box is NOT defined in the ISO/MPEG-4 specs.
 * Basically, this box exists in User Data Box inside Movie Box if present. */
typedef struct
{
    uint64_t start_time;    /* version = 0: expressed in movie timescale units
                             * version = 1: expressed in 100 nanoseconds */
    /* Chapter name is Pascal string */
    uint8_t chapter_name_length;
    char *chapter_name;
} isom_chpl_entry_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;            /* version = 0 is defined in F4V file format. */
    uint8_t unknown;                /* only available under version = 1 */
    lsmash_entry_list_t *list;      /* if version is set to 0, entry_count is uint8_t. */
} isom_chpl_t;

typedef struct
{
    char *chapter_name;
    uint64_t start_time;
} isom_chapter_entry_t;

/* Metadata Item Keys Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    lsmash_entry_list_t *list;
} isom_keys_t;

typedef struct
{
    uint32_t key_size;          /* the size of the entire structure containing a key definition
                                 * key_size = sizeof(key_size) + sizeof(key_namespace) + sizeof(key_value) */
    uint32_t key_namespace;     /* a naming scheme used for metadata keys
                                 * Location metadata keys, for example, use the 'mdta' key namespace. */
    uint8_t *key_value;         /* the actual name of the metadata key
                                 * Keys with the 'mdta' namespace use a reverse DNS naming convention. */
} isom_keys_entry_t;

/* Meaning Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint8_t *meaning_string;        /* to fill the box */

        uint32_t meaning_string_length;
} isom_mean_t;

/* Name Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint8_t *name;      /* to fill the box */

        uint32_t name_length;
} isom_name_t;

/* Data Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    /* type indicator */
    uint16_t reserved;              /* always 0 */
    uint8_t  type_set_identifier;   /* 0: type set of the common basic data types */
    uint8_t  type_code;             /* type of data code */
    /* */
    uint32_t the_locale;            /* reserved to be 0 */
    uint8_t *value;                 /* to fill the box */

        uint32_t value_length;
} isom_data_t;

/* Metadata Item Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_mean_t *mean;      /* Meaning Box */
    isom_name_t *name;      /* Name Box */
    isom_data_t *data;      /* Data Box */
} isom_metaitem_t;

/* Metadata Item List Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    lsmash_entry_list_t metaitem_list;  /* Metadata Item Box List
                                         * There is no entry_count field. */
} isom_ilst_t;

/* Meta Box */
typedef struct
{
    ISOM_FULLBOX_COMMON;    /* ISOM: FullBox / QTFF: BaseBox */
    isom_hdlr_t *hdlr;      /* Metadata Handler Reference Box */
    isom_dinf_t *dinf;      /* ISOM: Data Information Box / QTFF: null */
    isom_keys_t *keys;      /* ISOM: null / QTFF: Metadata Item Keys Box */
    isom_ilst_t *ilst;      /* Metadata Item List Box only defined in Apple MPEG-4 and QTFF */
} isom_meta_t;

/* Window Location Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    /* default window location for movie */
    uint16_t x;
    uint16_t y;
} isom_WLOC_t;

/* Looping Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t looping_mode;      /* 0 for none, 1 for looping, 2 for palindromic looping */
} isom_LOOP_t;

/* Play Selection Only Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint8_t selection_only;     /* whether only the selected area of the movie should be played */
} isom_SelO_t;

/* Play All Frames Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint8_t play_all_frames;    /* whether all frames of video should be played, regardless of timing */
} isom_AllF_t;

/* Copyright Box
 * The Copyright box contains a copyright declaration which applies to the entire presentation,
 * when contained within the Movie Box, or, when contained in a track, to that entire track.
 * There may be multiple copyright boxes using different language codes. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint16_t language;              /* ISO-639-2/T language codes. Most significant 1-bit is 0.
                                     * Each character is packed as the difference between its ASCII value and 0x60. */
    uint8_t *notice;                /* a null-terminated string in either UTF-8 or UTF-16 characters, giving a copyright notice.
                                     * If UTF-16 is used, the string shall start with the BYTE ORDER MARK (0xFEFF), to distinguish it from a UTF-8 string.
                                     * This mark does not form part of the final string. */
        uint32_t notice_length;
} isom_cprt_t;

/* Movie SDP Information box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint32_t descriptionformat;
    uint8_t *sdptext;
    uint32_t sdp_length;
}isom_rtp_t;

/* Track SDP Information box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    uint8_t *sdptext;
    uint32_t sdp_length;
}isom_sdp_t;

typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_rtp_t *rtp;      /* Movie-level SDP box*/
    isom_sdp_t *sdp;      /* Track-level SDP box*/
} isom_hnti_t;

/* User Data Box
 * This box is a container box for informative user-data.
 * This user data is formatted as a set of boxes with more specific box types, which declare more precisely their content.
 * QTFF: for historical reasons, this box is optionally terminated by a 32-bit integer set to 0. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_chpl_t *chpl;      /* Chapter List Box */
    isom_meta_t *meta;      /* Meta Box extended by Apple for iTunes movie */
    /* QuickTime user data */
    isom_WLOC_t *WLOC;      /* Window Location Box */
    isom_LOOP_t *LOOP;      /* Looping Box */
    isom_SelO_t *SelO;      /* Play Selection Only Box */
    isom_AllF_t *AllF;      /* Play All Frames Box */
    /* Copyright Box List */
    lsmash_entry_list_t cprt_list;  /* Copyright Boxes is defined in ISO Base Media and 3GPP file format */
    /* Hint information box */
    isom_hnti_t *hnti;
} isom_udta_t;

/** Caches for handling tracks **/
typedef struct
{
    uint64_t alloc;             /* total buffer size for the pool */
    uint64_t size;              /* total size of samples in the pool */
    uint32_t sample_count;      /* number of samples in the pool */
    uint8_t *data;              /* actual data of samples in the pool */
} isom_sample_pool_t;

typedef struct
{
    uint32_t chunk_number;                  /* chunk number */
    uint32_t sample_description_index;      /* sample description index */
    uint64_t first_dts;                     /* the first DTS in chunk */
    isom_sample_pool_t *pool;               /* samples pooled to interleave */
} isom_chunk_t;

typedef struct
{
    uint64_t dts;
    uint64_t cts;
    int32_t  ctd_shift;
} isom_timestamp_t;

typedef struct
{
    isom_group_assignment_entry_t *assignment;          /* the address corresponding to the entry in Sample to Group Box */
    isom_group_assignment_entry_t *prev_assignment;     /* the address of the previous assignment */
    isom_rap_entry_t              *random_access;       /* the address corresponding to the random access entry in Sample Group Description Box */
    uint8_t                        is_prev_rap;         /* whether the previous sample is a random access point or not */
} isom_rap_group_t;

typedef struct
{
    isom_group_assignment_entry_t *assignment;      /* the address corresponding to the entry in Sample to Group Box */
    isom_sgpd_t                   *sgpd;            /* the address to the active Sample Group Description Box */
    uint32_t first_sample;                          /* the number of the first sample of the group */
    uint32_t recovery_point;                        /* the identifier necessary for the recovery from its starting point to be completed */
    uint64_t rp_cts;                                /* the CTS of the recovery point */
    int16_t  roll_distance;                         /* the current roll_distance
                                                     * The value may be updated when 'described' is set to ROLL_DISTANCE_INITIALIZED. */
#define MAX_ROLL_WAIT_AND_SEE_COUNT 64
    uint8_t  wait_and_see_count;                    /* Wait-and-see after initialization of roll_distance until reaching MAX_ROLL_WAIT_AND_SEE. */
    uint8_t  is_fragment;                           /* the flag if the current group is in fragment */
    uint8_t  prev_is_recovery_start;                /* whether the previous sample is a starting point of recovery or not */
    uint8_t  delimited;                             /* the flag if the sample_count is determined */
#define ROLL_DISTANCE_INITIALIZED 1
#define ROLL_DISTANCE_DETERMINED  2
    uint8_t  described;                             /* the status of the group description */
} isom_roll_group_t;

typedef struct
{
    lsmash_entry_list_t *pool;  /* grouping pooled to delimit and describe */
} isom_grouping_t;

typedef struct
{
    uint64_t segment_duration;     /* the sum of the subsegment_duration of preceeding subsegments */
    uint64_t largest_cts;          /* the largest CTS of a subsegment of the reference stream */
    uint64_t smallest_cts;         /* the smallest CTS of a subsegment of the reference stream */
    uint64_t first_sample_cts;     /* the CTS of the first sample of a subsegment of the reference stream  */
    /* SAP related info within the active subsegment of the reference stream */
    uint64_t                  first_ed_cts;     /* the earliest CTS of decodable samples after the first recovery point */
    uint64_t                  first_rp_cts;     /* the CTS of the first recovery point */
    uint32_t                  first_rp_number;  /* the number of the first recovery point */
    uint32_t                  first_ra_number;  /* the number of the first random accessible sample */
    lsmash_random_access_flag first_ra_flags;   /* the flags of the first random accessible sample */
    int                       is_first_recovery_point;
    int                       decodable;
} isom_subsegment_t;

typedef struct
{
    uint8_t           has_samples;          /* Whether whole movie has any sample or not. */
    uint8_t           roll_grouping;
    uint8_t           rap_grouping;
    uint32_t          traf_number;
    uint32_t          last_duration;        /* the last sample duration in this track fragment */
    uint64_t          largest_cts;          /* the largest CTS in this track fragment */
    uint32_t          sample_count;         /* the number of samples in this track fragment */
    uint32_t          output_sample_count;  /* the number of output samples in this track fragment */
    isom_subsegment_t subsegment;
} isom_fragment_t;

typedef struct
{
    uint8_t           all_sync;     /* if all samples are sync sample */
    uint8_t           is_audio;
    isom_chunk_t      chunk;
    isom_timestamp_t  timestamp;    /* Each field stores the last valid value. */
    isom_grouping_t   roll;
    isom_rap_group_t *rap;
    isom_fragment_t  *fragment;
} isom_cache_t;

/** Movie Fragments Boxes **/
/* Track Fragments Flags ('tf_flags') */
typedef enum
{
    ISOM_TF_FLAGS_BASE_DATA_OFFSET_PRESENT               = 0x000001,    /* base-data-offset-present:
                                                                         * This flag indicates the presence of the base_data_offset field.
                                                                         * The base_data_offset is the base offset to use when calculating data offsets.
                                                                         * Offsets are file offsets as like as chunk_offset in Chunk Offset Box.
                                                                         * If this flag is set and default-base-is-moof is not set, the base_data_offset
                                                                         * for the first track in the movie fragment is the position of the first byte
                                                                         * of the enclosing Movie Fragment Box, and for second and subsequent track
                                                                         * fragments, the default is the end of the data defined by the preceding fragment. */
    ISOM_TF_FLAGS_SAMPLE_DESCRIPTION_INDEX_PRESENT       = 0x000002,    /* sample-description-index-present
                                                                         * This flag indicates the presence of the sample_description_index field. */
    ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT        = 0x000008,    /* default-sample-duration-present:
                                                                         * This flag indicates the presence of the default_sample_duration field. */
    ISOM_TF_FLAGS_DEFAULT_SAMPLE_SIZE_PRESENT            = 0x000010,    /* default-sample-size-present:
                                                                         * This flag indicates the presence of the default_sample_size field. */
    ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT           = 0x000020,    /* default-sample-flags-present:
                                                                         * This flag indicates the presence of the default_sample_flags field. */
    ISOM_TF_FLAGS_DURATION_IS_EMPTY                      = 0x010000,    /* duration-is-empty:
                                                                         * This flag indicates there are no samples for this time interval. */
    ISOM_TF_FLAGS_DEFAULT_BASE_IS_MOOF                   = 0x020000,    /* default-base-is-moof:
                                                                         * If base-data-offset-present is not set, this flag indicates the implicit
                                                                         * base_data_offset is always equal to the position of the first byte of the
                                                                         * enclosing Movie Fragment BOX.
                                                                         * This flag is only available under the 'iso5' or later brands and cannot be set
                                                                         * when earlier brands are included in the File Type box. */
} isom_tf_flags_code;

/* Track Run Flags ('tr_flags') */
typedef enum
{
    ISOM_TR_FLAGS_DATA_OFFSET_PRESENT                    = 0x000001,    /* data-offset-present:
                                                                         * This flag indicates the presence of the data_offset field. */
    ISOM_TR_FLAGS_FIRST_SAMPLE_FLAGS_PRESENT             = 0x000004,    /* first-sample-flags-present:
                                                                         * This flag indicates the presence of the first_sample_flags field. */
    ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT                = 0x000100,    /* sample-duration-present:
                                                                         * This flag indicates the presence of the sample_duration field. */
    ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT                    = 0x000200,    /* sample-size-present:
                                                                         * This flag indicates the presence of the sample_size field. */
    ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT                   = 0x000400,    /* sample-flags-present:
                                                                         * This flag indicates the presence of the sample_flags field. */
    ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT = 0x000800,    /* sample-composition-time-offsets-present:
                                                                         * This flag indicates the presence of the sample_composition_time_offset field. */
} isom_tr_flags_code;

/* Sample Flags */
typedef struct
{
    unsigned reserved                  : 4;
    /* The definition of the following fields is quite the same as Independent and Disposable Samples Box. */
    unsigned is_leading                : 2;
    unsigned sample_depends_on         : 2;
    unsigned sample_is_depended_on     : 2;
    unsigned sample_has_redundancy     : 2;
    /* */
    unsigned sample_padding_value      : 3;     /* the number of bits at the end of this sample */
    unsigned sample_is_non_sync_sample : 1;     /* 0 value means this sample is sync sample. */
    uint16_t sample_degradation_priority;
} isom_sample_flags_t;

/* Movie Extends Header Box
 * This box is omitted when used in live streaming.
 * If this box is not present, the overall duration must be computed by examining each fragment. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    /* version == 0: uint64_t -> uint32_t */
    uint64_t fragment_duration;     /* the duration of the longest track, in the timescale indicated in the Movie Header Box, including movie fragments. */
} isom_mehd_t;

/* Track Extends Box
 * This box sets up default values used by the movie fragments. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t            track_ID;       /* identifier of the track; this shall be the track ID of a track in the Movie Box */
    uint32_t            default_sample_description_index;
    uint32_t            default_sample_duration;
    uint32_t            default_sample_size;
    isom_sample_flags_t default_sample_flags;
} isom_trex_t;

/* Movie Extends Box
 * This box warns readers that there might be Movie Fragment Boxes in this file. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_mehd_t         *mehd;          /* Movie Extends Header Box / omitted when used in live streaming */
    lsmash_entry_list_t  trex_list;     /* Track Extends Box */
} isom_mvex_t;

/* Movie Fragment Header Box
 * This box contains a sequence number, as a safety check.
 * The sequence number 'usually' starts at 1 and must increase for each movie fragment in the file, in the order in which they occur. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t sequence_number;       /* the ordinal number of this fragment, in increasing order */
} isom_mfhd_t;

/* Track Fragment Header Box
 * Each movie fragment can contain zero or more fragments for each track;
 * and a track fragment can contain zero or more contiguous runs of samples.
 * This box sets up information and defaults used for those runs of samples. */
typedef struct
{
    ISOM_FULLBOX_COMMON;                            /* flags field is used for 'tf_flags'. */
    uint32_t            track_ID;
    /* all the following are optional fields */
    uint64_t            base_data_offset;           /* an explicit anchor for the data offsets in each track run
                                                     * To avoid the case this field might overflow, e.g. semi-permanent live streaming and broadcasting,
                                                     * you shall not use this optional field. */
    uint32_t            sample_description_index;   /* override default_sample_description_index in Track Extends Box */
    uint32_t            default_sample_duration;    /* override default_sample_duration in Track Extends Box */
    uint32_t            default_sample_size;        /* override default_sample_size in Track Extends Box */
    isom_sample_flags_t default_sample_flags;       /* override default_sample_flags in Track Extends Box */
} isom_tfhd_t;

/* Track Fragment Base Media Decode Time Box
 * This box provides the absolute decode time, measured on the media timeline, of the first sample in decode order in the track fragment.
 * This can be useful, for example, when performing random access in a file;
 * it is not necessary to sum the sample durations of all preceding samples in previous fragments to find this value
 * (where the sample durations are the deltas in the Decoding Time to Sample Box and the sample_durations in the preceding track runs).
 * This box, if present, shall be positioned after the Track Fragment Header Box and before the first Track Fragment Run box. */
typedef struct
{
    ISOM_FULLBOX_COMMON;    /* version is either 0 or 1 */
    /* version == 0: 64bits -> 32bits */
    uint64_t baseMediaDecodeTime;   /* an integer equal to the sum of the decode durations of all earlier samples in the media, expressed in the media's timescale
                                     * It does not include the samples added in the enclosing track fragment.
                                     * NOTE: the decode timeline is a media timeline, established before any explicit or implied mapping of media time to presentation time,
                                     *       for example by an edit list or similar structure. */
} isom_tfdt_t;

/* Track Fragment Run Box
 * Within the Track Fragment Box, there are zero or more Track Fragment Run Boxes.
 * If the duration-is-empty flag is set in the tf_flags, there are no track runs.
 * A track run documents a contiguous set of samples for a track. */
typedef struct
{
    ISOM_FULLBOX_COMMON;                        /* flags field is used for 'tr_flags'. */
    uint32_t            sample_count;           /* the number of samples being added in this run; also the number of rows in the following table */
    /* The following are optional fields. */
    int32_t             data_offset;            /* This value is added to the implicit or explicit data_offset established in the Track Fragment Header Box.
                                                 * If this field is not present, then the data for this run starts immediately after the data of the previous run,
                                                 * or at the base_data_offset defined by the Track Fragment Header Box if this is the first run in a track fragment. */
    isom_sample_flags_t first_sample_flags;     /* a set of flags for the first sample only of this run */
    lsmash_entry_list_t *optional;              /* all fields in this array are optional. */
} isom_trun_t;

typedef struct
{
    /* If the following fields is present, each field overrides default value described in Track Fragment Header Box or Track Extends Box. */
    uint32_t            sample_duration;                    /* override default_sample_duration */
    uint32_t            sample_size;                        /* override default_sample_size */
    isom_sample_flags_t sample_flags;                       /* override default_sample_flags */
    /* */
    uint32_t            sample_composition_time_offset;     /* composition time offset
                                                             *   If version == 0, unsigned 32-bit integer.
                                                             *   Otherwise, signed 32-bit integer. */
} isom_trun_optional_row_t;

/* Track Fragment Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_tfhd_t         *tfhd;          /* Track Fragment Header Box */
    isom_tfdt_t         *tfdt;          /* Track Fragment Base Media Decode Time Box */
    lsmash_entry_list_t  trun_list;     /* Track Fragment Run Box List
                                         * If the duration-is-empty flag is set in the tf_flags, there are no track runs. */
    isom_sdtp_t         *sdtp;          /* Independent and Disposable Samples Box (available under Protected Interoperable File Format) */
    lsmash_entry_list_t  sgpd_list;     /* Sample Group Description Boxes (available under ISO Base Media version 6 or later) */
    lsmash_entry_list_t  sbgp_list;     /* Sample To Group Boxes */

        isom_cache_t *cache;            /* taken over from corresponding 'trak' */
} isom_traf_t;

/* Movie Fragment Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_mfhd_t         *mfhd;          /* Movie Fragment Header Box */
    lsmash_entry_list_t  traf_list;     /* Track Fragment Box List */
} isom_moof_t;

/* Track Fragment Random Access Box
 * Each entry in this box contains the location and the presentation time of the sync sample.
 * Note that not every sync sample in the track needs to be listed in the table.
 * The absence of this box does not mean that all the samples are sync samples. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t track_ID;
    unsigned int reserved                  : 26;
    unsigned int length_size_of_traf_num   : 2;     /* the length in byte of the traf_number field minus one */
    unsigned int length_size_of_trun_num   : 2;     /* the length in byte of the trun_number field minus one */
    unsigned int length_size_of_sample_num : 2;     /* the length in byte of the sample_number field minus one */
    uint32_t number_of_entry;                       /* the number of the entries for this track
                                                     * Value zero indicates that every sample is a sync sample and no table entry follows. */
    lsmash_entry_list_t *list;                      /* entry_count corresponds to number_of_entry. */
} isom_tfra_t;

typedef struct
{
    /* version == 0: 64bits -> 32bits */
    uint64_t time;              /* the presentation time of the sync sample in units defined in the Media Header Box of the associated track
                                 * For segments based on movie sample tables or movie fragments, presentation times are in the movie timeline,
                                 * that is they are composition times after the application of any edit list for the track.
                                 * Note: the definition of segment is portion of an ISO base media file format file, consisting of either
                                 *       (a) a movie box, with its associated media data (if any) and other associated boxes
                                 *        or
                                 *       (b) one or more movie fragment boxes, with their associated media data, and other associated boxes. */
    uint64_t moof_offset;       /* the offset of the Movie Fragment Box used in this entry
                                 * Offset is the byte-offset between the beginning of the file and the beginning of the Movie Fragment Box. */
    /* */
    uint32_t traf_number;       /* the Track Fragment Box ('traf') number that contains the sync sample
                                 * The number ranges from 1 in each Movie Fragment Box ('moof'). */
    uint32_t trun_number;       /* the Track Fragment Run Box ('trun') number that contains the sync sample
                                 * The number ranges from 1 in each Track Fragment Box ('traf'). */
    uint32_t sample_number;     /* the sample number that contains the sync sample
                                 * The number ranges from 1 in each Track Fragment Run Box ('trun'). */
} isom_tfra_location_time_entry_t;

/* Movie Fragment Random Access Offset Box
 * This box provides a copy of the length field from the enclosing Movie Fragment Random Access Box. */
typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t length;        /* an integer gives the number of bytes of the enclosing Movie Fragment Random Access Box
                             * This field is placed at the last of the enclosing box to assist readers scanning
                             * from the end of the file in finding the Movie Fragment Random Access Box. */
} isom_mfro_t;

/* Movie Fragment Random Access Box
 * This box provides a table which may assist readers in finding sync samples in a file using movie fragments,
 * and is usually placed at or near the end of the file.
 * The last box within the Movie Fragment Random Access Box, which is called Movie Fragment Random Access Offset Box,
 * provides a copy of the length field from the Movie Fragment Random Access Box. */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    lsmash_entry_list_t  tfra_list;     /* Track Fragment Random Access Box */
    isom_mfro_t         *mfro;          /* Movie Fragment Random Access Offset Box */
} isom_mfra_t;

/* Movie fragment manager
 * The presence of this means we use the structure of movie fragments. */
typedef struct
{
#define FIRST_MOOF_POS_UNDETERMINED UINT64_MAX
    isom_moof_t         *movie;             /* the address corresponding to the current Movie Fragment Box */
    uint64_t             first_moof_pos;
    uint64_t             pool_size;         /* the total sample size in the current movie fragment */
    uint64_t             sample_count;      /* the number of samples within the current movie fragment */
    lsmash_entry_list_t *pool;              /* samples pooled to interleave for the current movie fragment */
} isom_fragment_manager_t;

/** **/

/* Track Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_tkhd_t *tkhd;          /* Track Header Box */
    isom_tapt_t *tapt;          /* ISOM: null / QTFF: Track Aperture Mode Dimensions Box */
    isom_edts_t *edts;          /* Edit Box */
    isom_tref_t *tref;          /* Track Reference Box */
    isom_mdia_t *mdia;          /* Media Box */
    isom_udta_t *udta;          /* User Data Box */
    isom_meta_t *meta;          /* Meta Box */

        isom_cache_t *cache;
        uint32_t      related_track_ID;
        uint8_t       is_chapter;
} isom_trak_t;

/* Movie Box */
typedef struct
{
    ISOM_BASEBOX_COMMON;
    isom_mvhd_t         *mvhd;          /* Movie Header Box */
    isom_iods_t         *iods;          /* MP4: Object Descriptor Box */
    lsmash_entry_list_t  trak_list;     /* Track Box List */
    isom_udta_t         *udta;          /* User Data Box */
    isom_ctab_t         *ctab;          /* ISOM: null / QTFF: Color Table Box */
    isom_meta_t         *meta;          /* Meta Box */
    isom_mvex_t         *mvex;          /* Movie Extends Box */
} isom_moov_t;

/** Segments
 * segment
 *   portion of an ISO base media file format file, consisting of either (a) a movie box, with its associated media data
 *   (if any) and other associated boxes or (b) one or more movie fragment boxes, with their associated media data, and
 *   and other associated boxes
 * subsegment
 *   time interval of a segment formed from movie fragment boxes, that is also a valid segment
 *     A subsegment is defined as a time interval of the containing (sub)segment, and corresponds to a single range of
 *     bytes of the containing (sub)segment. The durations of all the subsegments sum to the duration of the containing
 *     (sub)segment.
 **/
/* Segment Type Box
 * Media presentations may be divided into segments for delivery, for example, it is possible (e.g. in HTTP streaming) to
 * form files that contain a segment ? or concatenated segments ? which would not necessarily form ISO Base Media file
 * format compliant files (e.g. they do not contain a Movie Box).
 * If segments are stored in separate files (e.g. on a standard HTTP server) it is recommended that these 'segment files'
 * contain a Segment Type Box, which must be first if present, to enable identification of those files, and declaration of
 * the specifications with which they are compliant.
 * Segment Type Boxes that are not first in a file may be ignored.
 * Valid Segment Type Boxes shall be the first box in a segment.
 * Note:
 *   The 'valid' here does not always mean that any brand of that segment has compatibility against other brands of it.
 *   After concatenations of segments, the result file might contain incompatibilities among brands. */
typedef isom_ftyp_t isom_styp_t;

/* Segment Index Box
 * This box provides a compact index of one media stream within the media segment to which it applies.
 *
 * Each Segment Index Box documents how a (sub)segment is divided into one or more subsegments (which may themselves be
 * further subdivided using Segment Index boxes).
 *
 * Each entry in the Segment Index Box contains a reference type that indicates whether the reference points directly to
 * the media bytes of a referenced leaf subsegment, which is a subsegment that does not contain any indexing information
 * that would enable its further division into subsegments, or to a Segment Index box that describes how the referenced
 * subsegment is further subdivided; as a result, the segment may be indexed in a 'hierarchical' or 'daisy-chain' or
 * other form by documenting time and byte offset information for other Segment Index Boxes applying to portions of the
 * same (sub)segment.
 *
 * For segments based on ISO Base Media file format (i.e. based on movie sample tables or movie fragments):
 *   ! an access unit is a sample;
 *   ! a subsegment is a self-contained set of one or more consecutive movie fragments; a self-contained set contains
 *     one or more Movie Fragment Boxes with the corresponding Media Data Box(es), and a Media Data Box containing data
 *     referenced by a Movie Fragment Box must follow that Movie Fragment Box and precede the next Movie Fragment box
 *     containing information about the same track;
 *   ! Segment Index Boxes shall be placed before subsegment material they document, that is, before any Movie Fragment
 *     Box of the documented material of the subsegment;
 *   ! streams are tracks in the file format, and stream IDs are track IDs;
 *   ! a subsegment contains a stream access point if a track fragment within the subsegment for the track with track_ID
 *     equal to reference_ID contains a stream access point;
 *   ! initialisation data for SAPs consists of the Movie Box;
 *   ! presentation times are in the movie timeline, that is they are composition times after the application of any edit
 *     list for the track;
 *   ! the ISAP is a position exactly pointing to the start of a top-level box, such as a Movie Fragment Box;
 *   ! a SAP of type 1 or type 2 is indicated as a sync sample;
 *   ! a SAP of type 3 is marked as a member of a sample group of type 'rap ';
 *   ! a SAP of type 4 is marked as a member of a sample group of type 'roll' where the value of the roll_distance field
 *     is greater than 0.
 *   For SAPs of type 5 and 6, no specific signalling in the ISO Base Media file format is supported. */
typedef struct
{
    unsigned int reference_type  : 1;   /* 1: the reference is to a Segment Index Box
                                         * 0: the reference is to media content
                                         *      For files based on the ISO Base Media file format, the reference is to a
                                         *      Movie Fragment Box.
                                         *   If a separate index segment is used, then entries with reference type 1 are
                                         *   in the index segment, and entries with reference type 0 are in the media file. */
    unsigned int reference_size  : 31;  /* the distance in bytes from the first byte of the referenced item to the first
                                         * byte of the next referenced item, or in the case of the last entry, the end of
                                         * the referenced material */
    uint32_t     subsegment_duration;   /* when the reference is to Segment Index Box, i.e. reference_type is equal to 1:
                                         *   this field carries the sum of the subsegment_duration fields in that box;
                                         * when the reference is to a subsegment:
                                         *   this field carries the difference between the earliest presentation time of
                                         *   any access unit of the reference stream in the next subsegment (or the first
                                         *   subsegment of the next segment, if this is the last subsegment of the segment,
                                         *   or the end presentation time of the reference stream if this is the last
                                         *   subsegment of the stream) and the earliest presentation time of any access
                                         *   unit of the reference stream in the referenced subsegment;
                                         * The duration is expressed in the timescale of the enclosing Segment Index Box. */
    unsigned int starts_with_SAP : 1;   /* whether the referenced subsegments start with a SAP */
    unsigned int SAP_type        : 3;   /* a SAP type or the value 0
                                         *   When starting with a SAP, the value 0 means a SAP may be of an unknown type.
                                         *   Otherwise, the value 0 means no information of SAPs is provided. */
    unsigned int SAP_delta_time  : 28;  /* TSAP of the first SAP, in decoding order, in the referenced subsegment for
                                         * the reference stream
                                         *   If the referenced subsegments do not contain a SAP, SAP_delta_time is
                                         *   reserved with the value 0, otherwise SAP_delta_time is the difference between
                                         *   the earliest presentation time of the subsegment, and the TSAP.
                                         *   Note that this difference may be zero, in the case that the subsegment starts
                                         *   with a SAP. */
} isom_sidx_referenced_item_t;

typedef struct
{
    ISOM_FULLBOX_COMMON;
    uint32_t reference_ID;      /* the stream ID for the reference stream
                                 *   If this Segment Index box is referenced from a "parent" Segment Index box, the value
                                 *   of the value of reference_ID shall be the same as the value of reference_ID of the
                                 *   "parent" Segment Index Box. */
    uint32_t timescale;         /* the timescale, in ticks per second, for the time and duration fields within this box
                                 *   It is recommended that this match the timescale of the reference stream or track.
                                 *   For files based on the ISO Base Media file format, that is the timescale field of
                                 *   the Media Header Box of the track. */
    /* version == 0: 64bits -> 32bits */
    uint64_t earliest_presentation_time;    /* the earliest presentation time of any access unit in the reference stream
                                             * in the first subsegment, in the timescale indicated in the timescale field */
    uint64_t first_offset;                  /* the distance in bytes, in the file containing media, from the anchor point,
                                             * to the first byte of the indexed material */
    /* */
    uint16_t reserved;          /* 0 */
    uint16_t reference_count;   /* the number of referenced items */
    lsmash_entry_list_t *list;  /* entry_count corresponds to reference_count. */
} isom_sidx_t;

/** **/

/* File */
struct lsmash_file_tag
{
    ISOM_FULLBOX_COMMON;                /* The 'size' field indicates total file size.
                                         * The 'flags' field indicates file mode. */
    isom_ftyp_t         *ftyp;          /* File Type Box */
    lsmash_entry_list_t  styp_list;     /* Segment Type Box List */
    isom_moov_t         *moov;          /* Movie Box */
    lsmash_entry_list_t  sidx_list;     /* Segment Index Box List */
    lsmash_entry_list_t  moof_list;     /* Movie Fragment Box List */
    isom_mdat_t         *mdat;          /* Media Data Box */
    isom_meta_t         *meta;          /* Meta Box */
    isom_mfra_t         *mfra;          /* Movie Fragment Random Access Box */

        lsmash_bs_t             *bs;        /* bytestream manager */
        isom_fragment_manager_t *fragment;  /* movie fragment manager */
        lsmash_entry_list_t     *print;
        lsmash_entry_list_t     *timeline;
        lsmash_file_t           *initializer;   /* A file containing the initialization information of whole movie including subsequent segments
                                                 * For ISOBMFF, an initializer corresponds to a file containing the 'moov' box.
                                                 * ROOT-to-initializer is designed to be a one-to-one relationship while initializer-to-file
                                                 * is designed to be a one-to-many relationship. */
        struct importer_tag     *importer;      /* An importer of this file
                                                 * Importer-to-file is designed to be a one-to-one relationship. */
        uint64_t  fragment_count;           /* the number of movie fragments we created */
        double    max_chunk_duration;       /* max duration per chunk in seconds */
        double    max_async_tolerance;      /* max tolerance, in seconds, for amount of interleaving asynchronization between tracks */
        uint64_t  max_chunk_size;           /* max size per chunk in bytes. */
        uint32_t  brand_count;
        uint32_t *compatible_brands;        /* the backup of the compatible brands in the File Type Box or the valid Segment Type Box */
        uint8_t   fake_file_mode;           /* If set to 1, the bytestream manager handles fake-file stream. */
        /* flags for compatibility */
#define COMPAT_FLAGS_OFFSET offsetof( lsmash_file_t, qt_compatible )
        uint8_t qt_compatible;              /* compatibility with QuickTime file format */
        uint8_t isom_compatible;            /* compatibility with ISO Base Media file format */
        uint8_t avc_extensions;             /* compatibility with AVC extensions */
        uint8_t mp4_version1;               /* compatibility with MP4 ver.1 file format */
        uint8_t mp4_version2;               /* compatibility with MP4 ver.2 file format */
        uint8_t itunes_movie;               /* compatibility with iTunes Movie */
        uint8_t max_3gpp_version;           /* maximum 3GPP version */
        uint8_t max_isom_version;           /* maximum ISO Base Media file format version */
        uint8_t min_isom_version;           /* minimum ISO Base Media file format version */
        uint8_t forbid_tref;                /* If set to 1, track reference is forbidden. */
        uint8_t undefined_64_ver;           /* If set to 1, 64-bit version fields, e.g. duration, are undefined. */
        uint8_t allow_moof_base;            /* If set to 1, default-base-is-moof is available for muxing. */
        uint8_t media_segment;              /* If set to 1, this file is a media segment. */
};

/* fake-file stream */
typedef struct
{
    uint32_t size;
    uint8_t *data;
    uint32_t pos;
} fake_file_stream_t;

/* ROOT */
struct lsmash_root_tag
{
    ISOM_FULLBOX_COMMON;                    /* The 'file' field contains the address of the current active file. */
    lsmash_entry_list_t file_abstract_list; /* the list of all files the ROOT contains */
};

/** **/

/* Pre-defined precedence */
#define LSMASH_BOX_PRECEDENCE_ISOM_FTYP (LSMASH_BOX_PRECEDENCE_H  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STYP (LSMASH_BOX_PRECEDENCE_H  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SIDX (LSMASH_BOX_PRECEDENCE_N  +  1 * LSMASH_BOX_PRECEDENCE_S)   /* shall be placed before any 'moof' of the documented subsegments */
#define LSMASH_BOX_PRECEDENCE_ISOM_MOOV (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MVHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_IODS (LSMASH_BOX_PRECEDENCE_HM -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TRAK (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TKHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_TAPT (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_CLEF (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_PROF (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_ENOF (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_EDTS (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_ELST (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TREF (LSMASH_BOX_PRECEDENCE_N  -  3 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TREF_TYPE (LSMASH_BOX_PRECEDENCE_N - 0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MDIA (LSMASH_BOX_PRECEDENCE_N  -  4 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MDHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_HDLR (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MINF (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_VMHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SMHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_HMHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_NMHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_GMHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_GMIN (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_TEXT (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_DINF (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_DREF (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_DREF_ENTRY (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STBL (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STSD (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_GLBL (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_ESDS (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_ESDS (LSMASH_BOX_PRECEDENCE_HM -  1 * LSMASH_BOX_PRECEDENCE_S)   /* preceded by 'frma' and 'mp4a' */
#define LSMASH_BOX_PRECEDENCE_ISOM_BTRT (LSMASH_BOX_PRECEDENCE_HM -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TIMS (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TSRO (LSMASH_BOX_PRECEDENCE_HM -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TSSY (LSMASH_BOX_PRECEDENCE_HM -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_COLR (LSMASH_BOX_PRECEDENCE_LP +  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_COLR (LSMASH_BOX_PRECEDENCE_LP +  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_GAMA (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_FIEL (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_CLLI (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_MDCV (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_CSPC (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_SGBT (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)   /* 'v216' specific */
#define LSMASH_BOX_PRECEDENCE_ISOM_CLAP (LSMASH_BOX_PRECEDENCE_LP +  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_PASP (LSMASH_BOX_PRECEDENCE_LP -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STSL (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CHAN (LSMASH_BOX_PRECEDENCE_LP -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_CHAN (LSMASH_BOX_PRECEDENCE_LP -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_WAVE (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_FRMA (LSMASH_BOX_PRECEDENCE_HM +  1 * LSMASH_BOX_PRECEDENCE_S)   /* precede any as much as possible */
#define LSMASH_BOX_PRECEDENCE_QTFF_ENDA (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_MP4A (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_TERMINATOR (LSMASH_BOX_PRECEDENCE_L - 0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SRAT (LSMASH_BOX_PRECEDENCE_LP -  1 * LSMASH_BOX_PRECEDENCE_S)   /* place at the end for maximum compatibility */
#define LSMASH_BOX_PRECEDENCE_ISOM_FTAB (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STTS (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CTTS (LSMASH_BOX_PRECEDENCE_N  -  4 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CSLG (LSMASH_BOX_PRECEDENCE_N  -  6 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STSS (LSMASH_BOX_PRECEDENCE_N  -  8 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_STPS (LSMASH_BOX_PRECEDENCE_N  - 10 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SDTP (LSMASH_BOX_PRECEDENCE_N  - 12 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STSC (LSMASH_BOX_PRECEDENCE_N  - 14 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STSZ (LSMASH_BOX_PRECEDENCE_N  - 16 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STZ2 (LSMASH_BOX_PRECEDENCE_N  - 16 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_STCO (LSMASH_BOX_PRECEDENCE_N  - 18 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CO64 (LSMASH_BOX_PRECEDENCE_N  - 18 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SGPD (LSMASH_BOX_PRECEDENCE_N  - 20 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SBGP (LSMASH_BOX_PRECEDENCE_N  - 22 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_UDTA (LSMASH_BOX_PRECEDENCE_N  -  5 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MEAN (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_NAME (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_DATA (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_KEYS (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_ILST (LSMASH_BOX_PRECEDENCE_N  -  2 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_METAITEM (LSMASH_BOX_PRECEDENCE_N - 0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CHPL (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_META (LSMASH_BOX_PRECEDENCE_N  -  7 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_HNTI (LSMASH_BOX_PRECEDENCE_N  -  8 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_RTP  (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SDP  (LSMASH_BOX_PRECEDENCE_N  -  1 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_WLOC (LSMASH_BOX_PRECEDENCE_N  -  8 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_LOOP (LSMASH_BOX_PRECEDENCE_N  -  9 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_SELO (LSMASH_BOX_PRECEDENCE_N  - 10 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_ALLF (LSMASH_BOX_PRECEDENCE_N  - 11 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_CPRT (LSMASH_BOX_PRECEDENCE_N  - 12 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_QTFF_CTAB (LSMASH_BOX_PRECEDENCE_N  -  6 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MVEX (LSMASH_BOX_PRECEDENCE_N  -  8 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MEHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TREX (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MOOF (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MFHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TRAF (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TFHD (LSMASH_BOX_PRECEDENCE_HM -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TFDT (LSMASH_BOX_PRECEDENCE_HM -  1 * LSMASH_BOX_PRECEDENCE_S)   /* shall be positioned after 'tfhd' and before 'trun' */
#define LSMASH_BOX_PRECEDENCE_ISOM_TRUN (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MFRA (LSMASH_BOX_PRECEDENCE_L  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_TFRA (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MFRO (LSMASH_BOX_PRECEDENCE_L  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_MDAT (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_FREE (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)
#define LSMASH_BOX_PRECEDENCE_ISOM_SKIP (LSMASH_BOX_PRECEDENCE_N  -  0 * LSMASH_BOX_PRECEDENCE_S)

/* Track reference types */
typedef enum
{
    ISOM_TREF_TYPE_AVCP = LSMASH_4CC( 'a', 'v', 'c', 'p' ),   /* AVC parameter set stream link */
    ISOM_TREF_TYPE_CDSC = LSMASH_4CC( 'c', 'd', 's', 'c' ),   /* This track describes the referenced track. */
    ISOM_TREF_TYPE_DPND = LSMASH_4CC( 'd', 'p', 'n', 'd' ),   /* This track has an MPEG-4 dependency on the referenced track. */
    ISOM_TREF_TYPE_HIND = LSMASH_4CC( 'h', 'i', 'n', 'd' ),   /* Hint dependency */
    ISOM_TREF_TYPE_HINT = LSMASH_4CC( 'h', 'i', 'n', 't' ),   /* Links hint track to original media track */
    ISOM_TREF_TYPE_IPIR = LSMASH_4CC( 'i', 'p', 'i', 'r' ),   /* This track contains IPI declarations for the referenced track. */
    ISOM_TREF_TYPE_MPOD = LSMASH_4CC( 'm', 'p', 'o', 'd' ),   /* This track is an OD track which uses the referenced track as an included elementary stream track. */
    ISOM_TREF_TYPE_SBAS = LSMASH_4CC( 's', 'b', 'a', 's' ),   /* Scalable base */
    ISOM_TREF_TYPE_SCAL = LSMASH_4CC( 's', 'c', 'a', 'l' ),   /* Scalable extraction */
    ISOM_TREF_TYPE_SWFR = LSMASH_4CC( 's', 'w', 'f', 'r' ),   /* AVC Switch from */
    ISOM_TREF_TYPE_SWTO = LSMASH_4CC( 's', 'w', 't', 'o' ),   /* AVC Switch to */
    ISOM_TREF_TYPE_SYNC = LSMASH_4CC( 's', 'y', 'n', 'c' ),   /* This track uses the referenced track as its synchronization source. */
    ISOM_TREF_TYPE_VDEP = LSMASH_4CC( 'v', 'd', 'e', 'p' ),   /* Auxiliary video depth */
    ISOM_TREF_TYPE_VPLX = LSMASH_4CC( 'v', 'p', 'l', 'x' ),   /* Auxiliary video parallax */

    QT_TREF_TYPE_CHAP   = LSMASH_4CC( 'c', 'h', 'a', 'p' ),   /* Chapter or scene list. Usually references a text track. */
    QT_TREF_TYPE_SCPT   = LSMASH_4CC( 's', 'c', 'p', 't' ),   /* Transcript. Usually references a text track. */
    QT_TREF_TYPE_SSRC   = LSMASH_4CC( 's', 's', 'r', 'c' ),   /* Nonprimary source. Indicates that the referenced track should send its data to this track, rather than presenting it. */
    QT_TREF_TYPE_TMCD   = LSMASH_4CC( 't', 'm', 'c', 'd' ),   /* Time code. Usually references a time code track. */
} isom_track_reference_type;

/* Handler types */
enum isom_handler_type
{
    QT_HANDLER_TYPE_DATA    = LSMASH_4CC( 'd', 'h', 'l', 'r' ),
    QT_HANDLER_TYPE_MEDIA   = LSMASH_4CC( 'm', 'h', 'l', 'r' ),
};

enum isom_meta_type
{
    ISOM_META_HANDLER_TYPE_ITUNES_METADATA = LSMASH_4CC( 'm', 'd', 'i', 'r' ),
};

/* Data reference types */
enum isom_data_reference_type
{
    ISOM_REFERENCE_HANDLER_TYPE_URL     = LSMASH_4CC( 'u', 'r', 'l', ' ' ),
    ISOM_REFERENCE_HANDLER_TYPE_URN     = LSMASH_4CC( 'u', 'r', 'n', ' ' ),

    QT_REFERENCE_HANDLER_TYPE_ALIAS     = LSMASH_4CC( 'a', 'l', 'i', 's' ),
    QT_REFERENCE_HANDLER_TYPE_RESOURCE  = LSMASH_4CC( 'r', 's', 'r', 'c' ),
    QT_REFERENCE_HANDLER_TYPE_URL       = LSMASH_4CC( 'u', 'r', 'l', ' ' ),
};

/* Lanuage codes */
typedef struct
{
    uint16_t mac_value;
    uint16_t iso_name;
} isom_language_t;

static const isom_language_t isom_languages[] =
{
    {   0, ISOM_LANGUAGE_CODE_ENGLISH },
    {   1, ISOM_LANGUAGE_CODE_FRENCH },
    {   2, ISOM_LANGUAGE_CODE_GERMAN },
    {   3, ISOM_LANGUAGE_CODE_ITALIAN },
    {   4, ISOM_LANGUAGE_CODE_DUTCH_M },
    {   5, ISOM_LANGUAGE_CODE_SWEDISH },
    {   6, ISOM_LANGUAGE_CODE_SPANISH },
    {   7, ISOM_LANGUAGE_CODE_DANISH },
    {   8, ISOM_LANGUAGE_CODE_PORTUGUESE },
    {   9, ISOM_LANGUAGE_CODE_NORWEGIAN },
    {  10, ISOM_LANGUAGE_CODE_HEBREW },
    {  11, ISOM_LANGUAGE_CODE_JAPANESE },
    {  12, ISOM_LANGUAGE_CODE_ARABIC },
    {  13, ISOM_LANGUAGE_CODE_FINNISH },
    {  14, ISOM_LANGUAGE_CODE_GREEK },
    {  15, ISOM_LANGUAGE_CODE_ICELANDIC },
    {  16, ISOM_LANGUAGE_CODE_MALTESE },
    {  17, ISOM_LANGUAGE_CODE_TURKISH },
    {  18, ISOM_LANGUAGE_CODE_CROATIAN },
    {  19, ISOM_LANGUAGE_CODE_CHINESE },
    {  20, ISOM_LANGUAGE_CODE_URDU },
    {  21, ISOM_LANGUAGE_CODE_HINDI },
    {  22, ISOM_LANGUAGE_CODE_THAI },
    {  23, ISOM_LANGUAGE_CODE_KOREAN },
    {  24, ISOM_LANGUAGE_CODE_LITHUANIAN },
    {  25, ISOM_LANGUAGE_CODE_POLISH },
    {  26, ISOM_LANGUAGE_CODE_HUNGARIAN },
    {  27, ISOM_LANGUAGE_CODE_ESTONIAN },
    {  28, ISOM_LANGUAGE_CODE_LATVIAN },
    {  29, ISOM_LANGUAGE_CODE_SAMI },
    {  30, ISOM_LANGUAGE_CODE_FAROESE },
    {  32, ISOM_LANGUAGE_CODE_RUSSIAN },
    {  33, ISOM_LANGUAGE_CODE_CHINESE },
    {  34, ISOM_LANGUAGE_CODE_DUTCH },
    {  35, ISOM_LANGUAGE_CODE_IRISH },
    {  36, ISOM_LANGUAGE_CODE_ALBANIAN },
    {  37, ISOM_LANGUAGE_CODE_ROMANIAN },
    {  38, ISOM_LANGUAGE_CODE_CZECH },
    {  39, ISOM_LANGUAGE_CODE_SLOVAK },
    {  40, ISOM_LANGUAGE_CODE_SLOVENIA },
    {  41, ISOM_LANGUAGE_CODE_YIDDISH },
    {  42, ISOM_LANGUAGE_CODE_SERBIAN },
    {  43, ISOM_LANGUAGE_CODE_MACEDONIAN },
    {  44, ISOM_LANGUAGE_CODE_BULGARIAN },
    {  45, ISOM_LANGUAGE_CODE_UKRAINIAN },
    {  46, ISOM_LANGUAGE_CODE_BELARUSIAN },
    {  47, ISOM_LANGUAGE_CODE_UZBEK },
    {  48, ISOM_LANGUAGE_CODE_KAZAKH },
    {  49, ISOM_LANGUAGE_CODE_AZERBAIJANI },
    {  51, ISOM_LANGUAGE_CODE_ARMENIAN },
    {  52, ISOM_LANGUAGE_CODE_GEORGIAN },
    {  53, ISOM_LANGUAGE_CODE_MOLDAVIAN },
    {  54, ISOM_LANGUAGE_CODE_KIRGHIZ },
    {  55, ISOM_LANGUAGE_CODE_TAJIK },
    {  56, ISOM_LANGUAGE_CODE_TURKMEN },
    {  57, ISOM_LANGUAGE_CODE_MONGOLIAN },
    {  59, ISOM_LANGUAGE_CODE_PASHTO },
    {  60, ISOM_LANGUAGE_CODE_KURDISH },
    {  61, ISOM_LANGUAGE_CODE_KASHMIRI },
    {  62, ISOM_LANGUAGE_CODE_SINDHI },
    {  63, ISOM_LANGUAGE_CODE_TIBETAN },
    {  64, ISOM_LANGUAGE_CODE_NEPALI },
    {  65, ISOM_LANGUAGE_CODE_SANSKRIT },
    {  66, ISOM_LANGUAGE_CODE_MARATHI },
    {  67, ISOM_LANGUAGE_CODE_BENGALI },
    {  68, ISOM_LANGUAGE_CODE_ASSAMESE },
    {  69, ISOM_LANGUAGE_CODE_GUJARATI },
    {  70, ISOM_LANGUAGE_CODE_PUNJABI },
    {  71, ISOM_LANGUAGE_CODE_ORIYA },
    {  72, ISOM_LANGUAGE_CODE_MALAYALAM },
    {  73, ISOM_LANGUAGE_CODE_KANNADA },
    {  74, ISOM_LANGUAGE_CODE_TAMIL },
    {  75, ISOM_LANGUAGE_CODE_TELUGU },
    {  76, ISOM_LANGUAGE_CODE_SINHALESE },
    {  77, ISOM_LANGUAGE_CODE_BURMESE },
    {  78, ISOM_LANGUAGE_CODE_KHMER },
    {  79, ISOM_LANGUAGE_CODE_LAO },
    {  80, ISOM_LANGUAGE_CODE_VIETNAMESE },
    {  81, ISOM_LANGUAGE_CODE_INDONESIAN },
    {  82, ISOM_LANGUAGE_CODE_TAGALOG },
    {  83, ISOM_LANGUAGE_CODE_MALAY_ROMAN },
    {  84, ISOM_LANGUAGE_CODE_MAYAY_ARABIC },
    {  85, ISOM_LANGUAGE_CODE_AMHARIC },
    {  87, ISOM_LANGUAGE_CODE_OROMO },
    {  88, ISOM_LANGUAGE_CODE_SOMALI },
    {  89, ISOM_LANGUAGE_CODE_SWAHILI },
    {  90, ISOM_LANGUAGE_CODE_KINYARWANDA },
    {  91, ISOM_LANGUAGE_CODE_RUNDI },
    {  92, ISOM_LANGUAGE_CODE_CHEWA },
    {  93, ISOM_LANGUAGE_CODE_MALAGASY },
    {  94, ISOM_LANGUAGE_CODE_ESPERANTO },
    { 128, ISOM_LANGUAGE_CODE_WELSH },
    { 129, ISOM_LANGUAGE_CODE_BASQUE },
    { 130, ISOM_LANGUAGE_CODE_CATALAN },
    { 131, ISOM_LANGUAGE_CODE_LATIN },
    { 132, ISOM_LANGUAGE_CODE_QUECHUA },
    { 133, ISOM_LANGUAGE_CODE_GUARANI },
    { 134, ISOM_LANGUAGE_CODE_AYMARA },
    { 135, ISOM_LANGUAGE_CODE_TATAR },
    { 136, ISOM_LANGUAGE_CODE_UIGHUR },
    { 137, ISOM_LANGUAGE_CODE_DZONGKHA },
    { 138, ISOM_LANGUAGE_CODE_JAVANESE },
    { UINT16_MAX, 0 }
};

/* Color parameters */
enum isom_color_patameter_type
{
    ISOM_COLOR_PARAMETER_TYPE_NCLX = LSMASH_4CC( 'n', 'c', 'l', 'x' ),      /* on-screen colours */
    ISOM_COLOR_PARAMETER_TYPE_RICC = LSMASH_4CC( 'r', 'I', 'C', 'C' ),      /* restricted ICC profile */
    ISOM_COLOR_PARAMETER_TYPE_PROF = LSMASH_4CC( 'p', 'r', 'o', 'f' ),      /* unrestricted ICC profile */

    QT_COLOR_PARAMETER_TYPE_NCLC   = LSMASH_4CC( 'n', 'c', 'l', 'c' ),      /* NonConstant Luminance Coding */
    QT_COLOR_PARAMETER_TYPE_PROF   = LSMASH_4CC( 'p', 'r', 'o', 'f' ),      /* ICC profile */
};

/* Sample grouping types */
typedef enum
{
    ISOM_GROUP_TYPE_3GAG = LSMASH_4CC( '3', 'g', 'a', 'g' ),      /* Text track3GPP PSS Annex G video buffer parameters */
    ISOM_GROUP_TYPE_ALST = LSMASH_4CC( 'a', 'l', 's', 't' ),      /* Alternative startup sequence */
    ISOM_GROUP_TYPE_AVCB = LSMASH_4CC( 'a', 'v', 'c', 'b' ),      /* AVC HRD parameters */
    ISOM_GROUP_TYPE_AVLL = LSMASH_4CC( 'a', 'v', 'l', 'l' ),      /* AVC Layer */
    ISOM_GROUP_TYPE_AVSS = LSMASH_4CC( 'a', 'v', 's', 's' ),      /* AVC Sub Sequence */
    ISOM_GROUP_TYPE_DTRT = LSMASH_4CC( 'd', 't', 'r', 't' ),      /* Decode re-timing */
    ISOM_GROUP_TYPE_MVIF = LSMASH_4CC( 'm', 'v', 'i', 'f' ),      /* MVC Scalability Information */
    ISOM_GROUP_TYPE_PROL = LSMASH_4CC( 'p', 'r', 'o', 'l' ),      /* Pre-roll */
    ISOM_GROUP_TYPE_RAP  = LSMASH_4CC( 'r', 'a', 'p', ' ' ),      /* Random Access Point */
    ISOM_GROUP_TYPE_RASH = LSMASH_4CC( 'r', 'a', 's', 'h' ),      /* Rate Share */
    ISOM_GROUP_TYPE_ROLL = LSMASH_4CC( 'r', 'o', 'l', 'l' ),      /* Pre-roll/Post-roll */
    ISOM_GROUP_TYPE_SCIF = LSMASH_4CC( 's', 'c', 'i', 'f' ),      /* SVC Scalability Information */
    ISOM_GROUP_TYPE_SCNM = LSMASH_4CC( 's', 'c', 'n', 'm' ),      /* AVC/SVC/MVC map groups */
    ISOM_GROUP_TYPE_VIPR = LSMASH_4CC( 'v', 'i', 'p', 'r' ),      /* View priority */
} isom_grouping_type;

/* wrapper to avoid boring cast */
#define isom_init_box_common( box, parent, box_type, precedence, destructor ) \
        isom_init_box_common_orig( box, parent, box_type, precedence, (isom_extension_destructor_t)(destructor) )

void isom_init_box_common_orig
(
    void                       *box,
    void                       *parent,
    lsmash_box_type_t           box_type,
    uint64_t                    precedence,
    isom_extension_destructor_t destructor
);

int isom_is_fullbox( const void *box );
int isom_is_lpcm_audio( const void *box );
int isom_is_qt_audio( lsmash_codec_type_t type );
int isom_is_uncompressed_ycbcr( lsmash_codec_type_t type );
int isom_is_waveform_audio( lsmash_box_type_t type );

size_t isom_skip_box_common
(
    uint8_t **p_data
);

uint8_t *isom_get_child_box_position
(
    uint8_t           *parent_data,
    uint32_t          parent_size,
    lsmash_box_type_t child_type,
    uint32_t         *child_size
);

void isom_bs_put_basebox_common( lsmash_bs_t *bs, isom_box_t *box );
void isom_bs_put_fullbox_common( lsmash_bs_t *bs, isom_box_t *box );
void isom_bs_put_box_common( lsmash_bs_t *bs, void *box );

#define isom_is_printable_char( c ) ((c) >= 32 && (c) < 128)
#define isom_is_printable_4cc( fourcc )                \
    (isom_is_printable_char( ((fourcc) >> 24) & 0xff ) \
  && isom_is_printable_char( ((fourcc) >> 16) & 0xff ) \
  && isom_is_printable_char( ((fourcc) >>  8) & 0xff ) \
  && isom_is_printable_char(  (fourcc)        & 0xff ))

#define isom_4cc2str( fourcc ) (const char [5]){ (fourcc) >> 24, (fourcc) >> 16, (fourcc) >> 8, (fourcc), 0 }

int isom_check_initializer_present( lsmash_root_t *root );

isom_trak_t *isom_get_trak( lsmash_file_t *file, uint32_t track_ID );
isom_trex_t *isom_get_trex( isom_mvex_t *mvex, uint32_t track_ID );
isom_traf_t *isom_get_traf( isom_moof_t *moof, uint32_t track_ID );
isom_tfra_t *isom_get_tfra( isom_mfra_t *mfra, uint32_t track_ID );
isom_sgpd_t *isom_get_sample_group_description( isom_stbl_t *stbl, uint32_t grouping_type );
isom_sbgp_t *isom_get_sample_to_group( isom_stbl_t *stbl, uint32_t grouping_type );
isom_sgpd_t *isom_get_roll_recovery_sample_group_description( lsmash_entry_list_t *list );
isom_sbgp_t *isom_get_roll_recovery_sample_to_group( lsmash_entry_list_t *list );
isom_sgpd_t *isom_get_fragment_sample_group_description( isom_traf_t *traf, uint32_t grouping_type );
isom_sbgp_t *isom_get_fragment_sample_to_group( isom_traf_t *traf, uint32_t grouping_type );

isom_trak_t *isom_track_create( lsmash_file_t *file, lsmash_media_type media_type );
isom_moov_t *isom_movie_create( lsmash_file_t *file );

int isom_setup_handler_reference( isom_hdlr_t *hdlr, uint32_t media_type );
int isom_setup_iods( isom_moov_t *moov );

uint32_t isom_get_sample_count
(
    isom_trak_t *trak
);

isom_sample_pool_t *isom_create_sample_pool
(
    uint64_t size
);

int isom_update_sample_tables
(
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    uint32_t            *samples_per_packet,
    isom_sample_entry_t *sample_entry
);

int isom_pool_sample
(
    isom_sample_pool_t *pool,
    lsmash_sample_t    *sample,
    uint32_t            samples_per_packet
);

int isom_append_sample_by_type
(
    void                *track,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry,
    int (*func_append_sample)( void *, lsmash_sample_t *, isom_sample_entry_t * )
);

int isom_calculate_bitrate_description
(
    isom_stbl_t *stbl,
    isom_mdhd_t *mdhd,
    uint32_t    *bufferSizeDB,
    uint32_t    *maxBitrate,
    uint32_t    *avgBitrate,
    uint32_t     sample_description_index
);

int isom_is_variable_size
(
    isom_stbl_t *stbl
);

uint32_t isom_get_first_sample_size
(
    isom_stbl_t *stbl
);


void isom_update_cache_timestamp
(
    isom_cache_t *cache,
    uint64_t      dts,
    uint64_t      cts,
    int32_t       ctd_shift,
    uint32_t      sample_duration,
    int           non_output_sample
);

/* Make CTS from DTS and sample_offset.
 * This function does NOT add the value of composition to decode timeline shift to the result. */
static inline uint64_t isom_make_cts
(
    uint64_t dts,
    uint32_t sample_offset,
    int32_t  ctd_shift
)
{
    if( sample_offset != ISOM_NON_OUTPUT_SAMPLE_OFFSET )
        return ctd_shift ? (dts + (int32_t)sample_offset) : (dts + sample_offset);
    else
        return LSMASH_TIMESTAMP_UNDEFINED;
}

/* Make CTS from DTS and sample_offset.
 * This function adds the value of composition to decode timeline shift to the result. */
static inline uint64_t isom_make_cts_adjust
(
    uint64_t dts,
    uint32_t sample_offset,
    int32_t  ctd_shift
)
{
    if( sample_offset != ISOM_NON_OUTPUT_SAMPLE_OFFSET )
        return ctd_shift ? (dts + (int32_t)sample_offset + ctd_shift) : (dts + sample_offset);
    else
        return LSMASH_TIMESTAMP_UNDEFINED;
}

/* Utilities for sample entry type decision
 * NOTE: This implementation does not work when 'mdia' and/or 'hdlr' is stored as binary string. */
static inline int isom_check_media_hdlr_from_stsd( isom_stsd_t *stsd )
{
    return ((isom_stbl_t *)stsd->parent
        &&  (isom_minf_t *)stsd->parent->parent
        &&  (isom_mdia_t *)stsd->parent->parent->parent
        && ((isom_mdia_t *)stsd->parent->parent->parent)->hdlr);
}
static inline lsmash_media_type isom_get_media_type_from_stsd( isom_stsd_t *stsd )
{
    assert( isom_check_media_hdlr_from_stsd( stsd ) );
    return ((isom_mdia_t *)stsd->parent->parent->parent)->hdlr->componentSubtype;
}

int isom_add_sample_grouping( isom_box_t *parent, isom_grouping_type grouping_type );
int isom_group_random_access( isom_box_t *parent, isom_cache_t *cache, lsmash_sample_t *sample );
int isom_group_roll_recovery( isom_box_t *parent, isom_cache_t *cache, lsmash_sample_t *sample );

int isom_update_tkhd_duration( isom_trak_t *trak );
int isom_update_bitrate_description( isom_mdia_t *mdia );
int isom_complement_data_reference( isom_minf_t *minf );
int isom_check_large_offset_requirement( isom_moov_t *moov, uint64_t meta_size );
void isom_add_preceding_box_size( isom_moov_t *moov, uint64_t preceding_size );
int isom_establish_movie( lsmash_file_t *file );
int isom_rap_grouping_established( isom_rap_group_t *group, int num_leading_samples_known, isom_sgpd_t *sgpd, int is_fragment );
int isom_all_recovery_completed( isom_sbgp_t *sbgp, lsmash_entry_list_t *pool );

lsmash_file_t *isom_add_file_abstract( lsmash_root_t *root );
isom_ftyp_t *isom_add_ftyp( lsmash_file_t *file );
isom_moov_t *isom_add_moov( lsmash_file_t *file );
isom_mvhd_t *isom_add_mvhd( isom_moov_t *moov );
isom_iods_t *isom_add_iods( isom_moov_t *moov );
isom_ctab_t *isom_add_ctab( void *parent_box );
isom_trak_t *isom_add_trak( isom_moov_t *moov );
isom_tkhd_t *isom_add_tkhd( isom_trak_t *trak );
isom_tapt_t *isom_add_tapt( isom_trak_t *trak );
isom_clef_t *isom_add_clef( isom_tapt_t *tapt );
isom_prof_t *isom_add_prof( isom_tapt_t *tapt );
isom_enof_t *isom_add_enof( isom_tapt_t *tapt );
isom_edts_t *isom_add_edts( isom_trak_t *trak );
isom_elst_t *isom_add_elst( isom_edts_t *edts );
isom_tref_t *isom_add_tref( isom_trak_t *trak );
isom_tref_type_t *isom_add_track_reference_type( isom_tref_t *tref, isom_track_reference_type type );
isom_mdia_t *isom_add_mdia( isom_trak_t *trak );
isom_mdhd_t *isom_add_mdhd( isom_mdia_t *mdia );
isom_hdlr_t *isom_add_hdlr( void *parent_box );
isom_minf_t *isom_add_minf( isom_mdia_t *mdia );
isom_vmhd_t *isom_add_vmhd( isom_minf_t *minf );
isom_smhd_t *isom_add_smhd( isom_minf_t *minf );
isom_hmhd_t *isom_add_hmhd( isom_minf_t *minf );
isom_nmhd_t *isom_add_nmhd( isom_minf_t *minf );
isom_gmhd_t *isom_add_gmhd( isom_minf_t *minf );
isom_gmin_t *isom_add_gmin( isom_gmhd_t *gmhd );
isom_text_t *isom_add_text( isom_gmhd_t *gmhd );
isom_dinf_t *isom_add_dinf( void *parent_box );
isom_dref_t *isom_add_dref( isom_dinf_t *dinf );
isom_dref_entry_t *isom_add_dref_entry( isom_dref_t *dref, lsmash_box_type_t type );
isom_stbl_t *isom_add_stbl( isom_minf_t *minf );
isom_stsd_t *isom_add_stsd( isom_stbl_t *stbl );
isom_visual_entry_t *isom_add_visual_description( isom_stsd_t *stsd, lsmash_codec_type_t sample_type );
isom_audio_entry_t *isom_add_audio_description( isom_stsd_t *stsd, lsmash_codec_type_t sample_type );
isom_hint_entry_t *isom_add_hint_description(isom_stsd_t *stsd, lsmash_codec_type_t sample_type);
isom_qt_text_entry_t *isom_add_qt_text_description( isom_stsd_t *stsd );
isom_tx3g_entry_t *isom_add_tx3g_description( isom_stsd_t *stsd );
isom_esds_t *isom_add_esds( void *parent_box );
isom_glbl_t *isom_add_glbl( void *parent_box );
isom_clap_t *isom_add_clap( isom_visual_entry_t *visual );
isom_pasp_t *isom_add_pasp( isom_visual_entry_t *visual );
isom_colr_t *isom_add_colr( isom_visual_entry_t *visual );
isom_gama_t *isom_add_gama( isom_visual_entry_t *visual );
isom_fiel_t *isom_add_fiel( isom_visual_entry_t *visual );
isom_clli_t *isom_add_clli( isom_visual_entry_t *visual );
isom_mdcv_t *isom_add_mdcv( isom_visual_entry_t *visual );
isom_cspc_t *isom_add_cspc( isom_visual_entry_t *visual );
isom_sgbt_t *isom_add_sgbt( isom_visual_entry_t *visual );
isom_stsl_t *isom_add_stsl( isom_visual_entry_t *visual );
isom_btrt_t *isom_add_btrt( isom_visual_entry_t *visual );
isom_tims_t *isom_add_tims( isom_hint_entry_t *hint );
isom_tsro_t *isom_add_tsro( isom_hint_entry_t *hint );
isom_tssy_t *isom_add_tssy( isom_hint_entry_t *hint );
isom_wave_t *isom_add_wave( isom_audio_entry_t *audio );
isom_frma_t *isom_add_frma( isom_wave_t *wave );
isom_enda_t *isom_add_enda( isom_wave_t *wave );
isom_mp4a_t *isom_add_mp4a( isom_wave_t *wave );
isom_terminator_t *isom_add_terminator( isom_wave_t *wave );
isom_chan_t *isom_add_chan( isom_audio_entry_t *audio );
isom_srat_t *isom_add_srat( isom_audio_entry_t *audio );
isom_ftab_t *isom_add_ftab( isom_tx3g_entry_t *tx3g );
isom_stts_t *isom_add_stts( isom_stbl_t *stbl );
isom_ctts_t *isom_add_ctts( isom_stbl_t *stbl );
isom_cslg_t *isom_add_cslg( isom_stbl_t *stbl );
isom_stsc_t *isom_add_stsc( isom_stbl_t *stbl );
isom_stsz_t *isom_add_stsz( isom_stbl_t *stbl );
isom_stz2_t *isom_add_stz2( isom_stbl_t *stbl );
isom_stss_t *isom_add_stss( isom_stbl_t *stbl );
isom_stps_t *isom_add_stps( isom_stbl_t *stbl );
isom_sdtp_t *isom_add_sdtp( isom_box_t *parent );
isom_sgpd_t *isom_add_sgpd( void *parent_box );
isom_sbgp_t *isom_add_sbgp( void *parent_box );
isom_stco_t *isom_add_stco( isom_stbl_t *stbl );
isom_stco_t *isom_add_co64( isom_stbl_t *stbl );
isom_udta_t *isom_add_udta( void *parent_box );
isom_cprt_t *isom_add_cprt( isom_udta_t *udta );
isom_hnti_t *isom_add_hnti( isom_udta_t *udta );
isom_rtp_t  *isom_add_rtp(  isom_hnti_t *hnti );
isom_sdp_t  *isom_add_sdp(  isom_hnti_t *hnti );
isom_WLOC_t *isom_add_WLOC( isom_udta_t *udta );
isom_LOOP_t *isom_add_LOOP( isom_udta_t *udta );
isom_SelO_t *isom_add_SelO( isom_udta_t *udta );
isom_AllF_t *isom_add_AllF( isom_udta_t *udta );
isom_chpl_t *isom_add_chpl( isom_udta_t *udta );
isom_meta_t *isom_add_meta( void *parent_box );
isom_keys_t *isom_add_keys( isom_meta_t *meta );
isom_ilst_t *isom_add_ilst( isom_meta_t *meta );
isom_metaitem_t *isom_add_metaitem( isom_ilst_t *ilst, lsmash_itunes_metadata_item item );
isom_mean_t *isom_add_mean( isom_metaitem_t *metaitem );
isom_name_t *isom_add_name( isom_metaitem_t *metaitem );
isom_data_t *isom_add_data( isom_metaitem_t *metaitem );
isom_mvex_t *isom_add_mvex( isom_moov_t *moov );
isom_mehd_t *isom_add_mehd( isom_mvex_t *mvex );
isom_trex_t *isom_add_trex( isom_mvex_t *mvex );
isom_moof_t *isom_add_moof( lsmash_file_t *file );
isom_mfhd_t *isom_add_mfhd( isom_moof_t *moof );
isom_traf_t *isom_add_traf( isom_moof_t *moof );
isom_tfhd_t *isom_add_tfhd( isom_traf_t *traf );
isom_tfdt_t *isom_add_tfdt( isom_traf_t *traf );
isom_trun_t *isom_add_trun( isom_traf_t *traf );
isom_mfra_t *isom_add_mfra( lsmash_file_t *file );
isom_tfra_t *isom_add_tfra( isom_mfra_t *mfra );
isom_mfro_t *isom_add_mfro( isom_mfra_t *mfra );
isom_mdat_t *isom_add_mdat( lsmash_file_t *file );
isom_free_t *isom_add_free( void *parent_box );
isom_styp_t *isom_add_styp( lsmash_file_t *file );
isom_sidx_t *isom_add_sidx( lsmash_file_t *file );

void isom_remove_extension_box( isom_box_t *ext );
void isom_remove_sample_description( isom_sample_entry_t *sample );
void isom_remove_unknown_box( isom_unknown_box_t *unknown_box );
void isom_remove_sample_pool( isom_sample_pool_t *pool );

uint64_t isom_update_box_size( void *box );

int isom_add_extension_binary( void *parent_box, lsmash_box_type_t box_type, uint64_t precedence, uint8_t *box_data, uint32_t box_size );
void isom_remove_all_extension_boxes( lsmash_entry_list_t *extensions );
isom_box_t *isom_get_extension_box( lsmash_entry_list_t *extensions, lsmash_box_type_t box_type );
void *isom_get_extension_box_format( lsmash_entry_list_t *extensions, lsmash_box_type_t box_type );
void isom_remove_box_by_itself( void *opaque_box );

#endif

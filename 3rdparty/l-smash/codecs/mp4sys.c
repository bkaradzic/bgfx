/*****************************************************************************
 * mp4sys.c
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

#include "common/internal.h" /* must be placed first */

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "core/box.h"

#include "description.h"
#include "mp4a.h"
#define MP4SYS_INTERNAL
#include "mp4sys.h"

/***************************************************************************
    MPEG-4 Systems
***************************************************************************/

#define ALWAYS_28BITS_LENGTH_CODING 1 // for some weird (but originator's) devices

static const lsmash_class_t lsmash_mp4sys_class =
{
    "mp4sys"
};

/* List of Class Tags for Descriptors */
typedef enum
{
    MP4SYS_DESCRIPTOR_TAG_Forbidden                           = 0x00, /* Forbidden */
    MP4SYS_DESCRIPTOR_TAG_ObjectDescrTag                      = 0x01, /* ObjectDescrTag */
    MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag               = 0x02, /* InitialObjectDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ES_DescrTag                         = 0x03, /* ES_DescrTag */
    MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag               = 0x04, /* DecoderConfigDescrTag */
    MP4SYS_DESCRIPTOR_TAG_DecSpecificInfoTag                  = 0x05, /* DecSpecificInfoTag */
    MP4SYS_DESCRIPTOR_TAG_SLConfigDescrTag                    = 0x06, /* SLConfigDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ContentIdentDescrTag                = 0x07, /* ContentIdentDescrTag */
    MP4SYS_DESCRIPTOR_TAG_SupplContentIdentDescrTag           = 0x08, /* SupplContentIdentDescrTag */
    MP4SYS_DESCRIPTOR_TAG_IPI_DescrPointerTag                 = 0x09, /* IPI_DescrPointerTag */
    MP4SYS_DESCRIPTOR_TAG_IPMP_DescrPointerTag                = 0x0A, /* IPMP_DescrPointerTag */
    MP4SYS_DESCRIPTOR_TAG_IPMP_DescrTag                       = 0x0B, /* IPMP_DescrTag */
    MP4SYS_DESCRIPTOR_TAG_QoS_DescrTag                        = 0x0C, /* QoS_DescrTag */
    MP4SYS_DESCRIPTOR_TAG_RegistrationDescrTag                = 0x0D, /* RegistrationDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ES_ID_IncTag                        = 0x0E, /* ES_ID_IncTag */
    MP4SYS_DESCRIPTOR_TAG_ES_ID_RefTag                        = 0x0F, /* ES_ID_RefTag */
    MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag                         = 0x10, /* MP4_IOD_Tag, InitialObjectDescriptor for MP4 */
    MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag                          = 0x11, /* MP4_OD_Tag, ObjectDescriptor for MP4 */
    MP4SYS_DESCRIPTOR_TAG_IPI_DescrPointerRefTag              = 0x12, /* IPI_DescrPointerRefTag */
    MP4SYS_DESCRIPTOR_TAG_ExtendedProfileLevelDescrTag        = 0x13, /* ExtendedProfileLevelDescrTag */
    MP4SYS_DESCRIPTOR_TAG_profileLevelIndicationIndexDescrTag = 0x14, /* profileLevelIndicationIndexDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ContentClassificationDescrTag       = 0x40, /* ContentClassificationDescrTag */
    MP4SYS_DESCRIPTOR_TAG_KeyWordDescrTag                     = 0x41, /* KeyWordDescrTag */
    MP4SYS_DESCRIPTOR_TAG_RatingDescrTag                      = 0x42, /* RatingDescrTag */
    MP4SYS_DESCRIPTOR_TAG_LanguageDescrTag                    = 0x43, /* LanguageDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ShortTextualDescrTag                = 0x44, /* ShortTextualDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ExpandedTextualDescrTag             = 0x45, /* ExpandedTextualDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ContentCreatorNameDescrTag          = 0x46, /* ContentCreatorNameDescrTag */
    MP4SYS_DESCRIPTOR_TAG_ContentCreationDateDescrTag         = 0x47, /* ContentCreationDateDescrTag */
    MP4SYS_DESCRIPTOR_TAG_OCICreatorNameDescrTag              = 0x48, /* OCICreatorNameDescrTag */
    MP4SYS_DESCRIPTOR_TAG_OCICreationDateDescrTag             = 0x49, /* OCICreationDateDescrTag */
    MP4SYS_DESCRIPTOR_TAG_SmpteCameraPositionDescrTag         = 0x4A, /* SmpteCameraPositionDescrTag */
    MP4SYS_DESCRIPTOR_TAG_Forbidden1                          = 0xFF, /* Forbidden */
} mp4sys_descriptor_tag;
//    MP4SYS_DESCRIPTOR_TAG_ES_DescrRemoveRefTag                = 0x07, /* FIXME: (command tag), see 14496-14 Object Descriptors */

typedef struct
{
    uint32_t              size; // 2^28 at most
    mp4sys_descriptor_tag tag;
} mp4sys_descriptor_head_t;

typedef struct mp4sys_descriptor_tag mp4sys_descriptor_t;

typedef void (*mp4sys_descriptor_destructor_t)( void * );
typedef int (*mp4sys_descriptor_writer_t)( lsmash_bs_t *, void * );

#define MP4SYS_DESCRIPTOR_COMMON             \
    const lsmash_class_t          *class;    \
    mp4sys_descriptor_t           *parent;   \
    mp4sys_descriptor_destructor_t destruct; \
    mp4sys_descriptor_writer_t     write;    \
    mp4sys_descriptor_head_t       header;   \
    lsmash_entry_list_t            children

struct mp4sys_descriptor_tag
{
    MP4SYS_DESCRIPTOR_COMMON;
};

typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
} mp4sys_BaseDescriptor_t;

/* DecoderSpecificInfo */
/* contents varies depends on ObjectTypeIndication and StreamType. */
typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
    uint8_t *data;
} mp4sys_DecoderSpecificInfo_t;

/* DecoderConfigDescriptor */
typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
    lsmash_mp4sys_object_type_indication objectTypeIndication;
    lsmash_mp4sys_stream_type streamType;
    uint8_t  upStream;      /* bit(1), always 0 in this muxer, used for interactive contents. */
    uint8_t  reserved;      /* const bit(1), always 1. */
    uint32_t bufferSizeDB;  /* maybe CPB size in bytes, NOT bits. */
    uint32_t maxBitrate;
    uint32_t avgBitrate;    /* 0 if VBR */
    mp4sys_DecoderSpecificInfo_t *decSpecificInfo;  /* can be NULL. */
    /* 14496-1 seems to say if we are in IOD(InitialObjectDescriptor), we might use this.
     * See ExtensionProfileLevelDescr, The Initial Object Descriptor.
     * But I don't think this is mandatory despite 14496-1, because 14496-14 says, in OD or IOD,
     * we have to use ES_ID_Inc instead of ES_Descriptor, which does not have DecoderConfigDescriptor. */
    // profileLevelIndicationIndexDescriptor profileLevelIndicationIndexDescr [0..255];
} mp4sys_DecoderConfigDescriptor_t;

/* SLConfigDescriptor */
typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
    uint8_t predefined;     /* default the values from a set of predefined parameter sets as detailed below.
                             *  0x00        : Custom
                             *  0x01        : null SL packet header
                             *  0x02        : Reserved for use in MP4 files
                             *  0x03 - 0xFF : Reserved for ISO use
                             * MP4 file that does not use URL_Flag shall have constant value 0x02. */
    /* Custom values
     * The following fields are placed if predefined == 0x00. */
    unsigned useAccessUnitStartFlag       : 1;
    unsigned useAccessUnitEndFlag         : 1;
    unsigned useRandomAccessPointFlag     : 1;
    unsigned hasRandomAccessUnitsOnlyFlag : 1;
    unsigned usePaddingFlag               : 1;
    unsigned useTimeStampsFlag            : 1;
    unsigned useIdleFlag                  : 1;
    unsigned durationFlag                 : 1;
    uint32_t timeStampResolution;
    uint32_t OCRResolution;
    uint8_t  timeStampLength;
    uint8_t  OCRLength;
    uint8_t  AU_Length;
    uint8_t  instantBitrateLength;
    unsigned degradationPriorityLength    : 4;
    unsigned AU_seqNumLength              : 5;
    unsigned packetSeqNumLength           : 5;
    unsigned reserved                     : 2;
    /* The following fields are placed if durationFlag is true. */
    uint32_t timeScale;
    uint16_t accessUnitDuration;
    uint16_t compositionUnitDuration;
    /* The following fields are placed if useTimeStampsFlag is false. */
    uint64_t startDecodingTimeStamp;
    uint64_t startCompositionTimeStamp;
} mp4sys_SLConfigDescriptor_t;

/* ES_Descriptor */
typedef struct mp4sys_ES_Descriptor_t
{
    MP4SYS_DESCRIPTOR_COMMON;
    uint16_t ES_ID;
    unsigned streamDependenceFlag : 1;  /* no stream depencies between streams in this muxer, ES_ID of another elementary stream */
    unsigned URL_Flag             : 1;  /* no external URL referencing stream in MP4 */
    unsigned OCRstreamFlag        : 1;  /* no Object Clock Reference stream in this muxer (shall be false in MP4, useful if we're importing from MPEG-2?) */
    unsigned streamPriority       : 5;  /* no priority among streams in this muxer, higher is important */
    uint16_t dependsOn_ES_ID;
    uint8_t  URLlength;
    char     URLstring[256];
    uint16_t OCR_ES_Id;
    mp4sys_DecoderConfigDescriptor_t *decConfigDescr; /* cannot be NULL. */
    mp4sys_SLConfigDescriptor_t      *slConfigDescr;
    /* descriptors below are not mandatory, I think Language Descriptor may somewhat useful */
    /*
    IPI_DescrPointer ipiPtr[0 .. 1];               // used to indicate using other ES's IP_IdentificationDataSet
    IP_IdentificationDataSet ipIDS[0 .. 255];      // abstract class, actually ContentIdentificationDescriptor(for commercial contents management),
                                                   // or SupplementaryContentIdentificationDescriptor(for embedding titles)
    IPMP_DescriptorPointer ipmpDescrPtr[0 .. 255]; // used to intellectual property / protection management
    LanguageDescriptor langDescr[0 .. 255];        // used to identify the language of the audio/speech or text object
    QoS_Descriptor qosDescr[0 .. 1];               // used to achieve QoS
    RegistrationDescriptor regDescr[0 .. 1];       // used to carry elementary streams with data whose format is not recognized by ISO/IEC 14496-1
    ExtensionDescriptor extDescr[0 .. 255];        // abstract class, actually defined no subclass, maybe useless
    */
} mp4sys_ES_Descriptor_t;

/* 14496-14 Object Descriptors (ES_ID_Inc) */
typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
    uint32_t Track_ID;
} mp4sys_ES_ID_Inc_t;

/* 14496-1 ObjectDescriptor / InitialObjectDescriptor */
typedef struct
{
    MP4SYS_DESCRIPTOR_COMMON;
    unsigned ObjectDescriptorID            : 10;
    unsigned URL_Flag                      : 1;
    unsigned includeInlineProfileLevelFlag : 1; /* for OD, reserved and set to 1 */
    unsigned reserved                      : 4; /* 0b1111 */
    uint8_t  URLlength;
    char     URLstring[256];
    /* IOD only */
    mp4sys_ODProfileLevelIndication       ODProfileLevelIndication;
    mp4sys_sceneProfileLevelIndication    sceneProfileLevelIndication;
    mp4a_audioProfileLevelIndication      audioProfileLevelIndication;
    mp4sys_visualProfileLevelIndication   visualProfileLevelIndication;
    mp4sys_graphicsProfileLevelIndication graphicsProfileLevelIndication;
    /* */
    lsmash_entry_list_t esDescr;    /* List of ES_ID_Inc, not ES_Descriptor defined in 14496-1. 14496-14 overrides. */
    // OCI_Descriptor ociDescr[0 .. 255];
    // IPMP_DescriptorPointer ipmpDescrPtr[0 .. 255];
    // ExtensionDescriptor extDescr[0 .. 255];
} mp4sys_ObjectDescriptor_t;

static void mp4sys_remove_predefined_descriptor( void *opaque_descriptor, size_t offset_of_descriptor )
{
    assert( opaque_descriptor );
    mp4sys_descriptor_t *descriptor = (mp4sys_descriptor_t *)opaque_descriptor;
    if( descriptor->parent )
    {
        mp4sys_descriptor_t **p = (mp4sys_descriptor_t **)(((int8_t *)descriptor->parent) + offset_of_descriptor);
        if( *p == descriptor )
            *p = NULL;
    }
}

/* We always free descriptors through the children list of the parent descriptor.
 * Therefore, don't free descriptors through any list other than the children list. */
static void mp4sys_remove_descriptor_in_predefined_list( void *opaque_descriptor, size_t offset_of_list )
{
    assert( opaque_descriptor );
    mp4sys_descriptor_t *descriptor = (mp4sys_descriptor_t *)opaque_descriptor;
    if( descriptor->parent )
    {
        lsmash_entry_list_t *list = (lsmash_entry_list_t *)(((int8_t *)descriptor->parent) + offset_of_list);
        for( lsmash_entry_t *entry = list->head; entry; entry = entry->next )
            if( descriptor == entry->data )
            {
                /* We don't free this descriptor here.
                 * Because of freeing an entry of the list here, don't pass the list to free this descriptor.
                 * Or double free. */
                entry->data = NULL;
                lsmash_list_remove_entry_direct( list, entry );
                break;
            }
    }
}

static void mp4sys_remove_all_child_descriptors( lsmash_entry_list_t *children );

/* Free a descriptor and its children. */
static void mp4sys_destruct_descriptor( mp4sys_descriptor_t *descriptor )
{
    if( !descriptor )
        return;
    if( descriptor->destruct )
        descriptor->destruct( descriptor );
    mp4sys_remove_all_child_descriptors( &descriptor->children );
    lsmash_free( descriptor );
}

static void mp4sys_remove_all_child_descriptors( lsmash_entry_list_t *children )
{
    lsmash_list_remove_entries( children );
}

/* Remove a descriptor by the pointer containing its address.
 * In addition, remove from the children list of the parent descriptor if possible.
 * Don't call this function within a function freeing one or more entries of any children list because of double free.
 * Basically, don't use this function as a callback function. */
void mp4sys_remove_descriptor( void *opaque_descriptor )
{
    if( !opaque_descriptor )
        return;
    mp4sys_descriptor_t *descriptor = (mp4sys_descriptor_t *)opaque_descriptor;
    if( descriptor->parent )
    {
        mp4sys_descriptor_t *parent = descriptor->parent;
        for( lsmash_entry_t *entry = parent->children.head; entry; entry = entry->next )
            if( descriptor == entry->data )
            {
                /* Free the corresponding entry here, therefore don't call this function as a callback function
                 * if a function frees the same entry later and calls this function. */
                lsmash_list_remove_entry_direct( &parent->children, entry );
                return;
            }
    }
    mp4sys_destruct_descriptor( descriptor );
}

static void mp4sys_remove_DecoderSpecificInfo( mp4sys_DecoderSpecificInfo_t *dsi )
{
    if( !dsi )
        return;
    lsmash_free( dsi->data );
    mp4sys_remove_predefined_descriptor( dsi, offsetof( mp4sys_DecoderConfigDescriptor_t, decSpecificInfo ) );
}

static void mp4sys_remove_DecoderConfigDescriptor( mp4sys_DecoderConfigDescriptor_t *dcd )
{
    if( !dcd )
        return;
    mp4sys_remove_predefined_descriptor( dcd, offsetof( mp4sys_ES_Descriptor_t, decConfigDescr ) );
}

static void mp4sys_remove_SLConfigDescriptor( mp4sys_SLConfigDescriptor_t *slcd )
{
    if( !slcd )
        return;
    mp4sys_remove_predefined_descriptor( slcd, offsetof( mp4sys_ES_Descriptor_t, slConfigDescr ) );
}

static void mp4sys_remove_ES_Descriptor( mp4sys_ES_Descriptor_t *esd )
{
    if( !esd || (esd->parent && (esd->parent->header.tag == MP4SYS_DESCRIPTOR_TAG_ObjectDescrTag
                              || esd->parent->header.tag == MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag)) )
        return;
    mp4sys_remove_descriptor_in_predefined_list( esd, offsetof( mp4sys_ObjectDescriptor_t, esDescr ) );
}

static void mp4sys_remove_ES_ID_Inc( mp4sys_ES_ID_Inc_t *es_id_inc )
{
    if( !es_id_inc )
        return;
    mp4sys_remove_descriptor_in_predefined_list( es_id_inc, offsetof( mp4sys_ObjectDescriptor_t, esDescr ) );
}

static void mp4sys_remove_ObjectDescriptor( mp4sys_ObjectDescriptor_t *od )
{
}

static inline uint32_t mp4sys_get_descriptor_header_size( uint32_t payload_size_in_byte )
{
#if ALWAYS_28BITS_LENGTH_CODING
    return 4 + 1;   /* +4 means 28bits length coding, +1 means tag's space */
#else
    /* descriptor length will be split into 7bits
     * see 14496-1 Expandable classes and Length encoding of descriptors and commands */
    uint32_t i;
    for( i = 1; payload_size_in_byte >> ( 7 * i ); i++ );
    return i + 1; /* +1 means tag's space */
#endif
}

/* returns total size of descriptor, including header, 2 at least */
static inline uint32_t mp4sys_get_descriptor_size( uint32_t payload_size_in_byte )
{
    return payload_size_in_byte + mp4sys_get_descriptor_header_size( payload_size_in_byte );
}

static inline void mp4sys_write_descriptor_header( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header )
{
    lsmash_bs_put_byte( bs, header->tag );
    /* Descriptor length will be splitted into 7bits.
     * See 14496-1 Expandable classes and Length encoding of descriptors and commands */
#if ALWAYS_28BITS_LENGTH_CODING
    lsmash_bs_put_byte( bs, ( header->size >> 21 ) | 0x80 );
    lsmash_bs_put_byte( bs, ( header->size >> 14 ) | 0x80 );
    lsmash_bs_put_byte( bs, ( header->size >>  7 ) | 0x80 );
#else
    for( uint32_t i = mp4sys_get_descriptor_size( header->size ) - header->size - 2; i; i-- ){
        lsmash_bs_put_byte( bs, ( header->size >> ( 7 * i ) ) | 0x80 );
    }
#endif
    lsmash_bs_put_byte( bs, header->size & 0x7F );
}

int mp4sys_write_descriptor( lsmash_bs_t *bs, void *opaque_descriptor );

static int mp4sys_write_DecoderSpecificInfo( lsmash_bs_t *bs, mp4sys_DecoderSpecificInfo_t *dsi )
{
    if( dsi->data && dsi->header.size != 0 )
        lsmash_bs_put_bytes( bs, dsi->header.size, dsi->data );
    return 0;
}

static int mp4sys_write_DecoderConfigDescriptor( lsmash_bs_t *bs, mp4sys_DecoderConfigDescriptor_t *dcd )
{
    lsmash_bs_put_byte( bs, dcd->objectTypeIndication );
    uint8_t temp;
    temp  = (dcd->streamType & 0x3F) << 2;
    temp |= (dcd->upStream   & 0x01) << 1;
    temp |=  dcd->reserved   & 0x01;
    lsmash_bs_put_byte( bs, temp );
    lsmash_bs_put_be24( bs, dcd->bufferSizeDB );
    lsmash_bs_put_be32( bs, dcd->maxBitrate );
    lsmash_bs_put_be32( bs, dcd->avgBitrate );
    /* Here, profileLevelIndicationIndexDescriptor is omitted. */
    return 0;
}

static int mp4sys_write_SLConfigDescriptor( lsmash_bs_t *bs, mp4sys_SLConfigDescriptor_t *slcd )
{
    lsmash_bs_put_byte( bs, slcd->predefined );
    if( slcd->predefined == 0x00 )
    {
        uint8_t temp8;
        temp8  = slcd->useAccessUnitStartFlag       << 7;
        temp8 |= slcd->useAccessUnitEndFlag         << 6;
        temp8 |= slcd->useRandomAccessPointFlag     << 5;
        temp8 |= slcd->hasRandomAccessUnitsOnlyFlag << 4;
        temp8 |= slcd->usePaddingFlag               << 3;
        temp8 |= slcd->useTimeStampsFlag            << 2;
        temp8 |= slcd->useIdleFlag                  << 1;
        temp8 |= slcd->durationFlag;
        lsmash_bs_put_byte( bs, temp8 );
        lsmash_bs_put_be32( bs, slcd->timeStampResolution );
        lsmash_bs_put_be32( bs, slcd->OCRResolution );
        lsmash_bs_put_byte( bs, slcd->timeStampLength );
        lsmash_bs_put_byte( bs, slcd->OCRLength );
        lsmash_bs_put_byte( bs, slcd->AU_Length );
        lsmash_bs_put_byte( bs, slcd->instantBitrateLength );
        uint16_t temp16;
        temp16  = slcd->degradationPriorityLength << 12;
        temp16 |= slcd->AU_seqNumLength           << 7;
        temp16 |= slcd->packetSeqNumLength        << 2;
        temp16 |= slcd->reserved;
        lsmash_bs_put_be16( bs, temp16 );
    }
    if( slcd->durationFlag )
    {
        lsmash_bs_put_be32( bs, slcd->timeScale );
        lsmash_bs_put_be16( bs, slcd->accessUnitDuration );
        lsmash_bs_put_be16( bs, slcd->compositionUnitDuration );
    }
    if( !slcd->useTimeStampsFlag )
    {
        lsmash_bits_t *bits = lsmash_bits_create( bs );
        if( !bits )
            return LSMASH_ERR_MEMORY_ALLOC;
        lsmash_bits_put( bits, slcd->timeStampLength, slcd->startDecodingTimeStamp );
        lsmash_bits_put( bits, slcd->timeStampLength, slcd->startCompositionTimeStamp );
        lsmash_bits_put_align( bits );
        lsmash_bits_cleanup( bits );
    }
    return 0;
}

static int mp4sys_write_ES_Descriptor( lsmash_bs_t *bs, mp4sys_ES_Descriptor_t *esd )
{
    lsmash_bs_put_be16( bs, esd->ES_ID );
    uint8_t temp;
    temp  = esd->streamDependenceFlag << 7;
    temp |= esd->URL_Flag             << 6;
    temp |= esd->OCRstreamFlag        << 5;
    temp |= esd->streamPriority;
    lsmash_bs_put_byte( bs, temp );
    if( esd->streamDependenceFlag )
        lsmash_bs_put_be16( bs, esd->dependsOn_ES_ID );
    if( esd->URL_Flag )
    {
        lsmash_bs_put_byte( bs, esd->URLlength );
        lsmash_bs_put_bytes( bs, esd->URLlength, esd->URLstring );
    }
    if( esd->OCRstreamFlag )
        lsmash_bs_put_be16( bs, esd->OCR_ES_Id );
    /* Here, some syntax elements are omitted due to previous flags (all 0). */
    return 0;
}

static int mp4sys_write_ES_ID_Inc( lsmash_bs_t *bs, mp4sys_ES_ID_Inc_t *es_id_inc )
{
    lsmash_bs_put_be32( bs, es_id_inc->Track_ID );
    return 0;
}

static int mp4sys_write_ObjectDescriptor( lsmash_bs_t *bs, mp4sys_ObjectDescriptor_t *od )
{
    uint16_t temp = (od->ObjectDescriptorID << 6);
    // temp |= (0x0 << 5); /* URL_Flag */
    temp |= (od->includeInlineProfileLevelFlag << 4); /* if MP4_OD, includeInlineProfileLevelFlag is 0x1. */
    temp |= 0xF;  /* reserved */
    lsmash_bs_put_be16( bs, temp );
    /* here, since we don't support URL_Flag, we put ProfileLevelIndications */
    if( od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag )
    {
        lsmash_bs_put_byte( bs, od->ODProfileLevelIndication );
        lsmash_bs_put_byte( bs, od->sceneProfileLevelIndication );
        lsmash_bs_put_byte( bs, od->audioProfileLevelIndication );
        lsmash_bs_put_byte( bs, od->visualProfileLevelIndication );
        lsmash_bs_put_byte( bs, od->graphicsProfileLevelIndication );
    }
    return 0;
}

static int mp4sys_write_children( lsmash_bs_t *bs, mp4sys_descriptor_t *descriptor )
{
    for( lsmash_entry_t *entry = descriptor->children.head; entry; entry = entry->next )
    {
        mp4sys_descriptor_t *child = (mp4sys_descriptor_t *)entry->data;
        if( !child )
            continue;
        int ret = mp4sys_write_descriptor( bs, child );
        if( ret < 0 )
            return ret;
    }
    return 0;
}

int mp4sys_write_descriptor( lsmash_bs_t *bs, void *opaque_descriptor )
{
    if( !bs || !opaque_descriptor )
        return LSMASH_ERR_NAMELESS;
    mp4sys_descriptor_t *descriptor = (mp4sys_descriptor_t *)opaque_descriptor;
    mp4sys_write_descriptor_header( bs, &descriptor->header );
    if( !descriptor->write )
        return 0;
    int err = descriptor->write( bs, descriptor );
    if( err < 0 )
        return err;
    return mp4sys_write_children( bs, descriptor );
}

/* descriptor size updater */
uint32_t mp4sys_update_descriptor_size( void *opaque_descriptor )
{
    assert( opaque_descriptor );
    mp4sys_descriptor_t *descriptor = (mp4sys_descriptor_t *)opaque_descriptor;
    uint64_t size = 0;
    if( descriptor->write )
    {
        uint32_t header_size = descriptor->header.size;
        /* Calculate the size of this descriptor excluding its children with a fake bytestream writer. */
        {
            lsmash_bs_t fake_bs = { NULL };
            mp4sys_write_descriptor_header( &fake_bs, &descriptor->header );
            if( descriptor->write( &fake_bs, descriptor ) == 0 )
                size = lsmash_bs_get_valid_data_size( &fake_bs );
        }
        /* Calculate the size including the children if no error. */
        if( size >= mp4sys_get_descriptor_header_size( header_size ) )
        {
            for( lsmash_entry_t *entry = descriptor->children.head; entry; entry = entry->next )
                if( entry->data )
                    size += mp4sys_update_descriptor_size( entry->data );
            /* Calculate the size of this descriptor excluding its header. */
            size -= mp4sys_get_descriptor_header_size( header_size );
            descriptor->header.size = size;
            /* Now, we get the actual size of this descriptor. */
            size += mp4sys_get_descriptor_header_size( size );
        }
        else
        {
            /* Invalid descriptor */
            descriptor->header.size = 0;
            size = 0;
        }
    }
    else
        descriptor->header.size = 0;
    return size;
}

static inline void *mp4sys_construct_descriptor_orig
(
    size_t                         size,
    mp4sys_descriptor_t           *parent,
    mp4sys_descriptor_destructor_t destructor,
    mp4sys_descriptor_writer_t     writer
)
{
    assert( size >= sizeof(mp4sys_BaseDescriptor_t) );
    mp4sys_descriptor_t *descriptor = lsmash_malloc_zero( size );
    if( !descriptor )
        return NULL;
    descriptor->class    = &lsmash_mp4sys_class;
    descriptor->parent   = parent;
    descriptor->destruct = destructor;
    descriptor->write    = writer;
    lsmash_list_init( &descriptor->children, mp4sys_destruct_descriptor );
    return descriptor;
}

#define mp4sys_construct_descriptor( size, parent, destructor, writer ) \
        mp4sys_construct_descriptor_orig                                \
        (                                                               \
            size,                                                       \
            (mp4sys_descriptor_t *)parent,                              \
            (mp4sys_descriptor_destructor_t)destructor,                 \
            (mp4sys_descriptor_writer_t)writer                          \
        )

#define MP4SYS_CONSTRUCT_DESCRIPTOR( var, descriptor_name, parent, ret ) \
        mp4sys_##descriptor_name##_t *var =                              \
            mp4sys_construct_descriptor                                  \
            (                                                            \
                sizeof(mp4sys_##descriptor_name##_t),                    \
                parent,                                                  \
                mp4sys_remove_##descriptor_name,                         \
                mp4sys_write_##descriptor_name                           \
            );                                                           \
        if( !var )                                                       \
            return ret

static mp4sys_DecoderSpecificInfo_t *mp4sys_add_DecoderSpecificInfo( mp4sys_DecoderConfigDescriptor_t *dcd )
{
    if( !dcd )
        return NULL;
    MP4SYS_CONSTRUCT_DESCRIPTOR( dsi, DecoderSpecificInfo, dcd, NULL );
    dsi->header.tag = MP4SYS_DESCRIPTOR_TAG_DecSpecificInfoTag;
    if( lsmash_list_add_entry( &dcd->children, dsi ) < 0 )
    {
        mp4sys_remove_descriptor( dsi );
        return NULL;
    }
    dcd->decSpecificInfo = dsi;
    return dsi;
}

/*
    bufferSizeDB is byte unit, NOT bit unit.
    avgBitrate is 0 if VBR
*/
static mp4sys_DecoderConfigDescriptor_t *mp4sys_add_DecoderConfigDescriptor
(
    mp4sys_ES_Descriptor_t *esd
)
{
    if( !esd )
        return NULL;
    MP4SYS_CONSTRUCT_DESCRIPTOR( dcd, DecoderConfigDescriptor, esd, NULL );
    dcd->header.tag = MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag;
    if( lsmash_list_add_entry( &esd->children, dcd ) < 0 )
    {
        mp4sys_remove_descriptor( dcd );
        return NULL;
    }
    esd->decConfigDescr = dcd;
    return dcd;
}

static mp4sys_SLConfigDescriptor_t *mp4sys_add_SLConfigDescriptor( mp4sys_ES_Descriptor_t *esd )
{
    if( !esd )
        return NULL;
    MP4SYS_CONSTRUCT_DESCRIPTOR( slcd, SLConfigDescriptor, esd, NULL );
    slcd->header.tag = MP4SYS_DESCRIPTOR_TAG_SLConfigDescrTag;
    if( lsmash_list_add_entry( &esd->children, slcd ) < 0 )
    {
        mp4sys_remove_descriptor( slcd );
        return NULL;
    }
    esd->slConfigDescr = slcd;
    return slcd;
}

/* NOTE: This is only for MP4_IOD and MP4_OD, not for ISO Base Media's ObjectDescriptor and InitialObjectDescriptor */
static mp4sys_ES_ID_Inc_t *mp4sys_add_ES_ID_Inc( mp4sys_ObjectDescriptor_t *od )
{
    if( !od
     || (od->header.tag != MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag
      && od->header.tag != MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag) )
        return NULL;
    MP4SYS_CONSTRUCT_DESCRIPTOR( es_id_inc, ES_ID_Inc, od, NULL );
    es_id_inc->header.tag = MP4SYS_DESCRIPTOR_TAG_ES_ID_IncTag;
    if( lsmash_list_add_entry( &od->children, es_id_inc ) < 0 )
    {
        mp4sys_remove_descriptor( es_id_inc );
        return NULL;
    }
    if( lsmash_list_add_entry( &od->esDescr, es_id_inc ) < 0 )
    {
        lsmash_list_remove_entry_tail( &od->children );
        return NULL;
    }
    return es_id_inc;
}

int mp4sys_create_ES_ID_Inc( mp4sys_ObjectDescriptor_t *od, uint32_t Track_ID )
{
    mp4sys_ES_ID_Inc_t *es_id_inc = mp4sys_add_ES_ID_Inc( od );
    if( !es_id_inc )
        return LSMASH_ERR_NAMELESS;
    es_id_inc->Track_ID = Track_ID;
    return 0;
}

/* ES_ID of the ES Descriptor is stored as 0 when the ES Descriptor is built into sample descriptions in MP4 file format
 * since the lower 16 bits of the track_ID is used, instead of ES_ID, for the identifier of the elemental stream within the track. */
mp4sys_ES_Descriptor_t *mp4sys_create_ES_Descriptor( uint16_t ES_ID )
{
    MP4SYS_CONSTRUCT_DESCRIPTOR( esd, ES_Descriptor, NULL, NULL );
    esd->header.tag = MP4SYS_DESCRIPTOR_TAG_ES_DescrTag;
    esd->ES_ID      = ES_ID;
    return esd;
}

/* NOTE: This is only for MP4_OD, not for ISO Base Media's ObjectDescriptor */
mp4sys_ObjectDescriptor_t *mp4sys_create_ObjectDescriptor( uint16_t ObjectDescriptorID )
{
    MP4SYS_CONSTRUCT_DESCRIPTOR( od, ObjectDescriptor, NULL, NULL );
    od->header.tag                     = MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag;
    od->ObjectDescriptorID             = ObjectDescriptorID;
    od->includeInlineProfileLevelFlag  = 1; /* 1 as part of reserved flag. */
    od->ODProfileLevelIndication       = MP4SYS_OD_PLI_NONE_REQUIRED;
    od->sceneProfileLevelIndication    = MP4SYS_SCENE_PLI_NONE_REQUIRED;
    od->audioProfileLevelIndication    = MP4A_AUDIO_PLI_NONE_REQUIRED;
    od->visualProfileLevelIndication   = MP4SYS_VISUAL_PLI_NONE_REQUIRED;
    od->graphicsProfileLevelIndication = MP4SYS_GRAPHICS_PLI_NONE_REQUIRED;
    return od;
}

/* NOTE: This is only for MP4_IOD, not for Iso Base Media's InitialObjectDescriptor */
int mp4sys_to_InitialObjectDescriptor
(
    mp4sys_ObjectDescriptor_t            *od,
    uint8_t                               include_inline_pli,
    mp4sys_ODProfileLevelIndication       od_pli,
    mp4sys_sceneProfileLevelIndication    scene_pli,
    mp4a_audioProfileLevelIndication      audio_pli,
    mp4sys_visualProfileLevelIndication   visual_pli,
    mp4sys_graphicsProfileLevelIndication graph_pli
)
{
    if( !od )
        return LSMASH_ERR_NAMELESS;
    od->header.tag                     = MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag;
    od->includeInlineProfileLevelFlag  = include_inline_pli;
    od->ODProfileLevelIndication       = od_pli;
    od->sceneProfileLevelIndication    = scene_pli;
    od->audioProfileLevelIndication    = audio_pli;
    od->visualProfileLevelIndication   = visual_pli;
    od->graphicsProfileLevelIndication = graph_pli;
    return 0;
}

/*
    bufferSizeDB is byte unit, NOT bit unit.
    avgBitrate is 0 if VBR
*/
int mp4sys_update_DecoderConfigDescriptor( mp4sys_ES_Descriptor_t *esd, uint32_t bufferSizeDB, uint32_t maxBitrate, uint32_t avgBitrate )
{
    if( !esd || !esd->decConfigDescr )
        return LSMASH_ERR_NAMELESS;
    mp4sys_DecoderConfigDescriptor_t *dcd = esd->decConfigDescr;
    dcd->bufferSizeDB = bufferSizeDB;
    dcd->maxBitrate   = maxBitrate;
    dcd->avgBitrate   = avgBitrate;
    return 0;
}

void mp4sys_print_descriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent );

static void mp4sys_print_descriptor_header( FILE *fp, mp4sys_descriptor_head_t *header, int indent )
{
    static const char *descriptor_names_table[256] =
        {
            "Forbidden",
            "ObjectDescriptor",
            "InitialObjectDescriptor",
            "ES_Descriptor",
            "DecoderConfigDescriptor",
            "DecoderSpecificInfo",
            "SLConfigDescriptor",
            [0x0E] = "ES_ID_Inc",
            [0x0F] = "ES_ID_Ref",
            [0x10] = "MP4_IOD",
            [0x11] = "MP4_OD"
        };
    if( descriptor_names_table[ header->tag ] )
        lsmash_ifprintf( fp, indent, "[tag = 0x%02"PRIx8": %s]\n", header->tag, descriptor_names_table[ header->tag ] );
    else
        lsmash_ifprintf( fp, indent, "[tag = 0x%02"PRIx8"]\n", header->tag );
    lsmash_ifprintf( fp, ++indent, "expandableClassSize = %"PRIu32"\n", header->size );
}

static void mp4sys_print_DecoderSpecificInfo( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    extern void mp4a_print_AudioSpecificConfig( FILE *, uint8_t *, uint32_t, int );
    if( !descriptor->parent || descriptor->parent->header.tag != MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag )
        return;
    mp4sys_DecoderConfigDescriptor_t *dcd = (mp4sys_DecoderConfigDescriptor_t *)descriptor->parent;
    if( dcd->streamType           != MP4SYS_STREAM_TYPE_AudioStream
     || dcd->objectTypeIndication != MP4SYS_OBJECT_TYPE_Audio_ISO_14496_3 )
        return; /* We support only AudioSpecificConfig here currently. */
    mp4sys_DecoderSpecificInfo_t *dsi = (mp4sys_DecoderSpecificInfo_t *)descriptor;
    mp4a_print_AudioSpecificConfig( fp, dsi->data, dsi->header.size, indent );
}

static void mp4sys_print_DecoderConfigDescriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    mp4sys_DecoderConfigDescriptor_t *dcd = (mp4sys_DecoderConfigDescriptor_t *)descriptor;
    static const char *object_type_indication_descriptions_table[256] =
        {
            "Forbidden",
            "Systems ISO/IEC 14496-1 (a)",
            "Systems ISO/IEC 14496-1 (b)",
            "Interaction Stream",
            "Systems ISO/IEC 14496-1 Extended BIFS Configuration",
            "Systems ISO/IEC 14496-1 AFX",
            "Font Data Stream",
            "Synthesized Texture Stream",
            "Streaming Text Stream",
            "LASeR Stream",
            "Simple Aggregation Format (SAF) Stream",
            [0x20] = "Visual ISO/IEC 14496-2",
            [0x21] = "Visual ITU-T Recommendation H.264 | ISO/IEC 14496-10",
            [0x22] = "Parameter Sets for ITU-T Recommendation H.264 | ISO/IEC 14496-10",
            [0x40] = "Audio ISO/IEC 14496-3",
            [0x60] = "Visual ISO/IEC 13818-2 Simple Profile",
            [0x61] = "Visual ISO/IEC 13818-2 Main Profile",
            [0x62] = "Visual ISO/IEC 13818-2 SNR Profile",
            [0x63] = "Visual ISO/IEC 13818-2 Spatial Profile",
            [0x64] = "Visual ISO/IEC 13818-2 High Profile",
            [0x65] = "Visual ISO/IEC 13818-2 422 Profile",
            [0x66] = "Audio ISO/IEC 13818-7 Main Profile",
            [0x67] = "Audio ISO/IEC 13818-7 LowComplexity Profile",
            [0x68] = "Audio ISO/IEC 13818-7 Scaleable Sampling Rate Profile",
            [0x69] = "Audio ISO/IEC 13818-3",
            [0x6A] = "Visual ISO/IEC 11172-2",
            [0x6B] = "Audio ISO/IEC 11172-3",
            [0x6C] = "Visual ISO/IEC 10918-1",
            [0x6D] = "Portable Network Graphics",
            [0x6E] = "Visual ISO/IEC 15444-1 (JPEG 2000)",
            [0xA0] = "EVRC Voice",
            [0xA1] = "SMV Voice",
            [0xA2] = "3GPP2 Compact Multimedia Format (CMF)",
            [0xA3] = "SMPTE VC-1 Video",
            [0xA4] = "Dirac Video Coder",
            [0xA5] = "AC-3 Audio",
            [0xA6] = "Enhanced AC-3 audio",
            [0xA7] = "DRA Audio",
            [0xA8] = "ITU G.719 Audio",
            [0xA9] = "DTS Coherent Acoustics audio",
            [0xAA] = "DTS-HD High Resolution Audio",
            [0xAB] = "DTS-HD Master Audio",
            [0xAC] = "DTS Express low bit rate audio",
            [0xE1] = "13K Voice",
            [0xFF] = "no object type specified"
        };
    static const char *stream_type_descriptions_table[64] =
        {
            "Forbidden",
            "ObjectDescriptorStream",
            "ClockReferenceStream",
            "SceneDescriptionStream",
            "VisualStream",
            "AudioStream",
            "MPEG7Stream",
            "IPMPStream",
            "ObjectContentInfoStream",
            "MPEGJStream",
            "Interaction Stream",
            "IPMPToolStream",
            "FontDataStream",
            "StreamingText"
        };
    if( object_type_indication_descriptions_table[ dcd->objectTypeIndication ] )
        lsmash_ifprintf( fp, indent, "objectTypeIndication = 0x%02"PRIx8" (%s)\n", dcd->objectTypeIndication, object_type_indication_descriptions_table[ dcd->objectTypeIndication ] );
    else
        lsmash_ifprintf( fp, indent, "objectTypeIndication = 0x%02"PRIx8"\n", dcd->objectTypeIndication );
    if( stream_type_descriptions_table[ dcd->streamType ] )
        lsmash_ifprintf( fp, indent, "streamType = 0x%02"PRIx8" (%s)\n", dcd->streamType, stream_type_descriptions_table[ dcd->streamType ] );
    else
        lsmash_ifprintf( fp, indent, "streamType = 0x%02"PRIx8"\n", dcd->streamType );
    lsmash_ifprintf( fp, indent, "upStream = %"PRIu8"\n", dcd->upStream );
    lsmash_ifprintf( fp, indent, "reserved = %"PRIu8"\n", dcd->reserved );
    lsmash_ifprintf( fp, indent, "bufferSizeDB = %"PRIu32"\n", dcd->bufferSizeDB );
    lsmash_ifprintf( fp, indent, "maxBitrate = %"PRIu32"\n", dcd->maxBitrate );
    lsmash_ifprintf( fp, indent, "avgBitrate = %"PRIu32"%s\n", dcd->avgBitrate, dcd->avgBitrate ? "" : " (variable bitrate)" );
}

static void mp4sys_print_SLConfigDescriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    mp4sys_SLConfigDescriptor_t *slcd = (mp4sys_SLConfigDescriptor_t *)descriptor;
    lsmash_ifprintf( fp, indent, "predefined = %"PRIu8"\n", slcd->predefined );
    if( slcd->predefined == 0 )
    {
        lsmash_ifprintf( fp, indent, "useAccessUnitStartFlag = %"PRIu8"\n", slcd->useAccessUnitStartFlag );
        lsmash_ifprintf( fp, indent, "useAccessUnitEndFlag = %"PRIu8"\n", slcd->useAccessUnitEndFlag );
        lsmash_ifprintf( fp, indent, "useRandomAccessPointFlag = %"PRIu8"\n", slcd->useRandomAccessPointFlag );
        lsmash_ifprintf( fp, indent, "hasRandomAccessUnitsOnlyFlag = %"PRIu8"\n", slcd->hasRandomAccessUnitsOnlyFlag );
        lsmash_ifprintf( fp, indent, "usePaddingFlag = %"PRIu8"\n", slcd->usePaddingFlag );
        lsmash_ifprintf( fp, indent, "useTimeStampsFlag = %"PRIu8"\n", slcd->useTimeStampsFlag );
        lsmash_ifprintf( fp, indent, "useIdleFlag = %"PRIu8"\n", slcd->useIdleFlag );
        lsmash_ifprintf( fp, indent, "durationFlag = %"PRIu8"\n", slcd->durationFlag );
        lsmash_ifprintf( fp, indent, "timeStampResolution = %"PRIu32"\n", slcd->timeStampResolution );
        lsmash_ifprintf( fp, indent, "OCRResolution = %"PRIu32"\n", slcd->OCRResolution );
        lsmash_ifprintf( fp, indent, "timeStampLength = %"PRIu8"\n", slcd->timeStampLength );
        lsmash_ifprintf( fp, indent, "OCRLength = %"PRIu8"\n", slcd->OCRLength );
        lsmash_ifprintf( fp, indent, "AU_Length = %"PRIu8"\n", slcd->AU_Length );
        lsmash_ifprintf( fp, indent, "instantBitrateLength = %"PRIu8"\n", slcd->instantBitrateLength );
        lsmash_ifprintf( fp, indent, "degradationPriorityLength = %"PRIu8"\n", slcd->degradationPriorityLength );
        lsmash_ifprintf( fp, indent, "AU_seqNumLength = %"PRIu8"\n", slcd->AU_seqNumLength );
        lsmash_ifprintf( fp, indent, "packetSeqNumLength = %"PRIu8"\n", slcd->packetSeqNumLength );
        lsmash_ifprintf( fp, indent, "reserved = 0x%01"PRIx8"\n", slcd->reserved );
    }
    if( slcd->durationFlag )
    {
        lsmash_ifprintf( fp, indent, "timeScale = %"PRIu32"\n", slcd->timeScale );
        lsmash_ifprintf( fp, indent, "accessUnitDuration = %"PRIu16"\n", slcd->accessUnitDuration );
        lsmash_ifprintf( fp, indent, "compositionUnitDuration = %"PRIu16"\n", slcd->compositionUnitDuration );
    }
    if( !slcd->useTimeStampsFlag )
    {
        lsmash_ifprintf( fp, indent, "startDecodingTimeStamp = %"PRIu64"\n", slcd->startDecodingTimeStamp );
        lsmash_ifprintf( fp, indent, "startCompositionTimeStamp = %"PRIu64"\n", slcd->startCompositionTimeStamp );
    }
}

static void mp4sys_print_ES_Descriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    mp4sys_ES_Descriptor_t *esd = (mp4sys_ES_Descriptor_t *)descriptor;
    lsmash_ifprintf( fp, indent, "ES_ID = %"PRIu16"\n", esd->ES_ID );
    lsmash_ifprintf( fp, indent, "streamDependenceFlag = %"PRIu8"\n", esd->streamDependenceFlag );
    lsmash_ifprintf( fp, indent, "URL_Flag = %"PRIu8"\n", esd->URL_Flag );
    lsmash_ifprintf( fp, indent, "OCRstreamFlag = %"PRIu8"\n", esd->OCRstreamFlag );
    lsmash_ifprintf( fp, indent, "streamPriority = %"PRIu8"\n", esd->streamPriority );
    if( esd->streamDependenceFlag )
        lsmash_ifprintf( fp, indent, "dependsOn_ES_ID = %"PRIu16"\n", esd->dependsOn_ES_ID );
    if( esd->URL_Flag )
    {
        lsmash_ifprintf( fp, indent, "URLlength = %"PRIu8"\n", esd->URLlength );
        lsmash_ifprintf( fp, indent, "URLstring = %s\n", esd->URLstring );
    }
    if( esd->OCRstreamFlag )
        lsmash_ifprintf( fp, indent, "OCR_ES_Id = %"PRIu16"\n", esd->OCR_ES_Id );
}

static void mp4sys_print_ES_ID_Inc( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    mp4sys_ES_ID_Inc_t *es_id_inc = (mp4sys_ES_ID_Inc_t *)descriptor;
    lsmash_ifprintf( fp, indent, "Track_ID = %"PRIu32"\n", es_id_inc->Track_ID );
}

static void mp4sys_print_ObjectDescriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    mp4sys_ObjectDescriptor_t *od = (mp4sys_ObjectDescriptor_t *)descriptor;
    lsmash_ifprintf( fp, indent, "ObjectDescriptorID = %"PRIu16"\n", od->ObjectDescriptorID );
    lsmash_ifprintf( fp, indent, "URL_Flag = %"PRIu8"\n", od->URL_Flag );
    if( od->header.tag == MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag
     || od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag )
    {
        lsmash_ifprintf( fp, indent, "includeInlineProfileLevelFlag = %"PRIu8"\n", od->includeInlineProfileLevelFlag );
        lsmash_ifprintf( fp, indent, "reserved = 0x%01"PRIx8"\n", od->reserved );
    }
    else
        lsmash_ifprintf( fp, indent, "reserved = 0x%02"PRIx8"\n", od->reserved | (od->includeInlineProfileLevelFlag << 4) );
    if( od->URL_Flag )
    {
        lsmash_ifprintf( fp, indent, "URLlength = %"PRIu8"\n", od->URLlength );
        lsmash_ifprintf( fp, indent, "URLstring = %s\n", od->URLstring );
    }
    else
    {
        if( od->header.tag == MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag
         || od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag )
        {
            lsmash_ifprintf( fp, indent, "ODProfileLevelIndication = 0x%02"PRIx8"\n",       od->ODProfileLevelIndication );
            lsmash_ifprintf( fp, indent, "sceneProfileLevelIndication = 0x%02"PRIx8"\n",    od->sceneProfileLevelIndication );
            lsmash_ifprintf( fp, indent, "audioProfileLevelIndication = 0x%02"PRIx8"\n",    od->audioProfileLevelIndication );
            lsmash_ifprintf( fp, indent, "visualProfileLevelIndication = 0x%02"PRIx8"\n",   od->visualProfileLevelIndication );
            lsmash_ifprintf( fp, indent, "graphicsProfileLevelIndication = 0x%02"PRIx8"\n", od->graphicsProfileLevelIndication );
        }
    }
}

void mp4sys_print_descriptor( FILE *fp, mp4sys_descriptor_t *descriptor, int indent )
{
    if( !descriptor )
        return;
    mp4sys_print_descriptor_header( fp, &descriptor->header, indent++ );
    switch( descriptor->header.tag )
    {
        case MP4SYS_DESCRIPTOR_TAG_ObjectDescrTag        :
        case MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag :
        case MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag            :
        case MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag           :
            mp4sys_print_ObjectDescriptor( fp, descriptor, indent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_ES_DescrTag :
            mp4sys_print_ES_Descriptor( fp, descriptor, indent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag :
            mp4sys_print_DecoderConfigDescriptor( fp, descriptor, indent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_DecSpecificInfoTag :
            mp4sys_print_DecoderSpecificInfo( fp, descriptor, indent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_SLConfigDescrTag :
            mp4sys_print_SLConfigDescriptor( fp, descriptor, indent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_ES_ID_IncTag :
            mp4sys_print_ES_ID_Inc( fp, descriptor, indent );
            break;
        default :
            break;
    }
    for( lsmash_entry_t *entry = descriptor->children.head; entry; entry = entry->next )
        if( entry->data )
            mp4sys_print_descriptor( fp, entry->data, indent );
}

int mp4sys_print_codec_specific( FILE *fp, lsmash_file_t *file, isom_box_t *box, int level )
{
    assert( !(box->manager & LSMASH_BINARY_CODED_BOX) );
    isom_esds_t *esds = (isom_esds_t *)box;
    int indent = level;
    lsmash_ifprintf( fp, indent++, "[%s: Elemental Stream Descriptor Box]\n", isom_4cc2str( esds->type.fourcc ) );
    lsmash_ifprintf( fp, indent, "position = %"PRIu64"\n", esds->pos );
    lsmash_ifprintf( fp, indent, "size = %"PRIu64"\n", esds->size );
    lsmash_ifprintf( fp, indent, "version = %"PRIu8"\n", esds->version );
    lsmash_ifprintf( fp, indent, "flags = 0x%06"PRIx32"\n", esds->flags & 0x00ffffff );
    mp4sys_print_descriptor( fp, (mp4sys_descriptor_t *)esds->ES, indent );
    return 0;
}

mp4sys_descriptor_t *mp4sys_get_descriptor( lsmash_bs_t *bs, void *parent );

static void mp4sys_get_descriptor_header( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header )
{
    header->tag  = lsmash_bs_get_byte( bs );
    uint8_t temp = lsmash_bs_get_byte( bs );
    int nextByte = temp & 0x80;
    uint32_t sizeOfInstance = temp & 0x7F;
    while( nextByte )
    {
        temp = lsmash_bs_get_byte( bs );
        nextByte = temp & 0x80;
        sizeOfInstance = (sizeOfInstance << 7) | (temp & 0x7F);
    }
    header->size = sizeOfInstance;
}

static mp4sys_DecoderSpecificInfo_t *mp4sys_get_DecoderSpecificInfo( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    mp4sys_DecoderSpecificInfo_t *dsi = mp4sys_add_DecoderSpecificInfo( parent );
    if( !dsi )
        return NULL;
    dsi->header.size = header->size;
    if( dsi->header.size )
    {
        dsi->data = lsmash_bs_get_bytes( bs, dsi->header.size );
        if( !dsi->data )
        {
            mp4sys_remove_descriptor( dsi );
            return NULL;
        }
    }
    return dsi;
}

static mp4sys_DecoderConfigDescriptor_t *mp4sys_get_DecoderConfigDescriptor( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    mp4sys_DecoderConfigDescriptor_t *dcd = mp4sys_add_DecoderConfigDescriptor( parent );
    if( !dcd )
        return NULL;
    uint64_t end_pos = header->size + lsmash_bs_count( bs );
    dcd->header.size = header->size;
    dcd->objectTypeIndication = lsmash_bs_get_byte( bs );
    uint8_t temp              = lsmash_bs_get_byte( bs );
    dcd->streamType = (temp >> 2) & 0x3F;
    dcd->upStream   = (temp >> 1) & 0x01;
    dcd->reserved   =  temp       & 0x01;
    dcd->bufferSizeDB         = lsmash_bs_get_be24( bs );
    dcd->maxBitrate           = lsmash_bs_get_be32( bs );
    dcd->avgBitrate           = lsmash_bs_get_be32( bs );
    while( lsmash_bs_count( bs ) < end_pos )
    {
        mp4sys_descriptor_t *desc = mp4sys_get_descriptor( bs, dcd );
        if( desc )
        {
            if( desc->header.tag == MP4SYS_DESCRIPTOR_TAG_DecSpecificInfoTag )
                dcd->decSpecificInfo = (mp4sys_DecoderSpecificInfo_t *)desc;
            else
                mp4sys_remove_descriptor( desc );
        }
        else
            break;
    }
    return dcd;
}

static mp4sys_SLConfigDescriptor_t *mp4sys_get_SLConfigDescriptor( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    mp4sys_SLConfigDescriptor_t *slcd = mp4sys_add_SLConfigDescriptor( parent );
    if( !slcd )
        return NULL;
    slcd->header.size = header->size;
    slcd->predefined = lsmash_bs_get_byte( bs );
    if( slcd->predefined == 0x00 )
    {
        uint8_t temp8              = lsmash_bs_get_byte( bs );
        slcd->useAccessUnitStartFlag       = (temp8 >> 7) & 0x01;
        slcd->useAccessUnitEndFlag         = (temp8 >> 6) & 0x01;
        slcd->useRandomAccessPointFlag     = (temp8 >> 5) & 0x01;
        slcd->hasRandomAccessUnitsOnlyFlag = (temp8 >> 4) & 0x01;
        slcd->usePaddingFlag               = (temp8 >> 3) & 0x01;
        slcd->useTimeStampsFlag            = (temp8 >> 2) & 0x01;
        slcd->useIdleFlag                  = (temp8 >> 1) & 0x01;
        slcd->durationFlag                 =  temp8       & 0x01;
        slcd->timeStampResolution  = lsmash_bs_get_be32( bs );
        slcd->OCRResolution        = lsmash_bs_get_be32( bs );
        slcd->timeStampLength      = lsmash_bs_get_byte( bs );
        slcd->OCRLength            = lsmash_bs_get_byte( bs );
        slcd->AU_Length            = lsmash_bs_get_byte( bs );
        slcd->instantBitrateLength = lsmash_bs_get_byte( bs );
        uint16_t temp16            = lsmash_bs_get_be16( bs );
        slcd->degradationPriorityLength = (temp16 >> 12) & 0x0F;
        slcd->AU_seqNumLength           = (temp16 >>  7) & 0x1F;
        slcd->packetSeqNumLength        = (temp16 >>  2) & 0x1F;
        slcd->reserved                  =  temp16        & 0x03;
    }
    else if( slcd->predefined == 0x01 )
    {
        slcd->timeStampResolution  = 1000;
        slcd->timeStampLength      = 32;
    }
    else if( slcd->predefined == 0x02 )
        slcd->useTimeStampsFlag = 1;
    if( slcd->durationFlag )
    {
        slcd->timeScale               = lsmash_bs_get_be32( bs );
        slcd->accessUnitDuration      = lsmash_bs_get_be16( bs );
        slcd->compositionUnitDuration = lsmash_bs_get_be16( bs );
    }
    if( !slcd->useTimeStampsFlag )
    {
        lsmash_bits_t *bits = lsmash_bits_create( bs );
        if( !bits )
        {
            mp4sys_remove_descriptor( slcd );
            return NULL;
        }
        slcd->startDecodingTimeStamp    = lsmash_bits_get( bits, slcd->timeStampLength );
        slcd->startCompositionTimeStamp = lsmash_bits_get( bits, slcd->timeStampLength );
        lsmash_bits_cleanup( bits );
    }
    return slcd;
}

static mp4sys_ES_Descriptor_t *mp4sys_get_ES_Descriptor( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    MP4SYS_CONSTRUCT_DESCRIPTOR( esd, ES_Descriptor, parent, NULL );
    if( parent && lsmash_list_add_entry( &((mp4sys_descriptor_t *)parent)->children, esd ) < 0 )
    {
        mp4sys_remove_descriptor( esd );
        return NULL;
    }
    uint64_t end_pos = header->size + lsmash_bs_count( bs );
    esd->header  = *header;
    esd->ES_ID   = lsmash_bs_get_be16( bs );
    uint8_t temp = lsmash_bs_get_byte( bs );
    esd->streamDependenceFlag = (temp >> 7) & 0x01;
    esd->URL_Flag             = (temp >> 6) & 0x01;
    esd->OCRstreamFlag        = (temp >> 5) & 0x01;
    esd->streamPriority       =  temp       & 0x1F;
    if( esd->streamDependenceFlag )
        esd->dependsOn_ES_ID = lsmash_bs_get_be16( bs );
    if( esd->URL_Flag )
    {
        size_t length = lsmash_bs_get_byte( bs );
        lsmash_bs_read_data( bs, (uint8_t *)esd->URLstring, &length );
        esd->URLlength = length;
    }
    if( esd->OCRstreamFlag )
        esd->OCR_ES_Id = lsmash_bs_get_be16( bs );
    /* DecoderConfigDescriptor and SLConfigDescriptor are mandatory. */
    while( lsmash_bs_count( bs ) < end_pos )
    {
        mp4sys_descriptor_t *desc = mp4sys_get_descriptor( bs, esd );
        if( desc )
        {
            if( desc->header.tag == MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag )
                esd->decConfigDescr = (mp4sys_DecoderConfigDescriptor_t *)desc;
            else if( desc->header.tag == MP4SYS_DESCRIPTOR_TAG_SLConfigDescrTag )
                esd->slConfigDescr = (mp4sys_SLConfigDescriptor_t *)desc;
            else
                mp4sys_remove_descriptor( desc );
        }
        else
            break;
    }
    if( !esd->decConfigDescr || !esd->slConfigDescr )
    {
        mp4sys_remove_descriptor( esd );
        return NULL;
    }
    return esd;
}

static mp4sys_ES_ID_Inc_t *mp4sys_get_ES_ID_Inc( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    mp4sys_ES_ID_Inc_t *es_id_inc = mp4sys_add_ES_ID_Inc( parent );
    if( !es_id_inc )
        return NULL;
    es_id_inc->header.size = header->size;
    es_id_inc->Track_ID = lsmash_bs_get_be32( bs );
    return es_id_inc;
}

static mp4sys_ObjectDescriptor_t *mp4sys_get_ObjectDescriptor( lsmash_bs_t *bs, mp4sys_descriptor_head_t *header, void *parent )
{
    MP4SYS_CONSTRUCT_DESCRIPTOR( od, ObjectDescriptor, parent, NULL );
    if( parent && lsmash_list_add_entry( &((mp4sys_descriptor_t *)parent)->children, od ) < 0 )
    {
        mp4sys_remove_descriptor( od );
        return NULL;
    }
    od->header = *header;
    uint64_t end_pos = header->size + lsmash_bs_count( bs );
    uint16_t temp16 = lsmash_bs_get_be16( bs );
    od->ObjectDescriptorID            = (temp16 >> 6) & 0x03FF;
    od->URL_Flag                      = (temp16 >> 5) & 0x0001;
    od->includeInlineProfileLevelFlag = (temp16 >> 4) & 0x0001;
    od->reserved                      =  temp16       & 0x000F;
    if( od->URL_Flag )
    {
        size_t length = lsmash_bs_get_byte( bs );
        lsmash_bs_read_data( bs, (uint8_t *)od->URLstring, &length );
        od->URLlength = length;
    }
    else
    {
        if( od->header.tag == MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag
         || od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag )
        {
            od->ODProfileLevelIndication       = lsmash_bs_get_byte( bs );
            od->sceneProfileLevelIndication    = lsmash_bs_get_byte( bs );
            od->audioProfileLevelIndication    = lsmash_bs_get_byte( bs );
            od->visualProfileLevelIndication   = lsmash_bs_get_byte( bs );
            od->graphicsProfileLevelIndication = lsmash_bs_get_byte( bs );
        }
        const mp4sys_descriptor_tag at_least_one_descriptor_tag
            = od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag
           || od->header.tag == MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag
            ? MP4SYS_DESCRIPTOR_TAG_ES_ID_IncTag
            : MP4SYS_DESCRIPTOR_TAG_ES_DescrTag;
        while( lsmash_bs_count( bs ) < end_pos && od->esDescr.entry_count < 255 )
        {
            mp4sys_descriptor_t *desc = mp4sys_get_descriptor( bs, od );
            if( !desc )
                break;
            if( desc->header.tag != at_least_one_descriptor_tag )
            {
                mp4sys_remove_descriptor( desc );
                break;
            }
        }
    }
    return od;
}

mp4sys_descriptor_t *mp4sys_get_descriptor( lsmash_bs_t *bs, void *parent )
{
    mp4sys_descriptor_head_t header;
    mp4sys_get_descriptor_header( bs, &header );
    uint64_t end_pos = header.size + lsmash_bs_count( bs );
    mp4sys_descriptor_t *desc;
    switch( header.tag )
    {
        case MP4SYS_DESCRIPTOR_TAG_ObjectDescrTag        :
        case MP4SYS_DESCRIPTOR_TAG_InitialObjectDescrTag :
        case MP4SYS_DESCRIPTOR_TAG_MP4_OD_Tag            :
        case MP4SYS_DESCRIPTOR_TAG_MP4_IOD_Tag           :
            desc = (mp4sys_descriptor_t *)mp4sys_get_ObjectDescriptor( bs, &header, parent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_ES_DescrTag :
            desc = (mp4sys_descriptor_t *)mp4sys_get_ES_Descriptor( bs, &header, parent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_DecoderConfigDescrTag :
            desc = (mp4sys_descriptor_t *)mp4sys_get_DecoderConfigDescriptor( bs, &header, parent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_DecSpecificInfoTag :
            desc = (mp4sys_descriptor_t *)mp4sys_get_DecoderSpecificInfo( bs, &header, parent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_SLConfigDescrTag :
            desc = (mp4sys_descriptor_t *)mp4sys_get_SLConfigDescriptor( bs, &header, parent );
            break;
        case MP4SYS_DESCRIPTOR_TAG_ES_ID_IncTag :
            desc = (mp4sys_descriptor_t *)mp4sys_get_ES_ID_Inc( bs, &header, parent );
            break;
        default :
            desc = lsmash_malloc_zero( sizeof(mp4sys_descriptor_t) );
            if( desc )
            {
                desc->parent = parent;
                desc->header = header;
            }
            break;
    }
    /* Skip extra bytes if present. */
    uint64_t skip_bytes = end_pos - lsmash_bs_count( bs );
    if( skip_bytes )
    {
        fprintf( stderr, "[MPEG-4 Systems Descriptor Tag = 0x%02"PRIx8"] has more bytes than expected: %"PRId64"\n", header.tag, skip_bytes );
        if( !bs->unseekable )
        {
            /* The stream is seekable. So, skip by seeking the stream. */
            uint64_t start = lsmash_bs_get_stream_pos( bs );
            lsmash_bs_read_seek( bs, skip_bytes, SEEK_CUR );
            uint64_t end   = lsmash_bs_get_stream_pos( bs );
            bs->buffer.count += end - start;
        }
        else
            /* The stream is unseekable. So, skip by reading the stream. */
            lsmash_bs_skip_bytes_64( bs, skip_bytes );
    }
    return desc;
}

static uint8_t *mp4sys_export_DecoderSpecificInfo( mp4sys_ES_Descriptor_t *esd, uint32_t *dsi_payload_length )
{
    if( !esd || !esd->decConfigDescr || !esd->decConfigDescr->decSpecificInfo )
        return NULL;
    mp4sys_DecoderSpecificInfo_t *dsi = (mp4sys_DecoderSpecificInfo_t *)esd->decConfigDescr->decSpecificInfo;
    uint8_t *dsi_payload = NULL;
    /* DecoderSpecificInfo can be absent. */
    if( dsi->header.size )
    {
        dsi_payload = lsmash_memdup( dsi->data, dsi->header.size );
        if( !dsi_payload )
            return NULL;
    }
    if( dsi_payload_length )
        *dsi_payload_length = dsi->header.size;
    return dsi_payload;
}

/* Sumamry is needed to decide ProfileLevelIndication.
 * Currently, support audio's only. */
int mp4sys_setup_summary_from_DecoderSpecificInfo( lsmash_audio_summary_t *summary, mp4sys_ES_Descriptor_t *esd )
{
    uint32_t dsi_payload_length = UINT32_MAX;       /* arbitrary */
    uint8_t *dsi_payload = mp4sys_export_DecoderSpecificInfo( esd, &dsi_payload_length );
    if( !dsi_payload && dsi_payload_length )
        return LSMASH_ERR_NAMELESS;
    int err = 0;
    if( dsi_payload_length )
    {
        lsmash_codec_specific_t *cs = lsmash_create_codec_specific_data( LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG,
                                                                         LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
        if( !cs )
        {
            err = LSMASH_ERR_MEMORY_ALLOC;
            goto fail;
        }
        lsmash_mp4sys_decoder_parameters_t *params = (lsmash_mp4sys_decoder_parameters_t *)cs->data.structured;
        mp4sys_DecoderConfigDescriptor_t   *dcd    = esd->decConfigDescr;
        params->objectTypeIndication = dcd->objectTypeIndication;
        params->streamType           = dcd->streamType;
        params->bufferSizeDB         = dcd->bufferSizeDB;
        params->maxBitrate           = dcd->maxBitrate;
        params->avgBitrate           = dcd->avgBitrate;
        if( (err = mp4a_setup_summary_from_AudioSpecificConfig( summary, dsi_payload, dsi_payload_length )) < 0
         || (err = lsmash_set_mp4sys_decoder_specific_info( params, dsi_payload, dsi_payload_length ))      < 0
         || (err = lsmash_list_add_entry( &summary->opaque->list, cs ))                                          < 0 )
        {
            lsmash_destroy_codec_specific_data( cs );
            goto fail;
        }
    }
fail:
    lsmash_free( dsi_payload );
    return err;
}

/**** following functions are for facilitation purpose ****/

mp4sys_ES_Descriptor_t *mp4sys_setup_ES_Descriptor( mp4sys_ES_Descriptor_params_t *params )
{
    if( !params )
        return NULL;
    mp4sys_ES_Descriptor_t *esd = mp4sys_create_ES_Descriptor( params->ES_ID );
    if( !esd )
        return NULL;
    /* DecoderConfigDescriptor */
    mp4sys_DecoderConfigDescriptor_t *dcd = mp4sys_add_DecoderConfigDescriptor( esd );
    if( !dcd )
        goto fail;
    dcd->objectTypeIndication = params->objectTypeIndication;
    dcd->streamType           = params->streamType;
    dcd->upStream             = 0;
    dcd->reserved             = 1;
    dcd->bufferSizeDB         = params->bufferSizeDB;
    dcd->maxBitrate           = params->maxBitrate;
    dcd->avgBitrate           = params->avgBitrate;
    /* DecoderSpecificInfo */
    if( params->dsi_payload && params->dsi_payload_length != 0 )
    {
        mp4sys_DecoderSpecificInfo_t *dsi = mp4sys_add_DecoderSpecificInfo( dcd );
        if( !dsi )
            goto fail;
        dsi->data = lsmash_memdup( params->dsi_payload, params->dsi_payload_length );
        if( !dsi->data )
            goto fail;
        dsi->header.size = params->dsi_payload_length;
    }
    /* SLConfigDescriptor */
    {
        mp4sys_SLConfigDescriptor_t *slcd = mp4sys_add_SLConfigDescriptor( esd );
        if( !slcd )
            goto fail;
        slcd->predefined        = 0x02;     /* MP4 file which does not use URL_Flag shall have constant value 0x02 */
        slcd->useTimeStampsFlag = 1;        /* set to 1 if predefined == 2 */
    }
    return esd;
fail:
    mp4sys_remove_descriptor( esd );
    return NULL;
}

int lsmash_set_mp4sys_decoder_specific_info( lsmash_mp4sys_decoder_parameters_t *param, uint8_t *payload, uint32_t payload_length )
{
    if( !param || !payload || payload_length == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !param->dsi )
    {
        param->dsi = lsmash_malloc_zero( sizeof(lsmash_mp4sys_decoder_specific_info_t) );
        if( !param->dsi )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    else
    {
        lsmash_freep( &param->dsi->payload );
        param->dsi->payload_length = 0;
    }
    param->dsi->payload = lsmash_memdup( payload, payload_length );
    if( !param->dsi->payload )
        return LSMASH_ERR_MEMORY_ALLOC;
    param->dsi->payload_length = payload_length;
    return 0;
}

void lsmash_destroy_mp4sys_decoder_specific_info( lsmash_mp4sys_decoder_parameters_t *param )
{
    if( !param || !param->dsi )
        return;
    lsmash_free( param->dsi->payload );
    lsmash_freep( &param->dsi );
}

void mp4sys_destruct_decoder_config( void *data )
{
    if( !data )
        return;
    lsmash_destroy_mp4sys_decoder_specific_info( data );
    lsmash_free( data );
}

uint8_t *lsmash_create_mp4sys_decoder_config( lsmash_mp4sys_decoder_parameters_t *param, uint32_t *data_length )
{
    if( !param || !data_length )
        return NULL;
    mp4sys_ES_Descriptor_params_t esd_param = { 0 };
    esd_param.ES_ID                = 0; /* Within sample description, ES_ID is stored as 0. */
    esd_param.objectTypeIndication = param->objectTypeIndication;
    esd_param.streamType           = param->streamType;
    esd_param.bufferSizeDB         = param->bufferSizeDB;
    esd_param.maxBitrate           = param->maxBitrate;
    esd_param.avgBitrate           = param->avgBitrate;
    if( param->dsi
     && param->dsi->payload
     && param->dsi->payload_length )
    {
        esd_param.dsi_payload        = param->dsi->payload;
        esd_param.dsi_payload_length = param->dsi->payload_length;
    }
    mp4sys_ES_Descriptor_t *esd = mp4sys_setup_ES_Descriptor( &esd_param );
    if( !esd )
        return NULL;
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
    {
        mp4sys_remove_descriptor( esd );
        return NULL;
    }
    lsmash_bs_put_be32( bs, 0 );    /* update later */
    lsmash_bs_put_be32( bs, ISOM_BOX_TYPE_ESDS.fourcc );
    lsmash_bs_put_be32( bs, 0 );
    mp4sys_update_descriptor_size( esd );
    mp4sys_write_descriptor( bs, esd );
    mp4sys_remove_descriptor( esd );
    uint8_t *data = lsmash_bs_export_data( bs, data_length );
    lsmash_bs_cleanup( bs );
    if( !data )
        return NULL;
    /* Update box size. */
    LSMASH_SET_BE32( data, *data_length );
    return data;
}

int mp4sys_construct_decoder_config( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( dst && dst->data.structured && src && src->data.unstructured );
    if( src->size < ISOM_FULLBOX_COMMON_SIZE + 23 )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_mp4sys_decoder_parameters_t *param = (lsmash_mp4sys_decoder_parameters_t *)dst->data.structured;
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
    data += 4;  /* Skip version and flags. */
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = lsmash_bs_import_data( bs, data, src->size - (data - src->data.unstructured) );
    if( err < 0 )
    {
        lsmash_bs_cleanup( bs );
        return err;
    }
    mp4sys_ES_Descriptor_t *esd = (mp4sys_ES_Descriptor_t *)mp4sys_get_descriptor( bs, NULL );
    lsmash_bs_cleanup( bs );
    if( !esd || esd->header.tag != MP4SYS_DESCRIPTOR_TAG_ES_DescrTag || !esd->decConfigDescr )
        return LSMASH_ERR_INVALID_DATA;
    mp4sys_DecoderConfigDescriptor_t *dcd = esd->decConfigDescr;
    param->objectTypeIndication = dcd->objectTypeIndication;
    param->streamType           = dcd->streamType;
    param->bufferSizeDB         = dcd->bufferSizeDB;
    param->maxBitrate           = dcd->maxBitrate;
    param->avgBitrate           = dcd->avgBitrate;
    mp4sys_DecoderSpecificInfo_t *dsi = dcd->decSpecificInfo;
    if( dsi
     && dsi->header.size
     && dsi->data
     && (err = lsmash_set_mp4sys_decoder_specific_info( param, dsi->data, dsi->header.size )) < 0 )
    {
        mp4sys_remove_descriptor( esd );
        return err;
    }
    mp4sys_remove_descriptor( esd );
    return 0;
}

int mp4sys_copy_decoder_config( lsmash_codec_specific_t *dst, lsmash_codec_specific_t *src )
{
    assert( src && src->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && src->data.structured );
    assert( dst && dst->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED && dst->data.structured );
    lsmash_mp4sys_decoder_parameters_t *src_data = (lsmash_mp4sys_decoder_parameters_t *)src->data.structured;
    lsmash_mp4sys_decoder_parameters_t *dst_data = (lsmash_mp4sys_decoder_parameters_t *)dst->data.structured;
    lsmash_destroy_mp4sys_decoder_specific_info( dst_data );
    *dst_data = *src_data;
    dst_data->dsi = NULL;
    if( !src_data->dsi || !src_data->dsi->payload || src_data->dsi->payload_length == 0 )
        return 0;
    return lsmash_set_mp4sys_decoder_specific_info( dst_data, src_data->dsi->payload, src_data->dsi->payload_length );
}

lsmash_mp4sys_object_type_indication lsmash_mp4sys_get_object_type_indication( lsmash_summary_t *summary )
{
    if( !summary )
        return MP4SYS_OBJECT_TYPE_Forbidden;
    lsmash_codec_specific_t *orig = isom_get_codec_specific( summary->opaque, LSMASH_CODEC_SPECIFIC_DATA_TYPE_MP4SYS_DECODER_CONFIG );
    if( !orig )
        return MP4SYS_OBJECT_TYPE_Forbidden;
    /* Found decoder configuration.
     * Let's get objectTypeIndication. */
    lsmash_mp4sys_object_type_indication objectTypeIndication;
    if( orig->format == LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED )
        objectTypeIndication = ((lsmash_mp4sys_decoder_parameters_t *)orig->data.structured)->objectTypeIndication;
    else
    {
        lsmash_codec_specific_t *conv = lsmash_convert_codec_specific_format( orig, LSMASH_CODEC_SPECIFIC_FORMAT_STRUCTURED );
        if( !conv )
            return MP4SYS_OBJECT_TYPE_Forbidden;
        objectTypeIndication = ((lsmash_mp4sys_decoder_parameters_t *)conv->data.structured)->objectTypeIndication;
        lsmash_destroy_codec_specific_data( conv );
    }
    return objectTypeIndication;
}

int lsmash_get_mp4sys_decoder_specific_info( lsmash_mp4sys_decoder_parameters_t *param, uint8_t **payload, uint32_t *payload_length )
{
    if( !param || !payload || !payload_length )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !param->dsi || !param->dsi->payload || param->dsi->payload_length == 0 )
    {
        *payload = NULL;
        *payload_length = 0;
        return 0;
    }
    uint8_t *temp = lsmash_memdup( param->dsi->payload, param->dsi->payload_length );
    if( !temp )
        return LSMASH_ERR_MEMORY_ALLOC;
    *payload = temp;
    *payload_length = param->dsi->payload_length;
    return 0;
}

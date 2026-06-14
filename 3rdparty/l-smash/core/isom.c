/*****************************************************************************
 * isom.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
 * Contributors: Takashi Hirata <silverfilain@gmail.com>
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

#include "box.h"
#include "box_default.h"
#include "file.h"
#include "fragment.h"
#include "read.h"
#include "timeline.h"
#include "write.h"

#include "codecs/mp4a.h"
#include "codecs/mp4sys.h"
#include "codecs/description.h"

/*---- ----*/

#define RTP_SAMPLE_HEADER_SIZE    4
#define RTP_PACKET_SIZE           12 /* a structure in Hint track sample */
#define RTP_HEADER_SIZE           12
#define RTP_CONSTRUCTOR_SIZE      16

int isom_check_initializer_present( lsmash_root_t *root )
{
    if( LSMASH_IS_NON_EXISTING_BOX( root )
     || LSMASH_IS_NON_EXISTING_BOX( root->file )
     || LSMASH_IS_NON_EXISTING_BOX( root->file->initializer ) )
        return LSMASH_ERR_NAMELESS;
    return 0;
}

isom_trak_t *isom_get_trak( lsmash_file_t *file, uint32_t track_ID )
{
    if( track_ID == 0
     || LSMASH_IS_NON_EXISTING_BOX( file->moov )
     || file != file->initializer )
        return isom_non_existing_trak();
    for( lsmash_entry_t *entry = file->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
            return isom_non_existing_trak();
        if( trak->tkhd->track_ID == track_ID )
            return trak;
    }
    return isom_non_existing_trak();
}

isom_trex_t *isom_get_trex( isom_mvex_t *mvex, uint32_t track_ID )
{
    if( track_ID == 0 || LSMASH_IS_NON_EXISTING_BOX( mvex ) )
        return isom_non_existing_trex();
    for( lsmash_entry_t *entry = mvex->trex_list.head; entry; entry = entry->next )
    {
        isom_trex_t *trex = (isom_trex_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return isom_non_existing_trex();
        if( trex->track_ID == track_ID )
            return trex;
    }
    return isom_non_existing_trex();
}

isom_traf_t *isom_get_traf( isom_moof_t *moof, uint32_t track_ID )
{
    if( track_ID == 0 || LSMASH_IS_NON_EXISTING_BOX( moof ) )
        return isom_non_existing_traf();
    for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
    {
        isom_traf_t *traf = (isom_traf_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( traf )
         || LSMASH_IS_NON_EXISTING_BOX( traf->tfhd ) )
            return isom_non_existing_traf();
        if( traf->tfhd->track_ID == track_ID )
            return traf;
    }
    return isom_non_existing_traf();
}

isom_tfra_t *isom_get_tfra( isom_mfra_t *mfra, uint32_t track_ID )
{
    if( track_ID == 0 || LSMASH_IS_NON_EXISTING_BOX( mfra ) )
        return isom_non_existing_tfra();
    for( lsmash_entry_t *entry = mfra->tfra_list.head; entry; entry = entry->next )
    {
        isom_tfra_t *tfra = (isom_tfra_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( tfra ) )
            return isom_non_existing_tfra();
        if( tfra->track_ID == track_ID )
            return tfra;
    }
    return isom_non_existing_tfra();
}

static int isom_add_elst_entry( isom_elst_t *elst, uint64_t segment_duration, int64_t media_time, int32_t media_rate )
{
    assert( LSMASH_IS_EXISTING_BOX( elst->file ) );
    isom_elst_entry_t *data = lsmash_malloc( sizeof(isom_elst_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->segment_duration = segment_duration;
    data->media_time       = media_time;
    data->media_rate       = media_rate;
    if( lsmash_list_add_entry( elst->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    if( !elst->file->undefined_64_ver
     && (data->segment_duration > UINT32_MAX
      || data->media_time       >  INT32_MAX
      || data->media_time       <  INT32_MIN) )
        elst->version = 1;
    return 0;
}

/* This function returns 0 if failed, sample_entry_number if succeeded. */
int lsmash_add_sample_entry( lsmash_root_t *root, uint32_t track_ID, void *summary )
{
    if( LSMASH_IS_NON_EXISTING_BOX( root ) || !summary
     || ((lsmash_summary_t *)summary)->data_ref_index == 0
     || ((lsmash_summary_t *)summary)->data_ref_index > UINT16_MAX )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak )
     || LSMASH_IS_NON_EXISTING_BOX( trak->file )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->hdlr )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsd ) )
        return 0;
    isom_stsd_t      *stsd       = trak->mdia->minf->stbl->stsd;
    lsmash_media_type media_type = trak->mdia->hdlr->componentSubtype;
    if( isom_setup_sample_description( stsd, media_type, (lsmash_summary_t *)summary ) < 0 )
        return 0;
    else
        return stsd->list.entry_count;
}

static int isom_add_stts_entry( isom_stbl_t *stbl, uint32_t sample_delta )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stts ) );
    if( !stbl->stts->list )
        return LSMASH_ERR_NAMELESS;
    isom_stts_entry_t *data = lsmash_malloc( sizeof(isom_stts_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->sample_count = 1;
    data->sample_delta = sample_delta;
    if( lsmash_list_add_entry( stbl->stts->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_add_ctts_entry( isom_stbl_t *stbl, uint32_t sample_count, uint32_t sample_offset )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->ctts ) );
    if( !stbl->ctts->list )
        return LSMASH_ERR_NAMELESS;
    isom_ctts_entry_t *data = lsmash_malloc( sizeof(isom_ctts_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->sample_count  = sample_count;
    data->sample_offset = sample_offset;
    if( lsmash_list_add_entry( stbl->ctts->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_add_stsc_entry( isom_stbl_t *stbl, uint32_t first_chunk, uint32_t samples_per_chunk, uint32_t sample_description_index )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stsc ) );
    if( !stbl->stsc->list )
        return LSMASH_ERR_NAMELESS;
    isom_stsc_entry_t *data = lsmash_malloc( sizeof(isom_stsc_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->first_chunk              = first_chunk;
    data->samples_per_chunk        = samples_per_chunk;
    data->sample_description_index = sample_description_index;
    if( lsmash_list_add_entry( stbl->stsc->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_add_stsz_entry( isom_stbl_t *stbl, uint32_t entry_size )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl ) );
    if( LSMASH_IS_NON_EXISTING_BOX( stbl->stsz ) )
        return LSMASH_ERR_NAMELESS;
    isom_stsz_t *stsz = stbl->stsz;
    /* retrieve initial sample_size */
    if( stsz->sample_count == 0 )
        stsz->sample_size = entry_size;
    /* if it seems constant sample size at present, update sample_count only */
    if( !stsz->list && stsz->sample_size == entry_size )
    {
        ++ stsz->sample_count;
        return 0;
    }
    /* found sample_size varies, create sample_size list */
    if( !stsz->list )
    {
        stsz->list = lsmash_list_create_simple();
        if( !stsz->list )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( uint32_t i = 0; i < stsz->sample_count; i++ )
        {
            isom_stsz_entry_t *data = lsmash_malloc( sizeof(isom_stsz_entry_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            data->entry_size = stsz->sample_size;
            if( lsmash_list_add_entry( stsz->list, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
        stsz->sample_size = 0;
    }
    isom_stsz_entry_t *data = lsmash_malloc( sizeof(isom_stsz_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->entry_size = entry_size;
    if( lsmash_list_add_entry( stsz->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    ++ stsz->sample_count;
    return 0;
}

static int isom_add_stss_entry( isom_stbl_t *stbl, uint32_t sample_number )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stss ) );
    if( !stbl->stss->list )
        return LSMASH_ERR_NAMELESS;
    isom_stss_entry_t *data = lsmash_malloc( sizeof(isom_stss_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->sample_number = sample_number;
    if( lsmash_list_add_entry( stbl->stss->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_add_stps_entry( isom_stbl_t *stbl, uint32_t sample_number )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stps ) );
    if( !stbl->stps->list )
        return LSMASH_ERR_NAMELESS;
    isom_stps_entry_t *data = lsmash_malloc( sizeof(isom_stps_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->sample_number = sample_number;
    if( lsmash_list_add_entry( stbl->stps->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

/* Between ISOBMFF and QTFF, the most significant 2-bit has different meaning.
 * For the maximum compatibility, we set 0 to the most significant 2-bit when compatible with
 * both ISOBMFF with AVCFF extensions and QTFF.
 *   compatibility == 0 -> neither AVCFF extensions nor QTFF compatible
 *   compatibility == 1 -> AVCFF extensions compatible
 *   compatibility == 2 -> QTFF compatible
 *   compatibility == 3 -> both AVCFF extensions and QTFF compatible */
static int isom_add_sdtp_entry( isom_box_t *parent, lsmash_sample_property_t *prop, int compatibility )
{
    if( !prop || LSMASH_IS_NON_EXISTING_BOX( parent ) )
        return LSMASH_ERR_NAMELESS;
    isom_sdtp_t *sdtp = isom_non_existing_sdtp();
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL ) )
        sdtp = ((isom_stbl_t *)parent)->sdtp;
    else if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
        sdtp = ((isom_traf_t *)parent)->sdtp;
    else
        assert( 0 );
    if( LSMASH_IS_NON_EXISTING_BOX( sdtp )
     || !sdtp->list )
        return LSMASH_ERR_NAMELESS;
    isom_sdtp_entry_t *data = lsmash_malloc( sizeof(isom_sdtp_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    if( compatibility == 1 )
        data->is_leading = prop->leading & 0x03;
    else if( compatibility == 2 )
        data->is_leading = prop->allow_earlier & 0x03;
    else
    {
        data->is_leading = 0;
        assert( compatibility == 3 );
    }
    data->sample_depends_on     = prop->independent & 0x03;
    data->sample_is_depended_on = prop->disposable  & 0x03;
    data->sample_has_redundancy = prop->redundant   & 0x03;
    if( lsmash_list_add_entry( sdtp->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_add_co64_entry( isom_stbl_t *stbl, uint64_t chunk_offset )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stco ) );
    if( !stbl->stco->list )
        return LSMASH_ERR_NAMELESS;
    isom_co64_entry_t *data = lsmash_malloc( sizeof(isom_co64_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->chunk_offset = chunk_offset;
    if( lsmash_list_add_entry( stbl->stco->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_convert_stco_to_co64( isom_stbl_t *stbl )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stco ) );
    /* backup stco */
    int err = 0;
    isom_stco_t *stco = stbl->stco;
    LSMASH_MAKE_BOX_NON_EXISTING( stbl->stco );
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_co64( stbl ) ) )
    {
        err = LSMASH_ERR_NAMELESS;
        goto fail;
    }
    /* move chunk_offset to co64 from stco */
    for( lsmash_entry_t *entry = stco->list->head; entry; entry = entry->next )
    {
        isom_stco_entry_t *data = (isom_stco_entry_t*)entry->data;
        if( (err = isom_add_co64_entry( stbl, data->chunk_offset )) < 0 )
            goto fail;
    }
fail:
    isom_remove_box_by_itself( stco );
    return err;
}

static int isom_add_stco_entry( isom_stbl_t *stbl, uint64_t chunk_offset )
{
    if( !stbl->stco->list )
        return LSMASH_ERR_NAMELESS;
    if( stbl->stco->large_presentation )
        return isom_add_co64_entry( stbl, chunk_offset );
    if( chunk_offset > UINT32_MAX )
    {
        int err = isom_convert_stco_to_co64( stbl );
        if( err < 0 )
            return err;
        return isom_add_co64_entry( stbl, chunk_offset );
    }
    isom_stco_entry_t *data = lsmash_malloc( sizeof(isom_stco_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->chunk_offset = (uint32_t)chunk_offset;
    if( lsmash_list_add_entry( stbl->stco->list, data ) < 0 )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static isom_sgpd_t *isom_get_sample_group_description_common( lsmash_entry_list_t *list, uint32_t grouping_type )
{
    for( lsmash_entry_t *entry = list->head; entry; entry = entry->next )
    {
        isom_sgpd_t *sgpd = (isom_sgpd_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sgpd )
         || !sgpd->list )
            return isom_non_existing_sgpd();
        if( sgpd->grouping_type == grouping_type )
            return sgpd;
    }
    return isom_non_existing_sgpd();
}

static isom_sbgp_t *isom_get_sample_to_group_common( lsmash_entry_list_t *list, uint32_t grouping_type )
{
    for( lsmash_entry_t *entry = list->head; entry; entry = entry->next )
    {
        isom_sbgp_t *sbgp = (isom_sbgp_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sbgp )
         || !sbgp->list )
            return isom_non_existing_sbgp();
        if( sbgp->grouping_type == grouping_type )
            return sbgp;
    }
    return isom_non_existing_sbgp();
}

isom_sgpd_t *isom_get_sample_group_description( isom_stbl_t *stbl, uint32_t grouping_type )
{
    return isom_get_sample_group_description_common( &stbl->sgpd_list, grouping_type );
}

isom_sbgp_t *isom_get_sample_to_group( isom_stbl_t *stbl, uint32_t grouping_type )
{
    return isom_get_sample_to_group_common( &stbl->sbgp_list, grouping_type );
}

isom_sgpd_t *isom_get_roll_recovery_sample_group_description( lsmash_entry_list_t *list )
{
    isom_sgpd_t *sgpd;
    if( ((sgpd = isom_get_sample_group_description_common( list, ISOM_GROUP_TYPE_ROLL )), LSMASH_IS_EXISTING_BOX( sgpd ))
     || ((sgpd = isom_get_sample_group_description_common( list, ISOM_GROUP_TYPE_PROL )), LSMASH_IS_EXISTING_BOX( sgpd )) )
        return sgpd;
    return isom_non_existing_sgpd();
}

isom_sbgp_t *isom_get_roll_recovery_sample_to_group( lsmash_entry_list_t *list )
{
    isom_sbgp_t *sbgp;
    if( ((sbgp = isom_get_sample_to_group_common( list, ISOM_GROUP_TYPE_ROLL )), LSMASH_IS_EXISTING_BOX( sbgp ))
     || ((sbgp = isom_get_sample_to_group_common( list, ISOM_GROUP_TYPE_PROL )), LSMASH_IS_EXISTING_BOX( sbgp )) )
        return sbgp;
    return isom_non_existing_sbgp();
}

isom_sgpd_t *isom_get_fragment_sample_group_description( isom_traf_t *traf, uint32_t grouping_type )
{
    return isom_get_sample_group_description_common( &traf->sgpd_list, grouping_type );
}

isom_sbgp_t *isom_get_fragment_sample_to_group( isom_traf_t *traf, uint32_t grouping_type )
{
    return isom_get_sample_to_group_common( &traf->sbgp_list, grouping_type );
}

static isom_rap_entry_t *isom_add_rap_group_entry( isom_sgpd_t *sgpd )
{
    if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
        return NULL;
    isom_rap_entry_t *data = lsmash_malloc( sizeof(isom_rap_entry_t) );
     if( !data )
        return NULL;
    data->description_length        = 0;
    data->num_leading_samples_known = 0;
    data->num_leading_samples       = 0;
    if( lsmash_list_add_entry( sgpd->list, data ) < 0 )
    {
        lsmash_free( data );
        return NULL;
    }
    return data;
}

static isom_roll_entry_t *isom_add_roll_group_entry( isom_sgpd_t *sgpd, int16_t roll_distance )
{
    if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
        return NULL;
    isom_roll_entry_t *data = lsmash_malloc( sizeof(isom_roll_entry_t) );
     if( !data )
        return NULL;
    data->description_length = 0;
    data->roll_distance      = roll_distance;
    if( lsmash_list_add_entry( sgpd->list, data ) < 0 )
    {
        lsmash_free( data );
        return NULL;
    }
    return data;
}

static isom_group_assignment_entry_t *isom_add_group_assignment_entry( isom_sbgp_t *sbgp, uint32_t sample_count, uint32_t group_description_index )
{
    if( LSMASH_IS_NON_EXISTING_BOX( sbgp ) )
        return NULL;
    isom_group_assignment_entry_t *data = lsmash_malloc( sizeof(isom_group_assignment_entry_t) );
    if( !data )
        return NULL;
    data->sample_count            = sample_count;
    data->group_description_index = group_description_index;
    if( lsmash_list_add_entry( sbgp->list, data ) < 0 )
    {
        lsmash_free( data );
        return NULL;
    }
    return data;
}

static uint32_t isom_get_sample_count_from_sample_table( isom_stbl_t *stbl )
{
    if( LSMASH_IS_EXISTING_BOX( stbl->stsz ) )
        return stbl->stsz->sample_count;
    else if( LSMASH_IS_EXISTING_BOX( stbl->stz2 ) )
        return stbl->stz2->sample_count;
    else
        return 0;
}

uint32_t isom_get_sample_count( isom_trak_t *trak )
{
    return isom_get_sample_count_from_sample_table( trak->mdia->minf->stbl );
}

static uint64_t isom_get_dts( isom_stts_t *stts, uint32_t sample_number )
{
    if( !stts->list )
        return 0;
    uint64_t dts = 0;
    uint32_t i   = 1;
    lsmash_entry_t    *entry;
    isom_stts_entry_t *data = NULL;
    for( entry = stts->list->head; entry; entry = entry->next )
    {
        data = (isom_stts_entry_t *)entry->data;
        if( !data )
            return 0;
        if( i + data->sample_count > sample_number )
            break;
        dts += (uint64_t)data->sample_delta * data->sample_count;
        i   += data->sample_count;
    }
    if( !entry )
        return 0;
    dts += (uint64_t)data->sample_delta * (sample_number - i);
    return dts;
}

#if 0
static uint64_t isom_get_cts( isom_stts_t *stts, isom_ctts_t *ctts, uint32_t sample_number )
{
    if( !stts->list )
        return 0;
    if( LSMASH_IS_NON_EXISTING_BOX( ctts ) )
        return isom_get_dts( stts, sample_number );
    uint32_t i = 1;     /* This can be 0 (and then condition below shall be changed) but I dare use same algorithm with isom_get_dts. */
    lsmash_entry_t    *entry;
    isom_ctts_entry_t *data = NULL;
    if( sample_number == 0 )
        return 0;
    for( entry = ctts->list->head; entry; entry = entry->next )
    {
        data = (isom_ctts_entry_t *)entry->data;
        if( !data )
            return 0;
        if( i + data->sample_count > sample_number )
            break;
        i += data->sample_count;
    }
    if( !entry )
        return 0;
    return isom_get_dts( stts, sample_number ) + data->sample_offset;
}
#endif

static int isom_replace_last_sample_delta( isom_stbl_t *stbl, uint32_t sample_delta )
{
    assert( LSMASH_IS_EXISTING_BOX( stbl->stts ) );
    if( !stbl->stts->list
     || !stbl->stts->list->tail
     || !stbl->stts->list->tail->data )
        return LSMASH_ERR_NAMELESS;
    isom_stts_entry_t *last_stts_data = (isom_stts_entry_t *)stbl->stts->list->tail->data;
    if( sample_delta != last_stts_data->sample_delta )
    {
        if( last_stts_data->sample_count > 1 )
        {
            last_stts_data->sample_count -= 1;
            int err = isom_add_stts_entry( stbl, sample_delta );
            if( err < 0 )
                return err;
        }
        else
            last_stts_data->sample_delta = sample_delta;
    }
    return 0;
}

static int isom_update_mdhd_duration( isom_trak_t *trak, uint32_t last_sample_delta )
{
    assert( LSMASH_IS_EXISTING_BOX( trak ) );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->file )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
     || !trak->cache
     || !trak->mdia->minf->stbl->stts->list )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_file_t *file = trak->file;
    isom_mdhd_t *mdhd = trak->mdia->mdhd;
    isom_stbl_t *stbl = trak->mdia->minf->stbl;
    isom_stts_t *stts = stbl->stts;
    isom_ctts_t *ctts = stbl->ctts;
    isom_cslg_t *cslg = stbl->cslg;
    mdhd->duration = 0;
    uint32_t sample_count = isom_get_sample_count( trak );
    if( sample_count == 0 )
    {
        /* Return error if non-fragmented movie has no samples. */
        if( !file->fragment && !stts->list->entry_count )
            return LSMASH_ERR_INVALID_DATA;
        return 0;
    }
    /* Now we have at least 1 sample, so do stts_entry. */
    lsmash_entry_t    *last_stts      = stts->list->tail;
    isom_stts_entry_t *last_stts_data = (isom_stts_entry_t *)last_stts->data;
    if( sample_count == 1 )
        mdhd->duration = last_stts_data->sample_delta;
    /* Now we have at least 2 samples,
     * but dunno whether 1 stts_entry which has 2 samples or 2 stts_entry which has 1 samle each. */
    else if( LSMASH_IS_NON_EXISTING_BOX( ctts ) )
    {
        /* use dts instead of cts */
        mdhd->duration = isom_get_dts( stts, sample_count );
        int err;
        if( last_sample_delta )
        {
            mdhd->duration += last_sample_delta;
            if( (err = isom_replace_last_sample_delta( stbl, last_sample_delta )) < 0 )
                return err;
        }
        else if( last_stts_data->sample_count > 1 )
            mdhd->duration += last_stts_data->sample_delta; /* no need to update last_stts_data->sample_delta */
        else
        {
            /* Remove the last entry. */
            if( (err = lsmash_list_remove_entry_tail( stts->list )) < 0 )
                return err;
            /* copy the previous sample_delta. */
            ++ ((isom_stts_entry_t *)stts->list->tail->data)->sample_count;
            mdhd->duration += ((isom_stts_entry_t *)stts->list->tail->data)->sample_delta;
        }
    }
    else
    {
        if( !ctts->list
         ||  ctts->list->entry_count == 0 )
            return LSMASH_ERR_INVALID_DATA;
        uint64_t dts        = 0;
        uint64_t max_cts    = 0;
        uint64_t max2_cts   = 0;
        uint64_t min_cts    = LSMASH_TIMESTAMP_UNDEFINED;
        int64_t  max_offset = 0;
        int64_t  min_offset = UINT32_MAX;
        int32_t  ctd_shift  = trak->cache->timestamp.ctd_shift;
        uint32_t j = 0;
        uint32_t k = 0;
        lsmash_entry_t *stts_entry = stts->list->head;
        lsmash_entry_t *ctts_entry = ctts->list->head;
        for( uint32_t i = 0; i < sample_count; i++ )
        {
            if( !ctts_entry || !stts_entry )
                return LSMASH_ERR_INVALID_DATA;
            isom_stts_entry_t *stts_data = (isom_stts_entry_t *)stts_entry->data;
            isom_ctts_entry_t *ctts_data = (isom_ctts_entry_t *)ctts_entry->data;
            if( !stts_data || !ctts_data )
                return LSMASH_ERR_INVALID_DATA;
            if( ctts_data->sample_offset != ISOM_NON_OUTPUT_SAMPLE_OFFSET )
            {
                uint64_t cts;
                if( ctd_shift )
                {
                    /* Anyway, add composition to decode timeline shift for calculating maximum and minimum CTS correctly. */
                    int64_t sample_offset = (int32_t)ctts_data->sample_offset;
                    cts = dts + sample_offset + ctd_shift;
                    max_offset = LSMASH_MAX( max_offset, sample_offset );
                    min_offset = LSMASH_MIN( min_offset, sample_offset );
                }
                else
                {
                    cts = dts + ctts_data->sample_offset;
                    max_offset = LSMASH_MAX( max_offset, ctts_data->sample_offset );
                    min_offset = LSMASH_MIN( min_offset, ctts_data->sample_offset );
                }
                min_cts = LSMASH_MIN( min_cts, cts );
                if( max_cts < cts )
                {
                    max2_cts = max_cts;
                    max_cts  = cts;
                }
                else if( max2_cts < cts )
                    max2_cts = cts;
            }
            dts += stts_data->sample_delta;
            /* If finished sample_count of current entry, move to next. */
            if( ++j == ctts_data->sample_count )
            {
                ctts_entry = ctts_entry->next;
                j = 0;
            }
            if( ++k == stts_data->sample_count )
            {
                stts_entry = stts_entry->next;
                k = 0;
            }
        }
        dts -= last_stts_data->sample_delta;
        if( file->fragment )
            /* Overall presentation is extended exceeding this initial movie.
             * So, any players shall display the movie exceeding the durations
             * indicated in Movie Header Box, Track Header Boxes and Media Header Boxes.
             * Samples up to the duration indicated in Movie Extends Header Box shall be displayed.
             * In the absence of Movie Extends Header Box, all samples shall be displayed. */
            mdhd->duration += dts + last_sample_delta;
        else
        {
            if( !last_sample_delta )
            {
                /* The spec allows an arbitrary value for the duration of the last sample. So, we pick last-1 sample's. */
                last_sample_delta = max_cts - max2_cts;
            }
            if( min_cts != LSMASH_TIMESTAMP_UNDEFINED )
                mdhd->duration = max_cts - min_cts + last_sample_delta;
            /* To match dts and media duration, update stts and mdhd relatively. */
            if( mdhd->duration > dts )
                last_sample_delta = mdhd->duration - dts;
            else
                mdhd->duration = dts + last_sample_delta;   /* media duration must not less than last dts. */
        }
        int err = isom_replace_last_sample_delta( stbl, last_sample_delta );
        if( err < 0 )
            return err;
        /* Explicit composition information and timeline shifting  */
        if( LSMASH_IS_EXISTING_BOX( cslg ) || file->qt_compatible || file->max_isom_version >= 4 )
        {
            if( ctd_shift )
            {
                /* Remove composition to decode timeline shift. */
                max_cts  -= ctd_shift;
                max2_cts -= ctd_shift;
                min_cts  -= ctd_shift;
            }
            int64_t composition_end_time = max_cts + (max_cts - max2_cts);
            if( !file->fragment
             && min_cts != LSMASH_TIMESTAMP_UNDEFINED
             && (min_offset <= INT32_MAX) && (min_offset >= INT32_MIN)
             && (max_offset <= INT32_MAX) && (max_offset >= INT32_MIN)
             && ((int64_t)min_cts <= INT32_MAX) && (composition_end_time <= INT32_MAX) )
            {
                if( LSMASH_IS_NON_EXISTING_BOX( cslg ) )
                {
                    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_cslg( trak->mdia->minf->stbl ) ) )
                        return LSMASH_ERR_NAMELESS;
                    cslg = stbl->cslg;
                }
                cslg->compositionToDTSShift        = ctd_shift;
                cslg->leastDecodeToDisplayDelta    = min_offset;
                cslg->greatestDecodeToDisplayDelta = max_offset;
                cslg->compositionStartTime         = min_cts;
                cslg->compositionEndTime           = composition_end_time;
            }
            else
                isom_remove_box_by_itself( cslg );
        }
    }
    if( mdhd->duration > UINT32_MAX && !file->undefined_64_ver )
        mdhd->version = 1;
    return 0;
}

static int isom_update_mvhd_duration( isom_moov_t *moov )
{
    assert( LSMASH_IS_EXISTING_BOX( moov ) );
    if( LSMASH_IS_NON_EXISTING_BOX( moov->mvhd->file ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_mvhd_t *mvhd = moov->mvhd;
    mvhd->duration = 0;
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        /* We pick maximum track duration as movie duration. */
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
            return LSMASH_ERR_INVALID_DATA;
        mvhd->duration = entry != moov->trak_list.head
                       ? LSMASH_MAX( mvhd->duration, trak->tkhd->duration )
                       : trak->tkhd->duration;
    }
    if( mvhd->duration > UINT32_MAX && !mvhd->file->undefined_64_ver )
        mvhd->version = 1;
    return 0;
}

int isom_update_tkhd_duration( isom_trak_t *trak )
{
    assert( LSMASH_IS_EXISTING_BOX( trak ) );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->file->moov->mvhd ) )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_file_t *file = trak->file;
    isom_tkhd_t   *tkhd = trak->tkhd;
    tkhd->duration = 0;
    if( file->fragment
     || LSMASH_IS_NON_EXISTING_BOX( trak->edts->elst ) )
    {
        /* If this presentation might be extended or this track doesn't have edit list, calculate track duration from media duration. */
        if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
         || trak->mdia->mdhd->timescale == 0 )
            return LSMASH_ERR_INVALID_DATA;
        if( trak->mdia->mdhd->duration == 0 )
        {
            int err = isom_update_mdhd_duration( trak, 0 );
            if( err < 0 )
                return err;
        }
        tkhd->duration = trak->mdia->mdhd->duration * ((double)file->moov->mvhd->timescale / trak->mdia->mdhd->timescale);
    }
    else
    {
        /* If the presentation won't be extended and this track has any edit, then track duration is just the sum of the segment_duartions. */
        for( lsmash_entry_t *entry = trak->edts->elst->list->head; entry; entry = entry->next )
        {
            isom_elst_entry_t *data = (isom_elst_entry_t *)entry->data;
            if( !data )
                return LSMASH_ERR_INVALID_DATA;
            tkhd->duration += data->segment_duration;
        }
    }
    if( tkhd->duration > UINT32_MAX && !file->undefined_64_ver )
        tkhd->version = 1;
    if( !file->fragment && tkhd->duration == 0 )
        tkhd->duration = tkhd->version == 1 ? 0xffffffffffffffff : 0xffffffff;
    return isom_update_mvhd_duration( file->moov );
}

int lsmash_update_track_duration( lsmash_root_t *root, uint32_t track_ID, uint32_t last_sample_delta )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
        return LSMASH_ERR_NAMELESS;
    int err = isom_update_mdhd_duration( trak, last_sample_delta );
    if( err < 0 )
        return err;
    /* If the presentation won't be extended and this track has any edit, we don't change or update duration in tkhd. */
    if( !file->fragment
     && LSMASH_IS_EXISTING_BOX( trak->edts )
     && LSMASH_IS_EXISTING_BOX( trak->edts->elst ) )
        err = isom_update_mvhd_duration( file->moov );  /* Only update movie duration. */
    else
        err = isom_update_tkhd_duration( trak );        /* Also update movie duration internally. */
    return err;
}

static inline int isom_increment_sample_number_in_entry
(
    uint32_t        *sample_number_in_entry,
    uint32_t         sample_count_in_entry,
    lsmash_entry_t **entry
)
{
    if( *sample_number_in_entry != sample_count_in_entry )
    {
        *sample_number_in_entry += 1;
        return 0;
    }
    /* Precede the next entry. */
    *sample_number_in_entry = 1;
    if( *entry )
    {
        *entry = (*entry)->next;
        if( *entry && !(*entry)->data )
            return LSMASH_ERR_INVALID_DATA;
    }
    return 0;
}

int isom_calculate_bitrate_description
(
    isom_stbl_t *stbl,
    isom_mdhd_t *mdhd,
    uint32_t    *bufferSizeDB,
    uint32_t    *maxBitrate,
    uint32_t    *avgBitrate,
    uint32_t     sample_description_index
)
{
    isom_stsz_t *stsz = stbl->stsz;
    lsmash_entry_list_t *stsz_list  = LSMASH_IS_EXISTING_BOX( stsz ) ? stsz->list : stbl->stz2->list;
    lsmash_entry_t *stsz_entry      = stsz_list ? stsz_list->head : NULL;
    lsmash_entry_t *stts_entry      = stbl->stts->list->head;
    lsmash_entry_t *stsc_entry      = NULL;
    lsmash_entry_t *next_stsc_entry = stbl->stsc->list->head;
    isom_stts_entry_t *stts_data    = NULL;
    isom_stsc_entry_t *stsc_data    = NULL;
    if( next_stsc_entry && !next_stsc_entry->data )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t rate                   = 0;
    uint64_t dts                    = 0;
    uint32_t time_wnd               = 0;
    uint32_t chunk_number           = 0;
    uint32_t sample_number_in_stts  = 1;
    uint32_t sample_number_in_chunk = 1;
    uint32_t constant_sample_size   = LSMASH_IS_EXISTING_BOX( stsz ) ? stsz->sample_size : 0;
    *bufferSizeDB = 0;
    *maxBitrate   = 0;
    *avgBitrate   = 0;
    while( stts_entry )
    {
        int err;
        if( !stsc_data || sample_number_in_chunk == stsc_data->samples_per_chunk )
        {
            /* Move the next chunk. */
            sample_number_in_chunk = 1;
            ++chunk_number;
            /* Check if the next entry is broken. */
            while( next_stsc_entry && ((isom_stsc_entry_t *)next_stsc_entry->data)->first_chunk < chunk_number )
            {
                /* Just skip broken next entry. */
                next_stsc_entry = next_stsc_entry->next;
                if( next_stsc_entry && !next_stsc_entry->data )
                    return LSMASH_ERR_INVALID_DATA;
            }
            /* Check if the next chunk belongs to the next sequence of chunks. */
            if( next_stsc_entry && ((isom_stsc_entry_t *)next_stsc_entry->data)->first_chunk == chunk_number )
            {
                stsc_entry = next_stsc_entry;
                next_stsc_entry = next_stsc_entry->next;
                if( next_stsc_entry && !next_stsc_entry->data )
                    return LSMASH_ERR_INVALID_DATA;
                stsc_data = (isom_stsc_entry_t *)stsc_entry->data;
                /* Check if the next contiguous chunks belong to given sample description. */
                if( stsc_data->sample_description_index != sample_description_index )
                {
                    /* Skip chunks which don't belong to given sample description. */
                    uint32_t number_of_skips   = 0;
                    uint32_t first_chunk       = stsc_data->first_chunk;
                    uint32_t samples_per_chunk = stsc_data->samples_per_chunk;
                    while( next_stsc_entry )
                    {
                        if( ((isom_stsc_entry_t *)next_stsc_entry->data)->sample_description_index != sample_description_index )
                        {
                            stsc_data = (isom_stsc_entry_t *)next_stsc_entry->data;
                            number_of_skips  += (stsc_data->first_chunk - first_chunk) * samples_per_chunk;
                            first_chunk       = stsc_data->first_chunk;
                            samples_per_chunk = stsc_data->samples_per_chunk;
                        }
                        else if( ((isom_stsc_entry_t *)next_stsc_entry->data)->first_chunk <= first_chunk )
                            ;   /* broken entry */
                        else
                            break;
                        /* Just skip the next entry. */
                        next_stsc_entry = next_stsc_entry->next;
                        if( next_stsc_entry && !next_stsc_entry->data )
                            return LSMASH_ERR_INVALID_DATA;
                    }
                    if( !next_stsc_entry )
                        break;      /* There is no more chunks which don't belong to given sample description. */
                    number_of_skips += (((isom_stsc_entry_t *)next_stsc_entry->data)->first_chunk - first_chunk) * samples_per_chunk;
                    for( uint32_t i = 0; i < number_of_skips; i++ )
                    {
                        if( stsz_list )
                        {
                            if( !stsz_entry )
                                break;
                            stsz_entry = stsz_entry->next;
                        }
                        if( !stts_entry )
                            break;
                        if( (err = isom_increment_sample_number_in_entry( &sample_number_in_stts,
                                                                          ((isom_stts_entry_t *)stts_entry->data)->sample_count,
                                                                          &stts_entry )) < 0 )
                            return err;
                    }
                    if( (stsz_list && !stsz_entry) || !stts_entry )
                        break;
                    chunk_number = stsc_data->first_chunk;
                }
            }
        }
        else
            ++sample_number_in_chunk;
        /* Get current sample's size. */
        uint32_t size;
        if( stsz_list )
        {
            if( !stsz_entry )
                break;
            isom_stsz_entry_t *stsz_data = (isom_stsz_entry_t *)stsz_entry->data;
            if( !stsz_data )
                return LSMASH_ERR_INVALID_DATA;
            size = stsz_data->entry_size;
            stsz_entry = stsz_entry->next;
        }
        else
            size = constant_sample_size;
        /* Get current sample's DTS. */
        if( stts_data )
            dts += stts_data->sample_delta;
        stts_data = (isom_stts_entry_t *)stts_entry->data;
        if( !stts_data )
            return LSMASH_ERR_INVALID_DATA;
        if( (err = isom_increment_sample_number_in_entry( &sample_number_in_stts, stts_data->sample_count, &stts_entry )) < 0 )
            return err;
        /* Calculate bitrate description. */
        if( *bufferSizeDB < size )
            *bufferSizeDB = size;
        *avgBitrate += size;
        rate += size;
        if( dts > time_wnd + mdhd->timescale )
        {
            if( rate > *maxBitrate )
                *maxBitrate = rate;
            time_wnd = dts;
            rate = 0;
        }
    }
    double duration = (double)mdhd->duration / mdhd->timescale;
    *avgBitrate = (uint32_t)(*avgBitrate / duration);
    if( *maxBitrate == 0 )
        *maxBitrate = *avgBitrate;
    /* Convert to bits per second. */
    *maxBitrate *= 8;
    *avgBitrate *= 8;
    return 0;
}

int isom_is_variable_size( isom_stbl_t *stbl )
{
    if( (LSMASH_IS_EXISTING_BOX( stbl->stz2 ) && stbl->stz2->sample_count > 1)
     || (LSMASH_IS_EXISTING_BOX( stbl->stsz ) && stbl->stsz->sample_count > 1 && stbl->stsz->sample_size == 0) )
        return 1;
    else
        return 0;
}

uint32_t isom_get_first_sample_size( isom_stbl_t *stbl )
{
    if( LSMASH_IS_EXISTING_BOX( stbl->stsz ) )
    {
        /* 'stsz' */
        if( stbl->stsz->sample_size )
            return stbl->stsz->sample_size;
        else if( stbl->stsz->list && stbl->stsz->list->head && stbl->stsz->list->head->data )
            return ((isom_stsz_entry_t *)stbl->stsz->list->head->data)->entry_size;
        else
            return 0;
    }
    else if( LSMASH_IS_EXISTING_BOX( stbl->stz2 ) )
    {
        /* stz2 */
        if( stbl->stz2->list && stbl->stz2->list->head && stbl->stz2->list->head->data )
            return ((isom_stsz_entry_t *)stbl->stz2->list->head->data)->entry_size;
        else
            return 0;
    }
    else
        return 0;
}

int isom_update_bitrate_description( isom_mdia_t *mdia )
{
    if( LSMASH_IS_NON_EXISTING_BOX( mdia->mdhd ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_stbl_t *stbl = mdia->minf->stbl;
    if( LSMASH_IS_NON_EXISTING_BOX( stbl->stsd )
     || (LSMASH_IS_NON_EXISTING_BOX( stbl->stsz ) && LSMASH_IS_NON_EXISTING_BOX( stbl->stz2 ))
     || !stbl->stsc->list
     || !stbl->stts->list )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t sample_description_index = 0;
    for( lsmash_entry_t *entry = stbl->stsd->list.head; entry; entry = entry->next )
    {
        isom_sample_entry_t *sample_entry = (isom_sample_entry_t *)entry->data;
        if( !sample_entry )
            return LSMASH_ERR_INVALID_DATA;
        ++sample_description_index;
        isom_bitrate_updater_t func_update_bitrate = isom_get_bitrate_updater( sample_entry );
        if( func_update_bitrate )
        {
            int err = func_update_bitrate( stbl, mdia->mdhd, sample_description_index );
            if( err < 0 )
                return err;
        }
    }
    return sample_description_index ? 0 : LSMASH_ERR_INVALID_DATA;
}

static inline uint64_t isom_get_current_mp4time( void )
{
    return (uint64_t)time( NULL ) + ISOM_MAC_EPOCH_OFFSET;
}

static int isom_set_media_creation_time( isom_trak_t *trak, uint64_t current_mp4time )
{
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_mdhd_t *mdhd = trak->mdia->mdhd;
    if( mdhd->creation_time == 0 )
        mdhd->creation_time = mdhd->modification_time = current_mp4time;
    return 0;
}

static int isom_set_track_creation_time( isom_trak_t *trak, uint64_t current_mp4time )
{
    assert( LSMASH_IS_EXISTING_BOX( trak ) );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_tkhd_t *tkhd = trak->tkhd;
    if( tkhd->creation_time == 0 )
        tkhd->creation_time = tkhd->modification_time = current_mp4time;
    return isom_set_media_creation_time( trak, current_mp4time );
}

static int isom_set_movie_creation_time( lsmash_file_t *file )
{
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        return LSMASH_ERR_NAMELESS;
    uint64_t current_mp4time = isom_get_current_mp4time();
    for( lsmash_entry_t *entry = file->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
            return LSMASH_ERR_INVALID_DATA;
        int err = isom_set_track_creation_time( trak, current_mp4time );
        if( err < 0 )
            return err;
    }
    isom_mvhd_t *mvhd = file->moov->mvhd;
    if( mvhd->creation_time == 0 )
        mvhd->creation_time = mvhd->modification_time = current_mp4time;
    return 0;
}

int isom_setup_handler_reference( isom_hdlr_t *hdlr, uint32_t media_type )
{
    assert( LSMASH_IS_EXISTING_BOX( hdlr ) );
    isom_box_t    *parent = hdlr->parent;
    lsmash_file_t *file   = hdlr->file;
    if( LSMASH_IS_NON_EXISTING_BOX( parent )
     || LSMASH_IS_NON_EXISTING_BOX( file ) )
        return LSMASH_ERR_NAMELESS;
    isom_mdia_t *mdia = lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MDIA ) ? (isom_mdia_t *)parent : isom_non_existing_mdia();
    isom_meta_t *meta = lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META ) ? (isom_meta_t *)parent
                      : lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META ) ? (isom_meta_t *)parent : isom_non_existing_meta();
    uint32_t type    = LSMASH_IS_EXISTING_BOX( mdia ) ? (file->qt_compatible ? QT_HANDLER_TYPE_MEDIA : 0)
                                                      : (LSMASH_IS_EXISTING_BOX( meta ) ? 0 : QT_HANDLER_TYPE_DATA);
    uint32_t subtype = media_type;
    hdlr->componentType    = type;
    hdlr->componentSubtype = subtype;
    char *type_name    = NULL;
    char *subtype_name = NULL;
    uint8_t type_name_length    = 0;
    uint8_t subtype_name_length = 0;
    if( mdia )
        type_name = "Media ";
    else if( meta )
        type_name = "Metadata ";
    else    /* if( minf ) */
        type_name = "Data ";
    type_name_length = strlen( type_name );
    struct
    {
        uint32_t subtype;
        char    *subtype_name;
        uint8_t  subtype_name_length;
    } subtype_table[] =
        {
            { ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK,          "Sound ",    6 },
            { ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK,          "Video ",    6 },
            { ISOM_MEDIA_HANDLER_TYPE_HINT_TRACK,           "Hint ",     5 },
            { ISOM_MEDIA_HANDLER_TYPE_TIMED_METADATA_TRACK, "Metadata ", 9 },
            { ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK,           "Text ",     5 },
            { ISOM_META_HANDLER_TYPE_ITUNES_METADATA,       "iTunes ",   7 },
            { QT_REFERENCE_HANDLER_TYPE_ALIAS,              "Alias ",    6 },
            { QT_REFERENCE_HANDLER_TYPE_RESOURCE,           "Resource ", 9 },
            { QT_REFERENCE_HANDLER_TYPE_URL,                "URL ",      4 },
            { subtype,                                      "Unknown ",  8 }
        };
    for( int i = 0; subtype_table[i].subtype; i++ )
        if( subtype == subtype_table[i].subtype )
        {
            subtype_name        = subtype_table[i].subtype_name;
            subtype_name_length = subtype_table[i].subtype_name_length;
            break;
        }
    uint32_t name_length = 15 + subtype_name_length + type_name_length + file->isom_compatible + file->qt_compatible;
    uint8_t *name = lsmash_malloc( name_length );
    if( !name )
        return LSMASH_ERR_MEMORY_ALLOC;
    if( file->qt_compatible )
        name[0] = name_length & 0xff;
    memcpy( name + file->qt_compatible, "L-SMASH ", 8 );
    memcpy( name + file->qt_compatible + 8, subtype_name, subtype_name_length );
    memcpy( name + file->qt_compatible + 8 + subtype_name_length, type_name, type_name_length );
    memcpy( name + file->qt_compatible + 8 + subtype_name_length + type_name_length, "Handler", 7 );
    if( file->isom_compatible )
        name[name_length - 1] = 0;
    hdlr->componentName        = name;
    hdlr->componentName_length = name_length;
    return 0;
}

isom_trak_t *isom_track_create( lsmash_file_t *file, lsmash_media_type media_type )
{
    /* Don't allow to create a new track if the initial movie is already written. */
    if( (file->fragment && file->fragment->movie)
     || (LSMASH_IS_EXISTING_BOX( file->moov ) && (file->moov->manager & LSMASH_WRITTEN_BOX)) )
        return isom_non_existing_trak();
    isom_trak_t *trak = isom_add_trak( file->moov );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->file->moov->mvhd ) )
        goto fail;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tkhd( trak ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mdia( trak ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mdhd( trak->mdia ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_minf( trak->mdia ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_dinf( trak->mdia->minf ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_dref( trak->mdia->minf->dinf ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stbl( trak->mdia->minf ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stsd( trak->mdia->minf->stbl ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stts( trak->mdia->minf->stbl ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stsc( trak->mdia->minf->stbl ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stco( trak->mdia->minf->stbl ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stsz( trak->mdia->minf->stbl ) ) )
        goto fail;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_hdlr( trak->mdia ) )
     || isom_setup_handler_reference( trak->mdia->hdlr, media_type ) < 0 )
        goto fail;
    if( file->qt_compatible )
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_hdlr( trak->mdia->minf ) )
         || isom_setup_handler_reference( trak->mdia->minf->hdlr, QT_REFERENCE_HANDLER_TYPE_URL ) < 0 )
            goto fail;
    }
    switch( media_type )
    {
        case ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK :
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_vmhd( trak->mdia->minf ) ) )
                goto fail;
            trak->mdia->minf->vmhd->flags = 0x000001;
            break;
        case ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK :
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_smhd( trak->mdia->minf ) ) )
                goto fail;
            trak->cache->is_audio = 1;
            break;
        case ISOM_MEDIA_HANDLER_TYPE_HINT_TRACK :
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_hmhd( trak->mdia->minf ) ) )
                goto fail;
            trak->mdia->minf->hmhd->combinedPDUsize = 0;
            trak->mdia->minf->hmhd->PDUcount        = 0;
            trak->mdia->minf->hmhd->maxPDUsize      = 0;
            break;
        case ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK :
            if( file->qt_compatible || file->itunes_movie )
            {
                if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_gmhd( trak->mdia->minf ) )
                 || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_gmin( trak->mdia->minf->gmhd ) )
                 || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_text( trak->mdia->minf->gmhd ) ) )
                    return 0;
                /* Default Text Media Information Box. */
                {
                    isom_text_t *text = trak->mdia->minf->gmhd->text;
                    text->matrix[0] = 0x00010000;
                    text->matrix[4] = 0x00010000;
                    text->matrix[8] = 0x40000000;
                }
            }
            else
                goto fail;  /* We support only reference text media track for chapter yet. */
            break;
        default :
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_nmhd( trak->mdia->minf ) ) )
                goto fail;
            break;
    }
    /* Default Track Header Box. */
    {
        isom_tkhd_t *tkhd = trak->tkhd;
        if( media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK )
            tkhd->volume = 0x0100;
        tkhd->matrix[0] = 0x00010000;
        tkhd->matrix[4] = 0x00010000;
        tkhd->matrix[8] = 0x40000000;
        tkhd->duration  = 0xffffffff;
        tkhd->track_ID  = trak->file->moov->mvhd->next_track_ID ++;
    }
    trak->mdia->mdhd->language = file->qt_compatible ? 0 : ISOM_LANGUAGE_CODE_UNDEFINED;
    return trak;
fail:
    isom_remove_box_by_itself( trak );
    return isom_non_existing_trak();
}

isom_moov_t *isom_movie_create( lsmash_file_t *file )
{
    isom_moov_t *moov = isom_add_moov( file );
    isom_mvhd_t *mvhd = isom_add_mvhd( moov );
    if( LSMASH_IS_NON_EXISTING_BOX( mvhd ) )
    {
        isom_remove_box_by_itself( moov );
        return isom_non_existing_moov();
    }
    /* Default Movie Header Box. */
    mvhd->rate          = 0x00010000;
    mvhd->volume        = 0x0100;
    mvhd->matrix[0]     = 0x00010000;
    mvhd->matrix[4]     = 0x00010000;
    mvhd->matrix[8]     = 0x40000000;
    mvhd->next_track_ID = 1;
    file->initializer = file;
    return moov;
}

/*******************************
    public interfaces
*******************************/

/*---- track manipulators ----*/

void lsmash_delete_track( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return;
    for( lsmash_entry_t *entry = root->file->initializer->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
            return;
        if( trak->tkhd->track_ID == track_ID )
        {
            isom_remove_box_by_itself( trak );
            return;
        }
    }
}

uint32_t lsmash_create_track( lsmash_root_t *root, lsmash_media_type media_type )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_track_create( root->file, media_type );
    if( LSMASH_IS_NON_EXISTING_BOX( trak )
     || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return 0;
    return trak->tkhd->track_ID;
}

uint32_t lsmash_get_track_ID( lsmash_root_t *root, uint32_t track_number )
{
    if( isom_check_initializer_present( root ) < 0
     || LSMASH_IS_NON_EXISTING_BOX( root->file->initializer->moov ) )
        return 0;
    isom_trak_t *trak = (isom_trak_t *)lsmash_list_get_entry_data( &root->file->initializer->moov->trak_list, track_number );
    if( LSMASH_IS_NON_EXISTING_BOX( trak )
     || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return 0;
    return trak->tkhd->track_ID;
}

void lsmash_initialize_track_parameters( lsmash_track_parameters_t *param )
{
    memset( param, 0, sizeof(lsmash_track_parameters_t) );
    param->audio_volume = 0x0100;
    param->matrix[0]    = 0x00010000;
    param->matrix[4]    = 0x00010000;
    param->matrix[8]    = 0x40000000;
}

int lsmash_set_track_parameters( lsmash_root_t *root, uint32_t track_ID, lsmash_track_parameters_t *param )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->hdlr )
     || LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        return LSMASH_ERR_NAMELESS;
    /* Prepare Track Aperture Modes if required. */
    if( file->qt_compatible && param->aperture_modes )
    {
        if( LSMASH_IS_NON_EXISTING_BOX( trak->tapt ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tapt( trak ) ) )
            return LSMASH_ERR_NAMELESS;
        isom_tapt_t *tapt = trak->tapt;
        if( (LSMASH_IS_NON_EXISTING_BOX( tapt->clef ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_clef( tapt ) ))
         || (LSMASH_IS_NON_EXISTING_BOX( tapt->prof ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_prof( tapt ) ))
         || (LSMASH_IS_NON_EXISTING_BOX( tapt->enof ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_enof( tapt ) )) )
            return LSMASH_ERR_NAMELESS;
    }
    else
        isom_remove_box_by_itself( trak->tapt );
    /* Set up Track Header. */
    uint32_t media_type = trak->mdia->hdlr->componentSubtype;
    isom_tkhd_t *tkhd = trak->tkhd;
    tkhd->flags    = param->mode;
    tkhd->track_ID = param->track_ID ? param->track_ID : tkhd->track_ID;
    tkhd->duration = LSMASH_IS_NON_EXISTING_BOX( trak->edts->elst ) ? param->duration : tkhd->duration;
    /* Template fields
     *   alternate_group, layer, volume and matrix
     * According to 14496-14, these value are all set to defaut values in 14496-12.
     * And when a file is read as an MPEG-4 file, these values shall be ignored.
     * If a file complies with other specifications, then those fields may have non-default values
     * as required by those other specifications. */
    if( param->alternate_group )
    {
        if( file->qt_compatible || file->itunes_movie || file->max_3gpp_version >= 4 )
            tkhd->alternate_group = param->alternate_group;
        else
        {
            tkhd->alternate_group = 0;
            lsmash_log( NULL, LSMASH_LOG_WARNING,
                        "alternate_group is specified but not compatible with any of the brands. It won't be set.\n" );
        }
    }
    else
        tkhd->alternate_group = 0;
    if( file->qt_compatible || file->itunes_movie )
    {
        tkhd->layer  = media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK ? param->video_layer  : 0;
        tkhd->volume = media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK ? param->audio_volume : 0;
        if( media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK )
            for( int i = 0; i < 9; i++ )
                tkhd->matrix[i] = param->matrix[i];
        else
            for( int i = 0; i < 9; i++ )
                tkhd->matrix[i] = 0;
    }
    else
    {
        tkhd->layer     = 0;
        tkhd->volume    = media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK ? 0x0100 : 0;
        tkhd->matrix[0] = 0x00010000;
        tkhd->matrix[1] = 0;
        tkhd->matrix[2] = 0;
        tkhd->matrix[3] = 0;
        tkhd->matrix[4] = 0x00010000;
        tkhd->matrix[5] = 0;
        tkhd->matrix[6] = 0;
        tkhd->matrix[7] = 0;
        tkhd->matrix[8] = 0x40000000;
    }
    /* visual presentation size */
    tkhd->width  = media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK ? param->display_width  : 0;
    tkhd->height = media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK ? param->display_height : 0;
    /* Update next_track_ID if needed. */
    if( file->moov->mvhd->next_track_ID <= tkhd->track_ID )
        file->moov->mvhd->next_track_ID = tkhd->track_ID + 1;
    return 0;
}

int lsmash_get_track_parameters( lsmash_root_t *root, uint32_t track_ID, lsmash_track_parameters_t *param )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_tkhd_t *tkhd = trak->tkhd;
    param->mode            = tkhd->flags;
    param->track_ID        = tkhd->track_ID;
    param->duration        = tkhd->duration;
    param->video_layer     = tkhd->layer;
    param->alternate_group = tkhd->alternate_group;
    param->audio_volume    = tkhd->volume;
    for( int i = 0; i < 9; i++ )
        param->matrix[i]   = tkhd->matrix[i];
    param->display_width   = tkhd->width;
    param->display_height  = tkhd->height;
    param->aperture_modes  = LSMASH_IS_EXISTING_BOX( trak->tapt );
    return 0;
}

static inline int check_dref_presence( isom_trak_t *trak )
{
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->dinf->dref ) )
        return LSMASH_ERR_NAMELESS;
    return 0;
}

uint32_t lsmash_count_data_reference
(
    lsmash_root_t *root,
    uint32_t       track_ID
)
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( check_dref_presence( trak ) < 0 )
        return 0;
    return trak->mdia->minf->dinf->dref->list.entry_count;
}

int lsmash_get_data_reference
(
    lsmash_root_t           *root,
    uint32_t                 track_ID,
    lsmash_data_reference_t *data_ref
)
{
    if( isom_check_initializer_present( root ) < 0 || !data_ref )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( check_dref_presence( trak ) < 0 )
        return LSMASH_ERR_NAMELESS;
    isom_dref_entry_t *url = lsmash_list_get_entry_data( &trak->mdia->minf->dinf->dref->list, data_ref->index );
    if( LSMASH_IS_NON_EXISTING_BOX( url ) )
        return LSMASH_ERR_NAMELESS;
    if( !(url->flags & 0x000001) && url->location )
    {
        int length = strlen( url->location );
        char *location = lsmash_malloc( length + 1 );
        if( !location )
            return LSMASH_ERR_MEMORY_ALLOC;
        memcpy( location, url->location, length );
        location[length] = '\0';
        data_ref->location = location;
    }
    else
        data_ref->location = NULL;
    return 0;
}

void lsmash_cleanup_data_reference
(
    lsmash_data_reference_t *data_ref
)
{
    if( !data_ref )
        return;
    lsmash_freep( &data_ref->location );
}

int lsmash_create_data_reference
(
    lsmash_root_t           *root,
    uint32_t                 track_ID,
    lsmash_data_reference_t *data_ref,
    lsmash_file_t           *file
)
{
    /* At present, we don't support external data references for movie fragments.
     * Note that, for external media data, default-base-is-moof is meaningless since relative
     * offsets from Movie Fragment Boxes make no sense.
     * In the future, the condition of !(file->flags & LSMASH_FILE_MODE_WRITE) may be removed
     * for the implementation which does not write actually and does reference read-only file. */
    if( LSMASH_IS_NON_EXISTING_BOX( root )
     || LSMASH_IS_NON_EXISTING_BOX( file )
     || file->root != root
     || (!(file->flags & LSMASH_FILE_MODE_MEDIA) && !(file->flags & LSMASH_FILE_MODE_INITIALIZATION))
     || !(file->flags & LSMASH_FILE_MODE_WRITE)
     || (root->file != file && ((file->flags & LSMASH_FILE_MODE_FRAGMENTED) || file->fragment))
     || !data_ref )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file, track_ID );
    if( check_dref_presence( trak ) < 0 )
        return LSMASH_ERR_NAMELESS;
    isom_dref_entry_t *url = isom_add_dref_entry( trak->mdia->minf->dinf->dref, ISOM_BOX_TYPE_URL );
    if( LSMASH_IS_NON_EXISTING_BOX( url ) )
        return LSMASH_ERR_NAMELESS;
    if( !data_ref->location || root->file == file )
    {
        /* Media data is in the same file. */
        url->flags    = 0x000001;
        url->ref_file = root->file;
    }
    else
    {
        /* Set the location of the file. */
        int length = strlen( data_ref->location );
        url->location = lsmash_malloc( length + 1 );
        if( !url->location )
        {
            isom_remove_box_by_itself( url );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        memcpy( url->location, data_ref->location, length );
        url->location[length] = '\0';
        url->location_length  = length + 1;
        url->ref_file         = file;
    }
    data_ref->index = trak->mdia->minf->dinf->dref->list.entry_count;
    return 0;
}

int lsmash_assign_data_reference
(
    lsmash_root_t *root,
    uint32_t       track_ID,
    uint32_t       data_ref_index,
    lsmash_file_t *file
)
{
    if( isom_check_initializer_present( root ) < 0
     || !file || file->root != root
     || !(file->flags & LSMASH_FILE_MODE_MEDIA)
     || !(file->flags & LSMASH_FILE_MODE_READ)
     || data_ref_index == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( check_dref_presence( trak ) < 0 )
        return LSMASH_ERR_NAMELESS;
    isom_dref_entry_t *url = (isom_dref_entry_t *)lsmash_list_get_entry_data( &trak->mdia->minf->dinf->dref->list, data_ref_index );
    if( LSMASH_IS_NON_EXISTING_BOX( url ) )
        return LSMASH_ERR_NAMELESS;
    if( !(url->flags & 0x000001) )
        /* Reference an external media data. */
        url->ref_file = file;
    return 0;
}

static int isom_set_media_handler_name( lsmash_file_t *file, uint32_t track_ID, char *handler_name )
{
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->hdlr ) )
        return LSMASH_ERR_NAMELESS;
    isom_hdlr_t *hdlr = trak->mdia->hdlr;
    uint8_t *name        = NULL;
    uint32_t name_length = strlen( handler_name ) + file->isom_compatible + file->qt_compatible;
    if( file->qt_compatible )
        name_length = LSMASH_MIN( name_length, 255 );
    if( name_length > hdlr->componentName_length && hdlr->componentName )
        name = lsmash_realloc( hdlr->componentName, name_length );
    else if( !hdlr->componentName )
        name = lsmash_malloc( name_length );
    else
        name = hdlr->componentName;
    if( !name )
        return LSMASH_ERR_MEMORY_ALLOC;
    if( file->qt_compatible )
        name[0] = name_length & 0xff;
    memcpy( name + file->qt_compatible, handler_name, strlen( handler_name ) );
    if( file->isom_compatible )
        name[name_length - 1] = 0;
    hdlr->componentName        = name;
    hdlr->componentName_length = name_length;
    return 0;
}

static int isom_set_data_handler_name( lsmash_file_t *file, uint32_t track_ID, char *handler_name )
{
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->hdlr ) )
        return LSMASH_ERR_NAMELESS;
    isom_hdlr_t *hdlr = trak->mdia->minf->hdlr;
    uint8_t *name        = NULL;
    uint32_t name_length = strlen( handler_name ) + file->isom_compatible + file->qt_compatible;
    if( file->qt_compatible )
        name_length = LSMASH_MIN( name_length, 255 );
    if( name_length > hdlr->componentName_length && hdlr->componentName )
        name = lsmash_realloc( hdlr->componentName, name_length );
    else if( !hdlr->componentName )
        name = lsmash_malloc( name_length );
    else
        name = hdlr->componentName;
    if( !name )
        return LSMASH_ERR_MEMORY_ALLOC;
    if( file->qt_compatible )
        name[0] = name_length & 0xff;
    memcpy( name + file->qt_compatible, handler_name, strlen( handler_name ) );
    if( file->isom_compatible )
        name[name_length - 1] = 0;
    hdlr->componentName        = name;
    hdlr->componentName_length = name_length;
    return 0;
}

uint32_t lsmash_get_media_timescale( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
        return 0;
    return trak->mdia->mdhd->timescale;
}

uint64_t lsmash_get_media_duration( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
        return 0;
    return trak->mdia->mdhd->duration;
}

uint64_t lsmash_get_track_duration( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return 0;
    return trak->tkhd->duration;
}

uint32_t lsmash_get_last_sample_delta( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file, track_ID );
    if( !trak->mdia->minf->stbl->stts->list
     || !trak->mdia->minf->stbl->stts->list->tail
     || !trak->mdia->minf->stbl->stts->list->tail->data )
        return 0;
    return ((isom_stts_entry_t *)trak->mdia->minf->stbl->stts->list->tail->data)->sample_delta;
}

uint32_t lsmash_get_start_time_offset( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    isom_trak_t *trak = isom_get_trak( root->file, track_ID );
    if( !trak->mdia->minf->stbl->ctts->list
     || !trak->mdia->minf->stbl->ctts->list->head
     || !trak->mdia->minf->stbl->ctts->list->head->data )
        return 0;
    return ((isom_ctts_entry_t *)trak->mdia->minf->stbl->ctts->list->head->data)->sample_offset;
}

uint32_t lsmash_get_composition_to_decode_shift( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    lsmash_file_t *file = root->file->initializer;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    uint32_t sample_count = isom_get_sample_count( trak );
    if( sample_count == 0 )
        return 0;
    isom_stbl_t *stbl = trak->mdia->minf->stbl;
    if( !stbl->stts->list
     || !stbl->ctts->list )
        return 0;
    if( !(file->max_isom_version >= 4 && stbl->ctts->version == 1) && !file->qt_compatible )
        return 0;   /* This movie shall not have composition to decode timeline shift. */
    lsmash_entry_t *stts_entry = stbl->stts->list->head;
    lsmash_entry_t *ctts_entry = stbl->ctts->list->head;
    if( !stts_entry || !ctts_entry )
        return 0;
    uint64_t dts       = 0;
    uint64_t cts       = 0;
    uint32_t ctd_shift = 0;
    uint32_t i         = 0;
    uint32_t j         = 0;
    for( uint32_t k = 0; k < sample_count; k++ )
    {
        isom_stts_entry_t *stts_data = (isom_stts_entry_t *)stts_entry->data;
        isom_ctts_entry_t *ctts_data = (isom_ctts_entry_t *)ctts_entry->data;
        if( !stts_data || !ctts_data )
            return 0;
        if( ctts_data->sample_offset != ISOM_NON_OUTPUT_SAMPLE_OFFSET )
        {
            cts = dts + (int32_t)ctts_data->sample_offset;
            if( dts > cts + ctd_shift )
                ctd_shift = dts - cts;
        }
        dts += stts_data->sample_delta;
        if( ++i == stts_data->sample_count )
        {
            stts_entry = stts_entry->next;
            if( !stts_entry )
                return 0;
            i = 0;
        }
        if( ++j == ctts_data->sample_count )
        {
            ctts_entry = ctts_entry->next;
            if( !ctts_entry )
                return 0;
            j = 0;
        }
    }
    return ctd_shift;
}

uint16_t lsmash_pack_iso_language( char *iso_language )
{
    if( !iso_language || strlen( iso_language ) != 3 )
        return 0;
    return (uint16_t)LSMASH_PACK_ISO_LANGUAGE( iso_language[0], iso_language[1], iso_language[2] );
}

static int isom_iso2mac_language( uint16_t ISO_language, uint16_t *MAC_language )
{
    assert( MAC_language );
    int i = 0;
    for( ; isom_languages[i].iso_name; i++ )
        if( ISO_language == isom_languages[i].iso_name )
            break;
    if( !isom_languages[i].iso_name )
        return LSMASH_ERR_NAMELESS;
    *MAC_language = isom_languages[i].mac_value;
    return 0;
}

static int isom_mac2iso_language( uint16_t MAC_language, uint16_t *ISO_language )
{
    assert( ISO_language );
    int i = 0;
    for( ; isom_languages[i].iso_name; i++ )
        if( MAC_language == isom_languages[i].mac_value )
            break;
    *ISO_language = isom_languages[i].iso_name ? isom_languages[i].iso_name : ISOM_LANGUAGE_CODE_UNDEFINED;
    return 0;
}

static int isom_set_media_language( lsmash_file_t *file, uint32_t track_ID, uint16_t ISO_language, uint16_t MAC_language )
{
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
        return LSMASH_ERR_NAMELESS;
    uint16_t language = 0;
    if( file->isom_compatible )
    {
        if( ISO_language )
            language = ISO_language;
        else if( MAC_language )
        {
            int err = isom_mac2iso_language( MAC_language, &language );
            if( err )
                return err;
        }
        else
            language = ISOM_LANGUAGE_CODE_UNDEFINED;
    }
    else if( file->qt_compatible )
    {
        if( ISO_language )
        {
            int err = isom_iso2mac_language( ISO_language, &language );
            if( err )
                return err;
        }
        else
            language = MAC_language;
    }
    else
        return LSMASH_ERR_INVALID_DATA;
    trak->mdia->mdhd->language = language;
    return 0;
}

int isom_add_sample_grouping( isom_box_t *parent, isom_grouping_type grouping_type )
{
    isom_sgpd_t *sgpd;
    isom_sbgp_t *sbgp;
    if( ((sgpd = isom_add_sgpd( parent )), LSMASH_IS_NON_EXISTING_BOX( sgpd ))
     || ((sbgp = isom_add_sbgp( parent )), LSMASH_IS_NON_EXISTING_BOX( sbgp )) )
        return LSMASH_ERR_NAMELESS;
    sbgp->grouping_type = grouping_type;
    sgpd->grouping_type = grouping_type;
    sgpd->version       = 1;    /* We use version 1 for Sample Group Description Box because it is recommended in the spec. */
    switch( grouping_type )
    {
        case ISOM_GROUP_TYPE_RAP :
            sgpd->default_length = 1;
            break;
        case ISOM_GROUP_TYPE_ROLL :
        case ISOM_GROUP_TYPE_PROL :
            sgpd->default_length = 2;
            break;
        default :
            /* We don't consider other grouping types currently. */
            break;
    }
    return 0;
}

static int isom_create_sample_grouping( isom_trak_t *trak, isom_grouping_type grouping_type )
{
    assert( LSMASH_IS_EXISTING_BOX( trak ) );
    lsmash_file_t *file = trak->file;
    switch( grouping_type )
    {
        case ISOM_GROUP_TYPE_RAP :
            assert( file->max_isom_version >= 6 );
            break;
        case ISOM_GROUP_TYPE_ROLL :
        case ISOM_GROUP_TYPE_PROL :
            assert( file->avc_extensions || file->qt_compatible );
            break;
        default :
            assert( 0 );
            break;
    }
    int err = isom_add_sample_grouping( (isom_box_t *)trak->mdia->minf->stbl, grouping_type );
    if( err < 0 )
        return err;
    if( trak->cache->fragment && file->max_isom_version >= 6 )
        switch( grouping_type )
        {
            case ISOM_GROUP_TYPE_RAP :
                trak->cache->fragment->rap_grouping = 1;
                break;
            case ISOM_GROUP_TYPE_ROLL :
            case ISOM_GROUP_TYPE_PROL :
                trak->cache->fragment->roll_grouping = 1;
                break;
            default :
                /* We don't consider other grouping types currently. */
                break;
        }
    return 0;
}

static int isom_compress_sample_size_table( isom_stbl_t *stbl )
{
    if( stbl->file->max_3gpp_version )
        /* 3GPP: Limitations to the ISO base media file format
         *  - compact sample sizes ('stz2') shall not be used for tracks containing H.263, MPEG-4 video, AMR, AMR-WB, AAC or Timed text.
         * Note that 'mp4a' check is incomplete here since this restriction is not applied to Enhanced aacPlus audio (HE-AAC v2). */
        for( lsmash_entry_t *entry = stbl->stsd->list.head; entry; entry = entry->next )
        {
            isom_sample_entry_t *sample_entry = (isom_sample_entry_t *)entry->data;
            if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
                return LSMASH_ERR_INVALID_DATA;
            lsmash_codec_type_t sample_type = sample_entry->type;
            if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_S263_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4V_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4A_AUDIO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_SAMR_AUDIO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_SAWB_AUDIO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_TX3G_TEXT ) )
                return 0;
        }
    if( LSMASH_IS_EXISTING_BOX( stbl->stsz ) && isom_is_variable_size( stbl ) )
    {
        int max_num_bits = 0;
        for( lsmash_entry_t *entry = stbl->stsz->list->head; entry; entry = entry->next )
        {
            isom_stsz_entry_t *data = (isom_stsz_entry_t *)entry->data;
            if( !data )
                return LSMASH_ERR_INVALID_DATA;
            int num_bits;
            for( num_bits = 1; data->entry_size >> num_bits; num_bits++ );
            if( max_num_bits < num_bits )
            {
                max_num_bits = num_bits;
                if( max_num_bits > 16 )
                    return 0;   /* not compressible */
            }
        }
        if( max_num_bits <= 16 && LSMASH_IS_BOX_ADDITION_SUCCESS( isom_add_stz2( stbl ) ) )
        {
            /* The sample size table can be compressed by using 'stz2'. */
            isom_stsz_t *stsz = stbl->stsz;
            isom_stz2_t *stz2 = stbl->stz2;
            stz2->sample_count = stsz->sample_count;
            if( max_num_bits <= 4 )
                stz2->field_size = 4;
            else if( max_num_bits <= 8 )
                stz2->field_size = 8;
            else
                stz2->field_size = 16;
            lsmash_list_move_entries( stz2->list, stsz->list );
            isom_remove_box_by_itself( stsz );
        }
    }
    return 0;
}

static int isom_add_dependency_type( isom_stbl_t *stbl, lsmash_file_t *file, lsmash_sample_property_t *prop )
{
    if( !file->qt_compatible && !file->avc_extensions )
        return 0;
    int compatibility = file->avc_extensions && file->qt_compatible ? 3
                      : file->qt_compatible                         ? 2
                      : file->avc_extensions                        ? 1
                      :                                               0;
    if( LSMASH_IS_EXISTING_BOX( stbl->sdtp ) )
        return isom_add_sdtp_entry( (isom_box_t *)stbl, prop, compatibility );
    /* no null check for prop */
    if( !prop->allow_earlier
     && !prop->leading
     && !prop->independent
     && !prop->disposable
     && !prop->redundant )
        return 0;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_sdtp( (isom_box_t *)stbl ) ) )
        return LSMASH_ERR_NAMELESS;
    uint32_t count = isom_get_sample_count_from_sample_table( stbl );
    /* fill past samples with ISOM_SAMPLE_*_UNKNOWN */
    lsmash_sample_property_t null_prop = { 0 };
    for( uint32_t i = 1; i < count; i++ )
    {
        int err = isom_add_sdtp_entry( (isom_box_t *)stbl, &null_prop, compatibility );
        if( err < 0 )
            return err;
    }
    return isom_add_sdtp_entry( (isom_box_t *)stbl, prop, compatibility );
}

void lsmash_initialize_media_parameters( lsmash_media_parameters_t *param )
{
    memset( param, 0, sizeof(lsmash_media_parameters_t) );
    param->timescale = 1;
}

int lsmash_set_media_parameters( lsmash_root_t *root, uint32_t track_ID, lsmash_media_parameters_t *param )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl ) )
        return LSMASH_ERR_NAMELESS;
    trak->mdia->mdhd->timescale = param->timescale;
    int err = isom_set_media_language( file, track_ID, param->ISO_language, param->MAC_language );
    if( err < 0 )
        return err;
    if( param->media_handler_name
     && (err = isom_set_media_handler_name( file, track_ID, param->media_handler_name )) < 0 )
        return err;
    if( file->qt_compatible && param->data_handler_name
     && (err = isom_set_data_handler_name( file, track_ID, param->data_handler_name )) < 0 )
        return err;
    if( (file->avc_extensions || file->qt_compatible) && param->roll_grouping
     && (err = isom_create_sample_grouping( trak, ISOM_GROUP_TYPE_ROLL )) < 0 )
        return err;
    if( (file->max_isom_version >= 6) && param->rap_grouping
     && (err = isom_create_sample_grouping( trak, ISOM_GROUP_TYPE_RAP )) < 0 )
        return err;
    if( !file->qt_compatible && param->compact_sample_size_table )
        trak->mdia->minf->stbl->compress_sample_size_table = isom_compress_sample_size_table;
    if( !param->no_sample_dependency_table )
        trak->mdia->minf->stbl->add_dependency_type = isom_add_dependency_type;
    return 0;
}

static uint32_t get_actual_handler_name_length( isom_hdlr_t *hdlr, lsmash_file_t *file )
{
    if( hdlr->componentName_length == 0 )
        return 0;
    uint32_t length;
    uint8_t *name;
    if( file->qt_compatible )
    {
        length = LSMASH_MIN( hdlr->componentName[0], hdlr->componentName_length - 1 );
        if( !file->isom_compatible )
            return length;
        name = &hdlr->componentName[1];
    }
    else
    {
        length = hdlr->componentName_length;
        name   = hdlr->componentName;
    }
    /* Considering fool-proof such as not terminated by '\0'. */
    uint32_t i = 0;
    while( i < length && name[i] )
        ++i;
    return i;
}

int lsmash_get_media_parameters( lsmash_root_t *root, uint32_t track_ID, lsmash_media_parameters_t *param )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->hdlr )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl ) )
        return LSMASH_ERR_NAMELESS;
    isom_mdhd_t *mdhd = trak->mdia->mdhd;
    isom_stbl_t *stbl = trak->mdia->minf->stbl;
    param->timescale    = mdhd->timescale;
    param->handler_type = trak->mdia->hdlr->componentSubtype;
    param->duration     = mdhd->duration;
    /* Whether sample grouping present. */
    {
        isom_sbgp_t *sbgp;
        isom_sgpd_t *sgpd;
        sbgp = isom_get_sample_to_group         ( stbl, ISOM_GROUP_TYPE_RAP );
        sgpd = isom_get_sample_group_description( stbl, ISOM_GROUP_TYPE_RAP );
        param->rap_grouping = LSMASH_IS_EXISTING_BOX( sbgp ) && LSMASH_IS_EXISTING_BOX( sgpd );
        sbgp = isom_get_roll_recovery_sample_to_group         ( &stbl->sbgp_list );
        sgpd = isom_get_roll_recovery_sample_group_description( &stbl->sgpd_list );
        param->roll_grouping = LSMASH_IS_EXISTING_BOX( sbgp ) && LSMASH_IS_EXISTING_BOX( sgpd );
    }
    /* Get media language. */
    if( mdhd->language >= 0x800 )
    {
        param->MAC_language = 0;
        param->ISO_language = mdhd->language;
    }
    else
    {
        param->MAC_language = mdhd->language;
        param->ISO_language = 0;
    }
    /* Get handler name(s). */
    isom_hdlr_t *hdlr = trak->mdia->hdlr;
    uint32_t actual_length = get_actual_handler_name_length( hdlr, file );
    uint32_t length = LSMASH_MIN( 255, actual_length );
    if( length )
    {
        memcpy( param->media_handler_name_shadow, hdlr->componentName + file->qt_compatible, length );
        param->media_handler_name_shadow[length] = '\0';
        param->media_handler_name = param->media_handler_name_shadow;
    }
    else
    {
        param->media_handler_name = NULL;
        memset( param->media_handler_name_shadow, 0, sizeof(param->media_handler_name_shadow) );
    }
    if( LSMASH_IS_EXISTING_BOX( trak->mdia->minf->hdlr ) )
    {
        hdlr = trak->mdia->minf->hdlr;
        actual_length = get_actual_handler_name_length( hdlr, file );
        length = LSMASH_MIN( 255, actual_length );
        if( length )
        {
            memcpy( param->data_handler_name_shadow, hdlr->componentName + file->qt_compatible, length );
            param->data_handler_name_shadow[length] = '\0';
            param->data_handler_name = param->data_handler_name_shadow;
        }
        else
        {
            param->data_handler_name = NULL;
            memset( param->data_handler_name_shadow, 0, sizeof(param->data_handler_name_shadow) );
        }
    }
    else
    {
        param->data_handler_name = NULL;
        memset( param->data_handler_name_shadow, 0, sizeof(param->data_handler_name_shadow) );
    }
    param->compact_sample_size_table  = LSMASH_IS_EXISTING_BOX( stbl->stz2 );
    param->no_sample_dependency_table = LSMASH_IS_NON_EXISTING_BOX( stbl->sdtp );
    param->reserved[0] = param->reserved[1] = 0;
    return 0;
}

/*---- movie manipulators ----*/

void lsmash_initialize_movie_parameters( lsmash_movie_parameters_t *param )
{
    memset( param, 0, sizeof(lsmash_movie_parameters_t) );
    param->timescale           = 600;
    param->playback_rate       = 0x00010000;
    param->playback_volume     = 0x0100;
}

int lsmash_set_movie_parameters( lsmash_root_t *root, lsmash_movie_parameters_t *param )
{
    if( LSMASH_IS_NON_EXISTING_BOX( root ) )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_mvhd_t *mvhd = file->moov->mvhd;
    mvhd->timescale = param->timescale;
    if( file->qt_compatible || file->itunes_movie )
    {
        mvhd->rate            = param->playback_rate;
        mvhd->volume          = param->playback_volume;
        mvhd->previewTime     = param->preview_time;
        mvhd->previewDuration = param->preview_duration;
        mvhd->posterTime      = param->poster_time;
    }
    else
    {
        mvhd->rate            = 0x00010000;
        mvhd->volume          = 0x0100;
        mvhd->previewTime     = 0;
        mvhd->previewDuration = 0;
        mvhd->posterTime      = 0;
    }
    return 0;
}

int lsmash_get_movie_parameters( lsmash_root_t *root, lsmash_movie_parameters_t *param )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_mvhd_t *mvhd = file->moov->mvhd;
    param->timescale           = mvhd->timescale;
    param->duration            = mvhd->duration;
    param->playback_rate       = mvhd->rate;
    param->playback_volume     = mvhd->volume;
    param->preview_time        = mvhd->previewTime;
    param->preview_duration    = mvhd->previewDuration;
    param->poster_time         = mvhd->posterTime;
    param->number_of_tracks    = file->moov->trak_list.entry_count;
    return 0;
}

uint32_t lsmash_get_movie_timescale( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0 )
        return 0;
    return root->file->initializer->moov->mvhd->timescale;
}

int lsmash_reserve_media_data_size
(
    lsmash_root_t        *root,
    uint64_t              media_data_size
)
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    if( LSMASH_IS_EXISTING_BOX( file->mdat )    /* whether the Media Data Box is already written or not */
     || file->fragment )                        /* For fragmented movies, this function makes no sense. */
        return LSMASH_ERR_NAMELESS;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mdat( file ) ) )
        return LSMASH_ERR_NAMELESS;
    file->mdat->reserved_size = media_data_size;
    return 0;
}

static int isom_scan_trak_profileLevelIndication
(
    isom_trak_t                         *trak,
    mp4a_audioProfileLevelIndication    *audio_pli,
    mp4sys_visualProfileLevelIndication *visual_pli
)
{
    isom_stsd_t *stsd = trak->mdia->minf->stbl->stsd;
    if( !stsd->list.head )
        return LSMASH_ERR_INVALID_DATA;
    for( lsmash_entry_t *entry = stsd->list.head; entry; entry = entry->next )
    {
        isom_sample_entry_t *sample_entry = (isom_sample_entry_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
            return LSMASH_ERR_INVALID_DATA;
        lsmash_codec_type_t sample_type = sample_entry->type;
        if( LSMASH_IS_EXISTING_BOX( trak->mdia->minf->vmhd ) )
        {
            if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC1_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC2_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC3_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVC4_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_AVCP_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_SVC1_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MVC1_VIDEO )
             || lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MVC2_VIDEO ) )
            {
                /* FIXME: Do we have to arbitrate like audio? */
                if( *visual_pli == MP4SYS_VISUAL_PLI_NONE_REQUIRED )
                    *visual_pli = MP4SYS_VISUAL_PLI_H264_AVC;
            }
            else
                *visual_pli = MP4SYS_VISUAL_PLI_NOT_SPECIFIED;
        }
        else if( LSMASH_IS_EXISTING_BOX( trak->mdia->minf->smhd ) )
        {
            if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4A_AUDIO ) )
            {
                isom_audio_entry_t *audio = (isom_audio_entry_t *)sample_entry;
                isom_esds_t *esds = (isom_esds_t *)isom_get_extension_box_format( &audio->extensions, ISOM_BOX_TYPE_ESDS );
                if( LSMASH_IS_NON_EXISTING_BOX( esds ) || !esds->ES )
                    return LSMASH_ERR_INVALID_DATA;
                lsmash_audio_summary_t *summary = (lsmash_audio_summary_t *)lsmash_create_summary( LSMASH_SUMMARY_TYPE_AUDIO );
                if( !summary )
                    continue;
                if( mp4sys_setup_summary_from_DecoderSpecificInfo( summary, esds->ES ) < 0 )
                    *audio_pli = MP4A_AUDIO_PLI_NOT_SPECIFIED;
                else
                    *audio_pli = mp4a_max_audioProfileLevelIndication( *audio_pli, mp4a_get_audioProfileLevelIndication( summary ) );
                lsmash_cleanup_summary( (lsmash_summary_t *)summary );
            }
            else
                /* NOTE: Audio CODECs other than 'mp4a' does not have appropriate pli. */
                *audio_pli = MP4A_AUDIO_PLI_NOT_SPECIFIED;
        }
        else
            ;   /* FIXME: Do we have to set OD_profileLevelIndication? */
    }
    return 0;
}

int isom_setup_iods( isom_moov_t *moov )
{
    if( LSMASH_IS_NON_EXISTING_BOX( moov->iods ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_iods( moov ) ) )
        return LSMASH_ERR_NAMELESS;
    isom_iods_t *iods = moov->iods;
    int err = LSMASH_ERR_NAMELESS;
    iods->OD = mp4sys_create_ObjectDescriptor( 1 ); /* NOTE: Use 1 for ObjectDescriptorID of IOD. */
    if( !iods->OD )
        goto fail;
    mp4a_audioProfileLevelIndication     audio_pli = MP4A_AUDIO_PLI_NONE_REQUIRED;
    mp4sys_visualProfileLevelIndication visual_pli = MP4SYS_VISUAL_PLI_NONE_REQUIRED;
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
            goto fail;
        if( (err = isom_scan_trak_profileLevelIndication( trak, &audio_pli, &visual_pli )) < 0 )
            goto fail;
        if( (err = mp4sys_create_ES_ID_Inc( iods->OD, trak->tkhd->track_ID )) < 0 )
            goto fail;
    }
    if( (err = mp4sys_to_InitialObjectDescriptor( iods->OD,
                                                  0, /* FIXME: I'm not quite sure what the spec says. */
                                                  MP4SYS_OD_PLI_NONE_REQUIRED, MP4SYS_SCENE_PLI_NONE_REQUIRED,
                                                  audio_pli, visual_pli,
                                                  MP4SYS_GRAPHICS_PLI_NONE_REQUIRED )) < 0 )
        goto fail;
    return 0;
fail:
    isom_remove_box_by_itself( iods );
    return err;
}

int lsmash_create_object_descriptor( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    /* Return error if this file is not compatible with MP4 file format. */
    if( !file->mp4_version1
     && !file->mp4_version2 )
        return LSMASH_ERR_FUNCTION_PARAM;
    return isom_setup_iods( file->moov );
}

/*---- finishing functions ----*/

int isom_complement_data_reference( isom_minf_t *minf )
{
    if( LSMASH_IS_NON_EXISTING_BOX( minf->dinf->dref ) )
        return LSMASH_ERR_INVALID_DATA;
    /* Complement data referece if absent. */
    if( !minf->dinf->dref->list.head )
    {
        isom_dref_entry_t *url = isom_add_dref_entry( minf->dinf->dref, ISOM_BOX_TYPE_URL );
        if( LSMASH_IS_NON_EXISTING_BOX( url ) )
            return LSMASH_ERR_NAMELESS;
        url->flags = 0x000001;  /* Media data is in the same file. */
    }
    return 0;
}

static lsmash_file_t *isom_get_written_media_file
(
    isom_trak_t *trak,
    uint32_t     sample_description_index
)
{
    isom_minf_t         *minf        = trak->mdia->minf;
    isom_sample_entry_t *description = (isom_sample_entry_t *)lsmash_list_get_entry_data( &minf->stbl->stsd->list, sample_description_index );
    isom_dref_entry_t   *dref_entry  = (isom_dref_entry_t *)lsmash_list_get_entry_data( &minf->dinf->dref->list, description ? description->data_reference_index : 1 );
    lsmash_file_t       *file        = (!dref_entry || LSMASH_IS_NON_EXISTING_BOX( dref_entry->ref_file )) ? trak->file : dref_entry->ref_file;
    if( !(file->flags & LSMASH_FILE_MODE_MEDIA)
     || !(file->flags & LSMASH_FILE_MODE_WRITE) )
        return trak->file;
    return file;
}

int isom_check_large_offset_requirement
(
    isom_moov_t *moov,
    uint64_t     meta_size
)
{
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        isom_stco_t *stco = trak->mdia->minf->stbl->stco;
        if( !stco->list->tail   /* no samples */
         || stco->large_presentation
         || (((isom_stco_entry_t *)stco->list->tail->data)->chunk_offset + moov->size + meta_size) <= UINT32_MAX )
        {
            entry = entry->next;
            continue;   /* no need to convert stco into co64 */
        }
        /* stco->co64 conversion */
        int err = isom_convert_stco_to_co64( trak->mdia->minf->stbl );
        if( err < 0 )
            return err;
        if( isom_update_box_size( moov ) == 0 )
            return LSMASH_ERR_INVALID_DATA;
        entry = moov->trak_list.head;   /* whenever any conversion, re-check all traks */
    }
    return 0;
}

void isom_add_preceding_box_size
(
    isom_moov_t *moov,
    uint64_t     preceding_size
)
{
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        /* Apply to the chunks in the same file. */
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        isom_stsc_t *stsc = trak->mdia->minf->stbl->stsc;
        isom_stco_t *stco = trak->mdia->minf->stbl->stco;
        lsmash_entry_t    *stsc_entry = stsc->list->head;
        isom_stsc_entry_t *stsc_data  = stsc_entry ? (isom_stsc_entry_t *)stsc_entry->data : NULL;
        uint32_t chunk_number = 1;
        for( lsmash_entry_t *stco_entry = stco->list->head; stco_entry; )
        {
            if( stsc_data
             && stsc_data->first_chunk == chunk_number )
            {
                lsmash_file_t *ref_file = isom_get_written_media_file( trak, stsc_data->sample_description_index );
                stsc_entry = stsc_entry->next;
                stsc_data  = stsc_entry ? (isom_stsc_entry_t *)stsc_entry->data : NULL;
                if( ref_file != trak->file )
                {
                    /* The chunks are not contained in the same file. Skip applying the offset.
                     * If no more stsc entries, the rest of the chunks is not contained in the same file. */
                    if( !stsc_entry || !stsc_data )
                        break;
                    while( stco_entry && chunk_number < stsc_data->first_chunk )
                    {
                        stco_entry = stco_entry->next;
                        ++chunk_number;
                    }
                    continue;
                }
            }
            if( stco->large_presentation )
                ((isom_co64_entry_t *)stco_entry->data)->chunk_offset += preceding_size;
            else
                ((isom_stco_entry_t *)stco_entry->data)->chunk_offset += preceding_size;
            stco_entry = stco_entry->next;
            ++chunk_number;
        }
    }
}

int isom_establish_movie( lsmash_file_t *file )
{
    assert( file == file->initializer );
    int err;
    if( (err = isom_check_mandatory_boxes( file ))   < 0
     || (err = isom_set_movie_creation_time( file )) < 0 )
        return err;
    if( isom_update_box_size( file->moov ) == 0 )
        return LSMASH_ERR_INVALID_DATA;
    return 0;
}

int lsmash_finish_movie
(
    lsmash_root_t        *root,
    lsmash_adhoc_remux_t *remux
)
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( !file->bs
     || LSMASH_IS_NON_EXISTING_BOX( file->initializer->moov ) )
        return LSMASH_ERR_INVALID_DATA;
    if( file->fragment )
        return isom_finish_final_fragment_movie( file, remux );
    if( file != file->initializer )
        return LSMASH_ERR_INVALID_DATA;
    int err;
    isom_moov_t *moov = file->moov;
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
         || !trak->cache
         || !trak->mdia->minf->stbl->stsd->list.head
         || !trak->mdia->minf->stbl->stsd->list.head->data
         || !trak->mdia->minf->stbl->stco->list
         || !trak->mdia->minf->stbl->stco->list->tail )
            return LSMASH_ERR_INVALID_DATA;
        if( (err = isom_complement_data_reference( trak->mdia->minf )) < 0 )
            return err;
        uint32_t track_ID         = trak->tkhd->track_ID;
        uint32_t related_track_ID = trak->related_track_ID;
        /* Disable the track if the track is a track reference chapter. */
        if( trak->is_chapter )
            trak->tkhd->flags &= ~ISOM_TRACK_ENABLED;
        if( trak->is_chapter && related_track_ID )
        {
            /* In order that the track duration of the chapter track doesn't exceed that of the related track. */
            lsmash_edit_t edit;
            edit.duration   = LSMASH_MIN( trak->tkhd->duration, lsmash_get_track_duration( root, related_track_ID ) );
            edit.start_time = 0;
            edit.rate       = ISOM_EDIT_MODE_NORMAL;
            if( (err = lsmash_create_explicit_timeline_map( root, track_ID, edit )) < 0 )
                return err;
        }
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        /* Compress sample size table. */
        if( stbl->compress_sample_size_table
         && (err = stbl->compress_sample_size_table( stbl )) < 0 )
            return err;
        /* Add stss box if any samples aren't sync sample. */
        if( !trak->cache->all_sync && !stbl->stss && !isom_add_stss( stbl ) )
            return LSMASH_ERR_NAMELESS;
        if( (err = isom_update_tkhd_duration( trak ))             < 0
         || (err = isom_update_bitrate_description( trak->mdia )) < 0 )
            return err;
    }
    if( file->mp4_version1 == 1 && (err = isom_setup_iods( moov )) < 0 )
        return err;
    if( (err = isom_establish_movie( file )) < 0 )
        return err;
    /* Write the size of Media Data Box here. */
    lsmash_bs_t *bs = file->bs;
    file->mdat->manager &= ~LSMASH_INCOMPLETE_BOX;
    if( (err = isom_write_box( bs, (isom_box_t *)file->mdat )) < 0 )
        return err;
    /* Write the Movie Box and a Meta Box if no optimization for progressive download. */
    uint64_t meta_size = LSMASH_IS_EXISTING_BOX( file->meta ) ? file->meta->size : 0;
    if( !remux )
    {
        if( (err = isom_write_box( bs, (isom_box_t *)file->moov )) < 0
         || (err = isom_write_box( bs, (isom_box_t *)file->meta )) < 0 )
            return err;
        file->size += moov->size + meta_size;
        return 0;
    }
    /* stco->co64 conversion, depending on last chunk's offset */
    if( (err = isom_check_large_offset_requirement( moov, meta_size )) < 0 )
        return err;
    /* now the amount of offset is fixed. */
    uint64_t mtf_size = moov->size + meta_size;     /* sum of size of boxes moved to front */
    /* buffer size must be at least mtf_size * 2 */
    remux->buffer_size = LSMASH_MAX( remux->buffer_size, mtf_size * 2 );
    /* Split to 2 buffers. */
    uint8_t *buf[2] = { NULL, NULL };
    if( (buf[0] = (uint8_t*)lsmash_malloc( remux->buffer_size )) == NULL )
        return LSMASH_ERR_MEMORY_ALLOC; /* NOTE: I think we still can fallback to "return isom_write_moov();" here. */
    size_t size = remux->buffer_size / 2;
    buf[1] = buf[0] + size;
    /* Now, the amount of the offset is fixed. apply it to stco/co64 */
    isom_add_preceding_box_size( moov, mtf_size );
    /* Backup starting area of mdat and write moov + meta there instead. */
    isom_mdat_t *mdat            = file->mdat;
    uint64_t     total           = file->size + mtf_size;
    uint64_t     placeholder_pos = mdat->pos;
    if( (err = lsmash_bs_write_seek( bs, placeholder_pos, SEEK_SET )) < 0 )
        goto fail;
    size_t read_num = size;
    lsmash_bs_read_data( bs, buf[0], &read_num );
    uint64_t read_pos = bs->offset;
    /* Write moov + meta there instead. */
    if( (err = lsmash_bs_write_seek( bs, placeholder_pos, SEEK_SET )) < 0
     || (err = isom_write_box( bs, (isom_box_t *)file->moov ))        < 0
     || (err = isom_write_box( bs, (isom_box_t *)file->meta ))        < 0 )
        goto fail;
    uint64_t write_pos = bs->offset;
    /* Update the positions */
    mdat->pos += mtf_size;
    /* Move Media Data Box. */
    if( (err = isom_rearrange_data( file, remux, buf, read_num, size, read_pos, write_pos, total )) < 0 )
        goto fail;
    file->size += mtf_size;
    lsmash_free( buf[0] );
    return 0;
fail:
    lsmash_free( buf[0] );
    return err;
}

int lsmash_set_last_sample_delta( lsmash_root_t *root, uint32_t track_ID, uint32_t sample_delta )
{
    if( isom_check_initializer_present( root ) < 0 || track_ID == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( file->fragment
     && file->fragment->movie )
    {
        isom_traf_t *traf = isom_get_traf( file->fragment->movie, track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( traf )
         || LSMASH_IS_NON_EXISTING_BOX( traf->tfhd )
         || !traf->cache )
            return LSMASH_ERR_NAMELESS;
        return isom_set_fragment_last_duration( traf, sample_delta );
    }
    if( file != file->initializer )
        return LSMASH_ERR_INVALID_DATA;
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsd )
     || (LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsz )
      && LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stz2 ))
     || !trak->cache
     || !trak->mdia->minf->stbl->stts->list )
        return LSMASH_ERR_NAMELESS;
    isom_stbl_t *stbl = trak->mdia->minf->stbl;
    isom_stts_t *stts = stbl->stts;
    uint32_t sample_count = isom_get_sample_count( trak );
    int err;
    if( !stts->list->tail )
    {
        if( sample_count == 0 )
            return 0;       /* no samples */
        if( sample_count > 1 )
            return LSMASH_ERR_INVALID_DATA; /* irregular sample_count */
        /* Set the duration of the first sample.
         * This duration is also the duration of the last sample. */
        if( (err = isom_add_stts_entry( stbl, sample_delta )) < 0 )
            return err;
        return lsmash_update_track_duration( root, track_ID, 0 );
    }
    uint32_t i = 0;
    for( lsmash_entry_t *entry = stts->list->head; entry; entry = entry->next )
        i += ((isom_stts_entry_t *)entry->data)->sample_count;
    if( sample_count < i )
        return LSMASH_ERR_INVALID_DATA;
    int no_last = (sample_count > i);
    isom_stts_entry_t *last_stts_data = (isom_stts_entry_t *)stts->list->tail->data;
    if( !last_stts_data )
        return LSMASH_ERR_INVALID_DATA;
    /* Consider QuikcTime fixed compression audio. */
    isom_audio_entry_t *audio = (isom_audio_entry_t *)lsmash_list_get_entry_data( &trak->mdia->minf->stbl->stsd->list,
                                                                                  trak->cache->chunk.sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( audio ) )
        return LSMASH_ERR_INVALID_DATA;
    if( (audio->manager & LSMASH_AUDIO_DESCRIPTION)
     && (audio->manager & LSMASH_QTFF_BASE)
     && (audio->version == 1)
     && (audio->compression_ID != QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION) )
    {
        if( audio->samplesPerPacket == 0 )
            return LSMASH_ERR_INVALID_DATA;
        int exclude_last_sample = no_last ? 0 : 1;
        uint32_t j = audio->samplesPerPacket;
        for( lsmash_entry_t *entry = stts->list->tail; entry && j > 1; entry = entry->prev )
        {
            isom_stts_entry_t *stts_data = (isom_stts_entry_t *)entry->data;
            if( !stts_data )
                return LSMASH_ERR_INVALID_DATA;
            for( uint32_t k = exclude_last_sample; k < stts_data->sample_count && j > 1; k++ )
            {
                sample_delta -= stts_data->sample_delta;
                --j;
            }
            exclude_last_sample = 0;
        }
    }
    /* Set sample_delta. */
    if( no_last )
    {
        /* The duration of the last sample is not set yet. */
        if( sample_count - i > 1 )
            return LSMASH_ERR_INVALID_DATA;
        /* Add a sample_delta. */
        if( sample_delta == last_stts_data->sample_delta )
            ++ last_stts_data->sample_count;
        else if( (err = isom_add_stts_entry( stbl, sample_delta )) < 0 )
            return err;
    }
    /* The duration of the last sample is already set. Replace it with a new one. */
    else if( (err = isom_replace_last_sample_delta( stbl, sample_delta )) < 0 )
        return err;
    return lsmash_update_track_duration( root, track_ID, sample_delta );
}

/*---- timeline manipulator ----*/

int lsmash_modify_explicit_timeline_map( lsmash_root_t *root, uint32_t track_ID, uint32_t edit_number, lsmash_edit_t edit )
{
    if( isom_check_initializer_present( root ) < 0
     || edit.start_time < -1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    isom_trak_t   *trak = isom_get_trak( file, track_ID );
    if( !trak->edts->elst->list )
        return LSMASH_ERR_NAMELESS;
    isom_elst_t       *elst = trak->edts->elst;
    isom_elst_entry_t *data = (isom_elst_entry_t *)lsmash_list_get_entry_data( elst->list, edit_number );
    if( !data )
        return LSMASH_ERR_NAMELESS;
    data->segment_duration = edit.duration;
    data->media_time       = edit.start_time;
    data->media_rate       = edit.rate;
    if( elst->pos == 0 || !file->fragment || file->bs->unseekable )
        return isom_update_tkhd_duration( trak );
    /* Rewrite the specified entry.
     * Note: we don't update the version of the Edit List Box. */
    lsmash_bs_t *bs = file->bs;
    uint64_t current_pos = bs->offset;
    uint64_t entry_pos = elst->pos + ISOM_LIST_FULLBOX_COMMON_SIZE + ((uint64_t)edit_number - 1) * (elst->version == 1 ? 20 : 12);
    lsmash_bs_write_seek( bs, entry_pos, SEEK_SET );
    if( elst->version )
    {
        lsmash_bs_put_be64( bs, data->segment_duration );
        lsmash_bs_put_be64( bs, data->media_time );
    }
    else
    {
        lsmash_bs_put_be32( bs, (uint32_t)LSMASH_MIN( data->segment_duration, UINT32_MAX ) );
        lsmash_bs_put_be32( bs, (uint32_t)data->media_time );
    }
    lsmash_bs_put_be32( bs, data->media_rate );
    int ret = lsmash_bs_flush_buffer( bs );
    lsmash_bs_write_seek( bs, current_pos, SEEK_SET );
    return ret;
}

int lsmash_create_explicit_timeline_map( lsmash_root_t *root, uint32_t track_ID, lsmash_edit_t edit )
{
    if( isom_check_initializer_present( root ) < 0 || edit.start_time < -1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return LSMASH_ERR_NAMELESS;
    edit.duration = (edit.duration || root->file->fragment) ? edit.duration
                  : trak->tkhd->duration ? trak->tkhd->duration
                  : isom_update_tkhd_duration( trak ) < 0 ? 0
                  : trak->tkhd->duration;
    if( (LSMASH_IS_NON_EXISTING_BOX( trak->edts )       && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_edts( trak ) ))
     || (LSMASH_IS_NON_EXISTING_BOX( trak->edts->elst ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_elst( trak->edts ) )) )
        return LSMASH_ERR_NAMELESS;
    int err = isom_add_elst_entry( trak->edts->elst, edit.duration, edit.start_time, edit.rate );
    if( err < 0 )
        return err;
    return isom_update_tkhd_duration( trak );
}

int lsmash_get_explicit_timeline_map( lsmash_root_t *root, uint32_t track_ID, uint32_t edit_number, lsmash_edit_t *edit )
{
    if( isom_check_initializer_present( root ) < 0 || !edit )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_elst_entry_t *data;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
        data = isom_timelime_get_explicit_timeline_map( root, track_ID, edit_number );
    else
    {
        if( LSMASH_IS_NON_EXISTING_BOX( trak->edts->elst ) )
        {
            /* no edits */
            edit->duration   = 0;
            edit->start_time = 0;
            edit->rate       = 0;
            return 0;
        }
        data = (isom_elst_entry_t *)lsmash_list_get_entry_data( trak->edts->elst->list, edit_number );
    }
    if( !data )
        return LSMASH_ERR_NAMELESS;
    edit->duration   = data->segment_duration;
    edit->start_time = data->media_time;
    edit->rate       = data->media_rate;
    return 0;
}

uint32_t lsmash_count_explicit_timeline_map( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
        return isom_timelime_count_explicit_timeline_map( root, track_ID );
    else
        return trak->edts->elst->list ? trak->edts->elst->list->entry_count : 0;
}

/*---- create / modification time fields manipulators ----*/

int lsmash_update_media_modification_time( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_mdhd_t *mdhd = trak->mdia->mdhd;
    mdhd->modification_time = isom_get_current_mp4time();
    /* overwrite strange creation_time */
    if( mdhd->creation_time > mdhd->modification_time )
        mdhd->creation_time = mdhd->modification_time;
    return 0;
}

int lsmash_update_track_modification_time( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_tkhd_t *tkhd = trak->tkhd;
    tkhd->modification_time = isom_get_current_mp4time();
    /* overwrite strange creation_time */
    if( tkhd->creation_time > tkhd->modification_time )
        tkhd->creation_time = tkhd->modification_time;
    return 0;
}

int lsmash_update_movie_modification_time( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_mvhd_t *mvhd = file->moov->mvhd;
    mvhd->modification_time = isom_get_current_mp4time();
    /* overwrite strange creation_time */
    if( mvhd->creation_time > mvhd->modification_time )
        mvhd->creation_time = mvhd->modification_time;
    return 0;
}

/*---- sample manipulators ----*/
lsmash_sample_t *lsmash_create_sample( uint32_t size )
{
    lsmash_sample_t *sample = lsmash_malloc_zero( sizeof(lsmash_sample_t) );
    if( !sample )
        return NULL;
    if( size == 0 )
        return sample;
    sample->data = lsmash_malloc( size );
    if( !sample->data )
    {
        lsmash_free( sample );
        return NULL;
    }
    sample->length = size;
    return sample;
}

int lsmash_sample_alloc( lsmash_sample_t *sample, uint32_t size )
{
    if( !sample )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( size == 0 )
    {
        lsmash_free( sample->data );
        sample->data   = NULL;
        sample->length = 0;
        return 0;
    }
    if( size == sample->length )
        return 0;
    uint8_t *data;
    if( !sample->data )
        data = lsmash_malloc( size );
    else
        data = lsmash_realloc( sample->data, size );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    sample->data   = data;
    sample->length = size;
    return 0;
}

void lsmash_delete_sample( lsmash_sample_t *sample )
{
    if( !sample )
        return;
    lsmash_free( sample->data );
    lsmash_free( sample );
}

isom_sample_pool_t *isom_create_sample_pool( uint64_t size )
{
    isom_sample_pool_t *pool = lsmash_malloc_zero( sizeof(isom_sample_pool_t) );
    if( !pool )
        return NULL;
    if( size == 0 )
        return pool;
    pool->data = lsmash_malloc( size );
    if( !pool->data )
    {
        lsmash_free( pool );
        return NULL;
    }
    pool->alloc = size;
    return pool;
}

void isom_remove_sample_pool( isom_sample_pool_t *pool )
{
    if( !pool )
        return;
    lsmash_free( pool->data );
    lsmash_free( pool );
}

static uint32_t isom_add_size( isom_stbl_t *stbl, uint32_t sample_size )
{
    if( isom_add_stsz_entry( stbl, sample_size ) < 0 )
        return 0;
    return isom_get_sample_count_from_sample_table( stbl );
}

static uint32_t isom_add_dts( isom_stbl_t *stbl, uint64_t dts, uint64_t prev_dts )
{
    isom_stts_t *stts = stbl->stts;
    if( stts->list->entry_count == 0 )
        return isom_add_stts_entry( stbl, dts ) < 0 ? 0 : dts;
    if( dts <= prev_dts )
        return 0;
    uint32_t sample_delta = dts - prev_dts;
    isom_stts_entry_t *data = (isom_stts_entry_t *)stts->list->tail->data;
    if( data->sample_delta == sample_delta )
        ++ data->sample_count;
    else if( isom_add_stts_entry( stbl, sample_delta ) < 0 )
        return 0;
    return sample_delta;
}

/* Add ctts box and the first ctts entry. */
static int isom_add_initial_sample_offset( isom_stbl_t *stbl, uint32_t sample_offset )
{
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_ctts( stbl ) ) )
        return LSMASH_ERR_NAMELESS;
    if( sample_offset == ISOM_NON_OUTPUT_SAMPLE_OFFSET )
        stbl->ctts->version = 1;
    uint32_t sample_count = isom_get_sample_count_from_sample_table( stbl );
    if( sample_count > 1 )
    {
        /* Set all prior samples' sample_offset to 0. */
        int err = isom_add_ctts_entry( stbl, sample_count - 1, 0 );
        if( err < 0 )
            return err;
    }
    return isom_add_ctts_entry( stbl, 1, sample_offset );
}

static int isom_add_sample_offset( isom_stbl_t *stbl, uint32_t sample_offset )
{
    if( !stbl->ctts->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_ctts_entry_t *data = (isom_ctts_entry_t *)stbl->ctts->list->tail->data;
    if( data->sample_offset == sample_offset )
        ++ data->sample_count;
    else
    {
        int err = isom_add_ctts_entry( stbl, 1, sample_offset );
        if( err < 0 )
            return err;
    }
    return 0;
}

static int isom_add_cts( isom_stbl_t *stbl, uint64_t dts, uint64_t cts, int non_output_sample )
{
    uint32_t sample_offset = !non_output_sample ? cts - dts : ISOM_NON_OUTPUT_SAMPLE_OFFSET;
    if( LSMASH_IS_EXISTING_BOX( stbl->ctts ) )
        return isom_add_sample_offset( stbl, sample_offset );
    return sample_offset != 0 ? isom_add_initial_sample_offset( stbl, sample_offset ) : 0;
}

static int isom_check_sample_offset_compatibility( lsmash_file_t *file, uint64_t dts, uint64_t cts, int non_output_sample )
{
    if( non_output_sample )
    {
        if( file->min_isom_version < 4 )
            return LSMASH_ERR_INVALID_DATA; /* Non-output sample can be indicated under 'iso4' or later brands. */
    }
    else
    {
        if( file->isom_compatible && file->qt_compatible && (((cts >= dts) ? (cts - dts) : (dts - cts)) > INT32_MAX) )
            return LSMASH_ERR_INVALID_DATA; /* sample_offset is not compatible with both ISOBMFF and QTFF. */
    }
    if( non_output_sample || cts < dts )
    {
        /* Negative sample offset is required. */
        if( file->max_isom_version <  4 && !file->qt_compatible )
            return LSMASH_ERR_INVALID_DATA; /* Negative sample offset is not supported in both ISOBMFF and QTFF. */
        if( file->max_isom_version >= 4 &&  file->qt_compatible )
            return LSMASH_ERR_INVALID_DATA; /* ctts version 1 is not defined in QTFF. */
    }
    return 0;
}

void isom_update_cache_timestamp
(
    isom_cache_t *cache,
    uint64_t      dts,
    uint64_t      cts,
    int32_t       ctd_shift,
    uint32_t      sample_duration,
    int           non_output_sample
)
{
    cache->timestamp.dts       = dts;
    cache->timestamp.cts       = non_output_sample ? cache->timestamp.cts : cts;
    cache->timestamp.ctd_shift = ctd_shift;
    if( cache->fragment )
    {
        cache->fragment->last_duration = sample_duration;
        if( !non_output_sample )
            cache->fragment->largest_cts
                = cache->fragment->largest_cts != LSMASH_TIMESTAMP_UNDEFINED
                ? LSMASH_MAX( cache->timestamp.cts, cache->fragment->largest_cts )
                : cache->timestamp.cts;
    }
}

static int isom_add_timestamp( isom_stbl_t *stbl, isom_cache_t *cache, lsmash_file_t *file, uint64_t dts, uint64_t cts )
{
    if( !cache || !stbl->stts->list )
        return LSMASH_ERR_INVALID_DATA;
    int non_output_sample = (cts == LSMASH_TIMESTAMP_UNDEFINED);
    int err = isom_check_sample_offset_compatibility( file, dts, cts, non_output_sample );
    if( err < 0 )
        return err;
    uint32_t sample_count = isom_get_sample_count_from_sample_table( stbl );
    uint32_t sample_delta = sample_count > 1 ? isom_add_dts( stbl, dts, cache->timestamp.dts ) : 0;
    if( sample_count > 1 && sample_delta == 0 )
        return LSMASH_ERR_INVALID_DATA;
    if( (err = isom_add_cts( stbl, dts, cts, non_output_sample )) < 0 )
        return err;
    int32_t ctd_shift = cache->timestamp.ctd_shift;
    if( !non_output_sample && ((cts + ctd_shift) < dts) )
    {
        /* Check overflow of composition to decode timeline shift. */
        if( (dts - cts) > INT32_MAX )
            return LSMASH_ERR_INVALID_DATA;
        assert( LSMASH_IS_EXISTING_BOX( stbl->ctts ) );
        if( stbl->ctts->version == 0 && !file->qt_compatible )
            stbl->ctts->version = 1;
        ctd_shift = dts - cts;
    }
    isom_update_cache_timestamp( cache, dts, cts, ctd_shift, sample_delta, non_output_sample );
    return 0;
}

static int isom_add_sync_point( isom_stbl_t *stbl, isom_cache_t *cache, uint32_t sample_number, lsmash_sample_property_t *prop )
{
    if( !(prop->ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC) )   /* no null check for prop */
    {
        if( !cache->all_sync )
            return 0;
        if( LSMASH_IS_NON_EXISTING_BOX( stbl->stss )
         && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stss( stbl ) ) )
            return LSMASH_ERR_NAMELESS;
        int err = isom_add_stss_entry( stbl, 1 );
        if( err < 0 )   /* Declare here the first sample is a sync sample. */
            return err;
        cache->all_sync = 0;
        return 0;
    }
    if( cache->all_sync )     /* We don't need stss box if all samples are sync sample. */
        return 0;
    if( LSMASH_IS_NON_EXISTING_BOX( stbl->stss ) )
    {
        if( isom_get_sample_count_from_sample_table( stbl ) == 1 )
        {
            cache->all_sync = 1;    /* Also the first sample is a sync sample. */
            return 0;
        }
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stss( stbl ) ) )
            return LSMASH_ERR_NAMELESS;
    }
    return isom_add_stss_entry( stbl, sample_number );
}

static int isom_add_partial_sync( isom_stbl_t *stbl, lsmash_file_t *file, uint32_t sample_number, lsmash_sample_property_t *prop )
{
    if( !file->qt_compatible )
        return 0;
    if( !(prop->ra_flags & QT_SAMPLE_RANDOM_ACCESS_FLAG_PARTIAL_SYNC) )
        return 0;
    /* This sample is a partial sync sample. */
    if( LSMASH_IS_NON_EXISTING_BOX( stbl->stps )
     && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stps( stbl ) ) )
        return LSMASH_ERR_NAMELESS;
    return isom_add_stps_entry( stbl, sample_number );
}

int isom_rap_grouping_established( isom_rap_group_t *group, int num_leading_samples_known, isom_sgpd_t *sgpd, int is_fragment )
{
    isom_rap_entry_t *rap = group->random_access;
    if( !rap )
        return 0;
    assert( rap == (isom_rap_entry_t *)sgpd->list->tail->data );
    rap->num_leading_samples_known = num_leading_samples_known;
    /* Avoid duplication of sample group descriptions. */
    uint32_t group_description_index = is_fragment ? 0x10001 : 1;
    for( lsmash_entry_t *entry = sgpd->list->head; entry != sgpd->list->tail; entry = entry->next )
    {
        isom_rap_entry_t *data = (isom_rap_entry_t *)entry->data;
        if( !data )
            return LSMASH_ERR_INVALID_DATA;
        if( rap->num_leading_samples_known == data->num_leading_samples_known
         && rap->num_leading_samples       == data->num_leading_samples )
        {
            /* The same description already exists.
             * Remove the latest random access entry. */
            lsmash_list_remove_entry_tail( sgpd->list );
            /* Replace assigned group_description_index with the one corresponding the same description. */
            if( group->assignment->group_description_index == 0 )
            {
                /* We don't create consecutive sample groups not assigned to 'rap '.
                 * So the previous sample group shall be a group of 'rap ' if any. */
                if( group->prev_assignment )
                {
                    assert( group->prev_assignment->group_description_index );
                    group->prev_assignment->group_description_index = group_description_index;
                }
            }
            else
                group->assignment->group_description_index = group_description_index;
            break;
        }
        ++group_description_index;
    }
    group->random_access = NULL;
    return 0;
}

int isom_group_random_access( isom_box_t *parent, isom_cache_t *cache, lsmash_sample_t *sample )
{
    if( parent->file->max_isom_version < 6 )
        return 0;
    isom_sbgp_t  *sbgp;
    isom_sgpd_t  *sgpd;
    uint32_t      sample_count;
    int           is_fragment;
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL ) )
    {
        isom_stbl_t *stbl = (isom_stbl_t *)parent;
        sbgp  = isom_get_sample_to_group         ( stbl, ISOM_GROUP_TYPE_RAP );
        sgpd  = isom_get_sample_group_description( stbl, ISOM_GROUP_TYPE_RAP );
        sample_count = isom_get_sample_count_from_sample_table( stbl );
        is_fragment  = 0;
    }
    else if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
    {
        isom_traf_t *traf = (isom_traf_t *)parent;
        sbgp  = isom_get_fragment_sample_to_group         ( traf, ISOM_GROUP_TYPE_RAP );
        sgpd  = isom_get_fragment_sample_group_description( traf, ISOM_GROUP_TYPE_RAP );
        sample_count = cache->fragment->sample_count + 1;   /* Cached sample_count is incremented later in isom_fragment_update_cache(). */
        is_fragment  = 1;
    }
    else
    {
        assert( 0 );
        sbgp  = isom_non_existing_sbgp();
        sgpd  = isom_non_existing_sgpd();
        /* redundant initializations to suppress warnings from unclever compilers */
        sample_count = 0;
        is_fragment  = 0;
    }
    if( LSMASH_IS_NON_EXISTING_BOX( sbgp )
     || LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
        return 0;
    lsmash_sample_property_t *prop = &sample->prop;
    uint8_t is_rap = (prop->ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC)
                  || (prop->ra_flags & QT_SAMPLE_RANDOM_ACCESS_FLAG_PARTIAL_SYNC)
                  || (prop->ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP)
                  || (LSMASH_IS_POST_ROLL_START( prop->ra_flags ) && prop->post_roll.identifier == prop->post_roll.complete);
    isom_rap_group_t *group = cache->rap;
    if( !group )
    {
        /* This sample is the first sample, create a grouping cache. */
        assert( sample_count == 1 );
        group = lsmash_malloc( sizeof(isom_rap_group_t) );
        if( !group )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( is_rap )
        {
            group->random_access = isom_add_rap_group_entry( sgpd );
            group->assignment    = isom_add_group_assignment_entry( sbgp, 1, sgpd->list->entry_count + (is_fragment ? 0x10000 : 0) );
        }
        else
        {
            /* The first sample is not always a random access point. */
            group->random_access = NULL;
            group->assignment    = isom_add_group_assignment_entry( sbgp, 1, 0 );
        }
        if( !group->assignment )
        {
            lsmash_free( group );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        group->prev_assignment = NULL;
        group->is_prev_rap     = is_rap;
        cache->rap             = group;
        return 0;
    }
    int err;
    if( group->is_prev_rap )
    {
        /* OK. here, the previous sample is a menber of 'rap '. */
        if( !is_rap )
        {
            /* This sample isn't a member of 'rap ' and the previous sample is.
             * So we create a new group and set 0 on its group_description_index. */
            group->prev_assignment = group->assignment;
            group->assignment      = isom_add_group_assignment_entry( sbgp, 1, 0 );
            if( !group->assignment )
            {
                lsmash_free( group );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
        else if( !LSMASH_IS_CLOSED_RAP( prop->ra_flags ) )
        {
            /* Create a new group since there is the possibility the next sample is a leading sample.
             * This sample is a member of 'rap ', so we set appropriate value on its group_description_index. */
            if( (err = isom_rap_grouping_established( group, 1, sgpd, is_fragment )) < 0 )
                return err;
            group->random_access   = isom_add_rap_group_entry( sgpd );
            group->prev_assignment = group->assignment;
            group->assignment      = isom_add_group_assignment_entry( sbgp, 1, sgpd->list->entry_count + (is_fragment ? 0x10000 : 0) );
            if( !group->assignment )
            {
                lsmash_free( group );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
        }
        else    /* The previous and current sample are a member of 'rap ', and the next sample must not be a leading sample. */
            ++ group->assignment->sample_count;
    }
    else if( is_rap )
    {
        /* This sample is a member of 'rap ' and the previous sample isn't.
         * So we create a new group and set appropriate value on its group_description_index. */
        if( (err = isom_rap_grouping_established( group, 1, sgpd, is_fragment )) < 0 )
            return err;
        group->random_access   = isom_add_rap_group_entry( sgpd );
        group->prev_assignment = group->assignment;
        group->assignment      = isom_add_group_assignment_entry( sbgp, 1, sgpd->list->entry_count + (is_fragment ? 0x10000 : 0) );
        if( !group->assignment )
        {
            lsmash_free( group );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
    }
    else    /* The previous and current sample aren't a member of 'rap '. */
        ++ group->assignment->sample_count;
    /* Obtain the property of the latest random access point group. */
    if( !is_rap && group->random_access )
    {
        if( prop->leading == ISOM_SAMPLE_LEADING_UNKNOWN )
        {
            /* We can no longer know num_leading_samples in this group. */
            if( (err = isom_rap_grouping_established( group, 0, sgpd, is_fragment )) < 0 )
                return err;
        }
        else
        {
            if( prop->leading == ISOM_SAMPLE_IS_UNDECODABLE_LEADING
             || prop->leading == ISOM_SAMPLE_IS_DECODABLE_LEADING )
                ++ group->random_access->num_leading_samples;
            /* no more consecutive leading samples in this group */
            else if( (err = isom_rap_grouping_established( group, 1, sgpd, is_fragment )) < 0 )
                return err;
        }
    }
    group->is_prev_rap = is_rap;
    return 0;
}

static int isom_roll_grouping_established( isom_roll_group_t *group )
{
    /* Avoid duplication of sample group descriptions. */
    isom_sgpd_t *sgpd = group->sgpd;
    uint32_t group_description_index = group->is_fragment ? 0x10001 : 1;
    for( lsmash_entry_t *entry = sgpd->list->head; entry; entry = entry->next )
    {
        isom_roll_entry_t *data = (isom_roll_entry_t *)entry->data;
        if( !data )
            return LSMASH_ERR_INVALID_DATA;
        if( group->roll_distance == data->roll_distance )
        {
            /* The same description already exists.
             * Set the group_description_index corresponding the same description. */
            group->assignment->group_description_index = group_description_index;
            return 0;
        }
        ++group_description_index;
    }
    /* Add a new roll recovery description. */
    if( !isom_add_roll_group_entry( sgpd, group->roll_distance ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    group->assignment->group_description_index = sgpd->list->entry_count + (group->is_fragment ? 0x10000 : 0);
    return 0;
}

static int isom_deduplicate_roll_group( isom_sbgp_t *sbgp, lsmash_entry_list_t *pool )
{
    /* Deduplication */
    uint32_t current_group_number = sbgp->list->entry_count - pool->entry_count + 1;
    isom_group_assignment_entry_t *prev_assignment = (isom_group_assignment_entry_t *)lsmash_list_get_entry_data( sbgp->list, current_group_number - 1 );
    for( lsmash_entry_t *entry = pool->head; entry; )
    {
        isom_roll_group_t *group = (isom_roll_group_t *)entry->data;
        if( !group
         || !group->assignment )
            return LSMASH_ERR_INVALID_DATA;
        if( !group->delimited || group->described != ROLL_DISTANCE_DETERMINED )
            return 0;
        if( prev_assignment && prev_assignment->group_description_index == group->assignment->group_description_index )
        {
            /* Merge the current group with the previous. */
            lsmash_entry_t *next_entry = entry->next;
            prev_assignment->sample_count += group->assignment->sample_count;
            int err;
            if( (err = lsmash_list_remove_entry( sbgp->list, current_group_number )) < 0
             || (err = lsmash_list_remove_entry_direct( pool, entry ))               < 0 )
                return err;
            entry = next_entry;
        }
        else
        {
            entry = entry->next;
            prev_assignment = group->assignment;
            ++current_group_number;
        }
    }
    return 0;
}

/* Remove pooled caches that has become unnecessary. */
static int isom_clean_roll_pool( lsmash_entry_list_t *pool )
{
    for( lsmash_entry_t *entry = pool->head; entry; entry = pool->head )
    {
        isom_roll_group_t *group = (isom_roll_group_t *)entry->data;
        if( !group )
            return LSMASH_ERR_INVALID_DATA;
        if( !group->delimited || group->described != ROLL_DISTANCE_DETERMINED )
            return 0;
        int err = lsmash_list_remove_entry_direct( pool, entry );
        if( err < 0 )
            return err;
    }
    return 0;
}

static int isom_flush_roll_pool( isom_sbgp_t *sbgp, lsmash_entry_list_t *pool )
{
    int err;
    for( lsmash_entry_t *entry = pool->head; entry; entry = entry->next )
    {
        isom_roll_group_t *group = (isom_roll_group_t *)entry->data;
        if( !group )
            return LSMASH_ERR_INVALID_DATA;
        if( group->delimited
         && group->described == ROLL_DISTANCE_DETERMINED
         && group->roll_distance != 0
         && (err = isom_roll_grouping_established( group )) < 0 )
            return err;
    }
    if( (err = isom_deduplicate_roll_group( sbgp, pool )) < 0 )
        return err;
    return isom_clean_roll_pool( pool );
}

static int isom_all_recovery_described( isom_sbgp_t *sbgp, lsmash_entry_list_t *pool )
{
    for( lsmash_entry_t *entry = pool->head; entry; entry = entry->next )
    {
        isom_roll_group_t *group = (isom_roll_group_t *)entry->data;
        if( !group )
            return LSMASH_ERR_INVALID_DATA;
        group->described = ROLL_DISTANCE_DETERMINED;
    }
    return isom_flush_roll_pool( sbgp, pool );
}

int isom_all_recovery_completed( isom_sbgp_t *sbgp, lsmash_entry_list_t *pool )
{
    for( lsmash_entry_t *entry = pool->head; entry; entry = entry->next )
    {
        isom_roll_group_t *group = (isom_roll_group_t *)entry->data;
        if( !group )
            return LSMASH_ERR_INVALID_DATA;
        group->described = ROLL_DISTANCE_DETERMINED;
        group->delimited = 1;
    }
    return isom_flush_roll_pool( sbgp, pool );
}

static isom_roll_entry_t *isom_get_roll_description
(
    isom_roll_group_t *group
)
{
    uint32_t group_description_index = group->assignment->group_description_index;
    if( group_description_index && group->is_fragment )
    {
        assert( group_description_index > 0x10000 );
        group_description_index -= 0x10000;
    }
    return (isom_roll_entry_t *)lsmash_list_get_entry_data( group->sgpd->list, group_description_index );
}

int isom_group_roll_recovery( isom_box_t *parent, isom_cache_t *cache, lsmash_sample_t *sample )
{
    if( !parent->file->avc_extensions
     && !parent->file->qt_compatible )
        return 0;
    uint32_t sample_count;
    int      is_fragment;
    lsmash_entry_list_t *sbgp_list;
    lsmash_entry_list_t *sgpd_list;
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL ) )
    {
        isom_stbl_t *stbl = (isom_stbl_t *)parent;
        sbgp_list = &stbl->sbgp_list;
        sgpd_list = &stbl->sgpd_list;
        sample_count = isom_get_sample_count_from_sample_table( stbl );
        is_fragment  = 0;
    }
    else if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
    {
        if( parent->file->max_isom_version < 6 )
            return 0;
        isom_traf_t *traf = (isom_traf_t *)parent;
        sbgp_list = &traf->sbgp_list;
        sgpd_list = &traf->sgpd_list;
        sample_count = cache->fragment->sample_count + 1;   /* Cached sample_count is incremented later in isom_fragment_update_cache(). */
        is_fragment  = 1;
    }
    else
    {
        assert( 0 );
        return LSMASH_ERR_INVALID_DATA;
    }
    isom_sbgp_t *sbgp = isom_get_roll_recovery_sample_to_group         ( sbgp_list );
    isom_sgpd_t *sgpd = isom_get_roll_recovery_sample_group_description( sgpd_list );
    if( LSMASH_IS_NON_EXISTING_BOX( sbgp )
     || LSMASH_IS_NON_EXISTING_BOX( sgpd )
     || sbgp->grouping_type != sgpd->grouping_type )
        return 0;
    /* Check if 'roll' -> 'prol' conversion is needed. */
    if( cache->is_audio
     && sbgp->grouping_type == ISOM_GROUP_TYPE_ROLL
     && !(sample->prop.ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC) )
    {
        /* Since not every samples is a sync sample, change grouping_type into 'prol'. */
        sbgp->grouping_type = ISOM_GROUP_TYPE_PROL;
        sgpd->grouping_type = ISOM_GROUP_TYPE_PROL;
    }
    lsmash_entry_list_t *pool = cache->roll.pool;
    if( !pool )
    {
        pool = lsmash_list_create_simple();
        if( !pool )
            return LSMASH_ERR_MEMORY_ALLOC;
        cache->roll.pool = pool;
    }
    lsmash_sample_property_t *prop  = &sample->prop;
    isom_roll_group_t        *group = (isom_roll_group_t *)lsmash_list_get_entry_data( pool, pool->entry_count );
    int is_recovery_start = LSMASH_IS_POST_ROLL_START( prop->ra_flags );
    int valid_pre_roll = !is_recovery_start
                      && (prop->ra_flags != ISOM_SAMPLE_RANDOM_ACCESS_FLAG_NONE)
                      && (prop->pre_roll.distance > 0)
                      && (prop->pre_roll.distance <= -INT16_MIN);
    int new_group = !group || is_recovery_start || (group->prev_is_recovery_start != is_recovery_start);
    if( !new_group )
    {
        /* Check pre-roll distance. */
        assert( group->assignment && group->sgpd );
        isom_roll_entry_t *prev_roll = isom_get_roll_description( group );
        if( !prev_roll )
            new_group = valid_pre_roll;
        else if( !valid_pre_roll || (prop->pre_roll.distance != -prev_roll->roll_distance) )
            /* Pre-roll distance is different from the previous. */
            new_group = 1;
    }
    if( new_group )
    {
        if( group )
            group->delimited = 1;
        else
            assert( sample_count == 1 );
        /* Create a new group. */
        group = lsmash_malloc_zero( sizeof(isom_roll_group_t) );
        if( !group )
            return LSMASH_ERR_MEMORY_ALLOC;
        group->sgpd                   = sgpd;
        group->prev_is_recovery_start = is_recovery_start;
        group->is_fragment            = is_fragment;
        group->assignment             = isom_add_group_assignment_entry( sbgp, 1, 0 );
        if( !group->assignment || lsmash_list_add_entry( pool, group ) < 0 )
        {
            lsmash_free( group );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        if( is_recovery_start )
        {
            /* a member of non-roll or post-roll group */
            group->first_sample   = sample_count;
            group->recovery_point = prop->post_roll.complete;
        }
        else
        {
            group->described = ROLL_DISTANCE_DETERMINED;
            if( valid_pre_roll )
            {
                /* a member of pre-roll group */
                group->roll_distance = -(signed)prop->pre_roll.distance;
                int err = isom_roll_grouping_established( group );
                if( err < 0 )
                    return err;
            }
            else
                /* a member of non-roll group */
                group->roll_distance = 0;
        }
    }
    else
    {
        group->prev_is_recovery_start    = is_recovery_start;
        group->assignment->sample_count += 1;
    }
    /* If encountered a RAP, all recovery is completed here. */
    if( prop->ra_flags & (ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC
                        | ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP
                        |   QT_SAMPLE_RANDOM_ACCESS_FLAG_PARTIAL_SYNC) )
        return isom_all_recovery_described( sbgp, pool );
    /* Check whether this sample is a random access recovery point or not. */
    for( lsmash_entry_t *entry = pool->head; entry; entry = entry->next )
    {
        group = (isom_roll_group_t *)entry->data;
        if( !group )
            return LSMASH_ERR_INVALID_DATA;
        if( group->described == ROLL_DISTANCE_DETERMINED )
            continue;
        if( group->described == ROLL_DISTANCE_INITIALIZED )
        {
            /* Let's consider the following picture sequence.
             *   coded order : P[0] P[1] P[2] P[3] P[4] P[5]
             *   DTS         :   0    1    2    3    4    5
             *   CTS         :   2    4    3    6    7    5
             * Here, P[0] conveys a recovery point SEI and P[3] is the recovery point.
             * Correctness of decoded pictures is specified by recovery point in output order for both AVC and HEVC.
             * Therefore, as follows,
             *   output order : P[0] P[2] P[1] P[5]|P[3] P[4]
             *                  ---(incorrect?)--->|
             * there is no guarantee that P[5] is decoded and output correctly.
             * From this, it can be said that the roll_distance of this sequence is equal to 5. */
            isom_roll_entry_t *post_roll = isom_get_roll_description( group );
            if( post_roll && post_roll->roll_distance > 0 )
            {
                if( sample->cts   != LSMASH_TIMESTAMP_UNDEFINED
                 && group->rp_cts != LSMASH_TIMESTAMP_UNDEFINED
                 && group->rp_cts > sample->cts )
                    /* Updated roll_distance for composition reordering. */
                    post_roll->roll_distance = sample_count - group->first_sample;
                if( ++ group->wait_and_see_count >= MAX_ROLL_WAIT_AND_SEE_COUNT )
                    group->described = ROLL_DISTANCE_DETERMINED;
            }
        }
        else if( prop->post_roll.identifier == group->recovery_point )
        {
            int16_t distance = sample_count - group->first_sample;
            group->rp_cts        = sample->cts;
            group->roll_distance = distance;
            /* Add a roll recovery entry only when roll_distance isn't zero since roll_distance = 0 must not be used. */
            if( distance )
            {
                /* Now, this group is a 'roll'.
                 * The roll_distance may be updated later because of composition reordering. */
                group->described          = ROLL_DISTANCE_INITIALIZED;
                group->wait_and_see_count = 0;
                /* All groups with uninitialized roll_distance before the current group are described. */
                lsmash_entry_t *current = entry;
                for( entry = pool->head; entry != current; entry = entry->next )
                {
                    group = (isom_roll_group_t *)entry->data;
                    if( !group || group->described != ROLL_DISTANCE_INITIALIZED )
                        continue;
                    group->described = ROLL_DISTANCE_DETERMINED;
                }
                /* Cache the mark of the first recovery point in a subsegment. */
                if( cache->fragment
                 && cache->fragment->subsegment.first_rp_number == 0 )
                    cache->fragment->subsegment.is_first_recovery_point = 1;
            }
            else
                /* Random Accessible Point */
                return isom_all_recovery_described( sbgp, pool );
        }
    }
    return isom_flush_roll_pool( sbgp, pool );
}

static int isom_update_chunk_tables
(
    isom_stbl_t   *stbl,
    lsmash_file_t *media_file,
    isom_chunk_t  *current
)
{
    isom_stsc_entry_t *last_stsc_data = stbl->stsc->list->tail ? (isom_stsc_entry_t *)stbl->stsc->list->tail->data : NULL;
    /* Create a new chunk sequence in this track if needed. */
    int err;
    if( (!last_stsc_data
      || current->pool->sample_count       != last_stsc_data->samples_per_chunk
      || current->sample_description_index != last_stsc_data->sample_description_index)
     && (err = isom_add_stsc_entry( stbl, current->chunk_number,
                                          current->pool->sample_count,
                                          current->sample_description_index )) < 0 )
        return err;
    /* Add a new chunk offset in this track. */
    uint64_t offset = media_file->size;
    if( media_file->fragment )
        offset += ISOM_BASEBOX_COMMON_SIZE + media_file->fragment->pool_size;
    return isom_add_stco_entry( stbl, offset );
}

/* This function decides to put a give sample on the current chunk or the next new one.
 * Returns 1 if pooled samples must be flushed.
 *   FIXME: I wonder if this function should have a extra argument which indicates force_to_flush_cached_chunk.
 *          see lsmash_append_sample for detail. */
static int isom_add_sample_to_chunk
(
    isom_trak_t     *trak,
    lsmash_sample_t *sample
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( trak->file )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->dinf->dref )
     || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsd )
     || !trak->cache
     ||  trak->mdia->mdhd->timescale == 0
     || !trak->mdia->minf->stbl->stsc->list )
        return LSMASH_ERR_INVALID_DATA;
    isom_chunk_t *current = &trak->cache->chunk;
    if( !current->pool )
    {
        /* Very initial settings, just once per track */
        current->pool = isom_create_sample_pool( 0 );
        if( !current->pool )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    if( current->pool->sample_count == 0 )
    {
        /* Cannot decide whether we should flush the current sample or not here yet. */
        current->chunk_number            += 1;
        current->sample_description_index = sample->index;
        current->first_dts                = sample->dts;
        return 0;
    }
    if( sample->dts < current->first_dts )
        return LSMASH_ERR_INVALID_DATA; /* easy error check. */
    lsmash_file_t *media_file = isom_get_written_media_file( trak, current->sample_description_index );
    if( (current->sample_description_index == sample->index)
     && (media_file->max_chunk_duration >= ((double)(sample->dts - current->first_dts) / trak->mdia->mdhd->timescale))
     && (media_file->max_chunk_size     >= current->pool->size + sample->length) )
        return 0;   /* No need to flush current cached chunk, the current sample must be put into that. */
    /* NOTE: chunk relative stuff must be pushed into file after a chunk is fully determined with its contents.
     * Now the current cached chunk is fixed, actually add the chunk relative properties to its file accordingly. */
    int err = isom_update_chunk_tables( trak->mdia->minf->stbl, media_file, current );
    if( err < 0 )
        return err;
    /* Update and re-initialize cache, using the current sample */
    current->chunk_number            += 1;
    current->sample_description_index = sample->index;
    current->first_dts                = sample->dts;
    /* current->pool must be flushed in isom_append_sample_internal() */
    return 1;
}

static int isom_write_pooled_samples( lsmash_file_t *file, isom_sample_pool_t *pool )
{
    if( LSMASH_IS_NON_EXISTING_BOX( file )
     || !file->bs
     || !file->bs->stream
     || !(file->flags & LSMASH_FILE_MODE_WRITE)
     || !(file->flags & LSMASH_FILE_MODE_MEDIA)
     || ((file->flags & LSMASH_FILE_MODE_BOX) && LSMASH_IS_NON_EXISTING_BOX( file->mdat )) )
        return LSMASH_ERR_INVALID_DATA;
    lsmash_bs_put_bytes( file->bs, pool->size, pool->data );
    int err = lsmash_bs_flush_buffer( file->bs );
    if( err < 0 )
        return err;
    if( LSMASH_IS_EXISTING_BOX( file->mdat ) )
        file->mdat->media_size += pool->size;
    file->size += pool->size;
    pool->sample_count = 0;
    pool->size         = 0;
    return 0;
}

int isom_update_sample_tables
(
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    uint32_t            *samples_per_packet,
    isom_sample_entry_t *sample_entry
)
{
    int err;
    isom_audio_entry_t *audio = (isom_audio_entry_t *)sample_entry;
    if( (audio->manager & LSMASH_AUDIO_DESCRIPTION)
     && (audio->manager & LSMASH_QTFF_BASE)
     && (audio->version == 1)
     && (audio->compression_ID != QT_AUDIO_COMPRESSION_ID_VARIABLE_COMPRESSION) )
    {
        /* Add entries of the sample table for each uncompressed sample. */
        uint64_t sample_duration = trak->mdia->mdhd->timescale / (audio->samplerate >> 16);
        if( audio->samplesPerPacket == 0 || sample_duration == 0 || sample->cts == LSMASH_TIMESTAMP_UNDEFINED )
            return LSMASH_ERR_INVALID_DATA;
        uint64_t sample_dts = sample->dts;
        uint64_t sample_cts = sample->cts;
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        for( uint32_t i = 0; i < audio->samplesPerPacket; i++ )
        {
            /* Add a size of uncomressed audio and increment sample_count.
             * This points to individual uncompressed audio samples, each one byte in size, within the compressed frames. */
            uint32_t sample_count = isom_add_size( stbl, 1 );
            if( sample_count == 0 )
                return LSMASH_ERR_NAMELESS;
            /* Add a decoding timestamp and a composition timestamp. */
            if( (err = isom_add_timestamp( stbl, trak->cache, trak->file, sample_dts, sample_cts )) < 0 )
                return err;
            sample_dts += sample_duration;
            sample_cts += sample_duration;
        }
        *samples_per_packet = audio->samplesPerPacket;
    }
    else
    {
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        /* Add a sample_size and increment sample_count. */
        uint32_t sample_count = isom_add_size( stbl, sample->length );
        if( sample_count == 0 )
            return LSMASH_ERR_NAMELESS;
        /* Add a decoding timestamp and a composition timestamp. */
        if( (err = isom_add_timestamp( stbl, trak->cache, trak->file, sample->dts, sample->cts )) < 0 )
            return err;
        /* Add a sync point if needed. */
        if( (err = isom_add_sync_point( stbl, trak->cache, sample_count, &sample->prop )) < 0 )
            return err;
        /* Add a partial sync point if needed. */
        if( (err = isom_add_partial_sync( stbl, trak->file, sample_count, &sample->prop )) < 0 )
            return err;
        /* Add leading, independent, disposable and redundant information if needed. */
        if( stbl->add_dependency_type
         && (err = stbl->add_dependency_type( stbl, trak->file, &sample->prop )) < 0 )
            return err;
        /* Group samples into random access point type if needed. */
        if( (err = isom_group_random_access( (isom_box_t *)stbl, trak->cache, sample )) < 0 )
            return err;
        /* Group samples into random access recovery point type if needed. */
        if( (err = isom_group_roll_recovery( (isom_box_t *)stbl, trak->cache, sample )) < 0 )
            return err;
        *samples_per_packet = 1;
    }
    /* Add a chunk if needed. */
    return isom_add_sample_to_chunk( trak, sample );
}

static int isom_output_cached_chunk( isom_trak_t *trak )
{
    isom_chunk_t      *chunk          = &trak->cache->chunk;
    isom_stbl_t       *stbl           = trak->mdia->minf->stbl;
    isom_stsc_entry_t *last_stsc_data = stbl->stsc->list->tail ? (isom_stsc_entry_t *)stbl->stsc->list->tail->data : NULL;
    /* Create a new chunk sequence in this track if needed. */
    int err;
    if( (!last_stsc_data
      || chunk->pool->sample_count       != last_stsc_data->samples_per_chunk
      || chunk->sample_description_index != last_stsc_data->sample_description_index)
     && (err = isom_add_stsc_entry( stbl, chunk->chunk_number,
                                          chunk->pool->sample_count,
                                          chunk->sample_description_index )) < 0 )
        return err;
    lsmash_file_t *file = isom_get_written_media_file( trak, chunk->sample_description_index );
    if( file->fragment )
    {
        /* Add a new chunk offset in this track. */
        if( (err = isom_add_stco_entry( stbl, file->size + ISOM_BASEBOX_COMMON_SIZE + file->fragment->pool_size )) < 0 )
            return err;
        return isom_append_fragment_track_run( file, chunk );
    }
    /* Add a new chunk offset in this track. */
    if( (err = isom_add_stco_entry( stbl, file->size )) < 0 )
        return err;
    /* Output pooled samples in this track. */
    return isom_write_pooled_samples( file, chunk->pool );
}

int isom_pool_sample( isom_sample_pool_t *pool, lsmash_sample_t *sample, uint32_t samples_per_packet )
{
    uint64_t pool_size = pool->size + sample->length;
    if( pool->alloc < pool_size )
    {
        uint8_t *data;
        uint64_t alloc = pool_size + (1<<16);
        if( !pool->data )
            data = lsmash_malloc( alloc );
        else
            data = lsmash_realloc( pool->data, alloc );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        pool->data  = data;
        pool->alloc = alloc;
    }
    memcpy( pool->data + pool->size, sample->data, sample->length );
    pool->size          = pool_size;
    pool->sample_count += samples_per_packet;
    lsmash_delete_sample( sample );
    return 0;
}

static int isom_append_sample_internal
(
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry
)
{
    uint32_t samples_per_packet;
    int ret = isom_update_sample_tables( trak, sample, &samples_per_packet, sample_entry );
    if( ret < 0 )
        return ret;
    /* ret == 1 means pooled samples must be flushed. */
    isom_sample_pool_t *current_pool = trak->cache->chunk.pool;
    if( ret == 1 )
    {
        /* The sample_description_index in the cache is one of the next written chunk.
         * Therefore, it cannot be referenced here. */
        lsmash_entry_list_t *stsc_list      = trak->mdia->minf->stbl->stsc->list;
        isom_stsc_entry_t   *last_stsc_data = (isom_stsc_entry_t *)stsc_list->tail->data;
        lsmash_file_t       *file           = isom_get_written_media_file( trak, last_stsc_data->sample_description_index );
        if( (ret = isom_write_pooled_samples( file, current_pool )) < 0 )
            return ret;
    }
    /* Arbitration system between tracks with extremely scattering dts.
     * Here, we check whether asynchronization between the tracks exceeds the tolerance.
     * If a track has too old "first DTS" in its cached chunk than current sample's DTS, then its pooled samples must be flushed.
     * We don't consider presentation of media since any edit can pick an arbitrary portion of media in track.
     * Note: you needn't read this loop until you grasp the basic handling of chunks. */
    lsmash_file_t *file = trak->file;
    double tolerance = file->max_async_tolerance;
    for( lsmash_entry_t *entry = file->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *other = (isom_trak_t *)entry->data;
        if( trak == other )
            continue;
        if( LSMASH_IS_NON_EXISTING_BOX( other )
         || LSMASH_IS_NON_EXISTING_BOX( other->mdia->mdhd )
         || !other->cache
         ||  other->mdia->mdhd->timescale == 0
         || !other->mdia->minf->stbl->stsc->list )
            return LSMASH_ERR_INVALID_DATA;
        isom_chunk_t *chunk = &other->cache->chunk;
        if( !chunk->pool || chunk->pool->sample_count == 0 )
            continue;
        double diff = ((double)sample->dts      /  trak->mdia->mdhd->timescale)
                    - ((double)chunk->first_dts / other->mdia->mdhd->timescale);
        if( diff > tolerance && (ret = isom_output_cached_chunk( other )) < 0 )
            return ret;
        /* Note: we don't flush the cached chunk in the current track and the current sample here
         * even if the conditional expression of '-diff > tolerance' meets.
         * That's useless because appending a sample to another track would be a good equivalent.
         * It's even harmful because it causes excess chunk division by calling
         * isom_output_cached_chunk() which always generates a new chunk.
         * Anyway some excess chunk division will be there, but rather less without it.
         * To completely avoid this, we need to observe at least whether the current sample will be placed
         * right next to the previous chunk of the same track or not. */
    }
    /* anyway the current sample must be pooled. */
    return isom_pool_sample( current_pool, sample, samples_per_packet );
}

int isom_append_sample_by_type
(
    void                *track,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry,
    int (*func_append_sample)( void *, lsmash_sample_t *, isom_sample_entry_t * )
)
{
    if( isom_is_lpcm_audio( sample_entry ) )
    {
        uint32_t frame_size = ((isom_audio_entry_t *)sample_entry)->constBytesPerAudioPacket;
        if( sample->length == frame_size )
            return func_append_sample( track, sample, sample_entry );
        else if( sample->length < frame_size || sample->cts == LSMASH_TIMESTAMP_UNDEFINED )
            return LSMASH_ERR_INVALID_DATA;
        /* Append samples splitted into each LPCMFrame. */
        uint64_t dts = sample->dts;
        uint64_t cts = sample->cts;
        for( uint32_t offset = 0; offset < sample->length; offset += frame_size )
        {
            lsmash_sample_t *lpcm_sample = lsmash_create_sample( frame_size );
            if( !lpcm_sample )
                return LSMASH_ERR_MEMORY_ALLOC;
            memcpy( lpcm_sample->data, sample->data + offset, frame_size );
            lpcm_sample->dts   = dts++;
            lpcm_sample->cts   = cts++;
            lpcm_sample->prop  = sample->prop;
            lpcm_sample->index = sample->index;
            int err = func_append_sample( track, lpcm_sample, sample_entry );
            if( err < 0 )
            {
                lsmash_delete_sample( lpcm_sample );
                return err;
            }
        }
        lsmash_delete_sample( sample );
        return 0;
    }
    else if( lsmash_check_codec_type_identical( sample_entry->type, ISOM_CODEC_TYPE_RTP_HINT  )
          || lsmash_check_codec_type_identical( sample_entry->type, ISOM_CODEC_TYPE_RRTP_HINT ) )
    {
        /* calculate PDU statistics for hmhd box. 
         * It requires accessing sample data to get the number of packets per sample. */
        isom_trak_t *trak = (isom_trak_t*)track;
        isom_hmhd_t *hmhd = trak->mdia->minf->hmhd;
        uint16_t packetcount = LSMASH_GET_BE16( sample->data );
        uint8_t *data = sample->data + RTP_SAMPLE_HEADER_SIZE + RTP_PACKET_SIZE;
        /* Calculate only packet headers and packet payloads sizes int PDU size. Later use these two to get avgPDUsize. */
        hmhd->combinedPDUsize += sample->length - (packetcount * RTP_CONSTRUCTOR_SIZE) - RTP_SAMPLE_HEADER_SIZE;
        hmhd->PDUcount        += packetcount;
        for( unsigned int i = 0; i < packetcount; i++ )
        {
            /* constructor type */
            if( *data == 2 )
            {
                /* payload size*/
                uint16_t length = *(data + 2);
                /* Check if this packet is larger than any of the previous ones. */
                hmhd->maxPDUsize = hmhd->maxPDUsize > length + RTP_HEADER_SIZE ? hmhd->maxPDUsize : length + RTP_HEADER_SIZE;
                data += RTP_CONSTRUCTOR_SIZE + RTP_PACKET_SIZE;
            } /* TODO: other constructor types */
        }
    } /* TODO: add other hint tracks that have a hmhd box */
    return func_append_sample( track, sample, sample_entry );
}

/* This function is for non-fragmented movie. */
static int isom_append_sample
(
    lsmash_file_t       *file,
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry
)
{
    /* If there is no available Media Data Box to write samples, add and write a new one before any chunk offset is decided. */
    int err;
    int mdat_absent = LSMASH_IS_NON_EXISTING_BOX( file->mdat );
    if( mdat_absent || !(file->mdat->manager & LSMASH_INCOMPLETE_BOX) )
    {
        if( mdat_absent && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mdat( file ) ) )
            return LSMASH_ERR_NAMELESS;
        file->mdat->manager |= LSMASH_PLACEHOLDER;
        if( (err = isom_write_box( file->bs, (isom_box_t *)file->mdat )) < 0 )
            return err;
        file->size += file->mdat->size;
    }
    return isom_append_sample_by_type( trak, sample, sample_entry, (int (*)( void *, lsmash_sample_t *, isom_sample_entry_t * ))isom_append_sample_internal );
}

static int isom_output_cache( isom_trak_t *trak )
{
    int err;
    isom_cache_t *cache = trak->cache;
    if( cache->chunk.pool
     && cache->chunk.pool->sample_count
     && (err = isom_output_cached_chunk( trak )) < 0 )
        return err;
    isom_stbl_t *stbl = trak->mdia->minf->stbl;
    for( lsmash_entry_t *entry = stbl->sgpd_list.head; entry; entry = entry->next )
    {
        isom_sgpd_t *sgpd = (isom_sgpd_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
            return LSMASH_ERR_INVALID_DATA;
        switch( sgpd->grouping_type )
        {
            case ISOM_GROUP_TYPE_RAP :
            {
                isom_rap_group_t *group = cache->rap;
                if( !group )
                {
                    if( stbl->file->fragment )
                        continue;
                    else
                        return LSMASH_ERR_NAMELESS;
                }
                if( !group->random_access )
                    continue;
                group->random_access->num_leading_samples_known = 1;
                break;
            }
            case ISOM_GROUP_TYPE_ROLL :
            case ISOM_GROUP_TYPE_PROL :
                if( !cache->roll.pool )
                {
                    if( stbl->file->fragment )
                        continue;
                    else
                        return LSMASH_ERR_NAMELESS;
                }
                isom_sbgp_t *sbgp = isom_get_roll_recovery_sample_to_group( &stbl->sbgp_list );
                if( LSMASH_IS_NON_EXISTING_BOX( sbgp ) )
                    return LSMASH_ERR_NAMELESS;
                if( (err = isom_all_recovery_completed( sbgp, cache->roll.pool )) < 0 )
                    return err;
                break;
            default :
                break;
        }
    }
    return 0;
}

int lsmash_flush_pooled_samples( lsmash_root_t *root, uint32_t track_ID, uint32_t last_sample_delta )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( file->fragment
     && file->fragment->movie )
        return isom_flush_fragment_pooled_samples( file, track_ID, last_sample_delta );
    if( file != file->initializer )
        return LSMASH_ERR_INVALID_DATA;
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak )
     || !trak->cache
     || !trak->mdia->minf->stbl->stsc->list )
        return LSMASH_ERR_NAMELESS;
    int err = isom_output_cache( trak );
    if( err < 0 )
        return err;
    return lsmash_set_last_sample_delta( root, track_ID, last_sample_delta );
}

int lsmash_append_sample( lsmash_root_t *root, uint32_t track_ID, lsmash_sample_t *sample )
{
    if( isom_check_initializer_present( root ) < 0
     || track_ID     == 0
     || sample       == NULL
     || sample->data == NULL
     || sample->dts  == LSMASH_TIMESTAMP_UNDEFINED )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    /* We think max_chunk_duration == 0, which means all samples will be cached on memory, should be prevented.
     * This means removal of a feature that we used to have, but anyway very alone chunk does not make sense. */
    if( !file->bs
     || !(file->flags & LSMASH_FILE_MODE_BOX)
     || file->max_chunk_duration  == 0
     || file->max_async_tolerance == 0 )
        return LSMASH_ERR_NAMELESS;
    /* Write File Type Box here if it was not written yet. */
    if( file->flags & LSMASH_FILE_MODE_INITIALIZATION )
    {
        if( LSMASH_IS_EXISTING_BOX( file->ftyp ) && !(file->ftyp->manager & LSMASH_WRITTEN_BOX) )
        {
            int err = isom_write_box( file->bs, (isom_box_t *)file->ftyp );
            if( err < 0 )
                return err;
            file->size += file->ftyp->size;
        }
    }
    /* Get a sample initializer. */
    isom_trak_t *trak = isom_get_trak( file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->file )
     || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
     ||  trak->mdia->mdhd->timescale == 0
     || !trak->cache
     || !trak->mdia->minf->stbl->stsc->list )
        return LSMASH_ERR_NAMELESS;
    isom_sample_entry_t *sample_entry = (isom_sample_entry_t *)lsmash_list_get_entry_data( &trak->mdia->minf->stbl->stsd->list, sample->index );
    if( LSMASH_IS_NON_EXISTING_BOX( sample_entry ) )
        return LSMASH_ERR_NAMELESS;
    /* Append a sample. */
    if( (file->flags & LSMASH_FILE_MODE_FRAGMENTED)
     && file->fragment
     && file->fragment->pool )
        return isom_append_fragment_sample( file, trak, sample, sample_entry );
    if( file != file->initializer )
        return LSMASH_ERR_INVALID_DATA;
    return isom_append_sample( file, trak, sample, sample_entry );
}

/*---- misc functions ----*/

int lsmash_delete_explicit_timeline_map( lsmash_root_t *root, uint32_t track_ID )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_trak_t *trak = isom_get_trak( root->file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
        return LSMASH_ERR_NAMELESS;
    isom_remove_box_by_itself( trak->edts );
    return isom_update_tkhd_duration( trak );
}

void lsmash_delete_tyrant_chapter( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0
     || LSMASH_IS_NON_EXISTING_BOX( root->file->initializer->moov->udta ) )
        return;
    isom_remove_box_by_itself( root->file->moov->udta->chpl );
}

int lsmash_set_sdp( lsmash_root_t *root, uint32_t track_ID, char *sdptext )
{
    if( isom_check_initializer_present( root ) < 0 || sdptext == NULL )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov ) || !file->isom_compatible )
        return LSMASH_ERR_NAMELESS;
    isom_udta_t *udta;
    if( track_ID )
    {
        isom_trak_t *trak = isom_get_trak( file, track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
            return LSMASH_ERR_NAMELESS;
        if( LSMASH_IS_NON_EXISTING_BOX( trak->udta )
         && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( trak ) ) )
            return LSMASH_ERR_NAMELESS;
        udta = trak->udta;
    }
    else
    {
        if( LSMASH_IS_NON_EXISTING_BOX( file->moov->udta )
         && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( file->moov ) ) )
            return LSMASH_ERR_NAMELESS;
        udta = file->moov->udta;
    }
    assert( LSMASH_IS_EXISTING_BOX( udta ) );
    if( LSMASH_IS_NON_EXISTING_BOX( udta->hnti )
     && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_hnti( udta ) ) )
        return LSMASH_ERR_NAMELESS;
    isom_hnti_t *hnti = udta->hnti;
    /* If track ID is given, text is meant for track hnti box,
     * otherwise it is meant for movie 'hnti' box. */
    if( track_ID )
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_sdp( hnti ) ) )
            return LSMASH_ERR_NAMELESS;
        isom_sdp_t *sdp = hnti->sdp;
        sdp->sdp_length = strlen( sdptext );    /* leaves \0 out*/
        sdp->sdptext    = lsmash_memdup( sdptext, sdp->sdp_length );
        if( !sdp->sdptext )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    else
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_rtp( hnti ) ) )
            return LSMASH_ERR_NAMELESS;
        isom_rtp_t *rtp = hnti->rtp;
        rtp->descriptionformat = LSMASH_4CC( 's', 'd', 'p', ' ' );
        rtp->sdp_length        = strlen( sdptext );     /* leaves \0 out */
        rtp->sdptext           = lsmash_memdup( sdptext, rtp->sdp_length );
        if( !rtp->sdptext )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

int lsmash_set_copyright( lsmash_root_t *root, uint32_t track_ID, uint16_t ISO_language, char *notice )
{
    if( isom_check_initializer_present( root ) < 0
     || (ISO_language && ISO_language < 0x800)
     || !notice )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( !file->isom_compatible )
        return LSMASH_ERR_NAMELESS;
    isom_udta_t *udta;
    if( track_ID )
    {
        isom_trak_t *trak = isom_get_trak( file, track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trak->udta ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( trak ) ) )
            return LSMASH_ERR_NAMELESS;
        udta = trak->udta;
    }
    else
    {
        if( LSMASH_IS_NON_EXISTING_BOX( file->moov->udta ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( file->moov ) ) )
            return LSMASH_ERR_NAMELESS;
        udta = file->moov->udta;
    }
    assert( LSMASH_IS_EXISTING_BOX( udta ) );
    for( lsmash_entry_t *entry = udta->cprt_list.head; entry; entry = entry->next )
    {
        isom_cprt_t *cprt = (isom_cprt_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( cprt ) || cprt->language == ISO_language )
            return LSMASH_ERR_NAMELESS;
    }
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_cprt( udta ) ) )
        return LSMASH_ERR_NAMELESS;
    isom_cprt_t *cprt = (isom_cprt_t *)udta->cprt_list.tail->data;
    cprt->language      = ISO_language;
    cprt->notice_length = strlen( notice ) + 1;
    cprt->notice        = lsmash_memdup( notice, cprt->notice_length );
    return 0;
}

/*****************************************************************************
 * fragment.c
 *****************************************************************************
 * Copyright (C) 2011-2017 L-SMASH project
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

#include <string.h>
#include "box.h"
#include "box_default.h"
#include "file.h"
#include "write.h"
#include "fragment.h"

static isom_sidx_t *isom_get_sidx( lsmash_file_t *file, uint32_t reference_ID )
{
    if( reference_ID == 0 || !file )
        return isom_non_existing_sidx();
    for( lsmash_entry_t *entry = file->sidx_list.head; entry; entry = entry->next )
    {
        isom_sidx_t *sidx = (isom_sidx_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
            return isom_non_existing_sidx();
        if( sidx->reference_ID == reference_ID )
            return sidx;
    }
    return isom_non_existing_sidx();
}

static int isom_finish_fragment_movie( lsmash_file_t *file );

/* A movie fragment cannot switch a sample description to another.
 * So you must call this function before switching sample descriptions. */
int lsmash_create_fragment_movie( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( !file->bs
     || !file->fragment )
        return LSMASH_ERR_NAMELESS;
    /* Finish and write the current movie fragment before starting a new one. */
    int ret = isom_finish_fragment_movie( file );
    if( ret < 0 )
        return ret;
    /* Add a new movie fragment if the current one is not present or not written. */
    isom_moof_t *moof = file->fragment->movie;
    if( LSMASH_IS_NON_EXISTING_BOX( moof ) || (moof->manager & LSMASH_WRITTEN_BOX) )
    {
        /* We always hold only one movie fragment except for the initial movie (a pair of moov and mdat). */
        if( LSMASH_IS_EXISTING_BOX( moof )
         && file->moof_list.entry_count != 1 )
            return LSMASH_ERR_NAMELESS;
        moof = isom_add_moof( file );
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mfhd( moof ) ) )
            return LSMASH_ERR_NAMELESS;
        file->fragment->movie = moof;
        moof->mfhd->sequence_number = ++ file->fragment_count;
        if( file->moof_list.entry_count == 1 )
            return 0;
        /* Remove the previous movie fragment. */
        if( file->moof_list.head )
            isom_remove_box_by_itself( file->moof_list.head->data );
    }
    return 0;
}

static inline uint64_t isom_fragment_get_implicit_segment_duration
(
    isom_cache_t *cache
)
{
    return cache->fragment->largest_cts != LSMASH_TIMESTAMP_UNDEFINED
         ? cache->fragment->largest_cts + cache->fragment->last_duration
         : 0;
}

static int isom_set_fragment_overall_duration( lsmash_file_t *file )
{
    assert( file == file->initializer );
    /* Get the longest duration of the tracks. */
    uint64_t longest_duration = 0;
    for( lsmash_entry_t *entry = file->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
         || !trak->cache
         || !trak->cache->fragment
         ||  trak->mdia->mdhd->timescale == 0 )
            return LSMASH_ERR_NAMELESS;
        uint64_t duration;
        uint64_t implicit_segment_duration = isom_fragment_get_implicit_segment_duration( trak->cache );
        if( !trak->edts->elst->list )
            duration = (uint64_t)(((double)implicit_segment_duration / trak->mdia->mdhd->timescale) * file->moov->mvhd->timescale);
        else
        {
            duration = 0;
            for( lsmash_entry_t *elst_entry = trak->edts->elst->list->head; elst_entry; elst_entry = elst_entry->next )
            {
                isom_elst_entry_t *data = (isom_elst_entry_t *)elst_entry->data;
                if( !data )
                    return LSMASH_ERR_NAMELESS;
                if( data->segment_duration == ISOM_EDIT_DURATION_IMPLICIT )
                    duration += (uint64_t)(((double)implicit_segment_duration / trak->mdia->mdhd->timescale) * file->moov->mvhd->timescale);
                else
                    duration += data->segment_duration;
            }
        }
        longest_duration = LSMASH_MAX( duration, longest_duration );
    }
    isom_mehd_t *mehd = file->moov->mvex->mehd;
    mehd->fragment_duration = longest_duration;
    mehd->version           = 1;
    mehd->manager          &= ~(LSMASH_PLACEHOLDER | LSMASH_WRITTEN_BOX);   /* Update per media segment. */
    isom_update_box_size( mehd );
    /* Write Movie Extends Header Box here. */
    lsmash_bs_t *bs = file->bs;
    uint64_t current_pos = bs->offset;
    lsmash_bs_write_seek( bs, mehd->pos, SEEK_SET );
    int ret = isom_write_box( bs, (isom_box_t *)mehd );
    lsmash_bs_write_seek( bs, current_pos, SEEK_SET );
    return ret;
}

static int isom_write_fragment_random_access_info( lsmash_file_t *file )
{
    assert( file == file->initializer );
    if( LSMASH_IS_NON_EXISTING_BOX( file->mfra ) )
        return 0;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvex ) )
        return LSMASH_ERR_NAMELESS;
    /* Reconstruct the Movie Fragment Random Access Box.
     * All 'time' field in the Track Fragment Random Access Boxes shall reflect edit list. */
    uint32_t movie_timescale = lsmash_get_movie_timescale( file->root );
    if( movie_timescale == 0 )
        return LSMASH_ERR_NAMELESS; /* Division by zero will occur. */
    for( lsmash_entry_t *trex_entry = file->moov->mvex->trex_list.head; trex_entry; trex_entry = trex_entry->next )
    {
        isom_trex_t *trex = (isom_trex_t *)trex_entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return LSMASH_ERR_NAMELESS;
        /* Get the edit list of the track associated with the trex->track_ID.
         * If failed or absent, implicit timeline mapping edit is used, and skip this operation for the track. */
        isom_trak_t *trak = isom_get_trak( file, trex->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
            return LSMASH_ERR_NAMELESS;
        if( !trak->edts->elst->list
         || !trak->edts->elst->list->head
         || !trak->edts->elst->list->head->data )
            continue;
        isom_elst_t *elst = trak->edts->elst;
        /* Get the Track Fragment Random Access Boxes of the track associated with the trex->track_ID.
         * If failed or absent, skip reconstructing the Track Fragment Random Access Box of the track. */
        isom_tfra_t *tfra = isom_get_tfra( file->mfra, trex->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( tfra ) )
            continue;
        /* Reconstruct the Track Fragment Random Access Box. */
        lsmash_entry_t    *edit_entry      = elst->list->head;
        isom_elst_entry_t *edit            = edit_entry->data;
        uint64_t           edit_offset     = 0;     /* units in media timescale */
        uint32_t           media_timescale = lsmash_get_media_timescale( file->root, trex->track_ID );
        for( lsmash_entry_t *rap_entry = tfra->list->head; rap_entry; )
        {
            isom_tfra_location_time_entry_t *rap = (isom_tfra_location_time_entry_t *)rap_entry->data;
            if( !rap )
            {
                /* Irregular case. Drop this entry. */
                lsmash_entry_t *next = rap_entry->next;
                lsmash_list_remove_entry_direct( tfra->list, rap_entry );
                rap_entry = next;
                continue;
            }
            uint64_t composition_time          = rap->time;
            uint64_t implicit_segment_duration = isom_fragment_get_implicit_segment_duration( trak->cache );
            /* Skip edits that doesn't need the current sync sample indicated in the Track Fragment Random Access Box. */
            while( edit )
            {
                uint64_t segment_duration = edit->segment_duration == ISOM_EDIT_DURATION_IMPLICIT
                                          ? implicit_segment_duration
                                          : ((edit->segment_duration - 1) / movie_timescale + 1) * media_timescale;
                if( edit->media_time != ISOM_EDIT_MODE_EMPTY
                 && composition_time < edit->media_time + segment_duration )
                    break;  /* This Timeline Mapping Edit might require the current sync sample.
                             * Note: this condition doesn't cover all cases.
                             *       For instance, matching the both following conditions
                             *         1. A sync sample isn't in the presentation.
                             *         2. The other samples, which precede it in the composition timeline, is in the presentation. */
                edit_offset += segment_duration;
                edit_entry   = edit_entry->next;
                if( !edit_entry )
                {
                    /* No more presentation. */
                    edit = NULL;
                    break;
                }
                edit = edit_entry->data;
            }
            if( !edit )
            {
                /* No more presentation.
                 * Drop the rest of sync samples since they are generally absent in the whole presentation.
                 * Though the exceptions are sync samples with earlier composition time, we ignore them. (SAP type 2: TEPT = TDEC = TSAP < TPTF)
                 * To support this exception, we need sorting entries of the list by composition times. */
                while( rap_entry )
                {
                    lsmash_entry_t *next = rap_entry->next;
                    lsmash_list_remove_entry_direct( tfra->list, rap_entry );
                    rap_entry = next;
                }
                break;
            }
            /* If the sync sample isn't in the presentation,
             * we pick the earliest presentation time of the current edit as its presentation time. */
            rap->time = edit_offset;
            if( composition_time >= edit->media_time )
                rap->time += composition_time - edit->media_time;
            rap_entry = rap_entry->next;
        }
        tfra->number_of_entry = tfra->list->entry_count;
    }
    /* Decide the size of the Movie Fragment Random Access Box. */
    if( isom_update_box_size( file->mfra ) == 0 )
        return LSMASH_ERR_NAMELESS;
    /* Write the Movie Fragment Random Access Box. */
    return isom_write_box( file->bs, (isom_box_t *)file->mfra );
}

static int isom_update_indexed_material_offset
(
    lsmash_file_t *file,
    isom_sidx_t   *last_sidx
)
{
    /* Update the size of each Segment Index Box. */
    for( lsmash_entry_t *entry = file->sidx_list.head; entry; entry = entry->next )
    {
        isom_sidx_t *sidx = (isom_sidx_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
            continue;
        if( isom_update_box_size( sidx ) == 0 )
            return LSMASH_ERR_NAMELESS;
    }
    /* first_offset: the sum of the size of subsequent Segment Index Boxes
     * Be careful about changing the size of them. */
    last_sidx->first_offset = 0;
    for( lsmash_entry_t *a_entry = file->sidx_list.head; a_entry && a_entry->data != last_sidx; a_entry = a_entry->next )
    {
        isom_sidx_t *a = (isom_sidx_t *)a_entry->data;
        a->first_offset = 0;
        for( lsmash_entry_t *b_entry = a_entry->next; b_entry; b_entry = b_entry->next )
        {
            isom_sidx_t *b = (isom_sidx_t *)b_entry->data;
            a->first_offset += b->size;
        }
    }
    return 0;
}

static int isom_write_segment_indexes
(
    lsmash_file_t        *file,
    lsmash_adhoc_remux_t *remux
)
{
    /* Update the size of each Segment Index Box and establish the offset from the anchor point to the indexed material. */
    int ret;
    if( (ret = isom_update_indexed_material_offset( file, (isom_sidx_t *)file->sidx_list.tail->data )) < 0 )
        return ret;
    /* Get the total size of all Segment Index Boxes. */
    uint64_t total_sidx_size = 0;
    for( lsmash_entry_t *entry = file->sidx_list.head; entry; entry = entry->next )
    {
        isom_sidx_t *sidx = (isom_sidx_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
            continue;
        total_sidx_size += sidx->size;
    }
    /* The buffer size must be at least total_sidx_size * 2. */
    size_t buffer_size = total_sidx_size * 2;
    if( remux->buffer_size > buffer_size )
        buffer_size = remux->buffer_size;
    /* Split to 2 buffers. */
    uint8_t *buf[2] = { NULL, NULL };
    if( (buf[0] = (uint8_t *)lsmash_malloc( buffer_size )) == NULL )
        return LSMASH_ERR_MEMORY_ALLOC;
    size_t size = buffer_size / 2;
    buf[1] = buf[0] + size;
    /* Seek to the beginning of the first Movie Fragment Box i.e. the first subsegment within this media segment. */
    lsmash_bs_t *bs = file->bs;
    int64_t ret64;
    if( (ret64 = lsmash_bs_write_seek( bs, file->fragment->first_moof_pos, SEEK_SET )) < 0 )
    {
        ret = ret64;
        goto fail;
    }
    size_t read_num = size;
    lsmash_bs_read_data( bs, buf[0], &read_num );
    uint64_t read_pos = bs->offset;
    /* Write the Segment Index Boxes actually here. */
    if( (ret64 = lsmash_bs_write_seek( bs, file->fragment->first_moof_pos, SEEK_SET )) < 0 )
    {
        ret = ret64;
        goto fail;
    }
    for( lsmash_entry_t *entry = file->sidx_list.head; entry; entry = entry->next )
    {
        isom_sidx_t *sidx = (isom_sidx_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
            continue;
        if( (ret = isom_write_box( file->bs, (isom_box_t *)sidx )) < 0 )
            goto fail;
    }
    /* Rearrange subsequent data. */
    uint64_t write_pos = bs->offset;
    uint64_t total     = file->size + total_sidx_size;
    if( (ret = isom_rearrange_data( file, remux, buf, read_num, size, read_pos, write_pos, total )) < 0 )
        goto fail;
    file->size += total_sidx_size;
    lsmash_freep( &buf[0] );
    /* Update 'moof_offset' of each entry within the Track Fragment Random Access Boxes. */
    if( file->mfra )
        for( lsmash_entry_t *entry = file->mfra->tfra_list.head; entry; entry = entry->next )
        {
            isom_tfra_t *tfra = (isom_tfra_t *)entry->data;
            if( LSMASH_IS_NON_EXISTING_BOX( tfra ) )
                continue;
            for( lsmash_entry_t *rap_entry = tfra->list->head; rap_entry; rap_entry = rap_entry->next )
            {
                isom_tfra_location_time_entry_t *rap = (isom_tfra_location_time_entry_t *)rap_entry->data;
                if( !rap )
                    continue;
                rap->moof_offset += total_sidx_size;
            }
        }
    return 0;
fail:
    lsmash_free( buf[0] );
    return ret;
}

int isom_finish_final_fragment_movie
(
    lsmash_file_t        *file,
    lsmash_adhoc_remux_t *remux
)
{
    /* Output the final movie fragment. */
    int ret;
    if( (ret = isom_finish_fragment_movie( file )) < 0 )
        return ret;
    if( file->bs->unseekable )
        return 0;
    /* Write Segment Index Boxes.
     * This occurs only when the initial movie has no samples.
     * We don't consider updating of chunk offsets within initial movie sample table here.
     * This is reasonable since DASH requires no samples in the initial movie.
     * This implementation is not suitable for live-streaming.
     + To support live-streaming, it is good to use daisy-chained index. */
    if( (file->flags & LSMASH_FILE_MODE_MEDIA)
     && (file->flags & LSMASH_FILE_MODE_INDEX)
     && (file->flags & LSMASH_FILE_MODE_SEGMENT) )
    {
        if( !remux )
            return LSMASH_ERR_FUNCTION_PARAM;
        if( (ret = isom_write_segment_indexes( file, remux )) < 0 )
            return ret;
    }
    /* Write the overall random access information at the tail of the movie if this file is self-contained. */
    if( (ret = isom_write_fragment_random_access_info( file->initializer )) < 0 )
        return ret;
    /* Set overall duration of the movie. */
    return isom_set_fragment_overall_duration( file->initializer );
}

#define GET_MOST_USED( box_name, index, flag_name ) \
    if( most_used[index] < stats.flag_name[i] ) \
    { \
        most_used[index] = stats.flag_name[i]; \
        box_name->default_sample_flags.flag_name = i; \
    }

static int isom_create_fragment_overall_default_settings( lsmash_file_t *file )
{
    assert( file == file->initializer );
    if( !isom_add_mvex( file->moov ) )
        return LSMASH_ERR_NAMELESS;
    if( !file->bs->unseekable )
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mehd( file->moov->mvex ) ) )
            return LSMASH_ERR_NAMELESS;
        file->moov->mvex->mehd->manager |= LSMASH_PLACEHOLDER;
    }
    for( lsmash_entry_t *trak_entry = file->moov->trak_list.head; trak_entry; trak_entry = trak_entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)trak_entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
         || !trak->cache )
            return LSMASH_ERR_NAMELESS;
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        if( !stbl->stts->list
         || (stbl->stts->list->tail && !stbl->stts->list->tail->data)
         || (LSMASH_IS_NON_EXISTING_BOX( stbl->stsz ) && LSMASH_IS_NON_EXISTING_BOX( stbl->stz2 ))
         || (LSMASH_IS_EXISTING_BOX( stbl->stsz ) && stbl->stsz->list && stbl->stsz->list->head && !stbl->stsz->list->head->data)
         || (LSMASH_IS_EXISTING_BOX( stbl->stz2 ) && stbl->stz2->list && stbl->stz2->list->head && !stbl->stz2->list->head->data))
            return LSMASH_ERR_NAMELESS;
        isom_trex_t *trex = isom_add_trex( file->moov->mvex );
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return LSMASH_ERR_NAMELESS;
        trex->track_ID = trak->tkhd->track_ID;
        /* Set up defaults. */
        trex->default_sample_description_index = trak->cache->chunk.sample_description_index
                                               ? trak->cache->chunk.sample_description_index
                                               : 1;
        trex->default_sample_duration          = stbl->stts->list->tail
                                               ? ((isom_stts_entry_t *)stbl->stts->list->tail->data)->sample_delta
                                               : 1;
        trex->default_sample_size              = isom_get_first_sample_size( stbl );
        if( stbl->sdtp->list )
        {
            struct sample_flags_stats_t
            {
                uint32_t is_leading           [4];
                uint32_t sample_depends_on    [4];
                uint32_t sample_is_depended_on[4];
                uint32_t sample_has_redundancy[4];
            } stats = { { 0 }, { 0 }, { 0 }, { 0 } };
            for( lsmash_entry_t *sdtp_entry = stbl->sdtp->list->head; sdtp_entry; sdtp_entry = sdtp_entry->next )
            {
                isom_sdtp_entry_t *data = (isom_sdtp_entry_t *)sdtp_entry->data;
                if( !data )
                    return LSMASH_ERR_NAMELESS;
                ++ stats.is_leading           [ data->is_leading            ];
                ++ stats.sample_depends_on    [ data->sample_depends_on     ];
                ++ stats.sample_is_depended_on[ data->sample_is_depended_on ];
                ++ stats.sample_has_redundancy[ data->sample_has_redundancy ];
            }
            uint32_t most_used[4] = { 0, 0, 0, 0 };
            for( int i = 0; i < 4; i++ )
            {
                GET_MOST_USED( trex, 0, is_leading            );
                GET_MOST_USED( trex, 1, sample_depends_on     );
                GET_MOST_USED( trex, 2, sample_is_depended_on );
                GET_MOST_USED( trex, 3, sample_has_redundancy );
            }
        }
        trex->default_sample_flags.sample_is_non_sync_sample = !trak->cache->all_sync;
    }
    return 0;
}

static int isom_prepare_random_access_info( lsmash_file_t *file )
{
    assert( file == file->initializer );
    /* Don't write the random access info at the end of the file if unseekable or not self-contained. */
    if( file->bs->unseekable
     || !(file->flags & LSMASH_FILE_MODE_BOX)
     || !(file->flags & LSMASH_FILE_MODE_INITIALIZATION)
     || !(file->flags & LSMASH_FILE_MODE_MEDIA)
     ||  (file->flags & LSMASH_FILE_MODE_SEGMENT) )
        return 0;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mfra( file ) )
     || LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mfro( file->mfra ) ) )
        return LSMASH_ERR_NAMELESS;
    return 0;
}

static int isom_output_fragment_media_data( lsmash_file_t *file )
{
    isom_fragment_manager_t *frag_manager = file->fragment;
    /* If there is no available Media Data Box to write samples, add and write a new one. */
    if( frag_manager->sample_count )
    {
        if( LSMASH_IS_NON_EXISTING_BOX( file->mdat ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mdat( file ) ) )
            return LSMASH_ERR_NAMELESS;
        file->mdat->manager &= ~(LSMASH_INCOMPLETE_BOX | LSMASH_WRITTEN_BOX);
        int ret = isom_write_box( file->bs, (isom_box_t *)file->mdat );
        if( ret < 0 )
            return ret;
        file->size += file->mdat->size;
        file->mdat->size       = 0;
        file->mdat->media_size = 0;
    }
    lsmash_list_remove_entries( frag_manager->pool );
    frag_manager->pool_size    = 0;
    frag_manager->sample_count = 0;
    return 0;
}

static inline void isom_fragment_reset_sample_counts
(
    isom_cache_t *cache
)
{
    cache->fragment->sample_count        = 0;
    cache->fragment->output_sample_count = 0;
}

static int isom_finish_fragment_initial_movie( lsmash_file_t *file )
{
    assert( file == file->initializer );
    if( !file->moov )
        return LSMASH_ERR_NAMELESS;
    isom_moov_t *moov = file->moov;
    int ret;
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl )
         || !trak->cache )
            return LSMASH_ERR_NAMELESS;
        if( (ret = isom_complement_data_reference( trak->mdia->minf )) < 0 )
            return ret;
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        if( isom_get_sample_count( trak ) )
        {
            /* Compress sample size table. */
            if( stbl->compress_sample_size_table
             && (ret = stbl->compress_sample_size_table( stbl )) < 0 )
                return ret;
            /* Add stss box if any samples aren't sync sample. */
            if( !trak->cache->all_sync
             && LSMASH_IS_NON_EXISTING_BOX( stbl->stss )
             && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_stss( stbl ) ) )
                return LSMASH_ERR_NAMELESS;
            if( (ret = isom_update_tkhd_duration( trak )) < 0 )
                return ret;
        }
        else
            trak->tkhd->duration = 0;
        if( (ret = isom_update_bitrate_description( trak->mdia )) < 0 )
            return ret;
        /* Complete the last sample groups within tracks in the initial movie. */
        if( trak->cache->rap )
        {
            isom_sgpd_t *sgpd = isom_get_sample_group_description( stbl, ISOM_GROUP_TYPE_RAP );
            if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
                return LSMASH_ERR_NAMELESS;
            if( (ret = isom_rap_grouping_established( trak->cache->rap, 1, sgpd, 0 )) < 0 )
                return ret;
            lsmash_freep( &trak->cache->rap );
        }
        if( trak->cache->roll.pool )
        {
            isom_sbgp_t *sbgp = isom_get_roll_recovery_sample_to_group( &stbl->sbgp_list );
            if( LSMASH_IS_NON_EXISTING_BOX( sbgp ) )
                return LSMASH_ERR_NAMELESS;
            if( (ret = isom_all_recovery_completed( sbgp, trak->cache->roll.pool )) < 0 )
                return ret;
        }
    }
    if( file->mp4_version1 == 1 && (ret = isom_setup_iods( moov )) < 0 )
        return ret;
    if( (ret = isom_create_fragment_overall_default_settings( file )) < 0
     || (ret = isom_prepare_random_access_info              ( file )) < 0
     || (ret = isom_establish_movie                         ( file )) < 0 )
        return ret;
    /* stco->co64 conversion, depending on last chunk's offset */
    uint64_t meta_size = LSMASH_IS_EXISTING_BOX( file->meta ) ? file->meta->size : 0;
    if( (ret = isom_check_large_offset_requirement( moov, meta_size )) < 0 )
        return ret;
    /* Now, the amount of the offset is fixed. apply it to stco/co64 */
    uint64_t preceding_size = moov->size + meta_size;
    isom_add_preceding_box_size( moov, preceding_size );
    /* Write File Type Box here if it was not written yet. */
    if( LSMASH_IS_EXISTING_BOX( file->ftyp ) && !(file->ftyp->manager & LSMASH_WRITTEN_BOX) )
    {
        if( (ret = isom_write_box( file->bs, (isom_box_t *)file->ftyp )) < 0 )
            return ret;
        file->size += file->ftyp->size;
    }
    /* Write Movie Box. */
    if( (ret = isom_write_box( file->bs, (isom_box_t *)file->moov )) < 0
     || (ret = isom_write_box( file->bs, (isom_box_t *)file->meta )) < 0 )
        return ret;
    file->size += preceding_size;
    /* Output samples. */
    if( (ret = isom_output_fragment_media_data( file )) < 0 )
        return ret;
    /* Revert the number of samples in tracks to 0. */
    for( lsmash_entry_t *entry = moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        assert( LSMASH_IS_EXISTING_BOX( trak ) );
        if( trak->cache->fragment )
            isom_fragment_reset_sample_counts( trak->cache );
    }
    return 0;
}

/* Return 1 if there is diffrence, otherwise return 0. */
static int isom_compare_sample_flags( isom_sample_flags_t *a, isom_sample_flags_t *b )
{
    return (a->reserved                    != b->reserved)
        || (a->is_leading                  != b->is_leading)
        || (a->sample_depends_on           != b->sample_depends_on)
        || (a->sample_is_depended_on       != b->sample_is_depended_on)
        || (a->sample_has_redundancy       != b->sample_has_redundancy)
        || (a->sample_padding_value        != b->sample_padding_value)
        || (a->sample_is_non_sync_sample   != b->sample_is_non_sync_sample)
        || (a->sample_degradation_priority != b->sample_degradation_priority);
}

static int isom_make_segment_index_entry
(
    lsmash_file_t *file,
    isom_moof_t   *moof
)
{
    /* Make the index of this subsegment. */
    for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
    {
        isom_traf_t       *traf           = (isom_traf_t *)entry->data;
        isom_tfhd_t       *tfhd           = traf->tfhd;
        isom_fragment_t   *track_fragment = traf->cache->fragment;
        isom_subsegment_t *subsegment     = &track_fragment->subsegment;
        isom_sidx_t       *sidx           = isom_get_sidx( file,              tfhd->track_ID );
        isom_trak_t       *trak           = isom_get_trak( file->initializer, tfhd->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd ) )
            return LSMASH_ERR_NAMELESS;
        assert( LSMASH_IS_EXISTING_BOX( traf->tfdt ) );
        if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
        {
            sidx = isom_add_sidx( file );
            if( LSMASH_IS_NON_EXISTING_BOX( sidx ) )
                return LSMASH_ERR_NAMELESS;
            sidx->reference_ID    = tfhd->track_ID;
            sidx->timescale       = trak->mdia->mdhd->timescale;
            sidx->reserved        = 0;
            sidx->reference_count = 0;
            int ret = isom_update_indexed_material_offset( file, sidx );
            if( ret < 0 )
                return ret;
        }
        /* One pair of a Movie Fragment Box with an associated Media Box per subsegment. */
        isom_sidx_referenced_item_t *data = lsmash_malloc( sizeof(isom_sidx_referenced_item_t) );
        if( !data )
            return LSMASH_ERR_NAMELESS;
        if( lsmash_list_add_entry( sidx->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        sidx->reference_count = sidx->list->entry_count;
        data->reference_type = 0;  /* media */
        data->reference_size = file->size - moof->pos;
        /* presentation */
        uint64_t TSAP;
        uint64_t TDEC;
        uint64_t TEPT;
        uint64_t TPTF;
        uint64_t composition_duration = subsegment->largest_cts - subsegment->smallest_cts;
        if( subsegment->smallest_cts != LSMASH_TIMESTAMP_UNDEFINED
         && subsegment->largest_cts  != LSMASH_TIMESTAMP_UNDEFINED )
            composition_duration += track_fragment->last_duration;
        if( trak->edts->elst->list )
        {
            /**-- Explicit edits --**/
            const isom_elst_t       *elst = trak->edts->elst;
            const isom_elst_entry_t *edit = NULL;
            uint32_t movie_timescale = file->initializer->moov->mvhd->timescale;
            uint64_t pts             = subsegment->segment_duration;
            int subsegment_in_presentation   = 0;   /* If set to 1, TEPT is available. */
            int first_rp_in_presentation     = 0;   /* If set to 1, both TSAP and TDEC are available. */
            int first_sample_in_presentation = 0;   /* If set to 1, TPTF is available. */
            TSAP = LSMASH_TIMESTAMP_UNDEFINED;
            TDEC = LSMASH_TIMESTAMP_UNDEFINED;
            TEPT = LSMASH_TIMESTAMP_UNDEFINED;
            TPTF = LSMASH_TIMESTAMP_UNDEFINED;
            /* */
            for( lsmash_entry_t *elst_entry = elst->list->head; elst_entry; elst_entry = elst_entry->next )
            {
                edit = (isom_elst_entry_t *)elst_entry->data;
                if( !edit )
                    continue;
                uint64_t edit_end_pts;
                uint64_t edit_end_cts;
                if( edit->segment_duration == ISOM_EDIT_DURATION_IMPLICIT
                 || (elst->version == 0 && edit->segment_duration == ISOM_EDIT_DURATION_UNKNOWN32)
                 || (elst->version == 1 && edit->segment_duration == ISOM_EDIT_DURATION_UNKNOWN64) )
                {
                    edit_end_cts = UINT64_MAX;
                    edit_end_pts = UINT64_MAX;
                }
                else
                {
                    double segment_duration = edit->segment_duration * ((double)sidx->timescale / movie_timescale);
                    edit_end_cts = edit->media_time + (uint64_t)(segment_duration * ((double)edit->media_rate / (1 << 16)));
                    edit_end_pts = pts + (uint64_t)segment_duration;
                }
                if( edit->media_time == ISOM_EDIT_MODE_EMPTY )
                {
                    pts = edit_end_pts;
                    continue;
                }
                if( subsegment->smallest_cts != LSMASH_TIMESTAMP_UNDEFINED
                 && subsegment->largest_cts  != LSMASH_TIMESTAMP_UNDEFINED
                 && ((subsegment->smallest_cts >= edit->media_time && subsegment->smallest_cts < edit_end_cts)
                  || (subsegment->largest_cts  >= edit->media_time && subsegment->largest_cts  < edit_end_cts)) )
                {
                    /* This subsegment is present in this edit. */
                    double rate = (double)edit->media_rate / (1 << 16);
                    uint64_t start_time = LSMASH_MAX( subsegment->smallest_cts, edit->media_time );
                    if( sidx->reference_count == 1 )
                        sidx->earliest_presentation_time = pts;
                    if( subsegment_in_presentation == 0 )
                    {
                        subsegment_in_presentation = 1;
                        if( subsegment->smallest_cts >= edit->media_time )
                            TEPT = pts + (uint64_t)((subsegment->smallest_cts - start_time) / rate);
                        else
                            TEPT = pts;
                    }
                    if( first_rp_in_presentation == 0
                     && subsegment->first_ed_cts != LSMASH_TIMESTAMP_UNDEFINED
                     && subsegment->first_rp_cts != LSMASH_TIMESTAMP_UNDEFINED
                     && ((subsegment->first_ed_cts >= edit->media_time && subsegment->first_ed_cts < edit_end_cts)
                      || (subsegment->first_rp_cts >= edit->media_time && subsegment->first_rp_cts < edit_end_cts)) )
                    {
                        /* FIXME: to distinguish TSAP and TDEC, need something to indicate incorrectly decodable sample. */
                        first_rp_in_presentation = 1;
                        if( subsegment->first_ed_cts >= edit->media_time && subsegment->first_ed_cts < edit_end_cts )
                            TSAP = pts + (uint64_t)((subsegment->first_ed_cts - start_time) / rate);
                        else
                            TSAP = pts;
                        TDEC = TSAP;
                    }
                    if( first_sample_in_presentation == 0
                     && subsegment->first_sample_cts != LSMASH_TIMESTAMP_UNDEFINED
                     && subsegment->first_sample_cts >= edit->media_time && subsegment->first_sample_cts < edit_end_cts )
                    {
                        first_sample_in_presentation = 1;
                        TPTF = pts + (uint64_t)((subsegment->first_sample_cts - start_time) / rate);
                    }
                    uint64_t subsegment_end_pts = pts + (uint64_t)(composition_duration / rate);
                    pts = LSMASH_MIN( edit_end_pts, subsegment_end_pts );
                    /* Update subsegment_duration. */
                    data->subsegment_duration = pts - subsegment->segment_duration;
                }
                else
                    /* This subsegment is not present in this edit. */
                    pts = edit_end_pts;
            }
        }
        else
        {
            /**-- Implicit edit --**/
            if( sidx->reference_count == 1 )
                sidx->earliest_presentation_time = subsegment->smallest_cts;
            data->subsegment_duration = composition_duration;
            /* FIXME: to distinguish TSAP and TDEC, need something to indicate incorrectly decodable sample. */
            TSAP = subsegment->first_rp_cts;
            TDEC = subsegment->first_rp_cts;
            TEPT = subsegment->smallest_cts;
            TPTF = subsegment->first_sample_cts;
        }
        /* Decide SAP_type. */
        data->starts_with_SAP = (subsegment->first_ra_number == 1);
        data->SAP_type        = 0;
        data->SAP_delta_time  = 0;
        if( TSAP != LSMASH_TIMESTAMP_UNDEFINED
         && TDEC != LSMASH_TIMESTAMP_UNDEFINED
         && TEPT != LSMASH_TIMESTAMP_UNDEFINED )
        {
            if( TPTF != LSMASH_TIMESTAMP_UNDEFINED )
            {
                if( TEPT == TDEC && TDEC == TSAP && TSAP == TPTF )
                    data->SAP_type = 1;
                else if( TEPT == TDEC && TDEC == TSAP && TSAP < TPTF )
                    data->SAP_type = 2;
                else if( TEPT < TDEC && TDEC == TSAP && TSAP <= TPTF )
                    data->SAP_type = 3;
                else if( TEPT <= TPTF && TPTF < TDEC && TDEC == TSAP )
                    data->SAP_type = 4;
            }
            if( data->SAP_type == 0 )
            {
                if( TEPT == TDEC && TDEC < TSAP )
                    data->SAP_type = 5;
                else if( TEPT < TDEC && TDEC < TSAP )
                    data->SAP_type = 6;
            }
            if( data->SAP_type != 0 )
                data->SAP_delta_time = TSAP - TEPT;
        }
        /* Prepare for the next subsegment. */
        subsegment->segment_duration += data->subsegment_duration;
        subsegment->largest_cts       = LSMASH_TIMESTAMP_UNDEFINED;
        subsegment->smallest_cts      = LSMASH_TIMESTAMP_UNDEFINED;
        subsegment->first_sample_cts  = LSMASH_TIMESTAMP_UNDEFINED;
        subsegment->first_ed_cts      = LSMASH_TIMESTAMP_UNDEFINED;
        subsegment->first_rp_cts      = LSMASH_TIMESTAMP_UNDEFINED;
        subsegment->first_rp_number   = 0;
        subsegment->first_ra_number   = 0;
        subsegment->first_ra_flags    = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_NONE;
        subsegment->decodable         = 0;
    }
    return 0;
}

static int isom_finish_fragment_movie
(
    lsmash_file_t *file
)
{
    if( !file->fragment
     || !file->fragment->pool )
        return LSMASH_ERR_NAMELESS;
    isom_moof_t *moof = file->fragment->movie;
    if( LSMASH_IS_NON_EXISTING_BOX( moof ) )
    {
        if( file == file->initializer )
            return isom_finish_fragment_initial_movie( file );
        else
            return 0;   /* No movie fragment to be finished. */
    }
    /* Don't write the current movie fragment if containing no track fragments.
     * This is a requirement of DASH Media Segment. */
    if( !moof->traf_list.head
     || !moof->traf_list.head->data )
        return 0;
    /* Calculate appropriate default_sample_flags of each Track Fragment Header Box.
     * And check whether that default_sample_flags is useful or not. */
    for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
    {
        isom_traf_t *traf = (isom_traf_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( traf )
         || LSMASH_IS_NON_EXISTING_BOX( traf->tfhd )
         || LSMASH_IS_NON_EXISTING_BOX( traf->file->initializer->moov->mvex ) )
            return LSMASH_ERR_NAMELESS;
        isom_tfhd_t *tfhd = traf->tfhd;
        isom_trex_t *trex = isom_get_trex( file->initializer->moov->mvex, tfhd->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return LSMASH_ERR_NAMELESS;
        struct sample_flags_stats_t
        {
            uint32_t is_leading               [4];
            uint32_t sample_depends_on        [4];
            uint32_t sample_is_depended_on    [4];
            uint32_t sample_has_redundancy    [4];
            uint32_t sample_is_non_sync_sample[2];
        } stats = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };
        for( lsmash_entry_t *trun_entry = traf->trun_list.head; trun_entry; trun_entry = trun_entry->next )
        {
            isom_trun_t *trun = (isom_trun_t *)trun_entry->data;
            if( LSMASH_IS_NON_EXISTING_BOX( trun ) || trun->sample_count == 0 )
                return LSMASH_ERR_NAMELESS;
            isom_sample_flags_t *sample_flags;
            if( trun->flags & ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT )
            {
                if( !trun->optional )
                    return LSMASH_ERR_NAMELESS;
                for( lsmash_entry_t *optional_entry = trun->optional->head; optional_entry; optional_entry = optional_entry->next )
                {
                    isom_trun_optional_row_t *row = (isom_trun_optional_row_t *)optional_entry->data;
                    if( !row )
                        return LSMASH_ERR_NAMELESS;
                    sample_flags = &row->sample_flags;
                    ++ stats.is_leading               [ sample_flags->is_leading                ];
                    ++ stats.sample_depends_on        [ sample_flags->sample_depends_on         ];
                    ++ stats.sample_is_depended_on    [ sample_flags->sample_is_depended_on     ];
                    ++ stats.sample_has_redundancy    [ sample_flags->sample_has_redundancy     ];
                    ++ stats.sample_is_non_sync_sample[ sample_flags->sample_is_non_sync_sample ];
                }
            }
            else
            {
                sample_flags = &tfhd->default_sample_flags;
                stats.is_leading               [ sample_flags->is_leading                ] += trun->sample_count;
                stats.sample_depends_on        [ sample_flags->sample_depends_on         ] += trun->sample_count;
                stats.sample_is_depended_on    [ sample_flags->sample_is_depended_on     ] += trun->sample_count;
                stats.sample_has_redundancy    [ sample_flags->sample_has_redundancy     ] += trun->sample_count;
                stats.sample_is_non_sync_sample[ sample_flags->sample_is_non_sync_sample ] += trun->sample_count;
            }
        }
        uint32_t most_used[5] = { 0, 0, 0, 0, 0 };
        for( int i = 0; i < 4; i++ )
        {
            GET_MOST_USED( tfhd, 0, is_leading            );
            GET_MOST_USED( tfhd, 1, sample_depends_on     );
            GET_MOST_USED( tfhd, 2, sample_is_depended_on );
            GET_MOST_USED( tfhd, 3, sample_has_redundancy );
            if( i < 2 )
                GET_MOST_USED( tfhd, 4, sample_is_non_sync_sample );
        }
        int useful_default_sample_duration = 0;
        int useful_default_sample_size = 0;
        for( lsmash_entry_t *trun_entry = traf->trun_list.head; trun_entry; trun_entry = trun_entry->next )
        {
            isom_trun_t *trun = (isom_trun_t *)trun_entry->data;
            assert( LSMASH_IS_EXISTING_BOX( trun ) );
            if( !(trun->flags & ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT) )
                useful_default_sample_duration = 1;
            if( !(trun->flags & ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT) )
                useful_default_sample_size = 1;
            int useful_first_sample_flags   = 1;
            int useful_default_sample_flags = 1;
            if( trun->sample_count == 1 )
            {
                /* It is enough to check only if first_sample_flags equals default_sample_flags or not.
                 * If it is equal, just use default_sample_flags.
                 * If not, just use first_sample_flags of this run. */
                if( !isom_compare_sample_flags( &trun->first_sample_flags, &tfhd->default_sample_flags ) )
                    useful_first_sample_flags = 0;
            }
            else if( trun->optional
                  && trun->optional->head )
            {
                lsmash_entry_t           *optional_entry = trun->optional->head->next;
                isom_trun_optional_row_t *row            = (isom_trun_optional_row_t *)optional_entry->data;
                isom_sample_flags_t representative_sample_flags = row->sample_flags;
                if( isom_compare_sample_flags( &tfhd->default_sample_flags, &representative_sample_flags ) )
                    useful_default_sample_flags = 0;
                if( !isom_compare_sample_flags( &trun->first_sample_flags, &representative_sample_flags ) )
                    useful_first_sample_flags = 0;
                if( useful_default_sample_flags )
                    for( optional_entry = optional_entry->next; optional_entry; optional_entry = optional_entry->next )
                    {
                        row = (isom_trun_optional_row_t *)optional_entry->data;
                        if( isom_compare_sample_flags( &representative_sample_flags, &row->sample_flags ) )
                        {
                            useful_default_sample_flags = 0;
                            break;
                        }
                    }
            }
            if( useful_default_sample_flags )
            {
                tfhd->flags |=  ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT;
                trun->flags &= ~ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT;
            }
            else
            {
                useful_first_sample_flags = 0;
                trun->flags |= ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT;
            }
            if( useful_first_sample_flags )
                trun->flags |= ISOM_TR_FLAGS_FIRST_SAMPLE_FLAGS_PRESENT;
        }
        if( useful_default_sample_duration && tfhd->default_sample_duration != trex->default_sample_duration )
            tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT;
        else
            tfhd->default_sample_duration = trex->default_sample_duration;      /* This might be redundant, but is to be more natural. */
        if( useful_default_sample_size && tfhd->default_sample_size != trex->default_sample_size )
            tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_SIZE_PRESENT;
        else
            tfhd->default_sample_size = trex->default_sample_size;              /* This might be redundant, but is to be more natural. */
        if( !(tfhd->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT) )
            tfhd->default_sample_flags = trex->default_sample_flags;            /* This might be redundant, but is to be more natural. */
        else if( !isom_compare_sample_flags( &tfhd->default_sample_flags, &trex->default_sample_flags ) )
            tfhd->flags &= ~ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT;
    }
    /* Complete the last sample groups in the previous track fragments. */
    int ret;
    for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
    {
        isom_traf_t *traf = (isom_traf_t *)entry->data;
        assert( LSMASH_IS_EXISTING_BOX( traf ) );
        if( traf->cache->rap )
        {
            isom_sgpd_t *sgpd = isom_get_fragment_sample_group_description( traf, ISOM_GROUP_TYPE_RAP );
            if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
                return LSMASH_ERR_NAMELESS;
            if( (ret = isom_rap_grouping_established( traf->cache->rap, 1, sgpd, 1 )) < 0 )
                return ret;
            lsmash_freep( &traf->cache->rap );
        }
        if( traf->cache->roll.pool )
        {
            isom_sbgp_t *sbgp = isom_get_roll_recovery_sample_to_group( &traf->sbgp_list );
            if( LSMASH_IS_NON_EXISTING_BOX( sbgp ) )
                return LSMASH_ERR_NAMELESS;
            if( (ret = isom_all_recovery_completed( sbgp, traf->cache->roll.pool )) < 0 )
                return ret;
        }
    }
    /* Establish Movie Fragment Box.
     * We write exactly one Media Data Box starting immediately after the corresponding Movie Fragment Box. */
    if( file->allow_moof_base )
    {
        /* In this branch, we use default-base-is-moof flag, which indicates implicit base_data_offsets originate in the
         * first byte of each enclosing Movie Fragment Box.
         * We use the sum of the size of the Movie Fragment Box and the offset from the size field of the Media Data Box to
         * the type field of it as the data_offset of the first track run like the following.
         *
         *  _____________ _ offset := 0
         * |   |         |
         * | m | s i z e |
         * |   |_________|
         * | o |         |
         * |   | t y p e |
         * | o |_________|
         * |   |         |
         * | f | d a t a |
         * |___|_________|_ offset := the size of the Movie Fragment Box
         * |   |         |
         * | m | s i z e |
         * |   |_________|
         * | d |         |
         * |   | t y p e |
         * | a |_________|_ offset := the data_offset of the first track run
         * |   |         |
         * | t | d a t a |
         * |___|_________|_ offset := the size of a subsegment containing exactly one movie fragment
         *
         * For a pair of one Movie Fragment Box and one Media Data Box, placed in this order, implicit base_data_offsets
         * indicated by the absence of both base-data-offset-present and default-base-is-moof are somewhat complicated
         * since the implicit base_data_offset of the current track fragment is defined by the end of the data of the
         * previous track fragment and the data_offset of the track runs could be negative value because of interleaving
         * track runs or something other reasons.
         * In contrast, implicit base_data_offsets indicated by default-base-is-moof are simple since the base_data_offset
         * of each track fragment is always constant for that pair and has no dependency on other track fragments.
         */
        for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
        {
            isom_traf_t *traf = (isom_traf_t *)entry->data;
            assert( LSMASH_IS_EXISTING_BOX( traf ) );
            traf->tfhd->flags           |= ISOM_TF_FLAGS_DEFAULT_BASE_IS_MOOF;
            traf->tfhd->base_data_offset = file->size;  /* not written actually though */
            for( lsmash_entry_t *trun_entry = traf->trun_list.head; trun_entry; trun_entry = trun_entry->next )
            {
                /* Here, data_offset is always greater than zero. */
                isom_trun_t *trun = trun_entry->data;
                assert( LSMASH_IS_EXISTING_BOX( trun ) );
                trun->flags |= ISOM_TR_FLAGS_DATA_OFFSET_PRESENT;
            }
        }
        /* Consider the update of tr_flags here. */
        if( isom_update_box_size( moof ) == 0 )
            return LSMASH_ERR_NAMELESS;
        /* Now, we can calculate offsets in the current movie fragment, so do it. */
        for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
        {
            isom_traf_t *traf = (isom_traf_t *)entry->data;
            assert( LSMASH_IS_EXISTING_BOX( traf ) );
            for( lsmash_entry_t *trun_entry = traf->trun_list.head; trun_entry; trun_entry = trun_entry->next )
            {
                isom_trun_t *trun = trun_entry->data;
                assert( LSMASH_IS_EXISTING_BOX( trun ) );
                trun->data_offset += moof->size + ISOM_BASEBOX_COMMON_SIZE;
            }
        }
    }
    else
    {
        /* In this branch, we use explicit base_data_offset. */
        for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
        {
            isom_traf_t *traf = (isom_traf_t *)entry->data;
            assert( LSMASH_IS_EXISTING_BOX( traf ) );
            traf->tfhd->flags |= ISOM_TF_FLAGS_BASE_DATA_OFFSET_PRESENT;
        }
        /* Consider the update of tf_flags here. */
        if( isom_update_box_size( moof ) == 0 )
            return LSMASH_ERR_NAMELESS;
        /* Now, we can calculate offsets in the current movie fragment, so do it. */
        for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
        {
            isom_traf_t *traf = (isom_traf_t *)entry->data;
            assert( LSMASH_IS_EXISTING_BOX( traf ) );
            traf->tfhd->base_data_offset = file->size + moof->size + ISOM_BASEBOX_COMMON_SIZE;
        }
    }
    /* Write Movie Fragment Box and its children. */
    moof->pos = file->size;
    if( (ret = isom_write_box( file->bs, (isom_box_t *)moof )) < 0 )
        return ret;
    if( file->fragment->first_moof_pos == FIRST_MOOF_POS_UNDETERMINED )
        file->fragment->first_moof_pos = moof->pos;
    file->size += moof->size;
    /* Output samples. */
    if( (ret = isom_output_fragment_media_data( file )) < 0 )
        return ret;
    /* Revert the number of samples in track fragments to 0. */
    for( lsmash_entry_t *entry = moof->traf_list.head; entry; entry = entry->next )
    {
        isom_traf_t *traf = (isom_traf_t *)entry->data;
        assert( LSMASH_IS_EXISTING_BOX( traf ) );
        if( traf->cache->fragment )
            isom_fragment_reset_sample_counts( traf->cache );
    }
    if( !(file->flags & LSMASH_FILE_MODE_INDEX) || file->max_isom_version < 6 )
        return 0;
    return isom_make_segment_index_entry( file, moof );
}

#undef GET_MOST_USED

static isom_trun_optional_row_t *isom_request_trun_optional_row( isom_trun_t *trun, isom_tfhd_t *tfhd, uint32_t sample_number )
{
    isom_trun_optional_row_t *row = NULL;
    if( !trun->optional )
    {
        trun->optional = lsmash_list_create_simple();
        if( !trun->optional )
            return NULL;
    }
    if( trun->optional->entry_count < sample_number )
    {
        while( trun->optional->entry_count < sample_number )
        {
            row = lsmash_malloc( sizeof(isom_trun_optional_row_t) );
            if( !row )
                return NULL;
            /* Copy from default. */
            row->sample_duration                = tfhd->default_sample_duration;
            row->sample_size                    = tfhd->default_sample_size;
            row->sample_flags                   = tfhd->default_sample_flags;
            row->sample_composition_time_offset = 0;
            if( lsmash_list_add_entry( trun->optional, row ) < 0 )
            {
                lsmash_free( row );
                return NULL;
            }
        }
        return row;
    }
    uint32_t i = 0;
    for( lsmash_entry_t *entry = trun->optional->head; entry; entry = entry->next )
    {
        row = (isom_trun_optional_row_t *)entry->data;
        if( !row )
            return NULL;
        if( ++i == sample_number )
            return row;
    }
    return NULL;
}

int lsmash_create_fragment_empty_duration
(
    lsmash_root_t *root,
    uint32_t       track_ID,
    uint32_t       duration
)
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file;
    if( !file->fragment
     || !file->fragment->movie
     || LSMASH_IS_NON_EXISTING_BOX( file->initializer->moov ) )
        return LSMASH_ERR_NAMELESS;
    isom_trak_t *trak = isom_get_trak( file->initializer, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tkhd ) )
        return LSMASH_ERR_NAMELESS;
    isom_trex_t *trex = isom_get_trex( file->initializer->moov->mvex, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
        return LSMASH_ERR_NAMELESS;
    isom_moof_t *moof = file->fragment->movie;
    isom_traf_t *traf = isom_get_traf( moof, track_ID );
    if( LSMASH_IS_EXISTING_BOX( traf ) )
        return LSMASH_ERR_NAMELESS;
    traf = isom_add_traf( moof );
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tfhd( traf ) ) )
        return LSMASH_ERR_NAMELESS;
    isom_tfhd_t *tfhd = traf->tfhd;
    tfhd->flags                   = ISOM_TF_FLAGS_DURATION_IS_EMPTY;    /* no samples for this track fragment yet */
    tfhd->track_ID                = trak->tkhd->track_ID;
    tfhd->default_sample_duration = duration;
    if( duration != trex->default_sample_duration )
        tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT;
    traf->cache = trak->cache;
    traf->cache->fragment->traf_number    = moof->traf_list.entry_count;
    traf->cache->fragment->last_duration += duration;       /* The duration of the last sample includes this empty-duration. */
    return 0;
}

int isom_set_fragment_last_duration
(
    isom_traf_t *traf,
    uint32_t     last_duration
)
{
    isom_tfhd_t *tfhd = traf->tfhd;
    if( !traf->trun_list.tail
     || !traf->trun_list.tail->data )
    {
        /* There are no track runs in this track fragment, so it is a empty-duration. */
        isom_trex_t *trex = isom_get_trex( traf->file->initializer->moov->mvex, tfhd->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return LSMASH_ERR_NAMELESS;
        tfhd->flags |= ISOM_TF_FLAGS_DURATION_IS_EMPTY;
        if( last_duration != trex->default_sample_duration )
            tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT;
        tfhd->default_sample_duration        = last_duration;
        traf->cache->fragment->last_duration = last_duration;
        return 0;
    }
    /* Update the last sample_duration if needed. */
    isom_trun_t *trun = (isom_trun_t *)traf->trun_list.tail->data;
    if( trun->sample_count          == 1
     && traf->trun_list.entry_count == 1 )
    {
        isom_trex_t *trex = isom_get_trex( traf->file->initializer->moov->mvex, tfhd->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
            return LSMASH_ERR_NAMELESS;
        if( last_duration != trex->default_sample_duration )
            tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT;
        tfhd->default_sample_duration = last_duration;
    }
    else if( last_duration != tfhd->default_sample_duration )
        trun->flags |= ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT;
    if( trun->flags )
    {
        isom_trun_optional_row_t *row = isom_request_trun_optional_row( trun, tfhd, trun->sample_count );
        if( !row )
            return LSMASH_ERR_NAMELESS;
        row->sample_duration = last_duration;
    }
    traf->cache->fragment->last_duration = last_duration;
    return 0;
}

int isom_append_fragment_track_run
(
    lsmash_file_t *file,
    isom_chunk_t  *chunk
)
{
    if( !chunk->pool || chunk->pool->size == 0 )
        return 0;
    isom_fragment_manager_t *frag_manager = file->fragment;
    /* Move data in the pool of the current track fragment to the pool of the current movie fragment.
     * Empty the pool of current track. We don't delete data of samples here. */
    if( lsmash_list_add_entry( frag_manager->pool, chunk->pool ) < 0 )
        return LSMASH_ERR_MEMORY_ALLOC;
    frag_manager->sample_count += chunk->pool->sample_count;
    frag_manager->pool_size    += chunk->pool->size;
    chunk->pool = isom_create_sample_pool( chunk->pool->size );
    return chunk->pool ? 0 : LSMASH_ERR_MEMORY_ALLOC;
}

static int isom_output_fragment_cache( isom_traf_t *traf )
{
    isom_cache_t *cache = traf->cache;
    int ret = isom_append_fragment_track_run( traf->file, &cache->chunk );
    if( ret < 0 )
        return ret;
    for( lsmash_entry_t *entry = traf->sgpd_list.head; entry; entry = entry->next )
    {
        isom_sgpd_t *sgpd = (isom_sgpd_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( sgpd ) )
            return LSMASH_ERR_NAMELESS;
        switch( sgpd->grouping_type )
        {
            case ISOM_GROUP_TYPE_RAP :
            {
                isom_rap_group_t *group = cache->rap;
                if( !group )
                {
                    if( traf->file->fragment )
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
                    if( traf->file->fragment )
                        continue;
                    else
                        return LSMASH_ERR_NAMELESS;
                }
                isom_sbgp_t *sbgp = isom_get_roll_recovery_sample_to_group( &traf->sbgp_list );
                if( LSMASH_IS_NON_EXISTING_BOX( sbgp ) )
                    return LSMASH_ERR_NAMELESS;
                if( (ret = isom_all_recovery_completed( sbgp, cache->roll.pool )) < 0 )
                    return ret;
                break;
            default :
                break;
        }
    }
    return 0;
}

int isom_flush_fragment_pooled_samples
(
    lsmash_file_t *file,
    uint32_t       track_ID,
    uint32_t       last_sample_duration
)
{
    isom_traf_t *traf = isom_get_traf( file->fragment->movie, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( traf ) )
        /* No samples. We don't return as an error here since user might call the flushing function even if the
         * current movie fragment has no track fragment with this track_ID. */
        return 0;
    if( !traf->cache
     || !traf->cache->fragment )
        return LSMASH_ERR_NAMELESS;
    if( traf->trun_list.entry_count
     && traf->trun_list.tail
     && traf->trun_list.tail->data )
    {
        /* Media Data Box preceded by Movie Fragment Box could change base_data_offsets in each track fragments later.
         * We can't consider this here because the length of Movie Fragment Box is unknown at this step yet. */
        isom_trun_t *trun = (isom_trun_t *)traf->trun_list.tail->data;
        if( file->fragment->pool_size )
            trun->flags |= ISOM_TR_FLAGS_DATA_OFFSET_PRESENT;
        trun->data_offset = file->fragment->pool_size;
    }
    int ret = isom_output_fragment_cache( traf );
    if( ret < 0 )
        return ret;
    return isom_set_fragment_last_duration( traf, last_sample_duration );
}

/* This function doesn't update sample_duration of the last sample in the previous movie fragment.
 * Instead of this, isom_finish_movie_fragment undertakes this task. */
static int isom_update_fragment_previous_sample_duration( isom_traf_t *traf, isom_trex_t *trex, uint32_t duration )
{
    isom_tfhd_t *tfhd = traf->tfhd;
    isom_trun_t *trun = (isom_trun_t *)traf->trun_list.tail->data;
    int previous_run_has_previous_sample = 0;
    if( trun->sample_count == 1 )
    {
        if( traf->trun_list.entry_count == 1 )
            return 0;       /* The previous track run belongs to the previous movie fragment if it exists. */
        if( !traf->trun_list.tail->prev
         || !traf->trun_list.tail->prev->data )
            return LSMASH_ERR_NAMELESS;
        /* OK. The previous sample exists in the previous track run in the same track fragment. */
        trun = (isom_trun_t *)traf->trun_list.tail->prev->data;
        previous_run_has_previous_sample = 1;
    }
    /* Update default_sample_duration of the Track Fragment Header Box
     * if this duration is what the first sample in the current track fragment owns. */
    if( (trun->sample_count == 2 && traf->trun_list.entry_count == 1)
     || (trun->sample_count == 1 && traf->trun_list.entry_count == 2) )
    {
        if( duration != trex->default_sample_duration )
            tfhd->flags |= ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT;
        tfhd->default_sample_duration = duration;
    }
    /* Update the previous sample_duration if needed. */
    if( duration != tfhd->default_sample_duration )
        trun->flags |= ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT;
    if( trun->flags )
    {
        uint32_t sample_number = trun->sample_count - !previous_run_has_previous_sample;
        isom_trun_optional_row_t *row = isom_request_trun_optional_row( trun, tfhd, sample_number );
        if( !row )
            return LSMASH_ERR_NAMELESS;
        row->sample_duration = duration;
    }
    return 0;
}

static isom_sample_flags_t isom_generate_fragment_sample_flags( lsmash_sample_t *sample )
{
    isom_sample_flags_t flags;
    flags.reserved                    = 0;
    flags.is_leading                  = sample->prop.leading     & 0x3;
    flags.sample_depends_on           = sample->prop.independent & 0x3;
    flags.sample_is_depended_on       = sample->prop.disposable  & 0x3;
    flags.sample_has_redundancy       = sample->prop.redundant   & 0x3;
    flags.sample_padding_value        = 0;
    flags.sample_is_non_sync_sample   = !(sample->prop.ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC);
    flags.sample_degradation_priority = 0;
    return flags;
}

/* Set up the base media decode time of this track fragment.
 * This feature is available under ISO Base Media version 6 or later.
 * For DASH Media Segment, each Track Fragment Box shall contain a Track Fragment Base Media Decode Time Box. */
static int isom_fragment_set_base_media_decode_time( lsmash_file_t *file, isom_traf_t *traf, uint64_t dts )
{
    if( file->max_isom_version >= 6 || file->media_segment )
    {
        assert( LSMASH_IS_NON_EXISTING_BOX( traf->tfdt ) );
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tfdt( traf ) ) )
            return LSMASH_ERR_NAMELESS;
        if( dts > UINT32_MAX )
            traf->tfdt->version = 1;
        traf->tfdt->baseMediaDecodeTime = dts;
    }
    return 0;
}

/* Update the cache of SAP related information. */
static void isom_fragment_update_cache_for_sap
(
    isom_cache_t    *cache,
    lsmash_sample_t *sample
)
{
    isom_subsegment_t *subsegment = &cache->fragment->subsegment;
    int non_output_sample = (sample->cts == LSMASH_TIMESTAMP_UNDEFINED);
    if( !non_output_sample )
    {
        if( cache->fragment->sample_count == 1 )
        {
            assert( subsegment->first_sample_cts == LSMASH_TIMESTAMP_UNDEFINED );
            subsegment->first_sample_cts = sample->cts;
        }
        if( cache->fragment->output_sample_count > 1 )
        {
            assert( subsegment->largest_cts  != LSMASH_TIMESTAMP_UNDEFINED
                 && subsegment->smallest_cts != LSMASH_TIMESTAMP_UNDEFINED );
            subsegment->largest_cts  = LSMASH_MAX( sample->cts, subsegment->largest_cts );
            subsegment->smallest_cts = LSMASH_MIN( sample->cts, subsegment->smallest_cts );
        }
        else
        {
            assert( subsegment->largest_cts  == LSMASH_TIMESTAMP_UNDEFINED
                 && subsegment->smallest_cts == LSMASH_TIMESTAMP_UNDEFINED );
            if( cache->fragment->output_sample_count == 1 )
            {

                subsegment->largest_cts  = sample->cts;
                subsegment->smallest_cts = sample->cts;
            }
        }
    }
    if( subsegment->first_ra_flags == ISOM_SAMPLE_RANDOM_ACCESS_FLAG_NONE
     && sample->prop.ra_flags      != ISOM_SAMPLE_RANDOM_ACCESS_FLAG_NONE )
    {
        assert( subsegment->first_ra_number == 0 );
        subsegment->first_ra_flags  = sample->prop.ra_flags;
        subsegment->first_ra_number = cache->fragment->sample_count;
        if( sample->prop.ra_flags & (ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC | ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP) )
            subsegment->is_first_recovery_point = 1;
    }
    if( subsegment->is_first_recovery_point )
    {
        assert( subsegment->first_rp_number == 0 );
        if( !non_output_sample )
        {
            assert( subsegment->first_rp_cts == LSMASH_TIMESTAMP_UNDEFINED
                 && subsegment->first_ed_cts == LSMASH_TIMESTAMP_UNDEFINED );
            subsegment->first_rp_cts = sample->cts;
            subsegment->first_ed_cts = sample->cts;
        }
        subsegment->first_rp_number         = subsegment->first_ra_number;
        subsegment->decodable               = 1;
        subsegment->is_first_recovery_point = 0;
    }
    else if( subsegment->decodable )
    {
        if( (subsegment->first_ra_flags & (ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC | ISOM_SAMPLE_RANDOM_ACCESS_FLAG_RAP))
          ? (sample->prop.leading == ISOM_SAMPLE_IS_DECODABLE_LEADING)
          : (subsegment->first_ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_POST_ROLL_START) )
        {
            if( !non_output_sample )
                subsegment->first_ed_cts = LSMASH_MIN( sample->cts, subsegment->first_ed_cts );
        }
        else
            subsegment->decodable = 0;
    }
}

/* Update the cache of fragment related information.
 * The cached sample_count is incremented here, so be careful to treat it. */
static void isom_fragment_update_cache
(
    isom_cache_t    *cache,
    lsmash_sample_t *sample,
    lsmash_file_t   *file
)
{
    cache->fragment->has_samples          = 1;
    cache->fragment->sample_count        += 1;
    cache->fragment->output_sample_count += sample->cts == LSMASH_TIMESTAMP_UNDEFINED ? 0 : 1;
    assert( cache->fragment->sample_count >= cache->fragment->output_sample_count );
    if( (file->flags & LSMASH_FILE_MODE_INDEX) && (file->max_isom_version >= 6) )
        isom_fragment_update_cache_for_sap( cache, sample );
}

static int isom_fragment_update_sample_tables( isom_traf_t *traf, lsmash_sample_t *sample )
{
    isom_tfhd_t *tfhd = traf->tfhd;
    isom_trex_t *trex = isom_get_trex( traf->file->initializer->moov->mvex, tfhd->track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trex ) )
        return LSMASH_ERR_NAMELESS;
    lsmash_file_t *file    = traf->file;
    isom_cache_t  *cache   = traf->cache;
    isom_chunk_t  *current = &cache->chunk;
    if( !current->pool )
    {
        /* Very initial settings, just once per track */
        current->pool = isom_create_sample_pool( 0 );
        if( !current->pool )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    /* Create a new track run if the duration exceeds max_chunk_duration.
     * Old one will be appended to the pool of this movie fragment. */
    uint32_t media_timescale = lsmash_get_media_timescale( file->root, tfhd->track_ID );
    if( media_timescale == 0 )
        return LSMASH_ERR_NAMELESS;
    int delimit = (file->max_chunk_duration < ((double)(sample->dts - current->first_dts) / media_timescale))
               || (file->max_chunk_size < (current->pool->size + sample->length));
    isom_trun_t *trun;
    if( traf->trun_list.entry_count == 0 || delimit )
    {
        if( delimit
         && traf->trun_list.entry_count
         && traf->trun_list.tail
         && LSMASH_IS_EXISTING_BOX( (isom_trun_t *)traf->trun_list.tail->data ) )
        {
            /* Media Data Box preceded by Movie Fragment Box could change base data offsets in each track fragments later.
             * We can't consider this here because the length of Movie Fragment Box is unknown at this step yet. */
            trun = (isom_trun_t *)traf->trun_list.tail->data;
            if( file->fragment->pool_size )
                trun->flags |= ISOM_TR_FLAGS_DATA_OFFSET_PRESENT;
            trun->data_offset = file->fragment->pool_size;
        }
        trun = isom_add_trun( traf );
        if( LSMASH_IS_NON_EXISTING_BOX( trun ) )
            return LSMASH_ERR_NAMELESS;
    }
    else
    {
        if( !traf->trun_list.tail
         || LSMASH_IS_NON_EXISTING_BOX( (isom_trun_t *)traf->trun_list.tail->data ) )
            return LSMASH_ERR_NAMELESS;
        trun = (isom_trun_t *)traf->trun_list.tail->data;
    }
    isom_sample_flags_t sample_flags = isom_generate_fragment_sample_flags( sample );
    int non_output_sample = (sample->cts == LSMASH_TIMESTAMP_UNDEFINED);
    if( ++trun->sample_count == 1 )
    {
        if( traf->trun_list.entry_count == 1 )
        {
            tfhd->sample_description_index = current->sample_description_index
                                           = sample->index;
            tfhd->default_sample_size      = sample->length;
            tfhd->default_sample_flags     = sample_flags;      /* Note: we decide an appropriate default value at the end of this movie fragment. */
            tfhd->flags &= ~ISOM_TF_FLAGS_DURATION_IS_EMPTY;    /* This track fragment isn't empty-duration-fragment any more. */
            if( sample->index != trex->default_sample_description_index )
                tfhd->flags |= ISOM_TF_FLAGS_SAMPLE_DESCRIPTION_INDEX_PRESENT;
            /* Set up random access information if this sample is a sync sample.
             * We inform only the first sample in each movie fragment. */
            if( !non_output_sample
             && LSMASH_IS_EXISTING_BOX( file->mfra )
             && (sample->prop.ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC) )
            {
                isom_tfra_t *tfra = isom_get_tfra( file->mfra, tfhd->track_ID );
                if( LSMASH_IS_NON_EXISTING_BOX( tfra ) )
                {
                    tfra = isom_add_tfra( file->mfra );
                    if( LSMASH_IS_NON_EXISTING_BOX( tfra ) )
                        return LSMASH_ERR_NAMELESS;
                    tfra->track_ID = tfhd->track_ID;
                }
                if( !tfra->list )
                {
                    tfra->list = lsmash_list_create_simple();
                    if( !tfra->list )
                        return LSMASH_ERR_MEMORY_ALLOC;
                }
                isom_tfra_location_time_entry_t *rap = lsmash_malloc( sizeof(isom_tfra_location_time_entry_t) );
                if( !rap )
                    return LSMASH_ERR_MEMORY_ALLOC;
                rap->time          = sample->cts;   /* Set composition timestamp temporarily.
                                                     * At the end of the whole movie, this will be reset as presentation time. */
                rap->moof_offset   = file->size;    /* We place Movie Fragment Box in the head of each movie fragment. */
                rap->traf_number   = cache->fragment->traf_number;
                rap->trun_number   = traf->trun_list.entry_count;
                rap->sample_number = trun->sample_count;
                if( lsmash_list_add_entry( tfra->list, rap ) < 0 )
                {
                    lsmash_free( rap );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                tfra->number_of_entry = tfra->list->entry_count;
                int length;
                for( length = 1; rap->traf_number >> (length * 8); length++ );
                tfra->length_size_of_traf_num = LSMASH_MAX( length - 1, tfra->length_size_of_traf_num );
                for( length = 1; rap->traf_number >> (length * 8); length++ );
                tfra->length_size_of_trun_num = LSMASH_MAX( length - 1, tfra->length_size_of_trun_num );
                for( length = 1; rap->sample_number >> (length * 8); length++ );
                tfra->length_size_of_sample_num = LSMASH_MAX( length - 1, tfra->length_size_of_sample_num );
            }
            int err = isom_fragment_set_base_media_decode_time( file, traf, sample->dts );
            if( err < 0 )
                return err;
        }
        trun->first_sample_flags = sample_flags;
        current->first_dts = sample->dts;
    }
    /* Update the optional rows in the current track run except for sample_duration if needed. */
    if( sample->length != tfhd->default_sample_size )
        trun->flags |= ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT;
    if( isom_compare_sample_flags( &sample_flags, &tfhd->default_sample_flags ) )
        trun->flags |= ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT;
    uint32_t sample_composition_time_offset = !non_output_sample ? sample->cts - sample->dts : ISOM_NON_OUTPUT_SAMPLE_OFFSET;
    int32_t  ctd_shift                      = cache->timestamp.ctd_shift;
    if( sample_composition_time_offset )
    {
        trun->flags |= ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT;
        /* Check if negative composition time offset is present. */
        if( !non_output_sample )
        {
            if( (sample->cts + ctd_shift) < sample->dts )
            {
                if( file->max_isom_version < 6 )
                    return LSMASH_ERR_INVALID_DATA; /* Negative composition time offset is invalid. */
                if( (sample->dts - sample->cts) > INT32_MAX )
                    return LSMASH_ERR_INVALID_DATA; /* Overflow */
                ctd_shift = sample->dts - sample->cts;
                trun->version = 1;
            }
        }
        else
        {
            if( file->max_isom_version < 6 )
                return LSMASH_ERR_INVALID_DATA; /* Negative composition time offset is invalid. */
            trun->version = 1;
        }
    }
    if( trun->flags )
    {
        isom_trun_optional_row_t *row = isom_request_trun_optional_row( trun, tfhd, trun->sample_count );
        if( !row )
            return LSMASH_ERR_NAMELESS;
        row->sample_size                    = sample->length;
        row->sample_flags                   = sample_flags;
        row->sample_composition_time_offset = sample_composition_time_offset;
    }
    /* Set up the sample groupings for random access. */
    int ret;
    if( (ret = isom_group_random_access( (isom_box_t *)traf, cache, sample )) < 0
     || (ret = isom_group_roll_recovery( (isom_box_t *)traf, cache, sample )) < 0 )
        return ret;
    /* Set up the previous sample_duration if this sample is not the first sample in the overall movie. */
    uint32_t sample_duration;
    if( cache->fragment->has_samples )
    {
        /* Note: when using for live streaming, it is not good idea to return error by sample->dts < prev_dts
         * since that's trivial for such semi-permanent presentation. */
        uint64_t prev_dts = cache->timestamp.dts;
        if( sample->dts <= prev_dts
         || sample->dts >  prev_dts + UINT32_MAX )
            return LSMASH_ERR_INVALID_DATA;
        sample_duration = sample->dts - prev_dts;
        if( (ret = isom_update_fragment_previous_sample_duration( traf, trex, sample_duration )) < 0 )
            return ret;
    }
    else
        sample_duration = cache->fragment->last_duration;
    isom_update_cache_timestamp( cache, sample->dts, sample->cts, ctd_shift, sample_duration, non_output_sample );
    return delimit;
}

static int isom_append_fragment_sample_internal_initial
(
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry
)
{
    /* Update the sample tables of this track fragment enclosing the initial movie.
     * If a new chunk was created, append the previous one to the pool of this movie fragment. */
    uint32_t samples_per_packet;
    int ret = isom_update_sample_tables( trak, sample, &samples_per_packet, sample_entry );
    if( ret < 0 )
        return ret;
    else if( ret == 1 )
        isom_append_fragment_track_run( trak->file, &trak->cache->chunk );
    isom_fragment_update_cache( trak->cache, sample, trak->file );
    /* Add a new sample into the pool of this track fragment. */
    if( (ret = isom_pool_sample( trak->cache->chunk.pool, sample, samples_per_packet )) < 0 )
        return ret;
    return 0;
}

static int isom_append_fragment_sample_internal
(
    isom_traf_t         *traf,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry   /* unused */
)
{
    /* Update the sample tables of this track fragment.
     * If a new track run was created, append the previous one to the pool of this movie fragment. */
    int ret = isom_fragment_update_sample_tables( traf, sample );
    if( ret < 0 )
        return ret;
    else if( ret == 1 )
        isom_append_fragment_track_run( traf->file, &traf->cache->chunk );
    isom_fragment_update_cache( traf->cache, sample, traf->file );
    /* Add a new sample into the pool of this track fragment. */
    if( (ret = isom_pool_sample( traf->cache->chunk.pool, sample, 1 )) < 0 )
        return ret;
    return 0;
}

int isom_append_fragment_sample
(
    lsmash_file_t       *file,
    isom_trak_t         *trak,
    lsmash_sample_t     *sample,
    isom_sample_entry_t *sample_entry
)
{
    if( !trak->cache->fragment )
        return LSMASH_ERR_NAMELESS;
    isom_fragment_manager_t *fragment = file->fragment;
    assert( fragment && fragment->pool );
    /* Write the Segment Type Box here if required and if it was not written yet. */
    if( !(file->flags & LSMASH_FILE_MODE_INITIALIZATION)
     && file->styp_list.head
     && LSMASH_IS_NON_EXISTING_BOX( (isom_styp_t *)file->styp_list.head->data ) )
    {
        isom_styp_t *styp = (isom_styp_t *)file->styp_list.head->data;
        if( !(styp->manager & LSMASH_WRITTEN_BOX) )
        {
            int ret = isom_write_box( file->bs, (isom_box_t *)styp );
            if( ret < 0 )
                return ret;
            file->size += styp->size;
        }
    }
    int (*func_append_sample)( void *, lsmash_sample_t *, isom_sample_entry_t * ) = NULL;
    void *track_fragment;
    if( LSMASH_IS_NON_EXISTING_BOX( fragment->movie ) )
    {
        /* Forbid adding a sample into the initial movie if requiring compatibility with Media Segment. */
        if( file->media_segment )
            return LSMASH_ERR_NAMELESS;
        func_append_sample = (int (*)( void *, lsmash_sample_t *, isom_sample_entry_t * ))isom_append_fragment_sample_internal_initial;
        track_fragment = trak;
    }
    else
    {
        /* NOTE: there are codes to support non-output sample signaling in fragments but we disabled them currently since the
         * ISOBMFF spec 5th edition mentions 'ctts' and 'cslg' in 'stbl' which exists in the initial movie only. Therefore,
         * as a safety, reject non-output samples here. */
        if( sample->cts == LSMASH_TIMESTAMP_UNDEFINED )
            return LSMASH_ERR_INVALID_DATA;
        isom_traf_t *traf = isom_get_traf( fragment->movie, trak->tkhd->track_ID );
        if( LSMASH_IS_NON_EXISTING_BOX( traf ) )
        {
            traf = isom_add_traf( fragment->movie );
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tfhd( traf ) ) )
                return LSMASH_ERR_NAMELESS;
            traf->tfhd->flags                  = ISOM_TF_FLAGS_DURATION_IS_EMPTY; /* no samples for this track fragment yet */
            traf->tfhd->track_ID               = trak->tkhd->track_ID;
            traf->cache                        = trak->cache;
            traf->cache->fragment->traf_number = fragment->movie->traf_list.entry_count;
            int ret;
            if( (traf->cache->fragment->rap_grouping  && (ret = isom_add_sample_grouping( (isom_box_t *)traf, ISOM_GROUP_TYPE_RAP  )) < 0)
             || (traf->cache->fragment->roll_grouping && (ret = isom_add_sample_grouping( (isom_box_t *)traf, ISOM_GROUP_TYPE_ROLL )) < 0) )
                return ret;
        }
        else if( LSMASH_IS_NON_EXISTING_BOX( traf->file->initializer->moov->mvex )
              || LSMASH_IS_NON_EXISTING_BOX( traf->tfhd )
              || !traf->cache )
            return LSMASH_ERR_NAMELESS;
        func_append_sample = (int (*)( void *, lsmash_sample_t *, isom_sample_entry_t * ))isom_append_fragment_sample_internal;
        track_fragment = traf;
    }
    return isom_append_sample_by_type( track_fragment, sample, sample_entry, func_append_sample );
}

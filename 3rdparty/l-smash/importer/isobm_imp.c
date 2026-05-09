/*****************************************************************************
 * isobm_imp.c
 *****************************************************************************
 * Copyright (C) 2014-2017 L-SMASH project
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

#define LSMASH_IMPORTER_INTERNAL
#include "importer.h"

/*********************************************************************************
    ISO Base Media File Format (ISOBMFF) / QuickTime File Format (QTFF) importer

    TODO: Make this importer work for multiple tracks.
**********************************************************************************/
#include "core/read.h"
#include "core/timeline.h"

typedef struct
{
    uint64_t       timebase;
    uint32_t       track_ID;
    uint32_t       current_sample_description_index;
    uint32_t       au_number;
} isobm_importer_t;

static void remove_isobm_importer( isobm_importer_t *isobm_imp )
{
    if( !isobm_imp )
        return;
    lsmash_free( isobm_imp );
}

static isobm_importer_t *create_isobm_importer( importer_t *importer )
{
    isobm_importer_t *isobm_imp = (isobm_importer_t *)lsmash_malloc_zero( sizeof(isobm_importer_t) );
    if( isobm_imp )
    {
        isobm_imp->timebase = 1;
        return isobm_imp;
    }
    else
        return NULL;
}

static void isobm_importer_cleanup( importer_t *importer )
{
    debug_if( importer && importer->info )
        remove_isobm_importer( importer->info );
}

static int isobm_importer_get_accessunit( importer_t *importer, uint32_t track_number, lsmash_sample_t **p_sample )
{
    if( !importer->info )
        return LSMASH_ERR_NAMELESS;
    if( track_number != 1 )
        return LSMASH_ERR_FUNCTION_PARAM;
    importer_status current_status = importer->status;
    if( current_status == IMPORTER_ERROR )
        return LSMASH_ERR_NAMELESS;
    if( current_status == IMPORTER_EOF )
        return IMPORTER_EOF;
    isobm_importer_t *isobm_imp = (isobm_importer_t *)importer->info;
    lsmash_root_t *root     = importer->root;
    uint32_t       track_ID = lsmash_get_track_ID( root, track_number );
    if( track_ID != isobm_imp->track_ID )
        return LSMASH_ERR_PATCH_WELCOME;
    lsmash_sample_t *sample = lsmash_get_sample_from_media_timeline( root, track_ID, isobm_imp->au_number + 1 );
    if( !sample )
    {
        if( lsmash_check_sample_existence_in_media_timeline( root, track_ID, isobm_imp->au_number + 1 ) )
            return LSMASH_ERR_NAMELESS;
        else
        {
            /* No more samples. */
            importer->status = IMPORTER_EOF;
            return IMPORTER_EOF;
        }
    }
    sample->dts /= isobm_imp->timebase;
    sample->cts /= isobm_imp->timebase;
    if( sample->index != isobm_imp->current_sample_description_index )
    {
        /* Update the active summary. */
        lsmash_summary_t *summary = lsmash_get_summary( root, track_ID, sample->index );
        if( !summary )
        {
            lsmash_delete_sample( sample );
            return LSMASH_ERR_NAMELESS;
        }
        lsmash_list_remove_entry( importer->summaries, track_number );
        if( lsmash_list_add_entry( importer->summaries, summary ) < 0 )
        {
            lsmash_delete_sample( sample );
            lsmash_cleanup_summary( (lsmash_summary_t *)summary );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        isobm_imp->current_sample_description_index = sample->index;
        importer->status = IMPORTER_OK;
        current_status   = IMPORTER_CHANGE;
    }
    *p_sample = sample;
    ++ isobm_imp->au_number;
    return current_status;
}

static int isobm_importer_probe( importer_t *importer )
{
    isobm_importer_t *isobm_imp = create_isobm_importer( importer );
    if( !isobm_imp )
        return LSMASH_ERR_MEMORY_ALLOC;
    int err = 0;
    /* Get the file size if seekable when reading. */
    lsmash_bs_t *bs = importer->bs;
    if( !bs->unseekable )
    {
        int64_t ret = lsmash_bs_read_seek( bs, 0, SEEK_END );
        if( ret < 0 )
        {
            err = ret;
            goto fail;
        }
        bs->written = ret;
        lsmash_bs_read_seek( bs, 0, SEEK_SET );
    }
    if( (err = isom_read_file( importer->file )) < 0 )
        goto fail;
    if( !(importer->file->flags & (LSMASH_FILE_MODE_BOX
                                  | LSMASH_FILE_MODE_FRAGMENTED
                                  | LSMASH_FILE_MODE_INITIALIZATION
                                  | LSMASH_FILE_MODE_MEDIA
                                  | LSMASH_FILE_MODE_INDEX
                                  | LSMASH_FILE_MODE_SEGMENT)) )
    {
        err = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    importer->file->flags |= LSMASH_FILE_MODE_BOX;
    if( importer->is_adhoc_open )
    {
        lsmash_root_t *root = importer->root;
        if( (isobm_imp->track_ID = lsmash_get_track_ID( root, 1 )) == 0 )
        {
            err = LSMASH_ERR_PATCH_WELCOME;
            goto fail;
        }
        lsmash_summary_t *summary = lsmash_get_summary( root, isobm_imp->track_ID, 1 );
        if( (err = lsmash_list_add_entry( importer->summaries, summary )) < 0 )
        {
            lsmash_cleanup_summary( (lsmash_summary_t *)summary );
            goto fail;
        }
        isobm_imp->current_sample_description_index = 1;
    }
    importer->info   = isobm_imp;
    importer->status = IMPORTER_OK;
    return 0;
fail:
    remove_isobm_importer( isobm_imp );
    return err;
}

static uint32_t isobm_importer_get_last_delta( importer_t *importer, uint32_t track_number )
{
    debug_if( !importer || !importer->info )
        return 0;
    isobm_importer_t *isobm_imp = (isobm_importer_t *)importer->info;
    if( !isobm_imp || track_number != 1 )
        return 0;
    uint32_t last_sample_delta;
    if( lsmash_get_last_sample_delta_from_media_timeline( importer->root, isobm_imp->track_ID, &last_sample_delta ) < 0 )
        return 0;
    return last_sample_delta / isobm_imp->timebase;
}

static int isobm_importer_construct_timeline( importer_t *importer, uint32_t track_number )
{
    lsmash_root_t *root = importer->root;
    uint32_t track_ID = lsmash_get_track_ID( root, track_number );
    int err = isom_timeline_construct( root, track_ID );
    if( err < 0 )
        return err;
    if( importer->is_adhoc_open )
    {
        lsmash_summary_t *summary = lsmash_list_get_entry_data( importer->summaries, track_number );
        if( !summary )
            return LSMASH_ERR_NAMELESS;
        summary->max_au_length = lsmash_get_max_sample_size_in_media_timeline( root, track_ID );
        if( summary->summary_type == LSMASH_SUMMARY_TYPE_VIDEO )
        {
            lsmash_media_ts_list_t ts_list;
            if( (err = lsmash_get_media_timestamps( root, track_ID, &ts_list )) < 0 )
                return err;
            uint32_t last_sample_delta;
            if( (err = lsmash_get_last_sample_delta_from_media_timeline( root, track_ID, &last_sample_delta )) < 0 )
                return err;
            isobm_importer_t *isobm_imp = (isobm_importer_t *)importer->info;
            isobm_imp->timebase = last_sample_delta;
            for( uint32_t i = 1; i < ts_list.sample_count; i++ )
                isobm_imp->timebase = lsmash_get_gcd( isobm_imp->timebase, ts_list.timestamp[i].dts - ts_list.timestamp[i - 1].dts );
            lsmash_sort_timestamps_composition_order( &ts_list );
            for( uint32_t i = 1; i < ts_list.sample_count; i++ )
                isobm_imp->timebase = lsmash_get_gcd( isobm_imp->timebase, ts_list.timestamp[i].cts - ts_list.timestamp[i - 1].cts );
            lsmash_delete_media_timestamps( &ts_list );
            if( isobm_imp->timebase == 0 )
                isobm_imp->timebase = 1;
            ((lsmash_video_summary_t *)summary)->timebase  = isobm_imp->timebase;
            ((lsmash_video_summary_t *)summary)->timescale = lsmash_get_media_timescale( root, track_ID );
        }
    }
    return 0;
}

const importer_functions isobm_importer =
{
    { "ISOBMFF/QTFF", offsetof( importer_t, log_level ) },
    1,
    isobm_importer_probe,
    isobm_importer_get_accessunit,
    isobm_importer_get_last_delta,
    isobm_importer_cleanup,
    isobm_importer_construct_timeline
};

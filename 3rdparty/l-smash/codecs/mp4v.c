/*****************************************************************************
 * mp4v.c
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

#include "core/box.h"

#include "mp4a.h"   /* ugly hack for the definition of mp4a_audioProfileLevelIndication */
#include "mp4sys.h"

int mp4v_update_bitrate( isom_stbl_t *stbl, isom_mdhd_t *mdhd, uint32_t sample_description_index )
{
    isom_visual_entry_t *mp4v = (isom_visual_entry_t *)lsmash_list_get_entry_data( &stbl->stsd->list, sample_description_index );
    if( LSMASH_IS_NON_EXISTING_BOX( mp4v ) )
        return LSMASH_ERR_INVALID_DATA;
    isom_esds_t *esds = (isom_esds_t *)isom_get_extension_box_format( &mp4v->extensions, ISOM_BOX_TYPE_ESDS );
    if( LSMASH_IS_NON_EXISTING_BOX( esds ) || !esds->ES )
        return LSMASH_ERR_INVALID_DATA;
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    int err = isom_calculate_bitrate_description( stbl, mdhd, &bufferSizeDB, &maxBitrate, &avgBitrate, sample_description_index );
    if( err < 0 )
        return err;
    /* FIXME: avgBitrate is 0 only if VBR in proper. */
    return mp4sys_update_DecoderConfigDescriptor( esds->ES, bufferSizeDB, maxBitrate, 0 );
}

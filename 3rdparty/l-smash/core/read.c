/*****************************************************************************
 * read.c
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

#include "box.h"
#include "box_default.h"
#include "file.h"
#include "print.h"
#include "read.h"
#include "write.h"

#include "codecs/mp4a.h"
#include "codecs/mp4sys.h"
#include "codecs/description.h"

static int isom_bs_read_box_common( lsmash_bs_t *bs, isom_box_t *box )
{
    assert( bs && box && box->file );
    /* Reset the counter so that we can use it to get position within the box. */
    lsmash_bs_reset_counter( bs );
    /* Read the common fields of box. */
    box->pos = lsmash_bs_get_stream_pos( bs );
    if( bs->eob )
        /* No more read. */
        return 1;
    /* Read size and type. */
    box->size        = lsmash_bs_get_be32( bs );
    box->type.fourcc = lsmash_bs_get_be32( bs );
    /* If size is set to 1, the actual size is repersented in the next 8 bytes.
     * If size is set to 0, this box ends at the end of the stream. */
    if( box->size == 1 )
        box->size = lsmash_bs_get_be64( bs );
    if( box->size == 0 )
    {
        /* This box is the last box in the stream. */
        box->manager |= LSMASH_LAST_BOX;
        if( !bs->unseekable )
            box->size = bs->written - (lsmash_bs_get_stream_pos( bs ) - lsmash_bs_count( bs ));
        else
            /* We haven't known the box size yet.
             * To get the box size, read the stream until the end of the stream. */
            while( 1 )
            {
                int ret = lsmash_bs_read( bs, 1 );
                if( bs->eof || ret < 0 )
                {
                    /* OK, now we know the box size. */
                    box->size = lsmash_bs_count( bs ) + lsmash_bs_get_remaining_buffer_size( bs );
                    if( ret < 0 )
                        /* This box may end incompletely at the end of the stream. */
                        box->manager |= LSMASH_INCOMPLETE_BOX;
                    break;
                }
            }
    }
    /* Here, we don't set up extended box type fields if this box is not a UUID Box. */
    if( box->type.fourcc == ISOM_BOX_TYPE_UUID.fourcc
     && box->size >= lsmash_bs_count( bs ) + 16 )
    {
        /* Get UUID. */
        lsmash_box_type_t *type = &box->type;
        uint64_t temp64 = lsmash_bs_get_be64( bs );
        type->user.fourcc = (temp64 >> 32) & 0xffffffff;
        LSMASH_SET_BE32( &type->user.id[0], temp64 );
        temp64 = lsmash_bs_get_be64( bs );
        LSMASH_SET_BE64( &type->user.id[4], temp64 );
    }
    return bs->eob;
}

static int isom_read_fullbox_common_extension( lsmash_bs_t *bs, isom_box_t *box )
{
    if( !isom_is_fullbox( box ) )
        return 0;
    /* Get version and flags. */
    box->version  = lsmash_bs_get_byte( bs );
    box->flags    = lsmash_bs_get_be24( bs );
    box->manager |= LSMASH_FULLBOX;
    return 0;
}

/* Don't copy destructor since a destructor is defined as box specific. */
static void isom_basebox_common_copy( isom_box_t *dst, const isom_box_t *src )
{
    dst->root    = src->root;
    dst->file    = src->file;
    dst->parent  = src->parent;
    dst->manager = src->manager;
    dst->pos     = src->pos;
    dst->size    = src->size;
    dst->type    = src->type;
}

static void isom_fullbox_common_copy( isom_box_t *dst, const isom_box_t *src )
{
    dst->root    = src->root;
    dst->file    = src->file;
    dst->parent  = src->parent;
    dst->manager = src->manager;
    dst->pos     = src->pos;
    dst->size    = src->size;
    dst->type    = src->type;
    dst->version = src->version;
    dst->flags   = src->flags;
}

static void isom_box_common_copy( void *dst, const void *src )
{
    assert( LSMASH_IS_EXISTING_BOX( (isom_box_t *)dst )
         && LSMASH_IS_EXISTING_BOX( (isom_box_t *)src ) );
    if( lsmash_check_box_type_identical( ((isom_box_t *)src)->type, ISOM_BOX_TYPE_STSD ) )
    {
        isom_basebox_common_copy( (isom_box_t *)dst, (isom_box_t *)src );
        return;
    }
    if( isom_is_fullbox( src ) )
        isom_fullbox_common_copy( (isom_box_t *)dst, (isom_box_t *)src );
    else
        isom_basebox_common_copy( (isom_box_t *)dst, (isom_box_t *)src );
}

static void isom_skip_box_rest( lsmash_bs_t *bs, isom_box_t *box )
{
    if( box->manager & LSMASH_LAST_BOX )
    {
        box->size = (box->manager & LSMASH_FULLBOX) ? ISOM_FULLBOX_COMMON_SIZE : ISOM_BASEBOX_COMMON_SIZE;
        uint64_t start = lsmash_bs_get_stream_pos( bs );
        if( !bs->unseekable )
            lsmash_bs_read_seek( bs, 0, SEEK_END );
        else
            while( !bs->eob )
                lsmash_bs_skip_bytes( bs, UINT32_MAX );
        uint64_t end = lsmash_bs_get_stream_pos( bs );
        box->size += end - start;
        return;
    }
    uint64_t skip_bytes = box->size - lsmash_bs_count( bs );
    if( !bs->unseekable )
    {
        /* The stream is seekable. So, skip by seeking the stream. */
        uint64_t start = lsmash_bs_get_stream_pos( bs );
        lsmash_bs_read_seek( bs, skip_bytes, SEEK_CUR );
        uint64_t end   = lsmash_bs_get_stream_pos( bs );
        if( end - start != skip_bytes )
            /* not match size */
            box->manager |= LSMASH_INCOMPLETE_BOX;
        return;
    }
    /* The stream is unseekable. So, skip by reading the stream. */
    lsmash_bs_skip_bytes_64( bs, skip_bytes );
    if( box->size > lsmash_bs_count( bs ) )
        box->manager |= LSMASH_INCOMPLETE_BOX;
}

static void isom_validate_box_size( lsmash_bs_t *bs, isom_box_t *box )
{
    uint64_t pos = lsmash_bs_count( bs );
    if( box->manager & LSMASH_LAST_BOX )
    {
        box->size = pos;
        return;
    }
    if( box->size < pos )
    {
        fprintf( stderr, "[%s] box has less bytes than expected: %"PRId64"\n", isom_4cc2str( box->type.fourcc ), pos - box->size );
        box->size = pos;
    }
    else if( box->size > pos )
    {
        /* The box probably has extra padding bytes at the end. */
        fprintf( stderr, "[%s] box has more bytes than expected: %"PRId64"\n", isom_4cc2str( box->type.fourcc ), box->size - pos );
        isom_skip_box_rest( bs, box );
    }
}

static int isom_read_children( lsmash_file_t *file, isom_box_t *box, void *parent, int level )
{
    int ret;
    lsmash_bs_t *bs         = file->bs;
    isom_box_t  *parent_box = (isom_box_t *)parent;
    uint64_t parent_pos = lsmash_bs_count( bs );
    while( !(ret = isom_read_box( file, box, parent_box, parent_pos, level )) )
    {
        parent_pos += box->size;
        if( parent_box->size <= parent_pos || bs->eob || bs->error )
            break;
    }
    box->size = parent_pos;    /* for file size */
    return ret;
}

static int isom_read_leaf_box_common_last_process( lsmash_file_t *file, isom_box_t *box, int level, void *instance )
{
    isom_validate_box_size( file->bs, box );
    isom_box_common_copy( instance, box );
    return isom_add_print_func( file, instance, level );
}

static int isom_read_unknown_box( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    lsmash_bs_t *bs = file->bs;
    uint64_t read_size = box->size - lsmash_bs_count( bs );
    if( box->manager & LSMASH_INCOMPLETE_BOX )
        return LSMASH_ERR_INVALID_DATA;
    isom_unknown_box_t *unknown = ALLOCATE_BOX( unknown );
    if( LSMASH_IS_NON_EXISTING_BOX( unknown ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    if( lsmash_list_add_entry( &parent->extensions, unknown ) < 0 )
    {
        isom_remove_box_by_itself( unknown );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    isom_box_common_copy( unknown, box );
    unknown->manager |= LSMASH_UNKNOWN_BOX;
    unknown->destruct = (isom_extension_destructor_t)isom_remove_unknown_box;
    isom_set_box_writer( (isom_box_t *)unknown );
    if( read_size )
    {
        unknown->unknown_field = lsmash_bs_get_bytes( bs, read_size );
        if( unknown->unknown_field )
            unknown->unknown_size = read_size;
        else
            unknown->manager |= LSMASH_INCOMPLETE_BOX;
    }
    if( !(file->flags & LSMASH_FILE_MODE_DUMP) )
        return 0;
    /* Create a dummy for dump. */
    isom_dummy_t *dummy = ALLOCATE_BOX( dummy );
    if( LSMASH_IS_NON_EXISTING_BOX( dummy ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    box->manager |= LSMASH_ABSENT_IN_FILE | LSMASH_UNKNOWN_BOX;
    isom_box_common_copy( dummy, box );
    int ret = isom_add_print_func( file, dummy, level );
    if( ret < 0 )
    {
        isom_remove_box_by_itself( dummy );
        return ret;
    }
    return 0;
}

#define ADD_BOX( box_name, parent_type )                                          \
    isom_##box_name##_t *box_name = isom_add_##box_name( (parent_type *)parent ); \
    if( LSMASH_IS_NON_EXISTING_BOX( box_name ) )                                  \
        return LSMASH_ERR_NAMELESS

static int isom_read_ftyp( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED )
     || LSMASH_IS_EXISTING_BOX( ((lsmash_file_t *)parent)->ftyp ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( ftyp, lsmash_file_t );
    lsmash_bs_t *bs = file->bs;
    ftyp->major_brand   = lsmash_bs_get_be32( bs );
    ftyp->minor_version = lsmash_bs_get_be32( bs );
    uint64_t pos = lsmash_bs_count( bs );
    ftyp->brand_count = box->size > pos ? (box->size - pos) / sizeof(uint32_t) : 0;
    size_t alloc_size = ftyp->brand_count * sizeof(uint32_t);
    ftyp->compatible_brands = ftyp->brand_count ? lsmash_malloc( alloc_size ) : NULL;
    if( ftyp->brand_count && !ftyp->compatible_brands )
        return LSMASH_ERR_MEMORY_ALLOC;
    for( uint32_t i = 0; i < ftyp->brand_count; i++ )
        ftyp->compatible_brands[i] = lsmash_bs_get_be32( bs );
    if( !file->compatible_brands && ftyp->compatible_brands )
    {
        file->compatible_brands = lsmash_memdup( ftyp->compatible_brands, alloc_size );
        if( !file->compatible_brands )
            return LSMASH_ERR_MEMORY_ALLOC;
        file->brand_count = ftyp->brand_count;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, ftyp );
}

static int isom_read_styp( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( styp, lsmash_file_t );
    lsmash_bs_t *bs = file->bs;
    styp->major_brand   = lsmash_bs_get_be32( bs );
    styp->minor_version = lsmash_bs_get_be32( bs );
    uint64_t pos = lsmash_bs_count( bs );
    styp->brand_count = box->size > pos ? (box->size - pos) / sizeof(uint32_t) : 0;
    size_t alloc_size = styp->brand_count * sizeof(uint32_t);
    styp->compatible_brands = styp->brand_count ? lsmash_malloc( alloc_size ) : NULL;
    if( styp->brand_count && !styp->compatible_brands )
        return LSMASH_ERR_MEMORY_ALLOC;
    for( uint32_t i = 0; i < styp->brand_count; i++ )
        styp->compatible_brands[i] = lsmash_bs_get_be32( bs );
    if( !file->compatible_brands && styp->compatible_brands )
    {
        file->compatible_brands = lsmash_memdup( styp->compatible_brands, alloc_size );
        if( !file->compatible_brands )
            return LSMASH_ERR_MEMORY_ALLOC;
        file->brand_count = styp->brand_count;
    }
    file->flags |= LSMASH_FILE_MODE_SEGMENT;
    return isom_read_leaf_box_common_last_process( file, box, level, styp );
}

static int isom_read_sidx( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( sidx, lsmash_file_t );
    lsmash_bs_t *bs = file->bs;
    sidx->reference_ID = lsmash_bs_get_be32( bs );
    sidx->timescale    = lsmash_bs_get_be32( bs );
    if( box->version == 0 )
    {
        sidx->earliest_presentation_time = lsmash_bs_get_be32( bs );
        sidx->first_offset               = lsmash_bs_get_be32( bs );
    }
    else
    {
        sidx->earliest_presentation_time = lsmash_bs_get_be64( bs );
        sidx->first_offset               = lsmash_bs_get_be64( bs );
    }
    sidx->reserved        = lsmash_bs_get_be16( bs );
    sidx->reference_count = lsmash_bs_get_be16( bs );
    for( uint64_t pos = lsmash_bs_count( bs );
         pos < box->size && sidx->list->entry_count < sidx->reference_count;
         pos = lsmash_bs_count( bs ) )
    {
        isom_sidx_referenced_item_t *data = lsmash_malloc( sizeof(isom_sidx_referenced_item_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( sidx->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        uint32_t temp32;
        temp32 = lsmash_bs_get_be32( bs );
        data->reference_type = (temp32 >> 31) & 0x00000001;
        data->reference_size =  temp32        & 0x7FFFFFFF;
        data->subsegment_duration = lsmash_bs_get_be32( bs );
        temp32 = lsmash_bs_get_be32( bs );
        data->starts_with_SAP = (temp32 >> 31) & 0x00000001;
        data->SAP_type        = (temp32 >> 28) & 0x00000007;
        data->SAP_delta_time  =  temp32        & 0x0FFFFFFF;
    }
    file->flags |= LSMASH_FILE_MODE_INDEX;
    return isom_read_leaf_box_common_last_process( file, box, level, sidx );
}

static int isom_read_moov( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED )
     || LSMASH_IS_EXISTING_BOX( ((lsmash_file_t *)parent)->moov ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( moov, lsmash_file_t );
    file->flags      |= LSMASH_FILE_MODE_INITIALIZATION;
    file->initializer = file;
    isom_box_common_copy( moov, box );
    int ret = isom_add_print_func( file, moov, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, moov, level );
}

static int isom_read_mvhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV )
     || LSMASH_IS_EXISTING_BOX( ((isom_moov_t *)parent)->mvhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mvhd, isom_moov_t );
    lsmash_bs_t *bs = file->bs;
    if( box->version )
    {
        mvhd->creation_time     = lsmash_bs_get_be64( bs );
        mvhd->modification_time = lsmash_bs_get_be64( bs );
        mvhd->timescale         = lsmash_bs_get_be32( bs );
        mvhd->duration          = lsmash_bs_get_be64( bs );
    }
    else
    {
        mvhd->creation_time     = lsmash_bs_get_be32( bs );
        mvhd->modification_time = lsmash_bs_get_be32( bs );
        mvhd->timescale         = lsmash_bs_get_be32( bs );
        mvhd->duration          = lsmash_bs_get_be32( bs );
    }
    mvhd->rate              = lsmash_bs_get_be32( bs );
    mvhd->volume            = lsmash_bs_get_be16( bs );
    mvhd->reserved          = lsmash_bs_get_be16( bs );
    mvhd->preferredLong[0]  = lsmash_bs_get_be32( bs );
    mvhd->preferredLong[1]  = lsmash_bs_get_be32( bs );
    for( int i = 0; i < 9; i++ )
        mvhd->matrix[i]     = lsmash_bs_get_be32( bs );
    mvhd->previewTime       = lsmash_bs_get_be32( bs );
    mvhd->previewDuration   = lsmash_bs_get_be32( bs );
    mvhd->posterTime        = lsmash_bs_get_be32( bs );
    mvhd->selectionTime     = lsmash_bs_get_be32( bs );
    mvhd->selectionDuration = lsmash_bs_get_be32( bs );
    mvhd->currentTime       = lsmash_bs_get_be32( bs );
    mvhd->next_track_ID     = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mvhd );
}

static int isom_read_iods( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( iods, isom_moov_t );
    lsmash_bs_t *bs = file->bs;
    iods->OD = mp4sys_get_descriptor( bs, NULL );
    if( !iods->OD )
        return LSMASH_ERR_INVALID_DATA;
    return isom_read_leaf_box_common_last_process( file, box, level, iods );
}

static int isom_read_qt_color_table( lsmash_bs_t *bs, isom_qt_color_table_t *color_table )
{
    color_table->seed  = lsmash_bs_get_be32( bs );
    color_table->flags = lsmash_bs_get_be16( bs );
    color_table->size  = lsmash_bs_get_be16( bs );
    if( bs->eob )
        return LSMASH_ERR_INVALID_DATA;
    isom_qt_color_array_t *array = lsmash_malloc_zero( (color_table->size + 1) * sizeof(isom_qt_color_array_t) );
    if( !array )
        return LSMASH_ERR_MEMORY_ALLOC;
    color_table->array = array;
    for( uint16_t i = 0; i <= color_table->size; i++ )
    {
        uint64_t color = lsmash_bs_get_be64( bs );
        array[i].value = (color >> 48) & 0xffff;
        array[i].r     = (color >> 32) & 0xffff;
        array[i].g     = (color >> 16) & 0xffff;
        array[i].b     =  color        & 0xffff;
    }
    return 0;
}

static int isom_read_ctab( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( ctab, isom_moov_t );
    lsmash_bs_t *bs = file->bs;
    int ret = isom_read_qt_color_table( bs, &ctab->color_table );
    if( ret < 0 )
        return ret;
    return isom_read_leaf_box_common_last_process( file, box, level, ctab );
}

static int isom_read_trak( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( trak, isom_moov_t );
    box->parent = parent;
    box->root   = file->root;
    box->file   = file;
    isom_box_common_copy( trak, box );
    int ret = isom_add_print_func( file, trak, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, trak, level );
}

static int isom_read_tkhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
     || LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->tkhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tkhd, isom_trak_t );
    lsmash_bs_t *bs = file->bs;
    if( box->version )
    {
        tkhd->creation_time     = lsmash_bs_get_be64( bs );
        tkhd->modification_time = lsmash_bs_get_be64( bs );
        tkhd->track_ID          = lsmash_bs_get_be32( bs );
        tkhd->reserved1         = lsmash_bs_get_be32( bs );
        tkhd->duration          = lsmash_bs_get_be64( bs );
    }
    else
    {
        tkhd->creation_time     = lsmash_bs_get_be32( bs );
        tkhd->modification_time = lsmash_bs_get_be32( bs );
        tkhd->track_ID          = lsmash_bs_get_be32( bs );
        tkhd->reserved1         = lsmash_bs_get_be32( bs );
        tkhd->duration          = lsmash_bs_get_be32( bs );
    }
    tkhd->reserved2[0]    = lsmash_bs_get_be32( bs );
    tkhd->reserved2[1]    = lsmash_bs_get_be32( bs );
    tkhd->layer           = lsmash_bs_get_be16( bs );
    tkhd->alternate_group = lsmash_bs_get_be16( bs );
    tkhd->volume          = lsmash_bs_get_be16( bs );
    tkhd->reserved3       = lsmash_bs_get_be16( bs );
    for( int i = 0; i < 9; i++ )
        tkhd->matrix[i]   = lsmash_bs_get_be32( bs );
    tkhd->width           = lsmash_bs_get_be32( bs );
    tkhd->height          = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, tkhd );
}

static int isom_read_tapt( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
     || LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->tapt ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tapt, isom_trak_t );
    isom_box_common_copy( tapt, box );
    int ret = isom_add_print_func( file, tapt, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, tapt, level );
}

static int isom_read_clef( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_TAPT )
     || LSMASH_IS_EXISTING_BOX( ((isom_tapt_t *)parent)->clef ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( clef, isom_tapt_t );
    lsmash_bs_t *bs = file->bs;
    clef->width  = lsmash_bs_get_be32( bs );
    clef->height = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, clef );
}

static int isom_read_prof( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_TAPT )
     || LSMASH_IS_EXISTING_BOX( ((isom_tapt_t *)parent)->prof ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( prof, isom_tapt_t );
    lsmash_bs_t *bs = file->bs;
    prof->width  = lsmash_bs_get_be32( bs );
    prof->height = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, prof );
}

static int isom_read_enof( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_TAPT )
     || LSMASH_IS_EXISTING_BOX( ((isom_tapt_t *)parent)->enof ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( enof, isom_tapt_t );
    lsmash_bs_t *bs = file->bs;
    enof->width  = lsmash_bs_get_be32( bs );
    enof->height = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, enof );
}

static int isom_read_edts( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
     || LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->edts ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( edts, isom_trak_t );
    isom_box_common_copy( edts, box );
    if( isom_add_print_func( file, edts, level ) < 0 )
        return -1;
    return isom_read_children( file, box, edts, level );
}

static int isom_read_elst( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_EDTS )
     || LSMASH_IS_EXISTING_BOX( ((isom_edts_t *)parent)->elst ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( elst, isom_edts_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && elst->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_elst_entry_t *data = lsmash_malloc( sizeof(isom_elst_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( elst->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        if( box->version == 1 )
        {
            data->segment_duration =          lsmash_bs_get_be64( bs );
            data->media_time       = (int64_t)lsmash_bs_get_be64( bs );
        }
        else
        {
            data->segment_duration =          lsmash_bs_get_be32( bs );
            data->media_time       = (int32_t)lsmash_bs_get_be32( bs );
        }
        data->media_rate = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, elst );
}

static int isom_read_tref( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
     || LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->tref ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tref, isom_trak_t );
    isom_box_common_copy( tref, box );
    int ret = isom_add_print_func( file, tref, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, tref, level );
}

static int isom_read_track_reference_type( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TREF ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_tref_type_t *ref = isom_add_track_reference_type( (isom_tref_t *)parent, box->type.fourcc );
    if( !ref )
        return LSMASH_ERR_NAMELESS;
    lsmash_bs_t *bs = file->bs;
    ref->ref_count = (box->size - lsmash_bs_count( bs ) ) / sizeof(uint32_t);
    if( ref->ref_count )
    {
        ref->track_ID = lsmash_malloc( ref->ref_count * sizeof(uint32_t) );
        if( !ref->track_ID )
        {
            ref->ref_count = 0;
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        for( uint32_t i = 0; i < ref->ref_count; i++ )
            ref->track_ID[i] = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, ref );
}

static int isom_read_mdia( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
     || LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->mdia ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mdia, isom_trak_t );
    isom_box_common_copy( mdia, box );
    int ret = isom_add_print_func( file, mdia, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, mdia, level );
}

static int isom_read_mdhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MDIA )
     || LSMASH_IS_EXISTING_BOX( ((isom_mdia_t *)parent)->mdhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mdhd, isom_mdia_t );
    lsmash_bs_t *bs = file->bs;
    if( box->version )
    {
        mdhd->creation_time     = lsmash_bs_get_be64( bs );
        mdhd->modification_time = lsmash_bs_get_be64( bs );
        mdhd->timescale         = lsmash_bs_get_be32( bs );
        mdhd->duration          = lsmash_bs_get_be64( bs );
    }
    else
    {
        mdhd->creation_time     = lsmash_bs_get_be32( bs );
        mdhd->modification_time = lsmash_bs_get_be32( bs );
        mdhd->timescale         = lsmash_bs_get_be32( bs );
        mdhd->duration          = lsmash_bs_get_be32( bs );
    }
    mdhd->language = lsmash_bs_get_be16( bs );
    mdhd->quality  = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mdhd );
}

static int isom_read_hdlr( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MDIA )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META )
      && !lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MDIA ) && LSMASH_IS_EXISTING_BOX( ((isom_mdia_t *)parent)->hdlr ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META ) && LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->hdlr ))
     || (lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META ) && LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->hdlr ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF ) && LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->hdlr )) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( hdlr, void );
    lsmash_bs_t *bs = file->bs;
    hdlr->componentType         = lsmash_bs_get_be32( bs );
    hdlr->componentSubtype      = lsmash_bs_get_be32( bs );
    hdlr->componentManufacturer = lsmash_bs_get_be32( bs );
    hdlr->componentFlags        = lsmash_bs_get_be32( bs );
    hdlr->componentFlagsMask    = lsmash_bs_get_be32( bs );
    uint64_t pos = lsmash_bs_count( bs );
    hdlr->componentName_length = box->size - pos;
    if( hdlr->componentName_length )
    {
        hdlr->componentName = lsmash_malloc( hdlr->componentName_length );
        if( !hdlr->componentName )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( uint32_t i = 0; pos < box->size; pos = lsmash_bs_count( bs ) )
            hdlr->componentName[i++] = lsmash_bs_get_byte( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, hdlr );
}

static int isom_read_minf( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MDIA )
     || LSMASH_IS_EXISTING_BOX( ((isom_mdia_t *)parent)->minf ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( minf, isom_mdia_t );
    isom_box_common_copy( minf, box );
    int ret = isom_add_print_func( file, minf, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, minf, level );
}

static int isom_read_vmhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->vmhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( vmhd, isom_minf_t );
    lsmash_bs_t *bs = file->bs;
    vmhd->graphicsmode   = lsmash_bs_get_be16( bs );
    for( int i = 0; i < 3; i++ )
        vmhd->opcolor[i] = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, vmhd );
}

static int isom_read_smhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->smhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( smhd, isom_minf_t );
    lsmash_bs_t *bs = file->bs;
    smhd->balance  = lsmash_bs_get_be16( bs );
    smhd->reserved = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, smhd );
}

static int isom_read_hmhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->hmhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( hmhd, isom_minf_t );
    lsmash_bs_t *bs = file->bs;
    hmhd->maxPDUsize = lsmash_bs_get_be16( bs );
    hmhd->avgPDUsize = lsmash_bs_get_be16( bs );
    hmhd->maxbitrate = lsmash_bs_get_be32( bs );
    hmhd->avgbitrate = lsmash_bs_get_be32( bs );
    hmhd->reserved   = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, hmhd );
}

static int isom_read_nmhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->nmhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( nmhd, isom_minf_t );
    return isom_read_leaf_box_common_last_process( file, box, level, nmhd );
}

static int isom_read_gmhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->gmhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( gmhd, isom_minf_t );
    isom_box_common_copy( gmhd, box );
    int ret = isom_add_print_func( file, gmhd, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, gmhd, level );
}

static int isom_read_gmin( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_GMHD )
     || LSMASH_IS_EXISTING_BOX( ((isom_gmhd_t *)parent)->gmin ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( gmin, isom_gmhd_t );
    lsmash_bs_t *bs = file->bs;
    gmin->graphicsmode   = lsmash_bs_get_be16( bs );
    for( int i = 0; i < 3; i++ )
        gmin->opcolor[i] = lsmash_bs_get_be16( bs );
    gmin->balance        = lsmash_bs_get_be16( bs );
    gmin->reserved       = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, gmin );
}

static int isom_read_text( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_GMHD )
     || LSMASH_IS_EXISTING_BOX( ((isom_gmhd_t *)parent)->text ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( text, isom_gmhd_t );
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 9; i++ )
        text->matrix[i] = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, text );
}

static int isom_read_dinf( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META )
      && !lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF ) && LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->dinf ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META ) && LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->dinf ))
     || (lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META ) && LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->dinf )) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( dinf, void );
    isom_box_common_copy( dinf, box );
    int ret = isom_add_print_func( file, dinf, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, dinf, level );
}

static int isom_read_dref( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_DINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_dinf_t *)parent)->dref ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( dref, isom_dinf_t );
    lsmash_bs_t *bs = file->bs;
    dref->list.entry_count = lsmash_bs_get_be32( bs );
    isom_box_common_copy( dref, box );
    int ret = isom_add_print_func( file, dref, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, dref, level );
}

static int isom_read_dref_entry( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_DREF ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_dref_t *dref = (isom_dref_t *)parent;
    if( !dref->list.head )
        dref->list.entry_count = 0; /* discard entry_count gotten from the file */
    isom_dref_entry_t *ref = isom_add_dref_entry( dref, box->type );
    if( !ref )
        return LSMASH_ERR_NAMELESS;
    lsmash_bs_t *bs = file->bs;
    if( lsmash_check_box_type_identical( ref->type, ISOM_BOX_TYPE_URL ) )
    {
        uint64_t pos = lsmash_bs_count( bs );
        ref->location_length = box->size - pos;
        if( ref->location_length )
        {
            ref->location = lsmash_malloc( ref->location_length );
            if( !ref->location )
                return LSMASH_ERR_MEMORY_ALLOC;
            for( uint32_t i = 0; pos < box->size; pos = lsmash_bs_count( bs ) )
                ref->location[i++] = lsmash_bs_get_byte( bs );
        }
    }
    if( box->flags & 0x000001 )
        ref->ref_file = ref->file;
    box->parent = parent;
    return isom_read_leaf_box_common_last_process( file, box, level, ref );
}

static int isom_read_stbl( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MINF )
     || LSMASH_IS_EXISTING_BOX( ((isom_minf_t *)parent)->stbl ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stbl, isom_minf_t );
    isom_box_common_copy( stbl, box );
    int ret = isom_add_print_func( file, stbl, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, stbl, level );
}

static int isom_read_stsd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stsd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stsd, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    stsd->entry_count = lsmash_bs_get_be32( bs );
    isom_box_common_copy( stsd, box );
    int ret = isom_add_print_func( file, stsd, level );
    if( ret < 0 )
        return ret;
    uint64_t stsd_pos = lsmash_bs_count( bs );
    for( uint32_t i = 0; i < stsd->entry_count || (stsd_pos + ISOM_BASEBOX_COMMON_SIZE) <= stsd->size; i++ )
    {
        if( (ret = isom_read_box( file, box, (isom_box_t *)stsd, stsd_pos, level )) != 0 )
            break;
        stsd_pos += box->size;
        if( stsd->size <= stsd_pos || bs->eob || bs->error )
            break;
    }
    if( stsd->size < stsd_pos )
    {
        fprintf( stderr, "[stsd] box has extra bytes: %"PRId64"\n", stsd_pos - stsd->size );
        stsd->size = stsd_pos;
    }
    box->size = stsd->size;
    return ret;
}

static int isom_read_codec_specific( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    lsmash_bs_t *bs = file->bs;
    uint64_t opaque_pos = lsmash_bs_count( bs );
    uint64_t exdata_length = box->size - opaque_pos;
    if( exdata_length > UINT32_MAX )
        return LSMASH_ERR_MEMORY_ALLOC;
    uint8_t *exdata = lsmash_malloc( box->size );
    if( !exdata )
        return LSMASH_ERR_MEMORY_ALLOC;
    int ret = lsmash_bs_get_bytes_ex( bs, exdata_length, exdata + (uintptr_t)opaque_pos );
    if( ret < 0 )
        goto fail;
    LSMASH_SET_BE32( &exdata[0], box->size );
    LSMASH_SET_BE32( &exdata[4], box->type.fourcc );
    uintptr_t i = 8;
    if( box->type.fourcc == ISOM_BOX_TYPE_UUID.fourcc )
    {
        LSMASH_SET_BE32( &exdata[8], box->type.user.fourcc );
        memcpy( &exdata[12], box->type.user.id, 12 );
        i += 16;
    }
    if( box->manager & LSMASH_FULLBOX )
    {
        LSMASH_SET_BYTE( &exdata[i], box->version );
        i += 1;
        LSMASH_SET_BE24( &exdata[i], box->flags );
        i += 3;
    }
    if( i != opaque_pos )
    {
        ret = LSMASH_ERR_INVALID_DATA;
        goto fail;
    }
    if( (ret = isom_add_extension_binary( parent, box->type, LSMASH_BOX_PRECEDENCE_N, exdata, box->size )) < 0 )
        goto fail;
    isom_box_t *ext = (isom_box_t *)parent->extensions.tail->data;
    box->manager |= ext->manager;
    isom_validate_box_size( file->bs, box );
    isom_basebox_common_copy( ext, box );
    return isom_add_print_func( file, ext, level );
fail:
    lsmash_free( exdata );
    return ret;
}

static void *isom_sample_description_alloc( lsmash_codec_type_t sample_type, isom_stsd_t *stsd )
{
    assert( isom_check_media_hdlr_from_stsd( stsd ) );
    void *sample_desc = NULL;
    lsmash_media_type media_type = ((isom_mdia_t *)stsd->parent->parent->parent)->hdlr->componentSubtype;
    if( media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK )
        sample_desc = ALLOCATE_BOX( visual_entry );
    else if( media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK )
        sample_desc = ALLOCATE_BOX( audio_entry );
    else if( media_type == ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK )
    {
        if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_TX3G_TEXT ) )
            sample_desc = ALLOCATE_BOX( tx3g_entry );
        else if( lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TEXT_TEXT ) )
            sample_desc = ALLOCATE_BOX( qt_text_entry );
    }
    else if( lsmash_check_codec_type_identical( sample_type, ISOM_CODEC_TYPE_MP4S_SYSTEM ) )
        sample_desc = ALLOCATE_BOX( mp4s_entry );
    if( !sample_desc )
        return NULL;
    ((isom_box_t *)sample_desc)->offset_in_parent = offsetof( isom_stsd_t, list );
    ((isom_box_t *)sample_desc)->destruct         = (isom_extension_destructor_t)isom_remove_sample_description;
    return sample_desc;
}

static void *isom_add_description( lsmash_codec_type_t sample_type, isom_stsd_t *stsd )
{
    void *sample_desc = isom_sample_description_alloc( sample_type, stsd );
    if( !sample_desc )
        return NULL;
    if( lsmash_list_add_entry( &stsd->list, sample_desc ) < 0 )
    {
        lsmash_free( sample_desc );
        return NULL;
    }
    if( lsmash_list_add_entry( &stsd->extensions, sample_desc ) < 0 )
    {
        lsmash_list_remove_entry_tail( &stsd->list );
        return NULL;
    }
    return sample_desc;
}

static int isom_read_visual_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_visual_entry_t *visual = (isom_visual_entry_t *)isom_add_description( box->type, (isom_stsd_t *)parent );
    if( LSMASH_IS_NON_EXISTING_BOX( visual ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 6; i++ )
        visual->reserved[i]       = lsmash_bs_get_byte( bs );
    visual->data_reference_index  = lsmash_bs_get_be16( bs );
    visual->version               = lsmash_bs_get_be16( bs );
    visual->revision_level        = lsmash_bs_get_be16( bs );
    visual->vendor                = lsmash_bs_get_be32( bs );
    visual->temporalQuality       = lsmash_bs_get_be32( bs );
    visual->spatialQuality        = lsmash_bs_get_be32( bs );
    visual->width                 = lsmash_bs_get_be16( bs );
    visual->height                = lsmash_bs_get_be16( bs );
    visual->horizresolution       = lsmash_bs_get_be32( bs );
    visual->vertresolution        = lsmash_bs_get_be32( bs );
    visual->dataSize              = lsmash_bs_get_be32( bs );
    visual->frame_count           = lsmash_bs_get_be16( bs );
    for( int i = 0; i < 32; i++ )
        visual->compressorname[i] = lsmash_bs_get_byte( bs );
    visual->depth                 = lsmash_bs_get_be16( bs );
    visual->color_table_ID        = lsmash_bs_get_be16( bs );
    int ret;
    if( visual->color_table_ID == 0
     && lsmash_bs_get_pos( bs ) < box->size
     && (ret = isom_read_qt_color_table( bs, &visual->color_table )) < 0 )
        return ret;
    box->parent   = parent;
    box->manager |= LSMASH_VIDEO_DESCRIPTION;
    isom_box_common_copy( visual, box );
    if( (ret = isom_add_print_func( file, visual, level )) < 0 )
        return ret;
    return isom_read_children( file, box, visual, level );
}

static int isom_read_esds( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_MP4V_VIDEO )
     && !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_MP4A_AUDIO )
     && !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_ENCA_AUDIO )
     && !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_M4AE_AUDIO )
     && !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_MP4S_SYSTEM )
     && !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE ) )
        return isom_read_codec_specific( file, box, parent, level );
    if( lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE ) )
    {
        box->type = QT_BOX_TYPE_ESDS;
        assert( LSMASH_IS_EXISTING_BOX( parent->parent ) );
        if( lsmash_check_box_type_identical( parent->parent->type, ISOM_CODEC_TYPE_MP4A_AUDIO ) )
            parent->parent->type = QT_CODEC_TYPE_MP4A_AUDIO;
    }
    else
        box->type = ISOM_BOX_TYPE_ESDS;
    ADD_BOX( esds, void );
    lsmash_bs_t *bs = file->bs;
    esds->ES = mp4sys_get_descriptor( bs, NULL );
    if( !esds->ES )
        return LSMASH_ERR_INVALID_DATA;
    return isom_read_leaf_box_common_last_process( file, box, level, esds );
}

static int isom_read_btrt( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( btrt, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    btrt->bufferSizeDB = lsmash_bs_get_be32( bs );
    btrt->maxBitrate   = lsmash_bs_get_be32( bs );
    btrt->avgBitrate   = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, btrt );
}

static int isom_read_glbl( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( glbl, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t header_size = box->size - ISOM_BASEBOX_COMMON_SIZE;
    if( header_size )
    {
        glbl->header_data = lsmash_malloc( header_size );
        if( !glbl->header_data )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( uint32_t i = 0; i < header_size; i++ )
            glbl->header_data[i] = lsmash_bs_get_byte( bs );
    }
    glbl->header_size = header_size;
    return isom_read_leaf_box_common_last_process( file, box, level, glbl );
}

static int isom_read_clap( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( clap, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    clap->cleanApertureWidthN  = lsmash_bs_get_be32( bs );
    clap->cleanApertureWidthD  = lsmash_bs_get_be32( bs );
    clap->cleanApertureHeightN = lsmash_bs_get_be32( bs );
    clap->cleanApertureHeightD = lsmash_bs_get_be32( bs );
    clap->horizOffN            = lsmash_bs_get_be32( bs );
    clap->horizOffD            = lsmash_bs_get_be32( bs );
    clap->vertOffN             = lsmash_bs_get_be32( bs );
    clap->vertOffD             = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, clap );
}

static int isom_read_pasp( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( pasp, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    pasp->hSpacing = lsmash_bs_get_be32( bs );
    pasp->vSpacing = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, pasp );
}

static int isom_read_colr( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( colr, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    colr->color_parameter_type = lsmash_bs_get_be32( bs );
    if( colr->color_parameter_type == QT_COLOR_PARAMETER_TYPE_NCLC
     || colr->color_parameter_type == ISOM_COLOR_PARAMETER_TYPE_NCLX )
    {
        colr->primaries_index         = lsmash_bs_get_be16( bs );
        colr->transfer_function_index = lsmash_bs_get_be16( bs );
        colr->matrix_index            = lsmash_bs_get_be16( bs );
        if( colr->color_parameter_type == ISOM_COLOR_PARAMETER_TYPE_NCLX )
        {
            if( lsmash_bs_count( bs ) < box->size )
            {
                uint8_t temp8 = lsmash_bs_get_byte( bs );
                colr->full_range_flag = (temp8 >> 7) & 0x01;
                colr->reserved        =  temp8       & 0x7f;
            }
            else
            {
                /* It seems this box is broken or incomplete. */
                box->manager |= LSMASH_INCOMPLETE_BOX;
                colr->full_range_flag = 0;
                colr->reserved        = 0;
            }
        }
        else
            box->manager |= LSMASH_QTFF_BASE;
    }
    box->type = (box->manager & LSMASH_QTFF_BASE) ? QT_BOX_TYPE_COLR : ISOM_BOX_TYPE_COLR;
    return isom_read_leaf_box_common_last_process( file, box, level, colr );
}

static int isom_read_gama( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( gama, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    gama->level = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, gama );
}

static int isom_read_fiel( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( fiel, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    fiel->fields = lsmash_bs_get_byte( bs );
    fiel->detail = lsmash_bs_get_byte( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, fiel );
}

static int isom_read_clli( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( clli, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    clli->max_content_light_level = lsmash_bs_get_be16( bs );
    clli->max_pic_average_light_level = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, clli );
}

static int isom_read_mdcv( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( mdcv, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    mdcv->display_primaries_g_x = lsmash_bs_get_be16( bs );
    mdcv->display_primaries_g_y = lsmash_bs_get_be16( bs );
    mdcv->display_primaries_b_x = lsmash_bs_get_be16( bs );
    mdcv->display_primaries_b_y = lsmash_bs_get_be16( bs );
    mdcv->display_primaries_r_x = lsmash_bs_get_be16( bs );
    mdcv->display_primaries_r_y = lsmash_bs_get_be16( bs );
    mdcv->white_point_x = lsmash_bs_get_be16( bs );
    mdcv->white_point_y = lsmash_bs_get_be16( bs );
    mdcv->max_display_mastering_luminance = lsmash_bs_get_be32( bs );
    mdcv->min_display_mastering_luminance = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mdcv );
}

static int isom_read_cspc( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( cspc, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    cspc->pixel_format = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, cspc );
}

static int isom_read_sgbt( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( sgbt, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    sgbt->significantBits = lsmash_bs_get_byte( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, sgbt );
}

static int isom_read_stsl( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( stsl, isom_visual_entry_t );
    lsmash_bs_t *bs = file->bs;
    stsl->constraint_flag  = lsmash_bs_get_byte( bs );
    stsl->scale_method     = lsmash_bs_get_byte( bs );
    stsl->display_center_x = lsmash_bs_get_be16( bs );
    stsl->display_center_y = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, stsl );
}

static int isom_read_audio_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_audio_entry_t *audio = (isom_audio_entry_t *)isom_add_description( box->type, (isom_stsd_t *)parent );
    if( LSMASH_IS_NON_EXISTING_BOX( audio ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 6; i++ )
        audio->reserved[i]      = lsmash_bs_get_byte( bs );
    audio->data_reference_index = lsmash_bs_get_be16( bs );
    audio->version              = lsmash_bs_get_be16( bs );
    audio->revision_level       = lsmash_bs_get_be16( bs );
    audio->vendor               = lsmash_bs_get_be32( bs );
    audio->channelcount         = lsmash_bs_get_be16( bs );
    audio->samplesize           = lsmash_bs_get_be16( bs );
    audio->compression_ID       = lsmash_bs_get_be16( bs );
    audio->packet_size          = lsmash_bs_get_be16( bs );
    audio->samplerate           = lsmash_bs_get_be32( bs );
    if( audio->version == 0 && isom_is_qt_audio( box->type ) )
    {
        /* Skip weird extra bytes.
         * About QTFF, extensions were first added with Sound Sample Description v1. */
        while( lsmash_bs_count( bs ) + ISOM_BASEBOX_COMMON_SIZE <= box->size )
        {
            uint32_t size = lsmash_bs_show_be32( bs, 0 );
            if( size == 0 || lsmash_bs_count( bs ) + size > box->size )
                lsmash_bs_skip_bytes( bs, 1 );
            else
                break;
        }
    }
    else if( audio->version == 1 )
    {
        if( ((isom_stsd_t *)parent)->version == 0 )
        {
            audio->samplesPerPacket = lsmash_bs_get_be32( bs );
            audio->bytesPerPacket   = lsmash_bs_get_be32( bs );
            audio->bytesPerFrame    = lsmash_bs_get_be32( bs );
            audio->bytesPerSample   = lsmash_bs_get_be32( bs );
            box->manager |= LSMASH_QTFF_BASE;
        }
        else
            /* AudioSampleEntryV1 has no additional fields. */
            box->manager &= ~LSMASH_QTFF_BASE;
    }
    else if( audio->version == 2 )
    {
        audio->sizeOfStructOnly              = lsmash_bs_get_be32( bs );
        audio->audioSampleRate               = lsmash_bs_get_be64( bs );
        audio->numAudioChannels              = lsmash_bs_get_be32( bs );
        audio->always7F000000                = lsmash_bs_get_be32( bs );
        audio->constBitsPerChannel           = lsmash_bs_get_be32( bs );
        audio->formatSpecificFlags           = lsmash_bs_get_be32( bs );
        audio->constBytesPerAudioPacket      = lsmash_bs_get_be32( bs );
        audio->constLPCMFramesPerAudioPacket = lsmash_bs_get_be32( bs );
        box->manager |= LSMASH_QTFF_BASE;
    }
    box->parent   = parent;
    box->manager |= LSMASH_AUDIO_DESCRIPTION;
    isom_box_common_copy( audio, box );
    int ret = isom_add_print_func( file, audio, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, audio, level );
}

static int isom_read_wave( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( wave, isom_audio_entry_t );
    isom_box_common_copy( wave, box );
    int ret = isom_add_print_func( file, wave, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, wave, level );
}

static int isom_read_frma( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE )
     || LSMASH_IS_EXISTING_BOX( ((isom_wave_t *)parent)->frma ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( frma, isom_wave_t );
    lsmash_bs_t *bs = file->bs;
    frma->data_format = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, frma );
}

static int isom_read_enda( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE )
     || LSMASH_IS_EXISTING_BOX( ((isom_wave_t *)parent)->enda ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( enda, isom_wave_t );
    lsmash_bs_t *bs = file->bs;
    enda->littleEndian = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, enda );
}

static int isom_read_terminator( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE )
     || LSMASH_IS_EXISTING_BOX( ((isom_wave_t *)parent)->terminator ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( terminator, isom_wave_t );
    return isom_read_leaf_box_common_last_process( file, box, level, terminator );
}

static int isom_read_chan( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( chan, isom_audio_entry_t );
    lsmash_bs_t *bs = file->bs;
    chan->channelLayoutTag          = lsmash_bs_get_be32( bs );
    chan->channelBitmap             = lsmash_bs_get_be32( bs );
    chan->numberChannelDescriptions = lsmash_bs_get_be32( bs );
    if( chan->numberChannelDescriptions )
    {
        isom_channel_description_t *desc = lsmash_malloc( chan->numberChannelDescriptions * sizeof(isom_channel_description_t) );
        if( !desc )
            return LSMASH_ERR_MEMORY_ALLOC;
        chan->channelDescriptions = desc;
        for( uint32_t i = 0; i < chan->numberChannelDescriptions; i++ )
        {
            desc->channelLabel       = lsmash_bs_get_be32( bs );
            desc->channelFlags       = lsmash_bs_get_be32( bs );
            for( int j = 0; j < 3; j++ )
                desc->coordinates[j] = lsmash_bs_get_be32( bs );
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, chan );
}

static int isom_read_srat( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    ADD_BOX( srat, isom_audio_entry_t );
    lsmash_bs_t *bs = file->bs;
    srat->sampling_rate = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, srat );
}

static int isom_read_qt_text_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_qt_text_entry_t *text = (isom_qt_text_entry_t *)isom_add_description( box->type, (isom_stsd_t *)parent );
    if( LSMASH_IS_NON_EXISTING_BOX( text ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 6; i++ )
        text->reserved[i]        = lsmash_bs_get_byte( bs );
    text->data_reference_index   = lsmash_bs_get_be16( bs );
    text->displayFlags           = lsmash_bs_get_be32( bs );
    text->textJustification      = lsmash_bs_get_be32( bs );
    for( int i = 0; i < 3; i++ )
        text->bgColor[i]         = lsmash_bs_get_be16( bs );
    text->top                    = lsmash_bs_get_be16( bs );
    text->left                   = lsmash_bs_get_be16( bs );
    text->bottom                 = lsmash_bs_get_be16( bs );
    text->right                  = lsmash_bs_get_be16( bs );
    text->scrpStartChar          = lsmash_bs_get_be32( bs );
    text->scrpHeight             = lsmash_bs_get_be16( bs );
    text->scrpAscent             = lsmash_bs_get_be16( bs );
    text->scrpFont               = lsmash_bs_get_be16( bs );
    text->scrpFace               = lsmash_bs_get_be16( bs );
    text->scrpSize               = lsmash_bs_get_be16( bs );
    for( int i = 0; i < 3; i++ )
        text->scrpColor[i]       = lsmash_bs_get_be16( bs );
    text->font_name_length       = lsmash_bs_get_byte( bs );
    if( text->font_name_length )
    {
        text->font_name = lsmash_malloc( text->font_name_length + 1 );
        if( !text->font_name )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( uint8_t i = 0; i < text->font_name_length; i++ )
            text->font_name[i] = lsmash_bs_get_byte( bs );
        text->font_name[text->font_name_length] = '\0';
    }
    box->parent = parent;
    isom_box_common_copy( text, box );
    int ret = isom_add_print_func( file, text, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, text, level );
}

static int isom_read_tx3g_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_tx3g_entry_t *tx3g = (isom_tx3g_entry_t *)isom_add_description( box->type, (isom_stsd_t *)parent );
    if( LSMASH_IS_NON_EXISTING_BOX( tx3g ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 6; i++ )
        tx3g->reserved[i]              = lsmash_bs_get_byte( bs );
    tx3g->data_reference_index         = lsmash_bs_get_be16( bs );
    tx3g->displayFlags                 = lsmash_bs_get_be32( bs );
    tx3g->horizontal_justification     = lsmash_bs_get_byte( bs );
    tx3g->vertical_justification       = lsmash_bs_get_byte( bs );
    for( int i = 0; i < 4; i++ )
        tx3g->background_color_rgba[i] = lsmash_bs_get_byte( bs );
    tx3g->top                          = lsmash_bs_get_be16( bs );
    tx3g->left                         = lsmash_bs_get_be16( bs );
    tx3g->bottom                       = lsmash_bs_get_be16( bs );
    tx3g->right                        = lsmash_bs_get_be16( bs );
    tx3g->startChar                    = lsmash_bs_get_be16( bs );
    tx3g->endChar                      = lsmash_bs_get_be16( bs );
    tx3g->font_ID                      = lsmash_bs_get_be16( bs );
    tx3g->face_style_flags             = lsmash_bs_get_byte( bs );
    tx3g->font_size                    = lsmash_bs_get_byte( bs );
    for( int i = 0; i < 4; i++ )
        tx3g->text_color_rgba[i]       = lsmash_bs_get_byte( bs );
    box->parent = parent;
    isom_box_common_copy( tx3g, box );
    int ret = isom_add_print_func( file, tx3g, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, tx3g, level );
}

static int isom_read_text_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( lsmash_check_codec_type_identical( box->type, QT_CODEC_TYPE_TEXT_TEXT ) )
        return isom_read_qt_text_description( file, box, parent, level );
    else if( lsmash_check_codec_type_identical( box->type, ISOM_CODEC_TYPE_TX3G_TEXT ) )
        return isom_read_tx3g_description( file, box, parent, level );
    assert( 0 );
    return isom_read_unknown_box( file, box, parent, level );
}

static int isom_read_ftab( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_CODEC_TYPE_TX3G_TEXT )
     || LSMASH_IS_EXISTING_BOX( ((isom_tx3g_entry_t *)parent)->ftab ) )
        return isom_read_codec_specific( file, box, parent, level );
    ADD_BOX( ftab, isom_tx3g_entry_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be16( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && ftab->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_font_record_t *data = lsmash_malloc_zero( sizeof(isom_font_record_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( ftab->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->font_ID          = lsmash_bs_get_be16( bs );
        data->font_name_length = lsmash_bs_get_byte( bs );
        if( data->font_name_length )
        {
            data->font_name = lsmash_malloc( data->font_name_length + 1 );
            if( !data->font_name )
                return LSMASH_ERR_MEMORY_ALLOC;
            for( uint8_t i = 0; i < data->font_name_length; i++ )
                data->font_name[i] = lsmash_bs_get_byte( bs );
            data->font_name[data->font_name_length] = '\0';
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, ftab );
}

static int isom_read_mp4s_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_mp4s_entry_t *mp4s = (isom_mp4s_entry_t *)isom_add_description( box->type, (isom_stsd_t *)parent );
    if( LSMASH_IS_NON_EXISTING_BOX( mp4s ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    lsmash_bs_t *bs = file->bs;
    for( int i = 0; i < 6; i++ )
        mp4s->reserved[i]      = lsmash_bs_get_byte( bs );
    mp4s->data_reference_index = lsmash_bs_get_be16( bs );
    box->parent = parent;
    isom_box_common_copy( mp4s, box );
    int ret = isom_add_print_func( file, mp4s, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, mp4s, level );
}

static int isom_read_other_description( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( lsmash_check_codec_type_identical( box->type, ISOM_CODEC_TYPE_MP4S_SYSTEM ) )
        return isom_read_mp4s_description( file, box, parent, level );
    return isom_read_unknown_box( file, box, parent, level );
}

static int isom_read_stts( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stts ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stts, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stts->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_stts_entry_t *data = lsmash_malloc( sizeof(isom_stts_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( stts->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->sample_count = lsmash_bs_get_be32( bs );
        data->sample_delta = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stts );
}

static int isom_read_ctts( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->ctts ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( ctts, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && ctts->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_ctts_entry_t *data = lsmash_malloc( sizeof(isom_ctts_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( ctts->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->sample_count  = lsmash_bs_get_be32( bs );
        data->sample_offset = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, ctts );
}

static int isom_read_cslg( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->cslg ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( cslg, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    cslg->compositionToDTSShift        = lsmash_bs_get_be32( bs );
    cslg->leastDecodeToDisplayDelta    = lsmash_bs_get_be32( bs );
    cslg->greatestDecodeToDisplayDelta = lsmash_bs_get_be32( bs );
    cslg->compositionStartTime         = lsmash_bs_get_be32( bs );
    cslg->compositionEndTime           = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, cslg );
}

static int isom_read_stss( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stss ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stss, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stss->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_stss_entry_t *data = lsmash_malloc( sizeof(isom_stss_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( stss->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->sample_number = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stss );
}

static int isom_read_stps( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stps ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stps, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stps->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_stps_entry_t *data = lsmash_malloc( sizeof(isom_stps_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( stps->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->sample_number = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stps );
}

static int isom_read_sdtp( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL ) && LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->sdtp ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) && LSMASH_IS_EXISTING_BOX( ((isom_traf_t *)parent)->sdtp )) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( sdtp, isom_box_t );
    lsmash_bs_t *bs = file->bs;
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size; pos = lsmash_bs_count( bs ) )
    {
        isom_sdtp_entry_t *data = lsmash_malloc( sizeof(isom_sdtp_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( sdtp->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        uint8_t temp = lsmash_bs_get_byte( bs );
        data->is_leading            = (temp >> 6) & 0x3;
        data->sample_depends_on     = (temp >> 4) & 0x3;
        data->sample_is_depended_on = (temp >> 2) & 0x3;
        data->sample_has_redundancy =  temp       & 0x3;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, sdtp );
}

static int isom_read_stsc( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stsc ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stsc, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stsc->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_stsc_entry_t *data = lsmash_malloc( sizeof(isom_stsc_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( stsc->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->first_chunk              = lsmash_bs_get_be32( bs );
        data->samples_per_chunk        = lsmash_bs_get_be32( bs );
        data->sample_description_index = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stsc );
}

static int isom_read_stsz( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stsz ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stsz, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    stsz->sample_size  = lsmash_bs_get_be32( bs );
    stsz->sample_count = lsmash_bs_get_be32( bs );
    uint64_t pos = lsmash_bs_count( bs );
    if( pos < box->size )
    {
        stsz->list = lsmash_list_create_simple();
        if( !stsz->list )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( ; pos < box->size && stsz->list->entry_count < stsz->sample_count; pos = lsmash_bs_count( bs ) )
        {
            isom_stsz_entry_t *data = lsmash_malloc( sizeof(isom_stsz_entry_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            if( lsmash_list_add_entry( stsz->list, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            data->entry_size = lsmash_bs_get_be32( bs );
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stsz );
}

static int isom_read_stz2( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stz2 ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( stz2, isom_stbl_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t temp32    = lsmash_bs_get_be32( bs );
    stz2->reserved     = temp32 >> 24;
    stz2->field_size   = temp32 & 0xff;
    stz2->sample_count = lsmash_bs_get_be32( bs );
    uint64_t pos = lsmash_bs_count( bs );
    if( pos < box->size )
    {
        if( stz2->field_size == 16 || stz2->field_size == 8 )
        {
            uint64_t (*bs_get_funcs[2])( lsmash_bs_t * ) =
                {
                  lsmash_bs_get_byte_to_64,
                  lsmash_bs_get_be16_to_64
                };
            uint64_t (*bs_get_entry_size)( lsmash_bs_t * ) = bs_get_funcs[ stz2->field_size == 16 ? 1 : 0 ];
            for( ; pos < box->size && stz2->list->entry_count < stz2->sample_count; pos = lsmash_bs_count( bs ) )
            {
                isom_stsz_entry_t *data = lsmash_malloc( sizeof(isom_stsz_entry_t) );
                if( !data )
                    return LSMASH_ERR_MEMORY_ALLOC;
                if( lsmash_list_add_entry( stz2->list, data ) < 0 )
                {
                    lsmash_free( data );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                data->entry_size = bs_get_entry_size( bs );
            }
        }
        else if( stz2->field_size == 4 )
        {
            int parity = 1;
            uint8_t temp8;
            while( pos < box->size && stz2->list->entry_count < stz2->sample_count )
            {
                isom_stsz_entry_t *data = lsmash_malloc( sizeof(isom_stsz_entry_t) );
                if( !data )
                    return LSMASH_ERR_MEMORY_ALLOC;
                if( lsmash_list_add_entry( stz2->list, data ) < 0 )
                {
                    lsmash_free( data );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                /* Read a byte by two entries. */
                if( parity )
                {
                    temp8 = lsmash_bs_get_byte( bs );
                    data->entry_size = (temp8 >> 4) & 0xf;
                }
                else
                {
                    pos = lsmash_bs_count( bs );
                    data->entry_size =  temp8       & 0xf;
                }
                parity ^= 1;
            }
        }
        else
            return LSMASH_ERR_INVALID_DATA;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stz2 );
}

static int isom_read_stco( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     || LSMASH_IS_EXISTING_BOX( ((isom_stbl_t *)parent)->stco ) )
        return isom_read_unknown_box( file, box, parent, level );
    box->type = lsmash_form_iso_box_type( box->type.fourcc );
    int is_stco = lsmash_check_box_type_identical( box->type, ISOM_BOX_TYPE_STCO );
    isom_stco_t *stco = is_stco
                      ? isom_add_stco( (isom_stbl_t *)parent )
                      : isom_add_co64( (isom_stbl_t *)parent );
    if( !stco )
        return LSMASH_ERR_NAMELESS;
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    if( is_stco )
        for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stco->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
        {
            isom_stco_entry_t *data = lsmash_malloc( sizeof(isom_stco_entry_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            if( lsmash_list_add_entry( stco->list, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            data->chunk_offset = lsmash_bs_get_be32( bs );
        }
    else
    {
        for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && stco->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
        {
            isom_co64_entry_t *data = lsmash_malloc( sizeof(isom_co64_entry_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            if( lsmash_list_add_entry( stco->list, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            data->chunk_offset = lsmash_bs_get_be64( bs );
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, stco );
}

static int isom_read_sgpd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( sgpd, void );
    lsmash_bs_t *bs = file->bs;
    sgpd->grouping_type      = lsmash_bs_get_be32( bs );
    if( box->version == 1 )
        sgpd->default_length = lsmash_bs_get_be32( bs );
    uint32_t entry_count     = lsmash_bs_get_be32( bs );
    switch( sgpd->grouping_type )
    {
        case ISOM_GROUP_TYPE_RAP :
        {
            for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && sgpd->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
            {
                isom_rap_entry_t *data = lsmash_malloc( sizeof(isom_rap_entry_t) );
                if( !data )
                    return LSMASH_ERR_MEMORY_ALLOC;
                if( lsmash_list_add_entry( sgpd->list, data ) < 0 )
                {
                    lsmash_free( data );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                memset( data, 0, sizeof(isom_rap_entry_t) );
                /* We don't know groups decided by variable description length. If encountering, skip getting of bytes of it. */
                if( box->version == 1 && !sgpd->default_length )
                    data->description_length = lsmash_bs_get_be32( bs );
                else
                {
                    uint8_t temp = lsmash_bs_get_byte( bs );
                    data->num_leading_samples_known = (temp >> 7) & 0x01;
                    data->num_leading_samples       =  temp       & 0x7f;
                }
            }
            break;
        }
        case ISOM_GROUP_TYPE_ROLL :
        case ISOM_GROUP_TYPE_PROL :
        {
            for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && sgpd->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
            {
                isom_roll_entry_t *data = lsmash_malloc( sizeof(isom_roll_entry_t) );
                if( !data )
                    return LSMASH_ERR_MEMORY_ALLOC;
                if( lsmash_list_add_entry( sgpd->list, data ) < 0 )
                {
                    lsmash_free( data );
                    return LSMASH_ERR_MEMORY_ALLOC;
                }
                memset( data, 0, sizeof(isom_roll_entry_t) );
                /* We don't know groups decided by variable description length. If encountering, skip getting of bytes of it. */
                if( box->version == 1 && !sgpd->default_length )
                    data->description_length = lsmash_bs_get_be32( bs );
                else
                    data->roll_distance      = lsmash_bs_get_be16( bs );
            }
            break;
        }
        default :
            break;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, sgpd );
}

static int isom_read_sbgp( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STBL )
     && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( sbgp, void );
    lsmash_bs_t *bs = file->bs;
    sbgp->grouping_type  = lsmash_bs_get_be32( bs );
    if( box->version == 1 )
        sbgp->grouping_type_parameter = lsmash_bs_get_be32( bs );
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && sbgp->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_group_assignment_entry_t *data = lsmash_malloc( sizeof(isom_group_assignment_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( sbgp->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->sample_count            = lsmash_bs_get_be32( bs );
        data->group_description_index = lsmash_bs_get_be32( bs );
    }
    return isom_read_leaf_box_common_last_process( file, box, level,sbgp );
}

static int isom_read_udta( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV ) && LSMASH_IS_EXISTING_BOX( ((isom_moov_t *)parent)->udta ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK ) && LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->udta )) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( udta, void );
    isom_box_common_copy( udta, box );
    int ret = isom_add_print_func( file, udta, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, udta, level );
}

static int isom_read_chpl( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA )
     || LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->chpl ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( chpl, isom_udta_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count;
    if( box->version == 1 )
    {
        chpl->unknown = lsmash_bs_get_byte( bs );
        entry_count   = lsmash_bs_get_be32( bs );
    }
    else
        entry_count   = lsmash_bs_get_byte( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && chpl->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_chpl_entry_t *data = lsmash_malloc( sizeof(isom_chpl_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( chpl->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->start_time          = lsmash_bs_get_be64( bs );
        data->chapter_name_length = lsmash_bs_get_byte( bs );
        data->chapter_name        = lsmash_malloc( data->chapter_name_length + 1 );
        if( !data->chapter_name )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        for( uint8_t i = 0; i < data->chapter_name_length; i++ )
            data->chapter_name[i] = lsmash_bs_get_byte( bs );
        data->chapter_name[data->chapter_name_length] = '\0';
    }
    return isom_read_leaf_box_common_last_process( file, box, level, chpl );
}

static int isom_read_mvex( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV )
     || LSMASH_IS_EXISTING_BOX( ((isom_moov_t *)parent)->mvex ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mvex, isom_moov_t );
    file->flags |= LSMASH_FILE_MODE_FRAGMENTED;
    isom_box_common_copy( mvex, box );
    int ret = isom_add_print_func( file, mvex, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, mvex, level );
}

static int isom_read_mehd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MVEX )
     || LSMASH_IS_EXISTING_BOX( ((isom_mvex_t *)parent)->mehd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mehd, isom_mvex_t );
    lsmash_bs_t *bs = file->bs;
    if( box->version == 1 )
        mehd->fragment_duration = lsmash_bs_get_be64( bs );
    else
        mehd->fragment_duration = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mehd );
}

static isom_sample_flags_t isom_bs_get_sample_flags( lsmash_bs_t *bs )
{
    uint32_t temp = lsmash_bs_get_be32( bs );
    isom_sample_flags_t flags;
    flags.reserved                    = (temp >> 28) & 0xf;
    flags.is_leading                  = (temp >> 26) & 0x3;
    flags.sample_depends_on           = (temp >> 24) & 0x3;
    flags.sample_is_depended_on       = (temp >> 22) & 0x3;
    flags.sample_has_redundancy       = (temp >> 20) & 0x3;
    flags.sample_padding_value        = (temp >> 17) & 0x7;
    flags.sample_is_non_sync_sample   = (temp >> 16) & 0x1;
    flags.sample_degradation_priority =  temp        & 0xffff;
    return flags;
}

static int isom_read_trex( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MVEX ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( trex, isom_mvex_t );
    box->parent = parent;
    lsmash_bs_t *bs = file->bs;
    trex->track_ID                         = lsmash_bs_get_be32( bs );
    trex->default_sample_description_index = lsmash_bs_get_be32( bs );
    trex->default_sample_duration          = lsmash_bs_get_be32( bs );
    trex->default_sample_size              = lsmash_bs_get_be32( bs );
    trex->default_sample_flags             = isom_bs_get_sample_flags( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, trex );
}

static int isom_read_moof( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( moof, lsmash_file_t );
    box->parent = parent;
    isom_box_common_copy( moof, box );
    int ret = isom_add_print_func( file, moof, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, moof, level );
}

static int isom_read_mfhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOF )
     || LSMASH_IS_EXISTING_BOX( ((isom_moof_t *)parent)->mfhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mfhd, isom_moof_t );
    lsmash_bs_t *bs = file->bs;
    mfhd->sequence_number = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mfhd );
}

static int isom_read_traf( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOF ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( traf, isom_moof_t );
    box->parent = parent;
    isom_box_common_copy( traf, box );
    int ret = isom_add_print_func( file, traf, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, traf, level );
}

static int isom_read_tfhd( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF )
     || LSMASH_IS_EXISTING_BOX( ((isom_traf_t *)parent)->tfhd ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tfhd, isom_traf_t );
    lsmash_bs_t *bs = file->bs;
    tfhd->track_ID = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TF_FLAGS_BASE_DATA_OFFSET_PRESENT         ) tfhd->base_data_offset         = lsmash_bs_get_be64( bs );
    if( box->flags & ISOM_TF_FLAGS_SAMPLE_DESCRIPTION_INDEX_PRESENT ) tfhd->sample_description_index = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_DURATION_PRESENT  ) tfhd->default_sample_duration  = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_SIZE_PRESENT      ) tfhd->default_sample_size      = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TF_FLAGS_DEFAULT_SAMPLE_FLAGS_PRESENT     ) tfhd->default_sample_flags     = isom_bs_get_sample_flags( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, tfhd );
}

static int isom_read_tfdt( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF )
     || LSMASH_IS_EXISTING_BOX( ((isom_traf_t *)parent)->tfdt ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tfdt, isom_traf_t );
    lsmash_bs_t *bs = file->bs;
    if( box->version == 1 )
        tfdt->baseMediaDecodeTime = lsmash_bs_get_be64( bs );
    else
        tfdt->baseMediaDecodeTime = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, tfdt );
}

static int isom_read_trun( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAF ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( trun, isom_traf_t );
    box->parent = parent;
    lsmash_bs_t *bs = file->bs;
    int has_optional_rows = ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT
                          | ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT
                          | ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT
                          | ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT;
    has_optional_rows &= box->flags;
    trun->sample_count = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TR_FLAGS_DATA_OFFSET_PRESENT        ) trun->data_offset        = lsmash_bs_get_be32( bs );
    if( box->flags & ISOM_TR_FLAGS_FIRST_SAMPLE_FLAGS_PRESENT ) trun->first_sample_flags = isom_bs_get_sample_flags( bs );
    if( trun->sample_count && has_optional_rows )
    {
        trun->optional = lsmash_list_create_simple();
        if( !trun->optional )
            return LSMASH_ERR_MEMORY_ALLOC;
        for( uint32_t i = 0; i < trun->sample_count; i++ )
        {
            isom_trun_optional_row_t *data = lsmash_malloc( sizeof(isom_trun_optional_row_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            if( lsmash_list_add_entry( trun->optional, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            if( box->flags & ISOM_TR_FLAGS_SAMPLE_DURATION_PRESENT                ) data->sample_duration                = lsmash_bs_get_be32( bs );
            if( box->flags & ISOM_TR_FLAGS_SAMPLE_SIZE_PRESENT                    ) data->sample_size                    = lsmash_bs_get_be32( bs );
            if( box->flags & ISOM_TR_FLAGS_SAMPLE_FLAGS_PRESENT                   ) data->sample_flags                   = isom_bs_get_sample_flags( bs );
            if( box->flags & ISOM_TR_FLAGS_SAMPLE_COMPOSITION_TIME_OFFSET_PRESENT ) data->sample_composition_time_offset = lsmash_bs_get_be32( bs );
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, trun );
}

static int isom_read_free( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( file->fake_file_mode )
        return isom_read_unknown_box( file, box, parent, level );
    isom_skip_t *skip = ALLOCATE_BOX( skip );
    if( LSMASH_IS_NON_EXISTING_BOX( skip ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    isom_skip_box_rest( file->bs, box );
    box->manager |= LSMASH_ABSENT_IN_FILE;
    isom_box_common_copy( skip, box );
    int ret = isom_add_print_func( file, skip, level );
    if( ret < 0 )
    {
        isom_remove_box_by_itself( skip );
        return ret;
    }
    return 0;
}

static int isom_read_mdat( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( file->fake_file_mode || !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_mdat_t *mdat = ALLOCATE_BOX( mdat );
    if( LSMASH_IS_NON_EXISTING_BOX( mdat ) )
        return LSMASH_ERR_MEMORY_ALLOC;
    isom_skip_box_rest( file->bs, box );
    box->manager |= LSMASH_ABSENT_IN_FILE;
    file->flags |= LSMASH_FILE_MODE_MEDIA;
    isom_box_common_copy( mdat, box );
    int ret = isom_add_print_func( file, mdat, level );
    if( ret < 0 )
    {
        isom_remove_box_by_itself( mdat );
        return ret;
    }
    return 0;
}

static int isom_read_meta( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK )
      && !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA ))
     || (lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED ) && LSMASH_IS_EXISTING_BOX( ((lsmash_file_t *)parent)->meta ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MOOV ) && LSMASH_IS_EXISTING_BOX( ((isom_moov_t *)parent)->meta ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TRAK ) && LSMASH_IS_EXISTING_BOX( ((isom_trak_t *)parent)->meta ))
     || (lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA ) && LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->meta )) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( meta, void );
    isom_box_common_copy( meta, box );
    int is_qtff = lsmash_check_box_type_identical( box->type, QT_BOX_TYPE_META );
    if( is_qtff )
    {
        box->manager  |= LSMASH_QTFF_BASE;
        meta->manager |= LSMASH_QTFF_BASE;
    }
    int ret = isom_add_print_func( file, meta, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, meta, level );
}

static int isom_read_keys( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_META ) && !(parent->manager & LSMASH_QTFF_BASE))
     || LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->keys ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( keys, isom_meta_t );
    lsmash_bs_t *bs = file->bs;
    uint32_t entry_count = lsmash_bs_get_be32( bs );
    for( uint64_t pos = lsmash_bs_count( bs ); pos < box->size && keys->list->entry_count < entry_count; pos = lsmash_bs_count( bs ) )
    {
        isom_keys_entry_t *data = lsmash_malloc( sizeof(isom_keys_entry_t) );
        if( !data )
            return LSMASH_ERR_MEMORY_ALLOC;
        if( lsmash_list_add_entry( keys->list, data ) < 0 )
        {
            lsmash_free( data );
            return LSMASH_ERR_MEMORY_ALLOC;
        }
        data->key_size      = lsmash_bs_get_be32( bs );
        data->key_namespace = lsmash_bs_get_be32( bs );
        if( data->key_size > 8 )
        {
            data->key_value = lsmash_bs_get_bytes( bs, data->key_size - 8 );
            if( !data->key_value )
                return LSMASH_ERR_NAMELESS;
        }
        else
            data->key_value = NULL;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, keys );
}

static int isom_read_ilst( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( (!lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META )
      && !lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_META ))
     || LSMASH_IS_EXISTING_BOX( ((isom_meta_t *)parent)->ilst ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( ilst, isom_meta_t );
    isom_box_common_copy( ilst, box );
    int ret = isom_add_print_func( file, ilst, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, ilst, level );
}

static int isom_read_metaitem( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_ILST )
     && !lsmash_check_box_type_identical( parent->type,   QT_BOX_TYPE_ILST ) )
        return isom_read_unknown_box( file, box, parent, level );
    isom_metaitem_t *metaitem = isom_add_metaitem( (isom_ilst_t *)parent, box->type.fourcc );
    if( !metaitem )
        return -1;
    box->parent = parent;
    isom_box_common_copy( metaitem, box );
    int ret = isom_add_print_func( file, metaitem, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, metaitem, level );
}

static int isom_read_mean( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( parent->type.fourcc != ITUNES_METADATA_ITEM_CUSTOM
     || LSMASH_IS_EXISTING_BOX( ((isom_metaitem_t *)parent)->mean ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mean, isom_metaitem_t );
    lsmash_bs_t *bs = file->bs;
    mean->meaning_string_length = box->size - lsmash_bs_count( bs );
    mean->meaning_string = lsmash_bs_get_bytes( bs, mean->meaning_string_length );
    if( !mean->meaning_string )
        return LSMASH_ERR_NAMELESS;
    return isom_read_leaf_box_common_last_process( file, box, level, mean );
}

static int isom_read_name( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( parent->type.fourcc != ITUNES_METADATA_ITEM_CUSTOM
     || LSMASH_IS_EXISTING_BOX( ((isom_metaitem_t *)parent)->name ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( name, isom_metaitem_t );
    lsmash_bs_t *bs = file->bs;
    name->name_length = box->size - lsmash_bs_count( bs );
    name->name = lsmash_bs_get_bytes( bs, name->name_length );
    if( !name->name )
        return LSMASH_ERR_NAMELESS;
    return isom_read_leaf_box_common_last_process( file, box, level, name );
}

static int isom_read_data( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( LSMASH_IS_EXISTING_BOX( ((isom_metaitem_t *)parent)->data ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( data, isom_metaitem_t );
    lsmash_bs_t *bs = file->bs;
    data->value_length = box->size - lsmash_bs_count( bs ) - 8;
    data->reserved            = lsmash_bs_get_be16( bs );
    data->type_set_identifier = lsmash_bs_get_byte( bs );
    data->type_code           = lsmash_bs_get_byte( bs );
    data->the_locale          = lsmash_bs_get_be32( bs );
    if( data->value_length )
    {
        data->value = lsmash_bs_get_bytes( bs, data->value_length );
        if( !data->value )
            return LSMASH_ERR_NAMELESS;
    }
    return isom_read_leaf_box_common_last_process( file, box, level, data );
}

static int isom_read_WLOC( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA )
     || LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->WLOC ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( WLOC, isom_udta_t );
    lsmash_bs_t *bs = file->bs;
    WLOC->x = lsmash_bs_get_be16( bs );
    WLOC->y = lsmash_bs_get_be16( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, WLOC );
}

static int isom_read_LOOP( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA )
     || LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->LOOP ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( LOOP, isom_udta_t );
    lsmash_bs_t *bs = file->bs;
    LOOP->looping_mode = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, LOOP );
}

static int isom_read_SelO( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA )
     || LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->SelO ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( SelO, isom_udta_t );
    lsmash_bs_t *bs = file->bs;
    SelO->selection_only = lsmash_bs_get_byte( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, SelO );
}

static int isom_read_AllF( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA )
     || LSMASH_IS_EXISTING_BOX( ((isom_udta_t *)parent)->AllF ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( AllF, isom_udta_t );
    lsmash_bs_t *bs = file->bs;
    AllF->play_all_frames = lsmash_bs_get_byte( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, AllF );
}

static int isom_read_cprt( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_UDTA ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( cprt, isom_udta_t );
    box->parent = parent;
    lsmash_bs_t *bs = file->bs;
    cprt->language      = lsmash_bs_get_be16( bs );
    cprt->notice_length = box->size - (ISOM_FULLBOX_COMMON_SIZE + 2);
    if( cprt->notice_length )
    {
        cprt->notice = lsmash_bs_get_bytes( bs, cprt->notice_length );
        if( !cprt->notice )
        {
            cprt->notice_length = 0;
            return LSMASH_ERR_NAMELESS;
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, cprt );
}

static int isom_read_mfra( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, LSMASH_BOX_TYPE_UNSPECIFIED )
     || LSMASH_IS_EXISTING_BOX( ((lsmash_file_t *)parent)->mfra ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mfra, lsmash_file_t );
    isom_box_common_copy( mfra, box );
    int ret = isom_add_print_func( file, mfra, level );
    if( ret < 0 )
        return ret;
    return isom_read_children( file, box, mfra, level );
}

static int isom_read_tfra( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MFRA ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( tfra, isom_mfra_t );
    box->parent = parent;
    lsmash_bs_t *bs = file->bs;
    tfra->track_ID        = lsmash_bs_get_be32( bs );
    uint32_t temp         = lsmash_bs_get_be32( bs );
    tfra->number_of_entry = lsmash_bs_get_be32( bs );
    tfra->reserved                  = (temp >> 6) & 0x3ffffff;
    tfra->length_size_of_traf_num   = (temp >> 4) & 0x3;
    tfra->length_size_of_trun_num   = (temp >> 2) & 0x3;
    tfra->length_size_of_sample_num =  temp       & 0x3;
    if( tfra->number_of_entry )
    {
        tfra->list = lsmash_list_create_simple();
        if( !tfra->list )
            return LSMASH_ERR_MEMORY_ALLOC;
        uint64_t (*bs_get_funcs[5])( lsmash_bs_t * ) =
            {
              lsmash_bs_get_byte_to_64,
              lsmash_bs_get_be16_to_64,
              lsmash_bs_get_be24_to_64,
              lsmash_bs_get_be32_to_64,
              lsmash_bs_get_be64
            };
        uint64_t (*bs_put_time)         ( lsmash_bs_t * ) = bs_get_funcs[ 3 + (box->version == 1)         ];
        uint64_t (*bs_put_moof_offset)  ( lsmash_bs_t * ) = bs_get_funcs[ 3 + (box->version == 1)         ];
        uint64_t (*bs_put_traf_number)  ( lsmash_bs_t * ) = bs_get_funcs[ tfra->length_size_of_traf_num   ];
        uint64_t (*bs_put_trun_number)  ( lsmash_bs_t * ) = bs_get_funcs[ tfra->length_size_of_trun_num   ];
        uint64_t (*bs_put_sample_number)( lsmash_bs_t * ) = bs_get_funcs[ tfra->length_size_of_sample_num ];
        for( uint32_t i = 0; i < tfra->number_of_entry; i++ )
        {
            isom_tfra_location_time_entry_t *data = lsmash_malloc( sizeof(isom_tfra_location_time_entry_t) );
            if( !data )
                return LSMASH_ERR_MEMORY_ALLOC;
            if( lsmash_list_add_entry( tfra->list, data ) < 0 )
            {
                lsmash_free( data );
                return LSMASH_ERR_MEMORY_ALLOC;
            }
            data->time          = bs_put_time         ( bs );
            data->moof_offset   = bs_put_moof_offset  ( bs );
            data->traf_number   = bs_put_traf_number  ( bs );
            data->trun_number   = bs_put_trun_number  ( bs );
            data->sample_number = bs_put_sample_number( bs );
        }
    }
    return isom_read_leaf_box_common_last_process( file, box, level, tfra );
}

static int isom_read_mfro( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, int level )
{
    if( !lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_MFRA )
     || LSMASH_IS_EXISTING_BOX( ((isom_mfra_t *)parent)->mfro ) )
        return isom_read_unknown_box( file, box, parent, level );
    ADD_BOX( mfro, isom_mfra_t );
    lsmash_bs_t *bs = file->bs;
    mfro->length = lsmash_bs_get_be32( bs );
    return isom_read_leaf_box_common_last_process( file, box, level, mfro );
}

static void isom_read_skip_extra_bytes( lsmash_bs_t *bs, uint64_t size )
{
    if( !bs->unseekable )
    {
        /* lsmash_bs_read_seek() could fail on offset=INT64_MAX, so use (INT64_MAX >> 1) instead. */
        while( size > (INT64_MAX >> 1) )
        {
            lsmash_bs_read_seek( bs, INT64_MAX >> 1, SEEK_CUR );
            if( lsmash_bs_is_end( bs, 0 ) )
                return;
            size -= (INT64_MAX >> 1);
        }
        lsmash_bs_read_seek( bs, size, SEEK_CUR );
    }
    else
        lsmash_bs_skip_bytes_64( bs, size );
}

static int isom_read_skip_box_extra_bytes( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, uint64_t parent_pos )
{
    lsmash_bs_t *bs = file->bs;
    /* Skip extra bytes of the parent box if any. */
    if( parent->size < parent_pos + ISOM_BASEBOX_COMMON_SIZE )
    {
        uint64_t extra_bytes = parent->size - parent_pos;
        isom_read_skip_extra_bytes( bs, extra_bytes );
        /* This is not the size of a box but makes sense in isom_read_children(). */
        box->size = extra_bytes;
        return 1;
    }
    /* Check if the size is valid or not. */
    if( lsmash_bs_is_end( bs, 3 ) == 0 )
    {
        uint64_t size = (uint64_t)lsmash_bs_show_be32( bs, 0 );
        if( size > 1
         && size < ISOM_BASEBOX_COMMON_SIZE )
        {
            /* It's not a valid size of any box, therefore, it seems we are still within the box considered as the previous.
             * Skip bytes up to the next box of the parent box. */
            uint64_t extra_bytes = parent->size - parent_pos;
            isom_read_skip_extra_bytes( bs, extra_bytes );
            box->size = extra_bytes;
            return 1;
        }
        if( size == 1 && lsmash_bs_is_end( bs, 15 ) == 0 )
            size = lsmash_bs_show_be64( bs, 8 );    /* large size */
        if( size == 0 && parent != (isom_box_t *)file )
        {
            /* Check if this box is actually the last box or not. */
            uint64_t extra_bytes = parent->size - parent_pos;
            if( !bs->unseekable )
                size = bs->written - lsmash_bs_get_stream_pos( bs );
            else
            {
                size = lsmash_bs_get_remaining_buffer_size( bs );
                while( size <= extra_bytes )
                {
                    int ret = lsmash_bs_read( bs, 1 );
                    if( bs->eof || ret < 0 )
                        break;
                    size = lsmash_bs_get_remaining_buffer_size( bs );
                }
            }
            if( size != extra_bytes )
            {
                /* This is not the size of the last box.
                 * It seems we are still within the box considered as the previous or the parent box.
                 * Skip bytes up to the next box. */
                if( box->size > lsmash_bs_count( bs ) )
                {
                    /* within the previous */
                    isom_read_skip_extra_bytes( bs, box->size - lsmash_bs_count( bs ) );
                    box->size = 0;  /* already added to the size of the parent box */
                }
                else
                {
                    /* within the parent */
                    isom_read_skip_extra_bytes( bs, extra_bytes );
                    box->size = extra_bytes;
                }
                return 1;
            }
        }
    }
    return 0;
}

int isom_read_box( lsmash_file_t *file, isom_box_t *box, isom_box_t *parent, uint64_t parent_pos, int level )
{
    assert( parent && parent->root && parent->file );
    if( isom_read_skip_box_extra_bytes( file, box, parent, parent_pos ) != 0 )
        return 0;
    memset( box, 0, sizeof(isom_box_t) );
    box->root   = parent->root;
    box->file   = parent->file;
    box->parent = parent;
    lsmash_bs_t *bs = file->bs;
    int ret = isom_bs_read_box_common( bs, box );
    if( !!ret )
        return ret;     /* return if reached EOF */
    ++level;
    lsmash_box_type_t (*form_box_type_func)( lsmash_compact_box_type_t )   = NULL;
    int (*reader_func)( lsmash_file_t *, isom_box_t *, isom_box_t *, int ) = NULL;
    if( box->type.fourcc != ISOM_BOX_TYPE_FREE.fourcc
     && box->type.fourcc != ISOM_BOX_TYPE_SKIP.fourcc
     && lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_STSD ) )
    {
        /* OK, this box is a sample entry.
         * Here, determine the suitable sample entry reader by media type if possible. */
        if( !isom_check_media_hdlr_from_stsd( (isom_stsd_t *)parent ) )
            goto read_box;
        lsmash_media_type media_type = isom_get_media_type_from_stsd( (isom_stsd_t *)parent );
        if( media_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK )
            reader_func = isom_read_visual_description;
        else if( media_type == ISOM_MEDIA_HANDLER_TYPE_AUDIO_TRACK )
            reader_func = isom_read_audio_description;
        else if( media_type == ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK )
            reader_func = isom_read_text_description;
        else
            reader_func = isom_read_other_description;
        /* Determine either of file formats the sample type is defined in; ISOBMFF or QTFF. */
        static struct description_reader_table_tag
        {
            lsmash_compact_box_type_t fourcc;
            lsmash_box_type_t (*form_box_type_func)( lsmash_compact_box_type_t );
        } description_reader_table[160] = { { 0, NULL } };
        if( !description_reader_table[0].form_box_type_func )
        {
            /* Initialize the table. */
            int i = 0;
#define ADD_DESCRIPTION_READER_TABLE_ELEMENT( type, form_box_type_func ) \
    description_reader_table[i++] = (struct description_reader_table_tag){ type.fourcc, form_box_type_func }
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AVC1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AVC2_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AVC3_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AVC4_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AVCP_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DRAC_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_ENCV_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_HVC1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_HEV1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MJP2_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MP4V_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MVC1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MVC2_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_S263_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SVC1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_VC_1_VIDEO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_2VUY_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_CFHD_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DV10_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVOO_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVOR_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVTV_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVVT_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_HD10_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_M105_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_PNTG_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SVQ1_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SVQ3_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SHR0_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SHR1_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SHR2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SHR3_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SHR4_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_WRLE_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_APCH_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_APCN_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_APCS_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_APCO_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_AP4H_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_AP4X_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_CIVD_VIDEO, lsmash_form_qtff_box_type );
            //ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DRAC_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVC_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVCP_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVPP_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DV5N_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DV5P_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVH2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVH3_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVH5_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVH6_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVHP_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVHQ_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_FLIC_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_GIF_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_H261_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_H263_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_JPEG_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_MJPA_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_MJPB_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_PNG_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_RLE_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_RPZA_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_TGA_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_TIFF_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULRA_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULRG_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULY2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULY0_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULH2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULH0_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_UQY2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_V210_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_V216_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_V308_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_V408_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_V410_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_YUV2_VIDEO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_AC_3_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_ALAC_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DRA1_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSEL_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSDL_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSC_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSE_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSH_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSL_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_DTSX_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_EC_3_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_ENCA_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_G719_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_G726_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_M4AE_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MLPA_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MP4A_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SAMR_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SAWB_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SAWP_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SEVC_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SQCP_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_SSMV_AUDIO, lsmash_form_iso_box_type );
            //ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_TWOS_AUDIO, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_WMA_AUDIO,  lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_23NI_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_MAC3_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_MAC6_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_NONE_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_QDM2_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_QDMC_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_QCLP_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_AGSM_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ALAW_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_CDX2_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_CDX4_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVCA_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_DVI_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_FL32_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_FL64_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_IMA4_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_IN24_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_IN32_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_LPCM_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_SOWT_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_TWOS_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ULAW_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_VDVA_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_FULLMP3_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_MP3_AUDIO,     lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ADPCM2_AUDIO,  lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_ADPCM17_AUDIO, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_GSM49_AUDIO,   lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_NOT_SPECIFIED, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( QT_CODEC_TYPE_TEXT_TEXT, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_TX3G_TEXT, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( ISOM_CODEC_TYPE_MP4S_SYSTEM, lsmash_form_iso_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( LSMASH_CODEC_TYPE_RAW, lsmash_form_qtff_box_type );
            ADD_DESCRIPTION_READER_TABLE_ELEMENT( LSMASH_CODEC_TYPE_UNSPECIFIED, NULL );
            assert( sizeof(description_reader_table) >= (size_t)i * sizeof(description_reader_table[0]) );
#undef ADD_DESCRIPTION_READER_TABLE_ELEMENT
        }
        for( int i = 0; description_reader_table[i].form_box_type_func; i++ )
            if( box->type.fourcc == description_reader_table[i].fourcc )
            {
                form_box_type_func = description_reader_table[i].form_box_type_func;
                goto read_box;
            }
        goto read_box;
    }
    if( lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_WAVE ) )
    {
        form_box_type_func = lsmash_form_qtff_box_type;
             if( box->type.fourcc == QT_BOX_TYPE_FRMA.fourcc )       reader_func = isom_read_frma;
        else if( box->type.fourcc == QT_BOX_TYPE_ENDA.fourcc )       reader_func = isom_read_enda;
        else if( box->type.fourcc == QT_BOX_TYPE_ESDS.fourcc )       reader_func = isom_read_esds;
        else if( box->type.fourcc == QT_BOX_TYPE_CHAN.fourcc )       reader_func = isom_read_chan;
        else if( box->type.fourcc == QT_BOX_TYPE_TERMINATOR.fourcc ) reader_func = isom_read_terminator;
        else                                                         reader_func = isom_read_codec_specific;
        goto read_box;
    }
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_TREF ) )
    {
        form_box_type_func = lsmash_form_iso_box_type;
        reader_func        = isom_read_track_reference_type;
        goto read_box;
    }
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_DREF ) )
    {
        if( box->type.fourcc == ISOM_BOX_TYPE_URL.fourcc
         || box->type.fourcc == ISOM_BOX_TYPE_URN.fourcc )
            form_box_type_func = lsmash_form_iso_box_type;
        else if( box->type.fourcc == QT_BOX_TYPE_ALIS.fourcc
              || box->type.fourcc == QT_BOX_TYPE_RSRC.fourcc )
            form_box_type_func = lsmash_form_qtff_box_type;
        reader_func = isom_read_dref_entry;
        goto read_box;
    }
    static struct box_reader_table_tag
    {
        lsmash_compact_box_type_t fourcc;
        lsmash_box_type_t (*form_box_type_func)( lsmash_compact_box_type_t );
        int (*reader_func)( lsmash_file_t *, isom_box_t *, isom_box_t *, int );
    } box_reader_table[128] = { { 0, NULL, NULL } };
    if( !box_reader_table[0].reader_func )
    {
        /* Initialize the table. */
        int i = 0;
#define ADD_BOX_READER_TABLE_ELEMENT( type, form_box_type_func, reader_func ) \
    box_reader_table[i++] = (struct box_reader_table_tag){ type.fourcc, form_box_type_func, reader_func }
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_FTYP, lsmash_form_iso_box_type,  isom_read_ftyp );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STYP, lsmash_form_iso_box_type,  isom_read_styp );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SIDX, lsmash_form_iso_box_type,  isom_read_sidx );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MOOV, lsmash_form_iso_box_type,  isom_read_moov );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MVHD, lsmash_form_iso_box_type,  isom_read_mvhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_IODS, lsmash_form_iso_box_type,  isom_read_iods );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_CTAB, lsmash_form_qtff_box_type, isom_read_ctab );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TRAK, lsmash_form_iso_box_type,  isom_read_trak );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TKHD, lsmash_form_iso_box_type,  isom_read_tkhd );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_TAPT, lsmash_form_qtff_box_type, isom_read_tapt );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_CLEF, lsmash_form_qtff_box_type, isom_read_clef );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_PROF, lsmash_form_qtff_box_type, isom_read_prof );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_ENOF, lsmash_form_qtff_box_type, isom_read_enof );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_EDTS, lsmash_form_iso_box_type,  isom_read_edts );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_ELST, lsmash_form_iso_box_type,  isom_read_elst );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TREF, lsmash_form_iso_box_type,  isom_read_tref );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MDIA, lsmash_form_iso_box_type,  isom_read_mdia );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MDHD, lsmash_form_iso_box_type,  isom_read_mdhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_HDLR, lsmash_form_iso_box_type,  isom_read_hdlr );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MINF, lsmash_form_iso_box_type,  isom_read_minf );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_VMHD, lsmash_form_iso_box_type,  isom_read_vmhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SMHD, lsmash_form_iso_box_type,  isom_read_smhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_HMHD, lsmash_form_iso_box_type,  isom_read_hmhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_NMHD, lsmash_form_iso_box_type,  isom_read_nmhd );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_GMHD, lsmash_form_qtff_box_type, isom_read_gmhd );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_GMIN, lsmash_form_qtff_box_type, isom_read_gmin );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_TEXT, lsmash_form_qtff_box_type, isom_read_text );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DINF, lsmash_form_iso_box_type,  isom_read_dinf );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DREF, lsmash_form_iso_box_type,  isom_read_dref );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STBL, lsmash_form_iso_box_type,  isom_read_stbl );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STSD, lsmash_form_iso_box_type,  isom_read_stsd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STTS, lsmash_form_iso_box_type,  isom_read_stts );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_CTTS, lsmash_form_iso_box_type,  isom_read_ctts );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_CSLG, lsmash_form_iso_box_type,  isom_read_cslg );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STSS, lsmash_form_iso_box_type,  isom_read_stss );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_STPS, lsmash_form_qtff_box_type, isom_read_stps );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SDTP, lsmash_form_iso_box_type,  isom_read_sdtp );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STSC, lsmash_form_iso_box_type,  isom_read_stsc );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STSZ, lsmash_form_iso_box_type,  isom_read_stsz );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STZ2, lsmash_form_iso_box_type,  isom_read_stz2 );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STCO, lsmash_form_iso_box_type,  isom_read_stco );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_CO64, lsmash_form_iso_box_type,  isom_read_stco );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SGPD, lsmash_form_iso_box_type,  isom_read_sgpd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SBGP, lsmash_form_iso_box_type,  isom_read_sbgp );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_UDTA, lsmash_form_iso_box_type,  isom_read_udta );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_CHPL, lsmash_form_iso_box_type,  isom_read_chpl );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_WLOC, lsmash_form_qtff_box_type, isom_read_WLOC );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_LOOP, lsmash_form_qtff_box_type, isom_read_LOOP );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_SELO, lsmash_form_qtff_box_type, isom_read_SelO );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_ALLF, lsmash_form_qtff_box_type, isom_read_AllF );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MVEX, lsmash_form_iso_box_type,  isom_read_mvex );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MEHD, lsmash_form_iso_box_type,  isom_read_mehd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TREX, lsmash_form_iso_box_type,  isom_read_trex );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MOOF, lsmash_form_iso_box_type,  isom_read_moof );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MFHD, lsmash_form_iso_box_type,  isom_read_mfhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TRAF, lsmash_form_iso_box_type,  isom_read_traf );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TFHD, lsmash_form_iso_box_type,  isom_read_tfhd );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TFDT, lsmash_form_iso_box_type,  isom_read_tfdt );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TRUN, lsmash_form_iso_box_type,  isom_read_trun );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_FREE, lsmash_form_iso_box_type,  isom_read_free );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SKIP, lsmash_form_iso_box_type,  isom_read_free );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MDAT, lsmash_form_iso_box_type,  isom_read_mdat );
        ADD_BOX_READER_TABLE_ELEMENT(   QT_BOX_TYPE_KEYS, lsmash_form_qtff_box_type, isom_read_keys );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MFRA, lsmash_form_iso_box_type,  isom_read_mfra );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_TFRA, lsmash_form_iso_box_type,  isom_read_tfra );
        ADD_BOX_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_MFRO, lsmash_form_iso_box_type,  isom_read_mfro );
        ADD_BOX_READER_TABLE_ELEMENT( LSMASH_BOX_TYPE_UNSPECIFIED, NULL,  NULL );
        assert( sizeof(box_reader_table) >= (size_t)i * sizeof(box_reader_table[0]) );
#undef ADD_BOX_READER_TABLE_ELEMENT
    }
    for( int i = 0; box_reader_table[i].reader_func; i++ )
        if( box->type.fourcc == box_reader_table[i].fourcc )
        {
            form_box_type_func = box_reader_table[i].form_box_type_func;
            reader_func        = box_reader_table[i].reader_func;
            goto read_box;
        }
    if( box->type.fourcc == ISOM_BOX_TYPE_META.fourcc )
    {
       if( lsmash_bs_is_end   ( bs, 3 ) == 0
        && lsmash_bs_show_be32( bs, 0 ) == 0 )
            form_box_type_func = lsmash_form_iso_box_type;
        else
            form_box_type_func = lsmash_form_qtff_box_type;
        reader_func = isom_read_meta;
        goto read_box;
    }
    if( box->type.fourcc == ISOM_BOX_TYPE_ILST.fourcc )
    {
        if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_META ) )
            form_box_type_func = lsmash_form_iso_box_type;
        else if( lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_META ) )
            form_box_type_func = lsmash_form_qtff_box_type;
        if( form_box_type_func )
        {
            reader_func = isom_read_ilst;
            goto read_box;
        }
    }
    if( lsmash_check_box_type_identical( parent->type, ISOM_BOX_TYPE_ILST ) )
        form_box_type_func = lsmash_form_iso_box_type;
    else if( lsmash_check_box_type_identical( parent->type, QT_BOX_TYPE_ILST ) )
        form_box_type_func = lsmash_form_qtff_box_type;
    if( form_box_type_func )
    {
        reader_func = isom_read_metaitem;
        goto read_box;
    }
    if( parent->parent && parent->parent->type.fourcc == ISOM_BOX_TYPE_ILST.fourcc )
    {
        if( box->type.fourcc == ISOM_BOX_TYPE_MEAN.fourcc )
            reader_func = isom_read_mean;
        else if( box->type.fourcc == ISOM_BOX_TYPE_NAME.fourcc )
            reader_func = isom_read_name;
        else if( box->type.fourcc == ISOM_BOX_TYPE_DATA.fourcc )
            reader_func = isom_read_data;
        if( reader_func )
        {
            form_box_type_func = lsmash_form_iso_box_type;
            goto read_box;
        }
    }
    else if( box->type.fourcc == ISOM_BOX_TYPE_CPRT.fourcc )
    {
        /* Avoid confusing udta.cprt with ilst.cprt. */
        form_box_type_func = lsmash_form_iso_box_type;
        reader_func        = isom_read_cprt;
        goto read_box;
    }
    if( parent->parent && lsmash_check_box_type_identical( parent->parent->type, ISOM_BOX_TYPE_STSD ) )
    {
        static struct sample_description_extension_reader_table_tag
        {
            lsmash_compact_box_type_t fourcc;
            lsmash_box_type_t (*form_box_type_func)( lsmash_compact_box_type_t );
            int (*reader_func)( lsmash_file_t *, isom_box_t *, isom_box_t *, int );
        } extension_reader_table[32] = { { 0, NULL, NULL } };
        if( !extension_reader_table[0].reader_func )
        {
            /* Initialize the table. */
            int i = 0;
#define ADD_EXTENSION_READER_TABLE_ELEMENT( type, form_box_type_func, reader_func ) \
    extension_reader_table[i++] = (struct sample_description_extension_reader_table_tag){ type.fourcc, form_box_type_func, reader_func }
            /* Audio */
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_ALAC, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DAC3, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DAMR, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DDTS, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DEC3, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_SRAT, lsmash_form_iso_box_type,  isom_read_srat );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_WFEX, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_CHAN, lsmash_form_qtff_box_type, isom_read_chan );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_WAVE, lsmash_form_qtff_box_type, isom_read_wave );
            /* Video */
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_AVCC, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_BTRT, lsmash_form_iso_box_type,  isom_read_btrt );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_COLR, lsmash_form_iso_box_type,  isom_read_colr );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_CLAP, lsmash_form_iso_box_type,  isom_read_clap );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_DVC1, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_HVCC, lsmash_form_iso_box_type,  isom_read_codec_specific );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_PASP, lsmash_form_iso_box_type,  isom_read_pasp );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_STSL, lsmash_form_iso_box_type,  isom_read_stsl );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_CLLI, lsmash_form_qtff_box_type, isom_read_clli );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_CSPC, lsmash_form_qtff_box_type, isom_read_cspc );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_MDCV, lsmash_form_qtff_box_type, isom_read_mdcv );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_FIEL, lsmash_form_qtff_box_type, isom_read_fiel );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_GAMA, lsmash_form_qtff_box_type, isom_read_gama );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_GLBL, lsmash_form_qtff_box_type, isom_read_glbl );
            ADD_EXTENSION_READER_TABLE_ELEMENT(   QT_BOX_TYPE_SGBT, lsmash_form_qtff_box_type, isom_read_sgbt );
            /* Others */
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_ESDS, lsmash_form_iso_box_type,  isom_read_esds );
            ADD_EXTENSION_READER_TABLE_ELEMENT( ISOM_BOX_TYPE_FTAB, lsmash_form_iso_box_type,  isom_read_ftab );
            ADD_EXTENSION_READER_TABLE_ELEMENT( LSMASH_BOX_TYPE_UNSPECIFIED, NULL,  NULL );
            assert( sizeof(extension_reader_table) >= (size_t)i * sizeof(extension_reader_table[0]) );
#undef ADD_EXTENSION_READER_TABLE_ELEMENT
        }
        for( int i = 0; extension_reader_table[i].reader_func; i++ )
            if( box->type.fourcc == extension_reader_table[i].fourcc )
            {
                form_box_type_func = extension_reader_table[i].form_box_type_func;
                reader_func        = extension_reader_table[i].reader_func;
                goto read_box;
            }
        reader_func = isom_read_codec_specific;
    }
read_box:
    if( form_box_type_func )
        box->type = form_box_type_func( box->type.fourcc );
    if( (ret = isom_read_fullbox_common_extension( bs, box )) < 0 )
        return ret;
    return reader_func
         ? reader_func( file, box, parent, level )
         : isom_read_unknown_box( file, box, parent, level );
}

int isom_read_file( lsmash_file_t *file )
{
    lsmash_bs_t *bs = file->bs;
    if( !bs )
        return LSMASH_ERR_NAMELESS;
    /* Reset the counter so that we can use it to get position within the box. */
    lsmash_bs_reset_counter( bs );
    if( file->flags & LSMASH_FILE_MODE_DUMP )
    {
        file->print = isom_printer_create_list();
        if( !file->print )
            return LSMASH_ERR_MEMORY_ALLOC;
    }
    file->size = UINT64_MAX;
    isom_box_t box;
    int ret = isom_read_children( file, &box, file, 0 );
    file->size = box.size;
    lsmash_bs_empty( bs );
    bs->error = 0;  /* Clear error flag. */
    if( ret < 0 )
        return ret;
    return isom_check_compatibility( file );
}

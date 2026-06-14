/*****************************************************************************
 * file.c
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

/* for _setmode() */
#ifdef _WIN32
#include <io.h>
#endif

#include <string.h>
#include <fcntl.h>

#include "box.h"
#include "read.h"
#include "fragment.h"

#include "importer/importer.h"

static void isom_clear_compat_flags
(
    lsmash_file_t *file
)
{
    /* Clear flags for compatibility. */
    memset( (int8_t *)file + COMPAT_FLAGS_OFFSET, 0, sizeof(lsmash_file_t) - COMPAT_FLAGS_OFFSET );
    file->min_isom_version = UINT8_MAX; /* undefined value */
}

int isom_check_compatibility
(
    lsmash_file_t *file
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( file ) )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_clear_compat_flags( file );
    /* Get the brand container. */
    isom_ftyp_t *ftyp = LSMASH_IS_EXISTING_BOX( file->ftyp )
                      ? file->ftyp
                      : (isom_ftyp_t *)lsmash_list_get_entry_data( &file->styp_list, 1 );
    /* Check brand to decide mandatory boxes. */
    if( LSMASH_IS_NON_EXISTING_BOX( ftyp ) )
    {
        /* No brand declaration means this file is a MP4 version 1 or QuickTime file format. */
        if( LSMASH_IS_EXISTING_BOX( file->moov->iods ) )
        {
            file->mp4_version1    = 1;
            file->isom_compatible = 1;
        }
        else
        {
            file->qt_compatible    = 1;
            file->undefined_64_ver = 1;
        }
        return 0;
    }
    for( uint32_t i = 0; i <= ftyp->brand_count; i++ )
    {
        uint32_t brand = (i == ftyp->brand_count ? ftyp->major_brand : ftyp->compatible_brands[i]);
        switch( brand )
        {
            case ISOM_BRAND_TYPE_QT :
                file->qt_compatible = 1;
                break;
            case ISOM_BRAND_TYPE_MP41 :
                file->mp4_version1 = 1;
                break;
            case ISOM_BRAND_TYPE_MP42 :
                file->mp4_version2 = 1;
                break;
            case ISOM_BRAND_TYPE_AVC1 :
            case ISOM_BRAND_TYPE_ISOM :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 1 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 1 );
                break;
            case ISOM_BRAND_TYPE_ISO2 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 2 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 2 );
                break;
            case ISOM_BRAND_TYPE_ISO3 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 3 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 3 );
                break;
            case ISOM_BRAND_TYPE_ISO4 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 4 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 4 );
                break;
            case ISOM_BRAND_TYPE_ISO5 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 5 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 5 );
                break;
            case ISOM_BRAND_TYPE_ISO6 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 6 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 6 );
                break;
            case ISOM_BRAND_TYPE_ISO7 :
                file->max_isom_version = LSMASH_MAX( file->max_isom_version, 7 );
                file->min_isom_version = LSMASH_MIN( file->min_isom_version, 7 );
                break;
            case ISOM_BRAND_TYPE_M4A :
            case ISOM_BRAND_TYPE_M4B :
            case ISOM_BRAND_TYPE_M4P :
            case ISOM_BRAND_TYPE_M4V :
                file->itunes_movie = 1;
                break;
            case ISOM_BRAND_TYPE_3GP4 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 4 );
                break;
            case ISOM_BRAND_TYPE_3GP5 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 5 );
                break;
            case ISOM_BRAND_TYPE_3GE6 :
            case ISOM_BRAND_TYPE_3GG6 :
            case ISOM_BRAND_TYPE_3GP6 :
            case ISOM_BRAND_TYPE_3GR6 :
            case ISOM_BRAND_TYPE_3GS6 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 6 );
                break;
            case ISOM_BRAND_TYPE_3GP7 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 7 );
                break;
            case ISOM_BRAND_TYPE_3GP8 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 8 );
                break;
            case ISOM_BRAND_TYPE_3GE9 :
            case ISOM_BRAND_TYPE_3GF9 :
            case ISOM_BRAND_TYPE_3GG9 :
            case ISOM_BRAND_TYPE_3GH9 :
            case ISOM_BRAND_TYPE_3GM9 :
            case ISOM_BRAND_TYPE_3GP9 :
            case ISOM_BRAND_TYPE_3GR9 :
            case ISOM_BRAND_TYPE_3GS9 :
            case ISOM_BRAND_TYPE_3GT9 :
                file->max_3gpp_version = LSMASH_MAX( file->max_3gpp_version, 9 );
                break;
            default :
                break;
        }
        switch( brand )
        {
            case ISOM_BRAND_TYPE_AVC1 :
            case ISOM_BRAND_TYPE_ISO2 :
            case ISOM_BRAND_TYPE_ISO3 :
            case ISOM_BRAND_TYPE_ISO4 :
            case ISOM_BRAND_TYPE_ISO5 :
            case ISOM_BRAND_TYPE_ISO6 :
                file->avc_extensions = 1;
                break;
            case ISOM_BRAND_TYPE_3GP4 :
            case ISOM_BRAND_TYPE_3GP5 :
            case ISOM_BRAND_TYPE_3GP6 :
            case ISOM_BRAND_TYPE_3GP7 :
            case ISOM_BRAND_TYPE_3GP8 :
            case ISOM_BRAND_TYPE_3GP9 :
                file->forbid_tref = 1;
                break;
            case ISOM_BRAND_TYPE_3GH9 :
            case ISOM_BRAND_TYPE_3GM9 :
            case ISOM_BRAND_TYPE_DASH :
            case ISOM_BRAND_TYPE_DSMS :
            case ISOM_BRAND_TYPE_LMSG :
            case ISOM_BRAND_TYPE_MSDH :
            case ISOM_BRAND_TYPE_MSIX :
            case ISOM_BRAND_TYPE_SIMS :
                file->media_segment = 1;
                break;
            default :
                break;
        }
    }
    file->isom_compatible = !file->qt_compatible
                          || file->mp4_version1
                          || file->mp4_version2
                          || file->itunes_movie
                          || file->max_3gpp_version;
    file->undefined_64_ver = file->qt_compatible || file->itunes_movie;
    if( file->flags & LSMASH_FILE_MODE_WRITE )
    {
        /* Media Segment is incompatible with ISO Base Media File Format version 4 or former must be compatible with
         * version 6 or later since it requires default-base-is-moof and Track Fragment Base Media Decode Time Box. */
        if( file->media_segment && (file->min_isom_version < 5 || (file->max_isom_version && file->max_isom_version < 6)) )
            return LSMASH_ERR_INVALID_DATA;
        file->allow_moof_base = (file->max_isom_version >= 5 && file->min_isom_version >= 5)
                             || (file->max_isom_version == 0 && file->min_isom_version == UINT8_MAX && file->media_segment);
    }
    return 0;
}

int isom_check_mandatory_boxes
(
    lsmash_file_t *file
)
{
    assert( LSMASH_IS_EXISTING_BOX( file ) );
    /* A movie requires at least one track. */
    if( !file->moov->trak_list.head )
        return LSMASH_ERR_INVALID_DATA;
    for( lsmash_entry_t *entry = file->moov->trak_list.head; entry; entry = entry->next )
    {
        isom_trak_t *trak = (isom_trak_t *)entry->data;
        if( LSMASH_IS_NON_EXISTING_BOX( trak )
         || LSMASH_IS_NON_EXISTING_BOX( trak->tkhd )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->mdhd )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->hdlr )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->dinf->dref )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsd )
         || (LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsz )
          && LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stz2 ))
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stts )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stsc )
         || LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->stbl->stco ) )
            return LSMASH_ERR_INVALID_DATA;
        if( file->qt_compatible && LSMASH_IS_NON_EXISTING_BOX( trak->mdia->minf->hdlr ) )
            return LSMASH_ERR_INVALID_DATA;
        isom_stbl_t *stbl = trak->mdia->minf->stbl;
        if( !stbl->stsd->list.head )
            return LSMASH_ERR_INVALID_DATA;
        if( !file->fragment
         && (!stbl->stsd->list.head
          || !stbl->stts->list || !stbl->stts->list->head
          || !stbl->stsc->list || !stbl->stsc->list->head
          || !stbl->stco->list || !stbl->stco->list->head) )
            return LSMASH_ERR_INVALID_DATA;
    }
    if( !file->fragment )
        return 0;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvex ) )
        return LSMASH_ERR_INVALID_DATA;
    for( lsmash_entry_t *entry = file->moov->mvex->trex_list.head; entry; entry = entry->next )
        if( LSMASH_IS_NON_EXISTING_BOX( (isom_trex_t *)entry->data ) )
            return LSMASH_ERR_INVALID_DATA;
    return 0;
}

int isom_rearrange_data
(
    lsmash_file_t        *file,
    lsmash_adhoc_remux_t *remux,
    uint8_t              *buf[2],
    size_t                read_num,
    size_t                size,
    uint64_t              read_pos,
    uint64_t              write_pos,
    uint64_t              file_size
)
{
    assert( remux );
    /* Copy-pastan */
    int buf_switch = 1;
    lsmash_bs_t *bs = file->bs;
    int     ret;
    int64_t ret64;
    while( read_num == size )
    {
        ret64 = lsmash_bs_write_seek( bs, read_pos, SEEK_SET );
        if( ret64 < 0 )
            return ret64;
        ret = lsmash_bs_read_data( bs, buf[buf_switch], &read_num );
        if( ret < 0 )
            return ret;
        read_pos    = bs->offset;
        buf_switch ^= 0x1;
        ret64 = lsmash_bs_write_seek( bs, write_pos, SEEK_SET );
        if( ret64 < 0 )
            return ret64;
        ret = lsmash_bs_write_data( bs, buf[buf_switch], size );
        if( ret < 0 )
            return ret;
        write_pos = bs->offset;
        if( remux->func )
            remux->func( remux->param, write_pos, file_size ); // FIXME:
    }
    ret = lsmash_bs_write_data( bs, buf[buf_switch ^ 0x1], read_num );
    if( ret < 0 )
        return ret;
    if( remux->func )
        remux->func( remux->param, file_size, file_size ); // FIXME:
    return 0;
}

static int isom_set_brands
(
    lsmash_file_t     *file,
    lsmash_brand_type  major_brand,
    uint32_t           minor_version,
    lsmash_brand_type *brands,
    uint32_t           brand_count
)
{
    if( brand_count > 50 )
        return LSMASH_ERR_FUNCTION_PARAM;   /* We support setting brands up to 50. */
    if( major_brand == 0 && (!brands || brand_count == 0 || brands[0] == 0) )
    {
        if( file->flags & LSMASH_FILE_MODE_INITIALIZATION )
        {
            /* Absence of File Type Box means this file is a QuickTime or MP4 version 1 format file. */
            isom_remove_box_by_itself( file->ftyp );
            /* Anyway we use QTFF as a default file format. */
            isom_clear_compat_flags( file );
            file->qt_compatible = 1;
        }
        else
        {
            /* The absence of the Segment Type Box is allowed.
             * We set brands from the initialization segment after switching to this segment. */
            for( lsmash_entry_t *entry = file->styp_list.head; entry; entry = entry->next )
                isom_remove_box_by_itself( entry->data );
            if( LSMASH_IS_EXISTING_BOX( file->initializer ) )
            {
                /* Copy flags for compatibility. */
                memcpy( (int8_t *)file + COMPAT_FLAGS_OFFSET, file->initializer, sizeof(lsmash_file_t) - COMPAT_FLAGS_OFFSET );
                file->isom_compatible  = 1;
                file->allow_moof_base  = 1;
                file->media_segment    = 1;
                if( file->min_isom_version < 5 )
                    file->min_isom_version = 5;
                if( file->max_isom_version < 6 )
                    file->max_isom_version = 6;
            }
        }
        return 0;
    }
    else if( major_brand == 0 )
    {
        major_brand = brands[0];
        lsmash_log( NULL, LSMASH_LOG_WARNING,
                    "major_brand is not specified. Use the first brand in the compatible brand list as major_brand.\n" );
    }
    else if( !brands )
        brand_count = 0;
    isom_ftyp_t *ftyp;
    if( file->flags & LSMASH_FILE_MODE_INITIALIZATION )
    {
        /* Add File Type Box if absent yet. */
        if( LSMASH_IS_NON_EXISTING_BOX( file->ftyp ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_ftyp( file ) ) )
            return LSMASH_ERR_NAMELESS;
        ftyp = file->ftyp;
    }
    else
    {
        /* Add Segment Type Box if absent yet. */
        ftyp = file->styp_list.head && LSMASH_IS_EXISTING_BOX( (isom_styp_t *)file->styp_list.head->data )
             ? (isom_styp_t *)file->styp_list.head->data
             : isom_add_styp( file );
        if( LSMASH_IS_NON_EXISTING_BOX( ftyp ) )
            return LSMASH_ERR_NAMELESS;
    }
    /* Allocate an array of compatible brands.
     * ISO/IEC 14496-12 doesn't forbid the absence of brands in the compatible brand list.
     * For a reason of safety, however, we set at least one brand in the list. */
    size_t alloc_size = (brand_count ? brand_count : 1) * sizeof(uint32_t);
    lsmash_brand_type *compatible_brands;
    if( !file->compatible_brands )
        compatible_brands = lsmash_malloc( alloc_size );
    else
        compatible_brands = lsmash_realloc( file->compatible_brands, alloc_size );
    if( !compatible_brands )
        return LSMASH_ERR_MEMORY_ALLOC;
    /* Set compatible brands. */
    if( brand_count )
        for( uint32_t i = 0; i < brand_count; i++ )
            compatible_brands[i] = brands[i];
    else
    {
        /* At least one compatible brand. */
        compatible_brands[0] = major_brand;
        brand_count = 1;
    }
    file->compatible_brands = compatible_brands;
    /* Duplicate an array of compatible brands. */
    lsmash_free( ftyp->compatible_brands );
    ftyp->compatible_brands = lsmash_memdup( compatible_brands, alloc_size );
    if( !ftyp->compatible_brands )
    {
        lsmash_freep( &file->compatible_brands );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    ftyp->size          = ISOM_BASEBOX_COMMON_SIZE + 8 + brand_count * 4;
    ftyp->major_brand   = major_brand;
    ftyp->minor_version = minor_version;
    ftyp->brand_count   = brand_count;
    file->brand_count   = brand_count;
    return isom_check_compatibility( file );
}

/*---- default I/O ----*/
typedef struct
{
    FILE *file_ptr;
    int   is_standard_stream;   /* If set to 1, 'file_ptr' points to standard stream (i.e. stdin, stdout or stderr).
                                 * This flag prevents from accidentally closing standard streams. */
    lsmash_file_mode file_mode;
} default_io_stream_t;

static default_io_stream_t *default_io_stream_open( const char *filename, int open_mode )
{
#ifdef _WIN32
    _setmode( _fileno( stdin ),  _O_BINARY );
    _setmode( _fileno( stdout ), _O_BINARY );
    _setmode( _fileno( stderr ), _O_BINARY );
#endif
    default_io_stream_t *stream = (default_io_stream_t *)lsmash_malloc_zero( sizeof(default_io_stream_t) );
    if( !stream )
        return NULL;
    char mode[4] = { 0 };
    if( open_mode == 0 )
    {
        memcpy( mode, "w+b", 4 );
        stream->file_mode = LSMASH_FILE_MODE_WRITE
                          | LSMASH_FILE_MODE_BOX
                          | LSMASH_FILE_MODE_INITIALIZATION
                          | LSMASH_FILE_MODE_MEDIA;
    }
    else if( open_mode == 1 )
    {
        memcpy( mode, "rb", 3 );
        stream->file_mode = LSMASH_FILE_MODE_READ;
    }
    else
        assert( 0 );
    if( !strcmp( filename, "-" ) )
    {
        if( stream->file_mode & LSMASH_FILE_MODE_READ )
        {
            stream->file_ptr           = stdin;
            stream->is_standard_stream = 1;
        }
        else if( stream->file_mode & LSMASH_FILE_MODE_WRITE )
        {
            stream->file_ptr           = stdout;
            stream->is_standard_stream = 1;
            stream->file_mode         |= LSMASH_FILE_MODE_FRAGMENTED;
        }
    }
    else
        stream->file_ptr = lsmash_fopen( filename, mode );
    if( stream->file_ptr == NULL )
        lsmash_freep( &stream );
    return stream;
}

static int default_io_stream_close( default_io_stream_t *stream )
{
    if( !stream )
        return 0;
    int ret = stream->is_standard_stream ? 0 : fclose( stream->file_ptr );
    lsmash_free( stream );
    return ret;
}

static int default_io_stream_read( void *opaque, uint8_t *buf, int size )
{
    int read_size = fread( buf, 1, size, ((default_io_stream_t *)opaque)->file_ptr );
    return ferror( ((default_io_stream_t *)opaque)->file_ptr ) ? LSMASH_ERR_NAMELESS : read_size;
}

static int default_io_stream_write( void *opaque, uint8_t *buf, int size )
{
    return fwrite( buf, 1, size, ((default_io_stream_t *)opaque)->file_ptr );
}

static int64_t default_io_stream_seek( void *opaque, int64_t offset, int whence )
{
    if( lsmash_fseek( ((default_io_stream_t *)opaque)->file_ptr, offset, whence ) != 0 )
        return LSMASH_ERR_NAMELESS;
    return lsmash_ftell( ((default_io_stream_t *)opaque)->file_ptr );
}

/*******************************
    public interfaces
*******************************/

void lsmash_discard_boxes
(
    lsmash_root_t *root
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( root )
     || LSMASH_IS_NON_EXISTING_BOX( root->file ) )
        return;
    isom_remove_all_extension_boxes( &root->file->extensions );
}

int lsmash_open_file
(
    const char               *filename,
    int                       open_mode,
    lsmash_file_parameters_t *param
)
{
    if( !filename || !param || (open_mode != 0 && open_mode != 1) )
        return LSMASH_ERR_FUNCTION_PARAM;
    default_io_stream_t *stream = default_io_stream_open( filename, open_mode );
    if( !stream )
        return LSMASH_ERR_NAMELESS;
    memset( param, 0, sizeof(lsmash_file_parameters_t) );
    param->mode                = stream->file_mode;
    param->opaque              = (void *)stream;
    param->read                = default_io_stream_read;
    param->write               = default_io_stream_write;
    param->seek                = stream->is_standard_stream ? NULL : default_io_stream_seek;
    param->major_brand         = 0;
    param->brands              = NULL;
    param->brand_count         = 0;
    param->minor_version       = 0;
    param->max_chunk_duration  = 0.5;
    param->max_async_tolerance = 2.0;
    param->max_chunk_size      = 4 * 1024 * 1024;
    param->max_read_size       = 4 * 1024 * 1024;
    return 0;
}

int lsmash_close_file
(
    lsmash_file_parameters_t *param
)
{
    if( !param )
        return LSMASH_ERR_NAMELESS;
    int ret = default_io_stream_close( (default_io_stream_t *)param->opaque );
    param->opaque = NULL;
    return ret == 0 ? 0 : LSMASH_ERR_UNKNOWN;
}

lsmash_file_t *lsmash_set_file
(
    lsmash_root_t            *root,
    lsmash_file_parameters_t *param
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( root ) || !param )
        return NULL;
    lsmash_file_t *file = isom_add_file_abstract( root );
    if( LSMASH_IS_NON_EXISTING_BOX( file ) )
        return NULL;
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        goto fail;
    file->bs                  = bs;
    file->flags               = param->mode;
    file->bs->stream          = param->opaque;
    file->bs->read            = param->read;
    file->bs->write           = param->write;
    file->bs->seek            = param->seek;
    file->bs->unseekable      = (param->seek == NULL);
    file->bs->buffer.max_size = param->max_read_size;
    file->max_chunk_duration  = param->max_chunk_duration;
    file->max_async_tolerance = LSMASH_MAX( param->max_async_tolerance, 2 * param->max_chunk_duration );
    file->max_chunk_size      = param->max_chunk_size;
    if( (file->flags & LSMASH_FILE_MODE_WRITE)
     && (file->flags & LSMASH_FILE_MODE_BOX) )
    {
        /* Construction of Segment Index Box requires seekability at our current implementation.
         * If segment is not so large, data rearrangement can be avoided by buffering i.e. the
         * seekability is not essential, but at present we don't support buffering of all materials
         * within segment. */
        if( (file->flags & LSMASH_FILE_MODE_INDEX) && file->bs->unseekable )
            goto fail;
        /* Establish the fragment handler if required. */
        if( file->flags & LSMASH_FILE_MODE_FRAGMENTED )
        {
            file->fragment = lsmash_malloc_zero( sizeof(isom_fragment_manager_t) );
            if( !file->fragment )
                goto fail;
            file->fragment->first_moof_pos = FIRST_MOOF_POS_UNDETERMINED;
            file->fragment->pool = lsmash_list_create( isom_remove_sample_pool );
            if( !file->fragment->pool )
                goto fail;
        }
        else if( file->bs->unseekable )
            /* For unseekable output operations, LSMASH_FILE_MODE_FRAGMENTED shall be set. */
            goto fail;
        /* Establish file types. */
        if( isom_set_brands( file, param->major_brand,
                                   param->minor_version,
                                   param->brands, param->brand_count ) < 0 )
            goto fail;
        /* Create the movie header if the initialization of the streams is required. */
        if( (file->flags & LSMASH_FILE_MODE_INITIALIZATION) && !isom_movie_create( file ) )
            goto fail;
    }
    if( LSMASH_IS_NON_EXISTING_BOX( root->file ) )
        root->file = file;
    return file;
fail:
    isom_remove_box_by_itself( file );
    return NULL;
}

int64_t lsmash_read_file
(
    lsmash_file_t            *file,
    lsmash_file_parameters_t *param
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( file ) )
        return (int64_t)LSMASH_ERR_FUNCTION_PARAM;
    if( !file->bs )
        return (int64_t)LSMASH_ERR_NAMELESS;
    int64_t ret = LSMASH_ERR_NAMELESS;
    if( file->flags & (LSMASH_FILE_MODE_READ | LSMASH_FILE_MODE_DUMP) )
    {
        importer_t *importer = lsmash_importer_alloc( file->root );
        if( !importer )
            return (int64_t)LSMASH_ERR_MEMORY_ALLOC;
        lsmash_importer_set_file( importer, file );
        ret = lsmash_importer_find( importer, "ISOBMFF/QTFF", !file->bs->unseekable );
        if( ret < 0 )
            return ret;
        if( param )
        {
            if( LSMASH_IS_EXISTING_BOX( file->ftyp ) )
            {
                /* file types */
                isom_ftyp_t *ftyp = file->ftyp;
                param->major_brand   = ftyp->major_brand ? ftyp->major_brand : ISOM_BRAND_TYPE_QT;
                param->minor_version = ftyp->minor_version;
                param->brands        = file->compatible_brands;
                param->brand_count   = file->brand_count;
            }
            else if( file->styp_list.head && LSMASH_IS_EXISTING_BOX( (isom_styp_t *)file->styp_list.head->data ) )
            {
                /* segment types */
                isom_styp_t *styp = (isom_styp_t *)file->styp_list.head->data;
                param->major_brand   = styp->major_brand ? styp->major_brand : ISOM_BRAND_TYPE_QT;
                param->minor_version = styp->minor_version;
                param->brands        = file->compatible_brands;
                param->brand_count   = file->brand_count;
            }
            else
            {
                param->major_brand   = file->mp4_version1 ? ISOM_BRAND_TYPE_MP41 : ISOM_BRAND_TYPE_QT;
                param->minor_version = 0;
                param->brands        = NULL;
                param->brand_count   = 0;
            }
        }
    }
    return ret;
}

int lsmash_activate_file
(
    lsmash_root_t *root,
    lsmash_file_t *file
)
{
    if( !root || !file || file->root != root )
        return LSMASH_ERR_FUNCTION_PARAM;
    root->file = file;
    return 0;
}

int lsmash_switch_media_segment
(
    lsmash_root_t        *root,
    lsmash_file_t        *successor,
    lsmash_adhoc_remux_t *remux
)
{
    if( LSMASH_IS_NON_EXISTING_BOX( root ) || !remux )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *predecessor = root->file;
    if( LSMASH_IS_NON_EXISTING_BOX( predecessor ) || LSMASH_IS_NON_EXISTING_BOX( successor )
     || predecessor == successor
     || predecessor->root != successor->root
     || LSMASH_IS_NON_EXISTING_BOX( predecessor->root ) || LSMASH_IS_NON_EXISTING_BOX( successor->root )
     || predecessor->root != root || successor->root != root
     ||  (successor->flags & LSMASH_FILE_MODE_INITIALIZATION)
     || !(successor->flags & LSMASH_FILE_MODE_MEDIA)
     || !(predecessor->flags & LSMASH_FILE_MODE_WRITE)      || !(successor->flags & LSMASH_FILE_MODE_WRITE)
     || !(predecessor->flags & LSMASH_FILE_MODE_BOX)        || !(successor->flags & LSMASH_FILE_MODE_BOX)
     || !(predecessor->flags & LSMASH_FILE_MODE_FRAGMENTED) || !(successor->flags & LSMASH_FILE_MODE_FRAGMENTED)
     || !(predecessor->flags & LSMASH_FILE_MODE_SEGMENT)    || !(successor->flags & LSMASH_FILE_MODE_SEGMENT)
     || (!(predecessor->flags & LSMASH_FILE_MODE_MEDIA) && !(predecessor->flags & LSMASH_FILE_MODE_INITIALIZATION)) )
        return LSMASH_ERR_FUNCTION_PARAM;
    int ret = isom_finish_final_fragment_movie( predecessor, remux );
    if( ret < 0 )
        return ret;
    if( predecessor->flags & LSMASH_FILE_MODE_INITIALIZATION )
    {
        if( predecessor->initializer != predecessor )
            return LSMASH_ERR_INVALID_DATA;
        successor->initializer = predecessor;
    }
    else
        successor->initializer = predecessor->initializer;
    isom_styp_t *styp = (isom_styp_t *)lsmash_list_get_entry_data( &successor->styp_list, 1 );
    if( LSMASH_IS_NON_EXISTING_BOX( styp ) )
    {
        ret = isom_set_brands( successor, 0, 0, NULL, 0 );
        if( ret < 0 )
            return LSMASH_ERR_NAMELESS;
    }
    successor->fragment_count = predecessor->fragment_count;
    root->file = successor;
    return 0;
}

/*****************************************************************************
 * chapter.c
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
#include <ctype.h>

#include "box.h"

#define CHAPTER_BUFSIZE 512
#define UTF8_BOM "\xEF\xBB\xBF"
#define UTF8_BOM_LENGTH 3

static int isom_get_start_time( char *chap_time, isom_chapter_entry_t *data )
{
    uint64_t hh, mm;
    double ss;
    if( sscanf( chap_time, "%"SCNu64":%2"SCNu64":%lf", &hh, &mm, &ss ) != 3 )
        return LSMASH_ERR_INVALID_DATA;
    /* check overflow */
    if( hh >= 5124095
     || mm >= 60
     || ss >= 60 )
        return LSMASH_ERR_INVALID_DATA;
    /* 1ns timescale */
    data->start_time = (hh * 3600 + mm * 60 + ss) * 1e9;
    return 0;
}

static int isom_lumber_line( char *buff, int bufsize, FILE *chapter  )
{
    char *tail;
    /* remove newline codes and skip empty line */
    do
    {
        if( fgets( buff, bufsize, chapter ) == NULL )
            return LSMASH_ERR_NAMELESS;
        tail = &buff[ strlen( buff ) - 1 ];
        while( tail >= buff && (*tail == '\n' || *tail == '\r') )
            *tail-- = '\0';
    } while( tail < buff );
    return 0;
}

static int isom_read_simple_chapter( FILE *chapter, isom_chapter_entry_t *data )
{
    char buff[CHAPTER_BUFSIZE];
    /* get start_time */
    if( isom_lumber_line( buff, CHAPTER_BUFSIZE, chapter ) < 0 )
        return LSMASH_ERR_NAMELESS;
    char *chapter_time = strchr( buff, '=' );   /* find separator */
    if( !chapter_time++ )
        return LSMASH_ERR_INVALID_DATA;
    if( isom_get_start_time( chapter_time, data ) < 0 )
        return LSMASH_ERR_INVALID_DATA;
    if( isom_lumber_line( buff, CHAPTER_BUFSIZE, chapter ) < 0 )    /* get chapter_name */
        return LSMASH_ERR_NAMELESS;
    char *chapter_name = strchr( buff, '=' );   /* find separator */
    if( !chapter_name++ )
        return LSMASH_ERR_INVALID_DATA;
    int len = LSMASH_MIN( 255, strlen( chapter_name ) );    /* We support length of chapter_name up to 255 */
    data->chapter_name = (char *)lsmash_malloc( len + 1 );
    if( !data->chapter_name )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( data->chapter_name, chapter_name, len );
    data->chapter_name[len] = '\0';
    return 0;
}

static int isom_read_minimum_chapter( FILE *chapter, isom_chapter_entry_t *data )
{
    char buff[CHAPTER_BUFSIZE];
    if( isom_lumber_line( buff, CHAPTER_BUFSIZE, chapter ) < 0 )    /* read newline */
        return LSMASH_ERR_NAMELESS;
    char *p_buff = &buff[ !memcmp( buff, UTF8_BOM, UTF8_BOM_LENGTH ) ? UTF8_BOM_LENGTH : 0 ];   /* BOM detection */
    if( isom_get_start_time( p_buff, data ) < 0 )   /* get start_time */
        return LSMASH_ERR_INVALID_DATA;
    /* get chapter_name */
    char *chapter_name = strchr( buff, ' ' );   /* find separator */
    if( !chapter_name++ )
        return LSMASH_ERR_INVALID_DATA;
    int len = LSMASH_MIN( 255, strlen( chapter_name ) );    /* We support length of chapter_name up to 255 */
    data->chapter_name = (char *)lsmash_malloc( len + 1 );
    if( !data->chapter_name )
        return LSMASH_ERR_MEMORY_ALLOC;
    memcpy( data->chapter_name, chapter_name, len );
    data->chapter_name[len] = '\0';
    return 0;
}

typedef int (*fn_get_chapter_data)( FILE *, isom_chapter_entry_t * );

static fn_get_chapter_data isom_check_chap_line( char *file_name )
{
    FILE *fp = lsmash_fopen( file_name, "rb" );
    if( !fp )
    {
        lsmash_log( NULL, LSMASH_LOG_ERROR, "failed to open the chapter file \"%s\".\n", file_name );
        return NULL;
    }
    char buff[CHAPTER_BUFSIZE];
    fn_get_chapter_data fnc = NULL;
    if( fgets( buff, CHAPTER_BUFSIZE, fp ) != NULL )
    {
        char *p_buff = &buff[ !memcmp( buff, UTF8_BOM, UTF8_BOM_LENGTH ) ? UTF8_BOM_LENGTH : 0 ];   /* BOM detection */
        if( !strncmp( p_buff, "CHAPTER", 7 ) )
            fnc = isom_read_simple_chapter;
        else if( isdigit( (unsigned char)p_buff[0] ) && isdigit( (unsigned char)p_buff[1] ) && p_buff[2] == ':'
              && isdigit( (unsigned char)p_buff[3] ) && isdigit( (unsigned char)p_buff[4] ) && p_buff[5] == ':' )
            fnc = isom_read_minimum_chapter;
        else
            lsmash_log( NULL, LSMASH_LOG_ERROR, "the chapter file is malformed.\n" );
    }
    fclose( fp );
    return fnc;
}

static int isom_add_chpl_entry( isom_chpl_t *chpl, isom_chapter_entry_t *chap_data )
{
    assert( LSMASH_IS_EXISTING_BOX( chpl ) );
    if( !chap_data->chapter_name || !chpl->list )
        return LSMASH_ERR_FUNCTION_PARAM;
    isom_chpl_entry_t *data = lsmash_malloc( sizeof(isom_chpl_entry_t) );
    if( !data )
        return LSMASH_ERR_MEMORY_ALLOC;
    data->start_time          = chap_data->start_time;
    data->chapter_name_length = strlen( chap_data->chapter_name );
    data->chapter_name        = (char *)lsmash_malloc( data->chapter_name_length + 1 );
    if( !data->chapter_name )
    {
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    memcpy( data->chapter_name, chap_data->chapter_name, data->chapter_name_length );
    data->chapter_name[ data->chapter_name_length ] = '\0';
    if( lsmash_list_add_entry( chpl->list, data ) < 0 )
    {
        lsmash_free( data->chapter_name );
        lsmash_free( data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

int lsmash_set_tyrant_chapter( lsmash_root_t *root, char *file_name, int add_bom )
{
    if( isom_check_initializer_present( root ) < 0 )
        goto error_message;
    /* This function should be called after updating of the latest movie duration. */
    lsmash_file_t *file = root->file;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd )
     || file->moov->mvhd->timescale == 0
     || file->moov->mvhd->duration  == 0 )
        goto error_message;
    /* check each line format */
    fn_get_chapter_data fnc = isom_check_chap_line( file_name );
    if( !fnc )
        goto error_message;
    FILE *chapter = lsmash_fopen( file_name, "rb" );
    if( !chapter )
    {
        lsmash_log( NULL, LSMASH_LOG_ERROR, "failed to open the chapter file \"%s\".\n", file_name );
        goto error_message;
    }
    if( (LSMASH_IS_NON_EXISTING_BOX( file->moov->udta )       && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( file->moov ) ))
     || (LSMASH_IS_NON_EXISTING_BOX( file->moov->udta->chpl ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_chpl( file->moov->udta ) )) )
        goto fail;
    file->moov->udta->chpl->version = 1;    /* version = 1 is popular. */
    isom_chapter_entry_t data = { 0 };
    while( !fnc( chapter, &data ) )
    {
        if( add_bom )
        {
            char *chapter_name_with_bom = (char *)lsmash_malloc( strlen( data.chapter_name ) + 1 + UTF8_BOM_LENGTH );
            if( !chapter_name_with_bom )
                goto fail2;
            sprintf( chapter_name_with_bom, "%s%s", UTF8_BOM, data.chapter_name );
            lsmash_free( data.chapter_name );
            data.chapter_name = chapter_name_with_bom;
        }
        data.start_time = (data.start_time + 50) / 100;    /* convert to 100ns unit */
        if( data.start_time / 1e7 > (double)file->moov->mvhd->duration / file->moov->mvhd->timescale )
        {
            lsmash_log( NULL, LSMASH_LOG_WARNING,
                        "a chapter point exceeding the actual duration detected."
                        "This chapter point and the following ones (if any) will be cut off.\n" );
            lsmash_free( data.chapter_name );
            break;
        }
        if( isom_add_chpl_entry( file->moov->udta->chpl, &data ) < 0 )
            goto fail2;
        lsmash_freep( &data.chapter_name );
    }
    fclose( chapter );
    return 0;
fail2:
    lsmash_free( data.chapter_name );
fail:
    fclose( chapter );
error_message:
    lsmash_log( NULL, LSMASH_LOG_ERROR, "failed to set chapter list.\n" );
    return LSMASH_ERR_NAMELESS;
}

int lsmash_create_reference_chapter_track( lsmash_root_t *root, uint32_t track_ID, char *file_name )
{
    if( isom_check_initializer_present( root ) < 0 )
        goto error_message;
    lsmash_file_t *file = root->file;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
        goto error_message;
    if( file->forbid_tref || (!file->qt_compatible && !file->itunes_movie) )
    {
        lsmash_log( NULL, LSMASH_LOG_ERROR, "reference chapter is not available for this file.\n" );
        goto error_message;
    }
    FILE *chapter = NULL;       /* shut up 'uninitialized' warning */
    /* Create a Track Reference Box. */
    isom_trak_t *trak = isom_get_trak( file, track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( trak ) )
    {
        lsmash_log( NULL, LSMASH_LOG_ERROR, "the specified track ID to apply the chapter doesn't exist.\n" );
        goto error_message;
    }
    if( LSMASH_IS_NON_EXISTING_BOX( trak->tref ) && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_tref( trak ) ) )
        goto error_message;
    /* Create a track_ID for a new chapter track. */
    uint32_t *id = (uint32_t *)lsmash_malloc( sizeof(uint32_t) );
    if( !id )
        goto error_message;
    uint32_t chapter_track_ID = *id = file->moov->mvhd->next_track_ID;
    /* Create a Track Reference Type Box. */
    isom_tref_type_t *chap = isom_add_track_reference_type( trak->tref, QT_TREF_TYPE_CHAP );
    if( LSMASH_IS_NON_EXISTING_BOX( chap ) )
    {
        lsmash_free( id );
        goto error_message;
    }
    chap->ref_count = 1;
    chap->track_ID  = id;
    /* Create a reference chapter track. */
    if( chapter_track_ID != lsmash_create_track( root, ISOM_MEDIA_HANDLER_TYPE_TEXT_TRACK ) )
        goto error_message;
    /* Set track parameters. */
    lsmash_track_parameters_t track_param;
    lsmash_initialize_track_parameters( &track_param );
    track_param.mode = ISOM_TRACK_IN_MOVIE | ISOM_TRACK_IN_PREVIEW;
    if( lsmash_set_track_parameters( root, chapter_track_ID, &track_param ) < 0 )
        goto fail;
    /* Set media parameters. */
    uint64_t media_timescale = lsmash_get_media_timescale( root, track_ID );
    if( media_timescale == 0 )
        goto fail;
    lsmash_media_parameters_t media_param;
    lsmash_initialize_media_parameters( &media_param );
    media_param.timescale    = media_timescale;
    media_param.ISO_language = file->max_3gpp_version >= 6 || file->itunes_movie ? ISOM_LANGUAGE_CODE_UNDEFINED : 0;
    media_param.MAC_language = 0;
    if( lsmash_set_media_parameters( root, chapter_track_ID, &media_param ) < 0 )
        goto fail;
    /* Create a sample description. */
    lsmash_codec_type_t sample_type = file->max_3gpp_version >= 6 || file->itunes_movie
                                    ? ISOM_CODEC_TYPE_TX3G_TEXT
                                    : QT_CODEC_TYPE_TEXT_TEXT;
    lsmash_summary_t summary = { .sample_type = sample_type, .data_ref_index = 1 };
    uint32_t sample_entry = lsmash_add_sample_entry( root, chapter_track_ID, &summary );
    if( sample_entry == 0 )
        goto fail;
    /* Check each line format. */
    fn_get_chapter_data fnc = isom_check_chap_line( file_name );
    if( !fnc )
        goto fail;
    /* Open chapter format file. */
    chapter = lsmash_fopen( file_name, "rb" );
    if( !chapter )
    {
        lsmash_log( NULL, LSMASH_LOG_ERROR, "failed to open the chapter file \"%s\".\n", file_name );
        goto fail;
    }
    /* Parse the file and write text samples. */
    isom_chapter_entry_t data;
    while( !fnc( chapter, &data ) )
    {
        /* set start_time */
        data.start_time = data.start_time * 1e-9 * media_timescale + 0.5;
        /* write a text sample here */
        int is_qt_text = lsmash_check_codec_type_identical( sample_type, QT_CODEC_TYPE_TEXT_TEXT );
        uint16_t name_length = strlen( data.chapter_name );
        lsmash_sample_t *sample = lsmash_create_sample( 2 + name_length + 12 * is_qt_text );
        if( !sample )
        {
            lsmash_free( data.chapter_name );
            goto fail;
        }
        sample->data[0] = (name_length >> 8) & 0xff;
        sample->data[1] =  name_length       & 0xff;
        memcpy( sample->data + 2, data.chapter_name, name_length );
        if( is_qt_text )
        {
            /* QuickTime Player requires Text Encoding Attribute Box ('encd') if media language is ISO language codes : undefined.
             * Also this box can avoid garbling if the QuickTime text sample is encoded by Unicode characters.
             * Note: 3GPP Timed Text supports only UTF-8 or UTF-16, so this box isn't needed. */
            static const uint8_t encd[12] =
                {
                    0x00, 0x00, 0x00, 0x0C,     /* size: 12 */
                    0x65, 0x6E, 0x63, 0x64,     /* type: 'encd' */
                    0x00, 0x00, 0x01, 0x00      /* Unicode Encoding */
                };
            memcpy( sample->data + 2 + name_length, encd, 12 );
        }
        sample->dts           = data.start_time;
        sample->cts           = data.start_time;
        sample->prop.ra_flags = ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC;
        sample->index         = sample_entry;
        if( lsmash_append_sample( root, chapter_track_ID, sample ) < 0 )
        {
            lsmash_free( data.chapter_name );
            goto fail;
        }
        lsmash_freep( &data.chapter_name );
    }
    if( lsmash_flush_pooled_samples( root, chapter_track_ID, 0 ) < 0 )
        goto fail;
    isom_trak_t *chapter_trak = isom_get_trak( file, chapter_track_ID );
    if( LSMASH_IS_NON_EXISTING_BOX( chapter_trak ) )
        goto fail;
    fclose( chapter );
    chapter_trak->is_chapter       = 1;
    chapter_trak->related_track_ID = track_ID;
    return 0;
fail:
    if( chapter )
        fclose( chapter );
    /* Remove chapter track reference. */
    if( trak->tref->ref_list.tail )
        isom_remove_box_by_itself( trak->tref->ref_list.tail->data );
    if( trak->tref->ref_list.entry_count == 0 )
        isom_remove_box_by_itself( trak->tref );
    /* Remove the reference chapter track attached at tail of the list. */
    if( file->moov->trak_list.tail )
        isom_remove_box_by_itself( file->moov->trak_list.tail->data );
error_message:
    lsmash_log( NULL, LSMASH_LOG_ERROR, "failed to set reference chapter.\n" );
    return LSMASH_ERR_NAMELESS;
}

uint32_t lsmash_count_tyrant_chapter( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0
     && root->file->initializer->moov->udta->chpl->list )
        return root->file->initializer->moov->udta->chpl->list->entry_count;
    return 0;
}

char *lsmash_get_tyrant_chapter( lsmash_root_t *root, uint32_t index, double *timestamp )
{
    if( isom_check_initializer_present( root ) < 0 )
        return NULL;
    lsmash_file_t *file = root->file->initializer;
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd )
     || LSMASH_IS_NON_EXISTING_BOX( file->moov->udta->chpl ) )
        return NULL;
    isom_chpl_t *chpl = file->moov->udta->chpl;
    isom_chpl_entry_t *data = (isom_chpl_entry_t *)lsmash_list_get_entry_data( chpl->list, index );
    if( !data )
        return NULL;
    double timescale = chpl->version ? 10000000.0 : file->moov->mvhd->timescale;
    *timestamp = data->start_time / timescale;
    if( !memcmp( data->chapter_name, UTF8_BOM, UTF8_BOM_LENGTH ) )
        return data->chapter_name + UTF8_BOM_LENGTH;
    return data->chapter_name;
}


int lsmash_print_chapter_list( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0
     || !(root->file->initializer->flags & LSMASH_FILE_MODE_READ) )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    if( LSMASH_IS_EXISTING_BOX( file->moov->udta->chpl ) )
    {
        isom_chpl_t *chpl = file->moov->udta->chpl;
        uint32_t timescale;
        if( chpl->version == 0 )
        {
            if( LSMASH_IS_NON_EXISTING_BOX( file->moov->mvhd ) )
                return LSMASH_ERR_NAMELESS;
            timescale = file->moov->mvhd->timescale;
        }
        else
            timescale = 10000000;
        uint32_t i = 1;
        for( lsmash_entry_t *entry = chpl->list->head; entry; entry = entry->next )
        {
            isom_chpl_entry_t *data = (isom_chpl_entry_t *)entry->data;
            int64_t start_time = data->start_time / timescale;
            int hh =  start_time / 3600;
            int mm = (start_time /   60) % 60;
            int ss =  start_time         % 60;
            int ms = ((data->start_time / (double)timescale) - hh * 3600 - mm * 60 - ss) * 1e3 + 0.5;
            if( !memcmp( data->chapter_name, UTF8_BOM, UTF8_BOM_LENGTH ) )    /* detect BOM */
            {
                data->chapter_name += UTF8_BOM_LENGTH;
#ifdef _WIN32
                if( i == 1 )
                    printf( UTF8_BOM );    /* add BOM on Windows */
#endif
            }
            printf( "CHAPTER%02"PRIu32"=%02d:%02d:%02d.%03d\n", i, hh, mm, ss, ms );
            printf( "CHAPTER%02"PRIu32"NAME=%s\n", i++, data->chapter_name );
        }
        return 0;
    }
    lsmash_log( NULL, LSMASH_LOG_ERROR, "this file doesn't have a chapter list.\n" );
    return LSMASH_ERR_NAMELESS;
}

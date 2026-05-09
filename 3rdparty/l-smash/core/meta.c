/*****************************************************************************
 * meta.c
 *****************************************************************************
 * Copyright (C) 2012-2017 L-SMASH project
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
#include <stdlib.h>

#include "box.h"
#include "box_default.h"

static isom_data_t *isom_add_metadata( lsmash_file_t *file,
                                       lsmash_itunes_metadata_item item,
                                       char *meaning_string, char *name_string )
{
    assert( LSMASH_IS_EXISTING_BOX( file->moov ) );
    if( ((item == ITUNES_METADATA_ITEM_CUSTOM) && (!meaning_string || !meaning_string[0]) )
     || (LSMASH_IS_NON_EXISTING_BOX( file->moov->udta )
      && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_udta( file->moov ) ))
     || (LSMASH_IS_NON_EXISTING_BOX( file->moov->udta->meta )
      && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_meta( file->moov->udta ) ))
     || (LSMASH_IS_NON_EXISTING_BOX( file->moov->udta->meta->ilst )
      && LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_ilst( file->moov->udta->meta ) )) )
        return isom_non_existing_data();
    if( LSMASH_IS_NON_EXISTING_BOX( file->moov->udta->meta->hdlr ) )
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_hdlr( file->moov->udta->meta ) )
         || isom_setup_handler_reference( file->moov->udta->meta->hdlr, ISOM_META_HANDLER_TYPE_ITUNES_METADATA ) < 0 )
            return isom_non_existing_data();
    }
    isom_ilst_t *ilst = file->moov->udta->meta->ilst;
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_metaitem( ilst, item ) ) )
        return isom_non_existing_data();
    isom_metaitem_t *metaitem = (isom_metaitem_t *)ilst->metaitem_list.tail->data;
    if( item == ITUNES_METADATA_ITEM_CUSTOM )
    {
        if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_mean( metaitem ) ) )
            goto fail;
        isom_mean_t *mean = metaitem->mean;
        mean->meaning_string_length = strlen( meaning_string );    /* No null terminator */
        mean->meaning_string        = lsmash_memdup( meaning_string, mean->meaning_string_length );
        if( !mean->meaning_string )
            goto fail;
        if( name_string && name_string[0] )
        {
            if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_name( metaitem ) ) )
                goto fail;
            isom_name_t *name = metaitem->name;
            name->name_length = strlen( name_string );    /* No null terminator */
            name->name        = lsmash_memdup( name_string, name->name_length );
            if( !name->name )
                goto fail;
        }
    }
    if( LSMASH_IS_BOX_ADDITION_FAILURE( isom_add_data( metaitem ) ) )
        goto fail;
    return metaitem->data;
fail:
    isom_remove_box_by_itself( metaitem );
    return isom_non_existing_data();
}

static int isom_set_itunes_metadata_string( lsmash_file_t *file,
                                            lsmash_itunes_metadata_item item,
                                            lsmash_itunes_metadata_value_t value, char *meaning, char *name )
{
    uint32_t value_length = strlen( value.string );
    if( item == ITUNES_METADATA_ITEM_DESCRIPTION && value_length > 255 )
        item = ITUNES_METADATA_ITEM_LONG_DESCRIPTION;
    isom_data_t *data = isom_add_metadata( file, item, meaning, name );
    if( LSMASH_IS_NON_EXISTING_BOX( data ) )
        return LSMASH_ERR_NAMELESS;
    data->type_code    = ITUNES_METADATA_SUBTYPE_UTF8;
    data->value_length = value_length;      /* No null terminator */
    data->value        = lsmash_memdup( value.string, data->value_length );
    if( !data->value )
    {
        isom_ilst_t *ilst = file->moov->udta->meta->ilst;
        isom_remove_box_by_itself( ilst->metaitem_list.tail->data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_set_itunes_metadata_integer( lsmash_file_t *file,
                                             lsmash_itunes_metadata_item item,
                                             lsmash_itunes_metadata_value_t value, char *meaning, char *name )
{
    static const struct
    {
        lsmash_itunes_metadata_item item;
        int                         length;
    } metadata_code_type_table[] =
        {
            { ITUNES_METADATA_ITEM_EPISODE_GLOBAL_ID,          1 },
            { ITUNES_METADATA_ITEM_PREDEFINED_GENRE,           2 },
            { ITUNES_METADATA_ITEM_CONTENT_RATING,             1 },
            { ITUNES_METADATA_ITEM_MEDIA_TYPE,                 1 },
            { ITUNES_METADATA_ITEM_BEATS_PER_MINUTE,           2 },
            { ITUNES_METADATA_ITEM_TV_EPISODE,                 4 },
            { ITUNES_METADATA_ITEM_TV_SEASON,                  4 },
            { ITUNES_METADATA_ITEM_ITUNES_ACCOUNT_TYPE,        1 },
            { ITUNES_METADATA_ITEM_ITUNES_ARTIST_ID,           4 },
            { ITUNES_METADATA_ITEM_ITUNES_COMPOSER_ID,         4 },
            { ITUNES_METADATA_ITEM_ITUNES_CATALOG_ID,          4 },
            { ITUNES_METADATA_ITEM_ITUNES_TV_GENRE_ID,         4 },
            { ITUNES_METADATA_ITEM_ITUNES_PLAYLIST_ID,         8 },
            { ITUNES_METADATA_ITEM_ITUNES_COUNTRY_CODE,        4 },
            { ITUNES_METADATA_ITEM_CUSTOM,                     8 },
            { 0,                                               0 }
        };
    int i;
    for( i = 0; metadata_code_type_table[i].item; i++ )
        if( item == metadata_code_type_table[i].item )
            break;
    if( metadata_code_type_table[i].length == 0 )
        return LSMASH_ERR_NAMELESS;
    isom_data_t *data = isom_add_metadata( file, item, meaning, name );
    if( LSMASH_IS_NON_EXISTING_BOX( data ) )
        return LSMASH_ERR_NAMELESS;
    if( item == ITUNES_METADATA_ITEM_PREDEFINED_GENRE )
        data->type_code = ITUNES_METADATA_SUBTYPE_IMPLICIT;
    else
        data->type_code = ITUNES_METADATA_SUBTYPE_INTEGER;
    data->value_length = metadata_code_type_table[i].length;
    uint8_t temp[8];
    for( i = 0; i < data->value_length; i++ )
    {
        int shift = (data->value_length - i - 1) * 8;
        temp[i] = (value.integer >> shift) & 0xff;
    }
    data->value = lsmash_memdup( temp, data->value_length );
    if( !data->value )
    {
        isom_ilst_t *ilst = file->moov->udta->meta->ilst;
        isom_remove_box_by_itself( ilst->metaitem_list.tail->data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_set_itunes_metadata_boolean( lsmash_file_t *file,
                                             lsmash_itunes_metadata_item item,
                                             lsmash_itunes_metadata_value_t value, char *meaning, char *name )
{
    isom_data_t *data = isom_add_metadata( file, item, meaning, name );
    if( LSMASH_IS_NON_EXISTING_BOX( data ) )
        return LSMASH_ERR_NAMELESS;
    data->type_code = ITUNES_METADATA_SUBTYPE_INTEGER;
    data->value_length = 1;
    uint8_t temp = (uint8_t)value.boolean;
    data->value = lsmash_memdup( &temp, 1 );
    if( !data->value )
    {
        isom_ilst_t *ilst = file->moov->udta->meta->ilst;
        isom_remove_box_by_itself( ilst->metaitem_list.tail->data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

static int isom_set_itunes_metadata_binary( lsmash_file_t *file,
                                            lsmash_itunes_metadata_item item,
                                            lsmash_itunes_metadata_value_t value, char *meaning, char *name )
{
    isom_data_t *data = isom_add_metadata( file, item, meaning, name );
    if( LSMASH_IS_NON_EXISTING_BOX( data ) )
        return LSMASH_ERR_NAMELESS;
    switch( item )
    {
        case ITUNES_METADATA_ITEM_COVER_ART :
            if( value.binary.subtype != ITUNES_METADATA_SUBTYPE_JPEG
             && value.binary.subtype != ITUNES_METADATA_SUBTYPE_PNG
             && value.binary.subtype != ITUNES_METADATA_SUBTYPE_BMP )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        case ITUNES_METADATA_ITEM_DISC_NUMBER :
        case ITUNES_METADATA_ITEM_TRACK_NUMBER :
            value.binary.subtype = ITUNES_METADATA_SUBTYPE_IMPLICIT;
            break;
        default :
            break;
    }
    switch( value.binary.subtype )
    {
        case ITUNES_METADATA_SUBTYPE_UUID :
            if( value.binary.size != 16 )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        case ITUNES_METADATA_SUBTYPE_DURATION :
            if( value.binary.size != 4 )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        case ITUNES_METADATA_SUBTYPE_TIME :
            if( value.binary.size != 4 && value.binary.size != 8 )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        case ITUNES_METADATA_SUBTYPE_INTEGER :
            if( value.binary.size != 1 && value.binary.size != 2
             && value.binary.size != 3 && value.binary.size != 4
             && value.binary.size != 8 )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        case ITUNES_METADATA_SUBTYPE_RIAAPA :
            if( value.binary.size != 1 )
                return LSMASH_ERR_FUNCTION_PARAM;
            break;
        default :
            break;
    }
    data->type_code    = value.binary.subtype;
    data->value_length = value.binary.size;
    data->value        = lsmash_memdup( value.binary.data, value.binary.size );
    if( !data->value )
    {
        isom_ilst_t *ilst = file->moov->udta->meta->ilst;
        isom_remove_box_by_itself( ilst->metaitem_list.tail->data );
        return LSMASH_ERR_MEMORY_ALLOC;
    }
    return 0;
}

int lsmash_set_itunes_metadata( lsmash_root_t *root, lsmash_itunes_metadata_t metadata )
{
    if( isom_check_initializer_present( root ) < 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    static const struct
    {
        lsmash_itunes_metadata_item item;
        int (*func_set_itunes_metadata)( lsmash_file_t *, lsmash_itunes_metadata_item, lsmash_itunes_metadata_value_t, char *, char * );
    } itunes_metadata_function_mapping[] =
        {
            { ITUNES_METADATA_ITEM_ALBUM_NAME,                 isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ARTIST,                     isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_USER_COMMENT,               isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_RELEASE_DATE,               isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ENCODED_BY,                 isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_USER_GENRE,                 isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_GROUPING,                   isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_LYRICS,                     isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_TITLE,                      isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_TRACK_SUBTITLE,             isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ENCODING_TOOL,              isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_COMPOSER,                   isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ALBUM_ARTIST,               isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_PODCAST_CATEGORY,           isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_COPYRIGHT,                  isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_DESCRIPTION,                isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_GROUPING_DRAFT,             isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_PODCAST_KEYWORD,            isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_LONG_DESCRIPTION,           isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_PURCHASE_DATE,              isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_TV_EPISODE_ID,              isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_TV_NETWORK,                 isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_TV_SHOW_NAME,               isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_PURCHASE_ACCOUNT_ID, isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM,          isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ARTIST,         isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM_ARTIST,   isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_COMPOSER,       isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_NAME,           isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_SHOW,           isom_set_itunes_metadata_string },
            { ITUNES_METADATA_ITEM_EPISODE_GLOBAL_ID,          isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_PREDEFINED_GENRE,           isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_CONTENT_RATING,             isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_MEDIA_TYPE,                 isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_BEATS_PER_MINUTE,           isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_TV_EPISODE,                 isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_TV_SEASON,                  isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_ACCOUNT_TYPE,        isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_ARTIST_ID,           isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_COMPOSER_ID,         isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_CATALOG_ID,          isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_TV_GENRE_ID,         isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_PLAYLIST_ID,         isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_ITUNES_COUNTRY_CODE,        isom_set_itunes_metadata_integer },
            { ITUNES_METADATA_ITEM_DISC_COMPILATION,           isom_set_itunes_metadata_boolean },
            { ITUNES_METADATA_ITEM_HIGH_DEFINITION_VIDEO,      isom_set_itunes_metadata_boolean },
            { ITUNES_METADATA_ITEM_PODCAST,                    isom_set_itunes_metadata_boolean },
            { ITUNES_METADATA_ITEM_GAPLESS_PLAYBACK,           isom_set_itunes_metadata_boolean },
            { ITUNES_METADATA_ITEM_COVER_ART,                  isom_set_itunes_metadata_binary },
            { ITUNES_METADATA_ITEM_DISC_NUMBER,                isom_set_itunes_metadata_binary },
            { ITUNES_METADATA_ITEM_TRACK_NUMBER,               isom_set_itunes_metadata_binary },
            { 0,                                               NULL }
        };
    lsmash_file_t *file = root->file;
    for( int i = 0; itunes_metadata_function_mapping[i].func_set_itunes_metadata; i++ )
        if( metadata.item == itunes_metadata_function_mapping[i].item )
            return itunes_metadata_function_mapping[i].func_set_itunes_metadata( file, metadata.item, metadata.value, metadata.meaning, metadata.name );
    if( metadata.item == ITUNES_METADATA_ITEM_CUSTOM )
        switch( metadata.type )
        {
            case ITUNES_METADATA_TYPE_STRING :
                return isom_set_itunes_metadata_string( file, metadata.item, metadata.value, metadata.meaning, metadata.name );
            case ITUNES_METADATA_TYPE_INTEGER :
                return isom_set_itunes_metadata_integer( file, metadata.item, metadata.value, metadata.meaning, metadata.name );
            case ITUNES_METADATA_TYPE_BOOLEAN :
                return isom_set_itunes_metadata_boolean( file, metadata.item, metadata.value, metadata.meaning, metadata.name );
            case ITUNES_METADATA_TYPE_BINARY :
                return isom_set_itunes_metadata_binary( file, metadata.item, metadata.value, metadata.meaning, metadata.name );
            default :
                break;
        }
    return LSMASH_ERR_FUNCTION_PARAM;
}

static lsmash_itunes_metadata_type isom_get_itunes_metadata_type( lsmash_itunes_metadata_item item )
{
    static const struct
    {
        lsmash_itunes_metadata_item item;
        lsmash_itunes_metadata_type type;
    } itunes_metadata_item_type_mapping[] =
        {
            { ITUNES_METADATA_ITEM_ALBUM_NAME,                 ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ARTIST,                     ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_USER_COMMENT,               ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_RELEASE_DATE,               ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ENCODED_BY,                 ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_USER_GENRE,                 ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_GROUPING,                   ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_LYRICS,                     ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_TITLE,                      ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_TRACK_SUBTITLE,             ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ENCODING_TOOL,              ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_COMPOSER,                   ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ALBUM_ARTIST,               ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_PODCAST_CATEGORY,           ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_COPYRIGHT,                  ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_DESCRIPTION,                ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_GROUPING_DRAFT,             ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_PODCAST_KEYWORD,            ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_LONG_DESCRIPTION,           ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_PURCHASE_DATE,              ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_TV_EPISODE_ID,              ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_TV_NETWORK,                 ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_TV_SHOW_NAME,               ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_PURCHASE_ACCOUNT_ID, ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM,          ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ARTIST,         ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_ALBUM_ARTIST,   ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_COMPOSER,       ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_NAME,           ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_ITUNES_SORT_SHOW,           ITUNES_METADATA_TYPE_STRING },
            { ITUNES_METADATA_ITEM_EPISODE_GLOBAL_ID,          ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_PREDEFINED_GENRE,           ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_CONTENT_RATING,             ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_MEDIA_TYPE,                 ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_BEATS_PER_MINUTE,           ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_TV_EPISODE,                 ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_TV_SEASON,                  ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_ACCOUNT_TYPE,        ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_ARTIST_ID,           ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_COMPOSER_ID,         ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_CATALOG_ID,          ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_TV_GENRE_ID,         ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_PLAYLIST_ID,         ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_ITUNES_COUNTRY_CODE,        ITUNES_METADATA_TYPE_INTEGER },
            { ITUNES_METADATA_ITEM_DISC_COMPILATION,           ITUNES_METADATA_TYPE_BOOLEAN },
            { ITUNES_METADATA_ITEM_HIGH_DEFINITION_VIDEO,      ITUNES_METADATA_TYPE_BOOLEAN },
            { ITUNES_METADATA_ITEM_PODCAST,                    ITUNES_METADATA_TYPE_BOOLEAN },
            { ITUNES_METADATA_ITEM_GAPLESS_PLAYBACK,           ITUNES_METADATA_TYPE_BOOLEAN },
            { ITUNES_METADATA_ITEM_COVER_ART,                  ITUNES_METADATA_TYPE_BINARY },
            { ITUNES_METADATA_ITEM_DISC_NUMBER,                ITUNES_METADATA_TYPE_BINARY },
            { ITUNES_METADATA_ITEM_TRACK_NUMBER,               ITUNES_METADATA_TYPE_BINARY },
            { 0,                                               ITUNES_METADATA_TYPE_NONE }
        };
    for( int i = 0; itunes_metadata_item_type_mapping[i].type != ITUNES_METADATA_TYPE_NONE; i++ )
        if( item == itunes_metadata_item_type_mapping[i].item )
            return itunes_metadata_item_type_mapping[i].type;
    return ITUNES_METADATA_TYPE_NONE;
}

int lsmash_get_itunes_metadata( lsmash_root_t *root, uint32_t metadata_number, lsmash_itunes_metadata_t *metadata )
{
    if( isom_check_initializer_present( root ) < 0 || !metadata )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_file_t *file = root->file->initializer;
    if( !file->moov->udta->meta->ilst )
        return LSMASH_ERR_NAMELESS;
    isom_ilst_t *ilst = file->moov->udta->meta->ilst;
    isom_metaitem_t *metaitem = (isom_metaitem_t *)lsmash_list_get_entry_data( &ilst->metaitem_list, metadata_number );
    if( LSMASH_IS_NON_EXISTING_BOX( metaitem )
     || LSMASH_IS_NON_EXISTING_BOX( metaitem->data )
     || metaitem->data->value        == NULL
     || metaitem->data->value_length == 0 )
        return LSMASH_ERR_NAMELESS;
    metadata->item = metaitem->type.fourcc;
    metadata->type = isom_get_itunes_metadata_type( metadata->item );
    /* Get 'meaning'. */
    int err = LSMASH_ERR_MEMORY_ALLOC;
    isom_mean_t *mean = metaitem->mean;
    if( LSMASH_IS_NON_EXISTING_BOX( mean ) )
    {
        uint8_t *temp = lsmash_malloc( mean->meaning_string_length + 1 );
        if( !temp )
            goto fail;
        memcpy( temp, mean->meaning_string, mean->meaning_string_length );
        temp[ mean->meaning_string_length ] = 0;
        metadata->meaning = (char *)temp;
    }
    else
        metadata->meaning = NULL;
    /* Get 'name'. */
    isom_name_t *name = metaitem->name;
    if( LSMASH_IS_NON_EXISTING_BOX( name ) )
    {
        uint8_t *temp = lsmash_malloc( name->name_length + 1 );
        if( !temp )
            goto fail;
        memcpy( temp, name->name, name->name_length );
        temp[ name->name_length ] = 0;
        metadata->name = (char *)temp;
    }
    else
        metadata->name = NULL;
    /* Get 'value'. */
    isom_data_t *data = metaitem->data;
    switch( metadata->type )
    {
        case ITUNES_METADATA_TYPE_STRING :
        {
            uint8_t *temp = lsmash_malloc( data->value_length + 1 );
            if( !temp )
                goto fail;
            memcpy( temp, data->value, data->value_length );
            temp[ data->value_length ] = 0;
            metadata->value.string = (char *)temp;
            break;
        }
        case ITUNES_METADATA_TYPE_INTEGER :
            if( data->value_length > 8 )
            {
                err = LSMASH_ERR_INVALID_DATA;
                goto fail;
            }
            metadata->value.integer = 0;
            for( uint32_t i = 0; i < data->value_length; i++ )
            {
                int shift = (data->value_length - i - 1) * 8;
                metadata->value.integer |= (uint64_t)data->value[i] << shift;
            }
            break;
        case ITUNES_METADATA_TYPE_BOOLEAN :
            metadata->value.boolean = !!data->value[0];
            break;
        default :
            metadata->type                 = ITUNES_METADATA_TYPE_BINARY;
            metadata->value.binary.subtype = data->type_code;
            metadata->value.binary.size    = data->value_length;
            metadata->value.binary.data    = lsmash_memdup( data->value, data->value_length );
            if( !metadata->value.binary.data )
                goto fail;
            break;
    }
    return 0;
fail:
    lsmash_freep( &metadata->meaning );
    lsmash_freep( &metadata->name );
    return err;
}

uint32_t lsmash_count_itunes_metadata( lsmash_root_t *root )
{
    if( isom_check_initializer_present( root ) < 0
     || LSMASH_IS_NON_EXISTING_BOX( root->file->initializer->moov->udta->meta->ilst ) )
        return 0;
    return root->file->initializer->moov->udta->meta->ilst->metaitem_list.entry_count;
}

void lsmash_cleanup_itunes_metadata( lsmash_itunes_metadata_t *metadata )
{
    if( !metadata )
        return;
    lsmash_freep( &metadata->meaning );
    lsmash_freep( &metadata->name );
    if( metadata->type == ITUNES_METADATA_TYPE_STRING )
        lsmash_freep( &metadata->value.string );
    else if( metadata->type == ITUNES_METADATA_TYPE_BINARY )
        lsmash_freep( &metadata->value.binary.data );
}

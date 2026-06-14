/*****************************************************************************
 * list.c
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

#include "internal.h" /* must be placed first */

#include <string.h>

static void lsmash_list_clear
(
    lsmash_entry_list_t *list
)
{
    list->head                 = NULL;
    list->tail                 = NULL;
    list->last_accessed_entry  = NULL;
    list->last_accessed_number = 0;
    list->entry_count          = 0;
    list->eliminator           = NULL;
}

void lsmash_list_init_orig
(
    lsmash_entry_list_t         *list,
    lsmash_entry_data_eliminator eliminator
)
{
    assert( eliminator != NULL );
    list->head                 = NULL;
    list->tail                 = NULL;
    list->last_accessed_entry  = NULL;
    list->last_accessed_number = 0;
    list->entry_count          = 0;
    list->eliminator           = eliminator;
}

lsmash_entry_list_t *lsmash_list_create_orig
(
    lsmash_entry_data_eliminator eliminator
)
{
    lsmash_entry_list_t *list = lsmash_malloc( sizeof(lsmash_entry_list_t) );
    if( !list )
        return NULL;
    lsmash_list_init( list, eliminator );
    return list;
}

void lsmash_list_destroy
(
    lsmash_entry_list_t *list
)
{
    lsmash_list_remove_entries( list );
    lsmash_free( list );
}

int lsmash_list_add_entry
(
    lsmash_entry_list_t *list,
    void                *data
)
{
    if( !list )
        return LSMASH_ERR_FUNCTION_PARAM;
    lsmash_entry_t *entry = lsmash_malloc( sizeof(lsmash_entry_t) );
    if( !entry )
        return LSMASH_ERR_MEMORY_ALLOC;
    entry->next = NULL;
    entry->prev = list->tail;
    entry->data = data;
    if( list->head )
        list->tail->next = entry;
    else
        list->head = entry;
    list->tail = entry;
    list->entry_count += 1;
    return 0;
}

int lsmash_list_remove_entry_direct
(
    lsmash_entry_list_t *list,
    lsmash_entry_t      *entry
)
{
    if( !list || !entry )
        return LSMASH_ERR_FUNCTION_PARAM;
    assert( !entry->data || list->eliminator );
    lsmash_entry_t *next = entry->next;
    lsmash_entry_t *prev = entry->prev;
    if( entry == list->head )
        list->head = next;
    else
        prev->next = next;
    if( entry == list->tail )
        list->tail = prev;
    else
        next->prev = prev;
    if( entry->data )
        list->eliminator( entry->data );
    if( entry == list->last_accessed_entry )
    {
        if( next )
            list->last_accessed_entry = next;
        else if( prev )
        {
            list->last_accessed_entry   = prev;
            list->last_accessed_number -= 1;
        }
        else
        {
            list->last_accessed_entry  = NULL;
            list->last_accessed_number = 0;
        }
    }
    else
    {
        /* We can't know the current entry number immediately,
         * so discard the last accessed entry info because time is wasted to know it. */
        list->last_accessed_entry  = NULL;
        list->last_accessed_number = 0;
    }
    lsmash_free( entry );
    list->entry_count -= 1;
    return 0;
}

int lsmash_list_remove_entry
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
)
{
    lsmash_entry_t *entry = lsmash_list_get_entry( list, entry_number );
    return lsmash_list_remove_entry_direct( list, entry );
}

int lsmash_list_remove_entry_tail
(
    lsmash_entry_list_t *list
)
{
    return lsmash_list_remove_entry_direct( list, list->tail );
}

void lsmash_list_remove_entries
(
    lsmash_entry_list_t *list
)
{
    if( !list )
        return;
    /* Note that it's valid that list contain no entries or no data to be eliminated. */
    for( lsmash_entry_t *entry = list->head; entry; )
    {
        lsmash_entry_t *next = entry->next;
        if( entry->data )
            list->eliminator( entry->data );
        lsmash_free( entry );
        entry = next;
    }
    lsmash_entry_data_eliminator eliminator = list->eliminator;
    lsmash_list_clear( list );
    list->eliminator = eliminator;
}

void lsmash_list_move_entries
(
    lsmash_entry_list_t *dst,
    lsmash_entry_list_t *src
)
{
    *dst = *src;
    lsmash_entry_data_eliminator eliminator = src->eliminator;
    lsmash_list_clear( src );
    src->eliminator = eliminator;
}

lsmash_entry_t *lsmash_list_get_entry
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
)
{
    if( !list || !entry_number || entry_number > list->entry_count )
        return NULL;
    int shortcut = 1;
    lsmash_entry_t *entry = NULL;
    if( list->last_accessed_entry )
    {
        if( entry_number == list->last_accessed_number )
            entry = list->last_accessed_entry;
        else if( entry_number == list->last_accessed_number + 1 )
            entry = list->last_accessed_entry->next;
        else if( entry_number == list->last_accessed_number - 1 )
            entry = list->last_accessed_entry->prev;
        else
            shortcut = 0;
    }
    else
        shortcut = 0;
    if( !shortcut )
    {
        if( entry_number <= (list->entry_count >> 1) )
        {
            /* Look for from the head. */
            uint32_t distance_plus_one = entry_number;
            for( entry = list->head; entry && --distance_plus_one; entry = entry->next );
        }
        else
        {
            /* Look for from the tail. */
            uint32_t distance = list->entry_count - entry_number;
            for( entry = list->tail; entry && distance--; entry = entry->prev );
        }
    }
    if( entry )
    {
        list->last_accessed_entry  = entry;
        list->last_accessed_number = entry_number;
    }
    return entry;
}

void *lsmash_list_get_entry_data
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
)
{
    lsmash_entry_t *entry = lsmash_list_get_entry( list, entry_number );
    return entry ? entry->data : NULL;
}

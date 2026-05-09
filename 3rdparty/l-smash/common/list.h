/*****************************************************************************
 * list.h
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

typedef void (*lsmash_entry_data_eliminator)( void *data ); /* very same as free() of standard C lib; void free( void * );
                                                             * If 'data' is equal to NULL, the eliminator must do nothing. */

typedef struct lsmash_entry_tag lsmash_entry_t;

struct lsmash_entry_tag
{
    lsmash_entry_t *next;
    lsmash_entry_t *prev;
    void           *data;
};

typedef struct
{
    lsmash_entry_t              *head;
    lsmash_entry_t              *tail;
    lsmash_entry_t              *last_accessed_entry;
    uint32_t                     last_accessed_number;
    uint32_t                     entry_count;
    lsmash_entry_data_eliminator eliminator;
} lsmash_entry_list_t;

/* Utility macros to avoid 'lsmash_entry_data_eliminator' casts to the 'eliminator' argument */
#define lsmash_list_init( list, eliminator ) \
        lsmash_list_init_orig( list, (lsmash_entry_data_eliminator)(eliminator) )
#define lsmash_list_init_simple( list ) \
        lsmash_list_init_orig( list, (lsmash_entry_data_eliminator)lsmash_free )

#define lsmash_list_create( eliminator ) \
        lsmash_list_create_orig( (lsmash_entry_data_eliminator)(eliminator) )
#define lsmash_list_create_simple() \
        lsmash_list_create_orig( (lsmash_entry_data_eliminator)lsmash_free )

/* functions for internal usage */
void lsmash_list_init_orig
(
    lsmash_entry_list_t         *list,
    lsmash_entry_data_eliminator eliminator
);

lsmash_entry_list_t *lsmash_list_create_orig
(
    lsmash_entry_data_eliminator eliminator
);

void lsmash_list_destroy
(
    lsmash_entry_list_t *list
);

int lsmash_list_add_entry
(
    lsmash_entry_list_t *list,
    void                *data
);

int lsmash_list_remove_entry_direct
(
    lsmash_entry_list_t *list,
    lsmash_entry_t      *entry
);

int lsmash_list_remove_entry
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
);

int lsmash_list_remove_entry_tail
(
    lsmash_entry_list_t *list
);

void lsmash_list_remove_entries
(
    lsmash_entry_list_t *list
);

void lsmash_list_move_entries
(
    lsmash_entry_list_t *dst,
    lsmash_entry_list_t *src
);

lsmash_entry_t *lsmash_list_get_entry
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
);

void *lsmash_list_get_entry_data
(
    lsmash_entry_list_t *list,
    uint32_t             entry_number
);

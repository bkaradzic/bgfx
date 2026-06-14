/*****************************************************************************
 * alloc.c
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

#include "internal.h" /* must be placed first */

#include <stdlib.h>
#include <string.h>

void *lsmash_malloc( size_t size )
{
    return malloc( size );
}

void *lsmash_malloc_zero( size_t size )
{
    if( !size )
        return NULL;
    void *p = malloc( size );
    if( !p )
        return NULL;
    memset( p, 0, size );
    return p;
}

void *lsmash_realloc( void *ptr, size_t size )
{
    return realloc( ptr, size );
}

void *lsmash_memdup( const void *ptr, size_t size )
{
    if( !ptr || size == 0 )
        return NULL;
    void *dst = malloc( size );
    if( !dst )
        return NULL;
    memcpy( dst, ptr, size );
    return dst;
}

void lsmash_free( void *ptr )
{
    /* free() shall do nothing if a given address is NULL. */
    free( ptr );
}

void lsmash_freep( void *ptrptr )
{
    if( !ptrptr )
        return;
    void **ptr = (void **)ptrptr;
    free( *ptr );
    *ptr = NULL;
}

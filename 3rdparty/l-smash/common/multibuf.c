/*****************************************************************************
 * multibuf.c
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

#include <string.h>

lsmash_multiple_buffers_t *lsmash_create_multiple_buffers( uint32_t number_of_buffers, uint32_t buffer_size )
{
    if( (uint64_t)number_of_buffers * buffer_size > UINT32_MAX )
        return NULL;
    lsmash_multiple_buffers_t *multiple_buffer = lsmash_malloc( sizeof(lsmash_multiple_buffers_t) );
    if( !multiple_buffer )
        return NULL;
    multiple_buffer->buffers = lsmash_malloc( number_of_buffers * buffer_size );
    if( !multiple_buffer->buffers )
    {
        lsmash_free( multiple_buffer );
        return NULL;
    }
    multiple_buffer->number_of_buffers = number_of_buffers;
    multiple_buffer->buffer_size = buffer_size;
    return multiple_buffer;
}

void *lsmash_withdraw_buffer( lsmash_multiple_buffers_t *multiple_buffer, uint32_t buffer_number )
{
    if( !multiple_buffer || !buffer_number || buffer_number > multiple_buffer->number_of_buffers )
        return NULL;
    return (uint8_t *)multiple_buffer->buffers + (buffer_number - 1) * multiple_buffer->buffer_size;
}

lsmash_multiple_buffers_t *lsmash_resize_multiple_buffers( lsmash_multiple_buffers_t *multiple_buffer, uint32_t buffer_size )
{
    if( !multiple_buffer )
        return NULL;
    if( buffer_size == multiple_buffer->buffer_size )
        return multiple_buffer;
    if( (uint64_t)multiple_buffer->number_of_buffers * buffer_size > UINT32_MAX )
        return NULL;
    uint8_t *temp;
    if( buffer_size > multiple_buffer->buffer_size )
    {
        temp = lsmash_realloc( multiple_buffer->buffers, multiple_buffer->number_of_buffers * buffer_size );
        if( !temp )
            return NULL;
        for( uint32_t i = multiple_buffer->number_of_buffers - 1; i ; i-- )
            memmove( temp + buffer_size, temp + i * multiple_buffer->buffer_size, multiple_buffer->buffer_size );
    }
    else
    {
        for( uint32_t i = 1; i < multiple_buffer->number_of_buffers; i++ )
            memmove( (uint8_t *)multiple_buffer->buffers + buffer_size,
                     (uint8_t *)multiple_buffer->buffers + i * multiple_buffer->buffer_size,
                                multiple_buffer->buffer_size );
        temp = lsmash_realloc( multiple_buffer->buffers, multiple_buffer->number_of_buffers * buffer_size );
        if( !temp )
            return NULL;
    }
    multiple_buffer->buffers     = temp;
    multiple_buffer->buffer_size = buffer_size;
    return multiple_buffer;
}

void lsmash_destroy_multiple_buffers( lsmash_multiple_buffers_t *multiple_buffer )
{
    if( !multiple_buffer )
        return;
    lsmash_free( multiple_buffer->buffers );
    lsmash_free( multiple_buffer );
}

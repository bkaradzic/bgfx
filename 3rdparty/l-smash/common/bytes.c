/*****************************************************************************
 * bytes.c
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
#include <limits.h>

lsmash_bs_t *lsmash_bs_create( void )
{
    lsmash_bs_t *bs = lsmash_malloc_zero( sizeof(lsmash_bs_t) );
    if( !bs )
        return NULL;
    bs->unseekable      = 1;
    bs->buffer.internal = 1;
    bs->buffer.max_size = BS_MAX_DEFAULT_READ_SIZE;
    return bs;
}

static void bs_buffer_free( lsmash_bs_t *bs )
{
    if( bs->buffer.internal )
        lsmash_free( bs->buffer.data );
    bs->buffer.data  = NULL;
    bs->buffer.alloc = 0;
    bs->buffer.store = 0;
    bs->buffer.pos   = 0;
}

void lsmash_bs_cleanup( lsmash_bs_t *bs )
{
    if( !bs )
        return;
    bs_buffer_free( bs );
    lsmash_free( bs );
}

int lsmash_bs_set_empty_stream( lsmash_bs_t *bs, uint8_t *data, size_t size )
{
    if( !bs )
        return LSMASH_ERR_FUNCTION_PARAM;
    bs->stream     = NULL;      /* empty stream */
    bs->eof        = 1;         /* unreadable because of empty stream */
    bs->eob        = 0;         /* readable on the buffer */
    bs->error      = 0;
    bs->unseekable = 1;         /* only seek on the buffer */
    bs->written    = size;      /* behave as if the size of the empty stream is 'size' */
    bs->offset     = size;      /* behave as if the poiter of the stream is at the end */
    bs->buffer.unseekable = 0;  /* only seek on the buffer */
    bs->buffer.internal   = 0;  /* must not be allocated internally */
    bs->buffer.data       = data;
    bs->buffer.store      = size;
    bs->buffer.alloc      = size;
    bs->buffer.pos        = 0;
    bs->buffer.max_size   = 0;  /* make no sense */
    bs->buffer.count      = 0;
    bs->read  = NULL;
    bs->write = NULL;
    bs->seek  = NULL;
    return 0;
}

void lsmash_bs_empty( lsmash_bs_t *bs )
{
    if( !bs )
        return;
    if( bs->buffer.data )
        memset( bs->buffer.data, 0, bs->buffer.alloc );
    bs->buffer.store = 0;
    bs->buffer.pos   = 0;
}

static void bs_alloc( lsmash_bs_t *bs, size_t alloc )
{
    if( (bs->buffer.alloc >= alloc) || bs->error )
        return;
    if( !bs->buffer.internal )
    {
        /* We cannot re-allocate the memory block. */
        bs->error = 1;
        return;
    }
    alloc  = LSMASH_MAX( alloc, bs->buffer.max_size );
    uint8_t *data;
    if( !bs->buffer.data )
        data = lsmash_malloc( alloc );
    else
        data = lsmash_realloc( bs->buffer.data, alloc );
    if( !data )
    {
        bs_buffer_free( bs );
        bs->error = 1;
        return;
    }
    bs->buffer.internal = 1;
    bs->buffer.data     = data;
    bs->buffer.alloc    = alloc;
}

static uint64_t bs_estimate_seek_offset( lsmash_bs_t *bs, int64_t offset, int whence )
{
    /* Calculate the offset after the seek. */
    uint64_t dst_offset;
    if( whence == SEEK_SET )
    {
        assert( offset >= 0 );
        if( bs->written < offset )
            dst_offset = bs->written;
        else
            dst_offset = offset;
    }
    else if( whence == SEEK_CUR )
    {
        if( offset < 0 && bs->offset < -offset )
            dst_offset = 0;
        else if( offset > 0 && bs->written < bs->offset + offset )
            dst_offset = bs->written;
        else
            dst_offset = bs->offset + offset;
    }
    else /* if( whence == SEEK_END ) */
    {
        assert( offset <= 0 );
        if( bs->written < -offset )
            dst_offset = 0;
        else
            dst_offset = bs->written + offset;
    }
    return dst_offset;
}

/* TODO: Support offset > INT64_MAX */
int64_t lsmash_bs_write_seek( lsmash_bs_t *bs, int64_t offset, int whence )
{
    if( bs->unseekable )
        return LSMASH_ERR_NAMELESS;
    if( whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END )
        return LSMASH_ERR_FUNCTION_PARAM;
    /* Try to seek the stream. */
    int64_t ret = bs->seek( bs->stream, offset, whence );
    if( ret < 0 )
        return ret;
    bs->offset = bs_estimate_seek_offset( bs, offset, whence );
    bs->eof    = 0;
    bs->eob    = 0;
    return ret;
}

/* TODO: Support offset > INT64_MAX */
int64_t lsmash_bs_read_seek( lsmash_bs_t *bs, int64_t offset, int whence )
{
    if( whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( whence == SEEK_CUR )
        offset -= lsmash_bs_get_remaining_buffer_size( bs );
    /* Check whether we can seek on the buffer. */
    if( !bs->buffer.unseekable )
    {
        assert( bs->offset >= bs->buffer.store );
        uint64_t dst_offset = bs_estimate_seek_offset( bs, offset, whence );
        uint64_t offset_s = bs->offset - bs->buffer.store;
        uint64_t offset_e = bs->offset;
        if( bs->unseekable || (dst_offset >= offset_s && dst_offset < offset_e) )
        {
            /* OK, we can. So, seek on the buffer. */
            bs->buffer.pos = dst_offset - offset_s;
            bs->eob        = 0;
            return lsmash_bs_get_stream_pos( bs );
        }
    }
    if( bs->unseekable )
        return LSMASH_ERR_NAMELESS;
    /* Try to seek the stream. */
    int64_t ret = bs->seek( bs->stream, offset, whence );
    if( ret < 0 )
        return ret;
    bs->offset  = ret;
    bs->written = LSMASH_MAX( bs->written, bs->offset );
    bs->eof     = 0;
    bs->eob     = 0;
    /* The data on the buffer is invalid. */
    lsmash_bs_empty( bs );
    return ret;
}

void lsmash_bs_dispose_past_data( lsmash_bs_t *bs )
{
    /* Move remainder bytes. */
    assert( bs->buffer.store >= bs->buffer.pos );
    size_t remainder = lsmash_bs_get_remaining_buffer_size( bs );
    if( bs->buffer.pos && remainder )
        memmove( lsmash_bs_get_buffer_data_start( bs ), lsmash_bs_get_buffer_data( bs ), remainder );
    bs->buffer.store = remainder;
    bs->buffer.pos   = 0;
}

/*---- bitstream writer ----*/
void lsmash_bs_put_byte( lsmash_bs_t *bs, uint8_t value )
{
    if( bs->buffer.internal
     || bs->buffer.data )
    {
        bs_alloc( bs, bs->buffer.store + 1 );
        if( bs->error )
            return;
        bs->buffer.data[ bs->buffer.store ] = value;
    }
    ++ bs->buffer.store;
}

void lsmash_bs_put_bytes( lsmash_bs_t *bs, uint32_t size, void *value )
{
    if( size == 0 || !value )
        return;
    if( bs->buffer.internal
     || bs->buffer.data )
    {
        bs_alloc( bs, bs->buffer.store + size );
        if( bs->error )
            return;
        memcpy( lsmash_bs_get_buffer_data_end( bs ), value, size );
    }
    bs->buffer.store += size;
}

void lsmash_bs_put_be16( lsmash_bs_t *bs, uint16_t value )
{
    lsmash_bs_put_byte( bs, value >> 8 );
    lsmash_bs_put_byte( bs, value );
}

void lsmash_bs_put_be24( lsmash_bs_t *bs, uint32_t value )
{
    lsmash_bs_put_byte( bs, value >> 16 );
    lsmash_bs_put_be16( bs, value );
}

void lsmash_bs_put_be32( lsmash_bs_t *bs, uint32_t value )
{
    lsmash_bs_put_be16( bs, value >> 16 );
    lsmash_bs_put_be16( bs, value );
}

void lsmash_bs_put_be64( lsmash_bs_t *bs, uint64_t value )
{
    lsmash_bs_put_be32( bs, value >> 32 );
    lsmash_bs_put_be32( bs, value );
}

void lsmash_bs_put_byte_from_64( lsmash_bs_t *bs, uint64_t value )
{
    lsmash_bs_put_byte( bs, value );
}

void lsmash_bs_put_be16_from_64( lsmash_bs_t *bs, uint64_t value )
{
    lsmash_bs_put_be16( bs, value );
}

void lsmash_bs_put_be24_from_64( lsmash_bs_t *bs, uint64_t value )
{
    lsmash_bs_put_be24( bs, value );
}

void lsmash_bs_put_be32_from_64( lsmash_bs_t *bs, uint64_t value )
{
    lsmash_bs_put_be32( bs, value );
}

void lsmash_bs_put_le16( lsmash_bs_t *bs, uint16_t value )
{
    lsmash_bs_put_byte( bs, value );
    lsmash_bs_put_byte( bs, value >> 8 );
}

void lsmash_bs_put_le32( lsmash_bs_t *bs, uint32_t value )
{
    lsmash_bs_put_le16( bs, value );
    lsmash_bs_put_le16( bs, value >> 16 );
}

int lsmash_bs_flush_buffer( lsmash_bs_t *bs )
{
    if( !bs )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( bs->buffer.store == 0
     || (bs->stream && bs->write && !bs->buffer.data) )
        return 0;
    if( bs->error
     || (bs->stream && bs->write && bs->write( bs->stream, lsmash_bs_get_buffer_data_start( bs ), bs->buffer.store ) != bs->buffer.store) )
    {
        bs_buffer_free( bs );
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    if( bs->write )
    {
        bs->written += bs->buffer.store;
        bs->offset  += bs->buffer.store;
    }
    bs->buffer.store = 0;
    return 0;
}

int lsmash_bs_write_data( lsmash_bs_t *bs, const uint8_t *buf, size_t size )
{
    if( !bs || size > INT_MAX )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !buf || size == 0 )
        return 0;
    if( bs->error || !bs->stream )
    {
        bs_buffer_free( bs );
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    int write_size = bs->write( bs->stream, (uint8_t *)buf, size );
    bs->written += write_size;
    bs->offset  += write_size;
    return write_size != size ? LSMASH_ERR_NAMELESS : 0;
}

void *lsmash_bs_export_data( lsmash_bs_t *bs, uint32_t *length )
{
    if( !bs || !bs->buffer.data || bs->buffer.store == 0 || bs->error )
        return NULL;
    void *buf = lsmash_memdup( lsmash_bs_get_buffer_data_start( bs ), bs->buffer.store );
    if( !buf )
        return NULL;
    if( length )
        *length = bs->buffer.store;
    return buf;
}
/*---- ----*/

/*---- bitstream reader ----*/
static void bs_fill_buffer( lsmash_bs_t *bs )
{
    if( bs->eof || bs->error )
        return;
    if( !bs->read || !bs->stream || bs->buffer.max_size == 0 )
    {
        bs->eof = 1;
        return;
    }
    if( !bs->buffer.data )
    {
        bs_alloc( bs, bs->buffer.max_size );
        if( bs->error )
            return;
    }
    /* Read bytes from the stream to fill the buffer. */
    lsmash_bs_dispose_past_data( bs );
    while( bs->buffer.alloc > bs->buffer.store )
    {
        uint64_t invalid_buffer_size = bs->buffer.alloc - bs->buffer.store;
        int max_read_size = LSMASH_MIN( invalid_buffer_size, bs->buffer.max_size );
        int read_size = bs->read( bs->stream, lsmash_bs_get_buffer_data_end( bs ), max_read_size );
        if( read_size == 0 )
        {
            bs->eof = 1;
            return;
        }
        else if( read_size < 0 )
        {
            bs->error = 1;
            return;
        }
        bs->buffer.unseekable = 0;
        bs->buffer.store += read_size;
        bs->offset       += read_size;
        bs->written = LSMASH_MAX( bs->written, bs->offset );
    }
}

uint8_t lsmash_bs_show_byte( lsmash_bs_t *bs, uint32_t offset )
{
    if( bs->error )
        return 0;
    if( offset >= lsmash_bs_get_remaining_buffer_size( bs ) )
    {
        bs_fill_buffer( bs );
        if( bs->error )
            return 0;
        if( offset >= lsmash_bs_get_remaining_buffer_size( bs ) )
        {
            if( bs->eof )
                /* No more read from both the stream and the buffer. */
                return 0;
            /* We need increase the buffer size. */
            bs_alloc( bs, bs->buffer.pos + offset + 1 );
            bs_fill_buffer( bs );
            if( bs->error )
                return 0;
        }
    }
    return bs->buffer.data[ bs->buffer.pos + offset ];
}

uint16_t lsmash_bs_show_be16( lsmash_bs_t *bs, uint32_t offset )
{
    return ((uint16_t)lsmash_bs_show_byte( bs, offset     ) << 8)
         | ((uint16_t)lsmash_bs_show_byte( bs, offset + 1 ));
}

uint32_t lsmash_bs_show_be24( lsmash_bs_t *bs, uint32_t offset )
{
    return ((uint32_t)lsmash_bs_show_byte( bs, offset     ) << 16)
         | ((uint32_t)lsmash_bs_show_byte( bs, offset + 1 ) <<  8)
         | ((uint32_t)lsmash_bs_show_byte( bs, offset + 2 ));
}

uint32_t lsmash_bs_show_be32( lsmash_bs_t *bs, uint32_t offset )
{
    return ((uint32_t)lsmash_bs_show_byte( bs, offset     ) << 24)
         | ((uint32_t)lsmash_bs_show_byte( bs, offset + 1 ) << 16)
         | ((uint32_t)lsmash_bs_show_byte( bs, offset + 2 ) <<  8)
         | ((uint32_t)lsmash_bs_show_byte( bs, offset + 3 ));
}

uint64_t lsmash_bs_show_be64( lsmash_bs_t *bs, uint32_t offset )
{
    return ((uint64_t)lsmash_bs_show_byte( bs, offset     ) << 56)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 1 ) << 48)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 2 ) << 40)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 3 ) << 32)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 4 ) << 24)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 5 ) << 16)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 6 ) <<  8)
         | ((uint64_t)lsmash_bs_show_byte( bs, offset + 7 ));
}

uint8_t lsmash_bs_get_byte( lsmash_bs_t *bs )
{
    if( bs->eob || bs->error )
        return 0;
    assert( bs->buffer.pos <= bs->buffer.store );
    if( bs->buffer.pos == bs->buffer.store )
    {
        bs_fill_buffer( bs );
        if( bs->error )
            return 0;
        if( bs->buffer.pos == bs->buffer.store && bs->eof )
        {
            /* No more read from both the stream and the buffer. */
            bs->eob = 1;
            return 0;
        }
    }
    ++ bs->buffer.count;    /* increment counter */
    return bs->buffer.data[ bs->buffer.pos ++ ];
}

void lsmash_bs_skip_bytes( lsmash_bs_t *bs, uint32_t size )
{
    if( bs->eob || bs->error || size == 0 )
        return;
    uint64_t remainder;
    uint64_t offset = 0;
    while( size > lsmash_bs_get_remaining_buffer_size( bs ) )
    {
        remainder = lsmash_bs_get_remaining_buffer_size( bs );
        offset += remainder;
        size   -= remainder;
        bs->buffer.pos = bs->buffer.store;
        if( bs->eof )
        {
            /* No more read from both the stream and the buffer. */
            bs->eob = 1;
            break;
        }
        else
        {
            bs_fill_buffer( bs );
            if( bs->error )
                break;
        }
    }
    remainder = LSMASH_MIN( size, lsmash_bs_get_remaining_buffer_size( bs ) );
    offset           += remainder;
    bs->buffer.pos   += remainder;
    bs->buffer.count += offset;
}

void lsmash_bs_skip_bytes_64( lsmash_bs_t *bs, uint64_t size )
{
    while( size )
    {
        uint64_t skip_bytes = LSMASH_MIN( size, UINT32_MAX );
        lsmash_bs_skip_bytes( bs, (uint32_t)skip_bytes );
        size -= skip_bytes;
        if( bs->eob )
            return;
    }
}

static int64_t bs_get_bytes( lsmash_bs_t *bs, uint32_t size, uint8_t *buf )
{
    size_t    remainder;
    size_t    remain_size = size;
    uintptr_t offset      = 0;
    while( remain_size > lsmash_bs_get_remaining_buffer_size( bs ) )
    {
        remainder = lsmash_bs_get_remaining_buffer_size( bs );
        memcpy( buf + offset, lsmash_bs_get_buffer_data( bs ), remainder );
        offset      += remainder;
        remain_size -= remainder;
        bs->buffer.pos = bs->buffer.store;
        if( bs->eof )
        {
            /* No more read from both the stream and the buffer. */
            bs->eob = 1;
            break;
        }
        else
        {
            bs_fill_buffer( bs );
            if( bs->error )
            {
                bs->buffer.count += offset;
                return LSMASH_ERR_NAMELESS;
            }
        }
    }
    remainder = LSMASH_MIN( remain_size, lsmash_bs_get_remaining_buffer_size( bs ) );
    memcpy( buf + offset, lsmash_bs_get_buffer_data( bs ), remainder );
    offset           += remainder;
    bs->buffer.pos   += remainder;
    bs->buffer.count += offset;
    if( offset < size )
        memset( buf + offset, 0, size - offset );
    return (int64_t)offset;
}

uint8_t *lsmash_bs_get_bytes( lsmash_bs_t *bs, uint32_t size )
{
    if( bs->eob || bs->error || size == 0 )
        return NULL;
    uint8_t *value = lsmash_malloc( size );
    if( !value )
    {
        bs->error = 1;
        return NULL;
    }
    if( bs_get_bytes( bs, size, value ) < 0 )
    {
        lsmash_free( value );
        return NULL;
    }
    return value;
}

int64_t lsmash_bs_get_bytes_ex( lsmash_bs_t *bs, uint32_t size, uint8_t *value )
{
    if( size == 0 )
        return 0;
    if( bs->eob || bs->error )
        return LSMASH_ERR_NAMELESS;
    return bs_get_bytes( bs, size, value );
}

uint16_t lsmash_bs_get_be16( lsmash_bs_t *bs )
{
    uint16_t    value = lsmash_bs_get_byte( bs );
    return (value<<8) | lsmash_bs_get_byte( bs );
}

uint32_t lsmash_bs_get_be24( lsmash_bs_t *bs )
{
    uint32_t     value = lsmash_bs_get_byte( bs );
    return (value<<16) | lsmash_bs_get_be16( bs );
}

uint32_t lsmash_bs_get_be32( lsmash_bs_t *bs )
{
    uint32_t     value = lsmash_bs_get_be16( bs );
    return (value<<16) | lsmash_bs_get_be16( bs );
}

uint64_t lsmash_bs_get_be64( lsmash_bs_t *bs )
{
    uint64_t     value = lsmash_bs_get_be32( bs );
    return (value<<32) | lsmash_bs_get_be32( bs );
}

uint64_t lsmash_bs_get_byte_to_64( lsmash_bs_t *bs )
{
    return lsmash_bs_get_byte( bs );
}

uint64_t lsmash_bs_get_be16_to_64( lsmash_bs_t *bs )
{
    return lsmash_bs_get_be16( bs );
}

uint64_t lsmash_bs_get_be24_to_64( lsmash_bs_t *bs )
{
    return lsmash_bs_get_be24( bs );
}

uint64_t lsmash_bs_get_be32_to_64( lsmash_bs_t *bs )
{
    return lsmash_bs_get_be32( bs );
}

uint16_t lsmash_bs_get_le16( lsmash_bs_t *bs )
{
    uint16_t value = lsmash_bs_get_byte( bs );
    return value | (lsmash_bs_get_byte( bs ) << 8);
}

uint32_t lsmash_bs_get_le32( lsmash_bs_t *bs )
{
    uint32_t value = lsmash_bs_get_le16( bs );
    return value | (lsmash_bs_get_le16( bs ) << 16);
}

int lsmash_bs_read( lsmash_bs_t *bs, uint32_t size )
{
    if( !bs || size > INT_MAX )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( size == 0 )
        return 0;
    bs_alloc( bs, bs->buffer.store + size );
    if( bs->error || !bs->stream )
    {
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    int read_size = bs->read( bs->stream, lsmash_bs_get_buffer_data_end( bs ), size );
    if( read_size == 0 )
    {
        bs->eof = 1;
        return 0;
    }
    else if( read_size < 0 )
    {
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    bs->buffer.store += read_size;
    bs->offset       += read_size;
    bs->written = LSMASH_MAX( bs->written, bs->offset );
    return read_size;
}

int lsmash_bs_read_data( lsmash_bs_t *bs, uint8_t *buf, size_t *size )
{
    if( !bs || !size || *size > INT_MAX )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( !buf || *size == 0 )
        return 0;
    if( bs->error || !bs->stream )
    {
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    int read_size = bs->read( bs->stream, buf, *size );
    if( read_size == 0 )
        bs->eof = 1;
    else if( read_size < 0 )
    {
        bs->error = 1;
        return LSMASH_ERR_NAMELESS;
    }
    bs->buffer.unseekable = 1;
    bs->offset += read_size;
    *size       = read_size;
    bs->written = LSMASH_MAX( bs->written, bs->offset );
    return 0;
}

int lsmash_bs_import_data( lsmash_bs_t *bs, void *data, uint32_t length )
{
    if( !bs || !data || length == 0 )
        return LSMASH_ERR_FUNCTION_PARAM;
    if( bs->error )
        return LSMASH_ERR_NAMELESS;
    bs_alloc( bs, bs->buffer.store + length );
    if( bs->error || !bs->buffer.data ) /* means, failed to alloc. */
    {
        bs_buffer_free( bs );
        return LSMASH_ERR_NAMELESS;
    }
    memcpy( lsmash_bs_get_buffer_data_end( bs ), data, length );
    bs->buffer.store += length;
    return 0;
}

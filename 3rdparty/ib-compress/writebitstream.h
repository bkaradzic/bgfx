/*
Copyright (c) 2014-2015, Conor Stokes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef WRITE_BIT_STREAM_H__
#define WRITE_BIT_STREAM_H__
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _MSC_VER
#define WBS_INLINE __forceinline
#else
#define WBS_INLINE inline
#endif

// Very simple bitstream for writing that will grow to accomodate written bits.
class WriteBitstream
{
public:

    // Construct the bit stream with an initial buffer capacity - should be a multiple of 8 and > 0
    WriteBitstream( size_t initialBufferCapacity = 16 )
    {
        m_bufferCursor =
        m_buffer       = new uint8_t[ initialBufferCapacity ];
        m_bufferEnd    = m_buffer + initialBufferCapacity;
        m_size         = 0;
        m_bitsLeft     = 64;
        m_bitBuffer    = 0;
    }

    ~WriteBitstream()
    {
        delete[] m_buffer;
    }

    // Size in bits.
    size_t Size() const { return m_size; }

    // Write a number of bits to the stream.
    void Write( uint32_t value, uint32_t bitCount );

    // Write a V int to the stream.
    void WriteVInt( uint32_t value );

    // Get the size in bytes
    size_t ByteSize() const { return ( m_size + 7 ) >> 3; }

    // Finish writing by flushing the buffer.
    void Finish();

    // Get the raw data for this buffer.
    const uint8_t* RawData() const { return m_buffer; }

private:

    // If we need to grow the buffer.
    void GrowBuffer();

    // Not copyable
    WriteBitstream( const WriteBitstream& );

    // Not assignable
    WriteBitstream& operator=( const WriteBitstream& );

    uint64_t  m_bitBuffer;
    size_t    m_size;
    uint8_t*  m_buffer;
    uint8_t*  m_bufferCursor;
    uint8_t*  m_bufferEnd;
    uint32_t  m_bitsLeft;
};

WBS_INLINE void WriteBitstream::Write( uint32_t value, uint32_t bitCount )
{
    m_bitBuffer |= ( static_cast<uint64_t>( value ) << ( 64 - m_bitsLeft ) ) & ( m_bitsLeft == 0 ? 0 : UINT64_C(0xFFFFFFFFFFFFFFFF) );

    if ( bitCount > m_bitsLeft )
    {
        if ( m_bufferCursor > m_bufferEnd - 7 )
        {
            GrowBuffer();
        }

        m_bufferCursor[ 0 ] = m_bitBuffer & 0xFF;
        m_bufferCursor[ 1 ] = ( m_bitBuffer >> 8 ) & 0xFF;
        m_bufferCursor[ 2 ] = ( m_bitBuffer >> 16 ) & 0xFF;
        m_bufferCursor[ 3 ] = ( m_bitBuffer >> 24 ) & 0xFF;
        m_bufferCursor[ 4 ] = ( m_bitBuffer >> 32 ) & 0xFF;
        m_bufferCursor[ 5 ] = ( m_bitBuffer >> 40 ) & 0xFF;
        m_bufferCursor[ 6 ] = ( m_bitBuffer >> 48 ) & 0xFF;
        m_bufferCursor[ 7 ] = ( m_bitBuffer >> 56 ) & 0xFF;

        m_bufferCursor += 8;

        m_bitBuffer = value >> ( m_bitsLeft );
        m_bitsLeft  = 64 - ( bitCount - m_bitsLeft );
    }
    else
    {
        m_bitsLeft -= bitCount;
    }

    m_size += bitCount;
}

WBS_INLINE void WriteBitstream::WriteVInt( uint32_t value )
{
    do
    {
        uint32_t lower7 = value & 0x7F;

        value >>= 7;

        Write( lower7 | ( value > 0 ? 0x80 : 0 ), 8 );

    } while ( value > 0 );
}

inline void WriteBitstream::Finish()
{
    if ( m_bufferCursor > m_bufferEnd - 8 )
    {
        GrowBuffer();
    }

    m_bufferCursor[ 0 ] = m_bitBuffer & 0xFF;
    m_bufferCursor[ 1 ] = ( m_bitBuffer >> 8 ) & 0xFF;
    m_bufferCursor[ 2 ] = ( m_bitBuffer >> 16 ) & 0xFF;
    m_bufferCursor[ 3 ] = ( m_bitBuffer >> 24 ) & 0xFF;
    m_bufferCursor[ 4 ] = ( m_bitBuffer >> 32 ) & 0xFF;
    m_bufferCursor[ 5 ] = ( m_bitBuffer >> 40 ) & 0xFF;
    m_bufferCursor[ 6 ] = ( m_bitBuffer >> 48 ) & 0xFF;
    m_bufferCursor[ 7 ] = ( m_bitBuffer >> 56 ) & 0xFF;

    m_bufferCursor += 8;
}

WBS_INLINE void WriteBitstream::GrowBuffer()
{
    size_t    bufferSize     = m_bufferEnd - m_buffer;
    size_t    newBufferSize  = bufferSize * 2;
    size_t    bufferPosition = m_bufferCursor - m_buffer;
    uint8_t*  newBuffer      = new uint8_t[ newBufferSize ];

    ::memcpy( reinterpret_cast<void*>( newBuffer ), reinterpret_cast<void*>( m_buffer ), bufferSize );

    delete[] m_buffer;

    m_buffer       = newBuffer;
    m_bufferCursor = m_buffer + bufferPosition;
    m_bufferEnd    = m_buffer + newBufferSize;
}

#endif // -- WRITE_BIT_STREAM_H__

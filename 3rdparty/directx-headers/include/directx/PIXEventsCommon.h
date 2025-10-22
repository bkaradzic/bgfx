// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// Don't include this file directly - use pix3.h

#pragma once

#ifndef _PIXEventsCommon_H_
#define _PIXEventsCommon_H_

//
// The PIXBeginEvent and PIXSetMarker functions have an optimized path for
// copying strings that work by copying 128-bit or 64-bits at a time. In some
// circumstances this may result in PIX logging the remaining memory after the
// null terminator.
//
// By default this optimization is enabled unless Address Sanitizer is enabled,
// since this optimization can trigger a global-buffer-overflow when copying
// string literals.
//
// The PIX_ENABLE_BLOCK_ARGUMENT_COPY controls whether or not this optimization
// is enabled. Applications may also explicitly set this macro to 0 to disable
// the optimization if necessary.
//

// Check for Address Sanitizer on either Clang or MSVC

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define PIX_ASAN_ENABLED
#endif
#elif defined(__SANITIZE_ADDRESS__)
#define PIX_ASAN_ENABLED
#endif

#if defined(PIX_ENABLE_BLOCK_ARGUMENT_COPY)
// Previously set values override everything
# define PIX_ENABLE_BLOCK_ARGUMENT_COPY_SET 0
#elif defined(PIX_ASAN_ENABLED)
// Disable block argument copy when address sanitizer is enabled
#define PIX_ENABLE_BLOCK_ARGUMENT_COPY 0
#define PIX_ENABLE_BLOCK_ARGUMENT_COPY_SET 1
#endif

#if !defined(PIX_ENABLE_BLOCK_ARGUMENT_COPY)
// Default to enabled.
#define PIX_ENABLE_BLOCK_ARGUMENT_COPY 1
#define PIX_ENABLE_BLOCK_ARGUMENT_COPY_SET 1
#endif

struct PIXEventsBlockInfo;

struct PIXEventsThreadInfo
{
    PIXEventsBlockInfo* block;
    UINT64* biasedLimit;
    UINT64* destination;
};

//extern "C" UINT64 WINAPI PIXEventsReplaceBlock(PIXEventsThreadInfo * threadInfo, bool getEarliestTime) noexcept;

#define PIX_EVENT_METADATA_NONE                     0x0
#define PIX_EVENT_METADATA_ON_CONTEXT               0x1
#define PIX_EVENT_METADATA_STRING_IS_ANSI           0x2
#define PIX_EVENT_METADATA_HAS_COLOR                0xF0

#ifndef PIX_GAMING_XBOX
#include "PIXEventsLegacy.h"
#endif

enum PIXEventType : UINT8
{
    PIXEvent_EndEvent       = 0x00,
    PIXEvent_BeginEvent     = 0x01,
    PIXEvent_SetMarker      = 0x02,
};

static const UINT64 PIXEventsReservedRecordSpaceQwords = 64;
//this is used to make sure SSE string copy always will end 16-byte write in the current block
//this way only a check if destination < limit can be performed, instead of destination < limit - 1
//since both these are UINT64* and SSE writes in 16 byte chunks, 8 bytes are kept in reserve
//so even if SSE overwrites 8-15 extra bytes, those will still belong to the correct block
//on next iteration check destination will be greater than limit
//this is used as well for fixed size UMD events and PIXEndEvent since these require less space
//than other variable length user events and do not need big reserved space
static const UINT64 PIXEventsReservedTailSpaceQwords = 2;
static const UINT64 PIXEventsSafeFastCopySpaceQwords = PIXEventsReservedRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;
static const UINT64 PIXEventsGraphicsRecordSpaceQwords = 64;

//Bits 7-19 (13 bits)
static const UINT64 PIXEventsBlockEndMarker     = 0x00000000000FFF80;


// V2 events

// Bits 00..06 (7 bits) - Size in QWORDS
static const UINT64 PIXEventsSizeWriteMask      = 0x000000000000007F;
static const UINT64 PIXEventsSizeBitShift       = 0;
static const UINT64 PIXEventsSizeReadMask       = PIXEventsSizeWriteMask << PIXEventsSizeBitShift;
static const UINT64 PIXEventsSizeMax            = (1ull << 7) - 1ull;

// Bits 07..11 (5 bits) - Event Type
static const UINT64 PIXEventsTypeWriteMask      = 0x000000000000001F;
static const UINT64 PIXEventsTypeBitShift       = 7;
static const UINT64 PIXEventsTypeReadMask       = PIXEventsTypeWriteMask << PIXEventsTypeBitShift;

// Bits 12..19 (8 bits) - Event Specific Metadata
static const UINT64 PIXEventsMetadataWriteMask  = 0x00000000000000FF;
static const UINT64 PIXEventsMetadataBitShift   = 12;
static const UINT64 PIXEventsMetadataReadMask   = PIXEventsMetadataWriteMask << PIXEventsMetadataBitShift;

// Buts 20..63 (44 bits) - Timestamp
static const UINT64 PIXEventsTimestampWriteMask = 0x00000FFFFFFFFFFF;
static const UINT64 PIXEventsTimestampBitShift  = 20;
static const UINT64 PIXEventsTimestampReadMask  = PIXEventsTimestampWriteMask << PIXEventsTimestampBitShift;

inline UINT64 PIXEncodeEventInfo(UINT64 timestamp, PIXEventType eventType, UINT8 eventSize, UINT8 eventMetadata)
{
    return
        ((timestamp & PIXEventsTimestampWriteMask) << PIXEventsTimestampBitShift) |
        (((UINT64)eventType & PIXEventsTypeWriteMask) << PIXEventsTypeBitShift) |
        (((UINT64)eventMetadata & PIXEventsMetadataWriteMask) << PIXEventsMetadataBitShift) |
        (((UINT64)eventSize & PIXEventsSizeWriteMask) << PIXEventsSizeBitShift);
}

inline UINT8 PIXEncodeIndexColor(UINT8 color)
{
    // There are 8 index colors, indexed 0 (default) to 7
    return (color & 0x7) << 4;
}

//Bits 60-63 (4)
static const UINT64 PIXEventsStringAlignmentWriteMask     = 0x000000000000000F;
static const UINT64 PIXEventsStringAlignmentReadMask      = 0xF000000000000000;
static const UINT64 PIXEventsStringAlignmentBitShift      = 60;

//Bits 55-59 (5)
static const UINT64 PIXEventsStringCopyChunkSizeWriteMask = 0x000000000000001F;
static const UINT64 PIXEventsStringCopyChunkSizeReadMask  = 0x0F80000000000000;
static const UINT64 PIXEventsStringCopyChunkSizeBitShift  = 55;

//Bit 54
static const UINT64 PIXEventsStringIsANSIWriteMask        = 0x0000000000000001;
static const UINT64 PIXEventsStringIsANSIReadMask         = 0x0040000000000000;
static const UINT64 PIXEventsStringIsANSIBitShift         = 54;

//Bit 53
static const UINT64 PIXEventsStringIsShortcutWriteMask    = 0x0000000000000001;
static const UINT64 PIXEventsStringIsShortcutReadMask     = 0x0020000000000000;
static const UINT64 PIXEventsStringIsShortcutBitShift     = 53;

inline void PIXEncodeStringInfo(UINT64*& destination, BOOL isANSI)
{
    const UINT64 encodedStringInfo = 
        ((sizeof(UINT64) & PIXEventsStringCopyChunkSizeWriteMask) << PIXEventsStringCopyChunkSizeBitShift) |
        (((UINT64)isANSI & PIXEventsStringIsANSIWriteMask) << PIXEventsStringIsANSIBitShift);

    *destination++ = encodedStringInfo;
}

template<UINT alignment, class T>
inline bool PIXIsPointerAligned(T* pointer)
{
    return !(((UINT64)pointer) & (alignment - 1));
}

// Generic template version slower because of the additional clear write
template<class T>
inline void PIXCopyEventArgument(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, T argument)
{
    if (destination < limit)
    {
        *destination = 0ull;
        *((T*)destination) = argument;
        ++destination;
    }
}

// int32 specialization to avoid slower double memory writes
template<>
inline void PIXCopyEventArgument<INT32>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, INT32 argument)
{
    if (destination < limit)
    {
        *reinterpret_cast<INT64*>(destination) = static_cast<INT64>(argument);
        ++destination;
    }
}

// unsigned int32 specialization to avoid slower double memory writes
template<>
inline void PIXCopyEventArgument<UINT32>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, UINT32 argument)
{
    if (destination < limit)
    {
        *destination = static_cast<UINT64>(argument);
        ++destination;
    }
}

// int64 specialization to avoid slower double memory writes
template<>
inline void PIXCopyEventArgument<INT64>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, INT64 argument)
{
    if (destination < limit)
    {
        *reinterpret_cast<INT64*>(destination) = argument;
        ++destination;
    }
}

// unsigned int64 specialization to avoid slower double memory writes
template<>
inline void PIXCopyEventArgument<UINT64>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, UINT64 argument)
{
    if (destination < limit)
    {
        *destination = argument;
        ++destination;
    }
}

//floats must be cast to double during writing the data to be properly printed later when reading the data
//this is needed because when float is passed to varargs function it's cast to double
template<>
inline void PIXCopyEventArgument<float>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, float argument)
{
    if (destination < limit)
    {
        *reinterpret_cast<double*>(destination) = static_cast<double>(argument);
        ++destination;
    }
}

//char has to be cast to a longer signed integer type
//this is due to printf not ignoring correctly the upper bits of unsigned long long for a char format specifier
template<>
inline void PIXCopyEventArgument<char>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, char argument)
{
    if (destination < limit)
    {
        *reinterpret_cast<INT64*>(destination) = static_cast<INT64>(argument);
        ++destination;
    }
}

//UINT8 has to be cast to a longer unsigned integer type
//this is due to printf not ignoring correctly the upper bits of unsigned long long for a char format specifier
template<>
inline void PIXCopyEventArgument<UINT8>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, UINT8 argument)
{
    if (destination < limit)
    {
        *destination = static_cast<UINT64>(argument);
        ++destination;
    }
}

//bool has to be cast to an integer since it's not explicitly supported by string format routines
//there's no format specifier for bool type, but it should work with integer format specifiers
template<>
inline void PIXCopyEventArgument<bool>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, bool argument)
{
    if (destination < limit)
    {
        *destination = static_cast<UINT64>(argument);
        ++destination;
    }
}

inline void PIXCopyEventStringArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    while (destination < limit)
    {
        UINT64 c = static_cast<UINT8>(argument[0]);
        if (!c)
        {
            *destination++ = 0;
            return;
        }
        UINT64 x = c;
        c = static_cast<UINT8>(argument[1]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 8;
        c = static_cast<UINT8>(argument[2]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 16;
        c = static_cast<UINT8>(argument[3]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 24;
        c = static_cast<UINT8>(argument[4]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 32;
        c = static_cast<UINT8>(argument[5]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 40;
        c = static_cast<UINT8>(argument[6]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 48;
        c = static_cast<UINT8>(argument[7]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 56;
        *destination++ = x;
        argument += 8;
    }
}

template<bool>
inline void PIXCopyEventArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    PIXEncodeStringInfo(destination, TRUE);
    PIXCopyEventStringArgumentSlow(destination, limit, argument);
}

template<>
inline void PIXCopyEventArgumentSlow<false>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    PIXCopyEventStringArgumentSlow(destination, limit, argument);
}

#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY

inline void PIXCopyEventStringArgumentFast(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    constexpr UINT64 mask1 = 0x0101010101010101ULL;
    constexpr UINT64 mask2 = 0x8080808080808080ULL;
    UINT64* source = (UINT64*)argument;

    while (destination < limit)
    {
        UINT64 qword = *source++;
        *destination++ = qword;

        //check if any of the characters is a terminating zero
        UINT64 isTerminated = (qword - mask1) & (~qword & mask2);

        if (isTerminated)
        {
            break;
        }
    }
}
#endif

template<>
inline void PIXCopyEventArgument<PCSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    if (destination < limit)
    {
        if (argument != nullptr)
        {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
            if (PIXIsPointerAligned<8>(argument))
            {
                PIXEncodeStringInfo(destination, TRUE);
                PIXCopyEventStringArgumentFast(destination, limit, argument);
            }
            else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
            {
                PIXCopyEventArgumentSlow<true>(destination, limit, argument);
            }
        }
        else
        {
            *destination++ = 0ull;
        }
    }
}

inline void PIXCopyStringArgument(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
{
    if (argument != nullptr)
    {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
        if (PIXIsPointerAligned<8>(argument))
        {
            PIXCopyEventStringArgumentFast(destination, limit, argument);
        }
        else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
        {
            PIXCopyEventArgumentSlow<false>(destination, limit, argument);
        }
    }
    else
    {
        *destination++ = 0ull;
    }
}

template<>
inline void PIXCopyEventArgument<PSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PSTR argument)
{
    PIXCopyEventArgument(destination, limit, (PCSTR)argument);
}

inline void PIXCopyStringArgument(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PSTR argument)
{
    PIXCopyStringArgument(destination, limit, (PCSTR)argument);
}

inline void PIXCopyEventStringArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    while (destination < limit)
    {
        UINT64 c = static_cast<UINT16>(argument[0]);
        if (!c)
        {
            *destination++ = 0;
            return;
        }
        UINT64 x = c;
        c = static_cast<UINT16>(argument[1]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 16;
        c = static_cast<UINT16>(argument[2]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 32;
        c = static_cast<UINT16>(argument[3]);
        if (!c)
        {
            *destination++ = x;
            return;
        }
        x |= c << 48;
        *destination++ = x;
        argument += 4;
    }
}

template<bool>
inline void PIXCopyEventArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    PIXEncodeStringInfo(destination, FALSE);
    PIXCopyEventStringArgumentSlow(destination, limit, argument);
}

template<>
inline void PIXCopyEventArgumentSlow<false>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    PIXCopyEventStringArgumentSlow(destination, limit, argument);
}

#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
inline void PIXCopyEventStringArgumentFast(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    UINT64* source = (UINT64*)argument;
    while (destination < limit)
    {
        UINT64 qword = *source++;
        *destination++ = qword;
        //check if any of the characters is a terminating zero
        //TODO: check if reversed condition is faster
        if (!((qword & 0xFFFF000000000000) &&
            (qword & 0xFFFF00000000) &&
            (qword & 0xFFFF0000) &&
            (qword & 0xFFFF)))
        {
            break;
        }
    }
}
#endif

template<>
inline void PIXCopyEventArgument<PCWSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    if (destination < limit)
    {
        if (argument != nullptr)
        {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
            if (PIXIsPointerAligned<8>(argument))
            {
                PIXEncodeStringInfo(destination, FALSE);
                PIXCopyEventStringArgumentFast(destination, limit, argument);
            }
            else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
            {
                PIXCopyEventArgumentSlow<true>(destination, limit, argument);
            }
        }
        else
        {
            *destination++ = 0ull;
        }
    }
}

inline void PIXCopyStringArgument(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
{
    if (argument != nullptr)
    {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
        if (PIXIsPointerAligned<8>(argument))
        {
            PIXCopyEventStringArgumentFast(destination, limit, argument);
        }
        else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
        {
            PIXCopyEventArgumentSlow<false>(destination, limit, argument);
        }
    }
    else
    {
        *destination++ = 0ull;
    }
}

template<>
inline void PIXCopyEventArgument<PWSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PWSTR argument)
{
    PIXCopyEventArgument(destination, limit, (PCWSTR)argument);
};

inline void PIXCopyStringArgument(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PWSTR argument)
{
    PIXCopyStringArgument(destination, limit, (PCWSTR)argument);
};

#if defined(__d3d12_x_h__) || defined(__d3d12_xs_h__) || defined(__d3d12_h__)

inline void PIXSetGPUMarkerOnContext(_In_ ID3D12GraphicsCommandList* commandList, _In_reads_bytes_(size) void* data, UINT size)
{
    commandList->SetMarker(D3D12_EVENT_METADATA, data, size);
}

inline void PIXSetGPUMarkerOnContext(_In_ ID3D12CommandQueue* commandQueue, _In_reads_bytes_(size) void* data, UINT size)
{
    commandQueue->SetMarker(D3D12_EVENT_METADATA, data, size);
}

inline void PIXBeginGPUEventOnContext(_In_ ID3D12GraphicsCommandList* commandList, _In_reads_bytes_(size) void* data, UINT size)
{
    commandList->BeginEvent(D3D12_EVENT_METADATA, data, size);
}

inline void PIXBeginGPUEventOnContext(_In_ ID3D12CommandQueue* commandQueue, _In_reads_bytes_(size) void* data, UINT size)
{
    commandQueue->BeginEvent(D3D12_EVENT_METADATA, data, size);
}

inline void PIXEndGPUEventOnContext(_In_ ID3D12GraphicsCommandList* commandList)
{
    commandList->EndEvent();
}

inline void PIXEndGPUEventOnContext(_In_ ID3D12CommandQueue* commandQueue)
{
    commandQueue->EndEvent();
}

#endif //__d3d12_h__

template<class T> struct PIXInferScopedEventType { typedef T Type; };
template<class T> struct PIXInferScopedEventType<const T> { typedef T Type; };
template<class T> struct PIXInferScopedEventType<T*> { typedef T Type; };
template<class T> struct PIXInferScopedEventType<T* const> { typedef T Type; };
template<> struct PIXInferScopedEventType<UINT64> { typedef void Type; };
template<> struct PIXInferScopedEventType<const UINT64> { typedef void Type; };
template<> struct PIXInferScopedEventType<INT64> { typedef void Type; };
template<> struct PIXInferScopedEventType<const INT64> { typedef void Type; };
template<> struct PIXInferScopedEventType<UINT> { typedef void Type; };
template<> struct PIXInferScopedEventType<const UINT> { typedef void Type; };
template<> struct PIXInferScopedEventType<INT> { typedef void Type; };
template<> struct PIXInferScopedEventType<const INT> { typedef void Type; };
template<> struct PIXInferScopedEventType<UINT8> { typedef void Type; };
template<> struct PIXInferScopedEventType<const UINT8> { typedef void Type; };
template<> struct PIXInferScopedEventType<INT8> { typedef void Type; };
template<> struct PIXInferScopedEventType<const INT8> { typedef void Type; };

#endif //_PIXEventsCommon_H_

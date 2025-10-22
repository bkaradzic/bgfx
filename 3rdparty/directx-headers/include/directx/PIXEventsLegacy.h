// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

// Don't include this file directly - use pix3.h
// This file encodes PIX events in the legacy PIX event format.

#ifndef _PIXEventsLegacy_H_
#define _PIXEventsLegacy_H_

#include <cstdint>

#if defined(_M_X64) || defined(_M_IX86)
#include <emmintrin.h>
#endif

namespace PixEventsLegacy
{
    enum PIXEventType
    {
        PIXEvent_EndEvent = 0x000,
        PIXEvent_BeginEvent_VarArgs = 0x001,
        PIXEvent_BeginEvent_NoArgs = 0x002,
        PIXEvent_SetMarker_VarArgs = 0x007,
        PIXEvent_SetMarker_NoArgs = 0x008,

        PIXEvent_EndEvent_OnContext = 0x010,
        PIXEvent_BeginEvent_OnContext_VarArgs = 0x011,
        PIXEvent_BeginEvent_OnContext_NoArgs = 0x012,
        PIXEvent_SetMarker_OnContext_VarArgs = 0x017,
        PIXEvent_SetMarker_OnContext_NoArgs = 0x018,
    };

    static const UINT64 PIXEventsReservedRecordSpaceQwords = 64;
    static const UINT64 PIXEventsReservedTailSpaceQwords = 2;
    static const UINT64 PIXEventsSafeFastCopySpaceQwords = PIXEventsReservedRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;
    static const UINT64 PIXEventsGraphicsRecordSpaceQwords = 64;

    //Bits 7-19 (13 bits)
    static const UINT64 PIXEventsBlockEndMarker = 0x00000000000FFF80;

    //Bits 10-19 (10 bits)
    static const UINT64 PIXEventsTypeReadMask = 0x00000000000FFC00;
    static const UINT64 PIXEventsTypeWriteMask = 0x00000000000003FF;
    static const UINT64 PIXEventsTypeBitShift = 10;

    //Bits 20-63 (44 bits)
    static const UINT64 PIXEventsTimestampReadMask = 0xFFFFFFFFFFF00000;
    static const UINT64 PIXEventsTimestampWriteMask = 0x00000FFFFFFFFFFF;
    static const UINT64 PIXEventsTimestampBitShift = 20;

    inline UINT64 PIXEncodeEventInfo(UINT64 timestamp, PIXEventType eventType)
    {
        return ((timestamp & PIXEventsTimestampWriteMask) << PIXEventsTimestampBitShift) |
            (((UINT64)eventType & PIXEventsTypeWriteMask) << PIXEventsTypeBitShift);
    }

    //Bits 60-63 (4)
    static const UINT64 PIXEventsStringAlignmentWriteMask = 0x000000000000000F;
    static const UINT64 PIXEventsStringAlignmentReadMask = 0xF000000000000000;
    static const UINT64 PIXEventsStringAlignmentBitShift = 60;

    //Bits 55-59 (5)
    static const UINT64 PIXEventsStringCopyChunkSizeWriteMask = 0x000000000000001F;
    static const UINT64 PIXEventsStringCopyChunkSizeReadMask = 0x0F80000000000000;
    static const UINT64 PIXEventsStringCopyChunkSizeBitShift = 55;

    //Bit 54
    static const UINT64 PIXEventsStringIsANSIWriteMask = 0x0000000000000001;
    static const UINT64 PIXEventsStringIsANSIReadMask = 0x0040000000000000;
    static const UINT64 PIXEventsStringIsANSIBitShift = 54;

    //Bit 53
    static const UINT64 PIXEventsStringIsShortcutWriteMask = 0x0000000000000001;
    static const UINT64 PIXEventsStringIsShortcutReadMask = 0x0020000000000000;
    static const UINT64 PIXEventsStringIsShortcutBitShift = 53;

    inline UINT64 PIXEncodeStringInfo(UINT64 alignment, UINT64 copyChunkSize, BOOL isANSI, BOOL isShortcut)
    {
        return ((alignment & PIXEventsStringAlignmentWriteMask) << PIXEventsStringAlignmentBitShift) |
            ((copyChunkSize & PIXEventsStringCopyChunkSizeWriteMask) << PIXEventsStringCopyChunkSizeBitShift) |
            (((UINT64)isANSI & PIXEventsStringIsANSIWriteMask) << PIXEventsStringIsANSIBitShift) |
            (((UINT64)isShortcut & PIXEventsStringIsShortcutWriteMask) << PIXEventsStringIsShortcutBitShift);
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

    //unsigned char has to be cast to a longer unsigned integer type
    //this is due to printf not ignoring correctly the upper bits of unsigned long long for a char format specifier
    template<>
    inline void PIXCopyEventArgument<unsigned char>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, unsigned char argument)
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

    inline void PIXCopyEventArgumentSlowest(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
    {
        *destination++ = PIXEncodeStringInfo(0, 8, TRUE, FALSE);
        while (destination < limit)
        {
            UINT64 c = static_cast<uint8_t>(argument[0]);
            if (!c)
            {
                *destination++ = 0;
                return;
            }
            UINT64 x = c;
            c = static_cast<uint8_t>(argument[1]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 8;
            c = static_cast<uint8_t>(argument[2]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 16;
            c = static_cast<uint8_t>(argument[3]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 24;
            c = static_cast<uint8_t>(argument[4]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 32;
            c = static_cast<uint8_t>(argument[5]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 40;
            c = static_cast<uint8_t>(argument[6]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 48;
            c = static_cast<uint8_t>(argument[7]);
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

    inline void PIXCopyEventArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
    {
#if PIX_ENABLE_BLOCK_ARGUMENT_COPY
        if (PIXIsPointerAligned<8>(argument))
        {
            *destination++ = PIXEncodeStringInfo(0, 8, TRUE, FALSE);
            UINT64* source = (UINT64*)argument;
            while (destination < limit)
            {
                UINT64 qword = *source++;
                *destination++ = qword;
                //check if any of the characters is a terminating zero
                if (!((qword & 0xFF00000000000000) &&
                    (qword & 0xFF000000000000) &&
                    (qword & 0xFF0000000000) &&
                    (qword & 0xFF00000000) &&
                    (qword & 0xFF000000) &&
                    (qword & 0xFF0000) &&
                    (qword & 0xFF00) &&
                    (qword & 0xFF)))
                {
                    break;
                }
            }
        }
        else
#endif // PIX_ENABLE_BLOCK_ARGUMENT_COPY
        {
            PIXCopyEventArgumentSlowest(destination, limit, argument);
        }
    }

    template<>
    inline void PIXCopyEventArgument<PCSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCSTR argument)
    {
        if (destination < limit)
        {
            if (argument != nullptr)
            {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
                if (PIXIsPointerAligned<16>(argument))
                {
                    *destination++ = PIXEncodeStringInfo(0, 16, TRUE, FALSE);
                    __m128i zero = _mm_setzero_si128();
                    if (PIXIsPointerAligned<16>(destination))
                    {
                        while (destination < limit)
                        {
                            __m128i mem = _mm_load_si128((__m128i*)argument);
                            _mm_store_si128((__m128i*)destination, mem);
                            //check if any of the characters is a terminating zero
                            __m128i res = _mm_cmpeq_epi8(mem, zero);
                            destination += 2;
                            if (_mm_movemask_epi8(res))
                                break;
                            argument += 16;
                        }
                    }
                    else
                    {
                        while (destination < limit)
                        {
                            __m128i mem = _mm_load_si128((__m128i*)argument);
                            _mm_storeu_si128((__m128i*)destination, mem);
                            //check if any of the characters is a terminating zero
                            __m128i res = _mm_cmpeq_epi8(mem, zero);
                            destination += 2;
                            if (_mm_movemask_epi8(res))
                                break;
                            argument += 16;
                        }
                    }
                }
                else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
                {
                    PIXCopyEventArgumentSlow(destination, limit, argument);
                }
            }
            else
            {
                *destination++ = 0ull;
            }
        }
    }

    template<>
    inline void PIXCopyEventArgument<PSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PSTR argument)
    {
        PIXCopyEventArgument(destination, limit, (PCSTR)argument);
    }

    inline void PIXCopyEventArgumentSlowest(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
    {
        *destination++ = PIXEncodeStringInfo(0, 8, FALSE, FALSE);
        while (destination < limit)
        {
            UINT64 c = static_cast<uint16_t>(argument[0]);
            if (!c)
            {
                *destination++ = 0;
                return;
            }
            UINT64 x = c;
            c = static_cast<uint16_t>(argument[1]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 16;
            c = static_cast<uint16_t>(argument[2]);
            if (!c)
            {
                *destination++ = x;
                return;
            }
            x |= c << 32;
            c = static_cast<uint16_t>(argument[3]);
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

    inline void PIXCopyEventArgumentSlow(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
    {
#if PIX_ENABLE_BLOCK_ARGUMENT_COPY
        if (PIXIsPointerAligned<8>(argument))
        {
            *destination++ = PIXEncodeStringInfo(0, 8, FALSE, FALSE);
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
        else
#endif // PIX_ENABLE_BLOCK_ARGUMENT_COPY
        {
            PIXCopyEventArgumentSlowest(destination, limit, argument);
        }
    }

    template<>
    inline void PIXCopyEventArgument<PCWSTR>(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, _In_ PCWSTR argument)
    {
        if (destination < limit)
        {
            if (argument != nullptr)
            {
#if (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
                if (PIXIsPointerAligned<16>(argument))
                {
                    *destination++ = PIXEncodeStringInfo(0, 16, FALSE, FALSE);
                    __m128i zero = _mm_setzero_si128();
                    if (PIXIsPointerAligned<16>(destination))
                    {
                        while (destination < limit)
                        {
                            __m128i mem = _mm_load_si128((__m128i*)argument);
                            _mm_store_si128((__m128i*)destination, mem);
                            //check if any of the characters is a terminating zero
                            __m128i res = _mm_cmpeq_epi16(mem, zero);
                            destination += 2;
                            if (_mm_movemask_epi8(res))
                                break;
                            argument += 8;
                        }
                    }
                    else
                    {
                        while (destination < limit)
                        {
                            __m128i mem = _mm_load_si128((__m128i*)argument);
                            _mm_storeu_si128((__m128i*)destination, mem);
                            //check if any of the characters is a terminating zero
                            __m128i res = _mm_cmpeq_epi16(mem, zero);
                            destination += 2;
                            if (_mm_movemask_epi8(res))
                                break;
                            argument += 8;
                        }
                    }
                }
                else
#endif // (defined(_M_X64) || defined(_M_IX86)) && PIX_ENABLE_BLOCK_ARGUMENT_COPY
                {
                    PIXCopyEventArgumentSlow(destination, limit, argument);
                }
            }
            else
            {
                *destination++ = 0ull;
            }
        }
    }

    inline void PIXCopyEventArguments(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit)
    {
        // nothing
        UNREFERENCED_PARAMETER(destination);
        UNREFERENCED_PARAMETER(limit);
    }

    template<typename ARG, typename... ARGS>
    void PIXCopyEventArguments(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, ARG const& arg, ARGS const&... args)
    {
        PIXCopyEventArgument(destination, limit, arg);
        PIXCopyEventArguments(destination, limit, args...);
    }

    template<typename... ARGS>
    struct PIXEventTypeInferer
    {
        static constexpr PIXEventType Begin() { return PIXEvent_BeginEvent_VarArgs; }
        static constexpr PIXEventType SetMarker() { return PIXEvent_SetMarker_VarArgs; }
        static constexpr PIXEventType BeginOnContext() { return PIXEvent_BeginEvent_OnContext_VarArgs; }
        static constexpr PIXEventType SetMarkerOnContext() { return PIXEvent_SetMarker_OnContext_VarArgs; }
        static constexpr PIXEventType End() { return PIXEvent_EndEvent; }

        // Xbox and Windows store different types of events for context events.
        // On Xbox these include a context argument, while on Windows they do
        // not. It is important not to change the event types used on the
        // Windows version as there are OS components (eg debug layer & DRED)
        // that decode event structs.
#ifdef PIX_XBOX
        static constexpr PIXEventType GpuBeginOnContext() { return PIXEvent_BeginEvent_OnContext_VarArgs; }
        static constexpr PIXEventType GpuSetMarkerOnContext() { return PIXEvent_SetMarker_OnContext_VarArgs; }
        static constexpr PIXEventType GpuEndOnContext() { return PIXEvent_EndEvent_OnContext; }
#else
        static constexpr PIXEventType GpuBeginOnContext() { return PIXEvent_BeginEvent_VarArgs; }
        static constexpr PIXEventType GpuSetMarkerOnContext() { return PIXEvent_SetMarker_VarArgs; }
        static constexpr PIXEventType GpuEndOnContext() { return PIXEvent_EndEvent; }
#endif
    };

    template<>
    struct PIXEventTypeInferer<>
    {
        static constexpr PIXEventType Begin() { return PIXEvent_BeginEvent_NoArgs; }
        static constexpr PIXEventType SetMarker() { return PIXEvent_SetMarker_NoArgs; }
        static constexpr PIXEventType BeginOnContext() { return PIXEvent_BeginEvent_OnContext_NoArgs; }
        static constexpr PIXEventType SetMarkerOnContext() { return PIXEvent_SetMarker_OnContext_NoArgs; }
        static constexpr PIXEventType End() { return PIXEvent_EndEvent; }

#ifdef PIX_XBOX
        static constexpr PIXEventType GpuBeginOnContext() { return PIXEvent_BeginEvent_OnContext_NoArgs; }
        static constexpr PIXEventType GpuSetMarkerOnContext() { return PIXEvent_SetMarker_OnContext_NoArgs; }
        static constexpr PIXEventType GpuEndOnContext() { return PIXEvent_EndEvent_OnContext; }
#else
        static constexpr PIXEventType GpuBeginOnContext() { return PIXEvent_BeginEvent_NoArgs; }
        static constexpr PIXEventType GpuSetMarkerOnContext() { return PIXEvent_SetMarker_NoArgs; }
        static constexpr PIXEventType GpuEndOnContext() { return PIXEvent_EndEvent; }
#endif
    };


    template<size_t size, typename STR, typename... ARGS>
    UINT64* EncodeBeginEventForContext(UINT64 (&buffer)[size], UINT64 color, STR formatString, ARGS... args)
    {
        UINT64* destination = buffer;
        UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

        *destination++ = PIXEncodeEventInfo(0, PIXEventTypeInferer<ARGS...>::GpuBeginOnContext());
        *destination++ = color;

        PIXCopyEventArguments(destination, limit, formatString, args...);
        *destination = 0ull;

        return destination;
    }

    template<size_t size, typename STR, typename... ARGS>
    UINT64* EncodeSetMarkerForContext(UINT64 (&buffer)[size], UINT64 color, STR formatString, ARGS... args)
    {
        UINT64* destination = buffer;
        UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

        *destination++ = PIXEncodeEventInfo(0, PIXEventTypeInferer<ARGS...>::GpuSetMarkerOnContext());
        *destination++ = color;

        PIXCopyEventArguments(destination, limit, formatString, args...);
        *destination = 0ull;

        return destination;
    }
}

#endif //_PIXEventsLegacy_H_

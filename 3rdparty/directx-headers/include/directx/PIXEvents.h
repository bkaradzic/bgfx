// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// Don't include this file directly - use pix3.h

#pragma once

#ifndef _PixEvents_H_
#define _PixEvents_H_

#ifndef _PIX3_H_
# error Do not include this file directly - use pix3.h
#endif

#include "PIXEventsCommon.h"

#if _MSC_VER < 1800
# error This version of pix3.h is only supported on Visual Studio 2013 or higher
#elif _MSC_VER < 1900
# ifndef constexpr // Visual Studio 2013 doesn't support constexpr
#  define constexpr
#  define PIX3__DEFINED_CONSTEXPR
# endif
#endif

 // Xbox does not support CPU events for retail scenarios
#if defined(USE_PIX) || !defined(PIX_XBOX)
#define PIX_CONTEXT_EMIT_CPU_EVENTS
#endif

namespace PIXEventsDetail
{
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

    template<typename ARG, typename... ARGS>
    void PIXCopyStringArguments(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, ARG const& arg, ARGS const&... args)
    {
        PIXCopyStringArgument(destination, limit, arg);
        PIXCopyEventArguments(destination, limit, args...);
    }

    template<typename ARG, typename... ARGS>
    void PIXCopyStringArgumentsWithContext(_Out_writes_to_ptr_(limit) UINT64*& destination, _In_ const UINT64* limit, void* context, ARG const& arg, ARGS const&... args)
    {
#ifdef PIX_XBOX
        UNREFERENCED_PARAMETER(context);
        PIXCopyStringArgument(destination, limit, arg);
        PIXCopyEventArguments(destination, limit, args...);
#else
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyStringArgument(destination, limit, arg);
        PIXCopyEventArguments(destination, limit, args...);
#endif
    }

    inline UINT8 PIXGetEventSize(const UINT64* end, const UINT64* start)
    {
        const UINT64 actualEventSize = end - start;

        return static_cast<UINT8>(actualEventSize > PIXEventsSizeMax ? PIXEventsSizeMax : actualEventSize);
    }

    template<typename STR>
    inline UINT8 PIXEncodeStringIsAnsi()
    {
        return PIX_EVENT_METADATA_NONE;
    }

    template<>
    inline UINT8 PIXEncodeStringIsAnsi<char*>()
    {
        return PIX_EVENT_METADATA_STRING_IS_ANSI;
    }

    template<>
    inline UINT8 PIXEncodeStringIsAnsi<const char*>()
    {
        return PIX_EVENT_METADATA_STRING_IS_ANSI;
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXBeginEventAllocate(PIXEventsThreadInfo* threadInfo, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
            return;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;
        if (destination >= limit)
            return;

        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64* eventDestination = destination++;
        *destination++ = color;

        PIXCopyStringArguments(destination, limit, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIX_EVENT_METADATA_HAS_COLOR |
            PIXEncodeStringIsAnsi<STR>();
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXBeginEvent(UINT64 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                UINT64* eventDestination = destination++;
                *destination++ = color;

                PIXCopyStringArguments(destination, limit, formatString, args...);
                *destination = PIXEventsBlockEndMarker;

                const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
                const UINT8 eventMetadata =
                    PIX_EVENT_METADATA_HAS_COLOR |
                    PIXEncodeStringIsAnsi<STR>();
                *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

                threadInfo->destination = destination;
            }
            else
            {
                PIXBeginEventAllocate(threadInfo, color, formatString, args...);
            }
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXBeginEventAllocate(PIXEventsThreadInfo* threadInfo, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
            return;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;
        if (destination >= limit)
            return;

        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64* eventDestination = destination++;

        PIXCopyStringArguments(destination, limit, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIXEncodeStringIsAnsi<STR>() |
            PIXEncodeIndexColor(color);
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXBeginEvent(UINT8 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                UINT64* eventDestination = destination++;

                PIXCopyStringArguments(destination, limit, formatString, args...);
                *destination = PIXEventsBlockEndMarker;

                const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
                const UINT8 eventMetadata =
                    PIXEncodeStringIsAnsi<STR>() |
                    PIXEncodeIndexColor(color);
                *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

                threadInfo->destination = destination;
            }
            else
            {
                PIXBeginEventAllocate(threadInfo, color, formatString, args...);
            }
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXSetMarkerAllocate(PIXEventsThreadInfo* threadInfo, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
            return;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
            return;

        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64* eventDestination = destination++;
        *destination++ = color;

        PIXCopyStringArguments(destination, limit, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIXEncodeStringIsAnsi<STR>() |
            PIX_EVENT_METADATA_HAS_COLOR;
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXSetMarker(UINT64 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                UINT64* eventDestination = destination++;
                *destination++ = color;

                PIXCopyStringArguments(destination, limit, formatString, args...);
                *destination = PIXEventsBlockEndMarker;

                const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
                const UINT8 eventMetadata =
                    PIXEncodeStringIsAnsi<STR>() |
                    PIX_EVENT_METADATA_HAS_COLOR;
                *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

                threadInfo->destination = destination;
            }
            else
            {
                PIXSetMarkerAllocate(threadInfo, color, formatString, args...);
            }
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXSetMarkerAllocate(PIXEventsThreadInfo* threadInfo, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
            return;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
            return;

        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64* eventDestination = destination++;

        PIXCopyStringArguments(destination, limit, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIXEncodeStringIsAnsi<STR>() |
            PIXEncodeIndexColor(color);
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXSetMarker(UINT8 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                UINT64* eventDestination = destination++;

                PIXCopyStringArguments(destination, limit, formatString, args...);
                *destination = PIXEventsBlockEndMarker;

                const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
                const UINT8 eventMetadata =
                    PIXEncodeStringIsAnsi<STR>() |
                    PIXEncodeIndexColor(color);
                *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

                threadInfo->destination = destination;
            }
            else
            {
                PIXSetMarkerAllocate(threadInfo, color, formatString, args...);
            }
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXBeginEventOnContextCpuAllocate(UINT64*& eventDestination, UINT8& eventSize, PIXEventsThreadInfo* threadInfo, void* context, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
        {
            eventDestination = nullptr;
            return;
        }

        limit += PIXEventsSafeFastCopySpaceQwords;
        eventDestination = destination++;
        *destination++ = color;

        PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIX_EVENT_METADATA_ON_CONTEXT |
            PIXEncodeStringIsAnsi<STR>() |
            PIX_EVENT_METADATA_HAS_COLOR;
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXBeginEventOnContextCpu(UINT64*& eventDestination, UINT8& eventSize, void* context, UINT64 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit == nullptr)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        if (destination < limit)
        {
            limit += PIXEventsSafeFastCopySpaceQwords;
            UINT64 time = PIXGetTimestampCounter();
            eventDestination = destination++;
            *destination++ = color;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = PIXEventsBlockEndMarker;

            eventSize = PIXGetEventSize(destination, threadInfo->destination);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIX_EVENT_METADATA_HAS_COLOR;
            *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

            threadInfo->destination = destination;
        }
        else
        {
            PIXBeginEventOnContextCpuAllocate(eventDestination, eventSize, threadInfo, context, color, formatString, args...);
        }
    }

    template<typename CONTEXT, typename STR, typename... ARGS>
    void PIXBeginEvent(CONTEXT* context, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64* destination = nullptr;
        UINT8 eventSize = 0u;

#ifdef PIX_CONTEXT_EMIT_CPU_EVENTS
        PIXBeginEventOnContextCpu(destination, eventSize, context, color, formatString, args...);
#endif

#ifdef PIX_USE_GPU_MARKERS_V2
        if (destination != nullptr)
        {
            PIXInsertTimingMarkerOnContextForBeginEvent(context, PIXEvent_BeginEvent, static_cast<void*>(destination), eventSize * sizeof(UINT64));
        }
        else
#endif
        {
            UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];

#ifdef PIX_USE_GPU_MARKERS_V2
            destination = buffer;
            UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

            UINT64* eventDestination = destination++;
            *destination++ = color;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = 0ull;

            eventSize = static_cast<const UINT8>(destination - buffer);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIX_EVENT_METADATA_HAS_COLOR;
            *eventDestination = PIXEncodeEventInfo(0, PIXEvent_BeginEvent, eventSize, eventMetadata);
            PIXInsertGPUMarkerOnContextForBeginEvent(context, PIXEvent_BeginEvent, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#else
            destination = PixEventsLegacy::EncodeBeginEventForContext(buffer, color, formatString, args...);
            PIXBeginGPUEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#endif
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXBeginEventOnContextCpuAllocate(UINT64*& eventDestination, UINT8& eventSize, PIXEventsThreadInfo* threadInfo, void* context, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
        {
            eventDestination = nullptr;
            return;
        }

        limit += PIXEventsSafeFastCopySpaceQwords;
        eventDestination = destination++;

        PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIX_EVENT_METADATA_ON_CONTEXT |
            PIXEncodeStringIsAnsi<STR>() |
            PIXEncodeIndexColor(color);
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXBeginEventOnContextCpu(UINT64*& eventDestination, UINT8& eventSize, void* context, UINT8 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit == nullptr)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        if (destination < limit)
        {
            limit += PIXEventsSafeFastCopySpaceQwords;
            UINT64 time = PIXGetTimestampCounter();
            eventDestination = destination++;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = PIXEventsBlockEndMarker;

            eventSize = PIXGetEventSize(destination, threadInfo->destination);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIXEncodeIndexColor(color);
            *eventDestination = PIXEncodeEventInfo(time, PIXEvent_BeginEvent, eventSize, eventMetadata);

            threadInfo->destination = destination;
        }
        else
        {
            PIXBeginEventOnContextCpuAllocate(eventDestination, eventSize, threadInfo, context, color, formatString, args...);
        }
    }

    template<typename CONTEXT, typename STR, typename... ARGS>
    void PIXBeginEvent(CONTEXT* context, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64* destination = nullptr;
        UINT8 eventSize = 0u;

#ifdef PIX_CONTEXT_EMIT_CPU_EVENTS
        PIXBeginEventOnContextCpu(destination, eventSize, context, color, formatString, args...);
#endif

#ifdef PIX_USE_GPU_MARKERS_V2
        if (destination != nullptr)
        {
            PIXInsertTimingMarkerOnContextForBeginEvent(context, PIXEvent_BeginEvent, static_cast<void*>(destination), eventSize * sizeof(UINT64));
        }
        else
#endif
        {
            UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];

#ifdef PIX_USE_GPU_MARKERS_V2
            destination = buffer;
            UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

            UINT64* eventDestination = destination++;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = 0ull;

            eventSize = static_cast<const UINT8>(destination - buffer);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIXEncodeIndexColor(color);
            *eventDestination = PIXEncodeEventInfo(0, PIXEvent_BeginEvent, eventSize, eventMetadata);

            PIXInsertGPUMarkerOnContextForBeginEvent(context, PIXEvent_BeginEvent, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#else
            destination = PixEventsLegacy::EncodeBeginEventForContext(buffer, color, formatString, args...);
            PIXBeginGPUEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#endif
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXSetMarkerOnContextCpuAllocate(UINT64*& eventDestination, UINT8& eventSize, PIXEventsThreadInfo* threadInfo, void* context, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
        {
            eventDestination = nullptr;
            return;
        }

        limit += PIXEventsSafeFastCopySpaceQwords;
        eventDestination = destination++;
        *destination++ = color;

        PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIX_EVENT_METADATA_ON_CONTEXT |
            PIXEncodeStringIsAnsi<STR>() |
            PIX_EVENT_METADATA_HAS_COLOR;
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXSetMarkerOnContextCpu(UINT64*& eventDestination, UINT8& eventSize, void* context, UINT64 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit == nullptr)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        if (destination < limit)
        {
            limit += PIXEventsSafeFastCopySpaceQwords;
            UINT64 time = PIXGetTimestampCounter();
            eventDestination = destination++;
            *destination++ = color;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = PIXEventsBlockEndMarker;

            eventSize = PIXGetEventSize(destination, threadInfo->destination);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIX_EVENT_METADATA_HAS_COLOR;
            *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

            threadInfo->destination = destination;
        }
        else
        {
            PIXSetMarkerOnContextCpuAllocate(eventDestination, eventSize, threadInfo, context, color, formatString, args...);
        }
    }

    template<typename CONTEXT, typename STR, typename... ARGS>
    void PIXSetMarker(CONTEXT* context, UINT64 color, STR formatString, ARGS... args)
    {
        UINT64* destination = nullptr;
        UINT8 eventSize = 0u;

#ifdef PIX_CONTEXT_EMIT_CPU_EVENTS
        PIXSetMarkerOnContextCpu(destination, eventSize, context, color, formatString, args...);
#endif

#ifdef PIX_USE_GPU_MARKERS_V2
        if (destination != nullptr)
        {
            PIXInsertTimingMarkerOnContextForSetMarker(context, PIXEvent_SetMarker, static_cast<void*>(destination), eventSize * sizeof(UINT64));
        }
        else
#endif
        {
            UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];

#ifdef PIX_USE_GPU_MARKERS_V2
            destination = buffer;
            UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

            UINT64* eventDestination = destination++;
            *destination++ = color;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = 0ull;

            eventSize = static_cast<const UINT8>(destination - buffer);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIX_EVENT_METADATA_HAS_COLOR;
            *eventDestination = PIXEncodeEventInfo(0, PIXEvent_SetMarker, eventSize, eventMetadata);
            PIXInsertGPUMarkerOnContextForSetMarker(context, PIXEvent_SetMarker, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#else
            destination = PixEventsLegacy::EncodeSetMarkerForContext(buffer, color, formatString, args...);
            PIXSetGPUMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#endif
        }
    }

    template<typename STR, typename... ARGS>
    __declspec(noinline) void PIXSetMarkerOnContextCpuAllocate(UINT64*& eventDestination, UINT8& eventSize, PIXEventsThreadInfo* threadInfo, void* context, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, false);
        if (!time)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
        {
            eventDestination = nullptr;
            return;
        }

        limit += PIXEventsSafeFastCopySpaceQwords;
        eventDestination = destination++;

        PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
        *destination = PIXEventsBlockEndMarker;

        eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata =
            PIX_EVENT_METADATA_ON_CONTEXT |
            PIXEncodeStringIsAnsi<STR>() |
            PIXEncodeIndexColor(color);
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

        threadInfo->destination = destination;
    }

    template<typename STR, typename... ARGS>
    void PIXSetMarkerOnContextCpu(UINT64*& eventDestination, UINT8& eventSize, void* context, UINT8 color, STR formatString, ARGS... args)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit == nullptr)
        {
            eventDestination = nullptr;
            return;
        }

        UINT64* destination = threadInfo->destination;
        if (destination < limit)
        {
            limit += PIXEventsSafeFastCopySpaceQwords;
            UINT64 time = PIXGetTimestampCounter();
            eventDestination = destination++;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = PIXEventsBlockEndMarker;

            eventSize = PIXGetEventSize(destination, threadInfo->destination);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIXEncodeIndexColor(color);
            *eventDestination = PIXEncodeEventInfo(time, PIXEvent_SetMarker, eventSize, eventMetadata);

            threadInfo->destination = destination;
        }
        else
        {
            PIXSetMarkerOnContextCpuAllocate(eventDestination, eventSize, threadInfo, context, color, formatString, args...);
        }
    }

    template<typename CONTEXT, typename STR, typename... ARGS>
    void PIXSetMarker(CONTEXT* context, UINT8 color, STR formatString, ARGS... args)
    {
        UINT64* destination = nullptr;
        UINT8 eventSize = 0u;

#ifdef PIX_CONTEXT_EMIT_CPU_EVENTS
        PIXSetMarkerOnContextCpu(destination, eventSize, context, color, formatString, args...);
#endif

#ifdef PIX_USE_GPU_MARKERS_V2
        if (destination != nullptr)
        {
            PIXInsertTimingMarkerOnContextForSetMarker(context, PIXEvent_SetMarker, static_cast<void*>(destination), eventSize * sizeof(UINT64));
        }
        else
#endif
        {
            UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];

#ifdef PIX_USE_GPU_MARKERS_V2
            destination = buffer;
            UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

            UINT64* eventDestination = destination++;

            PIXCopyStringArgumentsWithContext(destination, limit, context, formatString, args...);
            *destination = 0ull;

            eventSize = static_cast<const UINT8>(destination - buffer);
            const UINT8 eventMetadata =
                PIX_EVENT_METADATA_ON_CONTEXT |
                PIXEncodeStringIsAnsi<STR>() |
                PIXEncodeIndexColor(color);
            *eventDestination = PIXEncodeEventInfo(0, PIXEvent_SetMarker, eventSize, eventMetadata);
            PIXInsertGPUMarkerOnContextForSetMarker(context, PIXEvent_SetMarker, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#else
            destination = PixEventsLegacy::EncodeSetMarkerForContext(buffer, color, formatString, args...);
            PIXSetGPUMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#endif
        }
    }

    __declspec(noinline) inline void PIXEndEventAllocate(PIXEventsThreadInfo* threadInfo)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, true);
        if (!time)
            return;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
            return;

        limit += PIXEventsSafeFastCopySpaceQwords;
        const UINT8 eventSize = 1;
        const UINT8 eventMetadata = PIX_EVENT_METADATA_NONE;
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent, eventSize, eventMetadata);
        *destination = PIXEventsBlockEndMarker;

        threadInfo->destination = destination;
    }

    inline void PIXEndEvent()
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                const UINT8 eventSize = 1;
                const UINT8 eventMetadata = PIX_EVENT_METADATA_NONE;
                *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent, eventSize, eventMetadata);
                *destination = PIXEventsBlockEndMarker;

                threadInfo->destination = destination;
            }
            else
            {
                PIXEndEventAllocate(threadInfo);
            }
        }
    }

    __declspec(noinline) inline UINT64* PIXEndEventOnContextCpuAllocate(PIXEventsThreadInfo* threadInfo, void* context)
    {
        UINT64 time = PIXEventsReplaceBlock(threadInfo, true);
        if (!time)
            return nullptr;

        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->biasedLimit;

        if (destination >= limit)
            return nullptr;

        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64* eventDestination = destination++;
#ifdef PIX_XBOX
        UNREFERENCED_PARAMETER(context);
#else
        PIXCopyEventArgument(destination, limit, context);
#endif
        * destination = PIXEventsBlockEndMarker;

        const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
        const UINT8 eventMetadata = PIX_EVENT_METADATA_ON_CONTEXT;
        *eventDestination = PIXEncodeEventInfo(time, PIXEvent_EndEvent, eventSize, eventMetadata);

        threadInfo->destination = destination;

        return eventDestination;
    }

    inline UINT64* PIXEndEventOnContextCpu(void* context)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* limit = threadInfo->biasedLimit;
        if (limit != nullptr)
        {
            UINT64* destination = threadInfo->destination;
            if (destination < limit)
            {
                limit += PIXEventsSafeFastCopySpaceQwords;
                UINT64 time = PIXGetTimestampCounter();
                UINT64* eventDestination = destination++;
#ifndef PIX_XBOX
                PIXCopyEventArgument(destination, limit, context);
#endif
                * destination = PIXEventsBlockEndMarker;

                const UINT8 eventSize = PIXGetEventSize(destination, threadInfo->destination);
                const UINT8 eventMetadata = PIX_EVENT_METADATA_ON_CONTEXT;
                *eventDestination = PIXEncodeEventInfo(time, PIXEvent_EndEvent, eventSize, eventMetadata);

                threadInfo->destination = destination;

                return eventDestination;
            }
            else
            {
                return PIXEndEventOnContextCpuAllocate(threadInfo, context);
            }
        }

        return nullptr;
    }

    template<typename CONTEXT>
    void PIXEndEvent(CONTEXT* context)
    {
        UINT64* destination = nullptr;
#ifdef PIX_CONTEXT_EMIT_CPU_EVENTS
        destination = PIXEndEventOnContextCpu(context);
#endif

#ifdef PIX_USE_GPU_MARKERS_V2
        if (destination != nullptr)
        {
            PIXInsertTimingMarkerOnContextForEndEvent(context, PIXEvent_EndEvent);
        }
        else
#endif
        {
#ifdef PIX_USE_GPU_MARKERS_V2
            UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
            destination = buffer;

            UINT64* eventDestination = destination++;

            const UINT8 eventSize = static_cast<const UINT8>(destination - buffer);
            const UINT8 eventMetadata = PIX_EVENT_METADATA_NONE;
            *eventDestination = PIXEncodeEventInfo(0, PIXEvent_EndEvent, eventSize, eventMetadata);
            PIXInsertGPUMarkerOnContextForEndEvent(context, PIXEvent_EndEvent, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
#else
            PIXEndGPUEventOnContext(context);
#endif
        }
    }
}

#if defined(USE_PIX)

template<typename... ARGS>
void PIXBeginEvent(UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(color, formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(color, formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(color, formatString, args...);
}

template<typename... ARGS>
void PIXBeginEvent(UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(color, formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(color, formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(color, formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(static_cast<UINT64>(color), formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(color, formatString, args...);
}

template<typename... ARGS>
void PIXSetMarker(UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginEvent(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetMarker(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

inline void PIXEndEvent()
{
    PIXEventsDetail::PIXEndEvent();
}

template<typename CONTEXT>
void PIXEndEvent(CONTEXT* context)
{
    PIXEventsDetail::PIXEndEvent(context);
}

#else // USE_PIX_RETAIL

inline void PIXBeginEvent(UINT64, _In_ PCSTR, ...) {}
inline void PIXBeginEvent(UINT64, _In_ PCWSTR, ...) {}
inline void PIXBeginEvent(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXBeginEvent(void*, UINT64, _In_ PCWSTR, ...) {}
inline void PIXEndEvent() {}
inline void PIXEndEvent(void*) {}
inline void PIXSetMarker(UINT64, _In_ PCSTR, ...) {}
inline void PIXSetMarker(UINT64, _In_ PCWSTR, ...) {}
inline void PIXSetMarker(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXSetMarker(void*, UINT64, _In_ PCWSTR, ...) {}

#endif // USE_PIX

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXBeginRetailEvent(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXBeginEvent(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, static_cast<UINT64>(color), formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT, typename... ARGS>
void PIXSetRetailMarker(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
{
    PIXEventsDetail::PIXSetMarker(context, color, formatString, args...);
}

template<typename CONTEXT>
void PIXEndRetailEvent(CONTEXT* context)
{
    PIXEventsDetail::PIXEndEvent(context);
}

template<typename CONTEXT>
class PIXScopedEventObject
{
    CONTEXT* m_context;

public:
    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginEvent(m_context, color, formatString, args...);
    }

    ~PIXScopedEventObject()
    {
        PIXEndEvent(m_context);
    }
};

template<typename CONTEXT>
class PIXScopedRetailEventObject
{
    CONTEXT* m_context;

public:
    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT64 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT64 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT32 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT32 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, INT32 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, INT32 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, DWORD color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, DWORD color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT8 color, PCWSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedRetailEventObject(CONTEXT* context, UINT8 color, PCSTR formatString, ARGS... args)
        : m_context(context)
    {
        PIXBeginRetailEvent(m_context, color, formatString, args...);
    }

    ~PIXScopedRetailEventObject()
    {
        PIXEndRetailEvent(m_context);
    }
};

template<>
class PIXScopedEventObject<void>
{
public:
    template<typename... ARGS>
    PIXScopedEventObject(UINT64 color, PCWSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(UINT64 color, PCSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(UINT32 color, PCWSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(UINT32 color, PCSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(INT32 color, PCWSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(INT32 color, PCSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(DWORD color, PCWSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(DWORD color, PCSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(UINT8 color, PCWSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    template<typename... ARGS>
    PIXScopedEventObject(UINT8 color, PCSTR formatString, ARGS... args)
    {
        PIXBeginEvent(color, formatString, args...);
    }

    ~PIXScopedEventObject()
    {
        PIXEndEvent();
    }
};

#define PIXConcatenate(a, b) a ## b
#define PIXGetScopedEventVariableName(a, b) PIXConcatenate(a, b)
#define PIXScopedEvent(context, ...) PIXScopedEventObject<PIXInferScopedEventType<decltype(context)>::Type> PIXGetScopedEventVariableName(pixEvent, __LINE__)(context, __VA_ARGS__)

#ifdef PIX3__DEFINED_CONSTEXPR
#undef constexpr
#undef PIX3__DEFINED_CONSTEXPR
#endif

#endif // _PIXEvents_H__


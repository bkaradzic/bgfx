//This is a generated file.
#pragma once

#ifndef _PIXEventsGenerated_H_
#define _PIXEventsGenerated_H_

#ifndef _PIX3_H_
#error Don't include this file directly - use pix3.h
#endif

#include "PIXEventsCommon.h"

//__declspec(noinline) is specified to stop compiler from making bad inlining decisions
//inline has to be specified for functions fully defined in header due to one definition rule
//supported context types for TContext are ID3D11DeviceContextX, ID3D11ComputeContextX and ID3D11DmaEngineContextX

__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void PIXBeginEventAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_NoArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString);
    }
}

template<class T1>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1);
    }
}

template<class T1, class T2>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXBeginEvent(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_NoArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString);
    }
}

template<class T1>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1);
    }
}

template<class T1, class T2>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXBeginEvent(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXBeginEventAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void PIXSetMarkerAllocate(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_NoArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString);
    }
}

template<class T1>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1);
    }
}

template<class T1, class T2>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXSetMarker(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_NoArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString);
    }
}

template<class T1>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1);
    }
}

template<class T1, class T2>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXSetMarker(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_VarArgs);
        *destination++ = color;

        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXSetMarkerAllocate(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

template<class TContext>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString)
{
    PIXBeginCPUEventOnContext(context, color, formatString);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_NoArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    PIXCopyEventArgument(destination, limit, a16);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString)
{
    PIXBeginCPUEventOnContext(context, color, formatString);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_NoArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXBeginEvent(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXBeginCPUEventOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_BeginEvent_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    PIXCopyEventArgument(destination, limit, a16);
    *destination = 0ull;
    PIXBeginEventOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString)
{
    PIXSetCPUMarkerOnContext(context, color, formatString);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_NoArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    PIXCopyEventArgument(destination, limit, a16);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString)
{
    PIXSetCPUMarkerOnContext(context, color, formatString);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_NoArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

template<class TContext, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void PIXSetMarker(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXSetCPUMarkerOnContext(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);

    UINT64 buffer[PIXEventsGraphicsRecordSpaceQwords];
    UINT64* destination = buffer;
    UINT64* limit = buffer + PIXEventsGraphicsRecordSpaceQwords - PIXEventsReservedTailSpaceQwords;

    *destination++ = PIXEncodeEventInfo(0, PIXEvent_SetMarker_VarArgs);
    *destination++ = color;

    PIXCopyEventArgument(destination, limit, formatString);
    PIXCopyEventArgument(destination, limit, a1);
    PIXCopyEventArgument(destination, limit, a2);
    PIXCopyEventArgument(destination, limit, a3);
    PIXCopyEventArgument(destination, limit, a4);
    PIXCopyEventArgument(destination, limit, a5);
    PIXCopyEventArgument(destination, limit, a6);
    PIXCopyEventArgument(destination, limit, a7);
    PIXCopyEventArgument(destination, limit, a8);
    PIXCopyEventArgument(destination, limit, a9);
    PIXCopyEventArgument(destination, limit, a10);
    PIXCopyEventArgument(destination, limit, a11);
    PIXCopyEventArgument(destination, limit, a12);
    PIXCopyEventArgument(destination, limit, a13);
    PIXCopyEventArgument(destination, limit, a14);
    PIXCopyEventArgument(destination, limit, a15);
    PIXCopyEventArgument(destination, limit, a16);
    *destination = 0ull;
    PIXSetMarkerOnContext(context, static_cast<void*>(buffer), static_cast<UINT>(reinterpret_cast<BYTE*>(destination) - reinterpret_cast<BYTE*>(buffer)));
}

__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline)  inline void MakeCPUSetMarkerForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);

            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_NoArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString);
    }
}

template<class T1>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1);
    }
}

template<class T1, class T2>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_NoArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString);
    }
}

template<class T1>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1);
    }
}

template<class T1, class T2>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void MakeCPUSetMarkerForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_SetMarker_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUSetMarkerForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}


__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_NoArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
__declspec(noinline) inline void MakeCPUBeginEventForContextAllocate(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    UINT64 time = PIXEventsReplaceBlock(false);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
            *destination++ = color;

            PIXCopyEventArgument(destination, limit, context);
            PIXCopyEventArgument(destination, limit, formatString);
            PIXCopyEventArgument(destination, limit, a1);
            PIXCopyEventArgument(destination, limit, a2);
            PIXCopyEventArgument(destination, limit, a3);
            PIXCopyEventArgument(destination, limit, a4);
            PIXCopyEventArgument(destination, limit, a5);
            PIXCopyEventArgument(destination, limit, a6);
            PIXCopyEventArgument(destination, limit, a7);
            PIXCopyEventArgument(destination, limit, a8);
            PIXCopyEventArgument(destination, limit, a9);
            PIXCopyEventArgument(destination, limit, a10);
            PIXCopyEventArgument(destination, limit, a11);
            PIXCopyEventArgument(destination, limit, a12);
            PIXCopyEventArgument(destination, limit, a13);
            PIXCopyEventArgument(destination, limit, a14);
            PIXCopyEventArgument(destination, limit, a15);
            PIXCopyEventArgument(destination, limit, a16);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_NoArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString);
    }
}

template<class T1>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1);
    }
}

template<class T1, class T2>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}

inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_NoArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString);
    }
}

template<class T1>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1);
    }
}

template<class T1, class T2>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2);
    }
}

template<class T1, class T2, class T3>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3);
    }
}

template<class T1, class T2, class T3, class T4>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4);
    }
}

template<class T1, class T2, class T3, class T4, class T5>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
inline void MakeCPUBeginEventForContext(UINT64 color, PVOID context, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_BeginEvent_OnContext_VarArgs);
        *destination++ = color;
        
        PIXCopyEventArgument(destination, limit, context);
        PIXCopyEventArgument(destination, limit, formatString);
        PIXCopyEventArgument(destination, limit, a1);
        PIXCopyEventArgument(destination, limit, a2);
        PIXCopyEventArgument(destination, limit, a3);
        PIXCopyEventArgument(destination, limit, a4);
        PIXCopyEventArgument(destination, limit, a5);
        PIXCopyEventArgument(destination, limit, a6);
        PIXCopyEventArgument(destination, limit, a7);
        PIXCopyEventArgument(destination, limit, a8);
        PIXCopyEventArgument(destination, limit, a9);
        PIXCopyEventArgument(destination, limit, a10);
        PIXCopyEventArgument(destination, limit, a11);
        PIXCopyEventArgument(destination, limit, a12);
        PIXCopyEventArgument(destination, limit, a13);
        PIXCopyEventArgument(destination, limit, a14);
        PIXCopyEventArgument(destination, limit, a15);
        PIXCopyEventArgument(destination, limit, a16);

        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUBeginEventForContextAllocate(color, context, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }
}


__declspec(noinline) inline void PIXEndEventAllocate()
{
    UINT64 time = PIXEventsReplaceBlock(true);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void PIXEndEvent()
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->limit;
    if (destination < limit)
    {
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent);
        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        PIXEndEventAllocate();
    }
}

__declspec(noinline) inline void MakeCPUEndEventForContextAllocate(PVOID context)
{
    UINT64 time = PIXEventsReplaceBlock(true);
    if (time)
    {
        PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
        UINT64* destination = threadInfo->destination;
        UINT64* limit = threadInfo->limit;
        if (destination < limit)
        {
            *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent_OnContext);
            PIXCopyEventArgument(destination, limit, context);
            *destination = PIXEventsBlockEndMarker;
            threadInfo->destination = destination;
        }
    }
}

inline void MakeCPUEndEventForContext(PVOID context)
{
    PIXEventsThreadInfo* threadInfo = PIXGetThreadInfo();
    UINT64* destination = threadInfo->destination;
    UINT64* limit = threadInfo->biasedLimit;
    if (destination < limit)
    {
        limit += PIXEventsSafeFastCopySpaceQwords;
        UINT64 time = PIXGetTimestampCounter();
        *destination++ = PIXEncodeEventInfo(time, PIXEvent_EndEvent_OnContext);
        PIXCopyEventArgument(destination, limit, context);
        *destination = PIXEventsBlockEndMarker;
        threadInfo->destination = destination;
    }
    else if (limit != nullptr)
    {
        MakeCPUEndEventForContextAllocate(context);
    }
}

template<class TContext>
inline void PIXEndEvent(TContext* context)
{
    PIXEndCPUEventOnContext(context);
    PIXEndEventOnContext(context);
}

template<class TContext>
class PIXScopedEventObject
{
private:
    TContext* m_context;

public:
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString);
    }

    template<class T1>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1);
    }

    template<class T1, class T2>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2);
    }

    template<class T1, class T2, class T3>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3);
    }

    template<class T1, class T2, class T3, class T4>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4);
    }

    template<class T1, class T2, class T3, class T4, class T5>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }

    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString);
    }

    template<class T1>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1);
    }

    template<class T1, class T2>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2);
    }

    template<class T1, class T2, class T3>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3);
    }

    template<class T1, class T2, class T3, class T4>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4);
    }

    template<class T1, class T2, class T3, class T4, class T5>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
    PIXScopedEventObject(TContext* context, UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
        : m_context(context)
    {
        PIXBeginEvent(context, color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }

    ~PIXScopedEventObject()
    {
        PIXEndEvent(m_context);
    }
};

template<>
class PIXScopedEventObject<void>
{
public:
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString)
    {
        PIXBeginEvent(color, formatString);
    }

    template<class T1>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1)
    {
        PIXBeginEvent(color, formatString, a1);
    }

    template<class T1, class T2>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2)
    {
        PIXBeginEvent(color, formatString, a1, a2);
    }

    template<class T1, class T2, class T3>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3);
    }

    template<class T1, class T2, class T3, class T4>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4);
    }

    template<class T1, class T2, class T3, class T4, class T5>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
    PIXScopedEventObject(UINT64 color, _In_ PCSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }

    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString)
    {
        PIXBeginEvent(color, formatString);
    }

    template<class T1>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1)
    {
        PIXBeginEvent(color, formatString, a1);
    }

    template<class T1, class T2>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2)
    {
        PIXBeginEvent(color, formatString, a1, a2);
    }

    template<class T1, class T2, class T3>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3);
    }

    template<class T1, class T2, class T3, class T4>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4);
    }

    template<class T1, class T2, class T3, class T4, class T5>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
    PIXScopedEventObject(UINT64 color, _In_ PCWSTR formatString, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9, T10 a10, T11 a11, T12 a12, T13 a13, T14 a14, T15 a15, T16 a16)
    {
        PIXBeginEvent(color, formatString, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    }

    ~PIXScopedEventObject()
    {
        PIXEndEvent();
    }
};

#define PIXConcatenate(a, b) a ## b
#define PIXGetScopedEventVariableName(a, b) PIXConcatenate(a, b)
#define PIXScopedEvent(context, ...) PIXScopedEventObject<PIXInferScopedEventType<decltype(context)>::Type> PIXGetScopedEventVariableName(pixEvent, __LINE__)(context, __VA_ARGS__)

#endif

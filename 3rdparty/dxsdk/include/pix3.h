/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       pix3.h
 *  Content:    PIX include file
 *
 ****************************************************************************/
#pragma once

#ifndef _PIX3_H_
#define _PIX3_H_

#include <sal.h>

#ifndef __cplusplus
#error "Only C++ files can include pix.h. C is not supported."
#endif

#if defined(XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#include "pix3_xbox.h"
#else
#include "pix3_win.h"
#endif

//
// The PIX event/marker APIs compile to nothing on retail builds and on x86 builds
//
#if (!defined(USE_PIX)) && ((defined(_DEBUG) || DBG || (defined(PROFILE) && !defined(FASTCAP)) || defined(PROFILE_BUILD)) && !defined(i386) && defined(_AMD64_) && !defined(_PREFAST_))
#define USE_PIX
#endif

#if defined(USE_PIX) && !defined(_AMD64_) && !defined(USE_PIX_ON_ALL_ARCHITECTURES)
#pragma message("Warning: Pix markers are only supported on AMD64")
#endif

// These flags are used by both PIXBeginCapture and PIXGetCaptureState
#define PIX_CAPTURE_TIMING                  (1 << 0)
#define PIX_CAPTURE_GPU                     (1 << 1)
#define PIX_CAPTURE_FUNCTION_SUMMARY        (1 << 2)
#define PIX_CAPTURE_FUNCTION_DETAILS        (1 << 3)
#define PIX_CAPTURE_CALLGRAPH               (1 << 4)
#define PIX_CAPTURE_INSTRUCTION_TRACE       (1 << 5)
#define PIX_CAPTURE_SYSTEM_MONITOR_COUNTERS (1 << 6)
#define PIX_CAPTURE_VIDEO                   (1 << 7)
#define PIX_CAPTURE_AUDIO                   (1 << 8)

typedef union PIXCaptureParameters
{
    struct GpuCaptureParameters
    {
        PVOID reserved;
    } GpuCaptureParameters;

    struct TimingCaptureParameters
    {
        BOOL CaptureCallstacks;
        PWSTR FileName;
    } TimingCaptureParameters;

} PIXCaptureParameters, *PPIXCaptureParameters;



#if defined (USE_PIX) && (defined(_AMD64_) || defined(USE_PIX_ON_ALL_ARCHITECTURES))

#include "PIXEventsCommon.h"
#include "PIXEventsGenerated.h"

// Starts a programmatically controlled capture.
// captureFlags uses the PIX_CAPTURE_* family of flags to specify the type of capture to take
extern "C" HRESULT WINAPI PIXBeginCapture(DWORD captureFlags, _In_opt_ const PPIXCaptureParameters captureParameters);

// Stops a programmatically controlled capture
//  If discard == TRUE, the captured data is discarded
//  If discard == FALSE, the captured data is saved
extern "C" HRESULT WINAPI PIXEndCapture(BOOL discard);

extern "C" DWORD WINAPI PIXGetCaptureState();

extern "C" void WINAPI PIXReportCounter(_In_ PCWSTR name, float value);

#else

// Eliminate these APIs when not using PIX
inline HRESULT PIXBeginCapture(DWORD, _In_opt_ const PIXCaptureParameters*) { return S_OK; }
inline HRESULT PIXEndCapture(BOOL) { return S_OK; }
inline DWORD PIXGetCaptureState() { return 0; }
inline void PIXReportCounter(_In_ PCWSTR, float) {}

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
inline void PIXScopedEvent(UINT64, _In_ PCSTR, ...) {}
inline void PIXScopedEvent(UINT64, _In_ PCWSTR, ...) {}
inline void PIXScopedEvent(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXScopedEvent(void*, UINT64, _In_ PCWSTR, ...) {}

#endif // USE_PIX

// Use these functions to specify colors to pass as metadata to a PIX event/marker API.
// Use PIX_COLOR() to specify a particular color for an event.
// Or, use PIX_COLOR_INDEX() to specify a set of unique event categories, and let PIX choose
// the colors to represent each category.
inline UINT PIX_COLOR(BYTE r, BYTE g, BYTE b) { return 0xff000000 | (r << 16) | (g << 8) | b; }
inline UINT PIX_COLOR_INDEX(BYTE i) { return i; }
const UINT PIX_COLOR_DEFAULT = PIX_COLOR_INDEX(0);

#endif // _PIX3_H_

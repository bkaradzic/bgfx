// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#ifndef _PIX3_H_
#define _PIX3_H_

#include <sal.h>

#ifndef __cplusplus
#error "Only C++ files can include pix3.h. C is not supported."
#endif

#if !defined(USE_PIX_SUPPORTED_ARCHITECTURE)
#if defined(_M_X64) || defined(USE_PIX_ON_ALL_ARCHITECTURES) || defined(_M_ARM64)
#define USE_PIX_SUPPORTED_ARCHITECTURE
#endif
#endif

#if !defined(USE_PIX)
#if defined(USE_PIX_SUPPORTED_ARCHITECTURE) && (defined(_DEBUG) || DBG || defined(PROFILE) || defined(PROFILE_BUILD)) && !defined(_PREFAST_)
#define USE_PIX
#endif
#endif

#if defined(USE_PIX) && !defined(USE_PIX_SUPPORTED_ARCHITECTURE)
#pragma message("Warning: Pix markers are only supported on AMD64 and ARM64")
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
#define PIX_CAPTURE_GPU_TRACE               (1 << 9)
#define PIX_CAPTURE_RESERVED                (1 << 15)

union PIXCaptureParameters
{
    enum PIXCaptureStorage
    {
        Memory = 0,
        MemoryCircular = 1, // Xbox only
        FileCircular = 2, // PC only
    };

    struct GpuCaptureParameters
    {
        PCWSTR FileName;
    } GpuCaptureParameters;

    struct TimingCaptureParameters
    {
        PCWSTR FileName;
        UINT32 MaximumToolingMemorySizeMb;
        PIXCaptureStorage CaptureStorage;

        BOOL CaptureGpuTiming;

        BOOL CaptureCallstacks;
        BOOL CaptureCpuSamples;
        UINT32 CpuSamplesPerSecond;

        BOOL CaptureFileIO;

        BOOL CaptureVirtualAllocEvents;
        BOOL CaptureHeapAllocEvents;
        BOOL CaptureXMemEvents; // Xbox only
        BOOL CapturePixMemEvents;
        BOOL CapturePageFaultEvents;
        BOOL CaptureVideoFrames; // Xbox only
    } TimingCaptureParameters;

    struct GpuTraceParameters // Xbox Series and newer only
    {
        PWSTR FileName;
        UINT32 MaximumToolingMemorySizeMb;

        BOOL CaptureGpuOccupancy;

    } GpuTraceParameters;
};

typedef PIXCaptureParameters* PPIXCaptureParameters;

#if defined(XBOX) || defined(_XBOX_ONE) || defined(_DURANGO) || defined(_GAMING_XBOX) || defined(_GAMING_XBOX_SCARLETT)
#include "pix3_xbox.h"
#else
#include "pix3_win.h"
#endif

#if defined(XBOX) || defined(_XBOX_ONE) || defined(_DURANGO) || defined(_GAMING_XBOX) || defined(_GAMING_XBOX_SCARLETT)
#define PIX_XBOX
#if defined(_GAMING_XBOX) || defined(_GAMING_XBOX_SCARLETT)
#define PIX_GAMING_XBOX
#endif
#endif

#if !defined(PIX_USE_GPU_MARKERS_V2)
#ifdef PIX_GAMING_XBOX 
#define PIX_USE_GPU_MARKERS_V2
#endif
#endif

#if defined(USE_PIX_SUPPORTED_ARCHITECTURE) && (defined(USE_PIX) || defined(USE_PIX_RETAIL))

#define PIX_EVENTS_ARE_TURNED_ON

#include "PIXEventsCommon.h"
#include "PIXEvents.h"

#ifdef USE_PIX
// Starts a programmatically controlled capture.
// captureFlags uses the PIX_CAPTURE_* family of flags to specify the type of capture to take
extern "C" HRESULT WINAPI PIXBeginCapture2(DWORD captureFlags, _In_opt_ const PPIXCaptureParameters captureParameters);
inline HRESULT PIXBeginCapture(DWORD captureFlags, _In_opt_ const PPIXCaptureParameters captureParameters) { return PIXBeginCapture2(captureFlags, captureParameters); }

// Stops a programmatically controlled capture
//  If discard == TRUE, the captured data is discarded
//  If discard == FALSE, the captured data is saved
//  discard parameter is not supported on Windows
extern "C" HRESULT WINAPI PIXEndCapture(BOOL discard);

extern "C" DWORD WINAPI PIXGetCaptureState();

extern "C" void WINAPI PIXReportCounter(_In_ PCWSTR name, float value);

#endif // USE_PIX

#endif // (USE_PIX_SUPPORTED_ARCHITECTURE) && (USE_PIX || USE_PIX_RETAIL)

#if !defined(USE_PIX_SUPPORTED_ARCHITECTURE) || !defined(USE_PIX)

// Eliminate these APIs when not using PIX
inline HRESULT PIXBeginCapture2(DWORD, _In_opt_ const PIXCaptureParameters*) { return S_OK; }
inline HRESULT PIXBeginCapture(DWORD, _In_opt_ const PIXCaptureParameters*) { return S_OK; }
inline HRESULT PIXEndCapture(BOOL) { return S_OK; }
inline HRESULT PIXGpuCaptureNextFrames(PCWSTR, UINT32) { return S_OK; }
inline HRESULT PIXSetTargetWindow(HWND) { return S_OK; }
inline HRESULT PIXForceD3D11On12() { return S_OK; }
inline HRESULT WINAPI PIXSetHUDOptions(PIXHUDOptions) { return S_OK; }
inline bool WINAPI PIXIsAttachedForGpuCapture() { return false; }
inline HINSTANCE WINAPI PIXOpenCaptureInUI(PCWSTR) { return 0; }
inline HMODULE PIXLoadLatestWinPixGpuCapturerLibrary() { return nullptr; }
inline HMODULE PIXLoadLatestWinPixTimingCapturerLibrary() { return nullptr; }
inline DWORD PIXGetCaptureState() { return 0; }
inline void PIXReportCounter(_In_ PCWSTR, float) {}
inline void PIXNotifyWakeFromFenceSignal(_In_ HANDLE) {}

#if !defined(USE_PIX_RETAIL)

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
inline void PIXBeginRetailEvent(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXBeginRetailEvent(void*, UINT64, _In_ PCWSTR, ...) {}
inline void PIXEndRetailEvent(void*) {}
inline void PIXSetRetailMarker(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXSetRetailMarker(void*, UINT64, _In_ PCWSTR, ...) {}
inline void PIXScopedEvent(UINT64, _In_ PCSTR, ...) {}
inline void PIXScopedEvent(UINT64, _In_ PCWSTR, ...) {}
inline void PIXScopedEvent(void*, UINT64, _In_ PCSTR, ...) {}
inline void PIXScopedEvent(void*, UINT64, _In_ PCWSTR, ...) {}

#endif // !USE_PIX_RETAIL

// don't show warnings about expressions with no effect
#pragma warning(disable:4548)
#pragma warning(disable:4555)

#endif // !USE_PIX_SUPPORTED_ARCHITECTURE || !USE_PIX

// Use these functions to specify colors to pass as metadata to a PIX event/marker API.
// Use PIX_COLOR() to specify a particular color for an event.
// Or, use PIX_COLOR_INDEX() to specify a set of unique event categories, and let PIX choose
// the colors to represent each category.
inline UINT32 PIX_COLOR(UINT8 r, UINT8 g, UINT8 b) { return 0xff000000u | ((UINT32)r << 16) | ((UINT32)g << 8) | (UINT32)b; }
inline UINT8 PIX_COLOR_INDEX(UINT8 i) { return i; }
const UINT8 PIX_COLOR_DEFAULT = PIX_COLOR_INDEX(0);

#endif // _PIX3_H_

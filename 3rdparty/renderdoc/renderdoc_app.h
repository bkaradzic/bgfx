/******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Crytek
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/


#pragma once

#include <stdint.h>

#ifdef WIN32

#ifdef RENDERDOC_EXPORTS
#define RENDERDOC_API __declspec(dllexport)
#else
#define RENDERDOC_API __declspec(dllimport)
#endif
#define RENDERDOC_CC __cdecl

#elif defined(__linux__)

#ifdef RENDERDOC_EXPORTS
#define RENDERDOC_API __attribute__ ((visibility ("default")))
#else
#define RENDERDOC_API
#endif

#define RENDERDOC_CC

#else

#error "Unknown platform"

#endif

struct CaptureOptions
{
	CaptureOptions()
		: AllowVSync(true),
		  AllowFullscreen(true),
		  DebugDeviceMode(false),
		  CaptureCallstacks(false),
		  CaptureCallstacksOnlyDraws(false),
		  DelayForDebugger(0),
		  VerifyMapWrites(false),
		  HookIntoChildren(false),
		  RefAllResources(false),
		  SaveAllInitials(false),
		  CaptureAllCmdLists(false)
	{}

	// Whether or not to allow the application to enable vsync
	//
	// 1 - allows the application to enable or disable vsync at will
	// 0 - vsync is force disabled
	uint32_t AllowVSync;
	
	// Whether or not to allow the application to enable fullscreen
	//
	// 1 - allows the application to enable or disable fullscreen at will
	// 0 - fullscreen is force disabled
	uint32_t AllowFullscreen;

	// 1 - in-built API debugging features and records the results into the
	//     capture logfile, which is matched up with events on replay
	// 0 - no API debugging is enabled
	uint32_t DebugDeviceMode;

	// 1 - Captures callstacks for every API event during capture
	// 0 - no callstacks are captured
	uint32_t CaptureCallstacks;

	// 1 - Only captures callstacks for drawcall type API events.
	//     Ignored if CaptureCallstacks is disabled
	// 0 - Callstacks, if enabled, are captured for every event.
	uint32_t CaptureCallstacksOnlyDraws;

	// Specify a delay in seconds to wait for a debugger to attach after
	// creating or injecting into a process, before continuing to allow it to run.
	// 0 indicates no delay, and the process will run immediately after injection
	uint32_t DelayForDebugger;

	// 1 - Verify any writes to mapped buffers, to check that they don't overwrite the
	//     bounds of the pointer returned.
	// 0 - No verification is performed, and overwriting bounds may cause crashes or
	//     corruption in RenderDoc
	uint32_t VerifyMapWrites;

	// 1 - Hooks any system API events that create child processes, and injects
	//     renderdoc into them recursively with the same options.
	// 0 - Child processes are not hooked by RenderDoc
	uint32_t HookIntoChildren;

	// By default renderdoc only includes resources in the final logfile necessary
	// for that frame, this allows you to override that behaviour
	//
	// 1 - all live resources at the time of capture are included in the log
	//     and available for inspection
	// 0 - only the resources referenced by the captured frame are included
	uint32_t RefAllResources;

	// By default renderdoc skips saving initial states for resources where the
	// previous contents don't appear to be used, assuming that writes before
	// reads indicate previous contents aren't used.
	//
	// 1 - initial contents at the start of each captured frame are saved, even if
	//     they are later overwritten or cleared before being used.
	// 0 - unless a read is detected, initial contents will not be saved and will
	//     appear as black or empty data.
	uint32_t SaveAllInitials;

	// In APIs that allow for the recording of command lists to be replayed later,
	// renderdoc may choose to not capture command lists before a frame capture is
	// triggered, to reduce overheads. This means any command lists recorded once
	// and replayed many times will not be available and may cause a failure to
	// capture.
	//
	// Note this is typically only true for APIs where multithreading is difficult
	// or discouraged. Newer APIs like Vulkan and D3D12 will ignore this option and
	// always capture all command lists since the API is heavily oriented around it,
	// and the overheads have been reduced by API design.
	//
	// 1 - All command lists are captured from the start of the application
	// 0 - Command lists are only captured if their recording begins during
	//     the period when a frame capture is in progress.
	uint32_t CaptureAllCmdLists;
};

enum KeyButton
{
	eKey_0 = 0x30, // '0'
	// ...
	eKey_9 = 0x39, // '9'
	eKey_A = 0x41, // 'A'
	// ...
	eKey_Z = 0x5A, // 'Z'

	eKey_Divide,
	eKey_Multiply,
	eKey_Subtract,
	eKey_Plus,

	eKey_F1,
	eKey_F2,
	eKey_F3,
	eKey_F4,
	eKey_F5,
	eKey_F6,
	eKey_F7,
	eKey_F8,
	eKey_F9,
	eKey_F10,
	eKey_F11,
	eKey_F12,

	eKey_Home,
	eKey_End,
	eKey_Insert,
	eKey_Delete,
	eKey_PageUp,
	eKey_PageDn,

	eKey_Backspace,
	eKey_Tab,
	eKey_PrtScrn,
	eKey_Pause,

	eKey_Max,
};

enum InAppOverlay
{
	eOverlay_Enabled = 0x1,
	eOverlay_FrameRate = 0x2,
	eOverlay_FrameNumber = 0x4,
	eOverlay_CaptureList = 0x8,

	eOverlay_Default = (eOverlay_Enabled|eOverlay_FrameRate|eOverlay_FrameNumber|eOverlay_CaptureList),
	eOverlay_All = ~0U,
	eOverlay_None = 0,
};

////////////////////////////////////////////////
//          !!!! IMPORTANT NOTE !!!!          //
//                                            //
// This API is pretty much experimental and   //
// still in flux. The only thing guaranteed   //
// to remain compatible is a call to          //
// RENDERDOC_GetAPIVersion which must exactly //
// match the version you expect.              //
// It will be bumped on breaking changes.     //
////////////////////////////////////////////////

// API breaking change history:
// Version 1 -> 2 - strings changed from wchar_t* to char* (UTF-8)
// Version 2 -> 3 - StartFrameCapture, EndFrameCapture and SetActiveWindow take
//                  'device' pointer as well as window handles.
//                  This is either ID3D11Device* or the GL context (HGLRC/GLXContext)
//                  You can still pass NULL to both to capture the default, as long as
//                  there's only one device/window pair alive.
#define RENDERDOC_API_VERSION 3

//////////////////////////////////////////////////////////////////////////
// In-program functions
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API int RENDERDOC_CC RENDERDOC_GetAPIVersion();
typedef int (RENDERDOC_CC *pRENDERDOC_GetAPIVersion)();

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_Shutdown();
typedef void (RENDERDOC_CC *pRENDERDOC_Shutdown)();

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetLogFile(const char *logfile);
typedef void (RENDERDOC_CC *pRENDERDOC_SetLogFile)(const char *logfile);

extern "C" RENDERDOC_API const char* RENDERDOC_CC RENDERDOC_GetLogFile();
typedef const char* (RENDERDOC_CC *pRENDERDOC_GetLogFile)();

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_GetNumCaptures();
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_GetNumCaptures)();

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_GetCapture(uint32_t idx, char *logfile, uint32_t *pathlength, uint64_t *timestamp);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_GetCapture)(uint32_t idx, char *logfile, uint32_t *pathlength, uint64_t *timestamp);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetCaptureOptions(const CaptureOptions *opts);
typedef void (RENDERDOC_CC *pRENDERDOC_SetCaptureOptions)(const CaptureOptions *opts);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_TriggerCapture();
typedef void (RENDERDOC_CC *pRENDERDOC_TriggerCapture)();

// In the below functions 'device pointer' corresponds to the API specific handle, e.g.
// ID3D11Device, or the GL context pointer.
// The 'window handle' is the OS's native window handle (HWND or GLXDrawable).

// This must match precisely to a pair, and it sets the RenderDoc in-app overlay to select that
// window as 'active' and respond to keypresses.
extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetActiveWindow(void *device, void *wndHandle);
typedef void (RENDERDOC_CC *pRENDERDOC_SetActiveWindow)(void *device, void *wndHandle);

// Either parameter can be NULL to wild-card match, such that you can capture from any
// device to a particular window, or a particular device to any window.
// In either case, if there are two or more possible matching (device,window) pairs it
// is undefined which one will be captured.
// You can pass (NULL, NULL) if you know you only have one device and one window, and
// it will match. Likewise if you have not created a window at all (only off-screen
// rendering), then NULL window pointer will capture, whether you pass a NULL device
// or specify a device among multiple.

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_StartFrameCapture(void *device, void *wndHandle);
typedef void (RENDERDOC_CC *pRENDERDOC_StartFrameCapture)(void *device, void *wndHandle);

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_EndFrameCapture(void *device, void *wndHandle);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_EndFrameCapture)(void *device, void *wndHandle);

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_GetOverlayBits();
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_GetOverlayBits)();

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_MaskOverlayBits(uint32_t And, uint32_t Or);
typedef void (RENDERDOC_CC *pRENDERDOC_MaskOverlayBits)(uint32_t And, uint32_t Or);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetFocusToggleKeys(KeyButton *keys, int num);
typedef void (RENDERDOC_CC *pRENDERDOC_SetFocusToggleKeys)(KeyButton *keys, int num);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetCaptureKeys(KeyButton *keys, int num);
typedef void (RENDERDOC_CC *pRENDERDOC_SetCaptureKeys)(KeyButton *keys, int num);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_InitRemoteAccess(uint32_t *ident);
typedef void (RENDERDOC_CC *pRENDERDOC_InitRemoteAccess)(uint32_t *ident);

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_IsRemoteAccessConnected();
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_IsRemoteAccessConnected)();

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_LaunchReplayUI(uint32_t connectRemoteAccess, const char *cmdline);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_LaunchReplayUI)(uint32_t connectRemoteAccess, const char *cmdline);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_UnloadCrashHandler();
typedef void (RENDERDOC_CC *pRENDERDOC_UnloadCrashHandler)();

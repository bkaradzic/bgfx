// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// Don't include this file directly - use pix3.h

#pragma once

#ifndef _PIX3_H_
#error "Don't include this file directly - use pix3.h"
#endif

#ifndef _PIX3_WIN_H_
#define _PIX3_WIN_H_

// PIXEventsThreadInfo is defined in PIXEventsCommon.h
struct PIXEventsThreadInfo;

//extern "C" PIXEventsThreadInfo* WINAPI PIXGetThreadInfo() noexcept;
//
//#if defined(USE_PIX) && defined(USE_PIX_SUPPORTED_ARCHITECTURE)
//// Notifies PIX that an event handle was set as a result of a D3D12 fence being signaled.
//// The event specified must have the same handle value as the handle
//// used in ID3D12Fence::SetEventOnCompletion.
//extern "C" void WINAPI PIXNotifyWakeFromFenceSignal(_In_ HANDLE event);
//
//// Notifies PIX that a block of memory was allocated
//extern "C" void WINAPI PIXRecordMemoryAllocationEvent(USHORT allocatorId, void* baseAddress, size_t size, UINT64 metadata);
//
//// Notifies PIX that a block of memory was freed
//extern "C" void WINAPI PIXRecordMemoryFreeEvent(USHORT allocatorId, void* baseAddress, size_t size, UINT64 metadata);
//
//#else
//
//// Eliminate these APIs when not using PIX
//inline void PIXRecordMemoryAllocationEvent(USHORT, void*, size_t, UINT64) {}
//inline void PIXRecordMemoryFreeEvent(USHORT, void*, size_t, UINT64) {}
//
//#endif

// The following WINPIX_EVENT_* defines denote the different metadata values that have
// been used by tools to denote how to parse pix marker event data. The first two values
// are legacy values used by pix.h in the Windows SDK.
#define WINPIX_EVENT_UNICODE_VERSION 0
#define WINPIX_EVENT_ANSI_VERSION 1

// These values denote PIX marker event data that was created by the WinPixEventRuntime.
// In early 2023 we revised the PIX marker format and defined a new version number.
#define WINPIX_EVENT_PIX3BLOB_VERSION 2
#define WINPIX_EVENT_PIX3BLOB_V2 6345127 // A number that other applications are unlikely to have used before

// For backcompat reasons, the WinPixEventRuntime uses the older PIX3BLOB format when it passes data
// into the D3D12 runtime. It will be updated to use the V2 format in the future.
#define D3D12_EVENT_METADATA WINPIX_EVENT_PIX3BLOB_VERSION

__forceinline UINT64 PIXGetTimestampCounter()
{
    LARGE_INTEGER time = {};
    QueryPerformanceCounter(&time);
    return static_cast<UINT64>(time.QuadPart);
}

enum PIXHUDOptions
{
    PIX_HUD_SHOW_ON_ALL_WINDOWS = 0x1,
    PIX_HUD_SHOW_ON_TARGET_WINDOW_ONLY = 0x2,
    PIX_HUD_SHOW_ON_NO_WINDOWS = 0x4
};
DEFINE_ENUM_FLAG_OPERATORS(PIXHUDOptions);

#if defined(USE_PIX_SUPPORTED_ARCHITECTURE) && defined(USE_PIX)

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM | WINAPI_PARTITION_GAMES)

#include <shlobj.h>
#include <strsafe.h>
#include <knownfolders.h>
#include <shellapi.h>

#define PIXERRORCHECK(value)  do {                      \
                                 if (FAILED(value))     \
                                     return nullptr;    \
                                 } while(0)

namespace PixImpl
{
#ifndef PIX3_WIN_UNIT_TEST

    __forceinline BOOL GetModuleHandleExW(
        DWORD dwFlags,
        LPCWSTR lpModuleName,
        HMODULE* phModule)
    {
        return ::GetModuleHandleExW(dwFlags, lpModuleName, phModule);
    }

    __forceinline HRESULT SHGetKnownFolderPath(
        REFKNOWNFOLDERID rfid,
        DWORD dwFlags,
        HANDLE hToken,
        PWSTR* ppszPath)
    {
        return ::SHGetKnownFolderPath(rfid, dwFlags, hToken, ppszPath);
    }

    __forceinline void CoTaskMemFree(LPVOID pv)
    {
        return ::CoTaskMemFree(pv);
    }

    __forceinline HANDLE FindFirstFileW(
        LPCWSTR lpFileName,
        LPWIN32_FIND_DATAW lpFindFileData)
    {
        return ::FindFirstFileW(lpFileName, lpFindFileData);
    }

    __forceinline DWORD GetFileAttributesW(LPCWSTR lpFileName)
    {
        return ::GetFileAttributesW(lpFileName);
    }

    __forceinline BOOL FindNextFileW(
        HANDLE hFindFile,
        LPWIN32_FIND_DATAW lpFindFileData)
    {
        return ::FindNextFileW(hFindFile, lpFindFileData);
    }

    __forceinline BOOL FindClose(HANDLE hFindFile)
    {
        return ::FindClose(hFindFile);
    }

    __forceinline HMODULE LoadLibraryExW(LPCWSTR lpLibFileName, DWORD flags)
    {
        return ::LoadLibraryExW(lpLibFileName, NULL, flags);
    }

#endif // !PIX3_WIN_UNIT_TESTS

    __forceinline void * GetGpuCaptureFunctionPtr(LPCSTR fnName) noexcept
    {
        HMODULE module = GetModuleHandleW(L"WinPixGpuCapturer.dll");
        if (module == NULL)
        {
            return nullptr;
        }

        auto fn = (void*)GetProcAddress(module, fnName);
        if (fn == nullptr)
        {
            return nullptr;
        }

        return fn;
    }

    __forceinline void* GetTimingCaptureFunctionPtr(LPCSTR fnName) noexcept
    {
        HMODULE module = GetModuleHandleW(L"WinPixTimingCapturer.dll");
        if (module == NULL)
        {
            return nullptr;
        }

        auto fn = (void*)GetProcAddress(module, fnName);
        if (fn == nullptr)
        {
            return nullptr;
        }

        return fn;
    }

    __forceinline HMODULE PIXLoadLatestCapturerLibrary(wchar_t const* capturerDllName, DWORD flags)
    {
        HMODULE libHandle{};

        if (PixImpl::GetModuleHandleExW(0, capturerDllName, &libHandle))
        {
            return libHandle;
        }

        LPWSTR programFilesPath = nullptr;
        if (FAILED(PixImpl::SHGetKnownFolderPath(FOLDERID_ProgramFiles, KF_FLAG_DEFAULT, NULL, &programFilesPath)))
        {
            PixImpl::CoTaskMemFree(programFilesPath);
            return nullptr;
        }

        wchar_t pixSearchPath[MAX_PATH];

        if (FAILED(StringCchCopyW(pixSearchPath, MAX_PATH, programFilesPath)))
        {
            PixImpl::CoTaskMemFree(programFilesPath);
            return nullptr;
        }
        PixImpl::CoTaskMemFree(programFilesPath);

        PIXERRORCHECK(StringCchCatW(pixSearchPath, MAX_PATH, L"\\Microsoft PIX\\*"));

        WIN32_FIND_DATAW findData;
        bool foundPixInstallation = false;
        wchar_t newestVersionFound[MAX_PATH];
        wchar_t output[MAX_PATH];
        wchar_t possibleOutput[MAX_PATH];

        HANDLE hFind = PixImpl::FindFirstFileW(pixSearchPath, &findData);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) &&
                    (findData.cFileName[0] != '.'))
                {
                    if (!foundPixInstallation || wcscmp(newestVersionFound, findData.cFileName) <= 0)
                    {
                        // length - 1 to get rid of the wildcard character in the search path
                        PIXERRORCHECK(StringCchCopyNW(possibleOutput, MAX_PATH, pixSearchPath, wcslen(pixSearchPath) - 1));
                        PIXERRORCHECK(StringCchCatW(possibleOutput, MAX_PATH, findData.cFileName));
                        PIXERRORCHECK(StringCchCatW(possibleOutput, MAX_PATH, L"\\"));
                        PIXERRORCHECK(StringCchCatW(possibleOutput, MAX_PATH, capturerDllName));

                        DWORD result = PixImpl::GetFileAttributesW(possibleOutput);

                        if (result != INVALID_FILE_ATTRIBUTES && !(result & FILE_ATTRIBUTE_DIRECTORY))
                        {
                            foundPixInstallation = true;
                            PIXERRORCHECK(StringCchCopyW(newestVersionFound, _countof(newestVersionFound), findData.cFileName));
                            PIXERRORCHECK(StringCchCopyW(output, _countof(possibleOutput), possibleOutput));
                        }
                    }
                }
            } while (PixImpl::FindNextFileW(hFind, &findData) != 0);
        }

        PixImpl::FindClose(hFind);

        if (!foundPixInstallation)
        {
            SetLastError(ERROR_FILE_NOT_FOUND);
            return nullptr;
        }

        return PixImpl::LoadLibraryExW(output, flags);
    }
}

#undef PIXERRORCHECK

__forceinline HMODULE PIXLoadLatestWinPixGpuCapturerLibrary()
{
    return PixImpl::PIXLoadLatestCapturerLibrary(
        L"WinPixGpuCapturer.dll",
        LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
}

__forceinline HMODULE PIXLoadLatestWinPixTimingCapturerLibrary()
{
    return PixImpl::PIXLoadLatestCapturerLibrary(
        L"WinPixTimingCapturer.dll",
        LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
}

__forceinline HRESULT WINAPI PIXSetTargetWindow(HWND hwnd)
{
    typedef void(WINAPI* SetGlobalTargetWindowFn)(HWND);

    auto fn = (SetGlobalTargetWindowFn)PixImpl::GetGpuCaptureFunctionPtr("SetGlobalTargetWindow");
    if (fn == nullptr)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    fn(hwnd);
    return S_OK;
}

__forceinline HRESULT WINAPI PIXGpuCaptureNextFrames(PCWSTR fileName, UINT32 numFrames)
{
    typedef HRESULT(WINAPI* CaptureNextFrameFn)(PCWSTR, UINT32);

    auto fn = (CaptureNextFrameFn)PixImpl::GetGpuCaptureFunctionPtr("CaptureNextFrame");
    if (fn == nullptr)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return fn(fileName, numFrames);
}

extern "C"  __forceinline HRESULT WINAPI PIXBeginCapture2(DWORD captureFlags, _In_opt_ const PPIXCaptureParameters captureParameters)
{
    if (captureFlags == PIX_CAPTURE_GPU)
    {
        typedef HRESULT(WINAPI* BeginProgrammaticGpuCaptureFn)(const PPIXCaptureParameters);

        auto fn = (BeginProgrammaticGpuCaptureFn)PixImpl::GetGpuCaptureFunctionPtr("BeginProgrammaticGpuCapture");
        if (fn == nullptr)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return fn(captureParameters);
    }
    else if (captureFlags == PIX_CAPTURE_TIMING)
    {
        typedef HRESULT(WINAPI* BeginProgrammaticTimingCaptureFn)(void const*, UINT64);

        auto fn = (BeginProgrammaticTimingCaptureFn)PixImpl::GetTimingCaptureFunctionPtr("BeginProgrammaticTimingCapture");
        if (fn == nullptr)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return fn(&captureParameters->TimingCaptureParameters, sizeof(captureParameters->TimingCaptureParameters));
    }
    else
    {
        return E_NOTIMPL;
    }
}

extern "C"  __forceinline HRESULT WINAPI PIXEndCapture(BOOL discard)
{
    // We can't tell if the user wants to end a GPU Capture or a Timing Capture.
    // The user shouldn't have both WinPixGpuCapturer and WinPixTimingCapturer loaded in the process though,
    // so we can just look for one of them and call it.
    typedef HRESULT(WINAPI* EndProgrammaticGpuCaptureFn)(void);
    auto gpuFn = (EndProgrammaticGpuCaptureFn)PixImpl::GetGpuCaptureFunctionPtr("EndProgrammaticGpuCapture");
    if (gpuFn != NULL)
    {
        return gpuFn();
    }

    typedef HRESULT(WINAPI* EndProgrammaticTimingCaptureFn)(BOOL);
    auto timingFn = (EndProgrammaticTimingCaptureFn)PixImpl::GetTimingCaptureFunctionPtr("EndProgrammaticTimingCapture");
    if (timingFn != NULL)
    {
        return timingFn(discard);
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

__forceinline HRESULT WINAPI PIXForceD3D11On12()
{
    typedef HRESULT (WINAPI* ForceD3D11On12Fn)(void);

    auto fn = (ForceD3D11On12Fn)PixImpl::GetGpuCaptureFunctionPtr("ForceD3D11On12");
    if (fn == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return fn();
}

__forceinline HRESULT WINAPI PIXSetHUDOptions(PIXHUDOptions hudOptions)
{
    typedef HRESULT(WINAPI* SetHUDOptionsFn)(PIXHUDOptions);

    auto fn = (SetHUDOptionsFn)PixImpl::GetGpuCaptureFunctionPtr("SetHUDOptions");
    if (fn == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return fn(hudOptions);
}

__forceinline bool WINAPI PIXIsAttachedForGpuCapture()
{
    typedef bool(WINAPI* GetIsAttachedToPixFn)(void);
    auto fn = (GetIsAttachedToPixFn)PixImpl::GetGpuCaptureFunctionPtr("GetIsAttachedToPix");
    if (fn == NULL)
    {
        OutputDebugStringW(L"WinPixEventRuntime error: Mismatched header/dll. Please ensure that pix3.h and WinPixGpuCapturer.dll match");
        return false;
    }

    return fn();
}

__forceinline HINSTANCE WINAPI PIXOpenCaptureInUI(PCWSTR fileName)
{
    return ShellExecuteW(0, 0, fileName, 0, 0, SW_SHOW);
}

#else
__forceinline HMODULE PIXLoadLatestWinPixGpuCapturerLibrary()
{
    return nullptr;
}
__forceinline HMODULE PIXLoadLatestWinPixTimingCapturerLibrary()
{
    return nullptr;
}
__forceinline HRESULT WINAPI PIXSetTargetWindow(HWND)
{
    return E_NOTIMPL;
}

__forceinline HRESULT WINAPI PIXGpuCaptureNextFrames(PCWSTR, UINT32)
{
    return E_NOTIMPL;
}
extern "C"  __forceinline HRESULT WINAPI PIXBeginCapture2(DWORD, _In_opt_ const PPIXCaptureParameters)
{
    return E_NOTIMPL;
}
extern "C"  __forceinline HRESULT WINAPI PIXEndCapture(BOOL)
{
    return E_NOTIMPL;
}
__forceinline HRESULT WINAPI PIXForceD3D11On12()
{
    return E_NOTIMPL;
}
__forceinline HRESULT WINAPI PIXSetHUDOptions(PIXHUDOptions)
{
    return E_NOTIMPL;
}
__forceinline bool WINAPI PIXIsAttachedForGpuCapture()
{
    return false;
}
__forceinline HINSTANCE WINAPI PIXOpenCaptureInUI(PCWSTR)
{
    return 0;
}
#endif // WINAPI_PARTITION

#endif // USE_PIX_SUPPORTED_ARCHITECTURE || USE_PIX

#if defined(__d3d12_h__)

inline void PIXInsertTimingMarkerOnContextForBeginEvent(_In_ ID3D12GraphicsCommandList* commandList, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandList->BeginEvent(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertTimingMarkerOnContextForBeginEvent(_In_ ID3D12CommandQueue* commandQueue, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandQueue->BeginEvent(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertTimingMarkerOnContextForSetMarker(_In_ ID3D12GraphicsCommandList* commandList, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandList->SetMarker(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertTimingMarkerOnContextForSetMarker(_In_ ID3D12CommandQueue* commandQueue, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandQueue->SetMarker(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertTimingMarkerOnContextForEndEvent(_In_ ID3D12GraphicsCommandList* commandList, UINT8 eventType)
{
    UNREFERENCED_PARAMETER(eventType);
    commandList->EndEvent();
}

inline void PIXInsertTimingMarkerOnContextForEndEvent(_In_ ID3D12CommandQueue* commandQueue, UINT8 eventType)
{
    UNREFERENCED_PARAMETER(eventType);
    commandQueue->EndEvent();
}

inline void PIXInsertGPUMarkerOnContextForBeginEvent(_In_ ID3D12GraphicsCommandList* commandList, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandList->BeginEvent(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertGPUMarkerOnContextForBeginEvent(_In_ ID3D12CommandQueue* commandQueue, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandQueue->BeginEvent(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertGPUMarkerOnContextForSetMarker(_In_ ID3D12GraphicsCommandList* commandList, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandList->SetMarker(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertGPUMarkerOnContextForSetMarker(_In_ ID3D12CommandQueue* commandQueue, UINT8 eventType, _In_reads_bytes_(size) void* data, UINT size)
{
    UNREFERENCED_PARAMETER(eventType);
    commandQueue->SetMarker(WINPIX_EVENT_PIX3BLOB_V2, data, size);
}

inline void PIXInsertGPUMarkerOnContextForEndEvent(_In_ ID3D12GraphicsCommandList* commandList, UINT8, void*, UINT)
{
    commandList->EndEvent();
}

inline void PIXInsertGPUMarkerOnContextForEndEvent(_In_ ID3D12CommandQueue* commandQueue, UINT8, void*, UINT)
{
    commandQueue->EndEvent();
}

#endif

#endif //_PIX3_WIN_H_

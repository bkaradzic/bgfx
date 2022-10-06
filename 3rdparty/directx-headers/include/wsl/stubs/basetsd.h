// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

// These #defines prevent the idl-generated headers from trying to include
// Windows.h from the SDK rather than this one.
#define RPC_NO_WINDOWS_H
#define COM_NO_WINDOWS_H

// Allcaps type definitions
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <sal.h>

// Note: using fixed-width here to match Windows widths
// Specifically this is different for 'long' vs 'LONG'
typedef uint8_t UINT8;
typedef int8_t INT8;
typedef uint16_t UINT16;
typedef int16_t INT16;
typedef uint32_t UINT32, UINT, ULONG, DWORD, BOOL, WINBOOL;
typedef int32_t INT32, INT, LONG;
typedef uint64_t UINT64, ULONG_PTR;
typedef int64_t INT64, LONG_PTR;
typedef void VOID, *HANDLE, *RPC_IF_HANDLE, *LPVOID;
typedef const void *LPCVOID;
typedef size_t SIZE_T;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned char BYTE;
typedef HANDLE HWND;
typedef HANDLE HMODULE;
typedef size_t SIZE;
typedef int PALETTEENTRY;
typedef int HDC;
typedef uint16_t WORD;
typedef void* PVOID;
typedef char BOOLEAN;
typedef uint64_t ULONGLONG;
typedef int16_t SHORT, *PSHORT;
typedef uint16_t USHORT, *PUSHORT;
typedef int64_t LONGLONG, *PLONGLONG;
typedef int64_t LONG_PTR, *PLONG_PTR;
typedef int64_t LONG64, *PLONG64;
typedef uint64_t ULONG64, *PULONG64;
typedef wchar_t WCHAR, *PWSTR;
typedef uint8_t UCHAR, *PUCHAR;
typedef uint64_t ULONG_PTR, *PULONG_PTR;
typedef uint64_t UINT_PTR, *PUINT_PTR;
typedef int64_t INT_PTR, *PINT_PTR;

// Note: WCHAR is not the same between Windows and Linux, to enable
// string manipulation APIs to work with resulting strings.
// APIs to D3D/DXCore will work on Linux wchars, but beware with
// interactions directly with the Windows kernel.
typedef char CHAR, *PSTR, *LPSTR, TCHAR, *PTSTR;
typedef const char *LPCSTR, *PCSTR, *LPCTSTR, *PCTSTR;
typedef wchar_t WCHAR, *PWSTR, *LPWSTR, *PWCHAR;
typedef const wchar_t *LPCWSTR, *PCWSTR;

#undef LONG_MAX
#define LONG_MAX INT_MAX
#undef ULONG_MAX
#define ULONG_MAX UINT_MAX

// Misc defines
#define MIDL_INTERFACE(x) interface
#define __analysis_assume(x)
#define TRUE 1u
#define FALSE 0u
#define DECLSPEC_UUID(x)
#define DECLSPEC_NOVTABLE
#define DECLSPEC_SELECTANY
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#define APIENTRY
#define OUT
#define IN
#define CONST const
#define MAX_PATH 260
#define GENERIC_ALL 0x10000000L
#define C_ASSERT(expr) static_assert((expr))
#define _countof(a) (sizeof(a) / sizeof(*(a)))

typedef struct tagRECTL
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECTL;

typedef struct tagPOINT
{
    int x;
    int y;
} POINT;

typedef struct _GUID {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[ 8 ];
} GUID;

#ifdef INITGUID
#ifdef __cplusplus
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
#else
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
#endif
#else
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID name
#endif

typedef GUID IID;
typedef GUID UUID;
typedef GUID CLSID;
#ifdef __cplusplus
#define REFGUID const GUID &
#define REFIID const IID &
#define REFCLSID const IID &

__inline int InlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
    return (
        ((uint32_t *)&rguid1)[0] == ((uint32_t *)&rguid2)[0] &&
        ((uint32_t *)&rguid1)[1] == ((uint32_t *)&rguid2)[1] &&
        ((uint32_t *)&rguid1)[2] == ((uint32_t *)&rguid2)[2] &&
        ((uint32_t *)&rguid1)[3] == ((uint32_t *)&rguid2)[3]);
}

inline bool operator==(REFGUID guidOne, REFGUID guidOther)
{
    return !!InlineIsEqualGUID(guidOne, guidOther);
}

inline bool operator!=(REFGUID guidOne, REFGUID guidOther)
{
    return !(guidOne == guidOther);
}

#else
#define REFGUID const GUID *
#define REFIID const IID *
#define REFCLSID const IID *
#endif

// Calling conventions
#define __cdecl
#define __stdcall
#define STDMETHODCALLTYPE
#define STDAPICALLTYPE
#define STDAPI EXTERN_C HRESULT STDAPICALLTYPE
#define WINAPI

#define interface struct
#if defined (__cplusplus) && !defined (CINTERFACE)
#define STDMETHOD(method) virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type, method) virtual type STDMETHODCALLTYPE method
#define PURE = 0
#define THIS_
#define THIS void
#define DECLARE_INTERFACE(iface) interface DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface) interface DECLSPEC_NOVTABLE iface : public baseiface

interface IUnknown;
extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp)
    {
        (void)static_cast<IUnknown*>(*pp);
        return reinterpret_cast<void**>(pp);
    }
}
#define IID_PPV_ARGS(ppType) __uuidof (**(ppType)), IID_PPV_ARGS_Helper (ppType)
#else
#define STDMETHOD(method) HRESULT (STDMETHODCALLTYPE *method)
#define STDMETHOD_(type, method) type (STDMETHODCALLTYPE *method)
#define PURE
#define THIS_ INTERFACE *This,
#define THIS INTERFACE *This
#ifdef CONST_VTABLE
#define DECLARE_INTERFACE(iface) typedef interface iface { const struct iface##Vtbl *lpVtbl; } iface; typedef const struct iface##Vtbl iface##Vtbl; const struct iface##Vtbl
#else
#define DECLARE_INTERFACE(iface) typedef interface iface { struct iface##Vtbl *lpVtbl; } iface; typedef struct iface##Vtbl iface##Vtbl; struct iface##Vtbl
#endif
#define DECLARE_INTERFACE_(iface, baseiface) DECLARE_INTERFACE (iface)
#endif

#define IFACEMETHOD(method) /*override*/ STDMETHOD (method)
#define IFACEMETHOD_(type, method) /*override*/ STDMETHOD_(type, method)
#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#define END_INTERFACE
#endif

// Error codes
typedef LONG HRESULT;
#define SUCCEEDED(hr)  (((HRESULT)(hr)) >= 0)
#define FAILED(hr)     (((HRESULT)(hr)) < 0)
#define S_OK           ((HRESULT)0L)
#define S_FALSE        ((HRESULT)1L)
#define E_NOTIMPL      ((HRESULT)0x80004001L)
#define E_OUTOFMEMORY  ((HRESULT)0x8007000EL)
#define E_INVALIDARG   ((HRESULT)0x80070057L)
#define E_NOINTERFACE  ((HRESULT)0x80004002L)
#define E_POINTER      ((HRESULT)0x80004003L)
#define E_HANDLE       ((HRESULT)0x80070006L)
#define E_ABORT        ((HRESULT)0x80004004L)
#define E_FAIL         ((HRESULT)0x80004005L)
#define E_ACCESSDENIED ((HRESULT)0x80070005L)
#define E_UNEXPECTED   ((HRESULT)0x8000FFFFL)
#define DXGI_ERROR_INVALID_CALL ((HRESULT)0x887A0001L)
#define DXGI_ERROR_NOT_FOUND ((HRESULT)0x887A0002L)
#define DXGI_ERROR_MORE_DATA ((HRESULT)0x887A0003L)
#define DXGI_ERROR_UNSUPPORTED ((HRESULT)0x887A0004L)
#define DXGI_ERROR_DEVICE_REMOVED ((HRESULT)0x887A0005L)
#define DXGI_ERROR_DEVICE_HUNG ((HRESULT)0x887A0006L)
#define DXGI_ERROR_DEVICE_RESET ((HRESULT)0x887A0007L)
#define DXGI_ERROR_DRIVER_INTERNAL_ERROR ((HRESULT)0x887A0020L)

typedef struct _LUID
{
    ULONG LowPart;
    LONG HighPart;
} LUID;

typedef struct _RECT
{
    int left;
    int top;
    int right;
    int bottom;
} RECT;

typedef union _LARGE_INTEGER {
  struct {
    uint32_t LowPart;
    uint32_t HighPart;
  } u;
  int64_t QuadPart;
} LARGE_INTEGER;
typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
  struct {
    uint32_t LowPart;
    uint32_t HighPart;
  } u;
  uint64_t QuadPart;
} ULARGE_INTEGER;
typedef ULARGE_INTEGER *PULARGE_INTEGER;

#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    WINBOOL bInheritHandle;
} SECURITY_ATTRIBUTES;

struct STATSTG;

#ifdef __cplusplus
// ENUM_FLAG_OPERATORS
// Define operator overloads to enable bit operations on enum values that are
// used to define flags. Use DEFINE_ENUM_FLAG_OPERATORS(YOUR_TYPE) to enable these
// operators on YOUR_TYPE.
extern "C++" {
    template <size_t S>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE;

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<1>
    {
        typedef int8_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<2>
    {
        typedef int16_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<4>
    {
        typedef int32_t type;
    };

    template <>
    struct _ENUM_FLAG_INTEGER_FOR_SIZE<8>
    {
        typedef int64_t type;
    };

    // used as an approximation of std::underlying_type<T>
    template <class T>
    struct _ENUM_FLAG_SIZED_INTEGER
    {
        typedef typename _ENUM_FLAG_INTEGER_FOR_SIZE<sizeof(T)>::type type;
    };

}
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline constexpr ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) | ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) |= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline constexpr ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) & ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) &= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline constexpr ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a)); } \
inline constexpr ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) ^ ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type &)a) ^= ((_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); } \
}
#else
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) /* */
#endif

// D3DX12 uses these
#include <stdlib.h>
#define HeapAlloc(heap, flags, size) malloc(size)
#define HeapFree(heap, flags, ptr) free(ptr)

#if defined(lint)
// Note: lint -e530 says don't complain about uninitialized variables for
// this variable.  Error 527 has to do with unreachable code.
// -restore restores checking to the -save state
#define UNREFERENCED_PARAMETER(P) \
    /*lint -save -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#else
#define UNREFERENCED_PARAMETER(P) (P)
#endif

//===- WinAdapter.h - Windows Adapter for non-Windows platforms -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines Windows-specific types, macros, and SAL annotations used
// in the codebase for non-Windows platforms.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_WIN_ADAPTER_H
#define LLVM_SUPPORT_WIN_ADAPTER_H

#ifndef _WIN32

#include "../wsl/winadapter.h"

constexpr uint8_t nybble_from_hex(char c) {
  return ((c >= '0' && c <= '9')
              ? (c - '0')
              : ((c >= 'a' && c <= 'f')
                     ? (c - 'a' + 10)
                     : ((c >= 'A' && c <= 'F') ? (c - 'A' + 10)
                                               : /* Should be an error */ -1)));
}

constexpr uint8_t byte_from_hex(char c1, char c2) {
  return nybble_from_hex(c1) << 4 | nybble_from_hex(c2);
}

constexpr uint8_t byte_from_hexstr(const char str[2]) {
  return nybble_from_hex(str[0]) << 4 | nybble_from_hex(str[1]);
}

constexpr GUID guid_from_string(const char str[37]) {
  return GUID{static_cast<uint32_t>(byte_from_hexstr(str)) << 24 |
                  static_cast<uint32_t>(byte_from_hexstr(str + 2)) << 16 |
                  static_cast<uint32_t>(byte_from_hexstr(str + 4)) << 8 |
                  byte_from_hexstr(str + 6),
              static_cast<uint16_t>(
                  static_cast<uint16_t>(byte_from_hexstr(str + 9)) << 8 |
                  byte_from_hexstr(str + 11)),
              static_cast<uint16_t>(
                  static_cast<uint16_t>(byte_from_hexstr(str + 14)) << 8 |
                  byte_from_hexstr(str + 16)),
              {byte_from_hexstr(str + 19), byte_from_hexstr(str + 21),
               byte_from_hexstr(str + 24), byte_from_hexstr(str + 26),
               byte_from_hexstr(str + 28), byte_from_hexstr(str + 30),
               byte_from_hexstr(str + 32), byte_from_hexstr(str + 34)}};
}

template <typename XX> inline GUID __emulated_uuidof();

#define CROSS_PLATFORM_UUIDOF(interface, spec)                                 \
  struct interface;                                                            \
  template <> inline GUID __emulated_uuidof<interface>() {                     \
    static const IID _IID = guid_from_string(spec);                            \
    return _IID;                                                               \
  }

typedef wchar_t *BSTR;

CROSS_PLATFORM_UUIDOF(INoMarshal, "ECC8691B-C1DB-4DC0-855E-65F6C551AF49")
struct INoMarshal : public IUnknown {};

CROSS_PLATFORM_UUIDOF(IMalloc, "00000002-0000-0000-C000-000000000046")
struct IMalloc : public IUnknown {
  virtual void *Alloc(SIZE_T size) = 0;
  virtual void *Realloc(void *ptr, SIZE_T size) = 0;
  virtual void Free(void *ptr) = 0;
  virtual SIZE_T GetSize(void *pv) = 0;
  virtual int DidAlloc(void *pv) = 0;
  virtual void HeapMinimize(void) = 0;
};

CROSS_PLATFORM_UUIDOF(ISequentialStream, "0C733A30-2A1C-11CE-ADE5-00AA0044773D")
struct ISequentialStream : public IUnknown {
  virtual HRESULT Read(void *pv, ULONG cb, ULONG *pcbRead) = 0;
  virtual HRESULT Write(const void *pv, ULONG cb, ULONG *pcbWritten) = 0;
};

CROSS_PLATFORM_UUIDOF(IStream, "0000000c-0000-0000-C000-000000000046")
struct IStream : public ISequentialStream {
  virtual HRESULT Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
                       ULARGE_INTEGER *plibNewPosition) = 0;
  virtual HRESULT SetSize(ULARGE_INTEGER libNewSize) = 0;
  virtual HRESULT CopyTo(IStream *pstm, ULARGE_INTEGER cb,
                         ULARGE_INTEGER *pcbRead,
                         ULARGE_INTEGER *pcbWritten) = 0;

  virtual HRESULT Commit(DWORD grfCommitFlags) = 0;

  virtual HRESULT Revert(void) = 0;

  virtual HRESULT LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                             DWORD dwLockType) = 0;

  virtual HRESULT UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                               DWORD dwLockType) = 0;

  virtual HRESULT Stat(STATSTG *pstatstg, DWORD grfStatFlag) = 0;

  virtual HRESULT Clone(IStream **ppstm) = 0;
};

// These don't need stub implementations as they come from the DirectX Headers
// They still need the __uuidof() though
CROSS_PLATFORM_UUIDOF(ID3D12LibraryReflection,
                      "8E349D19-54DB-4A56-9DC9-119D87BDB804")
CROSS_PLATFORM_UUIDOF(ID3D12ShaderReflection,
                      "5A58797D-A72C-478D-8BA2-EFC6B0EFE88E")

#endif // !WIN32

#endif // LLVM_SUPPORT_WIN_ADAPTER_H

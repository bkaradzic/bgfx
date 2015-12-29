// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>

#ifndef NV_CORE_H
#define NV_CORE_H

#define NVCORE_SHARED 0
#define NV_NO_ASSERT 0

// Function linkage
#if NVCORE_SHARED
#ifdef NVCORE_EXPORTS
#define NVCORE_API DLL_EXPORT
#define NVCORE_CLASS DLL_EXPORT_CLASS
#else
#define NVCORE_API DLL_IMPORT
#define NVCORE_CLASS DLL_IMPORT
#endif
#else // NVCORE_SHARED
#define NVCORE_API
#define NVCORE_CLASS
#endif // NVCORE_SHARED

// Platform definitions
#include "posh.h"

#define NV_OS_STRING POSH_OS_STRING

#if defined POSH_OS_LINUX
#   define NV_OS_LINUX 1
#   define NV_OS_UNIX 1
#elif defined POSH_OS_ORBIS
#   define NV_OS_ORBIS 1
#elif defined POSH_OS_FREEBSD
#   define NV_OS_FREEBSD 1
#   define NV_OS_UNIX 1
#elif defined POSH_OS_OPENBSD
#   define NV_OS_OPENBSD 1
#   define NV_OS_UNIX 1
#elif defined POSH_OS_CYGWIN32
#   define NV_OS_CYGWIN 1
#elif defined POSH_OS_MINGW
#   define NV_OS_MINGW 1
#   define NV_OS_WIN32 1
#elif defined POSH_OS_OSX
#   define NV_OS_DARWIN 1
#   define NV_OS_UNIX 1
#elif defined POSH_OS_IOS
#   define NV_OS_DARWIN 1 //ACS should we keep this on IOS?
#   define NV_OS_UNIX 1
#   define NV_OS_IOS 1
#elif defined POSH_OS_UNIX
#   define NV_OS_UNIX 1
#elif defined POSH_OS_WIN64
#   define NV_OS_WIN32 1
#   define NV_OS_WIN64 1
#elif defined POSH_OS_WIN32
#   define NV_OS_WIN32 1
#elif defined POSH_OS_XBOX
#   define NV_OS_XBOX 1
#else
#   error "Unsupported OS"
#endif

#ifndef NV_OS_WIN32
#	define NV_OS_WIN32  0
#endif // NV_OS_WIN32

#ifndef NV_OS_WIN64
#	define NV_OS_WIN64  0
#endif // NV_OS_WIN64

#ifndef NV_OS_MINGW
#	define NV_OS_MINGW  0
#endif // NV_OS_MINGW

#ifndef NV_OS_CYGWIN
#	define NV_OS_CYGWIN 0
#endif // NV_OS_CYGWIN

#ifndef NV_OS_LINUX
#	define NV_OS_LINUX  0
#endif // NV_OS_LINUX

#ifndef NV_OS_FREEBSD
#	define NV_OS_FREEBSD 0
#endif // NV_OS_FREEBSD

#ifndef NV_OS_OPENBSD
#	define NV_OS_OPENBSD 0
#endif // NV_OS_OPENBSD

#ifndef NV_OS_UNIX
#	define NV_OS_UNIX   0
#endif // NV_OS_UNIX

#ifndef NV_OS_DARWIN
#	define NV_OS_DARWIN 0
#endif // NV_OS_DARWIN

#ifndef NV_OS_XBOX
#	define NV_OS_XBOX   0
#endif // NV_OS_XBOX

#ifndef NV_OS_ORBIS
#	define NV_OS_ORBIS  0
#endif // NV_OS_ORBIS

#ifndef NV_OS_IOS
#	define NV_OS_IOS    0
#endif // NV_OS_IOS

// Threading:
// some platforms don't implement __thread or similar for thread-local-storage
#if NV_OS_UNIX || NV_OS_ORBIS || NV_OS_IOS //ACStodoIOS darwin instead of ios?
#   define NV_OS_USE_PTHREAD 1
#   if NV_OS_DARWIN || NV_OS_IOS
#       define NV_OS_HAS_TLS_QUALIFIER 0
#   else
#       define NV_OS_HAS_TLS_QUALIFIER 1
#   endif
#else
#   define NV_OS_USE_PTHREAD 0
#   define NV_OS_HAS_TLS_QUALIFIER 1
#endif


// CPUs:

#define NV_CPU_STRING   POSH_CPU_STRING

#if defined POSH_CPU_X86_64
//#   define NV_CPU_X86 1
#   define NV_CPU_X86_64 1
#elif defined POSH_CPU_X86
#   define NV_CPU_X86 1
#elif defined POSH_CPU_PPC
#   define NV_CPU_PPC 1
#elif defined POSH_CPU_STRONGARM
#   define NV_CPU_ARM 1
#elif defined POSH_CPU_AARCH64
#   define NV_CPU_AARCH64 1
#else
#   error "Unsupported CPU"
#endif

#ifndef NV_CPU_X86
#	define NV_CPU_X86     0
#endif // NV_CPU_X86

#ifndef NV_CPU_X86_64
#	define NV_CPU_X86_64  0
#endif // NV_CPU_X86_64

#ifndef NV_CPU_PPC
#	define NV_CPU_PPC     0
#endif // NV_CPU_PPC

#ifndef NV_CPU_ARM
#	define NV_CPU_ARM     0
#endif // NV_CPU_ARM

#ifndef NV_CPU_AARCH64
#	define NV_CPU_AARCH64 0
#endif // NV_CPU_AARCH64

// Compiler:

#if defined POSH_COMPILER_CLANG
#   define NV_CC_CLANG  1
#   define NV_CC_GNUC   1    // Clang is compatible with GCC.
#   define NV_CC_STRING "clang"
#	pragma clang diagnostic ignored "-Wmissing-braces"
#	pragma clang diagnostic ignored "-Wshadow"
#	pragma clang diagnostic ignored "-Wunused-local-typedef"
#	pragma clang diagnostic ignored "-Wunused-function"
#	pragma clang diagnostic ignored "-Wunused-variable"
#	pragma clang diagnostic ignored "-Wunused-parameter"
#	pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#elif defined POSH_COMPILER_GCC
#   define NV_CC_GNUC   1
#   define NV_CC_STRING "gcc"
#	pragma GCC diagnostic ignored "-Wshadow"
#	pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#	pragma GCC diagnostic ignored "-Wunused-function"
#	pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#	pragma GCC diagnostic ignored "-Wunused-variable"
#	pragma GCC diagnostic ignored "-Wunused-parameter"
#	pragma GCC diagnostic ignored "-Warray-bounds"
#elif defined POSH_COMPILER_MSVC
#   define NV_CC_MSVC   1
#   define NV_CC_STRING "msvc"
#else
#   error "Unsupported compiler"
#endif

#ifndef NV_CC_GNUC
#	define NV_CC_GNUC  0
#endif // NV_CC_GNUC

#ifndef NV_CC_MSVC
#	define NV_CC_MSVC  0
#endif // NV_CC_MSVC

#ifndef NV_CC_CLANG
#	define NV_CC_CLANG 0
#endif // NV_CC_CLANG

#if NV_CC_MSVC
#define NV_CC_CPP11 (__cplusplus > 199711L || _MSC_VER >= 1800) // Visual Studio 2013 has all the features we use, but doesn't advertise full C++11 support yet.
#else
// @@ IC: This works in CLANG, about GCC?
// @@ ES: Doesn't work in gcc. These 3 features are available in GCC >= 4.4.
#ifdef __clang__
#define NV_CC_CPP11 (__has_feature(cxx_deleted_functions) && __has_feature(cxx_rvalue_references) && __has_feature(cxx_static_assert))
#elif defined __GNUC__ 
#define NV_CC_CPP11 ( __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4))
#endif
#endif

// Endiannes:
#define NV_LITTLE_ENDIAN    POSH_LITTLE_ENDIAN
#define NV_BIG_ENDIAN       POSH_BIG_ENDIAN
#define NV_ENDIAN_STRING    POSH_ENDIAN_STRING


// Type definitions:
typedef posh_u8_t   uint8;
typedef posh_i8_t   int8;

typedef posh_u16_t  uint16;
typedef posh_i16_t  int16;

typedef posh_u32_t  uint32;
typedef posh_i32_t  int32;

typedef posh_u64_t  uint64;
typedef posh_i64_t  int64;

// Aliases
typedef uint32      uint;


// Version string:
#define NV_VERSION_STRING \
    NV_OS_STRING "/" NV_CC_STRING "/" NV_CPU_STRING"/" \
    NV_ENDIAN_STRING"-endian - " __DATE__ "-" __TIME__


// Disable copy constructor and assignment operator. 
#if NV_CC_CPP11
#define NV_FORBID_COPY(C) \
    C( const C & ) = delete; \
    C &operator=( const C & ) = delete
#else
#define NV_FORBID_COPY(C) \
    private: \
    C( const C & ); \
    C &operator=( const C & )
#endif

// Disable dynamic allocation on the heap. 
// See Prohibiting Heap-Based Objects in More Effective C++.
#define NV_FORBID_HEAPALLOC() \
    private: \
    void *operator new(size_t size); \
    void *operator new[](size_t size)

// String concatenation macros.
#define NV_STRING_JOIN2(arg1, arg2) NV_DO_STRING_JOIN2(arg1, arg2)
#define NV_DO_STRING_JOIN2(arg1, arg2) arg1 ## arg2
#define NV_STRING_JOIN3(arg1, arg2, arg3) NV_DO_STRING_JOIN3(arg1, arg2, arg3)
#define NV_DO_STRING_JOIN3(arg1, arg2, arg3) arg1 ## arg2 ## arg3
#define NV_STRING2(x) #x
#define NV_STRING(x) NV_STRING2(x)

#if NV_CC_MSVC
#define NV_MULTI_LINE_MACRO_BEGIN do {  
#define NV_MULTI_LINE_MACRO_END \
    __pragma(warning(push)) \
    __pragma(warning(disable:4127)) \
    } while(false) \
    __pragma(warning(pop))  
#else
#define NV_MULTI_LINE_MACRO_BEGIN do {
#define NV_MULTI_LINE_MACRO_END } while(false)
#endif

#if NV_CC_CPP11
#define nvStaticCheck(x) static_assert((x), "Static assert "#x" failed")
#else
#define nvStaticCheck(x) typedef char NV_STRING_JOIN2(__static_assert_,__LINE__)[(x)]
#endif
#define NV_COMPILER_CHECK(x) nvStaticCheck(x)   // I like this name best.

// Make sure type definitions are fine.
NV_COMPILER_CHECK(sizeof(int8) == 1);
NV_COMPILER_CHECK(sizeof(uint8) == 1);
NV_COMPILER_CHECK(sizeof(int16) == 2);
NV_COMPILER_CHECK(sizeof(uint16) == 2);
NV_COMPILER_CHECK(sizeof(int32) == 4);
NV_COMPILER_CHECK(sizeof(uint32) == 4);
NV_COMPILER_CHECK(sizeof(int32) == 4);
NV_COMPILER_CHECK(sizeof(uint32) == 4);


#define NV_ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#if 0 // Disabled in The Witness.
#if NV_CC_MSVC
#define NV_MESSAGE(x) message(__FILE__ "(" NV_STRING(__LINE__) ") : " x)
#else
#define NV_MESSAGE(x) message(x)
#endif
#else
#define NV_MESSAGE(x) 
#endif


// Startup initialization macro.
#define NV_AT_STARTUP(some_code) \
    namespace { \
        static struct NV_STRING_JOIN2(AtStartup_, __LINE__) { \
            NV_STRING_JOIN2(AtStartup_, __LINE__)() { some_code; } \
        } \
        NV_STRING_JOIN3(AtStartup_, __LINE__, Instance); \
    }

// Indicate the compiler that the parameter is not used to suppress compier warnings.
#define NV_UNUSED(a) ((a)=(a))

// Null index. @@ Move this somewhere else... it's only used by nvmesh.
//const unsigned int NIL = unsigned int(~0);
//#define NIL uint(~0)

// Null pointer.
#ifndef NULL
#define NULL 0
#endif

// Platform includes
#if NV_CC_MSVC
#   if NV_OS_WIN32
#       include "defsvcwin32.h"
#   elif NV_OS_XBOX
#       include "defsvcxbox.h"
#   else
#       error "MSVC: Platform not supported"
#   endif
#elif NV_CC_GNUC
#   if NV_OS_LINUX
#       include "defsgnuclinux.h"
#   elif NV_OS_DARWIN || NV_OS_FREEBSD || NV_OS_OPENBSD
#       include "defsgnucdarwin.h"
#   elif NV_OS_MINGW
#       include "defsgnucwin32.h"
#   elif NV_OS_CYGWIN
#       error "GCC: Cygwin not supported"
#   else
#       error "GCC: Platform not supported"
#   endif
#endif

#endif // NV_CORE_H

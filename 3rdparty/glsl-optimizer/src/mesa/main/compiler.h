/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
 * Copyright (C) 2009  VMware, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


/**
 * \file compiler.h
 * Compiler-related stuff.
 */


#ifndef COMPILER_H
#define COMPILER_H


#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdarg.h>

#include "c99_compat.h" /* inline, __func__, etc. */


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Get standard integer types
 */
#include <stdint.h>


/**
  * Sun compilers define __i386 instead of the gcc-style __i386__
 */
#ifdef __SUNPRO_C
# if !defined(__i386__) && defined(__i386)
#  define __i386__
# elif !defined(__amd64__) && defined(__amd64)
#  define __amd64__
# elif !defined(__sparc__) && defined(__sparc)
#  define __sparc__
# endif
# if !defined(__volatile)
#  define __volatile volatile
# endif
#endif


/**
 * finite macro.
 */
#if defined(_MSC_VER)
#  define finite _finite
#endif


/**
 * Disable assorted warnings
 */
#if defined(_WIN32) && !defined(__CYGWIN__)
#  if !defined(__GNUC__) /* mingw environment */
#    pragma warning( disable : 4068 ) /* unknown pragma */
#    pragma warning( disable : 4710 ) /* function 'foo' not inlined */
#    pragma warning( disable : 4711 ) /* function 'foo' selected for automatic inline expansion */
#    pragma warning( disable : 4127 ) /* conditional expression is constant */
#    if defined(MESA_MINWARN)
#      pragma warning( disable : 4244 ) /* '=' : conversion from 'const double ' to 'float ', possible loss of data */
#      pragma warning( disable : 4018 ) /* '<' : signed/unsigned mismatch */
#      pragma warning( disable : 4305 ) /* '=' : truncation from 'const double ' to 'float ' */
#      pragma warning( disable : 4550 ) /* 'function' undefined; assuming extern returning int */
#      pragma warning( disable : 4761 ) /* integral size mismatch in argument; conversion supplied */
#    endif
#  endif
#endif



/* XXX: Use standard `inline` keyword instead */
#ifndef INLINE
#  define INLINE inline
#endif


/**
 * PUBLIC/USED macros
 *
 * If we build the library with gcc's -fvisibility=hidden flag, we'll
 * use the PUBLIC macro to mark functions that are to be exported.
 *
 * We also need to define a USED attribute, so the optimizer doesn't 
 * inline a static function that we later use in an alias. - ajax
 */
#ifndef PUBLIC
#  if (defined(__GNUC__) && __GNUC__ >= 4) || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#    define PUBLIC __attribute__((visibility("default")))
#    define USED __attribute__((used))
#  else
#    define PUBLIC
#    define USED
#  endif
#endif


/**
 * __builtin_expect macros
 */
#if !defined(__GNUC__)
#  define __builtin_expect(x, y) (x)
#endif

#ifndef likely
#  ifdef __GNUC__
#    define likely(x)   __builtin_expect(!!(x), 1)
#    define unlikely(x) __builtin_expect(!!(x), 0)
#  else
#    define likely(x)   (x)
#    define unlikely(x) (x)
#  endif
#endif

/* XXX: Use standard `__func__` instead */
#ifndef __FUNCTION__
#  define __FUNCTION__ __func__
#endif

/**
 * Either define MESA_BIG_ENDIAN or MESA_LITTLE_ENDIAN, and CPU_TO_LE32.
 * Do not use these unless absolutely necessary!
 * Try to use a runtime test instead.
 * For now, only used by some DRI hardware drivers for color/texel packing.
 */
#if defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN
#if defined(__linux__)
#include <byteswap.h>
#define CPU_TO_LE32( x )	bswap_32( x )
#elif defined(__APPLE__)
#include <CoreFoundation/CFByteOrder.h>
#define CPU_TO_LE32( x )	CFSwapInt32HostToLittle( x )
#elif (defined(_AIX) || defined(__blrts))
static INLINE GLuint CPU_TO_LE32(GLuint x)
{
   return (((x & 0x000000ff) << 24) |
           ((x & 0x0000ff00) <<  8) |
           ((x & 0x00ff0000) >>  8) |
           ((x & 0xff000000) >> 24));
}
#elif defined(__OpenBSD__)
#include <sys/types.h>
#define CPU_TO_LE32( x )	htole32( x )
#else /*__linux__ */
#include <sys/endian.h>
#define CPU_TO_LE32( x )	bswap32( x )
#endif /*__linux__*/
#define MESA_BIG_ENDIAN 1
#else
#define CPU_TO_LE32( x )	( x )
#define MESA_LITTLE_ENDIAN 1
#endif
#define LE32_TO_CPU( x )	CPU_TO_LE32( x )



#if !defined(CAPI) && defined(_WIN32)
#define CAPI _cdecl
#endif


/**
 * Create a macro so that asm functions can be linked into compilers other
 * than GNU C
 */
#ifndef _ASMAPI
#if defined(_WIN32)
#define _ASMAPI __cdecl
#else
#define _ASMAPI
#endif
#ifdef	PTR_DECL_IN_FRONT
#define	_ASMAPIP * _ASMAPI
#else
#define	_ASMAPIP _ASMAPI *
#endif
#endif

#ifdef USE_X86_ASM
#define _NORMAPI _ASMAPI
#define _NORMAPIP _ASMAPIP
#else
#define _NORMAPI
#define _NORMAPIP *
#endif


/* Turn off macro checking systems used by other libraries */
#ifdef CHECK
#undef CHECK
#endif


/**
 * ASSERT macro
 */
#if !defined(_WIN32_WCE)
#if defined(DEBUG)
#  define ASSERT(X)   assert(X)
#else
#  define ASSERT(X)
#endif
#endif


/**
 * Static (compile-time) assertion.
 * Basically, use COND to dimension an array.  If COND is false/zero the
 * array size will be -1 and we'll get a compilation error.
 */
#define STATIC_ASSERT(COND) \
   do { \
      (void) sizeof(char [1 - 2*!(COND)]); \
   } while (0)

/**
 * Unreachable macro. Useful for suppressing "control reaches end of non-void
 * function" warnings.
 */
#if __GNUC__ >= 4 && __GNUC_MINOR__ >= 5
#define unreachable() __builtin_unreachable()
#elif (defined(__clang__) && defined(__has_builtin))
# if __has_builtin(__builtin_unreachable)
#  define unreachable() __builtin_unreachable()
# endif
#endif

#ifndef unreachable
#define unreachable()
#endif

#if (__GNUC__ >= 3)
#define PRINTFLIKE(f, a) __attribute__ ((format(__printf__, f, a)))
#else
#define PRINTFLIKE(f, a)
#endif

#ifndef NULL
#define NULL 0
#endif

/* Used to optionally mark structures with misaligned elements or size as
 * packed, to trade off performance for space.
 */
#if (__GNUC__ >= 3)
#define PACKED __attribute__((__packed__))
#else
#define PACKED
#endif


/**
 * LONGSTRING macro
 * gcc -pedantic warns about long string literals, LONGSTRING silences that.
 */
#if !defined(__GNUC__)
# define LONGSTRING
#else
# define LONGSTRING __extension__
#endif


#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_E
#define M_E (2.7182818284590452354)
#endif

#ifndef M_LOG2E
#define M_LOG2E     (1.4426950408889634074)
#endif

#ifndef ONE_DIV_SQRT_LN2
#define ONE_DIV_SQRT_LN2 (1.201122408786449815)
#endif

#ifndef FLT_MAX_EXP
#define FLT_MAX_EXP 128
#endif


/**
 * USE_IEEE: Determine if we're using IEEE floating point
 */
#if defined(__i386__) || defined(__386__) || defined(__sparc__) || \
    defined(__s390__) || defined(__s390x__) || defined(__powerpc__) || \
    defined(__x86_64__) || \
    defined(__m68k__) || \
    defined(ia64) || defined(__ia64__) || \
    defined(__hppa__) || defined(hpux) || \
    defined(__mips) || defined(_MIPS_ARCH) || \
    defined(__arm__) || defined(__aarch64__) || \
    defined(__sh__) || defined(__m32r__) || \
    (defined(__sun) && defined(_IEEE_754)) || \
    defined(__alpha__)
#define USE_IEEE
#define IEEE_ONE 0x3f800000
#endif


/**
 * START/END_FAST_MATH macros:
 *
 * START_FAST_MATH: Set x86 FPU to faster, 32-bit precision mode (and save
 *                  original mode to a temporary).
 * END_FAST_MATH: Restore x86 FPU to original mode.
 */
#if defined(__GNUC__) && defined(__i386__)
/*
 * Set the x86 FPU control word to guarentee only 32 bits of precision
 * are stored in registers.  Allowing the FPU to store more introduces
 * differences between situations where numbers are pulled out of memory
 * vs. situations where the compiler is able to optimize register usage.
 *
 * In the worst case, we force the compiler to use a memory access to
 * truncate the float, by specifying the 'volatile' keyword.
 */
/* Hardware default: All exceptions masked, extended double precision,
 * round to nearest (IEEE compliant):
 */
#define DEFAULT_X86_FPU		0x037f
/* All exceptions masked, single precision, round to nearest:
 */
#define FAST_X86_FPU		0x003f
/* The fldcw instruction will cause any pending FP exceptions to be
 * raised prior to entering the block, and we clear any pending
 * exceptions before exiting the block.  Hence, asm code has free
 * reign over the FPU while in the fast math block.
 */
#if defined(NO_FAST_MATH)
#define START_FAST_MATH(x)						\
do {									\
   static GLuint mask = DEFAULT_X86_FPU;				\
   __asm__ ( "fnstcw %0" : "=m" (*&(x)) );				\
   __asm__ ( "fldcw %0" : : "m" (mask) );				\
} while (0)
#else
#define START_FAST_MATH(x)						\
do {									\
   static GLuint mask = FAST_X86_FPU;					\
   __asm__ ( "fnstcw %0" : "=m" (*&(x)) );				\
   __asm__ ( "fldcw %0" : : "m" (mask) );				\
} while (0)
#endif
/* Restore original FPU mode, and clear any exceptions that may have
 * occurred in the FAST_MATH block.
 */
#define END_FAST_MATH(x)						\
do {									\
   __asm__ ( "fnclex ; fldcw %0" : : "m" (*&(x)) );			\
} while (0)

#elif defined(_MSC_VER) && defined(_M_IX86)
#define DEFAULT_X86_FPU		0x037f /* See GCC comments above */
#define FAST_X86_FPU		0x003f /* See GCC comments above */
#if defined(NO_FAST_MATH)
#define START_FAST_MATH(x) do {\
	static GLuint mask = DEFAULT_X86_FPU;\
	__asm fnstcw word ptr [x]\
	__asm fldcw word ptr [mask]\
} while(0)
#else
#define START_FAST_MATH(x) do {\
	static GLuint mask = FAST_X86_FPU;\
	__asm fnstcw word ptr [x]\
	__asm fldcw word ptr [mask]\
} while(0)
#endif
#define END_FAST_MATH(x) do {\
	__asm fnclex\
	__asm fldcw word ptr [x]\
} while(0)

#else
#define START_FAST_MATH(x)  x = 0
#define END_FAST_MATH(x)  (void)(x)
#endif


#ifndef Elements
#define Elements(x) (sizeof(x)/sizeof(*(x)))
#endif

#ifdef __cplusplus
/**
 * Macro function that evaluates to true if T is a trivially
 * destructible type -- that is, if its (non-virtual) destructor
 * performs no action and all member variables and base classes are
 * trivially destructible themselves.
 */
#   if defined(__GNUC__)
#      if ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
#         define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#      endif
#   elif (defined(__clang__) && defined(__has_feature))
#      if __has_feature(has_trivial_destructor)
#         define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#      endif
#   endif
#   ifndef HAS_TRIVIAL_DESTRUCTOR
       /* It's always safe (if inefficient) to assume that a
        * destructor is non-trivial.
        */
#      define HAS_TRIVIAL_DESTRUCTOR(T) (false)
#   endif
#endif

#ifdef __cplusplus
}
#endif


#endif /* COMPILER_H */

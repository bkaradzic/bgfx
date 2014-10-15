/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
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
 * \file imports.h
 * Standard C library function wrappers.
 *
 * This file provides wrappers for all the standard C library functions
 * like malloc(), free(), printf(), getenv(), etc.
 */


#ifndef IMPORTS_H
#define IMPORTS_H


#include "compiler.h"
#include "glheader.h"

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************************/
/** Memory macros */
/*@{*/

/** Allocate a structure of type \p T */
#define MALLOC_STRUCT(T)   (struct T *) malloc(sizeof(struct T))
/** Allocate and zero a structure of type \p T */
#define CALLOC_STRUCT(T)   (struct T *) calloc(1, sizeof(struct T))

/*@}*/


/*
 * For GL_ARB_vertex_buffer_object we need to treat vertex array pointers
 * as offsets into buffer stores.  Since the vertex array pointer and
 * buffer store pointer are both pointers and we need to add them, we use
 * this macro.
 * Both pointers/offsets are expressed in bytes.
 */
#define ADD_POINTERS(A, B)  ( (GLubyte *) (A) + (uintptr_t) (B) )


/**
 * Sometimes we treat GLfloats as GLints.  On x86 systems, moving a float
 * as a int (thereby using integer registers instead of FP registers) is
 * a performance win.  Typically, this can be done with ordinary casts.
 * But with gcc's -fstrict-aliasing flag (which defaults to on in gcc 3.0)
 * these casts generate warnings.
 * The following union typedef is used to solve that.
 */
typedef union { GLfloat f; GLint i; GLuint u; } fi_type;



/**********************************************************************
 * Math macros
 */

#define MAX_GLUSHORT	0xffff
#define MAX_GLUINT	0xffffffff

/* Degrees to radians conversion: */
#define DEG2RAD (M_PI/180.0)


/**
 * \name Work-arounds for platforms that lack C99 math functions
 */
/*@{*/
#if (!defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE < 600)) && !defined(_ISOC99_SOURCE) \
   && (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)) \
   && (!defined(_MSC_VER) || (_MSC_VER < 1400))
#define acosf(f) ((float) acos(f))
#define asinf(f) ((float) asin(f))
#define atan2f(x,y) ((float) atan2(x,y))
#define atanf(f) ((float) atan(f))
#define ceilf(f) ((float) ceil(f))
#define cosf(f) ((float) cos(f))
#define coshf(f) ((float) cosh(f))
#define expf(f) ((float) exp(f))
#define exp2f(f) ((float) exp2(f))
#define floorf(f) ((float) floor(f))
#define logf(f) ((float) log(f))

#ifdef ANDROID
#define log2f(f) (logf(f) * (float) (1.0 / M_LN2))
#else
#define log2f(f) ((float) log2(f))
#endif

#define powf(x,y) ((float) pow(x,y))
#define sinf(f) ((float) sin(f))
#define sinhf(f) ((float) sinh(f))
#define sqrtf(f) ((float) sqrt(f))
#define tanf(f) ((float) tan(f))
#define tanhf(f) ((float) tanh(f))
#define acoshf(f) ((float) acosh(f))
#define asinhf(f) ((float) asinh(f))
#define atanhf(f) ((float) atanh(f))
#endif

#if defined(_MSC_VER)
#if _MSC_VER < 1800  /* Not req'd on VS2013 and above */
static inline float truncf(float x) { return x < 0.0f ? ceilf(x) : floorf(x); }
static inline float exp2f(float x) { return powf(2.0f, x); }
static inline float log2f(float x) { return logf(x) * 1.442695041f; }
static inline float asinhf(float x) { return logf(x + sqrtf(x * x + 1.0f)); }
static inline float acoshf(float x) { return logf(x + sqrtf(x * x - 1.0f)); }
static inline float atanhf(float x) { return (logf(1.0f + x) - logf(1.0f - x)) / 2.0f; }
static inline int isblank(int ch) { return ch == ' ' || ch == '\t'; }
#define strtoll(p, e, b) _strtoi64(p, e, b)
#endif /* _MSC_VER < 1800 */
#define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif
/*@}*/


/*
 * signbit() is a macro on Linux.  Not available on Windows.
 */
#ifndef signbit
#define signbit(x) ((x) < 0.0f)
#endif


/** single-precision inverse square root */
static inline float
INV_SQRTF(float x)
{
   /* XXX we could try Quake's fast inverse square root function here */
   return 1.0F / sqrtf(x);
}


/***
 *** LOG2: Log base 2 of float
 ***/
static inline GLfloat LOG2(GLfloat x)
{
#if 0
   /* This is pretty fast, but not accurate enough (only 2 fractional bits).
    * Based on code from http://www.stereopsis.com/log2.html
    */
   const GLfloat y = x * x * x * x;
   const GLuint ix = *((GLuint *) &y);
   const GLuint exp = (ix >> 23) & 0xFF;
   const GLint log2 = ((GLint) exp) - 127;
   return (GLfloat) log2 * (1.0 / 4.0);  /* 4, because of x^4 above */
#endif
   /* Pretty fast, and accurate.
    * Based on code from http://www.flipcode.com/totd/
    */
   fi_type num;
   GLint log_2;
   num.f = x;
   log_2 = ((num.i >> 23) & 255) - 128;
   num.i &= ~(255 << 23);
   num.i += 127 << 23;
   num.f = ((-1.0f/3) * num.f + 2) * num.f - 2.0f/3;
   return num.f + log_2;
}



/***
 *** IS_INF_OR_NAN: test if float is infinite or NaN
 ***/
#if defined(isfinite)
#define IS_INF_OR_NAN(x)        (!isfinite(x))
#elif defined(finite)
#define IS_INF_OR_NAN(x)        (!finite(x))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define IS_INF_OR_NAN(x)        (!isfinite(x))
#else
#define IS_INF_OR_NAN(x)        (!finite(x))
#endif


/***
 *** CEILF: ceiling of float
 *** FLOORF: floor of float
 *** FABSF: absolute value of float
 *** LOGF: the natural logarithm (base e) of the value
 *** EXPF: raise e to the value
 *** LDEXPF: multiply value by an integral power of two
 *** FREXPF: extract mantissa and exponent from value
 ***/
#if defined(__gnu_linux__)
/* C99 functions */
#define CEILF(x)   ceilf(x)
#define FLOORF(x)  floorf(x)
#define FABSF(x)   fabsf(x)
#define LOGF(x)    logf(x)
#define EXPF(x)    expf(x)
#define LDEXPF(x,y)  ldexpf(x,y)
#define FREXPF(x,y)  frexpf(x,y)
#else
#define CEILF(x)   ((GLfloat) ceil(x))
#define FLOORF(x)  ((GLfloat) floor(x))
#define FABSF(x)   ((GLfloat) fabs(x))
#define LOGF(x)    ((GLfloat) log(x))
#define EXPF(x)    ((GLfloat) exp(x))
#define LDEXPF(x,y)  ((GLfloat) ldexp(x,y))
#define FREXPF(x,y)  ((GLfloat) frexp(x,y))
#endif


/**
 * Convert float to int by rounding to nearest integer, away from zero.
 */
static inline int IROUND(float f)
{
   return (int) ((f >= 0.0F) ? (f + 0.5F) : (f - 0.5F));
}



/**
 * Convert positive float to int by rounding to nearest integer.
 */
static inline int IROUND_POS(float f)
{
   assert(f >= 0.0F);
   return (int) (f + 0.5F);
}

#ifdef __x86_64__
#  include <xmmintrin.h>
#endif

/**
 * Convert float to int using a fast method.  The rounding mode may vary.
 */
static inline int F_TO_I(float f)
{
#if defined(USE_X86_ASM) && defined(__GNUC__) && defined(__i386__)
   int r;
   __asm__ ("fistpl %0" : "=m" (r) : "t" (f) : "st");
   return r;
#elif defined(USE_X86_ASM) && defined(_MSC_VER)
   int r;
   _asm {
	 fld f
	 fistp r
	}
   return r;
#elif defined(__x86_64__)
   return _mm_cvt_ss2si(_mm_load_ss(&f));
#else
   return IROUND(f);
#endif
}


/** Return (as an integer) floor of float */
static inline int IFLOOR(float f)
{
#if defined(USE_X86_ASM) && defined(__GNUC__) && defined(__i386__)
   /*
    * IEEE floor for computers that round to nearest or even.
    * 'f' must be between -4194304 and 4194303.
    * This floor operation is done by "(iround(f + .5) + iround(f - .5)) >> 1",
    * but uses some IEEE specific tricks for better speed.
    * Contributed by Josh Vanderhoof
    */
   int ai, bi;
   double af, bf;
   af = (3 << 22) + 0.5 + (double)f;
   bf = (3 << 22) + 0.5 - (double)f;
   /* GCC generates an extra fstp/fld without this. */
   __asm__ ("fstps %0" : "=m" (ai) : "t" (af) : "st");
   __asm__ ("fstps %0" : "=m" (bi) : "t" (bf) : "st");
   return (ai - bi) >> 1;
#else
   int ai, bi;
   double af, bf;
   fi_type u;
   af = (3 << 22) + 0.5 + (double)f;
   bf = (3 << 22) + 0.5 - (double)f;
   u.f = (float) af;  ai = u.i;
   u.f = (float) bf;  bi = u.i;
   return (ai - bi) >> 1;
#endif
}


/** Return (as an integer) ceiling of float */
static inline int ICEIL(float f)
{
#if defined(USE_X86_ASM) && defined(__GNUC__) && defined(__i386__)
   /*
    * IEEE ceil for computers that round to nearest or even.
    * 'f' must be between -4194304 and 4194303.
    * This ceil operation is done by "(iround(f + .5) + iround(f - .5) + 1) >> 1",
    * but uses some IEEE specific tricks for better speed.
    * Contributed by Josh Vanderhoof
    */
   int ai, bi;
   double af, bf;
   af = (3 << 22) + 0.5 + (double)f;
   bf = (3 << 22) + 0.5 - (double)f;
   /* GCC generates an extra fstp/fld without this. */
   __asm__ ("fstps %0" : "=m" (ai) : "t" (af) : "st");
   __asm__ ("fstps %0" : "=m" (bi) : "t" (bf) : "st");
   return (ai - bi + 1) >> 1;
#else
   int ai, bi;
   double af, bf;
   fi_type u;
   af = (3 << 22) + 0.5 + (double)f;
   bf = (3 << 22) + 0.5 - (double)f;
   u.f = (float) af; ai = u.i;
   u.f = (float) bf; bi = u.i;
   return (ai - bi + 1) >> 1;
#endif
}


/**
 * Is x a power of two?
 */
static inline int
_mesa_is_pow_two(int x)
{
   return !(x & (x - 1));
}

/**
 * Round given integer to next higer power of two
 * If X is zero result is undefined.
 *
 * Source for the fallback implementation is
 * Sean Eron Anderson's webpage "Bit Twiddling Hacks"
 * http://graphics.stanford.edu/~seander/bithacks.html
 *
 * When using builtin function have to do some work
 * for case when passed values 1 to prevent hiting
 * undefined result from __builtin_clz. Undefined
 * results would be different depending on optimization
 * level used for build.
 */
static inline int32_t
_mesa_next_pow_two_32(uint32_t x)
{
#ifdef HAVE___BUILTIN_CLZ
	uint32_t y = (x != 1);
	return (1 + y) << ((__builtin_clz(x - y) ^ 31) );
#else
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
#endif
}

static inline int64_t
_mesa_next_pow_two_64(uint64_t x)
{
#ifdef HAVE___BUILTIN_CLZLL
	uint64_t y = (x != 1);
	STATIC_ASSERT(sizeof(x) == sizeof(long long));
	return (1 + y) << ((__builtin_clzll(x - y) ^ 63));
#else
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	x++;
	return x;
#endif
}


/*
 * Returns the floor form of binary logarithm for a 32-bit integer.
 */
static inline GLuint
_mesa_logbase2(GLuint n)
{
#ifdef HAVE___BUILTIN_CLZ
   return (31 - __builtin_clz(n | 1));
#else
   GLuint pos = 0;
   if (n >= 1<<16) { n >>= 16; pos += 16; }
   if (n >= 1<< 8) { n >>=  8; pos +=  8; }
   if (n >= 1<< 4) { n >>=  4; pos +=  4; }
   if (n >= 1<< 2) { n >>=  2; pos +=  2; }
   if (n >= 1<< 1) {           pos +=  1; }
   return pos;
#endif
}


/**
 * Return 1 if this is a little endian machine, 0 if big endian.
 */
static inline GLboolean
_mesa_little_endian(void)
{
   const GLuint ui = 1; /* intentionally not static */
   return *((const GLubyte *) &ui);
}



/**********************************************************************
 * Functions
 */

extern void *
_mesa_align_malloc( size_t bytes, unsigned long alignment );

extern void *
_mesa_align_calloc( size_t bytes, unsigned long alignment );

extern void
_mesa_align_free( void *ptr );

extern void *
_mesa_align_realloc(void *oldBuffer, size_t oldSize, size_t newSize,
                    unsigned long alignment);

extern void *
_mesa_exec_malloc( GLuint size );

extern void 
_mesa_exec_free( void *addr );


#ifndef FFS_DEFINED
#define FFS_DEFINED 1
#ifdef HAVE___BUILTIN_FFS
#define ffs __builtin_ffs
#else
extern int ffs(int i);
#endif

#ifdef HAVE___BUILTIN_FFSLL
#define ffsll __builtin_ffsll
#else
extern int ffsll(long long int i);
#endif
#endif /* FFS_DEFINED */


#ifdef HAVE___BUILTIN_POPCOUNT
#define _mesa_bitcount(i) __builtin_popcount(i)
#else
extern unsigned int
_mesa_bitcount(unsigned int n);
#endif

#ifdef HAVE___BUILTIN_POPCOUNTLL
#define _mesa_bitcount_64(i) __builtin_popcountll(i)
#else
extern unsigned int
_mesa_bitcount_64(uint64_t n);
#endif

/**
 * Find the last (most significant) bit set in a word.
 *
 * Essentially ffs() in the reverse direction.
 */
static inline unsigned int
_mesa_fls(unsigned int n)
{
#ifdef HAVE___BUILTIN_CLZ
   return n == 0 ? 0 : 32 - __builtin_clz(n);
#else
   unsigned int v = 1;

   if (n == 0)
      return 0;

   while (n >>= 1)
       v++;

   return v;
#endif
}

extern int
_mesa_round_to_even(float val);

extern GLhalfARB
_mesa_float_to_half(float f);

extern float
_mesa_half_to_float(GLhalfARB h);

extern char *
_mesa_strdup( const char *s );

extern float
_mesa_strtof( const char *s, char **end );

extern unsigned int
_mesa_str_checksum(const char *str);

extern int
_mesa_snprintf( char *str, size_t size, const char *fmt, ... ) PRINTFLIKE(3, 4);

extern int
_mesa_vsnprintf(char *str, size_t size, const char *fmt, va_list arg);


#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf _snprintf
#endif


#ifdef __cplusplus
}
#endif


#endif /* IMPORTS_H */

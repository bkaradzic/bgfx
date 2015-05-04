/**
 * \file imports.c
 * Standard C library function wrappers.
 * 
 * Imports are services which the device driver or window system or
 * operating system provides to the core renderer.  The core renderer (Mesa)
 * will call these functions in order to do memory allocation, simple I/O,
 * etc.
 *
 * Some drivers will want to override/replace this file with something
 * specialized, but that'll be rare.
 *
 * Eventually, I want to move roll the glheader.h file into this.
 *
 * \todo Functions still needed:
 * - scanf
 * - qsort
 * - rand and RAND_MAX
 */

/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
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



#include "imports.h"

#ifdef _GNU_SOURCE
#include <locale.h>
#ifdef __APPLE__
#include <xlocale.h>
#endif
#endif


#ifdef _WIN32
#define vsnprintf _vsnprintf
#elif defined(__IBMC__) || defined(__IBMCPP__)
extern int vsnprintf(char *str, size_t count, const char *fmt, va_list arg);
#endif

/**********************************************************************/
/** \name Memory */
/*@{*/

/**
 * Allocate aligned memory.
 *
 * \param bytes number of bytes to allocate.
 * \param alignment alignment (must be greater than zero).
 * 
 * Allocates extra memory to accommodate rounding up the address for
 * alignment and to record the real malloc address.
 *
 * \sa _mesa_align_free().
 */
void *
_mesa_align_malloc(size_t bytes, unsigned long alignment)
{
#if defined(HAVE_POSIX_MEMALIGN)
   void *mem;
   int err = posix_memalign(& mem, alignment, bytes);
   if (err)
      return NULL;
   return mem;
#elif defined(_WIN32) && defined(_MSC_VER)
   return _aligned_malloc(bytes, alignment);
#else
   uintptr_t ptr, buf;

   ASSERT( alignment > 0 );

   ptr = (uintptr_t)malloc(bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(uintptr_t)(alignment - 1);
   *(uintptr_t *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *) buf;
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Same as _mesa_align_malloc(), but using calloc(1, ) instead of
 * malloc()
 */
void *
_mesa_align_calloc(size_t bytes, unsigned long alignment)
{
#if defined(HAVE_POSIX_MEMALIGN)
   void *mem;
   
   mem = _mesa_align_malloc(bytes, alignment);
   if (mem != NULL) {
      (void) memset(mem, 0, bytes);
   }

   return mem;
#elif defined(_WIN32) && defined(_MSC_VER)
   void *mem;

   mem = _aligned_malloc(bytes, alignment);
   if (mem != NULL) {
      (void) memset(mem, 0, bytes);
   }

   return mem;
#else
   uintptr_t ptr, buf;

   ASSERT( alignment > 0 );

   ptr = (uintptr_t)calloc(1, bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(uintptr_t)(alignment - 1);
   *(uintptr_t *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *)buf;
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Free memory which was allocated with either _mesa_align_malloc()
 * or _mesa_align_calloc().
 * \param ptr pointer to the memory to be freed.
 * The actual address to free is stored in the word immediately before the
 * address the client sees.
 * Note that it is legal to pass NULL pointer to this function and will be
 * handled accordingly.
 */
void
_mesa_align_free(void *ptr)
{
#if defined(HAVE_POSIX_MEMALIGN)
   free(ptr);
#elif defined(_WIN32) && defined(_MSC_VER)
   _aligned_free(ptr);
#else
   if (ptr) {
      void **cubbyHole = (void **) ((char *) ptr - sizeof(void *));
      void *realAddr = *cubbyHole;
      free(realAddr);
   }
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Reallocate memory, with alignment.
 */
void *
_mesa_align_realloc(void *oldBuffer, size_t oldSize, size_t newSize,
                    unsigned long alignment)
{
#if defined(_WIN32) && defined(_MSC_VER)
   (void) oldSize;
   return _aligned_realloc(oldBuffer, newSize, alignment);
#else
   const size_t copySize = (oldSize < newSize) ? oldSize : newSize;
   void *newBuf = _mesa_align_malloc(newSize, alignment);
   if (newBuf && oldBuffer && copySize > 0) {
      memcpy(newBuf, oldBuffer, copySize);
   }

   _mesa_align_free(oldBuffer);
   return newBuf;
#endif
}

/*@}*/


/**********************************************************************/
/** \name Math */
/*@{*/


#ifndef HAVE___BUILTIN_FFS
/**
 * Find the first bit set in a word.
 */
int
ffs(int i)
{
   register int bit = 0;
   if (i != 0) {
      if ((i & 0xffff) == 0) {
         bit += 16;
         i >>= 16;
      }
      if ((i & 0xff) == 0) {
         bit += 8;
         i >>= 8;
      }
      if ((i & 0xf) == 0) {
         bit += 4;
         i >>= 4;
      }
      while ((i & 1) == 0) {
         bit++;
         i >>= 1;
      }
      bit++;
   }
   return bit;
}
#endif

#ifndef HAVE___BUILTIN_FFSLL
/**
 * Find position of first bit set in given value.
 * XXX Warning: this function can only be used on 64-bit systems!
 * \return  position of least-significant bit set, starting at 1, return zero
 *          if no bits set.
 */
int
ffsll(long long int val)
{
   int bit;

   assert(sizeof(val) == 8);

   bit = ffs((int) val);
   if (bit != 0)
      return bit;

   bit = ffs((int) (val >> 32));
   if (bit != 0)
      return 32 + bit;

   return 0;
}
#endif


#ifndef HAVE___BUILTIN_POPCOUNT
/**
 * Return number of bits set in given GLuint.
 */
unsigned int
_mesa_bitcount(unsigned int n)
{
   unsigned int bits;
   for (bits = 0; n > 0; n = n >> 1) {
      bits += (n & 1);
   }
   return bits;
}
#endif

#ifndef HAVE___BUILTIN_POPCOUNTLL
/**
 * Return number of bits set in given 64-bit uint.
 */
unsigned int
_mesa_bitcount_64(uint64_t n)
{
   unsigned int bits;
   for (bits = 0; n > 0; n = n >> 1) {
      bits += (n & 1);
   }
   return bits;
}
#endif


/* Using C99 rounding functions for roundToEven() implementation is
 * difficult, because round(), rint, and nearbyint() are affected by
 * fesetenv(), which the application may have done for its own
 * purposes.  Mesa's IROUND macro is close to what we want, but it
 * rounds away from 0 on n + 0.5.
 */
int
_mesa_round_to_even(float val)
{
   int rounded = IROUND(val);

   if (val - floor(val) == 0.5) {
      if (rounded % 2 != 0)
         rounded += val > 0 ? -1 : 1;
   }

   return rounded;
}


/**
 * Convert a 4-byte float to a 2-byte half float.
 *
 * Not all float32 values can be represented exactly as a float16 value. We
 * round such intermediate float32 values to the nearest float16. When the
 * float32 lies exactly between to float16 values, we round to the one with
 * an even mantissa.
 *
 * This rounding behavior has several benefits:
 *   - It has no sign bias.
 *
 *   - It reproduces the behavior of real hardware: opcode F32TO16 in Intel's
 *     GPU ISA.
 *
 *   - By reproducing the behavior of the GPU (at least on Intel hardware),
 *     compile-time evaluation of constant packHalf2x16 GLSL expressions will
 *     result in the same value as if the expression were executed on the GPU.
 */
GLhalfARB
_mesa_float_to_half(float val)
{
   const fi_type fi = {val};
   const int flt_m = fi.i & 0x7fffff;
   const int flt_e = (fi.i >> 23) & 0xff;
   const int flt_s = (fi.i >> 31) & 0x1;
   int s, e, m = 0;
   GLhalfARB result;
   
   /* sign bit */
   s = flt_s;

   /* handle special cases */
   if ((flt_e == 0) && (flt_m == 0)) {
      /* zero */
      /* m = 0; - already set */
      e = 0;
   }
   else if ((flt_e == 0) && (flt_m != 0)) {
      /* denorm -- denorm float maps to 0 half */
      /* m = 0; - already set */
      e = 0;
   }
   else if ((flt_e == 0xff) && (flt_m == 0)) {
      /* infinity */
      /* m = 0; - already set */
      e = 31;
   }
   else if ((flt_e == 0xff) && (flt_m != 0)) {
      /* NaN */
      m = 1;
      e = 31;
   }
   else {
      /* regular number */
      const int new_exp = flt_e - 127;
      if (new_exp < -14) {
         /* The float32 lies in the range (0.0, min_normal16) and is rounded
          * to a nearby float16 value. The result will be either zero, subnormal,
          * or normal.
          */
         e = 0;
         m = _mesa_round_to_even((1 << 24) * fabsf(fi.f));
      }
      else if (new_exp > 15) {
         /* map this value to infinity */
         /* m = 0; - already set */
         e = 31;
      }
      else {
         /* The float32 lies in the range
          *   [min_normal16, max_normal16 + max_step16)
          * and is rounded to a nearby float16 value. The result will be
          * either normal or infinite.
          */
         e = new_exp + 15;
         m = _mesa_round_to_even(flt_m / (float) (1 << 13));
      }
   }

   assert(0 <= m && m <= 1024);
   if (m == 1024) {
      /* The float32 was rounded upwards into the range of the next exponent,
       * so bump the exponent. This correctly handles the case where f32
       * should be rounded up to float16 infinity.
       */
      ++e;
      m = 0;
   }

   result = (s << 15) | (e << 10) | m;
   return result;
}


/**
 * Convert a 2-byte half float to a 4-byte float.
 * Based on code from:
 * http://www.opengl.org/discussion_boards/ubb/Forum3/HTML/008786.html
 */
float
_mesa_half_to_float(GLhalfARB val)
{
   /* XXX could also use a 64K-entry lookup table */
   const int m = val & 0x3ff;
   const int e = (val >> 10) & 0x1f;
   const int s = (val >> 15) & 0x1;
   int flt_m, flt_e, flt_s;
   fi_type fi;
   float result;

   /* sign bit */
   flt_s = s;

   /* handle special cases */
   if ((e == 0) && (m == 0)) {
      /* zero */
      flt_m = 0;
      flt_e = 0;
   }
   else if ((e == 0) && (m != 0)) {
      /* denorm -- denorm half will fit in non-denorm single */
      const float half_denorm = 1.0f / 16384.0f; /* 2^-14 */
      float mantissa = ((float) (m)) / 1024.0f;
      float sign = s ? -1.0f : 1.0f;
      return sign * mantissa * half_denorm;
   }
   else if ((e == 31) && (m == 0)) {
      /* infinity */
      flt_e = 0xff;
      flt_m = 0;
   }
   else if ((e == 31) && (m != 0)) {
      /* NaN */
      flt_e = 0xff;
      flt_m = 1;
   }
   else {
      /* regular */
      flt_e = e + 112;
      flt_m = m << 13;
   }

   fi.i = (flt_s << 31) | (flt_e << 23) | flt_m;
   result = fi.f;
   return result;
}

/*@}*/


/**********************************************************************/
/** \name String */
/*@{*/

/**
 * Implemented using malloc() and strcpy.
 * Note that NULL is handled accordingly.
 */
char *
_mesa_strdup( const char *s )
{
   if (s) {
      size_t l = strlen(s);
      char *s2 = malloc(l + 1);
      if (s2)
         strcpy(s2, s);
      return s2;
   }
   else {
      return NULL;
   }
}

/** Wrapper around strtof() */
float
_mesa_strtof( const char *s, char **end )
{
#if defined(_GNU_SOURCE) && !defined(__CYGWIN__) && !defined(__FreeBSD__) && \
   !defined(ANDROID) && !defined(__HAIKU__) && !defined(__UCLIBC__) && \
   !defined(__NetBSD__)
   static locale_t loc = NULL;
   if (!loc) {
      loc = newlocale(LC_CTYPE_MASK, "C", NULL);
   }
   return strtof_l(s, end, loc);
#elif defined(_ISOC99_SOURCE) || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 600)
   return strtof(s, end);
#else
   return (float)strtod(s, end);
#endif
}

/** Compute simple checksum/hash for a string */
unsigned int
_mesa_str_checksum(const char *str)
{
   /* This could probably be much better */
   unsigned int sum, i;
   const char *c;
   sum = i = 1;
   for (c = str; *c; c++, i++)
      sum += *c * (i % 100);
   return sum + i;
}


/*@}*/


/** Needed due to #ifdef's, above. */
int
_mesa_vsnprintf(char *str, size_t size, const char *fmt, va_list args)
{
   return vsnprintf( str, size, fmt, args);
}

/** Wrapper around vsnprintf() */
int
_mesa_snprintf( char *str, size_t size, const char *fmt, ... )
{
   int r;
   va_list args;
   va_start( args, fmt );  
   r = vsnprintf( str, size, fmt, args );
   va_end( args );
   return r;
}



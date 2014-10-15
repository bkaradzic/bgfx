/*
 * Copyright © 2014 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef UTIL_MACROS_H
#define UTIL_MACROS_H

/* Compute the size of an array */
#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))
#endif


/**
 * __builtin_expect macros
 */
#if !defined(HAVE___BUILTIN_EXPECT)
#  define __builtin_expect(x, y) (x)
#endif

#ifndef likely
#  ifdef HAVE___BUILTIN_EXPECT
#    define likely(x)   __builtin_expect(!!(x), 1)
#    define unlikely(x) __builtin_expect(!!(x), 0)
#  else
#    define likely(x)   (x)
#    define unlikely(x) (x)
#  endif
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
#ifdef HAVE___BUILTIN_UNREACHABLE
#define unreachable(str)    \
do {                        \
   assert(!str);            \
   __builtin_unreachable(); \
} while (0)
#endif

#ifndef unreachable
#define unreachable(str)
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_FLATTEN
#define FLATTEN __attribute__((__flatten__))
#else
#define FLATTEN
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_FORMAT
#define PRINTFLIKE(f, a) __attribute__ ((format(__printf__, f, a)))
#else
#define PRINTFLIKE(f, a)
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_MALLOC
#define MALLOCLIKE __attribute__((__malloc__))
#else
#define MALLOCLIKE
#endif

/* Used to optionally mark structures with misaligned elements or size as
 * packed, to trade off performance for space.
 */
#ifdef HAVE_FUNC_ATTRIBUTE_PACKED
#define PACKED __attribute__((__packed__))
#else
#define PACKED
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

#endif /* UTIL_MACROS_H */

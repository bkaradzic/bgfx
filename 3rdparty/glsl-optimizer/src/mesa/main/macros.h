/**
 * \file macros.h
 * A collection of useful macros.
 */

/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
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


#ifndef MACROS_H
#define MACROS_H

#include "imports.h"


/**
 * \name Integer / float conversion for colors, normals, etc.
 */
/*@{*/

/** Convert GLubyte in [0,255] to GLfloat in [0.0,1.0] */
extern GLfloat _mesa_ubyte_to_float_color_tab[256];
#define UBYTE_TO_FLOAT(u) _mesa_ubyte_to_float_color_tab[(unsigned int)(u)]

/** Convert GLfloat in [0.0,1.0] to GLubyte in [0,255] */
#define FLOAT_TO_UBYTE(X)   ((GLubyte) (GLint) ((X) * 255.0F))


/** Convert GLbyte in [-128,127] to GLfloat in [-1.0,1.0] */
#define BYTE_TO_FLOAT(B)    ((2.0F * (B) + 1.0F) * (1.0F/255.0F))

/** Convert GLfloat in [-1.0,1.0] to GLbyte in [-128,127] */
#define FLOAT_TO_BYTE(X)    ( (((GLint) (255.0F * (X))) - 1) / 2 )


/** Convert GLbyte to GLfloat while preserving zero */
#define BYTE_TO_FLOATZ(B)   ((B) == 0 ? 0.0F : BYTE_TO_FLOAT(B))


/** Convert GLbyte in [-128,127] to GLfloat in [-1.0,1.0], texture/fb data */
#define BYTE_TO_FLOAT_TEX(B)    ((B) == -128 ? -1.0F : (B) * (1.0F/127.0F))

/** Convert GLfloat in [-1.0,1.0] to GLbyte in [-128,127], texture/fb data */
#define FLOAT_TO_BYTE_TEX(X)    CLAMP( (GLint) (127.0F * (X)), -128, 127 )

/** Convert GLushort in [0,65535] to GLfloat in [0.0,1.0] */
#define USHORT_TO_FLOAT(S)  ((GLfloat) (S) * (1.0F / 65535.0F))

/** Convert GLfloat in [0.0,1.0] to GLushort in [0, 65535] */
#define FLOAT_TO_USHORT(X)   ((GLuint) ((X) * 65535.0F))


/** Convert GLshort in [-32768,32767] to GLfloat in [-1.0,1.0] */
#define SHORT_TO_FLOAT(S)   ((2.0F * (S) + 1.0F) * (1.0F/65535.0F))

/** Convert GLfloat in [-1.0,1.0] to GLshort in [-32768,32767] */
#define FLOAT_TO_SHORT(X)   ( (((GLint) (65535.0F * (X))) - 1) / 2 )

/** Convert GLshort to GLfloat while preserving zero */
#define SHORT_TO_FLOATZ(S)   ((S) == 0 ? 0.0F : SHORT_TO_FLOAT(S))


/** Convert GLshort in [-32768,32767] to GLfloat in [-1.0,1.0], texture/fb data */
#define SHORT_TO_FLOAT_TEX(S)    ((S) == -32768 ? -1.0F : (S) * (1.0F/32767.0F))

/** Convert GLfloat in [-1.0,1.0] to GLshort in [-32768,32767], texture/fb data */
#define FLOAT_TO_SHORT_TEX(X)    ( (GLint) (32767.0F * (X)) )


/** Convert GLuint in [0,4294967295] to GLfloat in [0.0,1.0] */
#define UINT_TO_FLOAT(U)    ((GLfloat) ((U) * (1.0F / 4294967295.0)))

/** Convert GLfloat in [0.0,1.0] to GLuint in [0,4294967295] */
#define FLOAT_TO_UINT(X)    ((GLuint) ((X) * 4294967295.0))


/** Convert GLint in [-2147483648,2147483647] to GLfloat in [-1.0,1.0] */
#define INT_TO_FLOAT(I)     ((GLfloat) ((2.0F * (I) + 1.0F) * (1.0F/4294967294.0)))

/** Convert GLfloat in [-1.0,1.0] to GLint in [-2147483648,2147483647] */
/* causes overflow:
#define FLOAT_TO_INT(X)     ( (((GLint) (4294967294.0 * (X))) - 1) / 2 )
*/
/* a close approximation: */
#define FLOAT_TO_INT(X)     ( (GLint) (2147483647.0 * (X)) )

/** Convert GLint in [-2147483648,2147483647] to GLfloat in [-1.0,1.0], texture/fb data */
#define INT_TO_FLOAT_TEX(I)    ((I) == -2147483648 ? -1.0F : (I) * (1.0F/2147483647.0))

/** Convert GLfloat in [-1.0,1.0] to GLint in [-2147483648,2147483647], texture/fb data */
#define FLOAT_TO_INT_TEX(X)    ( (GLint) (2147483647.0 * (X)) )


#define BYTE_TO_UBYTE(b)   ((GLubyte) ((b) < 0 ? 0 : (GLubyte) (b)))
#define SHORT_TO_UBYTE(s)  ((GLubyte) ((s) < 0 ? 0 : (GLubyte) ((s) >> 7)))
#define USHORT_TO_UBYTE(s) ((GLubyte) ((s) >> 8))
#define INT_TO_UBYTE(i)    ((GLubyte) ((i) < 0 ? 0 : (GLubyte) ((i) >> 23)))
#define UINT_TO_UBYTE(i)   ((GLubyte) ((i) >> 24))


#define BYTE_TO_USHORT(b)  ((b) < 0 ? 0 : ((GLushort) (((b) * 65535) / 255)))
#define UBYTE_TO_USHORT(b) (((GLushort) (b) << 8) | (GLushort) (b))
#define SHORT_TO_USHORT(s) ((s) < 0 ? 0 : ((GLushort) (((s) * 65535 / 32767))))
#define INT_TO_USHORT(i)   ((i) < 0 ? 0 : ((GLushort) ((i) >> 15)))
#define UINT_TO_USHORT(i)  ((i) < 0 ? 0 : ((GLushort) ((i) >> 16)))
#define UNCLAMPED_FLOAT_TO_USHORT(us, f)  \
        us = ( (GLushort) F_TO_I( CLAMP((f), 0.0F, 1.0F) * 65535.0F) )
#define CLAMPED_FLOAT_TO_USHORT(us, f)  \
        us = ( (GLushort) F_TO_I( (f) * 65535.0F) )

#define UNCLAMPED_FLOAT_TO_SHORT(s, f)  \
        s = ( (GLshort) F_TO_I( CLAMP((f), -1.0F, 1.0F) * 32767.0F) )

/***
 *** UNCLAMPED_FLOAT_TO_UBYTE: clamp float to [0,1] and map to ubyte in [0,255]
 *** CLAMPED_FLOAT_TO_UBYTE: map float known to be in [0,1] to ubyte in [0,255]
 ***/
#ifndef DEBUG
/* This function/macro is sensitive to precision.  Test very carefully
 * if you change it!
 */
#define UNCLAMPED_FLOAT_TO_UBYTE(UB, FLT)				\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (FLT);						\
           if (__tmp.i < 0)						\
              UB = (GLubyte) 0;						\
           else if (__tmp.i >= IEEE_ONE)				\
              UB = (GLubyte) 255;					\
           else {							\
              __tmp.f = __tmp.f * (255.0F/256.0F) + 32768.0F;		\
              UB = (GLubyte) __tmp.i;					\
           }								\
        } while (0)
#define CLAMPED_FLOAT_TO_UBYTE(UB, FLT)					\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (FLT) * (255.0F/256.0F) + 32768.0F;		\
           UB = (GLubyte) __tmp.i;					\
        } while (0)
#else
#define UNCLAMPED_FLOAT_TO_UBYTE(ub, f) \
	ub = ((GLubyte) F_TO_I(CLAMP((f), 0.0F, 1.0F) * 255.0F))
#define CLAMPED_FLOAT_TO_UBYTE(ub, f) \
	ub = ((GLubyte) F_TO_I((f) * 255.0F))
#endif

static inline GLfloat INT_AS_FLT(GLint i)
{
   fi_type tmp;
   tmp.i = i;
   return tmp.f;
}

static inline GLfloat UINT_AS_FLT(GLuint u)
{
   fi_type tmp;
   tmp.u = u;
   return tmp.f;
}

static inline unsigned FLT_AS_UINT(float f)
{
   fi_type tmp;
   tmp.f = f;
   return tmp.u;
}

/**
 * Convert a floating point value to an unsigned fixed point value.
 *
 * \param frac_bits   The number of bits used to store the fractional part.
 */
static inline uint32_t
U_FIXED(float value, uint32_t frac_bits)
{
   value *= (1 << frac_bits);
   return value < 0.0f ? 0 : (uint32_t) value;
}

/**
 * Convert a floating point value to an signed fixed point value.
 *
 * \param frac_bits   The number of bits used to store the fractional part.
 */
static inline int32_t
S_FIXED(float value, uint32_t frac_bits)
{
   return (int32_t) (value * (1 << frac_bits));
}
/*@}*/


/** Stepping a GLfloat pointer by a byte stride */
#define STRIDE_F(p, i)  (p = (GLfloat *)((GLubyte *)p + i))
/** Stepping a GLuint pointer by a byte stride */
#define STRIDE_UI(p, i)  (p = (GLuint *)((GLubyte *)p + i))
/** Stepping a GLubyte[4] pointer by a byte stride */
#define STRIDE_4UB(p, i)  (p = (GLubyte (*)[4])((GLubyte *)p + i))
/** Stepping a GLfloat[4] pointer by a byte stride */
#define STRIDE_4F(p, i)  (p = (GLfloat (*)[4])((GLubyte *)p + i))
/** Stepping a \p t pointer by a byte stride */
#define STRIDE_T(p, t, i)  (p = (t)((GLubyte *)p + i))


/**********************************************************************/
/** \name 4-element vector operations */
/*@{*/

/** Zero */
#define ZERO_4V( DST )  (DST)[0] = (DST)[1] = (DST)[2] = (DST)[3] = 0

/** Test for equality */
#define TEST_EQ_4V(a,b)  ((a)[0] == (b)[0] &&   \
              (a)[1] == (b)[1] &&   \
              (a)[2] == (b)[2] &&   \
              (a)[3] == (b)[3])

/** Test for equality (unsigned bytes) */
static inline GLboolean
TEST_EQ_4UBV(const GLubyte a[4], const GLubyte b[4])
{
#if defined(__i386__)
   return *((const GLuint *) a) == *((const GLuint *) b);
#else
   return TEST_EQ_4V(a, b);
#endif
}


/** Copy a 4-element vector */
#define COPY_4V( DST, SRC )         \
do {                                \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
   (DST)[2] = (SRC)[2];             \
   (DST)[3] = (SRC)[3];             \
} while (0)

/** Copy a 4-element unsigned byte vector */
static inline void
COPY_4UBV(GLubyte dst[4], const GLubyte src[4])
{
#if defined(__i386__)
   *((GLuint *) dst) = *((GLuint *) src);
#else
   /* The GLuint cast might fail if DST or SRC are not dword-aligned (RISC) */
   COPY_4V(dst, src);
#endif
}

/** Copy a 4-element float vector */
static inline void
COPY_4FV(GLfloat dst[4], const GLfloat src[4])
{
   /* memcpy seems to be most efficient */
   memcpy(dst, src, sizeof(GLfloat) * 4);
}

/** Copy \p SZ elements into a 4-element vector */
#define COPY_SZ_4V(DST, SZ, SRC)  \
do {                              \
   switch (SZ) {                  \
   case 4: (DST)[3] = (SRC)[3];   \
   case 3: (DST)[2] = (SRC)[2];   \
   case 2: (DST)[1] = (SRC)[1];   \
   case 1: (DST)[0] = (SRC)[0];   \
   }                              \
} while(0)

/** Copy \p SZ elements into a homegeneous (4-element) vector, giving
 * default values to the remaining */
#define COPY_CLEAN_4V(DST, SZ, SRC)  \
do {                                 \
      ASSIGN_4V( DST, 0, 0, 0, 1 );  \
      COPY_SZ_4V( DST, SZ, SRC );    \
} while (0)

/** Subtraction */
#define SUB_4V( DST, SRCA, SRCB )           \
do {                                        \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] - (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] - (SRCB)[3];     \
} while (0)

/** Addition */
#define ADD_4V( DST, SRCA, SRCB )           \
do {                                        \
      (DST)[0] = (SRCA)[0] + (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] + (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] + (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] + (SRCB)[3];     \
} while (0)

/** Element-wise multiplication */
#define SCALE_4V( DST, SRCA, SRCB )         \
do {                                        \
      (DST)[0] = (SRCA)[0] * (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] * (SRCB)[1];     \
      (DST)[2] = (SRCA)[2] * (SRCB)[2];     \
      (DST)[3] = (SRCA)[3] * (SRCB)[3];     \
} while (0)

/** In-place addition */
#define ACC_4V( DST, SRC )          \
do {                                \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
      (DST)[2] += (SRC)[2];         \
      (DST)[3] += (SRC)[3];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_4V( DST, SRCA, SRCB )     \
do {                                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
      (DST)[2] += (SRCA)[2] * (SRCB)[2];    \
      (DST)[3] += (SRCA)[3] * (SRCB)[3];    \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_4V( DST, S, SRCB ) \
do {                                        \
      (DST)[0] += S * (SRCB)[0];            \
      (DST)[1] += S * (SRCB)[1];            \
      (DST)[2] += S * (SRCB)[2];            \
      (DST)[3] += S * (SRCB)[3];            \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_4V( DST, S, SRCB ) \
do {                                    \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
      (DST)[2] = S * (SRCB)[2];         \
      (DST)[3] = S * (SRCB)[3];         \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_4V( DST, S ) \
do {                                   \
      (DST)[0] *= S;                   \
      (DST)[1] *= S;                   \
      (DST)[2] *= S;                   \
      (DST)[3] *= S;                   \
} while (0)

/** Assignment */
#define ASSIGN_4V( V, V0, V1, V2, V3 )  \
do {                                    \
    V[0] = V0;                          \
    V[1] = V1;                          \
    V[2] = V2;                          \
    V[3] = V3;                          \
} while(0)

/*@}*/


/**********************************************************************/
/** \name 3-element vector operations*/
/*@{*/

/** Zero */
#define ZERO_3V( DST )  (DST)[0] = (DST)[1] = (DST)[2] = 0

/** Test for equality */
#define TEST_EQ_3V(a,b)  \
   ((a)[0] == (b)[0] &&  \
    (a)[1] == (b)[1] &&  \
    (a)[2] == (b)[2])

/** Copy a 3-element vector */
#define COPY_3V( DST, SRC )         \
do {                                \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
   (DST)[2] = (SRC)[2];             \
} while (0)

/** Copy a 3-element vector with cast */
#define COPY_3V_CAST( DST, SRC, CAST )  \
do {                                    \
   (DST)[0] = (CAST)(SRC)[0];           \
   (DST)[1] = (CAST)(SRC)[1];           \
   (DST)[2] = (CAST)(SRC)[2];           \
} while (0)

/** Copy a 3-element float vector */
#define COPY_3FV( DST, SRC )        \
do {                                \
   const GLfloat *_tmp = (SRC);     \
   (DST)[0] = _tmp[0];              \
   (DST)[1] = _tmp[1];              \
   (DST)[2] = _tmp[2];              \
} while (0)

/** Subtraction */
#define SUB_3V( DST, SRCA, SRCB )        \
do {                                     \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];  \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];  \
      (DST)[2] = (SRCA)[2] - (SRCB)[2];  \
} while (0)

/** Addition */
#define ADD_3V( DST, SRCA, SRCB )       \
do {                                    \
      (DST)[0] = (SRCA)[0] + (SRCB)[0]; \
      (DST)[1] = (SRCA)[1] + (SRCB)[1]; \
      (DST)[2] = (SRCA)[2] + (SRCB)[2]; \
} while (0)

/** In-place scalar multiplication */
#define SCALE_3V( DST, SRCA, SRCB )     \
do {                                    \
      (DST)[0] = (SRCA)[0] * (SRCB)[0]; \
      (DST)[1] = (SRCA)[1] * (SRCB)[1]; \
      (DST)[2] = (SRCA)[2] * (SRCB)[2]; \
} while (0)

/** In-place element-wise multiplication */
#define SELF_SCALE_3V( DST, SRC )   \
do {                                \
      (DST)[0] *= (SRC)[0];         \
      (DST)[1] *= (SRC)[1];         \
      (DST)[2] *= (SRC)[2];         \
} while (0)

/** In-place addition */
#define ACC_3V( DST, SRC )          \
do {                                \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
      (DST)[2] += (SRC)[2];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_3V( DST, SRCA, SRCB )     \
do {                                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
      (DST)[2] += (SRCA)[2] * (SRCB)[2];    \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_3V( DST, S, SRCB ) \
do {                                    \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
      (DST)[2] = S * (SRCB)[2];         \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_3V( DST, S, SRCB ) \
do {                                        \
      (DST)[0] += S * (SRCB)[0];            \
      (DST)[1] += S * (SRCB)[1];            \
      (DST)[2] += S * (SRCB)[2];            \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_3V( DST, S ) \
do {                                   \
      (DST)[0] *= S;                   \
      (DST)[1] *= S;                   \
      (DST)[2] *= S;                   \
} while (0)

/** In-place scalar addition */
#define ACC_SCALAR_3V( DST, S )     \
do {                                \
      (DST)[0] += S;                \
      (DST)[1] += S;                \
      (DST)[2] += S;                \
} while (0)

/** Assignment */
#define ASSIGN_3V( V, V0, V1, V2 )  \
do {                                \
    V[0] = V0;                      \
    V[1] = V1;                      \
    V[2] = V2;                      \
} while(0)

/*@}*/


/**********************************************************************/
/** \name 2-element vector operations*/
/*@{*/

/** Zero */
#define ZERO_2V( DST )  (DST)[0] = (DST)[1] = 0

/** Copy a 2-element vector */
#define COPY_2V( DST, SRC )         \
do {                        \
   (DST)[0] = (SRC)[0];             \
   (DST)[1] = (SRC)[1];             \
} while (0)

/** Copy a 2-element vector with cast */
#define COPY_2V_CAST( DST, SRC, CAST )      \
do {                        \
   (DST)[0] = (CAST)(SRC)[0];           \
   (DST)[1] = (CAST)(SRC)[1];           \
} while (0)

/** Copy a 2-element float vector */
#define COPY_2FV( DST, SRC )            \
do {                        \
   const GLfloat *_tmp = (SRC);         \
   (DST)[0] = _tmp[0];              \
   (DST)[1] = _tmp[1];              \
} while (0)

/** Subtraction */
#define SUB_2V( DST, SRCA, SRCB )       \
do {                        \
      (DST)[0] = (SRCA)[0] - (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] - (SRCB)[1];     \
} while (0)

/** Addition */
#define ADD_2V( DST, SRCA, SRCB )       \
do {                        \
      (DST)[0] = (SRCA)[0] + (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] + (SRCB)[1];     \
} while (0)

/** In-place scalar multiplication */
#define SCALE_2V( DST, SRCA, SRCB )     \
do {                        \
      (DST)[0] = (SRCA)[0] * (SRCB)[0];     \
      (DST)[1] = (SRCA)[1] * (SRCB)[1];     \
} while (0)

/** In-place addition */
#define ACC_2V( DST, SRC )          \
do {                        \
      (DST)[0] += (SRC)[0];         \
      (DST)[1] += (SRC)[1];         \
} while (0)

/** Element-wise multiplication and addition */
#define ACC_SCALE_2V( DST, SRCA, SRCB )     \
do {                        \
      (DST)[0] += (SRCA)[0] * (SRCB)[0];    \
      (DST)[1] += (SRCA)[1] * (SRCB)[1];    \
} while (0)

/** Scalar multiplication */
#define SCALE_SCALAR_2V( DST, S, SRCB )     \
do {                        \
      (DST)[0] = S * (SRCB)[0];         \
      (DST)[1] = S * (SRCB)[1];         \
} while (0)

/** In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_2V( DST, S, SRCB ) \
do {                        \
      (DST)[0] += S * (SRCB)[0];        \
      (DST)[1] += S * (SRCB)[1];        \
} while (0)

/** In-place scalar multiplication */
#define SELF_SCALE_SCALAR_2V( DST, S )      \
do {                        \
      (DST)[0] *= S;                \
      (DST)[1] *= S;                \
} while (0)

/** In-place scalar addition */
#define ACC_SCALAR_2V( DST, S )         \
do {                        \
      (DST)[0] += S;                \
      (DST)[1] += S;                \
} while (0)

/** Assign scalers to short vectors */
#define ASSIGN_2V( V, V0, V1 )	\
do {				\
    V[0] = V0;			\
    V[1] = V1;			\
} while(0)

/*@}*/

/** Copy \p sz elements into a homegeneous (4-element) vector, giving
 * default values to the remaining components.
 * The default values are chosen based on \p type.
 */
static inline void
COPY_CLEAN_4V_TYPE_AS_FLOAT(GLfloat dst[4], int sz, const GLfloat src[4],
                            GLenum type)
{
   switch (type) {
   case GL_FLOAT:
      ASSIGN_4V(dst, 0, 0, 0, 1);
      break;
   case GL_INT:
      ASSIGN_4V(dst, INT_AS_FLT(0), INT_AS_FLT(0),
                     INT_AS_FLT(0), INT_AS_FLT(1));
      break;
   case GL_UNSIGNED_INT:
      ASSIGN_4V(dst, UINT_AS_FLT(0), UINT_AS_FLT(0),
                     UINT_AS_FLT(0), UINT_AS_FLT(1));
      break;
   default:
      ASSIGN_4V(dst, 0.0f, 0.0f, 0.0f, 1.0f); /* silence warnings */
      ASSERT(!"Unexpected type in COPY_CLEAN_4V_TYPE_AS_FLOAT macro");
   }
   COPY_SZ_4V(dst, sz, src);
}

/** \name Linear interpolation functions */
/*@{*/

static inline GLfloat
LINTERP(GLfloat t, GLfloat out, GLfloat in)
{
   return out + t * (in - out);
}

static inline void
INTERP_3F(GLfloat t, GLfloat dst[3], const GLfloat out[3], const GLfloat in[3])
{
   dst[0] = LINTERP( t, out[0], in[0] );
   dst[1] = LINTERP( t, out[1], in[1] );
   dst[2] = LINTERP( t, out[2], in[2] );
}

static inline void
INTERP_4F(GLfloat t, GLfloat dst[4], const GLfloat out[4], const GLfloat in[4])
{
   dst[0] = LINTERP( t, out[0], in[0] );
   dst[1] = LINTERP( t, out[1], in[1] );
   dst[2] = LINTERP( t, out[2], in[2] );
   dst[3] = LINTERP( t, out[3], in[3] );
}

/*@}*/



/** Clamp X to [MIN,MAX] */
#define CLAMP( X, MIN, MAX )  ( (X)<(MIN) ? (MIN) : ((X)>(MAX) ? (MAX) : (X)) )

/** Minimum of two values: */
#define MIN2( A, B )   ( (A)<(B) ? (A) : (B) )

/** Maximum of two values: */
#define MAX2( A, B )   ( (A)>(B) ? (A) : (B) )

/** Minimum and maximum of three values: */
#define MIN3( A, B, C ) ((A) < (B) ? MIN2(A, C) : MIN2(B, C))
#define MAX3( A, B, C ) ((A) > (B) ? MAX2(A, C) : MAX2(B, C))

static inline unsigned
minify(unsigned value, unsigned levels)
{
    return MAX2(1, value >> levels);
}

/**
 * Return true if the given value is a power of two.
 *
 * Note that this considers 0 a power of two.
 */
static inline bool
is_power_of_two(unsigned value)
{
   return (value & (value - 1)) == 0;
}

/**
 * Align a value up to an alignment value
 *
 * If \c value is not already aligned to the requested alignment value, it
 * will be rounded up.
 *
 * \param value  Value to be rounded
 * \param alignment  Alignment value to be used.  This must be a power of two.
 *
 * \sa ROUND_DOWN_TO()
 */
#define ALIGN(value, alignment)  (((value) + (alignment) - 1) & ~((alignment) - 1))

/**
 * Align a value down to an alignment value
 *
 * If \c value is not already aligned to the requested alignment value, it
 * will be rounded down.
 *
 * \param value  Value to be rounded
 * \param alignment  Alignment value to be used.  This must be a power of two.
 *
 * \sa ALIGN()
 */
#define ROUND_DOWN_TO(value, alignment) ((value) & ~(alignment - 1))


/** Cross product of two 3-element vectors */
static inline void
CROSS3(GLfloat n[3], const GLfloat u[3], const GLfloat v[3])
{
   n[0] = u[1] * v[2] - u[2] * v[1];
   n[1] = u[2] * v[0] - u[0] * v[2];
   n[2] = u[0] * v[1] - u[1] * v[0];
}


/** Dot product of two 2-element vectors */
static inline GLfloat
DOT2(const GLfloat a[2], const GLfloat b[2])
{
   return a[0] * b[0] + a[1] * b[1];
}

static inline GLfloat
DOT3(const GLfloat a[3], const GLfloat b[3])
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

static inline GLfloat
DOT4(const GLfloat a[4], const GLfloat b[4])
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}


static inline GLfloat
LEN_SQUARED_3FV(const GLfloat v[3])
{
   return DOT3(v, v);
}

static inline GLfloat
LEN_SQUARED_2FV(const GLfloat v[2])
{
   return DOT2(v, v);
}


static inline GLfloat
LEN_3FV(const GLfloat v[3])
{
   return sqrtf(LEN_SQUARED_3FV(v));
}

static inline GLfloat
LEN_2FV(const GLfloat v[2])
{
   return sqrtf(LEN_SQUARED_2FV(v));
}


/* Normalize a 3-element vector to unit length. */
static inline void
NORMALIZE_3FV(GLfloat v[3])
{
   GLfloat len = (GLfloat) LEN_SQUARED_3FV(v);
   if (len) {
      len = INV_SQRTF(len);
      v[0] *= len;
      v[1] *= len;
      v[2] *= len;
   }
}


/** Test two floats have opposite signs */
static inline GLboolean
DIFFERENT_SIGNS(GLfloat x, GLfloat y)
{
   return signbit(x) != signbit(y);
}


/** Compute ceiling of integer quotient of A divided by B. */
#define CEILING( A, B )  ( (A) % (B) == 0 ? (A)/(B) : (A)/(B)+1 )


/** casts to silence warnings with some compilers */
#define ENUM_TO_INT(E)     ((GLint)(E))
#define ENUM_TO_FLOAT(E)   ((GLfloat)(GLint)(E))
#define ENUM_TO_DOUBLE(E)  ((GLdouble)(GLint)(E))
#define ENUM_TO_BOOLEAN(E) ((E) ? GL_TRUE : GL_FALSE)

/* Compute the size of an array */
#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

/* Stringify */
#define STRINGIFY(x) #x

#endif

/*
 * Mesa 3-D graphics library
 * Version:  7.3
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
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \file prog_parameter.c
 * Program parameter lists and functions.
 * \author Brian Paul
 */

#ifndef PROG_PARAMETER_H
#define PROG_PARAMETER_H

#include "main/mtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Program parameter flags
 */
/*@{*/
#define PROG_PARAM_BIT_CENTROID   0x1  /**< for varying vars (GLSL 1.20) */
#define PROG_PARAM_BIT_INVARIANT  0x2  /**< for varying vars (GLSL 1.20) */
#define PROG_PARAM_BIT_FLAT       0x4  /**< for varying vars (GLSL 1.30) */
#define PROG_PARAM_BIT_LINEAR     0x8  /**< for varying vars (GLSL 1.30) */
#define PROG_PARAM_BIT_CYL_WRAP  0x10  /**< XXX gallium debug */
/*@}*/


/**
 * Actual data for constant values of parameters.
 */
typedef union gl_constant_value
{
   GLfloat f;
   GLint b;
   GLint i;
   GLuint u;
} gl_constant_value;




#ifdef __cplusplus
}
#endif

#endif /* PROG_PARAMETER_H */

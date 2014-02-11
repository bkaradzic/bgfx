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


#ifndef CONTEXT_H
#define CONTEXT_H


#include "imports.h"
#include "mtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Checks if the context is for Desktop GL (Compatibility or Core)
 */
static inline GLboolean
_mesa_is_desktop_gl(const struct gl_context *ctx)
{
   return ctx->API == API_OPENGL_COMPAT || ctx->API == API_OPENGL_CORE;
}


/**
 * Checks if the context is for any GLES version
 */
static inline GLboolean
_mesa_is_gles(const struct gl_context *ctx)
{
   return ctx->API == API_OPENGLES || ctx->API == API_OPENGLES2;
}


/**
 * Checks if the context is for GLES 3.x
 */
static inline GLboolean
_mesa_is_gles3(const struct gl_context *ctx)
{
   return ctx->API == API_OPENGLES2 && ctx->Version >= 30;
}


/**
 * Checks if the context supports geometry shaders.
 */
static inline GLboolean
_mesa_has_geometry_shaders(const struct gl_context *ctx)
{
   return _mesa_is_desktop_gl(ctx) &&
      (ctx->Version >= 32 || ctx->Extensions.ARB_geometry_shader4);
}


#ifdef __cplusplus
}
#endif


#endif /* CONTEXT_H */

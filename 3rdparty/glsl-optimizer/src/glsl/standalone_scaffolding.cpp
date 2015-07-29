/*
 * Copyright © 2011 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* This file declares stripped-down versions of functions that
 * normally exist outside of the glsl folder, so that they can be used
 * when running the GLSL compiler standalone (for unit testing or
 * compiling builtins).
 */

#include "standalone_scaffolding.h"

#include <assert.h>
#include <string.h>
#include <limits.h>
#include "util/ralloc.h"


void
_mesa_reference_shader(struct gl_context *, struct gl_shader **ptr,
                       struct gl_shader *sh)
{
   *ptr = sh;
}

void
_mesa_shader_debug(struct gl_context *, GLenum, GLuint *,
                   const char *, int)
{
}

extern "C" void
_mesa_error_no_memory(const char *)
{
}


struct gl_shader *
_mesa_new_shader(struct gl_context *ctx, GLuint name, GLenum type)
{
   struct gl_shader *shader;

   (void) ctx;

   assert(type == GL_FRAGMENT_SHADER || type == GL_VERTEX_SHADER);
   shader = rzalloc(NULL, struct gl_shader);
   if (shader) {
      shader->Type = type;
      shader->Stage = _mesa_shader_enum_to_shader_stage(type);
      shader->Name = name;
      shader->RefCount = 1;
   }
   return shader;
}

void initialize_context_to_defaults(struct gl_context *ctx, gl_api api)
{
   memset(ctx, 0, sizeof(*ctx));

   ctx->API = api;

   ctx->Extensions.dummy_false = false;
   ctx->Extensions.dummy_true = true;
   ctx->Extensions.ARB_compute_shader = true;
   ctx->Extensions.ARB_conservative_depth = true;
   ctx->Extensions.ARB_draw_instanced = true;
   ctx->Extensions.ARB_ES2_compatibility = true;
   ctx->Extensions.ARB_ES3_compatibility = true;
   ctx->Extensions.ARB_explicit_attrib_location = true;
   ctx->Extensions.ARB_fragment_coord_conventions = true;
   ctx->Extensions.ARB_fragment_layer_viewport = true;
   ctx->Extensions.ARB_gpu_shader5 = true;
   ctx->Extensions.ARB_sample_shading = true;
   ctx->Extensions.ARB_shader_bit_encoding = true;
   ctx->Extensions.ARB_shader_stencil_export = true;
   ctx->Extensions.ARB_shader_texture_lod = true;
   ctx->Extensions.ARB_shading_language_420pack = true;
   ctx->Extensions.ARB_shading_language_packing = true;
   ctx->Extensions.ARB_texture_cube_map_array = true;
   ctx->Extensions.ARB_texture_gather = true;
   ctx->Extensions.ARB_texture_multisample = true;
   ctx->Extensions.ARB_texture_query_levels = true;
   ctx->Extensions.ARB_texture_query_lod = true;
   ctx->Extensions.ARB_uniform_buffer_object = true;
   ctx->Extensions.ARB_viewport_array = true;

   ctx->Extensions.OES_EGL_image_external = true;
   ctx->Extensions.OES_standard_derivatives = true;

   ctx->Extensions.EXT_draw_instanced = true;
   ctx->Extensions.EXT_gpu_shader4 = true;
   ctx->Extensions.EXT_shader_integer_mix = true;
   ctx->Extensions.EXT_texture3D = true;
   ctx->Extensions.EXT_texture_array = true;
   ctx->Extensions.EXT_draw_buffers = true;

   ctx->Extensions.NV_texture_rectangle = true;

   ctx->Const.AllowGLSLExtensionDirectiveMidShader = true; // makes it easier to run tests

   ctx->Const.GLSLVersion = 120;

   /* 1.20 minimums. */
   ctx->Const.MaxLights = 8;
   ctx->Const.MaxClipPlanes = 6;
   ctx->Const.MaxTextureUnits = 2;
   ctx->Const.MaxTextureCoordUnits = 2;
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;

   ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 512;
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 32;
   ctx->Const.MaxVarying = 8; /* == gl_MaxVaryingFloats / 4 */
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 0;
   ctx->Const.MaxCombinedTextureImageUnits = 2;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits = 2;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 64;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents = 32;

   ctx->Const.MaxDrawBuffers = 1;
   ctx->Const.MaxComputeWorkGroupCount[0] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[1] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[2] = 65535;
   ctx->Const.MaxComputeWorkGroupSize[0] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[1] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[2] = 64;
   ctx->Const.MaxComputeWorkGroupInvocations = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxTextureImageUnits = 16;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxUniformComponents = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxInputComponents = 0; /* not used */
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxOutputComponents = 0; /* not used */

   /* Set up default shader compiler options. */
   struct gl_shader_compiler_options options;
   memset(&options, 0, sizeof(options));
   options.MaxUnrollIterations = 8;
   options.MaxIfDepth = UINT_MAX;

   /* Default pragma settings */
   options.DefaultPragmas.Optimize = true;

   for (int sh = 0; sh < MESA_SHADER_STAGES; ++sh)
      memcpy(&ctx->Const.ShaderCompilerOptions[sh], &options, sizeof(options));
}

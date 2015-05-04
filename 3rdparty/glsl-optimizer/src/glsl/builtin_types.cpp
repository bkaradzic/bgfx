/*
 * Copyright © 2013 Intel Corporation
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

/**
 * \file builtin_types.cpp
 *
 * The glsl_type class has static members to represent all the built-in types
 * (such as the glsl_type::_float_type flyweight) as well as convenience pointer
 * accessors (such as glsl_type::float_type).  Those global variables are
 * declared and initialized in this file.
 *
 * This also contains _mesa_glsl_initialize_types(), a function which populates
 * a symbol table with the available built-in types for a particular language
 * version and set of enabled extensions.
 */

#include "glsl_types.h"
#include "glsl_parser_extras.h"
#include "util/macros.h"

/**
 * Declarations of type flyweights (glsl_type::_foo_type) and
 * convenience pointers (glsl_type::foo_type).
 * @{
 */
#define DECL_TYPE(NAME, ...)                                    \
   const glsl_type glsl_type::_##NAME##_type = glsl_type(__VA_ARGS__, #NAME); \
   const glsl_type *const glsl_type::NAME##_type = &glsl_type::_##NAME##_type;

#define STRUCT_TYPE(NAME)                                       \
   const glsl_type glsl_type::_struct_##NAME##_type =           \
      glsl_type(NAME##_fields, ARRAY_SIZE(NAME##_fields), #NAME); \
   const glsl_type *const glsl_type::struct_##NAME##_type =     \
      &glsl_type::_struct_##NAME##_type;

static const struct glsl_struct_field gl_DepthRangeParameters_fields[] = {
   { glsl_type::float_type, "near", glsl_precision_high, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "far",  glsl_precision_high, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "diff", glsl_precision_high, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_PointParameters_fields[] = {
   { glsl_type::float_type, "size", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "sizeMin", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "sizeMax", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "fadeThresholdSize", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "distanceConstantAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "distanceLinearAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "distanceQuadraticAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_MaterialParameters_fields[] = {
   { glsl_type::vec4_type, "emission", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "ambient", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "diffuse", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "specular", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "shininess", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_LightSourceParameters_fields[] = {
   { glsl_type::vec4_type, "ambient", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "diffuse", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "specular", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "position", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "halfVector", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec3_type, "spotDirection", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "spotExponent", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "spotCutoff", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "spotCosCutoff", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "constantAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "linearAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "quadraticAttenuation", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_LightModelParameters_fields[] = {
   { glsl_type::vec4_type, "ambient", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_LightModelProducts_fields[] = {
   { glsl_type::vec4_type, "sceneColor", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_LightProducts_fields[] = {
   { glsl_type::vec4_type, "ambient", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "diffuse", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::vec4_type, "specular", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

static const struct glsl_struct_field gl_FogParameters_fields[] = {
   { glsl_type::vec4_type, "color", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "density", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "start", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "end", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
   { glsl_type::float_type, "scale", glsl_precision_undefined, -1, 0, 0, 0, GLSL_MATRIX_LAYOUT_INHERITED, 0 },
};

#include "builtin_type_macros.h"
/** @} */

/**
 * Code to populate a symbol table with the built-in types available in a
 * particular shading language version.  The table below contains tags every
 * type with the GLSL/GLSL ES versions where it was introduced.
 *
 * @{
 */
#define T(TYPE, MIN_GL, MIN_ES) \
   { glsl_type::TYPE##_type, MIN_GL, MIN_ES },

const static struct builtin_type_versions {
   const glsl_type *const type;
   int min_gl;
   int min_es;
} builtin_type_versions[] = {
   T(void,                            110, 100)
   T(bool,                            110, 100)
   T(bvec2,                           110, 100)
   T(bvec3,                           110, 100)
   T(bvec4,                           110, 100)
   T(int,                             110, 100)
   T(ivec2,                           110, 100)
   T(ivec3,                           110, 100)
   T(ivec4,                           110, 100)
   T(uint,                            130, 300)
   T(uvec2,                           130, 300)
   T(uvec3,                           130, 300)
   T(uvec4,                           130, 300)
   T(float,                           110, 100)
   T(vec2,                            110, 100)
   T(vec3,                            110, 100)
   T(vec4,                            110, 100)
   T(mat2,                            110, 100)
   T(mat3,                            110, 100)
   T(mat4,                            110, 100)
   T(mat2x3,                          120, 300)
   T(mat2x4,                          120, 300)
   T(mat3x2,                          120, 300)
   T(mat3x4,                          120, 300)
   T(mat4x2,                          120, 300)
   T(mat4x3,                          120, 300)

   T(sampler1D,                       110, 999)
   T(sampler2D,                       110, 100)
   T(sampler3D,                       110, 300)
   T(samplerCube,                     110, 100)
   T(sampler1DArray,                  130, 999)
   T(sampler2DArray,                  130, 300)
   T(samplerCubeArray,                400, 999)
   T(sampler2DRect,                   140, 999)
   T(samplerBuffer,                   140, 999)
   T(sampler2DMS,                     150, 999)
   T(sampler2DMSArray,                150, 999)

   T(isampler1D,                      130, 999)
   T(isampler2D,                      130, 300)
   T(isampler3D,                      130, 300)
   T(isamplerCube,                    130, 300)
   T(isampler1DArray,                 130, 999)
   T(isampler2DArray,                 130, 300)
   T(isamplerCubeArray,               400, 999)
   T(isampler2DRect,                  140, 999)
   T(isamplerBuffer,                  140, 999)
   T(isampler2DMS,                    150, 999)
   T(isampler2DMSArray,               150, 999)

   T(usampler1D,                      130, 999)
   T(usampler2D,                      130, 300)
   T(usampler3D,                      130, 300)
   T(usamplerCube,                    130, 300)
   T(usampler1DArray,                 130, 999)
   T(usampler2DArray,                 130, 300)
   T(usamplerCubeArray,               400, 999)
   T(usampler2DRect,                  140, 999)
   T(usamplerBuffer,                  140, 999)
   T(usampler2DMS,                    150, 999)
   T(usampler2DMSArray,               150, 999)

   T(sampler1DShadow,                 110, 999)
   T(sampler2DShadow,                 110, 300)
   T(samplerCubeShadow,               130, 300)
   T(sampler1DArrayShadow,            130, 999)
   T(sampler2DArrayShadow,            130, 300)
   T(samplerCubeArrayShadow,          400, 999)
   T(sampler2DRectShadow,             140, 999)

   T(struct_gl_DepthRangeParameters,  110, 100)

   T(image1D,                         420, 999)
   T(image2D,                         420, 999)
   T(image3D,                         420, 999)
   T(image2DRect,                     420, 999)
   T(imageCube,                       420, 999)
   T(imageBuffer,                     420, 999)
   T(image1DArray,                    420, 999)
   T(image2DArray,                    420, 999)
   T(imageCubeArray,                  420, 999)
   T(image2DMS,                       420, 999)
   T(image2DMSArray,                  420, 999)
   T(iimage1D,                        420, 999)
   T(iimage2D,                        420, 999)
   T(iimage3D,                        420, 999)
   T(iimage2DRect,                    420, 999)
   T(iimageCube,                      420, 999)
   T(iimageBuffer,                    420, 999)
   T(iimage1DArray,                   420, 999)
   T(iimage2DArray,                   420, 999)
   T(iimageCubeArray,                 420, 999)
   T(iimage2DMS,                      420, 999)
   T(iimage2DMSArray,                 420, 999)
   T(uimage1D,                        420, 999)
   T(uimage2D,                        420, 999)
   T(uimage3D,                        420, 999)
   T(uimage2DRect,                    420, 999)
   T(uimageCube,                      420, 999)
   T(uimageBuffer,                    420, 999)
   T(uimage1DArray,                   420, 999)
   T(uimage2DArray,                   420, 999)
   T(uimageCubeArray,                 420, 999)
   T(uimage2DMS,                      420, 999)
   T(uimage2DMSArray,                 420, 999)

   T(atomic_uint,                     420, 999)
};

static const glsl_type *const deprecated_types[] = {
   glsl_type::struct_gl_PointParameters_type,
   glsl_type::struct_gl_MaterialParameters_type,
   glsl_type::struct_gl_LightSourceParameters_type,
   glsl_type::struct_gl_LightModelParameters_type,
   glsl_type::struct_gl_LightModelProducts_type,
   glsl_type::struct_gl_LightProducts_type,
   glsl_type::struct_gl_FogParameters_type,
};

static inline void
add_type(glsl_symbol_table *symbols, const glsl_type *const type)
{
   symbols->add_type(type->name, type);
}

/**
 * Populate the symbol table with available built-in types.
 */
void
_mesa_glsl_initialize_types(struct _mesa_glsl_parse_state *state)
{
   struct glsl_symbol_table *symbols = state->symbols;

   for (unsigned i = 0; i < ARRAY_SIZE(builtin_type_versions); i++) {
      const struct builtin_type_versions *const t = &builtin_type_versions[i];
      if (state->is_version(t->min_gl, t->min_es)) {
         add_type(symbols, t->type);
      }
   }

   /* Add deprecated structure types.  While these were deprecated in 1.30,
    * they're still present.  We've removed them in 1.40+ (OpenGL 3.1+).
    */
   if (!state->es_shader && state->language_version < 140) {
      for (unsigned i = 0; i < ARRAY_SIZE(deprecated_types); i++) {
         add_type(symbols, deprecated_types[i]);
      }
   }

   /* Add types for enabled extensions.  They may have already been added
    * by the version-based loop, but attempting to add them a second time
    * is harmless.
    */
   if (state->ARB_texture_cube_map_array_enable) {
      add_type(symbols, glsl_type::samplerCubeArray_type);
      add_type(symbols, glsl_type::samplerCubeArrayShadow_type);
      add_type(symbols, glsl_type::isamplerCubeArray_type);
      add_type(symbols, glsl_type::usamplerCubeArray_type);
   }

   if (state->ARB_texture_multisample_enable) {
      add_type(symbols, glsl_type::sampler2DMS_type);
      add_type(symbols, glsl_type::isampler2DMS_type);
      add_type(symbols, glsl_type::usampler2DMS_type);
      add_type(symbols, glsl_type::sampler2DMSArray_type);
      add_type(symbols, glsl_type::isampler2DMSArray_type);
      add_type(symbols, glsl_type::usampler2DMSArray_type);
   }

   if (state->ARB_texture_rectangle_enable) {
      add_type(symbols, glsl_type::sampler2DRect_type);
      add_type(symbols, glsl_type::sampler2DRectShadow_type);
   }

   if (state->EXT_texture_array_enable) {
      add_type(symbols, glsl_type::sampler1DArray_type);
      add_type(symbols, glsl_type::sampler2DArray_type);
      add_type(symbols, glsl_type::sampler1DArrayShadow_type);
      add_type(symbols, glsl_type::sampler2DArrayShadow_type);
   }

   if (state->OES_EGL_image_external_enable) {
      add_type(symbols, glsl_type::samplerExternalOES_type);
   }

   if (state->EXT_shadow_samplers_enable) {
      add_type(symbols, glsl_type::sampler2DShadow_type);
   }

   if (state->OES_texture_3D_enable) {
      add_type(symbols, glsl_type::sampler3D_type);
   }

   if (state->ARB_shader_image_load_store_enable) {
      add_type(symbols, glsl_type::image1D_type);
      add_type(symbols, glsl_type::image2D_type);
      add_type(symbols, glsl_type::image3D_type);
      add_type(symbols, glsl_type::image2DRect_type);
      add_type(symbols, glsl_type::imageCube_type);
      add_type(symbols, glsl_type::imageBuffer_type);
      add_type(symbols, glsl_type::image1DArray_type);
      add_type(symbols, glsl_type::image2DArray_type);
      add_type(symbols, glsl_type::imageCubeArray_type);
      add_type(symbols, glsl_type::image2DMS_type);
      add_type(symbols, glsl_type::image2DMSArray_type);
      add_type(symbols, glsl_type::iimage1D_type);
      add_type(symbols, glsl_type::iimage2D_type);
      add_type(symbols, glsl_type::iimage3D_type);
      add_type(symbols, glsl_type::iimage2DRect_type);
      add_type(symbols, glsl_type::iimageCube_type);
      add_type(symbols, glsl_type::iimageBuffer_type);
      add_type(symbols, glsl_type::iimage1DArray_type);
      add_type(symbols, glsl_type::iimage2DArray_type);
      add_type(symbols, glsl_type::iimageCubeArray_type);
      add_type(symbols, glsl_type::iimage2DMS_type);
      add_type(symbols, glsl_type::iimage2DMSArray_type);
      add_type(symbols, glsl_type::uimage1D_type);
      add_type(symbols, glsl_type::uimage2D_type);
      add_type(symbols, glsl_type::uimage3D_type);
      add_type(symbols, glsl_type::uimage2DRect_type);
      add_type(symbols, glsl_type::uimageCube_type);
      add_type(symbols, glsl_type::uimageBuffer_type);
      add_type(symbols, glsl_type::uimage1DArray_type);
      add_type(symbols, glsl_type::uimage2DArray_type);
      add_type(symbols, glsl_type::uimageCubeArray_type);
      add_type(symbols, glsl_type::uimage2DMS_type);
      add_type(symbols, glsl_type::uimage2DMSArray_type);
   }

   if (state->ARB_shader_atomic_counters_enable) {
      add_type(symbols, glsl_type::atomic_uint_type);
   }
}
/** @} */

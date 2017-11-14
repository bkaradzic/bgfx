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
 * \file builtin_functions.cpp
 *
 * Support for GLSL built-in functions.
 *
 * This file is split into several main components:
 *
 * 1. Availability predicates
 *
 *    A series of small functions that check whether the current shader
 *    supports the version/extensions required to expose a built-in.
 *
 * 2. Core builtin_builder class functionality
 *
 * 3. Lists of built-in functions
 *
 *    The builtin_builder::create_builtins() function contains lists of all
 *    built-in function signatures, where they're available, what types they
 *    take, and so on.
 *
 * 4. Implementations of built-in function signatures
 *
 *    A series of functions which create ir_function_signatures and emit IR
 *    via ir_builder to implement them.
 *
 * 5. External API
 *
 *    A few functions the rest of the compiler can use to interact with the
 *    built-in function module.  For example, searching for a built-in by
 *    name and parameters.
 */

#include <stdarg.h>
#include <stdio.h>
#include "main/core.h" /* for struct gl_shader */
#include "standalone_scaffolding.h"
#include "ir_builder.h"
#include "glsl_parser_extras.h"
#include "program/prog_instruction.h"
#include <limits>

#define M_PIf   ((float) M_PI)
#define M_PI_2f ((float) M_PI_2)
#define M_PI_4f ((float) M_PI_4)

using namespace ir_builder;

/**
 * Availability predicates:
 *  @{
 */
static bool
always_available(const _mesa_glsl_parse_state *)
{
   return true;
}

static bool
compatibility_vs_only(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_VERTEX &&
          state->language_version <= 130 &&
          !state->es_shader;
}

static bool
fs_only(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT;
}

static bool
gs_only(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_GEOMETRY;
}

static bool
v110(const _mesa_glsl_parse_state *state)
{
   return !state->es_shader;
}

static bool
v110_fs_only(const _mesa_glsl_parse_state *state)
{
   return !state->es_shader && state->stage == MESA_SHADER_FRAGMENT;
}

static bool
v120(const _mesa_glsl_parse_state *state)
{
   return state->is_version(120, 300);
}

static bool
v130(const _mesa_glsl_parse_state *state)
{
   return state->is_version(130, 300);
}

static bool
v130_fs_only(const _mesa_glsl_parse_state *state)
{
   return state->is_version(130, 300) &&
          state->stage == MESA_SHADER_FRAGMENT;
}

static bool
v140(const _mesa_glsl_parse_state *state)
{
   return state->is_version(140, 0);
}

static bool
texture_rectangle(const _mesa_glsl_parse_state *state)
{
   return state->ARB_texture_rectangle_enable;
}

static bool
texture_external(const _mesa_glsl_parse_state *state)
{
   return state->OES_EGL_image_external_enable;
}

/** True if texturing functions with explicit LOD are allowed. */
static bool
lod_exists_in_stage(const _mesa_glsl_parse_state *state)
{
   /* Texturing functions with "Lod" in their name exist:
    * - In the vertex shader stage (for all languages)
    * - In any stage for GLSL 1.30+ or GLSL ES 3.00
    * - In any stage for desktop GLSL with ARB_shader_texture_lod enabled.
    *
    * Since ARB_shader_texture_lod can only be enabled on desktop GLSL, we
    * don't need to explicitly check state->es_shader.
    */
   return state->stage == MESA_SHADER_VERTEX ||
          state->is_version(130, 300) ||
          state->EXT_texture_array_enable ||      /* BK - don't complain about texture array in fragment shaders. */
          state->OES_texture_3D_enable ||         /* BK - shut up */
          state->EXT_shader_texture_lod_enable || /* BK - pretend it's ok too */
          state->ARB_shader_texture_lod_enable;
}

static bool
es_lod_exists_in_stage(const _mesa_glsl_parse_state *state)
{
	/* Texturing functions with "LodEXT" in their name exist:
	 * In the fragment shader, for ES1 shader, when EXT_shader_texture_lod
	 * is enabled.
	 */
	return
// BK - EXT_shader_texture_lod is available in vertex and fragment shaders.
//		state->stage == MESA_SHADER_FRAGMENT &&
		state->es_shader &&
		state->is_version(110, 100) &&
		state->EXT_shader_texture_lod_enable;
}

static bool
v110_lod(const _mesa_glsl_parse_state *state)
{
   return !state->es_shader && lod_exists_in_stage(state);
}

static bool
shader_texture_lod(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shader_texture_lod_enable;
}

static bool
es_shader_texture_lod(const _mesa_glsl_parse_state *state)
{
	return state->EXT_shader_texture_lod_enable;
}

static bool
es_shadow_samplers(const _mesa_glsl_parse_state *state)
{
	return state->EXT_shadow_samplers_enable;
}

static bool
shader_texture_lod_and_rect(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shader_texture_lod_enable &&
          state->ARB_texture_rectangle_enable;
}

static bool
shader_bit_encoding(const _mesa_glsl_parse_state *state)
{
   return state->is_version(330, 300) ||
          state->ARB_shader_bit_encoding_enable ||
          state->ARB_gpu_shader5_enable;
}

static bool
shader_integer_mix(const _mesa_glsl_parse_state *state)
{
   return v130(state) && state->EXT_shader_integer_mix_enable;
}

static bool
shader_packing_or_es3(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shading_language_packing_enable ||
          state->is_version(400, 300);
}

static bool
shader_packing_or_es3_or_gpu_shader5(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shading_language_packing_enable ||
          state->ARB_gpu_shader5_enable ||
          state->is_version(400, 300);
}

static bool
gpu_shader5(const _mesa_glsl_parse_state *state)
{
   return state->is_version(400, 0) || state->ARB_gpu_shader5_enable;
}

static bool
shader_packing_or_gpu_shader5(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shading_language_packing_enable ||
          gpu_shader5(state);
}

static bool
fs_gpu_shader5(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          (state->is_version(400, 0) || state->ARB_gpu_shader5_enable);
}


static bool
texture_array_lod(const _mesa_glsl_parse_state *state)
{
   return lod_exists_in_stage(state) &&
          state->EXT_texture_array_enable;
}

static bool
fs_texture_array(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          state->EXT_texture_array_enable;
}

static bool
texture_array(const _mesa_glsl_parse_state *state)
{
   return state->EXT_texture_array_enable;
}

static bool
texture_multisample(const _mesa_glsl_parse_state *state)
{
   return state->is_version(150, 0) ||
          state->ARB_texture_multisample_enable;
}

static bool
fs_texture_cube_map_array(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          (state->is_version(400, 0) ||
           state->ARB_texture_cube_map_array_enable);
}

static bool
texture_cube_map_array(const _mesa_glsl_parse_state *state)
{
   return state->is_version(400, 0) ||
          state->ARB_texture_cube_map_array_enable;
}

static bool
texture_query_levels(const _mesa_glsl_parse_state *state)
{
   return state->is_version(430, 0) ||
          state->ARB_texture_query_levels_enable;
}

static bool
texture_query_lod(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          state->ARB_texture_query_lod_enable;
}

static bool
texture_gather(const _mesa_glsl_parse_state *state)
{
   return state->is_version(400, 0) ||
          state->ARB_texture_gather_enable ||
          state->ARB_gpu_shader5_enable;
}

/* Only ARB_texture_gather but not GLSL 4.0 or ARB_gpu_shader5.
 * used for relaxation of const offset requirements.
 */
static bool
texture_gather_only(const _mesa_glsl_parse_state *state)
{
   return !state->is_version(400, 0) &&
          !state->ARB_gpu_shader5_enable &&
          state->ARB_texture_gather_enable;
}

/* Desktop GL or OES_standard_derivatives + fragment shader only */
static bool
fs_oes_derivatives(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          (state->is_version(110, 300) ||
           state->OES_standard_derivatives_enable);
}

static bool
fs_derivative_control(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          (state->is_version(450, 0) ||
           state->ARB_derivative_control_enable);
}

static bool
tex1d_lod(const _mesa_glsl_parse_state *state)
{
   return !state->es_shader && lod_exists_in_stage(state);
}

/** True if sampler3D exists */
static bool
tex3d(const _mesa_glsl_parse_state *state)
{
   /* sampler3D exists in all desktop GLSL versions, GLSL ES 1.00 with the
    * OES_texture_3D extension, and in GLSL ES 3.00.
    */
   return !state->es_shader ||
          state->OES_texture_3D_enable ||
          state->language_version >= 300;
}

static bool
fs_tex3d(const _mesa_glsl_parse_state *state)
{
   return state->stage == MESA_SHADER_FRAGMENT &&
          (!state->es_shader || state->OES_texture_3D_enable);
}

static bool
tex3d_lod(const _mesa_glsl_parse_state *state)
{
   return tex3d(state) && lod_exists_in_stage(state);
}

static bool
shader_atomic_counters(const _mesa_glsl_parse_state *state)
{
   return state->ARB_shader_atomic_counters_enable;
}

static bool
shader_trinary_minmax(const _mesa_glsl_parse_state *state)
{
   return state->AMD_shader_trinary_minmax_enable;
}

static bool
shader_image_load_store(const _mesa_glsl_parse_state *state)
{
   return (state->is_version(420, 0) ||
           state->ARB_shader_image_load_store_enable);
}

static bool
gs_streams(const _mesa_glsl_parse_state *state)
{
   return gpu_shader5(state) && gs_only(state);
}

/** @} */

/******************************************************************************/

namespace {

/**
 * builtin_builder: A singleton object representing the core of the built-in
 * function module.
 *
 * It generates IR for every built-in function signature, and organizes them
 * into functions.
 */
class builtin_builder {
public:
   builtin_builder();
   ~builtin_builder();

   void initialize();
   void release();
   ir_function_signature *find(_mesa_glsl_parse_state *state,
                               const char *name, exec_list *actual_parameters);

   /**
    * A shader to hold all the built-in signatures; created by this module.
    *
    * This includes signatures for every built-in, regardless of version or
    * enabled extensions.  The availability predicate associated with each
    * signature allows matching_signature() to filter out the irrelevant ones.
    */
   gl_shader *shader;

private:
   void *mem_ctx;

   /** Global variables used by built-in functions. */
   ir_variable *gl_ModelViewProjectionMatrix;
   ir_variable *gl_Vertex;

   void create_shader();
   void create_intrinsics();
   void create_builtins();

   /**
    * IR builder helpers:
    *
    * These convenience functions assist in emitting IR, but don't necessarily
    * fit in ir_builder itself.  Many of them rely on having a mem_ctx class
    * member available.
    */
   ir_variable *in_var(const glsl_type *type, const char *name);
   ir_variable *out_var(const glsl_type *type, const char *name);
   ir_constant *imm(float f, unsigned vector_elements=1);
   ir_constant *imm(int i, unsigned vector_elements=1);
   ir_constant *imm(unsigned u, unsigned vector_elements=1);
   ir_constant *imm(const glsl_type *type, const ir_constant_data &);
   ir_dereference_variable *var_ref(ir_variable *var);
   ir_dereference_array *array_ref(ir_variable *var, int i);
   ir_swizzle *matrix_elt(ir_variable *var, int col, int row);

   ir_expression *asin_expr(ir_variable *x);
   void do_atan(ir_factory &body, const glsl_type *type, ir_variable *res, operand y_over_x);

   /**
    * Call function \param f with parameters specified as the linked
    * list \param params of \c ir_variable objects.  \param ret should
    * point to the ir_variable that will hold the function return
    * value, or be \c NULL if the function has void return type.
    */
   ir_call *call(ir_function *f, ir_variable *ret, exec_list params);

   /** Create a new function and add the given signatures. */
   void add_function(const char *name, ...);

   enum image_function_flags {
      IMAGE_FUNCTION_EMIT_STUB = (1 << 0),
      IMAGE_FUNCTION_RETURNS_VOID = (1 << 1),
      IMAGE_FUNCTION_HAS_VECTOR_DATA_TYPE = (1 << 2),
      IMAGE_FUNCTION_SUPPORTS_FLOAT_DATA_TYPE = (1 << 3),
      IMAGE_FUNCTION_READ_ONLY = (1 << 4),
      IMAGE_FUNCTION_WRITE_ONLY = (1 << 5)
   };

   /**
    * Create a new image built-in function for all known image types.
    * \p flags is a bitfield of \c image_function_flags flags.
    */
   void add_image_function(const char *name,
                           const char *intrinsic_name,
                           unsigned num_arguments,
                           unsigned flags);

   /**
    * Create new functions for all known image built-ins and types.
    * If \p glsl is \c true, use the GLSL built-in names and emit code
    * to call into the actual compiler intrinsic.  If \p glsl is
    * false, emit a function prototype with no body for each image
    * intrinsic name.
    */
   void add_image_functions(bool glsl);

   ir_function_signature *new_sig(const glsl_type *return_type,
                                  builtin_available_predicate avail,
                                  int num_params, ...);

   /**
    * Function signature generators:
    *  @{
    */
   ir_function_signature *unop(builtin_available_predicate avail,
                               ir_expression_operation opcode,
                               const glsl_type *return_type,
                               const glsl_type *param_type);
   ir_function_signature *binop(ir_expression_operation opcode,
                                builtin_available_predicate avail,
                                const glsl_type *return_type,
                                const glsl_type *param0_type,
                                const glsl_type *param1_type);

#define B0(X) ir_function_signature *_##X();
#define B1(X) ir_function_signature *_##X(const glsl_type *);
#define B2(X) ir_function_signature *_##X(const glsl_type *, const glsl_type *);
#define B3(X) ir_function_signature *_##X(const glsl_type *, const glsl_type *, const glsl_type *);
#define BA1(X) ir_function_signature *_##X(builtin_available_predicate, const glsl_type *);
#define BA2(X) ir_function_signature *_##X(builtin_available_predicate, const glsl_type *, const glsl_type *);
   B1(radians)
   B1(degrees)
   B1(sin)
   B1(cos)
   B1(tan)
   B1(asin)
   B1(acos)
   B1(atan2)
   B1(atan)
   B1(sinh)
   B1(cosh)
   B1(tanh)
   B1(asinh)
   B1(acosh)
   B1(atanh)
   B1(pow)
   B1(exp)
   B1(log)
   B1(exp2)
   B1(log2)
   B1(sqrt)
   B1(inversesqrt)
   B1(abs)
   B1(sign)
   B1(floor)
   B1(trunc)
   B1(round)
   B1(roundEven)
   B1(ceil)
   B1(fract)
   B2(mod)
   B1(modf)
   BA2(min)
   BA2(max)
   BA2(clamp)
   B2(mix_lrp)
   ir_function_signature *_mix_sel(builtin_available_predicate avail,
                                   const glsl_type *val_type,
                                   const glsl_type *blend_type);
   B2(step)
   B2(smoothstep)
   B1(isnan)
   B1(isinf)
   B1(floatBitsToInt)
   B1(floatBitsToUint)
   B1(intBitsToFloat)
   B1(uintBitsToFloat)
   ir_function_signature *_packUnorm2x16(builtin_available_predicate avail);
   ir_function_signature *_packSnorm2x16(builtin_available_predicate avail);
   ir_function_signature *_packUnorm4x8(builtin_available_predicate avail);
   ir_function_signature *_packSnorm4x8(builtin_available_predicate avail);
   ir_function_signature *_unpackUnorm2x16(builtin_available_predicate avail);
   ir_function_signature *_unpackSnorm2x16(builtin_available_predicate avail);
   ir_function_signature *_unpackUnorm4x8(builtin_available_predicate avail);
   ir_function_signature *_unpackSnorm4x8(builtin_available_predicate avail);
   ir_function_signature *_packHalf2x16(builtin_available_predicate avail);
   ir_function_signature *_unpackHalf2x16(builtin_available_predicate avail);
   B1(length)
   B1(distance);
   B1(dot);
   B1(cross);
   B1(normalize);
   B0(ftransform);
   B1(faceforward);
   B1(reflect);
   B1(refract);
   B1(matrixCompMult);
   B1(outerProduct);
   B0(determinant_mat2);
   B0(determinant_mat3);
   B0(determinant_mat4);
   B0(inverse_mat2);
   B0(inverse_mat3);
   B0(inverse_mat4);
   B1(transpose);
   BA1(lessThan);
   BA1(lessThanEqual);
   BA1(greaterThan);
   BA1(greaterThanEqual);
   BA1(equal);
   BA1(notEqual);
   B1(any);
   B1(all);
   B1(not);
   B2(textureSize);
   ir_function_signature *_textureSize(builtin_available_predicate avail,
                                       const glsl_type *return_type,
                                       const glsl_type *sampler_type);

/** Flags to _texture() */
#define TEX_PROJECT 1
#define TEX_OFFSET  2
#define TEX_COMPONENT 4
#define TEX_OFFSET_NONCONST 8
#define TEX_OFFSET_ARRAY 16

   ir_function_signature *_texture(ir_texture_opcode opcode,
                                   builtin_available_predicate avail,
                                   const glsl_type *return_type,
                                   const glsl_type *sampler_type,
                                   const glsl_type *coord_type,
                                   int flags = 0);
   B0(textureCubeArrayShadow);
   ir_function_signature *_texelFetch(builtin_available_predicate avail,
                                      const glsl_type *return_type,
                                      const glsl_type *sampler_type,
                                      const glsl_type *coord_type,
                                      const glsl_type *offset_type = NULL);

   B0(EmitVertex)
   B0(EndPrimitive)
   ir_function_signature *_EmitStreamVertex(builtin_available_predicate avail,
                                            const glsl_type *stream_type);
   ir_function_signature *_EndStreamPrimitive(builtin_available_predicate avail,
                                              const glsl_type *stream_type);

   B2(textureQueryLod);
   B1(textureQueryLevels);
   B1(dFdx);
   B1(dFdy);
   B1(fwidth);
   B1(dFdxCoarse);
   B1(dFdyCoarse);
   B1(fwidthCoarse);
   B1(dFdxFine);
   B1(dFdyFine);
   B1(fwidthFine);
   B1(noise1);
   B1(noise2);
   B1(noise3);
   B1(noise4);

   B1(bitfieldExtract)
   B1(bitfieldInsert)
   B1(bitfieldReverse)
   B1(bitCount)
   B1(findLSB)
   B1(findMSB)
   B1(fma)
   B2(ldexp)
   B2(frexp)
   B1(uaddCarry)
   B1(usubBorrow)
   B1(mulExtended)
   B1(interpolateAtCentroid)
   B1(interpolateAtOffset)
   B1(interpolateAtSample)

   ir_function_signature *_atomic_intrinsic(builtin_available_predicate avail);
   ir_function_signature *_atomic_op(const char *intrinsic,
                                     builtin_available_predicate avail);

   B1(min3)
   B1(max3)
   B1(mid3)

   ir_function_signature *_image_prototype(const glsl_type *image_type,
                                           const char *intrinsic_name,
                                           unsigned num_arguments,
                                           unsigned flags);
   ir_function_signature *_image(const glsl_type *image_type,
                                 const char *intrinsic_name,
                                 unsigned num_arguments,
                                 unsigned flags);

   ir_function_signature *_memory_barrier_intrinsic(
      builtin_available_predicate avail);
   ir_function_signature *_memory_barrier(
      builtin_available_predicate avail);

#undef B0
#undef B1
#undef B2
#undef B3
#undef BA1
#undef BA2
   /** @} */
};

} /* anonymous namespace */

/**
 * Core builtin_builder functionality:
 *  @{
 */
builtin_builder::builtin_builder()
   : shader(NULL),
     gl_ModelViewProjectionMatrix(NULL),
     gl_Vertex(NULL)
{
   mem_ctx = NULL;
}

builtin_builder::~builtin_builder()
{
   ralloc_free(mem_ctx);
}

ir_function_signature *
builtin_builder::find(_mesa_glsl_parse_state *state,
                      const char *name, exec_list *actual_parameters)
{
   /* The shader currently being compiled requested a built-in function;
    * it needs to link against builtin_builder::shader in order to get them.
    *
    * Even if we don't find a matching signature, we still need to do this so
    * that the "no matching signature" error will list potential candidates
    * from the available built-ins.
    */
   state->uses_builtin_functions = true;

   ir_function *f = shader->symbols->get_function(name);
   if (f == NULL)
      return NULL;

   ir_function_signature *sig =
      f->matching_signature(state, actual_parameters, true);
   if (sig == NULL)
      return NULL;

   return sig;
}

void
builtin_builder::initialize()
{
   /* If already initialized, don't do it again. */
   if (mem_ctx != NULL)
      return;

   mem_ctx = ralloc_context(NULL);
   create_shader();
   create_intrinsics();
   create_builtins();
}

void
builtin_builder::release()
{
   ralloc_free(mem_ctx);
   mem_ctx = NULL;

   ralloc_free(shader);
   shader = NULL;
}

void
builtin_builder::create_shader()
{
   /* The target doesn't actually matter.  There's no target for generic
    * GLSL utility code that could be linked against any stage, so just
    * arbitrarily pick GL_VERTEX_SHADER.
    */
   shader = _mesa_new_shader(NULL, 0, GL_VERTEX_SHADER);
   shader->symbols = new(mem_ctx) glsl_symbol_table;

   gl_ModelViewProjectionMatrix =
      new(mem_ctx) ir_variable(glsl_type::mat4_type,
                               "gl_ModelViewProjectionMatrix",
                               ir_var_uniform, glsl_precision_high);

   shader->symbols->add_variable(gl_ModelViewProjectionMatrix);

   gl_Vertex = in_var(glsl_type::vec4_type, "gl_Vertex");
   shader->symbols->add_variable(gl_Vertex);
}

/** @} */

/**
 * Create ir_function and ir_function_signature objects for each
 * intrinsic.
 */
void
builtin_builder::create_intrinsics()
{
   add_function("__intrinsic_atomic_read",
                _atomic_intrinsic(shader_atomic_counters),
                NULL);
   add_function("__intrinsic_atomic_increment",
                _atomic_intrinsic(shader_atomic_counters),
                NULL);
   add_function("__intrinsic_atomic_predecrement",
                _atomic_intrinsic(shader_atomic_counters),
                NULL);

   add_image_functions(false);

   add_function("__intrinsic_memory_barrier",
                _memory_barrier_intrinsic(shader_image_load_store),
                NULL);
}

/**
 * Create ir_function and ir_function_signature objects for each built-in.
 *
 * Contains a list of every available built-in.
 */
void
builtin_builder::create_builtins()
{
#define F(NAME)                                 \
   add_function(#NAME,                          \
                _##NAME(glsl_type::float_type), \
                _##NAME(glsl_type::vec2_type),  \
                _##NAME(glsl_type::vec3_type),  \
                _##NAME(glsl_type::vec4_type),  \
                NULL);

#define FI(NAME)                                \
   add_function(#NAME,                          \
                _##NAME(glsl_type::float_type), \
                _##NAME(glsl_type::vec2_type),  \
                _##NAME(glsl_type::vec3_type),  \
                _##NAME(glsl_type::vec4_type),  \
                _##NAME(glsl_type::int_type),   \
                _##NAME(glsl_type::ivec2_type), \
                _##NAME(glsl_type::ivec3_type), \
                _##NAME(glsl_type::ivec4_type), \
                NULL);

#define FIU(NAME)                                                 \
   add_function(#NAME,                                            \
                _##NAME(always_available, glsl_type::float_type), \
                _##NAME(always_available, glsl_type::vec2_type),  \
                _##NAME(always_available, glsl_type::vec3_type),  \
                _##NAME(always_available, glsl_type::vec4_type),  \
                                                                  \
                _##NAME(always_available, glsl_type::int_type),   \
                _##NAME(always_available, glsl_type::ivec2_type), \
                _##NAME(always_available, glsl_type::ivec3_type), \
                _##NAME(always_available, glsl_type::ivec4_type), \
                                                                  \
                _##NAME(v130, glsl_type::uint_type),              \
                _##NAME(v130, glsl_type::uvec2_type),             \
                _##NAME(v130, glsl_type::uvec3_type),             \
                _##NAME(v130, glsl_type::uvec4_type),             \
                NULL);

#define IU(NAME)                                \
   add_function(#NAME,                          \
                _##NAME(glsl_type::int_type),   \
                _##NAME(glsl_type::ivec2_type), \
                _##NAME(glsl_type::ivec3_type), \
                _##NAME(glsl_type::ivec4_type), \
                                                \
                _##NAME(glsl_type::uint_type),  \
                _##NAME(glsl_type::uvec2_type), \
                _##NAME(glsl_type::uvec3_type), \
                _##NAME(glsl_type::uvec4_type), \
                NULL);

#define FIUB(NAME)                                                \
   add_function(#NAME,                                            \
                _##NAME(always_available, glsl_type::float_type), \
                _##NAME(always_available, glsl_type::vec2_type),  \
                _##NAME(always_available, glsl_type::vec3_type),  \
                _##NAME(always_available, glsl_type::vec4_type),  \
                                                                  \
                _##NAME(always_available, glsl_type::int_type),   \
                _##NAME(always_available, glsl_type::ivec2_type), \
                _##NAME(always_available, glsl_type::ivec3_type), \
                _##NAME(always_available, glsl_type::ivec4_type), \
                                                                  \
                _##NAME(v130, glsl_type::uint_type),              \
                _##NAME(v130, glsl_type::uvec2_type),             \
                _##NAME(v130, glsl_type::uvec3_type),             \
                _##NAME(v130, glsl_type::uvec4_type),             \
                                                                  \
                _##NAME(always_available, glsl_type::bool_type),  \
                _##NAME(always_available, glsl_type::bvec2_type), \
                _##NAME(always_available, glsl_type::bvec3_type), \
                _##NAME(always_available, glsl_type::bvec4_type), \
                NULL);

#define FIU2_MIXED(NAME)                                                                 \
   add_function(#NAME,                                                                   \
                _##NAME(always_available, glsl_type::float_type, glsl_type::float_type), \
                _##NAME(always_available, glsl_type::vec2_type,  glsl_type::float_type), \
                _##NAME(always_available, glsl_type::vec3_type,  glsl_type::float_type), \
                _##NAME(always_available, glsl_type::vec4_type,  glsl_type::float_type), \
                                                                                         \
                _##NAME(always_available, glsl_type::vec2_type,  glsl_type::vec2_type),  \
                _##NAME(always_available, glsl_type::vec3_type,  glsl_type::vec3_type),  \
                _##NAME(always_available, glsl_type::vec4_type,  glsl_type::vec4_type),  \
                                                                                         \
                _##NAME(always_available, glsl_type::int_type,   glsl_type::int_type),   \
                _##NAME(always_available, glsl_type::ivec2_type, glsl_type::int_type),   \
                _##NAME(always_available, glsl_type::ivec3_type, glsl_type::int_type),   \
                _##NAME(always_available, glsl_type::ivec4_type, glsl_type::int_type),   \
                                                                                         \
                _##NAME(always_available, glsl_type::ivec2_type, glsl_type::ivec2_type), \
                _##NAME(always_available, glsl_type::ivec3_type, glsl_type::ivec3_type), \
                _##NAME(always_available, glsl_type::ivec4_type, glsl_type::ivec4_type), \
                                                                                         \
                _##NAME(v130, glsl_type::uint_type,  glsl_type::uint_type),              \
                _##NAME(v130, glsl_type::uvec2_type, glsl_type::uint_type),              \
                _##NAME(v130, glsl_type::uvec3_type, glsl_type::uint_type),              \
                _##NAME(v130, glsl_type::uvec4_type, glsl_type::uint_type),              \
                                                                                         \
                _##NAME(v130, glsl_type::uvec2_type, glsl_type::uvec2_type),             \
                _##NAME(v130, glsl_type::uvec3_type, glsl_type::uvec3_type),             \
                _##NAME(v130, glsl_type::uvec4_type, glsl_type::uvec4_type),             \
                NULL);

   F(radians)
   F(degrees)
   F(sin)
   F(cos)
   F(tan)
   F(asin)
   F(acos)

   add_function("atan",
                _atan(glsl_type::float_type),
                _atan(glsl_type::vec2_type),
                _atan(glsl_type::vec3_type),
                _atan(glsl_type::vec4_type),
                _atan2(glsl_type::float_type),
                _atan2(glsl_type::vec2_type),
                _atan2(glsl_type::vec3_type),
                _atan2(glsl_type::vec4_type),
                NULL);

   F(sinh)
   F(cosh)
   F(tanh)
   F(asinh)
   F(acosh)
   F(atanh)
   F(pow)
   F(exp)
   F(log)
   F(exp2)
   F(log2)
   F(sqrt)
   F(inversesqrt)
   FI(abs)
   FI(sign)
   F(floor)
   F(trunc)
   F(round)
   F(roundEven)
   F(ceil)
   F(fract)

   add_function("mod",
                _mod(glsl_type::float_type, glsl_type::float_type),
                _mod(glsl_type::vec2_type,  glsl_type::float_type),
                _mod(glsl_type::vec3_type,  glsl_type::float_type),
                _mod(glsl_type::vec4_type,  glsl_type::float_type),

                _mod(glsl_type::vec2_type,  glsl_type::vec2_type),
                _mod(glsl_type::vec3_type,  glsl_type::vec3_type),
                _mod(glsl_type::vec4_type,  glsl_type::vec4_type),
                NULL);

   F(modf)

   FIU2_MIXED(min)
   FIU2_MIXED(max)
   FIU2_MIXED(clamp)

   add_function("mix",
                _mix_lrp(glsl_type::float_type, glsl_type::float_type),
                _mix_lrp(glsl_type::vec2_type,  glsl_type::float_type),
                _mix_lrp(glsl_type::vec3_type,  glsl_type::float_type),
                _mix_lrp(glsl_type::vec4_type,  glsl_type::float_type),

                _mix_lrp(glsl_type::vec2_type,  glsl_type::vec2_type),
                _mix_lrp(glsl_type::vec3_type,  glsl_type::vec3_type),
                _mix_lrp(glsl_type::vec4_type,  glsl_type::vec4_type),

                _mix_sel(v130, glsl_type::float_type, glsl_type::bool_type),
                _mix_sel(v130, glsl_type::vec2_type,  glsl_type::bvec2_type),
                _mix_sel(v130, glsl_type::vec3_type,  glsl_type::bvec3_type),
                _mix_sel(v130, glsl_type::vec4_type,  glsl_type::bvec4_type),

                _mix_sel(shader_integer_mix, glsl_type::int_type,   glsl_type::bool_type),
                _mix_sel(shader_integer_mix, glsl_type::ivec2_type, glsl_type::bvec2_type),
                _mix_sel(shader_integer_mix, glsl_type::ivec3_type, glsl_type::bvec3_type),
                _mix_sel(shader_integer_mix, glsl_type::ivec4_type, glsl_type::bvec4_type),

                _mix_sel(shader_integer_mix, glsl_type::uint_type,  glsl_type::bool_type),
                _mix_sel(shader_integer_mix, glsl_type::uvec2_type, glsl_type::bvec2_type),
                _mix_sel(shader_integer_mix, glsl_type::uvec3_type, glsl_type::bvec3_type),
                _mix_sel(shader_integer_mix, glsl_type::uvec4_type, glsl_type::bvec4_type),

                _mix_sel(shader_integer_mix, glsl_type::bool_type,  glsl_type::bool_type),
                _mix_sel(shader_integer_mix, glsl_type::bvec2_type, glsl_type::bvec2_type),
                _mix_sel(shader_integer_mix, glsl_type::bvec3_type, glsl_type::bvec3_type),
                _mix_sel(shader_integer_mix, glsl_type::bvec4_type, glsl_type::bvec4_type),
                NULL);

   add_function("step",
                _step(glsl_type::float_type, glsl_type::float_type),
                _step(glsl_type::float_type, glsl_type::vec2_type),
                _step(glsl_type::float_type, glsl_type::vec3_type),
                _step(glsl_type::float_type, glsl_type::vec4_type),

                _step(glsl_type::vec2_type,  glsl_type::vec2_type),
                _step(glsl_type::vec3_type,  glsl_type::vec3_type),
                _step(glsl_type::vec4_type,  glsl_type::vec4_type),
                NULL);

   add_function("smoothstep",
                _smoothstep(glsl_type::float_type, glsl_type::float_type),
                _smoothstep(glsl_type::float_type, glsl_type::vec2_type),
                _smoothstep(glsl_type::float_type, glsl_type::vec3_type),
                _smoothstep(glsl_type::float_type, glsl_type::vec4_type),

                _smoothstep(glsl_type::vec2_type,  glsl_type::vec2_type),
                _smoothstep(glsl_type::vec3_type,  glsl_type::vec3_type),
                _smoothstep(glsl_type::vec4_type,  glsl_type::vec4_type),
                NULL);
 
   F(isnan)
   F(isinf)

   F(floatBitsToInt)
   F(floatBitsToUint)
   add_function("intBitsToFloat",
                _intBitsToFloat(glsl_type::int_type),
                _intBitsToFloat(glsl_type::ivec2_type),
                _intBitsToFloat(glsl_type::ivec3_type),
                _intBitsToFloat(glsl_type::ivec4_type),
                NULL);
   add_function("uintBitsToFloat",
                _uintBitsToFloat(glsl_type::uint_type),
                _uintBitsToFloat(glsl_type::uvec2_type),
                _uintBitsToFloat(glsl_type::uvec3_type),
                _uintBitsToFloat(glsl_type::uvec4_type),
                NULL);

   add_function("packUnorm2x16",   _packUnorm2x16(shader_packing_or_es3_or_gpu_shader5),   NULL);
   add_function("packSnorm2x16",   _packSnorm2x16(shader_packing_or_es3),                  NULL);
   add_function("packUnorm4x8",    _packUnorm4x8(shader_packing_or_gpu_shader5),           NULL);
   add_function("packSnorm4x8",    _packSnorm4x8(shader_packing_or_gpu_shader5),           NULL);
   add_function("unpackUnorm2x16", _unpackUnorm2x16(shader_packing_or_es3_or_gpu_shader5), NULL);
   add_function("unpackSnorm2x16", _unpackSnorm2x16(shader_packing_or_es3),                NULL);
   add_function("unpackUnorm4x8",  _unpackUnorm4x8(shader_packing_or_gpu_shader5),         NULL);
   add_function("unpackSnorm4x8",  _unpackSnorm4x8(shader_packing_or_gpu_shader5),         NULL);
   add_function("packHalf2x16",    _packHalf2x16(shader_packing_or_es3),                   NULL);
   add_function("unpackHalf2x16",  _unpackHalf2x16(shader_packing_or_es3),                 NULL);

   F(length)
   F(distance)
   F(dot)

   add_function("cross", _cross(glsl_type::vec3_type), NULL);

   F(normalize)
   add_function("ftransform", _ftransform(), NULL);
   F(faceforward)
   F(reflect)
   F(refract)
   // ...
   add_function("matrixCompMult",
                _matrixCompMult(glsl_type::mat2_type),
                _matrixCompMult(glsl_type::mat3_type),
                _matrixCompMult(glsl_type::mat4_type),
                _matrixCompMult(glsl_type::mat2x3_type),
                _matrixCompMult(glsl_type::mat2x4_type),
                _matrixCompMult(glsl_type::mat3x2_type),
                _matrixCompMult(glsl_type::mat3x4_type),
                _matrixCompMult(glsl_type::mat4x2_type),
                _matrixCompMult(glsl_type::mat4x3_type),
                NULL);
   add_function("outerProduct",
                _outerProduct(glsl_type::mat2_type),
                _outerProduct(glsl_type::mat3_type),
                _outerProduct(glsl_type::mat4_type),
                _outerProduct(glsl_type::mat2x3_type),
                _outerProduct(glsl_type::mat2x4_type),
                _outerProduct(glsl_type::mat3x2_type),
                _outerProduct(glsl_type::mat3x4_type),
                _outerProduct(glsl_type::mat4x2_type),
                _outerProduct(glsl_type::mat4x3_type),
                NULL);
   add_function("determinant",
                _determinant_mat2(),
                _determinant_mat3(),
                _determinant_mat4(),
                NULL);
   add_function("inverse",
                _inverse_mat2(),
                _inverse_mat3(),
                _inverse_mat4(),
                NULL);
   add_function("transpose",
                _transpose(glsl_type::mat2_type),
                _transpose(glsl_type::mat3_type),
                _transpose(glsl_type::mat4_type),
                _transpose(glsl_type::mat2x3_type),
                _transpose(glsl_type::mat2x4_type),
                _transpose(glsl_type::mat3x2_type),
                _transpose(glsl_type::mat3x4_type),
                _transpose(glsl_type::mat4x2_type),
                _transpose(glsl_type::mat4x3_type),
                NULL);
   FIU(lessThan)
   FIU(lessThanEqual)
   FIU(greaterThan)
   FIU(greaterThanEqual)
   FIUB(notEqual)
   FIUB(equal)

   add_function("any",
                _any(glsl_type::bvec2_type),
                _any(glsl_type::bvec3_type),
                _any(glsl_type::bvec4_type),
                NULL);

   add_function("all",
                _all(glsl_type::bvec2_type),
                _all(glsl_type::bvec3_type),
                _all(glsl_type::bvec4_type),
                NULL);

   add_function("not",
                _not(glsl_type::bvec2_type),
                _not(glsl_type::bvec3_type),
                _not(glsl_type::bvec4_type),
                NULL);

   add_function("textureSize",
                _textureSize(v130, glsl_type::int_type,   glsl_type::sampler1D_type),
                _textureSize(v130, glsl_type::int_type,   glsl_type::isampler1D_type),
                _textureSize(v130, glsl_type::int_type,   glsl_type::usampler1D_type),

                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler2D_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::isampler2D_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::usampler2D_type),

                _textureSize(v130, glsl_type::ivec3_type, glsl_type::sampler3D_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::isampler3D_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::usampler3D_type),

                _textureSize(v130, glsl_type::ivec2_type, glsl_type::samplerCube_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::isamplerCube_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::usamplerCube_type),

                _textureSize(v130, glsl_type::int_type,   glsl_type::sampler1DShadow_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler2DShadow_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::samplerCubeShadow_type),

                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler1DArray_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::isampler1DArray_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::usampler1DArray_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::sampler2DArray_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::isampler2DArray_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::usampler2DArray_type),

                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler1DArrayShadow_type),
                _textureSize(v130, glsl_type::ivec3_type, glsl_type::sampler2DArrayShadow_type),

                _textureSize(texture_cube_map_array, glsl_type::ivec3_type, glsl_type::samplerCubeArray_type),
                _textureSize(texture_cube_map_array, glsl_type::ivec3_type, glsl_type::isamplerCubeArray_type),
                _textureSize(texture_cube_map_array, glsl_type::ivec3_type, glsl_type::usamplerCubeArray_type),
                _textureSize(texture_cube_map_array, glsl_type::ivec3_type, glsl_type::samplerCubeArrayShadow_type),

                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler2DRect_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::isampler2DRect_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::usampler2DRect_type),
                _textureSize(v130, glsl_type::ivec2_type, glsl_type::sampler2DRectShadow_type),

                _textureSize(v140, glsl_type::int_type,   glsl_type::samplerBuffer_type),
                _textureSize(v140, glsl_type::int_type,   glsl_type::isamplerBuffer_type),
                _textureSize(v140, glsl_type::int_type,   glsl_type::usamplerBuffer_type),
                _textureSize(texture_multisample, glsl_type::ivec2_type, glsl_type::sampler2DMS_type),
                _textureSize(texture_multisample, glsl_type::ivec2_type, glsl_type::isampler2DMS_type),
                _textureSize(texture_multisample, glsl_type::ivec2_type, glsl_type::usampler2DMS_type),

                _textureSize(texture_multisample, glsl_type::ivec3_type, glsl_type::sampler2DMSArray_type),
                _textureSize(texture_multisample, glsl_type::ivec3_type, glsl_type::isampler2DMSArray_type),
                _textureSize(texture_multisample, glsl_type::ivec3_type, glsl_type::usampler2DMSArray_type),
                NULL);

   add_function("texture",
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::samplerCube_type,  glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type,   glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type,   glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::samplerCubeShadow_type, glsl_type::vec4_type),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type),

                _texture(ir_tex, texture_cube_map_array, glsl_type::vec4_type,  glsl_type::samplerCubeArray_type,  glsl_type::vec4_type),
                _texture(ir_tex, texture_cube_map_array, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_tex, texture_cube_map_array, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec4_type),
                /* samplerCubeArrayShadow is special; it has an extra parameter
                 * for the shadow comparitor since there is no vec5 type.
                 */
                _textureCubeArrayShadow(),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::samplerCube_type,  glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler1DShadow_type,   glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler2DShadow_type,   glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::samplerCubeShadow_type, glsl_type::vec4_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type),

                _texture(ir_txb, fs_texture_cube_map_array, glsl_type::vec4_type,  glsl_type::samplerCubeArray_type,  glsl_type::vec4_type),
                _texture(ir_txb, fs_texture_cube_map_array, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_txb, fs_texture_cube_map_array, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type),

                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("textureLod",
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::samplerCube_type,  glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec3_type),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type),

                _texture(ir_txl, texture_cube_map_array, glsl_type::vec4_type,  glsl_type::samplerCubeArray_type,  glsl_type::vec4_type),
                _texture(ir_txl, texture_cube_map_array, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_txl, texture_cube_map_array, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("textureOffset",
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txb, v130_fs_only, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txb, v130_fs_only, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                NULL);

   add_function("textureProj",
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txb, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texelFetch",
                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::int_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::int_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::int_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::ivec2_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::ivec3_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::ivec2_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::ivec2_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::ivec3_type),

                _texelFetch(v140, glsl_type::vec4_type,  glsl_type::samplerBuffer_type,  glsl_type::int_type),
                _texelFetch(v140, glsl_type::ivec4_type, glsl_type::isamplerBuffer_type, glsl_type::int_type),
                _texelFetch(v140, glsl_type::uvec4_type, glsl_type::usamplerBuffer_type, glsl_type::int_type),

                _texelFetch(texture_multisample, glsl_type::vec4_type,  glsl_type::sampler2DMS_type,  glsl_type::ivec2_type),
                _texelFetch(texture_multisample, glsl_type::ivec4_type, glsl_type::isampler2DMS_type, glsl_type::ivec2_type),
                _texelFetch(texture_multisample, glsl_type::uvec4_type, glsl_type::usampler2DMS_type, glsl_type::ivec2_type),

                _texelFetch(texture_multisample, glsl_type::vec4_type,  glsl_type::sampler2DMSArray_type,  glsl_type::ivec3_type),
                _texelFetch(texture_multisample, glsl_type::ivec4_type, glsl_type::isampler2DMSArray_type, glsl_type::ivec3_type),
                _texelFetch(texture_multisample, glsl_type::uvec4_type, glsl_type::usampler2DMSArray_type, glsl_type::ivec3_type),
                NULL);

   add_function("texelFetchOffset",
                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::int_type, glsl_type::int_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::int_type, glsl_type::int_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::int_type, glsl_type::int_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::ivec2_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::ivec2_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::ivec2_type, glsl_type::ivec2_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::ivec3_type, glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::ivec3_type, glsl_type::ivec3_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::ivec3_type, glsl_type::ivec3_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::ivec2_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::ivec2_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::ivec2_type, glsl_type::ivec2_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::ivec2_type, glsl_type::int_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::ivec2_type, glsl_type::int_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::ivec2_type, glsl_type::int_type),

                _texelFetch(v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::ivec3_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::ivec3_type, glsl_type::ivec2_type),
                _texelFetch(v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::ivec3_type, glsl_type::ivec2_type),

                NULL);

   add_function("textureProjOffset",
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_tex, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_tex, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txb, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txb, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txb, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                NULL);

   add_function("textureLodOffset",
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                NULL);

   add_function("textureProjLod",
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("textureProjLodOffset",
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txl, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                NULL);

   add_function("textureGrad",
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::samplerCube_type,  glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type,   glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type,   glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::samplerCubeShadow_type, glsl_type::vec4_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type),

                _texture(ir_txd, texture_cube_map_array, glsl_type::vec4_type,  glsl_type::samplerCubeArray_type,  glsl_type::vec4_type),
                _texture(ir_txd, texture_cube_map_array, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_txd, texture_cube_map_array, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec4_type),
                NULL);

   add_function("textureGradOffset",
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::float_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::float_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1DArray_type,  glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1DArray_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DArray_type,  glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec4_type, TEX_OFFSET),
                NULL);

   add_function("textureProjGrad",
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("textureProjGradOffset",
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec2_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler1D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler1D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler3D_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler3D_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::vec4_type,  glsl_type::sampler2DRect_type,  glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),

                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                _texture(ir_txd, v130, glsl_type::float_type, glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT | TEX_OFFSET),
                NULL);

   add_function("EmitVertex",   _EmitVertex(),   NULL);
   add_function("EndPrimitive", _EndPrimitive(), NULL);
   add_function("EmitStreamVertex",
                _EmitStreamVertex(gs_streams, glsl_type::uint_type),
                _EmitStreamVertex(gs_streams, glsl_type::int_type),
                NULL);
   add_function("EndStreamPrimitive",
                _EndStreamPrimitive(gs_streams, glsl_type::uint_type),
                _EndStreamPrimitive(gs_streams, glsl_type::int_type),
                NULL);

   add_function("textureQueryLOD",
                _textureQueryLod(glsl_type::sampler1D_type,  glsl_type::float_type),
                _textureQueryLod(glsl_type::isampler1D_type, glsl_type::float_type),
                _textureQueryLod(glsl_type::usampler1D_type, glsl_type::float_type),

                _textureQueryLod(glsl_type::sampler2D_type,  glsl_type::vec2_type),
                _textureQueryLod(glsl_type::isampler2D_type, glsl_type::vec2_type),
                _textureQueryLod(glsl_type::usampler2D_type, glsl_type::vec2_type),

                _textureQueryLod(glsl_type::sampler3D_type,  glsl_type::vec3_type),
                _textureQueryLod(glsl_type::isampler3D_type, glsl_type::vec3_type),
                _textureQueryLod(glsl_type::usampler3D_type, glsl_type::vec3_type),

                _textureQueryLod(glsl_type::samplerCube_type,  glsl_type::vec3_type),
                _textureQueryLod(glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _textureQueryLod(glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _textureQueryLod(glsl_type::sampler1DArray_type,  glsl_type::float_type),
                _textureQueryLod(glsl_type::isampler1DArray_type, glsl_type::float_type),
                _textureQueryLod(glsl_type::usampler1DArray_type, glsl_type::float_type),

                _textureQueryLod(glsl_type::sampler2DArray_type,  glsl_type::vec2_type),
                _textureQueryLod(glsl_type::isampler2DArray_type, glsl_type::vec2_type),
                _textureQueryLod(glsl_type::usampler2DArray_type, glsl_type::vec2_type),

                _textureQueryLod(glsl_type::samplerCubeArray_type,  glsl_type::vec3_type),
                _textureQueryLod(glsl_type::isamplerCubeArray_type, glsl_type::vec3_type),
                _textureQueryLod(glsl_type::usamplerCubeArray_type, glsl_type::vec3_type),

                _textureQueryLod(glsl_type::sampler1DShadow_type, glsl_type::float_type),
                _textureQueryLod(glsl_type::sampler2DShadow_type, glsl_type::vec2_type),
                _textureQueryLod(glsl_type::samplerCubeShadow_type, glsl_type::vec3_type),
                _textureQueryLod(glsl_type::sampler1DArrayShadow_type, glsl_type::float_type),
                _textureQueryLod(glsl_type::sampler2DArrayShadow_type, glsl_type::vec2_type),
                _textureQueryLod(glsl_type::samplerCubeArrayShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("textureQueryLevels",
                _textureQueryLevels(glsl_type::sampler1D_type),
                _textureQueryLevels(glsl_type::sampler2D_type),
                _textureQueryLevels(glsl_type::sampler3D_type),
                _textureQueryLevels(glsl_type::samplerCube_type),
                _textureQueryLevels(glsl_type::sampler1DArray_type),
                _textureQueryLevels(glsl_type::sampler2DArray_type),
                _textureQueryLevels(glsl_type::samplerCubeArray_type),
                _textureQueryLevels(glsl_type::sampler1DShadow_type),
                _textureQueryLevels(glsl_type::sampler2DShadow_type),
                _textureQueryLevels(glsl_type::samplerCubeShadow_type),
                _textureQueryLevels(glsl_type::sampler1DArrayShadow_type),
                _textureQueryLevels(glsl_type::sampler2DArrayShadow_type),
                _textureQueryLevels(glsl_type::samplerCubeArrayShadow_type),

                _textureQueryLevels(glsl_type::isampler1D_type),
                _textureQueryLevels(glsl_type::isampler2D_type),
                _textureQueryLevels(glsl_type::isampler3D_type),
                _textureQueryLevels(glsl_type::isamplerCube_type),
                _textureQueryLevels(glsl_type::isampler1DArray_type),
                _textureQueryLevels(glsl_type::isampler2DArray_type),
                _textureQueryLevels(glsl_type::isamplerCubeArray_type),

                _textureQueryLevels(glsl_type::usampler1D_type),
                _textureQueryLevels(glsl_type::usampler2D_type),
                _textureQueryLevels(glsl_type::usampler3D_type),
                _textureQueryLevels(glsl_type::usamplerCube_type),
                _textureQueryLevels(glsl_type::usampler1DArray_type),
                _textureQueryLevels(glsl_type::usampler2DArray_type),
                _textureQueryLevels(glsl_type::usamplerCubeArray_type),

                NULL);

   add_function("texture1D",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::float_type),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::float_type),
                NULL);

   add_function("texture1DArray",
                _texture(ir_tex, texture_array,    glsl_type::vec4_type, glsl_type::sampler1DArray_type, glsl_type::vec2_type),
                _texture(ir_txb, fs_texture_array, glsl_type::vec4_type, glsl_type::sampler1DArray_type, glsl_type::vec2_type),
                NULL);

   add_function("texture1DProj",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture1DLod",
                _texture(ir_txl, tex1d_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::float_type),
                NULL);

   add_function("texture1DArrayLod",
                _texture(ir_txl, texture_array_lod, glsl_type::vec4_type, glsl_type::sampler1DArray_type, glsl_type::vec2_type),
                NULL);

   add_function("texture1DProjLod",
                _texture(ir_txl, tex1d_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txl, tex1d_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture2D",
                _texture(ir_tex, always_available, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
                _texture(ir_txb, fs_only,          glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
                _texture(ir_tex, texture_external, glsl_type::vec4_type,  glsl_type::samplerExternalOES_type, glsl_type::vec2_type),
                NULL);

   add_function("texture2DArray",
                _texture(ir_tex, texture_array,    glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_txb, fs_texture_array, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type),
                NULL);

   add_function("texture2DProj",
                _texture(ir_tex, always_available, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, always_available, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, fs_only,          glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txb, fs_only,          glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_tex, texture_external, glsl_type::vec4_type,  glsl_type::samplerExternalOES_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, texture_external, glsl_type::vec4_type,  glsl_type::samplerExternalOES_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture2DLod",
                _texture(ir_txl, lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
                NULL);

   add_function("texture2DArrayLod",
                _texture(ir_txl, texture_array_lod, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type),
                NULL);

   add_function("texture2DProjLod",
                _texture(ir_txl, lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txl, lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture3D",
                _texture(ir_tex, tex3d,    glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec3_type),
                _texture(ir_txb, fs_tex3d, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec3_type),
                NULL);

   add_function("texture3DProj",
                _texture(ir_tex, tex3d,    glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, fs_tex3d, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture3DLod",
                _texture(ir_txl, tex3d_lod, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec3_type),
                NULL);

   add_function("texture3DProjLod",
                _texture(ir_txl, tex3d_lod, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("textureCube",
                _texture(ir_tex, always_available, glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
                _texture(ir_txb, fs_only,          glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
                NULL);

   add_function("textureCubeLod",
                _texture(ir_txl, lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
                NULL);

   add_function("texture2DRect",
                _texture(ir_tex, texture_rectangle, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec2_type),
                NULL);

   add_function("texture2DRectProj",
                _texture(ir_tex, texture_rectangle, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_tex, texture_rectangle, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

	add_function("texture2DLodEXT",
				 _texture(ir_txl, es_lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
				 NULL);
	add_function("texture2DProjLodEXT",
				 _texture(ir_txl, es_lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
				 _texture(ir_txl, es_lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
				 NULL);
	add_function("textureCubeLodEXT",
				 _texture(ir_txl, es_lod_exists_in_stage, glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
				 NULL);
	
   add_function("shadow1D",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec3_type),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow1DArray",
                _texture(ir_tex, texture_array,    glsl_type::vec4_type,  glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                _texture(ir_txb, fs_texture_array, glsl_type::vec4_type,  glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow2D",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec3_type),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec3_type),
                NULL);
	add_function("shadow2DEXT",
				 _texture(ir_tex, es_shadow_samplers, glsl_type::float_type,  glsl_type::sampler2DShadow_type, glsl_type::vec3_type),
				 NULL);

   add_function("shadow2DArray",
                _texture(ir_tex, texture_array,    glsl_type::vec4_type,  glsl_type::sampler2DArrayShadow_type, glsl_type::vec4_type),
                _texture(ir_txb, fs_texture_array, glsl_type::vec4_type,  glsl_type::sampler2DArrayShadow_type, glsl_type::vec4_type),
                NULL);

   add_function("shadow1DProj",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("shadow2DProj",
                _texture(ir_tex, v110,         glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                _texture(ir_txb, v110_fs_only, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);
	add_function("shadow2DProjEXT",
				 _texture(ir_tex, es_shadow_samplers, glsl_type::float_type,  glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
				 NULL);

   add_function("shadow1DLod",
                _texture(ir_txl, v110_lod, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow2DLod",
                _texture(ir_txl, v110_lod, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow1DArrayLod",
                _texture(ir_txl, texture_array_lod, glsl_type::vec4_type, glsl_type::sampler1DArrayShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow1DProjLod",
                _texture(ir_txl, v110_lod, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("shadow2DProjLod",
                _texture(ir_txl, v110_lod, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("shadow2DRect",
                _texture(ir_tex, texture_rectangle, glsl_type::vec4_type,  glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow2DRectProj",
                _texture(ir_tex, texture_rectangle, glsl_type::vec4_type,  glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture1DGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::float_type),
                NULL);

   add_function("texture1DProjGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec2_type, TEX_PROJECT),
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler1D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture2DGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
                NULL);

   add_function("texture2DProjGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture3DGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec3_type),
                NULL);

   add_function("texture3DProjGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler3D_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("textureCubeGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
                NULL);
	
	add_function("texture2DGradEXT",
				 _texture(ir_txd, es_shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec2_type),
				 NULL);
	add_function("texture2DProjGradEXT",
				 _texture(ir_txd, es_shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec3_type, TEX_PROJECT),
				 _texture(ir_txd, es_shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2D_type, glsl_type::vec4_type, TEX_PROJECT),
				 NULL);
	add_function("textureCubeGradEXT",
				 _texture(ir_txd, es_shader_texture_lod, glsl_type::vec4_type,  glsl_type::samplerCube_type, glsl_type::vec3_type),
				 NULL);
	
   add_function("shadow1DGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow1DProjGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler1DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("shadow2DGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow2DProjGradARB",
                _texture(ir_txd, shader_texture_lod, glsl_type::vec4_type,  glsl_type::sampler2DShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("texture2DRectGradARB",
                _texture(ir_txd, shader_texture_lod_and_rect, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec2_type),
                NULL);

   add_function("texture2DRectProjGradARB",
                _texture(ir_txd, shader_texture_lod_and_rect, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec3_type, TEX_PROJECT),
                _texture(ir_txd, shader_texture_lod_and_rect, glsl_type::vec4_type,  glsl_type::sampler2DRect_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("shadow2DRectGradARB",
                _texture(ir_txd, shader_texture_lod_and_rect, glsl_type::vec4_type,  glsl_type::sampler2DRectShadow_type, glsl_type::vec3_type),
                NULL);

   add_function("shadow2DRectProjGradARB",
                _texture(ir_txd, shader_texture_lod_and_rect, glsl_type::vec4_type,  glsl_type::sampler2DRectShadow_type, glsl_type::vec4_type, TEX_PROJECT),
                NULL);

   add_function("textureGather",
                _texture(ir_tg4, texture_gather, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type),
                _texture(ir_tg4, texture_gather, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type),
                _texture(ir_tg4, texture_gather, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type),

                _texture(ir_tg4, texture_gather, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_tg4, texture_gather, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type),
                _texture(ir_tg4, texture_gather, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type),

                _texture(ir_tg4, texture_gather, glsl_type::vec4_type, glsl_type::samplerCube_type, glsl_type::vec3_type),
                _texture(ir_tg4, texture_gather, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type),
                _texture(ir_tg4, texture_gather, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type),

                _texture(ir_tg4, texture_gather, glsl_type::vec4_type, glsl_type::samplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_tg4, texture_gather, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type),
                _texture(ir_tg4, texture_gather, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::samplerCube_type, glsl_type::vec3_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isamplerCube_type, glsl_type::vec3_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usamplerCube_type, glsl_type::vec3_type, TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::samplerCubeArray_type, glsl_type::vec4_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isamplerCubeArray_type, glsl_type::vec4_type, TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usamplerCubeArray_type, glsl_type::vec4_type, TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DShadow_type, glsl_type::vec2_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec3_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::samplerCubeShadow_type, glsl_type::vec3_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::samplerCubeArrayShadow_type, glsl_type::vec4_type),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec2_type),
                NULL);

   add_function("textureGatherOffset",
                _texture(ir_tg4, texture_gather_only, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tg4, texture_gather_only, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET),
                _texture(ir_tg4, texture_gather_only, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET),

                _texture(ir_tg4, texture_gather_only, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tg4, texture_gather_only, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),
                _texture(ir_tg4, texture_gather_only, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DShadow_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET_NONCONST),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec2_type, TEX_OFFSET_NONCONST),
                NULL);

   add_function("textureGatherOffsets",
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2D_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DArray_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::ivec4_type, glsl_type::isampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),
                _texture(ir_tg4, gpu_shader5, glsl_type::uvec4_type, glsl_type::usampler2DRect_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY | TEX_COMPONENT),

                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DShadow_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DArrayShadow_type, glsl_type::vec3_type, TEX_OFFSET_ARRAY),
                _texture(ir_tg4, gpu_shader5, glsl_type::vec4_type, glsl_type::sampler2DRectShadow_type, glsl_type::vec2_type, TEX_OFFSET_ARRAY),
                NULL);

   F(dFdx)
   F(dFdy)
   F(fwidth)
   F(dFdxCoarse)
   F(dFdyCoarse)
   F(fwidthCoarse)
   F(dFdxFine)
   F(dFdyFine)
   F(fwidthFine)
   F(noise1)
   F(noise2)
   F(noise3)
   F(noise4)

   IU(bitfieldExtract)
   IU(bitfieldInsert)
   IU(bitfieldReverse)
   IU(bitCount)
   IU(findLSB)
   IU(findMSB)
   F(fma)

   add_function("ldexp",
                _ldexp(glsl_type::float_type, glsl_type::int_type),
                _ldexp(glsl_type::vec2_type,  glsl_type::ivec2_type),
                _ldexp(glsl_type::vec3_type,  glsl_type::ivec3_type),
                _ldexp(glsl_type::vec4_type,  glsl_type::ivec4_type),
                NULL);

   add_function("frexp",
                _frexp(glsl_type::float_type, glsl_type::int_type),
                _frexp(glsl_type::vec2_type,  glsl_type::ivec2_type),
                _frexp(glsl_type::vec3_type,  glsl_type::ivec3_type),
                _frexp(glsl_type::vec4_type,  glsl_type::ivec4_type),
                NULL);
   add_function("uaddCarry",
                _uaddCarry(glsl_type::uint_type),
                _uaddCarry(glsl_type::uvec2_type),
                _uaddCarry(glsl_type::uvec3_type),
                _uaddCarry(glsl_type::uvec4_type),
                NULL);
   add_function("usubBorrow",
                _usubBorrow(glsl_type::uint_type),
                _usubBorrow(glsl_type::uvec2_type),
                _usubBorrow(glsl_type::uvec3_type),
                _usubBorrow(glsl_type::uvec4_type),
                NULL);
   add_function("imulExtended",
                _mulExtended(glsl_type::int_type),
                _mulExtended(glsl_type::ivec2_type),
                _mulExtended(glsl_type::ivec3_type),
                _mulExtended(glsl_type::ivec4_type),
                NULL);
   add_function("umulExtended",
                _mulExtended(glsl_type::uint_type),
                _mulExtended(glsl_type::uvec2_type),
                _mulExtended(glsl_type::uvec3_type),
                _mulExtended(glsl_type::uvec4_type),
                NULL);
   add_function("interpolateAtCentroid",
                _interpolateAtCentroid(glsl_type::float_type),
                _interpolateAtCentroid(glsl_type::vec2_type),
                _interpolateAtCentroid(glsl_type::vec3_type),
                _interpolateAtCentroid(glsl_type::vec4_type),
                NULL);
   add_function("interpolateAtOffset",
                _interpolateAtOffset(glsl_type::float_type),
                _interpolateAtOffset(glsl_type::vec2_type),
                _interpolateAtOffset(glsl_type::vec3_type),
                _interpolateAtOffset(glsl_type::vec4_type),
                NULL);
   add_function("interpolateAtSample",
                _interpolateAtSample(glsl_type::float_type),
                _interpolateAtSample(glsl_type::vec2_type),
                _interpolateAtSample(glsl_type::vec3_type),
                _interpolateAtSample(glsl_type::vec4_type),
                NULL);

   add_function("atomicCounter",
                _atomic_op("__intrinsic_atomic_read",
                           shader_atomic_counters),
                NULL);
   add_function("atomicCounterIncrement",
                _atomic_op("__intrinsic_atomic_increment",
                           shader_atomic_counters),
                NULL);
   add_function("atomicCounterDecrement",
                _atomic_op("__intrinsic_atomic_predecrement",
                           shader_atomic_counters),
                NULL);

   add_function("min3",
                _min3(glsl_type::float_type),
                _min3(glsl_type::vec2_type),
                _min3(glsl_type::vec3_type),
                _min3(glsl_type::vec4_type),

                _min3(glsl_type::int_type),
                _min3(glsl_type::ivec2_type),
                _min3(glsl_type::ivec3_type),
                _min3(glsl_type::ivec4_type),

                _min3(glsl_type::uint_type),
                _min3(glsl_type::uvec2_type),
                _min3(glsl_type::uvec3_type),
                _min3(glsl_type::uvec4_type),
                NULL);

   add_function("max3",
                _max3(glsl_type::float_type),
                _max3(glsl_type::vec2_type),
                _max3(glsl_type::vec3_type),
                _max3(glsl_type::vec4_type),

                _max3(glsl_type::int_type),
                _max3(glsl_type::ivec2_type),
                _max3(glsl_type::ivec3_type),
                _max3(glsl_type::ivec4_type),

                _max3(glsl_type::uint_type),
                _max3(glsl_type::uvec2_type),
                _max3(glsl_type::uvec3_type),
                _max3(glsl_type::uvec4_type),
                NULL);

   add_function("mid3",
                _mid3(glsl_type::float_type),
                _mid3(glsl_type::vec2_type),
                _mid3(glsl_type::vec3_type),
                _mid3(glsl_type::vec4_type),

                _mid3(glsl_type::int_type),
                _mid3(glsl_type::ivec2_type),
                _mid3(glsl_type::ivec3_type),
                _mid3(glsl_type::ivec4_type),

                _mid3(glsl_type::uint_type),
                _mid3(glsl_type::uvec2_type),
                _mid3(glsl_type::uvec3_type),
                _mid3(glsl_type::uvec4_type),
                NULL);

   add_image_functions(true);

   add_function("memoryBarrier",
                _memory_barrier(shader_image_load_store),
                NULL);

#undef F
#undef FI
#undef FIU
#undef FIUB
#undef FIU2_MIXED
}

void
builtin_builder::add_function(const char *name, ...)
{
   va_list ap;

   ir_function *f = new(mem_ctx) ir_function(name);

   va_start(ap, name);
   while (true) {
      ir_function_signature *sig = va_arg(ap, ir_function_signature *);
      if (sig == NULL)
         break;

      if (false) {
         exec_list stuff;
         stuff.push_tail(sig);
         validate_ir_tree(&stuff);
      }

      f->add_signature(sig);
   }
   va_end(ap);

   shader->symbols->add_function(f);
}

void
builtin_builder::add_image_function(const char *name,
                                    const char *intrinsic_name,
                                    unsigned num_arguments,
                                    unsigned flags)
{
   static const glsl_type *const types[] = {
      glsl_type::image1D_type,
      glsl_type::image2D_type,
      glsl_type::image3D_type,
      glsl_type::image2DRect_type,
      glsl_type::imageCube_type,
      glsl_type::imageBuffer_type,
      glsl_type::image1DArray_type,
      glsl_type::image2DArray_type,
      glsl_type::imageCubeArray_type,
      glsl_type::image2DMS_type,
      glsl_type::image2DMSArray_type,
      glsl_type::iimage1D_type,
      glsl_type::iimage2D_type,
      glsl_type::iimage3D_type,
      glsl_type::iimage2DRect_type,
      glsl_type::iimageCube_type,
      glsl_type::iimageBuffer_type,
      glsl_type::iimage1DArray_type,
      glsl_type::iimage2DArray_type,
      glsl_type::iimageCubeArray_type,
      glsl_type::iimage2DMS_type,
      glsl_type::iimage2DMSArray_type,
      glsl_type::uimage1D_type,
      glsl_type::uimage2D_type,
      glsl_type::uimage3D_type,
      glsl_type::uimage2DRect_type,
      glsl_type::uimageCube_type,
      glsl_type::uimageBuffer_type,
      glsl_type::uimage1DArray_type,
      glsl_type::uimage2DArray_type,
      glsl_type::uimageCubeArray_type,
      glsl_type::uimage2DMS_type,
      glsl_type::uimage2DMSArray_type
   };
   ir_function *f = new(mem_ctx) ir_function(name);

   for (unsigned i = 0; i < Elements(types); ++i) {
      if (types[i]->sampler_type != GLSL_TYPE_FLOAT ||
          (flags & IMAGE_FUNCTION_SUPPORTS_FLOAT_DATA_TYPE))
         f->add_signature(_image(types[i], intrinsic_name,
                                 num_arguments, flags));
   }

   shader->symbols->add_function(f);
}

void
builtin_builder::add_image_functions(bool glsl)
{
   const unsigned flags = (glsl ? IMAGE_FUNCTION_EMIT_STUB : 0);

   add_image_function(glsl ? "imageLoad" : "__intrinsic_image_load",
                      "__intrinsic_image_load", 0,
                      (flags | IMAGE_FUNCTION_HAS_VECTOR_DATA_TYPE |
                       IMAGE_FUNCTION_SUPPORTS_FLOAT_DATA_TYPE |
                       IMAGE_FUNCTION_READ_ONLY));

   add_image_function(glsl ? "imageStore" : "__intrinsic_image_store",
                      "__intrinsic_image_store", 1,
                      (flags | IMAGE_FUNCTION_RETURNS_VOID |
                       IMAGE_FUNCTION_HAS_VECTOR_DATA_TYPE |
                       IMAGE_FUNCTION_SUPPORTS_FLOAT_DATA_TYPE |
                       IMAGE_FUNCTION_WRITE_ONLY));

   add_image_function(glsl ? "imageAtomicAdd" : "__intrinsic_image_atomic_add",
                      "__intrinsic_image_atomic_add", 1, flags);

   add_image_function(glsl ? "imageAtomicMin" : "__intrinsic_image_atomic_min",
                      "__intrinsic_image_atomic_min", 1, flags);

   add_image_function(glsl ? "imageAtomicMax" : "__intrinsic_image_atomic_max",
                      "__intrinsic_image_atomic_max", 1, flags);

   add_image_function(glsl ? "imageAtomicAnd" : "__intrinsic_image_atomic_and",
                      "__intrinsic_image_atomic_and", 1, flags);

   add_image_function(glsl ? "imageAtomicOr" : "__intrinsic_image_atomic_or",
                      "__intrinsic_image_atomic_or", 1, flags);

   add_image_function(glsl ? "imageAtomicXor" : "__intrinsic_image_atomic_xor",
                      "__intrinsic_image_atomic_xor", 1, flags);

   add_image_function((glsl ? "imageAtomicExchange" :
                       "__intrinsic_image_atomic_exchange"),
                      "__intrinsic_image_atomic_exchange", 1, flags);

   add_image_function((glsl ? "imageAtomicCompSwap" :
                       "__intrinsic_image_atomic_comp_swap"),
                      "__intrinsic_image_atomic_comp_swap", 2, flags);
}

ir_variable *
builtin_builder::in_var(const glsl_type *type, const char *name)
{
   return new(mem_ctx) ir_variable(type, name, ir_var_function_in, glsl_precision_undefined);
}

ir_variable *
builtin_builder::out_var(const glsl_type *type, const char *name)
{
   return new(mem_ctx) ir_variable(type, name, ir_var_function_out, glsl_precision_undefined);
}

ir_constant *
builtin_builder::imm(float f, unsigned vector_elements)
{
   return new(mem_ctx) ir_constant(f, vector_elements);
}

ir_constant *
builtin_builder::imm(int i, unsigned vector_elements)
{
   return new(mem_ctx) ir_constant(i, vector_elements);
}

ir_constant *
builtin_builder::imm(unsigned u, unsigned vector_elements)
{
   return new(mem_ctx) ir_constant(u, vector_elements);
}

ir_constant *
builtin_builder::imm(const glsl_type *type, const ir_constant_data &data)
{
   return new(mem_ctx) ir_constant(type, &data);
}

ir_dereference_variable *
builtin_builder::var_ref(ir_variable *var)
{
   return new(mem_ctx) ir_dereference_variable(var);
}

ir_dereference_array *
builtin_builder::array_ref(ir_variable *var, int idx)
{
   return new(mem_ctx) ir_dereference_array(var, imm(idx));
}

/** Return an element of a matrix */
ir_swizzle *
builtin_builder::matrix_elt(ir_variable *var, int column, int row)
{
   return swizzle(array_ref(var, column), row, 1);
}

/**
 * Implementations of built-in functions:
 *  @{
 */
ir_function_signature *
builtin_builder::new_sig(const glsl_type *return_type,
                         builtin_available_predicate avail,
                         int num_params,
                         ...)
{
   va_list ap;

   ir_function_signature *sig =
      new(mem_ctx) ir_function_signature(return_type, glsl_precision_undefined, avail);

   exec_list plist;
   va_start(ap, num_params);
   for (int i = 0; i < num_params; i++) {
      plist.push_tail(va_arg(ap, ir_variable *));
   }
   va_end(ap);

   sig->replace_parameters(&plist);
   return sig;
}

#define MAKE_SIG(return_type, avail, ...)  \
   ir_function_signature *sig =               \
      new_sig(return_type, avail, __VA_ARGS__);      \
   ir_factory body(&sig->body, mem_ctx);             \
   sig->is_defined = true;

#define MAKE_INTRINSIC(return_type, avail, ...)      \
   ir_function_signature *sig =                      \
      new_sig(return_type, avail, __VA_ARGS__);      \
   sig->is_intrinsic = true;

ir_function_signature *
builtin_builder::unop(builtin_available_predicate avail,
                      ir_expression_operation opcode,
                      const glsl_type *return_type,
                      const glsl_type *param_type)
{
   ir_variable *x = in_var(param_type, "x");
   MAKE_SIG(return_type, avail, 1, x);
   body.emit(ret(expr(opcode, x)));
   return sig;
}

#define UNOP(NAME, OPCODE, AVAIL)               \
ir_function_signature *                         \
builtin_builder::_##NAME(const glsl_type *type) \
{                                               \
   return unop(&AVAIL, OPCODE, type, type);     \
}

ir_function_signature *
builtin_builder::binop(ir_expression_operation opcode,
                       builtin_available_predicate avail,
                       const glsl_type *return_type,
                       const glsl_type *param0_type,
                       const glsl_type *param1_type)
{
   ir_variable *x = in_var(param0_type, "x");
   ir_variable *y = in_var(param1_type, "y");
   MAKE_SIG(return_type, avail, 2, x, y);
   body.emit(ret(expr(opcode, x, y)));
   return sig;
}

#define BINOP(NAME, OPCODE, AVAIL)                                      \
ir_function_signature *                                                 \
builtin_builder::_##NAME(const glsl_type *return_type,                  \
                         const glsl_type *param0_type,                  \
                         const glsl_type *param1_type)                  \
{                                                                       \
   return binop(&AVAIL, OPCODE, return_type, param0_type, param1_type); \
}

/**
 * Angle and Trigonometry Functions @{
 */

ir_function_signature *
builtin_builder::_radians(const glsl_type *type)
{
   ir_variable *degrees = in_var(type, "degrees");
   MAKE_SIG(type, always_available, 1, degrees);
   body.emit(ret(mul(degrees, imm(0.0174532925f))));
   return sig;
}

ir_function_signature *
builtin_builder::_degrees(const glsl_type *type)
{
   ir_variable *radians = in_var(type, "radians");
   MAKE_SIG(type, always_available, 1, radians);
   body.emit(ret(mul(radians, imm(57.29578f))));
   return sig;
}

UNOP(sin, ir_unop_sin, always_available)
UNOP(cos, ir_unop_cos, always_available)

ir_function_signature *
builtin_builder::_tan(const glsl_type *type)
{
   ir_variable *theta = in_var(type, "theta");
   MAKE_SIG(type, always_available, 1, theta);
   body.emit(ret(div(sin(theta), cos(theta))));
   return sig;
}

ir_expression *
builtin_builder::asin_expr(ir_variable *x)
{
   return mul(sign(x),
              sub(imm(M_PI_2f),
                  mul(sqrt(sub(imm(1.0f), abs(x))),
                      add(imm(M_PI_2f),
                          mul(abs(x),
                              add(imm(M_PI_4f - 1.0f),
                                  mul(abs(x),
                                      add(imm(0.086566724f),
                                          mul(abs(x), imm(-0.03102955f))))))))));
}

ir_call *
builtin_builder::call(ir_function *f, ir_variable *ret, exec_list params)
{
   exec_list actual_params;

   foreach_in_list(ir_variable, var, &params) {
      actual_params.push_tail(var_ref(var));
   }

   ir_function_signature *sig =
      f->exact_matching_signature(NULL, &actual_params);
   if (!sig)
      return NULL;

   ir_dereference_variable *deref =
      (sig->return_type->is_void() ? NULL : var_ref(ret));

   return new(mem_ctx) ir_call(sig, deref, &actual_params);
}

ir_function_signature *
builtin_builder::_asin(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, always_available, 1, x);

   body.emit(ret(asin_expr(x)));

   return sig;
}

ir_function_signature *
builtin_builder::_acos(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, always_available, 1, x);

   body.emit(ret(sub(imm(M_PI_2f), asin_expr(x))));

   return sig;
}

ir_function_signature *
builtin_builder::_atan2(const glsl_type *type)
{
   ir_variable *vec_y = in_var(type, "vec_y");
   ir_variable *vec_x = in_var(type, "vec_x");
   MAKE_SIG(type, always_available, 2, vec_y, vec_x);

   ir_variable *vec_result = body.make_temp(type, "vec_result");
   ir_variable *r = body.make_temp(glsl_type::float_type, "r");
   for (unsigned i = 0; i < type->vector_elements; i++) {
      ir_variable *y = body.make_temp(glsl_type::float_type, "y");
      ir_variable *x = body.make_temp(glsl_type::float_type, "x");
      body.emit(assign(y, swizzle(vec_y, i, 1)));
      body.emit(assign(x, swizzle(vec_x, i, 1)));

      /* If |x| >= 1.0e-8 * |y|: */
      ir_if *outer_if =
         new(mem_ctx) ir_if(greater(abs(x), mul(imm(1.0e-8f), abs(y))));

      ir_factory outer_then(&outer_if->then_instructions, mem_ctx);

      /* Then...call atan(y/x) */
      do_atan(body, glsl_type::float_type, r, div(y, x));

      /*     ...and fix it up: */
      ir_if *inner_if = new(mem_ctx) ir_if(less(x, imm(0.0f)));
      inner_if->then_instructions.push_tail(
         if_tree(gequal(y, imm(0.0f)),
                 assign(r, add(r, imm(M_PIf))),
                 assign(r, sub(r, imm(M_PIf)))));
      outer_then.emit(inner_if);

      /* Else... */
      outer_if->else_instructions.push_tail(
         assign(r, mul(sign(y), imm(M_PI_2f))));

      body.emit(outer_if);

      body.emit(assign(vec_result, r, 1 << i));
   }
   body.emit(ret(vec_result));

   return sig;
}

void
builtin_builder::do_atan(ir_factory &body, const glsl_type *type, ir_variable *res, operand y_over_x)
{
   /*
    * range-reduction, first step:
    *
    *      / y_over_x         if |y_over_x| <= 1.0;
    * x = <
    *      \ 1.0 / y_over_x   otherwise
    */
   ir_variable *x = body.make_temp(type, "atan_x");
   body.emit(assign(x, div(min2(abs(y_over_x),
                                imm(1.0f)),
                           max2(abs(y_over_x),
                                imm(1.0f)))));

   /*
    * approximate atan by evaluating polynomial:
    *
    * x   * 0.9999793128310355 - x^3  * 0.3326756418091246 +
    * x^5 * 0.1938924977115610 - x^7  * 0.1173503194786851 +
    * x^9 * 0.0536813784310406 - x^11 * 0.0121323213173444
    */
   ir_variable *tmp = body.make_temp(type, "atan_tmp");
   body.emit(assign(tmp, mul(x, x)));
   body.emit(assign(tmp, mul(add(mul(sub(mul(add(mul(sub(mul(add(mul(imm(-0.0121323213173444f),
                                                                     tmp),
                                                                 imm(0.0536813784310406f)),
                                                             tmp),
                                                         imm(0.1173503194786851f)),
                                                     tmp),
                                                 imm(0.1938924977115610f)),
                                             tmp),
                                         imm(0.3326756418091246f)),
                                     tmp),
                                 imm(0.9999793128310355f)),
                             x)));

   /* range-reduction fixup */
   body.emit(assign(tmp, add(tmp,
                             mul(b2f(greater(abs(y_over_x),
                                          imm(1.0f, type->components()))),
                                  add(mul(tmp,
                                          imm(-2.0f)),
                                      imm(M_PI_2f))))));

   /* sign fixup */
   body.emit(assign(res, mul(tmp, sign(y_over_x))));
}

ir_function_signature *
builtin_builder::_atan(const glsl_type *type)
{
   ir_variable *y_over_x = in_var(type, "y_over_x");
   MAKE_SIG(type, always_available, 1, y_over_x);

   ir_variable *tmp = body.make_temp(type, "tmp");
   do_atan(body, type, tmp, y_over_x);
   body.emit(ret(tmp));

   return sig;
}

ir_function_signature *
builtin_builder::_sinh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   /* 0.5 * (e^x - e^(-x)) */
   body.emit(ret(mul(imm(0.5f), sub(exp(x), exp(neg(x))))));

   return sig;
}

ir_function_signature *
builtin_builder::_cosh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   /* 0.5 * (e^x + e^(-x)) */
   body.emit(ret(mul(imm(0.5f), add(exp(x), exp(neg(x))))));

   return sig;
}

ir_function_signature *
builtin_builder::_tanh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   /* (e^x - e^(-x)) / (e^x + e^(-x)) */
   body.emit(ret(div(sub(exp(x), exp(neg(x))),
                     add(exp(x), exp(neg(x))))));

   return sig;
}

ir_function_signature *
builtin_builder::_asinh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   body.emit(ret(mul(sign(x), log(add(abs(x), sqrt(add(mul(x, x),
                                                       imm(1.0f))))))));
   return sig;
}

ir_function_signature *
builtin_builder::_acosh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   body.emit(ret(log(add(x, sqrt(sub(mul(x, x), imm(1.0f)))))));
   return sig;
}

ir_function_signature *
builtin_builder::_atanh(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, v130, 1, x);

   body.emit(ret(mul(imm(0.5f), log(div(add(imm(1.0f), x),
                                        sub(imm(1.0f), x))))));
   return sig;
}
/** @} */

/**
 * Exponential Functions @{
 */

ir_function_signature *
builtin_builder::_pow(const glsl_type *type)
{
   return binop(ir_binop_pow, always_available, type, type, type);
}

UNOP(exp,         ir_unop_exp,  always_available)
UNOP(log,         ir_unop_log,  always_available)
UNOP(exp2,        ir_unop_exp2, always_available)
UNOP(log2,        ir_unop_log2, always_available)
UNOP(sqrt,        ir_unop_sqrt, always_available)
UNOP(inversesqrt, ir_unop_rsq,  always_available)

/** @} */

UNOP(abs,       ir_unop_abs,        always_available)
UNOP(sign,      ir_unop_sign,       always_available)
UNOP(floor,     ir_unop_floor,      always_available)
UNOP(trunc,     ir_unop_trunc,      v130)
UNOP(round,     ir_unop_round_even, always_available)
UNOP(roundEven, ir_unop_round_even, always_available)
UNOP(ceil,      ir_unop_ceil,       always_available)
UNOP(fract,     ir_unop_fract,      always_available)

ir_function_signature *
builtin_builder::_mod(const glsl_type *x_type, const glsl_type *y_type)
{
   return binop(ir_binop_mod, always_available, x_type, x_type, y_type);
}

ir_function_signature *
builtin_builder::_modf(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *i = out_var(type, "i");
   MAKE_SIG(type, v130, 2, x, i);

   ir_variable *t = body.make_temp(type, "t");
   body.emit(assign(t, expr(ir_unop_trunc, x)));
   body.emit(assign(i, t));
   body.emit(ret(sub(x, t)));

   return sig;
}

ir_function_signature *
builtin_builder::_min(builtin_available_predicate avail,
                      const glsl_type *x_type, const glsl_type *y_type)
{
   return binop(ir_binop_min, avail, x_type, x_type, y_type);
}

ir_function_signature *
builtin_builder::_max(builtin_available_predicate avail,
                      const glsl_type *x_type, const glsl_type *y_type)
{
   return binop(ir_binop_max, avail, x_type, x_type, y_type);
}

ir_function_signature *
builtin_builder::_clamp(builtin_available_predicate avail,
                        const glsl_type *val_type, const glsl_type *bound_type)
{
   ir_variable *x = in_var(val_type, "x");
   ir_variable *minVal = in_var(bound_type, "minVal");
   ir_variable *maxVal = in_var(bound_type, "maxVal");
   MAKE_SIG(val_type, avail, 3, x, minVal, maxVal);

   body.emit(ret(clamp(x, minVal, maxVal)));

   return sig;
}

ir_function_signature *
builtin_builder::_mix_lrp(const glsl_type *val_type, const glsl_type *blend_type)
{
   ir_variable *x = in_var(val_type, "x");
   ir_variable *y = in_var(val_type, "y");
   ir_variable *a = in_var(blend_type, "a");
   MAKE_SIG(val_type, always_available, 3, x, y, a);

   body.emit(ret(lrp(x, y, a)));

   return sig;
}

ir_function_signature *
builtin_builder::_mix_sel(builtin_available_predicate avail,
                          const glsl_type *val_type,
                          const glsl_type *blend_type)
{
   ir_variable *x = in_var(val_type, "x");
   ir_variable *y = in_var(val_type, "y");
   ir_variable *a = in_var(blend_type, "a");
   MAKE_SIG(val_type, avail, 3, x, y, a);

   /* csel matches the ternary operator in that a selector of true choses the
    * first argument. This differs from mix(x, y, false) which choses the
    * second argument (to remain consistent with the interpolating version of
    * mix() which takes a blend factor from 0.0 to 1.0 where 0.0 is only x.
    *
    * To handle the behavior mismatch, reverse the x and y arguments.
    */
   body.emit(ret(csel(a, y, x)));

   return sig;
}

ir_function_signature *
builtin_builder::_step(const glsl_type *edge_type, const glsl_type *x_type)
{
   ir_variable *edge = in_var(edge_type, "edge");
   ir_variable *x = in_var(x_type, "x");
   MAKE_SIG(x_type, always_available, 2, edge, x);

   ir_variable *t = body.make_temp(x_type, "t");
   if (x_type->vector_elements == 1) {
      /* Both are floats */
      body.emit(assign(t, b2f(gequal(x, edge))));
   } else if (edge_type->vector_elements == 1) {
      /* x is a vector but edge is a float */
      for (unsigned i = 0; i < x_type->vector_elements; i++) {
         body.emit(assign(t, b2f(gequal(swizzle(x, i, 1), edge)), 1 << i));
      }
   } else {
      /* Both are vectors */
      for (unsigned i = 0; i < x_type->vector_elements; i++) {
         body.emit(assign(t, b2f(gequal(swizzle(x, i, 1), swizzle(edge, i, 1))),
                          1 << i));
      }
   }
   body.emit(ret(t));

   return sig;
}

ir_function_signature *
builtin_builder::_smoothstep(const glsl_type *edge_type, const glsl_type *x_type)
{
   ir_variable *edge0 = in_var(edge_type, "edge0");
   ir_variable *edge1 = in_var(edge_type, "edge1");
   ir_variable *x = in_var(x_type, "x");
   MAKE_SIG(x_type, always_available, 3, edge0, edge1, x);

   /* From the GLSL 1.10 specification:
    *
    *    genType t;
    *    t = clamp((x - edge0) / (edge1 - edge0), 0, 1);
    *    return t * t * (3 - 2 * t);
    */

   ir_variable *t = body.make_temp(x_type, "t");
   body.emit(assign(t, clamp(div(sub(x, edge0), sub(edge1, edge0)),
                             imm(0.0f), imm(1.0f))));

   body.emit(ret(mul(t, mul(t, sub(imm(3.0f), mul(imm(2.0f), t))))));

   return sig;
}

ir_function_signature *
builtin_builder::_isnan(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::bvec(type->vector_elements), v130, 1, x);

   body.emit(ret(nequal(x, x)));

   return sig;
}

ir_function_signature *
builtin_builder::_isinf(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::bvec(type->vector_elements), v130, 1, x);

   ir_constant_data infinities;
   for (unsigned i = 0; i < type->vector_elements; i++) {
      infinities.f[i] = std::numeric_limits<float>::infinity();
   }

   body.emit(ret(equal(abs(x), imm(type, infinities))));

   return sig;
}

ir_function_signature *
builtin_builder::_floatBitsToInt(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::ivec(type->vector_elements), shader_bit_encoding, 1, x);
   body.emit(ret(bitcast_f2i(x)));
   return sig;
}

ir_function_signature *
builtin_builder::_floatBitsToUint(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::uvec(type->vector_elements), shader_bit_encoding, 1, x);
   body.emit(ret(bitcast_f2u(x)));
   return sig;
}

ir_function_signature *
builtin_builder::_intBitsToFloat(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::vec(type->vector_elements), shader_bit_encoding, 1, x);
   body.emit(ret(bitcast_i2f(x)));
   return sig;
}

ir_function_signature *
builtin_builder::_uintBitsToFloat(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::vec(type->vector_elements), shader_bit_encoding, 1, x);
   body.emit(ret(bitcast_u2f(x)));
   return sig;
}

ir_function_signature *
builtin_builder::_packUnorm2x16(builtin_available_predicate avail)
{
   ir_variable *v = in_var(glsl_type::vec2_type, "v");
   MAKE_SIG(glsl_type::uint_type, avail, 1, v);
   body.emit(ret(expr(ir_unop_pack_unorm_2x16, v)));
   return sig;
}

ir_function_signature *
builtin_builder::_packSnorm2x16(builtin_available_predicate avail)
{
   ir_variable *v = in_var(glsl_type::vec2_type, "v");
   MAKE_SIG(glsl_type::uint_type, avail, 1, v);
   body.emit(ret(expr(ir_unop_pack_snorm_2x16, v)));
   return sig;
}

ir_function_signature *
builtin_builder::_packUnorm4x8(builtin_available_predicate avail)
{
   ir_variable *v = in_var(glsl_type::vec4_type, "v");
   MAKE_SIG(glsl_type::uint_type, avail, 1, v);
   body.emit(ret(expr(ir_unop_pack_unorm_4x8, v)));
   return sig;
}

ir_function_signature *
builtin_builder::_packSnorm4x8(builtin_available_predicate avail)
{
   ir_variable *v = in_var(glsl_type::vec4_type, "v");
   MAKE_SIG(glsl_type::uint_type, avail, 1, v);
   body.emit(ret(expr(ir_unop_pack_snorm_4x8, v)));
   return sig;
}

ir_function_signature *
builtin_builder::_unpackUnorm2x16(builtin_available_predicate avail)
{
   ir_variable *p = in_var(glsl_type::uint_type, "p");
   MAKE_SIG(glsl_type::vec2_type, avail, 1, p);
   body.emit(ret(expr(ir_unop_unpack_unorm_2x16, p)));
   return sig;
}

ir_function_signature *
builtin_builder::_unpackSnorm2x16(builtin_available_predicate avail)
{
   ir_variable *p = in_var(glsl_type::uint_type, "p");
   MAKE_SIG(glsl_type::vec2_type, avail, 1, p);
   body.emit(ret(expr(ir_unop_unpack_snorm_2x16, p)));
   return sig;
}


ir_function_signature *
builtin_builder::_unpackUnorm4x8(builtin_available_predicate avail)
{
   ir_variable *p = in_var(glsl_type::uint_type, "p");
   MAKE_SIG(glsl_type::vec4_type, avail, 1, p);
   body.emit(ret(expr(ir_unop_unpack_unorm_4x8, p)));
   return sig;
}

ir_function_signature *
builtin_builder::_unpackSnorm4x8(builtin_available_predicate avail)
{
   ir_variable *p = in_var(glsl_type::uint_type, "p");
   MAKE_SIG(glsl_type::vec4_type, avail, 1, p);
   body.emit(ret(expr(ir_unop_unpack_snorm_4x8, p)));
   return sig;
}

ir_function_signature *
builtin_builder::_packHalf2x16(builtin_available_predicate avail)
{
   ir_variable *v = in_var(glsl_type::vec2_type, "v");
   MAKE_SIG(glsl_type::uint_type, avail, 1, v);
   body.emit(ret(expr(ir_unop_pack_half_2x16, v)));
   return sig;
}

ir_function_signature *
builtin_builder::_unpackHalf2x16(builtin_available_predicate avail)
{
   ir_variable *p = in_var(glsl_type::uint_type, "p");
   MAKE_SIG(glsl_type::vec2_type, avail, 1, p);
   body.emit(ret(expr(ir_unop_unpack_half_2x16, p)));
   return sig;
}

ir_function_signature *
builtin_builder::_length(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(glsl_type::float_type, always_available, 1, x);

   body.emit(ret(sqrt(dot(x, x))));

   return sig;
}

ir_function_signature *
builtin_builder::_distance(const glsl_type *type)
{
   ir_variable *p0 = in_var(type, "p0");
   ir_variable *p1 = in_var(type, "p1");
   MAKE_SIG(glsl_type::float_type, always_available, 2, p0, p1);

   if (type->vector_elements == 1) {
      body.emit(ret(abs(sub(p0, p1))));
   } else {
      ir_variable *p = body.make_temp(type, "p");
      body.emit(assign(p, sub(p0, p1)));
      body.emit(ret(sqrt(dot(p, p))));
   }

   return sig;
}

ir_function_signature *
builtin_builder::_dot(const glsl_type *type)
{
   if (type->vector_elements == 1)
      return binop(ir_binop_mul, always_available, type, type, type);

   return binop(ir_binop_dot, always_available,
                glsl_type::float_type, type, type);
}

ir_function_signature *
builtin_builder::_cross(const glsl_type *type)
{
   ir_variable *a = in_var(type, "a");
   ir_variable *b = in_var(type, "b");
   MAKE_SIG(type, always_available, 2, a, b);

   int yzx = MAKE_SWIZZLE4(SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_X, 0);
   int zxy = MAKE_SWIZZLE4(SWIZZLE_Z, SWIZZLE_X, SWIZZLE_Y, 0);

   body.emit(ret(sub(mul(swizzle(a, yzx, 3), swizzle(b, zxy, 3)),
                     mul(swizzle(a, zxy, 3), swizzle(b, yzx, 3)))));

   return sig;
}

ir_function_signature *
builtin_builder::_normalize(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   MAKE_SIG(type, always_available, 1, x);

   if (type->vector_elements == 1) {
      body.emit(ret(sign(x)));
   } else {
      body.emit(ret(expr(ir_unop_normalize, x)));
   }

   return sig;
}

ir_function_signature *
builtin_builder::_ftransform()
{
   MAKE_SIG(glsl_type::vec4_type, compatibility_vs_only, 0);

   body.emit(ret(new(mem_ctx) ir_expression(ir_binop_mul,
      glsl_type::vec4_type,
      var_ref(gl_ModelViewProjectionMatrix),
      var_ref(gl_Vertex))));

   /* FINISHME: Once the ir_expression() constructor handles type inference
    *           for matrix operations, we can simplify this to:
    *
    *    body.emit(ret(mul(gl_ModelViewProjectionMatrix, gl_Vertex)));
    */
   return sig;
}

ir_function_signature *
builtin_builder::_faceforward(const glsl_type *type)
{
   ir_variable *N = in_var(type, "N");
   ir_variable *I = in_var(type, "I");
   ir_variable *Nref = in_var(type, "Nref");
   MAKE_SIG(type, always_available, 3, N, I, Nref);

   body.emit(if_tree(less(dot(Nref, I), imm(0.0f)),
                     ret(N), ret(neg(N))));

   return sig;
}

ir_function_signature *
builtin_builder::_reflect(const glsl_type *type)
{
   ir_variable *I = in_var(type, "I");
   ir_variable *N = in_var(type, "N");
   MAKE_SIG(type, always_available, 2, I, N);

   /* I - 2 * dot(N, I) * N */
   body.emit(ret(sub(I, mul(imm(2.0f), mul(dot(N, I), N)))));

   return sig;
}

ir_function_signature *
builtin_builder::_refract(const glsl_type *type)
{
   ir_variable *I = in_var(type, "I");
   ir_variable *N = in_var(type, "N");
   ir_variable *eta = in_var(glsl_type::float_type, "eta");
   MAKE_SIG(type, always_available, 3, I, N, eta);

   ir_variable *n_dot_i = body.make_temp(glsl_type::float_type, "n_dot_i");
   body.emit(assign(n_dot_i, dot(N, I)));

   /* From the GLSL 1.10 specification:
    * k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I))
    * if (k < 0.0)
    *    return genType(0.0)
    * else
    *    return eta * I - (eta * dot(N, I) + sqrt(k)) * N
    */
   ir_variable *k = body.make_temp(glsl_type::float_type, "k");
   body.emit(assign(k, sub(imm(1.0f),
                           mul(eta, mul(eta, sub(imm(1.0f),
                                                 mul(n_dot_i, n_dot_i)))))));
   body.emit(if_tree(less(k, imm(0.0f)),
                     ret(ir_constant::zero(mem_ctx, type)),
                     ret(sub(mul(eta, I),
                             mul(add(mul(eta, n_dot_i), sqrt(k)), N)))));

   return sig;
}

ir_function_signature *
builtin_builder::_matrixCompMult(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   MAKE_SIG(type, always_available, 2, x, y);

   ir_variable *z = body.make_temp(type, "z");
   for (unsigned i = 0; i < type->matrix_columns; i++) {
      body.emit(assign(array_ref(z, i), mul(array_ref(x, i), array_ref(y, i))));
   }
   body.emit(ret(z));

   return sig;
}

ir_function_signature *
builtin_builder::_outerProduct(const glsl_type *type)
{
   ir_variable *c = in_var(glsl_type::vec(type->vector_elements), "c");
   ir_variable *r = in_var(glsl_type::vec(type->matrix_columns), "r");
   MAKE_SIG(type, v120, 2, c, r);

   ir_variable *m = body.make_temp(type, "m");
   for (unsigned i = 0; i < type->matrix_columns; i++) {
      body.emit(assign(array_ref(m, i), mul(c, swizzle(r, i, 1))));
   }
   body.emit(ret(m));

   return sig;
}

ir_function_signature *
builtin_builder::_transpose(const glsl_type *orig_type)
{
   const glsl_type *transpose_type =
      glsl_type::get_instance(GLSL_TYPE_FLOAT,
                              orig_type->matrix_columns,
                              orig_type->vector_elements);

   ir_variable *m = in_var(orig_type, "m");
   MAKE_SIG(transpose_type, v120, 1, m);

   ir_variable *t = body.make_temp(transpose_type, "t");
   for (unsigned i = 0; i < orig_type->matrix_columns; i++) {
      for (unsigned j = 0; j < orig_type->vector_elements; j++) {
         body.emit(assign(array_ref(t, j),
                          matrix_elt(m, i, j),
                          1 << i));
      }
   }
   body.emit(ret(t));

   return sig;
}

ir_function_signature *
builtin_builder::_determinant_mat2()
{
   ir_variable *m = in_var(glsl_type::mat2_type, "m");
   MAKE_SIG(glsl_type::float_type, v120, 1, m);

   body.emit(ret(sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 1, 1)),
                     mul(matrix_elt(m, 1, 0), matrix_elt(m, 0, 1)))));

   return sig;
}

ir_function_signature *
builtin_builder::_determinant_mat3()
{
   ir_variable *m = in_var(glsl_type::mat3_type, "m");
   MAKE_SIG(glsl_type::float_type, v120, 1, m);

   ir_expression *f1 =
      sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 2)),
          mul(matrix_elt(m, 1, 2), matrix_elt(m, 2, 1)));

   ir_expression *f2 =
      sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 2)),
          mul(matrix_elt(m, 1, 2), matrix_elt(m, 2, 0)));

   ir_expression *f3 =
      sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 1)),
          mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 0)));

   body.emit(ret(add(sub(mul(matrix_elt(m, 0, 0), f1),
                         mul(matrix_elt(m, 0, 1), f2)),
                     mul(matrix_elt(m, 0, 2), f3))));

   return sig;
}

ir_function_signature *
builtin_builder::_determinant_mat4()
{
   ir_variable *m = in_var(glsl_type::mat4_type, "m");
   MAKE_SIG(glsl_type::float_type, v120, 1, m);

   ir_variable *SubFactor00 = body.make_temp(glsl_type::float_type, "SubFactor00");
   ir_variable *SubFactor01 = body.make_temp(glsl_type::float_type, "SubFactor01");
   ir_variable *SubFactor02 = body.make_temp(glsl_type::float_type, "SubFactor02");
   ir_variable *SubFactor03 = body.make_temp(glsl_type::float_type, "SubFactor03");
   ir_variable *SubFactor04 = body.make_temp(glsl_type::float_type, "SubFactor04");
   ir_variable *SubFactor05 = body.make_temp(glsl_type::float_type, "SubFactor05");
   ir_variable *SubFactor06 = body.make_temp(glsl_type::float_type, "SubFactor06");
   ir_variable *SubFactor07 = body.make_temp(glsl_type::float_type, "SubFactor07");
   ir_variable *SubFactor08 = body.make_temp(glsl_type::float_type, "SubFactor08");
   ir_variable *SubFactor09 = body.make_temp(glsl_type::float_type, "SubFactor09");
   ir_variable *SubFactor10 = body.make_temp(glsl_type::float_type, "SubFactor10");
   ir_variable *SubFactor11 = body.make_temp(glsl_type::float_type, "SubFactor11");
   ir_variable *SubFactor12 = body.make_temp(glsl_type::float_type, "SubFactor12");
   ir_variable *SubFactor13 = body.make_temp(glsl_type::float_type, "SubFactor13");
   ir_variable *SubFactor14 = body.make_temp(glsl_type::float_type, "SubFactor14");
   ir_variable *SubFactor15 = body.make_temp(glsl_type::float_type, "SubFactor15");
   ir_variable *SubFactor16 = body.make_temp(glsl_type::float_type, "SubFactor16");
   ir_variable *SubFactor17 = body.make_temp(glsl_type::float_type, "SubFactor17");
   ir_variable *SubFactor18 = body.make_temp(glsl_type::float_type, "SubFactor18");

   body.emit(assign(SubFactor00, sub(mul(matrix_elt(m, 2, 2), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 2), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor01, sub(mul(matrix_elt(m, 2, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor02, sub(mul(matrix_elt(m, 2, 1), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 2, 2)))));
   body.emit(assign(SubFactor03, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor04, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 2)))));
   body.emit(assign(SubFactor05, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 1)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 1)))));
   body.emit(assign(SubFactor06, sub(mul(matrix_elt(m, 1, 2), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 2), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor07, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor08, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor09, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor10, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor11, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor12, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 1)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 1)))));
   body.emit(assign(SubFactor13, sub(mul(matrix_elt(m, 1, 2), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 2), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor14, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor15, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 2)), mul(matrix_elt(m, 2, 1), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor16, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor17, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 2)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor18, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 1)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 1)))));

   ir_variable *adj_0 = body.make_temp(glsl_type::vec4_type, "adj_0");

   body.emit(assign(adj_0,
                    add(sub(mul(matrix_elt(m, 1, 1), SubFactor00),
                            mul(matrix_elt(m, 1, 2), SubFactor01)),
                        mul(matrix_elt(m, 1, 3), SubFactor02)),
                    WRITEMASK_X));
   body.emit(assign(adj_0, neg(
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor00),
                            mul(matrix_elt(m, 1, 2), SubFactor03)),
                        mul(matrix_elt(m, 1, 3), SubFactor04))),
                    WRITEMASK_Y));
   body.emit(assign(adj_0,
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor01),
                            mul(matrix_elt(m, 1, 1), SubFactor03)),
                        mul(matrix_elt(m, 1, 3), SubFactor05)),
                    WRITEMASK_Z));
   body.emit(assign(adj_0, neg(
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor02),
                            mul(matrix_elt(m, 1, 1), SubFactor04)),
                        mul(matrix_elt(m, 1, 2), SubFactor05))),
                    WRITEMASK_W));

   body.emit(ret(dot(array_ref(m, 0), adj_0)));

   return sig;
}

ir_function_signature *
builtin_builder::_inverse_mat2()
{
   ir_variable *m = in_var(glsl_type::mat2_type, "m");
   MAKE_SIG(glsl_type::mat2_type, v120, 1, m);

   ir_variable *adj = body.make_temp(glsl_type::mat2_type, "adj");
   body.emit(assign(array_ref(adj, 0), matrix_elt(m, 1, 1), 1 << 0));
   body.emit(assign(array_ref(adj, 0), neg(matrix_elt(m, 0, 1)), 1 << 1));
   body.emit(assign(array_ref(adj, 1), neg(matrix_elt(m, 1, 0)), 1 << 0));
   body.emit(assign(array_ref(adj, 1), matrix_elt(m, 0, 0), 1 << 1));

   ir_expression *det =
      sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 1, 1)),
          mul(matrix_elt(m, 1, 0), matrix_elt(m, 0, 1)));

   body.emit(ret(div(adj, det)));
   return sig;
}

ir_function_signature *
builtin_builder::_inverse_mat3()
{
   ir_variable *m = in_var(glsl_type::mat3_type, "m");
   MAKE_SIG(glsl_type::mat3_type, v120, 1, m);

   ir_variable *f11_22_21_12 = body.make_temp(glsl_type::float_type, "f11_22_21_12");
   ir_variable *f10_22_20_12 = body.make_temp(glsl_type::float_type, "f10_22_20_12");
   ir_variable *f10_21_20_11 = body.make_temp(glsl_type::float_type, "f10_21_20_11");

   body.emit(assign(f11_22_21_12,
                    sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 2)),
                        mul(matrix_elt(m, 2, 1), matrix_elt(m, 1, 2)))));
   body.emit(assign(f10_22_20_12,
                    sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 2)),
                        mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 2)))));
   body.emit(assign(f10_21_20_11,
                    sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 1)),
                        mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 1)))));

   ir_variable *adj = body.make_temp(glsl_type::mat3_type, "adj");
   body.emit(assign(array_ref(adj, 0), f11_22_21_12, WRITEMASK_X));
   body.emit(assign(array_ref(adj, 1), neg(f10_22_20_12), WRITEMASK_X));
   body.emit(assign(array_ref(adj, 2), f10_21_20_11, WRITEMASK_X));

   body.emit(assign(array_ref(adj, 0), neg(
                    sub(mul(matrix_elt(m, 0, 1), matrix_elt(m, 2, 2)),
                        mul(matrix_elt(m, 2, 1), matrix_elt(m, 0, 2)))),
                    WRITEMASK_Y));
   body.emit(assign(array_ref(adj, 1),
                    sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 2, 2)),
                        mul(matrix_elt(m, 2, 0), matrix_elt(m, 0, 2))),
                    WRITEMASK_Y));
   body.emit(assign(array_ref(adj, 2), neg(
                    sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 2, 1)),
                        mul(matrix_elt(m, 2, 0), matrix_elt(m, 0, 1)))),
                    WRITEMASK_Y));

   body.emit(assign(array_ref(adj, 0),
                    sub(mul(matrix_elt(m, 0, 1), matrix_elt(m, 1, 2)),
                        mul(matrix_elt(m, 1, 1), matrix_elt(m, 0, 2))),
                    WRITEMASK_Z));
   body.emit(assign(array_ref(adj, 1), neg(
                    sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 1, 2)),
                        mul(matrix_elt(m, 1, 0), matrix_elt(m, 0, 2)))),
                    WRITEMASK_Z));
   body.emit(assign(array_ref(adj, 2),
                    sub(mul(matrix_elt(m, 0, 0), matrix_elt(m, 1, 1)),
                        mul(matrix_elt(m, 1, 0), matrix_elt(m, 0, 1))),
                    WRITEMASK_Z));

   ir_expression *det =
      add(sub(mul(matrix_elt(m, 0, 0), f11_22_21_12),
              mul(matrix_elt(m, 0, 1), f10_22_20_12)),
          mul(matrix_elt(m, 0, 2), f10_21_20_11));

   body.emit(ret(div(adj, det)));

   return sig;
}

ir_function_signature *
builtin_builder::_inverse_mat4()
{
   ir_variable *m = in_var(glsl_type::mat4_type, "m");
   MAKE_SIG(glsl_type::mat4_type, v120, 1, m);

   ir_variable *SubFactor00 = body.make_temp(glsl_type::float_type, "SubFactor00");
   ir_variable *SubFactor01 = body.make_temp(glsl_type::float_type, "SubFactor01");
   ir_variable *SubFactor02 = body.make_temp(glsl_type::float_type, "SubFactor02");
   ir_variable *SubFactor03 = body.make_temp(glsl_type::float_type, "SubFactor03");
   ir_variable *SubFactor04 = body.make_temp(glsl_type::float_type, "SubFactor04");
   ir_variable *SubFactor05 = body.make_temp(glsl_type::float_type, "SubFactor05");
   ir_variable *SubFactor06 = body.make_temp(glsl_type::float_type, "SubFactor06");
   ir_variable *SubFactor07 = body.make_temp(glsl_type::float_type, "SubFactor07");
   ir_variable *SubFactor08 = body.make_temp(glsl_type::float_type, "SubFactor08");
   ir_variable *SubFactor09 = body.make_temp(glsl_type::float_type, "SubFactor09");
   ir_variable *SubFactor10 = body.make_temp(glsl_type::float_type, "SubFactor10");
   ir_variable *SubFactor11 = body.make_temp(glsl_type::float_type, "SubFactor11");
   ir_variable *SubFactor12 = body.make_temp(glsl_type::float_type, "SubFactor12");
   ir_variable *SubFactor13 = body.make_temp(glsl_type::float_type, "SubFactor13");
   ir_variable *SubFactor14 = body.make_temp(glsl_type::float_type, "SubFactor14");
   ir_variable *SubFactor15 = body.make_temp(glsl_type::float_type, "SubFactor15");
   ir_variable *SubFactor16 = body.make_temp(glsl_type::float_type, "SubFactor16");
   ir_variable *SubFactor17 = body.make_temp(glsl_type::float_type, "SubFactor17");
   ir_variable *SubFactor18 = body.make_temp(glsl_type::float_type, "SubFactor18");

   body.emit(assign(SubFactor00, sub(mul(matrix_elt(m, 2, 2), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 2), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor01, sub(mul(matrix_elt(m, 2, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor02, sub(mul(matrix_elt(m, 2, 1), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 2, 2)))));
   body.emit(assign(SubFactor03, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 3)))));
   body.emit(assign(SubFactor04, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 2)))));
   body.emit(assign(SubFactor05, sub(mul(matrix_elt(m, 2, 0), matrix_elt(m, 3, 1)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 2, 1)))));
   body.emit(assign(SubFactor06, sub(mul(matrix_elt(m, 1, 2), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 2), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor07, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor08, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor09, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor10, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 2)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor11, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 3, 3)), mul(matrix_elt(m, 3, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor12, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 3, 1)), mul(matrix_elt(m, 3, 0), matrix_elt(m, 1, 1)))));
   body.emit(assign(SubFactor13, sub(mul(matrix_elt(m, 1, 2), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 2), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor14, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 1), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor15, sub(mul(matrix_elt(m, 1, 1), matrix_elt(m, 2, 2)), mul(matrix_elt(m, 2, 1), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor16, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 3)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 3)))));
   body.emit(assign(SubFactor17, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 2)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 2)))));
   body.emit(assign(SubFactor18, sub(mul(matrix_elt(m, 1, 0), matrix_elt(m, 2, 1)), mul(matrix_elt(m, 2, 0), matrix_elt(m, 1, 1)))));

   ir_variable *adj = body.make_temp(glsl_type::mat4_type, "adj");
   body.emit(assign(array_ref(adj, 0),
                    add(sub(mul(matrix_elt(m, 1, 1), SubFactor00),
                            mul(matrix_elt(m, 1, 2), SubFactor01)),
                        mul(matrix_elt(m, 1, 3), SubFactor02)),
                    WRITEMASK_X));
   body.emit(assign(array_ref(adj, 1), neg(
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor00),
                            mul(matrix_elt(m, 1, 2), SubFactor03)),
                        mul(matrix_elt(m, 1, 3), SubFactor04))),
                    WRITEMASK_X));
   body.emit(assign(array_ref(adj, 2),
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor01),
                            mul(matrix_elt(m, 1, 1), SubFactor03)),
                        mul(matrix_elt(m, 1, 3), SubFactor05)),
                    WRITEMASK_X));
   body.emit(assign(array_ref(adj, 3), neg(
                    add(sub(mul(matrix_elt(m, 1, 0), SubFactor02),
                            mul(matrix_elt(m, 1, 1), SubFactor04)),
                        mul(matrix_elt(m, 1, 2), SubFactor05))),
                    WRITEMASK_X));

   body.emit(assign(array_ref(adj, 0), neg(
                    add(sub(mul(matrix_elt(m, 0, 1), SubFactor00),
                            mul(matrix_elt(m, 0, 2), SubFactor01)),
                        mul(matrix_elt(m, 0, 3), SubFactor02))),
                    WRITEMASK_Y));
   body.emit(assign(array_ref(adj, 1),
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor00),
                            mul(matrix_elt(m, 0, 2), SubFactor03)),
                        mul(matrix_elt(m, 0, 3), SubFactor04)),
                    WRITEMASK_Y));
   body.emit(assign(array_ref(adj, 2), neg(
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor01),
                            mul(matrix_elt(m, 0, 1), SubFactor03)),
                        mul(matrix_elt(m, 0, 3), SubFactor05))),
                    WRITEMASK_Y));
   body.emit(assign(array_ref(adj, 3),
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor02),
                            mul(matrix_elt(m, 0, 1), SubFactor04)),
                        mul(matrix_elt(m, 0, 2), SubFactor05)),
                    WRITEMASK_Y));

   body.emit(assign(array_ref(adj, 0),
                    add(sub(mul(matrix_elt(m, 0, 1), SubFactor06),
                            mul(matrix_elt(m, 0, 2), SubFactor07)),
                        mul(matrix_elt(m, 0, 3), SubFactor08)),
                    WRITEMASK_Z));
   body.emit(assign(array_ref(adj, 1), neg(
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor06),
                            mul(matrix_elt(m, 0, 2), SubFactor09)),
                        mul(matrix_elt(m, 0, 3), SubFactor10))),
                    WRITEMASK_Z));
   body.emit(assign(array_ref(adj, 2),
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor11),
                            mul(matrix_elt(m, 0, 1), SubFactor09)),
                        mul(matrix_elt(m, 0, 3), SubFactor12)),
                    WRITEMASK_Z));
   body.emit(assign(array_ref(adj, 3), neg(
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor08),
                            mul(matrix_elt(m, 0, 1), SubFactor10)),
                        mul(matrix_elt(m, 0, 2), SubFactor12))),
                    WRITEMASK_Z));

   body.emit(assign(array_ref(adj, 0), neg(
                    add(sub(mul(matrix_elt(m, 0, 1), SubFactor13),
                            mul(matrix_elt(m, 0, 2), SubFactor14)),
                        mul(matrix_elt(m, 0, 3), SubFactor15))),
                    WRITEMASK_W));
   body.emit(assign(array_ref(adj, 1),
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor13),
                            mul(matrix_elt(m, 0, 2), SubFactor16)),
                        mul(matrix_elt(m, 0, 3), SubFactor17)),
                    WRITEMASK_W));
   body.emit(assign(array_ref(adj, 2), neg(
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor14),
                            mul(matrix_elt(m, 0, 1), SubFactor16)),
                        mul(matrix_elt(m, 0, 3), SubFactor18))),
                    WRITEMASK_W));
   body.emit(assign(array_ref(adj, 3),
                    add(sub(mul(matrix_elt(m, 0, 0), SubFactor15),
                            mul(matrix_elt(m, 0, 1), SubFactor17)),
                        mul(matrix_elt(m, 0, 2), SubFactor18)),
                    WRITEMASK_W));

   ir_expression *det =
      add(mul(matrix_elt(m, 0, 0), matrix_elt(adj, 0, 0)),
          add(mul(matrix_elt(m, 0, 1), matrix_elt(adj, 1, 0)),
              add(mul(matrix_elt(m, 0, 2), matrix_elt(adj, 2, 0)),
                  mul(matrix_elt(m, 0, 3), matrix_elt(adj, 3, 0)))));

   body.emit(ret(div(adj, det)));

   return sig;
}


ir_function_signature *
builtin_builder::_lessThan(builtin_available_predicate avail,
                           const glsl_type *type)
{
   return binop(ir_binop_less, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_lessThanEqual(builtin_available_predicate avail,
                                const glsl_type *type)
{
   return binop(ir_binop_lequal, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_greaterThan(builtin_available_predicate avail,
                              const glsl_type *type)
{
   return binop(ir_binop_greater, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_greaterThanEqual(builtin_available_predicate avail,
                                   const glsl_type *type)
{
   return binop(ir_binop_gequal, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_equal(builtin_available_predicate avail,
                        const glsl_type *type)
{
   return binop(ir_binop_equal, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_notEqual(builtin_available_predicate avail,
                           const glsl_type *type)
{
   return binop(ir_binop_nequal, avail,
                glsl_type::bvec(type->vector_elements), type, type);
}

ir_function_signature *
builtin_builder::_any(const glsl_type *type)
{
   return unop(always_available, ir_unop_any, glsl_type::bool_type, type);
}

ir_function_signature *
builtin_builder::_all(const glsl_type *type)
{
   ir_variable *v = in_var(type, "v");
   MAKE_SIG(glsl_type::bool_type, always_available, 1, v);

   switch (type->vector_elements) {
   case 2:
      body.emit(ret(logic_and(swizzle_x(v), swizzle_y(v))));
      break;
   case 3:
      body.emit(ret(logic_and(logic_and(swizzle_x(v), swizzle_y(v)),
                              swizzle_z(v))));
      break;
   case 4:
      body.emit(ret(logic_and(logic_and(logic_and(swizzle_x(v), swizzle_y(v)),
                                        swizzle_z(v)),
                              swizzle_w(v))));
      break;
   }

   return sig;
}

UNOP(not, ir_unop_logic_not, always_available)

ir_function_signature *
builtin_builder::_textureSize(builtin_available_predicate avail,
                              const glsl_type *return_type,
                              const glsl_type *sampler_type)
{
   ir_variable *s = in_var(sampler_type, "sampler");
   /* The sampler always exists; add optional lod later. */
   MAKE_SIG(return_type, avail, 1, s);

   ir_texture *tex = new(mem_ctx) ir_texture(ir_txs);
   tex->set_sampler(new(mem_ctx) ir_dereference_variable(s), return_type);

   if (ir_texture::has_lod(sampler_type)) {
      ir_variable *lod = in_var(glsl_type::int_type, "lod");
      sig->parameters.push_tail(lod);
      tex->lod_info.lod = var_ref(lod);
   } else {
      tex->lod_info.lod = imm(0u);
   }

   body.emit(ret(tex));

   return sig;
}

ir_function_signature *
builtin_builder::_texture(ir_texture_opcode opcode,
                          builtin_available_predicate avail,
                          const glsl_type *return_type,
                          const glsl_type *sampler_type,
                          const glsl_type *coord_type,
                          int flags)
{
   ir_variable *s = in_var(sampler_type, "sampler");
   ir_variable *P = in_var(coord_type, "P");
   /* The sampler and coordinate always exist; add optional parameters later. */
   MAKE_SIG(return_type, avail, 2, s, P);

   ir_texture *tex = new(mem_ctx) ir_texture(opcode);
   tex->set_sampler(var_ref(s), return_type);

   const int coord_size = sampler_type->coordinate_components();

   // removed for glsl optimizer
   //if (coord_size == coord_type->vector_elements) {
      tex->coordinate = var_ref(P);
   //} else {
   //   /* The incoming coordinate also has the projector or shadow comparitor,
   //    * so we need to swizzle those away.
   //    */
   //   tex->coordinate = swizzle_for_size(P, coord_size);
   //}

#if 0 // removed for glsl optimizer
   /* The projector is always in the last component. */
   if (flags & TEX_PROJECT)
      tex->projector = swizzle(P, coord_type->vector_elements - 1, 1);

   if (sampler_type->sampler_shadow) {
      if (opcode == ir_tg4) {
         /* gather has refz as a separate parameter, immediately after the
          * coordinate
          */
         ir_variable *refz = in_var(glsl_type::float_type, "refz");
         sig->parameters.push_tail(refz);
         tex->shadow_comparitor = var_ref(refz);
      } else {
         /* The shadow comparitor is normally in the Z component, but a few types
          * have sufficiently large coordinates that it's in W.
          */
         tex->shadow_comparitor = swizzle(P, MAX2(coord_size, SWIZZLE_Z), 1);
      }
   }
#endif // #if 0

   if (opcode == ir_txl) {
      ir_variable *lod = in_var(glsl_type::float_type, "lod");
      sig->parameters.push_tail(lod);
      tex->lod_info.lod = var_ref(lod);
   } else if (opcode == ir_txd) {
      int grad_size = coord_size - (sampler_type->sampler_array ? 1 : 0);
      ir_variable *dPdx = in_var(glsl_type::vec(grad_size), "dPdx");
      ir_variable *dPdy = in_var(glsl_type::vec(grad_size), "dPdy");
      sig->parameters.push_tail(dPdx);
      sig->parameters.push_tail(dPdy);
      tex->lod_info.grad.dPdx = var_ref(dPdx);
      tex->lod_info.grad.dPdy = var_ref(dPdy);
   }

   if (flags & (TEX_OFFSET | TEX_OFFSET_NONCONST)) {
      int offset_size = coord_size - (sampler_type->sampler_array ? 1 : 0);
      ir_variable *offset =
         new(mem_ctx) ir_variable(glsl_type::ivec(offset_size), "offset",
                                  (flags & TEX_OFFSET) ? ir_var_const_in : ir_var_function_in, glsl_precision_undefined);
      sig->parameters.push_tail(offset);
      tex->offset = var_ref(offset);
   }

   if (flags & TEX_OFFSET_ARRAY) {
      ir_variable *offsets =
         new(mem_ctx) ir_variable(glsl_type::get_array_instance(glsl_type::ivec2_type, 4),
                                  "offsets", ir_var_const_in, glsl_precision_undefined);
      sig->parameters.push_tail(offsets);
      tex->offset = var_ref(offsets);
   }

   if (opcode == ir_tg4) {
      if (flags & TEX_COMPONENT) {
         ir_variable *component =
            new(mem_ctx) ir_variable(glsl_type::int_type, "comp", ir_var_const_in, glsl_precision_undefined);
         sig->parameters.push_tail(component);
         tex->lod_info.component = var_ref(component);
      }
      else {
         tex->lod_info.component = imm(0);
      }
   }

   /* The "bias" parameter comes /after/ the "offset" parameter, which is
    * inconsistent with both textureLodOffset and textureGradOffset.
    */
   if (opcode == ir_txb) {
      ir_variable *bias = in_var(glsl_type::float_type, "bias");
      sig->parameters.push_tail(bias);
      tex->lod_info.bias = var_ref(bias);
   }

   body.emit(ret(tex));

   return sig;
}

ir_function_signature *
builtin_builder::_textureCubeArrayShadow()
{
   ir_variable *s = in_var(glsl_type::samplerCubeArrayShadow_type, "sampler");
   ir_variable *P = in_var(glsl_type::vec4_type, "P");
   ir_variable *compare = in_var(glsl_type::float_type, "compare");
   MAKE_SIG(glsl_type::float_type, texture_cube_map_array, 3, s, P, compare);

   ir_texture *tex = new(mem_ctx) ir_texture(ir_tex);
   tex->set_sampler(var_ref(s), glsl_type::float_type);

   tex->coordinate = var_ref(P);
   //tex->shadow_comparitor = var_ref(compare); //@TODO ?

   body.emit(ret(tex));

   return sig;
}

ir_function_signature *
builtin_builder::_texelFetch(builtin_available_predicate avail,
                             const glsl_type *return_type,
                             const glsl_type *sampler_type,
                             const glsl_type *coord_type,
                             const glsl_type *offset_type)
{
   ir_variable *s = in_var(sampler_type, "sampler");
   ir_variable *P = in_var(coord_type, "P");
   /* The sampler and coordinate always exist; add optional parameters later. */
   MAKE_SIG(return_type, avail, 2, s, P);

   ir_texture *tex = new(mem_ctx) ir_texture(ir_txf);
   tex->coordinate = var_ref(P);
   tex->set_sampler(var_ref(s), return_type);

   if (sampler_type->sampler_dimensionality == GLSL_SAMPLER_DIM_MS) {
      ir_variable *sample = in_var(glsl_type::int_type, "sample");
      sig->parameters.push_tail(sample);
      tex->lod_info.sample_index = var_ref(sample);
      tex->op = ir_txf_ms;
   } else if (ir_texture::has_lod(sampler_type)) {
      ir_variable *lod = in_var(glsl_type::int_type, "lod");
      sig->parameters.push_tail(lod);
      tex->lod_info.lod = var_ref(lod);
   } else {
      tex->lod_info.lod = imm(0u);
   }

   if (offset_type != NULL) {
      ir_variable *offset =
         new(mem_ctx) ir_variable(offset_type, "offset", ir_var_const_in, glsl_precision_undefined);
      sig->parameters.push_tail(offset);
      tex->offset = var_ref(offset);
   }

   body.emit(ret(tex));

   return sig;
}

ir_function_signature *
builtin_builder::_EmitVertex()
{
   MAKE_SIG(glsl_type::void_type, gs_only, 0);

   ir_rvalue *stream = new(mem_ctx) ir_constant(0, 1);
   body.emit(new(mem_ctx) ir_emit_vertex(stream));

   return sig;
}

ir_function_signature *
builtin_builder::_EmitStreamVertex(builtin_available_predicate avail,
                                   const glsl_type *stream_type)
{
   /* Section 8.12 (Geometry Shader Functions) of the GLSL 4.0 spec says:
    *
    *     "Emit the current values of output variables to the current output
    *     primitive on stream stream. The argument to stream must be a constant
    *     integral expression."
    */
   ir_variable *stream =
      new(mem_ctx) ir_variable(stream_type, "stream", ir_var_const_in, glsl_precision_undefined);

   MAKE_SIG(glsl_type::void_type, avail, 1, stream);

   body.emit(new(mem_ctx) ir_emit_vertex(var_ref(stream)));

   return sig;
}

ir_function_signature *
builtin_builder::_EndPrimitive()
{
   MAKE_SIG(glsl_type::void_type, gs_only, 0);

   ir_rvalue *stream = new(mem_ctx) ir_constant(0, 1);
   body.emit(new(mem_ctx) ir_end_primitive(stream));

   return sig;
}

ir_function_signature *
builtin_builder::_EndStreamPrimitive(builtin_available_predicate avail,
                                     const glsl_type *stream_type)
{
   /* Section 8.12 (Geometry Shader Functions) of the GLSL 4.0 spec says:
    *
    *     "Completes the current output primitive on stream stream and starts
    *     a new one. The argument to stream must be a constant integral
    *     expression."
    */
   ir_variable *stream =
      new(mem_ctx) ir_variable(stream_type, "stream", ir_var_const_in, glsl_precision_undefined);

   MAKE_SIG(glsl_type::void_type, avail, 1, stream);

   body.emit(new(mem_ctx) ir_end_primitive(var_ref(stream)));

   return sig;
}

ir_function_signature *
builtin_builder::_textureQueryLod(const glsl_type *sampler_type,
                                  const glsl_type *coord_type)
{
   ir_variable *s = in_var(sampler_type, "sampler");
   ir_variable *coord = in_var(coord_type, "coord");
   /* The sampler and coordinate always exist; add optional parameters later. */
   MAKE_SIG(glsl_type::vec2_type, texture_query_lod, 2, s, coord);

   ir_texture *tex = new(mem_ctx) ir_texture(ir_lod);
   tex->coordinate = var_ref(coord);
   tex->set_sampler(var_ref(s), glsl_type::vec2_type);

   body.emit(ret(tex));

   return sig;
}

ir_function_signature *
builtin_builder::_textureQueryLevels(const glsl_type *sampler_type)
{
   ir_variable *s = in_var(sampler_type, "sampler");
   const glsl_type *return_type = glsl_type::int_type;
   MAKE_SIG(return_type, texture_query_levels, 1, s);

   ir_texture *tex = new(mem_ctx) ir_texture(ir_query_levels);
   tex->set_sampler(var_ref(s), return_type);

   body.emit(ret(tex));

   return sig;
}

UNOP(dFdx, ir_unop_dFdx, fs_oes_derivatives)
UNOP(dFdxCoarse, ir_unop_dFdx_coarse, fs_derivative_control)
UNOP(dFdxFine, ir_unop_dFdx_fine, fs_derivative_control)
UNOP(dFdy, ir_unop_dFdy, fs_oes_derivatives)
UNOP(dFdyCoarse, ir_unop_dFdy_coarse, fs_derivative_control)
UNOP(dFdyFine, ir_unop_dFdy_fine, fs_derivative_control)

ir_function_signature *
builtin_builder::_fwidth(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(type, fs_oes_derivatives, 1, p);

   body.emit(ret(add(abs(expr(ir_unop_dFdx, p)), abs(expr(ir_unop_dFdy, p)))));

   return sig;
}

ir_function_signature *
builtin_builder::_fwidthCoarse(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(type, fs_derivative_control, 1, p);

   body.emit(ret(add(abs(expr(ir_unop_dFdx_coarse, p)),
                     abs(expr(ir_unop_dFdy_coarse, p)))));

   return sig;
}

ir_function_signature *
builtin_builder::_fwidthFine(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(type, fs_derivative_control, 1, p);

   body.emit(ret(add(abs(expr(ir_unop_dFdx_fine, p)),
                     abs(expr(ir_unop_dFdy_fine, p)))));

   return sig;
}

ir_function_signature *
builtin_builder::_noise1(const glsl_type *type)
{
   return unop(v110, ir_unop_noise, glsl_type::float_type, type);
}

ir_function_signature *
builtin_builder::_noise2(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(glsl_type::vec2_type, v110, 1, p);

   ir_constant_data b_offset;
   b_offset.f[0] = 601.0f;
   b_offset.f[1] = 313.0f;
   b_offset.f[2] = 29.0f;
   b_offset.f[3] = 277.0f;

   ir_variable *a = body.make_temp(glsl_type::float_type, "a");
   ir_variable *b = body.make_temp(glsl_type::float_type, "b");
   ir_variable *t = body.make_temp(glsl_type::vec2_type,  "t");
   body.emit(assign(a, expr(ir_unop_noise, p)));
   body.emit(assign(b, expr(ir_unop_noise, add(p, imm(type, b_offset)))));
   body.emit(assign(t, a, WRITEMASK_X));
   body.emit(assign(t, b, WRITEMASK_Y));
   body.emit(ret(t));

   return sig;
}

ir_function_signature *
builtin_builder::_noise3(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(glsl_type::vec3_type, v110, 1, p);

   ir_constant_data b_offset;
   b_offset.f[0] = 601.0f;
   b_offset.f[1] = 313.0f;
   b_offset.f[2] = 29.0f;
   b_offset.f[3] = 277.0f;

   ir_constant_data c_offset;
   c_offset.f[0] = 1559.0f;
   c_offset.f[1] = 113.0f;
   c_offset.f[2] = 1861.0f;
   c_offset.f[3] = 797.0f;

   ir_variable *a = body.make_temp(glsl_type::float_type, "a");
   ir_variable *b = body.make_temp(glsl_type::float_type, "b");
   ir_variable *c = body.make_temp(glsl_type::float_type, "c");
   ir_variable *t = body.make_temp(glsl_type::vec3_type,  "t");
   body.emit(assign(a, expr(ir_unop_noise, p)));
   body.emit(assign(b, expr(ir_unop_noise, add(p, imm(type, b_offset)))));
   body.emit(assign(c, expr(ir_unop_noise, add(p, imm(type, c_offset)))));
   body.emit(assign(t, a, WRITEMASK_X));
   body.emit(assign(t, b, WRITEMASK_Y));
   body.emit(assign(t, c, WRITEMASK_Z));
   body.emit(ret(t));

   return sig;
}

ir_function_signature *
builtin_builder::_noise4(const glsl_type *type)
{
   ir_variable *p = in_var(type, "p");
   MAKE_SIG(glsl_type::vec4_type, v110, 1, p);

   ir_variable *_p = body.make_temp(type, "_p");

   ir_constant_data p_offset;
   p_offset.f[0] = 1559.0f;
   p_offset.f[1] = 113.0f;
   p_offset.f[2] = 1861.0f;
   p_offset.f[3] = 797.0f;

   body.emit(assign(_p, add(p, imm(type, p_offset))));

   ir_constant_data offset;
   offset.f[0] = 601.0f;
   offset.f[1] = 313.0f;
   offset.f[2] = 29.0f;
   offset.f[3] = 277.0f;

   ir_variable *a = body.make_temp(glsl_type::float_type, "a");
   ir_variable *b = body.make_temp(glsl_type::float_type, "b");
   ir_variable *c = body.make_temp(glsl_type::float_type, "c");
   ir_variable *d = body.make_temp(glsl_type::float_type, "d");
   ir_variable *t = body.make_temp(glsl_type::vec4_type,  "t");
   body.emit(assign(a, expr(ir_unop_noise, p)));
   body.emit(assign(b, expr(ir_unop_noise, add(p, imm(type, offset)))));
   body.emit(assign(c, expr(ir_unop_noise, _p)));
   body.emit(assign(d, expr(ir_unop_noise, add(_p, imm(type, offset)))));
   body.emit(assign(t, a, WRITEMASK_X));
   body.emit(assign(t, b, WRITEMASK_Y));
   body.emit(assign(t, c, WRITEMASK_Z));
   body.emit(assign(t, d, WRITEMASK_W));
   body.emit(ret(t));

   return sig;
}

ir_function_signature *
builtin_builder::_bitfieldExtract(const glsl_type *type)
{
   ir_variable *value  = in_var(type, "value");
   ir_variable *offset = in_var(glsl_type::int_type, "offset");
   ir_variable *bits   = in_var(glsl_type::int_type, "bits");
   MAKE_SIG(type, gpu_shader5, 3, value, offset, bits);

   body.emit(ret(expr(ir_triop_bitfield_extract, value, offset, bits)));

   return sig;
}

ir_function_signature *
builtin_builder::_bitfieldInsert(const glsl_type *type)
{
   ir_variable *base   = in_var(type, "base");
   ir_variable *insert = in_var(type, "insert");
   ir_variable *offset = in_var(glsl_type::int_type, "offset");
   ir_variable *bits   = in_var(glsl_type::int_type, "bits");
   MAKE_SIG(type, gpu_shader5, 4, base, insert, offset, bits);

   body.emit(ret(bitfield_insert(base, insert, offset, bits)));

   return sig;
}

UNOP(bitfieldReverse, ir_unop_bitfield_reverse, gpu_shader5)

ir_function_signature *
builtin_builder::_bitCount(const glsl_type *type)
{
   return unop(gpu_shader5, ir_unop_bit_count,
               glsl_type::ivec(type->vector_elements), type);
}

ir_function_signature *
builtin_builder::_findLSB(const glsl_type *type)
{
   return unop(gpu_shader5, ir_unop_find_lsb,
               glsl_type::ivec(type->vector_elements), type);
}

ir_function_signature *
builtin_builder::_findMSB(const glsl_type *type)
{
   return unop(gpu_shader5, ir_unop_find_msb,
               glsl_type::ivec(type->vector_elements), type);
}

ir_function_signature *
builtin_builder::_fma(const glsl_type *type)
{
   ir_variable *a = in_var(type, "a");
   ir_variable *b = in_var(type, "b");
   ir_variable *c = in_var(type, "c");
   MAKE_SIG(type, gpu_shader5, 3, a, b, c);

   body.emit(ret(ir_builder::fma(a, b, c)));

   return sig;
}

ir_function_signature *
builtin_builder::_ldexp(const glsl_type *x_type, const glsl_type *exp_type)
{
   return binop(ir_binop_ldexp, gpu_shader5, x_type, x_type, exp_type);
}

ir_function_signature *
builtin_builder::_frexp(const glsl_type *x_type, const glsl_type *exp_type)
{
   ir_variable *x = in_var(x_type, "x");
   ir_variable *exponent = out_var(exp_type, "exp");
   MAKE_SIG(x_type, gpu_shader5, 2, x, exponent);

   const unsigned vec_elem = x_type->vector_elements;
   const glsl_type *bvec = glsl_type::get_instance(GLSL_TYPE_BOOL, vec_elem, 1);
   const glsl_type *uvec = glsl_type::get_instance(GLSL_TYPE_UINT, vec_elem, 1);

   /* Single-precision floating-point values are stored as
    *   1 sign bit;
    *   8 exponent bits;
    *   23 mantissa bits.
    *
    * An exponent shift of 23 will shift the mantissa out, leaving only the
    * exponent and sign bit (which itself may be zero, if the absolute value
    * was taken before the bitcast and shift.
    */
   ir_constant *exponent_shift = imm(23);
   ir_constant *exponent_bias = imm(-126, vec_elem);

   ir_constant *sign_mantissa_mask = imm(0x807fffffu, vec_elem);

   /* Exponent of floating-point values in the range [0.5, 1.0). */
   ir_constant *exponent_value = imm(0x3f000000u, vec_elem);

   ir_variable *is_not_zero = body.make_temp(bvec, "is_not_zero");
   body.emit(assign(is_not_zero, nequal(abs(x), imm(0.0f, vec_elem))));

   /* Since abs(x) ensures that the sign bit is zero, we don't need to bitcast
    * to unsigned integers to ensure that 1 bits aren't shifted in.
    */
   body.emit(assign(exponent, rshift(bitcast_f2i(abs(x)), exponent_shift)));
   body.emit(assign(exponent, add(exponent, csel(is_not_zero, exponent_bias,
                                                     imm(0, vec_elem)))));

   ir_variable *bits = body.make_temp(uvec, "bits");
   body.emit(assign(bits, bitcast_f2u(x)));
   body.emit(assign(bits, bit_and(bits, sign_mantissa_mask)));
   body.emit(assign(bits, bit_or(bits, csel(is_not_zero, exponent_value,
                                                imm(0u, vec_elem)))));
   body.emit(ret(bitcast_u2f(bits)));

   return sig;
}

ir_function_signature *
builtin_builder::_uaddCarry(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *carry = out_var(type, "carry");
   MAKE_SIG(type, gpu_shader5, 3, x, y, carry);

   body.emit(assign(carry, ir_builder::carry(x, y)));
   body.emit(ret(add(x, y)));

   return sig;
}

ir_function_signature *
builtin_builder::_usubBorrow(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *borrow = out_var(type, "borrow");
   MAKE_SIG(type, gpu_shader5, 3, x, y, borrow);

   body.emit(assign(borrow, ir_builder::borrow(x, y)));
   body.emit(ret(sub(x, y)));

   return sig;
}

/**
 * For both imulExtended() and umulExtended() built-ins.
 */
ir_function_signature *
builtin_builder::_mulExtended(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *msb = out_var(type, "msb");
   ir_variable *lsb = out_var(type, "lsb");
   MAKE_SIG(glsl_type::void_type, gpu_shader5, 4, x, y, msb, lsb);

   body.emit(assign(msb, imul_high(x, y)));
   body.emit(assign(lsb, mul(x, y)));

   return sig;
}

ir_function_signature *
builtin_builder::_interpolateAtCentroid(const glsl_type *type)
{
   ir_variable *interpolant = in_var(type, "interpolant");
   interpolant->data.must_be_shader_input = 1;
   MAKE_SIG(type, fs_gpu_shader5, 1, interpolant);

   body.emit(ret(interpolate_at_centroid(interpolant)));

   return sig;
}

ir_function_signature *
builtin_builder::_interpolateAtOffset(const glsl_type *type)
{
   ir_variable *interpolant = in_var(type, "interpolant");
   interpolant->data.must_be_shader_input = 1;
   ir_variable *offset = in_var(glsl_type::vec2_type, "offset");
   MAKE_SIG(type, fs_gpu_shader5, 2, interpolant, offset);

   body.emit(ret(interpolate_at_offset(interpolant, offset)));

   return sig;
}

ir_function_signature *
builtin_builder::_interpolateAtSample(const glsl_type *type)
{
   ir_variable *interpolant = in_var(type, "interpolant");
   interpolant->data.must_be_shader_input = 1;
   ir_variable *sample_num = in_var(glsl_type::int_type, "sample_num");
   MAKE_SIG(type, fs_gpu_shader5, 2, interpolant, sample_num);

   body.emit(ret(interpolate_at_sample(interpolant, sample_num)));

   return sig;
}

ir_function_signature *
builtin_builder::_atomic_intrinsic(builtin_available_predicate avail)
{
   ir_variable *counter = in_var(glsl_type::atomic_uint_type, "counter");
   MAKE_INTRINSIC(glsl_type::uint_type, avail, 1, counter);
   return sig;
}

ir_function_signature *
builtin_builder::_atomic_op(const char *intrinsic,
                            builtin_available_predicate avail)
{
   ir_variable *counter = in_var(glsl_type::atomic_uint_type, "atomic_counter");
   MAKE_SIG(glsl_type::uint_type, avail, 1, counter);

   ir_variable *retval = body.make_temp(glsl_type::uint_type, "atomic_retval");
   body.emit(call(shader->symbols->get_function(intrinsic), retval,
                  sig->parameters));
   body.emit(ret(retval));
   return sig;
}

ir_function_signature *
builtin_builder::_min3(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *z = in_var(type, "z");
   MAKE_SIG(type, shader_trinary_minmax, 3, x, y, z);

   ir_expression *min3 = min2(x, min2(y,z));
   body.emit(ret(min3));

   return sig;
}

ir_function_signature *
builtin_builder::_max3(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *z = in_var(type, "z");
   MAKE_SIG(type, shader_trinary_minmax, 3, x, y, z);

   ir_expression *max3 = max2(x, max2(y,z));
   body.emit(ret(max3));

   return sig;
}

ir_function_signature *
builtin_builder::_mid3(const glsl_type *type)
{
   ir_variable *x = in_var(type, "x");
   ir_variable *y = in_var(type, "y");
   ir_variable *z = in_var(type, "z");
   MAKE_SIG(type, shader_trinary_minmax, 3, x, y, z);

   ir_expression *mid3 = max2(min2(x, y), max2(min2(x, z), min2(y, z)));
   body.emit(ret(mid3));

   return sig;
}

ir_function_signature *
builtin_builder::_image_prototype(const glsl_type *image_type,
                                  const char *intrinsic_name,
                                  unsigned num_arguments,
                                  unsigned flags)
{
   const glsl_type *data_type = glsl_type::get_instance(
      image_type->sampler_type,
      (flags & IMAGE_FUNCTION_HAS_VECTOR_DATA_TYPE ? 4 : 1),
      1);
   const glsl_type *ret_type = (flags & IMAGE_FUNCTION_RETURNS_VOID ?
                                glsl_type::void_type : data_type);

   /* Addressing arguments that are always present. */
   ir_variable *image = in_var(image_type, "image");
   ir_variable *coord = in_var(
      glsl_type::ivec(image_type->coordinate_components()), "coord");

   ir_function_signature *sig = new_sig(
      ret_type, shader_image_load_store, 2, image, coord);

   /* Sample index for multisample images. */
   if (image_type->sampler_dimensionality == GLSL_SAMPLER_DIM_MS)
      sig->parameters.push_tail(in_var(glsl_type::int_type, "sample"));

   /* Data arguments. */
   for (unsigned i = 0; i < num_arguments; ++i) {
      char *arg_name = ralloc_asprintf(NULL, "arg%d", i);
      sig->parameters.push_tail(in_var(data_type, arg_name));
      ralloc_free(arg_name);
   }

   /* Set the maximal set of qualifiers allowed for this image
    * built-in.  Function calls with arguments having fewer
    * qualifiers than present in the prototype are allowed by the
    * spec, but not with more, i.e. this will make the compiler
    * accept everything that needs to be accepted, and reject cases
    * like loads from write-only or stores to read-only images.
    */
   image->data.image_read_only = (flags & IMAGE_FUNCTION_READ_ONLY) != 0;
   image->data.image_write_only = (flags & IMAGE_FUNCTION_WRITE_ONLY) != 0;
   image->data.image_coherent = true;
   image->data.image_volatile = true;
   image->data.image_restrict = true;

   return sig;
}

ir_function_signature *
builtin_builder::_image(const glsl_type *image_type,
                        const char *intrinsic_name,
                        unsigned num_arguments,
                        unsigned flags)
{
   ir_function_signature *sig = _image_prototype(image_type, intrinsic_name,
                                                 num_arguments, flags);

   if (flags & IMAGE_FUNCTION_EMIT_STUB) {
      ir_factory body(&sig->body, mem_ctx);
      ir_function *f = shader->symbols->get_function(intrinsic_name);

      if (flags & IMAGE_FUNCTION_RETURNS_VOID) {
         body.emit(call(f, NULL, sig->parameters));
      } else {
         ir_variable *ret_val =
            body.make_temp(sig->return_type, "_ret_val");
         body.emit(call(f, ret_val, sig->parameters));
         body.emit(ret(ret_val));
      }

      sig->is_defined = true;

   } else {
      sig->is_intrinsic = true;
   }

   return sig;
}

ir_function_signature *
builtin_builder::_memory_barrier_intrinsic(builtin_available_predicate avail)
{
   MAKE_INTRINSIC(glsl_type::void_type, avail, 0);
   return sig;
}

ir_function_signature *
builtin_builder::_memory_barrier(builtin_available_predicate avail)
{
   MAKE_SIG(glsl_type::void_type, avail, 0);
   body.emit(call(shader->symbols->get_function("__intrinsic_memory_barrier"),
                  NULL, sig->parameters));
   return sig;
}

/** @} */

/******************************************************************************/

//@TODO: implement
typedef int mtx_t;
#define _MTX_INITIALIZER_NP 0
#define mtx_lock(name)
#define mtx_unlock(name)


/* The singleton instance of builtin_builder. */
static builtin_builder builtins;
static mtx_t builtins_lock = _MTX_INITIALIZER_NP;

/**
 * External API (exposing the built-in module to the rest of the compiler):
 *  @{
 */
void
_mesa_glsl_initialize_builtin_functions()
{
   mtx_lock(&builtins_lock);
   builtins.initialize();
   mtx_unlock(&builtins_lock);
}

void
_mesa_glsl_release_builtin_functions()
{
   mtx_lock(&builtins_lock);
   builtins.release();
   mtx_unlock(&builtins_lock);
}

ir_function_signature *
_mesa_glsl_find_builtin_function(_mesa_glsl_parse_state *state,
                                 const char *name, exec_list *actual_parameters)
{
   ir_function_signature * s;
   mtx_lock(&builtins_lock);
   s = builtins.find(state, name, actual_parameters);
   mtx_unlock(&builtins_lock);
   return s;
}

gl_shader *
_mesa_glsl_get_builtin_function_shader()
{
   return builtins.shader;
}

/** @} */

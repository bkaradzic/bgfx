/*
 * Copyright © 2012 Intel Corporation
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

#pragma once
#ifndef GLSL_LINK_VARYINGS_H
#define GLSL_LINK_VARYINGS_H

/**
 * \file link_varyings.h
 *
 * Linker functions related specifically to linking varyings between shader
 * stages.
 */


#include "main/glheader.h"


struct gl_shader_program;
struct gl_shader;
class ir_variable;


/**
 * Data structure describing a varying which is available for use in transform
 * feedback.
 *
 * For example, if the vertex shader contains:
 *
 *     struct S {
 *       vec4 foo;
 *       float[3] bar;
 *     };
 *
 *     varying S[2] v;
 *
 * Then there would be tfeedback_candidate objects corresponding to the
 * following varyings:
 *
 *     v[0].foo
 *     v[0].bar
 *     v[1].foo
 *     v[1].bar
 */
struct tfeedback_candidate
{
   /**
    * Toplevel variable containing this varying.  In the above example, this
    * would point to the declaration of the varying v.
    */
   ir_variable *toplevel_var;

   /**
    * Type of this varying.  In the above example, this would point to the
    * glsl_type for "vec4" or "float[3]".
    */
   const glsl_type *type;

   /**
    * Offset within the toplevel variable where this varying occurs (counted
    * in multiples of the size of a float).
    */
   unsigned offset;
};


/**
 * Data structure tracking information about a transform feedback declaration
 * during linking.
 */
class tfeedback_decl
{
public:
   void init(struct gl_context *ctx, const void *mem_ctx, const char *input);
   static bool is_same(const tfeedback_decl &x, const tfeedback_decl &y);
   bool assign_location(struct gl_context *ctx,
                        struct gl_shader_program *prog);
   unsigned get_num_outputs() const;
   bool store(struct gl_context *ctx, struct gl_shader_program *prog,
              struct gl_transform_feedback_info *info, unsigned buffer,
              const unsigned max_outputs) const;
   const tfeedback_candidate *find_candidate(gl_shader_program *prog,
                                             hash_table *tfeedback_candidates);

   bool is_next_buffer_separator() const
   {
      return this->next_buffer_separator;
   }

   bool is_varying() const
   {
      return !this->next_buffer_separator && !this->skip_components;
   }

   const char *name() const
   {
      return this->orig_name;
   }

   unsigned get_stream_id() const
   {
      return this->stream_id;
   }

   /**
    * The total number of varying components taken up by this variable.  Only
    * valid if assign_location() has been called.
    */
   unsigned num_components() const
   {
      if (this->is_clip_distance_mesa)
         return this->size;
      else
         return this->vector_elements * this->matrix_columns * this->size;
   }

   unsigned get_location() const {
      return this->location;
   }

private:
   /**
    * The name that was supplied to glTransformFeedbackVaryings.  Used for
    * error reporting and glGetTransformFeedbackVarying().
    */
   const char *orig_name;

   /**
    * The name of the variable, parsed from orig_name.
    */
   const char *var_name;

   /**
    * True if the declaration in orig_name represents an array.
    */
   bool is_subscripted;

   /**
    * If is_subscripted is true, the subscript that was specified in orig_name.
    */
   unsigned array_subscript;

   /**
    * True if the variable is gl_ClipDistance and the driver lowers
    * gl_ClipDistance to gl_ClipDistanceMESA.
    */
   bool is_clip_distance_mesa;

   /**
    * The vertex shader output location that the linker assigned for this
    * variable.  -1 if a location hasn't been assigned yet.
    */
   int location;

   /**
    * If non-zero, then this variable may be packed along with other variables
    * into a single varying slot, so this offset should be applied when
    * accessing components.  For example, an offset of 1 means that the x
    * component of this variable is actually stored in component y of the
    * location specified by \c location.
    *
    * Only valid if location != -1.
    */
   unsigned location_frac;

   /**
    * If location != -1, the number of vector elements in this variable, or 1
    * if this variable is a scalar.
    */
   unsigned vector_elements;

   /**
    * If location != -1, the number of matrix columns in this variable, or 1
    * if this variable is not a matrix.
    */
   unsigned matrix_columns;

   /** Type of the varying returned by glGetTransformFeedbackVarying() */
   GLenum type;

   /**
    * If location != -1, the size that should be returned by
    * glGetTransformFeedbackVarying().
    */
   unsigned size;

   /**
    * How many components to skip. If non-zero, this is
    * gl_SkipComponents{1,2,3,4} from ARB_transform_feedback3.
    */
   unsigned skip_components;

   /**
    * Whether this is gl_NextBuffer from ARB_transform_feedback3.
    */
   bool next_buffer_separator;

   /**
    * If find_candidate() has been called, pointer to the tfeedback_candidate
    * data structure that was found.  Otherwise NULL.
    */
   const tfeedback_candidate *matched_candidate;

   /**
    * StreamId assigned to this varying (defaults to 0). Can only be set to
    * values other than 0 in geometry shaders that use the stream layout
    * modifier. Accepted values must be in the range [0, MAX_VERTEX_STREAMS-1].
    */
   unsigned stream_id;
};


void
cross_validate_outputs_to_inputs(struct gl_shader_program *prog,
				 gl_shader *producer, gl_shader *consumer);

bool
parse_tfeedback_decls(struct gl_context *ctx, struct gl_shader_program *prog,
                      const void *mem_ctx, unsigned num_names,
                      char **varying_names, tfeedback_decl *decls);

bool
store_tfeedback_info(struct gl_context *ctx, struct gl_shader_program *prog,
                     unsigned num_tfeedback_decls,
                     tfeedback_decl *tfeedback_decls);

bool
assign_varying_locations(struct gl_context *ctx,
			 void *mem_ctx,
			 struct gl_shader_program *prog,
			 gl_shader *producer, gl_shader *consumer,
                         unsigned num_tfeedback_decls,
                         tfeedback_decl *tfeedback_decls,
                         unsigned gs_input_vertices);

bool
check_against_output_limit(struct gl_context *ctx,
                           struct gl_shader_program *prog,
                           gl_shader *producer);

bool
check_against_input_limit(struct gl_context *ctx,
                          struct gl_shader_program *prog,
                          gl_shader *consumer);

#endif /* GLSL_LINK_VARYINGS_H */

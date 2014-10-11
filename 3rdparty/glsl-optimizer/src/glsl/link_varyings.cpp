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

/**
 * \file link_varyings.cpp
 *
 * Linker functions related specifically to linking varyings between shader
 * stages.
 */


#include "main/errors.h"
#include "main/mtypes.h"
#include "glsl_symbol_table.h"
#include "glsl_parser_extras.h"
#include "ir_optimization.h"
#include "linker.h"
#include "link_varyings.h"
#include "main/macros.h"
#include "program/hash_table.h"
#include "program.h"


/**
 * Validate the types and qualifiers of an output from one stage against the
 * matching input to another stage.
 */
static void
cross_validate_types_and_qualifiers(struct gl_shader_program *prog,
                                    const ir_variable *input,
                                    const ir_variable *output,
                                    gl_shader_stage consumer_stage,
                                    gl_shader_stage producer_stage)
{
   /* Check that the types match between stages.
    */
   const glsl_type *type_to_match = input->type;
   if (consumer_stage == MESA_SHADER_GEOMETRY) {
      assert(type_to_match->is_array()); /* Enforced by ast_to_hir */
      type_to_match = type_to_match->element_type();
   }
   if (type_to_match != output->type) {
      /* There is a bit of a special case for gl_TexCoord.  This
       * built-in is unsized by default.  Applications that variable
       * access it must redeclare it with a size.  There is some
       * language in the GLSL spec that implies the fragment shader
       * and vertex shader do not have to agree on this size.  Other
       * driver behave this way, and one or two applications seem to
       * rely on it.
       *
       * Neither declaration needs to be modified here because the array
       * sizes are fixed later when update_array_sizes is called.
       *
       * From page 48 (page 54 of the PDF) of the GLSL 1.10 spec:
       *
       *     "Unlike user-defined varying variables, the built-in
       *     varying variables don't have a strict one-to-one
       *     correspondence between the vertex language and the
       *     fragment language."
       */
      if (!output->type->is_array() || !is_gl_identifier(output->name)) {
         linker_error(prog,
                      "%s shader output `%s' declared as type `%s', "
                      "but %s shader input declared as type `%s'\n",
                      _mesa_shader_stage_to_string(producer_stage),
                      output->name,
                      output->type->name,
                      _mesa_shader_stage_to_string(consumer_stage),
                      input->type->name);
         return;
      }
   }

   /* Check that all of the qualifiers match between stages.
    */
   if (input->data.centroid != output->data.centroid) {
      linker_error(prog,
                   "%s shader output `%s' %s centroid qualifier, "
                   "but %s shader input %s centroid qualifier\n",
                   _mesa_shader_stage_to_string(producer_stage),
                   output->name,
                   (output->data.centroid) ? "has" : "lacks",
                   _mesa_shader_stage_to_string(consumer_stage),
                   (input->data.centroid) ? "has" : "lacks");
      return;
   }

   if (input->data.sample != output->data.sample) {
      linker_error(prog,
                   "%s shader output `%s' %s sample qualifier, "
                   "but %s shader input %s sample qualifier\n",
                   _mesa_shader_stage_to_string(producer_stage),
                   output->name,
                   (output->data.sample) ? "has" : "lacks",
                   _mesa_shader_stage_to_string(consumer_stage),
                   (input->data.sample) ? "has" : "lacks");
      return;
   }

   if (input->data.invariant != output->data.invariant) {
      linker_error(prog,
                   "%s shader output `%s' %s invariant qualifier, "
                   "but %s shader input %s invariant qualifier\n",
                   _mesa_shader_stage_to_string(producer_stage),
                   output->name,
                   (output->data.invariant) ? "has" : "lacks",
                   _mesa_shader_stage_to_string(consumer_stage),
                   (input->data.invariant) ? "has" : "lacks");
      return;
   }

   if (input->data.interpolation != output->data.interpolation) {
      linker_error(prog,
                   "%s shader output `%s' specifies %s "
                   "interpolation qualifier, "
                   "but %s shader input specifies %s "
                   "interpolation qualifier\n",
                   _mesa_shader_stage_to_string(producer_stage),
                   output->name,
                   interpolation_string(output->data.interpolation),
                   _mesa_shader_stage_to_string(consumer_stage),
                   interpolation_string(input->data.interpolation));
      return;
   }
}

/**
 * Validate front and back color outputs against single color input
 */
static void
cross_validate_front_and_back_color(struct gl_shader_program *prog,
                                    const ir_variable *input,
                                    const ir_variable *front_color,
                                    const ir_variable *back_color,
                                    gl_shader_stage consumer_stage,
                                    gl_shader_stage producer_stage)
{
   if (front_color != NULL && front_color->data.assigned)
      cross_validate_types_and_qualifiers(prog, input, front_color,
                                          consumer_stage, producer_stage);

   if (back_color != NULL && back_color->data.assigned)
      cross_validate_types_and_qualifiers(prog, input, back_color,
                                          consumer_stage, producer_stage);
}

/**
 * Validate that outputs from one stage match inputs of another
 */
void
cross_validate_outputs_to_inputs(struct gl_shader_program *prog,
				 gl_shader *producer, gl_shader *consumer)
{
   glsl_symbol_table parameters;
   ir_variable *explicit_locations[MAX_VARYING] = { NULL, };

   /* Find all shader outputs in the "producer" stage.
    */
   foreach_in_list(ir_instruction, node, producer->ir) {
      ir_variable *const var = node->as_variable();

      if ((var == NULL) || (var->data.mode != ir_var_shader_out))
	 continue;

      if (!var->data.explicit_location
          || var->data.location < VARYING_SLOT_VAR0)
         parameters.add_variable(var);
      else {
         /* User-defined varyings with explicit locations are handled
          * differently because they do not need to have matching names.
          */
         const unsigned idx = var->data.location - VARYING_SLOT_VAR0;

         if (explicit_locations[idx] != NULL) {
            linker_error(prog,
                         "%s shader has multiple outputs explicitly "
                         "assigned to location %d\n",
                         _mesa_shader_stage_to_string(producer->Stage),
                         idx);
            return;
         }

         explicit_locations[idx] = var;
      }
   }


   /* Find all shader inputs in the "consumer" stage.  Any variables that have
    * matching outputs already in the symbol table must have the same type and
    * qualifiers.
    *
    * Exception: if the consumer is the geometry shader, then the inputs
    * should be arrays and the type of the array element should match the type
    * of the corresponding producer output.
    */
   foreach_in_list(ir_instruction, node, consumer->ir) {
      ir_variable *const input = node->as_variable();

      if ((input == NULL) || (input->data.mode != ir_var_shader_in))
	 continue;

      if (strcmp(input->name, "gl_Color") == 0 && input->data.used) {
         const ir_variable *const front_color =
            parameters.get_variable("gl_FrontColor");

         const ir_variable *const back_color =
            parameters.get_variable("gl_BackColor");

         cross_validate_front_and_back_color(prog, input,
                                             front_color, back_color,
                                             consumer->Stage, producer->Stage);
      } else if (strcmp(input->name, "gl_SecondaryColor") == 0 && input->data.used) {
         const ir_variable *const front_color =
            parameters.get_variable("gl_FrontSecondaryColor");

         const ir_variable *const back_color =
            parameters.get_variable("gl_BackSecondaryColor");

         cross_validate_front_and_back_color(prog, input,
                                             front_color, back_color,
                                             consumer->Stage, producer->Stage);
      } else {
         /* The rules for connecting inputs and outputs change in the presence
          * of explicit locations.  In this case, we no longer care about the
          * names of the variables.  Instead, we care only about the
          * explicitly assigned location.
          */
         ir_variable *output = NULL;
         if (input->data.explicit_location
             && input->data.location >= VARYING_SLOT_VAR0) {
            output = explicit_locations[input->data.location - VARYING_SLOT_VAR0];

            if (output == NULL) {
               linker_error(prog,
                            "%s shader input `%s' with explicit location "
                            "has no matching output\n",
                            _mesa_shader_stage_to_string(consumer->Stage),
                            input->name);
            }
         } else {
            output = parameters.get_variable(input->name);
         }

         if (output != NULL) {
            cross_validate_types_and_qualifiers(prog, input, output,
                                                consumer->Stage, producer->Stage);
         }
      }
   }
}


/**
 * Initialize this object based on a string that was passed to
 * glTransformFeedbackVaryings.
 *
 * If the input is mal-formed, this call still succeeds, but it sets
 * this->var_name to a mal-formed input, so tfeedback_decl::find_output_var()
 * will fail to find any matching variable.
 */
void
tfeedback_decl::init(struct gl_context *ctx, const void *mem_ctx,
                     const char *input)
{
   /* We don't have to be pedantic about what is a valid GLSL variable name,
    * because any variable with an invalid name can't exist in the IR anyway.
    */

   this->location = -1;
   this->orig_name = input;
   this->is_clip_distance_mesa = false;
   this->skip_components = 0;
   this->next_buffer_separator = false;
   this->matched_candidate = NULL;
   this->stream_id = 0;

   if (ctx->Extensions.ARB_transform_feedback3) {
      /* Parse gl_NextBuffer. */
      if (strcmp(input, "gl_NextBuffer") == 0) {
         this->next_buffer_separator = true;
         return;
      }

      /* Parse gl_SkipComponents. */
      if (strcmp(input, "gl_SkipComponents1") == 0)
         this->skip_components = 1;
      else if (strcmp(input, "gl_SkipComponents2") == 0)
         this->skip_components = 2;
      else if (strcmp(input, "gl_SkipComponents3") == 0)
         this->skip_components = 3;
      else if (strcmp(input, "gl_SkipComponents4") == 0)
         this->skip_components = 4;

      if (this->skip_components)
         return;
   }

   /* Parse a declaration. */
   const char *base_name_end;
   long subscript = parse_program_resource_name(input, &base_name_end);
   this->var_name = ralloc_strndup(mem_ctx, input, base_name_end - input);
   if (this->var_name == NULL) {
      _mesa_error_no_memory(__func__);
      return;
   }

   if (subscript >= 0) {
      this->array_subscript = subscript;
      this->is_subscripted = true;
   } else {
      this->is_subscripted = false;
   }

   /* For drivers that lower gl_ClipDistance to gl_ClipDistanceMESA, this
    * class must behave specially to account for the fact that gl_ClipDistance
    * is converted from a float[8] to a vec4[2].
    */
   if (ctx->Const.ShaderCompilerOptions[MESA_SHADER_VERTEX].LowerClipDistance &&
       strcmp(this->var_name, "gl_ClipDistance") == 0) {
      this->is_clip_distance_mesa = true;
   }
}


/**
 * Determine whether two tfeedback_decl objects refer to the same variable and
 * array index (if applicable).
 */
bool
tfeedback_decl::is_same(const tfeedback_decl &x, const tfeedback_decl &y)
{
   assert(x.is_varying() && y.is_varying());

   if (strcmp(x.var_name, y.var_name) != 0)
      return false;
   if (x.is_subscripted != y.is_subscripted)
      return false;
   if (x.is_subscripted && x.array_subscript != y.array_subscript)
      return false;
   return true;
}


/**
 * Assign a location and stream ID for this tfeedback_decl object based on the
 * transform feedback candidate found by find_candidate.
 *
 * If an error occurs, the error is reported through linker_error() and false
 * is returned.
 */
bool
tfeedback_decl::assign_location(struct gl_context *ctx,
                                struct gl_shader_program *prog)
{
   assert(this->is_varying());

   unsigned fine_location
      = this->matched_candidate->toplevel_var->data.location * 4
      + this->matched_candidate->toplevel_var->data.location_frac
      + this->matched_candidate->offset;

   if (this->matched_candidate->type->is_array()) {
      /* Array variable */
      const unsigned matrix_cols =
         this->matched_candidate->type->fields.array->matrix_columns;
      const unsigned vector_elements =
         this->matched_candidate->type->fields.array->vector_elements;
      unsigned actual_array_size = this->is_clip_distance_mesa ?
         prog->LastClipDistanceArraySize :
         this->matched_candidate->type->array_size();

      if (this->is_subscripted) {
         /* Check array bounds. */
         if (this->array_subscript >= actual_array_size) {
            linker_error(prog, "Transform feedback varying %s has index "
                         "%i, but the array size is %u.",
                         this->orig_name, this->array_subscript,
                         actual_array_size);
            return false;
         }
         unsigned array_elem_size = this->is_clip_distance_mesa ?
            1 : vector_elements * matrix_cols;
         fine_location += array_elem_size * this->array_subscript;
         this->size = 1;
      } else {
         this->size = actual_array_size;
      }
      this->vector_elements = vector_elements;
      this->matrix_columns = matrix_cols;
      if (this->is_clip_distance_mesa)
         this->type = GL_FLOAT;
      else
         this->type = this->matched_candidate->type->fields.array->gl_type;
   } else {
      /* Regular variable (scalar, vector, or matrix) */
      if (this->is_subscripted) {
         linker_error(prog, "Transform feedback varying %s requested, "
                      "but %s is not an array.",
                      this->orig_name, this->var_name);
         return false;
      }
      this->size = 1;
      this->vector_elements = this->matched_candidate->type->vector_elements;
      this->matrix_columns = this->matched_candidate->type->matrix_columns;
      this->type = this->matched_candidate->type->gl_type;
   }
   this->location = fine_location / 4;
   this->location_frac = fine_location % 4;

   /* From GL_EXT_transform_feedback:
    *   A program will fail to link if:
    *
    *   * the total number of components to capture in any varying
    *     variable in <varyings> is greater than the constant
    *     MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT and the
    *     buffer mode is SEPARATE_ATTRIBS_EXT;
    */
   if (prog->TransformFeedback.BufferMode == GL_SEPARATE_ATTRIBS &&
       this->num_components() >
       ctx->Const.MaxTransformFeedbackSeparateComponents) {
      linker_error(prog, "Transform feedback varying %s exceeds "
                   "MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS.",
                   this->orig_name);
      return false;
   }

   /* Only transform feedback varyings can be assigned to non-zero streams,
    * so assign the stream id here.
    */
   this->stream_id = this->matched_candidate->toplevel_var->data.stream;

   return true;
}


unsigned
tfeedback_decl::get_num_outputs() const
{
   if (!this->is_varying()) {
      return 0;
   }

   return (this->num_components() + this->location_frac + 3)/4;
}


/**
 * Update gl_transform_feedback_info to reflect this tfeedback_decl.
 *
 * If an error occurs, the error is reported through linker_error() and false
 * is returned.
 */
bool
tfeedback_decl::store(struct gl_context *ctx, struct gl_shader_program *prog,
                      struct gl_transform_feedback_info *info,
                      unsigned buffer, const unsigned max_outputs) const
{
   assert(!this->next_buffer_separator);

   /* Handle gl_SkipComponents. */
   if (this->skip_components) {
      info->BufferStride[buffer] += this->skip_components;
      return true;
   }

   /* From GL_EXT_transform_feedback:
    *   A program will fail to link if:
    *
    *     * the total number of components to capture is greater than
    *       the constant MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT
    *       and the buffer mode is INTERLEAVED_ATTRIBS_EXT.
    */
   if (prog->TransformFeedback.BufferMode == GL_INTERLEAVED_ATTRIBS &&
       info->BufferStride[buffer] + this->num_components() >
       ctx->Const.MaxTransformFeedbackInterleavedComponents) {
      linker_error(prog, "The MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS "
                   "limit has been exceeded.");
      return false;
   }

   unsigned location = this->location;
   unsigned location_frac = this->location_frac;
   unsigned num_components = this->num_components();
   while (num_components > 0) {
      unsigned output_size = MIN2(num_components, 4 - location_frac);
      assert(info->NumOutputs < max_outputs);
      info->Outputs[info->NumOutputs].ComponentOffset = location_frac;
      info->Outputs[info->NumOutputs].OutputRegister = location;
      info->Outputs[info->NumOutputs].NumComponents = output_size;
      info->Outputs[info->NumOutputs].StreamId = stream_id;
      info->Outputs[info->NumOutputs].OutputBuffer = buffer;
      info->Outputs[info->NumOutputs].DstOffset = info->BufferStride[buffer];
      ++info->NumOutputs;
      info->BufferStride[buffer] += output_size;
      num_components -= output_size;
      location++;
      location_frac = 0;
   }

   info->Varyings[info->NumVarying].Name = ralloc_strdup(prog, this->orig_name);
   info->Varyings[info->NumVarying].Type = this->type;
   info->Varyings[info->NumVarying].Size = this->size;
   info->NumVarying++;

   return true;
}


const tfeedback_candidate *
tfeedback_decl::find_candidate(gl_shader_program *prog,
                               hash_table *tfeedback_candidates)
{
   const char *name = this->is_clip_distance_mesa
      ? "gl_ClipDistanceMESA" : this->var_name;
   this->matched_candidate = (const tfeedback_candidate *)
      hash_table_find(tfeedback_candidates, name);
   if (!this->matched_candidate) {
      /* From GL_EXT_transform_feedback:
       *   A program will fail to link if:
       *
       *   * any variable name specified in the <varyings> array is not
       *     declared as an output in the geometry shader (if present) or
       *     the vertex shader (if no geometry shader is present);
       */
      linker_error(prog, "Transform feedback varying %s undeclared.",
                   this->orig_name);
   }
   return this->matched_candidate;
}


/**
 * Parse all the transform feedback declarations that were passed to
 * glTransformFeedbackVaryings() and store them in tfeedback_decl objects.
 *
 * If an error occurs, the error is reported through linker_error() and false
 * is returned.
 */
bool
parse_tfeedback_decls(struct gl_context *ctx, struct gl_shader_program *prog,
                      const void *mem_ctx, unsigned num_names,
                      char **varying_names, tfeedback_decl *decls)
{
   for (unsigned i = 0; i < num_names; ++i) {
      decls[i].init(ctx, mem_ctx, varying_names[i]);

      if (!decls[i].is_varying())
         continue;

      /* From GL_EXT_transform_feedback:
       *   A program will fail to link if:
       *
       *   * any two entries in the <varyings> array specify the same varying
       *     variable;
       *
       * We interpret this to mean "any two entries in the <varyings> array
       * specify the same varying variable and array index", since transform
       * feedback of arrays would be useless otherwise.
       */
      for (unsigned j = 0; j < i; ++j) {
         if (!decls[j].is_varying())
            continue;

         if (tfeedback_decl::is_same(decls[i], decls[j])) {
            linker_error(prog, "Transform feedback varying %s specified "
                         "more than once.", varying_names[i]);
            return false;
         }
      }
   }
   return true;
}


/**
 * Store transform feedback location assignments into
 * prog->LinkedTransformFeedback based on the data stored in tfeedback_decls.
 *
 * If an error occurs, the error is reported through linker_error() and false
 * is returned.
 */
bool
store_tfeedback_info(struct gl_context *ctx, struct gl_shader_program *prog,
                     unsigned num_tfeedback_decls,
                     tfeedback_decl *tfeedback_decls)
{
   bool separate_attribs_mode =
      prog->TransformFeedback.BufferMode == GL_SEPARATE_ATTRIBS;

   ralloc_free(prog->LinkedTransformFeedback.Varyings);
   ralloc_free(prog->LinkedTransformFeedback.Outputs);

   memset(&prog->LinkedTransformFeedback, 0,
          sizeof(prog->LinkedTransformFeedback));

   prog->LinkedTransformFeedback.Varyings =
      rzalloc_array(prog,
		    struct gl_transform_feedback_varying_info,
		    num_tfeedback_decls);

   unsigned num_outputs = 0;
   for (unsigned i = 0; i < num_tfeedback_decls; ++i)
      num_outputs += tfeedback_decls[i].get_num_outputs();

   prog->LinkedTransformFeedback.Outputs =
      rzalloc_array(prog,
                    struct gl_transform_feedback_output,
                    num_outputs);

   unsigned num_buffers = 0;

   if (separate_attribs_mode) {
      /* GL_SEPARATE_ATTRIBS */
      for (unsigned i = 0; i < num_tfeedback_decls; ++i) {
         if (!tfeedback_decls[i].store(ctx, prog, &prog->LinkedTransformFeedback,
                                       num_buffers, num_outputs))
            return false;

         num_buffers++;
      }
   }
   else {
      /* GL_INVERLEAVED_ATTRIBS */
      int buffer_stream_id = -1;
      for (unsigned i = 0; i < num_tfeedback_decls; ++i) {
         if (tfeedback_decls[i].is_next_buffer_separator()) {
            num_buffers++;
            buffer_stream_id = -1;
            continue;
         } else if (buffer_stream_id == -1)  {
            /* First varying writing to this buffer: remember its stream */
            buffer_stream_id = (int) tfeedback_decls[i].get_stream_id();
         } else if (buffer_stream_id !=
                    (int) tfeedback_decls[i].get_stream_id()) {
            /* Varying writes to the same buffer from a different stream */
            linker_error(prog,
                         "Transform feedback can't capture varyings belonging "
                         "to different vertex streams in a single buffer. "
                         "Varying %s writes to buffer from stream %u, other "
                         "varyings in the same buffer write from stream %u.",
                         tfeedback_decls[i].name(),
                         tfeedback_decls[i].get_stream_id(),
                         buffer_stream_id);
            return false;
         }

         if (!tfeedback_decls[i].store(ctx, prog,
                                       &prog->LinkedTransformFeedback,
                                       num_buffers, num_outputs))
            return false;
      }
      num_buffers++;
   }

   assert(prog->LinkedTransformFeedback.NumOutputs == num_outputs);

   prog->LinkedTransformFeedback.NumBuffers = num_buffers;
   return true;
}

namespace {

/**
 * Data structure recording the relationship between outputs of one shader
 * stage (the "producer") and inputs of another (the "consumer").
 */
class varying_matches
{
public:
   varying_matches(bool disable_varying_packing, bool consumer_is_fs);
   ~varying_matches();
   void record(ir_variable *producer_var, ir_variable *consumer_var);
   unsigned assign_locations();
   void store_locations() const;

private:
   /**
    * If true, this driver disables varying packing, so all varyings need to
    * be aligned on slot boundaries, and take up a number of slots equal to
    * their number of matrix columns times their array size.
    */
   const bool disable_varying_packing;

   /**
    * Enum representing the order in which varyings are packed within a
    * packing class.
    *
    * Currently we pack vec4's first, then vec2's, then scalar values, then
    * vec3's.  This order ensures that the only vectors that are at risk of
    * having to be "double parked" (split between two adjacent varying slots)
    * are the vec3's.
    */
   enum packing_order_enum {
      PACKING_ORDER_VEC4,
      PACKING_ORDER_VEC2,
      PACKING_ORDER_SCALAR,
      PACKING_ORDER_VEC3,
   };

   static unsigned compute_packing_class(const ir_variable *var);
   static packing_order_enum compute_packing_order(const ir_variable *var);
   static int match_comparator(const void *x_generic, const void *y_generic);

   /**
    * Structure recording the relationship between a single producer output
    * and a single consumer input.
    */
   struct match {
      /**
       * Packing class for this varying, computed by compute_packing_class().
       */
      unsigned packing_class;

      /**
       * Packing order for this varying, computed by compute_packing_order().
       */
      packing_order_enum packing_order;
      unsigned num_components;

      /**
       * The output variable in the producer stage.
       */
      ir_variable *producer_var;

      /**
       * The input variable in the consumer stage.
       */
      ir_variable *consumer_var;

      /**
       * The location which has been assigned for this varying.  This is
       * expressed in multiples of a float, with the first generic varying
       * (i.e. the one referred to by VARYING_SLOT_VAR0) represented by the
       * value 0.
       */
      unsigned generic_location;
   } *matches;

   /**
    * The number of elements in the \c matches array that are currently in
    * use.
    */
   unsigned num_matches;

   /**
    * The number of elements that were set aside for the \c matches array when
    * it was allocated.
    */
   unsigned matches_capacity;

   const bool consumer_is_fs;
};

} /* anonymous namespace */

varying_matches::varying_matches(bool disable_varying_packing,
                                 bool consumer_is_fs)
   : disable_varying_packing(disable_varying_packing),
     consumer_is_fs(consumer_is_fs)
{
   /* Note: this initial capacity is rather arbitrarily chosen to be large
    * enough for many cases without wasting an unreasonable amount of space.
    * varying_matches::record() will resize the array if there are more than
    * this number of varyings.
    */
   this->matches_capacity = 8;
   this->matches = (match *)
      malloc(sizeof(*this->matches) * this->matches_capacity);
   this->num_matches = 0;
}


varying_matches::~varying_matches()
{
   free(this->matches);
}


/**
 * Record the given producer/consumer variable pair in the list of variables
 * that should later be assigned locations.
 *
 * It is permissible for \c consumer_var to be NULL (this happens if a
 * variable is output by the producer and consumed by transform feedback, but
 * not consumed by the consumer).
 *
 * If \c producer_var has already been paired up with a consumer_var, or
 * producer_var is part of fixed pipeline functionality (and hence already has
 * a location assigned), this function has no effect.
 *
 * Note: as a side effect this function may change the interpolation type of
 * \c producer_var, but only when the change couldn't possibly affect
 * rendering.
 */
void
varying_matches::record(ir_variable *producer_var, ir_variable *consumer_var)
{
   assert(producer_var != NULL || consumer_var != NULL);

   if ((producer_var && !producer_var->data.is_unmatched_generic_inout)
       || (consumer_var && !consumer_var->data.is_unmatched_generic_inout)) {
      /* Either a location already exists for this variable (since it is part
       * of fixed functionality), or it has already been recorded as part of a
       * previous match.
       */
      return;
   }

   if ((consumer_var == NULL && producer_var->type->contains_integer()) ||
       !consumer_is_fs) {
      /* Since this varying is not being consumed by the fragment shader, its
       * interpolation type varying cannot possibly affect rendering.  Also,
       * this variable is non-flat and is (or contains) an integer.
       *
       * lower_packed_varyings requires all integer varyings to flat,
       * regardless of where they appear.  We can trivially satisfy that
       * requirement by changing the interpolation type to flat here.
       */
      producer_var->data.centroid = false;
      producer_var->data.sample = false;
      producer_var->data.interpolation = INTERP_QUALIFIER_FLAT;

      if (consumer_var) {
         consumer_var->data.centroid = false;
         consumer_var->data.sample = false;
         consumer_var->data.interpolation = INTERP_QUALIFIER_FLAT;
      }
   }

   if (this->num_matches == this->matches_capacity) {
      this->matches_capacity *= 2;
      this->matches = (match *)
         realloc(this->matches,
                 sizeof(*this->matches) * this->matches_capacity);
   }

   const ir_variable *const var = (producer_var != NULL)
      ? producer_var : consumer_var;

   this->matches[this->num_matches].packing_class
      = this->compute_packing_class(var);
   this->matches[this->num_matches].packing_order
      = this->compute_packing_order(var);
   if (this->disable_varying_packing) {
      unsigned slots = var->type->is_array()
         ? (var->type->length * var->type->fields.array->matrix_columns)
         : var->type->matrix_columns;
      this->matches[this->num_matches].num_components = 4 * slots;
   } else {
      this->matches[this->num_matches].num_components
         = var->type->component_slots();
   }
   this->matches[this->num_matches].producer_var = producer_var;
   this->matches[this->num_matches].consumer_var = consumer_var;
   this->num_matches++;
   if (producer_var)
      producer_var->data.is_unmatched_generic_inout = 0;
   if (consumer_var)
      consumer_var->data.is_unmatched_generic_inout = 0;
}


/**
 * Choose locations for all of the variable matches that were previously
 * passed to varying_matches::record().
 */
unsigned
varying_matches::assign_locations()
{
   /* Sort varying matches into an order that makes them easy to pack. */
   qsort(this->matches, this->num_matches, sizeof(*this->matches),
         &varying_matches::match_comparator);

   unsigned generic_location = 0;

   for (unsigned i = 0; i < this->num_matches; i++) {
      /* Advance to the next slot if this varying has a different packing
       * class than the previous one, and we're not already on a slot
       * boundary.
       */
      if (i > 0 &&
          this->matches[i - 1].packing_class
          != this->matches[i].packing_class) {
         generic_location = ALIGN(generic_location, 4);
      }

      this->matches[i].generic_location = generic_location;

      generic_location += this->matches[i].num_components;
   }

   return (generic_location + 3) / 4;
}


/**
 * Update the producer and consumer shaders to reflect the locations
 * assignments that were made by varying_matches::assign_locations().
 */
void
varying_matches::store_locations() const
{
   for (unsigned i = 0; i < this->num_matches; i++) {
      ir_variable *producer_var = this->matches[i].producer_var;
      ir_variable *consumer_var = this->matches[i].consumer_var;
      unsigned generic_location = this->matches[i].generic_location;
      unsigned slot = generic_location / 4;
      unsigned offset = generic_location % 4;

      if (producer_var) {
         producer_var->data.location = VARYING_SLOT_VAR0 + slot;
         producer_var->data.location_frac = offset;
      }

      if (consumer_var) {
         assert(consumer_var->data.location == -1);
         consumer_var->data.location = VARYING_SLOT_VAR0 + slot;
         consumer_var->data.location_frac = offset;
      }
   }
}


/**
 * Compute the "packing class" of the given varying.  This is an unsigned
 * integer with the property that two variables in the same packing class can
 * be safely backed into the same vec4.
 */
unsigned
varying_matches::compute_packing_class(const ir_variable *var)
{
   /* Without help from the back-end, there is no way to pack together
    * variables with different interpolation types, because
    * lower_packed_varyings must choose exactly one interpolation type for
    * each packed varying it creates.
    *
    * However, we can safely pack together floats, ints, and uints, because:
    *
    * - varyings of base type "int" and "uint" must use the "flat"
    *   interpolation type, which can only occur in GLSL 1.30 and above.
    *
    * - On platforms that support GLSL 1.30 and above, lower_packed_varyings
    *   can store flat floats as ints without losing any information (using
    *   the ir_unop_bitcast_* opcodes).
    *
    * Therefore, the packing class depends only on the interpolation type.
    */
   unsigned packing_class = var->data.centroid | (var->data.sample << 1);
   packing_class *= 4;
   packing_class += var->data.interpolation;
   return packing_class;
}


/**
 * Compute the "packing order" of the given varying.  This is a sort key we
 * use to determine when to attempt to pack the given varying relative to
 * other varyings in the same packing class.
 */
varying_matches::packing_order_enum
varying_matches::compute_packing_order(const ir_variable *var)
{
   const glsl_type *element_type = var->type;

   while (element_type->base_type == GLSL_TYPE_ARRAY) {
      element_type = element_type->fields.array;
   }

   switch (element_type->component_slots() % 4) {
   case 1: return PACKING_ORDER_SCALAR;
   case 2: return PACKING_ORDER_VEC2;
   case 3: return PACKING_ORDER_VEC3;
   case 0: return PACKING_ORDER_VEC4;
   default:
      assert(!"Unexpected value of vector_elements");
      return PACKING_ORDER_VEC4;
   }
}


/**
 * Comparison function passed to qsort() to sort varyings by packing_class and
 * then by packing_order.
 */
int
varying_matches::match_comparator(const void *x_generic, const void *y_generic)
{
   const match *x = (const match *) x_generic;
   const match *y = (const match *) y_generic;

   if (x->packing_class != y->packing_class)
      return x->packing_class - y->packing_class;
   return x->packing_order - y->packing_order;
}


/**
 * Is the given variable a varying variable to be counted against the
 * limit in ctx->Const.MaxVarying?
 * This includes variables such as texcoords, colors and generic
 * varyings, but excludes variables such as gl_FrontFacing and gl_FragCoord.
 */
static bool
var_counts_against_varying_limit(gl_shader_stage stage, const ir_variable *var)
{
   /* Only fragment shaders will take a varying variable as an input */
   if (stage == MESA_SHADER_FRAGMENT &&
       var->data.mode == ir_var_shader_in) {
      switch (var->data.location) {
      case VARYING_SLOT_POS:
      case VARYING_SLOT_FACE:
      case VARYING_SLOT_PNTC:
         return false;
      default:
         return true;
      }
   }
   return false;
}


/**
 * Visitor class that generates tfeedback_candidate structs describing all
 * possible targets of transform feedback.
 *
 * tfeedback_candidate structs are stored in the hash table
 * tfeedback_candidates, which is passed to the constructor.  This hash table
 * maps varying names to instances of the tfeedback_candidate struct.
 */
class tfeedback_candidate_generator : public program_resource_visitor
{
public:
   tfeedback_candidate_generator(void *mem_ctx,
                                 hash_table *tfeedback_candidates)
      : mem_ctx(mem_ctx),
        tfeedback_candidates(tfeedback_candidates),
        toplevel_var(NULL),
        varying_floats(0)
   {
   }

   void process(ir_variable *var)
   {
      this->toplevel_var = var;
      this->varying_floats = 0;
      if (var->is_interface_instance())
         program_resource_visitor::process(var->get_interface_type(),
                                           var->get_interface_type()->name);
      else
         program_resource_visitor::process(var);
   }

private:
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      assert(!type->without_array()->is_record());
      assert(!type->without_array()->is_interface());

      (void) row_major;

      tfeedback_candidate *candidate
         = rzalloc(this->mem_ctx, tfeedback_candidate);
      candidate->toplevel_var = this->toplevel_var;
      candidate->type = type;
      candidate->offset = this->varying_floats;
      hash_table_insert(this->tfeedback_candidates, candidate,
                        ralloc_strdup(this->mem_ctx, name));
      this->varying_floats += type->component_slots();
   }

   /**
    * Memory context used to allocate hash table keys and values.
    */
   void * const mem_ctx;

   /**
    * Hash table in which tfeedback_candidate objects should be stored.
    */
   hash_table * const tfeedback_candidates;

   /**
    * Pointer to the toplevel variable that is being traversed.
    */
   ir_variable *toplevel_var;

   /**
    * Total number of varying floats that have been visited so far.  This is
    * used to determine the offset to each varying within the toplevel
    * variable.
    */
   unsigned varying_floats;
};


namespace linker {

bool
populate_consumer_input_sets(void *mem_ctx, exec_list *ir,
                             hash_table *consumer_inputs,
                             hash_table *consumer_interface_inputs,
                             ir_variable *consumer_inputs_with_locations[VARYING_SLOT_MAX])
{
   memset(consumer_inputs_with_locations,
          0,
          sizeof(consumer_inputs_with_locations[0]) * VARYING_SLOT_MAX);

   foreach_in_list(ir_instruction, node, ir) {
      ir_variable *const input_var = node->as_variable();

      if ((input_var != NULL) && (input_var->data.mode == ir_var_shader_in)) {
         if (input_var->type->is_interface())
            return false;

         if (input_var->data.explicit_location) {
            /* assign_varying_locations only cares about finding the
             * ir_variable at the start of a contiguous location block.
             *
             *     - For !producer, consumer_inputs_with_locations isn't used.
             *
             *     - For !consumer, consumer_inputs_with_locations is empty.
             *
             * For consumer && producer, if you were trying to set some
             * ir_variable to the middle of a location block on the other side
             * of producer/consumer, cross_validate_outputs_to_inputs() should
             * be link-erroring due to either type mismatch or location
             * overlaps.  If the variables do match up, then they've got a
             * matching data.location and you only looked at
             * consumer_inputs_with_locations[var->data.location], not any
             * following entries for the array/structure.
             */
            consumer_inputs_with_locations[input_var->data.location] =
               input_var;
         } else if (input_var->get_interface_type() != NULL) {
            char *const iface_field_name =
               ralloc_asprintf(mem_ctx, "%s.%s",
                               input_var->get_interface_type()->name,
                               input_var->name);
            hash_table_insert(consumer_interface_inputs, input_var,
                              iface_field_name);
         } else {
            hash_table_insert(consumer_inputs, input_var,
                              ralloc_strdup(mem_ctx, input_var->name));
         }
      }
   }

   return true;
}

/**
 * Find a variable from the consumer that "matches" the specified variable
 *
 * This function only finds inputs with names that match.  There is no
 * validation (here) that the types, etc. are compatible.
 */
ir_variable *
get_matching_input(void *mem_ctx,
                   const ir_variable *output_var,
                   hash_table *consumer_inputs,
                   hash_table *consumer_interface_inputs,
                   ir_variable *consumer_inputs_with_locations[VARYING_SLOT_MAX])
{
   ir_variable *input_var;

   if (output_var->data.explicit_location) {
      input_var = consumer_inputs_with_locations[output_var->data.location];
   } else if (output_var->get_interface_type() != NULL) {
      char *const iface_field_name =
         ralloc_asprintf(mem_ctx, "%s.%s",
                         output_var->get_interface_type()->name,
                         output_var->name);
      input_var =
         (ir_variable *) hash_table_find(consumer_interface_inputs,
                                         iface_field_name);
   } else {
      input_var =
         (ir_variable *) hash_table_find(consumer_inputs, output_var->name);
   }

   return (input_var == NULL || input_var->data.mode != ir_var_shader_in)
      ? NULL : input_var;
}

}

static int
io_variable_cmp(const void *_a, const void *_b)
{
   const ir_variable *const a = *(const ir_variable **) _a;
   const ir_variable *const b = *(const ir_variable **) _b;

   if (a->data.explicit_location && b->data.explicit_location)
      return b->data.location - a->data.location;

   if (a->data.explicit_location && !b->data.explicit_location)
      return 1;

   if (!a->data.explicit_location && b->data.explicit_location)
      return -1;

   return -strcmp(a->name, b->name);
}

/**
 * Sort the shader IO variables into canonical order
 */
static void
canonicalize_shader_io(exec_list *ir, enum ir_variable_mode io_mode)
{
   ir_variable *var_table[MAX_PROGRAM_OUTPUTS * 4];
   unsigned num_variables = 0;

   foreach_in_list(ir_instruction, node, ir) {
      ir_variable *const var = node->as_variable();

      if (var == NULL || var->data.mode != io_mode)
         continue;

      /* If we have already encountered more I/O variables that could
       * successfully link, bail.
       */
      if (num_variables == ARRAY_SIZE(var_table))
         return;

      var_table[num_variables++] = var;
   }

   if (num_variables == 0)
      return;

   /* Sort the list in reverse order (io_variable_cmp handles this).  Later
    * we're going to push the variables on to the IR list as a stack, so we
    * want the last variable (in canonical order) to be first in the list.
    */
   qsort(var_table, num_variables, sizeof(var_table[0]), io_variable_cmp);

   /* Remove the variable from it's current location in the IR, and put it at
    * the front.
    */
   for (unsigned i = 0; i < num_variables; i++) {
      var_table[i]->remove();
      ir->push_head(var_table[i]);
   }
}

/**
 * Assign locations for all variables that are produced in one pipeline stage
 * (the "producer") and consumed in the next stage (the "consumer").
 *
 * Variables produced by the producer may also be consumed by transform
 * feedback.
 *
 * \param num_tfeedback_decls is the number of declarations indicating
 *        variables that may be consumed by transform feedback.
 *
 * \param tfeedback_decls is a pointer to an array of tfeedback_decl objects
 *        representing the result of parsing the strings passed to
 *        glTransformFeedbackVaryings().  assign_location() will be called for
 *        each of these objects that matches one of the outputs of the
 *        producer.
 *
 * \param gs_input_vertices: if \c consumer is a geometry shader, this is the
 *        number of input vertices it accepts.  Otherwise zero.
 *
 * When num_tfeedback_decls is nonzero, it is permissible for the consumer to
 * be NULL.  In this case, varying locations are assigned solely based on the
 * requirements of transform feedback.
 */
bool
assign_varying_locations(struct gl_context *ctx,
			 void *mem_ctx,
			 struct gl_shader_program *prog,
			 gl_shader *producer, gl_shader *consumer,
                         unsigned num_tfeedback_decls,
                         tfeedback_decl *tfeedback_decls,
                         unsigned gs_input_vertices)
{
   varying_matches matches(!!ctx->Const.DisableVaryingPacking,
                           consumer && consumer->Stage == MESA_SHADER_FRAGMENT);
   hash_table *tfeedback_candidates
      = hash_table_ctor(0, hash_table_string_hash, hash_table_string_compare);
   hash_table *consumer_inputs
      = hash_table_ctor(0, hash_table_string_hash, hash_table_string_compare);
   hash_table *consumer_interface_inputs
      = hash_table_ctor(0, hash_table_string_hash, hash_table_string_compare);
   ir_variable *consumer_inputs_with_locations[VARYING_SLOT_MAX] = {
      NULL,
   };

   /* Operate in a total of four passes.
    *
    * 1. Sort inputs / outputs into a canonical order.  This is necessary so
    *    that inputs / outputs of separable shaders will be assigned
    *    predictable locations regardless of the order in which declarations
    *    appeared in the shader source.
    *
    * 2. Assign locations for any matching inputs and outputs.
    *
    * 3. Mark output variables in the producer that do not have locations as
    *    not being outputs.  This lets the optimizer eliminate them.
    *
    * 4. Mark input variables in the consumer that do not have locations as
    *    not being inputs.  This lets the optimizer eliminate them.
    */
   if (consumer)
      canonicalize_shader_io(consumer->ir, ir_var_shader_in);

   if (producer)
      canonicalize_shader_io(producer->ir, ir_var_shader_out);

   if (consumer
       && !linker::populate_consumer_input_sets(mem_ctx,
                                                consumer->ir,
                                                consumer_inputs,
                                                consumer_interface_inputs,
                                                consumer_inputs_with_locations)) {
      assert(!"populate_consumer_input_sets failed");
      hash_table_dtor(tfeedback_candidates);
      hash_table_dtor(consumer_inputs);
      hash_table_dtor(consumer_interface_inputs);
      return false;
   }

   if (producer) {
      foreach_in_list(ir_instruction, node, producer->ir) {
         ir_variable *const output_var = node->as_variable();

         if ((output_var == NULL) ||
             (output_var->data.mode != ir_var_shader_out))
            continue;

         /* Only geometry shaders can use non-zero streams */
         assert(output_var->data.stream == 0 ||
                (output_var->data.stream < MAX_VERTEX_STREAMS &&
                 producer->Stage == MESA_SHADER_GEOMETRY));

         tfeedback_candidate_generator g(mem_ctx, tfeedback_candidates);
         g.process(output_var);

         ir_variable *const input_var =
            linker::get_matching_input(mem_ctx, output_var, consumer_inputs,
                                       consumer_interface_inputs,
                                       consumer_inputs_with_locations);

         /* If a matching input variable was found, add this ouptut (and the
          * input) to the set.  If this is a separable program and there is no
          * consumer stage, add the output.
          */
         if (input_var || (prog->SeparateShader && consumer == NULL)) {
            matches.record(output_var, input_var);
         }

         /* Only stream 0 outputs can be consumed in the next stage */
         if (input_var && output_var->data.stream != 0) {
            linker_error(prog, "output %s is assigned to stream=%d but "
                         "is linked to an input, which requires stream=0",
                         output_var->name, output_var->data.stream);
            return false;
         }
      }
   } else {
      /* If there's no producer stage, then this must be a separable program.
       * For example, we may have a program that has just a fragment shader.
       * Later this program will be used with some arbitrary vertex (or
       * geometry) shader program.  This means that locations must be assigned
       * for all the inputs.
       */
      foreach_in_list(ir_instruction, node, consumer->ir) {
         ir_variable *const input_var = node->as_variable();

         if ((input_var == NULL) ||
             (input_var->data.mode != ir_var_shader_in))
            continue;

         matches.record(NULL, input_var);
      }
   }

   for (unsigned i = 0; i < num_tfeedback_decls; ++i) {
      if (!tfeedback_decls[i].is_varying())
         continue;

      const tfeedback_candidate *matched_candidate
         = tfeedback_decls[i].find_candidate(prog, tfeedback_candidates);

      if (matched_candidate == NULL) {
         hash_table_dtor(tfeedback_candidates);
         hash_table_dtor(consumer_inputs);
         hash_table_dtor(consumer_interface_inputs);
         return false;
      }

      if (matched_candidate->toplevel_var->data.is_unmatched_generic_inout)
         matches.record(matched_candidate->toplevel_var, NULL);
   }

   const unsigned slots_used = matches.assign_locations();
   matches.store_locations();

   for (unsigned i = 0; i < num_tfeedback_decls; ++i) {
      if (!tfeedback_decls[i].is_varying())
         continue;

      if (!tfeedback_decls[i].assign_location(ctx, prog)) {
         hash_table_dtor(tfeedback_candidates);
         hash_table_dtor(consumer_inputs);
         hash_table_dtor(consumer_interface_inputs);
         return false;
      }
   }

   hash_table_dtor(tfeedback_candidates);
   hash_table_dtor(consumer_inputs);
   hash_table_dtor(consumer_interface_inputs);

   if (ctx->Const.DisableVaryingPacking) {
      /* Transform feedback code assumes varyings are packed, so if the driver
       * has disabled varying packing, make sure it does not support transform
       * feedback.
       */
      assert(!ctx->Extensions.EXT_transform_feedback);
   } else {
      if (producer) {
         lower_packed_varyings(mem_ctx, slots_used, ir_var_shader_out,
                               0, producer);
      }
      if (consumer) {
         lower_packed_varyings(mem_ctx, slots_used, ir_var_shader_in,
                               gs_input_vertices, consumer);
      }
   }

   if (consumer && producer) {
      foreach_in_list(ir_instruction, node, consumer->ir) {
         ir_variable *const var = node->as_variable();

         if (var && var->data.mode == ir_var_shader_in &&
             var->data.is_unmatched_generic_inout) {
            if (prog->IsES) {
               /*
                * On Page 91 (Page 97 of the PDF) of the GLSL ES 1.0 spec:
                *
                *     If the vertex shader declares but doesn't write to a
                *     varying and the fragment shader declares and reads it,
                *     is this an error?
                *
                *     RESOLUTION: No.
                */
               linker_warning(prog, "%s shader varying %s not written "
                              "by %s shader\n.",
                              _mesa_shader_stage_to_string(consumer->Stage),
                              var->name,
                              _mesa_shader_stage_to_string(producer->Stage));
            } else if (prog->Version <= 120) {
               /* On page 25 (page 31 of the PDF) of the GLSL 1.20 spec:
                *
                *     Only those varying variables used (i.e. read) in
                *     the fragment shader executable must be written to
                *     by the vertex shader executable; declaring
                *     superfluous varying variables in a vertex shader is
                *     permissible.
                *
                * We interpret this text as meaning that the VS must
                * write the variable for the FS to read it.  See
                * "glsl1-varying read but not written" in piglit.
                */
               linker_error(prog, "%s shader varying %s not written "
                            "by %s shader\n.",
                            _mesa_shader_stage_to_string(consumer->Stage),
			    var->name,
                            _mesa_shader_stage_to_string(producer->Stage));
            }

            /* An 'in' variable is only really a shader input if its
             * value is written by the previous stage.
             */
            var->data.mode = ir_var_auto;
         }
      }
   }

   return true;
}

bool
check_against_output_limit(struct gl_context *ctx,
                           struct gl_shader_program *prog,
                           gl_shader *producer)
{
   unsigned output_vectors = 0;

   foreach_in_list(ir_instruction, node, producer->ir) {
      ir_variable *const var = node->as_variable();

      if (var && var->data.mode == ir_var_shader_out &&
          var_counts_against_varying_limit(producer->Stage, var)) {
         output_vectors += var->type->count_attribute_slots();
      }
   }

   assert(producer->Stage != MESA_SHADER_FRAGMENT);
   unsigned max_output_components =
      ctx->Const.Program[producer->Stage].MaxOutputComponents;

   const unsigned output_components = output_vectors * 4;
   if (output_components > max_output_components) {
      if (ctx->API == API_OPENGLES2 || prog->IsES)
         linker_error(prog, "shader uses too many output vectors "
                      "(%u > %u)\n",
                      output_vectors,
                      max_output_components / 4);
      else
         linker_error(prog, "shader uses too many output components "
                      "(%u > %u)\n",
                      output_components,
                      max_output_components);

      return false;
   }

   return true;
}

bool
check_against_input_limit(struct gl_context *ctx,
                          struct gl_shader_program *prog,
                          gl_shader *consumer)
{
   unsigned input_vectors = 0;

   foreach_in_list(ir_instruction, node, consumer->ir) {
      ir_variable *const var = node->as_variable();

      if (var && var->data.mode == ir_var_shader_in &&
          var_counts_against_varying_limit(consumer->Stage, var)) {
         input_vectors += var->type->count_attribute_slots();
      }
   }

   assert(consumer->Stage != MESA_SHADER_VERTEX);
   unsigned max_input_components =
      ctx->Const.Program[consumer->Stage].MaxInputComponents;

   const unsigned input_components = input_vectors * 4;
   if (input_components > max_input_components) {
      if (ctx->API == API_OPENGLES2 || prog->IsES)
         linker_error(prog, "shader uses too many input vectors "
                      "(%u > %u)\n",
                      input_vectors,
                      max_input_components / 4);
      else
         linker_error(prog, "shader uses too many input components "
                      "(%u > %u)\n",
                      input_components,
                      max_input_components);

      return false;
   }

   return true;
}

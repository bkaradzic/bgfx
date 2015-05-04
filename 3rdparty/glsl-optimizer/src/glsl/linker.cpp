/*
 * Copyright © 2010 Intel Corporation
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
 * \file linker.cpp
 * GLSL linker implementation
 *
 * Given a set of shaders that are to be linked to generate a final program,
 * there are three distinct stages.
 *
 * In the first stage shaders are partitioned into groups based on the shader
 * type.  All shaders of a particular type (e.g., vertex shaders) are linked
 * together.
 *
 *   - Undefined references in each shader are resolve to definitions in
 *     another shader.
 *   - Types and qualifiers of uniforms, outputs, and global variables defined
 *     in multiple shaders with the same name are verified to be the same.
 *   - Initializers for uniforms and global variables defined
 *     in multiple shaders with the same name are verified to be the same.
 *
 * The result, in the terminology of the GLSL spec, is a set of shader
 * executables for each processing unit.
 *
 * After the first stage is complete, a series of semantic checks are performed
 * on each of the shader executables.
 *
 *   - Each shader executable must define a \c main function.
 *   - Each vertex shader executable must write to \c gl_Position.
 *   - Each fragment shader executable must write to either \c gl_FragData or
 *     \c gl_FragColor.
 *
 * In the final stage individual shader executables are linked to create a
 * complete exectuable.
 *
 *   - Types of uniforms defined in multiple shader stages with the same name
 *     are verified to be the same.
 *   - Initializers for uniforms defined in multiple shader stages with the
 *     same name are verified to be the same.
 *   - Types and qualifiers of outputs defined in one stage are verified to
 *     be the same as the types and qualifiers of inputs defined with the same
 *     name in a later stage.
 *
 * \author Ian Romanick <ian.d.romanick@intel.com>
 */

#include "main/core.h"
#include "main/errors.h"
#include "glsl_symbol_table.h"
#include "glsl_parser_extras.h"
#include "ir.h"
#include "program.h"
#include "program/hash_table.h"
#include "linker.h"
#include "link_varyings.h"
#include "ir_optimization.h"
#include "ir_rvalue_visitor.h"
#include "ir_uniform.h"

extern "C" {
#include "standalone_scaffolding.h"
}

void linker_error(gl_shader_program *, const char *, ...);

namespace {

/**
 * Visitor that determines whether or not a variable is ever written.
 */
class find_assignment_visitor : public ir_hierarchical_visitor {
public:
   find_assignment_visitor(const char *name)
      : name(name), found(false)
   {
      /* empty */
   }

   virtual ir_visitor_status visit_enter(ir_assignment *ir)
   {
      ir_variable *const var = ir->lhs->variable_referenced();

      if (strcmp(name, var->name) == 0) {
	 found = true;
	 return visit_stop;
      }

      return visit_continue_with_parent;
   }

   virtual ir_visitor_status visit_enter(ir_call *ir)
   {
      foreach_two_lists(formal_node, &ir->callee->parameters,
                        actual_node, &ir->actual_parameters) {
	 ir_rvalue *param_rval = (ir_rvalue *) actual_node;
	 ir_variable *sig_param = (ir_variable *) formal_node;

	 if (sig_param->data.mode == ir_var_function_out ||
	     sig_param->data.mode == ir_var_function_inout) {
	    ir_variable *var = param_rval->variable_referenced();
	    if (var && strcmp(name, var->name) == 0) {
	       found = true;
	       return visit_stop;
	    }
	 }
      }

      if (ir->return_deref != NULL) {
	 ir_variable *const var = ir->return_deref->variable_referenced();

	 if (strcmp(name, var->name) == 0) {
	    found = true;
	    return visit_stop;
	 }
      }

      return visit_continue_with_parent;
   }

   bool variable_found()
   {
      return found;
   }

private:
   const char *name;       /**< Find writes to a variable with this name. */
   bool found;             /**< Was a write to the variable found? */
};


/**
 * Visitor that determines whether or not a variable is ever read.
 */
class find_deref_visitor : public ir_hierarchical_visitor {
public:
   find_deref_visitor(const char *name)
      : name(name), found(false)
   {
      /* empty */
   }

   virtual ir_visitor_status visit(ir_dereference_variable *ir)
   {
      if (strcmp(this->name, ir->var->name) == 0) {
	 this->found = true;
	 return visit_stop;
      }

      return visit_continue;
   }

   bool variable_found() const
   {
      return this->found;
   }

private:
   const char *name;       /**< Find writes to a variable with this name. */
   bool found;             /**< Was a write to the variable found? */
};


class geom_array_resize_visitor : public ir_hierarchical_visitor {
public:
   unsigned num_vertices;
   gl_shader_program *prog;

   geom_array_resize_visitor(unsigned num_vertices, gl_shader_program *prog)
   {
      this->num_vertices = num_vertices;
      this->prog = prog;
   }

   virtual ~geom_array_resize_visitor()
   {
      /* empty */
   }

   virtual ir_visitor_status visit(ir_variable *var)
   {
      if (!var->type->is_array() || var->data.mode != ir_var_shader_in)
         return visit_continue;

      unsigned size = var->type->length;

      /* Generate a link error if the shader has declared this array with an
       * incorrect size.
       */
      if (size && size != this->num_vertices) {
         linker_error(this->prog, "size of array %s declared as %u, "
                      "but number of input vertices is %u\n",
                      var->name, size, this->num_vertices);
         return visit_continue;
      }

      /* Generate a link error if the shader attempts to access an input
       * array using an index too large for its actual size assigned at link
       * time.
       */
      if (var->data.max_array_access >= this->num_vertices) {
         linker_error(this->prog, "geometry shader accesses element %i of "
                      "%s, but only %i input vertices\n",
                      var->data.max_array_access, var->name, this->num_vertices);
         return visit_continue;
      }

      var->type = glsl_type::get_array_instance(var->type->element_type(),
                                                this->num_vertices);
      var->data.max_array_access = this->num_vertices - 1;

      return visit_continue;
   }

   /* Dereferences of input variables need to be updated so that their type
    * matches the newly assigned type of the variable they are accessing. */
   virtual ir_visitor_status visit(ir_dereference_variable *ir)
   {
      ir->type = ir->var->type;
      return visit_continue;
   }

   /* Dereferences of 2D input arrays need to be updated so that their type
    * matches the newly assigned type of the array they are accessing. */
   virtual ir_visitor_status visit_leave(ir_dereference_array *ir)
   {
      const glsl_type *const vt = ir->array->type;
      if (vt->is_array())
         ir->type = vt->element_type();
      return visit_continue;
   }
};

/**
 * Visitor that determines the highest stream id to which a (geometry) shader
 * emits vertices. It also checks whether End{Stream}Primitive is ever called.
 */
class find_emit_vertex_visitor : public ir_hierarchical_visitor {
public:
   find_emit_vertex_visitor(int max_allowed)
      : max_stream_allowed(max_allowed),
        invalid_stream_id(0),
        invalid_stream_id_from_emit_vertex(false),
        end_primitive_found(false),
        uses_non_zero_stream(false)
   {
      /* empty */
   }

   virtual ir_visitor_status visit_leave(ir_emit_vertex *ir)
   {
      int stream_id = ir->stream_id();

      if (stream_id < 0) {
         invalid_stream_id = stream_id;
         invalid_stream_id_from_emit_vertex = true;
         return visit_stop;
      }

      if (stream_id > max_stream_allowed) {
         invalid_stream_id = stream_id;
         invalid_stream_id_from_emit_vertex = true;
         return visit_stop;
      }

      if (stream_id != 0)
         uses_non_zero_stream = true;

      return visit_continue;
   }

   virtual ir_visitor_status visit_leave(ir_end_primitive *ir)
   {
      end_primitive_found = true;

      int stream_id = ir->stream_id();

      if (stream_id < 0) {
         invalid_stream_id = stream_id;
         invalid_stream_id_from_emit_vertex = false;
         return visit_stop;
      }

      if (stream_id > max_stream_allowed) {
         invalid_stream_id = stream_id;
         invalid_stream_id_from_emit_vertex = false;
         return visit_stop;
      }

      if (stream_id != 0)
         uses_non_zero_stream = true;

      return visit_continue;
   }

   bool error()
   {
      return invalid_stream_id != 0;
   }

   const char *error_func()
   {
      return invalid_stream_id_from_emit_vertex ?
         "EmitStreamVertex" : "EndStreamPrimitive";
   }

   int error_stream()
   {
      return invalid_stream_id;
   }

   bool uses_streams()
   {
      return uses_non_zero_stream;
   }

   bool uses_end_primitive()
   {
      return end_primitive_found;
   }

private:
   int max_stream_allowed;
   int invalid_stream_id;
   bool invalid_stream_id_from_emit_vertex;
   bool end_primitive_found;
   bool uses_non_zero_stream;
};

} /* anonymous namespace */

void
linker_error(gl_shader_program *prog, const char *fmt, ...)
{
   va_list ap;

   ralloc_strcat(&prog->InfoLog, "error: ");
   va_start(ap, fmt);
   ralloc_vasprintf_append(&prog->InfoLog, fmt, ap);
   va_end(ap);

   prog->LinkStatus = false;
}


void
linker_warning(gl_shader_program *prog, const char *fmt, ...)
{
   va_list ap;

   ralloc_strcat(&prog->InfoLog, "warning: ");
   va_start(ap, fmt);
   ralloc_vasprintf_append(&prog->InfoLog, fmt, ap);
   va_end(ap);

}


/**
 * Given a string identifying a program resource, break it into a base name
 * and an optional array index in square brackets.
 *
 * If an array index is present, \c out_base_name_end is set to point to the
 * "[" that precedes the array index, and the array index itself is returned
 * as a long.
 *
 * If no array index is present (or if the array index is negative or
 * mal-formed), \c out_base_name_end, is set to point to the null terminator
 * at the end of the input string, and -1 is returned.
 *
 * Only the final array index is parsed; if the string contains other array
 * indices (or structure field accesses), they are left in the base name.
 *
 * No attempt is made to check that the base name is properly formed;
 * typically the caller will look up the base name in a hash table, so
 * ill-formed base names simply turn into hash table lookup failures.
 */
long
parse_program_resource_name(const GLchar *name,
                            const GLchar **out_base_name_end)
{
   /* Section 7.3.1 ("Program Interfaces") of the OpenGL 4.3 spec says:
    *
    *     "When an integer array element or block instance number is part of
    *     the name string, it will be specified in decimal form without a "+"
    *     or "-" sign or any extra leading zeroes. Additionally, the name
    *     string will not include white space anywhere in the string."
    */

   const size_t len = strlen(name);
   *out_base_name_end = name + len;

   if (len == 0 || name[len-1] != ']')
      return -1;

   /* Walk backwards over the string looking for a non-digit character.  This
    * had better be the opening bracket for an array index.
    *
    * Initially, i specifies the location of the ']'.  Since the string may
    * contain only the ']' charcater, walk backwards very carefully.
    */
   unsigned i;
   for (i = len - 1; (i > 0) && isdigit(name[i-1]); --i)
      /* empty */ ;

   if ((i == 0) || name[i-1] != '[')
      return -1;

   long array_index = strtol(&name[i], NULL, 10);
   if (array_index < 0)
      return -1;

   *out_base_name_end = name + (i - 1);
   return array_index;
}


void
link_invalidate_variable_locations(exec_list *ir)
{
   foreach_in_list(ir_instruction, node, ir) {
      ir_variable *const var = node->as_variable();

      if (var == NULL)
         continue;

      /* Only assign locations for variables that lack an explicit location.
       * Explicit locations are set for all built-in variables, generic vertex
       * shader inputs (via layout(location=...)), and generic fragment shader
       * outputs (also via layout(location=...)).
       */
      if (!var->data.explicit_location) {
         var->data.location = -1;
         var->data.location_frac = 0;
      }

      /* ir_variable::is_unmatched_generic_inout is used by the linker while
       * connecting outputs from one stage to inputs of the next stage.
       *
       * There are two implicit assumptions here.  First, we assume that any
       * built-in variable (i.e., non-generic in or out) will have
       * explicit_location set.  Second, we assume that any generic in or out
       * will not have explicit_location set.
       *
       * This second assumption will only be valid until
       * GL_ARB_separate_shader_objects is supported.  When that extension is
       * implemented, this function will need some modifications.
       */
      if (!var->data.explicit_location) {
         var->data.is_unmatched_generic_inout = 1;
      } else {
         var->data.is_unmatched_generic_inout = 0;
      }
   }
}


/**
 * Set UsesClipDistance and ClipDistanceArraySize based on the given shader.
 *
 * Also check for errors based on incorrect usage of gl_ClipVertex and
 * gl_ClipDistance.
 *
 * Return false if an error was reported.
 */
static void
analyze_clip_usage(struct gl_shader_program *prog,
                   struct gl_shader *shader, GLboolean *UsesClipDistance,
                   GLuint *ClipDistanceArraySize)
{
   *ClipDistanceArraySize = 0;

   if (!prog->IsES && prog->Version >= 130) {
      /* From section 7.1 (Vertex Shader Special Variables) of the
       * GLSL 1.30 spec:
       *
       *   "It is an error for a shader to statically write both
       *   gl_ClipVertex and gl_ClipDistance."
       *
       * This does not apply to GLSL ES shaders, since GLSL ES defines neither
       * gl_ClipVertex nor gl_ClipDistance.
       */
      find_assignment_visitor clip_vertex("gl_ClipVertex");
      find_assignment_visitor clip_distance("gl_ClipDistance");

      clip_vertex.run(shader->ir);
      clip_distance.run(shader->ir);
      if (clip_vertex.variable_found() && clip_distance.variable_found()) {
         linker_error(prog, "%s shader writes to both `gl_ClipVertex' "
                      "and `gl_ClipDistance'\n",
                      _mesa_shader_stage_to_string(shader->Stage));
         return;
      }
      *UsesClipDistance = clip_distance.variable_found();
      ir_variable *clip_distance_var =
         shader->symbols->get_variable("gl_ClipDistance");
      if (clip_distance_var)
         *ClipDistanceArraySize = clip_distance_var->type->length;
   } else {
      *UsesClipDistance = false;
   }
}


/**
 * Verify that a vertex shader executable meets all semantic requirements.
 *
 * Also sets prog->Vert.UsesClipDistance and prog->Vert.ClipDistanceArraySize
 * as a side effect.
 *
 * \param shader  Vertex shader executable to be verified
 */
void
validate_vertex_shader_executable(struct gl_shader_program *prog,
				  struct gl_shader *shader)
{
   if (shader == NULL)
      return;

   /* From the GLSL 1.10 spec, page 48:
    *
    *     "The variable gl_Position is available only in the vertex
    *      language and is intended for writing the homogeneous vertex
    *      position. All executions of a well-formed vertex shader
    *      executable must write a value into this variable. [...] The
    *      variable gl_Position is available only in the vertex
    *      language and is intended for writing the homogeneous vertex
    *      position. All executions of a well-formed vertex shader
    *      executable must write a value into this variable."
    *
    * while in GLSL 1.40 this text is changed to:
    *
    *     "The variable gl_Position is available only in the vertex
    *      language and is intended for writing the homogeneous vertex
    *      position. It can be written at any time during shader
    *      execution. It may also be read back by a vertex shader
    *      after being written. This value will be used by primitive
    *      assembly, clipping, culling, and other fixed functionality
    *      operations, if present, that operate on primitives after
    *      vertex processing has occurred. Its value is undefined if
    *      the vertex shader executable does not write gl_Position."
    *
    * All GLSL ES Versions are similar to GLSL 1.40--failing to write to
    * gl_Position is not an error.
    */
   if (prog->Version < (prog->IsES ? 300U : 140U)) {
      find_assignment_visitor find("gl_Position");
      find.run(shader->ir);
      if (!find.variable_found()) {
        if (prog->IsES) {
          linker_warning(prog,
                         "vertex shader does not write to `gl_Position'."
                         "It's value is undefined. \n");
        } else {
          linker_error(prog,
                       "vertex shader does not write to `gl_Position'. \n");
        }
	 return;
      }
   }

   analyze_clip_usage(prog, shader, &prog->Vert.UsesClipDistance,
                      &prog->Vert.ClipDistanceArraySize);
}


/**
 * Verify that a fragment shader executable meets all semantic requirements
 *
 * \param shader  Fragment shader executable to be verified
 */
void
validate_fragment_shader_executable(struct gl_shader_program *prog,
				    struct gl_shader *shader)
{
   if (shader == NULL)
      return;

   find_assignment_visitor frag_color("gl_FragColor");
   find_assignment_visitor frag_data("gl_FragData");

   frag_color.run(shader->ir);
   frag_data.run(shader->ir);

   if (frag_color.variable_found() && frag_data.variable_found()) {
      linker_error(prog,  "fragment shader writes to both "
		   "`gl_FragColor' and `gl_FragData'\n");
   }
}

/**
 * Verify that a geometry shader executable meets all semantic requirements
 *
 * Also sets prog->Geom.VerticesIn, prog->Geom.UsesClipDistance, and
 * prog->Geom.ClipDistanceArraySize as a side effect.
 *
 * \param shader Geometry shader executable to be verified
 */
void
validate_geometry_shader_executable(struct gl_shader_program *prog,
				    struct gl_shader *shader)
{
   if (shader == NULL)
      return;

   unsigned num_vertices = vertices_per_prim(prog->Geom.InputType);
   prog->Geom.VerticesIn = num_vertices;

   analyze_clip_usage(prog, shader, &prog->Geom.UsesClipDistance,
                      &prog->Geom.ClipDistanceArraySize);
}

/**
 * Check if geometry shaders emit to non-zero streams and do corresponding
 * validations.
 */
static void
validate_geometry_shader_emissions(struct gl_context *ctx,
                                   struct gl_shader_program *prog)
{
   if (prog->_LinkedShaders[MESA_SHADER_GEOMETRY] != NULL) {
      find_emit_vertex_visitor emit_vertex(ctx->Const.MaxVertexStreams - 1);
      emit_vertex.run(prog->_LinkedShaders[MESA_SHADER_GEOMETRY]->ir);
      if (emit_vertex.error()) {
         linker_error(prog, "Invalid call %s(%d). Accepted values for the "
                      "stream parameter are in the range [0, %d].",
                      emit_vertex.error_func(),
                      emit_vertex.error_stream(),
                      ctx->Const.MaxVertexStreams - 1);
      }
      prog->Geom.UsesStreams = emit_vertex.uses_streams();
      prog->Geom.UsesEndPrimitive = emit_vertex.uses_end_primitive();

      /* From the ARB_gpu_shader5 spec:
       *
       *   "Multiple vertex streams are supported only if the output primitive
       *    type is declared to be "points".  A program will fail to link if it
       *    contains a geometry shader calling EmitStreamVertex() or
       *    EndStreamPrimitive() if its output primitive type is not "points".
       *
       * However, in the same spec:
       *
       *   "The function EmitVertex() is equivalent to calling EmitStreamVertex()
       *    with <stream> set to zero."
       *
       * And:
       *
       *   "The function EndPrimitive() is equivalent to calling
       *    EndStreamPrimitive() with <stream> set to zero."
       *
       * Since we can call EmitVertex() and EndPrimitive() when we output
       * primitives other than points, calling EmitStreamVertex(0) or
       * EmitEndPrimitive(0) should not produce errors. This it also what Nvidia
       * does. Currently we only set prog->Geom.UsesStreams to TRUE when
       * EmitStreamVertex() or EmitEndPrimitive() are called with a non-zero
       * stream.
       */
      if (prog->Geom.UsesStreams && prog->Geom.OutputType != GL_POINTS) {
         linker_error(prog, "EmitStreamVertex(n) and EndStreamPrimitive(n) "
                      "with n>0 requires point output");
      }
   }
}


/**
 * Perform validation of global variables used across multiple shaders
 */
void
cross_validate_globals(struct gl_shader_program *prog,
		       struct gl_shader **shader_list,
		       unsigned num_shaders,
		       bool uniforms_only)
{
   /* Examine all of the uniforms in all of the shaders and cross validate
    * them.
    */
   glsl_symbol_table variables;
   for (unsigned i = 0; i < num_shaders; i++) {
      if (shader_list[i] == NULL)
	 continue;

      foreach_in_list(ir_instruction, node, shader_list[i]->ir) {
	 ir_variable *const var = node->as_variable();

	 if (var == NULL)
	    continue;

	 if (uniforms_only && (var->data.mode != ir_var_uniform))
	    continue;

	 /* Don't cross validate temporaries that are at global scope.  These
	  * will eventually get pulled into the shaders 'main'.
	  */
	 if (var->data.mode == ir_var_temporary)
	    continue;

	 /* If a global with this name has already been seen, verify that the
	  * new instance has the same type.  In addition, if the globals have
	  * initializers, the values of the initializers must be the same.
	  */
	 ir_variable *const existing = variables.get_variable(var->name);
	 if (existing != NULL) {
	    if (var->type != existing->type) {
	       /* Consider the types to be "the same" if both types are arrays
		* of the same type and one of the arrays is implicitly sized.
		* In addition, set the type of the linked variable to the
		* explicitly sized array.
		*/
	       if (var->type->is_array()
		   && existing->type->is_array()
		   && (var->type->fields.array == existing->type->fields.array)
		   && ((var->type->length == 0)
		       || (existing->type->length == 0))) {
		  if (var->type->length != 0) {
		     existing->type = var->type;
		  }
               } else if (var->type->is_record()
		   && existing->type->is_record()
		   && existing->type->record_compare(var->type)) {
		  existing->type = var->type;
	       } else {
		  linker_error(prog, "%s `%s' declared as type "
			       "`%s' and type `%s'\n",
			       mode_string(var),
			       var->name, var->type->name,
			       existing->type->name);
		  return;
	       }
	    }

	    if (var->data.explicit_location) {
	       if (existing->data.explicit_location
		   && (var->data.location != existing->data.location)) {
		     linker_error(prog, "explicit locations for %s "
				  "`%s' have differing values\n",
				  mode_string(var), var->name);
		     return;
	       }

	       existing->data.location = var->data.location;
	       existing->data.explicit_location = true;
	    }

            /* From the GLSL 4.20 specification:
             * "A link error will result if two compilation units in a program
             *  specify different integer-constant bindings for the same
             *  opaque-uniform name.  However, it is not an error to specify a
             *  binding on some but not all declarations for the same name"
             */
            if (var->data.explicit_binding) {
               if (existing->data.explicit_binding &&
                   var->data.binding != existing->data.binding) {
                  linker_error(prog, "explicit bindings for %s "
                               "`%s' have differing values\n",
                               mode_string(var), var->name);
                  return;
               }

               existing->data.binding = var->data.binding;
               existing->data.explicit_binding = true;
            }

            if (var->type->contains_atomic() &&
                var->data.atomic.offset != existing->data.atomic.offset) {
               linker_error(prog, "offset specifications for %s "
                            "`%s' have differing values\n",
                            mode_string(var), var->name);
               return;
            }

	    /* Validate layout qualifiers for gl_FragDepth.
	     *
	     * From the AMD/ARB_conservative_depth specs:
	     *
	     *    "If gl_FragDepth is redeclared in any fragment shader in a
	     *    program, it must be redeclared in all fragment shaders in
	     *    that program that have static assignments to
	     *    gl_FragDepth. All redeclarations of gl_FragDepth in all
	     *    fragment shaders in a single program must have the same set
	     *    of qualifiers."
	     */
	    if (strcmp(var->name, "gl_FragDepth") == 0) {
	       bool layout_declared = var->data.depth_layout != ir_depth_layout_none;
	       bool layout_differs =
		  var->data.depth_layout != existing->data.depth_layout;

	       if (layout_declared && layout_differs) {
		  linker_error(prog,
			       "All redeclarations of gl_FragDepth in all "
			       "fragment shaders in a single program must have "
			       "the same set of qualifiers.");
	       }

	       if (var->data.used && layout_differs) {
		  linker_error(prog,
			       "If gl_FragDepth is redeclared with a layout "
			       "qualifier in any fragment shader, it must be "
			       "redeclared with the same layout qualifier in "
			       "all fragment shaders that have assignments to "
			       "gl_FragDepth");
	       }
	    }

	    /* Page 35 (page 41 of the PDF) of the GLSL 4.20 spec says:
	     *
	     *     "If a shared global has multiple initializers, the
	     *     initializers must all be constant expressions, and they
	     *     must all have the same value. Otherwise, a link error will
	     *     result. (A shared global having only one initializer does
	     *     not require that initializer to be a constant expression.)"
	     *
	     * Previous to 4.20 the GLSL spec simply said that initializers
	     * must have the same value.  In this case of non-constant
	     * initializers, this was impossible to determine.  As a result,
	     * no vendor actually implemented that behavior.  The 4.20
	     * behavior matches the implemented behavior of at least one other
	     * vendor, so we'll implement that for all GLSL versions.
	     */
	    if (var->constant_initializer != NULL) {
	       if (existing->constant_initializer != NULL) {
		  if (!var->constant_initializer->has_value(existing->constant_initializer)) {
		     linker_error(prog, "initializers for %s "
				  "`%s' have differing values\n",
				  mode_string(var), var->name);
		     return;
		  }
	       } else {
		  /* If the first-seen instance of a particular uniform did not
		   * have an initializer but a later instance does, copy the
		   * initializer to the version stored in the symbol table.
		   */
		  /* FINISHME: This is wrong.  The constant_value field should
		   * FINISHME: not be modified!  Imagine a case where a shader
		   * FINISHME: without an initializer is linked in two different
		   * FINISHME: programs with shaders that have differing
		   * FINISHME: initializers.  Linking with the first will
		   * FINISHME: modify the shader, and linking with the second
		   * FINISHME: will fail.
		   */
		  existing->constant_initializer =
		     var->constant_initializer->clone(ralloc_parent(existing),
						      NULL);
	       }
	    }

	    if (var->data.has_initializer) {
	       if (existing->data.has_initializer
		   && (var->constant_initializer == NULL
		       || existing->constant_initializer == NULL)) {
		  linker_error(prog,
			       "shared global variable `%s' has multiple "
			       "non-constant initializers.\n",
			       var->name);
		  return;
	       }

	       /* Some instance had an initializer, so keep track of that.  In
		* this location, all sorts of initializers (constant or
		* otherwise) will propagate the existence to the variable
		* stored in the symbol table.
		*/
	       existing->data.has_initializer = true;
	    }

	    if (existing->data.invariant != var->data.invariant) {
	       linker_error(prog, "declarations for %s `%s' have "
			    "mismatching invariant qualifiers\n",
			    mode_string(var), var->name);
	       return;
	    }
            if (existing->data.centroid != var->data.centroid) {
               linker_error(prog, "declarations for %s `%s' have "
			    "mismatching centroid qualifiers\n",
			    mode_string(var), var->name);
               return;
            }
            if (existing->data.sample != var->data.sample) {
               linker_error(prog, "declarations for %s `%s` have "
                            "mismatching sample qualifiers\n",
                            mode_string(var), var->name);
               return;
            }
	 } else
	    variables.add_variable(var);
      }
   }
}


/**
 * Perform validation of uniforms used across multiple shader stages
 */
void
cross_validate_uniforms(struct gl_shader_program *prog)
{
   cross_validate_globals(prog, prog->_LinkedShaders,
                          MESA_SHADER_STAGES, true);
}

/**
 * Accumulates the array of prog->UniformBlocks and checks that all
 * definitons of blocks agree on their contents.
 */
static bool
interstage_cross_validate_uniform_blocks(struct gl_shader_program *prog)
{
   unsigned max_num_uniform_blocks = 0;
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      if (prog->_LinkedShaders[i])
	 max_num_uniform_blocks += prog->_LinkedShaders[i]->NumUniformBlocks;
   }

   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      struct gl_shader *sh = prog->_LinkedShaders[i];

      prog->UniformBlockStageIndex[i] = ralloc_array(prog, int,
						     max_num_uniform_blocks);
      for (unsigned int j = 0; j < max_num_uniform_blocks; j++)
	 prog->UniformBlockStageIndex[i][j] = -1;

      if (sh == NULL)
	 continue;

      for (unsigned int j = 0; j < sh->NumUniformBlocks; j++) {
	 int index = link_cross_validate_uniform_block(prog,
						       &prog->UniformBlocks,
						       &prog->NumUniformBlocks,
						       &sh->UniformBlocks[j]);

	 if (index == -1) {
	    linker_error(prog, "uniform block `%s' has mismatching definitions",
			 sh->UniformBlocks[j].Name);
	    return false;
	 }

	 prog->UniformBlockStageIndex[i][index] = j;
      }
   }

   return true;
}


/**
 * Populates a shaders symbol table with all global declarations
 */
static void
populate_symbol_table(gl_shader *sh)
{
   sh->symbols = new(sh) glsl_symbol_table;

   foreach_in_list(ir_instruction, inst, sh->ir) {
      ir_variable *var;
      ir_function *func;

      if ((func = inst->as_function()) != NULL) {
	 sh->symbols->add_function(func);
      } else if ((var = inst->as_variable()) != NULL) {
         if (var->data.mode != ir_var_temporary)
            sh->symbols->add_variable(var);
      }
   }
}


/**
 * Remap variables referenced in an instruction tree
 *
 * This is used when instruction trees are cloned from one shader and placed in
 * another.  These trees will contain references to \c ir_variable nodes that
 * do not exist in the target shader.  This function finds these \c ir_variable
 * references and replaces the references with matching variables in the target
 * shader.
 *
 * If there is no matching variable in the target shader, a clone of the
 * \c ir_variable is made and added to the target shader.  The new variable is
 * added to \b both the instruction stream and the symbol table.
 *
 * \param inst         IR tree that is to be processed.
 * \param symbols      Symbol table containing global scope symbols in the
 *                     linked shader.
 * \param instructions Instruction stream where new variable declarations
 *                     should be added.
 */
void
remap_variables(ir_instruction *inst, struct gl_shader *target,
		hash_table *temps)
{
   class remap_visitor : public ir_hierarchical_visitor {
   public:
	 remap_visitor(struct gl_shader *target,
		    hash_table *temps)
      {
	 this->target = target;
	 this->symbols = target->symbols;
	 this->instructions = target->ir;
	 this->temps = temps;
      }

      virtual ir_visitor_status visit(ir_dereference_variable *ir)
      {
	 if (ir->var->data.mode == ir_var_temporary) {
	    ir_variable *var = (ir_variable *) hash_table_find(temps, ir->var);

	    assert(var != NULL);
	    ir->var = var;
	    return visit_continue;
	 }

	 ir_variable *const existing =
	    this->symbols->get_variable(ir->var->name);
	 if (existing != NULL)
	    ir->var = existing;
	 else {
	    ir_variable *copy = ir->var->clone(this->target, NULL);

	    this->symbols->add_variable(copy);
	    this->instructions->push_head(copy);
	    ir->var = copy;
	 }

	 return visit_continue;
      }

   private:
      struct gl_shader *target;
      glsl_symbol_table *symbols;
      exec_list *instructions;
      hash_table *temps;
   };

   remap_visitor v(target, temps);

   inst->accept(&v);
}


/**
 * Move non-declarations from one instruction stream to another
 *
 * The intended usage pattern of this function is to pass the pointer to the
 * head sentinel of a list (i.e., a pointer to the list cast to an \c exec_node
 * pointer) for \c last and \c false for \c make_copies on the first
 * call.  Successive calls pass the return value of the previous call for
 * \c last and \c true for \c make_copies.
 *
 * \param instructions Source instruction stream
 * \param last         Instruction after which new instructions should be
 *                     inserted in the target instruction stream
 * \param make_copies  Flag selecting whether instructions in \c instructions
 *                     should be copied (via \c ir_instruction::clone) into the
 *                     target list or moved.
 *
 * \return
 * The new "last" instruction in the target instruction stream.  This pointer
 * is suitable for use as the \c last parameter of a later call to this
 * function.
 */
exec_node *
move_non_declarations(exec_list *instructions, exec_node *last,
		      bool make_copies, gl_shader *target)
{
   hash_table *temps = NULL;

   if (make_copies)
      temps = hash_table_ctor(0, hash_table_pointer_hash,
			      hash_table_pointer_compare);

   foreach_in_list_safe(ir_instruction, inst, instructions) {
      if (inst->as_function())
	 continue;
	   
      if (inst->ir_type == ir_type_precision)
         continue;
      if (inst->ir_type == ir_type_typedecl)
         continue;

      ir_variable *var = inst->as_variable();
      if ((var != NULL) && (var->data.mode != ir_var_temporary))
	 continue;

      assert(inst->as_assignment()
             || inst->as_call()
             || inst->as_if() /* for initializers with the ?: operator */
	     || ((var != NULL) && (var->data.mode == ir_var_temporary)));

      if (make_copies) {
	 inst = inst->clone(target, NULL);

	 if (var != NULL)
	    hash_table_insert(temps, inst, var);
	 else
	    remap_variables(inst, target, temps);
      } else {
	 inst->remove();
      }

      last->insert_after(inst);
      last = inst;
   }

   if (make_copies)
      hash_table_dtor(temps);

   return last;
}

/**
 * Get the function signature for main from a shader
 */
ir_function_signature *
link_get_main_function_signature(gl_shader *sh)
{
   ir_function *const f = sh->symbols->get_function("main");
   if (f != NULL) {
      exec_list void_parameters;

      /* Look for the 'void main()' signature and ensure that it's defined.
       * This keeps the linker from accidentally pick a shader that just
       * contains a prototype for main.
       *
       * We don't have to check for multiple definitions of main (in multiple
       * shaders) because that would have already been caught above.
       */
      ir_function_signature *sig =
         f->matching_signature(NULL, &void_parameters, false);
      if ((sig != NULL) && sig->is_defined) {
	 return sig;
      }
   }

   return NULL;
}


/**
 * This class is only used in link_intrastage_shaders() below but declaring
 * it inside that function leads to compiler warnings with some versions of
 * gcc.
 */
class array_sizing_visitor : public ir_hierarchical_visitor {
public:
   array_sizing_visitor()
      : mem_ctx(ralloc_context(NULL)),
        unnamed_interfaces(hash_table_ctor(0, hash_table_pointer_hash,
                                           hash_table_pointer_compare))
   {
   }

   ~array_sizing_visitor()
   {
      hash_table_dtor(this->unnamed_interfaces);
      ralloc_free(this->mem_ctx);
   }

   virtual ir_visitor_status visit(ir_variable *var)
   {
      fixup_type(&var->type, var->data.max_array_access);
      if (var->type->is_interface()) {
         if (interface_contains_unsized_arrays(var->type)) {
            const glsl_type *new_type =
               resize_interface_members(var->type,
                                        var->get_max_ifc_array_access());
            var->type = new_type;
            var->change_interface_type(new_type);
         }
      } else if (var->type->is_array() &&
                 var->type->fields.array->is_interface()) {
         if (interface_contains_unsized_arrays(var->type->fields.array)) {
            const glsl_type *new_type =
               resize_interface_members(var->type->fields.array,
                                        var->get_max_ifc_array_access());
            var->change_interface_type(new_type);
            var->type =
               glsl_type::get_array_instance(new_type, var->type->length);
         }
      } else if (const glsl_type *ifc_type = var->get_interface_type()) {
         /* Store a pointer to the variable in the unnamed_interfaces
          * hashtable.
          */
         ir_variable **interface_vars = (ir_variable **)
            hash_table_find(this->unnamed_interfaces, ifc_type);
         if (interface_vars == NULL) {
            interface_vars = rzalloc_array(mem_ctx, ir_variable *,
                                           ifc_type->length);
            hash_table_insert(this->unnamed_interfaces, interface_vars,
                              ifc_type);
         }
         unsigned index = ifc_type->field_index(var->name);
         assert(index < ifc_type->length);
         assert(interface_vars[index] == NULL);
         interface_vars[index] = var;
      }
      return visit_continue;
   }

   /**
    * For each unnamed interface block that was discovered while running the
    * visitor, adjust the interface type to reflect the newly assigned array
    * sizes, and fix up the ir_variable nodes to point to the new interface
    * type.
    */
   void fixup_unnamed_interface_types()
   {
      hash_table_call_foreach(this->unnamed_interfaces,
                              fixup_unnamed_interface_type, NULL);
   }

private:
   /**
    * If the type pointed to by \c type represents an unsized array, replace
    * it with a sized array whose size is determined by max_array_access.
    */
   static void fixup_type(const glsl_type **type, unsigned max_array_access)
   {
      if ((*type)->is_unsized_array()) {
         *type = glsl_type::get_array_instance((*type)->fields.array,
                                               max_array_access + 1);
         assert(*type != NULL);
      }
   }

   /**
    * Determine whether the given interface type contains unsized arrays (if
    * it doesn't, array_sizing_visitor doesn't need to process it).
    */
   static bool interface_contains_unsized_arrays(const glsl_type *type)
   {
      for (unsigned i = 0; i < type->length; i++) {
         const glsl_type *elem_type = type->fields.structure[i].type;
         if (elem_type->is_unsized_array())
            return true;
      }
      return false;
   }

   /**
    * Create a new interface type based on the given type, with unsized arrays
    * replaced by sized arrays whose size is determined by
    * max_ifc_array_access.
    */
   static const glsl_type *
   resize_interface_members(const glsl_type *type,
                            const unsigned *max_ifc_array_access)
   {
      unsigned num_fields = type->length;
      glsl_struct_field *fields = new glsl_struct_field[num_fields];
      memcpy(fields, type->fields.structure,
             num_fields * sizeof(*fields));
      for (unsigned i = 0; i < num_fields; i++) {
         fixup_type(&fields[i].type, max_ifc_array_access[i]);
      }
      glsl_interface_packing packing =
         (glsl_interface_packing) type->interface_packing;
      const glsl_type *new_ifc_type =
         glsl_type::get_interface_instance(fields, num_fields,
                                           packing, type->name);
      delete [] fields;
      return new_ifc_type;
   }

   static void fixup_unnamed_interface_type(const void *key, void *data,
                                            void *)
   {
      const glsl_type *ifc_type = (const glsl_type *) key;
      ir_variable **interface_vars = (ir_variable **) data;
      unsigned num_fields = ifc_type->length;
      glsl_struct_field *fields = new glsl_struct_field[num_fields];
      memcpy(fields, ifc_type->fields.structure,
             num_fields * sizeof(*fields));
      bool interface_type_changed = false;
      for (unsigned i = 0; i < num_fields; i++) {
         if (interface_vars[i] != NULL &&
             fields[i].type != interface_vars[i]->type) {
            fields[i].type = interface_vars[i]->type;
            interface_type_changed = true;
         }
      }
      if (!interface_type_changed) {
         delete [] fields;
         return;
      }
      glsl_interface_packing packing =
         (glsl_interface_packing) ifc_type->interface_packing;
      const glsl_type *new_ifc_type =
         glsl_type::get_interface_instance(fields, num_fields, packing,
                                           ifc_type->name);
      delete [] fields;
      for (unsigned i = 0; i < num_fields; i++) {
         if (interface_vars[i] != NULL)
            interface_vars[i]->change_interface_type(new_ifc_type);
      }
   }

   /**
    * Memory context used to allocate the data in \c unnamed_interfaces.
    */
   void *mem_ctx;

   /**
    * Hash table from const glsl_type * to an array of ir_variable *'s
    * pointing to the ir_variables constituting each unnamed interface block.
    */
   hash_table *unnamed_interfaces;
};

/**
 * Performs the cross-validation of layout qualifiers specified in
 * redeclaration of gl_FragCoord for the attached fragment shaders,
 * and propagates them to the linked FS and linked shader program.
 */
static void
link_fs_input_layout_qualifiers(struct gl_shader_program *prog,
	                        struct gl_shader *linked_shader,
	                        struct gl_shader **shader_list,
	                        unsigned num_shaders)
{
   linked_shader->redeclares_gl_fragcoord = false;
   linked_shader->uses_gl_fragcoord = false;
   linked_shader->origin_upper_left = false;
   linked_shader->pixel_center_integer = false;

   if (linked_shader->Stage != MESA_SHADER_FRAGMENT ||
       (prog->Version < 150 && !prog->ARB_fragment_coord_conventions_enable))
      return;

   for (unsigned i = 0; i < num_shaders; i++) {
      struct gl_shader *shader = shader_list[i];
      /* From the GLSL 1.50 spec, page 39:
       *
       *   "If gl_FragCoord is redeclared in any fragment shader in a program,
       *    it must be redeclared in all the fragment shaders in that program
       *    that have a static use gl_FragCoord."
       *
       * Exclude the case when one of the 'linked_shader' or 'shader' redeclares
       * gl_FragCoord with no layout qualifiers but the other one doesn't
       * redeclare it. If we strictly follow GLSL 1.50 spec's language, it
       * should be a link error. But, generating link error for this case will
       * be a wrong behaviour which spec didn't intend to do and it could also
       * break some applications.
       */
      if ((linked_shader->redeclares_gl_fragcoord
           && !shader->redeclares_gl_fragcoord
           && shader->uses_gl_fragcoord
           && (linked_shader->origin_upper_left
               || linked_shader->pixel_center_integer))
          || (shader->redeclares_gl_fragcoord
              && !linked_shader->redeclares_gl_fragcoord
              && linked_shader->uses_gl_fragcoord
              && (shader->origin_upper_left
                  || shader->pixel_center_integer))) {
             linker_error(prog, "fragment shader defined with conflicting "
                         "layout qualifiers for gl_FragCoord\n");
      }

      /* From the GLSL 1.50 spec, page 39:
       *
       *   "All redeclarations of gl_FragCoord in all fragment shaders in a
       *    single program must have the same set of qualifiers."
       */
      if (linked_shader->redeclares_gl_fragcoord && shader->redeclares_gl_fragcoord
          && (shader->origin_upper_left != linked_shader->origin_upper_left
          || shader->pixel_center_integer != linked_shader->pixel_center_integer)) {
         linker_error(prog, "fragment shader defined with conflicting "
                      "layout qualifiers for gl_FragCoord\n");
      }

      /* Update the linked shader state.  Note that uses_gl_fragcoord should
       * accumulate the results.  The other values should replace.  If there
       * are multiple redeclarations, all the fields except uses_gl_fragcoord
       * are already known to be the same.
       */
      if (shader->redeclares_gl_fragcoord || shader->uses_gl_fragcoord) {
         linked_shader->redeclares_gl_fragcoord =
            shader->redeclares_gl_fragcoord;
         linked_shader->uses_gl_fragcoord = linked_shader->uses_gl_fragcoord
            || shader->uses_gl_fragcoord;
         linked_shader->origin_upper_left = shader->origin_upper_left;
         linked_shader->pixel_center_integer = shader->pixel_center_integer;
      }
   }
}

/**
 * Performs the cross-validation of geometry shader max_vertices and
 * primitive type layout qualifiers for the attached geometry shaders,
 * and propagates them to the linked GS and linked shader program.
 */
static void
link_gs_inout_layout_qualifiers(struct gl_shader_program *prog,
				struct gl_shader *linked_shader,
				struct gl_shader **shader_list,
				unsigned num_shaders)
{
   linked_shader->Geom.VerticesOut = 0;
   linked_shader->Geom.Invocations = 0;
   linked_shader->Geom.InputType = PRIM_UNKNOWN;
   linked_shader->Geom.OutputType = PRIM_UNKNOWN;

   /* No in/out qualifiers defined for anything but GLSL 1.50+
    * geometry shaders so far.
    */
   if (linked_shader->Stage != MESA_SHADER_GEOMETRY || prog->Version < 150)
      return;

   /* From the GLSL 1.50 spec, page 46:
    *
    *     "All geometry shader output layout declarations in a program
    *      must declare the same layout and same value for
    *      max_vertices. There must be at least one geometry output
    *      layout declaration somewhere in a program, but not all
    *      geometry shaders (compilation units) are required to
    *      declare it."
    */

   for (unsigned i = 0; i < num_shaders; i++) {
      struct gl_shader *shader = shader_list[i];

      if (shader->Geom.InputType != PRIM_UNKNOWN) {
	 if (linked_shader->Geom.InputType != PRIM_UNKNOWN &&
	     linked_shader->Geom.InputType != shader->Geom.InputType) {
	    linker_error(prog, "geometry shader defined with conflicting "
			 "input types\n");
	    return;
	 }
	 linked_shader->Geom.InputType = shader->Geom.InputType;
      }

      if (shader->Geom.OutputType != PRIM_UNKNOWN) {
	 if (linked_shader->Geom.OutputType != PRIM_UNKNOWN &&
	     linked_shader->Geom.OutputType != shader->Geom.OutputType) {
	    linker_error(prog, "geometry shader defined with conflicting "
			 "output types\n");
	    return;
	 }
	 linked_shader->Geom.OutputType = shader->Geom.OutputType;
      }

      if (shader->Geom.VerticesOut != 0) {
	 if (linked_shader->Geom.VerticesOut != 0 &&
	     linked_shader->Geom.VerticesOut != shader->Geom.VerticesOut) {
	    linker_error(prog, "geometry shader defined with conflicting "
			 "output vertex count (%d and %d)\n",
			 linked_shader->Geom.VerticesOut,
			 shader->Geom.VerticesOut);
	    return;
	 }
	 linked_shader->Geom.VerticesOut = shader->Geom.VerticesOut;
      }

      if (shader->Geom.Invocations != 0) {
	 if (linked_shader->Geom.Invocations != 0 &&
	     linked_shader->Geom.Invocations != shader->Geom.Invocations) {
	    linker_error(prog, "geometry shader defined with conflicting "
			 "invocation count (%d and %d)\n",
			 linked_shader->Geom.Invocations,
			 shader->Geom.Invocations);
	    return;
	 }
	 linked_shader->Geom.Invocations = shader->Geom.Invocations;
      }
   }

   /* Just do the intrastage -> interstage propagation right now,
    * since we already know we're in the right type of shader program
    * for doing it.
    */
   if (linked_shader->Geom.InputType == PRIM_UNKNOWN) {
      linker_error(prog,
		   "geometry shader didn't declare primitive input type\n");
      return;
   }
   prog->Geom.InputType = linked_shader->Geom.InputType;

   if (linked_shader->Geom.OutputType == PRIM_UNKNOWN) {
      linker_error(prog,
		   "geometry shader didn't declare primitive output type\n");
      return;
   }
   prog->Geom.OutputType = linked_shader->Geom.OutputType;

   if (linked_shader->Geom.VerticesOut == 0) {
      linker_error(prog,
		   "geometry shader didn't declare max_vertices\n");
      return;
   }
   prog->Geom.VerticesOut = linked_shader->Geom.VerticesOut;

   if (linked_shader->Geom.Invocations == 0)
      linked_shader->Geom.Invocations = 1;

   prog->Geom.Invocations = linked_shader->Geom.Invocations;
}


/**
 * Perform cross-validation of compute shader local_size_{x,y,z} layout
 * qualifiers for the attached compute shaders, and propagate them to the
 * linked CS and linked shader program.
 */
static void
link_cs_input_layout_qualifiers(struct gl_shader_program *prog,
                                struct gl_shader *linked_shader,
                                struct gl_shader **shader_list,
                                unsigned num_shaders)
{
   for (int i = 0; i < 3; i++)
      linked_shader->Comp.LocalSize[i] = 0;

   /* This function is called for all shader stages, but it only has an effect
    * for compute shaders.
    */
   if (linked_shader->Stage != MESA_SHADER_COMPUTE)
      return;

   /* From the ARB_compute_shader spec, in the section describing local size
    * declarations:
    *
    *     If multiple compute shaders attached to a single program object
    *     declare local work-group size, the declarations must be identical;
    *     otherwise a link-time error results. Furthermore, if a program
    *     object contains any compute shaders, at least one must contain an
    *     input layout qualifier specifying the local work sizes of the
    *     program, or a link-time error will occur.
    */
   for (unsigned sh = 0; sh < num_shaders; sh++) {
      struct gl_shader *shader = shader_list[sh];

      if (shader->Comp.LocalSize[0] != 0) {
         if (linked_shader->Comp.LocalSize[0] != 0) {
            for (int i = 0; i < 3; i++) {
               if (linked_shader->Comp.LocalSize[i] !=
                   shader->Comp.LocalSize[i]) {
                  linker_error(prog, "compute shader defined with conflicting "
                               "local sizes\n");
                  return;
               }
            }
         }
         for (int i = 0; i < 3; i++)
            linked_shader->Comp.LocalSize[i] = shader->Comp.LocalSize[i];
      }
   }

   /* Just do the intrastage -> interstage propagation right now,
    * since we already know we're in the right type of shader program
    * for doing it.
    */
   if (linked_shader->Comp.LocalSize[0] == 0) {
      linker_error(prog, "compute shader didn't declare local size\n");
      return;
   }
   for (int i = 0; i < 3; i++)
      prog->Comp.LocalSize[i] = linked_shader->Comp.LocalSize[i];
}


/**
 * Combine a group of shaders for a single stage to generate a linked shader
 *
 * \note
 * If this function is supplied a single shader, it is cloned, and the new
 * shader is returned.
 */
struct gl_shader *
link_intrastage_shaders(void *mem_ctx,
			struct gl_context *ctx,
			struct gl_shader_program *prog,
			struct gl_shader **shader_list,
			unsigned num_shaders)
{
   struct gl_uniform_block *uniform_blocks = NULL;

   /* Check that global variables defined in multiple shaders are consistent.
    */
   cross_validate_globals(prog, shader_list, num_shaders, false);
   if (!prog->LinkStatus)
      return NULL;

   /* Check that interface blocks defined in multiple shaders are consistent.
    */
   validate_intrastage_interface_blocks(prog, (const gl_shader **)shader_list,
                                        num_shaders);
   if (!prog->LinkStatus)
      return NULL;

   /* Link up uniform blocks defined within this stage. */
   const unsigned num_uniform_blocks =
      link_uniform_blocks(mem_ctx, prog, shader_list, num_shaders,
                          &uniform_blocks);
   if (!prog->LinkStatus)
      return NULL;

   /* Check that there is only a single definition of each function signature
    * across all shaders.
    */
   for (unsigned i = 0; i < (num_shaders - 1); i++) {
      foreach_in_list(ir_instruction, node, shader_list[i]->ir) {
	 ir_function *const f = node->as_function();

	 if (f == NULL)
	    continue;

	 for (unsigned j = i + 1; j < num_shaders; j++) {
	    ir_function *const other =
	       shader_list[j]->symbols->get_function(f->name);

	    /* If the other shader has no function (and therefore no function
	     * signatures) with the same name, skip to the next shader.
	     */
	    if (other == NULL)
	       continue;

	    foreach_in_list(ir_function_signature, sig, &f->signatures) {
	       if (!sig->is_defined || sig->is_builtin())
		  continue;

	       ir_function_signature *other_sig =
		  other->exact_matching_signature(NULL, &sig->parameters);

	       if ((other_sig != NULL) && other_sig->is_defined
		   && !other_sig->is_builtin()) {
		  linker_error(prog, "function `%s' is multiply defined",
			       f->name);
		  return NULL;
	       }
	    }
	 }
      }
   }

   /* Find the shader that defines main, and make a clone of it.
    *
    * Starting with the clone, search for undefined references.  If one is
    * found, find the shader that defines it.  Clone the reference and add
    * it to the shader.  Repeat until there are no undefined references or
    * until a reference cannot be resolved.
    */
   gl_shader *main = NULL;
   for (unsigned i = 0; i < num_shaders; i++) {
      if (link_get_main_function_signature(shader_list[i]) != NULL) {
	 main = shader_list[i];
	 break;
      }
   }

   if (main == NULL) {
      linker_error(prog, "%s shader lacks `main'\n",
		   _mesa_shader_stage_to_string(shader_list[0]->Stage));
      return NULL;
   }

   gl_shader *linked = ctx->Driver.NewShader(NULL, 0, main->Type);
   linked->ir = new(linked) exec_list;
   clone_ir_list(mem_ctx, linked->ir, main->ir);

   linked->UniformBlocks = uniform_blocks;
   linked->NumUniformBlocks = num_uniform_blocks;
   ralloc_steal(linked, linked->UniformBlocks);

   link_fs_input_layout_qualifiers(prog, linked, shader_list, num_shaders);
   link_gs_inout_layout_qualifiers(prog, linked, shader_list, num_shaders);
   link_cs_input_layout_qualifiers(prog, linked, shader_list, num_shaders);

   populate_symbol_table(linked);

   /* The a pointer to the main function in the final linked shader (i.e., the
    * copy of the original shader that contained the main function).
    */
   ir_function_signature *const main_sig =
      link_get_main_function_signature(linked);

   /* Move any instructions other than variable declarations, function
    * declarations or precision statements into main.
    */
   exec_node *insertion_point =
      move_non_declarations(linked->ir, (exec_node *) &main_sig->body, false,
			    linked);

   for (unsigned i = 0; i < num_shaders; i++) {
      if (shader_list[i] == main)
	 continue;

      insertion_point = move_non_declarations(shader_list[i]->ir,
					      insertion_point, true, linked);
   }

   /* Check if any shader needs built-in functions. */
   bool need_builtins = false;
   for (unsigned i = 0; i < num_shaders; i++) {
      if (shader_list[i]->uses_builtin_functions) {
         need_builtins = true;
         break;
      }
   }

   bool ok;
   if (need_builtins) {
      /* Make a temporary array one larger than shader_list, which will hold
       * the built-in function shader as well.
       */
      gl_shader **linking_shaders = (gl_shader **)
         calloc(num_shaders + 1, sizeof(gl_shader *));

      ok = linking_shaders != NULL;

      if (ok) {
         memcpy(linking_shaders, shader_list, num_shaders * sizeof(gl_shader *));
         linking_shaders[num_shaders] = _mesa_glsl_get_builtin_function_shader();

         ok = link_function_calls(prog, linked, linking_shaders, num_shaders + 1);

         free(linking_shaders);
      } else {
         _mesa_error_no_memory(__func__);
      }
   } else {
      ok = link_function_calls(prog, linked, shader_list, num_shaders);
   }


   if (!ok) {
      ctx->Driver.DeleteShader(ctx, linked);
      return NULL;
   }

   /* At this point linked should contain all of the linked IR, so
    * validate it to make sure nothing went wrong.
    */
   validate_ir_tree(linked->ir);

   /* Set the size of geometry shader input arrays */
   if (linked->Stage == MESA_SHADER_GEOMETRY) {
      unsigned num_vertices = vertices_per_prim(prog->Geom.InputType);
      geom_array_resize_visitor input_resize_visitor(num_vertices, prog);
      foreach_in_list(ir_instruction, ir, linked->ir) {
         ir->accept(&input_resize_visitor);
      }
   }

   if (ctx->Const.VertexID_is_zero_based)
      lower_vertex_id(linked);

   /* Make a pass over all variable declarations to ensure that arrays with
    * unspecified sizes have a size specified.  The size is inferred from the
    * max_array_access field.
    */
   array_sizing_visitor v;
   v.run(linked->ir);
   v.fixup_unnamed_interface_types();

   return linked;
}

/**
 * Update the sizes of linked shader uniform arrays to the maximum
 * array index used.
 *
 * From page 81 (page 95 of the PDF) of the OpenGL 2.1 spec:
 *
 *     If one or more elements of an array are active,
 *     GetActiveUniform will return the name of the array in name,
 *     subject to the restrictions listed above. The type of the array
 *     is returned in type. The size parameter contains the highest
 *     array element index used, plus one. The compiler or linker
 *     determines the highest index used.  There will be only one
 *     active uniform reported by the GL per uniform array.

 */
static void
update_array_sizes(struct gl_shader_program *prog)
{
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
	 if (prog->_LinkedShaders[i] == NULL)
	    continue;

      foreach_in_list(ir_instruction, node, prog->_LinkedShaders[i]->ir) {
	 ir_variable *const var = node->as_variable();

	 if ((var == NULL) || (var->data.mode != ir_var_uniform) ||
	     !var->type->is_array())
	    continue;

	 /* GL_ARB_uniform_buffer_object says that std140 uniforms
	  * will not be eliminated.  Since we always do std140, just
	  * don't resize arrays in UBOs.
          *
          * Atomic counters are supposed to get deterministic
          * locations assigned based on the declaration ordering and
          * sizes, array compaction would mess that up.
	  */
	 if (var->is_in_uniform_block() || var->type->contains_atomic())
	    continue;

	 unsigned int size = var->data.max_array_access;
	 for (unsigned j = 0; j < MESA_SHADER_STAGES; j++) {
	       if (prog->_LinkedShaders[j] == NULL)
		  continue;

	    foreach_in_list(ir_instruction, node2, prog->_LinkedShaders[j]->ir) {
	       ir_variable *other_var = node2->as_variable();
	       if (!other_var)
		  continue;

	       if (strcmp(var->name, other_var->name) == 0 &&
		   other_var->data.max_array_access > size) {
		  size = other_var->data.max_array_access;
	       }
	    }
	 }

	 if (size + 1 != var->type->length) {
	    /* If this is a built-in uniform (i.e., it's backed by some
	     * fixed-function state), adjust the number of state slots to
	     * match the new array size.  The number of slots per array entry
	     * is not known.  It seems safe to assume that the total number of
	     * slots is an integer multiple of the number of array elements.
	     * Determine the number of slots per array element by dividing by
	     * the old (total) size.
	     */
            const unsigned num_slots = var->get_num_state_slots();
	    if (num_slots > 0) {
	       var->set_num_state_slots((size + 1)
                                        * (num_slots / var->type->length));
	    }

	    var->type = glsl_type::get_array_instance(var->type->fields.array,
						      size + 1);
	    /* FINISHME: We should update the types of array
	     * dereferences of this variable now.
	     */
	 }
      }
   }
}

/**
 * Find a contiguous set of available bits in a bitmask.
 *
 * \param used_mask     Bits representing used (1) and unused (0) locations
 * \param needed_count  Number of contiguous bits needed.
 *
 * \return
 * Base location of the available bits on success or -1 on failure.
 */
int
find_available_slots(unsigned used_mask, unsigned needed_count)
{
   unsigned needed_mask = (1 << needed_count) - 1;
   const int max_bit_to_test = (8 * sizeof(used_mask)) - needed_count;

   /* The comparison to 32 is redundant, but without it GCC emits "warning:
    * cannot optimize possibly infinite loops" for the loop below.
    */
   if ((needed_count == 0) || (max_bit_to_test < 0) || (max_bit_to_test > 32))
      return -1;

   for (int i = 0; i <= max_bit_to_test; i++) {
      if ((needed_mask & ~used_mask) == needed_mask)
	 return i;

      needed_mask <<= 1;
   }

   return -1;
}


/**
 * Assign locations for either VS inputs for FS outputs
 *
 * \param prog          Shader program whose variables need locations assigned
 * \param target_index  Selector for the program target to receive location
 *                      assignmnets.  Must be either \c MESA_SHADER_VERTEX or
 *                      \c MESA_SHADER_FRAGMENT.
 * \param max_index     Maximum number of generic locations.  This corresponds
 *                      to either the maximum number of draw buffers or the
 *                      maximum number of generic attributes.
 *
 * \return
 * If locations are successfully assigned, true is returned.  Otherwise an
 * error is emitted to the shader link log and false is returned.
 */
bool
assign_attribute_or_color_locations(gl_shader_program *prog,
				    unsigned target_index,
				    unsigned max_index)
{
   /* Mark invalid locations as being used.
    */
   unsigned used_locations = (max_index >= 32)
      ? ~0 : ~((1 << max_index) - 1);

   assert((target_index == MESA_SHADER_VERTEX)
	  || (target_index == MESA_SHADER_FRAGMENT));

   gl_shader *const sh = prog->_LinkedShaders[target_index];
   if (sh == NULL)
      return true;

   /* Operate in a total of four passes.
    *
    * 1. Invalidate the location assignments for all vertex shader inputs.
    *
    * 2. Assign locations for inputs that have user-defined (via
    *    glBindVertexAttribLocation) locations and outputs that have
    *    user-defined locations (via glBindFragDataLocation).
    *
    * 3. Sort the attributes without assigned locations by number of slots
    *    required in decreasing order.  Fragmentation caused by attribute
    *    locations assigned by the application may prevent large attributes
    *    from having enough contiguous space.
    *
    * 4. Assign locations to any inputs without assigned locations.
    */

   const int generic_base = (target_index == MESA_SHADER_VERTEX)
      ? (int) VERT_ATTRIB_GENERIC0 : (int) FRAG_RESULT_DATA0;

   const enum ir_variable_mode direction =
      (target_index == MESA_SHADER_VERTEX)
      ? ir_var_shader_in : ir_var_shader_out;


   /* Temporary storage for the set of attributes that need locations assigned.
    */
   struct temp_attr {
      unsigned slots;
      ir_variable *var;

      /* Used below in the call to qsort. */
      static int compare(const void *a, const void *b)
      {
	 const temp_attr *const l = (const temp_attr *) a;
	 const temp_attr *const r = (const temp_attr *) b;

	 /* Reversed because we want a descending order sort below. */
	 return r->slots - l->slots;
      }
   } to_assign[16];

   unsigned num_attr = 0;

   foreach_in_list(ir_instruction, node, sh->ir) {
      ir_variable *const var = node->as_variable();

      if ((var == NULL) || (var->data.mode != (unsigned) direction))
	 continue;

      if (var->data.explicit_location) {
	 if ((var->data.location >= (int)(max_index + generic_base))
	     || (var->data.location < 0)) {
	    linker_error(prog,
			 "invalid explicit location %d specified for `%s'\n",
			 (var->data.location < 0)
			 ? var->data.location
                         : var->data.location - generic_base,
			 var->name);
	    return false;
	 }
      } else if (target_index == MESA_SHADER_VERTEX) {
	 unsigned binding;

	 if (prog->AttributeBindings->get(binding, var->name)) {
	    assert(binding >= VERT_ATTRIB_GENERIC0);
	    var->data.location = binding;
            var->data.is_unmatched_generic_inout = 0;
	 }
      } else if (target_index == MESA_SHADER_FRAGMENT) {
	 unsigned binding;
	 unsigned index;

	 if (prog->FragDataBindings->get(binding, var->name)) {
	    assert(binding >= FRAG_RESULT_DATA0);
	    var->data.location = binding;
            var->data.is_unmatched_generic_inout = 0;

	    if (prog->FragDataIndexBindings->get(index, var->name)) {
	       var->data.index = index;
	    }
	 }
      }

      /* If the variable is not a built-in and has a location statically
       * assigned in the shader (presumably via a layout qualifier), make sure
       * that it doesn't collide with other assigned locations.  Otherwise,
       * add it to the list of variables that need linker-assigned locations.
       */
      const unsigned slots = var->type->count_attribute_slots();
      if (var->data.location != -1) {
	 if (var->data.location >= generic_base && var->data.index < 1) {
	    /* From page 61 of the OpenGL 4.0 spec:
	     *
	     *     "LinkProgram will fail if the attribute bindings assigned
	     *     by BindAttribLocation do not leave not enough space to
	     *     assign a location for an active matrix attribute or an
	     *     active attribute array, both of which require multiple
	     *     contiguous generic attributes."
	     *
	     * I think above text prohibits the aliasing of explicit and
	     * automatic assignments. But, aliasing is allowed in manual
	     * assignments of attribute locations. See below comments for
	     * the details.
	     *
	     * From OpenGL 4.0 spec, page 61:
	     *
	     *     "It is possible for an application to bind more than one
	     *     attribute name to the same location. This is referred to as
	     *     aliasing. This will only work if only one of the aliased
	     *     attributes is active in the executable program, or if no
	     *     path through the shader consumes more than one attribute of
	     *     a set of attributes aliased to the same location. A link
	     *     error can occur if the linker determines that every path
	     *     through the shader consumes multiple aliased attributes,
	     *     but implementations are not required to generate an error
	     *     in this case."
	     *
	     * From GLSL 4.30 spec, page 54:
	     *
	     *    "A program will fail to link if any two non-vertex shader
	     *     input variables are assigned to the same location. For
	     *     vertex shaders, multiple input variables may be assigned
	     *     to the same location using either layout qualifiers or via
	     *     the OpenGL API. However, such aliasing is intended only to
	     *     support vertex shaders where each execution path accesses
	     *     at most one input per each location. Implementations are
	     *     permitted, but not required, to generate link-time errors
	     *     if they detect that every path through the vertex shader
	     *     executable accesses multiple inputs assigned to any single
	     *     location. For all shader types, a program will fail to link
	     *     if explicit location assignments leave the linker unable
	     *     to find space for other variables without explicit
	     *     assignments."
	     *
	     * From OpenGL ES 3.0 spec, page 56:
	     *
	     *    "Binding more than one attribute name to the same location
	     *     is referred to as aliasing, and is not permitted in OpenGL
	     *     ES Shading Language 3.00 vertex shaders. LinkProgram will
	     *     fail when this condition exists. However, aliasing is
	     *     possible in OpenGL ES Shading Language 1.00 vertex shaders.
	     *     This will only work if only one of the aliased attributes
	     *     is active in the executable program, or if no path through
	     *     the shader consumes more than one attribute of a set of
	     *     attributes aliased to the same location. A link error can
	     *     occur if the linker determines that every path through the
	     *     shader consumes multiple aliased attributes, but implemen-
	     *     tations are not required to generate an error in this case."
	     *
	     * After looking at above references from OpenGL, OpenGL ES and
	     * GLSL specifications, we allow aliasing of vertex input variables
	     * in: OpenGL 2.0 (and above) and OpenGL ES 2.0.
	     *
	     * NOTE: This is not required by the spec but its worth mentioning
	     * here that we're not doing anything to make sure that no path
	     * through the vertex shader executable accesses multiple inputs
	     * assigned to any single location.
	     */

	    /* Mask representing the contiguous slots that will be used by
	     * this attribute.
	     */
	    const unsigned attr = var->data.location - generic_base;
	    const unsigned use_mask = (1 << slots) - 1;
            const char *const string = (target_index == MESA_SHADER_VERTEX)
               ? "vertex shader input" : "fragment shader output";

            /* Generate a link error if the requested locations for this
             * attribute exceed the maximum allowed attribute location.
             */
            if (attr + slots > max_index) {
               linker_error(prog,
                           "insufficient contiguous locations "
                           "available for %s `%s' %d %d %d", string,
                           var->name, used_locations, use_mask, attr);
               return false;
            }

	    /* Generate a link error if the set of bits requested for this
	     * attribute overlaps any previously allocated bits.
	     */
	    if ((~(use_mask << attr) & used_locations) != used_locations) {
               if (target_index == MESA_SHADER_FRAGMENT ||
                   (prog->IsES && prog->Version >= 300)) {
                  linker_error(prog,
                               "overlapping location is assigned "
                               "to %s `%s' %d %d %d\n", string,
                               var->name, used_locations, use_mask, attr);
                  return false;
               } else {
                  linker_warning(prog,
                                 "overlapping location is assigned "
                                 "to %s `%s' %d %d %d\n", string,
                                 var->name, used_locations, use_mask, attr);
               }
	    }

	    used_locations |= (use_mask << attr);
	 }

	 continue;
      }

      to_assign[num_attr].slots = slots;
      to_assign[num_attr].var = var;
      num_attr++;
   }

   /* If all of the attributes were assigned locations by the application (or
    * are built-in attributes with fixed locations), return early.  This should
    * be the common case.
    */
   if (num_attr == 0)
      return true;

   qsort(to_assign, num_attr, sizeof(to_assign[0]), temp_attr::compare);

   if (target_index == MESA_SHADER_VERTEX) {
      /* VERT_ATTRIB_GENERIC0 is a pseudo-alias for VERT_ATTRIB_POS.  It can
       * only be explicitly assigned by via glBindAttribLocation.  Mark it as
       * reserved to prevent it from being automatically allocated below.
       */
      find_deref_visitor find("gl_Vertex");
      find.run(sh->ir);
      if (find.variable_found())
	 used_locations |= (1 << 0);
   }

   for (unsigned i = 0; i < num_attr; i++) {
      /* Mask representing the contiguous slots that will be used by this
       * attribute.
       */
      const unsigned use_mask = (1 << to_assign[i].slots) - 1;

      int location = find_available_slots(used_locations, to_assign[i].slots);

      if (location < 0) {
	 const char *const string = (target_index == MESA_SHADER_VERTEX)
	    ? "vertex shader input" : "fragment shader output";

	 linker_error(prog,
		      "insufficient contiguous locations "
		      "available for %s `%s'",
		      string, to_assign[i].var->name);
	 return false;
      }

      to_assign[i].var->data.location = generic_base + location;
      to_assign[i].var->data.is_unmatched_generic_inout = 0;
      used_locations |= (use_mask << location);
   }

   return true;
}


/**
 * Demote shader inputs and outputs that are not used in other stages
 */
void
demote_shader_inputs_and_outputs(gl_shader *sh, enum ir_variable_mode mode)
{
   foreach_in_list(ir_instruction, node, sh->ir) {
      ir_variable *const var = node->as_variable();

      if ((var == NULL) || (var->data.mode != int(mode)))
	 continue;

      /* A shader 'in' or 'out' variable is only really an input or output if
       * its value is used by other shader stages.  This will cause the variable
       * to have a location assigned.
       */
      if (var->data.is_unmatched_generic_inout) {
         assert(var->data.mode != ir_var_temporary);
	 var->data.mode = ir_var_auto;
      }
   }
}


/**
 * Store the gl_FragDepth layout in the gl_shader_program struct.
 */
static void
store_fragdepth_layout(struct gl_shader_program *prog)
{
   if (prog->_LinkedShaders[MESA_SHADER_FRAGMENT] == NULL) {
      return;
   }

   struct exec_list *ir = prog->_LinkedShaders[MESA_SHADER_FRAGMENT]->ir;

   /* We don't look up the gl_FragDepth symbol directly because if
    * gl_FragDepth is not used in the shader, it's removed from the IR.
    * However, the symbol won't be removed from the symbol table.
    *
    * We're only interested in the cases where the variable is NOT removed
    * from the IR.
    */
   foreach_in_list(ir_instruction, node, ir) {
      ir_variable *const var = node->as_variable();

      if (var == NULL || var->data.mode != ir_var_shader_out) {
         continue;
      }

      if (strcmp(var->name, "gl_FragDepth") == 0) {
         switch (var->data.depth_layout) {
         case ir_depth_layout_none:
            prog->FragDepthLayout = FRAG_DEPTH_LAYOUT_NONE;
            return;
         case ir_depth_layout_any:
            prog->FragDepthLayout = FRAG_DEPTH_LAYOUT_ANY;
            return;
         case ir_depth_layout_greater:
            prog->FragDepthLayout = FRAG_DEPTH_LAYOUT_GREATER;
            return;
         case ir_depth_layout_less:
            prog->FragDepthLayout = FRAG_DEPTH_LAYOUT_LESS;
            return;
         case ir_depth_layout_unchanged:
            prog->FragDepthLayout = FRAG_DEPTH_LAYOUT_UNCHANGED;
            return;
         default:
            assert(0);
            return;
         }
      }
   }
}

/**
 * Validate the resources used by a program versus the implementation limits
 */
static void
check_resources(struct gl_context *ctx, struct gl_shader_program *prog)
{
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      struct gl_shader *sh = prog->_LinkedShaders[i];

      if (sh == NULL)
	 continue;

      if (sh->num_samplers > ctx->Const.Program[i].MaxTextureImageUnits) {
	 linker_error(prog, "Too many %s shader texture samplers",
		      _mesa_shader_stage_to_string(i));
      }

      if (sh->num_uniform_components >
          ctx->Const.Program[i].MaxUniformComponents) {
         if (ctx->Const.GLSLSkipStrictMaxUniformLimitCheck) {
            linker_warning(prog, "Too many %s shader default uniform block "
                           "components, but the driver will try to optimize "
                           "them out; this is non-portable out-of-spec "
			   "behavior\n",
                           _mesa_shader_stage_to_string(i));
         } else {
            linker_error(prog, "Too many %s shader default uniform block "
			 "components",
                         _mesa_shader_stage_to_string(i));
         }
      }

      if (sh->num_combined_uniform_components >
	  ctx->Const.Program[i].MaxCombinedUniformComponents) {
         if (ctx->Const.GLSLSkipStrictMaxUniformLimitCheck) {
            linker_warning(prog, "Too many %s shader uniform components, "
                           "but the driver will try to optimize them out; "
                           "this is non-portable out-of-spec behavior\n",
                           _mesa_shader_stage_to_string(i));
         } else {
            linker_error(prog, "Too many %s shader uniform components",
                         _mesa_shader_stage_to_string(i));
         }
      }
   }

   unsigned blocks[MESA_SHADER_STAGES] = {0};
   unsigned total_uniform_blocks = 0;

   for (unsigned i = 0; i < prog->NumUniformBlocks; i++) {
      for (unsigned j = 0; j < MESA_SHADER_STAGES; j++) {
	 if (prog->UniformBlockStageIndex[j][i] != -1) {
	    blocks[j]++;
	    total_uniform_blocks++;
	 }
      }

      if (total_uniform_blocks > ctx->Const.MaxCombinedUniformBlocks) {
	 linker_error(prog, "Too many combined uniform blocks (%d/%d)",
		      prog->NumUniformBlocks,
		      ctx->Const.MaxCombinedUniformBlocks);
      } else {
	 for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
            const unsigned max_uniform_blocks =
               ctx->Const.Program[i].MaxUniformBlocks;
	    if (blocks[i] > max_uniform_blocks) {
	       linker_error(prog, "Too many %s uniform blocks (%d/%d)",
			    _mesa_shader_stage_to_string(i),
			    blocks[i],
			    max_uniform_blocks);
	       break;
	    }
	 }
      }
   }
}

/**
 * Validate shader image resources.
 */
static void
check_image_resources(struct gl_context *ctx, struct gl_shader_program *prog)
{
   unsigned total_image_units = 0;
   unsigned fragment_outputs = 0;

   if (!ctx->Extensions.ARB_shader_image_load_store)
      return;

   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      struct gl_shader *sh = prog->_LinkedShaders[i];

      if (sh) {
         if (sh->NumImages > ctx->Const.Program[i].MaxImageUniforms)
            linker_error(prog, "Too many %s shader image uniforms",
                         _mesa_shader_stage_to_string(i));

         total_image_units += sh->NumImages;

         if (i == MESA_SHADER_FRAGMENT) {
            foreach_in_list(ir_instruction, node, sh->ir) {
               ir_variable *var = node->as_variable();
               if (var && var->data.mode == ir_var_shader_out)
                  fragment_outputs += var->type->count_attribute_slots();
            }
         }
      }
   }

   if (total_image_units > ctx->Const.MaxCombinedImageUniforms)
      linker_error(prog, "Too many combined image uniforms");

   if (total_image_units + fragment_outputs >
       ctx->Const.MaxCombinedImageUnitsAndFragmentOutputs)
      linker_error(prog, "Too many combined image uniforms and fragment outputs");
}


/**
 * Initializes explicit location slots to INACTIVE_UNIFORM_EXPLICIT_LOCATION
 * for a variable, checks for overlaps between other uniforms using explicit
 * locations.
 */
static bool
reserve_explicit_locations(struct gl_shader_program *prog,
                           string_to_uint_map *map, ir_variable *var)
{
   unsigned slots = var->type->uniform_locations();
   unsigned max_loc = var->data.location + slots - 1;

   /* Resize remap table if locations do not fit in the current one. */
   if (max_loc + 1 > prog->NumUniformRemapTable) {
      prog->UniformRemapTable =
         reralloc(prog, prog->UniformRemapTable,
                  gl_uniform_storage *,
                  max_loc + 1);

      if (!prog->UniformRemapTable) {
         linker_error(prog, "Out of memory during linking.");
         return false;
      }

      /* Initialize allocated space. */
      for (unsigned i = prog->NumUniformRemapTable; i < max_loc + 1; i++)
         prog->UniformRemapTable[i] = NULL;

      prog->NumUniformRemapTable = max_loc + 1;
   }

   for (unsigned i = 0; i < slots; i++) {
      unsigned loc = var->data.location + i;

      /* Check if location is already used. */
      if (prog->UniformRemapTable[loc] == INACTIVE_UNIFORM_EXPLICIT_LOCATION) {

         /* Possibly same uniform from a different stage, this is ok. */
         unsigned hash_loc;
         if (map->get(hash_loc, var->name) && hash_loc == loc - i)
               continue;

         /* ARB_explicit_uniform_location specification states:
          *
          *     "No two default-block uniform variables in the program can have
          *     the same location, even if they are unused, otherwise a compiler
          *     or linker error will be generated."
          */
         linker_error(prog,
                      "location qualifier for uniform %s overlaps"
                      "previously used location",
                      var->name);
         return false;
      }

      /* Initialize location as inactive before optimization
       * rounds and location assignment.
       */
      prog->UniformRemapTable[loc] = INACTIVE_UNIFORM_EXPLICIT_LOCATION;
   }

   /* Note, base location used for arrays. */
   map->put(var->data.location, var->name);

   return true;
}

/**
 * Check and reserve all explicit uniform locations, called before
 * any optimizations happen to handle also inactive uniforms and
 * inactive array elements that may get trimmed away.
 */
static void
check_explicit_uniform_locations(struct gl_context *ctx,
                                 struct gl_shader_program *prog)
{
   if (!ctx->Extensions.ARB_explicit_uniform_location)
      return;

   /* This map is used to detect if overlapping explicit locations
    * occur with the same uniform (from different stage) or a different one.
    */
   string_to_uint_map *uniform_map = new string_to_uint_map;

   if (!uniform_map) {
      linker_error(prog, "Out of memory during linking.");
      return;
   }

   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      struct gl_shader *sh = prog->_LinkedShaders[i];

      if (!sh)
         continue;

      foreach_in_list(ir_instruction, node, sh->ir) {
         ir_variable *var = node->as_variable();
         if ((var && var->data.mode == ir_var_uniform) &&
             var->data.explicit_location) {
            if (!reserve_explicit_locations(prog, uniform_map, var)) {
               delete uniform_map;
               return;
            }
         }
      }
   }

   delete uniform_map;
}

void
link_shaders(struct gl_context *ctx, struct gl_shader_program *prog)
{
   tfeedback_decl *tfeedback_decls = NULL;
   unsigned num_tfeedback_decls = prog->TransformFeedback.NumVarying;

   void *mem_ctx = ralloc_context(NULL); // temporary linker context

   prog->LinkStatus = true; /* All error paths will set this to false */
   prog->Validated = false;
   prog->_Used = false;

   ralloc_free(prog->InfoLog);
   prog->InfoLog = ralloc_strdup(NULL, "");

   ralloc_free(prog->UniformBlocks);
   prog->UniformBlocks = NULL;
   prog->NumUniformBlocks = 0;
   for (int i = 0; i < MESA_SHADER_STAGES; i++) {
      ralloc_free(prog->UniformBlockStageIndex[i]);
      prog->UniformBlockStageIndex[i] = NULL;
   }

   ralloc_free(prog->AtomicBuffers);
   prog->AtomicBuffers = NULL;
   prog->NumAtomicBuffers = 0;
   prog->ARB_fragment_coord_conventions_enable = false;

   /* Separate the shaders into groups based on their type.
    */
   struct gl_shader **shader_list[MESA_SHADER_STAGES];
   unsigned num_shaders[MESA_SHADER_STAGES];

   for (int i = 0; i < MESA_SHADER_STAGES; i++) {
      shader_list[i] = (struct gl_shader **)
         calloc(prog->NumShaders, sizeof(struct gl_shader *));
      num_shaders[i] = 0;
   }

   unsigned min_version = UINT_MAX;
   unsigned max_version = 0;
   const bool is_es_prog =
      (prog->NumShaders > 0 && prog->Shaders[0]->IsES) ? true : false;
   for (unsigned i = 0; i < prog->NumShaders; i++) {
      min_version = MIN2(min_version, prog->Shaders[i]->Version);
      max_version = MAX2(max_version, prog->Shaders[i]->Version);

      if ((!!prog->Shaders[i]->IsES) != is_es_prog) {
	 linker_error(prog, "all shaders must use same shading "
		      "language version\n");
	 goto done;
      }

      prog->ARB_fragment_coord_conventions_enable |=
         prog->Shaders[i]->ARB_fragment_coord_conventions_enable;

      gl_shader_stage shader_type = prog->Shaders[i]->Stage;
      shader_list[shader_type][num_shaders[shader_type]] = prog->Shaders[i];
      num_shaders[shader_type]++;
   }

   /* In desktop GLSL, different shader versions may be linked together.  In
    * GLSL ES, all shader versions must be the same.
    */
   if (is_es_prog && min_version != max_version) {
      linker_error(prog, "all shaders must use same shading "
		   "language version\n");
      goto done;
   }

   prog->Version = max_version;
   prog->IsES = is_es_prog;

   /* Geometry shaders have to be linked with vertex shaders.
    */
   if (num_shaders[MESA_SHADER_GEOMETRY] > 0 &&
       num_shaders[MESA_SHADER_VERTEX] == 0 &&
       !prog->SeparateShader) {
      linker_error(prog, "Geometry shader must be linked with "
		   "vertex shader\n");
      goto done;
   }

   /* Compute shaders have additional restrictions. */
   if (num_shaders[MESA_SHADER_COMPUTE] > 0 &&
       num_shaders[MESA_SHADER_COMPUTE] != prog->NumShaders) {
      linker_error(prog, "Compute shaders may not be linked with any other "
                   "type of shader\n");
   }

   for (unsigned int i = 0; i < MESA_SHADER_STAGES; i++) {
      if (prog->_LinkedShaders[i] != NULL)
	 ctx->Driver.DeleteShader(ctx, prog->_LinkedShaders[i]);

      prog->_LinkedShaders[i] = NULL;
   }

   /* Link all shaders for a particular stage and validate the result.
    */
   for (int stage = 0; stage < MESA_SHADER_STAGES; stage++) {
      if (num_shaders[stage] > 0) {
         gl_shader *const sh =
            link_intrastage_shaders(mem_ctx, ctx, prog, shader_list[stage],
                                    num_shaders[stage]);

         if (!prog->LinkStatus)
            goto done;

         switch (stage) {
         case MESA_SHADER_VERTEX:
            validate_vertex_shader_executable(prog, sh);
            break;
         case MESA_SHADER_GEOMETRY:
            validate_geometry_shader_executable(prog, sh);
            break;
         case MESA_SHADER_FRAGMENT:
            validate_fragment_shader_executable(prog, sh);
            break;
         }
         if (!prog->LinkStatus)
            goto done;

         _mesa_reference_shader(ctx, &prog->_LinkedShaders[stage], sh);
      }
   }

   if (num_shaders[MESA_SHADER_GEOMETRY] > 0)
      prog->LastClipDistanceArraySize = prog->Geom.ClipDistanceArraySize;
   else if (num_shaders[MESA_SHADER_VERTEX] > 0)
      prog->LastClipDistanceArraySize = prog->Vert.ClipDistanceArraySize;
   else
      prog->LastClipDistanceArraySize = 0; /* Not used */

   /* Here begins the inter-stage linking phase.  Some initial validation is
    * performed, then locations are assigned for uniforms, attributes, and
    * varyings.
    */
   cross_validate_uniforms(prog);
   if (!prog->LinkStatus)
      goto done;

   unsigned prev;

   for (prev = 0; prev <= MESA_SHADER_FRAGMENT; prev++) {
      if (prog->_LinkedShaders[prev] != NULL)
         break;
   }

   check_explicit_uniform_locations(ctx, prog);
   if (!prog->LinkStatus)
      goto done;

   /* Validate the inputs of each stage with the output of the preceding
    * stage.
    */
   for (unsigned i = prev + 1; i <= MESA_SHADER_FRAGMENT; i++) {
      if (prog->_LinkedShaders[i] == NULL)
         continue;

      validate_interstage_inout_blocks(prog, prog->_LinkedShaders[prev],
                                       prog->_LinkedShaders[i]);
      if (!prog->LinkStatus)
         goto done;

      cross_validate_outputs_to_inputs(prog,
                                       prog->_LinkedShaders[prev],
                                       prog->_LinkedShaders[i]);
      if (!prog->LinkStatus)
         goto done;

      prev = i;
   }

   /* Cross-validate uniform blocks between shader stages */
   validate_interstage_uniform_blocks(prog, prog->_LinkedShaders,
                                      MESA_SHADER_STAGES);
   if (!prog->LinkStatus)
      goto done;

   for (unsigned int i = 0; i < MESA_SHADER_STAGES; i++) {
      if (prog->_LinkedShaders[i] != NULL)
         lower_named_interface_blocks(mem_ctx, prog->_LinkedShaders[i]);
   }

   /* Implement the GLSL 1.30+ rule for discard vs infinite loops Do
    * it before optimization because we want most of the checks to get
    * dropped thanks to constant propagation.
    *
    * This rule also applies to GLSL ES 3.00.
    */
   if (max_version >= (is_es_prog ? 300U : 130U)) {
      struct gl_shader *sh = prog->_LinkedShaders[MESA_SHADER_FRAGMENT];
      if (sh) {
	 lower_discard_flow(sh->ir);
      }
   }

   if (!interstage_cross_validate_uniform_blocks(prog))
      goto done;

   /* Do common optimization before assigning storage for attributes,
    * uniforms, and varyings.  Later optimization could possibly make
    * some of that unused.
    */
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      detect_recursion_linked(prog, prog->_LinkedShaders[i]->ir);
      if (!prog->LinkStatus)
	 goto done;

      if (ctx->Const.ShaderCompilerOptions[i].LowerClipDistance) {
         lower_clip_distance(prog->_LinkedShaders[i]);
      }

      while (do_common_optimization(prog->_LinkedShaders[i]->ir, true, false,
                                    &ctx->Const.ShaderCompilerOptions[i],
                                    ctx->Const.NativeIntegers))
	 ;
   }

   /* Check and validate stream emissions in geometry shaders */
   validate_geometry_shader_emissions(ctx, prog);

   /* Mark all generic shader inputs and outputs as unpaired. */
   for (unsigned i = MESA_SHADER_VERTEX; i <= MESA_SHADER_FRAGMENT; i++) {
      if (prog->_LinkedShaders[i] != NULL) {
         link_invalidate_variable_locations(prog->_LinkedShaders[i]->ir);
      }
   }

   /* FINISHME: The value of the max_attribute_index parameter is
    * FINISHME: implementation dependent based on the value of
    * FINISHME: GL_MAX_VERTEX_ATTRIBS.  GL_MAX_VERTEX_ATTRIBS must be
    * FINISHME: at least 16, so hardcode 16 for now.
    */
   if (!assign_attribute_or_color_locations(prog, MESA_SHADER_VERTEX, 16)) {
      goto done;
   }

   if (!assign_attribute_or_color_locations(prog, MESA_SHADER_FRAGMENT, MAX2(ctx->Const.MaxDrawBuffers, ctx->Const.MaxDualSourceDrawBuffers))) {
      goto done;
   }

   unsigned first;
   for (first = 0; first <= MESA_SHADER_FRAGMENT; first++) {
      if (prog->_LinkedShaders[first] != NULL)
	 break;
   }

   if (num_tfeedback_decls != 0) {
      /* From GL_EXT_transform_feedback:
       *   A program will fail to link if:
       *
       *   * the <count> specified by TransformFeedbackVaryingsEXT is
       *     non-zero, but the program object has no vertex or geometry
       *     shader;
       */
      if (first == MESA_SHADER_FRAGMENT) {
         linker_error(prog, "Transform feedback varyings specified, but "
                      "no vertex or geometry shader is present.");
         goto done;
      }

      tfeedback_decls = ralloc_array(mem_ctx, tfeedback_decl,
                                     prog->TransformFeedback.NumVarying);
      if (!parse_tfeedback_decls(ctx, prog, mem_ctx, num_tfeedback_decls,
                                 prog->TransformFeedback.VaryingNames,
                                 tfeedback_decls))
         goto done;
   }

   /* Linking the stages in the opposite order (from fragment to vertex)
    * ensures that inter-shader outputs written to in an earlier stage are
    * eliminated if they are (transitively) not used in a later stage.
    */
   int last, next;
   for (last = MESA_SHADER_FRAGMENT; last >= 0; last--) {
      if (prog->_LinkedShaders[last] != NULL)
         break;
   }

   if (last >= 0 && last < MESA_SHADER_FRAGMENT) {
      gl_shader *const sh = prog->_LinkedShaders[last];

      if (num_tfeedback_decls != 0 || prog->SeparateShader) {
         /* There was no fragment shader, but we still have to assign varying
          * locations for use by transform feedback.
          */
         if (!assign_varying_locations(ctx, mem_ctx, prog,
                                       sh, NULL,
                                       num_tfeedback_decls, tfeedback_decls,
                                       0))
            goto done;
      }

      do_dead_builtin_varyings(ctx, sh, NULL,
                               num_tfeedback_decls, tfeedback_decls);

      if (!prog->SeparateShader)
         demote_shader_inputs_and_outputs(sh, ir_var_shader_out);

      /* Eliminate code that is now dead due to unused outputs being demoted.
       */
      while (do_dead_code(sh->ir, false))
         ;
   }
   else if (first == MESA_SHADER_FRAGMENT) {
      /* If the program only contains a fragment shader...
       */
      gl_shader *const sh = prog->_LinkedShaders[first];

      do_dead_builtin_varyings(ctx, NULL, sh,
                               num_tfeedback_decls, tfeedback_decls);

      if (prog->SeparateShader) {
         if (!assign_varying_locations(ctx, mem_ctx, prog,
                                       NULL /* producer */,
                                       sh /* consumer */,
                                       0 /* num_tfeedback_decls */,
                                       NULL /* tfeedback_decls */,
                                       0 /* gs_input_vertices */))
            goto done;
      } else
         demote_shader_inputs_and_outputs(sh, ir_var_shader_in);

      while (do_dead_code(sh->ir, false))
         ;
   }

   next = last;
   for (int i = next - 1; i >= 0; i--) {
      if (prog->_LinkedShaders[i] == NULL)
         continue;

      gl_shader *const sh_i = prog->_LinkedShaders[i];
      gl_shader *const sh_next = prog->_LinkedShaders[next];
      unsigned gs_input_vertices =
         next == MESA_SHADER_GEOMETRY ? prog->Geom.VerticesIn : 0;

      if (!assign_varying_locations(ctx, mem_ctx, prog, sh_i, sh_next,
                next == MESA_SHADER_FRAGMENT ? num_tfeedback_decls : 0,
                tfeedback_decls, gs_input_vertices))
         goto done;

      do_dead_builtin_varyings(ctx, sh_i, sh_next,
                next == MESA_SHADER_FRAGMENT ? num_tfeedback_decls : 0,
                tfeedback_decls);

      demote_shader_inputs_and_outputs(sh_i, ir_var_shader_out);
      demote_shader_inputs_and_outputs(sh_next, ir_var_shader_in);

      /* Eliminate code that is now dead due to unused outputs being demoted.
       */
      while (do_dead_code(sh_i->ir, false))
         ;
      while (do_dead_code(sh_next->ir, false))
         ;

      /* This must be done after all dead varyings are eliminated. */
      if (!check_against_output_limit(ctx, prog, sh_i))
         goto done;
      if (!check_against_input_limit(ctx, prog, sh_next))
         goto done;

      next = i;
   }

   if (!store_tfeedback_info(ctx, prog, num_tfeedback_decls, tfeedback_decls))
      goto done;

   update_array_sizes(prog);
   link_assign_uniform_locations(prog, ctx->Const.UniformBooleanTrue);
   link_assign_atomic_counter_resources(ctx, prog);
   store_fragdepth_layout(prog);

   check_resources(ctx, prog);
   check_image_resources(ctx, prog);
   link_check_atomic_counter_resources(ctx, prog);

   if (!prog->LinkStatus)
      goto done;

   /* OpenGL ES requires that a vertex shader and a fragment shader both be
    * present in a linked program. GL_ARB_ES2_compatibility doesn't say
    * anything about shader linking when one of the shaders (vertex or
    * fragment shader) is absent. So, the extension shouldn't change the
    * behavior specified in GLSL specification.
    */
   if (!prog->SeparateShader && ctx->API == API_OPENGLES2) {
      if (prog->_LinkedShaders[MESA_SHADER_VERTEX] == NULL) {
	 linker_error(prog, "program lacks a vertex shader\n");
      } else if (prog->_LinkedShaders[MESA_SHADER_FRAGMENT] == NULL) {
	 linker_error(prog, "program lacks a fragment shader\n");
      }
   }

   /* FINISHME: Assign fragment shader output locations. */

done:
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      free(shader_list[i]);
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      /* Do a final validation step to make sure that the IR wasn't
       * invalidated by any modifications performed after intrastage linking.
       */
      validate_ir_tree(prog->_LinkedShaders[i]->ir);

      /* Retain any live IR, but trash the rest. */
      reparent_ir(prog->_LinkedShaders[i]->ir, prog->_LinkedShaders[i]->ir);

      /* The symbol table in the linked shaders may contain references to
       * variables that were removed (e.g., unused uniforms).  Since it may
       * contain junk, there is no possible valid use.  Delete it and set the
       * pointer to NULL.
       */
      delete prog->_LinkedShaders[i]->symbols;
      prog->_LinkedShaders[i]->symbols = NULL;
   }

   ralloc_free(mem_ctx);
}

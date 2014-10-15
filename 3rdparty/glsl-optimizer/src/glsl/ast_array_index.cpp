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

#include "ast.h"
#include "glsl_types.h"
#include "ir.h"

void
ast_array_specifier::print(void) const
{
   if (this->is_unsized_array) {
      printf("[ ] ");
   }

   foreach_list_typed (ast_node, array_dimension, link, &this->array_dimensions) {
      printf("[ ");
      array_dimension->print();
      printf("] ");
   }
}

/**
 * If \c ir is a reference to an array for which we are tracking the max array
 * element accessed, track that the given element has been accessed.
 * Otherwise do nothing.
 *
 * This function also checks whether the array is a built-in array whose
 * maximum size is too small to accommodate the given index, and if so uses
 * loc and state to report the error.
 */
static void
update_max_array_access(ir_rvalue *ir, unsigned idx, YYLTYPE *loc,
                        struct _mesa_glsl_parse_state *state)
{
   if (ir_dereference_variable *deref_var = ir->as_dereference_variable()) {
      ir_variable *var = deref_var->var;
      if (idx > var->data.max_array_access) {
         var->data.max_array_access = idx;

         /* Check whether this access will, as a side effect, implicitly cause
          * the size of a built-in array to be too large.
          */
         check_builtin_array_max_size(var->name, idx+1, *loc, state);
      }
   } else if (ir_dereference_record *deref_record =
              ir->as_dereference_record()) {
      /* There are two possibilities we need to consider:
       *
       * - Accessing an element of an array that is a member of a named
       *   interface block (e.g. ifc.foo[i])
       *
       * - Accessing an element of an array that is a member of a named
       *   interface block array (e.g. ifc[j].foo[i]).
       */
      ir_dereference_variable *deref_var =
         deref_record->record->as_dereference_variable();
      if (deref_var == NULL) {
         if (ir_dereference_array *deref_array =
             deref_record->record->as_dereference_array()) {
            deref_var = deref_array->array->as_dereference_variable();
         }
      }

      if (deref_var != NULL) {
         if (deref_var->var->is_interface_instance()) {
            const glsl_type *interface_type =
               deref_var->var->get_interface_type();
            unsigned field_index =
               deref_record->record->type->field_index(deref_record->field);
            assert(field_index < interface_type->length);

            unsigned *const max_ifc_array_access =
               deref_var->var->get_max_ifc_array_access();

            assert(max_ifc_array_access != NULL);

            if (idx > max_ifc_array_access[field_index]) {
               max_ifc_array_access[field_index] = idx;

               /* Check whether this access will, as a side effect, implicitly
                * cause the size of a built-in array to be too large.
                */
               check_builtin_array_max_size(deref_record->field, idx+1, *loc,
                                            state);
            }
         }
      }
   }
}


ir_rvalue *
_mesa_ast_array_index_to_hir(void *mem_ctx,
			     struct _mesa_glsl_parse_state *state,
			     ir_rvalue *array, ir_rvalue *idx,
			     YYLTYPE &loc, YYLTYPE &idx_loc)
{
   if (!array->type->is_error()
       && !array->type->is_array()
       && !array->type->is_matrix()
       && !array->type->is_vector()) {
      _mesa_glsl_error(& idx_loc, state,
		       "cannot dereference non-array / non-matrix / "
		       "non-vector");
   }

   if (!idx->type->is_error()) {
      if (!idx->type->is_integer()) {
	 _mesa_glsl_error(& idx_loc, state, "array index must be integer type");
      } else if (!idx->type->is_scalar()) {
	 _mesa_glsl_error(& idx_loc, state, "array index must be scalar");
      }
   }

   /* If the array index is a constant expression and the array has a
    * declared size, ensure that the access is in-bounds.  If the array
    * index is not a constant expression, ensure that the array has a
    * declared size.
    */
   ir_constant *const const_index = idx->constant_expression_value();
   if (const_index != NULL && idx->type->is_integer()) {
      const int idx = const_index->value.i[0];
      const char *type_name = "error";
      unsigned bound = 0;

      /* From page 24 (page 30 of the PDF) of the GLSL 1.50 spec:
       *
       *    "It is illegal to declare an array with a size, and then
       *    later (in the same shader) index the same array with an
       *    integral constant expression greater than or equal to the
       *    declared size. It is also illegal to index an array with a
       *    negative constant expression."
       */
      if (array->type->is_matrix()) {
	 if (array->type->row_type()->vector_elements <= (unsigned)idx) {
	    type_name = "matrix";
	    bound = array->type->row_type()->vector_elements;
	 }
      } else if (array->type->is_vector()) {
	 if (array->type->vector_elements <= (unsigned)idx) {
	    type_name = "vector";
	    bound = array->type->vector_elements;
	 }
      } else {
	 /* glsl_type::array_size() returns -1 for non-array types.  This means
	  * that we don't need to verify that the type is an array before
	  * doing the bounds checking.
	  */
	 if ((array->type->array_size() > 0)
	     && (array->type->array_size() <= idx)) {
	    type_name = "array";
	    bound = array->type->array_size();
	 }
      }

      if (bound > 0) {
	 _mesa_glsl_error(& loc, state, "%s index must be < %u",
			  type_name, bound);
      } else if (idx < 0) {
	 _mesa_glsl_error(& loc, state, "%s index must be >= 0",
			  type_name);
      }

      if (array->type->is_array())
         update_max_array_access(array, idx, &loc, state);
   } else if (const_index == NULL && array->type->is_array()) {
      if (array->type->is_unsized_array()) {
	 _mesa_glsl_error(&loc, state, "unsized array index must be constant");
      } else if (array->type->fields.array->is_interface()
                 && array->variable_referenced()->data.mode == ir_var_uniform
                 && !state->is_version(400, 0) && !state->ARB_gpu_shader5_enable) {
	 /* Page 46 in section 4.3.7 of the OpenGL ES 3.00 spec says:
	  *
	  *     "All indexes used to index a uniform block array must be
	  *     constant integral expressions."
	  */
	 _mesa_glsl_error(&loc, state,
			  "uniform block array index must be constant");
      } else {
	 /* whole_variable_referenced can return NULL if the array is a
	  * member of a structure.  In this case it is safe to not update
	  * the max_array_access field because it is never used for fields
	  * of structures.
	  */
	 ir_variable *v = array->whole_variable_referenced();
	 if (v != NULL)
	    v->data.max_array_access = array->type->array_size() - 1;
      }

      /* From page 23 (29 of the PDF) of the GLSL 1.30 spec:
       *
       *    "Samplers aggregated into arrays within a shader (using square
       *    brackets [ ]) can only be indexed with integral constant
       *    expressions [...]."
       *
       * This restriction was added in GLSL 1.30.  Shaders using earlier
       * version of the language should not be rejected by the compiler
       * front-end for using this construct.  This allows useful things such
       * as using a loop counter as the index to an array of samplers.  If the
       * loop in unrolled, the code should compile correctly.  Instead, emit a
       * warning.
       *
       * In GLSL 4.00 / ARB_gpu_shader5, this requirement is relaxed again to allow
       * indexing with dynamically uniform expressions. Note that these are not
       * required to be uniforms or expressions based on them, but merely that the
       * values must not diverge between shader invocations run together. If the
       * values *do* diverge, then the behavior of the operation requiring a
       * dynamically uniform expression is undefined.
       */
      if (array->type->element_type()->is_sampler()) {
	 if (!state->is_version(130, 100)) {
	    if (state->es_shader) {
	       _mesa_glsl_warning(&loc, state,
				  "sampler arrays indexed with non-constant "
				  "expressions is optional in %s",
				  state->get_version_string());
	    } else {
	       _mesa_glsl_warning(&loc, state,
				  "sampler arrays indexed with non-constant "
				  "expressions will be forbidden in GLSL 1.30 "
				  "and later");
	    }
	 } else if (!state->is_version(400, 0) && !state->ARB_gpu_shader5_enable) {
	    _mesa_glsl_error(&loc, state,
			     "sampler arrays indexed with non-constant "
			     "expressions is forbidden in GLSL 1.30 and "
			     "later");
	 }
      }
   }

   /* After performing all of the error checking, generate the IR for the
    * expression.
    */
   if (array->type->is_array()
       || array->type->is_matrix()) {
      return new(mem_ctx) ir_dereference_array(array, idx);
   } else if (array->type->is_vector()) {
      return new(mem_ctx) ir_expression(ir_binop_vector_extract, array, idx);
   } else if (array->type->is_error()) {
      return array;
   } else {
      ir_rvalue *result = new(mem_ctx) ir_dereference_array(array, idx);
      result->type = glsl_type::error_type;

      return result;
   }
}

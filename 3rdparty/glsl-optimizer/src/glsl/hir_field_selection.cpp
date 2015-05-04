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

#include "ir.h"
#include "glsl_parser_extras.h"
#include "ast.h"
#include "glsl_types.h"

ir_rvalue *
_mesa_ast_field_selection_to_hir(const ast_expression *expr,
				 exec_list *instructions,
				 struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   ir_rvalue *result = NULL;
   ir_rvalue *op;

   op = expr->subexpressions[0]->hir(instructions, state);

   /* There are two kinds of field selection.  There is the selection of a
    * specific field from a structure, and there is the selection of a
    * swizzle / mask from a vector.  Which is which is determined entirely
    * by the base type of the thing to which the field selection operator is
    * being applied.
    */
   YYLTYPE loc = expr->get_location();
   if (op->type->is_error()) {
      /* silently propagate the error */
   } else if (op->type->base_type == GLSL_TYPE_STRUCT
              || op->type->base_type == GLSL_TYPE_INTERFACE) {
      result = new(ctx) ir_dereference_record(op,
					      expr->primary_expression.identifier);

      if (result->type->is_error()) {
	 _mesa_glsl_error(& loc, state, "cannot access field `%s' of "
			  "structure",
			  expr->primary_expression.identifier);
      }
   } else if (expr->subexpressions[1] != NULL) {
      /* Handle "method calls" in GLSL 1.20 - namely, array.length() */
      state->check_version(120, 300, &loc, "methods not supported");

      ast_expression *call = expr->subexpressions[1];
      assert(call->oper == ast_function_call);

      const char *method;
      method = call->subexpressions[0]->primary_expression.identifier;

      if (strcmp(method, "length") == 0) {
         if (!call->expressions.is_empty())
            _mesa_glsl_error(&loc, state, "length method takes no arguments");

         if (op->type->is_array()) {
            if (op->type->is_unsized_array())
               _mesa_glsl_error(&loc, state, "length called on unsized array");

            result = new(ctx) ir_constant(op->type->array_size());
         } else if (op->type->is_vector()) {
            if (state->ARB_shading_language_420pack_enable) {
               /* .length() returns int. */
               result = new(ctx) ir_constant((int) op->type->vector_elements);
            } else {
               _mesa_glsl_error(&loc, state, "length method on matrix only available"
                                             "with ARB_shading_language_420pack");
            }
         } else if (op->type->is_matrix()) {
            if (state->ARB_shading_language_420pack_enable) {
               /* .length() returns int. */
               result = new(ctx) ir_constant((int) op->type->matrix_columns);
            } else {
               _mesa_glsl_error(&loc, state, "length method on matrix only available"
                                             "with ARB_shading_language_420pack");
            }
         }
      } else {
	 _mesa_glsl_error(&loc, state, "unknown method: `%s'", method);
      }
   } else if (op->type->is_vector() ||
              (state->ARB_shading_language_420pack_enable &&
               op->type->is_scalar())) {
      ir_swizzle *swiz = ir_swizzle::create(op,
					    expr->primary_expression.identifier,
					    op->type->vector_elements);
      if (swiz != NULL) {
	 result = swiz;
      } else {
	 /* FINISHME: Logging of error messages should be moved into
	  * FINISHME: ir_swizzle::create.  This allows the generation of more
	  * FINISHME: specific error messages.
	  */
	 _mesa_glsl_error(& loc, state, "invalid swizzle / mask `%s'",
			  expr->primary_expression.identifier);
      }
   } else {
      _mesa_glsl_error(& loc, state, "cannot access field `%s' of "
		       "non-structure / non-vector",
		       expr->primary_expression.identifier);
   }

   return result ? result : ir_rvalue::error_value(ctx);
}

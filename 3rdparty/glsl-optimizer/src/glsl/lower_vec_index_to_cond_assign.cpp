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
 * \file lower_vec_index_to_cond_assign.cpp
 *
 * Turns indexing into vector types to a series of conditional moves
 * of each channel's swizzle into a temporary.
 *
 * Most GPUs don't have a native way to do this operation, and this
 * works around that.  For drivers using both this pass and
 * ir_vec_index_to_swizzle, there's a risk that this pass will happen
 * before sufficient constant folding to find that the array index is
 * constant.  However, we hope that other optimization passes,
 * particularly constant folding of assignment conditions and copy
 * propagation, will result in the same code in the end.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_optimization.h"
#include "glsl_types.h"

namespace {

/**
 * Visitor class for replacing expressions with ir_constant values.
 */

class ir_vec_index_to_cond_assign_visitor : public ir_hierarchical_visitor {
public:
   ir_vec_index_to_cond_assign_visitor()
   {
      progress = false;
   }

   ir_rvalue *convert_vec_index_to_cond_assign(void *mem_ctx,
                                               ir_rvalue *orig_vector,
                                               ir_rvalue *orig_index,
                                               const glsl_type *type);

   ir_rvalue *convert_vector_extract_to_cond_assign(ir_rvalue *ir);

   virtual ir_visitor_status visit_enter(ir_expression *);
   virtual ir_visitor_status visit_enter(ir_swizzle *);
   virtual ir_visitor_status visit_leave(ir_assignment *);
   virtual ir_visitor_status visit_enter(ir_return *);
   virtual ir_visitor_status visit_enter(ir_call *);
   virtual ir_visitor_status visit_enter(ir_if *);

   bool progress;
};

} /* anonymous namespace */

ir_rvalue *
ir_vec_index_to_cond_assign_visitor::convert_vec_index_to_cond_assign(void *mem_ctx,
                                                                      ir_rvalue *orig_vector,
                                                                      ir_rvalue *orig_index,
                                                                      const glsl_type *type)
{
   ir_assignment *assign, *value_assign;
   ir_variable *index, *var, *value;
   ir_dereference *deref, *deref_value;
   unsigned i;


   exec_list list;

   /* Store the index to a temporary to avoid reusing its tree. */
   index = new(base_ir) ir_variable(glsl_type::int_type,
				    "vec_index_tmp_i",
				    ir_var_temporary, glsl_precision_undefined);
	list.push_tail(index);
   deref = new(base_ir) ir_dereference_variable(index);
   assign = new(base_ir) ir_assignment(deref, orig_index, NULL);
   list.push_tail(assign);

   /* Store the value inside a temp, thus avoiding matrixes duplication */
   value = new(base_ir) ir_variable(orig_vector->type, "vec_value_tmp",
                                    ir_var_temporary, orig_vector->get_precision());
   list.push_tail(value);
   deref_value = new(base_ir) ir_dereference_variable(value);
   value_assign = new(base_ir) ir_assignment(deref_value, orig_vector);
   list.push_tail(value_assign);

   /* Temporary where we store whichever value we swizzle out. */
   var = new(base_ir) ir_variable(type, "vec_index_tmp_v",
				  ir_var_temporary, orig_vector->get_precision());
   list.push_tail(var);

   /* Generate a single comparison condition "mask" for all of the components
    * in the vector.
    */
   ir_rvalue *const cond_deref =
      compare_index_block(&list, index, 0,
                          orig_vector->type->vector_elements,
			  mem_ctx);

   /* Generate a conditional move of each vector element to the temp. */
   for (i = 0; i < (int)orig_vector->type->vector_elements; i++) {
      ir_rvalue *condition_swizzle =
         new(base_ir) ir_swizzle(cond_deref->clone(mem_ctx, NULL),
                                 i, 0, 0, 0, 1);

      /* Just clone the rest of the deref chain when trying to get at the
       * underlying variable.
       */
      ir_rvalue *swizzle =
	 new(base_ir) ir_swizzle(deref_value->clone(mem_ctx, NULL),
				 i, 0, 0, 0, 1);

      deref = new(base_ir) ir_dereference_variable(var);
      assign = new(base_ir) ir_assignment(deref, swizzle, condition_swizzle);
      list.push_tail(assign);
   }

   /* Put all of the new instructions in the IR stream before the old
    * instruction.
    */
   base_ir->insert_before(&list);

   this->progress = true;
   return new(base_ir) ir_dereference_variable(var);
}

ir_rvalue *
ir_vec_index_to_cond_assign_visitor::convert_vector_extract_to_cond_assign(ir_rvalue *ir)
{
   ir_expression *const expr = ir->as_expression();

   if (expr == NULL || expr->operation != ir_binop_vector_extract)
      return ir;

   return convert_vec_index_to_cond_assign(ralloc_parent(ir),
                                           expr->operands[0],
                                           expr->operands[1],
                                           ir->type);
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_enter(ir_expression *ir)
{
   unsigned int i;

   for (i = 0; i < ir->get_num_operands(); i++) {
      ir->operands[i] = convert_vector_extract_to_cond_assign(ir->operands[i]);
   }

   return visit_continue;
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_enter(ir_swizzle *ir)
{
   /* Can't be hit from normal GLSL, since you can't swizzle a scalar (which
    * the result of indexing a vector is.  But maybe at some point we'll end up
    * using swizzling of scalars for vector construction.
    */
   ir->val = convert_vector_extract_to_cond_assign(ir->val);

   return visit_continue;
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_leave(ir_assignment *ir)
{

   ir->rhs = convert_vector_extract_to_cond_assign(ir->rhs);

   if (ir->condition) {
      ir->condition = convert_vector_extract_to_cond_assign(ir->condition);
   }

   return visit_continue;
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_enter(ir_call *ir)
{
   foreach_in_list_safe(ir_rvalue, param, &ir->actual_parameters) {
      ir_rvalue *new_param = convert_vector_extract_to_cond_assign(param);

      if (new_param != param) {
	 param->replace_with(new_param);
      }
   }

   return visit_continue;
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_enter(ir_return *ir)
{
   if (ir->value) {
      ir->value = convert_vector_extract_to_cond_assign(ir->value);
   }

   return visit_continue;
}

ir_visitor_status
ir_vec_index_to_cond_assign_visitor::visit_enter(ir_if *ir)
{
   ir->condition = convert_vector_extract_to_cond_assign(ir->condition);

   return visit_continue;
}

bool
do_vec_index_to_cond_assign(exec_list *instructions)
{
   ir_vec_index_to_cond_assign_visitor v;

   visit_list_elements(&v, instructions);

   return v.progress;
}

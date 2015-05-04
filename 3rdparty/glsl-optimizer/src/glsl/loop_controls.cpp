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

#include <limits.h>
#include "main/compiler.h"
#include "glsl_types.h"
#include "loop_analysis.h"
#include "ir_hierarchical_visitor.h"
#include "ir_variable_refcount.h"


/**
 * Find an initializer of a variable outside a loop
 *
 * Works backwards from the loop to find the pre-loop value of the variable.
 * This is used, for example, to find the initial value of loop induction
 * variables.
 *
 * \param loop  Loop where \c var is an induction variable
 * \param var   Variable whose initializer is to be found
 *
 * \return
 * The \c ir_rvalue assigned to the variable outside the loop.  May return
 * \c NULL if no initializer can be found.
 */
ir_rvalue *
find_initial_value(ir_loop *loop, ir_variable *var, ir_instruction **out_containing_ir)
{
   *out_containing_ir = NULL;
   ir_variable_refcount_visitor refs;
   
   for (exec_node *node = loop->prev;
	!node->is_head_sentinel();
	node = node->prev) {
      ir_instruction *ir = (ir_instruction *) node;

      switch (ir->ir_type) {
      case ir_type_call:
      case ir_type_loop:
      case ir_type_loop_jump:
      case ir_type_return:
      case ir_type_if:
         ir->accept(&refs);
         if (refs.find_variable_entry(var))
            return NULL;
         break;

      case ir_type_function:
      case ir_type_function_signature:
	 assert(!"Should not get here.");
	 return NULL;

      case ir_type_assignment: {
	 ir_assignment *assign = ir->as_assignment();
	 ir_variable *assignee = assign->lhs->whole_variable_referenced();

	 if (assignee == var)
	 {
	    *out_containing_ir = assign;
	    return (assign->condition != NULL) ? NULL : assign->rhs;
	 }

	 break;
      }

      default:
	 break;
      }
   }

   return NULL;
}


int
calculate_iterations(ir_rvalue *from, ir_rvalue *to, ir_rvalue *increment,
		     enum ir_expression_operation op)
{
   if (from == NULL || to == NULL || increment == NULL)
      return -1;

   void *mem_ctx = ralloc_context(NULL);

   ir_expression *const sub =
      new(mem_ctx) ir_expression(ir_binop_sub, from->type, to, from);

   ir_expression *const div =
      new(mem_ctx) ir_expression(ir_binop_div, sub->type, sub, increment);

   ir_constant *iter = div->constant_expression_value();

   if (iter == NULL)
      return -1;

   if (!iter->type->is_integer()) {
      ir_rvalue *cast =
	 new(mem_ctx) ir_expression(ir_unop_f2i, glsl_type::int_type, iter,
				    NULL);

      iter = cast->constant_expression_value();
   }

   int iter_value = iter->get_int_component(0);

   /* Make sure that the calculated number of iterations satisfies the exit
    * condition.  This is needed to catch off-by-one errors and some types of
    * ill-formed loops.  For example, we need to detect that the following
    * loop does not have a maximum iteration count.
    *
    *    for (float x = 0.0; x != 0.9; x += 0.2)
    *        ;
    */
   const int bias[] = { -1, 0, 1 };
   bool valid_loop = false;

   for (unsigned i = 0; i < Elements(bias); i++) {
      /* Increment may be of type int, uint or float. */
      switch (increment->type->base_type) {
      case GLSL_TYPE_INT:
         iter = new(mem_ctx) ir_constant(iter_value + bias[i]);
         break;
      case GLSL_TYPE_UINT:
         iter = new(mem_ctx) ir_constant(unsigned(iter_value + bias[i]));
         break;
      case GLSL_TYPE_FLOAT:
         iter = new(mem_ctx) ir_constant(float(iter_value + bias[i]));
         break;
      default:
          unreachable(!"Unsupported type for loop iterator.");
      }

      ir_expression *const mul =
	 new(mem_ctx) ir_expression(ir_binop_mul, increment->type, iter,
				    increment);

      ir_expression *const add =
	 new(mem_ctx) ir_expression(ir_binop_add, mul->type, mul, from);

      ir_expression *const cmp =
	 new(mem_ctx) ir_expression(op, glsl_type::bool_type, add, to);

      ir_constant *const cmp_result = cmp->constant_expression_value();

      assert(cmp_result != NULL);
      if (cmp_result->get_bool_component(0)) {
	 iter_value += bias[i];
	 valid_loop = true;
	 break;
      }
   }

   ralloc_free(mem_ctx);
   return (valid_loop) ? iter_value : -1;
}

namespace {

class loop_control_visitor : public ir_hierarchical_visitor {
public:
   loop_control_visitor(loop_state *state)
   {
      this->state = state;
      this->progress = false;
   }

   virtual ir_visitor_status visit_leave(ir_loop *ir);

   loop_state *state;

   bool progress;
};

} /* anonymous namespace */

ir_visitor_status
loop_control_visitor::visit_leave(ir_loop *ir)
{
   loop_variable_state *const ls = this->state->get(ir);

   /* If we've entered a loop that hasn't been analyzed, something really,
    * really bad has happened.
    */
   if (ls == NULL) {
      assert(ls != NULL);
      return visit_continue;
   }

   if (ls->limiting_terminator != NULL) {
      /* If the limiting terminator has an iteration count of zero, then we've
       * proven that the loop cannot run, so delete it.
       */
      int iterations = ls->limiting_terminator->iterations;
      if (iterations == 0) {
         ir->remove();
         this->progress = true;
         return visit_continue;
      }
   }

   /* Remove the conditional break statements associated with all terminators
    * that are associated with a fixed iteration count, except for the one
    * associated with the limiting terminator--that one needs to stay, since
    * it terminates the loop.  Exception: if the loop still has a normative
    * bound, then that terminates the loop, so we don't even need the limiting
    * terminator.
    */
   foreach_in_list(loop_terminator, t, &ls->terminators) {
      if (t->iterations < 0)
         continue;

      if (t != ls->limiting_terminator) {
         t->ir->remove();

         assert(ls->num_loop_jumps > 0);
         ls->num_loop_jumps--;

         this->progress = true;
      }
   }

   return visit_continue;
}


bool
set_loop_controls(exec_list *instructions, loop_state *ls)
{
   loop_control_visitor v(ls);

   v.run(instructions);

   return v.progress;
}

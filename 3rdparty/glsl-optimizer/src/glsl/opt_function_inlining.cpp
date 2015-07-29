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
 * \file opt_function_inlining.cpp
 *
 * Replaces calls to functions with the body of the function.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_function_inlining.h"
#include "ir_expression_flattening.h"
#include "glsl_types.h"
#include "program/hash_table.h"

static void
do_variable_replacement(exec_list *instructions,
                        ir_variable *orig,
                        ir_dereference *repl);

namespace {

class ir_function_inlining_visitor : public ir_hierarchical_visitor {
public:
   ir_function_inlining_visitor()
   {
      progress = false;
	  current_function = NULL;
   }

   virtual ~ir_function_inlining_visitor()
   {
      /* empty */
   }

   virtual ir_visitor_status visit_enter(ir_expression *);
   virtual ir_visitor_status visit_enter(ir_call *);
   virtual ir_visitor_status visit_enter(ir_return *);
   virtual ir_visitor_status visit_enter(ir_texture *);
   virtual ir_visitor_status visit_enter(ir_swizzle *);

   virtual ir_visitor_status visit_enter(ir_function_signature *sig)
   {
	   this->current_function = sig;
	   return ir_hierarchical_visitor::visit_enter(sig);
   }
   virtual ir_visitor_status visit_leave(ir_function_signature *sig)
   {
	   this->current_function = NULL;
	   return ir_hierarchical_visitor::visit_leave(sig);
   }

   ir_function_signature* current_function;
   bool progress;

};

} /* unnamed namespace */

bool
do_function_inlining(exec_list *instructions)
{
   ir_function_inlining_visitor v;

   v.run(instructions);

   return v.progress;
}

static void
replace_return_with_assignment(ir_instruction *ir, void *data)
{
   void *ctx = ralloc_parent(ir);
   ir_dereference *orig_deref = (ir_dereference *) data;
   ir_return *ret = ir->as_return();

   if (ret) {
      if (ret->value) {
	 ir_rvalue *lhs = orig_deref->clone(ctx, NULL);
	 ret->replace_with(new(ctx) ir_assignment(lhs, ret->value, NULL));
      } else {
	 /* un-valued return has to be the last return, or we shouldn't
	  * have reached here. (see can_inline()).
	  */
	 assert(ret->next->is_tail_sentinel());
	 ret->remove();
      }
   }
}

void
ir_call::generate_inline(ir_instruction *next_ir)
{
   void *ctx = ralloc_parent(this);
   ir_variable **parameters;
   unsigned num_parameters;
   int i;
   struct hash_table *ht;

   ht = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);

   num_parameters = this->callee->parameters.length();
   parameters = new ir_variable *[num_parameters];

   /* Generate the declarations for the parameters to our inlined code,
    * and set up the mapping of real function body variables to ours.
    */
   i = 0;
   glsl_precision prec_params_max = glsl_precision_undefined;
   foreach_two_lists(formal_node, &this->callee->parameters,
                     actual_node, &this->actual_parameters) {
      ir_variable *sig_param = (ir_variable *) formal_node;
      ir_rvalue *param = (ir_rvalue *) actual_node;

      /* Generate a new variable for the parameter. */
      if (sig_param->type->contains_opaque()) {
	 /* For opaque types, we want the inlined variable references
	  * referencing the passed in variable, since that will have
	  * the location information, which an assignment of an opaque
	  * variable wouldn't.  Fix it up below.
	  */
	 parameters[i] = NULL;
      } else {
	 parameters[i] = sig_param->clone(ctx, ht);
	 parameters[i]->data.mode = ir_var_auto;

     parameters[i]->data.precision = (glsl_precision)parameters[i]->data.precision;
     if (parameters[i]->data.precision == glsl_precision_undefined)
        parameters[i]->data.precision = param->get_precision();
     prec_params_max = higher_precision (prec_params_max, (glsl_precision)parameters[i]->data.precision);

	 /* Remove the read-only decoration because we're going to write
	  * directly to this variable.  If the cloned variable is left
	  * read-only and the inlined function is inside a loop, the loop
	  * analysis code will get confused.
	  */
	 parameters[i]->data.read_only = false;
	 next_ir->insert_before(parameters[i]);
      }

      /* Move the actual param into our param variable if it's an 'in' type. */
      if (parameters[i] && (sig_param->data.mode == ir_var_function_in ||
			    sig_param->data.mode == ir_var_const_in ||
			    sig_param->data.mode == ir_var_function_inout)) {
	 ir_assignment *assign;

	 assign = new(ctx) ir_assignment(new(ctx) ir_dereference_variable(parameters[i]),
					 param, NULL);
	 next_ir->insert_before(assign);
      }

      ++i;
   }
	
   exec_list new_instructions;

   /* Generate the inlined body of the function to a new list */
   foreach_in_list(ir_instruction, ir, &callee->body) {
      ir_instruction *new_ir = ir->clone(ctx, ht);

      new_instructions.push_tail(new_ir);
      visit_tree(new_ir, replace_return_with_assignment, this->return_deref);
   }

   /* If any opaque types were passed in, replace any deref of the
    * opaque variable with a deref of the argument.
    */
   foreach_two_lists(formal_node, &this->callee->parameters,
                     actual_node, &this->actual_parameters) {
      ir_rvalue *const param = (ir_rvalue *) actual_node;
      ir_variable *sig_param = (ir_variable *) formal_node;

      if (sig_param->type->contains_opaque()) {
	 ir_dereference *deref = param->as_dereference();

	 assert(deref);
	 do_variable_replacement(&new_instructions, sig_param, deref);
      }
   }

   /* Now push those new instructions in. */
   next_ir->insert_before(&new_instructions);

   /* Copy back the value of any 'out' parameters from the function body
    * variables to our own.
    */
   i = 0;
   foreach_two_lists(formal_node, &this->callee->parameters,
                     actual_node, &this->actual_parameters) {
      ir_rvalue *const param = (ir_rvalue *) actual_node;
      const ir_variable *const sig_param = (ir_variable *) formal_node;

      /* Move our param variable into the actual param if it's an 'out' type. */
      if (parameters[i] && (sig_param->data.mode == ir_var_function_out ||
			    sig_param->data.mode == ir_var_function_inout)) {
	 ir_assignment *assign;

	 assign = new(ctx) ir_assignment(param->clone(ctx, NULL)->as_rvalue(),
					 new(ctx) ir_dereference_variable(parameters[i]),
					 NULL);
	 next_ir->insert_before(assign);
      }

      ++i;
   }

   delete [] parameters;

   hash_table_dtor(ht);
}


ir_visitor_status
ir_function_inlining_visitor::visit_enter(ir_expression *ir)
{
   (void) ir;
   return visit_continue_with_parent;
}


ir_visitor_status
ir_function_inlining_visitor::visit_enter(ir_return *ir)
{
   (void) ir;
   return visit_continue_with_parent;
}


ir_visitor_status
ir_function_inlining_visitor::visit_enter(ir_texture *ir)
{
   (void) ir;
   return visit_continue_with_parent;
}


ir_visitor_status
ir_function_inlining_visitor::visit_enter(ir_swizzle *ir)
{
   (void) ir;
   return visit_continue_with_parent;
}


ir_visitor_status
ir_function_inlining_visitor::visit_enter(ir_call *ir)
{
   if (can_inline(ir)) {
      ir->generate_inline(ir);
      ir->remove();
      this->progress = true;
   }

   return visit_continue;
}


/**
 * Replaces references to the "orig" variable with a clone of "repl."
 *
 * From the spec, opaque types can appear in the tree as function
 * (non-out) parameters and as the result of array indexing and
 * structure field selection.  In our builtin implementation, they
 * also appear in the sampler field of an ir_tex instruction.
 */

class ir_variable_replacement_visitor : public ir_hierarchical_visitor {
public:
   ir_variable_replacement_visitor(ir_variable *orig, ir_dereference *repl)
   {
      this->orig = orig;
      this->repl = repl;
   }

   virtual ~ir_variable_replacement_visitor()
   {
   }

   virtual ir_visitor_status visit_leave(ir_call *);
   virtual ir_visitor_status visit_leave(ir_dereference_array *);
   virtual ir_visitor_status visit_leave(ir_dereference_record *);
   virtual ir_visitor_status visit_leave(ir_texture *);

   void replace_deref(ir_dereference **deref);
   void replace_rvalue(ir_rvalue **rvalue);

   ir_variable *orig;
   ir_dereference *repl;
};

void
ir_variable_replacement_visitor::replace_deref(ir_dereference **deref)
{
   ir_dereference_variable *deref_var = (*deref)->as_dereference_variable();
   if (deref_var && deref_var->var == this->orig) {
      *deref = this->repl->clone(ralloc_parent(*deref), NULL);
   }
}

void
ir_variable_replacement_visitor::replace_rvalue(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return;

   ir_dereference *deref = (*rvalue)->as_dereference();

   if (!deref)
      return;

   replace_deref(&deref);
   *rvalue = deref;
}

ir_visitor_status
ir_variable_replacement_visitor::visit_leave(ir_texture *ir)
{
   replace_deref(&ir->sampler);

   return visit_continue;
}

ir_visitor_status
ir_variable_replacement_visitor::visit_leave(ir_dereference_array *ir)
{
   replace_rvalue(&ir->array);
   return visit_continue;
}

ir_visitor_status
ir_variable_replacement_visitor::visit_leave(ir_dereference_record *ir)
{
   replace_rvalue(&ir->record);
   return visit_continue;
}

ir_visitor_status
ir_variable_replacement_visitor::visit_leave(ir_call *ir)
{
   foreach_in_list_safe(ir_rvalue, param, &ir->actual_parameters) {
      ir_rvalue *new_param = param;
      replace_rvalue(&new_param);

      if (new_param != param) {
	 param->replace_with(new_param);
      }
   }
   return visit_continue;
}

static void
do_variable_replacement(exec_list *instructions,
                        ir_variable *orig,
                        ir_dereference *repl)
{
   ir_variable_replacement_visitor v(orig, repl);

   visit_list_elements(&v, instructions);
}

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
 * \file opt_constant_variable.cpp
 *
 * Marks variables assigned a single constant value over the course
 * of the program as constant.
 *
 * The goal here is to trigger further constant folding and then dead
 * code elimination.  This is common with vector/matrix constructors
 * and calls to builtin functions.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_optimization.h"
#include "glsl_types.h"

namespace {

struct assignment_entry {
   exec_node link;
   int assignment_count;
   ir_variable *var;
   ir_constant *constval;
   bool our_scope;
};

class ir_constant_variable_visitor : public ir_hierarchical_visitor {
public:
   virtual ir_visitor_status visit_enter(ir_dereference_variable *);
   virtual ir_visitor_status visit(ir_variable *);
   virtual ir_visitor_status visit_enter(ir_assignment *);
   virtual ir_visitor_status visit_enter(ir_call *);
   virtual ir_visitor_status visit_enter(ir_function_signature *);

   exec_list list;
};

} /* unnamed namespace */

static struct assignment_entry *
get_assignment_entry(ir_variable *var, exec_list *list)
{
   struct assignment_entry *entry;

   foreach_list_typed(struct assignment_entry, entry, link, list) {
      if (entry->var == var)
	 return entry;
   }

   entry = (struct assignment_entry *)calloc(1, sizeof(*entry));
   entry->var = var;
   list->push_head(&entry->link);
   return entry;
}

ir_visitor_status
ir_constant_variable_visitor::visit(ir_variable *ir)
{
   struct assignment_entry *entry = get_assignment_entry(ir, &this->list);
   entry->our_scope = true;
   return visit_continue;
}

/* Skip derefs of variables so that we can detect declarations. */
ir_visitor_status
ir_constant_variable_visitor::visit_enter(ir_dereference_variable *ir)
{
   (void)ir;
   return visit_continue_with_parent;
}

ir_visitor_status
ir_constant_variable_visitor::visit_enter(ir_assignment *ir)
{
   ir_constant *constval;
   struct assignment_entry *entry;

   entry = get_assignment_entry(ir->lhs->variable_referenced(), &this->list);
   assert(entry);
   entry->assignment_count++;

   /* If it's already constant, don't do the work. */
   if (entry->var->constant_value)
      return visit_continue;

   /* OK, now find if we actually have all the right conditions for
    * this to be a constant value assigned to the var.
    */
   if (ir->condition)
      return visit_continue;

   ir_variable *var = ir->whole_variable_written();
   if (!var)
      return visit_continue;

   constval = ir->rhs->constant_expression_value();
   if (!constval)
      return visit_continue;

   /* Mark this entry as having a constant assignment (if the
    * assignment count doesn't go >1).  do_constant_variable will fix
    * up the variable with the constant value later.
    */
   entry->constval = constval;

   return visit_continue;
}

ir_visitor_status
ir_constant_variable_visitor::visit_enter(ir_call *ir)
{
   /* Mark any out parameters as assigned to */
   foreach_two_lists(formal_node, &ir->callee->parameters,
                     actual_node, &ir->actual_parameters) {
      ir_rvalue *param_rval = (ir_rvalue *) actual_node;
      ir_variable *param = (ir_variable *) formal_node;

      if (param->data.mode == ir_var_function_out ||
	  param->data.mode == ir_var_function_inout) {
	 ir_variable *var = param_rval->variable_referenced();
	 struct assignment_entry *entry;

	 assert(var);
	 entry = get_assignment_entry(var, &this->list);
	 entry->assignment_count++;
      }
   }

   /* Mark the return storage as having been assigned to */
   if (ir->return_deref != NULL) {
      ir_variable *var = ir->return_deref->variable_referenced();
      struct assignment_entry *entry;

      assert(var);
      entry = get_assignment_entry(var, &this->list);
      entry->assignment_count++;
   }

   return visit_continue;
}

ir_visitor_status
ir_constant_variable_visitor::visit_enter(ir_function_signature *ir)
{
   /* Mark any in parameters as assigned to */
   foreach_in_list(ir_variable, var, &ir->parameters) {
      if (var->data.mode == ir_var_function_in || var->data.mode == ir_var_const_in || var->data.mode == ir_var_function_inout) {
         struct assignment_entry *entry;
         entry = get_assignment_entry(var, &this->list);
         entry->assignment_count++;
      }
   }
   visit_list_elements(this, &ir->body);
   return visit_continue_with_parent;
}


/**
 * Does a copy propagation pass on the code present in the instruction stream.
 */
bool
do_constant_variable(exec_list *instructions)
{
   bool progress = false;
   ir_constant_variable_visitor v;

   v.run(instructions);

   while (!v.list.is_empty()) {

      struct assignment_entry *entry;
      entry = exec_node_data(struct assignment_entry, v.list.head, link);

      if (entry->assignment_count == 1 && entry->constval && entry->our_scope) {
	 entry->var->constant_value = entry->constval;
	 progress = true;
      }
      entry->link.remove();
      free(entry);
   }

   return progress;
}

bool
do_constant_variable_unlinked(exec_list *instructions)
{
   bool progress = false;

   foreach_in_list(ir_instruction, ir, instructions) {
      ir_function *f = ir->as_function();
      if (f) {
	 foreach_in_list(ir_function_signature, sig, &f->signatures) {
	    if (do_constant_variable(&sig->body))
	       progress = true;
	 }
      }
   }

   return progress;
}

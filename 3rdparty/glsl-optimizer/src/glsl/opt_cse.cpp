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
 * \file opt_cse.cpp
 *
 * constant subexpression elimination at the GLSL IR level.
 *
 * Compare to brw_fs_cse.cpp for a more complete CSE implementation.  This one
 * is generic and handles texture operations, but it's rather simple currently
 * and doesn't support modification of variables in the available expressions
 * list, so it can't do variables other than uniforms or shader inputs.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_rvalue_visitor.h"
#include "ir_basic_block.h"
#include "ir_optimization.h"
#include "ir_builder.h"
#include "glsl_types.h"

using namespace ir_builder;

static bool debug = false;

namespace {

/**
 * This is the record of an available expression for common subexpression
 * elimination.
 */
class ae_entry : public exec_node
{
public:
   ae_entry(ir_instruction *base_ir, ir_rvalue **val)
      : val(val), base_ir(base_ir)
   {
      assert(val);
      assert(*val);
      assert(base_ir);

      var = NULL;
   }

   /**
    * The pointer to the expression that we might be able to reuse
    *
    * Note the double pointer -- this is the place in the base_ir expression
    * tree that we would rewrite to move the expression out to a new variable
    * assignment.
    */
   ir_rvalue **val;

   /**
    * Root instruction in the basic block where the expression appeared.
    *
    * This is used so that we can insert the new variable declaration into the
    * instruction stream (since *val is just somewhere in base_ir's expression
    * tree).
    */
   ir_instruction *base_ir;

   /**
    * The variable that the expression has been stored in, if it's been CSEd
    * once already.
    */
   ir_variable *var;
};

class cse_visitor : public ir_rvalue_visitor {
public:
   cse_visitor(exec_list *validate_instructions)
      : validate_instructions(validate_instructions)
   {
      progress = false;
      mem_ctx = ralloc_context(NULL);
      this->ae = new(mem_ctx) exec_list;
   }
   ~cse_visitor()
   {
      ralloc_free(mem_ctx);
   }

   virtual ir_visitor_status visit_enter(ir_function_signature *ir);
   virtual ir_visitor_status visit_enter(ir_loop *ir);
   virtual ir_visitor_status visit_enter(ir_if *ir);
   virtual ir_visitor_status visit_enter(ir_call *ir);
   virtual void handle_rvalue(ir_rvalue **rvalue);

   bool progress;

private:
   void *mem_ctx;

   ir_rvalue *try_cse(ir_rvalue *rvalue);
   void add_to_ae(ir_rvalue **rvalue);

   /** List of ae_entry: The available expressions to reuse */
   exec_list *ae;

   /**
    * The whole shader, so that we can validate_ir_tree in debug mode.
    *
    * This proved quite useful when trying to get the tree manipulation
    * right.
    */
   exec_list *validate_instructions;
};

/**
 * Visitor to walk an expression tree to check that all variables referenced
 * are constants.
 */
class is_cse_candidate_visitor : public ir_hierarchical_visitor
{
public:

   is_cse_candidate_visitor()
      : ok(true)
   {
   }

   virtual ir_visitor_status visit(ir_dereference_variable *ir);

   bool ok;
};


class contains_rvalue_visitor : public ir_rvalue_visitor
{
public:

   contains_rvalue_visitor(ir_rvalue *val)
      : val(val)
   {
      found = false;
   }

   virtual void handle_rvalue(ir_rvalue **rvalue);

   bool found;

private:
   ir_rvalue *val;
};

} /* unnamed namespace */

static void
dump_ae(exec_list *ae)
{
   int i = 0;

   printf("CSE: AE contents:\n");
   foreach_in_list(ae_entry, entry, ae) {
      printf("CSE:   AE %2d (%p): ", i, entry);
      (*entry->val)->print();
      printf("\n");

      if (entry->var)
         printf("CSE:     in var %p:\n", entry->var);

      i++;
   }
}

ir_visitor_status
is_cse_candidate_visitor::visit(ir_dereference_variable *ir)
{
   /* Currently, since we don't handle kills of the ae based on variables
    * getting assigned, we can only handle constant variables.
    */
   if (ir->var->data.read_only) {
      return visit_continue;
   } else {
      ok = false;
      return visit_stop;
   }
}

void
contains_rvalue_visitor::handle_rvalue(ir_rvalue **rvalue)
{
   if (*rvalue == val)
      found = true;
}

static bool
contains_rvalue(ir_rvalue *haystack, ir_rvalue *needle)
{
   contains_rvalue_visitor v(needle);
   haystack->accept(&v);
   return v.found;
}

static bool
is_cse_candidate(ir_rvalue *ir)
{
   /* Our temporary variable assignment generation isn't ready to handle
    * anything bigger than a vector.
    */
   if (!ir->type->is_vector() && !ir->type->is_scalar())
      return false;

   /* Only handle expressions and textures currently.  We may want to extend
    * to variable-index array dereferences at some point.
    */
   switch (ir->ir_type) {
   case ir_type_expression:
   case ir_type_texture:
      break;
   default:
      return false;
   }

   is_cse_candidate_visitor v;

   ir->accept(&v);

   return v.ok;
}


/**
 * Tries to find and return a reference to a previous computation of a given
 * expression.
 *
 * Walk the list of available expressions checking if any of them match the
 * rvalue, and if so, move the previous copy of the expression to a temporary
 * and return a reference of the temporary.
 */
ir_rvalue *
cse_visitor::try_cse(ir_rvalue *rvalue)
{
   foreach_in_list(ae_entry, entry, ae) {
      if (debug) {
         printf("Comparing to AE %p: ", entry);
         (*entry->val)->print();
         printf("\n");
      }

      if (!rvalue->equals(*entry->val))
         continue;

      if (debug) {
         printf("CSE: Replacing: ");
         (*entry->val)->print();
         printf("\n");
         printf("CSE:      with: ");
         rvalue->print();
         printf("\n");
      }

      if (!entry->var) {
         ir_instruction *base_ir = entry->base_ir;

         ir_variable *var = new(rvalue) ir_variable(rvalue->type,
                                                    "cse",
                                                    ir_var_temporary, rvalue->get_precision());

         /* Write the previous expression result into a new variable. */
         base_ir->insert_before(var);
         ir_assignment *assignment = assign(var, *entry->val);
         base_ir->insert_before(assignment);

         /* Replace the expression in the original tree with a deref of the
          * variable, but keep tracking the expression for further reuse.
          */
         *entry->val = new(rvalue) ir_dereference_variable(var);
         entry->val = &assignment->rhs;

         entry->var = var;

         /* Update the base_irs in the AE list.  We have to be sure that
          * they're correct -- expressions from our base_ir that weren't moved
          * need to stay in this base_ir (so that later consumption of them
          * puts new variables between our new variable and our base_ir), but
          * expressions from our base_ir that we *did* move need base_ir
          * updated so that any further elimination from inside gets its new
          * assignments put before our new assignment.
          */
         foreach_in_list(ae_entry, fixup_entry, ae) {
            if (contains_rvalue(assignment->rhs, *fixup_entry->val))
               fixup_entry->base_ir = assignment;
         }

         if (debug)
            dump_ae(ae);
      }

      /* Replace the expression in our current tree with the variable. */
      return new(rvalue) ir_dereference_variable(entry->var);
   }

   return NULL;
}

/** Add the rvalue to the list of available expressions for CSE. */
void
cse_visitor::add_to_ae(ir_rvalue **rvalue)
{
   if (debug) {
      printf("CSE: Add to AE: ");
      (*rvalue)->print();
      printf("\n");
   }

   ae->push_tail(new(mem_ctx) ae_entry(base_ir, rvalue));

   if (debug)
      dump_ae(ae);
}

void
cse_visitor::handle_rvalue(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return;

   if (debug) {
      printf("CSE: handle_rvalue ");
      (*rvalue)->print();
      printf("\n");
   }

   if (!is_cse_candidate(*rvalue))
      return;

   ir_rvalue *new_rvalue = try_cse(*rvalue);
   if (new_rvalue) {
      *rvalue = new_rvalue;
      progress = true;

      if (debug)
         validate_ir_tree(validate_instructions);
   } else {
      add_to_ae(rvalue);
   }
}

ir_visitor_status
cse_visitor::visit_enter(ir_if *ir)
{
   handle_rvalue(&ir->condition);

   ae->make_empty();
   visit_list_elements(this, &ir->then_instructions);

   ae->make_empty();
   visit_list_elements(this, &ir->else_instructions);

   ae->make_empty();
   return visit_continue_with_parent;
}

ir_visitor_status
cse_visitor::visit_enter(ir_function_signature *ir)
{
   ae->make_empty();
   visit_list_elements(this, &ir->body);

   ae->make_empty();
   return visit_continue_with_parent;
}

ir_visitor_status
cse_visitor::visit_enter(ir_loop *ir)
{
   ae->make_empty();
   visit_list_elements(this, &ir->body_instructions);

   ae->make_empty();
   return visit_continue_with_parent;
}

ir_visitor_status
cse_visitor::visit_enter(ir_call *)
{
   /* Because call is an exec_list of ir_rvalues, handle_rvalue gets passed a
    * pointer to the (ir_rvalue *) on the stack.  Since we save those pointers
    * in the AE list, we can't let handle_rvalue get called.
    */
   return visit_continue_with_parent;
}

/**
 * Does a (uniform-value) constant subexpression elimination pass on the code
 * present in the instruction stream.
 */
bool
do_cse(exec_list *instructions)
{
   cse_visitor v(instructions);

   visit_list_elements(&v, instructions);

   return v.progress;
}

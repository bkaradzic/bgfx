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

#include "glsl_types.h"
#include "loop_analysis.h"
#include "ir_hierarchical_visitor.h"
#include "ir_variable_refcount.h"
#include "util/hash_table.h"

static bool is_loop_terminator(ir_if *ir);

static bool all_expression_operands_are_loop_constant(ir_rvalue *,
						      hash_table *);

static ir_rvalue *get_basic_induction_increment(ir_assignment *, hash_table *);


/**
 * Record the fact that the given loop variable was referenced inside the loop.
 *
 * \arg in_assignee is true if the reference was on the LHS of an assignment.
 *
 * \arg in_conditional_code_or_nested_loop is true if the reference occurred
 * inside an if statement or a nested loop.
 *
 * \arg current_assignment is the ir_assignment node that the loop variable is
 * on the LHS of, if any (ignored if \c in_assignee is false).
 */
void
loop_variable::record_reference(bool in_assignee,
                                bool in_conditional_code_or_nested_loop,
                                ir_assignment *current_assignment)
{
   if (in_assignee) {
      assert(current_assignment != NULL);

      if (in_conditional_code_or_nested_loop ||
          current_assignment->condition != NULL) {
         this->conditional_or_nested_assignment = true;
      }

      if (this->first_assignment == NULL) {
         assert(this->num_assignments == 0);

         this->first_assignment = current_assignment;
      }

      this->num_assignments++;
   } else if (this->first_assignment == current_assignment) {
      /* This catches the case where the variable is used in the RHS of an
       * assignment where it is also in the LHS.
       */
      this->read_before_write = true;
   }
}


loop_state::loop_state()
{
   this->ht = hash_table_ctor(0, hash_table_pointer_hash,
			      hash_table_pointer_compare);
   this->ht_inductors = hash_table_ctor(0, hash_table_pointer_hash,
            hash_table_pointer_compare);
   this->ht_non_inductors = hash_table_ctor(0, hash_table_pointer_hash,
										 hash_table_pointer_compare);
   this->ht_variables = hash_table_ctor(0, hash_table_pointer_hash,
										 hash_table_pointer_compare);
   this->mem_ctx = ralloc_context(NULL);
   this->loop_found = false;
}


loop_state::~loop_state()
{
   hash_table_dtor(this->ht);
   hash_table_dtor(this->ht_inductors);
   hash_table_dtor(this->ht_non_inductors);
   hash_table_dtor(this->ht_variables);
   ralloc_free(this->mem_ctx);
}


loop_variable_state *
loop_state::insert(ir_loop *ir)
{
   loop_variable_state *ls = new(this->mem_ctx) loop_variable_state;

   hash_table_insert(this->ht, ls, ir);
   this->loop_found = true;

   return ls;
}


loop_variable_state *
loop_state::get(const ir_loop *ir)
{
   return (loop_variable_state *) hash_table_find(this->ht, ir);
}

loop_variable_state *
loop_state::get_for_inductor(const ir_variable *ir)
{
   return (loop_variable_state *) hash_table_find(this->ht_inductors, ir);
}

static void *unreferenced_variable = (void *)1;
static void *assigned_variable = (void *)2;

void
loop_state::insert_variable(ir_variable *var)
{
	// data starts as 1. If an assignment is seen, it's replaced with 2.
	// this way we can mark a variable as a non-inductor if it's referenced
	// other than the first assignment
	hash_table_insert(this->ht_variables, unreferenced_variable, var);
}

void
loop_state::reference_variable(ir_variable *var, bool assignment)
{
	void *ref = hash_table_find(this->ht_variables, var);

	// variable declaration was not seen or already discarded, just ignore
	if (ref == NULL)
		return;

	if (ref == unreferenced_variable && assignment)
	{
		hash_table_replace(this->ht_variables, assigned_variable, var);
		return;
	}

	// variable is referenced and not just in an initial assignment,
	// so it cannot be an inductor
	hash_table_remove(this->ht_variables, var);
	hash_table_insert(this->ht_non_inductors, this, var);
}

bool
loop_state::insert_inductor(loop_variable* loopvar, loop_variable_state* state, ir_loop* loop)
{
	ir_variable* var = loopvar->var;

	// Check if this variable is already marked as "sure can't be a private inductor variable"
	if (hash_table_find(this->ht_non_inductors, var))
		return false;

	// Check if this variable is used after the loop anywhere. If it is, it can't be a
	// variable that's private to the loop.
	ir_variable_refcount_visitor refs;
	for (exec_node* node = loop->next;
		 !node->is_tail_sentinel();
		 node = node->next)
	{
		ir_instruction *ir = (ir_instruction *) node;
		ir->accept (&refs);
		if (refs.find_variable_entry(var))
		{
			// add to list of "non inductors", so that next loop does not try
			// to add it as inductor again
			hash_table_insert(this->ht_non_inductors, state, var);
			return false;
		}
	}

	// Check if this variable is used before the loop anywhere. If it is, it can't be a
	// variable that's private to the loop.
	// Skip over the IR that declared the variable or assigned the initial value though.
	for (exec_node* node = loop->prev;
		 !node->is_head_sentinel();
		 node = node->prev)
	{
		ir_instruction *ir = (ir_instruction *) node;
		if (ir == loopvar->initial_value_ir)
			continue;
		if (ir->ir_type == ir_type_variable)
			continue;

		ir->accept (&refs);
		if (refs.find_variable_entry(var))
		{
			// add to list of "non inductors", so that next loop does not try
			// to add it as inductor again
			hash_table_insert(this->ht_non_inductors, state, var);
			return false;
		}
	}
	
	state->private_induction_variable_count++;
	hash_table_insert(this->ht_inductors, state, var);
	return true;
}


loop_variable *
loop_variable_state::get(const ir_variable *ir)
{
   return (loop_variable *) hash_table_find(this->var_hash, ir);
}


loop_variable *
loop_variable_state::insert(ir_variable *var)
{
   void *mem_ctx = ralloc_parent(this);
   loop_variable *lv = rzalloc(mem_ctx, loop_variable);

   lv->var = var;

   hash_table_insert(this->var_hash, lv, lv->var);
   this->variables.push_tail(lv);

   return lv;
}


loop_terminator *
loop_variable_state::insert(ir_if *if_stmt)
{
   void *mem_ctx = ralloc_parent(this);
   loop_terminator *t = new(mem_ctx) loop_terminator();

   t->ir = if_stmt;
   this->terminators.push_tail(t);

   return t;
}


/**
 * If the given variable already is recorded in the state for this loop,
 * return the corresponding loop_variable object that records information
 * about it.
 *
 * Otherwise, create a new loop_variable object to record information about
 * the variable, and set its \c read_before_write field appropriately based on
 * \c in_assignee.
 *
 * \arg in_assignee is true if this variable was encountered on the LHS of an
 * assignment.
 */
loop_variable *
loop_variable_state::get_or_insert(ir_variable *var, bool in_assignee)
{
   loop_variable *lv = this->get(var);

   if (lv == NULL) {
      lv = this->insert(var);
      lv->read_before_write = !in_assignee;
   }

   return lv;
}


namespace {

class loop_analysis : public ir_hierarchical_visitor {
public:
   loop_analysis(loop_state *loops);

   virtual ir_visitor_status visit(ir_loop_jump *);
   virtual ir_visitor_status visit(ir_dereference_variable *);

   virtual ir_visitor_status visit(ir_variable *);

   virtual ir_visitor_status visit_enter(ir_call *);

   virtual ir_visitor_status visit_enter(ir_loop *);
   virtual ir_visitor_status visit_leave(ir_loop *);
   virtual ir_visitor_status visit_enter(ir_assignment *);
   virtual ir_visitor_status visit_leave(ir_assignment *);
   virtual ir_visitor_status visit_enter(ir_if *);
   virtual ir_visitor_status visit_leave(ir_if *);

   void visit_general(ir_instruction *);

   loop_state *loops;

   int if_statement_depth;

   bool first_pass;

   ir_assignment *current_assignment;

   exec_list state;
};

} /* anonymous namespace */

void loop_enter_callback(class ir_instruction *ir, void *data)
{
   ((loop_analysis *)data)->visit_general(ir);
}

loop_analysis::loop_analysis(loop_state *loops)
   : loops(loops), if_statement_depth(0), current_assignment(NULL), first_pass(false)
{
   /* empty */
   data_enter = this;
   callback_enter = &loop_enter_callback;
}


ir_visitor_status
loop_analysis::visit(ir_loop_jump *ir)
{
   (void) ir;

   assert(!this->state.is_empty());

   loop_variable_state *const ls =
      (loop_variable_state *) this->state.get_head();

   ls->num_loop_jumps++;

   return visit_continue;
}


ir_visitor_status
loop_analysis::visit(ir_variable *var)
{
	// if inside a loop, simply continue - we're only interested in variables declared
	// entirely outside of any loops
	if (!this->state.is_empty())
		return visit_continue;

	// In the first pass over the instructions we look at variables declared and
	// examine their references to determine if they can be an inductor or not
	// for the second pass
	if (this->first_pass)
		loops->insert_variable(var);

	return visit_continue;
}

ir_visitor_status
loop_analysis::visit_enter(ir_call *)
{
   /* Mark every loop that we're currently analyzing as containing an ir_call
    * (even those at outer nesting levels).
    */
   foreach_in_list(loop_variable_state, ls, &this->state) {
      ls->contains_calls = true;
   }

   return visit_continue_with_parent;
}


ir_visitor_status
loop_analysis::visit(ir_dereference_variable *ir)
{
   /* If we're not somewhere inside a loop, just check for
    * non-inductors
    */
   if (this->state.is_empty() || this->first_pass)
   {
      if (this->state.is_empty() && this->first_pass)
         loops->reference_variable(ir->variable_referenced(), this->in_assignee);
      return visit_continue;
   }

   bool nested = false;

   foreach_in_list(loop_variable_state, ls, &this->state) {
      ir_variable *var = ir->variable_referenced();
      loop_variable *lv = ls->get_or_insert(var, this->in_assignee);

      lv->record_reference(this->in_assignee,
                           nested || this->if_statement_depth > 0,
                           this->current_assignment);
      nested = true;
   }

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_enter(ir_loop *ir)
{
   loop_variable_state *ls = this->loops->insert(ir);
   this->state.push_head(ls);

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_leave(ir_loop *ir)
{
   loop_variable_state *const ls =
      (loop_variable_state *) this->state.pop_head();

   /* Function calls may contain side effects.  These could alter any of our
    * variables in ways that cannot be known, and may even terminate shader
    * execution (say, calling discard in the fragment shader).  So we can't
    * rely on any of our analysis about assignments to variables.
    *
    * We could perform some conservative analysis (prove there's no statically
    * possible assignment, etc.) but it isn't worth it for now; function
    * inlining will allow us to unroll loops anyway.
    *
    * We also skip doing any work in the first pass, where we are just identifying
    * variables that cannot be inductors.
    */
   if (ls->contains_calls || this->first_pass)
      return visit_continue;

   foreach_in_list(ir_instruction, node, &ir->body_instructions) {
      /* Skip over declarations at the start of a loop.
       */
      if (node->as_variable())
	 continue;

      ir_if *if_stmt = ((ir_instruction *) node)->as_if();

      if ((if_stmt != NULL) && is_loop_terminator(if_stmt))
	 ls->insert(if_stmt);
      else
	 break;
   }


   foreach_in_list_safe(loop_variable, lv, &ls->variables) {
       ir_variable *var = lv->var;
       if (var != NULL) {
           lv->initial_value = find_initial_value(ir, var, &lv->initial_value_ir);
       }
      /* Move variables that are already marked as being loop constant to
       * a separate list.  These trivially don't need to be tested.
       */
      if (lv->is_loop_constant()) {
	 lv->remove();
	 ls->constants.push_tail(lv);
      }
   }

   /* Each variable assigned in the loop that isn't already marked as being loop
    * constant might still be loop constant.  The requirements at this point
    * are:
    *
    *    - Variable is written before it is read.
    *
    *    - Only one assignment to the variable.
    *
    *    - All operands on the RHS of the assignment are also loop constants.
    *
    * The last requirement is the reason for the progress loop.  A variable
    * marked as a loop constant on one pass may allow other variables to be
    * marked as loop constant on following passes.
    */
   bool progress;
   do {
      progress = false;

      foreach_in_list_safe(loop_variable, lv, &ls->variables) {
	 if (lv->conditional_or_nested_assignment || (lv->num_assignments > 1))
	    continue;

	 /* Process the RHS of the assignment.  If all of the variables
	  * accessed there are loop constants, then add this
	  */
	 ir_rvalue *const rhs = lv->first_assignment->rhs;
	 if (all_expression_operands_are_loop_constant(rhs, ls->var_hash)) {
	    lv->rhs_clean = true;

	    if (lv->is_loop_constant()) {
	       progress = true;

	       lv->remove();
	       ls->constants.push_tail(lv);
	    }
	 }
      }
   } while (progress);

   /* The remaining variables that are not loop invariant might be loop
    * induction variables.
    */
   foreach_in_list_safe(loop_variable, lv, &ls->variables) {
      /* If there is more than one assignment to a variable, it cannot be a
       * loop induction variable.  This isn't strictly true, but this is a
       * very simple induction variable detector, and it can't handle more
       * complex cases.
       */
      if (lv->num_assignments > 1)
	 continue;

      /* All of the variables with zero assignments in the loop are loop
       * invariant, and they should have already been filtered out.
       */
      assert(lv->num_assignments == 1);
      assert(lv->first_assignment != NULL);

      /* The assignment to the variable in the loop must be unconditional and
       * not inside a nested loop.
       */
      if (lv->conditional_or_nested_assignment)
	 continue;

      /* Basic loop induction variables have a single assignment in the loop
       * that has the form 'VAR = VAR + i' or 'VAR = VAR - i' where i is a
       * loop invariant.
       */
      ir_rvalue *const inc =
	 get_basic_induction_increment(lv->first_assignment, ls->var_hash);
      if (inc != NULL) {
         lv->increment = inc;

         if (loops->insert_inductor(lv, ls, ir)) {
            lv->remove();
            ls->induction_variables.push_tail(lv);
         }
      }
   }

   /* Search the loop terminating conditions for those of the form 'i < c'
    * where i is a loop induction variable, c is a constant, and < is any
    * relative operator.  From each of these we can infer an iteration count.
    * Also figure out which terminator (if any) produces the smallest
    * iteration count--this is the limiting terminator.
    */
   foreach_in_list(loop_terminator, t, &ls->terminators) {
      ir_if *if_stmt = t->ir;

      /* If-statements can be either 'if (expr)' or 'if (deref)'.  We only care
       * about the former here.
       */
      ir_expression *cond = if_stmt->condition->as_expression();
      if (cond == NULL)
	 continue;

      switch (cond->operation) {
      case ir_binop_less:
      case ir_binop_greater:
      case ir_binop_lequal:
      case ir_binop_gequal: {
	 /* The expressions that we care about will either be of the form
	  * 'counter < limit' or 'limit < counter'.  Figure out which is
	  * which.
	  */
	 ir_rvalue *counter = cond->operands[0]->as_dereference_variable();
	 ir_constant *limit = cond->operands[1]->as_constant();
	 enum ir_expression_operation cmp = cond->operation;

	 if (limit == NULL) {
	    counter = cond->operands[1]->as_dereference_variable();
	    limit = cond->operands[0]->as_constant();

	    switch (cmp) {
	    case ir_binop_less:    cmp = ir_binop_greater; break;
	    case ir_binop_greater: cmp = ir_binop_less;    break;
	    case ir_binop_lequal:  cmp = ir_binop_gequal;  break;
	    case ir_binop_gequal:  cmp = ir_binop_lequal;  break;
	    default: assert(!"Should not get here.");
	    }
	 }

	 if ((counter == NULL) || (limit == NULL))
	    break;

	 ir_variable *var = counter->variable_referenced();

         loop_variable *lv = ls->get(var);
         if (lv != NULL && lv->is_induction_var()) {
            t->iterations = calculate_iterations(lv->initial_value, limit, lv->increment,
                                                 cmp);

            if (t->iterations >= 0 &&
                (ls->limiting_terminator == NULL ||
                 t->iterations < ls->limiting_terminator->iterations)) {
               ls->limiting_terminator = t;
            }
         }
         break;
      }

      default:
         break;
      }
   }

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_enter(ir_if *ir)
{
   (void) ir;

   if (!this->state.is_empty())
      this->if_statement_depth++;

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_leave(ir_if *ir)
{
   (void) ir;

   if (!this->state.is_empty())
      this->if_statement_depth--;

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_enter(ir_assignment *ir)
{
   /* If we're not somewhere inside a loop, there's nothing to do.
    */
   if (this->state.is_empty())
      return visit_continue;

   this->current_assignment = ir;

   return visit_continue;
}

ir_visitor_status
loop_analysis::visit_leave(ir_assignment *ir)
{
   if (this->state.is_empty())
      return visit_continue;

   assert(this->current_assignment == ir);
   this->current_assignment = NULL;

   return visit_continue;
}

void
loop_analysis::visit_general(ir_instruction *ir)
{
   /* If we're inside a loop, we can't start marking things as non-inductors
    * Likewise in the second pass we've done all this work, so return early
    */
   if (!this->state.is_empty() || !this->first_pass)
      return;

   ir_variable_refcount_visitor refs;
   ir->accept (&refs);

   struct hash_entry *referenced_var;
   hash_table_foreach (refs.ht, referenced_var) {
      ir_variable *var = (ir_variable *)referenced_var->key;
      loops->reference_variable(var, false);
   }
}

class examine_rhs : public ir_hierarchical_visitor {
public:
   examine_rhs(hash_table *loop_variables)
   {
      this->only_uses_loop_constants = true;
      this->loop_variables = loop_variables;
   }

   virtual ir_visitor_status visit(ir_dereference_variable *ir)
   {
      loop_variable *lv =
	 (loop_variable *) hash_table_find(this->loop_variables, ir->var);

      assert(lv != NULL);

      if (lv->is_loop_constant()) {
	 return visit_continue;
      } else {
	 this->only_uses_loop_constants = false;
	 return visit_stop;
      }
   }

   hash_table *loop_variables;
   bool only_uses_loop_constants;
};


bool
all_expression_operands_are_loop_constant(ir_rvalue *ir, hash_table *variables)
{
   examine_rhs v(variables);

   ir->accept(&v);

   return v.only_uses_loop_constants;
}


ir_rvalue *
get_basic_induction_increment(ir_assignment *ir, hash_table *var_hash)
{
   /* The RHS must be a binary expression.
    */
   ir_expression *const rhs = ir->rhs->as_expression();
   if ((rhs == NULL)
       || ((rhs->operation != ir_binop_add)
	   && (rhs->operation != ir_binop_sub)))
      return NULL;

   /* One of the of operands of the expression must be the variable assigned.
    * If the operation is subtraction, the variable in question must be the
    * "left" operand.
    */
   ir_variable *const var = ir->lhs->variable_referenced();

   ir_variable *const op0 = rhs->operands[0]->variable_referenced();
   ir_variable *const op1 = rhs->operands[1]->variable_referenced();

   if (((op0 != var) && (op1 != var))
       || ((op1 == var) && (rhs->operation == ir_binop_sub)))
      return NULL;

   ir_rvalue *inc = (op0 == var) ? rhs->operands[1] : rhs->operands[0];

   if (inc->as_constant() == NULL) {
      ir_variable *const inc_var = inc->variable_referenced();
      if (inc_var != NULL) {
	 loop_variable *lv =
	    (loop_variable *) hash_table_find(var_hash, inc_var);

         if (lv == NULL || !lv->is_loop_constant()) {
            assert(lv != NULL);
            inc = NULL;
         }
      } else
	 inc = NULL;
   }

   if ((inc != NULL) && (rhs->operation == ir_binop_sub)) {
      void *mem_ctx = ralloc_parent(ir);

      inc = new(mem_ctx) ir_expression(ir_unop_neg,
				       inc->type,
				       inc->clone(mem_ctx, NULL),
				       NULL);
   }

   return inc;
}


/**
 * Detect whether an if-statement is a loop terminating condition
 *
 * Detects if-statements of the form
 *
 *  (if (expression bool ...) (break))
 */
bool
is_loop_terminator(ir_if *ir)
{
   if (!ir->else_instructions.is_empty())
      return false;

   ir_instruction *const inst =
      (ir_instruction *) ir->then_instructions.get_head();
   if (inst == NULL)
      return false;

   if (inst->ir_type != ir_type_loop_jump)
      return false;

   ir_loop_jump *const jump = (ir_loop_jump *) inst;
   if (jump->mode != ir_loop_jump::jump_break)
      return false;

   return true;
}

loop_state *
analyze_loop_variables(exec_list *instructions)
{
   loop_state *loops = new loop_state;
   loop_analysis v(loops);

   /* Do two passes over the instructions. The first pass builds a view
    * of the variables declared and whether or not they're used outside
    * of loops (if so, they cannot be inductors).
    *
    * In the second pass we apply this information to do the loop analysis
    * itself.
    */
   v.first_pass = true;
   v.run(instructions);
   v.first_pass = false;
   v.run(instructions);

   return v.loops;
}

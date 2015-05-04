/*
 * Based on work Copyright © 2010 Intel Corporation, vector splitting
 * implemented by Copyright © 2014 Unity Technologies
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
 * \file opt_vector_splitting.cpp
 *
 * If a vector is always dereferenced only by its xyzw components separately,
 * and never accessed as a whole (or with swizzle mask with >1 bits set), then
 * split it apart into its elements, making it more amenable to other
 * optimization passes.
 *
 * This skips uniforms/varyings, which would need careful
 * handling due to their ir->location fields tying them to the GL API
 * and other shader stages.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_rvalue_visitor.h"
#include "glsl_types.h"
#include "ir_optimization.h"
#include "loop_analysis.h"

static bool debug = false;

namespace {
	namespace opt_vector_splitting {

		class variable_entry : public exec_node
		{
		public:
			variable_entry(ir_variable *var)
			{
				this->var = var;
				this->split = true;
				this->use_mask = 0;
				this->declaration = false;
				this->components = NULL;
				this->mem_ctx = NULL;
			}

			ir_variable *var; /* The key: the variable's pointer. */

			/** Whether this array should be split or not. */
			bool split;

			/** bitmask for the components in the vector that actually get written to.
			 * If multiple slots are written simultaneously, split gets set to false.*/
			int use_mask;

			/* If the variable had a decl we can work with in the instruction
			 * stream.  We can't do splitting on function arguments, which
			 * don't get this variable set.
			 */
			bool declaration;

			ir_variable **components;

			/** ralloc_parent(this->var) -- the shader's talloc context. */
			void *mem_ctx;
		};

	} /* namespace */


using namespace opt_vector_splitting;

/**
 * This class does a walk over the tree, coming up with the set of
 * variables that could be split by looking to see if they are arrays
 * that are only ever constant-index dereferenced.
 */
class ir_vector_reference_visitor : public ir_hierarchical_visitor {
public:
   ir_vector_reference_visitor(void)
   {
      this->mem_ctx = ralloc_context(NULL);
      this->variable_list.make_empty();
   }

   ~ir_vector_reference_visitor(void)
   {
      ralloc_free(mem_ctx);
   }

   bool get_split_list(exec_list *instructions, bool linked, glsl_vector_splitting_mode mode);

   virtual ir_visitor_status visit(ir_variable *);
   virtual ir_visitor_status visit(ir_dereference_variable *);
   virtual ir_visitor_status visit_enter(ir_swizzle *);
   virtual ir_visitor_status visit_enter(ir_assignment *);
   virtual ir_visitor_status visit_enter(ir_function_signature *);

   variable_entry *get_variable_entry(ir_variable *var);

   /* List of variable_entry */
   exec_list variable_list;

   /* Current split mode */
   glsl_vector_splitting_mode mode;

   loop_state *loopstate;

   void *mem_ctx;
};

} /* namespace */

variable_entry *
ir_vector_reference_visitor::get_variable_entry(ir_variable *var)
{
   assert(var);

   if (var->data.mode != ir_var_auto &&
       var->data.mode != ir_var_temporary)
      return NULL;

   if (!var->type->is_vector())
      return NULL;

   // If mode is loop_inductors, allow only loop inductors to be stored.
   if (mode == OPT_SPLIT_ONLY_LOOP_INDUCTORS && loopstate)
   {
	   loop_variable_state* inductor_state = loopstate->get_for_inductor(var);
	   if (!inductor_state)
	   {
		   return NULL;
	   }
   }

   foreach_in_list(variable_entry, entry, &this->variable_list) {
      if (entry->var == var)
	 return entry;
   }


   variable_entry *entry = new(mem_ctx) variable_entry(var);
   this->variable_list.push_tail(entry);
   return entry;
}


ir_visitor_status
ir_vector_reference_visitor::visit(ir_variable *ir)
{
   variable_entry *entry = this->get_variable_entry(ir);

   if (entry)
      entry->declaration = true;

   return visit_continue;
}

ir_visitor_status
ir_vector_reference_visitor::visit(ir_dereference_variable *ir)
{
   variable_entry *entry = this->get_variable_entry(ir->var);

   /* If we made it to here without seeing an ir_swizzle,
    * then the dereference of this vector didn't have a swizzle in it
    * (see the visit_continue_with_parent below), so we can't split
    * the variable.
    */
   if (entry)
      entry->split = false;

   return visit_continue;
}

ir_visitor_status
ir_vector_reference_visitor::visit_enter(ir_swizzle *ir)
{
	ir_variable *var = ir->variable_referenced();
   if (!var)
      return visit_continue;

   variable_entry *entry = this->get_variable_entry(var);

   if (entry)
   {
	   if (ir->mask.num_components > 1)
	   {
		   entry->split = false;
	   }
	   else
	   {
		   // Update the usemask
		   entry->use_mask |= (1 << ir->mask.x);
	   }
   }

	// Skip the rest of the swizzle IR tree, we're done here.
   return visit_continue_with_parent;
}

ir_visitor_status
ir_vector_reference_visitor::visit_enter(ir_assignment *ir)
{
	ir_dereference_variable *dest = ir->lhs->as_dereference_variable();
	if (dest)
	{
		variable_entry *entry = this->get_variable_entry(dest->var);
		if (entry)
		{
			// Count how many bits the write mask has
			unsigned maskbitval = ir->write_mask; // count the number of bits set
			int maskbitcount; // accumulates the total bits set
			for ( maskbitcount = 0; maskbitval; maskbitcount++)
			{
				maskbitval &= maskbitval - 1; // clear the least significant bit set
			}
			if (maskbitcount > 1)
			{
				// Writing to more than one slot, cannot split.
				entry->split = false;
			}

			// Update write mask
			entry->use_mask |= ir->write_mask;
		}
	}

	// Visit only the rhs, there may be swizzles and variable dereferences there as well
	ir->rhs->accept(this);
	return visit_continue_with_parent;

}

ir_visitor_status
ir_vector_reference_visitor::visit_enter(ir_function_signature *ir)
{
   /* We don't have logic for array-splitting function arguments,
    * so just look at the body instructions and not the parameter
    * declarations.
    */
   visit_list_elements(this, &ir->body);
   return visit_continue_with_parent;
}

bool
ir_vector_reference_visitor::get_split_list(exec_list *instructions,
					   bool linked,
					   glsl_vector_splitting_mode _mode)
{
	mode = _mode;

	if (linked)
	{
		loop_state* ls = analyze_loop_variables(instructions);
		if (ls->loop_found)
			set_loop_controls(instructions, ls);

		loopstate = ls;
	}
	else
	{
		loopstate = NULL;
	}

	visit_list_elements(this, instructions);

   /* If the shaders aren't linked yet, we can't mess with global
    * declarations, which need to be matched by name across shaders.
    */
   if (!linked) {
      foreach_in_list(ir_variable, var, instructions) {
	 if (var) {
	    variable_entry *entry = get_variable_entry(var);
	    if (entry)
	       entry->remove();
	 }
      }
   }

   /* Trim out variables we found that we can't split. */
   foreach_in_list_safe(variable_entry, entry, &variable_list) {

      if (debug) {
	 printf("array %s@%p: decl %d, split %d\n",
		entry->var->name, (void *) entry->var, entry->declaration,
		entry->split);
      }

      if (!(entry->declaration && entry->split)) {
	 entry->remove();
      }
	  else if (mode == OPT_SPLIT_ONLY_UNUSED)
	  {
		  /* Build mask of fully used vector (vec2 -> 0x3, vec3 -> 0x7, vec4 -> 0xe) */
		  unsigned int fullmask = (1 << entry->var->type->vector_elements) - 1;
		  if (entry->use_mask == fullmask)
		  {
			  entry->remove();
		  }
	  }
   }

   return !variable_list.is_empty();
}

/**
 * This class rewrites the dereferences of arrays that have been split
 * to use the newly created ir_variables for each component.
 */
class ir_vector_splitting_visitor : public ir_rvalue_visitor {
public:
   ir_vector_splitting_visitor(exec_list *vars)
   {
      this->variable_list = vars;
   }

   virtual ~ir_vector_splitting_visitor()
   {
   }

   virtual ir_visitor_status visit_leave(ir_assignment *);

   void split_rvalue(ir_rvalue **rval);
   void handle_rvalue(ir_rvalue **rvalue);
   variable_entry *get_splitting_entry(ir_variable *var);

   exec_list *variable_list;
};

variable_entry *
ir_vector_splitting_visitor::get_splitting_entry(ir_variable *var)
{
   assert(var);

   foreach_in_list(variable_entry, entry, this->variable_list) {
      if (entry->var == var) {
	 return entry;
      }
   }

   return NULL;
}

void
ir_vector_splitting_visitor::split_rvalue(ir_rvalue **rval)
{
	ir_swizzle *swizzle = (*rval)->as_swizzle();

	if (!swizzle)
		return;

	ir_variable *var = swizzle->variable_referenced();
	if (!var)
		return;

   variable_entry *entry = get_splitting_entry(var);
   if (!entry)
      return;

   assert(swizzle->mask.num_components == 1);

   *rval = new(entry->mem_ctx)
	 ir_dereference_variable(entry->components[swizzle->mask.x]);
}

void
ir_vector_splitting_visitor::handle_rvalue(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return;

   ir_rvalue *v = *rvalue;
   split_rvalue(&v);
   *rvalue = v;
}

ir_visitor_status
ir_vector_splitting_visitor::visit_leave(ir_assignment *ir)
{
   /* The normal rvalue visitor skips the LHS of assignments, but we
    * need to process those just the same.
    */
   ir_rvalue *lhs = ir->lhs;

   ir_dereference_variable *dest = ir->lhs->as_dereference_variable();
   if (dest)
   {
	   variable_entry *entry = get_splitting_entry(dest->var);
	   if (entry)
	   {
		   // Find the only set bit in writemask
		   int component = 0;
		   while (((ir->write_mask & (1 << component)) == 0) && (component < 4))
		   {
			   component++;
		   }
		   assert(ir->write_mask == (1 << component));

		   ir_dereference_variable *newderef = new(entry->mem_ctx)
			   ir_dereference_variable(entry->components[component]);

		   ir->set_lhs(newderef);
	   }
   }
   else
   {
	   ir->lhs = lhs->as_dereference();
	   ir->lhs->accept(this);
   }

   handle_rvalue(&ir->rhs);
   ir->rhs->accept(this);

   if (ir->condition) {
      handle_rvalue(&ir->condition);
      ir->condition->accept(this);
   }

   return visit_continue;
}

bool
optimize_split_vectors(exec_list *instructions, bool linked, glsl_vector_splitting_mode mode)
{
   ir_vector_reference_visitor refs;
   if (!refs.get_split_list(instructions, linked, mode))
      return false;

   void *mem_ctx = ralloc_context(NULL);

   /* Replace the decls of the vectors to be split with their split
    * components.
    */
   foreach_in_list(variable_entry, entry, &refs.variable_list) {
      const struct glsl_type *type = entry->var->type;
      const struct glsl_type *subtype;
      glsl_precision subprec = (glsl_precision)entry->var->data.precision;

	  subtype = type->get_base_type();

      entry->mem_ctx = ralloc_parent(entry->var);

      entry->components = ralloc_array(mem_ctx,
				       ir_variable *,
				       type->vector_elements);

      for (unsigned int i = 0; i < type->vector_elements; i++) {
	 const char *name = ralloc_asprintf(mem_ctx, "%s_%c",
					    entry->var->name, "xyzw"[i]);

	 entry->components[i] =
	    new(entry->mem_ctx) ir_variable(subtype, name, ir_var_temporary, subprec);
	 entry->var->insert_before(entry->components[i]);
      }

      entry->var->remove();
   }

   ir_vector_splitting_visitor split(&refs.variable_list);
   visit_list_elements(&split, instructions);

   if (debug)
      _mesa_print_ir(stdout, instructions, NULL);

   ralloc_free(mem_ctx);

   return true;

}

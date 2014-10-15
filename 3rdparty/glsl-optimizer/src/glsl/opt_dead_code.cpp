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
 * \file opt_dead_code.cpp
 *
 * Eliminates dead assignments and variable declarations from the code.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_variable_refcount.h"
#include "glsl_types.h"
#include "util/hash_table.h"

static bool debug = false;

/**
 * Do a dead code pass over instructions and everything that instructions
 * references.
 *
 * Note that this will remove assignments to globals, so it is not suitable
 * for usage on an unlinked instruction stream.
 */
bool
do_dead_code(exec_list *instructions, bool uniform_locations_assigned)
{
   ir_variable_refcount_visitor v;
   bool progress = false;

   v.run(instructions);

   struct hash_entry *e;
   hash_table_foreach(v.ht, e) {
      ir_variable_refcount_entry *entry = (ir_variable_refcount_entry *)e->data;

      /* Since each assignment is a reference, the refereneced count must be
       * greater than or equal to the assignment count.  If they are equal,
       * then all of the references are assignments, and the variable is
       * dead.
       *
       * Note that if the variable is neither assigned nor referenced, both
       * counts will be zero and will be caught by the equality test.
       */
      assert(entry->referenced_count >= entry->assigned_count);

      if (debug) {
	 printf("%s@%p: %d refs, %d assigns, %sdeclared in our scope\n",
		entry->var->name, (void *) entry->var,
		entry->referenced_count, entry->assigned_count,
		entry->declaration ? "" : "not ");
      }

      if ((entry->referenced_count_noself > entry->assigned_count)
	  || !entry->declaration)
	 continue;

      if (entry->assign) {
	 /* Remove a single dead assignment to the variable we found.
	  * Don't do so if it's a shader or function output, though.
	  */
	 if (entry->var->data.mode != ir_var_function_out &&
	     entry->var->data.mode != ir_var_function_inout &&
             entry->var->data.mode != ir_var_shader_out) {
	    entry->assign->remove();
	    progress = true;

	    if (debug) {
	       printf("Removed assignment to %s@%p\n",
		      entry->var->name, (void *) entry->var);
	    }
	 }
      } else {
	 /* If there are no assignments or references to the variable left,
	  * then we can remove its declaration.
	  */

	 /* uniform initializers are precious, and could get used by another
	  * stage.  Also, once uniform locations have been assigned, the
	  * declaration cannot be deleted.
	  */
         if (entry->var->data.mode == ir_var_uniform) {
            if (uniform_locations_assigned || entry->var->constant_value)
               continue;

            /* Section 2.11.6 (Uniform Variables) of the OpenGL ES 3.0.3 spec
             * says:
             *
             *     "All members of a named uniform block declared with a
             *     shared or std140 layout qualifier are considered active,
             *     even if they are not referenced in any shader in the
             *     program. The uniform block itself is also considered
             *     active, even if no member of the block is referenced."
             *
             * If the variable is in a uniform block with one of those
             * layouts, do not eliminate it.
             */
            if (entry->var->is_in_uniform_block()) {
               const glsl_type *const block_type =
                  entry->var->is_interface_instance()
                  ? entry->var->type : entry->var->get_interface_type();

               if (block_type->interface_packing != GLSL_INTERFACE_PACKING_PACKED)
                  continue;
            }
         }

	 entry->var->remove();
	 progress = true;

	 if (debug) {
	    printf("Removed declaration of %s@%p\n",
		   entry->var->name, (void *) entry->var);
	 }
      }
   }

   return progress;
}

/**
 * Does a dead code pass on the functions present in the instruction stream.
 *
 * This is suitable for use while the program is not linked, as it will
 * ignore variable declarations (and the assignments to them) for variables
 * with global scope.
 */
bool
do_dead_code_unlinked(exec_list *instructions)
{
   bool progress = false;

   foreach_in_list(ir_instruction, ir, instructions) {
      ir_function *f = ir->as_function();
      if (f) {
	 foreach_in_list(ir_function_signature, sig, &f->signatures) {
	    /* The setting of the uniform_locations_assigned flag here is
	     * irrelevent.  If there is a uniform declaration encountered
	     * inside the body of the function, something has already gone
	     * terribly, terribly wrong.
	     */
	    if (do_dead_code(&sig->body, false))
	       progress = true;
	 }
      }
   }

   return progress;
}

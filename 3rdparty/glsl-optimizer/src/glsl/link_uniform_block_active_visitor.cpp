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

#include "link_uniform_block_active_visitor.h"
#include "program.h"

link_uniform_block_active *
process_block(void *mem_ctx, struct hash_table *ht, ir_variable *var)
{
   const uint32_t h = _mesa_hash_string(var->get_interface_type()->name);
   const hash_entry *const existing_block =
      _mesa_hash_table_search(ht, h, var->get_interface_type()->name);

   const glsl_type *const block_type = var->is_interface_instance()
      ? var->type : var->get_interface_type();


   /* If a block with this block-name has not previously been seen, add it.
    * If a block with this block-name has been seen, it must be identical to
    * the block currently being examined.
    */
   if (existing_block == NULL) {
      link_uniform_block_active *const b =
	 rzalloc(mem_ctx, struct link_uniform_block_active);

      b->type = block_type;
      b->has_instance_name = var->is_interface_instance();

      if (var->data.explicit_binding) {
         b->has_binding = true;
         b->binding = var->data.binding;
      } else {
         b->has_binding = false;
         b->binding = 0;
      }

      _mesa_hash_table_insert(ht, h, var->get_interface_type()->name,
			      (void *) b);
      return b;
   } else {
      link_uniform_block_active *const b =
	 (link_uniform_block_active *) existing_block->data;

      if (b->type != block_type
	  || b->has_instance_name != var->is_interface_instance())
	 return NULL;
      else
	 return b;
   }

   assert(!"Should not get here.");
   return NULL;
}

ir_visitor_status
link_uniform_block_active_visitor::visit(ir_variable *var)
{
   if (!var->is_in_uniform_block())
      return visit_continue;

   const glsl_type *const block_type = var->is_interface_instance()
      ? var->type : var->get_interface_type();

   /* Section 2.11.6 (Uniform Variables) of the OpenGL ES 3.0.3 spec says:
    *
    *     "All members of a named uniform block declared with a shared or
    *     std140 layout qualifier are considered active, even if they are not
    *     referenced in any shader in the program. The uniform block itself is
    *     also considered active, even if no member of the block is
    *     referenced."
    */
   if (block_type->interface_packing == GLSL_INTERFACE_PACKING_PACKED)
      return visit_continue;

   /* Process the block.  Bail if there was an error.
    */
   link_uniform_block_active *const b =
      process_block(this->mem_ctx, this->ht, var);
   if (b == NULL) {
      linker_error(this->prog,
                   "uniform block `%s' has mismatching definitions",
                   var->get_interface_type()->name);
      this->success = false;
      return visit_stop;
   }

   assert(b->num_array_elements == 0);
   assert(b->array_elements == NULL);
   assert(b->type != NULL);

   return visit_continue;
}

ir_visitor_status
link_uniform_block_active_visitor::visit_enter(ir_dereference_array *ir)
{
   ir_dereference_variable *const d = ir->array->as_dereference_variable();
   ir_variable *const var = (d == NULL) ? NULL : d->var;

   /* If the r-value being dereferenced is not a variable (e.g., a field of a
    * structure) or is not a uniform block instance, continue.
    *
    * WARNING: It is not enough for the variable to be part of uniform block.
    * It must represent the entire block.  Arrays (or matrices) inside blocks
    * that lack an instance name are handled by the ir_dereference_variable
    * function.
    */
   if (var == NULL
       || !var->is_in_uniform_block()
       || !var->is_interface_instance())
      return visit_continue;

   /* Process the block.  Bail if there was an error.
    */
   link_uniform_block_active *const b =
      process_block(this->mem_ctx, this->ht, var);
   if (b == NULL) {
      linker_error(prog,
		   "uniform block `%s' has mismatching definitions",
		   var->get_interface_type()->name);
      this->success = false;
      return visit_stop;
   }

   /* Block arrays must be declared with an instance name.
    */
   assert(b->has_instance_name);
   assert((b->num_array_elements == 0) == (b->array_elements == NULL));
   assert(b->type != NULL);

   ir_constant *c = ir->array_index->as_constant();

   if (c) {
      /* Index is a constant, so mark just that element used, if not already */
      const unsigned idx = c->get_uint_component(0);

      unsigned i;
      for (i = 0; i < b->num_array_elements; i++) {
         if (b->array_elements[i] == idx)
            break;
      }

      assert(i <= b->num_array_elements);

      if (i == b->num_array_elements) {
         b->array_elements = reralloc(this->mem_ctx,
                                      b->array_elements,
                                      unsigned,
                                      b->num_array_elements + 1);

         b->array_elements[b->num_array_elements] = idx;

         b->num_array_elements++;
      }
   } else {
      /* The array index is not a constant, so mark the entire array used. */
      assert(b->type->is_array());
      if (b->num_array_elements < b->type->length) {
         b->num_array_elements = b->type->length;
         b->array_elements = reralloc(this->mem_ctx,
                                      b->array_elements,
                                      unsigned,
                                      b->num_array_elements);

         for (unsigned i = 0; i < b->num_array_elements; i++) {
            b->array_elements[i] = i;
         }
      }
   }

   return visit_continue_with_parent;
}

ir_visitor_status
link_uniform_block_active_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->var;

   if (!var->is_in_uniform_block())
      return visit_continue;

   assert(!var->is_interface_instance() || !var->type->is_array());

   /* Process the block.  Bail if there was an error.
    */
   link_uniform_block_active *const b =
      process_block(this->mem_ctx, this->ht, var);
   if (b == NULL) {
      linker_error(this->prog,
		   "uniform block `%s' has mismatching definitions",
		   var->get_interface_type()->name);
      this->success = false;
      return visit_stop;
   }

   assert(b->num_array_elements == 0);
   assert(b->array_elements == NULL);
   assert(b->type != NULL);

   return visit_continue;
}

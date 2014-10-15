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

#include <string.h>
#include "main/compiler.h"
#include "ir.h"
#include "glsl_types.h"
#include "program/hash_table.h"

ir_rvalue *
ir_rvalue::clone(void *mem_ctx, struct hash_table *) const
{
   /* The only possible instantiation is the generic error value. */
   return error_value(mem_ctx);
}

/**
 * Duplicate an IR variable
 */
ir_variable *
ir_variable::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_variable *var = new(mem_ctx) ir_variable(this->type, this->name,
					       (ir_variable_mode) this->data.mode, (glsl_precision)this->data.precision);

   var->data.max_array_access = this->data.max_array_access;
   if (this->is_interface_instance()) {
      var->u.max_ifc_array_access =
         rzalloc_array(var, unsigned, this->interface_type->length);
      memcpy(var->u.max_ifc_array_access, this->u.max_ifc_array_access,
             this->interface_type->length * sizeof(unsigned));
   }

   memcpy(&var->data, &this->data, sizeof(var->data));

   if (this->get_state_slots()) {
      ir_state_slot *s = var->allocate_state_slots(this->get_num_state_slots());
      memcpy(s, this->get_state_slots(),
             sizeof(s[0]) * var->get_num_state_slots());
   }

   if (this->constant_value)
      var->constant_value = this->constant_value->clone(mem_ctx, ht);

   if (this->constant_initializer)
      var->constant_initializer =
	 this->constant_initializer->clone(mem_ctx, ht);

   var->interface_type = this->interface_type;

   if (ht) {
      hash_table_insert(ht, var, (void *)const_cast<ir_variable *>(this));
   }

   return var;
}

ir_swizzle *
ir_swizzle::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_swizzle* rv = new(mem_ctx) ir_swizzle(this->val->clone(mem_ctx, ht), this->mask);
   rv->set_precision (this->get_precision());
   return rv;
}

ir_return *
ir_return::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_rvalue *new_value = NULL;

   if (this->value)
      new_value = this->value->clone(mem_ctx, ht);

   return new(mem_ctx) ir_return(new_value);
}

ir_discard *
ir_discard::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_rvalue *new_condition = NULL;

   if (this->condition != NULL)
      new_condition = this->condition->clone(mem_ctx, ht);

   return new(mem_ctx) ir_discard(new_condition);
}

ir_loop_jump *
ir_loop_jump::clone(void *mem_ctx, struct hash_table *ht) const
{
   (void)ht;

   return new(mem_ctx) ir_loop_jump(this->mode);
}

ir_if *
ir_if::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_if *new_if = new(mem_ctx) ir_if(this->condition->clone(mem_ctx, ht));

   foreach_in_list(ir_instruction, ir, &this->then_instructions) {
      new_if->then_instructions.push_tail(ir->clone(mem_ctx, ht));
   }

   foreach_in_list(ir_instruction, ir, &this->else_instructions) {
      new_if->else_instructions.push_tail(ir->clone(mem_ctx, ht));
   }

   return new_if;
}

ir_loop *
ir_loop::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_loop *new_loop = new(mem_ctx) ir_loop();

   foreach_in_list(ir_instruction, ir, &this->body_instructions) {
      new_loop->body_instructions.push_tail(ir->clone(mem_ctx, ht));
   }

   return new_loop;
}

ir_call *
ir_call::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_dereference_variable *new_return_ref = NULL;
   if (this->return_deref != NULL)
      new_return_ref = this->return_deref->clone(mem_ctx, ht);

   exec_list new_parameters;

   foreach_in_list(ir_instruction, ir, &this->actual_parameters) {
      new_parameters.push_tail(ir->clone(mem_ctx, ht));
   }

   ir_call* rv = new(mem_ctx) ir_call(this->callee, new_return_ref, &new_parameters);
   return rv;
}

ir_expression *
ir_expression::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_rvalue *op[Elements(this->operands)] = { NULL, };
   unsigned int i;

   for (i = 0; i < get_num_operands(); i++) {
      op[i] = this->operands[i]->clone(mem_ctx, ht);
   }

   ir_expression* rv = new(mem_ctx) ir_expression(this->operation, this->type,
				     op[0], op[1], op[2], op[3]);
   rv->set_precision (this->get_precision());
   return rv;
}

ir_dereference_variable *
ir_dereference_variable::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_variable *new_var;

   if (ht) {
      new_var = (ir_variable *)hash_table_find(ht, this->var);
      if (!new_var)
	 new_var = this->var;
   } else {
      new_var = this->var;
   }

   ir_dereference_variable* rv = new(mem_ctx) ir_dereference_variable(new_var);
   rv->set_precision (this->get_precision());
   return rv;
}

ir_dereference_array *
ir_dereference_array::clone(void *mem_ctx, struct hash_table *ht) const
{
   return new(mem_ctx) ir_dereference_array(this->array->clone(mem_ctx, ht),
					    this->array_index->clone(mem_ctx,
								     ht));
}

ir_dereference_record *
ir_dereference_record::clone(void *mem_ctx, struct hash_table *ht) const
{
   return new(mem_ctx) ir_dereference_record(this->record->clone(mem_ctx, ht),
					     this->field);
}

ir_texture *
ir_texture::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_texture *new_tex = new(mem_ctx) ir_texture(this->op);
   new_tex->type = this->type;

   new_tex->sampler = this->sampler->clone(mem_ctx, ht);
   if (this->coordinate)
      new_tex->coordinate = this->coordinate->clone(mem_ctx, ht);

   if (this->offset != NULL)
      new_tex->offset = this->offset->clone(mem_ctx, ht);

   switch (this->op) {
   case ir_tex:
   case ir_lod:
   case ir_query_levels:
      break;
   case ir_txb:
      new_tex->lod_info.bias = this->lod_info.bias->clone(mem_ctx, ht);
      break;
   case ir_txl:
   case ir_txf:
   case ir_txs:
      new_tex->lod_info.lod = this->lod_info.lod->clone(mem_ctx, ht);
      break;
   case ir_txf_ms:
      new_tex->lod_info.sample_index = this->lod_info.sample_index->clone(mem_ctx, ht);
      break;
   case ir_txd:
      new_tex->lod_info.grad.dPdx = this->lod_info.grad.dPdx->clone(mem_ctx, ht);
      new_tex->lod_info.grad.dPdy = this->lod_info.grad.dPdy->clone(mem_ctx, ht);
      break;
   case ir_tg4:
      new_tex->lod_info.component = this->lod_info.component->clone(mem_ctx, ht);
      break;
   }

   return new_tex;
}

ir_assignment *
ir_assignment::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_rvalue *new_condition = NULL;

   if (this->condition)
      new_condition = this->condition->clone(mem_ctx, ht);

   ir_assignment *cloned =
      new(mem_ctx) ir_assignment(this->lhs->clone(mem_ctx, ht),
                                 this->rhs->clone(mem_ctx, ht),
                                 new_condition);
   cloned->write_mask = this->write_mask;
   return cloned;
}

ir_function *
ir_function::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_function *copy = new(mem_ctx) ir_function(this->name);

   foreach_in_list(const ir_function_signature, sig, &this->signatures) {
      ir_function_signature *sig_copy = sig->clone(mem_ctx, ht);
      copy->add_signature(sig_copy);

      if (ht != NULL)
	 hash_table_insert(ht, sig_copy,
			   (void *)const_cast<ir_function_signature *>(sig));
   }

   return copy;
}

ir_function_signature *
ir_function_signature::clone(void *mem_ctx, struct hash_table *ht) const
{
   ir_function_signature *copy = this->clone_prototype(mem_ctx, ht);

   copy->is_defined = this->is_defined;

   /* Clone the instruction list.
    */
   foreach_in_list(const ir_instruction, inst, &this->body) {
      ir_instruction *const inst_copy = inst->clone(mem_ctx, ht);
      copy->body.push_tail(inst_copy);
   }

   return copy;
}

ir_function_signature *
ir_function_signature::clone_prototype(void *mem_ctx, struct hash_table *ht) const
{
   ir_function_signature *copy =
      new(mem_ctx) ir_function_signature(this->return_type, this->precision);

   copy->is_defined = false;
   copy->builtin_avail = this->builtin_avail;
   copy->origin = this;

   /* Clone the parameter list, but NOT the body.
    */
   foreach_in_list(const ir_variable, param, &this->parameters) {
      assert(const_cast<ir_variable *>(param)->as_variable() != NULL);

      ir_variable *const param_copy = param->clone(mem_ctx, ht);
      copy->parameters.push_tail(param_copy);
   }

   return copy;
}

ir_constant *
ir_constant::clone(void *mem_ctx, struct hash_table *ht) const
{
   (void)ht;

   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_INT:
   case GLSL_TYPE_FLOAT:
   case GLSL_TYPE_BOOL:
      return new(mem_ctx) ir_constant(this->type, &this->value);

   case GLSL_TYPE_STRUCT: {
      ir_constant *c = new(mem_ctx) ir_constant;

      c->type = this->type;
      for (exec_node *node = this->components.head
	      ; !node->is_tail_sentinel()
	      ; node = node->next) {
	 ir_constant *const orig = (ir_constant *) node;

	 c->components.push_tail(orig->clone(mem_ctx, NULL));
      }

      return c;
   }

   case GLSL_TYPE_ARRAY: {
      ir_constant *c = new(mem_ctx) ir_constant;

      c->type = this->type;
      c->array_elements = ralloc_array(c, ir_constant *, this->type->length);
      for (unsigned i = 0; i < this->type->length; i++) {
	 c->array_elements[i] = this->array_elements[i]->clone(mem_ctx, NULL);
      }
      return c;
   }

   case GLSL_TYPE_SAMPLER:
   case GLSL_TYPE_IMAGE:
   case GLSL_TYPE_ATOMIC_UINT:
   case GLSL_TYPE_VOID:
   case GLSL_TYPE_ERROR:
   case GLSL_TYPE_INTERFACE:
      assert(!"Should not get here.");
      break;
   }

   return NULL;
}


ir_precision_statement *
ir_precision_statement::clone(void *mem_ctx, struct hash_table *ht) const
{
   return new(mem_ctx) ir_precision_statement(this->precision_statement);
}

ir_typedecl_statement *
ir_typedecl_statement::clone(void *mem_ctx, struct hash_table *ht) const
{
	return new(mem_ctx) ir_typedecl_statement(this->type_decl);
}



class fixup_ir_call_visitor : public ir_hierarchical_visitor {
public:
   fixup_ir_call_visitor(struct hash_table *ht)
   {
      this->ht = ht;
   }

   virtual ir_visitor_status visit_enter(ir_call *ir)
   {
      /* Try to find the function signature referenced by the ir_call in the
       * table.  If it is found, replace it with the value from the table.
       */
      ir_function_signature *sig =
	 (ir_function_signature *) hash_table_find(this->ht, ir->callee);
      if (sig != NULL)
	 ir->callee = sig;

      /* Since this may be used before function call parameters are flattened,
       * the children also need to be processed.
       */
      return visit_continue;
   }

private:
   struct hash_table *ht;
};


static void
fixup_function_calls(struct hash_table *ht, exec_list *instructions)
{
   fixup_ir_call_visitor v(ht);
   v.run(instructions);
}


void
clone_ir_list(void *mem_ctx, exec_list *out, const exec_list *in)
{
   struct hash_table *ht =
      hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);

   foreach_in_list(const ir_instruction, original, in) {
      ir_instruction *copy = original->clone(mem_ctx, ht);

      out->push_tail(copy);
   }

   /* Make a pass over the cloned tree to fix up ir_call nodes to point to the
    * cloned ir_function_signature nodes.  This cannot be done automatically
    * during cloning because the ir_call might be a forward reference (i.e.,
    * the function signature that it references may not have been cloned yet).
    */
   fixup_function_calls(ht, out);

   hash_table_dtor(ht);
}

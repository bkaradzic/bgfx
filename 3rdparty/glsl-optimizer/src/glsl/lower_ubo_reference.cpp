/*
 * Copyright © 2012 Intel Corporation
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
 * \file lower_ubo_reference.cpp
 *
 * IR lower pass to replace dereferences of variables in a uniform
 * buffer object with usage of ir_binop_ubo_load expressions, each of
 * which can read data up to the size of a vec4.
 *
 * This relieves drivers of the responsibility to deal with tricky UBO
 * layout issues like std140 structures and row_major matrices on
 * their own.
 */

#include "ir.h"
#include "ir_builder.h"
#include "ir_rvalue_visitor.h"
#include "main/macros.h"

using namespace ir_builder;

namespace {
class lower_ubo_reference_visitor : public ir_rvalue_enter_visitor {
public:
   lower_ubo_reference_visitor(struct gl_shader *shader)
   : shader(shader)
   {
   }

   void handle_rvalue(ir_rvalue **rvalue);
   void emit_ubo_loads(ir_dereference *deref, ir_variable *base_offset,
		       unsigned int deref_offset);
   ir_expression *ubo_load(const struct glsl_type *type,
			   ir_rvalue *offset);

   void *mem_ctx;
   struct gl_shader *shader;
   struct gl_uniform_buffer_variable *ubo_var;
   unsigned uniform_block;
   bool progress;
};

static inline unsigned int
align(unsigned int a, unsigned int align)
{
   return (a + align - 1) / align * align;
}

void
lower_ubo_reference_visitor::handle_rvalue(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return;

   ir_dereference *deref = (*rvalue)->as_dereference();
   if (!deref)
      return;

   ir_variable *var = deref->variable_referenced();
   if (!var || var->uniform_block == -1)
      return;

   mem_ctx = ralloc_parent(*rvalue);
   uniform_block = var->uniform_block;
   struct gl_uniform_block *block = &shader->UniformBlocks[uniform_block];
   this->ubo_var = &block->Uniforms[var->location];
   ir_rvalue *offset = new(mem_ctx) ir_constant(0u);
   unsigned const_offset = 0;
   bool row_major = ubo_var->RowMajor;

   /* Calculate the offset to the start of the region of the UBO
    * dereferenced by *rvalue.  This may be a variable offset if an
    * array dereference has a variable index.
    */
   while (deref) {
      switch (deref->ir_type) {
      case ir_type_dereference_variable: {
	 const_offset += ubo_var->Offset;
	 deref = NULL;
	 break;
      }

      case ir_type_dereference_array: {
	 ir_dereference_array *deref_array = (ir_dereference_array *)deref;
	 unsigned array_stride;
	 if (deref_array->array->type->is_matrix() && row_major) {
	    /* When loading a vector out of a row major matrix, the
	     * step between the columns (vectors) is the size of a
	     * float, while the step between the rows (elements of a
	     * vector) is handled below in emit_ubo_loads.
	     */
	    array_stride = 4;
	 } else {
	    array_stride = deref_array->type->std140_size(row_major);
	    array_stride = align(array_stride, 16);
	 }

	 ir_constant *const_index = deref_array->array_index->as_constant();
	 if (const_index) {
	    const_offset += array_stride * const_index->value.i[0];
	 } else {
	    offset = add(offset,
			 mul(deref_array->array_index,
			     new(mem_ctx) ir_constant(array_stride)));
	 }
	 deref = deref_array->array->as_dereference();
	 break;
      }

      case ir_type_dereference_record: {
	 ir_dereference_record *deref_record = (ir_dereference_record *)deref;
	 const glsl_type *struct_type = deref_record->record->type;
	 unsigned intra_struct_offset = 0;

	 unsigned max_field_align = 16;
	 for (unsigned int i = 0; i < struct_type->length; i++) {
	    const glsl_type *type = struct_type->fields.structure[i].type;
	    unsigned field_align = type->std140_base_alignment(row_major);
	    max_field_align = MAX2(field_align, max_field_align);
	    intra_struct_offset = align(intra_struct_offset, field_align);

	    if (strcmp(struct_type->fields.structure[i].name,
		       deref_record->field) == 0)
	       break;
	    intra_struct_offset += type->std140_size(row_major);
	 }

	 const_offset = align(const_offset, max_field_align);
	 const_offset += intra_struct_offset;

	 deref = deref_record->record->as_dereference();
	 break;
      }
      default:
	 assert(!"not reached");
	 deref = NULL;
	 break;
      }
   }

   /* Now that we've calculated the offset to the start of the
    * dereference, walk over the type and emit loads into a temporary.
    */
   const glsl_type *type = (*rvalue)->type;
   ir_variable *load_var = new(mem_ctx) ir_variable(type,
						    "ubo_load_temp",
						    ir_var_temporary, (*rvalue)->get_precision());
   base_ir->insert_before(load_var);

   ir_variable *load_offset = new(mem_ctx) ir_variable(glsl_type::uint_type,
						       "ubo_load_temp_offset",
						       ir_var_temporary, glsl_precision_undefined);
   base_ir->insert_before(load_offset);
   base_ir->insert_before(assign(load_offset, offset));

   deref = new(mem_ctx) ir_dereference_variable(load_var);
   emit_ubo_loads(deref, load_offset, const_offset);
   *rvalue = deref;

   progress = true;
}

ir_expression *
lower_ubo_reference_visitor::ubo_load(const glsl_type *type,
				      ir_rvalue *offset)
{
   return new(mem_ctx)
      ir_expression(ir_binop_ubo_load,
		    type,
		    new(mem_ctx) ir_constant(this->uniform_block),
		    offset);

}

/**
 * Takes LHS and emits a series of assignments into its components
 * from the UBO variable at variable_offset + deref_offset.
 *
 * Recursively calls itself to break the deref down to the point that
 * the ir_binop_ubo_load expressions generated are contiguous scalars
 * or vectors.
 */
void
lower_ubo_reference_visitor::emit_ubo_loads(ir_dereference *deref,
					    ir_variable *base_offset,
					    unsigned int deref_offset)
{
   if (deref->type->is_record()) {
      unsigned int field_offset = 0;

      for (unsigned i = 0; i < deref->type->length; i++) {
	 const struct glsl_struct_field *field =
	    &deref->type->fields.structure[i];
	 ir_dereference *field_deref =
	    new(mem_ctx) ir_dereference_record(deref->clone(mem_ctx, NULL),
					       field->name);

	 field_offset =
	    align(field_offset,
		  field->type->std140_base_alignment(ubo_var->RowMajor));

	 emit_ubo_loads(field_deref, base_offset, deref_offset + field_offset);

	 field_offset += field->type->std140_size(ubo_var->RowMajor);
      }
      return;
   }

   if (deref->type->is_array()) {
      unsigned array_stride =
	 align(deref->type->fields.array->std140_size(ubo_var->RowMajor), 16);

      for (unsigned i = 0; i < deref->type->length; i++) {
	 ir_constant *element = new(mem_ctx) ir_constant(i);
	 ir_dereference *element_deref =
	    new(mem_ctx) ir_dereference_array(deref->clone(mem_ctx, NULL),
					      element);
	 emit_ubo_loads(element_deref, base_offset,
			deref_offset + i * array_stride);
      }
      return;
   }

   if (deref->type->is_matrix()) {
      for (unsigned i = 0; i < deref->type->matrix_columns; i++) {
	 ir_constant *col = new(mem_ctx) ir_constant(i);
	 ir_dereference *col_deref =
	    new(mem_ctx) ir_dereference_array(deref->clone(mem_ctx, NULL),
					      col);

	 /* std140 always rounds the stride of arrays (and matrices)
	  * to a vec4, so matrices are always 16 between columns/rows.
	  */
	 emit_ubo_loads(col_deref, base_offset, deref_offset + i * 16);
      }
      return;
   }

   assert(deref->type->is_scalar() ||
	  deref->type->is_vector());

   if (!ubo_var->RowMajor) {
      ir_rvalue *offset = add(base_offset,
			      new(mem_ctx) ir_constant(deref_offset));
      base_ir->insert_before(assign(deref->clone(mem_ctx, NULL),
				    ubo_load(deref->type, offset)));
   } else {
      /* We're dereffing a column out of a row-major matrix, so we
       * gather the vector from each stored row.
      */
      assert(deref->type->base_type == GLSL_TYPE_FLOAT);
      /* Matrices, row_major or not, are stored as if they were
       * arrays of vectors of the appropriate size in std140.
       * Arrays have their strides rounded up to a vec4, so the
       * matrix stride is always 16.
       */
      unsigned matrix_stride = 16;

      for (unsigned i = 0; i < deref->type->vector_elements; i++) {
	 ir_rvalue *chan = new(mem_ctx) ir_constant((int)i);
	 ir_dereference *deref_chan =
	    new(mem_ctx) ir_dereference_array(deref->clone(mem_ctx, NULL),
					      chan);

	 ir_rvalue *chan_offset =
	    add(base_offset,
		new(mem_ctx) ir_constant(deref_offset + i * matrix_stride));

	 base_ir->insert_before(assign(deref_chan,
				       ubo_load(glsl_type::float_type,
						chan_offset)));
      }
   }
}

} /* unnamed namespace */

void
lower_ubo_reference(struct gl_shader *shader, exec_list *instructions)
{
   lower_ubo_reference_visitor v(shader);

   /* Loop over the instructions lowering references, because we take
    * a deref of a UBO array using a UBO dereference as the index will
    * produce a collection of instructions all of which have cloned
    * UBO dereferences for that array index.
    */
   do {
      v.progress = false;
      visit_list_elements(&v, instructions);
   } while (v.progress);
}

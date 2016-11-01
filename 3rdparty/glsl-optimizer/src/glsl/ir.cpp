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
#include "main/core.h" /* for MAX2 */
#include "ir.h"
#include "glsl_types.h"

glsl_precision higher_precision (ir_instruction* a, ir_instruction* b)
{
	if (!a && !b)
		return glsl_precision_undefined;
	if (!a)
		return precision_from_ir (b);
	if (!b)
		return precision_from_ir (a);
	return higher_precision (precision_from_ir(a), precision_from_ir(b));
}


ir_rvalue::ir_rvalue(enum ir_node_type t, glsl_precision precision)
   : ir_instruction(t)
   , precision(precision)
{
   this->type = glsl_type::error_type;
}

bool ir_rvalue::is_zero() const
{
   return false;
}

bool ir_rvalue::is_one() const
{
   return false;
}

bool ir_rvalue::is_negative_one() const
{
   return false;
}

bool ir_rvalue::is_basis() const
{
   return false;
}

/**
 * Modify the swizzle make to move one component to another
 *
 * \param m    IR swizzle to be modified
 * \param from Component in the RHS that is to be swizzled
 * \param to   Desired swizzle location of \c from
 */
static void
update_rhs_swizzle(ir_swizzle_mask &m, unsigned from, unsigned to)
{
   switch (to) {
   case 0: m.x = from; break;
   case 1: m.y = from; break;
   case 2: m.z = from; break;
   case 3: m.w = from; break;
   default: assert(!"Should not get here.");
   }

   m.num_components = MAX2(m.num_components, (to + 1));
}

void
ir_assignment::set_lhs(ir_rvalue *lhs)
{
   void *mem_ctx = this;
   bool swizzled = false;

   while (lhs != NULL) {
      ir_swizzle *swiz = lhs->as_swizzle();

      if (swiz == NULL)
	 break;

      unsigned write_mask = 0;
      ir_swizzle_mask rhs_swiz = { 0, 0, 0, 0, 0, 0 };

      for (unsigned i = 0; i < swiz->mask.num_components; i++) {
	 unsigned c = 0;

	 switch (i) {
	 case 0: c = swiz->mask.x; break;
	 case 1: c = swiz->mask.y; break;
	 case 2: c = swiz->mask.z; break;
	 case 3: c = swiz->mask.w; break;
	 default: assert(!"Should not get here.");
	 }

	 write_mask |= (((this->write_mask >> i) & 1) << c);
	 update_rhs_swizzle(rhs_swiz, i, c);
      }

      this->write_mask = write_mask;
      lhs = swiz->val;

      this->rhs = new(mem_ctx) ir_swizzle(this->rhs, rhs_swiz);
      swizzled = true;
   }

   if (swizzled) {
      /* Now, RHS channels line up with the LHS writemask.  Collapse it
       * to just the channels that will be written.
       */
      ir_swizzle_mask rhs_swiz = { 0, 0, 0, 0, 0, 0 };
      int rhs_chan = 0;
      for (int i = 0; i < 4; i++) {
	 if (write_mask & (1 << i))
	    update_rhs_swizzle(rhs_swiz, i, rhs_chan++);
      }
      this->rhs = new(mem_ctx) ir_swizzle(this->rhs, rhs_swiz);
   }

   assert((lhs == NULL) || lhs->as_dereference());

   this->lhs = (ir_dereference *) lhs;
}

ir_variable *
ir_assignment::whole_variable_written()
{
   ir_variable *v = this->lhs->whole_variable_referenced();

   if (v == NULL)
      return NULL;

   if (v->type->is_scalar())
      return v;

   if (v->type->is_vector()) {
      const unsigned mask = (1U << v->type->vector_elements) - 1;

      if (mask != this->write_mask)
	 return NULL;
   }

   /* Either all the vector components are assigned or the variable is some
    * composite type (and the whole thing is assigned.
    */
   return v;
}

ir_assignment::ir_assignment(ir_dereference *lhs, ir_rvalue *rhs,
			     ir_rvalue *condition, unsigned write_mask)
   : ir_instruction(ir_type_assignment)
{
   this->condition = condition;
   this->rhs = rhs;
   this->lhs = lhs;
   this->write_mask = write_mask;

   if (lhs->type->is_scalar() || lhs->type->is_vector()) {
      int lhs_components = 0;
      for (int i = 0; i < 4; i++) {
	 if (write_mask & (1 << i))
	    lhs_components++;
      }

      assert(lhs_components == this->rhs->type->vector_elements);
   }
}

ir_assignment::ir_assignment(ir_rvalue *lhs, ir_rvalue *rhs,
			     ir_rvalue *condition)
   : ir_instruction(ir_type_assignment)
{
   this->condition = condition;
   this->rhs = rhs;

   /* If the RHS is a vector type, assume that all components of the vector
    * type are being written to the LHS.  The write mask comes from the RHS
    * because we can have a case where the LHS is a vec4 and the RHS is a
    * vec3.  In that case, the assignment is:
    *
    *     (assign (...) (xyz) (var_ref lhs) (var_ref rhs))
    */
   if (rhs->type->is_vector())
      this->write_mask = (1U << rhs->type->vector_elements) - 1;
   else if (rhs->type->is_scalar())
      this->write_mask = 1;
   else
      this->write_mask = 0;

   this->set_lhs(lhs);
}

ir_expression::ir_expression(int op, const struct glsl_type *type,
			     ir_rvalue *op0, ir_rvalue *op1,
			     ir_rvalue *op2, ir_rvalue *op3)
   : ir_rvalue(ir_type_expression, higher_precision(higher_precision(op0,op1), higher_precision(op2,op3)))
{
   this->type = type;
   this->operation = ir_expression_operation(op);
   this->operands[0] = op0;
   this->operands[1] = op1;
   this->operands[2] = op2;
   this->operands[3] = op3;
#ifndef NDEBUG
   int num_operands = get_num_operands(this->operation);
   for (int i = num_operands; i < 4; i++) {
      assert(this->operands[i] == NULL);
   }
#endif
}

ir_expression::ir_expression(int op, ir_rvalue *op0)
   : ir_rvalue(ir_type_expression, precision_from_ir(op0))
{
   this->operation = ir_expression_operation(op);
   this->operands[0] = op0;
   this->operands[1] = NULL;
   this->operands[2] = NULL;
   this->operands[3] = NULL;

   assert(op <= ir_last_unop);

   switch (this->operation) {
   case ir_unop_bit_not:
   case ir_unop_logic_not:
   case ir_unop_neg:
   case ir_unop_abs:
   case ir_unop_sign:
   case ir_unop_rcp:
   case ir_unop_rsq:
   case ir_unop_sqrt:
   case ir_unop_normalize:
   case ir_unop_exp:
   case ir_unop_log:
   case ir_unop_exp2:
   case ir_unop_log2:
   case ir_unop_trunc:
   case ir_unop_ceil:
   case ir_unop_floor:
   case ir_unop_fract:
   case ir_unop_round_even:
   case ir_unop_sin:
   case ir_unop_cos:
   case ir_unop_sin_reduced:
   case ir_unop_cos_reduced:
   case ir_unop_dFdx:
   case ir_unop_dFdx_coarse:
   case ir_unop_dFdx_fine:
   case ir_unop_dFdy:
   case ir_unop_dFdy_coarse:
   case ir_unop_dFdy_fine:
   case ir_unop_bitfield_reverse:
   case ir_unop_interpolate_at_centroid:
   case ir_unop_saturate:
      this->type = op0->type;
      break;

   case ir_unop_f2i:
   case ir_unop_b2i:
   case ir_unop_u2i:
   case ir_unop_bitcast_f2i:
   case ir_unop_bit_count:
   case ir_unop_find_msb:
   case ir_unop_find_lsb:
      this->type = glsl_type::get_instance(GLSL_TYPE_INT,
					   op0->type->vector_elements, 1);
      break;

   case ir_unop_b2f:
   case ir_unop_i2f:
   case ir_unop_u2f:
   case ir_unop_bitcast_i2f:
   case ir_unop_bitcast_u2f:
      this->type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
					   op0->type->vector_elements, 1);
      break;

   case ir_unop_f2b:
   case ir_unop_i2b:
      this->type = glsl_type::get_instance(GLSL_TYPE_BOOL,
					   op0->type->vector_elements, 1);
      break;

   case ir_unop_i2u:
   case ir_unop_f2u:
   case ir_unop_bitcast_f2u:
      this->type = glsl_type::get_instance(GLSL_TYPE_UINT,
					   op0->type->vector_elements, 1);
      break;

   case ir_unop_noise:
   case ir_unop_unpack_half_2x16_split_x:
   case ir_unop_unpack_half_2x16_split_y:
      this->type = glsl_type::float_type;
      break;

   case ir_unop_any:
      this->type = glsl_type::bool_type;
      break;

   case ir_unop_pack_snorm_2x16:
   case ir_unop_pack_snorm_4x8:
   case ir_unop_pack_unorm_2x16:
   case ir_unop_pack_unorm_4x8:
   case ir_unop_pack_half_2x16:
      this->type = glsl_type::uint_type;
      break;

   case ir_unop_unpack_snorm_2x16:
   case ir_unop_unpack_unorm_2x16:
   case ir_unop_unpack_half_2x16:
      this->type = glsl_type::vec2_type;
      break;

   case ir_unop_unpack_snorm_4x8:
   case ir_unop_unpack_unorm_4x8:
      this->type = glsl_type::vec4_type;
      break;

   default:
      assert(!"not reached: missing automatic type setup for ir_expression");
      this->type = op0->type;
      break;
   }
}

ir_expression::ir_expression(int op, ir_rvalue *op0, ir_rvalue *op1)
   : ir_rvalue(ir_type_expression, higher_precision(op0,op1))
{
   this->operation = ir_expression_operation(op);
   this->operands[0] = op0;
   this->operands[1] = op1;
   this->operands[2] = NULL;
   this->operands[3] = NULL;

   assert(op > ir_last_unop);

   switch (this->operation) {
   case ir_binop_all_equal:
   case ir_binop_any_nequal:
      this->type = glsl_type::bool_type;
      break;

   case ir_binop_add:
   case ir_binop_sub:
   case ir_binop_min:
   case ir_binop_max:
   case ir_binop_pow:
   case ir_binop_mul:
   case ir_binop_div:
   case ir_binop_mod:
      if (op0->type->is_scalar()) {
	 this->type = op1->type;
      } else if (op1->type->is_scalar()) {
	 this->type = op0->type;
      } else {
	 /* FINISHME: matrix types */
	 assert(!op0->type->is_matrix() && !op1->type->is_matrix());
	 assert(op0->type == op1->type);
	 this->type = op0->type;
      }
      break;

   case ir_binop_logic_and:
   case ir_binop_logic_xor:
   case ir_binop_logic_or:
   case ir_binop_bit_and:
   case ir_binop_bit_xor:
   case ir_binop_bit_or:
       assert(!op0->type->is_matrix());
       assert(!op1->type->is_matrix());
      if (op0->type->is_scalar()) {
         this->type = op1->type;
      } else if (op1->type->is_scalar()) {
         this->type = op0->type;
      } else {
          assert(op0->type->vector_elements == op1->type->vector_elements);
          this->type = op0->type;
      }
      break;

   case ir_binop_equal:
   case ir_binop_nequal:
   case ir_binop_lequal:
   case ir_binop_gequal:
   case ir_binop_less:
   case ir_binop_greater:
      assert(op0->type == op1->type);
      this->type = glsl_type::get_instance(GLSL_TYPE_BOOL,
					   op0->type->vector_elements, 1);
      break;

   case ir_binop_dot:
      this->type = glsl_type::float_type;
      break;

   case ir_binop_pack_half_2x16_split:
      this->type = glsl_type::uint_type;
      break;

   case ir_binop_imul_high:
   case ir_binop_carry:
   case ir_binop_borrow:
   case ir_binop_lshift:
   case ir_binop_rshift:
   case ir_binop_bfm:
   case ir_binop_ldexp:
   case ir_binop_interpolate_at_offset:
   case ir_binop_interpolate_at_sample:
      this->type = op0->type;
      this->set_precision(op0->get_precision());
      break;

   case ir_binop_vector_extract:
      this->type = op0->type->get_scalar_type();
      this->set_precision(op0->get_precision());
      break;

   default:
      assert(!"not reached: missing automatic type setup for ir_expression");
      this->type = glsl_type::float_type;
   }
}

ir_expression::ir_expression(int op, ir_rvalue *op0, ir_rvalue *op1,
                             ir_rvalue *op2)
   : ir_rvalue(ir_type_expression, higher_precision(precision_from_ir(op0),higher_precision(op1,op2)))
{
   this->operation = ir_expression_operation(op);
   this->operands[0] = op0;
   this->operands[1] = op1;
   this->operands[2] = op2;
   this->operands[3] = NULL;

   assert(op > ir_last_binop && op <= ir_last_triop);

   switch (this->operation) {
   case ir_triop_fma:
   case ir_triop_clamp:
   case ir_triop_lrp:
   case ir_triop_bitfield_extract:
   case ir_triop_vector_insert:
      this->type = op0->type;
      break;

   case ir_triop_bfi:
   case ir_triop_csel:
      this->type = op1->type;
      break;

   default:
      assert(!"not reached: missing automatic type setup for ir_expression");
      this->type = glsl_type::float_type;
   }
}

unsigned int
ir_expression::get_num_operands(ir_expression_operation op)
{
   assert(op <= ir_last_opcode);

   if (op <= ir_last_unop)
      return 1;

   if (op <= ir_last_binop)
      return 2;
	
   if (op <= ir_last_triop)
      return 3;

   if (op <= ir_last_quadop)
      return 4;

   assert(false);
   return 0;
}

static const char *const operator_strs[] = {
   "~",
   "!",
   "neg",
   "abs",
   "sign",
   "rcp",
   "rsq",
   "sqrt",
   "normalize",
   "exp",
   "log",
   "exp2",
   "log2",
   "f2i",
   "f2u",
   "i2f",
   "f2b",
   "b2f",
   "i2b",
   "b2i",
   "u2f",
   "i2u",
   "u2i",
   "bitcast_i2f",
   "bitcast_f2i",
   "bitcast_u2f",
   "bitcast_f2u",
   "any",
   "trunc",
   "ceil",
   "floor",
   "fract",
   "round_even",
   "sin",
   "cos",
   "sin_reduced",
   "cos_reduced",
   "dFdx",
   "dFdxCoarse",
   "dFdxFine",
   "dFdy",
   "dFdyCoarse",
   "dFdyFine",
   "packSnorm2x16",
   "packSnorm4x8",
   "packUnorm2x16",
   "packUnorm4x8",
   "packHalf2x16",
   "unpackSnorm2x16",
   "unpackSnorm4x8",
   "unpackUnorm2x16",
   "unpackUnorm4x8",
   "unpackHalf2x16",
   "unpackHalf2x16_split_x",
   "unpackHalf2x16_split_y",
   "bitfield_reverse",
   "bit_count",
   "find_msb",
   "find_lsb",
   "sat",
   "noise",
   "interpolate_at_centroid",
   "+",
   "-",
   "*",
   "imul_high",
   "/",
   "carry",
   "borrow",
   "%",
   "<",
   ">",
   "<=",
   ">=",
   "==",
   "!=",
   "all_equal",
   "any_nequal",
   "<<",
   ">>",
   "&",
   "^",
   "|",
   "&&",
   "^^",
   "||",
   "dot",
   "min",
   "max",
   "pow",
   "packHalf2x16_split",
   "bfm",
   "ubo_load",
   "ldexp",
   "vector_extract",
   "interpolate_at_offset",
   "interpolate_at_sample",
   "fma",
   "clamp",
   "lrp",
   "csel",
   "bfi",
   "bitfield_extract",
   "vector_insert",
   "bitfield_insert",
   "vector",
};

const char *ir_expression::operator_string(ir_expression_operation op)
{
   assert((unsigned int) op < Elements(operator_strs));
   assert(Elements(operator_strs) == (ir_quadop_vector + 1));
   return operator_strs[op];
}

const char *ir_expression::operator_string()
{
   return operator_string(this->operation);
}

const char*
depth_layout_string(ir_depth_layout layout)
{
   switch(layout) {
   case ir_depth_layout_none:      return "";
   case ir_depth_layout_any:       return "depth_any";
   case ir_depth_layout_greater:   return "depth_greater";
   case ir_depth_layout_less:      return "depth_less";
   case ir_depth_layout_unchanged: return "depth_unchanged";

   default:
      assert(0);
      return "";
   }
}

ir_expression_operation
ir_expression::get_operator(const char *str)
{
   const int operator_count = sizeof(operator_strs) / sizeof(operator_strs[0]);
   for (int op = 0; op < operator_count; op++) {
      if (strcmp(str, operator_strs[op]) == 0)
	 return (ir_expression_operation) op;
   }
   return (ir_expression_operation) -1;
}

ir_constant::ir_constant()
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
}

ir_constant::ir_constant(const struct glsl_type *type,
			 const ir_constant_data *data, glsl_precision precision)
   : ir_rvalue(ir_type_constant, precision)
{
   assert((type->base_type >= GLSL_TYPE_UINT)
	  && (type->base_type <= GLSL_TYPE_BOOL));

   this->type = type;
   memcpy(& this->value, data, sizeof(this->value));
}

ir_constant::ir_constant(float f, unsigned vector_elements)
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
   assert(vector_elements <= 4);
   this->type = glsl_type::get_instance(GLSL_TYPE_FLOAT, vector_elements, 1);
   for (unsigned i = 0; i < vector_elements; i++) {
      this->value.f[i] = f;
   }
   for (unsigned i = vector_elements; i < 16; i++)  {
      this->value.f[i] = 0;
   }
}

ir_constant::ir_constant(unsigned int u, unsigned vector_elements)
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
   assert(vector_elements <= 4);
   this->type = glsl_type::get_instance(GLSL_TYPE_UINT, vector_elements, 1);
   for (unsigned i = 0; i < vector_elements; i++) {
      this->value.u[i] = u;
   }
   for (unsigned i = vector_elements; i < 16; i++) {
      this->value.u[i] = 0;
   }
}

ir_constant::ir_constant(int integer, unsigned vector_elements)
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
   assert(vector_elements <= 4);
   this->type = glsl_type::get_instance(GLSL_TYPE_INT, vector_elements, 1);
   for (unsigned i = 0; i < vector_elements; i++) {
      this->value.i[i] = integer;
   }
   for (unsigned i = vector_elements; i < 16; i++) {
      this->value.i[i] = 0;
   }
}

ir_constant::ir_constant(bool b, unsigned vector_elements)
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
   assert(vector_elements <= 4);
   this->type = glsl_type::get_instance(GLSL_TYPE_BOOL, vector_elements, 1);
   for (unsigned i = 0; i < vector_elements; i++) {
      this->value.b[i] = b;
   }
   for (unsigned i = vector_elements; i < 16; i++) {
      this->value.b[i] = false;
   }
}

ir_constant::ir_constant(const ir_constant *c, unsigned i)
   : ir_rvalue(ir_type_constant, c->precision)
{
   this->type = c->type->get_base_type();

   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:  this->value.u[0] = c->value.u[i]; break;
   case GLSL_TYPE_INT:   this->value.i[0] = c->value.i[i]; break;
   case GLSL_TYPE_FLOAT: this->value.f[0] = c->value.f[i]; break;
   case GLSL_TYPE_BOOL:  this->value.b[0] = c->value.b[i]; break;
   default:              assert(!"Should not get here."); break;
   }
}

ir_constant::ir_constant(const struct glsl_type *type, exec_list *value_list)
   : ir_rvalue(ir_type_constant, glsl_precision_undefined)
{
   this->type = type;

   assert(type->is_scalar() || type->is_vector() || type->is_matrix()
	  || type->is_record() || type->is_array());

   if (type->is_array()) {
      this->array_elements = ralloc_array(this, ir_constant *, type->length);
      unsigned i = 0;
      foreach_in_list(ir_constant, value, value_list) {
	 assert(value->as_constant() != NULL);

	 this->array_elements[i++] = value;
      }
      return;
   }

   /* If the constant is a record, the types of each of the entries in
    * value_list must be a 1-for-1 match with the structure components.  Each
    * entry must also be a constant.  Just move the nodes from the value_list
    * to the list in the ir_constant.
    */
   /* FINISHME: Should there be some type checking and / or assertions here? */
   /* FINISHME: Should the new constant take ownership of the nodes from
    * FINISHME: value_list, or should it make copies?
    */
   if (type->is_record()) {
      value_list->move_nodes_to(& this->components);
      return;
   }

   for (unsigned i = 0; i < 16; i++) {
      this->value.u[i] = 0;
   }

   ir_constant *value = (ir_constant *) (value_list->head);

   /* Constructors with exactly one scalar argument are special for vectors
    * and matrices.  For vectors, the scalar value is replicated to fill all
    * the components.  For matrices, the scalar fills the components of the
    * diagonal while the rest is filled with 0.
    */
   if (value->type->is_scalar() && value->next->is_tail_sentinel()) {
      if (type->is_matrix()) {
	 /* Matrix - fill diagonal (rest is already set to 0) */
	 assert(type->base_type == GLSL_TYPE_FLOAT);
	 for (unsigned i = 0; i < type->matrix_columns; i++)
	    this->value.f[i * type->vector_elements + i] = value->value.f[0];
      } else {
	 /* Vector or scalar - fill all components */
	 switch (type->base_type) {
	 case GLSL_TYPE_UINT:
	 case GLSL_TYPE_INT:
	    for (unsigned i = 0; i < type->components(); i++)
	       this->value.u[i] = value->value.u[0];
	    break;
	 case GLSL_TYPE_FLOAT:
	    for (unsigned i = 0; i < type->components(); i++)
	       this->value.f[i] = value->value.f[0];
	    break;
	 case GLSL_TYPE_BOOL:
	    for (unsigned i = 0; i < type->components(); i++)
	       this->value.b[i] = value->value.b[0];
	    break;
	 default:
	    assert(!"Should not get here.");
	    break;
	 }
      }
      return;
   }

   if (type->is_matrix() && value->type->is_matrix()) {
      assert(value->next->is_tail_sentinel());

      /* From section 5.4.2 of the GLSL 1.20 spec:
       * "If a matrix is constructed from a matrix, then each component
       *  (column i, row j) in the result that has a corresponding component
       *  (column i, row j) in the argument will be initialized from there."
       */
      unsigned cols = MIN2(type->matrix_columns, value->type->matrix_columns);
      unsigned rows = MIN2(type->vector_elements, value->type->vector_elements);
      for (unsigned i = 0; i < cols; i++) {
	 for (unsigned j = 0; j < rows; j++) {
	    const unsigned src = i * value->type->vector_elements + j;
	    const unsigned dst = i * type->vector_elements + j;
	    this->value.f[dst] = value->value.f[src];
	 }
      }

      /* "All other components will be initialized to the identity matrix." */
      for (unsigned i = cols; i < type->matrix_columns; i++)
	 this->value.f[i * type->vector_elements + i] = 1.0;

      return;
   }

   /* Use each component from each entry in the value_list to initialize one
    * component of the constant being constructed.
    */
   for (unsigned i = 0; i < type->components(); /* empty */) {
      assert(value->as_constant() != NULL);
      assert(!value->is_tail_sentinel());

      for (unsigned j = 0; j < value->type->components(); j++) {
	 switch (type->base_type) {
	 case GLSL_TYPE_UINT:
	    this->value.u[i] = value->get_uint_component(j);
	    break;
	 case GLSL_TYPE_INT:
	    this->value.i[i] = value->get_int_component(j);
	    break;
	 case GLSL_TYPE_FLOAT:
	    this->value.f[i] = value->get_float_component(j);
	    break;
	 case GLSL_TYPE_BOOL:
	    this->value.b[i] = value->get_bool_component(j);
	    break;
	 default:
	    /* FINISHME: What to do?  Exceptions are not the answer.
	     */
	    break;
	 }

	 i++;
	 if (i >= type->components())
	    break;
      }

      value = (ir_constant *) value->next;
   }
}

ir_constant *
ir_constant::zero(void *mem_ctx, const glsl_type *type)
{
   assert(type->is_scalar() || type->is_vector() || type->is_matrix()
	  || type->is_record() || type->is_array());

   ir_constant *c = new(mem_ctx) ir_constant;
   c->type = type;
   memset(&c->value, 0, sizeof(c->value));

   if (type->is_array()) {
      c->array_elements = ralloc_array(c, ir_constant *, type->length);

      for (unsigned i = 0; i < type->length; i++)
	 c->array_elements[i] = ir_constant::zero(c, type->element_type());
   }

   if (type->is_record()) {
      for (unsigned i = 0; i < type->length; i++) {
	 ir_constant *comp = ir_constant::zero(mem_ctx, type->fields.structure[i].type);
	 c->components.push_tail(comp);
      }
   }

   return c;
}

bool
ir_constant::get_bool_component(unsigned i) const
{
   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:  return this->value.u[i] != 0;
   case GLSL_TYPE_INT:   return this->value.i[i] != 0;
   case GLSL_TYPE_FLOAT: return ((int)this->value.f[i]) != 0;
   case GLSL_TYPE_BOOL:  return this->value.b[i];
   default:              assert(!"Should not get here."); break;
   }

   /* Must return something to make the compiler happy.  This is clearly an
    * error case.
    */
   return false;
}

float
ir_constant::get_float_component(unsigned i) const
{
   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:  return (float) this->value.u[i];
   case GLSL_TYPE_INT:   return (float) this->value.i[i];
   case GLSL_TYPE_FLOAT: return this->value.f[i];
   case GLSL_TYPE_BOOL:  return this->value.b[i] ? 1.0f : 0.0f;
   default:              assert(!"Should not get here."); break;
   }

   /* Must return something to make the compiler happy.  This is clearly an
    * error case.
    */
   return 0.0;
}

int
ir_constant::get_int_component(unsigned i) const
{
   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:  return this->value.u[i];
   case GLSL_TYPE_INT:   return this->value.i[i];
   case GLSL_TYPE_FLOAT: return (int) this->value.f[i];
   case GLSL_TYPE_BOOL:  return this->value.b[i] ? 1 : 0;
   default:              assert(!"Should not get here."); break;
   }

   /* Must return something to make the compiler happy.  This is clearly an
    * error case.
    */
   return 0;
}

unsigned
ir_constant::get_uint_component(unsigned i) const
{
   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:  return this->value.u[i];
   case GLSL_TYPE_INT:   return this->value.i[i];
   case GLSL_TYPE_FLOAT: return (unsigned) this->value.f[i];
   case GLSL_TYPE_BOOL:  return this->value.b[i] ? 1 : 0;
   default:              assert(!"Should not get here."); break;
   }

   /* Must return something to make the compiler happy.  This is clearly an
    * error case.
    */
   return 0;
}

ir_constant *
ir_constant::get_array_element(unsigned i) const
{
   assert(this->type->is_array());

   /* From page 35 (page 41 of the PDF) of the GLSL 1.20 spec:
    *
    *     "Behavior is undefined if a shader subscripts an array with an index
    *     less than 0 or greater than or equal to the size the array was
    *     declared with."
    *
    * Most out-of-bounds accesses are removed before things could get this far.
    * There are cases where non-constant array index values can get constant
    * folded.
    */
   if (int(i) < 0)
      i = 0;
   else if (i >= this->type->length)
      i = this->type->length - 1;

   return array_elements[i];
}

ir_constant *
ir_constant::get_record_field(const char *name)
{
   int idx = this->type->field_index(name);

   if (idx < 0)
      return NULL;

   if (this->components.is_empty())
      return NULL;

   exec_node *node = this->components.head;
   for (int i = 0; i < idx; i++) {
      node = node->next;

      /* If the end of the list is encountered before the element matching the
       * requested field is found, return NULL.
       */
      if (node->is_tail_sentinel())
	 return NULL;
   }

   return (ir_constant *) node;
}

void
ir_constant::copy_offset(ir_constant *src, int offset)
{
   switch (this->type->base_type) {
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_INT:
   case GLSL_TYPE_FLOAT:
   case GLSL_TYPE_BOOL: {
      unsigned int size = src->type->components();
      assert (size <= this->type->components() - offset);
      for (unsigned int i=0; i<size; i++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    value.u[i+offset] = src->get_uint_component(i);
	    break;
	 case GLSL_TYPE_INT:
	    value.i[i+offset] = src->get_int_component(i);
	    break;
	 case GLSL_TYPE_FLOAT:
	    value.f[i+offset] = src->get_float_component(i);
	    break;
	 case GLSL_TYPE_BOOL:
	    value.b[i+offset] = src->get_bool_component(i);
	    break;
	 default: // Shut up the compiler
	    break;
	 }
      }
      break;
   }

   case GLSL_TYPE_STRUCT: {
      assert (src->type == this->type);
      this->components.make_empty();
      foreach_in_list(ir_constant, orig, &src->components) {
	 this->components.push_tail(orig->clone(this, NULL));
      }
      break;
   }

   case GLSL_TYPE_ARRAY: {
      assert (src->type == this->type);
      for (unsigned i = 0; i < this->type->length; i++) {
	 this->array_elements[i] = src->array_elements[i]->clone(this, NULL);
      }
      break;
   }

   default:
      assert(!"Should not get here.");
      break;
   }
}

void
ir_constant::copy_masked_offset(ir_constant *src, int offset, unsigned int mask)
{
   assert (!type->is_array() && !type->is_record());

   if (!type->is_vector() && !type->is_matrix()) {
      offset = 0;
      mask = 1;
   }

   int id = 0;
   for (int i=0; i<4; i++) {
      if (mask & (1 << i)) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    value.u[i+offset] = src->get_uint_component(id++);
	    break;
	 case GLSL_TYPE_INT:
	    value.i[i+offset] = src->get_int_component(id++);
	    break;
	 case GLSL_TYPE_FLOAT:
	    value.f[i+offset] = src->get_float_component(id++);
	    break;
	 case GLSL_TYPE_BOOL:
	    value.b[i+offset] = src->get_bool_component(id++);
	    break;
	 default:
	    assert(!"Should not get here.");
	    return;
	 }
      }
   }
}

bool
ir_constant::has_value(const ir_constant *c) const
{
   if (this->type != c->type)
      return false;

   if (this->type->is_array()) {
      for (unsigned i = 0; i < this->type->length; i++) {
	 if (!this->array_elements[i]->has_value(c->array_elements[i]))
	    return false;
      }
      return true;
   }

   if (this->type->base_type == GLSL_TYPE_STRUCT) {
      const exec_node *a_node = this->components.head;
      const exec_node *b_node = c->components.head;

      while (!a_node->is_tail_sentinel()) {
	 assert(!b_node->is_tail_sentinel());

	 const ir_constant *const a_field = (ir_constant *) a_node;
	 const ir_constant *const b_field = (ir_constant *) b_node;

	 if (!a_field->has_value(b_field))
	    return false;

	 a_node = a_node->next;
	 b_node = b_node->next;
      }

      return true;
   }

   for (unsigned i = 0; i < this->type->components(); i++) {
      switch (this->type->base_type) {
      case GLSL_TYPE_UINT:
	 if (this->value.u[i] != c->value.u[i])
	    return false;
	 break;
      case GLSL_TYPE_INT:
	 if (this->value.i[i] != c->value.i[i])
	    return false;
	 break;
      case GLSL_TYPE_FLOAT:
	 if (this->value.f[i] != c->value.f[i])
	    return false;
	 break;
      case GLSL_TYPE_BOOL:
	 if (this->value.b[i] != c->value.b[i])
	    return false;
	 break;
      default:
	 assert(!"Should not get here.");
	 return false;
      }
   }

   return true;
}

bool
ir_constant::is_value(float f, int i) const
{
   if (!this->type->is_scalar() && !this->type->is_vector())
      return false;

   /* Only accept boolean values for 0/1. */
   if (int(bool(i)) != i && this->type->is_boolean())
      return false;

   for (unsigned c = 0; c < this->type->vector_elements; c++) {
      switch (this->type->base_type) {
      case GLSL_TYPE_FLOAT:
	 if (this->value.f[c] != f)
	    return false;
	 break;
      case GLSL_TYPE_INT:
	 if (this->value.i[c] != i)
	    return false;
	 break;
      case GLSL_TYPE_UINT:
	 if (this->value.u[c] != unsigned(i))
	    return false;
	 break;
      case GLSL_TYPE_BOOL:
	 if (this->value.b[c] != bool(i))
	    return false;
	 break;
      default:
	 /* The only other base types are structures, arrays, and samplers.
	  * Samplers cannot be constants, and the others should have been
	  * filtered out above.
	  */
	 assert(!"Should not get here.");
	 return false;
      }
   }

   return true;
}

bool
ir_constant::is_zero() const
{
   return is_value(0.0, 0);
}

bool
ir_constant::is_one() const
{
   return is_value(1.0, 1);
}

bool
ir_constant::is_negative_one() const
{
   return is_value(-1.0, -1);
}

bool
ir_constant::is_basis() const
{
   if (!this->type->is_scalar() && !this->type->is_vector())
      return false;

   if (this->type->is_boolean())
      return false;

   unsigned ones = 0;
   for (unsigned c = 0; c < this->type->vector_elements; c++) {
      switch (this->type->base_type) {
      case GLSL_TYPE_FLOAT:
	 if (this->value.f[c] == 1.0)
	    ones++;
	 else if (this->value.f[c] != 0.0)
	    return false;
	 break;
      case GLSL_TYPE_INT:
	 if (this->value.i[c] == 1)
	    ones++;
	 else if (this->value.i[c] != 0)
	    return false;
	 break;
      case GLSL_TYPE_UINT:
	 if (int(this->value.u[c]) == 1)
	    ones++;
	 else if (int(this->value.u[c]) != 0)
	    return false;
	 break;
      default:
	 /* The only other base types are structures, arrays, samplers, and
	  * booleans.  Samplers cannot be constants, and the others should
	  * have been filtered out above.
	  */
	 assert(!"Should not get here.");
	 return false;
      }
   }

   return ones == 1;
}

bool
ir_constant::is_uint16_constant() const
{
   if (!type->is_integer())
      return false;

   return value.u[0] < (1 << 16);
}

ir_loop::ir_loop()
   : ir_instruction(ir_type_loop)
{
}


ir_dereference_variable::ir_dereference_variable(ir_variable *var)
   : ir_dereference(ir_type_dereference_variable, precision_from_ir(var))
{
   assert(var != NULL);

   this->var = var;
   this->type = var->type;
}


ir_dereference_array::ir_dereference_array(ir_rvalue *value,
					   ir_rvalue *array_index)
   : ir_dereference(ir_type_dereference_array, precision_from_ir(value))
{
   this->array_index = array_index;
   this->set_array(value);
}


ir_dereference_array::ir_dereference_array(ir_variable *var,
					   ir_rvalue *array_index)
   : ir_dereference(ir_type_dereference_array, precision_from_ir(var))
{
   void *ctx = ralloc_parent(var);

   this->array_index = array_index;
   this->set_array(new(ctx) ir_dereference_variable(var));
}


void
ir_dereference_array::set_array(ir_rvalue *value)
{
   assert(value != NULL);

   this->array = value;

   const glsl_type *const vt = this->array->type;

   if (vt->is_array()) {
      type = vt->element_type();
   } else if (vt->is_matrix()) {
      type = vt->column_type();
   } else if (vt->is_vector()) {
      type = vt->get_base_type();
   }
}


ir_dereference_record::ir_dereference_record(ir_rvalue *value,
					     const char *field)
   : ir_dereference(ir_type_dereference_record, precision_from_ir(value))
{
   assert(value != NULL);

   this->record = value;
   this->field = ralloc_strdup(this, field);
   this->type = this->record->type->field_type(field);
   if (this->record)
      this->precision = this->record->type->field_precision(field);
}


ir_dereference_record::ir_dereference_record(ir_variable *var,
					     const char *field)
   : ir_dereference(ir_type_dereference_record, precision_from_ir(var))
{
   void *ctx = ralloc_parent(var);

   this->record = new(ctx) ir_dereference_variable(var);
   this->field = ralloc_strdup(this, field);
   this->type = this->record->type->field_type(field);
   if (this->record)
      this->precision = this->record->type->field_precision(field);
}

bool
ir_dereference::is_lvalue() const
{
   ir_variable *var = this->variable_referenced();

   /* Every l-value derference chain eventually ends in a variable.
    */
   if ((var == NULL) || var->data.read_only)
      return false;

   /* From section 4.1.7 of the GLSL 4.40 spec:
    *
    *   "Opaque variables cannot be treated as l-values; hence cannot
    *    be used as out or inout function parameters, nor can they be
    *    assigned into."
    */
   if (this->type->contains_opaque())
      return false;

   return true;
}


static const char * const tex_opcode_strs[] = { "tex", "txb", "txl", "txd", "txf", "txf_ms", "txs", "lod", "tg4", "query_levels" };

const char *ir_texture::opcode_string()
{
   assert((unsigned int) op <=
	  sizeof(tex_opcode_strs) / sizeof(tex_opcode_strs[0]));
   return tex_opcode_strs[op];
}

ir_texture_opcode
ir_texture::get_opcode(const char *str)
{
   const int count = sizeof(tex_opcode_strs) / sizeof(tex_opcode_strs[0]);
   for (int op = 0; op < count; op++) {
      if (strcmp(str, tex_opcode_strs[op]) == 0)
	 return (ir_texture_opcode) op;
   }
   return (ir_texture_opcode) -1;
}


void
ir_texture::set_sampler(ir_dereference *sampler, const glsl_type *type)
{
   assert(sampler != NULL);
   assert(type != NULL);
   this->sampler = sampler;
   this->type = type;

   if (this->op == ir_txs || this->op == ir_query_levels) {
      assert(type->base_type == GLSL_TYPE_INT);
   } else if (this->op == ir_lod) {
      assert(type->vector_elements == 2);
      assert(type->base_type == GLSL_TYPE_FLOAT);
   } else {
      assert(sampler->type->sampler_type == (int) type->base_type);
      if (sampler->type->sampler_shadow)
	 assert(type->vector_elements == 4 || type->vector_elements == 1);
      else
	 assert(type->vector_elements == 4);
   }
}


bool
ir_texture::has_lod(const glsl_type *sampler_type)
{
	assert(sampler_type->is_sampler());

	switch (sampler_type->sampler_dimensionality) {
		case GLSL_SAMPLER_DIM_RECT:
		case GLSL_SAMPLER_DIM_BUF:
		case GLSL_SAMPLER_DIM_MS:
			return false;
		default:
			return true;
	}
}


void
ir_swizzle::init_mask(const unsigned *comp, unsigned count)
{
   assert((count >= 1) && (count <= 4));

   memset(&this->mask, 0, sizeof(this->mask));
   this->mask.num_components = count;

   unsigned dup_mask = 0;
   switch (count) {
   case 4:
      assert(comp[3] <= 3);
      dup_mask |= (1U << comp[3])
	 & ((1U << comp[0]) | (1U << comp[1]) | (1U << comp[2]));
      this->mask.w = comp[3];

   case 3:
      assert(comp[2] <= 3);
      dup_mask |= (1U << comp[2])
	 & ((1U << comp[0]) | (1U << comp[1]));
      this->mask.z = comp[2];

   case 2:
      assert(comp[1] <= 3);
      dup_mask |= (1U << comp[1])
	 & ((1U << comp[0]));
      this->mask.y = comp[1];

   case 1:
      assert(comp[0] <= 3);
      this->mask.x = comp[0];
   }

   this->mask.has_duplicates = dup_mask != 0;

   /* Based on the number of elements in the swizzle and the base type
    * (i.e., float, int, unsigned, or bool) of the vector being swizzled,
    * generate the type of the resulting value.
    */
   type = glsl_type::get_instance(val->type->base_type, mask.num_components, 1);
}

ir_swizzle::ir_swizzle(ir_rvalue *val, unsigned x, unsigned y, unsigned z,
		       unsigned w, unsigned count)
   : ir_rvalue(ir_type_swizzle, precision_from_ir(val)), val(val)
{
   const unsigned components[4] = { x, y, z, w };
   this->init_mask(components, count);
}

ir_swizzle::ir_swizzle(ir_rvalue *val, const unsigned *comp,
		       unsigned count)
   : ir_rvalue(ir_type_swizzle, precision_from_ir(val)), val(val)
{
   this->init_mask(comp, count);
}

ir_swizzle::ir_swizzle(ir_rvalue *val, ir_swizzle_mask mask)
   : ir_rvalue(ir_type_swizzle, precision_from_ir(val))
{
   this->val = val;
   this->mask = mask;
   this->type = glsl_type::get_instance(val->type->base_type,
					mask.num_components, 1);
}

#define X 1
#define R 5
#define S 9
#define I 13

ir_swizzle *
ir_swizzle::create(ir_rvalue *val, const char *str, unsigned vector_length)
{
   void *ctx = ralloc_parent(val);

   /* For each possible swizzle character, this table encodes the value in
    * \c idx_map that represents the 0th element of the vector.  For invalid
    * swizzle characters (e.g., 'k'), a special value is used that will allow
    * detection of errors.
    */
   static const unsigned char base_idx[26] = {
   /* a  b  c  d  e  f  g  h  i  j  k  l  m */
      R, R, I, I, I, I, R, I, I, I, I, I, I,
   /* n  o  p  q  r  s  t  u  v  w  x  y  z */
      I, I, S, S, R, S, S, I, I, X, X, X, X
   };

   /* Each valid swizzle character has an entry in the previous table.  This
    * table encodes the base index encoded in the previous table plus the actual
    * index of the swizzle character.  When processing swizzles, the first
    * character in the string is indexed in the previous table.  Each character
    * in the string is indexed in this table, and the value found there has the
    * value form the first table subtracted.  The result must be on the range
    * [0,3].
    *
    * For example, the string "wzyx" will get X from the first table.  Each of
    * the charcaters will get X+3, X+2, X+1, and X+0 from this table.  After
    * subtraction, the swizzle values are { 3, 2, 1, 0 }.
    *
    * The string "wzrg" will get X from the first table.  Each of the characters
    * will get X+3, X+2, R+0, and R+1 from this table.  After subtraction, the
    * swizzle values are { 3, 2, 4, 5 }.  Since 4 and 5 are outside the range
    * [0,3], the error is detected.
    */
   static const unsigned char idx_map[26] = {
   /* a    b    c    d    e    f    g    h    i    j    k    l    m */
      R+3, R+2, 0,   0,   0,   0,   R+1, 0,   0,   0,   0,   0,   0,
   /* n    o    p    q    r    s    t    u    v    w    x    y    z */
      0,   0,   S+2, S+3, R+0, S+0, S+1, 0,   0,   X+3, X+0, X+1, X+2
   };

   int swiz_idx[4] = { 0, 0, 0, 0 };
   unsigned i;


   /* Validate the first character in the swizzle string and look up the base
    * index value as described above.
    */
   if ((str[0] < 'a') || (str[0] > 'z'))
      return NULL;

   const unsigned base = base_idx[str[0] - 'a'];


   for (i = 0; (i < 4) && (str[i] != '\0'); i++) {
      /* Validate the next character, and, as described above, convert it to a
       * swizzle index.
       */
      if ((str[i] < 'a') || (str[i] > 'z'))
	 return NULL;

      swiz_idx[i] = idx_map[str[i] - 'a'] - base;
      if ((swiz_idx[i] < 0) || (swiz_idx[i] >= (int) vector_length))
	 return NULL;
   }

   if (str[i] != '\0')
	 return NULL;

   return new(ctx) ir_swizzle(val, swiz_idx[0], swiz_idx[1], swiz_idx[2],
			      swiz_idx[3], i);
}

#undef X
#undef R
#undef S
#undef I

ir_variable *
ir_swizzle::variable_referenced() const
{
   return this->val->variable_referenced();
}


bool ir_variable::temporaries_allocate_names = false;

const char ir_variable::tmp_name[] = "compiler_temp";

ir_variable::ir_variable(const struct glsl_type *type, const char *name,
			 ir_variable_mode mode, glsl_precision precision)
   : ir_instruction(ir_type_variable)
{
   this->type = type;

   if (mode == ir_var_temporary && !ir_variable::temporaries_allocate_names)
      name = NULL;

   /* The ir_variable clone method may call this constructor with name set to
    * tmp_name.
    */
   assert(name != NULL
          || mode == ir_var_temporary
          || mode == ir_var_function_in
          || mode == ir_var_function_out
          || mode == ir_var_function_inout);
   assert(name != ir_variable::tmp_name
          || mode == ir_var_temporary);
   if (mode == ir_var_temporary
       && (name == NULL || name == ir_variable::tmp_name)) {
      this->name = ir_variable::tmp_name;
   } else {
      this->name = ralloc_strdup(this, name);
   }

   this->u.max_ifc_array_access = NULL;

   this->data.explicit_location = false;
   this->data.has_initializer = false;
   this->data.location = -1;
   this->data.location_frac = 0;
   this->data.binding = 0;
   this->data.warn_extension_index = 0;
   this->constant_value = NULL;
   this->constant_initializer = NULL;
   this->data.origin_upper_left = false;
   this->data.pixel_center_integer = false;
   this->data.depth_layout = ir_depth_layout_none;
   this->data.used = false;
   this->data.read_only = false;
   this->data.centroid = false;
   this->data.sample = false;
   this->data.invariant = false;
   this->data.how_declared = ir_var_declared_normally;
   this->data.mode = mode;
   this->data.precision = precision;
   this->data.interpolation = INTERP_QUALIFIER_NONE;
   this->data.max_array_access = 0;
   this->data.atomic.offset = 0;
   this->data.image_read_only = false;
   this->data.image_write_only = false;
   this->data.image_coherent = false;
   this->data.image_volatile = false;
   this->data.image_restrict = false;

   if (type != NULL) {
      if (type->base_type == GLSL_TYPE_SAMPLER)
         this->data.read_only = true;

      if (type->is_interface())
         this->init_interface_type(type);
      else if (type->is_array() && type->fields.array->is_interface())
         this->init_interface_type(type->fields.array);
   }
}


const char *
interpolation_string(unsigned interpolation)
{
   switch (interpolation) {
   case INTERP_QUALIFIER_NONE:          return "no";
   case INTERP_QUALIFIER_SMOOTH:        return "smooth";
   case INTERP_QUALIFIER_FLAT:          return "flat";
   case INTERP_QUALIFIER_NOPERSPECTIVE: return "noperspective";
   }

   assert(!"Should not get here.");
   return "";
}


glsl_interp_qualifier
ir_variable::determine_interpolation_mode(bool flat_shade)
{
   if (this->data.interpolation != INTERP_QUALIFIER_NONE)
      return (glsl_interp_qualifier) this->data.interpolation;
   int location = this->data.location;
   bool is_gl_Color =
      location == VARYING_SLOT_COL0 || location == VARYING_SLOT_COL1;
   if (flat_shade && is_gl_Color)
      return INTERP_QUALIFIER_FLAT;
   else
      return INTERP_QUALIFIER_SMOOTH;
}

const char *const ir_variable::warn_extension_table[] = {
   "",
   "GL_ARB_shader_stencil_export",
   "GL_AMD_shader_stencil_export",
};

void
ir_variable::enable_extension_warning(const char *extension)
{
   for (unsigned i = 0; i < Elements(warn_extension_table); i++) {
      if (strcmp(warn_extension_table[i], extension) == 0) {
         this->data.warn_extension_index = i;
         return;
      }
   }

   assert(!"Should not get here.");
   this->data.warn_extension_index = 0;
}

const char *
ir_variable::get_extension_warning() const
{
   return this->data.warn_extension_index == 0
      ? NULL : warn_extension_table[this->data.warn_extension_index];
}

ir_function_signature::ir_function_signature(const glsl_type *return_type,
                                             glsl_precision precision, builtin_available_predicate b)
   : ir_instruction(ir_type_function_signature),
     return_type(return_type), precision(precision), is_defined(false), is_intrinsic(false),
     builtin_avail(b), _function(NULL)
{
   this->origin = NULL;
}


bool
ir_function_signature::is_builtin() const
{
   return builtin_avail != NULL;
}


bool
ir_function_signature::is_builtin_available(const _mesa_glsl_parse_state *state) const
{
   /* We can't call the predicate without a state pointer, so just say that
    * the signature is available.  At compile time, we need the filtering,
    * but also receive a valid state pointer.  At link time, we're resolving
    * imported built-in prototypes to their definitions, which will always
    * be an exact match.  So we can skip the filtering.
    */
   if (state == NULL)
      return true;

   assert(builtin_avail != NULL);
   return builtin_avail(state);
}


static bool
modes_match(unsigned a, unsigned b)
{
   if (a == b)
      return true;

   /* Accept "in" vs. "const in" */
   if ((a == ir_var_const_in && b == ir_var_function_in) ||
       (b == ir_var_const_in && a == ir_var_function_in))
      return true;

   return false;
}


const char *
ir_function_signature::qualifiers_match(exec_list *params)
{
   /* check that the qualifiers match. */
   foreach_two_lists(a_node, &this->parameters, b_node, params) {
      ir_variable *a = (ir_variable *) a_node;
      ir_variable *b = (ir_variable *) b_node;

      /* NOTE: precision does not affect qualifier matching */
      if (a->data.read_only != b->data.read_only ||
	  !modes_match(a->data.mode, b->data.mode) ||
	  a->data.interpolation != b->data.interpolation ||
	  a->data.centroid != b->data.centroid ||
          a->data.sample != b->data.sample ||
          a->data.image_read_only != b->data.image_read_only ||
          a->data.image_write_only != b->data.image_write_only ||
          a->data.image_coherent != b->data.image_coherent ||
          a->data.image_volatile != b->data.image_volatile ||
          a->data.image_restrict != b->data.image_restrict) {

	 /* parameter a's qualifiers don't match */
	 return a->name;
      }
   }
   return NULL;
}


void
ir_function_signature::replace_parameters(exec_list *new_params)
{
   /* Destroy all of the previous parameter information.  If the previous
    * parameter information comes from the function prototype, it may either
    * specify incorrect parameter names or not have names at all.
    */
   new_params->move_nodes_to(&parameters);
}


ir_function::ir_function(const char *name)
   : ir_instruction(ir_type_function)
{
   this->name = ralloc_strdup(this, name);
}


bool
ir_function::has_user_signature()
{
   foreach_in_list(ir_function_signature, sig, &this->signatures) {
      if (!sig->is_builtin())
	 return true;
   }
   return false;
}


ir_rvalue *
ir_rvalue::error_value(void *mem_ctx)
{
   ir_rvalue *v = new(mem_ctx) ir_rvalue(ir_type_unset, glsl_precision_undefined);

   v->type = glsl_type::error_type;
   return v;
}


void
visit_exec_list(exec_list *list, ir_visitor *visitor)
{
   foreach_in_list_safe(ir_instruction, node, list) {
      node->accept(visitor);
   }
}


static void
steal_memory(ir_instruction *ir, void *new_ctx)
{
   ir_variable *var = ir->as_variable();
   ir_constant *constant = ir->as_constant();
   if (var != NULL && var->constant_value != NULL)
      steal_memory(var->constant_value, ir);

   if (var != NULL && var->constant_initializer != NULL)
      steal_memory(var->constant_initializer, ir);

   /* The components of aggregate constants are not visited by the normal
    * visitor, so steal their values by hand.
    */
   if (constant != NULL) {
      if (constant->type->is_record()) {
	 foreach_in_list(ir_constant, field, &constant->components) {
	    steal_memory(field, ir);
	 }
      } else if (constant->type->is_array()) {
	 for (unsigned int i = 0; i < constant->type->length; i++) {
	    steal_memory(constant->array_elements[i], ir);
	 }
      }
   }

   ralloc_steal(new_ctx, ir);
}


void
reparent_ir(exec_list *list, void *mem_ctx)
{
   foreach_in_list(ir_instruction, node, list) {
      visit_tree(node, steal_memory, mem_ctx);
   }
}


glsl_precision
precision_from_ir (ir_instruction* ir)
{
	if (!ir)
		return glsl_precision_undefined;
	ir_variable* var = ir->as_variable();
	if (var)
		return (glsl_precision)var->data.precision;
	ir_rvalue* rv = ir->as_rvalue();
	if (rv)
		return rv->get_precision();
	ir_call* fcall = ir->as_call();
	if (fcall && fcall->return_deref)
		return fcall->return_deref->get_precision();
	if (ir->ir_type == ir_type_function_signature)
	{
		ir_function_signature* sig = (ir_function_signature*)ir;
		return sig->precision;
	}
	return glsl_precision_high;
}

static ir_rvalue *
try_min_one(ir_rvalue *ir)
{
   ir_expression *expr = ir->as_expression();

   if (!expr || expr->operation != ir_binop_min)
      return NULL;

   if (expr->operands[0]->is_one())
      return expr->operands[1];

   if (expr->operands[1]->is_one())
      return expr->operands[0];

   return NULL;
}

static ir_rvalue *
try_max_zero(ir_rvalue *ir)
{
   ir_expression *expr = ir->as_expression();

   if (!expr || expr->operation != ir_binop_max)
      return NULL;

   if (expr->operands[0]->is_zero())
      return expr->operands[1];

   if (expr->operands[1]->is_zero())
      return expr->operands[0];

   return NULL;
}

ir_rvalue *
ir_rvalue::as_rvalue_to_saturate()
{
   ir_expression *expr = this->as_expression();

   if (!expr)
      return NULL;

   ir_rvalue *max_zero = try_max_zero(expr);
   if (max_zero) {
      return try_min_one(max_zero);
   } else {
      ir_rvalue *min_one = try_min_one(expr);
      if (min_one) {
	 return try_max_zero(min_one);
      }
   }

   return NULL;
}


unsigned
vertices_per_prim(GLenum prim)
{
   switch (prim) {
   case GL_POINTS:
      return 1;
   case GL_LINES:
      return 2;
   case GL_TRIANGLES:
      return 3;
   case GL_LINES_ADJACENCY:
      return 4;
   case GL_TRIANGLES_ADJACENCY:
      return 6;
   default:
      assert(!"Bad primitive");
      return 3;
   }
}

/**
 * Generate a string describing the mode of a variable
 */
const char *
mode_string(const ir_variable *var)
{
   switch (var->data.mode) {
   case ir_var_auto:
      return (var->data.read_only) ? "global constant" : "global variable";

   case ir_var_uniform:
      return "uniform";

   case ir_var_shader_in:
      return "shader input";

   case ir_var_shader_out:
      return "shader output";

   case ir_var_shader_inout:
	   return "shader inout";

   case ir_var_function_in:
   case ir_var_const_in:
      return "function input";

   case ir_var_function_out:
      return "function output";

   case ir_var_function_inout:
      return "function inout";

   case ir_var_system_value:
      return "shader input";

   case ir_var_temporary:
      return "compiler temporary";

   case ir_var_mode_count:
      break;
   }

   assert(!"Should not get here.");
   return "invalid variable";
}

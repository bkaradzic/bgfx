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
 * \file lower_instructions.cpp
 *
 * Many GPUs lack native instructions for certain expression operations, and
 * must replace them with some other expression tree.  This pass lowers some
 * of the most common cases, allowing the lowering code to be implemented once
 * rather than in each driver backend.
 *
 * Currently supported transformations:
 * - SUB_TO_ADD_NEG
 * - DIV_TO_MUL_RCP
 * - INT_DIV_TO_MUL_RCP
 * - EXP_TO_EXP2
 * - POW_TO_EXP2
 * - LOG_TO_LOG2
 * - MOD_TO_FRACT
 * - LDEXP_TO_ARITH
 * - BITFIELD_INSERT_TO_BFM_BFI
 * - CARRY_TO_ARITH
 * - BORROW_TO_ARITH
 * - SAT_TO_CLAMP
 *
 * SUB_TO_ADD_NEG:
 * ---------------
 * Breaks an ir_binop_sub expression down to add(op0, neg(op1))
 *
 * This simplifies expression reassociation, and for many backends
 * there is no subtract operation separate from adding the negation.
 * For backends with native subtract operations, they will probably
 * want to recognize add(op0, neg(op1)) or the other way around to
 * produce a subtract anyway.
 *
 * DIV_TO_MUL_RCP and INT_DIV_TO_MUL_RCP:
 * --------------------------------------
 * Breaks an ir_binop_div expression down to op0 * (rcp(op1)).
 *
 * Many GPUs don't have a divide instruction (945 and 965 included),
 * but they do have an RCP instruction to compute an approximate
 * reciprocal.  By breaking the operation down, constant reciprocals
 * can get constant folded.
 *
 * DIV_TO_MUL_RCP only lowers floating point division; INT_DIV_TO_MUL_RCP
 * handles the integer case, converting to and from floating point so that
 * RCP is possible.
 *
 * EXP_TO_EXP2 and LOG_TO_LOG2:
 * ----------------------------
 * Many GPUs don't have a base e log or exponent instruction, but they
 * do have base 2 versions, so this pass converts exp and log to exp2
 * and log2 operations.
 *
 * POW_TO_EXP2:
 * -----------
 * Many older GPUs don't have an x**y instruction.  For these GPUs, convert
 * x**y to 2**(y * log2(x)).
 *
 * MOD_TO_FRACT:
 * -------------
 * Breaks an ir_binop_mod expression down to (op1 * fract(op0 / op1))
 *
 * Many GPUs don't have a MOD instruction (945 and 965 included), and
 * if we have to break it down like this anyway, it gives an
 * opportunity to do things like constant fold the (1.0 / op1) easily.
 *
 * LDEXP_TO_ARITH:
 * -------------
 * Converts ir_binop_ldexp to arithmetic and bit operations.
 *
 * BITFIELD_INSERT_TO_BFM_BFI:
 * ---------------------------
 * Breaks ir_quadop_bitfield_insert into ir_binop_bfm (bitfield mask) and
 * ir_triop_bfi (bitfield insert).
 *
 * Many GPUs implement the bitfieldInsert() built-in from ARB_gpu_shader_5
 * with a pair of instructions.
 *
 * CARRY_TO_ARITH:
 * ---------------
 * Converts ir_carry into (x + y) < x.
 *
 * BORROW_TO_ARITH:
 * ----------------
 * Converts ir_borrow into (x < y).
 *
 * SAT_TO_CLAMP:
 * -------------
 * Converts ir_unop_saturate into min(max(x, 0.0), 1.0)
 *
 */

#include "main/core.h" /* for M_LOG2E */
#include "glsl_types.h"
#include "ir.h"
#include "ir_builder.h"
#include "ir_optimization.h"

using namespace ir_builder;

namespace {

class lower_instructions_visitor : public ir_hierarchical_visitor {
public:
   lower_instructions_visitor(unsigned lower)
      : progress(false), lower(lower) { }

   ir_visitor_status visit_leave(ir_expression *);

   bool progress;

private:
   unsigned lower; /** Bitfield of which operations to lower */

   void sub_to_add_neg(ir_expression *);
   void div_to_mul_rcp(ir_expression *);
   void int_div_to_mul_rcp(ir_expression *);
   void mod_to_fract(ir_expression *);
   void exp_to_exp2(ir_expression *);
   void pow_to_exp2(ir_expression *);
   void log_to_log2(ir_expression *);
   void bitfield_insert_to_bfm_bfi(ir_expression *);
   void ldexp_to_arith(ir_expression *);
   void carry_to_arith(ir_expression *);
   void borrow_to_arith(ir_expression *);
   void sat_to_clamp(ir_expression *);
};

} /* anonymous namespace */

/**
 * Determine if a particular type of lowering should occur
 */
#define lowering(x) (this->lower & x)

bool
lower_instructions(exec_list *instructions, unsigned what_to_lower)
{
   lower_instructions_visitor v(what_to_lower);

   visit_list_elements(&v, instructions);
   return v.progress;
}

void
lower_instructions_visitor::sub_to_add_neg(ir_expression *ir)
{
   ir->operation = ir_binop_add;
   ir->operands[1] = new(ir) ir_expression(ir_unop_neg, ir->operands[1]->type,
					   ir->operands[1], NULL);
   this->progress = true;
}

void
lower_instructions_visitor::div_to_mul_rcp(ir_expression *ir)
{
   assert(ir->operands[1]->type->is_float());

   /* New expression for the 1.0 / op1 */
   ir_rvalue *expr;
   expr = new(ir) ir_expression(ir_unop_rcp,
				ir->operands[1]->type,
				ir->operands[1]);

   /* op0 / op1 -> op0 * (1.0 / op1) */
   ir->operation = ir_binop_mul;
   ir->operands[1] = expr;

   this->progress = true;
}

void
lower_instructions_visitor::int_div_to_mul_rcp(ir_expression *ir)
{
   assert(ir->operands[1]->type->is_integer());

   /* Be careful with integer division -- we need to do it as a
    * float and re-truncate, since rcp(n > 1) of an integer would
    * just be 0.
    */
   ir_rvalue *op0, *op1;
   const struct glsl_type *vec_type;

   vec_type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
				      ir->operands[1]->type->vector_elements,
				      ir->operands[1]->type->matrix_columns);

   if (ir->operands[1]->type->base_type == GLSL_TYPE_INT)
      op1 = new(ir) ir_expression(ir_unop_i2f, vec_type, ir->operands[1], NULL);
   else
      op1 = new(ir) ir_expression(ir_unop_u2f, vec_type, ir->operands[1], NULL);

   op1 = new(ir) ir_expression(ir_unop_rcp, op1->type, op1, NULL);

   vec_type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
				      ir->operands[0]->type->vector_elements,
				      ir->operands[0]->type->matrix_columns);

   if (ir->operands[0]->type->base_type == GLSL_TYPE_INT)
      op0 = new(ir) ir_expression(ir_unop_i2f, vec_type, ir->operands[0], NULL);
   else
      op0 = new(ir) ir_expression(ir_unop_u2f, vec_type, ir->operands[0], NULL);

   vec_type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
				      ir->type->vector_elements,
				      ir->type->matrix_columns);

   op0 = new(ir) ir_expression(ir_binop_mul, vec_type, op0, op1);

   if (ir->operands[1]->type->base_type == GLSL_TYPE_INT) {
      ir->operation = ir_unop_f2i;
      ir->operands[0] = op0;
   } else {
      ir->operation = ir_unop_i2u;
      ir->operands[0] = new(ir) ir_expression(ir_unop_f2i, op0);
   }
   ir->operands[1] = NULL;

   this->progress = true;
}

void
lower_instructions_visitor::exp_to_exp2(ir_expression *ir)
{
   ir_constant *log2_e = new(ir) ir_constant(float(M_LOG2E));

   ir->operation = ir_unop_exp2;
   ir->operands[0] = new(ir) ir_expression(ir_binop_mul, ir->operands[0]->type,
					   ir->operands[0], log2_e);
   this->progress = true;
}

void
lower_instructions_visitor::pow_to_exp2(ir_expression *ir)
{
   ir_expression *const log2_x =
      new(ir) ir_expression(ir_unop_log2, ir->operands[0]->type,
			    ir->operands[0]);

   ir->operation = ir_unop_exp2;
   ir->operands[0] = new(ir) ir_expression(ir_binop_mul, ir->operands[1]->type,
					   ir->operands[1], log2_x);
   ir->operands[1] = NULL;
   this->progress = true;
}

void
lower_instructions_visitor::log_to_log2(ir_expression *ir)
{
   ir->operation = ir_binop_mul;
   ir->operands[0] = new(ir) ir_expression(ir_unop_log2, ir->operands[0]->type,
					   ir->operands[0], NULL);
   ir->operands[1] = new(ir) ir_constant(float(1.0 / M_LOG2E));
   this->progress = true;
}

void
lower_instructions_visitor::mod_to_fract(ir_expression *ir)
{
   ir_variable *temp = new(ir) ir_variable(ir->operands[1]->type, "mod_b",
					   ir_var_temporary, precision_from_ir(ir->operands[1]));
   this->base_ir->insert_before(temp);

   ir_assignment *const assign =
      new(ir) ir_assignment(new(ir) ir_dereference_variable(temp),
			    ir->operands[1], NULL);

   this->base_ir->insert_before(assign);

   ir_expression *const div_expr =
      new(ir) ir_expression(ir_binop_div, ir->operands[0]->type,
			    ir->operands[0],
			    new(ir) ir_dereference_variable(temp));

   /* Don't generate new IR that would need to be lowered in an additional
    * pass.
    */
   if (lowering(DIV_TO_MUL_RCP))
      div_to_mul_rcp(div_expr);

   ir_rvalue *expr = new(ir) ir_expression(ir_unop_fract,
					   ir->operands[0]->type,
					   div_expr,
					   NULL);

   ir->operation = ir_binop_mul;
   ir->operands[0] = new(ir) ir_dereference_variable(temp);
   ir->operands[1] = expr;
   this->progress = true;
}

void
lower_instructions_visitor::bitfield_insert_to_bfm_bfi(ir_expression *ir)
{
   /* Translates
    *    ir_quadop_bitfield_insert base insert offset bits
    * into
    *    ir_triop_bfi (ir_binop_bfm bits offset) insert base
    */

   ir_rvalue *base_expr = ir->operands[0];

   ir->operation = ir_triop_bfi;
   ir->operands[0] = new(ir) ir_expression(ir_binop_bfm,
                                           ir->type->get_base_type(),
                                           ir->operands[3],
                                           ir->operands[2]);
   /* ir->operands[1] is still the value to insert. */
   ir->operands[2] = base_expr;
   ir->operands[3] = NULL;

   this->progress = true;
}

void
lower_instructions_visitor::ldexp_to_arith(ir_expression *ir)
{
   /* Translates
    *    ir_binop_ldexp x exp
    * into
    *
    *    extracted_biased_exp = rshift(bitcast_f2i(abs(x)), exp_shift);
    *    resulting_biased_exp = extracted_biased_exp + exp;
    *
    *    if (resulting_biased_exp < 1) {
    *       return copysign(0.0, x);
    *    }
    *
    *    return bitcast_u2f((bitcast_f2u(x) & sign_mantissa_mask) |
    *                       lshift(i2u(resulting_biased_exp), exp_shift));
    *
    * which we can't actually implement as such, since the GLSL IR doesn't
    * have vectorized if-statements. We actually implement it without branches
    * using conditional-select:
    *
    *    extracted_biased_exp = rshift(bitcast_f2i(abs(x)), exp_shift);
    *    resulting_biased_exp = extracted_biased_exp + exp;
    *
    *    is_not_zero_or_underflow = gequal(resulting_biased_exp, 1);
    *    x = csel(is_not_zero_or_underflow, x, copysign(0.0f, x));
    *    resulting_biased_exp = csel(is_not_zero_or_underflow,
    *                                resulting_biased_exp, 0);
    *
    *    return bitcast_u2f((bitcast_f2u(x) & sign_mantissa_mask) |
    *                       lshift(i2u(resulting_biased_exp), exp_shift));
    */

   const unsigned vec_elem = ir->type->vector_elements;

   /* Types */
   const glsl_type *ivec = glsl_type::get_instance(GLSL_TYPE_INT, vec_elem, 1);
   const glsl_type *bvec = glsl_type::get_instance(GLSL_TYPE_BOOL, vec_elem, 1);

   /* Constants */
   ir_constant *zeroi = ir_constant::zero(ir, ivec);

   ir_constant *sign_mask = new(ir) ir_constant(0x80000000u, vec_elem);

   ir_constant *exp_shift = new(ir) ir_constant(23);
   ir_constant *exp_width = new(ir) ir_constant(8);

   /* Temporary variables */
   glsl_precision prec = ir->get_precision();
   ir_variable *x = new(ir) ir_variable(ir->type, "x", ir_var_temporary, prec);
   ir_variable *exp = new(ir) ir_variable(ivec, "exp", ir_var_temporary, prec);

   ir_variable *zero_sign_x = new(ir) ir_variable(ir->type, "zero_sign_x",
                                                  ir_var_temporary, prec);

   ir_variable *extracted_biased_exp =
      new(ir) ir_variable(ivec, "extracted_biased_exp", ir_var_temporary, prec);
   ir_variable *resulting_biased_exp =
      new(ir) ir_variable(ivec, "resulting_biased_exp", ir_var_temporary, prec);

   ir_variable *is_not_zero_or_underflow =
      new(ir) ir_variable(bvec, "is_not_zero_or_underflow", ir_var_temporary, prec);

   ir_instruction &i = *base_ir;

   /* Copy <x> and <exp> arguments. */
   i.insert_before(x);
   i.insert_before(assign(x, ir->operands[0]));
   i.insert_before(exp);
   i.insert_before(assign(exp, ir->operands[1]));

   /* Extract the biased exponent from <x>. */
   i.insert_before(extracted_biased_exp);
   i.insert_before(assign(extracted_biased_exp,
                          rshift(bitcast_f2i(abs(x)), exp_shift)));

   i.insert_before(resulting_biased_exp);
   i.insert_before(assign(resulting_biased_exp,
                          add(extracted_biased_exp, exp)));

   /* Test if result is ±0.0, subnormal, or underflow by checking if the
    * resulting biased exponent would be less than 0x1. If so, the result is
    * 0.0 with the sign of x. (Actually, invert the conditions so that
    * immediate values are the second arguments, which is better for i965)
    */
   i.insert_before(zero_sign_x);
   i.insert_before(assign(zero_sign_x,
                          bitcast_u2f(bit_and(bitcast_f2u(x), sign_mask))));

   i.insert_before(is_not_zero_or_underflow);
   i.insert_before(assign(is_not_zero_or_underflow,
                          gequal(resulting_biased_exp,
                                  new(ir) ir_constant(0x1, vec_elem))));
   i.insert_before(assign(x, csel(is_not_zero_or_underflow,
                                  x, zero_sign_x)));
   i.insert_before(assign(resulting_biased_exp,
                          csel(is_not_zero_or_underflow,
                               resulting_biased_exp, zeroi)));

   /* We could test for overflows by checking if the resulting biased exponent
    * would be greater than 0xFE. Turns out we don't need to because the GLSL
    * spec says:
    *
    *    "If this product is too large to be represented in the
    *     floating-point type, the result is undefined."
    */

   ir_constant *exp_shift_clone = exp_shift->clone(ir, NULL);
   ir->operation = ir_unop_bitcast_i2f;
   ir->operands[0] = bitfield_insert(bitcast_f2i(x), resulting_biased_exp,
                                     exp_shift_clone, exp_width);
   ir->operands[1] = NULL;

   /* Don't generate new IR that would need to be lowered in an additional
    * pass.
    */
   if (lowering(BITFIELD_INSERT_TO_BFM_BFI))
      bitfield_insert_to_bfm_bfi(ir->operands[0]->as_expression());

   this->progress = true;
}

void
lower_instructions_visitor::carry_to_arith(ir_expression *ir)
{
   /* Translates
    *   ir_binop_carry x y
    * into
    *   sum = ir_binop_add x y
    *   bcarry = ir_binop_less sum x
    *   carry = ir_unop_b2i bcarry
    */

   ir_rvalue *x_clone = ir->operands[0]->clone(ir, NULL);
   ir->operation = ir_unop_i2u;
   ir->operands[0] = b2i(less(add(ir->operands[0], ir->operands[1]), x_clone));
   ir->operands[1] = NULL;

   this->progress = true;
}

void
lower_instructions_visitor::borrow_to_arith(ir_expression *ir)
{
   /* Translates
    *   ir_binop_borrow x y
    * into
    *   bcarry = ir_binop_less x y
    *   carry = ir_unop_b2i bcarry
    */

   ir->operation = ir_unop_i2u;
   ir->operands[0] = b2i(less(ir->operands[0], ir->operands[1]));
   ir->operands[1] = NULL;

   this->progress = true;
}

void
lower_instructions_visitor::sat_to_clamp(ir_expression *ir)
{
   /* Translates
    *   ir_unop_saturate x
    * into
    *   ir_binop_min (ir_binop_max(x, 0.0), 1.0)
    */

   ir->operation = ir_binop_min;
   ir->operands[0] = new(ir) ir_expression(ir_binop_max, ir->operands[0]->type,
                                           ir->operands[0],
                                           new(ir) ir_constant(0.0f));
   ir->operands[1] = new(ir) ir_constant(1.0f);

   this->progress = true;
}

ir_visitor_status
lower_instructions_visitor::visit_leave(ir_expression *ir)
{
   switch (ir->operation) {
   case ir_binop_sub:
      if (lowering(SUB_TO_ADD_NEG))
	 sub_to_add_neg(ir);
      break;

   case ir_binop_div:
      if (ir->operands[1]->type->is_integer() && lowering(INT_DIV_TO_MUL_RCP))
	 int_div_to_mul_rcp(ir);
      else if (ir->operands[1]->type->is_float() && lowering(DIV_TO_MUL_RCP))
	 div_to_mul_rcp(ir);
      break;

   case ir_unop_exp:
      if (lowering(EXP_TO_EXP2))
	 exp_to_exp2(ir);
      break;

   case ir_unop_log:
      if (lowering(LOG_TO_LOG2))
	 log_to_log2(ir);
      break;

   case ir_binop_mod:
      if (lowering(MOD_TO_FRACT) && ir->type->is_float())
	 mod_to_fract(ir);
      break;

   case ir_binop_pow:
      if (lowering(POW_TO_EXP2))
	 pow_to_exp2(ir);
      break;

   case ir_quadop_bitfield_insert:
      if (lowering(BITFIELD_INSERT_TO_BFM_BFI))
         bitfield_insert_to_bfm_bfi(ir);
      break;

   case ir_binop_ldexp:
      if (lowering(LDEXP_TO_ARITH))
         ldexp_to_arith(ir);
      break;

   case ir_binop_carry:
      if (lowering(CARRY_TO_ARITH))
         carry_to_arith(ir);
      break;

   case ir_binop_borrow:
      if (lowering(BORROW_TO_ARITH))
         borrow_to_arith(ir);
      break;

   case ir_unop_saturate:
      if (lowering(SAT_TO_CLAMP))
         sat_to_clamp(ir);
      break;

   default:
      return visit_continue;
   }

   return visit_continue;
}

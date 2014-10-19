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
 * \file opt_algebraic.cpp
 *
 * Takes advantage of association, commutivity, and other algebraic
 * properties to simplify expressions.
 */

#include "ir.h"
#include "ir_visitor.h"
#include "ir_rvalue_visitor.h"
#include "ir_optimization.h"
#include "ir_builder.h"
#include "glsl_types.h"

using namespace ir_builder;

namespace {

/**
 * Visitor class for replacing expressions with ir_constant values.
 */

class ir_algebraic_visitor : public ir_rvalue_visitor {
public:
   ir_algebraic_visitor(bool native_integers,
                        const struct gl_shader_compiler_options *options)
      : options(options)
   {
      this->progress = false;
      this->mem_ctx = NULL;
      this->native_integers = native_integers;
   }

   virtual ~ir_algebraic_visitor()
   {
   }

   ir_rvalue *handle_expression(ir_expression *ir);
   void handle_rvalue(ir_rvalue **rvalue);
   bool reassociate_constant(ir_expression *ir1,
			     int const_index,
			     ir_constant *constant,
			     ir_expression *ir2);
   void reassociate_operands(ir_expression *ir1,
			     int op1,
			     ir_expression *ir2,
			     int op2);
   ir_rvalue *swizzle_if_required(ir_expression *expr,
				  ir_rvalue *operand);

   const struct gl_shader_compiler_options *options;
   void *mem_ctx;

   bool native_integers;
   bool progress;
};

} /* unnamed namespace */

static inline bool
is_vec_zero(ir_constant *ir)
{
   return (ir == NULL) ? false : ir->is_zero();
}

static inline bool
is_vec_one(ir_constant *ir)
{
   return (ir == NULL) ? false : ir->is_one();
}

static inline bool
is_vec_two(ir_constant *ir)
{
   return (ir == NULL) ? false : ir->is_value(2.0, 2);
}

static inline bool
is_vec_negative_one(ir_constant *ir)
{
   return (ir == NULL) ? false : ir->is_negative_one();
}

static inline bool
is_vec_basis(ir_constant *ir)
{
   return (ir == NULL) ? false : ir->is_basis();
}

static inline bool
is_valid_vec_const(ir_constant *ir)
{
   if (ir == NULL)
      return false;

   if (!ir->type->is_scalar() && !ir->type->is_vector())
      return false;

   return true;
}

static inline bool
is_less_than_one(ir_constant *ir)
{
   if (!is_valid_vec_const(ir))
      return false;

   unsigned component = 0;
   for (unsigned c = 0; c < ir->type->vector_elements; c++) {
      if (ir->get_float_component(c) < 1.0f)
         component++;
   }

   return (component == ir->type->vector_elements);
}

static inline bool
is_greater_than_zero(ir_constant *ir)
{
   if (!is_valid_vec_const(ir))
      return false;

   unsigned component = 0;
   for (unsigned c = 0; c < ir->type->vector_elements; c++) {
      if (ir->get_float_component(c) > 0.0f)
         component++;
   }

   return (component == ir->type->vector_elements);
}

static void
update_type(ir_expression *ir)
{
   if (ir->operands[0]->type->is_vector())
   {
      ir->type = ir->operands[0]->type;
	  ir->set_precision (ir->operands[0]->get_precision());
   }
   else
   {
      ir->type = ir->operands[1]->type;
	  ir->set_precision (ir->operands[1]->get_precision());
   }
}

/* Recognize (v.x + v.y) + (v.z + v.w) as dot(v, 1.0) */
static ir_expression *
try_replace_with_dot(ir_expression *expr0, ir_expression *expr1, void *mem_ctx)
{
   if (expr0 && expr0->operation == ir_binop_add &&
       expr0->type->is_float() &&
       expr1 && expr1->operation == ir_binop_add &&
       expr1->type->is_float()) {
      ir_swizzle *x = expr0->operands[0]->as_swizzle();
      ir_swizzle *y = expr0->operands[1]->as_swizzle();
      ir_swizzle *z = expr1->operands[0]->as_swizzle();
      ir_swizzle *w = expr1->operands[1]->as_swizzle();

      if (!x || x->mask.num_components != 1 ||
          !y || y->mask.num_components != 1 ||
          !z || z->mask.num_components != 1 ||
          !w || w->mask.num_components != 1) {
         return NULL;
      }

      bool swiz_seen[4] = {false, false, false, false};
      swiz_seen[x->mask.x] = true;
      swiz_seen[y->mask.x] = true;
      swiz_seen[z->mask.x] = true;
      swiz_seen[w->mask.x] = true;

      if (!swiz_seen[0] || !swiz_seen[1] ||
          !swiz_seen[2] || !swiz_seen[3]) {
         return NULL;
      }

      if (x->val->equals(y->val) &&
          x->val->equals(z->val) &&
          x->val->equals(w->val)) {
         return dot(x->val, new(mem_ctx) ir_constant(1.0f, 4));
      }
   }
   return NULL;
}

void
ir_algebraic_visitor::reassociate_operands(ir_expression *ir1,
					   int op1,
					   ir_expression *ir2,
					   int op2)
{
   ir_rvalue *temp = ir2->operands[op2];
   ir2->operands[op2] = ir1->operands[op1];
   ir1->operands[op1] = temp;

   /* Update the type of ir2.  The type of ir1 won't have changed --
    * base types matched, and at least one of the operands of the 2
    * binops is still a vector if any of them were.
    */
   update_type(ir2);

   this->progress = true;
}

/**
 * Reassociates a constant down a tree of adds or multiplies.
 *
 * Consider (2 * (a * (b * 0.5))).  We want to send up with a * b.
 */
bool
ir_algebraic_visitor::reassociate_constant(ir_expression *ir1, int const_index,
					   ir_constant *constant,
					   ir_expression *ir2)
{
   if (!ir2 || ir1->operation != ir2->operation)
      return false;

   /* Don't want to even think about matrices. */
   if (ir1->operands[0]->type->is_matrix() ||
       ir1->operands[1]->type->is_matrix() ||
       ir2->operands[0]->type->is_matrix() ||
       ir2->operands[1]->type->is_matrix())
      return false;

   ir_constant *ir2_const[2];
   ir2_const[0] = ir2->operands[0]->constant_expression_value();
   ir2_const[1] = ir2->operands[1]->constant_expression_value();

   if (ir2_const[0] && ir2_const[1])
      return false;

   if (ir2_const[0]) {
      reassociate_operands(ir1, const_index, ir2, 1);
      return true;
   } else if (ir2_const[1]) {
      reassociate_operands(ir1, const_index, ir2, 0);
      return true;
   }

   if (reassociate_constant(ir1, const_index, constant,
			    ir2->operands[0]->as_expression())) {
      update_type(ir2);
      return true;
   }

   if (reassociate_constant(ir1, const_index, constant,
			    ir2->operands[1]->as_expression())) {
      update_type(ir2);
      return true;
   }

   return false;
}

/* When eliminating an expression and just returning one of its operands,
 * we may need to swizzle that operand out to a vector if the expression was
 * vector type.
 */
ir_rvalue *
ir_algebraic_visitor::swizzle_if_required(ir_expression *expr,
					  ir_rvalue *operand)
{
   if (expr->type->is_vector() && operand->type->is_scalar()) {
      return new(mem_ctx) ir_swizzle(operand, 0, 0, 0, 0,
				     expr->type->vector_elements);
   } else
      return operand;
}

ir_rvalue *
ir_algebraic_visitor::handle_expression(ir_expression *ir)
{
   ir_constant *op_const[4] = {NULL, NULL, NULL, NULL};
   ir_expression *op_expr[4] = {NULL, NULL, NULL, NULL};
   unsigned int i;

   assert(ir->get_num_operands() <= 4);
   for (i = 0; i < ir->get_num_operands(); i++) {
      if (ir->operands[i]->type->is_matrix())
	 return ir;

      op_const[i] = ir->operands[i]->constant_expression_value();
      op_expr[i] = ir->operands[i]->as_expression();
   }

   if (this->mem_ctx == NULL)
      this->mem_ctx = ralloc_parent(ir);

   switch (ir->operation) {
   case ir_unop_bit_not:
      if (op_expr[0] && op_expr[0]->operation == ir_unop_bit_not)
         return op_expr[0]->operands[0];
      break;

   case ir_unop_abs:
      if (op_expr[0] == NULL)
	 break;

      switch (op_expr[0]->operation) {
      case ir_unop_abs:
      case ir_unop_neg:
         return abs(op_expr[0]->operands[0]);
      default:
         break;
      }
      break;

   case ir_unop_neg:
      if (op_expr[0] == NULL)
	 break;

      if (op_expr[0]->operation == ir_unop_neg) {
         return op_expr[0]->operands[0];
      }
	   if (op_expr[0] && op_expr[0]->operation == ir_binop_sub) {
		   // -(A-B) => (B-A)
		   this->progress = true;
		   return new(mem_ctx) ir_expression(ir_binop_sub,
											 ir->type,
											 op_expr[0]->operands[1],
											 op_expr[0]->operands[0]);
	   }
      break;

   case ir_unop_exp:
      if (op_expr[0] == NULL)
	 break;

      if (op_expr[0]->operation == ir_unop_log) {
         return op_expr[0]->operands[0];
      }
      break;

   case ir_unop_log:
      if (op_expr[0] == NULL)
	 break;

      if (op_expr[0]->operation == ir_unop_exp) {
         return op_expr[0]->operands[0];
      }
      break;

   case ir_unop_exp2:
      if (op_expr[0] == NULL)
	 break;

      if (op_expr[0]->operation == ir_unop_log2) {
         return op_expr[0]->operands[0];
      }

      if (!options->EmitNoPow && op_expr[0]->operation == ir_binop_mul) {
         for (int log2_pos = 0; log2_pos < 2; log2_pos++) {
            ir_expression *log2_expr =
               op_expr[0]->operands[log2_pos]->as_expression();

            if (log2_expr && log2_expr->operation == ir_unop_log2) {
               return new(mem_ctx) ir_expression(ir_binop_pow,
                                                 ir->type,
                                                 log2_expr->operands[0],
                                                 op_expr[0]->operands[1 - log2_pos]);
            }
         }
      }
      break;

   case ir_unop_log2:
      if (op_expr[0] == NULL)
	 break;

      if (op_expr[0]->operation == ir_unop_exp2) {
         return op_expr[0]->operands[0];
      }
      break;

   case ir_unop_logic_not: {
      enum ir_expression_operation new_op = ir_unop_logic_not;

      if (op_expr[0] == NULL)
	 break;

      switch (op_expr[0]->operation) {
      case ir_binop_less:    new_op = ir_binop_gequal;  break;
      case ir_binop_greater: new_op = ir_binop_lequal;  break;
      case ir_binop_lequal:  new_op = ir_binop_greater; break;
      case ir_binop_gequal:  new_op = ir_binop_less;    break;
      case ir_binop_equal:   new_op = ir_binop_nequal;  break;
      case ir_binop_nequal:  new_op = ir_binop_equal;   break;
      case ir_binop_all_equal:   new_op = ir_binop_any_nequal;  break;
      case ir_binop_any_nequal:  new_op = ir_binop_all_equal;   break;

      default:
	 /* The default case handler is here to silence a warning from GCC.
	  */
	 break;
      }

      if (new_op != ir_unop_logic_not) {
	 return new(mem_ctx) ir_expression(new_op,
					   ir->type,
					   op_expr[0]->operands[0],
					   op_expr[0]->operands[1]);
      }

      break;
   }

   case ir_binop_add:
      if (is_vec_zero(op_const[0]))
	 return ir->operands[1];
      if (is_vec_zero(op_const[1]))
	 return ir->operands[0];

      /* Reassociate addition of constants so that we can do constant
       * folding.
       */
      if (op_const[0] && !op_const[1])
	 reassociate_constant(ir, 0, op_const[0], op_expr[1]);
      if (op_const[1] && !op_const[0])
	 reassociate_constant(ir, 1, op_const[1], op_expr[0]);
		   
		// A + (-B) => A-B
	   if (op_expr[1] && op_expr[1]->operation == ir_unop_neg) {
		   this->progress = true;
		   return sub(ir->operands[0], op_expr[1]->operands[0]);
	   }

      /* Recognize (v.x + v.y) + (v.z + v.w) as dot(v, 1.0) */
      if (options->OptimizeForAOS) {
         ir_expression *expr = try_replace_with_dot(op_expr[0], op_expr[1],
                                                    mem_ctx);
         if (expr)
            return expr;
      }

      /* Replace (-x + y) * a + x and commutative variations with lrp(x, y, a).
       *
       * (-x + y) * a + x
       * (x * -a) + (y * a) + x
       * x + (x * -a) + (y * a)
       * x * (1 - a) + y * a
       * lrp(x, y, a)
       */
      for (int mul_pos = 0; mul_pos < 2; mul_pos++) {
         ir_expression *mul = op_expr[mul_pos];

         if (!mul || mul->operation != ir_binop_mul)
            continue;

         /* Multiply found on one of the operands. Now check for an
          * inner addition operation.
          */
         for (int inner_add_pos = 0; inner_add_pos < 2; inner_add_pos++) {
            ir_expression *inner_add =
               mul->operands[inner_add_pos]->as_expression();

            if (!inner_add || inner_add->operation != ir_binop_add)
               continue;

            /* Inner addition found on one of the operands. Now check for
             * one of the operands of the inner addition to be the negative
             * of x_operand.
             */
            for (int neg_pos = 0; neg_pos < 2; neg_pos++) {
               ir_expression *neg =
                  inner_add->operands[neg_pos]->as_expression();

               if (!neg || neg->operation != ir_unop_neg)
                  continue;

               ir_rvalue *x_operand = ir->operands[1 - mul_pos];

               if (!neg->operands[0]->equals(x_operand))
                  continue;

               ir_rvalue *y_operand = inner_add->operands[1 - neg_pos];
               ir_rvalue *a_operand = mul->operands[1 - inner_add_pos];

               if (x_operand->type != y_operand->type ||
                   x_operand->type != a_operand->type)
                  continue;

               return lrp(x_operand, y_operand, a_operand);
            }
         }
      }

      break;

   case ir_binop_sub:
      if (is_vec_zero(op_const[0]))
	 return neg(ir->operands[1]);
      if (is_vec_zero(op_const[1]))
	 return ir->operands[0];
      break;

   case ir_binop_mul:
      if (is_vec_one(op_const[0]))
	 return ir->operands[1];
      if (is_vec_one(op_const[1]))
	 return ir->operands[0];

      if (is_vec_zero(op_const[0]) || is_vec_zero(op_const[1]))
	 return ir_constant::zero(ir, ir->type);

      if (is_vec_negative_one(op_const[0]))
         return neg(ir->operands[1]);
      if (is_vec_negative_one(op_const[1]))
         return neg(ir->operands[0]);


      /* Reassociate multiplication of constants so that we can do
       * constant folding.
       */
      if (op_const[0] && !op_const[1])
	 reassociate_constant(ir, 0, op_const[0], op_expr[1]);
      if (op_const[1] && !op_const[0])
	 reassociate_constant(ir, 1, op_const[1], op_expr[0]);

      break;

   case ir_binop_div:
      if (is_vec_one(op_const[0]) && ir->type->base_type == GLSL_TYPE_FLOAT) {
	 return new(mem_ctx) ir_expression(ir_unop_rcp,
					   ir->operands[1]->type,
					   ir->operands[1],
					   NULL);
      }
      if (is_vec_one(op_const[1]))
	 return ir->operands[0];
      break;

   case ir_binop_dot:
      if (is_vec_zero(op_const[0]) || is_vec_zero(op_const[1]))
	 return ir_constant::zero(mem_ctx, ir->type);

      if (is_vec_basis(op_const[0])) {
	 unsigned component = 0;
	 for (unsigned c = 0; c < op_const[0]->type->vector_elements; c++) {
	    if (op_const[0]->value.f[c] == 1.0)
	       component = c;
	 }
	 return new(mem_ctx) ir_swizzle(ir->operands[1], component, 0, 0, 0, 1);
      }
      if (is_vec_basis(op_const[1])) {
	 unsigned component = 0;
	 for (unsigned c = 0; c < op_const[1]->type->vector_elements; c++) {
	    if (op_const[1]->value.f[c] == 1.0)
	       component = c;
	 }
	 return new(mem_ctx) ir_swizzle(ir->operands[0], component, 0, 0, 0, 1);
      }
      break;

   case ir_binop_less:
   case ir_binop_lequal:
   case ir_binop_greater:
   case ir_binop_gequal:
   case ir_binop_equal:
   case ir_binop_nequal:
      for (int add_pos = 0; add_pos < 2; add_pos++) {
         ir_expression *add = op_expr[add_pos];

         if (!add || add->operation != ir_binop_add)
            continue;

         ir_constant *zero = op_const[1 - add_pos];
         if (!is_vec_zero(zero))
            continue;

         return new(mem_ctx) ir_expression(ir->operation,
                                           add->operands[0],
                                           neg(add->operands[1]));
      }
      break;

   case ir_binop_rshift:
   case ir_binop_lshift:
      /* 0 >> x == 0 */
      if (is_vec_zero(op_const[0]))
         return ir->operands[0];
      /* x >> 0 == x */
      if (is_vec_zero(op_const[1]))
         return ir->operands[0];
      break;

   case ir_binop_logic_and:
      if (is_vec_one(op_const[0])) {
	 return ir->operands[1];
      } else if (is_vec_one(op_const[1])) {
	 return ir->operands[0];
      } else if (is_vec_zero(op_const[0]) || is_vec_zero(op_const[1])) {
	 return ir_constant::zero(mem_ctx, ir->type);
      } else if (op_expr[0] && op_expr[0]->operation == ir_unop_logic_not &&
                 op_expr[1] && op_expr[1]->operation == ir_unop_logic_not) {
         /* De Morgan's Law:
          *    (not A) and (not B) === not (A or B)
          */
         return logic_not(logic_or(op_expr[0]->operands[0],
                                   op_expr[1]->operands[0]));
      } else if (ir->operands[0]->equals(ir->operands[1])) {
         /* (a && a) == a */
         return ir->operands[0];
      }
      break;

   case ir_binop_logic_xor:
      if (is_vec_zero(op_const[0])) {
	 return ir->operands[1];
      } else if (is_vec_zero(op_const[1])) {
	 return ir->operands[0];
      } else if (is_vec_one(op_const[0])) {
	 return logic_not(ir->operands[1]);
      } else if (is_vec_one(op_const[1])) {
	 return logic_not(ir->operands[0]);
      } else if (ir->operands[0]->equals(ir->operands[1])) {
         /* (a ^^ a) == false */
	 return ir_constant::zero(mem_ctx, ir->type);
      }
      break;

   case ir_binop_logic_or:
      if (is_vec_zero(op_const[0])) {
	 return ir->operands[1];
      } else if (is_vec_zero(op_const[1])) {
	 return ir->operands[0];
      } else if (is_vec_one(op_const[0]) || is_vec_one(op_const[1])) {
	 ir_constant_data data;

	 for (unsigned i = 0; i < 16; i++)
	    data.b[i] = true;

	 return new(mem_ctx) ir_constant(ir->type, &data);
      } else if (op_expr[0] && op_expr[0]->operation == ir_unop_logic_not &&
                 op_expr[1] && op_expr[1]->operation == ir_unop_logic_not) {
         /* De Morgan's Law:
          *    (not A) or (not B) === not (A and B)
          */
         return logic_not(logic_and(op_expr[0]->operands[0],
                                    op_expr[1]->operands[0]));
      } else if (ir->operands[0]->equals(ir->operands[1])) {
         /* (a || a) == a */
         return ir->operands[0];
      }
      break;

   case ir_binop_pow:
      /* 1^x == 1 */
      if (is_vec_one(op_const[0]))
         return op_const[0];

      /* x^1 == x */
      if (is_vec_one(op_const[1]))
         return ir->operands[0];

      /* pow(2,x) == exp2(x) */
      if (is_vec_two(op_const[0]))
         return expr(ir_unop_exp2, ir->operands[1]);

      if (is_vec_two(op_const[1])) {
         ir_variable *x = new(ir) ir_variable(ir->operands[1]->type, "x",
                                              ir_var_temporary, ir->operands[1]->get_precision());
         base_ir->insert_before(x);
         base_ir->insert_before(assign(x, ir->operands[0]));
         return mul(x, x);
      }

      break;

   case ir_binop_min:
   case ir_binop_max:
      if (ir->type->base_type != GLSL_TYPE_FLOAT)
         break;

      /* Replace min(max) operations and its commutative combinations with
       * a saturate operation
       */
      for (int op = 0; op < 2; op++) {
         ir_expression *minmax = op_expr[op];
         ir_constant *outer_const = op_const[1 - op];
         ir_expression_operation op_cond = (ir->operation == ir_binop_max) ?
            ir_binop_min : ir_binop_max;

         if (!minmax || !outer_const || (minmax->operation != op_cond))
            continue;

         /* Found a min(max) combination. Now try to see if its operands
          * meet our conditions that we can do just a single saturate operation
          */
         for (int minmax_op = 0; minmax_op < 2; minmax_op++) {
            ir_rvalue *inner_val_a = minmax->operands[minmax_op];
            ir_rvalue *inner_val_b = minmax->operands[1 - minmax_op];

            if (!inner_val_a || !inner_val_b)
               continue;

            /* Found a {min|max} ({max|min} (x, 0.0), 1.0) operation and its variations */
            if ((outer_const->is_one() && inner_val_a->is_zero()) ||
                (inner_val_a->is_one() && outer_const->is_zero()))
               return saturate(inner_val_b);

            /* Found a {min|max} ({max|min} (x, 0.0), b) where b < 1.0
             * and its variations
             */
            if (is_less_than_one(outer_const) && inner_val_b->is_zero())
               return expr(ir_binop_min, saturate(inner_val_a), outer_const);

            if (!inner_val_b->as_constant())
               continue;

            if (is_less_than_one(inner_val_b->as_constant()) && outer_const->is_zero())
               return expr(ir_binop_min, saturate(inner_val_a), inner_val_b);

            /* Found a {min|max} ({max|min} (x, b), 1.0), where b > 0.0
             * and its variations
             */
            if (outer_const->is_one() && is_greater_than_zero(inner_val_b->as_constant()))
               return expr(ir_binop_max, saturate(inner_val_a), inner_val_b);
            if (inner_val_b->as_constant()->is_one() && is_greater_than_zero(outer_const))
               return expr(ir_binop_max, saturate(inner_val_a), outer_const);
         }
      }

      break;

   case ir_unop_rcp:
      if (op_expr[0] && op_expr[0]->operation == ir_unop_rcp)
	 return op_expr[0]->operands[0];

      /* While ir_to_mesa.cpp will lower sqrt(x) to rcp(rsq(x)), it does so at
       * its IR level, so we can always apply this transformation.
       */
      if (op_expr[0] && op_expr[0]->operation == ir_unop_rsq)
         return sqrt(op_expr[0]->operands[0]);

      /* As far as we know, all backends are OK with rsq. */
      if (op_expr[0] && op_expr[0]->operation == ir_unop_sqrt) {
	 return rsq(op_expr[0]->operands[0]);
      }

      break;

   case ir_triop_fma:
      /* Operands are op0 * op1 + op2. */
      if (is_vec_zero(op_const[0]) || is_vec_zero(op_const[1])) {
         return ir->operands[2];
      } else if (is_vec_zero(op_const[2])) {
         return mul(ir->operands[0], ir->operands[1]);
      } else if (is_vec_one(op_const[0])) {
         return add(ir->operands[1], ir->operands[2]);
      } else if (is_vec_one(op_const[1])) {
         return add(ir->operands[0], ir->operands[2]);
      }
      break;

   case ir_triop_lrp:
      /* Operands are (x, y, a). */
      if (is_vec_zero(op_const[2])) {
         return ir->operands[0];
      } else if (is_vec_one(op_const[2])) {
         return ir->operands[1];
      } else if (ir->operands[0]->equals(ir->operands[1])) {
         return ir->operands[0];
      } else if (is_vec_zero(op_const[0])) {
         return mul(ir->operands[1], ir->operands[2]);
      } else if (is_vec_zero(op_const[1])) {
         unsigned op2_components = ir->operands[2]->type->vector_elements;
         ir_constant *one = new(mem_ctx) ir_constant(1.0f, op2_components);
         return mul(ir->operands[0], add(one, neg(ir->operands[2])));
      }
      break;

   case ir_triop_csel:
      if (is_vec_one(op_const[0]))
	 return ir->operands[1];
      if (is_vec_zero(op_const[0]))
	 return ir->operands[2];
      break;

   default:
      break;
   }

   return ir;
}

void
ir_algebraic_visitor::handle_rvalue(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return;

   ir_expression *expr = (*rvalue)->as_expression();
   if (!expr || expr->operation == ir_quadop_vector)
      return;

   ir_rvalue *new_rvalue = handle_expression(expr);
   if (new_rvalue == *rvalue)
      return;

   /* If the expr used to be some vec OP scalar returning a vector, and the
    * optimization gave us back a scalar, we still need to turn it into a
    * vector.
    */
   *rvalue = swizzle_if_required(expr, new_rvalue);

   this->progress = true;
}

bool
do_algebraic(exec_list *instructions, bool native_integers,
             const struct gl_shader_compiler_options *options)
{
   ir_algebraic_visitor v(native_integers, options);

   visit_list_elements(&v, instructions);

   return v.progress;
}

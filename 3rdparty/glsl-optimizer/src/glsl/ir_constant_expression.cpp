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
 * \file ir_constant_expression.cpp
 * Evaluate and process constant valued expressions
 *
 * In GLSL, constant valued expressions are used in several places.  These
 * must be processed and evaluated very early in the compilation process.
 *
 *    * Sizes of arrays
 *    * Initializers for uniforms
 *    * Initializers for \c const variables
 */

#include <math.h>
#include "main/core.h" /* for MAX2, MIN2, CLAMP */
#include "ir.h"
#include "ir_visitor.h"
#include "glsl_types.h"
#include "program/hash_table.h"

/* Using C99 rounding functions for roundToEven() implementation is
 * difficult, because round(), rint, and nearbyint() are affected by
 * fesetenv(), which the application may have done for its own
 * purposes.  Mesa's IROUND macro is close to what we want, but it
 * rounds away from 0 on n + 0.5.
 */
static int
round_to_even(float val)
{
   int rounded = IROUND(val);

   if (val - floor(val) == 0.5) {
      if (rounded % 2 != 0)
	 rounded += val > 0 ? -1 : 1;
   }

   return rounded;
}

static float
dot(ir_constant *op0, ir_constant *op1)
{
   assert(op0->type->is_float() && op1->type->is_float());

   float result = 0;
   for (unsigned c = 0; c < op0->type->components(); c++)
      result += op0->value.f[c] * op1->value.f[c];

   return result;
}

/* This method is the only one supported by gcc.  Unions in particular
 * are iffy, and read-through-converted-pointer is killed by strict
 * aliasing.  OTOH, the compiler sees through the memcpy, so the
 * resulting asm is reasonable.
 */
static float
bitcast_u2f(unsigned int u)
{
   assert(sizeof(float) == sizeof(unsigned int));
   float f;
   memcpy(&f, &u, sizeof(f));
   return f;
}

static unsigned int
bitcast_f2u(float f)
{
   assert(sizeof(float) == sizeof(unsigned int));
   unsigned int u;
   memcpy(&u, &f, sizeof(f));
   return u;
}

ir_constant *
ir_rvalue::constant_expression_value(struct hash_table *variable_context)
{
   assert(this->type->is_error());
   return NULL;
}

ir_constant *
ir_expression::constant_expression_value(struct hash_table *variable_context)
{
   if (this->type->is_error())
      return NULL;

   ir_constant *op[Elements(this->operands)] = { NULL, };
   ir_constant_data data;

   memset(&data, 0, sizeof(data));

   for (unsigned operand = 0; operand < this->get_num_operands(); operand++) {
      op[operand] = this->operands[operand]->constant_expression_value(variable_context);
      if (!op[operand])
	 return NULL;
   }

   if (op[1] != NULL)
      assert(op[0]->type->base_type == op[1]->type->base_type ||
	     this->operation == ir_binop_lshift ||
	     this->operation == ir_binop_rshift);

   bool op0_scalar = op[0]->type->is_scalar();
   bool op1_scalar = op[1] != NULL && op[1]->type->is_scalar();

   /* When iterating over a vector or matrix's components, we want to increase
    * the loop counter.  However, for scalars, we want to stay at 0.
    */
   unsigned c0_inc = op0_scalar ? 0 : 1;
   unsigned c1_inc = op1_scalar ? 0 : 1;
   unsigned components;
   if (op1_scalar || !op[1]) {
      components = op[0]->type->components();
   } else {
      components = op[1]->type->components();
   }

   void *ctx = ralloc_parent(this);

   /* Handle array operations here, rather than below. */
   if (op[0]->type->is_array()) {
      assert(op[1] != NULL && op[1]->type->is_array());
      switch (this->operation) {
      case ir_binop_all_equal:
	 return new(ctx) ir_constant(op[0]->has_value(op[1]));
      case ir_binop_any_nequal:
	 return new(ctx) ir_constant(!op[0]->has_value(op[1]));
      default:
	 break;
      }
      return NULL;
   }

   switch (this->operation) {
   case ir_unop_bit_not:
       switch (op[0]->type->base_type) {
       case GLSL_TYPE_INT:
           for (unsigned c = 0; c < components; c++)
               data.i[c] = ~ op[0]->value.i[c];
           break;
       case GLSL_TYPE_UINT:
           for (unsigned c = 0; c < components; c++)
               data.u[c] = ~ op[0]->value.u[c];
           break;
       default:
           assert(0);
       }
       break;

   case ir_unop_logic_not:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++)
	 data.b[c] = !op[0]->value.b[c];
      break;

   case ir_unop_f2i:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.i[c] = (int) op[0]->value.f[c];
      }
      break;
   case ir_unop_f2u:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
         data.i[c] = (unsigned) op[0]->value.f[c];
      }
      break;
   case ir_unop_i2f:
      assert(op[0]->type->base_type == GLSL_TYPE_INT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = (float) op[0]->value.i[c];
      }
      break;
   case ir_unop_u2f:
      assert(op[0]->type->base_type == GLSL_TYPE_UINT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = (float) op[0]->value.u[c];
      }
      break;
   case ir_unop_b2f:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = op[0]->value.b[c] ? 1.0F : 0.0F;
      }
      break;
   case ir_unop_f2b:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.b[c] = op[0]->value.f[c] != 0.0F ? true : false;
      }
      break;
   case ir_unop_b2i:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.u[c] = op[0]->value.b[c] ? 1 : 0;
      }
      break;
   case ir_unop_i2b:
      assert(op[0]->type->is_integer());
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.b[c] = op[0]->value.u[c] ? true : false;
      }
      break;
   case ir_unop_u2i:
      assert(op[0]->type->base_type == GLSL_TYPE_UINT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.i[c] = op[0]->value.u[c];
      }
      break;
   case ir_unop_i2u:
      assert(op[0]->type->base_type == GLSL_TYPE_INT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.u[c] = op[0]->value.i[c];
      }
      break;
   case ir_unop_bitcast_i2f:
      assert(op[0]->type->base_type == GLSL_TYPE_INT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = bitcast_u2f(op[0]->value.i[c]);
      }
      break;
   case ir_unop_bitcast_f2i:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.i[c] = bitcast_f2u(op[0]->value.f[c]);
      }
      break;
   case ir_unop_bitcast_u2f:
      assert(op[0]->type->base_type == GLSL_TYPE_UINT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = bitcast_u2f(op[0]->value.u[c]);
      }
      break;
   case ir_unop_bitcast_f2u:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.u[c] = bitcast_f2u(op[0]->value.f[c]);
      }
      break;
   case ir_unop_any:
      assert(op[0]->type->is_boolean());
      data.b[0] = false;
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 if (op[0]->value.b[c])
	    data.b[0] = true;
      }
      break;

   case ir_unop_trunc:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = truncf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_round_even:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = round_to_even(op[0]->value.f[c]);
      }
      break;

   case ir_unop_ceil:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = ceilf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_floor:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = floorf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_fract:
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = 0;
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = 0;
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = op[0]->value.f[c] - floor(op[0]->value.f[c]);
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_unop_sin:
   case ir_unop_sin_reduced:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = sinf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_cos:
   case ir_unop_cos_reduced:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = cosf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_neg:
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = -((int) op[0]->value.u[c]);
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = -op[0]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = -op[0]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_unop_abs:
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = op[0]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = op[0]->value.i[c];
	    if (data.i[c] < 0)
	       data.i[c] = -data.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = fabs(op[0]->value.f[c]);
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_unop_sign:
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = op[0]->value.i[c] > 0;
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = (op[0]->value.i[c] > 0) - (op[0]->value.i[c] < 0);
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = float((op[0]->value.f[c] > 0)-(op[0]->value.f[c] < 0));
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_unop_rcp:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    if (op[0]->value.u[c] != 0.0)
	       data.u[c] = 1 / op[0]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    if (op[0]->value.i[c] != 0.0)
	       data.i[c] = 1 / op[0]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    if (op[0]->value.f[c] != 0.0)
	       data.f[c] = 1.0F / op[0]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_unop_rsq:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = 1.0F / sqrtf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_sqrt:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = sqrtf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_exp:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = expf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_exp2:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = exp2f(op[0]->value.f[c]);
      }
      break;

   case ir_unop_log:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = logf(op[0]->value.f[c]);
      }
      break;

   case ir_unop_log2:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = log2f(op[0]->value.f[c]);
      }
      break;

   case ir_unop_dFdx:
   case ir_unop_dFdy:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = 0.0;
      }
      break;

   case ir_binop_pow:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = powf(op[0]->value.f[c], op[1]->value.f[c]);
      }
      break;

   case ir_binop_dot:
      data.f[0] = dot(op[0], op[1]);
      break;

   case ir_binop_min:
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = MIN2(op[0]->value.u[c0], op[1]->value.u[c1]);
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = MIN2(op[0]->value.i[c0], op[1]->value.i[c1]);
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = MIN2(op[0]->value.f[c0], op[1]->value.f[c1]);
	    break;
	 default:
	    assert(0);
	 }
      }

      break;
   case ir_binop_max:
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = MAX2(op[0]->value.u[c0], op[1]->value.u[c1]);
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = MAX2(op[0]->value.i[c0], op[1]->value.i[c1]);
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = MAX2(op[0]->value.f[c0], op[1]->value.f[c1]);
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   case ir_binop_add:
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = op[0]->value.u[c0] + op[1]->value.u[c1];
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = op[0]->value.i[c0] + op[1]->value.i[c1];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = op[0]->value.f[c0] + op[1]->value.f[c1];
	    break;
	 default:
	    assert(0);
	 }
      }

      break;
   case ir_binop_sub:
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.u[c] = op[0]->value.u[c0] - op[1]->value.u[c1];
	    break;
	 case GLSL_TYPE_INT:
	    data.i[c] = op[0]->value.i[c0] - op[1]->value.i[c1];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = op[0]->value.f[c0] - op[1]->value.f[c1];
	    break;
	 default:
	    assert(0);
	 }
      }

      break;
   case ir_binop_mul:
      /* Check for equal types, or unequal types involving scalars */
      if ((op[0]->type == op[1]->type && !op[0]->type->is_matrix())
	  || op0_scalar || op1_scalar) {
	 for (unsigned c = 0, c0 = 0, c1 = 0;
	      c < components;
	      c0 += c0_inc, c1 += c1_inc, c++) {

	    switch (op[0]->type->base_type) {
	    case GLSL_TYPE_UINT:
	       data.u[c] = op[0]->value.u[c0] * op[1]->value.u[c1];
	       break;
	    case GLSL_TYPE_INT:
	       data.i[c] = op[0]->value.i[c0] * op[1]->value.i[c1];
	       break;
	    case GLSL_TYPE_FLOAT:
	       data.f[c] = op[0]->value.f[c0] * op[1]->value.f[c1];
	       break;
	    default:
	       assert(0);
	    }
	 }
      } else {
	 assert(op[0]->type->is_matrix() || op[1]->type->is_matrix());

	 /* Multiply an N-by-M matrix with an M-by-P matrix.  Since either
	  * matrix can be a GLSL vector, either N or P can be 1.
	  *
	  * For vec*mat, the vector is treated as a row vector.  This
	  * means the vector is a 1-row x M-column matrix.
	  *
	  * For mat*vec, the vector is treated as a column vector.  Since
	  * matrix_columns is 1 for vectors, this just works.
	  */
	 const unsigned n = op[0]->type->is_vector()
	    ? 1 : op[0]->type->vector_elements;
	 const unsigned m = op[1]->type->vector_elements;
	 const unsigned p = op[1]->type->matrix_columns;
	 for (unsigned j = 0; j < p; j++) {
	    for (unsigned i = 0; i < n; i++) {
	       for (unsigned k = 0; k < m; k++) {
		  data.f[i+n*j] += op[0]->value.f[i+n*k]*op[1]->value.f[k+m*j];
	       }
	    }
	 }
      }

      break;
   case ir_binop_div:
      /* FINISHME: Emit warning when division-by-zero is detected. */
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    if (op[1]->value.u[c1] == 0) {
	       data.u[c] = 0;
	    } else {
	       data.u[c] = op[0]->value.u[c0] / op[1]->value.u[c1];
	    }
	    break;
	 case GLSL_TYPE_INT:
	    if (op[1]->value.i[c1] == 0) {
	       data.i[c] = 0;
	    } else {
	       data.i[c] = op[0]->value.i[c0] / op[1]->value.i[c1];
	    }
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = op[0]->value.f[c0] / op[1]->value.f[c1];
	    break;
	 default:
	    assert(0);
	 }
      }

      break;
   case ir_binop_mod:
      /* FINISHME: Emit warning when division-by-zero is detected. */
      assert(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
      for (unsigned c = 0, c0 = 0, c1 = 0;
	   c < components;
	   c0 += c0_inc, c1 += c1_inc, c++) {

	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    if (op[1]->value.u[c1] == 0) {
	       data.u[c] = 0;
	    } else {
	       data.u[c] = op[0]->value.u[c0] % op[1]->value.u[c1];
	    }
	    break;
	 case GLSL_TYPE_INT:
	    if (op[1]->value.i[c1] == 0) {
	       data.i[c] = 0;
	    } else {
	       data.i[c] = op[0]->value.i[c0] % op[1]->value.i[c1];
	    }
	    break;
	 case GLSL_TYPE_FLOAT:
	    /* We don't use fmod because it rounds toward zero; GLSL specifies
	     * the use of floor.
	     */
	    data.f[c] = op[0]->value.f[c0] - op[1]->value.f[c1]
	       * floorf(op[0]->value.f[c0] / op[1]->value.f[c1]);
	    break;
	 default:
	    assert(0);
	 }
      }

      break;

   case ir_binop_logic_and:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++)
	 data.b[c] = op[0]->value.b[c] && op[1]->value.b[c];
      break;
   case ir_binop_logic_xor:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++)
	 data.b[c] = op[0]->value.b[c] ^ op[1]->value.b[c];
      break;
   case ir_binop_logic_or:
      assert(op[0]->type->base_type == GLSL_TYPE_BOOL);
      for (unsigned c = 0; c < op[0]->type->components(); c++)
	 data.b[c] = op[0]->value.b[c] || op[1]->value.b[c];
      break;

   case ir_binop_less:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] < op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] < op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] < op[1]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_greater:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] > op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] > op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] > op[1]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_lequal:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] <= op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] <= op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] <= op[1]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_gequal:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] >= op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] >= op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] >= op[1]->value.f[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_equal:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < components; c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] == op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] == op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] == op[1]->value.f[c];
	    break;
	 case GLSL_TYPE_BOOL:
	    data.b[c] = op[0]->value.b[c] == op[1]->value.b[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_nequal:
      assert(op[0]->type == op[1]->type);
      for (unsigned c = 0; c < components; c++) {
	 switch (op[0]->type->base_type) {
	 case GLSL_TYPE_UINT:
	    data.b[c] = op[0]->value.u[c] != op[1]->value.u[c];
	    break;
	 case GLSL_TYPE_INT:
	    data.b[c] = op[0]->value.i[c] != op[1]->value.i[c];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.b[c] = op[0]->value.f[c] != op[1]->value.f[c];
	    break;
	 case GLSL_TYPE_BOOL:
	    data.b[c] = op[0]->value.b[c] != op[1]->value.b[c];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;
   case ir_binop_all_equal:
      data.b[0] = op[0]->has_value(op[1]);
      break;
   case ir_binop_any_nequal:
      data.b[0] = !op[0]->has_value(op[1]);
      break;

   case ir_binop_lshift:
      for (unsigned c = 0, c0 = 0, c1 = 0;
           c < components;
           c0 += c0_inc, c1 += c1_inc, c++) {

          if (op[0]->type->base_type == GLSL_TYPE_INT &&
              op[1]->type->base_type == GLSL_TYPE_INT) {
              data.i[c] = op[0]->value.i[c0] << op[1]->value.i[c1];

          } else if (op[0]->type->base_type == GLSL_TYPE_INT &&
                     op[1]->type->base_type == GLSL_TYPE_UINT) {
              data.i[c] = op[0]->value.i[c0] << op[1]->value.u[c1];

          } else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
                     op[1]->type->base_type == GLSL_TYPE_INT) {
              data.u[c] = op[0]->value.u[c0] << op[1]->value.i[c1];

          } else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
                     op[1]->type->base_type == GLSL_TYPE_UINT) {
              data.u[c] = op[0]->value.u[c0] << op[1]->value.u[c1];
          }
      }
      break;

   case ir_binop_rshift:
       for (unsigned c = 0, c0 = 0, c1 = 0;
            c < components;
            c0 += c0_inc, c1 += c1_inc, c++) {

           if (op[0]->type->base_type == GLSL_TYPE_INT &&
               op[1]->type->base_type == GLSL_TYPE_INT) {
               data.i[c] = op[0]->value.i[c0] >> op[1]->value.i[c1];

           } else if (op[0]->type->base_type == GLSL_TYPE_INT &&
                      op[1]->type->base_type == GLSL_TYPE_UINT) {
               data.i[c] = op[0]->value.i[c0] >> op[1]->value.u[c1];

           } else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
                      op[1]->type->base_type == GLSL_TYPE_INT) {
               data.u[c] = op[0]->value.u[c0] >> op[1]->value.i[c1];

           } else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
                      op[1]->type->base_type == GLSL_TYPE_UINT) {
               data.u[c] = op[0]->value.u[c0] >> op[1]->value.u[c1];
           }
       }
       break;

   case ir_binop_bit_and:
      for (unsigned c = 0, c0 = 0, c1 = 0;
           c < components;
           c0 += c0_inc, c1 += c1_inc, c++) {

          switch (op[0]->type->base_type) {
          case GLSL_TYPE_INT:
              data.i[c] = op[0]->value.i[c0] & op[1]->value.i[c1];
              break;
          case GLSL_TYPE_UINT:
              data.u[c] = op[0]->value.u[c0] & op[1]->value.u[c1];
              break;
          default:
              assert(0);
          }
      }
      break;

   case ir_binop_bit_or:
      for (unsigned c = 0, c0 = 0, c1 = 0;
           c < components;
           c0 += c0_inc, c1 += c1_inc, c++) {

          switch (op[0]->type->base_type) {
          case GLSL_TYPE_INT:
              data.i[c] = op[0]->value.i[c0] | op[1]->value.i[c1];
              break;
          case GLSL_TYPE_UINT:
              data.u[c] = op[0]->value.u[c0] | op[1]->value.u[c1];
              break;
          default:
              assert(0);
          }
      }
      break;

   case ir_binop_bit_xor:
      for (unsigned c = 0, c0 = 0, c1 = 0;
           c < components;
           c0 += c0_inc, c1 += c1_inc, c++) {

          switch (op[0]->type->base_type) {
          case GLSL_TYPE_INT:
              data.i[c] = op[0]->value.i[c0] ^ op[1]->value.i[c1];
              break;
          case GLSL_TYPE_UINT:
              data.u[c] = op[0]->value.u[c0] ^ op[1]->value.u[c1];
              break;
          default:
              assert(0);
          }
      }
      break;

   case ir_quadop_vector:
      for (unsigned c = 0; c < this->type->vector_elements; c++) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_INT:
	    data.i[c] = op[c]->value.i[0];
	    break;
	 case GLSL_TYPE_UINT:
	    data.u[c] = op[c]->value.u[0];
	    break;
	 case GLSL_TYPE_FLOAT:
	    data.f[c] = op[c]->value.f[0];
	    break;
	 default:
	    assert(0);
	 }
      }
      break;

   default:
      /* FINISHME: Should handle all expression types. */
      return NULL;
   }

   return new(ctx) ir_constant(this->type, &data);
}


ir_constant *
ir_texture::constant_expression_value(struct hash_table *variable_context)
{
   /* texture lookups aren't constant expressions */
   return NULL;
}


ir_constant *
ir_swizzle::constant_expression_value(struct hash_table *variable_context)
{
   ir_constant *v = this->val->constant_expression_value(variable_context);

   if (v != NULL) {
      ir_constant_data data = { { 0 } };

      const unsigned swiz_idx[4] = {
	 this->mask.x, this->mask.y, this->mask.z, this->mask.w
      };

      for (unsigned i = 0; i < this->mask.num_components; i++) {
	 switch (v->type->base_type) {
	 case GLSL_TYPE_UINT:
	 case GLSL_TYPE_INT:   data.u[i] = v->value.u[swiz_idx[i]]; break;
	 case GLSL_TYPE_FLOAT: data.f[i] = v->value.f[swiz_idx[i]]; break;
	 case GLSL_TYPE_BOOL:  data.b[i] = v->value.b[swiz_idx[i]]; break;
	 default:              assert(!"Should not get here."); break;
	 }
      }

      void *ctx = ralloc_parent(this);
      return new(ctx) ir_constant(this->type, &data);
   }
   return NULL;
}


void
ir_dereference_variable::constant_referenced(struct hash_table *variable_context,
					     ir_constant *&store, int &offset) const
{
   if (variable_context) {
      store = (ir_constant *)hash_table_find(variable_context, var);
      offset = 0;
   } else {
      store = NULL;
      offset = 0;
   }
}

ir_constant *
ir_dereference_variable::constant_expression_value(struct hash_table *variable_context)
{
   /* This may occur during compile and var->type is glsl_type::error_type */
   if (!var)
      return NULL;

   /* Give priority to the context hashtable, if it exists */
   if (variable_context) {
      ir_constant *value = (ir_constant *)hash_table_find(variable_context, var);
      if(value)
	 return value;
   }

   /* The constant_value of a uniform variable is its initializer,
    * not the lifetime constant value of the uniform.
    */
   if (var->mode == ir_var_uniform)
      return NULL;

   if (!var->constant_value)
      return NULL;

   return var->constant_value->clone(ralloc_parent(var), NULL);
}


void
ir_dereference_array::constant_referenced(struct hash_table *variable_context,
					  ir_constant *&store, int &offset) const
{
   ir_constant *index_c = array_index->constant_expression_value(variable_context);

   if (!index_c || !index_c->type->is_scalar() || !index_c->type->is_integer()) {
      store = 0;
      offset = 0;
      return;
   }

   int index = index_c->type->base_type == GLSL_TYPE_INT ?
      index_c->get_int_component(0) :
      index_c->get_uint_component(0);

   ir_constant *substore;
   int suboffset;
   const ir_dereference *deref = array->as_dereference();
   if (!deref) {
      store = 0;
      offset = 0;
      return;
   }

   deref->constant_referenced(variable_context, substore, suboffset);

   if (!substore) {
      store = 0;
      offset = 0;
      return;
   }

   const glsl_type *vt = substore->type;
   if (vt->is_array()) {
      store = substore->get_array_element(index);
      offset = 0;
      return;
   }
   if (vt->is_matrix()) {
      store = substore;
      offset = index * vt->vector_elements;
      return;
   }
   if (vt->is_vector()) {
      store = substore;
      offset = suboffset + index;
      return;
   }

   store = 0;
   offset = 0;
}

ir_constant *
ir_dereference_array::constant_expression_value(struct hash_table *variable_context)
{
   ir_constant *array = this->array->constant_expression_value(variable_context);
   ir_constant *idx = this->array_index->constant_expression_value(variable_context);

   if ((array != NULL) && (idx != NULL)) {
      void *ctx = ralloc_parent(this);
      if (array->type->is_matrix()) {
	 /* Array access of a matrix results in a vector.
	  */
	 const unsigned column = idx->value.u[0];

	 const glsl_type *const column_type = array->type->column_type();

	 /* Offset in the constant matrix to the first element of the column
	  * to be extracted.
	  */
	 const unsigned mat_idx = column * column_type->vector_elements;

	 ir_constant_data data = { { 0 } };

	 switch (column_type->base_type) {
	 case GLSL_TYPE_UINT:
	 case GLSL_TYPE_INT:
	    for (unsigned i = 0; i < column_type->vector_elements; i++)
	       data.u[i] = array->value.u[mat_idx + i];

	    break;

	 case GLSL_TYPE_FLOAT:
	    for (unsigned i = 0; i < column_type->vector_elements; i++)
	       data.f[i] = array->value.f[mat_idx + i];

	    break;

	 default:
	    assert(!"Should not get here.");
	    break;
	 }

	 return new(ctx) ir_constant(column_type, &data);
      } else if (array->type->is_vector()) {
	 const unsigned component = idx->value.u[0];

	 return new(ctx) ir_constant(array, component);
      } else {
	 const unsigned index = idx->value.u[0];
	 return array->get_array_element(index)->clone(ctx, NULL);
      }
   }
   return NULL;
}


void
ir_dereference_record::constant_referenced(struct hash_table *variable_context,
					   ir_constant *&store, int &offset) const
{
   ir_constant *substore;
   int suboffset;
   const ir_dereference *deref = record->as_dereference();
   if (!deref) {
      store = 0;
      offset = 0;
      return;
   }

   deref->constant_referenced(variable_context, substore, suboffset);

   if (!substore) {
      store = 0;
      offset = 0;
      return;
   }

   store = substore->get_record_field(field);
   offset = 0;
}

ir_constant *
ir_dereference_record::constant_expression_value(struct hash_table *variable_context)
{
   ir_constant *v = this->record->constant_expression_value();

   return (v != NULL) ? v->get_record_field(this->field) : NULL;
}


ir_constant *
ir_assignment::constant_expression_value(struct hash_table *variable_context)
{
   /* FINISHME: Handle CEs involving assignment (return RHS) */
   return NULL;
}


ir_constant *
ir_constant::constant_expression_value(struct hash_table *variable_context)
{
   return this;
}


ir_constant *
ir_call::constant_expression_value(struct hash_table *variable_context)
{
   return this->callee->constant_expression_value(&this->actual_parameters, variable_context);
}


bool ir_function_signature::constant_expression_evaluate_expression_list(const struct exec_list &body,
									 struct hash_table *variable_context,
									 ir_constant **result)
{
   foreach_list(n, &body) {
      ir_instruction *inst = (ir_instruction *)n;
      switch(inst->ir_type) {

	 /* (declare () type symbol) */
      case ir_type_variable: {
	 ir_variable *var = inst->as_variable();
	 hash_table_insert(variable_context, ir_constant::zero(this, var->type), var);
	 break;
      }

	 /* (assign [condition] (write-mask) (ref) (value)) */
      case ir_type_assignment: {
	 ir_assignment *asg = inst->as_assignment();
	 if (asg->condition) {
	    ir_constant *cond = asg->condition->constant_expression_value(variable_context);
	    if (!cond)
	       return false;
	    if (!cond->get_bool_component(0))
	       break;
	 }

	 ir_constant *store = NULL;
	 int offset = 0;
	 asg->lhs->constant_referenced(variable_context, store, offset);

	 if (!store)
	    return false;

	 ir_constant *value = asg->rhs->constant_expression_value(variable_context);

	 if (!value)
	    return false;

	 store->copy_masked_offset(value, offset, asg->write_mask);
	 break;
      }

	 /* (return (expression)) */
      case ir_type_return:
	 assert (result);
	 *result = inst->as_return()->value->constant_expression_value(variable_context);
	 return *result != NULL;

	 /* (call name (ref) (params))*/
      case ir_type_call: {
	 ir_call *call = inst->as_call();

	 /* Just say no to void functions in constant expressions.  We
	  * don't need them at that point.
	  */

	 if (!call->return_deref)
	    return false;

	 ir_constant *store = NULL;
	 int offset = 0;
	 call->return_deref->constant_referenced(variable_context, store, offset);

	 if (!store)
	    return false;

	 ir_constant *value = call->constant_expression_value(variable_context);

	 if(!value)
	    return false;

	 store->copy_offset(value, offset);
	 break;
      }

	 /* (if condition (then-instructions) (else-instructions)) */
      case ir_type_if: {
	 ir_if *iif = inst->as_if();

	 ir_constant *cond = iif->condition->constant_expression_value(variable_context);
	 if (!cond || !cond->type->is_boolean())
	    return false;

	 exec_list &branch = cond->get_bool_component(0) ? iif->then_instructions : iif->else_instructions;

	 *result = NULL;
	 if (!constant_expression_evaluate_expression_list(branch, variable_context, result))
	    return false;

	 /* If there was a return in the branch chosen, drop out now. */
	 if (*result)
	    return true;

	 break;
      }

	 /* Every other expression type, we drop out. */
      default:
	 return false;
      }
   }

   /* Reaching the end of the block is not an error condition */
   if (result)
      *result = NULL;

   return true;
}

ir_constant *
ir_function_signature::constant_expression_value(exec_list *actual_parameters, struct hash_table *variable_context)
{
   const glsl_type *type = this->return_type;
   if (type == glsl_type::void_type)
      return NULL;

   /* From the GLSL 1.20 spec, page 23:
    * "Function calls to user-defined functions (non-built-in functions)
    *  cannot be used to form constant expressions."
    */
   if (!this->is_builtin)
      return NULL;

   /*
    * Of the builtin functions, only the texture lookups and the noise
    * ones must not be used in constant expressions.  They all include
    * specific opcodes so they don't need to be special-cased at this
    * point.
    */

   /* Initialize the table of dereferencable names with the function
    * parameters.  Verify their const-ness on the way.
    *
    * We expect the correctness of the number of parameters to have
    * been checked earlier.
    */
   hash_table *deref_hash = hash_table_ctor(8, hash_table_pointer_hash,
					    hash_table_pointer_compare);

   /* If "origin" is non-NULL, then the function body is there.  So we
    * have to use the variable objects from the object with the body,
    * but the parameter instanciation on the current object.
    */
   const exec_node *parameter_info = origin ? origin->parameters.head : parameters.head;

   foreach_list(n, actual_parameters) {
      ir_constant *constant = ((ir_rvalue *) n)->constant_expression_value(variable_context);
      if (constant == NULL) {
         hash_table_dtor(deref_hash);
         return NULL;
      }


      ir_variable *var = (ir_variable *)parameter_info;
      hash_table_insert(deref_hash, constant, var);

      parameter_info = parameter_info->next;
   }

   ir_constant *result = NULL;

   /* Now run the builtin function until something non-constant
    * happens or we get the result.
    */
   if (constant_expression_evaluate_expression_list(origin ? origin->body : body, deref_hash, &result) && result)
      result = result->clone(ralloc_parent(this), NULL);

   hash_table_dtor(deref_hash);

   return result;
}

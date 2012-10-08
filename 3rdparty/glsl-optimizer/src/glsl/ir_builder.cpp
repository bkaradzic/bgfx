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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "ir_builder.h"
#include "program/prog_instruction.h"

using namespace ir_builder;

namespace ir_builder {

void
ir_factory::emit(ir_instruction *ir)
{
   instructions->push_tail(ir);
}

ir_variable *
ir_factory::make_temp(const glsl_type *type, const char *name)
{
   ir_variable *var;

   var = new(mem_ctx) ir_variable(type, name, ir_var_temporary, glsl_precision_undefined);
   emit(var);

   return var;
}

ir_assignment *
assign(deref lhs, operand rhs, int writemask)
{
   void *mem_ctx = ralloc_parent(lhs.val);

   ir_assignment *assign = new(mem_ctx) ir_assignment(lhs.val,
						      rhs.val,
						      NULL, writemask);

   return assign;
}

ir_assignment *
assign(deref lhs, operand rhs)
{
   return assign(lhs, rhs, (1 << lhs.val->type->vector_elements) - 1);
}

ir_swizzle *
swizzle(operand a, int swizzle, int components)
{
   void *mem_ctx = ralloc_parent(a.val);

   return new(mem_ctx) ir_swizzle(a.val,
				  GET_SWZ(swizzle, 0),
				  GET_SWZ(swizzle, 1),
				  GET_SWZ(swizzle, 2),
				  GET_SWZ(swizzle, 3),
				  components);
}

ir_swizzle *
swizzle_for_size(operand a, int components)
{
   void *mem_ctx = ralloc_parent(a.val);

   if (a.val->type->vector_elements < components)
      components = a.val->type->vector_elements;

   unsigned s[4] = { 0, 1, 2, 3 };
   for (int i = components; i < 4; i++)
      s[i] = components - 1;

   return new(mem_ctx) ir_swizzle(a.val, s, components);
}

ir_swizzle *
swizzle_xxxx(operand a)
{
   return swizzle(a, SWIZZLE_XXXX, 4);
}

ir_swizzle *
swizzle_yyyy(operand a)
{
   return swizzle(a, SWIZZLE_YYYY, 4);
}

ir_swizzle *
swizzle_zzzz(operand a)
{
   return swizzle(a, SWIZZLE_ZZZZ, 4);
}

ir_swizzle *
swizzle_wwww(operand a)
{
   return swizzle(a, SWIZZLE_WWWW, 4);
}

ir_swizzle *
swizzle_x(operand a)
{
   return swizzle(a, SWIZZLE_XXXX, 1);
}

ir_swizzle *
swizzle_y(operand a)
{
   return swizzle(a, SWIZZLE_YYYY, 1);
}

ir_swizzle *
swizzle_z(operand a)
{
   return swizzle(a, SWIZZLE_ZZZZ, 1);
}

ir_swizzle *
swizzle_w(operand a)
{
   return swizzle(a, SWIZZLE_WWWW, 1);
}

ir_swizzle *
swizzle_xy(operand a)
{
   return swizzle(a, SWIZZLE_XYZW, 2);
}

ir_swizzle *
swizzle_xyz(operand a)
{
   return swizzle(a, SWIZZLE_XYZW, 3);
}

ir_swizzle *
swizzle_xyzw(operand a)
{
   return swizzle(a, SWIZZLE_XYZW, 4);
}

ir_expression *
expr(ir_expression_operation op, operand a)
{
   void *mem_ctx = ralloc_parent(a.val);

   return new(mem_ctx) ir_expression(op, a.val);
}

ir_expression *
expr(ir_expression_operation op, operand a, operand b)
{
   void *mem_ctx = ralloc_parent(a.val);

   return new(mem_ctx) ir_expression(op, a.val, b.val);
}

ir_expression *add(operand a, operand b)
{
   return expr(ir_binop_add, a, b);
}

ir_expression *sub(operand a, operand b)
{
   return expr(ir_binop_sub, a, b);
}

ir_expression *mul(operand a, operand b)
{
   return expr(ir_binop_mul, a, b);
}

ir_expression *dot(operand a, operand b)
{
   return expr(ir_binop_dot, a, b);
}

ir_expression *
saturate(operand a)
{
   void *mem_ctx = ralloc_parent(a.val);

   return expr(ir_binop_max,
	       expr(ir_binop_min, a, new(mem_ctx) ir_constant(1.0f)),
	       new(mem_ctx) ir_constant(0.0f));
}

} /* namespace ir_builder */

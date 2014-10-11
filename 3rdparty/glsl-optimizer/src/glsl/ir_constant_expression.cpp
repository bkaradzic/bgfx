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
#include "glsl_types.h"
#include "program/hash_table.h"

#if defined(_MSC_VER) && (_MSC_VER < 1800)
static int isnormal(double x)
{
   return _fpclass(x) == _FPCLASS_NN || _fpclass(x) == _FPCLASS_PN;
}
#elif defined(__SUNPRO_CC)
#include <ieeefp.h>
static int isnormal(double x)
{
   return fpclass(x) == FP_NORMAL;
}
#endif

#if defined(_MSC_VER) && _MSC_VER < 1800
static double copysign(double x, double y)
{
   return _copysign(x, y);
}
#endif

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

/**
 * Evaluate one component of a floating-point 4x8 unpacking function.
 */
typedef uint8_t
(*pack_1x8_func_t)(float);

/**
 * Evaluate one component of a floating-point 2x16 unpacking function.
 */
typedef uint16_t
(*pack_1x16_func_t)(float);

/**
 * Evaluate one component of a floating-point 4x8 unpacking function.
 */
typedef float
(*unpack_1x8_func_t)(uint8_t);

/**
 * Evaluate one component of a floating-point 2x16 unpacking function.
 */
typedef float
(*unpack_1x16_func_t)(uint16_t);

/**
 * Evaluate a 2x16 floating-point packing function.
 */
static uint32_t
pack_2x16(pack_1x16_func_t pack_1x16,
          float x, float y)
{
   /* From section 8.4 of the GLSL ES 3.00 spec:
    *
    *    packSnorm2x16
    *    -------------
    *    The first component of the vector will be written to the least
    *    significant bits of the output; the last component will be written to
    *    the most significant bits.
    *
    * The specifications for the other packing functions contain similar
    * language.
    */
   uint32_t u = 0;
   u |= ((uint32_t) pack_1x16(x) << 0);
   u |= ((uint32_t) pack_1x16(y) << 16);
   return u;
}

/**
 * Evaluate a 4x8 floating-point packing function.
 */
static uint32_t
pack_4x8(pack_1x8_func_t pack_1x8,
         float x, float y, float z, float w)
{
   /* From section 8.4 of the GLSL 4.30 spec:
    *
    *    packSnorm4x8
    *    ------------
    *    The first component of the vector will be written to the least
    *    significant bits of the output; the last component will be written to
    *    the most significant bits.
    *
    * The specifications for the other packing functions contain similar
    * language.
    */
   uint32_t u = 0;
   u |= ((uint32_t) pack_1x8(x) << 0);
   u |= ((uint32_t) pack_1x8(y) << 8);
   u |= ((uint32_t) pack_1x8(z) << 16);
   u |= ((uint32_t) pack_1x8(w) << 24);
   return u;
}

/**
 * Evaluate a 2x16 floating-point unpacking function.
 */
static void
unpack_2x16(unpack_1x16_func_t unpack_1x16,
            uint32_t u,
            float *x, float *y)
{
    /* From section 8.4 of the GLSL ES 3.00 spec:
     *
     *    unpackSnorm2x16
     *    ---------------
     *    The first component of the returned vector will be extracted from
     *    the least significant bits of the input; the last component will be
     *    extracted from the most significant bits.
     *
     * The specifications for the other unpacking functions contain similar
     * language.
     */
   *x = unpack_1x16((uint16_t) (u & 0xffff));
   *y = unpack_1x16((uint16_t) (u >> 16));
}

/**
 * Evaluate a 4x8 floating-point unpacking function.
 */
static void
unpack_4x8(unpack_1x8_func_t unpack_1x8, uint32_t u,
           float *x, float *y, float *z, float *w)
{
    /* From section 8.4 of the GLSL 4.30 spec:
     *
     *    unpackSnorm4x8
     *    --------------
     *    The first component of the returned vector will be extracted from
     *    the least significant bits of the input; the last component will be
     *    extracted from the most significant bits.
     *
     * The specifications for the other unpacking functions contain similar
     * language.
     */
   *x = unpack_1x8((uint8_t) (u & 0xff));
   *y = unpack_1x8((uint8_t) (u >> 8));
   *z = unpack_1x8((uint8_t) (u >> 16));
   *w = unpack_1x8((uint8_t) (u >> 24));
}

/**
 * Evaluate one component of packSnorm4x8.
 */
static uint8_t
pack_snorm_1x8(float x)
{
    /* From section 8.4 of the GLSL 4.30 spec:
     *
     *    packSnorm4x8
     *    ------------
     *    The conversion for component c of v to fixed point is done as
     *    follows:
     *
     *      packSnorm4x8: round(clamp(c, -1, +1) * 127.0)
     *
     * We must first cast the float to an int, because casting a negative
     * float to a uint is undefined.
     */
   return (uint8_t) (int8_t)
          _mesa_round_to_even(CLAMP(x, -1.0f, +1.0f) * 127.0f);
}

/**
 * Evaluate one component of packSnorm2x16.
 */
static uint16_t
pack_snorm_1x16(float x)
{
    /* From section 8.4 of the GLSL ES 3.00 spec:
     *
     *    packSnorm2x16
     *    -------------
     *    The conversion for component c of v to fixed point is done as
     *    follows:
     *
     *      packSnorm2x16: round(clamp(c, -1, +1) * 32767.0)
     *
     * We must first cast the float to an int, because casting a negative
     * float to a uint is undefined.
     */
   return (uint16_t) (int16_t)
          _mesa_round_to_even(CLAMP(x, -1.0f, +1.0f) * 32767.0f);
}

/**
 * Evaluate one component of unpackSnorm4x8.
 */
static float
unpack_snorm_1x8(uint8_t u)
{
    /* From section 8.4 of the GLSL 4.30 spec:
     *
     *    unpackSnorm4x8
     *    --------------
     *    The conversion for unpacked fixed-point value f to floating point is
     *    done as follows:
     *
     *       unpackSnorm4x8: clamp(f / 127.0, -1, +1)
     */
   return CLAMP((int8_t) u / 127.0f, -1.0f, +1.0f);
}

/**
 * Evaluate one component of unpackSnorm2x16.
 */
static float
unpack_snorm_1x16(uint16_t u)
{
    /* From section 8.4 of the GLSL ES 3.00 spec:
     *
     *    unpackSnorm2x16
     *    ---------------
     *    The conversion for unpacked fixed-point value f to floating point is
     *    done as follows:
     *
     *       unpackSnorm2x16: clamp(f / 32767.0, -1, +1)
     */
   return CLAMP((int16_t) u / 32767.0f, -1.0f, +1.0f);
}

/**
 * Evaluate one component packUnorm4x8.
 */
static uint8_t
pack_unorm_1x8(float x)
{
    /* From section 8.4 of the GLSL 4.30 spec:
     *
     *    packUnorm4x8
     *    ------------
     *    The conversion for component c of v to fixed point is done as
     *    follows:
     *
     *       packUnorm4x8: round(clamp(c, 0, +1) * 255.0)
     */
   return (uint8_t) _mesa_round_to_even(CLAMP(x, 0.0f, 1.0f) * 255.0f);
}

/**
 * Evaluate one component packUnorm2x16.
 */
static uint16_t
pack_unorm_1x16(float x)
{
    /* From section 8.4 of the GLSL ES 3.00 spec:
     *
     *    packUnorm2x16
     *    -------------
     *    The conversion for component c of v to fixed point is done as
     *    follows:
     *
     *       packUnorm2x16: round(clamp(c, 0, +1) * 65535.0)
     */
   return (uint16_t) _mesa_round_to_even(CLAMP(x, 0.0f, 1.0f) * 65535.0f);
}

/**
 * Evaluate one component of unpackUnorm4x8.
 */
static float
unpack_unorm_1x8(uint8_t u)
{
    /* From section 8.4 of the GLSL 4.30 spec:
     *
     *    unpackUnorm4x8
     *    --------------
     *    The conversion for unpacked fixed-point value f to floating point is
     *    done as follows:
     *
     *       unpackUnorm4x8: f / 255.0
     */
   return (float) u / 255.0f;
}

/**
 * Evaluate one component of unpackUnorm2x16.
 */
static float
unpack_unorm_1x16(uint16_t u)
{
    /* From section 8.4 of the GLSL ES 3.00 spec:
     *
     *    unpackUnorm2x16
     *    ---------------
     *    The conversion for unpacked fixed-point value f to floating point is
     *    done as follows:
     *
     *       unpackUnorm2x16: f / 65535.0
     */
   return (float) u / 65535.0f;
}

/**
 * Evaluate one component of packHalf2x16.
 */
static uint16_t
pack_half_1x16(float x)
{
   return _mesa_float_to_half(x);
}

/**
 * Evaluate one component of unpackHalf2x16.
 */
static float
unpack_half_1x16(uint16_t u)
{
   return _mesa_half_to_float(u);
}

/**
 * Get the constant that is ultimately referenced by an r-value, in a constant
 * expression evaluation context.
 *
 * The offset is used when the reference is to a specific column of a matrix.
 */
static bool
constant_referenced(const ir_dereference *deref,
                    struct hash_table *variable_context,
                    ir_constant *&store, int &offset)
{
   store = NULL;
   offset = 0;

   if (variable_context == NULL)
      return false;

   switch (deref->ir_type) {
   case ir_type_dereference_array: {
      const ir_dereference_array *const da =
         (const ir_dereference_array *) deref;

      ir_constant *const index_c =
         da->array_index->constant_expression_value(variable_context);

      if (!index_c || !index_c->type->is_scalar() || !index_c->type->is_integer())
         break;

      const int index = index_c->type->base_type == GLSL_TYPE_INT ?
         index_c->get_int_component(0) :
         index_c->get_uint_component(0);

      ir_constant *substore;
      int suboffset;

      const ir_dereference *const deref = da->array->as_dereference();
      if (!deref)
         break;

      if (!constant_referenced(deref, variable_context, substore, suboffset))
         break;

      const glsl_type *const vt = da->array->type;
      if (vt->is_array()) {
         store = substore->get_array_element(index);
         offset = 0;
      } else if (vt->is_matrix()) {
         store = substore;
         offset = index * vt->vector_elements;
      } else if (vt->is_vector()) {
         store = substore;
         offset = suboffset + index;
      }

      break;
   }

   case ir_type_dereference_record: {
      const ir_dereference_record *const dr =
         (const ir_dereference_record *) deref;

      const ir_dereference *const deref = dr->record->as_dereference();
      if (!deref)
         break;

      ir_constant *substore;
      int suboffset;

      if (!constant_referenced(deref, variable_context, substore, suboffset))
         break;

      /* Since we're dropping it on the floor...
       */
      assert(suboffset == 0);

      store = substore->get_record_field(dr->field);
      break;
   }

   case ir_type_dereference_variable: {
      const ir_dereference_variable *const dv =
         (const ir_dereference_variable *) deref;

      store = (ir_constant *) hash_table_find(variable_context, dv->var);
      break;
   }

   default:
      assert(!"Should not get here.");
      break;
   }

   return store != NULL;
}


ir_constant *
ir_rvalue::constant_expression_value(struct hash_table *)
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
      switch (this->operation) {
      case ir_binop_lshift:
      case ir_binop_rshift:
      case ir_binop_ldexp:
      case ir_binop_interpolate_at_offset:
      case ir_binop_interpolate_at_sample:
      case ir_binop_vector_extract:
      case ir_triop_csel:
      case ir_triop_bitfield_extract:
         break;

      default:
         assert(op[0]->type->base_type == op[1]->type->base_type);
         break;
      }

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
	 data.f[c] = (float)_mesa_round_to_even(op[0]->value.f[c]);
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

	case ir_unop_normalize:
	{
		assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
		float mag2 = 0.0f;
		for (unsigned c = 0; c < op[0]->type->components(); c++) {
			mag2 += op[0]->value.f[c] * op[0]->value.f[c];
		}
		// how would one express "vec3(nan)" in GLSL? no idea, so let's just not handle it
		if (mag2 == 0.0f)
			return NULL;
		float mag = sqrtf(mag2);
		for (unsigned c = 0; c < op[0]->type->components(); c++) {
			data.f[c] = op[0]->value.f[c] / mag;
		}
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
   case ir_unop_dFdx_coarse:
   case ir_unop_dFdx_fine:
   case ir_unop_dFdy:
   case ir_unop_dFdy_coarse:
   case ir_unop_dFdy_fine:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      for (unsigned c = 0; c < op[0]->type->components(); c++) {
	 data.f[c] = 0.0;
      }
      break;

   case ir_unop_pack_snorm_2x16:
      assert(op[0]->type == glsl_type::vec2_type);
      data.u[0] = pack_2x16(pack_snorm_1x16,
                            op[0]->value.f[0],
                            op[0]->value.f[1]);
      break;
   case ir_unop_pack_snorm_4x8:
      assert(op[0]->type == glsl_type::vec4_type);
      data.u[0] = pack_4x8(pack_snorm_1x8,
                           op[0]->value.f[0],
                           op[0]->value.f[1],
                           op[0]->value.f[2],
                           op[0]->value.f[3]);
      break;
   case ir_unop_unpack_snorm_2x16:
      assert(op[0]->type == glsl_type::uint_type);
      unpack_2x16(unpack_snorm_1x16,
                  op[0]->value.u[0],
                  &data.f[0], &data.f[1]);
      break;
   case ir_unop_unpack_snorm_4x8:
      assert(op[0]->type == glsl_type::uint_type);
      unpack_4x8(unpack_snorm_1x8,
                 op[0]->value.u[0],
                 &data.f[0], &data.f[1], &data.f[2], &data.f[3]);
      break;
   case ir_unop_pack_unorm_2x16:
      assert(op[0]->type == glsl_type::vec2_type);
      data.u[0] = pack_2x16(pack_unorm_1x16,
                            op[0]->value.f[0],
                            op[0]->value.f[1]);
      break;
   case ir_unop_pack_unorm_4x8:
      assert(op[0]->type == glsl_type::vec4_type);
      data.u[0] = pack_4x8(pack_unorm_1x8,
                           op[0]->value.f[0],
                           op[0]->value.f[1],
                           op[0]->value.f[2],
                           op[0]->value.f[3]);
      break;
   case ir_unop_unpack_unorm_2x16:
      assert(op[0]->type == glsl_type::uint_type);
      unpack_2x16(unpack_unorm_1x16,
                  op[0]->value.u[0],
                  &data.f[0], &data.f[1]);
      break;
   case ir_unop_unpack_unorm_4x8:
      assert(op[0]->type == glsl_type::uint_type);
      unpack_4x8(unpack_unorm_1x8,
                 op[0]->value.u[0],
                 &data.f[0], &data.f[1], &data.f[2], &data.f[3]);
      break;
   case ir_unop_pack_half_2x16:
      assert(op[0]->type == glsl_type::vec2_type);
      data.u[0] = pack_2x16(pack_half_1x16,
                            op[0]->value.f[0],
                            op[0]->value.f[1]);
      break;
   case ir_unop_unpack_half_2x16:
      assert(op[0]->type == glsl_type::uint_type);
      unpack_2x16(unpack_half_1x16,
                  op[0]->value.u[0],
                  &data.f[0], &data.f[1]);
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

   case ir_binop_vector_extract: {
      const int c = CLAMP(op[1]->value.i[0], 0,
			  (int) op[0]->type->vector_elements - 1);

      switch (op[0]->type->base_type) {
      case GLSL_TYPE_UINT:
         data.u[0] = op[0]->value.u[c];
         break;
      case GLSL_TYPE_INT:
         data.i[0] = op[0]->value.i[c];
         break;
      case GLSL_TYPE_FLOAT:
         data.f[0] = op[0]->value.f[c];
         break;
      case GLSL_TYPE_BOOL:
         data.b[0] = op[0]->value.b[c];
         break;
      default:
         assert(0);
      }
      break;
   }

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

   case ir_unop_bitfield_reverse:
      /* http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious */
      for (unsigned c = 0; c < components; c++) {
         unsigned int v = op[0]->value.u[c]; // input bits to be reversed
         unsigned int r = v; // r will be reversed bits of v; first get LSB of v
         int s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end

         for (v >>= 1; v; v >>= 1) {
            r <<= 1;
            r |= v & 1;
            s--;
         }
         r <<= s; // shift when v's highest bits are zero

         data.u[c] = r;
      }
      break;

   case ir_unop_bit_count:
      for (unsigned c = 0; c < components; c++) {
         unsigned count = 0;
         unsigned v = op[0]->value.u[c];

         for (; v; count++) {
            v &= v - 1;
         }
         data.u[c] = count;
      }
      break;

   case ir_unop_find_msb:
      for (unsigned c = 0; c < components; c++) {
         int v = op[0]->value.i[c];

         if (v == 0 || (op[0]->type->base_type == GLSL_TYPE_INT && v == -1))
            data.i[c] = -1;
         else {
            int count = 0;
            int top_bit = op[0]->type->base_type == GLSL_TYPE_UINT
                          ? 0 : v & (1 << 31);

            while (((v & (1 << 31)) == top_bit) && count != 32) {
               count++;
               v <<= 1;
            }

            data.i[c] = 31 - count;
         }
      }
      break;

   case ir_unop_find_lsb:
      for (unsigned c = 0; c < components; c++) {
         if (op[0]->value.i[c] == 0)
            data.i[c] = -1;
         else {
            unsigned pos = 0;
            unsigned v = op[0]->value.u[c];

            for (; !(v & 1); v >>= 1) {
               pos++;
            }
            data.u[c] = pos;
         }
      }
      break;

   case ir_unop_saturate:
      for (unsigned c = 0; c < components; c++) {
         data.f[c] = CLAMP(op[0]->value.f[c], 0.0f, 1.0f);
      }
      break;

   case ir_triop_bitfield_extract: {
      int offset = op[1]->value.i[0];
      int bits = op[2]->value.i[0];

      for (unsigned c = 0; c < components; c++) {
         if (bits == 0)
            data.u[c] = 0;
         else if (offset < 0 || bits < 0)
            data.u[c] = 0; /* Undefined, per spec. */
         else if (offset + bits > 32)
            data.u[c] = 0; /* Undefined, per spec. */
         else {
            if (op[0]->type->base_type == GLSL_TYPE_INT) {
               /* int so that the right shift will sign-extend. */
               int value = op[0]->value.i[c];
               value <<= 32 - bits - offset;
               value >>= 32 - bits;
               data.i[c] = value;
            } else {
               unsigned value = op[0]->value.u[c];
               value <<= 32 - bits - offset;
               value >>= 32 - bits;
               data.u[c] = value;
            }
         }
      }
      break;
   }

   case ir_binop_bfm: {
      int bits = op[0]->value.i[0];
      int offset = op[1]->value.i[0];

      for (unsigned c = 0; c < components; c++) {
         if (bits == 0)
            data.u[c] = op[0]->value.u[c];
         else if (offset < 0 || bits < 0)
            data.u[c] = 0; /* Undefined for bitfieldInsert, per spec. */
         else if (offset + bits > 32)
            data.u[c] = 0; /* Undefined for bitfieldInsert, per spec. */
         else
            data.u[c] = ((1 << bits) - 1) << offset;
      }
      break;
   }

   case ir_binop_ldexp:
      for (unsigned c = 0; c < components; c++) {
         data.f[c] = ldexp(op[0]->value.f[c], op[1]->value.i[c]);
         /* Flush subnormal values to zero. */
         if (!isnormal(data.f[c]))
            data.f[c] = copysign(0.0f, op[0]->value.f[c]);
      }
      break;

   case ir_triop_fma:
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      assert(op[1]->type->base_type == GLSL_TYPE_FLOAT);
      assert(op[2]->type->base_type == GLSL_TYPE_FLOAT);

      for (unsigned c = 0; c < components; c++) {
         data.f[c] = op[0]->value.f[c] * op[1]->value.f[c]
                                       + op[2]->value.f[c];
      }
      break;

   case ir_triop_lrp: {
      assert(op[0]->type->base_type == GLSL_TYPE_FLOAT);
      assert(op[1]->type->base_type == GLSL_TYPE_FLOAT);
      assert(op[2]->type->base_type == GLSL_TYPE_FLOAT);

      unsigned c2_inc = op[2]->type->is_scalar() ? 0 : 1;
      for (unsigned c = 0, c2 = 0; c < components; c2 += c2_inc, c++) {
         data.f[c] = op[0]->value.f[c] * (1.0f - op[2]->value.f[c2]) +
                     (op[1]->value.f[c] * op[2]->value.f[c2]);
      }
      break;
   }

   case ir_triop_csel:
      for (unsigned c = 0; c < components; c++) {
         data.u[c] = op[0]->value.b[c] ? op[1]->value.u[c]
                                       : op[2]->value.u[c];
      }
      break;

   case ir_triop_vector_insert: {
      const unsigned idx = op[2]->value.u[0];

      memcpy(&data, &op[0]->value, sizeof(data));

      switch (this->type->base_type) {
      case GLSL_TYPE_INT:
	 data.i[idx] = op[1]->value.i[0];
	 break;
      case GLSL_TYPE_UINT:
	 data.u[idx] = op[1]->value.u[0];
	 break;
      case GLSL_TYPE_FLOAT:
	 data.f[idx] = op[1]->value.f[0];
	 break;
      case GLSL_TYPE_BOOL:
	 data.b[idx] = op[1]->value.b[0];
	 break;
      default:
	 assert(!"Should not get here.");
	 break;
      }
      break;
   }

   case ir_quadop_bitfield_insert: {
      int offset = op[2]->value.i[0];
      int bits = op[3]->value.i[0];

      for (unsigned c = 0; c < components; c++) {
         if (bits == 0)
            data.u[c] = op[0]->value.u[c];
         else if (offset < 0 || bits < 0)
            data.u[c] = 0; /* Undefined, per spec. */
         else if (offset + bits > 32)
            data.u[c] = 0; /* Undefined, per spec. */
         else {
            unsigned insert_mask = ((1 << bits) - 1) << offset;

            unsigned insert = op[1]->value.u[c];
            insert <<= offset;
            insert &= insert_mask;

            unsigned base = op[0]->value.u[c];
            base &= ~insert_mask;

            data.u[c] = base | insert;
         }
      }
      break;
   }

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
ir_texture::constant_expression_value(struct hash_table *)
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
   if (var->data.mode == ir_var_uniform)
      return NULL;

   if (!var->constant_value)
      return NULL;

   return var->constant_value->clone(ralloc_parent(var), NULL);
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


ir_constant *
ir_dereference_record::constant_expression_value(struct hash_table *)
{
   ir_constant *v = this->record->constant_expression_value();

   return (v != NULL) ? v->get_record_field(this->field) : NULL;
}


ir_constant *
ir_assignment::constant_expression_value(struct hash_table *)
{
   /* FINISHME: Handle CEs involving assignment (return RHS) */
   return NULL;
}


ir_constant *
ir_constant::constant_expression_value(struct hash_table *)
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
   foreach_in_list(ir_instruction, inst, &body) {
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

	 if (!constant_referenced(asg->lhs, variable_context, store, offset))
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

	 if (!constant_referenced(call->return_deref, variable_context,
                                  store, offset))
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
   if (!this->is_builtin())
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

   foreach_in_list(ir_rvalue, n, actual_parameters) {
      ir_constant *constant = n->constant_expression_value(variable_context);
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

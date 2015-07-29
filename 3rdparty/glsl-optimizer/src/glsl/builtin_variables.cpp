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

#include "ir.h"
#include "glsl_parser_extras.h"
#include "glsl_symbol_table.h"
#include "main/core.h"
#include "program/prog_parameter.h"
#include "program/prog_statevars.h"
#include "program/prog_instruction.h"

// these two are ripped from mesa/main/uniforms.h in upstream
struct gl_builtin_uniform_element {
	const char *field;
	int tokens[STATE_LENGTH];
	int swizzle;
};
struct gl_builtin_uniform_desc {
	const char *name;
	const struct gl_builtin_uniform_element *elements;
	unsigned int num_elements;
};


static const struct gl_builtin_uniform_element gl_NumSamples_elements[] = {
   {NULL, {STATE_NUM_SAMPLES, 0, 0}, SWIZZLE_XXXX}
};


static const struct gl_builtin_uniform_element gl_DepthRange_elements[] = {
   {"near", {STATE_DEPTH_RANGE, 0, 0}, SWIZZLE_XXXX},
   {"far", {STATE_DEPTH_RANGE, 0, 0}, SWIZZLE_YYYY},
   {"diff", {STATE_DEPTH_RANGE, 0, 0}, SWIZZLE_ZZZZ},
};

static const struct gl_builtin_uniform_element gl_ClipPlane_elements[] = {
   {NULL, {STATE_CLIPPLANE, 0, 0}, SWIZZLE_XYZW}
};

static const struct gl_builtin_uniform_element gl_Point_elements[] = {
   {"size", {STATE_POINT_SIZE}, SWIZZLE_XXXX},
   {"sizeMin", {STATE_POINT_SIZE}, SWIZZLE_YYYY},
   {"sizeMax", {STATE_POINT_SIZE}, SWIZZLE_ZZZZ},
   {"fadeThresholdSize", {STATE_POINT_SIZE}, SWIZZLE_WWWW},
   {"distanceConstantAttenuation", {STATE_POINT_ATTENUATION}, SWIZZLE_XXXX},
   {"distanceLinearAttenuation", {STATE_POINT_ATTENUATION}, SWIZZLE_YYYY},
   {"distanceQuadraticAttenuation", {STATE_POINT_ATTENUATION}, SWIZZLE_ZZZZ},
};

static const struct gl_builtin_uniform_element gl_FrontMaterial_elements[] = {
   {"emission", {STATE_MATERIAL, 0, STATE_EMISSION}, SWIZZLE_XYZW},
   {"ambient", {STATE_MATERIAL, 0, STATE_AMBIENT}, SWIZZLE_XYZW},
   {"diffuse", {STATE_MATERIAL, 0, STATE_DIFFUSE}, SWIZZLE_XYZW},
   {"specular", {STATE_MATERIAL, 0, STATE_SPECULAR}, SWIZZLE_XYZW},
   {"shininess", {STATE_MATERIAL, 0, STATE_SHININESS}, SWIZZLE_XXXX},
};

static const struct gl_builtin_uniform_element gl_BackMaterial_elements[] = {
   {"emission", {STATE_MATERIAL, 1, STATE_EMISSION}, SWIZZLE_XYZW},
   {"ambient", {STATE_MATERIAL, 1, STATE_AMBIENT}, SWIZZLE_XYZW},
   {"diffuse", {STATE_MATERIAL, 1, STATE_DIFFUSE}, SWIZZLE_XYZW},
   {"specular", {STATE_MATERIAL, 1, STATE_SPECULAR}, SWIZZLE_XYZW},
   {"shininess", {STATE_MATERIAL, 1, STATE_SHININESS}, SWIZZLE_XXXX},
};

static const struct gl_builtin_uniform_element gl_LightSource_elements[] = {
   {"ambient", {STATE_LIGHT, 0, STATE_AMBIENT}, SWIZZLE_XYZW},
   {"diffuse", {STATE_LIGHT, 0, STATE_DIFFUSE}, SWIZZLE_XYZW},
   {"specular", {STATE_LIGHT, 0, STATE_SPECULAR}, SWIZZLE_XYZW},
   {"position", {STATE_LIGHT, 0, STATE_POSITION}, SWIZZLE_XYZW},
   {"halfVector", {STATE_LIGHT, 0, STATE_HALF_VECTOR}, SWIZZLE_XYZW},
   {"spotDirection", {STATE_LIGHT, 0, STATE_SPOT_DIRECTION},
    MAKE_SWIZZLE4(SWIZZLE_X,
		  SWIZZLE_Y,
		  SWIZZLE_Z,
		  SWIZZLE_Z)},
   {"spotCosCutoff", {STATE_LIGHT, 0, STATE_SPOT_DIRECTION}, SWIZZLE_WWWW},
   {"spotCutoff", {STATE_LIGHT, 0, STATE_SPOT_CUTOFF}, SWIZZLE_XXXX},
   {"spotExponent", {STATE_LIGHT, 0, STATE_ATTENUATION}, SWIZZLE_WWWW},
   {"constantAttenuation", {STATE_LIGHT, 0, STATE_ATTENUATION}, SWIZZLE_XXXX},
   {"linearAttenuation", {STATE_LIGHT, 0, STATE_ATTENUATION}, SWIZZLE_YYYY},
   {"quadraticAttenuation", {STATE_LIGHT, 0, STATE_ATTENUATION}, SWIZZLE_ZZZZ},
};

static const struct gl_builtin_uniform_element gl_LightModel_elements[] = {
   {"ambient", {STATE_LIGHTMODEL_AMBIENT, 0}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_FrontLightModelProduct_elements[] = {
   {"sceneColor", {STATE_LIGHTMODEL_SCENECOLOR, 0}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_BackLightModelProduct_elements[] = {
   {"sceneColor", {STATE_LIGHTMODEL_SCENECOLOR, 1}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_FrontLightProduct_elements[] = {
   {"ambient", {STATE_LIGHTPROD, 0, 0, STATE_AMBIENT}, SWIZZLE_XYZW},
   {"diffuse", {STATE_LIGHTPROD, 0, 0, STATE_DIFFUSE}, SWIZZLE_XYZW},
   {"specular", {STATE_LIGHTPROD, 0, 0, STATE_SPECULAR}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_BackLightProduct_elements[] = {
   {"ambient", {STATE_LIGHTPROD, 0, 1, STATE_AMBIENT}, SWIZZLE_XYZW},
   {"diffuse", {STATE_LIGHTPROD, 0, 1, STATE_DIFFUSE}, SWIZZLE_XYZW},
   {"specular", {STATE_LIGHTPROD, 0, 1, STATE_SPECULAR}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_TextureEnvColor_elements[] = {
   {NULL, {STATE_TEXENV_COLOR, 0}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_EyePlaneS_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_EYE_S}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_EyePlaneT_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_EYE_T}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_EyePlaneR_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_EYE_R}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_EyePlaneQ_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_EYE_Q}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_ObjectPlaneS_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_OBJECT_S}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_ObjectPlaneT_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_OBJECT_T}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_ObjectPlaneR_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_OBJECT_R}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_ObjectPlaneQ_elements[] = {
   {NULL, {STATE_TEXGEN, 0, STATE_TEXGEN_OBJECT_Q}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_Fog_elements[] = {
   {"color", {STATE_FOG_COLOR}, SWIZZLE_XYZW},
   {"density", {STATE_FOG_PARAMS}, SWIZZLE_XXXX},
   {"start", {STATE_FOG_PARAMS}, SWIZZLE_YYYY},
   {"end", {STATE_FOG_PARAMS}, SWIZZLE_ZZZZ},
   {"scale", {STATE_FOG_PARAMS}, SWIZZLE_WWWW},
};

static const struct gl_builtin_uniform_element gl_NormalScale_elements[] = {
   {NULL, {STATE_NORMAL_SCALE}, SWIZZLE_XXXX},
};

static const struct gl_builtin_uniform_element gl_FogParamsOptimizedMESA_elements[] = {
   {NULL, {STATE_INTERNAL, STATE_FOG_PARAMS_OPTIMIZED}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_CurrentAttribVertMESA_elements[] = {
   {NULL, {STATE_INTERNAL, STATE_CURRENT_ATTRIB, 0}, SWIZZLE_XYZW},
};

static const struct gl_builtin_uniform_element gl_CurrentAttribFragMESA_elements[] = {
   {NULL, {STATE_INTERNAL, STATE_CURRENT_ATTRIB_MAYBE_VP_CLAMPED, 0}, SWIZZLE_XYZW},
};

#define MATRIX(name, statevar, modifier)				\
   static const struct gl_builtin_uniform_element name ## _elements[] = { \
      { NULL, { statevar, 0, 0, 0, modifier}, SWIZZLE_XYZW },		\
      { NULL, { statevar, 0, 1, 1, modifier}, SWIZZLE_XYZW },		\
      { NULL, { statevar, 0, 2, 2, modifier}, SWIZZLE_XYZW },		\
      { NULL, { statevar, 0, 3, 3, modifier}, SWIZZLE_XYZW },		\
   }

MATRIX(gl_ModelViewMatrix,
       STATE_MODELVIEW_MATRIX, STATE_MATRIX_TRANSPOSE);
MATRIX(gl_ModelViewMatrixInverse,
       STATE_MODELVIEW_MATRIX, STATE_MATRIX_INVTRANS);
MATRIX(gl_ModelViewMatrixTranspose,
       STATE_MODELVIEW_MATRIX, 0);
MATRIX(gl_ModelViewMatrixInverseTranspose,
       STATE_MODELVIEW_MATRIX, STATE_MATRIX_INVERSE);

MATRIX(gl_ProjectionMatrix,
       STATE_PROJECTION_MATRIX, STATE_MATRIX_TRANSPOSE);
MATRIX(gl_ProjectionMatrixInverse,
       STATE_PROJECTION_MATRIX, STATE_MATRIX_INVTRANS);
MATRIX(gl_ProjectionMatrixTranspose,
       STATE_PROJECTION_MATRIX, 0);
MATRIX(gl_ProjectionMatrixInverseTranspose,
       STATE_PROJECTION_MATRIX, STATE_MATRIX_INVERSE);

MATRIX(gl_ModelViewProjectionMatrix,
       STATE_MVP_MATRIX, STATE_MATRIX_TRANSPOSE);
MATRIX(gl_ModelViewProjectionMatrixInverse,
       STATE_MVP_MATRIX, STATE_MATRIX_INVTRANS);
MATRIX(gl_ModelViewProjectionMatrixTranspose,
       STATE_MVP_MATRIX, 0);
MATRIX(gl_ModelViewProjectionMatrixInverseTranspose,
       STATE_MVP_MATRIX, STATE_MATRIX_INVERSE);

MATRIX(gl_TextureMatrix,
       STATE_TEXTURE_MATRIX, STATE_MATRIX_TRANSPOSE);
MATRIX(gl_TextureMatrixInverse,
       STATE_TEXTURE_MATRIX, STATE_MATRIX_INVTRANS);
MATRIX(gl_TextureMatrixTranspose,
       STATE_TEXTURE_MATRIX, 0);
MATRIX(gl_TextureMatrixInverseTranspose,
       STATE_TEXTURE_MATRIX, STATE_MATRIX_INVERSE);

static const struct gl_builtin_uniform_element gl_NormalMatrix_elements[] = {
   { NULL, { STATE_MODELVIEW_MATRIX, 0, 0, 0, STATE_MATRIX_INVERSE},
     MAKE_SWIZZLE4(SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_Z) },
   { NULL, { STATE_MODELVIEW_MATRIX, 0, 1, 1, STATE_MATRIX_INVERSE},
     MAKE_SWIZZLE4(SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_Z) },
   { NULL, { STATE_MODELVIEW_MATRIX, 0, 2, 2, STATE_MATRIX_INVERSE},
     MAKE_SWIZZLE4(SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_Z) },
};

#undef MATRIX

#define STATEVAR(name) {#name, name ## _elements, Elements(name ## _elements)}

static const struct gl_builtin_uniform_desc _mesa_builtin_uniform_desc[] = {
   STATEVAR(gl_NumSamples),
   STATEVAR(gl_DepthRange),
   STATEVAR(gl_ClipPlane),
   STATEVAR(gl_Point),
   STATEVAR(gl_FrontMaterial),
   STATEVAR(gl_BackMaterial),
   STATEVAR(gl_LightSource),
   STATEVAR(gl_LightModel),
   STATEVAR(gl_FrontLightModelProduct),
   STATEVAR(gl_BackLightModelProduct),
   STATEVAR(gl_FrontLightProduct),
   STATEVAR(gl_BackLightProduct),
   STATEVAR(gl_TextureEnvColor),
   STATEVAR(gl_EyePlaneS),
   STATEVAR(gl_EyePlaneT),
   STATEVAR(gl_EyePlaneR),
   STATEVAR(gl_EyePlaneQ),
   STATEVAR(gl_ObjectPlaneS),
   STATEVAR(gl_ObjectPlaneT),
   STATEVAR(gl_ObjectPlaneR),
   STATEVAR(gl_ObjectPlaneQ),
   STATEVAR(gl_Fog),

   STATEVAR(gl_ModelViewMatrix),
   STATEVAR(gl_ModelViewMatrixInverse),
   STATEVAR(gl_ModelViewMatrixTranspose),
   STATEVAR(gl_ModelViewMatrixInverseTranspose),

   STATEVAR(gl_ProjectionMatrix),
   STATEVAR(gl_ProjectionMatrixInverse),
   STATEVAR(gl_ProjectionMatrixTranspose),
   STATEVAR(gl_ProjectionMatrixInverseTranspose),

   STATEVAR(gl_ModelViewProjectionMatrix),
   STATEVAR(gl_ModelViewProjectionMatrixInverse),
   STATEVAR(gl_ModelViewProjectionMatrixTranspose),
   STATEVAR(gl_ModelViewProjectionMatrixInverseTranspose),

   STATEVAR(gl_TextureMatrix),
   STATEVAR(gl_TextureMatrixInverse),
   STATEVAR(gl_TextureMatrixTranspose),
   STATEVAR(gl_TextureMatrixInverseTranspose),

   STATEVAR(gl_NormalMatrix),
   STATEVAR(gl_NormalScale),

   STATEVAR(gl_FogParamsOptimizedMESA),
   STATEVAR(gl_CurrentAttribVertMESA),
   STATEVAR(gl_CurrentAttribFragMESA),

   {NULL, NULL, 0}
};


namespace {

/**
 * Data structure that accumulates fields for the gl_PerVertex interface
 * block.
 */
class per_vertex_accumulator
{
public:
   per_vertex_accumulator();
   void add_field(int slot, const glsl_type *type, const char *name, glsl_precision prec);
   const glsl_type *construct_interface_instance() const;

private:
   glsl_struct_field fields[10];
   unsigned num_fields;
};


per_vertex_accumulator::per_vertex_accumulator()
   : fields(),
     num_fields(0)
{
}


void
per_vertex_accumulator::add_field(int slot, const glsl_type *type,
                                  const char *name, glsl_precision prec)
{
   assert(this->num_fields < ARRAY_SIZE(this->fields));
   this->fields[this->num_fields].type = type;
   this->fields[this->num_fields].name = name;
   this->fields[this->num_fields].matrix_layout = GLSL_MATRIX_LAYOUT_INHERITED;
   this->fields[this->num_fields].precision = prec;
   this->fields[this->num_fields].location = slot;
   this->fields[this->num_fields].interpolation = INTERP_QUALIFIER_NONE;
   this->fields[this->num_fields].centroid = 0;
   this->fields[this->num_fields].sample = 0;
   this->num_fields++;
}


const glsl_type *
per_vertex_accumulator::construct_interface_instance() const
{
   return glsl_type::get_interface_instance(this->fields, this->num_fields,
                                            GLSL_INTERFACE_PACKING_STD140,
                                            "gl_PerVertex");
}


class builtin_variable_generator
{
public:
   builtin_variable_generator(exec_list *instructions,
                              struct _mesa_glsl_parse_state *state);
   void generate_constants();
   void generate_uniforms();
   void generate_vs_special_vars();
   void generate_gs_special_vars();
   void generate_fs_special_vars();
   void generate_cs_special_vars();
   void generate_varyings();

private:
   const glsl_type *array(const glsl_type *base, unsigned elements)
   {
      return glsl_type::get_array_instance(base, elements);
   }

   const glsl_type *type(const char *name)
   {
      return symtab->get_type(name);
   }

   ir_variable *add_input(int slot, const glsl_type *type, const char *name, glsl_precision prec)
   {
      return add_variable(name, type, ir_var_shader_in, slot, prec);
   }

   ir_variable *add_output(int slot, const glsl_type *type, const char *name, glsl_precision prec)
   {
      return add_variable(name, type, ir_var_shader_out, slot, prec);
   }

   ir_variable *add_system_value(int slot, const glsl_type *type,
                                 const char *name, glsl_precision prec)
   {
      return add_variable(name, type, ir_var_system_value, slot, prec);
   }

   ir_variable *add_variable(const char *name, const glsl_type *type,
                             enum ir_variable_mode mode, int slot, glsl_precision prec);
   ir_variable *add_uniform(const glsl_type *type, const char *name, glsl_precision prec = glsl_precision_undefined);
   ir_variable *add_const(const char *name, int value);
   ir_variable *add_const_ivec3(const char *name, int x, int y, int z);
   void add_varying(int slot, const glsl_type *type, const char *name,
                    const char *name_as_gs_input, glsl_precision prec);

   exec_list * const instructions;
   struct _mesa_glsl_parse_state * const state;
   glsl_symbol_table * const symtab;

   /**
    * True if compatibility-profile-only variables should be included.  (In
    * desktop GL, these are always included when the GLSL version is 1.30 and
    * or below).
    */
   const bool compatibility;

   const glsl_type * const bool_t;
   const glsl_type * const int_t;
   const glsl_type * const uint_t;
   const glsl_type * const float_t;
   const glsl_type * const vec2_t;
   const glsl_type * const vec3_t;
   const glsl_type * const vec4_t;
   const glsl_type * const mat3_t;
   const glsl_type * const mat4_t;

   per_vertex_accumulator per_vertex_in;
   per_vertex_accumulator per_vertex_out;
};


builtin_variable_generator::builtin_variable_generator(
   exec_list *instructions, struct _mesa_glsl_parse_state *state)
   : instructions(instructions), state(state), symtab(state->symbols),
     compatibility(!state->is_version(140, 100)),
     bool_t(glsl_type::bool_type), int_t(glsl_type::int_type), uint_t(glsl_type::uint_type),
     float_t(glsl_type::float_type), vec2_t(glsl_type::vec2_type),
     vec3_t(glsl_type::vec3_type), vec4_t(glsl_type::vec4_type),
     mat3_t(glsl_type::mat3_type), mat4_t(glsl_type::mat4_type)
{
}


ir_variable *
builtin_variable_generator::add_variable(const char *name,
                                         const glsl_type *type,
                                         enum ir_variable_mode mode, int slot, glsl_precision prec)

{
   if (!this->state->es_shader)
      prec = glsl_precision_undefined;
   ir_variable *var = new(symtab) ir_variable(type, name, mode, prec);
   var->data.how_declared = ir_var_declared_implicitly;

   switch (var->data.mode) {
   case ir_var_auto:
   case ir_var_shader_in:
   case ir_var_uniform:
   case ir_var_system_value:
      var->data.read_only = true;
      break;
   case ir_var_shader_out:
      break;
   default:
      /* The only variables that are added using this function should be
       * uniforms, shader inputs, and shader outputs, constants (which use
       * ir_var_auto), and system values.
       */
      assert(0);
      break;
   }

   var->data.location = slot;
   var->data.explicit_location = (slot >= 0);
   var->data.explicit_index = 0;

   /* Once the variable is created an initialized, add it to the symbol table
    * and add the declaration to the IR stream.
    */
   instructions->push_tail(var);

   symtab->add_variable(var);
   return var;
}


ir_variable *
builtin_variable_generator::add_uniform(const glsl_type *type,
                                        const char *name, glsl_precision prec)
{
   ir_variable *const uni = add_variable(name, type, ir_var_uniform, -1, prec);

   unsigned i;
   for (i = 0; _mesa_builtin_uniform_desc[i].name != NULL; i++) {
      if (strcmp(_mesa_builtin_uniform_desc[i].name, name) == 0) {
	 break;
      }
   }

   assert(_mesa_builtin_uniform_desc[i].name != NULL);
   const struct gl_builtin_uniform_desc* const statevar =
      &_mesa_builtin_uniform_desc[i];

   const unsigned array_count = type->is_array() ? type->length : 1;

   ir_state_slot *slots =
      uni->allocate_state_slots(array_count * statevar->num_elements);

   for (unsigned a = 0; a < array_count; a++) {
      for (unsigned j = 0; j < statevar->num_elements; j++) {
	 const struct gl_builtin_uniform_element *element =
	    &statevar->elements[j];

	 memcpy(slots->tokens, element->tokens, sizeof(element->tokens));
	 if (type->is_array()) {
	    if (strcmp(name, "gl_CurrentAttribVertMESA") == 0 ||
		strcmp(name, "gl_CurrentAttribFragMESA") == 0) {
	       slots->tokens[2] = a;
	    } else {
	       slots->tokens[1] = a;
	    }
	 }

	 slots->swizzle = element->swizzle;
	 slots++;
      }
   }

   return uni;
}


ir_variable *
builtin_variable_generator::add_const(const char *name, int value)
{
   ir_variable *const var = add_variable(name, glsl_type::int_type,
					 ir_var_auto, -1, glsl_precision_undefined);
   var->constant_value = new(var) ir_constant(value);
   var->constant_initializer = new(var) ir_constant(value);
   var->data.has_initializer = true;
   return var;
}


ir_variable *
builtin_variable_generator::add_const_ivec3(const char *name, int x, int y,
                                            int z)
{
   ir_variable *const var = add_variable(name, glsl_type::ivec3_type,
                                         ir_var_auto, -1, glsl_precision_undefined);
   ir_constant_data data;
   memset(&data, 0, sizeof(data));
   data.i[0] = x;
   data.i[1] = y;
   data.i[2] = z;
   var->constant_value = new(var) ir_constant(glsl_type::ivec3_type, &data);
   var->constant_initializer =
      new(var) ir_constant(glsl_type::ivec3_type, &data);
   var->data.has_initializer = true;
   return var;
}


void
builtin_variable_generator::generate_constants()
{
   add_const("gl_MaxVertexAttribs", state->Const.MaxVertexAttribs);
   add_const("gl_MaxVertexTextureImageUnits",
             state->Const.MaxVertexTextureImageUnits);
   add_const("gl_MaxCombinedTextureImageUnits",
             state->Const.MaxCombinedTextureImageUnits);
   add_const("gl_MaxTextureImageUnits", state->Const.MaxTextureImageUnits);
   add_const("gl_MaxDrawBuffers", state->Const.MaxDrawBuffers);

   /* Max uniforms/varyings: GLSL ES counts these in units of vectors; desktop
    * GL counts them in units of "components" or "floats".
    */
   if (state->es_shader) {
      add_const("gl_MaxVertexUniformVectors",
                state->Const.MaxVertexUniformComponents / 4);
      add_const("gl_MaxFragmentUniformVectors",
                state->Const.MaxFragmentUniformComponents / 4);

      /* In GLSL ES 3.00, gl_MaxVaryingVectors was split out to separate
       * vertex and fragment shader constants.
       */
      if (state->is_version(0, 300)) {
         add_const("gl_MaxVertexOutputVectors",
                   state->ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents / 4);
         add_const("gl_MaxFragmentInputVectors",
                   state->ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents / 4);
      } else {
         add_const("gl_MaxVaryingVectors",
                   state->ctx->Const.MaxVarying);
      }
   } else {
      add_const("gl_MaxVertexUniformComponents",
                state->Const.MaxVertexUniformComponents);

      /* Note: gl_MaxVaryingFloats was deprecated in GLSL 1.30+, but not
       * removed
       */
      add_const("gl_MaxVaryingFloats", state->ctx->Const.MaxVarying * 4);

      add_const("gl_MaxFragmentUniformComponents",
                state->Const.MaxFragmentUniformComponents);
   }

   /* Texel offsets were introduced in ARB_shading_language_420pack (which
    * requires desktop GLSL version 130), and adopted into desktop GLSL
    * version 4.20 and GLSL ES version 3.00.
    */
   if ((state->is_version(130, 0) &&
        state->ARB_shading_language_420pack_enable) ||
      state->is_version(420, 300)) {
      add_const("gl_MinProgramTexelOffset",
                state->Const.MinProgramTexelOffset);
      add_const("gl_MaxProgramTexelOffset",
                state->Const.MaxProgramTexelOffset);
   }

   if (state->is_version(130, 0)) {
      add_const("gl_MaxClipDistances", state->Const.MaxClipPlanes);
      add_const("gl_MaxVaryingComponents", state->ctx->Const.MaxVarying * 4);
   }

   if (state->is_version(150, 0)) {
      add_const("gl_MaxVertexOutputComponents",
                state->Const.MaxVertexOutputComponents);
      add_const("gl_MaxGeometryInputComponents",
                state->Const.MaxGeometryInputComponents);
      add_const("gl_MaxGeometryOutputComponents",
                state->Const.MaxGeometryOutputComponents);
      add_const("gl_MaxFragmentInputComponents",
                state->Const.MaxFragmentInputComponents);
      add_const("gl_MaxGeometryTextureImageUnits",
                state->Const.MaxGeometryTextureImageUnits);
      add_const("gl_MaxGeometryOutputVertices",
                state->Const.MaxGeometryOutputVertices);
      add_const("gl_MaxGeometryTotalOutputComponents",
                state->Const.MaxGeometryTotalOutputComponents);
      add_const("gl_MaxGeometryUniformComponents",
                state->Const.MaxGeometryUniformComponents);

      /* Note: the GLSL 1.50-4.40 specs require
       * gl_MaxGeometryVaryingComponents to be present, and to be at least 64.
       * But they do not define what it means (and there does not appear to be
       * any corresponding constant in the GL specs).  However,
       * ARB_geometry_shader4 defines MAX_GEOMETRY_VARYING_COMPONENTS_ARB to
       * be the maximum number of components available for use as geometry
       * outputs.  So we assume this is a synonym for
       * gl_MaxGeometryOutputComponents.
       */
      add_const("gl_MaxGeometryVaryingComponents",
                state->Const.MaxGeometryOutputComponents);
   }

   if (compatibility) {
      /* Note: gl_MaxLights stopped being listed as an explicit constant in
       * GLSL 1.30, however it continues to be referred to (as a minimum size
       * for compatibility-mode uniforms) all the way up through GLSL 4.30, so
       * this seems like it was probably an oversight.
       */
      add_const("gl_MaxLights", state->Const.MaxLights);

      add_const("gl_MaxClipPlanes", state->Const.MaxClipPlanes);

      /* Note: gl_MaxTextureUnits wasn't made compatibility-only until GLSL
       * 1.50, however this seems like it was probably an oversight.
       */
      add_const("gl_MaxTextureUnits", state->Const.MaxTextureUnits);

      /* Note: gl_MaxTextureCoords was left out of GLSL 1.40, but it was
       * re-introduced in GLSL 1.50, so this seems like it was probably an
       * oversight.
       */
      add_const("gl_MaxTextureCoords", state->Const.MaxTextureCoords);
   }

   if (state->ARB_shader_atomic_counters_enable) {
      add_const("gl_MaxVertexAtomicCounters",
                state->Const.MaxVertexAtomicCounters);
      add_const("gl_MaxGeometryAtomicCounters",
                state->Const.MaxGeometryAtomicCounters);
      add_const("gl_MaxFragmentAtomicCounters",
                state->Const.MaxFragmentAtomicCounters);
      add_const("gl_MaxCombinedAtomicCounters",
                state->Const.MaxCombinedAtomicCounters);
      add_const("gl_MaxAtomicCounterBindings",
                state->Const.MaxAtomicBufferBindings);
      add_const("gl_MaxTessControlAtomicCounters", 0);
      add_const("gl_MaxTessEvaluationAtomicCounters", 0);
   }

   if (state->is_version(430, 0) || state->ARB_compute_shader_enable) {
      add_const("gl_MaxComputeAtomicCounterBuffers", MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS);
      add_const("gl_MaxComputeAtomicCounters", MAX_COMPUTE_ATOMIC_COUNTERS);
      add_const("gl_MaxComputeImageUniforms", MAX_COMPUTE_IMAGE_UNIFORMS);
      add_const("gl_MaxComputeTextureImageUnits", MAX_COMPUTE_TEXTURE_IMAGE_UNITS);
      add_const("gl_MaxComputeUniformComponents", MAX_COMPUTE_UNIFORM_COMPONENTS);

      add_const_ivec3("gl_MaxComputeWorkGroupCount",
                      state->Const.MaxComputeWorkGroupCount[0],
                      state->Const.MaxComputeWorkGroupCount[1],
                      state->Const.MaxComputeWorkGroupCount[2]);
      add_const_ivec3("gl_MaxComputeWorkGroupSize",
                      state->Const.MaxComputeWorkGroupSize[0],
                      state->Const.MaxComputeWorkGroupSize[1],
                      state->Const.MaxComputeWorkGroupSize[2]);

      /* From the GLSL 4.40 spec, section 7.1 (Built-In Language Variables):
       *
       *     The built-in constant gl_WorkGroupSize is a compute-shader
       *     constant containing the local work-group size of the shader.  The
       *     size of the work group in the X, Y, and Z dimensions is stored in
       *     the x, y, and z components.  The constants values in
       *     gl_WorkGroupSize will match those specified in the required
       *     local_size_x, local_size_y, and local_size_z layout qualifiers
       *     for the current shader.  This is a constant so that it can be
       *     used to size arrays of memory that can be shared within the local
       *     work group.  It is a compile-time error to use gl_WorkGroupSize
       *     in a shader that does not declare a fixed local group size, or
       *     before that shader has declared a fixed local group size, using
       *     local_size_x, local_size_y, and local_size_z.
       *
       * To prevent the shader from trying to refer to gl_WorkGroupSize before
       * the layout declaration, we don't define it here.  Intead we define it
       * in ast_cs_input_layout::hir().
       */
   }

   if (state->is_version(420, 0) ||
       state->ARB_shader_image_load_store_enable) {
      add_const("gl_MaxImageUnits",
                state->Const.MaxImageUnits);
      add_const("gl_MaxCombinedImageUnitsAndFragmentOutputs",
                state->Const.MaxCombinedImageUnitsAndFragmentOutputs);
      add_const("gl_MaxImageSamples",
                state->Const.MaxImageSamples);
      add_const("gl_MaxVertexImageUniforms",
                state->Const.MaxVertexImageUniforms);
      add_const("gl_MaxTessControlImageUniforms", 0);
      add_const("gl_MaxTessEvaluationImageUniforms", 0);
      add_const("gl_MaxGeometryImageUniforms",
                state->Const.MaxGeometryImageUniforms);
      add_const("gl_MaxFragmentImageUniforms",
                state->Const.MaxFragmentImageUniforms);
      add_const("gl_MaxCombinedImageUniforms",
                state->Const.MaxCombinedImageUniforms);
   }
}


/**
 * Generate uniform variables (which exist in all types of shaders).
 */
void
builtin_variable_generator::generate_uniforms()
{
   add_uniform(int_t, "gl_NumSamples", glsl_precision_undefined);
   add_uniform(type("gl_DepthRangeParameters"), "gl_DepthRange", glsl_precision_undefined);
   add_uniform(array(vec4_t, VERT_ATTRIB_MAX), "gl_CurrentAttribVertMESA", glsl_precision_undefined);
   add_uniform(array(vec4_t, VARYING_SLOT_MAX), "gl_CurrentAttribFragMESA", glsl_precision_undefined);

   if (compatibility) {
      add_uniform(mat4_t, "gl_ModelViewMatrix");
      add_uniform(mat4_t, "gl_ProjectionMatrix");
      add_uniform(mat4_t, "gl_ModelViewProjectionMatrix");
      add_uniform(mat3_t, "gl_NormalMatrix");
      add_uniform(mat4_t, "gl_ModelViewMatrixInverse");
      add_uniform(mat4_t, "gl_ProjectionMatrixInverse");
      add_uniform(mat4_t, "gl_ModelViewProjectionMatrixInverse");
      add_uniform(mat4_t, "gl_ModelViewMatrixTranspose");
      add_uniform(mat4_t, "gl_ProjectionMatrixTranspose");
      add_uniform(mat4_t, "gl_ModelViewProjectionMatrixTranspose");
      add_uniform(mat4_t, "gl_ModelViewMatrixInverseTranspose");
      add_uniform(mat4_t, "gl_ProjectionMatrixInverseTranspose");
      add_uniform(mat4_t, "gl_ModelViewProjectionMatrixInverseTranspose");
      add_uniform(float_t, "gl_NormalScale");
      add_uniform(type("gl_LightModelParameters"), "gl_LightModel");
      add_uniform(vec4_t, "gl_FogParamsOptimizedMESA");

      const glsl_type *const mat4_array_type =
	 array(mat4_t, state->Const.MaxTextureCoords);
      add_uniform(mat4_array_type, "gl_TextureMatrix", glsl_precision_undefined);
      add_uniform(mat4_array_type, "gl_TextureMatrixInverse", glsl_precision_undefined);
      add_uniform(mat4_array_type, "gl_TextureMatrixTranspose", glsl_precision_undefined);
      add_uniform(mat4_array_type, "gl_TextureMatrixInverseTranspose", glsl_precision_undefined);

      add_uniform(array(vec4_t, state->Const.MaxClipPlanes), "gl_ClipPlane", glsl_precision_undefined);
      add_uniform(type("gl_PointParameters"), "gl_Point", glsl_precision_undefined);

      const glsl_type *const material_parameters_type =
	 type("gl_MaterialParameters");
      add_uniform(material_parameters_type, "gl_FrontMaterial", glsl_precision_undefined);
      add_uniform(material_parameters_type, "gl_BackMaterial", glsl_precision_undefined);

      add_uniform(array(type("gl_LightSourceParameters"),
                        state->Const.MaxLights),
                  "gl_LightSource", glsl_precision_undefined);

      const glsl_type *const light_model_products_type =
         type("gl_LightModelProducts");
      add_uniform(light_model_products_type, "gl_FrontLightModelProduct", glsl_precision_undefined);
      add_uniform(light_model_products_type, "gl_BackLightModelProduct", glsl_precision_undefined);

      const glsl_type *const light_products_type =
         array(type("gl_LightProducts"), state->Const.MaxLights);
      add_uniform(light_products_type, "gl_FrontLightProduct", glsl_precision_undefined);
      add_uniform(light_products_type, "gl_BackLightProduct", glsl_precision_undefined);

      add_uniform(array(vec4_t, state->Const.MaxTextureUnits),
                  "gl_TextureEnvColor", glsl_precision_undefined);

      const glsl_type *const texcoords_vec4 =
	 array(vec4_t, state->Const.MaxTextureCoords);
      add_uniform(texcoords_vec4, "gl_EyePlaneS", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_EyePlaneT", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_EyePlaneR", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_EyePlaneQ", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_ObjectPlaneS", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_ObjectPlaneT", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_ObjectPlaneR", glsl_precision_undefined);
      add_uniform(texcoords_vec4, "gl_ObjectPlaneQ", glsl_precision_undefined);

      add_uniform(type("gl_FogParameters"), "gl_Fog", glsl_precision_undefined);
   }
}


/**
 * Generate variables which only exist in vertex shaders.
 */
void
builtin_variable_generator::generate_vs_special_vars()
{

   if (state->is_version(130, 300) || state->EXT_gpu_shader4_enable)
      add_system_value(SYSTEM_VALUE_VERTEX_ID, state->metal_target ? uint_t : int_t, "gl_VertexID", glsl_precision_high);
   if (state->ARB_draw_instanced_enable)
      add_system_value(SYSTEM_VALUE_INSTANCE_ID, int_t, "gl_InstanceIDARB", glsl_precision_high);
   if (state->EXT_draw_instanced_enable)
      add_system_value(SYSTEM_VALUE_INSTANCE_ID, int_t, "gl_InstanceIDEXT", glsl_precision_high);
   if (state->ARB_draw_instanced_enable || state->is_version(140, 300))
	   add_system_value(SYSTEM_VALUE_INSTANCE_ID, state->metal_target ? uint_t : int_t, "gl_InstanceID", glsl_precision_high);
   if (state->AMD_vertex_shader_layer_enable)
      add_output(VARYING_SLOT_LAYER, int_t, "gl_Layer", glsl_precision_high);
   if (state->AMD_vertex_shader_viewport_index_enable)
      add_output(VARYING_SLOT_VIEWPORT, int_t, "gl_ViewportIndex", glsl_precision_high);
   if (compatibility) {
      add_input(VERT_ATTRIB_POS, vec4_t, "gl_Vertex", glsl_precision_high);
      add_input(VERT_ATTRIB_NORMAL, vec3_t, "gl_Normal", glsl_precision_medium);
      add_input(VERT_ATTRIB_COLOR0, vec4_t, "gl_Color", glsl_precision_medium);
      add_input(VERT_ATTRIB_COLOR1, vec4_t, "gl_SecondaryColor", glsl_precision_medium);
      add_input(VERT_ATTRIB_TEX0, vec4_t, "gl_MultiTexCoord0", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX1, vec4_t, "gl_MultiTexCoord1", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX2, vec4_t, "gl_MultiTexCoord2", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX3, vec4_t, "gl_MultiTexCoord3", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX4, vec4_t, "gl_MultiTexCoord4", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX5, vec4_t, "gl_MultiTexCoord5", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX6, vec4_t, "gl_MultiTexCoord6", glsl_precision_high);
      add_input(VERT_ATTRIB_TEX7, vec4_t, "gl_MultiTexCoord7", glsl_precision_high);
      add_input(VERT_ATTRIB_FOG, float_t, "gl_FogCoord", glsl_precision_high);
   }
}


/**
 * Generate variables which only exist in geometry shaders.
 */
void
builtin_variable_generator::generate_gs_special_vars()
{
   add_output(VARYING_SLOT_LAYER, int_t, "gl_Layer", glsl_precision_high);
   if (state->ARB_viewport_array_enable)
      add_output(VARYING_SLOT_VIEWPORT, int_t, "gl_ViewportIndex", glsl_precision_high);
   if (state->ARB_gpu_shader5_enable)
      add_system_value(SYSTEM_VALUE_INVOCATION_ID, int_t, "gl_InvocationID", glsl_precision_high);

   /* Although gl_PrimitiveID appears in tessellation control and tessellation
    * evaluation shaders, it has a different function there than it has in
    * geometry shaders, so we treat it (and its counterpart gl_PrimitiveIDIn)
    * as special geometry shader variables.
    *
    * Note that although the general convention of suffixing geometry shader
    * input varyings with "In" was not adopted into GLSL 1.50, it is used in
    * the specific case of gl_PrimitiveIDIn.  So we don't need to treat
    * gl_PrimitiveIDIn as an {ARB,EXT}_geometry_shader4-only variable.
    */
   ir_variable *var;
   var = add_input(VARYING_SLOT_PRIMITIVE_ID, int_t, "gl_PrimitiveIDIn", glsl_precision_high);
   var->data.interpolation = INTERP_QUALIFIER_FLAT;
   var = add_output(VARYING_SLOT_PRIMITIVE_ID, int_t, "gl_PrimitiveID", glsl_precision_high);
   var->data.interpolation = INTERP_QUALIFIER_FLAT;
}


/**
 * Generate variables which only exist in fragment shaders.
 */
void
builtin_variable_generator::generate_fs_special_vars()
{
   add_input(VARYING_SLOT_POS, vec4_t, "gl_FragCoord", glsl_precision_high);
   add_input(VARYING_SLOT_FACE, bool_t, "gl_FrontFacing", glsl_precision_low);
   if (state->is_version(120, 100))
	   add_input(VARYING_SLOT_PNTC, vec2_t, "gl_PointCoord", state->metal_target ? glsl_precision_high : glsl_precision_medium);

   if (state->is_version(150, 0)) {
      ir_variable *var =
         add_input(VARYING_SLOT_PRIMITIVE_ID, int_t, "gl_PrimitiveID", glsl_precision_high);
      var->data.interpolation = INTERP_QUALIFIER_FLAT;
   }

   /* gl_FragColor and gl_FragData were deprecated starting in desktop GLSL
    * 1.30, and were relegated to the compatibility profile in GLSL 4.20.
    * They were removed from GLSL ES 3.00.
    */
   if (compatibility || !state->is_version(420, 300)) {
      add_output(FRAG_RESULT_COLOR, vec4_t, "gl_FragColor", glsl_precision_medium);
      add_output(FRAG_RESULT_DATA0,
                 array(vec4_t, state->Const.MaxDrawBuffers), "gl_FragData", glsl_precision_medium);
   }

   /* gl_FragDepth has always been in desktop GLSL, but did not appear in GLSL
    * ES 1.00.
    */
   if (state->is_version(110, 300))
      add_output(FRAG_RESULT_DEPTH, float_t, "gl_FragDepth", glsl_precision_high);

   if (state->ARB_shader_stencil_export_enable) {
      ir_variable *const var =
         add_output(FRAG_RESULT_STENCIL, int_t, "gl_FragStencilRefARB", glsl_precision_high);
      if (state->ARB_shader_stencil_export_warn)
         var->enable_extension_warning("GL_ARB_shader_stencil_export");
   }

   if (state->AMD_shader_stencil_export_enable) {
      ir_variable *const var =
         add_output(FRAG_RESULT_STENCIL, int_t, "gl_FragStencilRefAMD", glsl_precision_high);
      if (state->AMD_shader_stencil_export_warn)
         var->enable_extension_warning("GL_AMD_shader_stencil_export");
   }
	
	if (state->EXT_frag_depth_enable) {
		ir_variable *const var =
		add_output(FRAG_RESULT_DEPTH, float_t, "gl_FragDepthEXT", glsl_precision_high);
		if (state->EXT_frag_depth_warn)
			var->enable_extension_warning("GL_EXT_frag_depth");
	}
	
	if (state->EXT_shader_framebuffer_fetch_enable) {
		ir_variable *const var =
			add_input(VARYING_SLOT_VAR0, array(vec4_t, state->Const.MaxDrawBuffers), "gl_LastFragData", glsl_precision_medium);
		if (state->EXT_shader_framebuffer_fetch_warn)
			var->enable_extension_warning("GL_EXT_shader_framebuffer_fetch");
	}

	{
		// BK - gl_PrimitiveID
		ir_variable *var;
		var = add_output(VARYING_SLOT_PRIMITIVE_ID, int_t, "gl_PrimitiveID", glsl_precision_high);
		var->data.interpolation = INTERP_QUALIFIER_FLAT;
	}

   if (state->ARB_sample_shading_enable) {
      add_system_value(SYSTEM_VALUE_SAMPLE_ID, int_t, "gl_SampleID", glsl_precision_high);
      add_system_value(SYSTEM_VALUE_SAMPLE_POS, vec2_t, "gl_SamplePosition", glsl_precision_high);
      /* From the ARB_sample_shading specification:
       *    "The number of elements in the array is ceil(<s>/32), where
       *    <s> is the maximum number of color samples supported by the
       *    implementation."
       * Since no drivers expose more than 32x MSAA, we can simply set
       * the array size to 1 rather than computing it.
       */
      add_output(FRAG_RESULT_SAMPLE_MASK, array(int_t, 1), "gl_SampleMask", glsl_precision_high);
   }

   if (state->ARB_gpu_shader5_enable) {
      add_system_value(SYSTEM_VALUE_SAMPLE_MASK_IN, array(int_t, 1), "gl_SampleMaskIn", glsl_precision_high);
   }

   if (state->ARB_fragment_layer_viewport_enable) {
      add_input(VARYING_SLOT_LAYER, int_t, "gl_Layer", glsl_precision_high);
      add_input(VARYING_SLOT_VIEWPORT, int_t, "gl_ViewportIndex", glsl_precision_high);
   }
}


/**
 * Generate variables which only exist in compute shaders.
 */
void
builtin_variable_generator::generate_cs_special_vars()
{
   /* TODO: finish this. */
}


/**
 * Add a single "varying" variable.  The variable's type and direction (input
 * or output) are adjusted as appropriate for the type of shader being
 * compiled.  For geometry shaders using {ARB,EXT}_geometry_shader4,
 * name_as_gs_input is used for the input (to avoid ambiguity).
 */
void
builtin_variable_generator::add_varying(int slot, const glsl_type *type,
                                        const char *name,
                                        const char *name_as_gs_input,
										glsl_precision prec)
{
   switch (state->stage) {
   case MESA_SHADER_GEOMETRY:
      this->per_vertex_in.add_field(slot, type, name, prec);
      /* FALLTHROUGH */
   case MESA_SHADER_VERTEX:
      this->per_vertex_out.add_field(slot, type, name, prec);
      break;
   case MESA_SHADER_FRAGMENT:
      add_input(slot, type, name, prec);
      break;
   case MESA_SHADER_COMPUTE:
      /* Compute shaders don't have varyings. */
      break;
   }
}


/**
 * Generate variables that are used to communicate data from one shader stage
 * to the next ("varyings").
 */
void
builtin_variable_generator::generate_varyings()
{
#define ADD_VARYING(loc, type, name, prec) \
   add_varying(loc, type, name, name "In", prec)

   /* gl_Position and gl_PointSize are not visible from fragment shaders. */
   if (state->stage != MESA_SHADER_FRAGMENT) {
      ADD_VARYING(VARYING_SLOT_POS, vec4_t, "gl_Position", glsl_precision_high);
      ADD_VARYING(VARYING_SLOT_PSIZ, float_t, "gl_PointSize", glsl_precision_high);
   }

   if (state->is_version(130, 0)) {
       ADD_VARYING(VARYING_SLOT_CLIP_DIST0, array(float_t, 0),
                   "gl_ClipDistance", glsl_precision_high);
   }

   if (compatibility) {
      ADD_VARYING(VARYING_SLOT_TEX0, array(vec4_t, 0), "gl_TexCoord", glsl_precision_undefined);
      ADD_VARYING(VARYING_SLOT_FOGC, float_t, "gl_FogFragCoord", glsl_precision_undefined);
      if (state->stage == MESA_SHADER_FRAGMENT) {
         ADD_VARYING(VARYING_SLOT_COL0, vec4_t, "gl_Color", glsl_precision_medium);
         ADD_VARYING(VARYING_SLOT_COL1, vec4_t, "gl_SecondaryColor", glsl_precision_medium);
      } else {
         ADD_VARYING(VARYING_SLOT_CLIP_VERTEX, vec4_t, "gl_ClipVertex", glsl_precision_high);
         ADD_VARYING(VARYING_SLOT_COL0, vec4_t, "gl_FrontColor", glsl_precision_medium);
         ADD_VARYING(VARYING_SLOT_BFC0, vec4_t, "gl_BackColor", glsl_precision_medium);
         ADD_VARYING(VARYING_SLOT_COL1, vec4_t, "gl_FrontSecondaryColor", glsl_precision_medium);
         ADD_VARYING(VARYING_SLOT_BFC1, vec4_t, "gl_BackSecondaryColor", glsl_precision_medium);
      }
   }

   if (state->stage == MESA_SHADER_GEOMETRY) {
      const glsl_type *per_vertex_in_type =
         this->per_vertex_in.construct_interface_instance();
      add_variable("gl_in", array(per_vertex_in_type, 0),
                   ir_var_shader_in, -1, glsl_precision_undefined);
   }
   if (state->stage == MESA_SHADER_VERTEX || state->stage == MESA_SHADER_GEOMETRY) {
      const glsl_type *per_vertex_out_type =
         this->per_vertex_out.construct_interface_instance();
      const glsl_struct_field *fields = per_vertex_out_type->fields.structure;
      for (unsigned i = 0; i < per_vertex_out_type->length; i++) {
         ir_variable *var =
            add_variable(fields[i].name, fields[i].type, ir_var_shader_out,
                         fields[i].location, fields[i].precision);
         var->data.interpolation = fields[i].interpolation;
         var->data.centroid = fields[i].centroid;
         var->data.sample = fields[i].sample;
         var->init_interface_type(per_vertex_out_type);
      }
   }
}


}; /* Anonymous namespace */


void
_mesa_glsl_initialize_variables(exec_list *instructions,
				struct _mesa_glsl_parse_state *state)
{
   builtin_variable_generator gen(instructions, state);

   gen.generate_constants();
   gen.generate_uniforms();

   gen.generate_varyings();

   switch (state->stage) {
   case MESA_SHADER_VERTEX:
      gen.generate_vs_special_vars();
      break;
   case MESA_SHADER_GEOMETRY:
      gen.generate_gs_special_vars();
      break;
   case MESA_SHADER_FRAGMENT:
      gen.generate_fs_special_vars();
      break;
   case MESA_SHADER_COMPUTE:
      gen.generate_cs_special_vars();
      break;
   }
}

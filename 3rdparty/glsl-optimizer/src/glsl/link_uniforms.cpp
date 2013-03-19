/*
 * Copyright © 2011 Intel Corporation
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

#include "main/core.h"
#include "ir.h"
#include "linker.h"
#include "ir_uniform.h"
#include "glsl_symbol_table.h"
#include "program/hash_table.h"
#include "program.h"

static inline unsigned int
align(unsigned int a, unsigned int align)
{
   return (a + align - 1) / align * align;
}

/**
 * \file link_uniforms.cpp
 * Assign locations for GLSL uniforms.
 *
 * \author Ian Romanick <ian.d.romanick@intel.com>
 */

/**
 * Count the backing storage requirements for a type
 */
static unsigned
values_for_type(const glsl_type *type)
{
   if (type->is_sampler()) {
      return 1;
   } else if (type->is_array() && type->fields.array->is_sampler()) {
      return type->array_size();
   } else {
      return type->component_slots();
   }
}

void
uniform_field_visitor::process(ir_variable *var)
{
   const glsl_type *t = var->type;

   /* Only strdup the name if we actually will need to modify it. */
   if (t->is_record() || (t->is_array() && t->fields.array->is_record())) {
      char *name = ralloc_strdup(NULL, var->name);
      recursion(var->type, &name, strlen(name));
      ralloc_free(name);
   } else {
      this->visit_field(t, var->name);
   }
}

void
uniform_field_visitor::recursion(const glsl_type *t, char **name,
				 size_t name_length)
{
   /* Records need to have each field processed individually.
    *
    * Arrays of records need to have each array element processed
    * individually, then each field of the resulting array elements processed
    * individually.
    */
   if (t->is_record()) {
      for (unsigned i = 0; i < t->length; i++) {
	 const char *field = t->fields.structure[i].name;
	 size_t new_length = name_length;

	 /* Append '.field' to the current uniform name. */
	 ralloc_asprintf_rewrite_tail(name, &new_length, ".%s", field);

	 recursion(t->fields.structure[i].type, name, new_length);
      }
   } else if (t->is_array() && t->fields.array->is_record()) {
      for (unsigned i = 0; i < t->length; i++) {
	 size_t new_length = name_length;

	 /* Append the subscript to the current uniform name */
	 ralloc_asprintf_rewrite_tail(name, &new_length, "[%u]", i);

	 recursion(t->fields.array, name, new_length);
      }
   } else {
      this->visit_field(t, *name);
   }
}

/**
 * Class to help calculate the storage requirements for a set of uniforms
 *
 * As uniforms are added to the active set the number of active uniforms and
 * the storage requirements for those uniforms are accumulated.  The active
 * uniforms are added the the hash table supplied to the constructor.
 *
 * If the same uniform is added multiple times (i.e., once for each shader
 * target), it will only be accounted once.
 */
class count_uniform_size : public uniform_field_visitor {
public:
   count_uniform_size(struct string_to_uint_map *map)
      : num_active_uniforms(0), num_values(0), num_shader_samplers(0),
	num_shader_uniform_components(0), map(map)
   {
      /* empty */
   }

   void start_shader()
   {
      this->num_shader_samplers = 0;
      this->num_shader_uniform_components = 0;
   }

   /**
    * Total number of active uniforms counted
    */
   unsigned num_active_uniforms;

   /**
    * Number of data values required to back the storage for the active uniforms
    */
   unsigned num_values;

   /**
    * Number of samplers used
    */
   unsigned num_shader_samplers;

   /**
    * Number of uniforms used in the current shader
    */
   unsigned num_shader_uniform_components;

private:
   virtual void visit_field(const glsl_type *type, const char *name)
   {
      assert(!type->is_record());
      assert(!(type->is_array() && type->fields.array->is_record()));

      /* Count the number of samplers regardless of whether the uniform is
       * already in the hash table.  The hash table prevents adding the same
       * uniform for multiple shader targets, but in this case we want to
       * count it for each shader target.
       */
      const unsigned values = values_for_type(type);
      if (type->contains_sampler()) {
	 this->num_shader_samplers +=
	    type->is_array() ? type->array_size() : 1;
      } else {
	 /* Accumulate the total number of uniform slots used by this shader.
	  * Note that samplers do not count against this limit because they
	  * don't use any storage on current hardware.
	  */
	 this->num_shader_uniform_components += values;
      }

      /* If the uniform is already in the map, there's nothing more to do.
       */
      unsigned id;
      if (this->map->get(id, name))
	 return;

      this->map->put(this->num_active_uniforms, name);

      /* Each leaf uniform occupies one entry in the list of active
       * uniforms.
       */
      this->num_active_uniforms++;
      this->num_values += values;
   }

   struct string_to_uint_map *map;
};

/**
 * Class to help parcel out pieces of backing storage to uniforms
 *
 * Each uniform processed has some range of the \c gl_constant_value
 * structures associated with it.  The association is done by finding
 * the uniform in the \c string_to_uint_map and using the value from
 * the map to connect that slot in the \c gl_uniform_storage table
 * with the next available slot in the \c gl_constant_value array.
 *
 * \warning
 * This class assumes that every uniform that will be processed is
 * already in the \c string_to_uint_map.  In addition, it assumes that
 * the \c gl_uniform_storage and \c gl_constant_value arrays are "big
 * enough."
 */
class parcel_out_uniform_storage : public uniform_field_visitor {
public:
   parcel_out_uniform_storage(struct string_to_uint_map *map,
			      struct gl_uniform_storage *uniforms,
			      union gl_constant_value *values)
      : map(map), uniforms(uniforms), next_sampler(0), values(values)
   {
      memset(this->targets, 0, sizeof(this->targets));
   }

   void start_shader()
   {
      this->shader_samplers_used = 0;
      this->shader_shadow_samplers = 0;
   }

   void set_and_process(struct gl_shader_program *prog,
			struct gl_shader *shader,
			ir_variable *var)
   {
      ubo_var = NULL;
      if (var->uniform_block != -1) {
	 struct gl_uniform_block *block =
	    &shader->UniformBlocks[var->uniform_block];

	 ubo_block_index = -1;
	 for (unsigned i = 0; i < prog->NumUniformBlocks; i++) {
	    if (!strcmp(prog->UniformBlocks[i].Name,
			shader->UniformBlocks[var->uniform_block].Name)) {
	       ubo_block_index = i;
	       break;
	    }
	 }
	 assert(ubo_block_index != -1);

	 ubo_var_index = var->location;
	 ubo_var = &block->Uniforms[var->location];
	 ubo_byte_offset = ubo_var->Offset;
      }

      process(var);
   }

   struct gl_uniform_buffer_variable *ubo_var;
   int ubo_block_index;
   int ubo_var_index;
   int ubo_byte_offset;

private:
   virtual void visit_field(const glsl_type *type, const char *name)
   {
      assert(!type->is_record());
      assert(!(type->is_array() && type->fields.array->is_record()));

      unsigned id;
      bool found = this->map->get(id, name);
      assert(found);

      if (!found)
	 return;

      /* If there is already storage associated with this uniform, it means
       * that it was set while processing an earlier shader stage.  For
       * example, we may be processing the uniform in the fragment shader, but
       * the uniform was already processed in the vertex shader.
       */
      if (this->uniforms[id].storage != NULL) {
	 /* If the uniform already has storage set from another shader stage,
	  * mark the samplers used for this shader stage.
	  */
	 if (type->contains_sampler()) {
	    const unsigned count = MAX2(1, this->uniforms[id].array_elements);
	    const unsigned shadow = (type->is_array())
	       ? type->fields.array->sampler_shadow : type->sampler_shadow;

	    for (unsigned i = 0; i < count; i++) {
	       const unsigned s = this->uniforms[id].sampler + i;

	       this->shader_samplers_used |= 1U << s;
	       this->shader_shadow_samplers |= shadow << s;
	    }
	 }

	 return;
      }

      const glsl_type *base_type;
      if (type->is_array()) {
	 this->uniforms[id].array_elements = type->length;
	 base_type = type->fields.array;
      } else {
	 this->uniforms[id].array_elements = 0;
	 base_type = type;
      }

      if (base_type->is_sampler()) {
	 this->uniforms[id].sampler = this->next_sampler;

	 /* Increment the sampler by 1 for non-arrays and by the number of
	  * array elements for arrays.
	  */
	 this->next_sampler += MAX2(1, this->uniforms[id].array_elements);

	 const gl_texture_index target = base_type->sampler_index();
	 const unsigned shadow = base_type->sampler_shadow;
	 for (unsigned i = this->uniforms[id].sampler
		 ; i < MIN2(this->next_sampler, MAX_SAMPLERS)
		 ; i++) {
	    this->targets[i] = target;
	    this->shader_samplers_used |= 1U << i;
	    this->shader_shadow_samplers |= shadow << i;
	 }

      } else {
	 this->uniforms[id].sampler = ~0;
      }

      this->uniforms[id].name = ralloc_strdup(this->uniforms, name);
      this->uniforms[id].type = base_type;
      this->uniforms[id].initialized = 0;
      this->uniforms[id].num_driver_storage = 0;
      this->uniforms[id].driver_storage = NULL;
      this->uniforms[id].storage = this->values;
      if (this->ubo_var) {
	 this->uniforms[id].block_index = this->ubo_block_index;

	 unsigned alignment = type->std140_base_alignment(!!ubo_var->RowMajor);
	 this->ubo_byte_offset = align(this->ubo_byte_offset, alignment);
	 this->uniforms[id].offset = this->ubo_byte_offset;
	 this->ubo_byte_offset += type->std140_size(!!ubo_var->RowMajor);

	 if (type->is_array()) {
	    this->uniforms[id].array_stride =
	       align(type->fields.array->std140_size(!!ubo_var->RowMajor), 16);
	 } else {
	    this->uniforms[id].array_stride = 0;
	 }

	 if (type->is_matrix() ||
	     (type->is_array() && type->fields.array->is_matrix())) {
	    this->uniforms[id].matrix_stride = 16;
	    this->uniforms[id].row_major = !!ubo_var->RowMajor;
	 } else {
	    this->uniforms[id].matrix_stride = 0;
	    this->uniforms[id].row_major = false;
	 }
      } else {
	 this->uniforms[id].block_index = -1;
	 this->uniforms[id].offset = -1;
	 this->uniforms[id].array_stride = -1;
	 this->uniforms[id].matrix_stride = -1;
	 this->uniforms[id].row_major = false;
      }

      this->values += values_for_type(type);
   }

   struct string_to_uint_map *map;

   struct gl_uniform_storage *uniforms;
   unsigned next_sampler;

public:
   union gl_constant_value *values;

   gl_texture_index targets[MAX_SAMPLERS];

   /**
    * Mask of samplers used by the current shader stage.
    */
   unsigned shader_samplers_used;

   /**
    * Mask of samplers used by the current shader stage for shadows.
    */
   unsigned shader_shadow_samplers;
};

/**
 * Merges a uniform block into an array of uniform blocks that may or
 * may not already contain a copy of it.
 *
 * Returns the index of the new block in the array.
 */
int
link_cross_validate_uniform_block(void *mem_ctx,
				  struct gl_uniform_block **linked_blocks,
				  unsigned int *num_linked_blocks,
				  struct gl_uniform_block *new_block)
{
   for (unsigned int i = 0; i < *num_linked_blocks; i++) {
      struct gl_uniform_block *old_block = &(*linked_blocks)[i];
      if (strcmp(old_block->Name, new_block->Name) == 0) {
	 if (old_block->NumUniforms != new_block->NumUniforms) {
	    return -1;
	 }

	 for (unsigned j = 0; j < old_block->NumUniforms; j++) {
	    if (strcmp(old_block->Uniforms[j].Name,
		       new_block->Uniforms[j].Name) != 0)
	       return -1;

	    if (old_block->Uniforms[j].Offset !=
		new_block->Uniforms[j].Offset)
	       return -1;

	    if (old_block->Uniforms[j].RowMajor !=
		new_block->Uniforms[j].RowMajor)
	       return -1;
	 }
	 return i;
      }
   }

   *linked_blocks = reralloc(mem_ctx, *linked_blocks,
			     struct gl_uniform_block,
			     *num_linked_blocks + 1);
   int linked_block_index = (*num_linked_blocks)++;
   struct gl_uniform_block *linked_block = &(*linked_blocks)[linked_block_index];

   memcpy(linked_block, new_block, sizeof(*new_block));
   linked_block->Uniforms = ralloc_array(*linked_blocks,
					 struct gl_uniform_buffer_variable,
					 linked_block->NumUniforms);

   memcpy(linked_block->Uniforms,
	  new_block->Uniforms,
	  sizeof(*linked_block->Uniforms) * linked_block->NumUniforms);

   for (unsigned int i = 0; i < linked_block->NumUniforms; i++) {
      struct gl_uniform_buffer_variable *ubo_var =
	 &linked_block->Uniforms[i];

      ubo_var->Name = ralloc_strdup(*linked_blocks, ubo_var->Name);
   }

   return linked_block_index;
}

/**
 * Walks the IR and update the references to uniform blocks in the
 * ir_variables to point at linked shader's list (previously, they
 * would point at the uniform block list in one of the pre-linked
 * shaders).
 */
static bool
link_update_uniform_buffer_variables(struct gl_shader *shader)
{
   foreach_list(node, shader->ir) {
      ir_variable *const var = ((ir_instruction *) node)->as_variable();

      if ((var == NULL) || (var->uniform_block == -1))
	 continue;

      assert(var->mode == ir_var_uniform);

      bool found = false;
      for (unsigned i = 0; i < shader->NumUniformBlocks; i++) {
	 for (unsigned j = 0; j < shader->UniformBlocks[i].NumUniforms; j++) {
	    if (!strcmp(var->name, shader->UniformBlocks[i].Uniforms[j].Name)) {
	       found = true;
	       var->uniform_block = i;
	       var->location = j;
	       break;
	    }
	 }
	 if (found)
	    break;
      }
      assert(found);
   }

   return true;
}

void
link_assign_uniform_block_offsets(struct gl_shader *shader)
{
   for (unsigned b = 0; b < shader->NumUniformBlocks; b++) {
      struct gl_uniform_block *block = &shader->UniformBlocks[b];

      unsigned offset = 0;
      for (unsigned int i = 0; i < block->NumUniforms; i++) {
	 struct gl_uniform_buffer_variable *ubo_var = &block->Uniforms[i];
	 const struct glsl_type *type = ubo_var->Type;

	 unsigned alignment = type->std140_base_alignment(!!ubo_var->RowMajor);
	 unsigned size = type->std140_size(!!ubo_var->RowMajor);

	 offset = align(offset, alignment);
	 ubo_var->Offset = offset;
	 offset += size;
      }

      /* From the GL_ARB_uniform_buffer_object spec:
       *
       *     "For uniform blocks laid out according to [std140] rules,
       *      the minimum buffer object size returned by the
       *      UNIFORM_BLOCK_DATA_SIZE query is derived by taking the
       *      offset of the last basic machine unit consumed by the
       *      last uniform of the uniform block (including any
       *      end-of-array or end-of-structure padding), adding one,
       *      and rounding up to the next multiple of the base
       *      alignment required for a vec4."
       */
      block->UniformBufferSize = align(offset, 16);
   }
}

void
link_assign_uniform_locations(struct gl_shader_program *prog)
{
   ralloc_free(prog->UniformStorage);
   prog->UniformStorage = NULL;
   prog->NumUserUniformStorage = 0;

   if (prog->UniformHash != NULL) {
      prog->UniformHash->clear();
   } else {
      prog->UniformHash = new string_to_uint_map;
   }

   /* Uniforms that lack an initializer in the shader code have an initial
    * value of zero.  This includes sampler uniforms.
    *
    * Page 24 (page 30 of the PDF) of the GLSL 1.20 spec says:
    *
    *     "The link time initial value is either the value of the variable's
    *     initializer, if present, or 0 if no initializer is present. Sampler
    *     types cannot have initializers."
    */
   memset(prog->SamplerUnits, 0, sizeof(prog->SamplerUnits));

   for (unsigned i = 0; i < MESA_SHADER_TYPES; i++) {
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      if (!link_update_uniform_buffer_variables(prog->_LinkedShaders[i]))
	 return;
   }

   /* First pass: Count the uniform resources used by the user-defined
    * uniforms.  While this happens, each active uniform will have an index
    * assigned to it.
    *
    * Note: this is *NOT* the index that is returned to the application by
    * glGetUniformLocation.
    */
   count_uniform_size uniform_size(prog->UniformHash);
   for (unsigned i = 0; i < MESA_SHADER_TYPES; i++) {
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      /* Reset various per-shader target counts.
       */
      uniform_size.start_shader();

      foreach_list(node, prog->_LinkedShaders[i]->ir) {
	 ir_variable *const var = ((ir_instruction *) node)->as_variable();

	 if ((var == NULL) || (var->mode != ir_var_uniform))
	    continue;

	 /* FINISHME: Update code to process built-in uniforms!
	  */
	 if (strncmp("gl_", var->name, 3) == 0) {
	    uniform_size.num_shader_uniform_components +=
	       var->type->component_slots();
	    continue;
	 }

	 uniform_size.process(var);
      }

      prog->_LinkedShaders[i]->num_samplers = uniform_size.num_shader_samplers;
      prog->_LinkedShaders[i]->num_uniform_components =
	 uniform_size.num_shader_uniform_components;
   }

   const unsigned num_user_uniforms = uniform_size.num_active_uniforms;
   const unsigned num_data_slots = uniform_size.num_values;

   /* On the outside chance that there were no uniforms, bail out.
    */
   if (num_user_uniforms == 0)
      return;

   struct gl_uniform_storage *uniforms =
      rzalloc_array(prog, struct gl_uniform_storage, num_user_uniforms);
   union gl_constant_value *data =
      rzalloc_array(uniforms, union gl_constant_value, num_data_slots);
#ifndef NDEBUG
   union gl_constant_value *data_end = &data[num_data_slots];
#endif

   parcel_out_uniform_storage parcel(prog->UniformHash, uniforms, data);

   for (unsigned i = 0; i < MESA_SHADER_TYPES; i++) {
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      /* Reset various per-shader target counts.
       */
      parcel.start_shader();

      foreach_list(node, prog->_LinkedShaders[i]->ir) {
	 ir_variable *const var = ((ir_instruction *) node)->as_variable();

	 if ((var == NULL) || (var->mode != ir_var_uniform))
	    continue;

	 /* FINISHME: Update code to process built-in uniforms!
	  */
	 if (strncmp("gl_", var->name, 3) == 0)
	    continue;

	 parcel.set_and_process(prog, prog->_LinkedShaders[i], var);
      }

      prog->_LinkedShaders[i]->active_samplers = parcel.shader_samplers_used;
      prog->_LinkedShaders[i]->shadow_samplers = parcel.shader_shadow_samplers;
   }

   assert(sizeof(prog->SamplerTargets) == sizeof(parcel.targets));
   memcpy(prog->SamplerTargets, parcel.targets, sizeof(prog->SamplerTargets));

#ifndef NDEBUG
   for (unsigned i = 0; i < num_user_uniforms; i++) {
      assert(uniforms[i].storage != NULL);
   }

   assert(parcel.values == data_end);
#endif

   prog->NumUserUniformStorage = num_user_uniforms;
   prog->UniformStorage = uniforms;

   link_set_uniform_initializers(prog);

   return;
}

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
program_resource_visitor::process(const glsl_type *type, const char *name)
{
   assert(type->is_record()
          || (type->is_array() && type->fields.array->is_record())
          || type->is_interface()
          || (type->is_array() && type->fields.array->is_interface()));

   char *name_copy = ralloc_strdup(NULL, name);
   recursion(type, &name_copy, strlen(name), false, NULL);
   ralloc_free(name_copy);
}

void
program_resource_visitor::process(ir_variable *var)
{
   const glsl_type *t = var->type;

   /* false is always passed for the row_major parameter to the other
    * processing functions because no information is available to do
    * otherwise.  See the warning in linker.h.
    */

   /* Only strdup the name if we actually will need to modify it. */
   if (var->data.from_named_ifc_block_array) {
      /* lower_named_interface_blocks created this variable by lowering an
       * interface block array to an array variable.  For example if the
       * original source code was:
       *
       *     out Blk { vec4 bar } foo[3];
       *
       * Then the variable is now:
       *
       *     out vec4 bar[3];
       *
       * We need to visit each array element using the names constructed like
       * so:
       *
       *     Blk[0].bar
       *     Blk[1].bar
       *     Blk[2].bar
       */
      assert(t->is_array());
      const glsl_type *ifc_type = var->get_interface_type();
      char *name = ralloc_strdup(NULL, ifc_type->name);
      size_t name_length = strlen(name);
      for (unsigned i = 0; i < t->length; i++) {
         size_t new_length = name_length;
         ralloc_asprintf_rewrite_tail(&name, &new_length, "[%u].%s", i,
                                      var->name);
         /* Note: row_major is only meaningful for uniform blocks, and
          * lowering is only applied to non-uniform interface blocks, so we
          * can safely pass false for row_major.
          */
         recursion(var->type, &name, new_length, false, NULL);
      }
      ralloc_free(name);
   } else if (var->data.from_named_ifc_block_nonarray) {
      /* lower_named_interface_blocks created this variable by lowering a
       * named interface block (non-array) to an ordinary variable.  For
       * example if the original source code was:
       *
       *     out Blk { vec4 bar } foo;
       *
       * Then the variable is now:
       *
       *     out vec4 bar;
       *
       * We need to visit this variable using the name:
       *
       *     Blk.bar
       */
      const glsl_type *ifc_type = var->get_interface_type();
      char *name = ralloc_asprintf(NULL, "%s.%s", ifc_type->name, var->name);
      /* Note: row_major is only meaningful for uniform blocks, and lowering
       * is only applied to non-uniform interface blocks, so we can safely
       * pass false for row_major.
       */
      recursion(var->type, &name, strlen(name), false, NULL);
      ralloc_free(name);
   } else if (t->is_record() || (t->is_array() && t->fields.array->is_record())) {
      char *name = ralloc_strdup(NULL, var->name);
      recursion(var->type, &name, strlen(name), false, NULL);
      ralloc_free(name);
   } else if (t->is_interface()) {
      char *name = ralloc_strdup(NULL, var->type->name);
      recursion(var->type, &name, strlen(name), false, NULL);
      ralloc_free(name);
   } else if (t->is_array() && t->fields.array->is_interface()) {
      char *name = ralloc_strdup(NULL, var->type->fields.array->name);
      recursion(var->type, &name, strlen(name), false, NULL);
      ralloc_free(name);
   } else {
      this->visit_field(t, var->name, false, NULL);
   }
}

void
program_resource_visitor::recursion(const glsl_type *t, char **name,
                                    size_t name_length, bool row_major,
                                    const glsl_type *record_type)
{
   /* Records need to have each field processed individually.
    *
    * Arrays of records need to have each array element processed
    * individually, then each field of the resulting array elements processed
    * individually.
    */
   if (t->is_record() || t->is_interface()) {
      if (record_type == NULL && t->is_record())
         record_type = t;

      for (unsigned i = 0; i < t->length; i++) {
	 const char *field = t->fields.structure[i].name;
	 size_t new_length = name_length;

         if (t->fields.structure[i].type->is_record())
            this->visit_field(&t->fields.structure[i]);

         /* Append '.field' to the current variable name. */
         if (name_length == 0) {
            ralloc_asprintf_rewrite_tail(name, &new_length, "%s", field);
         } else {
            ralloc_asprintf_rewrite_tail(name, &new_length, ".%s", field);
         }

         recursion(t->fields.structure[i].type, name, new_length,
                   t->fields.structure[i].row_major, record_type);

         /* Only the first leaf-field of the record gets called with the
          * record type pointer.
          */
         record_type = NULL;
      }
   } else if (t->is_array() && (t->fields.array->is_record()
                                || t->fields.array->is_interface())) {
      if (record_type == NULL && t->fields.array->is_record())
         record_type = t->fields.array;

      for (unsigned i = 0; i < t->length; i++) {
	 size_t new_length = name_length;

	 /* Append the subscript to the current variable name */
	 ralloc_asprintf_rewrite_tail(name, &new_length, "[%u]", i);

         recursion(t->fields.array, name, new_length, row_major,
                   record_type);

         /* Only the first leaf-field of the record gets called with the
          * record type pointer.
          */
         record_type = NULL;
      }
   } else {
      this->visit_field(t, *name, row_major, record_type);
   }
}

void
program_resource_visitor::visit_field(const glsl_type *type, const char *name,
                                      bool row_major,
                                      const glsl_type *record_type)
{
   visit_field(type, name, row_major);
}

void
program_resource_visitor::visit_field(const glsl_struct_field *field)
{
   (void) field;
   /* empty */
}

namespace {

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
class count_uniform_size : public program_resource_visitor {
public:
   count_uniform_size(struct string_to_uint_map *map)
      : num_active_uniforms(0), num_values(0), num_shader_samplers(0),
        num_shader_images(0), num_shader_uniform_components(0),
        is_ubo_var(false), map(map)
   {
      /* empty */
   }

   void start_shader()
   {
      this->num_shader_samplers = 0;
      this->num_shader_images = 0;
      this->num_shader_uniform_components = 0;
   }

   void process(ir_variable *var)
   {
      this->is_ubo_var = var->is_in_uniform_block();
      if (var->is_interface_instance())
         program_resource_visitor::process(var->get_interface_type(),
                                           var->get_interface_type()->name);
      else
         program_resource_visitor::process(var);
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
    * Number of images used
    */
   unsigned num_shader_images;

   /**
    * Number of uniforms used in the current shader
    */
   unsigned num_shader_uniform_components;

   bool is_ubo_var;

private:
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      assert(!type->is_record());
      assert(!(type->is_array() && type->fields.array->is_record()));
      assert(!type->is_interface());
      assert(!(type->is_array() && type->fields.array->is_interface()));

      (void) row_major;

      /* Count the number of samplers regardless of whether the uniform is
       * already in the hash table.  The hash table prevents adding the same
       * uniform for multiple shader targets, but in this case we want to
       * count it for each shader target.
       */
      const unsigned values = values_for_type(type);
      if (type->contains_sampler()) {
	 this->num_shader_samplers +=
	    type->is_array() ? type->array_size() : 1;
      } else if (type->contains_image()) {
         this->num_shader_images += values;

         /* As drivers are likely to represent image uniforms as
          * scalar indices, count them against the limit of uniform
          * components in the default block.  The spec allows image
          * uniforms to use up no more than one scalar slot.
          */
         this->num_shader_uniform_components += values;
      } else {
	 /* Accumulate the total number of uniform slots used by this shader.
	  * Note that samplers do not count against this limit because they
	  * don't use any storage on current hardware.
	  */
	 if (!is_ubo_var)
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

} /* anonymous namespace */

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
class parcel_out_uniform_storage : public program_resource_visitor {
public:
   parcel_out_uniform_storage(struct string_to_uint_map *map,
			      struct gl_uniform_storage *uniforms,
			      union gl_constant_value *values)
      : map(map), uniforms(uniforms), values(values)
   {
   }

   void start_shader(gl_shader_stage shader_type)
   {
      assert(shader_type < MESA_SHADER_STAGES);
      this->shader_type = shader_type;

      this->shader_samplers_used = 0;
      this->shader_shadow_samplers = 0;
      this->next_sampler = 0;
      this->next_image = 0;
      memset(this->targets, 0, sizeof(this->targets));
   }

   void set_and_process(struct gl_shader_program *prog,
			ir_variable *var)
   {
      ubo_block_index = -1;
      if (var->is_in_uniform_block()) {
         if (var->is_interface_instance() && var->type->is_array()) {
            unsigned l = strlen(var->get_interface_type()->name);

            for (unsigned i = 0; i < prog->NumUniformBlocks; i++) {
               if (strncmp(var->get_interface_type()->name,
                           prog->UniformBlocks[i].Name,
                           l) == 0
                   && prog->UniformBlocks[i].Name[l] == '[') {
                  ubo_block_index = i;
                  break;
               }
            }
         } else {
            for (unsigned i = 0; i < prog->NumUniformBlocks; i++) {
               if (strcmp(var->get_interface_type()->name,
                          prog->UniformBlocks[i].Name) == 0) {
                  ubo_block_index = i;
                  break;
               }
	    }
	 }
	 assert(ubo_block_index != -1);

         /* Uniform blocks that were specified with an instance name must be
          * handled a little bit differently.  The name of the variable is the
          * name used to reference the uniform block instead of being the name
          * of a variable within the block.  Therefore, searching for the name
          * within the block will fail.
          */
         if (var->is_interface_instance()) {
            ubo_byte_offset = 0;
            ubo_row_major = false;
         } else {
            const struct gl_uniform_block *const block =
               &prog->UniformBlocks[ubo_block_index];

            assert(var->data.location != -1);

            const struct gl_uniform_buffer_variable *const ubo_var =
               &block->Uniforms[var->data.location];

            ubo_row_major = !!ubo_var->RowMajor;
            ubo_byte_offset = ubo_var->Offset;
         }

         if (var->is_interface_instance())
            process(var->get_interface_type(),
                    var->get_interface_type()->name);
         else
            process(var);
      } else
         process(var);
   }

   int ubo_block_index;
   int ubo_byte_offset;
   bool ubo_row_major;
   gl_shader_stage shader_type;

private:
   void handle_samplers(const glsl_type *base_type,
                        struct gl_uniform_storage *uniform)
   {
      if (base_type->is_sampler()) {
         uniform->sampler[shader_type].index = this->next_sampler;
         uniform->sampler[shader_type].active = true;

         /* Increment the sampler by 1 for non-arrays and by the number of
          * array elements for arrays.
          */
         this->next_sampler +=
               MAX2(1, uniform->array_elements);

         const gl_texture_index target = base_type->sampler_index();
         const unsigned shadow = base_type->sampler_shadow;
         for (unsigned i = uniform->sampler[shader_type].index;
              i < MIN2(this->next_sampler, MAX_SAMPLERS);
              i++) {
            this->targets[i] = target;
            this->shader_samplers_used |= 1U << i;
            this->shader_shadow_samplers |= shadow << i;
         }
      } else {
         uniform->sampler[shader_type].index = ~0;
         uniform->sampler[shader_type].active = false;
      }
   }

   void handle_images(const glsl_type *base_type,
                      struct gl_uniform_storage *uniform)
   {
      if (base_type->is_image()) {
         uniform->image[shader_type].index = this->next_image;
         uniform->image[shader_type].active = true;

         /* Increment the image index by 1 for non-arrays and by the
          * number of array elements for arrays.
          */
         this->next_image += MAX2(1, uniform->array_elements);

      } else {
         uniform->image[shader_type].index = ~0;
         uniform->image[shader_type].active = false;
      }
   }

   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      (void) type;
      (void) name;
      (void) row_major;
      assert(!"Should not get here.");
   }

   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major, const glsl_type *record_type)
   {
      assert(!type->is_record());
      assert(!(type->is_array() && type->fields.array->is_record()));
      assert(!type->is_interface());
      assert(!(type->is_array() && type->fields.array->is_interface()));

      (void) row_major;

      unsigned id;
      bool found = this->map->get(id, name);
      assert(found);

      if (!found)
	 return;

      const glsl_type *base_type;
      if (type->is_array()) {
	 this->uniforms[id].array_elements = type->length;
	 base_type = type->fields.array;
      } else {
	 this->uniforms[id].array_elements = 0;
	 base_type = type;
      }

      /* This assigns uniform indices to sampler and image uniforms. */
      handle_samplers(base_type, &this->uniforms[id]);
      handle_images(base_type, &this->uniforms[id]);

      /* If there is already storage associated with this uniform, it means
       * that it was set while processing an earlier shader stage.  For
       * example, we may be processing the uniform in the fragment shader, but
       * the uniform was already processed in the vertex shader.
       */
      if (this->uniforms[id].storage != NULL) {
         return;
      }

      this->uniforms[id].name = ralloc_strdup(this->uniforms, name);
      this->uniforms[id].type = base_type;
      this->uniforms[id].initialized = 0;
      this->uniforms[id].num_driver_storage = 0;
      this->uniforms[id].driver_storage = NULL;
      this->uniforms[id].storage = this->values;
      this->uniforms[id].atomic_buffer_index = -1;
      if (this->ubo_block_index != -1) {
	 this->uniforms[id].block_index = this->ubo_block_index;

	 const unsigned alignment = record_type
	    ? record_type->std140_base_alignment(ubo_row_major)
	    : type->std140_base_alignment(ubo_row_major);
	 this->ubo_byte_offset = glsl_align(this->ubo_byte_offset, alignment);
	 this->uniforms[id].offset = this->ubo_byte_offset;
	 this->ubo_byte_offset += type->std140_size(ubo_row_major);

	 if (type->is_array()) {
	    this->uniforms[id].array_stride =
	       glsl_align(type->fields.array->std140_size(ubo_row_major), 16);
	 } else {
	    this->uniforms[id].array_stride = 0;
	 }

	 if (type->is_matrix() ||
	     (type->is_array() && type->fields.array->is_matrix())) {
	    this->uniforms[id].matrix_stride = 16;
	    this->uniforms[id].row_major = ubo_row_major;
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
   unsigned next_image;

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

      if (strcmp(old_block->Name, new_block->Name) == 0)
	 return link_uniform_blocks_are_compatible(old_block, new_block)
	    ? i : -1;
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

      if (ubo_var->Name == ubo_var->IndexName) {
         ubo_var->Name = ralloc_strdup(*linked_blocks, ubo_var->Name);
         ubo_var->IndexName = ubo_var->Name;
      } else {
         ubo_var->Name = ralloc_strdup(*linked_blocks, ubo_var->Name);
         ubo_var->IndexName = ralloc_strdup(*linked_blocks, ubo_var->IndexName);
      }
   }

   return linked_block_index;
}

/**
 * Walks the IR and update the references to uniform blocks in the
 * ir_variables to point at linked shader's list (previously, they
 * would point at the uniform block list in one of the pre-linked
 * shaders).
 */
static void
link_update_uniform_buffer_variables(struct gl_shader *shader)
{
   foreach_list(node, shader->ir) {
      ir_variable *const var = ((ir_instruction *) node)->as_variable();

      if ((var == NULL) || !var->is_in_uniform_block())
	 continue;

      assert(var->data.mode == ir_var_uniform);

      if (var->is_interface_instance()) {
         var->data.location = 0;
         continue;
      }

      bool found = false;
      char sentinel = '\0';

      if (var->type->is_record()) {
         sentinel = '.';
      } else if (var->type->is_array()
                 && var->type->fields.array->is_record()) {
         sentinel = '[';
      }

      const unsigned l = strlen(var->name);
      for (unsigned i = 0; i < shader->NumUniformBlocks; i++) {
	 for (unsigned j = 0; j < shader->UniformBlocks[i].NumUniforms; j++) {
            if (sentinel) {
               const char *begin = shader->UniformBlocks[i].Uniforms[j].Name;
               const char *end = strchr(begin, sentinel);

               if (end == NULL)
                  continue;

               if (l != (end - begin))
                  continue;

               if (strncmp(var->name, begin, l) == 0) {
                  found = true;
                  var->data.location = j;
                  break;
               }
            } else if (!strcmp(var->name,
                               shader->UniformBlocks[i].Uniforms[j].Name)) {
	       found = true;
	       var->data.location = j;
	       break;
	    }
	 }
	 if (found)
	    break;
      }
      assert(found);
   }
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

	 offset = glsl_align(offset, alignment);
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
      block->UniformBufferSize = glsl_align(offset, 16);
   }
}

/**
 * Scan the program for image uniforms and store image unit access
 * information into the gl_shader data structure.
 */
static void
link_set_image_access_qualifiers(struct gl_shader_program *prog)
{
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      gl_shader *sh = prog->_LinkedShaders[i];

      if (sh == NULL)
	 continue;

      foreach_list(node, sh->ir) {
	 ir_variable *var = ((ir_instruction *) node)->as_variable();

         if (var && var->data.mode == ir_var_uniform &&
             var->type->contains_image()) {
            unsigned id;
            bool found = prog->UniformHash->get(id, var->name);
            assert(found);
            const gl_uniform_storage *storage = &prog->UniformStorage[id];
            const unsigned index = storage->image[i].index;
            const GLenum access = (var->data.image.read_only ? GL_READ_ONLY :
                                   var->data.image.write_only ? GL_WRITE_ONLY :
                                   GL_READ_WRITE);

            for (unsigned j = 0; j < MAX2(1, storage->array_elements); ++j)
               sh->ImageAccess[index + j] = access;
         }
      }
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

   /* First pass: Count the uniform resources used by the user-defined
    * uniforms.  While this happens, each active uniform will have an index
    * assigned to it.
    *
    * Note: this is *NOT* the index that is returned to the application by
    * glGetUniformLocation.
    */
   count_uniform_size uniform_size(prog->UniformHash);
   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      struct gl_shader *sh = prog->_LinkedShaders[i];

      if (sh == NULL)
	 continue;

      /* Uniforms that lack an initializer in the shader code have an initial
       * value of zero.  This includes sampler uniforms.
       *
       * Page 24 (page 30 of the PDF) of the GLSL 1.20 spec says:
       *
       *     "The link time initial value is either the value of the variable's
       *     initializer, if present, or 0 if no initializer is present. Sampler
       *     types cannot have initializers."
       */
      memset(sh->SamplerUnits, 0, sizeof(sh->SamplerUnits));
      memset(sh->ImageUnits, 0, sizeof(sh->ImageUnits));

      link_update_uniform_buffer_variables(sh);

      /* Reset various per-shader target counts.
       */
      uniform_size.start_shader();

      foreach_list(node, sh->ir) {
	 ir_variable *const var = ((ir_instruction *) node)->as_variable();

	 if ((var == NULL) || (var->data.mode != ir_var_uniform))
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

      sh->num_samplers = uniform_size.num_shader_samplers;
      sh->NumImages = uniform_size.num_shader_images;
      sh->num_uniform_components = uniform_size.num_shader_uniform_components;

      sh->num_combined_uniform_components = sh->num_uniform_components;
      for (unsigned i = 0; i < sh->NumUniformBlocks; i++) {
	 sh->num_combined_uniform_components +=
	    sh->UniformBlocks[i].UniformBufferSize / 4;
      }
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

   for (unsigned i = 0; i < MESA_SHADER_STAGES; i++) {
      if (prog->_LinkedShaders[i] == NULL)
	 continue;

      parcel.start_shader((gl_shader_stage)i);

      foreach_list(node, prog->_LinkedShaders[i]->ir) {
	 ir_variable *const var = ((ir_instruction *) node)->as_variable();

	 if ((var == NULL) || (var->data.mode != ir_var_uniform))
	    continue;

	 /* FINISHME: Update code to process built-in uniforms!
	  */
	 if (strncmp("gl_", var->name, 3) == 0)
	    continue;

	 parcel.set_and_process(prog, var);
      }

      prog->_LinkedShaders[i]->active_samplers = parcel.shader_samplers_used;
      prog->_LinkedShaders[i]->shadow_samplers = parcel.shader_shadow_samplers;

      STATIC_ASSERT(sizeof(prog->_LinkedShaders[i]->SamplerTargets) == sizeof(parcel.targets));
      memcpy(prog->_LinkedShaders[i]->SamplerTargets, parcel.targets,
             sizeof(prog->_LinkedShaders[i]->SamplerTargets));
   }

   /* Determine the size of the largest uniform array queryable via
    * glGetUniformLocation.  Using this as the location scale guarantees that
    * there is enough "room" for the array index to be stored in the low order
    * part of the uniform location.  It also makes the locations be more
    * tightly packed.
    */
   unsigned max_array_size = 1;
   for (unsigned i = 0; i < num_user_uniforms; i++) {
      if (uniforms[i].array_elements > max_array_size)
         max_array_size = uniforms[i].array_elements;
   }

   prog->UniformLocationBaseScale = max_array_size;

#ifndef NDEBUG
   for (unsigned i = 0; i < num_user_uniforms; i++) {
      assert(uniforms[i].storage != NULL);
   }

   assert(parcel.values == data_end);
#endif

   prog->NumUserUniformStorage = num_user_uniforms;
   prog->UniformStorage = uniforms;

   link_set_image_access_qualifiers(prog);
   link_set_uniform_initializers(prog);

   return;
}

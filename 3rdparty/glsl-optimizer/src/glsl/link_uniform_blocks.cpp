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

#include "main/core.h"
#include "main/errors.h"
#include "ir.h"
#include "linker.h"
#include "ir_uniform.h"
#include "link_uniform_block_active_visitor.h"
#include "util/hash_table.h"
#include "program.h"

namespace {

class ubo_visitor : public program_resource_visitor {
public:
   ubo_visitor(void *mem_ctx, gl_uniform_buffer_variable *variables,
               unsigned num_variables)
      : index(0), offset(0), buffer_size(0), variables(variables),
        num_variables(num_variables), mem_ctx(mem_ctx), is_array_instance(false)
   {
      /* empty */
   }

   void process(const glsl_type *type, const char *name)
   {
      this->offset = 0;
      this->buffer_size = 0;
      this->is_array_instance = strchr(name, ']') != NULL;
      this->program_resource_visitor::process(type, name);
   }

   unsigned index;
   unsigned offset;
   unsigned buffer_size;
   gl_uniform_buffer_variable *variables;
   unsigned num_variables;
   void *mem_ctx;
   bool is_array_instance;

private:
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      (void) type;
      (void) name;
      (void) row_major;
      assert(!"Should not get here.");
   }

   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major, const glsl_type *record_type,
                            bool last_field)
   {
      assert(this->index < this->num_variables);

      gl_uniform_buffer_variable *v = &this->variables[this->index++];

      v->Name = ralloc_strdup(mem_ctx, name);
      v->Type = type;
      v->RowMajor = type->without_array()->is_matrix() && row_major;

      if (this->is_array_instance) {
         v->IndexName = ralloc_strdup(mem_ctx, name);

         char *open_bracket = strchr(v->IndexName, '[');
         assert(open_bracket != NULL);

         char *close_bracket = strchr(open_bracket, ']');
         assert(close_bracket != NULL);

         /* Length of the tail without the ']' but with the NUL.
          */
         unsigned len = strlen(close_bracket + 1) + 1;

         memmove(open_bracket, close_bracket + 1, len);
      } else {
         v->IndexName = v->Name;
      }

      const unsigned alignment = record_type
         ? record_type->std140_base_alignment(!!v->RowMajor)
         : type->std140_base_alignment(!!v->RowMajor);
      unsigned size = type->std140_size(!!v->RowMajor);

      this->offset = glsl_align(this->offset, alignment);
      v->Offset = this->offset;

      /* If this is the last field of a structure, apply rule #9.  The
       * GL_ARB_uniform_buffer_object spec says:
       *
       *     "The structure may have padding at the end; the base offset of
       *     the member following the sub-structure is rounded up to the next
       *     multiple of the base alignment of the structure."
       *
       * last_field won't be set if this is the last field of a UBO that is
       * not a named instance.
       */
      this->offset += size;
      if (last_field)
         this->offset = glsl_align(this->offset, 16);

      /* From the GL_ARB_uniform_buffer_object spec:
       *
       *     "For uniform blocks laid out according to [std140] rules, the
       *      minimum buffer object size returned by the
       *      UNIFORM_BLOCK_DATA_SIZE query is derived by taking the offset of
       *      the last basic machine unit consumed by the last uniform of the
       *      uniform block (including any end-of-array or end-of-structure
       *      padding), adding one, and rounding up to the next multiple of
       *      the base alignment required for a vec4."
       */
      this->buffer_size = glsl_align(this->offset, 16);
   }

   virtual void visit_field(const glsl_struct_field *field)
   {
      /* FINISHME: When support for doubles (dvec4, etc.) is added to the
       * FINISHME: compiler, this may be incorrect for a structure in a UBO
       * FINISHME: like struct s { struct { float f } s1; dvec4 v; };.
       */
      this->offset = glsl_align(this->offset,
                                field->type->std140_base_alignment(false));
   }
};

class count_block_size : public program_resource_visitor {
public:
   count_block_size() : num_active_uniforms(0)
   {
      /* empty */
   }

   unsigned num_active_uniforms;

private:
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      (void) type;
      (void) name;
      (void) row_major;
      this->num_active_uniforms++;
   }
};

} /* anonymous namespace */

struct block {
   const glsl_type *type;
   bool has_instance_name;
};

unsigned
link_uniform_blocks(void *mem_ctx,
                    struct gl_shader_program *prog,
                    struct gl_shader **shader_list,
                    unsigned num_shaders,
                    struct gl_uniform_block **blocks_ret)
{
   /* This hash table will track all of the uniform blocks that have been
    * encountered.  Since blocks with the same block-name must be the same,
    * the hash is organized by block-name.
    */
   struct hash_table *block_hash =
      _mesa_hash_table_create(mem_ctx, _mesa_key_string_equal);

   if (block_hash == NULL) {
      _mesa_error_no_memory(__func__);
      linker_error(prog, "out of memory\n");
      return 0;
   }

   /* Determine which uniform blocks are active.
    */
   link_uniform_block_active_visitor v(mem_ctx, block_hash, prog);
   for (unsigned i = 0; i < num_shaders; i++) {
      visit_list_elements(&v, shader_list[i]->ir);
   }

   /* Count the number of active uniform blocks.  Count the total number of
    * active slots in those uniform blocks.
    */
   unsigned num_blocks = 0;
   unsigned num_variables = 0;
   count_block_size block_size;
   struct hash_entry *entry;

   hash_table_foreach (block_hash, entry) {
      const struct link_uniform_block_active *const b =
         (const struct link_uniform_block_active *) entry->data;

      const glsl_type *const block_type =
         b->type->is_array() ? b->type->fields.array : b->type;

      assert((b->num_array_elements > 0) == b->type->is_array());

      block_size.num_active_uniforms = 0;
      block_size.process(block_type, "");

      if (b->num_array_elements > 0) {
         num_blocks += b->num_array_elements;
         num_variables += b->num_array_elements
            * block_size.num_active_uniforms;
      } else {
         num_blocks++;
         num_variables += block_size.num_active_uniforms;
      }

   }

   if (num_blocks == 0) {
      assert(num_variables == 0);
      _mesa_hash_table_destroy(block_hash, NULL);
      return 0;
   }

   assert(num_variables != 0);

   /* Allocate storage to hold all of the informatation related to uniform
    * blocks that can be queried through the API.
    */
   gl_uniform_block *blocks =
      ralloc_array(mem_ctx, gl_uniform_block, num_blocks);
   gl_uniform_buffer_variable *variables =
      ralloc_array(blocks, gl_uniform_buffer_variable, num_variables);

   /* Add each variable from each uniform block to the API tracking
    * structures.
    */
   unsigned i = 0;
   ubo_visitor parcel(blocks, variables, num_variables);

   STATIC_ASSERT(unsigned(GLSL_INTERFACE_PACKING_STD140)
                 == unsigned(ubo_packing_std140));
   STATIC_ASSERT(unsigned(GLSL_INTERFACE_PACKING_SHARED)
                 == unsigned(ubo_packing_shared));
   STATIC_ASSERT(unsigned(GLSL_INTERFACE_PACKING_PACKED)
                 == unsigned(ubo_packing_packed));


   hash_table_foreach (block_hash, entry) {
      const struct link_uniform_block_active *const b =
         (const struct link_uniform_block_active *) entry->data;
      const glsl_type *block_type = b->type;

      if (b->num_array_elements > 0) {
         const char *const name = block_type->fields.array->name;

         assert(b->has_instance_name);
         for (unsigned j = 0; j < b->num_array_elements; j++) {
            blocks[i].Name = ralloc_asprintf(blocks, "%s[%u]", name,
                                             b->array_elements[j]);
            blocks[i].Uniforms = &variables[parcel.index];

            /* The GL_ARB_shading_language_420pack spec says:
             *
             *     "If the binding identifier is used with a uniform block
             *     instanced as an array then the first element of the array
             *     takes the specified block binding and each subsequent
             *     element takes the next consecutive uniform block binding
             *     point."
             */
            blocks[i].Binding = (b->has_binding) ? b->binding + j : 0;

            blocks[i].UniformBufferSize = 0;
            blocks[i]._Packing =
               gl_uniform_block_packing(block_type->interface_packing);

            parcel.process(block_type->fields.array,
                           blocks[i].Name);

            blocks[i].UniformBufferSize = parcel.buffer_size;

            blocks[i].NumUniforms =
               (unsigned)(ptrdiff_t)(&variables[parcel.index] - blocks[i].Uniforms);

            i++;
         }
      } else {
         blocks[i].Name = ralloc_strdup(blocks, block_type->name);
         blocks[i].Uniforms = &variables[parcel.index];
         blocks[i].Binding = (b->has_binding) ? b->binding : 0;
         blocks[i].UniformBufferSize = 0;
         blocks[i]._Packing =
            gl_uniform_block_packing(block_type->interface_packing);

         parcel.process(block_type,
                        b->has_instance_name ? block_type->name : "");

         blocks[i].UniformBufferSize = parcel.buffer_size;

         blocks[i].NumUniforms =
            (unsigned)(ptrdiff_t)(&variables[parcel.index] - blocks[i].Uniforms);

         i++;
      }
   }

   assert(parcel.index == num_variables);

   _mesa_hash_table_destroy(block_hash, NULL);

   *blocks_ret = blocks;
   return num_blocks;
}

bool
link_uniform_blocks_are_compatible(const gl_uniform_block *a,
				   const gl_uniform_block *b)
{
   assert(strcmp(a->Name, b->Name) == 0);

   /* Page 35 (page 42 of the PDF) in section 4.3.7 of the GLSL 1.50 spec says:
    *
    *     "Matched block names within an interface (as defined above) must
    *     match in terms of having the same number of declarations with the
    *     same sequence of types and the same sequence of member names, as
    *     well as having the same member-wise layout qualification....if a
    *     matching block is declared as an array, then the array sizes must
    *     also match... Any mismatch will generate a link error."
    *
    * Arrays are not yet supported, so there is no check for that.
    */
   if (a->NumUniforms != b->NumUniforms)
      return false;

   if (a->_Packing != b->_Packing)
      return false;

   for (unsigned i = 0; i < a->NumUniforms; i++) {
      if (strcmp(a->Uniforms[i].Name, b->Uniforms[i].Name) != 0)
	 return false;

      if (a->Uniforms[i].Type != b->Uniforms[i].Type)
	 return false;

      if (a->Uniforms[i].RowMajor != b->Uniforms[i].RowMajor)
	 return false;
   }

   return true;
}

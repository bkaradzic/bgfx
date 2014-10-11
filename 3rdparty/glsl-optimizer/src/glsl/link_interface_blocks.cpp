/*
 * Copyright © 2013 Intel Corporation
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
 * \file link_interface_blocks.cpp
 * Linker support for GLSL's interface blocks.
 */

#include "ir.h"
#include "glsl_symbol_table.h"
#include "linker.h"
#include "main/macros.h"
#include "program/hash_table.h"


namespace {

/**
 * Information about a single interface block definition that we need to keep
 * track of in order to check linkage rules.
 *
 * Note: this class is expected to be short lived, so it doesn't make copies
 * of the strings it references; it simply borrows the pointers from the
 * ir_variable class.
 */
struct interface_block_definition
{
   /**
    * Extract an interface block definition from an ir_variable that
    * represents either the interface instance (for named interfaces), or a
    * member of the interface (for unnamed interfaces).
    */
   explicit interface_block_definition(const ir_variable *var)
      : type(var->get_interface_type()),
        instance_name(NULL),
        array_size(-1)
   {
      if (var->is_interface_instance()) {
         instance_name = var->name;
         if (var->type->is_array())
            array_size = var->type->length;
      }
      explicitly_declared = (var->data.how_declared != ir_var_declared_implicitly);
   }

   /**
    * Interface block type
    */
   const glsl_type *type;

   /**
    * For a named interface block, the instance name.  Otherwise NULL.
    */
   const char *instance_name;

   /**
    * For an interface block array, the array size (or 0 if unsized).
    * Otherwise -1.
    */
   int array_size;

   /**
    * True if this interface block was explicitly declared in the shader;
    * false if it was an implicitly declared built-in interface block.
    */
   bool explicitly_declared;
};


/**
 * Check if two interfaces match, according to intrastage interface matching
 * rules.  If they do, and the first interface uses an unsized array, it will
 * be updated to reflect the array size declared in the second interface.
 */
bool
intrastage_match(interface_block_definition *a,
                 const interface_block_definition *b,
                 ir_variable_mode mode)
{
   /* Types must match. */
   if (a->type != b->type) {
      /* Exception: if both the interface blocks are implicitly declared,
       * don't force their types to match.  They might mismatch due to the two
       * shaders using different GLSL versions, and that's ok.
       */
      if (a->explicitly_declared || b->explicitly_declared)
         return false;
   }

   /* Presence/absence of interface names must match. */
   if ((a->instance_name == NULL) != (b->instance_name == NULL))
      return false;

   /* For uniforms, instance names need not match.  For shader ins/outs,
    * it's not clear from the spec whether they need to match, but
    * Mesa's implementation relies on them matching.
    */
   if (a->instance_name != NULL && mode != ir_var_uniform &&
       strcmp(a->instance_name, b->instance_name) != 0) {
      return false;
   }

   /* Array vs. nonarray must be consistent, and sizes must be
    * consistent, with the exception that unsized arrays match sized
    * arrays.
    */
   if ((a->array_size == -1) != (b->array_size == -1))
      return false;
   if (b->array_size != 0) {
      if (a->array_size == 0)
         a->array_size = b->array_size;
      else if (a->array_size != b->array_size)
         return false;
   }

   return true;
}


/**
 * Check if two interfaces match, according to interstage (in/out) interface
 * matching rules.
 *
 * If \c extra_array_level is true, then vertex-to-geometry shader matching
 * rules are enforced (i.e. a successful match requires the consumer interface
 * to be an array and the producer interface to be a non-array).
 */
bool
interstage_match(const interface_block_definition *producer,
                 const interface_block_definition *consumer,
                 bool extra_array_level)
{
   /* Unsized arrays should not occur during interstage linking.  They
    * should have all been assigned a size by link_intrastage_shaders.
    */
   assert(consumer->array_size != 0);
   assert(producer->array_size != 0);

   /* Types must match. */
   if (consumer->type != producer->type) {
      /* Exception: if both the interface blocks are implicitly declared,
       * don't force their types to match.  They might mismatch due to the two
       * shaders using different GLSL versions, and that's ok.
       */
      if (consumer->explicitly_declared || producer->explicitly_declared)
         return false;
   }
   if (extra_array_level) {
      /* Consumer must be an array, and producer must not. */
      if (consumer->array_size == -1)
         return false;
      if (producer->array_size != -1)
         return false;
   } else {
      /* Array vs. nonarray must be consistent, and sizes must be consistent.
       * Since unsized arrays have been ruled out, we can check this by just
       * making sure the sizes are equal.
       */
      if (consumer->array_size != producer->array_size)
         return false;
   }
   return true;
}


/**
 * This class keeps track of a mapping from an interface block name to the
 * necessary information about that interface block to determine whether to
 * generate a link error.
 *
 * Note: this class is expected to be short lived, so it doesn't make copies
 * of the strings it references; it simply borrows the pointers from the
 * ir_variable class.
 */
class interface_block_definitions
{
public:
   interface_block_definitions()
      : mem_ctx(ralloc_context(NULL)),
        ht(hash_table_ctor(0, hash_table_string_hash,
                           hash_table_string_compare))
   {
   }

   ~interface_block_definitions()
   {
      hash_table_dtor(ht);
      ralloc_free(mem_ctx);
   }

   /**
    * Lookup the interface definition having the given block name.  Return
    * NULL if none is found.
    */
   interface_block_definition *lookup(const char *block_name)
   {
      return (interface_block_definition *) hash_table_find(ht, block_name);
   }

   /**
    * Add a new interface definition.
    */
   void store(const interface_block_definition &def)
   {
      interface_block_definition *hash_entry =
         rzalloc(mem_ctx, interface_block_definition);
      *hash_entry = def;
      hash_table_insert(ht, hash_entry, def.type->name);
   }

private:
   /**
    * Ralloc context for data structures allocated by this class.
    */
   void *mem_ctx;

   /**
    * Hash table mapping interface block name to an \c
    * interface_block_definition struct.  interface_block_definition structs
    * are allocated using \c mem_ctx.
    */
   hash_table *ht;
};


}; /* anonymous namespace */


void
validate_intrastage_interface_blocks(struct gl_shader_program *prog,
                                     const gl_shader **shader_list,
                                     unsigned num_shaders)
{
   interface_block_definitions in_interfaces;
   interface_block_definitions out_interfaces;
   interface_block_definitions uniform_interfaces;

   for (unsigned int i = 0; i < num_shaders; i++) {
      if (shader_list[i] == NULL)
         continue;

      foreach_in_list(ir_instruction, node, shader_list[i]->ir) {
         ir_variable *var = node->as_variable();
         if (!var)
            continue;

         const glsl_type *iface_type = var->get_interface_type();

         if (iface_type == NULL)
            continue;

         interface_block_definitions *definitions;
         switch (var->data.mode) {
         case ir_var_shader_in:
            definitions = &in_interfaces;
            break;
         case ir_var_shader_out:
            definitions = &out_interfaces;
            break;
         case ir_var_uniform:
            definitions = &uniform_interfaces;
            break;
         default:
            /* Only in, out, and uniform interfaces are legal, so we should
             * never get here.
             */
            assert(!"illegal interface type");
            continue;
         }

         const interface_block_definition def(var);
         interface_block_definition *prev_def =
            definitions->lookup(iface_type->name);

         if (prev_def == NULL) {
            /* This is the first time we've seen the interface, so save
             * it into the appropriate data structure.
             */
            definitions->store(def);
         } else if (!intrastage_match(prev_def, &def,
                                      (ir_variable_mode) var->data.mode)) {
            linker_error(prog, "definitions of interface block `%s' do not"
                         " match\n", iface_type->name);
            return;
         }
      }
   }
}

void
validate_interstage_inout_blocks(struct gl_shader_program *prog,
                                 const gl_shader *producer,
                                 const gl_shader *consumer)
{
   interface_block_definitions definitions;
   const bool extra_array_level = consumer->Stage == MESA_SHADER_GEOMETRY;

   /* Add input interfaces from the consumer to the symbol table. */
   foreach_in_list(ir_instruction, node, consumer->ir) {
      ir_variable *var = node->as_variable();
      if (!var || !var->get_interface_type() || var->data.mode != ir_var_shader_in)
         continue;

      definitions.store(interface_block_definition(var));
   }

   /* Verify that the producer's output interfaces match. */
   foreach_in_list(ir_instruction, node, producer->ir) {
      ir_variable *var = node->as_variable();
      if (!var || !var->get_interface_type() || var->data.mode != ir_var_shader_out)
         continue;

      interface_block_definition *consumer_def =
         definitions.lookup(var->get_interface_type()->name);

      /* The consumer doesn't use this output block.  Ignore it. */
      if (consumer_def == NULL)
         continue;

      const interface_block_definition producer_def(var);

      if (!interstage_match(&producer_def, consumer_def, extra_array_level)) {
         linker_error(prog, "definitions of interface block `%s' do not "
                      "match\n", var->get_interface_type()->name);
         return;
      }
   }
}


void
validate_interstage_uniform_blocks(struct gl_shader_program *prog,
                                   gl_shader **stages, int num_stages)
{
   interface_block_definitions definitions;

   for (int i = 0; i < num_stages; i++) {
      if (stages[i] == NULL)
         continue;

      const gl_shader *stage = stages[i];
      foreach_in_list(ir_instruction, node, stage->ir) {
         ir_variable *var = node->as_variable();
         if (!var || !var->get_interface_type() || var->data.mode != ir_var_uniform)
            continue;

         interface_block_definition *old_def =
            definitions.lookup(var->get_interface_type()->name);
         const interface_block_definition new_def(var);
         if (old_def == NULL) {
            definitions.store(new_def);
         } else {
            /* Interstage uniform matching rules are the same as intrastage
             * uniform matchin rules (for uniforms, it is as though all
             * shaders are in the same shader stage).
             */
            if (!intrastage_match(old_def, &new_def, ir_var_uniform)) {
               linker_error(prog, "definitions of interface block `%s' do not "
                            "match\n", var->get_interface_type()->name);
               return;
            }
         }
      }
   }
}

/* -*- c++ -*- */
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

#pragma once
#ifndef GLSL_LINKER_H
#define GLSL_LINKER_H

ir_function_signature *
link_get_main_function_signature(gl_shader *sh);

extern bool
link_function_calls(gl_shader_program *prog, gl_shader *main,
		    gl_shader **shader_list, unsigned num_shaders);

extern void
link_invalidate_variable_locations(exec_list *ir);

extern void
link_assign_uniform_locations(struct gl_shader_program *prog,
                              unsigned int boolean_true);

extern void
link_set_uniform_initializers(struct gl_shader_program *prog,
                              unsigned int boolean_true);

extern int
link_cross_validate_uniform_block(void *mem_ctx,
				  struct gl_uniform_block **linked_blocks,
				  unsigned int *num_linked_blocks,
				  struct gl_uniform_block *new_block);

extern bool
link_uniform_blocks_are_compatible(const gl_uniform_block *a,
				   const gl_uniform_block *b);

extern unsigned
link_uniform_blocks(void *mem_ctx,
                    struct gl_shader_program *prog,
                    struct gl_shader **shader_list,
                    unsigned num_shaders,
                    struct gl_uniform_block **blocks_ret);

void
validate_intrastage_interface_blocks(struct gl_shader_program *prog,
                                     const gl_shader **shader_list,
                                     unsigned num_shaders);

void
validate_interstage_inout_blocks(struct gl_shader_program *prog,
                                 const gl_shader *producer,
                                 const gl_shader *consumer);

void
validate_interstage_uniform_blocks(struct gl_shader_program *prog,
                                   gl_shader **stages, int num_stages);

extern void
link_assign_atomic_counter_resources(struct gl_context *ctx,
                                     struct gl_shader_program *prog);

extern void
link_check_atomic_counter_resources(struct gl_context *ctx,
                                    struct gl_shader_program *prog);

/**
 * Class for processing all of the leaf fields of a variable that corresponds
 * to a program resource.
 *
 * The leaf fields are all the parts of the variable that the application
 * could query using \c glGetProgramResourceIndex (or that could be returned
 * by \c glGetProgramResourceName).
 *
 * Classes my derive from this class to implement specific functionality.
 * This class only provides the mechanism to iterate over the leaves.  Derived
 * classes must implement \c ::visit_field and may override \c ::process.
 */
class program_resource_visitor {
public:
   /**
    * Begin processing a variable
    *
    * Classes that overload this function should call \c ::process from the
    * base class to start the recursive processing of the variable.
    *
    * \param var  The variable that is to be processed
    *
    * Calls \c ::visit_field for each leaf of the variable.
    *
    * \warning
    * When processing a uniform block, this entry should only be used in cases
    * where the row / column ordering of matrices in the block does not
    * matter.  For example, enumerating the names of members of the block, but
    * not for determining the offsets of members.
    */
   void process(ir_variable *var);

   /**
    * Begin processing a variable of a structured type.
    *
    * This flavor of \c process should be used to handle structured types
    * (i.e., structures, interfaces, or arrays there of) that need special
    * name handling.  A common usage is to handle cases where the block name
    * (instead of the instance name) is used for an interface block.
    *
    * \param type  Type that is to be processed, associated with \c name
    * \param name  Base name of the structured variable being processed
    *
    * \note
    * \c type must be \c GLSL_TYPE_RECORD, \c GLSL_TYPE_INTERFACE, or an array
    * there of.
    */
   void process(const glsl_type *type, const char *name);

protected:
   /**
    * Method invoked for each leaf of the variable
    *
    * \param type  Type of the field.
    * \param name  Fully qualified name of the field.
    * \param row_major  For a matrix type, is it stored row-major.
    * \param record_type  Type of the record containing the field.
    * \param last_field   Set if \c name is the last field of the structure
    *                     containing it.  This will always be false for items
    *                     not contained in a structure or interface block.
    *
    * The default implementation just calls the other \c visit_field method.
    */
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major, const glsl_type *record_type,
                            bool last_field);

   /**
    * Method invoked for each leaf of the variable
    *
    * \param type  Type of the field.
    * \param name  Fully qualified name of the field.
    * \param row_major  For a matrix type, is it stored row-major.
    */
   virtual void visit_field(const glsl_type *type, const char *name,
                            bool row_major) = 0;

   /**
    * Visit a record before visiting its fields
    *
    * For structures-of-structures or interfaces-of-structures, this visits
    * the inner structure before visiting its fields.
    *
    * The default implementation does nothing.
    */
   virtual void visit_field(const glsl_struct_field *field);

private:
   /**
    * \param name_length  Length of the current name \b not including the
    *                     terminating \c NUL character.
    * \param last_field   Set if \c name is the last field of the structure
    *                     containing it.  This will always be false for items
    *                     not contained in a structure or interface block.
    */
   void recursion(const glsl_type *t, char **name, size_t name_length,
                  bool row_major, const glsl_type *record_type,
                  bool last_field);
};

extern struct gl_shader *
link_intrastage_shaders(void *mem_ctx,
						struct gl_context *ctx,
						struct gl_shader_program *prog,
						struct gl_shader **shader_list,
						unsigned num_shaders);

void
linker_error(gl_shader_program *prog, const char *fmt, ...);

void
linker_warning(gl_shader_program *prog, const char *fmt, ...);

#endif /* GLSL_LINKER_H */

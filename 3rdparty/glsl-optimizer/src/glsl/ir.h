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
#ifndef IR_H
#define IR_H

#include <stdio.h>
#include <stdlib.h>

#include "c99_compat.h"
#include "util/ralloc.h"
#include "glsl_types.h"
#include "list.h"
#include "ir_visitor.h"
#include "ir_hierarchical_visitor.h"
#include "main/mtypes.h"
#include "main/macros.h"

#ifdef __cplusplus

/**
 * \defgroup IR Intermediate representation nodes
 *
 * @{
 */

/**
 * Class tags
 *
 * Each concrete class derived from \c ir_instruction has a value in this
 * enumerant.  The value for the type is stored in \c ir_instruction::ir_type
 * by the constructor.  While using type tags is not very C++, it is extremely
 * convenient.  For example, during debugging you can simply inspect
 * \c ir_instruction::ir_type to find out the actual type of the object.
 *
 * In addition, it is possible to use a switch-statement based on \c
 * \c ir_instruction::ir_type to select different behavior for different object
 * types.  For functions that have only slight differences for several object
 * types, this allows writing very straightforward, readable code.
 */
enum ir_node_type {
   ir_type_dereference_array,
   ir_type_dereference_record,
   ir_type_dereference_variable,
   ir_type_constant,
   ir_type_expression,
   ir_type_swizzle,
   ir_type_texture,
   ir_type_variable,
   ir_type_assignment,
   ir_type_call,
   ir_type_function,
   ir_type_function_signature,
   ir_type_if,
   ir_type_loop,
   ir_type_loop_jump,
   ir_type_return,
   ir_type_precision,
   ir_type_typedecl,
   ir_type_discard,
   ir_type_emit_vertex,
   ir_type_end_primitive,
   ir_type_max, /**< maximum ir_type enum number, for validation */
   ir_type_unset = ir_type_max
};


/**
 * Base class of all IR instructions
 */
class ir_instruction : public exec_node {
public:
   enum ir_node_type ir_type;

   /**
    * GCC 4.7+ and clang warn when deleting an ir_instruction unless
    * there's a virtual destructor present.  Because we almost
    * universally use ralloc for our memory management of
    * ir_instructions, the destructor doesn't need to do any work.
    */
   virtual ~ir_instruction()
   {
   }

   /** ir_print_visitor helper for debugging. */
   void print(void) const;
   void fprint(FILE *f) const;

   virtual void accept(ir_visitor *) = 0;
   virtual ir_visitor_status accept(ir_hierarchical_visitor *) = 0;
   virtual ir_instruction *clone(void *mem_ctx,
				 struct hash_table *ht) const = 0;

   /**
    * \name IR instruction downcast functions
    *
    * These functions either cast the object to a derived class or return
    * \c NULL if the object's type does not match the specified derived class.
    * Additional downcast functions will be added as needed.
    */
   /*@{*/
   class ir_rvalue *as_rvalue()
   {
      if (ir_type == ir_type_dereference_array ||
          ir_type == ir_type_dereference_record ||
          ir_type == ir_type_dereference_variable ||
          ir_type == ir_type_constant ||
          ir_type == ir_type_expression ||
          ir_type == ir_type_swizzle ||
          ir_type == ir_type_texture)
         return (class ir_rvalue *) this;
      return NULL;
   }

   class ir_dereference *as_dereference()
   {
      if (ir_type == ir_type_dereference_array ||
          ir_type == ir_type_dereference_record ||
          ir_type == ir_type_dereference_variable)
         return (class ir_dereference *) this;
      return NULL;
   }

   class ir_jump *as_jump()
   {
      if (ir_type == ir_type_loop_jump ||
          ir_type == ir_type_return ||
          ir_type == ir_type_discard)
         return (class ir_jump *) this;
      return NULL;
   }

   #define AS_CHILD(TYPE) \
   class ir_##TYPE * as_##TYPE() \
   { \
      return ir_type == ir_type_##TYPE ? (ir_##TYPE *) this : NULL; \
   }
   AS_CHILD(variable)
   AS_CHILD(function)
   AS_CHILD(dereference_array)
   AS_CHILD(dereference_variable)
   AS_CHILD(dereference_record)
   AS_CHILD(expression)
   AS_CHILD(loop)
   AS_CHILD(assignment)
   AS_CHILD(call)
   AS_CHILD(return)
   AS_CHILD(if)
   AS_CHILD(swizzle)
   AS_CHILD(texture)
   AS_CHILD(constant)
   AS_CHILD(discard)
   #undef AS_CHILD
   /*@}*/

   /**
    * IR equality method: Return true if the referenced instruction would
    * return the same value as this one.
    *
    * This intended to be used for CSE and algebraic optimizations, on rvalues
    * in particular.  No support for other instruction types (assignments,
    * jumps, calls, etc.) is planned.
    */
   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

protected:
   ir_instruction(enum ir_node_type t)
      : ir_type(t)
   {
   }

private:
   ir_instruction()
   {
      assert(!"Should not get here.");
   }
};


/**
 * The base class for all "values"/expression trees.
 */
class ir_rvalue : public ir_instruction {
public:
   const struct glsl_type *type;

   virtual ir_rvalue *clone(void *mem_ctx, struct hash_table *) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   ir_rvalue *as_rvalue_to_saturate();

   virtual bool is_lvalue() const
   {
      return false;
   }

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const
   {
      return NULL;
   }


   /**
    * If an r-value is a reference to a whole variable, get that variable
    *
    * \return
    * Pointer to a variable that is completely dereferenced by the r-value.  If
    * the r-value is not a dereference or the dereference does not access the
    * entire variable (i.e., it's just one array element, struct field), \c NULL
    * is returned.
    */
   virtual ir_variable *whole_variable_referenced()
   {
      return NULL;
   }

   glsl_precision get_precision() const { return precision; }
   void set_precision (glsl_precision prec) { precision = prec; }

   /**
    * Determine if an r-value has the value zero
    *
    * The base implementation of this function always returns \c false.  The
    * \c ir_constant class over-rides this function to return \c true \b only
    * for vector and scalar types that have all elements set to the value
    * zero (or \c false for booleans).
    *
    * \sa ir_constant::has_value, ir_rvalue::is_one, ir_rvalue::is_negative_one,
    *     ir_constant::is_basis
    */
   virtual bool is_zero() const;

   /**
    * Determine if an r-value has the value one
    *
    * The base implementation of this function always returns \c false.  The
    * \c ir_constant class over-rides this function to return \c true \b only
    * for vector and scalar types that have all elements set to the value
    * one (or \c true for booleans).
    *
    * \sa ir_constant::has_value, ir_rvalue::is_zero, ir_rvalue::is_negative_one,
    *     ir_constant::is_basis
    */
   virtual bool is_one() const;

   /**
    * Determine if an r-value has the value negative one
    *
    * The base implementation of this function always returns \c false.  The
    * \c ir_constant class over-rides this function to return \c true \b only
    * for vector and scalar types that have all elements set to the value
    * negative one.  For boolean types, the result is always \c false.
    *
    * \sa ir_constant::has_value, ir_rvalue::is_zero, ir_rvalue::is_one
    *     ir_constant::is_basis
    */
   virtual bool is_negative_one() const;

   /**
    * Determine if an r-value is a basis vector
    *
    * The base implementation of this function always returns \c false.  The
    * \c ir_constant class over-rides this function to return \c true \b only
    * for vector and scalar types that have one element set to the value one,
    * and the other elements set to the value zero.  For boolean types, the
    * result is always \c false.
    *
    * \sa ir_constant::has_value, ir_rvalue::is_zero, ir_rvalue::is_one,
    *     is_constant::is_negative_one
    */
   virtual bool is_basis() const;

   /**
    * Determine if an r-value is an unsigned integer constant which can be
    * stored in 16 bits.
    *
    * \sa ir_constant::is_uint16_constant.
    */
   virtual bool is_uint16_constant() const { return false; }

   /**
    * Return a generic value of error_type.
    *
    * Allocation will be performed with 'mem_ctx' as ralloc owner.
    */
   static ir_rvalue *error_value(void *mem_ctx);

protected:
   ir_rvalue(enum ir_node_type t, glsl_precision precision);

   glsl_precision precision;
};


/**
 * Variable storage classes
 */
enum ir_variable_mode {
   ir_var_auto = 0,     /**< Function local variables and globals. */
   ir_var_uniform,      /**< Variable declared as a uniform. */
   ir_var_shader_in,
   ir_var_shader_out,
   ir_var_shader_inout,
   ir_var_function_in,
   ir_var_function_out,
   ir_var_function_inout,
   ir_var_const_in,	/**< "in" param that must be a constant expression */
   ir_var_system_value, /**< Ex: front-face, instance-id, etc. */
   ir_var_temporary,	/**< Temporary variable generated during compilation. */
   ir_var_mode_count	/**< Number of variable modes */
};

/**
 * Enum keeping track of how a variable was declared.  For error checking of
 * the gl_PerVertex redeclaration rules.
 */
enum ir_var_declaration_type {
   /**
    * Normal declaration (for most variables, this means an explicit
    * declaration.  Exception: temporaries are always implicitly declared, but
    * they still use ir_var_declared_normally).
    *
    * Note: an ir_variable that represents a named interface block uses
    * ir_var_declared_normally.
    */
   ir_var_declared_normally = 0,

   /**
    * Variable was explicitly declared (or re-declared) in an unnamed
    * interface block.
    */
   ir_var_declared_in_block,

   /**
    * Variable is an implicitly declared built-in that has not been explicitly
    * re-declared by the shader.
    */
   ir_var_declared_implicitly,
};

/**
 * \brief Layout qualifiers for gl_FragDepth.
 *
 * The AMD/ARB_conservative_depth extensions allow gl_FragDepth to be redeclared
 * with a layout qualifier.
 */
enum ir_depth_layout {
    ir_depth_layout_none, /**< No depth layout is specified. */
    ir_depth_layout_any,
    ir_depth_layout_greater,
    ir_depth_layout_less,
    ir_depth_layout_unchanged
};

/**
 * \brief Convert depth layout qualifier to string.
 */
const char*
depth_layout_string(ir_depth_layout layout);

/**
 * Description of built-in state associated with a uniform
 *
 * \sa ir_variable::state_slots
 */
struct ir_state_slot {
   int tokens[5];
   int swizzle;
};


/**
 * Get the string value for an interpolation qualifier
 *
 * \return The string that would be used in a shader to specify \c
 * mode will be returned.
 *
 * This function is used to generate error messages of the form "shader
 * uses %s interpolation qualifier", so in the case where there is no
 * interpolation qualifier, it returns "no".
 *
 * This function should only be used on a shader input or output variable.
 */
const char *interpolation_string(unsigned interpolation);


class ir_variable : public ir_instruction {
public:
   ir_variable(const struct glsl_type *, const char *, ir_variable_mode, glsl_precision);

   virtual ir_variable *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);


   /**
    * Determine how this variable should be interpolated based on its
    * interpolation qualifier (if present), whether it is gl_Color or
    * gl_SecondaryColor, and whether flatshading is enabled in the current GL
    * state.
    *
    * The return value will always be either INTERP_QUALIFIER_SMOOTH,
    * INTERP_QUALIFIER_NOPERSPECTIVE, or INTERP_QUALIFIER_FLAT.
    */
   glsl_interp_qualifier determine_interpolation_mode(bool flat_shade);

   /**
    * Determine whether or not a variable is part of a uniform block.
    */
   inline bool is_in_uniform_block() const
   {
      return this->data.mode == ir_var_uniform && this->interface_type != NULL;
   }

   /**
    * Determine whether or not a variable is the declaration of an interface
    * block
    *
    * For the first declaration below, there will be an \c ir_variable named
    * "instance" whose type and whose instance_type will be the same
    *  \cglsl_type.  For the second declaration, there will be an \c ir_variable
    * named "f" whose type is float and whose instance_type is B2.
    *
    * "instance" is an interface instance variable, but "f" is not.
    *
    * uniform B1 {
    *     float f;
    * } instance;
    *
    * uniform B2 {
    *     float f;
    * };
    */
   inline bool is_interface_instance() const
   {
      const glsl_type *const t = this->type;

      return (t == this->interface_type)
         || (t->is_array() && t->fields.array == this->interface_type);
    }

   /**
    * Set this->interface_type on a newly created variable.
    */
   void init_interface_type(const struct glsl_type *type)
   {
      assert(this->interface_type == NULL);
      this->interface_type = type;
      if (this->is_interface_instance()) {
         this->u.max_ifc_array_access =
            rzalloc_array(this, unsigned, type->length);
      }
   }

   /**
    * Change this->interface_type on a variable that previously had a
    * different, but compatible, interface_type.  This is used during linking
    * to set the size of arrays in interface blocks.
    */
   void change_interface_type(const struct glsl_type *type)
   {
      if (this->u.max_ifc_array_access != NULL) {
         /* max_ifc_array_access has already been allocated, so make sure the
          * new interface has the same number of fields as the old one.
          */
         assert(this->interface_type->length == type->length);
      }
      this->interface_type = type;
   }

   /**
    * Change this->interface_type on a variable that previously had a
    * different, and incompatible, interface_type. This is used during
    * compilation to handle redeclaration of the built-in gl_PerVertex
    * interface block.
    */
   void reinit_interface_type(const struct glsl_type *type)
   {
      if (this->u.max_ifc_array_access != NULL) {
#ifndef NDEBUG
         /* Redeclaring gl_PerVertex is only allowed if none of the built-ins
          * it defines have been accessed yet; so it's safe to throw away the
          * old max_ifc_array_access pointer, since all of its values are
          * zero.
          */
         for (unsigned i = 0; i < this->interface_type->length; i++)
            assert(this->u.max_ifc_array_access[i] == 0);
#endif
         ralloc_free(this->u.max_ifc_array_access);
         this->u.max_ifc_array_access = NULL;
      }
      this->interface_type = NULL;
      init_interface_type(type);
   }

   const glsl_type *get_interface_type() const
   {
      return this->interface_type;
   }

   /**
    * Get the max_ifc_array_access pointer
    *
    * A "set" function is not needed because the array is dynmically allocated
    * as necessary.
    */
   inline unsigned *get_max_ifc_array_access()
   {
      assert(this->data._num_state_slots == 0);
      return this->u.max_ifc_array_access;
   }

   inline unsigned get_num_state_slots() const
   {
      assert(!this->is_interface_instance()
             || this->data._num_state_slots == 0);
      return this->data._num_state_slots;
   }

   inline void set_num_state_slots(unsigned n)
   {
      assert(!this->is_interface_instance()
             || n == 0);
      this->data._num_state_slots = n;
   }

   inline ir_state_slot *get_state_slots()
   {
      return this->is_interface_instance() ? NULL : this->u.state_slots;
   }

   inline const ir_state_slot *get_state_slots() const
   {
      return this->is_interface_instance() ? NULL : this->u.state_slots;
   }

   inline ir_state_slot *allocate_state_slots(unsigned n)
   {
      assert(!this->is_interface_instance());

      this->u.state_slots = ralloc_array(this, ir_state_slot, n);
      this->data._num_state_slots = 0;

      if (this->u.state_slots != NULL)
         this->data._num_state_slots = n;

      return this->u.state_slots;
   }

   inline bool is_name_ralloced() const
   {
      return this->name != ir_variable::tmp_name;
   }

   /**
    * Enable emitting extension warnings for this variable
    */
   void enable_extension_warning(const char *extension);

   /**
    * Get the extension warning string for this variable
    *
    * If warnings are not enabled, \c NULL is returned.
    */
   const char *get_extension_warning() const;

   /**
    * Declared type of the variable
    */
   const struct glsl_type *type;

   /**
    * Declared name of the variable
    */
   const char *name;

   struct ir_variable_data {

      /**
       * Is the variable read-only?
       *
       * This is set for variables declared as \c const, shader inputs,
       * and uniforms.
       */
      unsigned read_only:1;
      unsigned centroid:1;
      unsigned sample:1;
      unsigned invariant:1;
      unsigned precise:1;

      /**
       * Has this variable been used for reading or writing?
       *
       * Several GLSL semantic checks require knowledge of whether or not a
       * variable has been used.  For example, it is an error to redeclare a
       * variable as invariant after it has been used.
       *
       * This is only maintained in the ast_to_hir.cpp path, not in
       * Mesa's fixed function or ARB program paths.
       */
      unsigned used:1;

      /**
       * Has this variable been statically assigned?
       *
       * This answers whether the variable was assigned in any path of
       * the shader during ast_to_hir.  This doesn't answer whether it is
       * still written after dead code removal, nor is it maintained in
       * non-ast_to_hir.cpp (GLSL parsing) paths.
       */
      unsigned assigned:1;

      /**
       * Enum indicating how the variable was declared.  See
       * ir_var_declaration_type.
       *
       * This is used to detect certain kinds of illegal variable redeclarations.
       */
      unsigned how_declared:2;

      /**
       * Storage class of the variable.
       *
       * \sa ir_variable_mode
       */
      unsigned mode:4;

      /**
       * Interpolation mode for shader inputs / outputs
       *
       * \sa ir_variable_interpolation
       */
      unsigned interpolation:2;

      unsigned precision:2;

      /**
       * \name ARB_fragment_coord_conventions
       * @{
       */
      unsigned origin_upper_left:1;
      unsigned pixel_center_integer:1;
      /*@}*/

      /**
       * Was the location explicitly set in the shader?
       *
       * If the location is explicitly set in the shader, it \b cannot be changed
       * by the linker or by the API (e.g., calls to \c glBindAttribLocation have
       * no effect).
       */
      unsigned explicit_location:1;
      unsigned explicit_index:1;

      /**
       * Was an initial binding explicitly set in the shader?
       *
       * If so, constant_value contains an integer ir_constant representing the
       * initial binding point.
       */
      unsigned explicit_binding:1;

      /**
       * Does this variable have an initializer?
       *
       * This is used by the linker to cross-validiate initializers of global
       * variables.
       */
      unsigned has_initializer:1;

      /**
       * Is this variable a generic output or input that has not yet been matched
       * up to a variable in another stage of the pipeline?
       *
       * This is used by the linker as scratch storage while assigning locations
       * to generic inputs and outputs.
       */
      unsigned is_unmatched_generic_inout:1;

      /**
       * If non-zero, then this variable may be packed along with other variables
       * into a single varying slot, so this offset should be applied when
       * accessing components.  For example, an offset of 1 means that the x
       * component of this variable is actually stored in component y of the
       * location specified by \c location.
       */
      unsigned location_frac:2;

      /**
       * Layout of the matrix.  Uses glsl_matrix_layout values.
       */
      unsigned matrix_layout:2;

      /**
       * Non-zero if this variable was created by lowering a named interface
       * block which was not an array.
       *
       * Note that this variable and \c from_named_ifc_block_array will never
       * both be non-zero.
       */
      unsigned from_named_ifc_block_nonarray:1;

      /**
       * Non-zero if this variable was created by lowering a named interface
       * block which was an array.
       *
       * Note that this variable and \c from_named_ifc_block_nonarray will never
       * both be non-zero.
       */
      unsigned from_named_ifc_block_array:1;

      /**
       * Non-zero if the variable must be a shader input. This is useful for
       * constraints on function parameters.
       */
      unsigned must_be_shader_input:1;

      /**
       * Output index for dual source blending.
       *
       * \note
       * The GLSL spec only allows the values 0 or 1 for the index in \b dual
       * source blending.
       */
      unsigned index:1;

      /**
       * \brief Layout qualifier for gl_FragDepth.
       *
       * This is not equal to \c ir_depth_layout_none if and only if this
       * variable is \c gl_FragDepth and a layout qualifier is specified.
       */
      ir_depth_layout depth_layout:3;

      /**
       * ARB_shader_image_load_store qualifiers.
       */
      unsigned image_read_only:1; /**< "readonly" qualifier. */
      unsigned image_write_only:1; /**< "writeonly" qualifier. */
      unsigned image_coherent:1;
      unsigned image_volatile:1;
      unsigned image_restrict:1;

      /**
       * Emit a warning if this variable is accessed.
       */
   private:
      uint8_t warn_extension_index;

   public:
      /** Image internal format if specified explicitly, otherwise GL_NONE. */
      uint16_t image_format;

   private:
      /**
       * Number of state slots used
       *
       * \note
       * This could be stored in as few as 7-bits, if necessary.  If it is made
       * smaller, add an assertion to \c ir_variable::allocate_state_slots to
       * be safe.
       */
      uint16_t _num_state_slots;

   public:
      /**
       * Initial binding point for a sampler, atomic, or UBO.
       *
       * For array types, this represents the binding point for the first element.
       */
      int16_t binding;

      /**
       * Storage location of the base of this variable
       *
       * The precise meaning of this field depends on the nature of the variable.
       *
       *   - Vertex shader input: one of the values from \c gl_vert_attrib.
       *   - Vertex shader output: one of the values from \c gl_varying_slot.
       *   - Geometry shader input: one of the values from \c gl_varying_slot.
       *   - Geometry shader output: one of the values from \c gl_varying_slot.
       *   - Fragment shader input: one of the values from \c gl_varying_slot.
       *   - Fragment shader output: one of the values from \c gl_frag_result.
       *   - Uniforms: Per-stage uniform slot number for default uniform block.
       *   - Uniforms: Index within the uniform block definition for UBO members.
       *   - Other: This field is not currently used.
       *
       * If the variable is a uniform, shader input, or shader output, and the
       * slot has not been assigned, the value will be -1.
       */
      int location;

      /**
       * Vertex stream output identifier.
       */
      unsigned stream;

      /**
       * Location an atomic counter is stored at.
       */
      struct {
         unsigned offset;
      } atomic;

      /**
       * Highest element accessed with a constant expression array index
       *
       * Not used for non-array variables.
       */
      unsigned max_array_access;

      /**
       * Allow (only) ir_variable direct access private members.
       */
      friend class ir_variable;
   } data;

   /**
    * Value assigned in the initializer of a variable declared "const"
    */
   ir_constant *constant_value;

   /**
    * Constant expression assigned in the initializer of the variable
    *
    * \warning
    * This field and \c ::constant_value are distinct.  Even if the two fields
    * refer to constants with the same value, they must point to separate
    * objects.
    */
   ir_constant *constant_initializer;

private:
   static const char *const warn_extension_table[];

   union {
      /**
       * For variables which satisfy the is_interface_instance() predicate,
       * this points to an array of integers such that if the ith member of
       * the interface block is an array, max_ifc_array_access[i] is the
       * maximum array element of that member that has been accessed.  If the
       * ith member of the interface block is not an array,
       * max_ifc_array_access[i] is unused.
       *
       * For variables whose type is not an interface block, this pointer is
       * NULL.
       */
      unsigned *max_ifc_array_access;

      /**
       * Built-in state that backs this uniform
       *
       * Once set at variable creation, \c state_slots must remain invariant.
       *
       * If the variable is not a uniform, \c _num_state_slots will be zero
       * and \c state_slots will be \c NULL.
       */
      ir_state_slot *state_slots;
   } u;

   /**
    * For variables that are in an interface block or are an instance of an
    * interface block, this is the \c GLSL_TYPE_INTERFACE type for that block.
    *
    * \sa ir_variable::location
    */
   const glsl_type *interface_type;

   /**
    * Name used for anonymous compiler temporaries
    */
   static const char tmp_name[];

public:
   /**
    * Should the construct keep names for ir_var_temporary variables?
    *
    * When this global is false, names passed to the constructor for
    * \c ir_var_temporary variables will be dropped.  Instead, the variable will
    * be named "compiler_temp".  This name will be in static storage.
    *
    * \warning
    * \b NEVER change the mode of an \c ir_var_temporary.
    *
    * \warning
    * This variable is \b not thread-safe.  It is global, \b not
    * per-context. It begins life false.  A context can, at some point, make
    * it true.  From that point on, it will be true forever.  This should be
    * okay since it will only be set true while debugging.
    */
   static bool temporaries_allocate_names;
};

/**
 * A function that returns whether a built-in function is available in the
 * current shading language (based on version, ES or desktop, and extensions).
 */
typedef bool (*builtin_available_predicate)(const _mesa_glsl_parse_state *);

/*@{*/
/**
 * The representation of a function instance; may be the full definition or
 * simply a prototype.
 */
class ir_function_signature : public ir_instruction {
   /* An ir_function_signature will be part of the list of signatures in
    * an ir_function.
    */
public:
   ir_function_signature(const glsl_type *return_type, glsl_precision precision,
                         builtin_available_predicate builtin_avail = NULL);

   virtual ir_function_signature *clone(void *mem_ctx,
					struct hash_table *ht) const;
   ir_function_signature *clone_prototype(void *mem_ctx,
					  struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /**
    * Attempt to evaluate this function as a constant expression,
    * given a list of the actual parameters and the variable context.
    * Returns NULL for non-built-ins.
    */
   ir_constant *constant_expression_value(exec_list *actual_parameters, struct hash_table *variable_context);

   /**
    * Get the name of the function for which this is a signature
    */
   const char *function_name() const;

   /**
    * Get a handle to the function for which this is a signature
    *
    * There is no setter function, this function returns a \c const pointer,
    * and \c ir_function_signature::_function is private for a reason.  The
    * only way to make a connection between a function and function signature
    * is via \c ir_function::add_signature.  This helps ensure that certain
    * invariants (i.e., a function signature is in the list of signatures for
    * its \c _function) are met.
    *
    * \sa ir_function::add_signature
    */
   inline const class ir_function *function() const
   {
      return this->_function;
   }

   /**
    * Check whether the qualifiers match between this signature's parameters
    * and the supplied parameter list.  If not, returns the name of the first
    * parameter with mismatched qualifiers (for use in error messages).
    */
   const char *qualifiers_match(exec_list *params);

   /**
    * Replace the current parameter list with the given one.  This is useful
    * if the current information came from a prototype, and either has invalid
    * or missing parameter names.
    */
   void replace_parameters(exec_list *new_params);

   /**
    * Function return type.
    */
   const struct glsl_type *return_type;

   glsl_precision precision;

   /**
    * List of ir_variable of function parameters.
    *
    * This represents the storage.  The paramaters passed in a particular
    * call will be in ir_call::actual_paramaters.
    */
   struct exec_list parameters;

   /** Whether or not this function has a body (which may be empty). */
   unsigned is_defined:1;

   /** Whether or not this function signature is a built-in. */
   bool is_builtin() const;

   /**
    * Whether or not this function is an intrinsic to be implemented
    * by the driver.
    */
   bool is_intrinsic;

   /** Whether or not a built-in is available for this shader. */
   bool is_builtin_available(const _mesa_glsl_parse_state *state) const;

   /** Body of instructions in the function. */
   struct exec_list body;

private:
   /**
    * A function pointer to a predicate that answers whether a built-in
    * function is available in the current shader.  NULL if not a built-in.
    */
   builtin_available_predicate builtin_avail;

   /** Function of which this signature is one overload. */
   class ir_function *_function;

   /** Function signature of which this one is a prototype clone */
   const ir_function_signature *origin;

   friend class ir_function;

   /**
    * Helper function to run a list of instructions for constant
    * expression evaluation.
    *
    * The hash table represents the values of the visible variables.
    * There are no scoping issues because the table is indexed on
    * ir_variable pointers, not variable names.
    *
    * Returns false if the expression is not constant, true otherwise,
    * and the value in *result if result is non-NULL.
    */
   bool constant_expression_evaluate_expression_list(const struct exec_list &body,
						     struct hash_table *variable_context,
						     ir_constant **result);
};


/**
 * Header for tracking multiple overloaded functions with the same name.
 * Contains a list of ir_function_signatures representing each of the
 * actual functions.
 */
class ir_function : public ir_instruction {
public:
   ir_function(const char *name);

   virtual ir_function *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   void add_signature(ir_function_signature *sig)
   {
      sig->_function = this;
      this->signatures.push_tail(sig);
   }

   /**
    * Find a signature that matches a set of actual parameters, taking implicit
    * conversions into account.  Also flags whether the match was exact.
    */
   ir_function_signature *matching_signature(_mesa_glsl_parse_state *state,
                                             const exec_list *actual_param,
                                             bool allow_builtins,
					     bool *match_is_exact);

   /**
    * Find a signature that matches a set of actual parameters, taking implicit
    * conversions into account.
    */
   ir_function_signature *matching_signature(_mesa_glsl_parse_state *state,
                                             const exec_list *actual_param,
                                             bool allow_builtins);

   /**
    * Find a signature that exactly matches a set of actual parameters without
    * any implicit type conversions.
    */
   ir_function_signature *exact_matching_signature(_mesa_glsl_parse_state *state,
                                                   const exec_list *actual_ps);

   /**
    * Name of the function.
    */
   const char *name;

   /** Whether or not this function has a signature that isn't a built-in. */
   bool has_user_signature();

   /**
    * List of ir_function_signature for each overloaded function with this name.
    */
   struct exec_list signatures;
};

inline const char *ir_function_signature::function_name() const
{
   return this->_function->name;
}
/*@}*/


/**
 * IR instruction representing high-level if-statements
 */
class ir_if : public ir_instruction {
public:
   ir_if(ir_rvalue *condition)
      : ir_instruction(ir_type_if), condition(condition)
   {
   }

   virtual ir_if *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_rvalue *condition;
   /** List of ir_instruction for the body of the then branch */
   exec_list  then_instructions;
   /** List of ir_instruction for the body of the else branch */
   exec_list  else_instructions;
};


/**
 * IR instruction representing a high-level loop structure.
 */
class ir_loop : public ir_instruction {
public:
   ir_loop();

   virtual ir_loop *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /** List of ir_instruction that make up the body of the loop. */
   exec_list body_instructions;
};


class ir_assignment : public ir_instruction {
public:
   ir_assignment(ir_rvalue *lhs, ir_rvalue *rhs, ir_rvalue *condition = NULL);

   /**
    * Construct an assignment with an explicit write mask
    *
    * \note
    * Since a write mask is supplied, the LHS must already be a bare
    * \c ir_dereference.  The cannot be any swizzles in the LHS.
    */
   ir_assignment(ir_dereference *lhs, ir_rvalue *rhs, ir_rvalue *condition,
		 unsigned write_mask);

   virtual ir_assignment *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /**
    * Get a whole variable written by an assignment
    *
    * If the LHS of the assignment writes a whole variable, the variable is
    * returned.  Otherwise \c NULL is returned.  Examples of whole-variable
    * assignment are:
    *
    *  - Assigning to a scalar
    *  - Assigning to all components of a vector
    *  - Whole array (or matrix) assignment
    *  - Whole structure assignment
    */
   ir_variable *whole_variable_written();

   /**
    * Set the LHS of an assignment
    */
   void set_lhs(ir_rvalue *lhs);

   /**
    * Left-hand side of the assignment.
    *
    * This should be treated as read only.  If you need to set the LHS of an
    * assignment, use \c ir_assignment::set_lhs.
    */
   ir_dereference *lhs;

   /**
    * Value being assigned
    */
   ir_rvalue *rhs;

   /**
    * Optional condition for the assignment.
    */
   ir_rvalue *condition;


   /**
    * Component mask written
    *
    * For non-vector types in the LHS, this field will be zero.  For vector
    * types, a bit will be set for each component that is written.  Note that
    * for \c vec2 and \c vec3 types only the lower bits will ever be set.
    *
    * A partially-set write mask means that each enabled channel gets
    * the value from a consecutive channel of the rhs.  For example,
    * to write just .xyw of gl_FrontColor with color:
    *
    * (assign (constant bool (1)) (xyw)
    *     (var_ref gl_FragColor)
    *     (swiz xyw (var_ref color)))
    */
   unsigned write_mask:4;
};

/* Update ir_expression::get_num_operands() and operator_strs when
 * updating this list.
 */
enum ir_expression_operation {
   ir_unop_bit_not,
   ir_unop_logic_not,
   ir_unop_neg,
   ir_unop_abs,
   ir_unop_sign,
   ir_unop_rcp,
   ir_unop_rsq,
   ir_unop_sqrt,
   ir_unop_normalize,
   ir_unop_exp,         /**< Log base e on gentype */
   ir_unop_log,	        /**< Natural log on gentype */
   ir_unop_exp2,
   ir_unop_log2,
   ir_unop_f2i,         /**< Float-to-integer conversion. */
   ir_unop_f2u,         /**< Float-to-unsigned conversion. */
   ir_unop_i2f,         /**< Integer-to-float conversion. */
   ir_unop_f2b,         /**< Float-to-boolean conversion */
   ir_unop_b2f,         /**< Boolean-to-float conversion */
   ir_unop_i2b,         /**< int-to-boolean conversion */
   ir_unop_b2i,         /**< Boolean-to-int conversion */
   ir_unop_u2f,         /**< Unsigned-to-float conversion. */
   ir_unop_i2u,         /**< Integer-to-unsigned conversion. */
   ir_unop_u2i,         /**< Unsigned-to-integer conversion. */
   ir_unop_bitcast_i2f, /**< Bit-identical int-to-float "conversion" */
   ir_unop_bitcast_f2i, /**< Bit-identical float-to-int "conversion" */
   ir_unop_bitcast_u2f, /**< Bit-identical uint-to-float "conversion" */
   ir_unop_bitcast_f2u, /**< Bit-identical float-to-uint "conversion" */
   ir_unop_any,

   /**
    * \name Unary floating-point rounding operations.
    */
   /*@{*/
   ir_unop_trunc,
   ir_unop_ceil,
   ir_unop_floor,
   ir_unop_fract,
   ir_unop_round_even,
   /*@}*/

   /**
    * \name Trigonometric operations.
    */
   /*@{*/
   ir_unop_sin,
   ir_unop_cos,
   ir_unop_sin_reduced,    /**< Reduced range sin. [-pi, pi] */
   ir_unop_cos_reduced,    /**< Reduced range cos. [-pi, pi] */
   /*@}*/

   /**
    * \name Partial derivatives.
    */
   /*@{*/
   ir_unop_dFdx,
   ir_unop_dFdx_coarse,
   ir_unop_dFdx_fine,
   ir_unop_dFdy,
   ir_unop_dFdy_coarse,
   ir_unop_dFdy_fine,
   /*@}*/

   /**
    * \name Floating point pack and unpack operations.
    */
   /*@{*/
   ir_unop_pack_snorm_2x16,
   ir_unop_pack_snorm_4x8,
   ir_unop_pack_unorm_2x16,
   ir_unop_pack_unorm_4x8,
   ir_unop_pack_half_2x16,
   ir_unop_unpack_snorm_2x16,
   ir_unop_unpack_snorm_4x8,
   ir_unop_unpack_unorm_2x16,
   ir_unop_unpack_unorm_4x8,
   ir_unop_unpack_half_2x16,
   /*@}*/

   /**
    * \name Lowered floating point unpacking operations.
    *
    * \see lower_packing_builtins_visitor::split_unpack_half_2x16
    */
   /*@{*/
   ir_unop_unpack_half_2x16_split_x,
   ir_unop_unpack_half_2x16_split_y,
   /*@}*/

   /**
    * \name Bit operations, part of ARB_gpu_shader5.
    */
   /*@{*/
   ir_unop_bitfield_reverse,
   ir_unop_bit_count,
   ir_unop_find_msb,
   ir_unop_find_lsb,
   /*@}*/

   ir_unop_saturate,
   ir_unop_noise,

   /**
    * Interpolate fs input at centroid
    *
    * operand0 is the fs input.
    */
   ir_unop_interpolate_at_centroid,

   /**
    * A sentinel marking the last of the unary operations.
    */
   ir_last_unop = ir_unop_interpolate_at_centroid,

   ir_binop_add,
   ir_binop_sub,
   ir_binop_mul,       /**< Floating-point or low 32-bit integer multiply. */
   ir_binop_imul_high, /**< Calculates the high 32-bits of a 64-bit multiply. */
   ir_binop_div,

   /**
    * Returns the carry resulting from the addition of the two arguments.
    */
   /*@{*/
   ir_binop_carry,
   /*@}*/

   /**
    * Returns the borrow resulting from the subtraction of the second argument
    * from the first argument.
    */
   /*@{*/
   ir_binop_borrow,
   /*@}*/

   /**
    * Takes one of two combinations of arguments:
    *
    * - mod(vecN, vecN)
    * - mod(vecN, float)
    *
    * Does not take integer types.
    */
   ir_binop_mod,

   /**
    * \name Binary comparison operators which return a boolean vector.
    * The type of both operands must be equal.
    */
   /*@{*/
   ir_binop_less,
   ir_binop_greater,
   ir_binop_lequal,
   ir_binop_gequal,
   ir_binop_equal,
   ir_binop_nequal,
   /**
    * Returns single boolean for whether all components of operands[0]
    * equal the components of operands[1].
    */
   ir_binop_all_equal,
   /**
    * Returns single boolean for whether any component of operands[0]
    * is not equal to the corresponding component of operands[1].
    */
   ir_binop_any_nequal,
   /*@}*/

   /**
    * \name Bit-wise binary operations.
    */
   /*@{*/
   ir_binop_lshift,
   ir_binop_rshift,
   ir_binop_bit_and,
   ir_binop_bit_xor,
   ir_binop_bit_or,
   /*@}*/

   ir_binop_logic_and,
   ir_binop_logic_xor,
   ir_binop_logic_or,

   ir_binop_dot,
   ir_binop_min,
   ir_binop_max,

   ir_binop_pow,

   /**
    * \name Lowered floating point packing operations.
    *
    * \see lower_packing_builtins_visitor::split_pack_half_2x16
    */
   /*@{*/
   ir_binop_pack_half_2x16_split,
   /*@}*/

   /**
    * \name First half of a lowered bitfieldInsert() operation.
    *
    * \see lower_instructions::bitfield_insert_to_bfm_bfi
    */
   /*@{*/
   ir_binop_bfm,
   /*@}*/

   /**
    * Load a value the size of a given GLSL type from a uniform block.
    *
    * operand0 is the ir_constant uniform block index in the linked shader.
    * operand1 is a byte offset within the uniform block.
    */
   ir_binop_ubo_load,

   /**
    * \name Multiplies a number by two to a power, part of ARB_gpu_shader5.
    */
   /*@{*/
   ir_binop_ldexp,
   /*@}*/

   /**
    * Extract a scalar from a vector
    *
    * operand0 is the vector
    * operand1 is the index of the field to read from operand0
    */
   ir_binop_vector_extract,

   /**
    * Interpolate fs input at offset
    *
    * operand0 is the fs input
    * operand1 is the offset from the pixel center
    */
   ir_binop_interpolate_at_offset,

   /**
    * Interpolate fs input at sample position
    *
    * operand0 is the fs input
    * operand1 is the sample ID
    */
   ir_binop_interpolate_at_sample,

   /**
    * A sentinel marking the last of the binary operations.
    */
   ir_last_binop = ir_binop_interpolate_at_sample,

   /**
    * \name Fused floating-point multiply-add, part of ARB_gpu_shader5.
    */
   /*@{*/
   ir_triop_fma,
   /*@}*/

   ir_triop_clamp,
   ir_triop_lrp,

   /**
    * \name Conditional Select
    *
    * A vector conditional select instruction (like ?:, but operating per-
    * component on vectors).
    *
    * \see lower_instructions_visitor::ldexp_to_arith
    */
   /*@{*/
   ir_triop_csel,
   /*@}*/

   /**
    * \name Second half of a lowered bitfieldInsert() operation.
    *
    * \see lower_instructions::bitfield_insert_to_bfm_bfi
    */
   /*@{*/
   ir_triop_bfi,
   /*@}*/

   ir_triop_bitfield_extract,

   /**
    * Generate a value with one field of a vector changed
    *
    * operand0 is the vector
    * operand1 is the value to write into the vector result
    * operand2 is the index in operand0 to be modified
    */
   ir_triop_vector_insert,

   /**
    * A sentinel marking the last of the ternary operations.
    */
   ir_last_triop = ir_triop_vector_insert,

   ir_quadop_bitfield_insert,

   ir_quadop_vector,

   /**
    * A sentinel marking the last of the ternary operations.
    */
   ir_last_quadop = ir_quadop_vector,

   /**
    * A sentinel marking the last of all operations.
    */
   ir_last_opcode = ir_quadop_vector
};

class ir_expression : public ir_rvalue {
public:
   ir_expression(int op, const struct glsl_type *type,
                 ir_rvalue *op0, ir_rvalue *op1 = NULL,
                 ir_rvalue *op2 = NULL, ir_rvalue *op3 = NULL);

   /**
    * Constructor for unary operation expressions
    */
   ir_expression(int op, ir_rvalue *);

   /**
    * Constructor for binary operation expressions
    */
   ir_expression(int op, ir_rvalue *op0, ir_rvalue *op1);

   /**
    * Constructor for ternary operation expressions
    */
   ir_expression(int op, ir_rvalue *op0, ir_rvalue *op1, ir_rvalue *op2);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   virtual ir_expression *clone(void *mem_ctx, struct hash_table *ht) const;

   /**
    * Attempt to constant-fold the expression
    *
    * The "variable_context" hash table links ir_variable * to ir_constant *
    * that represent the variables' values.  \c NULL represents an empty
    * context.
    *
    * If the expression cannot be constant folded, this method will return
    * \c NULL.
    */
   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   /**
    * Determine the number of operands used by an expression
    */
   static unsigned int get_num_operands(ir_expression_operation);

   /**
    * Determine the number of operands used by an expression
    */
   unsigned int get_num_operands() const
   {
      return (this->operation == ir_quadop_vector)
	 ? this->type->vector_elements : get_num_operands(operation);
   }

   /**
    * Return whether the expression operates on vectors horizontally.
    */
   bool is_horizontal() const
   {
      return operation == ir_binop_all_equal ||
             operation == ir_binop_any_nequal ||
             operation == ir_unop_any ||
             operation == ir_binop_dot ||
             operation == ir_quadop_vector;
   }

   /**
    * Return a string representing this expression's operator.
    */
   const char *operator_string();

   /**
    * Return a string representing this expression's operator.
    */
   static const char *operator_string(ir_expression_operation);


   /**
    * Do a reverse-lookup to translate the given string into an operator.
    */
   static ir_expression_operation get_operator(const char *);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_expression_operation operation;
   ir_rvalue *operands[4];
};


/**
 * HIR instruction representing a high-level function call, containing a list
 * of parameters and returning a value in the supplied temporary.
 */
class ir_call : public ir_instruction {
public:
   ir_call(ir_function_signature *callee,
	   ir_dereference_variable *return_deref,
	   exec_list *actual_parameters)
      : ir_instruction(ir_type_call), return_deref(return_deref), callee(callee)
   {
      assert(callee->return_type != NULL);
      actual_parameters->move_nodes_to(& this->actual_parameters);
      this->use_builtin = callee->is_builtin();
   }

   virtual ir_call *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /**
    * Get the name of the function being called.
    */
   const char *callee_name() const
   {
      return callee->function_name();
   }

   /**
    * Generates an inline version of the function before @ir,
    * storing the return value in return_deref.
    */
   void generate_inline(ir_instruction *ir);

   /**
    * Storage for the function's return value.
    * This must be NULL if the return type is void.
    */
   ir_dereference_variable *return_deref;

   /**
    * The specific function signature being called.
    */
   ir_function_signature *callee;

   /* List of ir_rvalue of paramaters passed in this call. */
   exec_list actual_parameters;

   /** Should this call only bind to a built-in function? */
   bool use_builtin;
};


/**
 * \name Jump-like IR instructions.
 *
 * These include \c break, \c continue, \c return, and \c discard.
 */
/*@{*/
class ir_jump : public ir_instruction {
protected:
   ir_jump(enum ir_node_type t)
      : ir_instruction(t)
   {
   }
};

class ir_return : public ir_jump {
public:
   ir_return()
      : ir_jump(ir_type_return), value(NULL)
   {
   }

   ir_return(ir_rvalue *value)
      : ir_jump(ir_type_return), value(value)
   {
   }

   virtual ir_return *clone(void *mem_ctx, struct hash_table *) const;

   ir_rvalue *get_value() const
   {
      return value;
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_rvalue *value;
};


/**
 * Jump instructions used inside loops
 *
 * These include \c break and \c continue.  The \c break within a loop is
 * different from the \c break within a switch-statement.
 *
 * \sa ir_switch_jump
 */
class ir_loop_jump : public ir_jump {
public:
   enum jump_mode {
      jump_break,
      jump_continue
   };

   ir_loop_jump(jump_mode mode)
      : ir_jump(ir_type_loop_jump)
   {
      this->mode = mode;
   }

   virtual ir_loop_jump *clone(void *mem_ctx, struct hash_table *) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   bool is_break() const
   {
      return mode == jump_break;
   }

   bool is_continue() const
   {
      return mode == jump_continue;
   }

   /** Mode selector for the jump instruction. */
   enum jump_mode mode;
};

/**
 * IR instruction representing discard statements.
 */
class ir_discard : public ir_jump {
public:
   ir_discard()
      : ir_jump(ir_type_discard)
   {
      this->condition = NULL;
   }

   ir_discard(ir_rvalue *cond)
      : ir_jump(ir_type_discard)
   {
      this->condition = cond;
   }

   virtual ir_discard *clone(void *mem_ctx, struct hash_table *ht) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_rvalue *condition;
};
/*@}*/


/**
 * Texture sampling opcodes used in ir_texture
 */
enum ir_texture_opcode {
   ir_tex,		/**< Regular texture look-up */
   ir_txb,		/**< Texture look-up with LOD bias */
   ir_txl,		/**< Texture look-up with explicit LOD */
   ir_txd,		/**< Texture look-up with partial derivatvies */
   ir_txf,		/**< Texel fetch with explicit LOD */
   ir_txf_ms,           /**< Multisample texture fetch */
   ir_txs,		/**< Texture size */
   ir_lod,		/**< Texture lod query */
   ir_tg4,		/**< Texture gather */
   ir_query_levels      /**< Texture levels query */
};


/**
 * IR instruction to sample a texture
 *
 * The specific form of the IR instruction depends on the \c mode value
 * selected from \c ir_texture_opcodes.  In the printed IR, these will
 * appear as:
 *
 *                                    Texel offset (0 or an expression)
 *                                    |
 *                                    v
 * (tex <type> <sampler> <coordinate> 0)
 * (txb <type> <sampler> <coordinate> 0 <bias>)
 * (txl <type> <sampler> <coordinate> 0 <lod>)
 * (txd <type> <sampler> <coordinate> 0 (dPdx dPdy))
 * (txf <type> <sampler> <coordinate> 0 <lod>)
 * (txf_ms
 *      <type> <sampler> <coordinate>   <sample_index>)
 * (txs <type> <sampler> <lod>)
 * (lod <type> <sampler> <coordinate>)
 * (tg4 <type> <sampler> <coordinate> <offset> <component>)
 * (query_levels <type> <sampler>)
 */
class ir_texture : public ir_rvalue {
public:
   ir_texture(enum ir_texture_opcode op)
      : ir_rvalue(ir_type_texture, glsl_precision_low),
        op(op), sampler(NULL), coordinate(NULL),
        offset(NULL)
   {
      memset(&lod_info, 0, sizeof(lod_info));
   }

   virtual ir_texture *clone(void *mem_ctx, struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   /**
    * Return a string representing the ir_texture_opcode.
    */
   const char *opcode_string();

   /** Set the sampler and type. */
   void set_sampler(ir_dereference *sampler, const glsl_type *type);

   static bool has_lod(const glsl_type *sampler_type);

   /**
    * Do a reverse-lookup to translate a string into an ir_texture_opcode.
    */
   static ir_texture_opcode get_opcode(const char *);

   enum ir_texture_opcode op;

   /** Sampler to use for the texture access. */
   ir_dereference *sampler;

   /** Texture coordinate to sample */
   ir_rvalue *coordinate;

   /** Texel offset. */
   ir_rvalue *offset;

   union {
      ir_rvalue *lod;		/**< Floating point LOD */
      ir_rvalue *bias;		/**< Floating point LOD bias */
      ir_rvalue *sample_index;  /**< MSAA sample index */
      ir_rvalue *component;     /**< Gather component selector */
      struct {
	 ir_rvalue *dPdx;	/**< Partial derivative of coordinate wrt X */
	 ir_rvalue *dPdy;	/**< Partial derivative of coordinate wrt Y */
      } grad;
   } lod_info;
};


struct ir_swizzle_mask {
   unsigned x:2;
   unsigned y:2;
   unsigned z:2;
   unsigned w:2;

   /**
    * Number of components in the swizzle.
    */
   unsigned num_components:3;

   /**
    * Does the swizzle contain duplicate components?
    *
    * L-value swizzles cannot contain duplicate components.
    */
   unsigned has_duplicates:1;
};


class ir_swizzle : public ir_rvalue {
public:
   ir_swizzle(ir_rvalue *, unsigned x, unsigned y, unsigned z, unsigned w,
              unsigned count);

   ir_swizzle(ir_rvalue *val, const unsigned *components, unsigned count);

   ir_swizzle(ir_rvalue *val, ir_swizzle_mask mask);

   virtual ir_swizzle *clone(void *mem_ctx, struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   /**
    * Construct an ir_swizzle from the textual representation.  Can fail.
    */
   static ir_swizzle *create(ir_rvalue *, const char *, unsigned vector_length);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   bool is_lvalue() const
   {
      return val->is_lvalue() && !mask.has_duplicates;
   }

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const;

   ir_rvalue *val;
   ir_swizzle_mask mask;

private:
   /**
    * Initialize the mask component of a swizzle
    *
    * This is used by the \c ir_swizzle constructors.
    */
   void init_mask(const unsigned *components, unsigned count);
};


class ir_dereference : public ir_rvalue {
public:
   virtual ir_dereference *clone(void *mem_ctx, struct hash_table *) const = 0;

   bool is_lvalue() const;

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const = 0;

protected:
   ir_dereference(ir_node_type t, glsl_precision precision) : ir_rvalue(t, precision) { }
};


class ir_dereference_variable : public ir_dereference {
public:
   ir_dereference_variable(ir_variable *var);

   virtual ir_dereference_variable *clone(void *mem_ctx,
					  struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const
   {
      return this->var;
   }

   virtual ir_variable *whole_variable_referenced()
   {
      /* ir_dereference_variable objects always dereference the entire
       * variable.  However, if this dereference is dereferenced by anything
       * else, the complete deferefernce chain is not a whole-variable
       * dereference.  This method should only be called on the top most
       * ir_rvalue in a dereference chain.
       */
      return this->var;
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /**
    * Object being dereferenced.
    */
   ir_variable *var;
};


class ir_dereference_array : public ir_dereference {
public:
   ir_dereference_array(ir_rvalue *value, ir_rvalue *array_index);

   ir_dereference_array(ir_variable *var, ir_rvalue *array_index);

   virtual ir_dereference_array *clone(void *mem_ctx,
				       struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const
   {
      return this->array->variable_referenced();
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_rvalue *array;
   ir_rvalue *array_index;

private:
   void set_array(ir_rvalue *value);
};


class ir_dereference_record : public ir_dereference {
public:
   ir_dereference_record(ir_rvalue *value, const char *field);

   ir_dereference_record(ir_variable *var, const char *field);

   virtual ir_dereference_record *clone(void *mem_ctx,
					struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   /**
    * Get the variable that is ultimately referenced by an r-value
    */
   virtual ir_variable *variable_referenced() const
   {
      return this->record->variable_referenced();
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   ir_rvalue *record;
   const char *field;
};


/**
 * Data stored in an ir_constant
 */
union ir_constant_data {
      unsigned u[16];
      int i[16];
      float f[16];
      bool b[16];
};


class ir_constant : public ir_rvalue {
public:
   ir_constant(const struct glsl_type *type, const ir_constant_data *data, glsl_precision precision = glsl_precision_undefined);
   ir_constant(bool b, unsigned vector_elements=1);
   ir_constant(unsigned int u, unsigned vector_elements=1);
   ir_constant(int i, unsigned vector_elements=1);
   ir_constant(float f, unsigned vector_elements=1);

   /**
    * Construct an ir_constant from a list of ir_constant values
    */
   ir_constant(const struct glsl_type *type, exec_list *values);

   /**
    * Construct an ir_constant from a scalar component of another ir_constant
    *
    * The new \c ir_constant inherits the type of the component from the
    * source constant.
    *
    * \note
    * In the case of a matrix constant, the new constant is a scalar, \b not
    * a vector.
    */
   ir_constant(const ir_constant *c, unsigned i);

   /**
    * Return a new ir_constant of the specified type containing all zeros.
    */
   static ir_constant *zero(void *mem_ctx, const glsl_type *type);

   virtual ir_constant *clone(void *mem_ctx, struct hash_table *) const;

   virtual ir_constant *constant_expression_value(struct hash_table *variable_context = NULL);

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   virtual bool equals(ir_instruction *ir, enum ir_node_type ignore = ir_type_unset);

   /**
    * Get a particular component of a constant as a specific type
    *
    * This is useful, for example, to get a value from an integer constant
    * as a float or bool.  This appears frequently when constructors are
    * called with all constant parameters.
    */
   /*@{*/
   bool get_bool_component(unsigned i) const;
   float get_float_component(unsigned i) const;
   int get_int_component(unsigned i) const;
   unsigned get_uint_component(unsigned i) const;
   /*@}*/

   ir_constant *get_array_element(unsigned i) const;

   ir_constant *get_record_field(const char *name);

   /**
    * Copy the values on another constant at a given offset.
    *
    * The offset is ignored for array or struct copies, it's only for
    * scalars or vectors into vectors or matrices.
    *
    * With identical types on both sides and zero offset it's clone()
    * without creating a new object.
    */

   void copy_offset(ir_constant *src, int offset);

   /**
    * Copy the values on another constant at a given offset and
    * following an assign-like mask.
    *
    * The mask is ignored for scalars.
    *
    * Note that this function only handles what assign can handle,
    * i.e. at most a vector as source and a column of a matrix as
    * destination.
    */

   void copy_masked_offset(ir_constant *src, int offset, unsigned int mask);

   /**
    * Determine whether a constant has the same value as another constant
    *
    * \sa ir_constant::is_zero, ir_constant::is_one,
    * ir_constant::is_negative_one, ir_constant::is_basis
    */
   bool has_value(const ir_constant *) const;

   /**
    * Return true if this ir_constant represents the given value.
    *
    * For vectors, this checks that each component is the given value.
    */
   virtual bool is_value(float f, int i) const;
   virtual bool is_zero() const;
   virtual bool is_one() const;
   virtual bool is_negative_one() const;
   virtual bool is_basis() const;

   /**
    * Return true for constants that could be stored as 16-bit unsigned values.
    *
    * Note that this will return true even for signed integer ir_constants, as
    * long as the value is non-negative and fits in 16-bits.
    */
   virtual bool is_uint16_constant() const;

   /**
    * Value of the constant.
    *
    * The field used to back the values supplied by the constant is determined
    * by the type associated with the \c ir_instruction.  Constants may be
    * scalars, vectors, or matrices.
    */
   union ir_constant_data value;

   /* Array elements */
   ir_constant **array_elements;

   /* Structure fields */
   exec_list components;

private:
   /**
    * Parameterless constructor only used by the clone method
    */
   ir_constant(void);
};


class ir_precision_statement : public ir_instruction {
public:
   ir_precision_statement(const char *statement_to_store)
	: ir_instruction(ir_type_precision)
   {
	   ir_type = ir_type_precision;
	   precision_statement = statement_to_store;
   }

   virtual ir_precision_statement *clone(void *mem_ctx, struct hash_table *) const;

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   /**
    * Precision statement
    */
   const char *precision_statement;
};


class ir_typedecl_statement : public ir_instruction {
public:
	ir_typedecl_statement(const glsl_type* type_decl)
	: ir_instruction(ir_type_typedecl)
	{
		this->ir_type = ir_type_typedecl;
		this->type_decl = type_decl;
	}
	
	virtual ir_typedecl_statement *clone(void *mem_ctx, struct hash_table *) const;
	
	virtual void accept(ir_visitor *v)
	{
		v->visit(this);
	}
	
	virtual ir_visitor_status accept(ir_hierarchical_visitor *);
	
	const glsl_type* type_decl;
};



/**
 * IR instruction to emit a vertex in a geometry shader.
 */
class ir_emit_vertex : public ir_instruction {
public:
   ir_emit_vertex(ir_rvalue *stream)
      : ir_instruction(ir_type_emit_vertex),
        stream(stream)
   {
      assert(stream);
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_emit_vertex *clone(void *mem_ctx, struct hash_table *ht) const
   {
      return new(mem_ctx) ir_emit_vertex(this->stream->clone(mem_ctx, ht));
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   int stream_id() const
   {
      return stream->as_constant()->value.i[0];
   }

   ir_rvalue *stream;
};

/**
 * IR instruction to complete the current primitive and start a new one in a
 * geometry shader.
 */
class ir_end_primitive : public ir_instruction {
public:
   ir_end_primitive(ir_rvalue *stream)
      : ir_instruction(ir_type_end_primitive),
        stream(stream)
   {
      assert(stream);
   }

   virtual void accept(ir_visitor *v)
   {
      v->visit(this);
   }

   virtual ir_end_primitive *clone(void *mem_ctx, struct hash_table *ht) const
   {
      return new(mem_ctx) ir_end_primitive(this->stream->clone(mem_ctx, ht));
   }

   virtual ir_visitor_status accept(ir_hierarchical_visitor *);

   int stream_id() const
   {
      return stream->as_constant()->value.i[0];
   }

   ir_rvalue *stream;
};

/*@}*/

/**
 * Apply a visitor to each IR node in a list
 */
void
visit_exec_list(exec_list *list, ir_visitor *visitor);

/**
 * Validate invariants on each IR node in a list
 */
void validate_ir_tree(exec_list *instructions);

struct _mesa_glsl_parse_state;
struct gl_shader_program;

/**
 * Detect whether an unlinked shader contains static recursion
 *
 * If the list of instructions is determined to contain static recursion,
 * \c _mesa_glsl_error will be called to emit error messages for each function
 * that is in the recursion cycle.
 */
void
detect_recursion_unlinked(struct _mesa_glsl_parse_state *state,
			  exec_list *instructions);

/**
 * Detect whether a linked shader contains static recursion
 *
 * If the list of instructions is determined to contain static recursion,
 * \c link_error_printf will be called to emit error messages for each function
 * that is in the recursion cycle.  In addition,
 * \c gl_shader_program::LinkStatus will be set to false.
 */
void
detect_recursion_linked(struct gl_shader_program *prog,
			exec_list *instructions);

/**
 * Make a clone of each IR instruction in a list
 *
 * \param in   List of IR instructions that are to be cloned
 * \param out  List to hold the cloned instructions
 */
void
clone_ir_list(void *mem_ctx, exec_list *out, const exec_list *in);

extern void
_mesa_glsl_initialize_variables(exec_list *instructions,
				struct _mesa_glsl_parse_state *state);

extern void
_mesa_glsl_initialize_builtin_functions();

extern ir_function_signature *
_mesa_glsl_find_builtin_function(_mesa_glsl_parse_state *state,
                                 const char *name, exec_list *actual_parameters);

extern gl_shader *
_mesa_glsl_get_builtin_function_shader(void);

extern void
_mesa_glsl_release_builtin_functions(void);

extern void
reparent_ir(exec_list *list, void *mem_ctx);

struct glsl_symbol_table;

extern void
import_prototypes(const exec_list *source, exec_list *dest,
		  struct glsl_symbol_table *symbols, void *mem_ctx);

extern void
do_set_program_inouts(exec_list *instructions, struct gl_program *prog,
                      gl_shader_stage shader_stage);

extern glsl_precision
precision_from_ir (ir_instruction* ir);


extern glsl_precision higher_precision (ir_instruction* a, ir_instruction* b);
static inline glsl_precision higher_precision (glsl_precision a, glsl_precision b)
{
	return MIN2 (a, b);
}

extern char *
prototype_string(const glsl_type *return_type, const char *name,
		 exec_list *parameters);

const char *
mode_string(const ir_variable *var);

/**
 * Built-in / reserved GL variables names start with "gl_"
 */
static inline bool
is_gl_identifier(const char *s)
{
   return s && s[0] == 'g' && s[1] == 'l' && s[2] == '_';
}

extern "C" {
#endif /* __cplusplus */

extern void _mesa_print_ir(FILE *f, struct exec_list *instructions,
                           struct _mesa_glsl_parse_state *state);

extern void
fprint_ir(FILE *f, const void *instruction);

#ifdef __cplusplus
} /* extern "C" */
#endif

unsigned
vertices_per_prim(GLenum prim);

#endif /* IR_H */

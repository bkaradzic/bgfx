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

#include "glsl_symbol_table.h"
#include "ast.h"
#include "glsl_types.h"
#include "ir.h"
#include "main/core.h" /* for MIN2 */

static ir_rvalue *
convert_component(ir_rvalue *src, const glsl_type *desired_type);

bool
apply_implicit_conversion(const glsl_type *to, ir_rvalue * &from,
                          struct _mesa_glsl_parse_state *state);

static unsigned
process_parameters(exec_list *instructions, exec_list *actual_parameters,
		   exec_list *parameters,
		   struct _mesa_glsl_parse_state *state)
{
   unsigned count = 0;

   foreach_list_typed(ast_node, ast, link, parameters) {
      ir_rvalue *result = ast->hir(instructions, state);

      ir_constant *const constant = result->constant_expression_value();
      if (constant != NULL)
	 result = constant;

      actual_parameters->push_tail(result);
      count++;
   }

   return count;
}


/**
 * Generate a source prototype for a function signature
 *
 * \param return_type Return type of the function.  May be \c NULL.
 * \param name        Name of the function.
 * \param parameters  List of \c ir_instruction nodes representing the
 *                    parameter list for the function.  This may be either a
 *                    formal (\c ir_variable) or actual (\c ir_rvalue)
 *                    parameter list.  Only the type is used.
 *
 * \return
 * A ralloced string representing the prototype of the function.
 */
char *
prototype_string(const glsl_type *return_type, const char *name,
		 exec_list *parameters)
{
   char *str = NULL;

   if (return_type != NULL)
      str = ralloc_asprintf(NULL, "%s ", return_type->name);

   ralloc_asprintf_append(&str, "%s(", name);

   const char *comma = "";
   foreach_in_list(const ir_variable, param, parameters) {
      ralloc_asprintf_append(&str, "%s%s", comma, param->type->name);
      comma = ", ";
   }

   ralloc_strcat(&str, ")");
   return str;
}

static glsl_precision precision_for_call (const ir_function_signature* sig, glsl_precision max_prec, glsl_precision first_prec)
{
	if (sig->precision != glsl_precision_undefined)
		return sig->precision;
	
	// if return type is boolean, treat as lowp
	if (sig->return_type->base_type == GLSL_TYPE_BOOL)
		return glsl_precision_low;
	
	// if it's a built-in texture function, precision comes from sampler (1st param) precision
	if (sig->is_builtin())
	{
		if (strncmp (sig->function_name(), "texture", 7) == 0)
			return first_prec;
		if (strncmp (sig->function_name(), "shadow", 6) == 0)
			return first_prec;
	}
	
	// other built-in: max precision of parameters
	if (sig->is_builtin())
		return max_prec;
	
	// otherwise: undefined
	return glsl_precision_undefined;	
}


static glsl_precision precision_for_call (const ir_function_signature* sig, exec_list *actual_parameters)
{
	glsl_precision prec_params_max = glsl_precision_undefined;
	glsl_precision prec_params_first = glsl_precision_undefined;
	int params_counter = 0;
	
	foreach_two_lists(formal_node, &sig->parameters,
					  actual_node, actual_parameters) {
		ir_rvalue *actual = (ir_rvalue *) actual_node;
		ir_variable *formal = (ir_variable *) formal_node;
		assert(actual != NULL);
		assert(formal != NULL);
		glsl_precision param_prec = (glsl_precision)formal->data.precision;
		if (param_prec == glsl_precision_undefined)
			param_prec = actual->get_precision();
		prec_params_max = higher_precision (prec_params_max, param_prec);
		if (params_counter == 0)
			prec_params_first = param_prec;
		
		++params_counter;
	}
	
	return precision_for_call (sig, prec_params_max, prec_params_first);
}

static bool
verify_image_parameter(YYLTYPE *loc, _mesa_glsl_parse_state *state,
                       const ir_variable *formal, const ir_variable *actual)
{
   /**
    * From the ARB_shader_image_load_store specification:
    *
    * "The values of image variables qualified with coherent,
    *  volatile, restrict, readonly, or writeonly may not be passed
    *  to functions whose formal parameters lack such
    *  qualifiers. [...] It is legal to have additional qualifiers
    *  on a formal parameter, but not to have fewer."
    */
   if (actual->data.image_coherent && !formal->data.image_coherent) {
      _mesa_glsl_error(loc, state,
                       "function call parameter `%s' drops "
                       "`coherent' qualifier", formal->name);
      return false;
   }

   if (actual->data.image_volatile && !formal->data.image_volatile) {
      _mesa_glsl_error(loc, state,
                       "function call parameter `%s' drops "
                       "`volatile' qualifier", formal->name);
      return false;
   }

   if (actual->data.image_restrict && !formal->data.image_restrict) {
      _mesa_glsl_error(loc, state,
                       "function call parameter `%s' drops "
                       "`restrict' qualifier", formal->name);
      return false;
   }

   if (actual->data.image_read_only && !formal->data.image_read_only) {
      _mesa_glsl_error(loc, state,
                       "function call parameter `%s' drops "
                       "`readonly' qualifier", formal->name);
      return false;
   }

   if (actual->data.image_write_only && !formal->data.image_write_only) {
      _mesa_glsl_error(loc, state,
                       "function call parameter `%s' drops "
                       "`writeonly' qualifier", formal->name);
      return false;
   }

   return true;
}


/**
 * Verify that 'out' and 'inout' actual parameters are lvalues.  Also, verify
 * that 'const_in' formal parameters (an extension in our IR) correspond to
 * ir_constant actual parameters.
 */
static bool
verify_parameter_modes(_mesa_glsl_parse_state *state,
		       ir_function_signature *sig,
		       exec_list &actual_ir_parameters,
		       exec_list &actual_ast_parameters)
{
   exec_node *actual_ir_node  = actual_ir_parameters.head;
   exec_node *actual_ast_node = actual_ast_parameters.head;

   foreach_in_list(const ir_variable, formal, &sig->parameters) {
      /* The lists must be the same length. */
      assert(!actual_ir_node->is_tail_sentinel());
      assert(!actual_ast_node->is_tail_sentinel());

      const ir_rvalue *const actual = (ir_rvalue *) actual_ir_node;
      const ast_expression *const actual_ast =
	 exec_node_data(ast_expression, actual_ast_node, link);

      /* FIXME: 'loc' is incorrect (as of 2011-01-21). It is always
       * FIXME: 0:0(0).
       */
      YYLTYPE loc = actual_ast->get_location();

      /* Verify that 'const_in' parameters are ir_constants. */
      if (formal->data.mode == ir_var_const_in &&
	  actual->ir_type != ir_type_constant) {
	 _mesa_glsl_error(&loc, state,
			  "parameter `in %s' must be a constant expression",
			  formal->name);
	 return false;
      }

      /* Verify that shader_in parameters are shader inputs */
      if (formal->data.must_be_shader_input) {
         ir_variable *var = actual->variable_referenced();
         if (var && var->data.mode != ir_var_shader_in) {
            _mesa_glsl_error(&loc, state,
                             "parameter `%s` must be a shader input",
                             formal->name);
            return false;
         }

         if (actual->ir_type == ir_type_swizzle) {
            _mesa_glsl_error(&loc, state,
                             "parameter `%s` must not be swizzled",
                             formal->name);
            return false;
         }
      }

      /* Verify that 'out' and 'inout' actual parameters are lvalues. */
      if (formal->data.mode == ir_var_function_out
          || formal->data.mode == ir_var_function_inout) {
	 const char *mode = NULL;
	 switch (formal->data.mode) {
	 case ir_var_function_out:   mode = "out";   break;
	 case ir_var_function_inout: mode = "inout"; break;
	 default:                    assert(false);  break;
	 }

	 /* This AST-based check catches errors like f(i++).  The IR-based
	  * is_lvalue() is insufficient because the actual parameter at the
	  * IR-level is just a temporary value, which is an l-value.
	  */
	 if (actual_ast->non_lvalue_description != NULL) {
	    _mesa_glsl_error(&loc, state,
			     "function parameter '%s %s' references a %s",
			     mode, formal->name,
			     actual_ast->non_lvalue_description);
	    return false;
	 }

	 ir_variable *var = actual->variable_referenced();
	 if (var)
	    var->data.assigned = true;

	 if (var && var->data.read_only) {
	    _mesa_glsl_error(&loc, state,
			     "function parameter '%s %s' references the "
			     "read-only variable '%s'",
			     mode, formal->name,
			     actual->variable_referenced()->name);
	    return false;
	 } else if (!actual->is_lvalue()) {
            /* Even though ir_binop_vector_extract is not an l-value, let it
             * slop through.  generate_call will handle it correctly.
             */
            ir_expression *const expr = ((ir_rvalue *) actual)->as_expression();
            if (expr == NULL
                || expr->operation != ir_binop_vector_extract
                || !expr->operands[0]->is_lvalue()) {
               _mesa_glsl_error(&loc, state,
                                "function parameter '%s %s' is not an lvalue",
                                mode, formal->name);
               return false;
            }
	 }
      }

      if (formal->type->is_image() &&
          actual->variable_referenced()) {
         if (!verify_image_parameter(&loc, state, formal,
                                     actual->variable_referenced()))
            return false;
      }

      actual_ir_node  = actual_ir_node->next;
      actual_ast_node = actual_ast_node->next;
   }
   return true;
}

static void
fix_parameter(void *mem_ctx, ir_rvalue *actual, const glsl_type *formal_type,
              exec_list *before_instructions, exec_list *after_instructions,
              bool parameter_is_inout, glsl_precision prec)
{
   ir_expression *const expr = actual->as_expression();

   /* If the types match exactly and the parameter is not a vector-extract,
    * nothing needs to be done to fix the parameter.
    */
   if (formal_type == actual->type
       && (expr == NULL || expr->operation != ir_binop_vector_extract))
      return;

   /* To convert an out parameter, we need to create a temporary variable to
    * hold the value before conversion, and then perform the conversion after
    * the function call returns.
    *
    * This has the effect of transforming code like this:
    *
    *   void f(out int x);
    *   float value;
    *   f(value);
    *
    * Into IR that's equivalent to this:
    *
    *   void f(out int x);
    *   float value;
    *   int out_parameter_conversion;
    *   f(out_parameter_conversion);
    *   value = float(out_parameter_conversion);
    *
    * If the parameter is an ir_expression of ir_binop_vector_extract,
    * additional conversion is needed in the post-call re-write.
    */
   ir_variable *tmp =
      new(mem_ctx) ir_variable(formal_type, "inout_tmp", ir_var_temporary, prec);

   before_instructions->push_tail(tmp);

   /* If the parameter is an inout parameter, copy the value of the actual
    * parameter to the new temporary.  Note that no type conversion is allowed
    * here because inout parameters must match types exactly.
    */
   if (parameter_is_inout) {
      /* Inout parameters should never require conversion, since that would
       * require an implicit conversion to exist both to and from the formal
       * parameter type, and there are no bidirectional implicit conversions.
       */
      assert (actual->type == formal_type);

      ir_dereference_variable *const deref_tmp_1 =
         new(mem_ctx) ir_dereference_variable(tmp);
      ir_assignment *const assignment =
         new(mem_ctx) ir_assignment(deref_tmp_1, actual);
      before_instructions->push_tail(assignment);
   }

   /* Replace the parameter in the call with a dereference of the new
    * temporary.
    */
   ir_dereference_variable *const deref_tmp_2 =
      new(mem_ctx) ir_dereference_variable(tmp);
   actual->replace_with(deref_tmp_2);


   /* Copy the temporary variable to the actual parameter with optional
    * type conversion applied.
    */
   ir_rvalue *rhs = new(mem_ctx) ir_dereference_variable(tmp);
   if (actual->type != formal_type)
      rhs = convert_component(rhs, actual->type);

   ir_rvalue *lhs = actual;
   if (expr != NULL && expr->operation == ir_binop_vector_extract) {
      rhs = new(mem_ctx) ir_expression(ir_triop_vector_insert,
                                       expr->operands[0]->type,
                                       expr->operands[0]->clone(mem_ctx, NULL),
                                       rhs,
                                       expr->operands[1]->clone(mem_ctx, NULL));
      lhs = expr->operands[0]->clone(mem_ctx, NULL);
   }

   ir_assignment *const assignment_2 = new(mem_ctx) ir_assignment(lhs, rhs);
   after_instructions->push_tail(assignment_2);
}

/**
 * Generate a function call.
 *
 * For non-void functions, this returns a dereference of the temporary variable
 * which stores the return value for the call.  For void functions, this returns
 * NULL.
 */
static ir_rvalue *
generate_call(exec_list *instructions, ir_function_signature *sig,
	      exec_list *actual_parameters,
	      struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   exec_list post_call_conversions;

   /* Perform implicit conversion of arguments.  For out parameters, we need
    * to place them in a temporary variable and do the conversion after the
    * call takes place.  Since we haven't emitted the call yet, we'll place
    * the post-call conversions in a temporary exec_list, and emit them later.
    */
   foreach_two_lists(formal_node, &sig->parameters,
                     actual_node, actual_parameters) {
      ir_rvalue *actual = (ir_rvalue *) actual_node;
      ir_variable *formal = (ir_variable *) formal_node;

      if (formal->type->is_numeric() || formal->type->is_boolean()) {
	 switch (formal->data.mode) {
	 case ir_var_const_in:
	 case ir_var_function_in: {
	    ir_rvalue *converted
	       = convert_component(actual, formal->type);
	    actual->replace_with(converted);
	    break;
	 }
	 case ir_var_function_out:
	 case ir_var_function_inout:
            fix_parameter(ctx, actual, formal->type,
                          instructions, &post_call_conversions,
                          formal->data.mode == ir_var_function_inout,
						  precision_for_call(sig,actual_parameters));
	    break;
	 default:
	    assert (!"Illegal formal parameter mode");
	    break;
	 }
      }
   }

   /* If the function call is a constant expression, don't generate any
    * instructions; just generate an ir_constant.
    *
    * Function calls were first allowed to be constant expressions in GLSL
    * 1.20 and GLSL ES 3.00.
    */
   if (state->is_version(120, 300)) {
      ir_constant *value = sig->constant_expression_value(actual_parameters, NULL);
      if (value != NULL) {
	 return value;
      }
   }

   ir_dereference_variable *deref = NULL;
   if (!sig->return_type->is_void()) {
      /* Create a new temporary to hold the return value. */
      char *const name = ir_variable::temporaries_allocate_names
         ? ralloc_asprintf(ctx, "%s_retval", sig->function_name())
         : NULL;

      ir_variable *var;

      var = new(ctx) ir_variable(sig->return_type, name, ir_var_temporary, precision_for_call(sig,actual_parameters));
      instructions->push_tail(var);

      ralloc_free(name);

      deref = new(ctx) ir_dereference_variable(var);
   }
   ir_call *call = new(ctx) ir_call(sig, deref, actual_parameters);
   instructions->push_tail(call);

   /* Also emit any necessary out-parameter conversions. */
   instructions->append_list(&post_call_conversions);

   return deref ? deref->clone(ctx, NULL) : NULL;
}

/**
 * Given a function name and parameter list, find the matching signature.
 */
static ir_function_signature *
match_function_by_name(const char *name,
		       exec_list *actual_parameters,
		       struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   ir_function *f = state->symbols->get_function(name);
   ir_function_signature *local_sig = NULL;
   ir_function_signature *sig = NULL;

   /* Is the function hidden by a record type constructor? */
   if (state->symbols->get_type(name))
      goto done; /* no match */

   /* Is the function hidden by a variable (impossible in 1.10)? */
   if (!state->symbols->separate_function_namespace
       && state->symbols->get_variable(name))
      goto done; /* no match */

   if (f != NULL) {
      /* In desktop GL, the presence of a user-defined signature hides any
       * built-in signatures, so we must ignore them.  In contrast, in ES2
       * user-defined signatures add new overloads, so we must consider them.
       */
      bool allow_builtins = state->es_shader || !f->has_user_signature();

      /* Look for a match in the local shader.  If exact, we're done. */
      bool is_exact = false;
      sig = local_sig = f->matching_signature(state, actual_parameters,
                                              allow_builtins, &is_exact);
      if (is_exact)
	 goto done;

      if (!allow_builtins)
	 goto done;
   }

   /* Local shader has no exact candidates; check the built-ins. */
   _mesa_glsl_initialize_builtin_functions();
   sig = _mesa_glsl_find_builtin_function(state, name, actual_parameters);

done:
   if (sig != NULL) {
      /* If the match is from a linked built-in shader, import the prototype. */
      if (sig != local_sig) {
	 if (f == NULL) {
	    f = new(ctx) ir_function(name);
	    state->symbols->add_global_function(f);
	    emit_function(state, f);
	 }
	 f->add_signature(sig->clone_prototype(f, NULL));
      }
   }
   return sig;
}

static void
print_function_prototypes(_mesa_glsl_parse_state *state, YYLTYPE *loc,
                          ir_function *f)
{
   if (f == NULL)
      return;

   foreach_in_list(ir_function_signature, sig, &f->signatures) {
      if (sig->is_builtin() && !sig->is_builtin_available(state))
         continue;

      char *str = prototype_string(sig->return_type, f->name, &sig->parameters);
      _mesa_glsl_error(loc, state, "   %s", str);
      ralloc_free(str);
   }
}

/**
 * Raise a "no matching function" error, listing all possible overloads the
 * compiler considered so developers can figure out what went wrong.
 */
static void
no_matching_function_error(const char *name,
			   YYLTYPE *loc,
			   exec_list *actual_parameters,
			   _mesa_glsl_parse_state *state)
{
   gl_shader *sh = _mesa_glsl_get_builtin_function_shader();

   if (state->symbols->get_function(name) == NULL
      && (!state->uses_builtin_functions
          || sh->symbols->get_function(name) == NULL)) {
      _mesa_glsl_error(loc, state, "no function with name '%s'", name);
   } else {
      char *str = prototype_string(NULL, name, actual_parameters);
      _mesa_glsl_error(loc, state,
                       "no matching function for call to `%s'; candidates are:",
                       str);
      ralloc_free(str);

      print_function_prototypes(state, loc, state->symbols->get_function(name));

      if (state->uses_builtin_functions) {
         print_function_prototypes(state, loc, sh->symbols->get_function(name));
      }
   }
}

/**
 * Perform automatic type conversion of constructor parameters
 *
 * This implements the rules in the "Conversion and Scalar Constructors"
 * section (GLSL 1.10 section 5.4.1), not the "Implicit Conversions" rules.
 */
static ir_rvalue *
convert_component(ir_rvalue *src, const glsl_type *desired_type)
{
   void *ctx = ralloc_parent(src);
   const unsigned a = desired_type->base_type;
   const unsigned b = src->type->base_type;
   ir_expression *result = NULL;

   if (src->type->is_error())
      return src;

   assert(a <= GLSL_TYPE_BOOL);
   assert(b <= GLSL_TYPE_BOOL);

   if (a == b)
      return src;

   switch (a) {
   case GLSL_TYPE_UINT:
      switch (b) {
      case GLSL_TYPE_INT:
	 result = new(ctx) ir_expression(ir_unop_i2u, src);
	 break;
      case GLSL_TYPE_FLOAT:
	 result = new(ctx) ir_expression(ir_unop_f2u, src);
	 break;
      case GLSL_TYPE_BOOL:
	 result = new(ctx) ir_expression(ir_unop_i2u,
		  new(ctx) ir_expression(ir_unop_b2i, src));
	 break;
      }
      break;
   case GLSL_TYPE_INT:
      switch (b) {
      case GLSL_TYPE_UINT:
	 result = new(ctx) ir_expression(ir_unop_u2i, src);
	 break;
      case GLSL_TYPE_FLOAT:
	 result = new(ctx) ir_expression(ir_unop_f2i, src);
	 break;
      case GLSL_TYPE_BOOL:
	 result = new(ctx) ir_expression(ir_unop_b2i, src);
	 break;
      }
      break;
   case GLSL_TYPE_FLOAT:
      switch (b) {
      case GLSL_TYPE_UINT:
	 result = new(ctx) ir_expression(ir_unop_u2f, desired_type, src, NULL);
	 break;
      case GLSL_TYPE_INT:
	 result = new(ctx) ir_expression(ir_unop_i2f, desired_type, src, NULL);
	 break;
      case GLSL_TYPE_BOOL:
	 result = new(ctx) ir_expression(ir_unop_b2f, desired_type, src, NULL);
	 break;
      }
      break;
   case GLSL_TYPE_BOOL:
      switch (b) {
      case GLSL_TYPE_UINT:
	 result = new(ctx) ir_expression(ir_unop_i2b,
		  new(ctx) ir_expression(ir_unop_u2i, src));
	 break;
      case GLSL_TYPE_INT:
	 result = new(ctx) ir_expression(ir_unop_i2b, desired_type, src, NULL);
	 break;
      case GLSL_TYPE_FLOAT:
	 result = new(ctx) ir_expression(ir_unop_f2b, desired_type, src, NULL);
	 break;
      }
      break;
   }

   assert(result != NULL);
   assert(result->type == desired_type);

   /* Try constant folding; it may fold in the conversion we just added. */
   ir_constant *const constant = result->constant_expression_value();
   return (constant != NULL) ? (ir_rvalue *) constant : (ir_rvalue *) result;
}

/**
 * Dereference a specific component from a scalar, vector, or matrix
 */
static ir_rvalue *
dereference_component(ir_rvalue *src, unsigned component)
{
   void *ctx = ralloc_parent(src);
   assert(component < src->type->components());

   /* If the source is a constant, just create a new constant instead of a
    * dereference of the existing constant.
    */
   ir_constant *constant = src->as_constant();
   if (constant)
      return new(ctx) ir_constant(constant, component);

   if (src->type->is_scalar()) {
      return src;
   } else if (src->type->is_vector()) {
      return new(ctx) ir_swizzle(src, component, 0, 0, 0, 1);
   } else {
      assert(src->type->is_matrix());

      /* Dereference a row of the matrix, then call this function again to get
       * a specific element from that row.
       */
      const int c = component / src->type->column_type()->vector_elements;
      const int r = component % src->type->column_type()->vector_elements;
      ir_constant *const col_index = new(ctx) ir_constant(c);
      ir_dereference *const col = new(ctx) ir_dereference_array(src, col_index);

      col->type = src->type->column_type();

      return dereference_component(col, r);
   }

   assert(!"Should not get here.");
   return NULL;
}


static ir_rvalue *
process_vec_mat_constructor(exec_list *instructions,
                            const glsl_type *constructor_type,
                            YYLTYPE *loc, exec_list *parameters,
                            struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;

   /* The ARB_shading_language_420pack spec says:
    *
    * "If an initializer is a list of initializers enclosed in curly braces,
    *  the variable being declared must be a vector, a matrix, an array, or a
    *  structure.
    *
    *      int i = { 1 }; // illegal, i is not an aggregate"
    */
   if (constructor_type->vector_elements <= 1) {
      _mesa_glsl_error(loc, state, "aggregates can only initialize vectors, "
                       "matrices, arrays, and structs");
      return ir_rvalue::error_value(ctx);
   }

   exec_list actual_parameters;
   const unsigned parameter_count =
      process_parameters(instructions, &actual_parameters, parameters, state);

   if (parameter_count == 0
       || (constructor_type->is_vector() &&
           constructor_type->vector_elements != parameter_count)
       || (constructor_type->is_matrix() &&
           constructor_type->matrix_columns != parameter_count)) {
      _mesa_glsl_error(loc, state, "%s constructor must have %u parameters",
                       constructor_type->is_vector() ? "vector" : "matrix",
                       constructor_type->vector_elements);
      return ir_rvalue::error_value(ctx);
   }

   bool all_parameters_are_constant = true;

   /* Type cast each parameter and, if possible, fold constants. */
   foreach_in_list_safe(ir_rvalue, ir, &actual_parameters) {
      ir_rvalue *result = ir;

      /* Apply implicit conversions (not the scalar constructor rules!). See
       * the spec quote above. */
      if (constructor_type->is_float()) {
         const glsl_type *desired_type =
            glsl_type::get_instance(GLSL_TYPE_FLOAT,
                                    ir->type->vector_elements,
                                    ir->type->matrix_columns);
         if (result->type->can_implicitly_convert_to(desired_type, state)) {
            /* Even though convert_component() implements the constructor
             * conversion rules (not the implicit conversion rules), its safe
             * to use it here because we already checked that the implicit
             * conversion is legal.
             */
            result = convert_component(ir, desired_type);
         }
      }

      if (constructor_type->is_matrix()) {
         if (result->type != constructor_type->column_type()) {
            _mesa_glsl_error(loc, state, "type error in matrix constructor: "
                             "expected: %s, found %s",
                             constructor_type->column_type()->name,
                             result->type->name);
            return ir_rvalue::error_value(ctx);
         }
      } else if (result->type != constructor_type->get_scalar_type()) {
         _mesa_glsl_error(loc, state, "type error in vector constructor: "
                          "expected: %s, found %s",
                          constructor_type->get_scalar_type()->name,
                          result->type->name);
         return ir_rvalue::error_value(ctx);
      }

      /* Attempt to convert the parameter to a constant valued expression.
       * After doing so, track whether or not all the parameters to the
       * constructor are trivially constant valued expressions.
       */
      ir_rvalue *const constant = result->constant_expression_value();

      if (constant != NULL)
         result = constant;
      else
         all_parameters_are_constant = false;

      ir->replace_with(result);
   }

   if (all_parameters_are_constant)
      return new(ctx) ir_constant(constructor_type, &actual_parameters);

   ir_variable *var = new(ctx) ir_variable(constructor_type, "vec_mat_ctor",
                                           ir_var_temporary, glsl_precision_undefined);
   instructions->push_tail(var);

   int i = 0;

   foreach_in_list(ir_rvalue, rhs, &actual_parameters) {
      ir_instruction *assignment = NULL;

      if (var->type->is_matrix()) {
         ir_rvalue *lhs = new(ctx) ir_dereference_array(var,
                                             new(ctx) ir_constant(i));
         assignment = new(ctx) ir_assignment(lhs, rhs, NULL);
      } else {
         /* use writemask rather than index for vector */
         assert(var->type->is_vector());
         assert(i < 4);
         ir_dereference *lhs = new(ctx) ir_dereference_variable(var);
         assignment = new(ctx) ir_assignment(lhs, rhs, NULL, (unsigned)(1 << i));
      }

      instructions->push_tail(assignment);

      i++;
   }

   return new(ctx) ir_dereference_variable(var);
}


static ir_rvalue *
process_array_constructor(exec_list *instructions,
			  const glsl_type *constructor_type,
			  YYLTYPE *loc, exec_list *parameters,
			  struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   /* Array constructors come in two forms: sized and unsized.  Sized array
    * constructors look like 'vec4[2](a, b)', where 'a' and 'b' are vec4
    * variables.  In this case the number of parameters must exactly match the
    * specified size of the array.
    *
    * Unsized array constructors look like 'vec4[](a, b)', where 'a' and 'b'
    * are vec4 variables.  In this case the size of the array being constructed
    * is determined by the number of parameters.
    *
    * From page 52 (page 58 of the PDF) of the GLSL 1.50 spec:
    *
    *    "There must be exactly the same number of arguments as the size of
    *    the array being constructed. If no size is present in the
    *    constructor, then the array is explicitly sized to the number of
    *    arguments provided. The arguments are assigned in order, starting at
    *    element 0, to the elements of the constructed array. Each argument
    *    must be the same type as the element type of the array, or be a type
    *    that can be converted to the element type of the array according to
    *    Section 4.1.10 "Implicit Conversions.""
    */
   exec_list actual_parameters;
   const unsigned parameter_count =
      process_parameters(instructions, &actual_parameters, parameters, state);
   bool is_unsized_array = constructor_type->is_unsized_array();

   if ((parameter_count == 0) ||
       (!is_unsized_array && (constructor_type->length != parameter_count))) {
      const unsigned min_param = is_unsized_array
         ? 1 : constructor_type->length;

      _mesa_glsl_error(loc, state, "array constructor must have %s %u "
		       "parameter%s",
		       is_unsized_array ? "at least" : "exactly",
		       min_param, (min_param <= 1) ? "" : "s");
      return ir_rvalue::error_value(ctx);
   }

   if (is_unsized_array) {
      constructor_type =
	 glsl_type::get_array_instance(constructor_type->element_type(),
				       parameter_count);
      assert(constructor_type != NULL);
      assert(constructor_type->length == parameter_count);
   }

   bool all_parameters_are_constant = true;

   /* Type cast each parameter and, if possible, fold constants. */
   foreach_in_list_safe(ir_rvalue, ir, &actual_parameters) {
      ir_rvalue *result = ir;

      /* Apply implicit conversions (not the scalar constructor rules!). See
       * the spec quote above. */
      if (constructor_type->element_type()->is_float()) {
	 const glsl_type *desired_type =
	    glsl_type::get_instance(GLSL_TYPE_FLOAT,
				    ir->type->vector_elements,
				    ir->type->matrix_columns);
	 if (result->type->can_implicitly_convert_to(desired_type, state)) {
	    /* Even though convert_component() implements the constructor
	     * conversion rules (not the implicit conversion rules), its safe
	     * to use it here because we already checked that the implicit
	     * conversion is legal.
	     */
	    result = convert_component(ir, desired_type);
	 }
      }

      if (result->type != constructor_type->element_type()) {
	 _mesa_glsl_error(loc, state, "type error in array constructor: "
			  "expected: %s, found %s",
			  constructor_type->element_type()->name,
			  result->type->name);
         return ir_rvalue::error_value(ctx);
      }

      /* Attempt to convert the parameter to a constant valued expression.
       * After doing so, track whether or not all the parameters to the
       * constructor are trivially constant valued expressions.
       */
      ir_rvalue *const constant = result->constant_expression_value();

      if (constant != NULL)
         result = constant;
      else
         all_parameters_are_constant = false;

      ir->replace_with(result);
   }

   if (all_parameters_are_constant)
      return new(ctx) ir_constant(constructor_type, &actual_parameters);

   ir_variable *var = new(ctx) ir_variable(constructor_type, "array_ctor",
					   ir_var_temporary, glsl_precision_undefined);
   instructions->push_tail(var);

   int i = 0;
   foreach_in_list(ir_rvalue, rhs, &actual_parameters) {
      ir_rvalue *lhs = new(ctx) ir_dereference_array(var,
						     new(ctx) ir_constant(i));

      ir_instruction *assignment = new(ctx) ir_assignment(lhs, rhs, NULL);
      instructions->push_tail(assignment);

      i++;
   }

   return new(ctx) ir_dereference_variable(var);
}


/**
 * Try to convert a record constructor to a constant expression
 */
static ir_constant *
constant_record_constructor(const glsl_type *constructor_type,
			    exec_list *parameters, void *mem_ctx)
{
   foreach_in_list(ir_instruction, node, parameters) {
      ir_constant *constant = node->as_constant();
      if (constant == NULL)
	 return NULL;
      node->replace_with(constant);
   }

   return new(mem_ctx) ir_constant(constructor_type, parameters);
}


/**
 * Determine if a list consists of a single scalar r-value
 */
bool
single_scalar_parameter(exec_list *parameters)
{
   const ir_rvalue *const p = (ir_rvalue *) parameters->head;
   assert(((ir_rvalue *)p)->as_rvalue() != NULL);

   return (p->type->is_scalar() && p->next->is_tail_sentinel());
}


/**
 * Generate inline code for a vector constructor
 *
 * The generated constructor code will consist of a temporary variable
 * declaration of the same type as the constructor.  A sequence of assignments
 * from constructor parameters to the temporary will follow.
 *
 * \return
 * An \c ir_dereference_variable of the temprorary generated in the constructor
 * body.
 */
ir_rvalue *
emit_inline_vector_constructor(const glsl_type *type, unsigned ast_precision,
			       exec_list *instructions,
			       exec_list *parameters,
			       void *ctx)
{
   assert(!parameters->is_empty());

   ir_variable *var = new(ctx) ir_variable(type, "vec_ctor", ir_var_temporary, (glsl_precision)ast_precision);
   instructions->push_tail(var);

   /* There are two kinds of vector constructors.
    *
    *  - Construct a vector from a single scalar by replicating that scalar to
    *    all components of the vector.
    *
    *  - Construct a vector from an arbirary combination of vectors and
    *    scalars.  The components of the constructor parameters are assigned
    *    to the vector in order until the vector is full.
    */
   const unsigned lhs_components = type->components();
   if (single_scalar_parameter(parameters)) {
      ir_rvalue *first_param = (ir_rvalue *)parameters->head;
      ir_rvalue *rhs = new(ctx) ir_swizzle(first_param, 0, 0, 0, 0,
					   lhs_components);
      var->data.precision = higher_precision ((glsl_precision)var->data.precision, rhs->get_precision());
      ir_dereference_variable *lhs = new(ctx) ir_dereference_variable(var);
      const unsigned mask = (1U << lhs_components) - 1;

      assert(rhs->type == lhs->type);

      ir_instruction *inst = new(ctx) ir_assignment(lhs, rhs, NULL, mask);
      instructions->push_tail(inst);
   } else {
      unsigned base_component = 0;
      unsigned base_lhs_component = 0;
      ir_constant_data data;
      unsigned constant_mask = 0, constant_components = 0;

      memset(&data, 0, sizeof(data));

      foreach_in_list(ir_rvalue, param, parameters) {
	 var->data.precision = higher_precision ((glsl_precision)var->data.precision, param->get_precision());
	 unsigned rhs_components = param->type->components();

	 /* Do not try to assign more components to the vector than it has!
	  */
	 if ((rhs_components + base_lhs_component) > lhs_components) {
	    rhs_components = lhs_components - base_lhs_component;
	 }

	 const ir_constant *const c = param->as_constant();
	 if (c != NULL) {
	    for (unsigned i = 0; i < rhs_components; i++) {
	       switch (c->type->base_type) {
	       case GLSL_TYPE_UINT:
		  data.u[i + base_component] = c->get_uint_component(i);
		  break;
	       case GLSL_TYPE_INT:
		  data.i[i + base_component] = c->get_int_component(i);
		  break;
	       case GLSL_TYPE_FLOAT:
		  data.f[i + base_component] = c->get_float_component(i);
		  break;
	       case GLSL_TYPE_BOOL:
		  data.b[i + base_component] = c->get_bool_component(i);
		  break;
	       default:
		  assert(!"Should not get here.");
		  break;
	       }
	    }

	    /* Mask of fields to be written in the assignment.
	     */
	    constant_mask |= ((1U << rhs_components) - 1) << base_lhs_component;
	    constant_components += rhs_components;

	    base_component += rhs_components;
	 }
	 /* Advance the component index by the number of components
	  * that were just assigned.
	  */
	 base_lhs_component += rhs_components;
      }

      if (constant_mask != 0) {
	 ir_dereference *lhs = new(ctx) ir_dereference_variable(var);
	 const glsl_type *rhs_type = glsl_type::get_instance(var->type->base_type,
							     constant_components,
							     1);
	 ir_rvalue *rhs = new(ctx) ir_constant(rhs_type, &data);

	 ir_instruction *inst =
	    new(ctx) ir_assignment(lhs, rhs, NULL, constant_mask);
	 instructions->push_tail(inst);
      }

      base_component = 0;
      foreach_in_list(ir_rvalue, param, parameters) {
	 unsigned rhs_components = param->type->components();

	 /* Do not try to assign more components to the vector than it has!
	  */
	 if ((rhs_components + base_component) > lhs_components) {
	    rhs_components = lhs_components - base_component;
	 }

	 const ir_constant *const c = param->as_constant();
	 if (c == NULL) {
	    /* Mask of fields to be written in the assignment.
	     */
	    const unsigned write_mask = ((1U << rhs_components) - 1)
	       << base_component;

	    ir_dereference *lhs = new(ctx) ir_dereference_variable(var);

	    /* Generate a swizzle so that LHS and RHS sizes match.
	     */
	    ir_rvalue *rhs =
	       new(ctx) ir_swizzle(param, 0, 1, 2, 3, rhs_components);

	    ir_instruction *inst =
	       new(ctx) ir_assignment(lhs, rhs, NULL, write_mask);
	    instructions->push_tail(inst);
	 }

	 /* Advance the component index by the number of components that were
	  * just assigned.
	  */
	 base_component += rhs_components;
      }
   }
   return new(ctx) ir_dereference_variable(var);
}


/**
 * Generate assignment of a portion of a vector to a portion of a matrix column
 *
 * \param src_base  First component of the source to be used in assignment
 * \param column    Column of destination to be assiged
 * \param row_base  First component of the destination column to be assigned
 * \param count     Number of components to be assigned
 *
 * \note
 * \c src_base + \c count must be less than or equal to the number of components
 * in the source vector.
 */
ir_instruction *
assign_to_matrix_column(ir_variable *var, unsigned column, unsigned row_base,
			ir_rvalue *src, unsigned src_base, unsigned count,
			void *mem_ctx)
{
   ir_constant *col_idx = new(mem_ctx) ir_constant(column);
   ir_dereference *column_ref = new(mem_ctx) ir_dereference_array(var, col_idx);

   assert(column_ref->type->components() >= (row_base + count));
   assert(src->type->components() >= (src_base + count));

   /* Generate a swizzle that extracts the number of components from the source
    * that are to be assigned to the column of the matrix.
    */
   if (count < src->type->vector_elements) {
      src = new(mem_ctx) ir_swizzle(src,
				    src_base + 0, src_base + 1,
				    src_base + 2, src_base + 3,
				    count);
   }

   /* Mask of fields to be written in the assignment.
    */
   const unsigned write_mask = ((1U << count) - 1) << row_base;

   return new(mem_ctx) ir_assignment(column_ref, src, NULL, write_mask);
}


/**
 * Generate inline code for a matrix constructor
 *
 * The generated constructor code will consist of a temporary variable
 * declaration of the same type as the constructor.  A sequence of assignments
 * from constructor parameters to the temporary will follow.
 *
 * \return
 * An \c ir_dereference_variable of the temprorary generated in the constructor
 * body.
 */
ir_rvalue *
emit_inline_matrix_constructor(const glsl_type *type, int ast_precision,
			       exec_list *instructions,
			       exec_list *parameters,
			       void *ctx)
{
   assert(!parameters->is_empty());

   ir_variable *var = new(ctx) ir_variable(type, "mat_ctor", ir_var_temporary, (glsl_precision)ast_precision);
   instructions->push_tail(var);

   /* There are three kinds of matrix constructors.
    *
    *  - Construct a matrix from a single scalar by replicating that scalar to
    *    along the diagonal of the matrix and setting all other components to
    *    zero.
    *
    *  - Construct a matrix from an arbirary combination of vectors and
    *    scalars.  The components of the constructor parameters are assigned
    *    to the matrix in column-major order until the matrix is full.
    *
    *  - Construct a matrix from a single matrix.  The source matrix is copied
    *    to the upper left portion of the constructed matrix, and the remaining
    *    elements take values from the identity matrix.
    */
   ir_rvalue *const first_param = (ir_rvalue *) parameters->head;
   if (single_scalar_parameter(parameters)) {
      /* Assign the scalar to the X component of a vec4, and fill the remaining
       * components with zero.
       */
      ir_variable *rhs_var =
	 new(ctx) ir_variable(glsl_type::vec4_type, "mat_ctor_vec",
			      ir_var_temporary, (glsl_precision)ast_precision);
      instructions->push_tail(rhs_var);

      ir_constant_data zero;
      zero.f[0] = 0.0;
      zero.f[1] = 0.0;
      zero.f[2] = 0.0;
      zero.f[3] = 0.0;

      ir_instruction *inst =
	 new(ctx) ir_assignment(new(ctx) ir_dereference_variable(rhs_var),
				new(ctx) ir_constant(rhs_var->type, &zero),
				NULL);
      instructions->push_tail(inst);

      ir_dereference *const rhs_ref = new(ctx) ir_dereference_variable(rhs_var);

      inst = new(ctx) ir_assignment(rhs_ref, first_param, NULL, 0x01);
      instructions->push_tail(inst);

      /* Assign the temporary vector to each column of the destination matrix
       * with a swizzle that puts the X component on the diagonal of the
       * matrix.  In some cases this may mean that the X component does not
       * get assigned into the column at all (i.e., when the matrix has more
       * columns than rows).
       */
      static const unsigned rhs_swiz[4][4] = {
	 { 0, 1, 1, 1 },
	 { 1, 0, 1, 1 },
	 { 1, 1, 0, 1 },
	 { 1, 1, 1, 0 }
      };

      const unsigned cols_to_init = MIN2(type->matrix_columns,
					 type->vector_elements);
      for (unsigned i = 0; i < cols_to_init; i++) {
	 ir_constant *const col_idx = new(ctx) ir_constant(i);
	 ir_rvalue *const col_ref = new(ctx) ir_dereference_array(var, col_idx);

	 ir_rvalue *const rhs_ref = new(ctx) ir_dereference_variable(rhs_var);
	 ir_rvalue *const rhs = new(ctx) ir_swizzle(rhs_ref, rhs_swiz[i],
						    type->vector_elements);

	 inst = new(ctx) ir_assignment(col_ref, rhs, NULL);
	 instructions->push_tail(inst);
      }

      for (unsigned i = cols_to_init; i < type->matrix_columns; i++) {
	 ir_constant *const col_idx = new(ctx) ir_constant(i);
	 ir_rvalue *const col_ref = new(ctx) ir_dereference_array(var, col_idx);

	 ir_rvalue *const rhs_ref = new(ctx) ir_dereference_variable(rhs_var);
	 ir_rvalue *const rhs = new(ctx) ir_swizzle(rhs_ref, 1, 1, 1, 1,
						    type->vector_elements);

	 inst = new(ctx) ir_assignment(col_ref, rhs, NULL);
	 instructions->push_tail(inst);
      }
   } else if (first_param->type->is_matrix()) {
      /* From page 50 (56 of the PDF) of the GLSL 1.50 spec:
       *
       *     "If a matrix is constructed from a matrix, then each component
       *     (column i, row j) in the result that has a corresponding
       *     component (column i, row j) in the argument will be initialized
       *     from there. All other components will be initialized to the
       *     identity matrix. If a matrix argument is given to a matrix
       *     constructor, it is an error to have any other arguments."
       */
      assert(first_param->next->is_tail_sentinel());
      ir_rvalue *const src_matrix = first_param;

      /* If the source matrix is smaller, pre-initialize the relavent parts of
       * the destination matrix to the identity matrix.
       */
      if ((src_matrix->type->matrix_columns < var->type->matrix_columns)
	  || (src_matrix->type->vector_elements < var->type->vector_elements)) {

	 /* If the source matrix has fewer rows, every column of the destination
	  * must be initialized.  Otherwise only the columns in the destination
	  * that do not exist in the source must be initialized.
	  */
	 unsigned col =
	    (src_matrix->type->vector_elements < var->type->vector_elements)
	    ? 0 : src_matrix->type->matrix_columns;

	 const glsl_type *const col_type = var->type->column_type();
	 for (/* empty */; col < var->type->matrix_columns; col++) {
	    ir_constant_data ident;

	    ident.f[0] = 0.0;
	    ident.f[1] = 0.0;
	    ident.f[2] = 0.0;
	    ident.f[3] = 0.0;

	    ident.f[col] = 1.0;

	    ir_rvalue *const rhs = new(ctx) ir_constant(col_type, &ident);

	    ir_rvalue *const lhs =
	       new(ctx) ir_dereference_array(var, new(ctx) ir_constant(col));

	    ir_instruction *inst = new(ctx) ir_assignment(lhs, rhs, NULL);
	    instructions->push_tail(inst);
	 }
      }

      /* Assign columns from the source matrix to the destination matrix.
       *
       * Since the parameter will be used in the RHS of multiple assignments,
       * generate a temporary and copy the paramter there.
       */
      ir_variable *const rhs_var =
	 new(ctx) ir_variable(first_param->type, "mat_ctor_mat",
			      ir_var_temporary, (glsl_precision)ast_precision);
      instructions->push_tail(rhs_var);

      ir_dereference *const rhs_var_ref =
	 new(ctx) ir_dereference_variable(rhs_var);
      ir_instruction *const inst =
	 new(ctx) ir_assignment(rhs_var_ref, first_param, NULL);
      instructions->push_tail(inst);

      const unsigned last_row = MIN2(src_matrix->type->vector_elements,
				     var->type->vector_elements);
      const unsigned last_col = MIN2(src_matrix->type->matrix_columns,
				     var->type->matrix_columns);

      unsigned swiz[4] = { 0, 0, 0, 0 };
      for (unsigned i = 1; i < last_row; i++)
	 swiz[i] = i;

      const unsigned write_mask = (1U << last_row) - 1;

      for (unsigned i = 0; i < last_col; i++) {
	 ir_dereference *const lhs =
	    new(ctx) ir_dereference_array(var, new(ctx) ir_constant(i));
	 ir_rvalue *const rhs_col =
	    new(ctx) ir_dereference_array(rhs_var, new(ctx) ir_constant(i));

	 /* If one matrix has columns that are smaller than the columns of the
	  * other matrix, wrap the column access of the larger with a swizzle
	  * so that the LHS and RHS of the assignment have the same size (and
	  * therefore have the same type).
	  *
	  * It would be perfectly valid to unconditionally generate the
	  * swizzles, this this will typically result in a more compact IR tree.
	  */
	 ir_rvalue *rhs;
	 if (lhs->type->vector_elements != rhs_col->type->vector_elements) {
	    rhs = new(ctx) ir_swizzle(rhs_col, swiz, last_row);
	 } else {
	    rhs = rhs_col;
	 }

	 ir_instruction *inst =
	    new(ctx) ir_assignment(lhs, rhs, NULL, write_mask);
	 instructions->push_tail(inst);
      }
   } else {
      const unsigned cols = type->matrix_columns;
      const unsigned rows = type->vector_elements;
      unsigned col_idx = 0;
      unsigned row_idx = 0;

      foreach_in_list(ir_rvalue, rhs, parameters) {
	 const unsigned components_remaining_this_column = rows - row_idx;
	 unsigned rhs_components = rhs->type->components();
	 unsigned rhs_base = 0;

	 /* Since the parameter might be used in the RHS of two assignments,
	  * generate a temporary and copy the paramter there.
	  */
	 ir_variable *rhs_var =
	    new(ctx) ir_variable(rhs->type, "mat_ctor_vec", ir_var_temporary, (glsl_precision)ast_precision);
	 instructions->push_tail(rhs_var);

	 ir_dereference *rhs_var_ref =
	    new(ctx) ir_dereference_variable(rhs_var);
	 ir_instruction *inst = new(ctx) ir_assignment(rhs_var_ref, rhs, NULL);
	 instructions->push_tail(inst);

	 /* Assign the current parameter to as many components of the matrix
	  * as it will fill.
	  *
	  * NOTE: A single vector parameter can span two matrix columns.  A
	  * single vec4, for example, can completely fill a mat2.
	  */
	 if (rhs_components >= components_remaining_this_column) {
	    const unsigned count = MIN2(rhs_components,
					components_remaining_this_column);

	    rhs_var_ref = new(ctx) ir_dereference_variable(rhs_var);

	    ir_instruction *inst = assign_to_matrix_column(var, col_idx,
							   row_idx,
							   rhs_var_ref, 0,
							   count, ctx);
	    instructions->push_tail(inst);

	    rhs_base = count;

	    col_idx++;
	    row_idx = 0;
	 }

	 /* If there is data left in the parameter and components left to be
	  * set in the destination, emit another assignment.  It is possible
	  * that the assignment could be of a vec4 to the last element of the
	  * matrix.  In this case col_idx==cols, but there is still data
	  * left in the source parameter.  Obviously, don't emit an assignment
	  * to data outside the destination matrix.
	  */
	 if ((col_idx < cols) && (rhs_base < rhs_components)) {
	    const unsigned count = rhs_components - rhs_base;

	    rhs_var_ref = new(ctx) ir_dereference_variable(rhs_var);

	    ir_instruction *inst = assign_to_matrix_column(var, col_idx,
							   row_idx,
							   rhs_var_ref,
							   rhs_base,
							   count, ctx);
	    instructions->push_tail(inst);

	    row_idx += count;
	 }
      }
   }

   return new(ctx) ir_dereference_variable(var);
}


ir_rvalue *
emit_inline_record_constructor(const glsl_type *type,
			       exec_list *instructions,
			       exec_list *parameters,
			       void *mem_ctx)
{
   ir_variable *const var =
      new(mem_ctx) ir_variable(type, "record_ctor", ir_var_temporary, glsl_precision_undefined);
   ir_dereference_variable *const d = new(mem_ctx) ir_dereference_variable(var);

   instructions->push_tail(var);

   exec_node *node = parameters->head;
   for (unsigned i = 0; i < type->length; i++) {
      assert(!node->is_tail_sentinel());

      ir_dereference *const lhs =
	 new(mem_ctx) ir_dereference_record(d->clone(mem_ctx, NULL),
					    type->fields.structure[i].name);

      ir_rvalue *const rhs = ((ir_instruction *) node)->as_rvalue();
      assert(rhs != NULL);

      ir_instruction *const assign = new(mem_ctx) ir_assignment(lhs, rhs, NULL);

      instructions->push_tail(assign);
      node = node->next;
   }

   return d;
}


static ir_rvalue *
process_record_constructor(exec_list *instructions,
                           const glsl_type *constructor_type,
                           YYLTYPE *loc, exec_list *parameters,
                           struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   exec_list actual_parameters;

   process_parameters(instructions, &actual_parameters,
                      parameters, state);

   exec_node *node = actual_parameters.head;
   for (unsigned i = 0; i < constructor_type->length; i++) {
      ir_rvalue *ir = (ir_rvalue *) node;

      if (node->is_tail_sentinel()) {
         _mesa_glsl_error(loc, state,
                          "insufficient parameters to constructor for `%s'",
                          constructor_type->name);
         return ir_rvalue::error_value(ctx);
      }

      if (apply_implicit_conversion(constructor_type->fields.structure[i].type,
                                 ir, state)) {
         node->replace_with(ir);
      } else {
         _mesa_glsl_error(loc, state,
                          "parameter type mismatch in constructor for `%s.%s' "
                          "(%s vs %s)",
                          constructor_type->name,
                          constructor_type->fields.structure[i].name,
                          ir->type->name,
                          constructor_type->fields.structure[i].type->name);
         return ir_rvalue::error_value(ctx);;
      }

      node = node->next;
   }

   if (!node->is_tail_sentinel()) {
      _mesa_glsl_error(loc, state, "too many parameters in constructor "
                                    "for `%s'", constructor_type->name);
      return ir_rvalue::error_value(ctx);
   }

   ir_rvalue *const constant =
      constant_record_constructor(constructor_type, &actual_parameters,
                                  state);

   return (constant != NULL)
            ? constant
            : emit_inline_record_constructor(constructor_type, instructions,
                                             &actual_parameters, state);
}


ir_rvalue *
ast_function_expression::hir(exec_list *instructions,
			     struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   /* There are three sorts of function calls.
    *
    * 1. constructors - The first subexpression is an ast_type_specifier.
    * 2. methods - Only the .length() method of array types.
    * 3. functions - Calls to regular old functions.
    *
    * Method calls are actually detected when the ast_field_selection
    * expression is handled.
    */
   if (is_constructor()) {
      const ast_type_specifier *type = (ast_type_specifier *) subexpressions[0];
      YYLTYPE loc = type->get_location();
      const char *name;

      const glsl_type *const constructor_type = type->glsl_type(& name, state);

      /* constructor_type can be NULL if a variable with the same name as the
       * structure has come into scope.
       */
      if (constructor_type == NULL) {
	 _mesa_glsl_error(& loc, state, "unknown type `%s' (structure name "
			  "may be shadowed by a variable with the same name)",
			  type->type_name);
	 return ir_rvalue::error_value(ctx);
      }


      /* Constructors for samplers are illegal.
       */
      if (constructor_type->is_sampler()) {
	 _mesa_glsl_error(& loc, state, "cannot construct sampler type `%s'",
			  constructor_type->name);
	 return ir_rvalue::error_value(ctx);
      }

      if (constructor_type->is_array()) {
         if (!state->check_version(120, 300, &loc,
                                   "array constructors forbidden")) {
	    return ir_rvalue::error_value(ctx);
	 }

	 return process_array_constructor(instructions, constructor_type,
					  & loc, &this->expressions, state);
      }


      /* There are two kinds of constructor calls.  Constructors for arrays and
       * structures must have the exact number of arguments with matching types
       * in the correct order.  These constructors follow essentially the same
       * type matching rules as functions.
       *
       * Constructors for built-in language types, such as mat4 and vec2, are
       * free form.  The only requirements are that the parameters must provide
       * enough values of the correct scalar type and that no arguments are
       * given past the last used argument.
       *
       * When using the C-style initializer syntax from GLSL 4.20, constructors
       * must have the exact number of arguments with matching types in the
       * correct order.
       */
      if (constructor_type->is_record()) {
         return process_record_constructor(instructions, constructor_type,
                                           &loc, &this->expressions,
                                           state);
      }

      if (!constructor_type->is_numeric() && !constructor_type->is_boolean())
	 return ir_rvalue::error_value(ctx);

      /* Total number of components of the type being constructed. */
      const unsigned type_components = constructor_type->components();

      /* Number of components from parameters that have actually been
       * consumed.  This is used to perform several kinds of error checking.
       */
      unsigned components_used = 0;

      unsigned matrix_parameters = 0;
      unsigned nonmatrix_parameters = 0;
      exec_list actual_parameters;
	   glsl_precision params_precision = glsl_precision_undefined;

      foreach_list_typed(ast_node, ast, link, &this->expressions) {
	 ir_rvalue *result = ast->hir(instructions, state);

	 /* From page 50 (page 56 of the PDF) of the GLSL 1.50 spec:
	  *
	  *    "It is an error to provide extra arguments beyond this
	  *    last used argument."
	  */
	 if (components_used >= type_components) {
	    _mesa_glsl_error(& loc, state, "too many parameters to `%s' "
			     "constructor",
			     constructor_type->name);
	    return ir_rvalue::error_value(ctx);
	 }

	 if (!result->type->is_numeric() && !result->type->is_boolean()) {
	    _mesa_glsl_error(& loc, state, "cannot construct `%s' from a "
			     "non-numeric data type",
			     constructor_type->name);
	    return ir_rvalue::error_value(ctx);
	 }

	 /* Count the number of matrix and nonmatrix parameters.  This
	  * is used below to enforce some of the constructor rules.
	  */
	 if (result->type->is_matrix())
	    matrix_parameters++;
	 else
	    nonmatrix_parameters++;

	 actual_parameters.push_tail(result);
		  params_precision = higher_precision(params_precision, result->get_precision());
	 components_used += result->type->components();
      }

      /* From page 28 (page 34 of the PDF) of the GLSL 1.10 spec:
       *
       *    "It is an error to construct matrices from other matrices. This
       *    is reserved for future use."
       */
      if (matrix_parameters > 0
          && constructor_type->is_matrix()
          && !state->check_version(120, 100, &loc,
                                   "cannot construct `%s' from a matrix",
                                   constructor_type->name)) {
	 return ir_rvalue::error_value(ctx);
      }

      /* From page 50 (page 56 of the PDF) of the GLSL 1.50 spec:
       *
       *    "If a matrix argument is given to a matrix constructor, it is
       *    an error to have any other arguments."
       */
      if ((matrix_parameters > 0)
	  && ((matrix_parameters + nonmatrix_parameters) > 1)
	  && constructor_type->is_matrix()) {
	 _mesa_glsl_error(& loc, state, "for matrix `%s' constructor, "
			  "matrix must be only parameter",
			  constructor_type->name);
	 return ir_rvalue::error_value(ctx);
      }

      /* From page 28 (page 34 of the PDF) of the GLSL 1.10 spec:
       *
       *    "In these cases, there must be enough components provided in the
       *    arguments to provide an initializer for every component in the
       *    constructed value."
       */
      if (components_used < type_components && components_used != 1
	  && matrix_parameters == 0) {
	 _mesa_glsl_error(& loc, state, "too few components to construct "
			  "`%s'",
			  constructor_type->name);
	 return ir_rvalue::error_value(ctx);
      }

      /* Later, we cast each parameter to the same base type as the
       * constructor.  Since there are no non-floating point matrices, we
       * need to break them up into a series of column vectors.
       */
      if (constructor_type->base_type != GLSL_TYPE_FLOAT) {
	 foreach_in_list_safe(ir_rvalue, matrix, &actual_parameters) {
	    if (!matrix->type->is_matrix())
	       continue;

	    /* Create a temporary containing the matrix. */
	    ir_variable *var = new(ctx) ir_variable(matrix->type, "matrix_tmp",
						    ir_var_temporary, matrix->get_precision());
	    instructions->push_tail(var);
	    instructions->push_tail(new(ctx) ir_assignment(new(ctx)
	       ir_dereference_variable(var), matrix, NULL));
	    var->constant_value = matrix->constant_expression_value();

	    /* Replace the matrix with dereferences of its columns. */
	    for (int i = 0; i < (int)matrix->type->matrix_columns; i++) {
	       matrix->insert_before(new (ctx) ir_dereference_array(var,
		  new(ctx) ir_constant(i)));
	    }
	    matrix->remove();
	 }
      }

      bool all_parameters_are_constant = true;

      /* Type cast each parameter and, if possible, fold constants.*/
      foreach_in_list_safe(ir_rvalue, ir, &actual_parameters) {
	 const glsl_type *desired_type =
	    glsl_type::get_instance(constructor_type->base_type,
				    ir->type->vector_elements,
				    ir->type->matrix_columns);
	 ir_rvalue *result = convert_component(ir, desired_type);

	 /* Attempt to convert the parameter to a constant valued expression.
	  * After doing so, track whether or not all the parameters to the
	  * constructor are trivially constant valued expressions.
	  */
	 ir_rvalue *const constant = result->constant_expression_value();

	 if (constant != NULL)
	    result = constant;
	 else
	    all_parameters_are_constant = false;

	 if (result != ir) {
	    ir->replace_with(result);
	 }
      }

      /* If all of the parameters are trivially constant, create a
       * constant representing the complete collection of parameters.
       */
      if (all_parameters_are_constant) {
	 return new(ctx) ir_constant(constructor_type, &actual_parameters);
      } else if (constructor_type->is_scalar()) {
	 return dereference_component((ir_rvalue *) actual_parameters.head,
				      0);
      } else if (constructor_type->is_vector()) {
	 return emit_inline_vector_constructor(constructor_type, params_precision,
					       instructions,
					       &actual_parameters,
					       ctx);
      } else {
	 assert(constructor_type->is_matrix());
	 return emit_inline_matrix_constructor(constructor_type, params_precision,
					       instructions,
					       &actual_parameters,
					       ctx);
      }
   } else {
      const ast_expression *id = subexpressions[0];
      const char *func_name = id->primary_expression.identifier;
      YYLTYPE loc = get_location();
      exec_list actual_parameters;

      process_parameters(instructions, &actual_parameters, &this->expressions,
			 state);

      ir_function_signature *sig =
	 match_function_by_name(func_name, &actual_parameters, state);

      ir_rvalue *value = NULL;
      if (sig == NULL) {
	 no_matching_function_error(func_name, &loc, &actual_parameters, state);
	 value = ir_rvalue::error_value(ctx);
      } else if (!verify_parameter_modes(state, sig, actual_parameters, this->expressions)) {
	 /* an error has already been emitted */
	 value = ir_rvalue::error_value(ctx);
      } else {
	 value = generate_call(instructions, sig, &actual_parameters, state);
      }

      return value;
   }

   return ir_rvalue::error_value(ctx);
}

ir_rvalue *
ast_aggregate_initializer::hir(exec_list *instructions,
                               struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;
   YYLTYPE loc = this->get_location();

   if (!this->constructor_type) {
      _mesa_glsl_error(&loc, state, "type of C-style initializer unknown");
      return ir_rvalue::error_value(ctx);
   }
   const glsl_type *const constructor_type = this->constructor_type;

   if (!state->ARB_shading_language_420pack_enable) {
      _mesa_glsl_error(&loc, state, "C-style initialization requires the "
                       "GL_ARB_shading_language_420pack extension");
      return ir_rvalue::error_value(ctx);
   }

   if (constructor_type->is_array()) {
      return process_array_constructor(instructions, constructor_type, &loc,
                                       &this->expressions, state);
   }

   if (constructor_type->is_record()) {
      return process_record_constructor(instructions, constructor_type, &loc,
                                        &this->expressions, state);
   }

   return process_vec_mat_constructor(instructions, constructor_type, &loc,
                                      &this->expressions, state);
}

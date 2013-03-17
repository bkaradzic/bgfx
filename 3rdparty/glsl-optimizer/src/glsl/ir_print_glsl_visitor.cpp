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

#include "ir_print_glsl_visitor.h"
#include "ir_visitor.h"
#include "glsl_types.h"
#include "glsl_parser_extras.h"
#include "ir_unused_structs.h"
#include "program/hash_table.h"
#include <math.h>

static char* print_type(char* buffer, const glsl_type *t, bool arraySize);
static char* print_type_post(char* buffer, const glsl_type *t, bool arraySize);

static inline const char* get_precision_string (glsl_precision p)
{
	switch (p) {
	case glsl_precision_high:		return "highp ";
	case glsl_precision_medium:		return "mediump ";
	case glsl_precision_low:		return "lowp ";
	case glsl_precision_undefined:	return "";
	}
	assert(!"Should not get here.");
	return "";
}

struct ga_entry : public exec_node
{
	ga_entry(ir_instruction* ir)
	{
		assert(ir);
		this->ir = ir;
	}	
	ir_instruction* ir;
};


struct global_print_tracker {
	global_print_tracker () {
		mem_ctx = ralloc_context(0);
		var_counter = 0;
		var_hash = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);
		main_function_done = false;
	}
	
	~global_print_tracker() {
		hash_table_dtor (var_hash);
		ralloc_free(mem_ctx);
	}
	
	unsigned	var_counter;
	hash_table*	var_hash;
	exec_list	global_assignements;
	void* mem_ctx;
	bool	main_function_done;
};

class ir_print_glsl_visitor : public ir_visitor {
public:
	ir_print_glsl_visitor(char* buf, global_print_tracker* globals_, PrintGlslMode mode_, bool use_precision_, const _mesa_glsl_parse_state* state_)
	{
		indentation = 0;
		buffer = buf;
		globals = globals_;
		mode = mode_;
		use_precision = use_precision_;
		state = state_;
	}

	virtual ~ir_print_glsl_visitor()
	{
	}


	void indent(void);
	void print_var_name (ir_variable* v);
	void print_precision (ir_instruction* ir, const glsl_type* type);

	virtual void visit(ir_variable *);
	virtual void visit(ir_function_signature *);
	virtual void visit(ir_function *);
	virtual void visit(ir_expression *);
	virtual void visit(ir_texture *);
	virtual void visit(ir_swizzle *);
	virtual void visit(ir_dereference_variable *);
	virtual void visit(ir_dereference_array *);
	virtual void visit(ir_dereference_record *);
	virtual void visit(ir_assignment *);
	virtual void visit(ir_constant *);
	virtual void visit(ir_call *);
	virtual void visit(ir_return *);
	virtual void visit(ir_discard *);
	virtual void visit(ir_if *);
	virtual void visit(ir_loop *);
	virtual void visit(ir_loop_jump *);
	virtual void visit(ir_precision_statement *);
	
	int indentation;
	char* buffer;
	global_print_tracker* globals;
	const _mesa_glsl_parse_state* state;
	PrintGlslMode mode;
	bool	use_precision;
};


char*
_mesa_print_ir_glsl(exec_list *instructions,
	    struct _mesa_glsl_parse_state *state,
		char* buffer, PrintGlslMode mode)
{
	if (state) {
		if (state->version_string)
			ralloc_asprintf_append (&buffer, "#version %i\n", state->language_version);
		if (state->ARB_shader_texture_lod_enable)
			ralloc_strcat (&buffer, "#extension GL_ARB_shader_texture_lod : enable\n");
		if (state->EXT_shader_texture_lod_enable)
			ralloc_strcat (&buffer, "#extension GL_EXT_shader_texture_lod : enable\n");
		if (state->OES_standard_derivatives_enable)
			ralloc_strcat (&buffer, "#extension GL_OES_standard_derivatives : enable\n");
		if (state->EXT_shadow_samplers_enable)
			ralloc_strcat (&buffer, "#extension GL_EXT_shadow_samplers : enable\n");
		if (state->EXT_frag_depth_enable)
			ralloc_strcat (&buffer, "#extension GL_EXT_frag_depth : enable\n");
	}
   if (state) {
	   ir_struct_usage_visitor v;
	   v.run (instructions);

      for (unsigned i = 0; i < state->num_user_structures; i++) {
	 const glsl_type *const s = state->user_structures[i];

	 if (!v.has_struct_entry(s))
		 continue;

	 ralloc_asprintf_append (&buffer, "struct %s {\n",
		s->name);

	 for (unsigned j = 0; j < s->length; j++) {
	    ralloc_asprintf_append (&buffer, "  ");
		if (state->es_shader)
			ralloc_asprintf_append (&buffer, "%s", get_precision_string(s->fields.structure[j].precision));
	    buffer = print_type(buffer, s->fields.structure[j].type, false);
	    ralloc_asprintf_append (&buffer, " %s", s->fields.structure[j].name);
        buffer = print_type_post(buffer, s->fields.structure[j].type, false);
        ralloc_asprintf_append (&buffer, ";\n");
	 }

	 ralloc_asprintf_append (&buffer, "};\n");
      }
   }
	
	global_print_tracker gtracker;

   foreach_iter(exec_list_iterator, iter, *instructions) {
      ir_instruction *ir = (ir_instruction *)iter.get();
	  if (ir->ir_type == ir_type_variable) {
		ir_variable *var = static_cast<ir_variable*>(ir);
		if ((strstr(var->name, "gl_") == var->name)
			  && !var->invariant)
			continue;
	  }

	  ir_print_glsl_visitor v (buffer, &gtracker, mode, state->es_shader, state);
	  ir->accept(&v);
	  buffer = v.buffer;
      if (ir->ir_type != ir_type_function)
		ralloc_asprintf_append (&buffer, ";\n");
   }

   return buffer;
}


void ir_print_glsl_visitor::indent(void)
{
   for (int i = 0; i < indentation; i++)
      ralloc_asprintf_append (&buffer, "  ");
}

void ir_print_glsl_visitor::print_var_name (ir_variable* v)
{
    long id = (long)hash_table_find (globals->var_hash, v);
	if (!id && v->mode == ir_var_temporary)
	{
        id = ++globals->var_counter;
        hash_table_insert (globals->var_hash, (void*)id, v);
	}
    if (id)
    {
        if (v->mode == ir_var_temporary)
            ralloc_asprintf_append (&buffer, "tmpvar_%d", id);
        else
            ralloc_asprintf_append (&buffer, "%s_%d", v->name, id);
    }
	else
	{
		ralloc_asprintf_append (&buffer, "%s", v->name);
	}
}

void ir_print_glsl_visitor::print_precision (ir_instruction* ir, const glsl_type* type)
{
	if (!this->use_precision)
		return;
	if (type &&
		!type->is_float() &&
		!type->is_sampler() &&
		(!type->is_array() || !type->element_type()->is_float())
	)
	{
		return;
	}
	glsl_precision prec = precision_from_ir(ir);
	
	// skip precision for samplers that end up being lowp (default anyway) or undefined
	if (type && type->is_sampler())
	{
		if (prec == glsl_precision_low || prec == glsl_precision_undefined)
			return;
	}
	
	if (prec == glsl_precision_high || prec == glsl_precision_undefined)
	{
		if (ir->ir_type == ir_type_function_signature)
			return;
	}
	ralloc_asprintf_append (&buffer, "%s", get_precision_string(prec));
}


static char*
print_type(char* buffer, const glsl_type *t, bool arraySize)
{
   if (t->base_type == GLSL_TYPE_ARRAY) {
      buffer = print_type(buffer, t->fields.array, true);
      if (arraySize)
         ralloc_asprintf_append (&buffer, "[%u]", t->length);
   } else if ((t->base_type == GLSL_TYPE_STRUCT)
	      && (strncmp("gl_", t->name, 3) != 0)) {
      ralloc_asprintf_append (&buffer, "%s", t->name);
   } else {
      ralloc_asprintf_append (&buffer, "%s", t->name);
   }
   return buffer;
}

static char*
print_type_post(char* buffer, const glsl_type *t, bool arraySize)
{
	if (t->base_type == GLSL_TYPE_ARRAY) {
		if (!arraySize)
			ralloc_asprintf_append (&buffer, "[%u]", t->length);
	}
	return buffer;
}


void ir_print_glsl_visitor::visit(ir_variable *ir)
{
   const char *const cent = (ir->centroid) ? "centroid " : "";
   const char *const inv = (ir->invariant) ? "invariant " : "";
   const char *const mode[3][8] = 
   {
	{ "", "uniform ", "in ",        "out ",     "inout ", "", "", "" },
	{ "", "uniform ", "attribute ", "varying ", "inout ", "", "", "" },
	{ "", "uniform ", "varying ",   "out ",     "inout ", "", "", "" },
   };
   const char *const interp[] = { "", "smooth ", "flat ", "noperspective " };
	
	int decormode = this->mode;
	// GLSL 1.30 and up use "in" and "out" for everything
	if (this->state->language_version >= 130)
	{
		decormode = 0;
	}

   // give an id to any variable defined in a function that is not an uniform
   if ((this->mode == kPrintGlslNone && ir->mode != ir_var_uniform))
   {
     long id = (long)hash_table_find (globals->var_hash, ir);
     if (id == 0)
     {
       id = ++globals->var_counter;
       hash_table_insert (globals->var_hash, (void*)id, ir);
     }
   }

   // keep invariant declaration for builtin variables
   if (strstr(ir->name, "gl_") == ir->name) {
      ralloc_asprintf_append (&buffer, "%s", inv);
      print_var_name (ir);
      return;
   }
	
   ralloc_asprintf_append (&buffer, "%s%s%s%s",
	  cent, inv, interp[ir->interpolation], mode[decormode][ir->mode]);
   print_precision (ir, ir->type);
   buffer = print_type(buffer, ir->type, false);
   ralloc_asprintf_append (&buffer, " ");
   print_var_name (ir);
   buffer = print_type_post(buffer, ir->type, false);
	
	if (ir->constant_value && ir->mode != ir_var_in && ir->mode != ir_var_out && ir->mode != ir_var_inout)
	{
		ralloc_asprintf_append (&buffer, " = ");
		visit (ir->constant_value);
	}
}


void ir_print_glsl_visitor::visit(ir_function_signature *ir)
{
   print_precision (ir, ir->return_type);
   buffer = print_type(buffer, ir->return_type, true);
   ralloc_asprintf_append (&buffer, " %s (", ir->function_name());

   if (!ir->parameters.is_empty())
   {
	   ralloc_asprintf_append (&buffer, "\n");

	   indentation++;
	   bool first = true;
	   foreach_iter(exec_list_iterator, iter, ir->parameters) {
		  ir_variable *const inst = (ir_variable *) iter.get();

		  if (!first)
			  ralloc_asprintf_append (&buffer, ",\n");
		  indent();
		  inst->accept(this);
		  first = false;
	   }
	   indentation--;

	   ralloc_asprintf_append (&buffer, "\n");
	   indent();
   }

   if (ir->body.is_empty())
   {
	   ralloc_asprintf_append (&buffer, ");\n");
	   return;
   }

   ralloc_asprintf_append (&buffer, ")\n");

   indent();
   ralloc_asprintf_append (&buffer, "{\n");
   indentation++;
	
	// insert postponed global assigments
	if (strcmp(ir->function()->name, "main") == 0)
	{
		assert (!globals->main_function_done);
		globals->main_function_done = true;
		foreach_iter(exec_list_iterator, it, globals->global_assignements)
		{
			ir_instruction* as = ((ga_entry *)it.get())->ir;
			as->accept(this);
			ralloc_asprintf_append(&buffer, ";\n");
		}
	}

   foreach_iter(exec_list_iterator, iter, ir->body) {
      ir_instruction *const inst = (ir_instruction *) iter.get();

      indent();
      inst->accept(this);
	  ralloc_asprintf_append (&buffer, ";\n");
   }
   indentation--;
   indent();
   ralloc_asprintf_append (&buffer, "}\n");
}


void ir_print_glsl_visitor::visit(ir_function *ir)
{
   bool found_non_builtin_proto = false;

   foreach_iter(exec_list_iterator, iter, *ir) {
      ir_function_signature *const sig = (ir_function_signature *) iter.get();
      if (!sig->is_builtin)
	 found_non_builtin_proto = true;
   }
   if (!found_non_builtin_proto)
      return;

   PrintGlslMode oldMode = this->mode;
   this->mode = kPrintGlslNone;

   foreach_iter(exec_list_iterator, iter, *ir) {
      ir_function_signature *const sig = (ir_function_signature *) iter.get();

      indent();
      sig->accept(this);
      ralloc_asprintf_append (&buffer, "\n");
   }

   this->mode = oldMode;

   indent();
}


static const char *const operator_glsl_strs[] = {
	"~",
	"!",
	"-",
	"abs",
	"sign",
	"1.0/",
	"inversesqrt",
	"sqrt",
	"normalize",
	"exp",
	"log",
	"exp2",
	"log2",
	"int",		// f2i
	"int",		// f2u
	"float",	// i2f
	"bool",		// f2b
	"float",	// b2f
	"bool",		// i2b
	"int",		// b2i
	"float",	// u2f
	"int",		// i2u
	"int",		// u2i
	"float",	// bit i2f
	"int",		// bit f2i
	"float",	// bit u2f
	"int",		// bit f2u
	"any",
	"trunc",
	"ceil",
	"floor",
	"fract",
	"roundEven",
	"sin",
	"cos",
	"sin", // reduced
	"cos", // reduced
	"dFdx",
	"dFdy",
	"noise",
	"+",
	"-",
	"*",
	"/",
	"mod",
	"<",
	">",
	"<=",
	">=",
	"equal",
	"notEqual",
	"==",
	"!=",
	"<<",
	">>",
	"&",
	"^",
	"|",
	"&&",
	"^^",
	"||",
	"dot",
	"min",
	"max",
	"pow",
	"uboloadTODO",
	"clamp",
	"mix",
	"vectorTODO",
};

static const char *const operator_vec_glsl_strs[] = {
	"lessThan",
	"greaterThan",
	"lessThanEqual",
	"greaterThanEqual",
	"equal",
	"notEqual",
};


static bool is_binop_func_like(ir_expression_operation op, const glsl_type* type)
{
	if (op == ir_binop_equal || 
		op == ir_binop_nequal ||
		op == ir_binop_mod ||
		(op >= ir_binop_dot && op <= ir_binop_pow))
		return true;
	if (type->is_vector() && (op >= ir_binop_less && op <= ir_binop_nequal))
	{
		return true;
	}
	return false;
}

void ir_print_glsl_visitor::visit(ir_expression *ir)
{
	if (ir->get_num_operands() == 1) {
		if (ir->operation >= ir_unop_f2i && ir->operation < ir_unop_any) {
			buffer = print_type(buffer, ir->type, true);
			ralloc_asprintf_append(&buffer, "(");
		} else if (ir->operation == ir_unop_rcp) {
			ralloc_asprintf_append (&buffer, "(1.0/(");
		} else {
			ralloc_asprintf_append (&buffer, "%s(", operator_glsl_strs[ir->operation]);
		}
		if (ir->operands[0])
			ir->operands[0]->accept(this);
		ralloc_asprintf_append (&buffer, ")");
		if (ir->operation == ir_unop_rcp) {
			ralloc_asprintf_append (&buffer, ")");
		}
	}
	else if (is_binop_func_like(ir->operation, ir->type))
	{
		if (ir->operation == ir_binop_mod)
		{
			ralloc_asprintf_append (&buffer, "(");
			buffer = print_type(buffer, ir->type, true);
			ralloc_asprintf_append (&buffer, "(");
		}
		if (ir->type->is_vector() && (ir->operation >= ir_binop_less && ir->operation <= ir_binop_nequal))
			ralloc_asprintf_append (&buffer, "%s (", operator_vec_glsl_strs[ir->operation-ir_binop_less]);
		else
			ralloc_asprintf_append (&buffer, "%s (", operator_glsl_strs[ir->operation]);
		
		if (ir->operands[0])
			ir->operands[0]->accept(this);
		ralloc_asprintf_append (&buffer, ", ");
		if (ir->operands[1])
			ir->operands[1]->accept(this);
		ralloc_asprintf_append (&buffer, ")");
		if (ir->operation == ir_binop_mod)
            ralloc_asprintf_append (&buffer, "))");
	}
	else if (ir->get_num_operands() == 2)
	{
		ralloc_asprintf_append (&buffer, "(");
		if (ir->operands[0])
			ir->operands[0]->accept(this);

		ralloc_asprintf_append (&buffer, " %s ", operator_glsl_strs[ir->operation]);

		if (ir->operands[1])
			ir->operands[1]->accept(this);
		ralloc_asprintf_append (&buffer, ")");
	}
	else
	{
		// ternary op
		ralloc_asprintf_append (&buffer, "%s (", operator_glsl_strs[ir->operation]);
		if (ir->operands[0])
			ir->operands[0]->accept(this);
		ralloc_asprintf_append (&buffer, ", ");
		if (ir->operands[1])
			ir->operands[1]->accept(this);
		ralloc_asprintf_append (&buffer, ", ");
		if (ir->operands[2])
			ir->operands[2]->accept(this);
		ralloc_asprintf_append (&buffer, ")");
	}
}

// [glsl_sampler_dim]
static const char* tex_sampler_dim_name[] = {
	"1D", "2D", "3D", "Cube", "Rect", "Buf",
};
static int tex_sampler_dim_size[] = {
	1, 2, 3, 3, 2, 2,
};


void ir_print_glsl_visitor::visit(ir_texture *ir)
{
	glsl_sampler_dim sampler_dim = (glsl_sampler_dim)ir->sampler->type->sampler_dimensionality;
	const bool is_shadow = ir->sampler->type->sampler_shadow;
	const glsl_type* uv_type = ir->coordinate->type;
	const int uv_dim = uv_type->vector_elements;
	int sampler_uv_dim = tex_sampler_dim_size[sampler_dim];
	if (is_shadow)
		sampler_uv_dim = 3;
	const bool is_proj = (uv_dim > sampler_uv_dim);
	
    // texture function name
    //ACS: shadow lookups and lookups with dimensionality included in the name were deprecated in 130
    if(state->language_version<130) 
    {
        ralloc_asprintf_append (&buffer, "%s", is_shadow ? "shadow" : "texture");
        ralloc_asprintf_append (&buffer, "%s", tex_sampler_dim_name[sampler_dim]);
    }
    else 
    {
        ralloc_asprintf_append (&buffer, "texture");
    }
	
	if (is_proj)
		ralloc_asprintf_append (&buffer, "Proj");
	if (ir->op == ir_txl)
		ralloc_asprintf_append (&buffer, "Lod");
	
	if (state->es_shader)
	{
		if ( (is_shadow && state->EXT_shadow_samplers_enable) ||
			(ir->op == ir_txl && state->EXT_shader_texture_lod_enable) )
		{
			ralloc_asprintf_append (&buffer, "EXT");
		}
	}
	
	ralloc_asprintf_append (&buffer, " (");
	
	// sampler
	ir->sampler->accept(this);
	ralloc_asprintf_append (&buffer, ", ");
	
	// texture coordinate
	ir->coordinate->accept(this);
	
	// lod bias
	if (ir->op == ir_txb)
	{
		ralloc_asprintf_append (&buffer, ", ");
		ir->lod_info.bias->accept(this);
	}
	
	// lod
	if (ir->op == ir_txl)
	{
		ralloc_asprintf_append (&buffer, ", ");
		ir->lod_info.lod->accept(this);
	}
	
	/*
	
   if (ir->offset != NULL) {
      ir->offset->accept(this);
   }
	
   if (ir->op != ir_txf) {
      if (ir->projector)
	 ir->projector->accept(this);
      else
	 ralloc_asprintf_append (&buffer, "1");

      if (ir->shadow_comparitor) {
	 ralloc_asprintf_append (&buffer, " ");
	 ir->shadow_comparitor->accept(this);
      } else {
	 ralloc_asprintf_append (&buffer, " ()");
      }
   }

   ralloc_asprintf_append (&buffer, " ");
   switch (ir->op)
   {
   case ir_tex:
      break;
   case ir_txb:
      ir->lod_info.bias->accept(this);
      break;
   case ir_txl:
   case ir_txf:
      ir->lod_info.lod->accept(this);
      break;
   case ir_txd:
      ralloc_asprintf_append (&buffer, "(");
      ir->lod_info.grad.dPdx->accept(this);
      ralloc_asprintf_append (&buffer, " ");
      ir->lod_info.grad.dPdy->accept(this);
      ralloc_asprintf_append (&buffer, ")");
      break;
   };
	 */
   ralloc_asprintf_append (&buffer, ")");
}


void ir_print_glsl_visitor::visit(ir_swizzle *ir)
{
   const unsigned swiz[4] = {
      ir->mask.x,
      ir->mask.y,
      ir->mask.z,
      ir->mask.w,
   };

	if (ir->val->type == glsl_type::float_type || ir->val->type == glsl_type::int_type)
	{
		if (ir->mask.num_components != 1)
		{
			buffer = print_type(buffer, ir->type, true);
			ralloc_asprintf_append (&buffer, "(");
		}
	}

	ir->val->accept(this);
	
	if (ir->val->type == glsl_type::float_type || ir->val->type == glsl_type::int_type)
	{
		if (ir->mask.num_components != 1)
		{
			ralloc_asprintf_append (&buffer, ")");
		}
		return;
	}

   ralloc_asprintf_append (&buffer, ".");
   for (unsigned i = 0; i < ir->mask.num_components; i++) {
		ralloc_asprintf_append (&buffer, "%c", "xyzw"[swiz[i]]);
   }
}


void ir_print_glsl_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->variable_referenced();
   print_var_name (var);
}


void ir_print_glsl_visitor::visit(ir_dereference_array *ir)
{
   ir->array->accept(this);
   ralloc_asprintf_append (&buffer, "[");
   ir->array_index->accept(this);
   ralloc_asprintf_append (&buffer, "]");
}


void ir_print_glsl_visitor::visit(ir_dereference_record *ir)
{
   ir->record->accept(this);
   ralloc_asprintf_append (&buffer, ".%s", ir->field);
}

void ir_print_glsl_visitor::visit(ir_assignment *ir)
{
	// assignments in global scope are postponed to main function
	if (this->mode != kPrintGlslNone)
	{
		assert (!this->globals->main_function_done);
		this->globals->global_assignements.push_tail (new(this->globals->mem_ctx) ga_entry(ir));
		ralloc_asprintf_append(&buffer, "//"); // for the ; that will follow (ugly, I know)
		return;
	}
	
   if (ir->condition)
   {
      ir->condition->accept(this);
	  ralloc_asprintf_append (&buffer, " ");
   }

   ir->lhs->accept(this);

   char mask[5];
   unsigned j = 0;
   const glsl_type* lhsType = ir->lhs->type;
   const glsl_type* rhsType = ir->rhs->type;
   if (ir->lhs->type->vector_elements > 1 && ir->write_mask != (1<<ir->lhs->type->vector_elements)-1)
   {
	   for (unsigned i = 0; i < 4; i++) {
		   if ((ir->write_mask & (1 << i)) != 0) {
			   mask[j] = "xyzw"[i];
			   j++;
		   }
	   }
	   lhsType = glsl_type::get_instance(lhsType->base_type, j, 1);
   }
   mask[j] = '\0';
   bool hasWriteMask = false;
   if (mask[0])
   {
	   ralloc_asprintf_append (&buffer, ".%s", mask);
	   hasWriteMask = true;
   }

   ralloc_asprintf_append (&buffer, " = ");

   bool typeMismatch = (lhsType != rhsType);
   const bool addSwizzle = hasWriteMask && typeMismatch;
   if (typeMismatch)
   {
	   if (!addSwizzle)
		buffer = print_type(buffer, lhsType, true);
	   ralloc_asprintf_append (&buffer, "(");
   }

   ir->rhs->accept(this);

   if (typeMismatch)
   {
	   ralloc_asprintf_append (&buffer, ")");
	   if (addSwizzle)
		   ralloc_asprintf_append (&buffer, ".%s", mask);
   }

}

static char* print_float (char* buffer, float f)
{
	// Kind of roundabout way, but this is to satisfy two things:
	// * MSVC and gcc-based compilers differ a bit in how they treat float
	//   widht/precision specifiers. Want to match for tests.
	// * GLSL (early version at least) require floats to have ".0" or
	//   exponential notation.
	char tmp[64];
	snprintf(tmp, 64, "%.6g", f);

	char* posE = NULL;
	posE = strchr(tmp, 'e');
	if (!posE)
		posE = strchr(tmp, 'E');

	#if _MSC_VER
	// While gcc would print something like 1.0e+07, MSVC will print 1.0e+007 -
	// only for exponential notation, it seems, will add one extra useless zero. Let's try to remove
	// that so compiler output matches.
	if (posE != NULL)
	{
		if((posE[1] == '+' || posE[1] == '-') && posE[2] == '0')
		{
			char* p = posE+2;
			while (p[0])
			{
				p[0] = p[1];
				++p;
			}
		}
	}
	#endif

	ralloc_strcat (&buffer, tmp);

	// need to append ".0"?
	if (!strchr(tmp,'.') && (posE == NULL))
		ralloc_strcat(&buffer, ".0");
	return buffer;
}

void ir_print_glsl_visitor::visit(ir_constant *ir)
{
	const glsl_type* type = ir->type;

	if (type == glsl_type::float_type)
	{
		buffer = print_float (buffer, ir->value.f[0]);
		return;
	}
	else if (type == glsl_type::int_type)
	{
		ralloc_asprintf_append (&buffer, "%d", ir->value.i[0]);
		return;
	}
	else if (type == glsl_type::uint_type)
	{
		ralloc_asprintf_append (&buffer, "%u", ir->value.u[0]);
		return;
	}

   const glsl_type *const base_type = ir->type->get_base_type();

   buffer = print_type(buffer, type, true);
   ralloc_asprintf_append (&buffer, "(");

   if (ir->type->is_array()) {
      for (unsigned i = 0; i < ir->type->length; i++)
      {
	 if (i != 0)
	    ralloc_asprintf_append (&buffer, ", ");
	 ir->get_array_element(i)->accept(this);
      }
   } else {
      bool first = true;
      for (unsigned i = 0; i < ir->type->components(); i++) {
	 if (!first)
	    ralloc_asprintf_append (&buffer, ", ");
	 first = false;
	 switch (base_type->base_type) {
	 case GLSL_TYPE_UINT:  ralloc_asprintf_append (&buffer, "%u", ir->value.u[i]); break;
	 case GLSL_TYPE_INT:   ralloc_asprintf_append (&buffer, "%d", ir->value.i[i]); break;
	 case GLSL_TYPE_FLOAT: buffer = print_float(buffer, ir->value.f[i]); break;
	 case GLSL_TYPE_BOOL:  ralloc_asprintf_append (&buffer, "%d", ir->value.b[i]); break;
	 default: assert(0);
	 }
      }
   }
   ralloc_asprintf_append (&buffer, ")");
}


void
ir_print_glsl_visitor::visit(ir_call *ir)
{
	// calls in global scope are postponed to main function
	if (this->mode != kPrintGlslNone)
	{
		assert (!this->globals->main_function_done);
		this->globals->global_assignements.push_tail (new(this->globals->mem_ctx) ga_entry(ir));
		ralloc_asprintf_append(&buffer, "//"); // for the ; that will follow (ugly, I know)
		return;
	}
	
	if (ir->return_deref)
	{
		visit(ir->return_deref);
		ralloc_asprintf_append (&buffer, " = ");		
	}
	
   ralloc_asprintf_append (&buffer, "%s (", ir->callee_name());
   bool first = true;
   foreach_iter(exec_list_iterator, iter, *ir) {
      ir_instruction *const inst = (ir_instruction *) iter.get();
	  if (!first)
		  ralloc_asprintf_append (&buffer, ", ");
      inst->accept(this);
	  first = false;
   }
   ralloc_asprintf_append (&buffer, ")");
}


void
ir_print_glsl_visitor::visit(ir_return *ir)
{
   ralloc_asprintf_append (&buffer, "return");

   ir_rvalue *const value = ir->get_value();
   if (value) {
      ralloc_asprintf_append (&buffer, " ");
      value->accept(this);
   }
}


void
ir_print_glsl_visitor::visit(ir_discard *ir)
{
   ralloc_asprintf_append (&buffer, "discard");

   if (ir->condition != NULL) {
      ralloc_asprintf_append (&buffer, " TODO ");
      ir->condition->accept(this);
   }
}


void
ir_print_glsl_visitor::visit(ir_if *ir)
{
   ralloc_asprintf_append (&buffer, "if (");
   ir->condition->accept(this);

   ralloc_asprintf_append (&buffer, ") {\n");
   indentation++;

   foreach_iter(exec_list_iterator, iter, ir->then_instructions) {
      ir_instruction *const inst = (ir_instruction *) iter.get();

      indent();
      inst->accept(this);
      ralloc_asprintf_append (&buffer, ";\n");
   }

   indentation--;
   indent();
   ralloc_asprintf_append (&buffer, "}");

   if (!ir->else_instructions.is_empty())
   {
	   ralloc_asprintf_append (&buffer, " else {\n");
	   indentation++;

	   foreach_iter(exec_list_iterator, iter, ir->else_instructions) {
		  ir_instruction *const inst = (ir_instruction *) iter.get();

		  indent();
		  inst->accept(this);
		  ralloc_asprintf_append (&buffer, ";\n");
	   }
	   indentation--;
	   indent();
	   ralloc_asprintf_append (&buffer, "}");
   }
}


void
ir_print_glsl_visitor::visit(ir_loop *ir)
{
	bool noData = (ir->counter == NULL && ir->from == NULL && ir->to == NULL && ir->increment == NULL);
	if (noData) {
		ralloc_asprintf_append (&buffer, "while (true) {\n");
		indentation++;
		foreach_iter(exec_list_iterator, iter, ir->body_instructions) {
			ir_instruction *const inst = (ir_instruction *) iter.get();
			indent();
			inst->accept(this);
			ralloc_asprintf_append (&buffer, ";\n");
		}
		indentation--;
		indent();
		ralloc_asprintf_append (&buffer, "}");
		return;
	}

	bool canonicalFor = (ir->counter && ir->from && ir->to && ir->increment);
	if (canonicalFor)
	{
		ralloc_asprintf_append (&buffer, "for (");
		ir->counter->accept (this);
		ralloc_asprintf_append (&buffer, " = ");
		ir->from->accept (this);
		ralloc_asprintf_append (&buffer, "; ");
		print_var_name (ir->counter);

		// IR cmp operator is when to terminate loop; whereas GLSL for loop syntax
		// is while to continue the loop. Invert the meaning of operator when outputting.
		const char* termOp = NULL;
		switch (ir->cmp) {
		case ir_binop_less: termOp = ">="; break;
		case ir_binop_greater: termOp = "<="; break;
		case ir_binop_lequal: termOp = ">"; break;
		case ir_binop_gequal: termOp = "<"; break;
		case ir_binop_equal: termOp = "!="; break;
		case ir_binop_nequal: termOp = "=="; break;
		default: assert(false);
		}
		ralloc_asprintf_append (&buffer, " %s ", termOp);
		ir->to->accept (this);
		ralloc_asprintf_append (&buffer, "; ");
		// IR already has instructions that modify the loop counter in the body
		//print_var_name (ir->counter);
		//ralloc_asprintf_append (&buffer, " = ");
		//print_var_name (ir->counter);
		//ralloc_asprintf_append (&buffer, "+(");
		//ir->increment->accept (this);
		//ralloc_asprintf_append (&buffer, ")");
		ralloc_asprintf_append (&buffer, ") {\n");
		indentation++;
		foreach_iter(exec_list_iterator, iter, ir->body_instructions) {
			ir_instruction *const inst = (ir_instruction *) iter.get();
			indent();
			inst->accept(this);
			ralloc_asprintf_append (&buffer, ";\n");
		}
		indentation--;
		indent();
		ralloc_asprintf_append (&buffer, "}");
		return;
	}


   ralloc_asprintf_append (&buffer, "( TODO loop (");
   if (ir->counter != NULL)
      ir->counter->accept(this);
   ralloc_asprintf_append (&buffer, ") (");
   if (ir->from != NULL)
      ir->from->accept(this);
   ralloc_asprintf_append (&buffer, ") (");
   if (ir->to != NULL)
      ir->to->accept(this);
   ralloc_asprintf_append (&buffer, ") (");
   if (ir->increment != NULL)
      ir->increment->accept(this);
   ralloc_asprintf_append (&buffer, ") (\n");
   indentation++;

   foreach_iter(exec_list_iterator, iter, ir->body_instructions) {
      ir_instruction *const inst = (ir_instruction *) iter.get();

      indent();
      inst->accept(this);
      ralloc_asprintf_append (&buffer, ";\n");
   }
   indentation--;
   indent();
   ralloc_asprintf_append (&buffer, "))\n");
}


void
ir_print_glsl_visitor::visit(ir_loop_jump *ir)
{
   ralloc_asprintf_append (&buffer, "%s", ir->is_break() ? "break" : "continue");
}

void
ir_print_glsl_visitor::visit(ir_precision_statement *ir)
{
	ralloc_asprintf_append (&buffer, "%s", ir->precision_statement);
}

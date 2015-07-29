/*
 * Copyright © 2014 Unity Technologies
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

#include "ir_print_metal_visitor.h"
#include "ir_visitor.h"
#include "glsl_types.h"
#include "glsl_parser_extras.h"
#include "ir_unused_structs.h"
#include "loop_analysis.h"
#include "program/hash_table.h"
#include <math.h>


static void print_type(string_buffer& buffer, ir_instruction* ir, const glsl_type *t, bool arraySize);
static void print_type_post(string_buffer& buffer, const glsl_type *t, bool arraySize);


struct ga_entry_metal : public exec_node
{
	ga_entry_metal(ir_instruction* ir)
	{
		assert(ir);
		this->ir = ir;
	}
	ir_instruction* ir;
};
struct gconst_entry_metal : public exec_node
{
	gconst_entry_metal(ir_constant* ir, unsigned id)
	{
		assert(ir);
		this->ir = ir;
		this->id = id;
	}
	ir_constant* ir;
	unsigned id;
};


struct global_print_tracker_metal
{
	global_print_tracker_metal ()
	{
		mem_ctx = ralloc_context(0);
		var_counter = 0;
		var_hash = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);
		const_counter = 0;
		const_hash = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);
		main_function_done = false;
	}

	~global_print_tracker_metal()
	{
		hash_table_dtor (var_hash);
		hash_table_dtor (const_hash);
		ralloc_free(mem_ctx);
	}

	unsigned	var_counter;
	hash_table*	var_hash;
	exec_list	global_assignements;

	unsigned	const_counter;
	hash_table*	const_hash;
	exec_list	global_constants;

	void*		mem_ctx;
	bool		main_function_done;
};


struct metal_print_context
{
	metal_print_context(char* buffer)
	: str(buffer)
	, prefixStr(ralloc_strdup(buffer, ""))
	, inputStr(ralloc_strdup(buffer, ""))
	, outputStr(ralloc_strdup(buffer, ""))
	, inoutStr(ralloc_strdup(buffer, ""))
	, uniformStr(ralloc_strdup(buffer, ""))
	, paramsStr(ralloc_strdup(buffer, ""))
	, writingParams(false)
	, matrixCastsDone(false)
	, matrixConstructorsDone(false)
	, shadowSamplerDone(false)
	, textureCounter(0)
	, attributeCounter(0)
	, uniformLocationCounter(0)
	, colorCounter(0)
	{
	}

	string_buffer str;
	string_buffer prefixStr;
	string_buffer inputStr;
	string_buffer outputStr;
	string_buffer inoutStr;
	string_buffer uniformStr;
	string_buffer paramsStr;
	bool writingParams;
	bool matrixCastsDone;
	bool matrixConstructorsDone;
	bool shadowSamplerDone;
	int textureCounter;
	int attributeCounter;
	int uniformLocationCounter;
	int colorCounter;
};


class ir_print_metal_visitor : public ir_visitor {
public:
	ir_print_metal_visitor(metal_print_context& ctx_, string_buffer& buf, global_print_tracker_metal* globals_, PrintGlslMode mode_, const _mesa_glsl_parse_state* state_)
		: ctx(ctx_)
		, buffer(buf)
		, loopstate(NULL)
		, inside_loop_body(false)
		, inside_lhs(false)
		, skipped_this_ir(false)
		, previous_skipped(false)
		, mode_whole(mode_)
	{
		indentation = 0;
		expression_depth = 0;
		globals = globals_;
		mode = mode_;
		state = state_;
	}

	virtual ~ir_print_metal_visitor()
	{
	}


	void indent(void);
	void newline_indent();
	void end_statement_line();
	void newline_deindent();
	void print_var_name (ir_variable* v);

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
	virtual void visit(ir_typedecl_statement *);
	virtual void visit(ir_emit_vertex *);
	virtual void visit(ir_end_primitive *);

	void emit_assignment_part (ir_dereference* lhs, ir_rvalue* rhs, unsigned write_mask, ir_rvalue* dstIndex);
	bool can_emit_canonical_for (loop_variable_state *ls);
	bool emit_canonical_for (ir_loop* ir);

	metal_print_context& ctx;
	int indentation;
	int expression_depth;
	string_buffer& buffer;
	global_print_tracker_metal* globals;
	const _mesa_glsl_parse_state* state;
	PrintGlslMode mode;
	const PrintGlslMode mode_whole;
	loop_state* loopstate;
	bool	inside_loop_body;
	bool	inside_lhs;
	bool	skipped_this_ir;
	bool	previous_skipped;
};


char*
_mesa_print_ir_metal(exec_list *instructions,
	    struct _mesa_glsl_parse_state *state,
		char* buffer, PrintGlslMode mode, int* outUniformsSize)
{
	metal_print_context ctx(buffer);

	// includes, prefix etc.
	ctx.prefixStr.asprintf_append ("#include <metal_stdlib>\n");
	ctx.prefixStr.asprintf_append ("using namespace metal;\n");

	ctx.inputStr.asprintf_append("struct xlatMtlShaderInput {\n");
	ctx.outputStr.asprintf_append("struct xlatMtlShaderOutput {\n");
	ctx.uniformStr.asprintf_append("struct xlatMtlShaderUniform {\n");

	// remove unused struct declarations
	do_remove_unused_typedecls(instructions);

	global_print_tracker_metal gtracker;

	loop_state* ls = analyze_loop_variables(instructions);
	if (ls->loop_found)
		set_loop_controls(instructions, ls);

	foreach_in_list(ir_instruction, ir, instructions)
	{
		string_buffer* strOut = &ctx.str;
		ctx.writingParams = false;
		if (ir->ir_type == ir_type_variable)
		{
			ir_variable *var = static_cast<ir_variable*>(ir);

			// skip gl_ variables if they aren't used/assigned
			if (strstr(var->name, "gl_") == var->name)
			{
				if (!var->data.used && !var->data.assigned)
					continue;
			}

			//
			if (var->data.mode == ir_var_uniform)
			{
				if (var->type->is_sampler())
				{
					strOut = &ctx.paramsStr;
					ctx.writingParams = true;
					strOut->asprintf_append ("\n  , ");
				}
				else
					strOut = &ctx.uniformStr;
			}
			if (var->data.mode == ir_var_system_value)
			{
				strOut = &ctx.paramsStr;
				ctx.writingParams = true;
				strOut->asprintf_append ("\n  , ");
			}
			if (var->data.mode == ir_var_shader_in)
				strOut = &ctx.inputStr;
			if (var->data.mode == ir_var_shader_out)
				strOut = &ctx.outputStr;
			if (var->data.mode == ir_var_shader_inout)
				strOut = &ctx.inoutStr;
		}


		ir_print_metal_visitor v (ctx, *strOut, &gtracker, mode, state);
		v.loopstate = ls;

		ir->accept(&v);
		if (ir->ir_type != ir_type_function && !v.skipped_this_ir)
		{
			if (!ctx.writingParams)
				strOut->asprintf_append (";\n");
		}
	}

	delete ls;

	// append inout variables to both input & output structs
	if (!ctx.inoutStr.empty())
	{
		ctx.inputStr.asprintf_append("%s", ctx.inoutStr.c_str());
		ctx.outputStr.asprintf_append("%s", ctx.inoutStr.c_str());
	}
	ctx.inputStr.asprintf_append("};\n");
	ctx.outputStr.asprintf_append("};\n");
	ctx.uniformStr.asprintf_append("};\n");

	// emit global array/struct constants
	foreach_in_list_safe(gconst_entry_metal, node, &gtracker.global_constants)
	{
		ir_constant* c = node->ir;

		ir_print_metal_visitor v (ctx, ctx.prefixStr, &gtracker, mode, state);

		v.buffer.asprintf_append ("constant ");
		print_type(v.buffer, c, c->type, false);
		v.buffer.asprintf_append (" _xlat_mtl_const%i", (int)((gconst_entry_metal*)node)->id);
		print_type_post(v.buffer, c->type, false);
		v.buffer.asprintf_append (" = {");

		if (c->type->is_array())
		{
			for (unsigned i = 0; i < c->type->length; i++)
			{
				if (i != 0)
					v.buffer.asprintf_append (", ");
				c->get_array_element(i)->accept(&v);
			}
		}
		else
		{
			assert(c->type->is_record());
			bool first = true;
			foreach_in_list(ir_constant, inst, &c->components)
			{
				if (!first)
					v.buffer.asprintf_append (", ");
				first = false;
				inst->accept(&v);
			}
		}
		v.buffer.asprintf_append ("};\n");
	}


	ctx.prefixStr.asprintf_append("%s", ctx.inputStr.c_str());
	ctx.prefixStr.asprintf_append("%s", ctx.outputStr.c_str());
	ctx.prefixStr.asprintf_append("%s", ctx.uniformStr.c_str());
	ctx.prefixStr.asprintf_append("%s", ctx.str.c_str());

	*outUniformsSize = ctx.uniformLocationCounter;

	return ralloc_strdup(buffer, ctx.prefixStr.c_str());
}


void ir_print_metal_visitor::indent(void)
{
	if (previous_skipped)
		return;
	previous_skipped = false;
	for (int i = 0; i < indentation; i++)
		buffer.asprintf_append ("  ");
}

void ir_print_metal_visitor::end_statement_line()
{
	if (!skipped_this_ir)
		buffer.asprintf_append(";\n");
	previous_skipped = skipped_this_ir;
	skipped_this_ir = false;
}

void ir_print_metal_visitor::newline_indent()
{
	if (expression_depth % 4 == 0)
	{
		++indentation;
		buffer.asprintf_append ("\n");
		indent();
	}
}
void ir_print_metal_visitor::newline_deindent()
{
	if (expression_depth % 4 == 0)
	{
		--indentation;
		buffer.asprintf_append ("\n");
		indent();
	}
}


void ir_print_metal_visitor::print_var_name (ir_variable* v)
{
    uintptr_t id = (uintptr_t)hash_table_find (globals->var_hash, v);
	if (!id && v->data.mode == ir_var_temporary)
	{
        id = ++globals->var_counter;
        hash_table_insert (globals->var_hash, (void*)id, v);
	}
    if (id)
    {
        if (v->data.mode == ir_var_temporary)
            buffer.asprintf_append ("tmpvar_%d", (int)id);
        else
            buffer.asprintf_append ("%s_%d", v->name, (int)id);
    }
	else
	{
		buffer.asprintf_append ("%s", v->name);
	}
}



static void print_type_precision(string_buffer& buffer, const glsl_type *t, glsl_precision prec, bool arraySize)
{
	const bool halfPrec = (prec == glsl_precision_medium || prec == glsl_precision_low);

	const char* typeName = t->name;
	// scalars
	if (!strcmp(typeName, "float"))
		typeName = halfPrec ? "half" : "float";
	else if (!strcmp(typeName, "int"))
		typeName = halfPrec ? "short" : "int";
	// vectors
	else if (!strcmp(typeName, "vec2"))
		typeName = halfPrec ? "half2" : "float2";
	else if (!strcmp(typeName, "vec3"))
		typeName = halfPrec ? "half3" : "float3";
	else if (!strcmp(typeName, "vec4"))
		typeName = halfPrec ? "half4" : "float4";
	else if (!strcmp(typeName, "ivec2"))
		typeName = halfPrec ? "short2" : "int2";
	else if (!strcmp(typeName, "ivec3"))
		typeName = halfPrec ? "short3" : "int3";
	else if (!strcmp(typeName, "ivec4"))
		typeName = halfPrec ? "short4" : "int4";
	else if (!strcmp(typeName, "bvec2"))
		typeName = "bool2";
	else if (!strcmp(typeName, "bvec3"))
		typeName = "bool3";
	else if (!strcmp(typeName, "bvec4"))
		typeName = "bool4";
	// matrices
	else if (!strcmp(typeName, "mat2"))
		typeName = halfPrec ? "half2x2" : "float2x2";
	else if (!strcmp(typeName, "mat3"))
		typeName = halfPrec ? "half3x3" : "float3x3";
	else if (!strcmp(typeName, "mat4"))
		typeName = halfPrec ? "half4x4" : "float4x4";
	// non-square matrices
	else if (!strcmp(typeName, "mat2x2"))
		typeName = halfPrec ? "half2x2" : "float2x2";
	else if (!strcmp(typeName, "mat2x3"))
		typeName = halfPrec ? "half2x3" : "float2x3";
	else if (!strcmp(typeName, "mat2x4"))
		typeName = halfPrec ? "half2x4" : "float2x4";
	else if (!strcmp(typeName, "mat3x2"))
		typeName = halfPrec ? "half3x2" : "float3x2";
	else if (!strcmp(typeName, "mat3x3"))
		typeName = halfPrec ? "half3x3" : "float3x3";
	else if (!strcmp(typeName, "mat3x4"))
		typeName = halfPrec ? "half3x4" : "float3x4";
	else if (!strcmp(typeName, "mat4x2"))
		typeName = halfPrec ? "half4x2" : "float4x2";
	else if (!strcmp(typeName, "mat4x3"))
		typeName = halfPrec ? "half4x3" : "float4x3";
	else if (!strcmp(typeName, "mat4x4"))
		typeName = halfPrec ? "half4x4" : "float4x4";
	// samplers
	else if (!strcmp(typeName, "sampler2D"))
		typeName = halfPrec ? "texture2d<half>" : "texture2d<float>";
	else if (!strcmp(typeName, "samplerCube"))
		typeName = halfPrec ? "texturecube<half>" : "texturecube<float>";
	else if (!strcmp(typeName, "sampler3D"))
		typeName = halfPrec ? "texture3d<half>" : "texture3d<float>";
	else if (!strcmp(typeName, "sampler2DShadow"))
		typeName = "depth2d<float>"; // depth type must always be float
	else if (!strcmp(typeName, "samplerCubeShadow"))
		typeName = "depthcube<float>"; // depth type must always be float

	if (t->base_type == GLSL_TYPE_ARRAY) {
		print_type_precision(buffer, t->fields.array, prec, true);
		if (arraySize)
			buffer.asprintf_append ("[%u]", t->length);
	} else if ((t->base_type == GLSL_TYPE_STRUCT)
			   && (strncmp("gl_", typeName, 3) != 0)) {
		buffer.asprintf_append ("%s", typeName);
	} else {
		buffer.asprintf_append ("%s", typeName);
	}
}


static void print_type(string_buffer& buffer, ir_instruction* ir, const glsl_type *t, bool arraySize)
{
	glsl_precision prec = precision_from_ir(ir);
	if (prec == glsl_precision_low)
		prec = glsl_precision_medium; // Metal does not have low precision; treat as medium
	print_type_precision(buffer, t, prec, arraySize);
}


static void print_type_post(string_buffer& buffer, const glsl_type *t, bool arraySize)
{
	if (t->base_type == GLSL_TYPE_ARRAY) {
		if (!arraySize)
			buffer.asprintf_append ("[%u]", t->length);
	}
}

static void get_metal_type_size(const glsl_type* type, glsl_precision prec, int& size, int& alignment)
{
	if (prec == glsl_precision_undefined)
		prec = glsl_precision_high;
	if (prec == glsl_precision_low)
		prec = glsl_precision_medium;
	const bool half = (prec == glsl_precision_medium);

	const int asize = type->is_array() ? type->length : 1;
	if (type->is_array())
		type = type->element_type();

	if (type->base_type == GLSL_TYPE_UINT || type->base_type == GLSL_TYPE_INT || type->base_type == GLSL_TYPE_FLOAT)
	{
		size = half ? 2 : 4;
	}
	else if (type->base_type == GLSL_TYPE_BOOL)
	{
		size = 1;
	}
	else
	{
		size = 0;
	}
	alignment = MAX2(size,1);

	int vsize = type->vector_elements;
	// float3 etc in Metal has both sizeof and alignment same as float4
	if (vsize == 3)
		vsize = 4;

	size *= vsize;
	alignment *= vsize;

	const int msize = type->matrix_columns;
	size *= msize;

	size *= asize;
}

void ir_print_metal_visitor::visit(ir_variable *ir)
{
	const char *const cent = (ir->data.centroid) ? "centroid " : "";
	const char *const inv = (ir->data.invariant) ? "invariant " : "";
	const char *const mode[ir_var_mode_count] = { "", "  ", "  ", "  ", "  ", "in ", "out ", "inout ", "", "", "" };

	const char *const interp[] = { "", "smooth ", "flat ", "noperspective " };

	// give an id to any variable defined in a function that is not an uniform
	if ((this->mode == kPrintGlslNone && ir->data.mode != ir_var_uniform))
	{
		uintptr_t id = (uintptr_t)hash_table_find (globals->var_hash, ir);
		if (id == 0)
		{
			id = ++globals->var_counter;
			hash_table_insert (globals->var_hash, (void*)id, ir);
		}
	}

	// auto/temp variables in global scope are postponed to main function
	if (this->mode != kPrintGlslNone && (ir->data.mode == ir_var_auto || ir->data.mode == ir_var_temporary))
	{
		assert (!this->globals->main_function_done);
		this->globals->global_assignements.push_tail (new(this->globals->mem_ctx) ga_entry_metal(ir));
		skipped_this_ir = true;
		return;
	}

	// if this is a loop induction variable, do not print it
	// (will be printed inside loop body)
	if (!inside_loop_body)
	{
		loop_variable_state* inductor_state = loopstate->get_for_inductor(ir);
		if (inductor_state && inductor_state->private_induction_variable_count == 1 &&
			can_emit_canonical_for(inductor_state))
		{
			skipped_this_ir = true;
			return;
		}
	}

	buffer.asprintf_append ("%s%s%s%s",
							cent, inv, interp[ir->data.interpolation], mode[ir->data.mode]);
	print_type(buffer, ir, ir->type, false);
	buffer.asprintf_append (" ");
	print_var_name (ir);
	print_type_post(buffer, ir->type, false);

	// special built-in variables
	if (!strcmp(ir->name, "gl_FragDepth"))
		buffer.asprintf_append (" [[depth(any)]]");
	else if (!strcmp(ir->name, "gl_FragCoord"))
		buffer.asprintf_append (" [[position]]");
	else if (!strcmp(ir->name, "gl_FrontFacing"))
		buffer.asprintf_append (" [[front_facing]]");
	else if (!strcmp(ir->name, "gl_PointCoord"))
		buffer.asprintf_append (" [[point_coord]]");
	else if (!strcmp(ir->name, "gl_PointSize"))
		buffer.asprintf_append (" [[point_size]]");
	else if (!strcmp(ir->name, "gl_Position"))
		buffer.asprintf_append (" [[position]]");
	else if (!strcmp(ir->name, "gl_VertexID"))
		buffer.asprintf_append (" [[vertex_id]]");
	else if (!strcmp(ir->name, "gl_InstanceID"))
		buffer.asprintf_append (" [[instance_id]]");

	// vertex shader input attribute?
	if (this->mode_whole == kPrintGlslVertex && ir->data.mode == ir_var_shader_in)
	{
		buffer.asprintf_append (" [[attribute(%i)]]", ctx.attributeCounter);
		ir->data.explicit_location = 1;
		ir->data.location = ctx.attributeCounter;
		++ctx.attributeCounter;
	}

	// fragment shader output?
	if (this->mode_whole == kPrintGlslFragment && (ir->data.mode == ir_var_shader_out || ir->data.mode == ir_var_shader_inout))
	{
		if (!ir->data.explicit_location)
		{
			ir->data.explicit_location = 1;
			ir->data.location = FRAG_RESULT_DATA0 + ctx.colorCounter;
			++ctx.colorCounter;
		}

		if (ir->data.explicit_location)
		{
			const int binding_base = (int)FRAG_RESULT_DATA0;
			const int location = ir->data.location - binding_base;
			if (location >= 0 && !ir->type->is_array())
				buffer.asprintf_append (" [[color(%d)]]", location);
		}
	}

	// uniform texture?
	if (ir->data.mode == ir_var_uniform && ctx.writingParams)
	{
		buffer.asprintf_append (" [[texture(%i)]]", ctx.textureCounter);
		buffer.asprintf_append (", sampler _mtlsmp_%s [[sampler(%i)]]", ir->name, ctx.textureCounter);
		ir->data.explicit_location = 1;
		ir->data.location = ctx.textureCounter;
		++ctx.textureCounter;
	}
	// regular uniform?
	if (ir->data.mode == ir_var_uniform && !ctx.writingParams)
	{
		int size, align;
		get_metal_type_size(ir->type, (glsl_precision)ir->data.precision, size, align);

		int loc = ctx.uniformLocationCounter;
		loc = (loc + align-1) & ~(align-1); // align it

		ir->data.explicit_location = 1;
		ir->data.location = loc;

		loc += size;
		ctx.uniformLocationCounter = loc;
	}

	if (ir->constant_value &&
		ir->data.mode != ir_var_shader_in &&
		ir->data.mode != ir_var_shader_out &&
		ir->data.mode != ir_var_shader_inout &&
		ir->data.mode != ir_var_function_in &&
		ir->data.mode != ir_var_function_out &&
		ir->data.mode != ir_var_function_inout)
	{
		buffer.asprintf_append (" = ");
		visit (ir->constant_value);
	}
}


void ir_print_metal_visitor::visit(ir_function_signature *ir)
{
	const bool isMain = (strcmp(ir->function()->name, "main") == 0);

	if (!isMain)
	{
		print_type(buffer, ir, ir->return_type, true);
		buffer.asprintf_append (" %s (", ir->function_name());

		if (!ir->parameters.is_empty())
		{
			buffer.asprintf_append ("\n");

			indentation++; previous_skipped = false;
			bool first = true;
			foreach_in_list(ir_variable, inst, &ir->parameters)
			{
				if (!first)
					buffer.asprintf_append (",\n");
				indent();
				inst->accept(this);
				first = false;
			}
			indentation--;

			buffer.asprintf_append ("\n");
			indent();
		}
	}
	else
	{
		if (this->mode_whole == kPrintGlslFragment)
			buffer.asprintf_append ("fragment ");
		if (this->mode_whole == kPrintGlslVertex)
			buffer.asprintf_append ("vertex ");
		buffer.asprintf_append ("xlatMtlShaderOutput xlatMtlMain (xlatMtlShaderInput _mtl_i [[stage_in]], constant xlatMtlShaderUniform& _mtl_u [[buffer(0)]]");
		if (!ctx.paramsStr.empty())
		{
			buffer.asprintf_append ("%s", ctx.paramsStr.c_str());
		}
	}

   if (ir->body.is_empty())
   {
	   buffer.asprintf_append (");\n");
	   return;
   }

   buffer.asprintf_append (")\n");

   indent();
   buffer.asprintf_append ("{\n");
   indentation++; previous_skipped = false;

	if (isMain)
	{
		// output struct
		indent(); buffer.asprintf_append ("xlatMtlShaderOutput _mtl_o;\n");

		// insert postponed global assigments and variable declarations
		assert (!globals->main_function_done);
		globals->main_function_done = true;
		foreach_in_list(ga_entry_metal, node, &globals->global_assignements)
		{
			ir_instruction* as = node->ir;
			as->accept(this);
			buffer.asprintf_append(";\n");
		}
	}

   foreach_in_list(ir_instruction, inst, &ir->body) {
      indent();
      inst->accept(this);
	   end_statement_line();
   }

	if (isMain)
	{
		// return stuff
		indent(); buffer.asprintf_append ("return _mtl_o;\n");
	}

   indentation--;
   indent();
   buffer.asprintf_append ("}\n");
}

void ir_print_metal_visitor::visit(ir_function *ir)
{
   bool found_non_builtin_proto = false;

   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
	   if (!sig->is_builtin())
		   found_non_builtin_proto = true;
   }
   if (!found_non_builtin_proto)
      return;

   PrintGlslMode oldMode = this->mode;
   this->mode = kPrintGlslNone;

   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
      indent();
      sig->accept(this);
      buffer.asprintf_append ("\n");
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
	"rsqrt",
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
	"as_type_",	// bit i2f
	"as_type_",	// bit f2i
	"as_type_",	// bit u2f
	"as_type_",	// bit f2u
	"any",
	"trunc",
	"ceil",
	"floor",
	"fract",
	"rint",
	"sin",
	"cos",
	"fast::sin", // reduced
	"fast::cos", // reduced
	"dfdx",
	"dfdx", // coarse
	"dfdx", // fine
	"dfdy",
	"dfdy", // coarse
	"dfdy", // fine
	"packSnorm2x16",
	"packSnorm4x8",
	"packUnorm2x16",
	"packUnorm4x8",
	"packHalf2x16",
	"unpackSnorm2x16",
	"unpackSnorm4x8",
	"unpackUnorm2x16",
	"unpackUnorm4x8",
	"unpackHalf2x16",
	"unpackHalf2x16_splitX_TODO",
	"unpackHalf2x16_splitY_TODO",
	"bitfieldReverse",
	"bitCount",
	"findMSB",
	"findLSB",
	"saturate",
	"noise",
	"interpolateAtCentroid_TODO",
	"+",
	"-",
	"*",
	"*_imul_high_TODO",
	"/",
	"carry_TODO",
	"borrow_TODO",
	"fmod",
	"<",
	">",
	"<=",
	">=",
	"==",
	"!=",
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
	"packHalf2x16_split_TODO",
	"bfm_TODO",
	"uboloadTODO",
	"ldexp_TODO",
	"vectorExtract_TODO",
	"interpolateAtOffset_TODO",
	"interpolateAtSample_TODO",
	"fma",
	"clamp",
	"mix",
	"csel_TODO",
	"bfi_TODO",
	"bitfield_extract_TODO",
	"vector_insert_TODO",
	"bitfield_insert_TODO",
	"vectorTODO",
};


static bool is_binop_func_like(ir_expression_operation op, const glsl_type* type)
{
	if (op == ir_binop_mod ||
		(op >= ir_binop_dot && op <= ir_binop_pow))
		return true;
	return false;
}


static bool is_different_precision(glsl_precision a, glsl_precision b)
{
	// Tread "undefined" as high precision
	if (a == glsl_precision_undefined)
		a = glsl_precision_high;
	if (b == glsl_precision_undefined)
		b = glsl_precision_high;
	// Metal does not have "low" precision; treat as medium
	if (a == glsl_precision_low)
		a = glsl_precision_medium;
	if (b == glsl_precision_low)
		b = glsl_precision_medium;

	return a != b;
}


static void print_cast(string_buffer& buffer, glsl_precision prec, ir_rvalue* ir)
{
	buffer.asprintf_append ("(");
	print_type_precision(buffer, ir->type, prec, false);
	buffer.asprintf_append (")");
}


void ir_print_metal_visitor::visit(ir_expression *ir)
{
	++this->expression_depth;
	newline_indent();

	glsl_precision arg_prec = glsl_precision_undefined;
	if (ir->operands[0])
		arg_prec = higher_precision(arg_prec, ir->operands[0]->get_precision());
	if (ir->operands[1])
		arg_prec = higher_precision(arg_prec, ir->operands[1]->get_precision());
	if (ir->operands[2])
		arg_prec = higher_precision(arg_prec, ir->operands[2]->get_precision());
	glsl_precision res_prec = ir->get_precision();

	bool op0cast = ir->operands[0] && is_different_precision(arg_prec, ir->operands[0]->get_precision());
	bool op1cast = ir->operands[1] && is_different_precision(arg_prec, ir->operands[1]->get_precision());
	bool op2cast = ir->operands[2] && is_different_precision(arg_prec, ir->operands[2]->get_precision());
	const bool op0matrix = ir->operands[0] && ir->operands[0]->type->is_matrix();
	const bool op1matrix = ir->operands[1] && ir->operands[1]->type->is_matrix();
	bool op0castTo1 = false;
	bool op1castTo0 = false;

	// Metal does not support matrix precision casts, so when any of the arguments is a matrix,
	// take precision from it. This isn't fully robust now, but oh well.
	if (op0cast && op0matrix && !op1cast)
	{
		op0cast = false;
		arg_prec = ir->operands[0]->get_precision();
		op1cast = ir->operands[1] && is_different_precision(arg_prec, ir->operands[1]->get_precision());
	}
	if (op1cast && op1matrix && !op0cast)
	{
		op1cast = false;
		arg_prec = ir->operands[1]->get_precision();
		op0cast = ir->operands[0] && is_different_precision(arg_prec, ir->operands[0]->get_precision());
	}

	// Metal does not have matrix+scalar and matrix-scalar operations; we need to create matrices
	// out of the non-matrix argument.
	if (ir->operation == ir_binop_add || ir->operation == ir_binop_sub)
	{
		if (op0matrix && !op1matrix)
		{
			op1cast = true;
			op1castTo0 = true;
		}
		if (op1matrix && !op0matrix)
		{
			op0cast = true;
			op0castTo1 = true;
		}
		if (op1castTo0 || op0castTo1)
		{
			if (!ctx.matrixConstructorsDone)
			{
				ctx.prefixStr.asprintf_append(
											  "inline float4x4 _xlinit_float4x4(float v) { return float4x4(float4(v), float4(v), float4(v), float4(v)); }\n"
											  "inline float3x3 _xlinit_float3x3(float v) { return float3x3(float3(v), float3(v), float3(v)); }\n"
											  "inline float2x2 _xlinit_float2x2(float v) { return float2x2(float2(v), float2(v)); }\n"
											  "inline half4x4 _xlinit_half4x4(half v) { return half4x4(half4(v), half4(v), half4(v), half4(v)); }\n"
											  "inline half3x3 _xlinit_half3x3(half v) { return half3x3(half3(v), half3(v), half3(v)); }\n"
											  "inline half2x2 _xlinit_half2x2(half v) { return half2x2(half2(v), half2(v)); }\n"
											  );
				ctx.matrixConstructorsDone = true;
			}
		}
	}
	
	const bool rescast = is_different_precision(arg_prec, res_prec) && !ir->type->is_boolean();
	if (rescast)
	{
		buffer.asprintf_append ("(");
		print_cast (buffer, res_prec, ir);
	}

	if (ir->get_num_operands() == 1)
	{
		if (op0cast)
			print_cast (buffer, arg_prec, ir->operands[0]);
		if (ir->operation >= ir_unop_f2i && ir->operation <= ir_unop_u2i) {
			print_type(buffer, ir, ir->type, true);
			buffer.asprintf_append ("(");
		} else if (ir->operation >= ir_unop_bitcast_i2f && ir->operation <= ir_unop_bitcast_f2u) {
			buffer.asprintf_append("as_type<");
			print_type(buffer, ir, ir->type, true);
			buffer.asprintf_append(">(");
		} else if (ir->operation == ir_unop_rcp) {
			const bool halfCast = (arg_prec == glsl_precision_medium || arg_prec == glsl_precision_low);
			buffer.asprintf_append (halfCast ? "((half)1.0/(" : "(1.0/(");
		} else {
			buffer.asprintf_append ("%s(", operator_glsl_strs[ir->operation]);
		}
		if (ir->operands[0])
			ir->operands[0]->accept(this);
		buffer.asprintf_append (")");
		if (ir->operation == ir_unop_rcp) {
			buffer.asprintf_append (")");
		}
	}
	else if (ir->operation == ir_binop_vector_extract)
	{
		// a[b]

		if (ir->operands[0])
			ir->operands[0]->accept(this);
		buffer.asprintf_append ("[");
		if (ir->operands[1])
			ir->operands[1]->accept(this);
		buffer.asprintf_append ("]");
	}
	else if (is_binop_func_like(ir->operation, ir->type))
	{
		// binary operation that must be printed like a function, "foo(a,b)"
		if (ir->operation == ir_binop_mod)
		{
			buffer.asprintf_append ("(");
			print_type(buffer, ir, ir->type, true);
			buffer.asprintf_append ("(");
		}
		buffer.asprintf_append ("%s (", operator_glsl_strs[ir->operation]);

		if (ir->operands[0])
		{
			if (op0cast)
				print_cast (buffer, arg_prec, ir->operands[0]);
			ir->operands[0]->accept(this);
		}
		buffer.asprintf_append (", ");
		if (ir->operands[1])
		{
			if (op1cast)
				print_cast (buffer, arg_prec, ir->operands[1]);
			ir->operands[1]->accept(this);
		}
		buffer.asprintf_append (")");
		if (ir->operation == ir_binop_mod)
            buffer.asprintf_append ("))");
	}
	else if (ir->get_num_operands() == 2 && ir->operation == ir_binop_div && op0matrix && !op1matrix)
	{
		// "matrix/scalar" - Metal does not have it, so print multiply by inverse instead
		buffer.asprintf_append ("(");
		ir->operands[0]->accept(this);
		const bool halfCast = (arg_prec == glsl_precision_medium || arg_prec == glsl_precision_low);
		buffer.asprintf_append (halfCast ? " * (1.0h/half(" : " * (1.0/(");
		ir->operands[1]->accept(this);
		buffer.asprintf_append (")))");
	}
	else if (ir->get_num_operands() == 2)
	{
		// regular binary operator
		buffer.asprintf_append ("(");
		if (ir->operands[0])
		{
			if (op0castTo1)
			{
				buffer.asprintf_append ("_xlinit_");
				print_type_precision(buffer, ir->operands[1]->type, arg_prec, false);
				buffer.asprintf_append ("(");
			}
			else if (op0cast)
			{
				print_cast (buffer, arg_prec, ir->operands[0]);
			}
			ir->operands[0]->accept(this);
			if (op0castTo1)
			{
				buffer.asprintf_append (")");
			}
		}

		buffer.asprintf_append (" %s ", operator_glsl_strs[ir->operation]);

		if (ir->operands[1])
		{
			if (op1castTo0)
			{
				buffer.asprintf_append ("_xlinit_");
				print_type_precision(buffer, ir->operands[0]->type, arg_prec, false);
				buffer.asprintf_append ("(");
			}
			else if (op1cast)
			{
				print_cast (buffer, arg_prec, ir->operands[1]);
			}
			ir->operands[1]->accept(this);
			if (op1castTo0)
			{
				buffer.asprintf_append (")");
			}
		}
		buffer.asprintf_append (")");
	}
	else
	{
		// ternary op
		buffer.asprintf_append ("%s (", operator_glsl_strs[ir->operation]);
		if (ir->operands[0])
		{
			if (op0cast)
				print_cast (buffer, arg_prec, ir->operands[0]);
			ir->operands[0]->accept(this);
		}
		buffer.asprintf_append (", ");
		if (ir->operands[1])
		{
			if (op1cast)
				print_cast (buffer, arg_prec, ir->operands[1]);
			ir->operands[1]->accept(this);
		}
		buffer.asprintf_append (", ");
		if (ir->operands[2])
		{
			if (op2cast)
				print_cast (buffer, arg_prec, ir->operands[2]);
			ir->operands[2]->accept(this);
		}
		buffer.asprintf_append (")");
	}

	if (rescast)
	{
		buffer.asprintf_append (")");
	}


	newline_deindent();
	--this->expression_depth;
}

static int tex_sampler_dim_size[] = {
	1, 2, 3, 3, 2, 2, 2,
};


static void print_texture_uv (ir_print_metal_visitor* vis, ir_texture* ir, bool is_shadow, bool is_proj, int uv_dim, int sampler_uv_dim)
{
	if (!is_shadow)
	{
		if (!is_proj)
		{
			// regular UV
			vis->buffer.asprintf_append (sampler_uv_dim == 3 ? "(float3)(" : "(float2)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (")");
		}
		else
		{
			// regular projected
			vis->buffer.asprintf_append (sampler_uv_dim == 3 ? "((float3)(" : "((float2)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (sampler_uv_dim == 3 ? ").xyz / (float)(" : ").xy / (float)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (uv_dim == 4 ? ").w)" : ").z)");
		}
	}
	else if (is_shadow)
	{
		if (!is_proj)
		{
			// regular shadow
			vis->buffer.asprintf_append (uv_dim == 4 ? "(float3)(" : "(float2)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (uv_dim == 4 ? ").xyz, (" : ").xy, (float)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (uv_dim == 4 ? ").w" : ").z");
		}
		else
		{
			// projected shadow
			vis->buffer.asprintf_append ("(float2)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (").xy / (float)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (").w, (float)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (").z / (float)(");
			ir->coordinate->accept(vis);
			vis->buffer.asprintf_append (").w");
		}
	}
}

void ir_print_metal_visitor::visit(ir_texture *ir)
{
	glsl_sampler_dim sampler_dim = (glsl_sampler_dim)ir->sampler->type->sampler_dimensionality;
	const bool is_shadow = ir->sampler->type->sampler_shadow;
	const glsl_type* uv_type = ir->coordinate->type;
	const int uv_dim = uv_type->vector_elements;
	int sampler_uv_dim = tex_sampler_dim_size[sampler_dim];
	if (is_shadow)
		sampler_uv_dim += 1;
	const bool is_proj = (uv_dim > sampler_uv_dim);

	// texture name & call to sample
	ir->sampler->accept(this);
	if (is_shadow)
	{
		// For shadow sampling, Metal right now needs a hardcoded sampler state :|
		if (!ctx.shadowSamplerDone)
		{
			ctx.prefixStr.asprintf_append("constexpr sampler _mtl_xl_shadow_sampler(address::clamp_to_edge, filter::linear, compare_func::less);\n");
			ctx.shadowSamplerDone = true;
		}
		buffer.asprintf_append (".sample_compare(_mtl_xl_shadow_sampler");
	}
	else
	{
		buffer.asprintf_append (".sample(_mtlsmp_");
		ir->sampler->accept(this);
	}
	buffer.asprintf_append (", ");

	// texture coordinate
	print_texture_uv (this, ir, is_shadow, is_proj, uv_dim, sampler_uv_dim);

	// lod bias
	if (ir->op == ir_txb)
	{
		buffer.asprintf_append (", bias(");
		ir->lod_info.bias->accept(this);
		buffer.asprintf_append (")");
	}

	// lod
	if (ir->op == ir_txl)
	{
		buffer.asprintf_append (", level(");
		ir->lod_info.lod->accept(this);
		buffer.asprintf_append (")");
	}

	// grad
	if (ir->op == ir_txd)
	{
		if (sampler_dim == GLSL_SAMPLER_DIM_CUBE)
			buffer.asprintf_append (", gradientcube((float3)(");
		else
			buffer.asprintf_append (", gradient2d((float2)(");

		ir->lod_info.grad.dPdx->accept(this);

		if (sampler_dim == GLSL_SAMPLER_DIM_CUBE)
			buffer.asprintf_append ("), (float3)(");
		else
			buffer.asprintf_append ("), (float2)(");

		ir->lod_info.grad.dPdy->accept(this);
		buffer.asprintf_append ("))");
	}

	//@TODO: texelFetch
	//@TODO: projected
	//@TODO: shadowmaps
	//@TODO: pixel offsets

	buffer.asprintf_append (")");
}


void ir_print_metal_visitor::visit(ir_swizzle *ir)
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
			print_type(buffer, ir, ir->type, true);
			buffer.asprintf_append ("(");
		}
	}

	ir->val->accept(this);

	if (ir->val->type == glsl_type::float_type || ir->val->type == glsl_type::int_type)
	{
		if (ir->mask.num_components != 1)
		{
			buffer.asprintf_append (")");
		}
		return;
	}

   buffer.asprintf_append (".");
   for (unsigned i = 0; i < ir->mask.num_components; i++) {
		buffer.asprintf_append ("%c", "xyzw"[swiz[i]]);
   }
}

static void print_var_inout (string_buffer& buf, ir_variable* var, bool insideLHS)
{
	if (var->data.mode == ir_var_shader_in)
		buf.asprintf_append ("_mtl_i.");
	if (var->data.mode == ir_var_shader_out)
		buf.asprintf_append ("_mtl_o.");
	if (var->data.mode == ir_var_uniform && !var->type->is_sampler())
		buf.asprintf_append ("_mtl_u.");
	if (var->data.mode == ir_var_shader_inout)
		buf.asprintf_append (insideLHS ? "_mtl_o." : "_mtl_i.");
}

void ir_print_metal_visitor::visit(ir_dereference_variable *ir)
{
	ir_variable *var = ir->variable_referenced();
	print_var_inout(buffer, var, this->inside_lhs);
	print_var_name (var);
}


void ir_print_metal_visitor::visit(ir_dereference_array *ir)
{
   ir->array->accept(this);
   buffer.asprintf_append ("[");
   ir->array_index->accept(this);
   buffer.asprintf_append ("]");
}


void ir_print_metal_visitor::visit(ir_dereference_record *ir)
{
   ir->record->accept(this);
   buffer.asprintf_append (".%s", ir->field);
}




void ir_print_metal_visitor::emit_assignment_part (ir_dereference* lhs, ir_rvalue* rhs, unsigned write_mask, ir_rvalue* dstIndex)
{
	const bool prev_lhs_flag = this->inside_lhs;
	this->inside_lhs = true;

	lhs->accept(this);

	this->inside_lhs = prev_lhs_flag;

	const glsl_type* lhsType = lhs->type;
	if (dstIndex)
	{
		// if dst index is a constant, then emit a swizzle
		ir_constant* dstConst = dstIndex->as_constant();
		if (dstConst)
		{
			const char* comps = "xyzw";
			char comp = comps[dstConst->get_int_component(0)];
			buffer.asprintf_append (".%c", comp);
		}
		else
		{
			buffer.asprintf_append ("[");
			dstIndex->accept(this);
			buffer.asprintf_append ("]");
		}

		if (lhsType->matrix_columns <= 1 && lhsType->vector_elements > 1)
			lhsType = glsl_type::get_instance(lhsType->base_type, 1, 1);
	}

	char mask[5];
	unsigned j = 0;
	const glsl_type* rhsType = rhs->type;
	if (!dstIndex && lhsType->matrix_columns <= 1 && lhsType->vector_elements > 1 && write_mask != (1<<lhsType->vector_elements)-1)
	{
		for (unsigned i = 0; i < 4; i++) {
			if ((write_mask & (1 << i)) != 0) {
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
		buffer.asprintf_append (".%s", mask);
		hasWriteMask = true;
	}

	buffer.asprintf_append (" = ");

	const bool typeMismatch = !dstIndex && (lhsType != rhsType);

	const bool precMismatch = is_different_precision (lhs->get_precision(), rhs->get_precision());
	const bool addSwizzle = hasWriteMask && typeMismatch;
	if (typeMismatch || precMismatch)
	{
		if (!addSwizzle)
		{
			if (lhsType->is_matrix())
			{
				// Metal does not have matrix precision casts right now, so emit workaround
				// functions that would do that.
				if (!ctx.matrixCastsDone)
				{
					ctx.prefixStr.asprintf_append(
												  "inline float4x4 _xlcast_float4x4(half4x4 v) { return float4x4(float4(v[0]), float4(v[1]), float4(v[2]), float4(v[3])); }\n"
												  "inline float3x3 _xlcast_float3x3(half3x3 v) { return float3x3(float3(v[0]), float3(v[1]), float3(v[2])); }\n"
												  "inline float2x2 _xlcast_float2x2(half2x2 v) { return float2x2(float2(v[0]), float2(v[1])); }\n"
												  "inline half4x4 _xlcast_half4x4(float4x4 v) { return half4x4(half4(v[0]), half4(v[1]), half4(v[2]), half4(v[3])); }\n"
												  "inline half3x3 _xlcast_half3x3(float3x3 v) { return half3x3(half3(v[0]), half3(v[1]), half3(v[2])); }\n"
												  "inline half2x2 _xlcast_half2x2(float2x2 v) { return half2x2(half2(v[0]), half2(v[1])); }\n"
												  );
					ctx.matrixCastsDone = true;
				}
				buffer.asprintf_append ("_xlcast_");
			}
			print_type(buffer, lhs, lhsType, true);
		}
		buffer.asprintf_append ("(");
	}

	rhs->accept(this);

	if (typeMismatch || precMismatch)
	{
		buffer.asprintf_append (")");
		if (addSwizzle)
			buffer.asprintf_append (".%s", mask);
	}
}


// Try to print (X = X + const) as (X += const), mostly to satisfy
// OpenGL ES 2.0 loop syntax restrictions.
static bool try_print_increment (ir_print_metal_visitor* vis, ir_assignment* ir)
{
	if (ir->condition)
		return false;

	// Needs to be + on rhs
	ir_expression* rhsOp = ir->rhs->as_expression();
	if (!rhsOp || rhsOp->operation != ir_binop_add)
		return false;

	// Needs to write to whole variable
	ir_variable* lhsVar = ir->whole_variable_written();
	if (lhsVar == NULL)
		return false;

	// Types must match
	if (ir->lhs->type != ir->rhs->type)
		return false;

	// Type must be scalar
	if (!ir->lhs->type->is_scalar())
		return false;

	// rhs0 must be variable deref, same one as lhs
	ir_dereference_variable* rhsDeref = rhsOp->operands[0]->as_dereference_variable();
	if (rhsDeref == NULL)
		return false;
	if (lhsVar != rhsDeref->var)
		return false;

	// rhs1 must be a constant
	ir_constant* rhsConst = rhsOp->operands[1]->as_constant();
	if (!rhsConst)
		return false;

	// print variable name
	const bool prev_lhs_flag = vis->inside_lhs;
	vis->inside_lhs = true;

	ir->lhs->accept (vis);

	vis->inside_lhs = prev_lhs_flag;


	// print ++ or +=const
	if (ir->lhs->type->base_type <= GLSL_TYPE_INT && rhsConst->is_one())
	{
		vis->buffer.asprintf_append ("++");
	}
	else
	{
		vis->buffer.asprintf_append(" += ");
		rhsConst->accept (vis);
	}

	return true;
}


void ir_print_metal_visitor::visit(ir_assignment *ir)
{
	// if this is a loop induction variable initial assignment, and we aren't inside loop body:
	// do not print it (will be printed when inside loop body)
	if (!inside_loop_body)
	{
		ir_variable* whole_var = ir->whole_variable_written();
		if (!ir->condition && whole_var)
		{
			loop_variable_state* inductor_state = loopstate->get_for_inductor(whole_var);
			if (inductor_state && inductor_state->private_induction_variable_count == 1 &&
				can_emit_canonical_for(inductor_state))
			{
				skipped_this_ir = true;
				return;
			}
		}
	}

	// assignments in global scope are postponed to main function
	if (this->mode != kPrintGlslNone)
	{
		assert (!this->globals->main_function_done);
		this->globals->global_assignements.push_tail (new(this->globals->mem_ctx) ga_entry_metal(ir));
		buffer.asprintf_append ("//"); // for the ; that will follow (ugly, I know)
		return;
	}

	// if RHS is ir_triop_vector_insert, then we have to do some special dance. If source expression is:
	//   dst = vector_insert (a, b, idx)
	// then emit it like:
	//   dst = a;
	//   dst.idx = b;
	ir_expression* rhsOp = ir->rhs->as_expression();
	if (rhsOp && rhsOp->operation == ir_triop_vector_insert)
	{
		// skip assignment if lhs and rhs would be the same
		bool skip_assign = false;
		ir_dereference_variable* lhsDeref = ir->lhs->as_dereference_variable();
		ir_dereference_variable* rhsDeref = rhsOp->operands[0]->as_dereference_variable();
		if (lhsDeref && rhsDeref)
		{
			if (lhsDeref->var == rhsDeref->var)
				skip_assign = true;
		}

		if (!skip_assign)
		{
			emit_assignment_part(ir->lhs, rhsOp->operands[0], ir->write_mask, NULL);
			buffer.asprintf_append ("; ");
		}
		emit_assignment_part(ir->lhs, rhsOp->operands[1], ir->write_mask, rhsOp->operands[2]);
		return;
	}

	if (try_print_increment (this, ir))
		return;

	if (ir->condition)
	{
	  ir->condition->accept(this);
	  buffer.asprintf_append (" ");
	}

	emit_assignment_part (ir->lhs, ir->rhs, ir->write_mask, NULL);
}

void ir_print_metal_visitor::visit(ir_constant *ir)
{
	const glsl_type* type = ir->type;

	// hoist array & struct constants into global scope
	if (type->is_array() || type->is_record())
	{
		size_t id = (size_t)hash_table_find(globals->const_hash, ir);
		if (id == 0)
		{
			id = ++globals->const_counter;
			hash_table_insert (globals->const_hash, (void*)id, ir);
			globals->global_constants.push_tail(new(globals->mem_ctx) gconst_entry_metal(ir,id));
		}
		buffer.asprintf_append("_xlat_mtl_const%i", (int)id);
		return;
	}

	if (type == glsl_type::float_type)
	{
		print_float (buffer, ir->value.f[0]);
		return;
	}
	else if (type == glsl_type::int_type)
	{
		buffer.asprintf_append ("%d", ir->value.i[0]);
		return;
	}
	else if (type == glsl_type::uint_type)
	{
		buffer.asprintf_append ("%u", ir->value.u[0]);
		return;
	}

   const glsl_type *const base_type = ir->type->get_base_type();

   print_type(buffer, ir, type, true);
   buffer.asprintf_append ("(");

	// should be dealt with above
	assert(!ir->type->is_array());
	assert(!ir->type->is_record());
	bool first = true;

	// Metal needs matrices to be constructed from vectors, not from a bunch of scalars.
	// So instead of printing mat2(1,2,3,4) like in glsl, we have to print float2x2(float2(1,2), float2(3,4))
	// here.
	const bool mtx = ir->type->is_matrix();
	const glsl_type* vec_type = NULL; // matrix column type
	if (mtx)
		vec_type = glsl_type::get_instance (ir->type->base_type, ir->type->vector_elements, 1);

	for (unsigned i = 0; i < ir->type->components(); i++)
	{
		if (!first)
		{
			if (mtx && (i % ir->type->matrix_columns == 0))
				buffer.asprintf_append (")");
			buffer.asprintf_append (", ");
		}
		first = false;

		if (mtx && (i % ir->type->matrix_columns == 0))
		{
			print_type(buffer, ir, vec_type, true);
			buffer.asprintf_append ("(");
		}

		switch (base_type->base_type) {
		case GLSL_TYPE_UINT:  buffer.asprintf_append ("%u", ir->value.u[i]); break;
		case GLSL_TYPE_INT:   buffer.asprintf_append ("%d", ir->value.i[i]); break;
		case GLSL_TYPE_FLOAT: print_float(buffer, ir->value.f[i]); break;
		case GLSL_TYPE_BOOL:  buffer.asprintf_append ("%d", ir->value.b[i]); break;
		default: assert(0);
		}
	}
	if (mtx)
		buffer.asprintf_append (")");
	buffer.asprintf_append (")");
}


void
ir_print_metal_visitor::visit(ir_call *ir)
{
	// calls in global scope are postponed to main function
	if (this->mode != kPrintGlslNone)
	{
		assert (!this->globals->main_function_done);
		this->globals->global_assignements.push_tail (new(this->globals->mem_ctx) ga_entry_metal(ir));
		buffer.asprintf_append ("//"); // for the ; that will follow (ugly, I know)
		return;
	}

	if (ir->return_deref)
	{
		visit(ir->return_deref);
		buffer.asprintf_append (" = ");
	}

   buffer.asprintf_append ("%s (", ir->callee_name());
   bool first = true;
   foreach_in_list(ir_instruction, inst, &ir->actual_parameters) {
	  if (!first)
		  buffer.asprintf_append (", ");
      inst->accept(this);
	  first = false;
   }
   buffer.asprintf_append (")");
}


void
ir_print_metal_visitor::visit(ir_return *ir)
{
   buffer.asprintf_append ("return");

   ir_rvalue *const value = ir->get_value();
   if (value) {
      buffer.asprintf_append (" ");
      value->accept(this);
   }
}


void
ir_print_metal_visitor::visit(ir_discard *ir)
{
   buffer.asprintf_append ("discard_fragment()");

   if (ir->condition != NULL) {
      buffer.asprintf_append (" TODO ");
      ir->condition->accept(this);
   }
}


void
ir_print_metal_visitor::visit(ir_if *ir)
{
   buffer.asprintf_append ("if (");
   ir->condition->accept(this);

   buffer.asprintf_append (") {\n");
	indentation++; previous_skipped = false;


   foreach_in_list(ir_instruction, inst, &ir->then_instructions) {
      indent();
      inst->accept(this);
	   end_statement_line();
   }

   indentation--;
   indent();
   buffer.asprintf_append ("}");

   if (!ir->else_instructions.is_empty())
   {
	   buffer.asprintf_append (" else {\n");
	   indentation++; previous_skipped = false;

	   foreach_in_list(ir_instruction, inst, &ir->else_instructions) {
		  indent();
		  inst->accept(this);
		   end_statement_line();
	   }
	   indentation--;
	   indent();
	   buffer.asprintf_append ("}");
   }
}


bool ir_print_metal_visitor::can_emit_canonical_for (loop_variable_state *ls)
{
	if (ls == NULL)
		return false;

	if (ls->induction_variables.is_empty())
		return false;

	if (ls->terminators.is_empty())
		return false;

	// only support for loops with one terminator condition
	int terminatorCount = ls->terminators.length();
	if (terminatorCount != 1)
		return false;

	return true;
}

bool ir_print_metal_visitor::emit_canonical_for (ir_loop* ir)
{
	loop_variable_state* const ls = this->loopstate->get(ir);

	if (!can_emit_canonical_for(ls))
		return false;

	hash_table* terminator_hash = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);
	hash_table* induction_hash = hash_table_ctor(0, hash_table_pointer_hash, hash_table_pointer_compare);

	buffer.asprintf_append("for (");
	inside_loop_body = true;

	// emit loop induction variable declarations.
	// only for loops with single induction variable, to avoid cases of different types of them
	if (ls->private_induction_variable_count == 1)
	{
		foreach_in_list(loop_variable, indvar, &ls->induction_variables)
		{
			if (!this->loopstate->get_for_inductor(indvar->var))
				continue;

			ir_variable* var = indvar->var;
			print_type(buffer, var, var->type, false);
			buffer.asprintf_append (" ");
			print_var_inout(buffer, var, true);
			print_var_name (var);
			print_type_post(buffer, var->type, false);
			if (indvar->initial_value)
			{
				buffer.asprintf_append (" = ");
				indvar->initial_value->accept(this);
			}
		}
	}
	buffer.asprintf_append("; ");

	// emit loop terminating conditions
	foreach_in_list(loop_terminator, term, &ls->terminators)
	{
		hash_table_insert(terminator_hash, term, term->ir);

		// IR has conditions in the form of "if (x) break",
		// whereas for loop needs them negated, in the form
		// if "while (x) continue the loop".
		// See if we can print them using syntax that reads nice.
		bool handled = false;
		ir_expression* term_expr = term->ir->condition->as_expression();
		if (term_expr)
		{
			// Binary comparison conditions
			const char* termOp = NULL;
			switch (term_expr->operation)
			{
				case ir_binop_less: termOp = ">="; break;
				case ir_binop_greater: termOp = "<="; break;
				case ir_binop_lequal: termOp = ">"; break;
				case ir_binop_gequal: termOp = "<"; break;
				case ir_binop_equal: termOp = "!="; break;
				case ir_binop_nequal: termOp = "=="; break;
				default: break;
			}
			if (termOp != NULL)
			{
				term_expr->operands[0]->accept(this);
				buffer.asprintf_append(" %s ", termOp);
				term_expr->operands[1]->accept(this);
				handled = true;
			}

			// Unary logic not
			if (!handled && term_expr->operation == ir_unop_logic_not)
			{
				term_expr->operands[0]->accept(this);
				handled = true;
			}
		}

		// More complex condition, print as "!(x)"
		if (!handled)
		{
			buffer.asprintf_append("!(");
			term->ir->condition->accept(this);
			buffer.asprintf_append(")");
		}
	}
	buffer.asprintf_append("; ");

	// emit loop induction variable updates
	bool first = true;
	foreach_in_list(loop_variable, indvar, &ls->induction_variables)
	{
		hash_table_insert(induction_hash, indvar, indvar->first_assignment);
		if (!first)
			buffer.asprintf_append(", ");
		visit(indvar->first_assignment);
		first = false;
	}
	buffer.asprintf_append(") {\n");

	inside_loop_body = false;

	// emit loop body
	indentation++; previous_skipped = false;
	foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
		// skip termination & induction statements,
		// they are part of "for" clause
		if (hash_table_find(terminator_hash, inst))
			continue;
		if (hash_table_find(induction_hash, inst))
			continue;

		indent();
		inst->accept(this);
		end_statement_line();
	}
	indentation--;

	indent();
	buffer.asprintf_append("}");

	hash_table_dtor (terminator_hash);
	hash_table_dtor (induction_hash);

	return true;
}


void
ir_print_metal_visitor::visit(ir_loop *ir)
{
	if (emit_canonical_for(ir))
		return;

	buffer.asprintf_append ("while (true) {\n");
	indentation++; previous_skipped = false;
	foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
		indent();
		inst->accept(this);
		end_statement_line();
	}
	indentation--;
	indent();
	buffer.asprintf_append ("}");
}


void
ir_print_metal_visitor::visit(ir_loop_jump *ir)
{
   buffer.asprintf_append ("%s", ir->is_break() ? "break" : "continue");
}

void
ir_print_metal_visitor::visit(ir_precision_statement *ir)
{
}

void
ir_print_metal_visitor::visit(ir_typedecl_statement *ir)
{
	const glsl_type *const s = ir->type_decl;
	buffer.asprintf_append ("struct %s {\n", s->name);

	for (unsigned j = 0; j < s->length; j++) {
		buffer.asprintf_append ("  ");
		//if (state->es_shader)
		//	buffer.asprintf_append ("%s", get_precision_string(s->fields.structure[j].precision)); //@TODO
		print_type(buffer, ir, s->fields.structure[j].type, false);
		buffer.asprintf_append (" %s", s->fields.structure[j].name);
		print_type_post(buffer, s->fields.structure[j].type, false);
		buffer.asprintf_append (";\n");
	}
	buffer.asprintf_append ("}");
}

void
ir_print_metal_visitor::visit(ir_emit_vertex *ir)
{
	buffer.asprintf_append ("emit-vertex-TODO");
}

void
ir_print_metal_visitor::visit(ir_end_primitive *ir)
{
	buffer.asprintf_append ("end-primitive-TODO");
}

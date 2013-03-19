#include "glsl_optimizer.h"
#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_parser.h"
#include "ir_optimization.h"
#include "ir_print_glsl_visitor.h"
#include "ir_print_visitor.h"
#include "loop_analysis.h"
#include "program.h"
#include "linker.h"


extern "C" struct gl_shader *
_mesa_new_shader(struct gl_context *ctx, GLuint name, GLenum type);


static void
initialize_mesa_context(struct gl_context *ctx, gl_api api)
{
   memset(ctx, 0, sizeof(*ctx));

   ctx->API = api;

   ctx->Extensions.ARB_fragment_coord_conventions = GL_TRUE;
   ctx->Extensions.EXT_texture_array = GL_TRUE;
   ctx->Extensions.NV_texture_rectangle = GL_TRUE;
   ctx->Extensions.ARB_shader_texture_lod = GL_TRUE;

   // Enable opengl es extensions we care about here
   if (api == API_OPENGLES2)
   {
	   ctx->Extensions.OES_standard_derivatives = GL_TRUE;
	   ctx->Extensions.EXT_shadow_samplers = GL_TRUE;
	   ctx->Extensions.EXT_frag_depth = GL_TRUE;
   }

   ctx->Const.GLSLVersion = 140;

   /* 1.20 minimums. */
   ctx->Const.MaxLights = 8;
   ctx->Const.MaxClipPlanes = 8;
   ctx->Const.MaxTextureUnits = 2;

   /* allow high amount */
   ctx->Const.MaxTextureCoordUnits = 16;

   ctx->Const.VertexProgram.MaxAttribs = 16;
   ctx->Const.VertexProgram.MaxUniformComponents = 512;
   ctx->Const.MaxVarying = 8;
   ctx->Const.MaxVertexTextureImageUnits = 0;
   ctx->Const.MaxCombinedTextureImageUnits = 2;
   ctx->Const.MaxTextureImageUnits = 2;
   ctx->Const.FragmentProgram.MaxUniformComponents = 64;

   ctx->Const.MaxDrawBuffers = 2;

   ctx->Driver.NewShader = _mesa_new_shader;
}


struct glslopt_ctx {
	glslopt_ctx (bool openglES) {
		mem_ctx = ralloc_context (NULL);
		initialize_mesa_context (&mesa_ctx, openglES ? API_OPENGLES2 : API_OPENGL);
	}
	~glslopt_ctx() {
		ralloc_free (mem_ctx);
	}
	struct gl_context mesa_ctx;
	void* mem_ctx;
};

glslopt_ctx* glslopt_initialize (bool openglES)
{
	return new glslopt_ctx(openglES);
}

void glslopt_cleanup (glslopt_ctx* ctx)
{
	delete ctx;
	_mesa_glsl_release_types();
	_mesa_glsl_release_functions();
}


struct glslopt_shader
{
	static void* operator new(size_t size, void *ctx)
	{
		void *node;
		node = ralloc_size(ctx, size);
		assert(node != NULL);
		return node;
	}
	static void operator delete(void *node)
	{
		ralloc_free(node);
	}

	glslopt_shader ()
		: rawOutput(0)
		, optimizedOutput(0)
		, status(false)
	{
		infoLog = "Shader not compiled yet";
		
		whole_program = rzalloc (NULL, struct gl_shader_program);
		assert(whole_program != NULL);
		whole_program->InfoLog = ralloc_strdup(whole_program, "");
		
		whole_program->Shaders = reralloc(whole_program, whole_program->Shaders, struct gl_shader *, whole_program->NumShaders + 1);
		assert(whole_program->Shaders != NULL);
		
		shader = rzalloc(whole_program, gl_shader);
		whole_program->Shaders[whole_program->NumShaders] = shader;
		whole_program->NumShaders++;
	}
	
	~glslopt_shader()
	{
		for (unsigned i = 0; i < MESA_SHADER_TYPES; i++)
			ralloc_free(whole_program->_LinkedShaders[i]);
		ralloc_free(whole_program);
	}
	
	struct gl_shader_program* whole_program;
	struct gl_shader* shader;

	char*	rawOutput;
	char*	optimizedOutput;
	const char*	infoLog;
	bool	status;
};

static inline void debug_print_ir (const char* name, exec_list* ir, _mesa_glsl_parse_state* state, void* memctx)
{
	#if 0
	printf("**** %s:\n", name);
	//_mesa_print_ir (ir, state);
	char* foobar = _mesa_print_ir_glsl(ir, state, ralloc_strdup(memctx, ""), kPrintGlslFragment);
	printf("%s\n", foobar);
	validate_ir_tree(ir);
	#endif
}

static void propagate_precision_deref(ir_instruction *ir, void *data)
{
	// variable -> deference
	ir_dereference_variable* der = ir->as_dereference_variable();
	if (der && der->get_precision() == glsl_precision_undefined && der->var->precision != glsl_precision_undefined)
	{
		der->set_precision ((glsl_precision)der->var->precision);
		*(bool*)data = true;
	}
	// swizzle value -> swizzle
	ir_swizzle* swz = ir->as_swizzle();
	if (swz && swz->get_precision() == glsl_precision_undefined && swz->val->get_precision() != glsl_precision_undefined)
	{
		swz->set_precision (swz->val->get_precision());
		*(bool*)data = true;
	}
	
}

static void propagate_precision_expr(ir_instruction *ir, void *data)
{
	ir_expression* expr = ir->as_expression();
	if (!expr)
		return;
	if (expr->get_precision() != glsl_precision_undefined)
		return;
	
	glsl_precision prec_params_max = glsl_precision_undefined;
	for (int i = 0; i < (int)expr->get_num_operands(); ++i)
	{
		ir_rvalue* op = expr->operands[i];
		if (op && op->get_precision() != glsl_precision_undefined)
			prec_params_max = higher_precision (prec_params_max, op->get_precision());
	}
	if (expr->get_precision() != prec_params_max)
	{
		expr->set_precision (prec_params_max);
		*(bool*)data = true;
	}
	
}


static void propagate_precision_assign(ir_instruction *ir, void *data)
{
	ir_assignment* ass = ir->as_assignment();
	if (ass && ass->lhs && ass->rhs)
	{
		glsl_precision lp = ass->lhs->get_precision();
		glsl_precision rp = ass->rhs->get_precision();
		if (rp == glsl_precision_undefined)
			return;
		ir_variable* lhs_var = ass->lhs->variable_referenced();
		if (lp == glsl_precision_undefined)
		{		
			if (lhs_var)
				lhs_var->precision = rp;
			ass->lhs->set_precision (rp);
			*(bool*)data = true;
		}
	}
}

static void propagate_precision_call(ir_instruction *ir, void *data)
{
	ir_call* call = ir->as_call();
	if (!call)
		return;
	if (!call->return_deref)
		return;
	if (call->return_deref->get_precision() == glsl_precision_undefined /*&& call->callee->precision == glsl_precision_undefined*/)
	{
		glsl_precision prec_params_max = glsl_precision_undefined;
		exec_list_iterator iter_sig  = call->callee->parameters.iterator();
		foreach_iter(exec_list_iterator, iter_param, call->actual_parameters)
		{
			ir_variable* sig_param = (ir_variable*)iter_sig.get();
			ir_rvalue* param = (ir_rvalue*)iter_param.get();
			
			glsl_precision p = (glsl_precision)sig_param->precision;
			if (p == glsl_precision_undefined)
				p = param->get_precision();
			
			prec_params_max = higher_precision (prec_params_max, p);
			
			iter_sig.next();
		}
		if (call->return_deref->get_precision() != prec_params_max)
		{
			call->return_deref->set_precision (prec_params_max);
			*(bool*)data = true;
		}
	}
}


static bool propagate_precision(exec_list* list)
{
	bool anyProgress = false;
	bool res;
	do {
		res = false;
		foreach_iter(exec_list_iterator, iter, *list) {
			ir_instruction* ir = (ir_instruction*)iter.get();
			visit_tree (ir, propagate_precision_deref, &res);
			visit_tree (ir, propagate_precision_assign, &res);
			visit_tree (ir, propagate_precision_call, &res);
			visit_tree (ir, propagate_precision_expr, &res);
		}
		anyProgress |= res;
	} while (res);
	return anyProgress;
}


static void do_optimization_passes(exec_list* ir, bool linked, _mesa_glsl_parse_state* state, glslopt_ctx* ctx)
{
	bool progress;
	do {
		progress = false;
		bool progress2;
		debug_print_ir ("Initial", ir, state, ctx->mem_ctx);
		if (linked) {
			progress2 = do_function_inlining(ir); progress |= progress2; if (progress2) debug_print_ir ("After inlining", ir, state, ctx->mem_ctx);
			progress2 = do_dead_functions(ir); progress |= progress2; if (progress2) debug_print_ir ("After dead functions", ir, state, ctx->mem_ctx);
			progress2 = do_structure_splitting(ir); progress |= progress2; if (progress2) debug_print_ir ("After struct splitting", ir, state, ctx->mem_ctx);
		}
		progress2 = do_if_simplification(ir); progress |= progress2; if (progress2) debug_print_ir ("After if simpl", ir, state, ctx->mem_ctx);
		progress2 = propagate_precision (ir); progress |= progress2; if (progress2) debug_print_ir ("After prec propagation", ir, state, ctx->mem_ctx);
		progress2 = do_copy_propagation(ir); progress |= progress2; if (progress2) debug_print_ir ("After copy propagation", ir, state, ctx->mem_ctx);
		progress2 = do_copy_propagation_elements(ir); progress |= progress2; if (progress2) debug_print_ir ("After copy propagation elems", ir, state, ctx->mem_ctx);
		if (linked) {
			progress2 = do_dead_code(ir,false); progress |= progress2; if (progress2) debug_print_ir ("After dead code", ir, state, ctx->mem_ctx);
		} else {
			progress2 = do_dead_code_unlinked(ir); progress |= progress2; if (progress2) debug_print_ir ("After dead code unlinked", ir, state, ctx->mem_ctx);
		}
		progress2 = do_dead_code_local(ir); progress |= progress2; if (progress2) debug_print_ir ("After dead code local", ir, state, ctx->mem_ctx);
		progress2 = propagate_precision (ir); progress |= progress2; if (progress2) debug_print_ir ("After prec propagation", ir, state, ctx->mem_ctx);
		progress2 = do_tree_grafting(ir); progress |= progress2; if (progress2) debug_print_ir ("After tree grafting", ir, state, ctx->mem_ctx);
		progress2 = do_constant_propagation(ir); progress |= progress2; if (progress2) debug_print_ir ("After const propagation", ir, state, ctx->mem_ctx);
		if (linked) {
			progress2 = do_constant_variable(ir); progress |= progress2; if (progress2) debug_print_ir ("After const variable", ir, state, ctx->mem_ctx);
		} else {
			progress2 = do_constant_variable_unlinked(ir); progress |= progress2; if (progress2) debug_print_ir ("After const variable unlinked", ir, state, ctx->mem_ctx);
		}
		progress2 = do_constant_folding(ir); progress |= progress2; if (progress2) debug_print_ir ("After const folding", ir, state, ctx->mem_ctx);
		progress2 = do_algebraic(ir); progress |= progress2; if (progress2) debug_print_ir ("After algebraic", ir, state, ctx->mem_ctx);
		progress2 = do_lower_jumps(ir); progress |= progress2; if (progress2) debug_print_ir ("After lower jumps", ir, state, ctx->mem_ctx);
		progress2 = do_vec_index_to_swizzle(ir); progress |= progress2; if (progress2) debug_print_ir ("After vec index to swizzle", ir, state, ctx->mem_ctx);
		//progress2 = do_vec_index_to_cond_assign(ir); progress |= progress2; if (progress2) debug_print_ir ("After vec index to cond assign", ir, state, ctx->mem_ctx);
		progress2 = do_swizzle_swizzle(ir); progress |= progress2; if (progress2) debug_print_ir ("After swizzle swizzle", ir, state, ctx->mem_ctx);
		progress2 = do_noop_swizzle(ir); progress |= progress2; if (progress2) debug_print_ir ("After noop swizzle", ir, state, ctx->mem_ctx);
		progress2 = optimize_split_arrays(ir, linked); progress |= progress2; if (progress2) debug_print_ir ("After split arrays", ir, state, ctx->mem_ctx);
		progress2 = optimize_redundant_jumps(ir); progress |= progress2; if (progress2) debug_print_ir ("After redundant jumps", ir, state, ctx->mem_ctx);
		
		// do loop stuff only when linked; otherwise causes duplicate loop induction variable
		// problems (ast-in.txt test)
		if (linked)
		{
			loop_state *ls = analyze_loop_variables(ir);
			if (ls->loop_found) {
				progress2 = set_loop_controls(ir, ls); progress |= progress2; if (progress2) debug_print_ir ("After set loop", ir, state, ctx->mem_ctx);
				progress2 = unroll_loops(ir, ls, 8); progress |= progress2; if (progress2) debug_print_ir ("After unroll", ir, state, ctx->mem_ctx);
			}
			delete ls;
		}
	} while (progress);
}


glslopt_shader* glslopt_optimize (glslopt_ctx* ctx, glslopt_shader_type type, const char* shaderSource, unsigned options)
{
	glslopt_shader* shader = new (ctx->mem_ctx) glslopt_shader ();

	PrintGlslMode printMode = kPrintGlslVertex;
	switch (type) {
	case kGlslOptShaderVertex: shader->shader->Type = GL_VERTEX_SHADER; printMode = kPrintGlslVertex; break;
	case kGlslOptShaderFragment: shader->shader->Type = GL_FRAGMENT_SHADER; printMode = kPrintGlslFragment; break;
	}
	if (!shader->shader->Type)
	{
		shader->infoLog = ralloc_asprintf (ctx->mem_ctx, "Unknown shader type %d", (int)type);
		shader->status = false;
		return shader;
	}
	
	_mesa_glsl_parse_state* state = new (ctx->mem_ctx) _mesa_glsl_parse_state (&ctx->mesa_ctx, shader->shader->Type, ctx->mem_ctx);
	state->error = 0;

	if (!(options & kGlslOptionSkipPreprocessor))
	{
		state->error = !!glcpp_preprocess (state, &shaderSource, &state->info_log, state->extensions, ctx->mesa_ctx.API);
		if (state->error)
		{
			shader->status = !state->error;
			shader->infoLog = state->info_log;
			return shader;
		}
	}

	_mesa_glsl_lexer_ctor (state, shaderSource);
	_mesa_glsl_parse (state);
	_mesa_glsl_lexer_dtor (state);

	exec_list* ir = new (ctx->mem_ctx) exec_list();
	shader->shader->ir = ir;

	if (!state->error && !state->translation_unit.is_empty())
		_mesa_ast_to_hir (ir, state);

	// Un-optimized output
	if (!state->error) {
		validate_ir_tree(ir);
		shader->rawOutput = _mesa_print_ir_glsl(ir, state, ralloc_strdup(ctx->mem_ctx, ""), printMode);
	}
	
	// Link built-in functions
	shader->shader->symbols = state->symbols;
	memcpy(shader->shader->builtins_to_link, state->builtins_to_link, sizeof(shader->shader->builtins_to_link[0]) * state->num_builtins_to_link);
	shader->shader->num_builtins_to_link = state->num_builtins_to_link;
	
	struct gl_shader* linked_shader = 0;

	if (!state->error && !ir->is_empty())
	{
		linked_shader = link_intrastage_shaders(ctx->mem_ctx,
												&ctx->mesa_ctx,
												shader->whole_program,
												shader->whole_program->Shaders,
												shader->whole_program->NumShaders);
		if (!linked_shader)
		{
			shader->status = false;
			shader->infoLog = shader->whole_program->InfoLog;
			return shader;
		}
		ir = linked_shader->ir;
		
		debug_print_ir ("==== After link ====", ir, state, ctx->mem_ctx);
	}
	
	// Do optimization post-link
	if (!state->error && !ir->is_empty())
	{		
		const bool linked = !(options & kGlslOptionNotFullShader);
		do_optimization_passes(ir, linked, state, ctx);
		validate_ir_tree(ir);
	}	
	
	// Final optimized output
	if (!state->error)
	{
		shader->optimizedOutput = _mesa_print_ir_glsl(ir, state, ralloc_strdup(ctx->mem_ctx, ""), printMode);
	}

	shader->status = !state->error;
	shader->infoLog = state->info_log;

	ralloc_free (ir);
	ralloc_free (state);

	if (linked_shader)
		ralloc_free(linked_shader);

	return shader;
}

void glslopt_shader_delete (glslopt_shader* shader)
{
	delete shader;
}

bool glslopt_get_status (glslopt_shader* shader)
{
	return shader->status;
}

const char* glslopt_get_output (glslopt_shader* shader)
{
	return shader->optimizedOutput;
}

const char* glslopt_get_raw_output (glslopt_shader* shader)
{
	return shader->rawOutput;
}

const char* glslopt_get_log (glslopt_shader* shader)
{
	return shader->infoLog;
}

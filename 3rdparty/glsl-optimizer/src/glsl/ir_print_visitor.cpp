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

#include "ir_print_visitor.h"
#include "glsl_types.h"
#include "glsl_parser_extras.h"
#include "main/macros.h"
#include "program/hash_table.h"

static void print_type(FILE *f, const glsl_type *t);

void
ir_instruction::print(void) const
{
   this->fprint(stdout);
}

void
ir_instruction::fprint(FILE *f) const
{
   ir_instruction *deconsted = const_cast<ir_instruction *>(this);

   ir_print_visitor v(f);
   deconsted->accept(&v);
}

extern "C" {
void
_mesa_print_ir(FILE *f, exec_list *instructions,
	       struct _mesa_glsl_parse_state *state)
{
   if (state) {
      for (unsigned i = 0; i < state->num_user_structures; i++) {
	 const glsl_type *const s = state->user_structures[i];

	 fprintf(f, "(structure (%s) (%s@%p) (%u) (\n",
                 s->name, s->name, (void *) s, s->length);

	 for (unsigned j = 0; j < s->length; j++) {
	    fprintf(f, "\t((");
	    print_type(f, s->fields.structure[j].type);
	    fprintf(f, ")(%s))\n", s->fields.structure[j].name);
	 }

	 fprintf(f, ")\n");
      }
   }

   fprintf(f, "(\n");
   foreach_in_list(ir_instruction, ir, instructions) {
      ir->fprint(f);
      if (ir->ir_type != ir_type_function)
	 fprintf(f, "\n");
   }
   fprintf(f, "\n)");
}

void
fprint_ir(FILE *f, const void *instruction)
{
   const ir_instruction *ir = (const ir_instruction *)instruction;
   ir->fprint(f);
}

} /* extern "C" */

ir_print_visitor::ir_print_visitor(FILE *f)
   : f(f)
{
   indentation = 0;
   printable_names =
      hash_table_ctor(32, hash_table_pointer_hash, hash_table_pointer_compare);
   symbols = _mesa_symbol_table_ctor();
   mem_ctx = ralloc_context(NULL);
}

ir_print_visitor::~ir_print_visitor()
{
   hash_table_dtor(printable_names);
   _mesa_symbol_table_dtor(symbols);
   ralloc_free(mem_ctx);
}

void ir_print_visitor::indent(void)
{
   for (int i = 0; i < indentation; i++)
      fprintf(f, "  ");
}

const char *
ir_print_visitor::unique_name(ir_variable *var)
{
   /* var->name can be NULL in function prototypes when a type is given for a
    * parameter but no name is given.  In that case, just return an empty
    * string.  Don't worry about tracking the generated name in the printable
    * names hash because this is the only scope where it can ever appear.
    */
   if (var->name == NULL) {
      static unsigned arg = 1;
      return ralloc_asprintf(this->mem_ctx, "parameter@%u", arg++);
   }

   /* Do we already have a name for this variable? */
   const char *name = (const char *) hash_table_find(this->printable_names, var);
   if (name != NULL)
      return name;

   /* If there's no conflict, just use the original name */
   if (_mesa_symbol_table_find_symbol(this->symbols, -1, var->name) == NULL) {
      name = var->name;
   } else {
      static unsigned i = 1;
      name = ralloc_asprintf(this->mem_ctx, "%s@%u", var->name, ++i);
   }
   hash_table_insert(this->printable_names, (void *) name, var);
   _mesa_symbol_table_add_symbol(this->symbols, -1, name, var);
   return name;
}

static void
print_type(FILE *f, const glsl_type *t)
{
   if (t->base_type == GLSL_TYPE_ARRAY) {
      fprintf(f, "(array ");
      print_type(f, t->fields.array);
      fprintf(f, " %u)", t->length);
   } else if ((t->base_type == GLSL_TYPE_STRUCT)
              && !is_gl_identifier(t->name)) {
      fprintf(f, "%s@%p", t->name, (void *) t);
   } else {
      fprintf(f, "%s", t->name);
   }
}

void ir_print_visitor::visit(ir_rvalue *)
{
   fprintf(f, "error");
}

void ir_print_visitor::visit(ir_variable *ir)
{
   fprintf(f, "(declare ");

   const char *const cent = (ir->data.centroid) ? "centroid " : "";
   const char *const samp = (ir->data.sample) ? "sample " : "";
   const char *const inv = (ir->data.invariant) ? "invariant " : "";
   const char *const mode[] = { "", "uniform ", "shader_in ", "shader_out ", "shader_inout ",
                                "in ", "out ", "inout ",
			        "const_in ", "sys ", "temporary " };
   STATIC_ASSERT(ARRAY_SIZE(mode) == ir_var_mode_count);
   const char *const stream [] = {"", "stream1 ", "stream2 ", "stream3 "};
   const char *const interp[] = { "", "smooth", "flat", "noperspective" };
   STATIC_ASSERT(ARRAY_SIZE(interp) == INTERP_QUALIFIER_COUNT);

   fprintf(f, "(%s%s%s%s%s%s) ",
           cent, samp, inv, mode[ir->data.mode],
           stream[ir->data.stream],
           interp[ir->data.interpolation]);

   print_type(f, ir->type);
   fprintf(f, " %s)", unique_name(ir));
}


void ir_print_visitor::visit(ir_function_signature *ir)
{
   _mesa_symbol_table_push_scope(symbols);
   fprintf(f, "(signature ");
   indentation++;

   print_type(f, ir->return_type);
   fprintf(f, "\n");
   indent();

   fprintf(f, "(parameters\n");
   indentation++;

   foreach_in_list(ir_variable, inst, &ir->parameters) {
      indent();
      inst->accept(this);
      fprintf(f, "\n");
   }
   indentation--;

   indent();
   fprintf(f, ")\n");

   indent();

   fprintf(f, "(\n");
   indentation++;

   foreach_in_list(ir_instruction, inst, &ir->body) {
      indent();
      inst->accept(this);
      fprintf(f, "\n");
   }
   indentation--;
   indent();
   fprintf(f, "))\n");
   indentation--;
   _mesa_symbol_table_pop_scope(symbols);
}


void ir_print_visitor::visit(ir_function *ir)
{
   fprintf(f, "(function %s\n", ir->name);
   indentation++;
   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
      indent();
      sig->accept(this);
      fprintf(f, "\n");
   }
   indentation--;
   indent();
   fprintf(f, ")\n\n");
}


void ir_print_visitor::visit(ir_expression *ir)
{
   fprintf(f, "(expression ");

   print_type(f, ir->type);

   fprintf(f, " %s ", ir->operator_string());

   for (unsigned i = 0; i < ir->get_num_operands(); i++) {
      ir->operands[i]->accept(this);
   }

   fprintf(f, ") ");
}


void ir_print_visitor::visit(ir_texture *ir)
{
   fprintf(f, "(%s ", ir->opcode_string());

   print_type(f, ir->type);
   fprintf(f, " ");

   ir->sampler->accept(this);
   fprintf(f, " ");

   if (ir->op != ir_txs && ir->op != ir_query_levels) {
      ir->coordinate->accept(this);

      fprintf(f, " ");

      if (ir->offset != NULL) {
	 ir->offset->accept(this);
      } else {
	 fprintf(f, "0");
      }

      fprintf(f, " ");
   }

   fprintf(f, " ");
   switch (ir->op)
   {
   case ir_tex:
   case ir_lod:
   case ir_query_levels:
      break;
   case ir_txb:
      ir->lod_info.bias->accept(this);
      break;
   case ir_txl:
   case ir_txf:
   case ir_txs:
      ir->lod_info.lod->accept(this);
      break;
   case ir_txf_ms:
      ir->lod_info.sample_index->accept(this);
      break;
   case ir_txd:
      fprintf(f, "(");
      ir->lod_info.grad.dPdx->accept(this);
      fprintf(f, " ");
      ir->lod_info.grad.dPdy->accept(this);
      fprintf(f, ")");
      break;
   case ir_tg4:
      ir->lod_info.component->accept(this);
      break;
   };
   fprintf(f, ")");
}


void ir_print_visitor::visit(ir_swizzle *ir)
{
   const unsigned swiz[4] = {
      ir->mask.x,
      ir->mask.y,
      ir->mask.z,
      ir->mask.w,
   };

   fprintf(f, "(swiz ");
   for (unsigned i = 0; i < ir->mask.num_components; i++) {
      fprintf(f, "%c", "xyzw"[swiz[i]]);
   }
   fprintf(f, " ");
   ir->val->accept(this);
   fprintf(f, ")");
}


void ir_print_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->variable_referenced();
   fprintf(f, "(var_ref %s) ", unique_name(var));
}


void ir_print_visitor::visit(ir_dereference_array *ir)
{
   fprintf(f, "(array_ref ");
   ir->array->accept(this);
   ir->array_index->accept(this);
   fprintf(f, ") ");
}


void ir_print_visitor::visit(ir_dereference_record *ir)
{
   fprintf(f, "(record_ref ");
   ir->record->accept(this);
   fprintf(f, " %s) ", ir->field);
}


void ir_print_visitor::visit(ir_assignment *ir)
{
   fprintf(f, "(assign ");

   if (ir->condition)
      ir->condition->accept(this);

   char mask[5];
   unsigned j = 0;

   for (unsigned i = 0; i < 4; i++) {
      if ((ir->write_mask & (1 << i)) != 0) {
	 mask[j] = "xyzw"[i];
	 j++;
      }
   }
   mask[j] = '\0';

   fprintf(f, " (%s) ", mask);

   ir->lhs->accept(this);

   fprintf(f, " ");

   ir->rhs->accept(this);
   fprintf(f, ") ");
}


void ir_print_visitor::visit(ir_constant *ir)
{
   fprintf(f, "(constant ");
   print_type(f, ir->type);
   fprintf(f, " (");

   if (ir->type->is_array()) {
      for (unsigned i = 0; i < ir->type->length; i++)
	 ir->get_array_element(i)->accept(this);
   } else if (ir->type->is_record()) {
      ir_constant *value = (ir_constant *) ir->components.get_head();
      for (unsigned i = 0; i < ir->type->length; i++) {
	 fprintf(f, "(%s ", ir->type->fields.structure[i].name);
	 value->accept(this);
	 fprintf(f, ")");

	 value = (ir_constant *) value->next;
      }
   } else {
      for (unsigned i = 0; i < ir->type->components(); i++) {
	 if (i != 0)
	    fprintf(f, " ");
	 switch (ir->type->base_type) {
	 case GLSL_TYPE_UINT:  fprintf(f, "%u", ir->value.u[i]); break;
	 case GLSL_TYPE_INT:   fprintf(f, "%d", ir->value.i[i]); break;
	 case GLSL_TYPE_FLOAT:
            if (ir->value.f[i] == 0.0f)
               /* 0.0 == -0.0, so print with %f to get the proper sign. */
               fprintf(f, "%f", ir->value.f[i]);
            else if (fabs(ir->value.f[i]) < 0.000001f)
               fprintf(f, "%a", ir->value.f[i]);
            else if (fabs(ir->value.f[i]) > 1000000.0f)
               fprintf(f, "%e", ir->value.f[i]);
            else
               fprintf(f, "%f", ir->value.f[i]);
            break;
	 case GLSL_TYPE_BOOL:  fprintf(f, "%d", ir->value.b[i]); break;
	 default: assert(0);
	 }
      }
   }
   fprintf(f, ")) ");
}


void
ir_print_visitor::visit(ir_call *ir)
{
   fprintf(f, "(call %s ", ir->callee_name());
   if (ir->return_deref)
      ir->return_deref->accept(this);
   fprintf(f, " (");
   foreach_in_list(ir_rvalue, param, &ir->actual_parameters) {
      param->accept(this);
   }
   fprintf(f, "))\n");
}


void
ir_print_visitor::visit(ir_return *ir)
{
   fprintf(f, "(return");

   ir_rvalue *const value = ir->get_value();
   if (value) {
      fprintf(f, " ");
      value->accept(this);
   }

   fprintf(f, ")");
}


void
ir_print_visitor::visit(ir_discard *ir)
{
   fprintf(f, "(discard ");

   if (ir->condition != NULL) {
      fprintf(f, " ");
      ir->condition->accept(this);
   }

   fprintf(f, ")");
}


void
ir_print_visitor::visit(ir_if *ir)
{
   fprintf(f, "(if ");
   ir->condition->accept(this);

   fprintf(f, "(\n");
   indentation++;

   foreach_in_list(ir_instruction, inst, &ir->then_instructions) {
      indent();
      inst->accept(this);
      fprintf(f, "\n");
   }

   indentation--;
   indent();
   fprintf(f, ")\n");

   indent();
   if (!ir->else_instructions.is_empty()) {
      fprintf(f, "(\n");
      indentation++;

      foreach_in_list(ir_instruction, inst, &ir->else_instructions) {
	 indent();
	 inst->accept(this);
	 fprintf(f, "\n");
      }
      indentation--;
      indent();
      fprintf(f, "))\n");
   } else {
      fprintf(f, "())\n");
   }
}


void
ir_print_visitor::visit(ir_loop *ir)
{
   fprintf(f, "(loop (\n");
   indentation++;

   foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
      indent();
      inst->accept(this);
      fprintf(f, "\n");
   }
   indentation--;
   indent();
   fprintf(f, "))\n");
}


void
ir_print_visitor::visit(ir_loop_jump *ir)
{
   fprintf(f, "%s", ir->is_break() ? "break" : "continue");
}

void
ir_print_visitor::visit(ir_precision_statement *ir)
{
	//printf("%s", ir->precision_statement);
}

void
ir_print_visitor::visit(ir_typedecl_statement *ir)
{
}

void
ir_print_visitor::visit(ir_emit_vertex *ir)
{
   fprintf(f, "(emit-vertex ");
   ir->stream->accept(this);
   fprintf(f, ")\n");
}

void
ir_print_visitor::visit(ir_end_primitive *ir)
{
   fprintf(f, "(end-primitive ");
   ir->stream->accept(this);
   fprintf(f, ")\n");

}

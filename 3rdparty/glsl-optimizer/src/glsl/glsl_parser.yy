%{
/*
 * Copyright © 2008, 2009 Intel Corporation
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#endif
#include <assert.h>

#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_types.h"
#include "main/context.h"

#if defined(_MSC_VER)
#	pragma warning(disable: 4065) // warning C4065: switch statement contains 'default' but no 'case' labels
#	pragma warning(disable: 4244) // warning C4244: '=' : conversion from 'double' to 'float', possible loss of data
#endif // defined(_MSC_VER)

#undef yyerror

static void yyerror(YYLTYPE *loc, _mesa_glsl_parse_state *st, const char *msg)
{
   _mesa_glsl_error(loc, st, "%s", msg);
}

static int
_mesa_glsl_lex(YYSTYPE *val, YYLTYPE *loc, _mesa_glsl_parse_state *state)
{
   return _mesa_glsl_lexer_lex(val, loc, state->scanner);
}

static bool match_layout_qualifier(const char *s1, const char *s2,
                                   _mesa_glsl_parse_state *state)
{
   /* From the GLSL 1.50 spec, section 4.3.8 (Layout Qualifiers):
    *
    *     "The tokens in any layout-qualifier-id-list ... are not case
    *     sensitive, unless explicitly noted otherwise."
    *
    * The text "unless explicitly noted otherwise" appears to be
    * vacuous--no desktop GLSL spec (up through GLSL 4.40) notes
    * otherwise.
    *
    * However, the GLSL ES 3.00 spec says, in section 4.3.8 (Layout
    * Qualifiers):
    *
    *     "As for other identifiers, they are case sensitive."
    *
    * So we need to do a case-sensitive or a case-insensitive match,
    * depending on whether we are compiling for GLSL ES.
    */
   if (state->es_shader)
      return strcmp(s1, s2);
   else
      return strcasecmp(s1, s2);
}
%}

%expect 0

%pure-parser
%error-verbose

%locations
%initial-action {
   @$.first_line = 1;
   @$.first_column = 1;
   @$.last_line = 1;
   @$.last_column = 1;
   @$.source = 0;
}

%lex-param   {struct _mesa_glsl_parse_state *state}
%parse-param {struct _mesa_glsl_parse_state *state}

%union {
   int n;
   float real;
   const char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
   ast_array_specifier *array_specifier;
   ast_fully_specified_type *fully_specified_type;
   ast_function *function;
   ast_parameter_declarator *parameter_declarator;
   ast_function_definition *function_definition;
   ast_compound_statement *compound_statement;
   ast_expression *expression;
   ast_declarator_list *declarator_list;
   ast_struct_specifier *struct_specifier;
   ast_declaration *declaration;
   ast_switch_body *switch_body;
   ast_case_label *case_label;
   ast_case_label_list *case_label_list;
   ast_case_statement *case_statement;
   ast_case_statement_list *case_statement_list;
   ast_interface_block *interface_block;

   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;
}

%token ATTRIBUTE CONST_TOK BOOL_TOK FLOAT_TOK INT_TOK UINT_TOK
%token BREAK CONTINUE DO ELSE FOR IF DISCARD RETURN SWITCH CASE DEFAULT
%token BVEC2 BVEC3 BVEC4 IVEC2 IVEC3 IVEC4 UVEC2 UVEC3 UVEC4 VEC2 VEC3 VEC4
%token CENTROID IN_TOK OUT_TOK INOUT_TOK UNIFORM VARYING SAMPLE
%token NOPERSPECTIVE FLAT SMOOTH
%token MAT2X2 MAT2X3 MAT2X4
%token MAT3X2 MAT3X3 MAT3X4
%token MAT4X2 MAT4X3 MAT4X4
%token SAMPLER1D SAMPLER2D SAMPLER3D SAMPLERCUBE SAMPLER1DSHADOW SAMPLER2DSHADOW
%token SAMPLERCUBESHADOW SAMPLER1DARRAY SAMPLER2DARRAY SAMPLER1DARRAYSHADOW
%token SAMPLER2DARRAYSHADOW SAMPLERCUBEARRAY SAMPLERCUBEARRAYSHADOW
%token ISAMPLER1D ISAMPLER2D ISAMPLER3D ISAMPLERCUBE
%token ISAMPLER1DARRAY ISAMPLER2DARRAY ISAMPLERCUBEARRAY
%token USAMPLER1D USAMPLER2D USAMPLER3D USAMPLERCUBE USAMPLER1DARRAY
%token USAMPLER2DARRAY USAMPLERCUBEARRAY
%token SAMPLER2DRECT ISAMPLER2DRECT USAMPLER2DRECT SAMPLER2DRECTSHADOW
%token SAMPLERBUFFER ISAMPLERBUFFER USAMPLERBUFFER
%token SAMPLER2DMS ISAMPLER2DMS USAMPLER2DMS
%token SAMPLER2DMSARRAY ISAMPLER2DMSARRAY USAMPLER2DMSARRAY
%token SAMPLEREXTERNALOES
%token IMAGE1D IMAGE2D IMAGE3D IMAGE2DRECT IMAGECUBE IMAGEBUFFER
%token IMAGE1DARRAY IMAGE2DARRAY IMAGECUBEARRAY IMAGE2DMS IMAGE2DMSARRAY
%token IIMAGE1D IIMAGE2D IIMAGE3D IIMAGE2DRECT IIMAGECUBE IIMAGEBUFFER
%token IIMAGE1DARRAY IIMAGE2DARRAY IIMAGECUBEARRAY IIMAGE2DMS IIMAGE2DMSARRAY
%token UIMAGE1D UIMAGE2D UIMAGE3D UIMAGE2DRECT UIMAGECUBE UIMAGEBUFFER
%token UIMAGE1DARRAY UIMAGE2DARRAY UIMAGECUBEARRAY UIMAGE2DMS UIMAGE2DMSARRAY
%token IMAGE1DSHADOW IMAGE2DSHADOW IMAGE1DARRAYSHADOW IMAGE2DARRAYSHADOW
%token COHERENT VOLATILE RESTRICT READONLY WRITEONLY
%token ATOMIC_UINT
%token STRUCT VOID_TOK WHILE
%token <identifier> IDENTIFIER TYPE_IDENTIFIER NEW_IDENTIFIER
%type <identifier> any_identifier
%type <interface_block> instance_name_opt
%token <real> FLOATCONSTANT
%token <n> INTCONSTANT UINTCONSTANT BOOLCONSTANT
%token <identifier> FIELD_SELECTION
%token LEFT_OP RIGHT_OP
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP XOR_OP MUL_ASSIGN DIV_ASSIGN ADD_ASSIGN
%token MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token SUB_ASSIGN
%token INVARIANT PRECISE
%token LOWP MEDIUMP HIGHP SUPERP PRECISION

%token VERSION_TOK EXTENSION LINE COLON EOL INTERFACE OUTPUT
%token PRAGMA_DEBUG_ON PRAGMA_DEBUG_OFF
%token PRAGMA_OPTIMIZE_ON PRAGMA_OPTIMIZE_OFF
%token PRAGMA_INVARIANT_ALL
%token LAYOUT_TOK

   /* Reserved words that are not actually used in the grammar.
    */
%token ASM CLASS UNION ENUM TYPEDEF TEMPLATE THIS PACKED_TOK GOTO
%token INLINE_TOK NOINLINE PUBLIC_TOK STATIC EXTERN EXTERNAL
%token LONG_TOK SHORT_TOK DOUBLE_TOK HALF FIXED_TOK UNSIGNED INPUT_TOK
%token HVEC2 HVEC3 HVEC4 DVEC2 DVEC3 DVEC4 FVEC2 FVEC3 FVEC4
%token SAMPLER3DRECT
%token SIZEOF CAST NAMESPACE USING
%token RESOURCE PATCH
%token SUBROUTINE

%token ERROR_TOK

%token COMMON PARTITION ACTIVE FILTER ROW_MAJOR

%type <identifier> variable_identifier
%type <node> statement
%type <node> statement_list
%type <node> simple_statement
%type <n> precision_qualifier
%type <type_qualifier> type_qualifier
%type <type_qualifier> auxiliary_storage_qualifier
%type <type_qualifier> storage_qualifier
%type <type_qualifier> interpolation_qualifier
%type <type_qualifier> layout_qualifier
%type <type_qualifier> layout_qualifier_id_list layout_qualifier_id
%type <type_qualifier> interface_block_layout_qualifier
%type <type_qualifier> interface_qualifier
%type <type_specifier> type_specifier
%type <type_specifier> type_specifier_nonarray
%type <array_specifier> array_specifier
%type <identifier> basic_type_specifier_nonarray
%type <fully_specified_type> fully_specified_type
%type <function> function_prototype
%type <function> function_header
%type <function> function_header_with_parameters
%type <function> function_declarator
%type <parameter_declarator> parameter_declarator
%type <parameter_declarator> parameter_declaration
%type <type_qualifier> parameter_qualifier
%type <type_qualifier> parameter_direction_qualifier
%type <type_specifier> parameter_type_specifier
%type <function_definition> function_definition
%type <compound_statement> compound_statement_no_new_scope
%type <compound_statement> compound_statement
%type <node> statement_no_new_scope
%type <node> expression_statement
%type <expression> expression
%type <expression> primary_expression
%type <expression> assignment_expression
%type <expression> conditional_expression
%type <expression> logical_or_expression
%type <expression> logical_xor_expression
%type <expression> logical_and_expression
%type <expression> inclusive_or_expression
%type <expression> exclusive_or_expression
%type <expression> and_expression
%type <expression> equality_expression
%type <expression> relational_expression
%type <expression> shift_expression
%type <expression> additive_expression
%type <expression> multiplicative_expression
%type <expression> unary_expression
%type <expression> constant_expression
%type <expression> integer_expression
%type <expression> postfix_expression
%type <expression> function_call_header_with_parameters
%type <expression> function_call_header_no_parameters
%type <expression> function_call_header
%type <expression> function_call_generic
%type <expression> function_call_or_method
%type <expression> function_call
%type <expression> method_call_generic
%type <expression> method_call_header_with_parameters
%type <expression> method_call_header_no_parameters
%type <expression> method_call_header
%type <n> assignment_operator
%type <n> unary_operator
%type <expression> function_identifier
%type <node> external_declaration
%type <declarator_list> init_declarator_list
%type <declarator_list> single_declaration
%type <expression> initializer
%type <expression> initializer_list
%type <node> declaration
%type <node> declaration_statement
%type <node> jump_statement
%type <node> interface_block
%type <interface_block> basic_interface_block
%type <struct_specifier> struct_specifier
%type <declarator_list> struct_declaration_list
%type <declarator_list> struct_declaration
%type <declaration> struct_declarator
%type <declaration> struct_declarator_list
%type <declarator_list> member_list
%type <declarator_list> member_declaration
%type <node> selection_statement
%type <selection_rest_statement> selection_rest_statement
%type <node> switch_statement
%type <switch_body> switch_body
%type <case_label_list> case_label_list
%type <case_label> case_label
%type <case_statement> case_statement
%type <case_statement_list> case_statement_list
%type <node> iteration_statement
%type <node> condition
%type <node> conditionopt
%type <node> for_init_statement
%type <for_rest_statement> for_rest_statement
%type <n> integer_constant
%type <node> layout_defaults

%right THEN ELSE
%%

translation_unit:
   version_statement extension_statement_list
   {
      _mesa_glsl_initialize_types(state);
   }
   external_declaration_list
   {
      delete state->symbols;
      state->symbols = new(ralloc_parent(state)) glsl_symbol_table;
      _mesa_glsl_initialize_types(state);
   }
   ;

version_statement:
   /* blank - no #version specified: defaults are already set */
   | VERSION_TOK INTCONSTANT EOL
   {
      state->process_version_directive(&@2, $2, NULL);
      if (state->error) {
         YYERROR;
      }
   }
   | VERSION_TOK INTCONSTANT any_identifier EOL
   {
      state->process_version_directive(&@2, $2, $3);
      if (state->error) {
         YYERROR;
      }
   }
   ;

pragma_statement:
   PRAGMA_DEBUG_ON EOL
   | PRAGMA_DEBUG_OFF EOL
   | PRAGMA_OPTIMIZE_ON EOL
   | PRAGMA_OPTIMIZE_OFF EOL
   | PRAGMA_INVARIANT_ALL EOL
   {
      if (!state->is_version(120, 100)) {
         _mesa_glsl_warning(& @1, state,
                            "pragma `invariant(all)' not supported in %s "
                            "(GLSL ES 1.00 or GLSL 1.20 required)",
                            state->get_version_string());
      } else {
         state->all_invariant = true;
      }
   }
   ;

extension_statement_list:

   | extension_statement_list extension_statement
   ;

any_identifier:
   IDENTIFIER
   | TYPE_IDENTIFIER
   | NEW_IDENTIFIER
   ;

extension_statement:
   EXTENSION any_identifier COLON any_identifier EOL
   {
      if (!_mesa_glsl_process_extension($2, & @2, $4, & @4, state)) {
         YYERROR;
      }
   }
   ;

external_declaration_list:
   external_declaration
   {
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if ($1 != NULL)
         state->translation_unit.push_tail(& $1->link);
   }
   | external_declaration_list external_declaration
   {
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if ($2 != NULL)
         state->translation_unit.push_tail(& $2->link);
   }
   | external_declaration_list extension_statement {
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& @2, state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
   ;

variable_identifier:
   IDENTIFIER
   | NEW_IDENTIFIER
   ;

primary_expression:
   variable_identifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
      $$->set_location(@1);
      $$->primary_expression.identifier = $1;
   }
   | INTCONSTANT
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
      $$->set_location(@1);
      $$->primary_expression.int_constant = $1;
   }
   | UINTCONSTANT
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
      $$->set_location(@1);
      $$->primary_expression.uint_constant = $1;
   }
   | FLOATCONSTANT
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
      $$->set_location(@1);
      $$->primary_expression.float_constant = $1;
   }
   | BOOLCONSTANT
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
      $$->set_location(@1);
      $$->primary_expression.bool_constant = $1;
   }
   | '(' expression ')'
   {
      $$ = $2;
   }
   ;

postfix_expression:
   primary_expression
   | postfix_expression '[' integer_expression ']'
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_array_index, $1, $3, NULL);
      $$->set_location_range(@1, @4);
   }
   | function_call
   {
      $$ = $1;
   }
   | postfix_expression '.' any_identifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_field_selection, $1, NULL, NULL);
      $$->set_location_range(@1, @3);
      $$->primary_expression.identifier = $3;
   }
   | postfix_expression INC_OP
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_post_inc, $1, NULL, NULL);
      $$->set_location_range(@1, @2);
   }
   | postfix_expression DEC_OP
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_post_dec, $1, NULL, NULL);
      $$->set_location_range(@1, @2);
   }
   ;

integer_expression:
   expression
   ;

function_call:
   function_call_or_method
   ;

function_call_or_method:
   function_call_generic
   | postfix_expression '.' method_call_generic
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_field_selection, $1, $3, NULL);
      $$->set_location_range(@1, @3);
   }
   ;

function_call_generic:
   function_call_header_with_parameters ')'
   | function_call_header_no_parameters ')'
   ;

function_call_header_no_parameters:
   function_call_header VOID_TOK
   | function_call_header
   ;

function_call_header_with_parameters:
   function_call_header assignment_expression
   {
      $$ = $1;
      $$->set_location(@1);
      $$->expressions.push_tail(& $2->link);
   }
   | function_call_header_with_parameters ',' assignment_expression
   {
      $$ = $1;
      $$->set_location(@1);
      $$->expressions.push_tail(& $3->link);
   }
   ;

   // Grammar Note: Constructors look like functions, but lexical
   // analysis recognized most of them as keywords. They are now
   // recognized through "type_specifier".
function_call_header:
   function_identifier '('
   ;

function_identifier:
   type_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_function_expression($1);
      $$->set_location(@1);
      }
   | variable_identifier
   {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression($1);
      callee->set_location(@1);
      $$ = new(ctx) ast_function_expression(callee);
      $$->set_location(@1);
      }
   | FIELD_SELECTION
   {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression($1);
      callee->set_location(@1);
      $$ = new(ctx) ast_function_expression(callee);
      $$->set_location(@1);
      }
   ;

method_call_generic:
   method_call_header_with_parameters ')'
   | method_call_header_no_parameters ')'
   ;

method_call_header_no_parameters:
   method_call_header VOID_TOK
   | method_call_header
   ;

method_call_header_with_parameters:
   method_call_header assignment_expression
   {
      $$ = $1;
      $$->set_location(@1);
      $$->expressions.push_tail(& $2->link);
   }
   | method_call_header_with_parameters ',' assignment_expression
   {
      $$ = $1;
      $$->set_location(@1);
      $$->expressions.push_tail(& $3->link);
   }
   ;

   // Grammar Note: Constructors look like methods, but lexical
   // analysis recognized most of them as keywords. They are now
   // recognized through "type_specifier".
method_call_header:
   variable_identifier '('
   {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression($1);
      callee->set_location(@1);
      $$ = new(ctx) ast_function_expression(callee);
      $$->set_location(@1);
   }
   ;

   // Grammar Note: No traditional style type casts.
unary_expression:
   postfix_expression
   | INC_OP unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_pre_inc, $2, NULL, NULL);
      $$->set_location(@1);
   }
   | DEC_OP unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_pre_dec, $2, NULL, NULL);
      $$->set_location(@1);
   }
   | unary_operator unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression($1, $2, NULL, NULL);
      $$->set_location_range(@1, @2);
   }
   ;

   // Grammar Note: No '*' or '&' unary ops. Pointers are not supported.
unary_operator:
   '+'   { $$ = ast_plus; }
   | '-' { $$ = ast_neg; }
   | '!' { $$ = ast_logic_not; }
   | '~' { $$ = ast_bit_not; }
   ;

multiplicative_expression:
   unary_expression
   | multiplicative_expression '*' unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_mul, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | multiplicative_expression '/' unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_div, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | multiplicative_expression '%' unary_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_mod, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

additive_expression:
   multiplicative_expression
   | additive_expression '+' multiplicative_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_add, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | additive_expression '-' multiplicative_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_sub, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

shift_expression:
   additive_expression
   | shift_expression LEFT_OP additive_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_lshift, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | shift_expression RIGHT_OP additive_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_rshift, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

relational_expression:
   shift_expression
   | relational_expression '<' shift_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_less, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | relational_expression '>' shift_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_greater, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | relational_expression LE_OP shift_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_lequal, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | relational_expression GE_OP shift_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_gequal, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

equality_expression:
   relational_expression
   | equality_expression EQ_OP relational_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_equal, $1, $3);
      $$->set_location_range(@1, @3);
   }
   | equality_expression NE_OP relational_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_nequal, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

and_expression:
   equality_expression
   | and_expression '&' equality_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_bit_and, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

exclusive_or_expression:
   and_expression
   | exclusive_or_expression '^' and_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_bit_xor, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

inclusive_or_expression:
   exclusive_or_expression
   | inclusive_or_expression '|' exclusive_or_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_bit_or, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

logical_and_expression:
   inclusive_or_expression
   | logical_and_expression AND_OP inclusive_or_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_logic_and, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

logical_xor_expression:
   logical_and_expression
   | logical_xor_expression XOR_OP logical_and_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_logic_xor, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

logical_or_expression:
   logical_xor_expression
   | logical_or_expression OR_OP logical_xor_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_bin(ast_logic_or, $1, $3);
      $$->set_location_range(@1, @3);
   }
   ;

conditional_expression:
   logical_or_expression
   | logical_or_expression '?' expression ':' assignment_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression(ast_conditional, $1, $3, $5);
      $$->set_location_range(@1, @5);
   }
   ;

assignment_expression:
   conditional_expression
   | unary_expression assignment_operator assignment_expression
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression($2, $1, $3, NULL);
      $$->set_location_range(@1, @3);
   }
   ;

assignment_operator:
   '='                { $$ = ast_assign; }
   | MUL_ASSIGN       { $$ = ast_mul_assign; }
   | DIV_ASSIGN       { $$ = ast_div_assign; }
   | MOD_ASSIGN       { $$ = ast_mod_assign; }
   | ADD_ASSIGN       { $$ = ast_add_assign; }
   | SUB_ASSIGN       { $$ = ast_sub_assign; }
   | LEFT_ASSIGN      { $$ = ast_ls_assign; }
   | RIGHT_ASSIGN     { $$ = ast_rs_assign; }
   | AND_ASSIGN       { $$ = ast_and_assign; }
   | XOR_ASSIGN       { $$ = ast_xor_assign; }
   | OR_ASSIGN        { $$ = ast_or_assign; }
   ;

expression:
   assignment_expression
   {
      $$ = $1;
   }
   | expression ',' assignment_expression
   {
      void *ctx = state;
      if ($1->oper != ast_sequence) {
         $$ = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
         $$->set_location_range(@1, @3);
         $$->expressions.push_tail(& $1->link);
      } else {
         $$ = $1;
      }

      $$->expressions.push_tail(& $3->link);
   }
   ;

constant_expression:
   conditional_expression
   ;

declaration:
   function_prototype ';'
   {
      state->symbols->pop_scope();
      $$ = $1;
   }
   | init_declarator_list ';'
   {
      $$ = $1;
   }
   | PRECISION precision_qualifier type_specifier ';'
   {
      $3->default_precision = $2;
      $$ = $3;
   }
   | interface_block
   {
      $$ = $1;
   }
   ;

function_prototype:
   function_declarator ')'
   ;

function_declarator:
   function_header
   | function_header_with_parameters
   ;

function_header_with_parameters:
   function_header parameter_declaration
   {
      $$ = $1;
      $$->parameters.push_tail(& $2->link);
   }
   | function_header_with_parameters ',' parameter_declaration
   {
      $$ = $1;
      $$->parameters.push_tail(& $3->link);
   }
   ;

function_header:
   fully_specified_type variable_identifier '('
   {
      void *ctx = state;
      $$ = new(ctx) ast_function();
      $$->set_location(@2);
      $$->return_type = $1;
      $$->identifier = $2;

      state->symbols->add_function(new(state) ir_function($2));
      state->symbols->push_scope();
   }
   ;

parameter_declarator:
   type_specifier any_identifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_parameter_declarator();
      $$->set_location_range(@1, @2);
      $$->type = new(ctx) ast_fully_specified_type();
      $$->type->set_location(@1);
      $$->type->specifier = $1;
      $$->identifier = $2;
   }
   | type_specifier any_identifier array_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_parameter_declarator();
      $$->set_location_range(@1, @3);
      $$->type = new(ctx) ast_fully_specified_type();
      $$->type->set_location(@1);
      $$->type->specifier = $1;
      $$->identifier = $2;
      $$->array_specifier = $3;
   }
   ;

parameter_declaration:
   parameter_qualifier parameter_declarator
   {
      $$ = $2;
      $$->type->qualifier = $1;
   }
   | parameter_qualifier parameter_type_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_parameter_declarator();
      $$->set_location(@2);
      $$->type = new(ctx) ast_fully_specified_type();
      $$->type->set_location_range(@1, @2);
      $$->type->qualifier = $1;
      $$->type->specifier = $2;
   }
   ;

parameter_qualifier:
   /* empty */
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
   }
   | CONST_TOK parameter_qualifier
   {
      if ($2.flags.q.constant)
         _mesa_glsl_error(&@1, state, "duplicate const qualifier");

      $$ = $2;
      $$.flags.q.constant = 1;
   }
   | PRECISE parameter_qualifier
   {
      if ($2.flags.q.precise)
         _mesa_glsl_error(&@1, state, "duplicate precise qualifier");

      $$ = $2;
      $$.flags.q.precise = 1;
   }
   | parameter_direction_qualifier parameter_qualifier
   {
      if (($1.flags.q.in || $1.flags.q.out) && ($2.flags.q.in || $2.flags.q.out))
         _mesa_glsl_error(&@1, state, "duplicate in/out/inout qualifier");

      if (!state->ARB_shading_language_420pack_enable && $2.flags.q.constant)
         _mesa_glsl_error(&@1, state, "in/out/inout must come after const "
                                      "or precise");

      $$ = $1;
      $$.merge_qualifier(&@1, state, $2);
   }
   | precision_qualifier parameter_qualifier
   {
      if ($2.precision != ast_precision_none)
         _mesa_glsl_error(&@1, state, "duplicate precision qualifier");

      if (!state->ARB_shading_language_420pack_enable && $2.flags.i != 0)
         _mesa_glsl_error(&@1, state, "precision qualifiers must come last");

      $$ = $2;
      $$.precision = $1;
   }

parameter_direction_qualifier:
   IN_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.in = 1;
   }
   | OUT_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.out = 1;
   }
   | INOUT_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.in = 1;
      $$.flags.q.out = 1;
   }
   ;

parameter_type_specifier:
   type_specifier
   ;

init_declarator_list:

   single_declaration
   | init_declarator_list ',' any_identifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($3, NULL, NULL);
      decl->set_location(@3);

      $$ = $1;
      $$->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, $3, ir_var_auto, glsl_precision_undefined));
   }
   | init_declarator_list ',' any_identifier array_specifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($3, $4, NULL);
      decl->set_location_range(@3, @4);

      $$ = $1;
      $$->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, $3, ir_var_auto, glsl_precision_undefined));
   }
   | init_declarator_list ',' any_identifier array_specifier '=' initializer
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($3, $4, $6);
      decl->set_location_range(@3, @4);

      $$ = $1;
      $$->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, $3, ir_var_auto, glsl_precision_undefined));
   }
   | init_declarator_list ',' any_identifier '=' initializer
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($3, NULL, $5);
      decl->set_location(@3);

      $$ = $1;
      $$->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, $3, ir_var_auto, glsl_precision_undefined));
   }
   ;

   // Grammar Note: No 'enum', or 'typedef'.
single_declaration:
   fully_specified_type
   {
      void *ctx = state;
      /* Empty declaration list is valid. */
      $$ = new(ctx) ast_declarator_list($1);
      $$->set_location(@1);
   }
   | fully_specified_type any_identifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, NULL, NULL);
      decl->set_location(@2);

      $$ = new(ctx) ast_declarator_list($1);
      $$->set_location_range(@1, @2);
      $$->declarations.push_tail(&decl->link);
   }
   | fully_specified_type any_identifier array_specifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, $3, NULL);
      decl->set_location_range(@2, @3);

      $$ = new(ctx) ast_declarator_list($1);
      $$->set_location_range(@1, @3);
      $$->declarations.push_tail(&decl->link);
   }
   | fully_specified_type any_identifier array_specifier '=' initializer
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, $3, $5);
      decl->set_location_range(@2, @3);

      $$ = new(ctx) ast_declarator_list($1);
      $$->set_location_range(@1, @3);
      $$->declarations.push_tail(&decl->link);
   }
   | fully_specified_type any_identifier '=' initializer
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, NULL, $4);
      decl->set_location(@2);

      $$ = new(ctx) ast_declarator_list($1);
      $$->set_location_range(@1, @2);
      $$->declarations.push_tail(&decl->link);
   }
   | INVARIANT variable_identifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, NULL, NULL);
      decl->set_location(@2);

      $$ = new(ctx) ast_declarator_list(NULL);
      $$->set_location_range(@1, @2);
      $$->invariant = true;

      $$->declarations.push_tail(&decl->link);
   }
   | PRECISE variable_identifier
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, NULL, NULL);
      decl->set_location(@2);

      $$ = new(ctx) ast_declarator_list(NULL);
      $$->set_location_range(@1, @2);
      $$->precise = true;

      $$->declarations.push_tail(&decl->link);
   }
   ;

fully_specified_type:
   type_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_fully_specified_type();
      $$->set_location(@1);
      $$->specifier = $1;
   }
   | type_qualifier type_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_fully_specified_type();
      $$->set_location_range(@1, @2);
      $$->qualifier = $1;
      $$->specifier = $2;
   }
   ;

layout_qualifier:
   LAYOUT_TOK '(' layout_qualifier_id_list ')'
   {
      $$ = $3;
   }
   ;

layout_qualifier_id_list:
   layout_qualifier_id
   | layout_qualifier_id_list ',' layout_qualifier_id
   {
      $$ = $1;
      if (!$$.merge_qualifier(& @3, state, $3)) {
         YYERROR;
      }
   }
   ;

integer_constant:
   INTCONSTANT { $$ = $1; }
   | UINTCONSTANT { $$ = $1; }
   ;

layout_qualifier_id:
   any_identifier
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;

      /* Layout qualifiers for ARB_fragment_coord_conventions. */
      if (!$$.flags.i && (state->ARB_fragment_coord_conventions_enable ||
                          state->is_version(150, 0))) {
         if (match_layout_qualifier($1, "origin_upper_left", state) == 0) {
            $$.flags.q.origin_upper_left = 1;
         } else if (match_layout_qualifier($1, "pixel_center_integer",
                                           state) == 0) {
            $$.flags.q.pixel_center_integer = 1;
         }

         if ($$.flags.i && state->ARB_fragment_coord_conventions_warn) {
            _mesa_glsl_warning(& @1, state,
                               "GL_ARB_fragment_coord_conventions layout "
                               "identifier `%s' used", $1);
         }
      }

      /* Layout qualifiers for AMD/ARB_conservative_depth. */
      if (!$$.flags.i &&
          (state->AMD_conservative_depth_enable ||
           state->ARB_conservative_depth_enable)) {
         if (match_layout_qualifier($1, "depth_any", state) == 0) {
            $$.flags.q.depth_any = 1;
         } else if (match_layout_qualifier($1, "depth_greater", state) == 0) {
            $$.flags.q.depth_greater = 1;
         } else if (match_layout_qualifier($1, "depth_less", state) == 0) {
            $$.flags.q.depth_less = 1;
         } else if (match_layout_qualifier($1, "depth_unchanged",
                                           state) == 0) {
            $$.flags.q.depth_unchanged = 1;
         }

         if ($$.flags.i && state->AMD_conservative_depth_warn) {
            _mesa_glsl_warning(& @1, state,
                               "GL_AMD_conservative_depth "
                               "layout qualifier `%s' is used", $1);
         }
         if ($$.flags.i && state->ARB_conservative_depth_warn) {
            _mesa_glsl_warning(& @1, state,
                               "GL_ARB_conservative_depth "
                               "layout qualifier `%s' is used", $1);
         }
      }

      /* See also interface_block_layout_qualifier. */
      if (!$$.flags.i && state->has_uniform_buffer_objects()) {
         if (match_layout_qualifier($1, "std140", state) == 0) {
            $$.flags.q.std140 = 1;
         } else if (match_layout_qualifier($1, "shared", state) == 0) {
            $$.flags.q.shared = 1;
         } else if (match_layout_qualifier($1, "column_major", state) == 0) {
            $$.flags.q.column_major = 1;
         /* "row_major" is a reserved word in GLSL 1.30+. Its token is parsed
          * below in the interface_block_layout_qualifier rule.
          *
          * It is not a reserved word in GLSL ES 3.00, so it's handled here as
          * an identifier.
          *
          * Also, this takes care of alternate capitalizations of
          * "row_major" (which is necessary because layout qualifiers
          * are case-insensitive in desktop GLSL).
          */
         } else if (match_layout_qualifier($1, "row_major", state) == 0) {
            $$.flags.q.row_major = 1;
         /* "packed" is a reserved word in GLSL, and its token is
          * parsed below in the interface_block_layout_qualifier rule.
          * However, we must take care of alternate capitalizations of
          * "packed", because layout qualifiers are case-insensitive
          * in desktop GLSL.
          */
         } else if (match_layout_qualifier($1, "packed", state) == 0) {
           $$.flags.q.packed = 1;
         }

         if ($$.flags.i && state->ARB_uniform_buffer_object_warn) {
            _mesa_glsl_warning(& @1, state,
                               "#version 140 / GL_ARB_uniform_buffer_object "
                               "layout qualifier `%s' is used", $1);
         }
      }

      /* Layout qualifiers for GLSL 1.50 geometry shaders. */
      if (!$$.flags.i) {
         static const struct {
            const char *s;
            GLenum e;
         } map[] = {
                 { "points", GL_POINTS },
                 { "lines", GL_LINES },
                 { "lines_adjacency", GL_LINES_ADJACENCY },
                 { "line_strip", GL_LINE_STRIP },
                 { "triangles", GL_TRIANGLES },
                 { "triangles_adjacency", GL_TRIANGLES_ADJACENCY },
                 { "triangle_strip", GL_TRIANGLE_STRIP },
         };
         for (unsigned i = 0; i < Elements(map); i++) {
            if (match_layout_qualifier($1, map[i].s, state) == 0) {
               $$.flags.q.prim_type = 1;
               $$.prim_type = map[i].e;
               break;
            }
         }

         if ($$.flags.i && !state->is_version(150, 0)) {
            _mesa_glsl_error(& @1, state, "#version 150 layout "
                             "qualifier `%s' used", $1);
         }
      }

      /* Layout qualifiers for ARB_shader_image_load_store. */
      if (state->ARB_shader_image_load_store_enable ||
          state->is_version(420, 0)) {
         if (!$$.flags.i) {
            static const struct {
               const char *name;
               GLenum format;
               glsl_base_type base_type;
            } map[] = {
               { "rgba32f", GL_RGBA32F, GLSL_TYPE_FLOAT },
               { "rgba16f", GL_RGBA16F, GLSL_TYPE_FLOAT },
               { "rg32f", GL_RG32F, GLSL_TYPE_FLOAT },
               { "rg16f", GL_RG16F, GLSL_TYPE_FLOAT },
               { "r11f_g11f_b10f", GL_R11F_G11F_B10F, GLSL_TYPE_FLOAT },
               { "r32f", GL_R32F, GLSL_TYPE_FLOAT },
               { "r16f", GL_R16F, GLSL_TYPE_FLOAT },
               { "rgba32ui", GL_RGBA32UI, GLSL_TYPE_UINT },
               { "rgba16ui", GL_RGBA16UI, GLSL_TYPE_UINT },
               { "rgb10_a2ui", GL_RGB10_A2UI, GLSL_TYPE_UINT },
               { "rgba8ui", GL_RGBA8UI, GLSL_TYPE_UINT },
               { "rg32ui", GL_RG32UI, GLSL_TYPE_UINT },
               { "rg16ui", GL_RG16UI, GLSL_TYPE_UINT },
               { "rg8ui", GL_RG8UI, GLSL_TYPE_UINT },
               { "r32ui", GL_R32UI, GLSL_TYPE_UINT },
               { "r16ui", GL_R16UI, GLSL_TYPE_UINT },
               { "r8ui", GL_R8UI, GLSL_TYPE_UINT },
               { "rgba32i", GL_RGBA32I, GLSL_TYPE_INT },
               { "rgba16i", GL_RGBA16I, GLSL_TYPE_INT },
               { "rgba8i", GL_RGBA8I, GLSL_TYPE_INT },
               { "rg32i", GL_RG32I, GLSL_TYPE_INT },
               { "rg16i", GL_RG16I, GLSL_TYPE_INT },
               { "rg8i", GL_RG8I, GLSL_TYPE_INT },
               { "r32i", GL_R32I, GLSL_TYPE_INT },
               { "r16i", GL_R16I, GLSL_TYPE_INT },
               { "r8i", GL_R8I, GLSL_TYPE_INT },
               { "rgba16", GL_RGBA16, GLSL_TYPE_FLOAT },
               { "rgb10_a2", GL_RGB10_A2, GLSL_TYPE_FLOAT },
               { "rgba8", GL_RGBA8, GLSL_TYPE_FLOAT },
               { "rg16", GL_RG16, GLSL_TYPE_FLOAT },
               { "rg8", GL_RG8, GLSL_TYPE_FLOAT },
               { "r16", GL_R16, GLSL_TYPE_FLOAT },
               { "r8", GL_R8, GLSL_TYPE_FLOAT },
               { "rgba16_snorm", GL_RGBA16_SNORM, GLSL_TYPE_FLOAT },
               { "rgba8_snorm", GL_RGBA8_SNORM, GLSL_TYPE_FLOAT },
               { "rg16_snorm", GL_RG16_SNORM, GLSL_TYPE_FLOAT },
               { "rg8_snorm", GL_RG8_SNORM, GLSL_TYPE_FLOAT },
               { "r16_snorm", GL_R16_SNORM, GLSL_TYPE_FLOAT },
               { "r8_snorm", GL_R8_SNORM, GLSL_TYPE_FLOAT }
            };

            for (unsigned i = 0; i < Elements(map); i++) {
               if (match_layout_qualifier($1, map[i].name, state) == 0) {
                  $$.flags.q.explicit_image_format = 1;
                  $$.image_format = map[i].format;
                  $$.image_base_type = map[i].base_type;
                  break;
               }
            }
         }

         if (!$$.flags.i &&
             match_layout_qualifier($1, "early_fragment_tests", state) == 0) {
            $$.flags.q.early_fragment_tests = 1;
         }
      }

      if (!$$.flags.i) {
         _mesa_glsl_error(& @1, state, "unrecognized layout identifier "
                          "`%s'", $1);
         YYERROR;
      }
   }
   | any_identifier '=' integer_constant
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;

      if (match_layout_qualifier("location", $1, state) == 0) {
         $$.flags.q.explicit_location = 1;

         if ($$.flags.q.attribute == 1 &&
             state->ARB_explicit_attrib_location_warn) {
            _mesa_glsl_warning(& @1, state,
                               "GL_ARB_explicit_attrib_location layout "
                               "identifier `%s' used", $1);
         }

         if ($3 >= 0) {
            $$.location = $3;
         } else {
             _mesa_glsl_error(& @3, state, "invalid location %d specified", $3);
             YYERROR;
         }
      }

      if (match_layout_qualifier("index", $1, state) == 0) {
         $$.flags.q.explicit_index = 1;

         if ($3 >= 0) {
            $$.index = $3;
         } else {
            _mesa_glsl_error(& @3, state, "invalid index %d specified", $3);
            YYERROR;
         }
      }

      if ((state->ARB_shading_language_420pack_enable ||
           state->ARB_shader_atomic_counters_enable) &&
          match_layout_qualifier("binding", $1, state) == 0) {
         $$.flags.q.explicit_binding = 1;
         $$.binding = $3;
      }

      if (state->ARB_shader_atomic_counters_enable &&
          match_layout_qualifier("offset", $1, state) == 0) {
         $$.flags.q.explicit_offset = 1;
         $$.offset = $3;
      }

      if (match_layout_qualifier("max_vertices", $1, state) == 0) {
         $$.flags.q.max_vertices = 1;

         if ($3 < 0) {
            _mesa_glsl_error(& @3, state,
                             "invalid max_vertices %d specified", $3);
            YYERROR;
         } else {
            $$.max_vertices = $3;
            if (!state->is_version(150, 0)) {
               _mesa_glsl_error(& @3, state,
                                "#version 150 max_vertices qualifier "
                                "specified", $3);
            }
         }
      }

      if (state->stage == MESA_SHADER_GEOMETRY) {
         if (match_layout_qualifier("stream", $1, state) == 0 &&
             state->check_explicit_attrib_stream_allowed(& @3)) {
            $$.flags.q.stream = 1;

            if ($3 < 0) {
               _mesa_glsl_error(& @3, state,
                                "invalid stream %d specified", $3);
               YYERROR;
            } else {
               $$.flags.q.explicit_stream = 1;
               $$.stream = $3;
            }
         }
      }

      static const char * const local_size_qualifiers[3] = {
         "local_size_x",
         "local_size_y",
         "local_size_z",
      };
      for (int i = 0; i < 3; i++) {
         if (match_layout_qualifier(local_size_qualifiers[i], $1,
                                    state) == 0) {
            if ($3 <= 0) {
               _mesa_glsl_error(& @3, state,
                                "invalid %s of %d specified",
                                local_size_qualifiers[i], $3);
               YYERROR;
            } else if (!state->is_version(430, 0) &&
                       !state->ARB_compute_shader_enable) {
               _mesa_glsl_error(& @3, state,
                                "%s qualifier requires GLSL 4.30 or "
                                "ARB_compute_shader",
                                local_size_qualifiers[i]);
               YYERROR;
            } else {
               $$.flags.q.local_size |= (1 << i);
               $$.local_size[i] = $3;
            }
            break;
         }
      }

      if (match_layout_qualifier("invocations", $1, state) == 0) {
         $$.flags.q.invocations = 1;

         if ($3 <= 0) {
            _mesa_glsl_error(& @3, state,
                             "invalid invocations %d specified", $3);
            YYERROR;
         } else if ($3 > MAX_GEOMETRY_SHADER_INVOCATIONS) {
            _mesa_glsl_error(& @3, state,
                             "invocations (%d) exceeds "
                             "GL_MAX_GEOMETRY_SHADER_INVOCATIONS", $3);
            YYERROR;
         } else {
            $$.invocations = $3;
            if (!state->is_version(400, 0) &&
                !state->ARB_gpu_shader5_enable) {
               _mesa_glsl_error(& @3, state,
                                "GL_ARB_gpu_shader5 invocations "
                                "qualifier specified", $3);
            }
         }
      }

      /* If the identifier didn't match any known layout identifiers,
       * emit an error.
       */
      if (!$$.flags.i) {
         _mesa_glsl_error(& @1, state, "unrecognized layout identifier "
                          "`%s'", $1);
         YYERROR;
      }
   }
   | interface_block_layout_qualifier
   {
      $$ = $1;
      /* Layout qualifiers for ARB_uniform_buffer_object. */
      if ($$.flags.q.uniform && !state->has_uniform_buffer_objects()) {
         _mesa_glsl_error(& @1, state,
                          "#version 140 / GL_ARB_uniform_buffer_object "
                          "layout qualifier `%s' is used", $1);
      } else if ($$.flags.q.uniform && state->ARB_uniform_buffer_object_warn) {
         _mesa_glsl_warning(& @1, state,
                            "#version 140 / GL_ARB_uniform_buffer_object "
                            "layout qualifier `%s' is used", $1);
      }
   }
   ;

/* This is a separate language rule because we parse these as tokens
 * (due to them being reserved keywords) instead of identifiers like
 * most qualifiers.  See the any_identifier path of
 * layout_qualifier_id for the others.
 *
 * Note that since layout qualifiers are case-insensitive in desktop
 * GLSL, all of these qualifiers need to be handled as identifiers as
 * well (by the any_identifier path of layout_qualifier_id).
 */
interface_block_layout_qualifier:
   ROW_MAJOR
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.row_major = 1;
   }
   | PACKED_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.packed = 1;
   }
   ;

interpolation_qualifier:
   SMOOTH
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.smooth = 1;
   }
   | FLAT
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.flat = 1;
   }
   | NOPERSPECTIVE
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.noperspective = 1;
   }
   ;

type_qualifier:
   /* Single qualifiers */
   INVARIANT
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.invariant = 1;
   }
   | PRECISE
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q.precise = 1;
   }
   | auxiliary_storage_qualifier
   | storage_qualifier
   | interpolation_qualifier
   | layout_qualifier
   | precision_qualifier
   {
      memset(&$$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.precision = $1;
   }

   /* Multiple qualifiers:
    * In GLSL 4.20, these can be specified in any order.  In earlier versions,
    * they appear in this order (see GLSL 1.50 section 4.7 & comments below):
    *
    *    invariant interpolation auxiliary storage precision  ...or...
    *    layout storage precision
    *
    * Each qualifier's rule ensures that the accumulated qualifiers on the right
    * side don't contain any that must appear on the left hand side.
    * For example, when processing a storage qualifier, we check that there are
    * no auxiliary, interpolation, layout, invariant, or precise qualifiers to the right.
    */
   | PRECISE type_qualifier
   {
      if ($2.flags.q.precise)
         _mesa_glsl_error(&@1, state, "duplicate \"precise\" qualifier");

      $$ = $2;
      $$.flags.q.precise = 1;
   }
   | INVARIANT type_qualifier
   {
      if ($2.flags.q.invariant)
         _mesa_glsl_error(&@1, state, "duplicate \"invariant\" qualifier");

      if (!state->ARB_shading_language_420pack_enable && $2.flags.q.precise)
         _mesa_glsl_error(&@1, state,
                          "\"invariant\" must come after \"precise\"");

      $$ = $2;
      $$.flags.q.invariant = 1;
   }
   | interpolation_qualifier type_qualifier
   {
      /* Section 4.3 of the GLSL 1.40 specification states:
       * "...qualified with one of these interpolation qualifiers"
       *
       * GLSL 1.30 claims to allow "one or more", but insists that:
       * "These interpolation qualifiers may only precede the qualifiers in,
       *  centroid in, out, or centroid out in a declaration."
       *
       * ...which means that e.g. smooth can't precede smooth, so there can be
       * only one after all, and the 1.40 text is a clarification, not a change.
       */
      if ($2.has_interpolation())
         _mesa_glsl_error(&@1, state, "duplicate interpolation qualifier");

      if (!state->ARB_shading_language_420pack_enable &&
          ($2.flags.q.precise || $2.flags.q.invariant)) {
         _mesa_glsl_error(&@1, state, "interpolation qualifiers must come "
                          "after \"precise\" or \"invariant\"");
      }

      $$ = $1;
      $$.merge_qualifier(&@1, state, $2);
   }
   | layout_qualifier type_qualifier
   {
      /* In the absence of ARB_shading_language_420pack, layout qualifiers may
       * appear no later than auxiliary storage qualifiers. There is no
       * particularly clear spec language mandating this, but in all examples
       * the layout qualifier precedes the storage qualifier.
       *
       * We allow combinations of layout with interpolation, invariant or
       * precise qualifiers since these are useful in ARB_separate_shader_objects.
       * There is no clear spec guidance on this either.
       */
      if (!state->ARB_shading_language_420pack_enable && $2.has_layout())
         _mesa_glsl_error(&@1, state, "duplicate layout(...) qualifiers");

      $$ = $1;
      $$.merge_qualifier(&@1, state, $2);
   }
   | auxiliary_storage_qualifier type_qualifier
   {
      if ($2.has_auxiliary_storage()) {
         _mesa_glsl_error(&@1, state,
                          "duplicate auxiliary storage qualifier (centroid or sample)");
      }

      if (!state->ARB_shading_language_420pack_enable &&
          ($2.flags.q.precise || $2.flags.q.invariant ||
           $2.has_interpolation() || $2.has_layout())) {
         _mesa_glsl_error(&@1, state, "auxiliary storage qualifiers must come "
                          "just before storage qualifiers");
      }
      $$ = $1;
      $$.merge_qualifier(&@1, state, $2);
   }
   | storage_qualifier type_qualifier
   {
      /* Section 4.3 of the GLSL 1.20 specification states:
       * "Variable declarations may have a storage qualifier specified..."
       *  1.30 clarifies this to "may have one storage qualifier".
       */
      if ($2.has_storage())
         _mesa_glsl_error(&@1, state, "duplicate storage qualifier");

      if (!state->ARB_shading_language_420pack_enable &&
          ($2.flags.q.precise || $2.flags.q.invariant || $2.has_interpolation() ||
           $2.has_layout() || $2.has_auxiliary_storage())) {
         _mesa_glsl_error(&@1, state, "storage qualifiers must come after "
                          "precise, invariant, interpolation, layout and auxiliary "
                          "storage qualifiers");
      }

      $$ = $1;
      $$.merge_qualifier(&@1, state, $2);
   }
   | precision_qualifier type_qualifier
   {
      if ($2.precision != ast_precision_none)
         _mesa_glsl_error(&@1, state, "duplicate precision qualifier");

      if (!state->ARB_shading_language_420pack_enable && $2.flags.i != 0)
         _mesa_glsl_error(&@1, state, "precision qualifiers must come last");

      $$ = $2;
      $$.precision = $1;
   }
   ;

auxiliary_storage_qualifier:
   CENTROID
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.centroid = 1;
   }
   | SAMPLE
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q.sample = 1;
   }
   /* TODO: "patch" also goes here someday. */

storage_qualifier:
   CONST_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.constant = 1;
   }
   | ATTRIBUTE
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.attribute = 1;
   }
   | VARYING
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.varying = 1;
   }
   | IN_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.in = 1;
   }
   | OUT_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.out = 1;
   }
   | INOUT_TOK
   {
      memset(& $$, 0, sizeof($$));
      $$.precision = ast_precision_none;
      $$.flags.q.in = 1;
      $$.flags.q.out = 1;

      if (state->stage == MESA_SHADER_GEOMETRY &&
          state->has_explicit_attrib_stream()) {
         /* Section 4.3.8.2 (Output Layout Qualifiers) of the GLSL 4.00
          * spec says:
          *
          *     "If the block or variable is declared with the stream
          *     identifier, it is associated with the specified stream;
          *     otherwise, it is associated with the current default stream."
          */
          $$.flags.q.stream = 1;
          $$.flags.q.explicit_stream = 0;
          $$.stream = state->out_qualifier->stream;
      }
   }
   | UNIFORM
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.uniform = 1;
   }
   | COHERENT
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q.coherent = 1;
   }
   | VOLATILE
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q._volatile = 1;
   }
   | RESTRICT
   {
      STATIC_ASSERT(sizeof($$.flags.q) <= sizeof($$.flags.i));
      memset(& $$, 0, sizeof($$));
      $$.flags.q.restrict_flag = 1;
   }
   | READONLY
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q.read_only = 1;
   }
   | WRITEONLY
   {
      memset(& $$, 0, sizeof($$));
      $$.flags.q.write_only = 1;
   }
   ;

array_specifier:
   '[' ']'
   {
      void *ctx = state;
      $$ = new(ctx) ast_array_specifier(@1);
      $$->set_location_range(@1, @2);
   }
   | '[' constant_expression ']'
   {
      void *ctx = state;
      $$ = new(ctx) ast_array_specifier(@1, $2);
      $$->set_location_range(@1, @3);
   }
   | array_specifier '[' ']'
   {
      $$ = $1;

      if (!state->ARB_arrays_of_arrays_enable) {
         _mesa_glsl_error(& @1, state,
                          "GL_ARB_arrays_of_arrays "
                          "required for defining arrays of arrays");
      } else {
         _mesa_glsl_error(& @1, state,
                          "only the outermost array dimension can "
                          "be unsized");
      }
   }
   | array_specifier '[' constant_expression ']'
   {
      $$ = $1;

      if (!state->ARB_arrays_of_arrays_enable) {
         _mesa_glsl_error(& @1, state,
                          "GL_ARB_arrays_of_arrays "
                          "required for defining arrays of arrays");
      }

      $$->add_dimension($3);
   }
   ;

type_specifier:
   type_specifier_nonarray
   | type_specifier_nonarray array_specifier
   {
      $$ = $1;
      $$->array_specifier = $2;
   }
   ;

type_specifier_nonarray:
   basic_type_specifier_nonarray
   {
      void *ctx = state;
      $$ = new(ctx) ast_type_specifier($1);
      $$->set_location(@1);
   }
   | struct_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_type_specifier($1);
      $$->set_location(@1);
   }
   | TYPE_IDENTIFIER
   {
      void *ctx = state;
      $$ = new(ctx) ast_type_specifier($1);
      $$->set_location(@1);
   }
   ;

basic_type_specifier_nonarray:
   VOID_TOK                 { $$ = "void"; }
   | FLOAT_TOK              { $$ = "float"; }
   | INT_TOK                { $$ = "int"; }
   | UINT_TOK               { $$ = "uint"; }
   | BOOL_TOK               { $$ = "bool"; }
   | VEC2                   { $$ = "vec2"; }
   | VEC3                   { $$ = "vec3"; }
   | VEC4                   { $$ = "vec4"; }
   | BVEC2                  { $$ = "bvec2"; }
   | BVEC3                  { $$ = "bvec3"; }
   | BVEC4                  { $$ = "bvec4"; }
   | IVEC2                  { $$ = "ivec2"; }
   | IVEC3                  { $$ = "ivec3"; }
   | IVEC4                  { $$ = "ivec4"; }
   | UVEC2                  { $$ = "uvec2"; }
   | UVEC3                  { $$ = "uvec3"; }
   | UVEC4                  { $$ = "uvec4"; }
   | MAT2X2                 { $$ = "mat2"; }
   | MAT2X3                 { $$ = "mat2x3"; }
   | MAT2X4                 { $$ = "mat2x4"; }
   | MAT3X2                 { $$ = "mat3x2"; }
   | MAT3X3                 { $$ = "mat3"; }
   | MAT3X4                 { $$ = "mat3x4"; }
   | MAT4X2                 { $$ = "mat4x2"; }
   | MAT4X3                 { $$ = "mat4x3"; }
   | MAT4X4                 { $$ = "mat4"; }
   | SAMPLER1D              { $$ = "sampler1D"; }
   | SAMPLER2D              { $$ = "sampler2D"; }
   | SAMPLER2DRECT          { $$ = "sampler2DRect"; }
   | SAMPLER3D              { $$ = "sampler3D"; }
   | SAMPLERCUBE            { $$ = "samplerCube"; }
   | SAMPLEREXTERNALOES     { $$ = "samplerExternalOES"; }
   | SAMPLER1DSHADOW        { $$ = "sampler1DShadow"; }
   | SAMPLER2DSHADOW        { $$ = "sampler2DShadow"; }
   | SAMPLER2DRECTSHADOW    { $$ = "sampler2DRectShadow"; }
   | SAMPLERCUBESHADOW      { $$ = "samplerCubeShadow"; }
   | SAMPLER1DARRAY         { $$ = "sampler1DArray"; }
   | SAMPLER2DARRAY         { $$ = "sampler2DArray"; }
   | SAMPLER1DARRAYSHADOW   { $$ = "sampler1DArrayShadow"; }
   | SAMPLER2DARRAYSHADOW   { $$ = "sampler2DArrayShadow"; }
   | SAMPLERBUFFER          { $$ = "samplerBuffer"; }
   | SAMPLERCUBEARRAY       { $$ = "samplerCubeArray"; }
   | SAMPLERCUBEARRAYSHADOW { $$ = "samplerCubeArrayShadow"; }
   | ISAMPLER1D             { $$ = "isampler1D"; }
   | ISAMPLER2D             { $$ = "isampler2D"; }
   | ISAMPLER2DRECT         { $$ = "isampler2DRect"; }
   | ISAMPLER3D             { $$ = "isampler3D"; }
   | ISAMPLERCUBE           { $$ = "isamplerCube"; }
   | ISAMPLER1DARRAY        { $$ = "isampler1DArray"; }
   | ISAMPLER2DARRAY        { $$ = "isampler2DArray"; }
   | ISAMPLERBUFFER         { $$ = "isamplerBuffer"; }
   | ISAMPLERCUBEARRAY      { $$ = "isamplerCubeArray"; }
   | USAMPLER1D             { $$ = "usampler1D"; }
   | USAMPLER2D             { $$ = "usampler2D"; }
   | USAMPLER2DRECT         { $$ = "usampler2DRect"; }
   | USAMPLER3D             { $$ = "usampler3D"; }
   | USAMPLERCUBE           { $$ = "usamplerCube"; }
   | USAMPLER1DARRAY        { $$ = "usampler1DArray"; }
   | USAMPLER2DARRAY        { $$ = "usampler2DArray"; }
   | USAMPLERBUFFER         { $$ = "usamplerBuffer"; }
   | USAMPLERCUBEARRAY      { $$ = "usamplerCubeArray"; }
   | SAMPLER2DMS            { $$ = "sampler2DMS"; }
   | ISAMPLER2DMS           { $$ = "isampler2DMS"; }
   | USAMPLER2DMS           { $$ = "usampler2DMS"; }
   | SAMPLER2DMSARRAY       { $$ = "sampler2DMSArray"; }
   | ISAMPLER2DMSARRAY      { $$ = "isampler2DMSArray"; }
   | USAMPLER2DMSARRAY      { $$ = "usampler2DMSArray"; }
   | IMAGE1D                { $$ = "image1D"; }
   | IMAGE2D                { $$ = "image2D"; }
   | IMAGE3D                { $$ = "image3D"; }
   | IMAGE2DRECT            { $$ = "image2DRect"; }
   | IMAGECUBE              { $$ = "imageCube"; }
   | IMAGEBUFFER            { $$ = "imageBuffer"; }
   | IMAGE1DARRAY           { $$ = "image1DArray"; }
   | IMAGE2DARRAY           { $$ = "image2DArray"; }
   | IMAGECUBEARRAY         { $$ = "imageCubeArray"; }
   | IMAGE2DMS              { $$ = "image2DMS"; }
   | IMAGE2DMSARRAY         { $$ = "image2DMSArray"; }
   | IIMAGE1D               { $$ = "iimage1D"; }
   | IIMAGE2D               { $$ = "iimage2D"; }
   | IIMAGE3D               { $$ = "iimage3D"; }
   | IIMAGE2DRECT           { $$ = "iimage2DRect"; }
   | IIMAGECUBE             { $$ = "iimageCube"; }
   | IIMAGEBUFFER           { $$ = "iimageBuffer"; }
   | IIMAGE1DARRAY          { $$ = "iimage1DArray"; }
   | IIMAGE2DARRAY          { $$ = "iimage2DArray"; }
   | IIMAGECUBEARRAY        { $$ = "iimageCubeArray"; }
   | IIMAGE2DMS             { $$ = "iimage2DMS"; }
   | IIMAGE2DMSARRAY        { $$ = "iimage2DMSArray"; }
   | UIMAGE1D               { $$ = "uimage1D"; }
   | UIMAGE2D               { $$ = "uimage2D"; }
   | UIMAGE3D               { $$ = "uimage3D"; }
   | UIMAGE2DRECT           { $$ = "uimage2DRect"; }
   | UIMAGECUBE             { $$ = "uimageCube"; }
   | UIMAGEBUFFER           { $$ = "uimageBuffer"; }
   | UIMAGE1DARRAY          { $$ = "uimage1DArray"; }
   | UIMAGE2DARRAY          { $$ = "uimage2DArray"; }
   | UIMAGECUBEARRAY        { $$ = "uimageCubeArray"; }
   | UIMAGE2DMS             { $$ = "uimage2DMS"; }
   | UIMAGE2DMSARRAY        { $$ = "uimage2DMSArray"; }
   | ATOMIC_UINT            { $$ = "atomic_uint"; }
   ;

precision_qualifier:
   HIGHP
   {
      state->check_precision_qualifiers_allowed(&@1);
      $$ = ast_precision_high;
   }
   | MEDIUMP
   {
      state->check_precision_qualifiers_allowed(&@1);
      $$ = ast_precision_medium;
   }
   | LOWP
   {
      state->check_precision_qualifiers_allowed(&@1);
      $$ = ast_precision_low;
   }
   ;

struct_specifier:
   STRUCT any_identifier '{' struct_declaration_list '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_struct_specifier($2, $4);
      $$->set_location_range(@2, @5);
      state->symbols->add_type($2, glsl_type::void_type);
   }
   | STRUCT '{' struct_declaration_list '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_struct_specifier(NULL, $3);
      $$->set_location_range(@2, @4);
   }
   ;

struct_declaration_list:
   struct_declaration
   {
      $$ = $1;
      $1->link.self_link();
   }
   | struct_declaration_list struct_declaration
   {
      $$ = $1;
      $$->link.insert_before(& $2->link);
   }
   ;

struct_declaration:
   fully_specified_type struct_declarator_list ';'
   {
      void *ctx = state;
      ast_fully_specified_type *const type = $1;
      type->set_location(@1);

      if (type->qualifier.flags.i != 0)
         _mesa_glsl_error(&@1, state,
			  "only precision qualifiers may be applied to "
			  "structure members");

      $$ = new(ctx) ast_declarator_list(type);
      $$->set_location(@2);

      $$->declarations.push_degenerate_list_at_head(& $2->link);
   }
   ;

struct_declarator_list:
   struct_declarator
   {
      $$ = $1;
      $1->link.self_link();
   }
   | struct_declarator_list ',' struct_declarator
   {
      $$ = $1;
      $$->link.insert_before(& $3->link);
   }
   ;

struct_declarator:
   any_identifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_declaration($1, NULL, NULL);
      $$->set_location(@1);
   }
   | any_identifier array_specifier
   {
      void *ctx = state;
      $$ = new(ctx) ast_declaration($1, $2, NULL);
      $$->set_location_range(@1, @2);
   }
   ;

initializer:
   assignment_expression
   | '{' initializer_list '}'
   {
      $$ = $2;
   }
   | '{' initializer_list ',' '}'
   {
      $$ = $2;
   }
   ;

initializer_list:
   initializer
   {
      void *ctx = state;
      $$ = new(ctx) ast_aggregate_initializer();
      $$->set_location(@1);
      $$->expressions.push_tail(& $1->link);
   }
   | initializer_list ',' initializer
   {
      $1->expressions.push_tail(& $3->link);
   }
   ;

declaration_statement:
   declaration
   ;

   // Grammar Note: labeled statements for SWITCH only; 'goto' is not
   // supported.
statement:
   compound_statement        { $$ = (ast_node *) $1; }
   | simple_statement
   ;

simple_statement:
   declaration_statement
   | expression_statement
   | selection_statement
   | switch_statement
   | iteration_statement
   | jump_statement
   ;

compound_statement:
   '{' '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_compound_statement(true, NULL);
      $$->set_location_range(@1, @2);
   }
   | '{'
   {
      state->symbols->push_scope();
   }
   statement_list '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_compound_statement(true, $3);
      $$->set_location_range(@1, @4);
      state->symbols->pop_scope();
   }
   ;

statement_no_new_scope:
   compound_statement_no_new_scope { $$ = (ast_node *) $1; }
   | simple_statement
   ;

compound_statement_no_new_scope:
   '{' '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_compound_statement(false, NULL);
      $$->set_location_range(@1, @2);
   }
   | '{' statement_list '}'
   {
      void *ctx = state;
      $$ = new(ctx) ast_compound_statement(false, $2);
      $$->set_location_range(@1, @3);
   }
   ;

statement_list:
   statement
   {
      if ($1 == NULL) {
         _mesa_glsl_error(& @1, state, "<nil> statement");
         assert($1 != NULL);
      }

      $$ = $1;
      $$->link.self_link();
   }
   | statement_list statement
   {
      if ($2 == NULL) {
         _mesa_glsl_error(& @2, state, "<nil> statement");
         assert($2 != NULL);
      }
      $$ = $1;
      $$->link.insert_before(& $2->link);
   }
   ;

expression_statement:
   ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_statement(NULL);
      $$->set_location(@1);
   }
   | expression ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_expression_statement($1);
      $$->set_location(@1);
   }
   ;

selection_statement:
   IF '(' expression ')' selection_rest_statement
   {
      $$ = new(state) ast_selection_statement($3, $5.then_statement,
                                              $5.else_statement);
      $$->set_location_range(@1, @5);
   }
   ;

selection_rest_statement:
   statement ELSE statement
   {
      $$.then_statement = $1;
      $$.else_statement = $3;
   }
   | statement %prec THEN
   {
      $$.then_statement = $1;
      $$.else_statement = NULL;
   }
   ;

condition:
   expression
   {
      $$ = (ast_node *) $1;
   }
   | fully_specified_type any_identifier '=' initializer
   {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration($2, NULL, $4);
      ast_declarator_list *declarator = new(ctx) ast_declarator_list($1);
      decl->set_location_range(@2, @4);
      declarator->set_location(@1);

      declarator->declarations.push_tail(&decl->link);
      $$ = declarator;
   }
   ;

/*
 * switch_statement grammar is based on the syntax described in the body
 * of the GLSL spec, not in it's appendix!!!
 */
switch_statement:
   SWITCH '(' expression ')' switch_body
   {
      $$ = new(state) ast_switch_statement($3, $5);
      $$->set_location_range(@1, @5);
   }
   ;

switch_body:
   '{' '}'
   {
      $$ = new(state) ast_switch_body(NULL);
      $$->set_location_range(@1, @2);
   }
   | '{' case_statement_list '}'
   {
      $$ = new(state) ast_switch_body($2);
      $$->set_location_range(@1, @3);
   }
   ;

case_label:
   CASE expression ':'
   {
      $$ = new(state) ast_case_label($2);
      $$->set_location(@2);
   }
   | DEFAULT ':'
   {
      $$ = new(state) ast_case_label(NULL);
      $$->set_location(@2);
   }
   ;

case_label_list:
   case_label
   {
      ast_case_label_list *labels = new(state) ast_case_label_list();

      labels->labels.push_tail(& $1->link);
      $$ = labels;
      $$->set_location(@1);
   }
   | case_label_list case_label
   {
      $$ = $1;
      $$->labels.push_tail(& $2->link);
   }
   ;

case_statement:
   case_label_list statement
   {
      ast_case_statement *stmts = new(state) ast_case_statement($1);
      stmts->set_location(@2);

      stmts->stmts.push_tail(& $2->link);
      $$ = stmts;
   }
   | case_statement statement
   {
      $$ = $1;
      $$->stmts.push_tail(& $2->link);
   }
   ;

case_statement_list:
   case_statement
   {
      ast_case_statement_list *cases= new(state) ast_case_statement_list();
      cases->set_location(@1);

      cases->cases.push_tail(& $1->link);
      $$ = cases;
   }
   | case_statement_list case_statement
   {
      $$ = $1;
      $$->cases.push_tail(& $2->link);
   }
   ;

iteration_statement:
   WHILE '(' condition ')' statement_no_new_scope
   {
      void *ctx = state;
      $$ = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
                                            NULL, $3, NULL, $5);
      $$->set_location_range(@1, @4);
   }
   | DO statement WHILE '(' expression ')' ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
                                            NULL, $5, NULL, $2);
      $$->set_location_range(@1, @6);
   }
   | FOR '(' for_init_statement for_rest_statement ')' statement_no_new_scope
   {
      void *ctx = state;
      $$ = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
                                            $3, $4.cond, $4.rest, $6);
      $$->set_location_range(@1, @6);
   }
   ;

for_init_statement:
   expression_statement
   | declaration_statement
   ;

conditionopt:
   condition
   | /* empty */
   {
      $$ = NULL;
   }
   ;

for_rest_statement:
   conditionopt ';'
   {
      $$.cond = $1;
      $$.rest = NULL;
   }
   | conditionopt ';' expression
   {
      $$.cond = $1;
      $$.rest = $3;
   }
   ;

   // Grammar Note: No 'goto'. Gotos are not supported.
jump_statement:
   CONTINUE ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
      $$->set_location(@1);
   }
   | BREAK ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
      $$->set_location(@1);
   }
   | RETURN ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
      $$->set_location(@1);
   }
   | RETURN expression ';'
   {
      void *ctx = state;
      $$ = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, $2);
      $$->set_location_range(@1, @2);
   }
   | DISCARD ';' // Fragment shader only.
   {
      void *ctx = state;
      $$ = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
      $$->set_location(@1);
   }
   ;

external_declaration:
   function_definition      { $$ = $1; }
   | declaration            { $$ = $1; }
   | pragma_statement       { $$ = NULL; }
   | layout_defaults        { $$ = $1; }
   ;

function_definition:
   function_prototype compound_statement_no_new_scope
   {
      void *ctx = state;
      $$ = new(ctx) ast_function_definition();
      $$->set_location_range(@1, @2);
      $$->prototype = $1;
      $$->body = $2;

      state->symbols->pop_scope();
   }
   ;

/* layout_qualifieropt is packed into this rule */
interface_block:
   basic_interface_block
   {
      $$ = $1;
   }
   | layout_qualifier basic_interface_block
   {
      ast_interface_block *block = $2;
      if (!block->layout.merge_qualifier(& @1, state, $1)) {
         YYERROR;
      }

      foreach_list_typed (ast_declarator_list, member, link, &block->declarations) {
         ast_type_qualifier& qualifier = member->type->qualifier;
         if (qualifier.flags.q.stream && qualifier.stream != block->layout.stream) {
               _mesa_glsl_error(& @1, state,
                             "stream layout qualifier on "
                             "interface block member does not match "
                             "the interface block (%d vs %d)",
                             qualifier.stream, block->layout.stream);
               YYERROR;
         }
      }
      $$ = block;
   }
   ;

basic_interface_block:
   interface_qualifier NEW_IDENTIFIER '{' member_list '}' instance_name_opt ';'
   {
      ast_interface_block *const block = $6;

      block->block_name = $2;
      block->declarations.push_degenerate_list_at_head(& $4->link);

      if ($1.flags.q.uniform) {
         if (!state->has_uniform_buffer_objects()) {
            _mesa_glsl_error(& @1, state,
                             "#version 140 / GL_ARB_uniform_buffer_object "
                             "required for defining uniform blocks");
         } else if (state->ARB_uniform_buffer_object_warn) {
            _mesa_glsl_warning(& @1, state,
                               "#version 140 / GL_ARB_uniform_buffer_object "
                               "required for defining uniform blocks");
         }
      } else {
         if (state->es_shader || state->language_version < 150) {
            _mesa_glsl_error(& @1, state,
                             "#version 150 required for using "
                             "interface blocks");
         }
      }

      /* From the GLSL 1.50.11 spec, section 4.3.7 ("Interface Blocks"):
       * "It is illegal to have an input block in a vertex shader
       *  or an output block in a fragment shader"
       */
      if ((state->stage == MESA_SHADER_VERTEX) && $1.flags.q.in) {
         _mesa_glsl_error(& @1, state,
                          "`in' interface block is not allowed for "
                          "a vertex shader");
      } else if ((state->stage == MESA_SHADER_FRAGMENT) && $1.flags.q.out) {
         _mesa_glsl_error(& @1, state,
                          "`out' interface block is not allowed for "
                          "a fragment shader");
      }

      /* Since block arrays require names, and both features are added in
       * the same language versions, we don't have to explicitly
       * version-check both things.
       */
      if (block->instance_name != NULL) {
         state->check_version(150, 300, & @1, "interface blocks with "
                               "an instance name are not allowed");
      }

      uint64_t interface_type_mask;
      struct ast_type_qualifier temp_type_qualifier;

      /* Get a bitmask containing only the in/out/uniform flags, allowing us
       * to ignore other irrelevant flags like interpolation qualifiers.
       */
      temp_type_qualifier.flags.i = 0;
      temp_type_qualifier.flags.q.uniform = true;
      temp_type_qualifier.flags.q.in = true;
      temp_type_qualifier.flags.q.out = true;
      interface_type_mask = temp_type_qualifier.flags.i;

      /* Get the block's interface qualifier.  The interface_qualifier
       * production rule guarantees that only one bit will be set (and
       * it will be in/out/uniform).
       */
      uint64_t block_interface_qualifier = $1.flags.i;

      block->layout.flags.i |= block_interface_qualifier;

      if (state->stage == MESA_SHADER_GEOMETRY &&
          state->has_explicit_attrib_stream()) {
         /* Assign global layout's stream value. */
         block->layout.flags.q.stream = 1;
         block->layout.flags.q.explicit_stream = 0;
         block->layout.stream = state->out_qualifier->stream;
      }

      foreach_list_typed (ast_declarator_list, member, link, &block->declarations) {
         ast_type_qualifier& qualifier = member->type->qualifier;
         if ((qualifier.flags.i & interface_type_mask) == 0) {
            /* GLSLangSpec.1.50.11, 4.3.7 (Interface Blocks):
             * "If no optional qualifier is used in a member declaration, the
             *  qualifier of the variable is just in, out, or uniform as declared
             *  by interface-qualifier."
             */
            qualifier.flags.i |= block_interface_qualifier;
         } else if ((qualifier.flags.i & interface_type_mask) !=
                    block_interface_qualifier) {
            /* GLSLangSpec.1.50.11, 4.3.7 (Interface Blocks):
             * "If optional qualifiers are used, they can include interpolation
             *  and storage qualifiers and they must declare an input, output,
             *  or uniform variable consistent with the interface qualifier of
             *  the block."
             */
            _mesa_glsl_error(& @1, state,
                             "uniform/in/out qualifier on "
                             "interface block member does not match "
                             "the interface block");
         }
      }

      $$ = block;
   }
   ;

interface_qualifier:
   IN_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.in = 1;
   }
   | OUT_TOK
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.out = 1;
   }
   | UNIFORM
   {
      memset(& $$, 0, sizeof($$));
	  $$.precision = ast_precision_none;
      $$.flags.q.uniform = 1;
   }
   ;

instance_name_opt:
   /* empty */
   {
      $$ = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          NULL, NULL);
   }
   | NEW_IDENTIFIER
   {
      $$ = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          $1, NULL);
      $$->set_location(@1);
   }
   | NEW_IDENTIFIER array_specifier
   {
      $$ = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          $1, $2);
      $$->set_location_range(@1, @2);
   }
   ;

member_list:
   member_declaration
   {
      $$ = $1;
      $1->link.self_link();
   }
   | member_declaration member_list
   {
      $$ = $1;
      $2->link.insert_before(& $$->link);
   }
   ;

member_declaration:
   fully_specified_type struct_declarator_list ';'
   {
      void *ctx = state;
      ast_fully_specified_type *type = $1;
      type->set_location(@1);

      if (type->qualifier.flags.q.attribute) {
         _mesa_glsl_error(& @1, state,
                          "keyword 'attribute' cannot be used with "
                          "interface block member");
      } else if (type->qualifier.flags.q.varying) {
         _mesa_glsl_error(& @1, state,
                          "keyword 'varying' cannot be used with "
                          "interface block member");
      }

      $$ = new(ctx) ast_declarator_list(type);
      $$->set_location(@2);

      $$->declarations.push_degenerate_list_at_head(& $2->link);
   }
   ;

layout_defaults:
   layout_qualifier UNIFORM ';'
   {
      if (!state->default_uniform_qualifier->merge_qualifier(& @1, state, $1)) {
         YYERROR;
      }
      $$ = NULL;
   }

   | layout_qualifier IN_TOK ';'
   {
      $$ = NULL;
      if (!state->in_qualifier->merge_in_qualifier(& @1, state, $1, $$)) {
         YYERROR;
      }
   }

   | layout_qualifier OUT_TOK ';'
   {
      if (state->stage != MESA_SHADER_GEOMETRY) {
         _mesa_glsl_error(& @1, state,
                          "out layout qualifiers only valid in "
                          "geometry shaders");
      } else {
         if ($1.flags.q.prim_type) {
            /* Make sure this is a valid output primitive type. */
            switch ($1.prim_type) {
            case GL_POINTS:
            case GL_LINE_STRIP:
            case GL_TRIANGLE_STRIP:
               break;
            default:
               _mesa_glsl_error(&@1, state, "invalid geometry shader output "
                                "primitive type");
               break;
            }
         }
         if (!state->out_qualifier->merge_qualifier(& @1, state, $1))
            YYERROR;

         /* Allow future assigments of global out's stream id value */
         state->out_qualifier->flags.q.explicit_stream = 0;
      }
      $$ = NULL;
   }

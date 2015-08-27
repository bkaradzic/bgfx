%{
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#include "glcpp.h"
#include "main/core.h" /* for struct gl_extensions */
#include "main/mtypes.h" /* for gl_api enum */

static void
yyerror (YYLTYPE *locp, glcpp_parser_t *parser, const char *error);

static void
_define_object_macro (glcpp_parser_t *parser,
		      YYLTYPE *loc,
		      const char *macro,
		      token_list_t *replacements);

static void
_define_function_macro (glcpp_parser_t *parser,
			YYLTYPE *loc,
			const char *macro,
			string_list_t *parameters,
			token_list_t *replacements);

static string_list_t *
_string_list_create (void *ctx);

static void
_string_list_append_item (string_list_t *list, const char *str);

static int
_string_list_contains (string_list_t *list, const char *member, int *index);

static const char *
_string_list_has_duplicate (string_list_t *list);

static int
_string_list_length (string_list_t *list);

static int
_string_list_equal (string_list_t *a, string_list_t *b);

static argument_list_t *
_argument_list_create (void *ctx);

static void
_argument_list_append (argument_list_t *list, token_list_t *argument);

static int
_argument_list_length (argument_list_t *list);

static token_list_t *
_argument_list_member_at (argument_list_t *list, int index);

/* Note: This function ralloc_steal()s the str pointer. */
static token_t *
_token_create_str (void *ctx, int type, char *str);

static token_t *
_token_create_ival (void *ctx, int type, int ival);

static token_list_t *
_token_list_create (void *ctx);

static void
_token_list_append (token_list_t *list, token_t *token);

static void
_token_list_append_list (token_list_t *list, token_list_t *tail);

static int
_token_list_equal_ignoring_space (token_list_t *a, token_list_t *b);

static void
_parser_active_list_push (glcpp_parser_t *parser,
			  const char *identifier,
			  token_node_t *marker);

static void
_parser_active_list_pop (glcpp_parser_t *parser);

static int
_parser_active_list_contains (glcpp_parser_t *parser, const char *identifier);

typedef enum {
	EXPANSION_MODE_IGNORE_DEFINED,
	EXPANSION_MODE_EVALUATE_DEFINED
} expansion_mode_t;

/* Expand list, and begin lexing from the result (after first
 * prefixing a token of type 'head_token_type').
 */
static void
_glcpp_parser_expand_and_lex_from (glcpp_parser_t *parser,
				   int head_token_type,
				   token_list_t *list,
				   expansion_mode_t mode);

/* Perform macro expansion in-place on the given list. */
static void
_glcpp_parser_expand_token_list (glcpp_parser_t *parser,
				 token_list_t *list,
				 expansion_mode_t mode);

static void
_glcpp_parser_print_expanded_token_list (glcpp_parser_t *parser,
					 token_list_t *list);

static void
_glcpp_parser_skip_stack_push_if (glcpp_parser_t *parser, YYLTYPE *loc,
				  int condition);

static void
_glcpp_parser_skip_stack_change_if (glcpp_parser_t *parser, YYLTYPE *loc,
				    const char *type, int condition);

static void
_glcpp_parser_skip_stack_pop (glcpp_parser_t *parser, YYLTYPE *loc);

static void
_glcpp_parser_handle_version_declaration(glcpp_parser_t *parser, intmax_t version,
                                         const char *ident, bool explicitly_set);

static int
glcpp_parser_lex (YYSTYPE *yylval, YYLTYPE *yylloc, glcpp_parser_t *parser);

static void
glcpp_parser_lex_from (glcpp_parser_t *parser, token_list_t *list);

static void
add_builtin_define(glcpp_parser_t *parser, const char *name, int value);

%}

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

%parse-param {glcpp_parser_t *parser}
%lex-param {glcpp_parser_t *parser}

%expect 0

	/* We use HASH_TOKEN, DEFINE_TOKEN and VERSION_TOKEN (as opposed to
         * HASH, DEFINE, and VERSION) to avoid conflicts with other symbols,
         * (such as the <HASH> and <DEFINE> start conditions in the lexer). */
%token DEFINED ELIF_EXPANDED HASH_TOKEN DEFINE_TOKEN FUNC_IDENTIFIER OBJ_IDENTIFIER ELIF ELSE ENDIF ERROR_TOKEN IF IFDEF IFNDEF LINE PRAGMA UNDEF VERSION_TOKEN GARBAGE IDENTIFIER IF_EXPANDED INTEGER INTEGER_STRING LINE_EXPANDED NEWLINE OTHER PLACEHOLDER SPACE PLUS_PLUS MINUS_MINUS
%token PASTE
%type <ival> INTEGER operator SPACE integer_constant
%type <expression_value> expression
%type <str> IDENTIFIER FUNC_IDENTIFIER OBJ_IDENTIFIER INTEGER_STRING OTHER ERROR_TOKEN PRAGMA
%type <string_list> identifier_list
%type <token> preprocessing_token
%type <token_list> pp_tokens replacement_list text_line
%left OR
%left AND
%left '|'
%left '^'
%left '&'
%left EQUAL NOT_EQUAL
%left '<' '>' LESS_OR_EQUAL GREATER_OR_EQUAL
%left LEFT_SHIFT RIGHT_SHIFT
%left '+' '-'
%left '*' '/' '%'
%right UNARY

%debug

%%

input:
	/* empty */
|	input line
;

line:
	control_line
|	SPACE control_line
|	text_line {
		_glcpp_parser_print_expanded_token_list (parser, $1);
		ralloc_asprintf_rewrite_tail (&parser->output, &parser->output_length, "\n");
		ralloc_free ($1);
	}
|	expanded_line
;

expanded_line:
	IF_EXPANDED expression NEWLINE {
		if (parser->is_gles && $2.undefined_macro)
			glcpp_error(& @1, parser, "undefined macro %s in expression (illegal in GLES)", $2.undefined_macro);
		_glcpp_parser_skip_stack_push_if (parser, & @1, $2.value);
	}
|	ELIF_EXPANDED expression NEWLINE {
		if (parser->is_gles && $2.undefined_macro)
			glcpp_error(& @1, parser, "undefined macro %s in expression (illegal in GLES)", $2.undefined_macro);
		_glcpp_parser_skip_stack_change_if (parser, & @1, "elif", $2.value);
	}
|	LINE_EXPANDED integer_constant NEWLINE {
		parser->has_new_line_number = 1;
		parser->new_line_number = $2;
		ralloc_asprintf_rewrite_tail (&parser->output,
					      &parser->output_length,
					      "#line %" PRIiMAX "\n",
					      $2);
	}
|	LINE_EXPANDED integer_constant integer_constant NEWLINE {
		parser->has_new_line_number = 1;
		parser->new_line_number = $2;
		parser->has_new_source_number = 1;
		parser->new_source_number = $3;
		ralloc_asprintf_rewrite_tail (&parser->output,
					      &parser->output_length,
					      "#line %" PRIiMAX " %" PRIiMAX "\n",
					      $2, $3);
	}
;

define:
	OBJ_IDENTIFIER replacement_list NEWLINE {
		_define_object_macro (parser, & @1, $1, $2);
	}
|	FUNC_IDENTIFIER '(' ')' replacement_list NEWLINE {
		_define_function_macro (parser, & @1, $1, NULL, $4);
	}
|	FUNC_IDENTIFIER '(' identifier_list ')' replacement_list NEWLINE {
		_define_function_macro (parser, & @1, $1, $3, $5);
	}
;

control_line:
	control_line_success {
		ralloc_asprintf_rewrite_tail (&parser->output, &parser->output_length, "\n");
	}
|	control_line_error
|	HASH_TOKEN LINE {
		glcpp_parser_resolve_implicit_version(parser);
	} pp_tokens NEWLINE {

		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   LINE_EXPANDED, $4,
							   EXPANSION_MODE_IGNORE_DEFINED);
		}
	}
;

control_line_success:
	HASH_TOKEN DEFINE_TOKEN {
		glcpp_parser_resolve_implicit_version(parser);
	} define
|	HASH_TOKEN UNDEF {
		glcpp_parser_resolve_implicit_version(parser);
	} IDENTIFIER NEWLINE {
		macro_t *macro;
		if (strcmp("__LINE__", $4) == 0
		    || strcmp("__FILE__", $4) == 0
		    || strcmp("__VERSION__", $4) == 0)
			glcpp_error(& @1, parser, "Built-in (pre-defined)"
				    " macro names can not be undefined.");

		macro = hash_table_find (parser->defines, $4);
		if (macro) {
			hash_table_remove (parser->defines, $4);
			ralloc_free (macro);
		}
		ralloc_free ($4);
	}
|	HASH_TOKEN IF {
		glcpp_parser_resolve_implicit_version(parser);
	} pp_tokens NEWLINE {
		/* Be careful to only evaluate the 'if' expression if
		 * we are not skipping. When we are skipping, we
		 * simply push a new 0-valued 'if' onto the skip
		 * stack.
		 *
		 * This avoids generating diagnostics for invalid
		 * expressions that are being skipped. */
		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   IF_EXPANDED, $4,
							   EXPANSION_MODE_EVALUATE_DEFINED);
		}	
		else
		{
			_glcpp_parser_skip_stack_push_if (parser, & @1, 0);
			parser->skip_stack->type = SKIP_TO_ENDIF;
		}
	}
|	HASH_TOKEN IF NEWLINE {
		/* #if without an expression is only an error if we
		 *  are not skipping */
		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			glcpp_error(& @1, parser, "#if with no expression");
		}	
		_glcpp_parser_skip_stack_push_if (parser, & @1, 0);
	}
|	HASH_TOKEN IFDEF {
		glcpp_parser_resolve_implicit_version(parser);
	} IDENTIFIER junk NEWLINE {
		macro_t *macro = hash_table_find (parser->defines, $4);
		ralloc_free ($4);
		_glcpp_parser_skip_stack_push_if (parser, & @1, macro != NULL);
	}
|	HASH_TOKEN IFNDEF {
		glcpp_parser_resolve_implicit_version(parser);
	} IDENTIFIER junk NEWLINE {
		macro_t *macro = hash_table_find (parser->defines, $4);
		ralloc_free ($4);
		_glcpp_parser_skip_stack_push_if (parser, & @3, macro == NULL);
	}
|	HASH_TOKEN ELIF pp_tokens NEWLINE {
		/* Be careful to only evaluate the 'elif' expression
		 * if we are not skipping. When we are skipping, we
		 * simply change to a 0-valued 'elif' on the skip
		 * stack.
		 *
		 * This avoids generating diagnostics for invalid
		 * expressions that are being skipped. */
		if (parser->skip_stack &&
		    parser->skip_stack->type == SKIP_TO_ELSE)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   ELIF_EXPANDED, $3,
							   EXPANSION_MODE_EVALUATE_DEFINED);
		}
		else if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& @1, parser, "#elif after #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & @1,
							    "elif", 0);
		}
	}
|	HASH_TOKEN ELIF NEWLINE {
		/* #elif without an expression is an error unless we
		 * are skipping. */
		if (parser->skip_stack &&
		    parser->skip_stack->type == SKIP_TO_ELSE)
		{
			glcpp_error(& @1, parser, "#elif with no expression");
		}
		else if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& @1, parser, "#elif after #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & @1,
							    "elif", 0);
			glcpp_warning(& @1, parser, "ignoring illegal #elif without expression");
		}
	}
|	HASH_TOKEN ELSE { parser->lexing_directive = 1; } NEWLINE {
		if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& @1, parser, "multiple #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & @1, "else", 1);
			if (parser->skip_stack)
				parser->skip_stack->has_else = true;
		}
	}
|	HASH_TOKEN ENDIF {
		_glcpp_parser_skip_stack_pop (parser, & @1);
	} NEWLINE
|	HASH_TOKEN VERSION_TOKEN integer_constant NEWLINE {
		if (parser->version_resolved) {
			glcpp_error(& @1, parser, "#version must appear on the first line");
		}
		_glcpp_parser_handle_version_declaration(parser, $3, NULL, true);
	}
|	HASH_TOKEN VERSION_TOKEN integer_constant IDENTIFIER NEWLINE {
		if (parser->version_resolved) {
			glcpp_error(& @1, parser, "#version must appear on the first line");
		}
		_glcpp_parser_handle_version_declaration(parser, $3, $4, true);
	}
|	HASH_TOKEN NEWLINE {
		glcpp_parser_resolve_implicit_version(parser);
	}
|	HASH_TOKEN PRAGMA NEWLINE {
		ralloc_asprintf_rewrite_tail (&parser->output, &parser->output_length, "#%s", $2);
	}
;

control_line_error:
	HASH_TOKEN ERROR_TOKEN NEWLINE {
		glcpp_error(& @1, parser, "#%s", $2);
	}
|	HASH_TOKEN DEFINE_TOKEN NEWLINE {
		glcpp_error (& @1, parser, "#define without macro name");
	}
|	HASH_TOKEN GARBAGE pp_tokens NEWLINE  {
		glcpp_error (& @1, parser, "Illegal non-directive after #");
	}
;

integer_constant:
	INTEGER_STRING {
		if (strlen ($1) >= 3 && strncmp ($1, "0x", 2) == 0) {
			$$ = (int)strtoll ($1 + 2, NULL, 16);
		} else if ($1[0] == '0') {
			$$ = (int)strtoll ($1, NULL, 8);
		} else {
			$$ = (int)strtoll ($1, NULL, 10);
		}
	}
|	INTEGER {
		$$ = $1;
	}

expression:
	integer_constant {
		$$.value = $1;
		$$.undefined_macro = NULL;
	}
|	IDENTIFIER {
		$$.value = 0;
		if (parser->is_gles)
			$$.undefined_macro = ralloc_strdup (parser, $1);
		else
			$$.undefined_macro = NULL;
	}
|	expression OR expression {
		$$.value = $1.value || $3.value;

		/* Short-circuit: Only flag undefined from right side
		 * if left side evaluates to false.
		 */
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else if (! $1.value)
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression AND expression {
		$$.value = $1.value && $3.value;

		/* Short-circuit: Only flag undefined from right-side
		 * if left side evaluates to true.
		 */
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else if ($1.value)
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '|' expression {
		$$.value = $1.value | $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '^' expression {
		$$.value = $1.value ^ $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '&' expression {
		$$.value = $1.value & $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression NOT_EQUAL expression {
		$$.value = $1.value != $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression EQUAL expression {
		$$.value = $1.value == $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression GREATER_OR_EQUAL expression {
		$$.value = $1.value >= $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression LESS_OR_EQUAL expression {
		$$.value = $1.value <= $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '>' expression {
		$$.value = $1.value > $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '<' expression {
		$$.value = $1.value < $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression RIGHT_SHIFT expression {
		$$.value = $1.value >> $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression LEFT_SHIFT expression {
		$$.value = $1.value << $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '-' expression {
		$$.value = $1.value - $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '+' expression {
		$$.value = $1.value + $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '%' expression {
		if ($3.value == 0) {
			yyerror (& @1, parser,
				 "zero modulus in preprocessor directive");
		} else {
			$$.value = $1.value % $3.value;
		}
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '/' expression {
		if ($3.value == 0) {
			yyerror (& @1, parser,
				 "division by 0 in preprocessor directive");
		} else {
			$$.value = $1.value / $3.value;
		}
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	expression '*' expression {
		$$.value = $1.value * $3.value;
		if ($1.undefined_macro)
			$$.undefined_macro = $1.undefined_macro;
                else
			$$.undefined_macro = $3.undefined_macro;
	}
|	'!' expression %prec UNARY {
		$$.value = ! $2.value;
		$$.undefined_macro = $2.undefined_macro;
	}
|	'~' expression %prec UNARY {
		$$.value = ~ $2.value;
		$$.undefined_macro = $2.undefined_macro;
	}
|	'-' expression %prec UNARY {
		$$.value = - $2.value;
		$$.undefined_macro = $2.undefined_macro;
	}
|	'+' expression %prec UNARY {
		$$.value = + $2.value;
		$$.undefined_macro = $2.undefined_macro;
	}
|	'(' expression ')' {
		$$ = $2;
	}
;

identifier_list:
	IDENTIFIER {
		$$ = _string_list_create (parser);
		_string_list_append_item ($$, $1);
		ralloc_steal ($$, $1);
	}
|	identifier_list ',' IDENTIFIER {
		$$ = $1;	
		_string_list_append_item ($$, $3);
		ralloc_steal ($$, $3);
	}
;

text_line:
	NEWLINE { $$ = NULL; }
|	pp_tokens NEWLINE
;

replacement_list:
	/* empty */ { $$ = NULL; }
|	pp_tokens
;

junk:
	/* empty */
|	pp_tokens {
		glcpp_error(&@1, parser, "extra tokens at end of directive");
	}
;

pp_tokens:
	preprocessing_token {
		parser->space_tokens = 1;
		$$ = _token_list_create (parser);
		_token_list_append ($$, $1);
	}
|	pp_tokens preprocessing_token {
		$$ = $1;
		_token_list_append ($$, $2);
	}
;

preprocessing_token:
	IDENTIFIER {
		$$ = _token_create_str (parser, IDENTIFIER, $1);
		$$->location = yylloc;
	}
|	INTEGER_STRING {
		$$ = _token_create_str (parser, INTEGER_STRING, $1);
		$$->location = yylloc;
	}
|	operator {
		$$ = _token_create_ival (parser, $1, $1);
		$$->location = yylloc;
	}
|	DEFINED {
		$$ = _token_create_ival (parser, DEFINED, DEFINED);
		$$->location = yylloc;
	}
|	OTHER {
		$$ = _token_create_str (parser, OTHER, $1);
		$$->location = yylloc;
	}
|	SPACE {
		$$ = _token_create_ival (parser, SPACE, SPACE);
		$$->location = yylloc;
	}
;

operator:
	'['			{ $$ = '['; }
|	']'			{ $$ = ']'; }
|	'('			{ $$ = '('; }
|	')'			{ $$ = ')'; }
|	'{'			{ $$ = '{'; }
|	'}'			{ $$ = '}'; }
|	'.'			{ $$ = '.'; }
|	'&'			{ $$ = '&'; }
|	'*'			{ $$ = '*'; }
|	'+'			{ $$ = '+'; }
|	'-'			{ $$ = '-'; }
|	'~'			{ $$ = '~'; }
|	'!'			{ $$ = '!'; }
|	'/'			{ $$ = '/'; }
|	'%'			{ $$ = '%'; }
|	LEFT_SHIFT		{ $$ = LEFT_SHIFT; }
|	RIGHT_SHIFT		{ $$ = RIGHT_SHIFT; }
|	'<'			{ $$ = '<'; }
|	'>'			{ $$ = '>'; }
|	LESS_OR_EQUAL		{ $$ = LESS_OR_EQUAL; }
|	GREATER_OR_EQUAL	{ $$ = GREATER_OR_EQUAL; }
|	EQUAL			{ $$ = EQUAL; }
|	NOT_EQUAL		{ $$ = NOT_EQUAL; }
|	'^'			{ $$ = '^'; }
|	'|'			{ $$ = '|'; }
|	AND			{ $$ = AND; }
|	OR			{ $$ = OR; }
|	';'			{ $$ = ';'; }
|	','			{ $$ = ','; }
|	'='			{ $$ = '='; }
|	PASTE			{ $$ = PASTE; }
|	PLUS_PLUS		{ $$ = PLUS_PLUS; }
|	MINUS_MINUS		{ $$ = MINUS_MINUS; }
;

%%

string_list_t *
_string_list_create (void *ctx)
{
	string_list_t *list;

	list = ralloc (ctx, string_list_t);
	list->head = NULL;
	list->tail = NULL;

	return list;
}

void
_string_list_append_item (string_list_t *list, const char *str)
{
	string_node_t *node;

	node = ralloc (list, string_node_t);
	node->str = ralloc_strdup (node, str);

	node->next = NULL;

	if (list->head == NULL) {
		list->head = node;
	} else {
		list->tail->next = node;
	}

	list->tail = node;
}

int
_string_list_contains (string_list_t *list, const char *member, int *index)
{
	string_node_t *node;
	int i;

	if (list == NULL)
		return 0;

	for (i = 0, node = list->head; node; i++, node = node->next) {
		if (strcmp (node->str, member) == 0) {
			if (index)
				*index = i;
			return 1;
		}
	}

	return 0;
}

/* Return duplicate string in list (if any), NULL otherwise. */
const char *
_string_list_has_duplicate (string_list_t *list)
{
	string_node_t *node, *dup;

	if (list == NULL)
		return NULL;

	for (node = list->head; node; node = node->next) {
		for (dup = node->next; dup; dup = dup->next) {
			if (strcmp (node->str, dup->str) == 0)
				return node->str;
		}
	}

	return NULL;
}

int
_string_list_length (string_list_t *list)
{
	int length = 0;
	string_node_t *node;

	if (list == NULL)
		return 0;

	for (node = list->head; node; node = node->next)
		length++;

	return length;
}

int
_string_list_equal (string_list_t *a, string_list_t *b)
{
	string_node_t *node_a, *node_b;

	if (a == NULL && b == NULL)
		return 1;

	if (a == NULL || b == NULL)
		return 0;

	for (node_a = a->head, node_b = b->head;
	     node_a && node_b;
	     node_a = node_a->next, node_b = node_b->next)
	{
		if (strcmp (node_a->str, node_b->str))
			return 0;
	}

	/* Catch the case of lists being different lengths, (which
	 * would cause the loop above to terminate after the shorter
	 * list). */
	return node_a == node_b;
}

argument_list_t *
_argument_list_create (void *ctx)
{
	argument_list_t *list;

	list = ralloc (ctx, argument_list_t);
	list->head = NULL;
	list->tail = NULL;

	return list;
}

void
_argument_list_append (argument_list_t *list, token_list_t *argument)
{
	argument_node_t *node;

	node = ralloc (list, argument_node_t);
	node->argument = argument;

	node->next = NULL;

	if (list->head == NULL) {
		list->head = node;
	} else {
		list->tail->next = node;
	}

	list->tail = node;
}

int
_argument_list_length (argument_list_t *list)
{
	int length = 0;
	argument_node_t *node;

	if (list == NULL)
		return 0;

	for (node = list->head; node; node = node->next)
		length++;

	return length;
}

token_list_t *
_argument_list_member_at (argument_list_t *list, int index)
{
	argument_node_t *node;
	int i;

	if (list == NULL)
		return NULL;

	node = list->head;
	for (i = 0; i < index; i++) {
		node = node->next;
		if (node == NULL)
			break;
	}

	if (node)
		return node->argument;

	return NULL;
}

/* Note: This function ralloc_steal()s the str pointer. */
token_t *
_token_create_str (void *ctx, int type, char *str)
{
	token_t *token;

	token = ralloc (ctx, token_t);
	token->type = type;
	token->value.str = str;

	ralloc_steal (token, str);

	return token;
}

token_t *
_token_create_ival (void *ctx, int type, int ival)
{
	token_t *token;

	token = ralloc (ctx, token_t);
	token->type = type;
	token->value.ival = ival;

	return token;
}

token_list_t *
_token_list_create (void *ctx)
{
	token_list_t *list;

	list = ralloc (ctx, token_list_t);
	list->head = NULL;
	list->tail = NULL;
	list->non_space_tail = NULL;

	return list;
}

void
_token_list_append (token_list_t *list, token_t *token)
{
	token_node_t *node;

	node = ralloc (list, token_node_t);
	node->token = token;
	node->next = NULL;

	if (list->head == NULL) {
		list->head = node;
	} else {
		list->tail->next = node;
	}

	list->tail = node;
	if (token->type != SPACE)
		list->non_space_tail = node;
}

void
_token_list_append_list (token_list_t *list, token_list_t *tail)
{
	if (tail == NULL || tail->head == NULL)
		return;

	if (list->head == NULL) {
		list->head = tail->head;
	} else {
		list->tail->next = tail->head;
	}

	list->tail = tail->tail;
	list->non_space_tail = tail->non_space_tail;
}

static token_list_t *
_token_list_copy (void *ctx, token_list_t *other)
{
	token_list_t *copy;
	token_node_t *node;

	if (other == NULL)
		return NULL;

	copy = _token_list_create (ctx);
	for (node = other->head; node; node = node->next) {
		token_t *new_token = ralloc (copy, token_t);
		*new_token = *node->token;
		_token_list_append (copy, new_token);
	}

	return copy;
}

static void
_token_list_trim_trailing_space (token_list_t *list)
{
	token_node_t *tail, *next;

	if (list->non_space_tail) {
		tail = list->non_space_tail->next;
		list->non_space_tail->next = NULL;
		list->tail = list->non_space_tail;

		while (tail) {
			next = tail->next;
			ralloc_free (tail);
			tail = next;
		}
	}
}

static int
_token_list_is_empty_ignoring_space (token_list_t *l)
{
	token_node_t *n;

	if (l == NULL)
		return 1;

	n = l->head;
	while (n != NULL && n->token->type == SPACE)
		n = n->next;

	return n == NULL;
}

int
_token_list_equal_ignoring_space (token_list_t *a, token_list_t *b)
{
	token_node_t *node_a, *node_b;

	if (a == NULL || b == NULL) {
		int a_empty = _token_list_is_empty_ignoring_space(a);
		int b_empty = _token_list_is_empty_ignoring_space(b);
		return a_empty == b_empty;
	}

	node_a = a->head;
	node_b = b->head;

	while (1)
	{
		if (node_a == NULL && node_b == NULL)
			break;

		if (node_a == NULL || node_b == NULL)
			return 0;
		/* Make sure whitespace appears in the same places in both.
		 * It need not be exactly the same amount of whitespace,
		 * though.
		 */
		if (node_a->token->type == SPACE
		    && node_b->token->type == SPACE) {
			while (node_a->token->type == SPACE)
				node_a = node_a->next;
			while (node_b->token->type == SPACE)
				node_b = node_b->next;
			continue;
		}

		if (node_a->token->type != node_b->token->type)
			return 0;

		switch (node_a->token->type) {
		case INTEGER:
			if (node_a->token->value.ival != 
			    node_b->token->value.ival)
			{
				return 0;
			}
			break;
		case IDENTIFIER:
		case INTEGER_STRING:
		case OTHER:
			if (strcmp (node_a->token->value.str,
				    node_b->token->value.str))
			{
				return 0;
			}
			break;
		}

		node_a = node_a->next;
		node_b = node_b->next;
	}

	return 1;
}

static void
_token_print (char **out, size_t *len, token_t *token)
{
	if (token->type < 256) {
		ralloc_asprintf_rewrite_tail (out, len, "%c", token->type);
		return;
	}

	switch (token->type) {
	case INTEGER:
		ralloc_asprintf_rewrite_tail (out, len, "%" PRIiMAX, token->value.ival);
		break;
	case IDENTIFIER:
	case INTEGER_STRING:
	case OTHER:
		ralloc_asprintf_rewrite_tail (out, len, "%s", token->value.str);
		break;
	case SPACE:
		ralloc_asprintf_rewrite_tail (out, len, " ");
		break;
	case LEFT_SHIFT:
		ralloc_asprintf_rewrite_tail (out, len, "<<");
		break;
	case RIGHT_SHIFT:
		ralloc_asprintf_rewrite_tail (out, len, ">>");
		break;
	case LESS_OR_EQUAL:
		ralloc_asprintf_rewrite_tail (out, len, "<=");
		break;
	case GREATER_OR_EQUAL:
		ralloc_asprintf_rewrite_tail (out, len, ">=");
		break;
	case EQUAL:
		ralloc_asprintf_rewrite_tail (out, len, "==");
		break;
	case NOT_EQUAL:
		ralloc_asprintf_rewrite_tail (out, len, "!=");
		break;
	case AND:
		ralloc_asprintf_rewrite_tail (out, len, "&&");
		break;
	case OR:
		ralloc_asprintf_rewrite_tail (out, len, "||");
		break;
	case PASTE:
		ralloc_asprintf_rewrite_tail (out, len, "##");
		break;
        case PLUS_PLUS:
		ralloc_asprintf_rewrite_tail (out, len, "++");
		break;
        case MINUS_MINUS:
		ralloc_asprintf_rewrite_tail (out, len, "--");
		break;
	case DEFINED:
		ralloc_asprintf_rewrite_tail (out, len, "defined");
		break;
	case PLACEHOLDER:
		/* Nothing to print. */
		break;
	default:
		assert(!"Error: Don't know how to print token.");

		break;
	}
}

/* Return a new token (ralloc()ed off of 'token') formed by pasting
 * 'token' and 'other'. Note that this function may return 'token' or
 * 'other' directly rather than allocating anything new.
 *
 * Caution: Only very cursory error-checking is performed to see if
 * the final result is a valid single token. */
static token_t *
_token_paste (glcpp_parser_t *parser, token_t *token, token_t *other)
{
	token_t *combined = NULL;

	/* Pasting a placeholder onto anything makes no change. */
	if (other->type == PLACEHOLDER)
		return token;

	/* When 'token' is a placeholder, just return 'other'. */
	if (token->type == PLACEHOLDER)
		return other;

	/* A very few single-character punctuators can be combined
	 * with another to form a multi-character punctuator. */
	switch (token->type) {
	case '<':
		if (other->type == '<')
			combined = _token_create_ival (token, LEFT_SHIFT, LEFT_SHIFT);
		else if (other->type == '=')
			combined = _token_create_ival (token, LESS_OR_EQUAL, LESS_OR_EQUAL);
		break;
	case '>':
		if (other->type == '>')
			combined = _token_create_ival (token, RIGHT_SHIFT, RIGHT_SHIFT);
		else if (other->type == '=')
			combined = _token_create_ival (token, GREATER_OR_EQUAL, GREATER_OR_EQUAL);
		break;
	case '=':
		if (other->type == '=')
			combined = _token_create_ival (token, EQUAL, EQUAL);
		break;
	case '!':
		if (other->type == '=')
			combined = _token_create_ival (token, NOT_EQUAL, NOT_EQUAL);
		break;
	case '&':
		if (other->type == '&')
			combined = _token_create_ival (token, AND, AND);
		break;
	case '|':
		if (other->type == '|')
			combined = _token_create_ival (token, OR, OR);
		break;
	}

	if (combined != NULL) {
		/* Inherit the location from the first token */
		combined->location = token->location;
		return combined;
	}

	/* Two string-valued (or integer) tokens can usually just be
	 * mashed together. (We also handle a string followed by an
	 * integer here as well.)
	 *
	 * There are some exceptions here. Notably, if the first token
	 * is an integer (or a string representing an integer), then
	 * the second token must also be an integer or must be a
	 * string representing an integer that begins with a digit.
	 */
	if ((token->type == IDENTIFIER || token->type == OTHER || token->type == INTEGER_STRING || token->type == INTEGER) &&
	    (other->type == IDENTIFIER || other->type == OTHER || other->type == INTEGER_STRING || other->type == INTEGER))
	{
		char *str;
		int combined_type;

		/* Check that pasting onto an integer doesn't create a
		 * non-integer, (that is, only digits can be
		 * pasted. */
		if (token->type == INTEGER_STRING || token->type == INTEGER)
		{
			switch (other->type) {
			case INTEGER_STRING:
				if (other->value.str[0] < '0' ||
				    other->value.str[0] > '9')
					goto FAIL;
				break;
			case INTEGER:
				if (other->value.ival < 0)
					goto FAIL;
				break;
			default:
				goto FAIL;
			}
		}

		if (token->type == INTEGER)
			str = ralloc_asprintf (token, "%" PRIiMAX,
					       token->value.ival);
		else
			str = ralloc_strdup (token, token->value.str);
					       

		if (other->type == INTEGER)
			ralloc_asprintf_append (&str, "%" PRIiMAX,
						other->value.ival);
		else
			ralloc_strcat (&str, other->value.str);

		/* New token is same type as original token, unless we
		 * started with an integer, in which case we will be
		 * creating an integer-string. */
		combined_type = token->type;
		if (combined_type == INTEGER)
			combined_type = INTEGER_STRING;

		combined = _token_create_str (token, combined_type, str);
		combined->location = token->location;
		return combined;
	}

    FAIL:
	glcpp_error (&token->location, parser, "");
	ralloc_asprintf_rewrite_tail (&parser->info_log, &parser->info_log_length, "Pasting \"");
	_token_print (&parser->info_log, &parser->info_log_length, token);
	ralloc_asprintf_rewrite_tail (&parser->info_log, &parser->info_log_length, "\" and \"");
	_token_print (&parser->info_log, &parser->info_log_length, other);
	ralloc_asprintf_rewrite_tail (&parser->info_log, &parser->info_log_length, "\" does not give a valid preprocessing token.\n");

	return token;
}

static void
_token_list_print (glcpp_parser_t *parser, token_list_t *list)
{
	token_node_t *node;

	if (list == NULL)
		return;

	for (node = list->head; node; node = node->next)
		_token_print (&parser->output, &parser->output_length, node->token);
}

void
yyerror (YYLTYPE *locp, glcpp_parser_t *parser, const char *error)
{
	glcpp_error(locp, parser, "%s", error);
}

static void add_builtin_define(glcpp_parser_t *parser,
			       const char *name, int value)
{
   token_t *tok;
   token_list_t *list;

   tok = _token_create_ival (parser, INTEGER, value);

   list = _token_list_create(parser);
   _token_list_append(list, tok);
   _define_object_macro(parser, NULL, name, list);
}

glcpp_parser_t *
glcpp_parser_create (const struct gl_extensions *extensions, gl_api api)
{
	glcpp_parser_t *parser;

	parser = ralloc (NULL, glcpp_parser_t);

	glcpp_lex_init_extra (parser, &parser->scanner);
	parser->defines = hash_table_ctor (32, hash_table_string_hash,
					   hash_table_string_compare);
	parser->active = NULL;
	parser->lexing_directive = 0;
	parser->space_tokens = 1;
	parser->last_token_was_newline = 0;
	parser->last_token_was_space = 0;
	parser->first_non_space_token_this_line = 1;
	parser->newline_as_space = 0;
	parser->in_control_line = 0;
	parser->paren_count = 0;
        parser->commented_newlines = 0;

	parser->skip_stack = NULL;
	parser->skipping = 0;

	parser->lex_from_list = NULL;
	parser->lex_from_node = NULL;

	parser->output = ralloc_strdup(parser, "");
	parser->output_length = 0;
	parser->info_log = ralloc_strdup(parser, "");
	parser->info_log_length = 0;
	parser->error = 0;

        parser->extensions = extensions;
        parser->api = api;
        parser->version_resolved = false;

	parser->has_new_line_number = 0;
	parser->new_line_number = 1;
	parser->has_new_source_number = 0;
	parser->new_source_number = 0;

	return parser;
}

void
glcpp_parser_destroy (glcpp_parser_t *parser)
{
	glcpp_lex_destroy (parser->scanner);
	hash_table_dtor (parser->defines);
	ralloc_free (parser);
}

typedef enum function_status
{
	FUNCTION_STATUS_SUCCESS,
	FUNCTION_NOT_A_FUNCTION,
	FUNCTION_UNBALANCED_PARENTHESES
} function_status_t;

/* Find a set of function-like macro arguments by looking for a
 * balanced set of parentheses.
 *
 * When called, 'node' should be the opening-parenthesis token, (or
 * perhaps preceeding SPACE tokens). Upon successful return *last will
 * be the last consumed node, (corresponding to the closing right
 * parenthesis).
 *
 * Return values:
 *
 *   FUNCTION_STATUS_SUCCESS:
 *
 *	Successfully parsed a set of function arguments.	
 *
 *   FUNCTION_NOT_A_FUNCTION:
 *
 *	Macro name not followed by a '('. This is not an error, but
 *	simply that the macro name should be treated as a non-macro.
 *
 *   FUNCTION_UNBALANCED_PARENTHESES
 *
 *	Macro name is not followed by a balanced set of parentheses.
 */
static function_status_t
_arguments_parse (argument_list_t *arguments,
		  token_node_t *node,
		  token_node_t **last)
{
	token_list_t *argument;
	int paren_count;

	node = node->next;

	/* Ignore whitespace before first parenthesis. */
	while (node && node->token->type == SPACE)
		node = node->next;

	if (node == NULL || node->token->type != '(')
		return FUNCTION_NOT_A_FUNCTION;

	node = node->next;

	argument = _token_list_create (arguments);
	_argument_list_append (arguments, argument);

	for (paren_count = 1; node; node = node->next) {
		if (node->token->type == '(')
		{
			paren_count++;
		}
		else if (node->token->type == ')')
		{
			paren_count--;
			if (paren_count == 0)
				break;
		}

		if (node->token->type == ',' &&
			 paren_count == 1)
		{
			_token_list_trim_trailing_space (argument);
			argument = _token_list_create (arguments);
			_argument_list_append (arguments, argument);
		}
		else {
			if (argument->head == NULL) {
				/* Don't treat initial whitespace as
				 * part of the argument. */
				if (node->token->type == SPACE)
					continue;
			}
			_token_list_append (argument, node->token);
		}
	}

	if (paren_count)
		return FUNCTION_UNBALANCED_PARENTHESES;

	*last = node;

	return FUNCTION_STATUS_SUCCESS;
}

static token_list_t *
_token_list_create_with_one_ival (void *ctx, int type, int ival)
{
	token_list_t *list;
	token_t *node;

	list = _token_list_create (ctx);
	node = _token_create_ival (list, type, ival);
	_token_list_append (list, node);

	return list;
}

static token_list_t *
_token_list_create_with_one_space (void *ctx)
{
	return _token_list_create_with_one_ival (ctx, SPACE, SPACE);
}

static token_list_t *
_token_list_create_with_one_integer (void *ctx, int ival)
{
	return _token_list_create_with_one_ival (ctx, INTEGER, ival);
}

/* Evaluate a DEFINED token node (based on subsequent tokens in the list).
 *
 * Note: This function must only be called when "node" is a DEFINED token,
 * (and will abort with an assertion failure otherwise).
 *
 * If "node" is followed, (ignoring any SPACE tokens), by an IDENTIFIER token
 * (optionally preceded and followed by '(' and ')' tokens) then the following
 * occurs:
 *
 *	If the identifier is a defined macro, this function returns 1.
 *
 *	If the identifier is not a defined macro, this function returns 0.
 *
 *	In either case, *last will be updated to the last node in the list
 *	consumed by the evaluation, (either the token of the identifier or the
 *	token of the closing parenthesis).
 *
 * In all other cases, (such as "node is the final node of the list", or
 * "missing closing parenthesis", etc.), this function generates a
 * preprocessor error, returns -1 and *last will not be set.
 */
static int
_glcpp_parser_evaluate_defined (glcpp_parser_t *parser,
				token_node_t *node,
				token_node_t **last)
{
	token_node_t *argument, *defined = node;

	assert (node->token->type == DEFINED);

	node = node->next;

	/* Ignore whitespace after DEFINED token. */
	while (node && node->token->type == SPACE)
		node = node->next;

	if (node == NULL)
		goto FAIL;

	if (node->token->type == IDENTIFIER || node->token->type == OTHER) {
		argument = node;
	} else if (node->token->type == '(') {
		node = node->next;

		/* Ignore whitespace after '(' token. */
		while (node && node->token->type == SPACE)
			node = node->next;

		if (node == NULL || (node->token->type != IDENTIFIER &&
				     node->token->type != OTHER))
		{
			goto FAIL;
		}

		argument = node;

		node = node->next;

		/* Ignore whitespace after identifier, before ')' token. */
		while (node && node->token->type == SPACE)
			node = node->next;

		if (node == NULL || node->token->type != ')')
			goto FAIL;
	} else {
		goto FAIL;
	}

	*last = node;

	return hash_table_find (parser->defines,
				argument->token->value.str) ? 1 : 0;

FAIL:
	glcpp_error (&defined->token->location, parser,
		     "\"defined\" not followed by an identifier");
	return -1;
}

/* Evaluate all DEFINED nodes in a given list, modifying the list in place.
 */
static void
_glcpp_parser_evaluate_defined_in_list (glcpp_parser_t *parser,
					token_list_t *list)
{
	token_node_t *node, *node_prev, *replacement, *last = NULL;
	int value;

	if (list == NULL)
		return;

	node_prev = NULL;
	node = list->head;

	while (node) {

		if (node->token->type != DEFINED)
			goto NEXT;

		value = _glcpp_parser_evaluate_defined (parser, node, &last);
		if (value == -1)
			goto NEXT;

		replacement = ralloc (list, token_node_t);
		replacement->token = _token_create_ival (list, INTEGER, value);

		/* Splice replacement node into list, replacing from "node"
		 * through "last". */
		if (node_prev)
			node_prev->next = replacement;
		else
			list->head = replacement;
		replacement->next = last->next;
		if (last == list->tail)
			list->tail = replacement;

		node = replacement;

	NEXT:
		node_prev = node;
		node = node->next;
	}
}

/* Perform macro expansion on 'list', placing the resulting tokens
 * into a new list which is initialized with a first token of type
 * 'head_token_type'. Then begin lexing from the resulting list,
 * (return to the current lexing source when this list is exhausted).
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static void
_glcpp_parser_expand_and_lex_from (glcpp_parser_t *parser,
				   int head_token_type,
				   token_list_t *list,
				   expansion_mode_t mode)
{
	token_list_t *expanded;
	token_t *token;

	expanded = _token_list_create (parser);
	token = _token_create_ival (parser, head_token_type, head_token_type);
	_token_list_append (expanded, token);
	_glcpp_parser_expand_token_list (parser, list, mode);
	_token_list_append_list (expanded, list);
	glcpp_parser_lex_from (parser, expanded);
}

static void
_glcpp_parser_apply_pastes (glcpp_parser_t *parser, token_list_t *list)
{
	token_node_t *node;

	node = list->head;
	while (node)
	{
		token_node_t *next_non_space;

		/* Look ahead for a PASTE token, skipping space. */
		next_non_space = node->next;
		while (next_non_space && next_non_space->token->type == SPACE)
			next_non_space = next_non_space->next;

		if (next_non_space == NULL)
			break;

		if (next_non_space->token->type != PASTE) {
			node = next_non_space;
			continue;
		}

		/* Now find the next non-space token after the PASTE. */
		next_non_space = next_non_space->next;
		while (next_non_space && next_non_space->token->type == SPACE)
			next_non_space = next_non_space->next;

		if (next_non_space == NULL) {
			yyerror (&node->token->location, parser, "'##' cannot appear at either end of a macro expansion\n");
			return;
		}

		node->token = _token_paste (parser, node->token, next_non_space->token);
		node->next = next_non_space->next;
		if (next_non_space == list->tail)
			list->tail = node;
	}

	list->non_space_tail = list->tail;
}

/* This is a helper function that's essentially part of the
 * implementation of _glcpp_parser_expand_node. It shouldn't be called
 * except for by that function.
 *
 * Returns NULL if node is a simple token with no expansion, (that is,
 * although 'node' corresponds to an identifier defined as a
 * function-like macro, it is not followed with a parenthesized
 * argument list).
 *
 * Compute the complete expansion of node (which is a function-like
 * macro) and subsequent nodes which are arguments.
 *
 * Returns the token list that results from the expansion and sets
 * *last to the last node in the list that was consumed by the
 * expansion. Specifically, *last will be set as follows: as the
 * token of the closing right parenthesis.
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static token_list_t *
_glcpp_parser_expand_function (glcpp_parser_t *parser,
			       token_node_t *node,
			       token_node_t **last,
			       expansion_mode_t mode)
{
	macro_t *macro;
	const char *identifier;
	argument_list_t *arguments;
	function_status_t status;
	token_list_t *substituted;
	int parameter_index;

	identifier = node->token->value.str;

	macro = hash_table_find (parser->defines, identifier);

	assert (macro->is_function);

	arguments = _argument_list_create (parser);
	status = _arguments_parse (arguments, node, last);

	switch (status) {
	case FUNCTION_STATUS_SUCCESS:
		break;
	case FUNCTION_NOT_A_FUNCTION:
		return NULL;
	case FUNCTION_UNBALANCED_PARENTHESES:
		glcpp_error (&node->token->location, parser, "Macro %s call has unbalanced parentheses\n", identifier);
		return NULL;
	}

	/* Replace a macro defined as empty with a SPACE token. */
	if (macro->replacements == NULL) {
		ralloc_free (arguments);
		return _token_list_create_with_one_space (parser);
	}

	if (! ((_argument_list_length (arguments) == 
		_string_list_length (macro->parameters)) ||
	       (_string_list_length (macro->parameters) == 0 &&
		_argument_list_length (arguments) == 1 &&
		arguments->head->argument->head == NULL)))
	{
		glcpp_error (&node->token->location, parser,
			      "Error: macro %s invoked with %d arguments (expected %d)\n",
			      identifier,
			      _argument_list_length (arguments),
			      _string_list_length (macro->parameters));
		return NULL;
	}

	/* Perform argument substitution on the replacement list. */
	substituted = _token_list_create (arguments);

	for (node = macro->replacements->head; node; node = node->next)
	{
		if (node->token->type == IDENTIFIER &&
		    _string_list_contains (macro->parameters,
					   node->token->value.str,
					   &parameter_index))
		{
			token_list_t *argument;
			argument = _argument_list_member_at (arguments,
							     parameter_index);
			/* Before substituting, we expand the argument
			 * tokens, or append a placeholder token for
			 * an empty argument. */
			if (argument->head) {
				token_list_t *expanded_argument;
				expanded_argument = _token_list_copy (parser,
								      argument);
				_glcpp_parser_expand_token_list (parser,
								 expanded_argument,
								 mode);
				_token_list_append_list (substituted,
							 expanded_argument);
			} else {
				token_t *new_token;

				new_token = _token_create_ival (substituted,
								PLACEHOLDER,
								PLACEHOLDER);
				_token_list_append (substituted, new_token);
			}
		} else {
			_token_list_append (substituted, node->token);
		}
	}

	/* After argument substitution, and before further expansion
	 * below, implement token pasting. */

	_token_list_trim_trailing_space (substituted);

	_glcpp_parser_apply_pastes (parser, substituted);

	return substituted;
}

/* Compute the complete expansion of node, (and subsequent nodes after
 * 'node' in the case that 'node' is a function-like macro and
 * subsequent nodes are arguments).
 *
 * Returns NULL if node is a simple token with no expansion.
 *
 * Otherwise, returns the token list that results from the expansion
 * and sets *last to the last node in the list that was consumed by
 * the expansion. Specifically, *last will be set as follows:
 *
 *	As 'node' in the case of object-like macro expansion.
 *
 *	As the token of the closing right parenthesis in the case of
 *	function-like macro expansion.
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static token_list_t *
_glcpp_parser_expand_node (glcpp_parser_t *parser,
			   token_node_t *node,
			   token_node_t **last,
			   expansion_mode_t mode)
{
	token_t *token = node->token;
	const char *identifier;
	macro_t *macro;

	/* We only expand identifiers */
	if (token->type != IDENTIFIER) {
		return NULL;
	}

	*last = node;
	identifier = token->value.str;

	/* Special handling for __LINE__ and __FILE__, (not through
	 * the hash table). */
	if (strcmp(identifier, "__LINE__") == 0)
		return _token_list_create_with_one_integer (parser, node->token->location.first_line);

	if (strcmp(identifier, "__FILE__") == 0)
		return _token_list_create_with_one_integer (parser, node->token->location.source);

	/* Look up this identifier in the hash table. */
	macro = hash_table_find (parser->defines, identifier);

	/* Not a macro, so no expansion needed. */
	if (macro == NULL)
		return NULL;

	/* Finally, don't expand this macro if we're already actively
	 * expanding it, (to avoid infinite recursion). */
	if (_parser_active_list_contains (parser, identifier)) {
		/* We change the token type here from IDENTIFIER to
		 * OTHER to prevent any future expansion of this
		 * unexpanded token. */
		char *str;
		token_list_t *expansion;
		token_t *final;

		str = ralloc_strdup (parser, token->value.str);
		final = _token_create_str (parser, OTHER, str);
		expansion = _token_list_create (parser);
		_token_list_append (expansion, final);
		return expansion;
	}

	if (! macro->is_function)
	{
		token_list_t *replacement;

		/* Replace a macro defined as empty with a SPACE token. */
		if (macro->replacements == NULL)
			return _token_list_create_with_one_space (parser);

		replacement = _token_list_copy (parser, macro->replacements);
		_glcpp_parser_apply_pastes (parser, replacement);
		return replacement;
	}

	return _glcpp_parser_expand_function (parser, node, last, mode);
}

/* Push a new identifier onto the parser's active list.
 *
 * Here, 'marker' is the token node that appears in the list after the
 * expansion of 'identifier'. That is, when the list iterator begins
 * examining 'marker', then it is time to pop this node from the
 * active stack.
 */
static void
_parser_active_list_push (glcpp_parser_t *parser,
			  const char *identifier,
			  token_node_t *marker)
{
	active_list_t *node;

	node = ralloc (parser->active, active_list_t);
	node->identifier = ralloc_strdup (node, identifier);
	node->marker = marker;
	node->next = parser->active;

	parser->active = node;
}

static void
_parser_active_list_pop (glcpp_parser_t *parser)
{
	active_list_t *node = parser->active;

	if (node == NULL) {
		parser->active = NULL;
		return;
	}

	node = parser->active->next;
	ralloc_free (parser->active);

	parser->active = node;
}

static int
_parser_active_list_contains (glcpp_parser_t *parser, const char *identifier)
{
	active_list_t *node;

	if (parser->active == NULL)
		return 0;

	for (node = parser->active; node; node = node->next)
		if (strcmp (node->identifier, identifier) == 0)
			return 1;

	return 0;
}

/* Walk over the token list replacing nodes with their expansion.
 * Whenever nodes are expanded the walking will walk over the new
 * nodes, continuing to expand as necessary. The results are placed in
 * 'list' itself.
 *
 * The "mode" argument controls the handling of any DEFINED tokens that
 * result from expansion as follows:
 *
 *	EXPANSION_MODE_IGNORE_DEFINED: Any resulting DEFINED tokens will be
 *		left in the final list, unevaluated. This is the correct mode
 *		for expanding any list in any context other than a
 *		preprocessor conditional, (#if or #elif).
 *
 *	EXPANSION_MODE_EVALUATE_DEFINED: Any resulting DEFINED tokens will be
 *		evaluated to 0 or 1 tokens depending on whether the following
 *		token is the name of a defined macro. If the DEFINED token is
 *		not followed by an (optionally parenthesized) identifier, then
 *		an error will be generated. This the correct mode for
 *		expanding any list in the context of a preprocessor
 *		conditional, (#if or #elif).
 */
static void
_glcpp_parser_expand_token_list (glcpp_parser_t *parser,
				 token_list_t *list,
				 expansion_mode_t mode)
{
	token_node_t *node_prev;
	token_node_t *node, *last = NULL;
	token_list_t *expansion;
	active_list_t *active_initial = parser->active;

	if (list == NULL)
		return;

	_token_list_trim_trailing_space (list);

	node_prev = NULL;
	node = list->head;

	if (mode == EXPANSION_MODE_EVALUATE_DEFINED)
		_glcpp_parser_evaluate_defined_in_list (parser, list);

	while (node) {

		while (parser->active && parser->active->marker == node)
			_parser_active_list_pop (parser);

		expansion = _glcpp_parser_expand_node (parser, node, &last, mode);
		if (expansion) {
			token_node_t *n;

			if (mode == EXPANSION_MODE_EVALUATE_DEFINED) {
				_glcpp_parser_evaluate_defined_in_list (parser,
									expansion);
			}

			for (n = node; n != last->next; n = n->next)
				while (parser->active &&
				       parser->active->marker == n)
				{
					_parser_active_list_pop (parser);
				}

			_parser_active_list_push (parser,
						  node->token->value.str,
						  last->next);
			
			/* Splice expansion into list, supporting a
			 * simple deletion if the expansion is
			 * empty. */
			if (expansion->head) {
				if (node_prev)
					node_prev->next = expansion->head;
				else
					list->head = expansion->head;
				expansion->tail->next = last->next;
				if (last == list->tail)
					list->tail = expansion->tail;
			} else {
				if (node_prev)
					node_prev->next = last->next;
				else
					list->head = last->next;
				if (last == list->tail)
					list->tail = NULL;
			}
		} else {
			node_prev = node;
		}
		node = node_prev ? node_prev->next : list->head;
	}

	/* Remove any lingering effects of this invocation on the
	 * active list. That is, pop until the list looks like it did
	 * at the beginning of this function. */
	while (parser->active && parser->active != active_initial)
		_parser_active_list_pop (parser);

	list->non_space_tail = list->tail;
}

void
_glcpp_parser_print_expanded_token_list (glcpp_parser_t *parser,
					 token_list_t *list)
{
	if (list == NULL)
		return;

	_glcpp_parser_expand_token_list (parser, list, EXPANSION_MODE_IGNORE_DEFINED);

	_token_list_trim_trailing_space (list);

	_token_list_print (parser, list);
}

static void
_check_for_reserved_macro_name (glcpp_parser_t *parser, YYLTYPE *loc,
				const char *identifier)
{
	/* Section 3.3 (Preprocessor) of the GLSL 1.30 spec (and later) and
	 * the GLSL ES spec (all versions) say:
	 *
	 *     "All macro names containing two consecutive underscores ( __ )
	 *     are reserved for future use as predefined macro names. All
	 *     macro names prefixed with "GL_" ("GL" followed by a single
	 *     underscore) are also reserved."
	 *
	 * The intention is that names containing __ are reserved for internal
	 * use by the implementation, and names prefixed with GL_ are reserved
	 * for use by Khronos.  Since every extension adds a name prefixed
	 * with GL_ (i.e., the name of the extension), that should be an
	 * error.  Names simply containing __ are dangerous to use, but should
	 * be allowed.
	 *
	 * A future version of the GLSL specification will clarify this.
	 */
	if (strstr(identifier, "__")) {
		glcpp_warning(loc, parser,
			      "Macro names containing \"__\" are reserved "
			      "for use by the implementation.\n");
	}
	if (strncmp(identifier, "GL_", 3) == 0) {
		glcpp_error (loc, parser, "Macro names starting with \"GL_\" are reserved.\n");
	}
}

static int
_macro_equal (macro_t *a, macro_t *b)
{
	if (a->is_function != b->is_function)
		return 0;

	if (a->is_function) {
		if (! _string_list_equal (a->parameters, b->parameters))
			return 0;
	}

	return _token_list_equal_ignoring_space (a->replacements,
						 b->replacements);
}

void
_define_object_macro (glcpp_parser_t *parser,
		      YYLTYPE *loc,
		      const char *identifier,
		      token_list_t *replacements)
{
	macro_t *macro, *previous;

	/* We define pre-defined macros before we've started parsing the
         * actual file. So if there's no location defined yet, that's what
         * were doing and we don't want to generate an error for using the
         * reserved names. */
	if (loc != NULL)
		_check_for_reserved_macro_name(parser, loc, identifier);

	macro = ralloc (parser, macro_t);

	macro->is_function = 0;
	macro->parameters = NULL;
	macro->identifier = ralloc_strdup (macro, identifier);
	macro->replacements = replacements;
	ralloc_steal (macro, replacements);

	previous = hash_table_find (parser->defines, identifier);
	if (previous) {
		if (_macro_equal (macro, previous)) {
			ralloc_free (macro);
			return;
		}
		glcpp_error (loc, parser, "Redefinition of macro %s\n",
			     identifier);
	}

	hash_table_insert (parser->defines, macro, identifier);
}

void
_define_function_macro (glcpp_parser_t *parser,
			YYLTYPE *loc,
			const char *identifier,
			string_list_t *parameters,
			token_list_t *replacements)
{
	macro_t *macro, *previous;
	const char *dup;

	_check_for_reserved_macro_name(parser, loc, identifier);

        /* Check for any duplicate parameter names. */
	if ((dup = _string_list_has_duplicate (parameters)) != NULL) {
		glcpp_error (loc, parser, "Duplicate macro parameter \"%s\"",
			     dup);
	}

	macro = ralloc (parser, macro_t);
	ralloc_steal (macro, parameters);
	ralloc_steal (macro, replacements);

	macro->is_function = 1;
	macro->parameters = parameters;
	macro->identifier = ralloc_strdup (macro, identifier);
	macro->replacements = replacements;
	previous = hash_table_find (parser->defines, identifier);
	if (previous) {
		if (_macro_equal (macro, previous)) {
			ralloc_free (macro);
			return;
		}
		glcpp_error (loc, parser, "Redefinition of macro %s\n",
			     identifier);
	}

	hash_table_insert (parser->defines, macro, identifier);
}

static int
glcpp_parser_lex (YYSTYPE *yylval, YYLTYPE *yylloc, glcpp_parser_t *parser)
{
	token_node_t *node;
	int ret;

	if (parser->lex_from_list == NULL) {
		ret = glcpp_lex (yylval, yylloc, parser->scanner);

		/* XXX: This ugly block of code exists for the sole
		 * purpose of converting a NEWLINE token into a SPACE
		 * token, but only in the case where we have seen a
		 * function-like macro name, but have not yet seen its
		 * closing parenthesis.
		 *
		 * There's perhaps a more compact way to do this with
		 * mid-rule actions in the grammar.
		 *
		 * I'm definitely not pleased with the complexity of
		 * this code here.
		 */
		if (parser->newline_as_space)
		{
			if (ret == '(') {
				parser->paren_count++;
			} else if (ret == ')') {
				parser->paren_count--;
				if (parser->paren_count == 0)
					parser->newline_as_space = 0;
			} else if (ret == NEWLINE) {
				ret = SPACE;
			} else if (ret != SPACE) {
				if (parser->paren_count == 0)
					parser->newline_as_space = 0;
			}
		}
		else if (parser->in_control_line)
		{
			if (ret == NEWLINE)
				parser->in_control_line = 0;
		}
		else if (ret == DEFINE_TOKEN ||
			 ret == UNDEF || ret == IF ||
			 ret == IFDEF || ret == IFNDEF ||
			 ret == ELIF || ret == ELSE ||
			 ret == ENDIF || ret == HASH_TOKEN)
		{
			parser->in_control_line = 1;
		}
		else if (ret == IDENTIFIER)
		{
			macro_t *macro;
			macro = hash_table_find (parser->defines,
						 yylval->str);
			if (macro && macro->is_function) {
				parser->newline_as_space = 1;
				parser->paren_count = 0;
			}
		}

		return ret;
	}

	node = parser->lex_from_node;

	if (node == NULL) {
		ralloc_free (parser->lex_from_list);
		parser->lex_from_list = NULL;
		return NEWLINE;
	}

	*yylval = node->token->value;
	ret = node->token->type;

	parser->lex_from_node = node->next;

	return ret;
}

static void
glcpp_parser_lex_from (glcpp_parser_t *parser, token_list_t *list)
{
	token_node_t *node;

	assert (parser->lex_from_list == NULL);

	/* Copy list, eliminating any space tokens. */
	parser->lex_from_list = _token_list_create (parser);

	for (node = list->head; node; node = node->next) {
		if (node->token->type == SPACE)
			continue;
		_token_list_append (parser->lex_from_list, node->token);
	}

	ralloc_free (list);

	parser->lex_from_node = parser->lex_from_list->head;

	/* It's possible the list consisted of nothing but whitespace. */
	if (parser->lex_from_node == NULL) {
		ralloc_free (parser->lex_from_list);
		parser->lex_from_list = NULL;
	}
}

static void
_glcpp_parser_skip_stack_push_if (glcpp_parser_t *parser, YYLTYPE *loc,
				  int condition)
{
	skip_type_t current = SKIP_NO_SKIP;
	skip_node_t *node;

	if (parser->skip_stack)
		current = parser->skip_stack->type;

	node = ralloc (parser, skip_node_t);
	node->loc = *loc;

	if (current == SKIP_NO_SKIP) {
		if (condition)
			node->type = SKIP_NO_SKIP;
		else
			node->type = SKIP_TO_ELSE;
	} else {
		node->type = SKIP_TO_ENDIF;
	}

	node->has_else = false;
	node->next = parser->skip_stack;
	parser->skip_stack = node;
}

static void
_glcpp_parser_skip_stack_change_if (glcpp_parser_t *parser, YYLTYPE *loc,
				    const char *type, int condition)
{
	if (parser->skip_stack == NULL) {
		glcpp_error (loc, parser, "#%s without #if\n", type);
		return;
	}

	if (parser->skip_stack->type == SKIP_TO_ELSE) {
		if (condition)
			parser->skip_stack->type = SKIP_NO_SKIP;
	} else {
		parser->skip_stack->type = SKIP_TO_ENDIF;
	}
}

static void
_glcpp_parser_skip_stack_pop (glcpp_parser_t *parser, YYLTYPE *loc)
{
	skip_node_t *node;

	if (parser->skip_stack == NULL) {
		glcpp_error (loc, parser, "#endif without #if\n");
		return;
	}

	node = parser->skip_stack;
	parser->skip_stack = node->next;
	ralloc_free (node);
}

static void
_glcpp_parser_handle_version_declaration(glcpp_parser_t *parser, intmax_t version,
                                         const char *es_identifier,
                                         bool explicitly_set)
{
	const struct gl_extensions *extensions = parser->extensions;

	if (parser->version_resolved)
		return;

	parser->version_resolved = true;

	add_builtin_define (parser, "__VERSION__", version);

	parser->is_gles = (version == 100) ||
			   (es_identifier &&
			    (strcmp(es_identifier, "es") == 0));

	/* Add pre-defined macros. */
	if (parser->is_gles) {
	   add_builtin_define(parser, "GL_ES", 1);
           add_builtin_define(parser, "GL_EXT_separate_shader_objects", 1);

	   if (extensions != NULL) {
	      if (extensions->OES_EGL_image_external)
	         add_builtin_define(parser, "GL_OES_EGL_image_external", 1);
              if (extensions->OES_standard_derivatives)
                 add_builtin_define(parser, "GL_OES_standard_derivatives", 1);
	   }
	} else {
	   add_builtin_define(parser, "GL_ARB_draw_buffers", 1);
           add_builtin_define(parser, "GL_ARB_separate_shader_objects", 1);
	   add_builtin_define(parser, "GL_ARB_texture_rectangle", 1);
           add_builtin_define(parser, "GL_AMD_shader_trinary_minmax", 1);


	   if (extensions != NULL) {
	      if (extensions->EXT_texture_array)
	         add_builtin_define(parser, "GL_EXT_texture_array", 1);

	      if (extensions->ARB_arrays_of_arrays)
	          add_builtin_define(parser, "GL_ARB_arrays_of_arrays", 1);

	      if (extensions->ARB_fragment_coord_conventions)
	         add_builtin_define(parser, "GL_ARB_fragment_coord_conventions",
				    1);

              if (extensions->ARB_fragment_layer_viewport)
                 add_builtin_define(parser, "GL_ARB_fragment_layer_viewport", 1);

	      if (extensions->ARB_explicit_attrib_location)
	         add_builtin_define(parser, "GL_ARB_explicit_attrib_location", 1);

	      if (extensions->ARB_explicit_uniform_location)
	         add_builtin_define(parser, "GL_ARB_explicit_uniform_location", 1);

	      if (extensions->ARB_shader_texture_lod)
	         add_builtin_define(parser, "GL_ARB_shader_texture_lod", 1);

	      if (extensions->ARB_draw_instanced)
	         add_builtin_define(parser, "GL_ARB_draw_instanced", 1);

	      if (extensions->EXT_draw_instanced)
	         add_builtin_define(parser, "GL_EXT_draw_instanced", 1);

	      if (extensions->ARB_conservative_depth) {
	         add_builtin_define(parser, "GL_AMD_conservative_depth", 1);
	         add_builtin_define(parser, "GL_ARB_conservative_depth", 1);
	      }

	      if (extensions->ARB_shader_bit_encoding)
	         add_builtin_define(parser, "GL_ARB_shader_bit_encoding", 1);

	      if (extensions->ARB_uniform_buffer_object)
	         add_builtin_define(parser, "GL_ARB_uniform_buffer_object", 1);

	      if (extensions->ARB_texture_cube_map_array)
	         add_builtin_define(parser, "GL_ARB_texture_cube_map_array", 1);

	      if (extensions->ARB_shading_language_packing)
	         add_builtin_define(parser, "GL_ARB_shading_language_packing", 1);

	      if (extensions->ARB_texture_multisample)
	         add_builtin_define(parser, "GL_ARB_texture_multisample", 1);

	      if (extensions->ARB_texture_query_levels)
	         add_builtin_define(parser, "GL_ARB_texture_query_levels", 1);

	      if (extensions->ARB_texture_query_lod)
	         add_builtin_define(parser, "GL_ARB_texture_query_lod", 1);

	      if (extensions->ARB_gpu_shader5)
	         add_builtin_define(parser, "GL_ARB_gpu_shader5", 1);

	      if (extensions->AMD_vertex_shader_layer)
	         add_builtin_define(parser, "GL_AMD_vertex_shader_layer", 1);

	      if (extensions->AMD_vertex_shader_viewport_index)
	         add_builtin_define(parser, "GL_AMD_vertex_shader_viewport_index", 1);

	      if (extensions->ARB_shading_language_420pack)
	         add_builtin_define(parser, "GL_ARB_shading_language_420pack", 1);

	      if (extensions->ARB_sample_shading)
	         add_builtin_define(parser, "GL_ARB_sample_shading", 1);

	      if (extensions->ARB_texture_gather)
	         add_builtin_define(parser, "GL_ARB_texture_gather", 1);

	      if (extensions->ARB_shader_atomic_counters)
	         add_builtin_define(parser, "GL_ARB_shader_atomic_counters", 1);

	      if (extensions->ARB_viewport_array)
	         add_builtin_define(parser, "GL_ARB_viewport_array", 1);

              if (extensions->ARB_compute_shader)
                 add_builtin_define(parser, "GL_ARB_compute_shader", 1);

	      if (extensions->ARB_shader_image_load_store)
	         add_builtin_define(parser, "GL_ARB_shader_image_load_store", 1);

              if (extensions->ARB_derivative_control)
                 add_builtin_define(parser, "GL_ARB_derivative_control", 1);
	   }
	}

	if (extensions != NULL) {
	   if (extensions->EXT_shader_integer_mix)
	      add_builtin_define(parser, "GL_EXT_shader_integer_mix", 1);
	}

	if (version >= 150)
		add_builtin_define(parser, "GL_core_profile", 1);

	/* Currently, all ES2/ES3 implementations support highp in the
	 * fragment shader, so we always define this macro in ES2/ES3.
	 * If we ever get a driver that doesn't support highp, we'll
	 * need to add a flag to the gl_context and check that here.
	 */
	if (version >= 130 || parser->is_gles)
		add_builtin_define (parser, "GL_FRAGMENT_PRECISION_HIGH", 1);

	if (explicitly_set) {
	   ralloc_asprintf_rewrite_tail (&parser->output, &parser->output_length,
					 "#version %" PRIiMAX "%s%s", version,
					 es_identifier ? " " : "",
					 es_identifier ? es_identifier : "");
	}
}

/* GLSL version if no version is explicitly specified. */
#define IMPLICIT_GLSL_VERSION 110
#define IMPLICIT_GLSL_ES_VERSION 100

/* GLSL ES version if no version is explicitly specified. */
#define IMPLICIT_GLSL_ES_VERSION 100

void
glcpp_parser_resolve_implicit_version(glcpp_parser_t *parser)
{
	int language_version = parser->api == API_OPENGLES2 ?
			       IMPLICIT_GLSL_ES_VERSION :
			       IMPLICIT_GLSL_VERSION;

	_glcpp_parser_handle_version_declaration(parser, language_version,
						 NULL, false);
}

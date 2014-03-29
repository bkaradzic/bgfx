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
#include <string.h>
#include <ctype.h>

#include "glcpp.h"
#include "glcpp-parse.h"

/* Flex annoyingly generates some functions without making them
 * static. Let's declare them here. */
int glcpp_get_column  (yyscan_t yyscanner);
void glcpp_set_column (int  column_no , yyscan_t yyscanner);

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#pragma warning(disable: 4267) // warning C4267: '=' : conversion from 'size_t' to 'int', possible loss of data
#endif

#define YY_NO_INPUT

#define YY_USER_ACTION							\
	do {								\
		if (parser->has_new_line_number)			\
			yylineno = parser->new_line_number;		\
		if (parser->has_new_source_number)			\
			yylloc->source = parser->new_source_number;	\
		yylloc->first_column = yycolumn + 1;			\
		yylloc->first_line = yylineno;				\
		yycolumn += yyleng;					\
		parser->has_new_line_number = 0;			\
		parser->has_new_source_number = 0;			\
 } while(0);

#define YY_USER_INIT			\
	do {				\
		yylineno = 1;		\
		yycolumn = 1;		\
		yylloc->source = 0;	\
	} while(0)
%}

%option bison-bridge bison-locations reentrant noyywrap
%option extra-type="glcpp_parser_t *"
%option prefix="glcpp_"
%option stack
%option never-interactive

%x DONE COMMENT UNREACHABLE SKIP DEFINE NEWLINE_CATCHUP

SPACE		[[:space:]]
NONSPACE	[^[:space:]]
NEWLINE		[\n]
HSPACE		[ \t]
HASH		^{HSPACE}*#{HSPACE}*
IDENTIFIER	[_a-zA-Z][_a-zA-Z0-9]*
PUNCTUATION	[][(){}.&*~!/%<>^|;,=+-]

/* The OTHER class is simply a catch-all for things that the CPP
parser just doesn't care about. Since flex regular expressions that
match longer strings take priority over those matching shorter
strings, we have to be careful to avoid OTHER matching and hiding
something that CPP does care about. So we simply exclude all
characters that appear in any other expressions. */

OTHER		[^][_#[:space:]#a-zA-Z0-9(){}.&*~!/%<>^|;,=+-]

DIGITS			[0-9][0-9]*
DECIMAL_INTEGER		[1-9][0-9]*[uU]?
OCTAL_INTEGER		0[0-7]*[uU]?
HEXADECIMAL_INTEGER	0[xX][0-9a-fA-F]+[uU]?

%%

	glcpp_parser_t *parser = yyextra;

	/* When we lex a multi-line comment, we replace it (as
	 * specified) with a single space. But if the comment spanned
	 * multiple lines, then subsequent parsing stages will not
	 * count correct line numbers. To avoid this problem we keep
	 * track of all newlines that were commented out by a
	 * multi-line comment, and we emit a NEWLINE token for each at
	 * the next legal opportunity, (which is when the lexer would
	 * be emitting a NEWLINE token anyway).
	 */
	if (YY_START == NEWLINE_CATCHUP) {
		if (parser->commented_newlines)
			parser->commented_newlines--;
		if (parser->commented_newlines == 0)
			BEGIN INITIAL;
		return NEWLINE;
	}

	/* The handling of the SKIP vs INITIAL start states requires
	 * some special handling. Typically, a lexer would change
	 * start states with statements like "BEGIN SKIP" within the
	 * lexer rules. We can't get away with that here, since we
	 * need the parser to actually evaluate expressions for
	 * directives like "#if".
	 *
	 * So, here, in code that will be executed on every call to
	 * the lexer,and before any rules, we examine the skip_stack
	 * as set by the parser to know whether to change from INITIAL
	 * to SKIP or from SKIP back to INITIAL.
	 *
	 * Three cases cause us to switch out of the SKIP state and
	 * back to the INITIAL state:
	 *
	 *	1. The top of the skip_stack is of type SKIP_NO_SKIP
	 *	   This means we're still evaluating some #if
	 *	   hierarchy, but we're on a branch of it where
	 *	   content should not be skipped (such as "#if 1" or
	 *	   "#else" or so).
	 *
	 *	2. The skip_stack is NULL meaning that we've reached
	 *	   the last #endif.
	 *
	 *	3. The lexing_if bit is set. This indicates that we
	 *	   are lexing the expression following an "#if" of
	 *	   "#elif". Even inside an "#if 0" we need to lex this
	 *	   expression so the parser can correctly update the
	 *	   skip_stack state.
	 */
	if (YY_START == INITIAL || YY_START == SKIP) {
		if (parser->lexing_if ||
		    parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			BEGIN INITIAL;
		} else {
			BEGIN SKIP;
		}
	}

	/* Single-line comments */
"//"[^\n]* {
}

	/* Multi-line comments */
"/*"                    { yy_push_state(COMMENT, yyscanner); }
<COMMENT>[^*\n]*
<COMMENT>[^*\n]*\n      { yylineno++; yycolumn = 0; parser->commented_newlines++; }
<COMMENT>"*"+[^*/\n]*
<COMMENT>"*"+[^*/\n]*\n { yylineno++; yycolumn = 0; parser->commented_newlines++; }
<COMMENT>"*"+"/"        {
	yy_pop_state(yyscanner);
	if (yyextra->space_tokens)
		return SPACE;
}

{HASH}version{HSPACE}+ {
	yylval->str = ralloc_strdup (yyextra, yytext);
	yyextra->space_tokens = 0;
	return HASH_VERSION;
}

	/* glcpp doesn't handle #extension, #version, or #pragma directives.
	 * Simply pass them through to the main compiler's lexer/parser. */
{HASH}(extension|pragma)[^\n]+ {
	if (parser->commented_newlines)
		BEGIN NEWLINE_CATCHUP;
	yylval->str = ralloc_strdup (yyextra, yytext);
	yylineno++;
	yycolumn = 0;
	return OTHER;
}

{HASH}line{HSPACE}+ {
	return HASH_LINE;
}

<SKIP,INITIAL>{
{HASH}ifdef {
	yyextra->lexing_if = 1;
	yyextra->space_tokens = 0;
	return HASH_IFDEF;
}

{HASH}ifndef {
	yyextra->lexing_if = 1;
	yyextra->space_tokens = 0;
	return HASH_IFNDEF;
}

{HASH}if/[^_a-zA-Z0-9] {
	yyextra->lexing_if = 1;
	yyextra->space_tokens = 0;
	return HASH_IF;
}

{HASH}elif/[^_a-zA-Z0-9] {
	yyextra->lexing_if = 1;
	yyextra->space_tokens = 0;
	return HASH_ELIF;
}

{HASH}else {
	yyextra->space_tokens = 0;
	return HASH_ELSE;
}

{HASH}endif {
	yyextra->space_tokens = 0;
	return HASH_ENDIF;
}
}

<SKIP>[^\n] {
	if (parser->commented_newlines)
		BEGIN NEWLINE_CATCHUP;
}

{HASH}error.* {
	char *p;
	for (p = yytext; !isalpha(p[0]); p++); /* skip "  #   " */
	p += 5; /* skip "error" */
	glcpp_error(yylloc, yyextra, "#error%s", p);
}

{HASH}define{HSPACE}+ {
	yyextra->space_tokens = 0;
	yy_push_state(DEFINE, yyscanner);
	return HASH_DEFINE;
}

<DEFINE>{IDENTIFIER}/"(" {
	yy_pop_state(yyscanner);
	yylval->str = ralloc_strdup (yyextra, yytext);
	return FUNC_IDENTIFIER;
}

<DEFINE>{IDENTIFIER} {
	yy_pop_state(yyscanner);
	yylval->str = ralloc_strdup (yyextra, yytext);
	return OBJ_IDENTIFIER;
}

{HASH}undef {
	yyextra->space_tokens = 0;
	return HASH_UNDEF;
}

{HASH} {
	yyextra->space_tokens = 0;
	return HASH;
}

{DECIMAL_INTEGER} {
	yylval->str = ralloc_strdup (yyextra, yytext);
	return INTEGER_STRING;
}

{OCTAL_INTEGER} {
	yylval->str = ralloc_strdup (yyextra, yytext);
	return INTEGER_STRING;
}

{HEXADECIMAL_INTEGER} {
	yylval->str = ralloc_strdup (yyextra, yytext);
	return INTEGER_STRING;
}

"<<"  {
	return LEFT_SHIFT;
}

">>" {
	return RIGHT_SHIFT;
}

"<=" {
	return LESS_OR_EQUAL;
}

">=" {
	return GREATER_OR_EQUAL;
}

"==" {
	return EQUAL;
}

"!=" {
	return NOT_EQUAL;
}

"&&" {
	return AND;
}

"||" {
	return OR;
}

"##" {
	if (parser->is_gles)
		glcpp_error(yylloc, yyextra, "Token pasting (##) is illegal in GLES");
	return PASTE;
}

"defined" {
	return DEFINED;
}

{IDENTIFIER} {
	yylval->str = ralloc_strdup (yyextra, yytext);
	return IDENTIFIER;
}

{PUNCTUATION} {
	return yytext[0];
}

{OTHER}+ {
	yylval->str = ralloc_strdup (yyextra, yytext);
	return OTHER;
}

{HSPACE}+ {
	if (yyextra->space_tokens) {
		return SPACE;
	}
}

<SKIP,INITIAL>\n {
	if (parser->commented_newlines) {
		BEGIN NEWLINE_CATCHUP;
	}
	yyextra->lexing_if = 0;
	yylineno++;
	yycolumn = 0;
	return NEWLINE;
}

	/* Handle missing newline at EOF. */
<INITIAL><<EOF>> {
	BEGIN DONE; /* Don't keep matching this rule forever. */
	yyextra->lexing_if = 0;
	return NEWLINE;
}

	/* We don't actually use the UNREACHABLE start condition. We
	only have this action here so that we can pretend to call some
	generated functions, (to avoid "defined but not used"
	warnings. */
<UNREACHABLE>. {
	unput('.');
	yy_top_state(yyextra);
}

%%

void
glcpp_lex_set_source_string(glcpp_parser_t *parser, const char *shader)
{
	yy_scan_string(shader, parser->scanner);
}

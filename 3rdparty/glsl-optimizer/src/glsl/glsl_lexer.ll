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
#include <ctype.h>
#include <limits.h>
#include "strtod.h"
#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_parser.h"

#if defined(_MSC_VER)
#	pragma warning(disable: 4065) // warning C4065: switch statement contains 'default' but no 'case' labels
#	pragma warning(disable: 4244) // warning C4244: '=' : conversion from 'double' to 'float', possible loss of data
#	pragma warning(disable: 4267) // warning C4267: '=' : conversion from 'size_t' to 'int', possible loss of data
#endif // defined(_MSC_VER)

static int classify_identifier(struct _mesa_glsl_parse_state *, const char *);

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif

#define YY_USER_ACTION						\
   do {								\
      yylloc->source = 0;					\
      yylloc->first_column = yycolumn + 1;			\
      yylloc->first_line = yylloc->last_line = yylineno + 1;	\
      yycolumn += yyleng;					\
      yylloc->last_column = yycolumn + 1;			\
   } while(0);

#define YY_USER_INIT yylineno = 0; yycolumn = 0;

/* A macro for handling reserved words and keywords across language versions.
 *
 * Certain words start out as identifiers, become reserved words in
 * later language revisions, and finally become language keywords.
 * This may happen at different times in desktop GLSL and GLSL ES.
 *
 * For example, consider the following lexer rule:
 * samplerBuffer       KEYWORD(130, 0, 140, 0, SAMPLERBUFFER)
 *
 * This means that "samplerBuffer" will be treated as:
 * - a keyword (SAMPLERBUFFER token)         ...in GLSL >= 1.40
 * - a reserved word - error                 ...in GLSL >= 1.30
 * - an identifier                           ...in GLSL <  1.30 or GLSL ES
 */
#define KEYWORD(reserved_glsl, reserved_glsl_es,			\
                allowed_glsl, allowed_glsl_es, token)			\
   KEYWORD_WITH_ALT(reserved_glsl, reserved_glsl_es,			\
                    allowed_glsl, allowed_glsl_es, false, token)

/**
 * Like the KEYWORD macro, but the word is also treated as a keyword
 * if the given boolean expression is true.
 */
#define KEYWORD_WITH_ALT(reserved_glsl, reserved_glsl_es,		\
                         allowed_glsl, allowed_glsl_es,			\
                         alt_expr, token)				\
   do {									\
      if (yyextra->is_version(allowed_glsl, allowed_glsl_es)		\
          || (alt_expr)) {						\
	 return token;							\
      } else if (yyextra->is_version(reserved_glsl,			\
                                     reserved_glsl_es)) {		\
	 _mesa_glsl_error(yylloc, yyextra,				\
			  "illegal use of reserved word `%s'", yytext);	\
	 return ERROR_TOK;						\
      } else {								\
	 void *mem_ctx = yyextra;					\
	 yylval->identifier = ralloc_strdup(mem_ctx, yytext);		\
	 return classify_identifier(yyextra, yytext);			\
      }									\
   } while (0)

/**
 * A macro for handling keywords that have been present in GLSL since
 * its origin, but were changed into reserved words in GLSL 3.00 ES.
 */
#define DEPRECATED_ES_KEYWORD(token)					\
   do {									\
      if (yyextra->is_version(0, 300)) {				\
	 _mesa_glsl_error(yylloc, yyextra,				\
			  "illegal use of reserved word `%s'", yytext);	\
	 return ERROR_TOK;						\
      } else {								\
         return token;							\
      }									\
   } while (0)

static int
literal_integer(char *text, int len, struct _mesa_glsl_parse_state *state,
		YYSTYPE *lval, YYLTYPE *lloc, int base)
{
   bool is_uint = (text[len - 1] == 'u' ||
		   text[len - 1] == 'U');
   const char *digits = text;

   /* Skip "0x" */
   if (base == 16)
      digits += 2;

#ifdef _MSC_VER
   unsigned __int64 value = _strtoui64(digits, NULL, base);
#else
   unsigned long long value = strtoull(digits, NULL, base);
#endif

   lval->n = (int)value;

   if (value > UINT_MAX) {
      /* Note that signed 0xffffffff is valid, not out of range! */
      if (state->is_version(130, 300)) {
	 _mesa_glsl_error(lloc, state,
			  "literal value `%s' out of range", text);
      } else {
	 _mesa_glsl_warning(lloc, state,
			    "literal value `%s' out of range", text);
      }
   } else if (base == 10 && !is_uint && (unsigned)value > (unsigned)INT_MAX + 1) {
      /* Tries to catch unintentionally providing a negative value.
       * Note that -2147483648 is parsed as -(2147483648), so we don't
       * want to warn for INT_MAX.
       */
      _mesa_glsl_warning(lloc, state,
			 "signed literal value `%s' is interpreted as %d",
			 text, lval->n);
   }
   return is_uint ? UINTCONSTANT : INTCONSTANT;
}

#define LITERAL_INTEGER(base) \
   literal_integer(yytext, yyleng, yyextra, yylval, yylloc, base)

%}

%option bison-bridge bison-locations reentrant noyywrap
%option nounput noyy_top_state
%option never-interactive
%option prefix="_mesa_glsl_lexer_"
%option extra-type="struct _mesa_glsl_parse_state *"
%option warn nodefault

	/* Note: When adding any start conditions to this list, you must also
	 * update the "Internal compiler error" catch-all rule near the end of
	 * this file. */
%x PP PRAGMA

DEC_INT		[1-9][0-9]*
HEX_INT		0[xX][0-9a-fA-F]+
OCT_INT		0[0-7]*
INT_T	({DEC_INT}|{HEX_INT}|{OCT_INT})
SPC		[ \t]*
SPCP		[ \t]+
HASH		^{SPC}#{SPC}
%%

[ \r\t]+		;

    /* Preprocessor tokens. */ 
^[ \t]*#[ \t]*$			;
^[ \t]*#[ \t]*version		{ BEGIN PP; return VERSION_TOK; }
^[ \t]*#[ \t]*extension		{ BEGIN PP; return EXTENSION; }
{HASH}line{SPCP}{INT_T}{SPCP}{INT_T}{SPC}$ {
				   /* Eat characters until the first digit is
				    * encountered
				    */
				   char *ptr = yytext;
				   while (!isdigit(*ptr))
				      ptr++;

				   /* Subtract one from the line number because
				    * yylineno is zero-based instead of
				    * one-based.
				    */
				   yylineno = strtol(ptr, &ptr, 0) - 1;
				   yylloc->source = strtol(ptr, NULL, 0);
				}
{HASH}line{SPCP}{INT_T}{SPC}$	{
				   /* Eat characters until the first digit is
				    * encountered
				    */
				   char *ptr = yytext;
				   while (!isdigit(*ptr))
				      ptr++;

				   /* Subtract one from the line number because
				    * yylineno is zero-based instead of
				    * one-based.
				    */
				   yylineno = strtol(ptr, &ptr, 0) - 1;
				}
^{SPC}#{SPC}pragma{SPCP}debug{SPC}\({SPC}on{SPC}\) {
				  BEGIN PP;
				  return PRAGMA_DEBUG_ON;
				}
^{SPC}#{SPC}pragma{SPCP}debug{SPC}\({SPC}off{SPC}\) {
				  BEGIN PP;
				  return PRAGMA_DEBUG_OFF;
				}
^{SPC}#{SPC}pragma{SPCP}optimize{SPC}\({SPC}on{SPC}\) {
				  BEGIN PP;
				  return PRAGMA_OPTIMIZE_ON;
				}
^{SPC}#{SPC}pragma{SPCP}optimize{SPC}\({SPC}off{SPC}\) {
				  BEGIN PP;
				  return PRAGMA_OPTIMIZE_OFF;
				}
^{SPC}#{SPC}pragma{SPCP}STDGL{SPCP}invariant{SPC}\({SPC}all{SPC}\) {
				  BEGIN PP;
				  return PRAGMA_INVARIANT_ALL;
				}
^{SPC}#{SPC}pragma{SPCP}	{ BEGIN PRAGMA; }

<PRAGMA>\n			{ BEGIN 0; yylineno++; yycolumn = 0; }
<PRAGMA>.			{ }

<PP>\/\/[^\n]*			{ }
<PP>[ \t\r]*			{ }
<PP>:				return COLON;
<PP>[_a-zA-Z][_a-zA-Z0-9]*	{
				   void *mem_ctx = yyextra;
				   yylval->identifier = ralloc_strdup(mem_ctx, yytext);
				   return IDENTIFIER;
				}
<PP>[1-9][0-9]*			{
				    yylval->n = strtol(yytext, NULL, 10);
				    return INTCONSTANT;
				}
<PP>\n				{ BEGIN 0; yylineno++; yycolumn = 0; return EOL; }
<PP>.				{ return yytext[0]; }

\n		{ yylineno++; yycolumn = 0; }

attribute	DEPRECATED_ES_KEYWORD(ATTRIBUTE);
const		return CONST_TOK;
bool		return BOOL_TOK;
float		return FLOAT_TOK;
int		return INT_TOK;
uint		KEYWORD(130, 300, 130, 300, UINT_TOK);

break		return BREAK;
continue	return CONTINUE;
do		return DO;
while		return WHILE;
else		return ELSE;
for		return FOR;
if		return IF;
discard		return DISCARD;
return		return RETURN;

bvec2		return BVEC2;
bvec3		return BVEC3;
bvec4		return BVEC4;
ivec2		return IVEC2;
ivec3		return IVEC3;
ivec4		return IVEC4;
uvec2		KEYWORD(130, 300, 130, 300, UVEC2);
uvec3		KEYWORD(130, 300, 130, 300, UVEC3);
uvec4		KEYWORD(130, 300, 130, 300, UVEC4);
vec2		return VEC2;
vec3		return VEC3;
vec4		return VEC4;
mat2		return MAT2X2;
mat3		return MAT3X3;
mat4		return MAT4X4;
mat2x2		KEYWORD(120, 300, 120, 300, MAT2X2);
mat2x3		KEYWORD(120, 300, 120, 300, MAT2X3);
mat2x4		KEYWORD(120, 300, 120, 300, MAT2X4);
mat3x2		KEYWORD(120, 300, 120, 300, MAT3X2);
mat3x3		KEYWORD(120, 300, 120, 300, MAT3X3);
mat3x4		KEYWORD(120, 300, 120, 300, MAT3X4);
mat4x2		KEYWORD(120, 300, 120, 300, MAT4X2);
mat4x3		KEYWORD(120, 300, 120, 300, MAT4X3);
mat4x4		KEYWORD(120, 300, 120, 300, MAT4X4);

in		return IN_TOK;
out		return OUT_TOK;
inout		return INOUT_TOK;
uniform		return UNIFORM;
varying		DEPRECATED_ES_KEYWORD(VARYING);
centroid	KEYWORD(120, 300, 120, 300, CENTROID);
invariant	KEYWORD(120, 100, 120, 100, INVARIANT);
flat		KEYWORD(130, 100, 130, 300, FLAT);
smooth		KEYWORD(130, 300, 130, 300, SMOOTH);
noperspective	KEYWORD(130, 300, 130, 0, NOPERSPECTIVE);

sampler1D	DEPRECATED_ES_KEYWORD(SAMPLER1D);
sampler2D	return SAMPLER2D;
sampler3D	return SAMPLER3D;
samplerCube	return SAMPLERCUBE;
sampler1DArray	KEYWORD(130, 300, 130, 0, SAMPLER1DARRAY);
sampler2DArray	KEYWORD(130, 300, 130, 300, SAMPLER2DARRAY);
sampler1DShadow	DEPRECATED_ES_KEYWORD(SAMPLER1DSHADOW);
sampler2DShadow	return SAMPLER2DSHADOW;
samplerCubeShadow	KEYWORD(130, 300, 130, 300, SAMPLERCUBESHADOW);
sampler1DArrayShadow	KEYWORD(130, 300, 130, 0, SAMPLER1DARRAYSHADOW);
sampler2DArrayShadow	KEYWORD(130, 300, 130, 300, SAMPLER2DARRAYSHADOW);
isampler1D		KEYWORD(130, 300, 130, 0, ISAMPLER1D);
isampler2D		KEYWORD(130, 300, 130, 300, ISAMPLER2D);
isampler3D		KEYWORD(130, 300, 130, 300, ISAMPLER3D);
isamplerCube		KEYWORD(130, 300, 130, 300, ISAMPLERCUBE);
isampler1DArray		KEYWORD(130, 300, 130, 0, ISAMPLER1DARRAY);
isampler2DArray		KEYWORD(130, 300, 130, 300, ISAMPLER2DARRAY);
usampler1D		KEYWORD(130, 300, 130, 0, USAMPLER1D);
usampler2D		KEYWORD(130, 300, 130, 300, USAMPLER2D);
usampler3D		KEYWORD(130, 300, 130, 300, USAMPLER3D);
usamplerCube		KEYWORD(130, 300, 130, 300, USAMPLERCUBE);
usampler1DArray		KEYWORD(130, 300, 130, 0, USAMPLER1DARRAY);
usampler2DArray		KEYWORD(130, 300, 130, 300, USAMPLER2DARRAY);

   /* additional keywords in ARB_texture_multisample, included in GLSL 1.50 */
   /* these are reserved but not defined in GLSL 3.00 */
sampler2DMS        KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, SAMPLER2DMS);
isampler2DMS       KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, ISAMPLER2DMS);
usampler2DMS       KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, USAMPLER2DMS);
sampler2DMSArray   KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, SAMPLER2DMSARRAY);
isampler2DMSArray  KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, ISAMPLER2DMSARRAY);
usampler2DMSArray  KEYWORD_WITH_ALT(150, 300, 150, 0, yyextra->ARB_texture_multisample_enable, USAMPLER2DMSARRAY);

   /* keywords available with ARB_texture_cube_map_array_enable extension on desktop GLSL */
samplerCubeArray   KEYWORD_WITH_ALT(400, 0, 400, 0, yyextra->ARB_texture_cube_map_array_enable, SAMPLERCUBEARRAY);
isamplerCubeArray KEYWORD_WITH_ALT(400, 0, 400, 0, yyextra->ARB_texture_cube_map_array_enable, ISAMPLERCUBEARRAY);
usamplerCubeArray KEYWORD_WITH_ALT(400, 0, 400, 0, yyextra->ARB_texture_cube_map_array_enable, USAMPLERCUBEARRAY);
samplerCubeArrayShadow   KEYWORD_WITH_ALT(400, 0, 400, 0, yyextra->ARB_texture_cube_map_array_enable, SAMPLERCUBEARRAYSHADOW);

samplerExternalOES		{
			  if (yyextra->OES_EGL_image_external_enable)
			     return SAMPLEREXTERNALOES;
			  else
			     return IDENTIFIER;
		}

   /* keywords available with ARB_gpu_shader5 */
precise		KEYWORD_WITH_ALT(400, 0, 400, 0, yyextra->ARB_gpu_shader5_enable, PRECISE);

   /* keywords available with ARB_shader_image_load_store */
image1D         KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE1D);
image2D         KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE2D);
image3D         KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE3D);
image2DRect     KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE2DRECT);
imageCube       KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGECUBE);
imageBuffer     KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGEBUFFER);
image1DArray    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE1DARRAY);
image2DArray    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE2DARRAY);
imageCubeArray  KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGECUBEARRAY);
image2DMS       KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE2DMS);
image2DMSArray  KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IMAGE2DMSARRAY);
iimage1D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE1D);
iimage2D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE2D);
iimage3D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE3D);
iimage2DRect    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE2DRECT);
iimageCube      KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGECUBE);
iimageBuffer    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGEBUFFER);
iimage1DArray   KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE1DARRAY);
iimage2DArray   KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE2DARRAY);
iimageCubeArray KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGECUBEARRAY);
iimage2DMS      KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE2DMS);
iimage2DMSArray KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, IIMAGE2DMSARRAY);
uimage1D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE1D);
uimage2D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE2D);
uimage3D        KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE3D);
uimage2DRect    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE2DRECT);
uimageCube      KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGECUBE);
uimageBuffer    KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGEBUFFER);
uimage1DArray   KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE1DARRAY);
uimage2DArray   KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE2DARRAY);
uimageCubeArray KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGECUBEARRAY);
uimage2DMS      KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE2DMS);
uimage2DMSArray KEYWORD_WITH_ALT(130, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, UIMAGE2DMSARRAY);
image1DShadow           KEYWORD(130, 300, 0, 0, IMAGE1DSHADOW);
image2DShadow           KEYWORD(130, 300, 0, 0, IMAGE2DSHADOW);
image1DArrayShadow      KEYWORD(130, 300, 0, 0, IMAGE1DARRAYSHADOW);
image2DArrayShadow      KEYWORD(130, 300, 0, 0, IMAGE2DARRAYSHADOW);

coherent	KEYWORD_WITH_ALT(420, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, COHERENT);
volatile	KEYWORD_WITH_ALT(110, 100, 420, 0, yyextra->ARB_shader_image_load_store_enable, VOLATILE);
restrict	KEYWORD_WITH_ALT(420, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, RESTRICT);
readonly	KEYWORD_WITH_ALT(420, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, READONLY);
writeonly	KEYWORD_WITH_ALT(420, 300, 420, 0, yyextra->ARB_shader_image_load_store_enable, WRITEONLY);

atomic_uint     KEYWORD_WITH_ALT(420, 300, 420, 0, yyextra->ARB_shader_atomic_counters_enable, ATOMIC_UINT);

struct		return STRUCT;
void		return VOID_TOK;

layout		{
		  if ((yyextra->is_version(140, 300))
		      || yyextra->AMD_conservative_depth_enable
		      || yyextra->ARB_conservative_depth_enable
		      || yyextra->ARB_explicit_attrib_location_enable
		      || yyextra->ARB_explicit_uniform_location_enable
                      || yyextra->has_separate_shader_objects()
		      || yyextra->ARB_uniform_buffer_object_enable
		      || yyextra->ARB_fragment_coord_conventions_enable
                      || yyextra->ARB_shading_language_420pack_enable
                      || yyextra->ARB_compute_shader_enable) {
		      return LAYOUT_TOK;
		   } else {
		      void *mem_ctx = yyextra;
		      yylval->identifier = ralloc_strdup(mem_ctx, yytext);
		      return classify_identifier(yyextra, yytext);
		   }
		}

\+\+		return INC_OP;
--		return DEC_OP;
\<=		return LE_OP;
>=		return GE_OP;
==		return EQ_OP;
!=		return NE_OP;
&&		return AND_OP;
\|\|		return OR_OP;
"^^"		return XOR_OP;
"<<"		return LEFT_OP;
">>"		return RIGHT_OP;

\*=		return MUL_ASSIGN;
\/=		return DIV_ASSIGN;
\+=		return ADD_ASSIGN;
\%=		return MOD_ASSIGN;
\<\<=		return LEFT_ASSIGN;
>>=		return RIGHT_ASSIGN;
&=		return AND_ASSIGN;
"^="		return XOR_ASSIGN;
\|=		return OR_ASSIGN;
-=		return SUB_ASSIGN;

[1-9][0-9]*[uU]?	{
			    return LITERAL_INTEGER(10);
			}
0[xX][0-9a-fA-F]+[uU]?	{
			    return LITERAL_INTEGER(16);
			}
0[0-7]*[uU]?		{
			    return LITERAL_INTEGER(8);
			}

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)?[fF]?	{
			    yylval->real = glsl_strtof(yytext, NULL);
			    return FLOATCONSTANT;
			}
\.[0-9]+([eE][+-]?[0-9]+)?[fF]?		{
			    yylval->real = glsl_strtof(yytext, NULL);
			    return FLOATCONSTANT;
			}
[0-9]+\.([eE][+-]?[0-9]+)?[fF]?		{
			    yylval->real = glsl_strtof(yytext, NULL);
			    return FLOATCONSTANT;
			}
[0-9]+[eE][+-]?[0-9]+[fF]?		{
			    yylval->real = glsl_strtof(yytext, NULL);
			    return FLOATCONSTANT;
			}
[0-9]+[fF]		{
			    yylval->real = glsl_strtof(yytext, NULL);
			    return FLOATCONSTANT;
			}

true			{
			    yylval->n = 1;
			    return BOOLCONSTANT;
			}
false			{
			    yylval->n = 0;
			    return BOOLCONSTANT;
			}


    /* Reserved words in GLSL 1.10. */
asm		KEYWORD(110, 100, 0, 0, ASM);
class		KEYWORD(110, 100, 0, 0, CLASS);
union		KEYWORD(110, 100, 0, 0, UNION);
enum		KEYWORD(110, 100, 0, 0, ENUM);
typedef		KEYWORD(110, 100, 0, 0, TYPEDEF);
template	KEYWORD(110, 100, 0, 0, TEMPLATE);
this		KEYWORD(110, 100, 0, 0, THIS);
packed		KEYWORD_WITH_ALT(110, 100, 140, 300, yyextra->ARB_uniform_buffer_object_enable, PACKED_TOK);
goto		KEYWORD(110, 100, 0, 0, GOTO);
switch		KEYWORD(110, 100, 130, 300, SWITCH);
default		KEYWORD(110, 100, 130, 300, DEFAULT);
inline		KEYWORD(110, 100, 0, 0, INLINE_TOK);
noinline	KEYWORD(110, 100, 0, 0, NOINLINE);
public		KEYWORD(110, 100, 0, 0, PUBLIC_TOK);
static		KEYWORD(110, 100, 0, 0, STATIC);
extern		KEYWORD(110, 100, 0, 0, EXTERN);
external	KEYWORD(110, 100, 0, 0, EXTERNAL);
interface	KEYWORD(110, 100, 0, 0, INTERFACE);
long		KEYWORD(110, 100, 0, 0, LONG_TOK);
short		KEYWORD(110, 100, 0, 0, SHORT_TOK);
double		KEYWORD(110, 100, 400, 0, DOUBLE_TOK);
half		KEYWORD(110, 100, 0, 0, HALF);
fixed		KEYWORD(110, 100, 0, 0, FIXED_TOK);
unsigned	KEYWORD(110, 100, 0, 0, UNSIGNED);
input		KEYWORD(110, 100, 0, 0, INPUT_TOK);
output		KEYWORD(110, 100, 0, 0, OUTPUT);
hvec2		KEYWORD(110, 100, 0, 0, HVEC2);
hvec3		KEYWORD(110, 100, 0, 0, HVEC3);
hvec4		KEYWORD(110, 100, 0, 0, HVEC4);
dvec2		KEYWORD(110, 100, 400, 0, DVEC2);
dvec3		KEYWORD(110, 100, 400, 0, DVEC3);
dvec4		KEYWORD(110, 100, 400, 0, DVEC4);
fvec2		KEYWORD(110, 100, 0, 0, FVEC2);
fvec3		KEYWORD(110, 100, 0, 0, FVEC3);
fvec4		KEYWORD(110, 100, 0, 0, FVEC4);
sampler2DRect		DEPRECATED_ES_KEYWORD(SAMPLER2DRECT);
sampler3DRect		KEYWORD(110, 100, 0, 0, SAMPLER3DRECT);
sampler2DRectShadow	DEPRECATED_ES_KEYWORD(SAMPLER2DRECTSHADOW);
sizeof		KEYWORD(110, 100, 0, 0, SIZEOF);
cast		KEYWORD(110, 100, 0, 0, CAST);
namespace	KEYWORD(110, 100, 0, 0, NAMESPACE);
using		KEYWORD(110, 100, 0, 0, USING);

    /* Additional reserved words in GLSL 1.20. */
lowp		KEYWORD(120, 100, 130, 100, LOWP);
mediump		KEYWORD(120, 100, 130, 100, MEDIUMP);
highp		KEYWORD(120, 100, 130, 100, HIGHP);
precision	KEYWORD(120, 100, 130, 100, PRECISION);

    /* Additional reserved words in GLSL 1.30. */
case		KEYWORD(130, 300, 130, 300, CASE);
common		KEYWORD(130, 300, 0, 0, COMMON);
partition	KEYWORD(130, 300, 0, 0, PARTITION);
active		KEYWORD(130, 300, 0, 0, ACTIVE);
superp		KEYWORD(130, 100, 0, 0, SUPERP);
samplerBuffer	KEYWORD(130, 300, 140, 0, SAMPLERBUFFER);
filter		KEYWORD(130, 300, 0, 0, FILTER);
row_major	KEYWORD_WITH_ALT(130, 0, 140, 0, yyextra->ARB_uniform_buffer_object_enable && !yyextra->es_shader, ROW_MAJOR);

    /* Additional reserved words in GLSL 1.40 */
isampler2DRect	KEYWORD(140, 300, 140, 0, ISAMPLER2DRECT);
usampler2DRect	KEYWORD(140, 300, 140, 0, USAMPLER2DRECT);
isamplerBuffer	KEYWORD(140, 300, 140, 0, ISAMPLERBUFFER);
usamplerBuffer	KEYWORD(140, 300, 140, 0, USAMPLERBUFFER);

    /* Additional reserved words in GLSL ES 3.00 */
resource	KEYWORD(0, 300, 0, 0, RESOURCE);
patch		KEYWORD(0, 300, 0, 0, PATCH);
sample		KEYWORD_WITH_ALT(400, 300, 400, 0, yyextra->ARB_gpu_shader5_enable, SAMPLE);
subroutine	KEYWORD(0, 300, 0, 0, SUBROUTINE);


[_a-zA-Z][_a-zA-Z0-9]*	{
			    struct _mesa_glsl_parse_state *state = yyextra;
			    void *ctx = state;	
			    yylval->identifier = ralloc_strdup(ctx, yytext);
			    return classify_identifier(state, yytext);
			}

.			{ return yytext[0]; }

%%

int
classify_identifier(struct _mesa_glsl_parse_state *state, const char *name)
{
   if (state->symbols->get_variable(name) || state->symbols->get_function(name))
      return IDENTIFIER;
   else if (state->symbols->get_type(name))
      return TYPE_IDENTIFIER;
   else
      return NEW_IDENTIFIER;
}

void
_mesa_glsl_lexer_ctor(struct _mesa_glsl_parse_state *state, const char *string)
{
   yylex_init_extra(state, & state->scanner);
   yy_scan_string(string, state->scanner);
}

void
_mesa_glsl_lexer_dtor(struct _mesa_glsl_parse_state *state)
{
   yylex_destroy(state->scanner);
}

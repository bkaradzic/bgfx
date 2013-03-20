/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     CONST_TOK = 259,
     BOOL_TOK = 260,
     FLOAT_TOK = 261,
     INT_TOK = 262,
     UINT_TOK = 263,
     BREAK = 264,
     CONTINUE = 265,
     DO = 266,
     ELSE = 267,
     FOR = 268,
     IF = 269,
     DISCARD = 270,
     RETURN = 271,
     SWITCH = 272,
     CASE = 273,
     DEFAULT = 274,
     BVEC2 = 275,
     BVEC3 = 276,
     BVEC4 = 277,
     IVEC2 = 278,
     IVEC3 = 279,
     IVEC4 = 280,
     UVEC2 = 281,
     UVEC3 = 282,
     UVEC4 = 283,
     VEC2 = 284,
     VEC3 = 285,
     VEC4 = 286,
     CENTROID = 287,
     IN_TOK = 288,
     OUT_TOK = 289,
     INOUT_TOK = 290,
     UNIFORM = 291,
     VARYING = 292,
     NOPERSPECTIVE = 293,
     FLAT = 294,
     SMOOTH = 295,
     MAT2X2 = 296,
     MAT2X3 = 297,
     MAT2X4 = 298,
     MAT3X2 = 299,
     MAT3X3 = 300,
     MAT3X4 = 301,
     MAT4X2 = 302,
     MAT4X3 = 303,
     MAT4X4 = 304,
     SAMPLER1D = 305,
     SAMPLER2D = 306,
     SAMPLER3D = 307,
     SAMPLERCUBE = 308,
     SAMPLER1DSHADOW = 309,
     SAMPLER2DSHADOW = 310,
     SAMPLERCUBESHADOW = 311,
     SAMPLER1DARRAY = 312,
     SAMPLER2DARRAY = 313,
     SAMPLER1DARRAYSHADOW = 314,
     SAMPLER2DARRAYSHADOW = 315,
     ISAMPLER1D = 316,
     ISAMPLER2D = 317,
     ISAMPLER3D = 318,
     ISAMPLERCUBE = 319,
     ISAMPLER1DARRAY = 320,
     ISAMPLER2DARRAY = 321,
     USAMPLER1D = 322,
     USAMPLER2D = 323,
     USAMPLER3D = 324,
     USAMPLERCUBE = 325,
     USAMPLER1DARRAY = 326,
     USAMPLER2DARRAY = 327,
     SAMPLER2DRECT = 328,
     ISAMPLER2DRECT = 329,
     USAMPLER2DRECT = 330,
     SAMPLER2DRECTSHADOW = 331,
     SAMPLERBUFFER = 332,
     ISAMPLERBUFFER = 333,
     USAMPLERBUFFER = 334,
     SAMPLEREXTERNALOES = 335,
     STRUCT = 336,
     VOID_TOK = 337,
     WHILE = 338,
     IDENTIFIER = 339,
     TYPE_IDENTIFIER = 340,
     NEW_IDENTIFIER = 341,
     FLOATCONSTANT = 342,
     INTCONSTANT = 343,
     UINTCONSTANT = 344,
     BOOLCONSTANT = 345,
     FIELD_SELECTION = 346,
     LEFT_OP = 347,
     RIGHT_OP = 348,
     INC_OP = 349,
     DEC_OP = 350,
     LE_OP = 351,
     GE_OP = 352,
     EQ_OP = 353,
     NE_OP = 354,
     AND_OP = 355,
     OR_OP = 356,
     XOR_OP = 357,
     MUL_ASSIGN = 358,
     DIV_ASSIGN = 359,
     ADD_ASSIGN = 360,
     MOD_ASSIGN = 361,
     LEFT_ASSIGN = 362,
     RIGHT_ASSIGN = 363,
     AND_ASSIGN = 364,
     XOR_ASSIGN = 365,
     OR_ASSIGN = 366,
     SUB_ASSIGN = 367,
     INVARIANT = 368,
     LOWP = 369,
     MEDIUMP = 370,
     HIGHP = 371,
     SUPERP = 372,
     PRECISION = 373,
     VERSION_TOK = 374,
     EXTENSION = 375,
     LINE = 376,
     COLON = 377,
     EOL = 378,
     INTERFACE = 379,
     OUTPUT = 380,
     PRAGMA_DEBUG_ON = 381,
     PRAGMA_DEBUG_OFF = 382,
     PRAGMA_OPTIMIZE_ON = 383,
     PRAGMA_OPTIMIZE_OFF = 384,
     PRAGMA_INVARIANT_ALL = 385,
     LAYOUT_TOK = 386,
     ASM = 387,
     CLASS = 388,
     UNION = 389,
     ENUM = 390,
     TYPEDEF = 391,
     TEMPLATE = 392,
     THIS = 393,
     PACKED_TOK = 394,
     GOTO = 395,
     INLINE_TOK = 396,
     NOINLINE = 397,
     VOLATILE = 398,
     PUBLIC_TOK = 399,
     STATIC = 400,
     EXTERN = 401,
     EXTERNAL = 402,
     LONG_TOK = 403,
     SHORT_TOK = 404,
     DOUBLE_TOK = 405,
     HALF = 406,
     FIXED_TOK = 407,
     UNSIGNED = 408,
     INPUT_TOK = 409,
     OUPTUT = 410,
     HVEC2 = 411,
     HVEC3 = 412,
     HVEC4 = 413,
     DVEC2 = 414,
     DVEC3 = 415,
     DVEC4 = 416,
     FVEC2 = 417,
     FVEC3 = 418,
     FVEC4 = 419,
     SAMPLER3DRECT = 420,
     SIZEOF = 421,
     CAST = 422,
     NAMESPACE = 423,
     USING = 424,
     ERROR_TOK = 425,
     COMMON = 426,
     PARTITION = 427,
     ACTIVE = 428,
     FILTER = 429,
     IMAGE1D = 430,
     IMAGE2D = 431,
     IMAGE3D = 432,
     IMAGECUBE = 433,
     IMAGE1DARRAY = 434,
     IMAGE2DARRAY = 435,
     IIMAGE1D = 436,
     IIMAGE2D = 437,
     IIMAGE3D = 438,
     IIMAGECUBE = 439,
     IIMAGE1DARRAY = 440,
     IIMAGE2DARRAY = 441,
     UIMAGE1D = 442,
     UIMAGE2D = 443,
     UIMAGE3D = 444,
     UIMAGECUBE = 445,
     UIMAGE1DARRAY = 446,
     UIMAGE2DARRAY = 447,
     IMAGE1DSHADOW = 448,
     IMAGE2DSHADOW = 449,
     IMAGEBUFFER = 450,
     IIMAGEBUFFER = 451,
     UIMAGEBUFFER = 452,
     IMAGE1DARRAYSHADOW = 453,
     IMAGE2DARRAYSHADOW = 454,
     ROW_MAJOR = 455
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 64 "src/glsl/glsl_parser.yy"

   int n;
   float real;
   const char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
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

   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;



/* Line 2068 of yacc.c  */
#line 287 "src/glsl/glsl_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




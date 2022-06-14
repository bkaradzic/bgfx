/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY__MESA_GLSL_SRC_GLSL_GLSL_PARSER_H_INCLUDED
# define YY__MESA_GLSL_SRC_GLSL_GLSL_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int _mesa_glsl_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    SAMPLE = 293,
    NOPERSPECTIVE = 294,
    FLAT = 295,
    SMOOTH = 296,
    MAT2X2 = 297,
    MAT2X3 = 298,
    MAT2X4 = 299,
    MAT3X2 = 300,
    MAT3X3 = 301,
    MAT3X4 = 302,
    MAT4X2 = 303,
    MAT4X3 = 304,
    MAT4X4 = 305,
    SAMPLER1D = 306,
    SAMPLER2D = 307,
    SAMPLER3D = 308,
    SAMPLERCUBE = 309,
    SAMPLER1DSHADOW = 310,
    SAMPLER2DSHADOW = 311,
    SAMPLERCUBESHADOW = 312,
    SAMPLER1DARRAY = 313,
    SAMPLER2DARRAY = 314,
    SAMPLER1DARRAYSHADOW = 315,
    SAMPLER2DARRAYSHADOW = 316,
    SAMPLERCUBEARRAY = 317,
    SAMPLERCUBEARRAYSHADOW = 318,
    ISAMPLER1D = 319,
    ISAMPLER2D = 320,
    ISAMPLER3D = 321,
    ISAMPLERCUBE = 322,
    ISAMPLER1DARRAY = 323,
    ISAMPLER2DARRAY = 324,
    ISAMPLERCUBEARRAY = 325,
    USAMPLER1D = 326,
    USAMPLER2D = 327,
    USAMPLER3D = 328,
    USAMPLERCUBE = 329,
    USAMPLER1DARRAY = 330,
    USAMPLER2DARRAY = 331,
    USAMPLERCUBEARRAY = 332,
    SAMPLER2DRECT = 333,
    ISAMPLER2DRECT = 334,
    USAMPLER2DRECT = 335,
    SAMPLER2DRECTSHADOW = 336,
    SAMPLERBUFFER = 337,
    ISAMPLERBUFFER = 338,
    USAMPLERBUFFER = 339,
    SAMPLER2DMS = 340,
    ISAMPLER2DMS = 341,
    USAMPLER2DMS = 342,
    SAMPLER2DMSARRAY = 343,
    ISAMPLER2DMSARRAY = 344,
    USAMPLER2DMSARRAY = 345,
    SAMPLEREXTERNALOES = 346,
    IMAGE1D = 347,
    IMAGE2D = 348,
    IMAGE3D = 349,
    IMAGE2DRECT = 350,
    IMAGECUBE = 351,
    IMAGEBUFFER = 352,
    IMAGE1DARRAY = 353,
    IMAGE2DARRAY = 354,
    IMAGECUBEARRAY = 355,
    IMAGE2DMS = 356,
    IMAGE2DMSARRAY = 357,
    IIMAGE1D = 358,
    IIMAGE2D = 359,
    IIMAGE3D = 360,
    IIMAGE2DRECT = 361,
    IIMAGECUBE = 362,
    IIMAGEBUFFER = 363,
    IIMAGE1DARRAY = 364,
    IIMAGE2DARRAY = 365,
    IIMAGECUBEARRAY = 366,
    IIMAGE2DMS = 367,
    IIMAGE2DMSARRAY = 368,
    UIMAGE1D = 369,
    UIMAGE2D = 370,
    UIMAGE3D = 371,
    UIMAGE2DRECT = 372,
    UIMAGECUBE = 373,
    UIMAGEBUFFER = 374,
    UIMAGE1DARRAY = 375,
    UIMAGE2DARRAY = 376,
    UIMAGECUBEARRAY = 377,
    UIMAGE2DMS = 378,
    UIMAGE2DMSARRAY = 379,
    IMAGE1DSHADOW = 380,
    IMAGE2DSHADOW = 381,
    IMAGE1DARRAYSHADOW = 382,
    IMAGE2DARRAYSHADOW = 383,
    COHERENT = 384,
    VOLATILE = 385,
    RESTRICT = 386,
    READONLY = 387,
    WRITEONLY = 388,
    ATOMIC_UINT = 389,
    STRUCT = 390,
    VOID_TOK = 391,
    WHILE = 392,
    IDENTIFIER = 393,
    TYPE_IDENTIFIER = 394,
    NEW_IDENTIFIER = 395,
    FLOATCONSTANT = 396,
    INTCONSTANT = 397,
    UINTCONSTANT = 398,
    BOOLCONSTANT = 399,
    FIELD_SELECTION = 400,
    LEFT_OP = 401,
    RIGHT_OP = 402,
    INC_OP = 403,
    DEC_OP = 404,
    LE_OP = 405,
    GE_OP = 406,
    EQ_OP = 407,
    NE_OP = 408,
    AND_OP = 409,
    OR_OP = 410,
    XOR_OP = 411,
    MUL_ASSIGN = 412,
    DIV_ASSIGN = 413,
    ADD_ASSIGN = 414,
    MOD_ASSIGN = 415,
    LEFT_ASSIGN = 416,
    RIGHT_ASSIGN = 417,
    AND_ASSIGN = 418,
    XOR_ASSIGN = 419,
    OR_ASSIGN = 420,
    SUB_ASSIGN = 421,
    INVARIANT = 422,
    PRECISE = 423,
    LOWP = 424,
    MEDIUMP = 425,
    HIGHP = 426,
    SUPERP = 427,
    PRECISION = 428,
    VERSION_TOK = 429,
    EXTENSION = 430,
    LINE = 431,
    COLON = 432,
    EOL = 433,
    INTERFACE = 434,
    OUTPUT = 435,
    PRAGMA_DEBUG_ON = 436,
    PRAGMA_DEBUG_OFF = 437,
    PRAGMA_OPTIMIZE_ON = 438,
    PRAGMA_OPTIMIZE_OFF = 439,
    PRAGMA_INVARIANT_ALL = 440,
    LAYOUT_TOK = 441,
    ASM = 442,
    CLASS = 443,
    UNION = 444,
    ENUM = 445,
    TYPEDEF = 446,
    TEMPLATE = 447,
    THIS = 448,
    PACKED_TOK = 449,
    GOTO = 450,
    INLINE_TOK = 451,
    NOINLINE = 452,
    PUBLIC_TOK = 453,
    STATIC = 454,
    EXTERN = 455,
    EXTERNAL = 456,
    LONG_TOK = 457,
    SHORT_TOK = 458,
    DOUBLE_TOK = 459,
    HALF = 460,
    FIXED_TOK = 461,
    UNSIGNED = 462,
    INPUT_TOK = 463,
    HVEC2 = 464,
    HVEC3 = 465,
    HVEC4 = 466,
    DVEC2 = 467,
    DVEC3 = 468,
    DVEC4 = 469,
    FVEC2 = 470,
    FVEC3 = 471,
    FVEC4 = 472,
    SAMPLER3DRECT = 473,
    SIZEOF = 474,
    CAST = 475,
    NAMESPACE = 476,
    USING = 477,
    RESOURCE = 478,
    PATCH = 479,
    SUBROUTINE = 480,
    ERROR_TOK = 481,
    COMMON = 482,
    PARTITION = 483,
    ACTIVE = 484,
    FILTER = 485,
    ROW_MAJOR = 486,
    THEN = 487
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 99 "src/glsl/glsl_parser.yy"

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

#line 327 "src/glsl/glsl_parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int _mesa_glsl_parse (struct _mesa_glsl_parse_state *state);

#endif /* !YY__MESA_GLSL_SRC_GLSL_GLSL_PARSER_H_INCLUDED  */

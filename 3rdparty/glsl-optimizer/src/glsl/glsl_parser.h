/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    SAMPLERCUBEARRAY = 316,
    SAMPLERCUBEARRAYSHADOW = 317,
    ISAMPLER1D = 318,
    ISAMPLER2D = 319,
    ISAMPLER3D = 320,
    ISAMPLERCUBE = 321,
    ISAMPLER1DARRAY = 322,
    ISAMPLER2DARRAY = 323,
    ISAMPLERCUBEARRAY = 324,
    USAMPLER1D = 325,
    USAMPLER2D = 326,
    USAMPLER3D = 327,
    USAMPLERCUBE = 328,
    USAMPLER1DARRAY = 329,
    USAMPLER2DARRAY = 330,
    USAMPLERCUBEARRAY = 331,
    SAMPLER2DRECT = 332,
    ISAMPLER2DRECT = 333,
    USAMPLER2DRECT = 334,
    SAMPLER2DRECTSHADOW = 335,
    SAMPLERBUFFER = 336,
    ISAMPLERBUFFER = 337,
    USAMPLERBUFFER = 338,
    SAMPLER2DMS = 339,
    ISAMPLER2DMS = 340,
    USAMPLER2DMS = 341,
    SAMPLER2DMSARRAY = 342,
    ISAMPLER2DMSARRAY = 343,
    USAMPLER2DMSARRAY = 344,
    SAMPLEREXTERNALOES = 345,
    IMAGE1D = 346,
    IMAGE2D = 347,
    IMAGE3D = 348,
    IMAGE2DRECT = 349,
    IMAGECUBE = 350,
    IMAGEBUFFER = 351,
    IMAGE1DARRAY = 352,
    IMAGE2DARRAY = 353,
    IMAGECUBEARRAY = 354,
    IMAGE2DMS = 355,
    IMAGE2DMSARRAY = 356,
    IIMAGE1D = 357,
    IIMAGE2D = 358,
    IIMAGE3D = 359,
    IIMAGE2DRECT = 360,
    IIMAGECUBE = 361,
    IIMAGEBUFFER = 362,
    IIMAGE1DARRAY = 363,
    IIMAGE2DARRAY = 364,
    IIMAGECUBEARRAY = 365,
    IIMAGE2DMS = 366,
    IIMAGE2DMSARRAY = 367,
    UIMAGE1D = 368,
    UIMAGE2D = 369,
    UIMAGE3D = 370,
    UIMAGE2DRECT = 371,
    UIMAGECUBE = 372,
    UIMAGEBUFFER = 373,
    UIMAGE1DARRAY = 374,
    UIMAGE2DARRAY = 375,
    UIMAGECUBEARRAY = 376,
    UIMAGE2DMS = 377,
    UIMAGE2DMSARRAY = 378,
    IMAGE1DSHADOW = 379,
    IMAGE2DSHADOW = 380,
    IMAGE1DARRAYSHADOW = 381,
    IMAGE2DARRAYSHADOW = 382,
    COHERENT = 383,
    VOLATILE = 384,
    RESTRICT = 385,
    READONLY = 386,
    WRITEONLY = 387,
    ATOMIC_UINT = 388,
    STRUCT = 389,
    VOID_TOK = 390,
    WHILE = 391,
    IDENTIFIER = 392,
    TYPE_IDENTIFIER = 393,
    NEW_IDENTIFIER = 394,
    FLOATCONSTANT = 395,
    INTCONSTANT = 396,
    UINTCONSTANT = 397,
    BOOLCONSTANT = 398,
    FIELD_SELECTION = 399,
    LEFT_OP = 400,
    RIGHT_OP = 401,
    INC_OP = 402,
    DEC_OP = 403,
    LE_OP = 404,
    GE_OP = 405,
    EQ_OP = 406,
    NE_OP = 407,
    AND_OP = 408,
    OR_OP = 409,
    XOR_OP = 410,
    MUL_ASSIGN = 411,
    DIV_ASSIGN = 412,
    ADD_ASSIGN = 413,
    MOD_ASSIGN = 414,
    LEFT_ASSIGN = 415,
    RIGHT_ASSIGN = 416,
    AND_ASSIGN = 417,
    XOR_ASSIGN = 418,
    OR_ASSIGN = 419,
    SUB_ASSIGN = 420,
    INVARIANT = 421,
    LOWP = 422,
    MEDIUMP = 423,
    HIGHP = 424,
    SUPERP = 425,
    PRECISION = 426,
    VERSION_TOK = 427,
    EXTENSION = 428,
    LINE = 429,
    COLON = 430,
    EOL = 431,
    INTERFACE = 432,
    OUTPUT = 433,
    PRAGMA_DEBUG_ON = 434,
    PRAGMA_DEBUG_OFF = 435,
    PRAGMA_OPTIMIZE_ON = 436,
    PRAGMA_OPTIMIZE_OFF = 437,
    PRAGMA_INVARIANT_ALL = 438,
    LAYOUT_TOK = 439,
    ASM = 440,
    CLASS = 441,
    UNION = 442,
    ENUM = 443,
    TYPEDEF = 444,
    TEMPLATE = 445,
    THIS = 446,
    PACKED_TOK = 447,
    GOTO = 448,
    INLINE_TOK = 449,
    NOINLINE = 450,
    PUBLIC_TOK = 451,
    STATIC = 452,
    EXTERN = 453,
    EXTERNAL = 454,
    LONG_TOK = 455,
    SHORT_TOK = 456,
    DOUBLE_TOK = 457,
    HALF = 458,
    FIXED_TOK = 459,
    UNSIGNED = 460,
    INPUT_TOK = 461,
    OUPTUT = 462,
    HVEC2 = 463,
    HVEC3 = 464,
    HVEC4 = 465,
    DVEC2 = 466,
    DVEC3 = 467,
    DVEC4 = 468,
    FVEC2 = 469,
    FVEC3 = 470,
    FVEC4 = 471,
    SAMPLER3DRECT = 472,
    SIZEOF = 473,
    CAST = 474,
    NAMESPACE = 475,
    USING = 476,
    RESOURCE = 477,
    PATCH = 478,
    SAMPLE = 479,
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
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 96 "src/glsl/glsl_parser.yy" /* yacc.c:1909  */

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

#line 324 "src/glsl/glsl_parser.h" /* yacc.c:1909  */
};
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

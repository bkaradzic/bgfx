/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         _mesa_glsl_parse
#define yylex           _mesa_glsl_lex
#define yyerror         _mesa_glsl_error
#define yydebug         _mesa_glsl_debug
#define yynerrs         _mesa_glsl_nerrs


/* Copy the first part of user declarations.  */
#line 1 "src/glsl/glsl_parser.yy" /* yacc.c:339  */

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

#line 150 "src/glsl/glsl_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "glsl_parser.h".  */
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
#line 96 "src/glsl/glsl_parser.yy" /* yacc.c:355  */

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

#line 460 "src/glsl/glsl_parser.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 488 "src/glsl/glsl_parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5407

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  257
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  108
/* YYNRULES -- Number of rules.  */
#define YYNRULES  380
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  532

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   487

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   241,     2,     2,     2,   245,   248,     2,
     233,   234,   243,   239,   238,   240,   237,   244,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   252,   254,
     246,   253,   247,   251,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   235,     2,   236,   249,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   255,   250,   256,   242,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   300,   300,   299,   311,   313,   320,   330,   331,   332,
     333,   334,   347,   349,   353,   354,   355,   359,   368,   376,
     387,   388,   392,   399,   406,   413,   420,   427,   434,   435,
     441,   445,   452,   458,   467,   471,   475,   476,   485,   486,
     490,   491,   495,   501,   513,   517,   523,   530,   540,   541,
     545,   546,   550,   556,   568,   579,   580,   586,   592,   602,
     603,   604,   605,   609,   610,   616,   622,   631,   632,   638,
     647,   648,   654,   663,   664,   670,   676,   682,   691,   692,
     698,   707,   708,   717,   718,   727,   728,   737,   738,   747,
     748,   757,   758,   767,   768,   777,   778,   787,   788,   789,
     790,   791,   792,   793,   794,   795,   796,   797,   801,   805,
     821,   825,   830,   834,   839,   846,   850,   851,   855,   860,
     868,   882,   892,   906,   911,   924,   928,   936,   948,   961,
     967,   973,   983,   988,   989,   999,  1009,  1019,  1033,  1040,
    1049,  1058,  1067,  1076,  1090,  1097,  1108,  1115,  1116,  1126,
    1127,  1131,  1317,  1415,  1441,  1447,  1456,  1462,  1468,  1478,
    1484,  1485,  1486,  1487,  1488,  1507,  1520,  1548,  1571,  1586,
    1606,  1620,  1626,  1634,  1640,  1646,  1652,  1658,  1664,  1670,
    1675,  1680,  1686,  1691,  1699,  1704,  1709,  1723,  1738,  1739,
    1747,  1753,  1759,  1768,  1769,  1770,  1771,  1772,  1773,  1774,
    1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,  1784,
    1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,
    1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,
    1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,
    1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,
    1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,
    1865,  1866,  1867,  1868,  1872,  1877,  1882,  1890,  1898,  1907,
    1912,  1920,  1939,  1944,  1952,  1958,  1967,  1968,  1972,  1979,
    1986,  1993,  1999,  2000,  2004,  2005,  2006,  2007,  2008,  2009,
    2013,  2020,  2019,  2033,  2034,  2038,  2044,  2053,  2063,  2075,
    2081,  2090,  2099,  2104,  2112,  2116,  2134,  2142,  2147,  2155,
    2160,  2168,  2176,  2184,  2192,  2200,  2208,  2216,  2223,  2230,
    2240,  2241,  2245,  2247,  2253,  2258,  2267,  2273,  2279,  2285,
    2291,  2300,  2301,  2302,  2303,  2307,  2321,  2325,  2336,  2433,
    2439,  2445,  2455,  2459,  2464,  2472,  2477,  2485,  2509,  2517,
    2578
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "CONST_TOK", "BOOL_TOK",
  "FLOAT_TOK", "INT_TOK", "UINT_TOK", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "BVEC2",
  "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "UVEC2", "UVEC3", "UVEC4",
  "VEC2", "VEC3", "VEC4", "CENTROID", "IN_TOK", "OUT_TOK", "INOUT_TOK",
  "UNIFORM", "VARYING", "NOPERSPECTIVE", "FLAT", "SMOOTH", "MAT2X2",
  "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3",
  "MAT4X4", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D", "ISAMPLERCUBE",
  "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "ISAMPLERCUBEARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "USAMPLERCUBEARRAY", "SAMPLER2DRECT",
  "ISAMPLER2DRECT", "USAMPLER2DRECT", "SAMPLER2DRECTSHADOW",
  "SAMPLERBUFFER", "ISAMPLERBUFFER", "USAMPLERBUFFER", "SAMPLER2DMS",
  "ISAMPLER2DMS", "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "IMAGE1D", "IMAGE2D",
  "IMAGE3D", "IMAGE2DRECT", "IMAGECUBE", "IMAGEBUFFER", "IMAGE1DARRAY",
  "IMAGE2DARRAY", "IMAGECUBEARRAY", "IMAGE2DMS", "IMAGE2DMSARRAY",
  "IIMAGE1D", "IIMAGE2D", "IIMAGE3D", "IIMAGE2DRECT", "IIMAGECUBE",
  "IIMAGEBUFFER", "IIMAGE1DARRAY", "IIMAGE2DARRAY", "IIMAGECUBEARRAY",
  "IIMAGE2DMS", "IIMAGE2DMSARRAY", "UIMAGE1D", "UIMAGE2D", "UIMAGE3D",
  "UIMAGE2DRECT", "UIMAGECUBE", "UIMAGEBUFFER", "UIMAGE1DARRAY",
  "UIMAGE2DARRAY", "UIMAGECUBEARRAY", "UIMAGE2DMS", "UIMAGE2DMSARRAY",
  "IMAGE1DSHADOW", "IMAGE2DSHADOW", "IMAGE1DARRAYSHADOW",
  "IMAGE2DARRAYSHADOW", "COHERENT", "VOLATILE", "RESTRICT", "READONLY",
  "WRITEONLY", "ATOMIC_UINT", "STRUCT", "VOID_TOK", "WHILE", "IDENTIFIER",
  "TYPE_IDENTIFIER", "NEW_IDENTIFIER", "FLOATCONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "BOOLCONSTANT", "FIELD_SELECTION", "LEFT_OP", "RIGHT_OP",
  "INC_OP", "DEC_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "XOR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "ADD_ASSIGN",
  "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "SUB_ASSIGN", "INVARIANT", "LOWP", "MEDIUMP", "HIGHP",
  "SUPERP", "PRECISION", "VERSION_TOK", "EXTENSION", "LINE", "COLON",
  "EOL", "INTERFACE", "OUTPUT", "PRAGMA_DEBUG_ON", "PRAGMA_DEBUG_OFF",
  "PRAGMA_OPTIMIZE_ON", "PRAGMA_OPTIMIZE_OFF", "PRAGMA_INVARIANT_ALL",
  "LAYOUT_TOK", "ASM", "CLASS", "UNION", "ENUM", "TYPEDEF", "TEMPLATE",
  "THIS", "PACKED_TOK", "GOTO", "INLINE_TOK", "NOINLINE", "PUBLIC_TOK",
  "STATIC", "EXTERN", "EXTERNAL", "LONG_TOK", "SHORT_TOK", "DOUBLE_TOK",
  "HALF", "FIXED_TOK", "UNSIGNED", "INPUT_TOK", "OUPTUT", "HVEC2", "HVEC3",
  "HVEC4", "DVEC2", "DVEC3", "DVEC4", "FVEC2", "FVEC3", "FVEC4",
  "SAMPLER3DRECT", "SIZEOF", "CAST", "NAMESPACE", "USING", "RESOURCE",
  "PATCH", "SAMPLE", "SUBROUTINE", "ERROR_TOK", "COMMON", "PARTITION",
  "ACTIVE", "FILTER", "ROW_MAJOR", "THEN", "'('", "')'", "'['", "']'",
  "'.'", "','", "'+'", "'-'", "'!'", "'~'", "'*'", "'/'", "'%'", "'<'",
  "'>'", "'&'", "'^'", "'|'", "'?'", "':'", "'='", "';'", "'{'", "'}'",
  "$accept", "translation_unit", "$@1", "version_statement",
  "pragma_statement", "extension_statement_list", "any_identifier",
  "extension_statement", "external_declaration_list",
  "variable_identifier", "primary_expression", "postfix_expression",
  "integer_expression", "function_call", "function_call_or_method",
  "function_call_generic", "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "method_call_generic",
  "method_call_header_no_parameters", "method_call_header_with_parameters",
  "method_call_header", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "function_prototype",
  "function_declarator", "function_header_with_parameters",
  "function_header", "parameter_declarator", "parameter_declaration",
  "parameter_qualifier", "parameter_direction_qualifier",
  "parameter_type_specifier", "init_declarator_list", "single_declaration",
  "fully_specified_type", "layout_qualifier", "layout_qualifier_id_list",
  "integer_constant", "layout_qualifier_id",
  "interface_block_layout_qualifier", "interpolation_qualifier",
  "type_qualifier", "auxiliary_storage_qualifier", "storage_qualifier",
  "array_specifier", "type_specifier", "type_specifier_nonarray",
  "basic_type_specifier_nonarray", "precision_qualifier",
  "struct_specifier", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "initializer",
  "initializer_list", "declaration_statement", "statement",
  "simple_statement", "compound_statement", "$@2",
  "statement_no_new_scope", "compound_statement_no_new_scope",
  "statement_list", "expression_statement", "selection_statement",
  "selection_rest_statement", "condition", "switch_statement",
  "switch_body", "case_label", "case_label_list", "case_statement",
  "case_statement_list", "iteration_statement", "for_init_statement",
  "conditionopt", "for_rest_statement", "jump_statement",
  "external_declaration", "function_definition", "interface_block",
  "basic_interface_block", "interface_qualifier", "instance_name_opt",
  "member_list", "member_declaration", "layout_defaults", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,    40,    41,    91,    93,    46,    44,    43,
      45,    33,   126,    42,    47,    37,    60,    62,    38,    94,
     124,    63,    58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF -393

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-393)))

#define YYTABLE_NINF -372

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -85,   -88,    33,  -393,   -94,  -393,  -133,  -393,  -393,  -393,
    -393,   -80,   -75,  4754,  -393,  -393,   -67,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,    12,    19,    36,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -115,  -393,  -393,   261,  -393,  -393,  -393,    41,
     -64,   -48,    24,    29,    37,   -51,  -393,  -393,  4754,  -393,
    -132,   -41,   -23,     1,  -147,  -393,    86,    35,  5064,  5269,
    5064,  5064,  -393,    -6,  -393,  5064,  -393,  -393,  -393,  -393,
    -393,    88,  -393,   -75,  4943,   -24,  -393,  -393,  -393,  -393,
    -393,  5064,  -393,  5064,  -393,  5269,  -393,  -393,  -393,  -393,
    -393,   -83,  -393,  -393,   517,  -393,  -393,    17,    17,  -393,
    -393,  -393,  -393,  5269,    17,    17,   -75,  -393,    10,    27,
    -204,    38,  -125,  -121,  -113,  -393,  -393,  -393,  -393,  -393,
    -393,  3639,    15,  -393,     2,    69,   -75,  1265,  -393,  4943,
      22,  -393,  -393,    13,  -148,  -393,  -393,    23,    25,  1999,
      45,    50,    31,  3176,    53,    54,  -393,  -393,  -393,  -393,
    -393,  4085,  4085,  4085,  -393,  -393,  -393,  -393,  -393,    34,
    -393,    56,  -393,  -101,  -393,  -393,  -393,    57,  -145,  4308,
      63,   181,  4085,    -3,   -96,    42,  -108,    66,    55,    60,
      52,   151,   152,  -126,  -393,  -393,  -140,  -393,    59,  5083,
      77,  -393,  -393,  -393,  -393,   771,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,   -75,  -393,  -393,  -187,  2953,
    -175,  -393,  -393,  -393,  -393,  -393,  -393,  -393,    75,  -393,
    3862,  4943,  -393,    -6,  -138,  -393,  -393,  -393,  1502,  -393,
      79,  -393,   -83,  -393,  -393,   176,  2492,  4085,  -393,  -393,
    -127,  4085,  3416,  -393,  -393,  -117,  -393,  1999,  -393,  -393,
    4085,    86,  -393,  -393,  4085,    80,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  4085,
    -393,  4085,  4085,  4085,  4085,  4085,  4085,  4085,  4085,  4085,
    4085,  4085,  4085,  4085,  4085,  4085,  4085,  4085,  4085,  4085,
    4085,  4085,  -393,  -393,  -393,    -6,  2953,  -159,  2953,  -393,
    -393,  2953,  -393,  -393,    81,   -75,    62,  4943,    15,   -75,
    -393,  -393,  -393,  -393,  -393,  -393,    83,  -393,  -393,  3416,
     -89,  -393,   -58,    82,   -75,    85,  -393,  1025,    90,    82,
    -393,    89,  -393,    87,   -40,  4531,  -393,  -393,  -393,  -393,
    -393,    -3,    -3,   -96,   -96,    42,    42,    42,    42,  -108,
    -108,    66,    55,    60,    52,   151,   152,  -173,  -393,    15,
    -393,  2953,  -393,  -161,  -393,  -393,  -112,   185,  -393,  -393,
    4085,  -393,    73,    94,  1999,    76,    95,  2252,  -393,  -393,
    -393,  -393,  -393,  4085,    96,  -393,  4085,  -393,  2730,  -393,
    -393,    -6,    93,   -39,  4085,  2252,   321,  -393,   -10,  -393,
    2953,  -393,  -393,  -393,  -393,  -393,  -393,  -393,    15,  -393,
      98,    82,  -393,  1999,  4085,    97,  -393,  -393,  1746,  1999,
      -8,  -393,  -393,  -393,  -139,  -393,  -393,  -393,  -393,  -393,
    1999,  -393
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,    12,     0,     1,     2,    14,    15,    16,
       5,     0,     0,     0,    13,     6,     0,   174,   173,   197,
     194,   195,   196,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   198,   199,   200,   171,   176,   177,   178,   175,
     158,   157,   156,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   222,   223,   225,   226,   228,   229,
     230,   231,   232,   234,   235,   236,   237,   239,   240,   241,
     242,   244,   245,   246,   248,   249,   250,   251,   253,   221,
     238,   247,   227,   233,   243,   252,   254,   255,   256,   257,
     258,   259,   224,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   179,   180,   181,   182,
     183,   293,     0,   193,   192,   159,   296,   295,   294,     0,
       0,     0,     0,     0,     0,     0,   172,   363,     3,   362,
       0,     0,   117,   125,     0,   133,   138,   163,   162,     0,
     160,   161,   144,   188,   190,   164,   191,    18,   361,   114,
     366,     0,   364,     0,     0,     0,   176,   177,   178,    20,
      21,   159,   143,   163,   165,     0,     7,     8,     9,    10,
      11,     0,    19,   111,     0,   365,   115,   125,   125,   129,
     130,   131,   118,     0,   125,   125,     0,   112,    14,    16,
     139,     0,   176,   177,   178,   167,   367,   166,   145,   168,
     169,     0,   189,   170,     0,     0,     0,     0,   299,     0,
       0,   155,   154,   151,     0,   147,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    25,    23,    24,    26,
      47,     0,     0,     0,    59,    60,    61,    62,   329,   321,
     325,    22,    28,    55,    30,    35,    36,     0,     0,    41,
       0,    63,     0,    67,    70,    73,    78,    81,    83,    85,
      87,    89,    91,    93,    95,   108,     0,   311,     0,   163,
     144,   314,   327,   313,   312,     0,   315,   316,   317,   318,
     319,   119,   126,   123,   124,   132,   127,   128,   134,     0,
     140,   120,   379,   380,   378,   184,    63,   110,     0,    45,
       0,     0,    17,   304,     0,   302,   298,   300,     0,   113,
       0,   146,     0,   357,   356,     0,     0,     0,   360,   358,
       0,     0,     0,    56,    57,     0,   320,     0,    32,    33,
       0,     0,    39,    38,     0,   193,    42,    44,    98,    99,
     101,   100,   103,   104,   105,   106,   107,   102,    97,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   330,   326,   328,   121,     0,   135,     0,   306,
     142,     0,   185,   186,     0,     0,     0,   375,   305,     0,
     301,   297,   149,   150,   152,   148,     0,   351,   350,   353,
       0,   359,     0,   334,     0,     0,    27,     0,     0,    34,
      31,     0,    37,     0,     0,    51,    43,    96,    64,    65,
      66,    68,    69,    71,    72,    76,    77,    74,    75,    79,
      80,    82,    84,    86,    88,    90,    92,     0,   109,   122,
     137,     0,   309,     0,   141,   187,     0,   372,   376,   303,
       0,   352,     0,     0,     0,     0,     0,     0,   322,    29,
      54,    49,    48,     0,   193,    52,     0,   136,     0,   307,
     377,   373,     0,     0,   354,     0,   333,   331,     0,   336,
       0,   324,   347,   323,    53,    94,   308,   310,   374,   368,
       0,   355,   349,     0,     0,     0,   337,   341,     0,   345,
       0,   335,   348,   332,     0,   340,   343,   342,   344,   338,
     346,   339
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -393,  -393,  -393,  -393,  -393,  -393,     0,  -393,  -393,  -119,
    -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -393,  -393,  -393,   -14,  -393,  -141,  -124,  -111,  -110,
     -49,   -35,   -33,   -32,   -34,   -12,  -393,  -196,  -239,  -393,
    -240,    61,     6,     7,  -393,  -393,  -393,  -393,   159,   -27,
    -393,  -393,  -393,  -393,  -168,   -11,  -393,  -393,    44,  -393,
    -393,   -77,  -393,  -393,  -203,   -13,  -393,  -393,    58,  -393,
     149,  -210,   -26,   -29,  -369,  -393,    46,  -238,  -392,  -393,
    -393,  -109,   233,    40,    48,  -393,  -393,   -31,  -393,  -393,
    -123,  -393,  -135,  -393,  -393,  -393,  -393,  -393,  -393,   248,
    -393,  -393,  -142,  -393,  -393,    -5,  -393,  -393
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    13,     3,   147,     6,   323,    14,   148,   261,
     262,   263,   428,   264,   265,   266,   267,   268,   269,   270,
     432,   433,   434,   435,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   369,
     286,   318,   287,   288,   151,   152,   153,   303,   202,   203,
     204,   304,   154,   155,   156,   183,   234,   414,   235,   236,
     158,   159,   160,   161,   222,   319,   163,   164,   165,   166,
     227,   228,   324,   325,   400,   463,   291,   292,   293,   294,
     347,   502,   503,   295,   296,   297,   497,   425,   298,   499,
     517,   518,   519,   520,   299,   419,   472,   473,   300,   167,
     168,   169,   170,   171,   492,   406,   407,   172
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     162,   335,   157,   340,    11,   198,   226,   310,   514,   515,
     514,   515,    16,   345,  -369,   216,   182,   327,  -370,   149,
     150,   198,     7,     8,     9,   317,  -371,   460,   389,   462,
     356,   221,   464,     5,   199,   200,   201,   211,    17,    18,
      12,   378,   379,     7,     8,     9,   348,   349,   221,   309,
     199,   200,   201,     4,     7,     8,     9,   394,   184,   226,
     320,   226,     7,     8,     9,   391,   396,    35,   212,   213,
     399,   214,    39,    40,    41,    42,   320,   488,   401,   486,
     215,   217,    10,   219,   220,   501,   331,     1,   223,   353,
     332,   206,   487,   354,   461,   489,    15,   420,   391,   391,
     409,   422,   423,   501,   184,   397,   215,   207,   173,   231,
     429,   391,   186,   531,   392,   436,   410,   426,   327,   507,
     408,   391,   193,   194,   317,   390,   409,   421,   187,   312,
     437,   521,   175,   313,   350,   162,   351,   157,   380,   381,
     174,   314,   490,   374,   375,   474,   218,   216,   232,   391,
     457,  -369,   458,   405,   149,   150,   210,   399,  -370,   399,
     226,   162,   399,   126,   127,   128,   129,   130,   136,   137,
     138,   302,   230,   225,   424,  -371,   475,   306,   307,   423,
     391,   290,   191,   289,   136,   137,   138,   376,   377,   394,
     305,   233,   459,   196,   482,   510,   485,   185,   483,   391,
     188,   181,   136,   137,   138,   189,   308,   316,   136,   137,
     138,   205,   215,   190,   162,   197,   162,   382,   383,   145,
     412,   413,   399,   208,     8,   209,   290,   224,   289,   221,
     493,   229,   431,   441,   442,  -116,   496,   343,   344,   405,
     371,   372,   373,   -20,   504,   322,   516,   505,   529,   399,
     320,   424,   443,   444,   511,   205,   205,   321,   370,   146,
     -21,   399,   205,   205,    17,    18,   330,   445,   446,   447,
     448,   311,   449,   450,   524,   523,   329,   333,   336,   334,
     526,   528,   290,   337,   289,   338,   341,   342,   508,   -46,
     346,   352,   528,    35,   176,   177,   357,   178,    39,    40,
      41,    42,   386,   384,   387,   395,   316,   388,   162,   385,
     -45,   402,   416,   193,   -40,   162,   470,   465,   467,   477,
     391,   481,   480,   290,   491,   289,   479,   494,   495,   290,
     -50,   498,   233,   513,   290,   451,   289,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   509,   500,   525,
     452,   430,   522,   453,   455,   454,   301,   438,   439,   440,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   415,   456,   328,   466,
     469,   404,   417,   195,   418,   530,   512,   427,   471,   126,
     127,   128,   129,   130,   162,   527,   192,     0,   179,     0,
     180,     0,   468,     0,     0,     0,   290,     0,     0,     0,
       0,     0,     0,     0,   290,     0,   289,     0,     0,     0,
       0,     0,     0,     0,   476,     0,     0,   181,   136,   137,
     138,     0,     0,     0,   368,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,     0,   289,   290,     0,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290,     0,   289,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     290,     0,   289,     0,     0,   290,   290,   289,   289,     0,
       0,     0,     0,     0,     0,     0,     0,   290,     0,   289,
      17,    18,    19,    20,    21,    22,   237,   238,   239,     0,
     240,   241,   242,   243,   244,     0,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     0,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,     0,     0,     0,     0,   126,   127,   128,   129,   130,
     131,   132,   133,   245,   179,   134,   180,   246,   247,   248,
     249,   250,     0,     0,   251,   252,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,   137,   138,     0,   139,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   145,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   146,     0,     0,     0,     0,     0,     0,     0,     0,
     253,     0,     0,     0,     0,     0,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   258,   259,   260,    17,    18,    19,    20,    21,    22,
     237,   238,   239,     0,   240,   241,   242,   243,   244,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     0,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   245,   179,   134,
     180,   246,   247,   248,   249,   250,     0,     0,   251,   252,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,     0,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,     0,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   258,   259,   393,    17,    18,
      19,    20,    21,    22,   237,   238,   239,     0,   240,   241,
     242,   243,   244,     0,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       0,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   245,   179,   134,   180,   246,   247,   248,   249,   250,
       0,     0,   251,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,   137,   138,     0,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
       0,     0,     0,     0,     0,     0,     0,     0,   253,     0,
       0,     0,     0,     0,   254,   255,   256,   257,    17,    18,
      19,    20,    21,    22,     0,     0,     0,     0,     0,   258,
     259,   478,     0,     0,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,   176,   177,
       0,   178,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   181,   136,   137,   138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   326,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,   176,   177,     0,   178,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,   132,   133,     0,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   181,   136,
     137,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      18,    19,    20,    21,    22,   237,   238,   239,   411,   240,
     241,   242,   243,   244,   514,   515,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,     0,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   245,   179,   134,   180,   246,   247,   248,   249,
     250,     0,     0,   251,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,   136,   137,   138,     0,   139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,     0,   254,   255,   256,   257,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   259,    17,    18,    19,    20,    21,    22,   237,   238,
     239,     0,   240,   241,   242,   243,   244,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   245,   179,   134,   180,   246,
     247,   248,   249,   250,     0,     0,   251,   252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,   137,   138,     0,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   145,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   146,     0,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,     0,     0,     0,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   258,   259,    17,    18,    19,    20,    21,
      22,   237,   238,   239,     0,   240,   241,   242,   243,   244,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   245,   179,
     134,   180,   246,   247,   248,   249,   250,     0,     0,   251,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
     137,   138,     0,   139,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
       0,     0,     0,     0,     0,   253,     0,     0,     0,     0,
       0,   254,   255,   256,   257,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,   258,   194,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,   132,   133,     0,   179,
     134,   180,   246,   247,   248,   249,   250,     0,     0,   251,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
     137,   138,     0,   139,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
       0,     0,     0,     0,     0,   253,     0,     0,     0,     0,
       0,   254,   255,   256,   257,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,   258,     0,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,   133,     0,   179,   134,   180,
     246,   247,   248,   249,   250,     0,     0,   251,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,     0,   253,     0,     0,     0,     0,     0,   254,
     255,   256,   257,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   398,   506,     0,     0,     0,
       0,     0,     0,     0,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,   133,     0,
     179,   134,   180,   246,   247,   248,   249,   250,     0,     0,
     251,   252,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    20,    21,    22,     0,   253,     0,     0,     0,
       0,     0,   254,   255,   256,   257,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,   398,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,   133,     0,   179,   134,   180,   246,   247,   248,   249,
     250,     0,     0,   251,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,     0,   254,   255,   256,   257,    17,
      18,    19,    20,    21,    22,     0,     0,     0,     0,     0,
     339,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   176,
     177,     0,   178,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
     132,   133,     0,   179,   134,   180,   246,   247,   248,   249,
     250,     0,     0,   251,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,   136,   137,   138,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,    19,    20,    21,    22,     0,   253,
       0,     0,     0,     0,     0,   254,   255,   256,   257,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,   133,     0,   179,   134,   180,   246,
     247,   248,   249,   250,     0,     0,   251,   252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,    20,    21,
      22,     0,   253,     0,     0,   315,     0,     0,   254,   255,
     256,   257,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,   133,     0,   179,
     134,   180,   246,   247,   248,   249,   250,     0,     0,   251,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    20,    21,    22,     0,   253,     0,     0,   403,     0,
       0,   254,   255,   256,   257,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
     133,     0,   179,   134,   180,   246,   247,   248,   249,   250,
       0,     0,   251,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,    21,    22,     0,   253,     0,
       0,     0,     0,     0,   254,   255,   256,   257,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,   355,     0,   179,   134,   180,   246,   247,
     248,   249,   250,     0,     0,   251,   252,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
       0,   253,     0,     0,     0,     0,     0,   254,   255,   256,
     257,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,   484,     0,   179,   134,
     180,   246,   247,   248,   249,   250,     0,     0,   251,   252,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,    19,
      20,    21,    22,     0,   253,     0,     0,     0,     0,     0,
     254,   255,   256,   257,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,   126,   127,   128,   129,   130,   131,   132,   133,
       0,     0,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,   137,   138,     0,   139,     0,     0,     0,     0,
       0,     0,     0,   140,   141,   142,   143,   144,   145,     0,
       0,     0,     0,     0,     0,     0,    17,    18,    19,    20,
      21,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   176,   177,   146,   178,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    17,    18,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,     0,
       0,   134,     0,     0,     0,     0,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,    35,   176,   177,     0,
     178,    39,    40,    41,    42,     0,     0,     0,     0,   181,
     136,   137,   138,     0,     0,    35,    36,    37,     0,    38,
      39,    40,    41,    42,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   126,   127,   128,   129,   130,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     181,   136,   137,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   145,   181,
     136,   137,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,    19,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,     0,     0,     0,     0,     0,   146,     0,     0,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,   133,     0,     0,   134
};

static const yytype_int16 yycheck[] =
{
      13,   239,    13,   243,     4,     4,   174,   210,    18,    19,
      18,    19,    12,   253,   139,   157,   135,   227,   139,    13,
      13,     4,   137,   138,   139,   221,   139,   396,   154,   398,
     269,   235,   401,     0,    33,    34,    35,   156,     3,     4,
     173,   149,   150,   137,   138,   139,   147,   148,   235,   253,
      33,    34,    35,   141,   137,   138,   139,   295,   135,   227,
     235,   229,   137,   138,   139,   238,   253,    32,    33,    34,
     309,    36,    37,    38,    39,    40,   235,   238,   253,   252,
     157,   158,   176,   160,   161,   477,   234,   172,   165,   234,
     238,   238,   461,   238,   253,   256,   176,   337,   238,   238,
     238,   341,   342,   495,   181,   308,   183,   254,   175,   192,
     350,   238,   176,   252,   254,   354,   254,   234,   328,   488,
     323,   238,   254,   255,   320,   251,   238,   254,   176,   254,
     369,   500,   132,   254,   235,   148,   237,   148,   246,   247,
     255,   254,   254,   239,   240,   234,   159,   289,   231,   238,
     390,   139,   391,   321,   148,   148,   156,   396,   139,   398,
     328,   174,   401,   128,   129,   130,   131,   132,   167,   168,
     169,   198,   185,   173,   342,   139,   234,   204,   205,   419,
     238,   194,   233,   194,   167,   168,   169,   145,   146,   427,
     203,   191,   395,   234,   234,   234,   435,   139,   238,   238,
     176,   166,   167,   168,   169,   176,   206,   221,   167,   168,
     169,   153,   289,   176,   227,   238,   229,   151,   152,   184,
     141,   142,   461,   137,   138,   139,   239,   139,   239,   235,
     470,   255,   351,   374,   375,   234,   474,   251,   252,   407,
     243,   244,   245,   233,   483,   176,   256,   486,   256,   488,
     235,   419,   376,   377,   494,   197,   198,   255,   272,   224,
     233,   500,   204,   205,     3,     4,   253,   378,   379,   380,
     381,   233,   382,   383,   514,   513,   254,   254,   233,   254,
     518,   519,   295,   233,   295,   254,   233,   233,   491,   233,
     256,   234,   530,    32,    33,    34,   233,    36,    37,    38,
      39,    40,   250,   248,   153,   305,   320,   155,   321,   249,
     233,   236,   136,   254,   234,   328,   233,   236,   256,   234,
     238,   234,   233,   336,   139,   336,   236,   254,   234,   342,
     234,   255,   332,    12,   347,   384,   347,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   254,   253,   252,
     385,   351,   254,   386,   388,   387,   197,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   332,   389,   229,   405,
     409,   320,   336,   150,   336,   520,   495,   347,   419,   128,
     129,   130,   131,   132,   407,   518,   148,    -1,   137,    -1,
     139,    -1,   407,    -1,    -1,    -1,   419,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   427,    -1,   427,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   424,    -1,    -1,   166,   167,   168,
     169,    -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   474,    -1,   474,   477,    -1,   477,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   495,    -1,   495,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     513,    -1,   513,    -1,    -1,   518,   519,   518,   519,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   530,    -1,   530,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,    -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,    -1,    -1,   147,   148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   166,   167,   168,   169,    -1,   171,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     233,    -1,    -1,    -1,    -1,    -1,   239,   240,   241,   242,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   254,   255,   256,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,    -1,    -1,   147,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,   167,   168,
     169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,
     239,   240,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   254,   255,   256,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
      -1,    -1,   147,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,   167,   168,   169,    -1,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,    -1,    -1,   239,   240,   241,   242,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,   254,
     255,   256,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,   128,   129,   130,   131,   132,   133,   134,
     135,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,   167,   168,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   256,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,    -1,    -1,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,   167,
     168,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   256,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
      -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,    -1,    -1,   147,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,   167,   168,   169,    -1,   171,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,    -1,    -1,   239,   240,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     254,   255,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    -1,    -1,    -1,    -1,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   166,   167,   168,   169,    -1,
     171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   224,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,   239,   240,
     241,   242,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   254,   255,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,    -1,    -1,   147,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,   167,
     168,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,
      -1,   239,   240,   241,   242,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,   254,   255,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,    -1,   137,
     138,   139,   140,   141,   142,   143,   144,    -1,    -1,   147,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,   167,
     168,   169,    -1,   171,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,
      -1,   239,   240,   241,   242,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   133,   134,   135,    -1,   137,   138,   139,
     140,   141,   142,   143,   144,    -1,    -1,   147,   148,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,   233,    -1,    -1,    -1,    -1,    -1,   239,
     240,   241,   242,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,   255,   256,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   133,   134,   135,    -1,
     137,   138,   139,   140,   141,   142,   143,   144,    -1,    -1,
     147,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,     6,     7,     8,    -1,   233,    -1,    -1,    -1,
      -1,    -1,   239,   240,   241,   242,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,   255,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,
     134,   135,    -1,   137,   138,   139,   140,   141,   142,   143,
     144,    -1,    -1,   147,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,    -1,    -1,   239,   240,   241,   242,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
     254,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
      -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,   133,
     134,   135,    -1,   137,   138,   139,   140,   141,   142,   143,
     144,    -1,    -1,   147,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,   167,   168,   169,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     224,    -1,    -1,    -1,     5,     6,     7,     8,    -1,   233,
      -1,    -1,    -1,    -1,    -1,   239,   240,   241,   242,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   133,   134,   135,    -1,   137,   138,   139,   140,
     141,   142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,
       8,    -1,   233,    -1,    -1,   236,    -1,    -1,   239,   240,
     241,   242,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   133,   134,   135,    -1,   137,
     138,   139,   140,   141,   142,   143,   144,    -1,    -1,   147,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,     7,     8,    -1,   233,    -1,    -1,   236,    -1,
      -1,   239,   240,   241,   242,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,   134,
     135,    -1,   137,   138,   139,   140,   141,   142,   143,   144,
      -1,    -1,   147,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,     8,    -1,   233,    -1,
      -1,    -1,    -1,    -1,   239,   240,   241,   242,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   133,   134,   135,    -1,   137,   138,   139,   140,   141,
     142,   143,   144,    -1,    -1,   147,   148,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,     8,
      -1,   233,    -1,    -1,    -1,    -1,    -1,   239,   240,   241,
     242,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   133,   134,   135,    -1,   137,   138,
     139,   140,   141,   142,   143,   144,    -1,    -1,   147,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   233,    -1,    -1,    -1,    -1,    -1,
     239,   240,   241,   242,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,    -1,    -1,
      -1,    -1,   128,   129,   130,   131,   132,   133,   134,   135,
      -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,   167,   168,   169,    -1,   171,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   179,   180,   181,   182,   183,   184,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,   224,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     3,     4,    -1,
      -1,   128,   129,   130,   131,   132,   133,   134,   135,    -1,
      -1,   138,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,   166,
     167,   168,   169,    -1,    -1,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    -1,    -1,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,   129,   130,   131,   132,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,   129,   130,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,   167,   168,   169,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   166,
     167,   168,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   133,   134,   135,    -1,    -1,   138
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   172,   258,   260,   141,     0,   262,   137,   138,   139,
     176,   263,   173,   259,   264,   176,   263,     3,     4,     5,
       6,     7,     8,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   128,   129,   130,   131,
     132,   133,   134,   135,   138,   166,   167,   168,   169,   171,
     179,   180,   181,   182,   183,   184,   224,   261,   265,   299,
     300,   301,   302,   303,   309,   310,   311,   312,   317,   318,
     319,   320,   322,   323,   324,   325,   326,   356,   357,   358,
     359,   360,   364,   175,   255,   263,    33,    34,    36,   137,
     139,   166,   266,   312,   318,   325,   176,   176,   176,   176,
     176,   233,   356,   254,   255,   339,   234,   238,     4,    33,
      34,    35,   305,   306,   307,   325,   238,   254,   137,   139,
     263,   266,    33,    34,    36,   318,   359,   318,   322,   318,
     318,   235,   321,   318,   139,   263,   311,   327,   328,   255,
     322,   192,   231,   263,   313,   315,   316,     9,    10,    11,
      13,    14,    15,    16,    17,   136,   140,   141,   142,   143,
     144,   147,   148,   233,   239,   240,   241,   242,   254,   255,
     256,   266,   267,   268,   270,   271,   272,   273,   274,   275,
     276,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   297,   299,   300,   312,
     322,   333,   334,   335,   336,   340,   341,   342,   345,   351,
     355,   305,   306,   304,   308,   322,   306,   306,   263,   253,
     321,   233,   254,   254,   254,   236,   281,   294,   298,   322,
     235,   255,   176,   263,   329,   330,   256,   328,   327,   254,
     253,   234,   238,   254,   254,   334,   233,   233,   254,   254,
     297,   233,   233,   281,   281,   297,   256,   337,   147,   148,
     235,   237,   234,   234,   238,   135,   295,   233,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   253,   296,
     281,   243,   244,   245,   239,   240,   145,   146,   149,   150,
     246,   247,   151,   152,   248,   249,   250,   153,   155,   154,
     251,   238,   254,   256,   334,   263,   253,   321,   255,   295,
     331,   253,   236,   236,   298,   311,   362,   363,   321,   238,
     254,   256,   141,   142,   314,   315,   136,   333,   341,   352,
     297,   254,   297,   297,   311,   344,   234,   340,   269,   297,
     263,   266,   277,   278,   279,   280,   295,   295,   281,   281,
     281,   283,   283,   284,   284,   285,   285,   285,   285,   286,
     286,   287,   288,   289,   290,   291,   292,   297,   295,   321,
     331,   253,   331,   332,   331,   236,   329,   256,   362,   330,
     233,   344,   353,   354,   234,   234,   263,   234,   256,   236,
     233,   234,   234,   238,   135,   295,   252,   331,   238,   256,
     254,   139,   361,   297,   254,   234,   334,   343,   255,   346,
     253,   335,   338,   339,   295,   295,   256,   331,   321,   254,
     234,   297,   338,    12,    18,    19,   256,   347,   348,   349,
     350,   331,   254,   334,   297,   252,   334,   347,   334,   256,
     349,   252
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   257,   259,   258,   260,   260,   260,   261,   261,   261,
     261,   261,   262,   262,   263,   263,   263,   264,   265,   265,
     266,   266,   267,   267,   267,   267,   267,   267,   268,   268,
     268,   268,   268,   268,   269,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   276,   276,   276,   277,   277,
     278,   278,   279,   279,   280,   281,   281,   281,   281,   282,
     282,   282,   282,   283,   283,   283,   283,   284,   284,   284,
     285,   285,   285,   286,   286,   286,   286,   286,   287,   287,
     287,   288,   288,   289,   289,   290,   290,   291,   291,   292,
     292,   293,   293,   294,   294,   295,   295,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   297,   297,
     298,   299,   299,   299,   299,   300,   301,   301,   302,   302,
     303,   304,   304,   305,   305,   306,   306,   306,   306,   307,
     307,   307,   308,   309,   309,   309,   309,   309,   310,   310,
     310,   310,   310,   310,   311,   311,   312,   313,   313,   314,
     314,   315,   315,   315,   316,   316,   317,   317,   317,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   319,   319,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   321,   321,   321,   321,   322,   322,
     323,   323,   323,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   325,   325,   325,   326,   326,   327,
     327,   328,   329,   329,   330,   330,   331,   331,   331,   332,
     332,   333,   334,   334,   335,   335,   335,   335,   335,   335,
     336,   337,   336,   338,   338,   339,   339,   340,   340,   341,
     341,   342,   343,   343,   344,   344,   345,   346,   346,   347,
     347,   348,   348,   349,   349,   350,   350,   351,   351,   351,
     352,   352,   353,   353,   354,   354,   355,   355,   355,   355,
     355,   356,   356,   356,   356,   357,   358,   358,   359,   360,
     360,   360,   361,   361,   361,   362,   362,   363,   364,   364,
     364
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     4,     2,     2,     2,
       2,     2,     0,     2,     1,     1,     1,     5,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     4,
       1,     3,     2,     2,     1,     1,     1,     3,     2,     2,
       2,     1,     2,     3,     2,     1,     1,     1,     2,     2,
       2,     1,     2,     3,     2,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     2,     4,     1,     2,     1,     1,     2,     3,
       3,     2,     3,     2,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     3,     4,     6,     5,     1,     2,
       3,     5,     4,     2,     1,     2,     4,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     1,
       2,     3,     1,     3,     1,     2,     1,     3,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     4,     1,     1,     2,     3,     1,     2,     1,
       2,     5,     3,     1,     1,     4,     5,     2,     3,     3,
       2,     1,     2,     2,     2,     1,     2,     5,     7,     6,
       1,     1,     1,     0,     2,     3,     2,     2,     2,     3,
       2,     1,     1,     1,     1,     2,     1,     2,     7,     1,
       1,     1,     0,     1,     2,     1,     2,     3,     3,     3,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, state, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, state); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (state);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, state);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct _mesa_glsl_parse_state *state)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, state); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct _mesa_glsl_parse_state *state)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (state);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct _mesa_glsl_parse_state *state)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 85 "src/glsl/glsl_parser.yy" /* yacc.c:1429  */
{
   yylloc.first_line = 1;
   yylloc.first_column = 1;
   yylloc.last_line = 1;
   yylloc.last_column = 1;
   yylloc.source = 0;
}

#line 2986 "src/glsl/glsl_parser.cpp" /* yacc.c:1429  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, state);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 300 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      _mesa_glsl_initialize_types(state);
   }
#line 3177 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 304 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      delete state->symbols;
      state->symbols = new(ralloc_parent(state)) glsl_symbol_table;
      _mesa_glsl_initialize_types(state);
   }
#line 3187 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 314 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->process_version_directive(&(yylsp[-1]), (yyvsp[-1].n), NULL);
      if (state->error) {
         YYERROR;
      }
   }
#line 3198 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 321 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->process_version_directive(&(yylsp[-2]), (yyvsp[-2].n), (yyvsp[-1].identifier));
      if (state->error) {
         YYERROR;
      }
   }
#line 3209 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 335 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if (!state->is_version(120, 100)) {
         _mesa_glsl_warning(& (yylsp[-1]), state,
                            "pragma `invariant(all)' not supported in %s "
                            "(GLSL ES 1.00 or GLSL 1.20 required)",
                            state->get_version_string());
      } else {
         state->all_invariant = true;
      }
   }
#line 3224 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 360 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if (!_mesa_glsl_process_extension((yyvsp[-3].identifier), & (yylsp[-3]), (yyvsp[-1].identifier), & (yylsp[-1]), state)) {
         YYERROR;
      }
   }
#line 3234 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 369 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if ((yyvsp[0].node) != NULL)
         state->translation_unit.push_tail(& (yyvsp[0].node)->link);
   }
#line 3246 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 377 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if ((yyvsp[0].node) != NULL)
         state->translation_unit.push_tail(& (yyvsp[0].node)->link);
   }
#line 3258 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 393 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.identifier = (yyvsp[0].identifier);
   }
#line 3269 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 400 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.int_constant = (yyvsp[0].n);
   }
#line 3280 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 407 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.uint_constant = (yyvsp[0].n);
   }
#line 3291 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 414 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.float_constant = (yyvsp[0].real);
   }
#line 3302 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 421 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.bool_constant = (yyvsp[0].n);
   }
#line 3313 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 428 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
   }
#line 3321 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 436 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_array_index, (yyvsp[-3].expression), (yyvsp[-1].expression), NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3331 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 442 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[0].expression);
   }
#line 3339 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 446 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[-2].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->primary_expression.identifier = (yyvsp[0].identifier);
   }
#line 3350 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 453 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_post_inc, (yyvsp[-1].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3360 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 459 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_post_dec, (yyvsp[-1].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3370 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 477 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[-2].expression), (yyvsp[0].expression), NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3380 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 496 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 3390 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 502 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 3400 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 518 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_function_expression((yyvsp[0].type_specifier));
      (yyval.expression)->set_location(yylloc);
      }
#line 3410 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 524 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression((yyvsp[0].identifier));
      (yyval.expression) = new(ctx) ast_function_expression(callee);
      (yyval.expression)->set_location(yylloc);
      }
#line 3421 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 531 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression((yyvsp[0].identifier));
      (yyval.expression) = new(ctx) ast_function_expression(callee);
      (yyval.expression)->set_location(yylloc);
      }
#line 3432 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 551 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 3442 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 557 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 3452 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 569 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_expression *callee = new(ctx) ast_expression((yyvsp[-1].identifier));
      (yyval.expression) = new(ctx) ast_function_expression(callee);
      (yyval.expression)->set_location(yylloc);
   }
#line 3463 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 581 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_pre_inc, (yyvsp[0].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3473 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 587 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_pre_dec, (yyvsp[0].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3483 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 593 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression((yyvsp[-1].n), (yyvsp[0].expression), NULL, NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3493 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 602 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_plus; }
#line 3499 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 603 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_neg; }
#line 3505 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 604 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_logic_not; }
#line 3511 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 605 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_bit_not; }
#line 3517 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 611 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_mul, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3527 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 617 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_div, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3537 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 623 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_mod, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3547 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 633 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_add, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3557 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 639 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_sub, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3567 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 649 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_lshift, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3577 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 655 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_rshift, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3587 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 665 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_less, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3597 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 671 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_greater, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3607 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 677 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_lequal, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3617 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 683 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_gequal, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3627 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 693 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_equal, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3637 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 699 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_nequal, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3647 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 709 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_and, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3657 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 719 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_xor, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3667 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 729 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_or, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3677 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 739 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_and, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3687 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 749 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_xor, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3697 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 759 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_or, (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3707 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 769 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression(ast_conditional, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression));
      (yyval.expression)->set_location(yylloc);
   }
#line 3717 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 779 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_expression((yyvsp[-1].n), (yyvsp[-2].expression), (yyvsp[0].expression), NULL);
      (yyval.expression)->set_location(yylloc);
   }
#line 3727 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 787 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_assign; }
#line 3733 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 788 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_mul_assign; }
#line 3739 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 789 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_div_assign; }
#line 3745 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 790 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_mod_assign; }
#line 3751 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 791 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_add_assign; }
#line 3757 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 792 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_sub_assign; }
#line 3763 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 793 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_ls_assign; }
#line 3769 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 794 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_rs_assign; }
#line 3775 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 795 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_and_assign; }
#line 3781 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 796 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_xor_assign; }
#line 3787 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 797 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = ast_or_assign; }
#line 3793 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 802 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[0].expression);
   }
#line 3801 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 806 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      if ((yyvsp[-2].expression)->oper != ast_sequence) {
         (yyval.expression) = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
         (yyval.expression)->set_location(yylloc);
         (yyval.expression)->expressions.push_tail(& (yyvsp[-2].expression)->link);
      } else {
         (yyval.expression) = (yyvsp[-2].expression);
      }

      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 3818 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 826 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->symbols->pop_scope();
      (yyval.node) = (yyvsp[-1].function);
   }
#line 3827 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 831 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = (yyvsp[-1].declarator_list);
   }
#line 3835 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 835 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyvsp[-1].type_specifier)->default_precision = (yyvsp[-2].n);
      (yyval.node) = (yyvsp[-1].type_specifier);
   }
#line 3844 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 840 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = (yyvsp[0].node);
   }
#line 3852 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 856 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.function) = (yyvsp[-1].function);
      (yyval.function)->parameters.push_tail(& (yyvsp[0].parameter_declarator)->link);
   }
#line 3861 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 861 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.function) = (yyvsp[-2].function);
      (yyval.function)->parameters.push_tail(& (yyvsp[0].parameter_declarator)->link);
   }
#line 3870 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 869 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.function) = new(ctx) ast_function();
      (yyval.function)->set_location(yylloc);
      (yyval.function)->return_type = (yyvsp[-2].fully_specified_type);
      (yyval.function)->identifier = (yyvsp[-1].identifier);

      state->symbols->add_function(new(state) ir_function((yyvsp[-1].identifier)));
      state->symbols->push_scope();
   }
#line 3885 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 883 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
      (yyval.parameter_declarator)->set_location(yylloc);
      (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
      (yyval.parameter_declarator)->type->set_location(yylloc);
      (yyval.parameter_declarator)->type->specifier = (yyvsp[-1].type_specifier);
      (yyval.parameter_declarator)->identifier = (yyvsp[0].identifier);
   }
#line 3899 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 893 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
      (yyval.parameter_declarator)->set_location(yylloc);
      (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
      (yyval.parameter_declarator)->type->set_location(yylloc);
      (yyval.parameter_declarator)->type->specifier = (yyvsp[-2].type_specifier);
      (yyval.parameter_declarator)->identifier = (yyvsp[-1].identifier);
      (yyval.parameter_declarator)->array_specifier = (yyvsp[0].array_specifier);
   }
#line 3914 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 907 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.parameter_declarator) = (yyvsp[0].parameter_declarator);
      (yyval.parameter_declarator)->type->qualifier = (yyvsp[-1].type_qualifier);
   }
#line 3923 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 912 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
      (yyval.parameter_declarator)->set_location(yylloc);
      (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
      (yyval.parameter_declarator)->type->qualifier = (yyvsp[-1].type_qualifier);
      (yyval.parameter_declarator)->type->specifier = (yyvsp[0].type_specifier);
   }
#line 3936 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 924 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
   }
#line 3945 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 929 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].type_qualifier).flags.q.constant)
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate const qualifier");

      (yyval.type_qualifier) = (yyvsp[0].type_qualifier);
      (yyval.type_qualifier).flags.q.constant = 1;
   }
#line 3957 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 937 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if (((yyvsp[-1].type_qualifier).flags.q.in || (yyvsp[-1].type_qualifier).flags.q.out) && ((yyvsp[0].type_qualifier).flags.q.in || (yyvsp[0].type_qualifier).flags.q.out))
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate in/out/inout qualifier");

      if (!state->ARB_shading_language_420pack_enable && (yyvsp[0].type_qualifier).flags.q.constant)
         _mesa_glsl_error(&(yylsp[-1]), state, "const must be specified before "
                          "in/out/inout");

      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
      (yyval.type_qualifier).merge_qualifier(&(yylsp[-1]), state, (yyvsp[0].type_qualifier));
   }
#line 3973 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 949 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].type_qualifier).precision != ast_precision_none)
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate precision qualifier");

      if (!state->ARB_shading_language_420pack_enable && (yyvsp[0].type_qualifier).flags.i != 0)
         _mesa_glsl_error(&(yylsp[-1]), state, "precision qualifiers must come last");

      (yyval.type_qualifier) = (yyvsp[0].type_qualifier);
      (yyval.type_qualifier).precision = (yyvsp[-1].n);
   }
#line 3988 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 962 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.in = 1;
   }
#line 3998 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 968 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.out = 1;
   }
#line 4008 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 974 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.in = 1;
      (yyval.type_qualifier).flags.q.out = 1;
   }
#line 4019 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 990 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[0].identifier), NULL, NULL);
      decl->set_location(yylloc);

      (yyval.declarator_list) = (yyvsp[-2].declarator_list);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[0].identifier), ir_var_auto, glsl_precision_undefined));
   }
#line 4033 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1000 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-1].identifier), (yyvsp[0].array_specifier), NULL);
      decl->set_location(yylloc);

      (yyval.declarator_list) = (yyvsp[-3].declarator_list);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[-1].identifier), ir_var_auto, glsl_precision_undefined));
   }
#line 4047 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1010 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-3].identifier), (yyvsp[-2].array_specifier), (yyvsp[0].expression));
      decl->set_location(yylloc);

      (yyval.declarator_list) = (yyvsp[-5].declarator_list);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[-3].identifier), ir_var_auto, glsl_precision_undefined));
   }
#line 4061 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1020 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-2].identifier), NULL, (yyvsp[0].expression));
      decl->set_location(yylloc);

      (yyval.declarator_list) = (yyvsp[-4].declarator_list);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[-2].identifier), ir_var_auto, glsl_precision_undefined));
   }
#line 4075 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1034 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      /* Empty declaration list is valid. */
      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[0].fully_specified_type));
      (yyval.declarator_list)->set_location(yylloc);
   }
#line 4086 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1041 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[0].identifier), NULL, NULL);

      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[-1].fully_specified_type));
      (yyval.declarator_list)->set_location(yylloc);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
   }
#line 4099 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1050 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-1].identifier), (yyvsp[0].array_specifier), NULL);

      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[-2].fully_specified_type));
      (yyval.declarator_list)->set_location(yylloc);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
   }
#line 4112 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1059 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-3].identifier), (yyvsp[-2].array_specifier), (yyvsp[0].expression));

      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[-4].fully_specified_type));
      (yyval.declarator_list)->set_location(yylloc);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
   }
#line 4125 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1068 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-2].identifier), NULL, (yyvsp[0].expression));

      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[-3].fully_specified_type));
      (yyval.declarator_list)->set_location(yylloc);
      (yyval.declarator_list)->declarations.push_tail(&decl->link);
   }
#line 4138 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1077 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[0].identifier), NULL, NULL);

      (yyval.declarator_list) = new(ctx) ast_declarator_list(NULL);
      (yyval.declarator_list)->set_location(yylloc);
      (yyval.declarator_list)->invariant = true;

      (yyval.declarator_list)->declarations.push_tail(&decl->link);
   }
#line 4153 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1091 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
      (yyval.fully_specified_type)->set_location(yylloc);
      (yyval.fully_specified_type)->specifier = (yyvsp[0].type_specifier);
   }
#line 4164 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1098 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
      (yyval.fully_specified_type)->set_location(yylloc);
      (yyval.fully_specified_type)->qualifier = (yyvsp[-1].type_qualifier);
      (yyval.fully_specified_type)->specifier = (yyvsp[0].type_specifier);
   }
#line 4176 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1109 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
   }
#line 4184 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1117 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.type_qualifier) = (yyvsp[-2].type_qualifier);
      if (!(yyval.type_qualifier).merge_qualifier(& (yylsp[0]), state, (yyvsp[0].type_qualifier))) {
         YYERROR;
      }
   }
#line 4195 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1126 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 4201 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1127 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 4207 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1132 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;

      /* Layout qualifiers for ARB_fragment_coord_conventions. */
      if (!(yyval.type_qualifier).flags.i && (state->ARB_fragment_coord_conventions_enable ||
                          state->is_version(150, 0))) {
         if (match_layout_qualifier((yyvsp[0].identifier), "origin_upper_left", state) == 0) {
            (yyval.type_qualifier).flags.q.origin_upper_left = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "pixel_center_integer",
                                           state) == 0) {
            (yyval.type_qualifier).flags.q.pixel_center_integer = 1;
         }

         if ((yyval.type_qualifier).flags.i && state->ARB_fragment_coord_conventions_warn) {
            _mesa_glsl_warning(& (yylsp[0]), state,
                               "GL_ARB_fragment_coord_conventions layout "
                               "identifier `%s' used", (yyvsp[0].identifier));
         }
      }

      /* Layout qualifiers for AMD/ARB_conservative_depth. */
      if (!(yyval.type_qualifier).flags.i &&
          (state->AMD_conservative_depth_enable ||
           state->ARB_conservative_depth_enable)) {
         if (match_layout_qualifier((yyvsp[0].identifier), "depth_any", state) == 0) {
            (yyval.type_qualifier).flags.q.depth_any = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "depth_greater", state) == 0) {
            (yyval.type_qualifier).flags.q.depth_greater = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "depth_less", state) == 0) {
            (yyval.type_qualifier).flags.q.depth_less = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "depth_unchanged",
                                           state) == 0) {
            (yyval.type_qualifier).flags.q.depth_unchanged = 1;
         }

         if ((yyval.type_qualifier).flags.i && state->AMD_conservative_depth_warn) {
            _mesa_glsl_warning(& (yylsp[0]), state,
                               "GL_AMD_conservative_depth "
                               "layout qualifier `%s' is used", (yyvsp[0].identifier));
         }
         if ((yyval.type_qualifier).flags.i && state->ARB_conservative_depth_warn) {
            _mesa_glsl_warning(& (yylsp[0]), state,
                               "GL_ARB_conservative_depth "
                               "layout qualifier `%s' is used", (yyvsp[0].identifier));
         }
      }

      /* See also interface_block_layout_qualifier. */
      if (!(yyval.type_qualifier).flags.i && state->has_uniform_buffer_objects()) {
         if (match_layout_qualifier((yyvsp[0].identifier), "std140", state) == 0) {
            (yyval.type_qualifier).flags.q.std140 = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "shared", state) == 0) {
            (yyval.type_qualifier).flags.q.shared = 1;
         } else if (match_layout_qualifier((yyvsp[0].identifier), "column_major", state) == 0) {
            (yyval.type_qualifier).flags.q.column_major = 1;
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
         } else if (match_layout_qualifier((yyvsp[0].identifier), "row_major", state) == 0) {
            (yyval.type_qualifier).flags.q.row_major = 1;
         /* "packed" is a reserved word in GLSL, and its token is
          * parsed below in the interface_block_layout_qualifier rule.
          * However, we must take care of alternate capitalizations of
          * "packed", because layout qualifiers are case-insensitive
          * in desktop GLSL.
          */
         } else if (match_layout_qualifier((yyvsp[0].identifier), "packed", state) == 0) {
           (yyval.type_qualifier).flags.q.packed = 1;
         }

         if ((yyval.type_qualifier).flags.i && state->ARB_uniform_buffer_object_warn) {
            _mesa_glsl_warning(& (yylsp[0]), state,
                               "#version 140 / GL_ARB_uniform_buffer_object "
                               "layout qualifier `%s' is used", (yyvsp[0].identifier));
         }
      }

      /* Layout qualifiers for GLSL 1.50 geometry shaders. */
      if (!(yyval.type_qualifier).flags.i) {
         struct {
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
            if (match_layout_qualifier((yyvsp[0].identifier), map[i].s, state) == 0) {
               (yyval.type_qualifier).flags.q.prim_type = 1;
               (yyval.type_qualifier).prim_type = map[i].e;
               break;
            }
         }

         if ((yyval.type_qualifier).flags.i && !state->is_version(150, 0)) {
            _mesa_glsl_error(& (yylsp[0]), state, "#version 150 layout "
                             "qualifier `%s' used", (yyvsp[0].identifier));
         }
      }

      /* Layout qualifiers for ARB_shader_image_load_store. */
      if (state->ARB_shader_image_load_store_enable ||
          state->is_version(420, 0)) {
         if (!(yyval.type_qualifier).flags.i) {
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
               if (match_layout_qualifier((yyvsp[0].identifier), map[i].name, state) == 0) {
                  (yyval.type_qualifier).flags.q.explicit_image_format = 1;
                  (yyval.type_qualifier).image_format = map[i].format;
                  (yyval.type_qualifier).image_base_type = map[i].base_type;
                  break;
               }
            }
         }

         if (!(yyval.type_qualifier).flags.i &&
             match_layout_qualifier((yyvsp[0].identifier), "early_fragment_tests", state) == 0) {
            (yyval.type_qualifier).flags.q.early_fragment_tests = 1;
         }
      }

      if (!(yyval.type_qualifier).flags.i) {
         _mesa_glsl_error(& (yylsp[0]), state, "unrecognized layout identifier "
                          "`%s'", (yyvsp[0].identifier));
         YYERROR;
      }
   }
#line 4397 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1318 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;

      if (match_layout_qualifier("location", (yyvsp[-2].identifier), state) == 0) {
         (yyval.type_qualifier).flags.q.explicit_location = 1;

         if ((yyvsp[0].n) >= 0) {
            (yyval.type_qualifier).location = (yyvsp[0].n);
         } else {
             _mesa_glsl_error(& (yylsp[0]), state, "invalid location %d specified", (yyvsp[0].n));
             YYERROR;
         }
      }

      if (match_layout_qualifier("index", (yyvsp[-2].identifier), state) == 0) {
         (yyval.type_qualifier).flags.q.explicit_index = 1;

         if ((yyvsp[0].n) >= 0) {
            (yyval.type_qualifier).index = (yyvsp[0].n);
         } else {
            _mesa_glsl_error(& (yylsp[0]), state, "invalid index %d specified", (yyvsp[0].n));
            YYERROR;
         }
      }

      if ((state->ARB_shading_language_420pack_enable ||
           state->ARB_shader_atomic_counters_enable) &&
          match_layout_qualifier("binding", (yyvsp[-2].identifier), state) == 0) {
         (yyval.type_qualifier).flags.q.explicit_binding = 1;
         (yyval.type_qualifier).binding = (yyvsp[0].n);
      }

      if (state->ARB_shader_atomic_counters_enable &&
          match_layout_qualifier("offset", (yyvsp[-2].identifier), state) == 0) {
         (yyval.type_qualifier).flags.q.explicit_offset = 1;
         (yyval.type_qualifier).offset = (yyvsp[0].n);
      }

      if (match_layout_qualifier("max_vertices", (yyvsp[-2].identifier), state) == 0) {
         (yyval.type_qualifier).flags.q.max_vertices = 1;

         if ((yyvsp[0].n) < 0) {
            _mesa_glsl_error(& (yylsp[0]), state,
                             "invalid max_vertices %d specified", (yyvsp[0].n));
            YYERROR;
         } else {
            (yyval.type_qualifier).max_vertices = (yyvsp[0].n);
            if (!state->is_version(150, 0)) {
               _mesa_glsl_error(& (yylsp[0]), state,
                                "#version 150 max_vertices qualifier "
                                "specified", (yyvsp[0].n));
            }
         }
      }

      static const char *local_size_qualifiers[3] = {
         "local_size_x",
         "local_size_y",
         "local_size_z",
      };
      for (int i = 0; i < 3; i++) {
         if (match_layout_qualifier(local_size_qualifiers[i], (yyvsp[-2].identifier),
                                    state) == 0) {
            if ((yyvsp[0].n) <= 0) {
               _mesa_glsl_error(& (yylsp[0]), state,
                                "invalid %s of %d specified",
                                local_size_qualifiers[i], (yyvsp[0].n));
               YYERROR;
            } else if (!state->is_version(430, 0) &&
                       !state->ARB_compute_shader_enable) {
               _mesa_glsl_error(& (yylsp[0]), state,
                                "%s qualifier requires GLSL 4.30 or "
                                "ARB_compute_shader",
                                local_size_qualifiers[i]);
               YYERROR;
            } else {
               (yyval.type_qualifier).flags.q.local_size |= (1 << i);
               (yyval.type_qualifier).local_size[i] = (yyvsp[0].n);
            }
            break;
         }
      }

      /* If the identifier didn't match any known layout identifiers,
       * emit an error.
       */
      if (!(yyval.type_qualifier).flags.i) {
         _mesa_glsl_error(& (yylsp[-2]), state, "unrecognized layout identifier "
                          "`%s'", (yyvsp[-2].identifier));
         YYERROR;
      } else if (state->ARB_explicit_attrib_location_warn) {
         _mesa_glsl_warning(& (yylsp[-2]), state,
                            "GL_ARB_explicit_attrib_location layout "
                            "identifier `%s' used", (yyvsp[-2].identifier));
      }
   }
#line 4499 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1416 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.type_qualifier) = (yyvsp[0].type_qualifier);
      /* Layout qualifiers for ARB_uniform_buffer_object. */
      if ((yyval.type_qualifier).flags.q.uniform && !state->has_uniform_buffer_objects()) {
         _mesa_glsl_error(& (yylsp[0]), state,
                          "#version 140 / GL_ARB_uniform_buffer_object "
                          "layout qualifier `%s' is used", (yyvsp[0].type_qualifier));
      } else if ((yyval.type_qualifier).flags.q.uniform && state->ARB_uniform_buffer_object_warn) {
         _mesa_glsl_warning(& (yylsp[0]), state,
                            "#version 140 / GL_ARB_uniform_buffer_object "
                            "layout qualifier `%s' is used", (yyvsp[0].type_qualifier));
      }
   }
#line 4517 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1442 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.row_major = 1;
   }
#line 4527 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1448 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.packed = 1;
   }
#line 4537 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1457 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.smooth = 1;
   }
#line 4547 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1463 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.flat = 1;
   }
#line 4557 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1469 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.noperspective = 1;
   }
#line 4567 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1479 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.invariant = 1;
   }
#line 4577 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1489 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(&(yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).precision = (yyvsp[0].n);
   }
#line 4587 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1508 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].type_qualifier).flags.q.invariant)
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate \"invariant\" qualifier");

      if ((yyvsp[0].type_qualifier).has_layout()) {
         _mesa_glsl_error(&(yylsp[-1]), state,
                          "\"invariant\" cannot be used with layout(...)");
      }

      (yyval.type_qualifier) = (yyvsp[0].type_qualifier);
      (yyval.type_qualifier).flags.q.invariant = 1;
   }
#line 4604 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1521 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
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
      if ((yyvsp[0].type_qualifier).has_interpolation())
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate interpolation qualifier");

      if ((yyvsp[0].type_qualifier).has_layout()) {
         _mesa_glsl_error(&(yylsp[-1]), state, "interpolation qualifiers cannot be used "
                          "with layout(...)");
      }

      if (!state->ARB_shading_language_420pack_enable && (yyvsp[0].type_qualifier).flags.q.invariant) {
         _mesa_glsl_error(&(yylsp[-1]), state, "interpolation qualifiers must come "
                          "after \"invariant\"");
      }

      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
      (yyval.type_qualifier).merge_qualifier(&(yylsp[-1]), state, (yyvsp[0].type_qualifier));
   }
#line 4636 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1549 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      /* The GLSL 1.50 grammar indicates that a layout(...) declaration can be
       * used standalone or immediately before a storage qualifier.  It cannot
       * be used with interpolation qualifiers or invariant.  There does not
       * appear to be any text indicating that it must come before the storage
       * qualifier, but always seems to in examples.
       */
      if (!state->ARB_shading_language_420pack_enable && (yyvsp[0].type_qualifier).has_layout())
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate layout(...) qualifiers");

      if ((yyvsp[0].type_qualifier).flags.q.invariant)
         _mesa_glsl_error(&(yylsp[-1]), state, "layout(...) cannot be used with "
                          "the \"invariant\" qualifier");

      if ((yyvsp[0].type_qualifier).has_interpolation()) {
         _mesa_glsl_error(&(yylsp[-1]), state, "layout(...) cannot be used with "
                          "interpolation qualifiers");
      }

      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
      (yyval.type_qualifier).merge_qualifier(&(yylsp[-1]), state, (yyvsp[0].type_qualifier));
   }
#line 4663 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1572 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].type_qualifier).has_auxiliary_storage()) {
         _mesa_glsl_error(&(yylsp[-1]), state,
                          "duplicate auxiliary storage qualifier (centroid or sample)");
      }

      if (!state->ARB_shading_language_420pack_enable &&
          ((yyvsp[0].type_qualifier).flags.q.invariant || (yyvsp[0].type_qualifier).has_interpolation() || (yyvsp[0].type_qualifier).has_layout())) {
         _mesa_glsl_error(&(yylsp[-1]), state, "auxiliary storage qualifiers must come "
                          "just before storage qualifiers");
      }
      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
      (yyval.type_qualifier).merge_qualifier(&(yylsp[-1]), state, (yyvsp[0].type_qualifier));
   }
#line 4682 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1587 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      /* Section 4.3 of the GLSL 1.20 specification states:
       * "Variable declarations may have a storage qualifier specified..."
       *  1.30 clarifies this to "may have one storage qualifier".
       */
      if ((yyvsp[0].type_qualifier).has_storage())
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate storage qualifier");

      if (!state->ARB_shading_language_420pack_enable &&
          ((yyvsp[0].type_qualifier).flags.q.invariant || (yyvsp[0].type_qualifier).has_interpolation() || (yyvsp[0].type_qualifier).has_layout() ||
           (yyvsp[0].type_qualifier).has_auxiliary_storage())) {
         _mesa_glsl_error(&(yylsp[-1]), state, "storage qualifiers must come after "
                          "invariant, interpolation, layout and auxiliary "
                          "storage qualifiers");
      }

      (yyval.type_qualifier) = (yyvsp[-1].type_qualifier);
      (yyval.type_qualifier).merge_qualifier(&(yylsp[-1]), state, (yyvsp[0].type_qualifier));
   }
#line 4706 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 1607 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].type_qualifier).precision != ast_precision_none)
         _mesa_glsl_error(&(yylsp[-1]), state, "duplicate precision qualifier");

      if (!state->ARB_shading_language_420pack_enable && (yyvsp[0].type_qualifier).flags.i != 0)
         _mesa_glsl_error(&(yylsp[-1]), state, "precision qualifiers must come last");

      (yyval.type_qualifier) = (yyvsp[0].type_qualifier);
      (yyval.type_qualifier).precision = (yyvsp[-1].n);
   }
#line 4721 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1621 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.centroid = 1;
   }
#line 4731 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1627 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q.sample = 1;
   }
#line 4740 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1635 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.constant = 1;
   }
#line 4750 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1641 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.attribute = 1;
   }
#line 4760 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1647 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.varying = 1;
   }
#line 4770 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1653 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.in = 1;
   }
#line 4780 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1659 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.out = 1;
   }
#line 4790 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 1665 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.uniform = 1;
   }
#line 4800 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 1671 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q.coherent = 1;
   }
#line 4809 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 1676 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q._volatile = 1;
   }
#line 4818 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1681 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      STATIC_ASSERT(sizeof((yyval.type_qualifier).flags.q) <= sizeof((yyval.type_qualifier).flags.i));
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q.restrict_flag = 1;
   }
#line 4828 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1687 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q.read_only = 1;
   }
#line 4837 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1692 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
      (yyval.type_qualifier).flags.q.write_only = 1;
   }
#line 4846 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1700 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.array_specifier) = new(ctx) ast_array_specifier(yylloc);
   }
#line 4855 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 1705 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.array_specifier) = new(ctx) ast_array_specifier(yylloc, (yyvsp[-1].expression));
   }
#line 4864 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 1710 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.array_specifier) = (yyvsp[-2].array_specifier);

      if (!state->ARB_arrays_of_arrays_enable) {
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "GL_ARB_arrays_of_arrays "
                          "required for defining arrays of arrays");
      } else {
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "only the outermost array dimension can "
                          "be unsized");
      }
   }
#line 4882 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1724 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.array_specifier) = (yyvsp[-3].array_specifier);

      if (!state->ARB_arrays_of_arrays_enable) {
         _mesa_glsl_error(& (yylsp[-3]), state,
                          "GL_ARB_arrays_of_arrays "
                          "required for defining arrays of arrays");
      }

      (yyval.array_specifier)->add_dimension((yyvsp[-1].expression));
   }
#line 4898 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1740 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.type_specifier) = (yyvsp[-1].type_specifier);
      (yyval.type_specifier)->array_specifier = (yyvsp[0].array_specifier);
   }
#line 4907 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 1748 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[0].identifier));
      (yyval.type_specifier)->set_location(yylloc);
   }
#line 4917 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 1754 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[0].struct_specifier));
      (yyval.type_specifier)->set_location(yylloc);
   }
#line 4927 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 1760 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[0].identifier));
      (yyval.type_specifier)->set_location(yylloc);
   }
#line 4937 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1768 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "void"; }
#line 4943 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1769 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "float"; }
#line 4949 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1770 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "int"; }
#line 4955 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1771 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uint"; }
#line 4961 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1772 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "bool"; }
#line 4967 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1773 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "vec2"; }
#line 4973 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1774 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "vec3"; }
#line 4979 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 1775 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "vec4"; }
#line 4985 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 1776 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "bvec2"; }
#line 4991 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1777 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "bvec3"; }
#line 4997 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1778 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "bvec4"; }
#line 5003 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 1779 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "ivec2"; }
#line 5009 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 1780 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "ivec3"; }
#line 5015 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1781 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "ivec4"; }
#line 5021 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1782 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uvec2"; }
#line 5027 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1783 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uvec3"; }
#line 5033 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1784 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uvec4"; }
#line 5039 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1785 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat2"; }
#line 5045 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 1786 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat2x3"; }
#line 5051 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1787 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat2x4"; }
#line 5057 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 1788 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat3x2"; }
#line 5063 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 1789 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat3"; }
#line 5069 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1790 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat3x4"; }
#line 5075 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1791 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat4x2"; }
#line 5081 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 1792 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat4x3"; }
#line 5087 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1793 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "mat4"; }
#line 5093 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 1794 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler1D"; }
#line 5099 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 1795 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2D"; }
#line 5105 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1796 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DRect"; }
#line 5111 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1797 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler3D"; }
#line 5117 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1798 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerCube"; }
#line 5123 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1799 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerExternalOES"; }
#line 5129 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1800 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler1DShadow"; }
#line 5135 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 1801 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DShadow"; }
#line 5141 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 1802 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DRectShadow"; }
#line 5147 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1803 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerCubeShadow"; }
#line 5153 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1804 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler1DArray"; }
#line 5159 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1805 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DArray"; }
#line 5165 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1806 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler1DArrayShadow"; }
#line 5171 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1807 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DArrayShadow"; }
#line 5177 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 1808 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerBuffer"; }
#line 5183 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1809 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerCubeArray"; }
#line 5189 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1810 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "samplerCubeArrayShadow"; }
#line 5195 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1811 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler1D"; }
#line 5201 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 1812 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler2D"; }
#line 5207 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1813 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler2DRect"; }
#line 5213 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1814 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler3D"; }
#line 5219 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 1815 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isamplerCube"; }
#line 5225 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 1816 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler1DArray"; }
#line 5231 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1817 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler2DArray"; }
#line 5237 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1818 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isamplerBuffer"; }
#line 5243 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1819 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isamplerCubeArray"; }
#line 5249 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1820 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler1D"; }
#line 5255 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 1821 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler2D"; }
#line 5261 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1822 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler2DRect"; }
#line 5267 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1823 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler3D"; }
#line 5273 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 1824 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usamplerCube"; }
#line 5279 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1825 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler1DArray"; }
#line 5285 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1826 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler2DArray"; }
#line 5291 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1827 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usamplerBuffer"; }
#line 5297 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1828 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usamplerCubeArray"; }
#line 5303 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 1829 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DMS"; }
#line 5309 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1830 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler2DMS"; }
#line 5315 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 1831 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler2DMS"; }
#line 5321 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 1832 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "sampler2DMSArray"; }
#line 5327 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 1833 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "isampler2DMSArray"; }
#line 5333 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1834 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "usampler2DMSArray"; }
#line 5339 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1835 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image1D"; }
#line 5345 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1836 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image2D"; }
#line 5351 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1837 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image3D"; }
#line 5357 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 1838 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image2DRect"; }
#line 5363 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1839 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "imageCube"; }
#line 5369 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 1840 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "imageBuffer"; }
#line 5375 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 1841 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image1DArray"; }
#line 5381 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1842 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image2DArray"; }
#line 5387 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 1843 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "imageCubeArray"; }
#line 5393 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1844 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image2DMS"; }
#line 5399 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 1845 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "image2DMSArray"; }
#line 5405 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 1846 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage1D"; }
#line 5411 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 1847 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage2D"; }
#line 5417 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 1848 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage3D"; }
#line 5423 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 1849 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage2DRect"; }
#line 5429 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 1850 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimageCube"; }
#line 5435 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1851 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimageBuffer"; }
#line 5441 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1852 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage1DArray"; }
#line 5447 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 1853 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage2DArray"; }
#line 5453 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 1854 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimageCubeArray"; }
#line 5459 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 1855 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage2DMS"; }
#line 5465 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 1856 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "iimage2DMSArray"; }
#line 5471 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 1857 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage1D"; }
#line 5477 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 1858 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage2D"; }
#line 5483 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 1859 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage3D"; }
#line 5489 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 1860 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage2DRect"; }
#line 5495 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 1861 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimageCube"; }
#line 5501 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 1862 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimageBuffer"; }
#line 5507 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 1863 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage1DArray"; }
#line 5513 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 1864 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage2DArray"; }
#line 5519 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 1865 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimageCubeArray"; }
#line 5525 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 1866 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage2DMS"; }
#line 5531 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 1867 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "uimage2DMSArray"; }
#line 5537 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 1868 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.identifier) = "atomic_uint"; }
#line 5543 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 1873 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->check_precision_qualifiers_allowed(&(yylsp[0]));
      (yyval.n) = ast_precision_high;
   }
#line 5552 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 1878 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->check_precision_qualifiers_allowed(&(yylsp[0]));
      (yyval.n) = ast_precision_medium;
   }
#line 5561 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 1883 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->check_precision_qualifiers_allowed(&(yylsp[0]));
      (yyval.n) = ast_precision_low;
   }
#line 5570 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 1891 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.struct_specifier) = new(ctx) ast_struct_specifier((yyvsp[-3].identifier), (yyvsp[-1].declarator_list));
      (yyval.struct_specifier)->set_location(yylloc);
      state->symbols->add_type((yyvsp[-3].identifier), glsl_type::void_type);
      state->symbols->add_type_ast((yyvsp[-3].identifier), new(ctx) ast_type_specifier((yyval.struct_specifier)));
   }
#line 5582 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 1899 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.struct_specifier) = new(ctx) ast_struct_specifier(NULL, (yyvsp[-1].declarator_list));
      (yyval.struct_specifier)->set_location(yylloc);
   }
#line 5592 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 1908 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declarator_list) = (yyvsp[0].declarator_list);
      (yyvsp[0].declarator_list)->link.self_link();
   }
#line 5601 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 1913 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declarator_list) = (yyvsp[-1].declarator_list);
      (yyval.declarator_list)->link.insert_before(& (yyvsp[0].declarator_list)->link);
   }
#line 5610 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 1921 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_fully_specified_type *const type = (yyvsp[-2].fully_specified_type);
      type->set_location(yylloc);

      if (type->qualifier.flags.i != 0)
         _mesa_glsl_error(&(yylsp[-2]), state,
			  "only precision qualifiers may be applied to "
			  "structure members");

      (yyval.declarator_list) = new(ctx) ast_declarator_list(type);
      (yyval.declarator_list)->set_location(yylloc);

      (yyval.declarator_list)->declarations.push_degenerate_list_at_head(& (yyvsp[-1].declaration)->link);
   }
#line 5630 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 1940 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declaration) = (yyvsp[0].declaration);
      (yyvsp[0].declaration)->link.self_link();
   }
#line 5639 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 1945 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declaration) = (yyvsp[-2].declaration);
      (yyval.declaration)->link.insert_before(& (yyvsp[0].declaration)->link);
   }
#line 5648 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 1953 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.declaration) = new(ctx) ast_declaration((yyvsp[0].identifier), NULL, NULL);
      (yyval.declaration)->set_location(yylloc);
   }
#line 5658 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 1959 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.declaration) = new(ctx) ast_declaration((yyvsp[-1].identifier), (yyvsp[0].array_specifier), NULL);
      (yyval.declaration)->set_location(yylloc);
   }
#line 5668 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 1969 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
   }
#line 5676 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 1973 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.expression) = (yyvsp[-2].expression);
   }
#line 5684 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 1980 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.expression) = new(ctx) ast_aggregate_initializer();
      (yyval.expression)->set_location(yylloc);
      (yyval.expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 5695 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 1987 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyvsp[-2].expression)->expressions.push_tail(& (yyvsp[0].expression)->link);
   }
#line 5703 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 1999 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = (ast_node *) (yyvsp[0].compound_statement); }
#line 5709 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 2014 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.compound_statement) = new(ctx) ast_compound_statement(true, NULL);
      (yyval.compound_statement)->set_location(yylloc);
   }
#line 5719 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 2020 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      state->symbols->push_scope();
   }
#line 5727 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 2024 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.compound_statement) = new(ctx) ast_compound_statement(true, (yyvsp[-1].node));
      (yyval.compound_statement)->set_location(yylloc);
      state->symbols->pop_scope();
   }
#line 5738 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 2033 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = (ast_node *) (yyvsp[0].compound_statement); }
#line 5744 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 2039 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.compound_statement) = new(ctx) ast_compound_statement(false, NULL);
      (yyval.compound_statement)->set_location(yylloc);
   }
#line 5754 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 2045 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.compound_statement) = new(ctx) ast_compound_statement(false, (yyvsp[-1].node));
      (yyval.compound_statement)->set_location(yylloc);
   }
#line 5764 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 2054 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].node) == NULL) {
         _mesa_glsl_error(& (yylsp[0]), state, "<nil> statement");
         assert((yyvsp[0].node) != NULL);
      }

      (yyval.node) = (yyvsp[0].node);
      (yyval.node)->link.self_link();
   }
#line 5778 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 328:
#line 2064 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if ((yyvsp[0].node) == NULL) {
         _mesa_glsl_error(& (yylsp[0]), state, "<nil> statement");
         assert((yyvsp[0].node) != NULL);
      }
      (yyval.node) = (yyvsp[-1].node);
      (yyval.node)->link.insert_before(& (yyvsp[0].node)->link);
   }
#line 5791 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 2076 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_expression_statement(NULL);
      (yyval.node)->set_location(yylloc);
   }
#line 5801 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 2082 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_expression_statement((yyvsp[-1].expression));
      (yyval.node)->set_location(yylloc);
   }
#line 5811 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 2091 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = new(state) ast_selection_statement((yyvsp[-2].expression), (yyvsp[0].selection_rest_statement).then_statement,
                                              (yyvsp[0].selection_rest_statement).else_statement);
      (yyval.node)->set_location(yylloc);
   }
#line 5821 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 2100 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.selection_rest_statement).then_statement = (yyvsp[-2].node);
      (yyval.selection_rest_statement).else_statement = (yyvsp[0].node);
   }
#line 5830 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 2105 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.selection_rest_statement).then_statement = (yyvsp[0].node);
      (yyval.selection_rest_statement).else_statement = NULL;
   }
#line 5839 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 2113 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = (ast_node *) (yyvsp[0].expression);
   }
#line 5847 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 2117 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_declaration *decl = new(ctx) ast_declaration((yyvsp[-2].identifier), NULL, (yyvsp[0].expression));
      ast_declarator_list *declarator = new(ctx) ast_declarator_list((yyvsp[-3].fully_specified_type));
      decl->set_location(yylloc);
      declarator->set_location(yylloc);

      declarator->declarations.push_tail(&decl->link);
      (yyval.node) = declarator;
   }
#line 5862 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 2135 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = new(state) ast_switch_statement((yyvsp[-2].expression), (yyvsp[0].switch_body));
      (yyval.node)->set_location(yylloc);
   }
#line 5871 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 2143 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.switch_body) = new(state) ast_switch_body(NULL);
      (yyval.switch_body)->set_location(yylloc);
   }
#line 5880 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 2148 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.switch_body) = new(state) ast_switch_body((yyvsp[-1].case_statement_list));
      (yyval.switch_body)->set_location(yylloc);
   }
#line 5889 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 339:
#line 2156 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.case_label) = new(state) ast_case_label((yyvsp[-1].expression));
      (yyval.case_label)->set_location(yylloc);
   }
#line 5898 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 340:
#line 2161 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.case_label) = new(state) ast_case_label(NULL);
      (yyval.case_label)->set_location(yylloc);
   }
#line 5907 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 341:
#line 2169 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      ast_case_label_list *labels = new(state) ast_case_label_list();

      labels->labels.push_tail(& (yyvsp[0].case_label)->link);
      (yyval.case_label_list) = labels;
      (yyval.case_label_list)->set_location(yylloc);
   }
#line 5919 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 342:
#line 2177 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.case_label_list) = (yyvsp[-1].case_label_list);
      (yyval.case_label_list)->labels.push_tail(& (yyvsp[0].case_label)->link);
   }
#line 5928 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 343:
#line 2185 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      ast_case_statement *stmts = new(state) ast_case_statement((yyvsp[-1].case_label_list));
      stmts->set_location(yylloc);

      stmts->stmts.push_tail(& (yyvsp[0].node)->link);
      (yyval.case_statement) = stmts;
   }
#line 5940 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 344:
#line 2193 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.case_statement) = (yyvsp[-1].case_statement);
      (yyval.case_statement)->stmts.push_tail(& (yyvsp[0].node)->link);
   }
#line 5949 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 345:
#line 2201 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      ast_case_statement_list *cases= new(state) ast_case_statement_list();
      cases->set_location(yylloc);

      cases->cases.push_tail(& (yyvsp[0].case_statement)->link);
      (yyval.case_statement_list) = cases;
   }
#line 5961 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 346:
#line 2209 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.case_statement_list) = (yyvsp[-1].case_statement_list);
      (yyval.case_statement_list)->cases.push_tail(& (yyvsp[0].case_statement)->link);
   }
#line 5970 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 347:
#line 2217 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
                                            NULL, (yyvsp[-2].node), NULL, (yyvsp[0].node));
      (yyval.node)->set_location(yylloc);
   }
#line 5981 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 348:
#line 2224 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
                                            NULL, (yyvsp[-2].expression), NULL, (yyvsp[-5].node));
      (yyval.node)->set_location(yylloc);
   }
#line 5992 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 349:
#line 2231 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
                                            (yyvsp[-3].node), (yyvsp[-2].for_rest_statement).cond, (yyvsp[-2].for_rest_statement).rest, (yyvsp[0].node));
      (yyval.node)->set_location(yylloc);
   }
#line 6003 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 353:
#line 2247 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = NULL;
   }
#line 6011 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 354:
#line 2254 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.for_rest_statement).cond = (yyvsp[-1].node);
      (yyval.for_rest_statement).rest = NULL;
   }
#line 6020 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 355:
#line 2259 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.for_rest_statement).cond = (yyvsp[-2].node);
      (yyval.for_rest_statement).rest = (yyvsp[0].expression);
   }
#line 6029 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 356:
#line 2268 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
      (yyval.node)->set_location(yylloc);
   }
#line 6039 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 357:
#line 2274 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
      (yyval.node)->set_location(yylloc);
   }
#line 6049 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 358:
#line 2280 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
      (yyval.node)->set_location(yylloc);
   }
#line 6059 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 359:
#line 2286 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, (yyvsp[-1].expression));
      (yyval.node)->set_location(yylloc);
   }
#line 6069 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 360:
#line 2292 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
      (yyval.node)->set_location(yylloc);
   }
#line 6079 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 361:
#line 2300 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].function_definition); }
#line 6085 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 362:
#line 2301 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 6091 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 363:
#line 2302 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 6097 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 364:
#line 2303 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 6103 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 365:
#line 2308 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.function_definition) = new(ctx) ast_function_definition();
      (yyval.function_definition)->set_location(yylloc);
      (yyval.function_definition)->prototype = (yyvsp[-1].function);
      (yyval.function_definition)->body = (yyvsp[0].compound_statement);

      state->symbols->pop_scope();
   }
#line 6117 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 366:
#line 2322 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.node) = (yyvsp[0].interface_block);
   }
#line 6125 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 367:
#line 2326 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      ast_interface_block *block = (yyvsp[0].interface_block);
      if (!block->layout.merge_qualifier(& (yylsp[-1]), state, (yyvsp[-1].type_qualifier))) {
         YYERROR;
      }
      (yyval.node) = block;
   }
#line 6137 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 368:
#line 2337 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      ast_interface_block *const block = (yyvsp[-1].interface_block);

      block->block_name = (yyvsp[-5].identifier);
      block->declarations.push_degenerate_list_at_head(& (yyvsp[-3].declarator_list)->link);

      if ((yyvsp[-6].type_qualifier).flags.q.uniform) {
         if (!state->has_uniform_buffer_objects()) {
            _mesa_glsl_error(& (yylsp[-6]), state,
                             "#version 140 / GL_ARB_uniform_buffer_object "
                             "required for defining uniform blocks");
         } else if (state->ARB_uniform_buffer_object_warn) {
            _mesa_glsl_warning(& (yylsp[-6]), state,
                               "#version 140 / GL_ARB_uniform_buffer_object "
                               "required for defining uniform blocks");
         }
      } else {
         if (state->es_shader || state->language_version < 150) {
            _mesa_glsl_error(& (yylsp[-6]), state,
                             "#version 150 required for using "
                             "interface blocks");
         }
      }

      /* From the GLSL 1.50.11 spec, section 4.3.7 ("Interface Blocks"):
       * "It is illegal to have an input block in a vertex shader
       *  or an output block in a fragment shader"
       */
      if ((state->stage == MESA_SHADER_VERTEX) && (yyvsp[-6].type_qualifier).flags.q.in) {
         _mesa_glsl_error(& (yylsp[-6]), state,
                          "`in' interface block is not allowed for "
                          "a vertex shader");
      } else if ((state->stage == MESA_SHADER_FRAGMENT) && (yyvsp[-6].type_qualifier).flags.q.out) {
         _mesa_glsl_error(& (yylsp[-6]), state,
                          "`out' interface block is not allowed for "
                          "a fragment shader");
      }

      /* Since block arrays require names, and both features are added in
       * the same language versions, we don't have to explicitly
       * version-check both things.
       */
      if (block->instance_name != NULL) {
         state->check_version(150, 300, & (yylsp[-6]), "interface blocks with "
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
      uint64_t block_interface_qualifier = (yyvsp[-6].type_qualifier).flags.i;

      block->layout.flags.i |= block_interface_qualifier;

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
            _mesa_glsl_error(& (yylsp[-6]), state,
                             "uniform/in/out qualifier on "
                             "interface block member does not match "
                             "the interface block");
         }
      }

      (yyval.interface_block) = block;
   }
#line 6235 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 369:
#line 2434 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.in = 1;
   }
#line 6245 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 370:
#line 2440 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.out = 1;
   }
#line 6255 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 371:
#line 2446 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	  (yyval.type_qualifier).precision = ast_precision_none;
      (yyval.type_qualifier).flags.q.uniform = 1;
   }
#line 6265 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 372:
#line 2455 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.interface_block) = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          NULL, NULL);
   }
#line 6274 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 373:
#line 2460 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.interface_block) = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          (yyvsp[0].identifier), NULL);
   }
#line 6283 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 374:
#line 2465 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.interface_block) = new(state) ast_interface_block(*state->default_uniform_qualifier,
                                          (yyvsp[-1].identifier), (yyvsp[0].array_specifier));
   }
#line 6292 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 375:
#line 2473 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declarator_list) = (yyvsp[0].declarator_list);
      (yyvsp[0].declarator_list)->link.self_link();
   }
#line 6301 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 376:
#line 2478 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      (yyval.declarator_list) = (yyvsp[-1].declarator_list);
      (yyvsp[0].declarator_list)->link.insert_before(& (yyval.declarator_list)->link);
   }
#line 6310 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 377:
#line 2486 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      ast_fully_specified_type *type = (yyvsp[-2].fully_specified_type);
      type->set_location(yylloc);

      if (type->qualifier.flags.q.attribute) {
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "keyword 'attribute' cannot be used with "
                          "interface block member");
      } else if (type->qualifier.flags.q.varying) {
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "keyword 'varying' cannot be used with "
                          "interface block member");
      }

      (yyval.declarator_list) = new(ctx) ast_declarator_list(type);
      (yyval.declarator_list)->set_location(yylloc);

      (yyval.declarator_list)->declarations.push_degenerate_list_at_head(& (yyvsp[-1].declaration)->link);
   }
#line 6335 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 378:
#line 2510 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if (!state->default_uniform_qualifier->merge_qualifier(& (yylsp[-2]), state, (yyvsp[-2].type_qualifier))) {
         YYERROR;
      }
      (yyval.node) = NULL;
   }
#line 6346 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 379:
#line 2518 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      void *ctx = state;
      (yyval.node) = NULL;
      switch (state->stage) {
      case MESA_SHADER_GEOMETRY: {
         if (!(yyvsp[-2].type_qualifier).flags.q.prim_type) {
            _mesa_glsl_error(& (yylsp[-2]), state,
                             "input layout qualifiers must specify a primitive"
                             " type");
         } else {
            /* Make sure this is a valid input primitive type. */
            switch ((yyvsp[-2].type_qualifier).prim_type) {
            case GL_POINTS:
            case GL_LINES:
            case GL_LINES_ADJACENCY:
            case GL_TRIANGLES:
            case GL_TRIANGLES_ADJACENCY:
               (yyval.node) = new(ctx) ast_gs_input_layout((yylsp[-2]), (yyvsp[-2].type_qualifier).prim_type);
               break;
            default:
               _mesa_glsl_error(&(yylsp[-2]), state,
                                "invalid geometry shader input primitive type");
               break;
            }
         }
      }
         break;
      case MESA_SHADER_FRAGMENT:
         if ((yyvsp[-2].type_qualifier).flags.q.early_fragment_tests) {
            state->early_fragment_tests = true;
         } else {
            _mesa_glsl_error(& (yylsp[-2]), state, "invalid input layout qualifier");
         }
         break;
      case MESA_SHADER_COMPUTE: {
         if ((yyvsp[-2].type_qualifier).flags.q.local_size == 0) {
            _mesa_glsl_error(& (yylsp[-2]), state,
                             "input layout qualifiers must specify a local "
                             "size");
         } else {
            /* Infer a local_size of 1 for every unspecified dimension */
            unsigned local_size[3];
            for (int i = 0; i < 3; i++) {
               if ((yyvsp[-2].type_qualifier).flags.q.local_size & (1 << i))
                  local_size[i] = (yyvsp[-2].type_qualifier).local_size[i];
               else
                  local_size[i] = 1;
            }
            (yyval.node) = new(ctx) ast_cs_input_layout((yylsp[-2]), local_size);
         }
      }
         break;
      default:
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "input layout qualifiers only valid in "
                          "geometry, fragment and compute shaders");
         break;
      }
   }
#line 6410 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;

  case 380:
#line 2579 "src/glsl/glsl_parser.yy" /* yacc.c:1646  */
    {
      if (state->stage != MESA_SHADER_GEOMETRY) {
         _mesa_glsl_error(& (yylsp[-2]), state,
                          "out layout qualifiers only valid in "
                          "geometry shaders");
      } else {
         if ((yyvsp[-2].type_qualifier).flags.q.prim_type) {
            /* Make sure this is a valid output primitive type. */
            switch ((yyvsp[-2].type_qualifier).prim_type) {
            case GL_POINTS:
            case GL_LINE_STRIP:
            case GL_TRIANGLE_STRIP:
               break;
            default:
               _mesa_glsl_error(&(yylsp[-2]), state, "invalid geometry shader output "
                                "primitive type");
               break;
            }
         }
         if (!state->out_qualifier->merge_qualifier(& (yylsp[-2]), state, (yyvsp[-2].type_qualifier)))
            YYERROR;
      }
      (yyval.node) = NULL;
   }
#line 6439 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
    break;


#line 6443 "src/glsl/glsl_parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, state, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, state, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, state);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, state, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, state);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, state);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 43 "MachineIndependent/glslang.y" /* yacc.c:339  */


/* Based on:
ANSI C Yacc grammar

In 1985, Jeff Lee published his Yacc grammar (which is accompanied by a
matching Lex specification) for the April 30, 1985 draft version of the
ANSI C standard.  Tom Stockfisch reposted it to net.sources in 1987; that
original, as mentioned in the answer to question 17.25 of the comp.lang.c
FAQ, can be ftp'ed from ftp.uu.net, file usenet/net.sources/ansi.c.grammar.Z.

I intend to keep this version as close to the current C Standard grammar as
possible; please let me know if you discover discrepancies.

Jutta Degener, 1995
*/

#include "SymbolTable.h"
#include "ParseHelper.h"
#include "../Public/ShaderLang.h"
#include "attribute.h"

using namespace glslang;


#line 92 "MachineIndependent/glslang_tab.cpp" /* yacc.c:339  */

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
   by #include "glslang_tab.cpp.h".  */
#ifndef YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ATTRIBUTE = 258,
    VARYING = 259,
    FLOAT16_T = 260,
    FLOAT = 261,
    FLOAT32_T = 262,
    DOUBLE = 263,
    FLOAT64_T = 264,
    CONST = 265,
    BOOL = 266,
    INT = 267,
    UINT = 268,
    INT64_T = 269,
    UINT64_T = 270,
    INT32_T = 271,
    UINT32_T = 272,
    INT16_T = 273,
    UINT16_T = 274,
    INT8_T = 275,
    UINT8_T = 276,
    BREAK = 277,
    CONTINUE = 278,
    DO = 279,
    ELSE = 280,
    FOR = 281,
    IF = 282,
    DISCARD = 283,
    RETURN = 284,
    SWITCH = 285,
    CASE = 286,
    DEFAULT = 287,
    SUBROUTINE = 288,
    BVEC2 = 289,
    BVEC3 = 290,
    BVEC4 = 291,
    IVEC2 = 292,
    IVEC3 = 293,
    IVEC4 = 294,
    UVEC2 = 295,
    UVEC3 = 296,
    UVEC4 = 297,
    I64VEC2 = 298,
    I64VEC3 = 299,
    I64VEC4 = 300,
    U64VEC2 = 301,
    U64VEC3 = 302,
    U64VEC4 = 303,
    I32VEC2 = 304,
    I32VEC3 = 305,
    I32VEC4 = 306,
    U32VEC2 = 307,
    U32VEC3 = 308,
    U32VEC4 = 309,
    I16VEC2 = 310,
    I16VEC3 = 311,
    I16VEC4 = 312,
    U16VEC2 = 313,
    U16VEC3 = 314,
    U16VEC4 = 315,
    I8VEC2 = 316,
    I8VEC3 = 317,
    I8VEC4 = 318,
    U8VEC2 = 319,
    U8VEC3 = 320,
    U8VEC4 = 321,
    VEC2 = 322,
    VEC3 = 323,
    VEC4 = 324,
    MAT2 = 325,
    MAT3 = 326,
    MAT4 = 327,
    CENTROID = 328,
    IN = 329,
    OUT = 330,
    INOUT = 331,
    UNIFORM = 332,
    PATCH = 333,
    SAMPLE = 334,
    BUFFER = 335,
    SHARED = 336,
    NONUNIFORM = 337,
    PAYLOADNV = 338,
    PAYLOADINNV = 339,
    HITATTRNV = 340,
    CALLDATANV = 341,
    CALLDATAINNV = 342,
    COHERENT = 343,
    VOLATILE = 344,
    RESTRICT = 345,
    READONLY = 346,
    WRITEONLY = 347,
    DEVICECOHERENT = 348,
    QUEUEFAMILYCOHERENT = 349,
    WORKGROUPCOHERENT = 350,
    SUBGROUPCOHERENT = 351,
    NONPRIVATE = 352,
    DVEC2 = 353,
    DVEC3 = 354,
    DVEC4 = 355,
    DMAT2 = 356,
    DMAT3 = 357,
    DMAT4 = 358,
    F16VEC2 = 359,
    F16VEC3 = 360,
    F16VEC4 = 361,
    F16MAT2 = 362,
    F16MAT3 = 363,
    F16MAT4 = 364,
    F32VEC2 = 365,
    F32VEC3 = 366,
    F32VEC4 = 367,
    F32MAT2 = 368,
    F32MAT3 = 369,
    F32MAT4 = 370,
    F64VEC2 = 371,
    F64VEC3 = 372,
    F64VEC4 = 373,
    F64MAT2 = 374,
    F64MAT3 = 375,
    F64MAT4 = 376,
    NOPERSPECTIVE = 377,
    FLAT = 378,
    SMOOTH = 379,
    LAYOUT = 380,
    EXPLICITINTERPAMD = 381,
    PERVERTEXNV = 382,
    PERPRIMITIVENV = 383,
    PERVIEWNV = 384,
    PERTASKNV = 385,
    MAT2X2 = 386,
    MAT2X3 = 387,
    MAT2X4 = 388,
    MAT3X2 = 389,
    MAT3X3 = 390,
    MAT3X4 = 391,
    MAT4X2 = 392,
    MAT4X3 = 393,
    MAT4X4 = 394,
    DMAT2X2 = 395,
    DMAT2X3 = 396,
    DMAT2X4 = 397,
    DMAT3X2 = 398,
    DMAT3X3 = 399,
    DMAT3X4 = 400,
    DMAT4X2 = 401,
    DMAT4X3 = 402,
    DMAT4X4 = 403,
    F16MAT2X2 = 404,
    F16MAT2X3 = 405,
    F16MAT2X4 = 406,
    F16MAT3X2 = 407,
    F16MAT3X3 = 408,
    F16MAT3X4 = 409,
    F16MAT4X2 = 410,
    F16MAT4X3 = 411,
    F16MAT4X4 = 412,
    F32MAT2X2 = 413,
    F32MAT2X3 = 414,
    F32MAT2X4 = 415,
    F32MAT3X2 = 416,
    F32MAT3X3 = 417,
    F32MAT3X4 = 418,
    F32MAT4X2 = 419,
    F32MAT4X3 = 420,
    F32MAT4X4 = 421,
    F64MAT2X2 = 422,
    F64MAT2X3 = 423,
    F64MAT2X4 = 424,
    F64MAT3X2 = 425,
    F64MAT3X3 = 426,
    F64MAT3X4 = 427,
    F64MAT4X2 = 428,
    F64MAT4X3 = 429,
    F64MAT4X4 = 430,
    ATOMIC_UINT = 431,
    ACCSTRUCTNV = 432,
    FCOOPMATNV = 433,
    SAMPLER1D = 434,
    SAMPLER2D = 435,
    SAMPLER3D = 436,
    SAMPLERCUBE = 437,
    SAMPLER1DSHADOW = 438,
    SAMPLER2DSHADOW = 439,
    SAMPLERCUBESHADOW = 440,
    SAMPLER1DARRAY = 441,
    SAMPLER2DARRAY = 442,
    SAMPLER1DARRAYSHADOW = 443,
    SAMPLER2DARRAYSHADOW = 444,
    ISAMPLER1D = 445,
    ISAMPLER2D = 446,
    ISAMPLER3D = 447,
    ISAMPLERCUBE = 448,
    ISAMPLER1DARRAY = 449,
    ISAMPLER2DARRAY = 450,
    USAMPLER1D = 451,
    USAMPLER2D = 452,
    USAMPLER3D = 453,
    USAMPLERCUBE = 454,
    USAMPLER1DARRAY = 455,
    USAMPLER2DARRAY = 456,
    SAMPLER2DRECT = 457,
    SAMPLER2DRECTSHADOW = 458,
    ISAMPLER2DRECT = 459,
    USAMPLER2DRECT = 460,
    SAMPLERBUFFER = 461,
    ISAMPLERBUFFER = 462,
    USAMPLERBUFFER = 463,
    SAMPLERCUBEARRAY = 464,
    SAMPLERCUBEARRAYSHADOW = 465,
    ISAMPLERCUBEARRAY = 466,
    USAMPLERCUBEARRAY = 467,
    SAMPLER2DMS = 468,
    ISAMPLER2DMS = 469,
    USAMPLER2DMS = 470,
    SAMPLER2DMSARRAY = 471,
    ISAMPLER2DMSARRAY = 472,
    USAMPLER2DMSARRAY = 473,
    SAMPLEREXTERNALOES = 474,
    SAMPLEREXTERNAL2DY2YEXT = 475,
    F16SAMPLER1D = 476,
    F16SAMPLER2D = 477,
    F16SAMPLER3D = 478,
    F16SAMPLER2DRECT = 479,
    F16SAMPLERCUBE = 480,
    F16SAMPLER1DARRAY = 481,
    F16SAMPLER2DARRAY = 482,
    F16SAMPLERCUBEARRAY = 483,
    F16SAMPLERBUFFER = 484,
    F16SAMPLER2DMS = 485,
    F16SAMPLER2DMSARRAY = 486,
    F16SAMPLER1DSHADOW = 487,
    F16SAMPLER2DSHADOW = 488,
    F16SAMPLER1DARRAYSHADOW = 489,
    F16SAMPLER2DARRAYSHADOW = 490,
    F16SAMPLER2DRECTSHADOW = 491,
    F16SAMPLERCUBESHADOW = 492,
    F16SAMPLERCUBEARRAYSHADOW = 493,
    SAMPLER = 494,
    SAMPLERSHADOW = 495,
    TEXTURE1D = 496,
    TEXTURE2D = 497,
    TEXTURE3D = 498,
    TEXTURECUBE = 499,
    TEXTURE1DARRAY = 500,
    TEXTURE2DARRAY = 501,
    ITEXTURE1D = 502,
    ITEXTURE2D = 503,
    ITEXTURE3D = 504,
    ITEXTURECUBE = 505,
    ITEXTURE1DARRAY = 506,
    ITEXTURE2DARRAY = 507,
    UTEXTURE1D = 508,
    UTEXTURE2D = 509,
    UTEXTURE3D = 510,
    UTEXTURECUBE = 511,
    UTEXTURE1DARRAY = 512,
    UTEXTURE2DARRAY = 513,
    TEXTURE2DRECT = 514,
    ITEXTURE2DRECT = 515,
    UTEXTURE2DRECT = 516,
    TEXTUREBUFFER = 517,
    ITEXTUREBUFFER = 518,
    UTEXTUREBUFFER = 519,
    TEXTURECUBEARRAY = 520,
    ITEXTURECUBEARRAY = 521,
    UTEXTURECUBEARRAY = 522,
    TEXTURE2DMS = 523,
    ITEXTURE2DMS = 524,
    UTEXTURE2DMS = 525,
    TEXTURE2DMSARRAY = 526,
    ITEXTURE2DMSARRAY = 527,
    UTEXTURE2DMSARRAY = 528,
    F16TEXTURE1D = 529,
    F16TEXTURE2D = 530,
    F16TEXTURE3D = 531,
    F16TEXTURE2DRECT = 532,
    F16TEXTURECUBE = 533,
    F16TEXTURE1DARRAY = 534,
    F16TEXTURE2DARRAY = 535,
    F16TEXTURECUBEARRAY = 536,
    F16TEXTUREBUFFER = 537,
    F16TEXTURE2DMS = 538,
    F16TEXTURE2DMSARRAY = 539,
    SUBPASSINPUT = 540,
    SUBPASSINPUTMS = 541,
    ISUBPASSINPUT = 542,
    ISUBPASSINPUTMS = 543,
    USUBPASSINPUT = 544,
    USUBPASSINPUTMS = 545,
    F16SUBPASSINPUT = 546,
    F16SUBPASSINPUTMS = 547,
    IMAGE1D = 548,
    IIMAGE1D = 549,
    UIMAGE1D = 550,
    IMAGE2D = 551,
    IIMAGE2D = 552,
    UIMAGE2D = 553,
    IMAGE3D = 554,
    IIMAGE3D = 555,
    UIMAGE3D = 556,
    IMAGE2DRECT = 557,
    IIMAGE2DRECT = 558,
    UIMAGE2DRECT = 559,
    IMAGECUBE = 560,
    IIMAGECUBE = 561,
    UIMAGECUBE = 562,
    IMAGEBUFFER = 563,
    IIMAGEBUFFER = 564,
    UIMAGEBUFFER = 565,
    IMAGE1DARRAY = 566,
    IIMAGE1DARRAY = 567,
    UIMAGE1DARRAY = 568,
    IMAGE2DARRAY = 569,
    IIMAGE2DARRAY = 570,
    UIMAGE2DARRAY = 571,
    IMAGECUBEARRAY = 572,
    IIMAGECUBEARRAY = 573,
    UIMAGECUBEARRAY = 574,
    IMAGE2DMS = 575,
    IIMAGE2DMS = 576,
    UIMAGE2DMS = 577,
    IMAGE2DMSARRAY = 578,
    IIMAGE2DMSARRAY = 579,
    UIMAGE2DMSARRAY = 580,
    F16IMAGE1D = 581,
    F16IMAGE2D = 582,
    F16IMAGE3D = 583,
    F16IMAGE2DRECT = 584,
    F16IMAGECUBE = 585,
    F16IMAGE1DARRAY = 586,
    F16IMAGE2DARRAY = 587,
    F16IMAGECUBEARRAY = 588,
    F16IMAGEBUFFER = 589,
    F16IMAGE2DMS = 590,
    F16IMAGE2DMSARRAY = 591,
    STRUCT = 592,
    VOID = 593,
    WHILE = 594,
    IDENTIFIER = 595,
    TYPE_NAME = 596,
    FLOATCONSTANT = 597,
    DOUBLECONSTANT = 598,
    INT16CONSTANT = 599,
    UINT16CONSTANT = 600,
    INT32CONSTANT = 601,
    UINT32CONSTANT = 602,
    INTCONSTANT = 603,
    UINTCONSTANT = 604,
    INT64CONSTANT = 605,
    UINT64CONSTANT = 606,
    BOOLCONSTANT = 607,
    FLOAT16CONSTANT = 608,
    LEFT_OP = 609,
    RIGHT_OP = 610,
    INC_OP = 611,
    DEC_OP = 612,
    LE_OP = 613,
    GE_OP = 614,
    EQ_OP = 615,
    NE_OP = 616,
    AND_OP = 617,
    OR_OP = 618,
    XOR_OP = 619,
    MUL_ASSIGN = 620,
    DIV_ASSIGN = 621,
    ADD_ASSIGN = 622,
    MOD_ASSIGN = 623,
    LEFT_ASSIGN = 624,
    RIGHT_ASSIGN = 625,
    AND_ASSIGN = 626,
    XOR_ASSIGN = 627,
    OR_ASSIGN = 628,
    SUB_ASSIGN = 629,
    LEFT_PAREN = 630,
    RIGHT_PAREN = 631,
    LEFT_BRACKET = 632,
    RIGHT_BRACKET = 633,
    LEFT_BRACE = 634,
    RIGHT_BRACE = 635,
    DOT = 636,
    COMMA = 637,
    COLON = 638,
    EQUAL = 639,
    SEMICOLON = 640,
    BANG = 641,
    DASH = 642,
    TILDE = 643,
    PLUS = 644,
    STAR = 645,
    SLASH = 646,
    PERCENT = 647,
    LEFT_ANGLE = 648,
    RIGHT_ANGLE = 649,
    VERTICAL_BAR = 650,
    CARET = 651,
    AMPERSAND = 652,
    QUESTION = 653,
    INVARIANT = 654,
    PRECISE = 655,
    HIGH_PRECISION = 656,
    MEDIUM_PRECISION = 657,
    LOW_PRECISION = 658,
    PRECISION = 659,
    PACKED = 660,
    RESOURCE = 661,
    SUPERP = 662
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 71 "MachineIndependent/glslang.y" /* yacc.c:355  */

    struct {
        glslang::TSourceLoc loc;
        union {
            glslang::TString *string;
            int i;
            unsigned int u;
            long long i64;
            unsigned long long u64;
            bool b;
            double d;
        };
        glslang::TSymbol* symbol;
    } lex;
    struct {
        glslang::TSourceLoc loc;
        glslang::TOperator op;
        union {
            TIntermNode* intermNode;
            glslang::TIntermNodePair nodePair;
            glslang::TIntermTyped* intermTypedNode;
            glslang::TAttributes* attributes;
        };
        union {
            glslang::TPublicType type;
            glslang::TFunction* function;
            glslang::TParameter param;
            glslang::TTypeLoc typeLine;
            glslang::TTypeList* typeList;
            glslang::TArraySizes* arraySizes;
            glslang::TIdentifierList* identifierList;
        };
        glslang::TArraySizes* typeParameters;
    } interm;

#line 576 "MachineIndependent/glslang_tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 107 "MachineIndependent/glslang.y" /* yacc.c:358  */


/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


#line 607 "MachineIndependent/glslang_tab.cpp" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  384
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   9348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  408
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  578
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  722

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   662

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
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
     405,   406,   407
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   302,   302,   308,   311,   315,   319,   322,   326,   330,
     334,   338,   342,   345,   349,   353,   356,   364,   367,   370,
     373,   376,   381,   389,   396,   403,   409,   413,   420,   423,
     429,   436,   446,   454,   459,   486,   494,   500,   504,   508,
     528,   529,   530,   531,   537,   538,   543,   548,   557,   558,
     563,   571,   572,   578,   587,   588,   593,   598,   603,   611,
     612,   620,   631,   632,   641,   642,   651,   652,   661,   662,
     670,   671,   679,   680,   688,   689,   689,   707,   708,   724,
     728,   732,   736,   741,   745,   749,   753,   757,   761,   765,
     772,   775,   786,   793,   798,   803,   811,   815,   819,   823,
     828,   833,   842,   842,   853,   857,   864,   871,   874,   881,
     889,   909,   932,   947,   972,   983,   993,  1003,  1013,  1022,
    1025,  1029,  1033,  1038,  1046,  1051,  1056,  1061,  1066,  1075,
    1086,  1113,  1122,  1129,  1136,  1147,  1156,  1166,  1178,  1187,
    1199,  1205,  1208,  1215,  1219,  1223,  1231,  1240,  1243,  1254,
    1257,  1260,  1264,  1268,  1272,  1276,  1282,  1286,  1298,  1312,
    1317,  1323,  1329,  1336,  1342,  1347,  1352,  1357,  1367,  1377,
    1387,  1397,  1406,  1418,  1422,  1427,  1432,  1437,  1442,  1447,
    1451,  1455,  1459,  1463,  1469,  1478,  1485,  1488,  1496,  1501,
    1511,  1516,  1524,  1528,  1538,  1541,  1547,  1553,  1560,  1570,
    1574,  1578,  1583,  1588,  1593,  1598,  1602,  1607,  1612,  1617,
    1622,  1627,  1632,  1637,  1642,  1647,  1651,  1656,  1661,  1666,
    1672,  1678,  1684,  1690,  1696,  1702,  1708,  1714,  1720,  1726,
    1732,  1738,  1743,  1748,  1753,  1758,  1763,  1768,  1774,  1780,
    1786,  1792,  1798,  1804,  1810,  1816,  1822,  1828,  1834,  1840,
    1846,  1852,  1858,  1864,  1870,  1876,  1882,  1888,  1894,  1900,
    1906,  1912,  1918,  1924,  1930,  1935,  1940,  1945,  1950,  1955,
    1960,  1965,  1970,  1975,  1980,  1985,  1990,  1996,  2002,  2008,
    2014,  2020,  2026,  2032,  2038,  2044,  2050,  2056,  2062,  2068,
    2074,  2080,  2086,  2092,  2098,  2104,  2110,  2116,  2122,  2128,
    2134,  2140,  2146,  2152,  2158,  2164,  2170,  2176,  2182,  2188,
    2194,  2200,  2206,  2212,  2218,  2224,  2230,  2236,  2242,  2248,
    2254,  2260,  2266,  2272,  2278,  2284,  2289,  2294,  2299,  2304,
    2309,  2314,  2319,  2324,  2329,  2334,  2339,  2344,  2349,  2354,
    2362,  2370,  2378,  2386,  2394,  2402,  2410,  2418,  2426,  2434,
    2442,  2450,  2458,  2463,  2468,  2473,  2478,  2483,  2488,  2493,
    2498,  2503,  2508,  2513,  2518,  2523,  2528,  2533,  2538,  2546,
    2554,  2559,  2564,  2569,  2577,  2582,  2587,  2592,  2600,  2605,
    2610,  2615,  2623,  2628,  2633,  2638,  2643,  2648,  2656,  2661,
    2669,  2674,  2682,  2687,  2695,  2700,  2708,  2713,  2721,  2726,
    2734,  2739,  2744,  2749,  2754,  2759,  2764,  2769,  2774,  2779,
    2784,  2789,  2794,  2799,  2804,  2809,  2817,  2822,  2827,  2832,
    2840,  2845,  2850,  2855,  2863,  2868,  2873,  2878,  2886,  2891,
    2896,  2901,  2909,  2914,  2919,  2924,  2932,  2937,  2942,  2947,
    2955,  2960,  2965,  2970,  2978,  2983,  2988,  2993,  3001,  3006,
    3011,  3016,  3024,  3029,  3034,  3039,  3047,  3052,  3057,  3062,
    3070,  3075,  3080,  3085,  3093,  3098,  3103,  3108,  3116,  3121,
    3126,  3131,  3139,  3144,  3149,  3155,  3161,  3167,  3173,  3182,
    3191,  3197,  3203,  3209,  3215,  3221,  3226,  3242,  3247,  3252,
    3260,  3260,  3271,  3271,  3281,  3284,  3297,  3319,  3346,  3350,
    3356,  3361,  3372,  3375,  3381,  3390,  3393,  3399,  3403,  3404,
    3410,  3411,  3412,  3413,  3414,  3415,  3416,  3420,  3421,  3425,
    3421,  3437,  3438,  3442,  3442,  3449,  3449,  3463,  3466,  3474,
    3482,  3493,  3494,  3498,  3501,  3507,  3514,  3518,  3526,  3530,
    3543,  3546,  3552,  3552,  3572,  3575,  3581,  3593,  3605,  3608,
    3614,  3614,  3629,  3629,  3645,  3645,  3666,  3669,  3675,  3678,
    3684,  3688,  3695,  3700,  3705,  3712,  3715,  3724,  3728,  3737,
    3740,  3743,  3751,  3751,  3773,  3779,  3782,  3787,  3790
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "VARYING", "FLOAT16_T",
  "FLOAT", "FLOAT32_T", "DOUBLE", "FLOAT64_T", "CONST", "BOOL", "INT",
  "UINT", "INT64_T", "UINT64_T", "INT32_T", "UINT32_T", "INT16_T",
  "UINT16_T", "INT8_T", "UINT8_T", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT",
  "SUBROUTINE", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4",
  "UVEC2", "UVEC3", "UVEC4", "I64VEC2", "I64VEC3", "I64VEC4", "U64VEC2",
  "U64VEC3", "U64VEC4", "I32VEC2", "I32VEC3", "I32VEC4", "U32VEC2",
  "U32VEC3", "U32VEC4", "I16VEC2", "I16VEC3", "I16VEC4", "U16VEC2",
  "U16VEC3", "U16VEC4", "I8VEC2", "I8VEC3", "I8VEC4", "U8VEC2", "U8VEC3",
  "U8VEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID",
  "IN", "OUT", "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED",
  "NONUNIFORM", "PAYLOADNV", "PAYLOADINNV", "HITATTRNV", "CALLDATANV",
  "CALLDATAINNV", "COHERENT", "VOLATILE", "RESTRICT", "READONLY",
  "WRITEONLY", "DEVICECOHERENT", "QUEUEFAMILYCOHERENT",
  "WORKGROUPCOHERENT", "SUBGROUPCOHERENT", "NONPRIVATE", "DVEC2", "DVEC3",
  "DVEC4", "DMAT2", "DMAT3", "DMAT4", "F16VEC2", "F16VEC3", "F16VEC4",
  "F16MAT2", "F16MAT3", "F16MAT4", "F32VEC2", "F32VEC3", "F32VEC4",
  "F32MAT2", "F32MAT3", "F32MAT4", "F64VEC2", "F64VEC3", "F64VEC4",
  "F64MAT2", "F64MAT3", "F64MAT4", "NOPERSPECTIVE", "FLAT", "SMOOTH",
  "LAYOUT", "EXPLICITINTERPAMD", "PERVERTEXNV", "PERPRIMITIVENV",
  "PERVIEWNV", "PERTASKNV", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2",
  "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3",
  "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3",
  "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "F32MAT2X2", "F32MAT2X3", "F32MAT2X4", "F32MAT3X2", "F32MAT3X3",
  "F32MAT3X4", "F32MAT4X2", "F32MAT4X3", "F32MAT4X4", "F64MAT2X2",
  "F64MAT2X3", "F64MAT2X4", "F64MAT3X2", "F64MAT3X3", "F64MAT3X4",
  "F64MAT4X2", "F64MAT4X3", "F64MAT4X4", "ATOMIC_UINT", "ACCSTRUCTNV",
  "FCOOPMATNV", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D",
  "ISAMPLERCUBE", "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW",
  "ISAMPLER2DRECT", "USAMPLER2DRECT", "SAMPLERBUFFER", "ISAMPLERBUFFER",
  "USAMPLERBUFFER", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLERCUBEARRAY", "USAMPLERCUBEARRAY", "SAMPLER2DMS", "ISAMPLER2DMS",
  "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "SAMPLEREXTERNAL2DY2YEXT",
  "F16SAMPLER1D", "F16SAMPLER2D", "F16SAMPLER3D", "F16SAMPLER2DRECT",
  "F16SAMPLERCUBE", "F16SAMPLER1DARRAY", "F16SAMPLER2DARRAY",
  "F16SAMPLERCUBEARRAY", "F16SAMPLERBUFFER", "F16SAMPLER2DMS",
  "F16SAMPLER2DMSARRAY", "F16SAMPLER1DSHADOW", "F16SAMPLER2DSHADOW",
  "F16SAMPLER1DARRAYSHADOW", "F16SAMPLER2DARRAYSHADOW",
  "F16SAMPLER2DRECTSHADOW", "F16SAMPLERCUBESHADOW",
  "F16SAMPLERCUBEARRAYSHADOW", "SAMPLER", "SAMPLERSHADOW", "TEXTURE1D",
  "TEXTURE2D", "TEXTURE3D", "TEXTURECUBE", "TEXTURE1DARRAY",
  "TEXTURE2DARRAY", "ITEXTURE1D", "ITEXTURE2D", "ITEXTURE3D",
  "ITEXTURECUBE", "ITEXTURE1DARRAY", "ITEXTURE2DARRAY", "UTEXTURE1D",
  "UTEXTURE2D", "UTEXTURE3D", "UTEXTURECUBE", "UTEXTURE1DARRAY",
  "UTEXTURE2DARRAY", "TEXTURE2DRECT", "ITEXTURE2DRECT", "UTEXTURE2DRECT",
  "TEXTUREBUFFER", "ITEXTUREBUFFER", "UTEXTUREBUFFER", "TEXTURECUBEARRAY",
  "ITEXTURECUBEARRAY", "UTEXTURECUBEARRAY", "TEXTURE2DMS", "ITEXTURE2DMS",
  "UTEXTURE2DMS", "TEXTURE2DMSARRAY", "ITEXTURE2DMSARRAY",
  "UTEXTURE2DMSARRAY", "F16TEXTURE1D", "F16TEXTURE2D", "F16TEXTURE3D",
  "F16TEXTURE2DRECT", "F16TEXTURECUBE", "F16TEXTURE1DARRAY",
  "F16TEXTURE2DARRAY", "F16TEXTURECUBEARRAY", "F16TEXTUREBUFFER",
  "F16TEXTURE2DMS", "F16TEXTURE2DMSARRAY", "SUBPASSINPUT",
  "SUBPASSINPUTMS", "ISUBPASSINPUT", "ISUBPASSINPUTMS", "USUBPASSINPUT",
  "USUBPASSINPUTMS", "F16SUBPASSINPUT", "F16SUBPASSINPUTMS", "IMAGE1D",
  "IIMAGE1D", "UIMAGE1D", "IMAGE2D", "IIMAGE2D", "UIMAGE2D", "IMAGE3D",
  "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT", "IIMAGE2DRECT", "UIMAGE2DRECT",
  "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "IMAGE1DARRAY", "IIMAGE1DARRAY", "UIMAGE1DARRAY",
  "IMAGE2DARRAY", "IIMAGE2DARRAY", "UIMAGE2DARRAY", "IMAGECUBEARRAY",
  "IIMAGECUBEARRAY", "UIMAGECUBEARRAY", "IMAGE2DMS", "IIMAGE2DMS",
  "UIMAGE2DMS", "IMAGE2DMSARRAY", "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY",
  "F16IMAGE1D", "F16IMAGE2D", "F16IMAGE3D", "F16IMAGE2DRECT",
  "F16IMAGECUBE", "F16IMAGE1DARRAY", "F16IMAGE2DARRAY",
  "F16IMAGECUBEARRAY", "F16IMAGEBUFFER", "F16IMAGE2DMS",
  "F16IMAGE2DMSARRAY", "STRUCT", "VOID", "WHILE", "IDENTIFIER",
  "TYPE_NAME", "FLOATCONSTANT", "DOUBLECONSTANT", "INT16CONSTANT",
  "UINT16CONSTANT", "INT32CONSTANT", "UINT32CONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "INT64CONSTANT", "UINT64CONSTANT", "BOOLCONSTANT",
  "FLOAT16CONSTANT", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE",
  "RIGHT_BRACE", "DOT", "COMMA", "COLON", "EQUAL", "SEMICOLON", "BANG",
  "DASH", "TILDE", "PLUS", "STAR", "SLASH", "PERCENT", "LEFT_ANGLE",
  "RIGHT_ANGLE", "VERTICAL_BAR", "CARET", "AMPERSAND", "QUESTION",
  "INVARIANT", "PRECISE", "HIGH_PRECISION", "MEDIUM_PRECISION",
  "LOW_PRECISION", "PRECISION", "PACKED", "RESOURCE", "SUPERP", "$accept",
  "variable_identifier", "primary_expression", "postfix_expression",
  "integer_expression", "function_call", "function_call_or_method",
  "function_call_generic", "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression", "$@1",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "block_structure", "$@2",
  "identifier_list", "function_prototype", "function_declarator",
  "function_header_with_parameters", "function_header",
  "parameter_declarator", "parameter_declaration",
  "parameter_type_specifier", "init_declarator_list", "single_declaration",
  "fully_specified_type", "invariant_qualifier", "interpolation_qualifier",
  "layout_qualifier", "layout_qualifier_id_list", "layout_qualifier_id",
  "precise_qualifier", "type_qualifier", "single_type_qualifier",
  "storage_qualifier", "non_uniform_qualifier", "type_name_list",
  "type_specifier", "array_specifier", "type_parameter_specifier_opt",
  "type_parameter_specifier", "type_parameter_specifier_list",
  "type_specifier_nonarray", "precision_qualifier", "struct_specifier",
  "$@3", "$@4", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "initializer",
  "initializer_list", "declaration_statement", "statement",
  "simple_statement", "compound_statement", "$@5", "$@6",
  "statement_no_new_scope", "statement_scoped", "$@7", "$@8",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_statement_nonattributed", "selection_rest_statement",
  "condition", "switch_statement", "switch_statement_nonattributed", "$@9",
  "switch_statement_list", "case_label", "iteration_statement",
  "iteration_statement_nonattributed", "$@10", "$@11", "$@12",
  "for_init_statement", "conditionopt", "for_rest_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "$@13", "attribute", "attribute_list",
  "single_attribute", YY_NULLPTR
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
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662
};
# endif

#define YYPACT_NINF -659

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-659)))

#define YYTABLE_NINF -524

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3535,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -331,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -324,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -319,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -256,  -659,  -314,  -351,  -309,  -306,  5942,
    -257,  -659,  -217,  -659,  -659,  -659,  -659,  4338,  -659,  -659,
    -659,  -659,  -241,  -659,  -659,   721,  -659,  -659,  -204,   -71,
    -219,  -659,  9007,  -349,  -659,  -659,  -215,  -659,  5942,  -659,
    -659,  -659,  5942,  -178,  -172,  -659,  -337,  -267,  -659,  -659,
    -659,  8237,  -207,  -659,  -659,  -659,  -659,  -341,  -659,  -211,
    -330,  -659,  -659,  5942,  -210,  6697,  -659,  -322,  1123,  -659,
    -659,  -659,  -659,  -207,  -328,  -659,  7082,  -304,  -659,  -163,
    -659,  -252,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,  -659,  8237,  8237,  8237,  -659,  -659,
    -659,  -659,  -659,  -659,  -303,  -659,  -659,  -659,  -196,  -299,
    8622,  -194,  -659,  8237,  -659,  -659,  -355,  -195,  -659,  -157,
    8237,  -659,   -71,  5942,  5942,  -155,  4739,  -659,  -659,  -659,
    -659,  -242,  -236,  -249,  -335,  -206,  -191,  -187,  -209,  -149,
    -150,  -333,  -162,  7467,  -659,  -170,  -168,  -659,  -154,  -153,
    -167,  7852,  -152,  8237,  -159,  -148,  -151,  -160,  -659,  -659,
    -274,  -659,  -659,  -251,  -659,  -351,  -147,  -144,  -659,  -659,
    -659,  -659,  1525,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,   -19,  -195,  7082,  -302,  7082,  -659,  -659,  7082,
    5942,  -659,  -115,  -659,  -659,  -659,  -292,  -659,  -659,  8237,
    -108,  -659,  -659,  8237,  -143,  -659,  -659,  -659,  8237,  -659,
    -659,  -659,  -659,  -659,  5140,  -155,  -207,  -250,  -659,  -659,
    -659,  8237,  8237,  8237,  8237,  8237,  8237,  8237,  8237,  8237,
    8237,  8237,  8237,  8237,  8237,  8237,  8237,  8237,  8237,  8237,
    -659,  -659,  -659,  -142,  -659,  -659,  1927,  -659,  8237,  -659,
    -659,  -245,  8237,  -226,  -659,  -659,  -106,  -659,  1927,  -659,
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    8237,  8237,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  7082,
    -659,  -238,  -659,  5541,  -659,  -659,  -141,  -140,  -659,  -659,
    -659,  -659,  -244,  -195,  -155,  -659,  -659,  -659,  -659,  -242,
    -242,  -236,  -236,  -249,  -249,  -249,  -249,  -335,  -335,  -206,
    -191,  -187,  -209,  -149,  -150,  8237,  -659,  -104,  3133,  -263,
    -659,  -260,  -659,  3937,  -136,  -297,  -659,  1927,  -659,  -659,
    -659,  -659,  6312,  -659,  -659,  -659,  -659,  -224,  -135,  -659,
    -659,  3937,  -138,  -659,  -140,   -97,  5942,  -132,  8237,  -133,
    -106,  -134,  -659,  -659,  8237,  8237,  -659,  -137,  -129,   224,
    -128,  2731,  -659,  -127,  -131,  2329,  -126,  -659,  -659,  -659,
    -659,  -255,  8237,  2329,  -138,  -659,  -659,  1927,  7082,  -659,
    -659,  -659,  -659,  -130,  -140,  -659,  -659,  1927,  -123,  -659,
    -659,  -659
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   157,   158,   202,   200,   203,   201,   204,   156,   215,
     205,   206,   213,   214,   211,   212,   209,   210,   207,   208,
     183,   231,   232,   233,   234,   235,   236,   249,   250,   251,
     246,   247,   248,   261,   262,   263,   243,   244,   245,   258,
     259,   260,   240,   241,   242,   255,   256,   257,   237,   238,
     239,   252,   253,   254,   216,   217,   218,   264,   265,   266,
     162,   160,   161,   159,   165,   163,   164,   166,   172,   185,
     168,   169,   167,   170,   171,   173,   179,   180,   181,   182,
     174,   175,   176,   177,   178,   219,   220,   221,   276,   277,
     278,   222,   223,   224,   288,   289,   290,   225,   226,   227,
     300,   301,   302,   228,   229,   230,   312,   313,   314,   134,
     133,   132,     0,   135,   136,   137,   138,   139,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   325,   324,   484,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   352,   353,   354,
     355,   356,   357,   359,   360,   361,   362,   363,   364,   366,
     367,   370,   371,   372,   374,   375,   337,   338,   358,   365,
     376,   378,   379,   380,   382,   383,   474,   475,   339,   340,
     341,   368,   342,   346,   347,   350,   373,   377,   381,   343,
     344,   348,   349,   369,   345,   351,   384,   385,   386,   388,
     390,   392,   394,   396,   400,   401,   402,   403,   404,   405,
     407,   408,   409,   410,   411,   412,   414,   416,   417,   418,
     420,   421,   398,   406,   413,   422,   424,   425,   426,   428,
     429,   387,   389,   391,   415,   393,   395,   397,   399,   419,
     423,   427,   476,   477,   480,   481,   482,   483,   478,   479,
     430,   432,   433,   434,   436,   437,   438,   440,   441,   442,
     444,   445,   446,   448,   449,   450,   452,   453,   454,   456,
     457,   458,   460,   461,   462,   464,   465,   466,   468,   469,
     470,   472,   473,   431,   435,   439,   443,   447,   455,   459,
     463,   451,   467,   471,     0,   199,   486,   571,   131,   146,
     487,   488,   489,     0,   570,     0,   572,     0,   108,   107,
       0,   119,   124,   153,   152,   150,   154,     0,   147,   149,
     155,   129,   195,   151,   485,     0,   567,   569,     0,     0,
       0,   492,     0,     0,    96,    93,     0,   106,     0,   115,
     109,   117,     0,   118,     0,    94,   125,     0,    99,   148,
     130,     0,   188,   194,     1,   568,   186,     0,   145,   143,
       0,   141,   490,     0,     0,     0,    97,     0,     0,   573,
     110,   114,   116,   112,   120,   111,     0,   126,   102,     0,
     100,     0,     2,    12,    13,    10,    11,     4,     5,     6,
       7,     8,     9,    15,    14,     0,     0,     0,    42,    41,
      43,    40,     3,    17,    36,    19,    24,    25,     0,     0,
      29,     0,   197,     0,    35,    33,     0,   189,   184,     0,
       0,   140,     0,     0,     0,     0,     0,   494,    95,   190,
      44,    48,    51,    54,    59,    62,    64,    66,    68,    70,
      72,    74,     0,     0,    98,     0,     0,   552,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   518,   527,   531,
      44,    77,    90,     0,   507,     0,   155,   129,   510,   529,
     509,   508,     0,   511,   512,   533,   513,   540,   514,   515,
     548,   516,     0,   113,     0,   121,     0,   502,   128,     0,
       0,   104,     0,   101,    37,    38,     0,    21,    22,     0,
       0,    27,    26,     0,   199,    30,    32,    39,     0,   196,
     187,    92,   144,   142,     0,     0,   500,     0,   498,   493,
     495,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,   191,   192,     0,   563,   562,     0,   554,     0,   566,
     564,     0,     0,     0,   547,   550,     0,   517,     0,    80,
      81,    83,    82,    85,    86,    87,    88,    89,    84,    79,
       0,     0,   532,   528,   530,   534,   541,   549,   123,     0,
     505,     0,   127,     0,   105,    16,     0,    23,    20,    31,
     198,   491,     0,   501,     0,   496,    45,    46,    47,    50,
      49,    52,    53,    57,    58,    55,    56,    60,    61,    63,
      65,    67,    69,    71,    73,     0,   193,     0,     0,     0,
     565,     0,   546,     0,   577,     0,   575,   519,    78,    91,
     122,   503,     0,   103,    18,   497,   499,     0,     0,   557,
     556,   559,   525,   542,   538,     0,     0,     0,     0,     0,
       0,     0,   504,   506,     0,     0,   558,     0,     0,   537,
       0,     0,   535,     0,     0,     0,     0,   574,   576,   520,
      76,     0,   560,     0,   525,   524,   526,   544,     0,   522,
     551,   521,   578,     0,   561,   555,   536,   545,     0,   539,
     553,   543
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,  -659,
    -659,  -659,  -364,  -659,  -389,  -385,  -457,  -384,  -310,  -307,
    -305,  -308,  -301,  -298,  -659,  -386,  -659,  -390,  -659,  -415,
    -418,     1,  -659,  -659,  -659,     2,  -659,  -659,  -659,  -110,
    -105,  -107,  -659,  -659,  -628,  -659,  -659,  -659,  -659,  -188,
    -659,  -336,  -343,  -659,     6,  -659,     0,  -334,  -659,  -659,
    -659,  -659,   -67,  -659,  -659,  -659,  -431,  -437,  -277,  -350,
    -501,  -659,  -375,  -488,  -658,  -414,  -659,  -659,  -428,  -426,
    -659,  -659,   -87,  -568,  -368,  -659,  -231,  -659,  -388,  -659,
    -230,  -659,  -659,  -659,  -659,  -228,  -659,  -659,  -659,  -659,
    -659,  -659,  -659,  -659,   -70,  -659,  -659,  -659,  -659,  -394
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   432,   433,   434,   616,   435,   436,   437,   438,   439,
     440,   441,   490,   443,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   491,   645,   492,   600,   493,
     542,   494,   335,   520,   411,   495,   337,   338,   339,   369,
     370,   371,   340,   341,   342,   343,   344,   345,   390,   391,
     346,   347,   348,   349,   444,   387,   445,   397,   382,   383,
     446,   352,   353,   354,   453,   393,   456,   457,   547,   548,
     518,   611,   498,   499,   500,   501,   588,   681,   710,   689,
     690,   691,   711,   502,   503,   504,   505,   692,   677,   506,
     507,   693,   718,   508,   509,   510,   653,   576,   648,   671,
     687,   688,   511,   355,   356,   357,   366,   512,   655,   656
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     351,   334,   336,   372,   379,   477,   350,   478,   479,   472,
     388,   482,   526,   608,   604,   610,   517,   442,   612,   550,
     657,   360,   544,   558,   559,   675,   363,   538,   395,   379,
     569,   460,   372,   706,   365,   448,   396,   709,   405,   539,
     395,   449,   407,   675,   358,   709,   451,   406,   447,   395,
     535,   359,   452,   527,   528,   473,   514,   454,   560,   561,
     361,   524,   525,   474,   541,   570,   581,   367,   583,   513,
     515,   364,   -34,   473,   529,   473,   368,   532,   530,   537,
     519,   679,   609,   533,   615,   680,   460,   573,   647,   613,
     601,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     598,   633,   634,   635,   636,   556,   557,   550,   660,   460,
     599,   379,   408,   672,   617,   409,   673,   454,   410,   601,
     454,   713,   601,   376,   517,   374,   517,   601,   375,   517,
     522,   601,   624,   523,   602,   625,   386,   601,   624,   717,
     650,   665,   661,   619,   662,   330,   331,   332,   551,   552,
     553,   554,   381,   555,   562,   563,   601,   652,   601,   684,
     392,   683,   403,   649,   398,   629,   630,   651,   404,   604,
     395,   631,   632,   450,   620,   458,   550,   521,   637,   638,
     531,   536,   473,   540,   454,   546,   566,   626,   627,   628,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   564,   719,   454,   565,
     658,   659,   623,   567,   568,   574,   571,   575,   579,   517,
     587,   577,   578,   582,   584,   614,   586,   585,   -35,   604,
     667,   -33,   618,   -28,   654,   668,   646,   664,   674,   678,
     685,  -523,   601,   694,   695,   697,   699,   703,   702,   704,
     712,   487,   707,   708,   639,   720,   674,   721,   640,   642,
     696,   641,   401,   400,   543,   402,   362,   643,   622,   389,
     701,   644,   517,   669,   666,   715,   705,   454,   716,   399,
     670,   605,   606,   686,   607,   385,   698,   714,     0,     0,
       0,     0,   541,     0,   700,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   460,     0,     0,   676,   517,     0,
     485,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   379,     0,   676,     0,     0,     0,   373,
       0,     0,     0,     0,     0,   350,     0,   380,     0,     0,
       0,     0,     0,   350,     0,   351,   334,   336,     0,     0,
       0,   350,   394,     0,     0,     0,     0,     0,   373,     0,
       0,     0,   373,     0,   350,     0,     0,     0,   350,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,     0,     0,     0,     0,   497,   350,
       0,     0,     0,     0,   496,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,   545,     0,   455,     0,     0,   350,
     350,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   497,     0,     0,     0,     0,     0,   496,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,     0,     0,     0,     0,     0,   350,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,     0,     0,     0,     0,     0,
     350,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   497,     0,     0,     0,
       0,     0,   496,     0,     0,     0,     0,     0,   497,     0,
       0,     0,     0,     0,   496,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,     0,     0,     0,     0,     0,   350,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   497,     0,
       0,     0,     0,   497,   496,     0,     0,   497,     0,   496,
       0,     0,     0,   496,     0,     0,     0,     0,     0,     0,
       0,   497,     0,     0,     0,     0,   380,   496,     0,     0,
       0,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,   497,     0,     0,     0,   497,     0,   496,     0,     0,
       0,   496,     0,   497,     0,     0,     0,   497,     0,   496,
       0,     0,     0,   496,     0,     0,     0,   497,     0,     0,
       0,   384,     0,   496,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,   326,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,   333,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   475,   476,   477,     0,   478,
     479,   480,   481,   482,   483,   484,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   485,   412,   326,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,     0,     0,   425,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   427,     0,
     486,     0,   487,   488,     0,     0,     0,     0,   489,   428,
     429,   430,   431,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,   329,   330,   331,   332,   333,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,   475,   476,   477,
       0,   478,   479,   480,   481,   482,   483,   484,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   485,   412,   326,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,     0,
       0,   425,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     427,     0,   486,     0,   487,   603,     0,     0,     0,     0,
     489,   428,   429,   430,   431,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   328,   329,   330,   331,   332,   333,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   475,
     476,   477,     0,   478,   479,   480,   481,   482,   483,   484,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   485,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,   486,     0,   487,     0,     0,     0,
       0,     0,   489,   428,   429,   430,   431,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,   329,   330,   331,
     332,   333,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   475,   476,   477,     0,   478,   479,   480,   481,   482,
     483,   484,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   485,   412,
     326,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,     0,     0,   425,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   427,     0,   486,     0,   398,     0,
       0,     0,     0,     0,   489,   428,   429,   430,   431,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   328,   329,
     330,   331,   332,   333,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,   475,   476,   477,     0,   478,   479,   480,
     481,   482,   483,   484,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     485,   412,   326,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,     0,     0,   425,   426,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     0,   486,     0,
       0,     0,     0,     0,     0,     0,   489,   428,   429,   430,
     431,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,   333,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,     0,   412,   326,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,     0,     0,   425,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   427,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   489,   428,
     429,   430,   431,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,   329,   330,   331,   332,   333,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,     0,     0,   326,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     327,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   328,   329,   330,   331,   332,   333,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   428,   429,   430,   431,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,   329,   330,   331,
     332,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,     0,   377,   326,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   378,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   328,   329,   330,
     331,   332,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,     0,     0,
     326,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   549,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   328,   329,
     330,   331,   332,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,     0,
       0,   326,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     621,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   328,
     329,   330,   331,   332,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,   326,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   663,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,   326,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       6,     7,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,   328,   329,   330,   331,   332,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,   412,   326,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,     0,     0,   425,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,     0,     0,
       0,   516,   682,     0,     0,     0,     0,     0,   428,   429,
     430,   431,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,     0,   459,     0,     0,     0,     0,
       0,     0,     0,   428,   429,   430,   431,     3,     4,     5,
       6,     7,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,   412,   326,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,     0,     0,   425,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,     0,     0,
       0,   516,     0,     0,     0,     0,     0,     0,   428,   429,
     430,   431,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,     0,   572,     0,     0,     0,     0,
       0,     0,     0,   428,   429,   430,   431,     3,     4,     5,
       6,     7,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,   412,   326,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,     0,     0,   425,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   580,   428,   429,
     430,   431,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   428,   429,   430,   431,     3,     4,     5,
       6,     7,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     534,     0,   412,   326,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,     0,     0,   425,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   428,   429,
     430,   431,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,     0,   326
};

static const yytype_int16 yycheck[] =
{
       0,     0,     0,   339,   347,    24,     0,    26,    27,   395,
      81,    30,   427,   514,   502,   516,   406,   381,   519,   456,
     588,   340,   453,   358,   359,   653,   340,   382,   377,   372,
     363,   395,   368,   691,   385,   376,   385,   695,   375,   394,
     377,   382,   376,   671,   375,   703,   376,   384,   382,   377,
     440,   375,   382,   356,   357,   377,   384,   393,   393,   394,
     379,   425,   426,   385,   450,   398,   481,   376,   483,   403,
     404,   385,   375,   377,   377,   377,   382,   376,   381,   443,
     384,   378,   384,   382,   376,   382,   450,   473,   576,   520,
     382,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   558,   559,   560,   561,   354,   355,   544,   609,   473,
     384,   454,   379,   376,   529,   382,   376,   453,   385,   382,
     456,   376,   382,   340,   514,   382,   516,   382,   385,   519,
     382,   382,   382,   385,   385,   385,   340,   382,   382,   707,
     385,   385,   380,   533,   382,   401,   402,   403,   390,   391,
     392,   387,   393,   389,   360,   361,   382,   383,   382,   383,
     379,   662,   340,   578,   379,   554,   555,   582,   340,   657,
     377,   556,   557,   384,   538,   385,   613,   340,   562,   563,
     376,   375,   377,   340,   520,   340,   395,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   397,   708,   544,   396,
     600,   601,   546,   362,   364,   385,   378,   385,   385,   609,
     380,   375,   375,   375,   383,   340,   377,   375,   375,   717,
     645,   375,   340,   376,   340,   339,   378,   378,   653,   375,
     375,   379,   382,   340,   376,   378,   380,   376,   385,    25,
     376,   379,   379,   384,   564,   385,   671,   380,   565,   567,
     678,   566,   372,   368,   452,   372,   333,   568,   545,   340,
     685,   569,   662,   648,   624,   703,   690,   613,   704,   366,
     648,   512,   512,   671,   512,   355,   680,   702,    -1,    -1,
      -1,    -1,   678,    -1,   684,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   678,    -1,    -1,   653,   708,    -1,
     339,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   676,    -1,   671,    -1,    -1,    -1,   339,
      -1,    -1,    -1,    -1,    -1,   339,    -1,   347,    -1,    -1,
      -1,    -1,    -1,   347,    -1,   355,   355,   355,    -1,    -1,
      -1,   355,   362,    -1,    -1,    -1,    -1,    -1,   368,    -1,
      -1,    -1,   372,    -1,   368,    -1,    -1,    -1,   372,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   393,    -1,    -1,    -1,    -1,   398,   393,
      -1,    -1,    -1,    -1,   398,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   453,   454,    -1,   456,    -1,    -1,   453,
     454,    -1,   456,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   502,    -1,    -1,    -1,    -1,    -1,   502,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     520,    -1,    -1,    -1,    -1,    -1,   520,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   544,    -1,    -1,    -1,    -1,    -1,
     544,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   576,    -1,    -1,    -1,
      -1,    -1,   576,    -1,    -1,    -1,    -1,    -1,   588,    -1,
      -1,    -1,    -1,    -1,   588,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   613,    -1,    -1,    -1,    -1,    -1,   613,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   648,    -1,
      -1,    -1,    -1,   653,   648,    -1,    -1,   657,    -1,   653,
      -1,    -1,    -1,   657,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   671,    -1,    -1,    -1,    -1,   676,   671,    -1,    -1,
      -1,    -1,   676,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   691,    -1,    -1,    -1,   695,    -1,   691,    -1,    -1,
      -1,   695,    -1,   703,    -1,    -1,    -1,   707,    -1,   703,
      -1,    -1,    -1,   707,    -1,    -1,    -1,   717,    -1,    -1,
      -1,     0,    -1,   717,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      -1,    -1,   341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   385,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     399,   400,   401,   402,   403,   404,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,    -1,    -1,   356,
     357,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
     377,    -1,   379,   380,    -1,    -1,    -1,    -1,   385,   386,
     387,   388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   399,   400,   401,   402,   403,   404,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,    -1,
      -1,   356,   357,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     375,    -1,   377,    -1,   379,   380,    -1,    -1,    -1,    -1,
     385,   386,   387,   388,   389,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   399,   400,   401,   402,   403,   404,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,   377,    -1,   379,    -1,    -1,    -1,
      -1,    -1,   385,   386,   387,   388,   389,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,
     403,   404,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,    -1,    -1,   356,   357,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   375,    -1,   377,    -1,   379,    -1,
      -1,    -1,    -1,    -1,   385,   386,   387,   388,   389,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,
     401,   402,   403,   404,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,    -1,    -1,   356,   357,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,   377,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   385,   386,   387,   388,
     389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     399,   400,   401,   402,   403,   404,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,    -1,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,    -1,    -1,   356,
     357,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,   386,
     387,   388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   399,   400,   401,   402,   403,   404,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
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
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    -1,    -1,   341,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     385,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   399,   400,   401,   402,   403,   404,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,
     403,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    -1,   340,   341,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   385,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,
     402,   403,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,    -1,    -1,
     341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,
     401,   402,   403,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    -1,
      -1,   341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,
     400,   401,   402,   403,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      -1,    -1,   341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   380,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     399,   400,   401,   402,   403,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,   341,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   400,   401,   402,   403,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    -1,    -1,   356,   357,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,   379,   380,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    -1,    -1,   356,   357,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    -1,    -1,   356,   357,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,   386,   387,
     388,   389,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    -1,    -1,   356,   357,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,    -1,   341
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   341,   385,   399,   400,
     401,   402,   403,   404,   439,   440,   443,   444,   445,   446,
     450,   451,   452,   453,   454,   455,   458,   459,   460,   461,
     462,   464,   469,   470,   471,   511,   512,   513,   375,   375,
     340,   379,   470,   340,   385,   385,   514,   376,   382,   447,
     448,   449,   459,   464,   382,   385,   340,   340,   385,   460,
     464,   393,   466,   467,     0,   512,   340,   463,    81,   340,
     456,   457,   379,   473,   464,   377,   385,   465,   379,   490,
     448,   447,   449,   340,   340,   375,   384,   465,   379,   382,
     385,   442,   340,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   356,   357,   375,   386,   387,
     388,   389,   409,   410,   411,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   462,   464,   468,   465,   376,   382,
     384,   376,   382,   472,   459,   464,   474,   475,   385,   378,
     420,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   377,   385,    22,    23,    24,    26,    27,
      28,    29,    30,    31,    32,   339,   377,   379,   380,   385,
     420,   433,   435,   437,   439,   443,   462,   464,   480,   481,
     482,   483,   491,   492,   493,   494,   497,   498,   501,   502,
     503,   510,   515,   465,   384,   465,   379,   435,   478,   384,
     441,   340,   382,   385,   420,   420,   437,   356,   357,   377,
     381,   376,   376,   382,   338,   435,   375,   420,   382,   394,
     340,   433,   438,   457,   474,   464,   340,   476,   477,   380,
     475,   390,   391,   392,   387,   389,   354,   355,   358,   359,
     393,   394,   360,   361,   397,   396,   395,   362,   364,   363,
     398,   378,   378,   433,   385,   385,   505,   375,   375,   385,
     385,   437,   375,   437,   383,   375,   377,   380,   484,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   384,
     436,   382,   385,   380,   481,   494,   498,   503,   478,   384,
     478,   479,   478,   474,   340,   376,   412,   437,   340,   435,
     420,   380,   476,   465,   382,   385,   420,   420,   420,   422,
     422,   423,   423,   424,   424,   424,   424,   425,   425,   426,
     427,   428,   429,   430,   431,   434,   378,   481,   506,   437,
     385,   437,   383,   504,   340,   516,   517,   491,   435,   435,
     478,   380,   382,   380,   378,   385,   477,   437,   339,   480,
     492,   507,   376,   376,   437,   452,   459,   496,   375,   378,
     382,   485,   380,   478,   383,   375,   496,   508,   509,   487,
     488,   489,   495,   499,   340,   376,   438,   378,   517,   380,
     435,   437,   385,   376,    25,   483,   482,   379,   384,   482,
     486,   490,   376,   376,   437,   486,   487,   491,   500,   478,
     385,   380
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   408,   409,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   411,   411,   411,
     411,   411,   411,   412,   413,   414,   415,   415,   416,   416,
     417,   417,   418,   419,   419,   419,   420,   420,   420,   420,
     421,   421,   421,   421,   422,   422,   422,   422,   423,   423,
     423,   424,   424,   424,   425,   425,   425,   425,   425,   426,
     426,   426,   427,   427,   428,   428,   429,   429,   430,   430,
     431,   431,   432,   432,   433,   434,   433,   435,   435,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     437,   437,   438,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   441,   440,   442,   442,   443,   444,   444,   445,
     445,   446,   447,   447,   448,   448,   448,   448,   449,   450,
     450,   450,   450,   450,   451,   451,   451,   451,   451,   452,
     452,   453,   454,   454,   454,   454,   454,   454,   454,   454,
     455,   456,   456,   457,   457,   457,   458,   459,   459,   460,
     460,   460,   460,   460,   460,   460,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   462,   463,   463,   464,   464,
     465,   465,   465,   465,   466,   466,   467,   468,   468,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   470,   470,   470,
     472,   471,   473,   471,   474,   474,   475,   475,   476,   476,
     477,   477,   478,   478,   478,   479,   479,   480,   481,   481,
     482,   482,   482,   482,   482,   482,   482,   483,   484,   485,
     483,   486,   486,   488,   487,   489,   487,   490,   490,   491,
     491,   492,   492,   493,   493,   494,   495,   495,   496,   496,
     497,   497,   499,   498,   500,   500,   501,   501,   502,   502,
     504,   503,   505,   503,   506,   503,   507,   507,   508,   508,
     509,   509,   510,   510,   510,   510,   510,   511,   511,   512,
     512,   512,   514,   513,   515,   516,   516,   517,   517
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     4,     1,
       3,     2,     2,     1,     1,     1,     2,     2,     2,     1,
       2,     3,     2,     1,     1,     1,     1,     2,     2,     2,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     2,     4,     2,     3,     4,     2,
       3,     4,     0,     6,     2,     3,     2,     1,     1,     2,
       3,     3,     2,     3,     2,     1,     2,     1,     1,     1,
       3,     4,     6,     5,     1,     2,     3,     5,     4,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     1,     3,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     1,     3,     2,     3,
       2,     3,     3,     4,     1,     0,     3,     1,     3,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     5,     1,     2,     3,     4,     1,     3,
       1,     2,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     0,
       5,     1,     1,     0,     2,     0,     2,     2,     3,     1,
       2,     1,     2,     1,     2,     5,     3,     1,     1,     4,
       1,     2,     0,     8,     0,     1,     3,     2,     1,     2,
       0,     6,     0,     8,     0,     7,     1,     1,     1,     0,
       2,     3,     2,     2,     2,     3,     2,     1,     2,     1,
       1,     1,     0,     3,     5,     1,     3,     1,     4
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
      yyerror (pParseContext, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (pParseContext);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, glslang::TParseContext* pParseContext)
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
                                              , pParseContext);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pParseContext); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
{
  YYUSE (yyvaluep);
  YYUSE (pParseContext);
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
yyparse (glslang::TParseContext* pParseContext)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex (&yylval, parseContext);
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 302 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[0].lex).loc, (yyvsp[0].lex).symbol, (yyvsp[0].lex).string);
    }
#line 4159 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 308 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4167 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 311 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4176 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 315 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4185 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 319 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4193 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 322 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4202 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 326 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 4211 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 330 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 4220 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 334 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4229 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 338 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4238 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 342 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 4246 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 345 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 4255 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 349 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
    }
#line 4264 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 353 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 4272 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 356 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 4282 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 364 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4290 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 367 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 4298 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 370 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4306 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 373 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 4314 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 376 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4324 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 381 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4334 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 389 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.integerCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4343 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 396 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 4352 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 403 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4360 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 409 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4369 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 413 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4378 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 420 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4386 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 423 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4394 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 429 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-1].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-1].interm).function;
        (yyval.interm).intermNode = (yyvsp[0].interm.intermTypedNode);
    }
#line 4406 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 436 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-2].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-2].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
    }
#line 4418 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 446 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4426 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 454 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4436 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 459 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
            (yyval.interm).intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = (yyvsp[0].interm.intermTypedNode)->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                (yyval.interm).function = function;
            } else
                parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ((yyval.interm).function == 0) {
            // error recover
            TString* empty = NewPoolTString("");
            (yyval.interm).function = new TFunction(empty, TType(EbtVoid), EOpNull);
        }
    }
#line 4468 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 486 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4478 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 494 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 4489 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 500 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4498 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 504 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4507 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 508 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm).op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch((yyvsp[-1].interm).op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].interm).loc, errorOp, (yyvsp[-1].interm).op, (yyvsp[0].interm.intermTypedNode));
        } else {
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
            if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
                (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
        }
    }
#line 4528 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 528 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 4534 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 529 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 4540 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 530 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 4546 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 531 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 4553 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 537 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4559 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 538 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4569 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 543 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4579 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 548 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4590 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 557 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4596 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 558 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4606 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 563 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4616 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 571 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4622 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 572 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4633 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 578 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4644 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 587 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4650 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 588 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4660 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 593 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4670 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 598 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4680 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 603 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4690 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 611 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4696 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 612 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4709 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 620 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4722 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 631 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4728 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 632 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4739 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 641 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4745 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 642 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4756 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 651 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4762 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 652 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4773 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 661 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4779 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 662 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4789 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 670 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4795 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 671 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4805 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 679 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4811 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 680 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4821 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 688 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4827 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 689 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 4835 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 692 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-4].lex).loc, "?", (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[-5].interm.intermTypedNode), (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-4].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-4].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 4852 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 707 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4858 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 708 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.storage16BitAssignmentCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addAssign((yyvsp[-1].interm).op, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].interm).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
        }
    }
#line 4876 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 724 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 4885 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 728 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 4894 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 732 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 4903 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 736 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 4913 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 741 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 4922 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 745 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 4931 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 749 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 4940 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 753 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 4949 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 757 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 4958 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 761 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 4967 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 765 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 4976 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 772 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4984 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 775 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 4997 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 786 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5006 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 793 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 5016 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 798 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 5026 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 803 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 5039 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 811 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
        (yyval.interm.intermNode) = 0;
    }
#line 5048 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 815 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5057 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 819 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    }
#line 5066 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 823 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 5076 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 828 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5086 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 833 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).shaderQualifiers);
        (yyvsp[-1].interm.identifierList)->push_back((yyvsp[-2].lex).string);
        parseContext.addQualifierToExisting((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 5097 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 842 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 5103 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 842 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 5117 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 853 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5126 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 857 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5135 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 864 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 5144 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 871 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5152 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 874 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5160 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 881 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 5173 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 889 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ((yyvsp[0].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[-1].lex).loc, "cannot be an argument type except for '(void)'", "void", "");
            delete (yyvsp[0].interm).param.type;
        } else {
            // Add the parameter
            (yyval.interm.function) = (yyvsp[-2].interm.function);
            (yyvsp[-2].interm.function)->addParameter((yyvsp[0].interm).param);
        }
    }
#line 5195 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 909 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.type).qualifier.storage != EvqGlobal && (yyvsp[-2].interm.type).qualifier.storage != EvqTemporary) {
            parseContext.error((yyvsp[-1].lex).loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString((yyvsp[-2].interm.type).qualifier.storage), "");
        }
        if ((yyvsp[-2].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type((yyvsp[-2].interm.type));

        // Potentially rename shader entry point function.  No-op most of the time.
        parseContext.renameShaderFunction((yyvsp[-1].lex).string);

        // Make the function
        function = new TFunction((yyvsp[-1].lex).string, type);
        (yyval.interm.function) = function;
    }
#line 5219 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 932 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-1].interm.type).loc, *(yyvsp[-1].interm.type).arraySizes);
        }
        if ((yyvsp[-1].interm.type).basicType == EbtVoid) {
            parseContext.error((yyvsp[0].lex).loc, "illegal use of type 'void'", (yyvsp[0].lex).string->c_str(), "");
        }
        parseContext.reservedErrorCheck((yyvsp[0].lex).loc, *(yyvsp[0].lex).string);

        TParameter param = {(yyvsp[0].lex).string, new TType((yyvsp[-1].interm.type))};
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).param = param;
    }
#line 5239 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 947 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }
        TType* type = new TType((yyvsp[-2].interm.type));
        type->transferArraySizes((yyvsp[0].interm).arraySizes);
        type->copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);

        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, type->getArraySizes());
        parseContext.arraySizeRequiredCheck((yyvsp[0].interm).loc, *(yyvsp[0].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string);

        TParameter param = { (yyvsp[-1].lex).string, type };

        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).param = param;
    }
#line 5263 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 972 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 5279 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 983 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5291 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 993 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 5306 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1003 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5318 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1013 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 5329 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1022 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 5337 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1025 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
    }
#line 5346 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1029 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
    }
#line 5355 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1033 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5365 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1038 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5375 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1046 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 5385 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1051 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
    }
#line 5395 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1056 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
    }
#line 5405 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1061 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5415 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1066 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5425 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1075 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    }
#line 5441 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1086 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.globalQualifierTypeCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, (yyvsp[0].interm.type));

        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[0].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).qualifier))
            (yyvsp[0].interm.type).arraySizes = nullptr;

        parseContext.checkNoShaderLayouts((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        (yyvsp[0].interm.type).shaderQualifiers.merge((yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyvsp[-1].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).basicType, (yyvsp[0].interm.type).qualifier);

        (yyval.interm.type) = (yyvsp[0].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    }
#line 5470 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1113 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 5481 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1122 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 5493 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1129 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 5505 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1136 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "noperspective");
#ifdef NV_EXTENSIONS
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_shader_noperspective_interpolation, "noperspective");
#else
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "noperspective");
#endif
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
#line 5521 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1147 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    }
#line 5535 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1156 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexNV = true;
#endif
    }
#line 5550 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1166 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshNVMask), "perprimitiveNV");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_NV_mesh_shader, "perprimitiveNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
#endif
    }
#line 5567 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1178 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perviewNV");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangMeshNV, "perviewNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perViewNV = true;
#endif
    }
#line 5581 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1187 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskNVMask | EShLangMeshNVMask), "taskNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perTaskNV = true;
#endif
    }
#line 5595 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1199 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 5603 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1205 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5611 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1208 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5621 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1215 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 5630 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1219 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 5639 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1223 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 5649 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1231 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 5660 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1240 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5668 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1243 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5681 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1254 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5689 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1257 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5697 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1260 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5706 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1264 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5715 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1268 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5724 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1272 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5733 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1276 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5741 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1282 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 5750 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1286 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangVertex, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "attribute");

        parseContext.globalCheck((yyvsp[0].lex).loc, "attribute");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 5767 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1298 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "varying");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "varying");

        parseContext.globalCheck((yyvsp[0].lex).loc, "varying");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).qualifier.storage = EvqVaryingOut;
        else
            (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 5786 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1312 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 5796 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1317 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 5807 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1323 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 5818 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1329 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 5830 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1336 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 5841 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1342 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 5851 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1347 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 5861 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1352 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 5871 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1357 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectNVMask | EShLangClosestHitNVMask
            | EShLangAnyHitNVMask), "hitAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttrNV;
#endif
    }
#line 5886 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1367 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenNVMask | EShLangClosestHitNVMask |
            EShLangAnyHitNVMask | EShLangMissNVMask), "rayPayloadNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadNV;
#endif
    }
#line 5901 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1377 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitNVMask |
            EShLangAnyHitNVMask | EShLangMissNVMask), "rayPayloadInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadInNV;
#endif
    }
#line 5916 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 1387 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenNVMask |
            EShLangClosestHitNVMask | EShLangMissNVMask | EShLangCallableNVMask), "callableDataNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataNV;
#endif
    }
#line 5931 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1397 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableNVMask), "callableDataInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataInNV;
#endif
    }
#line 5945 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1406 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 310, 0, "shared");
#ifdef NV_EXTENSIONS
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangComputeMask | EShLangMeshNVMask | EShLangTaskNVMask), "shared");
#else
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangCompute, "shared");
#endif
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
#line 5962 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1418 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 5971 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1422 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "devicecoherent");
        (yyval.interm.type).qualifier.devicecoherent = true;
    }
#line 5981 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1427 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "queuefamilycoherent");
        (yyval.interm.type).qualifier.queuefamilycoherent = true;
    }
#line 5991 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1432 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "workgroupcoherent");
        (yyval.interm.type).qualifier.workgroupcoherent = true;
    }
#line 6001 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1437 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "subgroupcoherent");
        (yyval.interm.type).qualifier.subgroupcoherent = true;
    }
#line 6011 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 1442 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "nonprivate");
        (yyval.interm.type).qualifier.nonprivate = true;
    }
#line 6021 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 1447 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 6030 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 1451 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 6039 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1455 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 6048 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1459 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 6057 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1463 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 6068 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1469 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 6079 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 1478 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nonUniform = true;
    }
#line 6088 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 1485 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // TODO
    }
#line 6096 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1488 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 6106 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 1496 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[0].interm.typeParameters);
    }
#line 6116 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1501 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes);
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[-1].interm.typeParameters);
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
    }
#line 6128 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 1511 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6138 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 1516 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6151 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 1524 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6160 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1528 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6172 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1538 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[0].interm.typeParameters);
    }
#line 6180 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1541 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = 0;
    }
#line 6188 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1547 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[-1].interm.typeParameters);
    }
#line 6196 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1553 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter");
        (yyval.interm.typeParameters)->addInnerSize(size);
    }
#line 6208 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1560 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[-2].interm.typeParameters);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter");
        (yyval.interm.typeParameters)->addInnerSize(size);
    }
#line 6220 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1570 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 6229 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 1574 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6238 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 1578 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6248 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1583 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "float16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
    }
#line 6258 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1588 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6268 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 1593 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6278 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 1598 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6287 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1602 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6297 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1607 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
    }
#line 6307 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1612 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
    }
#line 6317 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1617 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
    }
#line 6327 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1622 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
    }
#line 6337 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 1627 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6347 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1632 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6357 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 1637 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 6367 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 1642 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 6377 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1647 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 6386 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1651 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6396 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 1656 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6406 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1661 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6416 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 1666 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6427 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 1672 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6438 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1678 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6449 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1684 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 6460 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1690 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 6471 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1696 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 6482 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1702 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6493 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 1708 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6504 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 1714 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6515 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1720 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6526 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1726 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6537 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1732 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6548 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1738 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 6558 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1743 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 6568 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 1748 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 6578 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1753 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6588 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1758 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6598 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1763 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6608 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 1768 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(2);
    }
#line 6619 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1774 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(3);
    }
#line 6630 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1780 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(4);
    }
#line 6641 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 1786 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
    }
#line 6652 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 1792 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
    }
#line 6663 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1798 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
    }
#line 6674 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1804 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6685 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1810 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6696 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1816 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6707 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 1822 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 6718 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1828 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 6729 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1834 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 6740 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 1840 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6751 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1846 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6762 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1852 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6773 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1858 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(2);
    }
#line 6784 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1864 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(3);
    }
#line 6795 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 1870 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(4);
    }
#line 6806 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1876 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
    }
#line 6817 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 1882 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
    }
#line 6828 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 1888 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
    }
#line 6839 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 1894 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6850 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1900 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6861 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1906 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6872 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1912 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 6883 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1918 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 6894 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 1924 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 6905 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1930 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6915 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 1935 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6925 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 1940 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 6935 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1945 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6945 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 1950 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 6955 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1955 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 6965 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 1960 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 6975 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 1965 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6985 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 1970 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 6995 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 1975 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7005 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 1980 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7015 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 1985 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7025 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1990 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7036 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1996 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7047 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 2002 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7058 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 2008 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7069 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 2014 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7080 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 2020 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7091 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 2026 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7102 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 2032 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7113 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 2038 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7124 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 2044 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7135 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 2050 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7146 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 2056 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7157 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 2062 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7168 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 2068 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7179 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 2074 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7190 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 2080 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7201 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 2086 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7212 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 2092 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7223 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 2098 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7234 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 2104 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7245 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 2110 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7256 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 2116 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7267 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 2122 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7278 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 2128 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7289 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 2134 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7300 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 2140 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7311 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 2146 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7322 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 2152 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7333 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 2158 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7344 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 2164 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7355 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 306:
#line 2170 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7366 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 2176 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7377 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 2182 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7388 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 2188 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7399 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 2194 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7410 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 2200 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7421 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 2206 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7432 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 2212 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7443 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 2218 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7454 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 2224 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7465 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 2230 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7476 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 2236 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7487 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 2242 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7498 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 2248 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7509 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 2254 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7520 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 2260 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7531 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 2266 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7542 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 2272 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7553 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 324:
#line 2278 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStructNV;
#endif
    }
#line 7564 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 2284 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 7574 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 2289 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 7584 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 2294 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 7594 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 328:
#line 2299 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 7604 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 2304 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 7614 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 2309 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 7624 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 2314 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 7634 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 2319 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 7644 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 2324 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 7654 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 2329 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 7664 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 2334 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 7674 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 2339 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 7684 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 2344 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 7694 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 2349 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 7704 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 339:
#line 2354 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
#endif
    }
#line 7717 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 340:
#line 2362 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
#endif
    }
#line 7730 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 341:
#line 2370 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
#endif
    }
#line 7743 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 342:
#line 2378 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
#endif
    }
#line 7756 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 343:
#line 2386 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
#endif
    }
#line 7769 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 344:
#line 2394 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
#endif
    }
#line 7782 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 345:
#line 2402 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
#endif
    }
#line 7795 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 346:
#line 2410 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
#endif
    }
#line 7808 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 347:
#line 2418 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
#endif
    }
#line 7821 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 348:
#line 2426 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
#endif
    }
#line 7834 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 349:
#line 2434 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
#endif
    }
#line 7847 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 350:
#line 2442 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
#endif
    }
#line 7860 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 351:
#line 2450 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
#endif
    }
#line 7873 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 352:
#line 2458 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 7883 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 353:
#line 2463 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 7893 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 354:
#line 2468 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 7903 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 355:
#line 2473 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 7913 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 356:
#line 2478 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 7923 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 357:
#line 2483 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 7933 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 358:
#line 2488 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 7943 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 359:
#line 2493 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 7953 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 360:
#line 2498 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 7963 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 361:
#line 2503 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 7973 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 362:
#line 2508 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 7983 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 363:
#line 2513 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 7993 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 364:
#line 2518 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 8003 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 365:
#line 2523 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 8013 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 366:
#line 2528 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 8023 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 367:
#line 2533 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 8033 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 368:
#line 2538 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
#endif
    }
#line 8046 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 369:
#line 2546 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
#endif
    }
#line 8059 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 370:
#line 2554 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 8069 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 371:
#line 2559 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 8079 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 372:
#line 2564 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 8089 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 373:
#line 2569 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
#endif
    }
#line 8102 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 374:
#line 2577 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 8112 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 375:
#line 2582 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 8122 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 376:
#line 2587 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 8132 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 377:
#line 2592 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8145 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 378:
#line 2600 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 8155 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 379:
#line 2605 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 8165 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 380:
#line 2610 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 8175 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 381:
#line 2615 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8188 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 382:
#line 2623 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 8198 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 383:
#line 2628 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 8208 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 384:
#line 2633 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 8218 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 385:
#line 2638 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 8228 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 386:
#line 2643 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 8238 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 387:
#line 2648 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
#endif
    }
#line 8251 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 388:
#line 2656 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 8261 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 389:
#line 2661 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
#endif
    }
#line 8274 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 390:
#line 2669 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 8284 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 391:
#line 2674 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
#endif
    }
#line 8297 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 392:
#line 2682 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 8307 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 393:
#line 2687 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
#endif
    }
#line 8320 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 394:
#line 2695 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 8330 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 395:
#line 2700 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
#endif
    }
#line 8343 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 396:
#line 2708 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 8353 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 397:
#line 2713 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
#endif
    }
#line 8366 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 398:
#line 2721 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 8376 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 399:
#line 2726 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
#endif
    }
#line 8389 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 400:
#line 2734 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 8399 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 401:
#line 2739 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 8409 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 402:
#line 2744 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 8419 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 403:
#line 2749 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 8429 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 404:
#line 2754 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 8439 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 405:
#line 2759 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 8449 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 406:
#line 2764 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 8459 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 407:
#line 2769 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 8469 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 408:
#line 2774 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 8479 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 409:
#line 2779 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 8489 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 410:
#line 2784 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 8499 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 411:
#line 2789 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 8509 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 412:
#line 2794 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 8519 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 413:
#line 2799 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 8529 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 414:
#line 2804 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 8539 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 415:
#line 2809 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
#endif
    }
#line 8552 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 416:
#line 2817 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 8562 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 417:
#line 2822 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 8572 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 418:
#line 2827 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 8582 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 419:
#line 2832 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
#endif
    }
#line 8595 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 420:
#line 2840 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 8605 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 421:
#line 2845 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 8615 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 422:
#line 2850 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 8625 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 423:
#line 2855 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8638 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 424:
#line 2863 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 8648 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 425:
#line 2868 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 8658 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 426:
#line 2873 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 8668 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 427:
#line 2878 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8681 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 428:
#line 2886 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 8691 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 429:
#line 2891 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 8701 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 430:
#line 2896 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 8711 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 431:
#line 2901 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
#endif
    }
#line 8724 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 432:
#line 2909 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 8734 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 433:
#line 2914 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 8744 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 434:
#line 2919 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 8754 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 435:
#line 2924 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
#endif
    }
#line 8767 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 436:
#line 2932 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 8777 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 437:
#line 2937 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 8787 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 438:
#line 2942 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 8797 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 439:
#line 2947 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
#endif
    }
#line 8810 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 440:
#line 2955 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 8820 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 441:
#line 2960 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 8830 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 442:
#line 2965 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 8840 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 443:
#line 2970 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
#endif
    }
#line 8853 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 444:
#line 2978 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 8863 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 445:
#line 2983 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 8873 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 446:
#line 2988 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 8883 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 447:
#line 2993 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
#endif
    }
#line 8896 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 448:
#line 3001 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 8906 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 449:
#line 3006 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 8916 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 450:
#line 3011 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 8926 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 451:
#line 3016 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
#endif
    }
#line 8939 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 452:
#line 3024 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 8949 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 453:
#line 3029 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 8959 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 454:
#line 3034 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 8969 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 455:
#line 3039 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
#endif
    }
#line 8982 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 456:
#line 3047 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 8992 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 457:
#line 3052 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 9002 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 458:
#line 3057 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 9012 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 459:
#line 3062 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
#endif
    }
#line 9025 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 460:
#line 3070 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 9035 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 461:
#line 3075 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 9045 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 462:
#line 3080 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 9055 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 463:
#line 3085 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
#endif
    }
#line 9068 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 464:
#line 3093 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 9078 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 465:
#line 3098 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 9088 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 466:
#line 3103 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 9098 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 467:
#line 3108 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 9111 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 468:
#line 3116 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 9121 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 469:
#line 3121 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 9131 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 470:
#line 3126 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 9141 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 471:
#line 3131 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 9154 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 472:
#line 3139 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 9164 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 473:
#line 3144 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 9174 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 474:
#line 3149 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 9185 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 475:
#line 3155 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { // GL_EXT_YUV_target
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.yuv = true;
    }
#line 9196 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 476:
#line 3161 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 9207 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 477:
#line 3167 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 9218 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 478:
#line 3173 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
#endif
    }
#line 9232 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 479:
#line 3182 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
#endif
    }
#line 9246 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 480:
#line 3191 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 9257 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 481:
#line 3197 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 9268 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 482:
#line 3203 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 9279 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 483:
#line 3209 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 9290 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 484:
#line 3215 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fcoopmatCheck((yyvsp[0].lex).loc, "fcoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).coopmat = true;
    }
#line 9301 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 485:
#line 3221 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 9311 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 486:
#line 3226 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ((yyvsp[0].lex).symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
            (yyval.interm.type).basicType = EbtStruct;
            (yyval.interm.type).userDef = &structure;
        } else
            parseContext.error((yyvsp[0].lex).loc, "expected type name", (yyvsp[0].lex).string->c_str(), "");
    }
#line 9329 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 487:
#line 3242 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 9339 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 488:
#line 3247 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 9349 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 489:
#line 3252 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 9359 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 490:
#line 3260 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 9365 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 491:
#line 3260 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), *(yyvsp[-4].lex).string);
        parseContext.structArrayCheck((yyvsp[-4].lex).loc, *structure);
        TVariable* userTypeDef = new TVariable((yyvsp[-4].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[-4].lex).loc, "redefinition", (yyvsp[-4].lex).string->c_str(), "struct");
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 9381 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 492:
#line 3271 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 9387 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 493:
#line 3271 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 9399 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 494:
#line 3281 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 9407 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 495:
#line 3284 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 9422 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 496:
#line 3297 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 9449 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 497:
#line 3319 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.memberQualifierCheck((yyvsp[-3].interm.type));
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, (yyvsp[-3].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 9478 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 498:
#line 3346 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9487 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 499:
#line 3350 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9495 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 500:
#line 3356 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 9505 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 501:
#line 3361 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->transferArraySizes((yyvsp[0].interm).arraySizes);
    }
#line 9518 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 502:
#line 3372 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 9526 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 503:
#line 3375 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 9537 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 504:
#line 3381 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 9548 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 505:
#line 3390 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 9556 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 506:
#line 3393 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 9564 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 507:
#line 3399 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9570 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 508:
#line 3403 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9576 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 509:
#line 3404 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9582 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 510:
#line 3410 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9588 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 511:
#line 3411 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9594 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 512:
#line 3412 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9600 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 513:
#line 3413 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9606 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 514:
#line 3414 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9612 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 515:
#line 3415 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9618 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 516:
#line 3416 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9624 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 517:
#line 3420 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 9630 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 518:
#line 3421 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 9639 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 519:
#line 3425 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 9648 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 520:
#line 3429 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate())
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 9658 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 521:
#line 3437 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9664 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 522:
#line 3438 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9670 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 523:
#line 3442 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 9678 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 524:
#line 3445 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9687 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 525:
#line 3449 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9697 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 526:
#line 3454 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9708 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 527:
#line 3463 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9716 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 528:
#line 3466 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate())
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 9726 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 529:
#line 3474 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 9739 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 530:
#line 3482 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 9752 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 531:
#line 3493 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 9758 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 532:
#line 3494 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 9764 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 533:
#line 3498 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9772 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 534:
#line 3501 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9781 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 535:
#line 3507 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 9790 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 536:
#line 3514 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 9799 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 537:
#line 3518 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 9808 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 538:
#line 3526 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 9817 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 539:
#line 3530 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    }
#line 9832 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 540:
#line 3543 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9840 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 541:
#line 3546 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9849 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 542:
#line 3552 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 9862 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 543:
#line 3560 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9876 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 544:
#line 3572 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9884 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 545:
#line 3575 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9892 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 546:
#line 3581 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-2].lex).loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-2].lex).loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck((yyvsp[-1].interm.intermTypedNode), "case");
            parseContext.integerCheck((yyvsp[-1].interm.intermTypedNode), "case");
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpCase, (yyvsp[-1].interm.intermTypedNode), (yyvsp[-2].lex).loc);
        }
    }
#line 9909 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 547:
#line 3593 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 9923 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 548:
#line 3605 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9931 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 549:
#line 3608 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9940 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 550:
#line 3614 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9953 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 551:
#line 3622 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, true, (yyvsp[-5].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9965 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 552:
#line 3629 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9975 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 553:
#line 3634 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9991 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 554:
#line 3645 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 10002 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 555:
#line 3651 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[-3].interm.intermNode), (yyvsp[-5].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node2), true, (yyvsp[-6].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[-6].lex).loc, (yyvsp[-3].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[-6].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 10019 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 556:
#line 3666 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10027 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 557:
#line 3669 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10035 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 558:
#line 3675 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 10043 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 559:
#line 3678 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = 0;
    }
#line 10051 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 560:
#line 3684 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 10060 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 561:
#line 3688 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 10069 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 562:
#line 3695 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 10079 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 563:
#line 3700 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 10089 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 564:
#line 3705 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 10101 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 565:
#line 3712 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10109 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 566:
#line 3715 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 10118 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 567:
#line 3724 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 10127 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 568:
#line 3728 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 10138 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 569:
#line 3737 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10146 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 570:
#line 3740 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10154 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 571:
#line 3743 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 10164 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 572:
#line 3751 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);
    }
#line 10173 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 573:
#line 3755 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[-2].interm).loc, "function does not return a value:", "", (yyvsp[-2].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermNode));
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[-2].interm).function->getType(), (yyvsp[-2].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[-2].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->setPragmaTable(parseContext.contextPragma.pragmaTable);
    }
#line 10193 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 574:
#line 3773 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
        parseContext.requireExtensions((yyvsp[-4].lex).loc, 1, &E_GL_EXT_control_flow_attributes, "attribute");
    }
#line 10202 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 575:
#line 3779 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 10210 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 576:
#line 3782 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 10218 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 577:
#line 3787 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 10226 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 578:
#line 3790 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10234 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;


#line 10238 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
      yyerror (pParseContext, YY_("syntax error"));
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
        yyerror (pParseContext, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval, pParseContext);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, pParseContext);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (pParseContext, YY_("memory exhausted"));
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
                  yytoken, &yylval, pParseContext);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, pParseContext);
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
#line 3794 "MachineIndependent/glslang.y" /* yacc.c:1906  */


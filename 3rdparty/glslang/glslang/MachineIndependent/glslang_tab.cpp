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
    DEMOTE = 289,
    BVEC2 = 290,
    BVEC3 = 291,
    BVEC4 = 292,
    IVEC2 = 293,
    IVEC3 = 294,
    IVEC4 = 295,
    UVEC2 = 296,
    UVEC3 = 297,
    UVEC4 = 298,
    I64VEC2 = 299,
    I64VEC3 = 300,
    I64VEC4 = 301,
    U64VEC2 = 302,
    U64VEC3 = 303,
    U64VEC4 = 304,
    I32VEC2 = 305,
    I32VEC3 = 306,
    I32VEC4 = 307,
    U32VEC2 = 308,
    U32VEC3 = 309,
    U32VEC4 = 310,
    I16VEC2 = 311,
    I16VEC3 = 312,
    I16VEC4 = 313,
    U16VEC2 = 314,
    U16VEC3 = 315,
    U16VEC4 = 316,
    I8VEC2 = 317,
    I8VEC3 = 318,
    I8VEC4 = 319,
    U8VEC2 = 320,
    U8VEC3 = 321,
    U8VEC4 = 322,
    VEC2 = 323,
    VEC3 = 324,
    VEC4 = 325,
    MAT2 = 326,
    MAT3 = 327,
    MAT4 = 328,
    CENTROID = 329,
    IN = 330,
    OUT = 331,
    INOUT = 332,
    UNIFORM = 333,
    PATCH = 334,
    SAMPLE = 335,
    BUFFER = 336,
    SHARED = 337,
    NONUNIFORM = 338,
    PAYLOADNV = 339,
    PAYLOADINNV = 340,
    HITATTRNV = 341,
    CALLDATANV = 342,
    CALLDATAINNV = 343,
    COHERENT = 344,
    VOLATILE = 345,
    RESTRICT = 346,
    READONLY = 347,
    WRITEONLY = 348,
    DEVICECOHERENT = 349,
    QUEUEFAMILYCOHERENT = 350,
    WORKGROUPCOHERENT = 351,
    SUBGROUPCOHERENT = 352,
    NONPRIVATE = 353,
    DVEC2 = 354,
    DVEC3 = 355,
    DVEC4 = 356,
    DMAT2 = 357,
    DMAT3 = 358,
    DMAT4 = 359,
    F16VEC2 = 360,
    F16VEC3 = 361,
    F16VEC4 = 362,
    F16MAT2 = 363,
    F16MAT3 = 364,
    F16MAT4 = 365,
    F32VEC2 = 366,
    F32VEC3 = 367,
    F32VEC4 = 368,
    F32MAT2 = 369,
    F32MAT3 = 370,
    F32MAT4 = 371,
    F64VEC2 = 372,
    F64VEC3 = 373,
    F64VEC4 = 374,
    F64MAT2 = 375,
    F64MAT3 = 376,
    F64MAT4 = 377,
    NOPERSPECTIVE = 378,
    FLAT = 379,
    SMOOTH = 380,
    LAYOUT = 381,
    EXPLICITINTERPAMD = 382,
    PERVERTEXNV = 383,
    PERPRIMITIVENV = 384,
    PERVIEWNV = 385,
    PERTASKNV = 386,
    MAT2X2 = 387,
    MAT2X3 = 388,
    MAT2X4 = 389,
    MAT3X2 = 390,
    MAT3X3 = 391,
    MAT3X4 = 392,
    MAT4X2 = 393,
    MAT4X3 = 394,
    MAT4X4 = 395,
    DMAT2X2 = 396,
    DMAT2X3 = 397,
    DMAT2X4 = 398,
    DMAT3X2 = 399,
    DMAT3X3 = 400,
    DMAT3X4 = 401,
    DMAT4X2 = 402,
    DMAT4X3 = 403,
    DMAT4X4 = 404,
    F16MAT2X2 = 405,
    F16MAT2X3 = 406,
    F16MAT2X4 = 407,
    F16MAT3X2 = 408,
    F16MAT3X3 = 409,
    F16MAT3X4 = 410,
    F16MAT4X2 = 411,
    F16MAT4X3 = 412,
    F16MAT4X4 = 413,
    F32MAT2X2 = 414,
    F32MAT2X3 = 415,
    F32MAT2X4 = 416,
    F32MAT3X2 = 417,
    F32MAT3X3 = 418,
    F32MAT3X4 = 419,
    F32MAT4X2 = 420,
    F32MAT4X3 = 421,
    F32MAT4X4 = 422,
    F64MAT2X2 = 423,
    F64MAT2X3 = 424,
    F64MAT2X4 = 425,
    F64MAT3X2 = 426,
    F64MAT3X3 = 427,
    F64MAT3X4 = 428,
    F64MAT4X2 = 429,
    F64MAT4X3 = 430,
    F64MAT4X4 = 431,
    ATOMIC_UINT = 432,
    ACCSTRUCTNV = 433,
    FCOOPMATNV = 434,
    SAMPLER1D = 435,
    SAMPLER2D = 436,
    SAMPLER3D = 437,
    SAMPLERCUBE = 438,
    SAMPLER1DSHADOW = 439,
    SAMPLER2DSHADOW = 440,
    SAMPLERCUBESHADOW = 441,
    SAMPLER1DARRAY = 442,
    SAMPLER2DARRAY = 443,
    SAMPLER1DARRAYSHADOW = 444,
    SAMPLER2DARRAYSHADOW = 445,
    ISAMPLER1D = 446,
    ISAMPLER2D = 447,
    ISAMPLER3D = 448,
    ISAMPLERCUBE = 449,
    ISAMPLER1DARRAY = 450,
    ISAMPLER2DARRAY = 451,
    USAMPLER1D = 452,
    USAMPLER2D = 453,
    USAMPLER3D = 454,
    USAMPLERCUBE = 455,
    USAMPLER1DARRAY = 456,
    USAMPLER2DARRAY = 457,
    SAMPLER2DRECT = 458,
    SAMPLER2DRECTSHADOW = 459,
    ISAMPLER2DRECT = 460,
    USAMPLER2DRECT = 461,
    SAMPLERBUFFER = 462,
    ISAMPLERBUFFER = 463,
    USAMPLERBUFFER = 464,
    SAMPLERCUBEARRAY = 465,
    SAMPLERCUBEARRAYSHADOW = 466,
    ISAMPLERCUBEARRAY = 467,
    USAMPLERCUBEARRAY = 468,
    SAMPLER2DMS = 469,
    ISAMPLER2DMS = 470,
    USAMPLER2DMS = 471,
    SAMPLER2DMSARRAY = 472,
    ISAMPLER2DMSARRAY = 473,
    USAMPLER2DMSARRAY = 474,
    SAMPLEREXTERNALOES = 475,
    SAMPLEREXTERNAL2DY2YEXT = 476,
    F16SAMPLER1D = 477,
    F16SAMPLER2D = 478,
    F16SAMPLER3D = 479,
    F16SAMPLER2DRECT = 480,
    F16SAMPLERCUBE = 481,
    F16SAMPLER1DARRAY = 482,
    F16SAMPLER2DARRAY = 483,
    F16SAMPLERCUBEARRAY = 484,
    F16SAMPLERBUFFER = 485,
    F16SAMPLER2DMS = 486,
    F16SAMPLER2DMSARRAY = 487,
    F16SAMPLER1DSHADOW = 488,
    F16SAMPLER2DSHADOW = 489,
    F16SAMPLER1DARRAYSHADOW = 490,
    F16SAMPLER2DARRAYSHADOW = 491,
    F16SAMPLER2DRECTSHADOW = 492,
    F16SAMPLERCUBESHADOW = 493,
    F16SAMPLERCUBEARRAYSHADOW = 494,
    SAMPLER = 495,
    SAMPLERSHADOW = 496,
    TEXTURE1D = 497,
    TEXTURE2D = 498,
    TEXTURE3D = 499,
    TEXTURECUBE = 500,
    TEXTURE1DARRAY = 501,
    TEXTURE2DARRAY = 502,
    ITEXTURE1D = 503,
    ITEXTURE2D = 504,
    ITEXTURE3D = 505,
    ITEXTURECUBE = 506,
    ITEXTURE1DARRAY = 507,
    ITEXTURE2DARRAY = 508,
    UTEXTURE1D = 509,
    UTEXTURE2D = 510,
    UTEXTURE3D = 511,
    UTEXTURECUBE = 512,
    UTEXTURE1DARRAY = 513,
    UTEXTURE2DARRAY = 514,
    TEXTURE2DRECT = 515,
    ITEXTURE2DRECT = 516,
    UTEXTURE2DRECT = 517,
    TEXTUREBUFFER = 518,
    ITEXTUREBUFFER = 519,
    UTEXTUREBUFFER = 520,
    TEXTURECUBEARRAY = 521,
    ITEXTURECUBEARRAY = 522,
    UTEXTURECUBEARRAY = 523,
    TEXTURE2DMS = 524,
    ITEXTURE2DMS = 525,
    UTEXTURE2DMS = 526,
    TEXTURE2DMSARRAY = 527,
    ITEXTURE2DMSARRAY = 528,
    UTEXTURE2DMSARRAY = 529,
    F16TEXTURE1D = 530,
    F16TEXTURE2D = 531,
    F16TEXTURE3D = 532,
    F16TEXTURE2DRECT = 533,
    F16TEXTURECUBE = 534,
    F16TEXTURE1DARRAY = 535,
    F16TEXTURE2DARRAY = 536,
    F16TEXTURECUBEARRAY = 537,
    F16TEXTUREBUFFER = 538,
    F16TEXTURE2DMS = 539,
    F16TEXTURE2DMSARRAY = 540,
    SUBPASSINPUT = 541,
    SUBPASSINPUTMS = 542,
    ISUBPASSINPUT = 543,
    ISUBPASSINPUTMS = 544,
    USUBPASSINPUT = 545,
    USUBPASSINPUTMS = 546,
    F16SUBPASSINPUT = 547,
    F16SUBPASSINPUTMS = 548,
    IMAGE1D = 549,
    IIMAGE1D = 550,
    UIMAGE1D = 551,
    IMAGE2D = 552,
    IIMAGE2D = 553,
    UIMAGE2D = 554,
    IMAGE3D = 555,
    IIMAGE3D = 556,
    UIMAGE3D = 557,
    IMAGE2DRECT = 558,
    IIMAGE2DRECT = 559,
    UIMAGE2DRECT = 560,
    IMAGECUBE = 561,
    IIMAGECUBE = 562,
    UIMAGECUBE = 563,
    IMAGEBUFFER = 564,
    IIMAGEBUFFER = 565,
    UIMAGEBUFFER = 566,
    IMAGE1DARRAY = 567,
    IIMAGE1DARRAY = 568,
    UIMAGE1DARRAY = 569,
    IMAGE2DARRAY = 570,
    IIMAGE2DARRAY = 571,
    UIMAGE2DARRAY = 572,
    IMAGECUBEARRAY = 573,
    IIMAGECUBEARRAY = 574,
    UIMAGECUBEARRAY = 575,
    IMAGE2DMS = 576,
    IIMAGE2DMS = 577,
    UIMAGE2DMS = 578,
    IMAGE2DMSARRAY = 579,
    IIMAGE2DMSARRAY = 580,
    UIMAGE2DMSARRAY = 581,
    F16IMAGE1D = 582,
    F16IMAGE2D = 583,
    F16IMAGE3D = 584,
    F16IMAGE2DRECT = 585,
    F16IMAGECUBE = 586,
    F16IMAGE1DARRAY = 587,
    F16IMAGE2DARRAY = 588,
    F16IMAGECUBEARRAY = 589,
    F16IMAGEBUFFER = 590,
    F16IMAGE2DMS = 591,
    F16IMAGE2DMSARRAY = 592,
    STRUCT = 593,
    VOID = 594,
    WHILE = 595,
    IDENTIFIER = 596,
    TYPE_NAME = 597,
    FLOATCONSTANT = 598,
    DOUBLECONSTANT = 599,
    INT16CONSTANT = 600,
    UINT16CONSTANT = 601,
    INT32CONSTANT = 602,
    UINT32CONSTANT = 603,
    INTCONSTANT = 604,
    UINTCONSTANT = 605,
    INT64CONSTANT = 606,
    UINT64CONSTANT = 607,
    BOOLCONSTANT = 608,
    FLOAT16CONSTANT = 609,
    LEFT_OP = 610,
    RIGHT_OP = 611,
    INC_OP = 612,
    DEC_OP = 613,
    LE_OP = 614,
    GE_OP = 615,
    EQ_OP = 616,
    NE_OP = 617,
    AND_OP = 618,
    OR_OP = 619,
    XOR_OP = 620,
    MUL_ASSIGN = 621,
    DIV_ASSIGN = 622,
    ADD_ASSIGN = 623,
    MOD_ASSIGN = 624,
    LEFT_ASSIGN = 625,
    RIGHT_ASSIGN = 626,
    AND_ASSIGN = 627,
    XOR_ASSIGN = 628,
    OR_ASSIGN = 629,
    SUB_ASSIGN = 630,
    LEFT_PAREN = 631,
    RIGHT_PAREN = 632,
    LEFT_BRACKET = 633,
    RIGHT_BRACKET = 634,
    LEFT_BRACE = 635,
    RIGHT_BRACE = 636,
    DOT = 637,
    COMMA = 638,
    COLON = 639,
    EQUAL = 640,
    SEMICOLON = 641,
    BANG = 642,
    DASH = 643,
    TILDE = 644,
    PLUS = 645,
    STAR = 646,
    SLASH = 647,
    PERCENT = 648,
    LEFT_ANGLE = 649,
    RIGHT_ANGLE = 650,
    VERTICAL_BAR = 651,
    CARET = 652,
    AMPERSAND = 653,
    QUESTION = 654,
    INVARIANT = 655,
    PRECISE = 656,
    HIGH_PRECISION = 657,
    MEDIUM_PRECISION = 658,
    LOW_PRECISION = 659,
    PRECISION = 660,
    PACKED = 661,
    RESOURCE = 662,
    SUPERP = 663
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

#line 577 "MachineIndependent/glslang_tab.cpp" /* yacc.c:355  */
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


#line 608 "MachineIndependent/glslang_tab.cpp" /* yacc.c:358  */

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
#define YYLAST   9372

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  409
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  111
/* YYNRULES -- Number of rules.  */
#define YYNRULES  580
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  725

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   663

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
     405,   406,   407,   408
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
     612,   621,   633,   634,   643,   644,   653,   654,   663,   664,
     672,   673,   681,   682,   690,   691,   691,   709,   710,   726,
     730,   734,   738,   743,   747,   751,   755,   759,   763,   767,
     774,   777,   788,   795,   800,   805,   813,   817,   821,   825,
     830,   835,   844,   844,   855,   859,   866,   873,   876,   883,
     891,   911,   934,   949,   974,   985,   995,  1005,  1015,  1024,
    1027,  1031,  1035,  1040,  1048,  1053,  1058,  1063,  1068,  1077,
    1088,  1115,  1124,  1131,  1138,  1149,  1158,  1168,  1180,  1189,
    1201,  1207,  1210,  1217,  1221,  1225,  1233,  1242,  1245,  1256,
    1259,  1262,  1266,  1270,  1274,  1278,  1284,  1288,  1300,  1314,
    1319,  1325,  1331,  1338,  1344,  1349,  1354,  1359,  1369,  1379,
    1389,  1399,  1408,  1420,  1424,  1429,  1434,  1439,  1444,  1449,
    1453,  1457,  1461,  1465,  1471,  1480,  1487,  1490,  1498,  1503,
    1513,  1518,  1526,  1530,  1540,  1543,  1549,  1555,  1562,  1572,
    1576,  1580,  1585,  1590,  1595,  1600,  1604,  1609,  1614,  1619,
    1624,  1629,  1634,  1639,  1644,  1649,  1653,  1658,  1663,  1668,
    1674,  1680,  1686,  1692,  1698,  1704,  1710,  1716,  1722,  1728,
    1734,  1740,  1745,  1750,  1755,  1760,  1765,  1770,  1776,  1782,
    1788,  1794,  1800,  1806,  1812,  1818,  1824,  1830,  1836,  1842,
    1848,  1854,  1860,  1866,  1872,  1878,  1884,  1890,  1896,  1902,
    1908,  1914,  1920,  1926,  1932,  1937,  1942,  1947,  1952,  1957,
    1962,  1967,  1972,  1977,  1982,  1987,  1992,  1998,  2004,  2010,
    2016,  2022,  2028,  2034,  2040,  2046,  2052,  2058,  2064,  2070,
    2076,  2082,  2088,  2094,  2100,  2106,  2112,  2118,  2124,  2130,
    2136,  2142,  2148,  2154,  2160,  2166,  2172,  2178,  2184,  2190,
    2196,  2202,  2208,  2214,  2220,  2226,  2232,  2238,  2244,  2250,
    2256,  2262,  2268,  2274,  2280,  2286,  2291,  2296,  2301,  2306,
    2311,  2316,  2321,  2326,  2331,  2336,  2341,  2346,  2351,  2356,
    2364,  2372,  2380,  2388,  2396,  2404,  2412,  2420,  2428,  2436,
    2444,  2452,  2460,  2465,  2470,  2475,  2480,  2485,  2490,  2495,
    2500,  2505,  2510,  2515,  2520,  2525,  2530,  2535,  2540,  2548,
    2556,  2561,  2566,  2571,  2579,  2584,  2589,  2594,  2602,  2607,
    2612,  2617,  2625,  2630,  2635,  2640,  2645,  2650,  2658,  2663,
    2671,  2676,  2684,  2689,  2697,  2702,  2710,  2715,  2723,  2728,
    2736,  2741,  2746,  2751,  2756,  2761,  2766,  2771,  2776,  2781,
    2786,  2791,  2796,  2801,  2806,  2811,  2819,  2824,  2829,  2834,
    2842,  2847,  2852,  2857,  2865,  2870,  2875,  2880,  2888,  2893,
    2898,  2903,  2911,  2916,  2921,  2926,  2934,  2939,  2944,  2949,
    2957,  2962,  2967,  2972,  2980,  2985,  2990,  2995,  3003,  3008,
    3013,  3018,  3026,  3031,  3036,  3041,  3049,  3054,  3059,  3064,
    3072,  3077,  3082,  3087,  3095,  3100,  3105,  3110,  3118,  3123,
    3128,  3133,  3141,  3146,  3151,  3157,  3163,  3169,  3175,  3184,
    3193,  3199,  3205,  3211,  3217,  3223,  3228,  3244,  3249,  3254,
    3262,  3262,  3273,  3273,  3283,  3286,  3299,  3321,  3348,  3352,
    3358,  3363,  3374,  3377,  3383,  3392,  3395,  3401,  3405,  3406,
    3412,  3413,  3414,  3415,  3416,  3417,  3418,  3419,  3423,  3431,
    3432,  3436,  3432,  3448,  3449,  3453,  3453,  3460,  3460,  3474,
    3477,  3485,  3493,  3504,  3505,  3509,  3512,  3518,  3525,  3529,
    3537,  3541,  3554,  3557,  3563,  3563,  3583,  3586,  3592,  3604,
    3616,  3619,  3625,  3625,  3640,  3640,  3656,  3656,  3677,  3680,
    3686,  3689,  3695,  3699,  3706,  3711,  3716,  3723,  3726,  3735,
    3739,  3748,  3751,  3754,  3762,  3762,  3784,  3790,  3793,  3798,
    3801
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
  "SUBROUTINE", "DEMOTE", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3",
  "IVEC4", "UVEC2", "UVEC3", "UVEC4", "I64VEC2", "I64VEC3", "I64VEC4",
  "U64VEC2", "U64VEC3", "U64VEC4", "I32VEC2", "I32VEC3", "I32VEC4",
  "U32VEC2", "U32VEC3", "U32VEC4", "I16VEC2", "I16VEC3", "I16VEC4",
  "U16VEC2", "U16VEC3", "U16VEC4", "I8VEC2", "I8VEC3", "I8VEC4", "U8VEC2",
  "U8VEC3", "U8VEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4",
  "CENTROID", "IN", "OUT", "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER",
  "SHARED", "NONUNIFORM", "PAYLOADNV", "PAYLOADINNV", "HITATTRNV",
  "CALLDATANV", "CALLDATAINNV", "COHERENT", "VOLATILE", "RESTRICT",
  "READONLY", "WRITEONLY", "DEVICECOHERENT", "QUEUEFAMILYCOHERENT",
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
  "simple_statement", "demote_statement", "compound_statement", "$@5",
  "$@6", "statement_no_new_scope", "statement_scoped", "$@7", "$@8",
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
     655,   656,   657,   658,   659,   660,   661,   662,   663
};
# endif

#define YYPACT_NINF -657

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-657)))

#define YYTABLE_NINF -526

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3545,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -328,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -307,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -318,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -259,  -657,  -320,  -286,  -236,  -251,  5958,
    -299,  -657,  -191,  -657,  -657,  -657,  -657,  4350,  -657,  -657,
    -657,  -657,  -228,  -657,  -657,   724,  -657,  -657,  -176,   -72,
    -212,  -657,  9030,  -352,  -657,  -657,  -211,  -657,  5958,  -657,
    -657,  -657,  5958,  -171,  -169,  -657,  -324,  -285,  -657,  -657,
    -657,  8258,  -205,  -657,  -657,  -657,  -657,  -281,  -657,  -210,
    -280,  -657,  -657,  5958,  -208,  6714,  -657,  -345,  1127,  -657,
    -657,  -657,  -657,  -205,  -325,  -657,  7100,  -322,  -657,  -167,
    -657,  -271,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  8258,  8258,  8258,  -657,  -657,
    -657,  -657,  -657,  -657,  -327,  -657,  -657,  -657,  -198,  -278,
    8644,  -196,  -657,  8258,  -657,  -657,  -355,  -197,  -657,  -159,
    8258,  -657,   -72,  5958,  5958,  -158,  4752,  -657,  -657,  -657,
    -657,  -245,  -305,  -291,  -323,  -209,  -214,  -207,  -204,  -178,
    -177,  -340,  -192,  7486,  -657,  -193,  -190,  -657,  -187,  -182,
    -189,  7872,  -181,  8258,  -186,  -185,  -174,  -179,  -172,  -657,
    -657,  -293,  -657,  -657,  -253,  -657,  -286,  -165,  -164,  -657,
    -657,  -657,  -657,  -657,  1530,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,   -19,  -197,  7100,  -292,  7100,  -657,
    -657,  7100,  5958,  -657,  -141,  -657,  -657,  -657,  -273,  -657,
    -657,  8258,  -137,  -657,  -657,  8258,  -163,  -657,  -657,  -657,
    8258,  -657,  -657,  -657,  -657,  -657,  5154,  -158,  -205,  -252,
    -657,  -657,  -657,  8258,  8258,  8258,  8258,  8258,  8258,  8258,
    8258,  8258,  8258,  8258,  8258,  8258,  8258,  8258,  8258,  8258,
    8258,  8258,  -657,  -657,  -657,  -166,  -657,  -657,  1933,  -657,
    8258,  -657,  -657,  -246,  8258,  -229,  -657,  -657,  -657,  -136,
    -657,  1933,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  8258,  8258,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  7100,  -657,  -232,  -657,  5556,  -657,  -657,  -142,
    -145,  -657,  -657,  -657,  -657,  -244,  -197,  -158,  -657,  -657,
    -657,  -657,  -245,  -245,  -305,  -305,  -291,  -291,  -291,  -291,
    -323,  -323,  -209,  -214,  -207,  -204,  -178,  -177,  8258,  -657,
    -101,  3142,  -269,  -657,  -261,  -657,  3948,  -135,  -344,  -657,
    1933,  -657,  -657,  -657,  -657,  6328,  -657,  -657,  -657,  -657,
    -227,  -134,  -657,  -657,  3948,  -140,  -657,  -145,   -97,  5958,
    -132,  8258,  -133,  -136,  -131,  -657,  -657,  8258,  8258,  -657,
    -139,  -129,   224,  -128,  2739,  -657,  -127,  -130,  2336,  -126,
    -657,  -657,  -657,  -657,  -254,  8258,  2336,  -140,  -657,  -657,
    1933,  7100,  -657,  -657,  -657,  -657,  -124,  -145,  -657,  -657,
    1933,  -125,  -657,  -657,  -657
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
     463,   451,   467,   471,     0,   199,   486,   573,   131,   146,
     487,   488,   489,     0,   572,     0,   574,     0,   108,   107,
       0,   119,   124,   153,   152,   150,   154,     0,   147,   149,
     155,   129,   195,   151,   485,     0,   569,   571,     0,     0,
       0,   492,     0,     0,    96,    93,     0,   106,     0,   115,
     109,   117,     0,   118,     0,    94,   125,     0,    99,   148,
     130,     0,   188,   194,     1,   570,   186,     0,   145,   143,
       0,   141,   490,     0,     0,     0,    97,     0,     0,   575,
     110,   114,   116,   112,   120,   111,     0,   126,   102,     0,
     100,     0,     2,    12,    13,    10,    11,     4,     5,     6,
       7,     8,     9,    15,    14,     0,     0,     0,    42,    41,
      43,    40,     3,    17,    36,    19,    24,    25,     0,     0,
      29,     0,   197,     0,    35,    33,     0,   189,   184,     0,
       0,   140,     0,     0,     0,     0,     0,   494,    95,   190,
      44,    48,    51,    54,    59,    62,    64,    66,    68,    70,
      72,    74,     0,     0,    98,     0,     0,   554,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   520,   529,
     533,    44,    77,    90,     0,   507,     0,   155,   129,   510,
     531,   509,   517,   508,     0,   511,   512,   535,   513,   542,
     514,   515,   550,   516,     0,   113,     0,   121,     0,   502,
     128,     0,     0,   104,     0,   101,    37,    38,     0,    21,
      22,     0,     0,    27,    26,     0,   199,    30,    32,    39,
       0,   196,   187,    92,   144,   142,     0,     0,   500,     0,
     498,   493,   495,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,   191,   192,     0,   565,   564,     0,   556,
       0,   568,   566,     0,     0,     0,   549,   518,   552,     0,
     519,     0,    80,    81,    83,    82,    85,    86,    87,    88,
      89,    84,    79,     0,     0,   534,   530,   532,   536,   543,
     551,   123,     0,   505,     0,   127,     0,   105,    16,     0,
      23,    20,    31,   198,   491,     0,   501,     0,   496,    45,
      46,    47,    50,    49,    52,    53,    57,    58,    55,    56,
      60,    61,    63,    65,    67,    69,    71,    73,     0,   193,
       0,     0,     0,   567,     0,   548,     0,   579,     0,   577,
     521,    78,    91,   122,   503,     0,   103,    18,   497,   499,
       0,     0,   559,   558,   561,   527,   544,   540,     0,     0,
       0,     0,     0,     0,     0,   504,   506,     0,     0,   560,
       0,     0,   539,     0,     0,   537,     0,     0,     0,     0,
     576,   578,   522,    76,     0,   562,     0,   527,   526,   528,
     546,     0,   524,   553,   523,   580,     0,   563,   557,   538,
     547,     0,   541,   555,   545
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -337,  -657,  -398,  -395,  -435,  -404,  -312,  -310,
    -309,  -311,  -306,  -308,  -657,  -383,  -657,  -397,  -657,  -413,
    -421,     1,  -657,  -657,  -657,     2,  -657,  -657,  -657,  -107,
    -102,  -105,  -657,  -657,  -629,  -657,  -657,  -657,  -657,  -180,
    -657,  -336,  -343,  -657,     6,  -657,     0,  -357,  -657,  -657,
    -657,  -657,   -63,  -657,  -657,  -657,  -431,  -439,  -276,  -354,
    -503,  -657,  -377,  -484,  -656,  -657,  -417,  -657,  -657,  -429,
    -428,  -657,  -657,   -88,  -575,  -370,  -657,  -231,  -657,  -392,
    -657,  -230,  -657,  -657,  -657,  -657,  -226,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,   -70,  -657,  -657,  -657,  -657,
    -396
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   432,   433,   434,   619,   435,   436,   437,   438,   439,
     440,   441,   491,   443,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   492,   648,   493,   603,   494,
     544,   495,   335,   522,   411,   496,   337,   338,   339,   369,
     370,   371,   340,   341,   342,   343,   344,   345,   390,   391,
     346,   347,   348,   349,   444,   387,   445,   397,   382,   383,
     446,   352,   353,   354,   453,   393,   456,   457,   549,   550,
     520,   614,   499,   500,   501,   502,   503,   591,   684,   713,
     692,   693,   694,   714,   504,   505,   506,   507,   695,   680,
     508,   509,   696,   721,   510,   511,   512,   656,   578,   651,
     674,   690,   691,   513,   355,   356,   357,   366,   514,   658,
     659
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     351,   334,   336,   372,   379,   477,   350,   478,   479,   519,
     388,   482,   472,   611,   528,   613,   660,   552,   615,   407,
     607,   363,   546,   360,   571,   447,   395,   678,   540,   379,
     529,   530,   372,   473,   396,   682,   560,   561,   709,   683,
     541,   474,   712,   537,   442,   678,   515,   517,   358,   -34,
     712,   531,   405,   395,   395,   532,   473,   454,   460,   572,
     516,   406,   361,   521,   558,   559,   364,   543,   583,   359,
     585,   562,   563,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   556,   374,   557,   473,   375,   526,   527,
     575,   616,   602,   612,   650,   408,   448,   451,   409,   534,
     365,   410,   449,   452,   618,   535,   539,   552,   675,   663,
     604,   379,   524,   460,   604,   525,   676,   454,   620,   519,
     454,   519,   604,   716,   519,   636,   637,   638,   639,   604,
     604,   627,   368,   605,   628,   720,   460,   604,   622,   627,
     653,   367,   668,   330,   331,   332,   553,   554,   555,   664,
     376,   665,   564,   565,   604,   655,   604,   687,   632,   633,
     640,   641,   686,   634,   635,   386,   381,   652,   392,   398,
     403,   654,   404,   395,   523,   450,   607,   552,   458,   533,
     538,   473,   542,   548,   566,   569,   454,   573,   570,   579,
     567,   626,   568,   576,   580,   584,   577,   581,   586,   589,
     617,   587,   588,   623,   621,   657,   661,   662,   722,   590,
     454,   -35,   -33,   649,   -28,   519,   629,   630,   631,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   670,   607,   667,   604,   671,
    -525,   681,   688,   677,   697,   698,   700,   705,   706,   707,
     702,   715,   488,   710,   642,   711,   724,   643,   645,   644,
     699,   677,   723,   647,   646,   401,   400,   402,   519,   389,
     362,   625,   545,   669,   672,   704,   708,   718,   399,   719,
     454,   673,   689,   608,   609,   385,     0,   701,   610,     0,
     703,     0,   717,     0,     0,     0,     0,     0,   543,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   519,     0,     0,     0,     0,     0,
     679,   486,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   379,     0,   679,   373,
       0,     0,     0,     0,   460,   350,     0,   380,     0,     0,
       0,     0,     0,   350,     0,   351,   334,   336,     0,     0,
       0,   350,   394,     0,     0,     0,     0,     0,   373,     0,
       0,     0,   373,     0,   350,     0,     0,     0,   350,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,     0,     0,     0,     0,   498,   350,
       0,     0,     0,     0,   497,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,   547,     0,   455,     0,     0,   350,
     350,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   498,     0,     0,     0,     0,     0,
     497,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,     0,     0,     0,     0,     0,   350,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,     0,     0,     0,
       0,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   498,     0,
       0,     0,     0,     0,   497,     0,     0,     0,     0,     0,
       0,   498,     0,     0,     0,     0,     0,   497,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,     0,     0,     0,
       0,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   498,     0,     0,     0,     0,   498,   497,     0,     0,
     498,     0,   497,     0,     0,     0,   497,     0,     0,     0,
       0,     0,     0,     0,   498,     0,     0,     0,     0,   380,
     497,     0,     0,     0,     0,   350,     0,     0,     0,     0,
       0,     0,     0,     0,   498,     0,     0,     0,   498,     0,
     497,     0,     0,     0,   497,     0,   498,     0,     0,     0,
     498,     0,   497,     0,     0,     0,   497,     0,     0,     0,
     498,     0,     0,     0,   384,     0,   497,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,    21,
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
      11,    12,    13,    14,    15,    16,    17,    18,    19,   475,
     476,   477,     0,   478,   479,   480,   481,   482,   483,   484,
      20,   485,    21,    22,    23,    24,    25,    26,    27,    28,
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
     319,   320,   321,   322,   323,   324,   325,   486,   412,   326,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,     0,     0,   425,   426,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   427,     0,   487,     0,   488,   489,     0,
       0,     0,     0,   490,   428,   429,   430,   431,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   328,   329,   330,
     331,   332,   333,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   475,   476,   477,     0,   478,   479,   480,   481,
     482,   483,   484,    20,   485,    21,    22,    23,    24,    25,
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
     486,   412,   326,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,     0,     0,   425,   426,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     0,   487,     0,
     488,   606,     0,     0,     0,     0,   490,   428,   429,   430,
     431,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,   333,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   475,   476,   477,     0,   478,
     479,   480,   481,   482,   483,   484,    20,   485,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
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
     323,   324,   325,   486,   412,   326,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,     0,     0,
     425,   426,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   427,
       0,   487,     0,   488,     0,     0,     0,     0,     0,   490,
     428,   429,   430,   431,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   328,   329,   330,   331,   332,   333,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   475,   476,
     477,     0,   478,   479,   480,   481,   482,   483,   484,    20,
     485,    21,    22,    23,    24,    25,    26,    27,    28,    29,
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
     320,   321,   322,   323,   324,   325,   486,   412,   326,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,     0,     0,   425,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,   487,     0,   398,     0,     0,     0,
       0,     0,   490,   428,   429,   430,   431,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,   329,   330,   331,
     332,   333,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   475,   476,   477,     0,   478,   479,   480,   481,   482,
     483,   484,    20,   485,    21,    22,    23,    24,    25,    26,
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
     317,   318,   319,   320,   321,   322,   323,   324,   325,   486,
     412,   326,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,     0,     0,   425,   426,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   427,     0,   487,     0,     0,
       0,     0,     0,     0,     0,   490,   428,   429,   430,   431,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   328,
     329,   330,   331,   332,   333,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    21,    22,    23,
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
       0,     0,     0,     0,     0,     0,     0,     0,   490,   428,
     429,   430,   431,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,   329,   330,   331,   332,   333,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
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
     321,   322,   323,   324,   325,     0,     0,   326,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   327,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   328,   329,   330,   331,   332,
     333,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,    21,    22,    23,    24,    25,    26,    27,
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
     318,   319,   320,   321,   322,   323,   324,   325,     0,   412,
     326,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,     0,     0,   425,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   427,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   428,   429,   430,   431,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   328,   329,
     330,   331,   332,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,     0,    21,    22,    23,    24,    25,
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
       0,   377,   326,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,   329,   330,   331,   332,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    21,    22,    23,
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
     324,   325,     0,     0,   326,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   551,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,   329,   330,   331,   332,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,    21,
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
       0,     0,     0,     0,     0,   624,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   328,   329,   330,   331,   332,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
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
     320,   321,   322,   323,   324,   325,     0,     0,   326,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   666,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,   329,   330,   331,
     332,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,    21,    22,    23,    24,    25,    26,    27,
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
       0,     0,     0,     3,     4,     5,     6,     7,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,   328,   329,
     330,   331,   332,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     318,   319,   320,   321,   322,   323,   324,   325,     0,   412,
     326,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,     0,     0,   425,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   427,     0,     0,     0,   518,   685,
       0,     0,     0,     0,     0,   428,   429,   430,   431,     3,
       4,     5,     6,     7,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
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
     322,   323,   324,   325,     0,   412,   326,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,     0,
       0,   425,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     427,     0,     0,   459,     0,     0,     0,     0,     0,     0,
       0,   428,   429,   430,   431,     3,     4,     5,     6,     7,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
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
       0,   412,   326,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,     0,     0,   425,   426,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     0,     0,     0,
     518,     0,     0,     0,     0,     0,     0,   428,   429,   430,
     431,     3,     4,     5,     6,     7,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
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
       0,     0,   427,     0,     0,   574,     0,     0,     0,     0,
       0,     0,     0,   428,   429,   430,   431,     3,     4,     5,
       6,     7,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
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
       0,     0,     0,     0,     0,     0,     0,     0,   582,   428,
     429,   430,   431,     3,     4,     5,     6,     7,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     318,   319,   320,   321,   322,   323,   324,   325,     0,   412,
     326,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,     0,     0,   425,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   427,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   428,   429,   430,   431,     3,
       4,     5,     6,     7,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
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
     322,   323,   324,   536,     0,   412,   326,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,     0,
       0,   425,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     427,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   428,   429,   430,   431,     3,     4,     5,     6,     7,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
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
       0,     0,   326
};

static const yytype_int16 yycheck[] =
{
       0,     0,     0,   339,   347,    24,     0,    26,    27,   406,
      82,    30,   395,   516,   427,   518,   591,   456,   521,   376,
     504,   341,   453,   341,   364,   382,   378,   656,   383,   372,
     357,   358,   368,   378,   386,   379,   359,   360,   694,   383,
     395,   386,   698,   440,   381,   674,   403,   404,   376,   376,
     706,   378,   376,   378,   378,   382,   378,   393,   395,   399,
     385,   385,   380,   385,   355,   356,   386,   450,   481,   376,
     483,   394,   395,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   388,   383,   390,   378,   386,   425,   426,
     473,   522,   385,   385,   578,   380,   377,   377,   383,   377,
     386,   386,   383,   383,   377,   383,   443,   546,   377,   612,
     383,   454,   383,   450,   383,   386,   377,   453,   531,   516,
     456,   518,   383,   377,   521,   560,   561,   562,   563,   383,
     383,   383,   383,   386,   386,   710,   473,   383,   535,   383,
     386,   377,   386,   402,   403,   404,   391,   392,   393,   381,
     341,   383,   361,   362,   383,   384,   383,   384,   556,   557,
     564,   565,   665,   558,   559,   341,   394,   580,   380,   380,
     341,   584,   341,   378,   341,   385,   660,   616,   386,   377,
     376,   378,   341,   341,   398,   363,   522,   379,   365,   376,
     397,   548,   396,   386,   376,   376,   386,   386,   384,   378,
     341,   386,   376,   540,   341,   341,   603,   604,   711,   381,
     546,   376,   376,   379,   377,   612,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   648,   720,   379,   383,   340,
     380,   376,   376,   656,   341,   377,   379,   386,   377,    25,
     381,   377,   380,   380,   566,   385,   381,   567,   569,   568,
     681,   674,   386,   571,   570,   372,   368,   372,   665,   341,
     333,   547,   452,   627,   651,   688,   693,   706,   366,   707,
     616,   651,   674,   514,   514,   355,    -1,   683,   514,    -1,
     687,    -1,   705,    -1,    -1,    -1,    -1,    -1,   681,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   711,    -1,    -1,    -1,    -1,    -1,
     656,   340,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   679,    -1,   674,   339,
      -1,    -1,    -1,    -1,   681,   339,    -1,   347,    -1,    -1,
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
      -1,    -1,    -1,    -1,   504,    -1,    -1,    -1,    -1,    -1,
     504,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   522,    -1,    -1,    -1,    -1,    -1,   522,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   546,    -1,    -1,    -1,
      -1,    -1,   546,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   578,    -1,
      -1,    -1,    -1,    -1,   578,    -1,    -1,    -1,    -1,    -1,
      -1,   591,    -1,    -1,    -1,    -1,    -1,   591,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   616,    -1,    -1,    -1,
      -1,    -1,   616,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   651,    -1,    -1,    -1,    -1,   656,   651,    -1,    -1,
     660,    -1,   656,    -1,    -1,    -1,   660,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   674,    -1,    -1,    -1,    -1,   679,
     674,    -1,    -1,    -1,    -1,   679,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   694,    -1,    -1,    -1,   698,    -1,
     694,    -1,    -1,    -1,   698,    -1,   706,    -1,    -1,    -1,
     710,    -1,   706,    -1,    -1,    -1,   710,    -1,    -1,    -1,
     720,    -1,    -1,    -1,     0,    -1,   720,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,
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
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,    -1,    -1,   342,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   400,   401,   402,   403,   404,   405,
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
     353,   354,    -1,    -1,   357,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   376,    -1,   378,    -1,   380,   381,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,   390,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,   401,   402,
     403,   404,   405,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    28,    29,
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
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,    -1,    -1,   357,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,   378,    -1,
     380,   381,    -1,    -1,    -1,    -1,   386,   387,   388,   389,
     390,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     400,   401,   402,   403,   404,   405,     3,     4,     5,     6,
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
     347,   348,   349,   350,   351,   352,   353,   354,    -1,    -1,
     357,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   376,
      -1,   378,    -1,   380,    -1,    -1,    -1,    -1,    -1,   386,
     387,   388,   389,   390,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   400,   401,   402,   403,   404,   405,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
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
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,    -1,    -1,   357,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   376,    -1,   378,    -1,   380,    -1,    -1,    -1,
      -1,    -1,   386,   387,   388,   389,   390,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   400,   401,   402,   403,
     404,   405,     3,     4,     5,     6,     7,     8,     9,    10,
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
     351,   352,   353,   354,    -1,    -1,   357,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   376,    -1,   378,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   386,   387,   388,   389,   390,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,
     401,   402,   403,   404,   405,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,    37,
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
     338,   339,    -1,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,    -1,    -1,   357,
     358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,   390,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,   401,   402,   403,   404,   405,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
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
     335,   336,   337,   338,   339,    -1,    -1,   342,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   400,   401,   402,   403,   404,
     405,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
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
     332,   333,   334,   335,   336,   337,   338,   339,    -1,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,    -1,    -1,   357,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,   389,   390,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,   401,
     402,   403,   404,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
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
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
      -1,   341,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     400,   401,   402,   403,   404,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,    37,
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
     338,   339,    -1,    -1,   342,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,   401,   402,   403,   404,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,
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
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,    -1,    -1,   342,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   400,   401,   402,   403,   404,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
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
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,    -1,    -1,   342,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   381,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   400,   401,   402,   403,
     404,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
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
     332,   333,   334,   335,   336,   337,   338,   339,    -1,    -1,
     342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,   401,
     402,   403,   404,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     332,   333,   334,   335,   336,   337,   338,   339,    -1,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,    -1,    -1,   357,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,   380,   381,
      -1,    -1,    -1,    -1,    -1,   387,   388,   389,   390,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   132,   133,   134,   135,
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
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,    -1,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,    -1,
      -1,   357,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     376,    -1,    -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   387,   388,   389,   390,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   132,   133,   134,   135,   136,   137,   138,   139,
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
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
      -1,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,    -1,    -1,   357,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,
     380,    -1,    -1,    -1,    -1,    -1,    -1,   387,   388,   389,
     390,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,   133,
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
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,    -1,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,    -1,    -1,   357,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   376,    -1,    -1,   379,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   387,   388,   389,   390,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,   137,
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
     338,   339,    -1,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,    -1,    -1,   357,
     358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,   390,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     332,   333,   334,   335,   336,   337,   338,   339,    -1,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,    -1,    -1,   357,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   387,   388,   389,   390,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   132,   133,   134,   135,
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
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,    -1,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,    -1,
      -1,   357,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   387,   388,   389,   390,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   132,   133,   134,   135,   136,   137,   138,   139,
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
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
      -1,    -1,   342
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      33,    35,    36,    37,    38,    39,    40,    41,    42,    43,
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
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   342,   386,   400,   401,
     402,   403,   404,   405,   440,   441,   444,   445,   446,   447,
     451,   452,   453,   454,   455,   456,   459,   460,   461,   462,
     463,   465,   470,   471,   472,   513,   514,   515,   376,   376,
     341,   380,   471,   341,   386,   386,   516,   377,   383,   448,
     449,   450,   460,   465,   383,   386,   341,   341,   386,   461,
     465,   394,   467,   468,     0,   514,   341,   464,    82,   341,
     457,   458,   380,   474,   465,   378,   386,   466,   380,   492,
     449,   448,   450,   341,   341,   376,   385,   466,   380,   383,
     386,   443,   341,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   357,   358,   376,   387,   388,
     389,   390,   410,   411,   412,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   463,   465,   469,   466,   377,   383,
     385,   377,   383,   473,   460,   465,   475,   476,   386,   379,
     421,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   378,   386,    22,    23,    24,    26,    27,
      28,    29,    30,    31,    32,    34,   340,   378,   380,   381,
     386,   421,   434,   436,   438,   440,   444,   463,   465,   481,
     482,   483,   484,   485,   493,   494,   495,   496,   499,   500,
     503,   504,   505,   512,   517,   466,   385,   466,   380,   436,
     479,   385,   442,   341,   383,   386,   421,   421,   438,   357,
     358,   378,   382,   377,   377,   383,   339,   436,   376,   421,
     383,   395,   341,   434,   439,   458,   475,   465,   341,   477,
     478,   381,   476,   391,   392,   393,   388,   390,   355,   356,
     359,   360,   394,   395,   361,   362,   398,   397,   396,   363,
     365,   364,   399,   379,   379,   434,   386,   386,   507,   376,
     376,   386,   386,   438,   376,   438,   384,   386,   376,   378,
     381,   486,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   385,   437,   383,   386,   381,   482,   496,   500,
     505,   479,   385,   479,   480,   479,   475,   341,   377,   413,
     438,   341,   436,   421,   381,   477,   466,   383,   386,   421,
     421,   421,   423,   423,   424,   424,   425,   425,   425,   425,
     426,   426,   427,   428,   429,   430,   431,   432,   435,   379,
     482,   508,   438,   386,   438,   384,   506,   341,   518,   519,
     493,   436,   436,   479,   381,   383,   381,   379,   386,   478,
     438,   340,   481,   494,   509,   377,   377,   438,   453,   460,
     498,   376,   379,   383,   487,   381,   479,   384,   376,   498,
     510,   511,   489,   490,   491,   497,   501,   341,   377,   439,
     379,   519,   381,   436,   438,   386,   377,    25,   485,   483,
     380,   385,   483,   488,   492,   377,   377,   438,   488,   489,
     493,   502,   479,   386,   381
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   409,   410,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   412,   412,   412,
     412,   412,   412,   413,   414,   415,   416,   416,   417,   417,
     418,   418,   419,   420,   420,   420,   421,   421,   421,   421,
     422,   422,   422,   422,   423,   423,   423,   423,   424,   424,
     424,   425,   425,   425,   426,   426,   426,   426,   426,   427,
     427,   427,   428,   428,   429,   429,   430,   430,   431,   431,
     432,   432,   433,   433,   434,   435,   434,   436,   436,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     438,   438,   439,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   442,   441,   443,   443,   444,   445,   445,   446,
     446,   447,   448,   448,   449,   449,   449,   449,   450,   451,
     451,   451,   451,   451,   452,   452,   452,   452,   452,   453,
     453,   454,   455,   455,   455,   455,   455,   455,   455,   455,
     456,   457,   457,   458,   458,   458,   459,   460,   460,   461,
     461,   461,   461,   461,   461,   461,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   463,   464,   464,   465,   465,
     466,   466,   466,   466,   467,   467,   468,   469,   469,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   471,   471,   471,
     473,   472,   474,   472,   475,   475,   476,   476,   477,   477,
     478,   478,   479,   479,   479,   480,   480,   481,   482,   482,
     483,   483,   483,   483,   483,   483,   483,   483,   484,   485,
     486,   487,   485,   488,   488,   490,   489,   491,   489,   492,
     492,   493,   493,   494,   494,   495,   495,   496,   497,   497,
     498,   498,   499,   499,   501,   500,   502,   502,   503,   503,
     504,   504,   506,   505,   507,   505,   508,   505,   509,   509,
     510,   510,   511,   511,   512,   512,   512,   512,   512,   513,
     513,   514,   514,   514,   516,   515,   517,   518,   518,   519,
     519
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       0,     0,     5,     1,     1,     0,     2,     0,     2,     2,
       3,     1,     2,     1,     2,     1,     2,     5,     3,     1,
       1,     4,     1,     2,     0,     8,     0,     1,     3,     2,
       1,     2,     0,     6,     0,     8,     0,     7,     1,     1,
       1,     0,     2,     3,     2,     2,     2,     3,     2,     1,
       2,     1,     1,     1,     0,     3,     5,     1,     3,     1,
       4
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
#line 4171 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 308 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4179 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 311 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4188 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 315 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4197 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 319 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4205 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 322 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4214 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 326 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 4223 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 330 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 4232 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 334 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4241 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 338 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4250 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 342 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 4258 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 345 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 4267 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 349 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
    }
#line 4276 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 353 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 4284 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 356 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 4294 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 364 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4302 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 367 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 4310 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 370 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4318 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 373 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 4326 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 376 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4336 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 381 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4346 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 389 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.integerCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4355 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 396 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 4364 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 403 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4372 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 409 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4381 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 413 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4390 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 420 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4398 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 423 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4406 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
#line 4418 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
#line 4430 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 446 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4438 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 454 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4448 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
#line 4480 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 486 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4490 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 494 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 4501 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 500 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4510 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 504 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4519 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
#line 4540 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 528 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 4546 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 529 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 4552 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 530 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 4558 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 531 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 4565 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 537 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4571 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 538 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4581 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 543 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4591 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 548 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4602 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 557 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4608 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 558 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4618 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 563 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4628 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 571 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4634 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 572 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4645 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 578 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4656 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 587 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4662 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 588 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4672 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 593 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4682 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 598 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4692 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 603 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4702 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 611 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4708 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 612 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4722 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 621 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4736 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 633 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4742 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 634 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4753 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 643 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4759 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 644 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4770 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 653 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4776 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 654 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4787 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 663 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4793 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 664 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4803 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 672 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4809 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 673 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4819 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 681 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4825 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 682 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4835 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 690 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4841 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 691 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 4849 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 694 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 4866 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 709 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4872 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 710 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 4890 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 726 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 4899 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 730 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 4908 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 734 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 4917 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 738 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 4927 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 743 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 4936 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 747 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 4945 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 751 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 4954 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 755 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 4963 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 759 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 4972 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 763 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 4981 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 767 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 4990 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 774 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4998 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 777 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 5011 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 788 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5020 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 795 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 5030 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 800 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 5040 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 805 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 5053 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 813 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
        (yyval.interm.intermNode) = 0;
    }
#line 5062 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 817 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5071 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 821 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    }
#line 5080 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 825 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 5090 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 830 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5100 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 835 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).shaderQualifiers);
        (yyvsp[-1].interm.identifierList)->push_back((yyvsp[-2].lex).string);
        parseContext.addQualifierToExisting((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 5111 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 844 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 5117 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 844 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 5131 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 855 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5140 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 859 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5149 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 866 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 5158 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 873 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5166 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 876 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5174 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 883 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 5187 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 891 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5209 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 911 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5233 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 934 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5253 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 949 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5277 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 974 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 5293 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 985 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5305 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 995 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 5320 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1005 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5332 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1015 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 5343 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1024 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 5351 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1027 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
    }
#line 5360 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1031 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
    }
#line 5369 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1035 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5379 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1040 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5389 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1048 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 5399 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1053 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
    }
#line 5409 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1058 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
    }
#line 5419 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1063 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5429 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1068 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5439 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1077 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    }
#line 5455 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1088 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5484 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1115 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 5495 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1124 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 5507 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1131 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 5519 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1138 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5535 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1149 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    }
#line 5549 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1158 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5564 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1168 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5581 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1180 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perviewNV");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangMeshNV, "perviewNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perViewNV = true;
#endif
    }
#line 5595 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1189 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskNVMask | EShLangMeshNVMask), "taskNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perTaskNV = true;
#endif
    }
#line 5609 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1201 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 5617 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1207 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5625 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1210 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5635 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1217 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 5644 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1221 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 5653 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1225 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 5663 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1233 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 5674 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1242 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5682 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1245 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5695 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1256 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5703 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1259 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5711 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1262 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5720 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1266 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5729 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1270 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5738 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1274 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5747 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1278 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5755 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1284 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 5764 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1288 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5781 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1300 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5800 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1314 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 5810 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1319 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 5821 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1325 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 5832 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1331 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 5844 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1338 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 5855 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1344 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 5865 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1349 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 5875 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1354 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 5885 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1359 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5900 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1369 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5915 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1379 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5930 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 1389 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5945 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1399 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableNVMask), "callableDataInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataInNV;
#endif
    }
#line 5959 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1408 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 5976 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1420 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 5985 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1424 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "devicecoherent");
        (yyval.interm.type).qualifier.devicecoherent = true;
    }
#line 5995 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1429 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "queuefamilycoherent");
        (yyval.interm.type).qualifier.queuefamilycoherent = true;
    }
#line 6005 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1434 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "workgroupcoherent");
        (yyval.interm.type).qualifier.workgroupcoherent = true;
    }
#line 6015 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1439 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "subgroupcoherent");
        (yyval.interm.type).qualifier.subgroupcoherent = true;
    }
#line 6025 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 1444 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "nonprivate");
        (yyval.interm.type).qualifier.nonprivate = true;
    }
#line 6035 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 1449 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 6044 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 1453 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 6053 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1457 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 6062 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1461 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 6071 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1465 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 6082 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1471 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 6093 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 1480 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nonUniform = true;
    }
#line 6102 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 1487 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // TODO
    }
#line 6110 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1490 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 6120 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 1498 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[0].interm.typeParameters);
    }
#line 6130 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1503 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes);
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[-1].interm.typeParameters);
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
    }
#line 6142 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 1513 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6152 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 1518 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6165 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 1526 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6174 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1530 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6186 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1540 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[0].interm.typeParameters);
    }
#line 6194 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1543 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = 0;
    }
#line 6202 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1549 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[-1].interm.typeParameters);
    }
#line 6210 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1555 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter");
        (yyval.interm.typeParameters)->addInnerSize(size);
    }
#line 6222 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1562 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeParameters) = (yyvsp[-2].interm.typeParameters);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter");
        (yyval.interm.typeParameters)->addInnerSize(size);
    }
#line 6234 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1572 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 6243 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 1576 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6252 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 1580 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6262 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1585 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "float16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
    }
#line 6272 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1590 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6282 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 1595 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6292 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 1600 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6301 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1604 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6311 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1609 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
    }
#line 6321 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1614 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
    }
#line 6331 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1619 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
    }
#line 6341 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1624 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
    }
#line 6351 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 1629 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6361 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1634 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6371 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 1639 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 6381 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 1644 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 6391 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1649 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 6400 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1653 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6410 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 1658 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6420 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1663 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6430 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 1668 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6441 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 1674 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6452 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1680 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6463 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1686 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 6474 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1692 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 6485 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1698 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 6496 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1704 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6507 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 1710 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6518 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 1716 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6529 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1722 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6540 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1728 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6551 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1734 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6562 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1740 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 6572 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1745 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 6582 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 1750 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 6592 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1755 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6602 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1760 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6612 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1765 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6622 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 1770 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(2);
    }
#line 6633 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1776 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(3);
    }
#line 6644 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1782 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(4);
    }
#line 6655 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 1788 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
    }
#line 6666 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 1794 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
    }
#line 6677 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1800 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
    }
#line 6688 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1806 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6699 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1812 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6710 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1818 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6721 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 1824 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 6732 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1830 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 6743 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1836 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 6754 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 1842 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6765 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1848 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6776 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1854 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6787 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1860 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(2);
    }
#line 6798 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1866 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(3);
    }
#line 6809 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 1872 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(4);
    }
#line 6820 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1878 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
    }
#line 6831 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 1884 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
    }
#line 6842 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 1890 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
    }
#line 6853 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 1896 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6864 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1902 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6875 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1908 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6886 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1914 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 6897 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1920 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 6908 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 1926 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 6919 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1932 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6929 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 1937 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6939 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 1942 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 6949 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1947 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6959 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 1952 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 6969 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1957 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 6979 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 1962 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 6989 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 1967 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6999 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 1972 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7009 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 1977 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7019 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 1982 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7029 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 1987 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7039 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1992 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7050 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1998 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7061 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 2004 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7072 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 2010 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7083 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 2016 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7094 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 2022 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7105 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 2028 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7116 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 2034 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7127 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 2040 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7138 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 2046 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7149 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 2052 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7160 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 2058 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7171 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 2064 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7182 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 2070 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7193 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 2076 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7204 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 2082 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7215 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 2088 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7226 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 2094 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7237 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 2100 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7248 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 2106 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7259 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 2112 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7270 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 2118 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7281 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 2124 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7292 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 2130 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7303 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 2136 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7314 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 2142 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7325 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 2148 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7336 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 2154 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7347 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 2160 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7358 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 2166 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7369 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 306:
#line 2172 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7380 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 2178 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7391 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 2184 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7402 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 2190 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7413 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 2196 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7424 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 2202 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7435 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 2208 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7446 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 2214 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7457 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 2220 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7468 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 2226 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7479 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 2232 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7490 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 2238 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7501 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 2244 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7512 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 2250 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7523 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 2256 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7534 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 2262 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7545 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 2268 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7556 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 2274 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7567 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 324:
#line 2280 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef NV_EXTENSIONS
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStructNV;
#endif
    }
#line 7578 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 2286 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 7588 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 2291 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 7598 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 2296 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 7608 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 328:
#line 2301 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 7618 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 2306 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 7628 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 2311 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 7638 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 2316 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 7648 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 2321 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 7658 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 2326 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 7668 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 2331 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 7678 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 2336 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 7688 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 2341 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 7698 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 2346 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 7708 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 2351 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 7718 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 339:
#line 2356 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
#endif
    }
#line 7731 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 340:
#line 2364 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
#endif
    }
#line 7744 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 341:
#line 2372 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
#endif
    }
#line 7757 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 342:
#line 2380 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
#endif
    }
#line 7770 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 343:
#line 2388 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
#endif
    }
#line 7783 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 344:
#line 2396 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
#endif
    }
#line 7796 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 345:
#line 2404 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
#endif
    }
#line 7809 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 346:
#line 2412 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
#endif
    }
#line 7822 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 347:
#line 2420 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
#endif
    }
#line 7835 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 348:
#line 2428 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
#endif
    }
#line 7848 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 349:
#line 2436 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
#endif
    }
#line 7861 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 350:
#line 2444 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
#endif
    }
#line 7874 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 351:
#line 2452 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
#endif
    }
#line 7887 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 352:
#line 2460 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 7897 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 353:
#line 2465 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 7907 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 354:
#line 2470 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 7917 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 355:
#line 2475 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 7927 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 356:
#line 2480 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 7937 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 357:
#line 2485 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 7947 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 358:
#line 2490 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 7957 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 359:
#line 2495 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 7967 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 360:
#line 2500 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 7977 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 361:
#line 2505 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 7987 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 362:
#line 2510 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 7997 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 363:
#line 2515 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 8007 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 364:
#line 2520 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 8017 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 365:
#line 2525 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 8027 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 366:
#line 2530 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 8037 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 367:
#line 2535 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 8047 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 368:
#line 2540 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
#endif
    }
#line 8060 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 369:
#line 2548 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
#endif
    }
#line 8073 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 370:
#line 2556 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 8083 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 371:
#line 2561 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 8093 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 372:
#line 2566 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 8103 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 373:
#line 2571 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
#endif
    }
#line 8116 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 374:
#line 2579 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 8126 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 375:
#line 2584 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 8136 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 376:
#line 2589 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 8146 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 377:
#line 2594 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8159 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 378:
#line 2602 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 8169 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 379:
#line 2607 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 8179 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 380:
#line 2612 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 8189 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 381:
#line 2617 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8202 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 382:
#line 2625 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 8212 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 383:
#line 2630 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 8222 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 384:
#line 2635 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 8232 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 385:
#line 2640 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 8242 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 386:
#line 2645 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 8252 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 387:
#line 2650 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
#endif
    }
#line 8265 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 388:
#line 2658 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 8275 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 389:
#line 2663 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
#endif
    }
#line 8288 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 390:
#line 2671 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 8298 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 391:
#line 2676 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
#endif
    }
#line 8311 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 392:
#line 2684 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 8321 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 393:
#line 2689 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
#endif
    }
#line 8334 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 394:
#line 2697 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 8344 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 395:
#line 2702 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
#endif
    }
#line 8357 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 396:
#line 2710 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 8367 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 397:
#line 2715 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
#endif
    }
#line 8380 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 398:
#line 2723 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 8390 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 399:
#line 2728 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
#endif
    }
#line 8403 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 400:
#line 2736 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 8413 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 401:
#line 2741 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 8423 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 402:
#line 2746 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 8433 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 403:
#line 2751 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 8443 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 404:
#line 2756 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 8453 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 405:
#line 2761 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 8463 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 406:
#line 2766 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 8473 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 407:
#line 2771 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 8483 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 408:
#line 2776 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 8493 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 409:
#line 2781 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 8503 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 410:
#line 2786 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 8513 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 411:
#line 2791 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 8523 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 412:
#line 2796 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 8533 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 413:
#line 2801 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 8543 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 414:
#line 2806 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 8553 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 415:
#line 2811 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
#endif
    }
#line 8566 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 416:
#line 2819 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 8576 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 417:
#line 2824 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 8586 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 418:
#line 2829 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 8596 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 419:
#line 2834 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
#endif
    }
#line 8609 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 420:
#line 2842 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 8619 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 421:
#line 2847 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 8629 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 422:
#line 2852 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 8639 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 423:
#line 2857 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8652 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 424:
#line 2865 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 8662 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 425:
#line 2870 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 8672 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 426:
#line 2875 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 8682 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 427:
#line 2880 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8695 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 428:
#line 2888 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 8705 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 429:
#line 2893 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 8715 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 430:
#line 2898 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 8725 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 431:
#line 2903 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
#endif
    }
#line 8738 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 432:
#line 2911 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 8748 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 433:
#line 2916 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 8758 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 434:
#line 2921 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 8768 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 435:
#line 2926 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
#endif
    }
#line 8781 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 436:
#line 2934 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 8791 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 437:
#line 2939 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 8801 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 438:
#line 2944 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 8811 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 439:
#line 2949 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
#endif
    }
#line 8824 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 440:
#line 2957 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 8834 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 441:
#line 2962 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 8844 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 442:
#line 2967 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 8854 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 443:
#line 2972 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
#endif
    }
#line 8867 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 444:
#line 2980 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 8877 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 445:
#line 2985 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 8887 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 446:
#line 2990 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 8897 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 447:
#line 2995 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
#endif
    }
#line 8910 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 448:
#line 3003 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 8920 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 449:
#line 3008 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 8930 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 450:
#line 3013 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 8940 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 451:
#line 3018 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
#endif
    }
#line 8953 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 452:
#line 3026 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 8963 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 453:
#line 3031 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 8973 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 454:
#line 3036 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 8983 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 455:
#line 3041 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
#endif
    }
#line 8996 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 456:
#line 3049 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 9006 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 457:
#line 3054 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 9016 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 458:
#line 3059 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 9026 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 459:
#line 3064 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
#endif
    }
#line 9039 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 460:
#line 3072 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 9049 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 461:
#line 3077 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 9059 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 462:
#line 3082 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 9069 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 463:
#line 3087 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
#endif
    }
#line 9082 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 464:
#line 3095 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 9092 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 465:
#line 3100 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 9102 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 466:
#line 3105 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 9112 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 467:
#line 3110 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 9125 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 468:
#line 3118 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 9135 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 469:
#line 3123 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 9145 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 470:
#line 3128 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 9155 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 471:
#line 3133 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 9168 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 472:
#line 3141 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 9178 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 473:
#line 3146 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 9188 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 474:
#line 3151 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 9199 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 475:
#line 3157 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { // GL_EXT_YUV_target
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.yuv = true;
    }
#line 9210 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 476:
#line 3163 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 9221 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 477:
#line 3169 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 9232 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 478:
#line 3175 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
#endif
    }
#line 9246 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 479:
#line 3184 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
#endif
    }
#line 9260 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 480:
#line 3193 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 9271 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 481:
#line 3199 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 9282 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 482:
#line 3205 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 9293 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 483:
#line 3211 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 9304 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 484:
#line 3217 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.fcoopmatCheck((yyvsp[0].lex).loc, "fcoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).coopmat = true;
    }
#line 9315 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 485:
#line 3223 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 9325 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 486:
#line 3228 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9343 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 487:
#line 3244 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 9353 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 488:
#line 3249 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 9363 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 489:
#line 3254 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 9373 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 490:
#line 3262 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 9379 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 491:
#line 3262 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9395 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 492:
#line 3273 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 9401 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 493:
#line 3273 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 9413 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 494:
#line 3283 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 9421 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 495:
#line 3286 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9436 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 496:
#line 3299 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9463 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 497:
#line 3321 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9492 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 498:
#line 3348 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9501 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 499:
#line 3352 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9509 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 500:
#line 3358 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 9519 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 501:
#line 3363 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->transferArraySizes((yyvsp[0].interm).arraySizes);
    }
#line 9532 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 502:
#line 3374 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 9540 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 503:
#line 3377 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 9551 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 504:
#line 3383 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 9562 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 505:
#line 3392 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 9570 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 506:
#line 3395 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 9578 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 507:
#line 3401 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9584 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 508:
#line 3405 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9590 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 509:
#line 3406 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9596 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 510:
#line 3412 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9602 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 511:
#line 3413 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9608 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 512:
#line 3414 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9614 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 513:
#line 3415 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9620 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 514:
#line 3416 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9626 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 515:
#line 3417 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9632 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 516:
#line 3418 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9638 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 517:
#line 3419 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9644 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 518:
#line 3423 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "demote");
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 1, &E_GL_EXT_demote_to_helper_invocation, "demote");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDemote, (yyvsp[-1].lex).loc);
    }
#line 9654 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 519:
#line 3431 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 9660 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 520:
#line 3432 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 9669 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 521:
#line 3436 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 9678 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 522:
#line 3440 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate())
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 9688 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 523:
#line 3448 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9694 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 524:
#line 3449 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9700 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 525:
#line 3453 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 9708 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 526:
#line 3456 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9717 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 527:
#line 3460 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9727 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 528:
#line 3465 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9738 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 529:
#line 3474 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9746 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 530:
#line 3477 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate())
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 9756 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 531:
#line 3485 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 9769 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 532:
#line 3493 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 9782 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 533:
#line 3504 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 9788 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 534:
#line 3505 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 9794 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 535:
#line 3509 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9802 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 536:
#line 3512 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9811 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 537:
#line 3518 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 9820 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 538:
#line 3525 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 9829 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 539:
#line 3529 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 9838 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 540:
#line 3537 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 9847 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 541:
#line 3541 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    }
#line 9862 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 542:
#line 3554 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9870 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 543:
#line 3557 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9879 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 544:
#line 3563 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 9892 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 545:
#line 3571 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9906 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 546:
#line 3583 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9914 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 547:
#line 3586 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9922 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 548:
#line 3592 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 9939 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 549:
#line 3604 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 9953 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 550:
#line 3616 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9961 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 551:
#line 3619 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9970 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 552:
#line 3625 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9983 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 553:
#line 3633 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, true, (yyvsp[-5].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9995 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 554:
#line 3640 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 10005 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 555:
#line 3645 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 10021 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 556:
#line 3656 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 10032 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 557:
#line 3662 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 10049 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 558:
#line 3677 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10057 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 559:
#line 3680 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10065 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 560:
#line 3686 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 10073 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 561:
#line 3689 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = 0;
    }
#line 10081 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 562:
#line 3695 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 10090 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 563:
#line 3699 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 10099 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 564:
#line 3706 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 10109 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 565:
#line 3711 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 10119 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 566:
#line 3716 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 10131 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 567:
#line 3723 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10139 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 568:
#line 3726 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 10148 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 569:
#line 3735 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 10157 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 570:
#line 3739 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 10168 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 571:
#line 3748 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10176 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 572:
#line 3751 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10184 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 573:
#line 3754 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 10194 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 574:
#line 3762 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);
    }
#line 10203 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 575:
#line 3766 "MachineIndependent/glslang.y" /* yacc.c:1646  */
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
#line 10223 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 576:
#line 3784 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
        parseContext.requireExtensions((yyvsp[-4].lex).loc, 1, &E_GL_EXT_control_flow_attributes, "attribute");
    }
#line 10232 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 577:
#line 3790 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 10240 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 578:
#line 3793 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 10248 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 579:
#line 3798 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 10256 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 580:
#line 3801 "MachineIndependent/glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10264 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
    break;


#line 10268 "MachineIndependent/glslang_tab.cpp" /* yacc.c:1646  */
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
#line 3805 "MachineIndependent/glslang.y" /* yacc.c:1906  */


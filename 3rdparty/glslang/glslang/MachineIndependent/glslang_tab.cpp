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
#line 41 "glslang.y" /* yacc.c:339  */


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


#line 92 "glslang_tab.cpp" /* yacc.c:339  */

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
#ifndef YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
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
    CONST = 260,
    BOOL = 261,
    FLOAT = 262,
    DOUBLE = 263,
    INT = 264,
    UINT = 265,
    INT64_T = 266,
    UINT64_T = 267,
    INT16_T = 268,
    UINT16_T = 269,
    FLOAT16_T = 270,
    BREAK = 271,
    CONTINUE = 272,
    DO = 273,
    ELSE = 274,
    FOR = 275,
    IF = 276,
    DISCARD = 277,
    RETURN = 278,
    SWITCH = 279,
    CASE = 280,
    DEFAULT = 281,
    SUBROUTINE = 282,
    BVEC2 = 283,
    BVEC3 = 284,
    BVEC4 = 285,
    IVEC2 = 286,
    IVEC3 = 287,
    IVEC4 = 288,
    I64VEC2 = 289,
    I64VEC3 = 290,
    I64VEC4 = 291,
    UVEC2 = 292,
    UVEC3 = 293,
    UVEC4 = 294,
    U64VEC2 = 295,
    U64VEC3 = 296,
    U64VEC4 = 297,
    VEC2 = 298,
    VEC3 = 299,
    VEC4 = 300,
    MAT2 = 301,
    MAT3 = 302,
    MAT4 = 303,
    CENTROID = 304,
    IN = 305,
    OUT = 306,
    INOUT = 307,
    UNIFORM = 308,
    PATCH = 309,
    SAMPLE = 310,
    BUFFER = 311,
    SHARED = 312,
    COHERENT = 313,
    VOLATILE = 314,
    RESTRICT = 315,
    READONLY = 316,
    WRITEONLY = 317,
    DVEC2 = 318,
    DVEC3 = 319,
    DVEC4 = 320,
    DMAT2 = 321,
    DMAT3 = 322,
    DMAT4 = 323,
    F16VEC2 = 324,
    F16VEC3 = 325,
    F16VEC4 = 326,
    F16MAT2 = 327,
    F16MAT3 = 328,
    F16MAT4 = 329,
    I16VEC2 = 330,
    I16VEC3 = 331,
    I16VEC4 = 332,
    U16VEC2 = 333,
    U16VEC3 = 334,
    U16VEC4 = 335,
    NOPERSPECTIVE = 336,
    FLAT = 337,
    SMOOTH = 338,
    LAYOUT = 339,
    __EXPLICITINTERPAMD = 340,
    MAT2X2 = 341,
    MAT2X3 = 342,
    MAT2X4 = 343,
    MAT3X2 = 344,
    MAT3X3 = 345,
    MAT3X4 = 346,
    MAT4X2 = 347,
    MAT4X3 = 348,
    MAT4X4 = 349,
    DMAT2X2 = 350,
    DMAT2X3 = 351,
    DMAT2X4 = 352,
    DMAT3X2 = 353,
    DMAT3X3 = 354,
    DMAT3X4 = 355,
    DMAT4X2 = 356,
    DMAT4X3 = 357,
    DMAT4X4 = 358,
    F16MAT2X2 = 359,
    F16MAT2X3 = 360,
    F16MAT2X4 = 361,
    F16MAT3X2 = 362,
    F16MAT3X3 = 363,
    F16MAT3X4 = 364,
    F16MAT4X2 = 365,
    F16MAT4X3 = 366,
    F16MAT4X4 = 367,
    ATOMIC_UINT = 368,
    SAMPLER1D = 369,
    SAMPLER2D = 370,
    SAMPLER3D = 371,
    SAMPLERCUBE = 372,
    SAMPLER1DSHADOW = 373,
    SAMPLER2DSHADOW = 374,
    SAMPLERCUBESHADOW = 375,
    SAMPLER1DARRAY = 376,
    SAMPLER2DARRAY = 377,
    SAMPLER1DARRAYSHADOW = 378,
    SAMPLER2DARRAYSHADOW = 379,
    ISAMPLER1D = 380,
    ISAMPLER2D = 381,
    ISAMPLER3D = 382,
    ISAMPLERCUBE = 383,
    ISAMPLER1DARRAY = 384,
    ISAMPLER2DARRAY = 385,
    USAMPLER1D = 386,
    USAMPLER2D = 387,
    USAMPLER3D = 388,
    USAMPLERCUBE = 389,
    USAMPLER1DARRAY = 390,
    USAMPLER2DARRAY = 391,
    SAMPLER2DRECT = 392,
    SAMPLER2DRECTSHADOW = 393,
    ISAMPLER2DRECT = 394,
    USAMPLER2DRECT = 395,
    SAMPLERBUFFER = 396,
    ISAMPLERBUFFER = 397,
    USAMPLERBUFFER = 398,
    SAMPLERCUBEARRAY = 399,
    SAMPLERCUBEARRAYSHADOW = 400,
    ISAMPLERCUBEARRAY = 401,
    USAMPLERCUBEARRAY = 402,
    SAMPLER2DMS = 403,
    ISAMPLER2DMS = 404,
    USAMPLER2DMS = 405,
    SAMPLER2DMSARRAY = 406,
    ISAMPLER2DMSARRAY = 407,
    USAMPLER2DMSARRAY = 408,
    SAMPLEREXTERNALOES = 409,
    F16SAMPLER1D = 410,
    F16SAMPLER2D = 411,
    F16SAMPLER3D = 412,
    F16SAMPLER2DRECT = 413,
    F16SAMPLERCUBE = 414,
    F16SAMPLER1DARRAY = 415,
    F16SAMPLER2DARRAY = 416,
    F16SAMPLERCUBEARRAY = 417,
    F16SAMPLERBUFFER = 418,
    F16SAMPLER2DMS = 419,
    F16SAMPLER2DMSARRAY = 420,
    F16SAMPLER1DSHADOW = 421,
    F16SAMPLER2DSHADOW = 422,
    F16SAMPLER1DARRAYSHADOW = 423,
    F16SAMPLER2DARRAYSHADOW = 424,
    F16SAMPLER2DRECTSHADOW = 425,
    F16SAMPLERCUBESHADOW = 426,
    F16SAMPLERCUBEARRAYSHADOW = 427,
    SAMPLER = 428,
    SAMPLERSHADOW = 429,
    TEXTURE1D = 430,
    TEXTURE2D = 431,
    TEXTURE3D = 432,
    TEXTURECUBE = 433,
    TEXTURE1DARRAY = 434,
    TEXTURE2DARRAY = 435,
    ITEXTURE1D = 436,
    ITEXTURE2D = 437,
    ITEXTURE3D = 438,
    ITEXTURECUBE = 439,
    ITEXTURE1DARRAY = 440,
    ITEXTURE2DARRAY = 441,
    UTEXTURE1D = 442,
    UTEXTURE2D = 443,
    UTEXTURE3D = 444,
    UTEXTURECUBE = 445,
    UTEXTURE1DARRAY = 446,
    UTEXTURE2DARRAY = 447,
    TEXTURE2DRECT = 448,
    ITEXTURE2DRECT = 449,
    UTEXTURE2DRECT = 450,
    TEXTUREBUFFER = 451,
    ITEXTUREBUFFER = 452,
    UTEXTUREBUFFER = 453,
    TEXTURECUBEARRAY = 454,
    ITEXTURECUBEARRAY = 455,
    UTEXTURECUBEARRAY = 456,
    TEXTURE2DMS = 457,
    ITEXTURE2DMS = 458,
    UTEXTURE2DMS = 459,
    TEXTURE2DMSARRAY = 460,
    ITEXTURE2DMSARRAY = 461,
    UTEXTURE2DMSARRAY = 462,
    F16TEXTURE1D = 463,
    F16TEXTURE2D = 464,
    F16TEXTURE3D = 465,
    F16TEXTURE2DRECT = 466,
    F16TEXTURECUBE = 467,
    F16TEXTURE1DARRAY = 468,
    F16TEXTURE2DARRAY = 469,
    F16TEXTURECUBEARRAY = 470,
    F16TEXTUREBUFFER = 471,
    F16TEXTURE2DMS = 472,
    F16TEXTURE2DMSARRAY = 473,
    SUBPASSINPUT = 474,
    SUBPASSINPUTMS = 475,
    ISUBPASSINPUT = 476,
    ISUBPASSINPUTMS = 477,
    USUBPASSINPUT = 478,
    USUBPASSINPUTMS = 479,
    F16SUBPASSINPUT = 480,
    F16SUBPASSINPUTMS = 481,
    IMAGE1D = 482,
    IIMAGE1D = 483,
    UIMAGE1D = 484,
    IMAGE2D = 485,
    IIMAGE2D = 486,
    UIMAGE2D = 487,
    IMAGE3D = 488,
    IIMAGE3D = 489,
    UIMAGE3D = 490,
    IMAGE2DRECT = 491,
    IIMAGE2DRECT = 492,
    UIMAGE2DRECT = 493,
    IMAGECUBE = 494,
    IIMAGECUBE = 495,
    UIMAGECUBE = 496,
    IMAGEBUFFER = 497,
    IIMAGEBUFFER = 498,
    UIMAGEBUFFER = 499,
    IMAGE1DARRAY = 500,
    IIMAGE1DARRAY = 501,
    UIMAGE1DARRAY = 502,
    IMAGE2DARRAY = 503,
    IIMAGE2DARRAY = 504,
    UIMAGE2DARRAY = 505,
    IMAGECUBEARRAY = 506,
    IIMAGECUBEARRAY = 507,
    UIMAGECUBEARRAY = 508,
    IMAGE2DMS = 509,
    IIMAGE2DMS = 510,
    UIMAGE2DMS = 511,
    IMAGE2DMSARRAY = 512,
    IIMAGE2DMSARRAY = 513,
    UIMAGE2DMSARRAY = 514,
    F16IMAGE1D = 515,
    F16IMAGE2D = 516,
    F16IMAGE3D = 517,
    F16IMAGE2DRECT = 518,
    F16IMAGECUBE = 519,
    F16IMAGE1DARRAY = 520,
    F16IMAGE2DARRAY = 521,
    F16IMAGECUBEARRAY = 522,
    F16IMAGEBUFFER = 523,
    F16IMAGE2DMS = 524,
    F16IMAGE2DMSARRAY = 525,
    STRUCT = 526,
    VOID = 527,
    WHILE = 528,
    IDENTIFIER = 529,
    TYPE_NAME = 530,
    FLOATCONSTANT = 531,
    DOUBLECONSTANT = 532,
    INTCONSTANT = 533,
    UINTCONSTANT = 534,
    INT64CONSTANT = 535,
    UINT64CONSTANT = 536,
    INT16CONSTANT = 537,
    UINT16CONSTANT = 538,
    BOOLCONSTANT = 539,
    FLOAT16CONSTANT = 540,
    LEFT_OP = 541,
    RIGHT_OP = 542,
    INC_OP = 543,
    DEC_OP = 544,
    LE_OP = 545,
    GE_OP = 546,
    EQ_OP = 547,
    NE_OP = 548,
    AND_OP = 549,
    OR_OP = 550,
    XOR_OP = 551,
    MUL_ASSIGN = 552,
    DIV_ASSIGN = 553,
    ADD_ASSIGN = 554,
    MOD_ASSIGN = 555,
    LEFT_ASSIGN = 556,
    RIGHT_ASSIGN = 557,
    AND_ASSIGN = 558,
    XOR_ASSIGN = 559,
    OR_ASSIGN = 560,
    SUB_ASSIGN = 561,
    LEFT_PAREN = 562,
    RIGHT_PAREN = 563,
    LEFT_BRACKET = 564,
    RIGHT_BRACKET = 565,
    LEFT_BRACE = 566,
    RIGHT_BRACE = 567,
    DOT = 568,
    COMMA = 569,
    COLON = 570,
    EQUAL = 571,
    SEMICOLON = 572,
    BANG = 573,
    DASH = 574,
    TILDE = 575,
    PLUS = 576,
    STAR = 577,
    SLASH = 578,
    PERCENT = 579,
    LEFT_ANGLE = 580,
    RIGHT_ANGLE = 581,
    VERTICAL_BAR = 582,
    CARET = 583,
    AMPERSAND = 584,
    QUESTION = 585,
    INVARIANT = 586,
    PRECISE = 587,
    HIGH_PRECISION = 588,
    MEDIUM_PRECISION = 589,
    LOW_PRECISION = 590,
    PRECISION = 591,
    PACKED = 592,
    RESOURCE = 593,
    SUPERP = 594
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 69 "glslang.y" /* yacc.c:355  */

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
    } interm;

#line 507 "glslang_tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_GLSLANG_TAB_CPP_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 104 "glslang.y" /* yacc.c:358  */


/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


#line 538 "glslang_tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  316
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7455

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  340
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  106
/* YYNRULES -- Number of rules.  */
#define YYNRULES  503
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  643

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   594

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
     335,   336,   337,   338,   339
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   272,   272,   278,   281,   284,   288,   292,   296,   302,
     308,   311,   315,   321,   324,   332,   335,   338,   341,   344,
     349,   357,   364,   371,   377,   381,   388,   391,   397,   404,
     414,   422,   427,   457,   463,   467,   471,   491,   492,   493,
     494,   500,   501,   506,   511,   520,   521,   526,   534,   535,
     541,   550,   551,   556,   561,   566,   574,   575,   583,   594,
     595,   604,   605,   614,   615,   624,   625,   633,   634,   642,
     643,   651,   652,   652,   670,   671,   686,   690,   694,   698,
     703,   707,   711,   715,   719,   723,   727,   734,   737,   748,
     755,   760,   765,   773,   777,   781,   785,   790,   795,   804,
     804,   815,   819,   826,   833,   836,   843,   851,   871,   894,
     909,   932,   943,   953,   963,   973,   982,   985,   989,   993,
     998,  1006,  1011,  1016,  1021,  1026,  1035,  1046,  1073,  1082,
    1089,  1096,  1103,  1115,  1121,  1124,  1131,  1135,  1139,  1147,
    1156,  1159,  1170,  1173,  1176,  1180,  1184,  1188,  1195,  1199,
    1211,  1225,  1230,  1236,  1242,  1249,  1255,  1260,  1265,  1270,
    1278,  1282,  1286,  1290,  1294,  1298,  1304,  1313,  1316,  1324,
    1328,  1337,  1342,  1350,  1354,  1364,  1368,  1372,  1377,  1384,
    1388,  1393,  1398,  1403,  1410,  1417,  1421,  1426,  1431,  1436,
    1442,  1448,  1454,  1462,  1470,  1478,  1483,  1488,  1493,  1498,
    1503,  1508,  1514,  1520,  1526,  1534,  1542,  1550,  1556,  1562,
    1568,  1574,  1580,  1586,  1594,  1602,  1610,  1615,  1620,  1625,
    1630,  1635,  1640,  1645,  1650,  1655,  1660,  1665,  1670,  1676,
    1682,  1688,  1694,  1700,  1706,  1712,  1718,  1724,  1730,  1736,
    1742,  1750,  1758,  1766,  1774,  1782,  1790,  1798,  1806,  1814,
    1822,  1830,  1838,  1843,  1848,  1853,  1858,  1863,  1868,  1873,
    1878,  1883,  1888,  1893,  1898,  1903,  1908,  1916,  1924,  1932,
    1940,  1948,  1956,  1964,  1972,  1980,  1988,  1996,  2004,  2012,
    2017,  2022,  2027,  2032,  2037,  2042,  2047,  2052,  2057,  2062,
    2067,  2072,  2077,  2082,  2087,  2092,  2100,  2108,  2113,  2118,
    2123,  2131,  2136,  2141,  2146,  2154,  2159,  2164,  2169,  2177,
    2182,  2187,  2192,  2197,  2202,  2210,  2215,  2223,  2228,  2236,
    2241,  2249,  2254,  2262,  2267,  2275,  2280,  2288,  2293,  2298,
    2303,  2308,  2313,  2318,  2323,  2328,  2333,  2338,  2343,  2348,
    2353,  2358,  2363,  2371,  2376,  2381,  2386,  2394,  2399,  2404,
    2409,  2417,  2422,  2427,  2432,  2440,  2445,  2450,  2455,  2463,
    2468,  2473,  2478,  2486,  2491,  2496,  2501,  2509,  2514,  2519,
    2524,  2532,  2537,  2542,  2547,  2555,  2560,  2565,  2570,  2578,
    2583,  2588,  2593,  2601,  2606,  2611,  2616,  2624,  2629,  2634,
    2639,  2647,  2652,  2657,  2662,  2670,  2675,  2680,  2685,  2693,
    2698,  2703,  2709,  2715,  2721,  2730,  2739,  2745,  2751,  2757,
    2763,  2768,  2784,  2789,  2794,  2802,  2802,  2813,  2813,  2823,
    2826,  2839,  2857,  2881,  2885,  2891,  2896,  2907,  2910,  2916,
    2925,  2928,  2934,  2938,  2939,  2945,  2946,  2947,  2948,  2949,
    2950,  2951,  2955,  2956,  2960,  2956,  2972,  2973,  2977,  2977,
    2984,  2984,  2998,  3001,  3009,  3017,  3028,  3029,  3033,  3036,
    3042,  3049,  3053,  3061,  3065,  3078,  3081,  3087,  3087,  3107,
    3110,  3116,  3128,  3140,  3143,  3149,  3149,  3164,  3164,  3180,
    3180,  3201,  3204,  3210,  3213,  3219,  3223,  3230,  3235,  3240,
    3247,  3250,  3259,  3263,  3272,  3275,  3278,  3286,  3286,  3308,
    3314,  3317,  3322,  3325
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "VARYING", "CONST", "BOOL",
  "FLOAT", "DOUBLE", "INT", "UINT", "INT64_T", "UINT64_T", "INT16_T",
  "UINT16_T", "FLOAT16_T", "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF",
  "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "SUBROUTINE", "BVEC2",
  "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "I64VEC2", "I64VEC3",
  "I64VEC4", "UVEC2", "UVEC3", "UVEC4", "U64VEC2", "U64VEC3", "U64VEC4",
  "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID", "IN", "OUT",
  "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED", "COHERENT",
  "VOLATILE", "RESTRICT", "READONLY", "WRITEONLY", "DVEC2", "DVEC3",
  "DVEC4", "DMAT2", "DMAT3", "DMAT4", "F16VEC2", "F16VEC3", "F16VEC4",
  "F16MAT2", "F16MAT3", "F16MAT4", "I16VEC2", "I16VEC3", "I16VEC4",
  "U16VEC2", "U16VEC3", "U16VEC4", "NOPERSPECTIVE", "FLAT", "SMOOTH",
  "LAYOUT", "__EXPLICITINTERPAMD", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2",
  "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3",
  "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3",
  "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "ATOMIC_UINT", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
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
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "F16SAMPLER1D",
  "F16SAMPLER2D", "F16SAMPLER3D", "F16SAMPLER2DRECT", "F16SAMPLERCUBE",
  "F16SAMPLER1DARRAY", "F16SAMPLER2DARRAY", "F16SAMPLERCUBEARRAY",
  "F16SAMPLERBUFFER", "F16SAMPLER2DMS", "F16SAMPLER2DMSARRAY",
  "F16SAMPLER1DSHADOW", "F16SAMPLER2DSHADOW", "F16SAMPLER1DARRAYSHADOW",
  "F16SAMPLER2DARRAYSHADOW", "F16SAMPLER2DRECTSHADOW",
  "F16SAMPLERCUBESHADOW", "F16SAMPLERCUBEARRAYSHADOW", "SAMPLER",
  "SAMPLERSHADOW", "TEXTURE1D", "TEXTURE2D", "TEXTURE3D", "TEXTURECUBE",
  "TEXTURE1DARRAY", "TEXTURE2DARRAY", "ITEXTURE1D", "ITEXTURE2D",
  "ITEXTURE3D", "ITEXTURECUBE", "ITEXTURE1DARRAY", "ITEXTURE2DARRAY",
  "UTEXTURE1D", "UTEXTURE2D", "UTEXTURE3D", "UTEXTURECUBE",
  "UTEXTURE1DARRAY", "UTEXTURE2DARRAY", "TEXTURE2DRECT", "ITEXTURE2DRECT",
  "UTEXTURE2DRECT", "TEXTUREBUFFER", "ITEXTUREBUFFER", "UTEXTUREBUFFER",
  "TEXTURECUBEARRAY", "ITEXTURECUBEARRAY", "UTEXTURECUBEARRAY",
  "TEXTURE2DMS", "ITEXTURE2DMS", "UTEXTURE2DMS", "TEXTURE2DMSARRAY",
  "ITEXTURE2DMSARRAY", "UTEXTURE2DMSARRAY", "F16TEXTURE1D", "F16TEXTURE2D",
  "F16TEXTURE3D", "F16TEXTURE2DRECT", "F16TEXTURECUBE",
  "F16TEXTURE1DARRAY", "F16TEXTURE2DARRAY", "F16TEXTURECUBEARRAY",
  "F16TEXTUREBUFFER", "F16TEXTURE2DMS", "F16TEXTURE2DMSARRAY",
  "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT", "ISUBPASSINPUTMS",
  "USUBPASSINPUT", "USUBPASSINPUTMS", "F16SUBPASSINPUT",
  "F16SUBPASSINPUTMS", "IMAGE1D", "IIMAGE1D", "UIMAGE1D", "IMAGE2D",
  "IIMAGE2D", "UIMAGE2D", "IMAGE3D", "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT",
  "IIMAGE2DRECT", "UIMAGE2DRECT", "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE",
  "IMAGEBUFFER", "IIMAGEBUFFER", "UIMAGEBUFFER", "IMAGE1DARRAY",
  "IIMAGE1DARRAY", "UIMAGE1DARRAY", "IMAGE2DARRAY", "IIMAGE2DARRAY",
  "UIMAGE2DARRAY", "IMAGECUBEARRAY", "IIMAGECUBEARRAY", "UIMAGECUBEARRAY",
  "IMAGE2DMS", "IIMAGE2DMS", "UIMAGE2DMS", "IMAGE2DMSARRAY",
  "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY", "F16IMAGE1D", "F16IMAGE2D",
  "F16IMAGE3D", "F16IMAGE2DRECT", "F16IMAGECUBE", "F16IMAGE1DARRAY",
  "F16IMAGE2DARRAY", "F16IMAGECUBEARRAY", "F16IMAGEBUFFER", "F16IMAGE2DMS",
  "F16IMAGE2DMSARRAY", "STRUCT", "VOID", "WHILE", "IDENTIFIER",
  "TYPE_NAME", "FLOATCONSTANT", "DOUBLECONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "INT64CONSTANT", "UINT64CONSTANT", "INT16CONSTANT",
  "UINT16CONSTANT", "BOOLCONSTANT", "FLOAT16CONSTANT", "LEFT_OP",
  "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP",
  "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "ADD_ASSIGN",
  "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "SUB_ASSIGN", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_BRACE", "RIGHT_BRACE", "DOT", "COMMA", "COLON",
  "EQUAL", "SEMICOLON", "BANG", "DASH", "TILDE", "PLUS", "STAR", "SLASH",
  "PERCENT", "LEFT_ANGLE", "RIGHT_ANGLE", "VERTICAL_BAR", "CARET",
  "AMPERSAND", "QUESTION", "INVARIANT", "PRECISE", "HIGH_PRECISION",
  "MEDIUM_PRECISION", "LOW_PRECISION", "PRECISION", "PACKED", "RESOURCE",
  "SUPERP", "$accept", "variable_identifier", "primary_expression",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_header_no_parameters",
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
  "storage_qualifier", "type_name_list", "type_specifier",
  "array_specifier", "type_specifier_nonarray", "precision_qualifier",
  "struct_specifier", "$@3", "$@4", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "initializer", "initializer_list", "declaration_statement", "statement",
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
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594
};
# endif

#define YYPACT_NINF -451

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-451)))

#define YYTABLE_NINF -449

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -284,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,    29,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,     8,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,    89,  -451,    20,
      28,    58,    60,  4552,    39,  -451,   108,  -451,  -451,  -451,
    -451,  3307,  -451,  -451,  -451,    82,  -451,  -451,   636,  -451,
    -451,   140,   220,   106,  -451,  7180,    11,  -451,  -451,   114,
    -451,  4552,  -451,  -451,  -451,  4552,   155,   160,  -451,  -292,
      51,  -451,  -451,  -451,  5141,   129,  -451,  -451,  -451,    -8,
    -451,   135,    46,  -451,  -451,  4552,   126,  -451,    31,   970,
    -451,  -451,  -451,  -451,    82,  -291,  -451,  5457,     6,  -451,
     171,  -451,    62,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  6405,  6405,  6405,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,    50,  -451,  -451,  -451,   144,    47,
    6707,   146,  -451,  6405,   109,    78,    22,    21,   127,   125,
     128,   130,   161,   162,    12,   149,  -451,  5773,  -451,   186,
    6405,  -451,   220,  4552,  4552,   187,  3622,  -451,  -451,  -451,
     145,   147,  -451,   156,   163,   150,  6089,   164,  6405,   153,
     165,   166,   157,  -451,  -451,   105,  -451,  -451,    70,  -451,
      28,   169,  -451,  -451,  -451,  -451,  1304,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,   266,   129,  5457,    42,
    5457,  -451,  -451,  5457,  4552,  -451,   199,  -451,  -451,  -451,
      56,  -451,  -451,  6405,   203,  -451,  -451,  6405,   170,  -451,
    -451,  -451,  6405,  6405,  6405,  6405,  6405,  6405,  6405,  6405,
    6405,  6405,  6405,  6405,  6405,  6405,  6405,  6405,  6405,  6405,
    6405,  -451,  -451,  -451,   172,  -451,  -451,  -451,  -451,  3932,
     187,    82,    75,  -451,  -451,  -451,  -451,  -451,  1638,  -451,
    6405,  -451,  -451,    98,  6405,   113,  -451,  -451,   205,  -451,
    1638,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  6405,  6405,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  5457,  -451,    66,  -451,  4242,  -451,  -451,   173,   167,
    -451,  -451,  -451,  -451,  -451,   109,   109,    78,    78,    22,
      22,    22,    22,    21,    21,   127,   125,   128,   130,   161,
     162,  6405,  -451,  -451,    99,   129,   187,  -451,   211,  2640,
      59,  -451,    61,  -451,  2974,   178,     7,  -451,  1638,  -451,
    -451,  -451,  -451,  4825,  -451,  -451,   122,  -451,  -451,   179,
    -451,  -451,  2974,   176,  -451,   167,   218,  4552,   185,  6405,
     189,   205,   183,  -451,  -451,  6405,  6405,  -451,   180,   192,
     482,   191,  2306,  -451,   193,   190,  1972,   195,  -451,  -451,
    -451,  -451,    63,  6405,  1972,   176,  -451,  -451,  1638,  5457,
    -451,  -451,  -451,  -451,   188,   167,  -451,  -451,  1638,   196,
    -451,  -451,  -451
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   149,   150,   148,   185,   176,   177,   179,   180,   181,
     182,   183,   184,   178,   165,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   207,   208,   209,   210,   211,   212,
     186,   187,   188,   216,   217,   218,   154,   152,   153,   151,
     157,   155,   156,   158,   159,   160,   161,   162,   163,   164,
     189,   190,   191,   228,   229,   230,   192,   193,   194,   240,
     241,   242,   204,   205,   206,   213,   214,   215,   131,   130,
     129,     0,   132,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   279,   280,   281,   282,   283,   284,   286,   287,
     288,   289,   290,   291,   293,   294,   297,   298,   299,   301,
     302,   264,   265,   285,   292,   303,   305,   306,   307,   309,
     310,   401,   266,   267,   268,   295,   269,   273,   274,   277,
     300,   304,   308,   270,   271,   275,   276,   296,   272,   278,
     311,   312,   313,   315,   317,   319,   321,   323,   327,   328,
     329,   330,   331,   332,   334,   335,   336,   337,   338,   339,
     341,   343,   344,   345,   347,   348,   325,   333,   340,   349,
     351,   352,   353,   355,   356,   314,   316,   318,   342,   320,
     322,   324,   326,   346,   350,   354,   402,   403,   406,   407,
     408,   409,   404,   405,   357,   359,   360,   361,   363,   364,
     365,   367,   368,   369,   371,   372,   373,   375,   376,   377,
     379,   380,   381,   383,   384,   385,   387,   388,   389,   391,
     392,   393,   395,   396,   397,   399,   400,   358,   362,   366,
     370,   374,   382,   386,   390,   378,   394,   398,     0,   175,
     411,   496,   128,   139,   412,   413,   414,     0,   495,     0,
     497,     0,   105,   104,     0,   116,   121,   146,   145,   143,
     147,     0,   140,   142,   126,   169,   144,   410,     0,   492,
     494,     0,     0,     0,   417,     0,     0,    93,    90,     0,
     103,     0,   112,   106,   114,     0,   115,     0,    91,   122,
       0,    96,   141,   127,     0,   170,     1,   493,   167,     0,
     138,   136,     0,   134,   415,     0,     0,    94,     0,     0,
     498,   107,   111,   113,   109,   117,   108,     0,   123,    99,
       0,    97,     0,     2,    10,    11,     4,     5,     6,     7,
       8,     9,    13,    12,     0,     0,     0,   171,    39,    38,
      40,    37,     3,    15,    33,    17,    22,    23,     0,     0,
      27,     0,    41,     0,    45,    48,    51,    56,    59,    61,
      63,    65,    67,    69,    71,     0,    31,     0,   166,     0,
       0,   133,     0,     0,     0,     0,     0,   419,    92,    95,
       0,     0,   477,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,   452,   456,    41,    74,    87,     0,   432,
       0,   126,   435,   454,   434,   433,     0,   436,   437,   458,
     438,   465,   439,   440,   473,   441,     0,   110,     0,   118,
       0,   427,   125,     0,     0,   101,     0,    98,    34,    35,
       0,    19,    20,     0,     0,    25,    24,     0,   175,    28,
      30,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,   172,   173,     0,   168,    89,   137,   135,     0,
       0,   425,     0,   423,   418,   420,   488,   487,     0,   479,
       0,   491,   489,     0,     0,     0,   472,   475,     0,   442,
       0,    77,    78,    80,    79,    82,    83,    84,    85,    86,
      81,    76,     0,     0,   457,   453,   455,   459,   466,   474,
     120,     0,   430,     0,   124,     0,   102,    14,     0,    21,
      18,    29,    42,    43,    44,    47,    46,    49,    50,    54,
      55,    52,    53,    57,    58,    60,    62,    64,    66,    68,
      70,     0,   174,   416,     0,   426,     0,   421,     0,     0,
       0,   490,     0,   471,     0,   502,     0,   500,   444,    75,
      88,   119,   428,     0,   100,    16,     0,   422,   424,     0,
     482,   481,   484,   450,   467,   463,     0,     0,     0,     0,
       0,     0,     0,   429,   431,     0,     0,   483,     0,     0,
     462,     0,     0,   460,     0,     0,     0,     0,   499,   501,
     445,    73,     0,   485,     0,   450,   449,   451,   469,     0,
     447,   476,   446,   503,     0,   486,   480,   461,   470,     0,
     464,   478,   468
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  6666,  -451,   -25,   -20,  -450,   -24,    32,    35,
      36,    34,    37,    38,  -451,   -38,  -451,   -57,  -451,   -65,
     -85,     1,  -451,  -451,  -451,    16,  -451,  -451,  -451,   210,
     216,   214,  -451,  -451,  -282,  -451,  -451,  -451,  -451,   131,
    -451,     2,    -9,  -451,  -451,     0,   -11,  -451,   253,  -451,
    -451,  -451,  -100,  -117,    40,   -45,  -141,  -451,   -47,  -148,
    -298,   -87,  -451,  -451,   -99,   -97,  -451,  -451,   230,  -227,
     -37,  -451,    95,  -451,   -59,  -451,   100,  -451,  -451,  -451,
    -451,   102,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
     246,  -451,  -451,  -451,  -451,   -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   362,   363,   364,   538,   365,   366,   367,   368,   369,
     370,   371,   415,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   416,   561,   417,   522,   418,
     487,   419,   269,   444,   342,   420,   271,   272,   273,   302,
     303,   304,   274,   275,   276,   277,   278,   279,   322,   323,
     280,   281,   282,   283,   319,   386,   315,   285,   286,   287,
     393,   325,   396,   397,   492,   493,   442,   533,   422,   423,
     424,   425,   510,   602,   631,   610,   611,   612,   632,   426,
     427,   428,   429,   613,   598,   430,   431,   614,   639,   432,
     433,   434,   574,   498,   569,   592,   608,   609,   435,   288,
     289,   290,   299,   436,   576,   577
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     284,   268,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   336,   270,   314,   314,   549,
     550,   551,   552,   291,   337,   438,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
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
     258,   259,   312,   306,   260,   305,   385,   320,   526,   495,
     441,   313,   293,   578,   402,   328,   403,   404,   284,   268,
     407,   450,   596,   489,   296,   326,   312,   530,   338,   532,
     388,   306,   534,   305,   270,   306,   389,   480,   467,   468,
     596,   469,   470,   459,   627,   387,   261,   600,   630,   294,
     314,   601,   443,   437,   439,   395,   630,   394,   327,   421,
     262,   263,   264,   265,   266,   267,   292,   297,   451,   452,
     387,   503,   481,   505,   535,   298,   471,   472,   399,   484,
     568,   387,   486,   307,   391,   456,   308,   -32,   531,   453,
     392,   457,   339,   454,   537,   340,   300,   593,   341,   594,
     523,   634,   495,   523,   301,   523,   446,   523,   582,   447,
     583,   441,   309,   441,   523,   312,   441,   524,   539,   566,
     581,   314,   567,   395,   490,   394,   395,   465,   394,   466,
     541,   638,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   523,   566,   318,   571,   587,   324,   495,   473,
     474,   521,   264,   265,   266,   329,   421,   523,   573,   334,
     526,   462,   463,   464,   335,   570,   523,   605,   387,   572,
     545,   546,   604,   398,   395,   445,   394,   547,   548,   553,
     554,   390,   455,   460,   475,   478,   476,   477,   479,   482,
     485,   491,   496,   499,   497,   579,   580,   501,   506,   509,
     500,   504,   507,   536,   441,   508,   -31,   540,   -26,   575,
     565,   523,   562,   585,   589,   599,   606,  -448,   640,   395,
     526,   394,   615,   616,   321,   620,   586,   623,   421,   618,
     624,   625,   412,   633,   628,   641,   629,   555,   642,   595,
     421,   556,   558,   557,   617,   332,   559,   331,   560,   333,
     295,   588,   590,   488,   626,   636,   441,   595,   637,   330,
     564,   527,   591,   607,   317,   395,   528,   394,   529,   410,
     619,   622,     0,     0,     0,     0,     0,     0,   621,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   635,     0,
       0,   486,     0,     0,     0,     0,     0,     0,     0,   421,
       0,     0,   441,     0,   421,     0,   597,     0,   421,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   312,     0,
       0,     0,   421,     0,   597,     0,     0,   313,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   421,     0,     0,     0,   421,     0,     0,     0,
       0,     0,     0,     0,   421,     0,     0,     0,   421,     0,
       0,     0,     0,     0,     0,     0,   316,     0,   421,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,    15,    16,    17,    18,    19,    20,
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
     251,   252,   253,   254,   255,   256,   257,   258,   259,     0,
       0,   260,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   261,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   262,   263,   264,
     265,   266,   267,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   400,   401,   402,     0,
     403,   404,   405,   406,   407,   408,   409,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
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
     257,   258,   259,   410,   343,   260,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,     0,     0,   354,   355,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   356,     0,   411,
       0,   412,   413,     0,     0,     0,     0,   414,   358,   359,
     360,   361,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   262,   263,   264,   265,   266,   267,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     400,   401,   402,     0,   403,   404,   405,   406,   407,   408,
     409,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     253,   254,   255,   256,   257,   258,   259,   410,   343,   260,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
       0,     0,   354,   355,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   356,     0,   411,     0,   412,   525,     0,     0,     0,
       0,   414,   358,   359,   360,   361,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   262,   263,   264,   265,   266,
     267,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   400,   401,   402,     0,   403,   404,
     405,   406,   407,   408,   409,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
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
     259,   410,   343,   260,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,     0,     0,   354,   355,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   356,     0,   411,     0,   412,
       0,     0,     0,     0,     0,   414,   358,   359,   360,   361,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   262,
     263,   264,   265,   266,   267,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   400,   401,
     402,     0,   403,   404,   405,   406,   407,   408,   409,    14,
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
     255,   256,   257,   258,   259,   410,   343,   260,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,     0,     0,
     354,   355,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   356,
       0,   411,     0,   329,     0,     0,     0,     0,     0,   414,
     358,   359,   360,   361,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,   267,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   400,   401,   402,     0,   403,   404,   405,   406,
     407,   408,   409,    14,    15,    16,    17,    18,    19,    20,
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
     251,   252,   253,   254,   255,   256,   257,   258,   259,   410,
     343,   260,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,     0,     0,   354,   355,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   356,     0,   411,     0,     0,     0,     0,
       0,     0,     0,   414,   358,   359,   360,   361,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   262,   263,   264,
     265,   266,   267,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
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
     257,   258,   259,     0,   343,   260,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,     0,     0,   354,   355,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   356,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   414,   358,   359,
     360,   361,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   262,   263,   264,   265,   266,   267,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     253,   254,   255,   256,   257,   258,   259,     0,   343,   260,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
       0,     0,   354,   355,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   356,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   358,   359,   360,   361,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   262,   263,   264,   265,   266,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,    18,    19,
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
       0,   310,   260,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   311,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   262,   263,
     264,   265,   266,     0,     0,     0,     0,     0,     0,    14,
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
     255,   256,   257,   258,   259,     0,     0,   260,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,     0,    14,
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
     255,   256,   257,   258,   259,     0,     0,   260,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   563,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,     0,    14,
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
     255,   256,   257,   258,   259,     0,     0,   260,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   584,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,     0,    14,
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
     255,   256,   257,   258,   259,     0,     0,   260,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   262,   263,   264,   265,   266,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     252,   253,   254,   255,   256,   257,   258,   259,     0,   343,
     260,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,     0,     0,   354,   355,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   356,     0,     0,     0,   440,   603,     0,     0,
       0,     0,     0,   358,   359,   360,   361,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,    73,    74,    75,
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
     256,   257,   258,   259,     0,   343,   260,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,     0,     0,   354,
     355,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   356,     0,
       0,   357,     0,     0,     0,     0,     0,     0,     0,   358,
     359,   360,   361,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
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
       0,   343,   260,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,     0,     0,   354,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   356,     0,     0,     0,   440,     0,
       0,     0,     0,     0,     0,   358,   359,   360,   361,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,    73,
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
     254,   255,   256,   257,   258,   259,     0,   343,   260,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,     0,
       0,   354,   355,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     356,     0,     0,   483,     0,     0,     0,     0,     0,     0,
       0,   358,   359,   360,   361,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
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
     258,   259,     0,   343,   260,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,     0,   354,   355,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   356,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   502,   358,   359,   360,
     361,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     252,   253,   254,   255,   256,   257,   258,   259,     0,   343,
     260,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,     0,     0,   354,   355,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   356,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   358,   359,   360,   361,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
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
     250,   251,   252,   253,   254,   255,   256,   257,   258,   458,
     372,   343,   260,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,     0,     0,   354,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   356,     0,     0,     0,     0,     0,
     448,   449,     0,     0,     0,   358,   359,   360,   361,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,     0,     0,   372,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   542,   543,
     544,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,     0,     0,     0,     0,   372,    73,    74,    75,    76,
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
     257,   258,   259,     0,     0,   260
};

static const yytype_int16 yycheck[] =
{
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   307,     0,   309,   309,   469,
     470,   471,   472,   307,   316,   316,    27,    28,    29,    30,
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
     271,   272,   281,   273,   275,   273,   314,    57,   426,   396,
     337,   281,   274,   510,    18,   296,    20,    21,   288,   288,
      24,   356,   574,   393,   274,   295,   305,   438,   309,   440,
     308,   301,   443,   301,   288,   305,   314,   295,   286,   287,
     592,   290,   291,   370,   612,   309,   317,   310,   616,   311,
     309,   314,   316,   334,   335,   325,   624,   325,   317,   329,
     331,   332,   333,   334,   335,   336,   307,   317,   288,   289,
     309,   406,   330,   408,   444,   317,   325,   326,   317,   387,
     498,   309,   390,   314,   308,   308,   317,   307,   316,   309,
     314,   314,   311,   313,   308,   314,   308,   308,   317,   308,
     314,   308,   489,   314,   314,   314,   314,   314,   312,   317,
     314,   438,   274,   440,   314,   394,   443,   317,   453,   314,
     531,   309,   317,   393,   394,   393,   396,   319,   396,   321,
     457,   628,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   314,   314,   274,   317,   317,   311,   535,   292,
     293,   316,   333,   334,   335,   311,   426,   314,   315,   274,
     578,   322,   323,   324,   274,   500,   314,   315,   309,   504,
     465,   466,   583,   317,   444,   274,   444,   467,   468,   473,
     474,   316,   308,   307,   329,   294,   328,   327,   296,   310,
     274,   274,   317,   307,   317,   522,   523,   317,   315,   312,
     307,   307,   307,   274,   531,   309,   307,   274,   308,   274,
     491,   314,   310,   310,   273,   307,   307,   311,   629,   489,
     638,   489,   274,   308,   274,   312,   561,   317,   498,   310,
     308,    19,   311,   308,   311,   317,   316,   475,   312,   574,
     510,   476,   478,   477,   599,   305,   479,   301,   480,   305,
     267,   566,   569,   392,   611,   624,   583,   592,   625,   299,
     490,   436,   569,   592,   288,   535,   436,   535,   436,   273,
     601,   606,    -1,    -1,    -1,    -1,    -1,    -1,   605,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   623,    -1,
      -1,   599,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   569,
      -1,    -1,   629,    -1,   574,    -1,   574,    -1,   578,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   597,    -1,
      -1,    -1,   592,    -1,   592,    -1,    -1,   597,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   612,    -1,    -1,    -1,   616,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   624,    -1,    -1,    -1,   628,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     0,    -1,   638,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
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
     264,   265,   266,   267,   268,   269,   270,   271,   272,    -1,
      -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   317,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   331,   332,   333,
     334,   335,   336,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
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
     280,   281,   282,   283,   284,   285,    -1,    -1,   288,   289,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   307,    -1,   309,
      -1,   311,   312,    -1,    -1,    -1,    -1,   317,   318,   319,
     320,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   331,   332,   333,   334,   335,   336,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    20,    21,    22,    23,    24,    25,
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
      -1,    -1,   288,   289,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   307,    -1,   309,    -1,   311,   312,    -1,    -1,    -1,
      -1,   317,   318,   319,   320,   321,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   331,   332,   333,   334,   335,
     336,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    20,    21,
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
     282,   283,   284,   285,    -1,    -1,   288,   289,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   307,    -1,   309,    -1,   311,
      -1,    -1,    -1,    -1,    -1,   317,   318,   319,   320,   321,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   331,
     332,   333,   334,   335,   336,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
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
     278,   279,   280,   281,   282,   283,   284,   285,    -1,    -1,
     288,   289,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   307,
      -1,   309,    -1,   311,    -1,    -1,    -1,    -1,    -1,   317,
     318,   319,   320,   321,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   331,   332,   333,   334,   335,   336,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    20,    21,    22,    23,
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
     284,   285,    -1,    -1,   288,   289,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   307,    -1,   309,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   317,   318,   319,   320,   321,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   331,   332,   333,
     334,   335,   336,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
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
     270,   271,   272,    -1,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,    -1,    -1,   288,   289,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   307,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   317,   318,   319,
     320,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   331,   332,   333,   334,   335,   336,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
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
     266,   267,   268,   269,   270,   271,   272,    -1,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
      -1,    -1,   288,   289,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   307,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   318,   319,   320,   321,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   331,   332,   333,   334,   335,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    32,
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
      -1,   274,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   317,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   331,   332,
     333,   334,   335,    -1,    -1,    -1,    -1,    -1,    -1,    27,
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
     268,   269,   270,   271,   272,    -1,    -1,   275,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   312,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,   331,   332,   333,   334,   335,    -1,    27,
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
     268,   269,   270,   271,   272,    -1,    -1,   275,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   312,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,   331,   332,   333,   334,   335,    -1,    27,
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
     268,   269,   270,   271,   272,    -1,    -1,   275,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   312,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,   331,   332,   333,   334,   335,    -1,    27,
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
     268,   269,   270,   271,   272,    -1,    -1,   275,    -1,    -1,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   331,   332,   333,   334,   335,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     265,   266,   267,   268,   269,   270,   271,   272,    -1,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    -1,    -1,   288,   289,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   307,    -1,    -1,    -1,   311,   312,    -1,    -1,
      -1,    -1,    -1,   318,   319,   320,   321,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
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
     269,   270,   271,   272,    -1,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,    -1,    -1,   288,
     289,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   307,    -1,
      -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,
     319,   320,   321,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
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
      -1,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,    -1,    -1,   288,   289,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   307,    -1,    -1,    -1,   311,    -1,
      -1,    -1,    -1,    -1,    -1,   318,   319,   320,   321,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    86,
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
     267,   268,   269,   270,   271,   272,    -1,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,    -1,
      -1,   288,   289,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     307,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   318,   319,   320,   321,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,
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
     271,   272,    -1,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,    -1,    -1,   288,   289,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   307,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   317,   318,   319,   320,
     321,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     265,   266,   267,   268,   269,   270,   271,   272,    -1,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    -1,    -1,   288,   289,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   307,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   318,   319,   320,   321,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
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
     314,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,    -1,    -1,   288,   289,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   307,    -1,    -1,    -1,    -1,    -1,
     354,   355,    -1,    -1,    -1,   318,   319,   320,   321,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   387,    -1,    -1,   390,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,   599,    86,    87,    88,    89,
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
     270,   271,   272,    -1,    -1,   275
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    27,    28,    29,    30,    31,    32,
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
     275,   317,   331,   332,   333,   334,   335,   336,   371,   372,
     375,   376,   377,   378,   382,   383,   384,   385,   386,   387,
     390,   391,   392,   393,   395,   397,   398,   399,   439,   440,
     441,   307,   307,   274,   311,   398,   274,   317,   317,   442,
     308,   314,   379,   380,   381,   391,   395,   314,   317,   274,
     274,   317,   392,   395,   309,   396,     0,   440,   274,   394,
      57,   274,   388,   389,   311,   401,   395,   317,   396,   311,
     418,   380,   379,   381,   274,   274,   307,   316,   396,   311,
     314,   317,   374,   274,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   288,   289,   307,   310,   318,   319,
     320,   321,   341,   342,   343,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   395,   309,   308,   314,
     316,   308,   314,   400,   391,   395,   402,   403,   317,   317,
      16,    17,    18,    20,    21,    22,    23,    24,    25,    26,
     273,   309,   311,   312,   317,   352,   365,   367,   369,   371,
     375,   395,   408,   409,   410,   411,   419,   420,   421,   422,
     425,   426,   429,   430,   431,   438,   443,   396,   316,   396,
     311,   367,   406,   316,   373,   274,   314,   317,   352,   352,
     369,   288,   289,   309,   313,   308,   308,   314,   272,   367,
     307,   352,   322,   323,   324,   319,   321,   286,   287,   290,
     291,   325,   326,   292,   293,   329,   328,   327,   294,   296,
     295,   330,   310,   310,   365,   274,   365,   370,   389,   402,
     395,   274,   404,   405,   312,   403,   317,   317,   433,   307,
     307,   317,   317,   369,   307,   369,   315,   307,   309,   312,
     412,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   316,   368,   314,   317,   312,   409,   422,   426,   431,
     406,   316,   406,   407,   406,   402,   274,   308,   344,   369,
     274,   367,   352,   352,   352,   354,   354,   355,   355,   356,
     356,   356,   356,   357,   357,   358,   359,   360,   361,   362,
     363,   366,   310,   312,   404,   396,   314,   317,   409,   434,
     369,   317,   369,   315,   432,   274,   444,   445,   419,   367,
     367,   406,   312,   314,   312,   310,   369,   317,   405,   273,
     408,   420,   435,   308,   308,   369,   384,   391,   424,   307,
     310,   314,   413,   312,   406,   315,   307,   424,   436,   437,
     415,   416,   417,   423,   427,   274,   308,   370,   310,   445,
     312,   367,   369,   317,   308,    19,   411,   410,   311,   316,
     410,   414,   418,   308,   308,   369,   414,   415,   419,   428,
     406,   317,   312
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   340,   341,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   343,   343,   343,   343,   343,
     343,   344,   345,   346,   347,   347,   348,   348,   349,   349,
     350,   351,   351,   352,   352,   352,   352,   353,   353,   353,
     353,   354,   354,   354,   354,   355,   355,   355,   356,   356,
     356,   357,   357,   357,   357,   357,   358,   358,   358,   359,
     359,   360,   360,   361,   361,   362,   362,   363,   363,   364,
     364,   365,   366,   365,   367,   367,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   369,   369,   370,
     371,   371,   371,   371,   371,   371,   371,   371,   371,   373,
     372,   374,   374,   375,   376,   376,   377,   377,   378,   379,
     379,   380,   380,   380,   380,   381,   382,   382,   382,   382,
     382,   383,   383,   383,   383,   383,   384,   384,   385,   386,
     386,   386,   386,   387,   388,   388,   389,   389,   389,   390,
     391,   391,   392,   392,   392,   392,   392,   392,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   394,   394,   395,
     395,   396,   396,   396,   396,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   398,   398,   398,   400,   399,   401,   399,   402,
     402,   403,   403,   404,   404,   405,   405,   406,   406,   406,
     407,   407,   408,   409,   409,   410,   410,   410,   410,   410,
     410,   410,   411,   412,   413,   411,   414,   414,   416,   415,
     417,   415,   418,   418,   419,   419,   420,   420,   421,   421,
     422,   423,   423,   424,   424,   425,   425,   427,   426,   428,
     428,   429,   429,   430,   430,   432,   431,   433,   431,   434,
     431,   435,   435,   436,   436,   437,   437,   438,   438,   438,
     438,   438,   439,   439,   440,   440,   440,   442,   441,   443,
     444,   444,   445,   445
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     4,     1,     3,     2,
       2,     1,     1,     1,     2,     2,     2,     1,     2,     3,
       2,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     2,     4,     2,     3,     4,     2,     3,     4,     0,
       6,     2,     3,     2,     1,     1,     2,     3,     3,     2,
       3,     2,     1,     2,     1,     1,     1,     3,     4,     6,
       5,     1,     2,     3,     5,     4,     1,     2,     1,     1,
       1,     1,     1,     4,     1,     3,     1,     3,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     1,
       2,     2,     3,     3,     4,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     0,     6,     0,     5,     1,
       2,     3,     4,     1,     3,     1,     2,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     0,     5,     1,     1,     0,     2,
       0,     2,     2,     3,     1,     2,     1,     2,     1,     2,
       5,     3,     1,     1,     4,     1,     2,     0,     8,     0,
       1,     3,     2,     1,     2,     0,     6,     0,     8,     0,
       7,     1,     1,     1,     0,     2,     3,     2,     2,     2,
       3,     2,     1,     2,     1,     1,     1,     0,     3,     5,
       1,     3,     1,     4
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
#line 272 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[0].lex).loc, (yyvsp[0].lex).symbol, (yyvsp[0].lex).string);
    }
#line 3637 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 278 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 3645 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 281 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 3653 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 284 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 3662 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 288 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 3671 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 292 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 3680 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 296 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
#endif
    }
#line 3691 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 302 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
#endif
    }
#line 3702 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 308 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 3710 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 311 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 3719 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 315 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
#endif
    }
#line 3730 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 321 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 3738 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 324 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 3748 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 332 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 3756 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 335 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 3764 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 338 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 3772 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 341 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 3780 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 344 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 3790 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 349 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 3800 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 357 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.integerCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 3809 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 364 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 3818 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 371 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 3826 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 377 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 3835 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 381 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 3844 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 388 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 3852 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 391 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 3860 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 397 "glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-1].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-1].interm).function;
        (yyval.interm).intermNode = (yyvsp[0].interm.intermTypedNode);
    }
#line 3872 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 404 "glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-2].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-2].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
    }
#line 3884 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 414 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 3892 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 422 "glslang.y" /* yacc.c:1646  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 3902 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 427 "glslang.y" /* yacc.c:1646  */
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
            TString empty("");
            (yyval.interm).function = new TFunction(&empty, TType(EbtVoid), EOpNull);
        }
    }
#line 3934 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 457 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 3945 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 463 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 3954 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 467 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 3963 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 471 "glslang.y" /* yacc.c:1646  */
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
#line 3984 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 491 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 3990 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 492 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 3996 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 493 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 4002 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 494 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 4009 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 500 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4015 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 501 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4025 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 506 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4035 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 511 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4046 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 520 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4052 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 521 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4062 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 526 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4072 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 534 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4078 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 535 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4089 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 541 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4100 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 550 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4106 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 551 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4116 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 556 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4126 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 561 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4136 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 566 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4146 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 574 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4152 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 575 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4165 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 583 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4178 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 594 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4184 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 595 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4195 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 604 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4201 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 605 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4212 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 614 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4218 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 615 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4229 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 624 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4235 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 625 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4245 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 633 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4251 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 634 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4261 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 642 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4267 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 643 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4277 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 651 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4283 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 652 "glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 4291 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 655 "glslang.y" /* yacc.c:1646  */
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
#line 4308 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 670 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4314 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 671 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addAssign((yyvsp[-1].interm).op, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].interm).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
        }
    }
#line 4331 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 686 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 4340 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 690 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 4349 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 694 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 4358 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 698 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 4368 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 703 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 4377 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 707 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 4386 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 711 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 4395 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 715 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 4404 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 719 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 4413 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 723 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 4422 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 727 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 4431 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 734 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4439 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 737 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 4452 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 748 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4461 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 755 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 4471 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 760 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 4481 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 765 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 4494 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 773 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
        (yyval.interm.intermNode) = 0;
    }
#line 4503 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 777 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 4512 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 781 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    }
#line 4521 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 785 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 4531 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 790 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 4541 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 795 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).shaderQualifiers);
        (yyvsp[-1].interm.identifierList)->push_back((yyvsp[-2].lex).string);
        parseContext.addQualifierToExisting((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 4552 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 804 "glslang.y" /* yacc.c:1646  */
    { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 4558 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 804 "glslang.y" /* yacc.c:1646  */
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 4572 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 815 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 4581 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 819 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 4590 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 826 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4599 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 833 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 4607 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 836 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 4615 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 843 "glslang.y" /* yacc.c:1646  */
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 4628 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 851 "glslang.y" /* yacc.c:1646  */
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
#line 4650 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 871 "glslang.y" /* yacc.c:1646  */
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
#line 4674 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 894 "glslang.y" /* yacc.c:1646  */
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
#line 4694 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 909 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }
        parseContext.arrayDimCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.type).arraySizes, (yyvsp[0].interm).arraySizes);

        parseContext.arraySizeRequiredCheck((yyvsp[0].interm).loc, *(yyvsp[0].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string);

        TParameter param = { (yyvsp[-1].lex).string, new TType((yyvsp[-2].interm.type))};
        parseContext.arrayDimMerge(*param.type, (yyvsp[0].interm).arraySizes);

        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).param = param;
    }
#line 4716 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 932 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 4732 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 943 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFix((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 4744 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 953 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 4759 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 963 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFix((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 4771 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 973 "glslang.y" /* yacc.c:1646  */
    {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 4782 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 982 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4790 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 985 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
    }
#line 4799 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 989 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
    }
#line 4808 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 993 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 4818 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 998 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 4828 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1006 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 4838 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1011 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
    }
#line 4848 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1016 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
    }
#line 4858 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1021 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 4868 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1026 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 4878 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1035 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    }
#line 4894 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 1046 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.globalQualifierTypeCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, (yyvsp[0].interm.type));

        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[0].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).qualifier))
            (yyvsp[0].interm.type).arraySizes = 0;

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
#line 4923 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 1073 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 4934 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 1082 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 4946 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1089 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 4958 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1096 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "noperspective");
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "noperspective");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
#line 4970 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1103 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    }
#line 4984 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1115 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 4992 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1121 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5000 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 1124 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5010 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 1131 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 5019 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 1135 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 5028 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 1139 "glslang.y" /* yacc.c:1646  */
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 5038 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 1147 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 5049 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 1156 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5057 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1159 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5070 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1170 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5078 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1173 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5086 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 1176 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5095 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1180 "glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5104 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 1184 "glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5113 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 1188 "glslang.y" /* yacc.c:1646  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5122 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 1195 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 5131 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1199 "glslang.y" /* yacc.c:1646  */
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
#line 5148 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1211 "glslang.y" /* yacc.c:1646  */
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
#line 5167 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1225 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 5177 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1230 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 5188 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1236 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 5199 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1242 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 5211 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1249 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 5222 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1255 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 5232 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1260 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 5242 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1265 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 5252 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1270 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 310, 0, "shared");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangCompute, "shared");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
#line 5265 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1278 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 5274 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1282 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 5283 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1286 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 5292 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1290 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 5301 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1294 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 5310 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1298 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 5321 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1304 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 5332 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1313 "glslang.y" /* yacc.c:1646  */
    {
        // TODO
    }
#line 5340 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1316 "glslang.y" /* yacc.c:1646  */
    {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 5350 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1324 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
    }
#line 5359 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 1328 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayDimCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes, 0);
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
    }
#line 5370 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1337 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 5380 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1342 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 5393 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1350 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 5402 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1354 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 5414 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1364 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 5423 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1368 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 5432 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1372 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 5442 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 1377 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
#endif
    }
#line 5454 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 1384 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 5463 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 1388 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 5473 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1393 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 5483 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1398 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 5493 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1403 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
#endif
    }
#line 5505 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1410 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
#endif
    }
#line 5517 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 1417 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 5526 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 1421 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 5536 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1426 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 5546 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 1431 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 5556 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1436 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 5567 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 1442 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 5578 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 1448 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 5589 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 1454 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
#endif
    }
#line 5602 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1462 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
#endif
    }
#line 5615 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1470 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
#endif
    }
#line 5628 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1478 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 5638 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1483 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 5648 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1488 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 5658 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1493 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 5668 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1498 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 5678 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 1503 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 5688 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 1508 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 5699 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1514 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 5710 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1520 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 5721 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 1526 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
#endif
    }
#line 5734 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 1534 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
#endif
    }
#line 5747 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1542 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
#endif
    }
#line 5760 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1550 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 5771 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1556 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 5782 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1562 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 5793 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1568 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 5804 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 1574 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 5815 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1580 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 5826 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 1586 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
#endif
    }
#line 5839 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 1594 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
#endif
    }
#line 5852 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1602 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
#endif
    }
#line 5865 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1610 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 5875 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 1615 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 5885 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1620 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 5895 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 1625 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 5905 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 1630 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 5915 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1635 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 5925 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1640 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 5935 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1645 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 5945 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1650 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 5955 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1655 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 5965 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 1660 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 5975 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 1665 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 5985 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1670 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 5996 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1676 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6007 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1682 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 6018 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1688 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6029 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1694 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 6040 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 1700 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 6051 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1706 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 6062 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1712 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6073 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1718 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 6084 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 1724 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 6095 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1730 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 6106 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1736 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 6117 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 1742 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    }
#line 6130 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 1750 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    }
#line 6143 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1758 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    }
#line 6156 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1766 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    }
#line 6169 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1774 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
#endif
    }
#line 6182 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1782 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
#endif
    }
#line 6195 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 1790 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
#endif
    }
#line 6208 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1798 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    }
#line 6221 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1806 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
#endif
    }
#line 6234 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 1814 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
#endif
    }
#line 6247 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1822 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
#endif
    }
#line 6260 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1830 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    }
#line 6273 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1838 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 6283 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1843 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 6293 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 1848 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 6303 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1853 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 6313 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 1858 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 6323 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 1863 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 6333 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 1868 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 6343 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1873 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 6353 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1878 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 6363 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1883 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 6373 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1888 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 6383 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 1893 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 6393 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1898 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 6403 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 1903 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 6413 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 1908 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
#endif
    }
#line 6426 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1916 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
#endif
    }
#line 6439 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 1924 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
#endif
    }
#line 6452 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1932 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
#endif
    }
#line 6465 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 1940 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
#endif
    }
#line 6478 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 1948 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
#endif
    }
#line 6491 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 1956 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
#endif
    }
#line 6504 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 1964 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
#endif
    }
#line 6517 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 1972 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
#endif
    }
#line 6530 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 1980 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
#endif
    }
#line 6543 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1988 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
#endif
    }
#line 6556 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1996 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
#endif
    }
#line 6569 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 2004 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
#endif
    }
#line 6582 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 2012 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 6592 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 2017 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 6602 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 2022 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 6612 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 2027 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 6622 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 2032 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 6632 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 2037 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 6642 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 2042 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 6652 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 2047 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 6662 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 2052 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 6672 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 2057 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 6682 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 2062 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 6692 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 2067 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 6702 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 2072 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 6712 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 2077 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 6722 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 2082 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 6732 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 2087 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 6742 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 2092 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
#endif
    }
#line 6755 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 2100 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
#endif
    }
#line 6768 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 2108 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 6778 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 2113 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 6788 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 2118 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 6798 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 2123 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
#endif
    }
#line 6811 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 2131 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 6821 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 2136 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 6831 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 2141 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 6841 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 2146 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 6854 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 2154 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 6864 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 306:
#line 2159 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 6874 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 2164 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 6884 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 2169 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 6897 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 2177 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 6907 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 2182 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 6917 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 2187 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 6927 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 2192 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 6937 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 2197 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 6947 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 2202 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
#endif
    }
#line 6960 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 2210 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 6970 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 2215 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
#endif
    }
#line 6983 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 2223 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 6993 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 2228 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
#endif
    }
#line 7006 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 2236 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 7016 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 2241 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
#endif
    }
#line 7029 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 2249 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 7039 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 2254 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
#endif
    }
#line 7052 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 2262 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 7062 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 324:
#line 2267 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
#endif
    }
#line 7075 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 2275 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 7085 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 2280 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
#endif
    }
#line 7098 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 2288 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 7108 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 328:
#line 2293 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 7118 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 2298 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 7128 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 2303 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 7138 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 2308 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 7148 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 2313 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 7158 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 2318 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 7168 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 2323 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 7178 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 2328 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 7188 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 2333 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 7198 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 2338 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 7208 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 2343 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 7218 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 339:
#line 2348 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 7228 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 340:
#line 2353 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 7238 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 341:
#line 2358 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 7248 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 342:
#line 2363 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
#endif
    }
#line 7261 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 343:
#line 2371 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 7271 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 344:
#line 2376 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 7281 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 345:
#line 2381 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 7291 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 346:
#line 2386 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
#endif
    }
#line 7304 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 347:
#line 2394 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 7314 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 348:
#line 2399 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 7324 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 349:
#line 2404 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 7334 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 350:
#line 2409 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 7347 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 351:
#line 2417 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 7357 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 352:
#line 2422 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 7367 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 353:
#line 2427 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 7377 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 354:
#line 2432 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 7390 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 355:
#line 2440 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 7400 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 356:
#line 2445 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 7410 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 357:
#line 2450 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 7420 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 358:
#line 2455 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
#endif
    }
#line 7433 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 359:
#line 2463 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 7443 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 360:
#line 2468 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 7453 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 361:
#line 2473 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 7463 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 362:
#line 2478 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
#endif
    }
#line 7476 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 363:
#line 2486 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 7486 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 364:
#line 2491 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 7496 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 365:
#line 2496 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 7506 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 366:
#line 2501 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
#endif
    }
#line 7519 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 367:
#line 2509 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 7529 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 368:
#line 2514 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 7539 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 369:
#line 2519 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 7549 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 370:
#line 2524 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
#endif
    }
#line 7562 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 371:
#line 2532 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 7572 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 372:
#line 2537 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 7582 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 373:
#line 2542 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 7592 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 374:
#line 2547 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
#endif
    }
#line 7605 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 375:
#line 2555 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 7615 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 376:
#line 2560 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 7625 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 377:
#line 2565 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 7635 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 378:
#line 2570 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
#endif
    }
#line 7648 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 379:
#line 2578 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 7658 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 380:
#line 2583 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 7668 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 381:
#line 2588 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 7678 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 382:
#line 2593 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
#endif
    }
#line 7691 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 383:
#line 2601 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 7701 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 384:
#line 2606 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 7711 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 385:
#line 2611 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 7721 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 386:
#line 2616 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
#endif
    }
#line 7734 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 387:
#line 2624 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 7744 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 388:
#line 2629 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 7754 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 389:
#line 2634 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 7764 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 390:
#line 2639 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
#endif
    }
#line 7777 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 391:
#line 2647 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 7787 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 392:
#line 2652 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 7797 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 393:
#line 2657 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 7807 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 394:
#line 2662 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 7820 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 395:
#line 2670 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 7830 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 396:
#line 2675 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 7840 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 397:
#line 2680 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 7850 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 398:
#line 2685 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 7863 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 399:
#line 2693 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 7873 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 400:
#line 2698 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 7883 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 401:
#line 2703 "glslang.y" /* yacc.c:1646  */
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 7894 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 402:
#line 2709 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 7905 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 403:
#line 2715 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 7916 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 404:
#line 2721 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
#endif
    }
#line 7930 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 405:
#line 2730 "glslang.y" /* yacc.c:1646  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
#endif
    }
#line 7944 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 406:
#line 2739 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 7955 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 407:
#line 2745 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 7966 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 408:
#line 2751 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 7977 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 409:
#line 2757 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 7988 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 410:
#line 2763 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 7998 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 411:
#line 2768 "glslang.y" /* yacc.c:1646  */
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
#line 8016 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 412:
#line 2784 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 8026 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 413:
#line 2789 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 8036 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 414:
#line 2794 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 8046 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 415:
#line 2802 "glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 8052 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 416:
#line 2802 "glslang.y" /* yacc.c:1646  */
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
#line 8068 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 417:
#line 2813 "glslang.y" /* yacc.c:1646  */
    { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 8074 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 418:
#line 2813 "glslang.y" /* yacc.c:1646  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 8086 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 419:
#line 2823 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 8094 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 420:
#line 2826 "glslang.y" /* yacc.c:1646  */
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
#line 8109 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 421:
#line 2839 "glslang.y" /* yacc.c:1646  */
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
            parseContext.arrayDimCheck((yyvsp[-2].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[-2].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[-2].interm.type));
        }
    }
#line 8132 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 422:
#line 2857 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).qualifier);
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.checkNoShaderLayouts((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).shaderQualifiers);
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, (yyvsp[-3].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            parseContext.arrayDimCheck((yyvsp[-3].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[-2].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[-2].interm.type));
        }
    }
#line 8158 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 423:
#line 2881 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 8167 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 424:
#line 2885 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 8175 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 425:
#line 2891 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 8185 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 426:
#line 2896 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.arrayDimCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes, 0);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->newArraySizes(*(yyvsp[0].interm).arraySizes);
    }
#line 8198 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 427:
#line 2907 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 8206 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 428:
#line 2910 "glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 8217 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 429:
#line 2916 "glslang.y" /* yacc.c:1646  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 8228 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 430:
#line 2925 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 8236 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 431:
#line 2928 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 8244 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 432:
#line 2934 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8250 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 433:
#line 2938 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8256 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 434:
#line 2939 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8262 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 435:
#line 2945 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8268 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 436:
#line 2946 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8274 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 437:
#line 2947 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8280 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 438:
#line 2948 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8286 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 439:
#line 2949 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8292 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 440:
#line 2950 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8298 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 441:
#line 2951 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8304 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 442:
#line 2955 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 8310 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 443:
#line 2956 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 8319 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 444:
#line 2960 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 8328 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 445:
#line 2964 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate())
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 8338 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 446:
#line 2972 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8344 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 447:
#line 2973 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 8350 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 448:
#line 2977 "glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 8358 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 449:
#line 2980 "glslang.y" /* yacc.c:1646  */
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8367 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 450:
#line 2984 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 8377 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 451:
#line 2989 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8388 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 452:
#line 2998 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 8396 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 453:
#line 3001 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate())
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 8406 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 454:
#line 3009 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 8419 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 455:
#line 3017 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 8432 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 456:
#line 3028 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = 0; }
#line 8438 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 457:
#line 3029 "glslang.y" /* yacc.c:1646  */
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 8444 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 458:
#line 3033 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8452 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 459:
#line 3036 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8461 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 460:
#line 3042 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 8470 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 461:
#line 3049 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 8479 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 462:
#line 3053 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 8488 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 463:
#line 3061 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 8497 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 464:
#line 3065 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    }
#line 8512 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 465:
#line 3078 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8520 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 466:
#line 3081 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8529 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 467:
#line 3087 "glslang.y" /* yacc.c:1646  */
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 8542 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 468:
#line 3095 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 8556 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 469:
#line 3107 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 8564 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 470:
#line 3110 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8572 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 471:
#line 3116 "glslang.y" /* yacc.c:1646  */
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
#line 8589 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 472:
#line 3128 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 8603 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 473:
#line 3140 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8611 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 474:
#line 3143 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8620 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 475:
#line 3149 "glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 8633 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 476:
#line 3157 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, true, (yyvsp[-5].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 8645 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 477:
#line 3164 "glslang.y" /* yacc.c:1646  */
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 8655 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 478:
#line 3169 "glslang.y" /* yacc.c:1646  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 8671 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 479:
#line 3180 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 8682 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 480:
#line 3186 "glslang.y" /* yacc.c:1646  */
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
#line 8699 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 481:
#line 3201 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8707 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 482:
#line 3204 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8715 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 483:
#line 3210 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 8723 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 484:
#line 3213 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermTypedNode) = 0;
    }
#line 8731 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 485:
#line 3219 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 8740 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 486:
#line 3223 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 8749 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 487:
#line 3230 "glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 8759 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 488:
#line 3235 "glslang.y" /* yacc.c:1646  */
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 8769 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 489:
#line 3240 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 8781 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 490:
#line 3247 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 8789 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 491:
#line 3250 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 8798 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 492:
#line 3259 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 8807 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 493:
#line 3263 "glslang.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 8818 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 494:
#line 3272 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8826 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 495:
#line 3275 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 8834 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 496:
#line 3278 "glslang.y" /* yacc.c:1646  */
    {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 8844 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 497:
#line 3286 "glslang.y" /* yacc.c:1646  */
    {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);
    }
#line 8853 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 498:
#line 3290 "glslang.y" /* yacc.c:1646  */
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
#line 8873 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 499:
#line 3308 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
        parseContext.requireExtensions((yyvsp[-4].lex).loc, 1, &E_GL_EXT_control_flow_attributes, "attribute");
    }
#line 8882 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 500:
#line 3314 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 8890 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 501:
#line 3317 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 8898 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 502:
#line 3322 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 8906 "glslang_tab.cpp" /* yacc.c:1646  */
    break;

  case 503:
#line 3325 "glslang.y" /* yacc.c:1646  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 8914 "glslang_tab.cpp" /* yacc.c:1646  */
    break;


#line 8918 "glslang_tab.cpp" /* yacc.c:1646  */
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
#line 3329 "glslang.y" /* yacc.c:1906  */


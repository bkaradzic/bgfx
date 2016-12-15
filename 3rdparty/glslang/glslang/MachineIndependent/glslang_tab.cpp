/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 41 "glslang.y"


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

using namespace glslang;


/* Line 371 of yacc.c  */
#line 93 "glslang_tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "glslang_tab.cpp.h".  */
#ifndef YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     FLOAT16_T = 268,
     BREAK = 269,
     CONTINUE = 270,
     DO = 271,
     ELSE = 272,
     FOR = 273,
     IF = 274,
     DISCARD = 275,
     RETURN = 276,
     SWITCH = 277,
     CASE = 278,
     DEFAULT = 279,
     SUBROUTINE = 280,
     BVEC2 = 281,
     BVEC3 = 282,
     BVEC4 = 283,
     IVEC2 = 284,
     IVEC3 = 285,
     IVEC4 = 286,
     I64VEC2 = 287,
     I64VEC3 = 288,
     I64VEC4 = 289,
     UVEC2 = 290,
     UVEC3 = 291,
     UVEC4 = 292,
     U64VEC2 = 293,
     U64VEC3 = 294,
     U64VEC4 = 295,
     VEC2 = 296,
     VEC3 = 297,
     VEC4 = 298,
     MAT2 = 299,
     MAT3 = 300,
     MAT4 = 301,
     CENTROID = 302,
     IN = 303,
     OUT = 304,
     INOUT = 305,
     UNIFORM = 306,
     PATCH = 307,
     SAMPLE = 308,
     BUFFER = 309,
     SHARED = 310,
     COHERENT = 311,
     VOLATILE = 312,
     RESTRICT = 313,
     READONLY = 314,
     WRITEONLY = 315,
     DVEC2 = 316,
     DVEC3 = 317,
     DVEC4 = 318,
     DMAT2 = 319,
     DMAT3 = 320,
     DMAT4 = 321,
     F16VEC2 = 322,
     F16VEC3 = 323,
     F16VEC4 = 324,
     F16MAT2 = 325,
     F16MAT3 = 326,
     F16MAT4 = 327,
     NOPERSPECTIVE = 328,
     FLAT = 329,
     SMOOTH = 330,
     LAYOUT = 331,
     __EXPLICITINTERPAMD = 332,
     MAT2X2 = 333,
     MAT2X3 = 334,
     MAT2X4 = 335,
     MAT3X2 = 336,
     MAT3X3 = 337,
     MAT3X4 = 338,
     MAT4X2 = 339,
     MAT4X3 = 340,
     MAT4X4 = 341,
     DMAT2X2 = 342,
     DMAT2X3 = 343,
     DMAT2X4 = 344,
     DMAT3X2 = 345,
     DMAT3X3 = 346,
     DMAT3X4 = 347,
     DMAT4X2 = 348,
     DMAT4X3 = 349,
     DMAT4X4 = 350,
     F16MAT2X2 = 351,
     F16MAT2X3 = 352,
     F16MAT2X4 = 353,
     F16MAT3X2 = 354,
     F16MAT3X3 = 355,
     F16MAT3X4 = 356,
     F16MAT4X2 = 357,
     F16MAT4X3 = 358,
     F16MAT4X4 = 359,
     ATOMIC_UINT = 360,
     SAMPLER1D = 361,
     SAMPLER2D = 362,
     SAMPLER3D = 363,
     SAMPLERCUBE = 364,
     SAMPLER1DSHADOW = 365,
     SAMPLER2DSHADOW = 366,
     SAMPLERCUBESHADOW = 367,
     SAMPLER1DARRAY = 368,
     SAMPLER2DARRAY = 369,
     SAMPLER1DARRAYSHADOW = 370,
     SAMPLER2DARRAYSHADOW = 371,
     ISAMPLER1D = 372,
     ISAMPLER2D = 373,
     ISAMPLER3D = 374,
     ISAMPLERCUBE = 375,
     ISAMPLER1DARRAY = 376,
     ISAMPLER2DARRAY = 377,
     USAMPLER1D = 378,
     USAMPLER2D = 379,
     USAMPLER3D = 380,
     USAMPLERCUBE = 381,
     USAMPLER1DARRAY = 382,
     USAMPLER2DARRAY = 383,
     SAMPLER2DRECT = 384,
     SAMPLER2DRECTSHADOW = 385,
     ISAMPLER2DRECT = 386,
     USAMPLER2DRECT = 387,
     SAMPLERBUFFER = 388,
     ISAMPLERBUFFER = 389,
     USAMPLERBUFFER = 390,
     SAMPLERCUBEARRAY = 391,
     SAMPLERCUBEARRAYSHADOW = 392,
     ISAMPLERCUBEARRAY = 393,
     USAMPLERCUBEARRAY = 394,
     SAMPLER2DMS = 395,
     ISAMPLER2DMS = 396,
     USAMPLER2DMS = 397,
     SAMPLER2DMSARRAY = 398,
     ISAMPLER2DMSARRAY = 399,
     USAMPLER2DMSARRAY = 400,
     SAMPLEREXTERNALOES = 401,
     SAMPLER = 402,
     SAMPLERSHADOW = 403,
     TEXTURE1D = 404,
     TEXTURE2D = 405,
     TEXTURE3D = 406,
     TEXTURECUBE = 407,
     TEXTURE1DARRAY = 408,
     TEXTURE2DARRAY = 409,
     ITEXTURE1D = 410,
     ITEXTURE2D = 411,
     ITEXTURE3D = 412,
     ITEXTURECUBE = 413,
     ITEXTURE1DARRAY = 414,
     ITEXTURE2DARRAY = 415,
     UTEXTURE1D = 416,
     UTEXTURE2D = 417,
     UTEXTURE3D = 418,
     UTEXTURECUBE = 419,
     UTEXTURE1DARRAY = 420,
     UTEXTURE2DARRAY = 421,
     TEXTURE2DRECT = 422,
     ITEXTURE2DRECT = 423,
     UTEXTURE2DRECT = 424,
     TEXTUREBUFFER = 425,
     ITEXTUREBUFFER = 426,
     UTEXTUREBUFFER = 427,
     TEXTURECUBEARRAY = 428,
     ITEXTURECUBEARRAY = 429,
     UTEXTURECUBEARRAY = 430,
     TEXTURE2DMS = 431,
     ITEXTURE2DMS = 432,
     UTEXTURE2DMS = 433,
     TEXTURE2DMSARRAY = 434,
     ITEXTURE2DMSARRAY = 435,
     UTEXTURE2DMSARRAY = 436,
     SUBPASSINPUT = 437,
     SUBPASSINPUTMS = 438,
     ISUBPASSINPUT = 439,
     ISUBPASSINPUTMS = 440,
     USUBPASSINPUT = 441,
     USUBPASSINPUTMS = 442,
     IMAGE1D = 443,
     IIMAGE1D = 444,
     UIMAGE1D = 445,
     IMAGE2D = 446,
     IIMAGE2D = 447,
     UIMAGE2D = 448,
     IMAGE3D = 449,
     IIMAGE3D = 450,
     UIMAGE3D = 451,
     IMAGE2DRECT = 452,
     IIMAGE2DRECT = 453,
     UIMAGE2DRECT = 454,
     IMAGECUBE = 455,
     IIMAGECUBE = 456,
     UIMAGECUBE = 457,
     IMAGEBUFFER = 458,
     IIMAGEBUFFER = 459,
     UIMAGEBUFFER = 460,
     IMAGE1DARRAY = 461,
     IIMAGE1DARRAY = 462,
     UIMAGE1DARRAY = 463,
     IMAGE2DARRAY = 464,
     IIMAGE2DARRAY = 465,
     UIMAGE2DARRAY = 466,
     IMAGECUBEARRAY = 467,
     IIMAGECUBEARRAY = 468,
     UIMAGECUBEARRAY = 469,
     IMAGE2DMS = 470,
     IIMAGE2DMS = 471,
     UIMAGE2DMS = 472,
     IMAGE2DMSARRAY = 473,
     IIMAGE2DMSARRAY = 474,
     UIMAGE2DMSARRAY = 475,
     STRUCT = 476,
     VOID = 477,
     WHILE = 478,
     IDENTIFIER = 479,
     TYPE_NAME = 480,
     FLOATCONSTANT = 481,
     DOUBLECONSTANT = 482,
     INTCONSTANT = 483,
     UINTCONSTANT = 484,
     INT64CONSTANT = 485,
     UINT64CONSTANT = 486,
     BOOLCONSTANT = 487,
     FLOAT16CONSTANT = 488,
     LEFT_OP = 489,
     RIGHT_OP = 490,
     INC_OP = 491,
     DEC_OP = 492,
     LE_OP = 493,
     GE_OP = 494,
     EQ_OP = 495,
     NE_OP = 496,
     AND_OP = 497,
     OR_OP = 498,
     XOR_OP = 499,
     MUL_ASSIGN = 500,
     DIV_ASSIGN = 501,
     ADD_ASSIGN = 502,
     MOD_ASSIGN = 503,
     LEFT_ASSIGN = 504,
     RIGHT_ASSIGN = 505,
     AND_ASSIGN = 506,
     XOR_ASSIGN = 507,
     OR_ASSIGN = 508,
     SUB_ASSIGN = 509,
     LEFT_PAREN = 510,
     RIGHT_PAREN = 511,
     LEFT_BRACKET = 512,
     RIGHT_BRACKET = 513,
     LEFT_BRACE = 514,
     RIGHT_BRACE = 515,
     DOT = 516,
     COMMA = 517,
     COLON = 518,
     EQUAL = 519,
     SEMICOLON = 520,
     BANG = 521,
     DASH = 522,
     TILDE = 523,
     PLUS = 524,
     STAR = 525,
     SLASH = 526,
     PERCENT = 527,
     LEFT_ANGLE = 528,
     RIGHT_ANGLE = 529,
     VERTICAL_BAR = 530,
     CARET = 531,
     AMPERSAND = 532,
     QUESTION = 533,
     INVARIANT = 534,
     PRECISE = 535,
     HIGH_PRECISION = 536,
     MEDIUM_PRECISION = 537,
     LOW_PRECISION = 538,
     PRECISION = 539,
     PACKED = 540,
     RESOURCE = 541,
     SUPERP = 542
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 66 "glslang.y"

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


/* Line 387 of yacc.c  */
#line 458 "glslang_tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (glslang::TParseContext* pParseContext);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_GLSLANG_TAB_CPP_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 100 "glslang.y"


/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


/* Line 390 of yacc.c  */
#line 501 "glslang_tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  265
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   6373

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  288
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  439
/* YYNRULES -- Number of states.  */
#define YYNSTATES  571

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   542

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
     285,   286,   287
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    27,    29,    34,    36,    40,    43,    46,
      48,    50,    52,    55,    58,    61,    63,    66,    70,    73,
      75,    77,    79,    82,    85,    88,    90,    92,    94,    96,
      98,   102,   106,   110,   112,   116,   120,   122,   126,   130,
     132,   136,   140,   144,   148,   150,   154,   158,   160,   164,
     166,   170,   172,   176,   178,   182,   184,   188,   190,   194,
     196,   197,   204,   206,   210,   212,   214,   216,   218,   220,
     222,   224,   226,   228,   230,   232,   234,   238,   240,   243,
     246,   251,   254,   258,   263,   266,   270,   275,   276,   283,
     286,   290,   293,   295,   297,   300,   304,   308,   311,   315,
     318,   320,   323,   325,   327,   329,   333,   338,   345,   351,
     353,   356,   360,   366,   371,   373,   376,   378,   380,   382,
     384,   386,   391,   393,   397,   399,   403,   405,   407,   409,
     412,   414,   416,   418,   420,   422,   424,   426,   428,   430,
     432,   434,   436,   438,   440,   442,   444,   446,   448,   450,
     452,   454,   456,   458,   460,   465,   467,   471,   473,   476,
     479,   483,   487,   492,   494,   496,   498,   500,   502,   504,
     506,   508,   510,   512,   514,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
     566,   568,   570,   572,   574,   576,   578,   580,   582,   584,
     586,   588,   590,   592,   594,   596,   598,   600,   602,   604,
     606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
     626,   628,   630,   632,   634,   636,   638,   640,   642,   644,
     646,   648,   650,   652,   654,   656,   658,   660,   662,   664,
     666,   668,   670,   672,   674,   676,   678,   680,   682,   684,
     686,   688,   690,   692,   694,   696,   698,   700,   702,   704,
     706,   708,   710,   712,   714,   716,   718,   720,   722,   724,
     726,   728,   730,   732,   734,   736,   738,   740,   742,   744,
     746,   748,   750,   752,   754,   756,   758,   760,   762,   764,
     766,   768,   770,   772,   774,   776,   778,   780,   782,   784,
     786,   788,   790,   792,   794,   796,   798,   800,   802,   804,
     806,   808,   810,   812,   814,   816,   818,   820,   822,   824,
     826,   828,   830,   832,   834,   836,   838,   840,   842,   844,
     846,   848,   850,   852,   854,   856,   858,   860,   862,   864,
     866,   868,   870,   872,   873,   880,   881,   887,   889,   892,
     896,   901,   903,   907,   909,   912,   914,   918,   923,   925,
     929,   931,   933,   935,   937,   939,   941,   943,   945,   947,
     949,   952,   953,   954,   960,   962,   964,   965,   968,   969,
     972,   975,   979,   981,   984,   986,   989,   995,   999,  1001,
    1003,  1008,  1009,  1018,  1019,  1021,  1025,  1028,  1029,  1036,
    1037,  1046,  1047,  1055,  1057,  1059,  1061,  1062,  1065,  1069,
    1072,  1075,  1078,  1082,  1085,  1087,  1090,  1092,  1094,  1095
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     384,     0,    -1,   224,    -1,   289,    -1,   228,    -1,   229,
      -1,   230,    -1,   231,    -1,   226,    -1,   227,    -1,   233,
      -1,   232,    -1,   255,   317,   256,    -1,   290,    -1,   291,
     257,   292,   258,    -1,   293,    -1,   291,   261,   224,    -1,
     291,   236,    -1,   291,   237,    -1,   317,    -1,   294,    -1,
     295,    -1,   297,   256,    -1,   296,   256,    -1,   298,   222,
      -1,   298,    -1,   298,   315,    -1,   297,   262,   315,    -1,
     299,   255,    -1,   343,    -1,   291,    -1,   291,    -1,   236,
     300,    -1,   237,   300,    -1,   301,   300,    -1,   269,    -1,
     267,    -1,   266,    -1,   268,    -1,   300,    -1,   302,   270,
     300,    -1,   302,   271,   300,    -1,   302,   272,   300,    -1,
     302,    -1,   303,   269,   302,    -1,   303,   267,   302,    -1,
     303,    -1,   304,   234,   303,    -1,   304,   235,   303,    -1,
     304,    -1,   305,   273,   304,    -1,   305,   274,   304,    -1,
     305,   238,   304,    -1,   305,   239,   304,    -1,   305,    -1,
     306,   240,   305,    -1,   306,   241,   305,    -1,   306,    -1,
     307,   277,   306,    -1,   307,    -1,   308,   276,   307,    -1,
     308,    -1,   309,   275,   308,    -1,   309,    -1,   310,   242,
     309,    -1,   310,    -1,   311,   244,   310,    -1,   311,    -1,
     312,   243,   311,    -1,   312,    -1,    -1,   312,   278,   314,
     317,   263,   315,    -1,   313,    -1,   300,   316,   315,    -1,
     264,    -1,   245,    -1,   246,    -1,   248,    -1,   247,    -1,
     254,    -1,   249,    -1,   250,    -1,   251,    -1,   252,    -1,
     253,    -1,   315,    -1,   317,   262,   315,    -1,   313,    -1,
     323,   265,    -1,   330,   265,    -1,   284,   346,   343,   265,
      -1,   320,   265,    -1,   320,   224,   265,    -1,   320,   224,
     344,   265,    -1,   339,   265,    -1,   339,   224,   265,    -1,
     339,   224,   322,   265,    -1,    -1,   339,   224,   259,   321,
     350,   260,    -1,   262,   224,    -1,   322,   262,   224,    -1,
     324,   256,    -1,   326,    -1,   325,    -1,   326,   328,    -1,
     325,   262,   328,    -1,   332,   224,   255,    -1,   343,   224,
      -1,   343,   224,   344,    -1,   339,   327,    -1,   327,    -1,
     339,   329,    -1,   329,    -1,   343,    -1,   331,    -1,   330,
     262,   224,    -1,   330,   262,   224,   344,    -1,   330,   262,
     224,   344,   264,   354,    -1,   330,   262,   224,   264,   354,
      -1,   332,    -1,   332,   224,    -1,   332,   224,   344,    -1,
     332,   224,   344,   264,   354,    -1,   332,   224,   264,   354,
      -1,   343,    -1,   339,   343,    -1,   279,    -1,    75,    -1,
      74,    -1,    73,    -1,    77,    -1,    76,   255,   336,   256,
      -1,   337,    -1,   336,   262,   337,    -1,   224,    -1,   224,
     264,   318,    -1,    55,    -1,   280,    -1,   340,    -1,   339,
     340,    -1,   341,    -1,   335,    -1,   346,    -1,   334,    -1,
     333,    -1,   338,    -1,     5,    -1,     3,    -1,     4,    -1,
      50,    -1,    48,    -1,    49,    -1,    47,    -1,    52,    -1,
      53,    -1,    51,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    25,    -1,
      25,   255,   342,   256,    -1,   225,    -1,   342,   262,   225,
      -1,   345,    -1,   345,   344,    -1,   257,   258,    -1,   257,
     313,   258,    -1,   344,   257,   258,    -1,   344,   257,   313,
     258,    -1,   222,    -1,     7,    -1,     8,    -1,    13,    -1,
       9,    -1,    10,    -1,    11,    -1,    12,    -1,     6,    -1,
      41,    -1,    42,    -1,    43,    -1,    61,    -1,    62,    -1,
      63,    -1,    67,    -1,    68,    -1,    69,    -1,    26,    -1,
      27,    -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    40,    -1,    44,    -1,
      45,    -1,    46,    -1,    78,    -1,    79,    -1,    80,    -1,
      81,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      86,    -1,    64,    -1,    65,    -1,    66,    -1,    87,    -1,
      88,    -1,    89,    -1,    90,    -1,    91,    -1,    92,    -1,
      93,    -1,    94,    -1,    95,    -1,    70,    -1,    71,    -1,
      72,    -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
     100,    -1,   101,    -1,   102,    -1,   103,    -1,   104,    -1,
     105,    -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,
     110,    -1,   111,    -1,   112,    -1,   113,    -1,   114,    -1,
     115,    -1,   116,    -1,   136,    -1,   137,    -1,   117,    -1,
     118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,    -1,
     138,    -1,   123,    -1,   124,    -1,   125,    -1,   126,    -1,
     127,    -1,   128,    -1,   139,    -1,   129,    -1,   130,    -1,
     131,    -1,   132,    -1,   133,    -1,   134,    -1,   135,    -1,
     140,    -1,   141,    -1,   142,    -1,   143,    -1,   144,    -1,
     145,    -1,   147,    -1,   148,    -1,   149,    -1,   150,    -1,
     151,    -1,   152,    -1,   153,    -1,   154,    -1,   173,    -1,
     155,    -1,   156,    -1,   157,    -1,   158,    -1,   159,    -1,
     160,    -1,   174,    -1,   161,    -1,   162,    -1,   163,    -1,
     164,    -1,   165,    -1,   166,    -1,   175,    -1,   167,    -1,
     168,    -1,   169,    -1,   170,    -1,   171,    -1,   172,    -1,
     176,    -1,   177,    -1,   178,    -1,   179,    -1,   180,    -1,
     181,    -1,   188,    -1,   189,    -1,   190,    -1,   191,    -1,
     192,    -1,   193,    -1,   194,    -1,   195,    -1,   196,    -1,
     197,    -1,   198,    -1,   199,    -1,   200,    -1,   201,    -1,
     202,    -1,   203,    -1,   204,    -1,   205,    -1,   206,    -1,
     207,    -1,   208,    -1,   209,    -1,   210,    -1,   211,    -1,
     212,    -1,   213,    -1,   214,    -1,   215,    -1,   216,    -1,
     217,    -1,   218,    -1,   219,    -1,   220,    -1,   146,    -1,
     182,    -1,   183,    -1,   184,    -1,   185,    -1,   186,    -1,
     187,    -1,   347,    -1,   225,    -1,   281,    -1,   282,    -1,
     283,    -1,    -1,   221,   224,   259,   348,   350,   260,    -1,
      -1,   221,   259,   349,   350,   260,    -1,   351,    -1,   350,
     351,    -1,   343,   352,   265,    -1,   339,   343,   352,   265,
      -1,   353,    -1,   352,   262,   353,    -1,   224,    -1,   224,
     344,    -1,   315,    -1,   259,   355,   260,    -1,   259,   355,
     262,   260,    -1,   354,    -1,   355,   262,   354,    -1,   319,
      -1,   359,    -1,   358,    -1,   356,    -1,   368,    -1,   369,
      -1,   372,    -1,   375,    -1,   376,    -1,   383,    -1,   259,
     260,    -1,    -1,    -1,   259,   360,   367,   361,   260,    -1,
     366,    -1,   358,    -1,    -1,   364,   359,    -1,    -1,   365,
     358,    -1,   259,   260,    -1,   259,   367,   260,    -1,   357,
      -1,   367,   357,    -1,   265,    -1,   317,   265,    -1,    19,
     255,   317,   256,   370,    -1,   363,    17,   363,    -1,   363,
      -1,   317,    -1,   332,   224,   264,   354,    -1,    -1,    22,
     255,   317,   256,   373,   259,   374,   260,    -1,    -1,   367,
      -1,    23,   317,   263,    -1,    24,   263,    -1,    -1,   223,
     255,   377,   371,   256,   362,    -1,    -1,    16,   378,   357,
     223,   255,   317,   256,   265,    -1,    -1,    18,   255,   379,
     380,   382,   256,   362,    -1,   368,    -1,   356,    -1,   371,
      -1,    -1,   381,   265,    -1,   381,   265,   317,    -1,    15,
     265,    -1,    14,   265,    -1,    21,   265,    -1,    21,   317,
     265,    -1,    20,   265,    -1,   385,    -1,   384,   385,    -1,
     386,    -1,   319,    -1,    -1,   323,   387,   366,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   250,   250,   256,   259,   262,   266,   270,   274,   277,
     281,   287,   290,   298,   301,   304,   307,   310,   315,   323,
     330,   337,   343,   347,   354,   357,   363,   370,   380,   388,
     393,   423,   429,   433,   437,   457,   458,   459,   460,   466,
     467,   472,   477,   486,   487,   492,   500,   501,   507,   516,
     517,   522,   527,   532,   540,   541,   549,   560,   561,   570,
     571,   580,   581,   590,   591,   599,   600,   608,   609,   617,
     618,   618,   636,   637,   652,   656,   660,   664,   669,   673,
     677,   681,   685,   689,   693,   700,   703,   714,   721,   726,
     731,   739,   743,   747,   751,   756,   761,   770,   770,   781,
     785,   792,   799,   802,   809,   817,   837,   855,   870,   893,
     904,   914,   924,   934,   943,   946,   950,   954,   959,   967,
     972,   977,   982,   987,   996,  1007,  1034,  1043,  1050,  1057,
    1064,  1076,  1082,  1085,  1092,  1096,  1100,  1108,  1117,  1120,
    1131,  1134,  1137,  1141,  1145,  1149,  1156,  1160,  1172,  1186,
    1191,  1197,  1203,  1210,  1216,  1221,  1226,  1231,  1238,  1242,
    1246,  1250,  1254,  1258,  1264,  1276,  1279,  1284,  1288,  1297,
    1302,  1310,  1314,  1324,  1328,  1332,  1337,  1344,  1348,  1353,
    1358,  1363,  1367,  1372,  1377,  1382,  1388,  1394,  1400,  1408,
    1416,  1424,  1429,  1434,  1439,  1444,  1449,  1454,  1460,  1466,
    1472,  1478,  1484,  1490,  1496,  1502,  1508,  1513,  1518,  1523,
    1528,  1533,  1538,  1543,  1548,  1553,  1558,  1563,  1568,  1574,
    1580,  1586,  1592,  1598,  1604,  1610,  1616,  1622,  1628,  1634,
    1640,  1648,  1656,  1664,  1672,  1680,  1688,  1696,  1704,  1712,
    1720,  1728,  1736,  1741,  1746,  1751,  1756,  1761,  1766,  1771,
    1776,  1781,  1786,  1791,  1796,  1801,  1806,  1811,  1816,  1821,
    1826,  1831,  1836,  1841,  1846,  1851,  1856,  1861,  1866,  1871,
    1876,  1881,  1886,  1891,  1896,  1901,  1906,  1911,  1916,  1921,
    1926,  1931,  1936,  1941,  1946,  1951,  1956,  1961,  1966,  1971,
    1976,  1981,  1986,  1991,  1996,  2001,  2006,  2011,  2016,  2021,
    2026,  2031,  2036,  2041,  2046,  2051,  2056,  2061,  2066,  2071,
    2076,  2081,  2086,  2091,  2096,  2101,  2106,  2111,  2116,  2121,
    2126,  2131,  2136,  2141,  2146,  2151,  2156,  2161,  2166,  2171,
    2176,  2181,  2186,  2191,  2196,  2201,  2206,  2211,  2216,  2221,
    2226,  2231,  2236,  2241,  2246,  2251,  2256,  2261,  2266,  2271,
    2276,  2281,  2287,  2293,  2299,  2305,  2311,  2317,  2323,  2328,
    2344,  2349,  2354,  2362,  2362,  2373,  2373,  2383,  2386,  2399,
    2417,  2441,  2445,  2451,  2456,  2467,  2470,  2476,  2485,  2488,
    2494,  2498,  2499,  2505,  2506,  2507,  2508,  2509,  2510,  2511,
    2515,  2516,  2520,  2516,  2532,  2533,  2537,  2537,  2544,  2544,
    2558,  2561,  2569,  2577,  2588,  2589,  2593,  2600,  2604,  2612,
    2616,  2629,  2629,  2649,  2652,  2658,  2670,  2682,  2682,  2697,
    2697,  2713,  2713,  2734,  2737,  2743,  2746,  2752,  2756,  2763,
    2768,  2773,  2780,  2783,  2792,  2796,  2803,  2806,  2812,  2812
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "VARYING", "CONST", "BOOL",
  "FLOAT", "DOUBLE", "INT", "UINT", "INT64_T", "UINT64_T", "FLOAT16_T",
  "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF", "DISCARD", "RETURN",
  "SWITCH", "CASE", "DEFAULT", "SUBROUTINE", "BVEC2", "BVEC3", "BVEC4",
  "IVEC2", "IVEC3", "IVEC4", "I64VEC2", "I64VEC3", "I64VEC4", "UVEC2",
  "UVEC3", "UVEC4", "U64VEC2", "U64VEC3", "U64VEC4", "VEC2", "VEC3",
  "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID", "IN", "OUT", "INOUT",
  "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED", "COHERENT", "VOLATILE",
  "RESTRICT", "READONLY", "WRITEONLY", "DVEC2", "DVEC3", "DVEC4", "DMAT2",
  "DMAT3", "DMAT4", "F16VEC2", "F16VEC3", "F16VEC4", "F16MAT2", "F16MAT3",
  "F16MAT4", "NOPERSPECTIVE", "FLAT", "SMOOTH", "LAYOUT",
  "__EXPLICITINTERPAMD", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3",
  "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3", "DMAT2X4",
  "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3", "DMAT4X4",
  "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2", "F16MAT3X3",
  "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4", "ATOMIC_UINT",
  "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE", "SAMPLER1DSHADOW",
  "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW", "SAMPLER1DARRAY",
  "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW", "SAMPLER2DARRAYSHADOW",
  "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D", "ISAMPLERCUBE",
  "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D", "USAMPLER2D",
  "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY", "USAMPLER2DARRAY",
  "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW", "ISAMPLER2DRECT",
  "USAMPLER2DRECT", "SAMPLERBUFFER", "ISAMPLERBUFFER", "USAMPLERBUFFER",
  "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW", "ISAMPLERCUBEARRAY",
  "USAMPLERCUBEARRAY", "SAMPLER2DMS", "ISAMPLER2DMS", "USAMPLER2DMS",
  "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY", "USAMPLER2DMSARRAY",
  "SAMPLEREXTERNALOES", "SAMPLER", "SAMPLERSHADOW", "TEXTURE1D",
  "TEXTURE2D", "TEXTURE3D", "TEXTURECUBE", "TEXTURE1DARRAY",
  "TEXTURE2DARRAY", "ITEXTURE1D", "ITEXTURE2D", "ITEXTURE3D",
  "ITEXTURECUBE", "ITEXTURE1DARRAY", "ITEXTURE2DARRAY", "UTEXTURE1D",
  "UTEXTURE2D", "UTEXTURE3D", "UTEXTURECUBE", "UTEXTURE1DARRAY",
  "UTEXTURE2DARRAY", "TEXTURE2DRECT", "ITEXTURE2DRECT", "UTEXTURE2DRECT",
  "TEXTUREBUFFER", "ITEXTUREBUFFER", "UTEXTUREBUFFER", "TEXTURECUBEARRAY",
  "ITEXTURECUBEARRAY", "UTEXTURECUBEARRAY", "TEXTURE2DMS", "ITEXTURE2DMS",
  "UTEXTURE2DMS", "TEXTURE2DMSARRAY", "ITEXTURE2DMSARRAY",
  "UTEXTURE2DMSARRAY", "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT",
  "ISUBPASSINPUTMS", "USUBPASSINPUT", "USUBPASSINPUTMS", "IMAGE1D",
  "IIMAGE1D", "UIMAGE1D", "IMAGE2D", "IIMAGE2D", "UIMAGE2D", "IMAGE3D",
  "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT", "IIMAGE2DRECT", "UIMAGE2DRECT",
  "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "IMAGE1DARRAY", "IIMAGE1DARRAY", "UIMAGE1DARRAY",
  "IMAGE2DARRAY", "IIMAGE2DARRAY", "UIMAGE2DARRAY", "IMAGECUBEARRAY",
  "IIMAGECUBEARRAY", "UIMAGECUBEARRAY", "IMAGE2DMS", "IIMAGE2DMS",
  "UIMAGE2DMS", "IMAGE2DMSARRAY", "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY",
  "STRUCT", "VOID", "WHILE", "IDENTIFIER", "TYPE_NAME", "FLOATCONSTANT",
  "DOUBLECONSTANT", "INTCONSTANT", "UINTCONSTANT", "INT64CONSTANT",
  "UINT64CONSTANT", "BOOLCONSTANT", "FLOAT16CONSTANT", "LEFT_OP",
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
  "selection_rest_statement", "condition", "switch_statement", "$@9",
  "switch_statement_list", "case_label", "iteration_statement", "$@10",
  "$@11", "$@12", "for_init_statement", "conditionopt",
  "for_rest_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "$@13", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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
     535,   536,   537,   538,   539,   540,   541,   542
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   288,   289,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   291,   291,   291,   291,   291,   291,   292,
     293,   294,   295,   295,   296,   296,   297,   297,   298,   299,
     299,   300,   300,   300,   300,   301,   301,   301,   301,   302,
     302,   302,   302,   303,   303,   303,   304,   304,   304,   305,
     305,   305,   305,   305,   306,   306,   306,   307,   307,   308,
     308,   309,   309,   310,   310,   311,   311,   312,   312,   313,
     314,   313,   315,   315,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   317,   317,   318,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   321,   320,   322,
     322,   323,   324,   324,   325,   325,   326,   327,   327,   328,
     328,   328,   328,   329,   330,   330,   330,   330,   330,   331,
     331,   331,   331,   331,   332,   332,   333,   334,   334,   334,
     334,   335,   336,   336,   337,   337,   337,   338,   339,   339,
     340,   340,   340,   340,   340,   340,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   342,   342,   343,   343,   344,
     344,   344,   344,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     346,   346,   346,   348,   347,   349,   347,   350,   350,   351,
     351,   352,   352,   353,   353,   354,   354,   354,   355,   355,
     356,   357,   357,   358,   358,   358,   358,   358,   358,   358,
     359,   360,   361,   359,   362,   362,   364,   363,   365,   363,
     366,   366,   367,   367,   368,   368,   369,   370,   370,   371,
     371,   373,   372,   374,   374,   375,   375,   377,   376,   378,
     376,   379,   376,   380,   380,   381,   381,   382,   382,   383,
     383,   383,   383,   383,   384,   384,   385,   385,   387,   386
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     4,     1,     3,     2,     2,     1,
       1,     1,     2,     2,     2,     1,     2,     3,     2,     1,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     2,
       4,     2,     3,     4,     2,     3,     4,     0,     6,     2,
       3,     2,     1,     1,     2,     3,     3,     2,     3,     2,
       1,     2,     1,     1,     1,     3,     4,     6,     5,     1,
       2,     3,     5,     4,     1,     2,     1,     1,     1,     1,
       1,     4,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     1,     2,     2,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     0,     6,     0,     5,     1,     2,     3,
       4,     1,     3,     1,     2,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     0,     5,     1,     1,     0,     2,     0,     2,
       2,     3,     1,     2,     1,     2,     5,     3,     1,     1,
       4,     0,     8,     0,     1,     3,     2,     0,     6,     0,
       8,     0,     7,     1,     1,     1,     0,     2,     3,     2,
       2,     2,     3,     2,     1,     2,     1,     1,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   147,   148,   146,   181,   174,   175,   177,   178,   179,
     180,   176,   163,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   182,   183,
     184,   206,   207,   208,   152,   150,   151,   149,   155,   153,
     154,   156,   157,   158,   159,   160,   161,   162,   185,   186,
     187,   218,   219,   220,   188,   189,   190,   230,   231,   232,
     129,   128,   127,     0,   130,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   256,   257,   258,   259,   260,   261,
     263,   264,   265,   266,   267,   268,   270,   271,   272,   273,
     274,   275,   276,   254,   255,   262,   269,   277,   278,   279,
     280,   281,   282,   351,   283,   284,   285,   286,   287,   288,
     289,   290,   292,   293,   294,   295,   296,   297,   299,   300,
     301,   302,   303,   304,   306,   307,   308,   309,   310,   311,
     291,   298,   305,   312,   313,   314,   315,   316,   317,   352,
     353,   354,   355,   356,   357,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,     0,   173,
     359,   126,   137,   360,   361,   362,     0,   437,     0,   438,
       0,   103,   102,     0,   114,   119,   144,   143,   141,   145,
       0,   138,   140,   124,   167,   142,   358,     0,   434,   436,
       0,     0,     0,   365,     0,     0,    91,    88,     0,   101,
       0,   110,   104,   112,     0,   113,     0,    89,   120,     0,
      94,   139,   125,     0,   168,     1,   435,   165,     0,   136,
     134,     0,   132,   363,     0,     0,    92,     0,     0,   439,
     105,   109,   111,   107,   115,   106,     0,   121,    97,     0,
      95,     0,     2,     8,     9,     4,     5,     6,     7,    11,
      10,     0,     0,     0,   169,    37,    36,    38,    35,     3,
      13,    31,    15,    20,    21,     0,     0,    25,     0,    39,
       0,    43,    46,    49,    54,    57,    59,    61,    63,    65,
      67,    69,     0,    29,     0,   164,     0,     0,   131,     0,
       0,     0,     0,     0,   367,    90,    93,     0,     0,   419,
       0,     0,     0,     0,     0,     0,     0,     0,   391,   400,
     404,    39,    72,    85,     0,   380,     0,   124,   383,   402,
     382,   381,     0,   384,   385,   386,   387,   388,   389,   108,
       0,   116,     0,   375,   123,     0,     0,    99,     0,    96,
      32,    33,     0,    17,    18,     0,     0,    23,    22,     0,
     173,    26,    28,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,   170,   171,     0,   166,    87,   135,
     133,     0,     0,   373,     0,   371,   366,   368,   430,   429,
       0,   421,     0,   433,   431,     0,     0,     0,   416,   417,
     390,     0,    75,    76,    78,    77,    80,    81,    82,    83,
      84,    79,    74,     0,     0,   405,   401,   403,   118,     0,
     378,     0,   122,     0,   100,    12,     0,    19,    16,    27,
      40,    41,    42,    45,    44,    47,    48,    52,    53,    50,
      51,    55,    56,    58,    60,    62,    64,    66,    68,     0,
     172,   364,     0,   374,     0,   369,     0,     0,     0,   432,
       0,   415,     0,   392,    73,    86,   117,   376,     0,    98,
      14,     0,   370,   372,     0,   424,   423,   426,   398,   411,
     409,     0,     0,     0,     0,   377,   379,     0,     0,   425,
       0,     0,   408,     0,     0,   406,     0,     0,     0,   393,
      71,     0,   427,     0,   398,   397,   399,   413,     0,   395,
     418,   394,     0,   428,   422,   407,   414,     0,   410,   420,
     412
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   309,   310,   311,   476,   312,   313,   314,   315,   316,
     317,   318,   361,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   362,   499,   363,   463,   364,
     429,   365,   218,   386,   291,   366,   220,   221,   222,   251,
     252,   253,   223,   224,   225,   226,   227,   228,   271,   272,
     229,   230,   231,   232,   268,   333,   264,   234,   235,   236,
     340,   274,   343,   344,   434,   435,   384,   471,   368,   369,
     370,   371,   451,   534,   560,   542,   543,   544,   561,   372,
     373,   374,   545,   533,   375,   546,   567,   376,   377,   512,
     440,   507,   527,   540,   541,   378,   237,   238,   239,   248
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -512
static const yytype_int16 yypact[] =
{
    2538,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -235,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -201,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -203,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -153,  -512,  -210,  -220,
    -152,  -189,  4119,  -160,  -512,  -128,  -512,  -512,  -512,  -512,
    3079,  -512,  -512,  -512,  -122,  -512,  -512,   564,  -512,  -512,
     -72,   -46,  -105,  -512,  6148,  -216,  -512,  -512,  -102,  -512,
    4119,  -512,  -512,  -512,  4119,   -68,   -66,  -512,  -225,  -187,
    -512,  -512,  -512,  4606,   -98,  -512,  -512,  -512,  -179,  -512,
    -104,  -172,  -512,  -512,  4119,  -101,  -512,  -186,   846,  -512,
    -512,  -512,  -512,  -122,  -233,  -512,  4870,  -217,  -512,   -63,
    -512,  -151,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  5648,  5648,  5648,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -209,  -512,  -512,  -512,   -94,  -170,  5898,   -92,  -512,
    5648,  -139,  -133,  -109,  -223,  -103,  -111,  -108,  -106,   -71,
     -74,  -218,   -86,  -512,  5134,  -512,   -52,  5648,  -512,   -46,
    4119,  4119,   -50,  3342,  -512,  -512,  -512,   -90,   -89,  -512,
     -78,   -76,   -85,  5398,   -70,  5648,   -80,   -69,   -64,  -512,
    -512,  -184,  -512,  -512,  -150,  -512,  -220,   -67,  -512,  -512,
    -512,  -512,  1128,  -512,  -512,  -512,  -512,  -512,  -512,   -98,
    4870,  -183,  4870,  -512,  -512,  4870,  4119,  -512,   -40,  -512,
    -512,  -512,  -169,  -512,  -512,  5648,   -35,  -512,  -512,  5648,
     -65,  -512,  -512,  -512,  5648,  5648,  5648,  5648,  5648,  5648,
    5648,  5648,  5648,  5648,  5648,  5648,  5648,  5648,  5648,  5648,
    5648,  5648,  5648,  -512,  -512,  -512,   -61,  -512,  -512,  -512,
    -512,  3601,   -50,  -122,  -144,  -512,  -512,  -512,  -512,  -512,
    1410,  -512,  5648,  -512,  -512,  -142,  5648,  -123,  -512,  -512,
    -512,  1410,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  5648,  5648,  -512,  -512,  -512,  -512,  4870,
    -512,  -226,  -512,  3860,  -512,  -512,   -60,   -62,  -512,  -512,
    -512,  -512,  -512,  -139,  -139,  -133,  -133,  -109,  -109,  -109,
    -109,  -223,  -223,  -103,  -111,  -108,  -106,   -71,   -74,  5648,
    -512,  -512,  -138,   -98,   -50,  -512,   -33,  2256,  -168,  -512,
    -167,  -512,  2798,  1410,  -512,  -512,  -512,  -512,  4342,  -512,
    -512,  -121,  -512,  -512,   -56,  -512,  -512,  2798,   -58,  -512,
     -62,   -32,  4119,   -49,   -51,  -512,  -512,  5648,  5648,  -512,
     -57,   -45,   177,   -55,  1974,  -512,   -47,   -44,  1692,  -512,
    -512,  -165,  5648,  1692,   -58,  -512,  -512,  1410,  4870,  -512,
    -512,  -512,   -48,   -62,  -512,  -512,  1410,   -42,  -512,  -512,
    -512
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,   -96,  -512,  -263,  -262,  -304,  -264,  -204,  -199,
    -205,  -197,  -206,  -196,  -512,  -252,  -512,  -282,  -512,  -296,
    -512,     3,  -512,  -512,  -512,     6,  -512,  -512,  -512,   -29,
     -23,   -26,  -512,  -512,  -489,  -512,  -512,  -512,  -512,  -118,
    -512,  -221,  -228,  -512,  -512,     0,  -240,  -512,    13,  -512,
    -512,  -512,  -328,  -330,  -200,  -271,  -363,  -512,  -273,  -364,
    -511,  -308,  -512,  -512,  -314,  -309,  -512,  -512,    -2,  -441,
    -260,  -512,  -512,  -279,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,    12,  -512,  -512
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -397
static const yytype_int16 yytable[] =
{
     233,   254,   261,   217,   383,   277,   219,   392,   467,   269,
     513,   332,   431,   437,   245,   411,   412,   468,   287,   470,
     240,   242,   472,   531,   263,   422,   261,   393,   394,   254,
     285,   380,   263,   556,   517,   401,   518,   559,   531,   286,
     334,   263,   559,   379,   381,   247,   -30,   385,   395,   276,
     413,   414,   396,   341,   241,   246,   243,   445,   473,   447,
     423,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   334,   288,   250,   334,   289,   506,   335,   290,   346,
     462,   469,   426,   336,   338,   428,   398,   475,   528,   529,
     339,   562,   399,   464,   464,   464,   258,   464,   383,   477,
     383,   437,   256,   383,   249,   257,   516,   487,   488,   489,
     490,   388,   464,   261,   389,   465,   566,   479,   504,   341,
     464,   505,   341,   509,   504,   409,   410,   522,   213,   214,
     215,   404,   405,   406,   407,   263,   408,   415,   416,   464,
     511,   464,   537,   437,   483,   484,   508,   485,   486,   467,
     510,   491,   492,   267,   273,   536,   283,   278,   284,   334,
     337,   387,   397,   402,   345,   341,   417,   319,   418,   419,
     421,   420,   424,   427,   433,   438,   439,   441,   270,   442,
     443,   514,   515,   448,   474,   446,   449,   383,   -29,   478,
     524,   -24,   547,   503,   554,   568,   450,   500,   520,   538,
     464,  -396,   467,   521,   358,   390,   391,   548,   552,   549,
     341,   553,   557,   493,   495,   497,   530,   569,   570,   494,
     558,   430,   255,   496,   403,   281,   498,   280,   282,   244,
     262,   530,   502,   523,   525,   555,   383,   233,   319,   564,
     217,   319,   551,   219,   275,   565,   279,   526,   539,   266,
     255,     0,   341,     0,   255,   550,   563,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   342,     0,   383,     0,   367,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   532,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   261,     0,   532,     0,   480,   481,
     482,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     342,   432,     0,   342,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   367,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   342,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   342,     0,     0,     0,     0,     0,     0,     0,     0,
     367,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   367,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   342,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   367,     0,     0,
       0,     0,   367,   367,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   367,     0,     0,
       0,     0,   262,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   367,     0,     0,     0,   367,     0,
       0,     0,     0,   367,     0,     0,     0,   367,     0,     0,
       0,     0,     0,     0,   265,     0,   367,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     203,   204,   205,   206,   207,   208,   209,     0,     0,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   211,   212,   213,   214,   215,   216,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     347,   348,   349,     0,   350,   351,   352,   353,   354,   355,
     356,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   357,
     292,   210,   293,   294,   295,   296,   297,   298,   299,   300,
       0,     0,   301,   302,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   303,     0,     0,     0,   358,   359,     0,     0,     0,
       0,   360,   305,   306,   307,   308,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   211,   212,   213,   214,   215,
     216,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   347,   348,   349,     0,   350,   351,   352,   353,
     354,   355,   356,    12,    13,    14,    15,    16,    17,    18,
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
     209,   357,   292,   210,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,   358,   466,     0,
       0,     0,     0,   360,   305,   306,   307,   308,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   211,   212,   213,
     214,   215,   216,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,   347,   348,   349,     0,   350,   351,
     352,   353,   354,   355,   356,    12,    13,    14,    15,    16,
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
     207,   208,   209,   357,   292,   210,   293,   294,   295,   296,
     297,   298,   299,   300,     0,     0,   301,   302,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   303,     0,     0,     0,   358,
       0,     0,     0,     0,     0,   360,   305,   306,   307,   308,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   211,
     212,   213,   214,   215,   216,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   347,   348,   349,     0,
     350,   351,   352,   353,   354,   355,   356,    12,    13,    14,
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
     205,   206,   207,   208,   209,   357,   292,   210,   293,   294,
     295,   296,   297,   298,   299,   300,     0,     0,   301,   302,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   303,     0,     0,
       0,   278,     0,     0,     0,     0,     0,   360,   305,   306,
     307,   308,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   211,   212,   213,   214,   215,   216,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   347,   348,
     349,     0,   350,   351,   352,   353,   354,   355,   356,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     203,   204,   205,   206,   207,   208,   209,   357,   292,   210,
     293,   294,   295,   296,   297,   298,   299,   300,     0,     0,
     301,   302,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   303,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   360,
     305,   306,   307,   308,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   211,   212,   213,   214,   215,   216,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     292,   210,   293,   294,   295,   296,   297,   298,   299,   300,
       0,     0,   301,   302,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   303,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   360,   305,   306,   307,   308,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   211,   212,   213,   214,   215,
     216,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,    14,    15,    16,    17,    18,
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
     209,     0,     0,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,   211,   212,   213,
     214,   215,   216,    12,    13,    14,    15,    16,    17,    18,
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
     209,     0,   292,   210,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   305,   306,   307,   308,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   211,   212,   213,
     214,   215,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    14,    15,    16,    17,
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
     208,   209,     0,   259,   210,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   260,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,   211,   212,
     213,   214,   215,     0,     0,     0,     0,    12,    13,    14,
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
     205,   206,   207,   208,   209,     0,     0,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   436,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
       0,   211,   212,   213,   214,   215,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
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
     206,   207,   208,   209,     0,     0,   210,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
     211,   212,   213,   214,   215,    12,    13,    14,    15,    16,
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
     207,   208,   209,     0,     0,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     519,     0,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,     0,   211,
     212,   213,   214,   215,    12,    13,    14,    15,    16,    17,
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
     208,   209,     0,     0,   210,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   211,   212,
     213,   214,   215,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
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
     205,   206,   207,   208,   209,     0,   292,   210,   293,   294,
     295,   296,   297,   298,   299,   300,     0,     0,   301,   302,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   303,     0,     0,
       0,   382,   535,     0,     0,     0,     0,     0,   305,   306,
     307,   308,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     292,   210,   293,   294,   295,   296,   297,   298,   299,   300,
       0,     0,   301,   302,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   303,     0,     0,   304,     0,     0,     0,     0,     0,
       0,     0,   305,   306,   307,   308,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,     0,     0,     0,    65,    66,
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
     207,   208,   209,     0,   292,   210,   293,   294,   295,   296,
     297,   298,   299,   300,     0,     0,   301,   302,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   303,     0,     0,     0,   382,
       0,     0,     0,     0,     0,     0,   305,   306,   307,   308,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,     0,     0,     0,
       0,     0,    65,    66,    67,    68,    69,    70,    71,    72,
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
     203,   204,   205,   206,   207,   208,   209,     0,   292,   210,
     293,   294,   295,   296,   297,   298,   299,   300,     0,     0,
     301,   302,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   303,
       0,     0,   425,     0,     0,     0,     0,     0,     0,     0,
     305,   306,   307,   308,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     0,     0,     0,     0,     0,    65,    66,    67,    68,
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
     209,     0,   292,   210,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     4,     5,     6,     7,     8,     9,
      10,    11,     0,   444,   305,   306,   307,   308,     0,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     0,     0,     0,     0,     0,    65,    66,    67,    68,
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
     209,     0,   292,   210,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,   305,   306,   307,   308,     0,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     0,     0,     0,     0,     0,    65,    66,    67,    68,
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
     400,     0,   292,   210,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,   305,   306,   307,   308,     0,     0,
       0,     0,     0,     0,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     0,     0,     0,     0,     0,    65,    66,    67,    68,
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
     209,     0,     0,   210
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-512)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,   222,   230,     0,   286,   245,     0,   303,   372,    55,
     451,   263,   340,   343,   224,   238,   239,   380,   258,   382,
     255,   224,   385,   512,   257,   243,   254,   236,   237,   250,
     255,   264,   257,   544,   260,   317,   262,   548,   527,   264,
     257,   257,   553,   283,   284,   265,   255,   264,   257,   265,
     273,   274,   261,   274,   255,   265,   259,   353,   386,   355,
     278,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   257,   259,   262,   257,   262,   440,   256,   265,   265,
     264,   264,   334,   262,   256,   337,   256,   256,   256,   256,
     262,   256,   262,   262,   262,   262,   224,   262,   380,   395,
     382,   431,   262,   385,   256,   265,   469,   411,   412,   413,
     414,   262,   262,   341,   265,   265,   557,   399,   262,   340,
     262,   265,   343,   265,   262,   234,   235,   265,   281,   282,
     283,   270,   271,   272,   267,   257,   269,   240,   241,   262,
     263,   262,   263,   473,   407,   408,   442,   409,   410,   513,
     446,   415,   416,   225,   259,   518,   224,   259,   224,   257,
     264,   224,   256,   255,   265,   386,   277,   263,   276,   275,
     244,   242,   258,   225,   224,   265,   265,   255,   224,   255,
     265,   463,   464,   263,   224,   255,   255,   469,   255,   224,
     223,   256,   224,   433,    17,   558,   260,   258,   258,   255,
     262,   259,   566,   499,   259,   301,   302,   256,   265,   260,
     431,   256,   259,   417,   419,   421,   512,   265,   260,   418,
     264,   339,   222,   420,   320,   254,   422,   250,   254,   216,
     230,   527,   432,   504,   507,   543,   518,   237,   334,   553,
     237,   337,   538,   237,   244,   554,   248,   507,   527,   237,
     250,    -1,   473,    -1,   254,   537,   552,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   274,    -1,   558,    -1,   278,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   512,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   532,    -1,   527,    -1,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     340,   341,    -1,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   451,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   473,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   507,    -1,    -1,
      -1,    -1,   512,   513,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   527,    -1,    -1,
      -1,    -1,   532,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   544,    -1,    -1,    -1,   548,    -1,
      -1,    -1,    -1,   553,    -1,    -1,    -1,   557,    -1,    -1,
      -1,    -1,    -1,    -1,     0,    -1,   566,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
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
     216,   217,   218,   219,   220,   221,   222,    -1,    -1,   225,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   279,   280,   281,   282,   283,   284,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    23,
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
      -1,    -1,   236,   237,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,    -1,   259,   260,    -1,    -1,    -1,
      -1,   265,   266,   267,   268,   269,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   279,   280,   281,   282,   283,
     284,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
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
     232,   233,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   255,    -1,    -1,    -1,   259,   260,    -1,
      -1,    -1,    -1,   265,   266,   267,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   279,   280,   281,
     282,   283,   284,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    18,    19,
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
     230,   231,   232,   233,    -1,    -1,   236,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,   259,
      -1,    -1,    -1,    -1,    -1,   265,   266,   267,   268,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   279,
     280,   281,   282,   283,   284,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
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
     228,   229,   230,   231,   232,   233,    -1,    -1,   236,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,    -1,    -1,
      -1,   259,    -1,    -1,    -1,    -1,    -1,   265,   266,   267,
     268,   269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   279,   280,   281,   282,   283,   284,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
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
     226,   227,   228,   229,   230,   231,   232,   233,    -1,    -1,
     236,   237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,
     266,   267,   268,   269,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   279,   280,   281,   282,   283,   284,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,    -1,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
      -1,    -1,   236,   237,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   265,   266,   267,   268,   269,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   279,   280,   281,   282,   283,
     284,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
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
     222,    -1,    -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,   279,   280,   281,
     282,   283,   284,    25,    26,    27,    28,    29,    30,    31,
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
     222,    -1,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   255,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   266,   267,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   279,   280,   281,
     282,   283,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
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
     221,   222,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   265,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,   279,   280,
     281,   282,   283,    -1,    -1,    -1,    -1,    25,    26,    27,
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
     218,   219,   220,   221,   222,    -1,    -1,   225,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   260,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,   279,   280,   281,   282,   283,    25,    26,    27,    28,
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
     219,   220,   221,   222,    -1,    -1,   225,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   260,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
     279,   280,   281,   282,   283,    25,    26,    27,    28,    29,
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
     220,   221,   222,    -1,    -1,   225,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     260,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,   279,
     280,   281,   282,   283,    25,    26,    27,    28,    29,    30,
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
     221,   222,    -1,    -1,   225,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   279,   280,
     281,   282,   283,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
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
     218,   219,   220,   221,   222,    -1,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,    -1,    -1,   236,   237,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,    -1,    -1,
      -1,   259,   260,    -1,    -1,    -1,    -1,    -1,   266,   267,
     268,   269,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,    -1,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
      -1,    -1,   236,   237,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,   258,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   266,   267,   268,   269,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    78,    79,
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
     220,   221,   222,    -1,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,    -1,    -1,   236,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   255,    -1,    -1,    -1,   259,
      -1,    -1,    -1,    -1,    -1,    -1,   266,   267,   268,   269,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
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
     216,   217,   218,   219,   220,   221,   222,    -1,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,    -1,    -1,
     236,   237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,
      -1,    -1,   258,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     266,   267,   268,   269,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
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
     222,    -1,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   255,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,   265,   266,   267,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
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
     222,    -1,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   255,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,   266,   267,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
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
     222,    -1,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   255,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,   266,   267,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
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
     222,    -1,    -1,   225
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    25,    26,    27,    28,    29,    30,    31,    32,
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
     225,   279,   280,   281,   282,   283,   284,   319,   320,   323,
     324,   325,   326,   330,   331,   332,   333,   334,   335,   338,
     339,   340,   341,   343,   345,   346,   347,   384,   385,   386,
     255,   255,   224,   259,   346,   224,   265,   265,   387,   256,
     262,   327,   328,   329,   339,   343,   262,   265,   224,   224,
     265,   340,   343,   257,   344,     0,   385,   225,   342,    55,
     224,   336,   337,   259,   349,   343,   265,   344,   259,   366,
     328,   327,   329,   224,   224,   255,   264,   344,   259,   262,
     265,   322,   224,   226,   227,   228,   229,   230,   231,   232,
     233,   236,   237,   255,   258,   266,   267,   268,   269,   289,
     290,   291,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   343,   257,   256,   262,   264,   256,   262,
     348,   339,   343,   350,   351,   265,   265,    14,    15,    16,
      18,    19,    20,    21,    22,    23,    24,   223,   259,   260,
     265,   300,   313,   315,   317,   319,   323,   343,   356,   357,
     358,   359,   367,   368,   369,   372,   375,   376,   383,   344,
     264,   344,   259,   315,   354,   264,   321,   224,   262,   265,
     300,   300,   317,   236,   237,   257,   261,   256,   256,   262,
     222,   315,   255,   300,   270,   271,   272,   267,   269,   234,
     235,   238,   239,   273,   274,   240,   241,   277,   276,   275,
     242,   244,   243,   278,   258,   258,   313,   225,   313,   318,
     337,   350,   343,   224,   352,   353,   260,   351,   265,   265,
     378,   255,   255,   265,   265,   317,   255,   317,   263,   255,
     260,   360,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   264,   316,   262,   265,   260,   357,   354,   264,
     354,   355,   354,   350,   224,   256,   292,   317,   224,   315,
     300,   300,   300,   302,   302,   303,   303,   304,   304,   304,
     304,   305,   305,   306,   307,   308,   309,   310,   311,   314,
     258,   260,   352,   344,   262,   265,   357,   379,   317,   265,
     317,   263,   377,   367,   315,   315,   354,   260,   262,   260,
     258,   317,   265,   353,   223,   356,   368,   380,   256,   256,
     317,   332,   339,   371,   361,   260,   354,   263,   255,   371,
     381,   382,   363,   364,   365,   370,   373,   224,   256,   260,
     315,   317,   265,   256,    17,   359,   358,   259,   264,   358,
     362,   366,   256,   317,   362,   363,   367,   374,   354,   265,
     260
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, parseContext)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (pParseContext);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, pParseContext)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, glslang::TParseContext* pParseContext)
#else
static void
yy_reduce_print (yyvsp, yyrule, pParseContext)
    YYSTYPE *yyvsp;
    int yyrule;
    glslang::TParseContext* pParseContext;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , pParseContext);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, pParseContext); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, pParseContext)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (pParseContext);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (glslang::TParseContext* pParseContext)
#else
int
yyparse (pParseContext)
    glslang::TParseContext* pParseContext;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 250 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[(1) - (1)].lex).loc, (yyvsp[(1) - (1)].lex).symbol, (yyvsp[(1) - (1)].lex).string);
    }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 256 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 259 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).i, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 262 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).u, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 266 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).i64, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 270 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).u64, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 274 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtFloat, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 277 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtDouble, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 281 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtFloat16, (yyvsp[(1) - (1)].lex).loc, true);
#endif
    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 287 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).b, (yyvsp[(1) - (1)].lex).loc, true);
    }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 290 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 298 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 301 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[(2) - (4)].lex).loc, (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(3) - (4)].interm.intermTypedNode));
    }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 304 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 307 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[(3) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode), *(yyvsp[(3) - (3)].lex).string);
    }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 310 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (2)].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).loc, "++", (yyvsp[(1) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(2) - (2)].lex).loc, "++", EOpPostIncrement, (yyvsp[(1) - (2)].interm.intermTypedNode));
    }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 315 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (2)].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).loc, "--", (yyvsp[(1) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(2) - (2)].lex).loc, "--", EOpPostDecrement, (yyvsp[(1) - (2)].interm.intermTypedNode));
    }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 323 "glslang.y"
    {
        parseContext.integerCheck((yyvsp[(1) - (1)].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 330 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[(1) - (1)].interm).loc, (yyvsp[(1) - (1)].interm).function, (yyvsp[(1) - (1)].interm).intermNode);
        delete (yyvsp[(1) - (1)].interm).function;
    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 337 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 343 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 347 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 354 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
    }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 357 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 363 "glslang.y"
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[(2) - (2)].interm.intermTypedNode)->getType());
        (yyvsp[(1) - (2)].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (2)].interm).function;
        (yyval.interm).intermNode = (yyvsp[(2) - (2)].interm.intermTypedNode);
    }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 370 "glslang.y"
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[(3) - (3)].interm.intermTypedNode)->getType());
        (yyvsp[(1) - (3)].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (3)].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermNode, (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 380 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 388 "glslang.y"
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type));
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 393 "glslang.y"
    {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
            (yyval.interm).intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                (yyval.interm).function = function;
            } else
                parseContext.error((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ((yyval.interm).function == 0) {
            // error recover
            TString empty("");
            (yyval.interm).function = new TFunction(&empty, TType(EbtVoid), EOpNull);
        }
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 423 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (1)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 429 "glslang.y"
    {
        parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).loc, "++", (yyvsp[(2) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].lex).loc, "++", EOpPreIncrement, (yyvsp[(2) - (2)].interm.intermTypedNode));
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 433 "glslang.y"
    {
        parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).loc, "--", (yyvsp[(2) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].lex).loc, "--", EOpPreDecrement, (yyvsp[(2) - (2)].interm.intermTypedNode));
    }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 437 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm).op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch((yyvsp[(1) - (2)].interm).op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].interm).loc, errorOp, (yyvsp[(1) - (2)].interm).op, (yyvsp[(2) - (2)].interm.intermTypedNode));
        } else {
            (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
            if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
                (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
        }
    }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 457 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpNull; }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 458 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpNegative; }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 459 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpLogicalNot; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 460 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise not"); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 466 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 467 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "*", EOpMul, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 472 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "/", EOpDiv, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 477 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "%", EOpMod, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 486 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 487 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "+", EOpAdd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 492 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "-", EOpSub, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 500 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 501 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<<", EOpLeftShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 507 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">>", EOpRightShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 516 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 517 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<", EOpLessThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 522 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">", EOpGreaterThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 527 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<=", EOpLessThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 532 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 540 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 541 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "==", EOpEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 549 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "!=", EOpNotEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 560 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 561 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "&", EOpAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 570 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 571 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "^", EOpExclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 580 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 581 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "|", EOpInclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 590 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 591 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "&&", EOpLogicalAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 599 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 600 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "^^", EOpLogicalXor, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 608 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 609 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "||", EOpLogicalOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 617 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 618 "glslang.y"
    {
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 621 "glslang.y"
    {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[(2) - (6)].lex).loc, (yyvsp[(1) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(2) - (6)].lex).loc, "?", (yyvsp[(1) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(5) - (6)].lex).loc, ":", (yyvsp[(4) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(5) - (6)].lex).loc, ":", (yyvsp[(6) - (6)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[(1) - (6)].interm.intermTypedNode), (yyvsp[(4) - (6)].interm.intermTypedNode), (yyvsp[(6) - (6)].interm.intermTypedNode), (yyvsp[(2) - (6)].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (6)].lex).loc, ":", (yyvsp[(4) - (6)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(6) - (6)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(6) - (6)].interm.intermTypedNode);
        }
    }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 636 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 637 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(3) - (3)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addAssign((yyvsp[(2) - (3)].interm).op, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].interm).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 652 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 656 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 660 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 664 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 669 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 673 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 677 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 681 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 685 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 689 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 693 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 700 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 703 "glslang.y"
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[(2) - (3)].lex).loc, ",", (yyvsp[(3) - (3)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).loc, ",", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(3) - (3)].interm.intermTypedNode);
        }
    }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 714 "glslang.y"
    {
        parseContext.constantValueCheck((yyvsp[(1) - (1)].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 721 "glslang.y"
    {
        parseContext.handleFunctionDeclarator((yyvsp[(1) - (2)].interm).loc, *(yyvsp[(1) - (2)].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 726 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm).intermNode && (yyvsp[(1) - (2)].interm).intermNode->getAsAggregate())
            (yyvsp[(1) - (2)].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(1) - (2)].interm).intermNode;
    }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 731 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (4)].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[(1) - (4)].lex).loc, (yyvsp[(3) - (4)].interm.type), (yyvsp[(2) - (4)].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 739 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (2)].interm).loc, *(yyvsp[(1) - (2)].interm).typeList);
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 743 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (3)].interm).loc, *(yyvsp[(1) - (3)].interm).typeList, (yyvsp[(2) - (3)].lex).string);
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 747 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (4)].interm).loc, *(yyvsp[(1) - (4)].interm).typeList, (yyvsp[(2) - (4)].lex).string, (yyvsp[(3) - (4)].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 751 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type));
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 756 "glslang.y"
    {
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).qualifier, *(yyvsp[(2) - (3)].lex).string);
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 761 "glslang.y"
    {
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).shaderQualifiers);
        (yyvsp[(3) - (4)].interm.identifierList)->push_back((yyvsp[(2) - (4)].lex).string);
        parseContext.addQualifierToExisting((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).qualifier, *(yyvsp[(3) - (4)].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 770 "glslang.y"
    { parseContext.nestedBlockCheck((yyvsp[(1) - (3)].interm.type).loc); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 770 "glslang.y"
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[(2) - (6)].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (6)].interm.type).loc, (yyvsp[(1) - (6)].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (6)].interm.type).loc, (yyvsp[(1) - (6)].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[(1) - (6)].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[(1) - (6)].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[(5) - (6)].interm.typeList);
    }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 781 "glslang.y"
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[(2) - (2)].lex).string);
    }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 785 "glslang.y"
    {
        (yyval.interm.identifierList) = (yyvsp[(1) - (3)].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[(3) - (3)].lex).string);
    }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 792 "glslang.y"
    {
        (yyval.interm).function = (yyvsp[(1) - (2)].interm.function);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 799 "glslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);
    }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 802 "glslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);
    }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 809 "glslang.y"
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[(1) - (2)].interm.function);
        if ((yyvsp[(2) - (2)].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[(1) - (2)].interm.function)->addParameter((yyvsp[(2) - (2)].interm).param);
        else
            delete (yyvsp[(2) - (2)].interm).param.type;
    }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 817 "glslang.y"
    {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ((yyvsp[(3) - (3)].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[(2) - (3)].lex).loc, "cannot be an argument type except for '(void)'", "void", "");
            delete (yyvsp[(3) - (3)].interm).param.type;
        } else {
            // Add the parameter
            (yyval.interm.function) = (yyvsp[(1) - (3)].interm.function);
            (yyvsp[(1) - (3)].interm.function)->addParameter((yyvsp[(3) - (3)].interm).param);
        }
    }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 837 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).qualifier.storage != EvqGlobal && (yyvsp[(1) - (3)].interm.type).qualifier.storage != EvqTemporary) {
            parseContext.error((yyvsp[(2) - (3)].lex).loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString((yyvsp[(1) - (3)].interm.type).qualifier.storage), "");
        }
        if ((yyvsp[(1) - (3)].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type((yyvsp[(1) - (3)].interm.type));
        function = new TFunction((yyvsp[(2) - (3)].lex).string, type);
        (yyval.interm.function) = function;
    }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 855 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (2)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (2)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (2)].interm.type).loc, *(yyvsp[(1) - (2)].interm.type).arraySizes);
        }
        if ((yyvsp[(1) - (2)].interm.type).basicType == EbtVoid) {
            parseContext.error((yyvsp[(2) - (2)].lex).loc, "illegal use of type 'void'", (yyvsp[(2) - (2)].lex).string->c_str(), "");
        }
        parseContext.reservedErrorCheck((yyvsp[(2) - (2)].lex).loc, *(yyvsp[(2) - (2)].lex).string);

        TParameter param = {(yyvsp[(2) - (2)].lex).string, new TType((yyvsp[(1) - (2)].interm.type))};
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
        (yyval.interm).param = param;
    }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 870 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);
        }
        parseContext.arrayDimCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.type).arraySizes, (yyvsp[(3) - (3)].interm).arraySizes);

        parseContext.arraySizeRequiredCheck((yyvsp[(3) - (3)].interm).loc, *(yyvsp[(3) - (3)].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[(2) - (3)].lex).loc, *(yyvsp[(2) - (3)].lex).string);

        (yyvsp[(1) - (3)].interm.type).arraySizes = (yyvsp[(3) - (3)].interm).arraySizes;

        TParameter param = { (yyvsp[(2) - (3)].lex).string, new TType((yyvsp[(1) - (3)].interm.type))};
        (yyval.interm).loc = (yyvsp[(2) - (3)].lex).loc;
        (yyval.interm).param = param;
    }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 893 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if ((yyvsp[(1) - (2)].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[(1) - (2)].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(1) - (2)].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, *(yyval.interm).param.type);

    }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 904 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);

        parseContext.parameterTypeCheck((yyvsp[(1) - (1)].interm).loc, EvqIn, *(yyvsp[(1) - (1)].interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (1)].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 914 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if ((yyvsp[(1) - (2)].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[(1) - (2)].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[(1) - (2)].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(1) - (2)].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, *(yyval.interm).param.type);
    }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 924 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);

        parseContext.parameterTypeCheck((yyvsp[(1) - (1)].interm).loc, EvqIn, *(yyvsp[(1) - (1)].interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (1)].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 934 "glslang.y"
    {
        TParameter param = { 0, new TType((yyvsp[(1) - (1)].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[(1) - (1)].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (1)].interm.type).loc, *(yyvsp[(1) - (1)].interm.type).arraySizes);
    }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 943 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 946 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (3)].interm);
        parseContext.declareVariable((yyvsp[(3) - (3)].lex).loc, *(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm).type);
    }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 950 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (4)].interm);
        parseContext.declareVariable((yyvsp[(3) - (4)].lex).loc, *(yyvsp[(3) - (4)].lex).string, (yyvsp[(1) - (4)].interm).type, (yyvsp[(4) - (4)].interm).arraySizes);
    }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 954 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (6)].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(3) - (6)].lex).loc, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(1) - (6)].interm).type, (yyvsp[(4) - (6)].interm).arraySizes, (yyvsp[(6) - (6)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (6)].interm).intermNode, initNode, (yyvsp[(5) - (6)].lex).loc);
    }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 959 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (5)].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(3) - (5)].lex).loc, *(yyvsp[(3) - (5)].lex).string, (yyvsp[(1) - (5)].interm).type, 0, (yyvsp[(5) - (5)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (5)].interm).intermNode, initNode, (yyvsp[(4) - (5)].lex).loc);
    }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 967 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 972 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (2)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[(2) - (2)].lex).loc, *(yyvsp[(2) - (2)].lex).string, (yyvsp[(1) - (2)].interm.type));
    }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 977 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (3)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[(2) - (3)].lex).loc, *(yyvsp[(2) - (3)].lex).string, (yyvsp[(1) - (3)].interm.type), (yyvsp[(3) - (3)].interm).arraySizes);
    }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 982 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (5)].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (5)].lex).loc, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(1) - (5)].interm.type), (yyvsp[(3) - (5)].interm).arraySizes, (yyvsp[(5) - (5)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[(4) - (5)].lex).loc);
    }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 987 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (4)].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (4)].lex).loc, *(yyvsp[(2) - (4)].lex).string, (yyvsp[(1) - (4)].interm.type), 0, (yyvsp[(4) - (4)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[(3) - (4)].lex).loc);
    }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 996 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[(1) - (1)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (1)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (1)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1007 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier);
        parseContext.globalQualifierTypeCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, (yyvsp[(2) - (2)].interm.type));

        if ((yyvsp[(2) - (2)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(2) - (2)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(2) - (2)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[(2) - (2)].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier))
            (yyvsp[(2) - (2)].interm.type).arraySizes = 0;

        parseContext.checkNoShaderLayouts((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        (yyvsp[(2) - (2)].interm.type).shaderQualifiers.merge((yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(2) - (2)].interm.type).qualifier, (yyvsp[(1) - (2)].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(2) - (2)].interm.type).basicType, (yyvsp[(2) - (2)].interm.type).qualifier);

        (yyval.interm.type) = (yyvsp[(2) - (2)].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1034 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1043 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1050 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1057 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "noperspective");
        parseContext.requireProfile((yyvsp[(1) - (1)].lex).loc, ~EEsProfile, "noperspective");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1064 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1076 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(3) - (4)].interm.type);
    }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1082 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1085 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (3)].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[(3) - (3)].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[(3) - (3)].interm.type).qualifier, false);
    }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1092 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type), *(yyvsp[(1) - (1)].lex).string);
    }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1096 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (3)].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[(1) - (3)].lex).loc, (yyval.interm.type), *(yyvsp[(1) - (3)].lex).string, (yyvsp[(3) - (3)].interm.intermTypedNode));
    }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1100 "glslang.y"
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type), strShared);
    }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1108 "glslang.y"
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1117 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1120 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (2)].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[(2) - (2)].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[(2) - (2)].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[(2) - (2)].interm.type).qualifier, false);
    }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1131 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1134 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1137 "glslang.y"
    {
        parseContext.checkPrecisionQualifier((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1141 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1145 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1149 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1156 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1160 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangVertex, "attribute");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, "attribute");

        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "attribute");

        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1172 "glslang.y"
    {
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, "varying");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, "varying");

        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "varying");

        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).qualifier.storage = EvqVaryingOut;
        else
            (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1186 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1191 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1197 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1203 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1210 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "patch");
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1216 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1221 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1226 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1231 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 310, 0, "shared");
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangCompute, "shared");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1238 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1242 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1246 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1250 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1254 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1258 "glslang.y"
    {
        parseContext.spvRemoved((yyvsp[(1) - (1)].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1264 "glslang.y"
    {
        parseContext.spvRemoved((yyvsp[(1) - (4)].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[(1) - (4)].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[(1) - (4)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1276 "glslang.y"
    {
        // TODO: 4.0 functionality: subroutine type to list
    }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1279 "glslang.y"
    {
    }
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1284 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
    }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1288 "glslang.y"
    {
        parseContext.arrayDimCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(2) - (2)].interm).arraySizes, 0);
        (yyval.interm.type) = (yyvsp[(1) - (2)].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).arraySizes = (yyvsp[(2) - (2)].interm).arraySizes;
    }
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1297 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (2)].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1302 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (3)].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[(2) - (3)].interm.intermTypedNode)->getLoc(), (yyvsp[(2) - (3)].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1310 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (3)].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1314 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (4)].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[(3) - (4)].interm.intermTypedNode)->getLoc(), (yyvsp[(3) - (4)].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1324 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1328 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1332 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1337 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
#endif
    }
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1344 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1348 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1353 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1358 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1363 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1367 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1372 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1377 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1382 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1388 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1394 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1400 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
#endif
    }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1408 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
#endif
    }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1416 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
#endif
    }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1424 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1429 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1434 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1439 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1444 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1449 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1454 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1460 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1466 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1472 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1478 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1484 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1490 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1496 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1502 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1508 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1513 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1518 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1523 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1528 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1533 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1538 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1543 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1548 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1553 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1558 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1563 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1568 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1574 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1580 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1586 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1592 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1598 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1604 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1610 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1616 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1622 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1628 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1634 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1640 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    }
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1648 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    }
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1656 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    }
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1664 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    }
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1672 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
#endif
    }
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1680 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
#endif
    }
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1688 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
#endif
    }
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1696 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    }
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1704 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
#endif
    }
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1712 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
#endif
    }
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1720 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
#endif
    }
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1728 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1736 "glslang.y"
    {
        parseContext.vulkanRemoved((yyvsp[(1) - (1)].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1741 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1746 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1751 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1756 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1761 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1766 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1771 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1776 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1781 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1786 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1791 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 1796 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1801 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1806 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 1811 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 1816 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1821 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 1826 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1831 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1836 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1841 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1846 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1851 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1856 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1861 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1866 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1871 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1876 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1881 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1886 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1891 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1896 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1901 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1906 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1911 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1916 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1921 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1926 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1931 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1936 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1941 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1946 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1951 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1956 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1961 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1966 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1971 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1976 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1981 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1986 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1991 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1996 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 2001 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 2006 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 2011 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 2016 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 2021 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 2026 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 2031 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 2036 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 2041 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 2046 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 2051 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 2056 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 2061 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 2066 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 2071 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 2076 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 2081 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 2086 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 2091 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 2096 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 2101 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 2106 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 2111 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 2116 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 2121 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 2126 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 2131 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
    break;

  case 322:
/* Line 1792 of yacc.c  */
#line 2136 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 2141 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
    break;

  case 324:
/* Line 1792 of yacc.c  */
#line 2146 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 2151 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 2156 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 2161 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 2166 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 2171 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 2176 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 2181 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
    break;

  case 332:
/* Line 1792 of yacc.c  */
#line 2186 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 2191 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 2196 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
    break;

  case 335:
/* Line 1792 of yacc.c  */
#line 2201 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
    break;

  case 336:
/* Line 1792 of yacc.c  */
#line 2206 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 2211 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 2216 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 2221 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
    break;

  case 340:
/* Line 1792 of yacc.c  */
#line 2226 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
    break;

  case 341:
/* Line 1792 of yacc.c  */
#line 2231 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
    break;

  case 342:
/* Line 1792 of yacc.c  */
#line 2236 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 2241 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 2246 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
    break;

  case 345:
/* Line 1792 of yacc.c  */
#line 2251 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 2256 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
    break;

  case 347:
/* Line 1792 of yacc.c  */
#line 2261 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
    break;

  case 348:
/* Line 1792 of yacc.c  */
#line 2266 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
    break;

  case 349:
/* Line 1792 of yacc.c  */
#line 2271 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 2276 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 2281 "glslang.y"
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 2287 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 2293 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 2299 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
    break;

  case 355:
/* Line 1792 of yacc.c  */
#line 2305 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 2311 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
    break;

  case 357:
/* Line 1792 of yacc.c  */
#line 2317 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 2323 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 2328 "glslang.y"
    {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ((yyvsp[(1) - (1)].lex).symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
            (yyval.interm.type).basicType = EbtStruct;
            (yyval.interm.type).userDef = &structure;
        } else
            parseContext.error((yyvsp[(1) - (1)].lex).loc, "expected type name", (yyvsp[(1) - (1)].lex).string->c_str(), "");
    }
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 2344 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 2349 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 2354 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
    break;

  case 363:
/* Line 1792 of yacc.c  */
#line 2362 "glslang.y"
    { parseContext.nestedStructCheck((yyvsp[(1) - (3)].lex).loc); }
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 2362 "glslang.y"
    {
        TType* structure = new TType((yyvsp[(5) - (6)].interm.typeList), *(yyvsp[(2) - (6)].lex).string);
        parseContext.structArrayCheck((yyvsp[(2) - (6)].lex).loc, *structure);
        TVariable* userTypeDef = new TVariable((yyvsp[(2) - (6)].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[(2) - (6)].lex).loc, "redefinition", (yyvsp[(2) - (6)].lex).string->c_str(), "struct");
        (yyval.interm.type).init((yyvsp[(1) - (6)].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
    break;

  case 365:
/* Line 1792 of yacc.c  */
#line 2373 "glslang.y"
    { parseContext.nestedStructCheck((yyvsp[(1) - (2)].lex).loc); }
    break;

  case 366:
/* Line 1792 of yacc.c  */
#line 2373 "glslang.y"
    {
        TType* structure = new TType((yyvsp[(4) - (5)].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[(1) - (5)].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
    break;

  case 367:
/* Line 1792 of yacc.c  */
#line 2383 "glslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (1)].interm.typeList);
    }
    break;

  case 368:
/* Line 1792 of yacc.c  */
#line 2386 "glslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (2)].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[(2) - (2)].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[(2) - (2)].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[(2) - (2)].interm.typeList))[i]);
        }
    }
    break;

  case 369:
/* Line 1792 of yacc.c  */
#line 2399 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[(2) - (3)].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[(1) - (3)].interm.type).loc, (*(yyvsp[(2) - (3)].interm.typeList))[0].type->getFieldName(), (yyvsp[(1) - (3)].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).basicType, (yyvsp[(1) - (3)].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            parseContext.arrayDimCheck((yyvsp[(1) - (3)].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[(1) - (3)].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[(1) - (3)].interm.type));
        }
    }
    break;

  case 370:
/* Line 1792 of yacc.c  */
#line 2417 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).qualifier);
        if ((yyvsp[(2) - (4)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(2) - (4)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(2) - (4)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[(2) - (4)].interm.type).loc, *(yyvsp[(2) - (4)].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[(3) - (4)].interm.typeList);

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).shaderQualifiers);
        parseContext.voidErrorCheck((yyvsp[(2) - (4)].interm.type).loc, (*(yyvsp[(3) - (4)].interm.typeList))[0].type->getFieldName(), (yyvsp[(2) - (4)].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[(2) - (4)].interm.type).loc, (yyvsp[(2) - (4)].interm.type).qualifier, (yyvsp[(1) - (4)].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[(2) - (4)].interm.type).loc, (yyvsp[(2) - (4)].interm.type).basicType, (yyvsp[(2) - (4)].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            parseContext.arrayDimCheck((yyvsp[(1) - (4)].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[(2) - (4)].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[(2) - (4)].interm.type));
        }
    }
    break;

  case 371:
/* Line 1792 of yacc.c  */
#line 2441 "glslang.y"
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[(1) - (1)].interm.typeLine));
    }
    break;

  case 372:
/* Line 1792 of yacc.c  */
#line 2445 "glslang.y"
    {
        (yyval.interm.typeList)->push_back((yyvsp[(3) - (3)].interm.typeLine));
    }
    break;

  case 373:
/* Line 1792 of yacc.c  */
#line 2451 "glslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (1)].lex).string);
    }
    break;

  case 374:
/* Line 1792 of yacc.c  */
#line 2456 "glslang.y"
    {
        parseContext.arrayDimCheck((yyvsp[(1) - (2)].lex).loc, (yyvsp[(2) - (2)].interm).arraySizes, 0);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[(1) - (2)].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (2)].lex).string);
        (yyval.interm.typeLine).type->newArraySizes(*(yyvsp[(2) - (2)].interm).arraySizes);
    }
    break;

  case 375:
/* Line 1792 of yacc.c  */
#line 2467 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 376:
/* Line 1792 of yacc.c  */
#line 2470 "glslang.y"
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[(1) - (3)].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[(1) - (3)].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermTypedNode);
    }
    break;

  case 377:
/* Line 1792 of yacc.c  */
#line 2476 "glslang.y"
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[(1) - (4)].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[(1) - (4)].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (4)].interm.intermTypedNode);
    }
    break;

  case 378:
/* Line 1792 of yacc.c  */
#line 2485 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[(1) - (1)].interm.intermTypedNode), (yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc());
    }
    break;

  case 379:
/* Line 1792 of yacc.c  */
#line 2488 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
    }
    break;

  case 380:
/* Line 1792 of yacc.c  */
#line 2494 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 381:
/* Line 1792 of yacc.c  */
#line 2498 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 382:
/* Line 1792 of yacc.c  */
#line 2499 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 383:
/* Line 1792 of yacc.c  */
#line 2505 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 384:
/* Line 1792 of yacc.c  */
#line 2506 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 385:
/* Line 1792 of yacc.c  */
#line 2507 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 386:
/* Line 1792 of yacc.c  */
#line 2508 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 387:
/* Line 1792 of yacc.c  */
#line 2509 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 388:
/* Line 1792 of yacc.c  */
#line 2510 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 389:
/* Line 1792 of yacc.c  */
#line 2511 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 390:
/* Line 1792 of yacc.c  */
#line 2515 "glslang.y"
    { (yyval.interm.intermNode) = 0; }
    break;

  case 391:
/* Line 1792 of yacc.c  */
#line 2516 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
    break;

  case 392:
/* Line 1792 of yacc.c  */
#line 2520 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
    break;

  case 393:
/* Line 1792 of yacc.c  */
#line 2524 "glslang.y"
    {
        if ((yyvsp[(3) - (5)].interm.intermNode) && (yyvsp[(3) - (5)].interm.intermNode)->getAsAggregate())
            (yyvsp[(3) - (5)].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(3) - (5)].interm.intermNode);
    }
    break;

  case 394:
/* Line 1792 of yacc.c  */
#line 2532 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 395:
/* Line 1792 of yacc.c  */
#line 2533 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); }
    break;

  case 396:
/* Line 1792 of yacc.c  */
#line 2537 "glslang.y"
    {
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 397:
/* Line 1792 of yacc.c  */
#line 2540 "glslang.y"
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[(2) - (2)].interm.intermNode);
    }
    break;

  case 398:
/* Line 1792 of yacc.c  */
#line 2544 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 399:
/* Line 1792 of yacc.c  */
#line 2549 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[(2) - (2)].interm.intermNode);
    }
    break;

  case 400:
/* Line 1792 of yacc.c  */
#line 2558 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 401:
/* Line 1792 of yacc.c  */
#line 2561 "glslang.y"
    {
        if ((yyvsp[(2) - (3)].interm.intermNode) && (yyvsp[(2) - (3)].interm.intermNode)->getAsAggregate())
            (yyvsp[(2) - (3)].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(2) - (3)].interm.intermNode);
    }
    break;

  case 402:
/* Line 1792 of yacc.c  */
#line 2569 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[(1) - (1)].interm.intermNode));
        if ((yyvsp[(1) - (1)].interm.intermNode) && (yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode() && ((yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[(1) - (1)].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
    break;

  case 403:
/* Line 1792 of yacc.c  */
#line 2577 "glslang.y"
    {
        if ((yyvsp[(2) - (2)].interm.intermNode) && (yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode() && ((yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[(1) - (2)].interm.intermNode) ? (yyvsp[(1) - (2)].interm.intermNode)->getAsAggregate() : 0, (yyvsp[(2) - (2)].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermNode), (yyvsp[(2) - (2)].interm.intermNode));
    }
    break;

  case 404:
/* Line 1792 of yacc.c  */
#line 2588 "glslang.y"
    { (yyval.interm.intermNode) = 0; }
    break;

  case 405:
/* Line 1792 of yacc.c  */
#line 2589 "glslang.y"
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[(1) - (2)].interm.intermTypedNode)); }
    break;

  case 406:
/* Line 1792 of yacc.c  */
#line 2593 "glslang.y"
    {
        parseContext.boolCheck((yyvsp[(1) - (5)].lex).loc, (yyvsp[(3) - (5)].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[(3) - (5)].interm.intermTypedNode), (yyvsp[(5) - (5)].interm.nodePair), (yyvsp[(1) - (5)].lex).loc);
    }
    break;

  case 407:
/* Line 1792 of yacc.c  */
#line 2600 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermNode);
    }
    break;

  case 408:
/* Line 1792 of yacc.c  */
#line 2604 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (1)].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
    break;

  case 409:
/* Line 1792 of yacc.c  */
#line 2612 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), (yyvsp[(1) - (1)].interm.intermTypedNode));
    }
    break;

  case 410:
/* Line 1792 of yacc.c  */
#line 2616 "glslang.y"
    {
        parseContext.boolCheck((yyvsp[(2) - (4)].lex).loc, (yyvsp[(1) - (4)].interm.type));

        TType type((yyvsp[(1) - (4)].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (4)].lex).loc, *(yyvsp[(2) - (4)].lex).string, (yyvsp[(1) - (4)].interm.type), 0, (yyvsp[(4) - (4)].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    }
    break;

  case 411:
/* Line 1792 of yacc.c  */
#line 2629 "glslang.y"
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
    break;

  case 412:
/* Line 1792 of yacc.c  */
#line 2637 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[(1) - (8)].lex).loc, (yyvsp[(3) - (8)].interm.intermTypedNode), (yyvsp[(7) - (8)].interm.intermNode) ? (yyvsp[(7) - (8)].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    break;

  case 413:
/* Line 1792 of yacc.c  */
#line 2649 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
    }
    break;

  case 414:
/* Line 1792 of yacc.c  */
#line 2652 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    }
    break;

  case 415:
/* Line 1792 of yacc.c  */
#line 2658 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[(1) - (3)].lex).loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[(1) - (3)].lex).loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck((yyvsp[(2) - (3)].interm.intermTypedNode), "case");
            parseContext.integerCheck((yyvsp[(2) - (3)].interm.intermTypedNode), "case");
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpCase, (yyvsp[(2) - (3)].interm.intermTypedNode), (yyvsp[(1) - (3)].lex).loc);
        }
    }
    break;

  case 416:
/* Line 1792 of yacc.c  */
#line 2670 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[(1) - (2)].lex).loc);
    }
    break;

  case 417:
/* Line 1792 of yacc.c  */
#line 2682 "glslang.y"
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 418:
/* Line 1792 of yacc.c  */
#line 2690 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(6) - (6)].interm.intermNode), (yyvsp[(4) - (6)].interm.intermTypedNode), 0, true, (yyvsp[(1) - (6)].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    break;

  case 419:
/* Line 1792 of yacc.c  */
#line 2697 "glslang.y"
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 420:
/* Line 1792 of yacc.c  */
#line 2702 "glslang.y"
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[(1) - (8)].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[(8) - (8)].lex).loc, (yyvsp[(6) - (8)].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(3) - (8)].interm.intermNode), (yyvsp[(6) - (8)].interm.intermTypedNode), 0, false, (yyvsp[(4) - (8)].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    break;

  case 421:
/* Line 1792 of yacc.c  */
#line 2713 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
    break;

  case 422:
/* Line 1792 of yacc.c  */
#line 2719 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[(4) - (7)].interm.intermNode), (yyvsp[(2) - (7)].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[(7) - (7)].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node2), true, (yyvsp[(1) - (7)].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[(1) - (7)].lex).loc, (yyvsp[(4) - (7)].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[(1) - (7)].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
    break;

  case 423:
/* Line 1792 of yacc.c  */
#line 2734 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    }
    break;

  case 424:
/* Line 1792 of yacc.c  */
#line 2737 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    }
    break;

  case 425:
/* Line 1792 of yacc.c  */
#line 2743 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    }
    break;

  case 426:
/* Line 1792 of yacc.c  */
#line 2746 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = 0;
    }
    break;

  case 427:
/* Line 1792 of yacc.c  */
#line 2752 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (2)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    }
    break;

  case 428:
/* Line 1792 of yacc.c  */
#line 2756 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermTypedNode);
    }
    break;

  case 429:
/* Line 1792 of yacc.c  */
#line 2763 "glslang.y"
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[(1) - (2)].lex).loc);
    }
    break;

  case 430:
/* Line 1792 of yacc.c  */
#line 2768 "glslang.y"
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[(1) - (2)].lex).loc);
    }
    break;

  case 431:
/* Line 1792 of yacc.c  */
#line 2773 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[(1) - (2)].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postMainReturn = true;
    }
    break;

  case 432:
/* Line 1792 of yacc.c  */
#line 2780 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[(1) - (3)].lex).loc, (yyvsp[(2) - (3)].interm.intermTypedNode));
    }
    break;

  case 433:
/* Line 1792 of yacc.c  */
#line 2783 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (2)].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[(1) - (2)].lex).loc);
    }
    break;

  case 434:
/* Line 1792 of yacc.c  */
#line 2792 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
    break;

  case 435:
/* Line 1792 of yacc.c  */
#line 2796 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermNode), (yyvsp[(2) - (2)].interm.intermNode));
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
    break;

  case 436:
/* Line 1792 of yacc.c  */
#line 2803 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    }
    break;

  case 437:
/* Line 1792 of yacc.c  */
#line 2806 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    }
    break;

  case 438:
/* Line 1792 of yacc.c  */
#line 2812 "glslang.y"
    {
        (yyvsp[(1) - (1)].interm).function = parseContext.handleFunctionDeclarator((yyvsp[(1) - (1)].interm).loc, *(yyvsp[(1) - (1)].interm).function, false /* not prototype */);
        (yyvsp[(1) - (1)].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[(1) - (1)].interm).loc, *(yyvsp[(1) - (1)].interm).function);
    }
    break;

  case 439:
/* Line 1792 of yacc.c  */
#line 2816 "glslang.y"
    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[(1) - (3)].interm).loc, "function does not return a value:", "", (yyvsp[(1) - (3)].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermNode, (yyvsp[(3) - (3)].interm.intermNode));
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[(1) - (3)].interm).function->getType(), (yyvsp[(1) - (3)].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[(1) - (3)].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->addToPragmaTable(parseContext.contextPragma.pragmaTable);
    }
    break;


/* Line 1792 of yacc.c  */
#line 8088 "glslang_tab.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 2833 "glslang.y"


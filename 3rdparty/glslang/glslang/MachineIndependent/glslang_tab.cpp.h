/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
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


/* Line 2058 of yacc.c  */
#line 379 "glslang_tab.cpp.h"
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

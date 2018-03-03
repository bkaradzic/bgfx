/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 69 "glslang.y" /* yacc.c:1909  */

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

#line 429 "glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_GLSLANG_TAB_CPP_H_INCLUDED  */

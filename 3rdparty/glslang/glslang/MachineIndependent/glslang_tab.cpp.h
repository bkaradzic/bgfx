/* A Bison parser, made by GNU Bison 3.0.  */

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
    COHERENT = 337,
    VOLATILE = 338,
    RESTRICT = 339,
    READONLY = 340,
    WRITEONLY = 341,
    DVEC2 = 342,
    DVEC3 = 343,
    DVEC4 = 344,
    DMAT2 = 345,
    DMAT3 = 346,
    DMAT4 = 347,
    F16VEC2 = 348,
    F16VEC3 = 349,
    F16VEC4 = 350,
    F16MAT2 = 351,
    F16MAT3 = 352,
    F16MAT4 = 353,
    F32VEC2 = 354,
    F32VEC3 = 355,
    F32VEC4 = 356,
    F32MAT2 = 357,
    F32MAT3 = 358,
    F32MAT4 = 359,
    F64VEC2 = 360,
    F64VEC3 = 361,
    F64VEC4 = 362,
    F64MAT2 = 363,
    F64MAT3 = 364,
    F64MAT4 = 365,
    NOPERSPECTIVE = 366,
    FLAT = 367,
    SMOOTH = 368,
    LAYOUT = 369,
    __EXPLICITINTERPAMD = 370,
    MAT2X2 = 371,
    MAT2X3 = 372,
    MAT2X4 = 373,
    MAT3X2 = 374,
    MAT3X3 = 375,
    MAT3X4 = 376,
    MAT4X2 = 377,
    MAT4X3 = 378,
    MAT4X4 = 379,
    DMAT2X2 = 380,
    DMAT2X3 = 381,
    DMAT2X4 = 382,
    DMAT3X2 = 383,
    DMAT3X3 = 384,
    DMAT3X4 = 385,
    DMAT4X2 = 386,
    DMAT4X3 = 387,
    DMAT4X4 = 388,
    F16MAT2X2 = 389,
    F16MAT2X3 = 390,
    F16MAT2X4 = 391,
    F16MAT3X2 = 392,
    F16MAT3X3 = 393,
    F16MAT3X4 = 394,
    F16MAT4X2 = 395,
    F16MAT4X3 = 396,
    F16MAT4X4 = 397,
    F32MAT2X2 = 398,
    F32MAT2X3 = 399,
    F32MAT2X4 = 400,
    F32MAT3X2 = 401,
    F32MAT3X3 = 402,
    F32MAT3X4 = 403,
    F32MAT4X2 = 404,
    F32MAT4X3 = 405,
    F32MAT4X4 = 406,
    F64MAT2X2 = 407,
    F64MAT2X3 = 408,
    F64MAT2X4 = 409,
    F64MAT3X2 = 410,
    F64MAT3X3 = 411,
    F64MAT3X4 = 412,
    F64MAT4X2 = 413,
    F64MAT4X3 = 414,
    F64MAT4X4 = 415,
    ATOMIC_UINT = 416,
    SAMPLER1D = 417,
    SAMPLER2D = 418,
    SAMPLER3D = 419,
    SAMPLERCUBE = 420,
    SAMPLER1DSHADOW = 421,
    SAMPLER2DSHADOW = 422,
    SAMPLERCUBESHADOW = 423,
    SAMPLER1DARRAY = 424,
    SAMPLER2DARRAY = 425,
    SAMPLER1DARRAYSHADOW = 426,
    SAMPLER2DARRAYSHADOW = 427,
    ISAMPLER1D = 428,
    ISAMPLER2D = 429,
    ISAMPLER3D = 430,
    ISAMPLERCUBE = 431,
    ISAMPLER1DARRAY = 432,
    ISAMPLER2DARRAY = 433,
    USAMPLER1D = 434,
    USAMPLER2D = 435,
    USAMPLER3D = 436,
    USAMPLERCUBE = 437,
    USAMPLER1DARRAY = 438,
    USAMPLER2DARRAY = 439,
    SAMPLER2DRECT = 440,
    SAMPLER2DRECTSHADOW = 441,
    ISAMPLER2DRECT = 442,
    USAMPLER2DRECT = 443,
    SAMPLERBUFFER = 444,
    ISAMPLERBUFFER = 445,
    USAMPLERBUFFER = 446,
    SAMPLERCUBEARRAY = 447,
    SAMPLERCUBEARRAYSHADOW = 448,
    ISAMPLERCUBEARRAY = 449,
    USAMPLERCUBEARRAY = 450,
    SAMPLER2DMS = 451,
    ISAMPLER2DMS = 452,
    USAMPLER2DMS = 453,
    SAMPLER2DMSARRAY = 454,
    ISAMPLER2DMSARRAY = 455,
    USAMPLER2DMSARRAY = 456,
    SAMPLEREXTERNALOES = 457,
    F16SAMPLER1D = 458,
    F16SAMPLER2D = 459,
    F16SAMPLER3D = 460,
    F16SAMPLER2DRECT = 461,
    F16SAMPLERCUBE = 462,
    F16SAMPLER1DARRAY = 463,
    F16SAMPLER2DARRAY = 464,
    F16SAMPLERCUBEARRAY = 465,
    F16SAMPLERBUFFER = 466,
    F16SAMPLER2DMS = 467,
    F16SAMPLER2DMSARRAY = 468,
    F16SAMPLER1DSHADOW = 469,
    F16SAMPLER2DSHADOW = 470,
    F16SAMPLER1DARRAYSHADOW = 471,
    F16SAMPLER2DARRAYSHADOW = 472,
    F16SAMPLER2DRECTSHADOW = 473,
    F16SAMPLERCUBESHADOW = 474,
    F16SAMPLERCUBEARRAYSHADOW = 475,
    SAMPLER = 476,
    SAMPLERSHADOW = 477,
    TEXTURE1D = 478,
    TEXTURE2D = 479,
    TEXTURE3D = 480,
    TEXTURECUBE = 481,
    TEXTURE1DARRAY = 482,
    TEXTURE2DARRAY = 483,
    ITEXTURE1D = 484,
    ITEXTURE2D = 485,
    ITEXTURE3D = 486,
    ITEXTURECUBE = 487,
    ITEXTURE1DARRAY = 488,
    ITEXTURE2DARRAY = 489,
    UTEXTURE1D = 490,
    UTEXTURE2D = 491,
    UTEXTURE3D = 492,
    UTEXTURECUBE = 493,
    UTEXTURE1DARRAY = 494,
    UTEXTURE2DARRAY = 495,
    TEXTURE2DRECT = 496,
    ITEXTURE2DRECT = 497,
    UTEXTURE2DRECT = 498,
    TEXTUREBUFFER = 499,
    ITEXTUREBUFFER = 500,
    UTEXTUREBUFFER = 501,
    TEXTURECUBEARRAY = 502,
    ITEXTURECUBEARRAY = 503,
    UTEXTURECUBEARRAY = 504,
    TEXTURE2DMS = 505,
    ITEXTURE2DMS = 506,
    UTEXTURE2DMS = 507,
    TEXTURE2DMSARRAY = 508,
    ITEXTURE2DMSARRAY = 509,
    UTEXTURE2DMSARRAY = 510,
    F16TEXTURE1D = 511,
    F16TEXTURE2D = 512,
    F16TEXTURE3D = 513,
    F16TEXTURE2DRECT = 514,
    F16TEXTURECUBE = 515,
    F16TEXTURE1DARRAY = 516,
    F16TEXTURE2DARRAY = 517,
    F16TEXTURECUBEARRAY = 518,
    F16TEXTUREBUFFER = 519,
    F16TEXTURE2DMS = 520,
    F16TEXTURE2DMSARRAY = 521,
    SUBPASSINPUT = 522,
    SUBPASSINPUTMS = 523,
    ISUBPASSINPUT = 524,
    ISUBPASSINPUTMS = 525,
    USUBPASSINPUT = 526,
    USUBPASSINPUTMS = 527,
    F16SUBPASSINPUT = 528,
    F16SUBPASSINPUTMS = 529,
    IMAGE1D = 530,
    IIMAGE1D = 531,
    UIMAGE1D = 532,
    IMAGE2D = 533,
    IIMAGE2D = 534,
    UIMAGE2D = 535,
    IMAGE3D = 536,
    IIMAGE3D = 537,
    UIMAGE3D = 538,
    IMAGE2DRECT = 539,
    IIMAGE2DRECT = 540,
    UIMAGE2DRECT = 541,
    IMAGECUBE = 542,
    IIMAGECUBE = 543,
    UIMAGECUBE = 544,
    IMAGEBUFFER = 545,
    IIMAGEBUFFER = 546,
    UIMAGEBUFFER = 547,
    IMAGE1DARRAY = 548,
    IIMAGE1DARRAY = 549,
    UIMAGE1DARRAY = 550,
    IMAGE2DARRAY = 551,
    IIMAGE2DARRAY = 552,
    UIMAGE2DARRAY = 553,
    IMAGECUBEARRAY = 554,
    IIMAGECUBEARRAY = 555,
    UIMAGECUBEARRAY = 556,
    IMAGE2DMS = 557,
    IIMAGE2DMS = 558,
    UIMAGE2DMS = 559,
    IMAGE2DMSARRAY = 560,
    IIMAGE2DMSARRAY = 561,
    UIMAGE2DMSARRAY = 562,
    F16IMAGE1D = 563,
    F16IMAGE2D = 564,
    F16IMAGE3D = 565,
    F16IMAGE2DRECT = 566,
    F16IMAGECUBE = 567,
    F16IMAGE1DARRAY = 568,
    F16IMAGE2DARRAY = 569,
    F16IMAGECUBEARRAY = 570,
    F16IMAGEBUFFER = 571,
    F16IMAGE2DMS = 572,
    F16IMAGE2DMSARRAY = 573,
    STRUCT = 574,
    VOID = 575,
    WHILE = 576,
    IDENTIFIER = 577,
    TYPE_NAME = 578,
    FLOATCONSTANT = 579,
    DOUBLECONSTANT = 580,
    INT16CONSTANT = 581,
    UINT16CONSTANT = 582,
    INT32CONSTANT = 583,
    UINT32CONSTANT = 584,
    INTCONSTANT = 585,
    UINTCONSTANT = 586,
    INT64CONSTANT = 587,
    UINT64CONSTANT = 588,
    BOOLCONSTANT = 589,
    FLOAT16CONSTANT = 590,
    LEFT_OP = 591,
    RIGHT_OP = 592,
    INC_OP = 593,
    DEC_OP = 594,
    LE_OP = 595,
    GE_OP = 596,
    EQ_OP = 597,
    NE_OP = 598,
    AND_OP = 599,
    OR_OP = 600,
    XOR_OP = 601,
    MUL_ASSIGN = 602,
    DIV_ASSIGN = 603,
    ADD_ASSIGN = 604,
    MOD_ASSIGN = 605,
    LEFT_ASSIGN = 606,
    RIGHT_ASSIGN = 607,
    AND_ASSIGN = 608,
    XOR_ASSIGN = 609,
    OR_ASSIGN = 610,
    SUB_ASSIGN = 611,
    LEFT_PAREN = 612,
    RIGHT_PAREN = 613,
    LEFT_BRACKET = 614,
    RIGHT_BRACKET = 615,
    LEFT_BRACE = 616,
    RIGHT_BRACE = 617,
    DOT = 618,
    COMMA = 619,
    COLON = 620,
    EQUAL = 621,
    SEMICOLON = 622,
    BANG = 623,
    DASH = 624,
    TILDE = 625,
    PLUS = 626,
    STAR = 627,
    SLASH = 628,
    PERCENT = 629,
    LEFT_ANGLE = 630,
    RIGHT_ANGLE = 631,
    VERTICAL_BAR = 632,
    CARET = 633,
    AMPERSAND = 634,
    QUESTION = 635,
    INVARIANT = 636,
    PRECISE = 637,
    HIGH_PRECISION = 638,
    MEDIUM_PRECISION = 639,
    LOW_PRECISION = 640,
    PRECISION = 641,
    PACKED = 642,
    RESOURCE = 643,
    SUPERP = 644
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 70 "MachineIndependent/glslang.y" /* yacc.c:1909  */

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

#line 479 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

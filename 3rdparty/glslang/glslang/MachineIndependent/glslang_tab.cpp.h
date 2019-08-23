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
    CONST = 258,
    BOOL = 259,
    INT = 260,
    UINT = 261,
    FLOAT = 262,
    BVEC2 = 263,
    BVEC3 = 264,
    BVEC4 = 265,
    IVEC2 = 266,
    IVEC3 = 267,
    IVEC4 = 268,
    UVEC2 = 269,
    UVEC3 = 270,
    UVEC4 = 271,
    VEC2 = 272,
    VEC3 = 273,
    VEC4 = 274,
    MAT2 = 275,
    MAT3 = 276,
    MAT4 = 277,
    MAT2X2 = 278,
    MAT2X3 = 279,
    MAT2X4 = 280,
    MAT3X2 = 281,
    MAT3X3 = 282,
    MAT3X4 = 283,
    MAT4X2 = 284,
    MAT4X3 = 285,
    MAT4X4 = 286,
    SAMPLER2D = 287,
    SAMPLER3D = 288,
    SAMPLERCUBE = 289,
    SAMPLER2DSHADOW = 290,
    SAMPLERCUBESHADOW = 291,
    SAMPLER2DARRAY = 292,
    SAMPLER2DARRAYSHADOW = 293,
    ISAMPLER2D = 294,
    ISAMPLER3D = 295,
    ISAMPLERCUBE = 296,
    ISAMPLER2DARRAY = 297,
    USAMPLER2D = 298,
    USAMPLER3D = 299,
    USAMPLERCUBE = 300,
    USAMPLER2DARRAY = 301,
    SAMPLERCUBEARRAY = 302,
    SAMPLERCUBEARRAYSHADOW = 303,
    ISAMPLERCUBEARRAY = 304,
    USAMPLERCUBEARRAY = 305,
    ATTRIBUTE = 306,
    VARYING = 307,
    FLOAT16_T = 308,
    FLOAT32_T = 309,
    DOUBLE = 310,
    FLOAT64_T = 311,
    INT64_T = 312,
    UINT64_T = 313,
    INT32_T = 314,
    UINT32_T = 315,
    INT16_T = 316,
    UINT16_T = 317,
    INT8_T = 318,
    UINT8_T = 319,
    I64VEC2 = 320,
    I64VEC3 = 321,
    I64VEC4 = 322,
    U64VEC2 = 323,
    U64VEC3 = 324,
    U64VEC4 = 325,
    I32VEC2 = 326,
    I32VEC3 = 327,
    I32VEC4 = 328,
    U32VEC2 = 329,
    U32VEC3 = 330,
    U32VEC4 = 331,
    I16VEC2 = 332,
    I16VEC3 = 333,
    I16VEC4 = 334,
    U16VEC2 = 335,
    U16VEC3 = 336,
    U16VEC4 = 337,
    I8VEC2 = 338,
    I8VEC3 = 339,
    I8VEC4 = 340,
    U8VEC2 = 341,
    U8VEC3 = 342,
    U8VEC4 = 343,
    DVEC2 = 344,
    DVEC3 = 345,
    DVEC4 = 346,
    DMAT2 = 347,
    DMAT3 = 348,
    DMAT4 = 349,
    F16VEC2 = 350,
    F16VEC3 = 351,
    F16VEC4 = 352,
    F16MAT2 = 353,
    F16MAT3 = 354,
    F16MAT4 = 355,
    F32VEC2 = 356,
    F32VEC3 = 357,
    F32VEC4 = 358,
    F32MAT2 = 359,
    F32MAT3 = 360,
    F32MAT4 = 361,
    F64VEC2 = 362,
    F64VEC3 = 363,
    F64VEC4 = 364,
    F64MAT2 = 365,
    F64MAT3 = 366,
    F64MAT4 = 367,
    DMAT2X2 = 368,
    DMAT2X3 = 369,
    DMAT2X4 = 370,
    DMAT3X2 = 371,
    DMAT3X3 = 372,
    DMAT3X4 = 373,
    DMAT4X2 = 374,
    DMAT4X3 = 375,
    DMAT4X4 = 376,
    F16MAT2X2 = 377,
    F16MAT2X3 = 378,
    F16MAT2X4 = 379,
    F16MAT3X2 = 380,
    F16MAT3X3 = 381,
    F16MAT3X4 = 382,
    F16MAT4X2 = 383,
    F16MAT4X3 = 384,
    F16MAT4X4 = 385,
    F32MAT2X2 = 386,
    F32MAT2X3 = 387,
    F32MAT2X4 = 388,
    F32MAT3X2 = 389,
    F32MAT3X3 = 390,
    F32MAT3X4 = 391,
    F32MAT4X2 = 392,
    F32MAT4X3 = 393,
    F32MAT4X4 = 394,
    F64MAT2X2 = 395,
    F64MAT2X3 = 396,
    F64MAT2X4 = 397,
    F64MAT3X2 = 398,
    F64MAT3X3 = 399,
    F64MAT3X4 = 400,
    F64MAT4X2 = 401,
    F64MAT4X3 = 402,
    F64MAT4X4 = 403,
    ATOMIC_UINT = 404,
    ACCSTRUCTNV = 405,
    FCOOPMATNV = 406,
    SAMPLER1D = 407,
    SAMPLER1DARRAY = 408,
    SAMPLER1DARRAYSHADOW = 409,
    ISAMPLER1D = 410,
    SAMPLER1DSHADOW = 411,
    SAMPLER2DRECT = 412,
    SAMPLER2DRECTSHADOW = 413,
    ISAMPLER2DRECT = 414,
    USAMPLER2DRECT = 415,
    SAMPLERBUFFER = 416,
    ISAMPLERBUFFER = 417,
    USAMPLERBUFFER = 418,
    SAMPLER2DMS = 419,
    ISAMPLER2DMS = 420,
    USAMPLER2DMS = 421,
    SAMPLER2DMSARRAY = 422,
    ISAMPLER2DMSARRAY = 423,
    USAMPLER2DMSARRAY = 424,
    SAMPLEREXTERNALOES = 425,
    SAMPLEREXTERNAL2DY2YEXT = 426,
    ISAMPLER1DARRAY = 427,
    USAMPLER1D = 428,
    USAMPLER1DARRAY = 429,
    F16SAMPLER1D = 430,
    F16SAMPLER2D = 431,
    F16SAMPLER3D = 432,
    F16SAMPLER2DRECT = 433,
    F16SAMPLERCUBE = 434,
    F16SAMPLER1DARRAY = 435,
    F16SAMPLER2DARRAY = 436,
    F16SAMPLERCUBEARRAY = 437,
    F16SAMPLERBUFFER = 438,
    F16SAMPLER2DMS = 439,
    F16SAMPLER2DMSARRAY = 440,
    F16SAMPLER1DSHADOW = 441,
    F16SAMPLER2DSHADOW = 442,
    F16SAMPLER1DARRAYSHADOW = 443,
    F16SAMPLER2DARRAYSHADOW = 444,
    F16SAMPLER2DRECTSHADOW = 445,
    F16SAMPLERCUBESHADOW = 446,
    F16SAMPLERCUBEARRAYSHADOW = 447,
    IMAGE1D = 448,
    IIMAGE1D = 449,
    UIMAGE1D = 450,
    IMAGE2D = 451,
    IIMAGE2D = 452,
    UIMAGE2D = 453,
    IMAGE3D = 454,
    IIMAGE3D = 455,
    UIMAGE3D = 456,
    IMAGE2DRECT = 457,
    IIMAGE2DRECT = 458,
    UIMAGE2DRECT = 459,
    IMAGECUBE = 460,
    IIMAGECUBE = 461,
    UIMAGECUBE = 462,
    IMAGEBUFFER = 463,
    IIMAGEBUFFER = 464,
    UIMAGEBUFFER = 465,
    IMAGE1DARRAY = 466,
    IIMAGE1DARRAY = 467,
    UIMAGE1DARRAY = 468,
    IMAGE2DARRAY = 469,
    IIMAGE2DARRAY = 470,
    UIMAGE2DARRAY = 471,
    IMAGECUBEARRAY = 472,
    IIMAGECUBEARRAY = 473,
    UIMAGECUBEARRAY = 474,
    IMAGE2DMS = 475,
    IIMAGE2DMS = 476,
    UIMAGE2DMS = 477,
    IMAGE2DMSARRAY = 478,
    IIMAGE2DMSARRAY = 479,
    UIMAGE2DMSARRAY = 480,
    F16IMAGE1D = 481,
    F16IMAGE2D = 482,
    F16IMAGE3D = 483,
    F16IMAGE2DRECT = 484,
    F16IMAGECUBE = 485,
    F16IMAGE1DARRAY = 486,
    F16IMAGE2DARRAY = 487,
    F16IMAGECUBEARRAY = 488,
    F16IMAGEBUFFER = 489,
    F16IMAGE2DMS = 490,
    F16IMAGE2DMSARRAY = 491,
    SAMPLER = 492,
    SAMPLERSHADOW = 493,
    TEXTURE1D = 494,
    TEXTURE2D = 495,
    TEXTURE3D = 496,
    TEXTURECUBE = 497,
    TEXTURE1DARRAY = 498,
    TEXTURE2DARRAY = 499,
    ITEXTURE1D = 500,
    ITEXTURE2D = 501,
    ITEXTURE3D = 502,
    ITEXTURECUBE = 503,
    ITEXTURE1DARRAY = 504,
    ITEXTURE2DARRAY = 505,
    UTEXTURE1D = 506,
    UTEXTURE2D = 507,
    UTEXTURE3D = 508,
    UTEXTURECUBE = 509,
    UTEXTURE1DARRAY = 510,
    UTEXTURE2DARRAY = 511,
    TEXTURE2DRECT = 512,
    ITEXTURE2DRECT = 513,
    UTEXTURE2DRECT = 514,
    TEXTUREBUFFER = 515,
    ITEXTUREBUFFER = 516,
    UTEXTUREBUFFER = 517,
    TEXTURECUBEARRAY = 518,
    ITEXTURECUBEARRAY = 519,
    UTEXTURECUBEARRAY = 520,
    TEXTURE2DMS = 521,
    ITEXTURE2DMS = 522,
    UTEXTURE2DMS = 523,
    TEXTURE2DMSARRAY = 524,
    ITEXTURE2DMSARRAY = 525,
    UTEXTURE2DMSARRAY = 526,
    F16TEXTURE1D = 527,
    F16TEXTURE2D = 528,
    F16TEXTURE3D = 529,
    F16TEXTURE2DRECT = 530,
    F16TEXTURECUBE = 531,
    F16TEXTURE1DARRAY = 532,
    F16TEXTURE2DARRAY = 533,
    F16TEXTURECUBEARRAY = 534,
    F16TEXTUREBUFFER = 535,
    F16TEXTURE2DMS = 536,
    F16TEXTURE2DMSARRAY = 537,
    SUBPASSINPUT = 538,
    SUBPASSINPUTMS = 539,
    ISUBPASSINPUT = 540,
    ISUBPASSINPUTMS = 541,
    USUBPASSINPUT = 542,
    USUBPASSINPUTMS = 543,
    F16SUBPASSINPUT = 544,
    F16SUBPASSINPUTMS = 545,
    LEFT_OP = 546,
    RIGHT_OP = 547,
    INC_OP = 548,
    DEC_OP = 549,
    LE_OP = 550,
    GE_OP = 551,
    EQ_OP = 552,
    NE_OP = 553,
    AND_OP = 554,
    OR_OP = 555,
    XOR_OP = 556,
    MUL_ASSIGN = 557,
    DIV_ASSIGN = 558,
    ADD_ASSIGN = 559,
    MOD_ASSIGN = 560,
    LEFT_ASSIGN = 561,
    RIGHT_ASSIGN = 562,
    AND_ASSIGN = 563,
    XOR_ASSIGN = 564,
    OR_ASSIGN = 565,
    SUB_ASSIGN = 566,
    LEFT_PAREN = 567,
    RIGHT_PAREN = 568,
    LEFT_BRACKET = 569,
    RIGHT_BRACKET = 570,
    LEFT_BRACE = 571,
    RIGHT_BRACE = 572,
    DOT = 573,
    COMMA = 574,
    COLON = 575,
    EQUAL = 576,
    SEMICOLON = 577,
    BANG = 578,
    DASH = 579,
    TILDE = 580,
    PLUS = 581,
    STAR = 582,
    SLASH = 583,
    PERCENT = 584,
    LEFT_ANGLE = 585,
    RIGHT_ANGLE = 586,
    VERTICAL_BAR = 587,
    CARET = 588,
    AMPERSAND = 589,
    QUESTION = 590,
    INVARIANT = 591,
    HIGH_PRECISION = 592,
    MEDIUM_PRECISION = 593,
    LOW_PRECISION = 594,
    PRECISION = 595,
    PACKED = 596,
    RESOURCE = 597,
    SUPERP = 598,
    FLOATCONSTANT = 599,
    INTCONSTANT = 600,
    UINTCONSTANT = 601,
    BOOLCONSTANT = 602,
    IDENTIFIER = 603,
    TYPE_NAME = 604,
    CENTROID = 605,
    IN = 606,
    OUT = 607,
    INOUT = 608,
    STRUCT = 609,
    VOID = 610,
    WHILE = 611,
    BREAK = 612,
    CONTINUE = 613,
    DO = 614,
    ELSE = 615,
    FOR = 616,
    IF = 617,
    DISCARD = 618,
    RETURN = 619,
    SWITCH = 620,
    CASE = 621,
    DEFAULT = 622,
    UNIFORM = 623,
    SHARED = 624,
    FLAT = 625,
    SMOOTH = 626,
    LAYOUT = 627,
    DOUBLECONSTANT = 628,
    INT16CONSTANT = 629,
    UINT16CONSTANT = 630,
    FLOAT16CONSTANT = 631,
    INT32CONSTANT = 632,
    UINT32CONSTANT = 633,
    INT64CONSTANT = 634,
    UINT64CONSTANT = 635,
    SUBROUTINE = 636,
    DEMOTE = 637,
    PAYLOADNV = 638,
    PAYLOADINNV = 639,
    HITATTRNV = 640,
    CALLDATANV = 641,
    CALLDATAINNV = 642,
    PATCH = 643,
    SAMPLE = 644,
    BUFFER = 645,
    NONUNIFORM = 646,
    COHERENT = 647,
    VOLATILE = 648,
    RESTRICT = 649,
    READONLY = 650,
    WRITEONLY = 651,
    DEVICECOHERENT = 652,
    QUEUEFAMILYCOHERENT = 653,
    WORKGROUPCOHERENT = 654,
    SUBGROUPCOHERENT = 655,
    NONPRIVATE = 656,
    NOPERSPECTIVE = 657,
    EXPLICITINTERPAMD = 658,
    PERVERTEXNV = 659,
    PERPRIMITIVENV = 660,
    PERVIEWNV = 661,
    PERTASKNV = 662,
    PRECISE = 663
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 96 "MachineIndependent/glslang.y" /* yacc.c:1909  */

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

#line 499 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

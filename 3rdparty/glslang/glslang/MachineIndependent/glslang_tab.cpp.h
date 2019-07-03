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
#line 71 "MachineIndependent/glslang.y" /* yacc.c:1909  */

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

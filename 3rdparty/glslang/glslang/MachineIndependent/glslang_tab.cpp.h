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
    ICOOPMATNV = 407,
    UCOOPMATNV = 408,
    SAMPLER1D = 409,
    SAMPLER1DARRAY = 410,
    SAMPLER1DARRAYSHADOW = 411,
    ISAMPLER1D = 412,
    SAMPLER1DSHADOW = 413,
    SAMPLER2DRECT = 414,
    SAMPLER2DRECTSHADOW = 415,
    ISAMPLER2DRECT = 416,
    USAMPLER2DRECT = 417,
    SAMPLERBUFFER = 418,
    ISAMPLERBUFFER = 419,
    USAMPLERBUFFER = 420,
    SAMPLER2DMS = 421,
    ISAMPLER2DMS = 422,
    USAMPLER2DMS = 423,
    SAMPLER2DMSARRAY = 424,
    ISAMPLER2DMSARRAY = 425,
    USAMPLER2DMSARRAY = 426,
    SAMPLEREXTERNALOES = 427,
    SAMPLEREXTERNAL2DY2YEXT = 428,
    ISAMPLER1DARRAY = 429,
    USAMPLER1D = 430,
    USAMPLER1DARRAY = 431,
    F16SAMPLER1D = 432,
    F16SAMPLER2D = 433,
    F16SAMPLER3D = 434,
    F16SAMPLER2DRECT = 435,
    F16SAMPLERCUBE = 436,
    F16SAMPLER1DARRAY = 437,
    F16SAMPLER2DARRAY = 438,
    F16SAMPLERCUBEARRAY = 439,
    F16SAMPLERBUFFER = 440,
    F16SAMPLER2DMS = 441,
    F16SAMPLER2DMSARRAY = 442,
    F16SAMPLER1DSHADOW = 443,
    F16SAMPLER2DSHADOW = 444,
    F16SAMPLER1DARRAYSHADOW = 445,
    F16SAMPLER2DARRAYSHADOW = 446,
    F16SAMPLER2DRECTSHADOW = 447,
    F16SAMPLERCUBESHADOW = 448,
    F16SAMPLERCUBEARRAYSHADOW = 449,
    IMAGE1D = 450,
    IIMAGE1D = 451,
    UIMAGE1D = 452,
    IMAGE2D = 453,
    IIMAGE2D = 454,
    UIMAGE2D = 455,
    IMAGE3D = 456,
    IIMAGE3D = 457,
    UIMAGE3D = 458,
    IMAGE2DRECT = 459,
    IIMAGE2DRECT = 460,
    UIMAGE2DRECT = 461,
    IMAGECUBE = 462,
    IIMAGECUBE = 463,
    UIMAGECUBE = 464,
    IMAGEBUFFER = 465,
    IIMAGEBUFFER = 466,
    UIMAGEBUFFER = 467,
    IMAGE1DARRAY = 468,
    IIMAGE1DARRAY = 469,
    UIMAGE1DARRAY = 470,
    IMAGE2DARRAY = 471,
    IIMAGE2DARRAY = 472,
    UIMAGE2DARRAY = 473,
    IMAGECUBEARRAY = 474,
    IIMAGECUBEARRAY = 475,
    UIMAGECUBEARRAY = 476,
    IMAGE2DMS = 477,
    IIMAGE2DMS = 478,
    UIMAGE2DMS = 479,
    IMAGE2DMSARRAY = 480,
    IIMAGE2DMSARRAY = 481,
    UIMAGE2DMSARRAY = 482,
    F16IMAGE1D = 483,
    F16IMAGE2D = 484,
    F16IMAGE3D = 485,
    F16IMAGE2DRECT = 486,
    F16IMAGECUBE = 487,
    F16IMAGE1DARRAY = 488,
    F16IMAGE2DARRAY = 489,
    F16IMAGECUBEARRAY = 490,
    F16IMAGEBUFFER = 491,
    F16IMAGE2DMS = 492,
    F16IMAGE2DMSARRAY = 493,
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
    LEFT_OP = 548,
    RIGHT_OP = 549,
    INC_OP = 550,
    DEC_OP = 551,
    LE_OP = 552,
    GE_OP = 553,
    EQ_OP = 554,
    NE_OP = 555,
    AND_OP = 556,
    OR_OP = 557,
    XOR_OP = 558,
    MUL_ASSIGN = 559,
    DIV_ASSIGN = 560,
    ADD_ASSIGN = 561,
    MOD_ASSIGN = 562,
    LEFT_ASSIGN = 563,
    RIGHT_ASSIGN = 564,
    AND_ASSIGN = 565,
    XOR_ASSIGN = 566,
    OR_ASSIGN = 567,
    SUB_ASSIGN = 568,
    LEFT_PAREN = 569,
    RIGHT_PAREN = 570,
    LEFT_BRACKET = 571,
    RIGHT_BRACKET = 572,
    LEFT_BRACE = 573,
    RIGHT_BRACE = 574,
    DOT = 575,
    COMMA = 576,
    COLON = 577,
    EQUAL = 578,
    SEMICOLON = 579,
    BANG = 580,
    DASH = 581,
    TILDE = 582,
    PLUS = 583,
    STAR = 584,
    SLASH = 585,
    PERCENT = 586,
    LEFT_ANGLE = 587,
    RIGHT_ANGLE = 588,
    VERTICAL_BAR = 589,
    CARET = 590,
    AMPERSAND = 591,
    QUESTION = 592,
    INVARIANT = 593,
    HIGH_PRECISION = 594,
    MEDIUM_PRECISION = 595,
    LOW_PRECISION = 596,
    PRECISION = 597,
    PACKED = 598,
    RESOURCE = 599,
    SUPERP = 600,
    FLOATCONSTANT = 601,
    INTCONSTANT = 602,
    UINTCONSTANT = 603,
    BOOLCONSTANT = 604,
    IDENTIFIER = 605,
    TYPE_NAME = 606,
    CENTROID = 607,
    IN = 608,
    OUT = 609,
    INOUT = 610,
    STRUCT = 611,
    VOID = 612,
    WHILE = 613,
    BREAK = 614,
    CONTINUE = 615,
    DO = 616,
    ELSE = 617,
    FOR = 618,
    IF = 619,
    DISCARD = 620,
    RETURN = 621,
    SWITCH = 622,
    CASE = 623,
    DEFAULT = 624,
    UNIFORM = 625,
    SHARED = 626,
    FLAT = 627,
    SMOOTH = 628,
    LAYOUT = 629,
    DOUBLECONSTANT = 630,
    INT16CONSTANT = 631,
    UINT16CONSTANT = 632,
    FLOAT16CONSTANT = 633,
    INT32CONSTANT = 634,
    UINT32CONSTANT = 635,
    INT64CONSTANT = 636,
    UINT64CONSTANT = 637,
    SUBROUTINE = 638,
    DEMOTE = 639,
    PAYLOADNV = 640,
    PAYLOADINNV = 641,
    HITATTRNV = 642,
    CALLDATANV = 643,
    CALLDATAINNV = 644,
    PATCH = 645,
    SAMPLE = 646,
    BUFFER = 647,
    NONUNIFORM = 648,
    COHERENT = 649,
    VOLATILE = 650,
    RESTRICT = 651,
    READONLY = 652,
    WRITEONLY = 653,
    DEVICECOHERENT = 654,
    QUEUEFAMILYCOHERENT = 655,
    WORKGROUPCOHERENT = 656,
    SUBGROUPCOHERENT = 657,
    NONPRIVATE = 658,
    NOPERSPECTIVE = 659,
    EXPLICITINTERPAMD = 660,
    PERVERTEXNV = 661,
    PERPRIMITIVENV = 662,
    PERVIEWNV = 663,
    PERTASKNV = 664,
    PRECISE = 665
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

#line 501 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

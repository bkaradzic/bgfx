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
    COHERENT = 341,
    VOLATILE = 342,
    RESTRICT = 343,
    READONLY = 344,
    WRITEONLY = 345,
    DEVICECOHERENT = 346,
    QUEUEFAMILYCOHERENT = 347,
    WORKGROUPCOHERENT = 348,
    SUBGROUPCOHERENT = 349,
    NONPRIVATE = 350,
    DVEC2 = 351,
    DVEC3 = 352,
    DVEC4 = 353,
    DMAT2 = 354,
    DMAT3 = 355,
    DMAT4 = 356,
    F16VEC2 = 357,
    F16VEC3 = 358,
    F16VEC4 = 359,
    F16MAT2 = 360,
    F16MAT3 = 361,
    F16MAT4 = 362,
    F32VEC2 = 363,
    F32VEC3 = 364,
    F32VEC4 = 365,
    F32MAT2 = 366,
    F32MAT3 = 367,
    F32MAT4 = 368,
    F64VEC2 = 369,
    F64VEC3 = 370,
    F64VEC4 = 371,
    F64MAT2 = 372,
    F64MAT3 = 373,
    F64MAT4 = 374,
    NOPERSPECTIVE = 375,
    FLAT = 376,
    SMOOTH = 377,
    LAYOUT = 378,
    EXPLICITINTERPAMD = 379,
    PERVERTEXNV = 380,
    PERPRIMITIVENV = 381,
    PERVIEWNV = 382,
    PERTASKNV = 383,
    MAT2X2 = 384,
    MAT2X3 = 385,
    MAT2X4 = 386,
    MAT3X2 = 387,
    MAT3X3 = 388,
    MAT3X4 = 389,
    MAT4X2 = 390,
    MAT4X3 = 391,
    MAT4X4 = 392,
    DMAT2X2 = 393,
    DMAT2X3 = 394,
    DMAT2X4 = 395,
    DMAT3X2 = 396,
    DMAT3X3 = 397,
    DMAT3X4 = 398,
    DMAT4X2 = 399,
    DMAT4X3 = 400,
    DMAT4X4 = 401,
    F16MAT2X2 = 402,
    F16MAT2X3 = 403,
    F16MAT2X4 = 404,
    F16MAT3X2 = 405,
    F16MAT3X3 = 406,
    F16MAT3X4 = 407,
    F16MAT4X2 = 408,
    F16MAT4X3 = 409,
    F16MAT4X4 = 410,
    F32MAT2X2 = 411,
    F32MAT2X3 = 412,
    F32MAT2X4 = 413,
    F32MAT3X2 = 414,
    F32MAT3X3 = 415,
    F32MAT3X4 = 416,
    F32MAT4X2 = 417,
    F32MAT4X3 = 418,
    F32MAT4X4 = 419,
    F64MAT2X2 = 420,
    F64MAT2X3 = 421,
    F64MAT2X4 = 422,
    F64MAT3X2 = 423,
    F64MAT3X3 = 424,
    F64MAT3X4 = 425,
    F64MAT4X2 = 426,
    F64MAT4X3 = 427,
    F64MAT4X4 = 428,
    ATOMIC_UINT = 429,
    ACCSTRUCTNV = 430,
    SAMPLER1D = 431,
    SAMPLER2D = 432,
    SAMPLER3D = 433,
    SAMPLERCUBE = 434,
    SAMPLER1DSHADOW = 435,
    SAMPLER2DSHADOW = 436,
    SAMPLERCUBESHADOW = 437,
    SAMPLER1DARRAY = 438,
    SAMPLER2DARRAY = 439,
    SAMPLER1DARRAYSHADOW = 440,
    SAMPLER2DARRAYSHADOW = 441,
    ISAMPLER1D = 442,
    ISAMPLER2D = 443,
    ISAMPLER3D = 444,
    ISAMPLERCUBE = 445,
    ISAMPLER1DARRAY = 446,
    ISAMPLER2DARRAY = 447,
    USAMPLER1D = 448,
    USAMPLER2D = 449,
    USAMPLER3D = 450,
    USAMPLERCUBE = 451,
    USAMPLER1DARRAY = 452,
    USAMPLER2DARRAY = 453,
    SAMPLER2DRECT = 454,
    SAMPLER2DRECTSHADOW = 455,
    ISAMPLER2DRECT = 456,
    USAMPLER2DRECT = 457,
    SAMPLERBUFFER = 458,
    ISAMPLERBUFFER = 459,
    USAMPLERBUFFER = 460,
    SAMPLERCUBEARRAY = 461,
    SAMPLERCUBEARRAYSHADOW = 462,
    ISAMPLERCUBEARRAY = 463,
    USAMPLERCUBEARRAY = 464,
    SAMPLER2DMS = 465,
    ISAMPLER2DMS = 466,
    USAMPLER2DMS = 467,
    SAMPLER2DMSARRAY = 468,
    ISAMPLER2DMSARRAY = 469,
    USAMPLER2DMSARRAY = 470,
    SAMPLEREXTERNALOES = 471,
    F16SAMPLER1D = 472,
    F16SAMPLER2D = 473,
    F16SAMPLER3D = 474,
    F16SAMPLER2DRECT = 475,
    F16SAMPLERCUBE = 476,
    F16SAMPLER1DARRAY = 477,
    F16SAMPLER2DARRAY = 478,
    F16SAMPLERCUBEARRAY = 479,
    F16SAMPLERBUFFER = 480,
    F16SAMPLER2DMS = 481,
    F16SAMPLER2DMSARRAY = 482,
    F16SAMPLER1DSHADOW = 483,
    F16SAMPLER2DSHADOW = 484,
    F16SAMPLER1DARRAYSHADOW = 485,
    F16SAMPLER2DARRAYSHADOW = 486,
    F16SAMPLER2DRECTSHADOW = 487,
    F16SAMPLERCUBESHADOW = 488,
    F16SAMPLERCUBEARRAYSHADOW = 489,
    SAMPLER = 490,
    SAMPLERSHADOW = 491,
    TEXTURE1D = 492,
    TEXTURE2D = 493,
    TEXTURE3D = 494,
    TEXTURECUBE = 495,
    TEXTURE1DARRAY = 496,
    TEXTURE2DARRAY = 497,
    ITEXTURE1D = 498,
    ITEXTURE2D = 499,
    ITEXTURE3D = 500,
    ITEXTURECUBE = 501,
    ITEXTURE1DARRAY = 502,
    ITEXTURE2DARRAY = 503,
    UTEXTURE1D = 504,
    UTEXTURE2D = 505,
    UTEXTURE3D = 506,
    UTEXTURECUBE = 507,
    UTEXTURE1DARRAY = 508,
    UTEXTURE2DARRAY = 509,
    TEXTURE2DRECT = 510,
    ITEXTURE2DRECT = 511,
    UTEXTURE2DRECT = 512,
    TEXTUREBUFFER = 513,
    ITEXTUREBUFFER = 514,
    UTEXTUREBUFFER = 515,
    TEXTURECUBEARRAY = 516,
    ITEXTURECUBEARRAY = 517,
    UTEXTURECUBEARRAY = 518,
    TEXTURE2DMS = 519,
    ITEXTURE2DMS = 520,
    UTEXTURE2DMS = 521,
    TEXTURE2DMSARRAY = 522,
    ITEXTURE2DMSARRAY = 523,
    UTEXTURE2DMSARRAY = 524,
    F16TEXTURE1D = 525,
    F16TEXTURE2D = 526,
    F16TEXTURE3D = 527,
    F16TEXTURE2DRECT = 528,
    F16TEXTURECUBE = 529,
    F16TEXTURE1DARRAY = 530,
    F16TEXTURE2DARRAY = 531,
    F16TEXTURECUBEARRAY = 532,
    F16TEXTUREBUFFER = 533,
    F16TEXTURE2DMS = 534,
    F16TEXTURE2DMSARRAY = 535,
    SUBPASSINPUT = 536,
    SUBPASSINPUTMS = 537,
    ISUBPASSINPUT = 538,
    ISUBPASSINPUTMS = 539,
    USUBPASSINPUT = 540,
    USUBPASSINPUTMS = 541,
    F16SUBPASSINPUT = 542,
    F16SUBPASSINPUTMS = 543,
    IMAGE1D = 544,
    IIMAGE1D = 545,
    UIMAGE1D = 546,
    IMAGE2D = 547,
    IIMAGE2D = 548,
    UIMAGE2D = 549,
    IMAGE3D = 550,
    IIMAGE3D = 551,
    UIMAGE3D = 552,
    IMAGE2DRECT = 553,
    IIMAGE2DRECT = 554,
    UIMAGE2DRECT = 555,
    IMAGECUBE = 556,
    IIMAGECUBE = 557,
    UIMAGECUBE = 558,
    IMAGEBUFFER = 559,
    IIMAGEBUFFER = 560,
    UIMAGEBUFFER = 561,
    IMAGE1DARRAY = 562,
    IIMAGE1DARRAY = 563,
    UIMAGE1DARRAY = 564,
    IMAGE2DARRAY = 565,
    IIMAGE2DARRAY = 566,
    UIMAGE2DARRAY = 567,
    IMAGECUBEARRAY = 568,
    IIMAGECUBEARRAY = 569,
    UIMAGECUBEARRAY = 570,
    IMAGE2DMS = 571,
    IIMAGE2DMS = 572,
    UIMAGE2DMS = 573,
    IMAGE2DMSARRAY = 574,
    IIMAGE2DMSARRAY = 575,
    UIMAGE2DMSARRAY = 576,
    F16IMAGE1D = 577,
    F16IMAGE2D = 578,
    F16IMAGE3D = 579,
    F16IMAGE2DRECT = 580,
    F16IMAGECUBE = 581,
    F16IMAGE1DARRAY = 582,
    F16IMAGE2DARRAY = 583,
    F16IMAGECUBEARRAY = 584,
    F16IMAGEBUFFER = 585,
    F16IMAGE2DMS = 586,
    F16IMAGE2DMSARRAY = 587,
    STRUCT = 588,
    VOID = 589,
    WHILE = 590,
    IDENTIFIER = 591,
    TYPE_NAME = 592,
    FLOATCONSTANT = 593,
    DOUBLECONSTANT = 594,
    INT16CONSTANT = 595,
    UINT16CONSTANT = 596,
    INT32CONSTANT = 597,
    UINT32CONSTANT = 598,
    INTCONSTANT = 599,
    UINTCONSTANT = 600,
    INT64CONSTANT = 601,
    UINT64CONSTANT = 602,
    BOOLCONSTANT = 603,
    FLOAT16CONSTANT = 604,
    LEFT_OP = 605,
    RIGHT_OP = 606,
    INC_OP = 607,
    DEC_OP = 608,
    LE_OP = 609,
    GE_OP = 610,
    EQ_OP = 611,
    NE_OP = 612,
    AND_OP = 613,
    OR_OP = 614,
    XOR_OP = 615,
    MUL_ASSIGN = 616,
    DIV_ASSIGN = 617,
    ADD_ASSIGN = 618,
    MOD_ASSIGN = 619,
    LEFT_ASSIGN = 620,
    RIGHT_ASSIGN = 621,
    AND_ASSIGN = 622,
    XOR_ASSIGN = 623,
    OR_ASSIGN = 624,
    SUB_ASSIGN = 625,
    LEFT_PAREN = 626,
    RIGHT_PAREN = 627,
    LEFT_BRACKET = 628,
    RIGHT_BRACKET = 629,
    LEFT_BRACE = 630,
    RIGHT_BRACE = 631,
    DOT = 632,
    COMMA = 633,
    COLON = 634,
    EQUAL = 635,
    SEMICOLON = 636,
    BANG = 637,
    DASH = 638,
    TILDE = 639,
    PLUS = 640,
    STAR = 641,
    SLASH = 642,
    PERCENT = 643,
    LEFT_ANGLE = 644,
    RIGHT_ANGLE = 645,
    VERTICAL_BAR = 646,
    CARET = 647,
    AMPERSAND = 648,
    QUESTION = 649,
    INVARIANT = 650,
    PRECISE = 651,
    HIGH_PRECISION = 652,
    MEDIUM_PRECISION = 653,
    LOW_PRECISION = 654,
    PRECISION = 655,
    PACKED = 656,
    RESOURCE = 657,
    SUPERP = 658
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

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

#line 493 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

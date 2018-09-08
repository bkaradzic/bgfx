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
    COHERENT = 338,
    VOLATILE = 339,
    RESTRICT = 340,
    READONLY = 341,
    WRITEONLY = 342,
    DEVICECOHERENT = 343,
    QUEUEFAMILYCOHERENT = 344,
    WORKGROUPCOHERENT = 345,
    SUBGROUPCOHERENT = 346,
    NONPRIVATE = 347,
    DVEC2 = 348,
    DVEC3 = 349,
    DVEC4 = 350,
    DMAT2 = 351,
    DMAT3 = 352,
    DMAT4 = 353,
    F16VEC2 = 354,
    F16VEC3 = 355,
    F16VEC4 = 356,
    F16MAT2 = 357,
    F16MAT3 = 358,
    F16MAT4 = 359,
    F32VEC2 = 360,
    F32VEC3 = 361,
    F32VEC4 = 362,
    F32MAT2 = 363,
    F32MAT3 = 364,
    F32MAT4 = 365,
    F64VEC2 = 366,
    F64VEC3 = 367,
    F64VEC4 = 368,
    F64MAT2 = 369,
    F64MAT3 = 370,
    F64MAT4 = 371,
    NOPERSPECTIVE = 372,
    FLAT = 373,
    SMOOTH = 374,
    LAYOUT = 375,
    EXPLICITINTERPAMD = 376,
    MAT2X2 = 377,
    MAT2X3 = 378,
    MAT2X4 = 379,
    MAT3X2 = 380,
    MAT3X3 = 381,
    MAT3X4 = 382,
    MAT4X2 = 383,
    MAT4X3 = 384,
    MAT4X4 = 385,
    DMAT2X2 = 386,
    DMAT2X3 = 387,
    DMAT2X4 = 388,
    DMAT3X2 = 389,
    DMAT3X3 = 390,
    DMAT3X4 = 391,
    DMAT4X2 = 392,
    DMAT4X3 = 393,
    DMAT4X4 = 394,
    F16MAT2X2 = 395,
    F16MAT2X3 = 396,
    F16MAT2X4 = 397,
    F16MAT3X2 = 398,
    F16MAT3X3 = 399,
    F16MAT3X4 = 400,
    F16MAT4X2 = 401,
    F16MAT4X3 = 402,
    F16MAT4X4 = 403,
    F32MAT2X2 = 404,
    F32MAT2X3 = 405,
    F32MAT2X4 = 406,
    F32MAT3X2 = 407,
    F32MAT3X3 = 408,
    F32MAT3X4 = 409,
    F32MAT4X2 = 410,
    F32MAT4X3 = 411,
    F32MAT4X4 = 412,
    F64MAT2X2 = 413,
    F64MAT2X3 = 414,
    F64MAT2X4 = 415,
    F64MAT3X2 = 416,
    F64MAT3X3 = 417,
    F64MAT3X4 = 418,
    F64MAT4X2 = 419,
    F64MAT4X3 = 420,
    F64MAT4X4 = 421,
    ATOMIC_UINT = 422,
    SAMPLER1D = 423,
    SAMPLER2D = 424,
    SAMPLER3D = 425,
    SAMPLERCUBE = 426,
    SAMPLER1DSHADOW = 427,
    SAMPLER2DSHADOW = 428,
    SAMPLERCUBESHADOW = 429,
    SAMPLER1DARRAY = 430,
    SAMPLER2DARRAY = 431,
    SAMPLER1DARRAYSHADOW = 432,
    SAMPLER2DARRAYSHADOW = 433,
    ISAMPLER1D = 434,
    ISAMPLER2D = 435,
    ISAMPLER3D = 436,
    ISAMPLERCUBE = 437,
    ISAMPLER1DARRAY = 438,
    ISAMPLER2DARRAY = 439,
    USAMPLER1D = 440,
    USAMPLER2D = 441,
    USAMPLER3D = 442,
    USAMPLERCUBE = 443,
    USAMPLER1DARRAY = 444,
    USAMPLER2DARRAY = 445,
    SAMPLER2DRECT = 446,
    SAMPLER2DRECTSHADOW = 447,
    ISAMPLER2DRECT = 448,
    USAMPLER2DRECT = 449,
    SAMPLERBUFFER = 450,
    ISAMPLERBUFFER = 451,
    USAMPLERBUFFER = 452,
    SAMPLERCUBEARRAY = 453,
    SAMPLERCUBEARRAYSHADOW = 454,
    ISAMPLERCUBEARRAY = 455,
    USAMPLERCUBEARRAY = 456,
    SAMPLER2DMS = 457,
    ISAMPLER2DMS = 458,
    USAMPLER2DMS = 459,
    SAMPLER2DMSARRAY = 460,
    ISAMPLER2DMSARRAY = 461,
    USAMPLER2DMSARRAY = 462,
    SAMPLEREXTERNALOES = 463,
    F16SAMPLER1D = 464,
    F16SAMPLER2D = 465,
    F16SAMPLER3D = 466,
    F16SAMPLER2DRECT = 467,
    F16SAMPLERCUBE = 468,
    F16SAMPLER1DARRAY = 469,
    F16SAMPLER2DARRAY = 470,
    F16SAMPLERCUBEARRAY = 471,
    F16SAMPLERBUFFER = 472,
    F16SAMPLER2DMS = 473,
    F16SAMPLER2DMSARRAY = 474,
    F16SAMPLER1DSHADOW = 475,
    F16SAMPLER2DSHADOW = 476,
    F16SAMPLER1DARRAYSHADOW = 477,
    F16SAMPLER2DARRAYSHADOW = 478,
    F16SAMPLER2DRECTSHADOW = 479,
    F16SAMPLERCUBESHADOW = 480,
    F16SAMPLERCUBEARRAYSHADOW = 481,
    SAMPLER = 482,
    SAMPLERSHADOW = 483,
    TEXTURE1D = 484,
    TEXTURE2D = 485,
    TEXTURE3D = 486,
    TEXTURECUBE = 487,
    TEXTURE1DARRAY = 488,
    TEXTURE2DARRAY = 489,
    ITEXTURE1D = 490,
    ITEXTURE2D = 491,
    ITEXTURE3D = 492,
    ITEXTURECUBE = 493,
    ITEXTURE1DARRAY = 494,
    ITEXTURE2DARRAY = 495,
    UTEXTURE1D = 496,
    UTEXTURE2D = 497,
    UTEXTURE3D = 498,
    UTEXTURECUBE = 499,
    UTEXTURE1DARRAY = 500,
    UTEXTURE2DARRAY = 501,
    TEXTURE2DRECT = 502,
    ITEXTURE2DRECT = 503,
    UTEXTURE2DRECT = 504,
    TEXTUREBUFFER = 505,
    ITEXTUREBUFFER = 506,
    UTEXTUREBUFFER = 507,
    TEXTURECUBEARRAY = 508,
    ITEXTURECUBEARRAY = 509,
    UTEXTURECUBEARRAY = 510,
    TEXTURE2DMS = 511,
    ITEXTURE2DMS = 512,
    UTEXTURE2DMS = 513,
    TEXTURE2DMSARRAY = 514,
    ITEXTURE2DMSARRAY = 515,
    UTEXTURE2DMSARRAY = 516,
    F16TEXTURE1D = 517,
    F16TEXTURE2D = 518,
    F16TEXTURE3D = 519,
    F16TEXTURE2DRECT = 520,
    F16TEXTURECUBE = 521,
    F16TEXTURE1DARRAY = 522,
    F16TEXTURE2DARRAY = 523,
    F16TEXTURECUBEARRAY = 524,
    F16TEXTUREBUFFER = 525,
    F16TEXTURE2DMS = 526,
    F16TEXTURE2DMSARRAY = 527,
    SUBPASSINPUT = 528,
    SUBPASSINPUTMS = 529,
    ISUBPASSINPUT = 530,
    ISUBPASSINPUTMS = 531,
    USUBPASSINPUT = 532,
    USUBPASSINPUTMS = 533,
    F16SUBPASSINPUT = 534,
    F16SUBPASSINPUTMS = 535,
    IMAGE1D = 536,
    IIMAGE1D = 537,
    UIMAGE1D = 538,
    IMAGE2D = 539,
    IIMAGE2D = 540,
    UIMAGE2D = 541,
    IMAGE3D = 542,
    IIMAGE3D = 543,
    UIMAGE3D = 544,
    IMAGE2DRECT = 545,
    IIMAGE2DRECT = 546,
    UIMAGE2DRECT = 547,
    IMAGECUBE = 548,
    IIMAGECUBE = 549,
    UIMAGECUBE = 550,
    IMAGEBUFFER = 551,
    IIMAGEBUFFER = 552,
    UIMAGEBUFFER = 553,
    IMAGE1DARRAY = 554,
    IIMAGE1DARRAY = 555,
    UIMAGE1DARRAY = 556,
    IMAGE2DARRAY = 557,
    IIMAGE2DARRAY = 558,
    UIMAGE2DARRAY = 559,
    IMAGECUBEARRAY = 560,
    IIMAGECUBEARRAY = 561,
    UIMAGECUBEARRAY = 562,
    IMAGE2DMS = 563,
    IIMAGE2DMS = 564,
    UIMAGE2DMS = 565,
    IMAGE2DMSARRAY = 566,
    IIMAGE2DMSARRAY = 567,
    UIMAGE2DMSARRAY = 568,
    F16IMAGE1D = 569,
    F16IMAGE2D = 570,
    F16IMAGE3D = 571,
    F16IMAGE2DRECT = 572,
    F16IMAGECUBE = 573,
    F16IMAGE1DARRAY = 574,
    F16IMAGE2DARRAY = 575,
    F16IMAGECUBEARRAY = 576,
    F16IMAGEBUFFER = 577,
    F16IMAGE2DMS = 578,
    F16IMAGE2DMSARRAY = 579,
    STRUCT = 580,
    VOID = 581,
    WHILE = 582,
    IDENTIFIER = 583,
    TYPE_NAME = 584,
    FLOATCONSTANT = 585,
    DOUBLECONSTANT = 586,
    INT16CONSTANT = 587,
    UINT16CONSTANT = 588,
    INT32CONSTANT = 589,
    UINT32CONSTANT = 590,
    INTCONSTANT = 591,
    UINTCONSTANT = 592,
    INT64CONSTANT = 593,
    UINT64CONSTANT = 594,
    BOOLCONSTANT = 595,
    FLOAT16CONSTANT = 596,
    LEFT_OP = 597,
    RIGHT_OP = 598,
    INC_OP = 599,
    DEC_OP = 600,
    LE_OP = 601,
    GE_OP = 602,
    EQ_OP = 603,
    NE_OP = 604,
    AND_OP = 605,
    OR_OP = 606,
    XOR_OP = 607,
    MUL_ASSIGN = 608,
    DIV_ASSIGN = 609,
    ADD_ASSIGN = 610,
    MOD_ASSIGN = 611,
    LEFT_ASSIGN = 612,
    RIGHT_ASSIGN = 613,
    AND_ASSIGN = 614,
    XOR_ASSIGN = 615,
    OR_ASSIGN = 616,
    SUB_ASSIGN = 617,
    LEFT_PAREN = 618,
    RIGHT_PAREN = 619,
    LEFT_BRACKET = 620,
    RIGHT_BRACKET = 621,
    LEFT_BRACE = 622,
    RIGHT_BRACE = 623,
    DOT = 624,
    COMMA = 625,
    COLON = 626,
    EQUAL = 627,
    SEMICOLON = 628,
    BANG = 629,
    DASH = 630,
    TILDE = 631,
    PLUS = 632,
    STAR = 633,
    SLASH = 634,
    PERCENT = 635,
    LEFT_ANGLE = 636,
    RIGHT_ANGLE = 637,
    VERTICAL_BAR = 638,
    CARET = 639,
    AMPERSAND = 640,
    QUESTION = 641,
    INVARIANT = 642,
    PRECISE = 643,
    HIGH_PRECISION = 644,
    MEDIUM_PRECISION = 645,
    LOW_PRECISION = 646,
    PRECISION = 647,
    PACKED = 648,
    RESOURCE = 649,
    SUPERP = 650
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

#line 485 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    BOOL = 259,                    /* BOOL  */
    INT = 260,                     /* INT  */
    UINT = 261,                    /* UINT  */
    FLOAT = 262,                   /* FLOAT  */
    BVEC2 = 263,                   /* BVEC2  */
    BVEC3 = 264,                   /* BVEC3  */
    BVEC4 = 265,                   /* BVEC4  */
    IVEC2 = 266,                   /* IVEC2  */
    IVEC3 = 267,                   /* IVEC3  */
    IVEC4 = 268,                   /* IVEC4  */
    UVEC2 = 269,                   /* UVEC2  */
    UVEC3 = 270,                   /* UVEC3  */
    UVEC4 = 271,                   /* UVEC4  */
    VEC2 = 272,                    /* VEC2  */
    VEC3 = 273,                    /* VEC3  */
    VEC4 = 274,                    /* VEC4  */
    MAT2 = 275,                    /* MAT2  */
    MAT3 = 276,                    /* MAT3  */
    MAT4 = 277,                    /* MAT4  */
    MAT2X2 = 278,                  /* MAT2X2  */
    MAT2X3 = 279,                  /* MAT2X3  */
    MAT2X4 = 280,                  /* MAT2X4  */
    MAT3X2 = 281,                  /* MAT3X2  */
    MAT3X3 = 282,                  /* MAT3X3  */
    MAT3X4 = 283,                  /* MAT3X4  */
    MAT4X2 = 284,                  /* MAT4X2  */
    MAT4X3 = 285,                  /* MAT4X3  */
    MAT4X4 = 286,                  /* MAT4X4  */
    SAMPLER2D = 287,               /* SAMPLER2D  */
    SAMPLER3D = 288,               /* SAMPLER3D  */
    SAMPLERCUBE = 289,             /* SAMPLERCUBE  */
    SAMPLER2DSHADOW = 290,         /* SAMPLER2DSHADOW  */
    SAMPLERCUBESHADOW = 291,       /* SAMPLERCUBESHADOW  */
    SAMPLER2DARRAY = 292,          /* SAMPLER2DARRAY  */
    SAMPLER2DARRAYSHADOW = 293,    /* SAMPLER2DARRAYSHADOW  */
    ISAMPLER2D = 294,              /* ISAMPLER2D  */
    ISAMPLER3D = 295,              /* ISAMPLER3D  */
    ISAMPLERCUBE = 296,            /* ISAMPLERCUBE  */
    ISAMPLER2DARRAY = 297,         /* ISAMPLER2DARRAY  */
    USAMPLER2D = 298,              /* USAMPLER2D  */
    USAMPLER3D = 299,              /* USAMPLER3D  */
    USAMPLERCUBE = 300,            /* USAMPLERCUBE  */
    USAMPLER2DARRAY = 301,         /* USAMPLER2DARRAY  */
    SAMPLER = 302,                 /* SAMPLER  */
    SAMPLERSHADOW = 303,           /* SAMPLERSHADOW  */
    TEXTURE2D = 304,               /* TEXTURE2D  */
    TEXTURE3D = 305,               /* TEXTURE3D  */
    TEXTURECUBE = 306,             /* TEXTURECUBE  */
    TEXTURE2DARRAY = 307,          /* TEXTURE2DARRAY  */
    ITEXTURE2D = 308,              /* ITEXTURE2D  */
    ITEXTURE3D = 309,              /* ITEXTURE3D  */
    ITEXTURECUBE = 310,            /* ITEXTURECUBE  */
    ITEXTURE2DARRAY = 311,         /* ITEXTURE2DARRAY  */
    UTEXTURE2D = 312,              /* UTEXTURE2D  */
    UTEXTURE3D = 313,              /* UTEXTURE3D  */
    UTEXTURECUBE = 314,            /* UTEXTURECUBE  */
    UTEXTURE2DARRAY = 315,         /* UTEXTURE2DARRAY  */
    ATTRIBUTE = 316,               /* ATTRIBUTE  */
    VARYING = 317,                 /* VARYING  */
    FLOATE5M2_T = 318,             /* FLOATE5M2_T  */
    FLOATE4M3_T = 319,             /* FLOATE4M3_T  */
    BFLOAT16_T = 320,              /* BFLOAT16_T  */
    FLOAT16_T = 321,               /* FLOAT16_T  */
    FLOAT32_T = 322,               /* FLOAT32_T  */
    DOUBLE = 323,                  /* DOUBLE  */
    FLOAT64_T = 324,               /* FLOAT64_T  */
    FLOATE2M1_T = 325,             /* FLOATE2M1_T  */
    FLOATE3M2_T = 326,             /* FLOATE3M2_T  */
    FLOATE2M3_T = 327,             /* FLOATE2M3_T  */
    FLOATUE8M0_T = 328,            /* FLOATUE8M0_T  */
    FLOATMXINT8_T = 329,           /* FLOATMXINT8_T  */
    INT64_T = 330,                 /* INT64_T  */
    UINT64_T = 331,                /* UINT64_T  */
    INT32_T = 332,                 /* INT32_T  */
    UINT32_T = 333,                /* UINT32_T  */
    INT16_T = 334,                 /* INT16_T  */
    UINT16_T = 335,                /* UINT16_T  */
    INT8_T = 336,                  /* INT8_T  */
    UINT8_T = 337,                 /* UINT8_T  */
    I64VEC2 = 338,                 /* I64VEC2  */
    I64VEC3 = 339,                 /* I64VEC3  */
    I64VEC4 = 340,                 /* I64VEC4  */
    U64VEC2 = 341,                 /* U64VEC2  */
    U64VEC3 = 342,                 /* U64VEC3  */
    U64VEC4 = 343,                 /* U64VEC4  */
    I32VEC2 = 344,                 /* I32VEC2  */
    I32VEC3 = 345,                 /* I32VEC3  */
    I32VEC4 = 346,                 /* I32VEC4  */
    U32VEC2 = 347,                 /* U32VEC2  */
    U32VEC3 = 348,                 /* U32VEC3  */
    U32VEC4 = 349,                 /* U32VEC4  */
    I16VEC2 = 350,                 /* I16VEC2  */
    I16VEC3 = 351,                 /* I16VEC3  */
    I16VEC4 = 352,                 /* I16VEC4  */
    U16VEC2 = 353,                 /* U16VEC2  */
    U16VEC3 = 354,                 /* U16VEC3  */
    U16VEC4 = 355,                 /* U16VEC4  */
    I8VEC2 = 356,                  /* I8VEC2  */
    I8VEC3 = 357,                  /* I8VEC3  */
    I8VEC4 = 358,                  /* I8VEC4  */
    U8VEC2 = 359,                  /* U8VEC2  */
    U8VEC3 = 360,                  /* U8VEC3  */
    U8VEC4 = 361,                  /* U8VEC4  */
    DVEC2 = 362,                   /* DVEC2  */
    DVEC3 = 363,                   /* DVEC3  */
    DVEC4 = 364,                   /* DVEC4  */
    DMAT2 = 365,                   /* DMAT2  */
    DMAT3 = 366,                   /* DMAT3  */
    DMAT4 = 367,                   /* DMAT4  */
    BF16VEC2 = 368,                /* BF16VEC2  */
    BF16VEC3 = 369,                /* BF16VEC3  */
    BF16VEC4 = 370,                /* BF16VEC4  */
    FE5M2VEC2 = 371,               /* FE5M2VEC2  */
    FE5M2VEC3 = 372,               /* FE5M2VEC3  */
    FE5M2VEC4 = 373,               /* FE5M2VEC4  */
    FE4M3VEC2 = 374,               /* FE4M3VEC2  */
    FE4M3VEC3 = 375,               /* FE4M3VEC3  */
    FE4M3VEC4 = 376,               /* FE4M3VEC4  */
    FE2M1VEC2 = 377,               /* FE2M1VEC2  */
    FE2M1VEC3 = 378,               /* FE2M1VEC3  */
    FE2M1VEC4 = 379,               /* FE2M1VEC4  */
    FE3M2VEC2 = 380,               /* FE3M2VEC2  */
    FE3M2VEC3 = 381,               /* FE3M2VEC3  */
    FE3M2VEC4 = 382,               /* FE3M2VEC4  */
    FE2M3VEC2 = 383,               /* FE2M3VEC2  */
    FE2M3VEC3 = 384,               /* FE2M3VEC3  */
    FE2M3VEC4 = 385,               /* FE2M3VEC4  */
    FUE8M0VEC2 = 386,              /* FUE8M0VEC2  */
    FUE8M0VEC3 = 387,              /* FUE8M0VEC3  */
    FUE8M0VEC4 = 388,              /* FUE8M0VEC4  */
    FMXINT8VEC2 = 389,             /* FMXINT8VEC2  */
    FMXINT8VEC3 = 390,             /* FMXINT8VEC3  */
    FMXINT8VEC4 = 391,             /* FMXINT8VEC4  */
    F16VEC2 = 392,                 /* F16VEC2  */
    F16VEC3 = 393,                 /* F16VEC3  */
    F16VEC4 = 394,                 /* F16VEC4  */
    F16MAT2 = 395,                 /* F16MAT2  */
    F16MAT3 = 396,                 /* F16MAT3  */
    F16MAT4 = 397,                 /* F16MAT4  */
    F32VEC2 = 398,                 /* F32VEC2  */
    F32VEC3 = 399,                 /* F32VEC3  */
    F32VEC4 = 400,                 /* F32VEC4  */
    F32MAT2 = 401,                 /* F32MAT2  */
    F32MAT3 = 402,                 /* F32MAT3  */
    F32MAT4 = 403,                 /* F32MAT4  */
    F64VEC2 = 404,                 /* F64VEC2  */
    F64VEC3 = 405,                 /* F64VEC3  */
    F64VEC4 = 406,                 /* F64VEC4  */
    F64MAT2 = 407,                 /* F64MAT2  */
    F64MAT3 = 408,                 /* F64MAT3  */
    F64MAT4 = 409,                 /* F64MAT4  */
    DMAT2X2 = 410,                 /* DMAT2X2  */
    DMAT2X3 = 411,                 /* DMAT2X3  */
    DMAT2X4 = 412,                 /* DMAT2X4  */
    DMAT3X2 = 413,                 /* DMAT3X2  */
    DMAT3X3 = 414,                 /* DMAT3X3  */
    DMAT3X4 = 415,                 /* DMAT3X4  */
    DMAT4X2 = 416,                 /* DMAT4X2  */
    DMAT4X3 = 417,                 /* DMAT4X3  */
    DMAT4X4 = 418,                 /* DMAT4X4  */
    F16MAT2X2 = 419,               /* F16MAT2X2  */
    F16MAT2X3 = 420,               /* F16MAT2X3  */
    F16MAT2X4 = 421,               /* F16MAT2X4  */
    F16MAT3X2 = 422,               /* F16MAT3X2  */
    F16MAT3X3 = 423,               /* F16MAT3X3  */
    F16MAT3X4 = 424,               /* F16MAT3X4  */
    F16MAT4X2 = 425,               /* F16MAT4X2  */
    F16MAT4X3 = 426,               /* F16MAT4X3  */
    F16MAT4X4 = 427,               /* F16MAT4X4  */
    F32MAT2X2 = 428,               /* F32MAT2X2  */
    F32MAT2X3 = 429,               /* F32MAT2X3  */
    F32MAT2X4 = 430,               /* F32MAT2X4  */
    F32MAT3X2 = 431,               /* F32MAT3X2  */
    F32MAT3X3 = 432,               /* F32MAT3X3  */
    F32MAT3X4 = 433,               /* F32MAT3X4  */
    F32MAT4X2 = 434,               /* F32MAT4X2  */
    F32MAT4X3 = 435,               /* F32MAT4X3  */
    F32MAT4X4 = 436,               /* F32MAT4X4  */
    F64MAT2X2 = 437,               /* F64MAT2X2  */
    F64MAT2X3 = 438,               /* F64MAT2X3  */
    F64MAT2X4 = 439,               /* F64MAT2X4  */
    F64MAT3X2 = 440,               /* F64MAT3X2  */
    F64MAT3X3 = 441,               /* F64MAT3X3  */
    F64MAT3X4 = 442,               /* F64MAT3X4  */
    F64MAT4X2 = 443,               /* F64MAT4X2  */
    F64MAT4X3 = 444,               /* F64MAT4X3  */
    F64MAT4X4 = 445,               /* F64MAT4X4  */
    ATOMIC_UINT = 446,             /* ATOMIC_UINT  */
    ACCSTRUCTNV = 447,             /* ACCSTRUCTNV  */
    ACCSTRUCTEXT = 448,            /* ACCSTRUCTEXT  */
    RAYQUERYEXT = 449,             /* RAYQUERYEXT  */
    FCOOPMATNV = 450,              /* FCOOPMATNV  */
    ICOOPMATNV = 451,              /* ICOOPMATNV  */
    UCOOPMATNV = 452,              /* UCOOPMATNV  */
    COOPMAT = 453,                 /* COOPMAT  */
    COOPVECNV = 454,               /* COOPVECNV  */
    VECTOR = 455,                  /* VECTOR  */
    HITOBJECTNV = 456,             /* HITOBJECTNV  */
    HITOBJECTATTRNV = 457,         /* HITOBJECTATTRNV  */
    HITOBJECTEXT = 458,            /* HITOBJECTEXT  */
    HITOBJECTATTREXT = 459,        /* HITOBJECTATTREXT  */
    TENSORLAYOUTNV = 460,          /* TENSORLAYOUTNV  */
    TENSORVIEWNV = 461,            /* TENSORVIEWNV  */
    TENSORARM = 462,               /* TENSORARM  */
    SAMPLERCUBEARRAY = 463,        /* SAMPLERCUBEARRAY  */
    SAMPLERCUBEARRAYSHADOW = 464,  /* SAMPLERCUBEARRAYSHADOW  */
    ISAMPLERCUBEARRAY = 465,       /* ISAMPLERCUBEARRAY  */
    USAMPLERCUBEARRAY = 466,       /* USAMPLERCUBEARRAY  */
    SAMPLER1D = 467,               /* SAMPLER1D  */
    SAMPLER1DARRAY = 468,          /* SAMPLER1DARRAY  */
    SAMPLER1DARRAYSHADOW = 469,    /* SAMPLER1DARRAYSHADOW  */
    ISAMPLER1D = 470,              /* ISAMPLER1D  */
    SAMPLER1DSHADOW = 471,         /* SAMPLER1DSHADOW  */
    SAMPLER2DRECT = 472,           /* SAMPLER2DRECT  */
    SAMPLER2DRECTSHADOW = 473,     /* SAMPLER2DRECTSHADOW  */
    ISAMPLER2DRECT = 474,          /* ISAMPLER2DRECT  */
    USAMPLER2DRECT = 475,          /* USAMPLER2DRECT  */
    SAMPLERBUFFER = 476,           /* SAMPLERBUFFER  */
    ISAMPLERBUFFER = 477,          /* ISAMPLERBUFFER  */
    USAMPLERBUFFER = 478,          /* USAMPLERBUFFER  */
    SAMPLER2DMS = 479,             /* SAMPLER2DMS  */
    ISAMPLER2DMS = 480,            /* ISAMPLER2DMS  */
    USAMPLER2DMS = 481,            /* USAMPLER2DMS  */
    SAMPLER2DMSARRAY = 482,        /* SAMPLER2DMSARRAY  */
    ISAMPLER2DMSARRAY = 483,       /* ISAMPLER2DMSARRAY  */
    USAMPLER2DMSARRAY = 484,       /* USAMPLER2DMSARRAY  */
    SAMPLEREXTERNALOES = 485,      /* SAMPLEREXTERNALOES  */
    SAMPLEREXTERNAL2DY2YEXT = 486, /* SAMPLEREXTERNAL2DY2YEXT  */
    ISAMPLER1DARRAY = 487,         /* ISAMPLER1DARRAY  */
    USAMPLER1D = 488,              /* USAMPLER1D  */
    USAMPLER1DARRAY = 489,         /* USAMPLER1DARRAY  */
    F16SAMPLER1D = 490,            /* F16SAMPLER1D  */
    F16SAMPLER2D = 491,            /* F16SAMPLER2D  */
    F16SAMPLER3D = 492,            /* F16SAMPLER3D  */
    F16SAMPLER2DRECT = 493,        /* F16SAMPLER2DRECT  */
    F16SAMPLERCUBE = 494,          /* F16SAMPLERCUBE  */
    F16SAMPLER1DARRAY = 495,       /* F16SAMPLER1DARRAY  */
    F16SAMPLER2DARRAY = 496,       /* F16SAMPLER2DARRAY  */
    F16SAMPLERCUBEARRAY = 497,     /* F16SAMPLERCUBEARRAY  */
    F16SAMPLERBUFFER = 498,        /* F16SAMPLERBUFFER  */
    F16SAMPLER2DMS = 499,          /* F16SAMPLER2DMS  */
    F16SAMPLER2DMSARRAY = 500,     /* F16SAMPLER2DMSARRAY  */
    F16SAMPLER1DSHADOW = 501,      /* F16SAMPLER1DSHADOW  */
    F16SAMPLER2DSHADOW = 502,      /* F16SAMPLER2DSHADOW  */
    F16SAMPLER1DARRAYSHADOW = 503, /* F16SAMPLER1DARRAYSHADOW  */
    F16SAMPLER2DARRAYSHADOW = 504, /* F16SAMPLER2DARRAYSHADOW  */
    F16SAMPLER2DRECTSHADOW = 505,  /* F16SAMPLER2DRECTSHADOW  */
    F16SAMPLERCUBESHADOW = 506,    /* F16SAMPLERCUBESHADOW  */
    F16SAMPLERCUBEARRAYSHADOW = 507, /* F16SAMPLERCUBEARRAYSHADOW  */
    IMAGE1D = 508,                 /* IMAGE1D  */
    IIMAGE1D = 509,                /* IIMAGE1D  */
    UIMAGE1D = 510,                /* UIMAGE1D  */
    IMAGE2D = 511,                 /* IMAGE2D  */
    IIMAGE2D = 512,                /* IIMAGE2D  */
    UIMAGE2D = 513,                /* UIMAGE2D  */
    IMAGE3D = 514,                 /* IMAGE3D  */
    IIMAGE3D = 515,                /* IIMAGE3D  */
    UIMAGE3D = 516,                /* UIMAGE3D  */
    IMAGE2DRECT = 517,             /* IMAGE2DRECT  */
    IIMAGE2DRECT = 518,            /* IIMAGE2DRECT  */
    UIMAGE2DRECT = 519,            /* UIMAGE2DRECT  */
    IMAGECUBE = 520,               /* IMAGECUBE  */
    IIMAGECUBE = 521,              /* IIMAGECUBE  */
    UIMAGECUBE = 522,              /* UIMAGECUBE  */
    IMAGEBUFFER = 523,             /* IMAGEBUFFER  */
    IIMAGEBUFFER = 524,            /* IIMAGEBUFFER  */
    UIMAGEBUFFER = 525,            /* UIMAGEBUFFER  */
    IMAGE1DARRAY = 526,            /* IMAGE1DARRAY  */
    IIMAGE1DARRAY = 527,           /* IIMAGE1DARRAY  */
    UIMAGE1DARRAY = 528,           /* UIMAGE1DARRAY  */
    IMAGE2DARRAY = 529,            /* IMAGE2DARRAY  */
    IIMAGE2DARRAY = 530,           /* IIMAGE2DARRAY  */
    UIMAGE2DARRAY = 531,           /* UIMAGE2DARRAY  */
    IMAGECUBEARRAY = 532,          /* IMAGECUBEARRAY  */
    IIMAGECUBEARRAY = 533,         /* IIMAGECUBEARRAY  */
    UIMAGECUBEARRAY = 534,         /* UIMAGECUBEARRAY  */
    IMAGE2DMS = 535,               /* IMAGE2DMS  */
    IIMAGE2DMS = 536,              /* IIMAGE2DMS  */
    UIMAGE2DMS = 537,              /* UIMAGE2DMS  */
    IMAGE2DMSARRAY = 538,          /* IMAGE2DMSARRAY  */
    IIMAGE2DMSARRAY = 539,         /* IIMAGE2DMSARRAY  */
    UIMAGE2DMSARRAY = 540,         /* UIMAGE2DMSARRAY  */
    F16IMAGE1D = 541,              /* F16IMAGE1D  */
    F16IMAGE2D = 542,              /* F16IMAGE2D  */
    F16IMAGE3D = 543,              /* F16IMAGE3D  */
    F16IMAGE2DRECT = 544,          /* F16IMAGE2DRECT  */
    F16IMAGECUBE = 545,            /* F16IMAGECUBE  */
    F16IMAGE1DARRAY = 546,         /* F16IMAGE1DARRAY  */
    F16IMAGE2DARRAY = 547,         /* F16IMAGE2DARRAY  */
    F16IMAGECUBEARRAY = 548,       /* F16IMAGECUBEARRAY  */
    F16IMAGEBUFFER = 549,          /* F16IMAGEBUFFER  */
    F16IMAGE2DMS = 550,            /* F16IMAGE2DMS  */
    F16IMAGE2DMSARRAY = 551,       /* F16IMAGE2DMSARRAY  */
    I64IMAGE1D = 552,              /* I64IMAGE1D  */
    U64IMAGE1D = 553,              /* U64IMAGE1D  */
    I64IMAGE2D = 554,              /* I64IMAGE2D  */
    U64IMAGE2D = 555,              /* U64IMAGE2D  */
    I64IMAGE3D = 556,              /* I64IMAGE3D  */
    U64IMAGE3D = 557,              /* U64IMAGE3D  */
    I64IMAGE2DRECT = 558,          /* I64IMAGE2DRECT  */
    U64IMAGE2DRECT = 559,          /* U64IMAGE2DRECT  */
    I64IMAGECUBE = 560,            /* I64IMAGECUBE  */
    U64IMAGECUBE = 561,            /* U64IMAGECUBE  */
    I64IMAGEBUFFER = 562,          /* I64IMAGEBUFFER  */
    U64IMAGEBUFFER = 563,          /* U64IMAGEBUFFER  */
    I64IMAGE1DARRAY = 564,         /* I64IMAGE1DARRAY  */
    U64IMAGE1DARRAY = 565,         /* U64IMAGE1DARRAY  */
    I64IMAGE2DARRAY = 566,         /* I64IMAGE2DARRAY  */
    U64IMAGE2DARRAY = 567,         /* U64IMAGE2DARRAY  */
    I64IMAGECUBEARRAY = 568,       /* I64IMAGECUBEARRAY  */
    U64IMAGECUBEARRAY = 569,       /* U64IMAGECUBEARRAY  */
    I64IMAGE2DMS = 570,            /* I64IMAGE2DMS  */
    U64IMAGE2DMS = 571,            /* U64IMAGE2DMS  */
    I64IMAGE2DMSARRAY = 572,       /* I64IMAGE2DMSARRAY  */
    U64IMAGE2DMSARRAY = 573,       /* U64IMAGE2DMSARRAY  */
    TEXTURECUBEARRAY = 574,        /* TEXTURECUBEARRAY  */
    ITEXTURECUBEARRAY = 575,       /* ITEXTURECUBEARRAY  */
    UTEXTURECUBEARRAY = 576,       /* UTEXTURECUBEARRAY  */
    TEXTURE1D = 577,               /* TEXTURE1D  */
    ITEXTURE1D = 578,              /* ITEXTURE1D  */
    UTEXTURE1D = 579,              /* UTEXTURE1D  */
    TEXTURE1DARRAY = 580,          /* TEXTURE1DARRAY  */
    ITEXTURE1DARRAY = 581,         /* ITEXTURE1DARRAY  */
    UTEXTURE1DARRAY = 582,         /* UTEXTURE1DARRAY  */
    TEXTURE2DRECT = 583,           /* TEXTURE2DRECT  */
    ITEXTURE2DRECT = 584,          /* ITEXTURE2DRECT  */
    UTEXTURE2DRECT = 585,          /* UTEXTURE2DRECT  */
    TEXTUREBUFFER = 586,           /* TEXTUREBUFFER  */
    ITEXTUREBUFFER = 587,          /* ITEXTUREBUFFER  */
    UTEXTUREBUFFER = 588,          /* UTEXTUREBUFFER  */
    TEXTURE2DMS = 589,             /* TEXTURE2DMS  */
    ITEXTURE2DMS = 590,            /* ITEXTURE2DMS  */
    UTEXTURE2DMS = 591,            /* UTEXTURE2DMS  */
    TEXTURE2DMSARRAY = 592,        /* TEXTURE2DMSARRAY  */
    ITEXTURE2DMSARRAY = 593,       /* ITEXTURE2DMSARRAY  */
    UTEXTURE2DMSARRAY = 594,       /* UTEXTURE2DMSARRAY  */
    F16TEXTURE1D = 595,            /* F16TEXTURE1D  */
    F16TEXTURE2D = 596,            /* F16TEXTURE2D  */
    F16TEXTURE3D = 597,            /* F16TEXTURE3D  */
    F16TEXTURE2DRECT = 598,        /* F16TEXTURE2DRECT  */
    F16TEXTURECUBE = 599,          /* F16TEXTURECUBE  */
    F16TEXTURE1DARRAY = 600,       /* F16TEXTURE1DARRAY  */
    F16TEXTURE2DARRAY = 601,       /* F16TEXTURE2DARRAY  */
    F16TEXTURECUBEARRAY = 602,     /* F16TEXTURECUBEARRAY  */
    F16TEXTUREBUFFER = 603,        /* F16TEXTUREBUFFER  */
    F16TEXTURE2DMS = 604,          /* F16TEXTURE2DMS  */
    F16TEXTURE2DMSARRAY = 605,     /* F16TEXTURE2DMSARRAY  */
    SUBPASSINPUT = 606,            /* SUBPASSINPUT  */
    SUBPASSINPUTMS = 607,          /* SUBPASSINPUTMS  */
    ISUBPASSINPUT = 608,           /* ISUBPASSINPUT  */
    ISUBPASSINPUTMS = 609,         /* ISUBPASSINPUTMS  */
    USUBPASSINPUT = 610,           /* USUBPASSINPUT  */
    USUBPASSINPUTMS = 611,         /* USUBPASSINPUTMS  */
    F16SUBPASSINPUT = 612,         /* F16SUBPASSINPUT  */
    F16SUBPASSINPUTMS = 613,       /* F16SUBPASSINPUTMS  */
    SPIRV_INSTRUCTION = 614,       /* SPIRV_INSTRUCTION  */
    SPIRV_EXECUTION_MODE = 615,    /* SPIRV_EXECUTION_MODE  */
    SPIRV_EXECUTION_MODE_ID = 616, /* SPIRV_EXECUTION_MODE_ID  */
    SPIRV_DECORATE = 617,          /* SPIRV_DECORATE  */
    SPIRV_DECORATE_ID = 618,       /* SPIRV_DECORATE_ID  */
    SPIRV_DECORATE_STRING = 619,   /* SPIRV_DECORATE_STRING  */
    SPIRV_TYPE = 620,              /* SPIRV_TYPE  */
    SPIRV_STORAGE_CLASS = 621,     /* SPIRV_STORAGE_CLASS  */
    SPIRV_BY_REFERENCE = 622,      /* SPIRV_BY_REFERENCE  */
    SPIRV_LITERAL = 623,           /* SPIRV_LITERAL  */
    ATTACHMENTEXT = 624,           /* ATTACHMENTEXT  */
    IATTACHMENTEXT = 625,          /* IATTACHMENTEXT  */
    UATTACHMENTEXT = 626,          /* UATTACHMENTEXT  */
    LEFT_OP = 627,                 /* LEFT_OP  */
    RIGHT_OP = 628,                /* RIGHT_OP  */
    INC_OP = 629,                  /* INC_OP  */
    DEC_OP = 630,                  /* DEC_OP  */
    LE_OP = 631,                   /* LE_OP  */
    GE_OP = 632,                   /* GE_OP  */
    EQ_OP = 633,                   /* EQ_OP  */
    NE_OP = 634,                   /* NE_OP  */
    AND_OP = 635,                  /* AND_OP  */
    OR_OP = 636,                   /* OR_OP  */
    XOR_OP = 637,                  /* XOR_OP  */
    MUL_ASSIGN = 638,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 639,              /* DIV_ASSIGN  */
    ADD_ASSIGN = 640,              /* ADD_ASSIGN  */
    MOD_ASSIGN = 641,              /* MOD_ASSIGN  */
    LEFT_ASSIGN = 642,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 643,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 644,              /* AND_ASSIGN  */
    XOR_ASSIGN = 645,              /* XOR_ASSIGN  */
    OR_ASSIGN = 646,               /* OR_ASSIGN  */
    SUB_ASSIGN = 647,              /* SUB_ASSIGN  */
    STRING_LITERAL = 648,          /* STRING_LITERAL  */
    LEFT_PAREN = 649,              /* LEFT_PAREN  */
    RIGHT_PAREN = 650,             /* RIGHT_PAREN  */
    LEFT_BRACKET = 651,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 652,           /* RIGHT_BRACKET  */
    LEFT_BRACE = 653,              /* LEFT_BRACE  */
    RIGHT_BRACE = 654,             /* RIGHT_BRACE  */
    DOT = 655,                     /* DOT  */
    COMMA = 656,                   /* COMMA  */
    COLON = 657,                   /* COLON  */
    EQUAL = 658,                   /* EQUAL  */
    SEMICOLON = 659,               /* SEMICOLON  */
    BANG = 660,                    /* BANG  */
    DASH = 661,                    /* DASH  */
    TILDE = 662,                   /* TILDE  */
    PLUS = 663,                    /* PLUS  */
    STAR = 664,                    /* STAR  */
    SLASH = 665,                   /* SLASH  */
    PERCENT = 666,                 /* PERCENT  */
    LEFT_ANGLE = 667,              /* LEFT_ANGLE  */
    RIGHT_ANGLE = 668,             /* RIGHT_ANGLE  */
    VERTICAL_BAR = 669,            /* VERTICAL_BAR  */
    CARET = 670,                   /* CARET  */
    AMPERSAND = 671,               /* AMPERSAND  */
    QUESTION = 672,                /* QUESTION  */
    INVARIANT = 673,               /* INVARIANT  */
    HIGH_PRECISION = 674,          /* HIGH_PRECISION  */
    MEDIUM_PRECISION = 675,        /* MEDIUM_PRECISION  */
    LOW_PRECISION = 676,           /* LOW_PRECISION  */
    PRECISION = 677,               /* PRECISION  */
    PACKED = 678,                  /* PACKED  */
    RESOURCE = 679,                /* RESOURCE  */
    SUPERP = 680,                  /* SUPERP  */
    INLINE = 681,                  /* INLINE  */
    NOINLINE = 682,                /* NOINLINE  */
    FLOATCONSTANT = 683,           /* FLOATCONSTANT  */
    INTCONSTANT = 684,             /* INTCONSTANT  */
    UINTCONSTANT = 685,            /* UINTCONSTANT  */
    BOOLCONSTANT = 686,            /* BOOLCONSTANT  */
    IDENTIFIER = 687,              /* IDENTIFIER  */
    TYPE_NAME = 688,               /* TYPE_NAME  */
    CENTROID = 689,                /* CENTROID  */
    IN = 690,                      /* IN  */
    OUT = 691,                     /* OUT  */
    INOUT = 692,                   /* INOUT  */
    STRUCT = 693,                  /* STRUCT  */
    VOID = 694,                    /* VOID  */
    WHILE = 695,                   /* WHILE  */
    BREAK = 696,                   /* BREAK  */
    CONTINUE = 697,                /* CONTINUE  */
    DO = 698,                      /* DO  */
    ELSE = 699,                    /* ELSE  */
    FOR = 700,                     /* FOR  */
    IF = 701,                      /* IF  */
    DISCARD = 702,                 /* DISCARD  */
    RETURN = 703,                  /* RETURN  */
    SWITCH = 704,                  /* SWITCH  */
    CASE = 705,                    /* CASE  */
    DEFAULT = 706,                 /* DEFAULT  */
    TERMINATE_INVOCATION = 707,    /* TERMINATE_INVOCATION  */
    TERMINATE_RAY = 708,           /* TERMINATE_RAY  */
    IGNORE_INTERSECTION = 709,     /* IGNORE_INTERSECTION  */
    UNIFORM = 710,                 /* UNIFORM  */
    SHARED = 711,                  /* SHARED  */
    BUFFER = 712,                  /* BUFFER  */
    TILEIMAGEEXT = 713,            /* TILEIMAGEEXT  */
    FLAT = 714,                    /* FLAT  */
    SMOOTH = 715,                  /* SMOOTH  */
    LAYOUT = 716,                  /* LAYOUT  */
    DOUBLECONSTANT = 717,          /* DOUBLECONSTANT  */
    INT16CONSTANT = 718,           /* INT16CONSTANT  */
    UINT16CONSTANT = 719,          /* UINT16CONSTANT  */
    FLOAT16CONSTANT = 720,         /* FLOAT16CONSTANT  */
    INT32CONSTANT = 721,           /* INT32CONSTANT  */
    UINT32CONSTANT = 722,          /* UINT32CONSTANT  */
    FLOATE2M1CONSTANT = 723,       /* FLOATE2M1CONSTANT  */
    FLOATE3M2CONSTANT = 724,       /* FLOATE3M2CONSTANT  */
    FLOATE2M3CONSTANT = 725,       /* FLOATE2M3CONSTANT  */
    FLOATUE8M0CONSTANT = 726,      /* FLOATUE8M0CONSTANT  */
    FLOATMXINT8CONSTANT = 727,     /* FLOATMXINT8CONSTANT  */
    INT64CONSTANT = 728,           /* INT64CONSTANT  */
    UINT64CONSTANT = 729,          /* UINT64CONSTANT  */
    SUBROUTINE = 730,              /* SUBROUTINE  */
    DEMOTE = 731,                  /* DEMOTE  */
    FUNCTION = 732,                /* FUNCTION  */
    PAYLOADNV = 733,               /* PAYLOADNV  */
    PAYLOADINNV = 734,             /* PAYLOADINNV  */
    HITATTRNV = 735,               /* HITATTRNV  */
    CALLDATANV = 736,              /* CALLDATANV  */
    CALLDATAINNV = 737,            /* CALLDATAINNV  */
    PAYLOADEXT = 738,              /* PAYLOADEXT  */
    PAYLOADINEXT = 739,            /* PAYLOADINEXT  */
    HITATTREXT = 740,              /* HITATTREXT  */
    CALLDATAEXT = 741,             /* CALLDATAEXT  */
    CALLDATAINEXT = 742,           /* CALLDATAINEXT  */
    PATCH = 743,                   /* PATCH  */
    SAMPLE = 744,                  /* SAMPLE  */
    NONUNIFORM = 745,              /* NONUNIFORM  */
    RESOURCEHEAP = 746,            /* RESOURCEHEAP  */
    SAMPLERHEAP = 747,             /* SAMPLERHEAP  */
    COHERENT = 748,                /* COHERENT  */
    VOLATILE = 749,                /* VOLATILE  */
    RESTRICT = 750,                /* RESTRICT  */
    READONLY = 751,                /* READONLY  */
    WRITEONLY = 752,               /* WRITEONLY  */
    NONTEMPORAL = 753,             /* NONTEMPORAL  */
    DEVICECOHERENT = 754,          /* DEVICECOHERENT  */
    QUEUEFAMILYCOHERENT = 755,     /* QUEUEFAMILYCOHERENT  */
    WORKGROUPCOHERENT = 756,       /* WORKGROUPCOHERENT  */
    SUBGROUPCOHERENT = 757,        /* SUBGROUPCOHERENT  */
    NONPRIVATE = 758,              /* NONPRIVATE  */
    SHADERCALLCOHERENT = 759,      /* SHADERCALLCOHERENT  */
    NOPERSPECTIVE = 760,           /* NOPERSPECTIVE  */
    EXPLICITINTERPAMD = 761,       /* EXPLICITINTERPAMD  */
    PERVERTEXEXT = 762,            /* PERVERTEXEXT  */
    PERVERTEXNV = 763,             /* PERVERTEXNV  */
    PERPRIMITIVENV = 764,          /* PERPRIMITIVENV  */
    PERVIEWNV = 765,               /* PERVIEWNV  */
    PERTASKNV = 766,               /* PERTASKNV  */
    PERPRIMITIVEEXT = 767,         /* PERPRIMITIVEEXT  */
    TASKPAYLOADWORKGROUPEXT = 768, /* TASKPAYLOADWORKGROUPEXT  */
    PRECISE = 769                  /* PRECISE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "MachineIndependent/glslang.y"

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
            glslang::TSpirvRequirement* spirvReq;
            glslang::TSpirvInstruction* spirvInst;
            glslang::TSpirvTypeParameters* spirvTypeParams;
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
        glslang::TTypeParameters* typeParameters;
    } interm;

#line 617 "MachineIndependent/glslang_tab.cpp.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (glslang::TParseContext* pParseContext);


#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

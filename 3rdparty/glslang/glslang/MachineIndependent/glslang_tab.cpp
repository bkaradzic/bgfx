/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 44 "MachineIndependent/glslang.y"


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
#include "attribute.h"

using namespace glslang;


#line 97 "MachineIndependent/glslang_tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "glslang_tab.cpp.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_BOOL = 4,                       /* BOOL  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_UINT = 6,                       /* UINT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_BVEC2 = 8,                      /* BVEC2  */
  YYSYMBOL_BVEC3 = 9,                      /* BVEC3  */
  YYSYMBOL_BVEC4 = 10,                     /* BVEC4  */
  YYSYMBOL_IVEC2 = 11,                     /* IVEC2  */
  YYSYMBOL_IVEC3 = 12,                     /* IVEC3  */
  YYSYMBOL_IVEC4 = 13,                     /* IVEC4  */
  YYSYMBOL_UVEC2 = 14,                     /* UVEC2  */
  YYSYMBOL_UVEC3 = 15,                     /* UVEC3  */
  YYSYMBOL_UVEC4 = 16,                     /* UVEC4  */
  YYSYMBOL_VEC2 = 17,                      /* VEC2  */
  YYSYMBOL_VEC3 = 18,                      /* VEC3  */
  YYSYMBOL_VEC4 = 19,                      /* VEC4  */
  YYSYMBOL_MAT2 = 20,                      /* MAT2  */
  YYSYMBOL_MAT3 = 21,                      /* MAT3  */
  YYSYMBOL_MAT4 = 22,                      /* MAT4  */
  YYSYMBOL_MAT2X2 = 23,                    /* MAT2X2  */
  YYSYMBOL_MAT2X3 = 24,                    /* MAT2X3  */
  YYSYMBOL_MAT2X4 = 25,                    /* MAT2X4  */
  YYSYMBOL_MAT3X2 = 26,                    /* MAT3X2  */
  YYSYMBOL_MAT3X3 = 27,                    /* MAT3X3  */
  YYSYMBOL_MAT3X4 = 28,                    /* MAT3X4  */
  YYSYMBOL_MAT4X2 = 29,                    /* MAT4X2  */
  YYSYMBOL_MAT4X3 = 30,                    /* MAT4X3  */
  YYSYMBOL_MAT4X4 = 31,                    /* MAT4X4  */
  YYSYMBOL_SAMPLER2D = 32,                 /* SAMPLER2D  */
  YYSYMBOL_SAMPLER3D = 33,                 /* SAMPLER3D  */
  YYSYMBOL_SAMPLERCUBE = 34,               /* SAMPLERCUBE  */
  YYSYMBOL_SAMPLER2DSHADOW = 35,           /* SAMPLER2DSHADOW  */
  YYSYMBOL_SAMPLERCUBESHADOW = 36,         /* SAMPLERCUBESHADOW  */
  YYSYMBOL_SAMPLER2DARRAY = 37,            /* SAMPLER2DARRAY  */
  YYSYMBOL_SAMPLER2DARRAYSHADOW = 38,      /* SAMPLER2DARRAYSHADOW  */
  YYSYMBOL_ISAMPLER2D = 39,                /* ISAMPLER2D  */
  YYSYMBOL_ISAMPLER3D = 40,                /* ISAMPLER3D  */
  YYSYMBOL_ISAMPLERCUBE = 41,              /* ISAMPLERCUBE  */
  YYSYMBOL_ISAMPLER2DARRAY = 42,           /* ISAMPLER2DARRAY  */
  YYSYMBOL_USAMPLER2D = 43,                /* USAMPLER2D  */
  YYSYMBOL_USAMPLER3D = 44,                /* USAMPLER3D  */
  YYSYMBOL_USAMPLERCUBE = 45,              /* USAMPLERCUBE  */
  YYSYMBOL_USAMPLER2DARRAY = 46,           /* USAMPLER2DARRAY  */
  YYSYMBOL_SAMPLER = 47,                   /* SAMPLER  */
  YYSYMBOL_SAMPLERSHADOW = 48,             /* SAMPLERSHADOW  */
  YYSYMBOL_TEXTURE2D = 49,                 /* TEXTURE2D  */
  YYSYMBOL_TEXTURE3D = 50,                 /* TEXTURE3D  */
  YYSYMBOL_TEXTURECUBE = 51,               /* TEXTURECUBE  */
  YYSYMBOL_TEXTURE2DARRAY = 52,            /* TEXTURE2DARRAY  */
  YYSYMBOL_ITEXTURE2D = 53,                /* ITEXTURE2D  */
  YYSYMBOL_ITEXTURE3D = 54,                /* ITEXTURE3D  */
  YYSYMBOL_ITEXTURECUBE = 55,              /* ITEXTURECUBE  */
  YYSYMBOL_ITEXTURE2DARRAY = 56,           /* ITEXTURE2DARRAY  */
  YYSYMBOL_UTEXTURE2D = 57,                /* UTEXTURE2D  */
  YYSYMBOL_UTEXTURE3D = 58,                /* UTEXTURE3D  */
  YYSYMBOL_UTEXTURECUBE = 59,              /* UTEXTURECUBE  */
  YYSYMBOL_UTEXTURE2DARRAY = 60,           /* UTEXTURE2DARRAY  */
  YYSYMBOL_ATTRIBUTE = 61,                 /* ATTRIBUTE  */
  YYSYMBOL_VARYING = 62,                   /* VARYING  */
  YYSYMBOL_FLOATE5M2_T = 63,               /* FLOATE5M2_T  */
  YYSYMBOL_FLOATE4M3_T = 64,               /* FLOATE4M3_T  */
  YYSYMBOL_BFLOAT16_T = 65,                /* BFLOAT16_T  */
  YYSYMBOL_FLOAT16_T = 66,                 /* FLOAT16_T  */
  YYSYMBOL_FLOAT32_T = 67,                 /* FLOAT32_T  */
  YYSYMBOL_DOUBLE = 68,                    /* DOUBLE  */
  YYSYMBOL_FLOAT64_T = 69,                 /* FLOAT64_T  */
  YYSYMBOL_FLOATE2M1_T = 70,               /* FLOATE2M1_T  */
  YYSYMBOL_FLOATE3M2_T = 71,               /* FLOATE3M2_T  */
  YYSYMBOL_FLOATE2M3_T = 72,               /* FLOATE2M3_T  */
  YYSYMBOL_FLOATUE8M0_T = 73,              /* FLOATUE8M0_T  */
  YYSYMBOL_FLOATMXINT8_T = 74,             /* FLOATMXINT8_T  */
  YYSYMBOL_INT64_T = 75,                   /* INT64_T  */
  YYSYMBOL_UINT64_T = 76,                  /* UINT64_T  */
  YYSYMBOL_INT32_T = 77,                   /* INT32_T  */
  YYSYMBOL_UINT32_T = 78,                  /* UINT32_T  */
  YYSYMBOL_INT16_T = 79,                   /* INT16_T  */
  YYSYMBOL_UINT16_T = 80,                  /* UINT16_T  */
  YYSYMBOL_INT8_T = 81,                    /* INT8_T  */
  YYSYMBOL_UINT8_T = 82,                   /* UINT8_T  */
  YYSYMBOL_I64VEC2 = 83,                   /* I64VEC2  */
  YYSYMBOL_I64VEC3 = 84,                   /* I64VEC3  */
  YYSYMBOL_I64VEC4 = 85,                   /* I64VEC4  */
  YYSYMBOL_U64VEC2 = 86,                   /* U64VEC2  */
  YYSYMBOL_U64VEC3 = 87,                   /* U64VEC3  */
  YYSYMBOL_U64VEC4 = 88,                   /* U64VEC4  */
  YYSYMBOL_I32VEC2 = 89,                   /* I32VEC2  */
  YYSYMBOL_I32VEC3 = 90,                   /* I32VEC3  */
  YYSYMBOL_I32VEC4 = 91,                   /* I32VEC4  */
  YYSYMBOL_U32VEC2 = 92,                   /* U32VEC2  */
  YYSYMBOL_U32VEC3 = 93,                   /* U32VEC3  */
  YYSYMBOL_U32VEC4 = 94,                   /* U32VEC4  */
  YYSYMBOL_I16VEC2 = 95,                   /* I16VEC2  */
  YYSYMBOL_I16VEC3 = 96,                   /* I16VEC3  */
  YYSYMBOL_I16VEC4 = 97,                   /* I16VEC4  */
  YYSYMBOL_U16VEC2 = 98,                   /* U16VEC2  */
  YYSYMBOL_U16VEC3 = 99,                   /* U16VEC3  */
  YYSYMBOL_U16VEC4 = 100,                  /* U16VEC4  */
  YYSYMBOL_I8VEC2 = 101,                   /* I8VEC2  */
  YYSYMBOL_I8VEC3 = 102,                   /* I8VEC3  */
  YYSYMBOL_I8VEC4 = 103,                   /* I8VEC4  */
  YYSYMBOL_U8VEC2 = 104,                   /* U8VEC2  */
  YYSYMBOL_U8VEC3 = 105,                   /* U8VEC3  */
  YYSYMBOL_U8VEC4 = 106,                   /* U8VEC4  */
  YYSYMBOL_DVEC2 = 107,                    /* DVEC2  */
  YYSYMBOL_DVEC3 = 108,                    /* DVEC3  */
  YYSYMBOL_DVEC4 = 109,                    /* DVEC4  */
  YYSYMBOL_DMAT2 = 110,                    /* DMAT2  */
  YYSYMBOL_DMAT3 = 111,                    /* DMAT3  */
  YYSYMBOL_DMAT4 = 112,                    /* DMAT4  */
  YYSYMBOL_BF16VEC2 = 113,                 /* BF16VEC2  */
  YYSYMBOL_BF16VEC3 = 114,                 /* BF16VEC3  */
  YYSYMBOL_BF16VEC4 = 115,                 /* BF16VEC4  */
  YYSYMBOL_FE5M2VEC2 = 116,                /* FE5M2VEC2  */
  YYSYMBOL_FE5M2VEC3 = 117,                /* FE5M2VEC3  */
  YYSYMBOL_FE5M2VEC4 = 118,                /* FE5M2VEC4  */
  YYSYMBOL_FE4M3VEC2 = 119,                /* FE4M3VEC2  */
  YYSYMBOL_FE4M3VEC3 = 120,                /* FE4M3VEC3  */
  YYSYMBOL_FE4M3VEC4 = 121,                /* FE4M3VEC4  */
  YYSYMBOL_FE2M1VEC2 = 122,                /* FE2M1VEC2  */
  YYSYMBOL_FE2M1VEC3 = 123,                /* FE2M1VEC3  */
  YYSYMBOL_FE2M1VEC4 = 124,                /* FE2M1VEC4  */
  YYSYMBOL_FE3M2VEC2 = 125,                /* FE3M2VEC2  */
  YYSYMBOL_FE3M2VEC3 = 126,                /* FE3M2VEC3  */
  YYSYMBOL_FE3M2VEC4 = 127,                /* FE3M2VEC4  */
  YYSYMBOL_FE2M3VEC2 = 128,                /* FE2M3VEC2  */
  YYSYMBOL_FE2M3VEC3 = 129,                /* FE2M3VEC3  */
  YYSYMBOL_FE2M3VEC4 = 130,                /* FE2M3VEC4  */
  YYSYMBOL_FUE8M0VEC2 = 131,               /* FUE8M0VEC2  */
  YYSYMBOL_FUE8M0VEC3 = 132,               /* FUE8M0VEC3  */
  YYSYMBOL_FUE8M0VEC4 = 133,               /* FUE8M0VEC4  */
  YYSYMBOL_FMXINT8VEC2 = 134,              /* FMXINT8VEC2  */
  YYSYMBOL_FMXINT8VEC3 = 135,              /* FMXINT8VEC3  */
  YYSYMBOL_FMXINT8VEC4 = 136,              /* FMXINT8VEC4  */
  YYSYMBOL_F16VEC2 = 137,                  /* F16VEC2  */
  YYSYMBOL_F16VEC3 = 138,                  /* F16VEC3  */
  YYSYMBOL_F16VEC4 = 139,                  /* F16VEC4  */
  YYSYMBOL_F16MAT2 = 140,                  /* F16MAT2  */
  YYSYMBOL_F16MAT3 = 141,                  /* F16MAT3  */
  YYSYMBOL_F16MAT4 = 142,                  /* F16MAT4  */
  YYSYMBOL_F32VEC2 = 143,                  /* F32VEC2  */
  YYSYMBOL_F32VEC3 = 144,                  /* F32VEC3  */
  YYSYMBOL_F32VEC4 = 145,                  /* F32VEC4  */
  YYSYMBOL_F32MAT2 = 146,                  /* F32MAT2  */
  YYSYMBOL_F32MAT3 = 147,                  /* F32MAT3  */
  YYSYMBOL_F32MAT4 = 148,                  /* F32MAT4  */
  YYSYMBOL_F64VEC2 = 149,                  /* F64VEC2  */
  YYSYMBOL_F64VEC3 = 150,                  /* F64VEC3  */
  YYSYMBOL_F64VEC4 = 151,                  /* F64VEC4  */
  YYSYMBOL_F64MAT2 = 152,                  /* F64MAT2  */
  YYSYMBOL_F64MAT3 = 153,                  /* F64MAT3  */
  YYSYMBOL_F64MAT4 = 154,                  /* F64MAT4  */
  YYSYMBOL_DMAT2X2 = 155,                  /* DMAT2X2  */
  YYSYMBOL_DMAT2X3 = 156,                  /* DMAT2X3  */
  YYSYMBOL_DMAT2X4 = 157,                  /* DMAT2X4  */
  YYSYMBOL_DMAT3X2 = 158,                  /* DMAT3X2  */
  YYSYMBOL_DMAT3X3 = 159,                  /* DMAT3X3  */
  YYSYMBOL_DMAT3X4 = 160,                  /* DMAT3X4  */
  YYSYMBOL_DMAT4X2 = 161,                  /* DMAT4X2  */
  YYSYMBOL_DMAT4X3 = 162,                  /* DMAT4X3  */
  YYSYMBOL_DMAT4X4 = 163,                  /* DMAT4X4  */
  YYSYMBOL_F16MAT2X2 = 164,                /* F16MAT2X2  */
  YYSYMBOL_F16MAT2X3 = 165,                /* F16MAT2X3  */
  YYSYMBOL_F16MAT2X4 = 166,                /* F16MAT2X4  */
  YYSYMBOL_F16MAT3X2 = 167,                /* F16MAT3X2  */
  YYSYMBOL_F16MAT3X3 = 168,                /* F16MAT3X3  */
  YYSYMBOL_F16MAT3X4 = 169,                /* F16MAT3X4  */
  YYSYMBOL_F16MAT4X2 = 170,                /* F16MAT4X2  */
  YYSYMBOL_F16MAT4X3 = 171,                /* F16MAT4X3  */
  YYSYMBOL_F16MAT4X4 = 172,                /* F16MAT4X4  */
  YYSYMBOL_F32MAT2X2 = 173,                /* F32MAT2X2  */
  YYSYMBOL_F32MAT2X3 = 174,                /* F32MAT2X3  */
  YYSYMBOL_F32MAT2X4 = 175,                /* F32MAT2X4  */
  YYSYMBOL_F32MAT3X2 = 176,                /* F32MAT3X2  */
  YYSYMBOL_F32MAT3X3 = 177,                /* F32MAT3X3  */
  YYSYMBOL_F32MAT3X4 = 178,                /* F32MAT3X4  */
  YYSYMBOL_F32MAT4X2 = 179,                /* F32MAT4X2  */
  YYSYMBOL_F32MAT4X3 = 180,                /* F32MAT4X3  */
  YYSYMBOL_F32MAT4X4 = 181,                /* F32MAT4X4  */
  YYSYMBOL_F64MAT2X2 = 182,                /* F64MAT2X2  */
  YYSYMBOL_F64MAT2X3 = 183,                /* F64MAT2X3  */
  YYSYMBOL_F64MAT2X4 = 184,                /* F64MAT2X4  */
  YYSYMBOL_F64MAT3X2 = 185,                /* F64MAT3X2  */
  YYSYMBOL_F64MAT3X3 = 186,                /* F64MAT3X3  */
  YYSYMBOL_F64MAT3X4 = 187,                /* F64MAT3X4  */
  YYSYMBOL_F64MAT4X2 = 188,                /* F64MAT4X2  */
  YYSYMBOL_F64MAT4X3 = 189,                /* F64MAT4X3  */
  YYSYMBOL_F64MAT4X4 = 190,                /* F64MAT4X4  */
  YYSYMBOL_ATOMIC_UINT = 191,              /* ATOMIC_UINT  */
  YYSYMBOL_ACCSTRUCTNV = 192,              /* ACCSTRUCTNV  */
  YYSYMBOL_ACCSTRUCTEXT = 193,             /* ACCSTRUCTEXT  */
  YYSYMBOL_RAYQUERYEXT = 194,              /* RAYQUERYEXT  */
  YYSYMBOL_FCOOPMATNV = 195,               /* FCOOPMATNV  */
  YYSYMBOL_ICOOPMATNV = 196,               /* ICOOPMATNV  */
  YYSYMBOL_UCOOPMATNV = 197,               /* UCOOPMATNV  */
  YYSYMBOL_COOPMAT = 198,                  /* COOPMAT  */
  YYSYMBOL_COOPVECNV = 199,                /* COOPVECNV  */
  YYSYMBOL_VECTOR = 200,                   /* VECTOR  */
  YYSYMBOL_HITOBJECTNV = 201,              /* HITOBJECTNV  */
  YYSYMBOL_HITOBJECTATTRNV = 202,          /* HITOBJECTATTRNV  */
  YYSYMBOL_HITOBJECTEXT = 203,             /* HITOBJECTEXT  */
  YYSYMBOL_HITOBJECTATTREXT = 204,         /* HITOBJECTATTREXT  */
  YYSYMBOL_TENSORLAYOUTNV = 205,           /* TENSORLAYOUTNV  */
  YYSYMBOL_TENSORVIEWNV = 206,             /* TENSORVIEWNV  */
  YYSYMBOL_TENSORARM = 207,                /* TENSORARM  */
  YYSYMBOL_SAMPLERCUBEARRAY = 208,         /* SAMPLERCUBEARRAY  */
  YYSYMBOL_SAMPLERCUBEARRAYSHADOW = 209,   /* SAMPLERCUBEARRAYSHADOW  */
  YYSYMBOL_ISAMPLERCUBEARRAY = 210,        /* ISAMPLERCUBEARRAY  */
  YYSYMBOL_USAMPLERCUBEARRAY = 211,        /* USAMPLERCUBEARRAY  */
  YYSYMBOL_SAMPLER1D = 212,                /* SAMPLER1D  */
  YYSYMBOL_SAMPLER1DARRAY = 213,           /* SAMPLER1DARRAY  */
  YYSYMBOL_SAMPLER1DARRAYSHADOW = 214,     /* SAMPLER1DARRAYSHADOW  */
  YYSYMBOL_ISAMPLER1D = 215,               /* ISAMPLER1D  */
  YYSYMBOL_SAMPLER1DSHADOW = 216,          /* SAMPLER1DSHADOW  */
  YYSYMBOL_SAMPLER2DRECT = 217,            /* SAMPLER2DRECT  */
  YYSYMBOL_SAMPLER2DRECTSHADOW = 218,      /* SAMPLER2DRECTSHADOW  */
  YYSYMBOL_ISAMPLER2DRECT = 219,           /* ISAMPLER2DRECT  */
  YYSYMBOL_USAMPLER2DRECT = 220,           /* USAMPLER2DRECT  */
  YYSYMBOL_SAMPLERBUFFER = 221,            /* SAMPLERBUFFER  */
  YYSYMBOL_ISAMPLERBUFFER = 222,           /* ISAMPLERBUFFER  */
  YYSYMBOL_USAMPLERBUFFER = 223,           /* USAMPLERBUFFER  */
  YYSYMBOL_SAMPLER2DMS = 224,              /* SAMPLER2DMS  */
  YYSYMBOL_ISAMPLER2DMS = 225,             /* ISAMPLER2DMS  */
  YYSYMBOL_USAMPLER2DMS = 226,             /* USAMPLER2DMS  */
  YYSYMBOL_SAMPLER2DMSARRAY = 227,         /* SAMPLER2DMSARRAY  */
  YYSYMBOL_ISAMPLER2DMSARRAY = 228,        /* ISAMPLER2DMSARRAY  */
  YYSYMBOL_USAMPLER2DMSARRAY = 229,        /* USAMPLER2DMSARRAY  */
  YYSYMBOL_SAMPLEREXTERNALOES = 230,       /* SAMPLEREXTERNALOES  */
  YYSYMBOL_SAMPLEREXTERNAL2DY2YEXT = 231,  /* SAMPLEREXTERNAL2DY2YEXT  */
  YYSYMBOL_ISAMPLER1DARRAY = 232,          /* ISAMPLER1DARRAY  */
  YYSYMBOL_USAMPLER1D = 233,               /* USAMPLER1D  */
  YYSYMBOL_USAMPLER1DARRAY = 234,          /* USAMPLER1DARRAY  */
  YYSYMBOL_F16SAMPLER1D = 235,             /* F16SAMPLER1D  */
  YYSYMBOL_F16SAMPLER2D = 236,             /* F16SAMPLER2D  */
  YYSYMBOL_F16SAMPLER3D = 237,             /* F16SAMPLER3D  */
  YYSYMBOL_F16SAMPLER2DRECT = 238,         /* F16SAMPLER2DRECT  */
  YYSYMBOL_F16SAMPLERCUBE = 239,           /* F16SAMPLERCUBE  */
  YYSYMBOL_F16SAMPLER1DARRAY = 240,        /* F16SAMPLER1DARRAY  */
  YYSYMBOL_F16SAMPLER2DARRAY = 241,        /* F16SAMPLER2DARRAY  */
  YYSYMBOL_F16SAMPLERCUBEARRAY = 242,      /* F16SAMPLERCUBEARRAY  */
  YYSYMBOL_F16SAMPLERBUFFER = 243,         /* F16SAMPLERBUFFER  */
  YYSYMBOL_F16SAMPLER2DMS = 244,           /* F16SAMPLER2DMS  */
  YYSYMBOL_F16SAMPLER2DMSARRAY = 245,      /* F16SAMPLER2DMSARRAY  */
  YYSYMBOL_F16SAMPLER1DSHADOW = 246,       /* F16SAMPLER1DSHADOW  */
  YYSYMBOL_F16SAMPLER2DSHADOW = 247,       /* F16SAMPLER2DSHADOW  */
  YYSYMBOL_F16SAMPLER1DARRAYSHADOW = 248,  /* F16SAMPLER1DARRAYSHADOW  */
  YYSYMBOL_F16SAMPLER2DARRAYSHADOW = 249,  /* F16SAMPLER2DARRAYSHADOW  */
  YYSYMBOL_F16SAMPLER2DRECTSHADOW = 250,   /* F16SAMPLER2DRECTSHADOW  */
  YYSYMBOL_F16SAMPLERCUBESHADOW = 251,     /* F16SAMPLERCUBESHADOW  */
  YYSYMBOL_F16SAMPLERCUBEARRAYSHADOW = 252, /* F16SAMPLERCUBEARRAYSHADOW  */
  YYSYMBOL_IMAGE1D = 253,                  /* IMAGE1D  */
  YYSYMBOL_IIMAGE1D = 254,                 /* IIMAGE1D  */
  YYSYMBOL_UIMAGE1D = 255,                 /* UIMAGE1D  */
  YYSYMBOL_IMAGE2D = 256,                  /* IMAGE2D  */
  YYSYMBOL_IIMAGE2D = 257,                 /* IIMAGE2D  */
  YYSYMBOL_UIMAGE2D = 258,                 /* UIMAGE2D  */
  YYSYMBOL_IMAGE3D = 259,                  /* IMAGE3D  */
  YYSYMBOL_IIMAGE3D = 260,                 /* IIMAGE3D  */
  YYSYMBOL_UIMAGE3D = 261,                 /* UIMAGE3D  */
  YYSYMBOL_IMAGE2DRECT = 262,              /* IMAGE2DRECT  */
  YYSYMBOL_IIMAGE2DRECT = 263,             /* IIMAGE2DRECT  */
  YYSYMBOL_UIMAGE2DRECT = 264,             /* UIMAGE2DRECT  */
  YYSYMBOL_IMAGECUBE = 265,                /* IMAGECUBE  */
  YYSYMBOL_IIMAGECUBE = 266,               /* IIMAGECUBE  */
  YYSYMBOL_UIMAGECUBE = 267,               /* UIMAGECUBE  */
  YYSYMBOL_IMAGEBUFFER = 268,              /* IMAGEBUFFER  */
  YYSYMBOL_IIMAGEBUFFER = 269,             /* IIMAGEBUFFER  */
  YYSYMBOL_UIMAGEBUFFER = 270,             /* UIMAGEBUFFER  */
  YYSYMBOL_IMAGE1DARRAY = 271,             /* IMAGE1DARRAY  */
  YYSYMBOL_IIMAGE1DARRAY = 272,            /* IIMAGE1DARRAY  */
  YYSYMBOL_UIMAGE1DARRAY = 273,            /* UIMAGE1DARRAY  */
  YYSYMBOL_IMAGE2DARRAY = 274,             /* IMAGE2DARRAY  */
  YYSYMBOL_IIMAGE2DARRAY = 275,            /* IIMAGE2DARRAY  */
  YYSYMBOL_UIMAGE2DARRAY = 276,            /* UIMAGE2DARRAY  */
  YYSYMBOL_IMAGECUBEARRAY = 277,           /* IMAGECUBEARRAY  */
  YYSYMBOL_IIMAGECUBEARRAY = 278,          /* IIMAGECUBEARRAY  */
  YYSYMBOL_UIMAGECUBEARRAY = 279,          /* UIMAGECUBEARRAY  */
  YYSYMBOL_IMAGE2DMS = 280,                /* IMAGE2DMS  */
  YYSYMBOL_IIMAGE2DMS = 281,               /* IIMAGE2DMS  */
  YYSYMBOL_UIMAGE2DMS = 282,               /* UIMAGE2DMS  */
  YYSYMBOL_IMAGE2DMSARRAY = 283,           /* IMAGE2DMSARRAY  */
  YYSYMBOL_IIMAGE2DMSARRAY = 284,          /* IIMAGE2DMSARRAY  */
  YYSYMBOL_UIMAGE2DMSARRAY = 285,          /* UIMAGE2DMSARRAY  */
  YYSYMBOL_F16IMAGE1D = 286,               /* F16IMAGE1D  */
  YYSYMBOL_F16IMAGE2D = 287,               /* F16IMAGE2D  */
  YYSYMBOL_F16IMAGE3D = 288,               /* F16IMAGE3D  */
  YYSYMBOL_F16IMAGE2DRECT = 289,           /* F16IMAGE2DRECT  */
  YYSYMBOL_F16IMAGECUBE = 290,             /* F16IMAGECUBE  */
  YYSYMBOL_F16IMAGE1DARRAY = 291,          /* F16IMAGE1DARRAY  */
  YYSYMBOL_F16IMAGE2DARRAY = 292,          /* F16IMAGE2DARRAY  */
  YYSYMBOL_F16IMAGECUBEARRAY = 293,        /* F16IMAGECUBEARRAY  */
  YYSYMBOL_F16IMAGEBUFFER = 294,           /* F16IMAGEBUFFER  */
  YYSYMBOL_F16IMAGE2DMS = 295,             /* F16IMAGE2DMS  */
  YYSYMBOL_F16IMAGE2DMSARRAY = 296,        /* F16IMAGE2DMSARRAY  */
  YYSYMBOL_I64IMAGE1D = 297,               /* I64IMAGE1D  */
  YYSYMBOL_U64IMAGE1D = 298,               /* U64IMAGE1D  */
  YYSYMBOL_I64IMAGE2D = 299,               /* I64IMAGE2D  */
  YYSYMBOL_U64IMAGE2D = 300,               /* U64IMAGE2D  */
  YYSYMBOL_I64IMAGE3D = 301,               /* I64IMAGE3D  */
  YYSYMBOL_U64IMAGE3D = 302,               /* U64IMAGE3D  */
  YYSYMBOL_I64IMAGE2DRECT = 303,           /* I64IMAGE2DRECT  */
  YYSYMBOL_U64IMAGE2DRECT = 304,           /* U64IMAGE2DRECT  */
  YYSYMBOL_I64IMAGECUBE = 305,             /* I64IMAGECUBE  */
  YYSYMBOL_U64IMAGECUBE = 306,             /* U64IMAGECUBE  */
  YYSYMBOL_I64IMAGEBUFFER = 307,           /* I64IMAGEBUFFER  */
  YYSYMBOL_U64IMAGEBUFFER = 308,           /* U64IMAGEBUFFER  */
  YYSYMBOL_I64IMAGE1DARRAY = 309,          /* I64IMAGE1DARRAY  */
  YYSYMBOL_U64IMAGE1DARRAY = 310,          /* U64IMAGE1DARRAY  */
  YYSYMBOL_I64IMAGE2DARRAY = 311,          /* I64IMAGE2DARRAY  */
  YYSYMBOL_U64IMAGE2DARRAY = 312,          /* U64IMAGE2DARRAY  */
  YYSYMBOL_I64IMAGECUBEARRAY = 313,        /* I64IMAGECUBEARRAY  */
  YYSYMBOL_U64IMAGECUBEARRAY = 314,        /* U64IMAGECUBEARRAY  */
  YYSYMBOL_I64IMAGE2DMS = 315,             /* I64IMAGE2DMS  */
  YYSYMBOL_U64IMAGE2DMS = 316,             /* U64IMAGE2DMS  */
  YYSYMBOL_I64IMAGE2DMSARRAY = 317,        /* I64IMAGE2DMSARRAY  */
  YYSYMBOL_U64IMAGE2DMSARRAY = 318,        /* U64IMAGE2DMSARRAY  */
  YYSYMBOL_TEXTURECUBEARRAY = 319,         /* TEXTURECUBEARRAY  */
  YYSYMBOL_ITEXTURECUBEARRAY = 320,        /* ITEXTURECUBEARRAY  */
  YYSYMBOL_UTEXTURECUBEARRAY = 321,        /* UTEXTURECUBEARRAY  */
  YYSYMBOL_TEXTURE1D = 322,                /* TEXTURE1D  */
  YYSYMBOL_ITEXTURE1D = 323,               /* ITEXTURE1D  */
  YYSYMBOL_UTEXTURE1D = 324,               /* UTEXTURE1D  */
  YYSYMBOL_TEXTURE1DARRAY = 325,           /* TEXTURE1DARRAY  */
  YYSYMBOL_ITEXTURE1DARRAY = 326,          /* ITEXTURE1DARRAY  */
  YYSYMBOL_UTEXTURE1DARRAY = 327,          /* UTEXTURE1DARRAY  */
  YYSYMBOL_TEXTURE2DRECT = 328,            /* TEXTURE2DRECT  */
  YYSYMBOL_ITEXTURE2DRECT = 329,           /* ITEXTURE2DRECT  */
  YYSYMBOL_UTEXTURE2DRECT = 330,           /* UTEXTURE2DRECT  */
  YYSYMBOL_TEXTUREBUFFER = 331,            /* TEXTUREBUFFER  */
  YYSYMBOL_ITEXTUREBUFFER = 332,           /* ITEXTUREBUFFER  */
  YYSYMBOL_UTEXTUREBUFFER = 333,           /* UTEXTUREBUFFER  */
  YYSYMBOL_TEXTURE2DMS = 334,              /* TEXTURE2DMS  */
  YYSYMBOL_ITEXTURE2DMS = 335,             /* ITEXTURE2DMS  */
  YYSYMBOL_UTEXTURE2DMS = 336,             /* UTEXTURE2DMS  */
  YYSYMBOL_TEXTURE2DMSARRAY = 337,         /* TEXTURE2DMSARRAY  */
  YYSYMBOL_ITEXTURE2DMSARRAY = 338,        /* ITEXTURE2DMSARRAY  */
  YYSYMBOL_UTEXTURE2DMSARRAY = 339,        /* UTEXTURE2DMSARRAY  */
  YYSYMBOL_F16TEXTURE1D = 340,             /* F16TEXTURE1D  */
  YYSYMBOL_F16TEXTURE2D = 341,             /* F16TEXTURE2D  */
  YYSYMBOL_F16TEXTURE3D = 342,             /* F16TEXTURE3D  */
  YYSYMBOL_F16TEXTURE2DRECT = 343,         /* F16TEXTURE2DRECT  */
  YYSYMBOL_F16TEXTURECUBE = 344,           /* F16TEXTURECUBE  */
  YYSYMBOL_F16TEXTURE1DARRAY = 345,        /* F16TEXTURE1DARRAY  */
  YYSYMBOL_F16TEXTURE2DARRAY = 346,        /* F16TEXTURE2DARRAY  */
  YYSYMBOL_F16TEXTURECUBEARRAY = 347,      /* F16TEXTURECUBEARRAY  */
  YYSYMBOL_F16TEXTUREBUFFER = 348,         /* F16TEXTUREBUFFER  */
  YYSYMBOL_F16TEXTURE2DMS = 349,           /* F16TEXTURE2DMS  */
  YYSYMBOL_F16TEXTURE2DMSARRAY = 350,      /* F16TEXTURE2DMSARRAY  */
  YYSYMBOL_SUBPASSINPUT = 351,             /* SUBPASSINPUT  */
  YYSYMBOL_SUBPASSINPUTMS = 352,           /* SUBPASSINPUTMS  */
  YYSYMBOL_ISUBPASSINPUT = 353,            /* ISUBPASSINPUT  */
  YYSYMBOL_ISUBPASSINPUTMS = 354,          /* ISUBPASSINPUTMS  */
  YYSYMBOL_USUBPASSINPUT = 355,            /* USUBPASSINPUT  */
  YYSYMBOL_USUBPASSINPUTMS = 356,          /* USUBPASSINPUTMS  */
  YYSYMBOL_F16SUBPASSINPUT = 357,          /* F16SUBPASSINPUT  */
  YYSYMBOL_F16SUBPASSINPUTMS = 358,        /* F16SUBPASSINPUTMS  */
  YYSYMBOL_SPIRV_INSTRUCTION = 359,        /* SPIRV_INSTRUCTION  */
  YYSYMBOL_SPIRV_EXECUTION_MODE = 360,     /* SPIRV_EXECUTION_MODE  */
  YYSYMBOL_SPIRV_EXECUTION_MODE_ID = 361,  /* SPIRV_EXECUTION_MODE_ID  */
  YYSYMBOL_SPIRV_DECORATE = 362,           /* SPIRV_DECORATE  */
  YYSYMBOL_SPIRV_DECORATE_ID = 363,        /* SPIRV_DECORATE_ID  */
  YYSYMBOL_SPIRV_DECORATE_STRING = 364,    /* SPIRV_DECORATE_STRING  */
  YYSYMBOL_SPIRV_TYPE = 365,               /* SPIRV_TYPE  */
  YYSYMBOL_SPIRV_STORAGE_CLASS = 366,      /* SPIRV_STORAGE_CLASS  */
  YYSYMBOL_SPIRV_BY_REFERENCE = 367,       /* SPIRV_BY_REFERENCE  */
  YYSYMBOL_SPIRV_LITERAL = 368,            /* SPIRV_LITERAL  */
  YYSYMBOL_ATTACHMENTEXT = 369,            /* ATTACHMENTEXT  */
  YYSYMBOL_IATTACHMENTEXT = 370,           /* IATTACHMENTEXT  */
  YYSYMBOL_UATTACHMENTEXT = 371,           /* UATTACHMENTEXT  */
  YYSYMBOL_LEFT_OP = 372,                  /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 373,                 /* RIGHT_OP  */
  YYSYMBOL_INC_OP = 374,                   /* INC_OP  */
  YYSYMBOL_DEC_OP = 375,                   /* DEC_OP  */
  YYSYMBOL_LE_OP = 376,                    /* LE_OP  */
  YYSYMBOL_GE_OP = 377,                    /* GE_OP  */
  YYSYMBOL_EQ_OP = 378,                    /* EQ_OP  */
  YYSYMBOL_NE_OP = 379,                    /* NE_OP  */
  YYSYMBOL_AND_OP = 380,                   /* AND_OP  */
  YYSYMBOL_OR_OP = 381,                    /* OR_OP  */
  YYSYMBOL_XOR_OP = 382,                   /* XOR_OP  */
  YYSYMBOL_MUL_ASSIGN = 383,               /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 384,               /* DIV_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 385,               /* ADD_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 386,               /* MOD_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 387,              /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 388,             /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 389,               /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 390,               /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 391,                /* OR_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 392,               /* SUB_ASSIGN  */
  YYSYMBOL_STRING_LITERAL = 393,           /* STRING_LITERAL  */
  YYSYMBOL_LEFT_PAREN = 394,               /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 395,              /* RIGHT_PAREN  */
  YYSYMBOL_LEFT_BRACKET = 396,             /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 397,            /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_BRACE = 398,               /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 399,              /* RIGHT_BRACE  */
  YYSYMBOL_DOT = 400,                      /* DOT  */
  YYSYMBOL_COMMA = 401,                    /* COMMA  */
  YYSYMBOL_COLON = 402,                    /* COLON  */
  YYSYMBOL_EQUAL = 403,                    /* EQUAL  */
  YYSYMBOL_SEMICOLON = 404,                /* SEMICOLON  */
  YYSYMBOL_BANG = 405,                     /* BANG  */
  YYSYMBOL_DASH = 406,                     /* DASH  */
  YYSYMBOL_TILDE = 407,                    /* TILDE  */
  YYSYMBOL_PLUS = 408,                     /* PLUS  */
  YYSYMBOL_STAR = 409,                     /* STAR  */
  YYSYMBOL_SLASH = 410,                    /* SLASH  */
  YYSYMBOL_PERCENT = 411,                  /* PERCENT  */
  YYSYMBOL_LEFT_ANGLE = 412,               /* LEFT_ANGLE  */
  YYSYMBOL_RIGHT_ANGLE = 413,              /* RIGHT_ANGLE  */
  YYSYMBOL_VERTICAL_BAR = 414,             /* VERTICAL_BAR  */
  YYSYMBOL_CARET = 415,                    /* CARET  */
  YYSYMBOL_AMPERSAND = 416,                /* AMPERSAND  */
  YYSYMBOL_QUESTION = 417,                 /* QUESTION  */
  YYSYMBOL_INVARIANT = 418,                /* INVARIANT  */
  YYSYMBOL_HIGH_PRECISION = 419,           /* HIGH_PRECISION  */
  YYSYMBOL_MEDIUM_PRECISION = 420,         /* MEDIUM_PRECISION  */
  YYSYMBOL_LOW_PRECISION = 421,            /* LOW_PRECISION  */
  YYSYMBOL_PRECISION = 422,                /* PRECISION  */
  YYSYMBOL_PACKED = 423,                   /* PACKED  */
  YYSYMBOL_RESOURCE = 424,                 /* RESOURCE  */
  YYSYMBOL_SUPERP = 425,                   /* SUPERP  */
  YYSYMBOL_INLINE = 426,                   /* INLINE  */
  YYSYMBOL_NOINLINE = 427,                 /* NOINLINE  */
  YYSYMBOL_FLOATCONSTANT = 428,            /* FLOATCONSTANT  */
  YYSYMBOL_INTCONSTANT = 429,              /* INTCONSTANT  */
  YYSYMBOL_UINTCONSTANT = 430,             /* UINTCONSTANT  */
  YYSYMBOL_BOOLCONSTANT = 431,             /* BOOLCONSTANT  */
  YYSYMBOL_IDENTIFIER = 432,               /* IDENTIFIER  */
  YYSYMBOL_TYPE_NAME = 433,                /* TYPE_NAME  */
  YYSYMBOL_CENTROID = 434,                 /* CENTROID  */
  YYSYMBOL_IN = 435,                       /* IN  */
  YYSYMBOL_OUT = 436,                      /* OUT  */
  YYSYMBOL_INOUT = 437,                    /* INOUT  */
  YYSYMBOL_STRUCT = 438,                   /* STRUCT  */
  YYSYMBOL_VOID = 439,                     /* VOID  */
  YYSYMBOL_WHILE = 440,                    /* WHILE  */
  YYSYMBOL_BREAK = 441,                    /* BREAK  */
  YYSYMBOL_CONTINUE = 442,                 /* CONTINUE  */
  YYSYMBOL_DO = 443,                       /* DO  */
  YYSYMBOL_ELSE = 444,                     /* ELSE  */
  YYSYMBOL_FOR = 445,                      /* FOR  */
  YYSYMBOL_IF = 446,                       /* IF  */
  YYSYMBOL_DISCARD = 447,                  /* DISCARD  */
  YYSYMBOL_RETURN = 448,                   /* RETURN  */
  YYSYMBOL_SWITCH = 449,                   /* SWITCH  */
  YYSYMBOL_CASE = 450,                     /* CASE  */
  YYSYMBOL_DEFAULT = 451,                  /* DEFAULT  */
  YYSYMBOL_TERMINATE_INVOCATION = 452,     /* TERMINATE_INVOCATION  */
  YYSYMBOL_TERMINATE_RAY = 453,            /* TERMINATE_RAY  */
  YYSYMBOL_IGNORE_INTERSECTION = 454,      /* IGNORE_INTERSECTION  */
  YYSYMBOL_UNIFORM = 455,                  /* UNIFORM  */
  YYSYMBOL_SHARED = 456,                   /* SHARED  */
  YYSYMBOL_BUFFER = 457,                   /* BUFFER  */
  YYSYMBOL_TILEIMAGEEXT = 458,             /* TILEIMAGEEXT  */
  YYSYMBOL_FLAT = 459,                     /* FLAT  */
  YYSYMBOL_SMOOTH = 460,                   /* SMOOTH  */
  YYSYMBOL_LAYOUT = 461,                   /* LAYOUT  */
  YYSYMBOL_DOUBLECONSTANT = 462,           /* DOUBLECONSTANT  */
  YYSYMBOL_INT16CONSTANT = 463,            /* INT16CONSTANT  */
  YYSYMBOL_UINT16CONSTANT = 464,           /* UINT16CONSTANT  */
  YYSYMBOL_FLOAT16CONSTANT = 465,          /* FLOAT16CONSTANT  */
  YYSYMBOL_INT32CONSTANT = 466,            /* INT32CONSTANT  */
  YYSYMBOL_UINT32CONSTANT = 467,           /* UINT32CONSTANT  */
  YYSYMBOL_FLOATE2M1CONSTANT = 468,        /* FLOATE2M1CONSTANT  */
  YYSYMBOL_FLOATE3M2CONSTANT = 469,        /* FLOATE3M2CONSTANT  */
  YYSYMBOL_FLOATE2M3CONSTANT = 470,        /* FLOATE2M3CONSTANT  */
  YYSYMBOL_FLOATUE8M0CONSTANT = 471,       /* FLOATUE8M0CONSTANT  */
  YYSYMBOL_FLOATMXINT8CONSTANT = 472,      /* FLOATMXINT8CONSTANT  */
  YYSYMBOL_INT64CONSTANT = 473,            /* INT64CONSTANT  */
  YYSYMBOL_UINT64CONSTANT = 474,           /* UINT64CONSTANT  */
  YYSYMBOL_SUBROUTINE = 475,               /* SUBROUTINE  */
  YYSYMBOL_DEMOTE = 476,                   /* DEMOTE  */
  YYSYMBOL_FUNCTION = 477,                 /* FUNCTION  */
  YYSYMBOL_PAYLOADNV = 478,                /* PAYLOADNV  */
  YYSYMBOL_PAYLOADINNV = 479,              /* PAYLOADINNV  */
  YYSYMBOL_HITATTRNV = 480,                /* HITATTRNV  */
  YYSYMBOL_CALLDATANV = 481,               /* CALLDATANV  */
  YYSYMBOL_CALLDATAINNV = 482,             /* CALLDATAINNV  */
  YYSYMBOL_PAYLOADEXT = 483,               /* PAYLOADEXT  */
  YYSYMBOL_PAYLOADINEXT = 484,             /* PAYLOADINEXT  */
  YYSYMBOL_HITATTREXT = 485,               /* HITATTREXT  */
  YYSYMBOL_CALLDATAEXT = 486,              /* CALLDATAEXT  */
  YYSYMBOL_CALLDATAINEXT = 487,            /* CALLDATAINEXT  */
  YYSYMBOL_PATCH = 488,                    /* PATCH  */
  YYSYMBOL_SAMPLE = 489,                   /* SAMPLE  */
  YYSYMBOL_NONUNIFORM = 490,               /* NONUNIFORM  */
  YYSYMBOL_RESOURCEHEAP = 491,             /* RESOURCEHEAP  */
  YYSYMBOL_SAMPLERHEAP = 492,              /* SAMPLERHEAP  */
  YYSYMBOL_COHERENT = 493,                 /* COHERENT  */
  YYSYMBOL_VOLATILE = 494,                 /* VOLATILE  */
  YYSYMBOL_RESTRICT = 495,                 /* RESTRICT  */
  YYSYMBOL_READONLY = 496,                 /* READONLY  */
  YYSYMBOL_WRITEONLY = 497,                /* WRITEONLY  */
  YYSYMBOL_NONTEMPORAL = 498,              /* NONTEMPORAL  */
  YYSYMBOL_DEVICECOHERENT = 499,           /* DEVICECOHERENT  */
  YYSYMBOL_QUEUEFAMILYCOHERENT = 500,      /* QUEUEFAMILYCOHERENT  */
  YYSYMBOL_WORKGROUPCOHERENT = 501,        /* WORKGROUPCOHERENT  */
  YYSYMBOL_SUBGROUPCOHERENT = 502,         /* SUBGROUPCOHERENT  */
  YYSYMBOL_NONPRIVATE = 503,               /* NONPRIVATE  */
  YYSYMBOL_SHADERCALLCOHERENT = 504,       /* SHADERCALLCOHERENT  */
  YYSYMBOL_NOPERSPECTIVE = 505,            /* NOPERSPECTIVE  */
  YYSYMBOL_EXPLICITINTERPAMD = 506,        /* EXPLICITINTERPAMD  */
  YYSYMBOL_PERVERTEXEXT = 507,             /* PERVERTEXEXT  */
  YYSYMBOL_PERVERTEXNV = 508,              /* PERVERTEXNV  */
  YYSYMBOL_PERPRIMITIVENV = 509,           /* PERPRIMITIVENV  */
  YYSYMBOL_PERVIEWNV = 510,                /* PERVIEWNV  */
  YYSYMBOL_PERTASKNV = 511,                /* PERTASKNV  */
  YYSYMBOL_PERPRIMITIVEEXT = 512,          /* PERPRIMITIVEEXT  */
  YYSYMBOL_TASKPAYLOADWORKGROUPEXT = 513,  /* TASKPAYLOADWORKGROUPEXT  */
  YYSYMBOL_PRECISE = 514,                  /* PRECISE  */
  YYSYMBOL_YYACCEPT = 515,                 /* $accept  */
  YYSYMBOL_variable_identifier = 516,      /* variable_identifier  */
  YYSYMBOL_primary_expression = 517,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 518,       /* postfix_expression  */
  YYSYMBOL_integer_expression = 519,       /* integer_expression  */
  YYSYMBOL_function_call = 520,            /* function_call  */
  YYSYMBOL_function_call_or_method = 521,  /* function_call_or_method  */
  YYSYMBOL_function_call_generic = 522,    /* function_call_generic  */
  YYSYMBOL_function_call_header_no_parameters = 523, /* function_call_header_no_parameters  */
  YYSYMBOL_function_call_header_with_parameters = 524, /* function_call_header_with_parameters  */
  YYSYMBOL_function_call_header = 525,     /* function_call_header  */
  YYSYMBOL_function_identifier = 526,      /* function_identifier  */
  YYSYMBOL_unary_expression = 527,         /* unary_expression  */
  YYSYMBOL_unary_operator = 528,           /* unary_operator  */
  YYSYMBOL_multiplicative_expression = 529, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 530,      /* additive_expression  */
  YYSYMBOL_shift_expression = 531,         /* shift_expression  */
  YYSYMBOL_relational_expression = 532,    /* relational_expression  */
  YYSYMBOL_equality_expression = 533,      /* equality_expression  */
  YYSYMBOL_and_expression = 534,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 535,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 536,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 537,   /* logical_and_expression  */
  YYSYMBOL_logical_xor_expression = 538,   /* logical_xor_expression  */
  YYSYMBOL_logical_or_expression = 539,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 540,   /* conditional_expression  */
  YYSYMBOL_541_1 = 541,                    /* $@1  */
  YYSYMBOL_assignment_expression = 542,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 543,      /* assignment_operator  */
  YYSYMBOL_expression = 544,               /* expression  */
  YYSYMBOL_constant_expression = 545,      /* constant_expression  */
  YYSYMBOL_declaration = 546,              /* declaration  */
  YYSYMBOL_block_structure = 547,          /* block_structure  */
  YYSYMBOL_548_2 = 548,                    /* $@2  */
  YYSYMBOL_identifier_list = 549,          /* identifier_list  */
  YYSYMBOL_function_prototype = 550,       /* function_prototype  */
  YYSYMBOL_function_declarator = 551,      /* function_declarator  */
  YYSYMBOL_function_header_with_parameters = 552, /* function_header_with_parameters  */
  YYSYMBOL_function_header = 553,          /* function_header  */
  YYSYMBOL_parameter_declarator = 554,     /* parameter_declarator  */
  YYSYMBOL_parameter_declaration = 555,    /* parameter_declaration  */
  YYSYMBOL_parameter_type_specifier = 556, /* parameter_type_specifier  */
  YYSYMBOL_init_declarator_list = 557,     /* init_declarator_list  */
  YYSYMBOL_single_declaration = 558,       /* single_declaration  */
  YYSYMBOL_fully_specified_type = 559,     /* fully_specified_type  */
  YYSYMBOL_invariant_qualifier = 560,      /* invariant_qualifier  */
  YYSYMBOL_interpolation_qualifier = 561,  /* interpolation_qualifier  */
  YYSYMBOL_layout_qualifier = 562,         /* layout_qualifier  */
  YYSYMBOL_layout_qualifier_id_list = 563, /* layout_qualifier_id_list  */
  YYSYMBOL_layout_qualifier_id = 564,      /* layout_qualifier_id  */
  YYSYMBOL_precise_qualifier = 565,        /* precise_qualifier  */
  YYSYMBOL_type_qualifier = 566,           /* type_qualifier  */
  YYSYMBOL_single_type_qualifier = 567,    /* single_type_qualifier  */
  YYSYMBOL_storage_qualifier = 568,        /* storage_qualifier  */
  YYSYMBOL_non_uniform_qualifier = 569,    /* non_uniform_qualifier  */
  YYSYMBOL_type_name_list = 570,           /* type_name_list  */
  YYSYMBOL_type_specifier = 571,           /* type_specifier  */
  YYSYMBOL_array_specifier = 572,          /* array_specifier  */
  YYSYMBOL_type_parameter_specifier_opt = 573, /* type_parameter_specifier_opt  */
  YYSYMBOL_type_parameter_specifier = 574, /* type_parameter_specifier  */
  YYSYMBOL_type_parameter_specifier_list = 575, /* type_parameter_specifier_list  */
  YYSYMBOL_type_specifier_nonarray = 576,  /* type_specifier_nonarray  */
  YYSYMBOL_precision_qualifier = 577,      /* precision_qualifier  */
  YYSYMBOL_struct_specifier = 578,         /* struct_specifier  */
  YYSYMBOL_579_3 = 579,                    /* $@3  */
  YYSYMBOL_580_4 = 580,                    /* $@4  */
  YYSYMBOL_struct_declaration_list = 581,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 582,       /* struct_declaration  */
  YYSYMBOL_block_heap_inner_structure = 583, /* block_heap_inner_structure  */
  YYSYMBOL_584_5 = 584,                    /* $@5  */
  YYSYMBOL_struct_declaration_no_inline_block_list = 585, /* struct_declaration_no_inline_block_list  */
  YYSYMBOL_struct_declaration_no_inline_block = 586, /* struct_declaration_no_inline_block  */
  YYSYMBOL_struct_declarator_list = 587,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 588,        /* struct_declarator  */
  YYSYMBOL_initializer = 589,              /* initializer  */
  YYSYMBOL_initializer_list = 590,         /* initializer_list  */
  YYSYMBOL_declaration_statement = 591,    /* declaration_statement  */
  YYSYMBOL_statement = 592,                /* statement  */
  YYSYMBOL_simple_statement = 593,         /* simple_statement  */
  YYSYMBOL_demote_statement = 594,         /* demote_statement  */
  YYSYMBOL_compound_statement = 595,       /* compound_statement  */
  YYSYMBOL_596_6 = 596,                    /* $@6  */
  YYSYMBOL_597_7 = 597,                    /* $@7  */
  YYSYMBOL_statement_no_new_scope = 598,   /* statement_no_new_scope  */
  YYSYMBOL_statement_scoped = 599,         /* statement_scoped  */
  YYSYMBOL_600_8 = 600,                    /* $@8  */
  YYSYMBOL_601_9 = 601,                    /* $@9  */
  YYSYMBOL_compound_statement_no_new_scope = 602, /* compound_statement_no_new_scope  */
  YYSYMBOL_statement_list = 603,           /* statement_list  */
  YYSYMBOL_expression_statement = 604,     /* expression_statement  */
  YYSYMBOL_selection_statement = 605,      /* selection_statement  */
  YYSYMBOL_selection_statement_nonattributed = 606, /* selection_statement_nonattributed  */
  YYSYMBOL_selection_rest_statement = 607, /* selection_rest_statement  */
  YYSYMBOL_condition = 608,                /* condition  */
  YYSYMBOL_switch_statement = 609,         /* switch_statement  */
  YYSYMBOL_switch_statement_nonattributed = 610, /* switch_statement_nonattributed  */
  YYSYMBOL_611_10 = 611,                   /* $@10  */
  YYSYMBOL_switch_statement_list = 612,    /* switch_statement_list  */
  YYSYMBOL_case_label = 613,               /* case_label  */
  YYSYMBOL_iteration_statement = 614,      /* iteration_statement  */
  YYSYMBOL_iteration_statement_nonattributed = 615, /* iteration_statement_nonattributed  */
  YYSYMBOL_616_11 = 616,                   /* $@11  */
  YYSYMBOL_617_12 = 617,                   /* $@12  */
  YYSYMBOL_618_13 = 618,                   /* $@13  */
  YYSYMBOL_for_init_statement = 619,       /* for_init_statement  */
  YYSYMBOL_conditionopt = 620,             /* conditionopt  */
  YYSYMBOL_for_rest_statement = 621,       /* for_rest_statement  */
  YYSYMBOL_jump_statement = 622,           /* jump_statement  */
  YYSYMBOL_translation_unit = 623,         /* translation_unit  */
  YYSYMBOL_external_declaration = 624,     /* external_declaration  */
  YYSYMBOL_function_definition = 625,      /* function_definition  */
  YYSYMBOL_626_14 = 626,                   /* $@14  */
  YYSYMBOL_attribute = 627,                /* attribute  */
  YYSYMBOL_attribute_list = 628,           /* attribute_list  */
  YYSYMBOL_single_attribute = 629,         /* single_attribute  */
  YYSYMBOL_spirv_requirements_list = 630,  /* spirv_requirements_list  */
  YYSYMBOL_spirv_requirements_parameter = 631, /* spirv_requirements_parameter  */
  YYSYMBOL_spirv_extension_list = 632,     /* spirv_extension_list  */
  YYSYMBOL_spirv_capability_list = 633,    /* spirv_capability_list  */
  YYSYMBOL_spirv_execution_mode_qualifier = 634, /* spirv_execution_mode_qualifier  */
  YYSYMBOL_spirv_execution_mode_parameter_list = 635, /* spirv_execution_mode_parameter_list  */
  YYSYMBOL_spirv_execution_mode_parameter = 636, /* spirv_execution_mode_parameter  */
  YYSYMBOL_spirv_execution_mode_id_parameter_list = 637, /* spirv_execution_mode_id_parameter_list  */
  YYSYMBOL_spirv_storage_class_qualifier = 638, /* spirv_storage_class_qualifier  */
  YYSYMBOL_spirv_decorate_qualifier = 639, /* spirv_decorate_qualifier  */
  YYSYMBOL_spirv_decorate_parameter_list = 640, /* spirv_decorate_parameter_list  */
  YYSYMBOL_spirv_decorate_parameter = 641, /* spirv_decorate_parameter  */
  YYSYMBOL_spirv_decorate_id_parameter_list = 642, /* spirv_decorate_id_parameter_list  */
  YYSYMBOL_spirv_decorate_id_parameter = 643, /* spirv_decorate_id_parameter  */
  YYSYMBOL_spirv_decorate_string_parameter_list = 644, /* spirv_decorate_string_parameter_list  */
  YYSYMBOL_spirv_type_specifier = 645,     /* spirv_type_specifier  */
  YYSYMBOL_spirv_type_parameter_list = 646, /* spirv_type_parameter_list  */
  YYSYMBOL_spirv_type_parameter = 647,     /* spirv_type_parameter  */
  YYSYMBOL_spirv_instruction_qualifier = 648, /* spirv_instruction_qualifier  */
  YYSYMBOL_spirv_instruction_qualifier_list = 649, /* spirv_instruction_qualifier_list  */
  YYSYMBOL_spirv_instruction_qualifier_id = 650 /* spirv_instruction_qualifier_id  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 111 "MachineIndependent/glslang.y"


#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


#line 790 "MachineIndependent/glslang_tab.cpp"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  496
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   15602

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  515
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  136
/* YYNRULES -- Number of rules.  */
#define YYNRULES  758
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1012

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   769


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
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
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   371,   371,   377,   380,   385,   388,   391,   395,   398,
     401,   405,   409,   413,   417,   421,   425,   431,   435,   439,
     443,   447,   451,   458,   461,   464,   467,   470,   475,   483,
     490,   497,   503,   507,   514,   517,   523,   541,   566,   574,
     579,   606,   614,   620,   624,   628,   644,   651,   652,   653,
     654,   660,   661,   666,   671,   680,   681,   686,   694,   695,
     701,   710,   711,   716,   721,   726,   734,   735,   744,   756,
     757,   766,   767,   776,   777,   786,   787,   795,   796,   804,
     805,   813,   814,   814,   832,   833,   849,   853,   857,   861,
     866,   870,   874,   878,   882,   886,   890,   897,   900,   911,
     918,   923,   930,   935,   940,   947,   950,   953,   956,   961,
     969,   969,   981,   985,   992,   997,  1005,  1013,  1025,  1028,
    1035,  1048,  1068,  1075,  1098,  1113,  1132,  1143,  1154,  1164,
    1174,  1184,  1193,  1196,  1201,  1206,  1211,  1219,  1224,  1230,
    1235,  1240,  1249,  1259,  1286,  1295,  1302,  1309,  1316,  1323,
    1331,  1339,  1349,  1359,  1366,  1376,  1382,  1385,  1392,  1396,
    1400,  1408,  1417,  1420,  1431,  1434,  1437,  1441,  1445,  1449,
    1453,  1456,  1461,  1465,  1470,  1478,  1482,  1487,  1493,  1499,
    1506,  1511,  1516,  1524,  1529,  1541,  1555,  1561,  1566,  1571,
    1576,  1584,  1592,  1600,  1608,  1616,  1624,  1632,  1640,  1648,
    1656,  1663,  1670,  1674,  1679,  1684,  1689,  1694,  1699,  1704,
    1708,  1712,  1716,  1720,  1724,  1730,  1736,  1746,  1753,  1756,
    1764,  1771,  1782,  1787,  1795,  1799,  1809,  1812,  1818,  1824,
    1830,  1838,  1848,  1852,  1856,  1860,  1865,  1869,  1874,  1879,
    1884,  1889,  1894,  1899,  1904,  1909,  1914,  1920,  1926,  1932,
    1937,  1942,  1947,  1952,  1957,  1962,  1967,  1972,  1977,  1982,
    1987,  1992,  1999,  2004,  2009,  2014,  2019,  2024,  2029,  2034,
    2039,  2044,  2049,  2054,  2059,  2064,  2069,  2074,  2079,  2084,
    2089,  2094,  2102,  2110,  2118,  2124,  2130,  2136,  2142,  2148,
    2154,  2160,  2166,  2172,  2178,  2184,  2190,  2196,  2202,  2208,
    2214,  2220,  2226,  2232,  2238,  2244,  2250,  2256,  2262,  2268,
    2274,  2280,  2286,  2292,  2298,  2304,  2310,  2316,  2322,  2328,
    2334,  2340,  2346,  2352,  2358,  2364,  2370,  2376,  2382,  2388,
    2394,  2400,  2406,  2412,  2418,  2424,  2430,  2436,  2442,  2448,
    2454,  2460,  2468,  2476,  2484,  2492,  2500,  2508,  2516,  2524,
    2532,  2540,  2548,  2556,  2562,  2568,  2574,  2580,  2586,  2592,
    2598,  2604,  2610,  2616,  2622,  2628,  2634,  2640,  2646,  2652,
    2658,  2664,  2670,  2676,  2682,  2688,  2694,  2700,  2706,  2712,
    2718,  2724,  2730,  2736,  2742,  2748,  2754,  2760,  2766,  2772,
    2776,  2780,  2784,  2789,  2794,  2799,  2804,  2809,  2814,  2819,
    2824,  2829,  2834,  2839,  2844,  2849,  2854,  2860,  2866,  2872,
    2878,  2884,  2890,  2896,  2902,  2908,  2914,  2920,  2926,  2932,
    2937,  2942,  2947,  2952,  2957,  2962,  2967,  2972,  2977,  2982,
    2987,  2992,  2997,  3002,  3007,  3012,  3017,  3022,  3027,  3032,
    3037,  3042,  3047,  3052,  3057,  3062,  3067,  3072,  3077,  3082,
    3087,  3092,  3097,  3103,  3109,  3114,  3119,  3124,  3130,  3135,
    3140,  3145,  3151,  3156,  3161,  3166,  3172,  3177,  3182,  3187,
    3193,  3199,  3205,  3211,  3216,  3222,  3228,  3234,  3239,  3244,
    3249,  3254,  3259,  3265,  3270,  3275,  3280,  3286,  3291,  3296,
    3301,  3307,  3312,  3317,  3322,  3328,  3333,  3338,  3343,  3349,
    3354,  3359,  3364,  3370,  3375,  3380,  3385,  3391,  3396,  3401,
    3406,  3412,  3417,  3422,  3427,  3433,  3438,  3443,  3448,  3454,
    3459,  3464,  3469,  3475,  3480,  3485,  3490,  3496,  3501,  3506,
    3511,  3517,  3522,  3527,  3532,  3538,  3543,  3548,  3553,  3559,
    3564,  3569,  3574,  3579,  3584,  3589,  3594,  3599,  3604,  3609,
    3614,  3619,  3624,  3629,  3634,  3639,  3644,  3649,  3654,  3659,
    3664,  3669,  3674,  3679,  3685,  3691,  3697,  3703,  3709,  3715,
    3721,  3728,  3735,  3741,  3747,  3753,  3759,  3766,  3773,  3780,
    3787,  3792,  3797,  3801,  3807,  3813,  3819,  3823,  3827,  3831,
    3836,  3854,  3859,  3864,  3872,  3872,  3888,  3888,  3898,  3901,
    3914,  3917,  3934,  3934,  3950,  3953,  3966,  3988,  4015,  4019,
    4025,  4030,  4041,  4044,  4050,  4056,  4065,  4068,  4074,  4078,
    4079,  4085,  4086,  4087,  4088,  4089,  4090,  4091,  4092,  4096,
    4104,  4105,  4109,  4105,  4123,  4124,  4128,  4128,  4135,  4135,
    4149,  4152,  4162,  4170,  4181,  4182,  4186,  4189,  4196,  4203,
    4207,  4215,  4219,  4228,  4231,  4238,  4238,  4258,  4261,  4267,
    4279,  4291,  4294,  4302,  4302,  4321,  4321,  4343,  4343,  4364,
    4367,  4373,  4376,  4382,  4386,  4393,  4398,  4403,  4410,  4413,
    4417,  4421,  4425,  4434,  4438,  4447,  4450,  4453,  4461,  4461,
    4504,  4509,  4512,  4517,  4520,  4523,  4526,  4531,  4534,  4539,
    4542,  4547,  4550,  4555,  4558,  4563,  4567,  4572,  4576,  4581,
    4585,  4592,  4595,  4600,  4603,  4606,  4609,  4612,  4617,  4626,
    4637,  4642,  4650,  4654,  4659,  4663,  4668,  4672,  4677,  4681,
    4688,  4691,  4696,  4699,  4702,  4705,  4710,  4713,  4718,  4724,
    4727,  4730,  4733,  4738,  4742,  4747,  4751,  4756,  4760,  4767,
    4770,  4775,  4778,  4783,  4786,  4792,  4795,  4800,  4803
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "BOOL", "INT",
  "UINT", "FLOAT", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4",
  "UVEC2", "UVEC3", "UVEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3",
  "MAT4", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4",
  "MAT4X2", "MAT4X3", "MAT4X4", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW", "SAMPLER2DARRAY",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER2D", "ISAMPLER3D", "ISAMPLERCUBE",
  "ISAMPLER2DARRAY", "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE",
  "USAMPLER2DARRAY", "SAMPLER", "SAMPLERSHADOW", "TEXTURE2D", "TEXTURE3D",
  "TEXTURECUBE", "TEXTURE2DARRAY", "ITEXTURE2D", "ITEXTURE3D",
  "ITEXTURECUBE", "ITEXTURE2DARRAY", "UTEXTURE2D", "UTEXTURE3D",
  "UTEXTURECUBE", "UTEXTURE2DARRAY", "ATTRIBUTE", "VARYING", "FLOATE5M2_T",
  "FLOATE4M3_T", "BFLOAT16_T", "FLOAT16_T", "FLOAT32_T", "DOUBLE",
  "FLOAT64_T", "FLOATE2M1_T", "FLOATE3M2_T", "FLOATE2M3_T", "FLOATUE8M0_T",
  "FLOATMXINT8_T", "INT64_T", "UINT64_T", "INT32_T", "UINT32_T", "INT16_T",
  "UINT16_T", "INT8_T", "UINT8_T", "I64VEC2", "I64VEC3", "I64VEC4",
  "U64VEC2", "U64VEC3", "U64VEC4", "I32VEC2", "I32VEC3", "I32VEC4",
  "U32VEC2", "U32VEC3", "U32VEC4", "I16VEC2", "I16VEC3", "I16VEC4",
  "U16VEC2", "U16VEC3", "U16VEC4", "I8VEC2", "I8VEC3", "I8VEC4", "U8VEC2",
  "U8VEC3", "U8VEC4", "DVEC2", "DVEC3", "DVEC4", "DMAT2", "DMAT3", "DMAT4",
  "BF16VEC2", "BF16VEC3", "BF16VEC4", "FE5M2VEC2", "FE5M2VEC3",
  "FE5M2VEC4", "FE4M3VEC2", "FE4M3VEC3", "FE4M3VEC4", "FE2M1VEC2",
  "FE2M1VEC3", "FE2M1VEC4", "FE3M2VEC2", "FE3M2VEC3", "FE3M2VEC4",
  "FE2M3VEC2", "FE2M3VEC3", "FE2M3VEC4", "FUE8M0VEC2", "FUE8M0VEC3",
  "FUE8M0VEC4", "FMXINT8VEC2", "FMXINT8VEC3", "FMXINT8VEC4", "F16VEC2",
  "F16VEC3", "F16VEC4", "F16MAT2", "F16MAT3", "F16MAT4", "F32VEC2",
  "F32VEC3", "F32VEC4", "F32MAT2", "F32MAT3", "F32MAT4", "F64VEC2",
  "F64VEC3", "F64VEC4", "F64MAT2", "F64MAT3", "F64MAT4", "DMAT2X2",
  "DMAT2X3", "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2",
  "DMAT4X3", "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "F32MAT2X2", "F32MAT2X3", "F32MAT2X4", "F32MAT3X2", "F32MAT3X3",
  "F32MAT3X4", "F32MAT4X2", "F32MAT4X3", "F32MAT4X4", "F64MAT2X2",
  "F64MAT2X3", "F64MAT2X4", "F64MAT3X2", "F64MAT3X3", "F64MAT3X4",
  "F64MAT4X2", "F64MAT4X3", "F64MAT4X4", "ATOMIC_UINT", "ACCSTRUCTNV",
  "ACCSTRUCTEXT", "RAYQUERYEXT", "FCOOPMATNV", "ICOOPMATNV", "UCOOPMATNV",
  "COOPMAT", "COOPVECNV", "VECTOR", "HITOBJECTNV", "HITOBJECTATTRNV",
  "HITOBJECTEXT", "HITOBJECTATTREXT", "TENSORLAYOUTNV", "TENSORVIEWNV",
  "TENSORARM", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLERCUBEARRAY", "USAMPLERCUBEARRAY", "SAMPLER1D", "SAMPLER1DARRAY",
  "SAMPLER1DARRAYSHADOW", "ISAMPLER1D", "SAMPLER1DSHADOW", "SAMPLER2DRECT",
  "SAMPLER2DRECTSHADOW", "ISAMPLER2DRECT", "USAMPLER2DRECT",
  "SAMPLERBUFFER", "ISAMPLERBUFFER", "USAMPLERBUFFER", "SAMPLER2DMS",
  "ISAMPLER2DMS", "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "SAMPLEREXTERNAL2DY2YEXT",
  "ISAMPLER1DARRAY", "USAMPLER1D", "USAMPLER1DARRAY", "F16SAMPLER1D",
  "F16SAMPLER2D", "F16SAMPLER3D", "F16SAMPLER2DRECT", "F16SAMPLERCUBE",
  "F16SAMPLER1DARRAY", "F16SAMPLER2DARRAY", "F16SAMPLERCUBEARRAY",
  "F16SAMPLERBUFFER", "F16SAMPLER2DMS", "F16SAMPLER2DMSARRAY",
  "F16SAMPLER1DSHADOW", "F16SAMPLER2DSHADOW", "F16SAMPLER1DARRAYSHADOW",
  "F16SAMPLER2DARRAYSHADOW", "F16SAMPLER2DRECTSHADOW",
  "F16SAMPLERCUBESHADOW", "F16SAMPLERCUBEARRAYSHADOW", "IMAGE1D",
  "IIMAGE1D", "UIMAGE1D", "IMAGE2D", "IIMAGE2D", "UIMAGE2D", "IMAGE3D",
  "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT", "IIMAGE2DRECT", "UIMAGE2DRECT",
  "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "IMAGE1DARRAY", "IIMAGE1DARRAY", "UIMAGE1DARRAY",
  "IMAGE2DARRAY", "IIMAGE2DARRAY", "UIMAGE2DARRAY", "IMAGECUBEARRAY",
  "IIMAGECUBEARRAY", "UIMAGECUBEARRAY", "IMAGE2DMS", "IIMAGE2DMS",
  "UIMAGE2DMS", "IMAGE2DMSARRAY", "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY",
  "F16IMAGE1D", "F16IMAGE2D", "F16IMAGE3D", "F16IMAGE2DRECT",
  "F16IMAGECUBE", "F16IMAGE1DARRAY", "F16IMAGE2DARRAY",
  "F16IMAGECUBEARRAY", "F16IMAGEBUFFER", "F16IMAGE2DMS",
  "F16IMAGE2DMSARRAY", "I64IMAGE1D", "U64IMAGE1D", "I64IMAGE2D",
  "U64IMAGE2D", "I64IMAGE3D", "U64IMAGE3D", "I64IMAGE2DRECT",
  "U64IMAGE2DRECT", "I64IMAGECUBE", "U64IMAGECUBE", "I64IMAGEBUFFER",
  "U64IMAGEBUFFER", "I64IMAGE1DARRAY", "U64IMAGE1DARRAY",
  "I64IMAGE2DARRAY", "U64IMAGE2DARRAY", "I64IMAGECUBEARRAY",
  "U64IMAGECUBEARRAY", "I64IMAGE2DMS", "U64IMAGE2DMS", "I64IMAGE2DMSARRAY",
  "U64IMAGE2DMSARRAY", "TEXTURECUBEARRAY", "ITEXTURECUBEARRAY",
  "UTEXTURECUBEARRAY", "TEXTURE1D", "ITEXTURE1D", "UTEXTURE1D",
  "TEXTURE1DARRAY", "ITEXTURE1DARRAY", "UTEXTURE1DARRAY", "TEXTURE2DRECT",
  "ITEXTURE2DRECT", "UTEXTURE2DRECT", "TEXTUREBUFFER", "ITEXTUREBUFFER",
  "UTEXTUREBUFFER", "TEXTURE2DMS", "ITEXTURE2DMS", "UTEXTURE2DMS",
  "TEXTURE2DMSARRAY", "ITEXTURE2DMSARRAY", "UTEXTURE2DMSARRAY",
  "F16TEXTURE1D", "F16TEXTURE2D", "F16TEXTURE3D", "F16TEXTURE2DRECT",
  "F16TEXTURECUBE", "F16TEXTURE1DARRAY", "F16TEXTURE2DARRAY",
  "F16TEXTURECUBEARRAY", "F16TEXTUREBUFFER", "F16TEXTURE2DMS",
  "F16TEXTURE2DMSARRAY", "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT",
  "ISUBPASSINPUTMS", "USUBPASSINPUT", "USUBPASSINPUTMS", "F16SUBPASSINPUT",
  "F16SUBPASSINPUTMS", "SPIRV_INSTRUCTION", "SPIRV_EXECUTION_MODE",
  "SPIRV_EXECUTION_MODE_ID", "SPIRV_DECORATE", "SPIRV_DECORATE_ID",
  "SPIRV_DECORATE_STRING", "SPIRV_TYPE", "SPIRV_STORAGE_CLASS",
  "SPIRV_BY_REFERENCE", "SPIRV_LITERAL", "ATTACHMENTEXT", "IATTACHMENTEXT",
  "UATTACHMENTEXT", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "STRING_LITERAL",
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_BRACE", "RIGHT_BRACE", "DOT", "COMMA", "COLON", "EQUAL",
  "SEMICOLON", "BANG", "DASH", "TILDE", "PLUS", "STAR", "SLASH", "PERCENT",
  "LEFT_ANGLE", "RIGHT_ANGLE", "VERTICAL_BAR", "CARET", "AMPERSAND",
  "QUESTION", "INVARIANT", "HIGH_PRECISION", "MEDIUM_PRECISION",
  "LOW_PRECISION", "PRECISION", "PACKED", "RESOURCE", "SUPERP", "INLINE",
  "NOINLINE", "FLOATCONSTANT", "INTCONSTANT", "UINTCONSTANT",
  "BOOLCONSTANT", "IDENTIFIER", "TYPE_NAME", "CENTROID", "IN", "OUT",
  "INOUT", "STRUCT", "VOID", "WHILE", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT",
  "TERMINATE_INVOCATION", "TERMINATE_RAY", "IGNORE_INTERSECTION",
  "UNIFORM", "SHARED", "BUFFER", "TILEIMAGEEXT", "FLAT", "SMOOTH",
  "LAYOUT", "DOUBLECONSTANT", "INT16CONSTANT", "UINT16CONSTANT",
  "FLOAT16CONSTANT", "INT32CONSTANT", "UINT32CONSTANT",
  "FLOATE2M1CONSTANT", "FLOATE3M2CONSTANT", "FLOATE2M3CONSTANT",
  "FLOATUE8M0CONSTANT", "FLOATMXINT8CONSTANT", "INT64CONSTANT",
  "UINT64CONSTANT", "SUBROUTINE", "DEMOTE", "FUNCTION", "PAYLOADNV",
  "PAYLOADINNV", "HITATTRNV", "CALLDATANV", "CALLDATAINNV", "PAYLOADEXT",
  "PAYLOADINEXT", "HITATTREXT", "CALLDATAEXT", "CALLDATAINEXT", "PATCH",
  "SAMPLE", "NONUNIFORM", "RESOURCEHEAP", "SAMPLERHEAP", "COHERENT",
  "VOLATILE", "RESTRICT", "READONLY", "WRITEONLY", "NONTEMPORAL",
  "DEVICECOHERENT", "QUEUEFAMILYCOHERENT", "WORKGROUPCOHERENT",
  "SUBGROUPCOHERENT", "NONPRIVATE", "SHADERCALLCOHERENT", "NOPERSPECTIVE",
  "EXPLICITINTERPAMD", "PERVERTEXEXT", "PERVERTEXNV", "PERPRIMITIVENV",
  "PERVIEWNV", "PERTASKNV", "PERPRIMITIVEEXT", "TASKPAYLOADWORKGROUPEXT",
  "PRECISE", "$accept", "variable_identifier", "primary_expression",
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
  "storage_qualifier", "non_uniform_qualifier", "type_name_list",
  "type_specifier", "array_specifier", "type_parameter_specifier_opt",
  "type_parameter_specifier", "type_parameter_specifier_list",
  "type_specifier_nonarray", "precision_qualifier", "struct_specifier",
  "$@3", "$@4", "struct_declaration_list", "struct_declaration",
  "block_heap_inner_structure", "$@5",
  "struct_declaration_no_inline_block_list",
  "struct_declaration_no_inline_block", "struct_declarator_list",
  "struct_declarator", "initializer", "initializer_list",
  "declaration_statement", "statement", "simple_statement",
  "demote_statement", "compound_statement", "$@6", "$@7",
  "statement_no_new_scope", "statement_scoped", "$@8", "$@9",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_statement_nonattributed", "selection_rest_statement",
  "condition", "switch_statement", "switch_statement_nonattributed",
  "$@10", "switch_statement_list", "case_label", "iteration_statement",
  "iteration_statement_nonattributed", "$@11", "$@12", "$@13",
  "for_init_statement", "conditionopt", "for_rest_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "$@14", "attribute", "attribute_list",
  "single_attribute", "spirv_requirements_list",
  "spirv_requirements_parameter", "spirv_extension_list",
  "spirv_capability_list", "spirv_execution_mode_qualifier",
  "spirv_execution_mode_parameter_list", "spirv_execution_mode_parameter",
  "spirv_execution_mode_id_parameter_list",
  "spirv_storage_class_qualifier", "spirv_decorate_qualifier",
  "spirv_decorate_parameter_list", "spirv_decorate_parameter",
  "spirv_decorate_id_parameter_list", "spirv_decorate_id_parameter",
  "spirv_decorate_string_parameter_list", "spirv_type_specifier",
  "spirv_type_parameter_list", "spirv_type_parameter",
  "spirv_instruction_qualifier", "spirv_instruction_qualifier_list",
  "spirv_instruction_qualifier_id", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-901)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-753)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    5111,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -335,  -307,  -276,
    -256,  -252,  -237,  -232,  -220,  -901,  -901,  -901,  -901,  -901,
    -274,  -901,  -901,  -901,  -901,  -901,   -75,  -901,  -901,  -901,
    -901,  -901,  -370,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -210,  -143,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -372,   -95,  -112,   -70, 10231,  -264,  -901,   -79,  -901,
    -901,  -901,  -901,  6135,  -901,  -901,  -901,  -901,   -76,  -901,
    -901,  1015,  -901,  -901, 10231,   -66,  -901,  -901,  -901,  6647,
     -78,  -378,  -246,  -195,  -191,  -161,   -78,  -157,  -279, 15125,
    -901,   -42,  -399,   -72,  -901,  -341,  -901,   -37,   -34,  7159,
    -901,  -901,  -901, 10231,   -69,   -68,  -901,  -338,  -901,   -33,
    -128,  -901,  -901, 13664,   -29,  -901,  -901,  -901,   -27,   -62,
   10231,  -901,   -32,   -30,   -26,  -901,  -250,  -901,  -245,   -25,
     -24,   -22,   -21,  -243,   -20,   -18,   -17,   -16,   -15,   -14,
    -235,   -19,   -13,  -901,  -901,   -23,  -281,  -901,   -12, 10231,
    -901,    -9,  -901,  -228,  -901,  -901,  -223, 11716,  -901,  -302,
    1527,  -901,  -901,   -11,  -901,  -901,  -901,  -293,  -282,  -901,
   12203,  -262,  -901,   -58,  -901, 13664, 13664,  -901, 13664,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -289,  -901,  -901,  -901,    -5,  -219, 14151,
      -3,  -901, 13664,  -901,     1,  -360,     6,   -34,     3,  -901,
    -350,   -78,  -901,   -36,  -901,  -362,     7,  -152, 13664,  -145,
    -901,  -183,  -141,  -176,  -140,     8,  -139,   -78,  -901, 14638,
    -901,  -135, 13664,    10,  -279,  -901,  7671,   -28,  8183,  -901,
     -28,  -901, 10231, 13664,  -901,  -399,  -901,   -10,  -901,  -901,
     -59,   -73,  -323,  -340,  -121,    -8,    -6,    -4,    18,    23,
    -347,    14,  -901, 12690,  -901,    16,  -901,  -901,    12,    13,
      15,  -901,    22,    24,    19, 13177,    26, 13664,    25,    20,
      21,    27,    29,  -259,  -901,  -901,  -106,  -901,   -95,    32,
       1,  -901,  -901,  -901,  -901,  -901,  2039,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  5623,    28, 12203,     6,
   12203,  -260, 10742,  -901,  -901, 12203, 10231,  -901,  -901,  -901,
    -216,  -300,  -901,  -901, 13664,    -2,  -901,  -901, 13664,    34,
    -901,  -901,  -901, 13664,  -901,  -901,  -901,  -354,  -901,  -901,
    -198,    31,  -901,  -901,  -901,  -901,  -901,  -901,  -197,  -901,
    -196,  -901,  -901,  -194,    35,  -901,  -901,  -901,  -901,  -193,
    -901,  -189,  -901,  -901,  -901,  -901,  -901,  -186,  -901,    36,
    -901,  -185,    37,  -182,    31,  -901,  -321,  -181,  -901,    44,
      45,  -901,  -901,  -901,   -28,   -29,  -102,  -901,  -901,  -901,
     -98,  8695,  -901,  -901,  -901, 13664, 13664, 13664, 13664, 13664,
   13664, 13664, 13664, 13664, 13664, 13664, 13664, 13664, 13664, 13664,
   13664, 13664, 13664, 13664,  -901,  -901,  -901,    48,  -901,  2551,
    -901,  -901,  -901,  2551,  -901, 13664,  -901,  -901,   -96, 13664,
    -123,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901, 13664, 13664,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901, 12203,  -901,
    -901,  -159,  -901,  9207,  -901, 13664,    49,    41,  -901,  -901,
    -901,  -901,  -901,  -242,  -226,  -901,  -345,  -901,  -362,  -901,
    -362,  -901, 13664, 13664,  -901,  -183,  -901,  -183,  -901,  -176,
    -176,  -901,    55,     8,  -901, 14638,  -901, 13664,  -901,  -901,
   10231,   -94,     6,   -28,  -901,  -901,  -901,  -901,  -901,  -901,
     -59,   -59,   -73,   -73,  -323,  -323,  -323,  -323,  -340,  -340,
    -121,    -8,    -6,    -4,    18,    23, 13664,  -901,  2551,  4599,
      17,  4087,  -178,  -901,  -177,  -901,  -901,  -901,  -901,  -901,
   11229,  -901,  -901,  -901,  -901,    56,  -901,    38,  -901,  -174,
    -901,  -173,  -901,  -170,  -901,  -169,  -901,  -166,  -165,  -901,
   10231,  9719,  -901,  -901,  -901,   -61,    51,    41,    33,    75,
      77,  -901,  -901,  4599,    74,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901, 13664,  -901,
      70,  3063, 13664,  -901,    71,    79,    40,    78,  3575,  -901,
      80,  -901, 12203,  -901,  -901,  -901,  -162, 13664,  3063,    74,
    -901,  -901,  2551,  -901,    73,    41,  -901,  -901,  2551,    82,
    -901,  -901
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   175,   236,   234,   235,   233,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   237,   238,   239,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     394,   395,   396,   397,   398,   399,   400,   420,   421,   422,
     423,   424,   425,   426,   435,   448,   449,   436,   437,   439,
     438,   440,   441,   442,   443,   444,   445,   446,   447,   184,
     185,   263,   264,   262,   270,   271,   261,   272,   265,   266,
     267,   268,   269,   279,   280,   277,   278,   275,   276,   273,
     274,   326,   327,   328,   338,   339,   340,   323,   324,   325,
     335,   336,   337,   320,   321,   322,   332,   333,   334,   317,
     318,   319,   329,   330,   331,   281,   282,   283,   341,   342,
     343,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   353,   354,
     355,   311,   312,   313,   365,   366,   367,   314,   315,   316,
     377,   378,   379,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   392,
     389,   390,   391,   576,   577,   578,   579,   583,   585,   587,
     191,   588,   192,   580,   581,   584,   404,   405,   428,   431,
     393,   402,   403,   419,   401,   450,   451,   454,   455,   456,
     458,   459,   460,   462,   463,   464,   466,   467,   563,   564,
     427,   429,   430,   406,   407,   408,   452,   409,   413,   414,
     417,   457,   461,   465,   410,   411,   415,   416,   453,   412,
     418,   497,   499,   500,   501,   503,   504,   505,   507,   508,
     509,   511,   512,   513,   515,   516,   517,   519,   520,   521,
     523,   524,   525,   527,   528,   529,   531,   532,   533,   535,
     536,   537,   539,   540,   498,   502,   506,   510,   514,   522,
     526,   530,   518,   534,   538,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   432,   433,   434,
     468,   477,   479,   473,   478,   480,   481,   483,   484,   485,
     487,   488,   489,   491,   492,   493,   495,   496,   469,   470,
     471,   482,   472,   474,   475,   476,   486,   490,   494,   568,
     569,   572,   573,   574,   575,   570,   571,     0,     0,     0,
       0,     0,     0,     0,     0,   173,   174,   565,   566,   567,
       0,   687,   144,   591,   592,   593,     0,   590,   179,   177,
     178,   176,     0,   232,   180,   182,   183,   181,   146,   145,
       0,   214,   582,   194,   196,   190,   198,   200,   195,   197,
     193,   199,   201,   186,   187,   217,   188,   189,   202,   209,
     210,   211,   212,   213,   203,   204,   205,   206,   207,   208,
     147,   148,   150,   149,   151,   153,   154,   152,   216,   161,
     686,     0,   688,     0,   119,   118,     0,   132,   137,   168,
     167,   165,   169,     0,   162,   164,   170,   142,   227,   166,
     589,     0,   683,   685,     0,     0,   171,   172,   586,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     596,     0,     0,     0,   105,     0,   100,     0,   114,     0,
     128,   120,   130,     0,   131,     0,   103,   138,   108,   112,
       0,   163,   143,     0,   220,   226,     1,   684,     0,     0,
       0,   102,     0,     0,     0,   697,     0,   755,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   695,   696,   693,     0,   691,     0,     0,
     594,   158,   160,     0,   156,   218,     0,     0,   106,     0,
       0,   689,   115,     0,   121,   127,   129,   124,   133,   123,
       0,   139,   110,     0,   109,     0,     0,     9,     0,    49,
      48,    50,    47,     5,     6,     7,     8,     2,    16,    14,
      15,    17,    10,    11,    18,    19,    20,    21,    22,    12,
      13,     3,    23,    42,    25,    30,    31,     0,     0,    35,
       0,   230,     0,    41,   229,     0,   221,   116,     0,   101,
       0,     0,   753,     0,   705,     0,     0,     0,     0,     0,
     722,     0,     0,     0,     0,     0,     0,     0,   747,     0,
     720,     0,     0,     0,     0,   104,     0,     0,     0,   598,
       0,   600,     0,     0,   155,     0,   215,     0,   222,    51,
      55,    58,    61,    66,    69,    71,    73,    75,    77,    79,
      81,     0,    39,     0,   107,   631,   640,   644,     0,     0,
       0,   665,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    84,    97,     0,   618,     0,   170,
     142,   621,   642,   620,   628,   619,     0,   622,   623,   646,
     624,   653,   625,   626,   661,   627,     0,     0,     0,   125,
       0,   134,     0,   612,   141,     0,     0,   113,    43,    44,
       0,   227,    27,    28,     0,     0,    33,    32,     0,   232,
      36,    38,    45,     0,   228,   117,   757,     0,   758,   698,
       0,     0,   756,   717,   713,   714,   715,   716,     0,   711,
       0,    99,   718,     0,     0,   732,   733,   734,   735,     0,
     730,     0,   739,   740,   741,   742,   738,     0,   736,     0,
     743,     0,     0,     0,     2,   751,   227,     0,   749,     0,
       0,   690,   692,   602,     0,   610,     0,   608,   597,   599,
       0,     0,   159,   157,   219,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,   223,   224,     0,   630,     0,
     663,   676,   675,     0,   667,     0,   679,   677,     0,     0,
       0,   660,   680,   681,   682,   629,    87,    88,    90,    89,
      92,    93,    94,    95,    96,    91,    86,     0,     0,   645,
     641,   643,   647,   654,   662,   122,   126,   136,     0,   615,
     616,     0,   140,     0,     4,     0,     0,    29,    26,    37,
     231,   701,   703,     0,     0,   754,     0,   707,     0,   706,
       0,   709,     0,     0,   724,     0,   723,     0,   726,     0,
       0,   728,     0,     0,   748,     0,   745,     0,   721,   694,
       0,     0,   611,     0,   606,   601,   595,    52,    53,    54,
      57,    56,    59,    60,    64,    65,    62,    63,    67,    68,
      70,    72,    74,    76,    78,    80,     0,   225,   632,     0,
       0,     0,     0,   678,     0,   659,    85,    98,   135,   613,
       0,   111,    46,    24,   699,     0,   700,     0,   712,     0,
     719,     0,   731,     0,   737,     0,   744,     0,     0,   750,
       0,     0,   604,   607,   609,     0,     0,   651,     0,     0,
       0,   670,   669,   672,   638,   655,   614,   617,   702,   704,
     708,   710,   725,   727,   729,   746,   603,   605,     0,   633,
       0,     0,     0,   671,     0,     0,   650,     0,     0,   648,
       0,    83,     0,   635,   664,   634,     0,   673,     0,   638,
     637,   639,   657,   652,     0,   674,   668,   649,   658,     0,
     666,   656
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -901,  -598,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,
    -901,  -901,  -473,  -901,  -522,  -443,  -532,  -438,  -316,  -314,
    -311,  -315,  -312,  -309,  -901,  -530,  -901,  -537,  -901,  -550,
    -587,    11,  -901,  -901,  -901,     5,  -437,  -901,  -901,    30,
      39,    42,  -901,  -901,  -453,  -901,  -901,  -901,  -901,  -144,
    -901,  -432,  -439,  -901,     9,  -901,     0,  -471,  -901,  -901,
    -901,  -548,   119,  -901,  -901,  -901,  -606,  -604,  -901,  -901,
    -901,  -861,  -605,  -397,  -660,  -901,  -424,  -674,  -900,  -901,
    -489,  -901,  -901,  -499,  -498,  -901,  -901,    43,  -791,  -419,
    -901,  -192,  -901,  -460,  -901,  -190,  -901,  -901,  -901,  -901,
    -188,  -901,  -901,  -901,  -901,  -901,  -901,  -901,  -901,    54,
    -901,  -901,     2,  -901,  -117,  -272,  -508,  -901,  -901,  -901,
    -358,  -353,  -359,  -901,  -901,  -361,  -352,  -363,  -357,  -356,
    -901,  -364,  -355,  -901,  -447,  -589
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   581,   582,   583,   856,   584,   585,   586,   587,   588,
     589,   590,   673,   592,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   649,   650,   674,   916,   675,   837,   676,
     765,   677,   431,   706,   490,   678,   433,   434,   435,   480,
     481,   482,   436,   437,   438,   439,   440,   441,   533,   534,
     442,   443,   444,   445,   593,   536,   652,   539,   494,   495,
     595,   448,   449,   450,   632,   529,   628,   629,   630,   890,
     951,   631,   776,   777,   704,   851,   681,   682,   683,   684,
     685,   809,   956,   994,   986,   987,   988,   995,   686,   687,
     688,   689,   989,   959,   690,   691,   990,  1009,   692,   693,
     694,   919,   813,   921,   963,   984,   985,   695,   451,   452,
     453,   477,   696,   526,   527,   504,   505,   863,   864,   455,
     738,   739,   743,   456,   457,   749,   750,   757,   758,   761,
     458,   767,   768,   459,   506,   507
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     447,   499,   454,   483,   491,   432,   499,   651,   710,   446,
     711,   430,   841,   703,   732,   756,   551,   498,   918,   520,
     591,   742,   500,   596,   779,   780,   781,   500,   470,   952,
     732,   733,   474,   531,   803,   770,   792,   793,   846,   861,
     847,   723,   850,   726,   491,   852,   727,   483,   726,   790,
     791,   508,   720,   724,   509,   537,   549,   532,   537,   460,
     475,   491,   471,   538,   639,   550,   734,   735,   736,   737,
     804,   766,   794,   795,  -752,   862,   699,   701,   741,   728,
    -752,   993,   708,   709,   728,   712,   713,   461,  1001,   741,
     977,   493,   741,   729,   653,   855,   782,   626,   993,   729,
     853,   729,   654,   537,   729,   -40,   729,   714,   729,   729,
     698,   715,   493,   729,   537,   818,   623,   820,   462,   722,
     624,   700,   468,   807,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   653,   639,   653,   485,   463,   920,
     486,   705,   464,   848,   836,   602,   639,   523,   524,   639,
     604,   603,   610,   525,   730,   934,   605,   465,   611,   935,
     618,   703,   466,   703,   857,   703,   619,   634,   703,   891,
     763,   936,   636,   635,   467,   937,   717,   779,   637,   854,
     639,   859,   718,   511,   472,   838,   509,   491,   928,   510,
     512,   514,   516,   518,   519,   522,   626,   865,   867,   869,
     626,   871,   874,   603,   868,   870,   876,   872,   875,   878,
     881,  1008,   877,   884,   886,   879,   882,   964,   965,   885,
     887,   970,   971,   838,   838,   972,   973,   868,   872,   974,
     975,   875,   879,  1004,   513,   882,   887,   509,   515,   838,
     929,   509,   930,   499,   841,   745,   746,   747,   748,   779,
     860,   473,   752,   753,   754,   755,   567,   796,   797,   498,
     904,   905,   906,   907,   500,   922,   900,   901,   517,   924,
     967,   509,   521,   553,   626,   509,   554,   740,   838,   925,
     509,   756,   756,   478,   744,   940,   742,   509,   751,   759,
     762,   509,   509,   509,   769,   838,   732,   509,   839,   893,
     926,   927,   894,   893,   892,   838,   895,   893,   923,   476,
     953,   703,   897,   898,   899,   639,   639,   639,   639,   639,
     639,   639,   639,   639,   639,   639,   639,   639,   639,   639,
     639,   479,  1003,   788,   841,   789,   493,   766,   501,   766,
     838,   978,   741,   741,   373,   374,   375,   902,   903,   626,
     785,   786,   787,   487,   503,   741,   530,   741,   908,   909,
     535,   540,   370,   547,   548,   552,   955,   537,   597,   957,
     598,   622,   599,   600,   707,   601,   620,   607,   606,   608,
     609,   612,   932,   613,   614,   615,   616,   617,   621,   697,
     716,   721,   625,   703,   633,   -39,   731,   549,   801,   639,
     639,   760,   653,   727,   775,   802,   810,   771,   798,   799,
     800,   805,   639,   957,   639,   808,   814,   811,   815,   812,
     819,   626,   784,   816,   822,   823,   -41,   821,   845,   -34,
     858,   824,   996,   825,   866,   484,   873,   880,   883,   888,
     889,   991,   838,   492,   446,   917,   933,  1005,   946,   968,
     979,   447,   446,   454,   447,   703,   432,   960,   950,   447,
     446,   454,   430,   446,   502,   980,   958,   969,   446,   528,
     981,   982,  -636,   992,   998,   997,   655,  1010,  1002,   484,
     542,  1011,   910,   484,   999,   911,   913,   500,   446,   912,
     914,   783,   446,   594,   915,   469,   954,   961,  1000,  1006,
     492,  1007,   962,   983,   842,   497,   843,   772,   844,   446,
     958,   491,   939,   545,   941,   938,   943,   945,   544,   950,
     541,   948,   944,   942,     0,   546,     0,   947,     0,   627,
       0,   500,   949,     0,     0,     0,     0,     0,   446,     0,
     680,     0,     0,     0,     0,     0,     0,     0,     0,   679,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   725,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   774,     0,   627,     0,
       0,     0,   627,     0,     0,   446,     0,   446,     0,     0,
       0,   446,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   680,     0,     0,     0,
       0,     0,     0,     0,     0,   679,   447,     0,     0,     0,
       0,     0,     0,     0,     0,   446,   627,     0,     0,     0,
       0,     0,     0,     0,     0,   446,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   627,     0,     0,     0,     0,     0,     0,     0,     0,
     446,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   680,
       0,     0,     0,   680,     0,     0,     0,     0,   679,     0,
       0,     0,   679,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   627,     0,     0,     0,     0,     0,     0,
       0,     0,   446,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     627,     0,     0,     0,     0,     0,     0,     0,     0,   446,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   680,   680,
       0,   680,     0,   454,     0,     0,     0,   679,   679,     0,
     679,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     774,   627,     0,     0,     0,     0,     0,     0,     0,   446,
     446,     0,     0,   680,     0,     0,     0,     0,     0,     0,
       0,     0,   679,     0,     0,     0,     0,     0,     0,     0,
       0,   680,     0,     0,     0,     0,     0,     0,   680,     0,
     679,     0,     0,     0,     0,     0,     0,   679,   680,     0,
       0,     0,   680,     0,     0,     0,     0,   679,   680,     0,
       0,   679,     0,     0,     0,   496,     0,   679,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,   371,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,   373,   374,   375,   376,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   377,   378,
     379,   380,   381,   382,   383,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     384,   385,   386,   387,   388,   389,   390,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     391,     0,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,     0,
       0,   555,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,     0,   370,     0,   655,   656,     0,     0,     0,
       0,   657,   559,   560,   561,   562,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   372,   373,   374,   375,   376,
       0,     0,     0,     0,     0,   563,   564,   565,   566,   567,
     377,   378,   379,   380,   381,   382,   383,   658,   659,   660,
     661,     0,   662,   663,   664,   665,   666,   667,   668,   669,
     670,   671,   384,   385,   386,   387,   388,   389,   390,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   391,   672,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,     0,     0,   555,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,     0,   370,     0,   655,   840,     0,
       0,     0,     0,   657,   559,   560,   561,   562,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   372,   373,   374,
     375,   376,     0,     0,     0,     0,     0,   563,   564,   565,
     566,   567,   377,   378,   379,   380,   381,   382,   383,   658,
     659,   660,   661,     0,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   384,   385,   386,   387,   388,   389,
     390,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   391,   672,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,     0,     0,   555,   556,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   557,   558,     0,   370,     0,   655,
       0,     0,     0,     0,     0,   657,   559,   560,   561,   562,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372,
     373,   374,   375,   376,     0,     0,     0,     0,     0,   563,
     564,   565,   566,   567,   377,   378,   379,   380,   381,   382,
     383,   658,   659,   660,   661,     0,   662,   663,   664,   665,
     666,   667,   668,   669,   670,   671,   384,   385,   386,   387,
     388,   389,   390,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   391,   672,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     1,     2,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,     0,     0,   555,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,   558,     0,   370,
       0,   540,     0,     0,     0,     0,     0,   657,   559,   560,
     561,   562,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   372,   373,   374,   375,   376,     0,     0,     0,     0,
       0,   563,   564,   565,   566,   567,   377,   378,   379,   380,
     381,   382,   383,   658,   659,   660,   661,     0,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   384,   385,
     386,   387,   388,   389,   390,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   391,   672,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,     0,     0,   555,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   557,   558,
       0,   370,     0,     0,     0,     0,     0,     0,     0,   657,
     559,   560,   561,   562,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,   373,   374,   375,   376,     0,     0,
       0,     0,     0,   563,   564,   565,   566,   567,   377,   378,
     379,   380,   381,   382,   383,   658,   659,   660,   661,     0,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     384,   385,   386,   387,   388,   389,   390,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     391,   672,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,     0,
       0,   555,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,     0,   370,     0,     0,     0,     0,     0,     0,
       0,   657,   559,   560,   561,   562,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   372,   373,   374,   375,   376,
       0,     0,     0,     0,     0,   563,   564,   565,   566,   567,
     377,   378,   379,   380,   381,   382,   383,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   384,   385,   386,   387,   388,   389,   390,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   391,     0,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
       0,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,     0,     0,   555,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   559,   560,   561,   562,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   372,   373,   374,
     375,     0,     0,     0,     0,     0,     0,   563,   564,   565,
     566,   567,   377,   378,   379,   380,   381,   382,   383,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   384,   385,   386,   387,   388,   389,
     390,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   391,     0,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,   371,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372,
     373,   374,   375,   376,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   377,   378,   379,   380,   381,   382,
     383,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   384,   385,   386,   387,
     388,   389,   390,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   391,     0,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     1,     2,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,     0,     0,     0,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   372,   373,   374,   375,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   377,   378,   379,   380,
     381,   382,   383,   658,     0,     0,   661,     0,   662,   663,
       0,     0,   666,     0,     0,     0,     0,     0,   384,   385,
     386,   387,   388,   389,   390,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   391,     0,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,     0,     0,     0,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   488,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,   373,   374,   375,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   489,   377,   378,
     379,   380,   381,   382,   383,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     384,   385,   386,   387,   388,   389,   390,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     391,     0,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,     0,     0,     0,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   372,   373,   374,   375,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     377,   378,   379,   380,   381,   382,   383,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   384,   385,   386,   387,   388,   389,   390,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   391,     0,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
       0,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   543,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   372,   373,   374,
     375,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   377,   378,   379,   380,   381,   382,   383,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   384,   385,   386,   387,   388,   389,
     390,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   391,     0,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   773,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372,
     373,   374,   375,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   377,   378,   379,   380,   381,   382,
     383,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   384,   385,   386,   387,
     388,   389,   390,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   391,     0,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     1,     2,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,     0,     0,     0,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   778,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   372,   373,   374,   375,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   377,   378,   379,   380,
     381,   382,   383,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   384,   385,
     386,   387,   388,   389,   390,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   391,     0,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,     0,     0,     0,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   896,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,   373,   374,   375,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   377,   378,
     379,   380,   381,   382,   383,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     384,   385,   386,   387,   388,   389,   390,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     391,     0,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,     0,     0,     0,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   931,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   372,   373,   374,   375,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     377,   378,   379,   380,   381,   382,   383,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   384,   385,   386,   387,   388,   389,   390,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   391,     0,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
       0,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   976,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   372,   373,   374,
     375,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   377,   378,   379,   380,   381,   382,   383,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   384,   385,   386,   387,   388,   389,
     390,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   391,     0,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372,
     373,   374,   375,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   377,   378,   379,   380,   381,   382,
     383,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   384,   385,   386,   387,
     388,   389,   390,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   391,     0,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,    61,    62,    63,    64,    65,
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
     196,   197,   198,   199,     0,   201,     0,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,     0,     0,     0,     0,     0,     0,   363,     0,     0,
       0,   367,   368,   369,     0,     0,   555,   556,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   557,   558,     0,     0,     0,
     702,   849,     0,     0,     0,     0,     0,   559,   560,   561,
     562,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     563,   564,   565,   566,   567,   377,     0,     0,     0,     0,
     382,   383,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,     0,     0,   392,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   405,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
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
     199,     0,   201,     0,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,     0,     0,
       0,     0,     0,     0,   363,     0,     0,     0,   367,   368,
     369,     0,     0,   555,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,     0,     0,     0,   702,   966,     0,
       0,     0,     0,     0,   559,   560,   561,   562,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   563,   564,   565,
     566,   567,   377,     0,     0,     0,     0,   382,   383,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,     0,     0,   392,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   405,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     0,     0,    61,
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
     192,   193,   194,   195,   196,   197,   198,   199,     0,   201,
       0,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,     0,     0,     0,     0,     0,
       0,   363,     0,     0,     0,   367,   368,   369,     0,     0,
     555,   556,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   557,
     558,     0,     0,   638,     0,     0,     0,     0,     0,     0,
       0,   559,   560,   561,   562,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   563,   564,   565,   566,   567,   377,
       0,     0,     0,     0,   382,   383,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,     0,     0,   392,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   405,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,     0,     0,    61,    62,    63,    64,
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
     195,   196,   197,   198,   199,     0,   201,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,     0,     0,     0,     0,     0,     0,   363,     0,
       0,     0,   367,   368,   369,     0,     0,   555,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,   558,     0,     0,
       0,   702,     0,     0,     0,     0,     0,     0,   559,   560,
     561,   562,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   563,   564,   565,   566,   567,   377,     0,     0,     0,
       0,   382,   383,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,     0,     0,
     392,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   405,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     0,     0,    61,    62,    63,    64,    65,    66,    67,
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
     198,   199,     0,   201,     0,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,     0,
       0,     0,     0,     0,     0,   363,     0,     0,     0,   367,
     368,   369,     0,     0,   555,   556,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   557,   558,     0,     0,   806,     0,     0,
       0,     0,     0,     0,     0,   559,   560,   561,   562,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   563,   564,
     565,   566,   567,   377,     0,     0,     0,     0,   382,   383,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,     0,     0,   392,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     405,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,     0,
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
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
     201,     0,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,     0,     0,     0,     0,
       0,     0,   363,     0,     0,     0,   367,   368,   369,     0,
       0,   555,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   817,   559,   560,   561,   562,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   563,   564,   565,   566,   567,
     377,     0,     0,     0,     0,   382,   383,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,     0,     0,   392,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   405,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,     0,    61,    62,    63,
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
     194,   195,   196,   197,   198,   199,     0,   201,     0,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,     0,     0,     0,     0,     0,     0,   363,
       0,     0,     0,   367,   368,   369,     0,     0,   555,   556,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,   558,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   559,
     560,   561,   562,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   563,   564,   565,   566,   567,   377,     0,     0,
       0,     0,   382,   383,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,     0,
       0,   392,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   405,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,     0,    61,    62,    63,    64,    65,    66,
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
     197,   198,   199,     0,   201,     0,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,     0,     0,     0,   363,     0,     0,     0,
     367,   368,   369,     0,     0,   555,   556,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   557,   558,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   559,   560,   561,   562,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   563,
     564,   565,   566,   567,   377,     0,     0,     0,     0,   382,
     719,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,     0,     0,   392,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   405,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
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
       0,   201,     0,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,     0,     0,     0,
       0,     0,     0,   363,     0,     0,     0,   367,   368,   369,
       0,     0,   555,   556,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   557,   558,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   559,   560,   561,   562,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   563,   564,   565,   566,
     764,   377,     0,     0,     0,     0,   382,   383,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,     0,     0,   392,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   405,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,     0,     0,    61,    62,
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
     193,   194,   195,   196,   197,   198,   199,     0,   201,     0,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,     0,     0,     0,     0,     0,     0,
     363,     0,     0,     0,   367,   368,   369,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   377,     0,
       0,     0,     0,   382,   383,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   392
};

static const yytype_int16 yycheck[] =
{
       0,   454,     0,   435,   443,     0,   459,   537,   558,     0,
     558,     0,   686,   550,   603,   613,   487,   454,   809,   466,
     493,   608,   454,   494,   628,   630,   632,   459,   398,   890,
     619,   393,   404,   432,   381,   622,   376,   377,   698,   393,
     700,   401,   702,   393,   483,   705,   396,   479,   393,   372,
     373,   429,   589,   413,   432,   396,   394,   456,   396,   394,
     432,   500,   432,   404,   537,   403,   428,   429,   430,   431,
     417,   619,   412,   413,   395,   429,   547,   548,   608,   429,
     401,   981,   555,   556,   429,   374,   375,   394,   988,   619,
     951,   412,   622,   601,   396,   395,   633,   529,   998,   607,
     706,   609,   404,   396,   612,   394,   614,   396,   616,   617,
     403,   400,   412,   621,   396,   665,   397,   667,   394,   592,
     401,   403,   396,   653,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   396,   608,   396,   401,   394,   813,
     404,   403,   394,   403,   403,   395,   619,   426,   427,   622,
     395,   401,   395,   432,   601,   397,   401,   394,   401,   401,
     395,   698,   394,   700,   714,   702,   401,   395,   705,   774,
     617,   397,   395,   401,   394,   401,   395,   781,   401,   395,
     653,   718,   401,   429,   394,   401,   432,   626,   848,   461,
     462,   463,   464,   465,   466,   467,   628,   395,   395,   395,
     632,   395,   395,   401,   401,   401,   395,   401,   401,   395,
     395,  1002,   401,   395,   395,   401,   401,   395,   395,   401,
     401,   395,   395,   401,   401,   395,   395,   401,   401,   395,
     395,   401,   401,   395,   429,   401,   401,   432,   429,   401,
     399,   432,   401,   696,   918,   428,   429,   430,   431,   853,
     723,   394,   428,   429,   430,   431,   432,   378,   379,   696,
     792,   793,   794,   795,   696,   815,   788,   789,   429,   819,
     930,   432,   429,   401,   706,   432,   404,   429,   401,   402,
     432,   879,   880,   395,   429,   872,   873,   432,   429,   429,
     429,   432,   432,   432,   429,   401,   885,   432,   404,   401,
     837,   838,   404,   401,   775,   401,   404,   401,   404,   404,
     404,   848,   785,   786,   787,   788,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   401,   992,   406,  1008,   408,   412,   885,   404,   887,
     401,   402,   872,   873,   419,   420,   421,   790,   791,   781,
     409,   410,   411,   432,   432,   885,   398,   887,   796,   797,
     432,   398,   396,   432,   432,   398,   916,   396,   395,   919,
     432,   394,   404,   403,   432,   401,   395,   401,   403,   401,
     401,   401,   855,   401,   401,   401,   401,   401,   401,   400,
     395,   394,   404,   930,   403,   394,   432,   394,   380,   872,
     873,   393,   396,   396,   432,   382,   394,   397,   416,   415,
     414,   397,   885,   963,   887,   399,   394,   404,   394,   404,
     394,   853,   432,   404,   404,   404,   394,   402,   400,   395,
     432,   404,   982,   404,   403,   435,   401,   401,   401,   395,
     395,   978,   401,   443,   435,   397,   397,   997,   393,   393,
     399,   451,   443,   451,   454,   992,   451,   440,   890,   459,
     451,   459,   451,   454,   459,   432,   919,   429,   459,   469,
     395,   394,   398,   403,   395,   404,   398,   404,   398,   479,
     478,   399,   798,   483,   444,   799,   801,   919,   479,   800,
     802,   635,   483,   493,   803,   376,   893,   921,   987,   998,
     500,   999,   921,   963,   696,   451,   696,   624,   696,   500,
     963,   950,   870,   483,   873,   868,   877,   880,   479,   951,
     477,   885,   879,   875,    -1,   483,    -1,   883,    -1,   529,
      -1,   963,   887,    -1,    -1,    -1,    -1,    -1,   529,    -1,
     540,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   540,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   597,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   626,    -1,   628,    -1,
      -1,    -1,   632,    -1,    -1,   626,    -1,   628,    -1,    -1,
      -1,   632,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   686,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   686,   696,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   696,   706,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   706,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   781,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     781,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   809,
      -1,    -1,    -1,   813,    -1,    -1,    -1,    -1,   809,    -1,
      -1,    -1,   813,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   853,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   853,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     890,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   890,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   918,   919,
      -1,   921,    -1,   921,    -1,    -1,    -1,   918,   919,    -1,
     921,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     950,   951,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   950,
     951,    -1,    -1,   963,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   963,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   981,    -1,    -1,    -1,    -1,    -1,    -1,   988,    -1,
     981,    -1,    -1,    -1,    -1,    -1,    -1,   988,   998,    -1,
      -1,    -1,  1002,    -1,    -1,    -1,    -1,   998,  1008,    -1,
      -1,  1002,    -1,    -1,    -1,     0,    -1,  1008,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   418,   419,   420,   421,   422,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,   434,
     435,   436,   437,   438,   439,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     455,   456,   457,   458,   459,   460,   461,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     475,    -1,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,    -1,
      -1,   374,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     393,   394,    -1,   396,    -1,   398,   399,    -1,    -1,    -1,
      -1,   404,   405,   406,   407,   408,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   418,   419,   420,   421,   422,
      -1,    -1,    -1,    -1,    -1,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,    -1,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,    -1,    -1,   374,   375,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   393,   394,    -1,   396,    -1,   398,   399,    -1,
      -1,    -1,    -1,   404,   405,   406,   407,   408,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,   419,   420,
     421,   422,    -1,    -1,    -1,    -1,    -1,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,    -1,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,    -1,    -1,   374,   375,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   393,   394,    -1,   396,    -1,   398,
      -1,    -1,    -1,    -1,    -1,   404,   405,   406,   407,   408,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,
     419,   420,   421,   422,    -1,    -1,    -1,    -1,    -1,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,    -1,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,    -1,    -1,   374,   375,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   393,   394,    -1,   396,
      -1,   398,    -1,    -1,    -1,    -1,    -1,   404,   405,   406,
     407,   408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   418,   419,   420,   421,   422,    -1,    -1,    -1,    -1,
      -1,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,    -1,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,    -1,    -1,   374,
     375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,   394,
      -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,
     405,   406,   407,   408,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   418,   419,   420,   421,   422,    -1,    -1,
      -1,    -1,    -1,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,    -1,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,    -1,
      -1,   374,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     393,   394,    -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   404,   405,   406,   407,   408,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   418,   419,   420,   421,   422,
      -1,    -1,    -1,    -1,    -1,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,    -1,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,    -1,    -1,
      -1,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,    -1,    -1,   374,   375,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   393,   394,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   405,   406,   407,   408,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,   419,   420,
     421,    -1,    -1,    -1,    -1,    -1,    -1,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,    -1,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   396,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,
     419,   420,   421,   422,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   433,   434,   435,   436,   437,   438,
     439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   455,   456,   457,   458,
     459,   460,   461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,    -1,    -1,    -1,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   418,   419,   420,   421,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   433,   434,   435,   436,
     437,   438,   439,   440,    -1,    -1,   443,    -1,   445,   446,
      -1,    -1,   449,    -1,    -1,    -1,    -1,    -1,   455,   456,
     457,   458,   459,   460,   461,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,    -1,    -1,    -1,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   418,   419,   420,   421,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   432,   433,   434,
     435,   436,   437,   438,   439,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     455,   456,   457,   458,   459,   460,   461,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     475,    -1,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,    -1,    -1,    -1,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   418,   419,   420,   421,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433,   434,   435,   436,   437,   438,   439,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   455,   456,   457,   458,   459,   460,   461,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   475,    -1,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,    -1,    -1,
      -1,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   400,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,   419,   420,
     421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   433,   434,   435,   436,   437,   438,   439,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   455,   456,   457,   458,   459,   460,
     461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   475,    -1,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
      -1,    -1,    -1,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,
     419,   420,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   433,   434,   435,   436,   437,   438,
     439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   455,   456,   457,   458,
     459,   460,   461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
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
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,    -1,    -1,    -1,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   399,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   418,   419,   420,   421,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   433,   434,   435,   436,
     437,   438,   439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   455,   456,
     457,   458,   459,   460,   461,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,     3,     4,
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,    -1,    -1,    -1,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   399,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   418,   419,   420,   421,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,   434,
     435,   436,   437,   438,   439,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     455,   456,   457,   458,   459,   460,   461,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     475,    -1,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
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
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,    -1,    -1,    -1,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   399,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   418,   419,   420,   421,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     433,   434,   435,   436,   437,   438,   439,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   455,   456,   457,   458,   459,   460,   461,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   475,    -1,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
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
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,    -1,    -1,
      -1,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,   419,   420,
     421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   433,   434,   435,   436,   437,   438,   439,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   455,   456,   457,   458,   459,   460,
     461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   475,    -1,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
      -1,    -1,    -1,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,
     419,   420,   421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   433,   434,   435,   436,   437,   438,
     439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   455,   456,   457,   458,
     459,   460,   461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    66,    67,
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
     198,   199,   200,   201,    -1,   203,    -1,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,
      -1,   369,   370,   371,    -1,    -1,   374,   375,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   393,   394,    -1,    -1,    -1,
     398,   399,    -1,    -1,    -1,    -1,    -1,   405,   406,   407,
     408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     428,   429,   430,   431,   432,   433,    -1,    -1,    -1,    -1,
     438,   439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,    -1,    -1,   477,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   490,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
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
     201,    -1,   203,    -1,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,    -1,    -1,
      -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,   369,   370,
     371,    -1,    -1,   374,   375,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   393,   394,    -1,    -1,    -1,   398,   399,    -1,
      -1,    -1,    -1,    -1,   405,   406,   407,   408,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   428,   429,   430,
     431,   432,   433,    -1,    -1,    -1,    -1,   438,   439,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,    -1,    -1,   477,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   490,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
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
     194,   195,   196,   197,   198,   199,   200,   201,    -1,   203,
      -1,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,    -1,    -1,    -1,    -1,    -1,
      -1,   365,    -1,    -1,    -1,   369,   370,   371,    -1,    -1,
     374,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,
     394,    -1,    -1,   397,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   405,   406,   407,   408,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   428,   429,   430,   431,   432,   433,
      -1,    -1,    -1,    -1,   438,   439,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,    -1,    -1,   477,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   490,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    65,    66,
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
     197,   198,   199,   200,   201,    -1,   203,    -1,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,
      -1,    -1,   369,   370,   371,    -1,    -1,   374,   375,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   393,   394,    -1,    -1,
      -1,   398,    -1,    -1,    -1,    -1,    -1,    -1,   405,   406,
     407,   408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   428,   429,   430,   431,   432,   433,    -1,    -1,    -1,
      -1,   438,   439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,    -1,    -1,
     477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   490,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
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
     200,   201,    -1,   203,    -1,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,    -1,
      -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,   369,
     370,   371,    -1,    -1,   374,   375,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   393,   394,    -1,    -1,   397,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   405,   406,   407,   408,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   428,   429,
     430,   431,   432,   433,    -1,    -1,    -1,    -1,   438,   439,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,    -1,    -1,   477,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     490,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
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
     193,   194,   195,   196,   197,   198,   199,   200,   201,    -1,
     203,    -1,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,    -1,    -1,    -1,    -1,
      -1,    -1,   365,    -1,    -1,    -1,   369,   370,   371,    -1,
      -1,   374,   375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     393,   394,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   404,   405,   406,   407,   408,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,   429,   430,   431,   432,
     433,    -1,    -1,    -1,    -1,   438,   439,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,    -1,    -1,   477,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   490,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    65,
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
     196,   197,   198,   199,   200,   201,    -1,   203,    -1,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,    -1,    -1,    -1,    -1,    -1,    -1,   365,
      -1,    -1,    -1,   369,   370,   371,    -1,    -1,   374,   375,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,   394,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   405,
     406,   407,   408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   428,   429,   430,   431,   432,   433,    -1,    -1,
      -1,    -1,   438,   439,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,    -1,
      -1,   477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   490,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    66,    67,    68,
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
     199,   200,   201,    -1,   203,    -1,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
     369,   370,   371,    -1,    -1,   374,   375,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   393,   394,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   405,   406,   407,   408,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   428,
     429,   430,   431,   432,   433,    -1,    -1,    -1,    -1,   438,
     439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,    -1,    -1,   477,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   490,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
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
      -1,   203,    -1,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,    -1,    -1,    -1,
      -1,    -1,    -1,   365,    -1,    -1,    -1,   369,   370,   371,
      -1,    -1,   374,   375,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   393,   394,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   405,   406,   407,   408,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   428,   429,   430,   431,
     432,   433,    -1,    -1,    -1,    -1,   438,   439,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,    -1,    -1,   477,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   490,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
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
     195,   196,   197,   198,   199,   200,   201,    -1,   203,    -1,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,    -1,    -1,    -1,    -1,    -1,    -1,
     365,    -1,    -1,    -1,   369,   370,   371,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,
      -1,    -1,    -1,   438,   439,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   477
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
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
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     396,   404,   418,   419,   420,   421,   422,   433,   434,   435,
     436,   437,   438,   439,   455,   456,   457,   458,   459,   460,
     461,   475,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     546,   547,   550,   551,   552,   553,   557,   558,   559,   560,
     561,   562,   565,   566,   567,   568,   569,   571,   576,   577,
     578,   623,   624,   625,   627,   634,   638,   639,   645,   648,
     394,   394,   394,   394,   394,   394,   394,   394,   396,   577,
     398,   432,   394,   394,   404,   432,   404,   626,   395,   401,
     554,   555,   556,   566,   571,   401,   404,   432,   404,   432,
     549,   567,   571,   412,   573,   574,     0,   624,   551,   559,
     566,   404,   550,   432,   630,   631,   649,   650,   429,   432,
     630,   429,   630,   429,   630,   429,   630,   429,   630,   630,
     649,   429,   630,   426,   427,   432,   628,   629,   571,   580,
     398,   432,   456,   563,   564,   432,   570,   396,   404,   572,
     398,   602,   627,   400,   555,   554,   556,   432,   432,   394,
     403,   572,   398,   401,   404,   374,   375,   393,   394,   405,
     406,   407,   408,   428,   429,   430,   431,   432,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   516,   517,   518,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   569,   571,   575,   572,   395,   432,   404,
     403,   401,   395,   401,   395,   401,   403,   401,   401,   401,
     395,   401,   401,   401,   401,   401,   401,   401,   395,   401,
     395,   401,   394,   397,   401,   404,   566,   571,   581,   582,
     583,   586,   579,   403,   395,   401,   395,   401,   397,   527,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   571,   396,   404,   398,   399,   404,   440,   441,
     442,   443,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   476,   527,   540,   542,   544,   546,   550,   569,
     571,   591,   592,   593,   594,   595,   603,   604,   605,   606,
     609,   610,   613,   614,   615,   622,   627,   400,   403,   572,
     403,   572,   398,   542,   589,   403,   548,   432,   527,   527,
     544,   576,   374,   375,   396,   400,   395,   395,   401,   439,
     542,   394,   527,   401,   413,   627,   393,   396,   429,   631,
     649,   432,   650,   393,   428,   429,   430,   431,   635,   636,
     429,   540,   545,   637,   429,   428,   429,   430,   431,   640,
     641,   429,   428,   429,   430,   431,   516,   642,   643,   429,
     393,   644,   429,   649,   432,   545,   576,   646,   647,   429,
     545,   397,   629,   398,   571,   432,   587,   588,   399,   582,
     587,   581,   542,   564,   432,   409,   410,   411,   406,   408,
     372,   373,   376,   377,   412,   413,   378,   379,   416,   415,
     414,   380,   382,   381,   417,   397,   397,   540,   399,   596,
     394,   404,   404,   617,   394,   394,   404,   404,   544,   394,
     544,   402,   404,   404,   404,   404,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   403,   543,   401,   404,
     399,   592,   606,   610,   615,   400,   589,   589,   403,   399,
     589,   590,   589,   581,   395,   395,   519,   544,   432,   542,
     527,   393,   429,   632,   633,   395,   403,   395,   401,   395,
     401,   395,   401,   401,   395,   401,   395,   401,   395,   401,
     401,   395,   401,   401,   395,   401,   395,   401,   395,   395,
     584,   587,   572,   401,   404,   404,   399,   527,   527,   527,
     529,   529,   530,   530,   531,   531,   531,   531,   532,   532,
     533,   534,   535,   536,   537,   538,   541,   397,   603,   616,
     592,   618,   544,   404,   544,   402,   542,   542,   589,   399,
     401,   399,   527,   397,   397,   401,   397,   401,   636,   635,
     545,   637,   641,   640,   643,   642,   393,   644,   646,   647,
     566,   585,   586,   404,   588,   544,   597,   544,   559,   608,
     440,   591,   604,   619,   395,   395,   399,   589,   393,   429,
     395,   395,   395,   395,   395,   395,   399,   586,   402,   399,
     432,   395,   394,   608,   620,   621,   599,   600,   601,   607,
     611,   542,   403,   593,   598,   602,   544,   404,   395,   444,
     595,   593,   398,   589,   395,   544,   598,   599,   603,   612,
     404,   399
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   515,   516,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   518,   518,   518,   518,   518,   518,   519,
     520,   521,   522,   522,   523,   523,   524,   524,   525,   526,
     526,   526,   527,   527,   527,   527,   527,   528,   528,   528,
     528,   529,   529,   529,   529,   530,   530,   530,   531,   531,
     531,   532,   532,   532,   532,   532,   533,   533,   533,   534,
     534,   535,   535,   536,   536,   537,   537,   538,   538,   539,
     539,   540,   541,   540,   542,   542,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   544,   544,   545,
     546,   546,   546,   546,   546,   546,   546,   546,   546,   546,
     548,   547,   549,   549,   550,   550,   550,   550,   551,   551,
     552,   552,   552,   553,   554,   554,   554,   555,   555,   555,
     555,   556,   557,   557,   557,   557,   557,   558,   558,   558,
     558,   558,   559,   559,   560,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   562,   563,   563,   564,   564,
     564,   565,   566,   566,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   569,   570,   570,
     571,   571,   572,   572,   572,   572,   573,   573,   574,   575,
     575,   575,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   577,   577,   577,   579,   578,   580,   578,   581,   581,
     582,   582,   584,   583,   585,   585,   586,   586,   587,   587,
     588,   588,   589,   589,   589,   589,   590,   590,   591,   592,
     592,   593,   593,   593,   593,   593,   593,   593,   593,   594,
     595,   596,   597,   595,   598,   598,   600,   599,   601,   599,
     602,   602,   603,   603,   604,   604,   605,   605,   606,   607,
     607,   608,   608,   609,   609,   611,   610,   612,   612,   613,
     613,   614,   614,   616,   615,   617,   615,   618,   615,   619,
     619,   620,   620,   621,   621,   622,   622,   622,   622,   622,
     622,   622,   622,   623,   623,   624,   624,   624,   626,   625,
     627,   628,   628,   629,   629,   629,   629,   630,   630,   631,
     631,   632,   632,   633,   633,   634,   634,   634,   634,   634,
     634,   635,   635,   636,   636,   636,   636,   636,   637,   637,
     638,   638,   639,   639,   639,   639,   639,   639,   639,   639,
     640,   640,   641,   641,   641,   641,   642,   642,   643,   643,
     643,   643,   643,   644,   644,   645,   645,   645,   645,   646,
     646,   647,   647,   648,   648,   649,   649,   650,   650
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     2,     2,     1,
       1,     1,     2,     2,     2,     1,     2,     3,     2,     1,
       1,     1,     1,     2,     2,     2,     4,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     3,     2,     2,     4,     2,     3,     4,     2,     3,
       0,     6,     1,     3,     2,     3,     3,     4,     1,     1,
       2,     3,     5,     3,     2,     3,     4,     2,     1,     2,
       1,     1,     1,     3,     4,     6,     5,     1,     2,     3,
       5,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     1,     3,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     3,
       2,     3,     2,     3,     3,     4,     1,     0,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     0,     6,     0,     5,     1,     2,
       1,     3,     0,     5,     1,     2,     3,     4,     1,     3,
       1,     2,     1,     3,     4,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     0,     0,     5,     1,     1,     0,     2,     0,     2,
       2,     3,     1,     2,     1,     2,     1,     2,     5,     3,
       1,     1,     4,     1,     2,     0,     8,     0,     1,     3,
       2,     1,     2,     0,     6,     0,     8,     0,     7,     1,
       1,     1,     0,     2,     3,     2,     2,     2,     3,     2,
       2,     2,     2,     1,     2,     1,     1,     1,     0,     3,
       5,     1,     3,     1,     4,     1,     1,     1,     3,     5,
       5,     1,     3,     1,     3,     4,     6,     6,     8,     6,
       8,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       4,     6,     4,     6,     6,     8,     6,     8,     6,     8,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     6,     8,     4,     6,     1,
       3,     1,     1,     4,     6,     1,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (pParseContext);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, pParseContext);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, glslang::TParseContext* pParseContext)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], pParseContext);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pParseContext); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
{
  YY_USE (yyvaluep);
  YY_USE (pParseContext);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (glslang::TParseContext* pParseContext)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, parseContext);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* variable_identifier: IDENTIFIER  */
#line 371 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[0].lex).loc, (yyvsp[0].lex).symbol, (yyvsp[0].lex).string);
    }
#line 5899 "MachineIndependent/glslang_tab.cpp"
    break;

  case 3: /* primary_expression: variable_identifier  */
#line 377 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5907 "MachineIndependent/glslang_tab.cpp"
    break;

  case 4: /* primary_expression: LEFT_PAREN expression RIGHT_PAREN  */
#line 380 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 5917 "MachineIndependent/glslang_tab.cpp"
    break;

  case 5: /* primary_expression: FLOATCONSTANT  */
#line 385 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 5925 "MachineIndependent/glslang_tab.cpp"
    break;

  case 6: /* primary_expression: INTCONSTANT  */
#line 388 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 5933 "MachineIndependent/glslang_tab.cpp"
    break;

  case 7: /* primary_expression: UINTCONSTANT  */
#line 391 "MachineIndependent/glslang.y"
                   {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 5942 "MachineIndependent/glslang_tab.cpp"
    break;

  case 8: /* primary_expression: BOOLCONSTANT  */
#line 395 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 5950 "MachineIndependent/glslang_tab.cpp"
    break;

  case 9: /* primary_expression: STRING_LITERAL  */
#line 398 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true);
    }
#line 5958 "MachineIndependent/glslang_tab.cpp"
    break;

  case 10: /* primary_expression: INT32CONSTANT  */
#line 401 "MachineIndependent/glslang.y"
                    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 5967 "MachineIndependent/glslang_tab.cpp"
    break;

  case 11: /* primary_expression: UINT32CONSTANT  */
#line 405 "MachineIndependent/glslang.y"
                     {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 5976 "MachineIndependent/glslang_tab.cpp"
    break;

  case 12: /* primary_expression: INT64CONSTANT  */
#line 409 "MachineIndependent/glslang.y"
                    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 5985 "MachineIndependent/glslang_tab.cpp"
    break;

  case 13: /* primary_expression: UINT64CONSTANT  */
#line 413 "MachineIndependent/glslang.y"
                     {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 5994 "MachineIndependent/glslang_tab.cpp"
    break;

  case 14: /* primary_expression: INT16CONSTANT  */
#line 417 "MachineIndependent/glslang.y"
                    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 6003 "MachineIndependent/glslang_tab.cpp"
    break;

  case 15: /* primary_expression: UINT16CONSTANT  */
#line 421 "MachineIndependent/glslang.y"
                     {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 6012 "MachineIndependent/glslang_tab.cpp"
    break;

  case 16: /* primary_expression: DOUBLECONSTANT  */
#line 425 "MachineIndependent/glslang.y"
                     {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double literal");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 6023 "MachineIndependent/glslang_tab.cpp"
    break;

  case 17: /* primary_expression: FLOAT16CONSTANT  */
#line 431 "MachineIndependent/glslang.y"
                      {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
    }
#line 6032 "MachineIndependent/glslang_tab.cpp"
    break;

  case 18: /* primary_expression: FLOATE2M1CONSTANT  */
#line 435 "MachineIndependent/glslang.y"
                        {
        parseContext.floate2m1ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m1 literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloatE2M1, (yyvsp[0].lex).loc, true);
    }
#line 6041 "MachineIndependent/glslang_tab.cpp"
    break;

  case 19: /* primary_expression: FLOATE3M2CONSTANT  */
#line 439 "MachineIndependent/glslang.y"
                        {
        parseContext.floate3m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe3m2 literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloatE3M2, (yyvsp[0].lex).loc, true);
    }
#line 6050 "MachineIndependent/glslang_tab.cpp"
    break;

  case 20: /* primary_expression: FLOATE2M3CONSTANT  */
#line 443 "MachineIndependent/glslang.y"
                        {
        parseContext.floate2m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m3 literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloatE2M3, (yyvsp[0].lex).loc, true);
    }
#line 6059 "MachineIndependent/glslang_tab.cpp"
    break;

  case 21: /* primary_expression: FLOATUE8M0CONSTANT  */
#line 447 "MachineIndependent/glslang.y"
                         {
        parseContext.floatue8m0ScalarVectorCheck((yyvsp[0].lex).loc, "fue8m0 literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloatUE8M0, (yyvsp[0].lex).loc, true);
    }
#line 6068 "MachineIndependent/glslang_tab.cpp"
    break;

  case 22: /* primary_expression: FLOATMXINT8CONSTANT  */
#line 451 "MachineIndependent/glslang.y"
                          {
        parseContext.floatmxint8ScalarVectorCheck((yyvsp[0].lex).loc, "fmxint8 literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloatMXINT8, (yyvsp[0].lex).loc, true);
    }
#line 6077 "MachineIndependent/glslang_tab.cpp"
    break;

  case 23: /* postfix_expression: primary_expression  */
#line 458 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6085 "MachineIndependent/glslang_tab.cpp"
    break;

  case 24: /* postfix_expression: postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET  */
#line 461 "MachineIndependent/glslang.y"
                                                                       {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 6093 "MachineIndependent/glslang_tab.cpp"
    break;

  case 25: /* postfix_expression: function_call  */
#line 464 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6101 "MachineIndependent/glslang_tab.cpp"
    break;

  case 26: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 467 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 6109 "MachineIndependent/glslang_tab.cpp"
    break;

  case 27: /* postfix_expression: postfix_expression INC_OP  */
#line 470 "MachineIndependent/glslang.y"
                                {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 6119 "MachineIndependent/glslang_tab.cpp"
    break;

  case 28: /* postfix_expression: postfix_expression DEC_OP  */
#line 475 "MachineIndependent/glslang.y"
                                {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 6129 "MachineIndependent/glslang_tab.cpp"
    break;

  case 29: /* integer_expression: expression  */
#line 483 "MachineIndependent/glslang.y"
                 {
        parseContext.arrayIndexCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6138 "MachineIndependent/glslang_tab.cpp"
    break;

  case 30: /* function_call: function_call_or_method  */
#line 490 "MachineIndependent/glslang.y"
                              {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 6147 "MachineIndependent/glslang_tab.cpp"
    break;

  case 31: /* function_call_or_method: function_call_generic  */
#line 497 "MachineIndependent/glslang.y"
                            {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 6155 "MachineIndependent/glslang_tab.cpp"
    break;

  case 32: /* function_call_generic: function_call_header_with_parameters RIGHT_PAREN  */
#line 503 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6164 "MachineIndependent/glslang_tab.cpp"
    break;

  case 33: /* function_call_generic: function_call_header_no_parameters RIGHT_PAREN  */
#line 507 "MachineIndependent/glslang.y"
                                                     {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6173 "MachineIndependent/glslang_tab.cpp"
    break;

  case 34: /* function_call_header_no_parameters: function_call_header VOID  */
#line 514 "MachineIndependent/glslang.y"
                                {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 6181 "MachineIndependent/glslang_tab.cpp"
    break;

  case 35: /* function_call_header_no_parameters: function_call_header  */
#line 517 "MachineIndependent/glslang.y"
                           {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 6189 "MachineIndependent/glslang_tab.cpp"
    break;

  case 36: /* function_call_header_with_parameters: function_call_header assignment_expression  */
#line 523 "MachineIndependent/glslang.y"
                                                 {
        if (parseContext.spvVersion.vulkan > 0
            && parseContext.spvVersion.vulkanRelaxed
            && (yyvsp[0].interm.intermTypedNode)->getType().containsOpaque())
        {
            (yyval.interm).intermNode = parseContext.vkRelaxedRemapFunctionArgument((yyval.interm).loc, (yyvsp[-1].interm).function, (yyvsp[0].interm.intermTypedNode));
            (yyval.interm).function = (yyvsp[-1].interm).function;
        }
        else
        {
            TParameter param = { 0, new TType, {} };
            param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());

            (yyvsp[-1].interm).function->addParameter(param);
            (yyval.interm).function = (yyvsp[-1].interm).function;
            (yyval.interm).intermNode = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6212 "MachineIndependent/glslang_tab.cpp"
    break;

  case 37: /* function_call_header_with_parameters: function_call_header_with_parameters COMMA assignment_expression  */
#line 541 "MachineIndependent/glslang.y"
                                                                       {
        if (parseContext.spvVersion.vulkan > 0
            && parseContext.spvVersion.vulkanRelaxed
            && (yyvsp[0].interm.intermTypedNode)->getType().containsOpaque())
        {
            TIntermNode* remappedNode = parseContext.vkRelaxedRemapFunctionArgument((yyvsp[-1].lex).loc, (yyvsp[-2].interm).function, (yyvsp[0].interm.intermTypedNode));
            if (remappedNode == (yyvsp[0].interm.intermTypedNode))
                (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
            else
                (yyval.interm).intermNode = parseContext.intermediate.mergeAggregate((yyvsp[-2].interm).intermNode, remappedNode, (yyvsp[-1].lex).loc);
            (yyval.interm).function = (yyvsp[-2].interm).function;
        }
        else
        {
            TParameter param = { 0, new TType, {} };
            param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());

            (yyvsp[-2].interm).function->addParameter(param);
            (yyval.interm).function = (yyvsp[-2].interm).function;
            (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        }
    }
#line 6239 "MachineIndependent/glslang_tab.cpp"
    break;

  case 38: /* function_call_header: function_identifier LEFT_PAREN  */
#line 566 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 6247 "MachineIndependent/glslang_tab.cpp"
    break;

  case 39: /* function_identifier: type_specifier  */
#line 574 "MachineIndependent/glslang.y"
                     {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 6257 "MachineIndependent/glslang_tab.cpp"
    break;

  case 40: /* function_identifier: postfix_expression  */
#line 579 "MachineIndependent/glslang.y"
                         {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), method->getType(), EOpArrayLength);
            (yyval.interm).intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = (yyvsp[0].interm.intermTypedNode)->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                (yyval.interm).function = function;
            } else
                parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ((yyval.interm).function == 0) {
            // error recover
            TString* empty = NewPoolTString("");
            (yyval.interm).function = new TFunction(empty, TType(EbtVoid), EOpNull);
        }
    }
#line 6289 "MachineIndependent/glslang_tab.cpp"
    break;

  case 41: /* function_identifier: non_uniform_qualifier  */
#line 606 "MachineIndependent/glslang.y"
                            {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 6299 "MachineIndependent/glslang_tab.cpp"
    break;

  case 42: /* unary_expression: postfix_expression  */
#line 614 "MachineIndependent/glslang.y"
                         {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 6310 "MachineIndependent/glslang_tab.cpp"
    break;

  case 43: /* unary_expression: INC_OP unary_expression  */
#line 620 "MachineIndependent/glslang.y"
                              {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 6319 "MachineIndependent/glslang_tab.cpp"
    break;

  case 44: /* unary_expression: DEC_OP unary_expression  */
#line 624 "MachineIndependent/glslang.y"
                              {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 6328 "MachineIndependent/glslang_tab.cpp"
    break;

  case 45: /* unary_expression: unary_operator unary_expression  */
#line 628 "MachineIndependent/glslang.y"
                                      {
        if ((yyvsp[-1].interm).op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch((yyvsp[-1].interm).op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].interm).loc, errorOp, (yyvsp[-1].interm).op, (yyvsp[0].interm.intermTypedNode));
        } else {
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
            if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
                (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
        }
    }
#line 6349 "MachineIndependent/glslang_tab.cpp"
    break;

  case 46: /* unary_expression: LEFT_PAREN type_specifier_nonarray RIGHT_PAREN unary_expression  */
#line 644 "MachineIndependent/glslang.y"
                                                                      {
        (yyval.interm.intermTypedNode) = parseContext.handleTypeCast((yyvsp[-3].lex).loc, new TType((yyvsp[-2].interm.type)), (yyvsp[0].interm.intermTypedNode));
    }
#line 6357 "MachineIndependent/glslang_tab.cpp"
    break;

  case 47: /* unary_operator: PLUS  */
#line 651 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 6363 "MachineIndependent/glslang_tab.cpp"
    break;

  case 48: /* unary_operator: DASH  */
#line 652 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 6369 "MachineIndependent/glslang_tab.cpp"
    break;

  case 49: /* unary_operator: BANG  */
#line 653 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 6375 "MachineIndependent/glslang_tab.cpp"
    break;

  case 50: /* unary_operator: TILDE  */
#line 654 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 6382 "MachineIndependent/glslang_tab.cpp"
    break;

  case 51: /* multiplicative_expression: unary_expression  */
#line 660 "MachineIndependent/glslang.y"
                       { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6388 "MachineIndependent/glslang_tab.cpp"
    break;

  case 52: /* multiplicative_expression: multiplicative_expression STAR unary_expression  */
#line 661 "MachineIndependent/glslang.y"
                                                      {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6398 "MachineIndependent/glslang_tab.cpp"
    break;

  case 53: /* multiplicative_expression: multiplicative_expression SLASH unary_expression  */
#line 666 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6408 "MachineIndependent/glslang_tab.cpp"
    break;

  case 54: /* multiplicative_expression: multiplicative_expression PERCENT unary_expression  */
#line 671 "MachineIndependent/glslang.y"
                                                         {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6419 "MachineIndependent/glslang_tab.cpp"
    break;

  case 55: /* additive_expression: multiplicative_expression  */
#line 680 "MachineIndependent/glslang.y"
                                { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6425 "MachineIndependent/glslang_tab.cpp"
    break;

  case 56: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 681 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6435 "MachineIndependent/glslang_tab.cpp"
    break;

  case 57: /* additive_expression: additive_expression DASH multiplicative_expression  */
#line 686 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6445 "MachineIndependent/glslang_tab.cpp"
    break;

  case 58: /* shift_expression: additive_expression  */
#line 694 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6451 "MachineIndependent/glslang_tab.cpp"
    break;

  case 59: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 695 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6462 "MachineIndependent/glslang_tab.cpp"
    break;

  case 60: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 701 "MachineIndependent/glslang.y"
                                                    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6473 "MachineIndependent/glslang_tab.cpp"
    break;

  case 61: /* relational_expression: shift_expression  */
#line 710 "MachineIndependent/glslang.y"
                       { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6479 "MachineIndependent/glslang_tab.cpp"
    break;

  case 62: /* relational_expression: relational_expression LEFT_ANGLE shift_expression  */
#line 711 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6489 "MachineIndependent/glslang_tab.cpp"
    break;

  case 63: /* relational_expression: relational_expression RIGHT_ANGLE shift_expression  */
#line 716 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6499 "MachineIndependent/glslang_tab.cpp"
    break;

  case 64: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 721 "MachineIndependent/glslang.y"
                                                    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6509 "MachineIndependent/glslang_tab.cpp"
    break;

  case 65: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 726 "MachineIndependent/glslang.y"
                                                    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6519 "MachineIndependent/glslang_tab.cpp"
    break;

  case 66: /* equality_expression: relational_expression  */
#line 734 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6525 "MachineIndependent/glslang_tab.cpp"
    break;

  case 67: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 735 "MachineIndependent/glslang.y"
                                                       {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6539 "MachineIndependent/glslang_tab.cpp"
    break;

  case 68: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 744 "MachineIndependent/glslang.y"
                                                      {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6553 "MachineIndependent/glslang_tab.cpp"
    break;

  case 69: /* and_expression: equality_expression  */
#line 756 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6559 "MachineIndependent/glslang_tab.cpp"
    break;

  case 70: /* and_expression: and_expression AMPERSAND equality_expression  */
#line 757 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6570 "MachineIndependent/glslang_tab.cpp"
    break;

  case 71: /* exclusive_or_expression: and_expression  */
#line 766 "MachineIndependent/glslang.y"
                     { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6576 "MachineIndependent/glslang_tab.cpp"
    break;

  case 72: /* exclusive_or_expression: exclusive_or_expression CARET and_expression  */
#line 767 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6587 "MachineIndependent/glslang_tab.cpp"
    break;

  case 73: /* inclusive_or_expression: exclusive_or_expression  */
#line 776 "MachineIndependent/glslang.y"
                              { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6593 "MachineIndependent/glslang_tab.cpp"
    break;

  case 74: /* inclusive_or_expression: inclusive_or_expression VERTICAL_BAR exclusive_or_expression  */
#line 777 "MachineIndependent/glslang.y"
                                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6604 "MachineIndependent/glslang_tab.cpp"
    break;

  case 75: /* logical_and_expression: inclusive_or_expression  */
#line 786 "MachineIndependent/glslang.y"
                              { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6610 "MachineIndependent/glslang_tab.cpp"
    break;

  case 76: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 787 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6620 "MachineIndependent/glslang_tab.cpp"
    break;

  case 77: /* logical_xor_expression: logical_and_expression  */
#line 795 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6626 "MachineIndependent/glslang_tab.cpp"
    break;

  case 78: /* logical_xor_expression: logical_xor_expression XOR_OP logical_and_expression  */
#line 796 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6636 "MachineIndependent/glslang_tab.cpp"
    break;

  case 79: /* logical_or_expression: logical_xor_expression  */
#line 804 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6642 "MachineIndependent/glslang_tab.cpp"
    break;

  case 80: /* logical_or_expression: logical_or_expression OR_OP logical_xor_expression  */
#line 805 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6652 "MachineIndependent/glslang_tab.cpp"
    break;

  case 81: /* conditional_expression: logical_or_expression  */
#line 813 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6658 "MachineIndependent/glslang_tab.cpp"
    break;

  case 82: /* $@1: %empty  */
#line 814 "MachineIndependent/glslang.y"
                                     {
        ++parseContext.controlFlowNestingLevel;
    }
#line 6666 "MachineIndependent/glslang_tab.cpp"
    break;

  case 83: /* conditional_expression: logical_or_expression QUESTION $@1 expression COLON assignment_expression  */
#line 817 "MachineIndependent/glslang.y"
                                             {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-4].lex).loc, "?", (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[-5].interm.intermTypedNode), (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-4].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-4].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6683 "MachineIndependent/glslang_tab.cpp"
    break;

  case 84: /* assignment_expression: conditional_expression  */
#line 832 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6689 "MachineIndependent/glslang_tab.cpp"
    break;

  case 85: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 833 "MachineIndependent/glslang.y"
                                                                 {
        parseContext.arrayObjectCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.storage16BitAssignmentCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.addAssign((yyvsp[-1].interm).loc, (yyvsp[-1].interm).op, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
        }
    }
#line 6707 "MachineIndependent/glslang_tab.cpp"
    break;

  case 86: /* assignment_operator: EQUAL  */
#line 849 "MachineIndependent/glslang.y"
            {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 6716 "MachineIndependent/glslang_tab.cpp"
    break;

  case 87: /* assignment_operator: MUL_ASSIGN  */
#line 853 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 6725 "MachineIndependent/glslang_tab.cpp"
    break;

  case 88: /* assignment_operator: DIV_ASSIGN  */
#line 857 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 6734 "MachineIndependent/glslang_tab.cpp"
    break;

  case 89: /* assignment_operator: MOD_ASSIGN  */
#line 861 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 6744 "MachineIndependent/glslang_tab.cpp"
    break;

  case 90: /* assignment_operator: ADD_ASSIGN  */
#line 866 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 6753 "MachineIndependent/glslang_tab.cpp"
    break;

  case 91: /* assignment_operator: SUB_ASSIGN  */
#line 870 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 6762 "MachineIndependent/glslang_tab.cpp"
    break;

  case 92: /* assignment_operator: LEFT_ASSIGN  */
#line 874 "MachineIndependent/glslang.y"
                  {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 6771 "MachineIndependent/glslang_tab.cpp"
    break;

  case 93: /* assignment_operator: RIGHT_ASSIGN  */
#line 878 "MachineIndependent/glslang.y"
                   {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 6780 "MachineIndependent/glslang_tab.cpp"
    break;

  case 94: /* assignment_operator: AND_ASSIGN  */
#line 882 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 6789 "MachineIndependent/glslang_tab.cpp"
    break;

  case 95: /* assignment_operator: XOR_ASSIGN  */
#line 886 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 6798 "MachineIndependent/glslang_tab.cpp"
    break;

  case 96: /* assignment_operator: OR_ASSIGN  */
#line 890 "MachineIndependent/glslang.y"
                {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 6807 "MachineIndependent/glslang_tab.cpp"
    break;

  case 97: /* expression: assignment_expression  */
#line 897 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6815 "MachineIndependent/glslang_tab.cpp"
    break;

  case 98: /* expression: expression COMMA assignment_expression  */
#line 900 "MachineIndependent/glslang.y"
                                             {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6828 "MachineIndependent/glslang_tab.cpp"
    break;

  case 99: /* constant_expression: conditional_expression  */
#line 911 "MachineIndependent/glslang.y"
                             {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6837 "MachineIndependent/glslang_tab.cpp"
    break;

  case 100: /* declaration: function_prototype SEMICOLON  */
#line 918 "MachineIndependent/glslang.y"
                                   {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 6847 "MachineIndependent/glslang_tab.cpp"
    break;

  case 101: /* declaration: spirv_instruction_qualifier function_prototype SEMICOLON  */
#line 923 "MachineIndependent/glslang.y"
                                                               {
        parseContext.requireExtensions((yyvsp[-1].interm).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V instruction qualifier");
        (yyvsp[-1].interm).function->setSpirvInstruction(*(yyvsp[-2].interm.spirvInst)); // Attach SPIR-V intruction qualifier
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 6859 "MachineIndependent/glslang_tab.cpp"
    break;

  case 102: /* declaration: spirv_execution_mode_qualifier SEMICOLON  */
#line 930 "MachineIndependent/glslang.y"
                                               {
        parseContext.globalCheck((yyvsp[0].lex).loc, "SPIR-V execution mode qualifier");
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V execution mode qualifier");
        (yyval.interm.intermNode) = 0;
    }
#line 6869 "MachineIndependent/glslang_tab.cpp"
    break;

  case 103: /* declaration: init_declarator_list SEMICOLON  */
#line 935 "MachineIndependent/glslang.y"
                                     {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 6879 "MachineIndependent/glslang_tab.cpp"
    break;

  case 104: /* declaration: PRECISION precision_qualifier type_specifier SEMICOLON  */
#line 940 "MachineIndependent/glslang.y"
                                                             {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");
        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 6891 "MachineIndependent/glslang_tab.cpp"
    break;

  case 105: /* declaration: block_structure SEMICOLON  */
#line 947 "MachineIndependent/glslang.y"
                                {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
    }
#line 6899 "MachineIndependent/glslang_tab.cpp"
    break;

  case 106: /* declaration: block_structure IDENTIFIER SEMICOLON  */
#line 950 "MachineIndependent/glslang.y"
                                           {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
    }
#line 6907 "MachineIndependent/glslang_tab.cpp"
    break;

  case 107: /* declaration: block_structure IDENTIFIER array_specifier SEMICOLON  */
#line 953 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
    }
#line 6915 "MachineIndependent/glslang_tab.cpp"
    break;

  case 108: /* declaration: type_qualifier SEMICOLON  */
#line 956 "MachineIndependent/glslang.y"
                               {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 6925 "MachineIndependent/glslang_tab.cpp"
    break;

  case 109: /* declaration: type_qualifier identifier_list SEMICOLON  */
#line 961 "MachineIndependent/glslang.y"
                                               {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 6935 "MachineIndependent/glslang_tab.cpp"
    break;

  case 110: /* $@2: %empty  */
#line 969 "MachineIndependent/glslang.y"
                                           { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 6941 "MachineIndependent/glslang_tab.cpp"
    break;

  case 111: /* block_structure: type_qualifier IDENTIFIER LEFT_BRACE $@2 struct_declaration_list RIGHT_BRACE  */
#line 969 "MachineIndependent/glslang.y"
                                                                                                                          {
        --parseContext.blockNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 6955 "MachineIndependent/glslang_tab.cpp"
    break;

  case 112: /* identifier_list: IDENTIFIER  */
#line 981 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 6964 "MachineIndependent/glslang_tab.cpp"
    break;

  case 113: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 985 "MachineIndependent/glslang.y"
                                       {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 6973 "MachineIndependent/glslang_tab.cpp"
    break;

  case 114: /* function_prototype: function_declarator RIGHT_PAREN  */
#line 992 "MachineIndependent/glslang.y"
                                       {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6983 "MachineIndependent/glslang_tab.cpp"
    break;

  case 115: /* function_prototype: function_declarator RIGHT_PAREN attribute  */
#line 997 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm).function = (yyvsp[-2].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        const char * extensions[3] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence, E_GL_EXT_function_control_attributes };
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 3, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyval.interm).function, *(yyvsp[0].interm.attributes));
    }
#line 6996 "MachineIndependent/glslang_tab.cpp"
    break;

  case 116: /* function_prototype: attribute function_declarator RIGHT_PAREN  */
#line 1005 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        const char * extensions[3] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence, E_GL_EXT_function_control_attributes };
        parseContext.requireExtensions((yyvsp[0].lex).loc, 3, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[0].lex).loc, *(yyval.interm).function, *(yyvsp[-2].interm.attributes));
    }
#line 7009 "MachineIndependent/glslang_tab.cpp"
    break;

  case 117: /* function_prototype: attribute function_declarator RIGHT_PAREN attribute  */
#line 1013 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm).function = (yyvsp[-2].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        const char * extensions[3] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence, E_GL_EXT_function_control_attributes };
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 3, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyval.interm).function, *(yyvsp[-3].interm.attributes));
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyval.interm).function, *(yyvsp[0].interm.attributes));
    }
#line 7023 "MachineIndependent/glslang_tab.cpp"
    break;

  case 118: /* function_declarator: function_header  */
#line 1025 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 7031 "MachineIndependent/glslang_tab.cpp"
    break;

  case 119: /* function_declarator: function_header_with_parameters  */
#line 1028 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 7039 "MachineIndependent/glslang_tab.cpp"
    break;

  case 120: /* function_header_with_parameters: function_header parameter_declaration  */
#line 1035 "MachineIndependent/glslang.y"
                                            {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
        {
            if (!(parseContext.spvVersion.vulkan > 0 && parseContext.spvVersion.vulkanRelaxed))
                (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
            else
                parseContext.vkRelaxedRemapFunctionParameter((yyvsp[-1].interm.function), (yyvsp[0].interm).param);
        }
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 7057 "MachineIndependent/glslang_tab.cpp"
    break;

  case 121: /* function_header_with_parameters: function_header_with_parameters COMMA parameter_declaration  */
#line 1048 "MachineIndependent/glslang.y"
                                                                  {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ((yyvsp[0].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[-1].lex).loc, "cannot be an argument type except for '(void)'", "void", "");
            delete (yyvsp[0].interm).param.type;
        } else {
            // Add the parameter
            (yyval.interm.function) = (yyvsp[-2].interm.function);
            if (!(parseContext.spvVersion.vulkan > 0 && parseContext.spvVersion.vulkanRelaxed))
                (yyvsp[-2].interm.function)->addParameter((yyvsp[0].interm).param);
            else
                parseContext.vkRelaxedRemapFunctionParameter((yyvsp[-2].interm.function), (yyvsp[0].interm).param);
        }
    }
#line 7082 "MachineIndependent/glslang_tab.cpp"
    break;

  case 122: /* function_header_with_parameters: function_header_with_parameters COMMA DOT DOT DOT  */
#line 1068 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm.function) = (yyvsp[-4].interm.function);
        parseContext.makeVariadic((yyvsp[-4].interm.function), (yyvsp[-2].lex).loc);
    }
#line 7091 "MachineIndependent/glslang_tab.cpp"
    break;

  case 123: /* function_header: fully_specified_type IDENTIFIER LEFT_PAREN  */
#line 1075 "MachineIndependent/glslang.y"
                                                 {
        if ((yyvsp[-2].interm.type).qualifier.storage != EvqGlobal && (yyvsp[-2].interm.type).qualifier.storage != EvqTemporary) {
            parseContext.error((yyvsp[-1].lex).loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString((yyvsp[-2].interm.type).qualifier.storage), "");
        }
        if ((yyvsp[-2].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type((yyvsp[-2].interm.type));

        // Potentially rename shader entry point function.  No-op most of the time.
        parseContext.renameShaderFunction((yyvsp[-1].lex).string);

        // Make the function
        function = new TFunction((yyvsp[-1].lex).string, type);
        (yyval.interm.function) = function;
    }
#line 7115 "MachineIndependent/glslang_tab.cpp"
    break;

  case 124: /* parameter_declarator: type_specifier IDENTIFIER  */
#line 1098 "MachineIndependent/glslang.y"
                                {
        if ((yyvsp[-1].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-1].interm.type).loc, *(yyvsp[-1].interm.type).arraySizes);
        }
        if ((yyvsp[-1].interm.type).basicType == EbtVoid) {
            parseContext.error((yyvsp[0].lex).loc, "illegal use of type 'void'", (yyvsp[0].lex).string->c_str(), "");
        }
        parseContext.reservedErrorCheck((yyvsp[0].lex).loc, *(yyvsp[0].lex).string);

        TParameter param = {(yyvsp[0].lex).string, new TType((yyvsp[-1].interm.type)), {}};
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).param = param;
    }
#line 7135 "MachineIndependent/glslang_tab.cpp"
    break;

  case 125: /* parameter_declarator: type_specifier IDENTIFIER array_specifier  */
#line 1113 "MachineIndependent/glslang.y"
                                                {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }
        TType* type = new TType((yyvsp[-2].interm.type));
        type->transferArraySizes((yyvsp[0].interm).arraySizes);
        type->copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);

        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, type->getArraySizes());
        parseContext.arraySizeRequiredCheck((yyvsp[0].interm).loc, *(yyvsp[0].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string);

        TParameter param = { (yyvsp[-1].lex).string, type, {} };

        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).param = param;
    }
#line 7159 "MachineIndependent/glslang_tab.cpp"
    break;

  case 126: /* parameter_declarator: type_specifier IDENTIFIER EQUAL initializer  */
#line 1132 "MachineIndependent/glslang.y"
                                                  {
        TParameter param = parseContext.getParamWithDefault((yyvsp[-3].interm.type), (yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).param = param;
    }
#line 7169 "MachineIndependent/glslang_tab.cpp"
    break;

  case 127: /* parameter_declaration: type_qualifier parameter_declarator  */
#line 1143 "MachineIndependent/glslang.y"
                                          {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 7185 "MachineIndependent/glslang_tab.cpp"
    break;

  case 128: /* parameter_declaration: parameter_declarator  */
#line 1154 "MachineIndependent/glslang.y"
                           {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());
    }
#line 7197 "MachineIndependent/glslang_tab.cpp"
    break;

  case 129: /* parameter_declaration: type_qualifier parameter_type_specifier  */
#line 1164 "MachineIndependent/glslang.y"
                                              {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 7212 "MachineIndependent/glslang_tab.cpp"
    break;

  case 130: /* parameter_declaration: parameter_type_specifier  */
#line 1174 "MachineIndependent/glslang.y"
                               {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());
    }
#line 7224 "MachineIndependent/glslang_tab.cpp"
    break;

  case 131: /* parameter_type_specifier: type_specifier  */
#line 1184 "MachineIndependent/glslang.y"
                     {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)), {} };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 7235 "MachineIndependent/glslang_tab.cpp"
    break;

  case 132: /* init_declarator_list: single_declaration  */
#line 1193 "MachineIndependent/glslang.y"
                         {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 7243 "MachineIndependent/glslang_tab.cpp"
    break;

  case 133: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER  */
#line 1196 "MachineIndependent/glslang.y"
                                            {
        (yyval.interm) = (yyvsp[-2].interm);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, declNode, (yyvsp[0].lex).loc);
    }
#line 7253 "MachineIndependent/glslang_tab.cpp"
    break;

  case 134: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER array_specifier  */
#line 1201 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm) = (yyvsp[-3].interm);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-3].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7263 "MachineIndependent/glslang_tab.cpp"
    break;

  case 135: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER array_specifier EQUAL initializer  */
#line 1206 "MachineIndependent/glslang.y"
                                                                              {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7273 "MachineIndependent/glslang_tab.cpp"
    break;

  case 136: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER EQUAL initializer  */
#line 1211 "MachineIndependent/glslang.y"
                                                              {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7283 "MachineIndependent/glslang_tab.cpp"
    break;

  case 137: /* single_declaration: fully_specified_type  */
#line 1219 "MachineIndependent/glslang.y"
                           {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 7293 "MachineIndependent/glslang_tab.cpp"
    break;

  case 138: /* single_declaration: fully_specified_type IDENTIFIER  */
#line 1224 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[0].lex).loc);

    }
#line 7304 "MachineIndependent/glslang_tab.cpp"
    break;

  case 139: /* single_declaration: fully_specified_type IDENTIFIER array_specifier  */
#line 1230 "MachineIndependent/glslang.y"
                                                      {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-1].lex).loc);
    }
#line 7314 "MachineIndependent/glslang_tab.cpp"
    break;

  case 140: /* single_declaration: fully_specified_type IDENTIFIER array_specifier EQUAL initializer  */
#line 1235 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-3].lex).loc);
    }
#line 7324 "MachineIndependent/glslang_tab.cpp"
    break;

  case 141: /* single_declaration: fully_specified_type IDENTIFIER EQUAL initializer  */
#line 1240 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-2].lex).loc);
    }
#line 7334 "MachineIndependent/glslang_tab.cpp"
    break;

  case 142: /* fully_specified_type: type_specifier  */
#line 1249 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }
        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier, (yyval.interm.type).hasTypeParameter());
    }
#line 7349 "MachineIndependent/glslang_tab.cpp"
    break;

  case 143: /* fully_specified_type: type_qualifier type_specifier  */
#line 1259 "MachineIndependent/glslang.y"
                                     {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, false, &(yyvsp[0].interm.type));
        parseContext.globalQualifierTypeCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, (yyvsp[0].interm.type));

        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[0].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).qualifier))
            (yyvsp[0].interm.type).arraySizes = nullptr;

        parseContext.checkNoShaderLayouts((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        (yyvsp[0].interm.type).shaderQualifiers.merge((yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyvsp[-1].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).basicType, (yyvsp[0].interm.type).qualifier, (yyvsp[0].interm.type).hasTypeParameter());

        (yyval.interm.type) = (yyvsp[0].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    }
#line 7378 "MachineIndependent/glslang_tab.cpp"
    break;

  case 144: /* invariant_qualifier: INVARIANT  */
#line 1286 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 7389 "MachineIndependent/glslang_tab.cpp"
    break;

  case 145: /* interpolation_qualifier: SMOOTH  */
#line 1295 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 7401 "MachineIndependent/glslang_tab.cpp"
    break;

  case 146: /* interpolation_qualifier: FLAT  */
#line 1302 "MachineIndependent/glslang.y"
           {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 7413 "MachineIndependent/glslang_tab.cpp"
    break;

  case 147: /* interpolation_qualifier: NOPERSPECTIVE  */
#line 1309 "MachineIndependent/glslang.y"
                    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "noperspective");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_shader_noperspective_interpolation, "noperspective");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
#line 7425 "MachineIndependent/glslang_tab.cpp"
    break;

  case 148: /* interpolation_qualifier: EXPLICITINTERPAMD  */
#line 1316 "MachineIndependent/glslang.y"
                        {
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
    }
#line 7437 "MachineIndependent/glslang_tab.cpp"
    break;

  case 149: /* interpolation_qualifier: PERVERTEXNV  */
#line 1323 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexNV = true;
    }
#line 7450 "MachineIndependent/glslang_tab.cpp"
    break;

  case 150: /* interpolation_qualifier: PERVERTEXEXT  */
#line 1331 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexEXT = true;
    }
#line 7463 "MachineIndependent/glslang_tab.cpp"
    break;

  case 151: /* interpolation_qualifier: PERPRIMITIVENV  */
#line 1339 "MachineIndependent/glslang.y"
                     {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshMask), "perprimitiveNV");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_NV_mesh_shader, "perprimitiveNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
    }
#line 7478 "MachineIndependent/glslang_tab.cpp"
    break;

  case 152: /* interpolation_qualifier: PERPRIMITIVEEXT  */
#line 1349 "MachineIndependent/glslang.y"
                      {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshMask), "perprimitiveEXT");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_mesh_shader, "perprimitiveEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
    }
#line 7493 "MachineIndependent/glslang_tab.cpp"
    break;

  case 153: /* interpolation_qualifier: PERVIEWNV  */
#line 1359 "MachineIndependent/glslang.y"
                {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perviewNV");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangMesh, "perviewNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perViewNV = true;
    }
#line 7505 "MachineIndependent/glslang_tab.cpp"
    break;

  case 154: /* interpolation_qualifier: PERTASKNV  */
#line 1366 "MachineIndependent/glslang.y"
                {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskMask | EShLangMeshMask), "taskNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perTaskNV = true;
    }
#line 7517 "MachineIndependent/glslang_tab.cpp"
    break;

  case 155: /* layout_qualifier: LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN  */
#line 1376 "MachineIndependent/glslang.y"
                                                             {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 7525 "MachineIndependent/glslang_tab.cpp"
    break;

  case 156: /* layout_qualifier_id_list: layout_qualifier_id  */
#line 1382 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7533 "MachineIndependent/glslang_tab.cpp"
    break;

  case 157: /* layout_qualifier_id_list: layout_qualifier_id_list COMMA layout_qualifier_id  */
#line 1385 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 7543 "MachineIndependent/glslang_tab.cpp"
    break;

  case 158: /* layout_qualifier_id: IDENTIFIER  */
#line 1392 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 7552 "MachineIndependent/glslang_tab.cpp"
    break;

  case 159: /* layout_qualifier_id: IDENTIFIER EQUAL assignment_expression  */
#line 1396 "MachineIndependent/glslang.y"
                                             {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 7561 "MachineIndependent/glslang_tab.cpp"
    break;

  case 160: /* layout_qualifier_id: SHARED  */
#line 1400 "MachineIndependent/glslang.y"
             { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 7571 "MachineIndependent/glslang_tab.cpp"
    break;

  case 161: /* precise_qualifier: PRECISE  */
#line 1408 "MachineIndependent/glslang.y"
              {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 7582 "MachineIndependent/glslang_tab.cpp"
    break;

  case 162: /* type_qualifier: single_type_qualifier  */
#line 1417 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7590 "MachineIndependent/glslang_tab.cpp"
    break;

  case 163: /* type_qualifier: type_qualifier single_type_qualifier  */
#line 1420 "MachineIndependent/glslang.y"
                                           {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 7603 "MachineIndependent/glslang_tab.cpp"
    break;

  case 164: /* single_type_qualifier: storage_qualifier  */
#line 1431 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7611 "MachineIndependent/glslang_tab.cpp"
    break;

  case 165: /* single_type_qualifier: layout_qualifier  */
#line 1434 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7619 "MachineIndependent/glslang_tab.cpp"
    break;

  case 166: /* single_type_qualifier: precision_qualifier  */
#line 1437 "MachineIndependent/glslang.y"
                          {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7628 "MachineIndependent/glslang_tab.cpp"
    break;

  case 167: /* single_type_qualifier: interpolation_qualifier  */
#line 1441 "MachineIndependent/glslang.y"
                              {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7637 "MachineIndependent/glslang_tab.cpp"
    break;

  case 168: /* single_type_qualifier: invariant_qualifier  */
#line 1445 "MachineIndependent/glslang.y"
                          {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7646 "MachineIndependent/glslang_tab.cpp"
    break;

  case 169: /* single_type_qualifier: precise_qualifier  */
#line 1449 "MachineIndependent/glslang.y"
                        {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7655 "MachineIndependent/glslang_tab.cpp"
    break;

  case 170: /* single_type_qualifier: non_uniform_qualifier  */
#line 1453 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7663 "MachineIndependent/glslang_tab.cpp"
    break;

  case 171: /* single_type_qualifier: spirv_storage_class_qualifier  */
#line 1456 "MachineIndependent/glslang.y"
                                    {
        parseContext.globalCheck((yyvsp[0].interm.type).loc, "spirv_storage_class");
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V storage class qualifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7673 "MachineIndependent/glslang_tab.cpp"
    break;

  case 172: /* single_type_qualifier: spirv_decorate_qualifier  */
#line 1461 "MachineIndependent/glslang.y"
                               {
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V decorate qualifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7682 "MachineIndependent/glslang_tab.cpp"
    break;

  case 173: /* single_type_qualifier: SPIRV_BY_REFERENCE  */
#line 1465 "MachineIndependent/glslang.y"
                         {
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "spirv_by_reference");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.setSpirvByReference();
    }
#line 7692 "MachineIndependent/glslang_tab.cpp"
    break;

  case 174: /* single_type_qualifier: SPIRV_LITERAL  */
#line 1470 "MachineIndependent/glslang.y"
                    {
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "spirv_by_literal");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.setSpirvLiteral();
    }
#line 7702 "MachineIndependent/glslang_tab.cpp"
    break;

  case 175: /* storage_qualifier: CONST  */
#line 1478 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 7711 "MachineIndependent/glslang_tab.cpp"
    break;

  case 176: /* storage_qualifier: INOUT  */
#line 1482 "MachineIndependent/glslang.y"
            {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 7721 "MachineIndependent/glslang_tab.cpp"
    break;

  case 177: /* storage_qualifier: IN  */
#line 1487 "MachineIndependent/glslang.y"
         {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 7732 "MachineIndependent/glslang_tab.cpp"
    break;

  case 178: /* storage_qualifier: OUT  */
#line 1493 "MachineIndependent/glslang.y"
          {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 7743 "MachineIndependent/glslang_tab.cpp"
    break;

  case 179: /* storage_qualifier: CENTROID  */
#line 1499 "MachineIndependent/glslang.y"
               {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 7755 "MachineIndependent/glslang_tab.cpp"
    break;

  case 180: /* storage_qualifier: UNIFORM  */
#line 1506 "MachineIndependent/glslang.y"
              {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 7765 "MachineIndependent/glslang_tab.cpp"
    break;

  case 181: /* storage_qualifier: TILEIMAGEEXT  */
#line 1511 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "tileImageEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqTileImageEXT;
    }
#line 7775 "MachineIndependent/glslang_tab.cpp"
    break;

  case 182: /* storage_qualifier: SHARED  */
#line 1516 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 310, 0, "shared");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangComputeMask | EShLangMeshMask | EShLangTaskMask), "shared");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
#line 7788 "MachineIndependent/glslang_tab.cpp"
    break;

  case 183: /* storage_qualifier: BUFFER  */
#line 1524 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 7798 "MachineIndependent/glslang_tab.cpp"
    break;

  case 184: /* storage_qualifier: ATTRIBUTE  */
#line 1529 "MachineIndependent/glslang.y"
                {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangVertex, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "attribute");

        parseContext.globalCheck((yyvsp[0].lex).loc, "attribute");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 7815 "MachineIndependent/glslang_tab.cpp"
    break;

  case 185: /* storage_qualifier: VARYING  */
#line 1541 "MachineIndependent/glslang.y"
              {
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "varying");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "varying");

        parseContext.globalCheck((yyvsp[0].lex).loc, "varying");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).qualifier.storage = EvqVaryingOut;
        else
            (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 7834 "MachineIndependent/glslang_tab.cpp"
    break;

  case 186: /* storage_qualifier: PATCH  */
#line 1555 "MachineIndependent/glslang.y"
            {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 7845 "MachineIndependent/glslang_tab.cpp"
    break;

  case 187: /* storage_qualifier: SAMPLE  */
#line 1561 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 7855 "MachineIndependent/glslang_tab.cpp"
    break;

  case 188: /* storage_qualifier: RESOURCEHEAP  */
#line 1566 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "resourceHeap");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqResourceHeap;
    }
#line 7865 "MachineIndependent/glslang_tab.cpp"
    break;

  case 189: /* storage_qualifier: SAMPLERHEAP  */
#line 1571 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "samplerHeap");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqSamplerHeap;
    }
#line 7875 "MachineIndependent/glslang_tab.cpp"
    break;

  case 190: /* storage_qualifier: HITATTRNV  */
#line 1576 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectMask | EShLangClosestHitMask
            | EShLangAnyHitMask), "hitAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttr;
    }
#line 7888 "MachineIndependent/glslang_tab.cpp"
    break;

  case 191: /* storage_qualifier: HITOBJECTATTRNV  */
#line 1584 "MachineIndependent/glslang.y"
                      {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask
            | EShLangMissMask), "hitObjectAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_shader_invocation_reorder, "hitObjectAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitObjectAttrNV;
    }
#line 7901 "MachineIndependent/glslang_tab.cpp"
    break;

  case 192: /* storage_qualifier: HITOBJECTATTREXT  */
#line 1592 "MachineIndependent/glslang.y"
                       {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask
            | EShLangMissMask), "hitObjectAttributeEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_shader_invocation_reorder, "hitObjectAttributeEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitObjectAttrEXT;
    }
#line 7914 "MachineIndependent/glslang_tab.cpp"
    break;

  case 193: /* storage_qualifier: HITATTREXT  */
#line 1600 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectMask | EShLangClosestHitMask
            | EShLangAnyHitMask), "hitAttributeEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttr;
    }
#line 7927 "MachineIndependent/glslang_tab.cpp"
    break;

  case 194: /* storage_qualifier: PAYLOADNV  */
#line 1608 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayload;
    }
#line 7940 "MachineIndependent/glslang_tab.cpp"
    break;

  case 195: /* storage_qualifier: PAYLOADEXT  */
#line 1616 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "rayPayloadEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayload;
    }
#line 7953 "MachineIndependent/glslang_tab.cpp"
    break;

  case 196: /* storage_qualifier: PAYLOADINNV  */
#line 1624 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadIn;
    }
#line 7966 "MachineIndependent/glslang_tab.cpp"
    break;

  case 197: /* storage_qualifier: PAYLOADINEXT  */
#line 1632 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadInEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "rayPayloadInEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadIn;
    }
#line 7979 "MachineIndependent/glslang_tab.cpp"
    break;

  case 198: /* storage_qualifier: CALLDATANV  */
#line 1640 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask |
            EShLangClosestHitMask | EShLangMissMask | EShLangCallableMask), "callableDataNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableData;
    }
#line 7992 "MachineIndependent/glslang_tab.cpp"
    break;

  case 199: /* storage_qualifier: CALLDATAEXT  */
#line 1648 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask |
            EShLangClosestHitMask | EShLangMissMask | EShLangCallableMask), "callableDataEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "callableDataEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableData;
    }
#line 8005 "MachineIndependent/glslang_tab.cpp"
    break;

  case 200: /* storage_qualifier: CALLDATAINNV  */
#line 1656 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableMask), "callableDataInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataIn;
    }
#line 8017 "MachineIndependent/glslang_tab.cpp"
    break;

  case 201: /* storage_qualifier: CALLDATAINEXT  */
#line 1663 "MachineIndependent/glslang.y"
                    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableMask), "callableDataInEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "callableDataInEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataIn;
    }
#line 8029 "MachineIndependent/glslang_tab.cpp"
    break;

  case 202: /* storage_qualifier: COHERENT  */
#line 1670 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 8038 "MachineIndependent/glslang_tab.cpp"
    break;

  case 203: /* storage_qualifier: DEVICECOHERENT  */
#line 1674 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "devicecoherent");
        (yyval.interm.type).qualifier.devicecoherent = true;
    }
#line 8048 "MachineIndependent/glslang_tab.cpp"
    break;

  case 204: /* storage_qualifier: QUEUEFAMILYCOHERENT  */
#line 1679 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "queuefamilycoherent");
        (yyval.interm.type).qualifier.queuefamilycoherent = true;
    }
#line 8058 "MachineIndependent/glslang_tab.cpp"
    break;

  case 205: /* storage_qualifier: WORKGROUPCOHERENT  */
#line 1684 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "workgroupcoherent");
        (yyval.interm.type).qualifier.workgroupcoherent = true;
    }
#line 8068 "MachineIndependent/glslang_tab.cpp"
    break;

  case 206: /* storage_qualifier: SUBGROUPCOHERENT  */
#line 1689 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "subgroupcoherent");
        (yyval.interm.type).qualifier.subgroupcoherent = true;
    }
#line 8078 "MachineIndependent/glslang_tab.cpp"
    break;

  case 207: /* storage_qualifier: NONPRIVATE  */
#line 1694 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "nonprivate");
        (yyval.interm.type).qualifier.nonprivate = true;
    }
#line 8088 "MachineIndependent/glslang_tab.cpp"
    break;

  case 208: /* storage_qualifier: SHADERCALLCOHERENT  */
#line 1699 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_ray_tracing, "shadercallcoherent");
        (yyval.interm.type).qualifier.shadercallcoherent = true;
    }
#line 8098 "MachineIndependent/glslang_tab.cpp"
    break;

  case 209: /* storage_qualifier: VOLATILE  */
#line 1704 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 8107 "MachineIndependent/glslang_tab.cpp"
    break;

  case 210: /* storage_qualifier: RESTRICT  */
#line 1708 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 8116 "MachineIndependent/glslang_tab.cpp"
    break;

  case 211: /* storage_qualifier: READONLY  */
#line 1712 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 8125 "MachineIndependent/glslang_tab.cpp"
    break;

  case 212: /* storage_qualifier: WRITEONLY  */
#line 1716 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 8134 "MachineIndependent/glslang_tab.cpp"
    break;

  case 213: /* storage_qualifier: NONTEMPORAL  */
#line 1720 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nontemporal  = true;
    }
#line 8143 "MachineIndependent/glslang_tab.cpp"
    break;

  case 214: /* storage_qualifier: SUBROUTINE  */
#line 1724 "MachineIndependent/glslang.y"
                 {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 8154 "MachineIndependent/glslang_tab.cpp"
    break;

  case 215: /* storage_qualifier: SUBROUTINE LEFT_PAREN type_name_list RIGHT_PAREN  */
#line 1730 "MachineIndependent/glslang.y"
                                                       {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 8165 "MachineIndependent/glslang_tab.cpp"
    break;

  case 216: /* storage_qualifier: TASKPAYLOADWORKGROUPEXT  */
#line 1736 "MachineIndependent/glslang.y"
                              {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskPayloadSharedEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskMask | EShLangMeshMask), "taskPayloadSharedEXT  ");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqtaskPayloadSharedEXT;
    }
#line 8177 "MachineIndependent/glslang_tab.cpp"
    break;

  case 217: /* non_uniform_qualifier: NONUNIFORM  */
#line 1746 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nonUniform = true;
    }
#line 8186 "MachineIndependent/glslang_tab.cpp"
    break;

  case 218: /* type_name_list: IDENTIFIER  */
#line 1753 "MachineIndependent/glslang.y"
                 {
        // TODO
    }
#line 8194 "MachineIndependent/glslang_tab.cpp"
    break;

  case 219: /* type_name_list: type_name_list COMMA IDENTIFIER  */
#line 1756 "MachineIndependent/glslang.y"
                                      {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 8204 "MachineIndependent/glslang_tab.cpp"
    break;

  case 220: /* type_specifier: type_specifier_nonarray type_parameter_specifier_opt  */
#line 1764 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[0].interm.typeParameters);
        parseContext.typeParametersCheck((yyvsp[-1].interm.type).loc, (yyval.interm.type));

    }
#line 8216 "MachineIndependent/glslang_tab.cpp"
    break;

  case 221: /* type_specifier: type_specifier_nonarray type_parameter_specifier_opt array_specifier  */
#line 1771 "MachineIndependent/glslang.y"
                                                                           {
        parseContext.arrayOfArrayVersionCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes);
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[-1].interm.typeParameters);
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
        parseContext.typeParametersCheck((yyvsp[-2].interm.type).loc, (yyval.interm.type));
    }
#line 8229 "MachineIndependent/glslang_tab.cpp"
    break;

  case 222: /* array_specifier: LEFT_BRACKET RIGHT_BRACKET  */
#line 1782 "MachineIndependent/glslang.y"
                                 {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 8239 "MachineIndependent/glslang_tab.cpp"
    break;

  case 223: /* array_specifier: LEFT_BRACKET conditional_expression RIGHT_BRACKET  */
#line 1787 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 8252 "MachineIndependent/glslang_tab.cpp"
    break;

  case 224: /* array_specifier: array_specifier LEFT_BRACKET RIGHT_BRACKET  */
#line 1795 "MachineIndependent/glslang.y"
                                                 {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 8261 "MachineIndependent/glslang_tab.cpp"
    break;

  case 225: /* array_specifier: array_specifier LEFT_BRACKET conditional_expression RIGHT_BRACKET  */
#line 1799 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 8273 "MachineIndependent/glslang_tab.cpp"
    break;

  case 226: /* type_parameter_specifier_opt: type_parameter_specifier  */
#line 1809 "MachineIndependent/glslang.y"
                               {
        (yyval.interm.typeParameters) = (yyvsp[0].interm.typeParameters);
    }
#line 8281 "MachineIndependent/glslang_tab.cpp"
    break;

  case 227: /* type_parameter_specifier_opt: %empty  */
#line 1812 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.typeParameters) = 0;
    }
#line 8289 "MachineIndependent/glslang_tab.cpp"
    break;

  case 228: /* type_parameter_specifier: LEFT_ANGLE type_parameter_specifier_list RIGHT_ANGLE  */
#line 1818 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.typeParameters) = (yyvsp[-1].interm.typeParameters);
    }
#line 8297 "MachineIndependent/glslang_tab.cpp"
    break;

  case 229: /* type_parameter_specifier_list: type_specifier  */
#line 1824 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.typeParameters) = new TTypeParameters;
        (yyval.interm.typeParameters)->arraySizes = new TArraySizes;
        (yyval.interm.typeParameters)->spirvType = (yyvsp[0].interm.type).spirvType;
        (yyval.interm.typeParameters)->basicType = (yyvsp[0].interm.type).basicType;
    }
#line 8308 "MachineIndependent/glslang_tab.cpp"
    break;

  case 230: /* type_parameter_specifier_list: unary_expression  */
#line 1830 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.typeParameters) = new TTypeParameters;
        (yyval.interm.typeParameters)->arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter", true);
        (yyval.interm.typeParameters)->arraySizes->addInnerSize(size);
    }
#line 8321 "MachineIndependent/glslang_tab.cpp"
    break;

  case 231: /* type_parameter_specifier_list: type_parameter_specifier_list COMMA unary_expression  */
#line 1838 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.typeParameters) = (yyvsp[-2].interm.typeParameters);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter", true);
        (yyval.interm.typeParameters)->arraySizes->addInnerSize(size);
    }
#line 8333 "MachineIndependent/glslang_tab.cpp"
    break;

  case 232: /* type_specifier_nonarray: VOID  */
#line 1848 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 8342 "MachineIndependent/glslang_tab.cpp"
    break;

  case 233: /* type_specifier_nonarray: FLOAT  */
#line 1852 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 8351 "MachineIndependent/glslang_tab.cpp"
    break;

  case 234: /* type_specifier_nonarray: INT  */
#line 1856 "MachineIndependent/glslang.y"
          {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 8360 "MachineIndependent/glslang_tab.cpp"
    break;

  case 235: /* type_specifier_nonarray: UINT  */
#line 1860 "MachineIndependent/glslang.y"
           {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 8370 "MachineIndependent/glslang_tab.cpp"
    break;

  case 236: /* type_specifier_nonarray: BOOL  */
#line 1865 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 8379 "MachineIndependent/glslang_tab.cpp"
    break;

  case 237: /* type_specifier_nonarray: VEC2  */
#line 1869 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 8389 "MachineIndependent/glslang_tab.cpp"
    break;

  case 238: /* type_specifier_nonarray: VEC3  */
#line 1874 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 8399 "MachineIndependent/glslang_tab.cpp"
    break;

  case 239: /* type_specifier_nonarray: VEC4  */
#line 1879 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 8409 "MachineIndependent/glslang_tab.cpp"
    break;

  case 240: /* type_specifier_nonarray: BVEC2  */
#line 1884 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 8419 "MachineIndependent/glslang_tab.cpp"
    break;

  case 241: /* type_specifier_nonarray: BVEC3  */
#line 1889 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 8429 "MachineIndependent/glslang_tab.cpp"
    break;

  case 242: /* type_specifier_nonarray: BVEC4  */
#line 1894 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 8439 "MachineIndependent/glslang_tab.cpp"
    break;

  case 243: /* type_specifier_nonarray: IVEC2  */
#line 1899 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 8449 "MachineIndependent/glslang_tab.cpp"
    break;

  case 244: /* type_specifier_nonarray: IVEC3  */
#line 1904 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 8459 "MachineIndependent/glslang_tab.cpp"
    break;

  case 245: /* type_specifier_nonarray: IVEC4  */
#line 1909 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 8469 "MachineIndependent/glslang_tab.cpp"
    break;

  case 246: /* type_specifier_nonarray: UVEC2  */
#line 1914 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 8480 "MachineIndependent/glslang_tab.cpp"
    break;

  case 247: /* type_specifier_nonarray: UVEC3  */
#line 1920 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 8491 "MachineIndependent/glslang_tab.cpp"
    break;

  case 248: /* type_specifier_nonarray: UVEC4  */
#line 1926 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 8502 "MachineIndependent/glslang_tab.cpp"
    break;

  case 249: /* type_specifier_nonarray: MAT2  */
#line 1932 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 8512 "MachineIndependent/glslang_tab.cpp"
    break;

  case 250: /* type_specifier_nonarray: MAT3  */
#line 1937 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 8522 "MachineIndependent/glslang_tab.cpp"
    break;

  case 251: /* type_specifier_nonarray: MAT4  */
#line 1942 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 8532 "MachineIndependent/glslang_tab.cpp"
    break;

  case 252: /* type_specifier_nonarray: MAT2X2  */
#line 1947 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 8542 "MachineIndependent/glslang_tab.cpp"
    break;

  case 253: /* type_specifier_nonarray: MAT2X3  */
#line 1952 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 8552 "MachineIndependent/glslang_tab.cpp"
    break;

  case 254: /* type_specifier_nonarray: MAT2X4  */
#line 1957 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 8562 "MachineIndependent/glslang_tab.cpp"
    break;

  case 255: /* type_specifier_nonarray: MAT3X2  */
#line 1962 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 8572 "MachineIndependent/glslang_tab.cpp"
    break;

  case 256: /* type_specifier_nonarray: MAT3X3  */
#line 1967 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 8582 "MachineIndependent/glslang_tab.cpp"
    break;

  case 257: /* type_specifier_nonarray: MAT3X4  */
#line 1972 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 8592 "MachineIndependent/glslang_tab.cpp"
    break;

  case 258: /* type_specifier_nonarray: MAT4X2  */
#line 1977 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 8602 "MachineIndependent/glslang_tab.cpp"
    break;

  case 259: /* type_specifier_nonarray: MAT4X3  */
#line 1982 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 8612 "MachineIndependent/glslang_tab.cpp"
    break;

  case 260: /* type_specifier_nonarray: MAT4X4  */
#line 1987 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 8622 "MachineIndependent/glslang_tab.cpp"
    break;

  case 261: /* type_specifier_nonarray: DOUBLE  */
#line 1992 "MachineIndependent/glslang.y"
             {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 8634 "MachineIndependent/glslang_tab.cpp"
    break;

  case 262: /* type_specifier_nonarray: BFLOAT16_T  */
#line 1999 "MachineIndependent/glslang.y"
                 {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "bfloat16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
    }
#line 8644 "MachineIndependent/glslang_tab.cpp"
    break;

  case 263: /* type_specifier_nonarray: FLOATE5M2_T  */
#line 2004 "MachineIndependent/glslang.y"
                  {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "floate5m2_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
    }
#line 8654 "MachineIndependent/glslang_tab.cpp"
    break;

  case 264: /* type_specifier_nonarray: FLOATE4M3_T  */
#line 2009 "MachineIndependent/glslang.y"
                  {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "floate4m3_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
    }
#line 8664 "MachineIndependent/glslang_tab.cpp"
    break;

  case 265: /* type_specifier_nonarray: FLOATE2M1_T  */
#line 2014 "MachineIndependent/glslang.y"
                  {
        parseContext.floate2m1ScalarVectorCheck((yyvsp[0].lex).loc, "floate2m1_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M1;
    }
#line 8674 "MachineIndependent/glslang_tab.cpp"
    break;

  case 266: /* type_specifier_nonarray: FLOATE3M2_T  */
#line 2019 "MachineIndependent/glslang.y"
                  {
        parseContext.floate3m2ScalarVectorCheck((yyvsp[0].lex).loc, "floate3m2_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE3M2;
    }
#line 8684 "MachineIndependent/glslang_tab.cpp"
    break;

  case 267: /* type_specifier_nonarray: FLOATE2M3_T  */
#line 2024 "MachineIndependent/glslang.y"
                  {
        parseContext.floate2m3ScalarVectorCheck((yyvsp[0].lex).loc, "floate2m3_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M3;
    }
#line 8694 "MachineIndependent/glslang_tab.cpp"
    break;

  case 268: /* type_specifier_nonarray: FLOATUE8M0_T  */
#line 2029 "MachineIndependent/glslang.y"
                   {
        parseContext.floatue8m0ScalarVectorCheck((yyvsp[0].lex).loc, "floatue8m0_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatUE8M0;
    }
#line 8704 "MachineIndependent/glslang_tab.cpp"
    break;

  case 269: /* type_specifier_nonarray: FLOATMXINT8_T  */
#line 2034 "MachineIndependent/glslang.y"
                    {
        parseContext.floatmxint8ScalarVectorCheck((yyvsp[0].lex).loc, "floatmxint8_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatMXINT8;
    }
#line 8714 "MachineIndependent/glslang_tab.cpp"
    break;

  case 270: /* type_specifier_nonarray: FLOAT16_T  */
#line 2039 "MachineIndependent/glslang.y"
                {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "float16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
    }
#line 8724 "MachineIndependent/glslang_tab.cpp"
    break;

  case 271: /* type_specifier_nonarray: FLOAT32_T  */
#line 2044 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 8734 "MachineIndependent/glslang_tab.cpp"
    break;

  case 272: /* type_specifier_nonarray: FLOAT64_T  */
#line 2049 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 8744 "MachineIndependent/glslang_tab.cpp"
    break;

  case 273: /* type_specifier_nonarray: INT8_T  */
#line 2054 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
    }
#line 8754 "MachineIndependent/glslang_tab.cpp"
    break;

  case 274: /* type_specifier_nonarray: UINT8_T  */
#line 2059 "MachineIndependent/glslang.y"
              {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
    }
#line 8764 "MachineIndependent/glslang_tab.cpp"
    break;

  case 275: /* type_specifier_nonarray: INT16_T  */
#line 2064 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
    }
#line 8774 "MachineIndependent/glslang_tab.cpp"
    break;

  case 276: /* type_specifier_nonarray: UINT16_T  */
#line 2069 "MachineIndependent/glslang.y"
               {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
    }
#line 8784 "MachineIndependent/glslang_tab.cpp"
    break;

  case 277: /* type_specifier_nonarray: INT32_T  */
#line 2074 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 8794 "MachineIndependent/glslang_tab.cpp"
    break;

  case 278: /* type_specifier_nonarray: UINT32_T  */
#line 2079 "MachineIndependent/glslang.y"
               {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 8804 "MachineIndependent/glslang_tab.cpp"
    break;

  case 279: /* type_specifier_nonarray: INT64_T  */
#line 2084 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 8814 "MachineIndependent/glslang_tab.cpp"
    break;

  case 280: /* type_specifier_nonarray: UINT64_T  */
#line 2089 "MachineIndependent/glslang.y"
               {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 8824 "MachineIndependent/glslang_tab.cpp"
    break;

  case 281: /* type_specifier_nonarray: DVEC2  */
#line 2094 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 8837 "MachineIndependent/glslang_tab.cpp"
    break;

  case 282: /* type_specifier_nonarray: DVEC3  */
#line 2102 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 8850 "MachineIndependent/glslang_tab.cpp"
    break;

  case 283: /* type_specifier_nonarray: DVEC4  */
#line 2110 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 8863 "MachineIndependent/glslang_tab.cpp"
    break;

  case 284: /* type_specifier_nonarray: BF16VEC2  */
#line 2118 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 8874 "MachineIndependent/glslang_tab.cpp"
    break;

  case 285: /* type_specifier_nonarray: BF16VEC3  */
#line 2124 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 8885 "MachineIndependent/glslang_tab.cpp"
    break;

  case 286: /* type_specifier_nonarray: BF16VEC4  */
#line 2130 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 8896 "MachineIndependent/glslang_tab.cpp"
    break;

  case 287: /* type_specifier_nonarray: FE5M2VEC2  */
#line 2136 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(2);
    }
#line 8907 "MachineIndependent/glslang_tab.cpp"
    break;

  case 288: /* type_specifier_nonarray: FE5M2VEC3  */
#line 2142 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(3);
    }
#line 8918 "MachineIndependent/glslang_tab.cpp"
    break;

  case 289: /* type_specifier_nonarray: FE5M2VEC4  */
#line 2148 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(4);
    }
#line 8929 "MachineIndependent/glslang_tab.cpp"
    break;

  case 290: /* type_specifier_nonarray: FE4M3VEC2  */
#line 2154 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(2);
    }
#line 8940 "MachineIndependent/glslang_tab.cpp"
    break;

  case 291: /* type_specifier_nonarray: FE4M3VEC3  */
#line 2160 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(3);
    }
#line 8951 "MachineIndependent/glslang_tab.cpp"
    break;

  case 292: /* type_specifier_nonarray: FE4M3VEC4  */
#line 2166 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(4);
    }
#line 8962 "MachineIndependent/glslang_tab.cpp"
    break;

  case 293: /* type_specifier_nonarray: FE2M1VEC2  */
#line 2172 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m1ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m1 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M1;
        (yyval.interm.type).setVector(2);
    }
#line 8973 "MachineIndependent/glslang_tab.cpp"
    break;

  case 294: /* type_specifier_nonarray: FE2M1VEC3  */
#line 2178 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m1ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m1 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M1;
        (yyval.interm.type).setVector(3);
    }
#line 8984 "MachineIndependent/glslang_tab.cpp"
    break;

  case 295: /* type_specifier_nonarray: FE2M1VEC4  */
#line 2184 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m1ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m1 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M1;
        (yyval.interm.type).setVector(4);
    }
#line 8995 "MachineIndependent/glslang_tab.cpp"
    break;

  case 296: /* type_specifier_nonarray: FE3M2VEC2  */
#line 2190 "MachineIndependent/glslang.y"
                {
        parseContext.floate3m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe3m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE3M2;
        (yyval.interm.type).setVector(2);
    }
#line 9006 "MachineIndependent/glslang_tab.cpp"
    break;

  case 297: /* type_specifier_nonarray: FE3M2VEC3  */
#line 2196 "MachineIndependent/glslang.y"
                {
        parseContext.floate3m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe3m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE3M2;
        (yyval.interm.type).setVector(3);
    }
#line 9017 "MachineIndependent/glslang_tab.cpp"
    break;

  case 298: /* type_specifier_nonarray: FE3M2VEC4  */
#line 2202 "MachineIndependent/glslang.y"
                {
        parseContext.floate3m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe3m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE3M2;
        (yyval.interm.type).setVector(4);
    }
#line 9028 "MachineIndependent/glslang_tab.cpp"
    break;

  case 299: /* type_specifier_nonarray: FE2M3VEC2  */
#line 2208 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M3;
        (yyval.interm.type).setVector(2);
    }
#line 9039 "MachineIndependent/glslang_tab.cpp"
    break;

  case 300: /* type_specifier_nonarray: FE2M3VEC3  */
#line 2214 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M3;
        (yyval.interm.type).setVector(3);
    }
#line 9050 "MachineIndependent/glslang_tab.cpp"
    break;

  case 301: /* type_specifier_nonarray: FE2M3VEC4  */
#line 2220 "MachineIndependent/glslang.y"
                {
        parseContext.floate2m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe2m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE2M3;
        (yyval.interm.type).setVector(4);
    }
#line 9061 "MachineIndependent/glslang_tab.cpp"
    break;

  case 302: /* type_specifier_nonarray: FUE8M0VEC2  */
#line 2226 "MachineIndependent/glslang.y"
                 {
        parseContext.floatue8m0ScalarVectorCheck((yyvsp[0].lex).loc, "fue8m0 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatUE8M0;
        (yyval.interm.type).setVector(2);
    }
#line 9072 "MachineIndependent/glslang_tab.cpp"
    break;

  case 303: /* type_specifier_nonarray: FUE8M0VEC3  */
#line 2232 "MachineIndependent/glslang.y"
                 {
        parseContext.floatue8m0ScalarVectorCheck((yyvsp[0].lex).loc, "fue8m0 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatUE8M0;
        (yyval.interm.type).setVector(3);
    }
#line 9083 "MachineIndependent/glslang_tab.cpp"
    break;

  case 304: /* type_specifier_nonarray: FUE8M0VEC4  */
#line 2238 "MachineIndependent/glslang.y"
                 {
        parseContext.floatue8m0ScalarVectorCheck((yyvsp[0].lex).loc, "fue8m0 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatUE8M0;
        (yyval.interm.type).setVector(4);
    }
#line 9094 "MachineIndependent/glslang_tab.cpp"
    break;

  case 305: /* type_specifier_nonarray: FMXINT8VEC2  */
#line 2244 "MachineIndependent/glslang.y"
                  {
        parseContext.floatmxint8ScalarVectorCheck((yyvsp[0].lex).loc, "fmxint8 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatMXINT8;
        (yyval.interm.type).setVector(2);
    }
#line 9105 "MachineIndependent/glslang_tab.cpp"
    break;

  case 306: /* type_specifier_nonarray: FMXINT8VEC3  */
#line 2250 "MachineIndependent/glslang.y"
                  {
        parseContext.floatmxint8ScalarVectorCheck((yyvsp[0].lex).loc, "fmxint8 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatMXINT8;
        (yyval.interm.type).setVector(3);
    }
#line 9116 "MachineIndependent/glslang_tab.cpp"
    break;

  case 307: /* type_specifier_nonarray: FMXINT8VEC4  */
#line 2256 "MachineIndependent/glslang.y"
                  {
        parseContext.floatmxint8ScalarVectorCheck((yyvsp[0].lex).loc, "fmxint8 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatMXINT8;
        (yyval.interm.type).setVector(4);
    }
#line 9127 "MachineIndependent/glslang_tab.cpp"
    break;

  case 308: /* type_specifier_nonarray: F16VEC2  */
#line 2262 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 9138 "MachineIndependent/glslang_tab.cpp"
    break;

  case 309: /* type_specifier_nonarray: F16VEC3  */
#line 2268 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 9149 "MachineIndependent/glslang_tab.cpp"
    break;

  case 310: /* type_specifier_nonarray: F16VEC4  */
#line 2274 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 9160 "MachineIndependent/glslang_tab.cpp"
    break;

  case 311: /* type_specifier_nonarray: F32VEC2  */
#line 2280 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 9171 "MachineIndependent/glslang_tab.cpp"
    break;

  case 312: /* type_specifier_nonarray: F32VEC3  */
#line 2286 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 9182 "MachineIndependent/glslang_tab.cpp"
    break;

  case 313: /* type_specifier_nonarray: F32VEC4  */
#line 2292 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 9193 "MachineIndependent/glslang_tab.cpp"
    break;

  case 314: /* type_specifier_nonarray: F64VEC2  */
#line 2298 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 9204 "MachineIndependent/glslang_tab.cpp"
    break;

  case 315: /* type_specifier_nonarray: F64VEC3  */
#line 2304 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 9215 "MachineIndependent/glslang_tab.cpp"
    break;

  case 316: /* type_specifier_nonarray: F64VEC4  */
#line 2310 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 9226 "MachineIndependent/glslang_tab.cpp"
    break;

  case 317: /* type_specifier_nonarray: I8VEC2  */
#line 2316 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(2);
    }
#line 9237 "MachineIndependent/glslang_tab.cpp"
    break;

  case 318: /* type_specifier_nonarray: I8VEC3  */
#line 2322 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(3);
    }
#line 9248 "MachineIndependent/glslang_tab.cpp"
    break;

  case 319: /* type_specifier_nonarray: I8VEC4  */
#line 2328 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(4);
    }
#line 9259 "MachineIndependent/glslang_tab.cpp"
    break;

  case 320: /* type_specifier_nonarray: I16VEC2  */
#line 2334 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
    }
#line 9270 "MachineIndependent/glslang_tab.cpp"
    break;

  case 321: /* type_specifier_nonarray: I16VEC3  */
#line 2340 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
    }
#line 9281 "MachineIndependent/glslang_tab.cpp"
    break;

  case 322: /* type_specifier_nonarray: I16VEC4  */
#line 2346 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
    }
#line 9292 "MachineIndependent/glslang_tab.cpp"
    break;

  case 323: /* type_specifier_nonarray: I32VEC2  */
#line 2352 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 9303 "MachineIndependent/glslang_tab.cpp"
    break;

  case 324: /* type_specifier_nonarray: I32VEC3  */
#line 2358 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 9314 "MachineIndependent/glslang_tab.cpp"
    break;

  case 325: /* type_specifier_nonarray: I32VEC4  */
#line 2364 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 9325 "MachineIndependent/glslang_tab.cpp"
    break;

  case 326: /* type_specifier_nonarray: I64VEC2  */
#line 2370 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 9336 "MachineIndependent/glslang_tab.cpp"
    break;

  case 327: /* type_specifier_nonarray: I64VEC3  */
#line 2376 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 9347 "MachineIndependent/glslang_tab.cpp"
    break;

  case 328: /* type_specifier_nonarray: I64VEC4  */
#line 2382 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 9358 "MachineIndependent/glslang_tab.cpp"
    break;

  case 329: /* type_specifier_nonarray: U8VEC2  */
#line 2388 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(2);
    }
#line 9369 "MachineIndependent/glslang_tab.cpp"
    break;

  case 330: /* type_specifier_nonarray: U8VEC3  */
#line 2394 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(3);
    }
#line 9380 "MachineIndependent/glslang_tab.cpp"
    break;

  case 331: /* type_specifier_nonarray: U8VEC4  */
#line 2400 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(4);
    }
#line 9391 "MachineIndependent/glslang_tab.cpp"
    break;

  case 332: /* type_specifier_nonarray: U16VEC2  */
#line 2406 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
    }
#line 9402 "MachineIndependent/glslang_tab.cpp"
    break;

  case 333: /* type_specifier_nonarray: U16VEC3  */
#line 2412 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
    }
#line 9413 "MachineIndependent/glslang_tab.cpp"
    break;

  case 334: /* type_specifier_nonarray: U16VEC4  */
#line 2418 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
    }
#line 9424 "MachineIndependent/glslang_tab.cpp"
    break;

  case 335: /* type_specifier_nonarray: U32VEC2  */
#line 2424 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 9435 "MachineIndependent/glslang_tab.cpp"
    break;

  case 336: /* type_specifier_nonarray: U32VEC3  */
#line 2430 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 9446 "MachineIndependent/glslang_tab.cpp"
    break;

  case 337: /* type_specifier_nonarray: U32VEC4  */
#line 2436 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 9457 "MachineIndependent/glslang_tab.cpp"
    break;

  case 338: /* type_specifier_nonarray: U64VEC2  */
#line 2442 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 9468 "MachineIndependent/glslang_tab.cpp"
    break;

  case 339: /* type_specifier_nonarray: U64VEC3  */
#line 2448 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 9479 "MachineIndependent/glslang_tab.cpp"
    break;

  case 340: /* type_specifier_nonarray: U64VEC4  */
#line 2454 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 9490 "MachineIndependent/glslang_tab.cpp"
    break;

  case 341: /* type_specifier_nonarray: DMAT2  */
#line 2460 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9503 "MachineIndependent/glslang_tab.cpp"
    break;

  case 342: /* type_specifier_nonarray: DMAT3  */
#line 2468 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9516 "MachineIndependent/glslang_tab.cpp"
    break;

  case 343: /* type_specifier_nonarray: DMAT4  */
#line 2476 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9529 "MachineIndependent/glslang_tab.cpp"
    break;

  case 344: /* type_specifier_nonarray: DMAT2X2  */
#line 2484 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9542 "MachineIndependent/glslang_tab.cpp"
    break;

  case 345: /* type_specifier_nonarray: DMAT2X3  */
#line 2492 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9555 "MachineIndependent/glslang_tab.cpp"
    break;

  case 346: /* type_specifier_nonarray: DMAT2X4  */
#line 2500 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9568 "MachineIndependent/glslang_tab.cpp"
    break;

  case 347: /* type_specifier_nonarray: DMAT3X2  */
#line 2508 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9581 "MachineIndependent/glslang_tab.cpp"
    break;

  case 348: /* type_specifier_nonarray: DMAT3X3  */
#line 2516 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9594 "MachineIndependent/glslang_tab.cpp"
    break;

  case 349: /* type_specifier_nonarray: DMAT3X4  */
#line 2524 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9607 "MachineIndependent/glslang_tab.cpp"
    break;

  case 350: /* type_specifier_nonarray: DMAT4X2  */
#line 2532 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9620 "MachineIndependent/glslang_tab.cpp"
    break;

  case 351: /* type_specifier_nonarray: DMAT4X3  */
#line 2540 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9633 "MachineIndependent/glslang_tab.cpp"
    break;

  case 352: /* type_specifier_nonarray: DMAT4X4  */
#line 2548 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9646 "MachineIndependent/glslang_tab.cpp"
    break;

  case 353: /* type_specifier_nonarray: F16MAT2  */
#line 2556 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9657 "MachineIndependent/glslang_tab.cpp"
    break;

  case 354: /* type_specifier_nonarray: F16MAT3  */
#line 2562 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9668 "MachineIndependent/glslang_tab.cpp"
    break;

  case 355: /* type_specifier_nonarray: F16MAT4  */
#line 2568 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9679 "MachineIndependent/glslang_tab.cpp"
    break;

  case 356: /* type_specifier_nonarray: F16MAT2X2  */
#line 2574 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9690 "MachineIndependent/glslang_tab.cpp"
    break;

  case 357: /* type_specifier_nonarray: F16MAT2X3  */
#line 2580 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9701 "MachineIndependent/glslang_tab.cpp"
    break;

  case 358: /* type_specifier_nonarray: F16MAT2X4  */
#line 2586 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9712 "MachineIndependent/glslang_tab.cpp"
    break;

  case 359: /* type_specifier_nonarray: F16MAT3X2  */
#line 2592 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9723 "MachineIndependent/glslang_tab.cpp"
    break;

  case 360: /* type_specifier_nonarray: F16MAT3X3  */
#line 2598 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9734 "MachineIndependent/glslang_tab.cpp"
    break;

  case 361: /* type_specifier_nonarray: F16MAT3X4  */
#line 2604 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9745 "MachineIndependent/glslang_tab.cpp"
    break;

  case 362: /* type_specifier_nonarray: F16MAT4X2  */
#line 2610 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9756 "MachineIndependent/glslang_tab.cpp"
    break;

  case 363: /* type_specifier_nonarray: F16MAT4X3  */
#line 2616 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9767 "MachineIndependent/glslang_tab.cpp"
    break;

  case 364: /* type_specifier_nonarray: F16MAT4X4  */
#line 2622 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9778 "MachineIndependent/glslang_tab.cpp"
    break;

  case 365: /* type_specifier_nonarray: F32MAT2  */
#line 2628 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9789 "MachineIndependent/glslang_tab.cpp"
    break;

  case 366: /* type_specifier_nonarray: F32MAT3  */
#line 2634 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9800 "MachineIndependent/glslang_tab.cpp"
    break;

  case 367: /* type_specifier_nonarray: F32MAT4  */
#line 2640 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9811 "MachineIndependent/glslang_tab.cpp"
    break;

  case 368: /* type_specifier_nonarray: F32MAT2X2  */
#line 2646 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9822 "MachineIndependent/glslang_tab.cpp"
    break;

  case 369: /* type_specifier_nonarray: F32MAT2X3  */
#line 2652 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9833 "MachineIndependent/glslang_tab.cpp"
    break;

  case 370: /* type_specifier_nonarray: F32MAT2X4  */
#line 2658 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9844 "MachineIndependent/glslang_tab.cpp"
    break;

  case 371: /* type_specifier_nonarray: F32MAT3X2  */
#line 2664 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9855 "MachineIndependent/glslang_tab.cpp"
    break;

  case 372: /* type_specifier_nonarray: F32MAT3X3  */
#line 2670 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9866 "MachineIndependent/glslang_tab.cpp"
    break;

  case 373: /* type_specifier_nonarray: F32MAT3X4  */
#line 2676 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9877 "MachineIndependent/glslang_tab.cpp"
    break;

  case 374: /* type_specifier_nonarray: F32MAT4X2  */
#line 2682 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9888 "MachineIndependent/glslang_tab.cpp"
    break;

  case 375: /* type_specifier_nonarray: F32MAT4X3  */
#line 2688 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9899 "MachineIndependent/glslang_tab.cpp"
    break;

  case 376: /* type_specifier_nonarray: F32MAT4X4  */
#line 2694 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9910 "MachineIndependent/glslang_tab.cpp"
    break;

  case 377: /* type_specifier_nonarray: F64MAT2  */
#line 2700 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9921 "MachineIndependent/glslang_tab.cpp"
    break;

  case 378: /* type_specifier_nonarray: F64MAT3  */
#line 2706 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9932 "MachineIndependent/glslang_tab.cpp"
    break;

  case 379: /* type_specifier_nonarray: F64MAT4  */
#line 2712 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9943 "MachineIndependent/glslang_tab.cpp"
    break;

  case 380: /* type_specifier_nonarray: F64MAT2X2  */
#line 2718 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9954 "MachineIndependent/glslang_tab.cpp"
    break;

  case 381: /* type_specifier_nonarray: F64MAT2X3  */
#line 2724 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9965 "MachineIndependent/glslang_tab.cpp"
    break;

  case 382: /* type_specifier_nonarray: F64MAT2X4  */
#line 2730 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9976 "MachineIndependent/glslang_tab.cpp"
    break;

  case 383: /* type_specifier_nonarray: F64MAT3X2  */
#line 2736 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9987 "MachineIndependent/glslang_tab.cpp"
    break;

  case 384: /* type_specifier_nonarray: F64MAT3X3  */
#line 2742 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9998 "MachineIndependent/glslang_tab.cpp"
    break;

  case 385: /* type_specifier_nonarray: F64MAT3X4  */
#line 2748 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 10009 "MachineIndependent/glslang_tab.cpp"
    break;

  case 386: /* type_specifier_nonarray: F64MAT4X2  */
#line 2754 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 10020 "MachineIndependent/glslang_tab.cpp"
    break;

  case 387: /* type_specifier_nonarray: F64MAT4X3  */
#line 2760 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 10031 "MachineIndependent/glslang_tab.cpp"
    break;

  case 388: /* type_specifier_nonarray: F64MAT4X4  */
#line 2766 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 10042 "MachineIndependent/glslang_tab.cpp"
    break;

  case 389: /* type_specifier_nonarray: ACCSTRUCTNV  */
#line 2772 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStruct;
    }
#line 10051 "MachineIndependent/glslang_tab.cpp"
    break;

  case 390: /* type_specifier_nonarray: ACCSTRUCTEXT  */
#line 2776 "MachineIndependent/glslang.y"
                   {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStruct;
    }
#line 10060 "MachineIndependent/glslang_tab.cpp"
    break;

  case 391: /* type_specifier_nonarray: RAYQUERYEXT  */
#line 2780 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtRayQuery;
    }
#line 10069 "MachineIndependent/glslang_tab.cpp"
    break;

  case 392: /* type_specifier_nonarray: ATOMIC_UINT  */
#line 2784 "MachineIndependent/glslang.y"
                  {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 10079 "MachineIndependent/glslang_tab.cpp"
    break;

  case 393: /* type_specifier_nonarray: SAMPLER1D  */
#line 2789 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 10089 "MachineIndependent/glslang_tab.cpp"
    break;

  case 394: /* type_specifier_nonarray: SAMPLER2D  */
#line 2794 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 10099 "MachineIndependent/glslang_tab.cpp"
    break;

  case 395: /* type_specifier_nonarray: SAMPLER3D  */
#line 2799 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 10109 "MachineIndependent/glslang_tab.cpp"
    break;

  case 396: /* type_specifier_nonarray: SAMPLERCUBE  */
#line 2804 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 10119 "MachineIndependent/glslang_tab.cpp"
    break;

  case 397: /* type_specifier_nonarray: SAMPLER2DSHADOW  */
#line 2809 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 10129 "MachineIndependent/glslang_tab.cpp"
    break;

  case 398: /* type_specifier_nonarray: SAMPLERCUBESHADOW  */
#line 2814 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 10139 "MachineIndependent/glslang_tab.cpp"
    break;

  case 399: /* type_specifier_nonarray: SAMPLER2DARRAY  */
#line 2819 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 10149 "MachineIndependent/glslang_tab.cpp"
    break;

  case 400: /* type_specifier_nonarray: SAMPLER2DARRAYSHADOW  */
#line 2824 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 10159 "MachineIndependent/glslang_tab.cpp"
    break;

  case 401: /* type_specifier_nonarray: SAMPLER1DSHADOW  */
#line 2829 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 10169 "MachineIndependent/glslang_tab.cpp"
    break;

  case 402: /* type_specifier_nonarray: SAMPLER1DARRAY  */
#line 2834 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 10179 "MachineIndependent/glslang_tab.cpp"
    break;

  case 403: /* type_specifier_nonarray: SAMPLER1DARRAYSHADOW  */
#line 2839 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 10189 "MachineIndependent/glslang_tab.cpp"
    break;

  case 404: /* type_specifier_nonarray: SAMPLERCUBEARRAY  */
#line 2844 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 10199 "MachineIndependent/glslang_tab.cpp"
    break;

  case 405: /* type_specifier_nonarray: SAMPLERCUBEARRAYSHADOW  */
#line 2849 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 10209 "MachineIndependent/glslang_tab.cpp"
    break;

  case 406: /* type_specifier_nonarray: F16SAMPLER1D  */
#line 2854 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
    }
#line 10220 "MachineIndependent/glslang_tab.cpp"
    break;

  case 407: /* type_specifier_nonarray: F16SAMPLER2D  */
#line 2860 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
    }
#line 10231 "MachineIndependent/glslang_tab.cpp"
    break;

  case 408: /* type_specifier_nonarray: F16SAMPLER3D  */
#line 2866 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
    }
#line 10242 "MachineIndependent/glslang_tab.cpp"
    break;

  case 409: /* type_specifier_nonarray: F16SAMPLERCUBE  */
#line 2872 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
    }
#line 10253 "MachineIndependent/glslang_tab.cpp"
    break;

  case 410: /* type_specifier_nonarray: F16SAMPLER1DSHADOW  */
#line 2878 "MachineIndependent/glslang.y"
                         {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
    }
#line 10264 "MachineIndependent/glslang_tab.cpp"
    break;

  case 411: /* type_specifier_nonarray: F16SAMPLER2DSHADOW  */
#line 2884 "MachineIndependent/glslang.y"
                         {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
    }
#line 10275 "MachineIndependent/glslang_tab.cpp"
    break;

  case 412: /* type_specifier_nonarray: F16SAMPLERCUBESHADOW  */
#line 2890 "MachineIndependent/glslang.y"
                           {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
    }
#line 10286 "MachineIndependent/glslang_tab.cpp"
    break;

  case 413: /* type_specifier_nonarray: F16SAMPLER1DARRAY  */
#line 2896 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
    }
#line 10297 "MachineIndependent/glslang_tab.cpp"
    break;

  case 414: /* type_specifier_nonarray: F16SAMPLER2DARRAY  */
#line 2902 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
    }
#line 10308 "MachineIndependent/glslang_tab.cpp"
    break;

  case 415: /* type_specifier_nonarray: F16SAMPLER1DARRAYSHADOW  */
#line 2908 "MachineIndependent/glslang.y"
                              {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
    }
#line 10319 "MachineIndependent/glslang_tab.cpp"
    break;

  case 416: /* type_specifier_nonarray: F16SAMPLER2DARRAYSHADOW  */
#line 2914 "MachineIndependent/glslang.y"
                              {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
    }
#line 10330 "MachineIndependent/glslang_tab.cpp"
    break;

  case 417: /* type_specifier_nonarray: F16SAMPLERCUBEARRAY  */
#line 2920 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
    }
#line 10341 "MachineIndependent/glslang_tab.cpp"
    break;

  case 418: /* type_specifier_nonarray: F16SAMPLERCUBEARRAYSHADOW  */
#line 2926 "MachineIndependent/glslang.y"
                                {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
    }
#line 10352 "MachineIndependent/glslang_tab.cpp"
    break;

  case 419: /* type_specifier_nonarray: ISAMPLER1D  */
#line 2932 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 10362 "MachineIndependent/glslang_tab.cpp"
    break;

  case 420: /* type_specifier_nonarray: ISAMPLER2D  */
#line 2937 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 10372 "MachineIndependent/glslang_tab.cpp"
    break;

  case 421: /* type_specifier_nonarray: ISAMPLER3D  */
#line 2942 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 10382 "MachineIndependent/glslang_tab.cpp"
    break;

  case 422: /* type_specifier_nonarray: ISAMPLERCUBE  */
#line 2947 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 10392 "MachineIndependent/glslang_tab.cpp"
    break;

  case 423: /* type_specifier_nonarray: ISAMPLER2DARRAY  */
#line 2952 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 10402 "MachineIndependent/glslang_tab.cpp"
    break;

  case 424: /* type_specifier_nonarray: USAMPLER2D  */
#line 2957 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 10412 "MachineIndependent/glslang_tab.cpp"
    break;

  case 425: /* type_specifier_nonarray: USAMPLER3D  */
#line 2962 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 10422 "MachineIndependent/glslang_tab.cpp"
    break;

  case 426: /* type_specifier_nonarray: USAMPLERCUBE  */
#line 2967 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 10432 "MachineIndependent/glslang_tab.cpp"
    break;

  case 427: /* type_specifier_nonarray: ISAMPLER1DARRAY  */
#line 2972 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 10442 "MachineIndependent/glslang_tab.cpp"
    break;

  case 428: /* type_specifier_nonarray: ISAMPLERCUBEARRAY  */
#line 2977 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 10452 "MachineIndependent/glslang_tab.cpp"
    break;

  case 429: /* type_specifier_nonarray: USAMPLER1D  */
#line 2982 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 10462 "MachineIndependent/glslang_tab.cpp"
    break;

  case 430: /* type_specifier_nonarray: USAMPLER1DARRAY  */
#line 2987 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 10472 "MachineIndependent/glslang_tab.cpp"
    break;

  case 431: /* type_specifier_nonarray: USAMPLERCUBEARRAY  */
#line 2992 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 10482 "MachineIndependent/glslang_tab.cpp"
    break;

  case 432: /* type_specifier_nonarray: TEXTURECUBEARRAY  */
#line 2997 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 10492 "MachineIndependent/glslang_tab.cpp"
    break;

  case 433: /* type_specifier_nonarray: ITEXTURECUBEARRAY  */
#line 3002 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 10502 "MachineIndependent/glslang_tab.cpp"
    break;

  case 434: /* type_specifier_nonarray: UTEXTURECUBEARRAY  */
#line 3007 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 10512 "MachineIndependent/glslang_tab.cpp"
    break;

  case 435: /* type_specifier_nonarray: USAMPLER2DARRAY  */
#line 3012 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 10522 "MachineIndependent/glslang_tab.cpp"
    break;

  case 436: /* type_specifier_nonarray: TEXTURE2D  */
#line 3017 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 10532 "MachineIndependent/glslang_tab.cpp"
    break;

  case 437: /* type_specifier_nonarray: TEXTURE3D  */
#line 3022 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 10542 "MachineIndependent/glslang_tab.cpp"
    break;

  case 438: /* type_specifier_nonarray: TEXTURE2DARRAY  */
#line 3027 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 10552 "MachineIndependent/glslang_tab.cpp"
    break;

  case 439: /* type_specifier_nonarray: TEXTURECUBE  */
#line 3032 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 10562 "MachineIndependent/glslang_tab.cpp"
    break;

  case 440: /* type_specifier_nonarray: ITEXTURE2D  */
#line 3037 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 10572 "MachineIndependent/glslang_tab.cpp"
    break;

  case 441: /* type_specifier_nonarray: ITEXTURE3D  */
#line 3042 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 10582 "MachineIndependent/glslang_tab.cpp"
    break;

  case 442: /* type_specifier_nonarray: ITEXTURECUBE  */
#line 3047 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 10592 "MachineIndependent/glslang_tab.cpp"
    break;

  case 443: /* type_specifier_nonarray: ITEXTURE2DARRAY  */
#line 3052 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 10602 "MachineIndependent/glslang_tab.cpp"
    break;

  case 444: /* type_specifier_nonarray: UTEXTURE2D  */
#line 3057 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 10612 "MachineIndependent/glslang_tab.cpp"
    break;

  case 445: /* type_specifier_nonarray: UTEXTURE3D  */
#line 3062 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 10622 "MachineIndependent/glslang_tab.cpp"
    break;

  case 446: /* type_specifier_nonarray: UTEXTURECUBE  */
#line 3067 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 10632 "MachineIndependent/glslang_tab.cpp"
    break;

  case 447: /* type_specifier_nonarray: UTEXTURE2DARRAY  */
#line 3072 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 10642 "MachineIndependent/glslang_tab.cpp"
    break;

  case 448: /* type_specifier_nonarray: SAMPLER  */
#line 3077 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 10652 "MachineIndependent/glslang_tab.cpp"
    break;

  case 449: /* type_specifier_nonarray: SAMPLERSHADOW  */
#line 3082 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 10662 "MachineIndependent/glslang_tab.cpp"
    break;

  case 450: /* type_specifier_nonarray: SAMPLER2DRECT  */
#line 3087 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 10672 "MachineIndependent/glslang_tab.cpp"
    break;

  case 451: /* type_specifier_nonarray: SAMPLER2DRECTSHADOW  */
#line 3092 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 10682 "MachineIndependent/glslang_tab.cpp"
    break;

  case 452: /* type_specifier_nonarray: F16SAMPLER2DRECT  */
#line 3097 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
    }
#line 10693 "MachineIndependent/glslang_tab.cpp"
    break;

  case 453: /* type_specifier_nonarray: F16SAMPLER2DRECTSHADOW  */
#line 3103 "MachineIndependent/glslang.y"
                             {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
    }
#line 10704 "MachineIndependent/glslang_tab.cpp"
    break;

  case 454: /* type_specifier_nonarray: ISAMPLER2DRECT  */
#line 3109 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 10714 "MachineIndependent/glslang_tab.cpp"
    break;

  case 455: /* type_specifier_nonarray: USAMPLER2DRECT  */
#line 3114 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 10724 "MachineIndependent/glslang_tab.cpp"
    break;

  case 456: /* type_specifier_nonarray: SAMPLERBUFFER  */
#line 3119 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 10734 "MachineIndependent/glslang_tab.cpp"
    break;

  case 457: /* type_specifier_nonarray: F16SAMPLERBUFFER  */
#line 3124 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
    }
#line 10745 "MachineIndependent/glslang_tab.cpp"
    break;

  case 458: /* type_specifier_nonarray: ISAMPLERBUFFER  */
#line 3130 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 10755 "MachineIndependent/glslang_tab.cpp"
    break;

  case 459: /* type_specifier_nonarray: USAMPLERBUFFER  */
#line 3135 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 10765 "MachineIndependent/glslang_tab.cpp"
    break;

  case 460: /* type_specifier_nonarray: SAMPLER2DMS  */
#line 3140 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 10775 "MachineIndependent/glslang_tab.cpp"
    break;

  case 461: /* type_specifier_nonarray: F16SAMPLER2DMS  */
#line 3145 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
    }
#line 10786 "MachineIndependent/glslang_tab.cpp"
    break;

  case 462: /* type_specifier_nonarray: ISAMPLER2DMS  */
#line 3151 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 10796 "MachineIndependent/glslang_tab.cpp"
    break;

  case 463: /* type_specifier_nonarray: USAMPLER2DMS  */
#line 3156 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 10806 "MachineIndependent/glslang_tab.cpp"
    break;

  case 464: /* type_specifier_nonarray: SAMPLER2DMSARRAY  */
#line 3161 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 10816 "MachineIndependent/glslang_tab.cpp"
    break;

  case 465: /* type_specifier_nonarray: F16SAMPLER2DMSARRAY  */
#line 3166 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
    }
#line 10827 "MachineIndependent/glslang_tab.cpp"
    break;

  case 466: /* type_specifier_nonarray: ISAMPLER2DMSARRAY  */
#line 3172 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 10837 "MachineIndependent/glslang_tab.cpp"
    break;

  case 467: /* type_specifier_nonarray: USAMPLER2DMSARRAY  */
#line 3177 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 10847 "MachineIndependent/glslang_tab.cpp"
    break;

  case 468: /* type_specifier_nonarray: TEXTURE1D  */
#line 3182 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 10857 "MachineIndependent/glslang_tab.cpp"
    break;

  case 469: /* type_specifier_nonarray: F16TEXTURE1D  */
#line 3187 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
    }
#line 10868 "MachineIndependent/glslang_tab.cpp"
    break;

  case 470: /* type_specifier_nonarray: F16TEXTURE2D  */
#line 3193 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
    }
#line 10879 "MachineIndependent/glslang_tab.cpp"
    break;

  case 471: /* type_specifier_nonarray: F16TEXTURE3D  */
#line 3199 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
    }
#line 10890 "MachineIndependent/glslang_tab.cpp"
    break;

  case 472: /* type_specifier_nonarray: F16TEXTURECUBE  */
#line 3205 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
    }
#line 10901 "MachineIndependent/glslang_tab.cpp"
    break;

  case 473: /* type_specifier_nonarray: TEXTURE1DARRAY  */
#line 3211 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 10911 "MachineIndependent/glslang_tab.cpp"
    break;

  case 474: /* type_specifier_nonarray: F16TEXTURE1DARRAY  */
#line 3216 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
    }
#line 10922 "MachineIndependent/glslang_tab.cpp"
    break;

  case 475: /* type_specifier_nonarray: F16TEXTURE2DARRAY  */
#line 3222 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
    }
#line 10933 "MachineIndependent/glslang_tab.cpp"
    break;

  case 476: /* type_specifier_nonarray: F16TEXTURECUBEARRAY  */
#line 3228 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
    }
#line 10944 "MachineIndependent/glslang_tab.cpp"
    break;

  case 477: /* type_specifier_nonarray: ITEXTURE1D  */
#line 3234 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 10954 "MachineIndependent/glslang_tab.cpp"
    break;

  case 478: /* type_specifier_nonarray: ITEXTURE1DARRAY  */
#line 3239 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 10964 "MachineIndependent/glslang_tab.cpp"
    break;

  case 479: /* type_specifier_nonarray: UTEXTURE1D  */
#line 3244 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 10974 "MachineIndependent/glslang_tab.cpp"
    break;

  case 480: /* type_specifier_nonarray: UTEXTURE1DARRAY  */
#line 3249 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 10984 "MachineIndependent/glslang_tab.cpp"
    break;

  case 481: /* type_specifier_nonarray: TEXTURE2DRECT  */
#line 3254 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 10994 "MachineIndependent/glslang_tab.cpp"
    break;

  case 482: /* type_specifier_nonarray: F16TEXTURE2DRECT  */
#line 3259 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
    }
#line 11005 "MachineIndependent/glslang_tab.cpp"
    break;

  case 483: /* type_specifier_nonarray: ITEXTURE2DRECT  */
#line 3265 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 11015 "MachineIndependent/glslang_tab.cpp"
    break;

  case 484: /* type_specifier_nonarray: UTEXTURE2DRECT  */
#line 3270 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 11025 "MachineIndependent/glslang_tab.cpp"
    break;

  case 485: /* type_specifier_nonarray: TEXTUREBUFFER  */
#line 3275 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 11035 "MachineIndependent/glslang_tab.cpp"
    break;

  case 486: /* type_specifier_nonarray: F16TEXTUREBUFFER  */
#line 3280 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
    }
#line 11046 "MachineIndependent/glslang_tab.cpp"
    break;

  case 487: /* type_specifier_nonarray: ITEXTUREBUFFER  */
#line 3286 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 11056 "MachineIndependent/glslang_tab.cpp"
    break;

  case 488: /* type_specifier_nonarray: UTEXTUREBUFFER  */
#line 3291 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 11066 "MachineIndependent/glslang_tab.cpp"
    break;

  case 489: /* type_specifier_nonarray: TEXTURE2DMS  */
#line 3296 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 11076 "MachineIndependent/glslang_tab.cpp"
    break;

  case 490: /* type_specifier_nonarray: F16TEXTURE2DMS  */
#line 3301 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
    }
#line 11087 "MachineIndependent/glslang_tab.cpp"
    break;

  case 491: /* type_specifier_nonarray: ITEXTURE2DMS  */
#line 3307 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 11097 "MachineIndependent/glslang_tab.cpp"
    break;

  case 492: /* type_specifier_nonarray: UTEXTURE2DMS  */
#line 3312 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 11107 "MachineIndependent/glslang_tab.cpp"
    break;

  case 493: /* type_specifier_nonarray: TEXTURE2DMSARRAY  */
#line 3317 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 11117 "MachineIndependent/glslang_tab.cpp"
    break;

  case 494: /* type_specifier_nonarray: F16TEXTURE2DMSARRAY  */
#line 3322 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
    }
#line 11128 "MachineIndependent/glslang_tab.cpp"
    break;

  case 495: /* type_specifier_nonarray: ITEXTURE2DMSARRAY  */
#line 3328 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 11138 "MachineIndependent/glslang_tab.cpp"
    break;

  case 496: /* type_specifier_nonarray: UTEXTURE2DMSARRAY  */
#line 3333 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 11148 "MachineIndependent/glslang_tab.cpp"
    break;

  case 497: /* type_specifier_nonarray: IMAGE1D  */
#line 3338 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 11158 "MachineIndependent/glslang_tab.cpp"
    break;

  case 498: /* type_specifier_nonarray: F16IMAGE1D  */
#line 3343 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
    }
#line 11169 "MachineIndependent/glslang_tab.cpp"
    break;

  case 499: /* type_specifier_nonarray: IIMAGE1D  */
#line 3349 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 11179 "MachineIndependent/glslang_tab.cpp"
    break;

  case 500: /* type_specifier_nonarray: UIMAGE1D  */
#line 3354 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 11189 "MachineIndependent/glslang_tab.cpp"
    break;

  case 501: /* type_specifier_nonarray: IMAGE2D  */
#line 3359 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 11199 "MachineIndependent/glslang_tab.cpp"
    break;

  case 502: /* type_specifier_nonarray: F16IMAGE2D  */
#line 3364 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
    }
#line 11210 "MachineIndependent/glslang_tab.cpp"
    break;

  case 503: /* type_specifier_nonarray: IIMAGE2D  */
#line 3370 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 11220 "MachineIndependent/glslang_tab.cpp"
    break;

  case 504: /* type_specifier_nonarray: UIMAGE2D  */
#line 3375 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 11230 "MachineIndependent/glslang_tab.cpp"
    break;

  case 505: /* type_specifier_nonarray: IMAGE3D  */
#line 3380 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 11240 "MachineIndependent/glslang_tab.cpp"
    break;

  case 506: /* type_specifier_nonarray: F16IMAGE3D  */
#line 3385 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
    }
#line 11251 "MachineIndependent/glslang_tab.cpp"
    break;

  case 507: /* type_specifier_nonarray: IIMAGE3D  */
#line 3391 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 11261 "MachineIndependent/glslang_tab.cpp"
    break;

  case 508: /* type_specifier_nonarray: UIMAGE3D  */
#line 3396 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 11271 "MachineIndependent/glslang_tab.cpp"
    break;

  case 509: /* type_specifier_nonarray: IMAGE2DRECT  */
#line 3401 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 11281 "MachineIndependent/glslang_tab.cpp"
    break;

  case 510: /* type_specifier_nonarray: F16IMAGE2DRECT  */
#line 3406 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
    }
#line 11292 "MachineIndependent/glslang_tab.cpp"
    break;

  case 511: /* type_specifier_nonarray: IIMAGE2DRECT  */
#line 3412 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 11302 "MachineIndependent/glslang_tab.cpp"
    break;

  case 512: /* type_specifier_nonarray: UIMAGE2DRECT  */
#line 3417 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 11312 "MachineIndependent/glslang_tab.cpp"
    break;

  case 513: /* type_specifier_nonarray: IMAGECUBE  */
#line 3422 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 11322 "MachineIndependent/glslang_tab.cpp"
    break;

  case 514: /* type_specifier_nonarray: F16IMAGECUBE  */
#line 3427 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
    }
#line 11333 "MachineIndependent/glslang_tab.cpp"
    break;

  case 515: /* type_specifier_nonarray: IIMAGECUBE  */
#line 3433 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 11343 "MachineIndependent/glslang_tab.cpp"
    break;

  case 516: /* type_specifier_nonarray: UIMAGECUBE  */
#line 3438 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 11353 "MachineIndependent/glslang_tab.cpp"
    break;

  case 517: /* type_specifier_nonarray: IMAGEBUFFER  */
#line 3443 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 11363 "MachineIndependent/glslang_tab.cpp"
    break;

  case 518: /* type_specifier_nonarray: F16IMAGEBUFFER  */
#line 3448 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
    }
#line 11374 "MachineIndependent/glslang_tab.cpp"
    break;

  case 519: /* type_specifier_nonarray: IIMAGEBUFFER  */
#line 3454 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 11384 "MachineIndependent/glslang_tab.cpp"
    break;

  case 520: /* type_specifier_nonarray: UIMAGEBUFFER  */
#line 3459 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 11394 "MachineIndependent/glslang_tab.cpp"
    break;

  case 521: /* type_specifier_nonarray: IMAGE1DARRAY  */
#line 3464 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 11404 "MachineIndependent/glslang_tab.cpp"
    break;

  case 522: /* type_specifier_nonarray: F16IMAGE1DARRAY  */
#line 3469 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
    }
#line 11415 "MachineIndependent/glslang_tab.cpp"
    break;

  case 523: /* type_specifier_nonarray: IIMAGE1DARRAY  */
#line 3475 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 11425 "MachineIndependent/glslang_tab.cpp"
    break;

  case 524: /* type_specifier_nonarray: UIMAGE1DARRAY  */
#line 3480 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 11435 "MachineIndependent/glslang_tab.cpp"
    break;

  case 525: /* type_specifier_nonarray: IMAGE2DARRAY  */
#line 3485 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 11445 "MachineIndependent/glslang_tab.cpp"
    break;

  case 526: /* type_specifier_nonarray: F16IMAGE2DARRAY  */
#line 3490 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
    }
#line 11456 "MachineIndependent/glslang_tab.cpp"
    break;

  case 527: /* type_specifier_nonarray: IIMAGE2DARRAY  */
#line 3496 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 11466 "MachineIndependent/glslang_tab.cpp"
    break;

  case 528: /* type_specifier_nonarray: UIMAGE2DARRAY  */
#line 3501 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 11476 "MachineIndependent/glslang_tab.cpp"
    break;

  case 529: /* type_specifier_nonarray: IMAGECUBEARRAY  */
#line 3506 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 11486 "MachineIndependent/glslang_tab.cpp"
    break;

  case 530: /* type_specifier_nonarray: F16IMAGECUBEARRAY  */
#line 3511 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
    }
#line 11497 "MachineIndependent/glslang_tab.cpp"
    break;

  case 531: /* type_specifier_nonarray: IIMAGECUBEARRAY  */
#line 3517 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 11507 "MachineIndependent/glslang_tab.cpp"
    break;

  case 532: /* type_specifier_nonarray: UIMAGECUBEARRAY  */
#line 3522 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 11517 "MachineIndependent/glslang_tab.cpp"
    break;

  case 533: /* type_specifier_nonarray: IMAGE2DMS  */
#line 3527 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 11527 "MachineIndependent/glslang_tab.cpp"
    break;

  case 534: /* type_specifier_nonarray: F16IMAGE2DMS  */
#line 3532 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
    }
#line 11538 "MachineIndependent/glslang_tab.cpp"
    break;

  case 535: /* type_specifier_nonarray: IIMAGE2DMS  */
#line 3538 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 11548 "MachineIndependent/glslang_tab.cpp"
    break;

  case 536: /* type_specifier_nonarray: UIMAGE2DMS  */
#line 3543 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 11558 "MachineIndependent/glslang_tab.cpp"
    break;

  case 537: /* type_specifier_nonarray: IMAGE2DMSARRAY  */
#line 3548 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 11568 "MachineIndependent/glslang_tab.cpp"
    break;

  case 538: /* type_specifier_nonarray: F16IMAGE2DMSARRAY  */
#line 3553 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
    }
#line 11579 "MachineIndependent/glslang_tab.cpp"
    break;

  case 539: /* type_specifier_nonarray: IIMAGE2DMSARRAY  */
#line 3559 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 11589 "MachineIndependent/glslang_tab.cpp"
    break;

  case 540: /* type_specifier_nonarray: UIMAGE2DMSARRAY  */
#line 3564 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 11599 "MachineIndependent/glslang_tab.cpp"
    break;

  case 541: /* type_specifier_nonarray: I64IMAGE1D  */
#line 3569 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd1D);
    }
#line 11609 "MachineIndependent/glslang_tab.cpp"
    break;

  case 542: /* type_specifier_nonarray: U64IMAGE1D  */
#line 3574 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd1D);
    }
#line 11619 "MachineIndependent/glslang_tab.cpp"
    break;

  case 543: /* type_specifier_nonarray: I64IMAGE2D  */
#line 3579 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D);
    }
#line 11629 "MachineIndependent/glslang_tab.cpp"
    break;

  case 544: /* type_specifier_nonarray: U64IMAGE2D  */
#line 3584 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D);
    }
#line 11639 "MachineIndependent/glslang_tab.cpp"
    break;

  case 545: /* type_specifier_nonarray: I64IMAGE3D  */
#line 3589 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd3D);
    }
#line 11649 "MachineIndependent/glslang_tab.cpp"
    break;

  case 546: /* type_specifier_nonarray: U64IMAGE3D  */
#line 3594 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd3D);
    }
#line 11659 "MachineIndependent/glslang_tab.cpp"
    break;

  case 547: /* type_specifier_nonarray: I64IMAGE2DRECT  */
#line 3599 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdRect);
    }
#line 11669 "MachineIndependent/glslang_tab.cpp"
    break;

  case 548: /* type_specifier_nonarray: U64IMAGE2DRECT  */
#line 3604 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdRect);
    }
#line 11679 "MachineIndependent/glslang_tab.cpp"
    break;

  case 549: /* type_specifier_nonarray: I64IMAGECUBE  */
#line 3609 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdCube);
    }
#line 11689 "MachineIndependent/glslang_tab.cpp"
    break;

  case 550: /* type_specifier_nonarray: U64IMAGECUBE  */
#line 3614 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdCube);
    }
#line 11699 "MachineIndependent/glslang_tab.cpp"
    break;

  case 551: /* type_specifier_nonarray: I64IMAGEBUFFER  */
#line 3619 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdBuffer);
    }
#line 11709 "MachineIndependent/glslang_tab.cpp"
    break;

  case 552: /* type_specifier_nonarray: U64IMAGEBUFFER  */
#line 3624 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdBuffer);
    }
#line 11719 "MachineIndependent/glslang_tab.cpp"
    break;

  case 553: /* type_specifier_nonarray: I64IMAGE1DARRAY  */
#line 3629 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd1D, true);
    }
#line 11729 "MachineIndependent/glslang_tab.cpp"
    break;

  case 554: /* type_specifier_nonarray: U64IMAGE1DARRAY  */
#line 3634 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd1D, true);
    }
#line 11739 "MachineIndependent/glslang_tab.cpp"
    break;

  case 555: /* type_specifier_nonarray: I64IMAGE2DARRAY  */
#line 3639 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, true);
    }
#line 11749 "MachineIndependent/glslang_tab.cpp"
    break;

  case 556: /* type_specifier_nonarray: U64IMAGE2DARRAY  */
#line 3644 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, true);
    }
#line 11759 "MachineIndependent/glslang_tab.cpp"
    break;

  case 557: /* type_specifier_nonarray: I64IMAGECUBEARRAY  */
#line 3649 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdCube, true);
    }
#line 11769 "MachineIndependent/glslang_tab.cpp"
    break;

  case 558: /* type_specifier_nonarray: U64IMAGECUBEARRAY  */
#line 3654 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdCube, true);
    }
#line 11779 "MachineIndependent/glslang_tab.cpp"
    break;

  case 559: /* type_specifier_nonarray: I64IMAGE2DMS  */
#line 3659 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, false, false, true);
    }
#line 11789 "MachineIndependent/glslang_tab.cpp"
    break;

  case 560: /* type_specifier_nonarray: U64IMAGE2DMS  */
#line 3664 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, false, false, true);
    }
#line 11799 "MachineIndependent/glslang_tab.cpp"
    break;

  case 561: /* type_specifier_nonarray: I64IMAGE2DMSARRAY  */
#line 3669 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, true, false, true);
    }
#line 11809 "MachineIndependent/glslang_tab.cpp"
    break;

  case 562: /* type_specifier_nonarray: U64IMAGE2DMSARRAY  */
#line 3674 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, true, false, true);
    }
#line 11819 "MachineIndependent/glslang_tab.cpp"
    break;

  case 563: /* type_specifier_nonarray: SAMPLEREXTERNALOES  */
#line 3679 "MachineIndependent/glslang.y"
                         {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 11830 "MachineIndependent/glslang_tab.cpp"
    break;

  case 564: /* type_specifier_nonarray: SAMPLEREXTERNAL2DY2YEXT  */
#line 3685 "MachineIndependent/glslang.y"
                              { // GL_EXT_YUV_target
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.yuv = true;
    }
#line 11841 "MachineIndependent/glslang_tab.cpp"
    break;

  case 565: /* type_specifier_nonarray: ATTACHMENTEXT  */
#line 3691 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtFloat);
    }
#line 11852 "MachineIndependent/glslang_tab.cpp"
    break;

  case 566: /* type_specifier_nonarray: IATTACHMENTEXT  */
#line 3697 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtInt);
    }
#line 11863 "MachineIndependent/glslang_tab.cpp"
    break;

  case 567: /* type_specifier_nonarray: UATTACHMENTEXT  */
#line 3703 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtUint);
    }
#line 11874 "MachineIndependent/glslang_tab.cpp"
    break;

  case 568: /* type_specifier_nonarray: SUBPASSINPUT  */
#line 3709 "MachineIndependent/glslang.y"
                   {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 11885 "MachineIndependent/glslang_tab.cpp"
    break;

  case 569: /* type_specifier_nonarray: SUBPASSINPUTMS  */
#line 3715 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 11896 "MachineIndependent/glslang_tab.cpp"
    break;

  case 570: /* type_specifier_nonarray: F16SUBPASSINPUT  */
#line 3721 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
    }
#line 11908 "MachineIndependent/glslang_tab.cpp"
    break;

  case 571: /* type_specifier_nonarray: F16SUBPASSINPUTMS  */
#line 3728 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
    }
#line 11920 "MachineIndependent/glslang_tab.cpp"
    break;

  case 572: /* type_specifier_nonarray: ISUBPASSINPUT  */
#line 3735 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 11931 "MachineIndependent/glslang_tab.cpp"
    break;

  case 573: /* type_specifier_nonarray: ISUBPASSINPUTMS  */
#line 3741 "MachineIndependent/glslang.y"
                      {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 11942 "MachineIndependent/glslang_tab.cpp"
    break;

  case 574: /* type_specifier_nonarray: USUBPASSINPUT  */
#line 3747 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 11953 "MachineIndependent/glslang_tab.cpp"
    break;

  case 575: /* type_specifier_nonarray: USUBPASSINPUTMS  */
#line 3753 "MachineIndependent/glslang.y"
                      {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 11964 "MachineIndependent/glslang_tab.cpp"
    break;

  case 576: /* type_specifier_nonarray: FCOOPMATNV  */
#line 3759 "MachineIndependent/glslang.y"
                 {
        parseContext.fcoopmatCheckNV((yyvsp[0].lex).loc, "fcoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 11976 "MachineIndependent/glslang_tab.cpp"
    break;

  case 577: /* type_specifier_nonarray: ICOOPMATNV  */
#line 3766 "MachineIndependent/glslang.y"
                 {
        parseContext.intcoopmatCheckNV((yyvsp[0].lex).loc, "icoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 11988 "MachineIndependent/glslang_tab.cpp"
    break;

  case 578: /* type_specifier_nonarray: UCOOPMATNV  */
#line 3773 "MachineIndependent/glslang.y"
                 {
        parseContext.intcoopmatCheckNV((yyvsp[0].lex).loc, "ucoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 12000 "MachineIndependent/glslang_tab.cpp"
    break;

  case 579: /* type_specifier_nonarray: COOPMAT  */
#line 3780 "MachineIndependent/glslang.y"
              {
        parseContext.coopmatCheck((yyvsp[0].lex).loc, "coopmat", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtCoopmat;
        (yyval.interm.type).coopmatNV = false;
        (yyval.interm.type).coopmatKHR = true;
    }
#line 12012 "MachineIndependent/glslang_tab.cpp"
    break;

  case 580: /* type_specifier_nonarray: TENSORLAYOUTNV  */
#line 3787 "MachineIndependent/glslang.y"
                     {
        parseContext.tensorLayoutViewCheck((yyvsp[0].lex).loc, "tensorLayoutNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtTensorLayoutNV;
    }
#line 12022 "MachineIndependent/glslang_tab.cpp"
    break;

  case 581: /* type_specifier_nonarray: TENSORVIEWNV  */
#line 3792 "MachineIndependent/glslang.y"
                   {
        parseContext.tensorLayoutViewCheck((yyvsp[0].lex).loc, "tensorViewNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtTensorViewNV;
    }
#line 12032 "MachineIndependent/glslang_tab.cpp"
    break;

  case 582: /* type_specifier_nonarray: FUNCTION  */
#line 3797 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).basicType = EbtFunction;
    }
#line 12041 "MachineIndependent/glslang_tab.cpp"
    break;

  case 583: /* type_specifier_nonarray: COOPVECNV  */
#line 3801 "MachineIndependent/glslang.y"
                {
        parseContext.coopvecCheck((yyvsp[0].lex).loc, "coopvecNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtCoopvecNV;
        (yyval.interm.type).coopvecNV = true;
    }
#line 12052 "MachineIndependent/glslang_tab.cpp"
    break;

  case 584: /* type_specifier_nonarray: TENSORARM  */
#line 3807 "MachineIndependent/glslang.y"
                {
        parseContext.tensorCheckARM((yyvsp[0].lex).loc, "tensorARM", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).tensorRankARM = 1; // placeholder value
        (yyval.interm.type).basicType = EbtTensorARM;
    }
#line 12063 "MachineIndependent/glslang_tab.cpp"
    break;

  case 585: /* type_specifier_nonarray: VECTOR  */
#line 3813 "MachineIndependent/glslang.y"
             {
        parseContext.longVectorCheck((yyvsp[0].lex).loc, "vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtLongVector;
        (yyval.interm.type).longVector = true;
    }
#line 12074 "MachineIndependent/glslang_tab.cpp"
    break;

  case 586: /* type_specifier_nonarray: spirv_type_specifier  */
#line 3819 "MachineIndependent/glslang.y"
                           {
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V type specifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 12083 "MachineIndependent/glslang_tab.cpp"
    break;

  case 587: /* type_specifier_nonarray: HITOBJECTNV  */
#line 3823 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtHitObjectNV;
    }
#line 12092 "MachineIndependent/glslang_tab.cpp"
    break;

  case 588: /* type_specifier_nonarray: HITOBJECTEXT  */
#line 3827 "MachineIndependent/glslang.y"
                   {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtHitObjectEXT;
    }
#line 12101 "MachineIndependent/glslang_tab.cpp"
    break;

  case 589: /* type_specifier_nonarray: struct_specifier  */
#line 3831 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 12111 "MachineIndependent/glslang_tab.cpp"
    break;

  case 590: /* type_specifier_nonarray: TYPE_NAME  */
#line 3836 "MachineIndependent/glslang.y"
                {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ((yyvsp[0].lex).symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
            (yyval.interm.type).basicType = EbtStruct;
            (yyval.interm.type).userDef = &structure;
            if (structure.getQualifier().isBufferType())
                (yyval.interm.type).qualifier = structure.getQualifier();
        } else
            parseContext.error((yyvsp[0].lex).loc, "expected type name", (yyvsp[0].lex).string->c_str(), "");
    }
#line 12131 "MachineIndependent/glslang_tab.cpp"
    break;

  case 591: /* precision_qualifier: HIGH_PRECISION  */
#line 3854 "MachineIndependent/glslang.y"
                     {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 12141 "MachineIndependent/glslang_tab.cpp"
    break;

  case 592: /* precision_qualifier: MEDIUM_PRECISION  */
#line 3859 "MachineIndependent/glslang.y"
                       {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 12151 "MachineIndependent/glslang_tab.cpp"
    break;

  case 593: /* precision_qualifier: LOW_PRECISION  */
#line 3864 "MachineIndependent/glslang.y"
                    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 12161 "MachineIndependent/glslang_tab.cpp"
    break;

  case 594: /* $@3: %empty  */
#line 3872 "MachineIndependent/glslang.y"
                                   { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 12167 "MachineIndependent/glslang_tab.cpp"
    break;

  case 595: /* struct_specifier: STRUCT IDENTIFIER LEFT_BRACE $@3 struct_declaration_list RIGHT_BRACE  */
#line 3872 "MachineIndependent/glslang.y"
                                                                                                                   {
        TType* structure = new TType((yyvsp[-1].interm.typeList), *(yyvsp[-4].lex).string);
        parseContext.structArrayCheck((yyvsp[-4].lex).loc, *structure);

        TVariable* userTypeDef = new TVariable((yyvsp[-4].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[-4].lex).loc, "redefinition", (yyvsp[-4].lex).string->c_str(), "struct");
        else if (parseContext.spvVersion.vulkanRelaxed
                 && structure->containsOpaque())
            parseContext.relaxedSymbols.push_back(structure->getTypeName());

        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 12188 "MachineIndependent/glslang_tab.cpp"
    break;

  case 596: /* $@4: %empty  */
#line 3888 "MachineIndependent/glslang.y"
                        { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 12194 "MachineIndependent/glslang_tab.cpp"
    break;

  case 597: /* struct_specifier: STRUCT LEFT_BRACE $@4 struct_declaration_list RIGHT_BRACE  */
#line 3888 "MachineIndependent/glslang.y"
                                                                                                        {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 12206 "MachineIndependent/glslang_tab.cpp"
    break;

  case 598: /* struct_declaration_list: struct_declaration  */
#line 3898 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 12214 "MachineIndependent/glslang_tab.cpp"
    break;

  case 599: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 3901 "MachineIndependent/glslang.y"
                                                 {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 12229 "MachineIndependent/glslang_tab.cpp"
    break;

  case 600: /* struct_declaration: struct_declaration_no_inline_block  */
#line 3914 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 12237 "MachineIndependent/glslang_tab.cpp"
    break;

  case 601: /* struct_declaration: block_heap_inner_structure struct_declarator_list SEMICOLON  */
#line 3917 "MachineIndependent/glslang.y"
                                                                  {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 12256 "MachineIndependent/glslang_tab.cpp"
    break;

  case 602: /* $@5: %empty  */
#line 3934 "MachineIndependent/glslang.y"
                                { parseContext.nestedBlockCheck((yyvsp[-1].interm.type).loc, true); }
#line 12262 "MachineIndependent/glslang_tab.cpp"
    break;

  case 603: /* block_heap_inner_structure: type_qualifier LEFT_BRACE $@5 struct_declaration_no_inline_block_list RIGHT_BRACE  */
#line 3934 "MachineIndependent/glslang.y"
                                                                                                                                     {
        --parseContext.blockNestingLevel;
        parseContext.globalQualifierFixCheck((yyvsp[-4].interm.type).loc, (yyvsp[-4].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-4].interm.type).loc, (yyvsp[-4].interm.type).shaderQualifiers);
        (yyval.interm.type).init((yyvsp[-4].interm.type).loc);
        TType* innerStructure = new TType((yyvsp[-1].interm.typeList), TString(""), (yyvsp[-4].interm.type).qualifier);
        if (! (yyvsp[-4].interm.type).qualifier.hasBufferReference())
            parseContext.error((yyvsp[-4].interm.type).loc, "only buffer_reference blocks can be declared inline inside a heap block", "", "");
        TType* referenceType = new TType(EbtReference, *innerStructure, TString(""));
        (yyval.interm.type).basicType = EbtReference;
        (yyval.interm.type).userDef = referenceType;
        (yyval.interm.type).qualifier.layoutDescriptorHeap = true;
    }
#line 12280 "MachineIndependent/glslang_tab.cpp"
    break;

  case 604: /* struct_declaration_no_inline_block_list: struct_declaration_no_inline_block  */
#line 3950 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 12288 "MachineIndependent/glslang_tab.cpp"
    break;

  case 605: /* struct_declaration_no_inline_block_list: struct_declaration_no_inline_block_list struct_declaration_no_inline_block  */
#line 3953 "MachineIndependent/glslang.y"
                                                                                 {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 12303 "MachineIndependent/glslang_tab.cpp"
    break;

  case 606: /* struct_declaration_no_inline_block: type_specifier struct_declarator_list SEMICOLON  */
#line 3966 "MachineIndependent/glslang.y"
                                                      {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 12330 "MachineIndependent/glslang_tab.cpp"
    break;

  case 607: /* struct_declaration_no_inline_block: type_qualifier type_specifier struct_declarator_list SEMICOLON  */
#line 3988 "MachineIndependent/glslang.y"
                                                                     {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.memberQualifierCheck((yyvsp[-3].interm.type));
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, (yyvsp[-3].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 12359 "MachineIndependent/glslang_tab.cpp"
    break;

  case 608: /* struct_declarator_list: struct_declarator  */
#line 4015 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 12368 "MachineIndependent/glslang_tab.cpp"
    break;

  case 609: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 4019 "MachineIndependent/glslang.y"
                                                     {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 12376 "MachineIndependent/glslang_tab.cpp"
    break;

  case 610: /* struct_declarator: IDENTIFIER  */
#line 4025 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 12386 "MachineIndependent/glslang_tab.cpp"
    break;

  case 611: /* struct_declarator: IDENTIFIER array_specifier  */
#line 4030 "MachineIndependent/glslang.y"
                                 {
        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->transferArraySizes((yyvsp[0].interm).arraySizes);
    }
#line 12399 "MachineIndependent/glslang_tab.cpp"
    break;

  case 612: /* initializer: assignment_expression  */
#line 4041 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 12407 "MachineIndependent/glslang_tab.cpp"
    break;

  case 613: /* initializer: LEFT_BRACE initializer_list RIGHT_BRACE  */
#line 4044 "MachineIndependent/glslang.y"
                                              {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 12418 "MachineIndependent/glslang_tab.cpp"
    break;

  case 614: /* initializer: LEFT_BRACE initializer_list COMMA RIGHT_BRACE  */
#line 4050 "MachineIndependent/glslang.y"
                                                    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 12429 "MachineIndependent/glslang_tab.cpp"
    break;

  case 615: /* initializer: LEFT_BRACE RIGHT_BRACE  */
#line 4056 "MachineIndependent/glslang.y"
                             {
        const char* initFeature = "empty { } initializer";
        parseContext.profileRequires((yyvsp[-1].lex).loc, EEsProfile, 0, E_GL_EXT_null_initializer, initFeature);
        parseContext.profileRequires((yyvsp[-1].lex).loc, ~EEsProfile, 0, E_GL_EXT_null_initializer, initFeature);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.makeAggregate((yyvsp[-1].lex).loc);
    }
#line 12440 "MachineIndependent/glslang_tab.cpp"
    break;

  case 616: /* initializer_list: initializer  */
#line 4065 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 12448 "MachineIndependent/glslang_tab.cpp"
    break;

  case 617: /* initializer_list: initializer_list COMMA initializer  */
#line 4068 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 12456 "MachineIndependent/glslang_tab.cpp"
    break;

  case 618: /* declaration_statement: declaration  */
#line 4074 "MachineIndependent/glslang.y"
                  { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12462 "MachineIndependent/glslang_tab.cpp"
    break;

  case 619: /* statement: compound_statement  */
#line 4078 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12468 "MachineIndependent/glslang_tab.cpp"
    break;

  case 620: /* statement: simple_statement  */
#line 4079 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12474 "MachineIndependent/glslang_tab.cpp"
    break;

  case 621: /* simple_statement: declaration_statement  */
#line 4085 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12480 "MachineIndependent/glslang_tab.cpp"
    break;

  case 622: /* simple_statement: expression_statement  */
#line 4086 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12486 "MachineIndependent/glslang_tab.cpp"
    break;

  case 623: /* simple_statement: selection_statement  */
#line 4087 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12492 "MachineIndependent/glslang_tab.cpp"
    break;

  case 624: /* simple_statement: switch_statement  */
#line 4088 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12498 "MachineIndependent/glslang_tab.cpp"
    break;

  case 625: /* simple_statement: case_label  */
#line 4089 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12504 "MachineIndependent/glslang_tab.cpp"
    break;

  case 626: /* simple_statement: iteration_statement  */
#line 4090 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12510 "MachineIndependent/glslang_tab.cpp"
    break;

  case 627: /* simple_statement: jump_statement  */
#line 4091 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12516 "MachineIndependent/glslang_tab.cpp"
    break;

  case 628: /* simple_statement: demote_statement  */
#line 4092 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12522 "MachineIndependent/glslang_tab.cpp"
    break;

  case 629: /* demote_statement: DEMOTE SEMICOLON  */
#line 4096 "MachineIndependent/glslang.y"
                       {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "demote");
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 1, &E_GL_EXT_demote_to_helper_invocation, "demote");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDemote, (yyvsp[-1].lex).loc);
    }
#line 12532 "MachineIndependent/glslang_tab.cpp"
    break;

  case 630: /* compound_statement: LEFT_BRACE RIGHT_BRACE  */
#line 4104 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermNode) = 0; }
#line 12538 "MachineIndependent/glslang_tab.cpp"
    break;

  case 631: /* $@6: %empty  */
#line 4105 "MachineIndependent/glslang.y"
                 {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 12547 "MachineIndependent/glslang_tab.cpp"
    break;

  case 632: /* $@7: %empty  */
#line 4109 "MachineIndependent/glslang.y"
                     {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 12556 "MachineIndependent/glslang_tab.cpp"
    break;

  case 633: /* compound_statement: LEFT_BRACE $@6 statement_list $@7 RIGHT_BRACE  */
#line 4113 "MachineIndependent/glslang.y"
                  {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate()) {
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(parseContext.intermediate.getDebugInfo() ? EOpScope : EOpSequence);
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setEndLoc((yyvsp[0].lex).loc);
        }
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 12568 "MachineIndependent/glslang_tab.cpp"
    break;

  case 634: /* statement_no_new_scope: compound_statement_no_new_scope  */
#line 4123 "MachineIndependent/glslang.y"
                                      { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12574 "MachineIndependent/glslang_tab.cpp"
    break;

  case 635: /* statement_no_new_scope: simple_statement  */
#line 4124 "MachineIndependent/glslang.y"
                                      { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12580 "MachineIndependent/glslang_tab.cpp"
    break;

  case 636: /* $@8: %empty  */
#line 4128 "MachineIndependent/glslang.y"
      {
        ++parseContext.controlFlowNestingLevel;
    }
#line 12588 "MachineIndependent/glslang_tab.cpp"
    break;

  case 637: /* statement_scoped: $@8 compound_statement  */
#line 4131 "MachineIndependent/glslang.y"
                          {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12597 "MachineIndependent/glslang_tab.cpp"
    break;

  case 638: /* $@9: %empty  */
#line 4135 "MachineIndependent/glslang.y"
      {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12607 "MachineIndependent/glslang_tab.cpp"
    break;

  case 639: /* statement_scoped: $@9 simple_statement  */
#line 4140 "MachineIndependent/glslang.y"
                       {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12618 "MachineIndependent/glslang_tab.cpp"
    break;

  case 640: /* compound_statement_no_new_scope: LEFT_BRACE RIGHT_BRACE  */
#line 4149 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.intermNode) = 0;
    }
#line 12626 "MachineIndependent/glslang_tab.cpp"
    break;

  case 641: /* compound_statement_no_new_scope: LEFT_BRACE statement_list RIGHT_BRACE  */
#line 4152 "MachineIndependent/glslang.y"
                                            {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate()) {
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setEndLoc((yyvsp[0].lex).loc);
        }
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 12638 "MachineIndependent/glslang_tab.cpp"
    break;

  case 642: /* statement_list: statement  */
#line 4162 "MachineIndependent/glslang.y"
                {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 12651 "MachineIndependent/glslang_tab.cpp"
    break;

  case 643: /* statement_list: statement_list statement  */
#line 4170 "MachineIndependent/glslang.y"
                               {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 12664 "MachineIndependent/glslang_tab.cpp"
    break;

  case 644: /* expression_statement: SEMICOLON  */
#line 4181 "MachineIndependent/glslang.y"
                 { (yyval.interm.intermNode) = 0; }
#line 12670 "MachineIndependent/glslang_tab.cpp"
    break;

  case 645: /* expression_statement: expression SEMICOLON  */
#line 4182 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 12676 "MachineIndependent/glslang_tab.cpp"
    break;

  case 646: /* selection_statement: selection_statement_nonattributed  */
#line 4186 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12684 "MachineIndependent/glslang_tab.cpp"
    break;

  case 647: /* selection_statement: attribute selection_statement_nonattributed  */
#line 4189 "MachineIndependent/glslang.y"
                                                  {
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 1, &E_GL_EXT_control_flow_attributes, "attribute");
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12694 "MachineIndependent/glslang_tab.cpp"
    break;

  case 648: /* selection_statement_nonattributed: IF LEFT_PAREN expression RIGHT_PAREN selection_rest_statement  */
#line 4196 "MachineIndependent/glslang.y"
                                                                    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 12703 "MachineIndependent/glslang_tab.cpp"
    break;

  case 649: /* selection_rest_statement: statement_scoped ELSE statement_scoped  */
#line 4203 "MachineIndependent/glslang.y"
                                             {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 12712 "MachineIndependent/glslang_tab.cpp"
    break;

  case 650: /* selection_rest_statement: statement_scoped  */
#line 4207 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 12721 "MachineIndependent/glslang_tab.cpp"
    break;

  case 651: /* condition: expression  */
#line 4215 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 12730 "MachineIndependent/glslang_tab.cpp"
    break;

  case 652: /* condition: fully_specified_type IDENTIFIER EQUAL initializer  */
#line 4219 "MachineIndependent/glslang.y"
                                                        {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        (yyval.interm.intermNode) = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
    }
#line 12741 "MachineIndependent/glslang_tab.cpp"
    break;

  case 653: /* switch_statement: switch_statement_nonattributed  */
#line 4228 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12749 "MachineIndependent/glslang_tab.cpp"
    break;

  case 654: /* switch_statement: attribute switch_statement_nonattributed  */
#line 4231 "MachineIndependent/glslang.y"
                                               {
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 1, &E_GL_EXT_control_flow_attributes, "attribute");
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12759 "MachineIndependent/glslang_tab.cpp"
    break;

  case 655: /* $@10: %empty  */
#line 4238 "MachineIndependent/glslang.y"
                                               {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 12772 "MachineIndependent/glslang_tab.cpp"
    break;

  case 656: /* switch_statement_nonattributed: SWITCH LEFT_PAREN expression RIGHT_PAREN $@10 LEFT_BRACE switch_statement_list RIGHT_BRACE  */
#line 4246 "MachineIndependent/glslang.y"
                                                 {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12786 "MachineIndependent/glslang_tab.cpp"
    break;

  case 657: /* switch_statement_list: %empty  */
#line 4258 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = 0;
    }
#line 12794 "MachineIndependent/glslang_tab.cpp"
    break;

  case 658: /* switch_statement_list: statement_list  */
#line 4261 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12802 "MachineIndependent/glslang_tab.cpp"
    break;

  case 659: /* case_label: CASE expression COLON  */
#line 4267 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-2].lex).loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-2].lex).loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck((yyvsp[-1].interm.intermTypedNode), "case");
            parseContext.integerCheck((yyvsp[-1].interm.intermTypedNode), "case");
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpCase, (yyvsp[-1].interm.intermTypedNode), (yyvsp[-2].lex).loc);
        }
    }
#line 12819 "MachineIndependent/glslang_tab.cpp"
    break;

  case 660: /* case_label: DEFAULT COLON  */
#line 4279 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 12833 "MachineIndependent/glslang_tab.cpp"
    break;

  case 661: /* iteration_statement: iteration_statement_nonattributed  */
#line 4291 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12841 "MachineIndependent/glslang_tab.cpp"
    break;

  case 662: /* iteration_statement: attribute iteration_statement_nonattributed  */
#line 4294 "MachineIndependent/glslang.y"
                                                  {
        const char * extensions[3] = { E_GL_EXT_control_flow_attributes, E_GL_EXT_control_flow_attributes2, E_GL_QCOM_multiple_wait_queues };
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 3, extensions, "attribute");
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12852 "MachineIndependent/glslang_tab.cpp"
    break;

  case 663: /* $@11: %empty  */
#line 4302 "MachineIndependent/glslang.y"
                       {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12865 "MachineIndependent/glslang_tab.cpp"
    break;

  case 664: /* iteration_statement_nonattributed: WHILE LEFT_PAREN $@11 condition RIGHT_PAREN statement_no_new_scope  */
#line 4310 "MachineIndependent/glslang.y"
                                                   {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermNode), 0, true, (yyvsp[-5].lex).loc);
        if (parseContext.intermediate.getDebugInfo()) {
            (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyval.interm.intermNode), (yyvsp[-5].lex).loc);
            (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpScope);
        }
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12881 "MachineIndependent/glslang_tab.cpp"
    break;

  case 665: /* $@12: %empty  */
#line 4321 "MachineIndependent/glslang.y"
         {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12892 "MachineIndependent/glslang_tab.cpp"
    break;

  case 666: /* iteration_statement_nonattributed: DO $@12 statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON  */
#line 4327 "MachineIndependent/glslang.y"
                                                                  {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        if (parseContext.intermediate.getDebugInfo()) {
            (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyval.interm.intermNode), (yyvsp[-4].lex).loc);
            (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpScope);
        }
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12913 "MachineIndependent/glslang_tab.cpp"
    break;

  case 667: /* $@13: %empty  */
#line 4343 "MachineIndependent/glslang.y"
                     {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12924 "MachineIndependent/glslang_tab.cpp"
    break;

  case 668: /* iteration_statement_nonattributed: FOR LEFT_PAREN $@13 for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope  */
#line 4349 "MachineIndependent/glslang.y"
                                                                               {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[-3].interm.intermNode), (yyvsp[-5].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node2), true, (yyvsp[-6].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[-6].lex).loc, (yyvsp[-3].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[-6].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(parseContext.intermediate.getDebugInfo() ? EOpScope : EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12941 "MachineIndependent/glslang_tab.cpp"
    break;

  case 669: /* for_init_statement: expression_statement  */
#line 4364 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12949 "MachineIndependent/glslang_tab.cpp"
    break;

  case 670: /* for_init_statement: declaration_statement  */
#line 4367 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12957 "MachineIndependent/glslang_tab.cpp"
    break;

  case 671: /* conditionopt: condition  */
#line 4373 "MachineIndependent/glslang.y"
                {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12965 "MachineIndependent/glslang_tab.cpp"
    break;

  case 672: /* conditionopt: %empty  */
#line 4376 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.intermNode) = 0;
    }
#line 12973 "MachineIndependent/glslang_tab.cpp"
    break;

  case 673: /* for_rest_statement: conditionopt SEMICOLON  */
#line 4382 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 12982 "MachineIndependent/glslang_tab.cpp"
    break;

  case 674: /* for_rest_statement: conditionopt SEMICOLON expression  */
#line 4386 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 12991 "MachineIndependent/glslang_tab.cpp"
    break;

  case 675: /* jump_statement: CONTINUE SEMICOLON  */
#line 4393 "MachineIndependent/glslang.y"
                         {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 13001 "MachineIndependent/glslang_tab.cpp"
    break;

  case 676: /* jump_statement: BREAK SEMICOLON  */
#line 4398 "MachineIndependent/glslang.y"
                      {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 13011 "MachineIndependent/glslang_tab.cpp"
    break;

  case 677: /* jump_statement: RETURN SEMICOLON  */
#line 4403 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 13023 "MachineIndependent/glslang_tab.cpp"
    break;

  case 678: /* jump_statement: RETURN expression SEMICOLON  */
#line 4410 "MachineIndependent/glslang.y"
                                  {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 13031 "MachineIndependent/glslang_tab.cpp"
    break;

  case 679: /* jump_statement: DISCARD SEMICOLON  */
#line 4413 "MachineIndependent/glslang.y"
                        {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 13040 "MachineIndependent/glslang_tab.cpp"
    break;

  case 680: /* jump_statement: TERMINATE_INVOCATION SEMICOLON  */
#line 4417 "MachineIndependent/glslang.y"
                                     {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "terminateInvocation");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpTerminateInvocation, (yyvsp[-1].lex).loc);
    }
#line 13049 "MachineIndependent/glslang_tab.cpp"
    break;

  case 681: /* jump_statement: TERMINATE_RAY SEMICOLON  */
#line 4421 "MachineIndependent/glslang.y"
                              {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangAnyHit, "terminateRayEXT");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpTerminateRayKHR, (yyvsp[-1].lex).loc);
    }
#line 13058 "MachineIndependent/glslang_tab.cpp"
    break;

  case 682: /* jump_statement: IGNORE_INTERSECTION SEMICOLON  */
#line 4425 "MachineIndependent/glslang.y"
                                    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangAnyHit, "ignoreIntersectionEXT");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpIgnoreIntersectionKHR, (yyvsp[-1].lex).loc);
    }
#line 13067 "MachineIndependent/glslang_tab.cpp"
    break;

  case 683: /* translation_unit: external_declaration  */
#line 4434 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 13076 "MachineIndependent/glslang_tab.cpp"
    break;

  case 684: /* translation_unit: translation_unit external_declaration  */
#line 4438 "MachineIndependent/glslang.y"
                                            {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 13087 "MachineIndependent/glslang_tab.cpp"
    break;

  case 685: /* external_declaration: function_definition  */
#line 4447 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 13095 "MachineIndependent/glslang_tab.cpp"
    break;

  case 686: /* external_declaration: declaration  */
#line 4450 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 13103 "MachineIndependent/glslang_tab.cpp"
    break;

  case 687: /* external_declaration: SEMICOLON  */
#line 4453 "MachineIndependent/glslang.y"
                {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 13113 "MachineIndependent/glslang_tab.cpp"
    break;

  case 688: /* $@14: %empty  */
#line 4461 "MachineIndependent/glslang.y"
                         {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);

        // For ES 100 only, according to ES shading language 100 spec: A function
        // body has a scope nested inside the function's definition.
        if (parseContext.profile == EEsProfile && parseContext.version == 100)
        {
            parseContext.symbolTable.push();
            ++parseContext.statementNestingLevel;
        }
    }
#line 13130 "MachineIndependent/glslang_tab.cpp"
    break;

  case 689: /* function_definition: function_prototype $@14 compound_statement_no_new_scope  */
#line 4473 "MachineIndependent/glslang.y"
                                    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[-2].interm).loc, "function does not return a value:", "", (yyvsp[-2].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode)->getAsAggregate()->setLinkType((yyvsp[-2].interm).function->getLinkType());
        (yyval.interm.intermNode)->getAsAggregate()->setFunctionControl((yyvsp[-2].interm).function->getFunctionControl());
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[-2].interm).function->getType(), (yyvsp[-2].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[-2].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->setPragmaTable(parseContext.contextPragma.pragmaTable);

        // Set currentFunctionType to empty pointer when goes outside of the function
        parseContext.currentFunctionType = nullptr;

        // For ES 100 only, according to ES shading language 100 spec: A function
        // body has a scope nested inside the function's definition.
        if (parseContext.profile == EEsProfile && parseContext.version == 100)
        {
            parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
            --parseContext.statementNestingLevel;
        }
    }
#line 13163 "MachineIndependent/glslang_tab.cpp"
    break;

  case 690: /* attribute: LEFT_BRACKET LEFT_BRACKET attribute_list RIGHT_BRACKET RIGHT_BRACKET  */
#line 4504 "MachineIndependent/glslang.y"
                                                                           {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
    }
#line 13171 "MachineIndependent/glslang_tab.cpp"
    break;

  case 691: /* attribute_list: single_attribute  */
#line 4509 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 13179 "MachineIndependent/glslang_tab.cpp"
    break;

  case 692: /* attribute_list: attribute_list COMMA single_attribute  */
#line 4512 "MachineIndependent/glslang.y"
                                            {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 13187 "MachineIndependent/glslang_tab.cpp"
    break;

  case 693: /* single_attribute: IDENTIFIER  */
#line 4517 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 13195 "MachineIndependent/glslang_tab.cpp"
    break;

  case 694: /* single_attribute: IDENTIFIER LEFT_PAREN constant_expression RIGHT_PAREN  */
#line 4520 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 13203 "MachineIndependent/glslang_tab.cpp"
    break;

  case 695: /* single_attribute: INLINE  */
#line 4523 "MachineIndependent/glslang.y"
             {
        (yyval.interm.attributes) = parseContext.makeAttributes(TString("inline"));
    }
#line 13211 "MachineIndependent/glslang_tab.cpp"
    break;

  case 696: /* single_attribute: NOINLINE  */
#line 4526 "MachineIndependent/glslang.y"
               {
        (yyval.interm.attributes) = parseContext.makeAttributes(TString("noinline"));
    }
#line 13219 "MachineIndependent/glslang_tab.cpp"
    break;

  case 697: /* spirv_requirements_list: spirv_requirements_parameter  */
#line 4531 "MachineIndependent/glslang.y"
                                   {
        (yyval.interm.spirvReq) = (yyvsp[0].interm.spirvReq);
    }
#line 13227 "MachineIndependent/glslang_tab.cpp"
    break;

  case 698: /* spirv_requirements_list: spirv_requirements_list COMMA spirv_requirements_parameter  */
#line 4534 "MachineIndependent/glslang.y"
                                                                 {
        (yyval.interm.spirvReq) = parseContext.mergeSpirvRequirements((yyvsp[-1].lex).loc, (yyvsp[-2].interm.spirvReq), (yyvsp[0].interm.spirvReq));
    }
#line 13235 "MachineIndependent/glslang_tab.cpp"
    break;

  case 699: /* spirv_requirements_parameter: IDENTIFIER EQUAL LEFT_BRACKET spirv_extension_list RIGHT_BRACKET  */
#line 4539 "MachineIndependent/glslang.y"
                                                                       {
        (yyval.interm.spirvReq) = parseContext.makeSpirvRequirement((yyvsp[-3].lex).loc, *(yyvsp[-4].lex).string, (yyvsp[-1].interm.intermNode)->getAsAggregate(), nullptr);
    }
#line 13243 "MachineIndependent/glslang_tab.cpp"
    break;

  case 700: /* spirv_requirements_parameter: IDENTIFIER EQUAL LEFT_BRACKET spirv_capability_list RIGHT_BRACKET  */
#line 4542 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm.spirvReq) = parseContext.makeSpirvRequirement((yyvsp[-3].lex).loc, *(yyvsp[-4].lex).string, nullptr, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13251 "MachineIndependent/glslang_tab.cpp"
    break;

  case 701: /* spirv_extension_list: STRING_LITERAL  */
#line 4547 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13259 "MachineIndependent/glslang_tab.cpp"
    break;

  case 702: /* spirv_extension_list: spirv_extension_list COMMA STRING_LITERAL  */
#line 4550 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13267 "MachineIndependent/glslang_tab.cpp"
    break;

  case 703: /* spirv_capability_list: INTCONSTANT  */
#line 4555 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true));
    }
#line 13275 "MachineIndependent/glslang_tab.cpp"
    break;

  case 704: /* spirv_capability_list: spirv_capability_list COMMA INTCONSTANT  */
#line 4558 "MachineIndependent/glslang.y"
                                              {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true));
    }
#line 13283 "MachineIndependent/glslang_tab.cpp"
    break;

  case 705: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4563 "MachineIndependent/glslang.y"
                                                              {
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-1].lex).i);
        (yyval.interm.intermNode) = 0;
    }
#line 13292 "MachineIndependent/glslang_tab.cpp"
    break;

  case 706: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4567 "MachineIndependent/glslang.y"
                                                                                            {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-1].lex).i);
        (yyval.interm.intermNode) = 0;
    }
#line 13302 "MachineIndependent/glslang_tab.cpp"
    break;

  case 707: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN INTCONSTANT COMMA spirv_execution_mode_parameter_list RIGHT_PAREN  */
#line 4572 "MachineIndependent/glslang.y"
                                                                                                        {
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13311 "MachineIndependent/glslang_tab.cpp"
    break;

  case 708: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_execution_mode_parameter_list RIGHT_PAREN  */
#line 4576 "MachineIndependent/glslang.y"
                                                                                                                                      {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13321 "MachineIndependent/glslang_tab.cpp"
    break;

  case 709: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE_ID LEFT_PAREN INTCONSTANT COMMA spirv_execution_mode_id_parameter_list RIGHT_PAREN  */
#line 4581 "MachineIndependent/glslang.y"
                                                                                                              {
        parseContext.intermediate.insertSpirvExecutionModeId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13330 "MachineIndependent/glslang_tab.cpp"
    break;

  case 710: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE_ID LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_execution_mode_id_parameter_list RIGHT_PAREN  */
#line 4585 "MachineIndependent/glslang.y"
                                                                                                                                            {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionModeId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13340 "MachineIndependent/glslang_tab.cpp"
    break;

  case 711: /* spirv_execution_mode_parameter_list: spirv_execution_mode_parameter  */
#line 4592 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13348 "MachineIndependent/glslang_tab.cpp"
    break;

  case 712: /* spirv_execution_mode_parameter_list: spirv_execution_mode_parameter_list COMMA spirv_execution_mode_parameter  */
#line 4595 "MachineIndependent/glslang.y"
                                                                               {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13356 "MachineIndependent/glslang_tab.cpp"
    break;

  case 713: /* spirv_execution_mode_parameter: FLOATCONSTANT  */
#line 4600 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13364 "MachineIndependent/glslang_tab.cpp"
    break;

  case 714: /* spirv_execution_mode_parameter: INTCONSTANT  */
#line 4603 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13372 "MachineIndependent/glslang_tab.cpp"
    break;

  case 715: /* spirv_execution_mode_parameter: UINTCONSTANT  */
#line 4606 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13380 "MachineIndependent/glslang_tab.cpp"
    break;

  case 716: /* spirv_execution_mode_parameter: BOOLCONSTANT  */
#line 4609 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13388 "MachineIndependent/glslang_tab.cpp"
    break;

  case 717: /* spirv_execution_mode_parameter: STRING_LITERAL  */
#line 4612 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true);
    }
#line 13396 "MachineIndependent/glslang_tab.cpp"
    break;

  case 718: /* spirv_execution_mode_id_parameter_list: constant_expression  */
#line 4617 "MachineIndependent/glslang.y"
                          {
        if ((yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtFloat &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtInt &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtUint &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtBool &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtString)
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "this type not allowed", (yyvsp[0].interm.intermTypedNode)->getType().getBasicString(), "");
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermTypedNode));
    }
#line 13410 "MachineIndependent/glslang_tab.cpp"
    break;

  case 719: /* spirv_execution_mode_id_parameter_list: spirv_execution_mode_id_parameter_list COMMA constant_expression  */
#line 4626 "MachineIndependent/glslang.y"
                                                                       {
        if ((yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtFloat &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtInt &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtUint &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtBool &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtString)
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "this type not allowed", (yyvsp[0].interm.intermTypedNode)->getType().getBasicString(), "");
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 13424 "MachineIndependent/glslang_tab.cpp"
    break;

  case 720: /* spirv_storage_class_qualifier: SPIRV_STORAGE_CLASS LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4637 "MachineIndependent/glslang.y"
                                                             {
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqSpirvStorageClass;
        (yyval.interm.type).qualifier.spirvStorageClass = (yyvsp[-1].lex).i;
    }
#line 13434 "MachineIndependent/glslang_tab.cpp"
    break;

  case 721: /* spirv_storage_class_qualifier: SPIRV_STORAGE_CLASS LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4642 "MachineIndependent/glslang.y"
                                                                                           {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).qualifier.storage = EvqSpirvStorageClass;
        (yyval.interm.type).qualifier.spirvStorageClass = (yyvsp[-1].lex).i;
    }
#line 13445 "MachineIndependent/glslang_tab.cpp"
    break;

  case 722: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4650 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-1].lex).i);
    }
#line 13454 "MachineIndependent/glslang_tab.cpp"
    break;

  case 723: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4654 "MachineIndependent/glslang.y"
                                                                                     {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-1].lex).i);
    }
#line 13464 "MachineIndependent/glslang_tab.cpp"
    break;

  case 724: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN INTCONSTANT COMMA spirv_decorate_parameter_list RIGHT_PAREN  */
#line 4659 "MachineIndependent/glslang.y"
                                                                                            {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13473 "MachineIndependent/glslang_tab.cpp"
    break;

  case 725: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_parameter_list RIGHT_PAREN  */
#line 4663 "MachineIndependent/glslang.y"
                                                                                                                          {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13483 "MachineIndependent/glslang_tab.cpp"
    break;

  case 726: /* spirv_decorate_qualifier: SPIRV_DECORATE_ID LEFT_PAREN INTCONSTANT COMMA spirv_decorate_id_parameter_list RIGHT_PAREN  */
#line 4668 "MachineIndependent/glslang.y"
                                                                                                  {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorateId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13492 "MachineIndependent/glslang_tab.cpp"
    break;

  case 727: /* spirv_decorate_qualifier: SPIRV_DECORATE_ID LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_id_parameter_list RIGHT_PAREN  */
#line 4672 "MachineIndependent/glslang.y"
                                                                                                                                {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorateId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13502 "MachineIndependent/glslang_tab.cpp"
    break;

  case 728: /* spirv_decorate_qualifier: SPIRV_DECORATE_STRING LEFT_PAREN INTCONSTANT COMMA spirv_decorate_string_parameter_list RIGHT_PAREN  */
#line 4677 "MachineIndependent/glslang.y"
                                                                                                          {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorateString((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13511 "MachineIndependent/glslang_tab.cpp"
    break;

  case 729: /* spirv_decorate_qualifier: SPIRV_DECORATE_STRING LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_string_parameter_list RIGHT_PAREN  */
#line 4681 "MachineIndependent/glslang.y"
                                                                                                                                        {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorateString((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13521 "MachineIndependent/glslang_tab.cpp"
    break;

  case 730: /* spirv_decorate_parameter_list: spirv_decorate_parameter  */
#line 4688 "MachineIndependent/glslang.y"
                               {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13529 "MachineIndependent/glslang_tab.cpp"
    break;

  case 731: /* spirv_decorate_parameter_list: spirv_decorate_parameter_list COMMA spirv_decorate_parameter  */
#line 4691 "MachineIndependent/glslang.y"
                                                                   {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13537 "MachineIndependent/glslang_tab.cpp"
    break;

  case 732: /* spirv_decorate_parameter: FLOATCONSTANT  */
#line 4696 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13545 "MachineIndependent/glslang_tab.cpp"
    break;

  case 733: /* spirv_decorate_parameter: INTCONSTANT  */
#line 4699 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13553 "MachineIndependent/glslang_tab.cpp"
    break;

  case 734: /* spirv_decorate_parameter: UINTCONSTANT  */
#line 4702 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13561 "MachineIndependent/glslang_tab.cpp"
    break;

  case 735: /* spirv_decorate_parameter: BOOLCONSTANT  */
#line 4705 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13569 "MachineIndependent/glslang_tab.cpp"
    break;

  case 736: /* spirv_decorate_id_parameter_list: spirv_decorate_id_parameter  */
#line 4710 "MachineIndependent/glslang.y"
                                  {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13577 "MachineIndependent/glslang_tab.cpp"
    break;

  case 737: /* spirv_decorate_id_parameter_list: spirv_decorate_id_parameter_list COMMA spirv_decorate_id_parameter  */
#line 4713 "MachineIndependent/glslang.y"
                                                                         {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13585 "MachineIndependent/glslang_tab.cpp"
    break;

  case 738: /* spirv_decorate_id_parameter: variable_identifier  */
#line 4718 "MachineIndependent/glslang.y"
                          {
        if ((yyvsp[0].interm.intermTypedNode)->getAsConstantUnion() || (yyvsp[0].interm.intermTypedNode)->getAsSymbolNode())
            (yyval.interm.intermNode) = (yyvsp[0].interm.intermTypedNode);
        else
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "only allow constants or variables which are not elements of a composite", "", "");
    }
#line 13596 "MachineIndependent/glslang_tab.cpp"
    break;

  case 739: /* spirv_decorate_id_parameter: FLOATCONSTANT  */
#line 4724 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13604 "MachineIndependent/glslang_tab.cpp"
    break;

  case 740: /* spirv_decorate_id_parameter: INTCONSTANT  */
#line 4727 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13612 "MachineIndependent/glslang_tab.cpp"
    break;

  case 741: /* spirv_decorate_id_parameter: UINTCONSTANT  */
#line 4730 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13620 "MachineIndependent/glslang_tab.cpp"
    break;

  case 742: /* spirv_decorate_id_parameter: BOOLCONSTANT  */
#line 4733 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13628 "MachineIndependent/glslang_tab.cpp"
    break;

  case 743: /* spirv_decorate_string_parameter_list: STRING_LITERAL  */
#line 4738 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(
            parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13637 "MachineIndependent/glslang_tab.cpp"
    break;

  case 744: /* spirv_decorate_string_parameter_list: spirv_decorate_string_parameter_list COMMA STRING_LITERAL  */
#line 4742 "MachineIndependent/glslang.y"
                                                                {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13645 "MachineIndependent/glslang_tab.cpp"
    break;

  case 745: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_instruction_qualifier_list COMMA spirv_type_parameter_list RIGHT_PAREN  */
#line 4747 "MachineIndependent/glslang.y"
                                                                                                         {
        (yyval.interm.type).init((yyvsp[-5].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).setSpirvType(*(yyvsp[-3].interm.spirvInst), (yyvsp[-1].interm.spirvTypeParams));
    }
#line 13654 "MachineIndependent/glslang_tab.cpp"
    break;

  case 746: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list COMMA spirv_type_parameter_list RIGHT_PAREN  */
#line 4751 "MachineIndependent/glslang.y"
                                                                                                                                       {
        (yyval.interm.type).init((yyvsp[-7].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).setSpirvType(*(yyvsp[-3].interm.spirvInst), (yyvsp[-1].interm.spirvTypeParams));
    }
#line 13664 "MachineIndependent/glslang_tab.cpp"
    break;

  case 747: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4756 "MachineIndependent/glslang.y"
                                                                         {
        (yyval.interm.type).init((yyvsp[-3].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).setSpirvType(*(yyvsp[-1].interm.spirvInst));
    }
#line 13673 "MachineIndependent/glslang_tab.cpp"
    break;

  case 748: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4760 "MachineIndependent/glslang.y"
                                                                                                       {
        (yyval.interm.type).init((yyvsp[-5].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).setSpirvType(*(yyvsp[-1].interm.spirvInst));
    }
#line 13683 "MachineIndependent/glslang_tab.cpp"
    break;

  case 749: /* spirv_type_parameter_list: spirv_type_parameter  */
#line 4767 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.spirvTypeParams) = (yyvsp[0].interm.spirvTypeParams);
    }
#line 13691 "MachineIndependent/glslang_tab.cpp"
    break;

  case 750: /* spirv_type_parameter_list: spirv_type_parameter_list COMMA spirv_type_parameter  */
#line 4770 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.spirvTypeParams) = parseContext.mergeSpirvTypeParameters((yyvsp[-2].interm.spirvTypeParams), (yyvsp[0].interm.spirvTypeParams));
    }
#line 13699 "MachineIndependent/glslang_tab.cpp"
    break;

  case 751: /* spirv_type_parameter: constant_expression  */
#line 4775 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.spirvTypeParams) = parseContext.makeSpirvTypeParameters((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode)->getAsConstantUnion());
    }
#line 13707 "MachineIndependent/glslang_tab.cpp"
    break;

  case 752: /* spirv_type_parameter: type_specifier_nonarray  */
#line 4778 "MachineIndependent/glslang.y"
                              {
        (yyval.interm.spirvTypeParams) = parseContext.makeSpirvTypeParameters((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 13715 "MachineIndependent/glslang_tab.cpp"
    break;

  case 753: /* spirv_instruction_qualifier: SPIRV_INSTRUCTION LEFT_PAREN spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4783 "MachineIndependent/glslang.y"
                                                                                {
        (yyval.interm.spirvInst) = (yyvsp[-1].interm.spirvInst);
    }
#line 13723 "MachineIndependent/glslang_tab.cpp"
    break;

  case 754: /* spirv_instruction_qualifier: SPIRV_INSTRUCTION LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4786 "MachineIndependent/glslang.y"
                                                                                                              {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.spirvInst) = (yyvsp[-1].interm.spirvInst);
    }
#line 13732 "MachineIndependent/glslang_tab.cpp"
    break;

  case 755: /* spirv_instruction_qualifier_list: spirv_instruction_qualifier_id  */
#line 4792 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.spirvInst) = (yyvsp[0].interm.spirvInst);
    }
#line 13740 "MachineIndependent/glslang_tab.cpp"
    break;

  case 756: /* spirv_instruction_qualifier_list: spirv_instruction_qualifier_list COMMA spirv_instruction_qualifier_id  */
#line 4795 "MachineIndependent/glslang.y"
                                                                            {
        (yyval.interm.spirvInst) = parseContext.mergeSpirvInstruction((yyvsp[-1].lex).loc, (yyvsp[-2].interm.spirvInst), (yyvsp[0].interm.spirvInst));
    }
#line 13748 "MachineIndependent/glslang_tab.cpp"
    break;

  case 757: /* spirv_instruction_qualifier_id: IDENTIFIER EQUAL STRING_LITERAL  */
#line 4800 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm.spirvInst) = parseContext.makeSpirvInstruction((yyvsp[-1].lex).loc, *(yyvsp[-2].lex).string, *(yyvsp[0].lex).string);
    }
#line 13756 "MachineIndependent/glslang_tab.cpp"
    break;

  case 758: /* spirv_instruction_qualifier_id: IDENTIFIER EQUAL INTCONSTANT  */
#line 4803 "MachineIndependent/glslang.y"
                                   {
        (yyval.interm.spirvInst) = parseContext.makeSpirvInstruction((yyvsp[-1].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[0].lex).i);
    }
#line 13764 "MachineIndependent/glslang_tab.cpp"
    break;


#line 13768 "MachineIndependent/glslang_tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (pParseContext, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, pParseContext);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (pParseContext, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, pParseContext);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, pParseContext);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 4807 "MachineIndependent/glslang.y"


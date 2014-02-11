/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     CONST_TOK = 259,
     BOOL_TOK = 260,
     FLOAT_TOK = 261,
     INT_TOK = 262,
     UINT_TOK = 263,
     BREAK = 264,
     CONTINUE = 265,
     DO = 266,
     ELSE = 267,
     FOR = 268,
     IF = 269,
     DISCARD = 270,
     RETURN = 271,
     SWITCH = 272,
     CASE = 273,
     DEFAULT = 274,
     BVEC2 = 275,
     BVEC3 = 276,
     BVEC4 = 277,
     IVEC2 = 278,
     IVEC3 = 279,
     IVEC4 = 280,
     UVEC2 = 281,
     UVEC3 = 282,
     UVEC4 = 283,
     VEC2 = 284,
     VEC3 = 285,
     VEC4 = 286,
     CENTROID = 287,
     IN_TOK = 288,
     OUT_TOK = 289,
     INOUT_TOK = 290,
     UNIFORM = 291,
     VARYING = 292,
     NOPERSPECTIVE = 293,
     FLAT = 294,
     SMOOTH = 295,
     MAT2X2 = 296,
     MAT2X3 = 297,
     MAT2X4 = 298,
     MAT3X2 = 299,
     MAT3X3 = 300,
     MAT3X4 = 301,
     MAT4X2 = 302,
     MAT4X3 = 303,
     MAT4X4 = 304,
     SAMPLER1D = 305,
     SAMPLER2D = 306,
     SAMPLER3D = 307,
     SAMPLERCUBE = 308,
     SAMPLER1DSHADOW = 309,
     SAMPLER2DSHADOW = 310,
     SAMPLERCUBESHADOW = 311,
     SAMPLER1DARRAY = 312,
     SAMPLER2DARRAY = 313,
     SAMPLER1DARRAYSHADOW = 314,
     SAMPLER2DARRAYSHADOW = 315,
     SAMPLERCUBEARRAY = 316,
     SAMPLERCUBEARRAYSHADOW = 317,
     ISAMPLER1D = 318,
     ISAMPLER2D = 319,
     ISAMPLER3D = 320,
     ISAMPLERCUBE = 321,
     ISAMPLER1DARRAY = 322,
     ISAMPLER2DARRAY = 323,
     ISAMPLERCUBEARRAY = 324,
     USAMPLER1D = 325,
     USAMPLER2D = 326,
     USAMPLER3D = 327,
     USAMPLERCUBE = 328,
     USAMPLER1DARRAY = 329,
     USAMPLER2DARRAY = 330,
     USAMPLERCUBEARRAY = 331,
     SAMPLER2DRECT = 332,
     ISAMPLER2DRECT = 333,
     USAMPLER2DRECT = 334,
     SAMPLER2DRECTSHADOW = 335,
     SAMPLERBUFFER = 336,
     ISAMPLERBUFFER = 337,
     USAMPLERBUFFER = 338,
     SAMPLER2DMS = 339,
     ISAMPLER2DMS = 340,
     USAMPLER2DMS = 341,
     SAMPLER2DMSARRAY = 342,
     ISAMPLER2DMSARRAY = 343,
     USAMPLER2DMSARRAY = 344,
     SAMPLEREXTERNALOES = 345,
     ATOMIC_UINT = 346,
     STRUCT = 347,
     VOID_TOK = 348,
     WHILE = 349,
     IDENTIFIER = 350,
     TYPE_IDENTIFIER = 351,
     NEW_IDENTIFIER = 352,
     FLOATCONSTANT = 353,
     INTCONSTANT = 354,
     UINTCONSTANT = 355,
     BOOLCONSTANT = 356,
     FIELD_SELECTION = 357,
     LEFT_OP = 358,
     RIGHT_OP = 359,
     INC_OP = 360,
     DEC_OP = 361,
     LE_OP = 362,
     GE_OP = 363,
     EQ_OP = 364,
     NE_OP = 365,
     AND_OP = 366,
     OR_OP = 367,
     XOR_OP = 368,
     MUL_ASSIGN = 369,
     DIV_ASSIGN = 370,
     ADD_ASSIGN = 371,
     MOD_ASSIGN = 372,
     LEFT_ASSIGN = 373,
     RIGHT_ASSIGN = 374,
     AND_ASSIGN = 375,
     XOR_ASSIGN = 376,
     OR_ASSIGN = 377,
     SUB_ASSIGN = 378,
     INVARIANT = 379,
     LOWP = 380,
     MEDIUMP = 381,
     HIGHP = 382,
     SUPERP = 383,
     PRECISION = 384,
     VERSION_TOK = 385,
     EXTENSION = 386,
     LINE = 387,
     COLON = 388,
     EOL = 389,
     INTERFACE = 390,
     OUTPUT = 391,
     PRAGMA_DEBUG_ON = 392,
     PRAGMA_DEBUG_OFF = 393,
     PRAGMA_OPTIMIZE_ON = 394,
     PRAGMA_OPTIMIZE_OFF = 395,
     PRAGMA_INVARIANT_ALL = 396,
     LAYOUT_TOK = 397,
     ASM = 398,
     CLASS = 399,
     UNION = 400,
     ENUM = 401,
     TYPEDEF = 402,
     TEMPLATE = 403,
     THIS = 404,
     PACKED_TOK = 405,
     GOTO = 406,
     INLINE_TOK = 407,
     NOINLINE = 408,
     VOLATILE = 409,
     PUBLIC_TOK = 410,
     STATIC = 411,
     EXTERN = 412,
     EXTERNAL = 413,
     LONG_TOK = 414,
     SHORT_TOK = 415,
     DOUBLE_TOK = 416,
     HALF = 417,
     FIXED_TOK = 418,
     UNSIGNED = 419,
     INPUT_TOK = 420,
     OUPTUT = 421,
     HVEC2 = 422,
     HVEC3 = 423,
     HVEC4 = 424,
     DVEC2 = 425,
     DVEC3 = 426,
     DVEC4 = 427,
     FVEC2 = 428,
     FVEC3 = 429,
     FVEC4 = 430,
     SAMPLER3DRECT = 431,
     SIZEOF = 432,
     CAST = 433,
     NAMESPACE = 434,
     USING = 435,
     COHERENT = 436,
     RESTRICT = 437,
     READONLY = 438,
     WRITEONLY = 439,
     RESOURCE = 440,
     PATCH = 441,
     SAMPLE = 442,
     SUBROUTINE = 443,
     ERROR_TOK = 444,
     COMMON = 445,
     PARTITION = 446,
     ACTIVE = 447,
     FILTER = 448,
     IMAGE1D = 449,
     IMAGE2D = 450,
     IMAGE3D = 451,
     IMAGECUBE = 452,
     IMAGE1DARRAY = 453,
     IMAGE2DARRAY = 454,
     IIMAGE1D = 455,
     IIMAGE2D = 456,
     IIMAGE3D = 457,
     IIMAGECUBE = 458,
     IIMAGE1DARRAY = 459,
     IIMAGE2DARRAY = 460,
     UIMAGE1D = 461,
     UIMAGE2D = 462,
     UIMAGE3D = 463,
     UIMAGECUBE = 464,
     UIMAGE1DARRAY = 465,
     UIMAGE2DARRAY = 466,
     IMAGE1DSHADOW = 467,
     IMAGE2DSHADOW = 468,
     IMAGEBUFFER = 469,
     IIMAGEBUFFER = 470,
     UIMAGEBUFFER = 471,
     IMAGE1DARRAYSHADOW = 472,
     IMAGE2DARRAYSHADOW = 473,
     ROW_MAJOR = 474,
     THEN = 475
   };
#endif
/* Tokens.  */
#define ATTRIBUTE 258
#define CONST_TOK 259
#define BOOL_TOK 260
#define FLOAT_TOK 261
#define INT_TOK 262
#define UINT_TOK 263
#define BREAK 264
#define CONTINUE 265
#define DO 266
#define ELSE 267
#define FOR 268
#define IF 269
#define DISCARD 270
#define RETURN 271
#define SWITCH 272
#define CASE 273
#define DEFAULT 274
#define BVEC2 275
#define BVEC3 276
#define BVEC4 277
#define IVEC2 278
#define IVEC3 279
#define IVEC4 280
#define UVEC2 281
#define UVEC3 282
#define UVEC4 283
#define VEC2 284
#define VEC3 285
#define VEC4 286
#define CENTROID 287
#define IN_TOK 288
#define OUT_TOK 289
#define INOUT_TOK 290
#define UNIFORM 291
#define VARYING 292
#define NOPERSPECTIVE 293
#define FLAT 294
#define SMOOTH 295
#define MAT2X2 296
#define MAT2X3 297
#define MAT2X4 298
#define MAT3X2 299
#define MAT3X3 300
#define MAT3X4 301
#define MAT4X2 302
#define MAT4X3 303
#define MAT4X4 304
#define SAMPLER1D 305
#define SAMPLER2D 306
#define SAMPLER3D 307
#define SAMPLERCUBE 308
#define SAMPLER1DSHADOW 309
#define SAMPLER2DSHADOW 310
#define SAMPLERCUBESHADOW 311
#define SAMPLER1DARRAY 312
#define SAMPLER2DARRAY 313
#define SAMPLER1DARRAYSHADOW 314
#define SAMPLER2DARRAYSHADOW 315
#define SAMPLERCUBEARRAY 316
#define SAMPLERCUBEARRAYSHADOW 317
#define ISAMPLER1D 318
#define ISAMPLER2D 319
#define ISAMPLER3D 320
#define ISAMPLERCUBE 321
#define ISAMPLER1DARRAY 322
#define ISAMPLER2DARRAY 323
#define ISAMPLERCUBEARRAY 324
#define USAMPLER1D 325
#define USAMPLER2D 326
#define USAMPLER3D 327
#define USAMPLERCUBE 328
#define USAMPLER1DARRAY 329
#define USAMPLER2DARRAY 330
#define USAMPLERCUBEARRAY 331
#define SAMPLER2DRECT 332
#define ISAMPLER2DRECT 333
#define USAMPLER2DRECT 334
#define SAMPLER2DRECTSHADOW 335
#define SAMPLERBUFFER 336
#define ISAMPLERBUFFER 337
#define USAMPLERBUFFER 338
#define SAMPLER2DMS 339
#define ISAMPLER2DMS 340
#define USAMPLER2DMS 341
#define SAMPLER2DMSARRAY 342
#define ISAMPLER2DMSARRAY 343
#define USAMPLER2DMSARRAY 344
#define SAMPLEREXTERNALOES 345
#define ATOMIC_UINT 346
#define STRUCT 347
#define VOID_TOK 348
#define WHILE 349
#define IDENTIFIER 350
#define TYPE_IDENTIFIER 351
#define NEW_IDENTIFIER 352
#define FLOATCONSTANT 353
#define INTCONSTANT 354
#define UINTCONSTANT 355
#define BOOLCONSTANT 356
#define FIELD_SELECTION 357
#define LEFT_OP 358
#define RIGHT_OP 359
#define INC_OP 360
#define DEC_OP 361
#define LE_OP 362
#define GE_OP 363
#define EQ_OP 364
#define NE_OP 365
#define AND_OP 366
#define OR_OP 367
#define XOR_OP 368
#define MUL_ASSIGN 369
#define DIV_ASSIGN 370
#define ADD_ASSIGN 371
#define MOD_ASSIGN 372
#define LEFT_ASSIGN 373
#define RIGHT_ASSIGN 374
#define AND_ASSIGN 375
#define XOR_ASSIGN 376
#define OR_ASSIGN 377
#define SUB_ASSIGN 378
#define INVARIANT 379
#define LOWP 380
#define MEDIUMP 381
#define HIGHP 382
#define SUPERP 383
#define PRECISION 384
#define VERSION_TOK 385
#define EXTENSION 386
#define LINE 387
#define COLON 388
#define EOL 389
#define INTERFACE 390
#define OUTPUT 391
#define PRAGMA_DEBUG_ON 392
#define PRAGMA_DEBUG_OFF 393
#define PRAGMA_OPTIMIZE_ON 394
#define PRAGMA_OPTIMIZE_OFF 395
#define PRAGMA_INVARIANT_ALL 396
#define LAYOUT_TOK 397
#define ASM 398
#define CLASS 399
#define UNION 400
#define ENUM 401
#define TYPEDEF 402
#define TEMPLATE 403
#define THIS 404
#define PACKED_TOK 405
#define GOTO 406
#define INLINE_TOK 407
#define NOINLINE 408
#define VOLATILE 409
#define PUBLIC_TOK 410
#define STATIC 411
#define EXTERN 412
#define EXTERNAL 413
#define LONG_TOK 414
#define SHORT_TOK 415
#define DOUBLE_TOK 416
#define HALF 417
#define FIXED_TOK 418
#define UNSIGNED 419
#define INPUT_TOK 420
#define OUPTUT 421
#define HVEC2 422
#define HVEC3 423
#define HVEC4 424
#define DVEC2 425
#define DVEC3 426
#define DVEC4 427
#define FVEC2 428
#define FVEC3 429
#define FVEC4 430
#define SAMPLER3DRECT 431
#define SIZEOF 432
#define CAST 433
#define NAMESPACE 434
#define USING 435
#define COHERENT 436
#define RESTRICT 437
#define READONLY 438
#define WRITEONLY 439
#define RESOURCE 440
#define PATCH 441
#define SAMPLE 442
#define SUBROUTINE 443
#define ERROR_TOK 444
#define COMMON 445
#define PARTITION 446
#define ACTIVE 447
#define FILTER 448
#define IMAGE1D 449
#define IMAGE2D 450
#define IMAGE3D 451
#define IMAGECUBE 452
#define IMAGE1DARRAY 453
#define IMAGE2DARRAY 454
#define IIMAGE1D 455
#define IIMAGE2D 456
#define IIMAGE3D 457
#define IIMAGECUBE 458
#define IIMAGE1DARRAY 459
#define IIMAGE2DARRAY 460
#define UIMAGE1D 461
#define UIMAGE2D 462
#define UIMAGE3D 463
#define UIMAGECUBE 464
#define UIMAGE1DARRAY 465
#define UIMAGE2DARRAY 466
#define IMAGE1DSHADOW 467
#define IMAGE2DSHADOW 468
#define IMAGEBUFFER 469
#define IIMAGEBUFFER 470
#define UIMAGEBUFFER 471
#define IMAGE1DARRAYSHADOW 472
#define IMAGE2DARRAYSHADOW 473
#define ROW_MAJOR 474
#define THEN 475




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 96 "src/glsl/glsl_parser.yy"
{
   int n;
   float real;
   const char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
   ast_array_specifier *array_specifier;
   ast_fully_specified_type *fully_specified_type;
   ast_function *function;
   ast_parameter_declarator *parameter_declarator;
   ast_function_definition *function_definition;
   ast_compound_statement *compound_statement;
   ast_expression *expression;
   ast_declarator_list *declarator_list;
   ast_struct_specifier *struct_specifier;
   ast_declaration *declaration;
   ast_switch_body *switch_body;
   ast_case_label *case_label;
   ast_case_label_list *case_label_list;
   ast_case_statement *case_statement;
   ast_case_statement_list *case_statement_list;
   ast_interface_block *interface_block;

   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;
}
/* Line 1529 of yacc.c.  */
#line 526 "src/glsl/glsl_parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



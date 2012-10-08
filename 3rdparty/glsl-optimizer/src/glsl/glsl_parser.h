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
     ISAMPLER1D = 316,
     ISAMPLER2D = 317,
     ISAMPLER3D = 318,
     ISAMPLERCUBE = 319,
     ISAMPLER1DARRAY = 320,
     ISAMPLER2DARRAY = 321,
     USAMPLER1D = 322,
     USAMPLER2D = 323,
     USAMPLER3D = 324,
     USAMPLERCUBE = 325,
     USAMPLER1DARRAY = 326,
     USAMPLER2DARRAY = 327,
     SAMPLER2DRECT = 328,
     ISAMPLER2DRECT = 329,
     USAMPLER2DRECT = 330,
     SAMPLER2DRECTSHADOW = 331,
     SAMPLERBUFFER = 332,
     ISAMPLERBUFFER = 333,
     USAMPLERBUFFER = 334,
     SAMPLEREXTERNALOES = 335,
     STRUCT = 336,
     VOID_TOK = 337,
     WHILE = 338,
     IDENTIFIER = 339,
     TYPE_IDENTIFIER = 340,
     NEW_IDENTIFIER = 341,
     FLOATCONSTANT = 342,
     INTCONSTANT = 343,
     UINTCONSTANT = 344,
     BOOLCONSTANT = 345,
     FIELD_SELECTION = 346,
     LEFT_OP = 347,
     RIGHT_OP = 348,
     INC_OP = 349,
     DEC_OP = 350,
     LE_OP = 351,
     GE_OP = 352,
     EQ_OP = 353,
     NE_OP = 354,
     AND_OP = 355,
     OR_OP = 356,
     XOR_OP = 357,
     MUL_ASSIGN = 358,
     DIV_ASSIGN = 359,
     ADD_ASSIGN = 360,
     MOD_ASSIGN = 361,
     LEFT_ASSIGN = 362,
     RIGHT_ASSIGN = 363,
     AND_ASSIGN = 364,
     XOR_ASSIGN = 365,
     OR_ASSIGN = 366,
     SUB_ASSIGN = 367,
     INVARIANT = 368,
     LOWP = 369,
     MEDIUMP = 370,
     HIGHP = 371,
     SUPERP = 372,
     PRECISION = 373,
     VERSION_TOK = 374,
     EXTENSION = 375,
     LINE = 376,
     COLON = 377,
     EOL = 378,
     INTERFACE = 379,
     OUTPUT = 380,
     PRAGMA_DEBUG_ON = 381,
     PRAGMA_DEBUG_OFF = 382,
     PRAGMA_OPTIMIZE_ON = 383,
     PRAGMA_OPTIMIZE_OFF = 384,
     PRAGMA_INVARIANT_ALL = 385,
     LAYOUT_TOK = 386,
     ASM = 387,
     CLASS = 388,
     UNION = 389,
     ENUM = 390,
     TYPEDEF = 391,
     TEMPLATE = 392,
     THIS = 393,
     PACKED_TOK = 394,
     GOTO = 395,
     INLINE_TOK = 396,
     NOINLINE = 397,
     VOLATILE = 398,
     PUBLIC_TOK = 399,
     STATIC = 400,
     EXTERN = 401,
     EXTERNAL = 402,
     LONG_TOK = 403,
     SHORT_TOK = 404,
     DOUBLE_TOK = 405,
     HALF = 406,
     FIXED_TOK = 407,
     UNSIGNED = 408,
     INPUT_TOK = 409,
     OUPTUT = 410,
     HVEC2 = 411,
     HVEC3 = 412,
     HVEC4 = 413,
     DVEC2 = 414,
     DVEC3 = 415,
     DVEC4 = 416,
     FVEC2 = 417,
     FVEC3 = 418,
     FVEC4 = 419,
     SAMPLER3DRECT = 420,
     SIZEOF = 421,
     CAST = 422,
     NAMESPACE = 423,
     USING = 424,
     ERROR_TOK = 425,
     COMMON = 426,
     PARTITION = 427,
     ACTIVE = 428,
     FILTER = 429,
     IMAGE1D = 430,
     IMAGE2D = 431,
     IMAGE3D = 432,
     IMAGECUBE = 433,
     IMAGE1DARRAY = 434,
     IMAGE2DARRAY = 435,
     IIMAGE1D = 436,
     IIMAGE2D = 437,
     IIMAGE3D = 438,
     IIMAGECUBE = 439,
     IIMAGE1DARRAY = 440,
     IIMAGE2DARRAY = 441,
     UIMAGE1D = 442,
     UIMAGE2D = 443,
     UIMAGE3D = 444,
     UIMAGECUBE = 445,
     UIMAGE1DARRAY = 446,
     UIMAGE2DARRAY = 447,
     IMAGE1DSHADOW = 448,
     IMAGE2DSHADOW = 449,
     IMAGEBUFFER = 450,
     IIMAGEBUFFER = 451,
     UIMAGEBUFFER = 452,
     IMAGE1DARRAYSHADOW = 453,
     IMAGE2DARRAYSHADOW = 454,
     ROW_MAJOR = 455
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
#define ISAMPLER1D 316
#define ISAMPLER2D 317
#define ISAMPLER3D 318
#define ISAMPLERCUBE 319
#define ISAMPLER1DARRAY 320
#define ISAMPLER2DARRAY 321
#define USAMPLER1D 322
#define USAMPLER2D 323
#define USAMPLER3D 324
#define USAMPLERCUBE 325
#define USAMPLER1DARRAY 326
#define USAMPLER2DARRAY 327
#define SAMPLER2DRECT 328
#define ISAMPLER2DRECT 329
#define USAMPLER2DRECT 330
#define SAMPLER2DRECTSHADOW 331
#define SAMPLERBUFFER 332
#define ISAMPLERBUFFER 333
#define USAMPLERBUFFER 334
#define SAMPLEREXTERNALOES 335
#define STRUCT 336
#define VOID_TOK 337
#define WHILE 338
#define IDENTIFIER 339
#define TYPE_IDENTIFIER 340
#define NEW_IDENTIFIER 341
#define FLOATCONSTANT 342
#define INTCONSTANT 343
#define UINTCONSTANT 344
#define BOOLCONSTANT 345
#define FIELD_SELECTION 346
#define LEFT_OP 347
#define RIGHT_OP 348
#define INC_OP 349
#define DEC_OP 350
#define LE_OP 351
#define GE_OP 352
#define EQ_OP 353
#define NE_OP 354
#define AND_OP 355
#define OR_OP 356
#define XOR_OP 357
#define MUL_ASSIGN 358
#define DIV_ASSIGN 359
#define ADD_ASSIGN 360
#define MOD_ASSIGN 361
#define LEFT_ASSIGN 362
#define RIGHT_ASSIGN 363
#define AND_ASSIGN 364
#define XOR_ASSIGN 365
#define OR_ASSIGN 366
#define SUB_ASSIGN 367
#define INVARIANT 368
#define LOWP 369
#define MEDIUMP 370
#define HIGHP 371
#define SUPERP 372
#define PRECISION 373
#define VERSION_TOK 374
#define EXTENSION 375
#define LINE 376
#define COLON 377
#define EOL 378
#define INTERFACE 379
#define OUTPUT 380
#define PRAGMA_DEBUG_ON 381
#define PRAGMA_DEBUG_OFF 382
#define PRAGMA_OPTIMIZE_ON 383
#define PRAGMA_OPTIMIZE_OFF 384
#define PRAGMA_INVARIANT_ALL 385
#define LAYOUT_TOK 386
#define ASM 387
#define CLASS 388
#define UNION 389
#define ENUM 390
#define TYPEDEF 391
#define TEMPLATE 392
#define THIS 393
#define PACKED_TOK 394
#define GOTO 395
#define INLINE_TOK 396
#define NOINLINE 397
#define VOLATILE 398
#define PUBLIC_TOK 399
#define STATIC 400
#define EXTERN 401
#define EXTERNAL 402
#define LONG_TOK 403
#define SHORT_TOK 404
#define DOUBLE_TOK 405
#define HALF 406
#define FIXED_TOK 407
#define UNSIGNED 408
#define INPUT_TOK 409
#define OUPTUT 410
#define HVEC2 411
#define HVEC3 412
#define HVEC4 413
#define DVEC2 414
#define DVEC3 415
#define DVEC4 416
#define FVEC2 417
#define FVEC3 418
#define FVEC4 419
#define SAMPLER3DRECT 420
#define SIZEOF 421
#define CAST 422
#define NAMESPACE 423
#define USING 424
#define ERROR_TOK 425
#define COMMON 426
#define PARTITION 427
#define ACTIVE 428
#define FILTER 429
#define IMAGE1D 430
#define IMAGE2D 431
#define IMAGE3D 432
#define IMAGECUBE 433
#define IMAGE1DARRAY 434
#define IMAGE2DARRAY 435
#define IIMAGE1D 436
#define IIMAGE2D 437
#define IIMAGE3D 438
#define IIMAGECUBE 439
#define IIMAGE1DARRAY 440
#define IIMAGE2DARRAY 441
#define UIMAGE1D 442
#define UIMAGE2D 443
#define UIMAGE3D 444
#define UIMAGECUBE 445
#define UIMAGE1DARRAY 446
#define UIMAGE2DARRAY 447
#define IMAGE1DSHADOW 448
#define IMAGE2DSHADOW 449
#define IMAGEBUFFER 450
#define IIMAGEBUFFER 451
#define UIMAGEBUFFER 452
#define IMAGE1DARRAYSHADOW 453
#define IMAGE2DARRAYSHADOW 454
#define ROW_MAJOR 455




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 59 "src/glsl/glsl_parser.yy"
{
   int n;
   float real;
   const char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
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
#line 484 "src/glsl/glsl_parser.h"
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



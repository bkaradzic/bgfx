/******************************************************************************
Copyright (c) 1999 Daniel Stenberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include "cppdef.h"
#include "cpp.h"

INLINE FILE_LOCAL ReturnCode fpp_evallex(struct Global *, int, int *);
INLINE FILE_LOCAL ReturnCode fpp_dosizeof(struct Global *, int *);
INLINE FILE_LOCAL int fpp_bittest(int);
INLINE FILE_LOCAL int fpp_evalnum(struct Global *, int);
INLINE FILE_LOCAL int fpp_evalchar(struct Global *, int);
INLINE FILE_LOCAL int *fpp_evaleval(struct Global *, int *, int, int);

/*
 * Evaluate an #if expression.
 */

static char *opname[] = {		/* For debug and error messages */
  "end of expression", "val", "id",
  "+",   "-",  "*",  "/",  "%",
  "<<", ">>",  "&",  "|",  "^",
  "==", "!=",  "<", "<=", ">=",  ">",
  "&&", "||",  "?",  ":",  ",",
  "unary +", "unary -", "~", "!",  "(",  ")", "(none)",
};

/*
 * opdope[] has the operator precedence:
 *     Bits
 *	  7	Unused (so the value is always positive)
 *	6-2	Precedence (000x .. 017x)
 *	1-0	Binary op. flags:
 *	    01	The binop flag should be set/cleared when this op is seen.
 *	    10	The new value of the binop flag.
 * Note:  Expected, New binop
 * constant	0	1	Binop, end, or ) should follow constants
 * End of line	1	0	End may not be preceeded by an operator
 * binary	1	0	Binary op follows a value, value follows.
 * unary	0	0	Unary op doesn't follow a value, value follows
 *   (          0       0       Doesn't follow value, value or unop follows
 *   )		1	1	Follows value.	Op follows.
 */

static char opdope[OP_MAX] = {
  0001, 				/* End of expression		*/
  0002, 				/* Digit			*/
  0000, 				/* Letter (identifier)          */
  0141, 0141, 0151, 0151, 0151, 	/* ADD, SUB, MUL, DIV, MOD	*/
  0131, 0131, 0101, 0071, 0071, 	/* ASL, ASR, AND,  OR, XOR	*/
  0111, 0111, 0121, 0121, 0121, 0121,	/*  EQ,  NE,  LT,  LE,	GE,  GT */
  0061, 0051, 0041, 0041, 0031, 	/* ANA, ORO, QUE, COL, CMA	*/
  /*
   * Unary op's follow
   */
  0160, 0160, 0160, 0160,		/* NEG, PLU, COM, NOT		*/
  0170, 0013, 0023,			/* LPA, RPA, END		*/
};
/*
 * OP_QUE and OP_RPA have alternate precedences:
 */
#define OP_RPA_PREC	0013
#define OP_QUE_PREC	0034

/*
 * S_ANDOR and S_QUEST signal "short-circuit" boolean evaluation, so that
 *	#if FOO != 0 && 10 / FOO ...
 * doesn't generate an error message.  They are stored in optab.skip.
 */
#define S_ANDOR 	2
#define S_QUEST 	1

typedef struct optab {
  char	op;			/* Operator			*/
  char	prec;			/* Its precedence		*/
  char	skip;			/* Short-circuit: FPP_TRUE to skip	*/
} OPTAB;
     
#ifdef	nomacargs
     FILE_LOCAL int
       isbinary(op)
     int op;
{
  return (op >= FIRST_BINOP && op <= LAST_BINOP);
}

FILE_LOCAL int
  isunary(op)
int op;
{
  return (op >= FIRST_UNOP && op <= LAST_UNOP);
}
#else
#define isbinary(op)    (op >= FIRST_BINOP && op <= LAST_BINOP)
#define isunary(op)     (op >= FIRST_UNOP  && op <= LAST_UNOP)
#endif

/*
 * The following definitions are used to specify basic variable sizes.
 */

#if OK_SIZEOF

#ifndef S_CHAR
#define S_CHAR		(sizeof (char))
#endif
#ifndef S_SINT
#ifdef manx		/* Aztec/Manx C does not like "short int" */
#define S_SINT		(sizeof (short))
#else
#define S_SINT		(sizeof (short int))
#endif
#endif
#ifndef S_INT
#define S_INT		(sizeof (int))
#endif
#ifndef S_LINT
#define S_LINT		(sizeof (long int))
#endif
#ifndef S_FLOAT
#define S_FLOAT 	(sizeof (float))
#endif
#ifndef S_DOUBLE
#define S_DOUBLE	(sizeof (double))
#endif
#ifndef S_PCHAR
#define S_PCHAR 	(sizeof (char *))
#endif
#ifndef S_PSINT
#ifdef manx		/* Aztec/Manx C does not like "short int" */
#define S_PSINT 	(sizeof (short *))
#else
#define S_PSINT 	(sizeof (short int *))
#endif
#endif
#ifndef S_PINT
#define S_PINT		(sizeof (int *))
#endif
#ifndef S_PLINT
#define S_PLINT 	(sizeof (long int *))
#endif
#ifndef S_PFLOAT
#define S_PFLOAT	(sizeof (float *))
#endif
#ifndef S_PDOUBLE
#define S_PDOUBLE	(sizeof (double *))
#endif
#ifndef S_PFPTR
#define S_PFPTR 	(sizeof (int (*)()))
#endif


typedef struct types {
  short	type;			/* This is the bit if		*/
  char	*name;			/* this is the token word	*/
} TYPES;

static TYPES basic_types[] = {
  { T_CHAR,	"char",         },
  { T_INT,	"int",          },
  { T_FLOAT,	"float",        },
  { T_DOUBLE,	"double",       },
  { T_SHORT,	"short",        },
  { T_LONG,	"long",         },
  { T_SIGNED,	"signed",       },
  { T_UNSIGNED,	"unsigned",     },
  { 0,		NULL,		},	/* Signal end		*/
};

/*
 * Test_table[] is used to test for illegal combinations.
 */
static short test_table[] = {
  T_FLOAT | T_DOUBLE | T_LONG | T_SHORT,
  T_FLOAT | T_DOUBLE | T_CHAR | T_INT,
  T_FLOAT | T_DOUBLE | T_SIGNED | T_UNSIGNED,
  T_LONG  | T_SHORT  | T_CHAR,
  0						/* end marker	*/
  };

/*
 * The order of this table is important -- it is also referenced by
 * the command line processor to allow run-time overriding of the
 * built-in size values.  The order must not be changed:
 *	char, short, int, long, float, double (func pointer)
 */
SIZES size_table[] = {
  { T_CHAR,	S_CHAR, 	S_PCHAR 	},	/* char 	*/
  { T_SHORT,	S_SINT, 	S_PSINT 	},	/* short int	*/
  { T_INT,	S_INT,		S_PINT		},	/* int		*/
  { T_LONG,	S_LINT, 	S_PLINT 	},	/* long 	*/
  { T_FLOAT,	S_FLOAT,	S_PFLOAT	},	/* float	*/
  { T_DOUBLE,	S_DOUBLE,	S_PDOUBLE	},	/* double	*/
  { T_FPTR,	0,		S_PFPTR 	},	/* int (*())    */
  { 0,		0,		0		},	/* End of table */
};

#endif /* OK_SIZEOF */

ReturnCode fpp_eval(struct Global *global, int *eval)
{
  /*
   * Evaluate an expression.  Straight-forward operator precedence.
   * This is called from fpp_control() on encountering an #if statement.
   * It calls the following routines:
   * fpp_evallex	Lexical analyser -- returns the type and value of
   *		the next input token.
   * fpp_evaleval	Evaluate the current operator, given the values on
   *		the value stack.  Returns a pointer to the (new)
   *		value stack.
   * For compatiblity with older cpp's, this return returns 1 (FPP_TRUE)
   * if a syntax error is detected.
   */
  int op;		/* Current operator		*/
  int *valp;		/* -> value vector		*/
  OPTAB *opp;		/* Operator stack		*/
  int prec;		/* Op precedence		*/
  int binop;		/* Set if binary op. needed	*/
  int op1;		/* Operand from stack		*/
  int skip;		/* For short-circuit testing	*/
  int value[NEXP];	/* Value stack			*/
  OPTAB opstack[NEXP];	/* Operand stack		*/
  ReturnCode ret;
  char again=FPP_TRUE;
  
  valp = value;
  opp = opstack;
  opp->op = OP_END;		/* Mark bottom of stack 	*/
  opp->prec = opdope[OP_END];	/* And its precedence		*/
  opp->skip = 0;		/* Not skipping now		*/
  binop = 0;

  while(again) {
    ret=fpp_evallex(global, opp->skip, &op);
    if(ret)
      return(ret);
    if (op == OP_SUB && binop == 0)
      op = OP_NEG;			/* Unary minus		*/
    else if (op == OP_ADD && binop == 0)
      op = OP_PLU;			/* Unary plus		*/
    else if (op == OP_FAIL) {
      *eval=1;                    	/* Error in evallex     */
      return(FPP_OK);
    }
    if (op == DIG) {                      /* Value?               */
      if (binop != 0) {
	fpp_cerror(global, ERROR_MISPLACED_CONSTANT);
	*eval=1;
	return(FPP_OK);
      } else if (valp >= &value[NEXP-1]) {
	fpp_cerror(global, ERROR_IF_OVERFLOW);
	*eval=1;
	return(FPP_OK);
      } else {
	*valp++ = global->evalue;
	binop = 1;
      }
      again=FPP_TRUE;
      continue;
    } else if (op > OP_END) {
      fpp_cerror(global, ERROR_ILLEGAL_IF_LINE);
      *eval=1;
      return(FPP_OK);
    }
    prec = opdope[op];
    if (binop != (prec & 1)) {
      fpp_cerror(global, ERROR_OPERATOR, opname[op]);
      *eval=1;
      return(FPP_OK);
    }
    binop = (prec & 2) >> 1;
    do {
      if (prec > opp->prec) {
	if (op == OP_LPA)
	  prec = OP_RPA_PREC;
	else if (op == OP_QUE)
	  prec = OP_QUE_PREC;
	op1 = opp->skip;		/* Save skip for test	*/
	/*
	 * Push operator onto op. stack.
	 */
	opp++;
	if (opp >= &opstack[NEXP]) {
	  fpp_cerror(global, ERROR_EXPR_OVERFLOW, opname[op]);
	  *eval=1;
	  return(FPP_OK);
	}
	opp->op = op;
	opp->prec = prec;
	skip = (valp[-1] != 0);         /* Short-circuit tester */
	/*
	 * Do the short-circuit stuff here.  Short-circuiting
	 * stops automagically when operators are evaluated.
	 */
	if ((op == OP_ANA && !skip)
	    || (op == OP_ORO && skip))
	  opp->skip = S_ANDOR;	/* And/or skip starts	*/
	else if (op == OP_QUE)          /* Start of ?: operator */
	  opp->skip = (op1 & S_ANDOR) | ((!skip) ? S_QUEST : 0);
	else if (op == OP_COL) {        /* : inverts S_QUEST    */
	  opp->skip = (op1 & S_ANDOR)
	    | (((op1 & S_QUEST) != 0) ? 0 : S_QUEST);
	}
	else {				/* Other ops leave	*/
	  opp->skip = op1;		/*  skipping unchanged. */
	}
	again=FPP_TRUE;
	continue;
      }
      /*
       * Pop operator from op. stack and evaluate it.
       * End of stack and '(' are specials.
       */
      skip = opp->skip;			/* Remember skip value	*/
      switch ((op1 = opp->op)) {          /* Look at stacked op   */
      case OP_END:			/* Stack end marker	*/
	if (op == OP_EOE) {
	  *eval=valp[-1];     		/* Finished ok.         */
	  return(FPP_OK);
	}
	/* Read another op.	*/
	again=FPP_TRUE;
	continue;
      case OP_LPA:			/* ( on stack           */
	if (op != OP_RPA) {             /* Matches ) on input   */
	  fpp_cerror(global, ERROR_UNBALANCED_PARENS, opname[op]);
	  *eval=1;
	  return(FPP_OK);
	}
	opp--;				/* Unstack it		*/
	/* -- Fall through 	*/
      case OP_QUE:
	/* Evaluate true expr.	*/
	again=FPP_TRUE;
	continue;
      case OP_COL:			/* : on stack.		*/
	opp--;				/* Unstack :		*/
	if (opp->op != OP_QUE) {        /* Matches ? on stack?  */
	  fpp_cerror(global, ERROR_MISPLACED, opname[(unsigned)opp->op]);
	  *eval=1;
	  return(FPP_OK);
	}
	/*
	 * Evaluate op1.
	 */
      default:				/* Others:		*/
	opp--;				/* Unstack the operator */
	valp = fpp_evaleval(global, valp, op1, skip);
	again=FPP_FALSE;
      }					/* op1 switch end	*/
    } while (!again);			/* Stack unwind loop	*/
  }
  return(FPP_OK);
}

INLINE FILE_LOCAL
ReturnCode fpp_evallex(struct Global *global,
		   int skip,	/* FPP_TRUE if short-circuit evaluation */
		   int *op)
{
  /*
   * Set *op to next fpp_eval operator or value. Called from fpp_eval(). It
   * calls a special-purpose routines for 'char' strings and
   * numeric values:
   * fpp_evalchar	called to evaluate 'x'
   * fpp_evalnum	called to evaluate numbers.
   */

  int c, c1, t;
  ReturnCode ret;
  char loop;
  
  do { /* while(loop); */
  /* again: */
    loop=FPP_FALSE;
    do {					/* Collect the token	*/
      c = fpp_skipws(global);
      if((ret=fpp_macroid(global, &c)))
      return(ret);
      if (c == EOF_CHAR || c == '\n') {
	fpp_unget(global);
	*op=OP_EOE;           /* End of expression    */
	return(FPP_OK);
      }
    } while ((t = type[c]) == LET && fpp_catenate(global, 0, &ret) && !ret);
    if(ret)
      /* If the loop was broken because of a fatal error! */
      return(ret);
    if (t == INV) {                         /* Total nonsense       */
      if (!skip) {
	if (isascii(c) && isprint(c))
	  fpp_cerror(global, ERROR_ILLEGAL_CHARACTER, c);
	else
	  fpp_cerror(global, ERROR_ILLEGAL_CHARACTER2, c);
      }
      return(FPP_ILLEGAL_CHARACTER);
    } else if (t == QUO) {                  /* ' or "               */
      if (c == '\'') {                    /* Character constant   */
	global->evalue = fpp_evalchar(global, skip);  /* Somewhat messy       */
	*op=DIG;                          /* Return a value       */
	return(FPP_OK);
      }
      fpp_cerror(global, ERROR_STRING_IN_IF);
      return(FPP_CANT_USE_STRING_IN_IF);
    } else if (t == LET) {                  /* ID must be a macro   */
      if (streq(global->tokenbuf, "defined")) {   /* Or defined name      */
	c1 = c = fpp_skipws(global);
	if (c == '(')                     /* Allow defined(name)  */
	  c = fpp_skipws(global);
	if (type[c] == LET) {
	  global->evalue = (fpp_lookid(global, c) != NULL);
	  if (c1 != '('                   /* Need to balance      */
	      || fpp_skipws(global) == ')') { /* Did we balance?      */
	    *op=DIG;
	    return(FPP_OK);               /* Parsed ok            */
	  }
	}
	fpp_cerror(global, ERROR_DEFINED_SYNTAX);
	return(FPP_BAD_IF_DEFINED_SYNTAX);
      }
#if OK_SIZEOF
else if (streq(global->tokenbuf, "sizeof")) { /* New sizeof hackery   */
  ret=fpp_dosizeof(global, op);             /* Gets own routine     */
  return(ret);
}
#endif
      global->evalue = 0;
      *op=DIG;
      return(FPP_OK);
    }
    else if (t == DIG) {                  /* Numbers are harder   */
      global->evalue = fpp_evalnum(global, c);
    }
    else if (strchr("!=<>&|\\", c) != NULL) {
      /*
       * Process a possible multi-byte lexeme.
       */
      c1 = fpp_cget(global);                        /* Peek at next char    */
      switch (c) {
      case '!':
	if (c1 == '=') {
	  *op=OP_NE;
	  return(FPP_OK);
	}
	break;
	
      case '=':
	if (c1 != '=') {                  /* Can't say a=b in #if */
	  fpp_unget(global);
	  fpp_cerror(global, ERROR_ILLEGAL_ASSIGN);
	  return (FPP_IF_ERROR);
	}
	*op=OP_EQ;
	return(FPP_OK);
	
      case '>':
      case '<':
	if (c1 == c) {
	  *op= ((c == '<') ? OP_ASL : OP_ASR);
	  return(FPP_OK);
	} else if (c1 == '=') {
	  *op= ((c == '<') ? OP_LE  : OP_GE);
	  return(FPP_OK);
	}
	break;
	
      case '|':
      case '&':
	if (c1 == c) {
	  *op= ((c == '|') ? OP_ORO : OP_ANA);
	  return(FPP_OK);
	}
	break;
      
      case '\\':
	if (c1 == '\n') {                  /* Multi-line if        */
	  loop=FPP_TRUE;
	  break;
	}
	fpp_cerror(global, ERROR_ILLEGAL_BACKSLASH);
	return(FPP_IF_ERROR);
      }
      if(!loop)
	fpp_unget(global);
    }
  } while(loop);
  *op=t;
  return(FPP_OK);
}

#if OK_SIZEOF

INLINE FILE_LOCAL
ReturnCode fpp_dosizeof(struct Global *global, int *result)
{
  /*
   * Process the sizeof (basic type) operation in an #if string.
   * Sets evalue to the size and returns
   *	DIG		success
   *	OP_FAIL 	bad parse or something.
   */
  int c;
  TYPES *tp;
  SIZES *sizp;
  short *testp;
  short typecode;
  ReturnCode ret;
  
  if ((c = fpp_skipws(global)) != '(') {
    fpp_unget(global);
    fpp_cerror(global, ERROR_SIZEOF_SYNTAX);
    return(FPP_SIZEOF_ERROR);
  }
  /*
   * Scan off the tokens.
   */
  typecode = 0;
  while ((c = fpp_skipws(global))) {
    if((ret=fpp_macroid(global, &c)))
      return(ret);
    /* (I) return on fail! */
    if (c  == EOF_CHAR || c == '\n') {
      /* End of line is a bug */
      fpp_unget(global);
      fpp_cerror(global, ERROR_SIZEOF_SYNTAX);
      return(FPP_SIZEOF_ERROR);
    } else if (c == '(') {                /* thing (*)() func ptr */
      if (fpp_skipws(global) == '*'
	  && fpp_skipws(global) == ')') {         /* We found (*)         */
	if (fpp_skipws(global) != '(')            /* Let () be optional   */
	  fpp_unget(global);
	else if (fpp_skipws(global) != ')') {
	  fpp_unget(global);
	  fpp_cerror(global, ERROR_SIZEOF_SYNTAX);
	  return(FPP_SIZEOF_ERROR);
	}
	typecode |= T_FPTR; 		/* Function pointer	*/
      } else {				/* Junk is a bug	*/
	fpp_unget(global);
	fpp_cerror(global, ERROR_SIZEOF_SYNTAX);
	return(FPP_SIZEOF_ERROR);
      }
    }
    else if (type[c] != LET)            /* Exit if not a type   */
      break;
    else if (!fpp_catenate(global, 0, &ret) && !ret) { /* Maybe combine tokens */
      /*
       * Look for this unexpandable token in basic_types.
       * The code accepts "int long" as well as "long int"
       * which is a minor bug as bugs go (and one shared with
       * a lot of C compilers).
       */
      for (tp = basic_types; tp->name != NULLST; tp++) {
	if (streq(global->tokenbuf, tp->name))
	  break;
      }
      if (tp->name == NULLST) {
	fpp_cerror(global, ERROR_SIZEOF_UNKNOWN, global->tokenbuf);
	return(FPP_SIZEOF_ERROR);
      }
      typecode |= tp->type;		/* Or in the type bit	*/
    } else if(ret)
      return(ret);
  }
  /*
   * We are at the end of the type scan.	Chew off '*' if necessary.
   */
  if (c == '*') {
    typecode |= T_PTR;
    c = fpp_skipws(global);
  }
  if (c == ')') {                         /* Last syntax check    */
    for (testp = test_table; *testp != 0; testp++) {
      if (!fpp_bittest(typecode & *testp)) {
	fpp_cerror(global, ERROR_SIZEOF_ILLEGAL_TYPE);
	return(FPP_SIZEOF_ERROR);
      }
    }
    /*
     * We assume that all function pointers are the same size:
     *		sizeof (int (*)()) == sizeof (float (*)())
     * We assume that signed and unsigned don't change the size:
     *		sizeof (signed int) == (sizeof unsigned int)
     */
    if ((typecode & T_FPTR) != 0)       /* Function pointer     */
      typecode = T_FPTR | T_PTR;
    else {				/* Var or var * datum	*/
      typecode &= ~(T_SIGNED | T_UNSIGNED);
      if ((typecode & (T_SHORT | T_LONG)) != 0)
	typecode &= ~T_INT;
    }
    if ((typecode & ~T_PTR) == 0) {
      fpp_cerror(global, ERROR_SIZEOF_NO_TYPE);
      return(FPP_SIZEOF_ERROR);
    }
    /*
     * Exactly one bit (and possibly T_PTR) may be set.
     */
    for (sizp = size_table; sizp->bits != 0; sizp++) {
      if ((typecode & ~T_PTR) == sizp->bits) {
	global->evalue = ((typecode & T_PTR) != 0)
	  ? sizp->psize : sizp->size;
	*result=DIG;
	return(FPP_OK);
      }
    }					/* We shouldn't fail    */
    fpp_cerror(global, ERROR_SIZEOF_BUG, typecode);
    return(FPP_SIZEOF_ERROR);
  }
  fpp_unget(global);
  fpp_cerror(global, ERROR_SIZEOF_SYNTAX);
  return(FPP_SIZEOF_ERROR);
}

INLINE FILE_LOCAL
int fpp_bittest(int value)
{
  /*
   * FPP_TRUE if value is zero or exactly one bit is set in value.
   */

#if (4096 & ~(-4096)) == 0
  return ((value & ~(-value)) == 0);
#else
  /*
   * Do it the hard way (for non 2's complement machines)
   */
  return (value == 0 || value ^ (value - 1) == (value * 2 - 1));
#endif
}

#endif /* OK_SIZEOF */

INLINE FILE_LOCAL
int fpp_evalnum(struct Global *global, int c)
{
  /*
   * Expand number for #if lexical analysis.  Note: fpp_evalnum recognizes
   * the unsigned suffix, but only returns a signed int value.
   */

  int value;
  int base;
  int c1;
  
  if (c != '0')
    base = 10;
  else if ((c = fpp_cget(global)) == 'x' || c == 'X') {
    base = 16;
    c = fpp_cget(global);
  }
  else base = 8;
  value = 0;
  for (;;) {
    c1 = c;
    if (isascii(c) && isupper(c1))
      c1 = fpp_tolower(c1);
    if (c1 >= 'a')
      c1 -= ('a' - 10);
    else c1 -= '0';
    if (c1 < 0 || c1 >= base)
      break;
    value *= base;
    value += c1;
    c = fpp_cget(global);
  }
  if (c == 'u' || c == 'U')       /* Unsigned nonsense            */
    c = fpp_cget(global);
  fpp_unget(global);
  return (value);
}

INLINE FILE_LOCAL
int fpp_evalchar(struct Global *global,
	     int skip)		/* FPP_TRUE if short-circuit evaluation	*/
     /*
      * Get a character constant
      */
{
  int c;
  int value;
  int count;
  
  global->instring = FPP_TRUE;
  if ((c = fpp_cget(global)) == '\\') {
    switch ((c = fpp_cget(global))) {
    case 'a':                           /* New in Standard      */
#if ('a' == '\a' || '\a' == ALERT)
      value = ALERT;			/* Use predefined value */
#else
      value = '\a';                   /* Use compiler's value */
#endif
      break;
      
    case 'b':
      value = '\b';
      break;
      
    case 'f':
      value = '\f';
      break;
      
    case 'n':
      value = '\n';
      break;
      
    case 'r':
      value = '\r';
      break;
      
    case 't':
      value = '\t';
      break;
      
    case 'v':                           /* New in Standard      */
#if ('v' == '\v' || '\v' == VT)
      value = VT;			/* Use predefined value */
#else
      value = '\v';                   /* Use compiler's value */
#endif
      break;
      
    case 'x':                           /* '\xFF'               */
      count = 3;
      value = 0;
      while ((((c = fpp_get(global)) >= '0' && c <= '9')
	      || (c >= 'a' && c <= 'f')
	      || (c >= 'A' && c <= 'F'))
	     && (--count >= 0)) {
	value *= 16;
	value += (c <= '9') ? (c - '0') : ((c & 0xF) + 9);
      }
      fpp_unget(global);
      break;
      
    default:
      if (c >= '0' && c <= '7') {
	count = 3;
	value = 0;
	while (c >= '0' && c <= '7' && --count >= 0) {
	  value *= 8;
	  value += (c - '0');
	  c = fpp_get(global);
	}
	fpp_unget(global);
      } else
	value = c;
      break;
    }
  } else if (c == '\'')
    value = 0;
  else value = c;
  /*
   * We warn on multi-byte constants and try to hack
   * (big|little)endian machines.
   */
#if BIG_ENDIAN
  count = 0;
#endif
  while ((c = fpp_get(global)) != '\'' && c != EOF_CHAR && c != '\n') {
    if (!skip)
      fpp_cwarn(global, WARN_MULTIBYTE_NOT_PORTABLE, c);
#if BIG_ENDIAN
    count += BITS_CHAR;
    value += (c << count);
#else
    value <<= BITS_CHAR;
    value += c;
#endif
  }
  global->instring = FPP_FALSE;
  return (value);
}

INLINE FILE_LOCAL
int *fpp_evaleval(struct Global *global,
	      int *valp,
	      int op,
	      int skip)		/* FPP_TRUE if short-circuit evaluation	*/
{
  /*
   * Apply the argument operator to the data on the value stack.
   * One or two values are popped from the value stack and the result
   * is pushed onto the value stack.
   *
   * OP_COL is a special case.
   *
   * fpp_evaleval() returns the new pointer to the top of the value stack.
   */
  int v1, v2 = 0;
  
  if (isbinary(op))
    v2 = *--valp;
  v1 = *--valp;
  switch (op) {
  case OP_EOE:
    break;
  case OP_ADD:
    v1 += v2;
    break;
  case OP_SUB:
    v1 -= v2;
    break;
  case OP_MUL:
    v1 *= v2;
    break;
  case OP_DIV:
  case OP_MOD:
    if (v2 == 0) {
      if (!skip) {
	fpp_cwarn(global, WARN_DIVISION_BY_ZERO,
	      (op == OP_DIV) ? "divide" : "mod");
      }
      v1 = 0;
    }
    else if (op == OP_DIV)
      v1 /= v2;
    else
      v1 %= v2;
    break;
  case OP_ASL:
    v1 <<= v2;
    break;
  case OP_ASR:
    v1 >>= v2;
    break;
  case OP_AND:
    v1 &= v2;
    break;
  case OP_OR:
    v1 |= v2;
    break;
  case OP_XOR:
    v1 ^= v2;
    break;
  case OP_EQ:
    v1 = (v1 == v2);
    break;
  case OP_NE:
    v1 = (v1 != v2);
    break;
  case OP_LT:
    v1 = (v1 < v2);
    break;
  case OP_LE:
    v1 = (v1 <= v2);
    break;
  case OP_GE:
    v1 = (v1 >= v2);
    break;
  case OP_GT:
    v1 = (v1 > v2);
    break;
  case OP_ANA:
    v1 = (v1 && v2);
    break;
  case OP_ORO:
    v1 = (v1 || v2);
    break;
  case OP_COL:
    /*
     * v1 has the "true" value, v2 the "false" value.
     * The top of the value stack has the test.
     */
    v1 = (*--valp) ? v1 : v2;
    break;
  case OP_NEG:
    v1 = (-v1);
    break;
  case OP_PLU:
    break;
  case OP_COM:
    v1 = ~v1;
    break;
  case OP_NOT:
    v1 = !v1;
    break;
  default:
    fpp_cerror(global, ERROR_IF_OPERAND, op);
    v1 = 0;
  }
  *valp++ = v1;
  return (valp);
}

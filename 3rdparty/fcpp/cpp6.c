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

INLINE FILE_LOCAL void fpp_outadefine(struct Global *, DEFBUF *);
INLINE FILE_LOCAL void fpp_domsg(struct Global *, ErrorCode, va_list);

/*
 * fpp_skipnl()     skips over input text to the end of the line.
 * fpp_skipws()     skips over "whitespace" (spaces or tabs), but
 *              not skip over the end of the line.  It skips over
 *              TOK_SEP, however (though that shouldn't happen).
 * fpp_scanid()     reads the next token (C identifier) into tokenbuf.
 *              The caller has already read the first character of
 *              the identifier.  Unlike fpp_macroid(), the token is
 *              never expanded.
 * fpp_macroid()    reads the next token (C identifier) into tokenbuf.
 *              If it is a #defined macro, it is expanded, and
 *              fpp_macroid() returns FPP_TRUE, otherwise, FPP_FALSE.
 * fpp_catenate()   Does the dirty work of token concatenation, FPP_TRUE if it did.
 * fpp_scanstring() Reads a string from the input stream, calling
 *              a user-supplied function for each character.
 *              This function may be fpp_output() to write the
 *              string to the output file, or fpp_save() to fpp_save
 *              the string in the work buffer.
 * fpp_scannumber() Reads a C numeric constant from the input stream,
 *              calling the user-supplied function for each
 *              character.  (fpp_output() or fpp_save() as noted above.)
 * fpp_save()       Save one character in the work[] buffer.
 * fpp_savestring() Saves a string in malloc() memory.
 * fpp_getfile()    Initialize a new FILEINFO structure, called when
 *              #include opens a new file, or a macro is to be
 *              expanded.
 * fpp_Getmem()     Get a specified number of bytes from malloc memory.
 * fpp_output()     Write one character to stdout (calling fpp_Putchar) --
 *              implemented as a function so its address may be
 *              passed to fpp_scanstring() and fpp_scannumber().
 * fpp_lookid()     Scans the next token (identifier) from the input
 *              stream.  Looks for it in the #defined symbol table.
 *              Returns a pointer to the definition, if found, or NULL
 *              if not present.  The identifier is stored in tokenbuf.
 * fpp_defendel()   Define enter/delete subroutine.  Updates the
 *              symbol table.
 * fpp_get()        Read the next byte from the current input stream,
 *              handling end of (macro/file) input and embedded
 *              comments appropriately.  Note that the global
 *              instring is -- essentially -- a parameter to fpp_get().
 * fpp_cget()       Like fpp_get(), but skip over TOK_SEP.
 * fpp_unget()      Push last gotten character back on the input stream.
 * fpp_cerror()     This routine format an print messages to the user.
 */

/*
 * This table must be rewritten for a non-Ascii machine.
 *
 * Note that several "non-visible" characters have special meaning:
 * Hex 1C QUOTE_PARM --a flag for # stringifying
 * Hex 1D DEF_MAGIC -- a flag to prevent #define recursion.
 * Hex 1E TOK_SEP   -- a delimiter for ## token concatenation
 * Hex 1F COM_SEP   -- a zero-width whitespace for comment concatenation
 */

#ifndef OS9
#if (TOK_SEP != 0x1E || COM_SEP != 0x1F || DEF_MAGIC != 0x1D)
#error "<< error type table isn't correct >>"
#endif
#endif

#if OK_DOLLAR
#define DOL     LET
#else
#define DOL     000
#endif

char type[256] = {              /* Character type codes    Hex          */
  END,   000,    000,   000,   000,   000,   000,   000, /* 00          */
  000,   SPA,    000,   000,   000,   000,   000,   000, /* 08          */
  000,   000,    000,   000,   000,   000,   000,   000, /* 10          */
  000,   000,    000,   000,   000,   LET,   000,   SPA, /* 18          */
  SPA,   OP_NOT, QUO,   000,   DOL,   OP_MOD,OP_AND,QUO, /* 20  !"#$%&' */
  OP_LPA,OP_RPA,OP_MUL,OP_ADD, 000,OP_SUB,   DOT,OP_DIV, /* 28 ()*+,-./ */
  DIG,   DIG,    DIG,   DIG,   DIG,   DIG,   DIG,   DIG, /* 30 01234567 */
  DIG,   DIG,OP_COL,    000, OP_LT, OP_EQ, OP_GT,OP_QUE, /* 38 89:;<=>? */
  000,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 40 @ABCDEFG */
  LET,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 48 HIJKLMNO */
  LET,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 50 PQRSTUVW */
  LET,   LET,    LET,   000,   BSH,   000,OP_XOR,   LET, /* 58 XYZ[\]^_ */
  000,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 60 `abcdefg */
  LET,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 68 hijklmno */
  LET,   LET,    LET,   LET,   LET,   LET,   LET,   LET, /* 70 pqrstuvw */
  LET,   LET,    LET,   000, OP_OR,   000,OP_NOT,   000, /* 78 xyz{|}~  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
  000,   000,    000,   000,   000,   000,   000,   000, /*   80 .. FF  */
};

void fpp_skipnl(struct Global *global)
{
  /*
   * Skip to the end of the current input line.
   */
  int c;

  do {                          /* Skip to newline      */
    c = fpp_get(global);
  } while (c != '\n' && c != EOF_CHAR);
  return;
}

int fpp_skipws(struct Global *global)
{
  /*
   * Skip over whitespace
   */
  int c;

  do {                          /* Skip whitespace      */
    c = fpp_get(global);
#if COMMENT_INVISIBLE
  } while (type[c] == SPA || c == COM_SEP);
#else
} while (type[c] == SPA);
#endif
 return(c);
}

void fpp_scanid(struct Global *global,
  int c)                                /* First char of id     */
{
  /*
   * Get the next token (an id) into the token buffer.
   * Note: this code is duplicated in fpp_lookid().
   * Change one, change both.
   */

  int ct;

  if (c == DEF_MAGIC)                     /* Eat the magic token  */
    c = fpp_get(global);                      /* undefiner.           */
  ct = 0;
  do
    {
      if (ct == global->tokenbsize)
        global->tokenbuf = realloc(global->tokenbuf, 1 +
                                   (global->tokenbsize *= 2));
      global->tokenbuf[ct++] = c;
      c = fpp_get(global);
    }
  while (type[c] == LET || type[c] == DIG);
  fpp_unget(global);
  global->tokenbuf[ct] = EOS;
}

ReturnCode fpp_macroid(struct Global *global, int *c)
{
  /*
   * If c is a letter, scan the id.  if it's #defined, expand it and scan
   * the next character and try again.
   *
   * Else, return the character. If type[c] is a LET, the token is in tokenbuf.
   */
  DEFBUF *dp;
  ReturnCode ret=FPP_OK;

  if (global->infile != NULL && global->infile->fp != NULL)
    global->recursion = 0;
  while (type[*c] == LET && (dp = fpp_lookid(global, *c)) != NULL) {
    if((ret=fpp_expand(global, dp)))
      return(ret);
    *c = fpp_get(global);
  }
  return(FPP_OK);
}

int fpp_catenate(struct Global *global, int lhs_number, ReturnCode *ret)
{
  /*
   * A token was just read (via fpp_macroid).
   * If the next character is TOK_SEP, concatenate the next token
   * return FPP_TRUE -- which should recall fpp_macroid after refreshing
   * fpp_macroid's argument.  If it is not TOK_SEP, fpp_unget() the character
   * and return FPP_FALSE.
   */

#if OK_CONCAT
  int c;
  char *token1 = "";
#endif

#if OK_CONCAT
  if (fpp_get(global) != TOK_SEP) {                 /* Token concatenation  */
    fpp_unget(global);
    return (FPP_FALSE);
  }
  else {
    if (lhs_number == 0) { /* The lhs number has already been emit */ 
      token1 = fpp_savestring(global, global->tokenbuf); /* Save first token     */
    }
    c= fpp_get(global);
    if(global->rightconcat) {
      *ret=fpp_macroid(global, &c);           /* Scan next token      */
      if(*ret)
        return(FPP_FALSE);
    } /* BK - BUG? Parses token into global->tokenbuf but never uses it.
      else
      fpp_lookid(global, c);
      */
    switch(type[c]) {                   /* What was it?         */
    case LET:                           /* An identifier, ...   */
      if ((int)strlen(token1) + (int)strlen(global->tokenbuf) >= NWORK) {
        fpp_cfatal(global, FATAL_WORK_AREA_OVERFLOW, token1);
        *ret=FPP_WORK_AREA_OVERFLOW;
        return(FPP_FALSE);
      }
      sprintf(global->work, "%s%s", token1, global->tokenbuf);
      break;
    case DIG:                           /* A number             */
    case DOT:                           /* Or maybe a float     */
      strcpy(global->work, token1);
      global->workp = global->work + strlen(global->work);
      *ret=fpp_scannumber(global, c, fpp_save);
      if(*ret)
        return(FPP_FALSE);
      *ret=fpp_save(global, EOS);
      if(*ret)
        return(FPP_FALSE);
      break;
    default:                            /* An error, ...        */
      if (isprint(c))
        fpp_cerror(global, ERROR_STRANG_CHARACTER, c);
      else
        fpp_cerror(global, ERROR_STRANG_CHARACTER2, c);
      strcpy(global->work, token1);
      fpp_unget(global);
      break;
    }
    /*
     * work has the concatenated token and token1 has
     * the first token (no longer needed).  Unget the
     * new (concatenated) token after freeing token1.
     * Finally, setup to read the new token.
     */
    if (lhs_number == 0) {
      free(token1);                            /* Free up memory       */
    }
    *ret=fpp_ungetstring(global, global->work);  /* Unget the new thing, */
    if(*ret)
      return(FPP_FALSE);
    return(FPP_TRUE);
  }
#else
  return(FPP_FALSE);                    /* Not supported        */
#endif
}

ReturnCode fpp_scanstring(struct Global *global,
                      int delim, /* ' or " */
                      /* Output function: */
                      ReturnCode (*outfun)(struct Global *, int))
{
  /*
   * Scan off a string.  Warning if terminated by newline or EOF.
   * outfun() outputs the character -- to a buffer if in a macro.
   * FPP_TRUE if ok, FPP_FALSE if error.
   */

  int c;
  ReturnCode ret;

  global->instring = FPP_TRUE;              /* Don't strip comments         */
  ret=(*outfun)(global, delim);
  if(ret)
    return(ret);
  while ((c = fpp_get(global)) != delim
         && c != '\n'
         && c != EOF_CHAR) {
    ret=(*outfun)(global, c);
    if(ret)
      return(ret);
    if (c == '\\') {
      ret=(*outfun)(global, fpp_get(global));
      if(ret)
        return(ret);
    }
  }
  global->instring = FPP_FALSE;
  if (c == delim) {
    ret=(*outfun)(global, c);
    return(ret);
  } else {
    fpp_cerror(global, ERROR_UNTERMINATED_STRING);
    fpp_unget(global);
    return(FPP_UNTERMINATED_STRING);
  }
}

ReturnCode fpp_scannumber(struct Global *global,
                      int c,            /* First char of number */
                      /* Output/store func: */
                      ReturnCode (*outfun)(struct Global *, int))
{
  /*
   * Process a number.  We know that c is from 0 to 9 or dot.
   * Algorithm from Dave Conroy's Decus C.
   */

  int radix;            /* 8, 10, or 16         */
  int expseen;          /* 'e' seen in floater  */
  int signseen;         /* '+' or '-' seen      */
  int octal89;          /* For bad octal test   */
  int dotflag;          /* FPP_TRUE if '.' was seen */
  ReturnCode ret;
  char done=FPP_FALSE;

  expseen = FPP_FALSE;                      /* No exponent seen yet */
  signseen = FPP_TRUE;                      /* No +/- allowed yet   */
  octal89 = FPP_FALSE;                      /* No bad octal yet     */
  radix = 10;                           /* Assume decimal       */
  if ((dotflag = (c == '.')) != FPP_FALSE) {/* . something?         */
    ret=(*outfun)(global, '.');         /* Always out the dot   */
    if(ret)
      return(ret);
    if (type[(c = fpp_get(global))] != DIG) { /* If not a float numb, */
      fpp_unget(global);                    /* Rescan strange char  */
      return(FPP_OK);                   /* All done for now     */
    }
  }                                     /* End of float test    */
  else if (c == '0') {                  /* Octal or hex?        */
    ret=(*outfun)(global, c);           /* Stuff initial zero   */
    if(ret)
      return(ret);
    radix = 8;                          /* Assume it's octal    */
    c = fpp_get(global);                    /* Look for an 'x'      */
    if (c == 'x' || c == 'X') {         /* Did we fpp_get one?      */
      radix = 16;                       /* Remember new radix   */
      ret=(*outfun)(global, c);         /* Stuff the 'x'        */
      if(ret)
        return(ret);
      c = fpp_get(global);                  /* Get next character   */
    }
  }
  while (!done) {                       /* Process curr. char.  */
    /*
     * Note that this algorithm accepts "012e4" and "03.4"
     * as legitimate floating-point numbers.
     */
    if (radix != 16 && (c == 'e' || c == 'E')) {
      if (expseen)                      /* Already saw 'E'?     */
        break;                          /* Exit loop, bad nbr.  */
      expseen = FPP_TRUE;                   /* Set exponent seen    */
      signseen = FPP_FALSE;                 /* We can read '+' now  */
      radix = 10;                       /* Decimal exponent     */
    }
    else if (radix != 16 && c == '.') {
      if (dotflag)                      /* Saw dot already?     */
        break;                          /* Exit loop, two dots  */
      dotflag = FPP_TRUE;                   /* Remember the dot     */
      radix = 10;                       /* Decimal fraction     */
    }
    else if (c == '+' || c == '-') {    /* 1.0e+10              */
      if (signseen)                     /* Sign in wrong place? */
        break;                          /* Exit loop, not nbr.  */
      /* signseen = FPP_TRUE; */            /* Remember we saw it   */
    } else {                            /* Check the digit      */
      switch (c) {
      case '8': case '9':               /* Sometimes wrong      */
        octal89 = FPP_TRUE;                 /* Do check later       */
      case '0': case '1': case '2': case '3':
      case '4': case '5': case '6': case '7':
        break;                          /* Always ok            */

      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        if (radix == 16)                /* Alpha's are ok only  */
          break;                        /* if reading hex.      */
      default:                          /* At number end        */
        done=FPP_TRUE;                      /* Break from for loop  */
        continue;
      }                                 /* End of switch        */
    }                                   /* End general case     */
    ret=(*outfun)(global, c);           /* Accept the character */
    if(ret)
      return(ret);
    signseen = FPP_TRUE;                    /* Don't read sign now  */
    c = fpp_get(global);                    /* Read another char    */
  }                                     /* End of scan loop     */
  /*
   * When we break out of the scan loop, c contains the first
   * character (maybe) not in the number.  If the number is an
   * integer, allow a trailing 'L' for long and/or a trailing 'U'
   * for unsigned.  If not those, push the trailing character back
   * on the input stream.  Floating point numbers accept a trailing
   * 'L' for "long double".
   */

  if (dotflag || expseen) {               /* Floating point?      */
    if (c == 'l' || c == 'L') {
      ret=(*outfun)(global, c);
      if(ret)
        return(ret);
      c = fpp_get(global);                   /* Ungotten later       */
    }
  } else {                                      /* Else it's an integer */
    /*
     * We know that dotflag and expseen are both zero, now:
     * dotflag signals "saw 'L'", and
     * expseen signals "saw 'U'".
     */
    done=FPP_TRUE;
    while(done) {
      switch (c) {
      case 'l':
      case 'L':
        if (dotflag) {
          done=FPP_FALSE;
          continue;
        }
        dotflag = FPP_TRUE;
        break;
      case 'u':
      case 'U':
        if (expseen) {
          done=FPP_FALSE;
          continue;
        }
        expseen = FPP_TRUE;
        break;
      default:
        done=FPP_FALSE;
        continue;
      }
      ret=(*outfun)(global, c);       /* Got 'L' or 'U'.      */
      if(ret)
        return(ret);
      c = fpp_get(global);                /* Look at next, too.   */
    }
  }
  fpp_unget(global);                         /* Not part of a number */
  if(!(global->webmode)) {
    if (octal89 && radix == 8)
      fpp_cwarn(global, WARN_ILLEGAL_OCTAL);
  }
  return(FPP_OK);
}

ReturnCode fpp_save(struct Global *global, int c)
{
  if (global->workp >= &global->work[NWORK]) {
    fpp_cfatal(global, FATAL_WORK_BUFFER_OVERFLOW);
    return(FPP_WORK_AREA_OVERFLOW);
  } else
    *global->workp++ = c;
  return(FPP_OK);
}

char *fpp_savestring(struct Global *global, char *text)
{
  /*
   * Store a string into free memory.
   */
  char *result;
  (void)global; // BK - not used but causes warning.
  result = malloc(strlen(text) + 1);
  strcpy(result, text);
  return (result);
}

ReturnCode fpp_getfile(struct Global *global,
                   size_t bufsize, /* Line or define buffer size   */
                   char *name,
                   FILEINFO **file) /* File or macro name string        */
{
  /*
   * Common FILEINFO buffer initialization for a new file or macro.
   */

  size_t size;

  size = strlen(name);                          /* File/macro name      */

  if(!size) {
      name = "[stdin]";
      size = strlen(name);
  }

  *file = (FILEINFO *) malloc((int)(sizeof (FILEINFO) + bufsize + size));
  if(!*file)
    return(FPP_OUT_OF_MEMORY);
  (*file)->parent = global->infile;             /* Chain files together */
  (*file)->fp = NULL;                           /* No file yet          */
  (*file)->filename = fpp_savestring(global, name); /* Save file/macro name */
  (*file)->progname = NULL;                     /* No #line seen yet    */
  (*file)->unrecur = 0;                         /* No macro fixup       */
  (*file)->bptr = (*file)->buffer;              /* Initialize line ptr  */
  (*file)->buffer[0] = EOS;                     /* Force first read     */
  (*file)->line = 0;                            /* (Not used just yet)  */
  if (global->infile != NULL)                   /* If #include file     */
    global->infile->line = global->line;        /* Save current line    */
  global->infile = (*file);                     /* New current file     */
  global->line = 1;                             /* Note first line      */
  return(FPP_OK);                               /* All done.            */
}

/*
 *                      C P P   S y m b o l   T a b l e s
 */

DEFBUF *fpp_lookid(struct Global *global,
               int c)           /* First character of token     */
{
  /*
   * Look for the next token in the symbol table. Returns token in tokenbuf.
   * If found, returns the table pointer;  Else returns NULL.
   */

  int nhash;
  DEFBUF *dp;
  int ct;
  int temp = 0;
  int isrecurse;        /* For #define foo foo  */

  nhash = 0;
  if ((isrecurse = (c == DEF_MAGIC)))   /* If recursive macro   */
    c = fpp_get(global);                    /* hack, skip DEF_MAGIC */
  ct = 0;
  do {
    if (ct == global->tokenbsize)
      global->tokenbuf = realloc(global->tokenbuf, 1 + (global->tokenbsize *= 2));
    global->tokenbuf[ct++] = c;         /* Store token byte     */
    nhash += c;                         /* Update hash value    */
    c = fpp_get(global);
  }  while (type[c] == LET || type[c] == DIG);
  fpp_unget(global);                        /* Rescan terminator    */
  global->tokenbuf[ct] = EOS;           /* Terminate token      */
  if (isrecurse)                        /* Recursive definition */
    return(NULL);                       /* undefined just now   */
  nhash += ct;                          /* Fix hash value       */
  dp = global->symtab[nhash % SBSIZE];  /* Starting bucket      */
  while (dp != (DEFBUF *) NULL) {       /* Search symbol table  */
    if (dp->hash == nhash               /* Fast precheck        */
        && (temp = strcmp(dp->name, global->tokenbuf)) >= 0)
      break;
    dp = dp->link;                      /* Nope, try next one   */
  }
  return((temp == 0) ? dp : NULL);
}

DEFBUF *fpp_defendel(struct Global *global,
                 char *name,
                 int delete)            /* FPP_TRUE to delete a symbol */
{
  /*
   * Enter this name in the lookup table (delete = FPP_FALSE)
   * or delete this name (delete = FPP_TRUE).
   * Returns a pointer to the define block (delete = FPP_FALSE)
   * Returns NULL if the symbol wasn't defined (delete = FPP_TRUE).
   */

  DEFBUF *dp;
  DEFBUF **prevp;
  char *np;
  int nhash;
  int temp;
  size_t size;

  for (nhash = 0, np = name; *np != EOS;)
    nhash += *np++;
  size = (np - name);
  nhash += (int)size;
  prevp = &global->symtab[nhash % SBSIZE];
  while ((dp = *prevp) != (DEFBUF *) NULL) {
    if (dp->hash == nhash
        && (temp = strcmp(dp->name, name)) >= 0) {
      if (temp > 0)
        dp = NULL;                      /* Not found            */
      else {
        *prevp = dp->link;              /* Found, unlink and    */
        if (dp->repl != NULL)           /* Free the replacement */
          free(dp->repl);               /* if any, and then     */
        free((char *) dp);              /* Free the symbol      */
      }
      break;
    }
    prevp = &dp->link;
  }
  if (!delete) {
    dp = (DEFBUF *) malloc(sizeof (DEFBUF) + size);
    dp->link = *prevp;
    *prevp = dp;
    dp->hash = nhash;
    dp->repl = NULL;
    dp->nargs = 0;
    strcpy(dp->name, name);
  }
  return(dp);
}

void fpp_delalldefines(struct Global *global)
{
  /*
   * Delete all the defines in the tables and free memory
   */

  DEFBUF *dp;
  DEFBUF *prevp;
  int i;

  for (i = 0; i < SBSIZE; ++i)
  {
    prevp = global->symtab[i];
    while ((dp = prevp) != (DEFBUF *)NULL) {
      prevp = dp->link;
      free(dp->repl);                /* Free the replacement */
      free((char *)dp);              /* Free the symbol      */
    }
    global->symtab[i] = NULL;
  }
}


void fpp_outdefines(struct Global *global)
{
  DEFBUF *dp;
  DEFBUF **syp;

  fpp_delbuiltindefines(global);                   /* Delete built-in #defines     */
  for (syp = global->symtab; syp < &global->symtab[SBSIZE]; syp++) {
    if ((dp = *syp) != (DEFBUF *) NULL) {
      do {
        fpp_outadefine(global, dp);
      } while ((dp = dp->link) != (DEFBUF *) NULL);
    }
  }
}

INLINE FILE_LOCAL
void fpp_outadefine(struct Global *global, DEFBUF *dp)
{
  char *cp;
  int c;

  /* printf("#define %s", dp->name); */
  fpp_Putstring(global, "#define ");
  fpp_Putstring(global, dp->name);

  if (dp->nargs > 0) {
    int i;
    fpp_Putchar(global, '(');
    for (i = 1; i < dp->nargs; i++) {
      /* printf("__%d,", i); */
      fpp_Putstring(global, "__");
      fpp_Putint(global, i);
      fpp_Putchar(global, ',');
    }
    /* printf("__%d)", i); */
    fpp_Putstring(global, "__");
    fpp_Putint(global, i);
    fpp_Putchar(global, ')');

  } else if (dp->nargs == 0) {
    fpp_Putstring(global, "()");
  }
  if (dp->repl != NULL) {
    fpp_Putchar(global, '\t');
    for (cp = dp->repl; (c = *cp++ & 0xFF) != EOS;) {
      if (c >= MAC_PARM && c < (MAC_PARM + PAR_MAC)) {
        /* printf("__%d", c - MAC_PARM + 1); */
        fpp_Putstring(global, "__");
        fpp_Putint(global, c - MAC_PARM + 1);
      } else if (isprint(c) || c == '\t' || c == '\n')
        fpp_Putchar(global, c);
      else switch (c) {
      case QUOTE_PARM:
        fpp_Putchar(global, '#');
        break;
      case DEF_MAGIC:       /* Special anti-recursion */
      case MAC_PARM + PAR_MAC:    /* Special "arg" marker */
        break;
      case COM_SEP:
#if COMMENT_INVISIBLE
        fpp_Putstring(global, "/**/");
#else
        fpp_Putchar(global, ' ');
#endif
        break;
      case TOK_SEP:
        fpp_Putstring(global, "##");
        break;
      default:
        {
          /* Octal output! */
          char buffer[32];
          sprintf(buffer, "\\0%o", c);
          fpp_Putstring(global, buffer);
        }
      }
    }
  }
  fpp_Putchar(global, '\n');
}

/*
 *                      G E T
 */

int fpp_get(struct Global *global)
{
  /*
   * Return the next character from a macro or the current file.
   * Handle end of file from #include files.
   */

  int c;
  FILEINFO *file;
  int popped;   /* Recursion fixup      */
  long comments=0;

  popped = 0;
 get_from_file:
  if ((file = global->infile) == NULL)
    return (EOF_CHAR);
 newline:
  /*
   * Read a character from the current input line or macro.
   * At EOS, either finish the current macro (freeing temp.
   * storage) or read another line from the current input file.
   * At EOF, exit the current file (#include) or, at EOF from
   * the cpp input file, return EOF_CHAR to finish processing.
   */
  if ((c = *file->bptr++ & 0xFF) == EOS) {
    /*
     * Nothing in current line or macro.  Get next line (if
     * input from a file), or do end of file/macro processing.
     * In the latter case, jump back to restart from the top.
     */
    if (file->fp == NULL) {             /* NULL if macro        */
      popped++;
      global->recursion -= file->unrecur;
      if (global->recursion < 0)
        global->recursion = 0;
      global->infile = file->parent;            /* Unwind file chain    */
    } else {                            /* Else get from a file */
      /*
       * If a input routine has been specified in the initial taglist,
       * we should get the next line from that function IF we're reading
       * from that certain file!
       */

      if(global->input && global->first_file && !strcmp(global->first_file, file->filename))
        file->bptr = global->input(file->buffer, NBUFF, global->userdata);
      else
        file->bptr = fgets(file->buffer, NBUFF, file->fp);
      if(file->bptr != NULL) {
        goto newline;           /* process the line     */
      } else {
        if(!(global->input && global->first_file && !strcmp(global->first_file, file->filename)))
          /* If the input function isn't user supplied, close the file! */
          fclose(file->fp);           /* Close finished file  */
        if ((global->infile = file->parent) != NULL) {
          /*
           * There is an "ungotten" newline in the current
           * infile buffer (set there by fpp_doinclude() in
           * cpp1.c).  Thus, we know that the mainline code
           * is skipping over blank lines and will do a
           * #line at its convenience.
           */
          global->wrongline = FPP_TRUE;     /* Need a #line now     */
        }
      }
    }
    /*
     * Free up space used by the (finished) file or macro and
     * restart input from the parent file/macro, if any.
     */
    free(file->filename);               /* Free name and        */
    if (file->progname != NULL)         /* if a #line was seen, */
      free(file->progname);             /* free it, too.        */
    free(file);                         /* Free file space      */
    if (global->infile == NULL)         /* If at end of file    */
      return (EOF_CHAR);                /* Return end of file   */
    global->line = global->infile->line; /* Reset line number   */
    goto get_from_file;                 /* Get from the top.    */
  }
  /*
   * Common processing for the new character.
   */
  if (c == DEF_MAGIC && file->fp != NULL) /* Don't allow delete   */
    goto newline;                       /* from a file          */
  if (file->parent != NULL) {           /* Macro or #include    */
    if (popped != 0)
      file->parent->unrecur += popped;
    else {
      global->recursion -= file->parent->unrecur;
      if (global->recursion < 0)
        global->recursion = 0;
      file->parent->unrecur = 0;
    }
  }
  if (c == '\n')                        /* Maintain current     */
    ++global->line;                     /* line counter         */
  if (global->instring)                 /* Strings just return  */
    return (c);                         /* the character.       */
  else if (c == '/') {                  /* Comment?             */
    global->instring = FPP_TRUE;            /* So fpp_get() won't loop  */

    /* Check next byte for '*' and if(cplusplus) also '/' */
    if ( (c = fpp_get(global)) != '*' )
      if(!global->cplusplus || (global->cplusplus && c!='/')) {
        global->instring = FPP_FALSE;       /* Nope, no comment     */
        fpp_unget(global);                  /* Push the char. back  */
        return ('/');                   /* Return the slash     */
      }

    comments = 1;

    if (global->keepcomments) {         /* If writing comments   */

      global->comment = FPP_TRUE; /* information that a comment has been output */
      if(global->showspace) {
        /* Show all whitespaces! */
        global->spacebuf[global->chpos] = '\0';
        fpp_Putstring(global, global->spacebuf);
      }

      if(c=='*') {
        fpp_Putchar(global, '/');           /* Write out the         */
        fpp_Putchar(global, '*');           /*   initializer         */
      } else {
        /* C++ style comment */
        fpp_Putchar(global, '/');           /* Write out the         */
        fpp_Putchar(global, '/');           /*   initializer         */
      }
    }

    if(global->cplusplus && c=='/') {   /* Eat C++ comment!      */
      do {
        c=fpp_get(global);
        if(global->keepcomments)
          fpp_Putchar(global, c);
      } while(c!='\n' && c!=EOF_CHAR);  /* eat all to EOL or EOF */
      global->instring = FPP_FALSE;         /* End of comment        */
      return(c);                        /* Return the end char   */
    }

    for (;;) {                          /* Eat a comment         */
      c = fpp_get(global);
    test:
      if (global->keepcomments && c != EOF_CHAR)
        fpp_Putchar(global, c);
      switch (c) {
      case EOF_CHAR:
        fpp_cerror(global, ERROR_EOF_IN_COMMENT);
        return (EOF_CHAR);

      case '/':
        if(global->nestcomments || global->warnnestcomments) {
          if((c = fpp_get(global)) != '*')
            goto test;
          if(global->warnnestcomments) {
            fpp_cwarn(global, WARN_NESTED_COMMENT);
          }
          if(global->nestcomments)
            comments++;
        }
        break;

      case '*':
        if ((c = fpp_get(global)) != '/')           /* If comment doesn't   */
          goto test;                    /* end, look at next    */
        if (global->keepcomments) {     /* Put out the comment  */
          fpp_Putchar(global, c);           /* terminator, too      */
        }
        if(--comments)
          /* nested comment, continue! */
          break;

        global->instring = FPP_FALSE;       /* End of comment,      */
        /*
         * A comment is syntactically "whitespace" --
         * however, there are certain strange sequences
         * such as
         *              #define foo(x)  (something)
         *                      foo|* comment *|(123)
         *           these are '/' ^           ^
         * where just returning space (or COM_SEP) will cause
         * problems.  This can be "fixed" by overwriting the
         * '/' in the input line buffer with ' ' (or COM_SEP)
         * but that may mess up an error message.
         * So, we peek ahead -- if the next character is
         * "whitespace" we just get another character, if not,
         * we modify the buffer.  All in the name of purity.
         */
        if (*file->bptr == '\n'
            || type[*file->bptr & 0xFF] == SPA)
          goto newline;
#if COMMENT_INVISIBLE
        /*
         * Return magic (old-fashioned) syntactic space.
         */
        return ((file->bptr[-1] = COM_SEP));
#else
        return ((file->bptr[-1] = ' '));
#endif

      case '\n':                        /* we'll need a #line   */
        if (!global->keepcomments)
          global->wrongline = FPP_TRUE;     /* later...             */
      default:                          /* Anything else is     */
        break;                          /* Just a character     */
      }                                 /* End switch           */
    }                                   /* End comment loop     */
  }                                     /* End if in comment    */
  else if (!global->inmacro && c == '\\') { /* If backslash, peek   */
    if ((c = fpp_get(global)) == '\n') {    /* for a <nl>.  If so,  */
      global->wrongline = FPP_TRUE;
      goto newline;
    } else {                            /* Backslash anything   */
      fpp_unget(global);                    /* Get it later         */
      return ('\\');                    /* Return the backslash */
    }
  } else if (c == '\f' || c == VT)      /* Form Feed, Vertical  */
    c = ' ';                            /* Tab are whitespace   */
  return (c);                           /* Just return the char */
}

void fpp_unget(struct Global *global)
{
  /*
   * Backup the pointer to reread the last character.  Fatal error
   * (code bug) if we backup too far.  fpp_unget() may be called,
   * without problems, at end of file.  Only one character may
   * be ungotten.  If you need to unget more, call fpp_ungetstring().
   */

  FILEINFO *file;
  if ((file = global->infile) == NULL)
    return;                     /* Unget after EOF            */
  if (--file->bptr < file->buffer) {
    fpp_cfatal(global, FATAL_TOO_MUCH_PUSHBACK);
    /* This happens only if used the wrong way! */
    return;
  }
  if (*file->bptr == '\n')              /* Ungetting a newline?       */
    --global->line;                     /* Unget the line number, too */
}

ReturnCode fpp_ungetstring(struct Global *global, char *text)
{
  /*
   * Push a string back on the input stream.  This is done by treating
   * the text as if it were a macro.
   */

  FILEINFO *file;
  ReturnCode ret;

  ret = fpp_getfile(global, strlen(text) + 1, "", &file);
  if(!ret)
    strcpy(file->buffer, text);
  return(ret);
}

int fpp_cget(struct Global *global)
{
  /*
   * Get one character, absorb "funny space" after comments or
   * token concatenation
   */

  int c;
  do {
    c = fpp_get(global);
#if COMMENT_INVISIBLE
  } while (c == TOK_SEP || c == COM_SEP);
#else
  } while (c == TOK_SEP);
#endif
  return (c);
}

/*
 * Error messages and other hacks.
 */

INLINE FILE_LOCAL
void fpp_domsg(struct Global *global,
  ErrorCode error,  /* error message number */
  va_list arg)      /* Something for the message    */
{
  /*
   * Print filenames, macro names, and line numbers for error messages.
   */

  static char *ErrorMessage[]={
    /*
     * ERRORS:
     */
    "#%s must be in an #if",
    "#%s may not follow #else",
    "#error directive encountered",
    "Preprocessor assertion failure",
    "#if, #ifdef, or #ifndef without an argument",
    "#include syntax error",
    "#define syntax error",
    "Redefining defined variable \"%s\"",
    "Illegal #undef argument",
    "Recursive macro definition of \"%s\"(Defined by \"%s\")",
    "end of file within macro argument",
    "misplaced constant in #if",
    "#if value stack overflow",
    "Illegal #if line",
    "Operator %s in incorrect context",
    "expression stack overflow at op \"%s\"",
    "unbalanced paren's, op is \"%s\"",
    "Misplaced '?' or ':', previous operator is %s",
    "Can't use a string in an #if",
    "Bad #if ... defined() syntax",
    "= not allowed in #if",
    "Unexpected \\ in #if",
    "#if ... sizeof() syntax error",
    "#if sizeof, unknown type \"%s\"",
    "#if ... sizeof: illegal type combination",
    "#if sizeof() error, no type specified",
    "Unterminated string",
    "EOF in comment",
    "Inside #ifdef block at end of input, depth = %d",
    "illegal character '%c' in #if",
    "illegal character (%d decimal) in #if",
    "#if ... sizeof: bug, unknown type code 0x%x",
    "#if bug, operand = %d.",
    "Strange character '%c' after ##",
    "Strange character (%d.) after ##",

    "", /* Dummy, to visualize the border between errors and warnings */
    /*
     * WARNINGS:
     */
    "Control line \"%s\" within macro expansion",
    "Illegal # command \"%s\"",
    "Unexpected text in #control line ignored",
    "too few values specified to sizeof",
    "too many values specified to sizeof! Not used.",
    "\"%s\" wasn't defined",
    "Internal error!",
    "Macro \"%s\" needs arguments",
    "Wrong number of macro arguments for \"%s\"",
    "%s by zero in #if, zero result assumed",
    "Illegal digit in octal number",
    "multi-byte constant '%c' isn't portable",
    "Cannot open include file \"%s\"",
    "Illegal bracket '[]' balance, depth = %d",
    "Illegal parentheses '()' balance, depth = %d",
    "Illegal brace '{}' balance, depth = %d",
    "Nested comment",

    "", /* Dummy, to visualize the border between warnings and fatals */

    /*
     * FATALS:
     */
    "Too many nested #%s statements",
    "Filename work buffer overflow",
    "Too many include directories",
    "Too many include files",
    "Too many arguments for macro",
    "Macro work area overflow",
    "Bug: Illegal __ macro \"%s\"",
    "Too many arguments in macro expansion",
    "Out of space in macro \"%s\" arg expansion",
    "work buffer overflow doing %s ##",
    "Work buffer overflow",
    "Out of memory",
    "Too much pushback", /* internal */
    };

  char *tp;
  FILEINFO *file;
  char *severity=error<BORDER_ERROR_WARN?"Error":
    error<BORDER_WARN_FATAL?"Warning":
      "Fatal";

  for (file = global->infile; file && !file->fp; file = file->parent)
    ;
  tp = file ? file->filename : 0;
  fpp_Error(global, "%s\"%s\", line %d: %s: ",
        MSG_PREFIX, tp, global->infile?(global->infile->fp?global->line:file->line):0, severity);
  if(global->error)
    global->error(global->userdata, ErrorMessage[error], arg);
#if defined(UNIX)
  else
    vfprintf(stderr, ErrorMessage[error], arg);
#elif defined(AMIGA)
  else
    return;
#endif
  fpp_Error(global, "\n");

  if (file)   /*OIS*0.92*/
    while ((file = file->parent) != NULL) { /* Print #includes, too */
      tp = file->parent ? "," : ".";
      if (file->fp == NULL)
        fpp_Error(global, " from macro %s%s\n", file->filename, tp);
      else
        fpp_Error(global, " from file %s, line %d%s\n",
              (file->progname != NULL) ? file->progname : file->filename,
              file->line, tp);
    }

  if(error<BORDER_ERROR_WARN)
    /* Error! Increase error counter! */
    global->errors++;
}

void fpp_cerror(struct Global *global,
            ErrorCode message,
            ...)        /* arguments    */
{
  /*
   * Print a normal error message, string argument.
   */
  va_list arg;
  va_start(arg, message);
  fpp_domsg(global, message, arg);
}

void fpp_Error(struct Global *global, char *format, ...)
{
  /*
   * Just get the arguments and send a decent string to the user error
   * string handler or to stderr.
   */

  va_list arg;
  va_start(arg, format);
  if(global->error)
    global->error(global->userdata, format, arg);
#if defined(UNIX)
  else
    vfprintf(stderr, format, arg);
#endif
}

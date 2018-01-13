/******************************************************************************
Copyright (c) 1993 - 2011 Daniel Stenberg

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

#if defined(AMIGA)
#include        <dos.h>
#if defined(SHARED)
int _OSERR=0;
char *_ProgramName="junk";
void __stdargs _XCEXIT(long a) { return; }
#endif
#endif

FILE_LOCAL ReturnCode output(struct Global *, int); /* Output one character */
FILE_LOCAL void sharp(struct Global *);
INLINE FILE_LOCAL ReturnCode cppmain(struct Global *);

int fppPreProcess(struct fppTag *tags)
{
  size_t i=0;
  ReturnCode ret;       /* cpp return code */
  int retVal;           /* fppPreProcess return code */
  struct Global *global;

  global=(struct Global *)malloc(sizeof(struct Global));
  if(!global)
    return(FPP_OUT_OF_MEMORY);

  memset(global, 0, sizeof(struct Global));

  global->infile=NULL;
  global->line=0;
  global->wrongline=0;
  global->errors=0;
  global->recursion=0;
  global->rec_recover=TRUE;
  global->instring=FALSE;
  global->inmacro=FALSE;
  global->workp=NULL;
  global->keepcomments = FALSE;  /* Write out comments flag     */
  global->cflag = FALSE;          /* -C option (keep comments)    */
  global->eflag = FALSE;          /* -E option (never fail)       */
  global->nflag = 0;              /* -N option (no predefines)    */
  global->wflag = FALSE;          /* -W option (write #defines)   */

  global->ifstack[0]=TRUE;       /* #if information     */
  global->ifptr = global->ifstack;
  global->incend = global->incdir;

  /* names defined at cpp start */
  global->preset[0]="frexxcpp"; /* This is the Frexx cpp program */
#if defined( amiga )
  global->preset[1]="amiga";
  global->preset[2]="m68000";
  global->preset[3]="amigados";
  global->preset[4]= NULL;              /* Must be last         */
#elif defined( unix )
  global->preset[1]="unix";
  global->preset[2]= NULL;
#endif

  /* Note: order is important   */
  global->magic[0] = "__LINE__";
  global->magic[1] = "__FILE__";
  global->magic[2] = "__FUNCTION__";
  global->magic[3] = "__FUNC_LINE__";
  global->magic[4] = NULL;                        /* Must be last       */

  global->funcline = 0;

  global->cplusplus=1;
  global->sharpfilename=NULL;

  global->parmp=NULL;
  global->nargs=0;

  global->macro=NULL;
  global->evalue=0;

  global->depends=NULL;
  global->input=NULL;
  global->output=NULL;
  global->error=NULL;
  global->first_file=NULL;
  global->userdata=NULL;

  global->linelines=TRUE;
  global->warnillegalcpp = FALSE;
  global->outputLINE = TRUE;
  global->warnnoinclude = TRUE;
  global->showversion = TRUE;
  global->showincluded = FALSE;
  global->showspace = FALSE;
  global->nestcomments = FALSE;
  global->warnnestcomments = FALSE;
  global->outputfile = TRUE;
  global->included = 0;

  global->comment = FALSE;
  global->rightconcat = FALSE;
  global->work[0] = '\0';
  global->initialfunc = NULL;

  memset(global->symtab, 0, SBSIZE * sizeof(DEFBUF *));

  ret=initdefines(global);  /* O.S. specific def's  */
  if(ret)
    return(ret);
  dooptions(global, tags);  /* Command line -flags  */
  ret=addfile(global, stdin, global->work); /* "open" main input file       */

  global->out = global->outputfile;

  if(!ret)
    ret=cppmain(global);             /* Process main file            */
  if ((i = (global->ifptr - global->ifstack)) != 0) {
#if OLD_PREPROCESSOR
    cwarn(global, ERROR_IFDEF_DEPTH, i);
#else
    cerror(global, ERROR_IFDEF_DEPTH, i);
#endif
  }
  fflush(stdout);
// BK -  fclose(stdout);
  delalldefines(global);

  retVal = IO_NORMAL;
  if (global->errors > 0 && !global->eflag)
    retVal = IO_ERROR;
  free(global->tokenbuf);
  free(global->functionname);
  free(global->spacebuf);
  free(global);
  return retVal;       /* No errors or -E option set   */
}

INLINE FILE_LOCAL
ReturnCode cppmain(struct Global *global)
{
  /*
   * Main process for cpp -- copies tokens from the current input
   * stream (main file, include file, or a macro) to the output
   * file.
   */

  int c;        /* Current character    */
  int counter;  /* newlines and spaces  */
  ReturnCode ret; /* return code variable type */

  long bracelevel = 0;
  long parenlevel = 0;
  long bracketlevel = 0;
  int fake = 0;

#define MAX_FUNC_LENGTH 50

  char tempfunc[MAX_FUNC_LENGTH + 1];
  char tempfunc2[MAX_FUNC_LENGTH + 1];
  char define = 0; /* probability of a function define phase in the program */
  char prev = 0; /* previous type */
  char go = 0;
  char include = 0;
  char initfunc = 0;

  /* Initialize for reading tokens */
  global->tokenbsize = 50;
  global->tokenbuf = malloc(global->tokenbsize + 1);
  if(!global->tokenbuf)
    return(FPP_OUT_OF_MEMORY);

  global->functionname = malloc(global->tokenbsize + 1);
  if(!global->functionname)
    return(FPP_OUT_OF_MEMORY);
  global->functionname[0] = '\0';

  if(global->showspace) {
    global->spacebuf = (char *)malloc(MAX_SPACE_SIZE);
    if(!global->spacebuf)
      return(FPP_OUT_OF_MEMORY);
  }

  if(global->showversion)
      Error(global, VERSION_TEXT);

  /*
   * Explicitly output a #line at the start of cpp output so
   * that lint (etc.) knows the name of the original source
   * file.  If we don't do this explicitly, we may get
   * the name of the first #include file instead.
   */
  if(global->linelines) /* if #line lines are wanted! */
    sharp(global);
  /*
   * This loop is started "from the top" at the beginning of each line
   * wrongline is set TRUE in many places if it is necessary to write
   * a #line record.  (But we don't write them when expanding macros.)
   *
   * The counter variable has two different uses:  at
   * the start of a line, it counts the number of blank lines that
   * have been skipped over. These are then either output via
   * #line records or by outputting explicit blank lines.
   * When expanding tokens within a line, the counter remembers
   * whether a blank/tab has been output.  These are dropped
   * at the end of the line, and replaced by a single blank
   * within lines.
   */

  include = global->included;

  while(include--) {
    openinclude(global, global->include[(unsigned)include], TRUE);
  }
  
  for (;;) {
    counter = 0;                        /* Count empty lines    */
    for (;;) {                          /* For each line, ...   */
      global->comment = FALSE;          /* No comment yet!      */
      global->chpos = 0;                /* Count whitespaces    */
      while (type[(c = get(global))] == SPA)  /* Skip leading blanks */
	if(global->showspace) {
	  if(global->chpos<MAX_SPACE_SIZE-1)
	    /* we still have buffer to store this! */
	    global->spacebuf[global->chpos++]=(char)c;
	}
      if (c == '\n') {                  /* If line's all blank, */
	if(global->comment) {
	  /* A comment was output! */
	  Putchar(global, '\n');
	}
	else
	  ++counter;                    /* Do nothing now       */
      }
      else if (c == '#') {              /* Is 1st non-space '#' */
	global->keepcomments = FALSE;   /* Don't pass comments  */
	ret = control(global, &counter); /* Yes, do a #command   */
	if(ret)
	  return(ret);
	global->keepcomments = (global->cflag && compiling);
      }
      else if (c == EOF_CHAR)           /* At end of file?      */
	break;
      else if (!compiling) {            /* #ifdef false?        */
	skipnl(global);                 /* Skip to newline      */
	counter++;                      /* Count it, too.       */
      } else {
	break;                          /* Actual token         */
      }
    }
    if (c == EOF_CHAR)                  /* Exit process at      */
      break;                            /* End of file          */
    /*
     * If the loop didn't terminate because of end of file, we
     * know there is a token to compile.  First, clean up after
     * absorbing newlines.  counter has the number we skipped.
     */
    if(global->linelines) { /* if #line lines are wanted! */
      if ((global->wrongline && global->infile->fp != NULL) || counter > 4)
        sharp(global);                    /* Output # line number */
      else {                              /* If just a few, stuff */
        while (--counter >= 0)            /* them out ourselves   */
	  Putchar(global, (int)'\n');
      }
    }
    if(global->showspace) {
      /* Show all whitespaces! */
      global->spacebuf[global->chpos] = '\0';
      Putstring(global, global->spacebuf);
    }
    
    /*
     * Process each token on this line.
     */
    unget(global);                      /* Reread the char.     */
    for (;;) {                          /* For the whole line,  */
      do {                              /* Token concat. loop   */
	for (global->chpos = counter = 0; type[(c = get(global))] == SPA;) {
#if COMMENT_INVISIBLE
	  if (c != COM_SEP)
	    counter++;
#else
	  if(global->showspace && global->chpos < MAX_SPACE_SIZE-1) {
	    global->spacebuf[global->chpos++]=(char)c;
	  }
	  counter++;            /* Skip over blanks     */
#endif
	}
	if (c == EOF_CHAR || c == '\n')
	  break;                      /* Exit line loop       */
	else if (counter > 0) {       /* If we got any spaces */
	  if(!global->showspace)      /* We don't output all spaces */
	    Putchar(global, (int)' ');/* Output one space     */
	  else {
	    global->spacebuf[global->chpos] = '\0';
	    Putstring(global, global->spacebuf); /* Output all whitespaces */
	  }
	}
	if((ret=macroid(global, &c)))   /* Grab the token       */
	  return(ret);
      } while (type[c] == LET && catenate(global, &ret) && !ret);
      if(ret)
	/* If the loop was broken because of a fatal error! */
	return(ret);
      if (c == EOF_CHAR || c == '\n') /* From macro exp error */
	break;                        /* Exit line loop       */
      go++;
      switch (type[c]) {
      case LET:
	go =0;
	/* Quite ordinary token */
	Putstring(global, global->tokenbuf);
	
	if(!define) {
	  /* Copy the name */
	  strncpy(tempfunc, global->tokenbuf, MAX_FUNC_LENGTH);
          tempfunc[MAX_FUNC_LENGTH]=0;
	}
	/* fputs(global->tokenbuf, stdout); */
	break;
      case DIG:                 /* Output a number      */
      case DOT:                 /* Dot may begin floats */
	go = 0;
	ret=scannumber(global, c, (ReturnCode(*)(struct Global *, int))output);
	if(ret)
	  return(ret);
	break;
      case QUO:                 /* char or string const */
	go = 0;
	/* Copy it to output */
        if(!global->webmode) {
          ret=scanstring(global, c,
                         (ReturnCode(*)(struct Global *, int))output);
          if(ret)
            return(ret);
          break;
        }
        /* FALLTHROUGH */
      default:                  /* Some other character */
	
	define++;
	switch(c) {
	case '{':
	  if(! bracelevel++ && define > 2) {
	    /*
	     * This is a starting brace. If there is a probability of a
	     * function defining, we copy the `tempfunc' function name to
	     * `global->functionname'.
	     */
	    strcpy(global->functionname, tempfunc2);
	    global->funcline = global->line;

		if(global->outputfunctions) {
			/*
			 * Output the discovered function name to stderr!
			 */
			Error(global, "#> Function defined at line %d: %s <#\n",
				  global->line,
				  global->functionname);
		}

	    if(global->initialfunc) {
		int a;
		for(a=0; a<global->excluded; a++) {
		    /* check for excluded functions */
		    if(!strcmp(global->functionname,
			       global->excludedinit[a]))
			break;
		}
		if(a==global->excluded) {
		    expstuff(global, "__brace__", "{");
		    expstuff(global, "__init_func__", global->initialfunc);
		    initfunc = TRUE;
		}
	    }

	  }
	  break;
	case '}':
	  go = 0;
	  if( (--bracelevel == initfunc) &&
	     strcmp(global->infile->filename, "__init_func__") ) {
	    /* we just stepped out of the function! */
	    global->functionname[0] = '\0';
	    global->funcline = 0;
	    define = 1;

	    if(initfunc) {
	      Putchar(global, '}');
	      bracelevel--;
	      initfunc=0;
	    }
	  }
	  fake = 0;
	  break;
	  
	case ';':
	case ',':
	  if(go == 2) {
	    define = 1;
	    fake = 0;
	    go--;
	    break;
	  }
	  break;
	case '(':
	  if(! parenlevel++ && !bracelevel) {
	    if(go == 2) {
	      /* foobar(text) -> "(" is found. This can't be a
		 function */
	      go--;
	      define = 1;
	      break;
	    }
	    if( define < 2 && prev == LET) {
	      /* This is the first parenthesis on the ground brace
		 level, and we did previously not have a probable
		 function name */
	      strncpy(tempfunc2, global->tokenbuf, MAX_FUNC_LENGTH);
              tempfunc2[MAX_FUNC_LENGTH]=0;
	      define++;
	    }
	    else {
	      /* we have a fake start */
	      fake++;
	    }
	  }
	  break;
	case ')':
	  if(! --parenlevel && !bracelevel && define>1 && !fake) {
	    /*
	     * The starting parentheses level and
	     * the starting brace level.
	     * This might be the start of a function defining coming
	     * up!
	     */
	    define++; /* increase probability */
	    fake = 0;
	    go = 1;
	  }
	  break;
	case '[':
	  bracketlevel++;
	  break;
	case ']':
	  bracketlevel--;
	  break;
	}
	define--; /* decrease function probability */
	
	Putchar(global, c);     /* Just output it       */
	break;
      }                         /* Switch ends          */
      prev = type[c];
    }                           /* Line for loop        */
    
    if (c == '\n') {  /* Compiling at EOL?    */
      Putchar(global, '\n');              /* Output newline, if   */
      if (global->infile->fp == NULL)     /* Expanding a macro,   */
	global->wrongline = TRUE; /* Output # line later        */
    }
  }                             /* Continue until EOF   */

  if(global->showbalance) {
    if(bracketlevel) {
      cwarn(global, WARN_BRACKET_DEPTH, bracketlevel);
    }
    if(parenlevel) {
      cwarn(global, WARN_PAREN_DEPTH, parenlevel);
    }
    if(bracelevel) {
      cwarn(global, WARN_BRACE_DEPTH, bracelevel);
    }
  }
  if (global->wflag) {
    global->out = TRUE;         /* enable output */
    outdefines(global);         /* Write out #defines   */
  }
  return(FPP_OK);
}

FILE_LOCAL
ReturnCode output(struct Global *global, int c)
{
  /*
   * Output one character to stdout -- output() is passed as an
   * argument to scanstring()
   */
#if COMMENT_INVISIBLE
  if (c != TOK_SEP && c != COM_SEP)
#else
  if (c != TOK_SEP)
#endif
    Putchar(global, c);
  return(FPP_OK);
}

void Putchar(struct Global *global, int c)
{
  /*
   * Output one character to stdout or to output function!
   */
  if(!global->out)
    return;
#if defined(UNIX)
  if(global->output)
    global->output(c, global->userdata);
  else
    putchar(c);
#else /* amiga */
  global->output(c, global->userdata);
#endif
}

void Putstring(struct Global *global, char *string)
{
  /*
   * Output a string! One letter at a time to the Putchar routine!
   */

  if(!string)
    return;

  while(*string)
    Putchar(global, *string++);
}

void Putint(struct Global *global, int number)
{
  /*
   * Output the number as a string.
   */

  char buffer[16]; /* an integer can't be that big! */
  char *point=buffer;

  sprintf(buffer, "%d", number);

  while(*point)
    Putchar(global, *point++);
}


FILE_LOCAL
void sharp(struct Global *global)
{
  /*
   * Output a line number line.
   */

  char *name;
  if (global->keepcomments)                     /* Make sure # comes on */
    Putchar(global, '\n');                      /* a fresh, new line.   */
  /*  printf("#%s %d", LINE_PREFIX, global->line); */

  Putchar(global, '#');
  if(global->outputLINE)
          Putstring(global, LINE_PREFIX);
  Putchar(global, ' ');
  Putint(global, global->line);

  if (global->infile->fp != NULL) {
    name = (global->infile->progname != NULL)
      ? global->infile->progname : global->infile->filename;
    if (global->sharpfilename == NULL
        || (global->sharpfilename != NULL && !streq(name, global->sharpfilename))) {
      if (global->sharpfilename != NULL)
        free(global->sharpfilename);
      global->sharpfilename = savestring(global, name);
      /* printf(" \"%s\"", name); */
      Putstring(global, " \"");
      Putstring(global, name);
      Putchar(global, '\"');
    }
  }
  Putchar(global, '\n');
  global->wrongline = FALSE;
  return;
}

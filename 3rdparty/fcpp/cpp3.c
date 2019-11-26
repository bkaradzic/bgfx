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
#include <time.h> /*OIS*0.92*/

#include "cppdef.h"
#include "cpp.h"

ReturnCode fpp_openfile(struct Global *global, char *filename)
{
  /*
   * Open a file, add it to the linked list of open files.
   * This is called only from fpp_openfile() in cpp2.c.
   */

  FILE *fp;
  ReturnCode ret;

  if (global->openfile)
    fp = global->openfile(filename, "r", global->userdata);
  else
    fp = fopen(filename, "r");

  if (fp == NULL)
    ret=FPP_OPEN_ERROR;
  else
    ret=fpp_addfile(global, fp, filename);

  if(!ret && global->depends) {
	global->depends(filename, global->userdata);
  }

  if(!ret && global->showincluded) {
          /* no error occured! */
          fpp_Error(global, "cpp: included \"");
          fpp_Error(global, filename);
          fpp_Error(global, "\"\n");
  }
  return(ret);
}

ReturnCode fpp_addfile(struct Global *global,
                   FILE *fp,            /* Open file pointer */
                   char *filename)      /* Name of the file  */
{
  /*
   * Initialize tables for this open file.  This is called from fpp_openfile()
   * above (for #include files), and from the entry to cpp to open the main
   * input file. It calls a common routine, fpp_getfile() to build the FILEINFO
   * structure which is used to read characters. (fpp_getfile() is also called
   * to setup a macro replacement.)
   */

  FILEINFO *file;
  ReturnCode ret;

  ret = fpp_getfile(global, NBUFF, filename, &file);
  if(ret)
    return(ret);
  file->fp = fp;                        /* Better remember FILE *       */
  file->buffer[0] = EOS;                /* Initialize for first read    */
  global->line = 1;                     /* Working on line 1 now        */
  global->wrongline = FPP_TRUE;             /* Force out initial #line      */
  return(FPP_OK);
}

int fpp_dooptions(struct Global *global, struct fppTag *tags)
{
  /*
   * fpp_dooptions is called to process command line arguments (-Detc).
   * It is called only at cpp startup.
   */
  DEFBUF *dp;
  char end=FPP_FALSE; /* end of taglist */

  while(tags && !end) {
    switch(tags->tag) {
    case FPPTAG_END:
      end=FPP_TRUE;
      break;
    case FPPTAG_INITFUNC:
      global->initialfunc = (char *) tags->data;
      break;
    case FPPTAG_DISPLAYFUNCTIONS:
      global->outputfunctions = tags->data?1:0;
      break;
    case FPPTAG_RIGHTCONCAT:
      global->rightconcat = tags->data?1:0;
      break;
    case FPPTAG_OUTPUTMAIN:
      global->outputfile = tags->data?1:0;
      break;
    case FPPTAG_NESTED_COMMENTS:
      global->nestcomments = tags->data?1:0;
      break;
    case FPPTAG_WARNMISSINCLUDE:
      global->warnnoinclude = tags->data?1:0;
      break;
    case FPPTAG_WARN_NESTED_COMMENTS:
      global->warnnestcomments =  tags->data?1:0;
      break;
    case FPPTAG_OUTPUTSPACE:
      global->showspace = tags->data?1:0;
      break;
    case FPPTAG_OUTPUTBALANCE:
      global->showbalance = tags->data?1:0;
      break;
    case FPPTAG_OUTPUTINCLUDES:
      global->showincluded = tags->data?1:0;
      break;
    case FPPTAG_SHOWVERSION:
      global->showversion = tags->data?1:0;
      break;
    case FPPTAG_WARNILLEGALCPP:
      global->warnillegalcpp = tags->data?1:0;
      break;
    case FPPTAG_OUTPUTLINE:
      global->outputLINE = tags->data?1:0;
      break;
    case FPPTAG_KEEPCOMMENTS:
      if(tags->data) {
        global->cflag = FPP_TRUE;
        global->keepcomments = FPP_TRUE;
      }
      break;
    case FPPTAG_DEFINE:
      /*
       * If the option is just "-Dfoo", make it -Dfoo=1
       */
      {
        char *symbol=(char *)tags->data;
        char *text=symbol;
        while (*text != EOS && *text != '=')
          text++;
        if (*text == EOS)
          text = "1";
        else
          *text++ = EOS;
        /*
         * Now, save the word and its definition.
         */
        dp = fpp_defendel(global, symbol, FPP_FALSE);
        if(!dp)
          return(FPP_OUT_OF_MEMORY);
        dp->repl = fpp_savestring(global, text);
        dp->nargs = DEF_NOARGS;
      }
      break;
    case FPPTAG_IGNORE_NONFATAL:
      global->eflag = FPP_TRUE;
      break;
    case FPPTAG_INCLUDE_DIR:
      if (global->incend >= &global->incdir[NINCLUDE]) {
          fpp_cfatal(global, FATAL_TOO_MANY_INCLUDE_DIRS);
          return(FPP_TOO_MANY_INCLUDE_DIRS);
      }
      *global->incend++ = (char *)tags->data;
      break;
    case FPPTAG_INCLUDE_FILE:
    case FPPTAG_INCLUDE_MACRO_FILE:
      if (global->included >= NINCLUDE) {
          fpp_cfatal(global, FATAL_TOO_MANY_INCLUDE_FILES);
          return(FPP_TOO_MANY_INCLUDE_FILES);
      }
      global->include[(unsigned)global->included] = (char *)tags->data;

      global->includeshow[(unsigned)global->included] =
          (tags->tag == FPPTAG_INCLUDE_FILE);

      global->included++;
      break;
    case FPPTAG_BUILTINS:
      global->nflag|=(tags->data?NFLAG_BUILTIN:0);
      break;
    case FPPTAG_PREDEFINES:
      global->nflag|=(tags->data?NFLAG_PREDEFINE:0);
      break;
    case FPPTAG_IGNORE_CPLUSPLUS:
      global->cplusplus=!tags->data;
      break;
    case FPPTAG_SIZEOF_TABLE:
      {
        SIZES *sizp;    /* For -S               */
        int size;       /* For -S               */
        int isdatum;    /* FPP_FALSE for -S*        */
        int endtest;    /* For -S               */

        char *text=(char *)tags->data;

        sizp = size_table;
        if ((isdatum = (*text != '*'))) /* If it's just -S,     */
          endtest = T_FPTR;     /* Stop here            */
        else {                  /* But if it's -S*      */
          text++;               /* Step over '*'        */
          endtest = 0;          /* Stop at end marker   */
        }
        while (sizp->bits != endtest && *text != EOS) {
          if (!isdigit(*text)) {    /* Skip to next digit   */
            text++;
            continue;
          }
          size = 0;             /* Compile the value    */
          while (isdigit(*text)) {
            size *= 10;
            size += (*text++ - '0');
          }
          if (isdatum)
            sizp->size = size;  /* Datum size           */
          else
            sizp->psize = size; /* Pointer size         */
          sizp++;
        }
        if (sizp->bits != endtest)
          fpp_cwarn(global, WARN_TOO_FEW_VALUES_TO_SIZEOF, NULL);
        else if (*text != EOS)
          fpp_cwarn(global, WARN_TOO_MANY_VALUES_TO_SIZEOF, NULL);
      }
      break;
    case FPPTAG_UNDEFINE:
      if (fpp_defendel(global, (char *)tags->data, FPP_TRUE) == NULL)
        fpp_cwarn(global, WARN_NOT_DEFINED, tags->data);
      break;
    case FPPTAG_OUTPUT_DEFINES:
      global->wflag++;
      break;
    case FPPTAG_INPUT_NAME:
      strcpy(global->work, tags->data);    /* Remember input filename */
      global->first_file=tags->data;
      break;
	case FPPTAG_DEPENDS:
      global->depends=(void (*)(char *, void *))tags->data;
	  break;
    case FPPTAG_INPUT:
      global->input=(char *(*)(char *, int, void *))tags->data;
      break;
    case FPPTAG_OUTPUT:
      global->output=(void (*)(int, void *))tags->data;
      break;
    case FPPTAG_ERROR:
      global->error=(void (*)(void *, char *, va_list))tags->data;
      break;
    case FPPTAG_USERDATA:
      global->userdata=tags->data;
      break;
    case FPPTAG_LINE:
      global->linelines= tags->data?1:0;
      break;
    case FPPTAG_EXCLFUNC:
      global->excludedinit[ global->excluded++ ] = (char *)tags->data;
      break;
    case FPPTAG_WEBMODE:
      global->webmode=(tags->data?1:0);
      break;
    case FPPTAG_ALLOW_INCLUDE_LOCAL:
      global->allowincludelocal=(tags->data?1:0);
      break;
    case FPPTAG_FILEOPENFUNC:
      global->openfile = (FILE* (*)(char *,char *,void *))tags->data;
      break;
    default:
      fpp_cwarn(global, WARN_INTERNAL_ERROR, NULL);
      break;
    }
    tags++;
  }
  return(0);
}

ReturnCode fpp_initdefines(struct Global *global)
{
  /*
   * Initialize the built-in #define's.  There are two flavors:
   *    #define decus   1               (static definitions)
   *    #define __FILE__ ??             (dynamic, evaluated by magic)
   * Called only on cpp startup.
   *
   * Note: the built-in static definitions are supressed by the -N option.
   * __LINE__, __FILE__, __TIME__ and __DATE__ are always present.
   */

  char **pp;
  char *tp;
  DEFBUF *dp;
  struct tm *tm;

  int i;
  time_t tvec;

  static char months[12][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

  /*
   * Predefine the built-in symbols.  Allow the
   * implementor to pre-define a symbol as "" to
   * eliminate it.
   */
  if (!(global->nflag & NFLAG_BUILTIN)) {
    for (pp = global->preset; *pp != NULL; pp++) {
      if (*pp[0] != EOS) {
        dp = fpp_defendel(global, *pp, FPP_FALSE);
        if(!dp)
          return(FPP_OUT_OF_MEMORY);
        dp->repl = fpp_savestring(global, "1");
        dp->nargs = DEF_NOARGS;
      }
    }
  }
  /*
   * The magic pre-defines (__FILE__ and __LINE__ are
   * initialized with negative argument counts.  fpp_expand()
   * notices this and calls the appropriate routine.
   * DEF_NOARGS is one greater than the first "magic" definition.
   */
  if (!(global->nflag & NFLAG_PREDEFINE)) {
    for (pp = global->magic, i = DEF_NOARGS; *pp != NULL; pp++) {
      dp = fpp_defendel(global, *pp, FPP_FALSE);
      if(!dp)
        return(FPP_OUT_OF_MEMORY);
      dp->nargs = --i;
    }
#if OK_DATE
    /*
     * Define __DATE__ as today's date.
     */
    dp = fpp_defendel(global, "__DATE__", FPP_FALSE);
    tp = malloc(32);
    if(!tp || !dp)
      return(FPP_OUT_OF_MEMORY);
    dp->repl = tp;
    dp->nargs = DEF_NOARGS;
    time(&tvec);
    tm = localtime(&tvec);
    sprintf(tp, "\"%3s %2d %4d\"",      /* "Aug 20 1988" */
            months[tm->tm_mon],
            tm->tm_mday,
            tm->tm_year + 1900);

    /*
     * Define __TIME__ as this moment's time.
     */
    dp = fpp_defendel(global, "__TIME__", FPP_FALSE);
    tp = malloc(11);
    if(!tp || !dp)
      return(FPP_OUT_OF_MEMORY);
    dp->repl = tp;
    dp->nargs = DEF_NOARGS;
    sprintf(tp, "\"%2d:%02d:%02d\"",    /* "20:42:31" */
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec);
#endif
  }
  return(FPP_OK);
}

void fpp_delbuiltindefines(struct Global *global)
{
  /*
   * Delete the built-in #define's.
   */
  char **pp;


  /*
   * Delete the built-in symbols, unless -WW.
   */
  if (global->wflag < 2) {
    for (pp = global->preset; *pp != NULL; pp++) {
      fpp_defendel(global, *pp, FPP_TRUE);
    }
  }
  /*
   * The magic pre-defines __FILE__ and __LINE__
   */
  for (pp = global->magic; *pp != NULL; pp++) {
    fpp_defendel(global, *pp, FPP_TRUE);
  }
#if OK_DATE
  /*
   * Undefine __DATE__.
   */
  fpp_defendel(global, "__DATE__", FPP_TRUE);

  /*
   * Undefine __TIME__.
   */
  fpp_defendel(global, "__TIME__", FPP_TRUE);
#endif
  return;
}


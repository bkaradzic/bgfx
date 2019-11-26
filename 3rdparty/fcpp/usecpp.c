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
/******************************************************************************
 *                               FREXXWARE
 * ----------------------------------------------------------------------------
 *
 * Project: Frexx C Preprocessor
 * $Source: /home/user/start/cpp/RCS/usecpp.c,v $
 * $Revision: 1.6 $
 * $Date: 1994/06/02 09:11:01 $
 * $Author: start $
 * $State: Exp $
 * $Locker: start $
 *
 * ----------------------------------------------------------------------------
 * $Log: usecpp.c,v $
 * Revision 1.6  1994/06/02  09:11:01  start
 * Added the '-n' option!
 *
 * Revision 1.5  1994/06/02  08:51:49  start
 * Added three more command line parameters
 * Made -h invokes exit nice
 *
 * Revision 1.4  1994/01/24  09:37:17  start
 * Major difference.
 *
 * Revision 1.3  1993/12/06  13:51:20  start
 * A lot of new stuff (too much to mention)
 *
 * Revision 1.2  1993/11/11  07:16:39  start
 * New stuff
 *
 * Revision 1.1  1993/11/03  09:13:08  start
 * Initial revision
 *
 *
 *****************************************************************************/
/**********************************************************************
 *
 * usecpp.c
 *
 * This is a routine that is should be used to call functions in the
 * fpp.library. We supply the own_input() and own_output() functions to
 * the preprocessor to remain flexible.
 */

#include <stdlib.h>

#ifdef AMIGA
#include <proto/exec.h>
#include <exec/types.h>

#if defined(SHARED)
#include <exec/libraries.h>
#include <libraries/dos.h>

#include "fpp_pragmas.h"
#include "fpp_protos.h"
#include "FPPBase.h"
struct Library *FPPBase=NULL;
#define PREFIX __saveds
#define REG(x) register __ ## x
#else
#define PREFIX
#define REG(x)
#endif

#elif defined(UNIX)
#if defined(OS9)
#include <types.h>
#else
#include <sys/types.h>
#ifdef BSD
#include <sys/unistd.h> /* for BSD systems (SUN OS at least) */
#endif
#endif
#define PREFIX
#define REG(x)
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef OS9
#include <stdarg.h>
#else
#define va_list void *
#endif

#include "fpp.h"
#define MAX_TAGS 40 /* maximum number of tags allowed! */
#define FILE_LOCAL static

#define CPP_PREFS_FILE "cpp.prefs"
#ifdef AMIGA
#define DEFAULT_CPP_PREFS_FILE "s:cpp.prefs"
#else
#define DEFAULT_CPP_PREFS_FILE "$HOME/cpp.prefs"
#endif

FILE_LOCAL char PREFIX *own_input(char *, int, void *);
FILE_LOCAL void PREFIX own_output(int, void *);
FILE_LOCAL void PREFIX own_error(void *, char *, va_list);
FILE_LOCAL int SetOptions(int, char **, struct fppTag **);
FILE_LOCAL char GetPrefs(struct fppTag **, char **);
FILE_LOCAL char DoString(struct fppTag **, char *);

#ifdef AMIGA
extern long __stack=8000;
#endif

FILE_LOCAL char ignore=FPP_FALSE;  /* if we should ignore strange flags! */
FILE_LOCAL char display=FPP_FALSE; /* display all options in use! */

FILE_LOCAL char dontreadprefs; /* set if only the command line is valid */

int main(int argc, char **argv)
{
  struct fppTag tags[MAX_TAGS];
  int i;
  struct fppTag *tagptr = tags;
  char *dealloc;

  /*
   * Append system-specific directories to the include directory list.
   * The include directories will be searched through in the same order
   * as you add them in the taglist!
   * The directory _must_ end with a proper directory speparator!
   */  

  tagptr->tag=FPPTAG_INCLUDE_DIR;
#if defined (AMIGA)
  tagptr->data = "INCLUDE:";
#elif defined (OS9)
  tagptr->data = "/dd/defs/";
#else
  tagptr->data = "/usr/include/";
#endif
  tagptr++;

  if(GetPrefs(&tagptr, &dealloc))
    return(0);

  if( !(i = SetOptions(argc, argv, &tagptr)))
    return(0);
  
  if (argc - i >2) {
    printf("Too many file arguments. Usage: cpp [options] [input [output]]\n");
    return(-1);
  }

  tagptr->tag=FPPTAG_INPUT;
  tagptr->data=(void *)own_input;
  tagptr++;

  if(i<argc) {
    /*
     * Open input file, "-" means use stdin.
     */
    if (strcmp(argv[i], "-")) {
      if (freopen(argv[i], "r", stdin) == NULL) {
	perror(argv[i]);
	fprintf(stderr, "Can't open input file \"%s\"", argv[i]);
	return(-2);
      }
      tagptr->tag=FPPTAG_INPUT_NAME;
      tagptr->data=argv[i];
      tagptr++;
      if(display)
	fprintf(stderr, "cpp: input: %s\n", argv[i]);
    } else				/* Else, just get stdin 	*/
      if(display)
	fprintf(stderr, "cpp: input: [stdin]\n");
    i++;
  } else
    if(display)
      fprintf(stderr, "cpp: input: [stdin]\n");

  if(i<argc) {
    /*
     * Get output file, "-" means use stdout.
     */
    if (strcmp(argv[i], "-")) {
      if (freopen(argv[i], "w", stdout) == NULL) {
	perror(argv[i]);
	fprintf(stderr, "Can't open output file \"%s\"", argv[i]);
	return(-1);
      }
      if(display)
	fprintf(stderr, "cpp: output: %s\n", argv[i]);
    } else
      if(display)
	fprintf(stderr, "cpp: output: [stdout]\n");
  } else
    if(display)
      fprintf(stderr, "cpp: output: [stdout]\n");

  tagptr->tag=FPPTAG_OUTPUT;
  tagptr->data=(void *)own_output;
  tagptr++;

  tagptr->tag=FPPTAG_ERROR;
  tagptr->data=(void *)own_error;
  tagptr++;

  /* The LAST tag: */

  tagptr->tag=FPPTAG_END;
  tagptr->data=0;
  tagptr++;

#if defined(SHARED) && defined(AMIGA)
  if(!(FPPBase=OpenLibrary(FPPNAME, 1))) {
    printf("Error opening %s!\n", FPPNAME);
    return(-1);
  }
#endif
  fppPreProcess(tags);

#if defined(SHARED) && defined(AMIGA)
  CloseLibrary((struct Library *)FPPBase);
#endif
  /*
   * Preprocess ready!
   */

  if( dealloc )
    free( dealloc );

  return(0);
}


FILE_LOCAL
char PREFIX *own_input(char *buffer, int size, void *userdata)
{
  return(fgets(buffer, size, stdin));
}

FILE_LOCAL
void PREFIX own_output(int c, void *userdata)
{
  putchar(c);
}

FILE_LOCAL
void PREFIX own_error(void *userdata, char *format, va_list arg)
{
  vfprintf(stderr, format, arg);
}

FILE_LOCAL
char GetPrefs(struct fppTag **tagptr, char **string)
{
  
  FILE     *PrefsFile_PF;
  unsigned  Length_U;
  char     *PrefsBuffer_PC;
  char ret= 0;
  char *env;

  *string = NULL;

  /* Open prefs file for read */
  if ( (PrefsFile_PF = fopen(CPP_PREFS_FILE, "r")) ||
      (PrefsFile_PF = fopen(DEFAULT_CPP_PREFS_FILE, "r"))) {
    
    fseek(PrefsFile_PF, 0 , SEEK_END);
    Length_U = ftell(PrefsFile_PF);
    fseek(PrefsFile_PF, 0, SEEK_SET);

    if (*string = (char *)malloc(Length_U+1)) {
      fread(*string, 1, Length_U, PrefsFile_PF);
      (*string)[Length_U] = '\0';
      
      ret = !DoString(tagptr, *string);
    }
    fclose(PrefsFile_PF);
    if(ret) {
      free( *string );
      return ret;
    }
  }

  if((env = getenv("CPP_PREFS"))) {
    ret= !DoString(tagptr, env);
    if(ret && *string)
      free( *string );
  }
  return ret;
}

FILE_LOCAL
char DoString(struct fppTag **tagptr, char *string)
{
  char     *argv[MAX_TAGS];
  int      argc=1;
  do {
    while(*string && *string != '-')
      string++;

    if(!*string)
      break;

    argv[argc]=string;

    do {
      string++;
      if(*string=='\"') {
	do
	  string++;
	while(*string != '\"');
	string++;
      }
    } while(*string && *string!=' ' && *string != '\n' && *string != '\t');
    argc++;
    if(*string) {
      *string='\0';
      string++;
    } else
      break;
  } while(1);

  return (SetOptions(argc, argv, tagptr));
}

FILE_LOCAL
int SetOptions(int argc, char **argv, struct fppTag **tagptr)
{
  int i;
  char *ap;
  for (i = 1; i < argc; i++) {
    ap = argv[i];
    if (*ap++ != '-' || *ap == '\0')
      break;
    else {
      char c = *ap++;

      if(display)
	fprintf(stderr, "cpp: option: %s\n", ap-2);

      switch (c) {                    /* Command character    */
      case 'Q':			      /* ignore unknown flags but */
	ignore=1;		      /* output them on stderr */
	break;

      case 'q':			      /* ignore unknown flags */
	ignore=2;
	break;

      case 'H':			      /* display all whitespaces */
	(*tagptr)->tag = FPPTAG_OUTPUTSPACE;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
	break;

      case 'b': 		      /* display unbalance */
	(*tagptr)->tag = FPPTAG_OUTPUTBALANCE;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
	break;

      case 'f':			      /* output all defined functions! */
	(*tagptr)->tag = FPPTAG_DISPLAYFUNCTIONS;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
        break;

      case 'F':			      /* output all included files! */
	(*tagptr)->tag = FPPTAG_OUTPUTINCLUDES;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
        break;

      case 'V':			      /* do not output version */
	(*tagptr)->tag = FPPTAG_SHOWVERSION;
	(*tagptr)->data= (void *)FPP_FALSE;
	(*tagptr)++;
	break;

      case 'C':                       /* Keep comments */
	(*tagptr)->tag = FPPTAG_KEEPCOMMENTS;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
	break;
	
      case 'D':                       /* Define symbol */
	(*tagptr)->tag=FPPTAG_DEFINE;
	(*tagptr)->data=argv[i]+2;
	(*tagptr)++;
	break;

      case 'd':                       /* Display all options */
	fprintf(stderr, "FOUND -d flag!\n");
	display = FPP_TRUE;
	break;
	
      case 'E':                       /* Ignore non-fatal errors */
	(*tagptr)->tag=FPPTAG_IGNORE_NONFATAL;
	(*tagptr)->data=(void *)FPP_TRUE;
	(*tagptr)++;
	break;
	
      case 'I':                       /* Include directory */
	(*tagptr)->tag=FPPTAG_INCLUDE_DIR;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 'J':                       /* Allow nested comments */
	(*tagptr)->tag=FPPTAG_NESTED_COMMENTS;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 'j':                       /* Warn at nested comments */
	(*tagptr)->tag=FPPTAG_WARN_NESTED_COMMENTS;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 'L':
	if(*ap == 'L') {	      /* Do not output #line */
	  (*tagptr)->tag=FPPTAG_LINE;
	} else {
	  /* Do not output the 'line' keyword */
	  (*tagptr)->tag=FPPTAG_OUTPUTLINE;
	}
	(*tagptr)->data=(void *)FPP_FALSE;
	(*tagptr)++;
	break;

      case 'M':                       /* Do not warn at missing includes */
	(*tagptr)->tag=FPPTAG_WARNMISSINCLUDE;
	(*tagptr)->data=(void *)FPP_FALSE;
	(*tagptr)++;
	break;

      case 'n':
        dontreadprefs^=1; /* toggle prefsreading, default is read prefs */

	/*
	 * This flag should reset all previously added tags!
	 */

        break;

      case 'N':                       /* No machine specific built-ins */
	(*tagptr)->tag=FPPTAG_BUILTINS;
	(*tagptr)->data=(void *)FPP_FALSE;
	(*tagptr)++;
	break;

      case 'B':			      /* No predefines like __LINE__, etc. */
	(*tagptr)->tag=FPPTAG_PREDEFINES;
	(*tagptr)->data=(void *)FPP_FALSE;
	(*tagptr)++;
	break;
	
      case 'P':			      /* No C++ comments */
	(*tagptr)->tag=FPPTAG_IGNORE_CPLUSPLUS;
	(*tagptr)->data=(void *)FPP_TRUE;
	(*tagptr)++;
	break;
	
      case 'p':			      /* warn about illegal # - instructions */
	(*tagptr)->tag = FPPTAG_WARNILLEGALCPP;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
	break;

      case 'R':
	(*tagptr)->tag = FPPTAG_RIGHTCONCAT;
	(*tagptr)->data= (void *)FPP_TRUE;
	(*tagptr)++;
	break;

      case 's':			      /* sizeof table */
	(*tagptr)->tag=FPPTAG_INITFUNC;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 't':			      /* excluded functions */
	(*tagptr)->tag=FPPTAG_EXCLFUNC;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 'S':			      /* sizeof table */
	(*tagptr)->tag=FPPTAG_SIZEOF_TABLE;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;
	
      case 'U':                       /* Undefine symbol */
	(*tagptr)->tag=FPPTAG_UNDEFINE;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;

      case 'w':			      /* Output all #defines but not the
					 main file */
	(*tagptr)->tag=FPPTAG_OUTPUTMAIN;
	(*tagptr)->data=(void *)FPP_FALSE;
	(*tagptr)++;
	
      case 'W':			      /* Output all #defines */
        if(!strncmp(ap, "WW", 2)) {
          (*tagptr)->tag=FPPTAG_WEBMODE;
          (*tagptr)->data=(void *)FPP_TRUE;
          (*tagptr)++;
        }
        else {
          (*tagptr)->tag=FPPTAG_OUTPUT_DEFINES;
          (*tagptr)->data=(void *)FPP_TRUE;
          (*tagptr)++;
        }
	break;

      case 'X':
	(*tagptr)->tag=FPPTAG_INCLUDE_FILE;
	(*tagptr)->data=ap;
	(*tagptr)++;
	break;

/*
      case 'x':
	tags[tag]->tag=FPPTAG_INCLUDE_MACRO_FILE;
	tags[tag++]->data=ap;
	break;
*/
      case 'h':
      case '?': /* if a question mark is possible to specify! */
      default:			/* What is this one?	*/
	if( ignore < 2 && c != 'h') {
	  fprintf(stderr, "cpp: unknown option: -%s\n", ap-1);
	}
	if(!ignore || c == 'h') {
	  fprintf(stderr,
		  "Usage: cpp [options] [infile [outfile] ]\n\n"
		  "The following options are valid:\n"
		  "  -B\tNo machine specific built-in symbols\n"
		  "  -b\tOutput any parentheses, brace or bracket unbalance\n"
		  "  -C\tWrite source file comments to output\n"
		  "  -D\tDefine a symbol with the given (optional) value \"symbol[=value]\"\n"
		  "  -d\tDisplay all specified options\n"
		  "  -E\tIgnore non-fatal errors\n"
		  "  -F\tOutput all included file names on stderr\n"
		  "  -f\tOutput all defined functions' names on stderr\n"
		  "  -H\tOutput all whitespaces from the source file\n"
		  "  -h\tOutput this help text\n"
		  "  -I\tAdd directory to the #include search list\n"
		  "  -J\tAllow nested comments\n"
		  "  -j\tEnable warnings for nested comments\n"
		  "  -LL\tDon't output #line instructions\n"
		  "  -L\tDon't output the 'line' keyword in \"#line\" instructions\n"
		  "  -M\tDon't warn for missing include files\n"
		  "  -N\tDon't predefine target-specific names\n"
		  "  -n\tToggle prefs usage\n"
		  "  -P\tDon't recognize C++ comment style\n"
		  "  -p\tEnable warnings on non ANSI preprocessor instructions\n"
		  "  -Q\tIgnore but visualize undefined flags\n"
		  "  -q\tIgnore all undefined flags\n"
		  "  -R\tEvaluate the right part first in symbol concatenations\n"
		  "  -s\tInclude the following string at the top of each function\n"
		  "  -S\tSpecify sizes for #if sizeof\n"
		  "  -t\tThis function should not get an initial function\n"
		  "  -U\tUndefine symbol\n"
		  "  -V\tDon't output version information\n"
		  "  -W\tOutput all #defines\n"
                  "  -WWW\tWeb mode preprocessing\n"
		  "  -w\tOnly output #defines\n"
		  "  -X\tInclude file\n");
	  return(0);
	}	/* if (!ignore) */
      }		/* Switch on all options	*/
    }		/* If it's a -option            */
  }		/* For all arguments		*/

  return i;

} /* end of function */

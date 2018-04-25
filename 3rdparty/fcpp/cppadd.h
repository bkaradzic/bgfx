/******************************************************************************
 *                               FREXXWARE
 * ----------------------------------------------------------------------------
 *
 * Project: Frexx C Preprocessor
 * $Source: /home/user/start/cpp/RCS/cppadd.h,v $
 * $Revision: 1.5 $
 * $Date: 1994/01/24 09:38:12 $
 * $Author: start $
 * $State: Exp $
 * $Locker: start $
 *
 * ----------------------------------------------------------------------------
 * $Log: cppadd.h,v $
 * Revision 1.5  1994/01/24  09:38:12  start
 * Added the 'rightconcat' in the global structure.
 *
 * Revision 1.4  1993/12/06  13:51:20  start
 * A lot of new stuff (too much to mention)
 *
 * Revision 1.3  1993/11/29  14:01:13  start
 * New features added
 *
 * Revision 1.2  1993/11/11  07:16:39  start
 * New stuff
 *
 * Revision 1.1  1993/11/03  09:15:59  start
 * Initial revision
 *
 *
 *****************************************************************************/
/**********************************************************************
 *
 * cppadd.h
 *
 * Prototypes and structures added by Daniel Stenberg.
 *
 *******/

#include <stdarg.h>
#include "memory.h"

struct Global {

  /*
   * Commonly used global variables:
   * line       is the current input line number.
   * wrongline  is set in many places when the actual output
   *            line is out of sync with the numbering, e.g,
   *            when expanding a macro with an embedded newline.
   *
   * tokenbuf   holds the last identifier scanned (which might
   *            be a candidate for macro expansion).
   * errors     is the running cpp error counter.
   * infile     is the head of a linked list of input files (extended by
   *            #include and macros being expanded).  infile always points
   *            to the current file/macro.  infile->parent to the includer,
   *            etc.  infile->fd is NULL if this input stream is a macro.
   */
  int           line;                   /* Current line number          */
  int           wrongline;              /* Force #line to compiler      */
  char          *tokenbuf;              /* Buffer for current input token */
  char      *functionname;  /* Buffer for current function */
  int       funcline;       /* Line number of current function */
  int           tokenbsize;             /* Allocated size of tokenbuf,  */
                                        /* not counting zero at end.    */
  int           errors;                 /* cpp error counter            */
  FILEINFO      *infile;                /* Current input file           */
#if DEBUG
  int           debug;                  /* FPP_TRUE if debugging now        */
#endif
  /*
   * This counter is incremented when a macro expansion is initiated.
   * If it exceeds a built-in value, the expansion stops -- this tests
   * for a runaway condition:
   *    #define X Y
   *    #define Y X
   *    X
   * This can be disabled by falsifying rec_recover.  (Nothing does this
   * currently: it is a hook for an eventual invocation flag.)
   */
  int           recursion;              /* Infinite recursion counter   */
  int           rec_recover;            /* Unwind recursive macros      */

  /*
   * instring is set FPP_TRUE when a string is scanned.  It modifies the
   * behavior of the "get next character" routine, causing all characters
   * to be passed to the caller (except <DEF_MAGIC>).  Note especially that
   * comments and \<newline> are not removed from the source.  (This
   * prevents cpp output lines from being arbitrarily long).
   *
   * inmacro is set by #define -- it absorbs comments and converts
   * form-feed and vertical-tab to space, but returns \<newline>
   * to the caller.  Strictly speaking, this is a bug as \<newline>
   * shouldn't delimit tokens, but we'll worry about that some other
   * time -- it is more important to prevent infinitly long output lines.
   *
   * instring and inmarcor are parameters to the fpp_get() routine which
   * were made global for speed.
   */
  int           instring;       /* FPP_TRUE if scanning string      */
  int           inmacro;        /* FPP_TRUE if #defining a macro    */
  
  /*
   * work[] and workp are used to store one piece of text in a temporay
   * buffer.  To initialize storage, set workp = work.  To store one
   * character, call fpp_save(c);  (This will fatally exit if there isn't
   * room.)  To terminate the string, call fpp_save(EOS).  Note that
   * the work buffer is used by several subroutines -- be sure your
   * data won't be overwritten.  The extra byte in the allocation is
   * needed for string formal replacement.
   */
  char          work[NWORK + 1];        /* Work buffer                  */
  char          *workp;                 /* Work buffer pointer          */

  /*
   * keepcomments is set FPP_TRUE by the -C option.  If FPP_TRUE, comments
   * are written directly to the output stream.  This is needed if
   * the output from cpp is to be passed to lint (which uses commands
   * embedded in comments).  cflag contains the permanent state of the
   * -C flag.  keepcomments is always falsified when processing #control
   * commands and when compilation is supressed by a false #if
   *
   * If eflag is set, CPP returns "success" even if non-fatal errors
   * were detected.
   *
   * If nflag is non-zero, no symbols are predefined except __LINE__.
   * __FILE__, and __DATE__.  If nflag > 1, absolutely no symbols
   * are predefined.
   */
  char          keepcomments;   /* Write out comments flag      */
  char          cflag;          /* -C option (keep comments)    */
  char          eflag;          /* -E option (never fail)       */
  char          nflag;          /* -N option (no predefines)    */
  char          wflag;          /* -W option (write #defines)   */

  /*
   * ifstack[] holds information about nested #if's.  It is always
   * accessed via *ifptr.  The information is as follows:
   *    WAS_COMPILING   state of compiling flag at outer level.
   *    ELSE_SEEN       set FPP_TRUE when #else seen to prevent 2nd #else.
   *    FPP_TRUE_SEEN       set FPP_TRUE when #if or #elif succeeds
   * ifstack[0] holds the compiling flag.  It is FPP_TRUE if compilation
   * is currently enabled.  Note that this must be initialized FPP_TRUE.
   */
  char          ifstack[BLK_NEST];      /* #if information      */
  char          *ifptr;                 /* -> current ifstack[] */

  /*
   * incdir[] stores the -i directories (and the system-specific
   * #include <...> directories.
   */
  char  *incdir[NINCLUDE];              /* -i directories               */
  char  **incend;                       /* -> free space in incdir[]    */

  /*
   * include[] stores the -X and -x files.
   */
  char  *include[NINCLUDE];
  char  includeshow[NINCLUDE]; /* show it or not! */
  unsigned  included;

  /*
   * This is the table used to predefine target machine and operating
   * system designators.        It may need hacking for specific circumstances.
   * Note: it is not clear that this is part of the Ansi Standard.
   * The -B option supresses preset definitions.
   */
  char  *preset[5];                     /* names defined at cpp start   */

  /*
   * The value of these predefined symbols must be recomputed whenever
   * they are evaluated.        The order must not be changed.
   */
  char  *magic[5];                      /* Note: order is important     */

  /*
   * This is the variable saying if Cpp should remove C++ style comments from
   * the output. Default is... FPP_TRUE, yes, pronto, do it!!!
   */
  
  char cplusplus;

  char *sharpfilename;


  /*
   * parm[], parmp, and parlist[] are used to store #define() argument
   * lists.  nargs contains the actual number of parameters stored.
   */
  char  parm[NPARMWORK + 1];    /* define param work buffer     */
  char  *parmp;                 /* Free space in parm           */
  char  *parlist[LASTPARM];     /* -> start of each parameter   */
  int   nargs;                  /* Parameters for this macro    */

  DEFBUF *macro;                /* Catches start of infinite macro      */

  DEFBUF *symtab[SBSIZE];       /* Symbol table queue headers   */

  int evalue;                   /* Current value from fpp_evallex() */

  void (*depends)(char *filename, void *); /* depends function */

  char *(*input)(char *, int, void *);  /* Input function */

  char *first_file;             /* Preprocessed file. */

  void *userdata;               /* Data sent to input function */

  void (*output)(int, void *);  /* output function */

  void (*error)(void *, char *, va_list);       /* error function */

  char linelines;

  char warnillegalcpp; /* warn for illegal preprocessor instructions? */

  char outputLINE;   /* output 'line' in #line instructions */

  char showversion;  /* display version */

  char showincluded; /* display included files */

  char showbalance; /* display paren balance */

  char showspace;   /* display all whitespaces as they are */

  char comment;     /* FPP_TRUE if a comment just has been written to output */

  char *spacebuf;    /* Buffer to store whitespaces in if -H */

  long chpos;       /* Number of whitespaces in buffer */

  char nestcomments; /* Allow nested comments */

  char warnnestcomments; /* Warn at nested comments */

  char warnnoinclude; /* Warn at missing include file */

  char outputfile; /* output the main file */

  char out; /* should we output anything now? */

  char rightconcat; /* should the right part of a concatenation be avaluated
					   before the concat (FPP_TRUE) or after (FPP_FALSE) */
  char *initialfunc; /* file to include first in all functions */

  char *excludedinit[20]; /* functions (names) excluded from the initfunc */
  int excluded;

  char outputfunctions;  /* output all discovered functions to stderr! */

  char webmode; /* WWW process mode */

  char allowincludelocal;

  FILE* (*openfile)(char *,char *, void *);
};

typedef enum {
  ERROR_STRING_MUST_BE_IF,
  ERROR_STRING_MAY_NOT_FOLLOW_ELSE,
  ERROR_ERROR,
  ERROR_PREPROC_FAILURE,
  ERROR_MISSING_ARGUMENT,
  ERROR_INCLUDE_SYNTAX,
  ERROR_DEFINE_SYNTAX,
  ERROR_REDEFINE,
  ERROR_ILLEGAL_UNDEF,
  ERROR_RECURSIVE_MACRO,
  ERROR_EOF_IN_ARGUMENT,
  ERROR_MISPLACED_CONSTANT,
  ERROR_IF_OVERFLOW,
  ERROR_ILLEGAL_IF_LINE,
  ERROR_OPERATOR,
  ERROR_EXPR_OVERFLOW,
  ERROR_UNBALANCED_PARENS,
  ERROR_MISPLACED,
  ERROR_STRING_IN_IF,
  ERROR_DEFINED_SYNTAX,
  ERROR_ILLEGAL_ASSIGN,
  ERROR_ILLEGAL_BACKSLASH,
  ERROR_SIZEOF_SYNTAX,
  ERROR_SIZEOF_UNKNOWN,
  ERROR_SIZEOF_ILLEGAL_TYPE,
  ERROR_SIZEOF_NO_TYPE,
  ERROR_UNTERMINATED_STRING,
  ERROR_EOF_IN_COMMENT,
  ERROR_IFDEF_DEPTH,
  ERROR_ILLEGAL_CHARACTER,
  ERROR_ILLEGAL_CHARACTER2,
  ERROR_SIZEOF_BUG,
  ERROR_IF_OPERAND,
  ERROR_STRANG_CHARACTER,
  ERROR_STRANG_CHARACTER2,

  BORDER_ERROR_WARN, /* below this number: errors, above: warnings */

  WARN_CONTROL_LINE_IN_MACRO,
  WARN_ILLEGAL_COMMAND,
  WARN_UNEXPECTED_TEXT_IGNORED,
  WARN_TOO_FEW_VALUES_TO_SIZEOF,
  WARN_TOO_MANY_VALUES_TO_SIZEOF,
  WARN_NOT_DEFINED,
  WARN_INTERNAL_ERROR,
  WARN_MACRO_NEEDS_ARGUMENTS,
  WARN_WRONG_NUMBER_ARGUMENTS,
  WARN_DIVISION_BY_ZERO,
  WARN_ILLEGAL_OCTAL,
  WARN_MULTIBYTE_NOT_PORTABLE,
  WARN_CANNOT_OPEN_INCLUDE,
  WARN_BRACKET_DEPTH,
  WARN_PAREN_DEPTH,
  WARN_BRACE_DEPTH,
  WARN_NESTED_COMMENT,

  BORDER_WARN_FATAL, /* below this number: warnings, above: fatals */

  FATAL_TOO_MANY_NESTINGS,
  FATAL_FILENAME_BUFFER_OVERFLOW,
  FATAL_TOO_MANY_INCLUDE_DIRS,
  FATAL_TOO_MANY_INCLUDE_FILES,
  FATAL_TOO_MANY_ARGUMENTS_MACRO,
  FATAL_MACRO_AREA_OVERFLOW,
  FATAL_ILLEGAL_MACRO,
  FATAL_TOO_MANY_ARGUMENTS_EXPANSION,
  FATAL_OUT_OF_SPACE_IN_ARGUMENT,
  FATAL_WORK_AREA_OVERFLOW,
  FATAL_WORK_BUFFER_OVERFLOW,
  FATAL_OUT_OF_MEMORY,
  FATAL_TOO_MUCH_PUSHBACK


  } ErrorCode;

/**********************************************************************
 * RETURN CODES:
 *********************************************************************/

typedef enum {
  FPP_OK,
  FPP_OUT_OF_MEMORY,
  FPP_TOO_MANY_NESTED_STATEMENTS,
  FPP_FILENAME_BUFFER_OVERFLOW,
  FPP_NO_INCLUDE,
  FPP_OPEN_ERROR,
  FPP_TOO_MANY_ARGUMENTS,
  FPP_WORK_AREA_OVERFLOW,
  FPP_ILLEGAL_MACRO,
  FPP_EOF_IN_MACRO,
  FPP_OUT_OF_SPACE_IN_MACRO_EXPANSION,
  FPP_ILLEGAL_CHARACTER,
  FPP_CANT_USE_STRING_IN_IF,
  FPP_BAD_IF_DEFINED_SYNTAX,
  FPP_IF_ERROR,
  FPP_SIZEOF_ERROR,
  FPP_UNTERMINATED_STRING,
  FPP_TOO_MANY_INCLUDE_DIRS,
  FPP_TOO_MANY_INCLUDE_FILES,
  FPP_INTERNAL_ERROR,

  FPP_LAST_ERROR
} ReturnCode;

/* Nasty defines to make them appear as three different functions! */
#define fpp_cwarn fpp_cerror
#define fpp_cfatal fpp_cerror 


/**********************************************************************
 * PROTOTYPES:
 *********************************************************************/
int PREFIX fppPreProcess(REG(a0) struct fppTag *);
void fpp_Freemem(void *);
void fpp_Error(struct Global *, char *, ...);
void fpp_Putchar(struct Global *, int);
void fpp_Putstring(struct Global *, char *);
void fpp_Putint(struct Global *, int);
char *fpp_savestring(struct Global *, char *);
ReturnCode fpp_addfile(struct Global *, FILE *, char *);
int fpp_catenate(struct Global *, int lhs_number, ReturnCode *);
void fpp_cerror(struct Global *, ErrorCode, ...);
ReturnCode fpp_control(struct Global *, int *);
ReturnCode fpp_dodefine(struct Global *);
int fpp_dooptions(struct Global *, struct fppTag *);
void fpp_doundef(struct Global *);
void fpp_dumpparm(char *);
ReturnCode fpp_expand(struct Global *, DEFBUF *);
int fpp_get(struct Global *);
ReturnCode fpp_initdefines(struct Global *);
void fpp_outdefines(struct Global *);
ReturnCode fpp_save(struct Global *, int);
void fpp_scanid(struct Global *, int);
ReturnCode fpp_scannumber(struct Global *, int, ReturnCode(*)(struct Global *, int));
ReturnCode fpp_scanstring(struct Global *, int, ReturnCode(*)(struct Global *, int));
void fpp_unget(struct Global *);
ReturnCode fpp_ungetstring(struct Global *, char *);
ReturnCode fpp_eval(struct Global *, int *);
#ifdef  DEBUG_EVAL
void fpp_dumpstack(OPTAB[NEXP], register OPTAB *, int [NEXP], register int *);
#endif
void fpp_skipnl(struct Global *);
int fpp_skipws(struct Global *);
ReturnCode fpp_macroid(struct Global *, int *);
ReturnCode fpp_getfile(struct Global *, size_t, char *, FILEINFO **);
DEFBUF *fpp_lookid(struct Global *, int );
DEFBUF *fpp_defendel(struct Global *, char *, int);
#if DEBUG
void fpp_dumpdef(char *);
void fpp_dumpadef(char *, register DEFBUF *);
#endif
ReturnCode fpp_openfile(struct Global *,char *);
int fpp_cget(struct Global *);
void fpp_delbuiltindefines(struct Global *);
void fpp_delalldefines(struct Global *);
char *fpp_Getmem(struct Global *, int);
ReturnCode fpp_openinclude(struct Global *, char *, int);
ReturnCode fpp_expstuff(struct Global *, char *, char *);

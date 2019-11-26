/******************************************************************************
 *                               FREXXWARE
 * ----------------------------------------------------------------------------
 *
 * Project: Frexx C Preprocessor
 * $Source: /home/user/start/cpp/RCS/fpp.h,v $
 * $Revision: 1.5 $
 * $Date: 1994/01/24 09:38:45 $
 * $Author: start $
 * $State: Exp $
 * $Locker: start $
 *
 * ----------------------------------------------------------------------------
 * $Log: fpp.h,v $
 * Revision 1.5  1994/01/24  09:38:45  start
 * Added FPPTAG_RIGHTCONCAT.
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
 * fpp.h
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

struct fppTag {
  int tag;
  void *data;
};

#ifndef FPP_TRUE
#define FPP_TRUE 1
#endif

#ifndef FPP_FALSE
#define FPP_FALSE 0
#endif

#define NFLAG_BUILTIN   1
#define NFLAG_PREDEFINE 2

/* end of taglist: */
#define FPPTAG_END 0

/* To make the preprocessed output keep the comments: */
#define FPPTAG_KEEPCOMMENTS 1 /* data is FPP_TRUE or FPP_FALSE */

/* To define symbols to the preprocessor: */
#define FPPTAG_DEFINE 2 /* data is the string "symbol" or "symbol=<value>" */

/* To make the preprocessor ignore all non-fatal errors: */
#define FPPTAG_IGNORE_NONFATAL 3 /* data is FPP_TRUE or FPP_FALSE */

/* To add an include directory to the include directory list: */
#define FPPTAG_INCLUDE_DIR 4 /* data is directory name ending with a '/' (on
				amiga a ':' is also valid) */

/* To define all machine specific built-in #defines, default is FPP_TRUE: */
#define FPPTAG_BUILTINS 5 /* data is FPP_TRUE or FPP_FALSE */

/* To define predefines like __LINE__, __DATE__, etc. default is FPP_TRUE: */
#define FPPTAG_PREDEFINES 6 /* data is FPP_TRUE or FPP_FALSE */

/* To make fpp leave C++ comments in the output: */
#define FPPTAG_IGNORE_CPLUSPLUS 7 /* data is FPP_TRUE or FPP_FALSE */

/* To define new sizes to #if sizeof: */
#define FPPTAG_SIZEOF_TABLE 8 /* data is sizeof table string */

/* To undefine symbols: */
#define FPPTAG_UNDEFINE 9 /* data is symbol name */

/* Output all #defines: */
#define FPPTAG_OUTPUT_DEFINES 10 /* data is FPP_TRUE or FPP_FALSE */

/* Initial input file name: */
#define FPPTAG_INPUT_NAME 11 /* data is string */

/* Input function: */
#define FPPTAG_INPUT 12 /* data is an input funtion */

/* Output function: */
#define FPPTAG_OUTPUT 13 /* data is an output function */

/* User data, sent in the last argument to the input function: */
#define FPPTAG_USERDATA 14 /* data is user data */

/* Whether to exclude #line instructions in the output, default is FPP_FALSE */
#define FPPTAG_LINE 15 /* data is FPP_TRUE or FPP_FALSE */

/* Error function. This is called when FPP finds any warning/error/fatal: */
#define FPPTAG_ERROR 16 /* data is function pointer to a
			   "void (*)(void *, char *, va_list)" */

/* Whether to warn for illegal cpp instructions */
#define FPPTAG_WARNILLEGALCPP 17 /* data is boolean, default is FPP_FALSE */

/* Output the 'line' keyword on #line-lines? */
#define FPPTAG_OUTPUTLINE 18 /* data is boolean, default is FPP_TRUE */

/* Output the version information string */
#define FPPTAG_SHOWVERSION 19 /* data is boolean, default is FPP_TRUE */

/* Output all included file names to stderr */
#define FPPTAG_OUTPUTINCLUDES 20 /* data is boolean, default is FPP_FALSE */

/* Display warning if there is any brace, bracket or parentheses unbalance */
#define FPPTAG_OUTPUTBALANCE 21 /* data is boolean, default is FPP_FALSE */

/* Display all whitespaces in the source */
#define FPPTAG_OUTPUTSPACE 22 /* data is boolean, default is FPP_FALSE */

/* Allow nested comments */
#define FPPTAG_NESTED_COMMENTS 23 /* data is boolean, default is FPP_FALSE */

/* Enable warnings at nested comments */
#define FPPTAG_WARN_NESTED_COMMENTS 24 /* data is boolean, default is FPP_FALSE */

/* Enable warnings at missing includes */
#define FPPTAG_WARNMISSINCLUDE 25 /* data is boolean, default is FPP_TRUE */

/* Output the main file */
#define FPPTAG_OUTPUTMAIN 26 /* data is boolean, default is FPP_TRUE */

/* Include file */
#define FPPTAG_INCLUDE_FILE 27 /* data is char pointer */

/* Include macro file */
#define FPPTAG_INCLUDE_MACRO_FILE 28 /* data is char pointer */

/* Evaluate the right part of a concatenate before the concat */
#define FPPTAG_RIGHTCONCAT 29 /* data is boolean, default is FPP_FALSE */

/* Include the specified file at the beginning of each function */
#define FPPTAG_INITFUNC 30 /* data is char pointer or NULL */

/* Define function to be excluded from the "beginning-function-addings" */
#define FPPTAG_EXCLFUNC 31 /* data is char pointer */

/* Enable output of all function names defined in the source */
#define FPPTAG_DISPLAYFUNCTIONS 32

/* Switch on WWW-mode */
#define FPPTAG_WEBMODE 33

/* Depends function: */
#define FPPTAG_DEPENDS 34 /* data is an depends funtion */

/* Allow include "X" (rather than <X>) to search local files, default is FPP_TRUE */
#define FPPTAG_ALLOW_INCLUDE_LOCAL 35

/* Fileopen function. If set, this is called when FPP tries to open a file: */
#define FPPTAG_FILEOPENFUNC 36 /* data is function pointer to a
			   "FILE* (*)(char * filename, char * mode, void * userdata)", default is NULL */

int fppPreProcess(struct fppTag *);

#ifdef __cplusplus
} // extern "C"
#endif

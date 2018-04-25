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
#include    <stdio.h>
#include    <ctype.h>
#include    "cppdef.h"
#include    "cpp.h"

#ifdef _AMIGA
#include <proto/dos.h>
#endif

FILE_LOCAL void fpp_dump_line(struct Global *, int *);
FILE_LOCAL ReturnCode fpp_doif(struct Global *, int);
INLINE FILE_LOCAL ReturnCode fpp_doinclude(struct Global *);
INLINE FILE_LOCAL int fpp_hasdirectory(char *, char *);


/*
 * Generate (by hand-inspection) a set of unique values for each control
 * operator.  Note that this is not guaranteed to work for non-Ascii
 * machines.  CPP won't compile if there are hash conflicts.
 */

#define L_assert    ('a' + ('s' << 1))
#define L_define    ('d' + ('f' << 1))
#define L_elif      ('e' + ('i' << 1))
#define L_else      ('e' + ('s' << 1))
#define L_endif     ('e' + ('d' << 1))
#define L_error     ('e' + ('r' << 1))
#define L_if        ('i' + (EOS << 1))
#define L_ifdef     ('i' + ('d' << 1))
#define L_ifndef    ('i' + ('n' << 1))
#define L_include   ('i' + ('c' << 1))
#define L_line      ('l' + ('n' << 1))
#define L_nogood    (EOS + (EOS << 1))      /* To catch #i          */
#define L_pragma    ('p' + ('a' << 1))
#define L_undef     ('u' + ('d' << 1))

ReturnCode fpp_control( struct Global *global,
    int *counter )  /* Pending newline counter */
{
    /*
     * Process #control lines.  Simple commands are processed inline,
     * while complex commands have their own subroutines.
     *
     * The counter is used to force out a newline before #line, and
     * #pragma commands.  This prevents these commands from ending up at
     * the end of the previous line if cpp is invoked with the -C option.
     */

    int c;
    char *tp;
    int hash;
    char *ep;
    ReturnCode ret;

    c = fpp_skipws( global );

    if( c == '\n' || c == EOF_CHAR )
        {
        (*counter)++;

        return(FPP_OK);
        }

    if( !isdigit(c) )
        fpp_scanid( global, c );                  /* Get #word to tokenbuf        */
    else
        {
        fpp_unget( global );                    /* Hack -- allow #123 as a      */

        strcpy( global->tokenbuf, "line" );   /* synonym for #line 123        */
        }

    hash = (global->tokenbuf[1] == EOS) ? L_nogood : (global->tokenbuf[0] + (global->tokenbuf[2] << 1));

    switch( hash )
        {
        case L_assert:
            tp = "assert";
            break;
        case L_define:
            tp = "define";
            break;
        case L_elif:
            tp = "elif";
            break;
        case L_else:
            tp = "else";
            break;
        case L_endif:
            tp = "endif";
            break;
        case L_error:
            tp = "error";
            break;
        case L_if:
            tp = "if";
            break;
        case L_ifdef:
            tp = "ifdef";
            break;
        case L_ifndef:
            tp = "ifndef";
            break;
        case L_include:
            tp = "include";
            break;
        case L_line:
            tp = "line";
            break;
        case L_pragma:
            tp = "pragma";
            break;
        case L_undef:
            tp = "undef";
            break;
        default:
            hash = L_nogood;
        case L_nogood:
            tp = "";
            break;
        }

    if( !streq( tp, global->tokenbuf ) )
        hash = L_nogood;

    /*
     * hash is set to a unique value corresponding to the
     * control keyword (or L_nogood if we think it's nonsense).
     */
    if( global->infile->fp == NULL )
        fpp_cwarn( global, WARN_CONTROL_LINE_IN_MACRO, global->tokenbuf );

    if( !compiling )
        {                       /* Not compiling now    */
        switch( hash )
            {
            case L_if:              /* These can't turn     */
            case L_ifdef:           /*  compilation on, but */
            case L_ifndef:          /*   we must nest #if's */
                if( ++global->ifptr >= &global->ifstack[BLK_NEST] )
                    {
                    fpp_cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

                    return( FPP_TOO_MANY_NESTED_STATEMENTS );
                    }

                *global->ifptr = 0;       /* !WAS_COMPILING   */

            case L_line:            /* Many         */
                /*
                 * Are pragma's always processed?
                 */
            case L_pragma:          /*  options     */
            case L_include:         /*   are uninteresting  */
            case L_define:          /*    if we     */
            case L_undef:           /*     aren't           */
            case L_assert:          /*  compiling.  */
            case L_error:
                fpp_dump_line( global, counter );       /* Ignore rest of line  */
                return(FPP_OK);
            }
        }
    /*
     * Make sure that #line and #pragma are output on a fresh line.
     */
    if( *counter > 0 && (hash == L_line || hash == L_pragma) )
        {
        fpp_Putchar( global, '\n' );

        (*counter)--;
        }

    switch( hash )
        {
        case L_line:
            /*
             * Parse the line to update the line number and "progname"
             * field and line number for the next input line.
             * Set wrongline to force it out later.
             */
            c = fpp_skipws( global );

            global->workp = global->work;       /* Save name in work    */

            while( c != '\n' && c != EOF_CHAR )
                {
                if( (ret = fpp_save( global, c )) )
                    return(ret);

                c = fpp_get( global );
                }

            fpp_unget( global );

            if( (ret = fpp_save( global, EOS )) )
                return(ret);

            /*
             * Split #line argument into <line-number> and <name>
             * We subtract 1 as we want the number of the next line.
             */
            global->line = atoi(global->work) - 1;     /* Reset line number    */

            for( tp = global->work; isdigit(*tp) || type[(unsigned)*tp] == SPA; tp++)
                ;             /* Skip over digits */

            if( *tp != EOS )
                {
                /* Got a filename, so:  */

                if( *tp == '"' && (ep = strrchr(tp + 1, '"')) != NULL )
                    {
                    tp++;           /* Skip over left quote */

                    *ep = EOS;      /* And ignore right one */
                    }

                if( global->infile->progname != NULL )
                    /* Give up the old name if it's allocated.   */
                    free( global->infile->progname );

                global->infile->progname = fpp_savestring( global, tp );
                }

            global->wrongline = FPP_TRUE;           /* Force output later   */
            break;

        case L_include:
            ret = fpp_doinclude( global );
            if( ret )
                return(ret);
            break;

        case L_define:
            ret = fpp_dodefine( global );
            if( ret )
                return(ret);
            break;

        case L_undef:
            fpp_doundef( global );
            break;

        case L_else:
            if( global->ifptr == &global->ifstack[0] )
                {
                fpp_cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                fpp_dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                fpp_cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                fpp_dump_line( global, counter );

                return( FPP_OK );
                }

            *global->ifptr |= ELSE_SEEN;

            if( (*global->ifptr & WAS_COMPILING) != 0 )
                {
                if( compiling || (*global->ifptr & FPP_TRUE_SEEN) != 0 )
                    compiling = FPP_FALSE;
                else
                    {
                    compiling = FPP_TRUE;
                    }
                }
            break;

        case L_elif:
            if( global->ifptr == &global->ifstack[0] )
                {
                fpp_cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                fpp_dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                fpp_cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                fpp_dump_line( global, counter );

                return( FPP_OK );
                }

            if( (*global->ifptr & (WAS_COMPILING | FPP_TRUE_SEEN)) != WAS_COMPILING )
                {
                compiling = FPP_FALSE;        /* Done compiling stuff */

                fpp_dump_line( global, counter );   /* Skip this clause */

                return( FPP_OK );
                }

            ret = fpp_doif( global, L_if );

            if( ret )
                return(ret);

            break;

        case L_error:
            fpp_cerror(global, ERROR_ERROR);
            break;

        case L_if:
        case L_ifdef:
        case L_ifndef:
            if( ++global->ifptr < &global->ifstack[BLK_NEST] )
                {
                *global->ifptr = WAS_COMPILING;

                ret = fpp_doif( global, hash );

                if( ret )
                    return(ret);

                break;
                }

            fpp_cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

            return( FPP_TOO_MANY_NESTED_STATEMENTS );

        case L_endif:
            if( global->ifptr == &global->ifstack[0] )
                {
                fpp_cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                fpp_dump_line( global, counter );

                return(FPP_OK);
                }

            if( !compiling && (*global->ifptr & WAS_COMPILING) != 0 )
                global->wrongline = FPP_TRUE;

            compiling = ((*global->ifptr & WAS_COMPILING) != 0);

            --global->ifptr;

            break;

        case L_assert:
            {
            int result;

            ret = fpp_eval( global, &result );

            if(ret)
                return(ret);

            if( result == 0 )
                fpp_cerror( global, ERROR_PREPROC_FAILURE );
            }
            break;

        case L_pragma:
            /*
             * #pragma is provided to pass "options" to later
             * passes of the compiler.  cpp doesn't have any yet.
             */
            fpp_Putstring( global, "#pragma " );

            while( (c = fpp_get( global ) ) != '\n' && c != EOF_CHAR )
                fpp_Putchar( global, c );

            fpp_unget( global );

            fpp_Putchar( global, '\n' );

            break;

        default:
            /*
             * Undefined #control keyword.
             * Note: the correct behavior may be to warn and
             * pass the line to a subsequent compiler pass.
             * This would allow #asm or similar extensions.
             */
            if( global->warnillegalcpp )
                fpp_cwarn( global, WARN_ILLEGAL_COMMAND, global->tokenbuf );

            fpp_Putchar( global, '#' );
            fpp_Putstring( global, global->tokenbuf );
            fpp_Putchar( global, ' ' );

            while( (c = fpp_get( global ) ) != '\n' && c != EOF_CHAR )
                fpp_Putchar( global, c );

            fpp_unget( global );

            fpp_Putchar( global, '\n' );

            break;
        }

    if( hash != L_include )
        {
        #if OLD_PREPROCESSOR
        /*
         * Ignore the rest of the #control line so you can write
         *      #if foo
         *      #endif  foo
         */
        fpp_dump_line( global, counter );         /* Take common exit */

        return( FPP_OK );
        #else
        if( fpp_skipws( global ) != '\n' )
            {
            fpp_cwarn( global, WARN_UNEXPECTED_TEXT_IGNORED );

            fpp_skipnl( global );
            }
        #endif
        }

    (*counter)++;

    return( FPP_OK );
}

FILE_LOCAL
void fpp_dump_line(struct Global *global, int *counter)
{
    fpp_skipnl( global );         /* Ignore rest of line  */

    (*counter)++;
}

FILE_LOCAL
ReturnCode fpp_doif(struct Global *global, int hash)
{
    /*
     * Process an #if, #ifdef, or #ifndef. The latter two are straightforward,
     * while #if needs a subroutine of its own to evaluate the expression.
     *
     * fpp_doif() is called only if compiling is FPP_TRUE.  If false, compilation
     * is always supressed, so we don't need to evaluate anything.  This
     * supresses unnecessary warnings.
     */

    int c;
    int found;
    ReturnCode ret;

    if( (c = fpp_skipws( global ) ) == '\n' || c == EOF_CHAR )
        {
        fpp_unget( global );

        fpp_cerror( global, ERROR_MISSING_ARGUMENT );

        #if !OLD_PREPROCESSOR
        fpp_skipnl( global );               /* Prevent an extra     */

        fpp_unget( global );                /* Error message        */
        #endif

        return(FPP_OK);
        }

    if( hash == L_if )
        {
        fpp_unget( global );

        ret = fpp_eval( global, &found );

        if( ret )
            return( ret );

        found = (found != 0);     /* Evaluate expr, != 0 is  FPP_TRUE */

        hash = L_ifdef;       /* #if is now like #ifdef */
        }
    else
        {
        if( type[c] != LET )
            {         /* Next non-blank isn't letter  */
                          /* ... is an error          */
            fpp_cerror( global, ERROR_MISSING_ARGUMENT );

            #if !OLD_PREPROCESSOR
            fpp_skipnl( global );             /* Prevent an extra     */

            fpp_unget( global );              /* Error message        */
            #endif

            return(FPP_OK);
            }

        found = ( fpp_lookid( global, c ) != NULL ); /* Look for it in symbol table */
        }

    if( found == (hash == L_ifdef) )
        {
        compiling = FPP_TRUE;

        *global->ifptr |= FPP_TRUE_SEEN;
        }
    else
        compiling = FPP_FALSE;

    return(FPP_OK);
}

INLINE FILE_LOCAL
ReturnCode fpp_doinclude( struct Global *global )
{
    /*
     *  Process the #include control line.
     *  There are three variations:
     *
     *      #include "file" search somewhere relative to the
     *                      current source file, if not found,
     *                      treat as #include <file>.
     *
     *      #include <file> Search in an implementation-dependent
     *                      list of places.
     *
     *      #include token  Expand the token, it must be one of
     *                      "file" or <file>, process as such.
     *
     *  Note:   the November 12 draft forbids '>' in the #include <file> format.
     *          This restriction is unnecessary and not implemented.
     */

    int c;
    int delim;
    ReturnCode ret;

    delim = fpp_skipws( global );

    if( (ret = fpp_macroid( global, &delim )) )
        return(ret);

    if( delim != '<' && delim != '"' )
        {
        fpp_cerror( global, ERROR_INCLUDE_SYNTAX );

        return( FPP_OK );
        }

    if( delim == '<' )
        delim = '>';

    global->workp = global->work;

    while( (c = fpp_get(global)) != '\n' && c != EOF_CHAR )
        if( (ret = fpp_save( global, c )) )       /* Put it away.                */
            return( ret );

    fpp_unget( global );                        /* Force nl after include      */

    /*
     * The draft is unclear if the following should be done.
     */
    while( --global->workp >= global->work &&
        (*global->workp == ' ' || *global->workp == '\t') )
        ;               /* Trim blanks from filename    */

    if( *global->workp != delim )
        {
        fpp_cerror( global, ERROR_INCLUDE_SYNTAX );

        return(FPP_OK);
        }

    *global->workp = EOS;         /* Terminate filename       */

    ret = fpp_openinclude( global, global->work, (delim == '"') );

    if( ret && global->warnnoinclude )
        {
        /*
         * Warn if #include file isn't there.
         */
        fpp_cwarn( global, WARN_CANNOT_OPEN_INCLUDE, global->work );
        }

    return( FPP_OK );
}

#ifdef _AMIGA
ReturnCode MultiAssignLoad( struct Global *global, char *incptr, char *filename, char *tmpname );
#endif

ReturnCode fpp_openinclude( struct Global *global,
    char *filename,     /* Input file name         */
    int searchlocal )   /* FPP_TRUE if #include "file" */
{
    /*
     * Actually open an include file.  This routine is only called from
     * fpp_doinclude() above, but was written as a separate subroutine for
     * programmer convenience.  It searches the list of directories
     * and actually opens the file, linking it into the list of
     * active files.  Returns ReturnCode. No error message is printed.
     */

    char **incptr;
    char tmpname[NWORK]; /* Filename work area    */
    size_t len;

    if( filename[0] == '/' )
        {
        if( ! fpp_openfile( global, filename ) )
            return(FPP_OK);
        }

    if( searchlocal && global->allowincludelocal )
        {
        /*
         * Look in local directory first.
         * Try to open filename relative to the directory of the current
         * source file (as opposed to the current directory). (ARF, SCK).
         * Note that the fully qualified pathname is always built by
         * discarding the last pathname component of the source file
         * name then tacking on the #include argument.
         */
        if( fpp_hasdirectory( global->infile->filename, tmpname ) )
            strcat( tmpname, filename );
        else
            strcpy( tmpname, filename );

        if( ! fpp_openfile( global, tmpname ) )
            return(FPP_OK);
        }

    /*
     * Look in any directories specified by -I command line
     * arguments, then in the builtin search list.
     */
    for( incptr = global->incdir; incptr < global->incend; incptr++ )
        {
        len = strlen(*incptr);

        if( len + strlen(filename) >= sizeof(tmpname) )
            {
            fpp_cfatal( global, FATAL_FILENAME_BUFFER_OVERFLOW );

            return( FPP_FILENAME_BUFFER_OVERFLOW );
            }
        else
            {
            if( (*incptr)[len-1] != '/' )
                sprintf( tmpname, "%s/%s", *incptr, filename );
            else
                sprintf( tmpname, "%s%s", *incptr, filename );

            if( !fpp_openfile( global, tmpname ) )
                return(FPP_OK);
            }
        }

    return( FPP_NO_INCLUDE );
}

INLINE FILE_LOCAL
int fpp_hasdirectory( char *source,   /* Directory to examine         */
    char *result )  /* Put directory stuff here     */
{
    /*
     * If a device or directory is found in the source filename string, the
     * node/device/directory part of the string is copied to result and
     * fpp_hasdirectory returns FPP_TRUE.  Else, nothing is copied and it returns FPP_FALSE.
     */

    char *tp2;

    if( (tp2 = strrchr( source, '/' ) ) == NULL )
        return(FPP_FALSE);

    strncpy( result, source, tp2 - source + 1 );

    result[tp2 - source + 1] = EOS;

    return( FPP_TRUE );
}

#ifdef _AMIGA
//
//  amp July 9, 1997
//
//  Use the OS Luke...
//
//  We do the sneaky version and let the OS do all
//  the hard work so we don't have to mess around
//  a lot ;)
//
ReturnCode MultiAssignLoad( struct Global *global, char *incptr, char *filename, char *tmpname )

{ /* MultiAssignLoad */

    struct MsgPort  *FSTask;
    struct DevProc  *DevProc = NULL;
    LONG            RtnCode = FPP_NO_INCLUDE;

    FSTask = GetFileSysTask();

    do
        {
        //
        //  This should not bring up a requester.
        //  check to see if cpp does in fact tweek
        //  the process WindowPtr.
        //
        DevProc = GetDeviceProc( incptr, DevProc );

        if( DevProc )
            {
            SetFileSysTask( DevProc->dvp_Port );

            //
            //  Normally we would pass the lock and filename
            //  to the Load() routine, which would CD to the
            //  directory and Open(filename), but in order to
            //  satisfy the exisiting fpp_openfile() function, we
            //  bite the bullet and build the complete pathspec
            //  rather than add the standard Load() routine.
            //
            if( NameFromLock( DevProc->dvp_Lock, tmpname, NWORK ) )
                {
                AddPart( tmpname, filename, NWORK );

                RtnCode = fpp_openfile( global, tmpname );

                if( ! RtnCode )
                    break;
                }
            }

        } while ( RtnCode &&
            DevProc &&
            (DevProc->dvp_Flags & DVPF_ASSIGN) &&
            IoErr() == ERROR_OBJECT_NOT_FOUND); /* repeat if multi-assign */

    SetFileSysTask( FSTask );

    if( DevProc )
        FreeDeviceProc( DevProc );

    return RtnCode;

} /* MultiAssignLoad */
#endif  //_AMIGA

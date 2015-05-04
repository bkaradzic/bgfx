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

FILE_LOCAL void dump_line(struct Global *, int *);
FILE_LOCAL ReturnCode doif(struct Global *, int);
INLINE FILE_LOCAL ReturnCode doinclude(struct Global *);
INLINE FILE_LOCAL int hasdirectory(char *, char *);


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

ReturnCode control( struct Global *global,
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

    c = skipws( global );

    if( c == '\n' || c == EOF_CHAR )
        {
        (*counter)++;

        return(FPP_OK);
        }

    if( !isdigit(c) )
        scanid( global, c );                  /* Get #word to tokenbuf        */
    else
        {
        unget( global );                    /* Hack -- allow #123 as a      */

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
        cwarn( global, WARN_CONTROL_LINE_IN_MACRO, global->tokenbuf );

    if( !compiling )
        {                       /* Not compiling now    */
        switch( hash )
            {
            case L_if:              /* These can't turn     */
            case L_ifdef:           /*  compilation on, but */
            case L_ifndef:          /*   we must nest #if's */
                if( ++global->ifptr >= &global->ifstack[BLK_NEST] )
                    {
                    cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

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
                dump_line( global, counter );       /* Ignore rest of line  */
                return(FPP_OK);
            }
        }
    /*
     * Make sure that #line and #pragma are output on a fresh line.
     */
    if( *counter > 0 && (hash == L_line || hash == L_pragma) )
        {
        Putchar( global, '\n' );

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
            c = skipws( global );

            global->workp = global->work;       /* Save name in work    */

            while( c != '\n' && c != EOF_CHAR )
                {
                if( (ret = save( global, c )) )
                    return(ret);

                c = get( global );
                }

            unget( global );

            if( (ret = save( global, EOS )) )
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

                global->infile->progname = savestring( global, tp );
                }

            global->wrongline = TRUE;           /* Force output later   */
            break;

        case L_include:
            ret = doinclude( global );
            if( ret )
                return(ret);
            break;

        case L_define:
            ret = dodefine( global );
            if( ret )
                return(ret);
            break;

        case L_undef:
            doundef( global );
            break;

        case L_else:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }

            *global->ifptr |= ELSE_SEEN;

            if( (*global->ifptr & WAS_COMPILING) != 0 )
                {
                if( compiling || (*global->ifptr & TRUE_SEEN) != 0 )
                    compiling = FALSE;
                else
                    {
                    compiling = TRUE;
                    }
                }
            break;

        case L_elif:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }
            else if( (*global->ifptr & ELSE_SEEN) != 0 )
                {
                cerror( global, ERROR_STRING_MAY_NOT_FOLLOW_ELSE, global->tokenbuf );

                dump_line( global, counter );

                return( FPP_OK );
                }

            if( (*global->ifptr & (WAS_COMPILING | TRUE_SEEN)) != WAS_COMPILING )
                {
                compiling = FALSE;        /* Done compiling stuff */

                dump_line( global, counter );   /* Skip this clause */

                return( FPP_OK );
                }

            ret = doif( global, L_if );

            if( ret )
                return(ret);

            break;

        case L_error:
            cerror(global, ERROR_ERROR);
            break;

        case L_if:
        case L_ifdef:
        case L_ifndef:
            if( ++global->ifptr < &global->ifstack[BLK_NEST] )
                {
                *global->ifptr = WAS_COMPILING;

                ret = doif( global, hash );

                if( ret )
                    return(ret);

                break;
                }

            cfatal( global, FATAL_TOO_MANY_NESTINGS, global->tokenbuf );

            return( FPP_TOO_MANY_NESTED_STATEMENTS );

        case L_endif:
            if( global->ifptr == &global->ifstack[0] )
                {
                cerror( global, ERROR_STRING_MUST_BE_IF, global->tokenbuf );

                dump_line( global, counter );

                return(FPP_OK);
                }

            if( !compiling && (*global->ifptr & WAS_COMPILING) != 0 )
                global->wrongline = TRUE;

            compiling = ((*global->ifptr & WAS_COMPILING) != 0);

            --global->ifptr;

            break;

        case L_assert:
            {
            int result;

            ret = eval( global, &result );

            if(ret)
                return(ret);

            if( result == 0 )
                cerror( global, ERROR_PREPROC_FAILURE );
            }
            break;

        case L_pragma:
            /*
             * #pragma is provided to pass "options" to later
             * passes of the compiler.  cpp doesn't have any yet.
             */
            Putstring( global, "#pragma " );

            while( (c = get( global ) ) != '\n' && c != EOF_CHAR )
                Putchar( global, c );

            unget( global );

            Putchar( global, '\n' );

            break;

        default:
            /*
             * Undefined #control keyword.
             * Note: the correct behavior may be to warn and
             * pass the line to a subsequent compiler pass.
             * This would allow #asm or similar extensions.
             */
            if( global->warnillegalcpp )
                cwarn( global, WARN_ILLEGAL_COMMAND, global->tokenbuf );

            Putchar( global, '#' );
            Putstring( global, global->tokenbuf );
            Putchar( global, ' ' );

            while( (c = get( global ) ) != '\n' && c != EOF_CHAR )
                Putchar( global, c );

            unget( global );

            Putchar( global, '\n' );

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
        dump_line( global, counter );         /* Take common exit */

        return( FPP_OK );
        #else
        if( skipws( global ) != '\n' )
            {
            cwarn( global, WARN_UNEXPECTED_TEXT_IGNORED );

            skipnl( global );
            }
        #endif
        }

    (*counter)++;

    return( FPP_OK );
}

FILE_LOCAL
void dump_line(struct Global *global, int *counter)
{
    skipnl( global );         /* Ignore rest of line  */

    (*counter)++;
}

FILE_LOCAL
ReturnCode doif(struct Global *global, int hash)
{
    /*
     * Process an #if, #ifdef, or #ifndef. The latter two are straightforward,
     * while #if needs a subroutine of its own to evaluate the expression.
     *
     * doif() is called only if compiling is TRUE.  If false, compilation
     * is always supressed, so we don't need to evaluate anything.  This
     * supresses unnecessary warnings.
     */

    int c;
    int found;
    ReturnCode ret;

    if( (c = skipws( global ) ) == '\n' || c == EOF_CHAR )
        {
        unget( global );

        cerror( global, ERROR_MISSING_ARGUMENT );

        #if !OLD_PREPROCESSOR
        skipnl( global );               /* Prevent an extra     */

        unget( global );                /* Error message        */
        #endif

        return(FPP_OK);
        }

    if( hash == L_if )
        {
        unget( global );

        ret = eval( global, &found );

        if( ret )
            return( ret );

        found = (found != 0);     /* Evaluate expr, != 0 is  TRUE */

        hash = L_ifdef;       /* #if is now like #ifdef */
        }
    else
        {
        if( type[c] != LET )
            {         /* Next non-blank isn't letter  */
                          /* ... is an error          */
            cerror( global, ERROR_MISSING_ARGUMENT );

            #if !OLD_PREPROCESSOR
            skipnl( global );             /* Prevent an extra     */

            unget( global );              /* Error message        */
            #endif

            return(FPP_OK);
            }

        found = ( lookid( global, c ) != NULL ); /* Look for it in symbol table */
        }

    if( found == (hash == L_ifdef) )
        {
        compiling = TRUE;

        *global->ifptr |= TRUE_SEEN;
        }
    else
        compiling = FALSE;

    return(FPP_OK);
}

INLINE FILE_LOCAL
ReturnCode doinclude( struct Global *global )
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

    delim = skipws( global );

    if( (ret = macroid( global, &delim )) )
        return(ret);

    if( delim != '<' && delim != '"' )
        {
        cerror( global, ERROR_INCLUDE_SYNTAX );

        return( FPP_OK );
        }

    if( delim == '<' )
        delim = '>';

    global->workp = global->work;

    while( (c = get(global)) != '\n' && c != EOF_CHAR )
        if( (ret = save( global, c )) )       /* Put it away.                */
            return( ret );

    unget( global );                        /* Force nl after include      */

    /*
     * The draft is unclear if the following should be done.
     */
    while( --global->workp >= global->work &&
        (*global->workp == ' ' || *global->workp == '\t') )
        ;               /* Trim blanks from filename    */

    if( *global->workp != delim )
        {
        cerror( global, ERROR_INCLUDE_SYNTAX );

        return(FPP_OK);
        }

    *global->workp = EOS;         /* Terminate filename       */

    ret = openinclude( global, global->work, (delim == '"') );

    if( ret && global->warnnoinclude )
        {
        /*
         * Warn if #include file isn't there.
         */
        cwarn( global, WARN_CANNOT_OPEN_INCLUDE, global->work );
        }

    return( FPP_OK );
}

#ifdef _AMIGA
ReturnCode MultiAssignLoad( struct Global *global, char *incptr, char *filename, char *tmpname );
#endif

ReturnCode openinclude( struct Global *global,
    char *filename,     /* Input file name         */
    int searchlocal )   /* TRUE if #include "file" */
{
    /*
     * Actually open an include file.  This routine is only called from
     * doinclude() above, but was written as a separate subroutine for
     * programmer convenience.  It searches the list of directories
     * and actually opens the file, linking it into the list of
     * active files.  Returns ReturnCode. No error message is printed.
     */

    char **incptr;
    char tmpname[NWORK]; /* Filename work area    */
    size_t len;

    if( filename[0] == '/' )
        {
        if( ! openfile( global, filename ) )
            return(FPP_OK);
        }

    if( searchlocal )
        {
        /*
         * Look in local directory first.
         * Try to open filename relative to the directory of the current
         * source file (as opposed to the current directory). (ARF, SCK).
         * Note that the fully qualified pathname is always built by
         * discarding the last pathname component of the source file
         * name then tacking on the #include argument.
         */
        if( hasdirectory( global->infile->filename, tmpname ) )
            strcat( tmpname, filename );
        else
            strcpy( tmpname, filename );

        if( ! openfile( global, tmpname ) )
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
            cfatal( global, FATAL_FILENAME_BUFFER_OVERFLOW );

            return( FPP_FILENAME_BUFFER_OVERFLOW );
            }
        else
            {
            if( (*incptr)[len-1] != '/' )
                sprintf( tmpname, "%s/%s", *incptr, filename );
            else
                sprintf( tmpname, "%s%s", *incptr, filename );

            if( !openfile( global, tmpname ) )
                return(FPP_OK);
            }
        }

    return( FPP_NO_INCLUDE );
}

INLINE FILE_LOCAL
int hasdirectory( char *source,   /* Directory to examine         */
    char *result )  /* Put directory stuff here     */
{
    /*
     * If a device or directory is found in the source filename string, the
     * node/device/directory part of the string is copied to result and
     * hasdirectory returns TRUE.  Else, nothing is copied and it returns FALSE.
     */

    char *tp2;

    if( (tp2 = strrchr( source, '/' ) ) == NULL )
        return(FALSE);

    strncpy( result, source, tp2 - source + 1 );

    result[tp2 - source + 1] = EOS;

    return( TRUE );
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
            //  satisfy the exisiting openfile() function, we
            //  bite the bullet and build the complete pathspec
            //  rather than add the standard Load() routine.
            //
            if( NameFromLock( DevProc->dvp_Lock, tmpname, NWORK ) )
                {
                AddPart( tmpname, filename, NWORK );

                RtnCode = openfile( global, tmpname );

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

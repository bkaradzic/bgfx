/******************************************************************************
 *                               FREXXWARE
 * ----------------------------------------------------------------------------
 *
 * Project: Frexx C Preprocessor
 * $Source: /home/user/start/cpp/RCS/FPPBase.h,v $
 * $Revision: 1.3 $
 * $Date: 1993/12/06 13:51:20 $
 * $Author: start $
 * $State: Exp $
 * $Locker: start $
 *
 * ----------------------------------------------------------------------------
 * $Log: FPPBase.h,v $
 * Revision 1.3  1993/12/06  13:51:20  start
 * A lot of new stuff (too much to mention)
 *
 * Revision 1.2  1993/11/11  07:16:39  start
 * New stuff
 *
 * Revision 1.2  1993/11/11  07:16:39  start
 * New stuff
 *
 * Revision 1.1  1993/11/03  09:15:59  start
 * Initial revision
 *
 *
 *****************************************************************************/
#ifndef FPP_BASE_H
#define FPP_BASE_H

/*
**   $Filename: libraries/FPPbase.h $
**   $Release: 1.0 $
**   $Date: 1993/12/06 13:51:20 $
**
**   (C) Copyright 1992, 1993 by FrexxWare
**       All Rights Reserved
*/

#include <exec/types.h>
#include <exec/libraries.h>

struct FPPBase {
  struct Library LibNode;
  UBYTE Flags;
  UBYTE pad;
  /* long word aligned */
  ULONG SysLib;
  ULONG DosLib;
  ULONG SegList;
};

#define FPPNAME "fpp.library"

#endif

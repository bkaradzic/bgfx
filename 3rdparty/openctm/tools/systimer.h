//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        systimer.h
// Description: Interface for the system timer routines.
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

#ifndef __SYSIMER_H_
#define __SYSIMER_H_

#if !defined(WIN32) && defined(_WIN32)
#define WIN32
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <list>

class SysTimer {
  private:
    std::list<double> mStack;
#ifdef WIN32
    __int64 mTimeFreq;
    __int64 mTimeStart;
#else
    long long mTimeStart;
#endif

  public:
    /// Constructor
    SysTimer();

    /// Get current time.
    double GetTime();

    /// Push current time (start measuring).
    void Push();

    /// Pop delta time since last push.
    double PopDelta();
};

#endif // __SYSIMER_H_

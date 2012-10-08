//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        systimer.cpp
// Description: Implementation of the system timer routines.
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

#include "systimer.h"

using namespace std;


/// Constructor
SysTimer::SysTimer()
{
#ifdef WIN32
  if(QueryPerformanceFrequency((LARGE_INTEGER *)&mTimeFreq))
    QueryPerformanceCounter((LARGE_INTEGER *)&mTimeStart);
  else
    mTimeFreq = 0;
#else
  struct timeval tv;
  gettimeofday(&tv, 0);
  mTimeStart = (long long) tv.tv_sec * (long long) 1000000 + (long long) tv.tv_usec;
#endif
}

/// Get current time.
double SysTimer::GetTime()
{
#ifdef WIN32
  __int64 t;
  QueryPerformanceCounter((LARGE_INTEGER *)&t);
  return double(t - mTimeStart) / double(mTimeFreq);
#else
  struct timeval tv;
  gettimeofday(&tv, 0);
  long long t = (long long) tv.tv_sec * (long long) 1000000 + (long long) tv.tv_usec;
  return (1e-6) * double(t - mTimeStart);
#endif
}

/// Push current time (start measuring).
void SysTimer::Push()
{
  mStack.push_back(GetTime());
}

/// Pop delta time since last push.
double SysTimer::PopDelta()
{
  double delta = GetTime() - mStack.back();
  mStack.pop_back();
  return delta;
}

//
// Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//
// This file contains the Linux-specific functions
//
#include "../osinclude.h"
#include "../../../OGLCompilersDLL/InitializeDll.h"

#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <cstdio>
#include <sys/time.h>

#if !defined(__Fuchsia__)
#include <sys/resource.h>
#endif

namespace glslang {

namespace {
    pthread_mutex_t gMutex;
}

static void InitMutex(void)
{
  pthread_mutexattr_t mutexattr;
  pthread_mutexattr_init(&mutexattr);
  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&gMutex, &mutexattr);
}

void InitGlobalLock()
{
  static pthread_once_t once = PTHREAD_ONCE_INIT;
  pthread_once(&once, InitMutex);
}

void GetGlobalLock()
{
  pthread_mutex_lock(&gMutex);
}

void ReleaseGlobalLock()
{
  pthread_mutex_unlock(&gMutex);
}

// #define DUMP_COUNTERS

void OS_DumpMemoryCounters()
{
#ifdef DUMP_COUNTERS
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0)
        printf("Working set size: %ld\n", usage.ru_maxrss * 1024);
#else
    printf("Recompile with DUMP_COUNTERS defined to see counters.\n");
#endif
}

} // end namespace glslang

//
// Copyright 2014-2017 Celtoys Ltd
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/*
@Contents:

    @DEPS:          External Dependencies
    @TIMERS:        Platform-specific timers
    @TLS:           Thread-Local Storage
    @ATOMIC:        Atomic Operations
    @VMBUFFER:      Mirror Buffer using Virtual Memory for auto-wrap
    @NEW:           New/Delete operators with error values for simplifying object create/destroy
    @THREADS:       Threads
    @SAFEC:         Safe C Library excerpts
    @OBJALLOC:      Reusable Object Allocator
    @DYNBUF:        Dynamic Buffer
    @HASHTABLE:     Integer pair hash map for inserts/finds. No removes for added simplicity.
    @STRINGTABLE:	Map from string hash to string offset in local buffer
    @SOCKETS:       Sockets TCP/IP Wrapper
    @SHA1:          SHA-1 Cryptographic Hash Function
    @BASE64:        Base-64 encoder
    @MURMURHASH:    Murmur-Hash 3
    @WEBSOCKETS:    WebSockets
    @MESSAGEQ:      Multiple producer, single consumer message queue
    @NETWORK:       Network Server
    @SAMPLE:        Base Sample Description (CPU by default)
    @SAMPLETREE:    A tree of samples with their allocator
    @TSAMPLER:      Per-Thread Sampler
    @REMOTERY:      Remotery
    @CUDA:          CUDA event sampling
    @D3D11:         Direct3D 11 event sampling
    @OPENGL:        OpenGL event sampling
    @METAL:         Metal event sampling
*/

#define RMT_IMPL
#include "Remotery.h"


#ifdef RMT_PLATFORM_WINDOWS
  #pragma comment(lib, "ws2_32.lib")
#endif


#if RMT_ENABLED


// Global settings
static rmtSettings g_Settings;
static rmtBool g_SettingsInitialized = RMT_FALSE;


/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @DEPS: External Dependencies
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



//
// Required CRT dependencies
//
#if RMT_USE_TINYCRT

    #include <TinyCRT/TinyCRT.h>
    #include <TinyCRT/TinyWinsock.h>
    #include <Memory/Memory.h>

    #define CreateFileMapping CreateFileMappingA

#else

    #ifdef RMT_PLATFORM_MACOS
        #include <mach/mach_time.h>
        #include <mach/vm_map.h>
        #include <mach/mach.h>
        #include <sys/time.h>
    #else
        #include <malloc.h>
    #endif

    #include <assert.h>

    #ifdef RMT_PLATFORM_WINDOWS
        #include <winsock2.h>
        #ifndef __MINGW32__
            #include <intrin.h>
        #endif
        #undef min
        #undef max
    #endif

    #ifdef RMT_PLATFORM_LINUX
        #include <time.h>
        #include <sys/prctl.h>
    #endif

    #if defined(RMT_PLATFORM_POSIX)
        #include <stdlib.h>
        #include <pthread.h>
        #include <unistd.h>
        #include <string.h>
        #include <sys/socket.h>
        #include <sys/mman.h>
        #include <netinet/in.h>
        #include <fcntl.h>
        #include <errno.h>
        #include <dlfcn.h>
    #endif

    #ifdef __MINGW32__
        #include <pthread.h>
    #endif

#endif

#if 0 //def _MSC_VER
    #define RMT_UNREFERENCED_PARAMETER(i) assert(i == 0 || i != 0);	// To fool warning C4100 on warning level 4
#else
    #define RMT_UNREFERENCED_PARAMETER(i) (void)(1 ? (void)0 : ((void)i))
#endif


#if RMT_USE_CUDA
    #include <cuda.h>
#endif



rmtU8 minU8(rmtU8 a, rmtU8 b)
{
    return a < b ? a : b;
}
rmtS64 minS64(rmtS64 a, rmtS64 b)
{
    return a < b ? a : b;
}


rmtU8 maxU8(rmtU8 a, rmtU8 b)
{
    return a > b ? a : b;
}
rmtS64 maxS64(rmtS64 a, rmtS64 b)
{
    return a > b ? a : b;
}


// Memory management functions
static void* rmtMalloc( rmtU32 size )
{
    return g_Settings.malloc( g_Settings.mm_context, size );
}

static void* rmtRealloc( void* ptr, rmtU32 size)
{
    return g_Settings.realloc( g_Settings.mm_context, ptr, size );
}

static void rmtFree( void* ptr )
{
    g_Settings.free( g_Settings.mm_context, ptr );
}

#if RMT_USE_OPENGL
// DLL/Shared Library functions
static void* rmtLoadLibrary(const char* path)
{
    #if defined(RMT_PLATFORM_WINDOWS)
        return (void*)LoadLibraryA(path);
    #elif defined(RMT_PLATFORM_POSIX)
        return dlopen(path, RTLD_LOCAL | RTLD_LAZY);
    #else
        return NULL;
    #endif
}

static void rmtFreeLibrary(void* handle)
{
    #if defined(RMT_PLATFORM_WINDOWS)
        FreeLibrary((HMODULE)handle);
    #elif defined(RMT_PLATFORM_POSIX)
        dlclose(handle);
    #endif
}

static void* rmtGetProcAddress(void* handle, const char* symbol)
{
    #if defined(RMT_PLATFORM_WINDOWS)
        #ifdef _MSC_VER
            #pragma warning(push)
            #pragma warning(disable:4152) // C4152: nonstandard extension, function/data pointer conversion in expression
        #endif
        return GetProcAddress((HMODULE)handle, (LPCSTR)symbol);
        #ifdef _MSC_VER
            #pragma warning(pop)
        #endif
    #elif defined(RMT_PLATFORM_POSIX)
        return dlsym(handle, symbol);
    #else
        return NULL;
    #endif
}
#endif

/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @TIMERS: Platform-specific timers
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



//
// Get millisecond timer value that has only one guarantee: multiple calls are consistently comparable.
// On some platforms, even though this returns milliseconds, the timer may be far less accurate.
//
static rmtU32 msTimer_Get()
{
    #ifdef RMT_PLATFORM_WINDOWS
        return (rmtU32)GetTickCount();
    #else
        clock_t time = clock();
        rmtU32 msTime = (rmtU32) (time / (CLOCKS_PER_SEC / 1000));
        return msTime;
    #endif
}


//
// Micro-second accuracy high performance counter
//
#ifndef RMT_PLATFORM_WINDOWS
    typedef rmtU64 LARGE_INTEGER;
#endif
typedef struct
{
    LARGE_INTEGER counter_start;
    double counter_scale;
} usTimer;


static void usTimer_Init(usTimer* timer)
{
    #if defined(RMT_PLATFORM_WINDOWS)
        LARGE_INTEGER performance_frequency;

        assert(timer != NULL);

        // Calculate the scale from performance counter to microseconds
        QueryPerformanceFrequency(&performance_frequency);
        timer->counter_scale = 1000000.0 / performance_frequency.QuadPart;

        // Record the offset for each read of the counter
        QueryPerformanceCounter(&timer->counter_start);

    #elif defined(RMT_PLATFORM_MACOS)

        mach_timebase_info_data_t nsScale;
        mach_timebase_info( &nsScale );
        const double ns_per_us = 1.0e3;
        timer->counter_scale = (double)(nsScale.numer) / ((double)nsScale.denom * ns_per_us);

        timer->counter_start = mach_absolute_time();

    #elif defined(RMT_PLATFORM_LINUX)

        struct timespec tv;
        clock_gettime(CLOCK_REALTIME, &tv);
        timer->counter_start = (rmtU64)(tv.tv_sec * (rmtU64)1000000) + (rmtU64)(tv.tv_nsec * 0.001);

    #endif
}


static rmtU64 usTimer_Get(usTimer* timer)
{
    #if defined(RMT_PLATFORM_WINDOWS)
        LARGE_INTEGER performance_count;

        assert(timer != NULL);

        // Read counter and convert to microseconds
        QueryPerformanceCounter(&performance_count);
        return (rmtU64)((performance_count.QuadPart - timer->counter_start.QuadPart) * timer->counter_scale);

    #elif defined(RMT_PLATFORM_MACOS)

        rmtU64 curr_time = mach_absolute_time();
        return (rmtU64)((curr_time - timer->counter_start) * timer->counter_scale);

    #elif defined(RMT_PLATFORM_LINUX)

        struct timespec tv;
        clock_gettime(CLOCK_REALTIME, &tv);
        return  ((rmtU64)(tv.tv_sec * (rmtU64)1000000) + (rmtU64)(tv.tv_nsec * 0.001)) - timer->counter_start;

    #endif
}


static void msSleep(rmtU32 time_ms)
{
    #ifdef RMT_PLATFORM_WINDOWS
        Sleep(time_ms);
    #elif defined(RMT_PLATFORM_POSIX)
        usleep(time_ms * 1000);
    #endif
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @TLS: Thread-Local Storage
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#define TLS_INVALID_HANDLE 0xFFFFFFFF

#if defined(RMT_PLATFORM_WINDOWS)
    typedef rmtU32 rmtTLS;
#else
    typedef pthread_key_t rmtTLS;
#endif

static rmtError tlsAlloc(rmtTLS* handle)
{
    assert(handle != NULL);

#if defined(RMT_PLATFORM_WINDOWS)

    *handle = (rmtTLS)TlsAlloc();
    if (*handle == TLS_OUT_OF_INDEXES)
    {
        *handle = TLS_INVALID_HANDLE;
        return RMT_ERROR_TLS_ALLOC_FAIL;
    }

#elif defined(RMT_PLATFORM_POSIX)

    if (pthread_key_create(handle, NULL) != 0)
    {
        *handle = TLS_INVALID_HANDLE;
        return RMT_ERROR_TLS_ALLOC_FAIL;
    }

#endif

    return RMT_ERROR_NONE;
}


static void tlsFree(rmtTLS handle)
{
    assert(handle != TLS_INVALID_HANDLE);

#if defined(RMT_PLATFORM_WINDOWS)

    TlsFree(handle);

#elif defined(RMT_PLATFORM_POSIX)

    pthread_key_delete((pthread_key_t)handle);

#endif
}


static void tlsSet(rmtTLS handle, void* value)
{
    assert(handle != TLS_INVALID_HANDLE);

#if defined(RMT_PLATFORM_WINDOWS)

    TlsSetValue(handle, value);

#elif defined(RMT_PLATFORM_POSIX)

    pthread_setspecific((pthread_key_t)handle, value);

#endif
}


static void* tlsGet(rmtTLS handle)
{
    assert(handle != TLS_INVALID_HANDLE);

#if defined(RMT_PLATFORM_WINDOWS)

    return TlsGetValue(handle);

#elif defined(RMT_PLATFORM_POSIX)

    return pthread_getspecific((pthread_key_t)handle);

#endif
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @ATOMIC: Atomic Operations
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


static rmtBool AtomicCompareAndSwap(rmtU32 volatile* val, long old_val, long new_val)
{
    #if defined(RMT_PLATFORM_WINDOWS) && !defined(__MINGW32__)
        return _InterlockedCompareExchange((long volatile*)val, new_val, old_val) == old_val ? RMT_TRUE : RMT_FALSE;
    #elif defined(RMT_PLATFORM_POSIX) || defined(__MINGW32__)
        return __sync_bool_compare_and_swap(val, old_val, new_val) ? RMT_TRUE : RMT_FALSE;
    #endif
}


static rmtBool AtomicCompareAndSwapPointer(long* volatile* ptr, long* old_ptr, long* new_ptr)
{
    #if defined(RMT_PLATFORM_WINDOWS) && !defined(__MINGW32__)
        #ifdef _WIN64
            return _InterlockedCompareExchange64((__int64 volatile*)ptr, (__int64)new_ptr, (__int64)old_ptr) == (__int64)old_ptr ? RMT_TRUE : RMT_FALSE;
        #else
            return _InterlockedCompareExchange((long volatile*)ptr, (long)new_ptr, (long)old_ptr) == (long)old_ptr ? RMT_TRUE : RMT_FALSE;
        #endif
    #elif defined(RMT_PLATFORM_POSIX) || defined(__MINGW32__)
        return __sync_bool_compare_and_swap(ptr, old_ptr, new_ptr) ? RMT_TRUE : RMT_FALSE;
    #endif
}


//
// NOTE: Does not guarantee a memory barrier
// TODO: Make sure all platforms don't insert a memory barrier as this is only for stats
//       Alternatively, add strong/weak memory order equivalents
//
static rmtS32 AtomicAdd(rmtS32 volatile* value, rmtS32 add)
{
    #if defined(RMT_PLATFORM_WINDOWS) && !defined(__MINGW32__)
        return _InterlockedExchangeAdd((long volatile*)value, (long)add);
    #elif defined(RMT_PLATFORM_POSIX) || defined(__MINGW32__)
        return __sync_fetch_and_add(value, add);
    #endif
}


static void AtomicSub(rmtS32 volatile* value, rmtS32 sub)
{
    // Not all platforms have an implementation so just negate and add
    AtomicAdd(value, -sub);
}


// Compiler write fences (windows implementation)
static void WriteFence()
{
#if defined(RMT_PLATFORM_WINDOWS) && !defined(__MINGW32__)
    _WriteBarrier();
#elif defined (__clang__)
	__asm__ volatile("" : : : "memory");
#else
    asm volatile ("" : : : "memory");
#endif
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @NEW: New/Delete operators with error values for simplifying object create/destroy
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



// Ensures the pointer is non-NULL, calls the destructor, frees memory and sets the pointer to NULL
#define Delete(type, obj)           \
    if (obj != NULL)                \
    {                               \
        type##_Destructor(obj);     \
        rmtFree(obj);               \
        obj = NULL;                 \
    }


// New is implemented in terms of two begin/end macros
// New will allocate enough space for the object and call the constructor
// If allocation fails the constructor won't be called
// If the constructor fails, the destructor is called and memory is released
// NOTE: Use of sizeof() requires that the type be defined at the point of call
// This is a disadvantage over requiring only a custom Create function
#define BeginNew(type, obj)                 \
    {                                       \
        obj = (type*)rmtMalloc(sizeof(type));  \
        if (obj == NULL)                    \
        {                                   \
            error = RMT_ERROR_MALLOC_FAIL;  \
        }                                   \
        else                                \
        {                                   \


#define EndNew(type, obj)                   \
            if (error != RMT_ERROR_NONE)    \
                Delete(type, obj);          \
        }                                   \
    }


// Specialisations for New with varying constructor parameter counts
#define New_0(type, obj)    \
    BeginNew(type, obj); error = type##_Constructor(obj); EndNew(type, obj)
#define New_1(type, obj, a0)    \
    BeginNew(type, obj); error = type##_Constructor(obj, a0); EndNew(type, obj)
#define New_2(type, obj, a0, a1)    \
    BeginNew(type, obj); error = type##_Constructor(obj, a0, a1); EndNew(type, obj)
#define New_3(type, obj, a0, a1, a2)    \
    BeginNew(type, obj); error = type##_Constructor(obj, a0, a1, a2); EndNew(type, obj)



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @VMBUFFER: Mirror Buffer using Virtual Memory for auto-wrap
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



typedef struct VirtualMirrorBuffer
{
    // Page-rounded size of the buffer without mirroring
    rmtU32 size;

    // Pointer to the first part of the mirror
    // The second part comes directly after at ptr+size bytes
    rmtU8* ptr;

#ifdef RMT_PLATFORM_WINDOWS
    HANDLE file_map_handle;
#endif

} VirtualMirrorBuffer;


#ifdef __ANDROID__
/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/ashmem.h>
#include <fcntl.h>
#include <string.h>
#define ASHMEM_DEVICE   "/dev/ashmem"

/*
 * ashmem_create_region - creates a new ashmem region and returns the file
 * descriptor, or <0 on error
 *
 * `name' is an optional label to give the region (visible in /proc/pid/maps)
 * `size' is the size of the region, in page-aligned bytes
 */
int ashmem_create_region(const char *name, size_t size)
{
        int fd, ret;

        fd = open(ASHMEM_DEVICE, O_RDWR);
        if (fd < 0)
                return fd;

        if (name) {
                char buf[ASHMEM_NAME_LEN] = {0};

                strncpy(buf, name, sizeof(buf));
                buf[sizeof(buf)-1] = 0;
                ret = ioctl(fd, ASHMEM_SET_NAME, buf);
                if (ret < 0)
                        goto error;
        }

        ret = ioctl(fd, ASHMEM_SET_SIZE, size);
        if (ret < 0)
                goto error;

        return fd;

error:
        close(fd);
        return ret;
}
#endif // __ANDROID__


static rmtError VirtualMirrorBuffer_Constructor(VirtualMirrorBuffer* buffer, rmtU32 size, int nb_attempts)
{
    static const rmtU32 k_64 = 64 * 1024;
    RMT_UNREFERENCED_PARAMETER(nb_attempts);

#ifdef RMT_PLATFORM_LINUX
    char path[] = "/dev/shm/ring-buffer-XXXXXX";
    int file_descriptor;
#endif

    // Round up to page-granulation; the nearest 64k boundary for now
    size = (size + k_64 - 1) / k_64 * k_64;

    // Set defaults
    buffer->size = size;
    buffer->ptr = NULL;
#ifdef RMT_PLATFORM_WINDOWS
    buffer->file_map_handle = INVALID_HANDLE_VALUE;
#endif

#ifdef RMT_PLATFORM_WINDOWS

    // Windows version based on https://gist.github.com/rygorous/3158316

    while (nb_attempts-- > 0)
    {
        rmtU8* desired_addr;

        // Create a file mapping for pointing to its physical address with multiple virtual pages
        buffer->file_map_handle = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            0,
            PAGE_READWRITE,
            0,
            size,
            0);
        if (buffer->file_map_handle == NULL)
            break;

        // Reserve two contiguous pages of virtual memory
        desired_addr = (rmtU8*)VirtualAlloc(0, size * 2, MEM_RESERVE, PAGE_NOACCESS);
        if (desired_addr == NULL)
            break;

        // Release the range immediately but retain the address for the next sequence of code to
        // try and map to it. In the mean-time some other OS thread may come along and allocate this
        // address range from underneath us so multiple attempts need to be made.
        VirtualFree(desired_addr, 0, MEM_RELEASE);

        // Immediately try to point both pages at the file mapping
        if (MapViewOfFileEx(buffer->file_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, size, desired_addr) == desired_addr &&
            MapViewOfFileEx(buffer->file_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, size, desired_addr + size) == desired_addr + size)
        {
            buffer->ptr = desired_addr;
            break;
        }

        // Failed to map the virtual pages; cleanup and try again
        CloseHandle(buffer->file_map_handle);
        buffer->file_map_handle = NULL;
    }

#endif

#ifdef RMT_PLATFORM_MACOS

    //
    // Mac version based on https://github.com/mikeash/MAMirroredQueue
    //
    // Copyright (c) 2010, Michael Ash
    // All rights reserved.
    //
    // Redistribution and use in source and binary forms, with or without modification, are permitted provided that
    // the following conditions are met:
    //
    // Redistributions of source code must retain the above copyright notice, this list of conditions and the following
    // disclaimer.
    //
    // Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
    // following disclaimer in the documentation and/or other materials provided with the distribution.
    // Neither the name of Michael Ash nor the names of its contributors may be used to endorse or promote products
    // derived from this software without specific prior written permission.
    //
    // THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    // INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    // ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    // INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    // GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    // LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    // OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    //

    while (nb_attempts-- > 0)
    {
        vm_prot_t cur_prot, max_prot;
        kern_return_t mach_error;
        rmtU8* ptr = NULL;
        rmtU8* target = NULL;

        // Allocate 2 contiguous pages of virtual memory
        if (vm_allocate(mach_task_self(), (vm_address_t*)&ptr, size * 2, VM_FLAGS_ANYWHERE) != KERN_SUCCESS)
            break;

        // Try to deallocate the last page, leaving its virtual memory address free
        target = ptr + size;
        if (vm_deallocate(mach_task_self(), (vm_address_t)target, size) != KERN_SUCCESS)
        {
            vm_deallocate(mach_task_self(), (vm_address_t)ptr, size * 2);
            break;
        }

        // Attempt to remap the page just deallocated to the buffer again
        mach_error = vm_remap(
            mach_task_self(),
            (vm_address_t*)&target,
            size,
            0,  // mask
            0,  // anywhere
            mach_task_self(),
            (vm_address_t)ptr,
            0,  //copy
            &cur_prot,
            &max_prot,
            VM_INHERIT_COPY);

        if (mach_error == KERN_NO_SPACE)
        {
            // Failed on this pass, cleanup and make another attempt
            if (vm_deallocate(mach_task_self(), (vm_address_t)ptr, size) != KERN_SUCCESS)
                break;
        }

        else if (mach_error == KERN_SUCCESS)
        {
            // Leave the loop on success
            buffer->ptr = ptr;
            break;
        }

        else
        {
            // Unknown error, can't recover
            vm_deallocate(mach_task_self(), (vm_address_t)ptr, size);
            break;
        }
    }

#endif

#ifdef RMT_PLATFORM_LINUX

    // Linux version based on now-defunct Wikipedia section http://en.wikipedia.org/w/index.php?title=Circular_buffer&oldid=600431497


#ifdef __ANDROID__
    file_descriptor = ashmem_create_region("remotery_shm", size * 2);
    if (file_descriptor < 0) {
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;
    }
#else
    // Create a unique temporary filename in the shared memory folder
    file_descriptor = mkstemp(path);
    if (file_descriptor < 0)
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;

    // Delete the name
    if (unlink(path))
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;

    // Set the file size to twice the buffer size
    // TODO: this 2x behaviour can be avoided with similar solution to Win/Mac
    if (ftruncate (file_descriptor, size * 2))
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;

#endif
    // Map 2 contiguous pages
    buffer->ptr = (rmtU8*)mmap(NULL, size * 2, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (buffer->ptr == MAP_FAILED)
    {
        buffer->ptr = NULL;
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;
    }

    // Point both pages to the same memory file
    if (mmap(buffer->ptr, size, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, file_descriptor, 0) != buffer->ptr ||
        mmap(buffer->ptr + size, size, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, file_descriptor, 0) != buffer->ptr + size)
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;

#endif

    // Cleanup if exceeded number of attempts or failed
    if (buffer->ptr == NULL)
        return RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL;

    return RMT_ERROR_NONE;
}


static void VirtualMirrorBuffer_Destructor(VirtualMirrorBuffer* buffer)
{
    assert(buffer != 0);

#ifdef RMT_PLATFORM_WINDOWS
    if (buffer->file_map_handle != NULL)
    {
        CloseHandle(buffer->file_map_handle);
        buffer->file_map_handle = NULL;
    }
#endif

#ifdef RMT_PLATFORM_MACOS
    if (buffer->ptr != NULL)
        vm_deallocate(mach_task_self(), (vm_address_t)buffer->ptr, buffer->size * 2);
#endif

#ifdef RMT_PLATFORM_LINUX
    if (buffer->ptr != NULL)
        munmap(buffer->ptr, buffer->size * 2);
#endif

    buffer->ptr = NULL;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @THREADS: Threads
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


typedef struct Thread_t rmtThread;
typedef rmtError(*ThreadProc)(rmtThread* thread);


struct Thread_t
{
    // OS-specific data
    #if defined(RMT_PLATFORM_WINDOWS)
        HANDLE handle;
    #else
        pthread_t handle;
    #endif

    // Callback executed when the thread is created
    ThreadProc callback;

    // Caller-specified parameter passed to Thread_Create
    void* param;

    // Error state returned from callback
    rmtError error;

    // External threads can set this to request an exit
    volatile rmtBool request_exit;

};


#if defined(RMT_PLATFORM_WINDOWS)

    static DWORD WINAPI ThreadProcWindows(LPVOID lpParameter)
    {
        rmtThread* thread = (rmtThread*)lpParameter;
        assert(thread != NULL);
        thread->error = thread->callback(thread);
        return thread->error == RMT_ERROR_NONE ? 1 : 0;
    }

#else
    static void* StartFunc( void* pArgs )
    {
        rmtThread* thread = (rmtThread*)pArgs;
        assert(thread != NULL);
        thread->error = thread->callback(thread);
        return NULL; // returned error not use, check thread->error.
    }
#endif


static int rmtThread_Valid(rmtThread* thread)
{
    assert(thread != NULL);

    #if defined(RMT_PLATFORM_WINDOWS)
        return thread->handle != NULL;
    #else
        return !pthread_equal(thread->handle, pthread_self());
    #endif
}


static rmtError rmtThread_Constructor(rmtThread* thread, ThreadProc callback, void* param)
{
    assert(thread != NULL);

    thread->callback = callback;
    thread->param = param;
    thread->error = RMT_ERROR_NONE;
    thread->request_exit = RMT_FALSE;

    // OS-specific thread creation

    #if defined (RMT_PLATFORM_WINDOWS)

        thread->handle = CreateThread(
            NULL,                               // lpThreadAttributes
            0,                                  // dwStackSize
            ThreadProcWindows,                  // lpStartAddress
            thread,                            // lpParameter
            0,                                  // dwCreationFlags
            NULL);                              // lpThreadId

        if (thread->handle == NULL)
            return RMT_ERROR_CREATE_THREAD_FAIL;

    #else

        int32_t error = pthread_create( &thread->handle, NULL, StartFunc, thread );
        if (error)
        {
            // Contents of 'thread' parameter to pthread_create() are undefined after
            // failure call so can't pre-set to invalid value before hand.
            thread->handle = pthread_self();
            return RMT_ERROR_CREATE_THREAD_FAIL;
        }

    #endif

    return RMT_ERROR_NONE;
}


static void rmtThread_RequestExit(rmtThread* thread)
{
    // Not really worried about memory barriers or delayed visibility to the target thread
    assert(thread != NULL);
    thread->request_exit = RMT_TRUE;
}


static void rmtThread_Join(rmtThread* thread)
{
    assert(rmtThread_Valid(thread));

    #if defined(RMT_PLATFORM_WINDOWS)
    WaitForSingleObject(thread->handle, INFINITE);
    #else
    pthread_join(thread->handle, NULL);
    #endif
}


static void rmtThread_Destructor(rmtThread* thread)
{
    assert(thread != NULL);

    if (rmtThread_Valid(thread))
    {
        // Shutdown the thread
        rmtThread_RequestExit(thread);
        rmtThread_Join(thread);

        // OS-specific release of thread resources

        #if defined(RMT_PLATFORM_WINDOWS)
        CloseHandle(thread->handle);
        thread->handle = NULL;
        #endif
    }
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @SAFEC: Safe C Library excerpts
   http://sourceforge.net/projects/safeclib/
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



/*------------------------------------------------------------------
 *
 * November 2008, Bo Berry
 *
 * Copyright (c) 2008-2011 by Cisco Systems, Inc
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */


// NOTE: Microsoft also has its own version of these functions so I'm do some hacky PP to remove them
#define strnlen_s strnlen_s_safe_c
#define strncat_s strncat_s_safe_c
#define strcpy_s strcpy_s_safe_c


#define RSIZE_MAX_STR (4UL << 10)   /* 4KB */
#define RCNEGATE(x) x


#define EOK             ( 0 )
#define ESNULLP         ( 400 )       /* null ptr                    */
#define ESZEROL         ( 401 )       /* length is zero              */
#define ESLEMAX         ( 403 )       /* length exceeds max          */
#define ESOVRLP         ( 404 )       /* overlap undefined           */
#define ESNOSPC         ( 406 )       /* not enough space for s2     */
#define ESUNTERM        ( 407 )       /* unterminated string         */
#define ESNOTFND        ( 409 )       /* not found                   */

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif

#if (!defined(_WIN64) && !defined(__APPLE__)) || (defined(__MINGW32__) && !defined(RSIZE_T_DEFINED))
typedef unsigned int rsize_t;
#endif

#if defined(RMT_PLATFORM_MACOS) && !defined(_RSIZE_T)
typedef __darwin_size_t rsize_t;
#endif

static rsize_t
strnlen_s (const char *dest, rsize_t dmax)
{
    rsize_t count;

    if (dest == NULL) {
        return RCNEGATE(0);
    }

    if (dmax == 0) {
        return RCNEGATE(0);
    }

    if (dmax > RSIZE_MAX_STR) {
        return RCNEGATE(0);
    }

    count = 0;
    while (*dest && dmax) {
        count++;
        dmax--;
        dest++;
    }

    return RCNEGATE(count);
}


static errno_t
strstr_s (char *dest, rsize_t dmax,
          const char *src, rsize_t slen, char **substring)
{
    rsize_t len;
    rsize_t dlen;
    int i;

    if (substring == NULL) {
        return RCNEGATE(ESNULLP);
    }
    *substring = NULL;

    if (dest == NULL) {
        return RCNEGATE(ESNULLP);
    }

    if (dmax == 0) {
        return RCNEGATE(ESZEROL);
    }

    if (dmax > RSIZE_MAX_STR) {
        return RCNEGATE(ESLEMAX);
    }

    if (src == NULL) {
        return RCNEGATE(ESNULLP);
    }

    if (slen == 0) {
        return RCNEGATE(ESZEROL);
    }

    if (slen > RSIZE_MAX_STR) {
        return RCNEGATE(ESLEMAX);
    }

    /*
     * src points to a string with zero length, or
     * src equals dest, return dest
     */
    if (*src == '\0' || dest == src) {
        *substring = dest;
        return RCNEGATE(EOK);
    }

    while (*dest && dmax) {
        i = 0;
        len = slen;
        dlen = dmax;

        while (src[i] && dlen) {

            /* not a match, not a substring */
            if (dest[i] != src[i]) {
                break;
            }

            /* move to the next char */
            i++;
            len--;
            dlen--;

            if (src[i] == '\0' || !len) {
                *substring = dest;
                return RCNEGATE(EOK);
            }
        }
        dest++;
        dmax--;
    }

    /*
     * substring was not found, return NULL
     */
    *substring = NULL;
    return RCNEGATE(ESNOTFND);
}


static errno_t
strncat_s (char *dest, rsize_t dmax, const char *src, rsize_t slen)
{
    const char *overlap_bumper;

    if (dest == NULL) {
        return RCNEGATE(ESNULLP);
    }

    if (src == NULL) {
        return RCNEGATE(ESNULLP);
    }

    if (slen > RSIZE_MAX_STR) {
        return RCNEGATE(ESLEMAX);
    }

    if (dmax == 0) {
        return RCNEGATE(ESZEROL);
    }

    if (dmax > RSIZE_MAX_STR) {
        return RCNEGATE(ESLEMAX);
    }

    /* hold base of dest in case src was not copied */

    if (dest < src) {
        overlap_bumper = src;

        /* Find the end of dest */
        while (*dest != '\0') {

            if (dest == overlap_bumper) {
                return RCNEGATE(ESOVRLP);
            }

            dest++;
            dmax--;
            if (dmax == 0) {
                return RCNEGATE(ESUNTERM);
            }
        }

        while (dmax > 0) {
            if (dest == overlap_bumper) {
                return RCNEGATE(ESOVRLP);
            }

            /*
             * Copying truncated before the source null is encountered
             */
            if (slen == 0) {
                *dest = '\0';
                return RCNEGATE(EOK);
            }

            *dest = *src;
            if (*dest == '\0') {
                return RCNEGATE(EOK);
            }

            dmax--;
            slen--;
            dest++;
            src++;
        }

    } else {
        overlap_bumper = dest;

        /* Find the end of dest */
        while (*dest != '\0') {

            /*
             * NOTE: no need to check for overlap here since src comes first
             * in memory and we're not incrementing src here.
             */
            dest++;
            dmax--;
            if (dmax == 0) {
                return RCNEGATE(ESUNTERM);
            }
        }

        while (dmax > 0) {
            if (src == overlap_bumper) {
                return RCNEGATE(ESOVRLP);
            }

            /*
             * Copying truncated
             */
            if (slen == 0) {
                *dest = '\0';
                return RCNEGATE(EOK);
            }

            *dest = *src;
            if (*dest == '\0') {
                return RCNEGATE(EOK);
            }

            dmax--;
            slen--;
            dest++;
            src++;
        }
    }

    /*
     * the entire src was not copied, so the string will be nulled.
     */
    return RCNEGATE(ESNOSPC);
}


errno_t
strcpy_s(char *dest, rsize_t dmax, const char *src)
{
    const char *overlap_bumper;

    if (dest == NULL) {
        return RCNEGATE(ESNULLP);
    }

    if (dmax == 0) {
        return RCNEGATE(ESZEROL);
    }

    if (dmax > RSIZE_MAX_STR) {
        return RCNEGATE(ESLEMAX);
    }

    if (src == NULL) {
        *dest = '\0';
        return RCNEGATE(ESNULLP);
    }

    if (dest == src) {
        return RCNEGATE(EOK);
    }

    if (dest < src) {
        overlap_bumper = src;

        while (dmax > 0) {
            if (dest == overlap_bumper) {
                return RCNEGATE(ESOVRLP);
            }

            *dest = *src;
            if (*dest == '\0') {
                return RCNEGATE(EOK);
            }

            dmax--;
            dest++;
            src++;
        }

    }
    else {
        overlap_bumper = dest;

        while (dmax > 0) {
            if (src == overlap_bumper) {
                return RCNEGATE(ESOVRLP);
            }

            *dest = *src;
            if (*dest == '\0') {
                return RCNEGATE(EOK);
            }

            dmax--;
            dest++;
            src++;
        }
    }

    /*
    * the entire src must have been copied, if not reset dest
    * to null the string.
    */
    return RCNEGATE(ESNOSPC);
}

#if !(defined(RMT_PLATFORM_LINUX) && RMT_USE_POSIX_THREADNAMES)

/* very simple integer to hex */
static const char* hex_encoding_table = "0123456789ABCDEF";

static void itoahex_s( char *dest, rsize_t dmax, rmtS32 value )
{
    rsize_t len;
    rmtS32 halfbytepos;

    halfbytepos = 8;

    /* strip leading 0's */
    while (halfbytepos > 1)
    {
        --halfbytepos;
        if (value >> (4 * halfbytepos) & 0xF)
        {
            ++halfbytepos;
            break;
        }
    }

    len = 0;
    while(len + 1 < dmax && halfbytepos > 0)
    {
        --halfbytepos;
        dest[len] = hex_encoding_table[value >> (4 * halfbytepos) & 0xF];
        ++len;
    }

    if (len < dmax)
    {
        dest[len] = 0;
    }
}

#endif

/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @OBJALLOC: Reusable Object Allocator
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



//
// All objects that require free-list-backed allocation need to inherit from this type.
//
typedef struct ObjectLink_s
{
    struct ObjectLink_s* volatile next;
} ObjectLink;


static void ObjectLink_Constructor(ObjectLink* link)
{
    assert(link != NULL);
    link->next = NULL;
}


typedef rmtError (*ObjConstructor)(void*);
typedef void (*ObjDestructor)(void*);


typedef struct
{
    // Object create/destroy parameters
    rmtU32 object_size;
    ObjConstructor constructor;
    ObjDestructor destructor;

    // Number of objects in the free list
    volatile rmtS32 nb_free;

    // Number of objects used by callers
    volatile rmtS32 nb_inuse;

    // Total allocation count
    volatile rmtS32 nb_allocated;

    ObjectLink* first_free;
} ObjectAllocator;


static rmtError ObjectAllocator_Constructor(ObjectAllocator* allocator, rmtU32 object_size, ObjConstructor constructor, ObjDestructor destructor)
{
    allocator->object_size = object_size;
    allocator->constructor = constructor;
    allocator->destructor = destructor;
    allocator->nb_free = 0;
    allocator->nb_inuse = 0;
    allocator->nb_allocated = 0;
    allocator->first_free = NULL;
    return RMT_ERROR_NONE;
}


static void ObjectAllocator_Destructor(ObjectAllocator* allocator)
{
    // Ensure everything has been released to the allocator
    assert(allocator != NULL);
    assert(allocator->nb_inuse == 0);

    // Destroy all objects released to the allocator
    while (allocator->first_free != NULL)
    {
        ObjectLink* next = allocator->first_free->next;
        assert(allocator->destructor != NULL);
        allocator->destructor(allocator->first_free);
        rmtFree(allocator->first_free);
        allocator->first_free = next;
    }
}


static void ObjectAllocator_Push(ObjectAllocator* allocator, ObjectLink* start, ObjectLink* end)
{
    assert(allocator != NULL);
    assert(start != NULL);
    assert(end != NULL);

    // CAS pop add range to the front of the list
    for (;;)
    {
        ObjectLink* old_link = (ObjectLink*)allocator->first_free;
        end->next = old_link;
        if (AtomicCompareAndSwapPointer((long* volatile*)&allocator->first_free, (long*)old_link, (long*)start) == RMT_TRUE)
            break;
    }
}


static ObjectLink* ObjectAllocator_Pop(ObjectAllocator* allocator)
{
    ObjectLink* link;

    assert(allocator != NULL);
    assert(allocator->first_free != NULL);

    // CAS pop from the front of the list
    for (;;)
    {
        ObjectLink* old_link = (ObjectLink*)allocator->first_free;
        ObjectLink* next_link = old_link->next;
        if (AtomicCompareAndSwapPointer((long* volatile*)&allocator->first_free, (long*)old_link, (long*)next_link) == RMT_TRUE)
        {
            link = old_link;
            break;
        }
    }

    link->next = NULL;

    return link;
}


static rmtError ObjectAllocator_Alloc(ObjectAllocator* allocator, void** object)
{
    // This function only calls the object constructor on initial malloc of an object

    assert(allocator != NULL);
    assert(object != NULL);

    // Has the free list run out?
    if (allocator->first_free == NULL)
    {
        rmtError error;

        // Allocate/construct a new object
        void* free_object = rmtMalloc( allocator->object_size );
        if (free_object == NULL)
            return RMT_ERROR_MALLOC_FAIL;
        assert(allocator->constructor != NULL);
        error = allocator->constructor(free_object);
        if (error != RMT_ERROR_NONE)
        {
            // Auto-teardown on failure
            assert(allocator->destructor != NULL);
            allocator->destructor(free_object);
            rmtFree(free_object);
            return error;
        }

        // Add to the free list
        ObjectAllocator_Push(allocator, (ObjectLink*)free_object, (ObjectLink*)free_object);
        AtomicAdd(&allocator->nb_allocated, 1);
        AtomicAdd(&allocator->nb_free, 1);
    }

    // Pull available objects from the free list
    *object = ObjectAllocator_Pop(allocator);
    AtomicSub(&allocator->nb_free, 1);
    AtomicAdd(&allocator->nb_inuse, 1);

    return RMT_ERROR_NONE;
}


static void ObjectAllocator_Free(ObjectAllocator* allocator, void* object)
{
    // Add back to the free-list
    assert(allocator != NULL);
    ObjectAllocator_Push(allocator, (ObjectLink*)object, (ObjectLink*)object);
    AtomicSub(&allocator->nb_inuse, 1);
    AtomicAdd(&allocator->nb_free, 1);
}


static void ObjectAllocator_FreeRange(ObjectAllocator* allocator, void* start, void* end, rmtU32 count)
{
    assert(allocator != NULL);
    ObjectAllocator_Push(allocator, (ObjectLink*)start, (ObjectLink*)end);
    AtomicSub(&allocator->nb_inuse, count);
    AtomicAdd(&allocator->nb_free, count);
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @DYNBUF: Dynamic Buffer
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



typedef struct
{
    rmtU32 alloc_granularity;

    rmtU32 bytes_allocated;
    rmtU32 bytes_used;

    rmtU8* data;
} Buffer;


static rmtError Buffer_Constructor(Buffer* buffer, rmtU32 alloc_granularity)
{
    assert(buffer != NULL);
    buffer->alloc_granularity = alloc_granularity;
    buffer->bytes_allocated = 0;
    buffer->bytes_used = 0;
    buffer->data = NULL;
    return RMT_ERROR_NONE;
}


static void Buffer_Destructor(Buffer* buffer)
{
    assert(buffer != NULL);

    if (buffer->data != NULL)
    {
        rmtFree(buffer->data);
        buffer->data = NULL;
    }
}


static rmtError Buffer_Write(Buffer* buffer, void* data, rmtU32 length)
{
    assert(buffer != NULL);

    // Reallocate the buffer on overflow
    if (buffer->bytes_used + length > buffer->bytes_allocated)
    {
        // Calculate size increase rounded up to the requested allocation granularity
        rmtU32 g = buffer->alloc_granularity;
        rmtU32 a = buffer->bytes_allocated + length;
        a = a + ((g - 1) - ((a - 1) % g));
        buffer->bytes_allocated = a;
        buffer->data = (rmtU8*)rmtRealloc(buffer->data, buffer->bytes_allocated);
        if (buffer->data == NULL)
            return RMT_ERROR_MALLOC_FAIL;
    }

    // Copy all bytes
    memcpy(buffer->data + buffer->bytes_used, data, length);
    buffer->bytes_used += length;

    // NULL terminate (if possible) for viewing in debug
    if (buffer->bytes_used < buffer->bytes_allocated)
        buffer->data[buffer->bytes_used] = 0;

    return RMT_ERROR_NONE;
}


static rmtError Buffer_WriteStringZ(Buffer* buffer, rmtPStr string)
{
    assert(string != NULL);
    return Buffer_Write(buffer, (void*)string, (rmtU32)strnlen_s(string, 2048) + 1);
}


static void U32ToByteArray(rmtU8* dest, rmtU32 value)
{
    // Commit as little-endian
    dest[0] = value & 255;
    dest[1] = (value >> 8) & 255;
    dest[2] = (value >> 16) & 255;
    dest[3] = value >> 24;
}


static rmtError Buffer_WriteU32(Buffer* buffer, rmtU32 value)
{
    rmtU8 temp[4];
    U32ToByteArray(temp, value);
    return Buffer_Write(buffer, temp, sizeof(temp));
}


static rmtBool IsLittleEndian()
{
    // Not storing this in a global variable allows the compiler to more easily optimise
    // this away altogether.
    union
    {
        unsigned int i;
        unsigned char c[sizeof(unsigned int)];
    } u;
    u.i = 1;
    return u.c[0] == 1 ? RMT_TRUE : RMT_FALSE;
}


static rmtError Buffer_WriteU64(Buffer* buffer, rmtU64 value)
{
    // Write as a double as Javascript DataView doesn't have a 64-bit integer read
    union
    {
        double d;
        unsigned char c[sizeof(double)];
    } u;
    char temp[8];
    u.d = (double)value;
    if (IsLittleEndian())
    {
        temp[0] = u.c[0];
        temp[1] = u.c[1];
        temp[2] = u.c[2];
        temp[3] = u.c[3];
        temp[4] = u.c[4];
        temp[5] = u.c[5];
        temp[6] = u.c[6];
        temp[7] = u.c[7];
    }
    else
    {
        temp[0] = u.c[7];
        temp[1] = u.c[6];
        temp[2] = u.c[5];
        temp[3] = u.c[4];
        temp[4] = u.c[3];
        temp[5] = u.c[2];
        temp[6] = u.c[1];
        temp[7] = u.c[0];
    }
    return Buffer_Write(buffer, u.c, sizeof(u.c));
}


static rmtError Buffer_WriteStringWithLength(Buffer* buffer, rmtPStr string)
{
    rmtU32 length = (rmtU32)strnlen_s(string, 2048);
    rmtError error;

    error = Buffer_WriteU32(buffer, length);
    if (error != RMT_ERROR_NONE)
        return error;

    return Buffer_Write(buffer, (void*)string, length);
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @HASHTABLE: Integer pair hash map for inserts/finds. No removes for added simplicity.
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#define RMT_NOT_FOUND 0xFFFFFFFF


typedef struct
{
    // Non-zero, pre-hashed key
    rmtU32 key;

    // Value that's not equal to RMT_NOT_FOUND
    rmtU32 value;
} HashSlot;


typedef struct
{
    // Stats
    rmtU32 max_nb_slots;
    rmtU32 nb_slots;

    // Data
    HashSlot* slots;
} rmtHashTable;


static rmtError rmtHashTable_Constructor(rmtHashTable* table, rmtU32 max_nb_slots)
{
    // Default initialise
    assert(table != NULL);
    table->max_nb_slots = max_nb_slots;
    table->nb_slots = 0;

    // Allocate and clear the hash slots
    table->slots = (HashSlot*)rmtMalloc(table->max_nb_slots * sizeof(HashSlot));
    if (table->slots == NULL)
        return RMT_ERROR_MALLOC_FAIL;
    memset(table->slots, 0, table->max_nb_slots * sizeof(HashSlot));

    return RMT_ERROR_NONE;
}


static void rmtHashTable_Destructor(rmtHashTable* table)
{
    assert(table != NULL);

    if (table->slots != NULL)
    {
        rmtFree(table->slots);
        table->slots = NULL;
    }
}


static rmtError rmtHashTable_Resize(rmtHashTable* table);


static rmtError rmtHashTable_Insert(rmtHashTable* table, rmtU32 key, rmtU32 value)
{
    HashSlot* slot = NULL;
    rmtError error = RMT_ERROR_NONE;

    // Calculate initial slot location for this key
    rmtU32 index_mask = table->max_nb_slots - 1;
    rmtU32 index = key & index_mask;

    assert(key != 0);
    assert(value != RMT_NOT_FOUND);

    // Linear probe for free slot, reusing any existing key matches
    // There will always be at least one free slot due to load factor management
    while (table->slots[index].key)
    {
        if (table->slots[index].key == key)
        {
            // Counter occupied slot increments below
            table->nb_slots--;
            break;
        }

        index = (index + 1) & index_mask;
    }

    // Just verify that I've got no errors in the code above
    assert(index < table->max_nb_slots);

    // Add to the table
    slot = table->slots + index;
    slot->key = key;
    slot->value = value;
    table->nb_slots++;

    // Resize when load factor is greater than 2/3
    if (table->nb_slots > (table->max_nb_slots * 2) / 3)
        error = rmtHashTable_Resize(table);

    return error;
}


static rmtError rmtHashTable_Resize(rmtHashTable* table)
{
    rmtU32 old_max_nb_slots = table->max_nb_slots;
    HashSlot* new_slots = NULL;
    HashSlot* old_slots = table->slots;

    // Increase the table size
    rmtU32 new_max_nb_slots = table->max_nb_slots;
    if (new_max_nb_slots < 8192 * 4)
        new_max_nb_slots *= 4;
    else
        new_max_nb_slots *= 2;

    // Allocate and clear a new table
    new_slots = (HashSlot*)rmtMalloc(new_max_nb_slots * sizeof(HashSlot));
    if (new_slots == NULL)
        return RMT_ERROR_MALLOC_FAIL;
    memset(new_slots, 0, new_max_nb_slots * sizeof(HashSlot));

    // Update fields of the table after successful allocation only
    table->slots = new_slots;
    table->max_nb_slots = new_max_nb_slots;
    table->nb_slots = 0;

    // Reinsert all objects into the new table
    for (rmtU32 i = 0; i < old_max_nb_slots; i++)
    {
        HashSlot* slot = old_slots + i;
        if (slot->key != 0)
            rmtHashTable_Insert(table, slot->key, slot->key);
    }

    free(old_slots);

    return RMT_ERROR_NONE;
}


static rmtU32 rmtHashTable_Find(rmtHashTable* table, rmtU32 key)
{
    // Calculate initial slot location for this key
    rmtU32 index_mask = table->max_nb_slots - 1;
    rmtU32 index = key & index_mask;

    // Linear probe for matching hash
    while (table->slots[index].key)
    {
        HashSlot* slot = table->slots + index;

        if (slot->key == key)
            return slot->value;

        index = (index + 1) & index_mask;
    }

    return RMT_NOT_FOUND;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @STRINGTABLE: Map from string hash to string offset in local buffer
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



typedef struct
{
    // Growable dynamic array of strings added so far
    Buffer* text;

    // Map from text hash to text location in the buffer
    rmtHashTable* text_map;
} StringTable;


static rmtError StringTable_Constructor(StringTable* table)
{
    rmtError error;

    // Default initialise
    assert(table != NULL);
    table->text = NULL;
    table->text_map = NULL;

    // Allocate reasonably storage for initial sample names

    New_1(Buffer, table->text, 8 * 1024);
    if (error != RMT_ERROR_NONE)
        return error;

    New_1(rmtHashTable, table->text_map, 1 * 1024);
    if (error != RMT_ERROR_NONE)
        return error;

    return RMT_ERROR_NONE;
}


static void StringTable_Destructor(StringTable* table)
{
    assert(table != NULL);

    Delete(rmtHashTable, table->text_map);
    Delete(Buffer, table->text);
}


static rmtPStr StringTable_Find(StringTable* table, rmtU32 name_hash)
{
    rmtU32 text_offset = rmtHashTable_Find(table->text_map, name_hash);
    if (text_offset != RMT_NOT_FOUND)
        return (rmtPStr)(table->text->data + text_offset);
    return NULL;
}


static void StringTable_Insert(StringTable* table, rmtU32 name_hash, rmtPStr name)
{
    // Only add to the buffer if the string isn't already there
    rmtU32 text_offset = rmtHashTable_Find(table->text_map, name_hash);
    if (text_offset == RMT_NOT_FOUND)
    {
        // TODO: Allocation errors aren't being passed on to the caller
        text_offset = table->text->bytes_used;
        Buffer_WriteStringZ(table->text, name);
        rmtHashTable_Insert(table->text_map, name_hash, text_offset);
    }
}


/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @SOCKETS: Sockets TCP/IP Wrapper
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#ifndef RMT_PLATFORM_WINDOWS
    typedef int SOCKET;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR   -1
    #define SD_SEND SHUT_WR
    #define closesocket close
#endif


typedef struct
{
    SOCKET socket;
} TCPSocket;


typedef struct
{
    rmtBool can_read;
    rmtBool can_write;
    rmtError error_state;
} SocketStatus;


//
// Function prototypes
//
static void TCPSocket_Close(TCPSocket* tcp_socket);


static rmtError InitialiseNetwork()
{
    #ifdef RMT_PLATFORM_WINDOWS

        WSADATA wsa_data;
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
            return RMT_ERROR_SOCKET_INIT_NETWORK_FAIL;
        if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
            return RMT_ERROR_SOCKET_INIT_NETWORK_FAIL;

        return RMT_ERROR_NONE;

    #else

        return RMT_ERROR_NONE;

    #endif
}


static void ShutdownNetwork()
{
    #ifdef RMT_PLATFORM_WINDOWS
        WSACleanup();
    #endif
}


static rmtError TCPSocket_Constructor(TCPSocket* tcp_socket)
{
    assert(tcp_socket != NULL);
    tcp_socket->socket = INVALID_SOCKET;
    return InitialiseNetwork();
}


static void TCPSocket_Destructor(TCPSocket* tcp_socket)
{
    assert(tcp_socket != NULL);
    TCPSocket_Close(tcp_socket);
    ShutdownNetwork();
}


static rmtError TCPSocket_RunServer(TCPSocket* tcp_socket, rmtU16 port, rmtBool limit_connections_to_localhost)
{
    SOCKET s = INVALID_SOCKET;
    struct sockaddr_in sin;
    int enable = 1;
    #ifdef RMT_PLATFORM_WINDOWS
        u_long nonblock = 1;
    #endif

    memset(&sin, 0, sizeof(sin) );
    assert(tcp_socket != NULL);

    // Try to create the socket
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == SOCKET_ERROR)
        return RMT_ERROR_SOCKET_CREATE_FAIL;

    // set SO_REUSEADDR so binding doesn't fail when restarting the application
    // (otherwise the same port can't be reused within TIME_WAIT)
    // I'm not checking for errors because if this fails (unlikely) we might still
    // be able to bind to the socket anyway
    #ifdef RMT_PLATFORM_POSIX
        setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    #elif defined(RMT_PLATFORM_WINDOWS)
        // windows also needs SO_EXCLUSEIVEADDRUSE,
        // see http://www.andy-pearce.com/blog/posts/2013/Feb/so_reuseaddr-on-windows/
        setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&enable, sizeof(enable));
        enable = 1;
        setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *)&enable, sizeof(enable));
    #endif

    // Bind the socket to the incoming port
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(limit_connections_to_localhost ? INADDR_LOOPBACK : INADDR_ANY);
    sin.sin_port = htons(port);
    if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
        return RMT_ERROR_SOCKET_BIND_FAIL;

    // Connection is valid, remaining code is socket state modification
    tcp_socket->socket = s;

    // Enter a listening state with a backlog of 1 connection
    if (listen(s, 1) == SOCKET_ERROR)
        return RMT_ERROR_SOCKET_LISTEN_FAIL;

    // Set as non-blocking
    #ifdef RMT_PLATFORM_WINDOWS
        if (ioctlsocket(tcp_socket->socket, FIONBIO, &nonblock) == SOCKET_ERROR)
            return RMT_ERROR_SOCKET_SET_NON_BLOCKING_FAIL;
    #else
        if (fcntl(tcp_socket->socket, F_SETFL, O_NONBLOCK) == SOCKET_ERROR)
            return RMT_ERROR_SOCKET_SET_NON_BLOCKING_FAIL;
    #endif

    return RMT_ERROR_NONE;
}


static void TCPSocket_Close(TCPSocket* tcp_socket)
{
    assert(tcp_socket != NULL);

    if (tcp_socket->socket != INVALID_SOCKET)
    {
        // Shutdown the connection, stopping all sends
        int result = shutdown(tcp_socket->socket, SD_SEND);
        if (result != SOCKET_ERROR)
        {
            // Keep receiving until the peer closes the connection
            int total = 0;
            char temp_buf[128];
            while (result > 0)
            {
                result = (int)recv(tcp_socket->socket, temp_buf, sizeof(temp_buf), 0);
                total += result;
            }
        }

        // Close the socket and issue a network shutdown request
        closesocket(tcp_socket->socket);
        tcp_socket->socket = INVALID_SOCKET;
    }
}


static SocketStatus TCPSocket_PollStatus(TCPSocket* tcp_socket)
{
    SocketStatus status;
    fd_set fd_read, fd_write, fd_errors;
    struct timeval tv;

    status.can_read = RMT_FALSE;
    status.can_write = RMT_FALSE;
    status.error_state = RMT_ERROR_NONE;

    assert(tcp_socket != NULL);
    if (tcp_socket->socket == INVALID_SOCKET)
    {
        status.error_state = RMT_ERROR_SOCKET_INVALID_POLL;
        return status;
    }

    // Set read/write/error markers for the socket
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_errors);
#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4127) // warning C4127: conditional expression is constant
#endif // _MSC_VER
    FD_SET(tcp_socket->socket, &fd_read);
    FD_SET(tcp_socket->socket, &fd_write);
    FD_SET(tcp_socket->socket, &fd_errors);
#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

    // Poll socket status without blocking
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (select(((int)tcp_socket->socket)+1, &fd_read, &fd_write, &fd_errors, &tv) == SOCKET_ERROR)
    {
        status.error_state = RMT_ERROR_SOCKET_SELECT_FAIL;
        return status;
    }

    status.can_read = FD_ISSET(tcp_socket->socket, &fd_read) != 0 ? RMT_TRUE : RMT_FALSE;
    status.can_write = FD_ISSET(tcp_socket->socket, &fd_write) != 0 ? RMT_TRUE : RMT_FALSE;
    status.error_state = FD_ISSET(tcp_socket->socket, &fd_errors) != 0 ? RMT_ERROR_SOCKET_POLL_ERRORS : RMT_ERROR_NONE;
    return status;
}


static rmtError TCPSocket_AcceptConnection(TCPSocket* tcp_socket, TCPSocket** client_socket)
{
    SocketStatus status;
    SOCKET s;
    rmtError error;

    // Ensure there is an incoming connection
    assert(tcp_socket != NULL);
    status = TCPSocket_PollStatus(tcp_socket);
    if (status.error_state != RMT_ERROR_NONE || !status.can_read)
        return status.error_state;

    // Accept the connection
    s = accept(tcp_socket->socket, 0, 0);
    if (s == SOCKET_ERROR)
        return RMT_ERROR_SOCKET_ACCEPT_FAIL;

#ifdef SO_NOSIGPIPE
    // On POSIX systems, send() may send a SIGPIPE signal when writing to an
    // already closed connection. By setting this option, we prevent the
    // signal from being emitted and send will instead return an error and set
    // errno to EPIPE.
    //
    // This is supported on BSD platforms and not on Linux.
    {
        int flag = 1;
        setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &flag, sizeof(flag));
    }
#endif
    // Create a client socket for the new connection
    assert(client_socket != NULL);
    New_0(TCPSocket, *client_socket);
    if (error != RMT_ERROR_NONE)
        return error;
    (*client_socket)->socket = s;

    return RMT_ERROR_NONE;
}


static int TCPSocketWouldBlock()
{
#ifdef RMT_PLATFORM_WINDOWS
    DWORD error = WSAGetLastError();
    return (error == WSAEWOULDBLOCK);
 #else
    int error = errno;
    return (error == EAGAIN || error == EWOULDBLOCK);
#endif

}


static rmtError TCPSocket_Send(TCPSocket* tcp_socket, const void* data, rmtU32 length, rmtU32 timeout_ms)
{
    SocketStatus status;
    char* cur_data = NULL;
    char* end_data = NULL;
    rmtU32 start_ms = 0;
    rmtU32 cur_ms = 0;

    assert(tcp_socket != NULL);

    start_ms = msTimer_Get();

    // Loop until timeout checking whether data can be written
    status.can_write = RMT_FALSE;
    while (!status.can_write)
    {
        status = TCPSocket_PollStatus(tcp_socket);
        if (status.error_state != RMT_ERROR_NONE)
            return status.error_state;

        cur_ms = msTimer_Get();
        if (cur_ms - start_ms > timeout_ms)
            return RMT_ERROR_SOCKET_SEND_TIMEOUT;
    }

    cur_data = (char*)data;
    end_data = cur_data + length;

    while (cur_data < end_data)
    {
        // Attempt to send the remaining chunk of data
        int bytes_sent;
        int send_flags = 0;
#ifdef MSG_NOSIGNAL
        // On Linux this prevents send from emitting a SIGPIPE signal
        // Equivalent on BSD to the SO_NOSIGPIPE option.
        send_flags = MSG_NOSIGNAL;
#endif
        bytes_sent = (int)send(tcp_socket->socket, cur_data, (int)(end_data - cur_data), send_flags);

        if (bytes_sent == SOCKET_ERROR || bytes_sent == 0)
        {
            // Close the connection if sending fails for any other reason other than blocking
            if (bytes_sent != 0 && !TCPSocketWouldBlock())
                return RMT_ERROR_SOCKET_SEND_FAIL;

            // First check for tick-count overflow and reset, giving a slight hitch every 49.7 days
            cur_ms = msTimer_Get();
            if (cur_ms < start_ms)
            {
                start_ms = cur_ms;
                continue;
            }

            //
            // Timeout can happen when:
            //
            //    1) endpoint is no longer there
            //    2) endpoint can't consume quick enough
            //    3) local buffers overflow
            //
            // As none of these are actually errors, we have to pass this timeout back to the caller.
            //
            // TODO: This strategy breaks down if a send partially completes and then times out!
            //
            if (cur_ms - start_ms > timeout_ms)
            {
                return RMT_ERROR_SOCKET_SEND_TIMEOUT;
            }
        }
        else
        {
            // Jump over the data sent
            cur_data += bytes_sent;
        }
    }

    return RMT_ERROR_NONE;
}


static rmtError TCPSocket_Receive(TCPSocket* tcp_socket, void* data, rmtU32 length, rmtU32 timeout_ms)
{
    SocketStatus status;
    char* cur_data = NULL;
    char* end_data = NULL;
    rmtU32 start_ms = 0;
    rmtU32 cur_ms = 0;

    assert(tcp_socket != NULL);

    // Ensure there is data to receive
    status = TCPSocket_PollStatus(tcp_socket);
    if (status.error_state != RMT_ERROR_NONE)
        return status.error_state;
    if (!status.can_read)
        return RMT_ERROR_SOCKET_RECV_NO_DATA;

    cur_data = (char*)data;
    end_data = cur_data + length;

    // Loop until all data has been received
    start_ms = msTimer_Get();
    while (cur_data < end_data)
    {
        int bytes_received = (int)recv(tcp_socket->socket, cur_data, (int)(end_data - cur_data), 0);

        if (bytes_received == SOCKET_ERROR || bytes_received == 0)
        {
            // Close the connection if receiving fails for any other reason other than blocking
            if (bytes_received != 0 && !TCPSocketWouldBlock())
                return RMT_ERROR_SOCKET_RECV_FAILED;

            // First check for tick-count overflow and reset, giving a slight hitch every 49.7 days
            cur_ms = msTimer_Get();
            if (cur_ms < start_ms)
            {
                start_ms = cur_ms;
                continue;
            }

            //
            // Timeout can happen when:
            //
            //    1) data is delayed by sender
            //    2) sender fails to send a complete set of packets
            //
            // As not all of these scenarios are errors, we need to pass this information back to the caller.
            //
            // TODO: This strategy breaks down if a receive partially completes and then times out!
            //
            if (cur_ms - start_ms > timeout_ms)
            {
                return RMT_ERROR_SOCKET_RECV_TIMEOUT;
            }
        }
        else
        {
            // Jump over the data received
            cur_data += bytes_received;
        }
    }

    return RMT_ERROR_NONE;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @SHA1: SHA-1 Cryptographic Hash Function
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


//
// Typed to allow enforced data size specification
//
typedef struct
{
    rmtU8 data[20];
} SHA1;


/*
 Copyright (c) 2011, Micael Hildenborg
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Micael Hildenborg nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY Micael Hildenborg ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL Micael Hildenborg BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 Contributors:
 Gustav
 Several members in the gamedev.se forum.
 Gregory Petrosyan
 */


// Rotate an integer value to left.
static unsigned int rol(const unsigned int value, const unsigned int steps)
{
    return ((value << steps) | (value >> (32 - steps)));
}


// Sets the first 16 integers in the buffert to zero.
// Used for clearing the W buffert.
static void clearWBuffert(unsigned int* buffert)
{
    int pos;
    for (pos = 16; --pos >= 0;)
    {
        buffert[pos] = 0;
    }
}

static void innerHash(unsigned int* result, unsigned int* w)
{
    unsigned int a = result[0];
    unsigned int b = result[1];
    unsigned int c = result[2];
    unsigned int d = result[3];
    unsigned int e = result[4];

    int round = 0;

    #define sha1macro(func,val) \
    { \
        const unsigned int t = rol(a, 5) + (func) + e + val + w[round]; \
        e = d; \
        d = c; \
        c = rol(b, 30); \
        b = a; \
        a = t; \
    }

    while (round < 16)
    {
        sha1macro((b & c) | (~b & d), 0x5a827999)
        ++round;
    }
    while (round < 20)
    {
        w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1macro((b & c) | (~b & d), 0x5a827999)
        ++round;
    }
    while (round < 40)
    {
        w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1macro(b ^ c ^ d, 0x6ed9eba1)
        ++round;
    }
    while (round < 60)
    {
        w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1macro((b & c) | (b & d) | (c & d), 0x8f1bbcdc)
        ++round;
    }
    while (round < 80)
    {
        w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1macro(b ^ c ^ d, 0xca62c1d6)
        ++round;
    }

    #undef sha1macro

    result[0] += a;
    result[1] += b;
    result[2] += c;
    result[3] += d;
    result[4] += e;
}


static void calc(const void* src, const int bytelength, unsigned char* hash)
{
    int roundPos;
    int lastBlockBytes;
    int hashByte;

    // Init the result array.
    unsigned int result[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

    // Cast the void src pointer to be the byte array we can work with.
    const unsigned char* sarray = (const unsigned char*) src;

    // The reusable round buffer
    unsigned int w[80];

    // Loop through all complete 64byte blocks.
    const int endOfFullBlocks = bytelength - 64;
    int endCurrentBlock;
    int currentBlock = 0;

    while (currentBlock <= endOfFullBlocks)
    {
        endCurrentBlock = currentBlock + 64;

        // Init the round buffer with the 64 byte block data.
        for (roundPos = 0; currentBlock < endCurrentBlock; currentBlock += 4)
        {
            // This line will swap endian on big endian and keep endian on little endian.
            w[roundPos++] = (unsigned int) sarray[currentBlock + 3]
                | (((unsigned int) sarray[currentBlock + 2]) << 8)
                | (((unsigned int) sarray[currentBlock + 1]) << 16)
                | (((unsigned int) sarray[currentBlock]) << 24);
        }
        innerHash(result, w);
    }

    // Handle the last and not full 64 byte block if existing.
    endCurrentBlock = bytelength - currentBlock;
    clearWBuffert(w);
    lastBlockBytes = 0;
    for (;lastBlockBytes < endCurrentBlock; ++lastBlockBytes)
    {
        w[lastBlockBytes >> 2] |= (unsigned int) sarray[lastBlockBytes + currentBlock] << ((3 - (lastBlockBytes & 3)) << 3);
    }
    w[lastBlockBytes >> 2] |= 0x80U << ((3 - (lastBlockBytes & 3)) << 3);
    if (endCurrentBlock >= 56)
    {
        innerHash(result, w);
        clearWBuffert(w);
    }
    w[15] = bytelength << 3;
    innerHash(result, w);

    // Store hash in result pointer, and make sure we get in in the correct order on both endian models.
    for (hashByte = 20; --hashByte >= 0;)
    {
        hash[hashByte] = (result[hashByte >> 2] >> (((3 - hashByte) & 0x3) << 3)) & 0xff;
    }
}


static SHA1 SHA1_Calculate(const void* src, unsigned int length)
{
    SHA1 hash;
    assert((int)length >= 0);
    calc(src, length, hash.data);
    return hash;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @BASE64: Base-64 encoder
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



static const char* b64_encoding_table =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";


static rmtU32 Base64_CalculateEncodedLength(rmtU32 length)
{
    // ceil(l * 4/3)
    return 4 * ((length + 2) / 3);
}


static void Base64_Encode(const rmtU8* in_bytes, rmtU32 length, rmtU8* out_bytes)
{
    rmtU32 i;
    rmtU32 encoded_length;
    rmtU32 remaining_bytes;

    rmtU8* optr = out_bytes;

    for (i = 0; i < length; )
    {
        // Read input 3 values at a time, null terminating
        rmtU32 c0 = i < length ? in_bytes[i++] : 0;
        rmtU32 c1 = i < length ? in_bytes[i++] : 0;
        rmtU32 c2 = i < length ? in_bytes[i++] : 0;

        // Encode 4 bytes for ever 3 input bytes
        rmtU32 triple = (c0 << 0x10) + (c1 << 0x08) + c2;
        *optr++ = b64_encoding_table[(triple >> 3 * 6) & 0x3F];
        *optr++ = b64_encoding_table[(triple >> 2 * 6) & 0x3F];
        *optr++ = b64_encoding_table[(triple >> 1 * 6) & 0x3F];
        *optr++ = b64_encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    // Pad output to multiple of 3 bytes with terminating '='
    encoded_length = Base64_CalculateEncodedLength(length);
    remaining_bytes = (3 - ((length + 2) % 3)) - 1;
    for (i = 0; i < remaining_bytes; i++)
        out_bytes[encoded_length - 1 - i] = '=';

    // Null terminate
    out_bytes[encoded_length] = 0;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @MURMURHASH: MurmurHash3
   https://code.google.com/p/smhasher
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
//-----------------------------------------------------------------------------


static rmtU32 rotl32(rmtU32 x, rmtS8 r)
{
    return (x << r) | (x >> (32 - r));
}


// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here
static rmtU32 getblock32(const rmtU32* p, int i)
{
    return p[i];
}


// Finalization mix - force all bits of a hash block to avalanche
static rmtU32 fmix32(rmtU32 h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}


static rmtU32 MurmurHash3_x86_32(const void* key, int len, rmtU32 seed)
{
    const rmtU8* data = (const rmtU8*)key;
    const int nblocks = len / 4;

    rmtU32 h1 = seed;

    const rmtU32 c1 = 0xcc9e2d51;
    const rmtU32 c2 = 0x1b873593;

    int i;

    const rmtU32 * blocks = (const rmtU32 *)(data + nblocks*4);
    const rmtU8 * tail = (const rmtU8*)(data + nblocks*4);

    rmtU32 k1 = 0;

    //----------
    // body

    for (i = -nblocks; i; i++)
    {
        rmtU32 k2 = getblock32(blocks,i);

        k2 *= c1;
        k2 = rotl32(k2,15);
        k2 *= c2;

        h1 ^= k2;
        h1 = rotl32(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    //----------
    // tail

    switch(len & 3)
    {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
        k1 *= c1;
        k1 = rotl32(k1,15);
        k1 *= c2;
        h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len;

    h1 = fmix32(h1);

    return h1;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @WEBSOCKETS: WebSockets
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



enum WebSocketMode
{
    WEBSOCKET_NONE = 0,
    WEBSOCKET_TEXT = 1,
    WEBSOCKET_BINARY = 2,
};


typedef struct
{
    TCPSocket* tcp_socket;

    enum WebSocketMode mode;

    rmtU32 frame_bytes_remaining;
    rmtU32 mask_offset;

    union
    {
        rmtU8 mask[4];
        rmtU32 mask_u32;
    } data;

} WebSocket;


static void WebSocket_Close(WebSocket* web_socket);


static char* GetField(char* buffer, rsize_t buffer_length, rmtPStr field_name)
{
    char* field = NULL;
    char* buffer_end = buffer + buffer_length - 1;

    rsize_t field_length = strnlen_s(field_name, buffer_length);
    if (field_length == 0)
        return NULL;

    // Search for the start of the field
    if (strstr_s(buffer, buffer_length, field_name, field_length, &field) != EOK)
        return NULL;

    // Field name is now guaranteed to be in the buffer so its safe to jump over it without hitting the bounds
    field += strlen(field_name);

    // Skip any trailing whitespace
    while (*field == ' ')
    {
        if (field >= buffer_end)
            return NULL;
        field++;
    }

    return field;
}


static const char websocket_guid[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
static const char websocket_response[] =
    "HTTP/1.1 101 Switching Protocols\r\n"
    "Upgrade: websocket\r\n"
    "Connection: Upgrade\r\n"
    "Sec-WebSocket-Accept: ";


static rmtError WebSocketHandshake(TCPSocket* tcp_socket, rmtPStr limit_host)
{
    rmtU32 start_ms, now_ms;

    // Parsing scratchpad
    char buffer[1024];
    char* buffer_ptr = buffer;
    int buffer_len = sizeof(buffer) - 1;
    char* buffer_end = buffer + buffer_len;

    char response_buffer[256];
    int response_buffer_len = sizeof(response_buffer) - 1;

    char* version;
    char* host;
    char* key;
    char* key_end;
    SHA1 hash;

    assert(tcp_socket != NULL);

    start_ms = msTimer_Get();

    // Really inefficient way of receiving the handshake data from the browser
    // Not really sure how to do this any better, as the termination requirement is \r\n\r\n
    while (buffer_ptr - buffer < buffer_len)
    {
        rmtError error = TCPSocket_Receive(tcp_socket, buffer_ptr, 1, 20);
        if (error == RMT_ERROR_SOCKET_RECV_FAILED)
            return error;

        // If there's a stall receiving the data, check for a handshake timeout
        if (error == RMT_ERROR_SOCKET_RECV_NO_DATA || error == RMT_ERROR_SOCKET_RECV_TIMEOUT)
        {
            now_ms = msTimer_Get();
            if (now_ms - start_ms > 1000)
                return RMT_ERROR_SOCKET_RECV_TIMEOUT;

            continue;
        }

        // Just in case new enums are added...
        assert(error == RMT_ERROR_NONE);

        if (buffer_ptr - buffer >= 4)
        {
            if (*(buffer_ptr - 3) == '\r' &&
                *(buffer_ptr - 2) == '\n' &&
                *(buffer_ptr - 1) == '\r' &&
                *(buffer_ptr - 0) == '\n')
                break;
        }

        buffer_ptr++;
    }
    *buffer_ptr = 0;

    // HTTP GET instruction
    if (memcmp(buffer, "GET", 3) != 0)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_NOT_GET;

    // Look for the version number and verify that it's supported
    version = GetField(buffer, buffer_len, "Sec-WebSocket-Version:");
    if (version == NULL)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_NO_VERSION;
    if (buffer_end - version < 2 || (version[0] != '8' && (version[0] != '1' || version[1] != '3')))
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_BAD_VERSION;

    // Make sure this connection comes from a known host
    host = GetField(buffer, buffer_len, "Host:");
    if (host == NULL)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_NO_HOST;
    if (limit_host != NULL)
    {
        rsize_t limit_host_len = strnlen_s(limit_host, 128);
        char* found = NULL;
        if (strstr_s(host, buffer_end - host, limit_host, limit_host_len, &found) != EOK)
            return RMT_ERROR_WEBSOCKET_HANDSHAKE_BAD_HOST;
    }

    // Look for the key start and null-terminate it within the receive buffer
    key = GetField(buffer, buffer_len, "Sec-WebSocket-Key:");
    if (key == NULL)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_NO_KEY;
    if (strstr_s(key, buffer_end - key, "\r\n", 2, &key_end) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_BAD_KEY;
    *key_end = 0;

    // Concatenate the browser's key with the WebSocket Protocol GUID and base64 encode
    // the hash, to prove to the browser that this is a bonafide WebSocket server
    buffer[0] = 0;
    if (strncat_s(buffer, buffer_len, key, key_end - key) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_STRING_FAIL;
    if (strncat_s(buffer, buffer_len, websocket_guid, sizeof(websocket_guid)) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_STRING_FAIL;
    hash = SHA1_Calculate(buffer, (rmtU32)strnlen_s(buffer, buffer_len));
    Base64_Encode(hash.data, sizeof(hash.data), (rmtU8*)buffer);

    // Send the response back to the server with a longer timeout than usual
    response_buffer[0] = 0;
    if (strncat_s(response_buffer, response_buffer_len, websocket_response, sizeof(websocket_response)) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_STRING_FAIL;
    if (strncat_s(response_buffer, response_buffer_len, buffer, buffer_len) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_STRING_FAIL;
    if (strncat_s(response_buffer, response_buffer_len, "\r\n\r\n", 4) != EOK)
        return RMT_ERROR_WEBSOCKET_HANDSHAKE_STRING_FAIL;

    return TCPSocket_Send(tcp_socket, response_buffer, (rmtU32)strnlen_s(response_buffer, response_buffer_len), 1000);
}


static rmtError WebSocket_Constructor(WebSocket* web_socket, TCPSocket* tcp_socket)
{
    rmtError error = RMT_ERROR_NONE;

    assert(web_socket != NULL);
    web_socket->tcp_socket = tcp_socket;
    web_socket->mode = WEBSOCKET_NONE;
    web_socket->frame_bytes_remaining = 0;
    web_socket->mask_offset = 0;
    web_socket->data.mask[0] = 0;
    web_socket->data.mask[1] = 0;
    web_socket->data.mask[2] = 0;
    web_socket->data.mask[3] = 0;

    // Caller can optionally specify which TCP socket to use
    if (web_socket->tcp_socket == NULL)
        New_0(TCPSocket, web_socket->tcp_socket);

    return error;
}


static void WebSocket_Destructor(WebSocket* web_socket)
{
    WebSocket_Close(web_socket);
}


static rmtError WebSocket_RunServer(WebSocket* web_socket, rmtU16 port, rmtBool limit_connections_to_localhost, enum WebSocketMode mode)
{
    // Create the server's listening socket
    assert(web_socket != NULL);
    web_socket->mode = mode;
    return TCPSocket_RunServer(web_socket->tcp_socket, port, limit_connections_to_localhost);
}


static void WebSocket_Close(WebSocket* web_socket)
{
    assert(web_socket != NULL);
    Delete(TCPSocket, web_socket->tcp_socket);
}


static SocketStatus WebSocket_PollStatus(WebSocket* web_socket)
{
    assert(web_socket != NULL);
    return TCPSocket_PollStatus(web_socket->tcp_socket);
}


static rmtError WebSocket_AcceptConnection(WebSocket* web_socket, WebSocket** client_socket)
{
    TCPSocket* tcp_socket = NULL;
    rmtError error;

    // Is there a waiting connection?
    assert(web_socket != NULL);
    error = TCPSocket_AcceptConnection(web_socket->tcp_socket, &tcp_socket);
    if (error != RMT_ERROR_NONE || tcp_socket == NULL)
        return error;

    // Need a successful handshake between client/server before allowing the connection
    // TODO: Specify limit_host
    error = WebSocketHandshake(tcp_socket, NULL);
    if (error != RMT_ERROR_NONE)
        return error;

    // Allocate and return a new client socket
    assert(client_socket != NULL);
    New_1(WebSocket, *client_socket, tcp_socket);
    if (error != RMT_ERROR_NONE)
        return error;

    (*client_socket)->mode = web_socket->mode;

    return RMT_ERROR_NONE;
}


static void WriteSize(rmtU32 size, rmtU8* dest, rmtU32 dest_size, rmtU32 dest_offset)
{
    int size_size = dest_size - dest_offset;
    rmtU32 i;
    for (i = 0; i < dest_size; i++)
    {
        int j = i - dest_offset;
        dest[i] = (j < 0) ? 0 : (size >> ((size_size - j - 1) * 8)) & 0xFF;
    }
}


static rmtError WebSocket_Send(WebSocket* web_socket, const void* data, rmtU32 length, rmtU32 timeout_ms)
{
    rmtError error;
    SocketStatus status;
    rmtU8 final_fragment, frame_type, frame_header[10];
    rmtU32 frame_header_size;

    assert(web_socket != NULL);

    // Can't send if there are socket errors
    status = WebSocket_PollStatus(web_socket);
    if (status.error_state != RMT_ERROR_NONE)
        return status.error_state;

    final_fragment = 0x1 << 7;
    frame_type = (rmtU8)web_socket->mode;
    frame_header[0] = final_fragment | frame_type;

    // Construct the frame header, correctly applying the narrowest size
    frame_header_size = 0;
    if (length <= 125)
    {
        frame_header_size = 2;
        frame_header[1] = (rmtU8)length;
    }
    else if (length <= 65535)
    {
        frame_header_size = 2 + 2;
        frame_header[1] = 126;
        WriteSize(length, frame_header + 2, 2, 0);
    }
    else
    {
        frame_header_size = 2 + 8;
        frame_header[1] = 127;
        WriteSize(length, frame_header + 2, 8, 4);
    }

    // Send frame header
    assert(data != NULL);
    error = TCPSocket_Send(web_socket->tcp_socket, frame_header, frame_header_size, timeout_ms);
    if (error != RMT_ERROR_NONE)
        return error;

    // Send frame data separately so that we don't have to allocate memory or memcpy it into
    // the same buffer as the header.
    // If this step times out then the frame data will be discarded and the browser will receive
    // an invalid frame without its data, forcing a disconnect error.
    // Before things get that far, flag this as a send fail and let the server schedule a graceful
    // disconnect.
    error = TCPSocket_Send(web_socket->tcp_socket, data, length, timeout_ms);
    if (error == RMT_ERROR_SOCKET_SEND_TIMEOUT)
        error = RMT_ERROR_SOCKET_SEND_FAIL;

    return error;
}


static rmtError ReceiveFrameHeader(WebSocket* web_socket)
{
    // TODO: Specify infinite timeout?

    rmtError error;
    rmtU8 msg_header[2] = { 0, 0 };
    int msg_length, size_bytes_remaining, i;
    rmtBool mask_present;

    assert(web_socket != NULL);

    // Get message header
    error = TCPSocket_Receive(web_socket->tcp_socket, msg_header, 2, 20);
    if (error != RMT_ERROR_NONE)
        return error;

    // Check for WebSocket Protocol disconnect
    if (msg_header[0] == 0x88)
        return RMT_ERROR_WEBSOCKET_DISCONNECTED;

    // Check that the client isn't sending messages we don't understand
    if (msg_header[0] != 0x81 && msg_header[0] != 0x82)
        return RMT_ERROR_WEBSOCKET_BAD_FRAME_HEADER;

    // Get message length and check to see if it's a marker for a wider length
    msg_length = msg_header[1] & 0x7F;
    size_bytes_remaining = 0;
    switch (msg_length)
    {
        case 126: size_bytes_remaining = 2; break;
        case 127: size_bytes_remaining = 8; break;
    }

    if (size_bytes_remaining > 0)
    {
        // Receive the wider bytes of the length
        rmtU8 size_bytes[4];
        error = TCPSocket_Receive(web_socket->tcp_socket, size_bytes, size_bytes_remaining, 20);
        if (error != RMT_ERROR_NONE)
            return RMT_ERROR_WEBSOCKET_BAD_FRAME_HEADER_SIZE;

        // Calculate new length, MSB first
        msg_length = 0;
        for (i = 0; i < size_bytes_remaining; i++)
            msg_length |= size_bytes[i] << ((size_bytes_remaining - 1 - i) * 8);
    }

    // Receive any message data masks
    mask_present = (msg_header[1] & 0x80) != 0 ? RMT_TRUE : RMT_FALSE;
    if (mask_present)
    {
        error = TCPSocket_Receive(web_socket->tcp_socket, web_socket->data.mask, 4, 20);
        if (error != RMT_ERROR_NONE)
            return error;
    }

    web_socket->frame_bytes_remaining = msg_length;
    web_socket->mask_offset = 0;

    return RMT_ERROR_NONE;
}


static rmtError WebSocket_Receive(WebSocket* web_socket, void* data, rmtU32* msg_len, rmtU32 length, rmtU32 timeout_ms)
{
    SocketStatus status;
    char* cur_data;
    char* end_data;
    rmtU32 start_ms, now_ms;
    rmtU32 bytes_to_read;
    rmtError error;

    assert(web_socket != NULL);

    // Can't read with any socket errors
    status = WebSocket_PollStatus(web_socket);
    if (status.error_state != RMT_ERROR_NONE)
        return status.error_state;

    cur_data = (char*)data;
    end_data = cur_data + length;

    start_ms = msTimer_Get();
    while (cur_data < end_data)
    {
        // Get next WebSocket frame if we've run out of data to read from the socket
        if (web_socket->frame_bytes_remaining == 0)
        {
            error = ReceiveFrameHeader(web_socket);
            if (error != RMT_ERROR_NONE)
                return error;

            // Set output message length only on initial receive
            if (msg_len != NULL)
                *msg_len = web_socket->frame_bytes_remaining;
        }

        // Read as much required data as possible
        bytes_to_read = web_socket->frame_bytes_remaining < length ? web_socket->frame_bytes_remaining : length;
        error = TCPSocket_Receive(web_socket->tcp_socket, cur_data, bytes_to_read, 20);
        if (error == RMT_ERROR_SOCKET_RECV_FAILED)
            return error;

        // If there's a stall receiving the data, check for timeout
        if (error == RMT_ERROR_SOCKET_RECV_NO_DATA || error == RMT_ERROR_SOCKET_RECV_TIMEOUT)
        {
            now_ms = msTimer_Get();
            if (now_ms - start_ms > timeout_ms)
                return RMT_ERROR_SOCKET_RECV_TIMEOUT;
            continue;
        }

        // Apply data mask
        if (web_socket->data.mask_u32 != 0)
        {
            rmtU32 i;
            for (i = 0; i < bytes_to_read; i++)
            {
                *((rmtU8*)cur_data + i) ^= web_socket->data.mask[web_socket->mask_offset & 3];
                web_socket->mask_offset++;
            }
        }

        cur_data += bytes_to_read;
        web_socket->frame_bytes_remaining -= bytes_to_read;
    }

    return RMT_ERROR_NONE;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @MESSAGEQ: Multiple producer, single consumer message queue
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


typedef enum MessageID
{
    MsgID_NotReady,
    MsgID_LogText,
    MsgID_SampleTree,
} MessageID;


typedef struct Message
{
    MessageID id;

    rmtU32 payload_size;

    // For telling which thread the message came from in the debugger
    struct ThreadSampler* thread_sampler;

    rmtU8 payload[1];
} Message;


// Multiple producer, single consumer message queue that uses its own data buffer
// to store the message data.
typedef struct rmtMessageQueue
{
    rmtU32 size;

    // The physical address of this data buffer is pointed to by two sequential
    // virtual memory pages, allowing automatic wrap-around of any reads or writes
    // that exceed the limits of the buffer.
    VirtualMirrorBuffer* data;

    // Read/write position never wrap allowing trivial overflow checks
    // with easier debugging
    rmtU32 read_pos;
    rmtU32 write_pos;

} rmtMessageQueue;


static rmtError rmtMessageQueue_Constructor(rmtMessageQueue* queue, rmtU32 size)
{
    rmtError error;

    assert(queue != NULL);

    // Set defaults
    queue->size = 0;
    queue->data = NULL;
    queue->read_pos = 0;
    queue->write_pos = 0;

    New_2(VirtualMirrorBuffer, queue->data, size, 10);
    if (error != RMT_ERROR_NONE)
        return error;

    // The mirror buffer needs to be page-aligned and will change the requested
    // size to match that.
    queue->size = queue->data->size;

    // Set the entire buffer to not ready message
    memset(queue->data->ptr, MsgID_NotReady, queue->size);

    return RMT_ERROR_NONE;
}


static void rmtMessageQueue_Destructor(rmtMessageQueue* queue)
{
    assert(queue != NULL);
    Delete(VirtualMirrorBuffer, queue->data);
}


static rmtU32 rmtMessageQueue_SizeForPayload(rmtU32 payload_size)
{
    // Add message header and align for ARM platforms
    rmtU32 size = sizeof(Message) + payload_size;
    size = (size + 3) & ~3U;
    return size;
}


static Message* rmtMessageQueue_AllocMessage(rmtMessageQueue* queue, rmtU32 payload_size, struct ThreadSampler* thread_sampler)
{
    Message* msg;

    rmtU32 write_size = rmtMessageQueue_SizeForPayload(payload_size);

    assert(queue != NULL);

    for (;;)
    {
        // Check for potential overflow
        rmtU32 s = queue->size;
        rmtU32 r = queue->read_pos;
        rmtU32 w = queue->write_pos;
        if ((int)(w - r) > ((int)(s - write_size)))
            return NULL;

        // Point to the newly allocated space
        msg = (Message*)(queue->data->ptr + (w & (s - 1)));

        // Increment the write position, leaving the loop if this is the thread that succeeded
        if (AtomicCompareAndSwap(&queue->write_pos, w, w + write_size) == RMT_TRUE)
        {
            // Safe to set payload size after thread claims ownership of this allocated range
            msg->payload_size = payload_size;
            msg->thread_sampler = thread_sampler;
            break;
        }
    }

    return msg;
}


static void rmtMessageQueue_CommitMessage(Message* message, MessageID id)
{
    assert(message != NULL);

    // Ensure message writes complete before commit
    WriteFence();

    // Setting the message ID signals to the consumer that the message is ready
    assert(message->id == MsgID_NotReady);
    message->id = id;
}


Message* rmtMessageQueue_PeekNextMessage(rmtMessageQueue* queue)
{
    Message* ptr;
    rmtU32 r;

    assert(queue != NULL);

    // First check that there are bytes queued
    if (queue->write_pos - queue->read_pos == 0)
        return NULL;

    // Messages are in the queue but may not have been commit yet
    // Messages behind this one may have been commit but it's not reachable until
    // the next one in the queue is ready.
    r = queue->read_pos & (queue->size - 1);
    ptr = (Message*)(queue->data->ptr + r);
    if (ptr->id != MsgID_NotReady)
        return ptr;

    return NULL;
}


static void rmtMessageQueue_ConsumeNextMessage(rmtMessageQueue* queue, Message* message)
{
    rmtU32 message_size;

    assert(queue != NULL);
    assert(message != NULL);

    // Setting the message ID to "not ready" serves as a marker to the consumer that even though
    // space has been allocated for a message, the message isn't ready to be consumed
    // yet.
    //
    // We can't do that when allocating the message because multiple threads will be fighting for
    // the same location. Instead, clear out any messages just read by the consumer before advancing
    // the read position so that a winning thread's allocation will inherit the "not ready" state.
    //
    // This costs some write bandwidth and has the potential to flush cache to other cores.
    message_size = rmtMessageQueue_SizeForPayload(message->payload_size);
    memset(message, MsgID_NotReady, message_size);

    // Ensure clear completes before advancing the read position
    WriteFence();
    queue->read_pos += message_size;
}


static rmtBool rmtMessageQueue_IsEmpty(rmtMessageQueue* queue)
{
    assert(queue != NULL);
    return queue->write_pos - queue->read_pos == 0;
}


/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @NETWORK: Network Server
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/


typedef rmtError (*Server_ReceiveHandler)(void*, char*, rmtU32);


typedef struct
{
    WebSocket* listen_socket;

    WebSocket* client_socket;

    rmtU32 last_ping_time;

    rmtU16 port;
    rmtBool limit_connections_to_localhost;

    // Handler for receiving messages from the client
    Server_ReceiveHandler receive_handler;
    void* receive_handler_context;
} Server;


static rmtError Server_CreateListenSocket(Server* server, rmtU16 port, rmtBool limit_connections_to_localhost)
{
    rmtError error = RMT_ERROR_NONE;

    New_1(WebSocket, server->listen_socket, NULL);
    if (error == RMT_ERROR_NONE)
        error = WebSocket_RunServer(server->listen_socket, port, limit_connections_to_localhost, WEBSOCKET_BINARY);

    return error;
}


static rmtError Server_Constructor(Server* server, rmtU16 port, rmtBool limit_connections_to_localhost)
{
    assert(server != NULL);
    server->listen_socket = NULL;
    server->client_socket = NULL;
    server->last_ping_time = 0;
    server->port = port;
    server->limit_connections_to_localhost = limit_connections_to_localhost;
    server->receive_handler = NULL;
    server->receive_handler_context = NULL;

    // Create the listening WebSocket
    return Server_CreateListenSocket(server, port, limit_connections_to_localhost);
}


static void Server_Destructor(Server* server)
{
    assert(server != NULL);
    Delete(WebSocket, server->client_socket);
    Delete(WebSocket, server->listen_socket);
}


static rmtBool Server_IsClientConnected(Server* server)
{
    assert(server != NULL);
    return server->client_socket != NULL ? RMT_TRUE : RMT_FALSE;
}


static void Server_DisconnectClient(Server* server)
{
    WebSocket* client_socket;

    assert(server != NULL);

    // NULL the variable before destroying the socket
    client_socket = server->client_socket;
    server->client_socket = NULL;
    WriteFence();
    Delete(WebSocket, client_socket);
}


static rmtError Server_Send(Server* server, const void* data, rmtU32 length, rmtU32 timeout)
{
    assert(server != NULL);
    if (Server_IsClientConnected(server))
    {
        rmtError error = WebSocket_Send(server->client_socket, data, length, timeout);
        if (error == RMT_ERROR_SOCKET_SEND_FAIL)
            Server_DisconnectClient(server);

        return error;
    }

    return RMT_ERROR_NONE;
}


static rmtError Server_ReceiveMessage(Server* server, char message_first_byte, rmtU32 message_length)
{
    char message_data[1024];
    rmtError error;

    // Check for potential message data overflow
    if (message_length >= sizeof(message_data) - 1)
    {
        rmt_LogText("Ignoring console input bigger than internal receive buffer (1024 bytes)");
        return RMT_ERROR_NONE;
    }

    // Receive the rest of the message
    message_data[0] = message_first_byte;
    error = WebSocket_Receive(server->client_socket, message_data + 1, NULL, message_length - 1, 100);
    if (error != RMT_ERROR_NONE)
        return error;
    message_data[message_length] = 0;

    // Each message must have a descriptive 4 byte header
    if (message_length < 4)
        return RMT_ERROR_NONE;

    // Dispatch to handler
    if (server->receive_handler)
        error = server->receive_handler(server->receive_handler_context, message_data, message_length);

    return error;
}


static void Server_Update(Server* server)
{
    rmtU32 cur_time;

    assert(server != NULL);

    // Recreate the listening socket if it's been destroyed earlier
    if (server->listen_socket == NULL)
        Server_CreateListenSocket(server, server->port, server->limit_connections_to_localhost);

    if (server->listen_socket != NULL && server->client_socket == NULL)
    {
        // Accept connections as long as there is no client connected
        WebSocket* client_socket = NULL;
        rmtError error = WebSocket_AcceptConnection(server->listen_socket, &client_socket);
        if (error == RMT_ERROR_NONE)
        {
            server->client_socket = client_socket;
        }
        else
        {
            // Destroy the listen socket on failure to accept
            // It will get recreated in another update
            Delete(WebSocket, server->listen_socket);
        }
    }

    else
    {
        // Loop checking for incoming messages
        for (;;)
        {
            // Inspect first byte to see if a message is there
            char message_first_byte;
            rmtU32 message_length;
            rmtError error = WebSocket_Receive(server->client_socket, &message_first_byte, &message_length, 1, 0);
            if (error == RMT_ERROR_NONE)
            {
                // Parse remaining message
                error = Server_ReceiveMessage(server, message_first_byte, message_length);
                if (error != RMT_ERROR_NONE)
                {
                    Server_DisconnectClient(server);
                    break;
                }

                // Check for more...
                continue;
            }

            // Passable errors...
            if (error == RMT_ERROR_SOCKET_RECV_NO_DATA)
            {
                // No data available
                break;
            }

            if (error == RMT_ERROR_SOCKET_RECV_TIMEOUT)
            {
                // Data not available yet, can afford to ignore as we're only reading the first byte
                break;
            }

            // Anything else is an error that may have closed the connection
            Server_DisconnectClient(server);
            break;
        }
    }

    // Send pings to the client every second
    cur_time = msTimer_Get();
    if (cur_time - server->last_ping_time > 1000)
    {
        rmtPStr ping_message = "PING";
        Server_Send(server, ping_message, (rmtU32)strlen(ping_message), 4);
        server->last_ping_time = cur_time;
    }
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @SAMPLE: Base Sample Description for CPU by default
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#define SAMPLE_NAME_LEN 128


enum SampleType
{
    SampleType_CPU,
    SampleType_CUDA,
    SampleType_D3D11,
    SampleType_OpenGL,
    SampleType_Metal,
    SampleType_Count,
};


typedef struct Sample
{
    // Inherit so that samples can be quickly allocated
    ObjectLink Link;

    enum SampleType type;

    // Used to anonymously copy sample data without knowning its type
    rmtU32 size_bytes;

    // Hash generated from sample name
    rmtU32 name_hash;

    // Unique, persistent ID among all samples
    rmtU32 unique_id;

    // Null-terminated string storing the hash-prefixed 6-digit colour
    rmtU8 unique_id_html_colour[8];

    // Links to related samples in the tree
    struct Sample* parent;
    struct Sample* first_child;
    struct Sample* last_child;
    struct Sample* next_sibling;

    // Keep track of child count to distinguish from repeated calls to the same function at the same stack level
    // This is also mixed with the callstack hash to allow consistent addressing of any point in the tree
    rmtU32 nb_children;

    // Sample end points and length in microseconds
    rmtU64 us_start;
    rmtU64 us_end;
    rmtU64 us_length;

} Sample;


static rmtError Sample_Constructor(Sample* sample)
{
    assert(sample != NULL);

    ObjectLink_Constructor((ObjectLink*)sample);

    sample->type = SampleType_CPU;
    sample->size_bytes = sizeof(Sample);
    sample->name_hash = 0;
    sample->unique_id = 0;
    sample->unique_id_html_colour[0] = '#';
    sample->unique_id_html_colour[1] = 0;
    sample->unique_id_html_colour[7] = 0;
    sample->parent = NULL;
    sample->first_child = NULL;
    sample->last_child = NULL;
    sample->next_sibling = NULL;
    sample->nb_children = 0;
    sample->us_start = 0;
    sample->us_end = 0;
    sample->us_length = 0;

    return RMT_ERROR_NONE;
}


static void Sample_Destructor(Sample* sample)
{
    RMT_UNREFERENCED_PARAMETER(sample);
}


static void Sample_Prepare(Sample* sample, rmtU32 name_hash, Sample* parent)
{
    sample->name_hash = name_hash;
    sample->unique_id = 0;
    sample->parent = parent;
    sample->first_child = NULL;
    sample->last_child = NULL;
    sample->next_sibling = NULL;
    sample->nb_children = 0;
    sample->us_start = 0;
    sample->us_end = 0;
    sample->us_length = 0;
}


#define BIN_ERROR_CHECK(stmt) { error = stmt; if (error != RMT_ERROR_NONE) return error; }


static rmtError bin_SampleArray(Buffer* buffer, Sample* first_sample);


static rmtError bin_Sample(Buffer* buffer, Sample* sample)
{
    rmtError error;

    assert(sample != NULL);

    BIN_ERROR_CHECK(Buffer_WriteU32(buffer, sample->name_hash));
    BIN_ERROR_CHECK(Buffer_WriteU32(buffer, sample->unique_id));
    BIN_ERROR_CHECK(Buffer_Write(buffer, sample->unique_id_html_colour, 7));
    BIN_ERROR_CHECK(Buffer_WriteU64(buffer, sample->us_start));
    BIN_ERROR_CHECK(Buffer_WriteU64(buffer, maxS64(sample->us_length, 0)));
    BIN_ERROR_CHECK(bin_SampleArray(buffer, sample));

    return RMT_ERROR_NONE;
}


static rmtError bin_SampleArray(Buffer* buffer, Sample* parent_sample)
{
    rmtError error;
    Sample* sample;

    BIN_ERROR_CHECK(Buffer_WriteU32(buffer, parent_sample->nb_children));
    for (sample = parent_sample->first_child; sample != NULL; sample = sample->next_sibling)
        BIN_ERROR_CHECK(bin_Sample(buffer, sample));

    return RMT_ERROR_NONE;
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @SAMPLETREE: A tree of samples with their allocator
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



typedef struct SampleTree
{
    // Allocator for all samples
    ObjectAllocator* allocator;

    // Root sample for all samples created by this thread
    Sample* root;

    // Most recently pushed sample
    Sample* current_parent;

} SampleTree;


static rmtError SampleTree_Constructor(SampleTree* tree, rmtU32 sample_size, ObjConstructor constructor, ObjDestructor destructor)
{
    rmtError error;

    assert(tree != NULL);

    tree->allocator = NULL;
    tree->root = NULL;
    tree->current_parent = NULL;

    // Create the sample allocator
    New_3(ObjectAllocator, tree->allocator, sample_size, constructor, destructor);
    if (error != RMT_ERROR_NONE)
        return error;

    // Create a root sample that's around for the lifetime of the thread
    error = ObjectAllocator_Alloc(tree->allocator, (void**)&tree->root);
    if (error != RMT_ERROR_NONE)
        return error;
    Sample_Prepare(tree->root, 0, NULL);
    tree->current_parent = tree->root;

    return RMT_ERROR_NONE;
}


static void SampleTree_Destructor(SampleTree* tree)
{
    assert(tree != NULL);

    if (tree->root != NULL)
    {
        ObjectAllocator_Free(tree->allocator, tree->root);
        tree->root = NULL;
    }

    Delete(ObjectAllocator, tree->allocator);
}


static rmtU32 HashCombine(rmtU32 hash_a, rmtU32 hash_b)
{
    // A sequence of 32 uniformly random bits so that each bit of the combined hash is changed on application
    // Derived from the golden ratio: UINT_MAX / ((1 + sqrt(5)) / 2)
    // In reality it's just an arbitrary value which happens to work well, avoiding mapping all zeros to zeros.
    // http://burtleburtle.net/bob/hash/doobs.html
    static rmtU32 random_bits = 0x9E3779B9;
    hash_a ^= hash_b + random_bits + (hash_a << 6) + (hash_a >> 2);
    return hash_a;
}


static rmtError SampleTree_Push(SampleTree* tree, rmtU32 name_hash, rmtU32 flags, Sample** sample)
{
    Sample* parent;
    rmtError error;
    rmtU32 unique_id;

    // As each tree has a root sample node allocated, a parent must always be present
    assert(tree != NULL);
    assert(tree->current_parent != NULL);
    parent = tree->current_parent;

    if ((flags & RMTSF_Aggregate) != 0)
    {
        // Linear search for previous instance of this sample name
        Sample* sibling;
        for (sibling = parent->first_child; sibling != NULL; sibling = sibling->next_sibling)
        {
            if (sibling->name_hash == name_hash)
            {
                tree->current_parent = sibling;
                *sample = sibling;
                return RMT_ERROR_NONE;
            }
        }
    }

    if (parent->name_hash == name_hash)
    {
        // TODO: Collapse recursion on flag?
    }

    // Allocate a new sample
    error = ObjectAllocator_Alloc(tree->allocator, (void**)sample);
    if (error != RMT_ERROR_NONE)
        return error;
    Sample_Prepare(*sample, name_hash, parent);

    // Generate a unique ID for this sample in the tree
    unique_id = parent->unique_id;
    unique_id = HashCombine(unique_id, (*sample)->name_hash);
    unique_id = HashCombine(unique_id, parent->nb_children);
    (*sample)->unique_id = unique_id;

    // Add sample to its parent
    parent->nb_children++;
    if (parent->first_child == NULL)
    {
        parent->first_child = *sample;
        parent->last_child = *sample;
    }
    else
    {
        assert(parent->last_child != NULL);
        parent->last_child->next_sibling = *sample;
        parent->last_child = *sample;
    }

    // Make this sample the new parent of any newly created samples
    tree->current_parent = *sample;

    return RMT_ERROR_NONE;
}


static void SampleTree_Pop(SampleTree* tree, Sample* sample)
{
    assert(tree != NULL);
    assert(sample != NULL);
    assert(sample != tree->root);
    tree->current_parent = sample->parent;
}


static ObjectLink* FlattenSampleTree(Sample* sample, rmtU32* nb_samples)
{
    Sample* child;
    ObjectLink* cur_link = &sample->Link;

    assert(sample != NULL);
    assert(nb_samples != NULL);

    *nb_samples += 1;
    sample->Link.next = (ObjectLink*)sample->first_child;

    // Link all children together
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        ObjectLink* last_link = FlattenSampleTree(child, nb_samples);
        last_link->next = (ObjectLink*)child->next_sibling;
        cur_link = last_link;
    }

    // Clear child info
    sample->first_child = NULL;
    sample->last_child = NULL;
    sample->nb_children = 0;

    return cur_link;
}


static void FreeSampleTree(Sample* sample, ObjectAllocator* allocator)
{
    // Chain all samples together in a flat list
    rmtU32 nb_cleared_samples = 0;
    ObjectLink* last_link = FlattenSampleTree(sample, &nb_cleared_samples);

    // Release the complete sample memory range
    if (sample->Link.next != NULL)
        ObjectAllocator_FreeRange(allocator, sample, last_link, nb_cleared_samples);
    else
        ObjectAllocator_Free(allocator, sample);
}


typedef struct Msg_SampleTree
{
    Sample* root_sample;

    ObjectAllocator* allocator;

    rmtPStr thread_name;
} Msg_SampleTree;


static void AddSampleTreeMessage(rmtMessageQueue* queue, Sample* sample, ObjectAllocator* allocator, rmtPStr thread_name, struct ThreadSampler* thread_sampler)
{
    Msg_SampleTree* payload;

    // Attempt to allocate a message for sending the tree to the viewer
    Message* message = rmtMessageQueue_AllocMessage(queue, sizeof(Msg_SampleTree), thread_sampler);
    if (message == NULL)
    {
        // Discard the tree on failure
        FreeSampleTree(sample, allocator);
        return;
    }

    // Populate and commit
    payload = (Msg_SampleTree*)message->payload;
    payload->root_sample = sample;
    payload->allocator = allocator;
    payload->thread_name = thread_name;
    rmtMessageQueue_CommitMessage(message, MsgID_SampleTree);
}




/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @TSAMPLER: Per-Thread Sampler
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



typedef struct ThreadSampler
{
    // Name to assign to the thread in the viewer
    rmtS8 name[64];

    // Store a unique sample tree for each type
    SampleTree* sample_trees[SampleType_Count];

    // Table of all sample names encountered on this thread
    StringTable* names;

    // Next in the global list of active thread samplers
    struct ThreadSampler* volatile next;

} ThreadSampler;

static rmtError ThreadSampler_Constructor(ThreadSampler* thread_sampler)
{
    rmtError error;
    int i;

    assert(thread_sampler != NULL);

    // Set defaults
    for (i = 0; i < SampleType_Count; i++)
        thread_sampler->sample_trees[i] = NULL;
    thread_sampler->names = NULL;
    thread_sampler->next = NULL;

    // Set the initial name to Thread0 etc. or use the existing Linux name.
    thread_sampler->name[0] = 0;
    #if defined(RMT_PLATFORM_LINUX) && RMT_USE_POSIX_THREADNAMES
    prctl(PR_GET_NAME,thread_sampler->name,0,0,0);
    #else
    {
        static rmtS32 countThreads = 0;
        strncat_s(thread_sampler->name, sizeof(thread_sampler->name), "Thread", 6);
        itoahex_s(thread_sampler->name + 6, sizeof(thread_sampler->name) - 6, AtomicAdd(&countThreads, 1));
    }
    #endif

    // Create the CPU sample tree only - the rest are created on-demand as they need
    // extra context information to function correctly.
    New_3(SampleTree, thread_sampler->sample_trees[SampleType_CPU], sizeof(Sample), (ObjConstructor)Sample_Constructor, (ObjDestructor)Sample_Destructor);
    if (error != RMT_ERROR_NONE)
        return error;

    // Create sample name string table
    New_0(StringTable, thread_sampler->names);
    if (error != RMT_ERROR_NONE)
        return error;

    return RMT_ERROR_NONE;
}


static void ThreadSampler_Destructor(ThreadSampler* ts)
{
    int i;

    assert(ts != NULL);

    Delete(StringTable, ts->names);

    for (i = 0; i < SampleType_Count; i++)
        Delete(SampleTree, ts->sample_trees[i]);
}


static rmtError ThreadSampler_Push(SampleTree* tree, rmtU32 name_hash, rmtU32 flags, Sample** sample)
{
    return SampleTree_Push(tree, name_hash, flags, sample);
}


static rmtBool ThreadSampler_Pop(ThreadSampler* ts, rmtMessageQueue* queue, Sample* sample)
{
    SampleTree* tree = ts->sample_trees[sample->type];
    SampleTree_Pop(tree, sample);

    // Are we back at the root?
    if (tree->current_parent == tree->root)
    {
        // Disconnect all samples from the root and pack in the chosen message queue
        Sample* root = tree->root;
        root->first_child = NULL;
        root->last_child = NULL;
        root->nb_children = 0;
        AddSampleTreeMessage(queue, sample, tree->allocator, ts->name, ts);

        return RMT_TRUE;
    }

    return RMT_FALSE;
}


static rmtU32 ThreadSampler_GetNameHash(ThreadSampler* ts, rmtPStr name, rmtU32* hash_cache)
{
    rmtU32 name_hash = 0;

    // Hash cache provided?
    if (hash_cache != NULL)
    {
        // Calculate the hash first time round only
        if (*hash_cache == 0)
        {
            assert(name != NULL);
            *hash_cache = MurmurHash3_x86_32(name, (int)strnlen_s(name, 256), 0);

            // Also add to the string table on its first encounter
            StringTable_Insert(ts->names, *hash_cache, name);
        }

        return *hash_cache;
    }

    // Have to recalculate and speculatively insert the name every time when no cache storage exists
    name_hash = MurmurHash3_x86_32(name, (int)strnlen_s(name, 256), 0);
    StringTable_Insert(ts->names, name_hash, name);
    return name_hash;
}




/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @REMOTERY: Remotery
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#if RMT_USE_D3D11
typedef struct D3D11 D3D11;
static rmtError D3D11_Create(D3D11** d3d11);
static void D3D11_Destructor(D3D11* d3d11);
#endif


#if RMT_USE_OPENGL
typedef struct OpenGL_t OpenGL;
static rmtError OpenGL_Create(OpenGL** opengl);
static void OpenGL_Destructor(OpenGL* opengl);
#endif


#if RMT_USE_METAL
typedef struct Metal_t Metal;
static rmtError Metal_Create(Metal** metal);
static void Metal_Destructor(Metal* metal);
#endif


struct Remotery
{
    Server* server;

    // Microsecond accuracy timer for CPU timestamps
    usTimer timer;

    rmtTLS thread_sampler_tls_handle;

    // Linked list of all known threads being sampled
    ThreadSampler* volatile first_thread_sampler;

    // Queue between clients and main remotery thread
    rmtMessageQueue* mq_to_rmt_thread;

    // A dynamically-sized buffer used for binary-encoding the sample tree and sending to the client
    Buffer* bin_buf;

    // The main server thread
    rmtThread* thread;

#if RMT_USE_CUDA
    rmtCUDABind cuda;
#endif

#if RMT_USE_D3D11
    D3D11* d3d11;
#endif

#if RMT_USE_OPENGL
    OpenGL* opengl;
#endif

#if RMT_USE_METAL
    Metal* metal;
#endif
};


//
// Global remotery context
//
static Remotery* g_Remotery = NULL;


//
// This flag marks the EXE/DLL that created the global remotery instance. We want to allow
// only the creating EXE/DLL to destroy the remotery instance.
//
static rmtBool g_RemoteryCreated = RMT_FALSE;


static void Remotery_DestroyThreadSamplers(Remotery* rmt);


static const rmtU8 g_DecimalToHex[17] = "0123456789abcdef";


static void GetSampleDigest(Sample* sample, rmtU32* digest_hash, rmtU32* nb_samples)
{
    Sample* child;

    assert(sample != NULL);
    assert(digest_hash != NULL);
    assert(nb_samples != NULL);

    // Concatenate this sample
    (*nb_samples)++;
    *digest_hash = MurmurHash3_x86_32(&sample->unique_id, sizeof(sample->unique_id), *digest_hash);

    {
        rmtU8 shift = 4;

        // Get 6 nibbles for lower 3 bytes of the unique sample ID
        rmtU8* sample_id = (rmtU8*)&sample->unique_id;
        rmtU8 hex_sample_id[6];
        hex_sample_id[0] = sample_id[0] & 15;
        hex_sample_id[1] = sample_id[0] >> 4;
        hex_sample_id[2] = sample_id[1] & 15;
        hex_sample_id[3] = sample_id[1] >> 4;
        hex_sample_id[4] = sample_id[2] & 15;
        hex_sample_id[5] = sample_id[2] >> 4;

        // As the nibbles will be used as hex colour digits, shift them up to make pastel colours
        hex_sample_id[0] = minU8(hex_sample_id[0] + shift, 15);
        hex_sample_id[1] = minU8(hex_sample_id[1] + shift, 15);
        hex_sample_id[2] = minU8(hex_sample_id[2] + shift, 15);
        hex_sample_id[3] = minU8(hex_sample_id[3] + shift, 15);
        hex_sample_id[4] = minU8(hex_sample_id[4] + shift, 15);
        hex_sample_id[5] = minU8(hex_sample_id[5] + shift, 15);

        // Convert the nibbles to hex for the final colour
        sample->unique_id_html_colour[1] = g_DecimalToHex[hex_sample_id[0]];
        sample->unique_id_html_colour[2] = g_DecimalToHex[hex_sample_id[1]];
        sample->unique_id_html_colour[3] = g_DecimalToHex[hex_sample_id[2]];
        sample->unique_id_html_colour[4] = g_DecimalToHex[hex_sample_id[3]];
        sample->unique_id_html_colour[5] = g_DecimalToHex[hex_sample_id[4]];
        sample->unique_id_html_colour[6] = g_DecimalToHex[hex_sample_id[5]];
    }

    // Concatenate children
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
        GetSampleDigest(child, digest_hash, nb_samples);
}


static rmtError Remotery_SendLogTextMessage(Remotery* rmt, Message* message)
{
    assert(rmt != NULL);
    assert(message != NULL);
    return Server_Send(rmt->server, message->payload, message->payload_size, 20);
}


static rmtError bin_SampleTree(Buffer* buffer, Msg_SampleTree* msg)
{
    Sample* root_sample;
    char thread_name[64];
    rmtU32 digest_hash = 0, nb_samples = 0;
    rmtError error;

    assert(buffer != NULL);
    assert(msg != NULL);

    // Get the message root sample
    root_sample = msg->root_sample;
    assert(root_sample != NULL);

    // Reset the buffer position to the start
    buffer->bytes_used = 0;

    // Add any sample types as a thread name post-fix to ensure they get their own viewer
    thread_name[0] = 0;
    strncat_s(thread_name, sizeof(thread_name), msg->thread_name, strnlen_s(msg->thread_name, 64));
    if (root_sample->type == SampleType_CUDA)
        strncat_s(thread_name, sizeof(thread_name), " (CUDA)", 7);
    if (root_sample->type == SampleType_D3D11)
        strncat_s(thread_name, sizeof(thread_name), " (D3D11)", 8);
    if (root_sample->type == SampleType_OpenGL)
        strncat_s(thread_name, sizeof(thread_name), " (OpenGL)", 9);
    if (root_sample->type == SampleType_Metal)
        strncat_s(thread_name, sizeof(thread_name), " (Metal)", 8);

    // Get digest hash of samples so that viewer can efficiently rebuild its tables
    rmt_BeginCPUSample(GetSampleDigest, RMTSF_Aggregate);
    GetSampleDigest(root_sample, &digest_hash, &nb_samples);
    rmt_EndCPUSample();

    // Write global message header
    BIN_ERROR_CHECK(Buffer_Write(buffer, (void*)"SMPL    ", 8));

    // Write sample message header
    BIN_ERROR_CHECK(Buffer_WriteStringWithLength(buffer, thread_name));
    BIN_ERROR_CHECK(Buffer_WriteU32(buffer, nb_samples));
    BIN_ERROR_CHECK(Buffer_WriteU32(buffer, digest_hash));

    // Write entire sample tree
    BIN_ERROR_CHECK(bin_Sample(buffer, root_sample));

    // Patch message size
    U32ToByteArray(buffer->data + 4, buffer->bytes_used);

    return RMT_ERROR_NONE;
}



#if RMT_USE_CUDA
static rmtBool AreCUDASamplesReady(Sample* sample);
static rmtBool GetCUDASampleTimes(Sample* root_sample, Sample* sample);
#endif


static rmtError Remotery_SendSampleTreeMessage(Remotery* rmt, Message* message)
{
    Msg_SampleTree* sample_tree;
    rmtError error = RMT_ERROR_NONE;
    Sample* sample;

    assert(rmt != NULL);
    assert(message != NULL);

    // Get the message root sample
    sample_tree = (Msg_SampleTree*)message->payload;
    sample = sample_tree->root_sample;
    assert(sample != NULL);

    #if RMT_USE_CUDA
    if (sample->type == SampleType_CUDA)
    {
        // If these CUDA samples aren't ready yet, stick them to the back of the queue and continue
        rmtBool are_samples_ready;
        rmt_BeginCPUSample(AreCUDASamplesReady, 0);
        are_samples_ready = AreCUDASamplesReady(sample);
        rmt_EndCPUSample();
        if (!are_samples_ready)
        {
            AddSampleTreeMessage(rmt->mq_to_rmt_thread, sample, sample_tree->allocator, sample_tree->thread_name, message->thread_sampler);
            return RMT_ERROR_NONE;
        }

        // Retrieve timing of all CUDA samples
        rmt_BeginCPUSample(GetCUDASampleTimes, 0);
        GetCUDASampleTimes(sample->parent, sample);
        rmt_EndCPUSample();
    }
    #endif

    // Serialise the sample tree and send to the viewer with a reasonably long timeout as the size
    // of the sample data may be large
    rmt_BeginCPUSample(bin_SampleTree, RMTSF_Aggregate);
    error = bin_SampleTree(rmt->bin_buf, sample_tree);
    rmt_EndCPUSample();
    if (error == RMT_ERROR_NONE)
    {
        rmt_BeginCPUSample(Server_Send, RMTSF_Aggregate);
        error = Server_Send(rmt->server, rmt->bin_buf->data, rmt->bin_buf->bytes_used, 50000);
        rmt_EndCPUSample();
    }

    // Release the sample tree back to its allocator
    FreeSampleTree(sample, sample_tree->allocator);

    return error;
}


static rmtError Remotery_ConsumeMessageQueue(Remotery* rmt)
{
    rmtU32 nb_messages_sent = 0;
    const rmtU32 maxNbMessagesPerUpdate = g_Settings.maxNbMessagesPerUpdate;

    assert(rmt != NULL);

    // Absorb as many messages in the queue while disconnected
    if (Server_IsClientConnected(rmt->server) == RMT_FALSE)
        return RMT_ERROR_NONE;

    // Loop reading the max number of messages for this update
    while( nb_messages_sent++ < maxNbMessagesPerUpdate )
    {
        rmtError error = RMT_ERROR_NONE;
        Message* message = rmtMessageQueue_PeekNextMessage(rmt->mq_to_rmt_thread);
        if (message == NULL)
            break;

        switch (message->id)
        {
            // This shouldn't be possible
            case MsgID_NotReady:
                assert(RMT_FALSE);
                break;

            // Dispatch to message handler
            case MsgID_LogText:
                error = Remotery_SendLogTextMessage(rmt, message);
                break;
            case MsgID_SampleTree:
                rmt_BeginCPUSample(SendSampleTreeMessage, RMTSF_Aggregate);
                error = Remotery_SendSampleTreeMessage(rmt, message);
                rmt_EndCPUSample();
                break;
        }

        // Consume the message before reacting to any errors
        rmtMessageQueue_ConsumeNextMessage(rmt->mq_to_rmt_thread, message);
        if (error != RMT_ERROR_NONE)
            return error;
    }

    return RMT_ERROR_NONE;
}


static void Remotery_FlushMessageQueue(Remotery* rmt)
{
    assert(rmt != NULL);

    // Loop reading all remaining messages
    for (;;)
    {
        Message* message = rmtMessageQueue_PeekNextMessage(rmt->mq_to_rmt_thread);
        if (message == NULL)
            break;

        switch (message->id)
        {
            // These can be safely ignored
            case MsgID_NotReady:
            case MsgID_LogText:
                break;

            // Release all samples back to their allocators
            case MsgID_SampleTree:
            {
                Msg_SampleTree* sample_tree = (Msg_SampleTree*)message->payload;
                FreeSampleTree(sample_tree->root_sample, sample_tree->allocator);
                break;
            }
        }

        rmtMessageQueue_ConsumeNextMessage(rmt->mq_to_rmt_thread, message);
    }
}


static rmtError Remotery_ThreadMain(rmtThread* thread)
{
    Remotery* rmt = (Remotery*)thread->param;
    assert(rmt != NULL);

    rmt_SetCurrentThreadName("Remotery");

    while (thread->request_exit == RMT_FALSE)
    {
        rmt_BeginCPUSample(Wakeup, 0);

            rmt_BeginCPUSample(ServerUpdate, 0);
            Server_Update(rmt->server);
            rmt_EndCPUSample();

            rmt_BeginCPUSample(ConsumeMessageQueue, 0);
            Remotery_ConsumeMessageQueue(rmt);
            rmt_EndCPUSample();

        rmt_EndCPUSample();

        //
        // [NOTE-A]
        //
        // Possible sequence of user events at this point:
        //
        //    1. Add samples to the queue.
        //    2. Shutdown remotery.
        //
        // This loop will exit with unrelease samples.
        //

        msSleep(g_Settings.msSleepBetweenServerUpdates);
    }

    // Release all samples to their allocators as a consequence of [NOTE-A]
    Remotery_FlushMessageQueue(rmt);

    return RMT_ERROR_NONE;
}


static rmtError Remotery_ReceiveMessage(void* context, char* message_data, rmtU32 message_length)
{
    Remotery* rmt = (Remotery*)context;

    // Manual dispatch on 4-byte message headers (message ID is little-endian encoded)
    #define FOURCC(a, b, c, d) (rmtU32)( ((d) << 24) | ((c) << 16) | ((b) << 8) | (a) )
    rmtU32 message_id = *(rmtU32*)message_data;

    switch (message_id)
    {
        case FOURCC('C', 'O', 'N', 'I'):
        {
            // Pass on to any registered handler
            if (g_Settings.input_handler != NULL)
                g_Settings.input_handler(message_data + 4, g_Settings.input_handler_context);

            rmt_LogText("Console message received...");
            rmt_LogText(message_data + 4);
            break;
        }

        case FOURCC('G', 'S', 'M', 'P'):
        {
            // Convert name hash to integer
            rmtU32 name_hash = 0;
            const char* cur = message_data + 4;
            const char* end = cur + message_length - 4;
            while (cur < end)
                name_hash = name_hash * 10 + *cur++ - '0';

            // Search all threads for a matching string hash
            ThreadSampler* ts;
            for (ts = rmt->first_thread_sampler; ts != NULL; ts = ts->next)
            {
                rmtPStr name = StringTable_Find(ts->names, name_hash);
                if (name != NULL)
                {
                    // Construct a response message containing the matching name
                    rmtU8 response[256];
                    rmtU32 name_length = (rmtU32)strnlen_s(name, 256 - 12);
                    response[0] = 'S';
                    response[1] = 'S';
                    response[2] = 'M';
                    response[3] = 'P';
                    U32ToByteArray(response + 4, name_hash);
                    U32ToByteArray(response + 8, name_length);
                    memcpy(response + 12, name, name_length);

                    // Send back immediately as we're on the server thread
                    return Server_Send(rmt->server, response, 12 + name_length, 10);
                }
            }

            break;
        }
    }

    #undef FOURCC

    return RMT_ERROR_NONE;
}


static rmtError Remotery_Constructor(Remotery* rmt)
{
    rmtError error;

    assert(rmt != NULL);

    // Set default state
    rmt->server = NULL;
    rmt->thread_sampler_tls_handle = TLS_INVALID_HANDLE;
    rmt->first_thread_sampler = NULL;
    rmt->mq_to_rmt_thread = NULL;
    rmt->bin_buf = NULL;
    rmt->thread = NULL;

    #if RMT_USE_CUDA
        rmt->cuda.CtxSetCurrent = NULL;
        rmt->cuda.EventCreate = NULL;
        rmt->cuda.EventDestroy = NULL;
        rmt->cuda.EventElapsedTime = NULL;
        rmt->cuda.EventQuery = NULL;
        rmt->cuda.EventRecord = NULL;
    #endif

    #if RMT_USE_D3D11
        rmt->d3d11 = NULL;
    #endif

    #if RMT_USE_OPENGL
        rmt->opengl = NULL;
    #endif

    #if RMT_USE_METAL
        rmt->metal = NULL;
    #endif

    // Kick-off the timer
    usTimer_Init(&rmt->timer);

    // Allocate a TLS handle for the thread sampler
    error = tlsAlloc(&rmt->thread_sampler_tls_handle);
    if (error != RMT_ERROR_NONE)
        return error;

    // Create the server
    New_2(Server, rmt->server, g_Settings.port, g_Settings.limit_connections_to_localhost);
    if (error != RMT_ERROR_NONE)
        return error;

    // Setup incoming message handler
    rmt->server->receive_handler = Remotery_ReceiveMessage;
    rmt->server->receive_handler_context = rmt;

    // Create the main message thread with only one page
    New_1(rmtMessageQueue, rmt->mq_to_rmt_thread, g_Settings.messageQueueSizeInBytes);
    if (error != RMT_ERROR_NONE)
        return error;

    // Create the binary serialisation buffer
    New_1(Buffer, rmt->bin_buf, 4096);
    if (error != RMT_ERROR_NONE)
        return error;

    #if RMT_USE_D3D11
        error = D3D11_Create(&rmt->d3d11);
        if (error != RMT_ERROR_NONE)
            return error;
    #endif

    #if RMT_USE_OPENGL
        error = OpenGL_Create(&rmt->opengl);
        if (error != RMT_ERROR_NONE)
            return error;
    #endif

    #if RMT_USE_METAL
        error = Metal_Create(&rmt->metal);
        if (error != RMT_ERROR_NONE)
            return error;
    #endif


    // Set as the global instance before creating any threads that uses it for sampling itself
    assert(g_Remotery == NULL);
    g_Remotery = rmt;
    g_RemoteryCreated = RMT_TRUE;

    // Ensure global instance writes complete before other threads get a chance to use it
    WriteFence();

    // Create the main update thread once everything has been defined for the global remotery object
    New_2(rmtThread, rmt->thread, Remotery_ThreadMain, rmt);
    return error;
}


static void Remotery_Destructor(Remotery* rmt)
{
    assert(rmt != NULL);

    // Join the remotery thread before clearing the global object as the thread is profiling itself
    Delete(rmtThread, rmt->thread);

    if (g_RemoteryCreated)
    {
      g_Remotery = NULL;
      g_RemoteryCreated = RMT_FALSE;
    }

    #if RMT_USE_D3D11
        Delete(D3D11, rmt->d3d11);
    #endif

    #if RMT_USE_OPENGL
        Delete(OpenGL, rmt->opengl);
    #endif

    #if RMT_USE_METAL
        Delete(Metal, rmt->metal);
    #endif

    Delete(Buffer, rmt->bin_buf);
    Delete(rmtMessageQueue, rmt->mq_to_rmt_thread);

    Remotery_DestroyThreadSamplers(rmt);

    Delete(Server, rmt->server);

    if (rmt->thread_sampler_tls_handle != TLS_INVALID_HANDLE)
    {
        tlsFree(rmt->thread_sampler_tls_handle);
        rmt->thread_sampler_tls_handle = 0;
    }
}


static rmtError Remotery_GetThreadSampler(Remotery* rmt, ThreadSampler** thread_sampler)
{
    ThreadSampler* ts;

    // Is there a thread sampler associated with this thread yet?
    assert(rmt != NULL);
    ts = (ThreadSampler*)tlsGet(rmt->thread_sampler_tls_handle);
    if (ts == NULL)
    {
        // Allocate on-demand
        rmtError error;
        New_0(ThreadSampler, *thread_sampler);
        if (error != RMT_ERROR_NONE)
            return error;
        ts = *thread_sampler;

        // Add to the beginning of the global linked list of thread samplers
        for (;;)
        {
            ThreadSampler* old_ts = rmt->first_thread_sampler;
            ts->next = old_ts;

            // If the old value is what we expect it to be then no other thread has
            // changed it since this thread sampler was used as a candidate first list item
            if (AtomicCompareAndSwapPointer((long* volatile*)&rmt->first_thread_sampler, (long*)old_ts, (long*)ts) == RMT_TRUE)
                break;
        }

        tlsSet(rmt->thread_sampler_tls_handle, ts);
    }

    assert(thread_sampler != NULL);
    *thread_sampler = ts;
    return RMT_ERROR_NONE;
}


static void Remotery_BlockingDeleteSampleTree(Remotery* rmt, enum SampleType sample_type)
{
    ThreadSampler* ts;

    // Get the attached thread sampler
    assert(rmt != NULL);
    if (Remotery_GetThreadSampler(rmt, &ts) == RMT_ERROR_NONE)
    {
        SampleTree* sample_tree = ts->sample_trees[sample_type];
        if (sample_tree != NULL)
        {
            // Wait around until the Remotery server thread has sent all sample trees
            // of this type to the client
            while (sample_tree->allocator->nb_inuse > 1)
                msSleep(1);

            // Now free to delete
            Delete(SampleTree, sample_tree);
            ts->sample_trees[sample_type] = NULL;
        }
    }
}



static void Remotery_DestroyThreadSamplers(Remotery* rmt)
{
    // If the handle failed to create in the first place then it shouldn't be possible to create thread samplers
    assert(rmt != NULL);
    if (rmt->thread_sampler_tls_handle == TLS_INVALID_HANDLE)
    {
        assert(rmt->first_thread_sampler == NULL);
        return;
    }

    // Keep popping thread samplers off the linked list until they're all gone
    // This does not make any assumptions, making it possible for thread samplers to be created while they're all
    // deleted. While this is erroneous calling code, this will prevent a confusing crash.
    while (rmt->first_thread_sampler != NULL)
    {
        ThreadSampler* ts;

        for (;;)
        {
            ThreadSampler* old_ts = rmt->first_thread_sampler;
            ThreadSampler* next_ts = old_ts->next;

            if (AtomicCompareAndSwapPointer((long* volatile*)&rmt->first_thread_sampler, (long*)old_ts, (long*)next_ts) == RMT_TRUE)
            {
                ts = old_ts;
                break;
            }
        }

        Delete(ThreadSampler, ts);
    }
}


static void* CRTMalloc(void* mm_context, rmtU32 size)
{
    RMT_UNREFERENCED_PARAMETER(mm_context);
    return malloc((size_t)size);
}


static void CRTFree(void* mm_context, void* ptr)
{
    RMT_UNREFERENCED_PARAMETER(mm_context);
    free(ptr);
}

static void* CRTRealloc(void* mm_context, void* ptr, rmtU32 size)
{
    RMT_UNREFERENCED_PARAMETER(mm_context);
    return realloc(ptr, size);
}


RMT_API rmtSettings* _rmt_Settings(void)
{
    // Default-initialize on first call
    if( g_SettingsInitialized == RMT_FALSE )
    {
        g_Settings.port = 0x4597;
        g_Settings.limit_connections_to_localhost = RMT_FALSE;
        g_Settings.msSleepBetweenServerUpdates = 10;
        g_Settings.messageQueueSizeInBytes = 128 * 1024;
        g_Settings.maxNbMessagesPerUpdate = 10;
        g_Settings.malloc = CRTMalloc;
        g_Settings.free = CRTFree;
        g_Settings.realloc = CRTRealloc;
        g_Settings.input_handler = NULL;
        g_Settings.input_handler_context = NULL;
        g_Settings.logFilename = "rmtLog.txt";

        g_SettingsInitialized = RMT_TRUE;
    }

    return &g_Settings;
}


RMT_API rmtError _rmt_CreateGlobalInstance(Remotery** remotery)
{
    rmtError error;

    // Default-initialise if user has not set values
    rmt_Settings();

    // Creating the Remotery instance also records it as the global instance
    assert(remotery != NULL);
    New_0(Remotery, *remotery);
    return error;
}


RMT_API void _rmt_DestroyGlobalInstance(Remotery* remotery)
{
    // Ensure this is the module that created it
    assert(g_RemoteryCreated == RMT_TRUE);
    assert(g_Remotery == remotery);
    Delete(Remotery, remotery);
}


RMT_API void _rmt_SetGlobalInstance(Remotery* remotery)
{
    // Default-initialise if user has not set values
    rmt_Settings();

    g_Remotery = remotery;
}


RMT_API Remotery* _rmt_GetGlobalInstance(void)
{
    return g_Remotery;
}


#ifdef RMT_PLATFORM_WINDOWS
    #pragma pack(push,8)
    typedef struct tagTHREADNAME_INFO
    {
       DWORD dwType; // Must be 0x1000.
       LPCSTR szName; // Pointer to name (in user addr space).
       DWORD dwThreadID; // Thread ID (-1=caller thread).
       DWORD dwFlags; // Reserved for future use, must be zero.
    } THREADNAME_INFO;
    #pragma pack(pop)
#endif

static void SetDebuggerThreadName(const char* name)
{
    #ifdef RMT_PLATFORM_WINDOWS
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = name;
        info.dwThreadID = (DWORD)-1;
        info.dwFlags = 0;

        #ifndef __MINGW32__
        __try
        {
            RaiseException(0x406D1388, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
        }
        __except(1 /* EXCEPTION_EXECUTE_HANDLER */)
        {
        }
        #endif
    #else
        RMT_UNREFERENCED_PARAMETER(name);
    #endif

    #ifdef RMT_PLATFORM_LINUX
        // pthread_setname_np is a non-standard GNU extension.
        char name_clamp[16];
        name_clamp[0] = 0;
        strncat_s(name_clamp, sizeof(name_clamp), name, 15);
        prctl(PR_SET_NAME,name_clamp,0,0,0);
    #endif
}


RMT_API void _rmt_SetCurrentThreadName(rmtPStr thread_name)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    // Get data for this thread
    if (Remotery_GetThreadSampler(g_Remotery, &ts) != RMT_ERROR_NONE)
        return;

    // Copy name and apply to the debugger
    strcpy_s(ts->name, sizeof(ts->name), thread_name);
    SetDebuggerThreadName(thread_name);
}


static rmtBool QueueLine(rmtMessageQueue* queue, unsigned char* text, rmtU32 size, struct ThreadSampler* thread_sampler)
{
    Message* message;

    assert(queue != NULL);

    // Prefix with text size
    rmtU32 text_size = size - 8;
    U32ToByteArray(text + 4, text_size);

    // Allocate some space for the line
    message = rmtMessageQueue_AllocMessage(queue, size, thread_sampler);
    if (message == NULL)
        return RMT_FALSE;

    // Copy the text and commit the message
    memcpy(message->payload, text, size);
    rmtMessageQueue_CommitMessage(message, MsgID_LogText);

    return RMT_TRUE;
}


RMT_API void _rmt_LogText(rmtPStr text)
{
    int start_offset, prev_offset, i;
    unsigned char line_buffer[1024] = { 0 };
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    Remotery_GetThreadSampler(g_Remotery, &ts);

    // Start the line with the message header
    line_buffer[0] = 'L';
    line_buffer[1] = 'O';
    line_buffer[2] = 'G';
    line_buffer[3] = 'M';
    start_offset = 8;

    // There might be newlines in the buffer, so split them into multiple network calls
    prev_offset = start_offset;
    for (i = 0; text[i] != 0; i++)
    {
        char c = text[i];

        // Line wrap when too long or newline encountered
        if (prev_offset == sizeof(line_buffer) - 3 || c == '\n')
        {
            if (QueueLine(g_Remotery->mq_to_rmt_thread, line_buffer, prev_offset, ts) == RMT_FALSE)
                return;

            // Restart line
            prev_offset = start_offset;
        }

        // Safe to insert 2 characters here as previous check would split lines if not enough space left
        switch (c)
        {
            // Skip newline, dealt with above
            case '\n':
                break;

            // Escape these
            case '\\':
                line_buffer[prev_offset++] = '\\';
                line_buffer[prev_offset++] = '\\';
                break;

            case '\"':
                line_buffer[prev_offset++] = '\\';
                line_buffer[prev_offset++] = '\"';
                break;

            // Add the rest
            default:
                line_buffer[prev_offset++] = c;
                break;
        }
    }

    // Send the last line
    if (prev_offset > start_offset)
    {
        assert(prev_offset < ((int)sizeof(line_buffer) - 3));
        QueueLine(g_Remotery->mq_to_rmt_thread, line_buffer, prev_offset, ts);
    }
}


RMT_API void _rmt_BeginCPUSample(rmtPStr name, rmtU32 flags, rmtU32* hash_cache)
{
    // 'hash_cache' stores a pointer to a sample name's hash value. Internally this is used to identify unique callstacks and it
    // would be ideal that it's not recalculated each time the sample is used. This can be statically cached at the point
    // of call or stored elsewhere when dynamic names are required.
    //
    // If 'hash_cache' is NULL then this call becomes more expensive, as it has to recalculate the hash of the name.

    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    // TODO: Time how long the bits outside here cost and subtract them from the parent

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        Sample* sample;
        rmtU32 name_hash = ThreadSampler_GetNameHash(ts, name, hash_cache);
        if (ThreadSampler_Push(ts->sample_trees[SampleType_CPU], name_hash, flags, &sample) == RMT_ERROR_NONE)
        {
            // If this is an aggregate sample, store the time in 'end' as we want to preserve 'start'
            if (sample->us_length != 0)
                sample->us_end = usTimer_Get(&g_Remotery->timer);
            else
                sample->us_start = usTimer_Get(&g_Remotery->timer);
        }
    }
}


RMT_API void _rmt_EndCPUSample(void)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        Sample* sample = ts->sample_trees[SampleType_CPU]->current_parent;

        rmtU64 us_end = usTimer_Get(&g_Remotery->timer);

        // Is this an aggregate sample?
        if (sample->us_length != 0)
        {
            sample->us_length += (us_end - sample->us_end);
            sample->us_end = us_end;
        }
        else
        {
            sample->us_end = us_end;
            sample->us_length = (us_end - sample->us_start);
        }

        sample->us_end = usTimer_Get(&g_Remotery->timer);
        ThreadSampler_Pop(ts, g_Remotery->mq_to_rmt_thread, sample);
    }
}



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @CUDA: CUDA event sampling
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#if RMT_USE_CUDA


typedef struct CUDASample
{
    // IS-A inheritance relationship
    Sample Sample;

    // Pair of events that wrap the sample
    CUevent event_start;
    CUevent event_end;

} CUDASample;


static rmtError MapCUDAResult(CUresult result)
{
    switch (result)
    {
        case CUDA_SUCCESS: return RMT_ERROR_NONE;
        case CUDA_ERROR_DEINITIALIZED: return RMT_ERROR_CUDA_DEINITIALIZED;
        case CUDA_ERROR_NOT_INITIALIZED: return RMT_ERROR_CUDA_NOT_INITIALIZED;
        case CUDA_ERROR_INVALID_CONTEXT: return RMT_ERROR_CUDA_INVALID_CONTEXT;
        case CUDA_ERROR_INVALID_VALUE: return RMT_ERROR_CUDA_INVALID_VALUE;
        case CUDA_ERROR_INVALID_HANDLE: return RMT_ERROR_CUDA_INVALID_HANDLE;
        case CUDA_ERROR_OUT_OF_MEMORY: return RMT_ERROR_CUDA_OUT_OF_MEMORY;
        case CUDA_ERROR_NOT_READY: return RMT_ERROR_ERROR_NOT_READY;
        default: return RMT_ERROR_CUDA_UNKNOWN;
    }
}


#define CUDA_MAKE_FUNCTION(name, params)                    \
    typedef CUresult (CUDAAPI *name##Ptr) params;           \
    name##Ptr name = (name##Ptr)g_Remotery->cuda.name;


#define CUDA_GUARD(call)                \
    {                                   \
        rmtError error = call;     \
        if (error != RMT_ERROR_NONE)    \
            return error;               \
    }


// Wrappers around CUDA driver functions that manage the active context.
static rmtError CUDASetContext(void* context)
{
    CUDA_MAKE_FUNCTION(CtxSetCurrent, (CUcontext ctx));
    assert(CtxSetCurrent != NULL);
    return MapCUDAResult(CtxSetCurrent((CUcontext)context));
}
static rmtError CUDAGetContext(void** context)
{
    CUDA_MAKE_FUNCTION(CtxGetCurrent, (CUcontext* ctx));
    assert(CtxGetCurrent != NULL);
    return MapCUDAResult(CtxGetCurrent((CUcontext*)context));
}
static rmtError CUDAEnsureContext()
{
    void* current_context;
    CUDA_GUARD(CUDAGetContext(&current_context));

    assert(g_Remotery != NULL);
    if (current_context != g_Remotery->cuda.context)
        CUDA_GUARD(CUDASetContext(g_Remotery->cuda.context));

    return RMT_ERROR_NONE;
}


// Wrappers around CUDA driver functions that manage events
static rmtError CUDAEventCreate(CUevent* phEvent, unsigned int Flags)
{
    CUDA_MAKE_FUNCTION(EventCreate, (CUevent *phEvent, unsigned int Flags));
    CUDA_GUARD(CUDAEnsureContext());
    return MapCUDAResult(EventCreate(phEvent, Flags));
}
static rmtError CUDAEventDestroy(CUevent hEvent)
{
    CUDA_MAKE_FUNCTION(EventDestroy, (CUevent hEvent));
    CUDA_GUARD(CUDAEnsureContext());
    return MapCUDAResult(EventDestroy(hEvent));
}
static rmtError CUDAEventRecord(CUevent hEvent, void* hStream)
{
    CUDA_MAKE_FUNCTION(EventRecord, (CUevent hEvent, CUstream hStream));
    CUDA_GUARD(CUDAEnsureContext());
    return MapCUDAResult(EventRecord(hEvent, (CUstream)hStream));
}
static rmtError CUDAEventQuery(CUevent hEvent)
{
    CUDA_MAKE_FUNCTION(EventQuery,  (CUevent hEvent));
    CUDA_GUARD(CUDAEnsureContext());
    return MapCUDAResult(EventQuery(hEvent));
}
static rmtError CUDAEventElapsedTime(float* pMilliseconds, CUevent hStart, CUevent hEnd)
{
    CUDA_MAKE_FUNCTION(EventElapsedTime, (float *pMilliseconds, CUevent hStart, CUevent hEnd));
    CUDA_GUARD(CUDAEnsureContext());
    return MapCUDAResult(EventElapsedTime(pMilliseconds, hStart, hEnd));
}


static rmtError CUDASample_Constructor(CUDASample* sample)
{
    rmtError error;

    assert(sample != NULL);

    // Chain to sample constructor
    Sample_Constructor((Sample*)sample);
    sample->Sample.type = SampleType_CUDA;
    sample->Sample.size_bytes = sizeof(CUDASample);
    sample->event_start = NULL;
    sample->event_end = NULL;

    // Create non-blocking events with timing
    assert(g_Remotery != NULL);
    error = CUDAEventCreate(&sample->event_start, CU_EVENT_DEFAULT);
    if (error == RMT_ERROR_NONE)
        error = CUDAEventCreate(&sample->event_end, CU_EVENT_DEFAULT);
    return error;
}


static void CUDASample_Destructor(CUDASample* sample)
{
    assert(sample != NULL);

    // Destroy events
    if (sample->event_start != NULL)
        CUDAEventDestroy(sample->event_start);
    if (sample->event_end != NULL)
        CUDAEventDestroy(sample->event_end);

    Sample_Destructor((Sample*)sample);
}


static rmtBool AreCUDASamplesReady(Sample* sample)
{
    rmtError error;
    Sample* child;

    CUDASample* cuda_sample = (CUDASample*)sample;
    assert(sample->type == SampleType_CUDA);

    // Check to see if both of the CUDA events have been processed
    error = CUDAEventQuery(cuda_sample->event_start);
    if (error != RMT_ERROR_NONE)
        return RMT_FALSE;
    error = CUDAEventQuery(cuda_sample->event_end);
    if (error != RMT_ERROR_NONE)
        return RMT_FALSE;

    // Check child sample events
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        if (!AreCUDASamplesReady(child))
            return RMT_FALSE;
    }

    return RMT_TRUE;
}


static rmtBool GetCUDASampleTimes(Sample* root_sample, Sample* sample)
{
    Sample* child;

    CUDASample* cuda_root_sample = (CUDASample*)root_sample;
    CUDASample* cuda_sample = (CUDASample*)sample;

    float ms_start, ms_end;

    assert(root_sample != NULL);
    assert(sample != NULL);

    // Get millisecond timing of each sample event, relative to initial root sample
    if (CUDAEventElapsedTime(&ms_start, cuda_root_sample->event_start, cuda_sample->event_start) != RMT_ERROR_NONE)
        return RMT_FALSE;
    if (CUDAEventElapsedTime(&ms_end, cuda_root_sample->event_start, cuda_sample->event_end) != RMT_ERROR_NONE)
        return RMT_FALSE;

    // Convert to microseconds and add to the sample
    sample->us_start = (rmtU64)(ms_start * 1000);
    sample->us_end = (rmtU64)(ms_end * 1000);
    sample->us_length = sample->us_end - sample->us_start;

    // Get child sample times
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        if (!GetCUDASampleTimes(root_sample, child))
            return RMT_FALSE;
    }

    return RMT_TRUE;
}


RMT_API void _rmt_BindCUDA(const rmtCUDABind* bind)
{
    assert(bind != NULL);
    if (g_Remotery != NULL)
        g_Remotery->cuda = *bind;
}


RMT_API void _rmt_BeginCUDASample(rmtPStr name, rmtU32* hash_cache, void* stream)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        rmtError error;
        Sample* sample;
        rmtU32 name_hash = ThreadSampler_GetNameHash(ts, name, hash_cache);

        // Create the CUDA tree on-demand as the tree needs an up-front-created root.
        // This is not possible to create on initialisation as a CUDA binding is not yet available.
        SampleTree** cuda_tree = &ts->sample_trees[SampleType_CUDA];
        if (*cuda_tree == NULL)
        {
            CUDASample* root_sample;

            New_3(SampleTree, *cuda_tree, sizeof(CUDASample), (ObjConstructor)CUDASample_Constructor, (ObjDestructor)CUDASample_Destructor);
            if (error != RMT_ERROR_NONE)
                return;

            // Record an event once on the root sample, used to measure absolute sample
            // times since this point
            root_sample = (CUDASample*)(*cuda_tree)->root;
            error = CUDAEventRecord(root_sample->event_start, stream);
            if (error != RMT_ERROR_NONE)
                return;
        }

        // Push the same and record its event
        if (ThreadSampler_Push(*cuda_tree, name_hash, 0, &sample) == RMT_ERROR_NONE)
        {
            CUDASample* cuda_sample = (CUDASample*)sample;
            CUDAEventRecord(cuda_sample->event_start, stream);
        }
    }
}


RMT_API void _rmt_EndCUDASample(void* stream)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        CUDASample* sample = (CUDASample*)ts->sample_trees[SampleType_CUDA]->current_parent;
        CUDAEventRecord(sample->event_end, stream);
        ThreadSampler_Pop(ts, g_Remotery->mq_to_rmt_thread, (Sample*)sample);
    }
}


#endif  // RMT_USE_CUDA



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
   @D3D11: Direct3D 11 event sampling
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#if RMT_USE_D3D11


// As clReflect has no way of disabling C++ compile mode, this forces C interfaces everywhere...
#define CINTERFACE

// ...unfortunately these C++ helpers aren't wrapped by the same macro but they can be disabled individually
#define D3D11_NO_HELPERS

// Allow use of the D3D11 helper macros for accessing the C-style vtable
#define COBJMACROS

#include <d3d11.h>


typedef struct D3D11
{
    // Context set by user
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    HRESULT last_error;

    // Queue to the D3D 11 main update thread
    // Given that BeginSample/EndSample need to be called from the same thread that does the update, there
    // is really no need for this to be a thread-safe queue. I'm using it for its convenience.
    rmtMessageQueue* mq_to_d3d11_main;

    // Mark the first time so that remaining timestamps are offset from this
    rmtU64 first_timestamp;
} D3D11;


static rmtError D3D11_Create(D3D11** d3d11)
{
    rmtError error;

    assert(d3d11 != NULL);

    // Allocate space for the D3D11 data
    *d3d11 = (D3D11*)rmtMalloc(sizeof(D3D11));
    if (*d3d11 == NULL)
        return RMT_ERROR_MALLOC_FAIL;

    // Set defaults
    (*d3d11)->device = NULL;
    (*d3d11)->context = NULL;
    (*d3d11)->last_error = S_OK;
    (*d3d11)->mq_to_d3d11_main = NULL;
    (*d3d11)->first_timestamp = 0;

    New_1(rmtMessageQueue, (*d3d11)->mq_to_d3d11_main, g_Settings.messageQueueSizeInBytes);
    if (error != RMT_ERROR_NONE)
    {
        Delete(D3D11, *d3d11);
        return error;
    }

    return RMT_ERROR_NONE;
}


static void D3D11_Destructor(D3D11* d3d11)
{
    assert(d3d11 != NULL);
    Delete(rmtMessageQueue, d3d11->mq_to_d3d11_main);
}


typedef struct D3D11Timestamp
{
    // Inherit so that timestamps can be quickly allocated
    ObjectLink Link;

    // Pair of timestamp queries that wrap the sample
    ID3D11Query* query_start;
    ID3D11Query* query_end;

    // A disjoint to measure frequency/stability
    // TODO: Does *each* sample need one of these?
    ID3D11Query* query_disjoint;
} D3D11Timestamp;


static rmtError D3D11Timestamp_Constructor(D3D11Timestamp* stamp)
{
    D3D11_QUERY_DESC timestamp_desc;
    D3D11_QUERY_DESC disjoint_desc;
    ID3D11Device* device;
    HRESULT* last_error;

    assert(stamp != NULL);

    ObjectLink_Constructor((ObjectLink*)stamp);

    // Set defaults
    stamp->query_start = NULL;
    stamp->query_end = NULL;
    stamp->query_disjoint = NULL;

    assert(g_Remotery != NULL);
    assert(g_Remotery->d3d11 != NULL);
    device = g_Remotery->d3d11->device;
    last_error = &g_Remotery->d3d11->last_error;

    // Create start/end timestamp queries
    timestamp_desc.Query = D3D11_QUERY_TIMESTAMP;
    timestamp_desc.MiscFlags = 0;
    *last_error = ID3D11Device_CreateQuery(device, &timestamp_desc, &stamp->query_start);
    if (*last_error != S_OK)
        return RMT_ERROR_D3D11_FAILED_TO_CREATE_QUERY;
    *last_error = ID3D11Device_CreateQuery(device, &timestamp_desc, &stamp->query_end);
    if (*last_error != S_OK)
        return RMT_ERROR_D3D11_FAILED_TO_CREATE_QUERY;

    // Create disjoint query
    disjoint_desc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
    disjoint_desc.MiscFlags = 0;
    *last_error = ID3D11Device_CreateQuery(device, &disjoint_desc, &stamp->query_disjoint);
    if (*last_error != S_OK)
        return RMT_ERROR_D3D11_FAILED_TO_CREATE_QUERY;

    return RMT_ERROR_NONE;
}


static void D3D11Timestamp_Destructor(D3D11Timestamp* stamp)
{
    assert(stamp != NULL);

    // Destroy queries
    if (stamp->query_disjoint != NULL)
        ID3D11Query_Release(stamp->query_disjoint);
    if (stamp->query_end != NULL)
        ID3D11Query_Release(stamp->query_end);
    if (stamp->query_start != NULL)
        ID3D11Query_Release(stamp->query_start);
}


static void D3D11Timestamp_Begin(D3D11Timestamp* stamp, ID3D11DeviceContext* context)
{
    assert(stamp != NULL);

    // Start of disjoint and first query
    ID3D11DeviceContext_Begin(context, (ID3D11Asynchronous*)stamp->query_disjoint);
    ID3D11DeviceContext_End(context, (ID3D11Asynchronous*)stamp->query_start);
}


static void D3D11Timestamp_End(D3D11Timestamp* stamp, ID3D11DeviceContext* context)
{
    assert(stamp != NULL);

    // End of disjoint and second query
    ID3D11DeviceContext_End(context, (ID3D11Asynchronous*)stamp->query_end);
    ID3D11DeviceContext_End(context, (ID3D11Asynchronous*)stamp->query_disjoint);
}


static HRESULT D3D11Timestamp_GetData(D3D11Timestamp* stamp, ID3D11DeviceContext* context, rmtU64* out_start, rmtU64* out_end, rmtU64* out_first_timestamp)
{
    ID3D11Asynchronous* query_start;
    ID3D11Asynchronous* query_end;
    ID3D11Asynchronous* query_disjoint;
    HRESULT result;

    UINT64 start;
    UINT64 end;
    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT disjoint;

    assert(stamp != NULL);
    query_start = (ID3D11Asynchronous*)stamp->query_start;
    query_end = (ID3D11Asynchronous*)stamp->query_end;
    query_disjoint = (ID3D11Asynchronous*)stamp->query_disjoint;

    // Check to see if all queries are ready
    // If any fail to arrive, wait until later
    result = ID3D11DeviceContext_GetData(context, query_start, &start, sizeof(start), D3D11_ASYNC_GETDATA_DONOTFLUSH);
    if (result != S_OK)
        return result;
    result = ID3D11DeviceContext_GetData(context, query_end, &end, sizeof(end), D3D11_ASYNC_GETDATA_DONOTFLUSH);
    if (result != S_OK)
        return result;
    result = ID3D11DeviceContext_GetData(context, query_disjoint, &disjoint, sizeof(disjoint), D3D11_ASYNC_GETDATA_DONOTFLUSH);
    if (result != S_OK)
        return result;

    if (disjoint.Disjoint == FALSE)
    {
        double frequency = disjoint.Frequency / 1000000.0;

        // Mark the first timestamp
        assert(out_first_timestamp != NULL);
        if (*out_first_timestamp == 0)
            *out_first_timestamp = start;

        // Calculate start and end timestamps from the disjoint info
        *out_start = (rmtU64)((start - *out_first_timestamp) / frequency);
        *out_end = (rmtU64)((end - *out_first_timestamp) / frequency);
    }

    return S_OK;
}


typedef struct D3D11Sample
{
    // IS-A inheritance relationship
    Sample Sample;

    D3D11Timestamp* timestamp;

} D3D11Sample;


static rmtError D3D11Sample_Constructor(D3D11Sample* sample)
{
    rmtError error;

    assert(sample != NULL);

    // Chain to sample constructor
    Sample_Constructor((Sample*)sample);
    sample->Sample.type = SampleType_D3D11;
    sample->Sample.size_bytes = sizeof(D3D11Sample);
    New_0(D3D11Timestamp, sample->timestamp);

    return RMT_ERROR_NONE;
}


static void D3D11Sample_Destructor(D3D11Sample* sample)
{
    Delete(D3D11Timestamp, sample->timestamp);
    Sample_Destructor((Sample*)sample);
}


RMT_API void _rmt_BindD3D11(void* device, void* context)
{
    if (g_Remotery != NULL)
    {
        assert(g_Remotery->d3d11 != NULL);

        assert(device != NULL);
        g_Remotery->d3d11->device = (ID3D11Device*)device;
        assert(context != NULL);
        g_Remotery->d3d11->context = (ID3D11DeviceContext*)context;
    }
}


static void UpdateD3D11Frame(void);


RMT_API void _rmt_UnbindD3D11(void)
{
    if (g_Remotery != NULL)
    {
        D3D11* d3d11 = g_Remotery->d3d11;
        assert(d3d11 != NULL);

        // Stall waiting for the D3D queue to empty into the Remotery queue
        while (!rmtMessageQueue_IsEmpty(d3d11->mq_to_d3d11_main))
            UpdateD3D11Frame();

        // Inform sampler to not add any more samples
        d3d11->device = NULL;
        d3d11->context = NULL;

        // Forcefully delete sample tree on this thread to release time stamps from
        // the same thread that created them
        Remotery_BlockingDeleteSampleTree(g_Remotery, SampleType_D3D11);
    }
}


RMT_API void _rmt_BeginD3D11Sample(rmtPStr name, rmtU32* hash_cache)
{
    ThreadSampler* ts;
    D3D11* d3d11;

    if (g_Remotery == NULL)
        return;

    // Has D3D11 been unbound?
    d3d11 = g_Remotery->d3d11;
    assert(d3d11 != NULL);
    if (d3d11->device == NULL || d3d11->context == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        Sample* sample;
        rmtU32 name_hash = ThreadSampler_GetNameHash(ts, name, hash_cache);

        // Create the D3D11 tree on-demand as the tree needs an up-front-created root.
        // This is not possible to create on initialisation as a D3D11 binding is not yet available.
        SampleTree** d3d_tree = &ts->sample_trees[SampleType_D3D11];
        if (*d3d_tree == NULL)
        {
            rmtError error;
            New_3(SampleTree, *d3d_tree, sizeof(D3D11Sample), (ObjConstructor)D3D11Sample_Constructor, (ObjDestructor)D3D11Sample_Destructor);
            if (error != RMT_ERROR_NONE)
                return;
        }

        // Push the sample and activate the timestamp
        if (ThreadSampler_Push(*d3d_tree, name_hash, 0, &sample) == RMT_ERROR_NONE)
        {
            D3D11Sample* d3d_sample = (D3D11Sample*)sample;
            D3D11Timestamp_Begin(d3d_sample->timestamp, d3d11->context);
        }
    }
}


static rmtBool GetD3D11SampleTimes(Sample* sample, rmtU64* out_first_timestamp)
{
    Sample* child;

    D3D11Sample* d3d_sample = (D3D11Sample*)sample;

    assert(sample != NULL);
    if (d3d_sample->timestamp != NULL)
    {
        HRESULT result;

        D3D11* d3d11 = g_Remotery->d3d11;
        assert(d3d11 != NULL);

        result = D3D11Timestamp_GetData(
            d3d_sample->timestamp,
            d3d11->context,
            &sample->us_start,
            &sample->us_end,
            out_first_timestamp);

        if (result != S_OK)
        {
            d3d11->last_error = result;
            return RMT_FALSE;
        }

        sample->us_length = sample->us_end - sample->us_start;
    }

    // Get child sample times
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        if (!GetD3D11SampleTimes(child, out_first_timestamp))
            return RMT_FALSE;
    }

    return RMT_TRUE;
}


static void UpdateD3D11Frame(void)
{
    D3D11* d3d11;

    if (g_Remotery == NULL)
        return;

    d3d11 = g_Remotery->d3d11;
    assert(d3d11 != NULL);

    rmt_BeginCPUSample(rmt_UpdateD3D11Frame, 0);

    // Process all messages in the D3D queue
    for (;;)
    {
        Msg_SampleTree* sample_tree;
        Sample* sample;

        Message* message = rmtMessageQueue_PeekNextMessage(d3d11->mq_to_d3d11_main);
        if (message == NULL)
            break;

        // There's only one valid message type in this queue
        assert(message->id == MsgID_SampleTree);
        sample_tree = (Msg_SampleTree*)message->payload;
        sample = sample_tree->root_sample;
        assert(sample->type == SampleType_D3D11);

        // Retrieve timing of all D3D11 samples
        // If they aren't ready leave the message unconsumed, holding up later frames and maintaining order
        if (!GetD3D11SampleTimes(sample, &d3d11->first_timestamp))
            break;

        // Pass samples onto the remotery thread for sending to the viewer
        AddSampleTreeMessage(g_Remotery->mq_to_rmt_thread, sample, sample_tree->allocator, sample_tree->thread_name, message->thread_sampler);
        rmtMessageQueue_ConsumeNextMessage(d3d11->mq_to_d3d11_main, message);
    }

    rmt_EndCPUSample();
}


RMT_API void _rmt_EndD3D11Sample(void)
{
    ThreadSampler* ts;
    D3D11* d3d11;

    if (g_Remotery == NULL)
        return;

    // Has D3D11 been unbound?
    d3d11 = g_Remotery->d3d11;
    assert(d3d11 != NULL);
    if (d3d11->device == NULL || d3d11->context == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        // Close the timestamp
        D3D11Sample* d3d_sample = (D3D11Sample*)ts->sample_trees[SampleType_D3D11]->current_parent;
        if (d3d_sample->timestamp != NULL)
            D3D11Timestamp_End(d3d_sample->timestamp, d3d11->context);

        // Send to the update loop for ready-polling
        if (ThreadSampler_Pop(ts, d3d11->mq_to_d3d11_main, (Sample*)d3d_sample))
            // Perform ready-polling on popping of the root sample
            UpdateD3D11Frame();
    }
}


#endif  // RMT_USE_D3D11



/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
@OpenGL: OpenGL event sampling
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/



#if RMT_USE_OPENGL


#ifndef APIENTRY
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define APIENTRY __stdcall
#  elif (defined(_MSC_VER) && (_MSC_VER >= 800)) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#    define APIENTRY __stdcall
#  else
#    define APIENTRY
#  endif
#endif

#ifndef GLAPI
#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define GLAPI extern
#  elif defined (_WIN32)
#    define GLAPI WINGDIAPI
#  else
#    define GLAPI extern
#  endif
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY APIENTRY
#endif

typedef rmtU32 GLenum;
typedef rmtU32 GLuint;
typedef rmtS32 GLint;
typedef rmtS32 GLsizei;
typedef rmtU64 GLuint64;
typedef rmtS64 GLint64;
typedef unsigned char GLubyte;

typedef GLenum (GLAPIENTRY * PFNGLGETERRORPROC) (void);
typedef void (GLAPIENTRY * PFNGLGENQUERIESPROC) (GLsizei n, GLuint* ids);
typedef void (GLAPIENTRY * PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint* ids);
typedef void (GLAPIENTRY * PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (GLAPIENTRY * PFNGLENDQUERYPROC) (GLenum target);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint* params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint* params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64* params);
typedef void (GLAPIENTRY * PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64* params);
typedef void (GLAPIENTRY * PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);

#define GL_NO_ERROR 0
#define GL_QUERY_RESULT 0x8866
#define GL_QUERY_RESULT_AVAILABLE 0x8867
#define GL_TIME_ELAPSED 0x88BF
#define GL_TIMESTAMP 0x8E28

#define RMT_GL_GET_FUN(x) assert(g_Remotery->opengl->x != NULL); g_Remotery->opengl->x

#define rmtglGenQueries RMT_GL_GET_FUN(__glGenQueries)
#define rmtglDeleteQueries RMT_GL_GET_FUN(__glDeleteQueries)
#define rmtglBeginQuery RMT_GL_GET_FUN(__glBeginQuery)
#define rmtglEndQuery RMT_GL_GET_FUN(__glEndQuery)
#define rmtglGetQueryObjectiv RMT_GL_GET_FUN(__glGetQueryObjectiv)
#define rmtglGetQueryObjectuiv RMT_GL_GET_FUN(__glGetQueryObjectuiv)
#define rmtglGetQueryObjecti64v RMT_GL_GET_FUN(__glGetQueryObjecti64v)
#define rmtglGetQueryObjectui64v RMT_GL_GET_FUN(__glGetQueryObjectui64v)
#define rmtglQueryCounter RMT_GL_GET_FUN(__glQueryCounter)


struct OpenGL_t
{
    // Handle to the OS OpenGL DLL
    void* dll_handle;

    PFNGLGETERRORPROC __glGetError;
    PFNGLGENQUERIESPROC __glGenQueries;
    PFNGLDELETEQUERIESPROC __glDeleteQueries;
    PFNGLBEGINQUERYPROC __glBeginQuery;
    PFNGLENDQUERYPROC __glEndQuery;
    PFNGLGETQUERYOBJECTIVPROC __glGetQueryObjectiv;
    PFNGLGETQUERYOBJECTUIVPROC __glGetQueryObjectuiv;
    PFNGLGETQUERYOBJECTI64VPROC __glGetQueryObjecti64v;
    PFNGLGETQUERYOBJECTUI64VPROC __glGetQueryObjectui64v;
    PFNGLQUERYCOUNTERPROC __glQueryCounter;

    // Queue to the OpenGL main update thread
    // Given that BeginSample/EndSample need to be called from the same thread that does the update, there
    // is really no need for this to be a thread-safe queue. I'm using it for its convenience.
    rmtMessageQueue* mq_to_opengl_main;

    // Mark the first time so that remaining timestamps are offset from this
    rmtU64 first_timestamp;
};


static GLenum rmtglGetError(void)
{
    if (g_Remotery != NULL)
    {
        assert(g_Remotery->opengl != NULL);
        if (g_Remotery->opengl->__glGetError != NULL)
            return g_Remotery->opengl->__glGetError();
    }

    return (GLenum)0;
}


#ifdef RMT_PLATFORM_LINUX
    #ifdef __cplusplus
        extern "C" void* glXGetProcAddressARB(const GLubyte*);
    #else
        extern void* glXGetProcAddressARB(const GLubyte*);
    #endif
#endif


static void* rmtglGetProcAddress(OpenGL* opengl, const char* symbol)
{
    #if defined(RMT_PLATFORM_WINDOWS)
    {
        // Get OpenGL extension-loading function for each call
        typedef void* (*wglGetProcAddressFn)(LPCSTR);
        {
            assert(opengl != NULL);
            wglGetProcAddressFn wglGetProcAddress = (wglGetProcAddressFn)rmtGetProcAddress(opengl->dll_handle, "wglGetProcAddress");
            if (wglGetProcAddress != NULL)
                return wglGetProcAddress(symbol);
        }
    }

    #elif defined(RMT_PLATFORM_MACOS) && !defined(GLEW_APPLE_GLX)

        return rmtGetProcAddress(opengl->dll_handle, symbol);

    #elif defined(RMT_PLATFORM_LINUX)

        return glXGetProcAddressARB((const GLubyte*)symbol);

    #endif

    return NULL;
}


static rmtError OpenGL_Create(OpenGL** opengl)
{
    rmtError error;

    assert(opengl != NULL);

    *opengl = (OpenGL*)rmtMalloc(sizeof(OpenGL));
    if (*opengl == NULL)
        return RMT_ERROR_MALLOC_FAIL;

    (*opengl)->dll_handle = NULL;

    (*opengl)->__glGetError = NULL;
    (*opengl)->__glGenQueries = NULL;
    (*opengl)->__glDeleteQueries = NULL;
    (*opengl)->__glBeginQuery = NULL;
    (*opengl)->__glEndQuery = NULL;
    (*opengl)->__glGetQueryObjectiv = NULL;
    (*opengl)->__glGetQueryObjectuiv = NULL;
    (*opengl)->__glGetQueryObjecti64v = NULL;
    (*opengl)->__glGetQueryObjectui64v = NULL;
    (*opengl)->__glQueryCounter = NULL;

    (*opengl)->mq_to_opengl_main = NULL;
    (*opengl)->first_timestamp = 0;

    New_1(rmtMessageQueue, (*opengl)->mq_to_opengl_main, g_Settings.messageQueueSizeInBytes);
    return error;
}


static void OpenGL_Destructor(OpenGL* opengl)
{
    assert(opengl != NULL);
    Delete(rmtMessageQueue, opengl->mq_to_opengl_main);
}


typedef struct OpenGLTimestamp
{
    // Inherit so that timestamps can be quickly allocated
    ObjectLink Link;

    // Pair of timestamp queries that wrap the sample
    GLuint queries[2];
} OpenGLTimestamp;


static rmtError OpenGLTimestamp_Constructor(OpenGLTimestamp* stamp)
{
    int error;

    assert(stamp != NULL);

    ObjectLink_Constructor((ObjectLink*)stamp);

    // Set defaults
    stamp->queries[0] = stamp->queries[1] = 0;

    // Create start/end timestamp queries
    assert(g_Remotery != NULL);
    rmtglGenQueries(2, stamp->queries);
    error = rmtglGetError();
    if (error != GL_NO_ERROR)
        return RMT_ERROR_OPENGL_ERROR;

    return RMT_ERROR_NONE;
}


static void OpenGLTimestamp_Destructor(OpenGLTimestamp* stamp)
{
    assert(stamp != NULL);

    // Destroy queries
    if (stamp->queries[0] != 0)
    {
        int error;
        rmtglDeleteQueries(2, stamp->queries);
        error = rmtglGetError();
        assert(error == GL_NO_ERROR);
    }
}


static void OpenGLTimestamp_Begin(OpenGLTimestamp* stamp)
{
    assert(stamp != NULL);

    // First query
    assert(g_Remotery != NULL);
    rmtglQueryCounter(stamp->queries[0], GL_TIMESTAMP);
}


static void OpenGLTimestamp_End(OpenGLTimestamp* stamp)
{
    assert(stamp != NULL);

    // Second query
    assert(g_Remotery != NULL);
    rmtglQueryCounter(stamp->queries[1], GL_TIMESTAMP);
}


static rmtBool OpenGLTimestamp_GetData(OpenGLTimestamp* stamp, rmtU64* out_start, rmtU64* out_end, rmtU64* out_first_timestamp)
{
    GLuint64 start = 0, end = 0;
    GLint startAvailable = 0, endAvailable = 0;
    int error;

    assert(g_Remotery != NULL);

    assert(stamp != NULL);
    assert(stamp->queries[0] != 0 && stamp->queries[1] != 0);

    // Check to see if all queries are ready
    // If any fail to arrive, wait until later
    rmtglGetQueryObjectiv(stamp->queries[0], GL_QUERY_RESULT_AVAILABLE, &startAvailable);
    error = rmtglGetError();
    assert(error == GL_NO_ERROR);
    if (!startAvailable)
        return RMT_FALSE;
    rmtglGetQueryObjectiv(stamp->queries[1], GL_QUERY_RESULT_AVAILABLE, &endAvailable);
    error = rmtglGetError();
    assert(error == GL_NO_ERROR);
    if (!endAvailable)
        return RMT_FALSE;

    rmtglGetQueryObjectui64v(stamp->queries[0], GL_QUERY_RESULT, &start);
    error = rmtglGetError();
    assert(error == GL_NO_ERROR);
    rmtglGetQueryObjectui64v(stamp->queries[1], GL_QUERY_RESULT, &end);
    error = rmtglGetError();
    assert(error == GL_NO_ERROR);

    // Mark the first timestamp
    assert(out_first_timestamp != NULL);
    if (*out_first_timestamp == 0)
        *out_first_timestamp = start;

    // Calculate start and end timestamps (we want us, the queries give us ns)
    *out_start = (rmtU64)(start - *out_first_timestamp) / 1000ULL;
    *out_end = (rmtU64)(end - *out_first_timestamp) / 1000ULL;

    return RMT_TRUE;
}


typedef struct OpenGLSample
{
    // IS-A inheritance relationship
    Sample m_sample;

    OpenGLTimestamp* timestamp;

} OpenGLSample;


static rmtError OpenGLSample_Constructor(OpenGLSample* sample)
{
	rmtError error;

    assert(sample != NULL);

    // Chain to sample constructor
    Sample_Constructor((Sample*)sample);
    sample->m_sample.type = SampleType_OpenGL;
    sample->m_sample.size_bytes = sizeof(OpenGLSample);
	New_0(OpenGLTimestamp, sample->timestamp);

    return RMT_ERROR_NONE;
}


static void OpenGLSample_Destructor(OpenGLSample* sample)
{
	Delete(OpenGLTimestamp, sample->timestamp);
    Sample_Destructor((Sample*)sample);
}


RMT_API void _rmt_BindOpenGL()
{
    if (g_Remotery != NULL)
    {
        OpenGL* opengl = g_Remotery->opengl;
        assert(opengl != NULL);

        #if defined (RMT_PLATFORM_WINDOWS)
            opengl->dll_handle = rmtLoadLibrary("opengl32.dll");
        #elif defined (RMT_PLATFORM_MACOS)
            opengl->dll_handle = rmtLoadLibrary("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
        #endif

        opengl->__glGetError = (PFNGLGETERRORPROC)rmtGetProcAddress(opengl->dll_handle, "glGetError");
        opengl->__glGenQueries = (PFNGLGENQUERIESPROC)rmtglGetProcAddress(opengl, "glGenQueries");
        opengl->__glDeleteQueries = (PFNGLDELETEQUERIESPROC)rmtglGetProcAddress(opengl, "glDeleteQueries");
        opengl->__glBeginQuery = (PFNGLBEGINQUERYPROC)rmtglGetProcAddress(opengl, "glBeginQuery");
        opengl->__glEndQuery = (PFNGLENDQUERYPROC)rmtglGetProcAddress(opengl, "glEndQuery");
        opengl->__glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)rmtglGetProcAddress(opengl, "glGetQueryObjectiv");
        opengl->__glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)rmtglGetProcAddress(opengl, "glGetQueryObjectuiv");
        opengl->__glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)rmtglGetProcAddress(opengl, "glGetQueryObjecti64v");
        opengl->__glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)rmtglGetProcAddress(opengl, "glGetQueryObjectui64v");
        opengl->__glQueryCounter = (PFNGLQUERYCOUNTERPROC)rmtglGetProcAddress(opengl, "glQueryCounter");
    }
}


static void UpdateOpenGLFrame(void);


RMT_API void _rmt_UnbindOpenGL(void)
{
    if (g_Remotery != NULL)
    {
        OpenGL* opengl = g_Remotery->opengl;
        assert(opengl != NULL);

		// Stall waiting for the OpenGL queue to empty into the Remotery queue
		while (!rmtMessageQueue_IsEmpty(opengl->mq_to_opengl_main))
			UpdateOpenGLFrame();

		// Forcefully delete sample tree on this thread to release time stamps from
		// the same thread that created them
		Remotery_BlockingDeleteSampleTree(g_Remotery, SampleType_OpenGL);

        // Release reference to the OpenGL DLL
        if (opengl->dll_handle != NULL)
        {
            rmtFreeLibrary(opengl->dll_handle);
            opengl->dll_handle = NULL;
        }
    }
}


RMT_API void _rmt_BeginOpenGLSample(rmtPStr name, rmtU32* hash_cache)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        Sample* sample;
        rmtU32 name_hash = ThreadSampler_GetNameHash(ts, name, hash_cache);

        // Create the OpenGL tree on-demand as the tree needs an up-front-created root.
        // This is not possible to create on initialisation as a OpenGL binding is not yet available.
        SampleTree** ogl_tree = &ts->sample_trees[SampleType_OpenGL];
        if (*ogl_tree == NULL)
        {
			rmtError error;
			New_3(SampleTree, *ogl_tree, sizeof(OpenGLSample), (ObjConstructor)OpenGLSample_Constructor, (ObjDestructor)OpenGLSample_Destructor);
            if (error != RMT_ERROR_NONE)
                return;
        }

        // Push the sample and activate the timestamp
        if (ThreadSampler_Push(*ogl_tree, name_hash, 0, &sample) == RMT_ERROR_NONE)
        {
            OpenGLSample* ogl_sample = (OpenGLSample*)sample;
            OpenGLTimestamp_Begin(ogl_sample->timestamp);
        }
    }
}


static rmtBool GetOpenGLSampleTimes(Sample* sample, rmtU64* out_first_timestamp)
{
    Sample* child;

    OpenGLSample* ogl_sample = (OpenGLSample*)sample;

    assert(sample != NULL);
    if (ogl_sample->timestamp != NULL)
    {
        if (!OpenGLTimestamp_GetData(ogl_sample->timestamp, &sample->us_start, &sample->us_end, out_first_timestamp))
            return RMT_FALSE;

        sample->us_length = sample->us_end - sample->us_start;
    }

    // Get child sample times
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        if (!GetOpenGLSampleTimes(child, out_first_timestamp))
            return RMT_FALSE;
    }

    return RMT_TRUE;
}


static void UpdateOpenGLFrame(void)
{
    OpenGL* opengl;

    if (g_Remotery == NULL)
        return;

    opengl = g_Remotery->opengl;
    assert(opengl != NULL);

    rmt_BeginCPUSample(rmt_UpdateOpenGLFrame, 0);

    // Process all messages in the OpenGL queue
    while (1)
    {
        Msg_SampleTree* sample_tree;
        Sample* sample;

        Message* message = rmtMessageQueue_PeekNextMessage(opengl->mq_to_opengl_main);
        if (message == NULL)
            break;

        // There's only one valid message type in this queue
        assert(message->id == MsgID_SampleTree);
        sample_tree = (Msg_SampleTree*)message->payload;
        sample = sample_tree->root_sample;
        assert(sample->type == SampleType_OpenGL);

        // Retrieve timing of all OpenGL samples
        // If they aren't ready leave the message unconsumed, holding up later frames and maintaining order
        if (!GetOpenGLSampleTimes(sample, &opengl->first_timestamp))
            break;

        // Pass samples onto the remotery thread for sending to the viewer
        AddSampleTreeMessage(g_Remotery->mq_to_rmt_thread, sample, sample_tree->allocator, sample_tree->thread_name, message->thread_sampler);
        rmtMessageQueue_ConsumeNextMessage(opengl->mq_to_opengl_main, message);
    }

    rmt_EndCPUSample();
}


RMT_API void _rmt_EndOpenGLSample(void)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        // Close the timestamp
        OpenGLSample* ogl_sample = (OpenGLSample*)ts->sample_trees[SampleType_OpenGL]->current_parent;
        if (ogl_sample->timestamp != NULL)
            OpenGLTimestamp_End(ogl_sample->timestamp);

        // Send to the update loop for ready-polling
        if (ThreadSampler_Pop(ts, g_Remotery->opengl->mq_to_opengl_main, (Sample*)ogl_sample))
            // Perform ready-polling on popping of the root sample
            UpdateOpenGLFrame();
    }
}



#endif  // RMT_USE_OPENGL



/*
 ------------------------------------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------------------------------------
 @Metal: Metal event sampling
 ------------------------------------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------------------------------------
 */



#if RMT_USE_METAL



struct Metal_t
{
    // Queue to the Metal main update thread
    // Given that BeginSample/EndSample need to be called from the same thread that does the update, there
    // is really no need for this to be a thread-safe queue. I'm using it for its convenience.
    rmtMessageQueue* mq_to_metal_main;
};


static rmtError Metal_Create(Metal** metal)
{
    rmtError error;

    assert(metal != NULL);

    *metal = (Metal*)rmtMalloc(sizeof(Metal));
    if (*metal == NULL)
        return RMT_ERROR_MALLOC_FAIL;

    (*metal)->mq_to_metal_main = NULL;

    New_1(rmtMessageQueue, (*metal)->mq_to_metal_main, g_Settings.messageQueueSizeInBytes);
    return error;
}


static void Metal_Destructor(Metal* metal)
{
    assert(metal != NULL);
    Delete(rmtMessageQueue, metal->mq_to_metal_main);
}


typedef struct MetalTimestamp
{
    // Inherit so that timestamps can be quickly allocated
    ObjectLink Link;

    // Output from GPU callbacks
    rmtU64 start;
    rmtU64 end;
    rmtBool ready;
} MetalTimestamp;


static rmtError MetalTimestamp_Constructor(MetalTimestamp* stamp)
{
    assert(stamp != NULL);

    ObjectLink_Constructor((ObjectLink*)stamp);

    // Set defaults
    stamp->start = 0;
    stamp->end = 0;
    stamp->ready = RMT_FALSE;

    return RMT_ERROR_NONE;
}


static void MetalTimestamp_Destructor(MetalTimestamp* stamp)
{
    assert(stamp != NULL);
}


rmtU64 rmtMetal_usGetTime()
{
    // Share the CPU timer for auto-sync
    assert(g_Remotery != NULL);
    return usTimer_Get(&g_Remotery->timer);
}


void rmtMetal_MeasureCommandBuffer(unsigned long long* out_start, unsigned long long* out_end, unsigned int* out_ready);


static void MetalTimestamp_Begin(MetalTimestamp* stamp)
{
    assert(stamp != NULL);
    stamp->ready = RMT_FALSE;

    // Metal can currently only issue callbacks at the command buffer level
    // So for now measure execution of the entire command buffer
    rmtMetal_MeasureCommandBuffer(&stamp->start, &stamp->end, &stamp->ready);
}


static void MetalTimestamp_End(MetalTimestamp* stamp)
{
    assert(stamp != NULL);

    // As Metal can currently only measure entire command buffers, this function is a no-op
    // as the completed handler was already issued in Begin
}


static rmtBool MetalTimestamp_GetData(MetalTimestamp* stamp, rmtU64* out_start, rmtU64* out_end)
{
    assert(g_Remotery != NULL);
    assert(stamp != NULL);

    // GPU writes ready flag when complete handler is called
    if (stamp->ready == RMT_FALSE)
        return RMT_FALSE;

    *out_start = stamp->start;
    *out_end = stamp->end;

    return RMT_TRUE;
}


typedef struct MetalSample
{
    // IS-A inheritance relationship
    Sample m_sample;

    MetalTimestamp* timestamp;

} MetalSample;


static rmtError MetalSample_Constructor(MetalSample* sample)
{
    rmtError error;

    assert(sample != NULL);

    // Chain to sample constructor
    Sample_Constructor((Sample*)sample);
    sample->m_sample.type = SampleType_Metal;
    sample->m_sample.size_bytes = sizeof(MetalSample);
    New_0(MetalTimestamp, sample->timestamp);

    return RMT_ERROR_NONE;
}


static void MetalSample_Destructor(MetalSample* sample)
{
    Delete(MetalTimestamp, sample->timestamp);
    Sample_Destructor((Sample*)sample);
}


static void UpdateOpenGLFrame(void);


/*RMT_API void _rmt_UnbindMetal(void)
{
    if (g_Remotery != NULL)
    {
        Metal* metal = g_Remotery->metal;
        assert(metal != NULL);

        // Stall waiting for the Metal queue to empty into the Remotery queue
        while (!rmtMessageQueue_IsEmpty(metal->mq_to_metal_main))
            UpdateMetalFrame();

        // Forcefully delete sample tree on this thread to release time stamps from
        // the same thread that created them
        Remotery_BlockingDeleteSampleTree(g_Remotery, SampleType_Metal);
    }
}*/


RMT_API void _rmt_BeginMetalSample(rmtPStr name, rmtU32* hash_cache)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        Sample* sample;
        rmtU32 name_hash = ThreadSampler_GetNameHash(ts, name, hash_cache);

        // Create the Metal tree on-demand as the tree needs an up-front-created root.
        // This is not possible to create on initialisation as a Metal binding is not yet available.
        SampleTree** metal_tree = &ts->sample_trees[SampleType_Metal];
        if (*metal_tree == NULL)
        {
            rmtError error;
            New_3(SampleTree, *metal_tree, sizeof(MetalSample), (ObjConstructor)MetalSample_Constructor, (ObjDestructor)MetalSample_Destructor);
            if (error != RMT_ERROR_NONE)
                return;
        }

        // Push the sample and activate the timestamp
        if (ThreadSampler_Push(*metal_tree, name_hash, 0, &sample) == RMT_ERROR_NONE)
        {
            MetalSample* metal_sample = (MetalSample*)sample;
            MetalTimestamp_Begin(metal_sample->timestamp);
        }
    }
}


static rmtBool GetMetalSampleTimes(Sample* sample)
{
    Sample* child;

    MetalSample* metal_sample = (MetalSample*)sample;

    assert(sample != NULL);
    if (metal_sample->timestamp != NULL)
    {
        if (!MetalTimestamp_GetData(metal_sample->timestamp, &sample->us_start, &sample->us_end))
            return RMT_FALSE;

        sample->us_length = sample->us_end - sample->us_start;
    }

    // Get child sample times
    for (child = sample->first_child; child != NULL; child = child->next_sibling)
    {
        if (!GetMetalSampleTimes(child))
            return RMT_FALSE;
    }

    return RMT_TRUE;
}


static void UpdateMetalFrame(void)
{
    Metal* metal;

    if (g_Remotery == NULL)
        return;

    metal = g_Remotery->metal;
    assert(metal != NULL);

    rmt_BeginCPUSample(rmt_UpdateMetalFrame, 0);

    // Process all messages in the Metal queue
    while (1)
    {
        Msg_SampleTree* sample_tree;
        Sample* sample;

        Message* message = rmtMessageQueue_PeekNextMessage(metal->mq_to_metal_main);
        if (message == NULL)
            break;

        // There's only one valid message type in this queue
        assert(message->id == MsgID_SampleTree);
        sample_tree = (Msg_SampleTree*)message->payload;
        sample = sample_tree->root_sample;
        assert(sample->type == SampleType_Metal);

        // Retrieve timing of all Metal samples
        // If they aren't ready leave the message unconsumed, holding up later frames and maintaining order
        if (!GetMetalSampleTimes(sample))
            break;

        // Pass samples onto the remotery thread for sending to the viewer
        AddSampleTreeMessage(g_Remotery->mq_to_rmt_thread, sample, sample_tree->allocator, sample_tree->thread_name, message->thread_sampler);
        rmtMessageQueue_ConsumeNextMessage(metal->mq_to_metal_main, message);
    }

    rmt_EndCPUSample();
}


RMT_API void _rmt_EndMetalSample(void)
{
    ThreadSampler* ts;

    if (g_Remotery == NULL)
        return;

    if (Remotery_GetThreadSampler(g_Remotery, &ts) == RMT_ERROR_NONE)
    {
        // Close the timestamp
        MetalSample* metal_sample = (MetalSample*)ts->sample_trees[SampleType_Metal]->current_parent;
        if (metal_sample->timestamp != NULL)
            MetalTimestamp_End(metal_sample->timestamp);
        
        // Send to the update loop for ready-polling
        if (ThreadSampler_Pop(ts, g_Remotery->metal->mq_to_metal_main, (Sample*)metal_sample))
            // Perform ready-polling on popping of the root sample
            UpdateMetalFrame();
    }
}



#endif  // RMT_USE_METAL


#endif // RMT_ENABLED


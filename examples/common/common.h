/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <bx/timer.h>
#include <bx/fpumath.h>

#include "entry/entry.h"

// For a custom tinystl allocator, define this and implement TinyStlCustomAllocator somewhere in the project.
#ifndef COMMON_CONFIG_USE_TINYSTL_CUSTOM_ALLOCATOR
#	define COMMON_CONFIG_USE_TINYSTL_CUSTOM_ALLOCATOR 0
#endif // COMMON_CONFIG_USE_TINYSTL

#if COMMON_CONFIG_USE_TINYSTL_CUSTOM_ALLOCATOR
struct TinyStlCustomAllocator
{
	static void* static_allocate(size_t _bytes);
	static void static_deallocate(void* _ptr, size_t /*_bytes*/);
};
#	define TINYSTL_ALLOCATOR TinyStlCustomAllocator
#endif //COMMON_CONFIG_USE_TINYSTL_CUSTOM_ALLOCATOR

#endif // COMMON_H_HEADER_GUARD

/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED FROM IDL! DO NOT EDIT! (source : $source)
 *
 * More info about IDL:
 * https://gist.github.com/bkaradzic/05a1c86a6dd57bf86e2d828878e88dc2#bgfx-is-switching-to-idl-to-generate-api
 *
 */

#ifndef BGFX_C99_H_HEADER_GUARD
#define BGFX_C99_H_HEADER_GUARD

#include <stdarg.h>  // va_list
#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t
#include <stdlib.h>  // size_t

#include <bx/platform.h>

#if !defined(BGFX_INVALID_HANDLE)
#   define BGFX_INVALID_HANDLE { UINT16_MAX }
#endif // !defined(BGFX_INVALID_HANDLE)

#ifndef BGFX_SHARED_LIB_BUILD
#    define BGFX_SHARED_LIB_BUILD 0
#endif // BGFX_SHARED_LIB_BUILD

#ifndef BGFX_SHARED_LIB_USE
#    define BGFX_SHARED_LIB_USE 0
#endif // BGFX_SHARED_LIB_USE

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
#   define BGFX_SYMBOL_EXPORT __declspec(dllexport)
#   define BGFX_SYMBOL_IMPORT __declspec(dllimport)
#else
#   define BGFX_SYMBOL_EXPORT __attribute__((visibility("default")))
#   define BGFX_SYMBOL_IMPORT
#endif // BX_PLATFORM_WINDOWS

#if BGFX_SHARED_LIB_BUILD
#   define BGFX_SHARED_LIB_API BGFX_SYMBOL_EXPORT
#elif BGFX_SHARED_LIB_USE
#   define BGFX_SHARED_LIB_API BGFX_SYMBOL_IMPORT
#else
#   define BGFX_SHARED_LIB_API
#endif // BGFX_SHARED_LIB_*

#if defined(__cplusplus)
#   define BGFX_C_API extern "C" BGFX_SHARED_LIB_API
#else
#   define BGFX_C_API BGFX_SHARED_LIB_API
#endif // defined(__cplusplus)

#include "../defines.h"

$cenums

/**/
typedef uint16_t bgfx_view_id_t;

/**/
typedef struct bgfx_allocator_interface_s
{
	const struct bgfx_allocator_vtbl_s* vtbl;

} bgfx_allocator_interface_t;

/**/
typedef struct bgfx_allocator_vtbl_s
{
	void* (*realloc)(bgfx_allocator_interface_t* _this, void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line);

} bgfx_allocator_vtbl_t;

/**/
typedef struct bgfx_interface_vtbl bgfx_interface_vtbl_t;

/**/
typedef struct bgfx_callback_interface_s
{
	const struct bgfx_callback_vtbl_s* vtbl;

} bgfx_callback_interface_t;

/**/
typedef struct bgfx_callback_vtbl_s
{
	void (*fatal)(bgfx_callback_interface_t* _this, const char* _filePath, uint16_t _line, bgfx_fatal_t _code, const char* _str);
	void (*trace_vargs)(bgfx_callback_interface_t* _this, const char* _filePath, uint16_t _line, const char* _format, va_list _argList);
	void (*profiler_begin)(bgfx_callback_interface_t* _this, const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line);
	void (*profiler_begin_literal)(bgfx_callback_interface_t* _this, const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line);
	void (*profiler_end)(bgfx_callback_interface_t* _this);
	uint32_t (*cache_read_size)(bgfx_callback_interface_t* _this, uint64_t _id);
	bool (*cache_read)(bgfx_callback_interface_t* _this, uint64_t _id, void* _data, uint32_t _size);
	void (*cache_write)(bgfx_callback_interface_t* _this, uint64_t _id, const void* _data, uint32_t _size);
	void (*screen_shot)(bgfx_callback_interface_t* _this, const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip);
	void (*capture_begin)(bgfx_callback_interface_t* _this, uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx_texture_format_t _format, bool _yflip);
	void (*capture_end)(bgfx_callback_interface_t* _this);
	void (*capture_frame)(bgfx_callback_interface_t* _this, const void* _data, uint32_t _size);

} bgfx_callback_vtbl_t;

$chandles

#define BGFX_HANDLE_IS_VALID(h) ((h).idx != UINT16_MAX)

$cfuncptrs

$cstructs

$c99decl

/**/
typedef enum bgfx_function_id
{
	$c99_functionid

	BGFX_FUNCTION_ID_COUNT

} bgfx_function_id_t;

/**/
struct bgfx_interface_vtbl
{
	$interface_struct
};

/**/
typedef bgfx_interface_vtbl_t* (*PFN_BGFX_GET_INTERFACE)(uint32_t _version);

/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version);

#endif // BGFX_C99_H_HEADER_GUARD

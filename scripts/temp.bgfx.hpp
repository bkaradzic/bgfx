/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT! ( source : $source )
 *
 */

#ifndef BGFX_H_HEADER_GUARD
#define BGFX_H_HEADER_GUARD

#define BGFX_IDL_CPP 1

#include <stdarg.h> // va_list
#include <stdint.h> // uint32_t
#include <stdlib.h> // NULL

#include "defines.h"

///
#define BGFX_HANDLE(_name)                                                           \
	struct _name { uint16_t idx; };                                                  \
	inline bool isValid(_name _handle) { return bgfx::kInvalidHandle != _handle.idx; }

#define BGFX_INVALID_HANDLE { bgfx::kInvalidHandle }

namespace bx { struct AllocatorI; }

/// BGFX
namespace bgfx
{
	struct CallbackI;

$enums

static const uint16_t kInvalidHandle = UINT16_MAX;

	/// View id.
	typedef uint16_t ViewId;

$handles

$structs

	/// Callback interface to implement application specific behavior.
	/// Cached items are currently used for OpenGL and Direct3D 12 binary
	/// shaders.
	///
	/// @remarks
	///   'fatal' and 'trace' callbacks can be called from any thread. Other
	///   callbacks are called from the render thread.
	///
	/// @attention C99's equivalent binding is `bgfx_callback_interface_t`.
	///
	struct CallbackI
	{
		virtual ~CallbackI() = 0;

		/// This callback is called on unrecoverable errors.
		/// It's not safe to continue (Excluding _code `Fatal::DebugCheck`),
		/// inform the user and terminate the application.
		///
		/// @param[in] _filePath File path where fatal message was generated.
		/// @param[in] _line Line where fatal message was generated.
		/// @param[in] _code Fatal error code.
		/// @param[in] _str More information about error.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.fatal`.
		///
		virtual void fatal(
			  const char* _filePath
			, uint16_t _line
			, Fatal::Enum _code
			, const char* _str
			) = 0;

		/// Print debug message.
		///
		/// @param[in] _filePath File path where debug message was generated.
		/// @param[in] _line Line where debug message was generated.
		/// @param[in] _format `printf` style format.
		/// @param[in] _argList Variable arguments list initialized with
		///   `va_start`.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.trace_vargs`.
		///
		virtual void traceVargs(
			  const char* _filePath
			, uint16_t _line
			, const char* _format
			, va_list _argList
			) = 0;

		/// Profiler region begin.
		///
		/// @param[in] _name Region name, contains dynamic string.
		/// @param[in] _abgr Color of profiler region.
		/// @param[in] _filePath File path where `profilerBegin` was called.
		/// @param[in] _line Line where `profilerBegin` was called.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.profiler_begin`.
		///
		virtual void profilerBegin(
			  const char* _name
			, uint32_t _abgr
			, const char* _filePath
			, uint16_t _line
			) = 0;

		/// Profiler region begin with string literal name.
		///
		/// @param[in] _name Region name, contains string literal.
		/// @param[in] _abgr Color of profiler region.
		/// @param[in] _filePath File path where `profilerBeginLiteral` was called.
		/// @param[in] _line Line where `profilerBeginLiteral` was called.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.profiler_begin_literal`.
		///
		virtual void profilerBeginLiteral(
			  const char* _name
			, uint32_t _abgr
			, const char* _filePath
			, uint16_t _line
			) = 0;

		/// Profiler region end.
		///
		/// @remarks
		///   Not thread safe and it can be called from any thread.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.profiler_end`.
		///
		virtual void profilerEnd() = 0;

		/// Returns the size of a cached item. Returns 0 if no cached item was
		/// found.
		///
		/// @param[in] _id Cache id.
		/// @returns Number of bytes to read.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.cache_read_size`.
		///
		virtual uint32_t cacheReadSize(uint64_t _id) = 0;

		/// Read cached item.
		///
		/// @param[in] _id Cache id.
		/// @param[in] _data Buffer where to read data.
		/// @param[in] _size Size of data to read.
		///
		/// @returns True if data is read.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.cache_read`.
		///
		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) = 0;

		/// Write cached item.
		///
		/// @param[in] _id Cache id.
		/// @param[in] _data Data to write.
		/// @param[in] _size Size of data to write.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.cache_write`.
		///
		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) = 0;

		/// Screenshot captured. Screenshot format is always 4-byte BGRA.
		///
		/// @param[in] _filePath File path.
		/// @param[in] _width Image width.
		/// @param[in] _height Image height.
		/// @param[in] _pitch Number of bytes to skip between the start of
		///   each horizontal line of the image.
		/// @param[in] _data Image data.
		/// @param[in] _size Image size.
		/// @param[in] _yflip If true, image origin is bottom left.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.screen_shot`.
		///
		virtual void screenShot(
			  const char* _filePath
			, uint32_t _width
			, uint32_t _height
			, uint32_t _pitch
			, const void* _data
			, uint32_t _size
			, bool _yflip
			) = 0;

		/// Called when a video capture begins.
		///
		/// @param[in] _width Image width.
		/// @param[in] _height Image height.
		/// @param[in] _pitch Number of bytes to skip between the start of
		///   each horizontal line of the image.
		/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
		/// @param[in] _yflip If true, image origin is bottom left.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.capture_begin`.
		///
		virtual void captureBegin(
			  uint32_t _width
			, uint32_t _height
			, uint32_t _pitch
			, TextureFormat::Enum _format
			, bool _yflip
			) = 0;

		/// Called when a video capture ends.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.capture_end`.
		///
		virtual void captureEnd() = 0;

		/// Captured frame.
		///
		/// @param[in] _data Image data.
		/// @param[in] _size Image size.
		///
		/// @attention C99's equivalent binding is `bgfx_callback_vtbl.capture_frame`.
		///
		virtual void captureFrame(const void* _data, uint32_t _size) = 0;
	};

	inline CallbackI::~CallbackI()
	{
	}

$funcptrs

$cppdecl

inline bool VertexLayout::has(Attrib::Enum _attrib) const { return UINT16_MAX != m_attributes[_attrib]; }

inline uint16_t VertexLayout::getOffset(Attrib::Enum _attrib) const { return m_offset[_attrib]; }

inline uint16_t VertexLayout::getStride() const { return m_stride; }

inline uint32_t VertexLayout::getSize(uint32_t _num) const { return _num*m_stride; }

} // namespace bgfx

#endif // BGFX_H_HEADER_GUARD

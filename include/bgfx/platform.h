/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_PLATFORM_H_HEADER_GUARD
#define BGFX_PLATFORM_H_HEADER_GUARD

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

#include <bx/platform.h>
#include "bgfx.h"

namespace bgfx
{
	/// Render frame enum.
	///
	/// @attention C99 equivalent is `bgfx_render_frame_t`.
	///
	struct RenderFrame
	{
		enum Enum
		{
			NoContext,
			Render,
			Timeout,
			Exiting,

			Count
		};
	};

	/// Render frame.
	///
	/// @param _msecs Timeout in milliseconds.
	///
	/// @returns Current renderer state. See: `bgfx::RenderFrame`.
	///
	/// @attention `bgfx::renderFrame` is blocking call. It waits for
	///   `bgfx::frame` to be called from API thread to process frame.
	///   If timeout value is passed call will timeout and return even
	///   if `bgfx::frame` is not called.
	///
	/// @warning This call should be only used on platforms that don't
	///   allow creating separate rendering thread. If it is called before
	///   to bgfx::init, render thread won't be created by bgfx::init call.
	RenderFrame::Enum renderFrame(int32_t _msecs = -1);

	/// Platform data.
	///
	/// @attention C99 equivalent is `bgfx_platform_data_t`.
	///
	struct PlatformData
	{
		void* ndt;          //!< Native display type.
		void* nwh;          //!< Native window handle.
		void* context;      //!< GL context, or D3D device.
		void* backBuffer;   //!< GL backbuffer, or D3D render target view.
		void* backBufferDS; //!< Backbuffer depth/stencil.
		void* session;      //!< ovrSession, for Oculus SDK
	};

	/// Set platform data.
	///
	/// @warning Must be called before `bgfx::init`.
	///
	/// @attention C99 equivalent is `bgfx_set_platform_data`.
	///
	void setPlatformData(const PlatformData& _data);

	/// Internal data.
	///
	/// @attention C99 equivalent is `bgfx_internal_data_t`.
	///
	struct InternalData
	{
		const struct Caps* caps; //!< Renderer capabilities.
		void* context;           //!< GL context, or D3D device.
	};

	/// Get internal data for interop.
	///
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	///
	/// @warning Must be called only on render thread.
	///
	/// @attention C99 equivalent is `bgfx_get_internal_data`.
	///
	const InternalData* getInternalData();

	/// Override internal texture with externally created texture. Previously
	/// created internal texture will released.
	///
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _ptr Native API pointer to texture.
	///
	/// @returns Native API pointer to texture. If result is 0, texture is not created yet from the
	///   main thread.
	///
	/// @warning Must be called only on render thread.
	///
	/// @attention C99 equivalent is `bgfx_override_internal_texture_ptr`.
	///
	uintptr_t overrideInternal(TextureHandle _handle, uintptr_t _ptr);

	/// Override internal texture by creating new texture. Previously created
	/// internal texture will released.
	///
	/// @attention It's expected you understand some bgfx internals before you
	///   use this call.
	///
	/// @param[in] _handle Texture handle.
	/// @param[in] _width Width.
	/// @param[in] _height Height.
	/// @param[in] _numMips Number of mip-maps.
	/// @param[in] _format Texture format. See: `TextureFormat::Enum`.
	/// @param[in] _flags Default texture sampling mode is linear, and wrap mode
	///   is repeat.
	///   - `BGFX_TEXTURE_[U/V/W]_[MIRROR/CLAMP]` - Mirror or clamp to edge wrap
	///     mode.
	///   - `BGFX_TEXTURE_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]` - Point or anisotropic
	///     sampling.
	///
	/// @returns Native API pointer to texture. If result is 0, texture is not created yet from the
	///   main thread.
	///
	/// @warning Must be called only on render thread.
	///
	/// @attention C99 equivalent is `bgfx_override_internal_texture`.
	///
	uintptr_t overrideInternal(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags = BGFX_TEXTURE_NONE);

} // namespace bgfx

#endif // BGFX_PLATFORM_H_HEADER_GUARD

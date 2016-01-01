/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_OVR_H_HEADER_GUARD
#define BGFX_OVR_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_USE_OVR

#	include <OVR_Version.h>

#	define OVR_VERSION_(_a, _b, _c) (_a * 10000 + _b * 100 + _c)
#	define OVR_VERSION     OVR_VERSION_(OVR_PRODUCT_VERSION, OVR_MAJOR_VERSION, OVR_MINOR_VERSION)
#	define OVR_VERSION_042 OVR_VERSION_(0, 4, 2)
#	define OVR_VERSION_043 OVR_VERSION_(0, 4, 3)
#	define OVR_VERSION_044 OVR_VERSION_(0, 4, 4)
#	define OVR_VERSION_050 OVR_VERSION_(0, 5, 0)

#	if OVR_VERSION < OVR_VERSION_050
#		include <OVR.h>
#	else
#		include <OVR_CAPI.h>
#	endif // OVR_VERSION < OVR_VERSION_050

#	if BGFX_CONFIG_RENDERER_DIRECT3D11
#		if OVR_VERSION < OVR_VERSION_050
#			define OVR_D3D_VERSION 11
#			include <OVR_D3D.h>
#		else
#			include <OVR_CAPI_D3D.h>
#		endif
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#	if BGFX_CONFIG_RENDERER_OPENGL
#		if OVR_VERSION < OVR_VERSION_050
#			include <OVR_GL.h>
#		else
#			include <OVR_CAPI_GL.h>
#		endif
#	endif // BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
	struct OVR
	{
		OVR();
		~OVR();

		bool isInitialized() const
		{
			return NULL != m_hmd;
		}

		bool isEnabled() const
		{
			return m_isenabled;
		}

		bool isDebug() const
		{
			return m_debug;
		}

		void init();
		void shutdown();

		void getViewport(uint8_t _eye, Rect* _viewport);
		bool postReset(void* _nwh, ovrRenderAPIConfig* _config, bool _debug = false);
		void postReset(const ovrTexture& _texture);
		void preReset();
		bool swap(HMD& _hmd);
		void recenter();
		void getEyePose(HMD& _hmd);
		void getSize(uint32_t& _width, uint32_t& _height) const
		{
			_width  = m_rtSize.w;
			_height = m_rtSize.h;
		}

		ovrHmd m_hmd;
		ovrFrameTiming m_timing;
		ovrEyeRenderDesc m_erd[2];
		ovrRecti m_rect[2];
		ovrPosef m_pose[2];
		ovrTexture m_texture[2];
		ovrSizei m_rtSize;
		bool m_warning;
		bool m_isenabled;
		bool m_debug;
	};

} // namespace bgfx

#else

namespace bgfx
{
	struct OVR
	{
		OVR()
		{
		}

		~OVR()
		{
		}

		bool isInitialized() const
		{
			return false;
		}

		bool isEnabled() const
		{
			return false;
		}

		bool isDebug() const
		{
			return false;
		}

		void init()
		{
		}

		void shutdown()
		{
		}

		void getViewport(uint8_t /*_eye*/, Rect* _viewport)
		{
			_viewport->m_x      = 0;
			_viewport->m_y      = 0;
			_viewport->m_width  = 0;
			_viewport->m_height = 0;
		}

		bool swap(HMD& _hmd)
		{
			_hmd.flags = BGFX_HMD_NONE;
			getEyePose(_hmd);
			return false;
		}

		void recenter()
		{
		}

		void getEyePose(HMD& _hmd)
		{
			_hmd.width  = 0;
			_hmd.height = 0;
		}

		void getSize(uint32_t& _width, uint32_t& _height) const
		{
			_width  = 0;
			_height = 0;
		}
	};

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

#endif // BGFX_OVR_H_HEADER_GUARD

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_OVR_H_HEADER_GUARD
#define BGFX_OVR_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_USE_OVR

#	include <OVR.h>

#	define OVR_VERSION_(_a, _b, _c) (_a * 10000 + _b * 100 + _c)
#	define OVR_VERSION     OVR_VERSION_(OVR_MAJOR_VERSION, OVR_MINOR_VERSION, OVR_BUILD_VERSION)
#	define OVR_VERSION_042 OVR_VERSION_(0, 4, 2)
#	define OVR_VERSION_043 OVR_VERSION_(0, 4, 3)
#	define OVR_VERSION_044 OVR_VERSION_(0, 4, 4)

#	if BGFX_CONFIG_RENDERER_DIRECT3D9
#		define OVR_D3D_VERSION 9
#		include <OVR_D3D.h>
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D9

#	if BGFX_CONFIG_RENDERER_DIRECT3D11
#		ifdef OVR_CAPI_D3D_h
#			undef OVR_CAPI_D3D_h
#			undef OVR_D3D_VERSION
#		endif // OVR_CAPI_D3D_h
#		define OVR_D3D_VERSION 11
#		include <OVR_D3D.h>
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#	if BGFX_CONFIG_RENDERER_OPENGL
#		include <OVR_GL.h>
#	endif // BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
	struct OVR
	{
		OVR();
		~OVR();

		bool isInitialized() const
		{
			return m_initialized;
		}

		bool isEnabled() const
		{
			return NULL != m_hmd;
		}

		bool isDebug() const
		{
			return m_debug;
		}

		void init();
		void shutdown();

		bool postReset(void* _nwh, ovrRenderAPIConfig* _config, bool _debug = false);
		void postReset(const ovrTexture& _texture);
		void preReset();
		bool swap();
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
		bool m_initialized;
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

		void init()
		{
		}

		void shutdown()
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

		bool swap()
		{
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

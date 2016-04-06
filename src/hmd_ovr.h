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

#	include <OVR_CAPI.h>

#	if BGFX_CONFIG_RENDERER_DIRECT3D11
#		include <OVR_CAPI_D3D.h>
#	endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#	if BGFX_CONFIG_RENDERER_OPENGL
#		include <OVR_CAPI_GL.h>
#	endif // BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
	// single eye buffer
	struct OVRBufferI
	{
		virtual ~OVRBufferI() {};
		virtual void create(const ovrSession& _session, int _eyeIdx) = 0;
		virtual void destroy(const ovrSession& _session) = 0;
		virtual void render(const ovrSession& _session) = 0;

		ovrSizei m_eyeTextureSize;
		ovrTextureSwapChain m_textureSwapChain;
	};

	// mirrored window output
	struct OVRMirrorI
	{
		virtual ~OVRMirrorI() {};
		virtual void create(const ovrSession& _session, int windowWidth, int windowHeight) = 0;
		virtual void destroy(const ovrSession& _session) = 0;
		virtual void blit(const ovrSession& _session) = 0;

		ovrMirrorTexture     m_mirrorTexture;
		ovrMirrorTextureDesc m_mirrorTextureDesc;
	};

	struct OVR
	{
		enum Enum
		{
			NotEnabled,
			DeviceLost,
			Success,

			Count
		};

		OVR();
		~OVR();

		bool isInitialized() const
		{
			return NULL != m_hmd;
		}

		bool isEnabled() const
		{
			return m_enabled;
		}

		void init();
		void shutdown();

		void getViewport(uint8_t _eye, Rect* _viewport);
		void renderEyeStart(uint8_t _eye);
		bool postReset();
		void preReset();
		Enum swap(HMD& _hmd, bool originBottomLeft);
		void recenter();
		void getEyePose(HMD& _hmd);

		ovrSession m_hmd;
		ovrHmdDesc m_hmdDesc;
		ovrEyeRenderDesc m_erd[2];
		ovrRecti    m_rect[2];
		ovrPosef    m_pose[2];
		ovrVector3f m_hmdToEyeOffset[2];
		ovrSizei    m_hmdSize;
		OVRBufferI *m_eyeBuffers[2];
		OVRMirrorI *m_mirror;
		uint64_t    m_frameIndex;
		double      m_sensorSampleTime;
		bool m_enabled;
	};

} // namespace bgfx

#else

namespace bgfx
{
	struct OVR
	{
		enum Enum
		{
			NotEnabled,
			DeviceLost,
			Success,

			Count
		};

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

		void renderEyeStart(uint8_t /*_eye*/)
		{
		}

		Enum swap(HMD& _hmd, bool /*originBottomLeft*/)
		{
			_hmd.flags = BGFX_HMD_NONE;
			getEyePose(_hmd);
			return NotEnabled;
		}

		void recenter()
		{
		}

		void getEyePose(HMD& _hmd)
		{
			_hmd.width  = 0;
			_hmd.height = 0;
		}
	};

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

#endif // BGFX_OVR_H_HEADER_GUARD

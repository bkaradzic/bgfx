/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_OVR_H_HEADER_GUARD
#define BGFX_OVR_H_HEADER_GUARD

#include "bgfx_p.h"

#if BGFX_CONFIG_USE_OVR

#	include "hmd.h"
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
	class VRImplOVR : public VRImplI
	{
	public:
		VRImplOVR();
		virtual ~VRImplOVR() = 0;

		virtual bool init();
		virtual void shutdown();
		virtual void connect(VRDesc* _desc);
		virtual void disconnect();

		virtual bool isConnected() const
		{
			return NULL != m_session;
		}

		virtual bool updateTracking(HMD& _hmd);
		virtual void updateInput(HMD& _hmd);
		virtual void recenter();

		virtual bool createSwapChain(const VRDesc& _desc, int _msaaSamples, int _mirrorWidth, int _mirrorHeight) = 0;
		virtual void destroySwapChain() = 0;
		virtual void destroyMirror() = 0;
		virtual void renderEyeStart(const VRDesc& _desc, uint8_t _eye) = 0;
		virtual bool submitSwapChain(const VRDesc& _desc) = 0;

	protected:
		ovrSession m_session;
		ovrLayerEyeFov m_renderLayer;
		ovrViewScaleDesc m_viewScale;
		ovrFovPort m_eyeFov[2];
		ovrVector2f m_pixelsPerTanAngleAtCenter[2];
	};

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

#endif // BGFX_OVR_H_HEADER_GUARD

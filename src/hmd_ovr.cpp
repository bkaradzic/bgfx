/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_USE_OVR

#include "hmd_ovr.h"

namespace bgfx
{
#define _OVR_CHECK(_call) \
			BX_MACRO_BLOCK_BEGIN \
				ovrResult __result__ = _call; \
				BX_CHECK(OVR_SUCCESS(__result__), #_call " FAILED %d", __result__); \
			BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define OVR_CHECK(_call) _OVR_CHECK(_call)
#else
#	define OVR_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

	VRImplOVR::VRImplOVR()
		: m_session(NULL)
	{
	}

	VRImplOVR::~VRImplOVR()
	{
		if (NULL != g_platformData.session)
		{
			return;
		}

		BX_CHECK(NULL == m_session, "OVR not shutdown properly.");
	}

	bool VRImplOVR::init()
	{
		if (NULL != g_platformData.session)
		{
			return true;
		}

		ovrResult initialized = ovr_Initialize(NULL);
		if (!OVR_SUCCESS(initialized))
		{
			BX_TRACE("Unable to initialize OVR runtime.");
			return false;
		}

		return true;
	}

	void VRImplOVR::shutdown()
	{
		if (NULL != g_platformData.session)
		{
			return;
		}

		ovr_Shutdown();
	}

	void VRImplOVR::connect(VRDesc* _desc)
	{
		if (NULL == g_platformData.session)
		{
			ovrGraphicsLuid luid;
			ovrResult result = ovr_Create(&m_session, &luid);
			if (!OVR_SUCCESS(result))
			{
				BX_TRACE("Failed to create OVR device.");
				return;
			}
		}
		else
		{
			m_session = (ovrSession)g_platformData.session;
		}

		ovrHmdDesc hmdDesc = ovr_GetHmdDesc(m_session);
		_desc->m_deviceType = hmdDesc.Type;
		_desc->m_refreshRate = hmdDesc.DisplayRefreshRate;
		_desc->m_deviceSize.m_w = hmdDesc.Resolution.w;
		_desc->m_deviceSize.m_h = hmdDesc.Resolution.h;

		BX_TRACE("OVR HMD: %s, %s, firmware: %d.%d"
			, hmdDesc.ProductName
			, hmdDesc.Manufacturer
			, hmdDesc.FirmwareMajor
			, hmdDesc.FirmwareMinor
			);

		ovrSizei eyeSize[2] =
		{
			ovr_GetFovTextureSize(m_session, ovrEye_Left, hmdDesc.DefaultEyeFov[0], 1.0f),
			ovr_GetFovTextureSize(m_session, ovrEye_Right, hmdDesc.DefaultEyeFov[0], 1.0f),
		};

		for (int eye = 0; eye < 2; ++eye)
		{
			BX_STATIC_ASSERT(sizeof(_desc->m_eyeFov[eye]) == sizeof(hmdDesc.DefaultEyeFov[eye]));
			bx::memCopy(&_desc->m_eyeFov[eye], &hmdDesc.DefaultEyeFov[eye], sizeof(_desc->m_eyeFov[eye]));
			_desc->m_eyeSize[eye].m_w = eyeSize[eye].w;
			_desc->m_eyeSize[eye].m_h = eyeSize[eye].h;
		}

		float neckOffset[2] = {OVR_DEFAULT_NECK_TO_EYE_HORIZONTAL, OVR_DEFAULT_NECK_TO_EYE_VERTICAL};
		ovr_GetFloatArray(m_session, OVR_KEY_NECK_TO_EYE_DISTANCE, neckOffset, 2);
		_desc->m_neckOffset[0] = neckOffset[0];
		_desc->m_neckOffset[1] = neckOffset[1];

		// build constant layer settings
		m_renderLayer.Header.Type = ovrLayerType_EyeFov;
		m_renderLayer.Header.Flags = 0;
		m_renderLayer.Fov[0] = hmdDesc.DefaultEyeFov[0];
		m_renderLayer.Fov[1] = hmdDesc.DefaultEyeFov[1];
		m_renderLayer.Viewport[0].Pos.x = 0;
		m_renderLayer.Viewport[0].Pos.y = 0;
		m_renderLayer.Viewport[0].Size.w = _desc->m_eyeSize[0].m_w;
		m_renderLayer.Viewport[0].Size.h = _desc->m_eyeSize[0].m_h;
		m_renderLayer.Viewport[1].Pos.x = _desc->m_eyeSize[0].m_w+1;
		m_renderLayer.Viewport[1].Pos.y = 0;
		m_renderLayer.Viewport[1].Size.w = _desc->m_eyeSize[1].m_w;
		m_renderLayer.Viewport[1].Size.h = _desc->m_eyeSize[1].m_h;

		m_viewScale.HmdSpaceToWorldScaleInMeters = 1.0f;
		for (int eye = 0; eye < 2; ++eye)
		{
			ovrEyeRenderDesc erd = ovr_GetRenderDesc(m_session, static_cast<ovrEyeType>(eye), hmdDesc.DefaultEyeFov[eye]);
			m_viewScale.HmdToEyeOffset[eye] = erd.HmdToEyeOffset;
			m_eyeFov[eye] = erd.Fov;
			m_pixelsPerTanAngleAtCenter[eye] = erd.PixelsPerTanAngleAtCenter;
		}
	}

	void VRImplOVR::disconnect()
	{
		if (NULL != g_platformData.session)
		{
			return;
		}

		if (NULL != m_session)
		{
			ovr_Destroy(m_session);
			m_session = NULL;
		}
	}

	bool VRImplOVR::updateTracking(HMD& _hmd)
	{
		if (NULL == m_session)
		{
			return false;
		}

		ovr_GetEyePoses(m_session, 0, ovrTrue, m_viewScale.HmdToEyeOffset, m_renderLayer.RenderPose, &m_renderLayer.SensorSampleTime);

		for (int eye = 0; eye < 2; ++eye)
		{
			const ovrPosef& pose = m_renderLayer.RenderPose[eye];
			HMD::Eye& hmdEye = _hmd.eye[eye];

			hmdEye.rotation[0] = pose.Orientation.x;
			hmdEye.rotation[1] = pose.Orientation.y;
			hmdEye.rotation[2] = pose.Orientation.z;
			hmdEye.rotation[3] = pose.Orientation.w;
			hmdEye.translation[0] = pose.Position.x;
			hmdEye.translation[1] = pose.Position.y;
			hmdEye.translation[2] = pose.Position.z;
			hmdEye.viewOffset[0] = -m_viewScale.HmdToEyeOffset[eye].x;
			hmdEye.viewOffset[1] = -m_viewScale.HmdToEyeOffset[eye].y;
			hmdEye.viewOffset[2] = -m_viewScale.HmdToEyeOffset[eye].z;

			hmdEye.pixelsPerTanAngle[0] = m_pixelsPerTanAngleAtCenter[eye].x;
			hmdEye.pixelsPerTanAngle[1] = m_pixelsPerTanAngleAtCenter[eye].y;

			ovrMatrix4f projection = ovrMatrix4f_Projection(m_eyeFov[eye], 0.1f, 1000.0f, ovrProjection_LeftHanded);
			for (uint32_t ii = 0; ii < 4; ++ii)
			{
				for (uint32_t jj = 0; jj < 4; ++jj)
				{
					hmdEye.projection[4*ii + jj] = projection.M[jj][ii];
				}
			}
		}

		return true;
	}

	void VRImplOVR::updateInput(HMD& /* _hmd */)
	{
	}

	void VRImplOVR::recenter()
	{
		if (NULL != m_session)
		{
			ovr_RecenterTrackingOrigin(m_session);
		}
	}

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

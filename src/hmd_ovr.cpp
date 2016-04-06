/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "hmd_ovr.h"

#if BGFX_CONFIG_USE_OVR

namespace bgfx
{
#define _OVR_CHECK(_call) \
			BX_MACRO_BLOCK_BEGIN \
				ovrResult __result__ = _call; \
				BX_CHECK(OVR_SUCCESS(__result__), #_call " FAILED %d", __result__); \
			BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define OVR_CHECK(_call) _OVR_CHECK(_call)
#endif // BGFX_CONFIG_DEBUG

	OVR::OVR()
		: m_hmd(NULL)
		, m_enabled(false)
		, m_mirror(NULL)
		, m_frameIndex(0)
		, m_sensorSampleTime(0)
	{
		memset(m_eyeBuffers, 0, sizeof(m_eyeBuffers));
	}

	OVR::~OVR()
	{
		BX_CHECK(NULL == m_hmd, "OVR not shutdown properly.");
	}

	void OVR::init()
	{
		ovrResult result = ovr_Initialize(NULL);

		if (result != ovrSuccess)
		{
			BX_TRACE("Unable to create OVR device.");
			return;
		}

		ovrGraphicsLuid luid;
		result = ovr_Create(&m_hmd, &luid);
		if (result != ovrSuccess)
		{
			BX_TRACE("Unable to create OVR device.");
			return;
		}

		m_hmdDesc = ovr_GetHmdDesc(m_hmd);

		BX_TRACE("HMD: %s, %s, firmware: %d.%d"
			, m_hmdDesc.ProductName
			, m_hmdDesc.Manufacturer
			, m_hmdDesc.FirmwareMajor
			, m_hmdDesc.FirmwareMinor
			);

		ovrSizei sizeL = ovr_GetFovTextureSize(m_hmd, ovrEye_Left,  m_hmdDesc.DefaultEyeFov[0], 1.0f);
		ovrSizei sizeR = ovr_GetFovTextureSize(m_hmd, ovrEye_Right, m_hmdDesc.DefaultEyeFov[1], 1.0f);
		m_hmdSize.w = sizeL.w + sizeR.w;
		m_hmdSize.h = bx::uint32_max(sizeL.h, sizeR.h);
	}

	void OVR::shutdown()
	{
		BX_CHECK(!m_enabled, "HMD not disabled.");

		for (uint32_t ii = 0; ii < 2; ++ii)
		{
			if (NULL != m_eyeBuffers[ii])
			{
				m_eyeBuffers[ii]->destroy(m_hmd);
				m_eyeBuffers[ii] = NULL;
			}
		}

		if (NULL != m_mirror)
		{
			m_mirror->destroy(m_hmd);
			m_mirror = NULL;
		}

		ovr_Destroy(m_hmd);
		m_hmd = NULL;
		ovr_Shutdown();
	}

	void OVR::getViewport(uint8_t _eye, Rect* _viewport)
	{
		_viewport->m_x      = 0;
		_viewport->m_y      = 0;
		_viewport->m_width  = m_eyeBuffers[_eye]->m_eyeTextureSize.w;
		_viewport->m_height = m_eyeBuffers[_eye]->m_eyeTextureSize.h;
	}

	void OVR::renderEyeStart(uint8_t _eye)
	{
		m_eyeBuffers[_eye]->render(m_hmd);
	}

	bool OVR::postReset()
	{
		if (NULL == m_hmd)
		{
			return false;
		}

		for (uint32_t ii = 0; ii < 2; ++ii)
		{
			m_erd[ii] = ovr_GetRenderDesc(m_hmd, ovrEyeType(ii), m_hmdDesc.DefaultEyeFov[ii]);
		}

		m_enabled = true;

		return true;
	}

	void OVR::preReset()
	{
		if (m_enabled)
		{
			// on window resize this will recreate the mirror texture in ovrPostReset
			m_mirror->destroy(m_hmd);
			m_mirror = NULL;
			m_enabled = false;
		}
	}

	OVR::Enum OVR::swap(HMD& _hmd, bool originBottomLeft)
	{
		_hmd.flags = BGFX_HMD_NONE;

		if (NULL != m_hmd)
		{
			_hmd.flags |= BGFX_HMD_DEVICE_RESOLUTION;
			_hmd.deviceWidth  = m_hmdDesc.Resolution.w;
			_hmd.deviceHeight = m_hmdDesc.Resolution.h;
		}

		if (!m_enabled)
		{
			return NotEnabled;
		}

		ovrResult result;

		for (uint32_t ii = 0; ii < 2; ++ii)
		{
			result = ovr_CommitTextureSwapChain(m_hmd, m_eyeBuffers[ii]->m_textureSwapChain);
			if (!OVR_SUCCESS(result) )
			{
				return DeviceLost;
			}
		}

		_hmd.flags |= BGFX_HMD_RENDERING;

		// finish frame for current eye
		ovrViewScaleDesc viewScaleDesc;
		viewScaleDesc.HmdSpaceToWorldScaleInMeters = 1.0f;
		viewScaleDesc.HmdToEyeOffset[0] = m_hmdToEyeOffset[0];
		viewScaleDesc.HmdToEyeOffset[1] = m_hmdToEyeOffset[1];

		// create the main eye layer
		ovrLayerEyeFov eyeLayer;
		eyeLayer.Header.Type = ovrLayerType_EyeFov;
		eyeLayer.Header.Flags = originBottomLeft ? ovrLayerFlag_TextureOriginAtBottomLeft : 0;

		for (uint32_t ii = 0; ii < 2; ++ii)
		{
			eyeLayer.ColorTexture[ii]    = m_eyeBuffers[ii]->m_textureSwapChain;
			eyeLayer.Viewport[ii].Pos.x  = 0;
			eyeLayer.Viewport[ii].Pos.y  = 0;
			eyeLayer.Viewport[ii].Size.w = m_eyeBuffers[ii]->m_eyeTextureSize.w;
			eyeLayer.Viewport[ii].Size.h = m_eyeBuffers[ii]->m_eyeTextureSize.h;
			eyeLayer.Fov[ii]             = m_hmdDesc.DefaultEyeFov[ii];
			eyeLayer.RenderPose[ii]      = m_pose[ii];
			eyeLayer.SensorSampleTime    = m_sensorSampleTime;
		}

		// append all the layers to global list
		ovrLayerHeader* layerList = &eyeLayer.Header;

		result = ovr_SubmitFrame(m_hmd, m_frameIndex, NULL, &layerList, 1);
		if (!OVR_SUCCESS(result) )
		{
			return DeviceLost;
		}

		// perform mirror texture blit right after the entire frame is submitted to HMD
		m_mirror->blit(m_hmd);

		m_hmdToEyeOffset[0] = m_erd[0].HmdToEyeOffset;
		m_hmdToEyeOffset[1] = m_erd[1].HmdToEyeOffset;

		ovr_GetEyePoses(m_hmd, m_frameIndex, ovrTrue, m_hmdToEyeOffset, m_pose, &m_sensorSampleTime);

		getEyePose(_hmd);

		return Success;
	}

	void OVR::recenter()
	{
		if (NULL != m_hmd)
		{
			OVR_CHECK(ovr_RecenterTrackingOrigin(m_hmd) );
		}
	}

	void OVR::getEyePose(HMD& _hmd)
	{
		if (NULL != m_hmd)
		{
			for (uint32_t ii = 0; ii < 2; ++ii)
			{
				const ovrPosef& pose = m_pose[ii];
				HMD::Eye& eye = _hmd.eye[ii];
				eye.rotation[0] = pose.Orientation.x;
				eye.rotation[1] = pose.Orientation.y;
				eye.rotation[2] = pose.Orientation.z;
				eye.rotation[3] = pose.Orientation.w;
				eye.translation[0] = pose.Position.x;
				eye.translation[1] = pose.Position.y;
				eye.translation[2] = pose.Position.z;

				const ovrEyeRenderDesc& erd = m_erd[ii];
				eye.fov[0] = erd.Fov.UpTan;
				eye.fov[1] = erd.Fov.DownTan;
				eye.fov[2] = erd.Fov.LeftTan;
				eye.fov[3] = erd.Fov.RightTan;

				ovrMatrix4f eyeProj = ovrMatrix4f_Projection(m_erd[ii].Fov, 0.01f, 1000.0f, ovrProjection_LeftHanded);
				for (uint32_t jj = 0; jj < 4; ++jj)
				{
					for (uint32_t kk = 0; kk < 4; ++kk)
					{
						eye.projection[4 * jj + kk] = eyeProj.M[kk][jj];
					}
				}

				eye.viewOffset[0] = erd.HmdToEyeOffset.x;
				eye.viewOffset[1] = erd.HmdToEyeOffset.y;
				eye.viewOffset[2] = erd.HmdToEyeOffset.z;

				eye.pixelsPerTanAngle[0] = erd.PixelsPerTanAngleAtCenter.x;
				eye.pixelsPerTanAngle[1] = erd.PixelsPerTanAngleAtCenter.y;
			}
		}

		_hmd.width  = uint16_t(m_hmdSize.w);
		_hmd.height = uint16_t(m_hmdSize.h);
	}

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

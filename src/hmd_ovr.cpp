/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "hmd_ovr.h"

#if BGFX_CONFIG_USE_OVR

namespace bgfx
{
	OVR::OVR()
		: m_hmd(NULL)
		, m_isenabled(false)
		, m_mirror(NULL)
		, m_hmdFrameReady(-1)
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
		ovrResult initialized = ovr_Initialize(NULL);
		ovrGraphicsLuid luid;

		BX_WARN(initialized == ovrSuccess, "Unable to create OVR device.");
		
		if (initialized != ovrSuccess)
		{
			return;
		}

		initialized = ovr_Create(&m_hmd, &luid);
		if (initialized != ovrSuccess)
		{
			BX_WARN(initialized == ovrSuccess, "Unable to create OVR device.");
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
		BX_CHECK(!m_isenabled, "HMD not disabled.");

		for (int i = 0; i < 2; i++)
		{
			if (m_eyeBuffers[i])
			{
				m_eyeBuffers[i]->destroy(m_hmd);
				BX_DELETE(g_allocator, m_eyeBuffers[i]);
			}
		}

		if (m_mirror)
		{
			m_mirror->destroy(m_hmd);
			BX_DELETE(g_allocator, m_mirror);
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
		m_eyeBuffers[_eye]->onRender(m_hmd);
	}

	bool OVR::postReset()
	{
		if (NULL == m_hmd)
		{
			return false;
		}

		for (int eyeIdx = 0; eyeIdx < ovrEye_Count; eyeIdx++)
		{
			m_erd[eyeIdx] = ovr_GetRenderDesc(m_hmd, (ovrEyeType)eyeIdx, m_hmdDesc.DefaultEyeFov[eyeIdx]);
		}

		m_isenabled = true;

		return true;
	}

	void OVR::preReset()
	{
		if (m_isenabled)
		{
			// on window resize this will recreate the mirror texture in ovrPostReset
			m_mirror->destroy(m_hmd);
			BX_DELETE(g_allocator, m_mirror);
			m_mirror = NULL;
			m_isenabled = false;
		}
	}

	void OVR::commitEye(uint8_t _eye)
	{
		if (m_isenabled)
		{
			m_hmdFrameReady = ovr_CommitTextureSwapChain(m_hmd, m_eyeBuffers[_eye]->m_swapTextureChain);
		}
	}

	bool OVR::swap(HMD& _hmd, bool originBottomLeft)
	{
		_hmd.flags = BGFX_HMD_NONE;

		if (NULL != m_hmd)
		{
			_hmd.flags |= BGFX_HMD_DEVICE_RESOLUTION;
			_hmd.deviceWidth  = m_hmdDesc.Resolution.w;
			_hmd.deviceHeight = m_hmdDesc.Resolution.h;
		}

		if (!m_isenabled || !OVR_SUCCESS(m_hmdFrameReady))
		{
			return false;
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

		for (int eye = 0; eye < ovrEye_Count; eye++)
		{
			eyeLayer.ColorTexture[eye] = m_eyeBuffers[eye]->m_swapTextureChain;
			eyeLayer.Viewport[eye].Pos.x  = 0;
			eyeLayer.Viewport[eye].Pos.y  = 0;
			eyeLayer.Viewport[eye].Size.w = m_eyeBuffers[eye]->m_eyeTextureSize.w;
			eyeLayer.Viewport[eye].Size.h = m_eyeBuffers[eye]->m_eyeTextureSize.h;
			eyeLayer.Fov[eye]          = m_hmdDesc.DefaultEyeFov[eye];
			eyeLayer.RenderPose[eye]   = m_pose[eye];
			eyeLayer.SensorSampleTime  = m_sensorSampleTime;
		}

		// append all the layers to global list
		ovrLayerHeader* layerList = &eyeLayer.Header;

		ovr_SubmitFrame(m_hmd, m_frameIndex, NULL, &layerList, 1);

		// perform mirror texture blit right after the entire frame is submitted to HMD
		m_mirror->blit(m_hmd);

		m_hmdToEyeOffset[0] = m_erd[0].HmdToEyeOffset;
		m_hmdToEyeOffset[1] = m_erd[1].HmdToEyeOffset;

		ovr_GetEyePoses(m_hmd, m_frameIndex, ovrTrue, m_hmdToEyeOffset, m_pose, &m_sensorSampleTime);

		getEyePose(_hmd);

		return true;
	}

	void OVR::recenter()
	{
		if (NULL != m_hmd)
		{
			ovr_RecenterTrackingOrigin(m_hmd);
		}
	}

	void OVR::getEyePose(HMD& _hmd)
	{
		if (NULL != m_hmd)
		{
			for (int ii = 0; ii < 2; ++ii)
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
				for (int jj = 0; jj < 4; ++jj)
				{
					for (int kk = 0; kk < 4; ++kk)
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

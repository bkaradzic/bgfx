/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "ovr.h"

#if BGFX_CONFIG_USE_OVR

namespace bgfx
{
#if OVR_VERSION <= OVR_VERSION_050
#	define OVR_EYE_BUFFER 100
#else
#	define OVR_EYE_BUFFER 8
#endif // OVR_VERSION...

	OVR::OVR()
		: m_hmd(NULL)
		, m_isenabled(false)
		, m_debug(false)
	{
	}

	OVR::~OVR()
	{
		BX_CHECK(NULL == m_hmd, "OVR not shutdown properly.");
	}

	void OVR::init()
	{
		bool initialized = !!ovr_Initialize();
		BX_WARN(initialized, "Unable to create OVR device.");
		if (!initialized)
		{
			return;
		}

		m_hmd = ovrHmd_Create(0);
		if (NULL == m_hmd)
		{
			m_hmd = ovrHmd_CreateDebug(ovrHmd_DK2);
			BX_WARN(NULL != m_hmd, "Unable to create OVR device.");
			if (NULL == m_hmd)
			{
				return;
			}
		}

		BX_TRACE("HMD: %s, %s, firmware: %d.%d"
			, m_hmd->ProductName
			, m_hmd->Manufacturer
			, m_hmd->FirmwareMajor
			, m_hmd->FirmwareMinor
			);

		ovrSizei sizeL = ovrHmd_GetFovTextureSize(m_hmd, ovrEye_Left,  m_hmd->DefaultEyeFov[0], 1.0f);
		ovrSizei sizeR = ovrHmd_GetFovTextureSize(m_hmd, ovrEye_Right, m_hmd->DefaultEyeFov[1], 1.0f);
		m_rtSize.w = sizeL.w + sizeR.w + OVR_EYE_BUFFER;
		m_rtSize.h = bx::uint32_max(sizeL.h, sizeR.h);
		m_warning = true;
	}

	void OVR::shutdown()
	{
		BX_CHECK(!m_isenabled, "HMD not disabled.");
		ovrHmd_Destroy(m_hmd);
		m_hmd = NULL;
		ovr_Shutdown();
	}

	void OVR::getViewport(uint8_t _eye, Rect* _viewport)
	{
		_viewport->m_x      = _eye * (m_rtSize.w + OVR_EYE_BUFFER + 1)/2;
		_viewport->m_y      = 0;
		_viewport->m_width  = (m_rtSize.w - OVR_EYE_BUFFER)/2;
		_viewport->m_height = m_rtSize.h;
	}

	bool OVR::postReset(void* _nwh, ovrRenderAPIConfig* _config, bool _debug)
	{
		if (_debug)
		{
			switch (_config->Header.API)
			{
#if BGFX_CONFIG_RENDERER_DIRECT3D11
			case ovrRenderAPI_D3D11:
				{
					ovrD3D11ConfigData* data = (ovrD3D11ConfigData*)_config;
#	if OVR_VERSION > OVR_VERSION_043
					m_rtSize = data->Header.BackBufferSize;
#	else
					m_rtSize = data->Header.RTSize;
#	endif // OVR_VERSION > OVR_VERSION_043
				}
				break;
#endif // BGFX_CONFIG_RENDERER_DIRECT3D11

#if BGFX_CONFIG_RENDERER_OPENGL
			case ovrRenderAPI_OpenGL:
				{
					ovrGLConfigData* data = (ovrGLConfigData*)_config;
#	if OVR_VERSION > OVR_VERSION_043
					m_rtSize = data->Header.BackBufferSize;
#	else
					m_rtSize = data->Header.RTSize;
#	endif // OVR_VERSION > OVR_VERSION_043
				}
				break;
#endif // BGFX_CONFIG_RENDERER_OPENGL

			case ovrRenderAPI_None:
			default:
				BX_CHECK(false, "You should not be here!");
				break;
			}

			m_debug = true;
			return false;
		}

		if (NULL == m_hmd)
		{
			return false;
		}

		m_isenabled = true;

		ovrBool result;
		result = ovrHmd_AttachToWindow(m_hmd, _nwh, NULL, NULL);
		if (!result) { goto ovrError; }

		ovrFovPort eyeFov[2] = { m_hmd->DefaultEyeFov[0], m_hmd->DefaultEyeFov[1] };
		result = ovrHmd_ConfigureRendering(m_hmd
			, _config
			, 0
#if OVR_VERSION < OVR_VERSION_050
			| ovrDistortionCap_Chromatic // permanently enabled >= v5.0
#endif
			| ovrDistortionCap_Vignette
			| ovrDistortionCap_TimeWarp
			| ovrDistortionCap_Overdrive
			| ovrDistortionCap_NoRestore
			| ovrDistortionCap_HqDistortion
			, eyeFov
			, m_erd
			);
		if (!result) { goto ovrError; }

		ovrHmd_SetEnabledCaps(m_hmd
			, 0
			| ovrHmdCap_LowPersistence
			| ovrHmdCap_DynamicPrediction
			);

		result = ovrHmd_ConfigureTracking(m_hmd
			, 0
			| ovrTrackingCap_Orientation
			| ovrTrackingCap_MagYawCorrection
			| ovrTrackingCap_Position
			, 0
			);

		if (!result)
		{
ovrError:
			BX_TRACE("Failed to initialize OVR.");
			m_isenabled = false;
			return false;
		}

		m_warning = true;
		return true;
	}

	void OVR::postReset(const ovrTexture& _texture)
	{
		if (NULL != m_hmd)
		{
			m_texture[0] = _texture;
			m_texture[1] = _texture;

			ovrRecti rect;
			rect.Pos.x  = 0;
			rect.Pos.y  = 0;
			rect.Size.w = (m_rtSize.w - OVR_EYE_BUFFER)/2;
			rect.Size.h = m_rtSize.h;

			m_texture[0].Header.RenderViewport = rect;

			rect.Pos.x += rect.Size.w + OVR_EYE_BUFFER;
			m_texture[1].Header.RenderViewport = rect;

			m_timing = ovrHmd_BeginFrame(m_hmd, 0);
#if OVR_VERSION > OVR_VERSION_042
			m_pose[0] = ovrHmd_GetHmdPosePerEye(m_hmd, ovrEye_Left);
			m_pose[1] = ovrHmd_GetHmdPosePerEye(m_hmd, ovrEye_Right);
#else
			m_pose[0] = ovrHmd_GetEyePose(m_hmd, ovrEye_Left);
			m_pose[1] = ovrHmd_GetEyePose(m_hmd, ovrEye_Right);
#endif // OVR_VERSION > OVR_VERSION_042
		}
	}

	void OVR::preReset()
	{
		if (m_isenabled)
		{
			ovrHmd_EndFrame(m_hmd, m_pose, m_texture);
			ovrHmd_AttachToWindow(m_hmd, NULL, NULL, NULL);
			ovrHmd_ConfigureRendering(m_hmd, NULL, 0, NULL, NULL);
			m_isenabled = false;
		}

		m_debug = false;
	}

	bool OVR::swap(HMD& _hmd)
	{
		_hmd.flags = BGFX_HMD_NONE;

		if (NULL != m_hmd)
		{
			_hmd.flags |= BGFX_HMD_DEVICE_RESOLUTION;
			_hmd.deviceWidth  = m_hmd->Resolution.w;
			_hmd.deviceHeight = m_hmd->Resolution.h;
		}

		if (!m_isenabled)
		{
			return false;
		}

		_hmd.flags |= BGFX_HMD_RENDERING;
		ovrHmd_EndFrame(m_hmd, m_pose, m_texture);

		if (m_warning)
		{
			m_warning = !ovrHmd_DismissHSWDisplay(m_hmd);
		}

		m_timing = ovrHmd_BeginFrame(m_hmd, 0);

#if OVR_VERSION > OVR_VERSION_042
		m_pose[0] = ovrHmd_GetHmdPosePerEye(m_hmd, ovrEye_Left);
		m_pose[1] = ovrHmd_GetHmdPosePerEye(m_hmd, ovrEye_Right);
#else
		m_pose[0] = ovrHmd_GetEyePose(m_hmd, ovrEye_Left);
		m_pose[1] = ovrHmd_GetEyePose(m_hmd, ovrEye_Right);
#endif // OVR_VERSION > OVR_VERSION_042

		getEyePose(_hmd);

		return true;
	}

	void OVR::recenter()
	{
		if (NULL != m_hmd)
		{
			ovrHmd_RecenterPose(m_hmd);
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
#if OVR_VERSION > OVR_VERSION_042
				eye.viewOffset[0] = erd.HmdToEyeViewOffset.x;
				eye.viewOffset[1] = erd.HmdToEyeViewOffset.y;
				eye.viewOffset[2] = erd.HmdToEyeViewOffset.z;
#else
				eye.viewOffset[0] = erd.ViewAdjust.x;
				eye.viewOffset[1] = erd.ViewAdjust.y;
				eye.viewOffset[2] = erd.ViewAdjust.z;
#endif // OVR_VERSION > OVR_VERSION_042
				eye.pixelsPerTanAngle[0] = erd.PixelsPerTanAngleAtCenter.x;
				eye.pixelsPerTanAngle[1] = erd.PixelsPerTanAngleAtCenter.y;
			}
		}
		else
		{
			for (int ii = 0; ii < 2; ++ii)
			{
				_hmd.eye[ii].rotation[0] = 0.0f;
				_hmd.eye[ii].rotation[1] = 0.0f;
				_hmd.eye[ii].rotation[2] = 0.0f;
				_hmd.eye[ii].rotation[3] = 1.0f;
				_hmd.eye[ii].translation[0] = 0.0f;
				_hmd.eye[ii].translation[1] = 0.0f;
				_hmd.eye[ii].translation[2] = 0.0f;
				_hmd.eye[ii].fov[0] = 1.32928634f;
				_hmd.eye[ii].fov[1] = 1.32928634f;
				_hmd.eye[ii].fov[2] = 0 == ii ? 1.05865765f : 1.09236801f;
				_hmd.eye[ii].fov[3] = 0 == ii ? 1.09236801f : 1.05865765f;
				_hmd.eye[ii].viewOffset[0] = 0 == ii ? 0.0355070010f  : -0.0375000015f;
				_hmd.eye[ii].viewOffset[1] = 0.0f;
				_hmd.eye[ii].viewOffset[2] = 0 == ii ? 0.00150949787f : -0.00150949787f;
				_hmd.eye[ii].pixelsPerTanAngle[0] = 1;
				_hmd.eye[ii].pixelsPerTanAngle[1] = 1;
			}
		}

		_hmd.width  = uint16_t(m_rtSize.w);
		_hmd.height = uint16_t(m_rtSize.h);
	}

} // namespace bgfx

#endif // BGFX_CONFIG_USE_OVR

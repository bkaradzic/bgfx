/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "hmd.h"

namespace bgfx
{
	VR::VR()
		: m_impl(NULL)
		, m_framesUntilReconnect(0)
		, m_enabled(false)
	{
	}

	void VR::init(VRImplI* _impl)
	{
		if (NULL == _impl)
		{
			return;
		}

		if (!_impl->init() )
		{
			return;
		}

		m_impl = _impl;
		m_impl->connect(&m_desc);

		if (!m_impl->isConnected() )
		{
			connectFailed();
			return;
		}

		m_hmdSize.m_w = m_desc.m_eyeSize[0].m_w + m_desc.m_eyeSize[1].m_w;
		m_hmdSize.m_h = bx::uint32_max(m_desc.m_eyeSize[0].m_h, m_desc.m_eyeSize[1].m_h);
	}

	void VR::shutdown()
	{
		if (NULL == m_impl)
		{
			return;
		}

		m_impl->destroySwapChain();

		if (m_impl->isConnected() )
		{
			m_impl->disconnect();
		}

		m_impl->shutdown();
		m_impl = NULL;
		m_enabled = false;
	}

	void VR::getViewport(uint8_t _eye, Rect* _viewport) const
	{
		_viewport->m_x      = uint16_t(_eye * (m_desc.m_eyeSize[_eye].m_w + 1) );
		_viewport->m_y      = 0;
		_viewport->m_width  = uint16_t(m_desc.m_eyeSize[_eye].m_w);
		_viewport->m_height = uint16_t(m_desc.m_eyeSize[_eye].m_h);
	}

	void VR::makeRenderTargetActive()
	{
		BX_CHECK(m_enabled, "VR::renderEyeStart called while not enabled - render usage error");

		if (NULL != m_impl)
		{
			m_impl->makeRenderTargetActive(m_desc);
		}
	}

	void VR::recenter()
	{
		if (NULL != m_impl)
		{
			m_impl->recenter();
		}
	}

	void VR::preReset()
	{
		if (NULL != m_impl)
		{
			m_impl->destroyMirror();
		}

		m_enabled = false;
	}

	void VR::postReset(int _msaaSamples, int _mirrorWidth, int _mirrorHeight)
	{
		if (NULL != m_impl
		&&  m_impl->createSwapChain(m_desc, _msaaSamples, _mirrorWidth, _mirrorHeight) )
		{
			m_enabled = true;
		}
	}

	void VR::flip()
	{
		if (NULL == m_impl
		||  !m_enabled)
		{
			return;
		}
		else if (!m_impl->isConnected()
			 &&  !tryReconnect() )
		{
			return;
		}

		if (!m_impl->submitSwapChain(m_desc) )
		{
			m_impl->destroySwapChain();
			m_impl->disconnect();
			return;
		}
	}

	void VR::swap(HMD& _hmd)
	{
		_hmd.flags = BGFX_HMD_NONE;

		if (NULL == m_impl)
		{
			return;
		}

		_hmd.flags = BGFX_HMD_DEVICE_RESOLUTION;
		_hmd.deviceWidth  = m_desc.m_deviceSize.m_w;
		_hmd.deviceHeight = m_desc.m_deviceSize.m_h;
		_hmd.width  = uint16_t(m_hmdSize.m_w);
		_hmd.height = uint16_t(m_hmdSize.m_h);

		if (!m_impl->updateTracking(_hmd) )
		{
			m_impl->destroySwapChain();
			m_impl->disconnect();
		}

		if (!m_impl->isConnected() )
		{
			return;
		}

		for (int eye = 0; eye < 2; ++eye)
		{
			_hmd.eye[eye].fov[0] = m_desc.m_eyeFov[eye].m_up;
			_hmd.eye[eye].fov[1] = m_desc.m_eyeFov[eye].m_down;
			_hmd.eye[eye].fov[2] = m_desc.m_eyeFov[eye].m_left;
			_hmd.eye[eye].fov[3] = m_desc.m_eyeFov[eye].m_right;
		}

		m_impl->updateInput(_hmd);
		if (m_enabled)
		{
			_hmd.flags |= BGFX_HMD_RENDERING;
		}
	}

	bool VR::tryReconnect()
	{
		if (!m_impl)
		{
			return false;
		}

		BX_CHECK(!m_impl->isConnected(), "VR::tryReconnect called when already connected. Usage error");

		--m_framesUntilReconnect;
		if (m_framesUntilReconnect > 0)
		{
			return false;
		}

		m_framesUntilReconnect = 90;
		m_impl->connect(&m_desc);
		if (!m_impl->isConnected() )
		{
			connectFailed();
			return false;
		}

		m_hmdSize.m_w = m_desc.m_eyeSize[0].m_w + m_desc.m_eyeSize[1].m_w;
		m_hmdSize.m_h = bx::uint32_max(m_desc.m_eyeSize[0].m_h, m_desc.m_eyeSize[1].m_h);
		return true;
	}

	void VR::connectFailed()
	{
		// sane defaults
		m_desc.m_deviceSize.m_w = 2160;
		m_desc.m_deviceSize.m_h = 1200;
		m_desc.m_deviceType     = 0;
		m_desc.m_refreshRate    = 90.0f;
		m_desc.m_neckOffset[0]  = 0.0805f;
		m_desc.m_neckOffset[1]  = 0.075f;

		for (int eye = 0; eye < 2; ++eye)
		{
			m_desc.m_eyeFov[eye].m_up   = 1.32928634f;
			m_desc.m_eyeFov[eye].m_down = 1.32928634f;
		}

		m_desc.m_eyeFov[0].m_left  = 1.05865765f;
		m_desc.m_eyeFov[0].m_right = 1.09236801f;
		m_desc.m_eyeFov[1].m_left  = 1.09236801f;
		m_desc.m_eyeFov[1].m_right = 1.05865765f;
	}

} // namesapce bgfx

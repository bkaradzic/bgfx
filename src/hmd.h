/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_HMD_H_HEADER_GUARD
#define BGFX_HMD_H_HEADER_GUARD

#include "bgfx_p.h"

namespace bgfx
{
	struct VRSize
	{
		uint32_t m_w;
		uint32_t m_h;
	};

	struct VRFovTan
	{
		float m_up;
		float m_down;
		float m_left;
		float m_right;
	};

	struct VRDesc
	{
		uint32_t m_deviceType;
		float m_refreshRate;
		VRSize m_deviceSize;
		VRSize m_eyeSize[2];
		VRFovTan m_eyeFov[2];
		float m_neckOffset[2];
	};

	struct BX_NO_VTABLE VRImplI
	{
		virtual ~VRImplI() = 0;

		virtual bool init() = 0;
		virtual void shutdown() = 0;
		virtual void connect(VRDesc* _desc) = 0;
		virtual void disconnect() = 0;
		virtual bool isConnected() const = 0;

		virtual bool updateTracking(HMD& _hmd) = 0;
		virtual void updateInput(HMD& _hmd) = 0;
		virtual void recenter() = 0;

		virtual bool createSwapChain(const VRDesc& _desc, int _msaaSamples, int _mirrorWidth, int _mirrorHeight) = 0;
		virtual void destroySwapChain() = 0;
		virtual void destroyMirror() = 0;
		virtual void makeRenderTargetActive(const VRDesc& _desc) = 0;
		virtual bool submitSwapChain(const VRDesc& _desc) = 0;
	};

	inline VRImplI::~VRImplI()
	{
	}

	class VR
	{
	public:
		VR();

		void init(VRImplI* _impl);
		void shutdown();

		bool isInitialized() const
		{
			return NULL != m_impl;
		}

		bool isEnabled() const
		{
			return m_enabled;
		}

		void getViewport(uint8_t _eye, Rect* _viewport) const;
		void makeRenderTargetActive();
		void recenter();

		void preReset();
		void postReset(int _msaaSamples, int _mirrorWidth, int _mirrorHeight);
		void flip();
		void swap(HMD& _hmd);

	private:
		bool tryReconnect();
		void connectFailed();

		VRImplI* m_impl;
		VRDesc m_desc;
		VRSize m_hmdSize;
		uint32_t m_framesUntilReconnect;
		bool m_enabled;
	};

} // namespace bgfx

#endif // BGFX_HMD_H_HEADER_GUARD

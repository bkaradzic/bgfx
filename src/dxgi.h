/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_DXGI_H_HEADER_GUARD
#define BGFX_DXGI_H_HEADER_GUARD

#include <d3dcommon.h>

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
#	include <dxgi1_6.h>
#endif // BX_PLATFORM_WINDOWS

namespace bgfx
{
	typedef HRESULT (WINAPI* PFN_CREATE_DXGI_FACTORY)(REFIID _riid, void** _factory);
	typedef HRESULT (WINAPI* PFN_GET_DEBUG_INTERFACE)(REFIID _riid, void** _debug);
	typedef HRESULT (WINAPI* PFN_GET_DEBUG_INTERFACE1)(UINT _flags, REFIID _riid, void** _debug);

	struct SwapChainDesc
	{
		uint32_t width;
		uint32_t height;
		DXGI_FORMAT format;
		bool stereo;
		DXGI_SAMPLE_DESC sampleDesc;
		DXGI_USAGE bufferUsage;
		uint32_t bufferCount;
		DXGI_SCALING scaling;
		DXGI_SWAP_EFFECT swapEffect;
		DXGI_ALPHA_MODE alphaMode;
		uint32_t flags;
		void* nwh;
		void* ndt;
		bool windowed;
	};

	struct DxgiSwapChain
	{
		///
		DxgiSwapChain();
	};

	///
	struct Dxgi
	{
		///
		Dxgi();

		///
		bool init(Caps& _caps);

		///
		void shutdown();

		///
		HRESULT createSwapChain(IUnknown* _device, const SwapChainDesc& _desc, IDXGISwapChain** _swapChain);

		///
		void trim();

		///
		void* m_dxgiDll;
		void* m_dxgiDebugDll;

		D3D_DRIVER_TYPE   m_driverType;
		DXGI_ADAPTER_DESC m_adapterDesc;
#if BX_PLATFORM_WINDOWS
		IDXGIFactory* m_factory;
#elif BX_PLATFORM_WINRT
		IDXGIFactory4* m_factory;
#else
		IDXGIFactory2* m_factory;
#endif // BX_PLATFORM_WINDOWS
		IDXGIAdapter* m_adapter;
		IDXGIOutput*  m_output;
	};
	
} // namespace bgfx

#endif // BGFX_DXGI_H_HEADER_GUARD

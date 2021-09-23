/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_DXGI_H_HEADER_GUARD
#define BGFX_DXGI_H_HEADER_GUARD

#if BX_PLATFORM_LINUX || BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
#	include <d3dcommon.h>
#	include <dxgi1_6.h>
#else
#	include <d3d11_x.h>
#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT

namespace bgfx
{
#if BX_PLATFORM_LINUX || BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
	typedef ::IUnknown IUnknown;
#else
	typedef ::IGraphicsUnknown IUnknown;
#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT

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
		uint8_t maxFrameLatency;
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
#if BX_PLATFORM_WINDOWS
		typedef ::IDXGIAdapter3   AdapterI;
		typedef ::IDXGIFactory5   FactoryI;
		typedef ::IDXGISwapChain3 SwapChainI;
		typedef ::IDXGIOutput     OutputI;
#elif BX_PLATFORM_WINRT
		typedef ::IDXGIAdapter    AdapterI;
		typedef ::IDXGIFactory4   FactoryI;
		typedef ::IDXGISwapChain1 SwapChainI;
		typedef ::IDXGIOutput     OutputI;
#else
		typedef ::IDXGIAdapter    AdapterI;
		typedef ::IDXGIFactory2   FactoryI;
		typedef ::IDXGISwapChain1 SwapChainI;
		typedef ::IDXGIOutput     OutputI;
#endif // BX_PLATFORM_WINDOWS

		///
		Dxgi();

		///
		bool init(Caps& _caps);

		///
		void shutdown();

		///
		void update(IUnknown* _device);

		///
		HRESULT createSwapChain(IUnknown* _device, const SwapChainDesc& _scd, SwapChainI** _swapChain);

#if BX_PLATFORM_WINRT
		///
		HRESULT removeSwapChain(const SwapChainDesc& _scd, SwapChainI** _swapChain);
#endif

		///
		void updateHdr10(SwapChainI* _swapChain, const SwapChainDesc& _scd);

		///
		HRESULT resizeBuffers(SwapChainI* _swapChain, const SwapChainDesc& _scd, const uint32_t* _nodeMask = NULL, IUnknown* const* _presentQueue = NULL);

		///
		void trim();

		///
		bool tearingSupported() const;

		///
		void* m_dxgiDll;
		void* m_dxgiDebugDll;

		D3D_DRIVER_TYPE   m_driverType;
		DXGI_ADAPTER_DESC m_adapterDesc;
		FactoryI* m_factory;
		AdapterI* m_adapter;
		OutputI*  m_output;
		bool m_tearingSupported;
	};

} // namespace bgfx

#endif // BGFX_DXGI_H_HEADER_GUARD

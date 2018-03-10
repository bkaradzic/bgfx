/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D11 || BGFX_CONFIG_RENDERER_DIRECT3D12

#include "dxgi.h"
#include "renderer_d3d.h"

#if !BX_PLATFORM_WINDOWS
#	include <inspectable.h>
#	if BX_PLATFORM_WINRT
#		include <windows.ui.xaml.media.dxinterop.h>
#	endif // BX_PLATFORM_WINRT
#endif // !BX_PLATFORM_WINDOWS

namespace bgfx
{
#if BX_PLATFORM_WINDOWS
	static PFN_CREATE_DXGI_FACTORY  CreateDXGIFactory;
	static PFN_GET_DEBUG_INTERFACE  DXGIGetDebugInterface;
	static PFN_GET_DEBUG_INTERFACE1 DXGIGetDebugInterface1;
#endif // BX_PLATFORM_WINDOWS

	static const GUID IID_IDXGIFactory    = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
	static const GUID IID_IDXGIFactory2   = { 0x50c83a1c, 0xe072, 0x4c48, { 0x87, 0xb0, 0x36, 0x30, 0xfa, 0x36, 0xa6, 0xd0 } };
	static const GUID IID_IDXGIDevice0    = { 0x54ec77fa, 0x1377, 0x44e6, { 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c } };
	static const GUID IID_IDXGIDevice1    = { 0x77db970f, 0x6276, 0x48ba, { 0xba, 0x28, 0x07, 0x01, 0x43, 0xb4, 0x39, 0x2c } };
	static const GUID IID_IDXGIDevice2    = { 0x05008617, 0xfbfd, 0x4051, { 0xa7, 0x90, 0x14, 0x48, 0x84, 0xb4, 0xf6, 0xa9 } };
	static const GUID IID_IDXGIDevice3    = { 0x6007896c, 0x3244, 0x4afd, { 0xbf, 0x18, 0xa6, 0xd3, 0xbe, 0xda, 0x50, 0x23 } };
	static const GUID IID_IDXGIAdapter    = { 0x2411e7e1, 0x12ac, 0x4ccf, { 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0xc0 } };
	static const GUID IID_IDXGISwapChain3 = { 0x94d99bdb, 0xf1f8, 0x4ab0, { 0xb2, 0x36, 0x7d, 0xa0, 0x17, 0x0e, 0xda, 0xb1 } };
	static const GUID IID_IDXGISwapChain4 = { 0x3d585d5a, 0xbd4a, 0x489e, { 0xb1, 0xf4, 0x3d, 0xbc, 0xb6, 0x45, 0x2f, 0xfb } };

	static const DXGI_COLOR_SPACE_TYPE s_colorSpace[] =
	{
		DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709,    // gamma 2.2,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709,    // gamma 1.0,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020, // gamma 2084, BT.2020
	};

	static const GUID s_dxgiDeviceIIDs[] =
	{
		IID_IDXGIDevice3,
		IID_IDXGIDevice2,
		IID_IDXGIDevice1,
		IID_IDXGIDevice0,
	};

	static const GUID s_dxgiSwapChainIIDs[] =
	{
		IID_IDXGISwapChain4,
		IID_IDXGISwapChain3,
	};

	DxgiSwapChain::DxgiSwapChain()
	{
	}

	Dxgi::Dxgi()
		: m_dxgiDll(NULL)
		, m_dxgiDebugDll(NULL)
		, m_driverType(D3D_DRIVER_TYPE_NULL)
		, m_factory(NULL)
		, m_adapter(NULL)
		, m_output(NULL)
	{
	}

	bool Dxgi::init(Caps& _caps)
	{
#if BX_PLATFORM_WINDOWS
		m_dxgiDll = bx::dlopen("dxgi.dll");
		if (NULL == m_dxgiDll)
		{
			BX_TRACE("Init error: Failed to load dxgi.dll.");
			return false;
		}

		m_dxgiDebugDll = bx::dlopen("dxgidebug.dll");
		if (NULL != m_dxgiDebugDll)
		{
			DXGIGetDebugInterface  = (PFN_GET_DEBUG_INTERFACE )bx::dlsym(m_dxgiDebugDll, "DXGIGetDebugInterface");
			DXGIGetDebugInterface1 = (PFN_GET_DEBUG_INTERFACE1)bx::dlsym(m_dxgiDebugDll, "DXGIGetDebugInterface1");
			if (NULL == DXGIGetDebugInterface
			&&  NULL == DXGIGetDebugInterface1)
			{
				bx::dlclose(m_dxgiDebugDll);
				m_dxgiDebugDll = NULL;
			}
		}

		CreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY)bx::dlsym(m_dxgiDll, "CreateDXGIFactory1");

		if (NULL == CreateDXGIFactory)
		{
			CreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY)bx::dlsym(m_dxgiDll, "CreateDXGIFactory");
		}

		if (NULL == CreateDXGIFactory)
		{
			BX_TRACE("Init error: Function CreateDXGIFactory not found.");
			return false;
		}
#endif // BX_PLATFORM_WINDOWS

		HRESULT hr = S_OK;
#if BX_PLATFORM_WINRT
		// WinRT requires the IDXGIFactory2 interface, which isn't supported on older platforms
		hr = CreateDXGIFactory1(IID_IDXGIFactory2, (void**)&m_factory);
#elif BX_PLATFORM_WINDOWS
		hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&m_factory);
#endif // BX_PLATFORM_*

		if (FAILED(hr) )
		{
			BX_TRACE("Init error: Unable to create DXGI factory.");
			return false;
		}

		m_driverType = BGFX_PCI_ID_SOFTWARE_RASTERIZER == _caps.vendorId
			? D3D_DRIVER_TYPE_WARP
			: D3D_DRIVER_TYPE_HARDWARE
			;

		IDXGIAdapter* adapter;
		for (uint32_t ii = 0
			; DXGI_ERROR_NOT_FOUND != m_factory->EnumAdapters(ii, &adapter) && ii < BX_COUNTOF(_caps.gpu)
			; ++ii
			)
		{
			DXGI_ADAPTER_DESC desc;
			hr = adapter->GetDesc(&desc);
			if (SUCCEEDED(hr) )
			{
				BX_TRACE("Adapter #%d", ii);

				char description[BX_COUNTOF(desc.Description)];
				wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
				BX_TRACE("\tDescription: %s", description);
				BX_TRACE("\tVendorId: 0x%08x, DeviceId: 0x%08x, SubSysId: 0x%08x, Revision: 0x%08x"
					, desc.VendorId
					, desc.DeviceId
					, desc.SubSysId
					, desc.Revision
					);
				BX_TRACE("\tMemory: %" PRIi64 " (video), %" PRIi64 " (system), %" PRIi64 " (shared)"
					, desc.DedicatedVideoMemory
					, desc.DedicatedSystemMemory
					, desc.SharedSystemMemory
					);

				_caps.gpu[ii].vendorId = (uint16_t)desc.VendorId;
				_caps.gpu[ii].deviceId = (uint16_t)desc.DeviceId;
				++_caps.numGPUs;

				if (NULL == m_adapter)
				{
					if ( (BGFX_PCI_ID_NONE != _caps.vendorId ||             0 != _caps.deviceId)
					&&   (BGFX_PCI_ID_NONE == _caps.vendorId || desc.VendorId == _caps.vendorId)
					&&   (               0 == _caps.deviceId || desc.DeviceId == _caps.deviceId) )
					{
						m_adapter = adapter;
						m_adapter->AddRef();
						m_driverType = D3D_DRIVER_TYPE_UNKNOWN;
					}

					if (BX_ENABLED(BGFX_CONFIG_DEBUG_PERFHUD)
					&&  0 != bx::strFind(description, "PerfHUD") )
					{
						m_adapter = adapter;
						m_driverType = D3D_DRIVER_TYPE_REFERENCE;
					}
				}
			}

			IDXGIOutput* output;
			for (uint32_t jj = 0
				; DXGI_ERROR_NOT_FOUND != adapter->EnumOutputs(jj, &output)
				; ++jj
				)
			{
				DXGI_OUTPUT_DESC outputDesc;
				hr = output->GetDesc(&outputDesc);
				if (SUCCEEDED(hr))
				{
					BX_TRACE("\tOutput #%d", jj);

					char deviceName[BX_COUNTOF(outputDesc.DeviceName)];
					wcstombs(deviceName, outputDesc.DeviceName, BX_COUNTOF(outputDesc.DeviceName));
					BX_TRACE("\t\tDeviceName: %s", deviceName);
					BX_TRACE("\t\tDesktopCoordinates: %d, %d, %d, %d"
						, outputDesc.DesktopCoordinates.left
						, outputDesc.DesktopCoordinates.top
						, outputDesc.DesktopCoordinates.right
						, outputDesc.DesktopCoordinates.bottom
						);
					BX_TRACE("\t\tAttachedToDesktop: %d", outputDesc.AttachedToDesktop);
					BX_TRACE("\t\tRotation: %d", outputDesc.Rotation);

					DX_RELEASE(output, 0);
				}
			}

			DX_RELEASE(adapter, adapter == m_adapter ? 1 : 0);
		}

		if (NULL == m_adapter)
		{
			hr = m_factory->EnumAdapters(0, &m_adapter);
			BX_WARN(SUCCEEDED(hr), "EnumAdapters failed 0x%08x.", hr);
			m_driverType = D3D_DRIVER_TYPE_UNKNOWN;
		}

		bx::memSet(&m_adapterDesc, 0, sizeof(m_adapterDesc) );
		hr = m_adapter->GetDesc(&m_adapterDesc);
		BX_WARN(SUCCEEDED(hr), "Adapter GetDesc failed 0x%08x.", hr);

		m_adapter->EnumOutputs(0, &m_output);

		_caps.vendorId = 0 == m_adapterDesc.VendorId
			? BGFX_PCI_ID_SOFTWARE_RASTERIZER
			: (uint16_t)m_adapterDesc.VendorId
			;
		_caps.deviceId = (uint16_t)m_adapterDesc.DeviceId;

		{
			IDXGIDevice* device = NULL;
			hr = E_FAIL;
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_dxgiDeviceIIDs) && FAILED(hr); ++ii)
			{
				hr = m_factory->QueryInterface(s_dxgiDeviceIIDs[ii], (void**)&device);
				BX_TRACE("DXGI device 11.%d, hr %x", BX_COUNTOF(s_dxgiDeviceIIDs) - 1 - ii, hr);

				if (SUCCEEDED(hr))
				{
#if BX_COMPILER_MSVC
					BX_PRAGMA_DIAGNOSTIC_PUSH();
					BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4530) // warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
						try
					{
						// QueryInterface above can succeed, but getting adapter call might crash on Win7.
						hr = device->GetAdapter(&adapter);
					}
					catch (...)
					{
						BX_TRACE("Failed to get adapter for IID_IDXGIDevice%d.", BX_COUNTOF(s_dxgiDeviceIIDs) - 1 - ii);
						DX_RELEASE(device, 0);
						hr = E_FAIL;
					}
					BX_PRAGMA_DIAGNOSTIC_POP();
#else
					hr = device->GetAdapter(&adapter);
#endif // BX_COMPILER_MSVC
				}
			}
		}

		return true;
	}

	void Dxgi::shutdown()
	{
		DX_RELEASE(m_output,  0);
		DX_RELEASE(m_adapter, 0);
		DX_RELEASE(m_factory, 0);

		bx::dlclose(m_dxgiDebugDll);
		m_dxgiDebugDll = NULL;

		bx::dlclose(m_dxgiDll);
		m_dxgiDll = NULL;
	}

	HRESULT Dxgi::createSwapChain(IUnknown* _device, const SwapChainDesc& _scd, IDXGISwapChain** _swapChain)
	{
		HRESULT hr = S_OK;

#if BX_PLATFORM_WINDOWS
		DXGI_SWAP_CHAIN_DESC scd;
		scd.BufferDesc.Width  = _scd.width;
		scd.BufferDesc.Height = _scd.height;
		scd.BufferDesc.RefreshRate.Numerator   = 1;
		scd.BufferDesc.RefreshRate.Denominator = 60;
		scd.BufferDesc.Format = _scd.format;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.SampleDesc   = _scd.sampleDesc;
		scd.BufferUsage  = _scd.bufferUsage;
		scd.BufferCount  = _scd.bufferCount;
		scd.SwapEffect   = _scd.swapEffect;
		scd.Flags        = _scd.flags;
		scd.OutputWindow = (HWND)_scd.nwh;
		scd.Windowed     = _scd.windowed;

		hr = m_factory->CreateSwapChain(_device, &scd, _swapChain);
#else
		DXGI_SWAP_CHAIN_DESC1 scd;
		scd.Width  = _scd.width;
		scd.Height = _scd.height;
		scd.Format = _scd.format;
		scd.Stereo = _scd.stereo;
		scd.SampleDesc  = _scd.sampleDesc;
		scd.BufferUsage = _scd.bufferUsage;
		scd.BufferCount = _scd.bufferCount;
		scd.Scaling    = _scd.scaling;
		scd.SwapEffect = _scd.swapEffect;
		scd.AlphaMode  = _scd.alphaMode;
		scd.Flags      = _scd.flags;

		if (NULL == _scd.ndt)
		{
			hr = m_factory->CreateSwapChainForCoreWindow(_device
					, (::IUnknown*)_scd.nwh
					, &scd
					, NULL
					, reinterpret_cast<IDXGISwapChain1**>(_swapChain)
					);
		}
		else if (reinterpret_cast<void*>(1) == _scd.ndt)
		{
			return E_FAIL;
		}
		else
		{
			hr = m_factory->CreateSwapChainForComposition(_device
					, &scd
					, NULL
					, reinterpret_cast<IDXGISwapChain1**>(_swapChain)
					);
			if (FAILED(hr) )
			{
				return hr;
			}

#	if BX_PLATFORM_WINRT
			IInspectable *nativeWindow = reinterpret_cast<IInspectable *>(_scd.nwh);
			ISwapChainBackgroundPanelNative* panel = NULL;
			hr = nativeWindow->QueryInterface(
				  __uuidof(ISwapChainBackgroundPanelNative)
				, (void **)&panel
				);
			if (FAILED(hr) )
			{
				return hr;
			}

			if (NULL != panel)
			{
				hr = panel->SetSwapChain(*_swapChain);
				if (FAILED(hr) )
				{
					return hr;
				}

				panel->Release();
			}
#	endif // BX_PLATFORM_WINRT
		}
#endif // BX_PLATFORM_WINDOWS

#if BX_PLATFORM_WINDOWS
		if (SUCCEEDED(hr) )
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_dxgiSwapChainIIDs); ++ii)
			{
				IDXGISwapChain1* swapChain;
				hr = (*_swapChain)->QueryInterface(s_dxgiSwapChainIIDs[ii], (void**)&swapChain);
				BX_TRACE("DXGI swap chain %d, hr %x", 4-ii, hr);

				if (SUCCEEDED(hr) )
				{
					DX_RELEASE(*_swapChain, 1);
					*_swapChain = swapChain;

					BX_TRACE("Color space support:");
					for (uint32_t jj = 0; jj < BX_COUNTOF(s_colorSpace); ++jj)
					{
						uint32_t colorSpaceSupport;
						reinterpret_cast<IDXGISwapChain3*>(*_swapChain)->CheckColorSpaceSupport(s_colorSpace[jj], &colorSpaceSupport);
						BX_TRACE("\t%2d, 0x%08x, %s"
							, s_colorSpace[jj]
							, colorSpaceSupport
							, 0 != (colorSpaceSupport & DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT)
							? "supported"
							: "-"
							);
					}

					break;
				}
			}
		}
#endif // BX_PLATFORM_WINDOWS

		return hr;
	}

	void Dxgi::trim()
	{
#if BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
		IDXGIDevice3* device;
		HRESULT hr = m_factory->QueryInterface(IID_IDXGIDevice3, (void**)&device);
		if (SUCCEEDED(hr) )
		{
			device->Trim();
			DX_RELEASE(device, 1);
		}
#else
		BX_UNUSED(_device);
#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
	}

} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11 || BGFX_CONFIG_RENDERER_DIRECT3D12

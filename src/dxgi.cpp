/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
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
	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_GCC("-Wunused-variable");
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunused-const-variable");
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunneeded-internal-declaration");

#if BX_PLATFORM_WINDOWS
	static PFN_CREATE_DXGI_FACTORY  CreateDXGIFactory;
	static PFN_GET_DEBUG_INTERFACE  DXGIGetDebugInterface;
	static PFN_GET_DEBUG_INTERFACE1 DXGIGetDebugInterface1;
#endif // BX_PLATFORM_WINDOWS

	static const GUID IID_IDXGIFactory    = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
	static const GUID IID_IDXGIFactory2   = { 0x50c83a1c, 0xe072, 0x4c48, { 0x87, 0xb0, 0x36, 0x30, 0xfa, 0x36, 0xa6, 0xd0 } };
	static const GUID IID_IDXGIFactory3   = { 0x25483823, 0xcd46, 0x4c7d, { 0x86, 0xca, 0x47, 0xaa, 0x95, 0xb8, 0x37, 0xbd } };
	static const GUID IID_IDXGIFactory4   = { 0x1bc6ea02, 0xef36, 0x464f, { 0xbf, 0x0c, 0x21, 0xca, 0x39, 0xe5, 0x16, 0x8a } };
	static const GUID IID_IDXGIFactory5   = { 0x7632e1f5, 0xee65, 0x4dca, { 0x87, 0xfd, 0x84, 0xcd, 0x75, 0xf8, 0x83, 0x8d } };
	static const GUID IID_IDXGIDevice0    = { 0x54ec77fa, 0x1377, 0x44e6, { 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c } };
	static const GUID IID_IDXGIDevice1    = { 0x77db970f, 0x6276, 0x48ba, { 0xba, 0x28, 0x07, 0x01, 0x43, 0xb4, 0x39, 0x2c } };
	static const GUID IID_IDXGIDevice2    = { 0x05008617, 0xfbfd, 0x4051, { 0xa7, 0x90, 0x14, 0x48, 0x84, 0xb4, 0xf6, 0xa9 } };
	static const GUID IID_IDXGIDevice3    = { 0x6007896c, 0x3244, 0x4afd, { 0xbf, 0x18, 0xa6, 0xd3, 0xbe, 0xda, 0x50, 0x23 } };
	static const GUID IID_IDXGIAdapter    = { 0x2411e7e1, 0x12ac, 0x4ccf, { 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0xc0 } };
	static const GUID IID_IDXGIAdapter2   = { 0x0aa1ae0a, 0xfa0e, 0x4b84, { 0x86, 0x44, 0xe0, 0x5f, 0xf8, 0xe5, 0xac, 0xb5 } };
	static const GUID IID_IDXGIAdapter3   = { 0x645967a4, 0x1392, 0x4310, { 0xa7, 0x98, 0x80, 0x53, 0xce, 0x3e, 0x93, 0xfd } };
	static const GUID IID_IDXGIAdapter4   = { 0x3c8d99d1, 0x4fbf, 0x4181, { 0xa8, 0x2c, 0xaf, 0x66, 0xbf, 0x7b, 0xd2, 0x4e } };
	static const GUID IID_IDXGISwapChain3 = { 0x94d99bdb, 0xf1f8, 0x4ab0, { 0xb2, 0x36, 0x7d, 0xa0, 0x17, 0x0e, 0xda, 0xb1 } };
	static const GUID IID_IDXGISwapChain4 = { 0x3d585d5a, 0xbd4a, 0x489e, { 0xb1, 0xf4, 0x3d, 0xbc, 0xb6, 0x45, 0x2f, 0xfb } };
	static const GUID IID_IDXGIOutput6    = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };

	BX_PRAGMA_DIAGNOSTIC_POP();

	static const DXGI_COLOR_SPACE_TYPE s_colorSpace[] =
	{
		DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709,    // gamma 2.2,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709,    // gamma 1.0,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020, // gamma 2084, BT.2020
	};

	static const char* s_colorSpaceStr[] =
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/dn903661(v=vs.85).aspx
		"RGB,    0-255, 2.2,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
		"RGB,    0-255, 1.0,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709
		"RGB,   16-235, 2.2,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709
		"RGB,   16-235, 2.2,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020
		"Reserved",                                    // DXGI_COLOR_SPACE_RESERVED
		"YCbCr,  0-255, 2.2,  Image, BT.709,  BT.601", // DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601
		"YCbCr, 16-235, 2.2,  Video, BT.601,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601
		"YCbCr,  0-255, 2.2,  Video, BT.601,  n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601
		"YCbCr, 16-235, 2.2,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709
		"YCbCr,  0-255, 2.2,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709
		"YCbCr, 16-235, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020
		"YCbCr,  0-255, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020
		"RGB,    0-255, 2084, Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
		"YCbCr, 16-235, 2084, Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020
		"RGB,    0-255, 2084, Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020
		"YCbCr, 16-235, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020
		"YCbCr, 16-235, 2084, Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020
#if BX_PLATFORM_WINDOWS
		"RGB,    0-255, 2.2,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020
		"YCbCr, 16-235, HLG,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020
		"YCbCr,  0-255, HLG,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020
//		"RGB,   16-235, 2.4,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709
//		"RGB,   16-235, 2.4,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020
//		"YCbCr, 16-235, 2.4,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709
//		"YCbCr, 16-235, 2.4,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020
//		"YCbCr, 16-235, 2.4,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020
#endif // BX_PLATFORM_WINDOWS
		"Custom",
	};
	static const DXGI_COLOR_SPACE_TYPE kDxgiLastColorSpace =
#if BX_PLATFORM_WINDOWS
		DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020
#else
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020
#endif // BX_PLATFORM_WINDOWS
		;
	BX_STATIC_ASSERT(BX_COUNTOF(s_colorSpaceStr) == kDxgiLastColorSpace+2, "Colorspace string table mismatch with DXGI_COLOR_SPACE_*.");

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

		if (NULL != m_factory)
		{
			AdapterI* adapter;
			for (uint32_t ii = 0
				; DXGI_ERROR_NOT_FOUND != m_factory->EnumAdapters(ii, reinterpret_cast<IDXGIAdapter**>(&adapter) ) && ii < BX_COUNTOF(_caps.gpu)
				; ++ii
				)
			{
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
							&&  !bx::strFind(description, "PerfHUD").isEmpty() )
							{
								m_adapter = adapter;
								m_driverType = D3D_DRIVER_TYPE_REFERENCE;
							}
						}
					}
				}

				bool hdr10 = false;

				IDXGIOutput* output;
				for (uint32_t jj = 0
					; SUCCEEDED(adapter->EnumOutputs(jj, &output) )
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
						BX_TRACE("\t\t           DeviceName: %s", deviceName);
						BX_TRACE("\t\t   DesktopCoordinates: %d, %d, %d, %d"
							, outputDesc.DesktopCoordinates.left
							, outputDesc.DesktopCoordinates.top
							, outputDesc.DesktopCoordinates.right
							, outputDesc.DesktopCoordinates.bottom
							);
						BX_TRACE("\t\t    AttachedToDesktop: %d", outputDesc.AttachedToDesktop);
						BX_TRACE("\t\t             Rotation: %d", outputDesc.Rotation);

#if BX_PLATFORM_WINDOWS
						IDXGIOutput6* output6;
						hr = output->QueryInterface(IID_IDXGIOutput6, (void**)&output6);
						if (SUCCEEDED(hr) )
						{
							DXGI_OUTPUT_DESC1 desc;
							hr = output6->GetDesc1(&desc);
							if (SUCCEEDED(hr) )
							{
								BX_TRACE("\t\t         BitsPerColor: %d", desc.BitsPerColor);
								BX_TRACE("\t\t          Color space: %s (colorspace, range, gamma, sitting, primaries, transform)"
									, s_colorSpaceStr[bx::min<uint32_t>(desc.ColorSpace, kDxgiLastColorSpace+1)]
									);
								BX_TRACE("\t\t           RedPrimary: %f, %f", desc.RedPrimary[0],   desc.RedPrimary[1]);
								BX_TRACE("\t\t         GreenPrimary: %f, %f", desc.GreenPrimary[0], desc.GreenPrimary[1]);
								BX_TRACE("\t\t          BluePrimary: %f, %f", desc.BluePrimary[0],  desc.BluePrimary[1]);
								BX_TRACE("\t\t           WhitePoint: %f, %f", desc.WhitePoint[0],   desc.WhitePoint[1]);
								BX_TRACE("\t\t         MinLuminance: %f", desc.MinLuminance);
								BX_TRACE("\t\t         MaxLuminance: %f", desc.MaxLuminance);
								BX_TRACE("\t\tMaxFullFrameLuminance: %f", desc.MaxFullFrameLuminance);
								BX_TRACE("\t\t          HDR support: %s", DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace ? "true" : "false");

								hdr10 |= DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace;
							}

							// BK - warn only because RenderDoc might be present.
							DX_RELEASE_W(output6, 1);
						}
#endif // BX_PLATFORM_WINDOWS

						DX_RELEASE(output, 0);
					}
				}

				_caps.supported |= hdr10 ? BGFX_CAPS_HDR10 : 0;

				DX_RELEASE(adapter, adapter == m_adapter ? 1 : 0);
			}

			if (NULL == m_adapter)
			{
				hr = m_factory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_adapter) );
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

	void Dxgi::update(IUnknown* _device)
	{
		IDXGIDevice* dxgiDevice = NULL;
		HRESULT hr = E_FAIL;
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_dxgiDeviceIIDs) && FAILED(hr); ++ii)
		{
			hr = _device->QueryInterface(s_dxgiDeviceIIDs[ii], (void**)&dxgiDevice);
			BX_TRACE("DXGI device 11.%d, hr %x", BX_COUNTOF(s_dxgiDeviceIIDs) - 1 - ii, hr);
		}

		if (NULL == m_factory)
		{
			DX_CHECK(dxgiDevice->GetAdapter(reinterpret_cast<IDXGIAdapter**>(&m_adapter) ) );

			bx::memSet(&m_adapterDesc, 0, sizeof(m_adapterDesc) );
			hr = m_adapter->GetDesc(&m_adapterDesc);
			BX_WARN(SUCCEEDED(hr), "Adapter GetDesc failed 0x%08x.", hr);

			DX_CHECK(m_adapter->GetParent(IID_IDXGIFactory2, (void**)&m_factory) );
		}

		DX_RELEASE_I(dxgiDevice);
	}

	static const GUID IID_ID3D12CommandQueue = { 0x0ec870a6, 0x5d7e, 0x4c22, { 0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed } };

	HRESULT Dxgi::createSwapChain(IUnknown* _device, const SwapChainDesc& _scd, SwapChainI** _swapChain)
	{
		HRESULT hr = S_OK;

		bool allowTearing = false;

#if BX_PLATFORM_WINDOWS
		if (windowsVersionIs(Condition::GreaterEqual, 0x0604) )
		{
			// BK - CheckFeatureSupport with DXGI_FEATURE_PRESENT_ALLOW_TEARING
			//      will crash on pre Windows 8. Issue #1356.
			hr = m_factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing) );
			BX_TRACE("Allow tearing is %ssupported.", allowTearing ? "" : "not ");
		}

		DXGI_SWAP_CHAIN_DESC scd;
		scd.BufferDesc.Width  = _scd.width;
		scd.BufferDesc.Height = _scd.height;
		scd.BufferDesc.RefreshRate.Numerator   = 1;
		scd.BufferDesc.RefreshRate.Denominator = 60;
		scd.BufferDesc.Format = _scd.format;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.SampleDesc.Count   = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage  = _scd.bufferUsage;
		scd.BufferCount  = _scd.bufferCount;
		scd.OutputWindow = (HWND)_scd.nwh;
		scd.Windowed     = _scd.windowed;
		scd.SwapEffect   = _scd.swapEffect;
		scd.Flags        = 0
			| _scd.flags
			| (allowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0)
			;

		hr = m_factory->CreateSwapChain(
			  _device
			, &scd
			, reinterpret_cast<IDXGISwapChain**>(_swapChain)
			);

		if (SUCCEEDED(hr) )
		{
			IDXGIDevice1* dxgiDevice1;
			_device->QueryInterface(IID_IDXGIDevice1, (void**)&dxgiDevice1);
			if (NULL != dxgiDevice1)
			{
				dxgiDevice1->SetMaximumFrameLatency(_scd.maxFrameLatency);
				DX_RELEASE_I(dxgiDevice1);
			}
		}
#else
		DXGI_SWAP_CHAIN_DESC1 scd;
		scd.Width  = _scd.width;
		scd.Height = _scd.height;
		scd.Format = _scd.format;
		scd.Stereo = _scd.stereo;
		scd.SampleDesc.Count   = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = _scd.bufferUsage;
		scd.BufferCount = _scd.bufferCount;
		scd.Scaling     = _scd.scaling;
		scd.SwapEffect  = _scd.swapEffect;
		scd.AlphaMode   = _scd.alphaMode;
		scd.Flags       = _scd.flags;

		if (NULL == _scd.ndt)
		{
			hr = m_factory->CreateSwapChainForCoreWindow(
				  _device
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
			hr = m_factory->CreateSwapChainForComposition(
				  _device
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

		if (FAILED(hr) )
		{
			BX_TRACE("Failed to create swap chain.");
			return hr;
		}

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
					*_swapChain = reinterpret_cast<SwapChainI*>(swapChain);

					BX_TRACE("Color space support:");
					for (uint32_t jj = 0; jj < BX_COUNTOF(s_colorSpace); ++jj)
					{
						uint32_t colorSpaceSupport;
						reinterpret_cast<IDXGISwapChain3*>(*_swapChain)->CheckColorSpaceSupport(s_colorSpace[jj], &colorSpaceSupport);
						BX_TRACE("\t%2d: \"%-20s\", 0x%08x, %s"
							, s_colorSpace[jj]
							, s_colorSpaceStr[s_colorSpace[jj]]
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

		updateHdr10(*_swapChain, _scd);

		return S_OK;
	}

	void Dxgi::updateHdr10(SwapChainI* _swapChain, const SwapChainDesc& _scd)
	{
#if BX_PLATFORM_WINDOWS
		::IDXGISwapChain4* swapChain4;
		HRESULT hr = _swapChain->QueryInterface(IID_IDXGISwapChain4, (void**)&swapChain4);

		if (SUCCEEDED(hr) )
		{
			const DXGI_COLOR_SPACE_TYPE colorSpace =
				  _scd.format == DXGI_FORMAT_R10G10B10A2_UNORM  ? DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
				: _scd.format == DXGI_FORMAT_R16G16B16A16_FLOAT ? DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709
				:                                                 DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
				;

			hr = swapChain4->SetColorSpace1(colorSpace);

			if (SUCCEEDED(hr) )
			{
				DXGI_OUTPUT_DESC1 desc;

				IDXGIOutput* output;
				hr = _swapChain->GetContainingOutput(&output);
				if (SUCCEEDED(hr) )
				{
					IDXGIOutput6* output6;
					hr = output->QueryInterface(IID_IDXGIOutput6, (void**)&output6);
					if (SUCCEEDED(hr) )
					{
						hr = output6->GetDesc1(&desc);
						if (SUCCEEDED(hr) )
						{
							BX_TRACE("Display specs:")
							BX_TRACE("\t         BitsPerColor: %d", desc.BitsPerColor);
							BX_TRACE("\t          Color space: %s (colorspace, range, gamma, sitting, primaries, transform)"
								, s_colorSpaceStr[bx::min<uint32_t>(desc.ColorSpace, kDxgiLastColorSpace+1)]
								);
							BX_TRACE("\t           RedPrimary: %f, %f", desc.RedPrimary[0],   desc.RedPrimary[1]);
							BX_TRACE("\t         GreenPrimary: %f, %f", desc.GreenPrimary[0], desc.GreenPrimary[1]);
							BX_TRACE("\t          BluePrimary: %f, %f", desc.BluePrimary[0],  desc.BluePrimary[1]);
							BX_TRACE("\t           WhitePoint: %f, %f", desc.WhitePoint[0],   desc.WhitePoint[1]);
							BX_TRACE("\t         MinLuminance: %f", desc.MinLuminance);
							BX_TRACE("\t         MaxLuminance: %f", desc.MaxLuminance);
							BX_TRACE("\tMaxFullFrameLuminance: %f", desc.MaxFullFrameLuminance);
						}

						DX_RELEASE(output6, 1);
					}

					DX_RELEASE(output, 0);
				}

				DXGI_HDR_METADATA_HDR10 hdr10;
				hdr10.RedPrimary[0]   = uint16_t(desc.RedPrimary[0]   * 50000.0f);
				hdr10.RedPrimary[1]   = uint16_t(desc.RedPrimary[1]   * 50000.0f);
				hdr10.GreenPrimary[0] = uint16_t(desc.GreenPrimary[0] * 50000.0f);
				hdr10.GreenPrimary[1] = uint16_t(desc.GreenPrimary[1] * 50000.0f);
				hdr10.BluePrimary[0]  = uint16_t(desc.BluePrimary[0]  * 50000.0f);
				hdr10.BluePrimary[1]  = uint16_t(desc.BluePrimary[1]  * 50000.0f);
				hdr10.WhitePoint[0]   = uint16_t(desc.WhitePoint[0]   * 50000.0f);
				hdr10.WhitePoint[1]   = uint16_t(desc.WhitePoint[1]   * 50000.0f);
				hdr10.MaxMasteringLuminance     = uint32_t(desc.MaxLuminance * 10000.0f);
				hdr10.MinMasteringLuminance     = uint32_t(desc.MinLuminance * 10000.0f);
				hdr10.MaxContentLightLevel      = uint16_t(desc.MaxFullFrameLuminance);
				hdr10.MaxFrameAverageLightLevel = uint16_t(desc.MaxFullFrameLuminance);
				hr = swapChain4->SetHDRMetaData(DXGI_HDR_METADATA_TYPE_HDR10, sizeof(DXGI_HDR_METADATA_HDR10), &hdr10);
			}

			DX_RELEASE(swapChain4, 1);
		}
#else
		BX_UNUSED(_swapChain, _scd);
#endif // BX_PLATFORM_WINDOWS
	}

	HRESULT Dxgi::resizeBuffers(SwapChainI* _swapChain, const SwapChainDesc& _scd, const uint32_t* _nodeMask, IUnknown* const* _presentQueue)
	{
		HRESULT hr;

#if BX_PLATFORM_WINDOWS
		if (NULL != _nodeMask
		&&  NULL != _presentQueue)
		{
			hr = _swapChain->ResizeBuffers1(
				  _scd.bufferCount
				, _scd.width
				, _scd.height
				, _scd.format
				, _scd.flags
				, _nodeMask
				, _presentQueue
				);
		}
		else
#endif // BX_PLATFORM_WINDOWS
		{
			BX_UNUSED(_nodeMask, _presentQueue);

			hr = _swapChain->ResizeBuffers(
				  _scd.bufferCount
				, _scd.width
				, _scd.height
				, _scd.format
				, _scd.flags
				);
		}

		if (SUCCEEDED(hr) )
		{
			updateHdr10(_swapChain, _scd);
		}

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
#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT
	}

} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11 || BGFX_CONFIG_RENDERER_DIRECT3D12

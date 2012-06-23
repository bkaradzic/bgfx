/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D
#	include "renderer_d3d9.h"

namespace bgfx
{
	static const D3DPRIMITIVETYPE s_primType[] =
	{
		D3DPT_TRIANGLELIST,
		D3DPT_LINELIST,
		D3DPT_POINTLIST,
	};

	static const uint32_t s_primNumVerts[] =
	{
		3,
		2,
		1,
	};

	static const D3DMULTISAMPLE_TYPE s_checkMsaa[] =
	{
		D3DMULTISAMPLE_NONE,
		D3DMULTISAMPLE_2_SAMPLES,
		D3DMULTISAMPLE_4_SAMPLES,
		D3DMULTISAMPLE_8_SAMPLES,
		D3DMULTISAMPLE_16_SAMPLES,
	};

	static Msaa s_msaa[] =
	{
		{ D3DMULTISAMPLE_NONE,       0 },
		{ D3DMULTISAMPLE_2_SAMPLES,  0 },
		{ D3DMULTISAMPLE_4_SAMPLES,  0 },
		{ D3DMULTISAMPLE_8_SAMPLES,  0 },
		{ D3DMULTISAMPLE_16_SAMPLES, 0 },
	};

	static const D3DBLEND s_blendFactor[] =
	{
		(D3DBLEND)0, // ignored
		D3DBLEND_ZERO,
		D3DBLEND_ONE,
		D3DBLEND_SRCCOLOR,
		D3DBLEND_INVSRCCOLOR,
		D3DBLEND_SRCALPHA,
		D3DBLEND_INVSRCALPHA,
		D3DBLEND_DESTALPHA,
		D3DBLEND_INVDESTALPHA,
		D3DBLEND_DESTCOLOR,
		D3DBLEND_INVDESTCOLOR,
		D3DBLEND_SRCALPHASAT,
	};

	static const D3DCMPFUNC s_depthFunc[] =
	{
		(D3DCMPFUNC)0, // ignored
		D3DCMP_LESS,
		D3DCMP_LESSEQUAL,
		D3DCMP_EQUAL,
		D3DCMP_GREATEREQUAL,
		D3DCMP_GREATER,
		D3DCMP_NOTEQUAL,
		D3DCMP_NEVER,
		D3DCMP_ALWAYS,
	};

	static const D3DCULL s_cullMode[] =
	{
		D3DCULL_NONE,
		D3DCULL_CW,
		D3DCULL_CCW,
	};

	static const D3DFORMAT s_checkColorFormats[] =
	{
		D3DFMT_UNKNOWN,
		D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,
		D3DFMT_R32F, D3DFMT_R16F, D3DFMT_G16R16, D3DFMT_A8R8G8B8, D3DFMT_UNKNOWN,

		D3DFMT_UNKNOWN, // terminator
	};

	static D3DFORMAT s_colorFormat[] =
	{
		D3DFMT_UNKNOWN, // ignored
		D3DFMT_A8R8G8B8,
		D3DFMT_R32F,
	};

	static const D3DFORMAT s_depthFormat[] =
	{
		D3DFMT_UNKNOWN, // ignored
		D3DFMT_D24S8,
	};

	static const D3DTEXTUREADDRESS s_textureAddress[] =
	{
		D3DTADDRESS_WRAP,
		D3DTADDRESS_MIRROR,
		D3DTADDRESS_CLAMP,
	};

	static const D3DTEXTUREFILTERTYPE s_textureFilter[] =
	{
		D3DTEXF_LINEAR,
		D3DTEXF_POINT,
		D3DTEXF_ANISOTROPIC,
	};

	struct TextureFormatInfo
	{
		D3DFORMAT m_fmt;
		uint8_t m_bpp;
	};

	static const TextureFormatInfo s_textureFormat[TextureFormat::Count] =
	{
		{ D3DFMT_DXT1,         1 },
		{ D3DFMT_DXT3,         1 },
		{ D3DFMT_DXT5,         1 },
		{ D3DFMT_UNKNOWN,      0 },
		{ D3DFMT_L8,           1 },
		{ D3DFMT_X8R8G8B8,     4 },
		{ D3DFMT_A8R8G8B8,     4 },
		{ D3DFMT_A16B16G16R16, 8 },
	};

	struct RendererContext
	{
		RendererContext()
			: m_flags(BGFX_RESET_NONE)
			, m_initialized(false)
			, m_fmtNULL(false)
			, m_fmtDF16(false)
			, m_fmtDF24(false)
			, m_fmtINTZ(false)
			, m_fmtRAWZ(false)
			, m_rtMsaa(false)
		{
			m_rt.idx = invalidHandle;
		}

		void init()
		{
			D3DFORMAT adapterFormat = D3DFMT_X8R8G8B8;

			// http://msdn.microsoft.com/en-us/library/windows/desktop/bb172588%28v=vs.85%29.aspx
			memset(&m_params, 0, sizeof(m_params) );
			m_params.BackBufferWidth = BGFX_DEFAULT_WIDTH;
			m_params.BackBufferHeight = BGFX_DEFAULT_HEIGHT;
			m_params.BackBufferFormat = adapterFormat;
			m_params.BackBufferCount = 1;
			m_params.MultiSampleType = D3DMULTISAMPLE_NONE;
			m_params.MultiSampleQuality = 0;
			m_params.EnableAutoDepthStencil = TRUE;
			m_params.AutoDepthStencilFormat = D3DFMT_D24S8;
			m_params.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
#if BX_PLATFORM_WINDOWS
			m_params.FullScreen_RefreshRateInHz = 0;
			m_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			m_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			m_params.hDeviceWindow = g_bgfxHwnd;
			m_params.Windowed = true;

			RECT rect;
			GetWindowRect(g_bgfxHwnd, &rect);
			m_params.BackBufferWidth = rect.right-rect.left;
			m_params.BackBufferHeight = rect.bottom-rect.top;

			m_d3d9dll = LoadLibrary("d3d9.dll");
			BGFX_FATAL(NULL != m_d3d9dll, bgfx::Fatal::D3D9_UnableToCreateInterface, "Failed to load d3d9.dll.");

			m_D3DPERF_SetMarker = (D3DPERF_SetMarkerFunc)GetProcAddress(m_d3d9dll, "D3DPERF_SetMarker");
			m_D3DPERF_BeginEvent = (D3DPERF_BeginEventFunc)GetProcAddress(m_d3d9dll, "D3DPERF_BeginEvent");
			m_D3DPERF_EndEvent = (D3DPERF_EndEventFunc)GetProcAddress(m_d3d9dll, "D3DPERF_EndEvent");

#if BGFX_CONFIG_RENDERER_DIRECT3D_EX
			Direct3DCreate9ExFunc direct3DCreate9Ex = (Direct3DCreate9ExFunc)GetProcAddress(m_d3d9dll, "Direct3DCreate9Ex");
			BGFX_FATAL(NULL != direct3DCreate9Ex, bgfx::Fatal::D3D9_UnableToCreateInterface, "Function Direct3DCreate9Ex not found.");
			direct3DCreate9Ex(D3D_SDK_VERSION, &m_d3d9);
#else
			Direct3DCreate9Func direct3DCreate9 = (Direct3DCreate9Func)GetProcAddress(m_d3d9dll, "Direct3DCreate9");
			BGFX_FATAL(NULL != direct3DCreate9, bgfx::Fatal::D3D9_UnableToCreateInterface, "Function Direct3DCreate9 not found.");
			m_d3d9 = direct3DCreate9(D3D_SDK_VERSION);
#endif // defined(D3D_DISABLE_9EX)

			BGFX_FATAL(m_d3d9, bgfx::Fatal::D3D9_UnableToCreateInterface, "Unable to create Direct3D.");

			m_adapter = D3DADAPTER_DEFAULT;
			m_deviceType = D3DDEVTYPE_HAL;

			uint32_t adapterCount = m_d3d9->GetAdapterCount();
			for (uint32_t ii = 0; ii < adapterCount; ++ii)
			{
				D3DADAPTER_IDENTIFIER9 identifier;
				DX_CHECK(m_d3d9->GetAdapterIdentifier(ii, 0, &identifier) );

				BX_TRACE("Adapter #%d", ii);
				BX_TRACE("\tDriver: %s", identifier.Driver);
				BX_TRACE("\tDescription: %s", identifier.Description);
				BX_TRACE("\tDeviceName: %s", identifier.DeviceName);
				BX_TRACE("\tVendorId: 0x%08x, DeviceId: 0x%08x, SubSysId: 0x%08x, Revision: 0x%08x"
						, identifier.VendorId
						, identifier.DeviceId
						, identifier.SubSysId
						, identifier.Revision
						);

#if BGFX_CONFIG_DEBUG_PERFHUD
				if (0 != strstr(identifier.Description, "PerfHUD") )
				{
					m_adapter = ii;
					m_deviceType = D3DDEVTYPE_REF;
				}
#endif // BGFX_CONFIG_DEBUG_PERFHUD
			}

			uint32_t behaviorFlags[] =
			{
				D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE,
				D3DCREATE_MIXED_VERTEXPROCESSING,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			};

			for (uint32_t ii = 0; ii < countof(behaviorFlags) && NULL == m_device; ++ii)
			{
#if BGFX_CONFIG_RENDERER_DIRECT3D_EX
				DX_CHECK(m_d3d9->CreateDeviceEx(m_adapter
						, m_deviceType
						, g_bgfxHwnd
						, behaviorFlags[ii]
						, &m_params
						, NULL
						, &m_device
						) );
#else
				DX_CHECK(m_d3d9->CreateDevice(m_adapter
					, m_deviceType
					, g_bgfxHwnd
					, behaviorFlags[ii]
					, &m_params
					, &m_device
					) );
#endif // BGFX_CONFIG_RENDERER_DIRECT3D_EX
			}

			BGFX_FATAL(m_device, bgfx::Fatal::D3D9_UnableToCreateDevice, "Unable to create Direct3D9 device.");

			DX_CHECK(m_device->GetDeviceCaps(&m_caps) );

			// For shit GPUs that can create DX9 device but can't do simple stuff. GTFO!
			BGFX_FATAL( (D3DPTEXTURECAPS_SQUAREONLY & m_caps.TextureCaps) == 0, bgfx::Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_SQUAREONLY");
			BGFX_FATAL( (D3DPTEXTURECAPS_MIPMAP & m_caps.TextureCaps) == D3DPTEXTURECAPS_MIPMAP, bgfx::Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_MIPMAP");
			BGFX_FATAL( (D3DPTEXTURECAPS_ALPHA & m_caps.TextureCaps) == D3DPTEXTURECAPS_ALPHA, bgfx::Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_ALPHA");
			BGFX_FATAL(m_caps.VertexShaderVersion >= D3DVS_VERSION(2, 0) && m_caps.PixelShaderVersion >= D3DPS_VERSION(2, 1)
					  , bgfx::Fatal::MinimumRequiredSpecs
					  , "Shader Model Version (vs: %x, ps: %x)."
					  , m_caps.VertexShaderVersion
					  , m_caps.PixelShaderVersion
					  );
			BGFX_FATAL(m_caps.MaxTextureWidth >= 2048 && m_caps.MaxTextureHeight >= 2048
					  , bgfx::Fatal::MinimumRequiredSpecs
					  , "Maximum texture size is below 2048 (w: %d, h: %d)."
					  , m_caps.MaxTextureWidth
					  , m_caps.MaxTextureHeight
					  );

			BX_TRACE("Max vertex shader 3.0 instr. slots: %d", m_caps.MaxVertexShader30InstructionSlots);
			BX_TRACE("Max vertex shader constants: %d", m_caps.MaxVertexShaderConst);
			BX_TRACE("Max fragment shader 2.0 instr. slots: %d", m_caps.PS20Caps.NumInstructionSlots);
			BX_TRACE("Max fragment shader 3.0 instr. slots: %d", m_caps.MaxPixelShader30InstructionSlots);

			m_fmtNULL = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_NULL) );
			m_fmtDF16 = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_DF16) );
			m_fmtDF24 = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_DF24) );
			m_fmtINTZ = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_INTZ) );
			m_fmtRAWZ = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_RAWZ) );

			uint32_t index = 1;
			for (const D3DFORMAT* fmt = &s_checkColorFormats[index]; *fmt != D3DFMT_UNKNOWN; ++fmt, ++index)
			{
				for (; *fmt != D3DFMT_UNKNOWN; ++fmt)
				{
					if (SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, *fmt) ) )
					{
						s_colorFormat[index] = *fmt;
						break;
					}
				}

				for (; *fmt != D3DFMT_UNKNOWN; ++fmt);
			}

			m_fmtDepth = D3DFMT_D24S8;

#elif BX_PLATFORM_XBOX360
			m_params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			m_params.DisableAutoBackBuffer = FALSE;
			m_params.DisableAutoFrontBuffer = FALSE;
			m_params.FrontBufferFormat = D3DFMT_X8R8G8B8;
			m_params.FrontBufferColorSpace = D3DCOLORSPACE_RGB;

			m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
			BX_TRACE("Creating D3D9 %p", m_d3d9);

			XVIDEO_MODE videoMode;
			XGetVideoMode(&videoMode);
			if (!videoMode.fIsWideScreen)
			{
				m_params.Flags |= D3DPRESENTFLAG_NO_LETTERBOX;
			}

			BX_TRACE("Creating device");
			DX_CHECK(m_d3d9->CreateDevice(m_adapter
					, m_deviceType
					, NULL
					, D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_BUFFER_2_FRAMES
					, &m_params
					, &m_device
					) );

			BX_TRACE("Device %p", m_device);

			m_fmtDepth = D3DFMT_D24FS8;
#endif // BX_PLATFORM_WINDOWS

			postReset();

			m_initialized = true;
		}

		void shutdown()
		{
			preReset();

			DX_RELEASE(m_device, 0);
			DX_RELEASE(m_d3d9, 0);

#if BX_PLATFORM_WINDOWS
			FreeLibrary(m_d3d9dll);
#endif // BX_PLATFORM_WINDOWS

			m_initialized = false;
		}

		void updateMsaa()
		{
			for (uint32_t ii = 1, last = 0; ii < countof(s_checkMsaa); ++ii)
			{
				D3DMULTISAMPLE_TYPE msaa = s_checkMsaa[ii];
				DWORD quality;

				HRESULT hr = m_d3d9->CheckDeviceMultiSampleType(m_adapter
					, m_deviceType
					, m_params.BackBufferFormat
					, m_params.Windowed
					, msaa
					, &quality
					);

				if (SUCCEEDED(hr) )
				{
					s_msaa[ii].m_type = msaa;
					s_msaa[ii].m_quality = uint32_imax(0, quality-1);
					last = ii;
				}
				else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}
		}

		void updateResolution(const Resolution& _resolution)
		{
			if (m_params.BackBufferWidth != _resolution.m_width
			||  m_params.BackBufferHeight != _resolution.m_height
			||  m_flags != _resolution.m_flags)
			{
				m_flags = _resolution.m_flags;

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

#if BX_PLATFORM_WINDOWS
				D3DDEVICE_CREATION_PARAMETERS dcp;
				DX_CHECK(m_device->GetCreationParameters(&dcp) );

				D3DDISPLAYMODE dm;
				DX_CHECK(m_d3d9->GetAdapterDisplayMode(dcp.AdapterOrdinal, &dm) );
				
				m_params.BackBufferFormat = dm.Format;
#endif // BX_PLATFORM_WINDOWS

				m_params.BackBufferWidth = _resolution.m_width;
				m_params.BackBufferHeight = _resolution.m_height;
				m_params.FullScreen_RefreshRateInHz = BGFX_RESET_FULLSCREEN == (m_flags&BGFX_RESET_FULLSCREEN_MASK) ? 60 : 0;
				m_params.PresentationInterval = !!(m_flags&BGFX_RESET_VSYNC) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

				updateMsaa();

				Msaa& msaa = s_msaa[(m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];
				m_params.MultiSampleType = msaa.m_type;
				m_params.MultiSampleQuality = msaa.m_quality;

				preReset();
				DX_CHECK(m_device->Reset(&m_params) );
				postReset();
			}
		}

		void setRenderTarget(RenderTargetHandle _rt, bool _msaa = true)
		{
			if (_rt.idx == invalidHandle)
			{
				DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
				DX_CHECK(m_device->SetDepthStencilSurface(m_backBufferDepthStencil) );
			}
			else
			{
				RenderTarget& renderTarget = m_renderTargets[_rt.idx];
				if (NULL != renderTarget.m_rt)
				{
					DX_CHECK(m_device->SetRenderTarget(0, renderTarget.m_rt) );
				}
				else
				{
					DX_CHECK(m_device->SetRenderTarget(0, renderTarget.m_color) );
				}

				DX_CHECK(m_device->SetDepthStencilSurface(NULL != renderTarget.m_depth ? renderTarget.m_depth : m_backBufferDepthStencil) );
			}

			if (m_rt.idx != invalidHandle
			&&  m_rt.idx != _rt.idx
			&&  m_rtMsaa)
			{
				RenderTarget& renderTarget = m_renderTargets[m_rt.idx];
				if (!renderTarget.m_depthOnly
				&&  renderTarget.m_rt != NULL)
				{
					renderTarget.resolve();
				}
			}

			m_rt = _rt;
			m_rtMsaa = _msaa;
		}

		void setShaderConstantF(uint8_t _flags, uint16_t _regIndex, const float* _val, uint16_t _numRegs)
		{
			if (_flags&BGFX_UNIFORM_FRAGMENTBIT)
			{
				DX_CHECK(m_device->SetPixelShaderConstantF(_regIndex, _val, _numRegs) );
			}
			else
			{
				DX_CHECK(m_device->SetVertexShaderConstantF(_regIndex, _val, _numRegs) );
			}
		}

		void reset()
		{
			preReset();

			HRESULT hr;

			do 
			{
				hr = m_device->Reset(&m_params);
			} while (FAILED(hr) );

			postReset();
		}

		bool isLost(HRESULT _hr) const
		{
			return D3DERR_DEVICELOST == _hr
				|| D3DERR_DRIVERINTERNALERROR == _hr
#if !defined(D3D_DISABLE_9EX)
				|| D3DERR_DEVICEHUNG == _hr
				|| D3DERR_DEVICEREMOVED == _hr
#endif // !defined(D3D_DISABLE_9EX)
				;
		}

		void flip()
		{
			if (NULL != m_device)
			{
#if BGFX_CONFIG_RENDERER_DIRECT3D_EX
				DX_CHECK(m_device->WaitForVBlank(0) );
#endif // BGFX_CONFIG_RENDERER_DIRECT3D_EX

				HRESULT hr;
				hr = m_device->Present(NULL, NULL, NULL, NULL);

#if BX_PLATFORM_WINDOWS
				if (isLost(hr) )
				{
					do
					{
						do 
						{
							hr = m_device->TestCooperativeLevel();
						}
						while (D3DERR_DEVICENOTRESET != hr);

						reset();
						hr = m_device->TestCooperativeLevel();
					}
					while (FAILED(hr) );
				}
				else if (FAILED(hr) )
				{
					BX_TRACE("Present failed with err 0x%08x.", hr);
				}
#endif // BX_PLATFORM_
			}
		}

		void preReset()
		{
			for (uint32_t stage = 0; stage < BGFX_STATE_TEX_COUNT; ++stage)
			{
				DX_CHECK(m_device->SetTexture(stage, NULL) );
			}

			DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
			DX_CHECK(m_device->SetDepthStencilSurface(m_backBufferDepthStencil) );
			DX_CHECK(m_device->SetVertexShader(NULL) );
			DX_CHECK(m_device->SetPixelShader(NULL) );
			DX_CHECK(m_device->SetStreamSource(0, NULL, 0, 0) );
			DX_CHECK(m_device->SetIndices(NULL) );

			DX_RELEASE(m_backBufferColor, 0);
			DX_RELEASE(m_backBufferDepthStencil, 0);

			for (uint32_t ii = 0; ii < countof(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].preReset();
			}

			for (uint32_t ii = 0; ii < countof(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].preReset();
			}

			for (uint32_t ii = 0; ii < countof(m_renderTargets); ++ii)
			{
				m_renderTargets[ii].preReset();
			}
		}

		void postReset()
		{
			DX_CHECK(m_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBufferColor) );
			DX_CHECK(m_device->GetDepthStencilSurface(&m_backBufferDepthStencil) );

			for (uint32_t ii = 0; ii < countof(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].postReset();
			}

			for (uint32_t ii = 0; ii < countof(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].postReset();
			}

			for (uint32_t ii = 0; ii < countof(m_renderTargets); ++ii)
			{
				m_renderTargets[ii].postReset();
			}
		}

		void saveScreenShot(Memory* _mem)
		{
#if BX_PLATFORM_WINDOWS
			IDirect3DSurface9* surface;
			D3DDEVICE_CREATION_PARAMETERS dcp;
			DX_CHECK(m_device->GetCreationParameters(&dcp) );

			D3DDISPLAYMODE dm;
			DX_CHECK(m_d3d9->GetAdapterDisplayMode(dcp.AdapterOrdinal, &dm) );

			DX_CHECK(m_device->CreateOffscreenPlainSurface(dm.Width
				, dm.Height
				, D3DFMT_A8R8G8B8
				, D3DPOOL_SCRATCH
				, &surface
				, NULL
				) );

			DX_CHECK(m_device->GetFrontBufferData(0, surface) );

			D3DLOCKED_RECT rect;
			DX_CHECK(surface->LockRect(&rect
				, NULL
				, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY
				) );

			RECT rc;
			GetClientRect(g_bgfxHwnd, &rc);
			POINT point;
			point.x = rc.left;
			point.y = rc.top;
			ClientToScreen(g_bgfxHwnd, &point);
			uint8_t* data = (uint8_t*)rect.pBits;
			uint32_t bpp = rect.Pitch/dm.Width;
			saveTga( (const char*)_mem->data, m_params.BackBufferWidth, m_params.BackBufferHeight, rect.Pitch, &data[point.y*rect.Pitch+point.x*bpp]);

			DX_CHECK(surface->UnlockRect() );
			DX_RELEASE(surface, 0);
#endif // BX_PLATFORM_WINDOWS
		}

#if BX_PLATFORM_WINDOWS
		D3DCAPS9 m_caps;

		D3DPERF_SetMarkerFunc m_D3DPERF_SetMarker;
		D3DPERF_BeginEventFunc  m_D3DPERF_BeginEvent;
		D3DPERF_EndEventFunc m_D3DPERF_EndEvent;
#endif // BX_PLATFORM_WINDOWS

#if BGFX_CONFIG_RENDERER_DIRECT3D_EX
		IDirect3D9Ex* m_d3d9;
		IDirect3DDevice9Ex* m_device;
#else
		IDirect3D9* m_d3d9;
		IDirect3DDevice9* m_device;
#endif // BGFX_CONFIG_RENDERER_DIRECT3D_EX

		IDirect3DSurface9* m_backBufferColor;
		IDirect3DSurface9* m_backBufferDepthStencil;

		HMODULE m_d3d9dll;
		uint32_t m_adapter;
		D3DDEVTYPE m_deviceType;
		D3DPRESENT_PARAMETERS m_params;
		uint32_t m_flags;

		bool m_initialized;
		bool m_fmtNULL;
		bool m_fmtDF16;
		bool m_fmtDF24;
		bool m_fmtINTZ;
		bool m_fmtRAWZ;

		D3DFORMAT m_fmtDepth;

		IndexBuffer m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
 		Shader m_vertexShaders[BGFX_CONFIG_MAX_VERTEX_SHADERS];
 		Shader m_fragmentShaders[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
 		Material m_materials[BGFX_CONFIG_MAX_MATERIALS];
 		Texture m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDeclaration m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
 		RenderTarget m_renderTargets[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		TextVideoMem m_textVideoMem;
		RenderTargetHandle m_rt;
		bool m_rtMsaa;
	};

	static RendererContext s_renderCtx;

	void IndexBuffer::create(uint32_t _size, void* _data)
	{
		m_size = _size;
		m_dynamic = NULL == _data;

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL pool = D3DPOOL_MANAGED;

		if (m_dynamic)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
		}

		DX_CHECK(s_renderCtx.m_device->CreateIndexBuffer(m_size
			, usage
			, D3DFMT_INDEX16
			, pool
			, &m_ptr
			, NULL
			) );

		if (NULL != _data)
		{
			update(_size, _data);
		}
	}

	void IndexBuffer::preReset()
	{
		if (m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void IndexBuffer::postReset()
	{
		if (m_dynamic)
		{
			DX_CHECK(s_renderCtx.m_device->CreateIndexBuffer(m_size
				, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC
				, D3DFMT_INDEX16
				, D3DPOOL_DEFAULT
				, &m_ptr
				, NULL
				) );
		}
	}

	void VertexBuffer::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle)
	{
		m_size = _size;
		m_decl = _declHandle;
		m_dynamic = NULL == _data;

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL pool = D3DPOOL_MANAGED;

		if (m_dynamic)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
		}

		DX_CHECK(s_renderCtx.m_device->CreateVertexBuffer(m_size
				, usage
				, 0
				, pool
				, &m_ptr
				, NULL 
				) );

		if (NULL != _data)
		{
			update(_size, _data);
		}
	}

	void VertexBuffer::preReset()
	{
		if (m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void VertexBuffer::postReset()
	{
		if (m_dynamic)
		{
			DX_CHECK(s_renderCtx.m_device->CreateVertexBuffer(m_size
					, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC
					, 0
					, D3DPOOL_DEFAULT
					, &m_ptr
					, NULL 
					) );
		}
	}

	static const D3DVERTEXELEMENT9 s_attrib[Attrib::Count+1] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0},
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,       0},
		{0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        0},
		{0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        1},
		{0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,  0},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     0},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     1},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     2},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     3},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     4},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     5},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     6},
		{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     7},
		D3DDECL_END()
	};

	void VertexDeclaration::create(const VertexDecl& _decl)
	{
		memcpy(&m_decl, &_decl, sizeof(VertexDecl) );
		dump(m_decl);

		D3DVERTEXELEMENT9 vertexElements[Attrib::Count+1];
		D3DVERTEXELEMENT9* elem = vertexElements;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (0xff != _decl.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				_decl.decode(Attrib::Enum(attr), num, type, normalized);

				memcpy(elem, &s_attrib[attr], sizeof(D3DVERTEXELEMENT9) );

				D3DDECLTYPE declType = D3DDECLTYPE(elem->Type);

				switch (type)
				{
				case AttribType::Uint8:
					if (normalized)
					{
						declType = D3DDECLTYPE_UBYTE4N;
					}
					else
					{
						declType = D3DDECLTYPE_UBYTE4;
					}
					break;

				case AttribType::Uint16:
					if (normalized)
					{
						switch (num)
						{
						default:
						case 2:
							declType = D3DDECLTYPE_SHORT2N;
							break;

						case 4:
							declType = D3DDECLTYPE_SHORT4N;
							break;
						}
					}
					else
					{
						switch (num)
						{
						default:
						case 2:
							declType = D3DDECLTYPE_SHORT2;
							break;

						case 4:
							declType = D3DDECLTYPE_SHORT4;
							break;
						}
					}
					break;

				case AttribType::Float:
					switch (num)
					{
					case 1:
						declType = D3DDECLTYPE_FLOAT1;
						break;

					case 2:
						declType = D3DDECLTYPE_FLOAT2;
						break;
						
					default:
					case 3:
						declType = D3DDECLTYPE_FLOAT3;
						break;

					case 4:
						declType = D3DDECLTYPE_FLOAT4;
						break;
					}

					break;

				default:
					BX_CHECK(false, "Invalid attrib type.");
					break;
				}

				elem->Type = declType;
				elem->Offset = _decl.m_offset[attr];
				++elem;

				BX_TRACE("\tattr %d, num %d, type %d, norm %d, offset %d"
					, attr
					, num
					, type
					, normalized
					, _decl.m_offset[attr]
				);
			}
		}

		memcpy(elem, &s_attrib[Attrib::Count], sizeof(D3DVERTEXELEMENT9) );

		DX_CHECK(s_renderCtx.m_device->CreateVertexDeclaration(vertexElements, &m_ptr) );
	}

	void Shader::create(bool _fragment, const Memory* _mem)
	{
		m_constantBuffer = ConstantBuffer::create(1024);

		StreamRead stream(_mem->data, _mem->size);
		uint16_t count;
		stream.read(count);

		m_numPredefined = 0;

		BX_TRACE("Shader consts %d", count);

		uint8_t fragmentBit = _fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		for (uint32_t ii = 0; ii < count; ++ii)
		{
			uint8_t nameSize;
			stream.read(nameSize);

			char name[256];
			stream.read(&name, nameSize);
			name[nameSize] = '\0';

			uint8_t type;
			stream.read(type);

			uint8_t num;
			stream.read(num);

			uint16_t regIndex;
			stream.read(regIndex);

			uint16_t regCount;
			stream.read(regCount);

			const char* kind = "invalid";

			const void* data = NULL;
			PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
			if (PredefinedUniform::Count != predefined)
			{
				kind = "predefined";
				m_predefined[m_numPredefined].m_loc = regIndex;
				m_predefined[m_numPredefined].m_count = regCount;
				m_predefined[m_numPredefined].m_type = predefined|fragmentBit;
				m_numPredefined++;
			}
			else
			{
				const UniformInfo* info = s_renderCtx.m_uniformReg.find(name);
				BX_CHECK(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);
				if (NULL != info)
				{
					kind = "user";
					data = info->m_data;
					m_constantBuffer->writeUniformRef( (ConstantType::Enum)(type|fragmentBit), regIndex, data, regCount);
				}
			}

			BX_TRACE("\t%s: %s, type %2d, num %2d, r.index %3d, r.count %2d"
				, kind
				, name
				, type
				, num
				, regIndex
				, regCount
				);
		}

		uint16_t shaderSize;
		stream.read(shaderSize);

		m_constantBuffer->finish();

		const DWORD* code = (const DWORD*)stream.getDataPtr();

		if (_fragment)
		{
			DX_CHECK(s_renderCtx.m_device->CreatePixelShader(code, (IDirect3DPixelShader9**)&m_ptr) );
		}
		else
		{
			DX_CHECK(s_renderCtx.m_device->CreateVertexShader(code, (IDirect3DVertexShader9**)&m_ptr) );
		}
	}

	void Texture::createTexture(uint32_t _width, uint32_t _height, uint8_t _numMips, D3DFORMAT _fmt)
	{
		m_type = Texture2D;

		DX_CHECK(s_renderCtx.m_device->CreateTexture(_width
			, _height
			, _numMips
			, 0
			, _fmt
			, D3DPOOL_MANAGED
			, (IDirect3DTexture9**)&m_ptr
			, NULL
			) );

		BGFX_FATAL(NULL != m_ptr, Fatal::D3D9_UnableToCreateTexture, "Failed to create texture (size: %dx%d, mips: %d, fmt: 0x%08x)."
			, _width
			, _height
			, _numMips
			, _fmt
			);
	}

	void Texture::createVolumeTexture(uint32_t _width, uint32_t _height, uint32_t _depth, uint32_t _numMips, D3DFORMAT _fmt)
	{
		m_type = Texture3D;

		DX_CHECK(s_renderCtx.m_device->CreateVolumeTexture(_width
			, _height
			, _depth
			, _numMips
			, 0
			, _fmt
			, D3DPOOL_MANAGED
			, (IDirect3DVolumeTexture9**)&m_ptr
			, NULL
			) );

		BGFX_FATAL(NULL != m_ptr, Fatal::D3D9_UnableToCreateTexture, "Failed to create volume texture (size: %dx%dx%d, mips: %d, fmt: 0x%08x)."
			, _width
			, _height
			, _depth
			, _numMips
			, _fmt
			);
	}

	void Texture::createCubeTexture(uint32_t _edge, uint32_t _numMips, D3DFORMAT _fmt)
	{
		m_type = TextureCube;

		DX_CHECK(s_renderCtx.m_device->CreateCubeTexture(_edge
			, _numMips
			, 0
			, _fmt
			, D3DPOOL_MANAGED
			, (IDirect3DCubeTexture9**)&m_ptr
			, NULL
			) );

		BGFX_FATAL(NULL != m_ptr, Fatal::D3D9_UnableToCreateTexture, "Failed to create cube texture (edge: %d, mips: %d, fmt: 0x%08x)."
			, _edge
			, _numMips
			, _fmt
			);
	}

	uint8_t* Texture::lock(uint8_t _side, uint8_t _lod, uint32_t& _pitch, uint32_t& _slicePitch)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				IDirect3DTexture9* texture = (IDirect3DTexture9*)m_ptr;
				D3DLOCKED_RECT rect;
				DX_CHECK(texture->LockRect(_lod, &rect, NULL, 0) );
				_pitch = rect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)rect.pBits;
			}

		case Texture3D:
			{
				IDirect3DVolumeTexture9* texture = (IDirect3DVolumeTexture9*)m_ptr;
				D3DLOCKED_BOX box;
				DX_CHECK(texture->LockBox(_lod, &box, NULL, 0) );
				_pitch = box.RowPitch;
				_slicePitch = box.SlicePitch;
				return (uint8_t*)box.pBits;
			}

		case TextureCube:
			{
				IDirect3DCubeTexture9* texture = (IDirect3DCubeTexture9*)m_ptr;
				D3DLOCKED_RECT rect;
				DX_CHECK(texture->LockRect(D3DCUBEMAP_FACES(_side), _lod, &rect, NULL, 0) );
				_pitch = rect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)rect.pBits;
			}
		}

		BX_CHECK(false, "You should not be here.");
		return NULL;
	}

	void Texture::unlock(uint8_t _side, uint8_t _lod)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				IDirect3DTexture9* texture = (IDirect3DTexture9*)m_ptr;
				DX_CHECK(texture->UnlockRect(_lod) );
			}
			return;

		case Texture3D:
			{
				IDirect3DVolumeTexture9* texture = (IDirect3DVolumeTexture9*)m_ptr;
				DX_CHECK(texture->UnlockBox(_lod) );
			}
			return;

		case TextureCube:
			{
				IDirect3DCubeTexture9* texture = (IDirect3DCubeTexture9*)m_ptr;
				DX_CHECK(texture->UnlockRect(D3DCUBEMAP_FACES(_side), _lod) );
			}
			return;
		}

		BX_CHECK(false, "You should not be here.");
	}

	void Texture::create(const Memory* _mem, uint32_t _flags)
	{
		m_tau = s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
		m_tav = s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
		m_taw = s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
		m_minFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
		m_magFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
		m_mipFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];
		m_srgb = (_flags&BGFX_TEXTURE_SRGB) == BGFX_TEXTURE_SRGB;

		Dds dds;

		if (parseDds(dds, _mem) )
		{
			uint8_t bpp = dds.m_bpp;

			bool decompress = false;

			if (dds.m_cubeMap)
			{
				createCubeTexture(dds.m_width, dds.m_numMips, s_textureFormat[dds.m_type].m_fmt);
			}
			else if (dds.m_depth > 1)
			{
				createVolumeTexture(dds.m_width, dds.m_height, dds.m_depth, dds.m_numMips, s_textureFormat[dds.m_type].m_fmt);
			}
			else
			{
				createTexture(dds.m_width, dds.m_height, dds.m_numMips, s_textureFormat[dds.m_type].m_fmt);
			}

			if (decompress
			||  TextureFormat::Unknown < dds.m_type)
			{
				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					uint32_t width = dds.m_width;
					uint32_t height = dds.m_height;
					uint32_t depth = dds.m_depth;

					for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
					{
						width = uint32_max(1, width);
						height = uint32_max(1, height);
						depth = uint32_max(1, depth);

						Mip mip;
						if (getRawImageData(dds, side, lod, _mem, mip) )
						{
							uint32_t pitch;
							uint32_t slicePitch;
							uint8_t* bits = lock(side, lod, pitch, slicePitch);

							if (width != mip.m_width
							||  height != mip.m_height)
							{
								uint32_t srcpitch = mip.m_width*bpp;

								uint8_t* temp = (uint8_t*)g_realloc(NULL, srcpitch*mip.m_height);
								mip.decode(temp);

								uint32_t dstpitch = pitch;
								for (uint32_t yy = 0; yy < height; ++yy)
								{
									uint8_t* src = &temp[yy*srcpitch];
									uint8_t* dst = &bits[yy*dstpitch];
									memcpy(dst, src, srcpitch);
								}

								g_free(temp);
							}
							else
							{
								mip.decode(bits);
							}

							unlock(side, lod);
						}

						width >>= 1;
						height >>= 1;
						depth >>= 1;
					}
				}
			}
			else
			{
				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
					{
						Mip mip;
						if (getRawImageData(dds, 0, lod, _mem, mip) )
						{
							uint32_t pitch;
							uint32_t slicePitch;
							uint8_t* dst = lock(side, lod, pitch, slicePitch);

							memcpy(dst, mip.m_data, mip.m_size);

							unlock(side, lod);
						}
					}
				}
			}
		}
		else
		{
			StreamRead stream(_mem->data, _mem->size);

			uint32_t magic;
			stream.read(magic);

			if (BGFX_MAGIC == magic)
			{
				uint16_t width;
				stream.read(width);

				uint16_t height;
				stream.read(height);

				uint8_t bpp;
				stream.read(bpp);

				uint8_t numMips;
				stream.read(numMips);

				stream.align(16);

				D3DFORMAT fmt = 1 == bpp ? D3DFMT_L8 : D3DFMT_A8R8G8B8;

				createTexture(width, height, numMips, fmt);

				for (uint8_t mip = 0; mip < numMips; ++mip)
				{
					width = uint32_max(width, 1);
					height = uint32_max(height, 1);

					uint32_t pitch;
					uint32_t slicePitch;
					uint8_t* dst = lock(0, mip, pitch, slicePitch);
					stream.read(dst, width*height*bpp);
					unlock(0, mip);

					width >>= 1;
					height >>= 1;
				}
			}
			else
			{
				//
			}
		}
	}

	void Texture::commit(uint8_t _stage)
	{
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MINFILTER, m_minFilter) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MAGFILTER, m_magFilter) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MIPFILTER, m_mipFilter) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_ADDRESSU, m_tau) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_ADDRESSV, m_tav) );
		if (m_type == Texture3D)
		{
			DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_ADDRESSW, m_taw) );
		}
#if BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_SRGBTEXTURE, m_srgb) );
#endif // BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderCtx.m_device->SetTexture(_stage, m_ptr) );
	}

	void RenderTarget::create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		m_width = _width;
		m_height = _height;
		m_flags = _flags;
		m_minFilter = s_textureFilter[(_textureFlags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
		m_magFilter = s_textureFilter[(_textureFlags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];

		createTextures();
	}

	void RenderTarget::createTextures()
	{
		if (0 != m_flags)
		{
			m_msaa = s_msaa[(m_flags&BGFX_RENDER_TARGET_MSAA_MASK)>>BGFX_RENDER_TARGET_MSAA_SHIFT];
			uint32_t colorFormat = (m_flags&BGFX_RENDER_TARGET_COLOR_MASK)>>BGFX_RENDER_TARGET_COLOR_SHIFT;
			uint32_t depthFormat = (m_flags&BGFX_RENDER_TARGET_DEPTH_MASK)>>BGFX_RENDER_TARGET_DEPTH_SHIFT;
			m_depthOnly = (0 == colorFormat && 0 < depthFormat);

			// CheckDeviceFormat D3DUSAGE_SRGBWRITE

			if (m_depthOnly)
			{
				DX_CHECK(s_renderCtx.m_device->CreateRenderTarget(1
					, 1
					, D3DFMT_R5G6B5
					, D3DMULTISAMPLE_NONE
					, 0
					, false
					, &m_rt
					, NULL
					) );

				BGFX_FATAL(m_rt, bgfx::Fatal::D3D9_UnableToCreateRenderTarget, "Unable to create 1x1 render target.");

				DX_CHECK(s_renderCtx.m_device->CreateTexture(m_width
					, m_height
					, 1
					, D3DUSAGE_DEPTHSTENCIL
					, D3DFMT_DF24 //s_depthFormat[depthFormat]
					, D3DPOOL_DEFAULT
					, &m_depthTexture
					, NULL
					) );

				BGFX_FATAL(m_depthTexture, bgfx::Fatal::D3D9_UnableToCreateRenderTarget, "Unable to create depth texture.");

				DX_CHECK(m_depthTexture->GetSurfaceLevel(0, &m_depth) );
			}
			else
			{
				if (D3DMULTISAMPLE_NONE != m_msaa.m_type)
				{
					DX_CHECK(s_renderCtx.m_device->CreateRenderTarget(m_width
						, m_height
						, s_colorFormat[colorFormat]
						, m_msaa.m_type
						, m_msaa.m_quality
						, false
						, &m_rt
						, NULL
						) );

					BGFX_FATAL(m_rt, bgfx::Fatal::D3D9_UnableToCreateRenderTarget, "Unable to create MSAA render target.");
				}

				if (0 < colorFormat)
				{
					DX_CHECK(s_renderCtx.m_device->CreateTexture(m_width
						, m_height
						, 1
						, D3DUSAGE_RENDERTARGET
						, s_colorFormat[colorFormat]
						, D3DPOOL_DEFAULT
						, &m_colorTexture
						, NULL
						) );

					BGFX_FATAL(m_colorTexture, bgfx::Fatal::D3D9_UnableToCreateRenderTarget, "Unable to create color render target.");

					DX_CHECK(m_colorTexture->GetSurfaceLevel(0, &m_color) );
				}

				if (0 < depthFormat)
				{
					DX_CHECK(s_renderCtx.m_device->CreateDepthStencilSurface(m_width
							, m_height
							, s_depthFormat[depthFormat] // s_renderCtx.m_fmtDepth
							, m_msaa.m_type
							, m_msaa.m_quality
							, FALSE
							, &m_depth
							, NULL
							) );

					BGFX_FATAL(m_depth, bgfx::Fatal::D3D9_UnableToCreateRenderTarget, "Unable to create depth stencil surface.");
				}
			}
		}
	}

	void RenderTarget::destroyTextures()
	{
		if (0 != m_flags)
		{
			if (m_depthOnly)
			{
				DX_RELEASE(m_rt, 0);

				DX_RELEASE(m_depth, 1);
				DX_RELEASE(m_depthTexture, 0);
			}
			else
			{
				uint32_t colorFormat = (m_flags&BGFX_RENDER_TARGET_COLOR_MASK)>>BGFX_RENDER_TARGET_COLOR_SHIFT;
				uint32_t depthFormat = (m_flags&BGFX_RENDER_TARGET_DEPTH_MASK)>>BGFX_RENDER_TARGET_DEPTH_SHIFT;

				if (D3DMULTISAMPLE_NONE != m_msaa.m_type)
				{
					DX_RELEASE(m_rt, 0);
				}

				if (0 < colorFormat)
				{
					DX_RELEASE(m_color, 1);
					DX_RELEASE(m_colorTexture, 0);
				}

				if (0 < depthFormat)
				{
					DX_RELEASE(m_depth, 0);
				}
			}
		}
	}

	void RenderTarget::commit(uint8_t _stage)
	{
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MINFILTER, m_minFilter) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MAGFILTER, m_magFilter) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_MIPFILTER, D3DTEXF_POINT) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP) );
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP) );
#if BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderCtx.m_device->SetSamplerState(_stage, D3DSAMP_SRGBTEXTURE, (m_flags&BGFX_RENDER_TARGET_SRGBWRITE) == BGFX_RENDER_TARGET_SRGBWRITE) );
#endif // BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderCtx.m_device->SetTexture(_stage, m_depthOnly ? m_depthTexture : m_colorTexture) );
	}

	void RenderTarget::resolve()
	{
#if BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderCtx.m_device->StretchRect(m_rt
				, NULL
				, m_color
				, NULL
				, D3DTEXF_NONE
				) );
#endif // BX_PLATFORM_WINDOWS
	}
	
	void ConstantBuffer::commit(bool _force)
	{
		reset();

		do
		{
			uint32_t opcode = read();

			if (ConstantType::End == opcode)
			{
				break;
			}

			ConstantType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			decodeOpcode(opcode, type, loc, num, copy);

			const char* data;
			if (copy)
			{
				data = read(g_constantTypeSize[type]*num);
			}
			else
			{
				memcpy(&data, read(sizeof(void*) ), sizeof(void*) );
			}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _glsuffix, _dxsuffix, _type) \
		case ConstantType::_uniform: \
		{ \
			_type* value = (_type*)data; \
			s_renderCtx.m_device->SetVertexShaderConstant##_dxsuffix(loc, value, num); \
		} \
		break; \
		\
		case ConstantType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
		{ \
			_type* value = (_type*)data; \
			s_renderCtx.m_device->SetPixelShaderConstant##_dxsuffix(loc, value, num); \
		} \
		break;

			switch ((int32_t)type)
			{
			CASE_IMPLEMENT_UNIFORM(Uniform1i, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1f, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform1iv, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1fv, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform2fv, 2fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform3fv, 3fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform4fv, 4fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform3x3fv, Matrix3fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform4x4fv, Matrix4fv, F, float);

			case ConstantType::End:
				break;

			default:
				BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", m_pos, opcode, type, loc, num, copy);
				break;
			}

#undef CASE_IMPLEMENT_UNIFORM

		} while (true);
	}

	void TextVideoMemBlitter::setup()
	{
		uint32_t width = s_renderCtx.m_params.BackBufferWidth;
		uint32_t height = s_renderCtx.m_params.BackBufferHeight;

		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		s_renderCtx.setRenderTarget(rt, false);

		D3DVIEWPORT9 vp;
		vp.X = 0;
		vp.Y = 0;
		vp.Width = width;
		vp.Height = height;
		vp.MinZ = 0.0f;
		vp.MaxZ = 1.0f;
		DX_CHECK(s_renderCtx.m_device->SetViewport(&vp) );

		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZENABLE, FALSE) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE) );
		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID) );

		Material& material = s_renderCtx.m_materials[m_material.idx];
		s_renderCtx.m_device->SetVertexShader( (IDirect3DVertexShader9*)material.m_vsh->m_ptr);
		s_renderCtx.m_device->SetPixelShader( (IDirect3DPixelShader9*)material.m_fsh->m_ptr);

		VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
		VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[m_vb->decl.idx];
		DX_CHECK(s_renderCtx.m_device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );
		DX_CHECK(s_renderCtx.m_device->SetVertexDeclaration(vertexDecl.m_ptr) );

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
		DX_CHECK(s_renderCtx.m_device->SetIndices(ib.m_ptr) );

		float proj[16];
		matrix_ortho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		PredefinedUniform& predefined = material.m_predefined[0];
		uint8_t flags = predefined.m_type&BGFX_UNIFORM_FRAGMENTBIT;
		s_renderCtx.setShaderConstantF(flags, predefined.m_loc, proj, 4);

		s_renderCtx.m_textures[m_texture.idx].commit(0);
	}

	void TextVideoMemBlitter::render(uint32_t _numIndices)
	{
		uint32_t numVertices = _numIndices*4/6;
		s_renderCtx.m_indexBuffers[m_ib->handle.idx].update(_numIndices*2, m_ib->data);
		s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(numVertices*m_decl.m_stride, m_vb->data);

		DX_CHECK(s_renderCtx.m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST
			, 0
			, 0
			, numVertices
			, 0
			, _numIndices/3
			) );
	}

	void Context::flip()
	{
		s_renderCtx.flip();
	}

	void Context::rendererInit()
	{
		s_renderCtx.init();
	}

	void Context::rendererShutdown()
	{
		s_renderCtx.shutdown();
	}

	void Context::rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data);
	}

	void Context::rendererDestroyIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateTransientIndexBuffer(IndexBufferHandle _handle, uint32_t _size)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_size, NULL);
	}

	void Context::rendererDestroyTransientIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl)
	{
		s_renderCtx.m_vertexDecls[_handle.idx].create(_decl);
	}

	void Context::rendererDestroyVertexDecl(VertexDeclHandle _handle)
	{
		s_renderCtx.m_vertexDecls[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle);
	}

	void Context::rendererDestroyVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateTransientVertexBuffer(VertexBufferHandle _handle, uint32_t _size)
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
	}

	void Context::rendererDestroyTransientVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexShader(VertexShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].create(false, _mem);
	}

	void Context::rendererDestroyVertexShader(VertexShaderHandle _handle)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateFragmentShader(FragmentShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].create(true, _mem);
	}

	void Context::rendererDestroyFragmentShader(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateMaterial(MaterialHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		s_renderCtx.m_materials[_handle.idx].create(s_renderCtx.m_vertexShaders[_vsh.idx], s_renderCtx.m_fragmentShaders[_fsh.idx]);
	}

	void Context::rendererDestroyMaterial(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_materials[_handle.idx].destroy();
	}

	void Context::rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags)
	{
		s_renderCtx.m_textures[_handle.idx].create(_mem, _flags);
	}

	void Context::rendererDestroyTexture(TextureHandle _handle)
	{
		s_renderCtx.m_textures[_handle.idx].destroy();
	}

	void Context::rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		s_renderCtx.m_renderTargets[_handle.idx].create(_width, _height, _flags, _textureFlags);
	}

	void Context::rendererDestroyRenderTarget(RenderTargetHandle _handle)
	{
		s_renderCtx.m_renderTargets[_handle.idx].destroy();
	}

	void Context::rendererCreateUniform(UniformHandle _handle, ConstantType::Enum _type, uint16_t _num, const char* _name)
	{
		uint32_t size = BX_ALIGN_16(g_constantTypeSize[_type]*_num);
		void* data = g_realloc(NULL, size);
		s_renderCtx.m_uniforms[_handle.idx] = data;
		s_renderCtx.m_uniformReg.reg(_name, s_renderCtx.m_uniforms[_handle.idx]);
	}

	void Context::rendererDestroyUniform(UniformHandle _handle)
	{
		g_free(s_renderCtx.m_uniforms[_handle.idx]);
	}

	void Context::rendererSaveScreenShot(Memory* _mem)
	{
		s_renderCtx.saveScreenShot(_mem);
	}

	void Context::rendererUpdateUniform(uint16_t _loc, const void* _data, uint32_t _size)
	{
		memcpy(s_renderCtx.m_uniforms[_loc], _data, _size);
	}

	void Context::rendererSubmit()
	{
		PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), "rendererSubmit");

		s_renderCtx.updateResolution(m_render->m_resolution);

		s_renderCtx.m_device->BeginScene();

		if (0 < m_render->m_iboffset)
		{
			TransientIndexBuffer* ib = m_render->m_transientIb;
			s_renderCtx.m_indexBuffers[ib->handle.idx].update(m_render->m_iboffset, ib->data);
		}

		if (0 < m_render->m_vboffset)
		{
			TransientVertexBuffer* vb = m_render->m_transientVb;
			s_renderCtx.m_vertexBuffers[vb->handle.idx].update(m_render->m_vboffset, vb->data);
		}

		m_render->sort();

		RenderState currentState;
		currentState.reset();
		currentState.m_flags = BGFX_STATE_NONE;

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			matrix_mul(viewProj[ii].val, m_render->m_view[ii].val, m_render->m_proj[ii].val);
		}

		DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_FILLMODE, m_render->m_debug&BGFX_DEBUG_WIREFRAME ? D3DFILL_WIREFRAME : D3DFILL_SOLID) );
		uint16_t materialIdx = bgfx::invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		float alphaRef = 0.0f;
		D3DPRIMITIVETYPE primType = D3DPT_TRIANGLELIST;
		uint32_t primNumVerts = 3;

		uint32_t statsNumPrims = 0;
		uint32_t statsNumIndices = 0;

		int64_t elapsed = -bx::getHPCounter();

		if (0 == (m_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = m_render->m_num; item < numItems; ++item)
			{
				key.decode(m_render->m_sortKeys[item]);
				const RenderState& state = m_render->m_renderState[m_render->m_sortValues[item] ];

				const uint64_t newFlags = state.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ state.m_flags;
				currentState.m_flags = newFlags;

				if (key.m_view != view)
				{
					currentState.clear();
					changedFlags = BGFX_STATE_MASK;
					currentState.m_flags = newFlags;

					PIX_ENDEVENT();
					PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), "view");

					view = key.m_view;
					materialIdx = bgfx::invalidHandle;

					if (m_render->m_rt[view].idx != rt.idx)
					{
						rt = m_render->m_rt[view];
						s_renderCtx.setRenderTarget(rt);
					}

					Rect& rect = m_render->m_rect[view];

					D3DVIEWPORT9 vp;
					vp.X = rect.m_x;
					vp.Y = rect.m_y;
					vp.Width = rect.m_width;
					vp.Height = rect.m_height;
					vp.MinZ = 0.0f;
					vp.MaxZ = 1.0f;
					DX_CHECK(s_renderCtx.m_device->SetViewport(&vp) );

					Clear& clear = m_render->m_clear[view];

					if (BGFX_CLEAR_NONE != clear.m_flags)
					{
						D3DCOLOR color;
						DWORD flags = 0;

						if (BGFX_CLEAR_COLOR_BIT & clear.m_flags)
						{
							flags |= D3DCLEAR_TARGET;
							uint32_t rgba = clear.m_rgba;
							color = D3DCOLOR_RGBA(rgba>>24, (rgba>>16)&0xff, (rgba>>8)&0xff, rgba&0xff);
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA) );
						}

						if (BGFX_CLEAR_DEPTH_BIT & clear.m_flags)
						{
							flags |= D3DCLEAR_ZBUFFER;
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE) );
						}

						if (BGFX_CLEAR_STENCIL_BIT & clear.m_flags)
						{
							flags |= D3DCLEAR_STENCIL;
						}

						if (0 != flags)
						{
							RECT rc;
							rc.left = rect.m_x;
							rc.top = rect.m_y;
							rc.right = rect.m_x + rect.m_width;
							rc.bottom = rect.m_y + rect.m_height;
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE) );
							DX_CHECK(s_renderCtx.m_device->SetScissorRect(&rc) );
							DX_CHECK(s_renderCtx.m_device->Clear(0, NULL, flags, color, clear.m_depth, clear.m_stencil) );
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE) );
						}
					}

 					DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZENABLE, TRUE) );
					DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS) );
					DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
					DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
					DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );
				}

				if ( (BGFX_STATE_CULL_MASK|BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK
					 |BGFX_STATE_ALPHA_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE
					 |BGFX_STATE_BLEND_MASK|BGFX_STATE_ALPHA_REF_MASK|BGFX_STATE_PT_MASK
					 |BGFX_STATE_POINT_SIZE_MASK|BGFX_STATE_SRGBWRITE|BGFX_STATE_MSAA) & changedFlags)
				{
					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						uint32_t cull = (newFlags&BGFX_STATE_CULL_MASK)>>BGFX_STATE_CULL_SHIFT;
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_CULLMODE, s_cullMode[cull]) );
					}

					if (BGFX_STATE_DEPTH_WRITE & changedFlags)
					{ 
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZWRITEENABLE, !!(BGFX_STATE_DEPTH_WRITE & newFlags) ) );
					}

					if (BGFX_STATE_DEPTH_TEST_MASK & changedFlags)
					{
						uint32_t func = (newFlags&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZENABLE, 0 != func) );

						if (0 != func)
						{
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ZFUNC, s_depthFunc[func]) );
						}
					}

					if ( (BGFX_STATE_ALPHA_TEST|BGFX_STATE_ALPHA_REF_MASK) & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						alphaRef = ref/255.0f;
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHAREF, ref) );
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHATESTENABLE, !!(BGFX_STATE_ALPHA_TEST & newFlags) ) );
					}

					if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
					{
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_POINTSIZE, castfi( (float)( (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) ) ) );
					}

#if BX_PLATFORM_WINDOWS
					if (BGFX_STATE_SRGBWRITE & changedFlags)
					{
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SRGBWRITEENABLE, (newFlags&BGFX_STATE_SRGBWRITE) == BGFX_STATE_SRGBWRITE) );
					}
#endif // BX_PLATFORM_WINDOWS

					if (BGFX_STATE_MSAA & changedFlags)
					{
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, (newFlags&BGFX_STATE_MSAA) == BGFX_STATE_MSAA) );
					}

					if ( (BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE) & changedFlags)
					{
						uint32_t writeEnable = (newFlags&BGFX_STATE_ALPHA_WRITE) ? D3DCOLORWRITEENABLE_ALPHA : 0;
 						writeEnable |= (newFlags&BGFX_STATE_RGB_WRITE) ? D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE : 0;
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_COLORWRITEENABLE, writeEnable) );
					}

					if (BGFX_STATE_BLEND_MASK & changedFlags)
					{
						bool alphaBlendEnabled = !!(BGFX_STATE_BLEND_MASK & newFlags);
						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlendEnabled) );
//						DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, alphaBlendEnabled) );

						if (alphaBlendEnabled)
						{
							uint32_t blend = (newFlags&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT;
							uint32_t src = blend&0xf;
							uint32_t dst = (blend>>4)&0xf;

 							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SRCBLEND, s_blendFactor[src]) );
							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_DESTBLEND, s_blendFactor[dst]) );
//							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_SRCALPHA) );
//							DX_CHECK(s_renderCtx.m_device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA) );
						}
					}

					uint8_t primIndex = uint8_t( (newFlags&BGFX_STATE_PT_MASK)>>BGFX_STATE_PT_SHIFT);
					primType = s_primType[primIndex];
					primNumVerts = s_primNumVerts[primIndex];
				}

				bool materialChanged = false;
				bool constantsChanged = state.m_constBegin < state.m_constEnd;
				rendererUpdateUniforms(m_render->m_constantBuffer, state.m_constBegin, state.m_constEnd);

				if (key.m_material != materialIdx)
				{
					materialIdx = key.m_material;

					if (bgfx::invalidHandle == materialIdx)
					{
						s_renderCtx.m_device->SetVertexShader(NULL);
						s_renderCtx.m_device->SetPixelShader(NULL);
					}
					else
					{
						Material& material = s_renderCtx.m_materials[materialIdx];
						s_renderCtx.m_device->SetVertexShader( (IDirect3DVertexShader9*)material.m_vsh->m_ptr);
						s_renderCtx.m_device->SetPixelShader( (IDirect3DPixelShader9*)material.m_fsh->m_ptr);
					}

					materialChanged = 
						constantsChanged = true;
				}

				if (bgfx::invalidHandle != materialIdx)
				{
					Material& material = s_renderCtx.m_materials[materialIdx];

					if (constantsChanged)
					{
						Material& material = s_renderCtx.m_materials[materialIdx];
						material.m_vsh->m_constantBuffer->commit(materialChanged);
						material.m_fsh->m_constantBuffer->commit(materialChanged);
					}

					for (uint32_t ii = 0, num = material.m_numPredefined; ii < num; ++ii)
					{
						PredefinedUniform& predefined = material.m_predefined[ii];
						uint8_t flags = predefined.m_type&BGFX_UNIFORM_FRAGMENTBIT;
						switch (predefined.m_type&(~BGFX_UNIFORM_FRAGMENTBIT) )
						{
						case PredefinedUniform::ViewRect:
							{
								float rect[4];
								rect[0] = m_render->m_rect[view].m_x;
								rect[1] = m_render->m_rect[view].m_y;
								rect[2] = m_render->m_rect[view].m_width;
								rect[3] = m_render->m_rect[view].m_height;

								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::ViewTexel:
							{
								float rect[4];
								rect[0] = 1.0f/float(m_render->m_rect[view].m_width);
								rect[1] = 1.0f/float(m_render->m_rect[view].m_height);

								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, &rect[0], 1);
							}
							break;

						case PredefinedUniform::View:
							{
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, m_render->m_view[view].val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ViewProj:
							{
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, viewProj[view].val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::Model:
							{
 								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, model.val, uint32_min(state.m_num*4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProj:
							{
								Matrix4 modelViewProj;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								matrix_mul(modelViewProj.val, model.val, viewProj[view].val);
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, modelViewProj.val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProjX:
							{
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];

								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								matrix_mul(viewProjBias.val, viewProj[other].val, s_bias);

								Matrix4 modelViewProj;
								matrix_mul(modelViewProj.val, model.val, viewProjBias.val);

								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, modelViewProj.val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ViewProjX:
							{
								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								matrix_mul(viewProjBias.val, viewProj[other].val, s_bias);

								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, viewProjBias.val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::AlphaRef:
							{
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, &alphaRef, 1);
							}
							break;

						default:
							BX_CHECK(false, "predefined %d not handled", predefined.m_type);
							break;
						}
					}
				}

//				if (BGFX_STATE_TEX_MASK & changedFlags)
				{
					uint64_t flag = BGFX_STATE_TEX0;
					for (uint32_t stage = 0; stage < BGFX_STATE_TEX_COUNT; ++stage)
					{
						const Sampler& sampler = state.m_sampler[stage];
						Sampler& current = currentState.m_sampler[stage];
						if (current.m_idx != sampler.m_idx
						||  current.m_flags != sampler.m_flags
						||  materialChanged)
						{
							if (bgfx::invalidHandle != sampler.m_idx)
							{
								switch (sampler.m_flags&BGFX_SAMPLER_TYPE_MASK)
								{
								case BGFX_SAMPLER_TEXTURE:
									s_renderCtx.m_textures[sampler.m_idx].commit(stage);
									break;

								case BGFX_SAMPLER_RENDERTARGET_COLOR:
									s_renderCtx.m_renderTargets[sampler.m_idx].commit(stage);
									break;

								case BGFX_SAMPLER_RENDERTARGET_DEPTH:
//									id = s_renderCtx.m_renderTargets[sampler.m_idx].m_depth.m_id;
									break;
								}
							}
							else
							{
								DX_CHECK(s_renderCtx.m_device->SetTexture(stage, NULL) );
							}
						}

						current = sampler;
						flag <<= 1;
					}
				}

				if (currentState.m_vertexBuffer.idx != state.m_vertexBuffer.idx || materialChanged)
				{
					currentState.m_vertexBuffer = state.m_vertexBuffer;

					uint16_t handle = state.m_vertexBuffer.idx;
					if (bgfx::invalidHandle != handle)
					{
						VertexBuffer& vb = s_renderCtx.m_vertexBuffers[handle];

						uint16_t decl = vb.m_decl.idx == bgfx::invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						DX_CHECK(s_renderCtx.m_device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );
						DX_CHECK(s_renderCtx.m_device->SetVertexDeclaration(vertexDecl.m_ptr) );
					}
					else
					{
						DX_CHECK(s_renderCtx.m_device->SetStreamSource(0, NULL, 0, 0) );
					}
				}

				if (currentState.m_indexBuffer.idx != state.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = state.m_indexBuffer;

					uint16_t handle = state.m_indexBuffer.idx;
					if (bgfx::invalidHandle != handle)
					{
						IndexBuffer& ib = s_renderCtx.m_indexBuffers[handle];
						DX_CHECK(s_renderCtx.m_device->SetIndices(ib.m_ptr) );
					}
					else
					{
						DX_CHECK(s_renderCtx.m_device->SetIndices(NULL) );
					}
				}

				if (bgfx::invalidHandle != currentState.m_vertexBuffer.idx)
				{
					uint32_t numVertices = state.m_numVertices;
					if (UINT32_C(0xffffffff) == numVertices)
					{
						VertexBuffer& vb = s_renderCtx.m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = vb.m_decl.idx == bgfx::invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_decl.m_stride;
					}

					uint32_t numIndices = 0;
					uint32_t numPrims = 0;

					if (bgfx::invalidHandle != state.m_indexBuffer.idx)
					{
						if (BGFX_DRAW_WHOLE_INDEX_BUFFER == state.m_startIndex)
						{
							numIndices = s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2;
							numPrims = numIndices/primNumVerts;

							DX_CHECK(s_renderCtx.m_device->DrawIndexedPrimitive(primType
								, state.m_startVertex
								, 0
								, numVertices
								, 0
								, numPrims
								) );
						}
						else if (primNumVerts <= state.m_numIndices)
						{
							numIndices = state.m_numIndices;
							numPrims = numIndices/primNumVerts;

							DX_CHECK(s_renderCtx.m_device->DrawIndexedPrimitive(primType
								, state.m_startVertex
								, 0
								, numVertices
								, state.m_startIndex
								, numPrims
								) );
						}
					}
					else
					{
						numPrims = numVertices/primNumVerts;
						DX_CHECK(s_renderCtx.m_device->DrawPrimitive(primType
							, state.m_startVertex
							, numPrims
							) );
					}

					statsNumPrims += numPrims;
					statsNumIndices += numIndices;
				}
			}

			PIX_ENDEVENT();
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;
		int64_t frameTime = now - last;
		last = now;

		if (m_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), "debugstats");

			TextVideoMem& tvm = s_renderCtx.m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 10;
				tvm.printf(10, pos++, 0x8e, "      Frame: %3.4f [ms] / %3.2f", frameTime*toMs, freq/frameTime);
				tvm.printf(10, pos++, 0x8e, " Draw calls: %4d / %3.4f [ms]", m_render->m_num, elapsed*toMs);
				tvm.printf(10, pos++, 0x8e, "      Prims: %7d", statsNumPrims);
				tvm.printf(10, pos++, 0x8e, "    Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "   DVB size: %7d", m_render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "   DIB size: %7d", m_render->m_iboffset);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = m_render->m_waitSubmit < m_render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], "Submit wait: %3.4f [ms]", m_render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], "Render wait: %3.4f [ms]", m_render->m_waitRender*toMs);
			}

			g_textVideoMemBlitter.blit(tvm);

			PIX_ENDEVENT();
		}
		else if (m_render->m_debug & BGFX_DEBUG_TEXT)
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), "debugtext");

			g_textVideoMemBlitter.blit(m_render->m_textVideoMem);

			PIX_ENDEVENT();
		}

		s_renderCtx.m_device->EndScene();
	}
}

#endif // BGFX_CONFIG_RENDERER_DIRECT3D

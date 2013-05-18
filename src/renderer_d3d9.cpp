/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D9
#	include "renderer_d3d9.h"

namespace bgfx
{
	static const D3DPRIMITIVETYPE s_primType[] =
	{
		D3DPT_TRIANGLELIST,
		D3DPT_LINELIST,
		D3DPT_POINTLIST,
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

	struct Blend
	{
		D3DBLEND m_src;
		D3DBLEND m_dst;
		bool m_factor;
	};

	static const Blend s_blendFactor[] =
	{
		{ (D3DBLEND)0,             (D3DBLEND)0,             false }, // ignored
		{ D3DBLEND_ZERO,           D3DBLEND_ZERO,           false },
		{ D3DBLEND_ONE,            D3DBLEND_ONE,            false },
		{ D3DBLEND_SRCCOLOR,       D3DBLEND_SRCCOLOR,       false },
		{ D3DBLEND_INVSRCCOLOR,    D3DBLEND_INVSRCCOLOR,    false },
		{ D3DBLEND_SRCALPHA,       D3DBLEND_SRCALPHA,       false },
		{ D3DBLEND_INVSRCALPHA,    D3DBLEND_INVSRCALPHA,    false },
		{ D3DBLEND_DESTALPHA,      D3DBLEND_DESTALPHA,      false },
		{ D3DBLEND_INVDESTALPHA,   D3DBLEND_INVDESTALPHA,   false },
		{ D3DBLEND_DESTCOLOR,      D3DBLEND_DESTCOLOR,      false },
		{ D3DBLEND_INVDESTCOLOR,   D3DBLEND_INVDESTCOLOR,   false },
		{ D3DBLEND_SRCALPHASAT,    D3DBLEND_ONE,            false },
		{ D3DBLEND_BLENDFACTOR,    D3DBLEND_BLENDFACTOR,    true  },
		{ D3DBLEND_INVBLENDFACTOR, D3DBLEND_INVBLENDFACTOR, true  },
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

	static const D3DCMPFUNC s_stencilFunc[] =
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

	static const D3DSTENCILOP s_stencilOp[] =
	{
		D3DSTENCILOP_ZERO,
		D3DSTENCILOP_KEEP,
		D3DSTENCILOP_REPLACE,
		D3DSTENCILOP_INCR,
		D3DSTENCILOP_INCRSAT,
		D3DSTENCILOP_DECR,
		D3DSTENCILOP_DECRSAT,
		D3DSTENCILOP_INVERT,
	};

	static const D3DRENDERSTATETYPE s_stencilFuncRs[] =
	{
		D3DRS_STENCILFUNC,
		D3DRS_CCW_STENCILFUNC,
	};

	static const D3DRENDERSTATETYPE s_stencilFailRs[] =
	{
		D3DRS_STENCILFAIL,
		D3DRS_CCW_STENCILFAIL,
	};

	static const D3DRENDERSTATETYPE s_stencilZFailRs[] =
	{
		D3DRS_STENCILZFAIL,
		D3DRS_CCW_STENCILZFAIL,
	};

	static const D3DRENDERSTATETYPE s_stencilZPassRs[] =
	{
		D3DRS_STENCILPASS,
		D3DRS_CCW_STENCILPASS,
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
		D3DFMT_A2B10G10R10,
		D3DFMT_A16B16G16R16,
		D3DFMT_A16B16G16R16F,
		D3DFMT_R16F,
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
		{ D3DFMT_DXT1,           4 },
		{ D3DFMT_DXT3,           8 },
		{ D3DFMT_DXT5,           8 },
		{ D3DFMT_ATI1,           4 },
		{ D3DFMT_ATI2,           8 },
		{ D3DFMT_UNKNOWN,        0 },
		{ D3DFMT_L8,             8 },
		{ D3DFMT_X8R8G8B8,      32 },
		{ D3DFMT_A8R8G8B8,      32 },
		{ D3DFMT_A16B16G16R16,  64 },
		{ D3DFMT_A16B16G16R16F, 64 },
		{ D3DFMT_R5G6B5,        16 },
		{ D3DFMT_A4R4G4B4,      16 },
		{ D3DFMT_A1R5G5B5,      16 },
		{ D3DFMT_A2B10G10R10,   32 },
	};

	static ExtendedFormat s_extendedFormats[ExtendedFormat::Count] =
	{
		{ D3DFMT_ATI1, 0,                     D3DRTYPE_TEXTURE, false },
		{ D3DFMT_ATI2, 0,                     D3DRTYPE_TEXTURE, false },
		{ D3DFMT_DF16, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, false },
		{ D3DFMT_DF24, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, false },
		{ D3DFMT_INST, 0,                     D3DRTYPE_SURFACE, false },
		{ D3DFMT_INTZ, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, false },
		{ D3DFMT_NULL, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, false },
		{ D3DFMT_RESZ, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, false },
		{ D3DFMT_RAWZ, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, false },
	};

	struct RendererContext
	{
		RendererContext()
			: m_flags(BGFX_RESET_NONE)
			, m_initialized(false)
			, m_amd(false)
			, m_nvidia(false)
			, m_instancing(false)
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
			BGFX_FATAL(NULL != m_d3d9dll, Fatal::UnableToInitialize, "Failed to load d3d9.dll.");

			m_D3DPERF_SetMarker = (D3DPERF_SetMarkerFunc)GetProcAddress(m_d3d9dll, "D3DPERF_SetMarker");
			m_D3DPERF_BeginEvent = (D3DPERF_BeginEventFunc)GetProcAddress(m_d3d9dll, "D3DPERF_BeginEvent");
			m_D3DPERF_EndEvent = (D3DPERF_EndEventFunc)GetProcAddress(m_d3d9dll, "D3DPERF_EndEvent");

#if BGFX_CONFIG_RENDERER_DIRECT3D9EX
			Direct3DCreate9ExFn direct3DCreate9Ex = (Direct3DCreate9ExFn)GetProcAddress(m_d3d9dll, "Direct3DCreate9Ex");
			BGFX_FATAL(NULL != direct3DCreate9Ex, Fatal::UnableToInitialize, "Function Direct3DCreate9Ex not found.");
			direct3DCreate9Ex(D3D_SDK_VERSION, &m_d3d9);
#else
			Direct3DCreate9Fn direct3DCreate9 = (Direct3DCreate9Fn)GetProcAddress(m_d3d9dll, "Direct3DCreate9");
			BGFX_FATAL(NULL != direct3DCreate9, Fatal::UnableToInitialize, "Function Direct3DCreate9 not found.");
			m_d3d9 = direct3DCreate9(D3D_SDK_VERSION);
#endif // defined(D3D_DISABLE_9EX)

			BGFX_FATAL(m_d3d9, Fatal::UnableToInitialize, "Unable to create Direct3D.");

			m_adapter = D3DADAPTER_DEFAULT;
			m_deviceType = D3DDEVTYPE_HAL;

			uint32_t adapterCount = m_d3d9->GetAdapterCount();
			for (uint32_t ii = 0; ii < adapterCount; ++ii)
			{
				D3DADAPTER_IDENTIFIER9 identifier;
				HRESULT hr = m_d3d9->GetAdapterIdentifier(ii, 0, &identifier);
				if (SUCCEEDED(hr) )
				{
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
			}

			DX_CHECK(m_d3d9->GetAdapterIdentifier(m_adapter, 0, &m_identifier) );
			m_amd = m_identifier.VendorId == 0x1002;
			m_nvidia = m_identifier.VendorId == 0x10de;

			uint32_t behaviorFlags[] =
			{
				D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE,
				D3DCREATE_MIXED_VERTEXPROCESSING,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			};

			for (uint32_t ii = 0; ii < countof(behaviorFlags) && NULL == m_device; ++ii)
			{
#if BGFX_CONFIG_RENDERER_DIRECT3D9EX
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
#endif // BGFX_CONFIG_RENDERER_DIRECT3D9EX
			}

			BGFX_FATAL(m_device, Fatal::UnableToInitialize, "Unable to create Direct3D9 device.");

			DX_CHECK(m_device->GetDeviceCaps(&m_caps) );

			// For shit GPUs that can create DX9 device but can't do simple stuff. GTFO!
			BGFX_FATAL( (D3DPTEXTURECAPS_SQUAREONLY & m_caps.TextureCaps) == 0, Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_SQUAREONLY");
			BGFX_FATAL( (D3DPTEXTURECAPS_MIPMAP & m_caps.TextureCaps) == D3DPTEXTURECAPS_MIPMAP, Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_MIPMAP");
			BGFX_FATAL( (D3DPTEXTURECAPS_ALPHA & m_caps.TextureCaps) == D3DPTEXTURECAPS_ALPHA, Fatal::MinimumRequiredSpecs, "D3DPTEXTURECAPS_ALPHA");
			BGFX_FATAL(m_caps.VertexShaderVersion >= D3DVS_VERSION(2, 0) && m_caps.PixelShaderVersion >= D3DPS_VERSION(2, 1)
					  , Fatal::MinimumRequiredSpecs
					  , "Shader Model Version (vs: %x, ps: %x)."
					  , m_caps.VertexShaderVersion
					  , m_caps.PixelShaderVersion
					  );
			BGFX_FATAL(m_caps.MaxTextureWidth >= 2048 && m_caps.MaxTextureHeight >= 2048
					  , Fatal::MinimumRequiredSpecs
					  , "Maximum texture size is below 2048 (w: %d, h: %d)."
					  , m_caps.MaxTextureWidth
					  , m_caps.MaxTextureHeight
					  );

			BX_TRACE("Max vertex shader 3.0 instr. slots: %d", m_caps.MaxVertexShader30InstructionSlots);
			BX_TRACE("Max vertex shader constants: %d", m_caps.MaxVertexShaderConst);
			BX_TRACE("Max fragment shader 2.0 instr. slots: %d", m_caps.PS20Caps.NumInstructionSlots);
			BX_TRACE("Max fragment shader 3.0 instr. slots: %d", m_caps.MaxPixelShader30InstructionSlots);

			BX_TRACE("Extended formats:");
			for (uint32_t ii = 0; ii < ExtendedFormat::Count; ++ii)
			{
				ExtendedFormat& fmt = s_extendedFormats[ii];
				fmt.m_supported = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, fmt.m_usage, fmt.m_type, fmt.m_fmt) );
				const char* fourcc = (const char*)&fmt.m_fmt;
				BX_TRACE("\t%2d: %c%c%c%c %s", ii, fourcc[0], fourcc[1], fourcc[2], fourcc[3], fmt.m_supported ? "supported" : "");
				BX_UNUSED(fourcc);
			}

			m_instancing = false
				|| s_extendedFormats[ExtendedFormat::Inst].m_supported
				|| (m_caps.VertexShaderVersion >= D3DVS_VERSION(3, 0) )
				;

			if (m_amd
			&&  s_extendedFormats[ExtendedFormat::Inst].m_supported)
			{
				// AMD only
				m_device->SetRenderState(D3DRS_POINTSIZE, D3DFMT_INST);
			}

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

			for (uint32_t ii = 0; ii < countof(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_vertexShaders); ++ii)
			{
				m_vertexShaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_fragmentShaders); ++ii)
			{
				m_fragmentShaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_vertexDecls); ++ii)
			{
				m_vertexDecls[ii].destroy();
			}

			for (uint32_t ii = 0; ii < countof(m_renderTargets); ++ii)
			{
				m_renderTargets[ii].destroy();
			}

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
#if BGFX_CONFIG_RENDERER_DIRECT3D9EX
				DX_CHECK(m_device->WaitForVBlank(0) );
#endif // BGFX_CONFIG_RENDERER_DIRECT3D9EX

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

			capturePreReset();

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

			capturePostReset();

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

		void capturePreReset()
		{
			if (NULL != m_captureSurface)
			{
				g_callback->captureEnd();
			}
			DX_RELEASE(m_captureSurface, 1);
			DX_RELEASE(m_captureTexture, 0);
			DX_RELEASE(m_captureResolve, 0);
		}

		void capturePostReset()
		{
			if (m_flags&BGFX_RESET_CAPTURE)
			{
				uint32_t width = m_params.BackBufferWidth;
				uint32_t height = m_params.BackBufferHeight;
				D3DFORMAT fmt = m_params.BackBufferFormat;

				DX_CHECK(m_device->CreateTexture(width
					, height
					, 1
					, 0
					, fmt
					, D3DPOOL_SYSTEMMEM
					, &m_captureTexture
					, NULL
					) );

				DX_CHECK(m_captureTexture->GetSurfaceLevel(0
					, &m_captureSurface
					) );

				if (m_params.MultiSampleType != D3DMULTISAMPLE_NONE)
				{
					DX_CHECK(m_device->CreateRenderTarget(width
						, height
						, fmt
						, D3DMULTISAMPLE_NONE
						, 0
						, false
						, &m_captureResolve
						, NULL
						) );
				}

				g_callback->captureBegin(width, height, width*4, TextureFormat::BGRA8, false);
			}
		}

		void capture()
		{
			if (NULL != m_captureSurface)
			{
				IDirect3DSurface9* resolve = m_backBufferColor;

				if (NULL != m_captureResolve)
				{
					resolve = m_captureResolve;
					DX_CHECK(m_device->StretchRect(m_backBufferColor
						, 0
						, m_captureResolve
						, NULL
						, D3DTEXF_NONE
						) );
				}

				HRESULT hr = m_device->GetRenderTargetData(resolve, m_captureSurface);
				if (SUCCEEDED(hr) )
				{
					D3DLOCKED_RECT rect;
					DX_CHECK(m_captureSurface->LockRect(&rect
						, NULL
						, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY
						) );

					g_callback->captureFrame(rect.pBits, m_params.BackBufferHeight*rect.Pitch);

					DX_CHECK(m_captureSurface->UnlockRect() );
				}
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
			uint32_t bytesPerPixel = rect.Pitch/dm.Width;

			g_callback->screenShot( (const char*)_mem->data
				, m_params.BackBufferWidth
				, m_params.BackBufferHeight
				, rect.Pitch
				, &data[point.y*rect.Pitch+point.x*bytesPerPixel]
				, m_params.BackBufferHeight*rect.Pitch
				, false
				);

			DX_CHECK(surface->UnlockRect() );
			DX_RELEASE(surface, 0);
#endif // BX_PLATFORM_WINDOWS
		}

#if BX_PLATFORM_WINDOWS
		D3DCAPS9 m_caps;

		D3DPERF_SetMarkerFunc m_D3DPERF_SetMarker;
		D3DPERF_BeginEventFunc m_D3DPERF_BeginEvent;
		D3DPERF_EndEventFunc m_D3DPERF_EndEvent;
#endif // BX_PLATFORM_WINDOWS

#if BGFX_CONFIG_RENDERER_DIRECT3D9EX
		IDirect3D9Ex* m_d3d9;
		IDirect3DDevice9Ex* m_device;
#else
		IDirect3D9* m_d3d9;
		IDirect3DDevice9* m_device;
#endif // BGFX_CONFIG_RENDERER_DIRECT3D9EX

		IDirect3DSurface9* m_backBufferColor;
		IDirect3DSurface9* m_backBufferDepthStencil;

		IDirect3DTexture9* m_captureTexture;
		IDirect3DSurface9* m_captureSurface;
		IDirect3DSurface9* m_captureResolve;

		IDirect3DVertexDeclaration9* m_instanceDataDecls[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

		HMODULE m_d3d9dll;
		uint32_t m_adapter;
		D3DDEVTYPE m_deviceType;
		D3DPRESENT_PARAMETERS m_params;
		uint32_t m_flags;
		D3DADAPTER_IDENTIFIER9 m_identifier;

		bool m_initialized;
		bool m_amd;
		bool m_nvidia;
		bool m_instancing;

		D3DFORMAT m_fmtDepth;

		IndexBuffer m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		Shader m_vertexShaders[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		Shader m_fragmentShaders[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		Program m_program[BGFX_CONFIG_MAX_PROGRAMS];
		Texture m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDeclaration m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		RenderTarget m_renderTargets[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		Texture* m_updateTexture;
		uint8_t* m_updateTextureBits;
		uint32_t m_updateTexturePitch;
		uint8_t m_updateTextureSide;
		uint8_t m_updateTextureMip;

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
			update(0, _size, _data);
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
			update(0, _size, _data);
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
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,       0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,      0 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        0 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        1 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,  0 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     0 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     1 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     2 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     3 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     4 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     5 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     6 },
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,     7 },
		D3DDECL_END()
	};

	static const D3DDECLTYPE s_attribType[AttribType::Count][4][2] =
	{
		{
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
		},
		{
			{ D3DDECLTYPE_SHORT2,    D3DDECLTYPE_SHORT2N   },
			{ D3DDECLTYPE_SHORT2,    D3DDECLTYPE_SHORT2N   },
			{ D3DDECLTYPE_SHORT4,    D3DDECLTYPE_SHORT4N   },
			{ D3DDECLTYPE_SHORT4,    D3DDECLTYPE_SHORT4N   },
		},
		{
			{ D3DDECLTYPE_FLOAT16_2, D3DDECLTYPE_FLOAT16_2 },
			{ D3DDECLTYPE_FLOAT16_2, D3DDECLTYPE_FLOAT16_2 },
			{ D3DDECLTYPE_FLOAT16_4, D3DDECLTYPE_FLOAT16_4 },
			{ D3DDECLTYPE_FLOAT16_4, D3DDECLTYPE_FLOAT16_4 },
		},
		{
			{ D3DDECLTYPE_FLOAT1,    D3DDECLTYPE_FLOAT1    },
			{ D3DDECLTYPE_FLOAT2,    D3DDECLTYPE_FLOAT2    },
			{ D3DDECLTYPE_FLOAT3,    D3DDECLTYPE_FLOAT3    },
			{ D3DDECLTYPE_FLOAT4,    D3DDECLTYPE_FLOAT4    },
		},
	};

	static D3DVERTEXELEMENT9* fillVertexDecl(D3DVERTEXELEMENT9* _out, const VertexDecl& _decl)
	{
		D3DVERTEXELEMENT9* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (0xff != _decl.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				bool asInt;
				_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);

				memcpy(elem, &s_attrib[attr], sizeof(D3DVERTEXELEMENT9) );

				elem->Type = s_attribType[type][num-1][normalized];
				elem->Offset = _decl.m_offset[attr];
				++elem;
			}
		}

		return elem;
	}

	static IDirect3DVertexDeclaration9* createVertexDecl(const VertexDecl& _decl, uint8_t _numInstanceData)
	{
		D3DVERTEXELEMENT9 vertexElements[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
		D3DVERTEXELEMENT9* elem = fillVertexDecl(vertexElements, _decl);

		const D3DVERTEXELEMENT9 inst = { 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };

		for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
		{
			memcpy(elem, &inst, sizeof(D3DVERTEXELEMENT9) );
			elem->UsageIndex = 8-_numInstanceData+ii;
			elem->Offset = ii*16;
			++elem;
		}

		memcpy(elem, &s_attrib[Attrib::Count], sizeof(D3DVERTEXELEMENT9) );

		IDirect3DVertexDeclaration9* ptr;
		DX_CHECK(s_renderCtx.m_device->CreateVertexDeclaration(vertexElements, &ptr) );
		return ptr;
	}

	void VertexDeclaration::create(const VertexDecl& _decl)
	{
		memcpy(&m_decl, &_decl, sizeof(VertexDecl) );
		dump(m_decl);
		m_ptr = createVertexDecl(_decl, 0);
	}

	void Shader::create(bool _fragment, const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		uint32_t iohash;
		bx::read(&reader, iohash);

		uint16_t count;
		bx::read(&reader, count);

		m_numPredefined = 0;

		BX_TRACE("Shader consts %d", count);

		uint8_t fragmentBit = _fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		if (0 < count)
		{
			m_constantBuffer = ConstantBuffer::create(1024);

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize;
				bx::read(&reader, nameSize);

				char name[256];
				bx::read(&reader, &name, nameSize);
				name[nameSize] = '\0';

				uint8_t type;
				bx::read(&reader, type);

				uint8_t num;
				bx::read(&reader, num);

				uint16_t regIndex;
				bx::read(&reader, regIndex);

				uint16_t regCount;
				bx::read(&reader, regCount);

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
						m_constantBuffer->writeUniformRef( (UniformType::Enum)(type|fragmentBit), regIndex, data, regCount);
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
				BX_UNUSED(kind);
			}

			m_constantBuffer->finish();
		}

		uint16_t shaderSize;
		bx::read(&reader, shaderSize);

		const DWORD* code = (const DWORD*)reader.getDataPtr();

		if (_fragment)
		{
			DX_CHECK(s_renderCtx.m_device->CreatePixelShader(code, (IDirect3DPixelShader9**)&m_ptr) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create fragment shader.");
		}
		else
		{
			DX_CHECK(s_renderCtx.m_device->CreateVertexShader(code, (IDirect3DVertexShader9**)&m_ptr) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create vertex shader.");
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
			, &m_texture2d
			, NULL
			) );

		BGFX_FATAL(NULL != m_texture2d, Fatal::UnableToCreateTexture, "Failed to create texture (size: %dx%d, mips: %d, fmt: 0x%08x)."
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
			, &m_texture3d
			, NULL
			) );

		BGFX_FATAL(NULL != m_texture3d, Fatal::UnableToCreateTexture, "Failed to create volume texture (size: %dx%dx%d, mips: %d, fmt: 0x%08x)."
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
			, &m_textureCube
			, NULL
			) );

		BGFX_FATAL(NULL != m_textureCube, Fatal::UnableToCreateTexture, "Failed to create cube texture (edge: %d, mips: %d, fmt: 0x%08x)."
			, _edge
			, _numMips
			, _fmt
			);
	}

	uint8_t* Texture::lock(uint8_t _side, uint8_t _lod, uint32_t& _pitch, uint32_t& _slicePitch, const Rect* _rect)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				D3DLOCKED_RECT lockedRect;

				if (NULL != _rect)
				{
					RECT rect;
					rect.left = _rect->m_x;
					rect.top = _rect->m_y;
					rect.right = rect.left + _rect->m_width;
					rect.bottom = rect.top + _rect->m_height;
					DX_CHECK(m_texture2d->LockRect(_lod, &lockedRect, &rect, 0) );
				}
				else
				{
					DX_CHECK(m_texture2d->LockRect(_lod, &lockedRect, NULL, 0) );
				}

				_pitch = lockedRect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)lockedRect.pBits;
			}

		case Texture3D:
			{
				D3DLOCKED_BOX box;
				DX_CHECK(m_texture3d->LockBox(_lod, &box, NULL, 0) );
				_pitch = box.RowPitch;
				_slicePitch = box.SlicePitch;
				return (uint8_t*)box.pBits;
			}

		case TextureCube:
			{
				D3DLOCKED_RECT lockedRect;

				if (NULL != _rect)
				{
					RECT rect;
					rect.left = _rect->m_x;
					rect.top = _rect->m_y;
					rect.right = rect.left + _rect->m_width;
					rect.bottom = rect.top + _rect->m_height;
					DX_CHECK(m_textureCube->LockRect(D3DCUBEMAP_FACES(_side), _lod, &lockedRect, &rect, 0) );
				}
				else
				{
					DX_CHECK(m_textureCube->LockRect(D3DCUBEMAP_FACES(_side), _lod, &lockedRect, NULL, 0) );
				}

				_pitch = lockedRect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)lockedRect.pBits;
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
				DX_CHECK(m_texture2d->UnlockRect(_lod) );
			}
			return;

		case Texture3D:
			{
				DX_CHECK(m_texture3d->UnlockBox(_lod) );
			}
			return;

		case TextureCube:
			{
				DX_CHECK(m_textureCube->UnlockRect(D3DCUBEMAP_FACES(_side), _lod) );
			}
			return;
		}

		BX_CHECK(false, "You should not be here.");
	}

	void Texture::dirty(uint8_t _side, const Rect& _rect, uint16_t _z, uint16_t _depth)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				RECT rect;
				rect.left = _rect.m_x;
				rect.top = _rect.m_y;
				rect.right = rect.left + _rect.m_width;
				rect.bottom = rect.top + _rect.m_height;
				DX_CHECK(m_texture2d->AddDirtyRect(&rect) );
			}
			return;

		case Texture3D:
			{
				D3DBOX box;
				box.Left = _rect.m_x;
				box.Top = _rect.m_y;
				box.Right = box.Left + _rect.m_width;
				box.Bottom = box.Top + _rect.m_height;
				box.Front = _z;
				box.Back = box.Front + _depth;
				DX_CHECK(m_texture3d->AddDirtyBox(&box) );
			}
			return;

		case TextureCube:
			{
				RECT rect;
				rect.left = _rect.m_x;
				rect.top = _rect.m_y;
				rect.right = rect.left + _rect.m_width;
				rect.bottom = rect.top + _rect.m_height;
				DX_CHECK(m_textureCube->AddDirtyRect(D3DCUBEMAP_FACES(_side), &rect) );
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
			m_format = dds.m_type;
			const TextureFormatInfo& tfi = s_textureFormat[dds.m_type];

			bool decompress = false
				|| (TextureFormat::BC4 == dds.m_type && !s_extendedFormats[ExtendedFormat::Ati1].m_supported)
				|| (TextureFormat::BC5 == dds.m_type && !s_extendedFormats[ExtendedFormat::Ati2].m_supported)
				;

			D3DFORMAT format = decompress ? D3DFMT_A8R8G8B8 : tfi.m_fmt;
			uint8_t bpp = decompress ? 32 : tfi.m_bpp;

			if (dds.m_cubeMap)
			{
				createCubeTexture(dds.m_width, dds.m_numMips, format);
			}
			else if (dds.m_depth > 1)
			{
				createVolumeTexture(dds.m_width, dds.m_height, dds.m_depth, dds.m_numMips, format);
			}
			else
			{
				createTexture(dds.m_width, dds.m_height, dds.m_numMips, format);
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
								uint32_t srcpitch = mip.m_width*bpp/8;

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
				// For BC4 and B5 in DX9 LockRect returns wrong number of
				// bytes. If actual mip size is used it causes memory corruption.
				// http://www.aras-p.info/texts/D3D9GPUHacks.html#3dc
				bool useMipSize = true
						&& dds.m_type != TextureFormat::BC4
						&& dds.m_type != TextureFormat::BC5
						;

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
						if (getRawImageData(dds, 0, lod, _mem, mip) )
						{
							uint32_t pitch;
							uint32_t slicePitch;
							uint8_t* dst = lock(side, lod, pitch, slicePitch);

							uint32_t size = useMipSize ? mip.m_size : width*height*depth*bpp/8;

							memcpy(dst, mip.m_data, size);

							unlock(side, lod);
						}

						width >>= 1;
						height >>= 1;
						depth >>= 1;
					}
				}
			}
		}
		else
		{
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			if (BGFX_CHUNK_MAGIC_TEX == magic)
			{
				TextureCreate tc;
				bx::read(&reader, tc);
				m_format = (TextureFormat::Enum)tc.m_format;

				if (tc.m_cubeMap)
				{
					createCubeTexture(tc.m_width, tc.m_numMips, s_textureFormat[tc.m_format].m_fmt);
				}
				else if (tc.m_depth > 1)
				{
					createVolumeTexture(tc.m_width, tc.m_height, tc.m_depth, tc.m_numMips, s_textureFormat[tc.m_format].m_fmt);
				}
				else
				{
					createTexture(tc.m_width, tc.m_height, tc.m_numMips, s_textureFormat[tc.m_format].m_fmt);
				}

				if (NULL != tc.m_mem)
				{
					uint32_t bpp = s_textureFormat[tc.m_format].m_bpp;
					uint8_t* data = tc.m_mem->data;

					for (uint8_t side = 0, numSides = tc.m_cubeMap ? 6 : 1; side < numSides; ++side)
					{
						uint32_t width = tc.m_width;
						uint32_t height = tc.m_height;
						uint32_t depth = tc.m_depth;

						for (uint32_t lod = 0, num = tc.m_numMips; lod < num; ++lod)
						{
							width = uint32_max(1, width);
							height = uint32_max(1, height);
							depth = uint32_max(1, depth);

							uint32_t pitch;
							uint32_t slicePitch;
							uint8_t* dst = lock(side, lod, pitch, slicePitch);
							uint32_t len = width*height*bpp/8;
							memcpy(dst, data, len);
							data += len;
							unlock(side, lod);

							width >>= 1;
							height >>= 1;
							depth >>= 1;
						}
					}

					release(tc.m_mem);
				}
			}
			else
			{
				//
			}
		}
	}

	void Texture::updateBegin(uint8_t _side, uint8_t _mip)
	{
		uint32_t slicePitch;
		s_renderCtx.m_updateTextureSide = _side;
		s_renderCtx.m_updateTextureMip = _mip;
		s_renderCtx.m_updateTextureBits = lock(_side, _mip, s_renderCtx.m_updateTexturePitch, slicePitch);
	}

	void Texture::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		uint32_t bpp = s_textureFormat[m_format].m_bpp;
		uint32_t srcpitch = _rect.m_width*bpp/8;
		uint32_t dstpitch = s_renderCtx.m_updateTexturePitch;
		uint8_t* bits = s_renderCtx.m_updateTextureBits + _rect.m_y*dstpitch + _rect.m_x*bpp/8;

		if (srcpitch == dstpitch)
		{
			memcpy(bits, _mem->data, srcpitch*_rect.m_height);
		}
		else
		{
			for (uint32_t yy = 0, height = _rect.m_height; yy < height; ++yy)
			{
				uint8_t* src = &_mem->data[yy*srcpitch];
				uint8_t* dst = &bits[yy*dstpitch];
				memcpy(dst, src, srcpitch);
			}
		}

		if (0 == _mip)
		{
			dirty(_side, _rect, _z, _depth);
		}
	}

	void Texture::updateEnd()
	{
		unlock(s_renderCtx.m_updateTextureSide, s_renderCtx.m_updateTextureMip);
	}

	void Texture::commit(uint8_t _stage)
	{
		IDirect3DDevice9* device = s_renderCtx.m_device;
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_MINFILTER, m_minFilter) );
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_MAGFILTER, m_magFilter) );
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_MIPFILTER, m_mipFilter) );
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_ADDRESSU, m_tau) );
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_ADDRESSV, m_tav) );
		if (m_type == Texture3D)
		{
			DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_ADDRESSW, m_taw) );
		}
#if BX_PLATFORM_WINDOWS
		DX_CHECK(device->SetSamplerState(_stage, D3DSAMP_SRGBTEXTURE, m_srgb) );
#endif // BX_PLATFORM_WINDOWS
		DX_CHECK(device->SetTexture(_stage, m_ptr) );
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

				BGFX_FATAL(m_rt, Fatal::UnableToCreateRenderTarget, "Unable to create 1x1 render target.");

				DX_CHECK(s_renderCtx.m_device->CreateTexture(m_width
					, m_height
					, 1
					, D3DUSAGE_DEPTHSTENCIL
					, D3DFMT_DF24 //s_depthFormat[depthFormat]
					, D3DPOOL_DEFAULT
					, &m_depthTexture
					, NULL
					) );

				BGFX_FATAL(m_depthTexture, Fatal::UnableToCreateRenderTarget, "Unable to create depth texture.");

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

					BGFX_FATAL(m_rt, Fatal::UnableToCreateRenderTarget, "Unable to create MSAA render target.");
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

					BGFX_FATAL(m_colorTexture, Fatal::UnableToCreateRenderTarget, "Unable to create color render target.");

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

					BGFX_FATAL(m_depth, Fatal::UnableToCreateRenderTarget, "Unable to create depth stencil surface.");
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

	void ConstantBuffer::commit()
	{
		reset();

		do
		{
			uint32_t opcode = read();

			if (UniformType::End == opcode)
			{
				break;
			}

			UniformType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			decodeOpcode(opcode, type, loc, num, copy);

			const char* data;
			if (copy)
			{
				data = read(g_uniformTypeSize[type]*num);
			}
			else
			{
				memcpy(&data, read(sizeof(void*) ), sizeof(void*) );
			}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _glsuffix, _dxsuffix, _type) \
		case UniformType::_uniform: \
		{ \
			_type* value = (_type*)data; \
			s_renderCtx.m_device->SetVertexShaderConstant##_dxsuffix(loc, value, num); \
		} \
		break; \
		\
		case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
		{ \
			_type* value = (_type*)data; \
			s_renderCtx.m_device->SetPixelShaderConstant##_dxsuffix(loc, value, num); \
		} \
		break

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

			case UniformType::End:
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

		IDirect3DDevice9* device = s_renderCtx.m_device;
		DX_CHECK(device->SetViewport(&vp) );
		DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
		DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, FALSE) );
		DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS) );
		DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
		DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
		DX_CHECK(device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );
		DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE) );
		DX_CHECK(device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID) );

		Program& program = s_renderCtx.m_program[m_program.idx];
		device->SetVertexShader( (IDirect3DVertexShader9*)program.m_vsh->m_ptr);
		device->SetPixelShader( (IDirect3DPixelShader9*)program.m_fsh->m_ptr);

		VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
		VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[m_vb->decl.idx];
		DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );
		DX_CHECK(device->SetVertexDeclaration(vertexDecl.m_ptr) );

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
		DX_CHECK(device->SetIndices(ib.m_ptr) );

		float proj[16];
		mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		PredefinedUniform& predefined = program.m_predefined[0];
		uint8_t flags = predefined.m_type;
		s_renderCtx.setShaderConstantF(flags, predefined.m_loc, proj, 4);

		s_renderCtx.m_textures[m_texture.idx].commit(0);
	}

	void TextVideoMemBlitter::render(uint32_t _numIndices)
	{
		uint32_t numVertices = _numIndices*4/6;
		s_renderCtx.m_indexBuffers[m_ib->handle.idx].update(0, _numIndices*2, m_ib->data, true);
		s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(0, numVertices*m_decl.m_stride, m_vb->data, true);

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

	void Context::rendererCreateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_size, NULL);
	}

	void Context::rendererUpdateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].update(_offset, uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size)
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
	}

	void Context::rendererUpdateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].update(_offset, uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicVertexBuffer(VertexBufferHandle _handle)
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

	void Context::rendererCreateProgram(ProgramHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		s_renderCtx.m_program[_handle.idx].create(s_renderCtx.m_vertexShaders[_vsh.idx], s_renderCtx.m_fragmentShaders[_fsh.idx]);
	}

	void Context::rendererDestroyProgram(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_program[_handle.idx].destroy();
	}

	void Context::rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags)
	{
		s_renderCtx.m_textures[_handle.idx].create(_mem, _flags);
	}

	void Context::rendererUpdateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip)
	{
		s_renderCtx.m_updateTexture = &s_renderCtx.m_textures[_handle.idx];
		s_renderCtx.m_updateTexture->updateBegin(_side, _mip);
	}

	void Context::rendererUpdateTexture(TextureHandle /*_handle*/, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		s_renderCtx.m_updateTexture->update(_side, _mip, _rect, _z, _depth, _mem);
	}

	void Context::rendererUpdateTextureEnd()
	{
		s_renderCtx.m_updateTexture->updateEnd();
		s_renderCtx.m_updateTexture = NULL;
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

	void Context::rendererCreateUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name)
	{
		uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type]*_num);
		void* data = g_realloc(NULL, size);
		memset(data, 0, size);
		s_renderCtx.m_uniforms[_handle.idx] = data;
		s_renderCtx.m_uniformReg.add(_name, s_renderCtx.m_uniforms[_handle.idx]);
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
		IDirect3DDevice9* device = s_renderCtx.m_device;

		PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), "rendererSubmit");

		s_renderCtx.updateResolution(m_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		device->BeginScene();

		if (0 < m_render->m_iboffset)
		{
			TransientIndexBuffer* ib = m_render->m_transientIb;
			s_renderCtx.m_indexBuffers[ib->handle.idx].update(0, m_render->m_iboffset, ib->data, true);
		}

		if (0 < m_render->m_vboffset)
		{
			TransientVertexBuffer* vb = m_render->m_transientVb;
			s_renderCtx.m_vertexBuffers[vb->handle.idx].update(0, m_render->m_vboffset, vb->data, true);
		}

		m_render->sort();

		RenderState currentState;
		currentState.reset();
		currentState.m_flags = BGFX_STATE_NONE;
		currentState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			mtxMul(viewProj[ii].val, m_render->m_view[ii].val, m_render->m_proj[ii].val);
		}

		DX_CHECK(device->SetRenderState(D3DRS_FILLMODE, m_render->m_debug&BGFX_DEBUG_WIREFRAME ? D3DFILL_WIREFRAME : D3DFILL_SOLID) );
		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		float alphaRef = 0.0f;
		uint32_t blendFactor = 0;
		D3DPRIMITIVETYPE primType = D3DPT_TRIANGLELIST;
		uint32_t primNumVerts = 3;

		uint32_t statsNumPrimsSubmitted = 0;
		uint32_t statsNumIndices = 0;
		uint32_t statsNumInstances = 0;
		uint32_t statsNumPrimsRendered = 0;

		if (0 == (m_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = m_render->m_num; item < numItems; ++item)
			{
				key.decode(m_render->m_sortKeys[item]);
				const RenderState& state = m_render->m_renderState[m_render->m_sortValues[item] ];

				const uint64_t newFlags = state.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ state.m_flags;
				currentState.m_flags = newFlags;

				const uint64_t newStencil = state.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ state.m_stencil;
				currentState.m_stencil = newStencil;

				if (key.m_view != view)
				{
					currentState.clear();
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_flags = newFlags;
					currentState.m_stencil = newStencil;

					PIX_ENDEVENT();
					PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), "view");

					view = key.m_view;
					programIdx = invalidHandle;

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
					DX_CHECK(device->SetViewport(&vp) );

					Clear& clear = m_render->m_clear[view];

					if (BGFX_CLEAR_NONE != clear.m_flags)
					{
						D3DCOLOR color = 0;
						DWORD flags = 0;

						if (BGFX_CLEAR_COLOR_BIT & clear.m_flags)
						{
							flags |= D3DCLEAR_TARGET;
							uint32_t rgba = clear.m_rgba;
							color = D3DCOLOR_RGBA(rgba>>24, (rgba>>16)&0xff, (rgba>>8)&0xff, rgba&0xff);
							DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA) );
						}

						if (BGFX_CLEAR_DEPTH_BIT & clear.m_flags)
						{
							flags |= D3DCLEAR_ZBUFFER;
							DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE) );
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
							DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE) );
							DX_CHECK(device->SetScissorRect(&rc) );
							DX_CHECK(device->Clear(0, NULL, flags, color, clear.m_depth, clear.m_stencil) );
							DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE) );
						}
					}

					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS) );
					DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );
				}

				if (0 != changedStencil)
				{
					bool enable = 0 != newStencil;
					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, enable) );
					
					if (0 != newStencil)
					{
						uint32_t fstencil = unpackStencil(0, newStencil);
						uint32_t bstencil = unpackStencil(1, newStencil);
						uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
						DX_CHECK(device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, 0 != frontAndBack) );

						uint32_t fchanged = unpackStencil(0, changedStencil);
						if ( (BGFX_STENCIL_FUNC_REF_MASK|BGFX_STENCIL_FUNC_RMASK_MASK) & fchanged)
						{
							uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
							DX_CHECK(device->SetRenderState(D3DRS_STENCILREF, ref) );

							uint32_t rmask = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
							DX_CHECK(device->SetRenderState(D3DRS_STENCILMASK, rmask) );
						}

// 						uint32_t bchanged = unpackStencil(1, changedStencil);
// 						if (BGFX_STENCIL_FUNC_RMASK_MASK & bchanged)
// 						{
// 							uint32_t wmask = (bstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
// 							DX_CHECK(device->SetRenderState(D3DRS_STENCILWRITEMASK, wmask) );
// 						}

						for (uint32_t ii = 0, num = frontAndBack+1; ii < num; ++ii)
						{
							uint32_t stencil = unpackStencil(ii, newStencil);
							uint32_t changed = unpackStencil(ii, changedStencil);

							if ( (BGFX_STENCIL_TEST_MASK|BGFX_STENCIL_FUNC_REF_MASK|BGFX_STENCIL_FUNC_RMASK_MASK) & changed)
							{
								uint32_t func = (stencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT;
								DX_CHECK(device->SetRenderState(s_stencilFuncRs[ii], s_stencilFunc[func]) );
							}

							if ( (BGFX_STENCIL_OP_FAIL_S_MASK|BGFX_STENCIL_OP_FAIL_Z_MASK|BGFX_STENCIL_OP_PASS_Z_MASK) & changed)
							{
								uint32_t sfail = (stencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT;
								DX_CHECK(device->SetRenderState(s_stencilFailRs[ii], s_stencilOp[sfail]) );

								uint32_t zfail = (stencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT;
								DX_CHECK(device->SetRenderState(s_stencilZFailRs[ii], s_stencilOp[zfail]) );

								uint32_t zpass = (stencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT;
								DX_CHECK(device->SetRenderState(s_stencilZPassRs[ii], s_stencilOp[zpass]) );
							}
						}
					}
				}

				if ( (BGFX_STATE_CULL_MASK|BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK
					 |BGFX_STATE_ALPHA_MASK|BGFX_STATE_RGB_WRITE|BGFX_STATE_BLEND_MASK
					 |BGFX_STATE_ALPHA_REF_MASK|BGFX_STATE_PT_MASK|BGFX_STATE_POINT_SIZE_MASK
					 |BGFX_STATE_SRGBWRITE|BGFX_STATE_MSAA) & changedFlags)
				{
					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						uint32_t cull = (newFlags&BGFX_STATE_CULL_MASK)>>BGFX_STATE_CULL_SHIFT;
						DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, s_cullMode[cull]) );
					}

					if (BGFX_STATE_DEPTH_WRITE & changedFlags)
					{ 
						DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, !!(BGFX_STATE_DEPTH_WRITE & newFlags) ) );
					}

					if (BGFX_STATE_DEPTH_TEST_MASK & changedFlags)
					{
						uint32_t func = (newFlags&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
						DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, 0 != func) );

						if (0 != func)
						{
							DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, s_depthFunc[func]) );
						}
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						alphaRef = ref/255.0f;
					}

					if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
					{
						DX_CHECK(device->SetRenderState(D3DRS_POINTSIZE, castfu( (float)( (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) ) ) );
					}

#if BX_PLATFORM_WINDOWS
					if (BGFX_STATE_SRGBWRITE & changedFlags)
					{
						DX_CHECK(device->SetRenderState(D3DRS_SRGBWRITEENABLE, (newFlags&BGFX_STATE_SRGBWRITE) == BGFX_STATE_SRGBWRITE) );
					}
#endif // BX_PLATFORM_WINDOWS

					if (BGFX_STATE_MSAA & changedFlags)
					{
						DX_CHECK(device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, (newFlags&BGFX_STATE_MSAA) == BGFX_STATE_MSAA) );
					}

					if ( (BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE) & changedFlags)
					{
						uint32_t writeEnable = (newFlags&BGFX_STATE_ALPHA_WRITE) ? D3DCOLORWRITEENABLE_ALPHA : 0;
 						writeEnable |= (newFlags&BGFX_STATE_RGB_WRITE) ? D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE : 0;
						DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, writeEnable) );
					}

					if (BGFX_STATE_BLEND_MASK & changedFlags)
					{
						bool alphaBlendEnabled = !!(BGFX_STATE_BLEND_MASK & newFlags);
						DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlendEnabled) );
//						DX_CHECK(device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, alphaBlendEnabled) );

						if (alphaBlendEnabled)
						{
							uint32_t blend = (newFlags&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT;
							uint32_t src = blend&0xf;
							uint32_t dst = (blend>>4)&0xf;

 							DX_CHECK(device->SetRenderState(D3DRS_SRCBLEND, s_blendFactor[src].m_src) );
							DX_CHECK(device->SetRenderState(D3DRS_DESTBLEND, s_blendFactor[dst].m_dst) );
//							DX_CHECK(device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_SRCALPHA) );
//							DX_CHECK(device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA) );

							if ( (s_blendFactor[src].m_factor || s_blendFactor[dst].m_factor)
							&&  blendFactor != state.m_rgba)
							{
								blendFactor = state.m_rgba;
								D3DCOLOR color = D3DCOLOR_RGBA(blendFactor>>24, (blendFactor>>16)&0xff, (blendFactor>>8)&0xff, blendFactor&0xff);
								DX_CHECK(device->SetRenderState(D3DRS_BLENDFACTOR, color) );
							}
						}
					}

					uint8_t primIndex = uint8_t( (newFlags&BGFX_STATE_PT_MASK)>>BGFX_STATE_PT_SHIFT);
					primType = s_primType[primIndex];
					primNumVerts = 3-primIndex;
				}

				bool programChanged = false;
				bool constantsChanged = state.m_constBegin < state.m_constEnd;
				rendererUpdateUniforms(m_render->m_constantBuffer, state.m_constBegin, state.m_constEnd);

				if (key.m_program != programIdx)
				{
					programIdx = key.m_program;

					if (invalidHandle == programIdx)
					{
						device->SetVertexShader(NULL);
						device->SetPixelShader(NULL);
					}
					else
					{
						Program& program = s_renderCtx.m_program[programIdx];
						device->SetVertexShader( (IDirect3DVertexShader9*)program.m_vsh->m_ptr);
						device->SetPixelShader( (IDirect3DPixelShader9*)program.m_fsh->m_ptr);
					}

					programChanged = 
						constantsChanged = true;
				}

				if (invalidHandle != programIdx)
				{
					Program& program = s_renderCtx.m_program[programIdx];

					if (constantsChanged)
					{
						program.commit();
					}

					for (uint32_t ii = 0, num = program.m_numPredefined; ii < num; ++ii)
					{
						PredefinedUniform& predefined = program.m_predefined[ii];
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

						case PredefinedUniform::ModelView:
							{
								Matrix4 modelView;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelView.val, model.val, m_render->m_view[view].val);
								s_renderCtx.setShaderConstantF(flags, predefined.m_loc, modelView.val, uint32_min(4, predefined.m_count) );
							}
							break;

						case PredefinedUniform::ModelViewProj:
							{
								Matrix4 modelViewProj;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelViewProj.val, model.val, viewProj[view].val);
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
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

								Matrix4 modelViewProj;
								mtxMul(modelViewProj.val, model.val, viewProjBias.val);

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
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

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
						||  programChanged)
						{
							if (invalidHandle != sampler.m_idx)
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
								DX_CHECK(device->SetTexture(stage, NULL) );
							}
						}

						current = sampler;
						flag <<= 1;
					}
				}

				if (currentState.m_vertexBuffer.idx != state.m_vertexBuffer.idx || programChanged)
				{
					currentState.m_vertexBuffer = state.m_vertexBuffer;

					uint16_t handle = state.m_vertexBuffer.idx;
					if (invalidHandle != handle)
					{
						const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[handle];

						uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );

						if (invalidHandle != state.m_instanceDataBuffer.idx
						&&  s_renderCtx.m_instancing)
						{
							const VertexBuffer& inst = s_renderCtx.m_vertexBuffers[state.m_instanceDataBuffer.idx];
							DX_CHECK(device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA|state.m_numInstances) );
							DX_CHECK(device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA|1) );
							DX_CHECK(device->SetStreamSource(1, inst.m_ptr, state.m_instanceDataOffset, state.m_instanceDataStride) );

							IDirect3DVertexDeclaration9* ptr = createVertexDecl(vertexDecl.m_decl, state.m_instanceDataStride/16);
							DX_CHECK(device->SetVertexDeclaration(ptr) );
							DX_RELEASE(ptr, 0);
						}
						else
						{
							DX_CHECK(device->SetStreamSourceFreq(0, 1) );
							DX_CHECK(device->SetStreamSource(1, NULL, 0, 0) );
							DX_CHECK(device->SetVertexDeclaration(vertexDecl.m_ptr) );
						}
					}
					else
					{
						DX_CHECK(device->SetStreamSource(0, NULL, 0, 0) );
						DX_CHECK(device->SetStreamSource(1, NULL, 0, 0) );
					}
				}

				if (currentState.m_indexBuffer.idx != state.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = state.m_indexBuffer;

					uint16_t handle = state.m_indexBuffer.idx;
					if (invalidHandle != handle)
					{
						const IndexBuffer& ib = s_renderCtx.m_indexBuffers[handle];
						DX_CHECK(device->SetIndices(ib.m_ptr) );
					}
					else
					{
						DX_CHECK(device->SetIndices(NULL) );
					}
				}

				if (invalidHandle != currentState.m_vertexBuffer.idx)
				{
					uint32_t numVertices = state.m_numVertices;
					if (UINT32_C(0xffffffff) == numVertices)
					{
						const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDeclaration& vertexDecl = s_renderCtx.m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_decl.m_stride;
					}

					uint32_t numIndices = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances = 0;
					uint32_t numPrimsRendered = 0;

					if (invalidHandle != state.m_indexBuffer.idx)
					{
						if (UINT32_MAX == state.m_numIndices)
						{
							numIndices = s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2;
							numPrimsSubmitted = numIndices/primNumVerts;
							numInstances = state.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

							DX_CHECK(device->DrawIndexedPrimitive(primType
								, state.m_startVertex
								, 0
								, numVertices
								, 0
								, numPrimsSubmitted
								) );
						}
						else if (primNumVerts <= state.m_numIndices)
						{
							numIndices = state.m_numIndices;
							numPrimsSubmitted = numIndices/primNumVerts;
							numInstances = state.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

							DX_CHECK(device->DrawIndexedPrimitive(primType
								, state.m_startVertex
								, 0
								, numVertices
								, state.m_startIndex
								, numPrimsSubmitted
								) );
						}
					}
					else
					{
						numPrimsSubmitted = numVertices/primNumVerts;
						numInstances = state.m_numInstances;
						numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

						DX_CHECK(device->DrawPrimitive(primType
							, state.m_startVertex
							, numPrimsSubmitted
							) );
					}

					statsNumPrimsSubmitted += numPrimsSubmitted;
					statsNumIndices += numIndices;
					statsNumInstances += numInstances;
					statsNumPrimsRendered += numPrimsRendered;
				}
			}

			PIX_ENDEVENT();

			if (0 < m_render->m_num)
			{
				captureElapsed = -bx::getHPCounter();
				s_renderCtx.capture();
				captureElapsed += bx::getHPCounter();
			}
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;
		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

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
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f, " " BGFX_RENDERER_NAME " ");

				const D3DADAPTER_IDENTIFIER9& identifier = s_renderCtx.m_identifier;
				tvm.printf(0, pos++, 0x0f, " Device: %s (%s)", identifier.Description, identifier.Driver);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "      Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS"
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, " Draw calls: %4d / CPU %3.4f [ms]"
					, m_render->m_num
					, elapsedCpuMs
					);
				tvm.printf(10, pos++, 0x8e, "      Prims: %7d (#inst: %5d), submitted: %7d"
					, statsNumPrimsRendered
					, statsNumInstances
					, statsNumPrimsSubmitted
					);

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "    Capture: %3.4f [ms]", captureMs);
				tvm.printf(10, pos++, 0x8e, "    Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "   DVB size: %7d", m_render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "   DIB size: %7d", m_render->m_iboffset);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = m_render->m_waitSubmit < m_render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], "Submit wait: %3.4f [ms]", m_render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], "Render wait: %3.4f [ms]", m_render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			m_textVideoMemBlitter.blit(tvm);

			PIX_ENDEVENT();
		}
		else if (m_render->m_debug & BGFX_DEBUG_TEXT)
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), "debugtext");

			m_textVideoMemBlitter.blit(m_render->m_textVideoMem);

			PIX_ENDEVENT();
		}

		device->EndScene();
	}
}

#endif // BGFX_CONFIG_RENDERER_DIRECT3D9

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D9
#	include "renderer_d3d9.h"

namespace bgfx { namespace d3d9
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];
	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	struct PrimInfo
	{
		D3DPRIMITIVETYPE m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ D3DPT_TRIANGLELIST,  3, 3, 0 },
		{ D3DPT_TRIANGLESTRIP, 3, 1, 2 },
		{ D3DPT_LINELIST,      2, 2, 0 },
		{ D3DPT_LINESTRIP,     2, 1, 1 },
		{ D3DPT_POINTLIST,     1, 1, 0 },
		{ D3DPRIMITIVETYPE(0), 0, 0, 0 },
	};

	static const char* s_primName[] =
	{
		"TriList",
		"TriStrip",
		"Line",
		"LineStrip",
		"Point",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_primInfo) == BX_COUNTOF(s_primName)+1);

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
		{ D3DBLEND_ZERO,           D3DBLEND_ZERO,           false }, // ZERO
		{ D3DBLEND_ONE,            D3DBLEND_ONE,            false }, // ONE
		{ D3DBLEND_SRCCOLOR,       D3DBLEND_SRCCOLOR,       false }, // SRC_COLOR
		{ D3DBLEND_INVSRCCOLOR,    D3DBLEND_INVSRCCOLOR,    false }, // INV_SRC_COLOR
		{ D3DBLEND_SRCALPHA,       D3DBLEND_SRCALPHA,       false }, // SRC_ALPHA
		{ D3DBLEND_INVSRCALPHA,    D3DBLEND_INVSRCALPHA,    false }, // INV_SRC_ALPHA
		{ D3DBLEND_DESTALPHA,      D3DBLEND_DESTALPHA,      false }, // DST_ALPHA
		{ D3DBLEND_INVDESTALPHA,   D3DBLEND_INVDESTALPHA,   false }, // INV_DST_ALPHA
		{ D3DBLEND_DESTCOLOR,      D3DBLEND_DESTCOLOR,      false }, // DST_COLOR
		{ D3DBLEND_INVDESTCOLOR,   D3DBLEND_INVDESTCOLOR,   false }, // INV_DST_COLOR
		{ D3DBLEND_SRCALPHASAT,    D3DBLEND_ONE,            false }, // SRC_ALPHA_SAT
		{ D3DBLEND_BLENDFACTOR,    D3DBLEND_BLENDFACTOR,    true  }, // FACTOR
		{ D3DBLEND_INVBLENDFACTOR, D3DBLEND_INVBLENDFACTOR, true  }, // INV_FACTOR
	};

	static const D3DBLENDOP s_blendEquation[] =
	{
		D3DBLENDOP_ADD,
		D3DBLENDOP_SUBTRACT,
		D3DBLENDOP_REVSUBTRACT,
		D3DBLENDOP_MIN,
		D3DBLENDOP_MAX,
	};

	static const D3DCMPFUNC s_cmpFunc[] =
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

	static const D3DTEXTUREADDRESS s_textureAddress[] =
	{
		D3DTADDRESS_WRAP,
		D3DTADDRESS_MIRROR,
		D3DTADDRESS_CLAMP,
		D3DTADDRESS_BORDER,
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
	};

	static TextureFormatInfo s_textureFormat[] =
	{
		{ D3DFMT_DXT1          }, // BC1
		{ D3DFMT_DXT3          }, // BC2
		{ D3DFMT_DXT5          }, // BC3
		{ D3DFMT_UNKNOWN       }, // BC4
		{ D3DFMT_UNKNOWN       }, // BC5
		{ D3DFMT_UNKNOWN       }, // BC6H
		{ D3DFMT_UNKNOWN       }, // BC7
		{ D3DFMT_UNKNOWN       }, // ETC1
		{ D3DFMT_UNKNOWN       }, // ETC2
		{ D3DFMT_UNKNOWN       }, // ETC2A
		{ D3DFMT_UNKNOWN       }, // ETC2A1
		{ D3DFMT_UNKNOWN       }, // PTC12
		{ D3DFMT_UNKNOWN       }, // PTC14
		{ D3DFMT_UNKNOWN       }, // PTC12A
		{ D3DFMT_UNKNOWN       }, // PTC14A
		{ D3DFMT_UNKNOWN       }, // PTC22
		{ D3DFMT_UNKNOWN       }, // PTC24
		{ D3DFMT_UNKNOWN       }, // Unknown
		{ D3DFMT_A1            }, // R1
		{ D3DFMT_A8            }, // A8
		{ D3DFMT_L8            }, // R8
		{ D3DFMT_UNKNOWN       }, // R8I
		{ D3DFMT_UNKNOWN       }, // R8U
		{ D3DFMT_UNKNOWN       }, // R8S
		{ D3DFMT_L16           }, // R16
		{ D3DFMT_UNKNOWN       }, // R16I
		{ D3DFMT_UNKNOWN       }, // R16U
		{ D3DFMT_R16F          }, // R16F
		{ D3DFMT_UNKNOWN       }, // R16S
		{ D3DFMT_UNKNOWN       }, // R32I
		{ D3DFMT_UNKNOWN       }, // R32U
		{ D3DFMT_R32F          }, // R32F
		{ D3DFMT_A8L8          }, // RG8
		{ D3DFMT_UNKNOWN       }, // RG8I
		{ D3DFMT_UNKNOWN       }, // RG8U
		{ D3DFMT_UNKNOWN       }, // RG8S
		{ D3DFMT_G16R16        }, // RG16
		{ D3DFMT_UNKNOWN       }, // RG16I
		{ D3DFMT_UNKNOWN       }, // RG16U
		{ D3DFMT_G16R16F       }, // RG16F
		{ D3DFMT_UNKNOWN       }, // RG16S
		{ D3DFMT_UNKNOWN       }, // RG32I
		{ D3DFMT_UNKNOWN       }, // RG32U
		{ D3DFMT_G32R32F       }, // RG32F
		{ D3DFMT_UNKNOWN       }, // RGB9E5F
		{ D3DFMT_A8R8G8B8      }, // BGRA8
		{ D3DFMT_UNKNOWN       }, // RGBA8
		{ D3DFMT_UNKNOWN       }, // RGBA8I
		{ D3DFMT_UNKNOWN       }, // RGBA8U
		{ D3DFMT_UNKNOWN       }, // RGBA8S
		{ D3DFMT_A16B16G16R16  }, // RGBA16
		{ D3DFMT_UNKNOWN       }, // RGBA16I
		{ D3DFMT_UNKNOWN       }, // RGBA16U
		{ D3DFMT_A16B16G16R16F }, // RGBA16F
		{ D3DFMT_UNKNOWN       }, // RGBA16S
		{ D3DFMT_UNKNOWN       }, // RGBA32I
		{ D3DFMT_UNKNOWN       }, // RGBA32U
		{ D3DFMT_A32B32G32R32F }, // RGBA32F
		{ D3DFMT_R5G6B5        }, // R5G6B5
		{ D3DFMT_A4R4G4B4      }, // RGBA4
		{ D3DFMT_A1R5G5B5      }, // RGB5A1
		{ D3DFMT_A2B10G10R10   }, // RGB10A2
		{ D3DFMT_UNKNOWN       }, // R11G11B10F
		{ D3DFMT_UNKNOWN       }, // UnknownDepth
		{ D3DFMT_D16           }, // D16
		{ D3DFMT_D24X8         }, // D24
		{ D3DFMT_D24S8         }, // D24S8
		{ D3DFMT_D32           }, // D32
		{ D3DFMT_DF16          }, // D16F
		{ D3DFMT_DF24          }, // D24F
		{ D3DFMT_D32F_LOCKABLE }, // D32F
		{ D3DFMT_S8_LOCKABLE   }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

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

	static const GUID IID_IDirect3D9         = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
	static const GUID IID_IDirect3DDevice9Ex = { 0xb18b10ce, 0x2649, 0x405a, { 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a } };

	typedef HRESULT (WINAPI *Direct3DCreate9ExFn)(UINT SDKVersion, IDirect3D9Ex**);
	static Direct3DCreate9ExFn     Direct3DCreate9Ex;
	typedef IDirect3D9* (WINAPI *Direct3DCreate9Fn)(UINT SDKVersion);
	static Direct3DCreate9Fn       Direct3DCreate9;
	static PFN_D3DPERF_SET_MARKER  D3DPERF_SetMarker;
	static PFN_D3DPERF_BEGIN_EVENT D3DPERF_BeginEvent;
	static PFN_D3DPERF_END_EVENT   D3DPERF_EndEvent;

	struct RendererContextD3D9 : public RendererContextI
	{
		RendererContextD3D9()
			: m_d3d9(NULL)
			, m_device(NULL)
			, m_flushQuery(NULL)
			, m_swapChain(NULL)
			, m_captureTexture(NULL)
			, m_captureSurface(NULL)
			, m_captureResolve(NULL)
			, m_maxAnisotropy(1)
			, m_initialized(false)
			, m_amd(false)
			, m_nvidia(false)
			, m_instancingSupport(false)
			, m_timerQuerySupport(false)
			, m_occlusionQuerySupport(false)
			, m_rtMsaa(false)
		{
		}

		~RendererContextD3D9()
		{
		}

		bool init()
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedD3D9,
					CreatedD3D9,
					CreatedDevice,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

			m_fbh.idx = invalidHandle;
			memset(m_uniforms, 0, sizeof(m_uniforms) );
			memset(&m_resolution, 0, sizeof(m_resolution) );

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
			m_params.hDeviceWindow = NULL;
			m_params.Windowed = true;

			RECT rect;
			GetWindowRect( (HWND)g_platformData.nwh, &rect);
			m_params.BackBufferWidth  = rect.right-rect.left;
			m_params.BackBufferHeight = rect.bottom-rect.top;

			m_d3d9dll = bx::dlopen("d3d9.dll");
			BX_WARN(NULL != m_d3d9dll, "Failed to load d3d9.dll.");

			if (NULL == m_d3d9dll)
			{
				goto error;
			}

			errorState = ErrorState::LoadedD3D9;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
			{
				D3DPERF_SetMarker  = (PFN_D3DPERF_SET_MARKER )bx::dlsym(m_d3d9dll, "D3DPERF_SetMarker");
				D3DPERF_BeginEvent = (PFN_D3DPERF_BEGIN_EVENT)bx::dlsym(m_d3d9dll, "D3DPERF_BeginEvent");
				D3DPERF_EndEvent   = (PFN_D3DPERF_END_EVENT  )bx::dlsym(m_d3d9dll, "D3DPERF_EndEvent");

				BX_CHECK(NULL != D3DPERF_SetMarker
					  && NULL != D3DPERF_BeginEvent
					  && NULL != D3DPERF_EndEvent
					  , "Failed to initialize PIX events."
					  );
			}

			m_d3d9ex   = NULL;
			m_deviceEx = NULL;

			Direct3DCreate9Ex = (Direct3DCreate9ExFn)bx::dlsym(m_d3d9dll, "Direct3DCreate9Ex");
			if (BX_ENABLED(BGFX_CONFIG_RENDERER_DIRECT3D9EX)
			&&  NULL != Direct3DCreate9Ex)
			{
				Direct3DCreate9Ex(D3D_SDK_VERSION, &m_d3d9ex);
				DX_CHECK(m_d3d9ex->QueryInterface(IID_IDirect3D9, (void**)&m_d3d9) );
				m_pool = D3DPOOL_DEFAULT;
			}
			else
			{
				Direct3DCreate9 = (Direct3DCreate9Fn)bx::dlsym(m_d3d9dll, "Direct3DCreate9");
				BX_WARN(NULL != Direct3DCreate9, "Function Direct3DCreate9 not found.");

				if (NULL == Direct3DCreate9)
				{
					goto error;
				}

				m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
				m_pool = D3DPOOL_MANAGED;
			}

			BX_WARN(NULL != m_d3d9, "Unable to create Direct3D.");

			if (NULL == m_d3d9)
			{
				goto error;
			}

			errorState = ErrorState::CreatedD3D9;

			{
				m_adapter    = D3DADAPTER_DEFAULT;
				m_deviceType = BGFX_PCI_ID_SOFTWARE_RASTERIZER == g_caps.vendorId
					? D3DDEVTYPE_REF
					: D3DDEVTYPE_HAL
					;

				uint8_t numGPUs = uint8_t(bx::uint32_min(BX_COUNTOF(g_caps.gpu), m_d3d9->GetAdapterCount() ) );
				for (uint32_t ii = 0; ii < numGPUs; ++ii)
				{
					D3DADAPTER_IDENTIFIER9 desc;
					HRESULT hr = m_d3d9->GetAdapterIdentifier(ii, 0, &desc);
					if (SUCCEEDED(hr) )
					{
						BX_TRACE("Adapter #%d", ii);
						BX_TRACE("\tDriver: %s", desc.Driver);
						BX_TRACE("\tDescription: %s", desc.Description);
						BX_TRACE("\tDeviceName: %s", desc.DeviceName);
						BX_TRACE("\tVendorId: 0x%08x, DeviceId: 0x%08x, SubSysId: 0x%08x, Revision: 0x%08x"
							, desc.VendorId
							, desc.DeviceId
							, desc.SubSysId
							, desc.Revision
							);

						g_caps.gpu[ii].vendorId = (uint16_t)desc.VendorId;
						g_caps.gpu[ii].deviceId = (uint16_t)desc.DeviceId;

						if (D3DADAPTER_DEFAULT == m_adapter)
						{
							if ( (BGFX_PCI_ID_NONE != g_caps.vendorId ||             0 != g_caps.deviceId)
							&&   (BGFX_PCI_ID_NONE == g_caps.vendorId || desc.VendorId == g_caps.vendorId)
							&&   (               0 == g_caps.deviceId || desc.DeviceId == g_caps.deviceId) )
							{
								m_adapter = ii;
							}

							if (BX_ENABLED(BGFX_CONFIG_DEBUG_PERFHUD)
							&&  0 != strstr(desc.Description, "PerfHUD") )
							{
								m_adapter = ii;
								m_deviceType = D3DDEVTYPE_REF;
							}
						}
					}
				}

				DX_CHECK(m_d3d9->GetAdapterIdentifier(m_adapter, 0, &m_identifier) );
				m_amd    = m_identifier.VendorId == BGFX_PCI_ID_AMD;
				m_nvidia = m_identifier.VendorId == BGFX_PCI_ID_NVIDIA;
				g_caps.vendorId = 0 == m_identifier.VendorId
					? BGFX_PCI_ID_SOFTWARE_RASTERIZER
					: (uint16_t)m_identifier.VendorId
					;
				g_caps.deviceId = (uint16_t)m_identifier.DeviceId;

				uint32_t behaviorFlags[] =
				{
					D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE | D3DCREATE_PUREDEVICE,
					D3DCREATE_MIXED_VERTEXPROCESSING    | D3DCREATE_FPU_PRESERVE,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
				};

				for (uint32_t ii = 0; ii < BX_COUNTOF(behaviorFlags) && NULL == m_device; ++ii)
				{
					if (NULL != m_d3d9ex)
					{
						DX_CHECK(m_d3d9ex->CreateDeviceEx(m_adapter
							, m_deviceType
							, (HWND)g_platformData.nwh
							, behaviorFlags[ii]
							, &m_params
							, NULL
							, &m_deviceEx
							) );

						m_device = m_deviceEx;
					}
					else
					{
						DX_CHECK(m_d3d9->CreateDevice(m_adapter
							, m_deviceType
							, (HWND)g_platformData.nwh
							, behaviorFlags[ii]
							, &m_params
							, &m_device
							) );
					}
				}
			}

			BX_WARN(NULL != m_device, "Unable to create Direct3D9 device.");

			if (NULL == m_device)
			{
				goto error;
			}

			errorState = ErrorState::CreatedDevice;

			m_numWindows = 1;

			if (NULL != m_d3d9ex)
			{
				DX_CHECK(m_device->QueryInterface(IID_IDirect3DDevice9Ex, (void**)&m_deviceEx) );
			}

			{
				IDirect3DQuery9* timerQueryTest[3] = {};
				m_timerQuerySupport = true
					&& SUCCEEDED(m_device->CreateQuery(D3DQUERYTYPE_TIMESTAMPDISJOINT, &timerQueryTest[0]) )
					&& SUCCEEDED(m_device->CreateQuery(D3DQUERYTYPE_TIMESTAMP,         &timerQueryTest[1]) )
					&& SUCCEEDED(m_device->CreateQuery(D3DQUERYTYPE_TIMESTAMPFREQ,     &timerQueryTest[2]) )
					;
				DX_RELEASE(timerQueryTest[0], 0);
				DX_RELEASE(timerQueryTest[1], 0);
				DX_RELEASE(timerQueryTest[2], 0);
			}

			{
				IDirect3DQuery9* occlusionQueryTest;
				m_occlusionQuerySupport = true
					&& SUCCEEDED(m_device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &occlusionQueryTest) )
					;
				DX_RELEASE(occlusionQueryTest, 0);
			}

			DX_CHECK(m_device->GetDeviceCaps(&m_caps) );

			// For shit GPUs that can create DX9 device but can't do simple stuff. GTFO!
			BX_WARN( (D3DPTEXTURECAPS_SQUAREONLY & m_caps.TextureCaps) == 0, "D3DPTEXTURECAPS_SQUAREONLY");
			BX_WARN( (D3DPTEXTURECAPS_MIPMAP     & m_caps.TextureCaps) == D3DPTEXTURECAPS_MIPMAP, "D3DPTEXTURECAPS_MIPMAP");
			BX_WARN( (D3DPTEXTURECAPS_ALPHA      & m_caps.TextureCaps) == D3DPTEXTURECAPS_ALPHA, "D3DPTEXTURECAPS_ALPHA");
			BX_WARN(m_caps.VertexShaderVersion >= D3DVS_VERSION(2, 0) && m_caps.PixelShaderVersion >= D3DPS_VERSION(2, 1)
					  , "Shader Model Version (vs: %x, ps: %x)."
					  , m_caps.VertexShaderVersion
					  , m_caps.PixelShaderVersion
					  );

			if ( (D3DPTEXTURECAPS_SQUAREONLY & m_caps.TextureCaps) != 0
			||   (D3DPTEXTURECAPS_MIPMAP     & m_caps.TextureCaps) != D3DPTEXTURECAPS_MIPMAP
			||   (D3DPTEXTURECAPS_ALPHA      & m_caps.TextureCaps) != D3DPTEXTURECAPS_ALPHA
			||   !(m_caps.VertexShaderVersion >= D3DVS_VERSION(2, 0) && m_caps.PixelShaderVersion >= D3DPS_VERSION(2, 1) ) )
			{
				goto error;
			}

			BX_TRACE("Max vertex shader 3.0 instr. slots: %d", m_caps.MaxVertexShader30InstructionSlots);
			BX_TRACE("Max vertex shader constants: %d", m_caps.MaxVertexShaderConst);
			BX_TRACE("Max fragment shader 2.0 instr. slots: %d", m_caps.PS20Caps.NumInstructionSlots);
			BX_TRACE("Max fragment shader 3.0 instr. slots: %d", m_caps.MaxPixelShader30InstructionSlots);
			BX_TRACE("Num simultaneous render targets: %d", m_caps.NumSimultaneousRTs);
			BX_TRACE("Max vertex index: %d", m_caps.MaxVertexIndex);

			g_caps.supported |= ( 0
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_SWAP_CHAIN
				| ( (UINT16_MAX < m_caps.MaxVertexIndex) ? BGFX_CAPS_INDEX32 : 0)
				| ( (m_caps.DevCaps2 & D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES) ? BGFX_CAPS_TEXTURE_BLIT : 0)
				| BGFX_CAPS_TEXTURE_READ_BACK
				| (m_occlusionQuerySupport ? BGFX_CAPS_OCCLUSION_QUERY : 0)
				);
			g_caps.maxTextureSize = uint16_t(bx::uint32_min(m_caps.MaxTextureWidth, m_caps.MaxTextureHeight) );
//			g_caps.maxVertexIndex = m_caps.MaxVertexIndex;

			m_caps.NumSimultaneousRTs = uint8_t(bx::uint32_min(m_caps.NumSimultaneousRTs, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) );
			g_caps.maxFBAttachments   = uint8_t(m_caps.NumSimultaneousRTs);

			m_caps.MaxAnisotropy = bx::uint32_max(m_caps.MaxAnisotropy, 1);

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_USE_EXTENSIONS) )
			{
				BX_TRACE("Extended formats:");
				for (uint32_t ii = 0; ii < ExtendedFormat::Count; ++ii)
				{
					ExtendedFormat& fmt = s_extendedFormats[ii];
					fmt.m_supported = SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter, m_deviceType, adapterFormat, fmt.m_usage, fmt.m_type, fmt.m_fmt) );
					const char* fourcc = (const char*)&fmt.m_fmt;
					BX_TRACE("\t%2d: %c%c%c%c %s", ii, fourcc[0], fourcc[1], fourcc[2], fourcc[3], fmt.m_supported ? "supported" : "");
					BX_UNUSED(fourcc);
				}

				m_instancingSupport = false
					|| s_extendedFormats[ExtendedFormat::Inst].m_supported
					|| (m_caps.VertexShaderVersion >= D3DVS_VERSION(3, 0) )
					;

				if (m_amd
				&&  s_extendedFormats[ExtendedFormat::Inst].m_supported)
				{   // AMD only
					m_device->SetRenderState(D3DRS_POINTSIZE, D3DFMT_INST);
				}

				if (s_extendedFormats[ExtendedFormat::Intz].m_supported)
				{
					s_textureFormat[TextureFormat::D24].m_fmt = D3DFMT_INTZ;
					s_textureFormat[TextureFormat::D32].m_fmt = D3DFMT_INTZ;
				}

				s_textureFormat[TextureFormat::BC4].m_fmt = s_extendedFormats[ExtendedFormat::Ati1].m_supported ? D3DFMT_ATI1 : D3DFMT_UNKNOWN;
				s_textureFormat[TextureFormat::BC5].m_fmt = s_extendedFormats[ExtendedFormat::Ati2].m_supported ? D3DFMT_ATI2 : D3DFMT_UNKNOWN;

				g_caps.supported |= m_instancingSupport ? BGFX_CAPS_INSTANCING : 0;
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint8_t support = 0;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, 0
					, D3DRTYPE_TEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_2D : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, D3DUSAGE_QUERY_SRGBREAD
					, D3DRTYPE_TEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, 0
					, D3DRTYPE_VOLUMETEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_3D : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, D3DUSAGE_QUERY_SRGBREAD
					, D3DRTYPE_VOLUMETEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, 0
					, D3DRTYPE_CUBETEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_CUBE : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, D3DUSAGE_QUERY_SRGBREAD
					, D3DRTYPE_CUBETEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, D3DUSAGE_QUERY_VERTEXTEXTURE
					, D3DRTYPE_TEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_VERTEX : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, isDepth(TextureFormat::Enum(ii) ) ? D3DUSAGE_DEPTHSTENCIL : D3DUSAGE_RENDERTARGET
					, D3DRTYPE_TEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				support |= SUCCEEDED(m_d3d9->CheckDeviceMultiSampleType(m_adapter
					, m_deviceType
					, s_textureFormat[ii].m_fmt
					, true
					, D3DMULTISAMPLE_2_SAMPLES
					, NULL
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[ii] = support;
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

			{
				IDirect3DSwapChain9* swapChain;
				DX_CHECK(m_device->GetSwapChain(0, &swapChain) );

				// GPA increases swapchain ref count.
				//
				// This causes assert in debug. When debugger is present refcount
				// checks are off.
				setGraphicsDebuggerPresent(1 != getRefCount(swapChain) );

				DX_RELEASE(swapChain, 0);
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED + 1, "%3d   ", ii);
				mbstowcs(s_viewNameW[ii], s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED);
			}

			if (NULL != m_deviceEx)
			{
				int32_t gpuPriority;
				DX_CHECK(m_deviceEx->GetGPUThreadPriority(&gpuPriority) );
				BX_TRACE("GPU thread priority: %d", gpuPriority);

				uint32_t maxLatency;
				DX_CHECK(m_deviceEx->GetMaximumFrameLatency(&maxLatency) );
				BX_TRACE("GPU max frame latency: %d", maxLatency);
			}

			postReset();

			m_initialized = true;

			g_internalData.context = m_device;
			return true;

		error:
			switch (errorState)
			{
			case ErrorState::CreatedDevice:
				if (NULL != m_d3d9ex)
				{
					DX_RELEASE(m_deviceEx, 1);
					DX_RELEASE(m_device, 0);
				}
				else
				{
					DX_RELEASE(m_device, 0);
				}

			case ErrorState::CreatedD3D9:
				if (NULL != m_d3d9ex)
				{
					DX_RELEASE(m_d3d9, 1);
					DX_RELEASE(m_d3d9ex, 0);
				}
				else
				{
					DX_RELEASE(m_d3d9, 0);
				}

#if BX_PLATFORM_WINDOWS
			case ErrorState::LoadedD3D9:
				bx::dlclose(m_d3d9dll);
#endif // BX_PLATFORM_WINDOWS

			case ErrorState::Default:
				break;
			}

			return false;
		}

		void shutdown()
		{
			preReset();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexDecls); ++ii)
			{
				m_vertexDecls[ii].destroy();
			}

			if (NULL != m_d3d9ex)
			{
				DX_RELEASE(m_deviceEx, 1);
				DX_RELEASE(m_device, 0);
				DX_RELEASE(m_d3d9, 1);
				DX_RELEASE(m_d3d9ex, 0);
			}
			else
			{
				DX_RELEASE(m_device, 0);
				DX_RELEASE(m_d3d9, 0);
			}

#if BX_PLATFORM_WINDOWS
			bx::dlclose(m_d3d9dll);
#endif // BX_PLATFORM_WINDOWS

			m_initialized = false;
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Direct3D9;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			if (NULL != m_d3d9ex)
			{
				return BGFX_RENDERER_DIRECT3D9_NAME " Ex";
			}

			return BGFX_RENDERER_DIRECT3D9_NAME;
		}

		void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem, uint16_t _flags) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl) BX_OVERRIDE
		{
			m_vertexDecls[_handle.idx].create(_decl);
		}

		void destroyVertexDecl(VertexDeclHandle _handle) BX_OVERRIDE
		{
			m_vertexDecls[_handle.idx].destroy();
		}

		void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle, uint16_t /*_flags*/) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t /*_flags*/) BX_OVERRIDE
		{
			VertexDeclHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, Memory* _mem) BX_OVERRIDE
		{
			m_shaders[_handle.idx].create(_mem);
		}

		void destroyShader(ShaderHandle _handle) BX_OVERRIDE
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) BX_OVERRIDE
		{
			m_program[_handle.idx].create(m_shaders[_vsh.idx], m_shaders[_fsh.idx]);
		}

		void destroyProgram(ProgramHandle _handle) BX_OVERRIDE
		{
			m_program[_handle.idx].destroy();
		}

		void createTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags, uint8_t _skip) BX_OVERRIDE
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
		}

		void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) BX_OVERRIDE
		{
			m_updateTexture = &m_textures[_handle.idx];
			m_updateTexture->updateBegin(_side, _mip);
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) BX_OVERRIDE
		{
			m_updateTexture->update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() BX_OVERRIDE
		{
			m_updateTexture->updateEnd();
			m_updateTexture = NULL;
		}

		void readTexture(TextureHandle _handle, void* _data) BX_OVERRIDE
		{
			TextureD3D9& texture = m_textures[_handle.idx];

			D3DLOCKED_RECT lockedRect;
			DX_CHECK(texture.m_texture2d->LockRect(0
				, &lockedRect
				, NULL
				, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY
				) );

			uint32_t srcPitch = lockedRect.Pitch;
			uint8_t* src      = (uint8_t*)lockedRect.pBits;

			const uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(texture.m_textureFormat) );
			uint8_t* dst      = (uint8_t*)_data;
			uint32_t dstPitch = texture.m_width*bpp/8;

			uint32_t pitch = bx::uint32_min(srcPitch, dstPitch);

			for (uint32_t yy = 0, height = texture.m_height; yy < height; ++yy)
			{
				memcpy(dst, src, pitch);

				src += srcPitch;
				dst += dstPitch;
			}

			DX_CHECK(texture.m_texture2d->UnlockRect(0) );
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height) BX_OVERRIDE
		{
			TextureD3D9& texture = m_textures[_handle.idx];
			texture.m_width  = _width;
			texture.m_height = _height;
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) BX_OVERRIDE
		{
			// Resource ref. counts might be messed up outside of bgfx.
			// Disabling ref. count check once texture is overridden.
			setGraphicsDebuggerPresent(true);
			m_textures[_handle.idx].overrideInternal(_ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) BX_OVERRIDE
		{
			// Resource ref. counts might be messed up outside of bgfx.
			// Disabling ref. count check once texture is overridden.
			setGraphicsDebuggerPresent(true);
			return uintptr_t(m_textures[_handle.idx].m_ptr);
		}

		void destroyTexture(TextureHandle _handle) BX_OVERRIDE
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const TextureHandle* _textureHandles) BX_OVERRIDE
		{
			m_frameBuffers[_handle.idx].create(_num, _textureHandles);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat) BX_OVERRIDE
		{
			uint16_t denseIdx = m_numWindows++;
			m_windows[denseIdx] = _handle;
			m_frameBuffers[_handle.idx].create(denseIdx, _nwh, _width, _height, _depthFormat);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) BX_OVERRIDE
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();
			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;
				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[denseIdx] = handle;
					m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) BX_OVERRIDE
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type]*_num);
			void* data = BX_ALLOC(g_allocator, size);
			memset(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name, data);
		}

		void destroyUniform(UniformHandle _handle) BX_OVERRIDE
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
		}

		void saveScreenShot(const char* _filePath) BX_OVERRIDE
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
			GetClientRect( (HWND)g_platformData.nwh, &rc);
			POINT point;
			point.x = rc.left;
			point.y = rc.top;
			ClientToScreen( (HWND)g_platformData.nwh, &point);
			uint8_t* data = (uint8_t*)rect.pBits;
			uint32_t bytesPerPixel = rect.Pitch/dm.Width;

			g_callback->screenShot(_filePath
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

		void updateViewName(uint8_t _id, const char* _name) BX_OVERRIDE
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
			{
				mbstowcs(&s_viewNameW[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
					, _name
					, BX_COUNTOF(s_viewNameW[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
					);
			}

			bx::strlcpy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, _name
				, BX_COUNTOF(s_viewName[0]) - BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) BX_OVERRIDE
		{
			memcpy(m_uniforms[_loc], _data, _size);
		}

		void setMarker(const char* _marker, uint32_t _size) BX_OVERRIDE
		{
#if BGFX_CONFIG_DEBUG_PIX
			uint32_t size = _size*sizeof(wchar_t);
			wchar_t* name = (wchar_t*)alloca(size);
			mbstowcs(name, _marker, size-2);
			PIX_SETMARKER(D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), name);
#endif // BGFX_CONFIG_DEBUG_PIX
			BX_UNUSED(_marker, _size);
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE;

		void blitSetup(TextVideoMemBlitter& _blitter) BX_OVERRIDE
		{
			uint32_t width  = m_params.BackBufferWidth;
			uint32_t height = m_params.BackBufferHeight;

			FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
			setFrameBuffer(fbh, false);

			D3DVIEWPORT9 vp;
			vp.X = 0;
			vp.Y = 0;
			vp.Width = width;
			vp.Height = height;
			vp.MinZ = 0.0f;
			vp.MaxZ = 1.0f;

			IDirect3DDevice9* device = m_device;
			DX_CHECK(device->SetViewport(&vp) );
			DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
			DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, FALSE) );
			DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS) );
			DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
			DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
			DX_CHECK(device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );
			DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE) );
			DX_CHECK(device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID) );

			ProgramD3D9& program = m_program[_blitter.m_program.idx];
			DX_CHECK(device->SetVertexShader(program.m_vsh->m_vertexShader) );
			DX_CHECK(device->SetPixelShader(program.m_fsh->m_pixelShader) );

			VertexBufferD3D9& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
			VertexDeclD3D9& vertexDecl = m_vertexDecls[_blitter.m_vb->decl.idx];
			DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );
			DX_CHECK(device->SetVertexDeclaration(vertexDecl.m_ptr) );

			IndexBufferD3D9& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			DX_CHECK(device->SetIndices(ib.m_ptr) );

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

			PredefinedUniform& predefined = program.m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			m_textures[_blitter.m_texture.idx].commit(0, BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER, NULL);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) BX_OVERRIDE
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers[_blitter.m_ib->handle.idx].update(0, _numIndices * 2, _blitter.m_ib->data, true);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_decl.m_stride, _blitter.m_vb->data, true);

				DX_CHECK(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST
					, 0
					, 0
					, numVertices
					, 0
					, _numIndices / 3
					) );
			}
		}

		void updateMsaa()
		{
			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_checkMsaa); ++ii)
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
					s_msaa[ii].m_quality = bx::uint32_imax(0, quality-1);
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
			m_maxAnisotropy = !!(_resolution.m_flags & BGFX_RESET_MAXANISOTROPY)
				? m_caps.MaxAnisotropy
				: 1
				;
			uint32_t flags = _resolution.m_flags & ~(BGFX_RESET_HMD_RECENTER | BGFX_RESET_MAXANISOTROPY);

			if (m_resolution.m_width  != _resolution.m_width
			||  m_resolution.m_height != _resolution.m_height
			||  m_resolution.m_flags  != flags)
			{
				flags &= ~BGFX_RESET_INTERNAL_FORCE;

				m_resolution = _resolution;
				m_resolution.m_flags = flags;

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

#if BX_PLATFORM_WINDOWS
				D3DDEVICE_CREATION_PARAMETERS dcp;
				DX_CHECK(m_device->GetCreationParameters(&dcp) );

				D3DDISPLAYMODE dm;
				DX_CHECK(m_d3d9->GetAdapterDisplayMode(dcp.AdapterOrdinal, &dm) );

				m_params.BackBufferFormat = dm.Format;
#endif // BX_PLATFORM_WINDOWS

				m_params.BackBufferWidth  = _resolution.m_width;
				m_params.BackBufferHeight = _resolution.m_height;
				m_params.FullScreen_RefreshRateInHz = BGFX_RESET_FULLSCREEN == (m_resolution.m_flags&BGFX_RESET_FULLSCREEN_MASK) ? 60 : 0;
				m_params.PresentationInterval = !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

				updateMsaa();

				Msaa& msaa = s_msaa[(m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];
				m_params.MultiSampleType    = msaa.m_type;
				m_params.MultiSampleQuality = msaa.m_quality;

				preReset();
				DX_CHECK(m_device->Reset(&m_params) );
				postReset();
			}
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true)
		{
			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx
			&&  m_rtMsaa)
			{
				FrameBufferD3D9& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();
			}

			if (!isValid(_fbh) )
			{
				DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
				for (uint32_t ii = 1, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					DX_CHECK(m_device->SetRenderTarget(ii, NULL) );
				}
				DX_CHECK(m_device->SetDepthStencilSurface(m_backBufferDepthStencil) );

				DX_CHECK(m_device->SetRenderState(D3DRS_SRGBWRITEENABLE, 0 != (m_resolution.m_flags & BGFX_RESET_SRGB_BACKBUFFER) ) );
			}
			else
			{
				const FrameBufferD3D9& frameBuffer = m_frameBuffers[_fbh.idx];

				// If frame buffer has only depth attachment D3DFMT_NULL
				// render target is created.
				uint32_t fbnum = bx::uint32_max(1, frameBuffer.m_num);

				for (uint32_t ii = 0; ii < fbnum; ++ii)
				{
					DX_CHECK(m_device->SetRenderTarget(ii, frameBuffer.m_color[ii]) );
				}

				for (uint32_t ii = fbnum, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					DX_CHECK(m_device->SetRenderTarget(ii, NULL) );
				}

				IDirect3DSurface9* depthStencil = frameBuffer.m_depthStencil;
				DX_CHECK(m_device->SetDepthStencilSurface(NULL != depthStencil ? depthStencil : m_backBufferDepthStencil) );

				DX_CHECK(m_device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE) );
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags&BGFX_UNIFORM_FRAGMENTBIT)
			{
				DX_CHECK(m_device->SetPixelShaderConstantF(_regIndex, (const float*)_val, _numRegs) );
			}
			else
			{
				DX_CHECK(m_device->SetVertexShaderConstantF(_regIndex, (const float*)_val, _numRegs) );
			}
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
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

		static bool isLost(HRESULT _hr)
		{
			return D3DERR_DEVICELOST == _hr
				|| D3DERR_DRIVERINTERNALERROR == _hr
#if !defined(D3D_DISABLE_9EX)
				|| D3DERR_DEVICEHUNG == _hr
				|| D3DERR_DEVICEREMOVED == _hr
#endif // !defined(D3D_DISABLE_9EX)
				;
		}

		void flip(HMD& /*_hmd*/) BX_OVERRIDE
		{
			if (NULL != m_swapChain)
			{
				if (NULL != m_deviceEx)
				{
					DX_CHECK(m_deviceEx->WaitForVBlank(0) );
				}

				for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
				{
					HRESULT hr;
					if (0 == ii)
					{
						hr = m_swapChain->Present(NULL, NULL, (HWND)g_platformData.nwh, NULL, 0);
					}
					else
					{
						hr = m_frameBuffers[m_windows[ii].idx].present();
					}

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

						break;
					}
					else if (FAILED(hr) )
					{
						BX_TRACE("Present failed with err 0x%08x.", hr);
					}
#endif // BX_PLATFORM_
				}
			}
		}

		void preReset()
		{
			invalidateSamplerState();

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				DX_CHECK(m_device->SetTexture(stage, NULL) );
			}

			DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
			for (uint32_t ii = 1, num = g_caps.maxFBAttachments; ii < num; ++ii)
			{
				DX_CHECK(m_device->SetRenderTarget(ii, NULL) );
			}
			DX_CHECK(m_device->SetDepthStencilSurface(m_backBufferDepthStencil) );
			DX_CHECK(m_device->SetVertexShader(NULL) );
			DX_CHECK(m_device->SetPixelShader(NULL) );
			DX_CHECK(m_device->SetStreamSource(0, NULL, 0, 0) );
			DX_CHECK(m_device->SetIndices(NULL) );

			DX_RELEASE(m_backBufferColor, 0);
			DX_RELEASE(m_backBufferDepthStencil, 0);
			DX_RELEASE(m_swapChain, 0);

			capturePreReset();

			DX_RELEASE(m_flushQuery, 0);
			if (m_timerQuerySupport)
			{
				m_gpuTimer.preReset();
			}

			if (m_occlusionQuerySupport)
			{
				m_occlusionQuery.preReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].preReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].preReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].preReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].preReset();
			}
		}

		void postReset()
		{
			DX_CHECK(m_device->GetSwapChain(0, &m_swapChain) );
			DX_CHECK(m_swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_backBufferColor) );
			DX_CHECK(m_device->GetDepthStencilSurface(&m_backBufferDepthStencil) );

			DX_CHECK(m_device->CreateQuery(D3DQUERYTYPE_EVENT, &m_flushQuery) );
			if (m_timerQuerySupport)
			{
				m_gpuTimer.postReset();
			}

			if (m_occlusionQuerySupport)
			{
				m_occlusionQuery.postReset();
			}

			capturePostReset();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_indexBuffers); ++ii)
			{
				m_indexBuffers[ii].postReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_vertexBuffers); ++ii)
			{
				m_vertexBuffers[ii].postReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].postReset();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}
		}

		void invalidateSamplerState()
		{
			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				m_samplerFlags[stage] = UINT32_MAX;
			}
		}

		static void setSamplerState(IDirect3DDevice9* _device, DWORD _stage, D3DSAMPLERSTATETYPE _type, DWORD _value)
		{
			DX_CHECK(_device->SetSamplerState(_stage, _type, _value) );
			if (4 > _stage)
			{
				DX_CHECK(_device->SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + _stage, _type, _value) );
			}
		}

		void setSamplerState(uint8_t _stage, uint32_t _flags, const float _rgba[4])
		{
			const uint32_t flags = _flags&( (~BGFX_TEXTURE_RESERVED_MASK) | BGFX_TEXTURE_SAMPLER_BITS_MASK | BGFX_TEXTURE_SRGB);
			BX_CHECK(_stage < BX_COUNTOF(m_samplerFlags), "");
			if (m_samplerFlags[_stage] != flags)
			{
				m_samplerFlags[_stage] = flags;
				IDirect3DDevice9* device = m_device;
				D3DTEXTUREADDRESS tau = s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
				D3DTEXTUREADDRESS tav = s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
				D3DTEXTUREADDRESS taw = s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
				D3DTEXTUREFILTERTYPE minFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
				D3DTEXTUREFILTERTYPE magFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
				D3DTEXTUREFILTERTYPE mipFilter = s_textureFilter[(_flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];

				setSamplerState(device, _stage, D3DSAMP_ADDRESSU,  tau);
				setSamplerState(device, _stage, D3DSAMP_ADDRESSV,  tav);
				setSamplerState(device, _stage, D3DSAMP_ADDRESSW,  taw);
				setSamplerState(device, _stage, D3DSAMP_MINFILTER, minFilter);
				setSamplerState(device, _stage, D3DSAMP_MAGFILTER, magFilter);
				setSamplerState(device, _stage, D3DSAMP_MIPFILTER, mipFilter);
				setSamplerState(device, _stage, D3DSAMP_MAXANISOTROPY, m_maxAnisotropy);
				setSamplerState(device, _stage, D3DSAMP_SRGBTEXTURE, 0 != (flags & BGFX_TEXTURE_SRGB) );
				if (NULL != _rgba)
				{
					if (needBorderColor(_flags) )
					{
						DWORD bc = D3DCOLOR_COLORVALUE(_rgba[0], _rgba[1], _rgba[2], _rgba[3]);
						setSamplerState(device
							, _stage
							, D3DSAMP_BORDERCOLOR
							, bc
							);
					}
				}
			}
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
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
			if (m_resolution.m_flags&BGFX_RESET_CAPTURE)
			{
				uint32_t width  = m_params.BackBufferWidth;
				uint32_t height = m_params.BackBufferHeight;
				D3DFORMAT fmt   = m_params.BackBufferFormat;

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

		void commit(UniformBuffer& _uniformBuffer)
		{
			_uniformBuffer.reset();

			IDirect3DDevice9* device = m_device;

			for (;;)
			{
				uint32_t opcode = _uniformBuffer.read();

				if (UniformType::End == opcode)
				{
					break;
				}

				UniformType::Enum type;
				uint16_t loc;
				uint16_t num;
				uint16_t copy;
				UniformBuffer::decodeOpcode(opcode, type, loc, num, copy);

				const char* data;
				if (copy)
				{
					data = _uniformBuffer.read(g_uniformTypeSize[type]*num);
				}
				else
				{
					UniformHandle handle;
					memcpy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
					data = (const char*)m_uniforms[handle.idx];
				}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type) \
				case UniformType::_uniform: \
				{ \
					_type* value = (_type*)data; \
					DX_CHECK(device->SetVertexShaderConstant##_dxsuffix(loc, value, num) ); \
				} \
				break; \
				\
				case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
				{ \
					_type* value = (_type*)data; \
					DX_CHECK(device->SetPixelShaderConstant##_dxsuffix(loc, value, num) ); \
				} \
				break

				switch ( (int32_t)type)
				{
				case UniformType::Mat3:
					{
						float* value = (float*)data;
						for (uint32_t ii = 0, count = num/3; ii < count; ++ii,  loc += 3, value += 9)
						{
							Matrix4 mtx;
							mtx.un.val[ 0] = value[0];
							mtx.un.val[ 1] = value[1];
							mtx.un.val[ 2] = value[2];
							mtx.un.val[ 3] = 0.0f;
							mtx.un.val[ 4] = value[3];
							mtx.un.val[ 5] = value[4];
							mtx.un.val[ 6] = value[5];
							mtx.un.val[ 7] = 0.0f;
							mtx.un.val[ 8] = value[6];
							mtx.un.val[ 9] = value[7];
							mtx.un.val[10] = value[8];
							mtx.un.val[11] = 0.0f;
							DX_CHECK(device->SetVertexShaderConstantF(loc, &mtx.un.val[0], 3) );
						}
					}
					break;

				case UniformType::Mat3|BGFX_UNIFORM_FRAGMENTBIT:
					{
						float* value = (float*)data;
						for (uint32_t ii = 0, count = num/3; ii < count; ++ii, loc += 3, value += 9)
						{
							Matrix4 mtx;
							mtx.un.val[ 0] = value[0];
							mtx.un.val[ 1] = value[1];
							mtx.un.val[ 2] = value[2];
							mtx.un.val[ 3] = 0.0f;
							mtx.un.val[ 4] = value[3];
							mtx.un.val[ 5] = value[4];
							mtx.un.val[ 6] = value[5];
							mtx.un.val[ 7] = 0.0f;
							mtx.un.val[ 8] = value[6];
							mtx.un.val[ 9] = value[7];
							mtx.un.val[10] = value[8];
							mtx.un.val[11] = 0.0f;
							DX_CHECK(device->SetPixelShaderConstantF(loc, &mtx.un.val[0], 3) );
						}
					}
					break;

				CASE_IMPLEMENT_UNIFORM(Int1, I, int);
				CASE_IMPLEMENT_UNIFORM(Vec4, F, float);
				CASE_IMPLEMENT_UNIFORM(Mat4, F, float);

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}
#undef CASE_IMPLEMENT_UNIFORM
			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			IDirect3DDevice9* device = m_device;

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) )
			{
				const FrameBufferD3D9& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			if (1 == numMrt)
			{
				D3DCOLOR color = 0;
				DWORD flags    = 0;

				if (BGFX_CLEAR_COLOR & _clear.m_flags)
				{
					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[0]);
						const float* rgba = _palette[index];
						const float rr = rgba[0];
						const float gg = rgba[1];
						const float bb = rgba[2];
						const float aa = rgba[3];
						color = D3DCOLOR_COLORVALUE(rr, gg, bb, aa);
					}
					else
					{
						color = D3DCOLOR_RGBA(_clear.m_index[0], _clear.m_index[1], _clear.m_index[2], _clear.m_index[3]);
					}

					flags |= D3DCLEAR_TARGET;
					DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE
						, D3DCOLORWRITEENABLE_RED
						| D3DCOLORWRITEENABLE_GREEN
						| D3DCOLORWRITEENABLE_BLUE
						| D3DCOLORWRITEENABLE_ALPHA
						) );
				}

				if (BGFX_CLEAR_DEPTH & _clear.m_flags)
				{
					flags |= D3DCLEAR_ZBUFFER;
					DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE) );
				}

				if (BGFX_CLEAR_STENCIL & _clear.m_flags)
				{
					flags |= D3DCLEAR_STENCIL;
				}

				if (0 != flags)
				{
					RECT rc;
					rc.left   = _rect.m_x;
					rc.top    = _rect.m_y;
					rc.right  = _rect.m_x + _rect.m_width;
					rc.bottom = _rect.m_y + _rect.m_height;
					DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE) );
					DX_CHECK(device->SetScissorRect(&rc) );
					DX_CHECK(device->Clear(0, NULL, flags, color, _clear.m_depth, _clear.m_stencil) );
					DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE) );
				}
			}
			else
			{
				DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE) );
				DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
				DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );

				if (BGFX_CLEAR_COLOR & _clear.m_flags)
				{
					DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE
						, D3DCOLORWRITEENABLE_RED
						| D3DCOLORWRITEENABLE_GREEN
						| D3DCOLORWRITEENABLE_BLUE
						| D3DCOLORWRITEENABLE_ALPHA
						) );
				}
				else
				{
					DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, 0) );
				}

				if (BGFX_CLEAR_DEPTH & _clear.m_flags)
				{
					DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS) );
				}
				else
				{
					DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, FALSE) );
				}

				if (BGFX_CLEAR_STENCIL & _clear.m_flags)
				{
					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILREF, _clear.m_stencil) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILMASK, 0xff) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_ALWAYS) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILFAIL,  D3DSTENCILOP_REPLACE) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE) );
					DX_CHECK(device->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_REPLACE) );
				}
				else
				{
					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
				}

				VertexBufferD3D9& vb = m_vertexBuffers[_clearQuad.m_vb->handle.idx];
				VertexDeclD3D9& vertexDecl = m_vertexDecls[_clearQuad.m_vb->decl.idx];
				uint32_t stride = _clearQuad.m_decl.m_stride;

				{
					struct Vertex
					{
						float m_x;
						float m_y;
						float m_z;
					};

					Vertex* vertex = (Vertex*)_clearQuad.m_vb->data;
					BX_CHECK(stride == sizeof(Vertex), "Stride/Vertex mismatch (stride %d, sizeof(Vertex) %d)", stride, sizeof(Vertex) );

					const float depth = _clear.m_depth;

					vertex->m_x = -1.0f;
					vertex->m_y = -1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x =  1.0f;
					vertex->m_y = -1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x = -1.0f;
					vertex->m_y =  1.0f;
					vertex->m_z = depth;
					vertex++;
					vertex->m_x =  1.0f;
					vertex->m_y =  1.0f;
					vertex->m_z = depth;
				}

				vb.update(0, 4*stride, _clearQuad.m_vb->data);

				ProgramD3D9& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				device->SetVertexShader(program.m_vsh->m_vertexShader);
				device->SetPixelShader(program.m_fsh->m_pixelShader);

				float mrtClear[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];

				if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
				{
					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE - 1, _clear.m_index[ii]);
						memcpy(mrtClear[ii], _palette[index], 16);
					}
				}
				else
				{
					float rgba[4] =
					{
						_clear.m_index[0] * 1.0f / 255.0f,
						_clear.m_index[1] * 1.0f / 255.0f,
						_clear.m_index[2] * 1.0f / 255.0f,
						_clear.m_index[3] * 1.0f / 255.0f,
					};

					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						memcpy(mrtClear[ii], rgba, 16);
					}
				}

				DX_CHECK(device->SetPixelShaderConstantF(0, mrtClear[0], numMrt));

				DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, stride) );
				DX_CHECK(device->SetStreamSourceFreq(0, 1) );
				DX_CHECK(device->SetStreamSource(1, NULL, 0, 0) );
				DX_CHECK(device->SetVertexDeclaration(vertexDecl.m_ptr) );
				DX_CHECK(device->SetIndices(NULL) );
				DX_CHECK(device->DrawPrimitive(D3DPT_TRIANGLESTRIP
					, 0
					, 2
					) );
			}
		}

#if BX_PLATFORM_WINDOWS
		D3DCAPS9 m_caps;
#endif // BX_PLATFORM_WINDOWS

		IDirect3D9Ex* m_d3d9ex;
		IDirect3DDevice9Ex* m_deviceEx;

		IDirect3D9*        m_d3d9;
		IDirect3DDevice9*  m_device;
		IDirect3DQuery9*   m_flushQuery;
		TimerQueryD3D9     m_gpuTimer;
		OcclusionQueryD3D9 m_occlusionQuery;
		D3DPOOL m_pool;

		IDirect3DSwapChain9* m_swapChain;
		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IDirect3DSurface9* m_backBufferColor;
		IDirect3DSurface9* m_backBufferDepthStencil;

		IDirect3DTexture9* m_captureTexture;
		IDirect3DSurface9* m_captureSurface;
		IDirect3DSurface9* m_captureResolve;

		IDirect3DVertexDeclaration9* m_instanceDataDecls[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

		void* m_d3d9dll;
		uint32_t m_adapter;
		D3DDEVTYPE m_deviceType;
		D3DPRESENT_PARAMETERS m_params;
		uint32_t m_maxAnisotropy;
		D3DADAPTER_IDENTIFIER9 m_identifier;
		Resolution m_resolution;

		bool m_initialized;
		bool m_amd;
		bool m_nvidia;
		bool m_instancingSupport;
		bool m_timerQuerySupport;
		bool m_occlusionQuerySupport;

		D3DFORMAT m_fmtDepth;

		IndexBufferD3D9 m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferD3D9 m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderD3D9 m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramD3D9 m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureD3D9 m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDeclD3D9 m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		FrameBufferD3D9 m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		uint32_t m_samplerFlags[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		TextureD3D9* m_updateTexture;
		uint8_t* m_updateTextureBits;
		uint32_t m_updateTexturePitch;
		uint8_t m_updateTextureSide;
		uint8_t m_updateTextureMip;

		TextVideoMem m_textVideoMem;

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;
	};

	static RendererContextD3D9* s_renderD3D9;

	RendererContextI* rendererCreate()
	{
		s_renderD3D9 = BX_NEW(g_allocator, RendererContextD3D9);
		if (!s_renderD3D9->init() )
		{
			BX_DELETE(g_allocator, s_renderD3D9);
			s_renderD3D9 = NULL;
		}
		return s_renderD3D9;
	}

	void rendererDestroy()
	{
		s_renderD3D9->shutdown();
		BX_DELETE(g_allocator, s_renderD3D9);
		s_renderD3D9 = NULL;
	}

	void IndexBufferD3D9::create(uint32_t _size, void* _data, uint16_t _flags)
	{
		m_size    = _size;
		m_flags   = _flags;
		m_dynamic = NULL == _data;

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL  pool  = s_renderD3D9->m_pool;

		if (m_dynamic)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
		}

		const D3DFORMAT format = 0 == (_flags & BGFX_BUFFER_INDEX32)
			? D3DFMT_INDEX16
			: D3DFMT_INDEX32
			;

		DX_CHECK(s_renderD3D9->m_device->CreateIndexBuffer(m_size
			, usage
			, format
			, pool
			, &m_ptr
			, NULL
			) );

		if (NULL != _data)
		{
			update(0, _size, _data);
		}
	}

	void IndexBufferD3D9::preReset()
	{
		if (m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void IndexBufferD3D9::postReset()
	{
		if (m_dynamic)
		{
			const D3DFORMAT format = 0 == (m_flags & BGFX_BUFFER_INDEX32)
				? D3DFMT_INDEX16
				: D3DFMT_INDEX32
				;

			DX_CHECK(s_renderD3D9->m_device->CreateIndexBuffer(m_size
				, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC
				, format
				, D3DPOOL_DEFAULT
				, &m_ptr
				, NULL
				) );
		}
	}

	void VertexBufferD3D9::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle)
	{
		m_size = _size;
		m_decl = _declHandle;
		m_dynamic = NULL == _data;

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL pool = s_renderD3D9->m_pool;

		if (m_dynamic)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
		}

		DX_CHECK(s_renderD3D9->m_device->CreateVertexBuffer(m_size
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

	void VertexBufferD3D9::preReset()
	{
		if (m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void VertexBufferD3D9::postReset()
	{
		if (m_dynamic)
		{
			DX_CHECK(s_renderD3D9->m_device->CreateVertexBuffer(m_size
					, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC
					, 0
					, D3DPOOL_DEFAULT
					, &m_ptr
					, NULL
					) );
		}
	}

	static const D3DVERTEXELEMENT9 s_attrib[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,       0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,      0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,     0 },
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
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attrib)-1);

	static const uint8_t s_attribType[][4][2] =
	{
		{ // Uint8
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
			{ D3DDECLTYPE_UBYTE4,    D3DDECLTYPE_UBYTE4N   },
		},
		{ // Uint10
			{ D3DDECLTYPE_UDEC3,     D3DDECLTYPE_DEC3N     },
			{ D3DDECLTYPE_UDEC3,     D3DDECLTYPE_DEC3N     },
			{ D3DDECLTYPE_UDEC3,     D3DDECLTYPE_DEC3N     },
			{ D3DDECLTYPE_UDEC3,     D3DDECLTYPE_DEC3N     },
		},
		{ // Int16
			{ D3DDECLTYPE_SHORT2,    D3DDECLTYPE_SHORT2N   },
			{ D3DDECLTYPE_SHORT2,    D3DDECLTYPE_SHORT2N   },
			{ D3DDECLTYPE_SHORT4,    D3DDECLTYPE_SHORT4N   },
			{ D3DDECLTYPE_SHORT4,    D3DDECLTYPE_SHORT4N   },
		},
		{ // Half
			{ D3DDECLTYPE_FLOAT16_2, D3DDECLTYPE_FLOAT16_2 },
			{ D3DDECLTYPE_FLOAT16_2, D3DDECLTYPE_FLOAT16_2 },
			{ D3DDECLTYPE_FLOAT16_4, D3DDECLTYPE_FLOAT16_4 },
			{ D3DDECLTYPE_FLOAT16_4, D3DDECLTYPE_FLOAT16_4 },
		},
		{ // Float
			{ D3DDECLTYPE_FLOAT1,    D3DDECLTYPE_FLOAT1    },
			{ D3DDECLTYPE_FLOAT2,    D3DDECLTYPE_FLOAT2    },
			{ D3DDECLTYPE_FLOAT3,    D3DDECLTYPE_FLOAT3    },
			{ D3DDECLTYPE_FLOAT4,    D3DDECLTYPE_FLOAT4    },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static D3DVERTEXELEMENT9* fillVertexDecl(D3DVERTEXELEMENT9* _out, const VertexDecl& _decl)
	{
		D3DVERTEXELEMENT9* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _decl.m_attributes[attr])
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

	static IDirect3DVertexDeclaration9* createVertexDeclaration(const VertexDecl& _decl, uint16_t _numInstanceData)
	{
		D3DVERTEXELEMENT9 vertexElements[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
		D3DVERTEXELEMENT9* elem = fillVertexDecl(vertexElements, _decl);

		const D3DVERTEXELEMENT9 inst = { 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };

		for (uint8_t ii = 0; ii < _numInstanceData; ++ii)
		{
			memcpy(elem, &inst, sizeof(D3DVERTEXELEMENT9) );
			elem->UsageIndex = uint8_t(7-ii); // TEXCOORD7 = i_data0, TEXCOORD6 = i_data1, etc.
			elem->Offset = ii*16;
			++elem;
		}

		memcpy(elem, &s_attrib[Attrib::Count], sizeof(D3DVERTEXELEMENT9) );

		IDirect3DVertexDeclaration9* ptr;
		DX_CHECK(s_renderD3D9->m_device->CreateVertexDeclaration(vertexElements, &ptr) );
		return ptr;
	}

	void VertexDeclD3D9::create(const VertexDecl& _decl)
	{
		memcpy(&m_decl, &_decl, sizeof(VertexDecl) );
		dump(m_decl);
		m_ptr = createVertexDeclaration(_decl, 0);
	}

	void ShaderD3D9::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		switch (magic)
		{
		case BGFX_CHUNK_MAGIC_FSH:
		case BGFX_CHUNK_MAGIC_VSH:
			break;

		default:
			BGFX_FATAL(false, Fatal::InvalidShader, "Unknown shader format %x.", magic);
			break;
		}

		bool fragment = BGFX_CHUNK_MAGIC_FSH == magic;

		uint32_t iohash;
		bx::read(&reader, iohash);

		uint16_t count;
		bx::read(&reader, count);

		m_numPredefined = 0;

		BX_TRACE("Shader consts %d", count);

		uint8_t fragmentBit = fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		if (0 < count)
		{
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

				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count != predefined)
				{
					kind = "predefined";
					m_predefined[m_numPredefined].m_loc   = regIndex;
					m_predefined[m_numPredefined].m_count = regCount;
					m_predefined[m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
					m_numPredefined++;
				}
				else if (0 == (BGFX_UNIFORM_SAMPLERBIT & type) )
				{
					const UniformInfo* info = s_renderD3D9->m_uniformReg.find(name);
					BX_CHECK(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

					if (NULL != info)
					{
						if (NULL == m_constantBuffer)
						{
							m_constantBuffer = UniformBuffer::create(1024);
						}

						kind = "user";
						m_constantBuffer->writeUniformHandle( (UniformType::Enum)(type|fragmentBit), regIndex, info->m_handle, regCount);
					}
				}
				else
				{
					kind = "sampler";
				}

				BX_TRACE("\t%s: %s (%s), num %2d, r.index %3d, r.count %2d"
					, kind
					, name
					, getUniformTypeName(UniformType::Enum(type&~BGFX_UNIFORM_MASK) )
					, num
					, regIndex
					, regCount
					);
				BX_UNUSED(kind);
			}

			if (NULL != m_constantBuffer)
			{
				m_constantBuffer->finish();
			}
		}

		uint16_t shaderSize;
		bx::read(&reader, shaderSize);

		const DWORD* code = (const DWORD*)reader.getDataPtr();

		if (fragment)
		{
			m_type = 1;
			DX_CHECK(s_renderD3D9->m_device->CreatePixelShader(code, &m_pixelShader) );
			BGFX_FATAL(NULL != m_pixelShader, bgfx::Fatal::InvalidShader, "Failed to create fragment shader.");
		}
		else
		{
			m_type = 0;
			DX_CHECK(s_renderD3D9->m_device->CreateVertexShader(code, &m_vertexShader) );
			BGFX_FATAL(NULL != m_vertexShader, bgfx::Fatal::InvalidShader, "Failed to create vertex shader.");
		}
	}

	void TextureD3D9::createTexture(uint32_t _width, uint32_t _height, uint8_t _numMips)
	{
		m_type = Texture2D;
		const TextureFormat::Enum fmt = (TextureFormat::Enum)m_textureFormat;

		DWORD usage = 0;
		D3DPOOL pool = D3DPOOL_DEFAULT;

		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);
		const bool readBack     = 0 != (m_flags&BGFX_TEXTURE_READ_BACK);
		if (isDepth(fmt) )
		{
			usage = D3DUSAGE_DEPTHSTENCIL;
		}
		else if (readBack)
		{
			usage = 0;
			pool  = D3DPOOL_SYSTEMMEM;
		}
		else if (renderTarget || blit)
		{
			usage = D3DUSAGE_RENDERTARGET;
		}

		IDirect3DDevice9* device = s_renderD3D9->m_device;

		if (renderTarget)
		{
			uint32_t msaaQuality = ( (m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT);
			msaaQuality = bx::uint32_satsub(msaaQuality, 1);

			bool writeOnly = 0 != (m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);

			if (0 != msaaQuality
			||  writeOnly)
			{
				const Msaa& msaa = s_msaa[msaaQuality];

				if (isDepth(fmt) )
				{
					DX_CHECK(device->CreateDepthStencilSurface(
						  m_width
						, m_height
						, s_textureFormat[m_textureFormat].m_fmt
						, msaa.m_type
						, msaa.m_quality
						, FALSE
						, &m_surface
						, NULL
						) );
				}
				else
				{
					DX_CHECK(device->CreateRenderTarget(
						  m_width
						, m_height
						, s_textureFormat[m_textureFormat].m_fmt
						, msaa.m_type
						, msaa.m_quality
						, FALSE
						, &m_surface
						, NULL
						) );
				}

				if (writeOnly)
				{
					// This is render buffer, there is no sampling, no need
					// to create texture.
					return;
				}
			}
		}

		DX_CHECK(device->CreateTexture(_width
			, _height
			, _numMips
			, usage
			, s_textureFormat[fmt].m_fmt
			, pool
			, &m_texture2d
			, NULL
			) );

		if (!renderTarget
		&&  !readBack)
		{
			if (NULL == m_staging)
			{
				DX_CHECK(device->CreateTexture(_width
					, _height
					, _numMips
					, 0
					, s_textureFormat[fmt].m_fmt
					, D3DPOOL_SYSTEMMEM
					, &m_staging2d
					, NULL
					) );
			}
			else
			{
				DX_CHECK(m_staging2d->AddDirtyRect(NULL));
				DX_CHECK(device->UpdateTexture(m_staging2d, m_texture2d));
			}
		}

		BGFX_FATAL(NULL != m_texture2d, Fatal::UnableToCreateTexture, "Failed to create texture (size: %dx%d, mips: %d, fmt: %d)."
			, _width
			, _height
			, _numMips
			, getName(fmt)
			);
	}

	void TextureD3D9::createVolumeTexture(uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips)
	{
		m_type = Texture3D;
		const TextureFormat::Enum fmt = (TextureFormat::Enum)m_textureFormat;

		IDirect3DDevice9* device = s_renderD3D9->m_device;
		DX_CHECK(device->CreateVolumeTexture(_width
			, _height
			, _depth
			, _numMips
			, 0
			, s_textureFormat[fmt].m_fmt
			, D3DPOOL_DEFAULT
			, &m_texture3d
			, NULL
			) );

		if (NULL == m_staging)
		{
			DX_CHECK(device->CreateVolumeTexture(_width
				, _height
				, _depth
				, _numMips
				, 0
				, s_textureFormat[fmt].m_fmt
				, D3DPOOL_SYSTEMMEM
				, &m_staging3d
				, NULL
				) );
		}
		else
		{
			DX_CHECK(m_staging3d->AddDirtyBox(NULL) );
			DX_CHECK(device->UpdateTexture(m_staging3d, m_texture3d) );
		}

		BGFX_FATAL(NULL != m_texture3d, Fatal::UnableToCreateTexture, "Failed to create volume texture (size: %dx%dx%d, mips: %d, fmt: %s)."
			, _width
			, _height
			, _depth
			, _numMips
			, getName(fmt)
			);
	}

	void TextureD3D9::createCubeTexture(uint32_t _width, uint8_t _numMips)
	{
		m_type = TextureCube;
		const TextureFormat::Enum fmt = (TextureFormat::Enum)m_textureFormat;

		DWORD usage = 0;

		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);
		if (isDepth(fmt) )
		{
			usage = D3DUSAGE_DEPTHSTENCIL;
		}
		else if (renderTarget || blit)
		{
			usage = D3DUSAGE_RENDERTARGET;
		}

		IDirect3DDevice9* device = s_renderD3D9->m_device;
		DX_CHECK(device->CreateCubeTexture(_width
			, _numMips
			, usage
			, s_textureFormat[fmt].m_fmt
			, D3DPOOL_DEFAULT
			, &m_textureCube
			, NULL
			) );

		if (!renderTarget)
		{
			if (NULL == m_staging)
			{
				DX_CHECK(device->CreateCubeTexture(_width
					, _numMips
					, 0
					, s_textureFormat[fmt].m_fmt
					, D3DPOOL_SYSTEMMEM
					, &m_stagingCube
					, NULL
					) );
			}
			else
			{
				for (uint8_t ii = 0; ii < 6; ++ii)
				{
					DX_CHECK(m_stagingCube->AddDirtyRect(D3DCUBEMAP_FACES(ii), NULL) );
				}
				DX_CHECK(device->UpdateTexture(m_stagingCube, m_textureCube) );
			}
		}

		BGFX_FATAL(NULL != m_textureCube, Fatal::UnableToCreateTexture, "Failed to create cube texture (edge: %d, mips: %d, fmt: %s)."
			, _width
			, _numMips
			, getName(fmt)
			);
	}

	uint8_t* TextureD3D9::lock(uint8_t _side, uint8_t _lod, uint32_t& _pitch, uint32_t& _slicePitch, const Rect* _rect)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				D3DLOCKED_RECT lockedRect;

				if (NULL != _rect)
				{
					RECT rect;
					rect.left   = _rect->m_x;
					rect.top    = _rect->m_y;
					rect.right  = rect.left + _rect->m_width;
					rect.bottom = rect.top  + _rect->m_height;
					DX_CHECK(m_staging2d->LockRect(_lod, &lockedRect, &rect, 0) );
					DX_CHECK(m_staging2d->AddDirtyRect(&rect) );
				}
				else
				{
					DX_CHECK(m_staging2d->LockRect(_lod, &lockedRect, NULL, 0) );
					DX_CHECK(m_staging2d->AddDirtyRect(NULL) );
				}

				_pitch = lockedRect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)lockedRect.pBits;
			}

		case Texture3D:
			{
				D3DLOCKED_BOX box;
				DX_CHECK(m_staging3d->LockBox(_lod, &box, NULL, 0) );
				DX_CHECK(m_staging3d->AddDirtyBox(NULL) );
				_pitch      = box.RowPitch;
				_slicePitch = box.SlicePitch;
				return (uint8_t*)box.pBits;
			}

		case TextureCube:
			{
				D3DLOCKED_RECT lockedRect;

				if (NULL != _rect)
				{
					RECT rect;
					rect.left   = _rect->m_x;
					rect.top    = _rect->m_y;
					rect.right  = rect.left + _rect->m_width;
					rect.bottom = rect.top + _rect->m_height;
					DX_CHECK(m_stagingCube->LockRect(D3DCUBEMAP_FACES(_side), _lod, &lockedRect, &rect, 0) );
					DX_CHECK(m_textureCube->AddDirtyRect(D3DCUBEMAP_FACES(_side), &rect) );
				}
				else
				{
					DX_CHECK(m_stagingCube->LockRect(D3DCUBEMAP_FACES(_side), _lod, &lockedRect, NULL, 0) );
					DX_CHECK(m_textureCube->AddDirtyRect(D3DCUBEMAP_FACES(_side), NULL) );
				}

				_pitch = lockedRect.Pitch;
				_slicePitch = 0;
				return (uint8_t*)lockedRect.pBits;
			}
		}

		BX_CHECK(false, "You should not be here.");
		_pitch      = 0;
		_slicePitch = 0;
		return NULL;
	}

	void TextureD3D9::unlock(uint8_t _side, uint8_t _lod)
	{
		IDirect3DDevice9* device = s_renderD3D9->m_device;

		switch (m_type)
		{
		case Texture2D:
			{
				DX_CHECK(m_staging2d->UnlockRect(_lod) );
				DX_CHECK(device->UpdateTexture(m_staging2d, m_texture2d) );
			}
			return;

		case Texture3D:
			{
				DX_CHECK(m_staging3d->UnlockBox(_lod) );
				DX_CHECK(device->UpdateTexture(m_staging3d, m_texture3d) );
			}
			return;

		case TextureCube:
			{
				DX_CHECK(m_stagingCube->UnlockRect(D3DCUBEMAP_FACES(_side), _lod) );
				DX_CHECK(device->UpdateTexture(m_stagingCube, m_textureCube) );
			}
			return;
		}

		BX_CHECK(false, "You should not be here.");
	}

	void TextureD3D9::dirty(uint8_t _side, const Rect& _rect, uint16_t _z, uint16_t _depth)
	{
		switch (m_type)
		{
		case Texture2D:
			{
				RECT rect;
				rect.left   = _rect.m_x;
				rect.top    = _rect.m_y;
				rect.right  = rect.left + _rect.m_width;
				rect.bottom = rect.top + _rect.m_height;
				DX_CHECK(m_texture2d->AddDirtyRect(&rect) );
			}
			return;

		case Texture3D:
			{
				D3DBOX box;
				box.Left   = _rect.m_x;
				box.Top    = _rect.m_y;
				box.Right  = box.Left + _rect.m_width;
				box.Bottom = box.Top + _rect.m_height;
				box.Front  = _z;
				box.Back   = box.Front + _depth;
				DX_CHECK(m_texture3d->AddDirtyBox(&box) );
			}
			return;

		case TextureCube:
			{
				RECT rect;
				rect.left   = _rect.m_x;
				rect.top    = _rect.m_y;
				rect.right  = rect.left + _rect.m_width;
				rect.bottom = rect.top + _rect.m_height;
				DX_CHECK(m_textureCube->AddDirtyRect(D3DCUBEMAP_FACES(_side), &rect) );
			}
			return;
		}

		BX_CHECK(false, "You should not be here.");
	}

	IDirect3DSurface9* TextureD3D9::getSurface(uint8_t _side, uint8_t _mip) const
	{
		IDirect3DSurface9* surface = NULL;

		switch (m_type)
		{
		case Texture2D:
			DX_CHECK(m_texture2d->GetSurfaceLevel(_mip, &surface) );
			break;

		case Texture3D:
			BX_CHECK(false, "");
			break;

		case TextureCube:
			DX_CHECK(m_textureCube->GetCubeMapSurface(D3DCUBEMAP_FACES(_side), _mip, &surface) );
			break;
		}

		return surface;
	}

	void TextureD3D9::create(const Memory* _mem, uint32_t _flags, uint8_t _skip)
	{
		ImageContainer imageContainer;

		if (imageParse(imageContainer, _mem->data, _mem->size) )
		{
			uint8_t numMips = imageContainer.m_numMips;
			const uint8_t startLod = uint8_t(bx::uint32_min(_skip, numMips-1) );
			numMips -= startLod;
			const ImageBlockInfo& blockInfo = getBlockInfo(TextureFormat::Enum(imageContainer.m_format) );
			const uint32_t textureWidth  = bx::uint32_max(blockInfo.blockWidth,  imageContainer.m_width >>startLod);
			const uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height>>startLod);

			m_flags   = _flags;
			m_width   = textureWidth;
			m_height  = textureHeight;
			m_depth   = imageContainer.m_depth;
			m_numMips = numMips;
			m_requestedFormat =
			m_textureFormat   = uint8_t(imageContainer.m_format);

			const TextureFormatInfo& tfi = s_textureFormat[m_requestedFormat];
			uint8_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
			if (D3DFMT_UNKNOWN == tfi.m_fmt)
			{
				m_textureFormat = (uint8_t)TextureFormat::BGRA8;
				bpp = 32;
			}

			if (imageContainer.m_cubeMap)
			{
				createCubeTexture(textureWidth, numMips);
			}
			else if (imageContainer.m_depth > 1)
			{
				createVolumeTexture(textureWidth, textureHeight, imageContainer.m_depth, numMips);
			}
			else
			{
				createTexture(textureWidth, textureHeight, numMips);
			}

			if (imageContainer.m_srgb)
			{
				m_flags |= BGFX_TEXTURE_SRGB;
			}

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s%s."
				, this - s_renderD3D9->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, textureWidth
				, textureHeight
				, imageContainer.m_cubeMap ? "x6" : ""
				, 0 != (m_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
				);

			if (0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY) )
			{
				return;
			}

			// For BC4 and B5 in DX9 LockRect returns wrong number of
			// bytes. If actual mip size is used it causes memory corruption.
			// http://www.aras-p.info/texts/D3D9GPUHacks.html#3dc
			const bool useMipSize = true
							&& imageContainer.m_format != TextureFormat::BC4
							&& imageContainer.m_format != TextureFormat::BC5
							;

			const bool convert = m_textureFormat != m_requestedFormat;

			for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width     = textureWidth;
				uint32_t height    = textureHeight;
				uint32_t depth     = imageContainer.m_depth;
				uint32_t mipWidth  = imageContainer.m_width;
				uint32_t mipHeight = imageContainer.m_height;

				for (uint8_t lod = 0, num = numMips; lod < num; ++lod)
				{
					width     = bx::uint32_max(1, width);
					height    = bx::uint32_max(1, height);
					depth     = bx::uint32_max(1, depth);
					mipWidth  = bx::uint32_max(blockInfo.blockWidth,  mipWidth);
					mipHeight = bx::uint32_max(blockInfo.blockHeight, mipHeight);
					uint32_t mipSize = width*height*depth*bpp/8;

					ImageMip mip;
					if (imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						uint32_t pitch;
						uint32_t slicePitch;
						uint8_t* bits = lock(side, lod, pitch, slicePitch);

						if (convert)
						{
							if (width  != mipWidth
							||  height != mipHeight)
							{
								uint32_t srcpitch = mipWidth*bpp/8;

								uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, srcpitch*mipHeight);
								imageDecodeToBgra8(temp
										, mip.m_data
										, mip.m_width
										, mip.m_height
										, srcpitch
										, mip.m_format
										);

								bx::memCopy(bits, temp, pitch, height, srcpitch, pitch);

								BX_FREE(g_allocator, temp);
							}
							else
							{
								imageDecodeToBgra8(bits, mip.m_data, mip.m_width, mip.m_height, pitch, mip.m_format);
							}
						}
						else
						{
							uint32_t size = useMipSize ? mip.m_size : mipSize;
							memcpy(bits, mip.m_data, size);
						}

						unlock(side, lod);
					}

					width     >>= 1;
					height    >>= 1;
					depth     >>= 1;
					mipWidth  >>= 1;
					mipHeight >>= 1;
				}
			}
		}
	}

	void TextureD3D9::updateBegin(uint8_t _side, uint8_t _mip)
	{
		uint32_t slicePitch;
		s_renderD3D9->m_updateTextureSide = _side;
		s_renderD3D9->m_updateTextureMip  = _mip;
		s_renderD3D9->m_updateTextureBits = lock(_side, _mip, s_renderD3D9->m_updateTexturePitch, slicePitch);
	}

	void TextureD3D9::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		const uint32_t bpp = getBitsPerPixel(TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t dstpitch  = s_renderD3D9->m_updateTexturePitch;
		uint8_t* bits = s_renderD3D9->m_updateTextureBits + _rect.m_y*dstpitch + _rect.m_x*bpp/8;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			imageDecodeToBgra8(temp, data, _rect.m_width, _rect.m_height, srcpitch, TextureFormat::Enum(m_requestedFormat) );
			data = temp;
		}

		{
			uint8_t* src = data;
			uint8_t* dst = bits;
			for (uint32_t yy = 0, height = _rect.m_height; yy < height; ++yy)
			{
				memcpy(dst, src, rectpitch);
				src += srcpitch;
				dst += dstpitch;
			}
		}

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}

		if (0 == _mip)
		{
			dirty(_side, _rect, _z, _depth);
		}
	}

	void TextureD3D9::updateEnd()
	{
		unlock(s_renderD3D9->m_updateTextureSide, s_renderD3D9->m_updateTextureMip);
	}

	void TextureD3D9::commit(uint8_t _stage, uint32_t _flags, const float _palette[][4])
	{
		uint32_t flags = 0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & _flags)
			? _flags
			: m_flags
			;
		uint32_t index = (flags & BGFX_TEXTURE_BORDER_COLOR_MASK) >> BGFX_TEXTURE_BORDER_COLOR_SHIFT;
		s_renderD3D9->setSamplerState(_stage, flags, _palette[index]);

		IDirect3DDevice9* device = s_renderD3D9->m_device;
		DX_CHECK(device->SetTexture(_stage, m_ptr) );
		if (4 > _stage)
		{
			DX_CHECK(device->SetTexture(D3DVERTEXTEXTURESAMPLER0 + _stage, m_ptr) );
		}
	}

	void TextureD3D9::resolve() const
	{
		if (NULL != m_surface
		&&  NULL != m_texture2d)
		{
			IDirect3DSurface9* surface = getSurface();
			DX_CHECK(s_renderD3D9->m_device->StretchRect(m_surface
				, NULL
				, surface
				, NULL
				, D3DTEXF_LINEAR
				) );
			DX_RELEASE(surface, 1);
		}
	}

	void TextureD3D9::preReset()
	{
		TextureFormat::Enum fmt = (TextureFormat::Enum)m_textureFormat;
		if (TextureFormat::Unknown != fmt)
		{
			DX_RELEASE(m_ptr, 0);
			DX_RELEASE(m_surface, 0);
		}
	}

	void TextureD3D9::postReset()
	{
		TextureFormat::Enum fmt = (TextureFormat::Enum)m_textureFormat;
		if (TextureFormat::Unknown != fmt)
		{
			switch (m_type)
			{
			default:
			case Texture2D:
				createTexture(m_width, m_height, m_numMips);
				break;

			case Texture3D:
				createVolumeTexture(m_width, m_height, m_depth, m_numMips);
				break;

			case TextureCube:
				createCubeTexture(m_width, m_numMips);
				break;
			}
		}
	}

	void FrameBufferD3D9::create(uint8_t _num, const TextureHandle* _handles)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_color); ++ii)
		{
			m_color[ii] = NULL;
		}
		m_depthStencil = NULL;

		m_num = 0;
		m_needResolve = false;
		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			TextureHandle handle = _handles[ii];
			if (isValid(handle) )
			{
				const TextureD3D9& texture = s_renderD3D9->m_textures[handle.idx];

				if (isDepth( (TextureFormat::Enum)texture.m_textureFormat) )
				{
					m_depthHandle = handle;
					if (NULL != texture.m_surface)
					{
						m_depthStencil = texture.m_surface;
						m_depthStencil->AddRef();
					}
					else
					{
						m_depthStencil = texture.getSurface();
					}
				}
				else
				{
					m_colorHandle[m_num] = handle;
					if (NULL != texture.m_surface)
					{
						m_color[m_num] = texture.m_surface;
						m_color[m_num]->AddRef();
					}
					else
					{
						m_color[m_num] = texture.getSurface();
					}
					m_num++;
				}

				m_needResolve |= (NULL != texture.m_surface) && (NULL != texture.m_texture2d);
			}
		}

		if (0 == m_num)
		{
			createNullColorRT();
		}
	}

	void FrameBufferD3D9::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_depthFormat);

		m_hwnd = (HWND)_nwh;

		m_width  = bx::uint32_max(_width,  16);
		m_height = bx::uint32_max(_height, 16);

		D3DPRESENT_PARAMETERS params;
		memcpy(&params, &s_renderD3D9->m_params, sizeof(D3DPRESENT_PARAMETERS) );
		params.BackBufferWidth  = m_width;
		params.BackBufferHeight = m_height;

		DX_CHECK(s_renderD3D9->m_device->CreateAdditionalSwapChain(&params, &m_swapChain) );
		DX_CHECK(m_swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_color[0]) );

		DX_CHECK(s_renderD3D9->m_device->CreateDepthStencilSurface(
			  params.BackBufferWidth
			, params.BackBufferHeight
			, params.AutoDepthStencilFormat
			, params.MultiSampleType
			, params.MultiSampleQuality
			, FALSE
			, &m_depthStencil
			, NULL
			) );

		m_colorHandle[0].idx = invalidHandle;
		m_denseIdx = _denseIdx;
		m_num = 1;
		m_needResolve = false;
	}

	uint16_t FrameBufferD3D9::destroy()
	{
		if (NULL != m_hwnd)
		{
			DX_RELEASE(m_depthStencil, 0);
			DX_RELEASE(m_color[0],     0);
			DX_RELEASE(m_swapChain,    0);
		}
		else
		{
			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				m_colorHandle[ii].idx = invalidHandle;

				IDirect3DSurface9* ptr = m_color[ii];
				if (NULL != ptr)
				{
					ptr->Release();
					m_color[ii] = NULL;
				}
			}

			if (NULL != m_depthStencil)
			{
				if (0 == m_num)
				{
					IDirect3DSurface9* ptr = m_color[0];
					if (NULL != ptr)
					{
						ptr->Release();
						m_color[0] = NULL;
					}
				}

				m_depthStencil->Release();
				m_depthStencil = NULL;
			}
		}

		m_hwnd = NULL;
		m_num = 0;
		m_depthHandle.idx = invalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	HRESULT FrameBufferD3D9::present()
	{
		return m_swapChain->Present(NULL, NULL, m_hwnd, NULL, 0);
	}

	void FrameBufferD3D9::resolve() const
	{
		if (m_needResolve)
		{
			if (isValid(m_depthHandle) )
			{
				const TextureD3D9& texture = s_renderD3D9->m_textures[m_depthHandle.idx];
				texture.resolve();
			}

			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				const TextureD3D9& texture = s_renderD3D9->m_textures[m_colorHandle[ii].idx];
				texture.resolve();
			}
		}
	}

	void FrameBufferD3D9::preReset()
	{
		if (NULL != m_hwnd)
		{
			DX_RELEASE(m_color[0], 0);
			DX_RELEASE(m_depthStencil, 0);
			DX_RELEASE(m_swapChain, 0);
		}
		else
		{
			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				m_color[ii]->Release();
				m_color[ii] = NULL;
			}

			if (isValid(m_depthHandle) )
			{
				if (0 == m_num)
				{
					m_color[0]->Release();
					m_color[0] = NULL;
				}

				m_depthStencil->Release();
				m_depthStencil = NULL;
			}
		}
	}

	void FrameBufferD3D9::postReset()
	{
		if (NULL != m_hwnd)
		{
			D3DPRESENT_PARAMETERS params;
			memcpy(&params, &s_renderD3D9->m_params, sizeof(D3DPRESENT_PARAMETERS) );
			params.BackBufferWidth  = m_width;
			params.BackBufferHeight = m_height;

			DX_CHECK(s_renderD3D9->m_device->CreateAdditionalSwapChain(&params, &m_swapChain) );
			DX_CHECK(m_swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_color[0]) );
			DX_CHECK(s_renderD3D9->m_device->CreateDepthStencilSurface(params.BackBufferWidth
					, params.BackBufferHeight
					, params.AutoDepthStencilFormat
					, params.MultiSampleType
					, params.MultiSampleQuality
					, FALSE
					, &m_depthStencil
					, NULL
					) );
		}
		else
		{
			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				TextureHandle th = m_colorHandle[ii];

				if (isValid(th) )
				{
					TextureD3D9& texture = s_renderD3D9->m_textures[th.idx];
					if (NULL != texture.m_surface)
					{
						m_color[ii] = texture.m_surface;
						m_color[ii]->AddRef();
					}
					else
					{
						m_color[ii] = texture.getSurface();
					}
				}
			}

			if (isValid(m_depthHandle) )
			{
				TextureD3D9& texture = s_renderD3D9->m_textures[m_depthHandle.idx];
				if (NULL != texture.m_surface)
				{
					m_depthStencil = texture.m_surface;
					m_depthStencil->AddRef();
				}
				else
				{
					m_depthStencil = texture.getSurface();
				}

				if (0 == m_num)
				{
					createNullColorRT();
				}
			}
		}
	}

	void FrameBufferD3D9::createNullColorRT()
	{
		const TextureD3D9& texture = s_renderD3D9->m_textures[m_depthHandle.idx];
		DX_CHECK(s_renderD3D9->m_device->CreateRenderTarget(texture.m_width
			, texture.m_height
			, D3DFMT_NULL
			, D3DMULTISAMPLE_NONE
			, 0
			, false
			, &m_color[0]
			, NULL
			) );
	}

	void TimerQueryD3D9::postReset()
	{
		IDirect3DDevice9* device = s_renderD3D9->m_device;

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_frame); ++ii)
		{
			Frame& frame = m_frame[ii];
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMPDISJOINT, &frame.m_disjoint) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMP,         &frame.m_begin) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMP,         &frame.m_end) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMPFREQ,     &frame.m_freq) );
		}

		m_elapsed   = 0;
		m_frequency = 1;
		m_control.reset();
	}

	void TimerQueryD3D9::preReset()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_frame); ++ii)
		{
			Frame& frame = m_frame[ii];
			DX_RELEASE(frame.m_disjoint, 0);
			DX_RELEASE(frame.m_begin, 0);
			DX_RELEASE(frame.m_end, 0);
			DX_RELEASE(frame.m_freq, 0);
		}
	}

	void TimerQueryD3D9::begin()
	{
		while (0 == m_control.reserve(1) )
		{
			get();
		}

		Frame& frame = m_frame[m_control.m_current];
		frame.m_disjoint->Issue(D3DISSUE_BEGIN);
		frame.m_begin->Issue(D3DISSUE_END);
	}

	void TimerQueryD3D9::end()
	{
		Frame& frame = m_frame[m_control.m_current];
		frame.m_disjoint->Issue(D3DISSUE_END);
		frame.m_freq->Issue(D3DISSUE_END);
		frame.m_end->Issue(D3DISSUE_END);
		m_control.commit(1);
	}

	bool TimerQueryD3D9::get()
	{
		if (0 != m_control.available() )
		{
			Frame& frame = m_frame[m_control.m_read];

			uint64_t timeEnd;
			HRESULT hr = frame.m_end->GetData(&timeEnd, sizeof(timeEnd), 0);
			if (S_OK == hr)
			{
				m_control.consume(1);

				uint64_t timeBegin;
				DX_CHECK(frame.m_begin->GetData(&timeBegin, sizeof(timeBegin), 0) );

				uint64_t freq;
				DX_CHECK(frame.m_freq->GetData(&freq, sizeof(freq), 0) );

				m_frequency = freq;
				m_begin     = timeBegin;
				m_end       = timeEnd;
				m_elapsed   = timeEnd - timeBegin;

				return true;
			}
		}

		return false;
	}

	void OcclusionQueryD3D9::postReset()
	{
		IDirect3DDevice9* device = s_renderD3D9->m_device;

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &query.m_ptr) );
		}
	}

	void OcclusionQueryD3D9::preReset()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			DX_RELEASE(query.m_ptr, 0);
		}
	}

	void OcclusionQueryD3D9::begin(Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		Query& query = m_query[m_control.m_current];
		query.m_ptr->Issue(D3DISSUE_BEGIN);
		query.m_handle = _handle;
	}

	void OcclusionQueryD3D9::end()
	{
		Query& query = m_query[m_control.m_current];
		query.m_ptr->Issue(D3DISSUE_END);
		m_control.commit(1);
	}

	void OcclusionQueryD3D9::resolve(Frame* _render, bool)
	{
		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			uint32_t result;
			HRESULT hr = query.m_ptr->GetData(&result, sizeof(result), 0);
			if (S_FALSE == hr)
			{
				break;
			}

			_render->m_occlusion[query.m_handle.idx] = 0 < result;
			m_control.consume(1);
		}
	}

	void RendererContextD3D9::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		IDirect3DDevice9* device = m_device;

		PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), L"rendererSubmit");

		updateResolution(_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		device->BeginScene();
		if (m_timerQuerySupport)
		{
			m_gpuTimer.begin();
		}

		if (0 < _render->m_iboffset)
		{
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		ViewState viewState(_render, false);

		DX_CHECK(device->SetRenderState(D3DRS_FILLMODE, _render->m_debug&BGFX_DEBUG_WIREFRAME ? D3DFILL_WIREFRAME : D3DFILL_SOLID) );
		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };
		uint32_t blendFactor = 0;

		BlitKey blitKey;
		blitKey.decode(_render->m_blitKeys[0]);
		uint16_t numBlitItems = _render->m_numBlitItems;
		uint16_t blitItem = 0;

		uint8_t primIndex;
		{
			const uint64_t pt = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
			primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
		}
		PrimInfo prim = s_primInfo[primIndex];

		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		invalidateSamplerState();

		if (m_occlusionQuerySupport)
		{
			m_occlusionQuery.resolve(_render);
		}

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = _render->m_num; item < numItems; ++item)
			{
				const bool isCompute = key.decode(_render->m_sortKeys[item], _render->m_viewRemap);
				statsKeyType[isCompute]++;

				if (isCompute)
				{
					BX_CHECK(false, "Compute is not supported on DirectX 9.");
					continue;
				}

				const RenderDraw& draw = _render->m_renderItem[_render->m_sortValues[item] ].draw;

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				if (isValid(draw.m_occlusionQuery)
				&&  !hasOcclusionQuery
				&&  !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) ) )
				{
					continue;
				}

				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (key.m_view != view)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					PIX_ENDEVENT();
					PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), s_viewNameW[key.m_view]);
					if (item > 0)
					{
						BGFX_PROFILER_END();
					}
					BGFX_PROFILER_BEGIN_DYNAMIC(s_viewName[key.m_view]);

					view = key.m_view;
					programIdx = invalidHandle;

					if (_render->m_fb[view].idx != fbh.idx)
					{
						fbh = _render->m_fb[view];
						setFrameBuffer(fbh);
					}

					viewState.m_rect        = _render->m_rect[view];
					const Rect& scissorRect = _render->m_scissor[view];
					viewHasScissor  = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;

					D3DVIEWPORT9 vp;
					vp.X      = viewState.m_rect.m_x;
					vp.Y      = viewState.m_rect.m_y;
					vp.Width  = viewState.m_rect.m_width;
					vp.Height = viewState.m_rect.m_height;
					vp.MinZ = 0.0f;
					vp.MaxZ = 1.0f;
					DX_CHECK(device->SetViewport(&vp) );

					Clear& clear = _render->m_clear[view];

					if (BGFX_CLEAR_NONE != (clear.m_flags & BGFX_CLEAR_MASK) )
					{
						clearQuad(_clearQuad, viewState.m_rect, clear, _render->m_colorPalette);
						prim = s_primInfo[BX_COUNTOF(s_primName)]; // Force primitive type update after clear quad.
					}

					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS) );
					DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );

					for (; blitItem < numBlitItems && blitKey.m_view <= view; blitItem++)
					{
						const BlitItem& blit = _render->m_blitItem[blitItem];
						blitKey.decode(_render->m_blitKeys[blitItem+1]);

						const TextureD3D9& src = m_textures[blit.m_src.idx];
						const TextureD3D9& dst = m_textures[blit.m_dst.idx];

						uint32_t srcWidth  = bx::uint32_min(src.m_width,  blit.m_srcX + blit.m_width)  - blit.m_srcX;
						uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
						uint32_t dstWidth  = bx::uint32_min(dst.m_width,  blit.m_dstX + blit.m_width)  - blit.m_dstX;
						uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
						uint32_t width     = bx::uint32_min(srcWidth,  dstWidth);
						uint32_t height    = bx::uint32_min(srcHeight, dstHeight);

						RECT srcRect = { LONG(blit.m_srcX), LONG(blit.m_srcY), LONG(blit.m_srcX + width), LONG(blit.m_srcY + height) };
						RECT dstRect = { LONG(blit.m_dstX), LONG(blit.m_dstY), LONG(blit.m_dstX + width), LONG(blit.m_dstY + height) };

						IDirect3DSurface9* srcSurface = src.getSurface(uint8_t(blit.m_srcZ), blit.m_srcMip);
						IDirect3DSurface9* dstSurface = dst.getSurface(uint8_t(blit.m_dstZ), blit.m_dstMip);

						// UpdateSurface (pool src: SYSTEMMEM, dst: DEFAULT)
						// s/d T   RTT RT
						// T   y   y   y
						// RTT -   -   -
						// RT  -   -   -
						//
						// StretchRect (pool src and dst must be DEFAULT)
						// s/d T   RTT RT
						// T   -   y   y
						// RTT -   y   y
						// RT  -   y   y
						//
						// GetRenderTargetData (dst must be SYSTEMMEM)

						bool depth = isDepth(TextureFormat::Enum(src.m_textureFormat) );
						HRESULT hr = m_device->StretchRect(srcSurface
							, depth ? NULL : &srcRect
							, dstSurface
							, depth ? NULL : &dstRect
							, D3DTEXF_NONE
							);
						if (FAILED(hr) )
						{
							hr = m_device->GetRenderTargetData(srcSurface, dstSurface);
							BX_WARN(SUCCEEDED(hr), "StretchRect and GetRenderTargetData failed %x.", hr);
						}

						srcSurface->Release();
						dstSurface->Release();
					}
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, viewHasScissor) );
						if (viewHasScissor)
						{
							RECT rc;
							rc.left   = viewScissorRect.m_x;
							rc.top    = viewScissorRect.m_y;
							rc.right  = viewScissorRect.m_x + viewScissorRect.m_width;
							rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
							DX_CHECK(device->SetScissorRect(&rc) );
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.intersect(viewScissorRect, _render->m_rectCache.m_cache[scissor]);
						DX_CHECK(device->SetRenderState(D3DRS_SCISSORTESTENABLE, true) );
						RECT rc;
						rc.left   = scissorRect.m_x;
						rc.top    = scissorRect.m_y;
						rc.right  = scissorRect.m_x + scissorRect.m_width;
						rc.bottom = scissorRect.m_y + scissorRect.m_height;
						DX_CHECK(device->SetScissorRect(&rc) );
					}
				}

				if (0 != changedStencil)
				{
					bool enable = 0 != newStencil;
					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, enable) );

					if (0 != newStencil)
					{
						uint32_t fstencil = unpackStencil(0, newStencil);
						uint32_t bstencil = unpackStencil(1, newStencil);
						uint8_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
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

						for (uint8_t ii = 0, num = frontAndBack+1; ii < num; ++ii)
						{
							uint32_t stencil = unpackStencil(ii, newStencil);
							uint32_t changed = unpackStencil(ii, changedStencil);

							if ( (BGFX_STENCIL_TEST_MASK|BGFX_STENCIL_FUNC_REF_MASK|BGFX_STENCIL_FUNC_RMASK_MASK) & changed)
							{
								uint32_t func = (stencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT;
								DX_CHECK(device->SetRenderState(s_stencilFuncRs[ii], s_cmpFunc[func]) );
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

				if ( (0
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_DEPTH_WRITE
					 | BGFX_STATE_DEPTH_TEST_MASK
					 | BGFX_STATE_RGB_WRITE
					 | BGFX_STATE_ALPHA_WRITE
					 | BGFX_STATE_BLEND_MASK
					 | BGFX_STATE_BLEND_EQUATION_MASK
					 | BGFX_STATE_ALPHA_REF_MASK
					 | BGFX_STATE_PT_MASK
					 | BGFX_STATE_POINT_SIZE_MASK
					 | BGFX_STATE_MSAA
					 ) & changedFlags)
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
							DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, s_cmpFunc[func]) );
						}
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
					}

					if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
					{
						DX_CHECK(device->SetRenderState(D3DRS_POINTSIZE, castfu( (float)( (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) ) ) );
					}

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

					if ( (BGFX_STATE_BLEND_MASK|BGFX_STATE_BLEND_EQUATION_MASK) & changedFlags
					||  blendFactor != draw.m_rgba)
					{
						bool enabled = !!(BGFX_STATE_BLEND_MASK & newFlags);
						DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, enabled) );

						if (enabled)
						{
							const uint32_t blend    = uint32_t( (newFlags&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT);
							const uint32_t equation = uint32_t( (newFlags&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

							const uint32_t srcRGB  = (blend    )&0xf;
							const uint32_t dstRGB  = (blend>> 4)&0xf;
							const uint32_t srcA    = (blend>> 8)&0xf;
							const uint32_t dstA    = (blend>>12)&0xf;

							const uint32_t equRGB = (equation   )&0x7;
							const uint32_t equA   = (equation>>3)&0x7;

 							DX_CHECK(device->SetRenderState(D3DRS_SRCBLEND,  s_blendFactor[srcRGB].m_src) );
							DX_CHECK(device->SetRenderState(D3DRS_DESTBLEND, s_blendFactor[dstRGB].m_dst) );
							DX_CHECK(device->SetRenderState(D3DRS_BLENDOP,   s_blendEquation[equRGB]) );

							const bool separate = srcRGB != srcA || dstRGB != dstA || equRGB != equA;

							DX_CHECK(device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, separate) );
							if (separate)
							{
								DX_CHECK(device->SetRenderState(D3DRS_SRCBLENDALPHA,  s_blendFactor[srcA].m_src) );
								DX_CHECK(device->SetRenderState(D3DRS_DESTBLENDALPHA, s_blendFactor[dstA].m_dst) );
								DX_CHECK(device->SetRenderState(D3DRS_BLENDOPALPHA,   s_blendEquation[equA]) );
							}

							if ( (s_blendFactor[srcRGB].m_factor || s_blendFactor[dstRGB].m_factor)
							&&  blendFactor != draw.m_rgba)
							{
								const uint32_t rgba = draw.m_rgba;
								D3DCOLOR color = D3DCOLOR_RGBA(rgba>>24
															, (rgba>>16)&0xff
															, (rgba>> 8)&0xff
															, (rgba    )&0xff
															);
								DX_CHECK(device->SetRenderState(D3DRS_BLENDFACTOR, color) );
							}
						}

						blendFactor = draw.m_rgba;
					}

					const uint64_t pt = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					prim = s_primInfo[primIndex];
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_constBegin < draw.m_constEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer, draw.m_constBegin, draw.m_constEnd);

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
						ProgramD3D9& program = m_program[programIdx];
						device->SetVertexShader(program.m_vsh->m_vertexShader);
						device->SetPixelShader(program.m_fsh->m_pixelShader);
					}

					programChanged =
						constantsChanged = true;
				}

				if (invalidHandle != programIdx)
				{
					ProgramD3D9& program = m_program[programIdx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						UniformBuffer* fcb = program.m_fsh->m_constantBuffer;
						if (NULL != fcb)
						{
							commit(*fcb);
						}
					}

					viewState.setPredefined<4>(this, view, 0, program, _render, draw);
				}

				{
					for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
					{
						const Binding& bind = draw.m_bind[stage];
						Binding& current = currentState.m_bind[stage];
						if (current.m_idx != bind.m_idx
						||  current.m_un.m_draw.m_textureFlags != bind.m_un.m_draw.m_textureFlags
						||  programChanged)
						{
							if (invalidHandle != bind.m_idx)
							{
								m_textures[bind.m_idx].commit(stage, bind.m_un.m_draw.m_textureFlags, _render->m_colorPalette);
							}
							else
							{
								DX_CHECK(device->SetTexture(stage, NULL) );
							}
						}

						current = bind;
					}
				}

				if (programChanged
				||  currentState.m_vertexBuffer.idx != draw.m_vertexBuffer.idx
				||  currentState.m_instanceDataBuffer.idx != draw.m_instanceDataBuffer.idx
				||  currentState.m_instanceDataOffset != draw.m_instanceDataOffset
				||  currentState.m_instanceDataStride != draw.m_instanceDataStride)
				{
					currentState.m_vertexBuffer = draw.m_vertexBuffer;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride = draw.m_instanceDataStride;

					uint16_t handle = draw.m_vertexBuffer.idx;
					if (invalidHandle != handle)
					{
						const VertexBufferD3D9& vb = m_vertexBuffers[handle];

						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDeclD3D9& vertexDecl = m_vertexDecls[decl];
						DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, vertexDecl.m_decl.m_stride) );

						if (isValid(draw.m_instanceDataBuffer)
						&&  m_instancingSupport)
						{
							const VertexBufferD3D9& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							DX_CHECK(device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA|draw.m_numInstances) );
							DX_CHECK(device->SetStreamSourceFreq(1, UINT(D3DSTREAMSOURCE_INSTANCEDATA|1) ) );
							DX_CHECK(device->SetStreamSource(1, inst.m_ptr, draw.m_instanceDataOffset, draw.m_instanceDataStride) );

							IDirect3DVertexDeclaration9* ptr = createVertexDeclaration(vertexDecl.m_decl, draw.m_instanceDataStride/16);
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

				if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = draw.m_indexBuffer;

					uint16_t handle = draw.m_indexBuffer.idx;
					if (invalidHandle != handle)
					{
						const IndexBufferD3D9& ib = m_indexBuffers[handle];
						DX_CHECK(device->SetIndices(ib.m_ptr) );
					}
					else
					{
						DX_CHECK(device->SetIndices(NULL) );
					}
				}

				if (isValid(currentState.m_vertexBuffer) )
				{
					uint32_t numVertices = draw.m_numVertices;
					if (UINT32_MAX == numVertices)
					{
						const VertexBufferD3D9& vb = m_vertexBuffers[currentState.m_vertexBuffer.idx];
						uint16_t decl = !isValid(vb.m_decl) ? draw.m_vertexDecl.idx : vb.m_decl.idx;
						const VertexDeclD3D9& vertexDecl = m_vertexDecls[decl];
						numVertices = vb.m_size/vertexDecl.m_decl.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(_render, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indexBuffer) )
					{
						if (UINT32_MAX == draw.m_numIndices)
						{
							const IndexBufferD3D9& ib = m_indexBuffers[draw.m_indexBuffer.idx];
							const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
							numIndices        = ib.m_size/indexSize;
							numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							DX_CHECK(device->DrawIndexedPrimitive(prim.m_type
								, draw.m_startVertex
								, 0
								, numVertices
								, 0
								, numPrimsSubmitted
								) );
						}
						else if (prim.m_min <= draw.m_numIndices)
						{
							numIndices        = draw.m_numIndices;
							numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							DX_CHECK(device->DrawIndexedPrimitive(prim.m_type
								, draw.m_startVertex
								, 0
								, numVertices
								, draw.m_startIndex
								, numPrimsSubmitted
								) );
						}
					}
					else
					{
						numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
						numInstances      = draw.m_numInstances;
						numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

						DX_CHECK(device->DrawPrimitive(prim.m_type
							, draw.m_startVertex
							, numPrimsSubmitted
							) );
					}

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end();
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumIndices += numIndices;
				}
			}

			if (0 < _render->m_num)
			{
				if (0 != (m_resolution.m_flags & BGFX_RESET_FLUSH_AFTER_RENDER) )
				{
					m_flushQuery->Issue(D3DISSUE_END);
					m_flushQuery->GetData(NULL, 0, D3DGETDATA_FLUSH);
				}

				captureElapsed = -bx::getHPCounter();
				capture();
				captureElapsed += bx::getHPCounter();

				BGFX_PROFILER_END();
			}
		}

		PIX_ENDEVENT();

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin = last;

		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		if (m_timerQuerySupport)
		{
			m_gpuTimer.end();

			while (m_gpuTimer.get() )
			{
				double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
				elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
				maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
			}
			maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);
		}

		const int64_t timerFreq = bx::getHPFrequency();

		perfStats.cpuTimeEnd   = now;
		perfStats.cpuTimerFreq = timerFreq;
		perfStats.gpuTimeBegin = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd   = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq = m_gpuTimer.m_frequency;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugstats");

			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + timerFreq;

				double freq = double(timerFreq);
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f, " %s / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					);

				const D3DADAPTER_IDENTIFIER9& identifier = m_identifier;
				tvm.printf(0, pos++, 0x8f, " Device: %s (%s)", identifier.Description, identifier.Driver);

				char processMemoryUsed[16];
				bx::prettify(processMemoryUsed, BX_COUNTOF(processMemoryUsed), bx::getProcessMemoryUsed() );
				tvm.printf(0, pos++, 0x8f, " Memory: %s (process) ", processMemoryUsed);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8e, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.m_flags&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "    Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] %c GPU %7.4f [ms] (latency %d)"
					, _render->m_num
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					, elapsedCpuMs > maxGpuElapsed ? '>' : '<'
					, maxGpuElapsed
					, maxGpuLatency
					);
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < BX_COUNTOF(s_primName); ++ii)
				{
					tvm.printf(10, pos++, 0x8e, "   %10s: %7d (#inst: %5d), submitted: %7d"
						, s_primName[ii]
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				tvm.printf(10, pos++, 0x8e, "      Indices: %7d ", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8e, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "     Capture: %7.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);

			PIX_ENDEVENT();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			PIX_ENDEVENT();
		}

		device->EndScene();
	}
} /* namespace d3d9 */ } // namespace bgfx

#else

namespace bgfx { namespace d3d9
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace d3d9 */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D9

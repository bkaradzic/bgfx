/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D9
#	include "renderer_d3d9.h"
#	include <bx/pixelformat.h>

namespace bgfx { namespace d3d9
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];
	static char    s_viewName [BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

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
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo)-1);

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
		{ D3DFMT_UNKNOWN       }, // ATC,
		{ D3DFMT_UNKNOWN       }, // ATCE,
		{ D3DFMT_UNKNOWN       }, // ATCI,
		{ D3DFMT_UNKNOWN       }, // ASTC4x4,
		{ D3DFMT_UNKNOWN       }, // ASTC5x5,
		{ D3DFMT_UNKNOWN       }, // ASTC6x6,
		{ D3DFMT_UNKNOWN       }, // ASTC8x5,
		{ D3DFMT_UNKNOWN       }, // ASTC8x6,
		{ D3DFMT_UNKNOWN       }, // ASTC10x5,
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
		{ D3DFMT_UNKNOWN       }, // RGB8
		{ D3DFMT_UNKNOWN       }, // RGB8I
		{ D3DFMT_UNKNOWN       }, // RGB8U
		{ D3DFMT_UNKNOWN       }, // RGB8S
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
		{ D3DFMT_UNKNOWN       }, // RG11B10F
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
		{ D3DFMT_ATOC, 0,                     D3DRTYPE_SURFACE, false },
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

	static const D3DVERTEXELEMENT9 s_attrib[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,       0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,      0 },
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,     0 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        0 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        1 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        2 },
		{ 0, 0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,        3 },
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

	static D3DVERTEXELEMENT9* fillVertexLayout(uint8_t _stream, D3DVERTEXELEMENT9* _out, const VertexLayout& _layout)
	{
		D3DVERTEXELEMENT9* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _layout.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				bool asInt;
				_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);

				bx::memCopy(elem, &s_attrib[attr], sizeof(D3DVERTEXELEMENT9) );

				elem->Stream = _stream;
				elem->Type   = s_attribType[type][num-1][normalized];
				elem->Offset = _layout.m_offset[attr];
				++elem;
			}
		}

		return elem;
	}

	inline bool isLost(HRESULT _hr)
	{
		return false
			|| _hr == D3DERR_DEVICELOST
			|| _hr == D3DERR_DRIVERINTERNALERROR
#if !defined(D3D_DISABLE_9EX)
			|| _hr == D3DERR_DEVICEHUNG
			|| _hr == D3DERR_DEVICEREMOVED
#endif // !defined(D3D_DISABLE_9EX)
			;
	}

	inline bool useD3D9Pitch(bimg::TextureFormat::Enum _format)
	{
		// Reference(s):
		//  - For BC4 and B5 in DX9 LockRect returns wrong number of
		//    bytes. If actual mip size is used it causes memory corruption.
		//    https://web.archive.org/web/20190207230133/http://www.aras-p.info/texts/D3D9GPUHacks.html
		return true
			&& _format != bimg::TextureFormat::BC4
			&& _format != bimg::TextureFormat::BC5
			;
	}

	static inline uint32_t calcRowPitch(const bimg::ImageBlockInfo& _blockInfo, uint8_t _lod, uint32_t _width)
	{
		const uint8_t blockWidth   = _blockInfo.blockWidth;
		const uint8_t blockHeight  = _blockInfo.blockHeight;
		const uint8_t minBlockX    = _blockInfo.minBlockX;
		const uint8_t bitsPerPixel = _blockInfo.bitsPerPixel;

		// Calculate the row pitch
		const uint32_t minBlkWidth = minBlockX;
		const uint32_t lodBlkWidth = (((_width >> _lod) + blockWidth - 1) / blockWidth);
		const uint32_t rowBlkWidth = bx::max<uint32_t>(minBlkWidth, lodBlkWidth);
		const uint32_t pixBlkWidth = rowBlkWidth * blockWidth * blockHeight;
		const uint32_t rowPitch    = pixBlkWidth * bitsPerPixel / 8u;

		return rowPitch;
	}

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
			, m_atocSupport(false)
			, m_instancingSupport(false)
			, m_occlusionQuerySupport(false)
			, m_timerQuerySupport(false)
			, m_rtMsaa(false)
		{
		}

		~RendererContextD3D9()
		{
		}

		bool init(const Init& _init)
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

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			D3DFORMAT adapterFormat = D3DFMT_X8R8G8B8;

			// Reference(s):
			// - https://web.archive.org/web/20190207230309/https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dpresent-parameters
			bx::memSet(&m_params, 0, sizeof(m_params) );
			m_params.BackBufferWidth  = _init.resolution.width;
			m_params.BackBufferHeight = _init.resolution.height;
			m_params.BackBufferFormat = adapterFormat;
			m_params.BackBufferCount  = bx::clamp<uint8_t>(_init.resolution.numBackBuffers, 2, BGFX_CONFIG_MAX_BACK_BUFFERS);
			m_params.MultiSampleType  = D3DMULTISAMPLE_NONE;
			m_params.MultiSampleQuality = 0;
			m_params.EnableAutoDepthStencil = TRUE;
			m_params.AutoDepthStencilFormat = D3DFMT_D24S8;
			m_params.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

			m_params.FullScreen_RefreshRateInHz = 0;
			m_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			m_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			m_params.hDeviceWindow = NULL;
			m_params.Windowed = true;

			RECT rect;
			GetWindowRect( (HWND)g_platformData.nwh, &rect);
			m_params.BackBufferWidth  = rect.right-rect.left;
			m_params.BackBufferHeight = rect.bottom-rect.top;

			m_d3d9Dll = bx::dlopen("d3d9.dll");

			if (NULL == m_d3d9Dll)
			{
				BX_TRACE("Init error: Failed to load d3d9.dll.");
				goto error;
			}

			errorState = ErrorState::LoadedD3D9;

			m_nvapi.init();

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				D3DPERF_SetMarker  = (PFN_D3DPERF_SET_MARKER )bx::dlsym(m_d3d9Dll, "D3DPERF_SetMarker");
				D3DPERF_BeginEvent = (PFN_D3DPERF_BEGIN_EVENT)bx::dlsym(m_d3d9Dll, "D3DPERF_BeginEvent");
				D3DPERF_EndEvent   = (PFN_D3DPERF_END_EVENT  )bx::dlsym(m_d3d9Dll, "D3DPERF_EndEvent");

				if (NULL == D3DPERF_SetMarker
				||  NULL == D3DPERF_BeginEvent
				||  NULL == D3DPERF_EndEvent)
				{
					BX_TRACE("Failed to initialize PIX events.");

					D3DPERF_SetMarker  = NULL;
					D3DPERF_BeginEvent = NULL;
					D3DPERF_EndEvent   = NULL;
				}
			}

			m_d3d9ex   = NULL;
			m_deviceEx = NULL;

			Direct3DCreate9Ex = (Direct3DCreate9ExFn)bx::dlsym(m_d3d9Dll, "Direct3DCreate9Ex");
			if (BX_ENABLED(BGFX_CONFIG_RENDERER_DIRECT3D9EX)
			&&  NULL != Direct3DCreate9Ex)
			{
				Direct3DCreate9Ex(D3D_SDK_VERSION, &m_d3d9ex);
				if (NULL != m_d3d9ex)
				{
					HRESULT hr = m_d3d9ex->QueryInterface(IID_IDirect3D9, (void**)&m_d3d9);
					if (FAILED(hr) )
					{
						BX_TRACE("Failed to query D3D9 interface 0x%08x.", hr);
						DX_RELEASE(m_d3d9ex, 0);
					}
					else
					{
						m_pool = D3DPOOL_DEFAULT;
					}
				}
			}

			if (NULL == m_d3d9)
			{
				Direct3DCreate9 = (Direct3DCreate9Fn)bx::dlsym(m_d3d9Dll, "Direct3DCreate9");

				if (NULL == Direct3DCreate9)
				{
					BX_TRACE("Init error: Function Direct3DCreate9 not found.");
					goto error;
				}

				m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
				m_pool = D3DPOOL_MANAGED;
			}

			if (NULL == m_d3d9)
			{
				BX_TRACE("Init error: Unable to create Direct3D.");
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
							&&  !bx::strFind(desc.Description, "PerfHUD").isEmpty() )
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

			if (NULL == m_device)
			{
				BX_TRACE("Init error: Unable to create Direct3D9 device.");
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
				BX_TRACE("Init error: Min spec not satisfied.");
				goto error;
			}

			BX_TRACE("Max vertex shader 3.0 instr. slots: %d", m_caps.MaxVertexShader30InstructionSlots);
			BX_TRACE("Max vertex shader constants: %d", m_caps.MaxVertexShaderConst);
			BX_TRACE("Max fragment shader 2.0 instr. slots: %d", m_caps.PS20Caps.NumInstructionSlots);
			BX_TRACE("Max fragment shader 3.0 instr. slots: %d", m_caps.MaxPixelShader30InstructionSlots);
			BX_TRACE("Num simultaneous render targets: %d", m_caps.NumSimultaneousRTs);
			BX_TRACE("Max vertex index: %d", m_caps.MaxVertexIndex);
			BX_TRACE("Max streams: %d", m_caps.MaxStreams);

			g_caps.supported |= ( 0
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_SWAP_CHAIN
				| ( (m_caps.DevCaps2 & D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES) ? BGFX_CAPS_TEXTURE_BLIT : 0)
				| BGFX_CAPS_TEXTURE_READ_BACK
				| (m_occlusionQuerySupport ? BGFX_CAPS_OCCLUSION_QUERY : 0)
				);

			m_caps.NumSimultaneousRTs = bx::uint32_min(m_caps.NumSimultaneousRTs, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);
			m_caps.MaxStreams         = bx::uint32_min(m_caps.MaxStreams,         BGFX_CONFIG_MAX_VERTEX_STREAMS);
			m_caps.MaxAnisotropy      = bx::uint32_max(m_caps.MaxAnisotropy, 1);

			g_caps.limits.maxTextureSize   = uint16_t(bx::uint32_min(m_caps.MaxTextureWidth, m_caps.MaxTextureHeight) );
			g_caps.limits.maxFBAttachments = uint8_t(m_caps.NumSimultaneousRTs);
			g_caps.limits.maxVertexStreams = uint8_t(m_caps.MaxStreams);

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

				m_atocSupport = false
					|| s_extendedFormats[ExtendedFormat::Atoc].m_supported
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

				g_caps.supported |= m_instancingSupport ? BGFX_CAPS_INSTANCING        : 0;
				g_caps.supported |= m_atocSupport       ? BGFX_CAPS_ALPHA_TO_COVERAGE : 0;
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = BGFX_CAPS_FORMAT_TEXTURE_NONE;

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
					, bimg::isDepth(bimg::TextureFormat::Enum(ii) ) ? D3DUSAGE_DEPTHSTENCIL : D3DUSAGE_RENDERTARGET
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

				support |= SUCCEEDED(m_d3d9->CheckDeviceFormat(m_adapter
					, m_deviceType
					, adapterFormat
					, bimg::isDepth(bimg::TextureFormat::Enum(ii) ) ? D3DUSAGE_DEPTHSTENCIL : D3DUSAGE_RENDERTARGET
					, D3DRTYPE_TEXTURE
					, s_textureFormat[ii].m_fmt
					) ) ? BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN : BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[ii] = support;
			}

			m_fmtDepth = D3DFMT_D24S8;

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
				BX_FALLTHROUGH;

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
				BX_FALLTHROUGH;

			case ErrorState::LoadedD3D9:
				m_nvapi.shutdown();
				bx::dlclose(m_d3d9Dll);
				BX_FALLTHROUGH;

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

			m_nvapi.shutdown();
			bx::dlclose(m_d3d9Dll);

			m_initialized = false;
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Direct3D9;
		}

		const char* getRendererName() const override
		{
			if (NULL != m_d3d9ex)
			{
				return BGFX_RENDERER_DIRECT3D9_NAME " Ex";
			}

			return BGFX_RENDERER_DIRECT3D9_NAME;
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) override
		{
			VertexLayout& layout = m_vertexLayouts[_handle.idx];
			bx::memCopy(&layout, &_layout, sizeof(VertexLayout) );
			dump(layout);
		}

		void destroyVertexLayout(VertexLayoutHandle /*_handle*/) override
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t /*_flags*/) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _layoutHandle);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t /*_flags*/) override
		{
			VertexLayoutHandle layoutHandle = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, layoutHandle);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			m_shaders[_handle.idx].create(_mem);
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override
		{
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
			return NULL;
		}

		void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) override
		{
			m_updateTexture = &m_textures[_handle.idx];
			m_updateTexture->updateBegin(_side, _mip);
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_updateTexture->update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
			m_updateTexture->updateEnd();
			m_updateTexture = NULL;
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			TextureD3D9& texture = m_textures[_handle.idx];

			D3DLOCKED_RECT lockedRect;
			DX_CHECK(texture.m_texture2d->LockRect(_mip
				, &lockedRect
				, NULL
				, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY
				) );

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width >>_mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height>>_mip);
			uint32_t srcPitch  = lockedRect.Pitch;
			uint8_t* src       = (uint8_t*)lockedRect.pBits;

			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat) );
			uint8_t* dst      = (uint8_t*)_data;
			uint32_t dstPitch = srcWidth*bpp/8;

			uint32_t pitch = bx::uint32_min(srcPitch, dstPitch);

			for (uint32_t yy = 0, height = srcHeight; yy < height; ++yy)
			{
				bx::memCopy(dst, src, pitch);

				src += srcPitch;
				dst += dstPitch;
			}

			DX_CHECK(texture.m_texture2d->UnlockRect(_mip) );
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureD3D9& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic, bx::ErrorAssert{});

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc, bx::ErrorAssert{});

			texture.destroy(true);
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override
		{
			// Resource ref. counts might be messed up outside of bgfx.
			// Disabling ref. count check once texture is overridden.
			setGraphicsDebuggerPresent(true);
			m_textures[_handle.idx].overrideInternal(_ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			// Resource ref. counts might be messed up outside of bgfx.
			// Disabling ref. count check once texture is overridden.
			setGraphicsDebuggerPresent(true);
			return uintptr_t(m_textures[_handle.idx].m_ptr);
		}

		void destroyTexture(TextureHandle _handle) override
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
		}

		void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override
		{
			uint16_t denseIdx = m_numWindows++;
			m_windows[denseIdx] = _handle;
			m_frameBuffers[_handle.idx].create(denseIdx, _nwh, _width, _height, _format, _depthFormat);
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			uint16_t denseIdx = m_frameBuffers[_handle.idx].destroy();
			if (UINT16_MAX != denseIdx)
			{
				--m_numWindows;
				if (m_numWindows > 1)
				{
					FrameBufferHandle handle = m_windows[m_numWindows];
					m_windows[m_numWindows]  = {kInvalidHandle};
					if (m_numWindows != denseIdx)
					{
						m_windows[denseIdx] = handle;
						m_frameBuffers[handle.idx].m_denseIdx = denseIdx;
					}
				}
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			const uint32_t size = bx::alignUp(g_uniformTypeSize[_type]*_num, 16);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override
		{
			IDirect3DSwapChain9* swapChain = isValid(_handle)
				? m_frameBuffers[_handle.idx].m_swapChain
				: m_swapChain
				;

			if (NULL == swapChain)
			{
				BX_TRACE("Unable to capture screenshot %s.", _filePath);
				return;
			}

			D3DPRESENT_PARAMETERS params;
			DX_CHECK(swapChain->GetPresentParameters(&params));

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

			HWND nwh = params.hDeviceWindow;

			SetWindowPos(nwh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

			DX_CHECK(m_device->GetFrontBufferData(0, surface) );

			SetWindowPos(nwh, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

			D3DLOCKED_RECT rect;
			DX_CHECK(surface->LockRect(&rect
				, NULL
				, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY
				) );

			RECT rc;
			GetClientRect(nwh, &rc);
			POINT point;
			point.x = rc.left;
			point.y = rc.top;
			ClientToScreen(nwh, &point);
			uint8_t* data = (uint8_t*)rect.pBits;
			uint32_t bytesPerPixel = rect.Pitch/dm.Width;

			g_callback->screenShot(_filePath
				, params.BackBufferWidth
				, params.BackBufferHeight
				, rect.Pitch
				, &data[point.y*rect.Pitch+point.x*bytesPerPixel]
				, params.BackBufferHeight*rect.Pitch
				, false
				);

			DX_CHECK(surface->UnlockRect() );
			DX_RELEASE(surface, 0);
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				mbstowcs(&s_viewNameW[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
					, _name
					, BX_COUNTOF(s_viewNameW[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
					);
			}

			bx::strCopy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0]) - BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
				);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			bx::memCopy(m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			m_occlusionQuery.invalidate(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				uint32_t size = _len*sizeof(wchar_t);
				wchar_t* name = (wchar_t*)alloca(size+2);
				mbstowcs(name, _marker, size);
				name[_len] = L'\0';
				PIX_SETMARKER(kColorMarker, name);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			BX_UNUSED(_handle, _name, _len)
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			uint32_t width  = m_params.BackBufferWidth;
			uint32_t height = m_params.BackBufferHeight;

			FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
			setFrameBuffer(fbh, false, false);

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
			VertexLayout& layout = m_vertexLayouts[_blitter.m_vb->layoutHandle.idx];
			DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, layout.m_stride) );
			setInputLayout(layout, 0);

			IndexBufferD3D9& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			DX_CHECK(device->SetIndices(ib.m_ptr) );

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

			PredefinedUniform& predefined = program.m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			m_textures[_blitter.m_texture.idx].commit(0, BGFX_SAMPLER_INTERNAL_DEFAULT, NULL);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers[_blitter.m_ib->handle.idx].update(0, _numIndices * 2, _blitter.m_ib->data, true);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_layout.m_stride, _blitter.m_vb->data, true);

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
			m_maxAnisotropy = !!(_resolution.reset & BGFX_RESET_MAXANISOTROPY)
				? m_caps.MaxAnisotropy
				: 1
				;
			const uint32_t maskFlags = ~(0
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.width            !=  _resolution.width
			||  m_resolution.height           !=  _resolution.height
			|| (m_resolution.reset&maskFlags) != (_resolution.reset&maskFlags) )
			{
				uint32_t flags = _resolution.reset & (~BGFX_RESET_INTERNAL_FORCE);

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				D3DDEVICE_CREATION_PARAMETERS dcp;
				DX_CHECK(m_device->GetCreationParameters(&dcp) );

				D3DDISPLAYMODE dm;
				DX_CHECK(m_d3d9->GetAdapterDisplayMode(dcp.AdapterOrdinal, &dm) );

				m_params.BackBufferFormat = dm.Format;

				m_params.BackBufferWidth  = _resolution.width;
				m_params.BackBufferHeight = _resolution.height;
				m_params.FullScreen_RefreshRateInHz = BGFX_RESET_FULLSCREEN == (m_resolution.reset&BGFX_RESET_FULLSCREEN_MASK) ? 60 : 0;
				m_params.PresentationInterval = !!(m_resolution.reset&BGFX_RESET_VSYNC) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

				updateMsaa();

				Msaa& msaa = s_msaa[(m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];
				m_params.MultiSampleType    = msaa.m_type;
				m_params.MultiSampleQuality = msaa.m_quality;

				preReset();
				DX_CHECK(m_device->Reset(&m_params) );
				postReset();
			}
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true, bool _needPresent = true)
		{
			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx)
			{
				FrameBufferD3D9& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();
			}

			if (!isValid(_fbh) )
			{
				m_needPresent |= _needPresent;
				DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
				for (uint32_t ii = 1, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
				{
					DX_CHECK(m_device->SetRenderTarget(ii, NULL) );
				}
				DX_CHECK(m_device->SetDepthStencilSurface(m_backBufferDepthStencil) );

				DX_CHECK(m_device->SetRenderState(D3DRS_SRGBWRITEENABLE, 0 != (m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER) ) );
			}
			else
			{
				m_frameBuffers[_fbh.idx].set();
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags&kUniformFragmentBit)
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

		void flush()
		{
			m_flushQuery->Issue(D3DISSUE_END);
			m_flushQuery->GetData(NULL, 0, D3DGETDATA_FLUSH);
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			if (NULL != m_swapChain)
			{
				if (NULL != m_deviceEx)
				{
					DX_CHECK(m_deviceEx->WaitForVBlank(0) );
				}

				for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
				{
					HRESULT hr = S_OK;
					if (0 == ii)
					{
						if (m_needPresent)
						{
							hr = m_swapChain->Present(NULL, NULL, (HWND)g_platformData.nwh, NULL, 0);
							m_needPresent = false;
						}
						else
						{
							flush();
						}
					}
					else
					{
						hr = m_frameBuffers[m_windows[ii].idx].present();
					}

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
				}
			}
		}

		void preReset()
		{
			m_needPresent = false;

			invalidateSamplerState();
			m_inputLayoutCache.invalidate();

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				DX_CHECK(m_device->SetTexture(stage, NULL) );
			}

			DX_CHECK(m_device->SetRenderTarget(0, m_backBufferColor) );
			for (uint32_t ii = 1, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
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

		void setSamplerState(uint8_t _stage, uint64_t _flags, const float _rgba[4])
		{
			const uint64_t flags = _flags&( (~BGFX_SAMPLER_RESERVED_MASK) | BGFX_SAMPLER_BITS_MASK | BGFX_TEXTURE_SRGB);
			BX_ASSERT(_stage < BX_COUNTOF(m_samplerFlags), "");
			if (m_samplerFlags[_stage] != flags)
			{
				m_samplerFlags[_stage] = flags;
				IDirect3DDevice9* device = m_device;
				D3DTEXTUREADDRESS tau = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
				D3DTEXTUREADDRESS tav = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
				D3DTEXTUREADDRESS taw = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
				D3DTEXTUREFILTERTYPE minFilter = s_textureFilter[(_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT];
				D3DTEXTUREFILTERTYPE magFilter = s_textureFilter[(_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT];
				D3DTEXTUREFILTERTYPE mipFilter = s_textureFilter[(_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT];

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
			if (m_resolution.reset&BGFX_RESET_CAPTURE)
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
					bx::memCopy(&handle, _uniformBuffer.read(sizeof(UniformHandle) ), sizeof(UniformHandle) );
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
				case UniformType::_uniform|kUniformFragmentBit: \
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

				case UniformType::Mat3|kUniformFragmentBit:
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

				CASE_IMPLEMENT_UNIFORM(Sampler, I, int);
				CASE_IMPLEMENT_UNIFORM(Vec4,    F, float);
				CASE_IMPLEMENT_UNIFORM(Mat4,    F, float);

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

				VertexBufferD3D9& vb = m_vertexBuffers[_clearQuad.m_vb.idx];
				VertexLayout& layout = _clearQuad.m_layout;
				uint32_t stride = _clearQuad.m_layout.m_stride;

				ProgramD3D9& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				device->SetVertexShader(program.m_vsh->m_vertexShader);
				device->SetPixelShader(program.m_fsh->m_pixelShader);

				float mrtClearDepth[4] = { _clear.m_depth };
				DX_CHECK(device->SetVertexShaderConstantF(0, mrtClearDepth, 1));

				float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];

				if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
				{
					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE - 1, _clear.m_index[ii]);
						bx::memCopy(mrtClearColor[ii], _palette[index], 16);
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
						bx::memCopy(mrtClearColor[ii], rgba, 16);
					}
				}

				DX_CHECK(device->SetPixelShaderConstantF(0, mrtClearColor[0], numMrt));

				DX_CHECK(device->SetStreamSource(0, vb.m_ptr, 0, stride) );
				DX_CHECK(device->SetStreamSourceFreq(0, 1) );
				DX_CHECK(device->SetStreamSource(1, NULL, 0, 0) );
				setInputLayout(layout, 0);
				DX_CHECK(device->SetIndices(NULL) );
				DX_CHECK(device->DrawPrimitive(D3DPT_TRIANGLESTRIP
					, 0
					, 2
					) );
			}
		}

		void setInputLayout(uint8_t _numStreams, const VertexLayout** _layouts, uint16_t _numInstanceData)
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_numInstanceData);
			for (uint8_t stream = 0; stream < _numStreams; ++stream)
			{
				murmur.add(_layouts[stream]->m_hash);
			}
			uint64_t layoutHash = murmur.end();

			IDirect3DVertexDeclaration9* layout = m_inputLayoutCache.find(layoutHash);
			if (NULL == layout)
			{
				D3DVERTEXELEMENT9 vertexElements[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
				D3DVERTEXELEMENT9* elem = vertexElements;

				for (uint8_t stream = 0; stream < _numStreams; ++stream)
				{
					elem = fillVertexLayout(stream, elem, *_layouts[stream]);
				}

				const D3DVERTEXELEMENT9 inst = { _numStreams, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };

				for (uint8_t ii = 0; ii < _numInstanceData; ++ii)
				{
					bx::memCopy(elem, &inst, sizeof(D3DVERTEXELEMENT9) );
					elem->UsageIndex = uint8_t(7-ii); // TEXCOORD7 = i_data0, TEXCOORD6 = i_data1, etc.
					elem->Offset = ii*16;
					++elem;
				}

				bx::memCopy(elem, &s_attrib[Attrib::Count], sizeof(D3DVERTEXELEMENT9) );

				DX_CHECK(m_device->CreateVertexDeclaration(vertexElements, &layout) );

				m_inputLayoutCache.add(layoutHash, layout);
			}

			DX_CHECK(m_device->SetVertexDeclaration(layout) );
		}

		void setInputLayout(const VertexLayout& _layout, uint16_t _numInstanceData)
		{
			const VertexLayout* layouts[1] = { &_layout };
			setInputLayout(BX_COUNTOF(layouts), layouts, _numInstanceData);
		}

		D3DCAPS9 m_caps;

		IDirect3D9Ex* m_d3d9ex;
		IDirect3DDevice9Ex* m_deviceEx;

		IDirect3D9*        m_d3d9;
		IDirect3DDevice9*  m_device;
		IDirect3DQuery9*   m_flushQuery;
		TimerQueryD3D9     m_gpuTimer;
		OcclusionQueryD3D9 m_occlusionQuery;
		D3DPOOL m_pool;

		IDirect3DSwapChain9* m_swapChain;

		bool m_needPresent;
		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IDirect3DSurface9* m_backBufferColor;
		IDirect3DSurface9* m_backBufferDepthStencil;

		IDirect3DTexture9* m_captureTexture;
		IDirect3DSurface9* m_captureSurface;
		IDirect3DSurface9* m_captureResolve;

		IDirect3DVertexDeclaration9* m_instanceDataDecls[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

		void* m_d3d9Dll;
		NvApi m_nvapi;
		uint32_t m_adapter;
		D3DDEVTYPE m_deviceType;
		D3DPRESENT_PARAMETERS m_params;
		uint32_t m_maxAnisotropy;
		D3DADAPTER_IDENTIFIER9 m_identifier;
		Resolution m_resolution;

		bool m_initialized;
		bool m_amd;
		bool m_nvidia;
		bool m_atocSupport;
		bool m_instancingSupport;
		bool m_occlusionQuerySupport;
		bool m_timerQuerySupport;

		D3DFORMAT m_fmtDepth;

		IndexBufferD3D9 m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferD3D9 m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderD3D9 m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramD3D9 m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureD3D9 m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferD3D9 m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		uint64_t m_samplerFlags[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		TextureD3D9* m_updateTexture;
		uint8_t* m_updateTextureBits;
		uint32_t m_updateTexturePitch;
		uint8_t m_updateTextureSide;
		uint8_t m_updateTextureMip;

		StateCacheT<IDirect3DVertexDeclaration9> m_inputLayoutCache;

		TextVideoMem m_textVideoMem;

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;
	};

	static RendererContextD3D9* s_renderD3D9;

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderD3D9 = BX_NEW(g_allocator, RendererContextD3D9);
		if (!s_renderD3D9->init(_init) )
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

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL  pool  = s_renderD3D9->m_pool;

		if (NULL == _data)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
			m_dynamic = (uint8_t*)BX_ALLOC(g_allocator, _size);
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
		if (NULL != m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void IndexBufferD3D9::postReset()
	{
		if (NULL != m_dynamic)
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

			update(0, m_size, m_dynamic);
		}
	}

	void VertexBufferD3D9::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle)
	{
		m_size = _size;
		m_layoutHandle = _layoutHandle;

		uint32_t usage = D3DUSAGE_WRITEONLY;
		D3DPOOL pool = s_renderD3D9->m_pool;

		if (NULL == _data)
		{
			usage |= D3DUSAGE_DYNAMIC;
			pool = D3DPOOL_DEFAULT;
			m_dynamic = (uint8_t*)BX_ALLOC(g_allocator, _size);
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
		if (NULL != m_dynamic)
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void VertexBufferD3D9::postReset()
	{
		if (NULL != m_dynamic)
		{
			DX_CHECK(s_renderD3D9->m_device->CreateVertexBuffer(m_size
				, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC
				, 0
				, D3DPOOL_DEFAULT
				, &m_ptr
				, NULL
				) );

			update(0, m_size, m_dynamic);
		}
	}

	void ShaderD3D9::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		bx::ErrorAssert err;

		uint32_t magic;
		bx::read(&reader, magic, &err);

		const bool fragment = isShaderType(magic, 'F');

		uint32_t hashIn;
		bx::read(&reader, hashIn, &err);

		uint32_t hashOut;

		if (isShaderVerLess(magic, 6) )
		{
			hashOut = hashIn;
		}
		else
		{
			bx::read(&reader, hashOut, &err);
		}

		uint16_t count;
		bx::read(&reader, count, &err);

		m_numPredefined = 0;

		BX_TRACE("Shader consts %d", count);

		uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize, &err);

				char name[256] = {};
				bx::read(&reader, &name, nameSize, &err);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type, &err);

				uint8_t num = 0;
				bx::read(&reader, num, &err);

				uint16_t regIndex = 0;
				bx::read(&reader, regIndex, &err);

				uint16_t regCount = 0;
				bx::read(&reader, regCount, &err);

				if (!isShaderVerLess(magic, 8) )
				{
					uint16_t texInfo = 0;
					bx::read(&reader, texInfo, &err);
				}

				if (!isShaderVerLess(magic, 10) )
				{
					uint16_t texFormat = 0;
					bx::read(&reader, texFormat, &err);
				}

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
				else if (0 == (kUniformSamplerBit & type) )
				{
					const UniformRegInfo* info = s_renderD3D9->m_uniformReg.find(name);
					BX_WARN(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

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
					, getUniformTypeName(UniformType::Enum(type&~kUniformMask) )
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

		uint32_t shaderSize;
		bx::read(&reader, shaderSize, &err);

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
		const bimg::TextureFormat::Enum fmt = (bimg::TextureFormat::Enum)m_textureFormat;

		DWORD usage = 0;
		D3DPOOL pool = D3DPOOL_DEFAULT;

		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);
		const bool readBack     = 0 != (m_flags&BGFX_TEXTURE_READ_BACK);
		if (bimg::isDepth(fmt) )
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
			usage = 0
				| D3DUSAGE_RENDERTARGET
				| (1 < _numMips ? D3DUSAGE_AUTOGENMIPMAP : 0)
				;
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

				if (bimg::isDepth(fmt) )
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
			, bimg::getName(fmt)
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
		const bimg::TextureFormat::Enum fmt = (bimg::TextureFormat::Enum)m_textureFormat;

		DWORD usage = 0;

		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);
		if (bimg::isDepth(fmt) )
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

		BX_ASSERT(false, "You should not be here.");
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

		BX_ASSERT(false, "You should not be here.");
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

		BX_ASSERT(false, "You should not be here.");
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
			BX_ASSERT(false, "");
			break;

		case TextureCube:
			DX_CHECK(m_textureCube->GetCubeMapSurface(D3DCUBEMAP_FACES(_side), _mip, &surface) );
			break;
		}

		return surface;
	}

	void TextureD3D9::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(imageContainer.m_format) );

			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips-1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width >>startLod)
				, uint16_t(imageContainer.m_height>>startLod)
				, uint16_t(imageContainer.m_depth >>startLod)
				, imageContainer.m_cubeMap
				, 1 < imageContainer.m_numMips
				, imageContainer.m_numLayers
				, imageContainer.m_format
				);
			ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips-startLod, ti.numMips);

			m_flags   = _flags;
			m_width   = ti.width;
			m_height  = ti.height;
			m_depth   = ti.depth;
			m_numMips = ti.numMips;
			m_requestedFormat = uint8_t(imageContainer.m_format);
			m_textureFormat   = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;

			uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			if (imageContainer.m_cubeMap)
			{
				createCubeTexture(ti.width, ti.numMips);
			}
			else if (imageContainer.m_depth > 1)
			{
				createVolumeTexture(ti.width, ti.height, ti.depth, ti.numMips);
			}
			else
			{
				createTexture(ti.width, ti.height, ti.numMips);
			}

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s%s."
				, this - s_renderD3D9->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, 0 != (m_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
				);

			if (0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY) )
			{
				return;
			}

			const bool useMipSize = useD3D9Pitch(imageContainer.m_format);
			for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width     = ti.width;
				uint32_t height    = ti.height;
				uint32_t depth     = ti.depth;
				uint32_t mipWidth  = ti.width;
				uint32_t mipHeight = ti.height;

				for (uint8_t lod = 0, num = ti.numMips; lod < num; ++lod)
				{
					width     = bx::max<uint32_t>(1, width);
					height    = bx::max<uint32_t>(1, height);
					depth     = bx::max<uint32_t>(1, depth);
					mipWidth  = bx::max<uint32_t>(blockInfo.blockWidth,  mipWidth);
					mipHeight = bx::max<uint32_t>(blockInfo.blockHeight, mipHeight);
					uint32_t mipSize = width*height*depth*bpp/8;

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
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
								bimg::imageDecodeToBgra8(
									  g_allocator
									, temp
									, mip.m_data
									, mip.m_width
									, mip.m_height
									, srcpitch
									, mip.m_format
									);

								bx::memCopy(bits, pitch, temp, srcpitch, pitch, height);

								BX_FREE(g_allocator, temp);
							}
							else
							{
								bimg::imageDecodeToBgra8(g_allocator, bits, mip.m_data, mip.m_width, mip.m_height, pitch, mip.m_format);
							}
						}
						else
						{
							uint32_t size = useMipSize ? mip.m_size : mipSize;
							switch (m_textureFormat)
							{
							case TextureFormat::RGBA4:
								bimg::imageConvert(bits, 16, bx::packBgra4, mip.m_data, bx::unpackRgba4, size);
								break;

							default:
								bx::memCopy(bits, mip.m_data, size);
								break;
							}
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
		const bimg::ImageBlockInfo & blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint16_t blockHeight = blockInfo.blockHeight;
		const uint16_t bpp         = blockInfo.bitsPerPixel;
		const bool useLockedPitch  = useD3D9Pitch(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch   = calcRowPitch(blockInfo, 0, _rect.m_width);
		const uint32_t srcpitch    = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t dstpitch    = (useLockedPitch) ? s_renderD3D9->m_updateTexturePitch : calcRowPitch(blockInfo, _mip, m_width);
		uint8_t* bits = s_renderD3D9->m_updateTextureBits + _rect.m_y*dstpitch/blockHeight + _rect.m_x*blockHeight*bpp/8;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			bimg::imageDecodeToBgra8(g_allocator, temp, data, _rect.m_width, _rect.m_height, srcpitch, bimg::TextureFormat::Enum(m_requestedFormat) );
			data = temp;
		}

		{
			uint8_t* src = data;
			uint8_t* dst = bits;
			for (uint32_t yy = 0, height = _rect.m_height; yy < height; yy += blockHeight)
			{
				switch (m_textureFormat)
				{
				case TextureFormat::RGBA4:
					bimg::imageConvert(dst, 16, bx::packBgra4, src, bx::unpackRgba4, rectpitch);
					break;

				default:
					bx::memCopy(dst, src, rectpitch);
					break;
				}
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
		const uint64_t flags = (m_flags & BGFX_TEXTURE_SRGB)
			| (0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags) ? _flags : uint32_t(m_flags) )
			;
		uint32_t index = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
		s_renderD3D9->setSamplerState(_stage, flags, _palette[index]);

		IDirect3DDevice9* device = s_renderD3D9->m_device;
		DX_CHECK(device->SetTexture(_stage, m_ptr) );
		if (4 > _stage)
		{
			DX_CHECK(device->SetTexture(D3DVERTEXTEXTURESAMPLER0 + _stage, m_ptr) );
		}
	}

	void TextureD3D9::resolve(uint8_t _resolve) const
	{
		if (NULL != m_surface
		&&  NULL != m_ptr)
		{
			IDirect3DSurface9* surface = getSurface();
			DX_CHECK(s_renderD3D9->m_device->StretchRect(m_surface
				, NULL
				, surface
				, NULL
				, D3DTEXF_LINEAR
				) );
			DX_RELEASE(surface, 1);

			if (1 < m_numMips
			&&  0 != (_resolve & BGFX_RESOLVE_AUTO_GEN_MIPS) )
			{
				m_ptr->GenerateMipSubLevels();
			}
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

	void FrameBufferD3D9::create(uint8_t _num, const Attachment* _attachment)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_surface); ++ii)
		{
			m_surface[ii] = NULL;
		}

		m_denseIdx = UINT16_MAX;
		m_dsIdx = UINT8_MAX;
		m_num   = 0;
		m_numTh = _num;
		m_needResolve = false;
		bx::memCopy(m_attachment, _attachment, _num*sizeof(Attachment) );

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const Attachment& at = m_attachment[ii];

			if (isValid(at.handle) )
			{
				const TextureD3D9& texture = s_renderD3D9->m_textures[at.handle.idx];

				if (NULL != texture.m_surface)
				{
					m_surface[ii] = texture.m_surface;
					m_surface[ii]->AddRef();
				}
				else
				{
					m_surface[ii] = texture.getSurface(uint8_t(at.layer), uint8_t(at.mip) );
				}

				if (0 == m_num)
				{
					m_width  = texture.m_width;
					m_height = texture.m_height;
				}

				if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
				{
					m_dsIdx = uint8_t(ii);
				}
				else
				{
					++m_num;
				}

				m_needResolve |= true
					&& (NULL != texture.m_surface)
					&& (NULL != texture.m_texture2d)
					;
			}
		}

		if (0 == m_num)
		{
			createNullColorRT();
		}
	}

	void FrameBufferD3D9::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_depthFormat);

		m_hwnd = (HWND)_nwh;

		m_width  = bx::uint32_max(_width,  16);
		m_height = bx::uint32_max(_height, 16);

		D3DPRESENT_PARAMETERS params;
		bx::memCopy(&params, &s_renderD3D9->m_params, sizeof(D3DPRESENT_PARAMETERS) );
		params.BackBufferFormat   = TextureFormat::Count == _format ? params.BackBufferFormat : s_textureFormat[_format].m_fmt;
		params.BackBufferWidth    = m_width;
		params.BackBufferHeight   = m_height;
		params.MultiSampleType    = s_msaa[0].m_type;
		params.MultiSampleQuality = s_msaa[0].m_quality;

		DX_CHECK(s_renderD3D9->m_device->CreateAdditionalSwapChain(&params, &m_swapChain) );
		DX_CHECK(m_swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_surface[0]) );

		DX_CHECK(s_renderD3D9->m_device->CreateDepthStencilSurface(
			  params.BackBufferWidth
			, params.BackBufferHeight
			, params.AutoDepthStencilFormat
			, params.MultiSampleType
			, params.MultiSampleQuality
			, FALSE
			, &m_surface[1]
			, NULL
			) );

		m_dsIdx = 1;
		m_denseIdx = _denseIdx;
		m_num = 1;
		m_needResolve = false;
		m_needPresent = false;
	}

	uint16_t FrameBufferD3D9::destroy()
	{
		if (NULL != m_hwnd)
		{
			DX_RELEASE(m_surface[0], 0);
			DX_RELEASE(m_surface[1], 0);
			DX_RELEASE(m_swapChain,  0);
		}
		else
		{
			uint32_t num = m_numTh;
			num += uint32_t(0 < m_numTh && 0 == m_num);

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				IDirect3DSurface9* ptr = m_surface[ii];
				if (NULL != ptr)
				{
					ptr->Release();
					m_surface[ii] = NULL;
				}
			}
		}

		m_hwnd  = NULL;
		m_num   = 0;
		m_numTh = 0;
		m_needPresent = false;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	HRESULT FrameBufferD3D9::present()
	{
		if (m_needPresent)
		{
			HRESULT hr = m_swapChain->Present(NULL, NULL, m_hwnd, NULL, 0);
			m_needPresent = false;
			return hr;
		}

		return S_OK;
	}

	void FrameBufferD3D9::resolve() const
	{
		if (m_needResolve)
		{
			for (uint32_t ii = 0, num = m_numTh; ii < num; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					const TextureD3D9& texture = s_renderD3D9->m_textures[at.handle.idx];
					texture.resolve(at.resolve);
				}
			}
		}
	}

	void FrameBufferD3D9::preReset()
	{
		if (NULL != m_hwnd)
		{
			DX_RELEASE(m_surface[0], 0);
			DX_RELEASE(m_surface[1], 0);
			DX_RELEASE(m_swapChain, 0);
		}
		else
		{
			uint32_t num = m_numTh;
			num += uint32_t(0 < m_numTh && 0 == m_num);

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				m_surface[ii]->Release();
				m_surface[ii] = NULL;
			}
		}
	}

	void FrameBufferD3D9::postReset()
	{
		if (NULL != m_hwnd)
		{
			D3DPRESENT_PARAMETERS params;
			bx::memCopy(&params, &s_renderD3D9->m_params, sizeof(D3DPRESENT_PARAMETERS) );
			params.BackBufferWidth  = m_width;
			params.BackBufferHeight = m_height;

			DX_CHECK(s_renderD3D9->m_device->CreateAdditionalSwapChain(&params, &m_swapChain) );
			DX_CHECK(m_swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_surface[0]) );
			DX_CHECK(s_renderD3D9->m_device->CreateDepthStencilSurface(params.BackBufferWidth
					, params.BackBufferHeight
					, params.AutoDepthStencilFormat
					, params.MultiSampleType
					, params.MultiSampleQuality
					, FALSE
					, &m_surface[1]
					, NULL
					) );
		}
		else if (0 < m_numTh)
		{
			for (uint32_t ii = 0, num = m_numTh; ii < num; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					TextureD3D9& texture = s_renderD3D9->m_textures[at.handle.idx];

					if (NULL != texture.m_surface)
					{
						m_surface[ii] = texture.m_surface;
						m_surface[ii]->AddRef();
					}
					else if (Access::Write == at.access)
					{
						m_surface[ii] = texture.getSurface(uint8_t(at.layer), uint8_t(at.mip) );
					}
					else
					{
						BX_ASSERT(false, "");
					}
				}
			}

			if (0 == m_num)
			{
				createNullColorRT();
			}
		}
	}

	void FrameBufferD3D9::createNullColorRT()
	{
		DX_CHECK(s_renderD3D9->m_device->CreateRenderTarget(
			  m_width
			, m_height
			, D3DFMT_NULL
			, D3DMULTISAMPLE_NONE
			, 0
			, false
			, &m_surface[1]
			, NULL
			) );
	}

	void FrameBufferD3D9::set()
	{
		m_needPresent = UINT16_MAX != m_denseIdx;

		// If frame buffer has only depth attachment D3DFMT_NULL
		// render target is created.
		const uint32_t fbnum = bx::uint32_max(2, m_numTh);
		const uint8_t  dsIdx = m_dsIdx;

		IDirect3DDevice9* device = s_renderD3D9->m_device;

		DX_CHECK(device->SetDepthStencilSurface(UINT8_MAX == dsIdx
			? s_renderD3D9->m_backBufferDepthStencil
			: m_surface[dsIdx]
			) );

		uint32_t rtIdx = 0;
		for (uint32_t ii = 0; ii < fbnum; ++ii)
		{
			IDirect3DSurface9* surface = m_surface[ii];
			if (ii != dsIdx)
			{
				DX_CHECK(device->SetRenderTarget(rtIdx, surface) );
				++rtIdx;
			}
		}

		for (uint32_t ii = rtIdx, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
		{
			DX_CHECK(device->SetRenderTarget(ii, NULL) );
		}

		DX_CHECK(device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE) );
	}

	void TimerQueryD3D9::postReset()
	{
		IDirect3DDevice9* device = s_renderD3D9->m_device;

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& frame = m_query[ii];
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMPDISJOINT, &frame.m_disjoint) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMP,         &frame.m_begin) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMP,         &frame.m_end) );
			DX_CHECK(device->CreateQuery(D3DQUERYTYPE_TIMESTAMPFREQ,     &frame.m_freq) );
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_result); ++ii)
		{
			Result& result = m_result[ii];
			result.reset();
		}

		m_control.reset();
	}

	void TimerQueryD3D9::preReset()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& frame = m_query[ii];
			DX_RELEASE(frame.m_disjoint, 0);
			DX_RELEASE(frame.m_begin, 0);
			DX_RELEASE(frame.m_end, 0);
			DX_RELEASE(frame.m_freq, 0);
		}
	}

	uint32_t TimerQueryD3D9::begin(uint32_t _resultIdx)
	{
		while (0 == m_control.reserve(1) )
		{
			update();
		}

		Result& result = m_result[_resultIdx];
		++result.m_pending;

		const uint32_t idx = m_control.m_current;
		Query& query = m_query[idx];
		query.m_resultIdx = _resultIdx;
		query.m_ready     = false;

		query.m_disjoint->Issue(D3DISSUE_BEGIN);
		query.m_begin->Issue(D3DISSUE_END);

		m_control.commit(1);

		return idx;
	}

	void TimerQueryD3D9::end(uint32_t _idx)
	{
		Query& query = m_query[_idx];
		query.m_ready = true;

		query.m_disjoint->Issue(D3DISSUE_END);
		query.m_freq->Issue(D3DISSUE_END);
		query.m_end->Issue(D3DISSUE_END);

		while (update() )
		{
		}
	}

	bool TimerQueryD3D9::update()
	{
		if (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (!query.m_ready)
			{
				return false;
			}

			uint64_t timeEnd;
			const bool flush = BX_COUNTOF(m_query)-1 == m_control.available();
			HRESULT hr = query.m_end->GetData(&timeEnd, sizeof(timeEnd), flush ? D3DGETDATA_FLUSH : 0);
			if (S_OK == hr
			||  isLost(hr) )
			{
				m_control.consume(1);

				uint64_t timeBegin;
				DX_CHECK(query.m_begin->GetData(&timeBegin, sizeof(timeBegin), 0) );

				uint64_t freq;
				DX_CHECK(query.m_freq->GetData(&freq, sizeof(freq), 0) );

				Result& result = m_result[query.m_resultIdx];
				--result.m_pending;

				result.m_frequency = freq;
				result.m_begin     = timeBegin;
				result.m_end       = timeEnd;

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

			if (isValid(query.m_handle) )
			{
				uint32_t result;
				HRESULT hr = query.m_ptr->GetData(&result, sizeof(result), 0);
				if (S_FALSE == hr)
				{
					break;
				}

				_render->m_occlusion[query.m_handle.idx] = int32_t(result);
			}

			m_control.consume(1);
		}
	}

	void OcclusionQueryD3D9::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
		{
			Query& query = m_query[(m_control.m_read + ii) % size];
			if (query.m_handle.idx == _handle.idx)
			{
				query.m_handle.idx = bgfx::kInvalidHandle;
			}
		}
	}

	void RendererContextD3D9::submitBlit(BlitState& _bs, uint16_t _view)
	{
		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureD3D9& src = m_textures[blit.m_src.idx];
			const TextureD3D9& dst = m_textures[blit.m_dst.idx];

			RECT srcRect = { LONG(blit.m_srcX), LONG(blit.m_srcY), LONG(blit.m_srcX + blit.m_width), LONG(blit.m_srcY + blit.m_height) };
			RECT dstRect = { LONG(blit.m_dstX), LONG(blit.m_dstY), LONG(blit.m_dstX + blit.m_width), LONG(blit.m_dstY + blit.m_height) };

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

			bool depth = bimg::isDepth(bimg::TextureFormat::Enum(src.m_textureFormat) );
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

	void RendererContextD3D9::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		IDirect3DDevice9* device = m_device;

		updateResolution(_render->m_resolution);

		BGFX_D3D9_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorView);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = UINT32_MAX;

		device->BeginScene();
		if (m_timerQuerySupport)
		{
			frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS);
		}

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data, true);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		static ViewState viewState;
		viewState.reset(_render);

		DX_CHECK(device->SetRenderState(D3DRS_FILLMODE, _render->m_debug&BGFX_DEBUG_WIREFRAME ? D3DFILL_WIREFRAME : D3DFILL_SOLID) );
		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };
		uint32_t blendFactor = 0;

		BlitState bs(_render);

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

		Profiler<TimerQueryD3D9> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			, m_timerQuerySupport
			);

		if (m_occlusionQuerySupport)
		{
			m_occlusionQuery.resolve(_render);
		}

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = _render->m_numRenderItems; item < numItems; ++item)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				statsKeyType[isCompute]++;

				if (isCompute)
				{
					BX_ASSERT(false, "Compute is not supported on DirectX 9.");
					continue;
				}

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderDraw& draw = _render->m_renderItem[itemIdx].draw;
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = true
						&& isValid(draw.m_occlusionQuery)
						&& !hasOcclusionQuery
						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) )
						;

					if (occluded
					||  _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor) )
					{
						continue;
					}
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

					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 0)
					{
						profiler.end();
					}

					BGFX_D3D9_PROFILER_END();
					BGFX_D3D9_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						fbh = _render->m_view[view].m_fbh;
						setFrameBuffer(fbh);
					}

					viewState.m_rect        = _render->m_view[view].m_rect;
					const Rect& scissorRect = _render->m_view[view].m_scissor;
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

					Clear& clear = _render->m_view[view].m_clear;

					if (BGFX_CLEAR_NONE != (clear.m_flags & BGFX_CLEAR_MASK) )
					{
						clearQuad(_clearQuad, viewState.m_rect, clear, _render->m_colorPalette);
					}

					DX_CHECK(device->SetRenderState(D3DRS_STENCILENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZENABLE, TRUE) );
					DX_CHECK(device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS) );
					DX_CHECK(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE) );
					DX_CHECK(device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER) );

					submitBlit(bs, view);
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
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

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
					 | BGFX_STATE_WRITE_Z
					 | BGFX_STATE_DEPTH_TEST_MASK
					 | BGFX_STATE_WRITE_RGB
					 | BGFX_STATE_WRITE_A
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

					if (BGFX_STATE_WRITE_Z & changedFlags)
					{
						DX_CHECK(device->SetRenderState(D3DRS_ZWRITEENABLE, !!(BGFX_STATE_WRITE_Z & newFlags) ) );
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

					if (BGFX_STATE_LINEAA & changedFlags)
					{
						DX_CHECK(m_device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, !!(newFlags&BGFX_STATE_LINEAA) ) );
					}

					if ( (BGFX_STATE_WRITE_A|BGFX_STATE_WRITE_RGB) & changedFlags)
					{
						uint32_t writeEnable = 0;
 						writeEnable |= (newFlags&BGFX_STATE_WRITE_R) ? D3DCOLORWRITEENABLE_RED   : 0;
 						writeEnable |= (newFlags&BGFX_STATE_WRITE_G) ? D3DCOLORWRITEENABLE_GREEN : 0;
 						writeEnable |= (newFlags&BGFX_STATE_WRITE_B) ? D3DCOLORWRITEENABLE_BLUE  : 0;
						writeEnable |= (newFlags&BGFX_STATE_WRITE_A) ? D3DCOLORWRITEENABLE_ALPHA : 0;
						DX_CHECK(device->SetRenderState(D3DRS_COLORWRITEENABLE, writeEnable) );
					}

					if ( ( (0
						| BGFX_STATE_BLEND_MASK
						| BGFX_STATE_BLEND_EQUATION_MASK
						| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
						) & changedFlags)
					||  blendFactor != draw.m_rgba)
					{
						bool enabled = !!(BGFX_STATE_BLEND_MASK & newFlags);
						DX_CHECK(device->SetRenderState(D3DRS_ALPHABLENDENABLE, enabled) );

						if (m_atocSupport
						&&  BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & changedFlags)
						{
							DX_CHECK(m_device->SetRenderState(D3DRS_ADAPTIVETESS_Y
								, !!(newFlags&BGFX_STATE_BLEND_ALPHA_TO_COVERAGE)
								? D3DFMT_ATOC
								: 0
								) );
						}

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
								D3DCOLOR color = D3DCOLOR_RGBA(
									   rgba>>24
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
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				if (key.m_program.idx != currentProgram.idx)
				{
					currentProgram = key.m_program;

					if (!isValid(currentProgram) )
					{
						device->SetVertexShader(NULL);
						device->SetPixelShader(NULL);
					}
					else
					{
						ProgramD3D9& program = m_program[currentProgram.idx];
						device->SetVertexShader(program.m_vsh->m_vertexShader);
						device->SetPixelShader(NULL == program.m_fsh
							? NULL
							: program.m_fsh->m_pixelShader
							);
					}

					programChanged =
						constantsChanged = true;
				}

				if (isValid(currentProgram) )
				{
					ProgramD3D9& program = m_program[currentProgram.idx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						if (NULL != program.m_fsh)
						{
							UniformBuffer* fcb = program.m_fsh->m_constantBuffer;
							if (NULL != fcb)
							{
								commit(*fcb);
							}
						}
					}

					viewState.setPredefined<4>(this, view, program, _render, draw);
				}

				{
					for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
					{
						const Binding& bind = renderBind.m_bind[stage];
						Binding& current = currentBind.m_bind[stage];

						if (current.m_idx          != bind.m_idx
						||  current.m_samplerFlags != bind.m_samplerFlags
						||  programChanged)
						{
							if (kInvalidHandle != bind.m_idx)
							{
								m_textures[bind.m_idx].commit(stage, bind.m_samplerFlags, _render->m_colorPalette);
							}
							else
							{
								DX_CHECK(device->SetTexture(stage, NULL) );
							}
						}

						current = bind;
					}
				}

				bool vertexStreamChanged = hasVertexStreamChanged(currentState, draw);

				if (programChanged
				||  vertexStreamChanged)
				{
				    currentState.m_streamMask             = draw.m_streamMask;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset     = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride     = draw.m_instanceDataStride;

					const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];

					const bool instanced = true
						&& isValid(draw.m_instanceDataBuffer)
						&& m_instancingSupport
						;

					const uint32_t freq = instanced
						? D3DSTREAMSOURCE_INDEXEDDATA|draw.m_numInstances
						: 1
						;

					uint32_t numVertices = draw.m_numVertices;
					uint8_t  numStreams  = 0;
					for (uint32_t idx = 0, streamMask = draw.m_streamMask
						; 0 != streamMask
						; streamMask >>= 1, idx += 1, ++numStreams
						)
					{
						const uint32_t ntz = bx::uint32_cnttz(streamMask);
						streamMask >>= ntz;
						idx         += ntz;

						currentState.m_stream[idx].m_layoutHandle = draw.m_stream[idx].m_layoutHandle;
						currentState.m_stream[idx].m_handle       = draw.m_stream[idx].m_handle;
						currentState.m_stream[idx].m_startVertex  = draw.m_stream[idx].m_startVertex;

						const uint16_t handle = draw.m_stream[idx].m_handle.idx;
						const VertexBufferD3D9& vb = m_vertexBuffers[handle];
						const uint16_t layoutIdx = isValid(draw.m_stream[idx].m_layoutHandle)
							? draw.m_stream[idx].m_layoutHandle.idx
							: vb.m_layoutHandle.idx;
						const VertexLayout& layout = m_vertexLayouts[layoutIdx];
						const uint32_t stride = layout.m_stride;

						layouts[numStreams] = &layout;

						numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
							? vb.m_size/stride
							: draw.m_numVertices
							, numVertices
							);

						DX_CHECK(device->SetStreamSourceFreq(0, freq) );
						DX_CHECK(device->SetStreamSource(numStreams, vb.m_ptr, 0, stride) );
					}

					if (0 < numStreams)
					{
						if (instanced)
						{
							const VertexBufferD3D9& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							DX_CHECK(device->SetStreamSourceFreq(numStreams, UINT(D3DSTREAMSOURCE_INSTANCEDATA|1) ) );
							DX_CHECK(device->SetStreamSource(numStreams, inst.m_ptr, draw.m_instanceDataOffset, draw.m_instanceDataStride) );
							setInputLayout(numStreams, layouts, draw.m_instanceDataStride/16);
						}
						else
						{
							DX_CHECK(device->SetStreamSource(numStreams, NULL, 0, 0) );
							setInputLayout(numStreams, layouts, 0);
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
					if (kInvalidHandle != handle)
					{
						const IndexBufferD3D9& ib = m_indexBuffers[handle];
						DX_CHECK(device->SetIndices(ib.m_ptr) );
					}
					else
					{
						DX_CHECK(device->SetIndices(NULL) );
					}
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices       = draw.m_numVertices;
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
							const bool isIndex16     = draw.isIndex16();
							const uint32_t indexSize = isIndex16 ? 2 : 4;
							numIndices        = ib.m_size/indexSize;
							numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							DX_CHECK(device->DrawIndexedPrimitive(prim.m_type
								, draw.m_stream[0].m_startVertex
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
								, draw.m_stream[0].m_startVertex
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
							, draw.m_stream[0].m_startVertex
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

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				if (0 != (m_resolution.reset & BGFX_RESET_FLUSH_AFTER_RENDER) )
				{
					flush();
				}

				captureElapsed = -bx::getHPCounter();
				capture();
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		BGFX_D3D9_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		if (UINT32_MAX != frameQueryIdx)
		{
			m_gpuTimer.end(frameQueryIdx);

			const TimerQueryD3D9::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
			double toGpuMs = 1000.0 / double(result.m_frequency);
			elapsedGpuMs   = (result.m_end - result.m_begin) * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;

			maxGpuLatency = bx::uint32_imax(maxGpuLatency, result.m_pending-1);
		}

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		const TimerQueryD3D9::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
		perfStats.gpuTimeBegin  = result.m_begin;
		perfStats.gpuTimeEnd    = result.m_end;
		perfStats.gpuTimerFreq  = result.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		m_nvapi.getMemoryInfo(perfStats.gpuMemoryUsed, perfStats.gpuMemoryMax);

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			BGFX_D3D9_PROFILER_BEGIN_LITERAL("debugstats", kColorFrame);

			m_needPresent = true;
			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = timeEnd;

			if (timeEnd >= next)
			{
				next = timeEnd + timerFreq;

				double freq = double(timerFreq);
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x8c : 0x8f
					, " %s / " BX_COMPILER_NAME
					  " / " BX_CPU_NAME
					  " / " BX_ARCH_NAME
					  " / " BX_PLATFORM_NAME
					  " / Version 1.%d.%d (commit: " BGFX_REV_SHA1 ")"
					, getRendererName()
					, BGFX_API_VERSION
					, BGFX_REV_NUMBER
					);

				const D3DADAPTER_IDENTIFIER9& identifier = m_identifier;
				tvm.printf(0, pos++, 0x8f, " Device: %s (%s)", identifier.Description, identifier.Driver);

				char processMemoryUsed[16];
				bx::prettify(processMemoryUsed, BX_COUNTOF(processMemoryUsed), bx::getProcessMemoryUsed() );
				tvm.printf(0, pos++, 0x8f, " Memory: %s (process) ", processMemoryUsed);

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "        Frame: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "    Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] %c GPU %7.4f [ms] (latency %d)"
					, _render->m_numRenderItems
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					, elapsedCpuMs > maxGpuElapsed ? '>' : '<'
					, maxGpuElapsed
					, maxGpuLatency
					);
				maxGpuLatency = 0;
				maxGpuElapsed = 0.0;

				for (uint32_t ii = 0; ii < Topology::Count; ++ii)
				{
					tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d"
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8b, " Occlusion queries: %3d ", m_occlusionQuery.m_control.available() );

				pos++;
				tvm.printf(10, pos++, 0x8b, " State cache: ");
				tvm.printf(10, pos++, 0x8b, " Input  ");
				tvm.printf(10, pos++, 0x8b, " %6d "
					, m_inputLayoutCache.getCount()
					);
				pos++;

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %7.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);

			BGFX_D3D9_PROFILER_END();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			BGFX_D3D9_PROFILER_BEGIN_LITERAL("debugtext", kColorFrame);

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			BGFX_D3D9_PROFILER_END();
		}

		device->EndScene();
	}
} /* namespace d3d9 */ } // namespace bgfx

#else

namespace bgfx { namespace d3d9
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace d3d9 */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D9

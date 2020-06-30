/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D11
#	include "renderer_d3d11.h"

namespace bgfx { namespace d3d11
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];
	static char    s_viewName [BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	inline void setViewType(ViewId _view, const bx::StringView _str)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION | BGFX_CONFIG_PROFILER) )
		{
			const uint32_t len = _str.getLength();

			bx::memCopy(&s_viewName[_view][3], _str.getPtr(), len);

			wchar_t tmpW[16];
			mbstowcs(tmpW, _str.getPtr(), len);

			bx::memCopy(&s_viewNameW[_view][3], tmpW, len*2);
		}
	}

	struct PrimInfo
	{
		D3D11_PRIMITIVE_TOPOLOGY m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,  3, 3, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, 3, 1, 2 },
		{ D3D11_PRIMITIVE_TOPOLOGY_LINELIST,      2, 2, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,     2, 1, 1 },
		{ D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,     1, 1, 0 },
		{ D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,     0, 0, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo)-1);

	union Zero
	{
		Zero()
		{
			bx::memSet(this, 0, sizeof(Zero) );
		}

		ID3D11Buffer*              m_buffer[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		ID3D11UnorderedAccessView* m_uav[D3D11_1_UAV_SLOT_COUNT];
		ID3D11ShaderResourceView*  m_srv[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
		ID3D11SamplerState*        m_sampler[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
		ID3D11RenderTargetView*    m_rtv[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		uint32_t                   m_zero[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		float                      m_zerof[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	};

	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4268) // warning C4268: '' : 'const' static/global data initialized with compiler generated default constructor fills the object with zeros
	static const Zero s_zero;
	BX_PRAGMA_DIAGNOSTIC_POP();

	static const uint32_t s_checkMsaa[] =
	{
		0,
		2,
		4,
		8,
		16,
	};

	static DXGI_SAMPLE_DESC s_msaa[] =
	{
		{  1, 0 },
		{  2, 0 },
		{  4, 0 },
		{  8, 0 },
		{ 16, 0 },
	};

	static const D3D11_BLEND s_blendFactor[][2] =
	{
		{ D3D11_BLEND(0),               D3D11_BLEND(0)               }, // ignored
		{ D3D11_BLEND_ZERO,             D3D11_BLEND_ZERO             }, // ZERO
		{ D3D11_BLEND_ONE,              D3D11_BLEND_ONE              }, // ONE
		{ D3D11_BLEND_SRC_COLOR,        D3D11_BLEND_SRC_ALPHA        }, // SRC_COLOR
		{ D3D11_BLEND_INV_SRC_COLOR,    D3D11_BLEND_INV_SRC_ALPHA    }, // INV_SRC_COLOR
		{ D3D11_BLEND_SRC_ALPHA,        D3D11_BLEND_SRC_ALPHA        }, // SRC_ALPHA
		{ D3D11_BLEND_INV_SRC_ALPHA,    D3D11_BLEND_INV_SRC_ALPHA    }, // INV_SRC_ALPHA
		{ D3D11_BLEND_DEST_ALPHA,       D3D11_BLEND_DEST_ALPHA       }, // DST_ALPHA
		{ D3D11_BLEND_INV_DEST_ALPHA,   D3D11_BLEND_INV_DEST_ALPHA   }, // INV_DST_ALPHA
		{ D3D11_BLEND_DEST_COLOR,       D3D11_BLEND_DEST_ALPHA       }, // DST_COLOR
		{ D3D11_BLEND_INV_DEST_COLOR,   D3D11_BLEND_INV_DEST_ALPHA   }, // INV_DST_COLOR
		{ D3D11_BLEND_SRC_ALPHA_SAT,    D3D11_BLEND_ONE              }, // SRC_ALPHA_SAT
		{ D3D11_BLEND_BLEND_FACTOR,     D3D11_BLEND_BLEND_FACTOR     }, // FACTOR
		{ D3D11_BLEND_INV_BLEND_FACTOR, D3D11_BLEND_INV_BLEND_FACTOR }, // INV_FACTOR
	};

	static const D3D11_BLEND_OP s_blendEquation[] =
	{
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX,
	};

	static const D3D11_COMPARISON_FUNC s_cmpFunc[] =
	{
		D3D11_COMPARISON_FUNC(0), // ignored
		D3D11_COMPARISON_LESS,
		D3D11_COMPARISON_LESS_EQUAL,
		D3D11_COMPARISON_EQUAL,
		D3D11_COMPARISON_GREATER_EQUAL,
		D3D11_COMPARISON_GREATER,
		D3D11_COMPARISON_NOT_EQUAL,
		D3D11_COMPARISON_NEVER,
		D3D11_COMPARISON_ALWAYS,
	};

	static const D3D11_STENCIL_OP s_stencilOp[] =
	{
		D3D11_STENCIL_OP_ZERO,
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_REPLACE,
		D3D11_STENCIL_OP_INCR,
		D3D11_STENCIL_OP_INCR_SAT,
		D3D11_STENCIL_OP_DECR,
		D3D11_STENCIL_OP_DECR_SAT,
		D3D11_STENCIL_OP_INVERT,
	};

	static const D3D11_CULL_MODE s_cullMode[] =
	{
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK,
	};

	static const D3D11_TEXTURE_ADDRESS_MODE s_textureAddress[] =
	{
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_MIRROR,
		D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_BORDER,
	};

	/*
	 * D3D11_FILTER_MIN_MAG_MIP_POINT               = 0x00,
	 * D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR        = 0x01,
	 * D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT  = 0x04,
	 * D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR        = 0x05,
	 * D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT        = 0x10,
	 * D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
	 * D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT        = 0x14,
	 * D3D11_FILTER_MIN_MAG_MIP_LINEAR              = 0x15,
	 * D3D11_FILTER_ANISOTROPIC                     = 0x55,
	 *
	 * D3D11_COMPARISON_FILTERING_BIT               = 0x80,
	 * D3D11_ANISOTROPIC_FILTERING_BIT              = 0x40,
	 *
	 * According to D3D11_FILTER enum bits for mip, mag and mip are:
	 * 0x10 // MIN_LINEAR
	 * 0x04 // MAG_LINEAR
	 * 0x01 // MIP_LINEAR
	 */

	static const uint8_t s_textureFilter[3][3] =
	{
		{
			0x10, // min linear
			0x00, // min point
			0x55, // anisotropic
		},
		{
			0x04, // mag linear
			0x00, // mag point
			0x55, // anisotropic
		},
		{
			0x01, // mip linear
			0x00, // mip point
			0x55, // anisotropic
		},
	};

	struct TextureFormatInfo
	{
		DXGI_FORMAT m_fmt;
		DXGI_FORMAT m_fmtSrv;
		DXGI_FORMAT m_fmtDsv;
		DXGI_FORMAT m_fmtSrgb;
	};

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC1_UNORM_SRGB       }, // BC1
		{ DXGI_FORMAT_BC2_UNORM,          DXGI_FORMAT_BC2_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC2_UNORM_SRGB       }, // BC2
		{ DXGI_FORMAT_BC3_UNORM,          DXGI_FORMAT_BC3_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC3_UNORM_SRGB       }, // BC3
		{ DXGI_FORMAT_BC4_UNORM,          DXGI_FORMAT_BC4_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC4
		{ DXGI_FORMAT_BC5_UNORM,          DXGI_FORMAT_BC5_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC5
		{ DXGI_FORMAT_BC6H_SF16,          DXGI_FORMAT_BC6H_SF16,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC6H
		{ DXGI_FORMAT_BC7_UNORM,          DXGI_FORMAT_BC7_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC7_UNORM_SRGB       }, // BC7
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2A1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC12
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC14
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC12A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC14A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC22
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC24
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATC
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATCE
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATCI
		{ DXGI_FORMAT_ASTC_4X4_UNORM,     DXGI_FORMAT_ASTC_4X4_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_4X4_UNORM_SRGB  }, // ASTC4x4
		{ DXGI_FORMAT_ASTC_5X5_UNORM,     DXGI_FORMAT_ASTC_5X5_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_5X5_UNORM_SRGB  }, // ASTC5x5
		{ DXGI_FORMAT_ASTC_6X6_UNORM,     DXGI_FORMAT_ASTC_6X6_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_6X6_UNORM_SRGB  }, // ASTC6x6
		{ DXGI_FORMAT_ASTC_8X5_UNORM,     DXGI_FORMAT_ASTC_8X5_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_8X5_UNORM_SRGB  }, // ASTC8x5
		{ DXGI_FORMAT_ASTC_8X6_UNORM,     DXGI_FORMAT_ASTC_8X6_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_8X6_UNORM_SRGB  }, // ASTC8x6
		{ DXGI_FORMAT_ASTC_10X5_UNORM,    DXGI_FORMAT_ASTC_10X5_UNORM,       DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_10X5_UNORM_SRGB }, // ASTC10x5
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // Unknown
		{ DXGI_FORMAT_R1_UNORM,           DXGI_FORMAT_R1_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R1
		{ DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_A8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // A8
		{ DXGI_FORMAT_R8_UNORM,           DXGI_FORMAT_R8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8
		{ DXGI_FORMAT_R8_SINT,            DXGI_FORMAT_R8_SINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8I
		{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8U
		{ DXGI_FORMAT_R8_SNORM,           DXGI_FORMAT_R8_SNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8S
		{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16
		{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16I
		{ DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_UINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16U
		{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16F
		{ DXGI_FORMAT_R16_SNORM,          DXGI_FORMAT_R16_SNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16S
		{ DXGI_FORMAT_R32_SINT,           DXGI_FORMAT_R32_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32I
		{ DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_UINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32U
		{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32F
		{ DXGI_FORMAT_R8G8_UNORM,         DXGI_FORMAT_R8G8_UNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8
		{ DXGI_FORMAT_R8G8_SINT,          DXGI_FORMAT_R8G8_SINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8I
		{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8U
		{ DXGI_FORMAT_R8G8_SNORM,         DXGI_FORMAT_R8G8_SNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8S
		{ DXGI_FORMAT_R16G16_UNORM,       DXGI_FORMAT_R16G16_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16
		{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16I
		{ DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16U
		{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16F
		{ DXGI_FORMAT_R16G16_SNORM,       DXGI_FORMAT_R16G16_SNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16S
		{ DXGI_FORMAT_R32G32_SINT,        DXGI_FORMAT_R32G32_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32I
		{ DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32U
		{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32F
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8I
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8U
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8S
		{ DXGI_FORMAT_R9G9B9E5_SHAREDEXP, DXGI_FORMAT_R9G9B9E5_SHAREDEXP,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB9E5F
		{ DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_B8G8R8A8_UNORM_SRGB  }, // BGRA8
		{ DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8
		{ DXGI_FORMAT_R8G8B8A8_SINT,      DXGI_FORMAT_R8G8B8A8_SINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8I
		{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8U
		{ DXGI_FORMAT_R8G8B8A8_SNORM,     DXGI_FORMAT_R8G8B8A8_SNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA8S
		{ DXGI_FORMAT_R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16
		{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16I
		{ DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16U
		{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16F
		{ DXGI_FORMAT_R16G16B16A16_SNORM, DXGI_FORMAT_R16G16B16A16_SNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16S
		{ DXGI_FORMAT_R32G32B32A32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32I
		{ DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32U
		{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32F
		{ DXGI_FORMAT_B5G6R5_UNORM,       DXGI_FORMAT_B5G6R5_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R5G6B5
		{ DXGI_FORMAT_B4G4R4A4_UNORM,     DXGI_FORMAT_B4G4R4A4_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA4
		{ DXGI_FORMAT_B5G5R5A1_UNORM,     DXGI_FORMAT_B5G5R5A1_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB5A1
		{ DXGI_FORMAT_R10G10B10A2_UNORM,  DXGI_FORMAT_R10G10B10A2_UNORM,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB10A2
		{ DXGI_FORMAT_R11G11B10_FLOAT,    DXGI_FORMAT_R11G11B10_FLOAT,       DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG11B10F
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // UnknownDepth
		{ DXGI_FORMAT_R16_TYPELESS,       DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_D16_UNORM,         DXGI_FORMAT_UNKNOWN              }, // D16
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D24
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D24S8
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D32
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D16F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D24F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D32F
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	static const D3D11_INPUT_ELEMENT_DESC s_attrib[] =
	{
		{ "POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BITANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        1, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        2, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",        3, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     1, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     2, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     3, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     4, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     5, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     6, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     7, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attrib) );

	static const DXGI_FORMAT s_attribType[][4][2] =
	{
		{ // Uint8
			{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UNORM           },
			{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UNORM         },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
		},
		{ // Uint10
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
		},
		{ // Int16
			{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SNORM          },
			{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SNORM       },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
		},
		{ // Half
			{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT          },
			{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT       },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
		},
		{ // Float
			{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT          },
			{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT       },
			{ DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT    },
			{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static D3D11_INPUT_ELEMENT_DESC* fillVertexLayout(uint8_t _stream, D3D11_INPUT_ELEMENT_DESC* _out, const VertexLayout& _layout)
	{
		D3D11_INPUT_ELEMENT_DESC* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _layout.m_attributes[attr])
			{
				bx::memCopy(elem, &s_attrib[attr], sizeof(D3D11_INPUT_ELEMENT_DESC) );

				elem->InputSlot = _stream;

				if (0 == _layout.m_attributes[attr])
				{
					elem->AlignedByteOffset = 0;
				}
				else
				{
					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);
					elem->Format = s_attribType[type][num-1][normalized];
					elem->AlignedByteOffset = _layout.m_offset[attr];
				}

				++elem;
			}
		}

		return elem;
	}

	struct TextureStage
	{
		TextureStage()
		{
			clear();
		}

		void clear()
		{
			bx::memSet(m_uav,     0, sizeof(m_uav) );
			bx::memSet(m_srv,     0, sizeof(m_srv) );
			bx::memSet(m_sampler, 0, sizeof(m_sampler) );
		}

		ID3D11UnorderedAccessView* m_uav[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		ID3D11ShaderResourceView*  m_srv[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		ID3D11SamplerState*        m_sampler[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
	};

	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunused-const-variable");
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunneeded-internal-declaration");

	static const GUID WKPDID_D3DDebugObjectName     = { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };
	static const GUID IID_ID3D11Texture2D           = { 0x6f15aaf2, 0xd208, 0x4e89, { 0x9a, 0xb4, 0x48, 0x95, 0x35, 0xd3, 0x4f, 0x9c } };
	static const GUID IID_ID3D11Device1             = { 0xa04bfb29, 0x08ef, 0x43d6, { 0xa4, 0x9c, 0xa9, 0xbd, 0xbd, 0xcb, 0xe6, 0x86 } };
	static const GUID IID_ID3D11Device2             = { 0x9d06dffa, 0xd1e5, 0x4d07, { 0x83, 0xa8, 0x1b, 0xb1, 0x23, 0xf2, 0xf8, 0x41 } };
	static const GUID IID_ID3D11Device3             = { 0xa05c8c37, 0xd2c6, 0x4732, { 0xb3, 0xa0, 0x9c, 0xe0, 0xb0, 0xdc, 0x9a, 0xe6 } };
	static const GUID IID_ID3D11InfoQueue           = { 0x6543dbb6, 0x1b48, 0x42f5, { 0xab, 0x82, 0xe9, 0x7e, 0xc7, 0x43, 0x26, 0xf6 } };
	static const GUID IID_IDXGIDeviceRenderDoc      = { 0xa7aa6116, 0x9c8d, 0x4bba, { 0x90, 0x83, 0xb4, 0xd8, 0x16, 0xb7, 0x1b, 0x78 } };
	static const GUID IID_ID3DUserDefinedAnnotation = { 0xb2daad8b, 0x03d4, 0x4dbf, { 0x95, 0xeb, 0x32, 0xab, 0x4b, 0x63, 0xd0, 0xab } };

	enum D3D11_FORMAT_SUPPORT2
	{
		D3D11_FORMAT_SUPPORT2_UAV_TYPED_LOAD  = 0x40,
		D3D11_FORMAT_SUPPORT2_UAV_TYPED_STORE = 0x80,
	};

	static const GUID s_d3dDeviceIIDs[] =
	{
		IID_ID3D11Device3,
		IID_ID3D11Device2,
		IID_ID3D11Device1,
	};

	inline bool isLost(HRESULT _hr)
	{
		return false
			|| _hr == DXGI_ERROR_DEVICE_REMOVED
			|| _hr == DXGI_ERROR_DEVICE_HUNG
			|| _hr == DXGI_ERROR_DEVICE_RESET
			|| _hr == DXGI_ERROR_DRIVER_INTERNAL_ERROR
			|| _hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE
			;
	}

	static const char* getLostReason(HRESULT _hr)
	{
		switch (_hr)
		{
		// The GPU device instance has been suspended. Use GetDeviceRemovedReason to determine the appropriate action.
		case DXGI_ERROR_DEVICE_REMOVED: return "DXGI_ERROR_DEVICE_REMOVED";

		// The GPU will not respond to more commands, most likely because of an invalid command passed by the calling application.
		case DXGI_ERROR_DEVICE_HUNG: return "DXGI_ERROR_DEVICE_HUNG";

		// The GPU will not respond to more commands, most likely because some other application submitted invalid commands.
		// The calling application should re-create the device and continue.
		case DXGI_ERROR_DEVICE_RESET: return "DXGI_ERROR_DEVICE_RESET";

		// An internal issue prevented the driver from carrying out the specified operation. The driver's state is probably
		// suspect, and the application should not continue.
		case DXGI_ERROR_DRIVER_INTERNAL_ERROR: return "DXGI_ERROR_DRIVER_INTERNAL_ERROR";

		// A resource is not available at the time of the call, but may become available later.
		case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE: return "DXGI_ERROR_NOT_CURRENTLY_AVAILABLE";

		case S_OK: return "S_OK";

		default: break;
		}

		return "Unknown HRESULT?";
	}

	template <typename Ty>
	static BX_NO_INLINE void setDebugObjectName(Ty* _interface, const char* _format, ...)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OBJECT_NAME) )
		{
			char temp[2048];
			va_list argList;
			va_start(argList, _format);
			int size = bx::uint32_min(sizeof(temp)-1, bx::vsnprintf(temp, sizeof(temp), _format, argList) );
			va_end(argList);
			temp[size] = '\0';

			_interface->SetPrivateData(WKPDID_D3DDebugObjectName, size, temp);
		}
	}

	BX_PRAGMA_DIAGNOSTIC_POP();

	static HRESULT setIntelExtension(ID3D11Device* _device, const void* _data, uint32_t _size)
	{
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = _data;
		initData.SysMemPitch = _size;
		initData.SysMemSlicePitch = 0;

		ID3D11Buffer* buffer;
		HRESULT hr = _device->CreateBuffer(&desc, &initData, &buffer);

		if (SUCCEEDED(hr) )
		{
			buffer->Release();
		}

		return hr;
	};

	static const uint32_t kIntelExtensionInterfaceVersion = UINT32_C(0x10000);

	struct IntelExtension
	{
		char     key[16];
		uint32_t version;
		uint32_t type;
		uint32_t data[16];
	};

	static const IntelExtension s_intelDirectAccessResource =
	{
		{ 'I', 'N', 'T', 'C', 'E', 'X', 'T', 'N', 'R', 'E', 'S', 'O', 'U', 'R', 'C', 'E' },
		kIntelExtensionInterfaceVersion,
		1,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	static HRESULT setIntelDirectAccessResource(ID3D11Device* _device)
	{
		return setIntelExtension(_device, &s_intelDirectAccessResource, sizeof(s_intelDirectAccessResource) );
	}

	static BX_NO_INLINE bool getIntelExtensions(ID3D11Device* _device)
	{
		if (windowsVersionIs(Condition::GreaterEqual, 0x0604) )
		{
			uint8_t temp[28];

			bx::StaticMemoryBlockWriter writer(&temp, sizeof(temp) );
			bx::write(&writer, "INTCEXTNCAPSFUNC", 16);
			bx::write(&writer, kIntelExtensionInterfaceVersion);
			bx::write(&writer, UINT32_C(0) );
			bx::write(&writer, UINT32_C(0) );

			if (SUCCEEDED(setIntelExtension(_device, temp, sizeof(temp) ) ) )
			{
				bx::MemoryReader reader(&temp, sizeof(temp) );
				bx::skip(&reader, 16);

				uint32_t version;
				bx::read(&reader, version);

				uint32_t driverVersion;
				bx::read(&reader, driverVersion);

				return version <= driverVersion;
			}
		}

		return false;
	}

	void resume(ID3D11Device* _device)
	{
		BX_UNUSED(_device);
	}

	void suspend(ID3D11Device* _device)
	{
		BX_UNUSED(_device);
	}

	/*
	 * AMD GPU Services (AGS) library
	 *
	 * Reference(s):
	 * - https://web.archive.org/web/20181126035805/https://github.com/GPUOpen-LibrariesAndSDKs/AGS_SDK
	 */
	enum AGS_RETURN_CODE
	{
		AGS_SUCCESS,
		AGS_INVALID_ARGS,
		AGS_OUT_OF_MEMORY,
		AGS_ERROR_MISSING_DLL,
		AGS_ERROR_LEGACY_DRIVER,
		AGS_EXTENSION_NOT_SUPPORTED,
		AGS_ADL_FAILURE,
	};

	enum AGS_DRIVER_EXTENSION
	{
		AGS_EXTENSION_QUADLIST          = 1 << 0,
		AGS_EXTENSION_UAV_OVERLAP       = 1 << 1,
		AGS_EXTENSION_DEPTH_BOUNDS_TEST = 1 << 2,
		AGS_EXTENSION_MULTIDRAWINDIRECT = 1 << 3,
	};

	struct AGSDriverVersionInfo
	{
		char strDriverVersion[256];
		char strCatalystVersion[256];
		char strCatalystWebLink[256];
	};

	struct AGSContext;

	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_INIT)(AGSContext**);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_DEINIT)(AGSContext*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_GET_CROSSFIRE_GPU_COUNT)(AGSContext*, int32_t*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_GET_TOTAL_GPU_COUNT)(AGSContext*, int32_t*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_GET_GPU_MEMORY_SIZE)(AGSContext*, int32_t, int64_t*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_GET_DRIVER_VERSION_INFO)(AGSContext*, AGSDriverVersionInfo*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_DRIVER_EXTENSIONS_INIT)(AGSContext*, ID3D11Device*, uint32_t*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_DRIVER_EXTENSIONS_DEINIT)(AGSContext*);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INSTANCED_INDIRECT)(AGSContext*, uint32_t, ID3D11Buffer*, uint32_t, uint32_t);
	typedef AGS_RETURN_CODE (__cdecl* PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INDEXED_INSTANCED_INDIRECT)(AGSContext*, uint32_t, ID3D11Buffer*, uint32_t, uint32_t);

	static PFN_AGS_INIT   agsInit;
	static PFN_AGS_DEINIT agsDeInit;
	static PFN_AGS_GET_CROSSFIRE_GPU_COUNT  agsGetCrossfireGPUCount;
	static PFN_AGS_GET_TOTAL_GPU_COUNT      agsGetTotalGPUCount;
	static PFN_AGS_GET_GPU_MEMORY_SIZE      agsGetGPUMemorySize;
	static PFN_AGS_GET_DRIVER_VERSION_INFO  agsGetDriverVersionInfo;
	static PFN_AGS_DRIVER_EXTENSIONS_INIT   agsDriverExtensions_Init;
	static PFN_AGS_DRIVER_EXTENSIONS_DEINIT agsDriverExtensions_DeInit;
	static PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INSTANCED_INDIRECT         agsDriverExtensions_MultiDrawInstancedIndirect;
	static PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INDEXED_INSTANCED_INDIRECT agsDriverExtensions_MultiDrawIndexedInstancedIndirect;

	typedef void (* MultiDrawIndirectFn)(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);

	void stubMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);
	void stubMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);

	void amdAgsMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);
	void amdAgsMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);

	void nvapiMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);
	void nvapiMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);

	static MultiDrawIndirectFn multiDrawInstancedIndirect;
	static MultiDrawIndirectFn multiDrawIndexedInstancedIndirect;

#if USE_D3D11_DYNAMIC_LIB
	static PFN_D3D11_CREATE_DEVICE  D3D11CreateDevice;
	static PFN_D3DPERF_SET_MARKER   D3DPERF_SetMarker;
	static PFN_D3DPERF_BEGIN_EVENT  D3DPERF_BeginEvent;
	static PFN_D3DPERF_END_EVENT    D3DPERF_EndEvent;
#endif // USE_D3D11_DYNAMIC_LIB

	int  WINAPI d3d11Annotation_BeginEvent(DWORD _color, LPCWSTR _name);
	int  WINAPI d3d11Annotation_EndEvent();
	void WINAPI d3d11Annotation_SetMarker(DWORD _color, LPCWSTR _name);

	struct RendererContextD3D11 : public RendererContextI
	{
		RendererContextD3D11()
			: m_d3d9Dll(NULL)
			, m_d3d11Dll(NULL)
			, m_renderDocDll(NULL)
			, m_agsDll(NULL)
			, m_ags(NULL)
			, m_featureLevel(D3D_FEATURE_LEVEL(0) )
			, m_swapChain(NULL)
			, m_lost(false)
			, m_numWindows(0)
			, m_device(NULL)
			, m_deviceCtx(NULL)
			, m_annotation(NULL)
			, m_infoQueue(NULL)
			, m_backBufferColor(NULL)
			, m_backBufferDepthStencil(NULL)
			, m_currentColor(NULL)
			, m_currentDepthStencil(NULL)
			, m_captureTexture(NULL)
			, m_captureResolve(NULL)
			, m_maxAnisotropy(1)
			, m_depthClamp(false)
			, m_wireframe(false)
			, m_currentProgram(NULL)
			, m_vsChanges(0)
			, m_fsChanges(0)
			, m_rtMsaa(false)
			, m_timerQuerySupport(false)
			, m_directAccessSupport(false)
			, m_needPresent(false)
		{
			m_fbh.idx = kInvalidHandle;
			bx::memSet(&m_scd, 0, sizeof(m_scd) );
			bx::memSet(&m_windows, 0xff, sizeof(m_windows) );
		}

		~RendererContextD3D11()
		{
		}

		bool init(const Init& _init)
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedD3D11,
					LoadedDXGI,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			m_ags = NULL;
			m_agsDll = bx::dlopen(
#if BX_ARCH_32BIT
				"amd_ags_x86.dll"
#else
				"amd_ags_x64.dll"
#endif // BX_ARCH_32BIT
				);
			if (NULL != m_agsDll)
			{
				agsInit   = (PFN_AGS_INIT  )bx::dlsym(m_agsDll, "agsInit");
				agsDeInit = (PFN_AGS_DEINIT)bx::dlsym(m_agsDll, "agsDeInit");
				agsGetCrossfireGPUCount    = (PFN_AGS_GET_CROSSFIRE_GPU_COUNT )bx::dlsym(m_agsDll, "agsGetCrossfireGPUCount");
				agsGetTotalGPUCount        = (PFN_AGS_GET_TOTAL_GPU_COUNT     )bx::dlsym(m_agsDll, "agsGetTotalGPUCount");
				agsGetGPUMemorySize        = (PFN_AGS_GET_GPU_MEMORY_SIZE     )bx::dlsym(m_agsDll, "agsGetGPUMemorySize");
				agsGetDriverVersionInfo    = (PFN_AGS_GET_DRIVER_VERSION_INFO )bx::dlsym(m_agsDll, "agsGetDriverVersionInfo");
				agsDriverExtensions_Init   = (PFN_AGS_DRIVER_EXTENSIONS_INIT  )bx::dlsym(m_agsDll, "agsDriverExtensions_Init");
				agsDriverExtensions_DeInit = (PFN_AGS_DRIVER_EXTENSIONS_DEINIT)bx::dlsym(m_agsDll, "agsDriverExtensions_DeInit");
				agsDriverExtensions_MultiDrawInstancedIndirect        = (PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INSTANCED_INDIRECT        )bx::dlsym(m_agsDll, "agsDriverExtensions_MultiDrawInstancedIndirect");
				agsDriverExtensions_MultiDrawIndexedInstancedIndirect = (PFN_AGS_DRIVER_EXTENSIONS_MULTIDRAW_INDEXED_INSTANCED_INDIRECT)bx::dlsym(m_agsDll, "agsDriverExtensions_MultiDrawIndexedInstancedIndirect");

				bool agsSupported = true
					&& NULL != agsInit
					&& NULL != agsDeInit
					&& NULL != agsGetCrossfireGPUCount
					&& NULL != agsGetTotalGPUCount
					&& NULL != agsGetGPUMemorySize
					&& NULL != agsGetDriverVersionInfo
					&& NULL != agsDriverExtensions_Init
					&& NULL != agsDriverExtensions_DeInit
					&& NULL != agsDriverExtensions_MultiDrawInstancedIndirect
					&& NULL != agsDriverExtensions_MultiDrawIndexedInstancedIndirect
					;
				if (agsSupported)
				{
					AGS_RETURN_CODE result = agsInit(&m_ags);
					agsSupported = AGS_SUCCESS == result;
					if (agsSupported)
					{
						AGSDriverVersionInfo vi;
						result = agsGetDriverVersionInfo(m_ags, &vi);
						BX_TRACE("      Driver version: %s", vi.strDriverVersion);
						BX_TRACE("    Catalyst version: %s", vi.strCatalystVersion);

						int32_t numCrossfireGPUs = 0;
						result = agsGetCrossfireGPUCount(m_ags, &numCrossfireGPUs);
						BX_TRACE("  Num crossfire GPUs: %d", numCrossfireGPUs);

						int32_t numGPUs = 0;
						result = agsGetTotalGPUCount(m_ags, &numGPUs);
						BX_TRACE("            Num GPUs: %d", numGPUs);

						for (int32_t ii = 0; ii < numGPUs; ++ii)
						{
							long long memSize;
							result = agsGetGPUMemorySize(m_ags, ii, &memSize);
							if (AGS_SUCCESS == result)
							{
								char memSizeStr[16];
								bx::prettify(memSizeStr, BX_COUNTOF(memSizeStr), memSize);
								BX_TRACE("     GPU #%d mem size: %s", ii, memSizeStr);
							}
						}
					}
				}

				BX_WARN(!agsSupported, "AMD/AGS supported.");
				if (!agsSupported)
				{
					if (NULL != m_ags)
					{
						agsDeInit(m_ags);
						m_ags = NULL;
					}

					bx::dlclose(m_agsDll);
					m_agsDll = NULL;
				}
			}

			m_nvapi.init();

#if USE_D3D11_DYNAMIC_LIB
			m_d3d11Dll = bx::dlopen("d3d11.dll");

			if (NULL == m_d3d11Dll)
			{
				BX_TRACE("Init error: Failed to load d3d11.dll.");
				goto error;
			}

			errorState = ErrorState::LoadedD3D11;

			m_d3d9Dll = NULL;

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				// D3D11_1.h has ID3DUserDefinedAnnotation
				// https://web.archive.org/web/20190207230424/https://docs.microsoft.com/en-us/windows/desktop/api/d3d11_1/nn-d3d11_1-id3duserdefinedannotation
				m_d3d9Dll = bx::dlopen("d3d9.dll");
				if (NULL != m_d3d9Dll)
				{
					D3DPERF_SetMarker  = (PFN_D3DPERF_SET_MARKER )bx::dlsym(m_d3d9Dll, "D3DPERF_SetMarker" );
					D3DPERF_BeginEvent = (PFN_D3DPERF_BEGIN_EVENT)bx::dlsym(m_d3d9Dll, "D3DPERF_BeginEvent");
					D3DPERF_EndEvent   = (PFN_D3DPERF_END_EVENT  )bx::dlsym(m_d3d9Dll, "D3DPERF_EndEvent"  );

					if (NULL == D3DPERF_SetMarker
					||  NULL == D3DPERF_BeginEvent
					||  NULL == D3DPERF_EndEvent)
					{
						BX_TRACE("Failed to initialize PIX events.");

						D3DPERF_SetMarker  = NULL;
						D3DPERF_BeginEvent = NULL;
						D3DPERF_EndEvent   = NULL;

						bx::dlclose(m_d3d9Dll);
						m_d3d9Dll = NULL;
					}
				}
			}

			D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)bx::dlsym(m_d3d11Dll, "D3D11CreateDevice");
			if (NULL == D3D11CreateDevice)
			{
				BX_TRACE("Init error: Function D3D11CreateDevice not found.");
				goto error;
			}
#endif // USE_D3D11_DYNAMIC_LIB

			m_device = (ID3D11Device*)g_platformData.context;

			if (!m_dxgi.init(g_caps) )
			{
				goto error;
			}

			errorState = ErrorState::LoadedDXGI;

			if (NULL == m_device)
			{
				if (NULL != m_renderDocDll)
				{
					setGraphicsDebuggerPresent(true);
				}

				D3D_FEATURE_LEVEL featureLevel[] =
				{
					D3D_FEATURE_LEVEL_12_1,
					D3D_FEATURE_LEVEL_12_0,
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
#if BX_PLATFORM_WINRT
					D3D_FEATURE_LEVEL_9_3,
					D3D_FEATURE_LEVEL_9_2,
#endif // BX_PLATFORM_WINRT
				};

				HRESULT hr = S_OK;

				for (;;)
				{
					uint32_t flags = 0
						| D3D11_CREATE_DEVICE_SINGLETHREADED
						| D3D11_CREATE_DEVICE_BGRA_SUPPORT
//						| D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
						| (_init.debug ? D3D11_CREATE_DEVICE_DEBUG : 0)
						;

					hr = E_FAIL;
					for (uint32_t ii = 0; ii < BX_COUNTOF(featureLevel) && FAILED(hr);)
					{
						hr = D3D11CreateDevice(m_dxgi.m_adapter
							, m_dxgi.m_driverType
							, NULL
							, flags
							, &featureLevel[ii]
							, BX_COUNTOF(featureLevel)-ii
							, D3D11_SDK_VERSION
							, &m_device
							, &m_featureLevel
							, &m_deviceCtx
							);
						BX_WARN(FAILED(hr), "Direct3D11 device feature level %d.%d."
							, (m_featureLevel >> 12) & 0xf
							, (m_featureLevel >>  8) & 0xf
							);
						if (FAILED(hr)
						&&  0 != (flags & D3D11_CREATE_DEVICE_DEBUG) )
						{
							// Try without debug in case D3D11 SDK Layers
							// is not present?
							flags &= ~D3D11_CREATE_DEVICE_DEBUG;
							continue;
						}

						// Enable debug flags.
						flags |= (BX_ENABLED(BGFX_CONFIG_DEBUG) ? D3D11_CREATE_DEVICE_DEBUG : 0);
						++ii;
					}

					if (FAILED(hr)
					&&  D3D_DRIVER_TYPE_WARP != m_dxgi.m_driverType)
					{
						// Try with WARP
						m_dxgi.m_driverType = D3D_DRIVER_TYPE_WARP;
						continue;
					}

					break;
				}

				if (FAILED(hr) )
				{
					BX_TRACE("Init error: Unable to create Direct3D11 device.");
					goto error;
				}
			}
			else
			{
				m_device->GetImmediateContext(&m_deviceCtx);

				if (NULL == m_deviceCtx)
				{
					BX_TRACE("Init error: Unable to retrieve Direct3D11 ImmediateContext.");
					goto error;
				}

				m_featureLevel = m_device->GetFeatureLevel();
			}

			m_dxgi.update(m_device);

			{
				m_deviceInterfaceVersion = 0;
				for (uint32_t ii = 0; ii < BX_COUNTOF(s_d3dDeviceIIDs); ++ii)
				{
					ID3D11Device* device;
					HRESULT hr = m_device->QueryInterface(s_d3dDeviceIIDs[ii], (void**)&device);
					if (SUCCEEDED(hr) )
					{
						device->Release(); // BK - ignore ref count.
						m_deviceInterfaceVersion = BX_COUNTOF(s_d3dDeviceIIDs)-ii;
						break;
					}
				}

				{ ///
					IDXGIDevice* renderdoc;
					HRESULT hr = m_device->QueryInterface(IID_IDXGIDeviceRenderDoc, (void**)&renderdoc);
					if (SUCCEEDED(hr) )
					{
						setGraphicsDebuggerPresent(true);
						DX_RELEASE(renderdoc, 2);
					}
					else
					{
						IUnknown* device = m_device;
						setGraphicsDebuggerPresent(2 != getRefCount(device) );
					}
				}

				if (BGFX_PCI_ID_NVIDIA != m_dxgi.m_adapterDesc.VendorId)
				{
					m_nvapi.shutdown();
				}

				m_msaaRt = NULL;

				if (NULL == g_platformData.backBuffer)
				{
					HRESULT hr = S_OK;

					m_swapEffect =
#if BX_PLATFORM_WINDOWS
						DXGI_SWAP_EFFECT_FLIP_DISCARD
#else
						DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
#endif // !BX_PLATFORM_WINDOWS
						;

					m_swapBufferCount = bx::clamp<uint8_t>(_init.resolution.numBackBuffers, 2, BGFX_CONFIG_MAX_BACK_BUFFERS);

					bx::memSet(&m_scd, 0, sizeof(m_scd) );
					m_scd.width  = _init.resolution.width;
					m_scd.height = _init.resolution.height;
					m_scd.format = (_init.resolution.reset & BGFX_RESET_SRGB_BACKBUFFER)
						? s_textureFormat[_init.resolution.format].m_fmtSrgb
						: s_textureFormat[_init.resolution.format].m_fmt
						;

					updateMsaa(m_scd.format);
					m_scd.sampleDesc  = s_msaa[(_init.resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

					m_scd.bufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					m_scd.bufferCount = m_swapBufferCount;
					m_scd.scaling = 0 == g_platformData.ndt
						? DXGI_SCALING_NONE
						: DXGI_SCALING_STRETCH
						;
					m_scd.swapEffect = m_swapEffect;
					m_scd.alphaMode  = DXGI_ALPHA_MODE_IGNORE;
					m_scd.flags      = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

					m_scd.maxFrameLatency = bx::min<uint8_t>(_init.resolution.maxFrameLatency, 3);
					m_scd.nwh             = g_platformData.nwh;
					m_scd.ndt             = g_platformData.ndt;
					m_scd.windowed        = true;

					if (NULL != m_scd.nwh)
					{
						hr = m_dxgi.createSwapChain(m_device
							, m_scd
							, &m_swapChain
							);

						if (FAILED(hr) )
						{
							// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL is not available on win7
							// Try again with DXGI_SWAP_EFFECT_DISCARD
							m_swapEffect      = DXGI_SWAP_EFFECT_DISCARD;
							m_swapBufferCount = 1;

							m_scd.bufferCount = m_swapBufferCount;
							m_scd.swapEffect  = m_swapEffect;
							hr = m_dxgi.createSwapChain(m_device
								, m_scd
								, &m_swapChain
								);

							if (FAILED(hr) )
							{
								BX_TRACE("Init error: Failed to create swap chain.");
								goto error;
							}
						}

						m_resolution       = _init.resolution;
						m_resolution.reset = _init.resolution.reset & (~BGFX_RESET_INTERNAL_FORCE);

						m_textVideoMem.resize(false, _init.resolution.width, _init.resolution.height);
						m_textVideoMem.clear();

						if (1 < m_scd.sampleDesc.Count)
						{
							D3D11_TEXTURE2D_DESC desc;
							desc.Width      = m_scd.width;
							desc.Height     = m_scd.height;
							desc.MipLevels  = 1;
							desc.ArraySize  = 1;
							desc.Format     = m_scd.format;
							desc.SampleDesc = m_scd.sampleDesc;
							desc.Usage      = D3D11_USAGE_DEFAULT;
							desc.BindFlags  = D3D11_BIND_RENDER_TARGET;
							desc.CPUAccessFlags = 0;
							desc.MiscFlags      = 0;
							DX_CHECK(m_device->CreateTexture2D(&desc, NULL, &m_msaaRt) );
						}
					}

#if BX_PLATFORM_WINDOWS
					DX_CHECK(m_dxgi.m_factory->MakeWindowAssociation( (HWND)g_platformData.nwh, 0
						| DXGI_MWA_NO_WINDOW_CHANGES
						| DXGI_MWA_NO_ALT_ENTER
						) );
#endif // BX_PLATFORM_WINDOWS

					if (FAILED(hr) )
					{
						BX_TRACE("Init error: Failed to create swap chain.");
						goto error;
					}
				}
				else
				{
					bx::memSet(&m_scd, 0, sizeof(m_scd) );
					m_scd.sampleDesc.Count   = 1;
					m_scd.sampleDesc.Quality = 0;
					m_scd.width  = _init.resolution.width;
					m_scd.height = _init.resolution.height;
					m_backBufferColor        = (ID3D11RenderTargetView*)g_platformData.backBuffer;
					m_backBufferDepthStencil = (ID3D11DepthStencilView*)g_platformData.backBufferDS;
				}
			}

			m_numWindows = 1;

#if USE_D3D11_DYNAMIC_LIB
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				HRESULT hr = m_deviceCtx->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&m_annotation);

				if (SUCCEEDED(hr) )
				{
					D3DPERF_BeginEvent = d3d11Annotation_BeginEvent;
					D3DPERF_EndEvent   = d3d11Annotation_EndEvent;
					D3DPERF_SetMarker  = d3d11Annotation_SetMarker;
				}
			}
#endif // USE_D3D11_DYNAMIC_LIB

			if (_init.debug)
			{
				HRESULT hr = m_device->QueryInterface(IID_ID3D11InfoQueue, (void**)&m_infoQueue);

				if (SUCCEEDED(hr) )
				{
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR,      false);
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING,    false);
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_INFO,       false);
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_MESSAGE,    false);

					D3D11_INFO_QUEUE_FILTER filter;
					bx::memSet(&filter, 0, sizeof(filter) );

					D3D11_MESSAGE_CATEGORY catlist[] =
					{
						D3D11_MESSAGE_CATEGORY_STATE_CREATION,
					};

					filter.DenyList.NumCategories = BX_COUNTOF(catlist);
					filter.DenyList.pCategoryList = catlist;

					D3D11_MESSAGE_ID idlist[] =
					{
						D3D11_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET,
						D3D11_MESSAGE_ID_QUERY_BEGIN_ABANDONING_PREVIOUS_RESULTS,
					};

					filter.DenyList.NumIDs  = BX_COUNTOF(idlist);
					filter.DenyList.pIDList = idlist;

					m_infoQueue->PushStorageFilter(&filter);
				}
			}

			{
				g_caps.supported |= (0
					| BGFX_CAPS_TEXTURE_3D
					| BGFX_CAPS_VERTEX_ATTRIB_HALF
					| BGFX_CAPS_VERTEX_ATTRIB_UINT10
					| BGFX_CAPS_VERTEX_ID
					| BGFX_CAPS_FRAGMENT_DEPTH
					| (getIntelExtensions(m_device)
						? BGFX_CAPS_FRAGMENT_ORDERING
						| BGFX_CAPS_TEXTURE_DIRECT_ACCESS
						: 0)
					| BGFX_CAPS_SWAP_CHAIN
					| BGFX_CAPS_DRAW_INDIRECT
					| BGFX_CAPS_TEXTURE_BLIT
					| BGFX_CAPS_TEXTURE_READ_BACK
					| ( (m_featureLevel >= D3D_FEATURE_LEVEL_9_2)
						? BGFX_CAPS_OCCLUSION_QUERY
						: 0)
					| BGFX_CAPS_ALPHA_TO_COVERAGE
					| ( (m_deviceInterfaceVersion >= 3)
						? BGFX_CAPS_CONSERVATIVE_RASTER
						: 0)
					| BGFX_CAPS_TEXTURE_2D_ARRAY
					| BGFX_CAPS_TEXTURE_CUBE_ARRAY
					| ((m_featureLevel >= D3D_FEATURE_LEVEL_11_1)
						? BGFX_CAPS_FRAMEBUFFER_RW
						: 0)
					);

				m_timerQuerySupport   = m_featureLevel >= D3D_FEATURE_LEVEL_10_0;
				m_directAccessSupport = 0 != (g_caps.supported & BGFX_CAPS_TEXTURE_DIRECT_ACCESS);

				if (m_featureLevel <= D3D_FEATURE_LEVEL_9_2)
				{
					g_caps.limits.maxTextureSize   = D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
					g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(
						  D3D_FL9_1_SIMULTANEOUS_RENDER_TARGET_COUNT
						, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
						) );
					g_caps.limits.maxVertexStreams = uint8_t(bx::uint32_min(
						  16
						, BGFX_CONFIG_MAX_VERTEX_STREAMS
						) );
				}
				else if (m_featureLevel == D3D_FEATURE_LEVEL_9_3)
				{
					g_caps.limits.maxTextureSize   = D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION;
					g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(
						  D3D_FL9_3_SIMULTANEOUS_RENDER_TARGET_COUNT
						, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
						) );
					g_caps.limits.maxVertexStreams = uint8_t(bx::uint32_min(
						  16
						, BGFX_CONFIG_MAX_VERTEX_STREAMS
						) );
				}
				else
				{
					g_caps.limits.maxComputeBindings = bx::min(BGFX_MAX_COMPUTE_BINDINGS
						, D3D_FEATURE_LEVEL_11_1 <= m_featureLevel
						? D3D11_1_UAV_SLOT_COUNT
						: D3D11_PS_CS_UAV_REGISTER_COUNT
						);

					g_caps.supported |= BGFX_CAPS_TEXTURE_COMPARE_ALL;
					g_caps.limits.maxTextureSize   = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
					g_caps.limits.maxTextureLayers = D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
					g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(
						  D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT
						, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
						) );
					g_caps.limits.maxVertexStreams = uint8_t(bx::uint32_min(
						  D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT
						, BGFX_CONFIG_MAX_VERTEX_STREAMS
						) );
				}

				// 32-bit indices only supported on 9_2+.
				if (m_featureLevel >= D3D_FEATURE_LEVEL_9_2)
				{
					g_caps.supported |= BGFX_CAPS_INDEX32;
				}

				// Independent blend only supported on 10_1+.
				if (m_featureLevel >= D3D_FEATURE_LEVEL_10_1)
				{
					g_caps.supported |= BGFX_CAPS_BLEND_INDEPENDENT;
				}

				// Compute support is optional on 10_0 and 10_1 targets.
				if (m_featureLevel == D3D_FEATURE_LEVEL_10_0
				||  m_featureLevel == D3D_FEATURE_LEVEL_10_1)
				{
					struct D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS
					{
						BOOL ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
					};

					D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS data;
					HRESULT hr = m_device->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &data, sizeof(data) );
					if (SUCCEEDED(hr)
					&&  data.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x)
					{
						g_caps.supported |= BGFX_CAPS_COMPUTE;
					}
				}
				else if (m_featureLevel >= D3D_FEATURE_LEVEL_11_0)
				{
					g_caps.supported |= BGFX_CAPS_COMPUTE;
				}

				// Instancing fully supported on 9_3+, optionally partially supported at lower levels.
				if (m_featureLevel >= D3D_FEATURE_LEVEL_9_3)
				{
					g_caps.supported |= BGFX_CAPS_INSTANCING;
				}
				else
				{
					struct D3D11_FEATURE_DATA_D3D9_SIMPLE_INSTANCING_SUPPORT
					{
						BOOL SimpleInstancingSupported;
					};

					D3D11_FEATURE_DATA_D3D9_SIMPLE_INSTANCING_SUPPORT data;
					HRESULT hr = m_device->CheckFeatureSupport(D3D11_FEATURE(11) /*D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT*/, &data, sizeof(data) );
					if (SUCCEEDED(hr)
					&&  data.SimpleInstancingSupported)
					{
						g_caps.supported |= BGFX_CAPS_INSTANCING;
					}
				}

				// shadow compare is optional on 9_1 through 9_3 targets
				if (m_featureLevel <= D3D_FEATURE_LEVEL_9_3)
				{
					struct D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT
					{
						BOOL SupportsDepthAsTextureWithLessEqualComparisonFilter;
					};

					D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT data;
					HRESULT hr = m_device->CheckFeatureSupport(D3D11_FEATURE(9) /*D3D11_FEATURE_D3D9_SHADOW_SUPPORT*/, &data, sizeof(data) );
					if (SUCCEEDED(hr)
					&&  data.SupportsDepthAsTextureWithLessEqualComparisonFilter)
					{
						g_caps.supported |= BGFX_CAPS_TEXTURE_COMPARE_LEQUAL;
					}
				}

				for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
				{
					uint16_t support = BGFX_CAPS_FORMAT_TEXTURE_NONE;

					const DXGI_FORMAT fmt = bimg::isDepth(bimg::TextureFormat::Enum(ii) )
						? s_textureFormat[ii].m_fmtDsv
						: s_textureFormat[ii].m_fmt
						;
					const DXGI_FORMAT fmtSrgb = s_textureFormat[ii].m_fmtSrgb;

					if (DXGI_FORMAT_UNKNOWN != fmt)
					{
						if (BX_ENABLED(BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT) )
						{
							struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
							{
								DXGI_FORMAT InFormat;
								UINT OutFormatSupport;
							};

							D3D11_FEATURE_DATA_FORMAT_SUPPORT data; // D3D11_FEATURE_DATA_FORMAT_SUPPORT2
							data.InFormat = fmt;
							HRESULT hr = m_device->CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof(data) );
							if (SUCCEEDED(hr) )
							{
								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURE2D
										| D3D11_FORMAT_SUPPORT_TEXTURE3D
										| D3D11_FORMAT_SUPPORT_TEXTURECUBE
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_2D
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURE3D
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_3D
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURECUBE
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_CUBE
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_BUFFER
										| D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER
										| D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_VERTEX
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_SHADER_LOAD
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_IMAGE
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_RENDER_TARGET
										| D3D11_FORMAT_SUPPORT_DEPTH_STENCIL
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_MSAA
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_MIP_AUTOGEN
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;
							}
							else
							{
								BX_TRACE("CheckFeatureSupport failed with %x for format %s.", hr, getName(TextureFormat::Enum(ii) ) );
							}

							if (0 != (support & BGFX_CAPS_FORMAT_TEXTURE_IMAGE) )
							{
								// clear image flag for additional testing
								support &= ~BGFX_CAPS_FORMAT_TEXTURE_IMAGE;

								data.InFormat = s_textureFormat[ii].m_fmt;
								hr = m_device->CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT2, &data, sizeof(data) );
								if (SUCCEEDED(hr) )
								{
									support |= 0 != (data.OutFormatSupport & (0
											| D3D11_FORMAT_SUPPORT2_UAV_TYPED_LOAD
											| D3D11_FORMAT_SUPPORT2_UAV_TYPED_STORE
											) )
											? BGFX_CAPS_FORMAT_TEXTURE_IMAGE
											: BGFX_CAPS_FORMAT_TEXTURE_NONE
											;
								}
							}
						}
						else
						{
							support |= 0
								| BGFX_CAPS_FORMAT_TEXTURE_2D
								| BGFX_CAPS_FORMAT_TEXTURE_3D
								| BGFX_CAPS_FORMAT_TEXTURE_CUBE
								| BGFX_CAPS_FORMAT_TEXTURE_IMAGE
								| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
								| BGFX_CAPS_FORMAT_TEXTURE_IMAGE
								| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
								| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
								| BGFX_CAPS_FORMAT_TEXTURE_MSAA
								;
						}
					}

					if (DXGI_FORMAT_UNKNOWN != fmtSrgb)
					{
						if (BX_ENABLED(BX_PLATFORM_WINDOWS || BX_PLATFORM_WINRT) )
						{
							struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
							{
								DXGI_FORMAT InFormat;
								UINT OutFormatSupport;
							};

							D3D11_FEATURE_DATA_FORMAT_SUPPORT data; // D3D11_FEATURE_DATA_FORMAT_SUPPORT2
							data.InFormat = fmtSrgb;
							HRESULT hr = m_device->CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof(data) );
							if (SUCCEEDED(hr) )
							{
								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURE2D
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURE3D
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;

								support |= 0 != (data.OutFormatSupport & (0
										| D3D11_FORMAT_SUPPORT_TEXTURECUBE
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;
							}
							else
							{
								BX_TRACE("CheckFeatureSupport failed with %x for sRGB format %s.", hr, getName(TextureFormat::Enum(ii) ) );
							}
						}
						else
						{
							support |= 0
								| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
								| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
								| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
								;
						}
					}

					g_caps.formats[ii] = support;
				}

				// Init reserved part of view name.
				for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
				{
					bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED + 1, "%3d   ", ii);
					mbstowcs(s_viewNameW[ii], s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED);
				}

				if (_init.debug
				&&  NULL != m_infoQueue)
				{
					m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
				}

				{ //
					multiDrawInstancedIndirect        = stubMultiDrawInstancedIndirect;
					multiDrawIndexedInstancedIndirect = stubMultiDrawIndexedInstancedIndirect;
					if (NULL != m_ags)
					{
						uint32_t flags;
						AGS_RETURN_CODE result = agsDriverExtensions_Init(m_ags, m_device, &flags);
						bool hasExtensions = AGS_SUCCESS == result;

						if (hasExtensions
						&&  0 != (flags & AGS_EXTENSION_MULTIDRAWINDIRECT) )
						{
							multiDrawInstancedIndirect        = amdAgsMultiDrawInstancedIndirect;
							multiDrawIndexedInstancedIndirect = amdAgsMultiDrawIndexedInstancedIndirect;
						}
						else
						{
							if (hasExtensions)
							{
								agsDriverExtensions_DeInit(m_ags);
							}

							agsDeInit(m_ags);
							m_ags = NULL;
						}
					}
					else if (m_nvapi.isInitialized()
						 &&  NULL != m_nvapi.nvApiD3D11MultiDrawInstancedIndirect
						 &&  NULL != m_nvapi.nvApiD3D11MultiDrawIndexedInstancedIndirect)
					{
						multiDrawInstancedIndirect        = nvapiMultiDrawInstancedIndirect;
						multiDrawIndexedInstancedIndirect = nvapiMultiDrawIndexedInstancedIndirect;
					}
				}

				//
				updateMsaa(m_scd.format);
				postReset();
			}

			m_nvapi.initAftermath(m_device, m_deviceCtx);

			g_internalData.context = m_device;
			return true;

		error:
			switch (errorState)
			{
			case ErrorState::LoadedDXGI:
				DX_RELEASE(m_annotation, 1);
				DX_RELEASE_W(m_infoQueue, 0);
				DX_RELEASE(m_msaaRt, 0);
				DX_RELEASE(m_swapChain, 0);
				DX_RELEASE(m_deviceCtx, 0);
				DX_RELEASE(m_device, 0);

#if USE_D3D11_DYNAMIC_LIB
				if (NULL != m_d3d9Dll)
				{
					bx::dlclose(m_d3d9Dll);
					m_d3d9Dll = NULL;
				}
#endif // USE_D3D11_DYNAMIC_LIB

				m_dxgi.shutdown();
				BX_FALLTHROUGH;

#if USE_D3D11_DYNAMIC_LIB
			case ErrorState::LoadedD3D11:
				bx::dlclose(m_d3d11Dll);
				m_d3d11Dll = NULL;
				BX_FALLTHROUGH;
#endif // USE_D3D11_DYNAMIC_LIB

			case ErrorState::Default:
			default:
				m_nvapi.shutdown();

				if (NULL != m_ags)
				{
					agsDeInit(m_ags);
					m_ags = NULL;
				}

				bx::dlclose(m_agsDll);
				m_agsDll = NULL;

				unloadRenderDoc(m_renderDocDll);
				break;
			}

			return false;
		}

		void shutdown()
		{
			preReset();

			if (NULL != m_ags)
			{
				agsDeInit(m_ags);
				m_ags = NULL;
			}

			bx::dlclose(m_agsDll);
			m_agsDll = NULL;

			m_deviceCtx->ClearState();

			invalidateCache();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].destroy();
			}

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

			DX_RELEASE(m_annotation, 1);
			DX_RELEASE_W(m_infoQueue, 0);
			DX_RELEASE(m_msaaRt, 0);
			DX_RELEASE(m_swapChain, 0);
			DX_RELEASE(m_deviceCtx, 0);
			DX_RELEASE(m_device, 0);

			m_nvapi.shutdown();
			m_dxgi.shutdown();

			unloadRenderDoc(m_renderDocDll);

#if USE_D3D11_DYNAMIC_LIB
			if (NULL != m_d3d9Dll)
			{
				bx::dlclose(m_d3d9Dll);
				m_d3d9Dll = NULL;
			}

			bx::dlclose(m_d3d11Dll);
			m_d3d11Dll = NULL;
#endif // USE_D3D11_DYNAMIC_LIB
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Direct3D11;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_DIRECT3D11_NAME;
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

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _layoutHandle, _flags);
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

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle layoutHandle = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, layoutHandle, _flags);
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
			return m_textures[_handle.idx].create(_mem, _flags, _skip);
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			const TextureD3D11& texture = m_textures[_handle.idx];
			D3D11_MAPPED_SUBRESOURCE mapped;
			DX_CHECK(m_deviceCtx->Map(texture.m_ptr, _mip, D3D11_MAP_READ, 0, &mapped) );

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width >>_mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height>>_mip);
			uint8_t* src       = (uint8_t*)mapped.pData;
			uint32_t srcPitch  = mapped.RowPitch;

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

			m_deviceCtx->Unmap(texture.m_ptr, _mip);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureD3D11& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc);

			texture.destroy();
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
			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferHandle handle = m_windows[ii];
				if (isValid(handle)
				&&  m_frameBuffers[handle.idx].m_nwh == _nwh)
				{
					destroyFrameBuffer(handle);
				}
			}

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
			IDXGISwapChain* swapChain = isValid(_handle)
				? m_frameBuffers[_handle.idx].m_swapChain
				: m_swapChain
				;

			if (NULL == swapChain)
			{
				BX_TRACE("Unable to capture screenshot %s.", _filePath);
				return;
			}

			ID3D11Texture2D* backBuffer;
			DX_CHECK(swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBuffer) );

			D3D11_TEXTURE2D_DESC backBufferDesc;
			backBuffer->GetDesc(&backBufferDesc);

			D3D11_TEXTURE2D_DESC desc;
			bx::memCopy(&desc, &backBufferDesc, sizeof(desc) );
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

			ID3D11Texture2D* texture;
			HRESULT hr = m_device->CreateTexture2D(&desc, NULL, &texture);
			if (SUCCEEDED(hr) )
			{
				if (backBufferDesc.SampleDesc.Count == 1)
				{
					m_deviceCtx->CopyResource(texture, backBuffer);
				}
				else
				{
					desc.Usage = D3D11_USAGE_DEFAULT;
					desc.CPUAccessFlags = 0;
					ID3D11Texture2D* resolve;
					hr = m_device->CreateTexture2D(&desc, NULL, &resolve);
					if (SUCCEEDED(hr) )
					{
						m_deviceCtx->ResolveSubresource(resolve, 0, backBuffer, 0, desc.Format);
						m_deviceCtx->CopyResource(texture, resolve);
						DX_RELEASE(resolve, 0);
					}
				}

				D3D11_MAPPED_SUBRESOURCE mapped;
				DX_CHECK(m_deviceCtx->Map(texture, 0, D3D11_MAP_READ, 0, &mapped) );
				bimg::imageSwizzleBgra8(
					  mapped.pData
					, mapped.RowPitch
					, backBufferDesc.Width
					, backBufferDesc.Height
					, mapped.pData
					, mapped.RowPitch
					);
				g_callback->screenShot(_filePath
					, backBufferDesc.Width
					, backBufferDesc.Height
					, mapped.RowPitch
					, mapped.pData
					, backBufferDesc.Height*mapped.RowPitch
					, false
					);
				m_deviceCtx->Unmap(texture, 0);

				DX_RELEASE(texture, 0);
			}

			DX_RELEASE(backBuffer, 0);
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
				name[_len] = L'\0';
				mbstowcs(name, _marker, _len);
				PIX_SETMARKER(kColorMarker, name);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				setDebugObjectName(m_indexBuffers[_handle.idx].m_ptr, "%.*s", _len, _name);
				break;

			case Handle::Shader:
				setDebugObjectName(m_shaders[_handle.idx].m_ptr, "%.*s", _len, _name);
				break;

			case Handle::Texture:
				setDebugObjectName(m_textures[_handle.idx].m_ptr, "%.*s", _len, _name);
				break;

			case Handle::VertexBuffer:
				setDebugObjectName(m_vertexBuffers[_handle.idx].m_ptr, "%.*s", _len, _name);
				break;

			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			ID3D11DeviceContext* deviceCtx = m_deviceCtx;

			const uint32_t width  = m_scd.width;
			const uint32_t height = m_scd.height;

			setFrameBuffer(BGFX_INVALID_HANDLE, false, false);

			D3D11_VIEWPORT vp;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			vp.Width    = (float)width;
			vp.Height   = (float)height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			deviceCtx->RSSetViewports(1, &vp);

			uint64_t state = BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			setBlendState(state);
			setDepthStencilState(state);
			setRasterizerState(state);

			ProgramD3D11& program = m_program[_blitter.m_program.idx];
			m_currentProgram = &program;
			deviceCtx->VSSetShader(program.m_vsh->m_vertexShader, NULL, 0);
			deviceCtx->VSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);
			deviceCtx->PSSetShader(program.m_fsh->m_pixelShader, NULL, 0);
			deviceCtx->PSSetConstantBuffers(0, 1, &program.m_fsh->m_buffer);

			VertexBufferD3D11& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
			VertexLayout& layout  = m_vertexLayouts[_blitter.m_vb->layoutHandle.idx];
			uint32_t stride = layout.m_stride;
			uint32_t offset = 0;
			deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
			setInputLayout(layout, program, 0);

			IndexBufferD3D11& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			deviceCtx->IASetIndexBuffer(ib.m_ptr, DXGI_FORMAT_R16_UINT, 0);

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

			PredefinedUniform& predefined = program.m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			commitShaderConstants();
			m_textures[_blitter.m_texture.idx].commit(0, BGFX_SAMPLER_INTERNAL_DEFAULT, NULL);
			commitTextureStage();
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				ID3D11DeviceContext* deviceCtx = m_deviceCtx;

				m_indexBuffers [_blitter.m_ib->handle.idx].update(0, _numIndices*2, _blitter.m_ib->data, true);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(0, numVertices*_blitter.m_layout.m_stride, _blitter.m_vb->data, true);

				deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				deviceCtx->DrawIndexed(_numIndices, 0, 0);
			}
		}

		void preReset()
		{
			m_needPresent = false;

			if (m_timerQuerySupport)
			{
				m_gpuTimer.preReset();
			}
			m_occlusionQuery.preReset();

			if (NULL == g_platformData.backBufferDS)
			{
				DX_RELEASE(m_backBufferDepthStencil, 0);
			}

			if (NULL != m_swapChain)
			{
				DX_RELEASE(m_backBufferColor, 0);
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].preReset();
			}

//			invalidateCache();

			capturePreReset();
		}

		void postReset()
		{
			if (NULL != m_swapChain)
			{
				ID3D11Texture2D* backBufferColor = NULL;
				if (NULL == m_msaaRt)
				{
					DX_CHECK(m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBufferColor) );
				}

				D3D11_RENDER_TARGET_VIEW_DESC desc;
				desc.ViewDimension = (m_resolution.reset & BGFX_RESET_MSAA_MASK)
					? D3D11_RTV_DIMENSION_TEXTURE2DMS
					: D3D11_RTV_DIMENSION_TEXTURE2D
					;
				desc.Texture2D.MipSlice = 0;
				desc.Format = (m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER)
					? m_scd.format == DXGI_FORMAT_R8G8B8A8_UNORM ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : m_scd.format
					: m_scd.format
					;

				DX_CHECK(m_device->CreateRenderTargetView(NULL == m_msaaRt ? backBufferColor : m_msaaRt, &desc, &m_backBufferColor) );
				DX_RELEASE(backBufferColor, 0);
			}

			if (m_timerQuerySupport)
			{
				m_gpuTimer.postReset();
			}
			m_occlusionQuery.postReset();

			if (NULL == m_backBufferDepthStencil)
			{
				D3D11_TEXTURE2D_DESC dsd;
				dsd.Width  = m_scd.width;
				dsd.Height = m_scd.height;
				dsd.MipLevels  = 1;
				dsd.ArraySize  = 1;
				dsd.Format     = DXGI_FORMAT_D24_UNORM_S8_UINT;
				dsd.SampleDesc = m_scd.sampleDesc;
				dsd.Usage      = D3D11_USAGE_DEFAULT;
				dsd.BindFlags  = D3D11_BIND_DEPTH_STENCIL;
				dsd.CPUAccessFlags = 0;
				dsd.MiscFlags      = 0;

				ID3D11Texture2D* depthStencil;
				DX_CHECK(m_device->CreateTexture2D(&dsd, NULL, &depthStencil) );
				DX_CHECK(m_device->CreateDepthStencilView(depthStencil, NULL, &m_backBufferDepthStencil) );
				DX_RELEASE(depthStencil, 0);
			}

			m_deviceCtx->OMSetRenderTargets(1, &m_backBufferColor, m_backBufferDepthStencil);

			m_currentColor        = m_backBufferColor;
			m_currentDepthStencil = m_backBufferDepthStencil;

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}

			capturePostReset();
		}

		bool isDeviceRemoved() override
		{
			return m_lost;
		}

		void flip() override
		{
			if (!m_lost)
			{
				HRESULT hr = S_OK;
				uint32_t syncInterval = BX_ENABLED(!BX_PLATFORM_WINDOWS)
					? 1 // sync interval of 0 is not supported on WinRT
					: !!(m_resolution.reset & BGFX_RESET_VSYNC)
					;

				for (uint32_t ii = 1, num = m_numWindows; ii < num && SUCCEEDED(hr); ++ii)
				{
					hr = m_frameBuffers[m_windows[ii].idx].present(syncInterval);
				}

				if (SUCCEEDED(hr) )
				{
					if (NULL != m_swapChain
					&&  m_needPresent)
					{
						hr = m_swapChain->Present(syncInterval, 0);

						m_needPresent = false;
					}
					else
					{
						m_deviceCtx->Flush();
					}
				}

				m_lost = isLost(hr);
				BGFX_FATAL(!m_lost
					, bgfx::Fatal::DeviceLost
					, "Device is lost. FAILED 0x%08x %s (%s)"
					, hr
					, getLostReason(hr)
					, DXGI_ERROR_DEVICE_REMOVED == hr ? getLostReason(m_device->GetDeviceRemovedReason() ) : "no info"
					);
			}
		}

		void invalidateCache()
		{
			m_inputLayoutCache.invalidate();
			m_blendStateCache.invalidate();
			m_depthStencilStateCache.invalidate();
			m_rasterizerStateCache.invalidate();
			m_samplerStateCache.invalidate();
			m_srvUavLru.invalidate();
		}

		void invalidateCompute()
		{
			const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;
			const uint32_t maxTextureSamplers = g_caps.limits.maxTextureSamplers;

			m_deviceCtx->CSSetShader(NULL, NULL, 0);
			m_deviceCtx->CSSetUnorderedAccessViews(0, maxComputeBindings, s_zero.m_uav, NULL);
			m_deviceCtx->CSSetShaderResources(0, maxTextureSamplers, s_zero.m_srv);
			m_deviceCtx->CSSetSamplers(0, maxTextureSamplers, s_zero.m_sampler);
		}

		void updateMsaa(DXGI_FORMAT _format) const
		{
			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				uint32_t msaa = s_checkMsaa[ii];
				uint32_t quality = 0;
				HRESULT hr = m_device->CheckMultisampleQualityLevels(_format, msaa, &quality);

				if (SUCCEEDED(hr)
				&&  0 < quality)
				{
					s_msaa[ii].Count = msaa;
					s_msaa[ii].Quality = quality - 1;
					last = ii;
				}
				else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}
		}

		bool updateResolution(const Resolution& _resolution)
		{
			const bool suspended    = !!( _resolution.reset & BGFX_RESET_SUSPEND);
			const bool wasSuspended = !!(m_resolution.reset & BGFX_RESET_SUSPEND);
			if (suspended && wasSuspended)
			{
				return true;
			}
			else if (suspended)
			{
				m_deviceCtx->Flush();
				m_deviceCtx->ClearState();
				m_dxgi.trim();
				suspend(m_device);
				m_resolution.reset |= BGFX_RESET_SUSPEND;
				return true;
			}
			else if (wasSuspended)
			{
				resume(m_device);
				m_resolution.reset &= ~BGFX_RESET_SUSPEND;
			}

			uint32_t maxAnisotropy = 1;
			if (!!(_resolution.reset & BGFX_RESET_MAXANISOTROPY) )
			{
				maxAnisotropy = (m_featureLevel == D3D_FEATURE_LEVEL_9_1)
								? D3D_FL9_1_DEFAULT_MAX_ANISOTROPY
								: D3D11_REQ_MAXANISOTROPY
								;
			}

			if (m_maxAnisotropy != maxAnisotropy)
			{
				m_maxAnisotropy = maxAnisotropy;
				m_samplerStateCache.invalidate();
			}

			bool depthClamp = true
				&& !!(_resolution.reset & BGFX_RESET_DEPTH_CLAMP)
				&& m_featureLevel > D3D_FEATURE_LEVEL_9_3 // disabling depth clamp is only supported on 10_0+
				;

			if (m_depthClamp != depthClamp)
			{
				m_depthClamp = depthClamp;
				m_rasterizerStateCache.invalidate();
			}

			const uint32_t maskFlags = ~(0
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.width            !=  _resolution.width
			||  m_resolution.height           !=  _resolution.height
			||  m_resolution.format           !=  _resolution.format
			|| (m_resolution.reset&maskFlags) != (_resolution.reset&maskFlags) )
			{
				uint32_t flags = _resolution.reset & (~BGFX_RESET_INTERNAL_FORCE);

				bool resize = true
					&& !BX_ENABLED(BX_PLATFORM_XBOXONE || BX_PLATFORM_WINRT) // can't use ResizeBuffers on Windows Phone
					&& (m_resolution.reset&BGFX_RESET_MSAA_MASK) == (flags&BGFX_RESET_MSAA_MASK)
					;

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				m_scd.width  = _resolution.width;
				m_scd.height = _resolution.height;
				m_scd.format = (_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER)
					? s_textureFormat[_resolution.format].m_fmtSrgb
					: s_textureFormat[_resolution.format].m_fmt
					;

				preReset();

				m_deviceCtx->Flush();
				m_deviceCtx->ClearState();

				if (NULL == m_swapChain)
				{
					// Updated backbuffer if it changed in PlatformData.
					m_backBufferColor        = (ID3D11RenderTargetView*)g_platformData.backBuffer;
					m_backBufferDepthStencil = (ID3D11DepthStencilView*)g_platformData.backBufferDS;
				}
				else
				{
					DX_RELEASE(m_msaaRt, 0);

					if (resize)
					{
						m_deviceCtx->OMSetRenderTargets(1, s_zero.m_rtv, NULL);

						DX_CHECK(m_dxgi.resizeBuffers(m_swapChain, m_scd) );
					}
					else
					{
						updateMsaa(m_scd.format);
						m_scd.sampleDesc = s_msaa[(m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

						DX_RELEASE(m_swapChain, 0);

						HRESULT hr = m_dxgi.createSwapChain(m_device
							, m_scd
							, &m_swapChain
							);
						BGFX_FATAL(SUCCEEDED(hr), bgfx::Fatal::UnableToInitialize, "Failed to create swap chain.");
					}

					if (1 < m_scd.sampleDesc.Count)
					{
						D3D11_TEXTURE2D_DESC desc;
						desc.Width      = m_scd.width;
						desc.Height     = m_scd.height;
						desc.MipLevels  = 1;
						desc.ArraySize  = 1;
						desc.Format     = m_scd.format;
						desc.SampleDesc = m_scd.sampleDesc;
						desc.Usage      = D3D11_USAGE_DEFAULT;
						desc.BindFlags  = D3D11_BIND_RENDER_TARGET;
						desc.CPUAccessFlags = 0;
						desc.MiscFlags      = 0;
						DX_CHECK(m_device->CreateTexture2D(&desc, NULL, &m_msaaRt) );
					}
				}

				postReset();
			}

			return false;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags&kUniformFragmentBit)
			{
				bx::memCopy(&m_fsScratch[_regIndex], _val, _numRegs*16);
				m_fsChanges += _numRegs;
			}
			else
			{
				bx::memCopy(&m_vsScratch[_regIndex], _val, _numRegs*16);
				m_vsChanges += _numRegs;
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

		void commitShaderConstants()
		{
			if (0 < m_vsChanges)
			{
				if (NULL != m_currentProgram->m_vsh->m_buffer)
				{
					m_deviceCtx->UpdateSubresource(m_currentProgram->m_vsh->m_buffer, 0, 0, m_vsScratch, 0, 0);
				}

				m_vsChanges = 0;
			}

			if (0 < m_fsChanges)
			{
				if (NULL != m_currentProgram->m_fsh->m_buffer)
				{
					m_deviceCtx->UpdateSubresource(m_currentProgram->m_fsh->m_buffer, 0, 0, m_fsScratch, 0, 0);
				}

				m_fsChanges = 0;
			}
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true, bool _needPresent = true)
		{
			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx
			&&  m_rtMsaa)
			{
				FrameBufferD3D11& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();
			}

			if (!isValid(_fbh) )
			{
				m_currentColor        = m_backBufferColor;
				m_currentDepthStencil = m_backBufferDepthStencil;

				m_deviceCtx->OMSetRenderTargetsAndUnorderedAccessViews(
					  1
					, &m_currentColor
					, m_currentDepthStencil
					, 1
					, 0
					, NULL
					, NULL
					);
				m_needPresent |= _needPresent;
			}
			else
			{
				invalidateTextureStage();

				FrameBufferD3D11& frameBuffer = m_frameBuffers[_fbh.idx];
				frameBuffer.set();
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void clear(const Clear& _clear, const float _palette[][4])
		{
			if (isValid(m_fbh) )
			{
				FrameBufferD3D11& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.clear(_clear, _palette);
			}
			else
			{
				if (NULL != m_currentColor
				&&  BGFX_CLEAR_COLOR & _clear.m_flags)
				{
					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						uint8_t index = _clear.m_index[0];
						if (UINT8_MAX != index)
						{
							m_deviceCtx->ClearRenderTargetView(m_currentColor, _palette[index]);
						}
					}
					else
					{
						float frgba[4] =
						{
							_clear.m_index[0]*1.0f/255.0f,
							_clear.m_index[1]*1.0f/255.0f,
							_clear.m_index[2]*1.0f/255.0f,
							_clear.m_index[3]*1.0f/255.0f,
						};
						m_deviceCtx->ClearRenderTargetView(m_currentColor, frgba);
					}
				}

				if (NULL != m_currentDepthStencil
				&& (BGFX_CLEAR_DEPTH|BGFX_CLEAR_STENCIL) & _clear.m_flags)
				{
					DWORD flags = 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH)   ? D3D11_CLEAR_DEPTH   : 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL) ? D3D11_CLEAR_STENCIL : 0;
					m_deviceCtx->ClearDepthStencilView(m_currentDepthStencil, flags, _clear.m_depth, _clear.m_stencil);
				}
			}
		}

		void setInputLayout(uint8_t _numStreams, const VertexLayout** _layouts, const ProgramD3D11& _program, uint16_t _numInstanceData)
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_numInstanceData);
			for (uint8_t stream = 0; stream < _numStreams; ++stream)
			{
				murmur.add(_layouts[stream]->m_hash);
			}
			uint64_t layoutHash = (uint64_t(_program.m_vsh->m_hash)<<32) | murmur.end();

			ID3D11InputLayout* inputLayout = m_inputLayoutCache.find(layoutHash);
			if (NULL == inputLayout)
			{
				D3D11_INPUT_ELEMENT_DESC vertexElements[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
				D3D11_INPUT_ELEMENT_DESC* elem = vertexElements;

				uint16_t attrMask[Attrib::Count];
				bx::memCopy(attrMask, _program.m_vsh->m_attrMask, sizeof(attrMask) );

				for (uint8_t stream = 0; stream < _numStreams; ++stream)
				{
					VertexLayout layout;
					bx::memCopy(&layout, _layouts[stream], sizeof(VertexLayout) );

					const bool last = stream == _numStreams-1;

					for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
					{
						uint16_t mask = attrMask[ii];
						uint16_t attr = (layout.m_attributes[ii] & mask);
						if (0          == attr
						||  UINT16_MAX == attr)
						{
							layout.m_attributes[ii] = last ? ~attr : UINT16_MAX;
						}
						else
						{
							attrMask[ii] = 0;
						}
					}

					elem = fillVertexLayout(stream, elem, layout);
				}

				uint32_t num = uint32_t(elem-vertexElements);

				const D3D11_INPUT_ELEMENT_DESC inst = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 };

				for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
				{
					uint32_t index = 7-ii; // TEXCOORD7 = i_data0, TEXCOORD6 = i_data1, etc.

					uint32_t jj;
					D3D11_INPUT_ELEMENT_DESC* curr = vertexElements;
					for (jj = 0; jj < num; ++jj)
					{
						curr = &vertexElements[jj];
						if (0 == bx::strCmp(curr->SemanticName, "TEXCOORD")
						&&  curr->SemanticIndex == index)
						{
							break;
						}
					}

					if (jj == num)
					{
						curr = elem;
						++elem;
					}

					bx::memCopy(curr, &inst, sizeof(D3D11_INPUT_ELEMENT_DESC) );
					curr->InputSlot = _numStreams;
					curr->SemanticIndex = index;
					curr->AlignedByteOffset = ii*16;
				}

				num = uint32_t(elem-vertexElements);
				DX_CHECK(m_device->CreateInputLayout(vertexElements
					, num
					, _program.m_vsh->m_code->data
					, _program.m_vsh->m_code->size
					, &inputLayout
					) );
				m_inputLayoutCache.add(layoutHash, inputLayout);
			}

			m_deviceCtx->IASetInputLayout(inputLayout);
		}

		void setInputLayout(const VertexLayout& _layout, const ProgramD3D11& _program, uint16_t _numInstanceData)
		{
			const VertexLayout* layouts[1] = { &_layout };
			setInputLayout(BX_COUNTOF(layouts), layouts, _program, _numInstanceData);
		}

		void setBlendState(uint64_t _state, uint32_t _rgba = 0)
		{
			_state &= BGFX_D3D11_BLEND_STATE_MASK;

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(!!(BGFX_STATE_BLEND_INDEPENDENT & _state)
				? _rgba
				: -1
				);
			const uint32_t hash = murmur.end();

			ID3D11BlendState* bs = m_blendStateCache.find(hash);
			if (NULL == bs)
			{
				D3D11_BLEND_DESC desc;
				desc.AlphaToCoverageEnable  = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);
				desc.IndependentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT       & _state);

				D3D11_RENDER_TARGET_BLEND_DESC* drt = &desc.RenderTarget[0];
				drt->BlendEnable = !!(BGFX_STATE_BLEND_MASK & _state);

				const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK         )>>BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend      ) & 0xf;
				const uint32_t dstRGB = (blend >>  4) & 0xf;
				const uint32_t srcA   = (blend >>  8) & 0xf;
				const uint32_t dstA   = (blend >> 12) & 0xf;

				const uint32_t equRGB = (equation     ) & 0x7;
				const uint32_t equA   = (equation >> 3) & 0x7;

				drt->SrcBlend       = s_blendFactor[srcRGB][0];
				drt->DestBlend      = s_blendFactor[dstRGB][0];
				drt->BlendOp        = s_blendEquation[equRGB];

				drt->SrcBlendAlpha  = s_blendFactor[srcA][1];
				drt->DestBlendAlpha = s_blendFactor[dstA][1];
				drt->BlendOpAlpha   = s_blendEquation[equA];

				uint8_t writeMask = 0;
				writeMask |= (_state&BGFX_STATE_WRITE_R) ? D3D11_COLOR_WRITE_ENABLE_RED   : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_G) ? D3D11_COLOR_WRITE_ENABLE_GREEN : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_B) ? D3D11_COLOR_WRITE_ENABLE_BLUE  : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_A) ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0;

				drt->RenderTargetWriteMask = writeMask;

				if (desc.IndependentBlendEnable)
				{
					for (uint32_t ii = 1, rgba = _rgba; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii, rgba >>= 11)
					{
						drt = &desc.RenderTarget[ii];
						drt->BlendEnable = 0 != (rgba & 0x7ff);

						const uint32_t src = (rgba     ) & 0xf;
						const uint32_t dst = (rgba >> 4) & 0xf;
						const uint32_t equ = (rgba >> 8) & 0x7;

						drt->SrcBlend       = s_blendFactor[src][0];
						drt->DestBlend      = s_blendFactor[dst][0];
						drt->BlendOp        = s_blendEquation[equ];

						drt->SrcBlendAlpha  = s_blendFactor[src][1];
						drt->DestBlendAlpha = s_blendFactor[dst][1];
						drt->BlendOpAlpha   = s_blendEquation[equ];

						drt->RenderTargetWriteMask = writeMask;
					}
				}
				else
				{
					for (uint32_t ii = 1; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii)
					{
						bx::memCopy(&desc.RenderTarget[ii], drt, sizeof(D3D11_RENDER_TARGET_BLEND_DESC) );
					}
				}

				DX_CHECK(m_device->CreateBlendState(&desc, &bs) );

				m_blendStateCache.add(hash, bs);
			}

			const uint64_t f0 = BGFX_STATE_BLEND_FACTOR;
			const uint64_t f1 = BGFX_STATE_BLEND_INV_FACTOR;
			const uint64_t f2 = BGFX_STATE_BLEND_FACTOR<<4;
			const uint64_t f3 = BGFX_STATE_BLEND_INV_FACTOR<<4;
			bool hasFactor = 0
				|| f0 == (_state & f0)
				|| f1 == (_state & f1)
				|| f2 == (_state & f2)
				|| f3 == (_state & f3)
				;

			float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			if (hasFactor)
			{
				blendFactor[0] = ( (_rgba>>24)     )/255.0f;
				blendFactor[1] = ( (_rgba>>16)&0xff)/255.0f;
				blendFactor[2] = ( (_rgba>> 8)&0xff)/255.0f;
				blendFactor[3] = ( (_rgba    )&0xff)/255.0f;
			}

			m_deviceCtx->OMSetBlendState(bs, blendFactor, 0xffffffff);
		}

		void setDepthStencilState(uint64_t _state, uint64_t _stencil = 0)
		{
			uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
			_state &= 0 == func ? 0 : BGFX_D3D11_DEPTH_STENCIL_MASK;

			uint32_t fstencil = unpackStencil(0, _stencil);
			uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
			_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, ~BGFX_STENCIL_FUNC_REF_MASK);

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			uint32_t hash = murmur.end();

			ID3D11DepthStencilState* dss = m_depthStencilStateCache.find(hash);
			if (NULL == dss)
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				bx::memSet(&desc, 0, sizeof(desc) );
				desc.DepthEnable    = 0 != func;
				desc.DepthWriteMask = !!(BGFX_STATE_WRITE_Z & _state) ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
				desc.DepthFunc      = s_cmpFunc[func];

				uint32_t bstencil     = unpackStencil(1, _stencil);
				uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				desc.StencilEnable    = 0 != _stencil;
				desc.StencilReadMask  = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
				desc.StencilWriteMask = 0xff;
				desc.FrontFace.StencilFailOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.FrontFace.StencilDepthFailOp = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.FrontFace.StencilPassOp      = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.FrontFace.StencilFunc        = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
				desc.BackFace.StencilFailOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
				desc.BackFace.StencilDepthFailOp  = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
				desc.BackFace.StencilPassOp       = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
				desc.BackFace.StencilFunc         = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];

				DX_CHECK(m_device->CreateDepthStencilState(&desc, &dss) );

				m_depthStencilStateCache.add(hash, dss);
			}

			m_deviceCtx->OMSetDepthStencilState(dss, ref);
		}

		void setDebugWireframe(bool _wireframe)
		{
			if (m_wireframe != _wireframe)
			{
				m_wireframe = _wireframe;
				m_rasterizerStateCache.invalidate();
			}
		}

		void setRasterizerState(uint64_t _state, bool _wireframe = false, bool _scissor = false)
		{
			_state &= 0
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_FRONT_CCW
				;
			_state |= _wireframe ? BGFX_STATE_PT_LINES : BGFX_STATE_NONE;
			_state |= _scissor   ? BGFX_STATE_RESERVED_MASK : 0;
			_state &= ~(m_deviceInterfaceVersion >= 3 ? 0 : BGFX_STATE_CONSERVATIVE_RASTER);

			ID3D11RasterizerState* rs = m_rasterizerStateCache.find(_state);
			if (NULL == rs)
			{
				uint32_t cull = (_state&BGFX_STATE_CULL_MASK)>>BGFX_STATE_CULL_SHIFT;

#if BX_PLATFORM_WINDOWS
				if (m_deviceInterfaceVersion >= 3)
				{
					D3D11_RASTERIZER_DESC2 desc;
					desc.FillMode = _wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
					desc.CullMode = s_cullMode[cull];
					desc.FrontCounterClockwise = !!(_state&BGFX_STATE_FRONT_CCW);
					desc.DepthBias             = 0;
					desc.DepthBiasClamp        = 0.0f;
					desc.SlopeScaledDepthBias  = 0.0f;
					desc.DepthClipEnable       = !m_depthClamp;
					desc.ScissorEnable         = _scissor;
					desc.MultisampleEnable     = !!(_state&BGFX_STATE_MSAA);
					desc.AntialiasedLineEnable = !!(_state&BGFX_STATE_LINEAA);
					desc.ForcedSampleCount     = 0;
					desc.ConservativeRaster    = !!(_state&BGFX_STATE_CONSERVATIVE_RASTER)
						? D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON
						: D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF
						;

					ID3D11Device3* device3 = reinterpret_cast<ID3D11Device3*>(m_device);
					DX_CHECK(device3->CreateRasterizerState2(&desc, reinterpret_cast<ID3D11RasterizerState2**>(&rs) ) );
				}
				else
#endif // BX_PLATFORM_WINDOWS
				{
					D3D11_RASTERIZER_DESC desc;
					desc.FillMode = _wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
					desc.CullMode = s_cullMode[cull];
					desc.FrontCounterClockwise = false;
					desc.DepthBias             = 0;
					desc.DepthBiasClamp        = 0.0f;
					desc.SlopeScaledDepthBias  = 0.0f;
					desc.DepthClipEnable       = !m_depthClamp;
					desc.ScissorEnable         = _scissor;
					desc.MultisampleEnable     = !!(_state&BGFX_STATE_MSAA);
					desc.AntialiasedLineEnable = !!(_state&BGFX_STATE_LINEAA);

					DX_CHECK(m_device->CreateRasterizerState(&desc, &rs) );
				}

				m_rasterizerStateCache.add(_state, rs);
			}

			m_deviceCtx->RSSetState(rs);
		}

		ID3D11SamplerState* getSamplerState(uint32_t _flags, const float _rgba[4])
		{
			const uint32_t index = (_flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
			_flags &= BGFX_SAMPLER_BITS_MASK;

			// Force both min+max anisotropic, can't be set individually.
			_flags |= 0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) )
					? BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC
					: 0
					;

			uint32_t hash;
			ID3D11SamplerState* sampler;
			if (!needBorderColor(_flags) )
			{
				bx::HashMurmur2A murmur;
				murmur.begin();
				murmur.add(_flags);
				murmur.add(-1);
				hash = murmur.end();
				_rgba = s_zero.m_zerof;

				sampler = m_samplerStateCache.find(hash);
			}
			else
			{
				bx::HashMurmur2A murmur;
				murmur.begin();
				murmur.add(_flags);
				murmur.add(index);
				hash = murmur.end();
				_rgba = NULL == _rgba ? s_zero.m_zerof : _rgba;

				sampler = m_samplerStateCache.find(hash);
				if (NULL != sampler)
				{
					D3D11_SAMPLER_DESC sd;
					sampler->GetDesc(&sd);
					if (0 != bx::memCmp(_rgba, sd.BorderColor, 16) )
					{
						// Sampler will be released when updated sampler
						// is added to cache.
						sampler = NULL;
					}
				}
			}

			if (NULL == sampler)
			{
				const uint32_t cmpFunc   = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
				const uint8_t  minFilter = s_textureFilter[0][(_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT];
				const uint8_t  magFilter = s_textureFilter[1][(_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT];
				const uint8_t  mipFilter = s_textureFilter[2][(_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT];
				const uint8_t  filter    = 0 == cmpFunc ? 0 : D3D11_COMPARISON_FILTERING_BIT;

				D3D11_SAMPLER_DESC sd;
				sd.Filter         = (D3D11_FILTER)(filter|minFilter|magFilter|mipFilter);
				sd.AddressU       = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
				sd.AddressV       = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
				sd.AddressW       = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
				sd.MipLODBias     = float(BGFX_CONFIG_MIP_LOD_BIAS);
				sd.MaxAnisotropy  = m_maxAnisotropy;
				sd.ComparisonFunc = 0 == cmpFunc ? D3D11_COMPARISON_NEVER : s_cmpFunc[cmpFunc];
				sd.BorderColor[0] = _rgba[0];
				sd.BorderColor[1] = _rgba[1];
				sd.BorderColor[2] = _rgba[2];
				sd.BorderColor[3] = _rgba[3];
				sd.MinLOD = 0;
				sd.MaxLOD = D3D11_FLOAT32_MAX;

				m_device->CreateSamplerState(&sd, &sampler);
				DX_CHECK_REFCOUNT(sampler, 1);

				m_samplerStateCache.add(hash, sampler);
			}

			return sampler;
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		void commitTextureStage()
		{
			const uint32_t maxTextureSamplers = g_caps.limits.maxTextureSamplers;

			// vertex texture fetch not supported on 9_1 through 9_3
			if (m_featureLevel > D3D_FEATURE_LEVEL_9_3)
			{
				m_deviceCtx->VSSetShaderResources(0, maxTextureSamplers, m_textureStage.m_srv);
				m_deviceCtx->VSSetSamplers(0, maxTextureSamplers, m_textureStage.m_sampler);
			}

			m_deviceCtx->PSSetShaderResources(0, maxTextureSamplers, m_textureStage.m_srv);
			m_deviceCtx->PSSetSamplers(0, maxTextureSamplers, m_textureStage.m_sampler);
		}

		void invalidateTextureStage()
		{
			m_textureStage.clear();
			commitTextureStage();
		}

		ID3D11UnorderedAccessView* getCachedUav(TextureHandle _handle, uint8_t _mip)
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_handle);
			murmur.add(_mip);
			murmur.add(1);
			uint32_t hash = murmur.end();

			IUnknown** ptr = m_srvUavLru.find(hash);
			ID3D11UnorderedAccessView* uav;
			if (NULL == ptr)
			{
				TextureD3D11& texture = m_textures[_handle.idx];

				D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
				desc.Format = texture.getSrvFormat();
				switch (texture.m_type)
				{
				case TextureD3D11::Texture2D:
					desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
					desc.Texture2D.MipSlice = _mip;
					break;

				case TextureD3D11::TextureCube:
					desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
					desc.Texture2DArray.ArraySize = 6;
					desc.Texture2DArray.FirstArraySlice = 0;
					desc.Texture2DArray.MipSlice = _mip;
					break;

				case TextureD3D11::Texture3D:
					desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
					desc.Texture3D.MipSlice    = _mip;
					desc.Texture3D.FirstWSlice = 0;
					desc.Texture3D.WSize       = UINT32_MAX;
					break;
				}

				DX_CHECK(m_device->CreateUnorderedAccessView(texture.m_ptr, &desc, &uav) );

				m_srvUavLru.add(hash, uav, _handle.idx);
			}
			else
			{
				uav = static_cast<ID3D11UnorderedAccessView*>(*ptr);
			}

			return uav;
		}

		ID3D11ShaderResourceView* getCachedSrv(TextureHandle _handle, uint8_t _mip, bool _compute = false, bool _stencil = false)
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_handle);
			murmur.add(_mip);
			murmur.add(0);
			murmur.add(_compute);
			murmur.add(_stencil);
			uint32_t hash = murmur.end();

			IUnknown** ptr = m_srvUavLru.find(hash);
			ID3D11ShaderResourceView* srv;
			if (NULL == ptr)
			{
				const TextureD3D11& texture = m_textures[_handle.idx];
				const uint32_t msaaQuality = bx::uint32_satsub( (texture.m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
				const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];
				const bool msaaSample = 1 < msaa.Count && 0 != (texture.m_flags&BGFX_TEXTURE_MSAA_SAMPLE);

				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				desc.Format = _stencil ? DXGI_FORMAT_X24_TYPELESS_G8_UINT : texture.getSrvFormat();
				switch (texture.m_type)
				{
				case TextureD3D11::Texture2D:
					if (1 < texture.m_numLayers)
					{
						desc.ViewDimension = msaaSample
							? D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY
							: D3D11_SRV_DIMENSION_TEXTURE2DARRAY
							;
						desc.Texture2DArray.MostDetailedMip = _mip;
						desc.Texture2DArray.MipLevels       = 1;
						desc.Texture2DArray.FirstArraySlice = 0;
						desc.Texture2DArray.ArraySize       = texture.m_numLayers;
					}
					else
					{
						desc.ViewDimension = msaaSample
							? D3D11_SRV_DIMENSION_TEXTURE2DMS
							: D3D11_SRV_DIMENSION_TEXTURE2D
							;
						desc.Texture2D.MostDetailedMip = _mip;
						desc.Texture2D.MipLevels       = 1;
					}
					break;

				case TextureD3D11::TextureCube:
					if (_compute)
					{
						desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
						desc.Texture2DArray.MostDetailedMip = _mip;
						desc.Texture2DArray.MipLevels       = 1;
						desc.Texture2DArray.FirstArraySlice = 0;
						desc.Texture2DArray.ArraySize       = 6;
					}
					else
					{
						desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
						desc.TextureCube.MostDetailedMip = _mip;
						desc.TextureCube.MipLevels       = 1;
					}
					break;

				case TextureD3D11::Texture3D:
					desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
					desc.Texture3D.MostDetailedMip = _mip;
					desc.Texture3D.MipLevels       = 1;
					break;
				}

				DX_CHECK(m_device->CreateShaderResourceView(texture.m_ptr, &desc, &srv) );

				m_srvUavLru.add(hash, srv, _handle.idx);
			}
			else
			{
				srv = static_cast<ID3D11ShaderResourceView*>(*ptr);
			}

			return srv;
		}

		void capturePostReset()
		{
			if (m_resolution.reset&BGFX_RESET_CAPTURE)
			{
				ID3D11Texture2D* backBuffer;
				DX_CHECK(m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBuffer) );

				D3D11_TEXTURE2D_DESC backBufferDesc;
				backBuffer->GetDesc(&backBufferDesc);

				D3D11_TEXTURE2D_DESC desc;
				bx::memCopy(&desc, &backBufferDesc, sizeof(desc) );
				desc.SampleDesc.Count   = 1;
				desc.SampleDesc.Quality = 0;
				desc.Usage = D3D11_USAGE_STAGING;
				desc.BindFlags = 0;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

				HRESULT hr = m_device->CreateTexture2D(&desc, NULL, &m_captureTexture);
				if (SUCCEEDED(hr) )
				{
					if (backBufferDesc.SampleDesc.Count != 1)
					{
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.CPUAccessFlags = 0;
						m_device->CreateTexture2D(&desc, NULL, &m_captureResolve);
					}

					g_callback->captureBegin(backBufferDesc.Width, backBufferDesc.Height, backBufferDesc.Width*4, TextureFormat::BGRA8, false);
				}

				DX_RELEASE(backBuffer, 0);
			}
		}

		void capturePreReset()
		{
			if (NULL != m_captureTexture)
			{
				g_callback->captureEnd();
			}

			DX_RELEASE(m_captureResolve, 0);
			DX_RELEASE(m_captureTexture, 0);
		}

		void capture()
		{
			if (NULL != m_captureTexture)
			{
				ID3D11Texture2D* backBuffer;
				DX_CHECK(m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBuffer) );

				if (NULL == m_captureResolve)
				{
					m_deviceCtx->CopyResource(m_captureTexture, backBuffer);
				}
				else
				{
					m_deviceCtx->ResolveSubresource(m_captureResolve, 0, backBuffer, 0, m_scd.format);
					m_deviceCtx->CopyResource(m_captureTexture, m_captureResolve);
				}

				D3D11_MAPPED_SUBRESOURCE mapped;
				DX_CHECK(m_deviceCtx->Map(m_captureTexture, 0, D3D11_MAP_READ, 0, &mapped) );

				bimg::imageSwizzleBgra8(
					  mapped.pData
					, mapped.RowPitch
					, m_scd.width
					, m_scd.height
					, mapped.pData
					, mapped.RowPitch
					);

				g_callback->captureFrame(mapped.pData, m_scd.height*mapped.RowPitch);

				m_deviceCtx->Unmap(m_captureTexture, 0);

				DX_RELEASE(backBuffer, 0);
			}
		}

		void commit(UniformBuffer& _uniformBuffer)
		{
			_uniformBuffer.reset();

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
		case UniformType::_uniform|kUniformFragmentBit: \
				{ \
					setShaderUniform(uint8_t(type), loc, data, num); \
				} \
				break;

				switch ( (uint32_t)type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3|kUniformFragmentBit: \
					 {
						 float* value = (float*)data;
						 for (uint32_t ii = 0, count = num/3; ii < count; ++ii,  loc += 3*16, value += 9)
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
							 setShaderUniform(uint8_t(type), loc, &mtx.un.val[0], 3);
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
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferD3D11& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = m_scd.width;
				height = m_scd.height;
			}

			if (0      == _rect.m_x
			&&  0      == _rect.m_y
			&&  width  == _rect.m_width
			&&  height == _rect.m_height)
			{
				clear(_clear, _palette);
			}
			else
			{
				ID3D11DeviceContext* deviceCtx = m_deviceCtx;

				uint64_t state = 0;
				state |= _clear.m_flags & BGFX_CLEAR_COLOR ? BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A         : 0;
				state |= _clear.m_flags & BGFX_CLEAR_DEPTH ? BGFX_STATE_DEPTH_TEST_ALWAYS|BGFX_STATE_WRITE_Z : 0;

				uint64_t stencil = 0;
				stencil |= _clear.m_flags & BGFX_CLEAR_STENCIL ? 0
					| BGFX_STENCIL_TEST_ALWAYS
					| BGFX_STENCIL_FUNC_REF(_clear.m_stencil)
					| BGFX_STENCIL_FUNC_RMASK(0xff)
					| BGFX_STENCIL_OP_FAIL_S_REPLACE
					| BGFX_STENCIL_OP_FAIL_Z_REPLACE
					| BGFX_STENCIL_OP_PASS_Z_REPLACE
					: 0
					;

				setBlendState(state);
				setDepthStencilState(state, stencil);
				setRasterizerState(state);

				uint32_t numMrt = 1;
				FrameBufferHandle fbh = m_fbh;
				if (isValid(fbh) )
				{
					const FrameBufferD3D11& fb = m_frameBuffers[fbh.idx];
					numMrt = bx::uint32_max(1, fb.m_num);
				}

				ProgramD3D11& program = m_program[_clearQuad.m_program[numMrt-1].idx];
				m_currentProgram = &program;

				const ShaderD3D11* vsh = program.m_vsh;
				deviceCtx->VSSetShader(vsh->m_vertexShader, NULL, 0);
				deviceCtx->VSSetConstantBuffers(0, 1, &vsh->m_buffer);
				float mrtClearDepth[4] = { _clear.m_depth };
				deviceCtx->UpdateSubresource(vsh->m_buffer, 0, 0, mrtClearDepth, 0, 0);

				if (NULL != m_currentColor)
				{
					const ShaderD3D11* fsh = program.m_fsh;
					deviceCtx->PSSetShader(fsh->m_pixelShader, NULL, 0);
					deviceCtx->PSSetConstantBuffers(0, 1, &fsh->m_buffer);

					float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						for (uint32_t ii = 0; ii < numMrt; ++ii)
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
							bx::memCopy(mrtClearColor[ii], _palette[index], 16);
						}
					}
					else
					{
						float rgba[4] =
						{
							_clear.m_index[0]*1.0f/255.0f,
							_clear.m_index[1]*1.0f/255.0f,
							_clear.m_index[2]*1.0f/255.0f,
							_clear.m_index[3]*1.0f/255.0f,
						};

						for (uint32_t ii = 0; ii < numMrt; ++ii)
						{
							bx::memCopy(mrtClearColor[ii], rgba, 16);
						}
					}

					deviceCtx->UpdateSubresource(fsh->m_buffer, 0, 0, mrtClearColor, 0, 0);
				}
				else
				{
					deviceCtx->PSSetShader(NULL, NULL, 0);
				}

				VertexBufferD3D11& vb = m_vertexBuffers[_clearQuad.m_vb.idx];
				const VertexLayout& layout = _clearQuad.m_layout;

				const uint32_t stride = layout.m_stride;
				const uint32_t offset = 0;

				deviceCtx->IASetVertexBuffers(0, 1, &vb.m_ptr, &stride, &offset);
				setInputLayout(layout, program, 0);

				deviceCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				deviceCtx->Draw(4, 0);
			}
		}

		void* m_d3d9Dll;
		void* m_d3d11Dll;
		void* m_renderDocDll;
		void* m_agsDll;

		Dxgi m_dxgi;
		AGSContext* m_ags;
		NvApi m_nvapi;

		D3D_FEATURE_LEVEL m_featureLevel;

		Dxgi::SwapChainI* m_swapChain;
		ID3D11Texture2D*  m_msaaRt;

		bool m_needPresent;
		bool m_lost;
		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		ID3D11Device*              m_device;
		ID3D11DeviceContext*       m_deviceCtx;
		ID3DUserDefinedAnnotation* m_annotation;
		ID3D11InfoQueue*           m_infoQueue;

		TimerQueryD3D11     m_gpuTimer;
		OcclusionQueryD3D11 m_occlusionQuery;

		uint32_t m_deviceInterfaceVersion;

		ID3D11RenderTargetView* m_backBufferColor;
		ID3D11DepthStencilView* m_backBufferDepthStencil;
		ID3D11RenderTargetView* m_currentColor;
		ID3D11DepthStencilView* m_currentDepthStencil;

		ID3D11Texture2D* m_captureTexture;
		ID3D11Texture2D* m_captureResolve;

		Resolution m_resolution;

		SwapChainDesc m_scd;
		DXGI_SWAP_EFFECT m_swapEffect;
		uint32_t m_swapBufferCount;
		uint32_t m_maxAnisotropy;
		bool m_depthClamp;
		bool m_wireframe;

		IndexBufferD3D11 m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferD3D11 m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderD3D11 m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramD3D11 m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureD3D11 m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferD3D11 m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		StateCacheT<ID3D11BlendState> m_blendStateCache;
		StateCacheT<ID3D11DepthStencilState> m_depthStencilStateCache;
		StateCacheT<ID3D11InputLayout> m_inputLayoutCache;
		StateCacheT<ID3D11RasterizerState> m_rasterizerStateCache;
		StateCacheT<ID3D11SamplerState> m_samplerStateCache;
		StateCacheLru<IUnknown*, 1024> m_srvUavLru;

		TextVideoMem m_textVideoMem;

		TextureStage m_textureStage;

		ProgramD3D11* m_currentProgram;

		uint8_t m_vsScratch[64<<10];
		uint8_t m_fsScratch[64<<10];
		uint32_t m_vsChanges;
		uint32_t m_fsChanges;

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;
		bool m_timerQuerySupport;
		bool m_directAccessSupport;
	};

	static RendererContextD3D11* s_renderD3D11;

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderD3D11 = BX_NEW(g_allocator, RendererContextD3D11);
		if (!s_renderD3D11->init(_init) )
		{
			BX_DELETE(g_allocator, s_renderD3D11);
			s_renderD3D11 = NULL;
		}
		return s_renderD3D11;
	}

	void rendererDestroy()
	{
		s_renderD3D11->shutdown();
		BX_DELETE(g_allocator, s_renderD3D11);
		s_renderD3D11 = NULL;
	}

	void stubMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		for (uint32_t ii = 0; ii < _numDrawIndirect; ++ii)
		{
			deviceCtx->DrawInstancedIndirect(_ptr, _offset);
			_offset += _stride;
		}
	}

	void stubMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		for (uint32_t ii = 0; ii < _numDrawIndirect; ++ii)
		{
			deviceCtx->DrawIndexedInstancedIndirect(_ptr, _offset);
			_offset += _stride;
		}
	}

	void amdAgsMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		agsDriverExtensions_MultiDrawInstancedIndirect(s_renderD3D11->m_ags, _numDrawIndirect, _ptr, _offset, _stride);
	}

	void amdAgsMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		agsDriverExtensions_MultiDrawIndexedInstancedIndirect(s_renderD3D11->m_ags, _numDrawIndirect, _ptr, _offset, _stride);
	}

	void nvapiMultiDrawInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		s_renderD3D11->m_nvapi.nvApiD3D11MultiDrawInstancedIndirect(s_renderD3D11->m_deviceCtx, _numDrawIndirect, _ptr, _offset, _stride);
	}

	void nvapiMultiDrawIndexedInstancedIndirect(uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride)
	{
		s_renderD3D11->m_nvapi.nvApiD3D11MultiDrawIndexedInstancedIndirect(s_renderD3D11->m_deviceCtx, _numDrawIndirect, _ptr, _offset, _stride);
	}

	int  WINAPI d3d11Annotation_BeginEvent(DWORD _color, LPCWSTR _name)
	{
		BX_UNUSED(_color);
		return s_renderD3D11->m_annotation->BeginEvent(_name);
	}

	int  WINAPI d3d11Annotation_EndEvent()
	{
		return s_renderD3D11->m_annotation->EndEvent();
	}

	void WINAPI d3d11Annotation_SetMarker(DWORD _color, LPCWSTR _name)
	{
		BX_UNUSED(_color);
		s_renderD3D11->m_annotation->SetMarker(_name);
	}

	struct UavFormat
	{
		DXGI_FORMAT format[3];
		uint32_t    stride;
	};

	static const UavFormat s_uavFormat[] =
	{	//  BGFX_BUFFER_COMPUTE_TYPE_INT,  BGFX_BUFFER_COMPUTE_TYPE_UINT,  BGFX_BUFFER_COMPUTE_TYPE_FLOAT
		{ { DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN            },  0 }, // ignored
		{ { DXGI_FORMAT_R8_SINT,           DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_UNKNOWN            },  1 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X1
		{ { DXGI_FORMAT_R8G8_SINT,         DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_UNKNOWN            },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X2
		{ { DXGI_FORMAT_R8G8B8A8_SINT,     DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_UNKNOWN            },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X4
		{ { DXGI_FORMAT_R16_SINT,          DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_FLOAT          },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X1
		{ { DXGI_FORMAT_R16G16_SINT,       DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_FLOAT       },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X2
		{ { DXGI_FORMAT_R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_FLOAT },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X4
		{ { DXGI_FORMAT_R32_SINT,          DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_FLOAT          },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X1
		{ { DXGI_FORMAT_R32G32_SINT,       DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_FLOAT       },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X2
		{ { DXGI_FORMAT_R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_FLOAT }, 16 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X4
	};

	void BufferD3D11::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
	{
		m_uav   = NULL;
		m_size  = _size;
		m_flags = _flags;

		const bool needUav = 0 != (_flags & (BGFX_BUFFER_COMPUTE_WRITE|BGFX_BUFFER_DRAW_INDIRECT) );
		const bool needSrv = 0 != (_flags & BGFX_BUFFER_COMPUTE_READ);
		const bool drawIndirect = 0 != (_flags & BGFX_BUFFER_DRAW_INDIRECT);
		m_dynamic = NULL == _data && !needUav;

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.BindFlags = 0
			| (_vertex ? D3D11_BIND_VERTEX_BUFFER    : D3D11_BIND_INDEX_BUFFER)
			| (needUav ? D3D11_BIND_UNORDERED_ACCESS : 0)
			| (needSrv ? D3D11_BIND_SHADER_RESOURCE  : 0)
			;
		desc.MiscFlags = 0
			| (drawIndirect ? D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0)
			;
		desc.StructureByteStride = 0;

		DXGI_FORMAT format;
		uint32_t    stride;

		if (drawIndirect)
		{
			format = DXGI_FORMAT_R32G32B32A32_UINT;
			stride = 16;
		}
		else
		{
			uint32_t uavFormat = (_flags & BGFX_BUFFER_COMPUTE_FORMAT_MASK) >> BGFX_BUFFER_COMPUTE_FORMAT_SHIFT;
			if (0 == uavFormat)
			{
				if (_vertex)
				{
					format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					stride = 16;
				}
				else
				{
					if (0 == (_flags & BGFX_BUFFER_INDEX32) )
					{
						format = DXGI_FORMAT_R16_UINT;
						stride = 2;
					}
					else
					{
						format = DXGI_FORMAT_R32_UINT;
						stride = 4;
					}
				}
			}
			else
			{
				const uint32_t uavType = bx::uint32_satsub( (_flags & BGFX_BUFFER_COMPUTE_TYPE_MASK  ) >> BGFX_BUFFER_COMPUTE_TYPE_SHIFT, 1);
				format = s_uavFormat[uavFormat].format[uavType];
				stride = s_uavFormat[uavFormat].stride;
			}
		}

		ID3D11Device* device = s_renderD3D11->m_device;

		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem = _data;
		srd.SysMemPitch = 0;
		srd.SysMemSlicePitch = 0;

		if (needUav)
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			desc.StructureByteStride = _stride;

			DX_CHECK(device->CreateBuffer(&desc
				, NULL == _data ? NULL : &srd
				, &m_ptr
				) );

			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = format;
			uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavd.Buffer.FirstElement = 0;
			uavd.Buffer.NumElements = m_size / stride;
			uavd.Buffer.Flags = 0;
			DX_CHECK(device->CreateUnorderedAccessView(m_ptr
				, &uavd
				, &m_uav
				) );
		}
		else if (m_dynamic)
		{
#if USE_D3D11_STAGING_BUFFER
			desc.Usage          = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;

			DX_CHECK(device->CreateBuffer(&desc
				, NULL
				, &m_ptr
				) );

			desc.BindFlags      = 0;
			desc.Usage          = D3D11_USAGE_STAGING;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			DX_CHECK(device->CreateBuffer(&desc
				, NULL
				, &m_staging
				) );
#else
			desc.Usage          = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			DX_CHECK(device->CreateBuffer(&desc
				, NULL
				, &m_ptr
				) );
#endif // USE_D3D11_STAGING_BUFFER
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;

			DX_CHECK(device->CreateBuffer(&desc
				, &srd
				, &m_ptr
				) );
		}

		if (needSrv)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			srvd.Format = format;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvd.Buffer.FirstElement = 0;
			srvd.Buffer.NumElements = m_size / stride;
			DX_CHECK(device->CreateShaderResourceView(m_ptr
				, &srvd
				, &m_srv
				) );
		}
	}

	void BufferD3D11::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		BX_ASSERT(m_dynamic, "Must be dynamic!");

#if USE_D3D11_STAGING_BUFFER
		BX_UNUSED(_discard);

		D3D11_MAPPED_SUBRESOURCE mapped;
		DX_CHECK(deviceCtx->Map(m_staging, 0, D3D11_MAP_WRITE, 0, &mapped) );
		bx::memCopy( (uint8_t*)mapped.pData + _offset, _data, _size);
		deviceCtx->Unmap(m_staging, 0);

		D3D11_BOX box;
		box.left   = _offset;
		box.top    = 0;
		box.front  = 0;
		box.right  = _offset + _size;
		box.bottom = 1;
		box.back   = 1;

		deviceCtx->CopySubresourceRegion(m_ptr
			, 0
			, _offset
			, 0
			, 0
			, m_staging
			, 0
			, &box
			);
#else
		if (_discard)
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			DX_CHECK(deviceCtx->Map(m_ptr, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped) );
			bx::memCopy( (uint8_t*)mapped.pData + _offset, _data, _size);
			deviceCtx->Unmap(m_ptr, 0);
		}
		else
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = _size;
			desc.Usage     = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.MiscFlags = 0;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA srd;
			srd.pSysMem     = _data;
			srd.SysMemPitch = 0;
			srd.SysMemSlicePitch = 0;

			D3D11_BOX srcBox;
			srcBox.left   = 0;
			srcBox.top    = 0;
			srcBox.front  = 0;
			srcBox.right  = _size;
			srcBox.bottom = 1;
			srcBox.back   = 1;

			ID3D11Device* device = s_renderD3D11->m_device;

			ID3D11Buffer* ptr;
			DX_CHECK(device->CreateBuffer(&desc, &srd, &ptr) );

			deviceCtx->CopySubresourceRegion(m_ptr
				, 0
				, _offset
				, 0
				, 0
				, ptr
				, 0
				, &srcBox
				);

			DX_RELEASE(ptr, 0);
		}
#endif // 0
	}

	void VertexBufferD3D11::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		m_layoutHandle = _layoutHandle;
		uint16_t stride = isValid(_layoutHandle)
			? s_renderD3D11->m_vertexLayouts[_layoutHandle.idx].m_stride
			: 0
			;

		BufferD3D11::create(_size, _data, _flags, stride, true);
	}

	static bool hasDepthOp(const void* _code, uint32_t _size)
	{
		bx::MemoryReader rd(_code, _size);

		bx::Error err;
		DxbcContext dxbc;
		read(&rd, dxbc, &err);

		struct FindDepthOp
		{
			FindDepthOp()
				: m_found(false)
			{
			}

			static bool find(uint32_t /*_offset*/, const DxbcInstruction& _instruction, void* _userData)
			{
				FindDepthOp& out = *reinterpret_cast<FindDepthOp*>(_userData);
				if (_instruction.opcode == DxbcOpcode::DISCARD
				|| (0 != _instruction.numOperands &&  DxbcOperandType::OutputDepth == _instruction.operand[0].type) )
				{
					out.m_found = true;
					return false;
				}

				return true;
			}

			bool m_found;

		} find;

		parse(dxbc.shader, FindDepthOp::find, &find);

		return find.m_found;
	}

	void ShaderD3D11::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		const bool fragment = isShaderType(magic, 'F');

		uint32_t hashIn;
		bx::read(&reader, hashIn);

		uint32_t hashOut;

		if (isShaderVerLess(magic, 6) )
		{
			hashOut = hashIn;
		}
		else
		{
			bx::read(&reader, hashOut);
		}

		uint16_t count;
		bx::read(&reader, count);

		m_numPredefined = 0;
		m_numUniforms = count;

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		const uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize);

				char name[256] = { '\0' };
				bx::read(&reader, &name, nameSize);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type);

				uint8_t num = 0;
				bx::read(&reader, num);

				uint16_t regIndex = 0;
				bx::read(&reader, regIndex);

				uint16_t regCount = 0;
				bx::read(&reader, regCount);

				if (!isShaderVerLess(magic, 8) )
				{
					uint16_t texInfo = 0;
					bx::read(&reader, texInfo);
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
					const UniformRegInfo* info = s_renderD3D11->m_uniformReg.find(name);
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
		bx::read(&reader, shaderSize);

		const void* code = reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		if (isShaderType(magic, 'F') )
		{
			m_hasDepthOp = hasDepthOp(code, shaderSize);
			DX_CHECK(s_renderD3D11->m_device->CreatePixelShader(code, shaderSize, NULL, &m_pixelShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create fragment shader.");
		}
		else if (isShaderType(magic, 'V') )
		{
			m_hash = bx::hash<bx::HashMurmur2A>(code, shaderSize);
			m_code = copy(code, shaderSize);

			DX_CHECK(s_renderD3D11->m_device->CreateVertexShader(code, shaderSize, NULL, &m_vertexShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create vertex shader.");
		}
		else if (isShaderType(magic, 'C') )
		{
			DX_CHECK(s_renderD3D11->m_device->CreateComputeShader(code, shaderSize, NULL, &m_computeShader) );
			BGFX_FATAL(NULL != m_ptr, bgfx::Fatal::InvalidShader, "Failed to create compute shader.");
		}

		uint8_t numAttrs = 0;
		bx::read(&reader, numAttrs);

		bx::memSet(m_attrMask, 0, sizeof(m_attrMask) );

		for (uint32_t ii = 0; ii < numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id);

			Attrib::Enum attr = idToAttrib(id);

			if (Attrib::Count != attr)
			{
				m_attrMask[attr] = UINT16_MAX;
			}
		}

		uint16_t size;
		bx::read(&reader, size);

		if (0 < size)
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = (size + 0xf) & ~0xf;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			DX_CHECK(s_renderD3D11->m_device->CreateBuffer(&desc, NULL, &m_buffer) );

			BX_TRACE("\tCB size: %d", desc.ByteWidth);
		}
	}

	void* DirectAccessResourceD3D11::createTexture2D(const D3D11_TEXTURE2D_DESC* _gpuDesc, const D3D11_SUBRESOURCE_DATA* _srd, ID3D11Texture2D** _gpuTexture2d)
	{
		ID3D11Device* device = s_renderD3D11->m_device;
		DX_CHECK(setIntelDirectAccessResource(device) );
		DX_CHECK(device->CreateTexture2D(_gpuDesc, _srd, _gpuTexture2d) );

		D3D11_TEXTURE2D_DESC cpuDesc;
		bx::memCopy(&cpuDesc, _gpuDesc, sizeof(cpuDesc) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		DX_CHECK(setIntelDirectAccessResource(s_renderD3D11->m_device) );
		DX_CHECK(device->CreateTexture2D(&cpuDesc, NULL, &m_texture2d) );

		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		deviceCtx->CopyResource(m_texture2d, *_gpuTexture2d);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceCtx->Map(m_texture2d, 0, D3D11_MAP_WRITE, 0, &mappedResource);
		m_descriptor = reinterpret_cast<IntelDirectAccessResourceDescriptor*>(mappedResource.pData);

		return m_descriptor->ptr;
	}

	void* DirectAccessResourceD3D11::createTexture3D(const D3D11_TEXTURE3D_DESC* _gpuDesc, const D3D11_SUBRESOURCE_DATA* _srd, ID3D11Texture3D** _gpuTexture3d)
	{
		ID3D11Device* device = s_renderD3D11->m_device;
		DX_CHECK(setIntelDirectAccessResource(device) );
		DX_CHECK(device->CreateTexture3D(_gpuDesc, _srd, _gpuTexture3d) );

		D3D11_TEXTURE3D_DESC cpuDesc;
		bx::memCopy(&cpuDesc, _gpuDesc, sizeof(cpuDesc) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		DX_CHECK(setIntelDirectAccessResource(s_renderD3D11->m_device) );
		DX_CHECK(device->CreateTexture3D(&cpuDesc, NULL, &m_texture3d) );

		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		deviceCtx->CopyResource(m_texture3d, *_gpuTexture3d);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceCtx->Map(m_texture3d, 0, D3D11_MAP_WRITE, 0, &mappedResource);
		m_descriptor = reinterpret_cast<IntelDirectAccessResourceDescriptor*>(mappedResource.pData);

		return m_descriptor->ptr;
	}

	void DirectAccessResourceD3D11::destroy()
	{
		if (NULL != m_descriptor)
		{
			s_renderD3D11->m_deviceCtx->Unmap(m_ptr, 0);
			m_descriptor = NULL;
			DX_RELEASE(m_ptr, 0);
		}
	}

	void* TextureD3D11::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		void* directAccessPtr = NULL;

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

			m_flags     = _flags;
			m_width     = ti.width;
			m_height    = ti.height;
			m_depth     = ti.depth;
			m_numLayers = ti.numLayers;

			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			if (imageContainer.m_cubeMap)
			{
				m_type  = TextureCube;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = Texture3D;
			}
			else
			{
				m_type = Texture2D;
			}

			m_numMips = ti.numMips;

			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const uint32_t numSrd   = numSides * ti.numMips;
			D3D11_SUBRESOURCE_DATA* srd = (D3D11_SUBRESOURCE_DATA*)alloca(numSrd*sizeof(D3D11_SUBRESOURCE_DATA) );

			uint32_t kk = 0;

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool swizzle    = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);

			BX_TRACE("Texture %3d: %s (requested: %s), layers %d, %dx%d%s%s%s."
				, getHandle()
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.numLayers
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, 0 != (m_flags&BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);

			for (uint16_t side = 0; side < numSides; ++side)
			{
				for (uint8_t lod = 0, num = ti.numMips; lod < num; ++lod)
				{
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						srd[kk].pSysMem = mip.m_data;

						if (convert)
						{
							uint32_t srcpitch = mip.m_width*bpp/8;
							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, srcpitch*mip.m_height);
							bimg::imageDecodeToBgra8(g_allocator, temp, mip.m_data, mip.m_width, mip.m_height, srcpitch, mip.m_format);

							srd[kk].pSysMem = temp;
							srd[kk].SysMemPitch = srcpitch;
						}
						else if (compressed)
						{
							srd[kk].SysMemPitch      = (mip.m_width /blockInfo.blockWidth )*mip.m_blockSize;
							srd[kk].SysMemSlicePitch = (mip.m_height/blockInfo.blockHeight)*srd[kk].SysMemPitch;
						}
						else
						{
							srd[kk].SysMemPitch = mip.m_width*mip.m_bpp/8;
						}

						srd[kk].SysMemSlicePitch = mip.m_height*srd[kk].SysMemPitch;
						++kk;
					}
				}
			}

			const bool writeOnly    = 0 != (m_flags&(BGFX_TEXTURE_RT_WRITE_ONLY|BGFX_TEXTURE_READ_BACK) );
			const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb         = 0 != (m_flags&BGFX_TEXTURE_SRGB);
			const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);
			const bool readBack     = 0 != (m_flags&BGFX_TEXTURE_READ_BACK);
			const uint32_t msaaQuality = bx::uint32_satsub( (m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];
			const bool msaaSample  = true
				&& 1 < msaa.Count
				&& 0 != (m_flags&BGFX_TEXTURE_MSAA_SAMPLE)
				&& !writeOnly
				;
			const bool needResolve = true
				&& 1 < msaa.Count
				&& 0 == (m_flags&BGFX_TEXTURE_MSAA_SAMPLE)
				&& !writeOnly
				;

			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			bx::memSet(&srvd, 0, sizeof(srvd) );

			DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
			if (swizzle)
			{
				format      = srgb ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
				srvd.Format = format;
			}
			else if (srgb)
			{
				format      = s_textureFormat[m_textureFormat].m_fmtSrgb;
				srvd.Format = format;
				BX_WARN(format != DXGI_FORMAT_UNKNOWN, "sRGB not supported for texture format %d", m_textureFormat);
			}

			if (format == DXGI_FORMAT_UNKNOWN)
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format      = s_textureFormat[m_textureFormat].m_fmt;
				srvd.Format = getSrvFormat();
			}

			const bool directAccess = s_renderD3D11->m_directAccessSupport
				&& !renderTarget
				&& !readBack
				&& !blit
				&& !writeOnly
				;

			switch (m_type)
			{
			case Texture2D:
			case TextureCube:
				{
					D3D11_TEXTURE2D_DESC desc = {};
					desc.Width      = ti.width;
					desc.Height     = ti.height;
					desc.MipLevels  = ti.numMips;
					desc.ArraySize  = numSides;
					desc.Format     = format;
					desc.SampleDesc = msaa;
					desc.Usage      = kk == 0 || blit ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags  = writeOnly ? 0 : D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags      = 0;

					if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) ) )
					{
						desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}
					else if (renderTarget)
					{
						desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.MiscFlags |= 0
							| (1 < ti.numMips ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0)
							;
					}

					if (computeWrite)
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if (readBack)
					{
						desc.BindFlags      = 0;
						desc.Usage          = D3D11_USAGE_STAGING;
						desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					}

					if (imageContainer.m_cubeMap)
					{
						desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
						if (1 < ti.numLayers)
						{
							srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
							srvd.TextureCubeArray.MipLevels = ti.numMips;
							srvd.TextureCubeArray.NumCubes  = ti.numLayers;
						}
						else
						{
							srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
							srvd.TextureCube.MipLevels = ti.numMips;
						}
					}
					else
					{
						if (msaaSample)
						{
							if (1 < ti.numLayers)
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
								srvd.Texture2DMSArray.ArraySize = ti.numLayers;
							}
							else
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
							}
						}
						else
						{
							if (1 < ti.numLayers)
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
								srvd.Texture2DArray.MipLevels = ti.numMips;
								srvd.Texture2DArray.ArraySize = ti.numLayers;
							}
							else
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
								srvd.Texture2D.MipLevels = ti.numMips;
							}
						}
					}

					if (needResolve)
					{
						DX_CHECK(s_renderD3D11->m_device->CreateTexture2D(&desc, NULL, &m_rt2d) );
						desc.BindFlags &= ~(D3D11_BIND_RENDER_TARGET|D3D11_BIND_DEPTH_STENCIL);
						desc.SampleDesc = s_msaa[0];
					}

					if (directAccess)
					{
						directAccessPtr = m_dar.createTexture2D(&desc, kk == 0 ? NULL : srd, &m_texture2d);
					}
					else
					{
						DX_CHECK(s_renderD3D11->m_device->CreateTexture2D(&desc, kk == 0 ? NULL : srd, &m_texture2d) );
					}
				}
				break;

			case Texture3D:
				{
					D3D11_TEXTURE3D_DESC desc = {};
					desc.Width     = ti.width;
					desc.Height    = ti.height;
					desc.Depth     = ti.depth;
					desc.MipLevels = ti.numMips;
					desc.Format    = format;
					desc.Usage     = kk == 0 || blit ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags      = 0;

					if (renderTarget)
					{
						desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.MiscFlags |= 0
							| (1 < ti.numMips ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0)
							;
					}

					if (computeWrite)
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if (readBack)
					{
						desc.BindFlags = 0;
						desc.Usage = D3D11_USAGE_STAGING;
						desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					}

					srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
					srvd.Texture3D.MipLevels = ti.numMips;

					if (directAccess)
					{
						directAccessPtr = m_dar.createTexture3D(&desc, kk == 0 ? NULL : srd, &m_texture3d);
					}
					else
					{
						DX_CHECK(s_renderD3D11->m_device->CreateTexture3D(&desc, kk == 0 ? NULL : srd, &m_texture3d) );
					}
				}
				break;
			}

			if (!writeOnly)
			{
				DX_CHECK(s_renderD3D11->m_device->CreateShaderResourceView(m_ptr, &srvd, &m_srv) );
			}

			if (computeWrite)
			{
				DX_CHECK(s_renderD3D11->m_device->CreateUnorderedAccessView(m_ptr, NULL, &m_uav) );
			}

			if (convert
			&&  0 != kk)
			{
				kk = 0;
				for (uint16_t side = 0; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = ti.numMips; lod < num; ++lod)
					{
						BX_FREE(g_allocator, const_cast<void*>(srd[kk].pSysMem) );
						++kk;
					}
				}
			}
		}

		return directAccessPtr;
	}

	void TextureD3D11::destroy()
	{
		m_dar.destroy();

		s_renderD3D11->m_srvUavLru.invalidateWithParent(getHandle().idx);
		DX_RELEASE(m_rt, 0);
		DX_RELEASE(m_srv, 0);
		DX_RELEASE(m_uav, 0);
		if (0 == (m_flags & BGFX_SAMPLER_INTERNAL_SHARED) )
		{
			DX_RELEASE(m_ptr, 0);
		}
	}

	void TextureD3D11::overrideInternal(uintptr_t _ptr)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		const bool readable = (m_srv != NULL);
		if (readable) {
			m_srv->GetDesc(&srvDesc);
		}

		destroy();
		m_flags |= BGFX_SAMPLER_INTERNAL_SHARED;
		m_ptr = (ID3D11Resource*)_ptr;

		if (readable) {
			s_renderD3D11->m_device->CreateShaderResourceView(m_ptr, &srvDesc, &m_srv);
		}
	}

	void TextureD3D11::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		D3D11_BOX box;
		box.left   = _rect.m_x;
		box.top    = _rect.m_y;
		box.right  = box.left + _rect.m_width;
		box.bottom = box.top  + _rect.m_height;

		uint32_t layer = 0;

		if (TextureD3D11::Texture3D == m_type)
		{
			box.front = _z;
			box.back  = box.front + _depth;
		}
		else
		{
			layer = _z * (TextureD3D11::TextureCube == m_type ? 6 : 1);
			box.front = 0;
			box.back  = 1;
		}

		const uint32_t subres = _mip + ( (layer + _side) * m_numMips);
		const bool     depth  = bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t bpp    = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		uint32_t rectpitch  = _rect.m_width*bpp/8;
		if (bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat)))
		{
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat));
			rectpitch = (_rect.m_width / blockInfo.blockWidth)*blockInfo.blockSize;
		}
		const uint32_t srcpitch   = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t slicepitch = rectpitch*_rect.m_height;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, slicepitch);
			bimg::imageDecodeToBgra8(g_allocator, temp, data, _rect.m_width, _rect.m_height, srcpitch, bimg::TextureFormat::Enum(m_requestedFormat) );
			data = temp;
		}

		deviceCtx->UpdateSubresource(
			  m_ptr
			, subres
			, depth ? NULL : &box
			, data
			, srcpitch
			, TextureD3D11::Texture3D == m_type ? slicepitch : 0
			);

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureD3D11::commit(uint8_t _stage, uint32_t _flags, const float _palette[][4])
	{
		TextureStage& ts = s_renderD3D11->m_textureStage;

		if (0 != (_flags & BGFX_SAMPLER_SAMPLE_STENCIL) )
		{
			ts.m_srv[_stage] = s_renderD3D11->getCachedSrv(
				  TextureHandle{ uint16_t(this - s_renderD3D11->m_textures) }
				, 0
				, false
				, true
				);
		}
		else
		{
			ts.m_srv[_stage] = m_srv;
		}

		const uint32_t flags = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags)
			? _flags
			: uint32_t(m_flags)
			;
		uint32_t index = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
		ts.m_sampler[_stage] = s_renderD3D11->getSamplerState(flags, _palette[index]);
	}

	void TextureD3D11::resolve(uint8_t _resolve) const
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		const bool needResolve = NULL != m_rt;
		if (needResolve)
		{
			deviceCtx->ResolveSubresource(m_texture2d, 0, m_rt, 0, s_textureFormat[m_textureFormat].m_fmt);
		}

		const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
		if (renderTarget
		&&  1 < m_numMips
		&&  0 != (_resolve & BGFX_RESOLVE_AUTO_GEN_MIPS) )
		{
			deviceCtx->GenerateMips(m_srv);
		}
	}

	TextureHandle TextureD3D11::getHandle() const
	{
		TextureHandle handle = { (uint16_t)(this - s_renderD3D11->m_textures) };
		return handle;
	}

	DXGI_FORMAT TextureD3D11::getSrvFormat() const
	{
		if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) ) )
		{
			return s_textureFormat[m_textureFormat].m_fmtSrv;
		}

		return 0 != (m_flags&BGFX_TEXTURE_SRGB)
			? s_textureFormat[m_textureFormat].m_fmtSrgb
			: s_textureFormat[m_textureFormat].m_fmt
			;
	}

	void FrameBufferD3D11::create(uint8_t _num, const Attachment* _attachment)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_rtv); ++ii)
		{
			m_rtv[ii] = NULL;
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_uav); ++ii)
		{
			m_uav[ii] = NULL;
		}

		m_dsv       = NULL;
		m_swapChain = NULL;

		m_denseIdx = UINT16_MAX;
		m_numTh    = _num;
		m_needPresent = false;
		bx::memCopy(m_attachment, _attachment, _num*sizeof(Attachment) );

		postReset();
	}

	void FrameBufferD3D11::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		SwapChainDesc scd;
		bx::memCopy(&scd, &s_renderD3D11->m_scd, sizeof(SwapChainDesc) );
		scd.format     = TextureFormat::Count == _format ? scd.format : s_textureFormat[_format].m_fmt;
		scd.width      = _width;
		scd.height     = _height;
		scd.nwh        = _nwh;
		scd.ndt        = NULL;
		scd.sampleDesc = s_msaa[0];

		ID3D11Device* device = s_renderD3D11->m_device;

		HRESULT hr = s_renderD3D11->m_dxgi.createSwapChain(device
			, scd
			, &m_swapChain
			);
		BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Failed to create swap chain.");

#if BX_PLATFORM_WINDOWS
		DX_CHECK(s_renderD3D11->m_dxgi.m_factory->MakeWindowAssociation(
			  (HWND)_nwh
			, 0
			| DXGI_MWA_NO_WINDOW_CHANGES
			| DXGI_MWA_NO_ALT_ENTER
			) );
#endif // BX_PLATFORM_WINDOWS

		ID3D11Resource* ptr;
		DX_CHECK(m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&ptr) );
		DX_CHECK(device->CreateRenderTargetView(ptr, NULL, &m_rtv[0]) );
		DX_RELEASE(ptr, 0);

		DXGI_FORMAT fmtDsv = bimg::isDepth(bimg::TextureFormat::Enum(_depthFormat) )
			? s_textureFormat[_depthFormat].m_fmtDsv
			: DXGI_FORMAT_D24_UNORM_S8_UINT
			;
		D3D11_TEXTURE2D_DESC dsd;
		dsd.Width  = scd.width;
		dsd.Height = scd.height;
		dsd.MipLevels  = 1;
		dsd.ArraySize  = 1;
		dsd.Format     = fmtDsv;
		dsd.SampleDesc = scd.sampleDesc;
		dsd.Usage      = D3D11_USAGE_DEFAULT;
		dsd.BindFlags  = D3D11_BIND_DEPTH_STENCIL;
		dsd.CPUAccessFlags = 0;
		dsd.MiscFlags      = 0;

		ID3D11Texture2D* depthStencil;
		DX_CHECK(device->CreateTexture2D(&dsd, NULL, &depthStencil) );
		DX_CHECK(device->CreateDepthStencilView(depthStencil, NULL, &m_dsv) );
		DX_RELEASE(depthStencil, 0);

		m_srv[0]   = NULL;
		m_nwh      = _nwh;
		m_denseIdx = _denseIdx;
		m_num      = 1;
	}

	uint16_t FrameBufferD3D11::destroy()
	{
		preReset(true);

		DX_RELEASE(m_swapChain, 0);

		m_num   = 0;
		m_nwh   = NULL;
		m_numTh = 0;
		m_needPresent = false;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void FrameBufferD3D11::preReset(bool _force)
	{
		if (0 < m_numTh
		||  _force)
		{
			for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
			{
				DX_RELEASE(m_srv[ii], 0);
				DX_RELEASE(m_rtv[ii], 0);
			}

			DX_RELEASE(m_dsv, 0);
		}
	}

	void FrameBufferD3D11::postReset()
	{
		m_width  = 0;
		m_height = 0;

		if (0 < m_numTh)
		{
			m_num    = 0;
			m_numUav = 0;

			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					const TextureD3D11& texture = s_renderD3D11->m_textures[at.handle.idx];

					if (0 == m_width)
					{
						switch (texture.m_type)
						{
						case TextureD3D11::Texture2D:
						case TextureD3D11::TextureCube:
							{
								D3D11_TEXTURE2D_DESC desc;
								texture.m_texture2d->GetDesc(&desc);
								m_width  = desc.Width;
								m_height = desc.Height;
							}
							break;

						case TextureD3D11::Texture3D:
							{
								D3D11_TEXTURE3D_DESC desc;
								texture.m_texture3d->GetDesc(&desc);
								m_width  = desc.Width;
								m_height = desc.Height;
							}
							break;
						}
					}

					const uint32_t msaaQuality = bx::uint32_satsub( (texture.m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
					const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

					if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
					{
						BX_ASSERT(NULL == m_dsv, "Frame buffer already has depth-stencil attached.");

						D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
						dsvDesc.Format = s_textureFormat[texture.m_textureFormat].m_fmtDsv;
						dsvDesc.Flags = 0;

						switch (texture.m_type)
						{
						default:
						case TextureD3D11::Texture2D:
							{
								if (1 < msaa.Count)
								{
									if (1 < texture.m_numLayers)
									{
										dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
										dsvDesc.Texture2DMSArray.FirstArraySlice = at.layer;
										dsvDesc.Texture2DMSArray.ArraySize       = 1;
									}
									else
									{
										dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
									}
								}
								else
								{
									if (1 < texture.m_numLayers)
									{
										dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
										dsvDesc.Texture2DArray.FirstArraySlice = at.layer;
										dsvDesc.Texture2DArray.ArraySize       = 1;
										dsvDesc.Texture2DArray.MipSlice        = at.mip;
									}
									else
									{
										dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
										dsvDesc.Texture2D.MipSlice = at.mip;
									}
								}
								DX_CHECK(s_renderD3D11->m_device->CreateDepthStencilView(
									  NULL == texture.m_rt ? texture.m_ptr : texture.m_rt
									, &dsvDesc
									, &m_dsv
									) );
							}
							break;

						case TextureD3D11::TextureCube:
							{
								if (1 < msaa.Count)
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
									dsvDesc.Texture2DMSArray.ArraySize       = 1;
									dsvDesc.Texture2DMSArray.FirstArraySlice = at.layer;
								}
								else
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
									dsvDesc.Texture2DArray.ArraySize       = 1;
									dsvDesc.Texture2DArray.FirstArraySlice = at.layer;
									dsvDesc.Texture2DArray.MipSlice        = at.mip;
								}
								DX_CHECK(s_renderD3D11->m_device->CreateDepthStencilView(texture.m_ptr, &dsvDesc, &m_dsv) );
							}
							break;
						}
					}
					else if (Access::Write == at.access)
					{
						D3D11_RENDER_TARGET_VIEW_DESC desc;
						desc.Format = texture.getSrvFormat();
						switch (texture.m_type)
						{
						default:
						case TextureD3D11::Texture2D:
							if (1 < msaa.Count)
							{
								if (1 < texture.m_numLayers)
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
									desc.Texture2DMSArray.FirstArraySlice = at.layer;
									desc.Texture2DMSArray.ArraySize       = 1;
								}
								else
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
								}
							}
							else
							{
								if (1 < texture.m_numLayers)
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
									desc.Texture2DArray.FirstArraySlice = at.layer;
									desc.Texture2DArray.ArraySize       = 1;
									desc.Texture2DArray.MipSlice        = at.mip;
								}
								else
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
									desc.Texture2D.MipSlice = at.mip;
								}
							}

							DX_CHECK(s_renderD3D11->m_device->CreateRenderTargetView(
								  NULL == texture.m_rt ? texture.m_ptr : texture.m_rt
								, &desc
								, &m_rtv[m_num]
								) );
							break;

						case TextureD3D11::TextureCube:
							if (1 < msaa.Count)
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
								desc.Texture2DMSArray.ArraySize       = 1;
								desc.Texture2DMSArray.FirstArraySlice = at.layer;
							}
							else
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
								desc.Texture2DArray.ArraySize       = 1;
								desc.Texture2DArray.FirstArraySlice = at.layer;
								desc.Texture2DArray.MipSlice        = at.mip;
							}

							DX_CHECK(s_renderD3D11->m_device->CreateRenderTargetView(texture.m_ptr, &desc, &m_rtv[m_num]) );
							break;

						case TextureD3D11::Texture3D:
							desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
							desc.Texture3D.MipSlice    = at.mip;
							desc.Texture3D.WSize       = 1;
							desc.Texture3D.FirstWSlice = at.layer;

							DX_CHECK(s_renderD3D11->m_device->CreateRenderTargetView(texture.m_ptr, &desc, &m_rtv[m_num]) );
							break;
						}

						D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
						texture.m_srv->GetDesc(&srvDesc);
						DX_CHECK(s_renderD3D11->m_device->CreateShaderResourceView(texture.m_ptr, &srvDesc, &m_srv[m_num]));
						m_num++;
					}
					else
					{
						m_uav[m_numUav++] = texture.m_uav;
					}
				}
			}
		}
	}

	void FrameBufferD3D11::resolve()
	{
		if (0 < m_numTh)
		{
			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					const TextureD3D11& texture = s_renderD3D11->m_textures[at.handle.idx];
					texture.resolve(at.resolve);
				}
			}
		}
	}

	void FrameBufferD3D11::clear(const Clear& _clear, const float _palette[][4])
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		if (BGFX_CLEAR_COLOR & _clear.m_flags)
		{
			if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
			{
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					uint8_t index = _clear.m_index[ii];
					if (NULL != m_rtv[ii]
					&&  UINT8_MAX != index)
					{
						deviceCtx->ClearRenderTargetView(m_rtv[ii], _palette[index]);
					}
				}
			}
			else
			{
				float frgba[4] =
				{
					_clear.m_index[0]*1.0f/255.0f,
					_clear.m_index[1]*1.0f/255.0f,
					_clear.m_index[2]*1.0f/255.0f,
					_clear.m_index[3]*1.0f/255.0f,
				};
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					if (NULL != m_rtv[ii])
					{
						deviceCtx->ClearRenderTargetView(m_rtv[ii], frgba);
					}
				}
			}
		}

		if (NULL != m_dsv
		&& (BGFX_CLEAR_DEPTH|BGFX_CLEAR_STENCIL) & _clear.m_flags)
		{
			DWORD flags = 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH) ? D3D11_CLEAR_DEPTH : 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL) ? D3D11_CLEAR_STENCIL : 0;
			deviceCtx->ClearDepthStencilView(m_dsv, flags, _clear.m_depth, _clear.m_stencil);
		}
	}

	void FrameBufferD3D11::set()
	{
		if (0 < m_numUav)
		{
			s_renderD3D11->m_deviceCtx->OMSetRenderTargetsAndUnorderedAccessViews(
				  m_num
				, m_rtv
				, m_dsv
				, 16
				, m_numUav
				, m_uav
				, NULL
				);
		}
		else
		{
			s_renderD3D11->m_deviceCtx->OMSetRenderTargets(m_num, m_rtv, m_dsv);
		}

		m_needPresent = UINT16_MAX != m_denseIdx;
		s_renderD3D11->m_currentColor        = m_rtv[0];
		s_renderD3D11->m_currentDepthStencil = m_dsv;
	}

	HRESULT FrameBufferD3D11::present(uint32_t _syncInterval)
	{
		if (m_needPresent)
		{
			HRESULT hr = m_swapChain->Present(_syncInterval, 0);
			hr = !isLost(hr) ? S_OK : hr;
			m_needPresent = false;
			return hr;
		}

		return S_OK;
	}

	void TimerQueryD3D11::postReset()
	{
		ID3D11Device* device = s_renderD3D11->m_device;

		D3D11_QUERY_DESC qd;
		qd.MiscFlags = 0;
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			query.m_ready = false;

			qd.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
			DX_CHECK(device->CreateQuery(&qd, &query.m_disjoint) );

			qd.Query = D3D11_QUERY_TIMESTAMP;
			DX_CHECK(device->CreateQuery(&qd, &query.m_begin) );
			DX_CHECK(device->CreateQuery(&qd, &query.m_end) );
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_result); ++ii)
		{
			Result& result = m_result[ii];
			result.reset();
		}

		m_control.reset();
	}

	void TimerQueryD3D11::preReset()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			DX_RELEASE(query.m_disjoint, 0);
			DX_RELEASE(query.m_begin, 0);
			DX_RELEASE(query.m_end, 0);
		}
	}

	uint32_t TimerQueryD3D11::begin(uint32_t _resultIdx)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

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

		deviceCtx->Begin(query.m_disjoint);
		deviceCtx->End(query.m_begin);

		m_control.commit(1);

		return idx;
	}

	void TimerQueryD3D11::end(uint32_t _idx)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		Query& query = m_query[_idx];
		query.m_ready = true;

		deviceCtx->End(query.m_end);
		deviceCtx->End(query.m_disjoint);

		while (update() )
		{
		}
	}

	bool TimerQueryD3D11::update()
	{
		if (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (!query.m_ready)
			{
				return false;
			}

			uint64_t timeEnd;
			ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
			HRESULT hr = deviceCtx->GetData(query.m_end, &timeEnd, sizeof(timeEnd), D3D11_ASYNC_GETDATA_DONOTFLUSH);
			if (S_OK == hr
			||  isLost(hr) )
			{
				m_control.consume(1);

				struct D3D11_QUERY_DATA_TIMESTAMP_DISJOINT
				{
					UINT64 Frequency;
					BOOL Disjoint;
				};

				D3D11_QUERY_DATA_TIMESTAMP_DISJOINT disjoint;
				DX_CHECK(deviceCtx->GetData(query.m_disjoint, &disjoint, sizeof(disjoint), 0) );

				uint64_t timeBegin;
				DX_CHECK(deviceCtx->GetData(query.m_begin, &timeBegin, sizeof(timeBegin), 0) );

				Result& result = m_result[query.m_resultIdx];
				--result.m_pending;

				result.m_frequency = disjoint.Frequency;
				result.m_begin     = timeBegin;
				result.m_end       = timeEnd;

				return true;
			}
		}

		return false;
	}

	void OcclusionQueryD3D11::postReset()
	{
		ID3D11Device* device = s_renderD3D11->m_device;

		D3D11_QUERY_DESC desc;
		desc.Query = D3D11_QUERY_OCCLUSION;
		desc.MiscFlags = 0;
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			DX_CHECK(device->CreateQuery(&desc, &query.m_ptr) );
		}
	}

	void OcclusionQueryD3D11::preReset()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_query); ++ii)
		{
			Query& query = m_query[ii];
			DX_RELEASE(query.m_ptr, 0);
		}
	}

	void OcclusionQueryD3D11::begin(Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		Query& query = m_query[m_control.m_current];
		deviceCtx->Begin(query.m_ptr);
		query.m_handle = _handle;
	}

	void OcclusionQueryD3D11::end()
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;
		Query& query = m_query[m_control.m_current];
		deviceCtx->End(query.m_ptr);
		m_control.commit(1);
	}

	void OcclusionQueryD3D11::resolve(Frame* _render, bool _wait)
	{
		ID3D11DeviceContext* deviceCtx = s_renderD3D11->m_deviceCtx;

		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (isValid(query.m_handle) )
			{
				uint64_t result = 0;
				HRESULT hr = deviceCtx->GetData(query.m_ptr, &result, sizeof(result), _wait ? 0 : D3D11_ASYNC_GETDATA_DONOTFLUSH);
				if (S_FALSE == hr)
				{
					break;
				}

				_render->m_occlusion[query.m_handle.idx] = int32_t(result);
			}

			m_control.consume(1);
		}
	}

	void OcclusionQueryD3D11::invalidate(OcclusionQueryHandle _handle)
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

	void RendererContextD3D11::submitBlit(BlitState& _bs, uint16_t _view)
	{
		ID3D11DeviceContext* deviceCtx = m_deviceCtx;

		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureD3D11& src = m_textures[blit.m_src.idx];
			const TextureD3D11& dst = m_textures[blit.m_dst.idx];

			uint32_t srcWidth  = bx::uint32_min(src.m_width,  blit.m_srcX + blit.m_width)  - blit.m_srcX;
			uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
			uint32_t srcDepth  = bx::uint32_min(src.m_depth,  blit.m_srcZ + blit.m_depth)  - blit.m_srcZ;
			uint32_t dstWidth  = bx::uint32_min(dst.m_width,  blit.m_dstX + blit.m_width)  - blit.m_dstX;
			uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
			uint32_t dstDepth  = bx::uint32_min(dst.m_depth,  blit.m_dstZ + blit.m_depth)  - blit.m_dstZ;
			uint32_t width     = bx::uint32_min(srcWidth,  dstWidth);
			uint32_t height    = bx::uint32_min(srcHeight, dstHeight);
			uint32_t depth     = bx::uint32_min(srcDepth,  dstDepth);

			if (TextureD3D11::Texture3D == src.m_type)
			{
				D3D11_BOX box;
				box.left   = blit.m_srcX;
				box.top    = blit.m_srcY;
				box.front  = blit.m_srcZ;
				box.right  = blit.m_srcX + width;
				box.bottom = blit.m_srcY + height;;
				box.back   = blit.m_srcZ + bx::uint32_imax(1, depth);

				deviceCtx->CopySubresourceRegion(dst.m_ptr
					, blit.m_dstMip
					, blit.m_dstX
					, blit.m_dstY
					, blit.m_dstZ
					, src.m_ptr
					, blit.m_srcMip
					, &box
					);
			}
			else
			{
				bool depthStencil = bimg::isDepth(bimg::TextureFormat::Enum(src.m_textureFormat) );
				BX_ASSERT(!depthStencil
					||  (width == src.m_width && height == src.m_height)
					, "When blitting depthstencil surface, source resolution must match destination."
					);

				D3D11_BOX box;
				box.left   = blit.m_srcX;
				box.top    = blit.m_srcY;
				box.front  = 0;
				box.right  = blit.m_srcX + width;
				box.bottom = blit.m_srcY + height;
				box.back   = 1;

				const uint32_t srcZ = blit.m_srcZ;
				const uint32_t dstZ = blit.m_dstZ;

				deviceCtx->CopySubresourceRegion(dst.m_ptr
					, dstZ*dst.m_numMips+blit.m_dstMip
					, blit.m_dstX
					, blit.m_dstY
					, 0
					, src.m_ptr
					, srcZ*src.m_numMips+blit.m_srcMip
					, depthStencil ? NULL : &box
					);
			}
		}
	}

	void RendererContextD3D11::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		if (m_lost
		||  updateResolution(_render->m_resolution) )
		{
			return;
		}

		if (_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		BGFX_D3D11_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorView);

		ID3D11DeviceContext* deviceCtx = m_deviceCtx;

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = UINT32_MAX;

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
		currentState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		static ViewState viewState;
		viewState.reset(_render);

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
		bool scissorEnabled = false;
		setDebugWireframe(wireframe);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		const uint64_t primType = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];
		deviceCtx->IASetPrimitiveTopology(prim.m_type);

		bool wasCompute = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;
		const uint32_t maxTextureSamplers = g_caps.limits.maxTextureSamplers;

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		Profiler<TimerQueryD3D11> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			, m_timerQuerySupport
			);

		m_occlusionQuery.resolve(_render);

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			// reset the framebuffer to be the backbuffer; depending on the swap effect,
			// if we don't do this we'll only see one frame of output and then nothing
			setFrameBuffer(BGFX_INVALID_HANDLE, true, false);

			viewState.m_rect = _render->m_view[0].m_rect;
			int32_t numItems = _render->m_numRenderItems;

			for (int32_t item = 0; item < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
					;

				const uint32_t itemIdx       = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged)
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_D3D11_PROFILER_END();
					setViewType(view, "  ");
					BGFX_D3D11_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						fbh = _render->m_view[view].m_fbh;
						setFrameBuffer(fbh);
					}

					viewState.m_rect = _render->m_view[view].m_rect;

					const Rect& scissorRect = _render->m_view[view].m_scissor;
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;

					D3D11_VIEWPORT vp;
					vp.TopLeftX = viewState.m_rect.m_x;
					vp.TopLeftY = viewState.m_rect.m_y;
					vp.Width    = viewState.m_rect.m_width;
					vp.Height   = viewState.m_rect.m_height;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					deviceCtx->RSSetViewports(1, &vp);
					Clear& clr = _render->m_view[view].m_clear;

					if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK) )
					{
						clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_colorPalette);
						prim = s_primInfo[Topology::Count]; // Force primitive type update after clear quad.
					}

					submitBlit(bs, view);
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						setViewType(view, "C");
						BGFX_D3D11_PROFILER_END();
						BGFX_D3D11_PROFILER_BEGIN(view, kColorCompute);

						deviceCtx->IASetVertexBuffers(0, 2, s_zero.m_buffer, s_zero.m_zero, s_zero.m_zero);
						deviceCtx->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);

						deviceCtx->VSSetShaderResources(0, maxTextureSamplers, s_zero.m_srv);
						deviceCtx->PSSetShaderResources(0, maxTextureSamplers, s_zero.m_srv);

						deviceCtx->VSSetSamplers(0, maxTextureSamplers, s_zero.m_sampler);
						deviceCtx->PSSetSamplers(0, maxTextureSamplers, s_zero.m_sampler);
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					bool constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
					rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

					if (key.m_program.idx != currentProgram.idx)
					{
						currentProgram = key.m_program;

						ProgramD3D11& program = m_program[currentProgram.idx];
						m_currentProgram = &program;

						deviceCtx->CSSetShader(program.m_vsh->m_computeShader, NULL, 0);
						deviceCtx->CSSetConstantBuffers(0, 1, &program.m_vsh->m_buffer);

						programChanged =
							constantsChanged = true;
					}

					if (isValid(currentProgram) )
					{
						ProgramD3D11& program = m_program[currentProgram.idx];

						if (constantsChanged)
						{
							UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
							if (NULL != vcb)
							{
								commit(*vcb);
							}
						}

						viewState.setPredefined<4>(this, view, program, _render, compute);

						if (constantsChanged
						||  program.m_numPredefined > 0)
						{
							commitShaderConstants();
						}
					}
					BX_UNUSED(programChanged);
					ID3D11UnorderedAccessView* uav[BGFX_MAX_COMPUTE_BINDINGS] = {};

					for (uint8_t stage = 0; stage < maxComputeBindings; ++stage)
					{
						const Binding& bind = renderBind.m_bind[stage];
						if (kInvalidHandle != bind.m_idx)
						{
							switch (bind.m_type)
							{
							case Binding::Image:
								{
									TextureD3D11& texture = m_textures[bind.m_idx];
									if (Access::Read != bind.m_access)
									{
										uav[stage] = 0 == bind.m_mip
											? texture.m_uav
											: s_renderD3D11->getCachedUav(texture.getHandle(), bind.m_mip)
											;
									}
									else
									{
										m_textureStage.m_srv[stage]     = s_renderD3D11->getCachedSrv(texture.getHandle(), bind.m_mip, true);
										m_textureStage.m_sampler[stage] = s_renderD3D11->getSamplerState(uint32_t(texture.m_flags), NULL);
									}
								}
								break;

							case Binding::Texture:
								{
									TextureD3D11& texture = m_textures[bind.m_idx];
									texture.commit(stage, bind.m_samplerFlags, _render->m_colorPalette);
								}
								break;

							case Binding::IndexBuffer:
							case Binding::VertexBuffer:
								{
									const BufferD3D11& buffer = Binding::IndexBuffer == bind.m_type
										? m_indexBuffers[bind.m_idx]
										: m_vertexBuffers[bind.m_idx]
										;
									if (Access::Read != bind.m_access)
									{
										uav[stage] = buffer.m_uav;
									}
									else
									{
										m_textureStage.m_srv[stage] = buffer.m_srv;
									}
								}
								break;
							}
						}
						else
						{
							m_textureStage.m_srv[stage]     = NULL;
							m_textureStage.m_sampler[stage] = NULL;
						}
					}

					if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
					{
						// Quiet validation: Resource being set to CS UnorderedAccessView slot 0 is still bound on input!
						deviceCtx->CSSetShaderResources(0, maxComputeBindings, s_zero.m_srv);
					}

					deviceCtx->CSSetUnorderedAccessViews(0, maxComputeBindings, uav, NULL);
					deviceCtx->CSSetShaderResources(0, maxTextureSamplers, m_textureStage.m_srv);
					deviceCtx->CSSetSamplers(0, maxTextureSamplers, m_textureStage.m_sampler);

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferD3D11& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];
						ID3D11Buffer* ptr = vb.m_ptr;

						uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: compute.m_numIndirect
							;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
							deviceCtx->DispatchIndirect(ptr, args);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						deviceCtx->Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);
					}

					continue;
				}

				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					setViewType(view, " ");
					BGFX_D3D11_PROFILER_END();
					BGFX_D3D11_PROFILER_BEGIN(view, kColorDraw);

					currentProgram   = BGFX_INVALID_HANDLE;
					m_currentProgram = NULL;

					invalidateCompute();
				}

				const RenderDraw& draw = renderItem.draw;

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
						if (resetState)
						{
							currentState.clear();
							currentState.m_scissor = !draw.m_scissor;
							currentBind.clear();
						}

						continue;
					}
				}

				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				changedFlags |= currentState.m_rgba != draw.m_rgba ? BGFX_D3D11_BLEND_STATE_MASK : 0;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				changedFlags |= 0 != changedStencil ? BGFX_D3D11_DEPTH_STENCIL_MASK : 0;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					wasCompute = false;

					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					currentBind.clear();

					setBlendState(newFlags);
					setDepthStencilState(newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT) );

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
				}

				if (prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
					deviceCtx->IASetPrimitiveTopology(prim.m_type);
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						scissorEnabled = viewHasScissor;
						if (viewHasScissor)
						{
							D3D11_RECT rc;
							rc.left   = viewScissorRect.m_x;
							rc.top    = viewScissorRect.m_y;
							rc.right  = viewScissorRect.m_x + viewScissorRect.m_width;
							rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
							deviceCtx->RSSetScissorRects(1, &rc);
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

						scissorEnabled = true;
						D3D11_RECT rc;
						rc.left   = scissorRect.m_x;
						rc.top    = scissorRect.m_y;
						rc.right  = scissorRect.m_x + scissorRect.m_width;
						rc.bottom = scissorRect.m_y + scissorRect.m_height;
						deviceCtx->RSSetScissorRects(1, &rc);
					}

					setRasterizerState(newFlags, wireframe, scissorEnabled);
				}

				if (BGFX_D3D11_DEPTH_STENCIL_MASK & changedFlags)
				{
					setDepthStencilState(newFlags, newStencil);
				}

				if (BGFX_D3D11_BLEND_STATE_MASK & changedFlags)
				{
					setBlendState(newFlags, draw.m_rgba);
					currentState.m_rgba = draw.m_rgba;
				}

				if ( (0
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_ALPHA_REF_MASK
					 | BGFX_STATE_PT_MASK
					 | BGFX_STATE_POINT_SIZE_MASK
					 | BGFX_STATE_MSAA
					 | BGFX_STATE_LINEAA
					 | BGFX_STATE_CONSERVATIVE_RASTER
					 ) & changedFlags)
				{
					if ( (0
						 | BGFX_STATE_CULL_MASK
						 | BGFX_STATE_MSAA
						 | BGFX_STATE_LINEAA
						 | BGFX_STATE_CONSERVATIVE_RASTER
						 ) & changedFlags)
					{
						setRasterizerState(newFlags, wireframe, scissorEnabled);
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
					}

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
						deviceCtx->IASetPrimitiveTopology(prim.m_type);
					}
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				if (key.m_program.idx != currentProgram.idx)
				{
					currentProgram = key.m_program;

					if (!isValid(currentProgram) )
					{
						m_currentProgram = NULL;

						deviceCtx->VSSetShader(NULL, NULL, 0);
						deviceCtx->PSSetShader(NULL, NULL, 0);
					}
					else
					{
						ProgramD3D11& program = m_program[currentProgram.idx];
						m_currentProgram = &program;

						const ShaderD3D11* vsh = program.m_vsh;
						deviceCtx->VSSetShader(vsh->m_vertexShader, NULL, 0);
						deviceCtx->VSSetConstantBuffers(0, 1, &vsh->m_buffer);

						const ShaderD3D11* fsh = program.m_fsh;
						if (NULL != fsh
						&& (NULL != m_currentColor || fsh->m_hasDepthOp) )
						{
							deviceCtx->PSSetShader(fsh->m_pixelShader, NULL, 0);
							deviceCtx->PSSetConstantBuffers(0, 1, &fsh->m_buffer);
						}
						else
						{
							deviceCtx->PSSetShader(NULL, NULL, 0);
						}
					}

					programChanged =
						constantsChanged = true;
				}

				if (isValid(currentProgram) )
				{
					ProgramD3D11& program = m_program[currentProgram.idx];

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

					if (constantsChanged
					||  program.m_numPredefined > 0)
					{
						commitShaderConstants();
					}
				}

				{
					uint32_t changes = 0;
					for (uint8_t stage = 0; stage < maxTextureSamplers; ++stage)
					{
						const Binding& bind = renderBind.m_bind[stage];
						Binding& current = currentBind.m_bind[stage];
						if (current.m_idx          != bind.m_idx
						||  current.m_type         != bind.m_type
						||  current.m_samplerFlags != bind.m_samplerFlags
						||  programChanged)
						{
							if (kInvalidHandle != bind.m_idx)
							{
								switch (bind.m_type)
								{
								case Binding::Texture:
									{
										TextureD3D11& texture = m_textures[bind.m_idx];
										texture.commit(stage, bind.m_samplerFlags, _render->m_colorPalette);
									}
									break;

								case Binding::IndexBuffer:
								case Binding::VertexBuffer:
									{
										const BufferD3D11& buffer = Binding::IndexBuffer == bind.m_type
											? m_indexBuffers[bind.m_idx]
											: m_vertexBuffers[bind.m_idx]
											;
										m_textureStage.m_srv[stage] = buffer.m_srv;
										m_textureStage.m_sampler[stage] = NULL;
									}
									break;
								}
							}
							else
							{
								m_textureStage.m_srv[stage]     = NULL;
								m_textureStage.m_sampler[stage] = NULL;
							}

							++changes;
						}

						current = bind;
					}

					if (0 < changes)
					{
						commitTextureStage();
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

					ID3D11Buffer* buffers[BGFX_CONFIG_MAX_VERTEX_STREAMS];
					uint32_t strides[BGFX_CONFIG_MAX_VERTEX_STREAMS];
					uint32_t offsets[BGFX_CONFIG_MAX_VERTEX_STREAMS];
					const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];

					uint32_t numVertices = draw.m_numVertices;
					uint8_t  numStreams  = 0;

					if (UINT8_MAX != draw.m_streamMask)
					{
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
							const VertexBufferD3D11& vb = m_vertexBuffers[handle];
							const uint16_t layoutIdx = isValid(draw.m_stream[idx].m_layoutHandle)
								? draw.m_stream[idx].m_layoutHandle.idx
								: vb.m_layoutHandle.idx;
							const VertexLayout& layout = m_vertexLayouts[layoutIdx];
							const uint32_t stride = layout.m_stride;

							buffers[numStreams] = vb.m_ptr;
							strides[numStreams] = stride;
							offsets[numStreams] = draw.m_stream[idx].m_startVertex * stride;
							layouts[numStreams]   = &layout;

							numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
								? vb.m_size/stride
								: draw.m_numVertices
								, numVertices
								);
						}
					}

					currentState.m_numVertices = numVertices;

					if (0 < numStreams)
					{
						deviceCtx->IASetVertexBuffers(0, numStreams, buffers, strides, offsets);

						if (isValid(draw.m_instanceDataBuffer) )
						{
							const VertexBufferD3D11& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							const uint32_t instStride = draw.m_instanceDataStride;
							deviceCtx->IASetVertexBuffers(numStreams, 1, &inst.m_ptr, &instStride, &draw.m_instanceDataOffset);
							setInputLayout(numStreams, layouts, m_program[currentProgram.idx], uint16_t(instStride/16) );
						}
						else
						{
							deviceCtx->IASetVertexBuffers(numStreams, 1, s_zero.m_buffer, s_zero.m_zero, s_zero.m_zero);
							setInputLayout(numStreams, layouts, m_program[currentProgram.idx], 0);
						}
					}
					else
					{
						deviceCtx->IASetVertexBuffers(0, 1, s_zero.m_buffer, s_zero.m_zero, s_zero.m_zero);

						if (isValid(draw.m_instanceDataBuffer) )
						{
							const VertexBufferD3D11& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
							const uint32_t instStride = draw.m_instanceDataStride;
							deviceCtx->IASetVertexBuffers(0, 1, &inst.m_ptr, &instStride, &draw.m_instanceDataOffset);
							setInputLayout(0, NULL, m_program[currentProgram.idx], uint16_t(instStride/16) );
						}
						else
						{
							deviceCtx->IASetInputLayout(NULL);
						}
					}
				}

				if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = draw.m_indexBuffer;

					uint16_t handle = draw.m_indexBuffer.idx;
					if (kInvalidHandle != handle)
					{
						const IndexBufferD3D11& ib = m_indexBuffers[handle];
						deviceCtx->IASetIndexBuffer(ib.m_ptr
							, 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT
							, 0
							);
					}
					else
					{
						deviceCtx->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
					}
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices       = currentState.m_numVertices;
					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(_render, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indirectBuffer) )
					{
						const VertexBufferD3D11& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];
						ID3D11Buffer* ptr = vb.m_ptr;

						if (isValid(draw.m_indexBuffer) )
						{
							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
								? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								: draw.m_numIndirect
								;

							multiDrawIndexedInstancedIndirect(
								  numDrawIndirect
								, ptr
								, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								);
						}
						else
						{
							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
								? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								: draw.m_numIndirect
								;

							multiDrawInstancedIndirect(
								  numDrawIndirect
								, ptr
								, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								);
						}
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							if (UINT32_MAX == draw.m_numIndices)
							{
								const IndexBufferD3D11& ib = m_indexBuffers[draw.m_indexBuffer.idx];
								const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								if (numInstances > 1)
								{
									deviceCtx->DrawIndexedInstanced(numIndices
										, draw.m_numInstances
										, 0
										, 0
										, 0
										);
								}
								else
								{
									deviceCtx->DrawIndexed(numIndices
										, 0
										, 0
										);
								}
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								if (numInstances > 1)
								{
									deviceCtx->DrawIndexedInstanced(numIndices
										, draw.m_numInstances
										, draw.m_startIndex
										, 0
										, 0
										);
								}
								else
								{
									deviceCtx->DrawIndexed(numIndices
										, draw.m_startIndex
										, 0
										);
								}
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							if (numInstances > 1)
							{
								deviceCtx->DrawInstanced(numVertices
									, draw.m_numInstances
									, 0
									, 0
									);
							}
							else
							{
								deviceCtx->Draw(numVertices
									, 0
									);
							}
						}

						if (hasOcclusionQuery)
						{
							m_occlusionQuery.end();
						}
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumDrawIndirect[primIndex]   += numDrawIndirect;
					statsNumIndices                   += numIndices;
				}
			}

			if (wasCompute)
			{
				setViewType(view, "C");
				BGFX_D3D11_PROFILER_END();
				BGFX_D3D11_PROFILER_BEGIN(view, kColorCompute);

				invalidateCompute();
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				if (0 != (m_resolution.reset & BGFX_RESET_FLUSH_AFTER_RENDER) )
				{
					deviceCtx->Flush();
				}

				captureElapsed = -bx::getHPCounter();
				capture();
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		BGFX_D3D11_PROFILER_END();

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

			const TimerQueryD3D11::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
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
		const TimerQueryD3D11::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
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
			BGFX_D3D11_PROFILER_BEGIN_LITERAL("debugstats", kColorFrame);

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
					, " %s.%d (FL %d.%d) / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					, m_deviceInterfaceVersion
					, (m_featureLevel >> 12) & 0xf
					, (m_featureLevel >>  8) & 0xf
					);

				const DXGI_ADAPTER_DESC& desc = m_dxgi.m_adapterDesc;
				char description[BX_COUNTOF(desc.Description)];
				wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
				tvm.printf(0, pos++, 0x8f, " Device: %s", description);

				char dedicatedVideo[16];
				bx::prettify(dedicatedVideo, BX_COUNTOF(dedicatedVideo), desc.DedicatedVideoMemory);

				char dedicatedSystem[16];
				bx::prettify(dedicatedSystem, BX_COUNTOF(dedicatedSystem), desc.DedicatedSystemMemory);

				char sharedSystem[16];
				bx::prettify(sharedSystem, BX_COUNTOF(sharedSystem), desc.SharedSystemMemory);

				char processMemoryUsed[16];
				bx::prettify(processMemoryUsed, BX_COUNTOF(processMemoryUsed), bx::getProcessMemoryUsed() );

				tvm.printf(0, pos++, 0x8f, " Memory: %s (video), %s (system), %s (shared), %s (process) "
					, dedicatedVideo
					, dedicatedSystem
					, sharedSystem
					, processMemoryUsed
					);

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
				tvm.printf(10, pos++, 0x8b, "    Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] %c GPU %7.4f [ms] (latency %d) "
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
					tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d, indirect %7d"
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						, statsNumDrawIndirect[ii]
						);
				}

				if (NULL != m_renderDocDll)
				{
					tvm.printf(tvm.m_width-27, 0, 0x4f, " [F11 - RenderDoc capture] ");
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8b, " Occlusion queries: %3d ", m_occlusionQuery.m_control.available() );

				pos++;
				tvm.printf(10, pos++, 0x8b, " State cache:                                ");
				tvm.printf(10, pos++, 0x8b, " Blend  | DepthS | Input  | Raster | Sampler ");
				tvm.printf(10, pos++, 0x8b, " %6d | %6d | %6d | %6d | %6d  "
					, m_blendStateCache.getCount()
					, m_depthStencilStateCache.getCount()
					, m_inputLayoutCache.getCount()
					, m_rasterizerStateCache.getCount()
					, m_samplerStateCache.getCount()
					);
				pos++;

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %7.4f [ms] ", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms] ", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms] ", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);

			BGFX_D3D11_PROFILER_END();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			BGFX_D3D11_PROFILER_BEGIN_LITERAL("debugtext", kColorFrame);

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			BGFX_D3D11_PROFILER_END();
		}

		m_deviceCtx->OMSetRenderTargets(1, s_zero.m_rtv, NULL);

		if (NULL != m_msaaRt)
		{
			ID3D11Texture2D* backBufferColor;
			DX_CHECK(m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBufferColor) );
			deviceCtx->ResolveSubresource(backBufferColor, 0, m_msaaRt, 0, m_scd.format);
			DX_RELEASE(backBufferColor, 0);
		}
	}
} /* namespace d3d11 */ } // namespace bgfx

#else

namespace bgfx { namespace d3d11
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace d3d11 */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11

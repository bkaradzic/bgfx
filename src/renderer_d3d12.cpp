/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D12
#	include "renderer_d3d12.h"

namespace bgfx { namespace d3d12
{
	static wchar_t s_viewNameW[BGFX_CONFIG_MAX_VIEWS][256];

	struct PrimInfo
	{
		D3D_PRIMITIVE_TOPOLOGY m_topology;
		D3D12_PRIMITIVE_TOPOLOGY_TYPE m_topologyType;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,  D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,  3, 3, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,  3, 1, 2 },
		{ D3D_PRIMITIVE_TOPOLOGY_LINELIST,      D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,      2, 2, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_POINTLIST,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,     1, 1, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED, 0, 0, 0 },
	};

	static const char* s_primName[] =
	{
		"TriList",
		"TriStrip",
		"Line",
		"Point",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_primInfo) == BX_COUNTOF(s_primName)+1);

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

	static const D3D12_BLEND s_blendFactor[][2] =
	{
		{ D3D12_BLEND(0),               D3D12_BLEND(0)               }, // ignored
		{ D3D12_BLEND_ZERO,             D3D12_BLEND_ZERO             }, // ZERO
		{ D3D12_BLEND_ONE,              D3D12_BLEND_ONE              }, // ONE
		{ D3D12_BLEND_SRC_COLOR,        D3D12_BLEND_SRC_ALPHA        }, // SRC_COLOR
		{ D3D12_BLEND_INV_SRC_COLOR,    D3D12_BLEND_INV_SRC_ALPHA    }, // INV_SRC_COLOR
		{ D3D12_BLEND_SRC_ALPHA,        D3D12_BLEND_SRC_ALPHA        }, // SRC_ALPHA
		{ D3D12_BLEND_INV_SRC_ALPHA,    D3D12_BLEND_INV_SRC_ALPHA    }, // INV_SRC_ALPHA
		{ D3D12_BLEND_DEST_ALPHA,       D3D12_BLEND_DEST_ALPHA       }, // DST_ALPHA
		{ D3D12_BLEND_INV_DEST_ALPHA,   D3D12_BLEND_INV_DEST_ALPHA   }, // INV_DST_ALPHA
		{ D3D12_BLEND_DEST_COLOR,       D3D12_BLEND_DEST_ALPHA       }, // DST_COLOR
		{ D3D12_BLEND_INV_DEST_COLOR,   D3D12_BLEND_INV_DEST_ALPHA   }, // INV_DST_COLOR
		{ D3D12_BLEND_SRC_ALPHA_SAT,    D3D12_BLEND_ONE              }, // SRC_ALPHA_SAT
		{ D3D12_BLEND_BLEND_FACTOR,     D3D12_BLEND_BLEND_FACTOR     }, // FACTOR
		{ D3D12_BLEND_INV_BLEND_FACTOR, D3D12_BLEND_INV_BLEND_FACTOR }, // INV_FACTOR
	};

	static const D3D12_BLEND_OP s_blendEquation[] =
	{
		D3D12_BLEND_OP_ADD,
		D3D12_BLEND_OP_SUBTRACT,
		D3D12_BLEND_OP_REV_SUBTRACT,
		D3D12_BLEND_OP_MIN,
		D3D12_BLEND_OP_MAX,
	};

	static const D3D12_COMPARISON_FUNC s_cmpFunc[] =
	{
		D3D12_COMPARISON_FUNC(0), // ignored
		D3D12_COMPARISON_FUNC_LESS,
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_COMPARISON_FUNC_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER,
		D3D12_COMPARISON_FUNC_NOT_EQUAL,
		D3D12_COMPARISON_FUNC_NEVER,
		D3D12_COMPARISON_FUNC_ALWAYS,
	};

	static const D3D12_STENCIL_OP s_stencilOp[] =
	{
		D3D12_STENCIL_OP_ZERO,
		D3D12_STENCIL_OP_KEEP,
		D3D12_STENCIL_OP_REPLACE,
		D3D12_STENCIL_OP_INCR,
		D3D12_STENCIL_OP_INCR_SAT,
		D3D12_STENCIL_OP_DECR,
		D3D12_STENCIL_OP_DECR_SAT,
		D3D12_STENCIL_OP_INVERT,
	};

	static const D3D12_CULL_MODE s_cullMode[] =
	{
		D3D12_CULL_MODE_NONE,
		D3D12_CULL_MODE_FRONT,
		D3D12_CULL_MODE_BACK,
	};

	static const D3D12_TEXTURE_ADDRESS_MODE s_textureAddress[] =
	{
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,
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
		{ DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC1_UNORM_SRGB      }, // BC1
		{ DXGI_FORMAT_BC2_UNORM,          DXGI_FORMAT_BC2_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC2_UNORM_SRGB      }, // BC2
		{ DXGI_FORMAT_BC3_UNORM,          DXGI_FORMAT_BC3_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC3_UNORM_SRGB      }, // BC3
		{ DXGI_FORMAT_BC4_UNORM,          DXGI_FORMAT_BC4_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // BC4
		{ DXGI_FORMAT_BC5_UNORM,          DXGI_FORMAT_BC5_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // BC5
		{ DXGI_FORMAT_BC6H_SF16,          DXGI_FORMAT_BC6H_SF16,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // BC6H
		{ DXGI_FORMAT_BC7_UNORM,          DXGI_FORMAT_BC7_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC7_UNORM_SRGB      }, // BC7
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // ETC1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // ETC2
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // ETC2A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // ETC2A1
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC12
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC14
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC12A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC14A
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC22
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // PTC24
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // Unknown
		{ DXGI_FORMAT_R1_UNORM,           DXGI_FORMAT_R1_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R1
		{ DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_A8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // A8
		{ DXGI_FORMAT_R8_UNORM,           DXGI_FORMAT_R8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R8
		{ DXGI_FORMAT_R8_SINT,            DXGI_FORMAT_R8_SINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R8I
		{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R8U
		{ DXGI_FORMAT_R8_SNORM,           DXGI_FORMAT_R8_SNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R8S
		{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R16
		{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R16I
		{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R16U
		{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R16F
		{ DXGI_FORMAT_R16_SNORM,          DXGI_FORMAT_R16_SNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R16S
		{ DXGI_FORMAT_R32_SINT,           DXGI_FORMAT_R32_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R32I
		{ DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_UINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R32U
		{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R32F
		{ DXGI_FORMAT_R8G8_UNORM,         DXGI_FORMAT_R8G8_UNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG8
		{ DXGI_FORMAT_R8G8_SINT,          DXGI_FORMAT_R8G8_SINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG8I
		{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG8U
		{ DXGI_FORMAT_R8G8_SNORM,         DXGI_FORMAT_R8G8_SNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG8S
		{ DXGI_FORMAT_R16G16_UNORM,       DXGI_FORMAT_R16G16_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG16
		{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG16I
		{ DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG16U
		{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG16F
		{ DXGI_FORMAT_R16G16_SNORM,       DXGI_FORMAT_R16G16_SNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG16S
		{ DXGI_FORMAT_R32G32_SINT,        DXGI_FORMAT_R32G32_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG32I
		{ DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG32U
		{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RG32F
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB8
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB8I
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB8U
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB8S
		{ DXGI_FORMAT_R9G9B9E5_SHAREDEXP, DXGI_FORMAT_R9G9B9E5_SHAREDEXP,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB9E5F
		{ DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_B8G8R8A8_UNORM_SRGB }, // BGRA8
		{ DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB }, // RGBA8
		{ DXGI_FORMAT_R8G8B8A8_SINT,      DXGI_FORMAT_R8G8B8A8_SINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB }, // RGBA8I
		{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB }, // RGBA8U
		{ DXGI_FORMAT_R8G8B8A8_SNORM,     DXGI_FORMAT_R8G8B8A8_SNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA8S
		{ DXGI_FORMAT_R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA16
		{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA16I
		{ DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA16U
		{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA16F
		{ DXGI_FORMAT_R16G16B16A16_SNORM, DXGI_FORMAT_R16G16B16A16_SNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA16S
		{ DXGI_FORMAT_R32G32B32A32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA32I
		{ DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA32U
		{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA32F
		{ DXGI_FORMAT_B5G6R5_UNORM,       DXGI_FORMAT_B5G6R5_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R5G6B5
		{ DXGI_FORMAT_B4G4R4A4_UNORM,     DXGI_FORMAT_B4G4R4A4_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGBA4
		{ DXGI_FORMAT_B5G5R5A1_UNORM,     DXGI_FORMAT_B5G5R5A1_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB5A1
		{ DXGI_FORMAT_R10G10B10A2_UNORM,  DXGI_FORMAT_R10G10B10A2_UNORM,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // RGB10A2
		{ DXGI_FORMAT_R11G11B10_FLOAT,    DXGI_FORMAT_R11G11B10_FLOAT,       DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // R11G11B10F
		{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN             }, // UnknownDepth
		{ DXGI_FORMAT_R16_TYPELESS,       DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_D16_UNORM,         DXGI_FORMAT_UNKNOWN             }, // D16
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN             }, // D24
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN             }, // D24S8
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN             }, // D32
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN             }, // D16F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN             }, // D24F
		{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN             }, // D32F
		{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN             }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	static const D3D12_INPUT_ELEMENT_DESC s_attrib[] =
	{
		{ "POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BITANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        1, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     1, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     2, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     3, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     4, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     5, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     6, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     7, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
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

	static D3D12_INPUT_ELEMENT_DESC* fillVertexDecl(D3D12_INPUT_ELEMENT_DESC* _out, const VertexDecl& _decl)
	{
		D3D12_INPUT_ELEMENT_DESC* elem = _out;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _decl.m_attributes[attr])
			{
				bx::memCopy(elem, &s_attrib[attr], sizeof(D3D12_INPUT_ELEMENT_DESC) );

				if (0 == _decl.m_attributes[attr])
				{
					elem->AlignedByteOffset = 0;
				}
				else
				{
					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);
					elem->Format = s_attribType[type][num-1][normalized];
					elem->AlignedByteOffset = _decl.m_offset[attr];
				}

				++elem;
			}
		}

		return elem;
	}

	void setResourceBarrier(ID3D12GraphicsCommandList* _commandList, const ID3D12Resource* _resource, D3D12_RESOURCE_STATES _stateBefore, D3D12_RESOURCE_STATES _stateAfter)
	{
		D3D12_RESOURCE_BARRIER barrier;
		barrier.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource   = const_cast<ID3D12Resource*>(_resource);
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = _stateBefore;
		barrier.Transition.StateAfter  = _stateAfter;
		_commandList->ResourceBarrier(1, &barrier);
	}

#if USE_D3D12_DYNAMIC_LIB
	static const GUID IID_ID3D12CommandAllocator    = { 0x6102dee4, 0xaf59, 0x4b09, { 0xb9, 0x99, 0xb4, 0x4d, 0x73, 0xf0, 0x9b, 0x24 } };
	static const GUID IID_ID3D12CommandQueue        = { 0x0ec870a6, 0x5d7e, 0x4c22, { 0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed } };
	static const GUID IID_ID3D12CommandSignature    = { 0xc36a797c, 0xec80, 0x4f0a, { 0x89, 0x85, 0xa7, 0xb2, 0x47, 0x50, 0x82, 0xd1 } };
	static const GUID IID_ID3D12Debug               = { 0x344488b7, 0x6846, 0x474b, { 0xb9, 0x89, 0xf0, 0x27, 0x44, 0x82, 0x45, 0xe0 } };
	static const GUID IID_ID3D12DescriptorHeap      = { 0x8efb471d, 0x616c, 0x4f49, { 0x90, 0xf7, 0x12, 0x7b, 0xb7, 0x63, 0xfa, 0x51 } };
	static const GUID IID_ID3D12Device              = { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
	static const GUID IID_ID3D12Fence               = { 0x0a753dcf, 0xc4d8, 0x4b91, { 0xad, 0xf6, 0xbe, 0x5a, 0x60, 0xd9, 0x5a, 0x76 } };
	static const GUID IID_ID3D12GraphicsCommandList = { 0x5b160d0f, 0xac1b, 0x4185, { 0x8b, 0xa8, 0xb3, 0xae, 0x42, 0xa5, 0xa4, 0x55 } };
	static const GUID IID_ID3D12InfoQueue           = { 0x0742a90b, 0xc387, 0x483f, { 0xb9, 0x46, 0x30, 0xa7, 0xe4, 0xe6, 0x14, 0x58 } };
	static const GUID IID_ID3D12PipelineState       = { 0x765a30f3, 0xf624, 0x4c6f, { 0xa8, 0x28, 0xac, 0xe9, 0x48, 0x62, 0x24, 0x45 } };
	static const GUID IID_ID3D12Resource            = { 0x696442be, 0xa72e, 0x4059, { 0xbc, 0x79, 0x5b, 0x5c, 0x98, 0x04, 0x0f, 0xad } };
	static const GUID IID_ID3D12RootSignature       = { 0xc54a6b66, 0x72df, 0x4ee8, { 0x8b, 0xe5, 0xa9, 0x46, 0xa1, 0x42, 0x92, 0x14 } };
	static const GUID IID_ID3D12QueryHeap           = { 0x0d9658ae, 0xed45, 0x469e, { 0xa6, 0x1d, 0x97, 0x0e, 0xc5, 0x83, 0xca, 0xb4 } };
	static const GUID IID_IDXGIFactory4             = { 0x1bc6ea02, 0xef36, 0x464f, { 0xbf, 0x0c, 0x21, 0xca, 0x39, 0xe5, 0x16, 0x8a } };
#else
	static const GUID IID_ID3D12CommandSignature    = { 0xc36a797c, 0xec80, 0x4f0a, { 0x89, 0x85, 0xa7, 0xb2, 0x47, 0x50, 0x82, 0xd1 } };
	static const GUID IID_ID3D12QueryHeap           = { 0x0d9658ae, 0xed45, 0x469e, { 0xa6, 0x1d, 0x97, 0x0e, 0xc5, 0x83, 0xca, 0xb4 } };
#endif // USE_D3D12_DYNAMIC_LIB

	struct HeapProperty
	{
		enum Enum
		{
			Default,
			Upload,
			ReadBack,

			Count
		};

		D3D12_HEAP_PROPERTIES m_properties;
		D3D12_RESOURCE_STATES m_state;
	};

	static const HeapProperty s_heapProperties[] =
	{
		{ { D3D12_HEAP_TYPE_DEFAULT,  D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1 }, D3D12_RESOURCE_STATE_COMMON       },
		{ { D3D12_HEAP_TYPE_UPLOAD,   D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1 }, D3D12_RESOURCE_STATE_GENERIC_READ },
		{ { D3D12_HEAP_TYPE_READBACK, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1 }, D3D12_RESOURCE_STATE_COPY_DEST    },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_heapProperties) == HeapProperty::Count);

	ID3D12Resource* createCommittedResource(ID3D12Device* _device, HeapProperty::Enum _heapProperty, D3D12_RESOURCE_DESC* _resourceDesc, D3D12_CLEAR_VALUE* _clearValue)
	{
		const HeapProperty& heapProperty = s_heapProperties[_heapProperty];
		ID3D12Resource* resource;
		DX_CHECK(_device->CreateCommittedResource(&heapProperty.m_properties
				, D3D12_HEAP_FLAG_NONE
				, _resourceDesc
				, heapProperty.m_state
				, _clearValue
				, IID_ID3D12Resource
				, (void**)&resource
				) );
		BX_WARN(NULL != resource, "CreateCommittedResource failed (size: %d). Out of memory?"
			, _resourceDesc->Width
			);

		return resource;
	}

	ID3D12Resource* createCommittedResource(ID3D12Device* _device, HeapProperty::Enum _heapProperty, uint64_t _size, D3D12_RESOURCE_FLAGS _flags = D3D12_RESOURCE_FLAG_NONE)
	{
		D3D12_RESOURCE_DESC resourceDesc;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width     = _size;
		resourceDesc.Height    = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format             = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count   = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags  = _flags;

		return createCommittedResource(_device, _heapProperty, &resourceDesc, NULL);
	}

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

	BX_NO_INLINE void setDebugObjectName(ID3D12Object* _object, const char* _format, ...)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OBJECT_NAME) )
		{
			char temp[2048];
			va_list argList;
			va_start(argList, _format);
			int size = bx::uint32_min(sizeof(temp)-1, bx::vsnprintf(temp, sizeof(temp), _format, argList) );
			va_end(argList);
			temp[size] = '\0';

			wchar_t* wtemp = (wchar_t*)alloca( (size+1)*2);
			mbstowcs(wtemp, temp, size+1);
			_object->SetName(wtemp);
		}
	}

#if USE_D3D12_DYNAMIC_LIB
	static PFN_D3D12_CREATE_DEVICE            D3D12CreateDevice;
	static PFN_D3D12_GET_DEBUG_INTERFACE      D3D12GetDebugInterface;
	static PFN_D3D12_SERIALIZE_ROOT_SIGNATURE D3D12SerializeRootSignature;
	static PFN_CREATE_DXGI_FACTORY            CreateDXGIFactory1;

	typedef HANDLE  (WINAPI* PFN_CREATE_EVENT_EX_A)(LPSECURITY_ATTRIBUTES _attrs, LPCSTR _name, DWORD _flags, DWORD _access);
	static PFN_CREATE_EVENT_EX_A CreateEventExA;
#endif // USE_D3D12_DYNAMIC_LIB

	struct RendererContextD3D12 : public RendererContextI
	{
		RendererContextD3D12()
			: m_d3d12dll(NULL)
			, m_dxgidll(NULL)
			, m_renderdocdll(NULL)
			, m_featureLevel(D3D_FEATURE_LEVEL(0) )
			, m_wireframe(false)
			, m_lost(false)
			, m_maxAnisotropy(1)
			, m_depthClamp(false)
			, m_fsChanges(0)
			, m_vsChanges(0)
			, m_backBufferColorIdx(0)
			, m_rtMsaa(false)
		{
		}

		~RendererContextD3D12()
		{
		}

		bool init()
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedKernel32,
					LoadedD3D12,
					LoadedDXGI,
					CreatedDXGIFactory,
					CreatedCommandQueue,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;
			LUID luid;

			m_renderdocdll = loadRenderDoc();

			m_fbh.idx = invalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

#if USE_D3D12_DYNAMIC_LIB
			m_kernel32dll = bx::dlopen("kernel32.dll");
			BX_WARN(NULL != m_kernel32dll, "Failed to load kernel32.dll.");
			if (NULL == m_kernel32dll)
			{
				goto error;
			}

			CreateEventExA = (PFN_CREATE_EVENT_EX_A)bx::dlsym(m_kernel32dll, "CreateEventExA");
			BX_WARN(NULL != CreateEventExA, "Function CreateEventExA not found.");
			if (NULL == CreateEventExA)
			{
				goto error;
			}

			errorState = ErrorState::LoadedKernel32;

			m_d3d12dll = bx::dlopen("d3d12.dll");
			BX_WARN(NULL != m_d3d12dll, "Failed to load d3d12.dll.");
			if (NULL == m_d3d12dll)
			{
				goto error;
			}

			errorState = ErrorState::LoadedD3D12;

			D3D12CreateDevice = (PFN_D3D12_CREATE_DEVICE)bx::dlsym(m_d3d12dll, "D3D12CreateDevice");
			BX_WARN(NULL != D3D12CreateDevice, "Function D3D12CreateDevice not found.");

			D3D12GetDebugInterface = (PFN_D3D12_GET_DEBUG_INTERFACE)bx::dlsym(m_d3d12dll, "D3D12GetDebugInterface");
			BX_WARN(NULL != D3D12GetDebugInterface, "Function D3D12GetDebugInterface not found.");

			D3D12SerializeRootSignature = (PFN_D3D12_SERIALIZE_ROOT_SIGNATURE)bx::dlsym(m_d3d12dll, "D3D12SerializeRootSignature");
			BX_WARN(NULL != D3D12SerializeRootSignature, "Function D3D12SerializeRootSignature not found.");

			if (NULL == D3D12CreateDevice
			||  NULL == D3D12GetDebugInterface
			||  NULL == D3D12SerializeRootSignature)
			{
				goto error;
			}

			m_dxgidll = bx::dlopen("dxgi.dll");
			BX_WARN(NULL != m_dxgidll, "Failed to load dxgi.dll.");

			if (NULL == m_dxgidll)
			{
				goto error;
			}

			CreateDXGIFactory1 = (PFN_CREATE_DXGI_FACTORY)bx::dlsym(m_dxgidll, "CreateDXGIFactory1");
			BX_WARN(NULL != CreateDXGIFactory1, "Function CreateDXGIFactory1 not found.");

			if (NULL == CreateDXGIFactory1)
			{
				goto error;
			}
#endif // USE_D3D12_DYNAMIC_LIB

			errorState = ErrorState::LoadedDXGI;

			HRESULT hr;

#if BX_PLATFORM_WINDOWS
			hr = CreateDXGIFactory1(IID_IDXGIFactory4, (void**)&m_factory);
#else
			hr = S_OK;
			m_factory = NULL;
#endif // BX_PLATFORM_*
			BX_WARN(SUCCEEDED(hr), "Unable to create DXGI factory.");

			if (FAILED(hr) )
			{
				goto error;
			}

			errorState = ErrorState::CreatedDXGIFactory;

			m_adapter = NULL;
			m_driverType = D3D_DRIVER_TYPE_HARDWARE;

			if (NULL != m_factory)
			{
#if BX_PLATFORM_WINDOWS
				IDXGIAdapter3* adapter;
#else
				IDXGIAdapter* adapter;
#endif // BX_PLATFORM_*
				for (uint32_t ii = 0; DXGI_ERROR_NOT_FOUND != m_factory->EnumAdapters(ii, reinterpret_cast<IDXGIAdapter**>(&adapter) ); ++ii)
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

						g_caps.gpu[ii].vendorId = (uint16_t)desc.VendorId;
						g_caps.gpu[ii].deviceId = (uint16_t)desc.DeviceId;
						++g_caps.numGPUs;

						if ( (BGFX_PCI_ID_NONE != g_caps.vendorId ||             0 != g_caps.deviceId)
						&&   (BGFX_PCI_ID_NONE == g_caps.vendorId || desc.VendorId == g_caps.vendorId)
						&&   (0 == g_caps.deviceId                || desc.DeviceId == g_caps.deviceId) )
						{
							m_adapter = adapter;
							m_adapter->AddRef();
							m_driverType = D3D_DRIVER_TYPE_UNKNOWN;
						}

						if (BX_ENABLED(BGFX_CONFIG_DEBUG_PERFHUD)
						&&  0 != bx::strnstr(description, "PerfHUD") )
						{
							m_adapter = adapter;
							m_driverType = D3D_DRIVER_TYPE_REFERENCE;
						}
					}

					DX_RELEASE(adapter, adapter == m_adapter ? 1 : 0);
				}
			}

			if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
			{
				ID3D12Debug* debug;
				hr = D3D12GetDebugInterface(IID_ID3D12Debug, (void**)&debug);

				if (SUCCEEDED(hr) )
				{
					debug->EnableDebugLayer();
				}
			}

			{
				D3D_FEATURE_LEVEL featureLevel[] =
				{
					D3D_FEATURE_LEVEL_12_1,
					D3D_FEATURE_LEVEL_12_0,
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0,
				};

				hr = E_FAIL;
				for (uint32_t ii = 0; ii < BX_COUNTOF(featureLevel) && FAILED(hr); ++ii)
				{
					hr = D3D12CreateDevice(m_adapter
							, featureLevel[ii]
							, IID_ID3D12Device
							, (void**)&m_device
							);
					BX_WARN(FAILED(hr), "Direct3D12 device feature level %d.%d."
						, (featureLevel[ii] >> 12) & 0xf
						, (featureLevel[ii] >>  8) & 0xf
						);
					m_featureLevel = featureLevel[ii];
				}
			}

			if (FAILED(hr) )
			{
				BX_TRACE("Unable to create Direct3D12 device.");
				goto error;
			}

			if (NULL != m_factory)
			{
				bx::memSet(&m_adapterDesc, 0, sizeof(m_adapterDesc) );
				luid = m_device->GetAdapterLuid();
#if BX_PLATFORM_WINDOWS
				IDXGIAdapter3* adapter;
#else
				IDXGIAdapter* adapter;
#endif // BX_PLATFORM_*
				for (uint32_t ii = 0; DXGI_ERROR_NOT_FOUND != m_factory->EnumAdapters(ii, reinterpret_cast<IDXGIAdapter**>(&adapter) ); ++ii)
				{
					adapter->GetDesc(&m_adapterDesc);
					if (m_adapterDesc.AdapterLuid.LowPart  == luid.LowPart
					&&  m_adapterDesc.AdapterLuid.HighPart == luid.HighPart)
					{
						if (NULL == m_adapter)
						{
							m_adapter = adapter;
						}
						else
						{
							DX_RELEASE(adapter, 0);
						}
						break;
					}
					DX_RELEASE(adapter, 0);
				}
			}

			g_caps.vendorId = (uint16_t)m_adapterDesc.VendorId;
			g_caps.deviceId = (uint16_t)m_adapterDesc.DeviceId;

			{
				uint32_t numNodes = m_device->GetNodeCount();
				BX_TRACE("D3D12 GPU Architecture (num nodes: %d):", numNodes);
				for (uint32_t ii = 0; ii < numNodes; ++ii)
				{
					D3D12_FEATURE_DATA_ARCHITECTURE architecture;
					architecture.NodeIndex = ii;
					DX_CHECK(m_device->CheckFeatureSupport(D3D12_FEATURE_ARCHITECTURE, &architecture, sizeof(architecture) ) );
					BX_TRACE("\tNode % 2d: TileBasedRenderer %d, UMA %d, CacheCoherentUMA %d"
							, ii
							, architecture.TileBasedRenderer
							, architecture.UMA
							, architecture.CacheCoherentUMA
							);
					if (0 == ii)
					{
						bx::memCopy(&m_architecture, &architecture, sizeof(architecture) );
					}
				}
			}

#if !BX_PLATFORM_WINDOWS
			if (NULL == m_factory)
			{
				IDXGIDevice1* dxgiDevice;
				hr = m_device->QueryInterface(IID_IDXGIDevice1, (void**)&dxgiDevice);

				if (FAILED(hr) )
				{
					BX_TRACE("Unable to query IDXGIDevice1 interface 0x%08x.", hr);
					goto error;
				}

				hr = dxgiDevice->GetAdapter(&m_adapter);

				if (FAILED(hr) )
				{
					BX_TRACE("DXGIDevice1::GetAdapter failed 0x%08x.", hr);
					goto error;
				}

				hr = m_adapter->GetParent(IID_IDXGIFactory2, (void**)&m_factory);

				if (FAILED(hr) )
				{
					BX_TRACE("IDXGIAdapter::GetParent failed 0x%08x.", hr);
					goto error;
				}
			}
#endif // !BX_PLATFORM_WINDOWS

			DX_CHECK(m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &m_options, sizeof(m_options) ) );
			BX_TRACE("D3D12 options:")
			BX_TRACE("\tTiledResourcesTier %d", m_options.TiledResourcesTier);
			BX_TRACE("\tResourceBindingTier %d", m_options.ResourceBindingTier);
			BX_TRACE("\tROVsSupported %d", m_options.ROVsSupported);
			BX_TRACE("\tConservativeRasterizationTier %d", m_options.ConservativeRasterizationTier);
			BX_TRACE("\tCrossNodeSharingTier %d", m_options.CrossNodeSharingTier);
			BX_TRACE("\tResourceHeapTier %d", m_options.ResourceHeapTier);

			m_cmd.init(m_device);
			errorState = ErrorState::CreatedCommandQueue;

			if (NULL == g_platformData.backBuffer)
			{
#if !BX_PLATFORM_WINDOWS
				hr = m_adapter->GetParent(__uuidof(IDXGIFactory2), (void**)&m_factory);
				DX_RELEASE(m_adapter, 1);
				if (FAILED(hr) )
				{
					BX_TRACE("Unable to create Direct3D11 device.");
					goto error;
				}

				m_scd.Width  = BGFX_DEFAULT_WIDTH;
				m_scd.Height = BGFX_DEFAULT_HEIGHT;
				m_scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				m_scd.Stereo  = false;
				m_scd.SampleDesc.Count   = 1;
				m_scd.SampleDesc.Quality = 0;
				m_scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				m_scd.BufferCount  = bx::uint32_min(BX_COUNTOF(m_backBufferColor), 4);
				m_scd.Scaling      = DXGI_SCALING_STRETCH;
				m_scd.SwapEffect   = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
				m_scd.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				if (NULL == g_platformData.ndt)
				{
					hr = m_factory->CreateSwapChainForCoreWindow(m_device
						, (::IUnknown*)g_platformData.nwh
						, &m_scd
						, NULL
						, &m_swapChain
						);
					BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to create Direct3D11 swap chain.");
				}
				else
				{
					BGFX_FATAL(g_platformData.ndt == reinterpret_cast<void*>(1), Fatal::UnableToInitialize, "Unable to set swap chain on panel.");

					hr = m_factory->CreateSwapChainForComposition(m_device
							, &m_scd
							, NULL
							, &m_swapChain
							);
					BX_WARN(SUCCEEDED(hr), "Unable to create Direct3D11 swap chain.");

#	if BX_PLATFORM_WINRT
					IInspectable* nativeWindow = reinterpret_cast<IInspectable *>(g_platformData.nwh);
					ISwapChainBackgroundPanelNative* panel = NULL;
					hr = nativeWindow->QueryInterface(__uuidof(ISwapChainBackgroundPanelNative), (void**)&panel);
					BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to set swap chain on panel.");

					if (NULL != panel)
					{
						hr = panel->SetSwapChain(m_swapChain);
						BGFX_FATAL(SUCCEEDED(hr), Fatal::UnableToInitialize, "Unable to set swap chain on panel.");

						panel->Release();
					}
#	endif // BX_PLATFORM_WINRT
				}
#else
				m_scd.BufferDesc.Width  = BGFX_DEFAULT_WIDTH;
				m_scd.BufferDesc.Height = BGFX_DEFAULT_HEIGHT;
				m_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				m_scd.BufferDesc.Scaling                 = DXGI_MODE_SCALING_STRETCHED;
				m_scd.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				m_scd.BufferDesc.RefreshRate.Numerator   = 60;
				m_scd.BufferDesc.RefreshRate.Denominator = 1;
				m_scd.SampleDesc.Count   = 1;
				m_scd.SampleDesc.Quality = 0;
				m_scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				m_scd.BufferCount  = bx::uint32_min(BX_COUNTOF(m_backBufferColor), 4);
				m_scd.OutputWindow = (HWND)g_platformData.nwh;
				m_scd.Windowed     = true;
				m_scd.SwapEffect   = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
				m_scd.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				BX_CHECK(m_scd.BufferCount <= BX_COUNTOF(m_backBufferColor), "Swap chain buffer count %d (max %d)."
						, m_scd.BufferCount
						, BX_COUNTOF(m_backBufferColor)
						);
				hr = m_factory->CreateSwapChain(m_cmd.m_commandQueue
						, &m_scd
						, reinterpret_cast<IDXGISwapChain**>(&m_swapChain)
						);
#endif // BX_PLATFORM_*
				if (FAILED(hr) )
				{
					BX_TRACE("Failed to create swap chain.");
					goto error;
				}
			}

			m_presentElapsed = 0;

			{
				m_resolution.m_width  = BGFX_DEFAULT_WIDTH;
				m_resolution.m_height = BGFX_DEFAULT_HEIGHT;

				m_numWindows = 1;

#if BX_PLATFORM_WINDOWS
				DX_CHECK(m_factory->MakeWindowAssociation( (HWND)g_platformData.nwh
						, 0
						| DXGI_MWA_NO_WINDOW_CHANGES
						| DXGI_MWA_NO_ALT_ENTER
						) );

				if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
				{
					hr = m_device->QueryInterface(IID_ID3D12InfoQueue, (void**)&m_infoQueue);

					if (SUCCEEDED(hr) )
					{
						m_infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
						m_infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR,      true);
						m_infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING,    false);

						D3D12_INFO_QUEUE_FILTER filter;
						bx::memSet(&filter, 0, sizeof(filter) );

						D3D12_MESSAGE_CATEGORY catlist[] =
						{
							D3D12_MESSAGE_CATEGORY_STATE_CREATION,
							D3D12_MESSAGE_CATEGORY_EXECUTION,
						};
						filter.DenyList.NumCategories = BX_COUNTOF(catlist);
						filter.DenyList.pCategoryList = catlist;
						m_infoQueue->PushStorageFilter(&filter);

						DX_RELEASE_WARNONLY(m_infoQueue, 0);
					}
				}
#endif // BX_PLATFORM_WINDOWS

				D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeap;
				rtvDescHeap.NumDescriptors = 0
						+ BX_COUNTOF(m_backBufferColor)
						+ BGFX_CONFIG_MAX_FRAME_BUFFERS*BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
						;
				rtvDescHeap.Type     = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				rtvDescHeap.Flags    = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				rtvDescHeap.NodeMask = 1;
				DX_CHECK(m_device->CreateDescriptorHeap(&rtvDescHeap
						, IID_ID3D12DescriptorHeap
						, (void**)&m_rtvDescriptorHeap
						) );

				D3D12_DESCRIPTOR_HEAP_DESC dsvDescHeap;
				dsvDescHeap.NumDescriptors = 0
						+ 1 // reserved for depth backbuffer.
						+ BGFX_CONFIG_MAX_FRAME_BUFFERS
						;
				dsvDescHeap.Type     = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				dsvDescHeap.Flags    = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				dsvDescHeap.NodeMask = 1;
				DX_CHECK(m_device->CreateDescriptorHeap(&dsvDescHeap
						, IID_ID3D12DescriptorHeap
						, (void**)&m_dsvDescriptorHeap
						) );

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffer); ++ii)
				{
					m_scratchBuffer[ii].create(BGFX_CONFIG_MAX_DRAW_CALLS*1024
							, BGFX_CONFIG_MAX_TEXTURES + BGFX_CONFIG_MAX_SHADERS + BGFX_CONFIG_MAX_DRAW_CALLS
							);
				}
				m_samplerAllocator.create(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
						, 1024
						, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS
						);

				D3D12_DESCRIPTOR_RANGE descRange[] =
				{
					{ D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
					{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV,     BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
					{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV,     1,                                0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
					{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV,     BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
				};
				BX_STATIC_ASSERT(BX_COUNTOF(descRange) == Rdt::Count);

				D3D12_ROOT_PARAMETER rootParameter[] =
				{
					{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[Rdt::Sampler] } }, D3D12_SHADER_VISIBILITY_ALL },
					{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[Rdt::SRV]     } }, D3D12_SHADER_VISIBILITY_ALL },
					{ D3D12_ROOT_PARAMETER_TYPE_CBV,              { { 0, 0                        } }, D3D12_SHADER_VISIBILITY_ALL },
					{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[Rdt::UAV]     } }, D3D12_SHADER_VISIBILITY_ALL },
				};
				rootParameter[Rdt::CBV].Descriptor.RegisterSpace  = 0;
				rootParameter[Rdt::CBV].Descriptor.ShaderRegister = 0;

				D3D12_ROOT_SIGNATURE_DESC descRootSignature;
				descRootSignature.NumParameters = BX_COUNTOF(rootParameter);
				descRootSignature.pParameters   = rootParameter;
				descRootSignature.NumStaticSamplers = 0;
				descRootSignature.pStaticSamplers   = NULL;
				descRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

				ID3DBlob* outBlob;
				ID3DBlob* errorBlob;
				DX_CHECK(D3D12SerializeRootSignature(&descRootSignature
						, D3D_ROOT_SIGNATURE_VERSION_1
						, &outBlob
						, &errorBlob
						) );

				DX_CHECK(m_device->CreateRootSignature(0
						, outBlob->GetBufferPointer()
						, outBlob->GetBufferSize()
						, IID_ID3D12RootSignature
						, (void**)&m_rootSignature
						) );

				g_caps.supported |= ( 0
									| BGFX_CAPS_TEXTURE_3D
									| BGFX_CAPS_TEXTURE_COMPARE_ALL
									| BGFX_CAPS_INSTANCING
									| BGFX_CAPS_VERTEX_ATTRIB_HALF
									| BGFX_CAPS_VERTEX_ATTRIB_UINT10
									| BGFX_CAPS_FRAGMENT_DEPTH
									| BGFX_CAPS_BLEND_INDEPENDENT
									| BGFX_CAPS_COMPUTE
									| (m_options.ROVsSupported ? BGFX_CAPS_FRAGMENT_ORDERING : 0)
//									| BGFX_CAPS_SWAP_CHAIN
									| BGFX_CAPS_TEXTURE_BLIT
									| BGFX_CAPS_TEXTURE_READ_BACK
									| BGFX_CAPS_OCCLUSION_QUERY
									| BGFX_CAPS_ALPHA_TO_COVERAGE
									| BGFX_CAPS_TEXTURE_2D_ARRAY
									| BGFX_CAPS_TEXTURE_CUBE_ARRAY
									);
				g_caps.limits.maxTextureSize   = 16384;
				g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(16, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) );

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
						D3D12_FEATURE_DATA_FORMAT_SUPPORT data;
						data.Format = fmt;
						hr = m_device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof(data) );
						if (SUCCEEDED(hr) )
						{
							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURE2D
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_2D
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURE3D
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_3D
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURECUBE
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_CUBE
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_BUFFER
									| D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER
									| D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_VERTEX
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_SHADER_LOAD
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_IMAGE
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_RENDER_TARGET
									| D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_MSAA
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

							data.Format = s_textureFormat[ii].m_fmt;
							hr = m_device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof(data) );
							if (SUCCEEDED(hr) )
							{
								support |= 0 != (data.Support2 & (0
										| D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD
										| D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE
										) )
										? BGFX_CAPS_FORMAT_TEXTURE_IMAGE
										: BGFX_CAPS_FORMAT_TEXTURE_NONE
										;
							}
						}
					}

					if (DXGI_FORMAT_UNKNOWN != fmtSrgb)
					{
						struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
						{
							DXGI_FORMAT InFormat;
							UINT OutFormatSupport;
						};

						D3D12_FEATURE_DATA_FORMAT_SUPPORT data;
						data.Format = fmtSrgb;
						hr = m_device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof(data) );
						if (SUCCEEDED(hr) )
						{
							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURE2D
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURE3D
									) )
									? BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
									: BGFX_CAPS_FORMAT_TEXTURE_NONE
									;

							support |= 0 != (data.Support1 & (0
									| D3D12_FORMAT_SUPPORT1_TEXTURECUBE
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

					g_caps.formats[ii] = support;
				}

				postReset();

				m_batch.create(4<<10);
				m_gpuTimer.init();
				m_occlusionQuery.init();
			}

			g_internalData.context = m_device;
			return true;

		error:
			switch (errorState)
			{
			case ErrorState::CreatedCommandQueue:
				m_cmd.shutdown();
			case ErrorState::CreatedDXGIFactory:
				DX_RELEASE(m_device,  0);
				DX_RELEASE(m_adapter, 0);
				DX_RELEASE(m_factory, 0);
#if USE_D3D12_DYNAMIC_LIB
			case ErrorState::LoadedDXGI:
				bx::dlclose(m_dxgidll);
			case ErrorState::LoadedD3D12:
				bx::dlclose(m_d3d12dll);
			case ErrorState::LoadedKernel32:
				bx::dlclose(m_kernel32dll);
#endif // USE_D3D12_DYNAMIC_LIB
			case ErrorState::Default:
			default:
				unloadRenderDoc(m_renderdocdll);
				break;
			}

			return false;
		}

		void shutdown()
		{
			m_batch.destroy();

			preReset();

			m_gpuTimer.shutdown();
			m_occlusionQuery.shutdown();

			m_samplerAllocator.destroy();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffer); ++ii)
			{
				m_scratchBuffer[ii].destroy();
			}

			m_pipelineStateCache.invalidate();

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

			DX_RELEASE(m_rtvDescriptorHeap, 0);
			DX_RELEASE(m_dsvDescriptorHeap, 0);

			DX_RELEASE(m_rootSignature, 0);

			DX_RELEASE(m_swapChain, 0);

			m_cmd.shutdown();

			DX_RELEASE(m_device, 0);
			DX_RELEASE(m_adapter, 0);
			DX_RELEASE(m_factory, 0);

			unloadRenderDoc(m_renderdocdll);

#if USE_D3D12_DYNAMIC_LIB
			bx::dlclose(m_dxgidll);
			bx::dlclose(m_d3d12dll);
			bx::dlclose(m_kernel32dll);
#endif // USE_D3D12_DYNAMIC_LIB
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Direct3D12;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			return BGFX_RENDERER_DIRECT3D12_NAME;
		}

		bool isDeviceRemoved() BX_OVERRIDE
		{
			return m_lost;
		}

		void flip(HMD& /*_hmd*/) BX_OVERRIDE
		{
			if (NULL != m_swapChain
			&&  !m_lost)
			{
				int64_t start = bx::getHPCounter();

				HRESULT hr = 0;
				uint32_t syncInterval = !!(m_resolution.m_flags & BGFX_RESET_VSYNC);
				uint32_t flags = 0 == syncInterval ? DXGI_PRESENT_RESTART : 0;
				for (uint32_t ii = 1, num = m_numWindows; ii < num && SUCCEEDED(hr); ++ii)
				{
					hr = m_frameBuffers[m_windows[ii].idx].m_swapChain->Present(syncInterval, flags);
				}

				if (SUCCEEDED(hr) )
				{
					m_cmd.finish(m_backBufferColorFence[(m_backBufferColorIdx-1) % m_scd.BufferCount]);
					hr = m_swapChain->Present(syncInterval, flags);
				}

				int64_t now = bx::getHPCounter();
				m_presentElapsed = now - start;

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

		void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem, uint16_t _flags) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags, false);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl) BX_OVERRIDE
		{
			VertexDecl& decl = m_vertexDecls[_handle.idx];
			bx::memCopy(&decl, &_decl, sizeof(VertexDecl) );
			dump(decl);
		}

		void destroyVertexDecl(VertexDeclHandle /*_handle*/) BX_OVERRIDE
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle, uint16_t _flags) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags, false);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].update(m_commandList, _offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) BX_OVERRIDE
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) BX_OVERRIDE
		{
			VertexDeclHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) BX_OVERRIDE
		{
			m_vertexBuffers[_handle.idx].update(m_commandList, _offset, bx::uint32_min(_size, _mem->size), _mem->data);
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
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void destroyProgram(ProgramHandle _handle) BX_OVERRIDE
		{
			m_program[_handle.idx].destroy();
		}

		void createTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags, uint8_t _skip) BX_OVERRIDE
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) BX_OVERRIDE
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) BX_OVERRIDE
		{
			m_textures[_handle.idx].update(m_commandList, _side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() BX_OVERRIDE
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip ) BX_OVERRIDE
		{
			const TextureD3D12& texture = m_textures[_handle.idx];

			D3D12_RESOURCE_DESC desc = texture.m_ptr->GetDesc();

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
			uint32_t numRows;
			uint64_t total;
			uint64_t srcPitch;
			m_device->GetCopyableFootprints(&desc
				, _mip
				, 1
				, 0
				, &layout
				, &numRows
				, &srcPitch
				, &total
				);

			ID3D12Resource* readback = createCommittedResource(m_device, HeapProperty::ReadBack, total);

			D3D12_BOX box;
			box.left   = 0;
			box.top    = 0;
			box.right  = texture.m_width;
			box.bottom = texture.m_height;
			box.front  = 0;
			box.back   = 1;

			D3D12_TEXTURE_COPY_LOCATION dstLocation = { readback,      D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
			D3D12_TEXTURE_COPY_LOCATION srcLocation = { texture.m_ptr, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {}         };
			m_commandList->CopyTextureRegion(&dstLocation, 0, 0, 0, &srcLocation, &box);

			finish();
			m_commandList = m_cmd.alloc();

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width >>_mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height>>_mip);
			uint8_t* src;
			readback->Map(0, NULL, (void**)&src);

			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat) );
			uint8_t* dst      = (uint8_t*)_data;
			uint32_t dstPitch = srcWidth*bpp/8;

			uint32_t pitch = bx::uint32_min(uint32_t(srcPitch), dstPitch);

			for (uint32_t yy = 0, height = srcHeight; yy < height; ++yy)
			{
				bx::memCopy(dst, src, pitch);

				src += srcPitch;
				dst += dstPitch;
			}

			readback->Unmap(0, NULL);

			DX_RELEASE(readback, 0);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips) BX_OVERRIDE
		{
			TextureD3D12& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width     = _width;
			tc.m_height    = _height;
			tc.m_depth     = 0;
			tc.m_numLayers = 1;
			tc.m_numMips   = _numMips;
			tc.m_format    = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc);

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) BX_OVERRIDE
		{
			BX_UNUSED(_handle, _ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) BX_OVERRIDE
		{
			BX_UNUSED(_handle);
			return 0;
		}

		void destroyTexture(TextureHandle _handle) BX_OVERRIDE
		{
			m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) BX_OVERRIDE
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
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

			uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type] * _num);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name, data);
		}

		void destroyUniform(UniformHandle _handle) BX_OVERRIDE
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) BX_OVERRIDE
		{
			BX_UNUSED(_handle);

			uint32_t idx = (m_backBufferColorIdx-1) % m_scd.BufferCount;
			m_cmd.finish(m_backBufferColorFence[idx]);
			ID3D12Resource* backBuffer = m_backBufferColor[idx];

			D3D12_RESOURCE_DESC desc = backBuffer->GetDesc();

			const uint32_t width  = (uint32_t)desc.Width;
			const uint32_t height = (uint32_t)desc.Height;

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
			uint32_t numRows;
			uint64_t total;
			uint64_t pitch;
			m_device->GetCopyableFootprints(&desc
				, 0
				, 1
				, 0
				, &layout
				, &numRows
				, &pitch
				, &total
				);

			ID3D12Resource* readback = createCommittedResource(m_device, HeapProperty::ReadBack, total);

			D3D12_BOX box;
			box.left   = 0;
			box.top    = 0;
			box.right  = width;
			box.bottom = height;
			box.front  = 0;
			box.back   = 1;

			setResourceBarrier(m_commandList, backBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_COPY_SOURCE);
			D3D12_TEXTURE_COPY_LOCATION dst = { readback,   D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
			D3D12_TEXTURE_COPY_LOCATION src = { backBuffer, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {}     };
			m_commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, &box);
			setResourceBarrier(m_commandList, backBuffer, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_PRESENT);
			finish();
			m_commandList = m_cmd.alloc();

			void* data;
			readback->Map(0, NULL, (void**)&data);
			bimg::imageSwizzleBgra8(
				  data
				, width
				, height
				, (uint32_t)pitch
				, data
				);
			g_callback->screenShot(_filePath
				, width
				, height
				, (uint32_t)pitch
				, data
				, (uint32_t)total
				, false
				);
			readback->Unmap(0, NULL);

			DX_RELEASE(readback, 0);
		}

		void updateViewName(uint8_t /*_id*/, const char* /*_name*/) BX_OVERRIDE
		{
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) BX_OVERRIDE
		{
			bx::memCopy(m_uniforms[_loc], _data, _size);
		}

		void setMarker(const char* /*_marker*/, uint32_t /*_size*/) BX_OVERRIDE
		{
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) BX_OVERRIDE
		{
			m_occlusionQuery.invalidate(_handle);
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) BX_OVERRIDE;

		void blitSetup(TextVideoMemBlitter& _blitter) BX_OVERRIDE
		{
			const uint32_t width  = getBufferWidth();
			const uint32_t height = getBufferHeight();

			FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
			setFrameBuffer(fbh, false);

			D3D12_VIEWPORT vp;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			vp.Width    = (float)width;
			vp.Height   = (float)height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			m_commandList->RSSetViewports(1, &vp);

			D3D12_RECT rc;
			rc.left   = 0;
			rc.top    = 0;
			rc.right  = width;
			rc.bottom = height;
			m_commandList->RSSetScissorRects(1, &rc);

			const uint64_t state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			ID3D12PipelineState* pso = getPipelineState(state
				, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT)
				, _blitter.m_vb->decl.idx
				, _blitter.m_program.idx
				, 0
				);
			m_commandList->SetPipelineState(pso);
			m_commandList->SetGraphicsRootSignature(m_rootSignature);

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

			PredefinedUniform& predefined = m_program[_blitter.m_program.idx].m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			D3D12_GPU_VIRTUAL_ADDRESS gpuAddress;
			commitShaderConstants(_blitter.m_program.idx, gpuAddress);

			ScratchBufferD3D12& scratchBuffer = m_scratchBuffer[m_backBufferColorIdx];
			ID3D12DescriptorHeap* heaps[] =
			{
				m_samplerAllocator.getHeap(),
				scratchBuffer.getHeap(),
			};
			m_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);
			m_commandList->SetGraphicsRootConstantBufferView(Rdt::CBV, gpuAddress);

			TextureD3D12& texture = m_textures[_blitter.m_texture.idx];
			uint32_t samplerFlags[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS] = { texture.m_flags & BGFX_TEXTURE_SAMPLER_BITS_MASK };
			uint16_t samplerStateIdx = getSamplerState(samplerFlags, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, NULL);
			m_commandList->SetGraphicsRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
			D3D12_GPU_DESCRIPTOR_HANDLE srvHandle;
			scratchBuffer.allocSrv(srvHandle, texture);
			m_commandList->SetGraphicsRootDescriptorTable(Rdt::SRV, srvHandle);

			VertexBufferD3D12& vb  = m_vertexBuffers[_blitter.m_vb->handle.idx];
			const VertexDecl& vertexDecl = m_vertexDecls[_blitter.m_vb->decl.idx];
			D3D12_VERTEX_BUFFER_VIEW viewDesc;
			viewDesc.BufferLocation = vb.m_gpuVA;
			viewDesc.StrideInBytes  = vertexDecl.m_stride;
			viewDesc.SizeInBytes    = vb.m_size;
			m_commandList->IASetVertexBuffers(0, 1, &viewDesc);

			const BufferD3D12& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			D3D12_INDEX_BUFFER_VIEW ibv;
			ibv.Format         = DXGI_FORMAT_R16_UINT;
			ibv.BufferLocation = ib.m_gpuVA;
			ibv.SizeInBytes    = ib.m_size;
			m_commandList->IASetIndexBuffer(&ibv);

			m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) BX_OVERRIDE
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers [_blitter.m_ib->handle.idx].update(m_commandList, 0, _numIndices*2, _blitter.m_ib->data);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(m_commandList, 0, numVertices*_blitter.m_decl.m_stride, _blitter.m_vb->data, true);

				m_commandList->DrawIndexedInstanced(_numIndices
					, 1
					, 0
					, 0
					, 0
					);
			}
		}

		void preReset()
		{
			finishAll();

			for (uint32_t ii = 0, num = m_scd.BufferCount; ii < num; ++ii)
			{
				DX_RELEASE(m_backBufferColor[ii], num-1-ii);
			}
			DX_RELEASE(m_backBufferDepthStencil, 0);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].preReset();
			}

			invalidateCache();

//			capturePreReset();
		}

		void postReset()
		{
			bx::memSet(m_backBufferColorFence, 0, sizeof(m_backBufferColorFence) );

			uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			for (uint32_t ii = 0, num = m_scd.BufferCount; ii < num; ++ii)
			{
				D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
				handle.ptr += ii * rtvDescriptorSize;
				DX_CHECK(m_swapChain->GetBuffer(ii
						, IID_ID3D12Resource
						, (void**)&m_backBufferColor[ii]
						) );
				m_device->CreateRenderTargetView(m_backBufferColor[ii], NULL, handle);
			}

			D3D12_RESOURCE_DESC resourceDesc;
			resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			resourceDesc.Alignment = 0;
			resourceDesc.Width     = bx::uint32_max(m_resolution.m_width,  1);
			resourceDesc.Height    = bx::uint32_max(m_resolution.m_height, 1);
			resourceDesc.DepthOrArraySize   = 1;
			resourceDesc.MipLevels          = 0;
			resourceDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
			resourceDesc.SampleDesc.Count   = 1;
			resourceDesc.SampleDesc.Quality = 0;
			resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resourceDesc.Flags  = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

			D3D12_CLEAR_VALUE clearValue;
			clearValue.Format = resourceDesc.Format;
			clearValue.DepthStencil.Depth   = 1.0f;
			clearValue.DepthStencil.Stencil = 0;

			m_backBufferDepthStencil = createCommittedResource(m_device, HeapProperty::Default, &resourceDesc, &clearValue);

			D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
			ZeroMemory(&dsvDesc, sizeof(dsvDesc) );
			dsvDesc.Format        = resourceDesc.Format;
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Flags         = D3D12_DSV_FLAGS(0)
// 				| D3D12_DSV_FLAG_READ_ONLY_DEPTH
// 				| D3D12_DSV_FLAG_READ_ONLY_DEPTH
				;

			m_device->CreateDepthStencilView(m_backBufferDepthStencil
				, &dsvDesc
				, m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart()
				);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}

			m_commandList = m_cmd.alloc();
//			capturePostReset();
		}

		void invalidateCache()
		{
			m_pipelineStateCache.invalidate();

			m_samplerStateCache.invalidate();
			m_samplerAllocator.reset();
		}

		void updateMsaa()
		{
			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				uint32_t msaa = s_checkMsaa[ii];

				D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS data;
				bx::memSet(&data, 0, sizeof(msaa) );
				data.Format = getBufferFormat();
				data.SampleCount = msaa;
				data.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
				HRESULT hr = m_device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &data, sizeof(data) );

data.NumQualityLevels = 0;

				if (SUCCEEDED(hr)
				&&  0 < data.NumQualityLevels)
				{
					s_msaa[ii].Count   = data.SampleCount;
					s_msaa[ii].Quality = data.NumQualityLevels - 1;
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
			if (!!(_resolution.m_flags & BGFX_RESET_MAXANISOTROPY) )
			{
				m_maxAnisotropy = D3D12_REQ_MAXANISOTROPY;
			}
			else
			{
				m_maxAnisotropy = 1;
			}

			bool depthClamp = !!(_resolution.m_flags & BGFX_RESET_DEPTH_CLAMP);

			if (m_depthClamp != depthClamp)
			{
				m_depthClamp = depthClamp;
				m_pipelineStateCache.invalidate();
			}

			const uint32_t maskFlags = ~(0
				| BGFX_RESET_HMD_RECENTER
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				| BGFX_RESET_SUSPEND
				);

			if (m_resolution.m_width            !=  _resolution.m_width
			||  m_resolution.m_height           !=  _resolution.m_height
			|| (m_resolution.m_flags&maskFlags) != (_resolution.m_flags&maskFlags) )
			{
				uint32_t flags = _resolution.m_flags & (~BGFX_RESET_INTERNAL_FORCE);

				bool resize = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK) == (_resolution.m_flags&BGFX_RESET_MSAA_MASK);

				m_resolution = _resolution;
				m_resolution.m_flags = flags;

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

				setBufferSize(_resolution.m_width, _resolution.m_height);

				preReset();

				BX_UNUSED(resize);
#if BX_PLATFORM_WINDOWS
				if (resize)
				{
					uint32_t nodeMask[] = { 1, 1, 1, 1 };
					BX_STATIC_ASSERT(BX_COUNTOF(m_backBufferColor) == BX_COUNTOF(nodeMask) );
					IUnknown* presentQueue[] ={ m_cmd.m_commandQueue, m_cmd.m_commandQueue, m_cmd.m_commandQueue, m_cmd.m_commandQueue };
					BX_STATIC_ASSERT(BX_COUNTOF(m_backBufferColor) == BX_COUNTOF(presentQueue) );

					DX_CHECK(m_swapChain->ResizeBuffers1(m_scd.BufferCount
							, m_scd.BufferDesc.Width
							, m_scd.BufferDesc.Height
							, m_scd.BufferDesc.Format
							, m_scd.Flags
							, nodeMask
							, presentQueue
							) );
				}
				else
#endif // BX_PLATFORM_WINDOWS
				{
					updateMsaa();
					m_scd.SampleDesc = s_msaa[(m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

					DX_RELEASE(m_swapChain, 0);

#if BX_PLATFORM_WINDOWS
					HRESULT hr;
					hr = m_factory->CreateSwapChain(m_cmd.m_commandQueue
							, &m_scd
							, reinterpret_cast<IDXGISwapChain**>(&m_swapChain)
							);
					BGFX_FATAL(SUCCEEDED(hr), bgfx::Fatal::UnableToInitialize, "Failed to create swap chain.");
#endif // BX_PLATFORM_WINDOWS
				}

				postReset();
			}

			return false;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags&BGFX_UNIFORM_FRAGMENTBIT)
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

		void commitShaderConstants(uint16_t _programIdx, D3D12_GPU_VIRTUAL_ADDRESS& _gpuAddress)
		{
			const ProgramD3D12& program = m_program[_programIdx];
			uint32_t total = bx::strideAlign(0
				+ program.m_vsh->m_size
				+ (NULL != program.m_fsh ? program.m_fsh->m_size : 0)
				, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT
				);
			uint8_t* data = (uint8_t*)m_scratchBuffer[m_backBufferColorIdx].allocCbv(_gpuAddress, total);

			{
				uint32_t size = program.m_vsh->m_size;
				bx::memCopy(data, m_vsScratch, size);
				data += size;

				m_vsChanges = 0;
			}

			if (NULL != program.m_fsh)
			{
				bx::memCopy(data, m_fsScratch, program.m_fsh->m_size);

				m_fsChanges = 0;
			}
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true)
		{
			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx)
			{
				const FrameBufferD3D12& frameBuffer = m_frameBuffers[m_fbh.idx];

				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
				{
					TextureD3D12& texture = m_textures[frameBuffer.m_texture[ii].idx];
					texture.setState(m_commandList, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
				}

				if (isValid(frameBuffer.m_depth) )
				{
					TextureD3D12& texture = m_textures[frameBuffer.m_depth.idx];
					const bool writeOnly  = 0 != (texture.m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
					if (!writeOnly)
					{
						texture.setState(m_commandList, D3D12_RESOURCE_STATE_DEPTH_READ);
					}
				}
			}

			if (!isValid(_fbh) )
			{
				m_rtvHandle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
				uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
				m_rtvHandle.ptr += m_backBufferColorIdx * rtvDescriptorSize;
				m_dsvHandle = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

				m_currentColor        = &m_rtvHandle;
				m_currentDepthStencil = &m_dsvHandle;
				m_commandList->OMSetRenderTargets(1, m_currentColor, true, m_currentDepthStencil);
			}
			else
			{
				const FrameBufferD3D12& frameBuffer = m_frameBuffers[_fbh.idx];

				if (0 < frameBuffer.m_num)
				{
					D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptor = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
					uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
					m_rtvHandle.ptr = rtvDescriptor.ptr + (BX_COUNTOF(m_backBufferColor) + _fbh.idx * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) * rtvDescriptorSize;
					m_currentColor  = &m_rtvHandle;
				}
				else
				{
					m_currentColor = NULL;
				}

				if (isValid(frameBuffer.m_depth) )
				{
					D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
					uint32_t dsvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
					m_dsvHandle.ptr = dsvDescriptor.ptr + (1 + _fbh.idx) * dsvDescriptorSize;
					m_currentDepthStencil = &m_dsvHandle;
				}
				else
				{
					m_currentDepthStencil = NULL;
				}

				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
				{
					TextureD3D12& texture = m_textures[frameBuffer.m_texture[ii].idx];
					texture.setState(m_commandList, D3D12_RESOURCE_STATE_RENDER_TARGET);
				}

				if (isValid(frameBuffer.m_depth) )
				{
					TextureD3D12& texture = m_textures[frameBuffer.m_depth.idx];
					texture.setState(m_commandList, D3D12_RESOURCE_STATE_DEPTH_WRITE);
				}

				m_commandList->OMSetRenderTargets(frameBuffer.m_num
												, m_currentColor
												, true
												, m_currentDepthStencil
												);
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void setBlendState(D3D12_BLEND_DESC& _desc, uint64_t _state, uint32_t _rgba = 0)
		{
			_desc.AlphaToCoverageEnable  = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);
			_desc.IndependentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

			D3D12_RENDER_TARGET_BLEND_DESC* drt = &_desc.RenderTarget[0];
			drt->BlendEnable   = !!(BGFX_STATE_BLEND_MASK & _state);
			drt->LogicOpEnable = false;

			{
				const uint32_t blend    = uint32_t( (_state & BGFX_STATE_BLEND_MASK         ) >> BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);

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
			}

			uint8_t writeMask = (_state & BGFX_STATE_ALPHA_WRITE)
					? D3D12_COLOR_WRITE_ENABLE_ALPHA
					: 0
					;
			writeMask |= (_state & BGFX_STATE_RGB_WRITE)
					? D3D12_COLOR_WRITE_ENABLE_RED
					| D3D12_COLOR_WRITE_ENABLE_GREEN
					| D3D12_COLOR_WRITE_ENABLE_BLUE
					: 0
					;

			drt->LogicOp = D3D12_LOGIC_OP_CLEAR;
			drt->RenderTargetWriteMask = writeMask;

			if (_desc.IndependentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii, rgba >>= 11)
				{
					drt = &_desc.RenderTarget[ii];
					drt->BlendEnable = 0 != (rgba & 0x7ff);
					drt->LogicOpEnable = false;

					const uint32_t src      = (rgba     ) & 0xf;
					const uint32_t dst      = (rgba >> 4) & 0xf;
					const uint32_t equation = (rgba >> 8) & 0x7;

					drt->SrcBlend       = s_blendFactor[src][0];
					drt->DestBlend      = s_blendFactor[dst][0];
					drt->BlendOp        = s_blendEquation[equation];

					drt->SrcBlendAlpha  = s_blendFactor[src][1];
					drt->DestBlendAlpha = s_blendFactor[dst][1];
					drt->BlendOpAlpha   = s_blendEquation[equation];

					drt->LogicOp = D3D12_LOGIC_OP_CLEAR;
					drt->RenderTargetWriteMask = writeMask;
				}
			}
			else
			{
				for (uint32_t ii = 1; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii)
				{
					bx::memCopy(&_desc.RenderTarget[ii], drt, sizeof(D3D12_RENDER_TARGET_BLEND_DESC) );
				}
			}
		}

		void setRasterizerState(D3D12_RASTERIZER_DESC& _desc, uint64_t _state, bool _wireframe = false)
		{
			const uint32_t cull = (_state&BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT;

			_desc.FillMode = _wireframe
				? D3D12_FILL_MODE_WIREFRAME
				: D3D12_FILL_MODE_SOLID
				;
			_desc.CullMode = s_cullMode[cull];
			_desc.FrontCounterClockwise = false;
			_desc.DepthBias             = 0;
			_desc.DepthBiasClamp        = 0.0f;
			_desc.SlopeScaledDepthBias  = 0.0f;
			_desc.DepthClipEnable       = !m_depthClamp;
			_desc.MultisampleEnable     = !!(_state&BGFX_STATE_MSAA);
			_desc.AntialiasedLineEnable = !!(_state&BGFX_STATE_LINEAA);
			_desc.ForcedSampleCount     = 0;
			_desc.ConservativeRaster    = !!(_state&BGFX_STATE_CONSERVATIVE_RASTER)
				? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON
				: D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
				;
		}

		void setDepthStencilState(D3D12_DEPTH_STENCIL_DESC& _desc, uint64_t _state, uint64_t _stencil = 0)
		{
			const uint32_t fstencil = unpackStencil(0, _stencil);

			bx::memSet(&_desc, 0, sizeof(_desc) );
			uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
			_desc.DepthEnable = 0 != func;
			_desc.DepthWriteMask = !!(BGFX_STATE_DEPTH_WRITE & _state)
				? D3D12_DEPTH_WRITE_MASK_ALL
				: D3D12_DEPTH_WRITE_MASK_ZERO
				;
			_desc.DepthFunc = s_cmpFunc[func];

			uint32_t bstencil = unpackStencil(1, _stencil);
			uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			_desc.StencilEnable    = 0 != _stencil;
			_desc.StencilReadMask  = (fstencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT;
			_desc.StencilWriteMask = 0xff;

			_desc.FrontFace.StencilFailOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT];
			_desc.FrontFace.StencilDepthFailOp = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT];
			_desc.FrontFace.StencilPassOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT];
			_desc.FrontFace.StencilFunc        = s_cmpFunc[(fstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];

			_desc.BackFace.StencilFailOp       = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT];
			_desc.BackFace.StencilDepthFailOp  = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT];
			_desc.BackFace.StencilPassOp       = s_stencilOp[(bstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT];
			_desc.BackFace.StencilFunc         = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];
		}

		uint32_t setInputLayout(D3D12_INPUT_ELEMENT_DESC* _vertexElements, const VertexDecl& _vertexDecl, const ProgramD3D12& _program, uint8_t _numInstanceData)
		{
			VertexDecl decl;
			bx::memCopy(&decl, &_vertexDecl, sizeof(VertexDecl) );
			const uint16_t* attrMask = _program.m_vsh->m_attrMask;

			for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
			{
				uint16_t mask = attrMask[ii];
				uint16_t attr = (decl.m_attributes[ii] & mask);
				decl.m_attributes[ii] = attr == 0 ? UINT16_MAX : attr == UINT16_MAX ? 0 : attr;
			}

			D3D12_INPUT_ELEMENT_DESC* elem = fillVertexDecl(_vertexElements, decl);
			uint32_t num = uint32_t(elem-_vertexElements);

			const D3D12_INPUT_ELEMENT_DESC inst = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };

			for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
			{
				uint32_t index = 7 - ii; // TEXCOORD7 = i_data0, TEXCOORD6 = i_data1, etc.

				uint32_t jj;
				D3D12_INPUT_ELEMENT_DESC* curr = _vertexElements;
				for (jj = 0; jj < num; ++jj)
				{
					curr = &_vertexElements[jj];
					if (0 == bx::strncmp(curr->SemanticName, "TEXCOORD")
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

				bx::memCopy(curr, &inst, sizeof(D3D12_INPUT_ELEMENT_DESC) );
				curr->InputSlot = 1;
				curr->SemanticIndex = index;
				curr->AlignedByteOffset = ii*16;
			}

			return uint32_t(elem-_vertexElements);
		}

		static void patchCb0(DxbcInstruction& _instruction, void* _userData)
		{
			union { void* ptr; uint32_t offset; } cast = { _userData };

			for (uint32_t ii = 0; ii < _instruction.numOperands; ++ii)
			{
				DxbcOperand& operand = _instruction.operand[ii];
				if (DxbcOperandType::ConstantBuffer == operand.type)
				{
					if (DxbcOperandAddrMode::Imm32 == operand.addrMode[0]
					&&  0 == operand.regIndex[0]
					&&  DxbcOperandAddrMode::Imm32 == operand.addrMode[1])
					{
						operand.regIndex[1] += cast.offset;
					}
				}
			}
		}

		ID3D12PipelineState* getPipelineState(uint16_t _programIdx)
		{
			ProgramD3D12& program = m_program[_programIdx];

			const uint32_t hash = program.m_vsh->m_hash;

			ID3D12PipelineState* pso = m_pipelineStateCache.find(hash);

			if (BX_LIKELY(NULL != pso) )
			{
				return pso;
			}

			D3D12_COMPUTE_PIPELINE_STATE_DESC desc;
			bx::memSet(&desc, 0, sizeof(desc) );

			desc.pRootSignature = m_rootSignature;

			desc.CS.pShaderBytecode = program.m_vsh->m_code->data;
			desc.CS.BytecodeLength  = program.m_vsh->m_code->size;

			DX_CHECK(m_device->CreateComputePipelineState(&desc
				, IID_ID3D12PipelineState
				, (void**)&pso
				) );
			m_pipelineStateCache.add(hash, pso);

			return pso;
		}

		ID3D12PipelineState* getPipelineState(uint64_t _state, uint64_t _stencil, uint16_t _declIdx, uint16_t _programIdx, uint8_t _numInstanceData)
		{
			ProgramD3D12& program = m_program[_programIdx];

			_state &= 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_MASK
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_PT_MASK
				;

			_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, BGFX_STENCIL_MASK);

			VertexDecl decl;
			bx::memCopy(&decl, &m_vertexDecls[_declIdx], sizeof(VertexDecl) );
			const uint16_t* attrMask = program.m_vsh->m_attrMask;

			for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
			{
				uint16_t mask = attrMask[ii];
				uint16_t attr = (decl.m_attributes[ii] & mask);
				decl.m_attributes[ii] = attr == 0 ? UINT16_MAX : attr == UINT16_MAX ? 0 : attr;
			}

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			murmur.add(program.m_vsh->m_hash);
			murmur.add(program.m_vsh->m_attrMask, sizeof(program.m_vsh->m_attrMask) );
			murmur.add(program.m_fsh->m_hash);
			murmur.add(m_vertexDecls[_declIdx].m_hash);
			murmur.add(decl.m_attributes, sizeof(decl.m_attributes) );
			murmur.add(m_fbh.idx);
			murmur.add(_numInstanceData);
			const uint32_t hash = murmur.end();

			ID3D12PipelineState* pso = m_pipelineStateCache.find(hash);

			if (NULL != pso)
			{
				return pso;
			}

			D3D12_GRAPHICS_PIPELINE_STATE_DESC desc;
			bx::memSet(&desc, 0, sizeof(desc) );

			desc.pRootSignature = m_rootSignature;

			desc.VS.pShaderBytecode = program.m_vsh->m_code->data;
			desc.VS.BytecodeLength  = program.m_vsh->m_code->size;

 			const Memory* temp = alloc(program.m_fsh->m_code->size);
 			bx::memSet(temp->data, 0, temp->size);
 			bx::MemoryReader rd(program.m_fsh->m_code->data, program.m_fsh->m_code->size);
 			bx::StaticMemoryBlockWriter wr(temp->data, temp->size);

			DxbcContext dxbc;
			bx::Error err;
			read(&rd, dxbc, &err);

			bool patchShader = !dxbc.shader.aon9;
			if (BX_ENABLED(BGFX_CONFIG_DEBUG)
			&&  patchShader)
			{
				union { uint32_t offset; void* ptr; } cast = { 0 };
				filter(dxbc.shader, dxbc.shader, patchCb0, cast.ptr);

				write(&wr, dxbc, &err);

				dxbcHash(temp->data + 20, temp->size - 20, temp->data + 4);

				patchShader = 0 == bx::memCmp(program.m_fsh->m_code->data, temp->data, 16);
				BX_CHECK(patchShader, "DXBC fragment shader patching error (ShaderHandle: %d).", program.m_fsh - m_shaders);

				if (!patchShader)
				{
					for (uint32_t ii = 20; ii < temp->size; ii += 16)
					{
						if (0 != bx::memCmp(&program.m_fsh->m_code->data[ii], &temp->data[ii], 16) )
						{
// 							bx::debugPrintfData(&program.m_fsh->m_code->data[ii], temp->size-ii, "");
// 							bx::debugPrintfData(&temp->data[ii], temp->size-ii, "");
							break;
						}
					}

					desc.PS.pShaderBytecode = program.m_fsh->m_code->data;
					desc.PS.BytecodeLength  = program.m_fsh->m_code->size;
				}
			}

			if (patchShader)
			{
				bx::memCopy(temp->data, program.m_fsh->m_code->data, program.m_fsh->m_code->size);

				bx::seek(&wr, 0, bx::Whence::Begin);
				union { uint32_t offset; void* ptr; } cast =
				{
					uint32_t(program.m_vsh->m_size)/16
				};
				filter(dxbc.shader, dxbc.shader, patchCb0, cast.ptr);
				write(&wr, dxbc, &err);
				dxbcHash(temp->data + 20, temp->size - 20, temp->data + 4);

				desc.PS.pShaderBytecode = temp->data;
				desc.PS.BytecodeLength  = temp->size;
			}
			else
			{
				desc.PS.pShaderBytecode = program.m_fsh->m_code->data;
				desc.PS.BytecodeLength  = program.m_fsh->m_code->size;
			}

			desc.DS.pShaderBytecode = NULL;
			desc.DS.BytecodeLength  = 0;

			desc.HS.pShaderBytecode = NULL;
			desc.HS.BytecodeLength  = 0;

			desc.GS.pShaderBytecode = NULL;
			desc.GS.BytecodeLength  = 0;

			desc.StreamOutput.pSODeclaration   = NULL;
			desc.StreamOutput.NumEntries       = 0;
			desc.StreamOutput.pBufferStrides   = NULL;
			desc.StreamOutput.NumStrides       = 0;
			desc.StreamOutput.RasterizedStream = 0;

			setBlendState(desc.BlendState, _state);
			desc.SampleMask = 1;
			setRasterizerState(desc.RasterizerState, _state);
			setDepthStencilState(desc.DepthStencilState, _state, _stencil);

			D3D12_INPUT_ELEMENT_DESC vertexElements[Attrib::Count + 1 + BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
			desc.InputLayout.NumElements = setInputLayout(vertexElements, m_vertexDecls[_declIdx], program, _numInstanceData);
			desc.InputLayout.pInputElementDescs = vertexElements;

			uint8_t primIndex = uint8_t( (_state&BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT);
			desc.PrimitiveTopologyType = s_primInfo[primIndex].m_topologyType;

			if (isValid(m_fbh) )
			{
				const FrameBufferD3D12& frameBuffer = m_frameBuffers[m_fbh.idx];
				desc.NumRenderTargets = frameBuffer.m_num;

				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
				{
					desc.RTVFormats[ii] = m_textures[frameBuffer.m_texture[ii].idx].m_srvd.Format;
				}

				if (isValid(frameBuffer.m_depth) )
				{
					desc.DSVFormat = s_textureFormat[m_textures[frameBuffer.m_depth.idx].m_textureFormat].m_fmtDsv;
				}
				else
				{
					desc.DSVFormat = DXGI_FORMAT_UNKNOWN;
				}
			}
			else
			{
				desc.NumRenderTargets = 1;
				desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
				desc.DSVFormat     = DXGI_FORMAT_D24_UNORM_S8_UINT;
			}

			desc.SampleDesc.Count   = 1;
			desc.SampleDesc.Quality = 0;

			uint32_t length = g_callback->cacheReadSize(hash);
			bool cached = length > 0;

			void* cachedData = NULL;

			if (cached)
			{
				cachedData = BX_ALLOC(g_allocator, length);
				if (g_callback->cacheRead(hash, cachedData, length) )
				{
					BX_TRACE("Loading cached PSO (size %d).", length);
					bx::MemoryReader reader(cachedData, length);

					desc.CachedPSO.pCachedBlob           = reader.getDataPtr();
					desc.CachedPSO.CachedBlobSizeInBytes = (size_t)reader.remaining();

					HRESULT hr = m_device->CreateGraphicsPipelineState(&desc
									, IID_ID3D12PipelineState
									, (void**)&pso
									);
					if (FAILED(hr) )
					{
						BX_TRACE("Failed to load cached PSO (HRESULT 0x%08x).", hr);
						bx::memSet(&desc.CachedPSO, 0, sizeof(desc.CachedPSO) );
					}
				}
			}

			if (NULL == pso)
			{
				DX_CHECK(m_device->CreateGraphicsPipelineState(&desc
						, IID_ID3D12PipelineState
						, (void**)&pso
						) );
			}
			m_pipelineStateCache.add(hash, pso);

			release(temp);

			ID3DBlob* blob;
			HRESULT hr = pso->GetCachedBlob(&blob);
			if (SUCCEEDED(hr) )
			{
				void* data = blob->GetBufferPointer();
				length = (uint32_t)blob->GetBufferSize();

				g_callback->cacheWrite(hash, data, length);

				DX_RELEASE(blob, 0);
			}

			if (NULL != cachedData)
			{
				BX_FREE(g_allocator, cachedData);
			}

			return pso;
		}

		uint16_t getSamplerState(const uint32_t* _flags, uint32_t _num, const float _palette[][4])
		{
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_flags, _num * sizeof(uint32_t) );
			uint32_t hash = murmur.end();

			uint16_t sampler = m_samplerStateCache.find(hash);
			if (UINT16_MAX == sampler)
			{
				sampler = m_samplerAllocator.alloc(_flags, _num, _palette);
				m_samplerStateCache.add(hash, sampler);
			}

			return sampler;
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		DXGI_FORMAT getBufferFormat()
		{
#if BX_PLATFORM_WINDOWS
			return m_scd.BufferDesc.Format;
#else
			return m_scd.Format;
#endif
		}

		uint32_t getBufferWidth()
		{
#if BX_PLATFORM_WINDOWS
			return m_scd.BufferDesc.Width;
#else
			return m_scd.Width;
#endif
		}

		uint32_t getBufferHeight()
		{
#if BX_PLATFORM_WINDOWS
			return m_scd.BufferDesc.Height;
#else
			return m_scd.Height;
#endif
		}

		void setBufferSize(uint32_t _width, uint32_t _height)
		{
#if BX_PLATFORM_WINDOWS
			m_scd.BufferDesc.Width  = _width;
			m_scd.BufferDesc.Height = _height;
#else
			m_scd.Width  = _width;
			m_scd.Height = _height;
#endif
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
				case UniformType::_uniform|BGFX_UNIFORM_FRAGMENTBIT: \
						{ \
							setShaderUniform(uint8_t(type), loc, data, num); \
						} \
						break;

				switch ( (uint32_t)type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3|BGFX_UNIFORM_FRAGMENTBIT:
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

		void clear(const Clear& _clear, const float _palette[][4], const D3D12_RECT* _rect = NULL, uint32_t _num = 0)
		{
			if (isValid(m_fbh) )
			{
				FrameBufferD3D12& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.clear(m_commandList, _clear, _palette);
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
							m_commandList->ClearRenderTargetView(*m_currentColor
								, _palette[index]
								, _num
								, _rect
								);
						}
					}
					else
					{
						float frgba[4] =
						{
							_clear.m_index[0] * 1.0f / 255.0f,
							_clear.m_index[1] * 1.0f / 255.0f,
							_clear.m_index[2] * 1.0f / 255.0f,
							_clear.m_index[3] * 1.0f / 255.0f,
						};
						m_commandList->ClearRenderTargetView(*m_currentColor
							, frgba
							, _num
							, _rect
							);
					}
				}

				if (NULL != m_currentDepthStencil
				&& (BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL) & _clear.m_flags)
				{
					uint32_t flags = 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH  ) ? D3D12_CLEAR_FLAG_DEPTH   : 0;
					flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL) ? D3D12_CLEAR_FLAG_STENCIL : 0;

					m_commandList->ClearDepthStencilView(*m_currentDepthStencil
						, D3D12_CLEAR_FLAGS(flags)
						, _clear.m_depth
						, _clear.m_stencil
						, _num
						, _rect
						);
				}
			}
		}

		void clearQuad(const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferD3D12& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = getBufferWidth();
				height = getBufferHeight();
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
				D3D12_RECT rect;
				rect.left   = _rect.m_x;
				rect.top    = _rect.m_y;
				rect.right  = _rect.m_x + _rect.m_width;
				rect.bottom = _rect.m_y + _rect.m_height;
				clear(_clear, _palette, &rect, 1);
			}
		}

		uint64_t kick()
		{
			uint64_t fence = m_cmd.kick();
			m_commandList = m_cmd.alloc();
			return fence;
		}

		void finish()
		{
			m_cmd.kick();
			m_cmd.finish();
			m_commandList = NULL;
		}

		void finishAll()
		{
			uint64_t fence = m_cmd.kick();
			m_cmd.finish(fence, true);
			m_commandList = NULL;
		}

		void* m_kernel32dll;
		void* m_d3d12dll;
		void* m_dxgidll;
		void* m_renderdocdll;

		D3D_FEATURE_LEVEL m_featureLevel;

		D3D_DRIVER_TYPE m_driverType;
		DXGI_ADAPTER_DESC m_adapterDesc;
		D3D12_FEATURE_DATA_ARCHITECTURE m_architecture;
		D3D12_FEATURE_DATA_D3D12_OPTIONS m_options;

#if BX_PLATFORM_WINDOWS
		IDXGIAdapter3*   m_adapter;
		IDXGIFactory4*   m_factory;
		IDXGISwapChain3* m_swapChain;
		ID3D12InfoQueue* m_infoQueue;
#else
		IDXGIAdapter*    m_adapter;
		IDXGIFactory2*   m_factory;
		IDXGISwapChain1* m_swapChain;
#endif // BX_PLATFORM_WINDOWS

		int64_t m_presentElapsed;
		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		ID3D12Device*       m_device;
		TimerQueryD3D12     m_gpuTimer;
		OcclusionQueryD3D12 m_occlusionQuery;

		ID3D12DescriptorHeap* m_rtvDescriptorHeap;
		ID3D12DescriptorHeap* m_dsvDescriptorHeap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_rtvHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE* m_currentColor;
		D3D12_CPU_DESCRIPTOR_HANDLE* m_currentDepthStencil;
		ID3D12Resource* m_backBufferColor[4];
		uint64_t m_backBufferColorFence[4];
		ID3D12Resource* m_backBufferDepthStencil;

		ScratchBufferD3D12 m_scratchBuffer[4];
		DescriptorAllocatorD3D12 m_samplerAllocator;

		ID3D12RootSignature* m_rootSignature;

		CommandQueueD3D12 m_cmd;
		BatchD3D12 m_batch;
		ID3D12GraphicsCommandList* m_commandList;

		Resolution m_resolution;
		bool m_wireframe;
		bool m_lost;

#if BX_PLATFORM_WINDOWS
		DXGI_SWAP_CHAIN_DESC m_scd;
#else
		DXGI_SWAP_CHAIN_DESC1 m_scd;
#endif // BX_PLATFORM_WINDOWS
		uint32_t m_maxAnisotropy;
		bool m_depthClamp;

		BufferD3D12 m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferD3D12 m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderD3D12 m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramD3D12 m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureD3D12 m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		FrameBufferD3D12 m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		StateCacheT<ID3D12PipelineState> m_pipelineStateCache;
		StateCache m_samplerStateCache;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64<<10];
		uint8_t m_vsScratch[64<<10];
		uint32_t m_fsChanges;
		uint32_t m_vsChanges;

		FrameBufferHandle m_fbh;
		uint32_t m_backBufferColorIdx;
		bool m_rtMsaa;
	};

	static RendererContextD3D12* s_renderD3D12;

	RendererContextI* rendererCreate()
	{
		s_renderD3D12 = BX_NEW(g_allocator, RendererContextD3D12);
		if (!s_renderD3D12->init() )
		{
			BX_DELETE(g_allocator, s_renderD3D12);
			s_renderD3D12 = NULL;
		}
		return s_renderD3D12;
	}

	void rendererDestroy()
	{
		s_renderD3D12->shutdown();
		BX_DELETE(g_allocator, s_renderD3D12);
		s_renderD3D12 = NULL;
	}

	void ScratchBufferD3D12::create(uint32_t _size, uint32_t _maxDescriptors)
	{
		m_size = _size;

		ID3D12Device* device = s_renderD3D12->m_device;

		m_incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = _maxDescriptors;
		desc.Type     = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.Flags    = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 1;
		DX_CHECK(device->CreateDescriptorHeap(&desc
				, IID_ID3D12DescriptorHeap
				, (void**)&m_heap
				) );

		m_upload = createCommittedResource(device, HeapProperty::Upload, desc.NumDescriptors * 1024);
		m_gpuVA  = m_upload->GetGPUVirtualAddress();
		m_upload->Map(0, NULL, (void**)&m_data);

		reset(m_gpuHandle);
	}

	void ScratchBufferD3D12::destroy()
	{
		m_upload->Unmap(0, NULL);

		DX_RELEASE(m_upload, 0);
		DX_RELEASE(m_heap, 0);
	}

	void ScratchBufferD3D12::reset(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle)
	{
		m_pos = 0;
		m_cpuHandle = m_heap->GetCPUDescriptorHandleForHeapStart();
		m_gpuHandle = m_heap->GetGPUDescriptorHandleForHeapStart();
		_gpuHandle = m_gpuHandle;
	}

	void* ScratchBufferD3D12::allocCbv(D3D12_GPU_VIRTUAL_ADDRESS& _gpuAddress, uint32_t _size)
	{
		_gpuAddress = m_gpuVA + m_pos;
		void* data = &m_data[m_pos];

		m_pos += BX_ALIGN_256(_size);

// 		D3D12_CONSTANT_BUFFER_VIEW_DESC desc;
// 		desc.BufferLocation = _gpuAddress;
// 		desc.SizeInBytes    = _size;
// 		ID3D12Device* device = s_renderD3D12->m_device;
// 		device->CreateConstantBufferView(&desc
// 			, m_cpuHandle
// 			);
// 		m_cpuHandle.ptr += m_incrementSize;
// 		m_gpuHandle.ptr += m_incrementSize;

		return data;
	}

	void ScratchBufferD3D12::allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, TextureD3D12& _texture, uint8_t _mip)
	{
		ID3D12Device* device = s_renderD3D12->m_device;

		D3D12_SHADER_RESOURCE_VIEW_DESC tmpSrvd;
		D3D12_SHADER_RESOURCE_VIEW_DESC* srvd = &_texture.m_srvd;
		if (0 != _mip)
		{
			bx::memCopy(&tmpSrvd, srvd, sizeof(tmpSrvd) );
			srvd = &tmpSrvd;

			switch (_texture.m_srvd.ViewDimension)
			{
			default:
			case D3D12_SRV_DIMENSION_TEXTURE2D:
				srvd->Texture2D.MostDetailedMip = _mip;
				srvd->Texture2D.MipLevels       = 1;
				srvd->Texture2D.PlaneSlice      = 0;
				srvd->Texture2D.ResourceMinLODClamp = 0;
				break;

			case D3D12_SRV_DIMENSION_TEXTURECUBE:
				srvd->TextureCube.MostDetailedMip = _mip;
				srvd->TextureCube.MipLevels       = 1;
				srvd->TextureCube.ResourceMinLODClamp = 0;
				break;

			case D3D12_SRV_DIMENSION_TEXTURE3D:
				srvd->Texture3D.MostDetailedMip = _mip;
				srvd->Texture3D.MipLevels       = 1;
				srvd->Texture3D.ResourceMinLODClamp = 0;
				break;
			}
		}

		device->CreateShaderResourceView(_texture.m_ptr
			, srvd
			, m_cpuHandle
			);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBufferD3D12::allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, TextureD3D12& _texture, uint8_t _mip)
	{
		ID3D12Device* device = s_renderD3D12->m_device;

		D3D12_UNORDERED_ACCESS_VIEW_DESC tmpUavd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC* uavd = &_texture.m_uavd;

		if (0 != _mip)
		{
			bx::memCopy(&tmpUavd, uavd, sizeof(tmpUavd) );
			uavd = &tmpUavd;

			switch (_texture.m_uavd.ViewDimension)
			{
			default:
			case D3D12_UAV_DIMENSION_TEXTURE2D:
				uavd->Texture2D.MipSlice   = _mip;
				uavd->Texture2D.PlaneSlice = 0;
				break;
			case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
				uavd->Texture2DArray.MipSlice   = _mip;
				uavd->Texture2DArray.PlaneSlice = 0;
				break;

			case D3D12_UAV_DIMENSION_TEXTURE3D:
				uavd->Texture3D.MipSlice = _mip;
				break;
			}
		}

		device->CreateUnorderedAccessView(_texture.m_ptr
			, NULL
			, uavd
			, m_cpuHandle
			);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBufferD3D12::allocSrv(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, BufferD3D12& _buffer)
	{
		ID3D12Device* device = s_renderD3D12->m_device;
		device->CreateShaderResourceView(_buffer.m_ptr
			, &_buffer.m_srvd
			, m_cpuHandle
			);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBufferD3D12::allocUav(D3D12_GPU_DESCRIPTOR_HANDLE& _gpuHandle, BufferD3D12& _buffer)
	{
		ID3D12Device* device = s_renderD3D12->m_device;
		device->CreateUnorderedAccessView(_buffer.m_ptr
			, NULL
			, &_buffer.m_uavd
			, m_cpuHandle
			);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void DescriptorAllocatorD3D12::create(D3D12_DESCRIPTOR_HEAP_TYPE _type, uint16_t _maxDescriptors, uint16_t _numDescriptorsPerBlock)
	{
		m_handleAlloc = bx::createHandleAlloc(g_allocator, _maxDescriptors);
		m_numDescriptorsPerBlock = _numDescriptorsPerBlock;

		ID3D12Device* device = s_renderD3D12->m_device;

		m_incrementSize = device->GetDescriptorHandleIncrementSize(_type);

		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = _maxDescriptors;
		desc.Type     = _type;
		desc.Flags    = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 1;
		DX_CHECK(device->CreateDescriptorHeap(&desc
				, IID_ID3D12DescriptorHeap
				, (void**)&m_heap
				) );

		m_cpuHandle = m_heap->GetCPUDescriptorHandleForHeapStart();
		m_gpuHandle = m_heap->GetGPUDescriptorHandleForHeapStart();
	}

	void DescriptorAllocatorD3D12::destroy()
	{
		bx::destroyHandleAlloc(g_allocator, m_handleAlloc);

		DX_RELEASE(m_heap, 0);
	}

	uint16_t DescriptorAllocatorD3D12::alloc(ID3D12Resource* _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC* _desc)
	{
		uint16_t idx = m_handleAlloc->alloc();

		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = { m_cpuHandle.ptr + idx * m_incrementSize };

		ID3D12Device* device = s_renderD3D12->m_device;
		device->CreateShaderResourceView(_ptr
			, _desc
			, cpuHandle
			);

		return idx;
	}

	uint16_t DescriptorAllocatorD3D12::alloc(const uint32_t* _flags, uint32_t _num, const float _palette[][4])
	{
		uint16_t idx = m_handleAlloc->alloc();

		ID3D12Device* device   = s_renderD3D12->m_device;
		uint32_t maxAnisotropy = s_renderD3D12->m_maxAnisotropy;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			uint32_t flags = _flags[ii];

			const uint32_t cmpFunc   = (flags&BGFX_TEXTURE_COMPARE_MASK)>>BGFX_TEXTURE_COMPARE_SHIFT;
			const uint8_t  minFilter = s_textureFilter[0][(flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
			const uint8_t  magFilter = s_textureFilter[1][(flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];
			const uint8_t  mipFilter = s_textureFilter[2][(flags&BGFX_TEXTURE_MIP_MASK)>>BGFX_TEXTURE_MIP_SHIFT];
			const uint8_t  filter    = 0 == cmpFunc ? 0 : D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

			D3D12_SAMPLER_DESC sd;
			sd.Filter   = (D3D12_FILTER)(filter|minFilter|magFilter|mipFilter);
			sd.AddressU = s_textureAddress[(flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT];
			sd.AddressV = s_textureAddress[(flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT];
			sd.AddressW = s_textureAddress[(flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT];
			sd.MipLODBias     = 0.0f;
			sd.MaxAnisotropy  = maxAnisotropy;
			sd.ComparisonFunc = 0 == cmpFunc ? D3D12_COMPARISON_FUNC_NEVER : s_cmpFunc[cmpFunc];

			uint32_t index = (flags & BGFX_TEXTURE_BORDER_COLOR_MASK) >> BGFX_TEXTURE_BORDER_COLOR_SHIFT;

			if (NULL != _palette
			&&  needBorderColor(flags) )
			{
				const float* rgba = _palette[index];
				sd.BorderColor[0] = rgba[0];
				sd.BorderColor[1] = rgba[1];
				sd.BorderColor[2] = rgba[2];
				sd.BorderColor[3] = rgba[3];
			}
			else
			{
				sd.BorderColor[0] = 0.0f;
				sd.BorderColor[1] = 0.0f;
				sd.BorderColor[2] = 0.0f;
				sd.BorderColor[3] = 0.0f;
			}
			sd.MinLOD   = 0;
			sd.MaxLOD   = D3D12_FLOAT32_MAX;

			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle =
			{
				m_cpuHandle.ptr + (idx * m_numDescriptorsPerBlock + ii) * m_incrementSize
			};

			device->CreateSampler(&sd, cpuHandle);
		}

		return idx;
	}

	void DescriptorAllocatorD3D12::free(uint16_t _idx)
	{
		m_handleAlloc->free(_idx);
	}

	void DescriptorAllocatorD3D12::reset()
	{
		uint16_t max = m_handleAlloc->getMaxHandles();
		bx::destroyHandleAlloc(g_allocator, m_handleAlloc);
		m_handleAlloc = bx::createHandleAlloc(g_allocator, max);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorAllocatorD3D12::get(uint16_t _idx)
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = { m_gpuHandle.ptr + _idx * m_numDescriptorsPerBlock * m_incrementSize };
		return gpuHandle;
	}

	void CommandQueueD3D12::init(ID3D12Device* _device)
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type     = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 1;
		DX_CHECK(_device->CreateCommandQueue(&queueDesc
				, IID_ID3D12CommandQueue
				, (void**)&m_commandQueue
				) );

		m_completedFence = 0;
		m_currentFence   = 0;
		DX_CHECK(_device->CreateFence(0
				, D3D12_FENCE_FLAG_NONE
				, IID_ID3D12Fence
				, (void**)&m_fence
				) );

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_commandList); ++ii)
		{
			DX_CHECK(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
					, IID_ID3D12CommandAllocator
					, (void**)&m_commandList[ii].m_commandAllocator
					) );

			DX_CHECK(_device->CreateCommandList(0
					, D3D12_COMMAND_LIST_TYPE_DIRECT
					, m_commandList[ii].m_commandAllocator
					, NULL
					, IID_ID3D12GraphicsCommandList
					, (void**)&m_commandList[ii].m_commandList
					) );

			DX_CHECK(m_commandList[ii].m_commandList->Close() );
		}
	}

	void CommandQueueD3D12::shutdown()
	{
		finish(UINT64_MAX, true);

		DX_RELEASE(m_fence, 0);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_commandList); ++ii)
		{
			DX_RELEASE(m_commandList[ii].m_commandAllocator, 0);
			DX_RELEASE(m_commandList[ii].m_commandList, 0);
		}

		DX_RELEASE(m_commandQueue, 0);
	}

	ID3D12GraphicsCommandList* CommandQueueD3D12::alloc()
	{
		while (0 == m_control.reserve(1) )
		{
			consume();
		}

		CommandList& commandList = m_commandList[m_control.m_current];
		DX_CHECK(commandList.m_commandAllocator->Reset() );
		DX_CHECK(commandList.m_commandList->Reset(commandList.m_commandAllocator, NULL) );
		return commandList.m_commandList;
	}

	uint64_t CommandQueueD3D12::kick()
	{
		CommandList& commandList = m_commandList[m_control.m_current];
		DX_CHECK(commandList.m_commandList->Close() );

		ID3D12CommandList* commandLists[] = { commandList.m_commandList };
		m_commandQueue->ExecuteCommandLists(BX_COUNTOF(commandLists), commandLists);

		commandList.m_event = CreateEventExA(NULL, NULL, 0, EVENT_ALL_ACCESS);
		const uint64_t fence = m_currentFence++;
		m_commandQueue->Signal(m_fence, fence);
		m_fence->SetEventOnCompletion(fence, commandList.m_event);

		m_control.commit(1);

		return fence;
	}

	void CommandQueueD3D12::finish(uint64_t _waitFence, bool _finishAll)
	{
		while (0 < m_control.available() )
		{
			consume();

			if (!_finishAll
			&&  _waitFence <= m_completedFence)
			{
				return;
			}
		}

		BX_CHECK(0 == m_control.available(), "");
	}

	bool CommandQueueD3D12::tryFinish(uint64_t _waitFence)
	{
		if (0 < m_control.available() )
		{
			if (consume(0)
			&& _waitFence <= m_completedFence)
			{
				return true;
			}
		}

		return false;
	}

	void CommandQueueD3D12::release(ID3D12Resource* _ptr)
	{
		m_release[m_control.m_current].push_back(_ptr);
	}

	bool CommandQueueD3D12::consume(uint32_t _ms)
	{
		CommandList& commandList = m_commandList[m_control.m_read];
		if (WAIT_OBJECT_0 == WaitForSingleObject(commandList.m_event, _ms) )
		{
			CloseHandle(commandList.m_event);
			commandList.m_event = NULL;
			m_completedFence = m_fence->GetCompletedValue();
			m_commandQueue->Wait(m_fence, m_completedFence);

			ResourceArray& ra = m_release[m_control.m_read];
			for (ResourceArray::iterator it = ra.begin(), itEnd = ra.end(); it != itEnd; ++it)
			{
				DX_RELEASE(*it, 0);
			}
			ra.clear();

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void BatchD3D12::create(uint32_t _maxDrawPerBatch)
	{
		m_maxDrawPerBatch = _maxDrawPerBatch;
		setSeqMode(false);
		setIndirectMode(true);

		ID3D12Device* device = s_renderD3D12->m_device;
		ID3D12RootSignature* rootSignature = s_renderD3D12->m_rootSignature;

		D3D12_INDIRECT_ARGUMENT_DESC drawArgDesc[] =
		{
			{ D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT_BUFFER_VIEW, { { Rdt::CBV } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW,   { { 0        } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW,   { { 1        } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_DRAW,                 { { 0        } } },
		};

		D3D12_COMMAND_SIGNATURE_DESC drawCommandSignature =
		{
			sizeof(DrawIndirectCommand),
			BX_COUNTOF(drawArgDesc),
			drawArgDesc,
			1,
		};

		DX_CHECK(device->CreateCommandSignature(&drawCommandSignature
				, rootSignature
				, IID_ID3D12CommandSignature
				, (void**)&m_commandSignature[Draw]
				) );

		D3D12_INDIRECT_ARGUMENT_DESC drawIndexedArgDesc[] =
		{
			{ D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT_BUFFER_VIEW, { { Rdt::CBV } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW,   { { 0        } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW,   { { 1        } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_INDEX_BUFFER_VIEW,    { { 0        } } },
			{ D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED,         { { 0        } } },
		};

		D3D12_COMMAND_SIGNATURE_DESC drawIndexedCommandSignature =
		{
			sizeof(DrawIndexedIndirectCommand),
			BX_COUNTOF(drawIndexedArgDesc),
			drawIndexedArgDesc,
			1,
		};

		DX_CHECK(device->CreateCommandSignature(&drawIndexedCommandSignature
				, rootSignature
				, IID_ID3D12CommandSignature
				, (void**)&m_commandSignature[DrawIndexed]
				) );

		m_cmds[Draw       ] = BX_ALLOC(g_allocator, m_maxDrawPerBatch*sizeof(DrawIndirectCommand) );
		m_cmds[DrawIndexed] = BX_ALLOC(g_allocator, m_maxDrawPerBatch*sizeof(DrawIndexedIndirectCommand) );

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_indirect); ++ii)
		{
			m_indirect[ii].create(m_maxDrawPerBatch*sizeof(DrawIndexedIndirectCommand)
				, NULL
				, BGFX_BUFFER_DRAW_INDIRECT
				, false
				, sizeof(DrawIndexedIndirectCommand)
				);
		}
	}

	void BatchD3D12::destroy()
	{
		BX_FREE(g_allocator, m_cmds[0]);
		BX_FREE(g_allocator, m_cmds[1]);

		DX_RELEASE(m_commandSignature[0], 0);
		DX_RELEASE(m_commandSignature[1], 0);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_indirect); ++ii)
		{
			m_indirect[ii].destroy();
		}
	}

	template<typename Ty>
	Ty& BatchD3D12::getCmd(Enum _type)
	{
		uint32_t index = m_num[_type];
		BX_CHECK(index < m_maxDrawPerBatch, "Memory corruption...");
		m_num[_type]++;
		Ty* cmd = &reinterpret_cast<Ty*>(m_cmds[_type])[index];
		return *cmd;
	}

	uint32_t BatchD3D12::draw(ID3D12GraphicsCommandList* _commandList, D3D12_GPU_VIRTUAL_ADDRESS _cbv, const RenderDraw& _draw)
	{
		Enum type = Enum(!!isValid(_draw.m_indexBuffer) );

		VertexBufferD3D12& vb = s_renderD3D12->m_vertexBuffers[_draw.m_stream[0].m_handle.idx];
		vb.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);

		uint16_t declIdx = !isValid(vb.m_decl) ? _draw.m_stream[0].m_decl.idx : vb.m_decl.idx;
		const VertexDecl& vertexDecl = s_renderD3D12->m_vertexDecls[declIdx];
		uint32_t numIndices = 0;

		if (Draw == type)
		{
			const uint32_t numVertices = UINT32_MAX == _draw.m_numVertices
				? vb.m_size / vertexDecl.m_stride
				: _draw.m_numVertices
				;

			DrawIndirectCommand& cmd = getCmd<DrawIndirectCommand>(Draw);
			cmd.cbv = _cbv;
			cmd.vbv[0].BufferLocation = vb.m_gpuVA;
			cmd.vbv[0].StrideInBytes  = vertexDecl.m_stride;
			cmd.vbv[0].SizeInBytes    = vb.m_size;
			if (isValid(_draw.m_instanceDataBuffer) )
			{
				VertexBufferD3D12& inst = s_renderD3D12->m_vertexBuffers[_draw.m_instanceDataBuffer.idx];
				inst.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
				cmd.vbv[1].BufferLocation = inst.m_gpuVA + _draw.m_instanceDataOffset;
				cmd.vbv[1].StrideInBytes  = _draw.m_instanceDataStride;
				cmd.vbv[1].SizeInBytes    = _draw.m_numInstances * _draw.m_instanceDataStride;
			}
			else
			{
				bx::memSet(&cmd.vbv[1], 0, sizeof(cmd.vbv[1]) );
			}
			cmd.draw.InstanceCount = _draw.m_numInstances;
			cmd.draw.VertexCountPerInstance = numVertices;
			cmd.draw.StartVertexLocation    = _draw.m_stream[0].m_startVertex;
			cmd.draw.StartInstanceLocation  = 0;
		}
		else
		{
			BufferD3D12& ib = s_renderD3D12->m_indexBuffers[_draw.m_indexBuffer.idx];
			ib.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);

			const bool hasIndex16 = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32);
			const uint32_t indexSize = hasIndex16 ? 2 : 4;

			numIndices = UINT32_MAX == _draw.m_numIndices
				? ib.m_size / indexSize
				: _draw.m_numIndices
				;

			DrawIndexedIndirectCommand& cmd = getCmd<DrawIndexedIndirectCommand>(DrawIndexed);
			cmd.cbv = _cbv;
			cmd.ibv.BufferLocation = ib.m_gpuVA;
			cmd.ibv.SizeInBytes    = ib.m_size;
			cmd.ibv.Format = hasIndex16
				? DXGI_FORMAT_R16_UINT
				: DXGI_FORMAT_R32_UINT
				;
			cmd.vbv[0].BufferLocation = vb.m_gpuVA;
			cmd.vbv[0].StrideInBytes  = vertexDecl.m_stride;
			cmd.vbv[0].SizeInBytes    = vb.m_size;
			if (isValid(_draw.m_instanceDataBuffer) )
			{
				VertexBufferD3D12& inst = s_renderD3D12->m_vertexBuffers[_draw.m_instanceDataBuffer.idx];
				inst.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
				cmd.vbv[1].BufferLocation = inst.m_gpuVA + _draw.m_instanceDataOffset;
				cmd.vbv[1].StrideInBytes  = _draw.m_instanceDataStride;
				cmd.vbv[1].SizeInBytes    = _draw.m_numInstances * _draw.m_instanceDataStride;
			}
			else
			{
				bx::memSet(&cmd.vbv[1], 0, sizeof(cmd.vbv[1]) );
			}
			cmd.drawIndexed.IndexCountPerInstance = numIndices;
			cmd.drawIndexed.InstanceCount = _draw.m_numInstances;
			cmd.drawIndexed.StartIndexLocation = _draw.m_startIndex;
			cmd.drawIndexed.BaseVertexLocation = _draw.m_stream[0].m_startVertex;
			cmd.drawIndexed.StartInstanceLocation = 0;
		}

		if (BX_UNLIKELY(m_flushPerBatch == m_num[type]) )
		{
			flush(_commandList, type);
		}

		return numIndices;
	}

	static const uint32_t s_indirectCommandSize[] =
	{
		sizeof(BatchD3D12::DrawIndirectCommand),
		sizeof(BatchD3D12::DrawIndexedIndirectCommand),
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_indirectCommandSize) == BatchD3D12::Count);

	void BatchD3D12::flush(ID3D12GraphicsCommandList* _commandList, Enum _type)
	{
		uint32_t num = m_num[_type];
		if (0 != num)
		{
			m_num[_type] = 0;

			if (m_minIndirect < num)
			{
				m_stats.m_numIndirect[_type]++;

				BufferD3D12& indirect = m_indirect[m_currIndirect++];
				m_currIndirect %= BX_COUNTOF(m_indirect);

				indirect.update(_commandList, 0, num*s_indirectCommandSize[_type], m_cmds[_type]);

				_commandList->ExecuteIndirect(m_commandSignature[_type]
					, num
					, indirect.m_ptr
					, 0
					, NULL
					, 0
					);
			}
			else
			{
				m_stats.m_numImmediate[_type]++;

				if (Draw == _type)
				{
					const DrawIndirectCommand* cmds = reinterpret_cast<DrawIndirectCommand*>(m_cmds[_type]);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						const DrawIndirectCommand& cmd = cmds[ii];
						if (m_current.cbv != cmd.cbv)
						{
							m_current.cbv = cmd.cbv;
							_commandList->SetGraphicsRootConstantBufferView(Rdt::CBV, cmd.cbv);
						}

						if (0 != bx::memCmp(m_current.vbv, cmd.vbv, sizeof(cmd.vbv) ) )
						{
							bx::memCopy(m_current.vbv, cmd.vbv, sizeof(cmd.vbv) );
							_commandList->IASetVertexBuffers(0
								, 0 == cmd.vbv[1].BufferLocation ? 1 : 2
								, cmd.vbv
								);
						}

						_commandList->DrawInstanced(
							  cmd.draw.VertexCountPerInstance
							, cmd.draw.InstanceCount
							, cmd.draw.StartVertexLocation
							, cmd.draw.StartInstanceLocation
							);
					}
				}
				else
				{
					const DrawIndexedIndirectCommand* cmds = reinterpret_cast<DrawIndexedIndirectCommand*>(m_cmds[_type]);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						const DrawIndexedIndirectCommand& cmd = cmds[ii];
						if (m_current.cbv != cmd.cbv)
						{
							m_current.cbv = cmd.cbv;
							_commandList->SetGraphicsRootConstantBufferView(Rdt::CBV, cmd.cbv);
						}

						if (0 != bx::memCmp(m_current.vbv, cmd.vbv, sizeof(cmd.vbv) ) )
						{
							bx::memCopy(m_current.vbv, cmd.vbv, sizeof(cmd.vbv) );
							_commandList->IASetVertexBuffers(0
								, 0 == cmd.vbv[1].BufferLocation ? 1 : 2
								, cmd.vbv
								);
						}

						if (0 != bx::memCmp(&m_current.ibv, &cmd.ibv, sizeof(cmd.ibv) ) )
						{
							bx::memCopy(&m_current.ibv, &cmd.ibv, sizeof(cmd.ibv) );
							_commandList->IASetIndexBuffer(&cmd.ibv);
						}

						_commandList->DrawIndexedInstanced(
							  cmd.drawIndexed.IndexCountPerInstance
							, cmd.drawIndexed.InstanceCount
							, cmd.drawIndexed.StartIndexLocation
							, cmd.drawIndexed.BaseVertexLocation
							, cmd.drawIndexed.StartInstanceLocation
							);
					}
				}
			}
		}
	}

	void BatchD3D12::flush(ID3D12GraphicsCommandList* _commandList, bool _clean)
	{
		flush(_commandList, Draw);
		flush(_commandList, DrawIndexed);

		if (_clean)
		{
			bx::memSet(&m_current, 0, sizeof(m_current) );
		}
	}

	void BatchD3D12::begin()
	{
		bx::memSet(&m_stats,   0, sizeof(m_stats) );
		bx::memSet(&m_current, 0, sizeof(m_current) );
	}

	void BatchD3D12::end(ID3D12GraphicsCommandList* _commandList)
	{
		flush(_commandList);
	}

	struct UavFormat
	{
		DXGI_FORMAT format[3];
		uint32_t    stride;
	};

	static const UavFormat s_uavFormat[] =
	{	//  BGFX_BUFFER_COMPUTE_TYPE_UINT, BGFX_BUFFER_COMPUTE_TYPE_INT,   BGFX_BUFFER_COMPUTE_TYPE_FLOAT
		{ { DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN            },  0 }, // ignored
		{ { DXGI_FORMAT_R8_SINT,           DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_UNKNOWN            },  1 }, // BGFX_BUFFER_COMPUTE_FORMAT_8x1
		{ { DXGI_FORMAT_R8G8_SINT,         DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_UNKNOWN            },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_8x2
		{ { DXGI_FORMAT_R8G8B8A8_SINT,     DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_UNKNOWN            },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_8x4
		{ { DXGI_FORMAT_R16_SINT,          DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_FLOAT          },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_16x1
		{ { DXGI_FORMAT_R16G16_SINT,       DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_FLOAT       },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_16x2
		{ { DXGI_FORMAT_R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_FLOAT },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_16x4
		{ { DXGI_FORMAT_R32_SINT,          DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_FLOAT          },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_32x1
		{ { DXGI_FORMAT_R32G32_SINT,       DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_FLOAT       },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_32x2
		{ { DXGI_FORMAT_R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_FLOAT }, 16 }, // BGFX_BUFFER_COMPUTE_FORMAT_32x4
	};

	void BufferD3D12::create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride)
	{
		m_size    = _size;
		m_flags   = _flags;

		const bool needUav = 0 != (_flags & (BGFX_BUFFER_COMPUTE_WRITE|BGFX_BUFFER_DRAW_INDIRECT) );
		const bool drawIndirect = 0 != (_flags & BGFX_BUFFER_DRAW_INDIRECT);
		m_dynamic = NULL == _data || needUav;

		DXGI_FORMAT format;
		uint32_t    stride;

		uint32_t flags = needUav
			? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
			: D3D12_RESOURCE_FLAG_NONE
			;

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
				const uint32_t uavType = bx::uint32_satsub( (_flags & BGFX_BUFFER_COMPUTE_TYPE_MASK) >> BGFX_BUFFER_COMPUTE_TYPE_SHIFT, 1);
				format = s_uavFormat[uavFormat].format[uavType];
				stride = s_uavFormat[uavFormat].stride;
			}
		}

		stride = 0 == _stride ? stride : _stride;

		m_srvd.Format                      = format;
		m_srvd.ViewDimension               = D3D12_SRV_DIMENSION_BUFFER;
		m_srvd.Shader4ComponentMapping     = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		m_srvd.Buffer.FirstElement         = 0;
		m_srvd.Buffer.NumElements          = m_size / stride;
		m_srvd.Buffer.StructureByteStride  = 0;
		m_srvd.Buffer.Flags                = D3D12_BUFFER_SRV_FLAG_NONE;

		m_uavd.Format                      = format;
		m_uavd.ViewDimension               = D3D12_UAV_DIMENSION_BUFFER;
		m_uavd.Buffer.FirstElement         = 0;
		m_uavd.Buffer.NumElements          = m_size / stride;
		m_uavd.Buffer.StructureByteStride  = 0;
		m_uavd.Buffer.CounterOffsetInBytes = 0;
		m_uavd.Buffer.Flags                = D3D12_BUFFER_UAV_FLAG_NONE;

		ID3D12Device* device = s_renderD3D12->m_device;
		ID3D12GraphicsCommandList* commandList = s_renderD3D12->m_commandList;

		m_ptr   = createCommittedResource(device, HeapProperty::Default, _size, D3D12_RESOURCE_FLAGS(flags) );
		m_gpuVA = m_ptr->GetGPUVirtualAddress();
		setState(commandList, drawIndirect
			? D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT
			: D3D12_RESOURCE_STATE_GENERIC_READ
			);

		if (!m_dynamic)
		{
			update(commandList, 0, _size, _data);
		}
	}

	void BufferD3D12::update(ID3D12GraphicsCommandList* _commandList, uint32_t _offset, uint32_t _size, void* _data, bool /*_discard*/)
	{
		ID3D12Resource* staging = createCommittedResource(s_renderD3D12->m_device, HeapProperty::Upload, _size);
		uint8_t* data;
		DX_CHECK(staging->Map(0, NULL, (void**)&data) );
		bx::memCopy(data, _data, _size);
		staging->Unmap(0, NULL);

		D3D12_RESOURCE_STATES state = setState(_commandList, D3D12_RESOURCE_STATE_COPY_DEST);
		_commandList->CopyBufferRegion(m_ptr, _offset, staging, 0, _size);
		setState(_commandList, state);

		s_renderD3D12->m_cmd.release(staging);
	}

	void BufferD3D12::destroy()
	{
		if (NULL != m_ptr)
		{
			s_renderD3D12->m_cmd.release(m_ptr);
			m_dynamic = false;
		}
	}

	D3D12_RESOURCE_STATES BufferD3D12::setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state)
	{
		if (m_state != _state)
		{
			setResourceBarrier(_commandList
				, m_ptr
				, m_state
				, _state
				);

			bx::xchg(m_state, _state);
		}

		return _state;
	}

	void VertexBufferD3D12::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags)
	{
		BufferD3D12::create(_size, _data, _flags, true);
		m_decl = _declHandle;
	}

	void ShaderD3D12::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		switch (magic)
		{
		case BGFX_CHUNK_MAGIC_CSH:
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
		m_numUniforms = count;

		BX_TRACE("%s Shader consts %d"
			, BGFX_CHUNK_MAGIC_FSH == magic ? "Fragment" : BGFX_CHUNK_MAGIC_VSH == magic ? "Vertex" : "Compute"
			, count
			);

		uint8_t fragmentBit = fragment ? BGFX_UNIFORM_FRAGMENTBIT : 0;

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize);

				char name[256] = {};
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
					const UniformRegInfo* info = s_renderD3D12->m_uniformReg.find(name);
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

		const void* code = reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		m_code = copy(code, shaderSize);

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

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(iohash);
		murmur.add(code, shaderSize);
		murmur.add(numAttrs);
		murmur.add(m_attrMask, numAttrs);
		m_hash = murmur.end();

		bx::read(&reader, m_size);
	}

	void TextureD3D12::create(const Memory* _mem, uint32_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			uint8_t numMips = imageContainer.m_numMips;
			const uint8_t startLod = uint8_t(bx::uint32_min(_skip, numMips-1) );
			numMips -= startLod;
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
			const uint32_t textureWidth  = bx::uint32_max(blockInfo.blockWidth,  imageContainer.m_width >>startLod);
			const uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height>>startLod);
			const uint16_t numLayers     = imageContainer.m_numLayers;

			m_flags  = _flags;
			m_width  = textureWidth;
			m_height = textureHeight;
			m_depth  = imageContainer.m_depth;
			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			if (imageContainer.m_cubeMap)
			{
				m_type = TextureCube;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = Texture3D;
			}
			else
			{
				m_type = Texture2D;
			}

			m_numMips = numMips;
			const uint16_t numSides = numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const uint32_t numSrd   = numSides * numMips;
			D3D12_SUBRESOURCE_DATA* srd = (D3D12_SUBRESOURCE_DATA*)alloca(numSrd*sizeof(D3D12_SUBRESOURCE_DATA) );

			uint32_t kk = 0;

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool swizzle    = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			uint32_t blockWidth   = 1;
			uint32_t blockHeight  = 1;

			if (convert && compressed)
			{
				blockWidth  = blockInfo.blockWidth;
				blockHeight = blockInfo.blockHeight;
			}

			const bool writeOnly    = 0 != (m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s RT[%c], BO[%c], CW[%c]%s."
				, this - s_renderD3D12->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, textureWidth
				, textureHeight
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly    ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);

			uint32_t totalSize = 0;

			for (uint8_t side = 0; side < numSides; ++side)
			{
				uint32_t width  = textureWidth;
				uint32_t height = textureHeight;
				uint32_t depth  = imageContainer.m_depth;

				for (uint8_t lod = 0; lod < numMips; ++lod)
				{
					width  = bx::uint32_max(blockWidth,  width);
					height = bx::uint32_max(blockHeight, height);
					depth  = bx::uint32_max(1, depth);

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						if (convert)
						{
							const uint32_t pitch = bx::strideAlign(width*bpp / 8,  D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							const uint32_t slice = bx::strideAlign(pitch * height, D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, slice);
							bimg::imageDecodeToBgra8(temp
									, mip.m_data
									, mip.m_width
									, mip.m_height
									, pitch, mip.m_format
									);

							srd[kk].pData      = temp;
							srd[kk].RowPitch   = pitch;
							srd[kk].SlicePitch = slice;
							totalSize += slice;
						}
						else if (compressed)
						{
							uint32_t pitch = bx::strideAlign( (mip.m_width /blockInfo.blockWidth )*mip.m_blockSize, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							uint32_t slice = bx::strideAlign( (mip.m_height/blockInfo.blockHeight)*pitch,           D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, slice);
							bimg::imageCopy(temp
									, mip.m_height/blockInfo.blockHeight
									, (mip.m_width /blockInfo.blockWidth )*mip.m_blockSize
									, mip.m_data
									, pitch
									);

							srd[kk].pData      = temp;
							srd[kk].RowPitch   = pitch;
							srd[kk].SlicePitch = slice;
							totalSize += slice;
						}
						else
						{
							const uint32_t pitch = bx::strideAlign(mip.m_width*mip.m_bpp / 8, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							const uint32_t slice = bx::strideAlign(pitch * mip.m_height,      D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, slice);
							bimg::imageCopy(temp
									, mip.m_height
									, mip.m_width*mip.m_bpp / 8
									, mip.m_data
									, pitch
									);

							srd[kk].pData = temp;
							srd[kk].RowPitch   = pitch;
							srd[kk].SlicePitch = slice;
							totalSize += slice;
						}

 						if (swizzle)
 						{
// 							imageSwizzleBgra8(temp, width, height, mip.m_width*4, data);
 						}

						srd[kk].SlicePitch = mip.m_height*srd[kk].RowPitch;
						++kk;
					}
					else
					{
						const uint32_t pitch = bx::strideAlign(width*bpp / 8, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
						const uint32_t slice = bx::strideAlign(pitch * height, D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);
						totalSize += slice;
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			BX_TRACE("texture total size: %d", totalSize);

			const uint32_t msaaQuality = bx::uint32_satsub( (m_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

			bx::memSet(&m_srvd, 0, sizeof(m_srvd) );
			m_srvd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			m_srvd.Format = s_textureFormat[m_textureFormat].m_fmtSrv;
			DXGI_FORMAT format = s_textureFormat[m_textureFormat].m_fmt;
			if (swizzle)
			{
				format        = DXGI_FORMAT_R8G8B8A8_UNORM;
				m_srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			}

			m_uavd.Format = m_srvd.Format;

			ID3D12Device* device = s_renderD3D12->m_device;
			ID3D12GraphicsCommandList* commandList = s_renderD3D12->m_commandList;

			D3D12_RESOURCE_DESC resourceDesc;
			resourceDesc.Alignment  = 0;
			resourceDesc.Width      = textureWidth;
			resourceDesc.Height     = textureHeight;
			resourceDesc.MipLevels  = numMips;
			resourceDesc.Format     = format;
			resourceDesc.SampleDesc = msaa;
			resourceDesc.Layout     = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resourceDesc.Flags      = D3D12_RESOURCE_FLAG_NONE;
			resourceDesc.DepthOrArraySize = numSides;

			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

			D3D12_CLEAR_VALUE* clearValue = NULL;
			if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) ) )
			{
				resourceDesc.Format = s_textureFormat[m_textureFormat].m_fmt;
				resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
				state              |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
				state              &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

				clearValue = (D3D12_CLEAR_VALUE*)alloca(sizeof(D3D12_CLEAR_VALUE) );
				clearValue->Format = s_textureFormat[m_textureFormat].m_fmtDsv;
				clearValue->DepthStencil.Depth   = 1.0f;
				clearValue->DepthStencil.Stencil = 0;
			}
			else if (renderTarget)
			{
				clearValue = (D3D12_CLEAR_VALUE*)alloca(sizeof(D3D12_CLEAR_VALUE) );
				clearValue->Format = resourceDesc.Format;
				clearValue->Color[0] = 0.0f;
				clearValue->Color[1] = 0.0f;
				clearValue->Color[2] = 0.0f;
				clearValue->Color[3] = 0.0f;

				resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			}

			if (writeOnly)
			{
				resourceDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
				state              &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			}

			if (computeWrite)
			{
				resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			}

			switch (m_type)
			{
			case Texture2D:
			case TextureCube:
				resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				if (imageContainer.m_cubeMap)
				{
					if (1 < numLayers)
					{
						m_srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
						m_srvd.TextureCubeArray.MostDetailedMip     = 0;
						m_srvd.TextureCubeArray.MipLevels           = numMips;
						m_srvd.TextureCubeArray.ResourceMinLODClamp = 0.0f;
						m_srvd.TextureCubeArray.NumCubes            = numLayers;
					}
					else
					{
						m_srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
						m_srvd.TextureCube.MostDetailedMip     = 0;
						m_srvd.TextureCube.MipLevels           = numMips;
						m_srvd.TextureCube.ResourceMinLODClamp = 0.0f;
					}
				}
				else
				{
					if (1 < numLayers)
					{
						m_srvd.ViewDimension = 1 < msaa.Count
							? D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY
							: D3D12_SRV_DIMENSION_TEXTURE2DARRAY
							;
						m_srvd.Texture2DArray.MostDetailedMip     = 0;
						m_srvd.Texture2DArray.MipLevels           = numMips;
						m_srvd.Texture2DArray.ResourceMinLODClamp = 0.0f;
						m_srvd.Texture2DArray.ArraySize           = numLayers;
					}
					else
					{
						m_srvd.ViewDimension = 1 < msaa.Count
							? D3D12_SRV_DIMENSION_TEXTURE2DMS
							: D3D12_SRV_DIMENSION_TEXTURE2D
							;
						m_srvd.Texture2D.MostDetailedMip     = 0;
						m_srvd.Texture2D.MipLevels           = numMips;
						m_srvd.Texture2D.ResourceMinLODClamp = 0.0f;
					}
				}

				if (1 < numLayers)
				{
					m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
					m_uavd.Texture2DArray.MipSlice   = 0;
					m_uavd.Texture2DArray.PlaneSlice = 0;
				}
				else
				{
					m_uavd.ViewDimension        = D3D12_UAV_DIMENSION_TEXTURE2D;
					m_uavd.Texture2D.MipSlice   = 0;
					m_uavd.Texture2D.PlaneSlice = 0;
				}

				if (TextureCube == m_type)
				{
					m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
					m_uavd.Texture2DArray.MipSlice   = 0;
					m_uavd.Texture2DArray.ArraySize = 6;
				}

				break;

			case Texture3D:
				resourceDesc.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
				resourceDesc.DepthOrArraySize = uint16_t(m_depth);
				m_srvd.ViewDimension                 = D3D12_SRV_DIMENSION_TEXTURE3D;
				m_srvd.Texture3D.MostDetailedMip     = 0;
				m_srvd.Texture3D.MipLevels           = numMips;
				m_srvd.Texture3D.ResourceMinLODClamp = 0.0f;

				m_uavd.ViewDimension         = D3D12_UAV_DIMENSION_TEXTURE3D;
				m_uavd.Texture3D.MipSlice    = 0;
				m_uavd.Texture3D.FirstWSlice = 0;
				m_uavd.Texture3D.WSize       = 0;
				break;
			}

			m_ptr = createCommittedResource(device, HeapProperty::Default, &resourceDesc, clearValue);

			{
				uint64_t uploadBufferSize;
				uint32_t* numRows        = (uint32_t*)alloca(sizeof(uint32_t)*numSrd);
				uint64_t* rowSizeInBytes = (uint64_t*)alloca(sizeof(uint64_t)*numSrd);
				D3D12_PLACED_SUBRESOURCE_FOOTPRINT* layouts = (D3D12_PLACED_SUBRESOURCE_FOOTPRINT*)alloca(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT)*numSrd);

				device->GetCopyableFootprints(&resourceDesc
					, 0
					, numSrd
					, 0
					, layouts
					, numRows
					, rowSizeInBytes
					, &uploadBufferSize
					);
				BX_WARN(uploadBufferSize == totalSize, "uploadBufferSize %d (totalSize %d), numRows %d, rowSizeInBytes %d"
					, uploadBufferSize
					, totalSize
					, numRows[0]
					, rowSizeInBytes[0]
					);
			}

			if (kk != 0)
			{
				ID3D12Resource* staging = createCommittedResource(s_renderD3D12->m_device, HeapProperty::Upload, totalSize);

				setState(commandList,D3D12_RESOURCE_STATE_COPY_DEST);

				uint64_t result = UpdateSubresources(commandList
					, m_ptr
					, staging
					, 0
					, 0
					, numSrd
					, srd
					);
				BX_CHECK(0 != result, "Invalid size"); BX_UNUSED(result);
				BX_TRACE("Update subresource %" PRId64, result);

				setState(commandList, state);

				s_renderD3D12->m_cmd.release(staging);
			}
			else
			{
				setState(commandList, state);
			}

			if (0 != kk)
			{
				kk = 0;
				for (uint8_t side = 0; side < numSides; ++side)
				{
					for (uint32_t lod = 0, num = numMips; lod < num; ++lod)
					{
						BX_FREE(g_allocator, const_cast<void*>(srd[kk].pData) );
						++kk;
					}
				}
			}
		}
	}

	void TextureD3D12::destroy()
	{
		if (NULL != m_ptr)
		{
			s_renderD3D12->m_cmd.release(m_ptr);
			m_ptr = NULL;
		}
	}

	void TextureD3D12::update(ID3D12GraphicsCommandList* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		setState(_commandList, D3D12_RESOURCE_STATE_COPY_DEST);

		const uint32_t subres = _mip + (_side * m_numMips);
		const uint32_t bpp    = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		const uint32_t rectpitch = _rect.m_width*bpp/8;
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;

		D3D12_RESOURCE_DESC desc = m_ptr->GetDesc();

		desc.Height = _rect.m_height;

		uint32_t numRows;
		uint64_t totalBytes;
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
		s_renderD3D12->m_device->GetCopyableFootprints(&desc
			, subres
			, 1
			, 0
			, &layout
			, &numRows
			, NULL
			, &totalBytes
			);

		const uint32_t rowPitch = layout.Footprint.RowPitch;

		ID3D12Resource* staging = createCommittedResource(s_renderD3D12->m_device, HeapProperty::Upload, totalBytes);
		uint8_t* data;

		DX_CHECK(staging->Map(0, NULL, (void**)&data) );
		for (uint32_t ii = 0, height = _rect.m_height; ii < height; ++ii)
		{
			bx::memCopy(&data[ii*rowPitch], &_mem->data[ii*srcpitch], srcpitch);
		}
		staging->Unmap(0, NULL);

		D3D12_BOX box;
		box.left   = 0;
		box.top    = 0;
		box.right  = box.left + _rect.m_width;
		box.bottom = box.top  + _rect.m_height;
		box.front  = _z;
		box.back   = _z+_depth;

		D3D12_TEXTURE_COPY_LOCATION dst = { m_ptr,   D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {        } };
		dst.SubresourceIndex = subres;
		D3D12_TEXTURE_COPY_LOCATION src = { staging, D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
		_commandList->CopyTextureRegion(&dst, _rect.m_x, _rect.m_y, 0, &src, &box);

		setState(_commandList, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		s_renderD3D12->m_cmd.release(staging);
	}

	void TextureD3D12::resolve()
	{
	}

	D3D12_RESOURCE_STATES TextureD3D12::setState(ID3D12GraphicsCommandList* _commandList, D3D12_RESOURCE_STATES _state)
	{
		if (m_state != _state)
		{
			setResourceBarrier(_commandList
				, m_ptr
				, m_state
				, _state
				);

			bx::xchg(m_state, _state);
		}

		return _state;
	}

	void FrameBufferD3D12::create(uint8_t _num, const Attachment* _attachment)
	{
		m_denseIdx = UINT16_MAX;
		m_numTh = _num;
		bx::memCopy(m_attachment, _attachment, _num*sizeof(Attachment) );

		postReset();
	}

	void FrameBufferD3D12::create(uint16_t /*_denseIdx*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_depthFormat*/)
	{
	}

	void FrameBufferD3D12::preReset()
	{
	}

	void FrameBufferD3D12::postReset()
	{
		if (m_numTh != 0)
		{
			ID3D12Device* device = s_renderD3D12->m_device;

			D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptor = s_renderD3D12->m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			uint32_t rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			uint32_t fbhIdx = (uint32_t)(this - s_renderD3D12->m_frameBuffers);
			rtvDescriptor.ptr += (BX_COUNTOF(s_renderD3D12->m_backBufferColor) + fbhIdx * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) * rtvDescriptorSize;

			m_width  = 0;
			m_height = 0;
			m_depth.idx = bgfx::invalidHandle;
			m_num = 0;
			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				TextureHandle handle = m_attachment[ii].handle;
				if (isValid(handle) )
				{
					const TextureD3D12& texture = s_renderD3D12->m_textures[handle.idx];

					if (0 == m_width)
					{
						D3D12_RESOURCE_DESC desc = texture.m_ptr->GetDesc();
						m_width  = uint32_t(desc.Width);
						m_height = uint32_t(desc.Height);
					}

					if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
					{
						BX_CHECK(!isValid(m_depth), "");
						m_depth = handle;
						D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor = s_renderD3D12->m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
						uint32_t dsvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
						dsvDescriptor.ptr += (1 + fbhIdx) * dsvDescriptorSize;

						const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(texture.m_textureFormat) );
						BX_UNUSED(blockInfo);

						D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
						ZeroMemory(&dsvDesc, sizeof(dsvDesc) );
						dsvDesc.Format        = s_textureFormat[texture.m_textureFormat].m_fmtDsv;
						dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
						dsvDesc.Flags         = D3D12_DSV_FLAG_NONE
// 							| (blockInfo.depthBits   > 0 ? D3D12_DSV_FLAG_READ_ONLY_DEPTH   : D3D12_DSV_FLAG_NONE)
// 							| (blockInfo.stencilBits > 0 ? D3D12_DSV_FLAG_READ_ONLY_STENCIL : D3D12_DSV_FLAG_NONE)
							;

						device->CreateDepthStencilView(texture.m_ptr
							, &dsvDesc
							, dsvDescriptor
							);
					}
					else
					{
						m_texture[m_num] = handle;
						D3D12_CPU_DESCRIPTOR_HANDLE rtv = { rtvDescriptor.ptr + m_num * rtvDescriptorSize };
						device->CreateRenderTargetView(texture.m_ptr
							, NULL
							, rtv
							);
						m_num++;
					}
				}
			}
		}
	}

	uint16_t FrameBufferD3D12::destroy()
	{
		m_numTh = 0;

		m_depth.idx = bgfx::invalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void FrameBufferD3D12::resolve()
	{
	}

	void FrameBufferD3D12::clear(ID3D12GraphicsCommandList* _commandList, const Clear& _clear, const float _palette[][4], const D3D12_RECT* _rect, uint32_t _num)
	{
		ID3D12Device* device = s_renderD3D12->m_device;
		const uint32_t fbhIdx = (uint32_t)(this - s_renderD3D12->m_frameBuffers);

		if (BGFX_CLEAR_COLOR & _clear.m_flags
		&&  0 != m_num)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptor = s_renderD3D12->m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			uint32_t rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			rtvDescriptor.ptr += (BX_COUNTOF(s_renderD3D12->m_backBufferColor) + fbhIdx * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) * rtvDescriptorSize;

			if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
			{
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					uint8_t index = _clear.m_index[ii];
					if (UINT8_MAX != index)
					{
						D3D12_CPU_DESCRIPTOR_HANDLE rtv = { rtvDescriptor.ptr + ii * rtvDescriptorSize };
						_commandList->ClearRenderTargetView(rtv
								, _palette[index]
								, _num
								, _rect
								);
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
					D3D12_CPU_DESCRIPTOR_HANDLE rtv = { rtvDescriptor.ptr + ii * rtvDescriptorSize };
					_commandList->ClearRenderTargetView(rtv
						, frgba
						, _num
						, _rect
						);
				}
			}
		}

		if (isValid(m_depth)
		&& (BGFX_CLEAR_DEPTH|BGFX_CLEAR_STENCIL) & _clear.m_flags)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor = s_renderD3D12->m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			uint32_t dsvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
			dsvDescriptor.ptr += (1 + fbhIdx) * dsvDescriptorSize;

			DWORD flags = 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_DEPTH)   ? D3D12_CLEAR_FLAG_DEPTH   : 0;
			flags |= (_clear.m_flags & BGFX_CLEAR_STENCIL) ? D3D12_CLEAR_FLAG_STENCIL : 0;

			_commandList->ClearDepthStencilView(dsvDescriptor
				, D3D12_CLEAR_FLAGS(flags)
				, _clear.m_depth
				, _clear.m_stencil
				, _num
				, _rect
				);
		}
	}

	void TimerQueryD3D12::init()
	{
		D3D12_QUERY_HEAP_DESC queryHeapDesc;
		queryHeapDesc.Count    = m_control.m_size * 2;
		queryHeapDesc.NodeMask = 1;
		queryHeapDesc.Type     = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
		DX_CHECK(s_renderD3D12->m_device->CreateQueryHeap(&queryHeapDesc
				, IID_ID3D12QueryHeap
				, (void**)&m_queryHeap
				) );

		const uint32_t size = queryHeapDesc.Count*sizeof(uint64_t);
		m_readback = createCommittedResource(s_renderD3D12->m_device
						, HeapProperty::ReadBack
						, size
						);

		DX_CHECK(s_renderD3D12->m_cmd.m_commandQueue->GetTimestampFrequency(&m_frequency) );

		D3D12_RANGE range = { 0, size };
		m_readback->Map(0, &range, (void**)&m_result);
	}

	void TimerQueryD3D12::shutdown()
	{
		D3D12_RANGE range = { 0, 0 };
		m_readback->Unmap(0, &range);

		DX_RELEASE(m_queryHeap, 0);
		DX_RELEASE(m_readback, 0);
	}

	void TimerQueryD3D12::begin(ID3D12GraphicsCommandList* _commandList)
	{
		BX_UNUSED(_commandList);
		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		uint32_t offset = m_control.m_current * 2 + 0;
		_commandList->EndQuery(m_queryHeap
			, D3D12_QUERY_TYPE_TIMESTAMP
			, offset
			);
	}

	void TimerQueryD3D12::end(ID3D12GraphicsCommandList* _commandList)
	{
		BX_UNUSED(_commandList);
		uint32_t offset = m_control.m_current * 2;
		_commandList->EndQuery(m_queryHeap
			, D3D12_QUERY_TYPE_TIMESTAMP
			, offset + 1
			);
		_commandList->ResolveQueryData(m_queryHeap
			, D3D12_QUERY_TYPE_TIMESTAMP
			, offset
			, 2
			, m_readback
			, offset * sizeof(uint64_t)
			);
		m_control.commit(1);
	}

	bool TimerQueryD3D12::get()
	{
		if (0 != m_control.available() )
		{
			uint32_t offset = m_control.m_read * 2;
			m_begin = m_result[offset+0];
			m_end   = m_result[offset+1];
			m_elapsed = m_end - m_begin;

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void OcclusionQueryD3D12::init()
	{
		D3D12_QUERY_HEAP_DESC queryHeapDesc;
		queryHeapDesc.Count    = BX_COUNTOF(m_handle);
		queryHeapDesc.NodeMask = 1;
		queryHeapDesc.Type     = D3D12_QUERY_HEAP_TYPE_OCCLUSION;
		DX_CHECK(s_renderD3D12->m_device->CreateQueryHeap(&queryHeapDesc
				, IID_ID3D12QueryHeap
				, (void**)&m_queryHeap
				) );

		const uint32_t size = BX_COUNTOF(m_handle)*sizeof(uint64_t);
		m_readback = createCommittedResource(s_renderD3D12->m_device
						, HeapProperty::ReadBack
						, size
						);

		D3D12_RANGE range = { 0, size };
		m_readback->Map(0, &range, (void**)&m_result);
	}

	void OcclusionQueryD3D12::shutdown()
	{
		D3D12_RANGE range = { 0, 0 };
		m_readback->Unmap(0, &range);

		DX_RELEASE(m_queryHeap, 0);
		DX_RELEASE(m_readback, 0);
	}

	void OcclusionQueryD3D12::begin(ID3D12GraphicsCommandList* _commandList, Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			OcclusionQueryHandle handle = m_handle[m_control.m_read];
			if (isValid(handle) )
			{
				_render->m_occlusion[handle.idx] = int32_t(m_result[handle.idx]);
			}
			m_control.consume(1);
		}

		m_handle[m_control.m_current] = _handle;
		_commandList->BeginQuery(m_queryHeap
			, D3D12_QUERY_TYPE_BINARY_OCCLUSION
			, _handle.idx
			);
	}

	void OcclusionQueryD3D12::end(ID3D12GraphicsCommandList* _commandList)
	{
		OcclusionQueryHandle handle = m_handle[m_control.m_current];
		_commandList->EndQuery(m_queryHeap
			, D3D12_QUERY_TYPE_BINARY_OCCLUSION
			, handle.idx
			);
		_commandList->ResolveQueryData(m_queryHeap
			, D3D12_QUERY_TYPE_BINARY_OCCLUSION
			, handle.idx
			, 1
			, m_readback
			, handle.idx * sizeof(uint64_t)
			);
		m_control.commit(1);
	}

	void OcclusionQueryD3D12::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
		{
			OcclusionQueryHandle& handle = m_handle[(m_control.m_read + ii) % size];
			if (handle.idx == _handle.idx)
			{
				handle.idx = bgfx::invalidHandle;
			}
		}
	}

	struct Bind
	{
		D3D12_GPU_DESCRIPTOR_HANDLE m_srvHandle;
		uint16_t m_samplerStateIdx;
	};

	void RendererContextD3D12::submit(Frame* _render, ClearQuad& /*_clearQuad*/, TextVideoMemBlitter& _textVideoMemBlitter)
	{
//		PIX_BEGINEVENT(D3DCOLOR_FRAME, L"rendererSubmit");

		if (m_lost
		||  updateResolution(_render->m_resolution) )
		{
			return;
		}

		int64_t elapsed = -bx::getHPCounter();
		int64_t captureElapsed = 0;

		m_gpuTimer.begin(m_commandList);

		if (0 < _render->m_iboffset)
		{
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(m_commandList, 0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(m_commandList, 0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		RenderBind currentBind;
		currentBind.clear();

		_render->m_hmdInitialized = false;

		const bool hmdEnabled = false;
		static ViewState viewState;
		viewState.reset(_render, hmdEnabled);

// 		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
// 		setDebugWireframe(wireframe);

		uint16_t currentSamplerStateIdx = invalidHandle;
		uint16_t currentProgramIdx      = invalidHandle;
		uint32_t currentBindHash        = 0;
		bool     hasPredefined          = false;
		bool     commandListChanged     = false;
		ID3D12PipelineState* currentPso = NULL;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitKey blitKey;
		blitKey.decode(_render->m_blitKeys[0]);
		uint16_t numBlitItems = _render->m_numBlitItems;
		uint16_t blitItem = 0;

		uint32_t blendFactor = 0;

		const uint64_t primType = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];

		bool wasCompute = false;
		bool viewHasScissor = false;
		bool restoreScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

#if BX_PLATFORM_WINDOWS
		m_backBufferColorIdx = m_swapChain->GetCurrentBackBufferIndex();
#endif // BX_PLATFORM_WINDOWS

		const uint64_t f0 = BGFX_STATE_BLEND_FACTOR;
		const uint64_t f1 = BGFX_STATE_BLEND_INV_FACTOR;
		const uint64_t f2 = BGFX_STATE_BLEND_FACTOR<<4;
		const uint64_t f3 = BGFX_STATE_BLEND_INV_FACTOR<<4;

		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
		ScratchBufferD3D12& scratchBuffer = m_scratchBuffer[m_backBufferColorIdx];
		scratchBuffer.reset(gpuHandle);

		D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = UINT64_C(0);

		StateCacheLru<Bind, 64> bindLru;

		setResourceBarrier(m_commandList
			, m_backBufferColor[m_backBufferColorIdx]
			, D3D12_RESOURCE_STATE_PRESENT
			, D3D12_RESOURCE_STATE_RENDER_TARGET
			);

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
			m_batch.begin();

// 			uint8_t eye = 0;
// 			uint8_t restartState = 0;
			viewState.m_rect = _render->m_rect[0];

			int32_t numItems = _render->m_num;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
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
					m_batch.flush(m_commandList, true);
					kick();

					view = key.m_view;
					currentPso = NULL;
					currentSamplerStateIdx = invalidHandle;
					currentProgramIdx      = invalidHandle;
					hasPredefined          = false;

					fbh = _render->m_fb[view];
					setFrameBuffer(fbh);

					viewState.m_rect = _render->m_rect[view];
					const Rect& rect        = _render->m_rect[view];
					const Rect& scissorRect = _render->m_scissor[view];
					viewHasScissor  = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : rect;

					D3D12_VIEWPORT vp;
					vp.TopLeftX = rect.m_x;
					vp.TopLeftY = rect.m_y;
					vp.Width    = rect.m_width;
					vp.Height   = rect.m_height;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					m_commandList->RSSetViewports(1, &vp);

					D3D12_RECT rc;
					rc.left   = viewScissorRect.m_x;
					rc.top    = viewScissorRect.m_y;
					rc.right  = viewScissorRect.m_x + viewScissorRect.m_width;
					rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
					m_commandList->RSSetScissorRects(1, &rc);
					restoreScissor = false;

					Clear& clr = _render->m_clear[view];
					if (BGFX_CLEAR_NONE != clr.m_flags)
					{
						Rect clearRect = rect;
						clearRect.setIntersect(rect, viewScissorRect);
						clearQuad(clearRect, clr, _render->m_colorPalette);
					}

					prim = s_primInfo[BX_COUNTOF(s_primName)]; // Force primitive type update.

					const uint8_t blitView = SortKey::decodeView(encodedKey);
					for (; blitItem < numBlitItems && blitKey.m_view <= blitView; blitItem++)
					{
						const BlitItem& blit = _render->m_blitItem[blitItem];
						blitKey.decode(_render->m_blitKeys[blitItem+1]);

						const TextureD3D12& src = m_textures[blit.m_src.idx];
						const TextureD3D12& dst = m_textures[blit.m_dst.idx];

 						uint32_t srcWidth  = bx::uint32_min(src.m_width,  blit.m_srcX + blit.m_width)  - blit.m_srcX;
 						uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
 						uint32_t srcDepth  = bx::uint32_min(src.m_depth,  blit.m_srcZ + blit.m_depth)  - blit.m_srcZ;
 						uint32_t dstWidth  = bx::uint32_min(dst.m_width,  blit.m_dstX + blit.m_width)  - blit.m_dstX;
 						uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
 						uint32_t dstDepth  = bx::uint32_min(dst.m_depth,  blit.m_dstZ + blit.m_depth)  - blit.m_dstZ;
 						uint32_t width     = bx::uint32_min(srcWidth,  dstWidth);
 						uint32_t height    = bx::uint32_min(srcHeight, dstHeight);
 						uint32_t depth     = bx::uint32_min(srcDepth,  dstDepth);

						if (TextureD3D12::Texture3D == src.m_type)
						{
							D3D12_BOX box;
 							box.left   = blit.m_srcX;
 							box.top    = blit.m_srcY;
 							box.front  = blit.m_srcZ;
 							box.right  = blit.m_srcX + width;
 							box.bottom = blit.m_srcY + height;;
 							box.back   = blit.m_srcZ + bx::uint32_imax(1, depth);

							D3D12_TEXTURE_COPY_LOCATION dstLocation = { dst.m_ptr, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {{}} };
							D3D12_TEXTURE_COPY_LOCATION srcLocation = { src.m_ptr, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {{}} };
							m_commandList->CopyTextureRegion(&dstLocation
								, blit.m_dstX
								, blit.m_dstY
								, blit.m_dstZ
								, &srcLocation
								, &box
								);
						}
						else
						{
							D3D12_BOX box;
							box.left   = blit.m_srcX;
							box.top    = blit.m_srcY;
							box.front  = 0;
							box.right  = blit.m_srcX + width;
							box.bottom = blit.m_srcY + height;;
							box.back   = 1;

							const uint32_t srcZ = TextureD3D12::TextureCube == src.m_type
								? blit.m_srcZ
								: 0
								;
							const uint32_t dstZ = TextureD3D12::TextureCube == dst.m_type
								? blit.m_dstZ
								: 0
								;

							D3D12_TEXTURE_COPY_LOCATION dstLocation;
							dstLocation.pResource = dst.m_ptr;
							dstLocation.Type      = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
							dstLocation.SubresourceIndex = dstZ*dst.m_numMips+blit.m_dstMip;
							D3D12_TEXTURE_COPY_LOCATION srcLocation;
							srcLocation.pResource = src.m_ptr;
							srcLocation.Type      = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
							srcLocation.SubresourceIndex = srcZ*src.m_numMips+blit.m_srcMip;

							bool depthStencil = bimg::isDepth(bimg::TextureFormat::Enum(src.m_textureFormat) );
							m_commandList->CopyTextureRegion(&dstLocation
								, blit.m_dstX
								, blit.m_dstY
								, 0
								, &srcLocation
								, depthStencil ? NULL : &box
								);
						}
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						m_commandList->SetComputeRootSignature(m_rootSignature);
						ID3D12DescriptorHeap* heaps[] = {
							m_samplerAllocator.getHeap(),
							scratchBuffer.getHeap(),
						};
						m_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);
					}

					const RenderCompute& compute = renderItem.compute;

					ID3D12PipelineState* pso = getPipelineState(key.m_program);
					if (pso != currentPso)
					{
						currentPso = pso;
						m_commandList->SetPipelineState(pso);
						currentBindHash = 0;
					}

					uint32_t bindHash = bx::hashMurmur2A(renderBind.m_bind, sizeof(renderBind.m_bind) );
					if (currentBindHash != bindHash)
					{
						currentBindHash  = bindHash;

						Bind* bindCached = bindLru.find(bindHash);
						if (NULL == bindCached)
						{
							D3D12_GPU_DESCRIPTOR_HANDLE srvHandle[BGFX_MAX_COMPUTE_BINDINGS] = {};
							uint32_t samplerFlags[BGFX_MAX_COMPUTE_BINDINGS] = {};

							for (uint32_t ii = 0; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
							{
								const Binding& bind = renderBind.m_bind[ii];
								if (invalidHandle != bind.m_idx)
								{
									switch (bind.m_type)
									{
									case Binding::Image:
										{
											TextureD3D12& texture = m_textures[bind.m_idx];

											if (Access::Read != bind.m_un.m_compute.m_access)
											{
												texture.setState(m_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
												scratchBuffer.allocUav(srvHandle[ii], texture, bind.m_un.m_compute.m_mip);
											}
											else
											{
												texture.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
												scratchBuffer.allocSrv(srvHandle[ii], texture, bind.m_un.m_compute.m_mip);
												samplerFlags[ii] = texture.m_flags;
											}
										}
										break;

									case Binding::IndexBuffer:
									case Binding::VertexBuffer:
										{
											BufferD3D12& buffer = Binding::IndexBuffer == bind.m_type
												? m_indexBuffers[bind.m_idx]
												: m_vertexBuffers[bind.m_idx]
												;

											if (Access::Read != bind.m_un.m_compute.m_access)
											{
												buffer.setState(m_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
												scratchBuffer.allocUav(srvHandle[ii], buffer);
											}
											else
											{
												buffer.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
												scratchBuffer.allocSrv(srvHandle[ii], buffer);
											}
										}
										break;
									}
								}
							}

							uint16_t samplerStateIdx = getSamplerState(samplerFlags, BGFX_MAX_COMPUTE_BINDINGS, _render->m_colorPalette);
							if (samplerStateIdx != currentSamplerStateIdx)
							{
								currentSamplerStateIdx = samplerStateIdx;
								m_commandList->SetComputeRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
							}

							m_commandList->SetComputeRootDescriptorTable(Rdt::SRV, srvHandle[0]);
							m_commandList->SetComputeRootDescriptorTable(Rdt::UAV, srvHandle[0]);

							Bind bind;
							bind.m_srvHandle = srvHandle[0];
							bind.m_samplerStateIdx = samplerStateIdx;
							bindLru.add(bindHash, bind, 0);
						}
						else
						{
							uint16_t samplerStateIdx = bindCached->m_samplerStateIdx;
							if (samplerStateIdx != currentSamplerStateIdx)
							{
								currentSamplerStateIdx = samplerStateIdx;
								m_commandList->SetComputeRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
							}
							m_commandList->SetComputeRootDescriptorTable(Rdt::SRV, bindCached->m_srvHandle);
							m_commandList->SetComputeRootDescriptorTable(Rdt::UAV, bindCached->m_srvHandle);
						}
					}

					bool constantsChanged = false;
					if (compute.m_constBegin < compute.m_constEnd
					||  currentProgramIdx != key.m_program)
					{
						rendererUpdateUniforms(this, _render->m_uniformBuffer, compute.m_constBegin, compute.m_constEnd);

						currentProgramIdx = key.m_program;
						ProgramD3D12& program = m_program[currentProgramIdx];

						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						hasPredefined = 0 < program.m_numPredefined;
						constantsChanged = true;
					}

					if (constantsChanged
					||  hasPredefined)
					{
						ProgramD3D12& program = m_program[currentProgramIdx];
						viewState.setPredefined<4>(this, view, 0, program, _render, compute);
						commitShaderConstants(key.m_program, gpuAddress);
						m_commandList->SetComputeRootConstantBufferView(Rdt::CBV, gpuAddress);
					}

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferD3D12& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];

						uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: compute.m_numIndirect
							;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
//							m_commandList->ExecuteIndirect(ptr, args);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						m_commandList->Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);
					}

					continue;
				}

				const RenderDraw& draw = renderItem.draw;

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
				uint64_t changedStencil = (currentState.m_stencil ^ draw.m_stencil) & BGFX_STENCIL_FUNC_REF_MASK;
				currentState.m_stencil = newStencil;

				if (viewChanged
				||  wasCompute)
				{
					if (wasCompute)
					{
						wasCompute = false;
					}

					if (BX_ENABLED(BGFX_CONFIG_DEBUG_PIX) )
					{
						BX_UNUSED(s_viewNameW);
// 						wchar_t* viewNameW = s_viewNameW[view];
// 						viewNameW[3] = L' ';
// 						PIX_ENDEVENT();
// 						PIX_BEGINEVENT(D3DCOLOR_DRAW, viewNameW);
					}

					commandListChanged = true;
				}

				if (commandListChanged)
				{
					commandListChanged = false;

					m_commandList->SetGraphicsRootSignature(m_rootSignature);
					ID3D12DescriptorHeap* heaps[] = {
						m_samplerAllocator.getHeap(),
						scratchBuffer.getHeap(),
					};
					m_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);

					currentPso             = NULL;
					currentBindHash        = 0;
					currentSamplerStateIdx = invalidHandle;
					currentProgramIdx      = invalidHandle;
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					currentBind.clear();

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
				}

				rendererUpdateUniforms(this, _render->m_uniformBuffer, draw.m_constBegin, draw.m_constEnd);

				if (isValid(draw.m_stream[0].m_handle) )
				{
					const uint64_t state = draw.m_stateFlags;
					bool hasFactor = 0
						|| f0 == (state & f0)
						|| f1 == (state & f1)
						|| f2 == (state & f2)
						|| f3 == (state & f3)
						;

					const VertexBufferD3D12& vb = m_vertexBuffers[draw.m_stream[0].m_handle.idx];
					uint16_t declIdx = !isValid(vb.m_decl) ? draw.m_stream[0].m_decl.idx : vb.m_decl.idx;

					ID3D12PipelineState* pso =
						getPipelineState(state
							, draw.m_stencil
							, declIdx
							, key.m_program
							, uint8_t(draw.m_instanceDataStride/16)
							);

					uint16_t scissor = draw.m_scissor;
					uint32_t bindHash = bx::hashMurmur2A(renderBind.m_bind, sizeof(renderBind.m_bind) );
					if (currentBindHash != bindHash
					||  0 != changedStencil
					|| (hasFactor && blendFactor != draw.m_rgba)
					|| (0 != (BGFX_STATE_PT_MASK & changedFlags)
					||  prim.m_topology != s_primInfo[primIndex].m_topology)
					||  currentState.m_scissor != scissor
					||  pso != currentPso
					||  hasOcclusionQuery)
					{
						m_batch.flush(m_commandList);
					}

					if (currentBindHash != bindHash)
					{
						currentBindHash  = bindHash;

						Bind* bindCached = bindLru.find(bindHash);
						if (NULL == bindCached)
						{
							D3D12_GPU_DESCRIPTOR_HANDLE srvHandle[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
							uint32_t samplerFlags[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
							{
								srvHandle[0].ptr = 0;
								for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
								{
									const Binding& bind = renderBind.m_bind[stage];
									if (invalidHandle != bind.m_idx)
									{
										switch (bind.m_type)
										{
										case Binding::Texture:
											{
												TextureD3D12& texture = m_textures[bind.m_idx];
												texture.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
												scratchBuffer.allocSrv(srvHandle[stage], texture);
												samplerFlags[stage] = (0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & bind.m_un.m_draw.m_textureFlags)
													? bind.m_un.m_draw.m_textureFlags
													: texture.m_flags
													) & (BGFX_TEXTURE_SAMPLER_BITS_MASK | BGFX_TEXTURE_BORDER_COLOR_MASK)
													;
											}
											break;

										case Binding::IndexBuffer:
										case Binding::VertexBuffer:
											{
												BufferD3D12& buffer = Binding::IndexBuffer == bind.m_type
													? m_indexBuffers[bind.m_idx]
													: m_vertexBuffers[bind.m_idx]
													;

												if (Access::Read != bind.m_un.m_compute.m_access)
												{
													// The api functions prevent binding with Access::Write,
													// but might as well allow it in here for future-proofing
													buffer.setState(m_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
													scratchBuffer.allocUav(srvHandle[stage], buffer);
												}
												else
												{
													buffer.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
													scratchBuffer.allocSrv(srvHandle[stage], buffer);
												}
											}
											break;
										}
									}
									else
									{
										bx::memCopy(&srvHandle[stage], &srvHandle[0], sizeof(D3D12_GPU_DESCRIPTOR_HANDLE) );
										samplerFlags[stage] = 0;
									}
								}
							}

							if (srvHandle[0].ptr != 0)
							{
								uint16_t samplerStateIdx = getSamplerState(samplerFlags, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, _render->m_colorPalette);
								if (samplerStateIdx != currentSamplerStateIdx)
								{
									currentSamplerStateIdx = samplerStateIdx;
									m_commandList->SetGraphicsRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
								}

								m_commandList->SetGraphicsRootDescriptorTable(Rdt::SRV, srvHandle[0]);

								Bind bind;
								bind.m_srvHandle = srvHandle[0];
								bind.m_samplerStateIdx = samplerStateIdx;
								bindLru.add(bindHash, bind, 0);
							}
						}
						else
						{
							uint16_t samplerStateIdx = bindCached->m_samplerStateIdx;
							if (samplerStateIdx != currentSamplerStateIdx)
							{
								currentSamplerStateIdx = samplerStateIdx;
								m_commandList->SetGraphicsRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
							}
							m_commandList->SetGraphicsRootDescriptorTable(Rdt::SRV, bindCached->m_srvHandle);
						}
					}

					if (0 != changedStencil)
					{
						const uint32_t fstencil = unpackStencil(0, draw.m_stencil);
						const uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
						m_commandList->OMSetStencilRef(ref);
					}

					if (hasFactor
					&&  blendFactor != draw.m_rgba)
					{
						blendFactor = draw.m_rgba;

						float bf[4];
						bf[0] = ( (draw.m_rgba>>24)     )/255.0f;
						bf[1] = ( (draw.m_rgba>>16)&0xff)/255.0f;
						bf[2] = ( (draw.m_rgba>> 8)&0xff)/255.0f;
						bf[3] = ( (draw.m_rgba    )&0xff)/255.0f;
						m_commandList->OMSetBlendFactor(bf);
					}

					if (0 != (BGFX_STATE_PT_MASK & changedFlags)
					||  prim.m_topology != s_primInfo[primIndex].m_topology)
					{
						const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
						primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
						prim = s_primInfo[primIndex];
						m_commandList->IASetPrimitiveTopology(prim.m_topology);
					}

					if (currentState.m_scissor != scissor)
					{
						currentState.m_scissor = scissor;

						if (UINT16_MAX == scissor)
						{
							if (restoreScissor
							||  viewHasScissor)
							{
								restoreScissor = false;
								D3D12_RECT rc;
								rc.left   = viewScissorRect.m_x;
								rc.top    = viewScissorRect.m_y;
								rc.right  = viewScissorRect.m_x + viewScissorRect.m_width;
								rc.bottom = viewScissorRect.m_y + viewScissorRect.m_height;
								m_commandList->RSSetScissorRects(1, &rc);
							}
						}
						else
						{
							restoreScissor = true;
							Rect scissorRect;
							scissorRect.setIntersect(viewScissorRect,_render->m_rectCache.m_cache[scissor]);
							if (scissorRect.isZeroArea() )
							{
								continue;
							}

							D3D12_RECT rc;
							rc.left   = scissorRect.m_x;
							rc.top    = scissorRect.m_y;
							rc.right  = scissorRect.m_x + scissorRect.m_width;
							rc.bottom = scissorRect.m_y + scissorRect.m_height;
							m_commandList->RSSetScissorRects(1, &rc);
						}
					}

					if (pso != currentPso)
					{
						currentPso = pso;
						m_commandList->SetPipelineState(pso);
					}

					bool constantsChanged = false;
					if (draw.m_constBegin < draw.m_constEnd
					||  currentProgramIdx != key.m_program
					||  BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						currentProgramIdx = key.m_program;
						ProgramD3D12& program = m_program[currentProgramIdx];

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

						hasPredefined = 0 < program.m_numPredefined;
						constantsChanged = true;
					}

					if (constantsChanged
					||  hasPredefined)
					{
						ProgramD3D12& program = m_program[currentProgramIdx];
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
						viewState.setPredefined<4>(this, view, 0, program, _render, draw);
						commitShaderConstants(key.m_program, gpuAddress);
					}

					uint32_t numIndices        = m_batch.draw(m_commandList, gpuAddress, draw);
					uint32_t numPrimsSubmitted = numIndices / prim.m_div - prim.m_sub;
					uint32_t numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += draw.m_numInstances;
					statsNumIndices                   += numIndices;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(m_commandList, _render, draw.m_occlusionQuery);
						m_batch.flush(m_commandList);
						m_occlusionQuery.end(m_commandList);
					}
				}
			}

			m_batch.end(m_commandList);
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin = last;

		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::int64_min(min, frameTime);
		max = bx::int64_max(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		static int64_t presentMin = m_presentElapsed;
		static int64_t presentMax = m_presentElapsed;
		presentMin = bx::int64_min(presentMin, m_presentElapsed);
		presentMax = bx::int64_max(presentMax, m_presentElapsed);

		m_gpuTimer.end(m_commandList);

		do
		{
			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
			elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
		}
		while (m_gpuTimer.get() );

		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		perfStats.cpuTimeEnd    = now;
		perfStats.cpuTimerFreq  = timerFreq;
		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.maxGpuLatency = maxGpuLatency;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
//			PIX_BEGINEVENT(D3DCOLOR_FRAME, L"debugstats");

//			m_needPresent = true;
			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0 / freq;

				tvm.clear();
				uint16_t pos = 0;
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f
					, " %s (FL %d.%d) / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					, (m_featureLevel >> 12) & 0xf
					, (m_featureLevel >>  8) & 0xf
					);

				const DXGI_ADAPTER_DESC& desc = m_adapterDesc;
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

#if BX_PLATFORM_WINDOWS
				DXGI_QUERY_VIDEO_MEMORY_INFO vmi[2];
				DX_CHECK(m_adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL,     &vmi[0]) );
				DX_CHECK(m_adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL, &vmi[1]) );

				for (uint32_t ii = 0; ii < BX_COUNTOF(vmi); ++ii)
				{
					const DXGI_QUERY_VIDEO_MEMORY_INFO& memInfo = vmi[ii];

					char budget[16];
					bx::prettify(budget, BX_COUNTOF(budget), memInfo.Budget);

					char currentUsage[16];
					bx::prettify(currentUsage, BX_COUNTOF(currentUsage), memInfo.CurrentUsage);

					char availableForReservation[16];
					bx::prettify(availableForReservation, BX_COUNTOF(currentUsage), memInfo.AvailableForReservation);

					char currentReservation[16];
					bx::prettify(currentReservation, BX_COUNTOF(currentReservation), memInfo.CurrentReservation);

					tvm.printf(0, pos++, 0x8f, "   %s - Budget: %10s, Usage: %10s, AvailRes: %10s, CurrRes: %10s "
						, 0 == ii ? "Local    " : "Non-local"
						, budget
						, currentUsage
						, availableForReservation
						, currentReservation
						);
				}
#endif // BX_PLATFORM_WINDOWS

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "       Frame: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);
				tvm.printf(10, pos++, 0x8e, "     Present: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] "
					, double(m_presentElapsed)*toMs
					, double(presentMin)*toMs
					, double(presentMax)*toMs
					);

				char hmd[16];
				bx::snprintf(hmd, BX_COUNTOF(hmd), ", [%c] HMD ", hmdEnabled ? '\xfe' : ' ');

				const uint32_t msaa = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8e, " Reset flags: [%c] vsync, [%c] MSAAx%d%s, [%c] MaxAnisotropy "
					, !!(m_resolution.m_flags&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, ", no-HMD "
					, !!(m_resolution.m_flags&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(elapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "   Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] "
					, _render->m_num
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					);

				for (uint32_t ii = 0; ii < BX_COUNTOF(s_primName); ++ii)
				{
					tvm.printf(10, pos++, 0x8e, "   %9s: %7d (#inst: %5d), submitted: %7d "
						, s_primName[ii]
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				tvm.printf(10, pos++, 0x8e, "       Batch: %7dx%d indirect, %7d immediate "
					, m_batch.m_stats.m_numIndirect[BatchD3D12::Draw]
					, m_batch.m_maxDrawPerBatch
					, m_batch.m_stats.m_numImmediate[BatchD3D12::Draw]
					);

				tvm.printf(10, pos++, 0x8e, "              %7dx%d indirect, %7d immediate "
					, m_batch.m_stats.m_numIndirect[BatchD3D12::DrawIndexed]
					, m_batch.m_maxDrawPerBatch
					, m_batch.m_stats.m_numImmediate[BatchD3D12::DrawIndexed]
					);

				if (NULL != m_renderdocdll)
				{
					tvm.printf(tvm.m_width-27, 0, 0x1f, " [F11 - RenderDoc capture] ");
				}

				tvm.printf(10, pos++, 0x8e, "      Indices: %7d ", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8e, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8e, " State cache:                        ");
				tvm.printf(10, pos++, 0x8e, " PSO    | Sampler | Bind   | Queued  ");
				tvm.printf(10, pos++, 0x8e, " %6d |  %6d | %6d | %6d  "
					, m_pipelineStateCache.getCount()
					, m_samplerStateCache.getCount()
					, bindLru.getCount()
					, m_cmd.m_control.available()
					);
				pos++;

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8e, "     Capture: %7.4f [ms] ", captureMs);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms] ", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms] ", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
				presentMin = m_presentElapsed;
				presentMax = m_presentElapsed;
			}

			blit(this, _textVideoMemBlitter, tvm);

//			PIX_ENDEVENT();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
//			PIX_BEGINEVENT(D3DCOLOR_FRAME, L"debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

//			PIX_ENDEVENT();
		}

		setResourceBarrier(m_commandList
			, m_backBufferColor[m_backBufferColorIdx]
			, D3D12_RESOURCE_STATE_RENDER_TARGET
			, D3D12_RESOURCE_STATE_PRESENT
			);
		m_backBufferColorFence[m_backBufferColorIdx] = kick();
	}

} /* namespace d3d12 */ } // namespace bgfx

#else

namespace bgfx { namespace d3d12
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace d3d12 */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D12

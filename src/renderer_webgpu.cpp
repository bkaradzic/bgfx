/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_WEBGPU
#	if BX_PLATFORM_OSX
#		include <MetalKit/MetalKit.h>
#		include <Cocoa/Cocoa.h>
#	endif // BX_PLATFORM_OSX
#	include <bx/pixelformat.h>
#	include "renderer_webgpu.h"

namespace bgfx { namespace wgpu
{
	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	inline void setViewType(ViewId _view, const bx::StringView _str)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION || BGFX_CONFIG_PROFILER) )
		{
			bx::memCopy(&s_viewName[_view][3], _str.getPtr(), _str.getLength() );
		}
	}

	struct PrimInfo
	{
		WGPUPrimitiveTopology m_topology;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
		WGPUIndexFormat m_stripIndexFormat[2];
	};

	static const PrimInfo s_primInfo[] =
	{
		{ WGPUPrimitiveTopology_TriangleList,  3, 3, 0, { WGPUIndexFormat_Undefined, WGPUIndexFormat_Undefined } },
		{ WGPUPrimitiveTopology_TriangleStrip, 3, 1, 2, { WGPUIndexFormat_Uint16,    WGPUIndexFormat_Uint32    } },
		{ WGPUPrimitiveTopology_LineList,      2, 2, 0, { WGPUIndexFormat_Undefined, WGPUIndexFormat_Undefined } },
		{ WGPUPrimitiveTopology_LineStrip,     2, 1, 1, { WGPUIndexFormat_Uint16,    WGPUIndexFormat_Uint32    } },
		{ WGPUPrimitiveTopology_PointList,     1, 1, 0, { WGPUIndexFormat_Undefined, WGPUIndexFormat_Undefined } },
		{ WGPUPrimitiveTopology_Undefined,     0, 0, 0, { WGPUIndexFormat_Undefined, WGPUIndexFormat_Undefined } },
	};
	static_assert(Topology::Count == BX_COUNTOF(s_primInfo)-1);

	static const uint32_t s_msaa[] =
	{
		1,
		1, // 2 is not supported.
		4,
		4,
		4,
	};

	static const WGPUVertexFormat s_attribType[][4][2] =
	{
		{ // Uint8
			{ WGPUVertexFormat_Uint8,     WGPUVertexFormat_Unorm8    },
			{ WGPUVertexFormat_Uint8x2,   WGPUVertexFormat_Unorm8x2  },
			{ WGPUVertexFormat_Uint8x4,   WGPUVertexFormat_Unorm8x4  },
			{ WGPUVertexFormat_Uint8x4,   WGPUVertexFormat_Unorm8x4  },
		},
		{ // Uint10
			{ WGPUVertexFormat_Force32,   WGPUVertexFormat_Force32   },
			{ WGPUVertexFormat_Force32,   WGPUVertexFormat_Force32   },
			{ WGPUVertexFormat_Force32,   WGPUVertexFormat_Force32   },
			{ WGPUVertexFormat_Force32,   WGPUVertexFormat_Force32   },
		},
		{ // Int16
			{ WGPUVertexFormat_Sint16,    WGPUVertexFormat_Snorm16   },
			{ WGPUVertexFormat_Sint16x2,  WGPUVertexFormat_Snorm16x2 },
			{ WGPUVertexFormat_Sint16x4,  WGPUVertexFormat_Snorm16x4 },
			{ WGPUVertexFormat_Sint16x4,  WGPUVertexFormat_Snorm16x4 },
		},
		{ // Half
			{ WGPUVertexFormat_Float16,   WGPUVertexFormat_Float16   },
			{ WGPUVertexFormat_Float16x2, WGPUVertexFormat_Float16x2 },
			{ WGPUVertexFormat_Float16x4, WGPUVertexFormat_Float16x4 },
			{ WGPUVertexFormat_Float16x4, WGPUVertexFormat_Float16x4 },
		},
		{ // Float
			{ WGPUVertexFormat_Float32,   WGPUVertexFormat_Float32   },
			{ WGPUVertexFormat_Float32x2, WGPUVertexFormat_Float32x2 },
			{ WGPUVertexFormat_Float32x3, WGPUVertexFormat_Float32x3 },
			{ WGPUVertexFormat_Float32x4, WGPUVertexFormat_Float32x4 },
		},
	};
	static_assert(AttribType::Count == BX_COUNTOF(s_attribType) );

	static const WGPUCullMode s_cullMode[] =
	{
		WGPUCullMode_None,
		WGPUCullMode_Front,
		WGPUCullMode_Back,
	};

	static const WGPUBlendFactor s_blendFactor[][2] =
	{
		{ WGPUBlendFactor_Undefined,          WGPUBlendFactor_Undefined        }, // ignored
		{ WGPUBlendFactor_Zero,               WGPUBlendFactor_Zero             }, // ZERO
		{ WGPUBlendFactor_One,                WGPUBlendFactor_One              }, // ONE
		{ WGPUBlendFactor_Src,                WGPUBlendFactor_SrcAlpha         }, // SRC_COLOR
		{ WGPUBlendFactor_OneMinusSrc,        WGPUBlendFactor_OneMinusSrcAlpha }, // INV_SRC_COLOR
		{ WGPUBlendFactor_SrcAlpha,           WGPUBlendFactor_SrcAlpha         }, // SRC_ALPHA
		{ WGPUBlendFactor_OneMinusSrcAlpha,   WGPUBlendFactor_OneMinusSrcAlpha }, // INV_SRC_ALPHA
		{ WGPUBlendFactor_DstAlpha,           WGPUBlendFactor_DstAlpha         }, // DST_ALPHA
		{ WGPUBlendFactor_OneMinusDstAlpha,   WGPUBlendFactor_OneMinusDstAlpha }, // INV_DST_ALPHA
		{ WGPUBlendFactor_Dst,                WGPUBlendFactor_DstAlpha         }, // DST_COLOR
		{ WGPUBlendFactor_OneMinusDst,        WGPUBlendFactor_OneMinusDstAlpha }, // INV_DST_COLOR
		{ WGPUBlendFactor_SrcAlphaSaturated,  WGPUBlendFactor_One              }, // SRC_ALPHA_SAT
		{ WGPUBlendFactor_Constant,           WGPUBlendFactor_Constant         }, // FACTOR
		{ WGPUBlendFactor_OneMinusConstant,   WGPUBlendFactor_OneMinusConstant }, // INV_FACTOR
	};

	static const WGPUBlendOperation s_blendEquation[] =
	{
		WGPUBlendOperation_Add,
		WGPUBlendOperation_Subtract,
		WGPUBlendOperation_ReverseSubtract,
		WGPUBlendOperation_Min,
		WGPUBlendOperation_Max,
	};

	static const WGPUCompareFunction s_cmpFunc[] =
	{
		WGPUCompareFunction_Always, // ignored
		WGPUCompareFunction_Less,
		WGPUCompareFunction_LessEqual,
		WGPUCompareFunction_Equal,
		WGPUCompareFunction_GreaterEqual,
		WGPUCompareFunction_Greater,
		WGPUCompareFunction_NotEqual,
		WGPUCompareFunction_Never,
		WGPUCompareFunction_Always,
	};

	static const WGPUStencilOperation s_stencilOp[] =
	{
		WGPUStencilOperation_Zero,
		WGPUStencilOperation_Keep,
		WGPUStencilOperation_Replace,
		WGPUStencilOperation_IncrementWrap,
		WGPUStencilOperation_IncrementClamp,
		WGPUStencilOperation_DecrementWrap,
		WGPUStencilOperation_DecrementClamp,
		WGPUStencilOperation_Invert,
	};

	static const WGPUStorageTextureAccess s_storageTextureAccess[] =
	{
		WGPUStorageTextureAccess_ReadOnly,
		WGPUStorageTextureAccess_WriteOnly,
		WGPUStorageTextureAccess_ReadWrite,
	};
	static_assert(BX_COUNTOF(s_storageTextureAccess) == Access::Count, "");

	static const WGPUAddressMode s_textureAddress[] =
	{
		WGPUAddressMode_Repeat,       // 0 - wrap
		WGPUAddressMode_MirrorRepeat, // 1 - mirror
		WGPUAddressMode_ClampToEdge,  // 2 - clamp
		WGPUAddressMode_ClampToEdge,  // 3 - border
	};
	static_assert(BX_COUNTOF(s_textureAddress) == (BGFX_SAMPLER_U_MASK>>BGFX_SAMPLER_U_SHIFT)+1, "");

	static const WGPUFilterMode s_textureFilterMinMag[] =
	{
		WGPUFilterMode_Linear,    // 0 - linear
		WGPUFilterMode_Nearest,   // 1 - point
		WGPUFilterMode_Linear,    // 2 - anisotropic
		WGPUFilterMode_Undefined,
	};
	static_assert(BX_COUNTOF(s_textureFilterMinMag) == (BGFX_SAMPLER_MAG_MASK>>BGFX_SAMPLER_MAG_SHIFT)+1, "");

	static const WGPUMipmapFilterMode s_textureFilterMip[] =
	{
		WGPUMipmapFilterMode_Linear,
		WGPUMipmapFilterMode_Nearest,
	};
	static_assert(BX_COUNTOF(s_textureFilterMip) == (BGFX_SAMPLER_MIP_MASK>>BGFX_SAMPLER_MIP_SHIFT)+1, "");

	static const WGPUTextureSampleType s_textureComponentType[] =
	{
		WGPUTextureSampleType_Float,
		WGPUTextureSampleType_Sint,
		WGPUTextureSampleType_Uint,
		WGPUTextureSampleType_Depth,
		WGPUTextureSampleType_UnfilterableFloat,
	};
	static_assert(TextureComponentType::Count == BX_COUNTOF(s_textureComponentType) );

	static const WGPUTextureViewDimension s_textureDimension[] =
	{
		WGPUTextureViewDimension_1D,
		WGPUTextureViewDimension_2D,
		WGPUTextureViewDimension_2DArray,
		WGPUTextureViewDimension_Cube,
		WGPUTextureViewDimension_CubeArray,
		WGPUTextureViewDimension_3D,
	};
	static_assert(TextureDimension::Count == BX_COUNTOF(s_textureDimension) );

	struct TextureFormatInfo
	{
		WGPUTextureFormat m_fmt;
		WGPUTextureFormat m_fmtSrgb;
		WGPUTextureSampleType m_samplerType;
		bool m_blendable;
		WGPUTextureComponentSwizzle m_mapping;
	};

	static const TextureFormatInfo s_textureFormat[] =
	{
#define $_ WGPUComponentSwizzle_Undefined
#define $0 WGPUComponentSwizzle_Zero
#define $1 WGPUComponentSwizzle_One
#define $R WGPUComponentSwizzle_R
#define $G WGPUComponentSwizzle_G
#define $B WGPUComponentSwizzle_B
#define $A WGPUComponentSwizzle_A
		{ WGPUTextureFormat_BC1RGBAUnorm,        WGPUTextureFormat_BC1RGBAUnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC1
		{ WGPUTextureFormat_BC2RGBAUnorm,        WGPUTextureFormat_BC2RGBAUnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC2
		{ WGPUTextureFormat_BC3RGBAUnorm,        WGPUTextureFormat_BC3RGBAUnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC3
		{ WGPUTextureFormat_BC4RUnorm,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC4
		{ WGPUTextureFormat_BC5RGUnorm,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC5
		{ WGPUTextureFormat_BC6HRGBFloat,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC6H
		{ WGPUTextureFormat_BC7RGBAUnorm,        WGPUTextureFormat_BC7RGBAUnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BC7
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ETC1
		{ WGPUTextureFormat_ETC2RGB8Unorm,       WGPUTextureFormat_ETC2RGB8UnormSrgb,   WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ETC2
		{ WGPUTextureFormat_ETC2RGBA8Unorm,      WGPUTextureFormat_ETC2RGBA8UnormSrgb,  WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ETC2A
		{ WGPUTextureFormat_ETC2RGB8A1Unorm,     WGPUTextureFormat_ETC2RGB8A1UnormSrgb, WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ETC2A1
		{ WGPUTextureFormat_EACR11Unorm,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // EACR11
		{ WGPUTextureFormat_EACR11Snorm,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // EACR11S
		{ WGPUTextureFormat_EACRG11Unorm,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // EACRG11
		{ WGPUTextureFormat_EACRG11Snorm,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // EACRG11S
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC12
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC14
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC12A
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC14A
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC22
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // PTC24
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ATC
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ATCE
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ATCI
		{ WGPUTextureFormat_ASTC4x4Unorm,        WGPUTextureFormat_ASTC4x4UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC4x4
		{ WGPUTextureFormat_ASTC5x4Unorm,        WGPUTextureFormat_ASTC5x4UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC5x4
		{ WGPUTextureFormat_ASTC5x5Unorm,        WGPUTextureFormat_ASTC5x5UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC5x5
		{ WGPUTextureFormat_ASTC6x5Unorm,        WGPUTextureFormat_ASTC6x5UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC6x5
		{ WGPUTextureFormat_ASTC6x6Unorm,        WGPUTextureFormat_ASTC6x6UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC6x6
		{ WGPUTextureFormat_ASTC8x5Unorm,        WGPUTextureFormat_ASTC8x5UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC8x5
		{ WGPUTextureFormat_ASTC8x6Unorm,        WGPUTextureFormat_ASTC8x6UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC8x6
		{ WGPUTextureFormat_ASTC8x8Unorm,        WGPUTextureFormat_ASTC8x8UnormSrgb,    WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC8x8
		{ WGPUTextureFormat_ASTC10x5Unorm,       WGPUTextureFormat_ASTC10x5UnormSrgb,   WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC10x5
		{ WGPUTextureFormat_ASTC10x6Unorm,       WGPUTextureFormat_ASTC10x6UnormSrgb,   WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC10x6
		{ WGPUTextureFormat_ASTC10x8Unorm,       WGPUTextureFormat_ASTC10x8UnormSrgb,   WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC10x8
		{ WGPUTextureFormat_ASTC10x10Unorm,      WGPUTextureFormat_ASTC10x10UnormSrgb,  WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC10x10
		{ WGPUTextureFormat_ASTC12x10Unorm,      WGPUTextureFormat_ASTC12x10UnormSrgb,  WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC12x10
		{ WGPUTextureFormat_ASTC12x12Unorm,      WGPUTextureFormat_ASTC12x12UnormSrgb,  WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // ASTC12x12
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Undefined,         false, { $_, $_, $_, $_ } }, // Unknown
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R1
		{ WGPUTextureFormat_R8Unorm,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $0, $0, $0, $R } }, // A8
		{ WGPUTextureFormat_R8Unorm,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R8
		{ WGPUTextureFormat_R8Sint,              WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R8I
		{ WGPUTextureFormat_R8Uint,              WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R8U
		{ WGPUTextureFormat_R8Snorm,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R8S
		{ WGPUTextureFormat_R16Unorm,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R16
		{ WGPUTextureFormat_R16Sint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R16I
		{ WGPUTextureFormat_R16Uint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R16U
		{ WGPUTextureFormat_R16Float,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R16F
		{ WGPUTextureFormat_R16Snorm,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R16S
		{ WGPUTextureFormat_R32Sint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R32I
		{ WGPUTextureFormat_R32Uint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R32U
		{ WGPUTextureFormat_R32Float,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // R32F
		{ WGPUTextureFormat_RG8Unorm,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG8
		{ WGPUTextureFormat_RG8Sint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG8I
		{ WGPUTextureFormat_RG8Uint,             WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG8U
		{ WGPUTextureFormat_RG8Snorm,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG8S
		{ WGPUTextureFormat_RG16Unorm,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG16
		{ WGPUTextureFormat_RG16Sint,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG16I
		{ WGPUTextureFormat_RG16Uint,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG16U
		{ WGPUTextureFormat_RG16Float,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG16F
		{ WGPUTextureFormat_RG16Snorm,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG16S
		{ WGPUTextureFormat_RG32Sint,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG32I
		{ WGPUTextureFormat_RG32Uint,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG32U
		{ WGPUTextureFormat_RG32Float,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // RG32F
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB8
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB8I
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB8U
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB8S
		{ WGPUTextureFormat_RGB9E5Ufloat,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB9E5F
		{ WGPUTextureFormat_BGRA8Unorm,          WGPUTextureFormat_BGRA8UnormSrgb,      WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BGRA8
		{ WGPUTextureFormat_RGBA8Unorm,          WGPUTextureFormat_RGBA8UnormSrgb,      WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA8
		{ WGPUTextureFormat_RGBA8Sint,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA8I
		{ WGPUTextureFormat_RGBA8Uint,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA8U
		{ WGPUTextureFormat_RGBA8Snorm,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA8S
		{ WGPUTextureFormat_RGBA16Unorm,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA16
		{ WGPUTextureFormat_RGBA16Sint,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA16I
		{ WGPUTextureFormat_RGBA16Uint,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA16U
		{ WGPUTextureFormat_RGBA16Float,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA16F
		{ WGPUTextureFormat_RGBA16Snorm,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA16S
		{ WGPUTextureFormat_RGBA32Sint,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA32I
		{ WGPUTextureFormat_RGBA32Uint,          WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA32U
		{ WGPUTextureFormat_RGBA32Float,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // RGBA32F
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // B5G6R5
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // R5G6B5
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BGRA4
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGBA4
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // BGR5A1
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB5A1
		{ WGPUTextureFormat_RGB10A2Unorm,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RGB10A2
		{ WGPUTextureFormat_RG11B10Ufloat,       WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Float,             true,  { $_, $_, $_, $_ } }, // RG11B10F
		{ WGPUTextureFormat_Undefined,           WGPUTextureFormat_Undefined,           WGPUTextureSampleType_Undefined,         false, { $_, $_, $_, $_ } }, // UnknownDepth
		{ WGPUTextureFormat_Depth16Unorm,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D16
		{ WGPUTextureFormat_Depth24Plus,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D24
		{ WGPUTextureFormat_Depth24PlusStencil8, WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D24S8
		{ WGPUTextureFormat_Depth32Float,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D32
		{ WGPUTextureFormat_Depth32Float,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D16F
		{ WGPUTextureFormat_Depth24Plus,         WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D24F
		{ WGPUTextureFormat_Depth32Float,        WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D32F
		{ WGPUTextureFormat_Stencil8,            WGPUTextureFormat_Undefined,           WGPUTextureSampleType_UnfilterableFloat, false, { $_, $_, $_, $_ } }, // D0S8
#undef $_
#undef $0
#undef $1
#undef $R
#undef $G
#undef $B
#undef $A
	};
	static_assert(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	static const char* s_backendType[] =
	{
		"Undefined",
		"Null",
		"WebGPU",
		"D3D11",
		"D3D12",
		"Metal",
		"Vulkan",
		"OpenGL",
		"OpenGLES",
	};

	static const char* s_adapterType[] =
	{
		"DiscreteGPU",
		"IntegratedGPU",
		"CPU",
		"Unknown",
	};

	template<typename Ty>
	struct FeatureT
	{
		Ty featureName;
		const char* name;
		bool optional;
		bool supported;

		static int32_t cmpFn(const void* _lhs, const void* _rhs)
		{
			const Ty lhs = ( (const FeatureT<Ty>*)(_lhs) )->featureName;
			const Ty rhs = ( (const FeatureT<Ty>*)(_rhs) )->featureName;
			return (lhs > rhs) - (lhs < rhs);
		}
	};

	using LanguageFeature = FeatureT<WGPUWGSLLanguageFeatureName>;

	static LanguageFeature s_languageFeature[] =
	{
#define LANGUAGE_FEATURE(_name) WGPUWGSLLanguageFeatureName_##_name, #_name

		{ LANGUAGE_FEATURE(ReadonlyAndReadwriteStorageTextures),  true, false },
		{ LANGUAGE_FEATURE(Packed4x8IntegerDotProduct),           true, false },
		{ LANGUAGE_FEATURE(UnrestrictedPointerParameters),        true, false },
		{ LANGUAGE_FEATURE(PointerCompositeAccess),               true, false },
		{ LANGUAGE_FEATURE(UniformBufferStandardLayout),          true, false },
		{ LANGUAGE_FEATURE(SubgroupId),                           true, false },
		{ LANGUAGE_FEATURE(ChromiumTestingUnimplemented),         true, false },
		{ LANGUAGE_FEATURE(ChromiumTestingUnsafeExperimental),    true, false },
		{ LANGUAGE_FEATURE(ChromiumTestingExperimental),          true, false },
		{ LANGUAGE_FEATURE(ChromiumTestingShippedWithKillswitch), true, false },
		{ LANGUAGE_FEATURE(ChromiumTestingShipped),               true, false },
		{ LANGUAGE_FEATURE(SizedBindingArray),                    true, false },
		{ LANGUAGE_FEATURE(TexelBuffers),                         true, false },
		{ LANGUAGE_FEATURE(ChromiumPrint),                        true, false },
		{ LANGUAGE_FEATURE(FragmentDepth),                        true, false },
		{ LANGUAGE_FEATURE(ImmediateAddressSpace),                true, false },
		{ LANGUAGE_FEATURE(SubgroupUniformity),                   true, false },
		{ LANGUAGE_FEATURE(TextureAndSamplerLet),                 true, false },

#undef LANGUAGE_FEATURE
	};

	using Feature = FeatureT<WGPUFeatureName>;

	static Feature s_feature[] =
	{
#define FEATURE(_name) WGPUFeatureName_##_name, #_name

		{ FEATURE(CoreFeaturesAndLimits),                                true, false },
		{ FEATURE(DepthClipControl),                                     true, false },
		{ FEATURE(Depth32FloatStencil8),                                 true, false },
		{ FEATURE(TextureCompressionBC),                                 true, false },
		{ FEATURE(TextureCompressionBCSliced3D),                         true, false },
		{ FEATURE(TextureCompressionETC2),                               true, false },
		{ FEATURE(TextureCompressionASTC),                               true, false },
		{ FEATURE(TextureCompressionASTCSliced3D),                       true, false },
		{ FEATURE(TimestampQuery),                                       true, false },
		{ FEATURE(IndirectFirstInstance),                                true, false },
		{ FEATURE(ShaderF16),                                            true, false },
		{ FEATURE(RG11B10UfloatRenderable),                              true, false },
		{ FEATURE(BGRA8UnormStorage),                                    true, false },
		{ FEATURE(Float32Filterable),                                    true, false },
		{ FEATURE(Float32Blendable),                                     true, false },
		{ FEATURE(ClipDistances),                                        true, false },
		{ FEATURE(DualSourceBlending),                                   true, false },
		{ FEATURE(Subgroups),                                            true, false },
		{ FEATURE(TextureFormatsTier1),                                  true, false },
		{ FEATURE(TextureFormatsTier2),                                  true, false },
		{ FEATURE(PrimitiveIndex),                                       true, false },
		{ FEATURE(TextureComponentSwizzle),                              true, false },
		{ FEATURE(DawnInternalUsages),                                   true, false },
		{ FEATURE(DawnMultiPlanarFormats),                               true, false },
		{ FEATURE(DawnNative),                                           true, false },
		{ FEATURE(ChromiumExperimentalTimestampQueryInsidePasses),       true, false },
		{ FEATURE(ImplicitDeviceSynchronization),                        true, false },
		{ FEATURE(TransientAttachments),                                 true, false },
		{ FEATURE(MSAARenderToSingleSampled),                            true, false },
		{ FEATURE(D3D11MultithreadProtected),                            true, false },
		{ FEATURE(ANGLETextureSharing),                                  true, false },
		{ FEATURE(PixelLocalStorageCoherent),                            true, false },
		{ FEATURE(PixelLocalStorageNonCoherent),                         true, false },
		{ FEATURE(Unorm16TextureFormats),                                true, false },
		{ FEATURE(MultiPlanarFormatExtendedUsages),                      true, false },
		{ FEATURE(MultiPlanarFormatP010),                                true, false },
		{ FEATURE(HostMappedPointer),                                    true, false },
		{ FEATURE(MultiPlanarRenderTargets),                             true, false },
		{ FEATURE(MultiPlanarFormatNv12a),                               true, false },
		{ FEATURE(FramebufferFetch),                                     true, false },
		{ FEATURE(BufferMapExtendedUsages),                              true, false },
		{ FEATURE(AdapterPropertiesMemoryHeaps),                         true, false },
		{ FEATURE(AdapterPropertiesD3D),                                 true, false },
		{ FEATURE(AdapterPropertiesVk),                                  true, false },
		{ FEATURE(DawnFormatCapabilities),                               true, false },
		{ FEATURE(DawnDrmFormatCapabilities),                            true, false },
		{ FEATURE(MultiPlanarFormatNv16),                                true, false },
		{ FEATURE(MultiPlanarFormatNv24),                                true, false },
		{ FEATURE(MultiPlanarFormatP210),                                true, false },
		{ FEATURE(MultiPlanarFormatP410),                                true, false },
		{ FEATURE(SharedTextureMemoryVkDedicatedAllocation),             true, false },
		{ FEATURE(SharedTextureMemoryAHardwareBuffer),                   true, false },
		{ FEATURE(SharedTextureMemoryDmaBuf),                            true, false },
		{ FEATURE(SharedTextureMemoryOpaqueFD),                          true, false },
		{ FEATURE(SharedTextureMemoryZirconHandle),                      true, false },
		{ FEATURE(SharedTextureMemoryDXGISharedHandle),                  true, false },
		{ FEATURE(SharedTextureMemoryD3D11Texture2D),                    true, false },
		{ FEATURE(SharedTextureMemoryIOSurface),                         true, false },
		{ FEATURE(SharedTextureMemoryEGLImage),                          true, false },
		{ FEATURE(SharedFenceVkSemaphoreOpaqueFD),                       true, false },
		{ FEATURE(SharedFenceSyncFD),                                    true, false },
		{ FEATURE(SharedFenceVkSemaphoreZirconHandle),                   true, false },
		{ FEATURE(SharedFenceDXGISharedHandle),                          true, false },
		{ FEATURE(SharedFenceMTLSharedEvent),                            true, false },
		{ FEATURE(SharedBufferMemoryD3D12Resource),                      true, false },
		{ FEATURE(StaticSamplers),                                       true, false },
		{ FEATURE(YCbCrVulkanSamplers),                                  true, false },
		{ FEATURE(ShaderModuleCompilationOptions),                       true, false },
		{ FEATURE(DawnLoadResolveTexture),                               true, false },
		{ FEATURE(DawnPartialLoadResolveTexture),                        true, false },
		{ FEATURE(MultiDrawIndirect),                                    true, false },
		{ FEATURE(DawnTexelCopyBufferRowAlignment),                      true, false },
		{ FEATURE(FlexibleTextureViews),                                 true, false },
		{ FEATURE(ChromiumExperimentalSubgroupMatrix),                   true, false },
		{ FEATURE(SharedFenceEGLSync),                                   true, false },
		{ FEATURE(DawnDeviceAllocatorControl),                           true, false },
		{ FEATURE(AdapterPropertiesWGPU),                                true, false },
		{ FEATURE(SharedBufferMemoryD3D12SharedMemoryFileMappingHandle), true, false },

#undef FEATURE
	};

	static WGPUFeatureName ifSupported(WGPUFeatureName _featureName)
	{
		const int32_t idx = bx::binarySearch(_featureName, s_feature, BX_COUNTOF(s_feature), sizeof(Feature), Feature::cmpFn);

		if (s_feature[idx].supported)
		{
			return _featureName;
		}

		return WGPUFeatureName_Force32;
	}

#	if USE_WEBGPU_DYNAMIC_LIB

#	define WGPU_IGNORE_____(_optional, _func)
#	define WGPU_IMPORT_FUNC(_optional, _func) WGPUProc##_func wgpu##_func
WGPU_IMPORT
#	undef WGPU_IGNORE_____
#	undef WGPU_IMPORT_FUNC

#	endif // USE_WEBGPU_DYNAMIC_LIB

#define WGPU_RELEASE_FUNC(_name)               \
	inline void wgpuRelease(WGPU##_name& _obj) \
	{                                          \
		if (NULL != _obj)                      \
		{                                      \
			wgpu##_name##Release(_obj);        \
			_obj = NULL;                       \
		}                                      \
	}

	WGPU_RELEASE

#undef WGPU_RELEASE_FUNC

#define WGPU_DESTROY_FUNC(_name)               \
	inline void wgpuDestroy(WGPU##_name& _obj) \
	{                                          \
		if (NULL != _obj)                      \
		{                                      \
			wgpu##_name##Destroy(_obj);        \
			wgpu##_name##Release(_obj);        \
			_obj = NULL;                       \
		}                                      \
	}

	WGPU_DESTROY

#undef WGPU_DESTROY_FUNC

	inline constexpr bx::StringView toStringView(const WGPUStringView& _str)
	{
		return bx::StringView(_str.data, int32_t(_str.length) );
	}

	static void trace(const WGPUStringView& _message)
	{
		if (NULL != _message.data
		&&     0 != _message.length)
		{
			BX_TRACE("WGPU: `%.*s`", _message.length, _message.data);
		}
	}

	static void deviceLostCb(
		  const WGPUDevice* _device
		, WGPUDeviceLostReason _reason
		, WGPUStringView _message
		, void* _userdata1
		, void* _userdata2
		)
	{
		BX_UNUSED(_device, _reason, _message, _userdata1, _userdata2);

		BX_TRACE("Reason: %d", _reason);

		trace(_message);
	}

	static uint32_t s_uncapturedError = 0;

	static bool wgpuErrorCheck()
	{
		BX_UNUSED(&wgpuErrorCheck);

		if (0 < s_uncapturedError)
		{
			BX_WARN(1 == s_uncapturedError
				, "Uncaptured error count is %d, which means that wgpu call that caused error wasn't wrapped with WGPU_CHECK macro!"
				, s_uncapturedError
				);

			s_uncapturedError = 0;

			return true;
		}

		return false;
	}

	static void uncapturedErrorCb(
		  const WGPUDevice* _device
		, WGPUErrorType _type
		, WGPUStringView _message
		, void* _userdata1
		, void* _userdata2
		)
	{
		BX_UNUSED(_device, _type, _message, _userdata1, _userdata2);

		BX_TRACE("WGPU uncaptured error!\n\nErrorType: %d\n\n%.*s\n"
			, _type
			, _message.length
			, _message.data
			);

		++s_uncapturedError;
	}

	static void popErrorScopeCb(
		  WGPUPopErrorScopeStatus _status
		, WGPUErrorType _type
		, WGPUStringView _message
		, void* _userdata1
		, void* _userdata2
		)
	{
		BX_UNUSED(_status, _type, _userdata1, _userdata2, &popErrorScopeCb);

		trace(_message);
	}

	struct RendererContextWGPU : public RendererContextI
	{
		RendererContextWGPU()
			: m_webgpuDll(NULL)
			, m_renderDocDll(NULL)
			, m_instance(NULL)
			, m_adapter(NULL)
			, m_device(NULL)
			, m_maxAnisotropy(1)
			, m_depthClamp(false)
			, m_wireframe(false)
		{
			BX_UNUSED(&popErrorScopeCb, &wgpuErrorCheck, s_backendType, s_adapterType);
		}

		~RendererContextWGPU()
		{
		}

		static void requestAdapterCb(
			  WGPURequestAdapterStatus _status
			, WGPUAdapter _adapter
			, WGPUStringView _message
			, void* _userdata1
			, void* _userdata2
			)
		{
			BX_UNUSED(_userdata2);

			trace(_message);

			if (WGPURequestAdapterStatus_Success != _status)
			{
				return;
			}

			RendererContextWGPU* renderCtx = (RendererContextWGPU*)_userdata1;
			renderCtx->m_adapter = _adapter;
		}

		static void requestDeviceCb(
			  WGPURequestDeviceStatus _status
			, WGPUDevice _device
			, WGPUStringView _message
			, void* _userdata1
			, void* _userdata2
			)
		{
			BX_UNUSED(_userdata2);

			trace(_message);

			if (WGPURequestDeviceStatus_Success != _status)
			{
				return;
			}

			RendererContextWGPU* renderCtx = (RendererContextWGPU*)_userdata1;
			renderCtx->m_device = _device;
		}

		bool init(const Init& _init)
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedWebGPU,
					InstanceCreated,
					AdapterCreated,
					DeviceCreated,
					QueueCreated,
					SwapChainCreated,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

//			m_fbh = BGFX_INVALID_HANDLE;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			setGraphicsDebuggerPresent(false
				|| NULL != m_renderDocDll
				);

			const bool headless = NULL == g_platformData.nwh;

			bool imported = true;

			m_webgpuDll = bx::dlopen(
#if BX_PLATFORM_WINDOWS
				"webgpu_dawn.dll"
//				"wgpu_native.dll"
#elif BX_PLATFORM_LINUX
				"libwebgpu_dawn.so"
//				"libwgpu_native.so"
#elif BX_PLATFORM_OSX
				"libwebgpu_dawn.dylib"
#else
				"webgpu?"
#endif //
				);

			if (NULL == m_webgpuDll)
			{
				BX_TRACE("Init error: Failed to load WebGPU dynamic library.");
				goto error;
			}

			errorState = ErrorState::LoadedWebGPU;

			BX_TRACE("Shared library functions:");

#if USE_WEBGPU_DYNAMIC_LIB

#	define WGPU_IGNORE_____(_optional, _func)
#	define WGPU_IMPORT_FUNC(_optional, _func)                                 \
		wgpu##_func = (WGPUProc##_func)bx::dlsym(m_webgpuDll, "wgpu" #_func); \
		BX_TRACE("\t%p wgpu" #_func, wgpu##_func);                            \
		imported &= _optional || NULL != wgpu##_func

WGPU_IMPORT

#	undef WGPU_IGNORE_____
#	undef WGPU_IMPORT_FUNC

#endif // USE_WEBGPU_DYNAMIC_LIB

			BX_TRACE("");

			if (!imported)
			{
				BX_TRACE("Init error: Failed to load shared library functions.");
				goto error;
			}

			{
				{
					WGPUInstanceFeatureName requiredFeatures[] =
					{
						WGPUInstanceFeatureName_TimedWaitAny,
						WGPUInstanceFeatureName_ShaderSourceSPIRV,
					};

					WGPUInstanceDescriptor instanceDesc =
					{
						.nextInChain          = NULL,
						.requiredFeatureCount = BX_COUNTOF(requiredFeatures),
						.requiredFeatures     = requiredFeatures,
						.requiredLimits       = NULL,
					};

					m_instance = wgpuCreateInstance(&instanceDesc);

					if (NULL == m_instance)
					{
						BX_TRACE("Failed to create instance!");
						goto error;
					}

					errorState = ErrorState::InstanceCreated;
				}

				{
					WGPURequestAdapterOptions rao =
					{
						.nextInChain          = NULL,
						.featureLevel         = WGPUFeatureLevel_Undefined,
						.powerPreference      = WGPUPowerPreference_HighPerformance,
						.forceFallbackAdapter = false,
						.backendType          = WGPUBackendType_Undefined,
						.compatibleSurface    = NULL,
					};

					WGPUFutureWaitInfo fwi =
					{
						.future = wgpuInstanceRequestAdapter(m_instance, &rao,
							{
								.nextInChain = NULL,
								.mode        = WGPUCallbackMode_WaitAnyOnly,
								.callback    = requestAdapterCb,
								.userdata1   = this,
								.userdata2   = NULL,
							}),
						.completed = false,
					};

					WGPUWaitStatus waitStatus = wgpuInstanceWaitAny(m_instance, 1, &fwi, UINT64_MAX);

					if (WGPUWaitStatus_Success != waitStatus
					||  NULL == m_adapter)
					{
						goto error;
					}

					errorState = ErrorState::AdapterCreated;
				}

				{
					WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures;
					wgpuInstanceGetWGSLLanguageFeatures(m_instance, &supportedWGSLLanguageFeatures);

					BX_ASSERT(bx::isSorted(s_languageFeature, BX_COUNTOF(s_languageFeature), LanguageFeature::cmpFn), "Feature table must be sorted!");

					BX_TRACE("Supported WGSL language features (%d):", supportedWGSLLanguageFeatures.featureCount);

					for (uint32_t ii = 0; ii < BX_COUNTOF(s_languageFeature); ++ii)
					{
						LanguageFeature& feature = s_languageFeature[ii];
						feature.supported = false;
					}

					for (uint32_t ii = 0; ii < uint32_t(supportedWGSLLanguageFeatures.featureCount); ++ii)
					{
						const WGPUWGSLLanguageFeatureName featureName = supportedWGSLLanguageFeatures.features[ii];
						const int32_t idx = bx::binarySearch(featureName, s_languageFeature, BX_COUNTOF(s_languageFeature), sizeof(LanguageFeature), LanguageFeature::cmpFn);

						if (0 <= idx)
						{
							LanguageFeature& feature = s_languageFeature[idx];
							BX_TRACE("\t%5x - %s", featureName, feature.name);
							feature.supported = true;
						}
						else
						{
							BX_TRACE("\t%5x - ** Unknown?! **", featureName);
						}
					}

					wgpuSupportedWGSLLanguageFeaturesFreeMembers(supportedWGSLLanguageFeatures);

					BX_TRACE("");

					WGPUSupportedFeatures supportedFeatures;
					wgpuAdapterGetFeatures(m_adapter, &supportedFeatures);

					BX_TRACE("Supported features (%d):", supportedFeatures.featureCount);

					BX_ASSERT(bx::isSorted(s_feature, BX_COUNTOF(s_feature), Feature::cmpFn), "Feature table must be sorted!");

					for (uint32_t ii = 0; ii < BX_COUNTOF(s_feature); ++ii)
					{
						Feature& feature = s_feature[ii];
						feature.supported = false;
					}

					for (uint32_t ii = 0; ii < uint32_t(supportedFeatures.featureCount); ++ii)
					{
						const WGPUFeatureName featureName = supportedFeatures.features[ii];
						const int32_t idx = bx::binarySearch(featureName, s_feature, BX_COUNTOF(s_feature), sizeof(Feature), Feature::cmpFn);

						if (0 <= idx)
						{
							Feature& feature = s_feature[idx];
							BX_TRACE("\t%5x - %s", featureName, feature.name);
							feature.supported = true;
						}
						else
						{
							BX_TRACE("\t%5x - ** Unknown?! **", featureName);
						}
					}

					BX_TRACE("");

					wgpuSupportedFeaturesFreeMembers(supportedFeatures);

					WGPUFeatureName requiredFeatures[] =
					{
						ifSupported(WGPUFeatureName_TimestampQuery),

						ifSupported(WGPUFeatureName_DepthClipControl),

						WGPUFeatureName_IndirectFirstInstance,

						ifSupported(WGPUFeatureName_Unorm16TextureFormats),

						ifSupported(WGPUFeatureName_TextureComponentSwizzle),
						ifSupported(WGPUFeatureName_TextureFormatsTier1),
						ifSupported(WGPUFeatureName_TextureFormatsTier2),

						ifSupported(WGPUFeatureName_TextureCompressionBC),
						ifSupported(WGPUFeatureName_TextureCompressionETC2),
						ifSupported(WGPUFeatureName_TextureCompressionASTC),

						ifSupported(WGPUFeatureName_RG11B10UfloatRenderable),

						ifSupported(WGPUFeatureName_Depth32FloatStencil8),
					};

					bx::quickSort(requiredFeatures, BX_COUNTOF(requiredFeatures) );

					uint32_t requiredFeatureCount = BX_COUNTOF(requiredFeatures);
					for (uint32_t ii = 0; ii < BX_COUNTOF(requiredFeatures); ++ii)
					{
						if (WGPUFeatureName_Force32 == requiredFeatures[ii])
						{
							requiredFeatureCount = ii;
							break;
						}
					}

					BX_TRACE("Required features (%d / %d):", requiredFeatureCount, BX_COUNTOF(requiredFeatures) );

					for (uint32_t ii = 0; ii < requiredFeatureCount; ++ii)
					{
						const WGPUFeatureName featureName = requiredFeatures[ii];

						const int32_t idx = bx::binarySearch(featureName, s_feature, BX_COUNTOF(s_feature), sizeof(Feature), Feature::cmpFn);
						BX_ASSERT(0 <= idx, "Feature listed in required features must be present in s_feature table!");

						const Feature& feature = s_feature[idx];
						BX_TRACE("\t%5x - %s%s", featureName, feature.name, feature.supported ? "" : " <- this feature is not optional, and it's not supported by WebGPU implementation!");
						BX_UNUSED(feature);
					}

					BX_TRACE("");

					WGPULimits requiredLimits = WGPU_LIMITS_INIT;
					WGPUStatus status = wgpuAdapterGetLimits(m_adapter, &requiredLimits);

					if (WGPUStatus_Success == status)
					{
						requiredLimits.maxComputeWorkgroupSizeX = 1024;
						requiredLimits.maxComputeWorkgroupSizeY = 1024;
						requiredLimits.maxComputeWorkgroupSizeZ = 64;
					}

					static constexpr uint32_t kMaxEnabledTogles = 10;
					const char* enabledToggles[kMaxEnabledTogles];
					uint32_t enabledTogglesCount = 0;

					enabledToggles[enabledTogglesCount++] = "allow_unsafe_apis"; // TimestampWrite requires this.

					if (_init.debug)
					{
//						bx::setEnv("DAWN_DEBUG_BREAK_ON_ERROR", "1");

						enabledToggles[enabledTogglesCount++] = "dump_shaders_on_failure";
						enabledToggles[enabledTogglesCount++] = "use_user_defined_labels_in_backend";
//						enabledToggles[enabledTogglesCount++] = "dump_shaders";
					}
					else
					{
						enabledToggles[enabledTogglesCount++] = "disable_robustness";
						enabledToggles[enabledTogglesCount++] = "lazy_clear_resource_on_first_use";
						enabledToggles[enabledTogglesCount++] = "disable_lazy_clear_for_mapped_at_creation_buffer";
						enabledToggles[enabledTogglesCount++] = "skip_validation";
					}

					BX_ASSERT(enabledTogglesCount < kMaxEnabledTogles, "");

					BX_TRACE("Dawn enabled toggles (%d):", enabledTogglesCount);

					for (uint32_t ii = 0; ii < enabledTogglesCount; ++ii)
					{
						BX_TRACE("\t%d: %s", ii, enabledToggles[ii]);
					}

					BX_TRACE("");

					WGPUDawnTogglesDescriptor dawnTogglesDescriptor =
					{
						.chain =
						{
							.next  = NULL,
							.sType = WGPUSType_DawnTogglesDescriptor,
						},
						.enabledToggleCount  = enabledTogglesCount,
						.enabledToggles      = enabledToggles,
						.disabledToggleCount = 0,
						.disabledToggles     = NULL,
					};

					WGPUDeviceDescriptor deviceDesc =
					{
						.nextInChain            = &dawnTogglesDescriptor.chain,
						.label                  = WGPU_STRING_VIEW_INIT,
						.requiredFeatureCount   = requiredFeatureCount,
						.requiredFeatures       = requiredFeatures,
						.requiredLimits         = &requiredLimits,
						.defaultQueue           = WGPU_QUEUE_DESCRIPTOR_INIT,
						.deviceLostCallbackInfo =
							{
								.nextInChain = NULL,
								.mode        = WGPUCallbackMode_WaitAnyOnly,
								.callback    = deviceLostCb,
								.userdata1   = this,
								.userdata2   = NULL,
							},
						.uncapturedErrorCallbackInfo
							{
								.nextInChain = NULL,
								.callback    = uncapturedErrorCb,
								.userdata1   = this,
								.userdata2   = NULL,
							},
					};

					WGPUFutureWaitInfo fwi =
					{
						.future = wgpuAdapterRequestDevice(m_adapter, &deviceDesc,
							{
								.nextInChain = NULL,
								.mode        = WGPUCallbackMode_WaitAnyOnly,
								.callback    = requestDeviceCb,
								.userdata1   = this,
								.userdata2   = NULL,
							}),
						.completed = false,
					};

					WGPUWaitStatus waitStatus = wgpuInstanceWaitAny(m_instance, 1, &fwi, UINT64_MAX);

					if (WGPUWaitStatus_Success != waitStatus
					||  NULL == m_device)
					{
						goto error;
					}

					errorState = ErrorState::DeviceCreated;
				}

				{
					WGPUStatus status;

					WGPUAdapterInfo adapterInfo = WGPU_ADAPTER_INFO_INIT;
					status = wgpuAdapterGetInfo(m_adapter, &adapterInfo);

					if (WGPUStatus_Success == status)
					{
#define FORMAT(_str) _str.length, _str.data

						BX_TRACE("Adapter info:");
						BX_TRACE("\t      Vendor: %.*s", FORMAT(adapterInfo.vendor) );
						BX_TRACE("\tArchitecture: %.*s", FORMAT(adapterInfo.architecture) );
						BX_TRACE("\t      Device: %.*s", FORMAT(adapterInfo.device) );
						BX_TRACE("\t Description: %.*s", FORMAT(adapterInfo.description) );
#undef FORMAT

						BX_TRACE("\t    VendorId: %x", adapterInfo.vendorID);
						BX_TRACE("\t    DeviceId: %x", adapterInfo.deviceID);

						BX_TRACE("\tBackend type (%x): %s"
							, adapterInfo.backendType
							, s_backendType[bx::min<uint32_t>(adapterInfo.backendType, BX_COUNTOF(s_backendType)-1)]
							);
						BX_TRACE("\tAdapter type (%x): %s"
							, adapterInfo.adapterType
							, s_adapterType[bx::min<uint32_t>(adapterInfo.adapterType, BX_COUNTOF(s_adapterType)-1)]
							);

						g_caps.vendorId = bx::narrowCast<uint16_t>(adapterInfo.vendorID);
						g_caps.deviceId = bx::narrowCast<uint16_t>(adapterInfo.deviceID);
					}

					BX_TRACE("");

					m_limits = WGPU_LIMITS_INIT;
					status = wgpuAdapterGetLimits(m_adapter, &m_limits);

					if (WGPUStatus_Success == status)
					{
						BX_TRACE("WGPU limits:");

						BX_TRACE("\tmaxTextureDimension1D: %u",                     m_limits.maxTextureDimension1D);
						BX_TRACE("\tmaxTextureDimension2D: %u",                     m_limits.maxTextureDimension2D);
						BX_TRACE("\tmaxTextureDimension3D: %u",                     m_limits.maxTextureDimension3D);
						BX_TRACE("\tmaxTextureArrayLayers: %u",                     m_limits.maxTextureArrayLayers);
						BX_TRACE("\tmaxBindGroups: %u",                             m_limits.maxBindGroups);
						BX_TRACE("\tmaxBindGroupsPlusVertexBuffers: %u",            m_limits.maxBindGroupsPlusVertexBuffers);
						BX_TRACE("\tmaxBindingsPerBindGroup: %u",                   m_limits.maxBindingsPerBindGroup);
						BX_TRACE("\tmaxDynamicUniformBuffersPerPipelineLayout: %u", m_limits.maxDynamicUniformBuffersPerPipelineLayout);
						BX_TRACE("\tmaxDynamicStorageBuffersPerPipelineLayout: %u", m_limits.maxDynamicStorageBuffersPerPipelineLayout);
						BX_TRACE("\tmaxSampledTexturesPerShaderStage: %u",          m_limits.maxSampledTexturesPerShaderStage);
						BX_TRACE("\tmaxSamplersPerShaderStage: %u",                 m_limits.maxSamplersPerShaderStage);
						BX_TRACE("\tmaxStorageBuffersPerShaderStage: %u",           m_limits.maxStorageBuffersPerShaderStage);
						BX_TRACE("\tmaxStorageTexturesPerShaderStage: %u",          m_limits.maxStorageTexturesPerShaderStage);
						BX_TRACE("\tmaxUniformBuffersPerShaderStage: %u",           m_limits.maxUniformBuffersPerShaderStage);
						BX_TRACE("\tmaxUniformBufferBindingSize: %u",               m_limits.maxUniformBufferBindingSize);
						BX_TRACE("\tmaxStorageBufferBindingSize: %u",               m_limits.maxStorageBufferBindingSize);
						BX_TRACE("\tminUniformBufferOffsetAlignment: %u",           m_limits.minUniformBufferOffsetAlignment);
						BX_TRACE("\tminStorageBufferOffsetAlignment: %u",           m_limits.minStorageBufferOffsetAlignment);
						BX_TRACE("\tmaxVertexBuffers: %u",                          m_limits.maxVertexBuffers);
						BX_TRACE("\tmaxBufferSize: %u",                             m_limits.maxBufferSize);
						BX_TRACE("\tmaxVertexAttributes: %u",                       m_limits.maxVertexAttributes);
						BX_TRACE("\tmaxVertexBufferArrayStride: %u",                m_limits.maxVertexBufferArrayStride);
						BX_TRACE("\tmaxInterStageShaderVariables: %u",              m_limits.maxInterStageShaderVariables);
						BX_TRACE("\tmaxColorAttachments: %u",                       m_limits.maxColorAttachments);
						BX_TRACE("\tmaxColorAttachmentBytesPerSample: %u",          m_limits.maxColorAttachmentBytesPerSample);
						BX_TRACE("\tmaxComputeWorkgroupStorageSize: %u",            m_limits.maxComputeWorkgroupStorageSize);
						BX_TRACE("\tmaxComputeInvocationsPerWorkgroup: %u",         m_limits.maxComputeInvocationsPerWorkgroup);
						BX_TRACE("\tmaxComputeWorkgroupSizeX: %u",                  m_limits.maxComputeWorkgroupSizeX);
						BX_TRACE("\tmaxComputeWorkgroupSizeY: %u",                  m_limits.maxComputeWorkgroupSizeY);
						BX_TRACE("\tmaxComputeWorkgroupSizeZ: %u",                  m_limits.maxComputeWorkgroupSizeZ);
						BX_TRACE("\tmaxComputeWorkgroupsPerDimension: %u",          m_limits.maxComputeWorkgroupsPerDimension);
						BX_TRACE("\tmaxImmediateSize: %u",                          m_limits.maxImmediateSize);

						g_caps.limits.maxTextureSize     = m_limits.maxTextureDimension2D;
						g_caps.limits.maxTextureLayers   = m_limits.maxTextureArrayLayers;
						g_caps.limits.maxTextureSamplers = bx::min(m_limits.maxSamplersPerShaderStage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
						g_caps.limits.maxComputeBindings = BGFX_CONFIG_MAX_TEXTURE_SAMPLERS;
						g_caps.limits.maxFBAttachments   = bx::min(m_limits.maxColorAttachments, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);
						g_caps.limits.maxVertexStreams   = bx::min(m_limits.maxVertexBuffers, BGFX_CONFIG_MAX_VERTEX_STREAMS);

						g_caps.supported = 0
							| BGFX_CAPS_ALPHA_TO_COVERAGE
							| BGFX_CAPS_BLEND_INDEPENDENT
							| BGFX_CAPS_COMPUTE
							| BGFX_CAPS_DRAW_INDIRECT
							| BGFX_CAPS_FRAGMENT_DEPTH
							| BGFX_CAPS_IMAGE_RW
							| BGFX_CAPS_INDEX32
							| BGFX_CAPS_INSTANCING
							| BGFX_CAPS_OCCLUSION_QUERY
							| BGFX_CAPS_PRIMITIVE_ID
							| BGFX_CAPS_RENDERER_MULTITHREADED
							| BGFX_CAPS_SWAP_CHAIN
							| BGFX_CAPS_TEXTURE_2D_ARRAY
							| BGFX_CAPS_TEXTURE_3D
							| BGFX_CAPS_TEXTURE_BLIT
							| BGFX_CAPS_TEXTURE_COMPARE_ALL
							| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
							| BGFX_CAPS_TEXTURE_CUBE_ARRAY
							| BGFX_CAPS_TEXTURE_READ_BACK
							| BGFX_CAPS_VERTEX_ATTRIB_HALF
							| BGFX_CAPS_VERTEX_ID
							;

						for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
						{
							g_caps.formats[formatIdx] = 0
								| BGFX_CAPS_FORMAT_TEXTURE_NONE
								| (WGPUTextureFormat_Undefined != s_textureFormat[formatIdx].m_fmt ? 0
									| BGFX_CAPS_FORMAT_TEXTURE_2D
									| BGFX_CAPS_FORMAT_TEXTURE_3D
									| BGFX_CAPS_FORMAT_TEXTURE_CUBE
									| 0
									| (!bimg::isCompressed(bimg::TextureFormat::Enum(formatIdx) ) ? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER : 0)
									: 0)
								| (WGPUTextureFormat_Undefined != s_textureFormat[formatIdx].m_fmtSrgb ? 0
									| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
									| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
									| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
									: 0)
//								| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
//								| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ
//								| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE
//								| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
//								| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
//								| BGFX_CAPS_FORMAT_TEXTURE_MSAA
//								| BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
								;
						}

						g_caps.formats[TextureFormat::ETC1] = 0
							| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
							| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
							| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
							;
						g_caps.formats[TextureFormat::ETC2] = 0
							| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
							| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
							| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
							;
						g_caps.formats[TextureFormat::ASTC4x4  ] = 0;
						g_caps.formats[TextureFormat::ASTC5x4  ] = 0;
						g_caps.formats[TextureFormat::ASTC5x5  ] = 0;
						g_caps.formats[TextureFormat::ASTC6x5  ] = 0;
						g_caps.formats[TextureFormat::ASTC6x6  ] = 0;
						g_caps.formats[TextureFormat::ASTC8x5  ] = 0;
						g_caps.formats[TextureFormat::ASTC8x6  ] = 0;
						g_caps.formats[TextureFormat::ASTC8x8  ] = 0;
						g_caps.formats[TextureFormat::ASTC10x5 ] = 0;
						g_caps.formats[TextureFormat::ASTC10x6 ] = 0;
						g_caps.formats[TextureFormat::ASTC10x8 ] = 0;
						g_caps.formats[TextureFormat::ASTC10x10] = 0;
						g_caps.formats[TextureFormat::ASTC12x10] = 0;
						g_caps.formats[TextureFormat::ASTC12x12] = 0;

						g_caps.formats[TextureFormat::RGBA8] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::BGRA8] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::R16F] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::RG16F] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::R32F] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::RGBA16F] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::D16] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::D24S8] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
						g_caps.formats[TextureFormat::D32F] |= 0
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
							| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
							;
					}
				}

				BX_TRACE("");

				{
					m_maxFrameLatency = _init.resolution.maxFrameLatency == 0
						? BGFX_CONFIG_MAX_FRAME_LATENCY
						: _init.resolution.maxFrameLatency
						;

					m_cmd.init(m_device);

					errorState = ErrorState::QueueCreated;
				}

				{
					m_resolution = _init.resolution;
					m_resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

					m_textVideoMem.resize(false, _init.resolution.width, _init.resolution.height);
					m_textVideoMem.clear();

					m_numWindows = 0;

					if (!headless)
					{
						m_backBuffer.create(
							  UINT16_MAX
							, g_platformData.nwh
							, m_resolution.width
							, m_resolution.height
							, m_resolution.formatColor
							);


						m_windows[0] = BGFX_INVALID_HANDLE;
						m_numWindows++;

						postReset();
					}

					errorState = ErrorState::SwapChainCreated;
				}

				{
					m_gpuTimer.init();
					m_occlusionQuery.init();
					m_uniformScratchBuffer.createUniform(1<<20, m_maxFrameLatency*2);
				}
			}

			return true;

		error:
			BX_TRACE("errorState %d", errorState);
			switch (errorState)
			{
			case ErrorState::SwapChainCreated:
				[[fallthrough]];

			case ErrorState::QueueCreated:
				m_cmd.shutdown();
				[[fallthrough]];

			case ErrorState::DeviceCreated:
				wgpuRelease(m_device);
				[[fallthrough]];

			case ErrorState::AdapterCreated:
				wgpuRelease(m_adapter);
				[[fallthrough]];

			case ErrorState::InstanceCreated:
				wgpuRelease(m_instance);
				[[fallthrough]];

			case ErrorState::LoadedWebGPU:
				bx::dlclose(m_webgpuDll);
				m_webgpuDll  = NULL;
				[[fallthrough]];

			case ErrorState::Default:
				unloadRenderDoc(m_renderDocDll);
				break;
			};

			return false;
		}

		void shutdown()
		{
			preReset();

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

			m_backBuffer.destroy();

			m_gpuTimer.shutdown();
			m_occlusionQuery.shutdown();
			m_uniformScratchBuffer.destroy();

			m_cmd.shutdown();

			wgpuRelease(m_device);
			wgpuRelease(m_adapter);
			wgpuRelease(m_instance);

			bx::dlclose(m_webgpuDll);
			m_webgpuDll  = NULL;

			unloadRenderDoc(m_renderDocDll);
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::WebGPU;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_WEBGPU_NAME;
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			int64_t start = bx::getHPCounter();

			for (uint16_t ii = 0; ii < m_numWindows; ++ii)
			{
				FrameBufferWGPU& fb = isValid(m_windows[ii])
					? m_frameBuffers[m_windows[ii].idx]
					: m_backBuffer
					;

				fb.present();
			}

			const int64_t now = bx::getHPCounter();

			m_presentElapsed += now - start;
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags, false);
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
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags, false);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
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
			m_vertexBuffers[_handle.idx].update(_offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
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

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip, uint64_t _external) override
		{
			BX_UNUSED(_external);
			m_textures[_handle.idx].create(_mem, _flags, _skip);
			return NULL;
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		bool s_done;

		struct ReadTexture
		{
			WGPUBuffer buffer;
			uint32_t size;
			void* data;
			uint32_t dataPitch;
			uint32_t pitch;
			uint32_t height;
		};

		static void readTextureCb(WGPUMapAsyncStatus _status, WGPUStringView _message, void* _userdata1, void* _userdata2)
		{
			BX_ASSERT(WGPUMapAsyncStatus_Success == _status, "%d", _status);

			BX_UNUSED(_status, _message, _userdata2);

			ReadTexture& readTexture = *(ReadTexture*)_userdata1;

			const void* result = (const void*)WGPU_CHECK(wgpuBufferGetConstMappedRange(
				  readTexture.buffer
				, 0
				, readTexture.size
				) );

			bx::gather(
				  readTexture.data
				, result
				, readTexture.pitch
				, readTexture.dataPitch
				, readTexture.height
				);

			WGPU_CHECK(wgpuBufferUnmap(readTexture.buffer) );

			wgpuRelease(readTexture.buffer);

			*(bool*)(_userdata2) = true;
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			const TextureWGPU& texture = m_textures[_handle.idx];

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width >>_mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height>>_mip);

			const uint8_t  bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat) );
			const uint32_t dstPitch = srcWidth*bpp/8;
			const uint32_t dstBufferPitch = bx::alignUp(dstPitch, 256);

			const uint32_t copySize = dstBufferPitch * srcHeight;

			WGPUBufferDescriptor readTextureBufferDesc =
			{
				.nextInChain = NULL,
				.label       = toWGPUStringView("Read Texture Buffer"),
				.usage       = 0
					| WGPUBufferUsage_MapRead
					| WGPUBufferUsage_CopyDst
					,
				.size = copySize,
				.mappedAtCreation = false,
			};

			WGPUBuffer readTextureBuffer = WGPU_CHECK(wgpuDeviceCreateBuffer(m_device, &readTextureBufferDesc) );

			s_done = false;

			m_cmd.copyTextureToBuffer(
				{
					.texture  = texture.m_texture,
					.mipLevel = _mip,
					.origin   =
					{
						.x = 0,
						.y = 0,
						.z = 0,
					},
					.aspect = WGPUTextureAspect_All,
				},
				{
					.layout =
					{
						.offset       = 0,
						.bytesPerRow  = dstBufferPitch,
						.rowsPerImage = srcHeight,
					},
					.buffer = readTextureBuffer,
				},
				{
					.width              = srcWidth,
					.height             = srcHeight,
					.depthOrArrayLayers = 1,
				}
				);

			m_cmd.kick();
			m_cmd.wait();

			ReadTexture readTexture =
			{
				.buffer    = readTextureBuffer,
				.size      = copySize,
				.data      = _data,
				.dataPitch = dstPitch,
				.pitch     = dstBufferPitch,
				.height    = srcHeight,
			};

			WGPU_CHECK(wgpuBufferMapAsync(
				  readTextureBuffer
				, WGPUMapMode_Read
				, 0
				, copySize
				, {
					.nextInChain = NULL,
					.mode        = WGPUCallbackMode_AllowProcessEvents,
					.callback    = readTextureCb,
					.userdata1   = &readTexture,
					.userdata2   = &s_done,
				}) );

			while (!s_done)
			{
				wgpuInstanceProcessEvents(m_instance);
			}
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureWGPU& texture = m_textures[_handle.idx];

			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			bx::write(&writer, kChunkMagicTex, bx::ErrorAssert{});

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

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/, uint16_t /*_layerIndex*/) override
		{
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			setGraphicsDebuggerPresent(true);
			return uintptr_t(m_textures[_handle.idx].m_texture);
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
				&&  m_frameBuffers[handle.idx].m_swapChain.m_nwh == _nwh)
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
			FrameBufferWGPU& frameBuffer = m_frameBuffers[_handle.idx];

			uint16_t denseIdx = frameBuffer.destroy();
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
				bx::free(g_allocator, m_uniforms[_handle.idx]);
			}

			uint32_t size = g_uniformTypeSize[_type]*_num;
			void* data = bx::alloc(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			bx::free(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
			m_uniformReg.remove(_handle);
		}

		void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) override
		{
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			bx::strCopy(
				  &s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0])-BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
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
			BX_UNUSED(_marker, _len);
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				WGPU_CHECK(wgpuBufferSetLabel(m_indexBuffers[_handle.idx].m_buffer, { .data = _name, .length = _len }) );
				break;

			case Handle::Shader:
				WGPU_CHECK(wgpuShaderModuleSetLabel(m_shaders[_handle.idx].m_module, { .data = _name, .length = _len }) );
				break;

			case Handle::Texture:
				WGPU_CHECK(wgpuTextureSetLabel(m_textures[_handle.idx].m_texture, { .data = _name, .length = _len }) );
				break;

			case Handle::VertexBuffer:
				WGPU_CHECK(wgpuBufferSetLabel(m_vertexBuffers[_handle.idx].m_buffer, { .data = _name, .length = _len }) );
				break;

			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submitUniformCache(UniformCacheState& _ucs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void dbgTextRenderBegin(TextVideoMemBlitter& _blitter) override
		{
			const uint32_t width  = m_backBuffer.m_width;
			const uint32_t height = m_backBuffer.m_height;

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

			const ProgramWGPU& program = m_program[_blitter.m_program.idx];

			const PredefinedUniform& predefined = program.m_predefined[0];
			const uint8_t flags = predefined.m_type;
			setShaderUniform4x4f(flags, predefined.m_loc, proj, 4);

			ChunkedScratchBufferOffset sbo;
			const uint32_t vsSize = program.m_vsh->m_size;
			const uint32_t fsSize = NULL != program.m_fsh ? program.m_fsh->m_size : 0;
			m_uniformScratchBuffer.write(sbo, m_vsScratch, vsSize, m_fsScratch, fsSize);

			const uint64_t state = 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			const TextureWGPU& texture = m_textures[_blitter.m_texture.idx];
			RenderBind renderBind;
			renderBind.clear();
			Binding& bind = renderBind.m_bind[0];
			bind.m_idx    = _blitter.m_texture.idx;
			bind.m_type   = uint8_t(Binding::Texture);
			bind.m_samplerFlags = uint32_t(texture.m_flags & BGFX_SAMPLER_BITS_MASK);
			bind.m_format = 0;
			bind.m_access = 0;
			bind.m_mip    = 0;

			const Stream stream =
			{
				.m_startVertex  = 0,
				.m_handle       = _blitter.m_vb->handle,
				.m_layoutHandle = _blitter.m_vb->layoutHandle,
			};

			const RenderPipeline& pipeline = *getPipeline(
				  _blitter.m_program
				, BGFX_INVALID_HANDLE
				, 1
				, state
				, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT)
				, 1
				, &stream
				, 0
				, true
				, renderBind
				, false
				);

			WGPURenderPassColorAttachment colorAttachment =
			{
				.nextInChain   = NULL,
				.view          = m_backBuffer.m_swapChain.m_textureView,
				.depthSlice    = WGPU_DEPTH_SLICE_UNDEFINED,
				.resolveTarget = NULL,
				.loadOp        = WGPULoadOp_Load,
				.storeOp       = WGPUStoreOp_Store,
				.clearValue    = {},
			};

			WGPURenderPassDescriptor renderPassDesc =
			{
				.nextInChain            = NULL,
				.label                  = WGPU_STRING_VIEW_INIT,
				.colorAttachmentCount   = 1,
				.colorAttachments       = &colorAttachment,
				.depthStencilAttachment = NULL,
				.occlusionQuerySet      = NULL,
				.timestampWrites        = NULL,
			};

			WGPUCommandEncoder cmdEncoder = m_cmd.alloc();
			WGPURenderPassEncoder blitRenderPassEncoder = WGPU_CHECK(wgpuCommandEncoderBeginRenderPass(cmdEncoder, &renderPassDesc) );
			_blitter.m_usedData = uintptr_t(blitRenderPassEncoder);

			BindGroup bindGroup = createBindGroup(pipeline.bindGroupLayout, program, renderBind, sbo, false);

			WGPU_CHECK(wgpuRenderPassEncoderSetViewport(
				  blitRenderPassEncoder
				, 0.0f
				, 0.0f
				, float(width)
				, float(height)
				, 0.0f
				, 1.0f
				) );

			WGPU_CHECK(wgpuRenderPassEncoderSetPipeline(blitRenderPassEncoder, pipeline.pipeline) );
			WGPU_CHECK(wgpuRenderPassEncoderSetBindGroup(blitRenderPassEncoder, 0, bindGroup.bindGroup, bindGroup.numOffsets, sbo.offsets) );
			release(bindGroup);
		}

		void dbgTextRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			WGPURenderPassEncoder blitRenderPassEncoder = WGPURenderPassEncoder(_blitter.m_usedData);

			const uint32_t numVertices = _numIndices*4/6;

			if (0 < numVertices)
			{
				const IndexBufferWGPU&  ib = m_indexBuffers[_blitter.m_ib->handle.idx];
				const uint32_t ibSize = _numIndices*2;
				ib.update(0, ibSize, _blitter.m_ib->data);

				const VertexBufferWGPU& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				const uint32_t vbSize = numVertices*_blitter.m_layout.m_stride;
				vb.update(0, vbSize, _blitter.m_vb->data, true);

				WGPU_CHECK(wgpuRenderPassEncoderSetVertexBuffer(blitRenderPassEncoder, 0, vb.m_buffer, 0, vbSize) );
				WGPU_CHECK(wgpuRenderPassEncoderSetIndexBuffer(blitRenderPassEncoder, ib.m_buffer, WGPUIndexFormat_Uint16, 0, ibSize) );
				WGPU_CHECK(wgpuRenderPassEncoderDrawIndexed(blitRenderPassEncoder, _numIndices, 1, 0, 0, 0) );
			}
		}

		void dbgTextRenderEnd(TextVideoMemBlitter& _blitter) override
		{
			WGPURenderPassEncoder blitRenderPassEncoder = WGPURenderPassEncoder(_blitter.m_usedData);
			_blitter.m_usedData = 0;
			WGPU_CHECK(wgpuRenderPassEncoderEnd(blitRenderPassEncoder) );
			wgpuRelease(blitRenderPassEncoder);
		}

		void clearQuad(WGPURenderPassEncoder _renderPassEncoder, FrameBufferHandle _fbh, uint32_t _msaaCount, const ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			BX_UNUSED(_clearQuad, _rect, _clear, _palette);

			uint64_t state = BGFX_STATE_PT_TRISTRIP;
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

			uint32_t numMrt = 1;
			if (isValid(_fbh) )
			{
				const FrameBufferWGPU& fb = m_frameBuffers[_fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_numColorAttachments);
			}

			const VertexBufferWGPU& vb = m_vertexBuffers[_clearQuad.m_vb.idx];

			const Stream stream = {
				.m_startVertex  = 0,
				.m_handle       = _clearQuad.m_vb,
				.m_layoutHandle = _clearQuad.m_layout,
				};

			RenderBind renderBind;
			renderBind.clear();

			const RenderPipeline& pipeline = *getPipeline(
				  _clearQuad.m_program[numMrt-1]
				, _fbh
				, _msaaCount
				, state
				, stencil
				, 1
				, &stream
				, 0
				, true
				, renderBind
				, true
				);

			const ProgramWGPU& program = m_program[_clearQuad.m_program[numMrt-1].idx];

			const float mrtClearDepth[4] = { _clear.m_depth };
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
				const float rgba[4] =
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

			ChunkedScratchBufferOffset sbo;
			m_uniformScratchBuffer.write(sbo, mrtClearDepth, sizeof(mrtClearDepth), mrtClearColor, sizeof(mrtClearColor) );

			BindGroup bindGroup = createBindGroup(pipeline.bindGroupLayout, program, renderBind, sbo, false);

			WGPU_CHECK(wgpuRenderPassEncoderSetPipeline(_renderPassEncoder, pipeline.pipeline) );
			WGPU_CHECK(wgpuRenderPassEncoderSetBindGroup(_renderPassEncoder, 0, bindGroup.bindGroup, bindGroup.numOffsets, sbo.offsets) );
			release(bindGroup);

			WGPU_CHECK(wgpuRenderPassEncoderSetVertexBuffer(_renderPassEncoder, 0, vb.m_buffer, 0, vb.m_size) );
			WGPU_CHECK(wgpuRenderPassEncoderDraw(_renderPassEncoder, 4, 1, 0, 0) );
		}

		void preReset()
		{
			m_renderPipelineCache.invalidate();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].preReset();
			}

			invalidateCache();
		}

		void postReset()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}

			if (m_resolution.reset & BGFX_RESET_CAPTURE)
			{
			}
		}

		void invalidateCache()
		{
			m_computePipelineCache.invalidate();
			m_renderPipelineCache.invalidate();
			m_textureViewStateCache.invalidate();
			m_samplerStateCache.invalidate();
		}

		bool updateResolution(const Resolution& _resolution)
		{
			const bool suspended = !!(_resolution.reset & BGFX_RESET_SUSPEND);

			uint16_t maxAnisotropy = 1;
			if (!!(_resolution.reset & BGFX_RESET_MAXANISOTROPY) )
			{
				maxAnisotropy = 16;
			}

			if (m_maxAnisotropy != maxAnisotropy)
			{
				m_maxAnisotropy = maxAnisotropy;
				m_samplerStateCache.invalidate();
			}

			const bool depthClamp = !!(_resolution.reset & BGFX_RESET_DEPTH_CLAMP);

			if (m_depthClamp != depthClamp)
			{
				m_depthClamp = depthClamp;
				m_renderPipelineCache.invalidate();
			}

			if (!m_backBuffer.isSwapChain() )
			{
				return suspended;
			}

			uint32_t flags = _resolution.reset & ~(0
				| BGFX_RESET_SUSPEND
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				);

			if (false
			||  m_resolution.formatColor        != _resolution.formatColor
			||  m_resolution.formatDepthStencil != _resolution.formatDepthStencil
			||  m_resolution.width              != _resolution.width
			||  m_resolution.height             != _resolution.height
			||  m_resolution.reset              != flags
				)
			{
				flags &= ~BGFX_RESET_INTERNAL_FORCE;

				if (m_backBuffer.m_swapChain.m_nwh != g_platformData.nwh)
				{
					m_backBuffer.m_swapChain.m_nwh = g_platformData.nwh;
				}

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				preReset();

				m_backBuffer.update(m_resolution);

				postReset();
			}

			return suspended;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags & kUniformFragmentBit)
			{
				bx::memCopy(&m_fsScratch[_regIndex], _val, _numRegs*16);
			}
			else
			{
				bx::memCopy(&m_vsScratch[_regIndex], _val, _numRegs*16);
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

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
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

				uint8_t type;
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

				switch (type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3|kUniformFragmentBit:
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

				case UniformType::Sampler:
				case UniformType::Sampler|kUniformFragmentBit:
					break;

				case UniformType::Vec4:
				case UniformType::Vec4 | kUniformFragmentBit:
					setShaderUniform(uint8_t(type), loc, data, num);
					break;

				case UniformType::Mat4:
				case UniformType::Mat4 | kUniformFragmentBit:
					setShaderUniform4x4f(uint8_t(type), loc, data, num);
					break;

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}
			}
		}

		void initBufferBinding(WGPUBindGroupLayoutEntry& _out, uint32_t _binding, WGPUShaderStage _visibility, WGPUBufferBindingType _type, bool _hasDynamicOffset)
		{
			_out =
			{
				.nextInChain      = NULL,
				.binding          = _binding,
				.visibility       = _visibility,
				.bindingArraySize = 0,
				.buffer =
				{
					.nextInChain      = NULL,
					.type             = _type,
					.hasDynamicOffset = _hasDynamicOffset,
					.minBindingSize   = 0,
				},
				.sampler = {},
				.texture = {},
				.storageTexture = {},
			};
		}

		void initSamplerBinding(WGPUBindGroupLayoutEntry& _out, uint32_t _binding, WGPUShaderStage _visibility, WGPUSamplerBindingType _type)
		{
			_out =
			{
				.nextInChain      = NULL,
				.binding          = _binding,
				.visibility       = _visibility,
				.bindingArraySize = 0,
				.buffer  = {},
				.sampler =
				{
					.nextInChain = NULL,
					.type        = _type,
				},
				.texture = {},
				.storageTexture = {},
			};
		}

		void initTextureBinding(WGPUBindGroupLayoutEntry& _out, uint32_t _binding, WGPUShaderStage _visibility, WGPUTextureSampleType _sampleType, WGPUTextureViewDimension _viewDimension)
		{
			_out =
			{
				.nextInChain      = NULL,
				.binding          = _binding,
				.visibility       = _visibility,
				.bindingArraySize = 0,
				.buffer  = {},
				.sampler = {},
				.texture =
				{
					.nextInChain   = NULL,
					.sampleType    = _sampleType,
					.viewDimension = _viewDimension,
					.multisampled  = false,
				},
				.storageTexture = {},
			};
		}

		void initStorageTextureBinding(WGPUBindGroupLayoutEntry& _out, uint32_t _binding, WGPUShaderStage _visibility, WGPUStorageTextureAccess _access, WGPUTextureFormat _format, WGPUTextureViewDimension _viewDimension)
		{
			_out =
			{
				.nextInChain      = NULL,
				.binding          = _binding,
				.visibility       = _visibility,
				.bindingArraySize = 0,
				.buffer  = {},
				.sampler = {},
				.texture = {},
				.storageTexture =
				{
					.nextInChain   = NULL,
					.access        = _access,
					.format        = _format,
					.viewDimension = _viewDimension,
				},
			};
		}

		uint8_t fillBindGroupLayoutEntry(WGPUBindGroupLayoutEntry* _entries, const ProgramWGPU& _program, const RenderBind& _renderBind, bool _isCompute)
		{
			uint8_t entryCount = 0;

			const uint32_t vsSize = _program.m_vsh->m_size;
			const uint32_t fsSize = NULL == _program.m_fsh ? 0 : _program.m_fsh->m_size;

			if (0 < vsSize)
			{
				initBufferBinding(
					  _entries[entryCount++]
					, 0
					, _isCompute
						? WGPUShaderStage_Compute
						: WGPUShaderStage_Vertex
					, WGPUBufferBindingType_Uniform
					, true
					);
			}

			if (0 < fsSize)
			{
				initBufferBinding(
					  _entries[entryCount++]
					, 1
					, WGPUShaderStage_Fragment
					, WGPUBufferBindingType_Uniform
					, true
					);
			}

			for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const ShaderBinding& shaderBind = _program.m_shaderBinding[stage];

				if (!isValid(shaderBind.uniformHandle) )
				{
					continue;
				}

				const Binding& bind = _renderBind.m_bind[stage];

				switch (shaderBind.type)
				{
				case ShaderBinding::Type::Buffer:
					initBufferBinding(
						  _entries[entryCount++]
						, shaderBind.binding
						, shaderBind.shaderStage
						, shaderBind.bufferBindingType
						, false
						);
					break;

				case ShaderBinding::Type::Image:
					initStorageTextureBinding(
						  _entries[entryCount++]
						, shaderBind.binding
						, shaderBind.shaderStage
						, s_storageTextureAccess[bind.m_access]
						, s_textureFormat[m_textures[bind.m_idx].m_textureFormat].m_fmt
						, shaderBind.viewDimension
						);
					break;

				case ShaderBinding::Type::Sampler:
					{
						TextureWGPU& texture = m_textures[bind.m_idx];
						WGPUTextureSampleType sampleType = WGPUTextureSampleType_Depth != shaderBind.sampleType
							? s_textureFormat[texture.m_textureFormat].m_samplerType
							: shaderBind.sampleType
							;

						WGPUSamplerBindingType samplerBindingType = WGPUSamplerBindingType_Filtering;
						switch (sampleType)
						{
						case WGPUTextureSampleType_UnfilterableFloat: samplerBindingType = WGPUSamplerBindingType_NonFiltering; break;
						case WGPUTextureSampleType_Depth:             samplerBindingType = WGPUSamplerBindingType_Comparison;   break;
						default: break;
						}

						initTextureBinding(
							  _entries[entryCount++]
							, shaderBind.binding
							, shaderBind.shaderStage
							, sampleType
							, m_textures[bind.m_idx].m_viewDimension
							);

						initSamplerBinding(
							  _entries[entryCount++]
							, shaderBind.samplerBinding
							, shaderBind.shaderStage
							, samplerBindingType
							);
					}
					break;

				case ShaderBinding::Type::Count:
					break;
				}
			}

			return entryCount;
		}

		ComputePipeline* getPipeline(ProgramHandle _program, const RenderBind& _renderBind)
		{
			const ProgramWGPU& program = m_program[_program.idx];

			bx::HashMurmur3 murmur;
			murmur.begin();
			murmur.add(program.m_vsh->m_hash);
			murmur.add(&_renderBind.m_bind, sizeof(_renderBind.m_bind) );
			const uint32_t hash = murmur.end();

			ComputePipeline* computePipeline = m_computePipelineCache.find(hash);

			if (BX_LIKELY(NULL != computePipeline) )
			{
				return computePipeline;
			}

			WGPUBindGroupLayoutEntry entries[2 + BGFX_CONFIG_MAX_TEXTURE_SAMPLERS * 3];
			const uint8_t entryCount = fillBindGroupLayoutEntry(entries, program, _renderBind, true);
			BX_ASSERT(entryCount < BX_COUNTOF(entries), "");
			BX_ASSERT(program.m_numBindings <= entryCount, "");

			WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.entryCount  = entryCount,
				.entries     = entries,
			};

			WGPUBindGroupLayout bindGroupLayout = WGPU_CHECK(wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc) );

			WGPUPipelineLayoutDescriptor pipelineLayoutDesc =
			{
				.nextInChain          = NULL,
				.label                = WGPU_STRING_VIEW_INIT,
				.bindGroupLayoutCount = 1,
				.bindGroupLayouts     = &bindGroupLayout,
				.immediateSize        = 0,
			};

			WGPUPipelineLayout pipelineLayout = WGPU_CHECK(wgpuDeviceCreatePipelineLayout(m_device, &pipelineLayoutDesc) );

			WGPUComputePipelineDescriptor computePipelineDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.layout      = pipelineLayout,
				.compute =
				{
					.nextInChain   = NULL,
					.module        = program.m_vsh->m_module,
					.entryPoint    = WGPU_STRING_VIEW_INIT, // toWGPUStringView("main"),
					.constantCount = 0,
					.constants     = NULL,
				},
			};

			computePipeline = m_computePipelineCache.add(
				  hash
				, {
					.bindGroupLayout = bindGroupLayout,
					.pipeline        = wgpuDeviceCreateComputePipeline(m_device, &computePipelineDesc),
				}
				, 0
				);
			wgpuRelease(pipelineLayout);

			return computePipeline;
		}

		static WGPUVertexAttribute* fillVertexLayout(const ShaderWGPU* _vsh, WGPUVertexAttribute* _out, const VertexLayout& _layout)
		{
			WGPUVertexAttribute* elem = _out;

			for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
			{
				if (UINT16_MAX != _layout.m_attributes[attr])
				{
					elem->nextInChain = NULL;
					elem->shaderLocation = _vsh->m_attrRemap[attr];

					if (0 != _layout.m_attributes[attr])
					{
						uint8_t num;
						AttribType::Enum type;
						bool normalized;
						bool asInt;
						_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);
						elem->format = s_attribType[type][num-1][normalized];
						elem->offset = 0 == _layout.m_attributes[attr]
							? 0
							: _layout.m_offset[attr]
							;
					}
					else
					{
						elem->format = WGPUVertexFormat_Float32x3;
						elem->offset = 0;
					}

					++elem;
				}
			}

			return elem;
		}

		RenderPipeline* getPipeline(
			  ProgramHandle _program
			, FrameBufferHandle _fbh
			, uint32_t _msaaCount
			, uint64_t _state
			, uint64_t _stencil
			, uint8_t _streamMask
			, const Stream* _stream
			, uint8_t _numInstanceData
			, bool _isIndex16
			, const RenderBind& _renderBind
			, bool _useDepthAttachment = true
			)
		{
			const ProgramWGPU& program = m_program[_program.idx];

			_state &= 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_MASK
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_FRONT_CCW
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_PT_MASK
				;

			_stencil &= kStencilNoRefMask;

			const uint8_t numVertexStreams = bx::countBits(_streamMask);

			VertexLayout layout;
			if (0 < numVertexStreams)
			{
				const uint16_t layoutIdx = isValid(_stream[0].m_layoutHandle)
					? _stream[0].m_layoutHandle.idx
					: m_vertexBuffers[_stream[0].m_handle.idx].m_layoutHandle.idx
					;

				bx::memCopy(&layout, &m_vertexLayouts[layoutIdx], sizeof(VertexLayout) );
				const uint16_t* attrMask = program.m_vsh->m_attrMask;

				for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
				{
					uint16_t mask = attrMask[ii];
					uint16_t attr = (layout.m_attributes[ii] & mask);
					layout.m_attributes[ii] = attr == 0 ? UINT16_MAX : attr == UINT16_MAX ? 0 : attr;
				}
			}

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			murmur.add(&_renderBind.m_bind, sizeof(_renderBind.m_bind) );
			murmur.add(program.m_vsh->m_hash);
			murmur.add(program.m_vsh->m_attrMask, sizeof(program.m_vsh->m_attrMask) );

			if (NULL != program.m_fsh)
			{
				murmur.add(program.m_fsh->m_hash);
			}

			for (BitMaskToIndexIteratorT it(_streamMask); !it.isDone(); it.next() )
			{
				const uint8_t idx = it.idx;

				uint16_t handle = _stream[idx].m_handle.idx;
				const VertexBufferWGPU& vb = m_vertexBuffers[handle];
				const uint16_t layoutIdx = isValid(_stream[idx].m_layoutHandle)
					? _stream[idx].m_layoutHandle.idx
					: vb.m_layoutHandle.idx;

				murmur.add(m_vertexLayouts[layoutIdx].m_hash);
			}

			murmur.add(layout.m_attributes, sizeof(layout.m_attributes) );
			murmur.add(_fbh);
			murmur.add(_msaaCount);
			murmur.add(_numInstanceData);
			const uint32_t hash = murmur.end();

			RenderPipeline* renderPipeline = m_renderPipelineCache.find(hash);

			if (BX_LIKELY(NULL != renderPipeline) )
			{
				return renderPipeline;
			}

			WGPUVertexBufferLayout vertexBufferLayout[BGFX_CONFIG_MAX_VERTEX_STREAMS];
			WGPUVertexAttribute vertexAttribute[Attrib::Count+1+BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

			uint8_t numStreams = 0;

			{
				WGPUVertexAttribute* elem = vertexAttribute;

				uint16_t attrMask[Attrib::Count];
				bx::memCopy(attrMask, program.m_vsh->m_attrMask, sizeof(attrMask) );

				uint32_t maxShaderLocation = 0;

				for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
				{
					maxShaderLocation = bx::max(maxShaderLocation, program.m_vsh->m_attrRemap[attr]);
				}

				if (UINT8_MAX != _streamMask)
				{
					for (BitMaskToIndexIteratorT it(_streamMask)
						; !it.isDone()
						; it.next(), numStreams++
						)
					{
						const uint8_t idx = it.idx;

						const uint16_t handle = _stream[idx].m_handle.idx;
						const VertexBufferWGPU& vb = m_vertexBuffers[handle];
						const uint16_t layoutIdx = isValid(_stream[idx].m_layoutHandle)
							? _stream[idx].m_layoutHandle.idx
							: vb.m_layoutHandle.idx
							;

						bx::memCopy(&layout, &m_vertexLayouts[layoutIdx], sizeof(VertexLayout) );

						const bool lastStream = idx == uint32_t(numVertexStreams-1);

						for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
						{
							const uint16_t mask = attrMask[ii];
							const uint16_t attr = (layout.m_attributes[ii] & mask);

							if (0          == attr
							||  UINT16_MAX == attr)
							{
								layout.m_attributes[ii] = lastStream ? ~attr : UINT16_MAX;
							}
							else
							{
								attrMask[ii] = 0;
							}
						}

						WGPUVertexAttribute* last = fillVertexLayout(program.m_vsh, elem, layout);

						vertexBufferLayout[idx] =
						{
							.nextInChain    = NULL,
							.stepMode       = WGPUVertexStepMode_Vertex,
							.arrayStride    = layout.m_stride,
							.attributeCount = uint32_t(last - elem),
							.attributes     = elem,
						};

						elem = last;
					}
				}

				if (0 < _numInstanceData)
				{
					maxShaderLocation += 0 < numStreams;

					for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
					{
						elem[ii] =
						{
							.nextInChain = 0,
							.format      = WGPUVertexFormat_Float32x4,
							.offset      = ii*16ull,
							.shaderLocation = maxShaderLocation+ii,
						};
					}

					vertexBufferLayout[numStreams] =
					{
						.nextInChain    = NULL,
						.stepMode       = WGPUVertexStepMode_Instance,
						.arrayStride    = _numInstanceData*16ull,
						.attributeCount = _numInstanceData,
						.attributes     = elem,
					};

					++numStreams;
				}
			}

			WGPUBindGroupLayoutEntry entries[2 + BGFX_CONFIG_MAX_TEXTURE_SAMPLERS * 3];
			const uint8_t entryCount = fillBindGroupLayoutEntry(entries, program, _renderBind, false);
			BX_ASSERT(entryCount < BX_COUNTOF(entries), "");
			BX_ASSERT(program.m_numBindings <= entryCount, "");

			WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.entryCount  = entryCount,
				.entries     = entries,
			};

			WGPUBindGroupLayout bindGroupLayout = WGPU_CHECK(wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc) );

			WGPUPipelineLayoutDescriptor pipelineLayoutDesc =
			{
				.nextInChain          = NULL,
				.label                = WGPU_STRING_VIEW_INIT,
				.bindGroupLayoutCount = 1,
				.bindGroupLayouts     = &bindGroupLayout,
				.immediateSize        = 0,
			};

			WGPUPipelineLayout pipelineLayout = WGPU_CHECK(wgpuDeviceCreatePipelineLayout(m_device, &pipelineLayoutDesc) );

			WGPUBlendState blendState[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			WGPUColorTargetState colorTragetState[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			WGPUDepthStencilState depthStencilState;

			const FrameBufferWGPU& fb = isValid(_fbh)
				? m_frameBuffers[_fbh.idx]
				: m_backBuffer
				;

			const WGPUTextureView depthStencilTextureView = _useDepthAttachment
				? fb.isSwapChain()
					? fb.m_swapChain.m_depthStencilView
					: fb.m_depthStencilView
				: NULL
				;

			const TextureFormat::Enum formatDepthStencil = fb.isSwapChain()
				? fb.m_swapChain.m_resolution.formatDepthStencil
				: TextureFormat::Enum(fb.m_formatDepthStencil)
				;

			const bool hasFragmentShader = NULL != program.m_fsh;

			const uint32_t targetCount = hasFragmentShader ? setColorTargetState(blendState, colorTragetState, fb, _state) : 0;

			if (NULL != depthStencilTextureView)
			{
				setDepthStencilState(depthStencilState, formatDepthStencil, _state, _stencil);
			}
			else
			{
				depthStencilState.format = WGPUTextureFormat_Undefined;
			}

			WGPUFragmentState fragmentState =
			{
				.nextInChain   = NULL,
				.module        = hasFragmentShader ? program.m_fsh->m_module : NULL,
				.entryPoint    = WGPU_STRING_VIEW_INIT, // toWGPUStringView("main"),
				.constantCount = 0,
				.constants     = NULL,
				.targetCount   = targetCount,
				.targets       = colorTragetState,
			};

			const uint32_t cull = (_state&BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT;
			const PrimInfo& primInfo = s_primInfo[(_state&BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT];

			WGPURenderPipelineDescriptor renderPipelineDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.layout      = pipelineLayout,
				.vertex =
				{
					.nextInChain   = NULL,
					.module        = program.m_vsh->m_module,
					.entryPoint    = WGPU_STRING_VIEW_INIT, // toWGPUStringView("main"),
					.constantCount = 0,
					.constants     = NULL,
					.bufferCount   = numStreams,
					.buffers       = vertexBufferLayout,
				},
				.primitive =
				{
					.nextInChain      = NULL,
					.topology         = primInfo.m_topology,
					.stripIndexFormat = primInfo.m_stripIndexFormat[!_isIndex16],
					.frontFace        = !!(_state&BGFX_STATE_FRONT_CCW) ? WGPUFrontFace_CCW : WGPUFrontFace_CW,
					.cullMode         = s_cullMode[cull],
					.unclippedDepth   = !m_depthClamp,
				},
				.depthStencil = WGPUTextureFormat_Undefined == depthStencilState.format
					? NULL
					: &depthStencilState
					,
				.multisample =
				{
					.nextInChain            = NULL,
					.count                  = _msaaCount,
					.mask                   = 0xffffffff,
					.alphaToCoverageEnabled = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state),
				},
				.fragment = hasFragmentShader ? &fragmentState : NULL,
			};

			renderPipeline = m_renderPipelineCache.add(
				  hash
				, {
					.bindGroupLayout = bindGroupLayout,
					.pipeline        = wgpuDeviceCreateRenderPipeline(m_device, &renderPipelineDesc),
				}
				, 0
				);
			wgpuRelease(pipelineLayout);

			return renderPipeline;
		}

		BindGroup createBindGroup(WGPUBindGroupLayout _bindGroupLayout, const ProgramWGPU& _program, const RenderBind& _renderBind, const ChunkedScratchBufferOffset& _sbo, bool _isCompute)
		{
			const uint32_t vsSize = _program.m_vsh->m_size;
			const uint32_t fsSize = NULL == _program.m_fsh ? 0 : _program.m_fsh->m_size;

			WGPUBindGroupEntry bindGroupEntry[2 + BGFX_CONFIG_MAX_TEXTURE_SAMPLERS*3];
			uint32_t entryCount = 0;
			uint32_t numOffsets = 0;

			if (0 < vsSize)
			{
				bindGroupEntry[entryCount++] =
				{
					.nextInChain = NULL,
					.binding     = 0,
					.buffer      = _sbo.buffer,
					.offset      = 0,
					.size        = _program.m_vsh->m_blockSize,
					.sampler     = NULL,
					.textureView = NULL,
				};

				++numOffsets;
			}

			if (0 < fsSize)
			{
				bindGroupEntry[entryCount++] =
				{
					.nextInChain = NULL,
					.binding     = 1,
					.buffer      = _sbo.buffer,
					.offset      = 0,
					.size        = _program.m_fsh->m_blockSize,
					.sampler     = NULL,
					.textureView = NULL,
				};

				++numOffsets;
			}

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const Binding& bind = _renderBind.m_bind[stage];
				const ShaderBinding& shaderBind = _program.m_shaderBinding[stage];

				if (isValid(shaderBind.uniformHandle) )
				{
					switch (bind.m_type)
					{
					case Binding::Image:
					case Binding::Texture:
						{
							const TextureWGPU& texture = m_textures[bind.m_idx];

							bindGroupEntry[entryCount++] =
							{
								.nextInChain = NULL,
								.binding     = shaderBind.binding,
								.buffer      = NULL,
								.offset      = 0,
								.size        = 0,
								.sampler     = NULL,
								.textureView = _isCompute
									? texture.getTextureView(bind.m_mip, 1, Binding::Image == bind.m_type)
									: texture.getTextureView(0, UINT8_MAX, false)
									,
							};

							if (!_isCompute
							||  ShaderBinding::Type::Sampler == shaderBind.type)
							{
								bindGroupEntry[entryCount++] =
								{
									.nextInChain = NULL,
									.binding     = shaderBind.samplerBinding,
									.buffer      = NULL,
									.offset      = 0,
									.size        = 0,
									.sampler     = texture.getSamplerState(bind.m_samplerFlags),
									.textureView = NULL,
								};
							}
						}
						break;

					case Binding::IndexBuffer:
					case Binding::VertexBuffer:
						{
							BufferWGPU& buffer = Binding::IndexBuffer == bind.m_type
								? m_indexBuffers[bind.m_idx]
								: m_vertexBuffers[bind.m_idx]
								;

							bindGroupEntry[entryCount++] =
							{
								.nextInChain = NULL,
								.binding     = shaderBind.binding,
								.buffer      = buffer.m_buffer,
								.offset      = 0,
								.size        = buffer.m_size,
								.sampler     = NULL,
								.textureView = NULL,
							};
						}
						break;
					}
				}
			}

			BX_ASSERT(_program.m_numBindings <= entryCount, "");

			WGPUBindGroupDescriptor bindGroupDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.layout      = _bindGroupLayout,
				.entryCount  = entryCount,
				.entries     = bindGroupEntry,
			};

			WGPUBindGroup bindGroup = WGPU_CHECK(wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc) );

			return {
					.bindGroup  = bindGroup,
					.numOffsets = numOffsets,
				};
		}

		void setDebugWireframe(bool _wireframe)
		{
			if (m_wireframe != _wireframe)
			{
				m_wireframe = _wireframe;
				m_renderPipelineCache.invalidate();
			}
		}

		uint32_t setColorTargetState(WGPUBlendState* _outBlendState, WGPUColorTargetState* _outColorTargetState, const FrameBufferWGPU& _fb, uint64_t _state, uint32_t _rgba = 0)
		{
			BX_UNUSED(_rgba);

			if (0 == _fb.m_numColorAttachments
			&&  !_fb.isSwapChain() )
			{
				return 0;
			}

//			const bool alphaToCoverageEnable  = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);
			const bool blendEnabled           = !!(BGFX_STATE_BLEND_MASK & _state);
			const bool independentBlendEnable = blendEnabled && !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

			if (blendEnabled)
			{
//				constexpr uint32_t kBlendOne = (BGFX_STATE_BLEND_ONE & BGFX_STATE_BLEND_MASK) >> BGFX_STATE_BLEND_SHIFT;

				const uint32_t blend    = uint32_t( (_state & BGFX_STATE_BLEND_MASK         ) >> BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t equRGB = (equation     ) & 0x7;
				const uint32_t equA   = (equation >> 3) & 0x7;

				const bool equRGBIsMinOrMax = 3 <= equRGB;
				const bool equAIsMinOrMax   = 3 <= equA;

				const uint32_t srcRGB = equRGBIsMinOrMax ? 0 : (blend      ) & 0xf;
				const uint32_t dstRGB = equRGBIsMinOrMax ? 0 : (blend >>  4) & 0xf;
				const uint32_t srcA   = equAIsMinOrMax   ? 0 : (blend >>  8) & 0xf;
				const uint32_t dstA   = equAIsMinOrMax   ? 0 : (blend >> 12) & 0xf;

				_outBlendState[0] =
				{
					.color =
					{
						.operation = s_blendEquation[equRGB],
						.srcFactor = s_blendFactor[srcRGB][0],
						.dstFactor = s_blendFactor[dstRGB][0],
					},
					.alpha =
					{
						.operation = s_blendEquation[equA],
						.srcFactor = s_blendFactor[srcA][1],
						.dstFactor = s_blendFactor[dstA][1],
					},
				};
			}

			if (independentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii, rgba >>= 11)
				{
					const uint32_t src      = (rgba     ) & 0xf;
					const uint32_t dst      = (rgba >> 4) & 0xf;
					const uint32_t equation = (rgba >> 8) & 0x7;

					_outBlendState[ii] =
					{
						.color =
						{
							.operation = s_blendEquation[equation],
							.srcFactor = s_blendFactor[src][0],
							.dstFactor = s_blendFactor[dst][0],
						},
						.alpha =
						{
							.operation = s_blendEquation[equation],
							.srcFactor = s_blendFactor[src][1],
							.dstFactor = s_blendFactor[dst][1],
						},
					};
				}
			}

			const bool isSwapChain = _fb.isSwapChain();
			const uint32_t numAttachments = isSwapChain ? 1 : _fb.m_numColorAttachments;
			const WGPUBlendState* blendState = blendEnabled ? &_outBlendState[0] : NULL;
			const WGPUColorWriteMask writeMask = 0
				| ( (_state & BGFX_STATE_WRITE_R) ? WGPUColorWriteMask_Red   : 0)
				| ( (_state & BGFX_STATE_WRITE_G) ? WGPUColorWriteMask_Green : 0)
				| ( (_state & BGFX_STATE_WRITE_B) ? WGPUColorWriteMask_Blue  : 0)
				| ( (_state & BGFX_STATE_WRITE_A) ? WGPUColorWriteMask_Alpha : 0)
				;

			for (uint32_t ii = 0; ii < numAttachments; ++ii)
			{
				TextureFormat::Enum textureFormat = isSwapChain
					? _fb.m_swapChain.m_resolution.formatColor
					: TextureFormat::Enum(m_textures[_fb.m_texture[ii].idx].m_textureFormat)
					;

				_outColorTargetState[ii] =
				{
					.nextInChain = NULL,
					.format      = s_textureFormat[textureFormat].m_fmt,
					.blend       = independentBlendEnable ? &_outBlendState[ii] : blendState,
					.writeMask   = writeMask,
				};
			}

			return numAttachments;
		}

		bool hasStencil(TextureFormat::Enum _format)
		{
			return 0 < bimg::getBlockInfo(bimg::TextureFormat::Enum(_format) ).stencilBits;
		}

		void setDepthStencilState(WGPUDepthStencilState& _outDepthStencilState, TextureFormat::Enum _format, uint64_t _state, uint64_t _stencil)
		{
			_stencil = 0 == _stencil ? kStencilDisabled : _stencil;

			const uint32_t fstencil = unpackStencil(0, _stencil);
			      uint32_t bstencil = unpackStencil(1, _stencil);
			const uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			const uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;

			_outDepthStencilState =
			{
				.nextInChain       = NULL,
				.format            = s_textureFormat[_format].m_fmt,
				.depthWriteEnabled = WGPUOptionalBool(!!(BGFX_STATE_WRITE_Z & _state) ),
				.depthCompare      = s_cmpFunc[func],
				.stencilFront =
				{
					.compare     = s_cmpFunc[(fstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT],
					.failOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT],
					.depthFailOp = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT],
					.passOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT],
				},
				.stencilBack =
				{
					.compare     = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT],
					.failOp      = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT],
					.depthFailOp = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT],
					.passOp      = s_stencilOp[(bstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT],
				},
				.stencilReadMask     = (fstencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT,
				.stencilWriteMask    = 0xff,
				.depthBias           = 0,
				.depthBiasSlopeScale = 0.0f,
				.depthBiasClamp      = 0.0f,
			};
		}

		void* m_webgpuDll;
		void* m_renderDocDll;

		WGPUInstance m_instance;
		WGPUAdapter  m_adapter;
		WGPUDevice   m_device;

		TimerQueryWGPU           m_gpuTimer;
		OcclusionQueryWGPU       m_occlusionQuery;
		ChunkedScratchBufferWGPU m_uniformScratchBuffer;

		WGPULimits m_limits;

		uint32_t         m_maxFrameLatency;
		CommandQueueWGPU m_cmd;

		Resolution m_resolution;
		uint16_t m_maxAnisotropy;
		bool m_depthClamp;
		bool m_wireframe;

		IndexBufferWGPU  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferWGPU m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderWGPU       m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramWGPU      m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureWGPU      m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout     m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferWGPU  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		StateCacheLru<ComputePipeline, 1024> m_computePipelineCache;
		StateCacheLru<RenderPipeline, 1024>  m_renderPipelineCache;
		StateCacheT<WGPUTextureView>         m_textureViewStateCache;
		StateCacheT<WGPUSampler>             m_samplerStateCache;

		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		FrameBufferWGPU m_backBuffer;

		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		int64_t m_presentElapsed;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64<<10];
		uint8_t m_vsScratch[64<<10];
	};

	static RendererContextWGPU* s_renderWGPU;

	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		s_renderWGPU = BX_NEW(g_allocator, RendererContextWGPU);
		if (!s_renderWGPU->init(_init) )
		{
			bx::deleteObject(g_allocator, s_renderWGPU);
			s_renderWGPU = NULL;
		}
		return s_renderWGPU;
	}

	void rendererDestroy()
	{
		s_renderWGPU->shutdown();
		bx::deleteObject(g_allocator, s_renderWGPU);
		s_renderWGPU = NULL;
	}

	void stubRenderPassEncoderMultiDrawIndirect(WGPURenderPassEncoder _renderPassEncoder, WGPUBuffer _indirectBuffer, uint64_t _indirectOffset, uint32_t _maxDrawCount, WGPUBuffer _drawCountBuffer, uint64_t _drawCountBufferOffset)
	{
		BX_ASSERT(NULL == _drawCountBuffer, "stubRenderPassEncoderMultiDrawIndirect doesn't support count buffer.");
		BX_UNUSED(_drawCountBuffer, _drawCountBufferOffset);

		for (uint32_t ii = 0; ii < _maxDrawCount; ++ii)
		{
			wgpuRenderPassEncoderDrawIndirect(
				  _renderPassEncoder
				, _indirectBuffer
				, _indirectOffset
				);

			_indirectOffset += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
		}
	}

	void stubRenderPassEncoderMultiDrawIndexedIndirect(WGPURenderPassEncoder _renderPassEncoder, WGPUBuffer _indirectBuffer, uint64_t _indirectOffset, uint32_t _maxDrawCount, WGPUBuffer _drawCountBuffer, uint64_t _drawCountBufferOffset)
	{
		BX_ASSERT(NULL == _drawCountBuffer, "stubRenderPassEncoderMultiDrawIndexedIndirect doesn't support count buffer.");
		BX_UNUSED(_drawCountBuffer, _drawCountBufferOffset);

		for (uint32_t ii = 0; ii < _maxDrawCount; ++ii)
		{
			wgpuRenderPassEncoderDrawIndexedIndirect(
				  _renderPassEncoder
				, _indirectBuffer
				, _indirectOffset
				);

			_indirectOffset += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
		}
	}

	void ChunkedScratchBufferWGPU::create(uint32_t _chunkSize, uint32_t _numChunks, WGPUBufferUsage _usage, uint32_t _align)
	{
		const uint32_t chunkSize = bx::alignUp(_chunkSize, 1<<20);

		m_chunkPos  = 0;
		m_chunkSize = chunkSize;
		m_align     = _align;
		m_usage     = _usage;

		m_chunkControl.m_size = 0;
		m_chunkControl.reset();

		bx::memSet(m_consume, 0, sizeof(m_consume) );
		m_totalUsed = 0;

		for (uint32_t ii = 0; ii < _numChunks; ++ii)
		{
			addChunk();
		}
	}

	void ChunkedScratchBufferWGPU::createUniform(uint32_t _chunkSize, uint32_t _numChunks)
	{
		const WGPULimits& limits = s_renderWGPU->m_limits;
		const uint32_t align = uint32_t(limits.minUniformBufferOffsetAlignment);

		create(_chunkSize, _numChunks, WGPUBufferUsage_Uniform, align);
	}

	void ChunkedScratchBufferWGPU::destroy()
	{
		for (Chunk& sbc : m_chunks)
		{
			wgpuRelease(sbc.buffer);
			bx::free(g_allocator, sbc.data);
		}
	}

	void ChunkedScratchBufferWGPU::addChunk(uint32_t _at)
	{
		Chunk sbc;

		WGPUBufferDescriptor bufferDesc =
		{
			.nextInChain = NULL,
			.label = toWGPUStringView("uniform buffer"),
			.usage = 0
				| m_usage
				| WGPUBufferUsage_CopyDst
				,
			.size = m_chunkSize,
			.mappedAtCreation = false,
		};

		sbc.buffer = WGPU_CHECK(wgpuDeviceCreateBuffer(s_renderWGPU->m_device, &bufferDesc) );
		sbc.data   = (uint8_t*)bx::alloc(g_allocator, m_chunkSize);

		const uint32_t lastChunk = bx::max(uint32_t(m_chunks.size()-1), 1);
		const uint32_t at = UINT32_MAX == _at ? lastChunk : _at;
		const uint32_t chunkIndex = at % bx::max(m_chunks.size(), 1);

		m_chunkControl.resize(m_chunkSize);

		m_chunks.insert(&m_chunks[chunkIndex], sbc);
	}

	ChunkedScratchBufferAlloc ChunkedScratchBufferWGPU::alloc(uint32_t _size)
	{
		BX_ASSERT(_size < m_chunkSize, "Size can't be larger than chunk size (size: %d, chunk size: %d)!", _size, m_chunkSize);

		uint32_t offset     = m_chunkPos;
		uint32_t nextOffset = offset + _size;
		uint32_t chunkIdx   = m_chunkControl.m_write/m_chunkSize;

		if (nextOffset >= m_chunkSize)
		{
			const uint32_t total = m_chunkSize - m_chunkPos + _size;
			uint32_t reserved    = m_chunkControl.reserve(total, true);

			if (total != reserved)
			{
				addChunk(chunkIdx + 1);
				reserved = m_chunkControl.reserve(total, true);
				BX_ASSERT(total == reserved, "Failed to reserve chunk memory after adding chunk.");
			}

			m_chunkPos = 0;
			offset     = 0;
			nextOffset = _size;
			chunkIdx   = m_chunkControl.m_write/m_chunkSize;
		}
		else
		{
			const uint32_t size = m_chunkControl.reserve(_size, true);
			BX_ASSERT(size == _size, "Failed to reserve chunk memory.");
			BX_UNUSED(size);
		}

		m_chunkPos = nextOffset;

		return { .offset = offset, .chunkIdx = chunkIdx };
	}

	void ChunkedScratchBufferWGPU::write(ChunkedScratchBufferOffset& _outSbo, const void* _vsData, uint32_t _vsSize, const void* _fsData, uint32_t _fsSize)
	{
		const uint32_t vsSize = bx::strideAlign(_vsSize, m_align);
		const uint32_t fsSize = bx::strideAlign(_fsSize, m_align);
		const uint32_t size   = vsSize + fsSize;

		const ChunkedScratchBufferAlloc sba = alloc(size);

		const uint32_t offset0 = sba.offset;
		const uint32_t offset1 = offset0 + vsSize;

		const Chunk& sbc = m_chunks[sba.chunkIdx];

		_outSbo.buffer = sbc.buffer;
		_outSbo.offsets[0] = offset0;
		_outSbo.offsets[1] = offset1;

		bx::memCopy(&sbc.data[offset0], _vsData, _vsSize);
		bx::memCopy(&sbc.data[offset1], _fsData, _fsSize);
	}

	void ChunkedScratchBufferWGPU::begin()
	{
		BX_ASSERT(0 == m_chunkPos, "");
		const uint32_t numConsumed = m_consume[s_renderWGPU->m_cmd.m_currentFrameInFlight];
		m_chunkControl.consume(numConsumed);
	}

	void ChunkedScratchBufferWGPU::end()
	{
		uint32_t numFlush = m_chunkControl.getNumReserved();

		if (0 != m_chunkPos)
		{
retry:
			const uint32_t remainder = m_chunkSize - m_chunkPos;
			const uint32_t rem = m_chunkControl.reserve(remainder, true);

			if (rem != remainder)
			{
				const uint32_t chunkIdx = m_chunkControl.m_write/m_chunkSize;
				addChunk(chunkIdx + 1);
				goto retry;
			}

			m_chunkPos = 0;
		}

		const uint32_t numReserved = m_chunkControl.getNumReserved();
		BX_ASSERT(0 == numReserved % m_chunkSize, "Number of reserved must always be aligned to chunk size!");

		const uint32_t first = m_chunkControl.m_current / m_chunkSize;

		for (uint32_t ii = first, end = numReserved / m_chunkSize + first; ii < end; ++ii)
		{
			const Chunk& chunk = m_chunks[ii % m_chunks.size()];

			s_renderWGPU->m_cmd.writeBuffer(chunk.buffer, 0, chunk.data, bx::min(numFlush, m_chunkSize) );

			m_chunkControl.commit(m_chunkSize);
			numFlush = bx::uint32_satsub(numFlush, m_chunkSize);
		}

		m_consume[s_renderWGPU->m_cmd.m_currentFrameInFlight] = numReserved;

		m_totalUsed = m_chunkControl.getNumUsed();
	}

	void ChunkedScratchBufferWGPU::flush()
	{
		end();
		begin();
	}

	void BufferWGPU::create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride)
	{
		BX_UNUSED(_stride);

		m_size  = bx::alignUp(_size, 4);
		m_flags = _flags;

		const bool indirect = !!(m_flags & BGFX_BUFFER_DRAW_INDIRECT);
		const bool storage  = indirect || !!(m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE);

		WGPUBufferDescriptor bufferDesc =
		{
			.nextInChain = NULL,
			.label = WGPU_STRING_VIEW_INIT,
			.usage = 0
				| (storage ? WGPUBufferUsage_Storage : 0)
				| (indirect
					? WGPUBufferUsage_Indirect
					: _vertex ? WGPUBufferUsage_Vertex : WGPUBufferUsage_Index
				  )
				| WGPUBufferUsage_CopyDst
				,
			.size = m_size,
			.mappedAtCreation = false,
		};

		m_buffer = WGPU_CHECK(wgpuDeviceCreateBuffer(s_renderWGPU->m_device, &bufferDesc) );

		if (NULL != _data)
		{
			s_renderWGPU->m_cmd.writeBuffer(m_buffer, 0, _data, m_size);
		}
	}

	void BufferWGPU::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard) const
	{
		BX_UNUSED(_discard);
		s_renderWGPU->m_cmd.writeBuffer(m_buffer, _offset, _data, bx::alignUp(_size, 4) );
	}

	void BufferWGPU::destroy()
	{
		wgpuDestroy(m_buffer);
	}

	void VertexBufferWGPU::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		BufferWGPU::create(_size, _data, _flags, true);
		m_layoutHandle = _layoutHandle;
	}

	void ShaderWGPU::create(const Memory* _mem)
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
		m_numUniforms   = count;
		m_numTextures   = 0;

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++ii)
		{
			m_shaderBinding[ii].clear();
		}

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize, &err);

				char name[256];
				bx::read(&reader, &name, nameSize, &err);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type, &err);

				uint8_t num;
				bx::read(&reader, num, &err);

				uint16_t regIndex;
				bx::read(&reader, regIndex, &err);

				uint16_t regCount;
				bx::read(&reader, regCount, &err);

				const bool hasTexData   = !isShaderVerLess(magic, 8);
				const bool hasTexFormat = !isShaderVerLess(magic, 10);
				uint8_t  texComponent   = 0;
				uint8_t  texDimension   = 0;
				uint16_t texFormat      = 0;

				if (hasTexData)
				{
					bx::read(&reader, texComponent, &err);
					bx::read(&reader, texDimension, &err);
				}

				if (hasTexFormat)
				{
					bx::read(&reader, texFormat, &err);
				}

				const char* kind = "invalid";

				BX_UNUSED(num, texComponent, texFormat);

				if (UINT16_MAX != regIndex)
				{
					PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);

					if (PredefinedUniform::Count != predefined)
					{
						kind = "predefined";
						m_predefined[m_numPredefined].m_loc   = regIndex;
						m_predefined[m_numPredefined].m_count = regCount;
						m_predefined[m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
						m_numPredefined++;
					}
					else if (UniformType::End == (~kUniformMask & type) )
					{
						const bool isBuffer = idToDescriptorType(regCount) == DescriptorType::StorageBuffer;

						if (0 == regIndex)
						{
							continue;
						}

						const uint8_t reverseShift = kSpirvBindShift;

						const uint16_t stage = regIndex - reverseShift; // regIndex is used for buffer binding index
						ShaderBinding& shaderBind = m_shaderBinding[stage];

						shaderBind.type = isBuffer ? ShaderBinding::Type::Buffer : ShaderBinding::Type::Image;
						shaderBind.uniformHandle  = { 0 };
						shaderBind.binding        = regIndex;

						if (isBuffer)
						{
							shaderBind.bufferBindingType = 0 != (kUniformReadOnlyBit & type)
								? WGPUBufferBindingType_ReadOnlyStorage
								: WGPUBufferBindingType_Storage
								;
						}
						else
						{
							shaderBind.bufferBindingType = WGPUBufferBindingType_BindingNotUsed;
						}

						if (!isBuffer
						&&  hasTexData)
						{
							shaderBind.viewDimension = s_textureDimension[idToTextureDimension(texDimension)];
							shaderBind.sampleType    = s_textureComponentType[idToTextureComponentType(texComponent)];
						}
						else
						{
							shaderBind.viewDimension = WGPUTextureViewDimension_Undefined;
							shaderBind.sampleType    = WGPUTextureSampleType_Float;
						}

						kind = "storage";
					}
					else if (UniformType::Sampler == (~kUniformMask & type) )
					{
						const UniformRegInfo* info = s_renderWGPU->m_uniformReg.find(name);
						BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

						const uint8_t reverseShift = kSpirvBindShift;

						const uint16_t stage = regIndex - reverseShift; // regIndex is used for image/sampler binding index
						ShaderBinding& shaderBind = m_shaderBinding[stage];

						shaderBind.uniformHandle    = info->m_handle;
						shaderBind.type             = ShaderBinding::Type::Sampler;
						shaderBind.binding          = regIndex;
						shaderBind.samplerBinding   = regIndex + kSpirvSamplerShift;

						if (hasTexData)
						{
							shaderBind.viewDimension = s_textureDimension[idToTextureDimension(texDimension)];
							shaderBind.sampleType    = s_textureComponentType[idToTextureComponentType(texComponent)];
						}
						else
						{
							shaderBind.viewDimension = WGPUTextureViewDimension_Undefined;
							shaderBind.sampleType    = WGPUTextureSampleType_Float;
						}

						if (type & kUniformCompareBit)
						{
							shaderBind.sampleType = WGPUTextureSampleType_Depth;
						}

						kind = "sampler";
					}
					else
					{
						const UniformRegInfo* info = s_renderWGPU->m_uniformReg.find(name);
						BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

						if (NULL != info)
						{
							if (NULL == m_constantBuffer)
							{
								m_constantBuffer = UniformBuffer::create(1024);
							}

							kind = "user";
							m_constantBuffer->writeUniformHandle(type|fragmentBit, regIndex, info->m_handle, regCount);
						}
					}
				}

				BX_TRACE("\t%s: %s (%s), r.index %3d, r.count %2d, r.texComponent %1d, r.texDimension %1d"
					, kind
					, name
					, getUniformTypeName(UniformType::Enum(type&~kUniformMask) )
					, regIndex
					, regCount
					, texComponent
					, texDimension
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

		const void* code = reader.getDataPtr();

		bx::skip(&reader, shaderSize+1);

		m_code = alloc(shaderSize);
		bx::memCopy(m_code->data, code, shaderSize);

		WGPUShaderSourceWGSL shaderSourceWgsl =
		{
			.chain =
			{
				.next = NULL,
				.sType = WGPUSType_ShaderSourceWGSL,
			},
			.code =
			{
				.data   = (const char*)m_code->data,
				.length = m_code->size,
			},
		};

		WGPUShaderModuleDescriptor shaderModuleDesc =
		{
			.nextInChain = &shaderSourceWgsl.chain,
			.label = WGPU_STRING_VIEW_INIT,
		};

		m_module = WGPU_CHECK(wgpuDeviceCreateShaderModule(s_renderWGPU->m_device, &shaderModuleDesc) );
		BX_ASSERT(NULL != m_module, "");

		bx::memSet(m_attrMask,  0, sizeof(m_attrMask) );
		bx::memSet(m_attrRemap, 0, sizeof(m_attrRemap) );

		bx::read(&reader, m_numAttrs, &err);

		for (uint8_t ii = 0; ii < m_numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id, &err);

			Attrib::Enum attr = idToAttrib(id);

			if (Attrib::Count != attr)
			{
				m_attrMask[attr]  = UINT16_MAX;
				m_attrRemap[attr] = ii;
			}
		}

		bx::HashMurmur3 murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(m_code->data, m_code->size);
		murmur.add(m_numAttrs);
		murmur.add(m_attrMask,  m_numAttrs);
		murmur.add(m_attrRemap, m_numAttrs);
		m_hash = murmur.end();

		bx::read(&reader, m_size, &err);
		bx::read(&reader, m_blockSize, &err);
	}

	void ShaderWGPU::destroy()
	{
		if (NULL != m_constantBuffer)
		{
			UniformBuffer::destroy(m_constantBuffer);
			m_constantBuffer = NULL;
		}

		m_numPredefined = 0;

		if (NULL != m_code)
		{
			release(m_code);
			m_code = NULL;
			m_hash = 0;
		}

		wgpuRelease(m_module);
	}

	void ProgramWGPU::create(const ShaderWGPU* _vsh, const ShaderWGPU* _fsh)
	{
		BX_ASSERT(_vsh->m_module, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		m_fsh = _fsh;

		const bool isCompute = NULL == m_fsh;

		m_vsh = _vsh;
		bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof(PredefinedUniform) );
		m_numPredefined = _vsh->m_numPredefined;

		if (NULL != _fsh)
		{
			m_fsh = _fsh;
			bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof(PredefinedUniform) );
			m_numPredefined += _fsh->m_numPredefined;
		}

		const uint32_t vsSize = m_vsh->m_size;
		const uint32_t fsSize = NULL != m_fsh ? m_fsh->m_size  : 0;

		uint8_t numBindings = 0
			+ (0 < vsSize)
			+ (0 < fsSize)
			;

		if (isCompute)
		{
			for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				ShaderBinding& shaderBind = m_shaderBinding[stage];
				shaderBind.clear();

				if (isValid(m_vsh->m_shaderBinding[stage].uniformHandle) )
				{
					shaderBind = m_vsh->m_shaderBinding[stage];
					shaderBind.shaderStage = WGPUShaderStage_Compute;
					numBindings++;
				}
			}
		}
		else
		{
			for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				ShaderBinding& shaderBind = m_shaderBinding[stage];
				shaderBind.clear();

				if (isValid(m_vsh->m_shaderBinding[stage].uniformHandle) )
				{
					shaderBind = m_vsh->m_shaderBinding[stage];
					shaderBind.shaderStage = WGPUShaderStage_Vertex;
					numBindings++;
				}
				else if (NULL != m_fsh && isValid(m_fsh->m_shaderBinding[stage].uniformHandle) )
				{
					shaderBind = m_fsh->m_shaderBinding[stage];
					shaderBind.shaderStage = WGPUShaderStage_Fragment;
					numBindings += 2;
				}
			}
		}

		m_numBindings = numBindings;
	}

	void ProgramWGPU::destroy()
	{
		m_numBindings   = 0;
		m_numPredefined = 0;
		m_vsh = NULL;
		m_fsh = NULL;
	}

	void TextureWGPU::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
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

			WGPUTextureDimension dimension = WGPUTextureDimension_2D;
			uint32_t depthOrArrayLayers = 1;

			if (imageContainer.m_cubeMap)
			{
				m_type = TextureCube;
				m_viewDimension = 1 < m_numLayers
					? WGPUTextureViewDimension_CubeArray
					: WGPUTextureViewDimension_Cube
					;
				depthOrArrayLayers = 6;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = Texture3D;
				m_viewDimension = WGPUTextureViewDimension_3D;

				dimension = WGPUTextureDimension_3D;
				depthOrArrayLayers = m_depth;
			}
			else
			{
				m_type = Texture2D;
				m_viewDimension = 1 < m_numLayers
					? WGPUTextureViewDimension_2DArray
					: WGPUTextureViewDimension_2D
					;
				depthOrArrayLayers = m_numLayers;
			}

			m_numMips = ti.numMips;
			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool swizzle    = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);

			const bool writeOnly    = 0 != (m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags&BGFX_TEXTURE_RT_MASK);
			const bool blit         = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);

			const uint32_t msaaQuality = bx::uint32_satsub((m_flags & BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const uint32_t msaaCount   = 1; //s_msaa[msaaQuality];
			BX_UNUSED(msaaQuality);

			const bool needResolve = true
				&& 1 < msaaCount
				&& 0 == (m_flags & BGFX_TEXTURE_MSAA_SAMPLE)
				&& !writeOnly
				;

			BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s RT[%c], BO[%c], CW[%c]%s."
				, this - s_renderWGPU->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly    ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);
			BX_UNUSED(swizzle);

			WGPUTextureDescriptor textureDesc =
			{
				.nextInChain = NULL,
				.label       = WGPU_STRING_VIEW_INIT,
				.usage       = 0
					| WGPUTextureUsage_TextureBinding
					| WGPUTextureUsage_CopySrc
					| (!writeOnly   ? WGPUTextureUsage_CopyDst          : 0)
					| (blit         ? WGPUTextureUsage_CopyDst          : 0)
					| (computeWrite ? WGPUTextureUsage_StorageBinding   : 0)
					| (renderTarget ? WGPUTextureUsage_RenderAttachment : 0)
					,
				.dimension = dimension,
				.size =
				{
					.width  = m_width,
					.height = m_height,
					.depthOrArrayLayers = depthOrArrayLayers,
				},
				.format = s_textureFormat[m_textureFormat].m_fmt,
				.mipLevelCount   = m_numMips,
				.sampleCount     = msaaCount,
				.viewFormatCount = 0,
				.viewFormats     = NULL,
			};

			m_texture = WGPU_CHECK(wgpuDeviceCreateTexture(s_renderWGPU->m_device, &textureDesc) );

			if (needResolve)
			{
				textureDesc.sampleCount = 1;
				m_textureResolve = WGPU_CHECK(wgpuDeviceCreateTexture(s_renderWGPU->m_device, &textureDesc) );
			}

			WGPUTexelCopyTextureInfo copyTextureDst =
			{
				.texture  = m_texture,
				.mipLevel = 0,
				.origin =
				{
					.x = 0,
					.y = 0,
					.z = 0,
				},
				.aspect = WGPUTextureAspect_All,
			};

			uint8_t* temp = convert ? (uint8_t*)bx::alloc(g_allocator, m_width*m_height*bpp/8) : NULL;

			for (uint16_t side = 0; side < numSides; ++side)
			{
				copyTextureDst.origin.z = side;

				for (uint8_t lod = 0; lod < ti.numMips; ++lod)
				{
					copyTextureDst.mipLevel = lod;

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						if (convert)
						{
							const uint32_t mipWidth    = bx::max<uint32_t>(mip.m_width,  4);
							const uint32_t mipHeight   = bx::max<uint32_t>(mip.m_height, 4);
							const uint32_t bytesPerRow = mipWidth*bpp/8;
							const uint32_t width       = bx::max<uint32_t>(m_width  >> lod, 1);
							const uint32_t height      = bx::max<uint32_t>(m_height >> lod, 1);
							const uint32_t size        = bytesPerRow*height*mip.m_depth;

							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mipWidth
								, mipHeight
								, bytesPerRow
								, bimg::TextureFormat::Enum(m_requestedFormat)
								);

							s_renderWGPU->m_cmd.writeTexture(
								  copyTextureDst
								, temp
								, size
								, {
									.offset       = 0,
									.bytesPerRow  = bytesPerRow,
									.rowsPerImage = height,
								}
								, {
									.width              = width,
									.height             = height,
									.depthOrArrayLayers = mip.m_depth,
								});
						}
						else if (compressed)
						{
							const uint32_t width       = mip.m_width;
							const uint32_t height      = mip.m_height;
							const uint32_t bytesPerRow = (mip.m_width/blockInfo.blockWidth)*mip.m_blockSize;

							s_renderWGPU->m_cmd.writeTexture(
								  copyTextureDst
								, mip.m_data
								, mip.m_size
								, {
									.offset       = 0,
									.bytesPerRow  = bytesPerRow,
									.rowsPerImage = height,
								}
								, {
									.width              = width,
									.height             = height,
									.depthOrArrayLayers = mip.m_depth,
								});
						}
						else
						{
							const uint32_t width       = mip.m_width;
							const uint32_t height      = mip.m_height;
							const uint32_t bytesPerRow = mip.m_width*mip.m_bpp / 8;

							s_renderWGPU->m_cmd.writeTexture(
								  copyTextureDst
								, mip.m_data
								, mip.m_size
								, {
									.offset       = 0,
									.bytesPerRow  = bytesPerRow,
									.rowsPerImage = height,
								}
								, {
									.width              = width,
									.height             = height,
									.depthOrArrayLayers = mip.m_depth,
								});
						}
					}
				}
			}

			if (NULL != temp)
			{
				bx::free(g_allocator, temp);
			}
		}
	}

	void TextureWGPU::destroy()
	{
		wgpuDestroy(m_texture);
		wgpuDestroy(m_textureResolve);
	}

	void TextureWGPU::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		uint32_t rectPitch = _rect.m_width*bpp/8;
		const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat) );

		if (bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) ) )
		{
			rectPitch = (_rect.m_width / blockInfo.blockWidth) * blockInfo.blockSize;
		}

		const uint32_t bytesPerRow = UINT16_MAX == _pitch ? rectPitch : _pitch;
		const uint32_t slicePitch  = rectPitch*_rect.m_height;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* srcData = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)bx::alloc(g_allocator, slicePitch);
			bimg::imageDecodeToBgra8(g_allocator, temp, srcData, _rect.m_width, _rect.m_height, bytesPerRow, bimg::TextureFormat::Enum(m_requestedFormat) );
			srcData = temp;

		}

		const uint32_t width   = bx::min(bx::max(1u, bx::alignUp(m_width  >> _mip, blockInfo.blockWidth ) ), _rect.m_width);
		const uint32_t height  = bx::min(bx::max(1u, bx::alignUp(m_height >> _mip, blockInfo.blockHeight) ), _rect.m_height);
		const uint32_t originZ = TextureWGPU::TextureCube == m_type ? _side : _z;

		s_renderWGPU->m_cmd.writeTexture(
			{
				.texture  = m_texture,
				.mipLevel = _mip,
				.origin =
				{
					.x = _rect.m_x,
					.y = _rect.m_y,
					.z = originZ,
				},
				.aspect = WGPUTextureAspect_All,
			}
			, srcData
			, bytesPerRow*height
			, {
				.offset       = 0,
				.bytesPerRow  = bytesPerRow,
				.rowsPerImage = height,
			}
			, {
				.width              = width,
				.height             = height,
				.depthOrArrayLayers = _depth,
			});

		if (NULL != temp)
		{
			bx::free(g_allocator, temp);
		}
	}

	WGPUSampler TextureWGPU::getSamplerState(uint32_t _samplerFlags) const
	{
		uint32_t samplerFlags = (0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _samplerFlags)
			? _samplerFlags
			: m_flags
			) & (BGFX_SAMPLER_BITS_MASK | BGFX_SAMPLER_BORDER_COLOR_MASK | BGFX_SAMPLER_COMPARE_MASK)
			;

		if (WGPUTextureSampleType_UnfilterableFloat == s_textureFormat[m_textureFormat].m_samplerType)
		{
			samplerFlags &= ~(BGFX_SAMPLER_MIN_MASK |BGFX_SAMPLER_MAG_MASK |BGFX_SAMPLER_MIP_MASK);
			samplerFlags |=  (BGFX_SAMPLER_MIN_POINT|BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIP_POINT);
		}

		samplerFlags &= BGFX_SAMPLER_BITS_MASK;
		WGPUSampler sampler = s_renderWGPU->m_samplerStateCache.find(samplerFlags);

		const bool disableAniso = true
			&& (BGFX_SAMPLER_MIN_POINT == (samplerFlags&BGFX_SAMPLER_MIN_POINT) )
			&& (BGFX_SAMPLER_MAG_POINT == (samplerFlags&BGFX_SAMPLER_MAG_POINT) )
			;

		if (NULL == sampler)
		{
			const uint32_t cmpFunc = (samplerFlags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
			WGPUSamplerDescriptor samplerDesc =
			{
				.nextInChain   = NULL,
				.label         = WGPU_STRING_VIEW_INIT,
				.addressModeU  = s_textureAddress[(samplerFlags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT],
				.addressModeV  = s_textureAddress[(samplerFlags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT],
				.addressModeW  = s_textureAddress[(samplerFlags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT],
				.magFilter     = s_textureFilterMinMag[(samplerFlags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT],
				.minFilter     = s_textureFilterMinMag[(samplerFlags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT],
				.mipmapFilter  = s_textureFilterMip[(samplerFlags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT],
				.lodMinClamp   = 0,
				.lodMaxClamp   = bx::kFloatLargest,
				.compare       = 0 == cmpFunc ? WGPUCompareFunction_Undefined : s_cmpFunc[cmpFunc],
				.maxAnisotropy = disableAniso ? uint16_t(1) : s_renderWGPU->m_maxAnisotropy,
			};

			sampler = WGPU_CHECK(wgpuDeviceCreateSampler(s_renderWGPU->m_device, &samplerDesc) );
			s_renderWGPU->m_samplerStateCache.add(samplerFlags, sampler);
		}

		return sampler;
	}

	WGPUTextureView TextureWGPU::getTextureView(uint8_t _baseMipLevel, uint8_t _mipLevelCount, bool _storage) const
	{
		bx::HashMurmur3 murmur;
		murmur.begin();
		murmur.add(uintptr_t(this) );
		murmur.add(_baseMipLevel);
		murmur.add(_mipLevelCount);
		murmur.add(_storage);
		const uint32_t hash = murmur.end();

		WGPUTextureView textureView = s_renderWGPU->m_textureViewStateCache.find(hash);

		if (NULL == textureView)
		{
			WGPUTextureViewDimension tvd = m_viewDimension;
			uint32_t arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;

			if (_storage)
			{
				if (WGPUTextureViewDimension_Cube == tvd)
				{
					tvd = WGPUTextureViewDimension_2DArray;
				}
			}

			WGPUTextureViewDescriptor textureViewDesc =
			{
				.nextInChain     = NULL,
				.label           = WGPU_STRING_VIEW_INIT,
				.format          = s_textureFormat[m_textureFormat].m_fmt,
				.dimension       = tvd,
				.baseMipLevel    = _baseMipLevel,
				.mipLevelCount   = UINT8_MAX == _mipLevelCount ? WGPU_MIP_LEVEL_COUNT_UNDEFINED : _mipLevelCount,
				.baseArrayLayer  = 0,
				.arrayLayerCount = arrayLayerCount,
				.aspect          = WGPUTextureAspect_All,
				.usage           = WGPUTextureUsage_TextureBinding
					| (_storage ? WGPUTextureUsage_StorageBinding : 0)
					,
			};

			textureView = WGPU_CHECK(wgpuTextureCreateView(m_texture, &textureViewDesc) );
			s_renderWGPU->m_textureViewStateCache.add(hash, textureView);
		}

		return textureView;
	}

	struct SwapChainFormatRemap
	{
		WGPUTextureFormat requestedFormat;
		WGPUTextureFormat alternativeFormat;
	};

	static const SwapChainFormatRemap s_swapChainFormatRemap[] =
	{
		{ WGPUTextureFormat_RGBA8Unorm,     WGPUTextureFormat_BGRA8Unorm     },
		{ WGPUTextureFormat_RGBA8UnormSrgb, WGPUTextureFormat_BGRA8UnormSrgb },
	};

	WGPUTextureFormat findSurfaceCapsFormat(const WGPUSurfaceCapabilities& _surfaceCaps, WGPUTextureFormat _requestedFormat)
	{
		for (uint32_t ii = 0; ii < _surfaceCaps.formatCount; ++ii)
		{
			if (_requestedFormat == _surfaceCaps.formats[ii])
			{
				return _requestedFormat;
			}
		}

		return WGPUTextureFormat_Undefined;
	}

	bool SwapChainWGPU::create(void* _nwh, const Resolution& _resolution)
	{
		if (NULL == _nwh
		||  !createSurface(_nwh) )
		{
			return false;
		}

		return configure(_resolution);
	}

	void SwapChainWGPU::destroy()
	{
		WGPU_CHECK(wgpuSurfaceUnconfigure(m_surface) );

		wgpuRelease(m_surface);
		wgpuRelease(m_textureView);
		wgpuRelease(m_depthStencilView);

		m_nwh = NULL;
	}

	bool SwapChainWGPU::configure(const Resolution& _resolution)
	{
		m_resolution = _resolution;

		WGPUSurfaceCapabilities surfaceCaps;
		WGPUStatus status = WGPU_CHECK(wgpuSurfaceGetCapabilities(m_surface, s_renderWGPU->m_adapter, &surfaceCaps) );

		if (WGPUStatus_Success != status)
		{
			return false;
		}

		WGPUTextureFormat requestedFormat = s_textureFormat[m_resolution.formatColor].m_fmt;
		WGPUTextureFormat format = findSurfaceCapsFormat(surfaceCaps, requestedFormat);

		if (WGPUTextureFormat_Undefined == format)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_swapChainFormatRemap); ++ii)
			{
				if (requestedFormat == s_swapChainFormatRemap[ii].requestedFormat)
				{
					format = findSurfaceCapsFormat(surfaceCaps, s_swapChainFormatRemap[ii].alternativeFormat);
m_resolution.formatColor = TextureFormat::BGRA8;
					break;
				}
			}
		}

		BX_ASSERT(WGPUTextureFormat_Undefined != format, "SwapChain surface format is not available!");

		m_surfaceConfig =
		{
			.nextInChain     = NULL,
			.device          = s_renderWGPU->m_device,
			.format          = format,
			.usage           = WGPUTextureUsage_RenderAttachment,
			.width           = m_resolution.width,
			.height          = m_resolution.height,
			.viewFormatCount = 0,
			.viewFormats     = NULL,
			.alphaMode       = WGPUCompositeAlphaMode_Auto,
			.presentMode     = WGPUPresentMode_Fifo,
		};

		WGPU_CHECK(wgpuSurfaceConfigure(m_surface, &m_surfaceConfig) );

		WGPUSurfaceTexture surfaceTexture = WGPU_SURFACE_TEXTURE_INIT;
		WGPU_CHECK(wgpuSurfaceGetCurrentTexture(m_surface, &surfaceTexture) );
		m_textureView = WGPU_CHECK(wgpuTextureCreateView(surfaceTexture.texture, NULL) );
		wgpuRelease(surfaceTexture.texture);

		const uint32_t msaa = s_msaa[(_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

		if (bimg::isDepth(bimg::TextureFormat::Enum(m_resolution.formatDepthStencil) ) )
		{
			WGPUTextureDescriptor textureDesc =
			{
				.nextInChain = NULL,
				.label       = toWGPUStringView("SwapChain Depth/Stencil"),
				.usage       = 0
					| WGPUTextureUsage_RenderAttachment
					,
				.dimension = WGPUTextureDimension_2D,
				.size =
				{
					.width  = m_surfaceConfig.width,
					.height = m_surfaceConfig.height,
					.depthOrArrayLayers = 1,
				},
				.format = s_textureFormat[m_resolution.formatDepthStencil].m_fmt,
				.mipLevelCount   = 1,
				.sampleCount     = msaa,
				.viewFormatCount = 0,
				.viewFormats     = NULL,
			};

			WGPUTexture texture = WGPU_CHECK(wgpuDeviceCreateTexture(s_renderWGPU->m_device, &textureDesc) );

			WGPUTextureViewDescriptor textureViewDesc =
			{
				.nextInChain     = NULL,
				.label           = textureDesc.label,
				.format          = textureDesc.format,
				.dimension       = WGPUTextureViewDimension_2D,
				.baseMipLevel    = 0,
				.mipLevelCount   = 1,
				.baseArrayLayer  = 0,
				.arrayLayerCount = 1,
				.aspect          = WGPUTextureAspect_All,
				.usage           = textureDesc.usage,
			};

			m_depthStencilView   = WGPU_CHECK(wgpuTextureCreateView(texture, &textureViewDesc) );
			m_formatDepthStencil = uint8_t(m_resolution.formatDepthStencil);

			wgpuRelease(texture);
		}

		if (1 < msaa)
		{
			WGPUTextureDescriptor textureDesc =
			{
				.nextInChain = NULL,
				.label       = toWGPUStringView("SwapChain MSAA"),
				.usage       = 0
					| WGPUTextureUsage_RenderAttachment
					,
				.dimension = WGPUTextureDimension_2D,
				.size =
				{
					.width  = m_surfaceConfig.width,
					.height = m_surfaceConfig.height,
					.depthOrArrayLayers = 1,
				},
				.format = format,
				.mipLevelCount   = 1,
				.sampleCount     = msaa,
				.viewFormatCount = 0,
				.viewFormats     = NULL,
			};

			WGPUTexture texture = WGPU_CHECK(wgpuDeviceCreateTexture(s_renderWGPU->m_device, &textureDesc) );

			WGPUTextureViewDescriptor textureViewDesc =
			{
				.nextInChain     = NULL,
				.label           = textureDesc.label,
				.format          = textureDesc.format,
				.dimension       = WGPUTextureViewDimension_2D,
				.baseMipLevel    = 0,
				.mipLevelCount   = 1,
				.baseArrayLayer  = 0,
				.arrayLayerCount = 1,
				.aspect          = WGPUTextureAspect_All,
				.usage           = textureDesc.usage,
			};

			m_msaaTextureView = WGPU_CHECK(wgpuTextureCreateView(texture, &textureViewDesc) );
		}

		return true;
	}

	void SwapChainWGPU::update(void* _nwh, const Resolution& _resolution)
	{
		BX_UNUSED(_nwh);

		wgpuRelease(m_textureView);
		wgpuRelease(m_msaaTextureView);
		wgpuRelease(m_depthStencilView);
		configure(_resolution);
	}

#if BX_PLATFORM_OSX || BX_PLATFORM_IOS || BX_PLATFORM_VISIONOS
	CAMetalLayer* toMetalLayer(void* _nwh)
	{
		if (NULL == _nwh)
		{
			return NULL;
		}

		if (NULL != NSClassFromString(@"MTKView") )
		{
			MTKView* view = (MTKView*)_nwh;

			if (NULL != view
			&& [view isKindOfClass:NSClassFromString(@"MTKView")])
			{
				return (CAMetalLayer*)view.layer;
			}
		}

		if (NULL != NSClassFromString(@"CAMetalLayer") )
		{
			NSObject* nwh = (NSObject*)_nwh;

			if ([nwh isKindOfClass:[CAMetalLayer class]])
			{
				return (CAMetalLayer*)nwh;
			}
			else
			{
#	if BX_PLATFORM_OSX
				__block NSView* contentView = NULL;
				__block CAMetalLayer* metalLayer = NULL;

				if ([nwh isKindOfClass:[NSView class]])
				{
					contentView = (NSView*)nwh;
				}
				else if ([nwh isKindOfClass:[NSWindow class]])
				{
					NSWindow* nsWindow = (NSWindow*)nwh;
					contentView = [nsWindow contentView];
				}
				else
				{
					return NULL;
				}

				void (^setLayer)() =
				^{
					CALayer* layer = contentView.layer;

					if (NULL != layer
					&& [layer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
					{
						metalLayer = (CAMetalLayer*)layer;
					}
					else
					{
						[contentView setWantsLayer: YES];
						metalLayer = [CAMetalLayer layer];
						[contentView setLayer:metalLayer];
					}
				};

				if ([NSThread isMainThread])
				{
					setLayer();
				}
				else
				{
					bx::Semaphore semaphore;
					bx::Semaphore* psemaphore = &semaphore;

					CFRunLoopPerformBlock([[NSRunLoop mainRunLoop] getCFRunLoop], kCFRunLoopCommonModes,
					^{
						setLayer();
						psemaphore->post();
					});

					semaphore.wait();
				}

				return metalLayer;
#	endif // BX_PLATFORM_*
			}
		}

		return NULL;
	}
#endif // BX_PLATFORM_OSX || BX_PLATFORM_IOS || BX_PLATFORM_TVOS || BX_PLATFORM_VISIONOS

	bool SwapChainWGPU::createSurface(void* _nwh)
	{
		m_nwh = _nwh;

		WGPUSurfaceDescriptor surfaceDesc = WGPU_SURFACE_DESCRIPTOR_INIT;

#if BX_PLATFORM_WINDOWS
		WGPUSurfaceSourceWindowsHWND surfaceSource =
		{
			.chain =
			{
				.next  = NULL,
				.sType = WGPUSType_SurfaceSourceWindowsHWND,
			},
			.hinstance = findModule(""),
			.hwnd      = m_nwh,
		};

		surfaceDesc =
		{
			.nextInChain = &surfaceSource.chain,
			.label = toWGPUStringView("SwapChainWGPU"),
		};
#elif BX_PLATFORM_LINUX
		WGPUSurfaceSourceXlibWindow surfaceSourceXlib =
		{
			.chain =
			{
				.next  = NULL,
				.sType = WGPUSType_SurfaceSourceXlibWindow,
			},
			.display = g_platformData.ndt,
			.window  = uint64_t(m_nwh),
		};

		WGPUSurfaceSourceWaylandSurface surfaceSourceWayland =
		{
			.chain =
			{
				.next  = NULL,
				.sType = WGPUSType_SurfaceSourceWaylandSurface,
			},
			.display = g_platformData.ndt,
			.surface = m_nwh,
		};

		surfaceDesc =
		{
			.nextInChain = g_platformData.type == bgfx::NativeWindowHandleType::Wayland
				? &surfaceSourceWayland.chain
				: &surfaceSourceXlib.chain
				,
			.label = toWGPUStringView("SwapChainWGPU"),
		};
#elif BX_PLATFORM_OSX
		WGPUSurfaceSourceMetalLayer surfaceSource =
		{
			.chain =
			{
				.next  = NULL,
				.sType = WGPUSType_SurfaceSourceMetalLayer,
			},
			.layer = toMetalLayer(m_nwh),
		};

		surfaceDesc =
		{
			.nextInChain = &surfaceSource.chain,
			.label = toWGPUStringView("SwapChainWGPU"),
		};
#else
#	error "Figure out WGPU surface..."
#endif // BX_PLATFORM_*

		m_surface = WGPU_CHECK(wgpuInstanceCreateSurface(s_renderWGPU->m_instance, &surfaceDesc) );

		return NULL != m_surface;
	}

	void SwapChainWGPU::present()
	{
		wgpuRelease(m_textureView);
		WGPU_CHECK(wgpuSurfacePresent(m_surface) );

		WGPUSurfaceTexture surfaceTexture = WGPU_SURFACE_TEXTURE_INIT;
		wgpuSurfaceGetCurrentTexture(m_surface, &surfaceTexture);

		switch (surfaceTexture.status)
		{
		case WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal:
		case WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal:
			break;

		case WGPUSurfaceGetCurrentTextureStatus_Timeout:
		case WGPUSurfaceGetCurrentTextureStatus_Outdated:
		case WGPUSurfaceGetCurrentTextureStatus_Lost:
//			wgpuTextureRelease(surfaceTexture.texture);
//			break;

		case WGPUSurfaceGetCurrentTextureStatus_Error:
//			BX_ASSERT(false, "");
			break;

		default:
			break;
		}

		m_textureView = WGPU_CHECK(wgpuTextureCreateView(surfaceTexture.texture, NULL) );
		wgpuRelease(surfaceTexture.texture);
	}

	void FrameBufferWGPU::create(uint8_t _num, const Attachment* _attachment)
	{
		m_numAttachments = _num;
		bx::memCopy(m_attachment, _attachment, sizeof(Attachment) * _num);

		postReset();
	}

	bool FrameBufferWGPU::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _colorFormat, TextureFormat::Enum _depthFormat)
	{
		bool result = true;

		Resolution resolution = s_renderWGPU->m_resolution;
		resolution.formatColor        = TextureFormat::Count == _colorFormat ? resolution.formatColor        : _colorFormat;
		resolution.formatDepthStencil = TextureFormat::Count == _depthFormat ? resolution.formatDepthStencil : _depthFormat;
		resolution.width  = _width;
		resolution.height = _height;

		m_width  = bx::max(resolution.width,  1);
		m_height = bx::max(resolution.height, 1);

		if (_denseIdx != UINT16_MAX)
		{
			resolution.reset &= ~BGFX_RESET_MSAA_MASK;
		}

		result = m_swapChain.create(_nwh, resolution);
		m_formatDepthStencil = m_swapChain.m_formatDepthStencil;

		m_denseIdx = _denseIdx;

		return result;
	}

	uint16_t FrameBufferWGPU::destroy()
	{
		preReset();

		if (isSwapChain() )
		{
			m_swapChain.destroy();
			m_needPresent = false;
		}

		m_numAttachments = 0;
		m_numColorAttachments = 0;
		m_depth = BGFX_INVALID_HANDLE;

		m_needResolve = false;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;
		return denseIdx;
	}

	void FrameBufferWGPU::preReset()
	{
		for (uint8_t ii = 0; ii < m_numColorAttachments; ++ii)
		{
			wgpuRelease(m_textureView[ii]);
		}

		wgpuRelease(m_depthStencilView);
	}

	void FrameBufferWGPU::postReset()
	{
		if (0 < m_numAttachments)
		{
			m_depth = BGFX_INVALID_HANDLE;
			m_numColorAttachments = 0;

			const TextureWGPU& firstTexture = s_renderWGPU->m_textures[m_attachment[0].handle.idx];
			m_width  = bx::max(firstTexture.m_width  >> m_attachment[0].mip, 1);
			m_height = bx::max(firstTexture.m_height >> m_attachment[0].mip, 1);

			for (uint8_t ii = 0; ii < m_numAttachments; ++ii)
			{
				const Attachment& at = m_attachment[ii];
				const TextureWGPU& texture = s_renderWGPU->m_textures[at.handle.idx];

				WGPUTextureViewDescriptor textureViewDesc =
				{
					.nextInChain     = NULL,
					.label           = WGPU_STRING_VIEW_INIT,
					.format          = s_textureFormat[texture.m_textureFormat].m_fmt,
					.dimension       = at.numLayers > 1 ? WGPUTextureViewDimension_2DArray : WGPUTextureViewDimension_2D,
					.baseMipLevel    = at.mip,
					.mipLevelCount   = 1,
					.baseArrayLayer  = at.layer,
					.arrayLayerCount = at.numLayers,
					.aspect          = WGPUTextureAspect_All,
					.usage           = WGPUTextureUsage_RenderAttachment,
				};

				if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
				{
					m_depthStencilView   = WGPU_CHECK(wgpuTextureCreateView(texture.m_texture, &textureViewDesc) );
					m_formatDepthStencil = texture.m_textureFormat;
					m_depth = at.handle;
				}
				else
				{
					m_textureView[m_numColorAttachments] = WGPU_CHECK(wgpuTextureCreateView(texture.m_texture, &textureViewDesc) );
					m_texture[m_numColorAttachments] = at.handle;
					m_numColorAttachments++;
				}
			}
		}
	}

	void FrameBufferWGPU::update(const Resolution& _resolution)
	{
		m_swapChain.update(m_swapChain.m_nwh, _resolution);
		m_width  = _resolution.width;
		m_height = _resolution.height;
		m_formatDepthStencil = m_swapChain.m_formatDepthStencil;
	}

	void FrameBufferWGPU::present()
	{
		if (m_needPresent)
		{
			m_swapChain.present();
			m_needPresent = false;
		}
	}

	void CommandQueueWGPU::init(WGPUDevice _device)
	{
		m_currentFrameInFlight = 0;
		m_queue = WGPU_CHECK(wgpuDeviceGetQueue(_device) );
		m_commandEncoder = WGPU_CHECK(wgpuDeviceCreateCommandEncoder(_device, NULL) );
	}

	void CommandQueueWGPU::shutdown()
	{
		wgpuRelease(m_queue);
	}

	static void queueWorkDoneCb(
		  WGPUQueueWorkDoneStatus _status
		, WGPUStringView _message
		, void* _userdata1
		, void* _userdata2
		)
	{
//		BX_ASSERT(WGPUQueueWorkDoneStatus_Success == _status, "%d", _status);
		BX_UNUSED(_status, _message, _userdata1, _userdata2);
		s_renderWGPU->m_cmd.m_counter--;
	}

	WGPUCommandEncoder CommandQueueWGPU::alloc()
	{
		s_renderWGPU->m_uniformScratchBuffer.flush();

		kick();

		return m_commandEncoder;
	}

	void CommandQueueWGPU::kick()
	{
		WGPUCommandBuffer commandBuffer = WGPU_CHECK(wgpuCommandEncoderFinish(m_commandEncoder, NULL) );

		WGPU_CHECK(wgpuQueueSubmit(m_queue, 1, &commandBuffer) );
		WGPU_CHECK(wgpuQueueOnSubmittedWorkDone(
			  m_queue
			, {
				.nextInChain = NULL,
				.mode        = WGPUCallbackMode_AllowProcessEvents,
				.callback    = queueWorkDoneCb,
				.userdata1   = (void*)uintptr_t(m_counter),
				.userdata2   = NULL,
			}) );
		wgpuRelease(commandBuffer);
		wgpuRelease(m_commandEncoder);
		++m_counter;

		WGPU_CHECK(wgpuInstanceProcessEvents(s_renderWGPU->m_instance) );

		m_commandEncoder = WGPU_CHECK(wgpuDeviceCreateCommandEncoder(s_renderWGPU->m_device, NULL) );
	}

	void CommandQueueWGPU::wait()
	{
		while (0 < m_counter)
		{
			WGPU_CHECK(wgpuInstanceProcessEvents(s_renderWGPU->m_instance) );
		}
	}

	void CommandQueueWGPU::frame()
	{
		kick();

		m_currentFrameInFlight = (m_currentFrameInFlight + 1) % s_renderWGPU->m_maxFrameLatency;
	}

	void CommandQueueWGPU::writeBuffer(WGPUBuffer _buffer, uint64_t _bufferOffset, const void* _data, size_t _size) const
	{
		WGPU_CHECK(wgpuQueueWriteBuffer(m_queue, _buffer, _bufferOffset, _data, _size) );
	}

	void CommandQueueWGPU::writeTexture(const WGPUTexelCopyTextureInfo& _destination, const void* _data, size_t _size, const WGPUTexelCopyBufferLayout& _source, const WGPUExtent3D& _writeSize) const
	{
		WGPU_CHECK(wgpuQueueWriteTexture(m_queue, &_destination, _data, _size, &_source, &_writeSize) );
	}

	void CommandQueueWGPU::copyBufferToBuffer(WGPUBuffer _source, uint64_t _sourceOffset, WGPUBuffer _destination, uint64_t _destinationOffset, uint64_t _size)
	{
		WGPU_CHECK(wgpuCommandEncoderCopyBufferToBuffer(m_commandEncoder, _source, _sourceOffset, _destination, _destinationOffset, _size) );
	}

	void CommandQueueWGPU::copyBufferToTexture(const WGPUTexelCopyBufferInfo& _source, const WGPUTexelCopyTextureInfo& _destination, const WGPUExtent3D& _copySize)
	{
		WGPU_CHECK(wgpuCommandEncoderCopyBufferToTexture(m_commandEncoder, &_source, &_destination, &_copySize) );
	}

	void CommandQueueWGPU::copyTextureToBuffer(const WGPUTexelCopyTextureInfo& _source, const WGPUTexelCopyBufferInfo& _destination, const WGPUExtent3D& _copySize)
	{
		WGPU_CHECK(wgpuCommandEncoderCopyTextureToBuffer(m_commandEncoder, &_source, &_destination, &_copySize) );
	}

	void CommandQueueWGPU::copyTextureToTexture(const WGPUTexelCopyTextureInfo& _source, const WGPUTexelCopyTextureInfo& _destination, const WGPUExtent3D& _copySize)
	{
		WGPU_CHECK(wgpuCommandEncoderCopyTextureToTexture(m_commandEncoder, &_source, &_destination, &_copySize) );
	}

	void TimerQueryWGPU::init()
	{
		WGPUDevice device = s_renderWGPU->m_device;

		static constexpr uint32_t kCount = BX_COUNTOF(m_query);

		WGPUQuerySetDescriptor querySetDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("TimerQuery"),
			.type        = WGPUQueryType_Timestamp,
			.count       = kCount,
		};

		m_querySet = WGPU_CHECK(wgpuDeviceCreateQuerySet(device, &querySetDesc) );

		static constexpr uint64_t kTimestampBufferSize = kCount * sizeof(uint64_t);

		WGPUBufferDescriptor resolveBufferDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("TimerQuery - Resolve Buffer"),
			.usage       = 0
				| WGPUBufferUsage_CopySrc
				| WGPUBufferUsage_QueryResolve
				,
			.size = kTimestampBufferSize,
			.mappedAtCreation = false,
		};

		m_resolve = WGPU_CHECK(wgpuDeviceCreateBuffer(device, &resolveBufferDesc) );

		WGPUBufferDescriptor readbackBufferDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("TimerQuery - Readback Buffer"),
			.usage       = 0
				| WGPUBufferUsage_MapRead
				| WGPUBufferUsage_CopyDst
				,
			.size = kTimestampBufferSize,
			.mappedAtCreation = false,
		};

		m_readback = WGPU_CHECK(wgpuDeviceCreateBuffer(device, &readbackBufferDesc) );
	}

	void TimerQueryWGPU::shutdown()
	{
		wgpuDestroy(m_querySet);
		wgpuDestroy(m_resolve);
		wgpuDestroy(m_readback);
	}

	uint32_t TimerQueryWGPU::begin(uint32_t _resultIdx, uint32_t _frameNum)
	{
		const uint32_t reserved = m_control.reserve(1);

		if (1 == reserved)
		{
			Result& result = m_result[_resultIdx];
			++result.m_pending;

			const uint32_t idx = m_control.m_current;
			Query& query = m_query[idx];
			query.m_resultIdx = _resultIdx;
			query.m_ready     = false;
			query.m_frameNum  = _frameNum;

			const uint32_t offset = idx * 2 + 0;
			WGPU_CHECK(wgpuCommandEncoderWriteTimestamp(s_renderWGPU->m_cmd.m_commandEncoder, m_querySet, offset) );

			return idx;
		}

		return UINT32_MAX;
	}

	void TimerQueryWGPU::end(uint32_t _idx)
	{
		m_control.commit(1);

		Query& query = m_query[_idx];
		query.m_ready = true;
		query.m_fence = s_renderWGPU->m_cmd.m_counter;

		const uint32_t offset = _idx * 2 + 1;
		WGPU_CHECK(wgpuCommandEncoderWriteTimestamp(s_renderWGPU->m_cmd.m_commandEncoder, m_querySet, offset) );

		m_control.consume(1);
	}

	void OcclusionQueryWGPU::init()
	{
		WGPUDevice device = s_renderWGPU->m_device;

		static constexpr uint32_t kCount = BX_COUNTOF(m_handle);

		WGPUQuerySetDescriptor querySetDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("OcclusionQuery"),
			.type        = WGPUQueryType_Occlusion,
			.count       = kCount,
		};

		m_querySet = WGPU_CHECK(wgpuDeviceCreateQuerySet(device, &querySetDesc) );

		static constexpr uint64_t kOcclusionQueryBufferSize = kCount * sizeof(uint64_t);

		WGPUBufferDescriptor resolveBufferDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("OcclusionQuery - Resolve Buffer"),
			.usage       = 0
				| WGPUBufferUsage_CopySrc
				| WGPUBufferUsage_QueryResolve
				,
			.size = kOcclusionQueryBufferSize,
			.mappedAtCreation = false,
		};

		m_resolve = WGPU_CHECK(wgpuDeviceCreateBuffer(device, &resolveBufferDesc) );

		WGPUBufferDescriptor readbackBufferDesc =
		{
			.nextInChain = NULL,
			.label       = toWGPUStringView("OcclusionQuery - Readback Buffer"),
			.usage       = 0
				| WGPUBufferUsage_MapRead
				| WGPUBufferUsage_CopyDst
				,
			.size = kOcclusionQueryBufferSize,
			.mappedAtCreation = false,
		};

		m_readback = WGPU_CHECK(wgpuDeviceCreateBuffer(device, &readbackBufferDesc) );
	}

	void OcclusionQueryWGPU::shutdown()
	{
		wgpuDestroy(m_querySet);
		wgpuDestroy(m_resolve);
		wgpuDestroy(m_readback);
	}

	void OcclusionQueryWGPU::begin(WGPURenderPassEncoder _renderPassEncoder, OcclusionQueryHandle _handle)
	{
		const uint32_t reserved = m_control.reserve(1);

		if (1 == reserved)
		{
			m_handle[m_control.m_current] = _handle;
			WGPU_CHECK(wgpuRenderPassEncoderBeginOcclusionQuery(_renderPassEncoder, _handle.idx) );
		}
	}

	void OcclusionQueryWGPU::end(WGPURenderPassEncoder _renderPassEncoder)
	{
		if (1 == m_control.getNumReserved() )
		{
			WGPU_CHECK(wgpuRenderPassEncoderEndOcclusionQuery(_renderPassEncoder) );

			m_control.commit(1);
		}
	}

	void OcclusionQueryWGPU::resolve()
	{
		if (0 < m_control.getNumUsed() )
		{
			WGPUCommandEncoder commandEncoder = s_renderWGPU->m_cmd.m_commandEncoder;

			constexpr uint64_t kOcclusionQueryBufferSize = BGFX_CONFIG_MAX_OCCLUSION_QUERIES * sizeof(uint64_t);

			WGPU_CHECK(wgpuCommandEncoderResolveQuerySet(
				  commandEncoder
				, m_querySet
				, 0
				, BGFX_CONFIG_MAX_OCCLUSION_QUERIES
				, m_resolve
				, 0
				) );

			WGPU_CHECK(wgpuCommandEncoderCopyBufferToBuffer(
				  commandEncoder
				, m_resolve
				, 0
				, m_readback
				, 0
				, kOcclusionQueryBufferSize
				) );
		}
	}

	static void readQueryResultsCb(WGPUMapAsyncStatus _status, WGPUStringView _message, void* _userdata1, void* _userdata2)
	{
		BX_UNUSED(_status, _message);
		OcclusionQueryWGPU& occlusionQuery = *(OcclusionQueryWGPU*)_userdata1;
		occlusionQuery.consumeResults( (Frame*)_userdata2);
	}

	void OcclusionQueryWGPU::readResultsAsync(Frame* _frame)
	{
		if (0 < m_control.getNumUsed() )
		{
			constexpr uint64_t kOcclusionQueryBufferSize = BGFX_CONFIG_MAX_OCCLUSION_QUERIES * sizeof(uint64_t);

			WGPU_CHECK(wgpuBufferMapAsync(
				  m_readback
				, WGPUMapMode_Read
				, 0
				, kOcclusionQueryBufferSize
				, {
					.nextInChain = NULL,
					.mode        = WGPUCallbackMode_AllowProcessEvents,
					.callback    = readQueryResultsCb,
					.userdata1   = this,
					.userdata2   = _frame,
				}) );
		}
	}

	void OcclusionQueryWGPU::consumeResults(Frame* _frame)
	{
		constexpr uint64_t kOcclusionQueryBufferSize = BGFX_CONFIG_MAX_OCCLUSION_QUERIES * sizeof(uint64_t);

		const uint64_t* result = (const uint64_t*)WGPU_CHECK(wgpuBufferGetConstMappedRange(
			  m_readback
			, 0
			, kOcclusionQueryBufferSize
			) );

		while (0 < m_control.getNumUsed() )
		{
			OcclusionQueryHandle handle = m_handle[m_control.m_read];
			if (isValid(handle) )
			{
				_frame->m_occlusion[handle.idx] = int32_t(result[handle.idx]);
			}

			m_control.consume(1);
		}

		WGPU_CHECK(wgpuBufferUnmap(m_readback) );
	}

	void OcclusionQueryWGPU::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.getNumUsed(); ii < num; ++ii)
		{
			OcclusionQueryHandle& handle = m_handle[(m_control.m_read + ii) % size];
			if (handle.idx == _handle.idx)
			{
				handle.idx = bgfx::kInvalidHandle;
			}
		}
	}

	void RendererContextWGPU::submitBlit(BlitState& _bs, uint16_t _view)
	{
		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureWGPU& src = m_textures[blit.m_src.idx];
			const TextureWGPU& dst = m_textures[blit.m_dst.idx];

			s_renderWGPU->m_cmd.copyTextureToTexture(
				{
					.texture  = src.m_texture,
					.mipLevel = blit.m_srcMip,
					.origin =
					{
						.x = blit.m_srcX,
						.y = blit.m_srcY,
						.z = blit.m_srcZ,
					},
					.aspect = WGPUTextureAspect_All,
				},
				{
					.texture  = dst.m_texture,
					.mipLevel = blit.m_dstMip,
					.origin =
					{
						.x = blit.m_dstX,
						.y = blit.m_dstY,
						.z = blit.m_dstZ,
					},
					.aspect = WGPUTextureAspect_All,
				},
				{
					.width              = blit.m_width,
					.height             = blit.m_height,
					.depthOrArrayLayers = bx::max<uint32_t>(1, blit.m_depth),
				}
				);
		}
	}

	void RendererContextWGPU::submitUniformCache(UniformCacheState& _ucs, uint16_t _view)
	{
		while (_ucs.hasItem(_view) )
		{
			const UniformCacheItem& uci = _ucs.advance();

			bx::memCopy(m_uniforms[uci.m_handle], &_ucs.m_frame->m_uniformCacheFrame.m_data[uci.m_offset], uci.m_size);
		}
	}

	void RendererContextWGPU::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		m_occlusionQuery.readResultsAsync(_render);
		WGPU_CHECK(wgpuInstanceProcessEvents(s_renderWGPU->m_instance) );

		if (updateResolution(_render->m_resolution) )
		{
			return;
		}

		if (_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		BGFX_WGPU_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorFrame);

		const int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = UINT32_MAX;

		frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS, _render->m_frameNum);

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);

			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);

			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		m_cmd.wait();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		uint32_t currentNumVertices = 0;

		static ViewState viewState;
		viewState.reset(_render);

		const bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
		setDebugWireframe(wireframe);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		bool hasPredefined = false;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		UniformCacheState ucs(_render);
		BlitState bs(_render);

		uint64_t blendFactor = 0;

		const uint64_t primType = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];

		bool viewHasScissor = false;
		bool restoreScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		bool isFrameBufferValid = true;

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		m_uniformScratchBuffer.begin();

		WGPURenderPassEncoder  renderPassEncoder  = NULL;
		WGPUComputePassEncoder computePassEncoder = NULL;

		WGPUBindGroupLayout bindGroupLayout = NULL;

		Profiler<TimerQueryWGPU> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			, true
			);

		StateCacheLru<BindGroup, 64> bindGroupLru;

		uint32_t msaaCount = 1;

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
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

				const uint32_t    itemIdx    = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged)
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;
					currentState.clear();
					hasPredefined = false;

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						if (NULL != renderPassEncoder)
						{
							WGPU_CHECK(wgpuRenderPassEncoderEnd(renderPassEncoder) );
							wgpuRelease(renderPassEncoder);
						}

						fbh = _render->m_view[view].m_fbh;
					}
				}

				if (!isCompute
				&& (viewChanged || NULL != computePassEncoder) )
				{
					if (NULL != computePassEncoder)
					{
						WGPU_CHECK(wgpuComputePassEncoderEnd(computePassEncoder) );
						wgpuRelease(computePassEncoder);
					}

					if (NULL != renderPassEncoder)
					{
						WGPU_CHECK(wgpuRenderPassEncoderEnd(renderPassEncoder) );
						wgpuRelease(renderPassEncoder);
					}

					if (item > 1)
					{
						profiler.end();
					}

					submitUniformCache(ucs, view);
					submitBlit(bs, view);

					BGFX_WGPU_PROFILER_END();
					setViewType(view, " ");
					BGFX_WGPU_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					FrameBufferWGPU& fb = isValid(fbh)
						? m_frameBuffers[fbh.idx]
						: m_backBuffer
						;

					const bool isSwapChain = fb.isSwapChain();

					if (isSwapChain)
					{
						fb.m_needPresent = true;
					}

					WGPUTextureView depthStencilTextureView = isSwapChain
						? fb.m_swapChain.m_depthStencilView
						: fb.m_depthStencilView
						;

					viewState.m_rect = _render->m_view[view].m_rect;
					Rect viewRect    = _render->m_view[view].m_rect;
					Rect scissorRect = _render->m_view[view].m_scissor;

					const Rect fbRect(0, 0, bx::narrowCast<uint16_t>(fb.m_width), bx::narrowCast<uint16_t>(fb.m_height) );
					viewRect.intersect(fbRect);
					scissorRect.intersect(fbRect);

					viewHasScissor   = !scissorRect.isZero();
					viewScissorRect  = viewHasScissor ? scissorRect : viewRect;
					restoreScissor   = false;

					const Clear& clr = _render->m_view[view].m_clear;

					const bool needClear  = BGFX_CLEAR_NONE != ( (BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH|BGFX_CLEAR_STENCIL) & clr.m_flags);
					const bool clearWhole = viewRect.isEqual(fbRect);

					WGPURenderPassColorAttachment colorAttachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];

					const uint32_t numColorAttachments = isSwapChain
						? 1
						: fb.m_numColorAttachments
						;

					for (uint32_t ii = 0; ii < numColorAttachments; ++ii)
					{
						WGPUTextureView colorTextureView = isSwapChain
							? fb.m_swapChain.m_textureView
							: (0 < fb.m_numColorAttachments ? fb.m_textureView[ii] : NULL)
							;
						WGPUTextureView msaaTextureView = isSwapChain
							? fb.m_swapChain.m_msaaTextureView
							: NULL
							;

						if (NULL != msaaTextureView)
						{
							bx::swap(colorTextureView, msaaTextureView);
							msaaCount = 4;
						}
						else
						{
							msaaCount = 1;
						}

						colorAttachment[ii] =
						{
							.nextInChain   = NULL,
							.view          = colorTextureView,
							.depthSlice    = WGPU_DEPTH_SLICE_UNDEFINED,
							.resolveTarget = msaaTextureView,
							.loadOp        = clearWhole && (BGFX_CLEAR_COLOR & clr.m_flags)
								? WGPULoadOp_Clear
								: WGPULoadOp_Load
								,
							.storeOp       = WGPUStoreOp_Store,
							.clearValue    = {},
						};

						if (0 != (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags) )
						{
							uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, clr.m_index[ii]);
							const float* rgba = _render->m_colorPalette[index];
							colorAttachment[ii].clearValue =
							{
								.r = rgba[0],
								.g = rgba[1],
								.b = rgba[2],
								.a = rgba[3],
							};
						}
						else
						{
							colorAttachment[ii].clearValue =
							{
								.r = clr.m_index[0] * 1.0/255.0,
								.g = clr.m_index[1] * 1.0/255.0,
								.b = clr.m_index[2] * 1.0/255.0,
								.a = clr.m_index[3] * 1.0/255.0,
							};
						}
					}

					const bool stencilRw = hasStencil(TextureFormat::Enum(fb.m_formatDepthStencil) );

					WGPURenderPassDepthStencilAttachment depthStencilAttachement =
					{
						.nextInChain       = NULL,
						.view              = depthStencilTextureView,
						.depthLoadOp       = clearWhole && (BGFX_CLEAR_DEPTH & clr.m_flags)
							? WGPULoadOp_Clear
							: WGPULoadOp_Load
							,
						.depthStoreOp      = WGPUStoreOp_Store,
						.depthClearValue   = clr.m_depth,
						.depthReadOnly     = false,
						.stencilLoadOp     = !stencilRw
							? WGPULoadOp_Undefined
							: (clearWhole && (BGFX_CLEAR_STENCIL & clr.m_flags) ? WGPULoadOp_Clear : WGPULoadOp_Load)
							,
						.stencilStoreOp    = !stencilRw ? WGPUStoreOp_Undefined : WGPUStoreOp_Store,
						.stencilClearValue = clr.m_stencil,
						.stencilReadOnly   = !stencilRw,
					};

					WGPURenderPassDescriptor renderPassDesc =
					{
						.nextInChain            = NULL,
						.label                  = toWGPUStringView(s_viewName[view]),
						.colorAttachmentCount   = numColorAttachments,
						.colorAttachments       = colorAttachment,
						.depthStencilAttachment = NULL == depthStencilTextureView
							? NULL
							: &depthStencilAttachement
							,
						.occlusionQuerySet      = m_occlusionQuery.m_querySet,
						.timestampWrites        = NULL,
					};

					WGPUCommandEncoder cmdEncoder = m_cmd.alloc();
					renderPassEncoder = WGPU_CHECK(wgpuCommandEncoderBeginRenderPass(cmdEncoder, &renderPassDesc) );

					wgpuRenderPassEncoderSetViewport(
						  renderPassEncoder
						, float(viewRect.m_x)
						, float(viewRect.m_y)
						, float(viewRect.m_width)
						, float(viewRect.m_height)
						, 0.0f
						, 1.0f
						);

					if (!clearWhole && needClear)
					{
						clearQuad(renderPassEncoder, fbh, msaaCount, _clearQuad, viewRect, clr, _render->m_colorPalette);
					}

					wgpuRenderPassEncoderSetScissorRect(
						  renderPassEncoder
						, viewScissorRect.m_x
						, viewScissorRect.m_y
						, viewScissorRect.m_width
						, viewScissorRect.m_height
						);
					restoreScissor = false;
				}

				if (isCompute)
				{
					if (NULL == computePassEncoder)
					{
						BGFX_WGPU_PROFILER_END();
						setViewType(view, "C");
						BGFX_WGPU_PROFILER_BEGIN(view, kColorCompute);

						if (NULL != renderPassEncoder)
						{
							WGPU_CHECK(wgpuRenderPassEncoderEnd(renderPassEncoder) );
							wgpuRelease(renderPassEncoder);
						}

						WGPUCommandEncoder cmdEncoder = m_cmd.alloc();
						computePassEncoder = WGPU_CHECK(wgpuCommandEncoderBeginComputePass(cmdEncoder, NULL) );
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					bool constantsChanged = compute.m_uniformBegin < compute.m_uniformEnd;
					rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

					if (key.m_program.idx != currentProgram.idx)
					{
						currentProgram = key.m_program;

						programChanged =
							constantsChanged = true;
					}

					const ProgramWGPU& program = m_program[currentProgram.idx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}
					}

					ChunkedScratchBufferOffset sbo;
					const uint32_t vsSize = program.m_vsh->m_size;

					if (constantsChanged
					||  hasPredefined)
					{
						viewState.setPredefined<4>(this, view, program, _render, compute);
						m_uniformScratchBuffer.write(sbo, m_vsScratch, vsSize);
					}

					if (programChanged)
					{
						const ComputePipeline& computePipeline = *getPipeline(key.m_program, renderBind);
						bindGroupLayout = computePipeline.bindGroupLayout;
						WGPU_CHECK(wgpuComputePassEncoderSetPipeline(computePassEncoder, computePipeline.pipeline) );
					}

					bx::HashMurmur3 murmur;
					murmur.begin(0x434f4d50);
					murmur.add(renderBind.m_bind, sizeof(renderBind.m_bind) );
					murmur.add(sbo.buffer);
					murmur.add(vsSize);
					const uint32_t bindHash = murmur.end();

					const BindGroup* bindGroupCached = bindGroupLru.find(bindHash);
					if (NULL == bindGroupCached)
					{
						const BindGroup bindGroup = createBindGroup(bindGroupLayout, program, renderBind, sbo, true);
						bindGroupCached = bindGroupLru.add(bindHash, bindGroup, 0);
					}

					WGPU_CHECK(wgpuComputePassEncoderSetBindGroup(computePassEncoder, 0, bindGroupCached->bindGroup, bindGroupCached->numOffsets, sbo.offsets) );

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferWGPU& indirect = m_vertexBuffers[compute.m_indirectBuffer.idx];
						const WGPUBuffer buffer = indirect.m_buffer;

						const uint32_t numDrawIndirect = UINT32_MAX == compute.m_numIndirect
							? indirect.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: compute.m_numIndirect
							;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
							WGPU_CHECK(wgpuComputePassEncoderDispatchWorkgroupsIndirect(computePassEncoder, buffer, args) );
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						WGPU_CHECK(wgpuComputePassEncoderDispatchWorkgroups(computePassEncoder, compute.m_numX, compute.m_numY, compute.m_numZ) );
					}

					continue;
				}

				if (NULL != computePassEncoder)
				{
					WGPU_CHECK(wgpuComputePassEncoderEnd(computePassEncoder) );
					wgpuRelease(computePassEncoder);

					setViewType(view, " ");
					BGFX_WGPU_PROFILER_END();
					BGFX_WGPU_PROFILER_BEGIN(view, kColorDraw);
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = true
						&& isValid(draw.m_occlusionQuery)
						&& !hasOcclusionQuery
						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags & BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) )
						;

					if (occluded
					||  !isFrameBufferValid
					||  0 == draw.m_streamMask
					||  _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor) )
					{
						continue;
					}
				}

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				currentNumVertices = draw.m_numVertices;

				const uint64_t state = draw.m_stateFlags;

				const RenderPipeline& renderPipeline = *getPipeline(
					  key.m_program
					, fbh
					, msaaCount
					, draw.m_stateFlags
					, draw.m_stencil
					, draw.m_streamMask
					, draw.m_stream
					, uint8_t(draw.m_instanceDataStride/16)
					, draw.isIndex16()
					, renderBind
					);
				bindGroupLayout = renderPipeline.bindGroupLayout;
				WGPU_CHECK(wgpuRenderPassEncoderSetPipeline(renderPassEncoder, renderPipeline.pipeline) );

				const ProgramWGPU& program = m_program[key.m_program.idx];

				if (constantsChanged
				||  currentProgram.idx != key.m_program.idx)
				{
					currentProgram = key.m_program;

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

					hasPredefined = 0 < program.m_numPredefined;
					constantsChanged = true;
				}

				if (constantsChanged
				||  hasPredefined)
				{
					const uint32_t ref = (draw.m_stateFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
					viewState.m_alphaRef = ref/255.0f;
					viewState.setPredefined<4>(this, view, program, _render, draw);
				}

				ChunkedScratchBufferOffset sbo;
				const uint32_t vsSize = program.m_vsh->m_size;
				const uint32_t fsSize = NULL != program.m_fsh ? program.m_fsh->m_size : 0;
				m_uniformScratchBuffer.write(sbo, m_vsScratch, vsSize, m_fsScratch, fsSize);

				bx::HashMurmur3 murmur;
				murmur.begin(0x44524157);
				murmur.add(renderBind.m_bind, sizeof(renderBind.m_bind) );
				murmur.add(sbo.buffer);
				murmur.add(vsSize);
				murmur.add(fsSize);
				const uint32_t bindHash = murmur.end();

				const BindGroup* bindGroupCached = bindGroupLru.find(bindHash);
				if (NULL == bindGroupCached)
				{
					const BindGroup bind = createBindGroup(bindGroupLayout, program, renderBind, sbo, false);
					bindGroupCached = bindGroupLru.add(bindHash, bind, 0);
				}

				WGPU_CHECK(wgpuRenderPassEncoderSetBindGroup(renderPassEncoder, 0, bindGroupCached->bindGroup, bindGroupCached->numOffsets, sbo.offsets) );

				if (0 != changedStencil)
				{
					const uint32_t fstencil = unpackStencil(0, draw.m_stencil);
					const uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
					WGPU_CHECK(wgpuRenderPassEncoderSetStencilReference(renderPassEncoder, ref) );
				}

				constexpr uint64_t kF0 = BGFX_STATE_BLEND_FACTOR;
				constexpr uint64_t kF1 = BGFX_STATE_BLEND_INV_FACTOR;
				constexpr uint64_t kF2 = BGFX_STATE_BLEND_FACTOR<<4;
				constexpr uint64_t kF3 = BGFX_STATE_BLEND_INV_FACTOR<<4;
				bool hasFactor = 0
					|| kF0 == (state & kF0)
					|| kF1 == (state & kF1)
					|| kF2 == (state & kF2)
					|| kF3 == (state & kF3)
					;

				if (hasFactor
				&&  blendFactor != draw.m_rgba)
				{
					blendFactor = draw.m_rgba;

					WGPUColor bf =
					{
						.r = ( (draw.m_rgba>>24)     )/255.0f,
						.g = ( (draw.m_rgba>>16)&0xff)/255.0f,
						.b = ( (draw.m_rgba>> 8)&0xff)/255.0f,
						.a = ( (draw.m_rgba    )&0xff)/255.0f,
					};

					WGPU_CHECK(wgpuRenderPassEncoderSetBlendConstant(renderPassEncoder, &bf) );
				}

				const uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					if (UINT16_MAX == scissor)
					{
						if (restoreScissor
						||  viewHasScissor)
						{
							restoreScissor = false;

							wgpuRenderPassEncoderSetScissorRect(
								  renderPassEncoder
								, viewScissorRect.m_x
								, viewScissorRect.m_y
								, viewScissorRect.m_width
								, viewScissorRect.m_height
								);
						}
					}
					else
					{
						restoreScissor = true;
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);
						if (scissorRect.isZeroArea() )
						{
							continue;
						}

						wgpuRenderPassEncoderSetScissorRect(
							  renderPassEncoder
							, scissorRect.m_x
							, scissorRect.m_y
							, scissorRect.m_width
							, scissorRect.m_height
							);
					}
				}

				bool vertexStreamChanged = programChanged || hasVertexStreamChanged(currentState, draw);

				if (vertexStreamChanged)
				{
					currentState.m_streamMask             = draw.m_streamMask;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset     = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride     = draw.m_instanceDataStride;

					WGPUBuffer buffers[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1 /* instanced buffer */];
					uint32_t offsets[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1 /* instanced buffer */];
					uint32_t sizes[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1 /* instanced buffer */];

					uint32_t numVertices = draw.m_numVertices;

					uint32_t numStreams = 0;

					if (UINT8_MAX != draw.m_streamMask)
					{
						for (BitMaskToIndexIteratorT it(draw.m_streamMask)
							; !it.isDone()
							; it.next(), numStreams++
							)
						{
							const uint8_t idx = it.idx;

							currentState.m_stream[idx].m_layoutHandle = draw.m_stream[idx].m_layoutHandle;
							currentState.m_stream[idx].m_handle       = draw.m_stream[idx].m_handle;
							currentState.m_stream[idx].m_startVertex  = draw.m_stream[idx].m_startVertex;

							const uint16_t handle = draw.m_stream[idx].m_handle.idx;
							const VertexBufferWGPU&vb = m_vertexBuffers[handle];
							const uint16_t layoutIdx = isValid(draw.m_stream[idx].m_layoutHandle)
								? draw.m_stream[idx].m_layoutHandle.idx
								: vb.m_layoutHandle.idx;
							const VertexLayout& layout = m_vertexLayouts[layoutIdx];
							const uint32_t stride = layout.m_stride;

							buffers[numStreams] = vb.m_buffer;
							offsets[numStreams] = draw.m_stream[idx].m_startVertex * stride;

							numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
								? vb.m_size/stride
								: draw.m_numVertices
								, numVertices
								);

							sizes[numStreams] = stride * numVertices;
						}

						if (isValid(draw.m_instanceDataBuffer) )
						{
							const VertexBufferWGPU& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];

							buffers[numStreams] = inst.m_buffer;
							offsets[numStreams] = draw.m_instanceDataOffset;
							sizes[numStreams] = draw.m_instanceDataStride * draw.m_numInstances;

							++numStreams;
						}
					}

					for (uint8_t ii = 0; ii < numStreams; ++ii)
					{
						WGPU_CHECK(wgpuRenderPassEncoderSetVertexBuffer(renderPassEncoder, ii, buffers[ii], offsets[ii], sizes[ii]) );
					}
				}

				if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx
				||  currentState.isIndex16() != draw.isIndex16() )
				{
					currentState.m_indexBuffer = draw.m_indexBuffer;
					currentState.m_submitFlags = draw.m_submitFlags;

					uint16_t handle = draw.m_indexBuffer.idx;
					if (kInvalidHandle != handle)
					{
						const IndexBufferWGPU& ib = m_indexBuffers[handle];
						WGPU_CHECK(wgpuRenderPassEncoderSetIndexBuffer(
							  renderPassEncoder
							, ib.m_buffer
							, draw.isIndex16() ? WGPUIndexFormat_Uint16 : WGPUIndexFormat_Uint32
							, 0
							, WGPU_WHOLE_SIZE
							) );
					}
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices       = currentNumVertices;
					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(renderPassEncoder, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indirectBuffer) )
					{
						const VertexBufferWGPU& indirect = m_vertexBuffers[draw.m_indirectBuffer.idx];
						numDrawIndirect = UINT32_MAX == draw.m_numIndirect
							? indirect.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;

						if (isValid(draw.m_indexBuffer) )
						{
							if (isValid(draw.m_numIndirectBuffer) )
							{
								const IndexBufferWGPU& numIndirect = m_indexBuffers[draw.m_numIndirectBuffer.idx];

								WGPU_CHECK(stubRenderPassEncoderMultiDrawIndexedIndirect(
									  renderPassEncoder
									, indirect.m_buffer
									, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									, numDrawIndirect
									, numIndirect.m_buffer
									, draw.m_numIndirectIndex * sizeof(uint32_t)
									) );
							}
							else
							{
								WGPU_CHECK(stubRenderPassEncoderMultiDrawIndexedIndirect(
									  renderPassEncoder
									, indirect.m_buffer
									, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									, numDrawIndirect
									, NULL
									, 0
									) );
							}
						}
						else
						{
							if (isValid(draw.m_numIndirectBuffer) )
							{
								const IndexBufferWGPU& numIndirect = m_indexBuffers[draw.m_numIndirectBuffer.idx];

								WGPU_CHECK(stubRenderPassEncoderMultiDrawIndirect(
									  renderPassEncoder
									, indirect.m_buffer
									, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									, numDrawIndirect
									, numIndirect.m_buffer
									, draw.m_numIndirectIndex * sizeof(uint32_t)
									) );
							}
							else
							{
								WGPU_CHECK(stubRenderPassEncoderMultiDrawIndirect(
									  renderPassEncoder
									, indirect.m_buffer
									, draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									, numDrawIndirect
									, NULL
									, 0
									) );
							}
						}
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							if (UINT32_MAX == draw.m_numIndices)
							{
								const IndexBufferWGPU& ib = m_indexBuffers[draw.m_indexBuffer.idx];
								const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								WGPU_CHECK(wgpuRenderPassEncoderDrawIndexed(renderPassEncoder, numIndices, draw.m_numInstances, 0, 0, 0) );
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								WGPU_CHECK(wgpuRenderPassEncoderDrawIndexed(renderPassEncoder, numIndices, draw.m_numInstances, draw.m_startIndex, 0, 0) );
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							WGPU_CHECK(wgpuRenderPassEncoderDraw(renderPassEncoder, numVertices, draw.m_numInstances, 0, 0) );
						}
					}

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end(renderPassEncoder);
					}

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += numInstances;
					statsNumDrawIndirect[primIndex]   += numDrawIndirect;
					statsNumIndices                   += numIndices;
				}
			}

			if (NULL != renderPassEncoder)
			{
				WGPU_CHECK(wgpuRenderPassEncoderEnd(renderPassEncoder) );
				wgpuRelease(renderPassEncoder);
			}

			if (NULL != computePassEncoder)
			{
				WGPU_CHECK(wgpuComputePassEncoderEnd(computePassEncoder) );
				wgpuRelease(computePassEncoder);

				setViewType(view, "C");
				BGFX_WGPU_PROFILER_END();
				BGFX_WGPU_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			m_occlusionQuery.resolve();

			if (0 < _render->m_numRenderItems)
			{
				captureElapsed = -bx::getHPCounter();
//				capture();
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		BGFX_WGPU_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::min<int64_t>(min, frameTime);
		max = bx::max<int64_t>(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;
		BX_UNUSED(elapsedGpuMs);

		static int64_t presentMin = m_presentElapsed;
		static int64_t presentMax = m_presentElapsed;
		presentMin = bx::min<int64_t>(presentMin, m_presentElapsed);
		presentMax = bx::max<int64_t>(presentMax, m_presentElapsed);

		if (UINT32_MAX != frameQueryIdx)
		{
			m_gpuTimer.end(frameQueryIdx);
		}

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeBegin;
		perfStats.cpuTimerFreq  = timerFreq;

		perfStats.gpuTimeBegin  = 0;
		perfStats.gpuTimeEnd    = 0;
		perfStats.gpuTimerFreq  = 1000000000;
		perfStats.gpuFrameNum   = 0;

		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;

		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;


		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			TextVideoMem& tvm = m_textVideoMem;

			static int64_t next = timeEnd;

			if (timeEnd >= next)
			{
				next = timeEnd + timerFreq;

				double freq = double(timerFreq);
				double toMs = 1000.0 / freq;

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

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "       Frame: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);
				tvm.printf(10, pos++, 0x8b, "     Present: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] "
					, double(m_presentElapsed)*toMs
					, double(presentMin)*toMs
					, double(presentMax)*toMs
					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, " Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "   Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] %c GPU %7.4f [ms] (latency %d) "
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
					tvm.printf(10, pos++, 0x8b, "   %9s: %7d (#inst: %5d), submitted: %7d "
						, getName(Topology::Enum(ii) )
						, statsNumPrimsRendered[ii]
						, statsNumInstances[ii]
						, statsNumPrimsSubmitted[ii]
						);
				}

				if (NULL != m_renderDocDll)
				{
					tvm.printf(tvm.m_width-27, 0, 0x4f, " [F11 - RenderDoc capture] ");
				}

				tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", statsNumIndices);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);
				pos++;

				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %7.4f [ms] ", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], " Submit wait: %7.4f [ms] ", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %7.4f [ms] ", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
				presentMin = m_presentElapsed;
				presentMax = m_presentElapsed;
			}

			dbgTextSubmit(this, _textVideoMemBlitter, tvm);
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			dbgTextSubmit(this, _textVideoMemBlitter, _render->m_textVideoMem);
		}

		m_presentElapsed = 0;

		m_uniformScratchBuffer.end();

		m_cmd.frame();
	}


} /* namespace wgpu */ } // namespace bgfx

#else

namespace bgfx { namespace wgpu
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace wgpu */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_WEBGPU
